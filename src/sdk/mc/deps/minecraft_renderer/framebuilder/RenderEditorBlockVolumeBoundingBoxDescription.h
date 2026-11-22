#pragma once

namespace mce::framebuilder {

// RenderEditorBlockVolumeBoundingBoxDescription (Editor group tag 0). Built by the thin BoundingBox insert
// clone 0x6c956b0 (docs/BGFX_MAP.md 6g/6w). Read by the Editor visitor tag-0 case (head 0x6674388, which
// tail-jumps to 0x66A1860; every [rdi+off] below is quoted from docs/progress/oc_U-D10c.md,
// delegate.py check OK). Field offsets and widths are [V]; field meanings are '-'. Size = highest
// [V]-read offset (+0x170 byte) + width -> 0x178. Cross-check: producer_fields.txt Editor0 (clone
// 0x6c956b0) last store +0x310 [I] (shared stack reused across editor types; not a per-type bound).
#pragma pack(push, 1) // game layout has unaligned wide fields (e.g. qword at +0xC); asserts below hold the exact offsets
struct RenderEditorBlockVolumeBoundingBoxDescription {
    uint64_t mField00;  // +0x0  qword read   [V] 0x66a1a0b  movsd xmm2,[rdi]
    uint8_t mField08[0x4];  // +0x8 clipped from 0x8 to 0x4 (overlapping read)  qword read   [V] 0x66a3c0f  mov rsi,[rdi+8]
    uint64_t mField0C;  // +0xc  qword read   [V] 0x66a1a0f  movsd xmm3,[rdi+0xC]
    float mField14;  // +0x14  dword read   [V] 0x66a19ec  subss xmm6,[rdi+0x14]
    uint64_t mField18;  // +0x18  qword read   [V] 0x66a384a  movsd xmm1,[rdi+0x18]
    float mField20;  // +0x20  dword read   [V] 0x66a3845  movss xmm0,[rdi+0x20]
    uint8_t mByte24;  // +0x24  byte read    [V] 0x66a3699  movzx ebx,byte ptr [rdi+0x24]
    uint8_t mPad25[0x3];
    float mBlock28[4];  // +0x28  16-byte read [V] 0x66a1ce9  movups xmm0,[rdi+0x28]
    uint8_t mPad38[0x48];
    uint8_t mByte80;  // +0x80  byte read    [V] 0x66a1a6a  cmp byte ptr [rdi+0x80],1
    uint8_t mPad81[0x57];
    uint8_t mByteD8;  // +0xd8  byte read    [V] 0x66a3519  cmp byte ptr [rdi+0xD8],1
    uint8_t mPadD9[0x57];
    uint8_t mByte130;  // +0x130 byte read    [V] 0x66a27c9  cmp byte ptr [rdi+0x130],1
    uint8_t mPad131[0x7];
    float mBlock138[4];  // +0x138 16-byte read [V] 0x66a30e5  movups xmm0,[rdi+0x138]
    float mBlock148[4];  // +0x148 16-byte read [V] 0x66a2395  movups xmm0,[rdi+0x148]
    float mBlock158[4];  // +0x158 16-byte read [V] 0x66a378d  movups xmm0,[rdi+0x158]
    uint8_t mPad168[0x4];
    uint32_t mField16C;  // +0x16c dword read   [V] 0x66a19f7  cvtsi2ss xmm0,dword ptr [rdi+0x16C]
    uint8_t mByte170;  // +0x170 byte read    [V] 0x66a1bf2  cmp byte ptr [rdi+0x170],1
    uint8_t mPad171[0x7];
};
#pragma pack(pop)
static_assert(sizeof(RenderEditorBlockVolumeBoundingBoxDescription) == 0x178);
static_assert(offsetof(RenderEditorBlockVolumeBoundingBoxDescription, mField0C) == 0x0C);
static_assert(offsetof(RenderEditorBlockVolumeBoundingBoxDescription, mBlock28) == 0x28);
static_assert(offsetof(RenderEditorBlockVolumeBoundingBoxDescription, mByte80) == 0x80);
static_assert(offsetof(RenderEditorBlockVolumeBoundingBoxDescription, mBlock138) == 0x138);
static_assert(offsetof(RenderEditorBlockVolumeBoundingBoxDescription, mBlock158) == 0x158);
static_assert(offsetof(RenderEditorBlockVolumeBoundingBoxDescription, mField16C) == 0x16C);
static_assert(offsetof(RenderEditorBlockVolumeBoundingBoxDescription, mByte170) == 0x170);

} // namespace mce::framebuilder
