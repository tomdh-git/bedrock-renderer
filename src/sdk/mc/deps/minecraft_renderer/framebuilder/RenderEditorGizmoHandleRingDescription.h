#pragma once

namespace mce::framebuilder {

// RenderEditorGizmoHandleRingDescription (Editor group tag 4). Built by the thin Ring insert clone
// 0x4c862b0 (docs/BGFX_MAP.md 6g/6w). Read by the Editor visitor tag-4 case (head 0x66743f4; every
// [rdi+off] below is quoted from docs/progress/oc_U-D10c.md, delegate.py check OK). Field offsets and
// widths are [V]; where several reads overlap the same span, the span is kept as one block and the
// smaller overlapping reads are subsumed (meaning '-'). Size = highest [V]-read offset (+0x1EC word)
// + width -> 0x1F0. Cross-check: producer_fields.txt Editor4 (clone 0x4c862b0) last store +0x27c [I]
// (shared stack reused across gizmo types; not a per-type bound).
#pragma pack(push, 1) // game layout has unaligned wide fields (e.g. qword at +0xC); asserts below hold the exact offsets
struct RenderEditorGizmoHandleRingDescription {
    uint64_t mField00;  // +0x0  qword read   [V] 0x66750ea  movsd xmm1,[rdi]
    uint8_t mField08[0x4];  // +0x8 clipped from 0x8 to 0x4 (overlapping read)  qword read   [V] 0x6679aa1  mov rsi,[rdi+8]
    float mBlock0C[4];  // +0xc  16-byte read [V] 0x6676456  movups xmm0,[rdi+0xC]
    uint8_t mBlock1C[0xc];  // +0x1c clipped from 0x10 to 0xc (overlapping read)  16-byte read [V] 0x6676461  movups xmm0,[rdi+0x1C]
    float mBlock28[4];  // +0x28  16-byte read [V] 0x6677105  movups xmm0,[rdi+0x28]
    uint8_t mPad38[0x4];
    float mBlock3C[4];  // +0x3c  16-byte read [V] 0x6676477  movups xmm0,[rdi+0x3C]
    uint64_t mField4C;  // +0x4c  qword read   [V] 0x6675866  movsd xmm6,[rdi+0x4C]
    uint64_t mField54;  // +0x54  qword read   [V] 0x667586b  movsd xmm7,[rdi+0x54]
    uint8_t mByte5C;  // +0x5c  byte read    [V] 0x6674fb3  movzx eax,byte ptr [rdi+0x5C]
    uint8_t mPad5D[0x3];
    uint64_t mBlock60[2];  // +0x60  16-byte span [V] 0x6675866/0x6676456 (overlapping reads merged)
    uint8_t mPad70[0x4];
    uint8_t mByte74;  // +0x74  byte read    [V] 0x66751a6  movzx eax,byte ptr [rdi+0x74]
    uint8_t mPad75[0x3];
    float mField78;  // +0x78  dword read   [V] 0x6675153  movss xmm0,[rdi+0x78]
    float mField7C;  // +0x7c  dword read   [V] 0x66764a0  cmp eax,[rdi+0x7C]
    uint8_t mByte80;  // +0x80  byte read    [V] 0x6676497  cmp byte ptr [rdi+0x80],1
    uint8_t mPad81[0x7];
    uint64_t mField88;  // +0x88  qword read   [V] 0x6677a3c  mov r8,[rdi+0x88]
    uint8_t mPad90[0x10];
    uint64_t mFieldA0;  // +0xa0  qword read   [V] 0x6677a27  mov r9,[rdi+0xA0]
    uint64_t mFieldA8;  // +0xa8  qword read   [V] 0x66764b6  mov r8,[rdi+0xA8]
    float mFieldB0;  // +0xb0  dword read   [V] 0x6676489  mov eax,[rdi+0xB0]
    uint8_t mPadB4[0x4];
    uint64_t mFieldB8;  // +0xb8  qword read   [V] 0x667888d  mov rcx,[rdi+0xB8]
    uint8_t mPadC0[0x10];
    uint16_t mFieldD0;  // +0xd0  word read    [V] 0x6676652  mov r12w,[rdi+0xD0]
    uint8_t mByteD2;  // +0xd2  byte read    [V] 0x667589a  cmp byte ptr [rdi+0xD2],0
    uint8_t mPadD3[0x1];
    float mFieldD4;  // +0xd4  dword read   [V] 0x6678885  cmp eax,[rdi+0xD4]
    uint8_t mByteD8;  // +0xd8  byte read    [V] 0x667887c  cmp byte ptr [rdi+0xD8],1
    uint8_t mPadD9[0x7];
    uint64_t mFieldE0;  // +0xe0  qword read   [V] 0x66771db  mov r15w,[rdi+0xE0]
    uint8_t mPadE8[0x10];
    uint64_t mFieldF8;  // +0xf8  qword read   [V] 0x66788cf  mov r9,[rdi+0xF8]
    uint64_t mField100;  // +0x100 qword read   [V] 0x667889f  mov r8,[rdi+0x100]
    uint8_t mByte108;  // +0x108 byte read    [V] 0x6678540  cmp byte ptr [rdi+0x108],1
    uint8_t mPad109[0xdf];
    uint32_t mField1E8;  // +0x1e8 dword read   [V] 0x6678566  mov eax,[rdi+0x1E8]
    uint16_t mField1EC;  // +0x1ec word read    [V] 0x6677a9f  mov r15w,[rdi+0x1EC]
    uint8_t mPad1EE[0x2];
};
#pragma pack(pop)
static_assert(sizeof(RenderEditorGizmoHandleRingDescription) == 0x1F0);
static_assert(offsetof(RenderEditorGizmoHandleRingDescription, mField08) == 0x08);
static_assert(offsetof(RenderEditorGizmoHandleRingDescription, mBlock28) == 0x28);
static_assert(offsetof(RenderEditorGizmoHandleRingDescription, mField54) == 0x54);
static_assert(offsetof(RenderEditorGizmoHandleRingDescription, mByte74) == 0x74);
static_assert(offsetof(RenderEditorGizmoHandleRingDescription, mField88) == 0x88);
static_assert(offsetof(RenderEditorGizmoHandleRingDescription, mFieldB8) == 0xB8);
static_assert(offsetof(RenderEditorGizmoHandleRingDescription, mFieldD0) == 0xD0);
static_assert(offsetof(RenderEditorGizmoHandleRingDescription, mField1E8) == 0x1E8);
static_assert(offsetof(RenderEditorGizmoHandleRingDescription, mField1EC) == 0x1EC);

} // namespace mce::framebuilder
