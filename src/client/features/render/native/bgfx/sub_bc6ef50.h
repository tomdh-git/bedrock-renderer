#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/helpers/sub_ebce650.h"

namespace native {

// sub_ebce5e0: bounded C-string length (strnlen-like): returns 0 for a null string,
// otherwise the number of non-null bytes up to maxlen. Declared in
// src/client/features/render/native/helpers/sub_ebce5e0.h.
extern "C" std::int32_t sub_ebce5e0(const char* str, std::int32_t maxlen) noexcept;

// sub_ebdbf10 (lock) / sub_ebdbf20 (unlock): lock/unlock a ctx+0x3D0 spinlock.
// Declared in src/client/features/render/native/helpers/sub_ebdbf10.h and
// src/client/features/render/native/helpers/sub_ebdbf20.h.
extern "C" void sub_ebdbf10(void* lock) noexcept;
extern "C" void sub_ebdbf20(void* lock) noexcept;

} // namespace native

namespace native::bgfx {

// Layout recovered from the disassembly of 0xbc6ef50 (size 0xf1, range [0xbc6ef50, 0xbc6f041)).
// The function walks a per-element block array starting at (a0 + 0x4F0). Each element block is
// 0x138 bytes and begins with a NUL-terminated string. The element count is *(uint16_t*)(a0+0x4E8)
// capped by the arg2 cap.
//   +0x00  char[0x138]   block data; block[0..] is a NUL-terminated string
struct FrameBlock {
    char data[0x138];  // +0x00: 312-byte block; data[0..] begins with a NUL-terminated string
};
static_assert(offsetof(FrameBlock, data) == 0x00, "sub_bc6ef50: FrameBlock::data must be at +0x00");
static_assert(sizeof(FrameBlock) == 0x138, "sub_bc6ef50: FrameBlock must be 0x138 bytes");

// data_f847a07: default (empty) source string used when a block's string length is 0;
// declared in src/client/features/render/native/d3d12/sub_e8189c0.h.
extern char data_f847a07[];

// Lifted function: 0xbc6ef50, size 0xf1, range [0xbc6ef50, 0xbc6f041), returns int.
// x64 Microsoft ABI:
//   rcx = void* a0    this / a0 (reads uint16_t count at a0+0x4E8, block array base at a0+0x4F0)
//   rdx = int   a2    count cap (arg2), unsigned; effective count = min(cap, *(uint16_t*)(a0+0x4E8))
//   r8  = void* a3    destination block base (must be non-null; each block gets 0x138 bytes +
//                     a bounded string copy at its start)
//   r9 = unused
//   return = int      number of blocks processed (esi), or 0 if a3 == 0 or effective count == 0
extern "C" int sub_bc6ef50(void* a0, int a2, void* a3) noexcept;

} // namespace native::bgfx
