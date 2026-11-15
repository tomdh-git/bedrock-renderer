#pragma once

// Sampler flag word -> D3D12_SAMPLER_DESC, exactly as RendererContextD3D12 sampler builder 0xe820500 does it (1.26.62.01, static [V],
// see docs/functions/e820500.md). Tables read from the exe: address modes at rva 0xf3d6530, filter bytes at 0xf4ecbbc, comparison at 0xf4ecbd0,
// MaxLOD floats at 0xf4ed270.
namespace bgfx::d3d12 {

namespace SamplerFlag {
// bit layout of the u32 flag word (stock bgfx 32-bit sampler flags)
inline constexpr uint32_t kUShift = 0, kUMask = 0x3;            // 0 WRAP 1 MIRROR 2 CLAMP 3 BORDER
inline constexpr uint32_t kVShift = 2, kVMask = 0xC;
inline constexpr uint32_t kWShift = 4, kWMask = 0x30;
inline constexpr uint32_t kMinShift = 6, kMinMask = 0xC0;       // 0 linear, 1 point (0x40), 2 anisotropic (0x80)
inline constexpr uint32_t kMagShift = 8, kMagMask = 0x300;      // same encoding
inline constexpr uint32_t kMipPoint = 0x400;                    // set = mip point, clear = mip linear
inline constexpr uint32_t kCmpShift = 16, kCmpMask = 0xF0000;   // 0 none, 1..8 = bgfx compare func
inline constexpr uint32_t kBorderShift = 24, kBorderMask = 0xF000000; // index into the caller's 16-byte border colour table
inline constexpr uint32_t kMaxLod3 = 0x10000000;                // fork: set = MaxLOD 3.0, clear = FLT_MAX (6ax claimed "border colour select": wrong)
} // namespace SamplerFlag

// D3D12_SAMPLER_DESC (0x34 bytes), the stack object the builder fills at rsp+0x70
struct SamplerDesc {
    uint32_t mFilter;        // +0x00
    uint32_t mAddressU;      // +0x04
    uint32_t mAddressV;      // +0x08
    uint32_t mAddressW;      // +0x0C
    float mMipLodBias;       // +0x10  always 0
    uint32_t mMaxAnisotropy; // +0x14  ctx+0x19FD8 (1, or 16 with reset flag 0x100)
    uint32_t mComparison;    // +0x18  D3D12_COMPARISON_FUNC, 1 (NEVER) when the flag nibble is 0
    float mBorderColor[4];   // +0x1C
    float mMinLod;           // +0x2C  always 0
    float mMaxLod;           // +0x30  3.0 or FLT_MAX
};
static_assert(sizeof(SamplerDesc) == 0x34);
static_assert(offsetof(SamplerDesc, mMaxAnisotropy) == 0x14 && offsetof(SamplerDesc, mComparison) == 0x18);
static_assert(offsetof(SamplerDesc, mBorderColor) == 0x1C && offsetof(SamplerDesc, mMinLod) == 0x2C && offsetof(SamplerDesc, mMaxLod) == 0x30);

// byte table at 0xf4ecbbc: min {0x10,0x00,0x55}, mag {0x04,0x00,0x55}, mip {0x01 (linear), 0x00 (point)}
inline constexpr uint8_t kMinFilterBits[3] = {0x10, 0x00, 0x55};
inline constexpr uint8_t kMagFilterBits[3] = {0x04, 0x00, 0x55};
inline constexpr uint8_t kMipFilterBits[2] = {0x01, 0x00};
// u32 table at 0xf3d6530 (D3D12_TEXTURE_ADDRESS_MODE: WRAP 1, MIRROR 2, CLAMP 3, BORDER 4)
inline constexpr uint32_t kAddressMode[4] = {1, 2, 3, 4};
// u32 table at 0xf4ecbd0, index = bgfx compare func: NONE, LESS, LEQUAL, EQUAL, GEQUAL, GREATER, NOTEQUAL, NEVER, ALWAYS
inline constexpr uint32_t kComparison[9] = {0, 2, 4, 3, 7, 5, 6, 1, 8};

constexpr uint32_t samplerFilter(uint32_t f) {
    uint32_t r = kMinFilterBits[(f >> SamplerFlag::kMinShift) & 3] | kMagFilterBits[(f >> SamplerFlag::kMagShift) & 3]
               | kMipFilterBits[(f & SamplerFlag::kMipPoint) ? 1 : 0];
    return r | (((f & SamplerFlag::kCmpMask) != 0) ? 0x80u : 0u);
}
constexpr uint32_t samplerComparison(uint32_t f) {
    uint32_t c = (f & SamplerFlag::kCmpMask) >> SamplerFlag::kCmpShift;
    return c ? kComparison[c] : 1u;
}
// the builder reads the border colour only when W, U or V is BORDER (3) and a table pointer was supplied; entry = (f >> 24) & 0xF, 16 bytes each
constexpr bool samplerUsesBorder(uint32_t f) {
    return (f & 0x30) == 0x30 || (f & 3) == 3 || (f & 0xC) == 0xC;
}

// worked checks against the tables: default flags 0 = linear/linear/linear, wrap; 0x400 = mip point
static_assert(samplerFilter(0) == 0x15);
static_assert(samplerFilter(0x400) == 0x14);
static_assert(samplerFilter(0x40 | 0x100 | 0x400) == 0x00);
static_assert(samplerFilter(0x80 | 0x200) == 0x55);
static_assert(samplerFilter(0x10000) == 0x95); // comparison filter = linear bits | 0x80
static_assert(samplerComparison(0) == 1 && samplerComparison(1u << 16) == 2 && samplerComparison(7u << 16) == 1 && samplerComparison(8u << 16) == 8);
static_assert(samplerUsesBorder(3) && samplerUsesBorder(0xC) && samplerUsesBorder(0x30) && !samplerUsesBorder(0x15));

} // namespace bgfx::d3d12
