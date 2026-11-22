#pragma once

namespace mce::framebuilder {

// RenderEditorRenderPlaneDescription (Editor group tag 7). Built by the fat RenderPlane insert clone
// 0x6d3c040 (docs/BGFX_MAP.md 6g/6w). Read by the Editor visitor tag-7 case (head 0x6674760; every
// [rdi+off] below is quoted from docs/progress/oc_U-D10c.md, delegate.py check OK). Field offsets and
// widths are [V]; field meanings are '-'. Size = highest [V]-read offset (+0xE0 word) + width -> 0xE8.
// Cross-check: docs/progress/descriptions.md L4x + producer_fields.txt Editor7: stores end +0xE3
// (word +0xE0, byte +0xE2) => size 0xE8 [I] (shared stack).
#pragma pack(push, 1) // game layout has unaligned wide fields (e.g. qword at +0xC); asserts below hold the exact offsets
struct RenderEditorRenderPlaneDescription {
    uint64_t mField00;  // +0x0  qword read   [V] 0x6674824  movsd xmm3,[rdi]
    uint8_t mField08[0x4];  // +0x8 clipped from 0x8 to 0x4 (overlapping read)  qword read   [V] 0x667b244  mov rsi,[rdi+8]
    uint64_t mField0C;  // +0xc  qword read   [V] 0x6674774  movsd xmm1,[rdi+0xC]
    float mField14;  // +0x14  dword read   [V] 0x66747a2  movss xmm1,[rdi+0x14]
    float mBlock18[4];  // +0x18  16-byte read [V] 0x667aede  movups xmm0,[rdi+0x18]
    uint8_t mBlock28[0xc];  // +0x28 clipped from 0x10 to 0xc (overlapping read)  16-byte read [V] 0x6677105  movups xmm0,[rdi+0x28]
    float mField34;  // +0x34  dword read   [V] 0x66755df  movss xmm0,[rdi+0x34]
    uint8_t mPad38[0x4];
    uint8_t mByte3C;  // +0x3c  byte read    [V] 0x6674760  cmp byte ptr [rdi+0x3C],1
    uint8_t mByte3D;  // +0x3d  byte read    [V] 0x66755d5  cmp byte ptr [rdi+0x3D],1
    uint8_t mByte3E;  // +0x3e  byte read    [V] 0x667ad48  cmp byte ptr [rdi+0x3E],1
    uint8_t mPad3F[0xa1];
    uint16_t mFieldE0;  // +0xe0  word read    [V] 0x66771db  mov r15w,[rdi+0xE0]
    uint8_t mPadE2[0x6];
};
#pragma pack(pop)
static_assert(sizeof(RenderEditorRenderPlaneDescription) == 0xE8);
static_assert(offsetof(RenderEditorRenderPlaneDescription, mField0C) == 0x0C);
static_assert(offsetof(RenderEditorRenderPlaneDescription, mBlock18) == 0x18);
static_assert(offsetof(RenderEditorRenderPlaneDescription, mByte3C) == 0x3C);
static_assert(offsetof(RenderEditorRenderPlaneDescription, mFieldE0) == 0xE0);

} // namespace mce::framebuilder
