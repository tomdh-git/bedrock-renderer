#pragma once

namespace mce::framebuilder {

// RenderEditorSelectionCursorDescription (Editor group tag 5). Built by the thin SelectionCursor insert
// clone 0x5371160 (docs/BGFX_MAP.md 6g/6w). Read by the Editor visitor tag-5 case (head 0x6674ac3; every
// [rdi+off] below is quoted from docs/progress/oc_U-D10c.md, delegate.py check OK). Field offsets and
// widths are [V]; field meanings are '-'. Size = highest [V]-read offset (+0xE0 word) + width -> 0xE8.
// Cross-check: producer_fields.txt Editor5 (clone 0x5371160) last store +0x160 [I] (shared stack).
#pragma pack(push, 1) // game layout has unaligned wide fields (e.g. qword at +0xC); asserts below hold the exact offsets
struct RenderEditorSelectionCursorDescription {
    uint64_t mField00;  // +0x0  qword read   [V] 0x6674b87  movsd xmm3,[rdi]
    uint8_t mField08[0x4];  // +0x8 clipped from 0x8 to 0x4 (overlapping read)  qword read   [V] 0x66779ee  mov rsi,[rdi+8]
    uint64_t mField0C;  // +0xc  qword read   [V] 0x6674ad7  movsd xmm1,[rdi+0xC]
    float mField14;  // +0x14  dword read   [V] 0x6674b05  movss xmm1,[rdi+0x14]
    float mBlock18[4];  // +0x18  16-byte read [V] 0x6677686  movups xmm0,[rdi+0x18]
    float mBlock28[4];  // +0x28  16-byte read [V] 0x6675a36  movups xmm0,[rdi+0x28]
    float mField38;  // +0x38  dword read   [V] 0x667598b  movss xmm0,[rdi+0x38]
    uint8_t mByte3C;  // +0x3c  byte read    [V] 0x6674ac3  cmp byte ptr [rdi+0x3C],1
    uint8_t mPad3D[0xa3];
    uint16_t mFieldE0;  // +0xe0  word read    [V] 0x6675b0c  mov bx,[rdi+0xE0]
    uint8_t mPadE2[0x6];
};
#pragma pack(pop)
static_assert(sizeof(RenderEditorSelectionCursorDescription) == 0xE8);
static_assert(offsetof(RenderEditorSelectionCursorDescription, mField0C) == 0x0C);
static_assert(offsetof(RenderEditorSelectionCursorDescription, mBlock18) == 0x18);
static_assert(offsetof(RenderEditorSelectionCursorDescription, mField38) == 0x38);
static_assert(offsetof(RenderEditorSelectionCursorDescription, mFieldE0) == 0xE0);

} // namespace mce::framebuilder
