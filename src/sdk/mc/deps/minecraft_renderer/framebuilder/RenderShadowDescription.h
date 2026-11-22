#pragma once
// RenderShadowDescription (Effect group tag 4), producer 0x53e6c30 + extractor case 0x666ad3b.
// Size 0x20 [V] (producer store extent reaches +0x19).
// Field-level [V] marks an offset touched by a verified producer store; [I] = inferred, not individually confirmed.
// Evidence RVAs verified verbatim against the exe with rdis.

namespace mce::framebuilder {

struct RenderShadowDescription {
    void* mPtr00;                     // +0x00 [V] `0x53e7353  mov [rbp+0x1D8],r13` (ptr store)
    void* mPtr08;                     // +0x08 [V] `0x53e735a  mov [rbp+0x1E0],rax` (qword store)
    void* mPtr10;                     // +0x10 [I] ptr (producer narrative)
    uint16_t mFlags;                  // +0x18 [V] `0x53e737a  mov [rbp+0x1F0],ax` (u16 store)
    uint8_t mPad1A[6];                // +0x1A padding (tail to reach 0x20)
};
static_assert(sizeof(RenderShadowDescription) == 0x20);
static_assert(offsetof(RenderShadowDescription, mPtr00) == 0x00);
static_assert(offsetof(RenderShadowDescription, mPtr08) == 0x08);
static_assert(offsetof(RenderShadowDescription, mFlags) == 0x18);

} // namespace mce::framebuilder
