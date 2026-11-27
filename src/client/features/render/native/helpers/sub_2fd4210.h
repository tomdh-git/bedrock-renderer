#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_2fd4210, reverse-engineered from the disassembly
// of [0x2fd4210, 0x2fd432f), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.

// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
// Read at 0x2fd4313: mov rax,[rcx] (vtable slot 0)
#pragma pack(push, 1)
struct sub_2fd4210_rcx {
    void* f0;   // +0x00: void* R  (vtable, R cited: 0x2fd4313:R)
};
#pragma pack(pop)

// Struct for base register rdx (dereferenced in this function) [proven base, [open] name/meaning]
// a1 parameter: reads at 0x2fd4282 (dword +0x0), 0x2fd4284 (dword +0x8)
#pragma pack(push, 1)
struct sub_2fd4210_rdx {
    std::uint32_t f0;   // +0x00: std::uint32_t R  (R cited: 0x2fd4282:R)
    std::uint8_t pad0x04[0x4];   // +0x04..+0x07 padding (no observed access)
    std::uint32_t f8;   // +0x08: std::uint32_t R  (R cited: 0x2fd4284:R)
};
#pragma pack(pop)

// Struct for base register r8 (dereferenced in this function) [proven base, [open] name/meaning]
// a2 parameter: reads at 0x2fd428f (dword +0x0 via rsi=a2), 0x2fd4292 (dword +0x8 via rsi=a2).
// Block 1 also uses r8 = [a2+0x38] as a vtable object: reads at 0x2fd4251 (qword +0x0).
#pragma pack(push, 1)
struct sub_2fd4210_r8 {
    void* f0;   // +0x00: void* R  (vtable, R cited: 0x2fd4251:R)
    std::uint32_t f8;   // +0x08: std::uint32_t R  (R cited: 0x2fd4292:R via rsi=a2)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
// Reads at 0x2fd4245 ([rax+0x38]), 0x2fd4254 ([[r8]] = vtable[0]), 0x2fd4304 ([rax+0x38]),
// 0x2fd4313 ([rcx] = vtable), 0x2fd4316 ([rax+0x20] = vtable[4])
#pragma pack(push, 1)
struct sub_2fd4210_rax {
    void* f0;   // +0x00: void* R  (vtable, R cited: 0x2fd4254:R)
    std::uint8_t pad0x08[0x18];   // +0x08..+0x1f padding (no observed access)
    std::uint64_t f20;   // +0x20: std::uint64_t R  (R cited: 0x2fd4316:R)
    std::uint8_t pad0x28[0x10];   // +0x28..+0x37 padding (no observed access)
    void* f38;   // +0x38: void* R  (R cited: 0x2fd4245:R, 0x2fd4304:R)
};
#pragma pack(pop)

// Struct for base register rbp (stack frame) [proven base, [open] name/meaning]
// Fields at offsets matching rbp-relative accesses in the listing.
#pragma pack(push, 1)
struct sub_2fd4210_rbp {
    std::int32_t f0;     // +0x00: std::int32_t W  (W cited: 0x2fd42a8:W)
    std::int32_t f4;     // +0x04: std::int32_t W  (W cited: 0x2fd42ac:W)
    std::int32_t f8;     // +0x08: std::int32_t W  (W cited: 0x2fd42b0:W)
    std::int32_t fc;     // +0x0c: std::int32_t W  (W cited: 0x2fd42b7:W)
    std::int32_t f10;    // +0x10: std::int32_t W  (W cited: 0x2fd42c7:W)
    std::int32_t f14;    // +0x14: std::int32_t W  (W cited: 0x2fd42cb:W)
    std::int32_t f18;    // +0x18: std::int32_t W  (W cited: 0x2fd42d2:W)
    std::int32_t f1c;    // +0x1c: std::int32_t W  (W cited: 0x2fd42da:W)
    std::int32_t f20;    // +0x20: std::int32_t W  (W cited: 0x2fd42de:W)
    std::int32_t f24;    // +0x24: std::int32_t W  (W cited: 0x2fd427b:W)
    std::uint64_t f28;   // +0x28: std::uint64_t W  (W cited: 0x2fd4225:W)
    std::uint8_t pad0x30[0x50];   // +0x30..+0x7f padding (no observed access)
    std::uint8_t f80;    // +0x80: std::uint8_t R  (R cited: 0x2fd4273:R)
    std::uint8_t pad0x81[0x7];    // +0x81..+0x87 padding (no observed access)
    void* f88;   // +0x88: void* R  (R cited: 0x2fd4236:R, 0x2fd42fd:R)
    void* f90;   // +0x90: void* R  (R cited: 0x2fd426c:R)
};
#pragma pack(pop)

// Struct for base register rsp (stack slots) [proven base, [open] name/meaning]
// Writes at 0x2fd42e2 ([rsp+0x28] = qword), 0x2fd42eb ([rsp+0x20] = qword).
#pragma pack(push, 1)
struct sub_2fd4210_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    void* f20;   // +0x20: void* W  (W cited: 0x2fd42eb:W)
    void* f28;   // +0x28: void* W  (W cited: 0x2fd42e2:W)
    std::uint8_t pad0x30[0x50];   // +0x30..+0x7f padding (no observed access)
    void* f80;   // +0x80: void* R  (R cited: 0x2fd421d:R - lea rbp,[rsp+0x80] uses rsp+0x80)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_2fd4210_rcx, f0) == 0x0, "sub_0x2fd4210 rcx+0x0 field");
static_assert(sizeof(sub_2fd4210_rcx) >= 0x8, "sub_0x2fd4210 rcx sizeof lower bound");

static_assert(offsetof(sub_2fd4210_rdx, f0) == 0x0, "sub_0x2fd4210 rdx+0x0 field");
static_assert(offsetof(sub_2fd4210_rdx, f8) == 0x8, "sub_0x2fd4210 rdx+0x8 field");
static_assert(sizeof(sub_2fd4210_rdx) >= 0xc, "sub_0x2fd4210 rdx sizeof lower bound");

static_assert(offsetof(sub_2fd4210_r8, f0) == 0x0, "sub_0x2fd4210 r8+0x0 field");
static_assert(offsetof(sub_2fd4210_r8, f8) == 0x8, "sub_0x2fd4210 r8+0x8 field");
static_assert(sizeof(sub_2fd4210_r8) >= 0xc, "sub_0x2fd4210 r8 sizeof lower bound");

static_assert(offsetof(sub_2fd4210_rax, f0) == 0x0, "sub_0x2fd4210 rax+0x0 field");
static_assert(offsetof(sub_2fd4210_rax, f20) == 0x20, "sub_0x2fd4210 rax+0x20 field");
static_assert(offsetof(sub_2fd4210_rax, f38) == 0x38, "sub_0x2fd4210 rax+0x38 field");
static_assert(sizeof(sub_2fd4210_rax) >= 0x40, "sub_0x2fd4210 rax sizeof lower bound");

static_assert(offsetof(sub_2fd4210_rbp, f0) == 0x0, "sub_0x2fd4210 rbp+0x0 field");
static_assert(offsetof(sub_2fd4210_rbp, f4) == 0x4, "sub_0x2fd4210 rbp+0x4 field");
static_assert(offsetof(sub_2fd4210_rbp, f8) == 0x8, "sub_0x2fd4210 rbp+0x8 field");
static_assert(offsetof(sub_2fd4210_rbp, fc) == 0xc, "sub_0x2fd4210 rbp+0xc field");
static_assert(offsetof(sub_2fd4210_rbp, f10) == 0x10, "sub_0x2fd4210 rbp+0x10 field");
static_assert(offsetof(sub_2fd4210_rbp, f14) == 0x14, "sub_0x2fd4210 rbp+0x14 field");
static_assert(offsetof(sub_2fd4210_rbp, f18) == 0x18, "sub_0x2fd4210 rbp+0x18 field");
static_assert(offsetof(sub_2fd4210_rbp, f1c) == 0x1c, "sub_0x2fd4210 rbp+0x1c field");
static_assert(offsetof(sub_2fd4210_rbp, f20) == 0x20, "sub_0x2fd4210 rbp+0x20 field");
static_assert(offsetof(sub_2fd4210_rbp, f24) == 0x24, "sub_0x2fd4210 rbp+0x24 field");
static_assert(offsetof(sub_2fd4210_rbp, f28) == 0x28, "sub_0x2fd4210 rbp+0x28 field");
static_assert(offsetof(sub_2fd4210_rbp, f80) == 0x80, "sub_0x2fd4210 rbp+0x80 field");
static_assert(offsetof(sub_2fd4210_rbp, f88) == 0x88, "sub_0x2fd4210 rbp+0x88 field");
static_assert(offsetof(sub_2fd4210_rbp, f90) == 0x90, "sub_0x2fd4210 rbp+0x90 field");
static_assert(sizeof(sub_2fd4210_rbp) >= 0x98, "sub_0x2fd4210 rbp sizeof lower bound");

static_assert(offsetof(sub_2fd4210_rsp, f20) == 0x20, "sub_0x2fd4210 rsp+0x20 field");
static_assert(offsetof(sub_2fd4210_rsp, f28) == 0x28, "sub_0x2fd4210 rsp+0x28 field");
static_assert(offsetof(sub_2fd4210_rsp, f80) == 0x80, "sub_0x2fd4210 rsp+0x80 field");
static_assert(sizeof(sub_2fd4210_rsp) >= 0x88, "sub_0x2fd4210 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI). rcx=self, rdx=a1, r8=a2, r9d=a3.
// Return: sub_eea6040 result if a2->f38 != 0, otherwise a2.
// Calls sub_eea6040 (boundary via data slot 0xF99FFA0) and sub_2fd3e60 (unresolved).
uintptr_t sub_2fd4210(void* self, sub_2fd4210_rdx* a1, sub_2fd4210_r8* a2, uint32_t a3);

} // namespace native::helpers
