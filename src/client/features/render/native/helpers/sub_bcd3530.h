#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// sub_bcd3530 (0xbcd3530..0xbcd3639) destroys the three owning containers of the object
// received in RCX. RCX is copied to RSI at 0xbcd3537 and RSI is the base of every self
// access until the end of the body, so the layout below is the RCX object seen through RSI:
//   +0x28  pointer to a list header owning a singly linked chain of 0x50-byte nodes
//   +0x38  begin/end/capacity pointer triple of heap buffer B
//   +0x08  begin/end/capacity pointer triple of heap buffer A
// Every offset and width is taken from the instruction operands; the field names state the
// role the instructions give each slot. The structs are packed (#pragma pack(1)) so each
// offsetof() equals its observed offset; sizeof is a lower bound because unobserved tail
// bytes are not declared.

#pragma pack(push, 1)

// One node of the chain reached through self+0x28; freed with size 0x50 at 0xbcd35b4.
struct sub_bcd3530_rdi {
    sub_bcd3530_rdi* next;      // +0x00  R 0xbcd35a0 (saved as the loop cursor at 0xbcd35b9)
    std::uint8_t pad08[0x8];    // +0x08..+0x0f  no observed access
    std::uint64_t payload;      // +0x10  address taken at 0xbcd35a3, passed in RCX to 0x9b250
    std::uint8_t pad18[0x38];   // +0x18..+0x4f  no observed access (node size 0x50)
};

// List header stored at self+0x28 (itself a 0x50-byte allocation, freed at 0xbcd35ca).
struct sub_bcd3530_rax {
    sub_bcd3530_rdi* first;     // +0x00  R 0xbcd3595 (head of the node chain)
    std::uint64_t* clearSlot;   // +0x08  R 0xbcd358a; *clearSlot = 0 written at 0xbcd358e
};

// The object passed in RCX (moved to RSI at 0xbcd3537).
struct sub_bcd3530_rcx {
    std::uint8_t pad00[0x8];    // +0x00..+0x07  no observed access
    void* bufferABegin;         // +0x08  R 0xbcd35cf  W 0xbcd360c
    void* bufferAEnd;           // +0x10  W 0xbcd360c (16-byte zero store covers +0x08/+0x10)
    void* bufferACap;           // +0x18  R 0xbcd35d8  W 0xbcd360f
    std::uint8_t pad20[0x8];    // +0x20..+0x27  no observed access
    sub_bcd3530_rax* listHeader;// +0x28  R 0xbcd3586, 0xbcd35c1
    std::uint8_t pad30[0x8];    // +0x30..+0x37  no observed access
    void* bufferBBegin;         // +0x38  R 0xbcd353a  W 0xbcd357b
    void* bufferBEnd;           // +0x40  W 0xbcd357b
    void* bufferBCap;           // +0x48  R 0xbcd3543  W 0xbcd357e
};

// Caller frame slot written by the failing aligned-deallocation path at 0xbcd361f; the
// five-argument call type in the .cpp places the same zero in this [rsp+0x20] position.
struct sub_bcd3530_rsp {
    std::uint8_t pad00[0x20];   // +0x00..+0x1f  no observed access
    std::uint64_t fifthArgument;// +0x20  W 0xbcd361f
};

#pragma pack(pop)

static_assert(offsetof(sub_bcd3530_rdi, next) == 0x0, "sub_0xbcd3530 rdi+0x0 field");
static_assert(offsetof(sub_bcd3530_rdi, payload) == 0x10, "sub_0xbcd3530 rdi+0x10 field");
static_assert(sizeof(sub_bcd3530_rdi) >= 0x50, "sub_0xbcd3530 rdi sizeof lower bound");

static_assert(offsetof(sub_bcd3530_rax, first) == 0x0, "sub_0xbcd3530 rax+0x0 field");
static_assert(offsetof(sub_bcd3530_rax, clearSlot) == 0x8, "sub_0xbcd3530 rax+0x8 field");
static_assert(sizeof(sub_bcd3530_rax) >= 0x10, "sub_0xbcd3530 rax sizeof lower bound");

static_assert(offsetof(sub_bcd3530_rcx, bufferABegin) == 0x8, "sub_0xbcd3530 rcx+0x8 field");
static_assert(offsetof(sub_bcd3530_rcx, bufferAEnd) == 0x10, "sub_0xbcd3530 rcx+0x10 field");
static_assert(offsetof(sub_bcd3530_rcx, bufferACap) == 0x18, "sub_0xbcd3530 rcx+0x18 field");
static_assert(offsetof(sub_bcd3530_rcx, listHeader) == 0x28, "sub_0xbcd3530 rcx+0x28 field");
static_assert(offsetof(sub_bcd3530_rcx, bufferBBegin) == 0x38, "sub_0xbcd3530 rcx+0x38 field");
static_assert(offsetof(sub_bcd3530_rcx, bufferBEnd) == 0x40, "sub_0xbcd3530 rcx+0x40 field");
static_assert(offsetof(sub_bcd3530_rcx, bufferBCap) == 0x48, "sub_0xbcd3530 rcx+0x48 field");
static_assert(sizeof(sub_bcd3530_rcx) >= 0x50, "sub_0xbcd3530 rcx sizeof lower bound");

static_assert(offsetof(sub_bcd3530_rsp, fifthArgument) == 0x20, "sub_0xbcd3530 rsp+0x20 field");
static_assert(sizeof(sub_bcd3530_rsp) >= 0x28, "sub_0xbcd3530 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI): the single argument arrives in RCX (0xbcd3537 mov rsi,rcx),
// RCX is a pointer whose +0x38 is dereferenced at 0xbcd353a, and the epilogue at 0xbcd361e
// returns without setting a result register, so the function returns void.
void sub_bcd3530(void* self);

} // namespace native::helpers
