#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_675b450 (0x675b450, size 0xc8, 1.26.62.01, "BgfxFrameBuilder::endFrame").
//
// Layout of the fields of BgfxFrameBuilder used by this function, observed in
// the disassembly of [0x675b450, 0x675b518):
//   0x675b486  mov rdx,[rcx+0x18]     (R: cur/end write pointer)
//   0x675b48a  cmp rdx,[rcx+0x20]     (R: cap/end pointer)
//   0x675b4a2  lea rcx,[rsi+0x10]     (&self+0x10 passed to sub_b0ad0 as the vector object: [+0x00]=begin,[+0x08]=end,[+0x10]=cap)
// Only the fields used by this function are declared; nothing else about the
// class layout is assumed.
namespace native {

struct BgfxFrameBuilder {
    std::uint8_t _pad_0x00[0x10];  // +0x00 unused by this function
    // +0x10: vector object base (used as &self+0x10; sub_b0ad0 reads/writes [+0x00],[+0x08],[+0x10] relative to it)
    // +0x18: cur/end write pointer (R/W)
    // +0x20: cap/end pointer (R)
    std::int64_t field0x10;        // +0x10
    std::int64_t field0x18;        // +0x18
    std::int64_t field0x20;        // +0x20
};
static_assert(offsetof(BgfxFrameBuilder, field0x10) == 0x10, "675b450: BgfxFrameBuilder::field0x10 at +0x10");
static_assert(offsetof(BgfxFrameBuilder, field0x18) == 0x18, "675b450: BgfxFrameBuilder::field0x18 at +0x18");
static_assert(offsetof(BgfxFrameBuilder, field0x20) == 0x20, "675b450: BgfxFrameBuilder::field0x20 at +0x20");

// Element pushed into the vector, laid out as the local at [rbp-0x50]:
//   0x675b473  movaps [rbp-0x40],xmm0   (elem+0x10 = xmm0 from [0xF2BE848])
//   0x675b47e  movaps [rbp-0x50],xmm1   (elem+0x00 = xmm1 from [0xF2BE838])
//   0x675b482  mov byte ptr [rbp],0     (elem+0x50 flag = 0)
// sub_b0ad0 copies [elem+0x00] (16B), [elem+0x10] (16B) and reads [elem+0x50].
// Element size is 0x58 (cur advances by 0x58).
struct EndFrameElem {
    std::uint64_t lo0;     // +0x00  xmm1 low
    std::uint64_t hi0;     // +0x08  xmm1 high
    std::uint64_t lo1;     // +0x10  xmm0 low
    std::uint64_t hi1;     // +0x18  xmm0 high
    std::uint8_t _pad[0x50 - 0x20];  // +0x20..+0x4f unused by this function
    std::uint8_t flag;     // +0x50  flag byte read by sub_b0ad0
};
static_assert(offsetof(EndFrameElem, lo0) == 0x00, "675b450: EndFrameElem::lo0 at +0x00");
static_assert(offsetof(EndFrameElem, lo1) == 0x10, "675b450: EndFrameElem::lo1 at +0x10");
static_assert(offsetof(EndFrameElem, flag) == 0x50, "675b450: EndFrameElem::flag at +0x50");
static_assert(sizeof(EndFrameElem) == 0x58, "675b450: EndFrameElem size 0x58");

// sub_b0ad0 (0xb0ad0, stl boundary, native_boundary.tsv row 0xb0ad0): MSVC STL
// vector-like push_back / reallocate.
//   RCX = vector object ([+0x00]=begin,[+0x08]=end,[+0x10]=cap)  -> &self+0x10
//   RDX = end pointer (position to push at)                     -> self+0x18
//   R8  = element to copy (0x58 bytes)                          -> &elem
// Reallocates if needed, copy-constructs the element at end, advances end by
// 0x58. Reads the element's +0x50 byte as a flag. Return value ignored by the
// caller. Called directly through its native symbol (stl boundary, not lifted).
void sub_b0ad0(void* vec, void* end, void* element);

// sub_e935700 (0xe935700, lift, already lifted in helpers/sub_e935700.cpp):
// tail jump to sub_392960; buffer free/dealloc via vendor thunk [0xF99FFA0].
// Argument forwarded in RCX, result in RAX (ignored by this caller).
void* sub_e935700(void* a0);

// Global 16-byte constants read by the function:
//   0x675b46c  movups xmm0,[0xF2BE848]
//   0x675b477  movups xmm1,[0xF2BE838]
inline const std::uint8_t* data_f2be848() {
    return reinterpret_cast<const std::uint8_t*>(RewriteRegistry::imageBase() + 0xF2BE848);
}
inline const std::uint8_t* data_f2be838() {
    return reinterpret_cast<const std::uint8_t*>(RewriteRegistry::imageBase() + 0xF2BE838);
}

// Signature of sub_675b450 itself: x64 Microsoft ABI, self in RCX, returns
// self in RAX.
void* sub_675b450(void* self);

} // namespace native
