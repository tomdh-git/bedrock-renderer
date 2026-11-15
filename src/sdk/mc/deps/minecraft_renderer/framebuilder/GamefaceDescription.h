#pragma once
// Effect/UI tag Gameface description, read from extractGameface 0x66ade80 (1.26.62.01). docs/functions/66ade80.md. All offsets [V] (displacements read through r8).
#include "WeatherDescription.h"

namespace bluey::gameface {

enum class Kind : uint32_t {  // jump table 0xf2bf8a8 at 0x66ae270; names resolved from the case tails
    Standard = 0, StandardRare = 1, Stencil = 2, StencilRare = 3, StencilPath = 4,
    ClearQuad = 5, Renoir = 6, Path = 7, TexturesWithColorMix = 8,
};

// Blend factor pair (desc+4, desc+5) -> enum stored at rbp+0x530 (0x66aeac0..0x66aebcb). Any other pair throws (0x66b049a).
struct BlendPairMap { uint8_t b4, b5, value; };
constexpr BlendPairMap kBlendPairs[] = {
    {6, 8, 3 /* only with desc+6 == 3 and desc+7 == 8; otherwise value 2 */}, {2, 2, 0}, {3, 2, 1}, {6, 8, 2},
    {3, 8, 4}, {4, 5, 5}, {3, 3, 6}, {6, 3, 7}, {0, 2, 8}, {0, 1, 9}, {2, 8, 10},
};
static_assert(sizeof(kBlendPairs) / sizeof(kBlendPairs[0]) == 11);

struct GamefaceDescription {
    Kind     kind;          // +0x00
    uint8_t  blendSrc;      // +0x04 \ pair, see kBlendPairs
    uint8_t  blendDst;      // +0x05 /
    uint8_t  b06;           // +0x06
    uint8_t  b07;           // +0x07
    uint8_t  b08;           // +0x08 (& 0xf -> draw state byte)
    uint8_t  pad09[3];
    uint8_t  b0c;           // +0x0c
    uint8_t  b0d;           // +0x0d
    uint8_t  b0e;           // +0x0e index into the table 0x104070502080603
    uint8_t  sub0f[8];      // +0x0f..+0x16 two overlapping windows (+0xf and +0x13) normalised by 0x66983b0
    uint8_t  pad17;         // +0x17 (==1 flag)
    uint8_t  pad18[0x10];
    uint8_t  variantA[0x10];// +0x28, tag byte at +0x38
    uint8_t  tagA;         // +0x38
    uint8_t  pad39[7];
    uint8_t  variantB[0x10];// +0x40, tag byte at +0x50
    uint8_t  tagB;         // +0x50
    uint8_t  pad51[7];
    weather::Vec4 viewport; // +0x58 (-> rbp+0x2f0)
    weather::Vec4 vec68;    // +0x68 (-> rbp+0x300)
    uint8_t  pad78[8];
    void*    records;       // +0x80 list of 0x1a0-byte records
};
static_assert(offsetof(GamefaceDescription, blendSrc) == 0x04);
static_assert(offsetof(GamefaceDescription, b08) == 0x08);
static_assert(offsetof(GamefaceDescription, b0c) == 0x0c);
static_assert(offsetof(GamefaceDescription, b0e) == 0x0e);
static_assert(offsetof(GamefaceDescription, pad17) == 0x17);
static_assert(offsetof(GamefaceDescription, variantA) == 0x28);
static_assert(offsetof(GamefaceDescription, tagA) == 0x38);
static_assert(offsetof(GamefaceDescription, variantB) == 0x40);
static_assert(offsetof(GamefaceDescription, tagB) == 0x50);
static_assert(offsetof(GamefaceDescription, viewport) == 0x58);
static_assert(offsetof(GamefaceDescription, vec68) == 0x68);
static_assert(offsetof(GamefaceDescription, records) == 0x80);

// Record at [desc+0x80] list, stride 0x1a0 (add r15, 0x1a0 at 0x66aece0).
constexpr size_t kRecordStride = 0x1a0;
constexpr size_t kRecDataVS = 0x50, kRecDataVSSize = 0x58, kRecDataPS = 0x60, kRecDataPSSize = 0x68;
constexpr size_t kRecMatBegin = 0x138, kRecMatEnd = 0x140;   // mat4 (0x40-byte) array
constexpr size_t kRecFloat184 = 0x184, kRecDword188 = 0x188, kRecByte18C = 0x18c, kRecVec4190 = 0x190;

// Draw record built at rbp+0x320 and the pass entry built at rbp+0x208 (size 0xc8), indices as P+vector item counts.
struct PassEntry {
    uint64_t head;       // +0x00: 0x10000, |= 0x7000 (0x17000), final 0x40000417000
    uint8_t  pad08[0x20];
    uint16_t idx780;     // +0x28 P+0x780 stride 0x28
    uint16_t idx768;     // +0x2a P+0x768 stride 0x88
    uint16_t idx750;     // +0x2c P+0x750 stride 0x58
    uint8_t  pad2e[2];
    uint16_t idx720;     // +0x30 P+0x720 (0x40-byte items, 0x67d7410)
    uint8_t  pad32[0x0a];
    uint16_t idx690;     // +0x3c P+0x690 (u16 vector)
    uint8_t  pad3e[0x26];
    uint16_t idx4b0;     // +0x64 P+0x4b0 (0x18-byte vector-of-buffers)
    uint8_t  pad66[0x62];
};
static_assert(sizeof(PassEntry) == 0xc8);
static_assert(offsetof(PassEntry, idx780) == 0x28);
static_assert(offsetof(PassEntry, idx768) == 0x2a);
static_assert(offsetof(PassEntry, idx750) == 0x2c);
static_assert(offsetof(PassEntry, idx720) == 0x30);
static_assert(offsetof(PassEntry, idx690) == 0x3c);
static_assert(offsetof(PassEntry, idx4b0) == 0x64);

} // namespace bluey::gameface
