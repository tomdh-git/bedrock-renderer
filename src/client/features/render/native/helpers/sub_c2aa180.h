#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_e3295f0 (0xe3295f0): callee outside the lift set and outside native_boundary.tsv
// (UNRESOLVED CALL). Declared as a plain extern so the lifted body can call it directly.
// x64 Microsoft ABI: RCX = a0+0x8, RDX = pointer to 16-byte buffer; returns bool in AL.
bool sub_e3295f0(void* a0, void* buf);
bool sub_e32a220(void* a0, void* buf);

// sub_e935700 (0xe935700): lift-set callee, forward-declared here rather than including
// sub_e935700.h (that unit's header has a static_assert on its own incomplete layout type
// that the syntax checker rejects). Signature matches sub_e935700.h: void* sub_e935700(void* a0).
void* sub_e935700(void* a0);

// sub_eea6040 (vendor boundary via data slot 0xF99FFA0; docs/data/native_boundary.tsv).
// The thunk at 0xeea6040 is a one-byte `jmp rax`; g_eea6040_thunk(RCX = object, RDX = target funcptr)
// moves RDX into RAX and jumps through the data slot, so the net effect is target(object).
namespace boundary {
using eea6040_fn = void(*)(void* rcx, void* rdx);
extern eea6040_fn g_eea6040_thunk;   // resolved from Sigs.json at install
} // namespace boundary

} // namespace native

namespace native::helpers {

// Layout of the object passed to sub_c2aa180 in rcx (this), reverse-engineered from the
// disassembly of [0xc2aa180, 0xc2aa26c), Minecraft Windows 1.26.62.01.
// Every offset below is cited by an instruction in the function.
struct RefcountedObj {
    void* vfptr;                         // +0x00 [R] vtable pointer
    std::uint32_t refcount1;             // +0x08 [R/W] lock dec dword ptr [object + 8]
    std::uint32_t refcount2;             // +0x0C [R/W] lock dec dword ptr [object + 0xC]
};

struct sub_c2aa180_state {
    std::uint8_t pad0x00[0x08];          // +0x00..0x07
    void* field0x8;                      // +0x08 [R] - passed as RCX to sub_e3295f0/sub_e32a220
    std::uint8_t pad0x10[8];             // +0x10..0x17
    std::uint8_t field0x18[16];          // +0x18 [R] 16-byte field; byte at +0x20 is field0x18[8]
    std::uint8_t pad0x28[8];             // +0x28..0x2F
    void* buffer_start;                  // +0x30 [R/W] buffer base
    std::uint8_t pad0x38[0x40 - 0x38];   // +0x38..0x3F
    void* buffer_end;                    // +0x40 [R/W] buffer end
    std::uint8_t pad0x48[0x50 - 0x48];   // +0x48..0x4F
    void* refcounted;                    // +0x50 [R] refcounted object
};

// Data-slot RVAs (call qword ptr [slot]; pointer read at call time).
struct sub_c2aa180Layout {
    static constexpr std::uintptr_t kFailfastSlotRva = 0xF9A8C78; // call qword ptr [0xF9A8C78]
    static_assert(kFailfastSlotRva == 0xF9A8C78, "sub_c2aa180: failfast data slot RVA 0xF9A8C78");
};

// Static layout assertions (every struct offset read or written by the function).
static_assert(offsetof(sub_c2aa180_state, field0x8) == 0x08, "sub_c2aa180: field0x8 at +0x08");
static_assert(offsetof(sub_c2aa180_state, field0x18) == 0x18, "sub_c2aa180: field0x18 at +0x18");
static_assert(offsetof(sub_c2aa180_state, buffer_start) == 0x30, "sub_c2aa180: buffer_start at +0x30");
static_assert(offsetof(sub_c2aa180_state, buffer_end) == 0x40, "sub_c2aa180: buffer_end at +0x40");
static_assert(offsetof(sub_c2aa180_state, refcounted) == 0x50, "sub_c2aa180: refcounted at +0x50");
static_assert(sizeof(sub_c2aa180_state) == 0x58, "sub_c2aa180: this mirror size");

static_assert(offsetof(RefcountedObj, vfptr) == 0x00, "sub_c2aa180: vfptr at +0x00");
static_assert(offsetof(RefcountedObj, refcount1) == 0x08, "sub_c2aa180: refcount1 at +0x08");
static_assert(offsetof(RefcountedObj, refcount2) == 0x0C, "sub_c2aa180: refcount2 at +0x0C");
static_assert(sizeof(RefcountedObj) == 0x10, "sub_c2aa180: RefcountedObj mirror size");

// Signature (x64 Microsoft ABI): argument (this) in RCX, return value in RAX.
uintptr_t sub_c2aa180(sub_c2aa180_state* self);

} // namespace native::helpers
