#pragma once

// Effect-group descriptions (1.26.62.01; Effect visitor 0x666aca0, jump table 0xF2BF49C: 0 FlameBillboard, 1 BlitFlipbook, 2 Particle, 3 PlayerVision, 4 Shadow,
// 5 FadeToBlack, 6 AimAssistHighlight, 7 FullscreenEffect, 8 EditorHighlight) plus VolumetricFog (Sky tag 8, visitor view is SkyDescriptions.h). Source:
// docs/functions/effect_descriptions.md (listings docs/data/listings/effect_*.txt; every quoted instruction re-run with rdis, tools/sigs/verify_oc.py).
// Layouts here come from the PRODUCER side (the description constructors / the clones' stores) and are cross-checked against the reads of the consumers. A member
// exists only at an offset that a listing stores or reads; gaps are explicit pad members with NO meaning. Where a member is only stored (never read by the
// consumers decoded so far) the comment says "stored only". Descriptions.h keeps the older RenderXxxDescription types (several of its field NAMES are [I]); the
// corrections found here are listed in the md (section 9).


namespace mce::framebuilder::effectvis {

// std::shared_ptr style pair as the constructors copy it: {object, control block}; ctrl != 0 => `lock inc dword [ctrl+8]` (use count).
struct SharedRefPair {
    void* mObject;
    void* mCtrl;
};
static_assert(sizeof(SharedRefPair) == 0x10);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------
// Particle (Effect tag 2). Visitor case 0x666ad88 tail-jumps to extractor 0x67417F0 (rcx, rdx = frame ctx, r8 = &variant -> description). Thin clone 0x5B8D520
// stores the description pointer + tag byte 2 (0x5b8d590/0x5b8d594) and inserts through vslot 0x360. Both producers (0x5B8C2B0 @0x5b8cfac, 0x6B550B0 @0x6b57290) build
// it with the constructor 0x668C220 (all stores below are its stores).
struct ParticleDescriptionLayout {
    void* mMesh;                     // +0x00 [rcx]=rdx (0x668c225); extractor: Mesh::hasDrawableData(0x4DEF080) on [desc] (0x6741822), nothing drawn when false
    SharedRefPair mParticleTexture;  // +0x08 (0x668c23f..0x668c247); extractor passes &desc+8 to the ParticleTexture bind (0x6742f74)
    SharedRefPair mMersTexture;      // +0x18 (0x668c24b..0x668c268); extractor reads the object at 0x6742fc2 (null => no MERS bind)
    uint8_t mMersFlag;               // +0x28 byte (0x668c271); extractor cmp byte [desc+0x28],1 (0x6743061): PBRTextureFlags bit pattern 3 instead of 1
    uint8_t mPad29[7];
    SharedRefPair mNormalTexture;    // +0x30 (0x668c27c..0x668c291); extractor reads the object at 0x6743077
    uint8_t mByte40;                 // +0x40 stored only (0x668c29a)
    uint8_t mPad41[7];
    SharedRefPair mRef48;            // +0x48 stored only (0x668c2cc, 0x668c2d4)
    SharedRefPair mRef58;            // +0x58 stored only (0x668c2ed, 0x668c2f5)
    uint32_t mDword68;               // +0x68 stored only (r9d, 0x668c2f9)
    float mFogColor[4];              // +0x6C four floats from [[holder+0x70]+0x40] (0x668c305..0x668c32b); extractor movups (0x6742dc9) -> uniform FogColor
    float mFogAndDistance[4];        // +0x7C floats from the +0x78/+0x80/+0x88 holders (0x668c338..0x668c378); extractor movups (0x6742e90) -> FogAndDistanceControl
    uint8_t mFlags8C[7];             // +0x8C..+0x92 7 bytes copied as two dwords from a stack-arg pointer (0x668c380..0x668c38e); read: +0x8C 0x6743400, +0x8D 0x6743408, +0x91 0x67418e1
    uint8_t mMode93;                 // +0x93 (0x668c395); extractor movzx (0x67433c9): 1 -> 2, 2 -> 1, else 0
    uint16_t mFlags94;               // +0x94 (0x668c39c); read by the DrawArgs assembler 0x67450A0 (mov r14w,[rcx+0x94] 0x6745102) -> DrawArgs.flags
    uint8_t mPad96[2];
    float mMersUniforms[4];          // +0x98 16 bytes (0x668c3a3/0x668c3a6); extractor movups (0x674311e) only when +0xA8 == 1 -> MERSUniforms
    uint32_t mDwordA8;               // +0xA8 dword (0x668c3b0); extractor cmp byte [desc+0xA8],1 (0x6743115)
    uint8_t mPadAC[4];
};
static_assert(offsetof(ParticleDescriptionLayout, mParticleTexture) == 0x08);
static_assert(offsetof(ParticleDescriptionLayout, mMersTexture) == 0x18);
static_assert(offsetof(ParticleDescriptionLayout, mMersFlag) == 0x28);
static_assert(offsetof(ParticleDescriptionLayout, mNormalTexture) == 0x30);
static_assert(offsetof(ParticleDescriptionLayout, mByte40) == 0x40);
static_assert(offsetof(ParticleDescriptionLayout, mRef48) == 0x48);
static_assert(offsetof(ParticleDescriptionLayout, mRef58) == 0x58);
static_assert(offsetof(ParticleDescriptionLayout, mDword68) == 0x68);
static_assert(offsetof(ParticleDescriptionLayout, mFogColor) == 0x6C);
static_assert(offsetof(ParticleDescriptionLayout, mFogAndDistance) == 0x7C);
static_assert(offsetof(ParticleDescriptionLayout, mFlags8C) == 0x8C);
static_assert(offsetof(ParticleDescriptionLayout, mMode93) == 0x93);
static_assert(offsetof(ParticleDescriptionLayout, mFlags94) == 0x94);
static_assert(offsetof(ParticleDescriptionLayout, mMersUniforms) == 0x98);
static_assert(offsetof(ParticleDescriptionLayout, mDwordA8) == 0xA8);
static_assert(sizeof(ParticleDescriptionLayout) == 0xB0);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------
// FlameBillboard (Effect tag 0). Visitor case 0x666ad04 tail-jumps to extractor 0x673D150. Fat clone 0x594CBE0 (the ActorRenderDispatcher::render post step) builds
// it with the constructor 0x668B160 (call 0x594eaa9) and inserts it with tag byte 0 (0x594eb1f) through vslot 0x360 (0x594eb29). Size 0xF8 is the aligned end
// (the last store is the word at +0xF2) [I].
struct FlameBillboardDescriptionLayout {
    void* mMesh;                     // +0x00 [rcx]=rdx (0x668b166); the extractor and the record helper 0x67411B0 read it
    float mMatrix08[16];             // +0x08..+0x47 sixteen movss from a 0x40-byte block (0x668b16e..0x668b213); read by 0x67411B0 as four movups (0x67411e8..0x6741204)
    SharedRefPair mFlameAtlas;       // +0x48 (0x668b22f, 0x668b237); extractor texture bind FlameAtlas (0x673d741)
    SharedRefPair mMersTexture;      // +0x58 (0x668b250, 0x668b258); MERSTexture bind (0x673d652)
    uint8_t mByte68;                 // +0x68 stored only (0x668b261)
    uint8_t mPad69[7];
    SharedRefPair mNormalTexture;    // +0x70 (0x668b279, 0x668b281); NormalTexture bind (0x673d828)
    uint8_t mNormalEnabled;          // +0x80 (0x668b28a); extractor cmp byte [desc+0x80] (0x673d871): bound only when != 0
    uint8_t mPad81[7];
    SharedRefPair mRef88;            // +0x88 stored only (0x668b2cb, 0x668b2d6)
    SharedRefPair mRef98;            // +0x98 stored only (0x668b2f5, 0x668b300)
    float mPbr[4];                   // +0xA8 Metalness/Emissive/Roughness/Subsurface: one 16-byte copy (0x668b307/0x668b30a); extractor movups at +0xA8/+0xAC/+0xB0/+0xB4
    uint32_t mDwordB8;               // +0xB8 dword (0x668b311); extractor cmp byte [desc+0xB8],1 (0x673dbc9) gates the PBR uniforms
    uint8_t mFogOverrideBC;          // +0xBC byte (0x668b31c); extractor cmp (0x673d456): 1 -> fog vec = {const, [+0xE0]}
    uint8_t mPadBD[3];
    float mUvOffset[2];              // +0xC0 (0x668b322..0x668b335); extractor movsd (0x673da07) -> UVOffset
    float mFogColor[4];              // +0xC8 four floats from [[holder+0x70]+0x40] (0x668b345..0x668b374); extractor movups (0x673d5ad) -> FogColor
    float mFogAndDistance[4];        // +0xD8 floats from the +0x78/+0x80/+0x88 holders (0x668b384..0x668b3c7); extractor movups (0x673d4e2), movsd +0xE0 (0x673d46f)
    float mTileLightIntensity[2];    // +0xE8 (0x668b3cf..0x668b3e2); extractor movsd (0x673e276) -> TileLightIntensity
    uint8_t mDithering;              // +0xF0 (0x668b3ea); extractor movsx (0x673e320) -> DitheringEnabledToggle
    uint8_t mPadF1;
    uint16_t mWordF2;                // +0xF2 (0x668b3f0); read by the record helper (movzx word [rax+0xF2] 0x6741210) -> record word
    uint8_t mPadF4[4];
};
static_assert(offsetof(FlameBillboardDescriptionLayout, mMatrix08) == 0x08);
static_assert(offsetof(FlameBillboardDescriptionLayout, mFlameAtlas) == 0x48);
static_assert(offsetof(FlameBillboardDescriptionLayout, mMersTexture) == 0x58);
static_assert(offsetof(FlameBillboardDescriptionLayout, mByte68) == 0x68);
static_assert(offsetof(FlameBillboardDescriptionLayout, mNormalTexture) == 0x70);
static_assert(offsetof(FlameBillboardDescriptionLayout, mNormalEnabled) == 0x80);
static_assert(offsetof(FlameBillboardDescriptionLayout, mRef88) == 0x88);
static_assert(offsetof(FlameBillboardDescriptionLayout, mRef98) == 0x98);
static_assert(offsetof(FlameBillboardDescriptionLayout, mPbr) == 0xA8);
static_assert(offsetof(FlameBillboardDescriptionLayout, mDwordB8) == 0xB8);
static_assert(offsetof(FlameBillboardDescriptionLayout, mFogOverrideBC) == 0xBC);
static_assert(offsetof(FlameBillboardDescriptionLayout, mUvOffset) == 0xC0);
static_assert(offsetof(FlameBillboardDescriptionLayout, mFogColor) == 0xC8);
static_assert(offsetof(FlameBillboardDescriptionLayout, mFogAndDistance) == 0xD8);
static_assert(offsetof(FlameBillboardDescriptionLayout, mTileLightIntensity) == 0xE8);
static_assert(offsetof(FlameBillboardDescriptionLayout, mDithering) == 0xF0);
static_assert(offsetof(FlameBillboardDescriptionLayout, mWordF2) == 0xF2);
static_assert(sizeof(FlameBillboardDescriptionLayout) == 0xF8);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------
// PlayerVision (Effect tag 3). Producer: fat clone 0x53E62B0 stores the five fields at [rbp+0x44..0x54] (0x53e6676..0x53e668a), variant {&desc, tag 3}
// (0x53e66f8/0x53e66fc), vslot 0x360 (0x53e6703). Visitor case 0x666adbf copies the whole description (byte +0x00, 16 bytes +0x04) into a 0x14-byte element
// of the pass vector pass+0x330/0x338/0x340 (0x666ae5e/0x666ae61), then appends one 0xC8 record whose qword +0x00 = 0x0400000000000000 and word +0x84 = element index.
struct PlayerVisionDescriptionLayout {
    uint8_t mVisionEffect;           // +0x00 r12b: night vision (id 0x10) or conduit power (id 0x1A) present (0x53e6432..0x53e6465); stored 0x53e6676
    uint8_t mPad01[3];
    float mVisionScale;              // +0x04 xmm0 (0x53e667a)
    float mPlayerValue;              // +0x08 [player+0x4D4] (0x53e6552, stored 0x53e667f)
    float mBlockLight;               // +0x0C (float)byte(block brightness) * 0.0625 (0x53e664b/0x53e6665, const 0xF0A3FD0 = 0.0625), stored 0x53e6685
    float mPulse;                    // +0x10 max(0, k * dim * 0.45) (0x53e666d/0x53e6671, 0xF215E90 = 0.45), stored 0x53e668a
};
static_assert(offsetof(PlayerVisionDescriptionLayout, mVisionScale) == 0x04);
static_assert(offsetof(PlayerVisionDescriptionLayout, mPlayerValue) == 0x08);
static_assert(offsetof(PlayerVisionDescriptionLayout, mBlockLight) == 0x0C);
static_assert(offsetof(PlayerVisionDescriptionLayout, mPulse) == 0x10);
static_assert(sizeof(PlayerVisionDescriptionLayout) == 0x14);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------
// Shadow (Effect tag 4). Producer: fat clone 0x53E6C30, stores at 0x53e7353 (+0x00), 0x53e735a (+0x08), 0x53e7368 (+0x10), 0x53e737a (+0x18), tag byte 4
// (0x53e73ef), vslot 0x360 (0x53e73f6). Visitor case 0x666ad3b checks [[desc]+0x28/+0x38/+0x48] != 0, then calls extractor 0x66A9D50 (frame ctx +0x70 == 1,
// material "SimpleOccluder") or 0x66A6830 (other modes: "ShadowVolume", "ShadowOverlay", "SimpleOccluder"), arguments (ctx, desc.source, desc, desc.entry, desc.local).
struct ShadowDescriptionLayout {
    void* mSource;                   // +0x00 = renderer-object + 0x5E0 (0x53e7311, 0x53e7353): a shadow-renderer record, see ShadowSourceReads
    const float* mEntryMatrix;       // +0x08 pointer to a 0x40-byte matrix = the newest element of a ring buffer (0x53e7318..0x53e733f, 0x53e735a); the extractors multiply it via 0xAA6580
    const float* mLocalVec3;         // +0x10 pointer to a producer-local {x,y,z} = [renderer+0xC..0x17] (0x53e6c80..0x53e6c94), extractors: movsd [p], movss [p+8]
    uint16_t mFlags;                 // +0x18 byte [[clone arg+8]+0x74] widened (0x53e736f..0x53e737a); extractors: mov si,[r12+0x18] (0x66aa452, 0x66a7099) -> record word
    uint8_t mPad1A[6];
};
static_assert(offsetof(ShadowDescriptionLayout, mEntryMatrix) == 0x08);
static_assert(offsetof(ShadowDescriptionLayout, mLocalVec3) == 0x10);
static_assert(offsetof(ShadowDescriptionLayout, mFlags) == 0x18);
static_assert(sizeof(ShadowDescriptionLayout) == 0x20);

// What the two extractors read through desc.mSource (rbx in 0x66A9D50; [rbp+0x580] in 0x66A6830). Read-view: size stops at the last read.
struct ShadowSourceReads {
    uint8_t mPad00[0x10];
    const uint8_t* mCasterBegin;     // +0x10 0x66aa13f (main), 0x66a6b9d / 0x66a6bee (alt): vector begin of 0x14-byte ShadowCasterElement
    const uint8_t* mCasterEnd;       // +0x18 0x66aa143 / 0x66a6ba1
    uint8_t mPad20[8];
    void* mMesh28;                   // +0x28 alt only: mov r12,[rax+0x28] (0x66a7001), then [r12+0x58]/[r12+0x60] item range (0x66a7005/0x66a700a)
    uint8_t mPad30[8];
    void* mObject38;                 // +0x38 alt only: mov r13,[rax+0x38] (0x66a78ef)
    uint8_t mPad40[8];
    void* mMesh48;                   // +0x48 main only: mov rsi,[rbx+0x48] (0x66a9ff9), Mesh::hasDrawableData (0x4DEF080) and 0x4DEF2B0
    uint8_t mPad50[0x20];
    float mVec70[4];                 // +0x70 alt only: movups xmm0,[rax+0x70] (0x66a7a0d)
};
static_assert(offsetof(ShadowSourceReads, mCasterBegin) == 0x10);
static_assert(offsetof(ShadowSourceReads, mCasterEnd) == 0x18);
static_assert(offsetof(ShadowSourceReads, mMesh28) == 0x28);
static_assert(offsetof(ShadowSourceReads, mObject38) == 0x38);
static_assert(offsetof(ShadowSourceReads, mMesh48) == 0x48);
static_assert(offsetof(ShadowSourceReads, mVec70) == 0x70);

// One caster element (stride 0x14): producer reads +4/+8/+0xC/+0x10 (0x53e6e5b..0x53e6e9f), main extractor movsd +4, movss +0xC, movss +0x10 (0x66aa307, 0x66aa302, 0x66aa2eb).
struct ShadowCasterElement {
    uint32_t mUnread00;              // +0x00 not read by either consumer
    float mPos[3];                   // +0x04 (+0x08 read as the second float of the movsd/movss pair and by the producer)
    float mScale;                    // +0x10
};
static_assert(offsetof(ShadowCasterElement, mPos) == 0x04);
static_assert(offsetof(ShadowCasterElement, mScale) == 0x10);
static_assert(sizeof(ShadowCasterElement) == 0x14);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------
// VolumetricFog (Sky tag 8): producer-side view of the 0x59 bytes the clone 0x53E3AA0 writes at [rbp+0x90..0xE8] (stores 0x53e4921..0x53e49b9); the visitor view is
// SkyDescriptionReads.h/VolumetricFogDescriptionReads in SkyDescriptions.h. NOTE: nothing is written at +0x5C..+0xDF (those rbp slots are other locals), so the
// older RenderVolumetricFogDescription::mUnreadTail5C in Descriptions.h is NOT part of the description; the variant {&desc, tag 8} sits at [rbp+0x170] (0x53e4a2f/0x53e4a36).
struct VolumetricFogProducerLayout {
    uint16_t mFlags;                 // +0x00 byte [[clone arg+0x10]+0x74] zero-extended (0x53e491c, 0x53e4921)
    uint8_t mPad02[2];
    float mV04[2];                   // +0x04 movsd [source+0x45C] (0x53e4928/0x53e4932)
    float mF0C;                      // +0x0C [source+0x464] (0x53e493a/0x53e4944)
    float mV10[4];                   // +0x10 [source+0x468] (0x53e494c/0x53e4955)
    float mV20[4];                   // +0x20 [source+0x478] (0x53e495c/0x53e4965)
    float mF30;                      // +0x30 [source+0x4C8] (0x53e496c/0x53e4976)
    float mV34[4];                   // +0x34 [source+0x488] (0x53e497e/0x53e4987)
    float mV44[4];                   // +0x44 [source+0x498] (0x53e498e/0x53e4997)
    float mF54;                      // +0x54 [source+0x4CC] (0x53e499e/0x53e49a8)
    uint8_t mB58;                    // +0x58 byte [source+0x968] (0x53e49b0/0x53e49b9); the visitor's qword read at +0x54 spans +0x54..+0x5B
    uint8_t mPad59[3];
};
static_assert(offsetof(VolumetricFogProducerLayout, mV04) == 0x04);
static_assert(offsetof(VolumetricFogProducerLayout, mF0C) == 0x0C);
static_assert(offsetof(VolumetricFogProducerLayout, mV10) == 0x10);
static_assert(offsetof(VolumetricFogProducerLayout, mV20) == 0x20);
static_assert(offsetof(VolumetricFogProducerLayout, mF30) == 0x30);
static_assert(offsetof(VolumetricFogProducerLayout, mV34) == 0x34);
static_assert(offsetof(VolumetricFogProducerLayout, mV44) == 0x44);
static_assert(offsetof(VolumetricFogProducerLayout, mF54) == 0x54);
static_assert(offsetof(VolumetricFogProducerLayout, mB58) == 0x58);
static_assert(sizeof(VolumetricFogProducerLayout) == 0x5C);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------
// BlitFlipbookTexture (Effect tag 1). Visitor case 0x666aec2 (material "Flipbook") -> shared tail 0x666b672, element loop 0x666b704..0x666c846. Thin clone
// 0x5ACBE20 (tag byte 1 at 0x5acbe94, vslot 0x360). Producer 0x5ACA680 builds the description at [rbp+0x30] (SharedRef via 0x4DFB570 @0x5acb24f, span {count, data}
// via 0x5ACBFE0 @0x5acb242 stored at +0x10/+0x18 @0x5acb25a, insert call @0x5acb267). Each element is written by 0x6BF7260 and copied by 0x5ACB9C0.
struct BlitFlipbookElementLayout {
    void* mObject;                   // +0x00 [rsi]=r12 (0x6bf73ad): handle used as the mesh after the setup helpers (visitor 0x666b942)
    SharedRefPair mTexture;          // +0x08 (0x6bf73b0/0x6bf73b8 via 0x4DFB570); visitor passes &elem+8 to 0xBCABA00 (0x666b858)
    float mFrameU;                   // +0x18 movss (0x6bf73ec); visitor movsd [r14+0x18] covers +0x18/+0x1C (0x666b897)
    float mFrameV;                   // +0x1C movss (0x6bf73f1)
    float mFrameLerp;                // +0x20 movss (0x6bf73f6): fractional part of the frame position; visitor movss (0x666b891)
    float mBlock24[4];               // +0x24 16 bytes copied from a 0x18-byte block (0x6bf73ff..0x6bf7402); visitor movups (0x666ba25)
    uint32_t mQword34[2];            // +0x34 8 bytes (0x6bf7406/0x6bf740a), stored only here
    uint8_t mByte3C;                 // +0x3C = 0 (0x6bf740e)
    uint8_t mPad3D[3];
};
static_assert(offsetof(BlitFlipbookElementLayout, mTexture) == 0x08);
static_assert(offsetof(BlitFlipbookElementLayout, mFrameU) == 0x18);
static_assert(offsetof(BlitFlipbookElementLayout, mFrameV) == 0x1C);
static_assert(offsetof(BlitFlipbookElementLayout, mFrameLerp) == 0x20);
static_assert(offsetof(BlitFlipbookElementLayout, mBlock24) == 0x24);
static_assert(offsetof(BlitFlipbookElementLayout, mQword34) == 0x34);
static_assert(offsetof(BlitFlipbookElementLayout, mByte3C) == 0x3C);
static_assert(sizeof(BlitFlipbookElementLayout) == 0x40);

struct BlitFlipbookDescriptionLayout {
    SharedRefPair mAtlasRef;         // +0x00 built by 0x4DFB570 from the 0x4C74180 result (0x5acb235..0x5acb24f); only the address is used by the visitor tail
    uint64_t mCount;                 // +0x10 (end - begin) >> 6 (0x5acbff4/0x5acbff8/0x5acbff8: mov [rcx],r9); visitor mov rax,[r15+0x10] (0x666b6cf)
    const BlitFlipbookElementLayout* mElements; // +0x18 begin (0x5acc001); visitor mov r14,[r15+0x18] (0x666b6d3)
};
static_assert(offsetof(BlitFlipbookDescriptionLayout, mCount) == 0x10);
static_assert(offsetof(BlitFlipbookDescriptionLayout, mElements) == 0x18);
static_assert(sizeof(BlitFlipbookDescriptionLayout) == 0x20);

// ---------------------------------------------------------------------------------------------------------------------------------------------------------
// FullscreenEffect (Effect tag 7). Producer: clone 0x530A1B0 calls the constructor 0x668BF20 (0x530a605) and inserts tag byte 7 (0x530a67b) through vslot 0x360
// (0x530a685). Descriptions.h RenderFullscreenEffectDescription keeps the full 0xD0 constructor layout. This read-view lists only the offsets that the tag-7 body of
// the Effect visitor reads (sites reached only from the tag-7 head by a control-flow walk, see the md section 8): the body is NOT fully decoded.
struct FullscreenEffectDescriptionReads {
    void* mObject00;                 // +0x00 pointer; byte [obj+0x39] passed to 0x66B2B30 (0x666ae98), the pointer itself to 0xBBD7F70 (0x666ef56, 0x66702bf)
    uint8_t mPad08[0x10];            // +0x08 address taken only: sampler data for 0xBCAB8F0 / 0xBCABA00 (0x666ef80, 0x6670261)
    float mMatrix18[16];             // +0x18/+0x28/+0x38/+0x48 four movups (0x666f32e..0x666f34f, 0x66703a0..0x66703c1)
    float mVec58[3];                 // +0x58 movss (0x667049a), +0x5C movsd (0x667049f)
    float mVec64[4];                 // +0x64 movups (0x666f2fe, 0x6670184) -> a 16-byte uniform (static 0x129F9288)
    uint8_t mPad74[4];
    void* mMesh78;                   // +0x78 mov rax,[r15+0x78] (0x666ae72): the pointee's +0x40 must be non-zero (0x666ae7f); &desc+0x78 goes to 0x66B2B30 (0x666ae91)
    uint8_t mPad80[8];
    uint16_t mWord88;                // +0x88 mov si,[rax+0x88] (0x666f36e), movzx (0x66703e2)
    uint8_t mPad8A[0x3E];
    uint8_t mByteC8;                 // +0xC8 cmp byte [r15+0xC8],1 (0x666d9c0)
    uint8_t mByteC9;                 // +0xC9 (0x6670513)
};
static_assert(offsetof(FullscreenEffectDescriptionReads, mMatrix18) == 0x18);
static_assert(offsetof(FullscreenEffectDescriptionReads, mVec58) == 0x58);
static_assert(offsetof(FullscreenEffectDescriptionReads, mVec64) == 0x64);
static_assert(offsetof(FullscreenEffectDescriptionReads, mMesh78) == 0x78);
static_assert(offsetof(FullscreenEffectDescriptionReads, mWord88) == 0x88);
static_assert(offsetof(FullscreenEffectDescriptionReads, mByteC8) == 0xC8);
static_assert(offsetof(FullscreenEffectDescriptionReads, mByteC9) == 0xC9);

}  // namespace mce::framebuilder::effectvis
