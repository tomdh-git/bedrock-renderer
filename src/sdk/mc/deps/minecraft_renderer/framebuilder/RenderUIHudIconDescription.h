#pragma once
// RenderUIHudIconDescription (UI group tag 1), producer e9aed0 (@0xe9b470) + extractor 0x6664d51 / movzx 0x6665561.
// Size 0x50 [V] (producer matrix block reaches +0x47, +0x48 low-word access, tail to 0x50).
// Field-level [V] marks an offset touched by a verified access; [I] = inferred, not individually confirmed.
// Evidence RVAs verified verbatim against the exe with rdis.

namespace mce::framebuilder {

struct RenderUIHudIconDescription {
    void* mPtr00;                     // +0x00 [I] qword (producer ctor call `0xe9b470  call qword ptr [0xF99FFA0]`)
    float mMatrix[16];                // +0x08 [I] matrix block +0x08..+0x47 (producer)
    uint16_t mValue48;                // +0x48 [V] `0x6665561  movzx esi,word ptr [rax+0x48]` (low-word read); extractor `0x6664d51  mov [rbp+0x520],r9`
    uint8_t mPad4A[6];                // +0x4A padding (tail to reach 0x50)
};
static_assert(sizeof(RenderUIHudIconDescription) == 0x50);
static_assert(offsetof(RenderUIHudIconDescription, mMatrix) == 0x08);
static_assert(offsetof(RenderUIHudIconDescription, mValue48) == 0x48);

} // namespace mce::framebuilder
