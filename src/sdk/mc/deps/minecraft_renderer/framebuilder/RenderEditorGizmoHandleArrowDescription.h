#pragma once

namespace mce::framebuilder {

// RenderEditorGizmoHandleArrowDescription (Editor group tag 1). Built by the thin Arrow insert clone
// 0x4c85d70 (docs/BGFX_MAP.md 6g/6w). Read by the Editor visitor tag-1 case (head 0x667499f; every
// [rdi+off] below is quoted from docs/progress/oc_U-D10c.md, which was delegate.py check OK).
// Field offsets and widths are [V] (visitor read instructions). Field meanings are not shown by any
// instruction/string and are '-'. Size = highest [V]-read offset (+0xD2 byte) + width, aligned -> 0xD8.
// Cross-check: producer_fields.txt Editor1 (clone 0x4c85d70) last store +0x3d0 [I] (shared stack,
// reused across gizmo types; not a per-type bound).
#pragma pack(push, 1) // game layout has unaligned wide fields (e.g. qword at +0xC); asserts below hold the exact offsets
struct RenderEditorGizmoHandleArrowDescription {
    uint64_t mField00;  // +0x0  qword read   [V] 0x6675477  movsd xmm3,[rdi]
    uint8_t mField08[0x4];  // +0x8 clipped from 0x8 to 0x4 (overlapping read)  qword read   [V] 0x667a763  mov rsi,[rdi+8]
    uint64_t mField0C;  // +0xc  qword read   [V] 0x66753c7  movsd xmm2,[rdi+0xC]
    float mField14;  // +0x14  dword read   [V] 0x66753f5  movss xmm2,[rdi+0x14]
    uint64_t mField18;  // +0x18  qword read   [V] 0x6676b7f  movsd xmm1,[rdi+0x18]
    float mField20;  // +0x20  dword read   [V] 0x6676b7a  movss xmm0,[rdi+0x20]
    uint8_t mPad24[0x40];
    float mBlock64[4];  // +0x64  16-byte read [V] 0x66758bd  movups xmm6,[rdi+0x64]
    uint8_t mByte74;  // +0x74  byte read    [V] 0x6675560  movzx eax,byte ptr [rdi+0x74]
    uint8_t mPad75[0x3];
    float mField78;  // +0x78  dword read   [V] 0x66754dd  movss xmm0,[rdi+0x78]
    uint8_t mPad7C[0x54];
    uint16_t mFieldD0;  // +0xd0  word read    [V] 0x6676c9b  mov r12w,[rdi+0xD0]
    uint8_t mByteD2;  // +0xd2  byte read    [V] 0x66758c1  cmp byte ptr [rdi+0xD2],1
    uint8_t mPadD3[0x5];
};
#pragma pack(pop)
static_assert(sizeof(RenderEditorGizmoHandleArrowDescription) == 0xD8);
static_assert(offsetof(RenderEditorGizmoHandleArrowDescription, mField0C) == 0x0C);
static_assert(offsetof(RenderEditorGizmoHandleArrowDescription, mBlock64) == 0x64);
static_assert(offsetof(RenderEditorGizmoHandleArrowDescription, mByte74) == 0x74);
static_assert(offsetof(RenderEditorGizmoHandleArrowDescription, mFieldD0) == 0xD0);
static_assert(offsetof(RenderEditorGizmoHandleArrowDescription, mByteD2) == 0xD2);

} // namespace mce::framebuilder
