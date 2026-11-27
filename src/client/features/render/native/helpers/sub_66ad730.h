#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Layout of the object passed to sub_66ad730 in rcx (this), reverse-engineered from the
// disassembly of [0x66ad730, 0x66ad818), Minecraft Windows 1.26.62.01.
// Every [reg+off] access listed below is a [V] fact (cited by instruction).
// Field names and meanings are [open] decisions; see docs/functions/66ad730.md '## DECISIONS'.
// This header is the real derived layout (lifted, not a placeholder).

struct sub_66ad730_state {
    std::uint8_t pad_0x00[0x08];          // +0x00
    void* refObject;                       // +0x08: intrusive refcounted object (R 0x66ad7b9)
    std::uint8_t pad_0x10[0x08];          // +0x10
    void* resourceObject;                  // +0x18: intrusive refcounted object (R 0x66ad785)
    std::uint8_t pad_0x20[0x08];          // +0x20
    void* buffer;                          // +0x28: buffer start pointer (R 0x66ad739, W 0x66ad77a)
    std::uint8_t pad_0x30[0x08];          // +0x30
    void* bufferEnd;                       // +0x38: buffer end pointer (R 0x66ad742, W 0x66ad77d)
};

// Refcounted object layout (objects at self+0x08 and self+0x18):
//   +0x00 vfptr   (void**)                 (R 0x66ad794/0x66ad7a9/0x66ad7c8/0x66ad7dd)
//   +0x08 strongRefs (std::int32)          (R/W 0x66ad78e/0x66ad7a3/0x66ad7c2/0x66ad7d7)
//   +0x0C weakRefs  (std::int32)           (R/W 0x66ad7a3/0x66ad7d7)
// vfptr[0] = destroyer, vfptr[1] = deallocator; both are invoked through the
// sub_eea6040 "jmp rax" vendor thunk (caller pre-loads RAX with vfptr[n]).
struct RefCountedObject {
    void* vfptr;
    std::int32_t strongRefs;
    std::int32_t weakRefs;
};

// Layout assertions for every field of sub_66ad730_state read or written.
static_assert(offsetof(sub_66ad730_state, refObject) == 0x08, "sub_66ad730 reads self+0x08 (0x66ad7b9)");
static_assert(offsetof(sub_66ad730_state, resourceObject) == 0x18, "sub_66ad730 reads self+0x18 (0x66ad785)");
static_assert(offsetof(sub_66ad730_state, buffer) == 0x28, "sub_66ad730 reads/writes self+0x28 (0x66ad739/0x66ad77a)");
static_assert(offsetof(sub_66ad730_state, bufferEnd) == 0x38, "sub_66ad730 reads/writes self+0x38 (0x66ad742/0x66ad77d)");
static_assert(sizeof(sub_66ad730_state) == 0x40, "sub_66ad730_state size");

// Layout assertions for RefCountedObject fields read/written via pointer casts.
static_assert(offsetof(RefCountedObject, vfptr) == 0x00, "RefCountedObject vfptr at +0x00");
static_assert(offsetof(RefCountedObject, strongRefs) == 0x08, "RefCountedObject strongRefs at +0x08 (0x66ad78e etc)");
static_assert(offsetof(RefCountedObject, weakRefs) == 0x0C, "RefCountedObject weakRefs at +0x0C (0x66ad7a3 etc)");

// Signature (x64 Microsoft ABI) - [V]: rcx copied to rsi at 0x66ad736 ('this').
// Return value in rax: [UNVERIFIED: 0x66ad7fd the normal `ret` path does not write rax,
// so the return value is indeterminate from the listing; 0 is returned there.
// [UNVERIFIED: 0x66ad811 call qword ptr [0xF9A8C78] is _invoke_watson via data slot;
// the error path then executes int3 (noreturn).
uintptr_t sub_66ad730(sub_66ad730_state* self);

} // namespace native::helpers
