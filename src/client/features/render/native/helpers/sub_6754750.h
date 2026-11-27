#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_6754750, reverse-engineered from the disassembly
// of [0x6754750, 0x675487f), Minecraft Windows 1.26.62.01. Offsets and widths come
// straight from the instruction operands ([proven] from the listing); field NAMES
// and MEANINGS are reverse-engineered ([open]). One struct per dereferenced base
// register; every field that is read or written is declared here with an
// offsetof static_assert. The structs are packed (#pragma pack(1)) so each declared
// field sits exactly at its observed offset; sizeof is a lower bound, not an exact
// size, because the real object may have compiler-inserted alignment padding.

// Struct for base register rcx (the `this`/state pointer, copied to rsi at 0x6754757).
//   f8  +0x08: void*    array of element pointers (R/W)
//   f10 +0x10: u64      array capacity (R; zeroed together with f8 by the 16-byte store at 0x675485a)
//   f18 +0x18: u64      cursor / live index (R/W)
//   f20 +0x20: u64      element count (R/W)
#pragma pack(push, 1)
struct sub_6754750_state {
    std::uint8_t pad0x00[0x8];
    void* f8;            // +0x08: void*   array base (R/W)
    std::uintptr_t f10;  // +0x10: u64     capacity (R)
    std::uintptr_t f18;  // +0x18: u64     cursor / live index (R/W)
    std::uintptr_t f20;  // +0x20: u64     element count (R/W)
};
#pragma pack(pop)

// Struct for base register rax when it holds an array element pointer; only +0x10 is read.
#pragma pack(push, 1)
struct sub_6754750_elem {
    std::uint8_t pad0x00[0x10];
    void* f10;           // +0x10: void*   pointer to the refcounted object (R)
};
#pragma pack(pop)

// Struct for base register rdi when it holds the refcounted object.
//   f0  +0x00: void*  vptr (R)
//   f8  +0x08: u32    strong reference count (lock dec, RW)
//   fc  +0x0c: u32    weak reference count (lock dec, RW)
#pragma pack(push, 1)
struct sub_6754750_obj {
    void* f0;            // +0x00: void*   vptr (R)
    std::uint32_t f8;    // +0x08: u32     strong refcount (lock dec, RW)
    std::uint32_t fc;    // +0x0c: u32     weak refcount (lock dec, RW)
};
#pragma pack(pop)

static_assert(offsetof(sub_6754750_state, f8) == 0x8, "sub_6754750 state f8 at +0x08");
static_assert(offsetof(sub_6754750_state, f10) == 0x10, "sub_6754750 state f10 at +0x10");
static_assert(offsetof(sub_6754750_state, f18) == 0x18, "sub_6754750 state f18 at +0x18");
static_assert(offsetof(sub_6754750_state, f20) == 0x20, "sub_6754750 state f20 at +0x20");
static_assert(sizeof(sub_6754750_state) >= 0x28, "sub_6754750 state sizeof lower bound");

static_assert(offsetof(sub_6754750_elem, f10) == 0x10, "sub_6754750 elem f10 at +0x10");
static_assert(sizeof(sub_6754750_elem) >= 0x18, "sub_6754750 elem sizeof lower bound");

static_assert(offsetof(sub_6754750_obj, f0) == 0x0, "sub_6754750 obj f0 at +0x00");
static_assert(offsetof(sub_6754750_obj, f8) == 0x8, "sub_6754750 obj f8 at +0x08");
static_assert(offsetof(sub_6754750_obj, fc) == 0xc, "sub_6754750 obj fc at +0x0c");
static_assert(sizeof(sub_6754750_obj) >= 0x10, "sub_6754750 obj sizeof lower bound");

// Callee lifted by its own unit, declared in sub_e935700.h as `namespace native {
// void* sub_e935700(void* a0); }` and called from this unit as native::sub_e935700.
// Exact ABI from its disassembly: the single input argument arrives in RCX and the
// result leaves in RAX. Call sites set RDX (0x18 or a size) but sub_392960/sub_e935700
// never read RDX, so a one-argument call is behaviorally identical to the calling
// convention seen in the listing.

// Signature (x64 Microsoft ABI): rcx = state pointer; return value in RAX.
// Prologue: 0x6754750 push rsi; 0x6754751 push rdi; 0x6754752 push rbx; 0x6754753 sub rsp,0x30
uintptr_t sub_6754750(void* self);

} // namespace native::helpers
