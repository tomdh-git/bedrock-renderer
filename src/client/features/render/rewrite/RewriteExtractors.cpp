
#include "client/features/render/rewrite/RewriteExtractors.h"
#include "sdk/mc/deps/minecraft_renderer/framebuilder/BatchActorDescription.h"

// Q3b: pure reimplementations of the seven extractors in cost order. Each function reads only the
// description fields the disassembly shows it reads, at the exact offsets verified against the exe.
// All RVAs/offsets tagged [V] are from rdis disassembly (docs/progress/oc_U-EQ3b.md).
//
// CLAUDE.md style: fail fast, no null guards, no SEH. These functions read through raw pointers;
// callers must guarantee the pointers are valid (the game guarantees this at each extractor call site).

namespace bluey::render::rewrite {

// -----------------------------------------------------------------------
// BatchActor (0x66d9af0, 0x8BB7 bytes, Item tag 10)
// Reads: desc+0xE0 instance count [V static @0x66d9b79], desc+0xE8 instances ptr [V static @0x66d9c07],
// instance+0x40 model hash key [V static @0x66d9c17] fed to XXH64 (0x19932c0, x30).
// -----------------------------------------------------------------------
BatchActorRead batchActorRead(const void* desc) {
    BatchActorRead r{};
    r.instanceCount = *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(desc) + 0xE0);
    r.instances = *reinterpret_cast<const void* const*>(reinterpret_cast<const uint8_t*>(desc) + 0xE8);
    // instance[0].model at +0x40: the original computes lea rcx,[rbx+rbx*8] (stride 0x48) then
    // mov rax,[rax+rcx*8+8]; mov rsi,[rax+0x40] for the first instance.
    r.modelKey = r.instances ? *reinterpret_cast<const void* const*>(reinterpret_cast<const uint8_t*>(r.instances) + 0x40) : nullptr;
    return r;
}

// -----------------------------------------------------------------------
// ChunkGeometry (0x66ea3d0, 0xF430 bytes, Item tag 3)
// M1d chunk reads - every description-field read of the head, verified [V]:
//   +0x30 bindingCount   cmp qword ptr [rbx+0x30],2        @0x66eafd2
//   +0x38 spanCount      imul by 0x58                      @0x66ec56d
//   +0x40 spanPtr        mov rdi,[rax+0x40]               @0x66ec569
//   +0x48 passKind       **(u64**)(desc+0x48)              @0x66ea5ba region
//   +0x50 flag50         selects predicate set              @0x66ea5ba
//   +0x54 fogColor       movups xmm0,[rbx+0x54]            @0x66eb99e
//   +0x64 fogAndDistance movups xmm0,[rbx+0x64]            @0x66eb91a
//   +0x74 time           movss xmm0,[rbx+0x74]            @0x66eb6c2
//   +0xB8 low byte       movzx eax,byte ptr [r12+0xB8]    @0x66ea56e
//   +0xD8 low byte       cmp byte ptr [r12+0xD8],3         @0x66ea72e
//   +0xE0 flagE0         movzx ebx,byte ptr [r12+0xE0]    @0x66ea65c
//   +0xE1 flagE1         cmp byte ptr [r12+0xE1],0         @0x66ea76f
//   +0xE4..0xEC viewPos  movsd/movss                        @0x66eb750
// Per-frame context (ctx = rdx):
//   +0x70 mode           render mode; ==1 -> ForwardPBR     @0x66ea58b region
//   +0x74 flag74                                 @0x66ea79a
//   +0x75 flag75                                 @0x66ea66c
//   +0x30/+0x40/+0x48/+0x68 registry/material args
// -----------------------------------------------------------------------
ChunkGeometryRead chunkGeometryRead(const void* desc) {
    const uint8_t* d = reinterpret_cast<const uint8_t*>(desc);
    ChunkGeometryRead r{};
    r.bindingCount   = *reinterpret_cast<const uint64_t*>(d + 0x30);
    r.spanCount      = *reinterpret_cast<const uint64_t*>(d + 0x38);
    r.spanPtr        = *reinterpret_cast<const void* const*>(d + 0x40);
    r.passKind       = *reinterpret_cast<const uint64_t* const*>(d + 0x48);
    r.flag50         = d[0x50];
    std::memcpy(r.fogColor,        d + 0x54, 16);
    std::memcpy(r.fogAndDistance,  d + 0x64, 16);
    r.time           = *reinterpret_cast<const float*>(d + 0x74);
    r.ptrB8Low       = d[0xB8];
    r.ptrD8Low       = d[0xD8];
    r.flagE0         = d[0xE0];
    r.flagE1         = d[0xE1];
    r.viewPos[0]     = *reinterpret_cast<const float*>(d + 0xE4);
    r.viewPos[1]     = *reinterpret_cast<const float*>(d + 0xE8);
    r.viewPos[2]     = *reinterpret_cast<const float*>(d + 0xEC);
    return r;
}

ChunkCtxRead chunkCtxRead(const void* ctx) {
    const uint8_t* c = reinterpret_cast<const uint8_t*>(ctx);
    ChunkCtxRead r{};
    r.mode    = *reinterpret_cast<const uint32_t*>(c + 0x70);
    r.flag74  = c[0x74];
    r.flag75  = c[0x75];
    r.reg30   = *reinterpret_cast<const void* const*>(c + 0x30);
    r.reg40   = *reinterpret_cast<const void* const*>(c + 0x40);
    r.reg48   = *reinterpret_cast<const void* const*>(c + 0x48);
    r.p68     = *reinterpret_cast<const void* const*>(c + 0x68);
    return r;
}

// -----------------------------------------------------------------------
// Nametag (0x1127330, 0x2C6 bytes, Item tag 1)
// Description RenderNametagDescription (0x98), every field written by ctor 0x668b6e0 [V]:
//   +0x00 owner, +0x08 matrix[16], +0x48 position[3], +0x58 SharedRef {ptr,ctrl},
//   +0x68 raw[16], +0x78 ctx20, +0x80 flags(u16), +0x84 color[4], +0x94 hasColor
// -----------------------------------------------------------------------
NametagRead nametagRead(const void* desc) {
    const uint8_t* d = reinterpret_cast<const uint8_t*>(desc);
    NametagRead r{};
    r.owner     = *reinterpret_cast<const void* const*>(d + 0x00);
    r.matrix    = reinterpret_cast<const float*>(d + 0x08);
    r.position  = reinterpret_cast<const float*>(d + 0x48);
    r.sharedPtr = *reinterpret_cast<const void* const*>(d + 0x58);
    r.sharedCtrl = *reinterpret_cast<const void* const*>(d + 0x60);
    r.flags     = *reinterpret_cast<const uint16_t*>(d + 0x80);
    r.color     = reinterpret_cast<const float*>(d + 0x84);
    r.hasColor  = d[0x94] != 0;
    return r;
}

// -----------------------------------------------------------------------
// Particle (0x67417f0, 0x2CD7 bytes, Effect tag 2)
// Description RenderParticleDescription (0xB0). Reads via ParticleExtractor::DescRead:
//   +0x00 mesh, +0x08 textureHandle, +0x18 mersTexture, +0x28 mersFlag,
//   +0x30 normalTexture, +0x6C fogColor, +0x7C fogAndDistance, +0x8C blendSrc,
//   +0x8D blendDst, +0x91 flagDeferred, +0x74 flagPointLight, +0x93 blendMode,
//   +0x98 mersUniforms, +0xA8 hasMERS
// -----------------------------------------------------------------------
ParticleRead particleRead(const void* desc) {
    const uint8_t* d = reinterpret_cast<const uint8_t*>(desc);
    ParticleRead r{};
    r.mesh          = *reinterpret_cast<const void* const*>(d + 0x00);
    r.textureHandle = reinterpret_cast<const void*>(d + 0x08);
    r.mersTexture   = *reinterpret_cast<const void* const*>(d + 0x18);
    r.mersFlag      = d[0x28];
    r.normalTexture = *reinterpret_cast<const void* const*>(d + 0x30);
    std::memcpy(r.fogColor,        d + 0x6C, 16);
    std::memcpy(r.fogAndDistance,  d + 0x7C, 16);
    r.blendSrc      = d[0x8C];
    r.blendDst      = d[0x8D];
    r.flagDeferred  = d[0x91];
    r.flagPointLight = d[0x74];
    r.blendMode     = d[0x93];
    std::memcpy(r.mersUniforms, d + 0x98, 16);
    r.hasMERS       = d[0xA8];
    return r;
}

// -----------------------------------------------------------------------
// Sky (0x5369b30, 0x4B9C bytes, Sky group)
// Per-tag read views from SkyDescriptions.h. Tag selects the layout:
//   5 Sky:    +0x00 mesh, +0x08 SkyColor, +0x18 FogColor, +0x28 matrix[16], +0x68 word
//   6 Stars:  +0x00 mesh, +0x08 StarsColor, +0x18 matrix[16], +0x58 word
//   3 EndSky: +0x00 mesh, +0x1C SkyColor, +0x2C matrix[16], +0x6C UV0Transform, +0xAC minSkyLuminance
//   7 CelestialBody: +0x00 mesh, +0x18 SunMoonColor, +0x28 matrix, +0x68 word, +0x6C flags, +0x80 emissive
// -----------------------------------------------------------------------
SkyRead skyRead(const void* desc, uint8_t tag) {
    SkyRead r{};
    r.tag = tag;
    r.mesh = *reinterpret_cast<const void* const*>(desc);
    return r;
}

// -----------------------------------------------------------------------
// Clouds (0x67375a0, 0x3DFB bytes, Sky tag 1)
// Description RenderCloudsDescription (0xA8). Reads via CloudsExtractor::DescRead:
//   +0x00 matrixA[16], +0x40 matrixB[16], +0x80 mesh, +0x88 color[4],
//   +0x98 byte98, +0x9A byte9A, +0x9C value9C, +0xA0 wordA0
// -----------------------------------------------------------------------
CloudsRead cloudsRead(const void* desc) {
    const uint8_t* d = reinterpret_cast<const uint8_t*>(desc);
    CloudsRead r{};
    std::memcpy(r.matrixA, d + 0x00, 64);
    std::memcpy(r.matrixB, d + 0x40, 64);
    r.mesh     = *reinterpret_cast<const void* const*>(d + 0x80);
    std::memcpy(r.color,  d + 0x88, 16);
    r.byte98   = d[0x98];
    r.byte9A   = d[0x9A];
    r.value9C  = *reinterpret_cast<const float*>(d + 0x9C);
    r.wordA0   = *reinterpret_cast<const uint16_t*>(d + 0xA0);
    return r;
}

// -----------------------------------------------------------------------
// Weather (0x6745440, 0x3A5A bytes, Sky tag 9)
// Description bluey::weather::WeatherDescription (0x130). Reads verified [V]:
//   +0x00 mesh                    mov r15,[rsi]             @0x6745b18
//   +0x10 matrix[16]              movups                    @0x6746679..0x674668f
//   +0x80 occlusionHeightOffset   cvtsi2ss                  @0x67465c8
//   +0x84 variant                 mov edi,[r8+0x84]         @0x6745482
//   +0x88 fogColor[4]             vec4 -> FogColor
//   +0x98 fogAndDistance[4]       movups xmm0,[rsi+0x98]    @0x6746335
//   +0x128 passSortKey(u16)       movzx esi,word [rsi+0x128] @0x67466b9
// -----------------------------------------------------------------------
WeatherRead weatherRead(const void* desc) {
    const uint8_t* d = reinterpret_cast<const uint8_t*>(desc);
    WeatherRead r{};
    r.mesh = *reinterpret_cast<const void* const*>(d + 0x00);
    std::memcpy(r.matrix, d + 0x10, 64);
    r.occlusionHeightOffset = *reinterpret_cast<const int32_t*>(d + 0x80);
    r.variant = *reinterpret_cast<const uint32_t*>(d + 0x84);
    std::memcpy(r.fogColor,        d + 0x88, 16);
    std::memcpy(r.fogAndDistance,  d + 0x98, 16);
    r.passSortKey = *reinterpret_cast<const uint16_t*>(d + 0x128);
    return r;
}

// -----------------------------------------------------------------------
// DrawItems/Frame comparison (verification)
// Compares extractor-emitted 0xC8 DrawItems against Frame draw headers consumed by submit 0xe82e230.
// Frame layout [V]: sorted u16 ids at Frame+0x94700 (65536 entries ending at Frame+0xB4700), then
// 0x80-byte draw headers at Frame+0xB4700, draw count u32 at Frame+0xDC57E8.
// -----------------------------------------------------------------------
bool compareDrawHeaders(const FrameDrawHeader* actual, const FrameDrawHeader* expected, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (actual[i].uniformOffset    != expected[i].uniformOffset) return false;
        if (actual[i].state            != expected[i].state)         return false;
        if (actual[i].program          != expected[i].program)       return false;
        if (actual[i].drawBindIndex    != expected[i].drawBindIndex) return false;
        if (actual[i].startIndex       != expected[i].startIndex)    return false;
        if (actual[i].indexCount       != expected[i].indexCount)    return false;
    }
    return true;
}

uint32_t frameDrawCount(const uint8_t* frame) {
    return *reinterpret_cast<const uint32_t*>(frame + 0xDC57E8);
}

const FrameDrawHeader* frameDrawHeader(const uint8_t* frame, uint32_t index) {
    return reinterpret_cast<const FrameDrawHeader*>(frame + 0xB4700 + static_cast<size_t>(index) * 0x80);
}

} // namespace bluey::render::rewrite
