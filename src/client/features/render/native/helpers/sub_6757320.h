#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_6757320, reverse-engineered from the disassembly
// of [0x6757320, 0x675744e). Offsets and widths come from the instruction operands;
// field names/meanings are [open]. One packed struct per base register that is
// dereferenced; sizeof is a lower bound, not an exact object size.

#pragma pack(push, 1)
// Struct for base register rcx (dereferenced in this function) [proven base, [open] name/meaning]
struct sub_6757320_rcx {
    void* f0;                   // +0x00: R (container begin iterator)
    std::uint64_t f8;           // +0x08: R (container end iterator)
    std::uint8_t pad0x10[0x8];  // +0x10..+0x17 padding (no observed access)
    std::uint64_t f18[2];       // +0x18: R/W (16 bytes, lea + store)
    std::uint64_t f28;          // +0x28: W
};
#pragma pack(pop)

#pragma pack(push, 1)
// Struct for base register r15 (dereferenced in this function) [proven base, [open] name/meaning]
struct sub_6757320_r15 {
    std::uint8_t pad0x00[0x10]; // +0x00..+0x0f padding (no observed access)
    std::uint8_t f10;           // +0x10: W
    std::uint8_t pad0x11[0x7];  // +0x11..+0x17 padding (no observed access)
    void* f18;                  // +0x18: R (managed-object field -> rax object)
};
#pragma pack(pop)

#pragma pack(push, 1)
// Struct for base register rax (dereferenced in this function) [proven base, [open] name/meaning]
struct sub_6757320_rax {
    void* f0;                   // +0x00: R/W/W (invalidation write 0xFFFF)
    std::uint64_t f8;           // +0x08: W (0)
    std::uint64_t f10[2];       // +0x10: W (movups x2)
    std::uint64_t f20[2];       // +0x20: W (movups x2)
    std::uint64_t f30[2];       // +0x30: W (movups x2)
    std::uint64_t f40[2];       // +0x40: W (movups x2)
    std::uint64_t f50[2];       // +0x50: W (movups x2)
    std::uint32_t f60;          // +0x60: W (0)
    std::uint8_t pad0x64[0x4];  // +0x64..+0x67 padding (no observed access)
    void* f68;                  // +0x68: R/W (sub-object control block)
};
#pragma pack(pop)

#pragma pack(push, 1)
// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
struct sub_6757320_rbx {
    void* f0;   // +0x00: R (managed pointer)
    void* f8;   // +0x08: R (control-block pointer)
};
#pragma pack(pop)

#pragma pack(push, 1)
// Struct for base register rdi (dereferenced in this function) [proven base, [open] name/meaning]
struct sub_6757320_rdi {
    void* f0;             // +0x00: R (vtable pointer)
    std::uint32_t f8;     // +0x08: RW (reference count, lock cmpxchg/dec)
    std::uint32_t fc;     // +0x0c: RW (weak count, lock dec)
};
#pragma pack(pop)

#pragma pack(push, 1)
// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
struct sub_6757320_rsp {
    std::uint8_t pad0x00[0x20]; // +0x00..+0x1f padding (no observed access)
    std::uint8_t f20;           // +0x20: R/W (xmm6 spill slot)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_6757320_rcx, f0) == 0x0, "sub_0x6757320 rcx+0x0 field");
static_assert(offsetof(sub_6757320_rcx, f8) == 0x8, "sub_0x6757320 rcx+0x8 field");
static_assert(offsetof(sub_6757320_rcx, f18) == 0x18, "sub_0x6757320 rcx+0x18 field");
static_assert(offsetof(sub_6757320_rcx, f28) == 0x28, "sub_0x6757320 rcx+0x28 field");
static_assert(sizeof(sub_6757320_rcx) >= 0x30, "sub_0x6757320 rcx sizeof lower bound");

static_assert(offsetof(sub_6757320_r15, f10) == 0x10, "sub_0x6757320 r15+0x10 field");
static_assert(offsetof(sub_6757320_r15, f18) == 0x18, "sub_0x6757320 r15+0x18 field");
static_assert(sizeof(sub_6757320_r15) >= 0x20, "sub_0x6757320 r15 sizeof lower bound");

static_assert(offsetof(sub_6757320_rax, f0) == 0x0, "sub_0x6757320 rax+0x0 field");
static_assert(offsetof(sub_6757320_rax, f8) == 0x8, "sub_0x6757320 rax+0x8 field");
static_assert(offsetof(sub_6757320_rax, f10) == 0x10, "sub_0x6757320 rax+0x10 field");
static_assert(offsetof(sub_6757320_rax, f20) == 0x20, "sub_0x6757320 rax+0x20 field");
static_assert(offsetof(sub_6757320_rax, f30) == 0x30, "sub_0x6757320 rax+0x30 field");
static_assert(offsetof(sub_6757320_rax, f40) == 0x40, "sub_0x6757320 rax+0x40 field");
static_assert(offsetof(sub_6757320_rax, f50) == 0x50, "sub_0x6757320 rax+0x50 field");
static_assert(offsetof(sub_6757320_rax, f60) == 0x60, "sub_0x6757320 rax+0x60 field");
static_assert(offsetof(sub_6757320_rax, f68) == 0x68, "sub_0x6757320 rax+0x68 field");
static_assert(sizeof(sub_6757320_rax) >= 0x70, "sub_0x6757320 rax sizeof lower bound");

static_assert(offsetof(sub_6757320_rbx, f0) == 0x0, "sub_0x6757320 rbx+0x0 field");
static_assert(offsetof(sub_6757320_rbx, f8) == 0x8, "sub_0x6757320 rbx+0x8 field");
static_assert(sizeof(sub_6757320_rbx) >= 0x10, "sub_0x6757320 rbx sizeof lower bound");

static_assert(offsetof(sub_6757320_rdi, f0) == 0x0, "sub_0x6757320 rdi+0x0 field");
static_assert(offsetof(sub_6757320_rdi, f8) == 0x8, "sub_0x6757320 rdi+0x8 field");
static_assert(offsetof(sub_6757320_rdi, fc) == 0xc, "sub_0x6757320 rdi+0xc field");
static_assert(sizeof(sub_6757320_rdi) >= 0x10, "sub_0x6757320 rdi sizeof lower bound");

static_assert(offsetof(sub_6757320_rsp, f20) == 0x20, "sub_0x6757320 rsp+0x20 field");
static_assert(sizeof(sub_6757320_rsp) >= 0x21, "sub_0x6757320 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI). The prologue saves r15/r14/rsi/rdi/rbx and takes the
// container pointer in rcx; no return value is established by the listing.
void sub_6757320(void* self);

} // namespace native::helpers
