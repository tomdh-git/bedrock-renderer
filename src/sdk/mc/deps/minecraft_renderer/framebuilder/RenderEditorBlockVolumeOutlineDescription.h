#pragma once

namespace mce::framebuilder {

// RenderEditorBlockVolumeOutlineDescription (Editor group tag 6). Built by the thin Outline insert clone
// 0x6c961e0 (docs/BGFX_MAP.md 6g/6w). Read by the Editor visitor tag-6 case (head 0x6674d02; every
// [rdi+off] below is quoted from docs/progress/oc_U-D10c.md, delegate.py check OK). Field offsets and
// widths are [V]; field meanings are '-'. Size = highest [V]-read offset (+0xE4 dword) + width -> 0xE8.
// Cross-check: producer_fields.txt Editor6 (clone 0x6c961e0) last store +0x150 [I] (shared stack).
#pragma pack(push, 1) // game layout has unaligned wide fields (e.g. qword at +0xC); asserts below hold the exact offsets
struct RenderEditorBlockVolumeOutlineDescription {
    uint64_t mField00;  // +0x0  qword read   [V] 0x6674dc6  movsd xmm3,[rdi]
    uint8_t mField08[0x4];  // +0x8 clipped from 0x8 to 0x4 (overlapping read)  qword read   [V] 0x667cbb6  mov rsi,[rdi+8]
    uint64_t mField0C;  // +0xc  qword read   [V] 0x6674d16  movsd xmm1,[rdi+0xC]
    float mField14;  // +0x14  dword read   [V] 0x6674d44  movss xmm1,[rdi+0x14]
    uint8_t mBlock18[0x8];  // +0x18 clipped from 0x10 to 0x8 (overlapping read)  16-byte read [V] 0x667c850  movups xmm0,[rdi+0x18]
    float mField20;  // +0x20  dword read   [V] 0x667a926  movss xmm0,[rdi+0x20]
    uint8_t mPad24[0x4];
    float mBlock28[4];  // +0x28  16-byte read [V] 0x667c2a9  movups xmm0,[rdi+0x28]
    float mField38;  // +0x38  dword read   [V] 0x667a87b  movss xmm0,[rdi+0x38]
    uint8_t mPad3C[0xa4];
    uint16_t mFieldE0;  // +0xe0  word read    [V] 0x667aa18  mov r15w,[rdi+0xE0]
    uint8_t mByteE2;  // +0xe2  byte read    [V] 0x6676eab  cmp byte ptr [rdi+0xE2],1
    uint8_t mByteE3;  // +0xe3  byte read    [V] 0x667c107  cmp byte ptr [rdi+0xE3],1
    uint32_t mFieldE4;  // +0xe4  dword read   [V] 0x667a92b  movss xmm1,[rdi+0xE4]
};
#pragma pack(pop)
static_assert(sizeof(RenderEditorBlockVolumeOutlineDescription) == 0xE8);
static_assert(offsetof(RenderEditorBlockVolumeOutlineDescription, mField0C) == 0x0C);
static_assert(offsetof(RenderEditorBlockVolumeOutlineDescription, mBlock18) == 0x18);
static_assert(offsetof(RenderEditorBlockVolumeOutlineDescription, mFieldE0) == 0xE0);
static_assert(offsetof(RenderEditorBlockVolumeOutlineDescription, mByteE2) == 0xE2);
static_assert(offsetof(RenderEditorBlockVolumeOutlineDescription, mFieldE4) == 0xE4);

} // namespace mce::framebuilder
