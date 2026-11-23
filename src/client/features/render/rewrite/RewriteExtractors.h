#pragma once

// Q3b: pure reimplementations of the seven extractors in cost order (BatchActor, ChunkGeometry, Nametag,
// Particle, Sky, Clouds, Weather), each reading only the description fields the disassembly shows it reads,
// at the exact offsets verified against Minecraft.Windows.exe 1.26.62.01.
//
// These are pure functions over the game's own memory: they read the description pointer and the per-frame
// context, compute what the extractor would emit (uniform bindings, material name, draw-item fields), and
// return it. They never write game memory, take no locks, and call no game functions. Each one is tagged
// with the RVAs and offsets it depends on, all [V] from rdis disassembly (docs/progress/oc_U-EQ3b.md).
//
// Cost order (rank 1 = extracted first, cheapest; rank 7 = most expensive) is the order a table-driven
// rewrite walks them. See ExtractorOrder.h for the rank table; this header holds the pure read logic.
//
// No detours, no hooks, no builds, no game run required. Register entries for each extractor are appended
// to Sigs.json (proven new entries only) and wired through RewriteRegistry when the batch build lands.


namespace bluey::render::rewrite {

// =====================================================================
// BatchActor extractor (0x66d9af0, size 0x8BB7, Item group tag 10, thin insert clone 0x4e39cb0)
// Description: bluey::batchactor::Description (BatchActorDescription.h, 0x110) + Instance (0x48)
// M1d/M2c: description fully typed; reads verified [V static] at 0x66d9b79 (+0xE0 instance count),
// 0x66d9c07 (+0xE8 instances), 0x66d9c17 (+0x40 model hash key for XXH64).
// =====================================================================

struct BatchActorRead {
    uint64_t instanceCount;      // desc +0xE0 [V static] mov rax,[r8+0xE0] @0x66d9b79
    const void* instances;       // desc +0xE8 [V static] mov rax,[rax+0xE8] @0x66d9c07
    const void* modelKey;        // instance +0x40 [V static] mov rsi,[rax+0x40] @0x66d9c17 (XXH64 key)
};

// Pure: reads the BatchActor description header + first instance's model key. Does not iterate the
// instance array (the original walks it with i*0x48 stride; iteration count = instanceCount).
static BatchActorRead batchActorRead(const void* desc);

// =====================================================================
// ChunkGeometry extractor (0x66ea3d0, size 0xF430, Item group tag 3, thin insert clone 0x15a6880)
// Description: mce::framebuilder::ChunkGeometryDescriptionView (ChunkGeometryDescription.h)
// M1d: chunk reads - every description-field read of the head, verified [V] in docs/functions/66ea3d0.md.
// =====================================================================

struct ChunkGeometryRead {
    uint64_t bindingCount;       // desc +0x30 [V] cmp qword ptr [rbx+0x30],2 @0x66eafd2
    uint64_t spanCount;          // desc +0x38 [V] read via imul by 0x58 @0x66ec56d
    const void* spanPtr;         // desc +0x40 [V] mov rdi,[rax+0x40] @0x66ec569
    const uint64_t* passKind;    // desc +0x48 [V] **(u64**)(desc+0x48) @0x66ea5ba region
    uint8_t flag50;              // desc +0x50 [V] selects predicate set @0x66ea5ba
    float fogColor[4];           // desc +0x54 [V] movups xmm0,[rbx+0x54] @0x66eb99e
    float fogAndDistance[4];     // desc +0x64 [V] movups xmm0,[rbx+0x64] @0x66eb91a
    float time;                  // desc +0x74 [V] movss xmm0,[rbx+0x74] @0x66eb6c2
    uint8_t ptrB8Low;            // desc +0xB8 low byte [V] movzx eax,byte ptr [r12+0xB8] @0x66ea56e
    uint8_t ptrD8Low;            // desc +0xD8 low byte [V] cmp byte ptr [r12+0xD8],3 @0x66ea72e
    uint8_t flagE0;              // desc +0xE0 [V] movzx ebx,byte ptr [r12+0xE0] @0x66ea65c
    uint8_t flagE1;              // desc +0xE1 [V] cmp byte ptr [r12+0xE1],0 @0x66ea76f
    float viewPos[3];            // desc +0xE4..+0xEC [V] movsd/movss @0x66eb750
};

// Pure: reads every ChunkGeometry description field the extractor head touches.
static ChunkGeometryRead chunkGeometryRead(const void* desc);

// Per-frame context fields read by the ChunkGeometry head (ctx = rdx, kept at [rbp+0x16a8]):
struct ChunkCtxRead {
    uint32_t mode;               // ctx +0x70 [V] render mode; ==1 selects ForwardPBR family
    uint8_t flag74;              // ctx +0x74 [V]
    uint8_t flag75;              // ctx +0x75 [V]
    const void* reg30;           // ctx +0x30 [V] registry object #2
    const void* reg40;           // ctx +0x40 [V] registry object #3 / material cache arg
    const void* reg48;           // ctx +0x48 [V] registry object #1
    const void* p68;             // ctx +0x68 [V] material resolver arg rcx for 0x675e440
};

// Pure: reads the per-frame context fields the ChunkGeometry extractor reads.
static ChunkCtxRead chunkCtxRead(const void* ctx);

// =====================================================================
// Nametag extractor (0x1127330, size 0x2C6, Item group tag 1, fat clone)
// Description: mce::framebuilder::RenderNametagDescription (0x98)
// =====================================================================

struct NametagRead {
    const void* owner;           // desc +0x00 [V]
    const float* matrix;         // desc +0x08 [V] 16 floats
    const float* position;       // desc +0x48 [V] 3 floats
    const void* sharedPtr;       // desc +0x58 [V] SharedRef mPtr
    const void* sharedCtrl;      // desc +0x58+8 [V] SharedRef mCtrl
    uint16_t flags;              // desc +0x80 [V]
    const float* color;          // desc +0x84 [V] 4 floats, conditional on mHasColor
    bool hasColor;               // desc +0x94 [V]
};

// Pure: reads the Nametag description fields.
static NametagRead nametagRead(const void* desc);

// =====================================================================
// Particle extractor (0x67417f0, size 0x2CD7, Effect group tag 2, thin insert clone 0x5b8d520)
// Description: mce::framebuilder::RenderParticleDescription (0xB0)
// ParticleSkyExtractors.h: ParticleExtractor::DescRead
// =====================================================================

struct ParticleRead {
    const void* mesh;            // desc +0x00 [V]
    const void* textureHandle;   // desc +0x08 [V] 16-byte handle to 0xbcaba00
    const void* mersTexture;     // desc +0x18 [V] pointer
    uint8_t mersFlag;            // desc +0x28 [V] byte == 1 -> PBRTextureFlags bit pattern 3
    const void* normalTexture;   // desc +0x30 [V] pointer
    float fogColor[4];           // desc +0x6C [V] vec4 -> uniform FogColor
    float fogAndDistance[4];     // desc +0x7C [V] vec4 -> uniform FogAndDistanceControl
    uint8_t blendSrc;            // desc +0x8C [V] u8 preset table key (a)
    uint8_t blendDst;            // desc +0x8D [V] u8 preset table key (b)
    uint8_t flagDeferred;        // desc +0x91 [V] ANDed with (frame mode == 1)
    uint8_t flagPointLight;      // desc +0x74 [V] with deferred -> PointLightShading=On
    uint8_t blendMode;           // desc +0x93 [V] 1->2, 2->1, else 0
    float mersUniforms[4];       // desc +0x98 [V] vec4 used when +0xA8 == 1
    uint8_t hasMERS;             // desc +0xA8 [V]
};

// Pure: reads the Particle description fields.
static ParticleRead particleRead(const void* desc);

// =====================================================================
// Sky extractor (0x5369b30, size 0x4B9C, Sky group; tags 1 Clouds, 2 Cubemap, 3 EndSky, 4 LegacyCubemap,
// 5 Sky/Stars, 6 Stars, 7 CelestialBody, 8 VolumetricFog, 9 Weather, 10 SkyAmbientSamples)
// Description: per-tag read views in SkyDescriptions.h
// =====================================================================

struct SkyRead {
    uint8_t tag;                 // variant tag selecting the description layout
    const void* mesh;            // tag-dependent +0x00 [V]
    // Tag 5 (Sky): +0x08 SkyColor, +0x18 FogColor, +0x28 matrix[16], +0x68 word
    // Tag 6 (Stars): +0x08 StarsColor, +0x18 matrix[16], +0x58 word
    // Tag 3 (EndSky): +0x1C SkyColor, +0x2C matrix[16], +0x6C UV0Transform, +0xAC minSkyLuminance
    // Tag 7 (CelestialBody): +0x18 SunMoonColor, +0x28 matrix, +0x68 word, +0x6C flags, +0x80 emissive
};

// Pure: reads the Sky description fields for the given tag.
static SkyRead skyRead(const void* desc, uint8_t tag);

// =====================================================================
// Clouds extractor (0x67375a0, size 0x3DFB, Sky group tag 1, thin insert clone 0x53e88a0)
// Description: mce::framebuilder::RenderCloudsDescription (0xA8)
// ParticleSkyExtractors.h: CloudsExtractor::DescRead
// =====================================================================

struct CloudsRead {
    float matrixA[16];           // desc +0x00 [V] 0x40 bytes instance transform
    float matrixB[16];           // desc +0x40 [V] address only, extent [I]
    const void* mesh;            // desc +0x80 [V] mov r14,[rbx+0x80] @0x6737880
    float color[4];              // desc +0x88 [V] movups xmm0,[rbx+0x88] @0x6737943
    uint8_t byte98;              // desc +0x98 [V] movzx eax,byte [rbx+0x98] @0x6737b1a
    uint8_t byte9A;              // desc +0x9A [V] movzx eax,byte [rbx+0x9A] @0x6737aaa
    float value9C;               // desc +0x9C [V] movss xmm0,[rbx+0x9C] @0x67379f7
    uint16_t wordA0;             // desc +0xA0 [V] movzx edi,word [rbx+0xA0] @0x6737dd8
};

// Pure: reads the Clouds description fields.
static CloudsRead cloudsRead(const void* desc);

// =====================================================================
// Weather extractor (0x6745440, size 0x3A5A, Sky group tag 9, thin insert clone 0x5ad5800)
// Description: bluey::weather::WeatherDescription (WeatherDescription.h, 0x130)
// =====================================================================

struct WeatherRead {
    const void* mesh;            // desc +0x00 [V] mov r15,[rsi] @0x6745b18
    float matrix[16];            // desc +0x10 [V] movups @0x6746679..0x674668f
    int32_t occlusionHeightOffset; // desc +0x80 [V] cvtsi2ss @0x67465c8
    uint32_t variant;            // desc +0x84 [V] mov edi,[r8+0x84] @0x6745482
    float fogColor[4];           // desc +0x88 [V] vec4 -> FogColor
    float fogAndDistance[4];     // desc +0x98 [V] movups xmm0,[rsi+0x98] @0x6746335
    uint16_t passSortKey;        // desc +0x128 [V] movzx esi,word [rsi+0x128] @0x67466b9
};

// Pure: reads the Weather description fields.
static WeatherRead weatherRead(const void* desc);

// =====================================================================
// DrawItems/Frame comparison (verification)
// Compares extractor-emitted 0xC8 DrawItems against Frame draw headers consumed by submit 0xe82e230.
// Frame layout [V]: sorted u16 ids at Frame+0x94700 (65536 entries ending at Frame+0xB4700), then
// 0x80-byte draw headers at Frame+0xB4700, draw count u32 at Frame+0xDC57E8.
// =====================================================================

struct FrameDrawHeader {
    uint32_t uniformOffset;      // +0x00
    uint32_t state;              // +0x20 u32 0x27
    uint32_t program;            // +0x38 u32
    uint32_t drawBindIndex;      // +0x3C counting up per draw
    uint32_t startIndex;         // +0x40
    uint32_t indexCount;         // +0x44
};

// Pure: compares the N draw headers at frameDrawHeaders against expected values. Returns true on match.
static bool compareDrawHeaders(const FrameDrawHeader* actual, const FrameDrawHeader* expected, size_t count);

// Pure: reads the draw count from Frame+0xDC57E8.
static uint32_t frameDrawCount(const uint8_t* frame);

// Pure: returns pointer to draw header N at Frame+0xB4700 + N*0x80.
static const FrameDrawHeader* frameDrawHeader(const uint8_t* frame, uint32_t index);

} // namespace bluey::render::rewrite
