#pragma once
// RenderLegacyCubemapDescription (Sky group tag 4), fat clone 0x660b1a0.
// Size 0x40 [V] (producer/clone write extent reaches +0x3F, so the object is 0x40 bytes).
// Field-level [V] marks an offset touched by a verified clone store; [I] = inferred from the fat-clone
// write-range narrative, not individually confirmed. Evidence RVAs verified verbatim against the exe with rdis.

namespace mce::framebuilder {

struct RenderLegacyCubemapDescription {
    uint32_t mValue00;                // +0x00 [V] `0x660b33c  mov [rbp+0x10],eax` (dword store)
    uint8_t mPad04[4];                // +0x04 padding
    void* mSharedPtr;                 // +0x08 [I] shared_ptr pair (object ptr + control block), per fat-clone extent
    void* mSharedCtrl;                // +0x10 [I] shared_ptr control block
    void* mValue18;                   // +0x18 [I] qword
    void* mValue20;                   // +0x20 [I] qword
    float mValue28;                   // +0x28 [I] float
    uint16_t mValue2C;                // +0x2C [I] u16
    uint8_t mPad2E[2];                // +0x2E padding
    float mValue30[2];                // +0x30 [I] vec2 (two floats)
    float mValue38;                   // +0x38 [I] float
    uint16_t mValue3C;                // +0x3C [I] u16
    uint8_t mValue3E;                 // +0x3E [I] byte
    uint8_t mValue3F;                 // +0x3F [V] `0x660b37c  mov [rbp+0x4F],r14b` (byte store)
};
static_assert(sizeof(RenderLegacyCubemapDescription) == 0x40);
static_assert(offsetof(RenderLegacyCubemapDescription, mValue00) == 0x00);
static_assert(offsetof(RenderLegacyCubemapDescription, mValue3F) == 0x3F);

} // namespace mce::framebuilder
