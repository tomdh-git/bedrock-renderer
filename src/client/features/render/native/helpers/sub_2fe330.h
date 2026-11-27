#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_2fe330, reverse-engineered from the disassembly
// of [0x2fe330, 0x2fe43b), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.

// Callee reached from this function (only direct call, at 0x2fe361). Signature is
// [open]: the call passes rcx = pointer to a 16-byte stack buffer, edx = 0, and the
// return value (rax) is stored as a pointer at a0+0x0.
void* sub_39a7ad0(void* p, std::uint32_t flags);

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
// Field types are fixed by the actual access width in the listing (e.g. mov [rsi],rax is 8 bytes).
#pragma pack(push, 1)
struct sub_2fe330_rcx {
    void* f0;       // +0x00: void* W 8B  (R/W cited: 0x2fe36d:W mov [rsi],rax)
    std::uint8_t f8;   // +0x08: std::uint8_t W 1B  (R/W cited: 0x2fe370:W mov [rsi+8],bl)
    std::uint8_t pad0x09[0x7];   // +0x09..+0x0f padding (no observed access)
    void* f10;   // +0x10: void* W 8B  (R/W cited: 0x2fe373:W mov [rsi+0x10],rcx)
    void* f18;   // +0x18: void* W 8B  (R/W cited: 0x2fe377:W mov [rsi+0x18],rcx)
    std::uint64_t f20;   // +0x20: std::uint64_t W 8B  (R/W cited: 0x2fe37b:W mov [rsi+0x20],rdx)
    std::uint8_t f28;   // +0x28: std::uint8_t W 1B  (R/W cited: 0x2fe37f:W mov byte [rsi+0x28],1)
    std::uint8_t pad0x29[0x7];   // +0x29..+0x2f padding (no observed access)
    std::uint32_t f30;   // +0x30: std::uint32_t W 4B  (R/W cited: 0x2fe383:W mov [rsi+0x30],ebp)
    std::uint8_t pad0x34[0x4];   // +0x34..+0x37 padding (no observed access)
    std::uint64_t f38[2];   // +0x38: std::uint64_t[2] W 16B  (R/W cited: 0x2fe38f:W movups [rsi+0x38],xmm0)
    std::uint64_t f48[2];   // +0x48: std::uint64_t[2] W 16B  (R/W cited: 0x2fe393:W movups [rsi+0x48],xmm1)
    std::uint32_t f58;   // +0x58: std::uint32_t W 4B  (R/W cited: 0x2fe397:W mov dword [rsi+0x58],0)
    std::uint8_t pad0x5c[0xc];   // +0x5c..+0x67 padding (no observed access)
    std::uint64_t f68[2];   // +0x68: std::uint64_t[2] W 16B  (R/W cited: 0x2fe3a1:W movups [rsi+0x68],xmm0)
    std::uint8_t pad0x78[0x10];   // +0x78..+0x87 padding (no observed access)
    std::uint8_t f88;   // +0x88: std::uint8_t W 1B  (R/W cited: 0x2fe3a5:W mov byte [rsi+0x88],0)
    std::uint8_t pad0x89[0x7];   // +0x89..+0x8f padding (no observed access)
    std::uint32_t f90;   // +0x90: std::uint32_t W 4B  (R/W cited: 0x2fe3ac:W mov dword [rsi+0x90],0)
    std::uint8_t pad0x94[0x4];   // +0x94..+0x97 padding (no observed access)
    std::uint64_t f98[2];   // +0x98: std::uint64_t[2] W 16B  (R/W cited: 0x2fe3c4:W movups [rsi+0x98],xmm0)
    std::uint64_t fa8[2];   // +0xa8: std::uint64_t[2] W 16B  (R/W cited: 0x2fe3bd:W movups [rsi+0xA8],xmm0)
    std::uint64_t fb8[2];   // +0xb8: std::uint64_t[2] W 16B  (R/W cited: 0x2fe3b6:W movups [rsi+0xB8],xmm0)
    std::uint64_t fc8;   // +0xc8: std::uint64_t W 8B  (R/W cited: 0x2fe3cb:W mov qword [rsi+0xC8],0xF)
    std::uint32_t fd0;   // +0xd0: std::uint32_t W 4B  (R/W cited: 0x2fe3d6:W mov dword [rsi+0xD0],0)
    std::uint8_t pad0xd4[0xc];   // +0xd4..+0xdf padding (no observed access)
    void* fe0;   // +0xe0: void* W 8B  (R/W cited: 0x2fe400:W mov [rsi+0xE0],rax "UNSET" ptr)
    std::uint64_t fe8;   // +0xe8: std::uint64_t W 8B  (R/W cited: 0x2fe407:W mov qword [rsi+0xE8],5)
    std::uint8_t ff0;   // +0xf0: std::uint8_t W 1B  (R/W cited: 0x2fe3f2:W mov byte [rsi+0xF0],0)
    std::uint8_t pad0xf1[0x7];   // +0xf1..+0xf7 padding (no observed access)
    std::uint64_t ff8[2];   // +0xf8: std::uint64_t[2] W 16B  (R/W cited: 0x2fe3e0:W movups [rsi+0xF8],xmm0)
    std::uint64_t f108;   // +0x108: std::uint64_t W 8B  (R/W cited: 0x2fe3e7:W mov qword [rsi+0x108],0)
    std::uint32_t f110;   // +0x110: std::uint32_t W 4B  (R/W cited: 0x2fe412:W mov dword [rsi+0x110],0)
    std::uint8_t pad0x114[0x14];   // +0x114..+0x127 padding (no observed access)
    std::uint8_t f128;   // +0x128: std::uint8_t W 1B  (R/W cited: 0x2fe41c:W mov byte [rsi+0x128],0)
    std::uint8_t pad0x129[0x7];   // +0x129..+0x12f padding (no observed access)
    std::uint32_t f130;   // +0x130: std::uint32_t W 4B  (R/W cited: 0x2fe423:W mov dword [rsi+0x130],0)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_2fe330_rdx {
    std::uint64_t f0[2];   // +0x00: std::uint64_t[2] R 16B  (R/W cited: 0x2fe352:R movups xmm0,[rdx])
};
#pragma pack(pop)

// Struct for base register r9 (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_2fe330_r9 {
    void* f0;   // +0x00: void* R 8B  (R/W cited: 0x2fe366:R mov rcx,[rdi]) vtable pointer
    std::uint64_t f8;   // +0x08: std::uint64_t R 8B  (R/W cited: 0x2fe369:R mov rdx,[rdi+8])
};
#pragma pack(pop)

// Struct for base register r14 (dereferenced in this function) [proven base, [open] name/meaning]
#pragma pack(push, 1)
struct sub_2fe330_r14 {
    std::uint64_t f0[2];   // +0x00: std::uint64_t[2] R 16B  (R/W cited: 0x2fe386:R movups xmm0,[r14])
    std::uint64_t f10[2];   // +0x10: std::uint64_t[2] R 16B  (R/W cited: 0x2fe38a:R movups xmm1,[r14+0x10])
};
#pragma pack(pop)

// Stack slots spilled from the 5th/6th x64 ABI args ([rsp+0x80], [rsp+0x88]) and the
// 16-byte local copy of a1->f0 at [rsp+0x20].
#pragma pack(push, 1)
struct sub_2fe330_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (local 16-byte copy lives at +0x20)
    std::uint64_t f20[2];   // +0x20: std::uint64_t[2] W 16B  (R/W cited: 0x2fe355:W movaps [rsp+0x20],xmm0)
    std::uint8_t pad0x30[0x50];   // +0x30..+0x7f padding (no observed access)
    std::uint32_t f80;   // +0x80: std::uint32_t R 4B  (R/W cited: 0x2fe34b:R mov ebp,[rsp+0x80])
    std::uint8_t pad0x84[0x4];   // +0x84..+0x87 padding (no observed access)
    void* f88;   // +0x88: void* R 8B  (R/W cited: 0x2fe343:R mov r14,[rsp+0x88])
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_2fe330_rcx, f0) == 0x0, "sub_0x2fe330 rcx+0x0 field");
static_assert(offsetof(sub_2fe330_rcx, f8) == 0x8, "sub_0x2fe330 rcx+0x8 field");
static_assert(offsetof(sub_2fe330_rcx, f10) == 0x10, "sub_0x2fe330 rcx+0x10 field");
static_assert(offsetof(sub_2fe330_rcx, f18) == 0x18, "sub_0x2fe330 rcx+0x18 field");
static_assert(offsetof(sub_2fe330_rcx, f20) == 0x20, "sub_0x2fe330 rcx+0x20 field");
static_assert(offsetof(sub_2fe330_rcx, f28) == 0x28, "sub_0x2fe330 rcx+0x28 field");
static_assert(offsetof(sub_2fe330_rcx, f30) == 0x30, "sub_0x2fe330 rcx+0x30 field");
static_assert(offsetof(sub_2fe330_rcx, f38) == 0x38, "sub_0x2fe330 rcx+0x38 field");
static_assert(offsetof(sub_2fe330_rcx, f48) == 0x48, "sub_0x2fe330 rcx+0x48 field");
static_assert(offsetof(sub_2fe330_rcx, f58) == 0x58, "sub_0x2fe330 rcx+0x58 field");
static_assert(offsetof(sub_2fe330_rcx, f68) == 0x68, "sub_0x2fe330 rcx+0x68 field");
static_assert(offsetof(sub_2fe330_rcx, f88) == 0x88, "sub_0x2fe330 rcx+0x88 field");
static_assert(offsetof(sub_2fe330_rcx, f90) == 0x90, "sub_0x2fe330 rcx+0x90 field");
static_assert(offsetof(sub_2fe330_rcx, f98) == 0x98, "sub_0x2fe330 rcx+0x98 field");
static_assert(offsetof(sub_2fe330_rcx, fa8) == 0xa8, "sub_0x2fe330 rcx+0xa8 field");
static_assert(offsetof(sub_2fe330_rcx, fb8) == 0xb8, "sub_0x2fe330 rcx+0xb8 field");
static_assert(offsetof(sub_2fe330_rcx, fc8) == 0xc8, "sub_0x2fe330 rcx+0xc8 field");
static_assert(offsetof(sub_2fe330_rcx, fd0) == 0xd0, "sub_0x2fe330 rcx+0xd0 field");
static_assert(offsetof(sub_2fe330_rcx, fe0) == 0xe0, "sub_0x2fe330 rcx+0xe0 field");
static_assert(offsetof(sub_2fe330_rcx, fe8) == 0xe8, "sub_0x2fe330 rcx+0xe8 field");
static_assert(offsetof(sub_2fe330_rcx, ff0) == 0xf0, "sub_0x2fe330 rcx+0xf0 field");
static_assert(offsetof(sub_2fe330_rcx, ff8) == 0xf8, "sub_0x2fe330 rcx+0xf8 field");
static_assert(offsetof(sub_2fe330_rcx, f108) == 0x108, "sub_0x2fe330 rcx+0x108 field");
static_assert(offsetof(sub_2fe330_rcx, f110) == 0x110, "sub_0x2fe330 rcx+0x110 field");
static_assert(offsetof(sub_2fe330_rcx, f128) == 0x128, "sub_0x2fe330 rcx+0x128 field");
static_assert(offsetof(sub_2fe330_rcx, f130) == 0x130, "sub_0x2fe330 rcx+0x130 field");
static_assert(sizeof(sub_2fe330_rcx) >= 0x134, "sub_0x2fe330 rcx sizeof lower bound");

static_assert(offsetof(sub_2fe330_rdx, f0) == 0x0, "sub_0x2fe330 rdx+0x0 field");
static_assert(sizeof(sub_2fe330_rdx) >= 0x10, "sub_0x2fe330 rdx sizeof lower bound");

static_assert(offsetof(sub_2fe330_r9, f0) == 0x0, "sub_0x2fe330 r9+0x0 field");
static_assert(offsetof(sub_2fe330_r9, f8) == 0x8, "sub_0x2fe330 r9+0x8 field");
static_assert(sizeof(sub_2fe330_r9) >= 0x10, "sub_0x2fe330 r9 sizeof lower bound");

static_assert(offsetof(sub_2fe330_r14, f0) == 0x0, "sub_0x2fe330 r14+0x0 field");
static_assert(offsetof(sub_2fe330_r14, f10) == 0x10, "sub_0x2fe330 r14+0x10 field");
static_assert(sizeof(sub_2fe330_r14) >= 0x20, "sub_0x2fe330 r14 sizeof lower bound");

static_assert(offsetof(sub_2fe330_rsp, f20) == 0x20, "sub_0x2fe330 rsp+0x20 field");
static_assert(offsetof(sub_2fe330_rsp, f80) == 0x80, "sub_0x2fe330 rsp+0x80 field");
static_assert(offsetof(sub_2fe330_rsp, f88) == 0x88, "sub_0x2fe330 rsp+0x88 field");
static_assert(sizeof(sub_2fe330_rsp) >= 0x90, "sub_0x2fe330 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI). rcx=a0 dest struct, rdx=a1 src 16B, r8d=a2 (truncated to byte),
// r9=a3 object (vtable ptr at +0, qword at +8), stack [rsp+0x80]=a4 (u32), [rsp+0x88]=a5 (r14 ptr).
// Returns rax = original rcx = a0. The call to sub_39a7ad0 signature is [open] (evidence-based only).
uintptr_t sub_2fe330(sub_2fe330_rcx* a0, const sub_2fe330_rdx* a1, std::uint32_t a2,
                     sub_2fe330_r9* a3, std::uint32_t a4, void* a5);

} // namespace native::helpers
