#pragma once
// Constants and small structs reversed from the Particle extractor 0x67417f0 (docs/functions/67417f0.md, phases P1..P13)
// and the Clouds extractor 0x67375a0. Self-contained: does not touch Descriptions.h / FrameBuilder.h.

namespace ParticleExtractor {

// Key record built by 0x5668ac0 (name -> 16-byte key); hashed bytewise over +8..+0xF by the material cache lookup (same code as 0x567d280).
struct Key16 {
    uint64_t a;
    uint64_t b;
};
static_assert(sizeof(Key16) == 0x10);

// Reads of the Particle description inside 0x67417f0 (offsets are displacements in the extractor; r8 is the description).
namespace DescRead {
constexpr size_t kMesh = 0x00;          // [r8] -> Mesh::hasDrawableData 0x4def080, vertex blob etc.
constexpr size_t kTextureHandle = 0x08; // 16-byte handle passed to 0xbcaba00 as the "ParticleTexture" texture
constexpr size_t kTextureMERS = 0x18;   // pointer; word at +0x10 is lock-incremented, byte +0x12 bit0 = usable
constexpr size_t kMERSFlag = 0x28;      // byte == 1 -> PBRTextureFlags bit pattern 3 instead of 1
constexpr size_t kTextureNormal = 0x30; // pointer, same shape as +0x18 (NormalTexture, flag bit 4)
constexpr size_t kFogColor = 0x6C;      // vec4 -> uniform FogColor
constexpr size_t kFogAndDistance = 0x7C; // vec4 -> uniform FogAndDistanceControl
constexpr size_t kBlendSrc = 0x8C;      // u8, preset table key (a)
constexpr size_t kBlendDst = 0x8D;      // u8, preset table key (b)
constexpr size_t kFlagDeferred = 0x91;  // u8: ANDed with (frame mode == 1) -> ParticleForwardPBR else ParticlePrepass
constexpr size_t kFlagPointLight = 0x74; // u8: with deferred -> defines {PointLightShading=On}
constexpr size_t kBlendMode = 0x93;     // u8: 1 -> 2, 2 -> 1, else 0 (DrawState +0x658)
constexpr size_t kMERSUniforms = 0x98;  // vec4 used when +0xA8 == 1, else frame-builder default
constexpr size_t kHasMERS = 0xA8;
} // namespace DescRead

// Frame-context (F) fields read by the extractor.
namespace FrameRead {
constexpr size_t kRenderer = 0x10;   // renderer; +0x9C8 named-transaction flag, +0x788 transaction list, +0x9D0 draw list
constexpr size_t kMode = 0x70;       // int; 1 selects the deferred/PBR family
constexpr size_t kMatCache = 0x68;   // MatCache*: recursive mutex +0x98, count +0xE4, map +0x40
} // namespace FrameRead

// Blend preset table (frame d+0x8C, d+0x8D) -> DrawState preset index, from the cmp chain at 0x6743400..0x6743497.
constexpr int blendPreset(uint8_t a, uint8_t b) {
    if (a == 3 && b == 2) return 1;
    if (a == 6 && b == 8) return 3;
    if (a == 3 && b == 8) return 4;
    if (a == 4 && b == 5) return 5;
    if (a == 3 && b == 3) return 6;
    if (a == 6 && b == 3) return 7;
    if (a == 0 && b == 2) return 8;
    if (a == 0 && b == 1) return 9;
    return 0;
}
static_assert(blendPreset(3, 2) == 1 && blendPreset(0, 1) == 9 && blendPreset(1, 1) == 0);

// Index count for the particle quad list (0x6742c94..0x6742cb3): kind 0 -> 6 per quad, kind 1 -> same, else 0.
constexpr uint32_t indexCount(int kind, uint32_t vertexCount) {
    return kind == 1 ? vertexCount : kind == 0 ? ((vertexCount >> 1) & ~1u) * 3 : 0;
}
static_assert(indexCount(0, 8) == 12 && indexCount(1, 8) == 8 && indexCount(2, 8) == 0);

// Material name chosen by 0x67418d1..0x6741b76.
constexpr const char* materialName(int mode, bool flag91) {
    return mode != 1 ? "Particle" : flag91 ? "ParticleForwardPBR" : "ParticlePrepass";
}
static_assert(materialName(0, true)[8] == '\0' && materialName(1, true)[8] == 'F' && materialName(1, false)[8] == 'P');

} // namespace ParticleExtractor

namespace CloudsExtractor {
// Reads of the Clouds description inside 0x67375a0 (r8 is the description).
namespace DescRead {
constexpr size_t kMatrix = 0x00;       // 0x40 bytes copied as the instance transform (3 vec4 + floats +0x30/+0x34 + double +0x38)
constexpr size_t kFloat34 = 0x34;      // xmm6, written to DrawState +0x230
constexpr size_t kPrevWorld = 0x40;    // matrix -> uniform PrevWorld (mode 1 only), via 0x56d55e0
constexpr size_t kMesh = 0x80;         // Mesh*: +0x1b0/+0x1b8 buffer pair, +0x1d0/+0x1d4 instance count, +0x58/+0x60 12-byte items
constexpr size_t kCloudColor = 0x88;   // vec4 -> CloudColor
constexpr size_t kByte98 = 0x98;       // mode != 1: cull state = v*3, flag = v^1
constexpr size_t kByte99 = 0x99;       // ==1 enables draw block D when F+0x75 != 1
constexpr size_t kByte9A = 0x9A;       // mode 1: cull state = 2 - v
constexpr size_t kDistance = 0x9C;     // float -> DistanceControl.x
constexpr size_t kFlags = 0xA0;        // u16 pushed to pass pool Q+0x8a0
} // namespace DescRead
namespace FrameRead {
constexpr size_t kMode = 0x70;         // int, 1 = deferred/PBR (CloudsForwardPBR)
constexpr size_t kFlag75 = 0x75;       // byte, 1 = per-mesh object path (0x6693850)
constexpr size_t kMatCache = 0x68;
} // namespace FrameRead
// Pass-queue pool offsets (Q = 0x5aba5c0(F->+0x10 + 0x9d0)) and the record words they patch in the 0xC8-byte draw record.
namespace Pass {
constexpr size_t kRecords = 0x008;     // vector of 0xC8-byte records
constexpr size_t kPool780 = 0x780;     // 0x58-byte elements -> record +0x28
constexpr size_t kPool8A0 = 0x8A0;     // u16 values -> record +0x10
constexpr size_t kPool648 = 0x648;     // 0x48-byte elements -> record +0x42
constexpr size_t kPool768 = 0x768;     // 0x88-byte elements -> record +0x2A
constexpr size_t kPool678 = 0x678;     // 12-byte elements -> record +0x3E
constexpr size_t kPool750 = 0x750;     // 0x58-byte elements -> record +0x2C
constexpr size_t kPool828 = 0x828;     // 1-byte counters -> record +0x1A
constexpr size_t kPool6D8 = 0x6D8;     // 1-byte counters -> record +0x36
constexpr size_t kPool480 = 0x480;     // byte vector -> record +0x48 (block B)
constexpr size_t kRecordSize = 0xC8;
} // namespace Pass
static_assert(Pass::kRecordSize == 200 && DescRead::kMesh == 0x80);
} // namespace CloudsExtractor
