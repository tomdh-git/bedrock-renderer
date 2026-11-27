#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_e935700 (0xe935700, lift set): tail-jump thunk to sub_392960.
// ABI recovered from its disassembly: the single argument arrives in RCX and the
// result leaves in RAX; no other input register and no stack argument is read.
void* sub_e935700(void* a0);

} // namespace native

namespace native::helpers {

// Typed state layout(s) for sub_56b8180, reverse-engineered from the disassembly
// of [0x56b8180, 0x56b827c), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.

// Struct for base register rcx (the 'self' argument, dereferenced in this function)
// +0x00: entries begin pointer (R at 0x56b818e/0x56b8212, W at 0x56b8248 as part of 16-byte clear)
// +0x08: entries end   pointer (R at 0x56b819d; loop step limit rbx)
// +0x10: outer end  pointer (R at 0x56b8215, W at 0x56b824b)
#pragma pack(push, 1)
struct sub_56b8180_rcx {
    void* slot[2];        // +0x00: void*[2] R/W  slot[0]=entries begin, slot[1]=entries end
    std::uint64_t outerEnd;   // +0x10: std::uint64_t R/W  outer end pointer
};
#pragma pack(pop)

// Struct for base register r14 (points into an entry at entry+0xe8)
// +0x00: buffer #2 begin pointer (R at 0x56b81dd, W at 0x56b81b5 as part of 16-byte clear)
// +0x10: buffer #2 end   pointer (R at 0x56b81e5 via rdi+0xf8 == r14+0x10, W at 0x56b81b9)
#pragma pack(push, 1)
struct sub_56b8180_r14 {
    void* slot2[2];       // +0x00: void*[2] R/W  slot2[0]=buffer #2 begin
    std::uint64_t buf2End;// +0x10: std::uint64_t R/W  buffer #2 end
};
#pragma pack(pop)

// Struct for base register rdi (a walked entry, stride 0x118)
// +0xe8:  address base for r14 (= rdi+0xE8), used in lea at 0x56b81d6 (no direct deref)
// +0xf8:  buffer #2 end   pointer (R at 0x56b81e5)
// +0x100: flag byte compared to 1 (R at 0x56b81cd)
#pragma pack(push, 1)
struct sub_56b8180_rdi {
    std::uint8_t pad0x00[0xe8];   // +0x00..+0xe7 padding (no observed access)
    std::uint8_t f_e8;            // +0xe8: std::uint8_t R  (lea r14,[rdi+0xE8] at 0x56b81d6)
    std::uint8_t pad0xe9[0xf];    // +0xe9..+0xf7 padding (no observed access)
    std::uint64_t f_f8;           // +0xf8: std::uint64_t R  (R cited: 0x56b81e5)
    std::uint8_t f_100;           // +0x100: std::uint8_t R  (R cited: 0x56b81cd)
};
#pragma pack(pop)

// Struct for base register rsp (spill slots)
// +0x20: scratch slot (W at 0x56b8262, dead store on the fail path)
// +0x30: xmm6 spill slot (16 bytes, W at 0x56b8189, R at 0x56b8253)
#pragma pack(push, 1)
struct sub_56b8180_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t failDead;       // +0x20: std::uint64_t W  (R/W cited: 0x56b8262:W)
    std::uint8_t pad0x28[0x8];    // +0x28..+0x2f padding (no observed access)
    std::uint8_t xmm6Slot[16];    // +0x30: 16-byte xmm6 slot R/W (R/W cited: 0x56b8189:W, 0x56b8253:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_56b8180_rcx, slot) == 0x0, "sub_0x56b8180 rcx+0x0 field");
static_assert(offsetof(sub_56b8180_rcx, outerEnd) == 0x10, "sub_0x56b8180 rcx+0x10 field");
static_assert(sizeof(sub_56b8180_rcx) >= 0x18, "sub_0x56b8180 rcx sizeof lower bound");

static_assert(offsetof(sub_56b8180_r14, slot2) == 0x0, "sub_0x56b8180 r14+0x0 field");
static_assert(offsetof(sub_56b8180_r14, buf2End) == 0x10, "sub_0x56b8180 r14+0x10 field");
static_assert(sizeof(sub_56b8180_r14) >= 0x18, "sub_0x56b8180 r14 sizeof lower bound");

static_assert(offsetof(sub_56b8180_rdi, f_e8) == 0xe8, "sub_0x56b8180 rdi+0xe8 field");
static_assert(offsetof(sub_56b8180_rdi, f_f8) == 0xf8, "sub_0x56b8180 rdi+0xf8 field");
static_assert(offsetof(sub_56b8180_rdi, f_100) == 0x100, "sub_0x56b8180 rdi+0x100 field");
static_assert(sizeof(sub_56b8180_rdi) >= 0x101, "sub_0x56b8180 rdi sizeof lower bound");

static_assert(offsetof(sub_56b8180_rsp, failDead) == 0x20, "sub_0x56b8180 rsp+0x20 field");
static_assert(offsetof(sub_56b8180_rsp, xmm6Slot) == 0x30, "sub_0x56b8180 rsp+0x30 field");
static_assert(sizeof(sub_56b8180_rsp) >= 0x40, "sub_0x56b8180 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI). rcx = self (a0): { entries begin@+0x0, entries end@+0x8,
// outer end@+0x10 }. Walks the entries [begin, end) with stride 0x118, releasing each
// entry whose flag byte at +0x100 equals 1 via sub_e935700 (argument in rcx, result in
// rax), then releases the outer range [begin, outer end) the same way and zeroes it.
// Returns the value sub_e935700 leaves in rax on the last release path; on the null-a0
// path RAX is not written by this function, so the return is entry-RAX (lift returns 0).
uintptr_t sub_56b8180(void* self);   // rcx=self, return=rax (uintptr_t)

} // namespace native::helpers
