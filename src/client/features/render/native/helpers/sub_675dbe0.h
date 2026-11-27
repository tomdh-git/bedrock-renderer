#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_675dbe0, reverse-engineered from the disassembly
// of [0x675dbe0, 0x675dcbf), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// The structs are packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// Accessed field: f19 (byte flag tested at entry; non-zero takes the epilogue).
#pragma pack(push, 1)
struct sub_675dbe0_rcx {
    std::uint8_t pad0x00[0x19];   // +0x00..+0x18 padding (no observed access)
    std::uint8_t f19;             // +0x19: std::uint8_t R  (R/W cited: 0x675dbed:R)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// r14 = self->f0; holds the object whose f19 flag is re-checked after each round.
#pragma pack(push, 1)
struct sub_675dbe0_r14 {
    void* f0;                     // +0x00: void* R  (R/W cited: 0x675dc4e:R)
    std::uint8_t pad0x08[0x8];    // +0x08..+0x0f padding (no observed access)
    std::uint64_t f10;            // +0x10: std::uint64_t R  (R/W cited: 0x675dc45:R)
    std::uint8_t pad0x18[0x1];    // +0x18..+0x18 padding (no observed access)
    std::uint8_t f19;             // +0x19: std::uint8_t R  (R/W cited: 0x675dc3b:R)
    std::uint8_t pad0x1a[0xe];    // +0x1a..+0x27 padding (no observed access)
    void* f28;                    // +0x28: void* R  (R/W cited: 0x675dc51:R)
};
#pragma pack(pop)

// Struct for base register r15 (dereferenced in this function) [proven base, [open] name/meaning]
// r15 is the element-range cursor ([r15+8] is the element pointer).
#pragma pack(push, 1)
struct sub_675dbe0_r15 {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;                    // +0x08: void* R // element pointer  (R/W cited: 0x675dc89:R)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// rax holds vtable pointers read through an element; f8 is vtable slot 1.
#pragma pack(push, 1)
struct sub_675dbe0_rax {
    void* f0;                    // +0x00: void* R // vtable pointer  (R/W cited: 0x675dc98:R, 0x675dcad:R)
    std::uint64_t f8;            // +0x08: std::uint64_t R  (R/W cited: 0x675dcb0:R)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// rbx is an element: f0 vtable pointer, f8 strong refcount, f0c weak refcount.
#pragma pack(push, 1)
struct sub_675dbe0_rbx {
    void* f0;                    // +0x00: void* R // vtable pointer  (R/W cited: 0x675dc98:R, 0x675dcad:R)
    std::uint32_t f8;            // +0x08: std::uint32_t RW  (R/W cited: 0x675dc92:RW)
    std::uint32_t fc;            // +0x0c: std::uint32_t RW  (R/W cited: 0x675dca7:RW)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
// rdi is an object with pointer fields f8, f10, f20, f28; f10/f28 are 8 bytes wide
// (cmp rax,[rdi+0x10] / mov [rdi+0x10],rax and mov [rdi+0x28],rax prove 8-byte access).
#pragma pack(push, 1)
struct sub_675dbe0_rdi {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;                    // +0x08: void* R  (R/W cited: 0x675dc18:R, 0x675dc5a:R)
    void* f10;                   // +0x10: void* RW   (R/W cited: 0x675dc5e:R, 0x675dc64:W)
    std::uint8_t pad0x18[0x8];   // +0x18..+0x1f padding (no observed access)
    void* f20;                   // +0x20: void* R  (R/W cited: 0x675dc10:R, 0x675dc68:R)
    void* f28;                   // +0x28: void* R/W  (R/W cited: 0x675dc14:W, 0x675dc6c:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_675dbe0_rcx, f19) == 0x19, "sub_0x675dbe0 rcx+0x19 field");
static_assert(sizeof(sub_675dbe0_rcx) >= 0x1a, "sub_0x675dbe0 rcx sizeof lower bound");

static_assert(offsetof(sub_675dbe0_r14, f0) == 0x0, "sub_0x675dbe0 r14+0x0 field");
static_assert(offsetof(sub_675dbe0_r14, f10) == 0x10, "sub_0x675dbe0 r14+0x10 field");
static_assert(offsetof(sub_675dbe0_r14, f19) == 0x19, "sub_0x675dbe0 r14+0x19 field");
static_assert(offsetof(sub_675dbe0_r14, f28) == 0x28, "sub_0x675dbe0 r14+0x28 field");
static_assert(sizeof(sub_675dbe0_r14) >= 0x30, "sub_0x675dbe0 r14 sizeof lower bound");

static_assert(offsetof(sub_675dbe0_r15, f8) == 0x8, "sub_0x675dbe0 r15+0x8 field");
static_assert(sizeof(sub_675dbe0_r15) >= 0x10, "sub_0x675dbe0 r15 sizeof lower bound");

static_assert(offsetof(sub_675dbe0_rax, f0) == 0x0, "sub_0x675dbe0 rax+0x0 field");
static_assert(offsetof(sub_675dbe0_rax, f8) == 0x8, "sub_0x675dbe0 rax+0x8 field");
static_assert(sizeof(sub_675dbe0_rax) >= 0x10, "sub_0x675dbe0 rax sizeof lower bound");

static_assert(offsetof(sub_675dbe0_rbx, f0) == 0x0, "sub_0x675dbe0 rbx+0x0 field");
static_assert(offsetof(sub_675dbe0_rbx, f8) == 0x8, "sub_0x675dbe0 rbx+0x8 field");
static_assert(offsetof(sub_675dbe0_rbx, fc) == 0xc, "sub_0x675dbe0 rbx+0xc field");
static_assert(sizeof(sub_675dbe0_rbx) >= 0x10, "sub_0x675dbe0 rbx sizeof lower bound");

static_assert(offsetof(sub_675dbe0_rdi, f8) == 0x8, "sub_0x675dbe0 rdi+0x8 field");
static_assert(offsetof(sub_675dbe0_rdi, f10) == 0x10, "sub_0x675dbe0 rdi+0x10 field");
static_assert(offsetof(sub_675dbe0_rdi, f20) == 0x20, "sub_0x675dbe0 rdi+0x20 field");
static_assert(offsetof(sub_675dbe0_rdi, f28) == 0x28, "sub_0x675dbe0 rdi+0x28 field");
static_assert(sizeof(sub_675dbe0_rdi) >= 0x30, "sub_0x675dbe0 rdi sizeof lower bound");

// Signature (x64 Microsoft ABI). Argument rcx = self. The original epilogue leaves RAX
// undefined and every caller ignores the result, so the lift returns 0 at the epilogue.
uintptr_t sub_675dbe0(void* self);

} // namespace native::helpers
