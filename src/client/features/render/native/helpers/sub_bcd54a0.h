#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_e935700 (0xe935700, size 0x5, 1.26.62.01): lift-set callee (tail jump to sub_392960).
// Forward declaration only; full declaration with layout lives in helpers/sub_e935700.h.
void* sub_e935700(void* a0);

// Layout overlay of the argument object of 0xbcd54a0 (sub_bcd54a0, size 0xb9,
// 1.26.62.01). Every offset below is [V] from the disassembly of the function:
//   +0x10  char[8] buffer (R: 0xbcd54e7 mov rcx,[rsi+0x10] reads the 8-byte buffer pointer;
//                              W: 0xbcd5528 mov byte ptr [rsi+0x10],0 stores a single zero byte)
//   +0x20  qword field20  (W: 0xbcd5518 mov qword ptr [rsi+0x20],0)
//   +0x28  qword size     (R: 0xbcd54dd mov rax,[rsi+0x28]; W: 0xbcd5520 mov qword ptr [rsi+0x28],0xF)
//   +0x40  qword refObject(R: 0xbcd54a9 mov rdi,[rcx+0x40])
struct alignas(8) ArgLayout {
    // +0x00..+0x0F: other fields (untouched by this function)
    char pad00[0x10];              // +0x00
    char field10[8];               // +0x10  R/W buffer pointer (dual-use: heap ptr when large, inline char when small)
    char pad18[0x8];               // +0x18
    uintptr_t field20;             // +0x20
    uintptr_t size;                // +0x28
    char pad30[0x10];              // +0x30
    void* refObject;               // +0x40
};
static_assert(offsetof(ArgLayout, field10) == 0x10, "ArgLayout+0x10 field10");
static_assert(offsetof(ArgLayout, field20) == 0x20, "ArgLayout+0x20 field20");
static_assert(offsetof(ArgLayout, size) == 0x28, "ArgLayout+0x28 size");
static_assert(offsetof(ArgLayout, refObject) == 0x40, "ArgLayout+0x40 refObject");
static_assert(sizeof(ArgLayout) == 0x48, "ArgLayout size");

// x64 Microsoft ABI: argument in RCX, return value in RAX (the tail call to
// sub_e935700 passes RAX through).
// 0xbcd54a0, size 0xb9, 1.26.62.01.
void* sub_bcd54a0(void* a0);

} // namespace native
