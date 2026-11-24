#pragma once
#include <cstdint>
#include <cstddef>

namespace native { namespace d3d12 {

// LIFT 0xe86d770 size 0x7d 1.26.62.01 sub_e86d770
// Stencil-face descriptor read by sub_e86d770 (offsets from disassembly [rcx+0x0], [rcx+0x4], [rcx+0x8], [rcx+0xC]).
struct StencilFaceDesc {
    std::uint8_t  op0;       // +0x00  ; dec al, lookup table at 0xF491060
    std::uint8_t  _pad0[3];
    std::uint32_t v1;        // +0x04  ; lookup table at 0xF4F0140
    std::uint32_t v2;        // +0x08  ; lookup table at 0xF4F0160
    std::uint32_t v3;        // +0x0C  ; lookup table at 0xF4F0120
};

static_assert(offsetof(StencilFaceDesc, op0) == 0x00, "StencilFaceDesc op0 +0x0");
static_assert(offsetof(StencilFaceDesc, v1) == 0x04, "StencilFaceDesc v1 +0x4");
static_assert(offsetof(StencilFaceDesc, v2) == 0x08, "StencilFaceDesc v2 +0x8");
static_assert(offsetof(StencilFaceDesc, v3) == 0x0C, "StencilFaceDesc v3 +0xC");
static_assert(sizeof(StencilFaceDesc) >= 0x10, "StencilFaceDesc size");

// x64 Microsoft ABI: rcx = const StencilFaceDesc* desc, dl = a2, r8b = a3.
extern "C" std::uint32_t sub_e86d770(const StencilFaceDesc* desc, std::uint8_t a2, std::uint8_t a3);

} } // namespace native::d3d12