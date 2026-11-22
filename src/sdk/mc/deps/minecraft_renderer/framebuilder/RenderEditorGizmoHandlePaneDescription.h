#pragma once

namespace mce::framebuilder {

// RenderEditorGizmoHandlePaneDescription (Editor group tag 3). Built by the thin Pane insert clone
// 0x4c860f0 (docs/BGFX_MAP.md 6g/6w). Read by the Editor visitor tag-3 case (head 0x667463c; every
// [rdi+off] below is quoted from docs/progress/oc_U-D10c.md, delegate.py check OK). Field offsets and
// widths are [V]; field meanings are '-'. Size = highest [V]-read offset (+0x122 byte) + width -> 0x128.
// Cross-check: producer_fields.txt Editor3 (clone 0x4c860f0) last store +0x27c [I] (shared stack).
#pragma pack(push, 1) // game layout has unaligned wide fields (e.g. qword at +0xC); asserts below hold the exact offsets
struct RenderEditorGizmoHandlePaneDescription {
    uint64_t mField00;  // +0x0  qword read   [V] 0x6675229  movsd xmm3,[rdi]
    uint8_t mField08[0x4];  // +0x8 clipped from 0x8 to 0x4 (overlapping read)  qword read   [V] 0x667bf1e  mov rsi,[rdi+8]
    uint64_t mField0C;  // +0xc  qword read   [V] 0x667522d  movsd xmm1,[rdi+0xC]
    float mField14;  // +0x14  dword read   [V] 0x667521d  subss xmm0,[rdi+0x14]
    uint64_t mField18;  // +0x18  qword read   [V] 0x6676856  movsd xmm1,[rdi+0x18]
    float mField20;  // +0x20  dword read   [V] 0x6676851  movss xmm0,[rdi+0x20]
    uint8_t mPad24[0x40];
    float mBlock64[4];  // +0x64  16-byte read [V] 0x6675dea  movups xmm9,[rdi+0x64]
    uint8_t mByte74;  // +0x74  byte read    [V] 0x6675340  cmp byte ptr [rdi+0x74],0
    uint8_t mPad75[0x3];
    float mField78;  // +0x78  dword read   [V] 0x667529c  movss xmm1,[rdi+0x78]
    uint8_t mPad7C[0xa4];
    uint16_t mField120;  // +0x120 word read    [V] 0x667696d  mov r12w,[rdi+0x120]
    uint8_t mByte122;  // +0x122 byte read    [V] 0x6679c65  cmp byte ptr [rdi+0x122],1
    uint8_t mPad123[0x5];
};
#pragma pack(pop)
static_assert(sizeof(RenderEditorGizmoHandlePaneDescription) == 0x128);
static_assert(offsetof(RenderEditorGizmoHandlePaneDescription, mField0C) == 0x0C);
static_assert(offsetof(RenderEditorGizmoHandlePaneDescription, mBlock64) == 0x64);
static_assert(offsetof(RenderEditorGizmoHandlePaneDescription, mByte74) == 0x74);
static_assert(offsetof(RenderEditorGizmoHandlePaneDescription, mField120) == 0x120);
static_assert(offsetof(RenderEditorGizmoHandlePaneDescription, mByte122) == 0x122);

} // namespace mce::framebuilder
