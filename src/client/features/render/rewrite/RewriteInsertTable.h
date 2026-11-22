#pragma once

// Q3a: one table-driven inserter replacing the 21 thin insert clones.
//
// Each thin clone (size 0x139, verified by rdis in docs/progress/oc_U-EQ3a.md) is ONE template:
//   prologue; mov rdi,rdx (desc); mov rsi,rcx (builder); ProfileScope;
//   mov [rbp+0x10],rdi              (InsertVariant.mDescription = desc, at variant+0)
//   mov byte ptr [rbp+0x18],<TAG>   (InsertVariant.mTag = tag, at variant+8)   <-- differs per clone
//   mov rax,[rsi]; mov rax,[rax+0x<SLOT>]   (builder->vtable[groupSlot])       <-- differs per group
//   lea rdx,[rbp+0x10] (&variant); mov rcx,rsi; call qword ptr [0xF99FFA0] (CFG thunk)
//
// The only observable pre-call output of a clone is the InsertVariant {desc, tag} plus the group-slot target.
// A single inserter parameterized by (groupSlot, tag) builds InsertVariant {desc=rdx, tag} and calls
// builder->vtable[groupSlot](builder, &variant), reproducing an IDENTICAL InsertVariant stream at all 21 sites
// (same desc pointer, same tag, same group slot).
//
// kEntries maps each clone RVA to {group, tag, groupSlot, name}; every tag and slot was read verbatim from
// rdis and is tagged [V] in docs/progress/oc_U-EQ3a.md. No existing hook registration, HookManager.cpp, CMake,
// or Sigs.json is touched: detours are installed late via HookTable::add from RewriteInsertTable.cpp.


#include "client/features/render/rewrite/RewriteDescriptions.h"
#include "sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h"

namespace mce::framebuilder {
struct InsertVariant;
}

// One row of the clone table: a thin clone's entry point and the (group, tag, groupSlot) it hard-codes.
struct RwInsertEntry {
    uintptr_t cloneRva;  // the thin clone's entry point (a call site in the game)
    RewriteGroup group;
    uint64_t tag;        // variant tag the clone stores at InsertVariant+8
    uintptr_t groupSlot; // byte offset into the builder vtable the clone calls
    const char* name;    // description name (RewriteDescriptions)
};

struct RewriteInsertTable {
    // All 21 thin clones, tag and groupSlot verified [V] by rdis (docs/progress/oc_U-EQ3a.md).
    static const RwInsertEntry kEntries[21];
    static size_t count() { return 21; }

    // Find the entry whose cloneRva matches a call site; nullptr when none.
    static const RwInsertEntry* findByClone(uintptr_t cloneRva);

    // The single table-driven inserter. Builds InsertVariant {mDescription=desc, mTag=e.tag} on the stack and
    // calls builder->vtable[e.groupSlot](builder, &variant). Identical stream to the clone it replaces:
    // same desc pointer, same tag, same group-slot target.
    static uint64_t insert(void* builder, void* desc, const RwInsertEntry& e);

    // Pure self test (no game): each entry's group slot is called once with the same desc pointer and tag. true when all 21 pass.
    static bool selfTest();
};
