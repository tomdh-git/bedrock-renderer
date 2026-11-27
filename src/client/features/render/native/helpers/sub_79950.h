#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// State layouts for sub_79950 (0x79950, size 0x11a, 1.26.62.01). Offsets,
// widths and signedness come straight from the instruction operands of
// [0x79950, 0x79a6a). Each struct is packed so every field sits at its observed
// offset and offsetof() matches it; the real object may carry compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.

// RCX on entry (a0): output object; also the value returned in RAX (0x79a41).
#pragma pack(push, 1)
struct sub_79950_rcx {
    std::uint64_t f0[2];    // +0x00: 16-byte output slot 0 (W 0x79992)
    std::uint64_t f10[2];   // +0x10: 16-byte output slot 1 (W 0x799a3)
    std::uint64_t f20[2];   // +0x20: 16-byte output slot 2 (W 0x799b5)
    std::uint64_t f30[2];   // +0x30: 16-byte output slot 3 (W 0x799b9)
    std::uint8_t f40;       // +0x40: state byte, cleared to 0 (W 0x79989)
};
#pragma pack(pop)

// RDX on entry (a1): source object. The 16-byte slots are copied out and then
// zeroed. The container at +0x28 (begin) overlaps the +0x20 slot; its end
// (+0x30) and allocation limit (+0x38) overlap the +0x30 slot.
#pragma pack(push, 1)
struct sub_79950_rdx {
    std::uint64_t f0[2];    // +0x00: 16-byte source slot 0 (R 0x79961)
    std::uint64_t f10[2];   // +0x10: 16-byte source slot 1 (R 0x7996e, W 0x7997d)
    std::uint64_t f20[2];   // +0x20: 16-byte source slot 2 (R 0x79972, W 0x79981); +0x28 is the child-list begin pointer (R 0x799c2, lea 0x799cb)
    std::uint64_t f30[2];   // +0x30: 16-byte source slot 3 (R 0x79976, W 0x79985); +0x30 child-list end (R 0x799cf), +0x38 allocation limit (R 0x799f7)
};
#pragma pack(pop)

// RBX = a1 + 0x28: the child-list container inside the source object.
#pragma pack(push, 1)
struct sub_79950_rbx {
    void* f0[2];            // +0x00: begin/end pair (R 0x799f4, W 0x79a2a)
    std::uint64_t f10;      // +0x10: allocation limit (W 0x79a2d)
};
#pragma pack(pop)

// RSP slots used for the temporary release context at rsp+0x40 and for the
// noreturn failure path at rsp+0x20.
#pragma pack(push, 1)
struct sub_79950_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f: no observed access
    std::uint64_t f20;            // +0x20: failure-path home slot, cleared (W 0x79a50)
    std::uint8_t pad0x28[0x8];    // +0x28..+0x2f: no observed access
    std::uint8_t f30;             // +0x30: first byte of the saved source slot 0 (W 0x79964, R 0x7998d)
    std::uint8_t pad0x31[0xf];    // +0x31..+0x3f: no observed access
    std::uint8_t f40;             // +0x40: first byte of the temporary context (R 0x79969, W 0x79995)
    std::uint8_t pad0x41[0xf];    // +0x41..+0x4f: no observed access
    std::uint64_t f50;            // +0x50: temporary context field (W 0x7999a)
    std::uint64_t f58[2];         // +0x58: temporary context field (W 0x799a7)
    std::uint64_t f68;            // +0x68: temporary context field (W 0x799ac)
};
#pragma pack(pop)

static_assert(offsetof(sub_79950_rcx, f0) == 0x0, "sub_0x79950 rcx+0x0 field");
static_assert(offsetof(sub_79950_rcx, f10) == 0x10, "sub_0x79950 rcx+0x10 field");
static_assert(offsetof(sub_79950_rcx, f20) == 0x20, "sub_0x79950 rcx+0x20 field");
static_assert(offsetof(sub_79950_rcx, f30) == 0x30, "sub_0x79950 rcx+0x30 field");
static_assert(offsetof(sub_79950_rcx, f40) == 0x40, "sub_0x79950 rcx+0x40 field");
static_assert(sizeof(sub_79950_rcx) >= 0x41, "sub_0x79950 rcx sizeof lower bound");

static_assert(offsetof(sub_79950_rdx, f0) == 0x0, "sub_0x79950 rdx+0x0 field");
static_assert(offsetof(sub_79950_rdx, f10) == 0x10, "sub_0x79950 rdx+0x10 field");
static_assert(offsetof(sub_79950_rdx, f20) == 0x20, "sub_0x79950 rdx+0x20 field");
static_assert(offsetof(sub_79950_rdx, f20) + 8 == 0x28, "sub_0x79950 rdx+0x28 field");
static_assert(offsetof(sub_79950_rdx, f30) == 0x30, "sub_0x79950 rdx+0x30 field");
static_assert(offsetof(sub_79950_rdx, f30) + 8 == 0x38, "sub_0x79950 rdx+0x38 field");
static_assert(sizeof(sub_79950_rdx) >= 0x40, "sub_0x79950 rdx sizeof lower bound");

static_assert(offsetof(sub_79950_rbx, f0) == 0x0, "sub_0x79950 rbx+0x0 field");
static_assert(offsetof(sub_79950_rbx, f10) == 0x10, "sub_0x79950 rbx+0x10 field");
static_assert(sizeof(sub_79950_rbx) >= 0x18, "sub_0x79950 rbx sizeof lower bound");

static_assert(offsetof(sub_79950_rsp, f20) == 0x20, "sub_0x79950 rsp+0x20 field");
static_assert(offsetof(sub_79950_rsp, f30) == 0x30, "sub_0x79950 rsp+0x30 field");
static_assert(offsetof(sub_79950_rsp, f40) == 0x40, "sub_0x79950 rsp+0x40 field");
static_assert(offsetof(sub_79950_rsp, f50) == 0x50, "sub_0x79950 rsp+0x50 field");
static_assert(offsetof(sub_79950_rsp, f58) == 0x58, "sub_0x79950 rsp+0x58 field");
static_assert(offsetof(sub_79950_rsp, f68) == 0x68, "sub_0x79950 rsp+0x68 field");
static_assert(sizeof(sub_79950_rsp) >= 0x70, "sub_0x79950 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI): RCX = a0 (output object, returned in RAX),
// RDX = a1 (source object, moved-from and then released).
// 0x79950  push r15; 0x7995b  mov rdi,rdx; 0x7995e  mov rsi,rcx
// 0x79a41  mov rax,rsi
uintptr_t sub_79950(void* a0, void* a1);

} // namespace native::helpers
