#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_c280a80, reverse-engineered from the disassembly
// of [0xc280a80, 0xc280b8f), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280a80_rcx {
    void* f0[2];   // // +0x00: void*[2] R/W // begin, end  (R/W cited: 0xc280a9a:R, 0xc280b01:R, 0xc280b37:W, 0xc280b45:W)
    void* f10;     // // +0x10: void* R/W // capacity  (R/W cited: 0xc280b04:R, 0xc280b3a:W, 0xc280b54:W)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280a80_rdx {
    void* f0[2];   // // +0x00: void*[2] R/W // begin, end  (R/W cited: 0xc280b42:R, 0xc280b5b:W)
    void* f10;     // // +0x10: void* R/W // capacity  (R/W cited: 0xc280b50:R, 0xc280b5e:W)
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280a80_r14 {
    void* f0;           // // +0x00: void* R // vtable pointer  (R/W cited: 0xc280ad9:R, 0xc280aef:R)
    std::uint32_t f8;   // // +0x08: std::uint32_t RW // strong refcount  (R/W cited: 0xc280ad2:RW)
    std::uint32_t fc;   // // +0x0c: std::uint32_t RW // weak refcount  (R/W cited: 0xc280ae8:RW)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280a80_rax {
    void* f0;           // // +0x00: void* R // vtable[0] = destructor  (R/W cited: 0xc280adc:R)
    void* f8;           // // +0x08: void* R // vtable[1] = delete  (R/W cited: 0xc280af2:R)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280a80_rbx {
    std::uint8_t pad0x00[0x10];   // +0x00..+0x0f padding (no observed access)
    void* f10;                    // // +0x10: void* R // element's owned pointer  (R/W cited: 0xc280ac9:R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_c280a80_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;            // // +0x20: std::uint64_t W  (R/W cited: 0xc280b75:W)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_c280a80_rcx, f0) == 0x0, "sub_0xc280a80 rcx+0x0 field");
static_assert(offsetof(sub_c280a80_rcx, f10) == 0x10, "sub_0xc280a80 rcx+0x10 field");
static_assert(sizeof(sub_c280a80_rcx) >= 0x18, "sub_0xc280a80 rcx sizeof lower bound");

static_assert(offsetof(sub_c280a80_rdx, f0) == 0x0, "sub_0xc280a80 rdx+0x0 field");
static_assert(offsetof(sub_c280a80_rdx, f10) == 0x10, "sub_0xc280a80 rdx+0x10 field");
static_assert(sizeof(sub_c280a80_rdx) >= 0x18, "sub_0xc280a80 rdx sizeof lower bound");

static_assert(offsetof(sub_c280a80_r14, f0) == 0x0, "sub_0xc280a80 r14+0x0 field");
static_assert(offsetof(sub_c280a80_r14, f8) == 0x8, "sub_0xc280a80 r14+0x8 field");
static_assert(offsetof(sub_c280a80_r14, fc) == 0xc, "sub_0xc280a80 r14+0xc field");
static_assert(sizeof(sub_c280a80_r14) >= 0x10, "sub_0xc280a80 r14 sizeof lower bound");

static_assert(offsetof(sub_c280a80_rax, f0) == 0x0, "sub_0xc280a80 rax+0x0 field");
static_assert(offsetof(sub_c280a80_rax, f8) == 0x8, "sub_0xc280a80 rax+0x8 field");
static_assert(sizeof(sub_c280a80_rax) >= 0x10, "sub_0xc280a80 rax sizeof lower bound");

static_assert(offsetof(sub_c280a80_rbx, f10) == 0x10, "sub_0xc280a80 rbx+0x10 field");
static_assert(sizeof(sub_c280a80_rbx) >= 0x18, "sub_0xc280a80 rbx sizeof lower bound");

static_assert(offsetof(sub_c280a80_rsp, f20) == 0x20, "sub_0xc280a80 rsp+0x20 field");
static_assert(sizeof(sub_c280a80_rsp) >= 0x28, "sub_0xc280a80 rsp sizeof lower bound");

// Forward declarations for callees
extern "C" void sub_e935700(void* ptr, std::uintptr_t size);  // 0xE935700 - deallocate
// 0xF99FFA0 = thunk to sub_eea6040 (vtable call dispatcher)
// 0xF9A8C78 = error handler (terminate)

// Signature (x64 Microsoft ABI) - matches the prologue: push r15/r14/rsi/rdi/rbx, sub rsp,0x30
// rcx = this (destination vector), rdx = source vector
// Returns this (rax = rcx)
sub_c280a80_rcx* sub_c280a80(sub_c280a80_rcx* dest, sub_c280a80_rdx* src);

} // namespace native::helpers