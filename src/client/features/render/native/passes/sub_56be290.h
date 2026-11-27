#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_56be290 (0x56be290, size 0xc6, 1.26.62.01): pass-tasks frame-graph helper.
//
// Operand object layout (rcx = a0) [V: rdis dis 0x56be290]:
//   +0x00  void* vtable        (8-byte write at [rcx]: the constant materialized by lea rax,[0xF25CB90])
//   +0x70  void* data          (8-byte read at [rcx+0x70]; byte write 0 at [rcx+0x70])
//   +0x80  uint64_t field0x80  (8-byte write 0 at [rcx+0x80])
//   +0x88  uint64_t field0x88  (8-byte read at [rcx+0x88], compared to 0x10; later written 0xF)
//   +0x10  void* refObj        (8-byte read at [rcx+0x10]; lock-dec dword at *refObj+0xC)
//   +0x18  void* releaseObj    (8-byte read at [rcx+0x18]; address &a0+0x18 passed to the slot thunk)
//
// Refcounted object pointed to by +0x10 [V]:
//   +0x00  void* vfptr         (8-byte read: vfptr, then vfptr[8] loaded dead)
//   +0x0C  uint32_t field0x0C  (4-byte read/write: lock dec dword)
//
// Callees [V]:
//   - sub_e935700 (lift set, docs/data/native_functions.tsv 0xe935700, boundary class lift): direct call at 0x56be2db.
//     Forward-declared below; called through its native symbol (brief rule 66).
//   - sub_eea6040 (boundary/vendor, docs/data/native_boundary.tsv line 506: thunk via data slot 0xF99FFA0):
//     indirect calls at 0x56be30b and 0x56be327 through data slot 0xF99FFA0 (brief rule 69: read the slot at call time).
//   - unknown target through data slot 0xF9A8C78 at 0x56be34f (neither table lists it): slot read per brief rule 69,
//     then int3 (noreturn path). Not a blocker (brief rule 69).
//
// Return: void. No instruction deliberately writes RAX; exits are ret or a tail jmp through data slot 0xF99FFA0.

struct Sub56be290Layout {
    static constexpr std::size_t kOffVtable = 0x00;
    static constexpr std::size_t kOffData = 0x70;
    static constexpr std::size_t kOffField0x80 = 0x80;
    static constexpr std::size_t kOffField0x88 = 0x88;
    static_assert(sizeof(void*) == 8, "sub_56be290: x64 pointers are 8 bytes");
};
static_assert(sizeof(Sub56be290Layout) > 0, "sub_56be290: layout constant block");

// Mirror of the a0 object at the offsets the function accesses (byte-exact, no semantics assumed beyond the accesses).
struct Sub56be290This {
    void* vtable;                        // +0x00 [W]
    std::uint8_t pad0x08[0x70 - 0x08];   // +0x08..0x6f
    void* data;                          // +0x70 [R/W]
    std::uint8_t pad0x78[0x80 - 0x78];   // +0x78..0x7f
    std::uint64_t field0x80;             // +0x80 [W]
    std::uint64_t field0x88;             // +0x88 [R/W]
};

struct Sub56be290Refcounted {
    void* vfptr;                         // +0x00 [R]
    std::uint32_t pad0x08;               // +0x08
    std::uint32_t field0x0C;             // +0x0C [R/W] lock dec
};

static_assert(offsetof(Sub56be290This, vtable) == Sub56be290Layout::kOffVtable,
              "sub_56be290: vtable at +0x00");
static_assert(offsetof(Sub56be290This, data) == Sub56be290Layout::kOffData,
              "sub_56be290: data at +0x70");
static_assert(offsetof(Sub56be290This, field0x80) == Sub56be290Layout::kOffField0x80,
              "sub_56be290: field0x80 at +0x80");
static_assert(offsetof(Sub56be290This, field0x88) == Sub56be290Layout::kOffField0x88,
              "sub_56be290: field0x88 at +0x88");
static_assert(sizeof(Sub56be290This) == 0x90, "sub_56be290: this mirror size");
static_assert(offsetof(Sub56be290Refcounted, field0x0C) == 0x0C,
              "sub_56be290: refcounted field0x0C at +0x0C");
static_assert(sizeof(Sub56be290Refcounted) == 0x10, "sub_56be290: refcounted mirror size");

// Data-slot RVAs (call qword ptr [slot]; pointer read at call time, brief rule 69).
static constexpr std::uintptr_t kRvaReleaseSlot = 0xF99FFA0;  // sub_eea6040, boundary/vendor thunk
static constexpr std::uintptr_t kRvaFailSlot = 0xF9A8C78;     // fail handler (noreturn path, then int3)

namespace native {

// sub_e935700 (0xe935700, size 0x5): lift-set callee, tail jump to sub_392960.
// Single argument in RCX, result in RAX. Called directly, never through a boundary wrapper.
void* sub_e935700(void* a0);

// Lifted body of sub_56be290 (0x56be290, size 0xc6, 1.26.62.01).
void sub_56be290(void* a0);

} // namespace native
