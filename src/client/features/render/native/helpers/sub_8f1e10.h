#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_8f1e10, reverse-engineered from the disassembly
// of [0x8f1e10, 0x8f1f28), Minecraft Windows 1.26.62.01. Offsets, widths and
// signedness come straight from the instruction operands; the field comments name
// the meaning proven by the instructions that touch each field.
// One struct per base register that is dereferenced (rcx/rdx/rax/rbp/rsp).

// Struct for base register rcx (the `self` argument). The same register also holds the
// callable object at 0x8f1e5a, so f0 describes that object's first word.
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.
#pragma pack(push, 1)
struct sub_8f1e10_rcx {
    void* f0;                     // +0x00: first word (vtable pointer) of the callable reached through f88
                                  //        R at 0x8f1e5a (mov rax,[rcx])
    std::uint8_t pad0x08[0x80];   // +0x08..+0x87 padding (no observed access)
    void* f88;                    // +0x88: callable object; vtable slot 2 at +0x10 and slot 4 at +0x20
                                  //        R at 0x8f1e4a (mov rcx,[rdi+0x88])
    std::uint64_t f90;            // +0x90: 64-bit reference count, released with `lock dec qword ptr`
                                  //        R/W at 0x8f1e9c (lock dec qword ptr [rdi+0x90])
    void* f98;                    // +0x98: head slot of the sub_ae500 list
                                  //        passed as RCX at 0x8f1e3e (add rcx,0x98)
    std::uint8_t pad0xa0[0x260];  // +0xa0..+0x2ff padding (no observed access)
    std::uint8_t f300;            // +0x300: base of the embedded _Mtx object (0x50 bytes)
                                  //        address taken at 0x8f1ea6 (lea rbx,[rdi+0x300])
    std::uint8_t pad0x301[0x4b];  // +0x301..+0x34b padding (no observed access)
    std::uint32_t f34c;           // +0x34c: _Mtx state word
                                  //        R at 0x8f1eb9 (cmp dword ptr [rdi+0x34C],0x7FFFFFFF)
                                  //        W at 0x8f1f13 (mov dword ptr [rdi+0x34C],0x7FFFFFFE)
    std::uint8_t f350;            // +0x350: base of the embedded _Cnd_t object
                                  //        address taken at 0x8f1ec5 (add rdi,0x350)
};
#pragma pack(pop)

// Struct for base register rdx (the `out` argument). Two quadwords written as one
// 16-byte movups store; the caller reads byte 0 as a ready flag.
#pragma pack(push, 1)
struct sub_8f1e10_rdx {
    std::uint64_t f0[2];   // +0x00: 16-byte result
                           //       W at 0x8f1e75 (movups [rsi],xmm0)
                           //       W at 0x8f1ef4 (movups [rsi],xmm0)
};
#pragma pack(pop)

// Struct for base register rax (the vtable of the callable object). The two fields are
// function pointers fetched from the vtable and called indirectly.
#pragma pack(push, 1)
struct sub_8f1e10_rax {
    std::uint8_t pad0x00[0x10];   // +0x00..+0x0f padding (no observed access)
    void* f10;                    // +0x10: vtable slot 2, called with (callable, &ctx)
                                  //        R at 0x8f1e5d (mov rax,[rax+0x10])
    std::uint8_t pad0x18[0x8];    // +0x18..+0x1f padding (no observed access)
    void* f20;                    // +0x20: vtable slot 4, called with (object, object != &ctx)
                                  //        R at 0x8f1e8e (mov rax,[rax+0x20])
};
#pragma pack(pop)

// Struct for the stack context object at RBP-0x40. Only the last two quadwords are touched.
#pragma pack(push, 1)
struct sub_8f1e10_ctx {
    std::uint8_t pad0x00[0x38];   // +0x00..+0x37 padding (no observed access)
    void* f38;                    // +0x38: owned context pointer, destroyed through vtable slot 4
                                  //        W at 0x8f1e2b (mov qword ptr [rbp-8],0)
                                  //        R at 0x8f1e78 (mov rcx,[rbp-8])
    std::uint64_t f40;            // +0x40: sentinel 0xFFFFFFFFFFFFFFFE
                                  //        W at 0x8f1e1d (mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE)
};
#pragma pack(pop)

// Struct for base register rbp (points at ctx+0x40).
#pragma pack(push, 1)
struct sub_8f1e10_rbp {
    std::uint64_t f0;   // +0x00 (= ctx+0x40): sentinel
                        //       W at 0x8f1e1d (mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE)
};
#pragma pack(pop)

// Struct for base register rsp (rbp = rsp+0x60, so rsp+0x60 is the ctx base).
#pragma pack(push, 1)
struct sub_8f1e10_rsp {
    std::uint8_t pad0x00[0x60];   // +0x00..+0x5f padding (no observed access)
    std::uint8_t f60;             // +0x60: ctx base, address formed by lea rbp,[rsp+0x60]
                                  //       R at 0x8f1e18 (lea rbp,[rsp+0x60])
};
#pragma pack(pop)

static_assert(offsetof(sub_8f1e10_rcx, f0) == 0x0, "sub_0x8f1e10 rcx+0x0 field");
static_assert(offsetof(sub_8f1e10_rcx, f88) == 0x88, "sub_0x8f1e10 rcx+0x88 field");
static_assert(offsetof(sub_8f1e10_rcx, f90) == 0x90, "sub_0x8f1e10 rcx+0x90 field");
static_assert(offsetof(sub_8f1e10_rcx, f98) == 0x98, "sub_0x8f1e10 rcx+0x98 field");
static_assert(offsetof(sub_8f1e10_rcx, f300) == 0x300, "sub_0x8f1e10 rcx+0x300 field");
static_assert(offsetof(sub_8f1e10_rcx, f34c) == 0x34c, "sub_0x8f1e10 rcx+0x34c field");
static_assert(offsetof(sub_8f1e10_rcx, f350) == 0x350, "sub_0x8f1e10 rcx+0x350 field");
static_assert(sizeof(sub_8f1e10_rcx) >= 0x351, "sub_0x8f1e10 rcx sizeof lower bound");

static_assert(offsetof(sub_8f1e10_rdx, f0) == 0x0, "sub_0x8f1e10 rdx+0x0 field");
static_assert(sizeof(sub_8f1e10_rdx) >= 0x10, "sub_0x8f1e10 rdx sizeof lower bound");

static_assert(offsetof(sub_8f1e10_rax, f10) == 0x10, "sub_0x8f1e10 rax+0x10 field");
static_assert(offsetof(sub_8f1e10_rax, f20) == 0x20, "sub_0x8f1e10 rax+0x20 field");
static_assert(sizeof(sub_8f1e10_rax) >= 0x28, "sub_0x8f1e10 rax sizeof lower bound");

static_assert(offsetof(sub_8f1e10_ctx, f38) == 0x38, "sub_0x8f1e10 ctx+0x38 field");
static_assert(offsetof(sub_8f1e10_ctx, f40) == 0x40, "sub_0x8f1e10 ctx+0x40 field");
static_assert(sizeof(sub_8f1e10_ctx) >= 0x48, "sub_0x8f1e10 ctx sizeof lower bound");

static_assert(offsetof(sub_8f1e10_rbp, f0) == 0x0, "sub_0x8f1e10 rbp+0x0 field");
static_assert(sizeof(sub_8f1e10_rbp) >= 0x8, "sub_0x8f1e10 rbp sizeof lower bound");

static_assert(offsetof(sub_8f1e10_rsp, f60) == 0x60, "sub_0x8f1e10 rsp+0x60 field");
static_assert(sizeof(sub_8f1e10_rsp) >= 0x61, "sub_0x8f1e10 rsp sizeof lower bound");

// x64 Microsoft ABI: RCX = self, RDX = out; returns RAX = out.
// 0x8f1e25  mov rsi,rdx; 0x8f1e28  mov rdi,rcx; 0x8f1ef7  mov rax,rsi.
sub_8f1e10_rdx* sub_8f1e10(sub_8f1e10_rcx* self, sub_8f1e10_rdx* out);

} // namespace native::helpers
