#pragma once
// Effect tag 0 (FlameBillboard) description, read from extractFlameBillboard 0x673d150 (1.26.62.01).
// docs/functions/673d150.md. Offsets are the displacements the extractor reads through r8 ([V] descscan + disassembly).
#include <cstddef>
#include <cstdint>
#include "WeatherDescription.h"

namespace bluey::flame {

struct FlameDescription {
    void*    owner;                 // +0x00
    uint32_t f10;                   // +0x10
    uint8_t  pad14[0x34];
    weather::TextureBind16 flameAtlas;      // +0x48
    uint8_t  pad58a[0x00];
    weather::TextureBind16 merTexture;      // +0x58
    uint8_t  pad68[0x08];
    weather::TextureBind16 normalTexture;   // +0x70 (bound only if normalEnabled)
    uint8_t  normalEnabled;         // +0x80
    uint8_t  pad81[0x27];
    float    metalness;             // +0xa8
    float    emissive;              // +0xac
    float    roughness;             // +0xb0
    float    subsurface;            // +0xb4
    uint8_t  pbrEnabled;            // +0xb8
    uint8_t  pad_b9[3];
    uint8_t  fogOverride;           // +0xbc
    uint8_t  pad_bd[3];
    float    uvOffset[2];           // +0xc0
    weather::Vec4 fogColor;         // +0xc8
    weather::Vec4 fogAndDistanceControl; // +0xd8 (+0xe0 qword overlaps its upper half and is the override source)
    uint64_t tileLightIntensity;    // +0xe8 (movsd)
    int8_t   ditheringEnabled;      // +0xf0 (movsx)
};
static_assert(offsetof(FlameDescription, f10) == 0x10);
static_assert(offsetof(FlameDescription, flameAtlas) == 0x48);
static_assert(offsetof(FlameDescription, merTexture) == 0x58);
static_assert(offsetof(FlameDescription, normalTexture) == 0x70);
static_assert(offsetof(FlameDescription, normalEnabled) == 0x80);
static_assert(offsetof(FlameDescription, metalness) == 0xa8);
static_assert(offsetof(FlameDescription, emissive) == 0xac);
static_assert(offsetof(FlameDescription, roughness) == 0xb0);
static_assert(offsetof(FlameDescription, subsurface) == 0xb4);
static_assert(offsetof(FlameDescription, pbrEnabled) == 0xb8);
static_assert(offsetof(FlameDescription, fogOverride) == 0xbc);
static_assert(offsetof(FlameDescription, uvOffset) == 0xc0);
static_assert(offsetof(FlameDescription, fogColor) == 0xc8);
static_assert(offsetof(FlameDescription, fogAndDistanceControl) == 0xd8);
static_assert(offsetof(FlameDescription, tileLightIntensity) == 0xe8);
static_assert(offsetof(FlameDescription, ditheringEnabled) == 0xf0);

} // namespace bluey::flame
