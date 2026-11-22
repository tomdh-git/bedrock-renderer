#pragma once

namespace mce::framebuilder {

// RenderEditorGizmoHandleCubeDescription (Editor group tag 2). Built by the thin Cube insert clone
// 0x4c85f30 (docs/BGFX_MAP.md 6g/6w). Read by the Editor visitor tag-2 case (head 0x6674518; every
// [rdi+off] below is quoted from docs/progress/oc_U-D10c.md, delegate.py check OK). Field offsets and
// widths are [V]; field meanings are '-'. Size = highest [V]-read offset (+0xD2 byte) + width -> 0xD8.
// Cross-check: producer_fields.txt Editor2 (clone 0x4c85f30) last store +0x337 [I] (shared stack).
#pragma pack(push, 1) // game layout has unaligned wide fields (e.g. qword at +0xC); asserts below hold the exact offsets
struct RenderEditorGizmoHandleCubeDescription {
    uint64_t mField00;  // +0x0  qword read   [V] 0x66750ea  movsd xmm3,[rdi]
    uint8_t mField08[0x4];  // +0x8 clipped from 0x8 to 0x4 (overlapping read)  qword read   [V] 0x6679aa1  mov rsi,[rdi+8]
    uint64_t mField0C;  // +0xc  qword read   [V] 0x667503a  movsd xmm2,[rdi+0xC]
    float mField14;  // +0x14  dword read   [V] 0x6675068  movss xmm2,[rdi+0x14]
    uint64_t mField18;  // +0x18  qword read   [V] 0x667653d  movsd xmm1,[rdi+0x18]
    float mField20;  // +0x20  dword read   [V] 0x6676538  movss xmm0,[rdi+0x20]
    uint8_t mPad24[0x40];
    float mBlock64[4];  // +0x64  16-byte read [V] 0x66751b2  movups xmm6,[rdi+0x64]
    uint8_t mByte74;  // +0x74  byte read    [V] 0x66751a6  movzx eax,byte ptr [rdi+0x74]
    uint8_t mPad75[0x3];
    float mField78;  // +0x78  dword read   [V] 0x6675153  movss xmm0,[rdi+0x78]
    uint8_t mPad7C[0x54];
    uint16_t mFieldD0;  // +0xd0  word read    [V] 0x6676652  mov r12w,[rdi+0xD0]
    uint8_t mByteD2;  // +0xd2  byte read    [V] 0x667589a  cmp byte ptr [rdi+0xD2],0
    uint8_t mPadD3[0x5];
};
#pragma pack(pop)
static_assert(sizeof(RenderEditorGizmoHandleCubeDescription) == 0xD8);
static_assert(offsetof(RenderEditorGizmoHandleCubeDescription, mField0C) == 0x0C);
static_assert(offsetof(RenderEditorGizmoHandleCubeDescription, mBlock64) == 0x64);
static_assert(offsetof(RenderEditorGizmoHandleCubeDescription, mByte74) == 0x74);
static_assert(offsetof(RenderEditorGizmoHandleCubeDescription, mFieldD0) == 0xD0);
static_assert(offsetof(RenderEditorGizmoHandleCubeDescription, mByteD2) == 0xD2);

} // namespace mce::framebuilder
