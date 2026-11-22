#pragma once
// RenderFullscreenEffectDescription (Effect group tag 7), ctor 0x668bf20.
// Size 0xD0 [V] (ctor write extent per the ctor narrative: +0x00, +0x08 shared_ptr, +0x18..+0x63 floats,
// +0x64 block, +0x78 pair, +0x88 u16, +0x90 block, +0xA0 byte, +0xA8 storage, +0xC8/+0xC9 bytes).
// Only ctor entry is directly verified (`0x668bf20  push rbp`); individual field offsets are [I] from the
// ctor-write narrative, not individually confirmed. Evidence RVA verified verbatim against the exe with rdis.

namespace mce::framebuilder {

struct RenderFullscreenEffectDescription {
    void* mValue00;                   // +0x00 [I] (ctor writes +0x00)
    void* mSharedPtr;                 // +0x08 [I] shared_ptr object ptr
    void* mSharedCtrl;                // +0x10 [I] shared_ptr control block
    uint8_t mFieldBlock18[0xD0 - 0x18]; // +0x18..+0xCF [I] float block + other fields per ctor narrative
};
static_assert(sizeof(RenderFullscreenEffectDescription) == 0xD0);

} // namespace mce::framebuilder
