#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_e87c6d0 (0xe87c6d0, size 0x9d, 1.26.62.01): lift-set callee.
// Declared in src/client/features/render/native/d3d12/sub_e87c6d0.h.
void sub_e87c6d0(void* a0);

// sub_e935700 (0xe935700, size 0x5, 1.26.62.01): lift-set callee (tail jump to sub_392960).
// Declared in src/client/features/render/native/helpers/sub_e935700.h.
void* sub_e935700(void* a0);

// Layout overlay of the argument object of 0xbcd41c0 (sub_bcd41c0, size 0xad,
// 1.26.62.01). Every offset below is [V] from the disassembly of the function:
//   +0x00  pointer field (R: 0xbcd41c9 mov rdi,[rcx]; W: 0xbcd423e movups [rsi],xmm0)
//   +0x08  pointer field (R: 0xbcd41d4 mov r14,[rcx+8]; W: 0xbcd423e movups [rsi],xmm0)
//   +0x10  pointer field (R: 0xbcd420b mov rdx,[rsi+0x10]; W: 0xbcd4241 mov [rsi+0x10],0)
struct alignas(8) ArgLayout {
    void* field00;          // +0x00  R/W list current/start pointer
    void* field08;          // +0x08  R/W end pointer
    void* field10;          // +0x10  R/W buffer end pointer
};

static_assert(offsetof(ArgLayout, field00) == 0x00, "ArgLayout+0x00 field00");
static_assert(offsetof(ArgLayout, field08) == 0x08, "ArgLayout+0x08 field08");
static_assert(offsetof(ArgLayout, field10) == 0x10, "ArgLayout+0x10 field10");
static_assert(sizeof(ArgLayout) == 0x18, "ArgLayout size");

// x64 Microsoft ABI: argument in RCX, no return value.
// 0xbcd41c0, size 0xad, 1.26.62.01.
void sub_bcd41c0(void* a0);

} // namespace native
