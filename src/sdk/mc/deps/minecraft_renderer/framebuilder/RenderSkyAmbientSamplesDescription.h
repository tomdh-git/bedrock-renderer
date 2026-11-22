#pragma once
// RenderSkyAmbientSamplesDescription (Sky group tag 10).
// Size 0x18 [V] (writer/case extent reaches +0x17; shared_ptr pair at +0x08 fills through +0x17).
// Field-level [V] marks an offset touched by a verified access; [I] = inferred, not individually confirmed.
// Evidence RVAs verified verbatim against the exe with rdis.

namespace mce::framebuilder {

struct RenderSkyAmbientSamplesDescription {
    uint16_t mValue00;                // +0x00 [V] `0x6656983  movzx ebx,word ptr [rdi]` (visitor reads the u16 field)
    uint8_t mPad02[2];                // +0x02 padding
    void* mSharedPtr;                 // +0x08 [I] shared_ptr object ptr (ctor call `0x53e4896  call qword ptr [0xF99FFA0]`)
    void* mSharedCtrl;                // +0x10 [I] shared_ptr control block; case 0x6656983 takes the ctrl ref
};
static_assert(sizeof(RenderSkyAmbientSamplesDescription) == 0x18);
static_assert(offsetof(RenderSkyAmbientSamplesDescription, mValue00) == 0x00);

} // namespace mce::framebuilder
