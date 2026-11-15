#pragma once
// Sky tag 9 (Weather) description + pass entry, read from the disassembly of extractWeather 0x6745440 (1.26.62.01).
// docs/functions/6745440.md. Offsets are the displacements the extractor reads through r8; every one is [V].
#include <cstddef>
#include <cstdint>

namespace bluey::weather {

struct Vec4 { float x, y, z, w; };
static_assert(sizeof(Vec4) == 0x10);

struct TextureBind16 { uint8_t raw[0x10]; };   // +0x50/+0x60/+0x70 passed by address to 0xbcaba00 (bind texture); inner layout not read here

struct WeatherDescription {
    void*         owner;            // +0x00: [+0x58/+0x60] vector of 12-byte items, [+0x1b0/+0x1b8] shared_ptr, [+0x1d0] u32 + [+0x1d4] present byte
    uint32_t      f08;              // +0x08 (stack arg to 0x66a0f60)
    uint32_t      f0c;              // +0x0c (stack arg to 0x66a0f60)
    Vec4          m10[3];           // +0x10..+0x3f copied to local rbp+0x250
    uint64_t      f40;              // +0x40 (vec3 x,y)
    uint64_t      f48;              // +0x48 (vec3 z)
    TextureBind16 weatherTexture;   // +0x50
    TextureBind16 occlusionTexture; // +0x60
    TextureBind16 heightTexture;    // +0x70 (fallback when the OcclusionTexture slot is missing)
    int32_t       occlusionHeightOffset; // +0x80 cvtsi2ss + splat
    uint32_t      variant;          // +0x84 selects the material option table
    Vec4          fogColor;                  // +0x88
    Vec4          fogAndDistanceControl;     // +0x98
    Vec4          positionBaseOffset;        // +0xa8
    Vec4          prevPositionForwardOffset; // +0xb8
    Vec4          prevPositionBaseOffset;    // +0xc8
    Vec4          positionForwardOffset;     // +0xd8
    Vec4          viewPosition;              // +0xe8
    Vec4          uvOffsetAndScale;          // +0xf8
    Vec4          velocity;                  // +0x108
    Vec4          dimensions;                // +0x118
    uint16_t      passSortKey;               // +0x128 pushed to pass vector P+0x8a0
};
static_assert(offsetof(WeatherDescription, m10) == 0x10);
static_assert(offsetof(WeatherDescription, weatherTexture) == 0x50);
static_assert(offsetof(WeatherDescription, occlusionTexture) == 0x60);
static_assert(offsetof(WeatherDescription, heightTexture) == 0x70);
static_assert(offsetof(WeatherDescription, occlusionHeightOffset) == 0x80);
static_assert(offsetof(WeatherDescription, variant) == 0x84);
static_assert(offsetof(WeatherDescription, fogColor) == 0x88);
static_assert(offsetof(WeatherDescription, fogAndDistanceControl) == 0x98);
static_assert(offsetof(WeatherDescription, positionBaseOffset) == 0xa8);
static_assert(offsetof(WeatherDescription, prevPositionForwardOffset) == 0xb8);
static_assert(offsetof(WeatherDescription, prevPositionBaseOffset) == 0xc8);
static_assert(offsetof(WeatherDescription, positionForwardOffset) == 0xd8);
static_assert(offsetof(WeatherDescription, viewPosition) == 0xe8);
static_assert(offsetof(WeatherDescription, uvOffsetAndScale) == 0xf8);
static_assert(offsetof(WeatherDescription, velocity) == 0x108);
static_assert(offsetof(WeatherDescription, dimensions) == 0x118);
static_assert(offsetof(WeatherDescription, passSortKey) == 0x128);

// 0xc8-byte pass entry appended at P+8 (P = 0x5aba5c0(frame+0x9d0)); built at rbp+0x4f0, zero-initialised, so unnamed bytes are 0.
struct PassEntry {
    uint64_t head;          // +0x00: 0x2001001 / 0x2803001 / 0x2807021 / 0x8010000002807021 (last one written before the entry push)
    uint8_t  pad08[0x08];
    uint16_t idx8a0;        // +0x10 index into P+0x8a0 (u16 vector)
    uint8_t  pad12[0x08];
    uint16_t idx828;        // +0x1a P+0x828 (counter vector)
    uint8_t  pad1c[0x0c];
    uint16_t idx780;        // +0x28 P+0x780 (stride 0x28)
    uint16_t idx768;        // +0x2a P+0x768 (stride 0x88)
    uint16_t idx750;        // +0x2c P+0x750 (stride 0x58)
    uint8_t  pad2e[0x10];
    uint16_t idx678;        // +0x3e P+0x678 (vec3, stride 0xc)
    uint8_t  pad40[0x02];
    uint16_t idx648;        // +0x42 P+0x648 (stride 0x24)
    uint8_t  pad44[0x34];
    uint16_t idx3c0;        // +0x78 P+0x3c0 (counter vector)
    uint8_t  pad7a[0x14];
    uint16_t idx2b8;        // +0x8e P+0x2b8 (counter vector)
    uint8_t  pad90[0x38];
};
static_assert(sizeof(PassEntry) == 0xc8);
static_assert(offsetof(PassEntry, idx8a0) == 0x10);
static_assert(offsetof(PassEntry, idx828) == 0x1a);
static_assert(offsetof(PassEntry, idx780) == 0x28);
static_assert(offsetof(PassEntry, idx768) == 0x2a);
static_assert(offsetof(PassEntry, idx750) == 0x2c);
static_assert(offsetof(PassEntry, idx678) == 0x3e);
static_assert(offsetof(PassEntry, idx648) == 0x42);
static_assert(offsetof(PassEntry, idx3c0) == 0x78);
static_assert(offsetof(PassEntry, idx2b8) == 0x8e);

} // namespace bluey::weather
