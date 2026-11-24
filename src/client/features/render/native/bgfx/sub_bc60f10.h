#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"

namespace native {

// Layout reconstructed from the disassembly of 0xbc60f10 (size 0x22a, Frame::commitSideTable).
// Every offset below is read or written by that function [V] (instruction cites in sub_bc60f10.cpp).
//
// The side table holds, for each of the 65 binding stages, a variable-length array of 0x14-byte
// bindings (this is the storage behind ranged/multi binds). One SideTable is stored per render
// item at Frame+0x8B4778, indexed by draw index (stride 8).
struct SideEntry {
    void* data;              // +0x00  pointer to the binding array (count * 0x14 bytes allocated)
    std::uint64_t count;     // +0x08  number of bindings in the array
};                           // sizeof == 0x10

struct SideTable {
    SideEntry entry[0x41];   // +0x00  65 stages x 0x10 bytes = 0x410
    std::uint32_t used;      // +0x410 number of stages in use (u32), then 4 pad bytes
};                           // sizeof == 0x418 (the allocation size the function requests)

struct Frame {
    std::uint8_t pad_0x0000[0x8B4778];
    SideTable* m_sideTable;  // +0x8B4778 array of per-render-item SideTable* (8 bytes each)
};

// Allocator handle used by the function: the encoder's bx::AllocatorI*, stored at image slot
// RVA 0x12ADF800 (original: 0xbc60f48  mov rcx,[0x12ADF800]). The function calls realloc, which
// lives at vtable slot 1, reached through the jmp-rax trampoline slot [0xF99FFA0]
// (sub_eea6040 is `jmp rax`). The original does:
//   mov rax,[rcx]; mov rax,[rax+8]      ; rax = allocator->vtable[1] = realloc
//   call qword ptr [0xF99FFA0]          ; tail-call rax, rcx == allocator (this) preserved
// so the lifted code reads vtable slot 1 at call time and invokes it with rcx == allocator.
struct AllocatorI {
    void* vptr;              // +0x00
};
using ReallocFn = void* (*)(void* alloc, void* ptr, std::uint32_t size,
                            std::uint32_t align, const char* file, std::uint32_t line);

inline AllocatorI* g_allocator() {                                            // mov rcx,[0x12ADF800]
    return *reinterpret_cast<AllocatorI**>(RewriteRegistry::imageBase() + 0x12ADF800ull);
}

inline ReallocFn allocatorRealloc(AllocatorI* alloc) {                        // mov rax,[rcx]; mov rax,[rax+8]
    return reinterpret_cast<ReallocFn>(reinterpret_cast<void**>(alloc->vptr)[1]);
}

// realloc(alloc, ptr, size, align = 0, file = 0, line = 0); size 0 frees [V call shape at
// 0xbc60f72/0xbc60ffc/0xbc61044/0xbc610f1]. memset/memcpy are CRT intrinsics
// (0xbc60f86/0xbc6112b call 0xEEC6ED0, 0xbc61070 call 0xEBCE390).

static constexpr std::size_t kSideEntryDataOffset = 0x00;
static constexpr std::size_t kSideEntryCountOffset = 0x08;
static constexpr std::size_t kSideEntrySize = 0x10;
static constexpr std::size_t kSideTableStageCount = 0x41;
static constexpr std::size_t kSideTableUsedOffset = 0x410;
static constexpr std::size_t kSideTableSize = 0x418;
static constexpr std::size_t kFrameSideTableOffset = 0x8B4778;
static constexpr std::size_t kBindingSize = 0x14;
static constexpr std::size_t kSideTableAllocSize = 0x418;

static_assert(offsetof(SideEntry, data) == kSideEntryDataOffset, "SideEntry::data must be at +0x00");
static_assert(offsetof(SideEntry, count) == kSideEntryCountOffset, "SideEntry::count must be at +0x08");
static_assert(sizeof(SideEntry) == kSideEntrySize, "SideEntry must be 0x10 bytes");
static_assert(offsetof(SideTable, used) == kSideTableUsedOffset, "SideTable::used must be at +0x410");
static_assert(sizeof(SideTable) == kSideTableSize, "SideTable must be 0x418 bytes");
static_assert(offsetof(Frame, m_sideTable) == kFrameSideTableOffset, "Frame::m_sideTable must be at +0x8B4778");
static_assert(offsetof(AllocatorI, vptr) == 0x00, "AllocatorI::vptr must be at +0x00");

// Lifted function: 0xbc60f10, size 0x22a, returns void.
// x64 ABI: rcx = frame (Frame*), edx = idx (std::uint32_t), r8 = src (const SideTable*).
extern "C" void commitSideTable(Frame* frame, std::uint32_t idx, const SideTable* src);

} // namespace native
