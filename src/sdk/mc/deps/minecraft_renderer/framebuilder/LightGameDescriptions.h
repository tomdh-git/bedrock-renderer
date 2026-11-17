#pragma once

// Producer-side stores and visitor-side pass records of the descriptions of items D6c (Clouds, Weather, Atmosphere), D9a (LightAmbient,
// LightDirectional, LightPoint) and D9c (GameplayMetadata, ServerGraphicsOverrideParameters, EditorHighlightConfiguration), 1.26.62.01.
// Source: docs/functions/light_game_descriptions.md; listings docs/data/listings/lightgame_*.txt (exact `rdis` listings, every quoted instruction
// re-checked with tools/sigs/verify_oc.py). Visitor field reads of the same types are in Descriptions.h / SkyDescriptions.h / LightDescriptions.h;
// this header adds the PRODUCER stores (what the clone or constructor writes, by offset) and the pass-object element records the Light visitor
// 0x6640d80 builds from them.
//
// Rules: a named member exists only where a store (producer views) or a read/store (pass records) was seen at an instruction quoted in the doc.
// Gaps are explicit `mPadXX` members that carry NO meaning and are never written/read at that offset in the listed code. Producer views are
// write-views: sizeof is the aligned end of the last store and is cross-checked against the consumer (the visitor copy length or the next local).


namespace mce::framebuilder::lightgame {

// ---------------------------------------------------------------------------------------------------------------------------------------
// Light visitor 0x6640d80 pass-object vectors that the D9a/D9c cases append to (offsets inside the pass returned by 0x5ABA5C0(0x9D0+[frame+0x10])).
// begin/end/cap are three consecutive qwords; "end" is the one the cases compare with cap (`cmp rdx,[rsi+cap]`).
// ---------------------------------------------------------------------------------------------------------------------------------------
namespace passoff {
inline constexpr uint32_t kLightRecordVecBegin = 0x648;     // 0x48-byte light records (0x675FB30; index math `imul eax,0xFFFF8E39`): Directional and Point push one
inline constexpr uint32_t kDwordVecBegin = 0x6F0;           // dword vector (Directional pushes the dword 2)
inline constexpr uint32_t kShadowCubeVecBegin = 0x7B0;      // 0xC8-byte shadow-cube records (Point; `imul eax,0x5C29`)
inline constexpr uint32_t kByteVecAmbientBegin = 0x7C8;     // one byte appended per Ambient (value never stored by the case)
inline constexpr uint32_t kByteVecDirectionalBegin = 0x7E0; // one byte appended per Directional
inline constexpr uint32_t kSummaryVecBegin = 0x7F8;         // 0x14-byte light summary elements (Ambient, Directional, Point)
inline constexpr uint32_t kU16VecBegin = 0x8A0;             // u16 vector (Ambient desc+0x14, Directional desc+0x20, Point desc+0x30)
inline constexpr uint32_t kGameplayMetaVecBegin = 0x498;    // 0x84-byte elements (GameplayMetadata); the case compares +0x4A0 (end) with +0x4A8 (cap)
inline constexpr uint32_t kServerOverrideVecBegin = 0x258;  // 0xB00-byte elements (ServerGraphicsOverrideParameters); end +0x260, cap +0x268
inline constexpr uint32_t kEditorHighlightVecBegin = 0x78;  // 0x58-byte elements (Effect-group visitor 0x666aca0 case 0x666b316): begin +0x78, end +0x80, cap +0x88
}  // namespace passoff

// Element of the summary vector at pass+0x7F8 (stride 0x14, index math `imul eax,0xFFFFCCCD`). Ambient writes {qword, f32, f32(desc+0x10), u16 0};
// Directional {qword desc+0, f32 desc+8, f32 desc+0xC, u8 1, u8 desc+0x10}; Point {f32 desc+8, f32 desc+0xC, f32 desc+0x10, f32 desc+0, u8 desc+0x20, u8 0}.
struct LightSummaryElement {
    float mVec[3];        // +0x00 (Ambient/Directional store the first two as one qword)
    uint32_t mDword0C;    // +0x0C
    uint8_t mByte10;      // +0x10 first byte of the word store `mov [rdx+0x10],ax`
    uint8_t mByte11;      // +0x11
    uint8_t mPad12[2];    // +0x12 never written
};
static_assert(offsetof(LightSummaryElement, mDword0C) == 0x0C);
static_assert(offsetof(LightSummaryElement, mByte10) == 0x10);
static_assert(offsetof(LightSummaryElement, mByte11) == 0x11);
static_assert(sizeof(LightSummaryElement) == 0x14);

// ---------------------------------------------------------------------------------------------------------------------------------------
// D9a LightAmbient: Light tag 0, clone 0x53e2c00 (shared with RenderAtmosphere), description local [rbp+0x118]; insert 0x53e352c through vslot 0x380
// with the variant {&desc, tag 0} (stores 0x53e3503 / 0x53e3511). Stores 0x53e3473..0x53e3493.
// ---------------------------------------------------------------------------------------------------------------------------------------
struct LightAmbientProducer {
    float mVec00[2];      // +0x00 movlps [rbp+0x118],xmm8 (Atmosphere +0xA4/+0xA8 copy, optionally x [obj+0x70])
    float mValue08;       // +0x08 movss [rbp+0x120],xmm7 (Atmosphere +0xAC)
    float mValue0C;       // +0x0C movss [rbp+0x124],xmm6 (Atmosphere +0xB0); WRITTEN by the producer, never READ by the visitor case
    float mValue10;       // +0x10 movss [rbp+0x128],xmm0 (xmm6, or xmm6 x [obj+0x70] x [obj+0x74] when mode == 1)
    uint16_t mValue14;    // +0x14 mov [rbp+0x12C],ax (byte [[rbp+0x1B8]+0x74])
    uint8_t mPad16[2];    // +0x16 never written
};
static_assert(offsetof(LightAmbientProducer, mValue08) == 0x08);
static_assert(offsetof(LightAmbientProducer, mValue0C) == 0x0C);
static_assert(offsetof(LightAmbientProducer, mValue10) == 0x10);
static_assert(offsetof(LightAmbientProducer, mValue14) == 0x14);
static_assert(sizeof(LightAmbientProducer) == 0x18);

// ---------------------------------------------------------------------------------------------------------------------------------------
// D9a LightDirectional: Light tag 1, thin clone 0x5370960 (tag store 0x53709d4, vslot 0x380 at 0x53709db), called from the sky/light producer 0x5369b30
// at 0x536b1a1 (first light) and 0x536c2cc (second light), description local [rbp+0xF0]. Stores 0x536b15f..0x536b190 / 0x536c288..0x536c2be.
// ---------------------------------------------------------------------------------------------------------------------------------------
struct LightDirectionalProducer {
    float mVec00[2];      // +0x00 movlps [rbp+0xF0]: site 1 xmm14 (0x6752A20 output +0x274), site 2 xmm13 (blend of the two keyframe vectors)
    float mValue08;       // +0x08 movss [rbp+0xF8]: site 1 xmm13 (output +0x27C), site 2 xmm8
    float mValue0C;       // +0x0C movss [rbp+0xFC]: site 1 xmm6 (output +0x284), site 2 xmm6
    uint8_t mByte10;      // +0x10 mov byte [rbp+0x100]: site 1 constant 0 (0x536b178), site 2 `sete` ([rbp+0x288]==0, 0x536c2a1)
    uint8_t mPad11[3];    // +0x11 never written
    float mVec14[2];      // +0x14 movq [rbp+0x104]: site 1 xmm7 (keyframe +0x14), site 2 [r15+0x14]
    float mValue1C;       // +0x1C movss [rbp+0x10C]: site 1 xmm8 (keyframe +0x1C), site 2 [r15+0x1C]
    uint16_t mValue20;    // +0x20 mov [rbp+0x110],ax = byte [[rbp+0x2E0]+0x74]
    uint8_t mPad22[2];    // +0x22
};
static_assert(offsetof(LightDirectionalProducer, mValue08) == 0x08);
static_assert(offsetof(LightDirectionalProducer, mValue0C) == 0x0C);
static_assert(offsetof(LightDirectionalProducer, mByte10) == 0x10);
static_assert(offsetof(LightDirectionalProducer, mVec14) == 0x14);
static_assert(offsetof(LightDirectionalProducer, mValue1C) == 0x1C);
static_assert(offsetof(LightDirectionalProducer, mValue20) == 0x20);
static_assert(sizeof(LightDirectionalProducer) == 0x24);

// ---------------------------------------------------------------------------------------------------------------------------------------
// D9a LightPoint: Light tag 3. Built by the constructor 0x668ADE0 (call 0x535a949 in the producer 0x53599d0; args rcx = dest [rbp+0xC0], rdx = config
// copy [rbp+0x80], r8b = u16 +0x30, r9 = six {weak_ptr, vec4} slices [rbp-0x40], [rsp+0x20] = three floats [rbp+0xB0]); insert 0x535a9ce through
// vslot 0x380 with tag 3 (0x535a9b7). The constructor stores every member below (0x668adec..0x668af97) and decrements the source weak counts.
// ---------------------------------------------------------------------------------------------------------------------------------------
struct LightPointProducer {
    struct Slice {
        void* mObject;       // +0x00 weak_ptr pointer (moved from the source slice; `lock inc [ctrl+0xC]` = weak count)
        void* mControl;      // +0x08 weak_ptr control block
        float mVec[4];       // +0x10
    };
    float mValue00;          // +0x00 mov [rcx],eax (config +0)
    uint8_t mByte04;         // +0x04 mov [rcx+4],al (config +4); never read by the visitor
    uint8_t mPad05[3];       // +0x05 never written
    float mValue08;          // +0x08..+0x1C six config floats
    float mValue0C;
    float mValue10;
    float mValue14;
    float mValue18;
    float mValue1C;
    float mVec20[4];         // +0x20 movups (config +0x20)
    uint16_t mValue30;       // +0x30 mov [rcx+0x30],r8w
    uint8_t mPad32[6];       // +0x32 never written
    Slice mSlices[6];        // +0x38 + 0x20*k, k = 0..5 (+0x38, +0x58, +0x78, +0x98, +0xB8, +0xD8)
    float mValueF8;          // +0xF8 movss from the 3-float argument [0]
    float mValueFC;          // +0xFC argument [1]
    float mValue100;         // +0x100 argument [2]
    uint8_t mPad104[4];      // +0x104 never written
};
static_assert(offsetof(LightPointProducer, mByte04) == 0x04);
static_assert(offsetof(LightPointProducer, mValue08) == 0x08);
static_assert(offsetof(LightPointProducer, mValue1C) == 0x1C);
static_assert(offsetof(LightPointProducer, mVec20) == 0x20);
static_assert(offsetof(LightPointProducer, mValue30) == 0x30);
static_assert(offsetof(LightPointProducer, mSlices) == 0x38);
static_assert(sizeof(LightPointProducer::Slice) == 0x20);
static_assert(offsetof(LightPointProducer, mValueF8) == 0xF8);
static_assert(offsetof(LightPointProducer, mValue100) == 0x100);
static_assert(sizeof(LightPointProducer) == 0x108);

// Pass element of the shadow-cube vector pass+0x7B0/+0x7B8/+0x7C0 pushed by the Point case (stride 0xC8: `add qword ptr [rsi+0x7B8],0xC8` 0x6642016).
// Built at 0x6641ef8..0x6642016 by MOVING the staging copy at [rbp-0x48..]: qword = description +0x28; slice k = {pair, vec4} from description +0x38+0x20k.
struct LightPointShadowCubeElement {
    uint64_t mQword00;                   // +0x00 mov rax,[rbp-0x48]; mov [r12],rax (description +0x28)
    struct Slice {
        void* mObject;                   // +0x00 of the slice (element +0x08 + 0x20k)
        void* mControl;                  // +0x08
        float mVec[4];                   // +0x10
    } mSlices[6];                        // element +0x08, +0x28, +0x48, +0x68, +0x88, +0xA8
};
static_assert(sizeof(LightPointShadowCubeElement::Slice) == 0x20);
static_assert(offsetof(LightPointShadowCubeElement, mSlices) == 0x08);
static_assert(sizeof(LightPointShadowCubeElement) == 0xC8);

// ---------------------------------------------------------------------------------------------------------------------------------------
// D9c GameplayMetadata: Light tag 2, clone 0x53e5910 (fat; description built INLINE at [rbp+0x40], tag store 0x53e5fb4, vslot 0x380 at 0x53e5fbf,
// srcloc names gamecomponents::GameplayMetadata). Visitor case 0x6640f1b copies all 0x84 bytes into the vector pass+0x498/+0x4A0/+0x4A8 (stride 0x84).
// Offsets below are [rbp+0x40+off]. Bytes the producer never stores directly (+0x04, +0x10, +0x2A..+0x2B overlap, ...) are zero-initialised by the
// 16-byte stores at 0x53e5ad6..0x53e5b19 or may be written by the virtual call at 0x53e5de7 (rdx = &desc) [?].
// ---------------------------------------------------------------------------------------------------------------------------------------
struct GameplayMetadataProducer {
    float mValue00;          // +0x00 cvtsi2ss of byte [rbp+0x107] (0x53e5eec..0x53e5ef3), from the world query 0x32D10F0
    uint8_t mPad04[4];       // +0x04 only the zero-init
    float mValue08;          // +0x08 [rdi+0x5D8] (0x53e5c8f)
    float mValue0C;          // +0x0C cvtsi2ss of byte [rbp+0x106] (0x53e5ed2..0x53e5ee0)
    uint8_t mPad10[4];       // +0x10 only the zero-init
    float mValue14;          // +0x14 result of the vcall at 0x53e5d28 (0x53e5d2f)
    float mValue18;          // +0x18 [[r13+0xA8]+4] (0x53e5d34..0x53e5d40)
    uint32_t mValue1C;       // +0x1C u16 [[0x32DC5A0 result]+0x168] zero-extended (0x53e5f40..0x53e5f47)
    uint32_t mValue20;       // +0x20 vcall [[rdi+0x970]+0x420] (0x53e5b31)
    uint32_t mValue24;       // +0x24 hash of the same vcall result (0x53e5bfe..0x53e5c1e)
    uint32_t mValue28;       // +0x28 vcall [[rdi+0x988]+0x18] result (0x53e5c44)
    uint32_t mValue2C;       // +0x2C hash of the vcall [[[rdi+0x988]+0xC0]+0x420] result & 7 (0x53e5c8c)
    uint32_t mFlags30;       // +0x30 bits 0..6 set when float [[rdi+0x950]+0x2BC0 + 4*k] > 0 (0x53e5e08..0x53e5e7d)
    uint16_t mValue34;       // +0x34 vcall [[rdi+0x988]+0xC8] (0x53e5be0)
    uint8_t mByte36;         // +0x36 ([rbp+0x76]: first vcall == 0 ? 1 : second vcall >= 0x3E8)
    uint8_t mByte37;         // +0x37 sete (vcall == 2) (0x53e5bcb)
    uint8_t mByte38;         // +0x38 byte [rsi+0x7D] (0x53e5b57)
    uint8_t mByte39;         // +0x39 byte [r13+0x74] (0x53e5c47)
    uint8_t mPad3A[2];       // +0x3A never written, never read
    float mValue3C;          // +0x3C [rsi] (0x53e5b34)
    float mValue40;          // +0x40 [rsi+4]
    float mValue44;          // +0x44 [rsi+8]
    float mValue48;          // +0x48 [rdi+0x850] / |[rdi+0x850..0x858]| (0x53e5d45..0x53e5d93)
    float mVec4C[4];         // +0x4C {y', z' (unit vector of [rdi+0x850..0x858]), qword [rsi+0xA8]} (0x53e5d8d..0x53e5da2)
    float mValue5C;          // +0x5C [rsi+0xB0] (0x53e5da9)
    float mVec60[2];         // +0x60 movsd [rbp+0xA0] from [[[r13+0x20]+0x70]+0x40] (0x53e5dc6)
    float mValue68;          // +0x68 movss [rbp+0xA8] (0x53e5dce)
    uint8_t mPad6C[0x18];    // +0x6C..+0x83 only the zero-init stores 0x53e5b04..0x53e5b19
};
static_assert(offsetof(GameplayMetadataProducer, mValue08) == 0x08);
static_assert(offsetof(GameplayMetadataProducer, mValue14) == 0x14);
static_assert(offsetof(GameplayMetadataProducer, mValue1C) == 0x1C);
static_assert(offsetof(GameplayMetadataProducer, mValue20) == 0x20);
static_assert(offsetof(GameplayMetadataProducer, mFlags30) == 0x30);
static_assert(offsetof(GameplayMetadataProducer, mValue34) == 0x34);
static_assert(offsetof(GameplayMetadataProducer, mByte36) == 0x36);
static_assert(offsetof(GameplayMetadataProducer, mByte39) == 0x39);
static_assert(offsetof(GameplayMetadataProducer, mValue3C) == 0x3C);
static_assert(offsetof(GameplayMetadataProducer, mValue48) == 0x48);
static_assert(offsetof(GameplayMetadataProducer, mVec4C) == 0x4C);
static_assert(offsetof(GameplayMetadataProducer, mValue5C) == 0x5C);
static_assert(offsetof(GameplayMetadataProducer, mVec60) == 0x60);
static_assert(offsetof(GameplayMetadataProducer, mValue68) == 0x68);
static_assert(offsetof(GameplayMetadataProducer, mPad6C) == 0x6C);
static_assert(sizeof(GameplayMetadataProducer) == 0x84);

// ---------------------------------------------------------------------------------------------------------------------------------------
// D9c ServerGraphicsOverrideParameters: Light tag 5, producer 0x6c2e820 (description = the 44 local containers [rbp-0x50 + 0x40*k], insert 0x6c2f6f7
// through vslot 0x380, tag store 0x6c2f6dc, srcloc names gamecomponents::ServerGraphicsOverrideParameters). Visitor case 0x66417af copies it with
// 0x67B6300 (44 container copies) and 0x67E90D0 into pass+0x258 (stride 0xB00).
// Container = MSVC std::_Hash layout (empty ctor 0xA1C40 / 0x433020: float 1.0 at +0, list head, bucket vector, mask 7, maxidx 8).
// ---------------------------------------------------------------------------------------------------------------------------------------
struct ServerOverrideHashContainer {
    float mMaxLoadFactor;    // +0x00 mov dword [rsi],0x3F800000 (0xa1cc3)
    uint8_t mPad04[4];       // +0x04 never written
    void* mListHead;         // +0x08 list sentinel node (0x18/0x20-byte alloc, self-linked) (0xa1c9b)
    uint64_t mSize;          // +0x10 zeroed by movups [rsi+8] (0xa1c63)
    void* mBucketBegin;      // +0x18 (0xa1d26)
    void* mBucketEnd;        // +0x20 bucket vector end = begin + 0x80 (0xa1d31)
    void* mBucketCap;        // +0x28 (0xa1d35)
    uint64_t mMask;          // +0x30 = 7 (0xa1cb3)
    uint64_t mMaxIndex;      // +0x38 = 8 (0xa1cbb)
};
static_assert(offsetof(ServerOverrideHashContainer, mListHead) == 0x08);
static_assert(offsetof(ServerOverrideHashContainer, mBucketBegin) == 0x18);
static_assert(offsetof(ServerOverrideHashContainer, mBucketEnd) == 0x20);
static_assert(offsetof(ServerOverrideHashContainer, mBucketCap) == 0x28);
static_assert(offsetof(ServerOverrideHashContainer, mMask) == 0x30);
static_assert(offsetof(ServerOverrideHashContainer, mMaxIndex) == 0x38);
static_assert(sizeof(ServerOverrideHashContainer) == 0x40);

// Element kinds by container index k (copy constructor 0x67B6300 + producer constructors, both listed):
//   k 0..16, 18..20, 36..38, 40..43  unordered_set<u16>        (copy 0x67B7810, node 0x18 bytes {next, prev, u16 key +0x10}; producer ctor 0xA1C40)
//   k 21..35, 39                     unordered_map<u16, 3 floats> (copy 0x67B7C10, node 0x20 bytes {next, prev, u16 +0x10, floats +0x14/+0x18/+0x1C}; producer ctor 0x433020)
//   k 17                             unordered_map<u16, u32>   (copied inline 0x67b6538..0x67b6891; producer inline init [rbp+0x3F0], filled by 0x6C3FEA0: node u32 +0x14)
inline constexpr uint32_t kServerOverrideContainerCount = 44;
struct ServerGraphicsOverrideParametersDesc {
    ServerOverrideHashContainer mContainer[kServerOverrideContainerCount];
};
static_assert(offsetof(ServerGraphicsOverrideParametersDesc, mContainer) == 0x00);
static_assert(sizeof(ServerGraphicsOverrideParametersDesc) == 0xB00);
static_assert(offsetof(ServerGraphicsOverrideParametersDesc, mContainer[43]) == 0xAC0);

// ---------------------------------------------------------------------------------------------------------------------------------------
// D9c EditorHighlightConfiguration: Effect tag 8, thin clone 0x4c8a5b0 (tag store 0x4c8a624, vslot 0x360 at 0x4c8a62b, srcloc names
// gamecomponents::EditorHighlightConfiguration), called from the producer 0x4c88900 at 0x4c89478 with the description local [rbp+0x568].
// Stores 0x4c893d6..0x4c8943c; visitor case 0x666b316 copies all 0x58 bytes (+0x00,+0x08,+0x10..+0x4F, +0x50) into pass+0x78 (stride 0x58).
// ---------------------------------------------------------------------------------------------------------------------------------------
struct EditorHighlightConfigurationProducer {
    void* mObject;           // +0x00 shared_ptr pointer, filled by 0x4DFB570(&desc, &[rbp+0x480]) (0x4c893d6)
    void* mControl;          // +0x08 control block (use count at ctrl+8)
    uint32_t mValue10;       // +0x10 mov dword [rbp+0x578],1 (0x4c893df)
    float mVec14[3];         // +0x14 qword [rcx] + dword [rcx+8], from [r12+0x84] / [r12+0x8C] (0x4c89400, 0x4c893f6)
    float mValue20;          // +0x20 movss [rbp+0x588],xmm14 = [r12+0x90] (0x4c89403)
    float mVec24[3];         // +0x24 qword [rcx+0x10] + dword [rcx+0x18], the same [r12+0x84]/[r12+0x8C] again (0x4c8941c, 0x4c89412)
    float mValue30;          // +0x30 movss [rbp+0x598],xmm14 (0x4c89420)
    float mVec34[4];         // +0x34 movups [rcx+0x20] = [r12+0x74] (0x4c89363, 0x4c89434 via [rbp+0x470])
    float mVec44[4];         // +0x44 movups [rbp+0x5AC],xmm12 = constant [0xF20A380] (0.12, 1, 1, 0.125) (0x4c89434)
    float mValue54;          // +0x54 mov dword [rbp+0x5BC],0x3F800000 (0x4c8943c)
};
static_assert(offsetof(EditorHighlightConfigurationProducer, mControl) == 0x08);
static_assert(offsetof(EditorHighlightConfigurationProducer, mValue10) == 0x10);
static_assert(offsetof(EditorHighlightConfigurationProducer, mVec14) == 0x14);
static_assert(offsetof(EditorHighlightConfigurationProducer, mValue20) == 0x20);
static_assert(offsetof(EditorHighlightConfigurationProducer, mVec24) == 0x24);
static_assert(offsetof(EditorHighlightConfigurationProducer, mValue30) == 0x30);
static_assert(offsetof(EditorHighlightConfigurationProducer, mVec34) == 0x34);
static_assert(offsetof(EditorHighlightConfigurationProducer, mVec44) == 0x44);
static_assert(offsetof(EditorHighlightConfigurationProducer, mValue54) == 0x54);
static_assert(sizeof(EditorHighlightConfigurationProducer) == 0x58);

// ---------------------------------------------------------------------------------------------------------------------------------------
// D6c Atmosphere: Sky tag 0, same fat clone 0x53e2c00 (description [rbp-0x38 .. rbp+0x100), variant {&desc, 0} at [rbp+0x130] stored 0x53e328a/0x53e3291,
// vslot 0x370 at 0x53e32ac, srcloc names RenderAtmosphereDescription). Defaults 0x53e2e76..0x53e2f61, overrides 0x53e2fa1..0x53e31f5, offset = [rbp+disp+0x38].
// The visitor reads of this type are RenderAtmosphereDescription in Descriptions.h (0x138).
// ---------------------------------------------------------------------------------------------------------------------------------------
struct AtmosphereProducer {
    uint16_t mWord00;        // +0x00 default 0 (0x53e2e7c), then byte [[rbp+0x1B8]+0x74] (0x53e2fa5)
    uint8_t mPad02[2];       // +0x02 never written
    uint32_t mDword04;       // +0x04 vcall [[rsi+0x988]+0x18] mode value (0x53e2dd2 -> 0x53e2e82)
    float mVec08[2];         // +0x08 default (0.1, 500.0) [0xF2470E0], then [rsi+0x45C] (0x53e2fb1)
    float mValue10;          // +0x10 default 500.0 (0x53e2e92), then [rsi+0x464] (0x53e2fbe)
    float mRow[7][4];        // +0x14 + 0x10*k: defaults (0,0,0,1); +0x14..+0x6F overwritten by six movups from [rsi+0x478/0x468/0x498/0x488/0x4B8/0x4A8]; +0x74 by [rsi+0x424]
    float mVec84[4];         // +0x84 default 0 (0x53e2ebf), then shufps of [rsi+0x434] and [rsi+0x5D4] + [0xF2470F0] (0x53e2fe3..0x53e2fea)
    float mValue94;          // +0x94 default 0, then [[...+0x1E8]+0x4C] (0x53e3011)
    float mValue98;          // +0x98 [[...+0x1E8]+0x34] when byte [[[...+0x1E8]+0x58]+0x100]==1, else 0 (lerp factor 0, 0x53e3022..0x53e3041)
    float mValue9C;          // +0x9C default 1.0 (0x53e2ecb), then 0 or 1.0 depending on [rsi+0x96A] (0x53e30e0)
    uint8_t mByteA0;         // +0xA0 default 0, then [rsi+0x96B]==0 ? [rsi+0x96A] : 1 (cmove, 0x53e309a..0x53e309d)
    uint8_t mPadA1[3];       // +0xA1 never written
    float mVecA4[4];         // +0xA4 default 0; [r13+0x18]x2 / x[0xF247100] / [r13+0x18] / [r13+0x28] (0x53e30fc..0x53e314f)
    float mVecB4[4];         // +0xB4 default 0; [r13+0x38] on the last branch (0x53e3157)
    float mVecC4[4];         // +0xC4 default 0; [r13+0x48] on the last branch (0x53e3160)
    uint8_t mPadD4[4];       // +0xD4 never written
    uint8_t mTextureRefD8[0x10];  // +0xD8 shared pair from 0x4DFB570 (0x53e2efd) or zero (0x53e2f05)
    float mVecE8[4];         // +0xE8 default (1,1,1,1) [0xEF40DE0] (0x53e2f0c); first qword overwritten (16,16)/(1,1) (0x53e30ec/0x53e3129); +0xF0 qword = [rsi+0x414] (0x53e30a8)
    float mVecF8[4];         // +0xF8 default (0,0,0,1) [0xF0922E0]; qword overwritten by the biome-lookup result x [0xF0A3FE0] (0x53e31f5)
    uint32_t mDword108;      // +0x108 default 0 (0x53e2f28)
    float mVec10C[4];        // +0x10C default (1,1,1,1) [0xF0FFAA0] (0x53e2f32)
    float mVec11C[2];        // +0x11C default (0,1) [0xEFD32F0] (0x53e2f48)
    uint32_t mDword124;      // +0x124 default 0 (0x53e2f50)
    float mVec128[4];        // +0x128 default (1,1,1,1) [0xF0FFAA0] (0x53e2f5a)
};
static_assert(offsetof(AtmosphereProducer, mDword04) == 0x04);
static_assert(offsetof(AtmosphereProducer, mVec08) == 0x08);
static_assert(offsetof(AtmosphereProducer, mValue10) == 0x10);
static_assert(offsetof(AtmosphereProducer, mRow) == 0x14);
static_assert(offsetof(AtmosphereProducer, mVec84) == 0x84);
static_assert(offsetof(AtmosphereProducer, mValue94) == 0x94);
static_assert(offsetof(AtmosphereProducer, mValue9C) == 0x9C);
static_assert(offsetof(AtmosphereProducer, mByteA0) == 0xA0);
static_assert(offsetof(AtmosphereProducer, mVecA4) == 0xA4);
static_assert(offsetof(AtmosphereProducer, mVecC4) == 0xC4);
static_assert(offsetof(AtmosphereProducer, mTextureRefD8) == 0xD8);
static_assert(offsetof(AtmosphereProducer, mVecE8) == 0xE8);
static_assert(offsetof(AtmosphereProducer, mVecF8) == 0xF8);
static_assert(offsetof(AtmosphereProducer, mDword108) == 0x108);
static_assert(offsetof(AtmosphereProducer, mVec10C) == 0x10C);
static_assert(offsetof(AtmosphereProducer, mVec11C) == 0x11C);
static_assert(offsetof(AtmosphereProducer, mDword124) == 0x124);
static_assert(offsetof(AtmosphereProducer, mVec128) == 0x128);
static_assert(sizeof(AtmosphereProducer) == 0x138);

// ---------------------------------------------------------------------------------------------------------------------------------------
// D6c Clouds: Sky tag 1, clone 0x53e88a0 builds ONE description per cloud mesh piece with the constructor 0x668E940 (call 0x53e90ea, dest [rbp-0x28],
// rdx = matrix A [rbp+0x80], r8 = matrix B [rbp+0x100], r9 = mesh r12 = begin of vector [cloud state+0x90] + index*0x260, stack args 0x53e90b0..0x53e90d0);
// insert 0x53e9174 through vslot 0x370 with the variant {&desc, 1} (stores 0x53e9156/0x53e915d). Constructor stores 0x668e969..0x668eaf8.
// ---------------------------------------------------------------------------------------------------------------------------------------
struct CloudsProducer {
    float mMatrixA[16];      // +0x00 copied from rdx (0x668e965..0x668e9fe)
    float mMatrixB[16];      // +0x40 copied from r8 (0x668ea03..0x668eaad)
    const void* mMesh;       // +0x80 mov [rax+0x80],r9 (0x668eab2)
    float mColor[4];         // +0x88 movups from the stack argument [rsp+0x40] -> caller [rbp+0x1E0] = cloud state +0xA8 (0x668eab9)
    uint8_t mByte98;         // +0x98 caller dl = byte [cloud state+0xD4] (0x53e9098)
    uint8_t mByte99;         // +0x99 caller r15b: 1, or the result of 0x1999140 (0x53e9045..0x53e904b)
    uint8_t mByte9A;         // +0x9A caller al = byte of [rbp+0x298]
    uint8_t mPad9B;          // +0x9B never written
    uint32_t mValue9C;       // +0x9C bt r10,0x20: optional override value, else [[[arg+0x80]+0x40]] default (0x668ead7..0x668eaf8)
    uint16_t mFlags;         // +0xA0 caller ax = byte [ctx+0x74] (0x53e9089)
    uint8_t mPadA2[6];       // +0xA2 never written
};
static_assert(offsetof(CloudsProducer, mMatrixB) == 0x40);
static_assert(offsetof(CloudsProducer, mMesh) == 0x80);
static_assert(offsetof(CloudsProducer, mColor) == 0x88);
static_assert(offsetof(CloudsProducer, mByte98) == 0x98);
static_assert(offsetof(CloudsProducer, mByte99) == 0x99);
static_assert(offsetof(CloudsProducer, mByte9A) == 0x9A);
static_assert(offsetof(CloudsProducer, mValue9C) == 0x9C);
static_assert(offsetof(CloudsProducer, mFlags) == 0xA0);
static_assert(sizeof(CloudsProducer) == 0xA8);

// ---------------------------------------------------------------------------------------------------------------------------------------
// D6c Weather: Sky tag 9, thin clone 0x5ad5800 (tag store 0x5ad5874, vslot 0x370 at 0x5ad587b, srcloc names RenderWeatherDescription), called from
// the producer 0x5ad3f70 at 0x5ad4d61 and 0x5ad4f47 after the constructor 0x668DD20 (call 0x5ad4d54 / 0x5ad4f3a) filled the local [rbp-0x28].
// Constructor stores 0x668dd3d..0x668e0dd. The three texture refs need count >= 3 in the argument array (else 0x668e0f0 -> 0x78ED0).
// ---------------------------------------------------------------------------------------------------------------------------------------
struct WeatherProducer {
    uint64_t mQword00;       // +0x00 rdx (the mesh object, read by the visitor as [rsi] -> mesh)
    uint32_t mDword08;       // +0x08 r8d (caller: 6 * (2 * r12))
    uint32_t mDword0C;       // +0x0C r9d (caller esi)
    float mMatrix[16];       // +0x10 16 floats copied from the 5th argument (caller [rbp+0x2A0])
    uint8_t mTextureRef[3][0x10];  // +0x50 / +0x60 / +0x70 three shared refs via 0x4DFB570 from the 6th argument array {count, ptr} (stride 0x10)
    uint32_t mValue80;       // +0x80 7th argument (caller [rdi+0x60])
    uint32_t mValue84;       // +0x84 8th argument (caller [rbp+0x300])
    float mVec88[4];         // +0x88 [[a9+0x70]+0x40]..+0xC
    float mVec98[2];         // +0x98 [[a9+0x78]+0x40]..+4
    float mValueA0;          // +0xA0 [[a9+0x80]+0x40]
    float mValueA4;          // +0xA4 [[a9+0x88]+0x40]
    float mVecA8[4];         // +0xA8 [[a9+0x190]+0x40]..+0xC
    float mVecB8[4];         // +0xB8 [a11+0x10]..+0x1C
    float mVecC8[4];         // +0xC8 [a11+0]..+0xC
    float mVecD8[4];         // +0xD8 [[a9+0x1B8]+0x40]
    float mVecE8[4];         // +0xE8 [[a9+0x1A8]+0x40]
    float mVecF8[4];         // +0xF8 [[a9+0x1C0]+0x40]
    float mVec108[4];        // +0x108 [[a9+0x198]+0x40]
    float mVec118[4];        // +0x118 [[a9+0x1B0]+0x40]
    uint16_t mWord128;       // +0x128 10th argument (caller byte [r14+0x74])
    uint8_t mPad12A[6];      // +0x12A never written
};
static_assert(offsetof(WeatherProducer, mDword08) == 0x08);
static_assert(offsetof(WeatherProducer, mMatrix) == 0x10);
static_assert(offsetof(WeatherProducer, mTextureRef) == 0x50);
static_assert(offsetof(WeatherProducer, mValue80) == 0x80);
static_assert(offsetof(WeatherProducer, mVec88) == 0x88);
static_assert(offsetof(WeatherProducer, mVec98) == 0x98);
static_assert(offsetof(WeatherProducer, mValueA0) == 0xA0);
static_assert(offsetof(WeatherProducer, mVecA8) == 0xA8);
static_assert(offsetof(WeatherProducer, mVecB8) == 0xB8);
static_assert(offsetof(WeatherProducer, mVecC8) == 0xC8);
static_assert(offsetof(WeatherProducer, mVecD8) == 0xD8);
static_assert(offsetof(WeatherProducer, mVec118) == 0x118);
static_assert(offsetof(WeatherProducer, mWord128) == 0x128);
static_assert(sizeof(WeatherProducer) == 0x130);

}  // namespace mce::framebuilder::lightgame
