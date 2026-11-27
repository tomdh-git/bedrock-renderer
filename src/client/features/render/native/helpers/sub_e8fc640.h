#pragma once
#include <cstddef>
#include <cstdint>

#include "sub_2462890.h"   // lift callees: sub_2462890(void*) and sub_e935700(void*) forward declarations

namespace native::helpers {

// Typed state layouts for sub_e8fc640 (0xe8fc640, size 0x11f, 1.26.62.01).
// Every field is cited with the instruction that reads or writes it. The layouts
// are packed so each declared field sits exactly at its observed offset; the real
// objects may carry compiler alignment padding, so sizeof is a lower bound.
//
// The function releases, in order: the +0xE8 child object (through vtable slot 0),
// the +0xB0 allocation, the +0xA0 sub-object (through lift callee sub_2462890), and
// the +0x58 string allocation, then resets the string to its empty inline state.

// Sub-object at +0xA0 of the self object. sub_2462890 treats its argument as an
// object whose vtable pointer is at +0x00 and whose state pointer is at +0x08
// (see sub_2462890.h), so those two slots are typed here.
#pragma pack(push, 1)
struct sub_e8fc640_list {
    void* vtable;   // +0x00: 0xe8fc6e3 passes &self->list to sub_2462890, which reads [a0]
    void* state;    // +0x08: sub_2462890 reads [vtable+0x08] and clears the pointed-to qword
};
#pragma pack(pop)

// Object addressed by RCX (the `self` argument).
#pragma pack(push, 1)
struct sub_e8fc640_rcx {
    void* f0;                      // +0x00: R 0xe8fc660, R 0xe8fc67d (RCX there is the +0xE8 child; same offset 0)
    std::uint8_t pad0x08[0x50];    // +0x08..+0x57: no access in this function
    void* stringData;              // +0x58: R 0xe8fc6f9 (heap text pointer), W 0xe8fc73a (first byte reset to 0)
    std::uint8_t pad0x60[0x8];     // +0x60..+0x67: no access in this function
    std::uint64_t stringSize;      // +0x68: W 0xe8fc72a
    std::uint64_t stringCapacity;  // +0x70: R 0xe8fc6ef, W 0xe8fc732
    std::uint8_t pad0x78[0x28];    // +0x78..+0x9f: no access in this function
    sub_e8fc640_list list;         // +0xa0: address taken by 0xe8fc6e3 for sub_2462890
    void* bufferBegin;             // +0xb0: R 0xe8fc68e, zeroed by 0xe8fc6d8
    std::uint8_t pad0xb8[0x8];     // +0xb8: zeroed by 0xe8fc6d8 (second half of the 16-byte store)
    void* bufferEnd;               // +0xc0: R 0xe8fc69a, zeroed by 0xe8fc6db
    std::uint8_t pad0xc8[0x20];    // +0xc8..+0xe7: no access in this function
    void* child;                   // +0xe8: R 0xe8fc649, W 0xe8fc650, R 0xe8fc671
};
#pragma pack(pop)

// Vtable array of the +0xE8 child object. 0xe8fc660/0xe8fc67d read the vtable
// pointer from the child, then read slot 0 and call it with (child, 1).
#pragma pack(push, 1)
struct sub_e8fc640_rax {
    void* slot0;   // +0x00: R 0xe8fc663, R 0xe8fc680 (the called target)
};
#pragma pack(pop)

// Overlay used by 0xe8fc6c9 (lea rdi,[rsi+0xB0]): 0xe8fc6d8 stores 16 zero bytes
// at +0xB0 and 0xe8fc6db stores a zero qword at +0xC0.
#pragma pack(push, 1)
struct sub_e8fc640_rdi {
    std::uint64_t clearedWords[2];   // +0x00: W 0xe8fc6d8 (movups [rdi],xmm0)
    std::uint64_t clearedTail;       // +0x10: W 0xe8fc6db
};
#pragma pack(pop)

// Stack slot written by 0xe8fc745 (mov qword ptr [rsp+0x20],0), the home of the
// fifth argument of the failure call at 0xe8fc758.
#pragma pack(push, 1)
struct sub_e8fc640_rsp {
    std::uint8_t pad0x00[0x20];      // +0x00..+0x1f: shadow space of the failure call
    std::uint64_t fifthArgumentHome; // +0x20: W 0xe8fc745
};
#pragma pack(pop)

static_assert(offsetof(sub_e8fc640_list, vtable) == 0x0, "sub_0xe8fc640 list+0x0 field");
static_assert(offsetof(sub_e8fc640_list, state) == 0x8, "sub_0xe8fc640 list+0x8 field");
static_assert(sizeof(sub_e8fc640_list) == 0x10, "sub_0xe8fc640 list extent");

static_assert(offsetof(sub_e8fc640_rcx, f0) == 0x0, "sub_0xe8fc640 rcx+0x0 field");
static_assert(offsetof(sub_e8fc640_rcx, stringData) == 0x58, "sub_0xe8fc640 rcx+0x58 field");
static_assert(offsetof(sub_e8fc640_rcx, stringSize) == 0x68, "sub_0xe8fc640 rcx+0x68 field");
static_assert(offsetof(sub_e8fc640_rcx, stringCapacity) == 0x70, "sub_0xe8fc640 rcx+0x70 field");
static_assert(offsetof(sub_e8fc640_rcx, list) == 0xa0, "sub_0xe8fc640 rcx+0xa0 field");
static_assert(offsetof(sub_e8fc640_rcx, bufferBegin) == 0xb0, "sub_0xe8fc640 rcx+0xb0 field");
static_assert(offsetof(sub_e8fc640_rcx, bufferEnd) == 0xc0, "sub_0xe8fc640 rcx+0xc0 field");
static_assert(offsetof(sub_e8fc640_rcx, child) == 0xe8, "sub_0xe8fc640 rcx+0xe8 field");
static_assert(sizeof(sub_e8fc640_rcx) >= 0xf0, "sub_0xe8fc640 rcx sizeof lower bound");

static_assert(offsetof(sub_e8fc640_rax, slot0) == 0x0, "sub_0xe8fc640 rax+0x0 field");
static_assert(sizeof(sub_e8fc640_rax) >= 0x8, "sub_0xe8fc640 rax sizeof lower bound");

static_assert(offsetof(sub_e8fc640_rdi, clearedWords) == 0x0, "sub_0xe8fc640 rdi+0x0 field");
static_assert(offsetof(sub_e8fc640_rdi, clearedTail) == 0x10, "sub_0xe8fc640 rdi+0x10 field");
static_assert(sizeof(sub_e8fc640_rdi) >= 0x18, "sub_0xe8fc640 rdi sizeof lower bound");

static_assert(offsetof(sub_e8fc640_rsp, fifthArgumentHome) == 0x20, "sub_0xe8fc640 rsp+0x20 field");
static_assert(sizeof(sub_e8fc640_rsp) >= 0x28, "sub_0xe8fc640 rsp sizeof lower bound");

// x64 Microsoft ABI: the self object arrives in RCX (0xe8fc646 mov rsi,rcx); the
// function writes no result register on its normal exit (0xe8fc744 ret) and is a
// destructor-style release routine, so the C++ return type is void.
void sub_e8fc640(void* self);

} // namespace native::helpers
