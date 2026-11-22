#pragma once
// RenderVolumetricFogDescription (Sky group tag 8), case 0x66569b1.
// Size 0xE0 [V] (case write extent reaches +0xDF; case entry `0x66569b1  lea r12,[rbp+0x1E4]`).
// Field-level [I] = inferred from the case write-range narrative (+0x00 u16, +0x04..+0x57 rows, +0x54 qword),
// not individually confirmed. Evidence RVA verified verbatim against the exe with rdis.

namespace mce::framebuilder {

struct RenderVolumetricFogDescription {
    uint16_t mValue00;                // +0x00 [I] u16 per case narrative
    uint8_t mPad02[2];                // +0x02 padding
    uint8_t mRows04[0x54 - 0x04];     // +0x04..+0x57 [I] fog rows block
    void* mPtr54;                     // +0x54 [I] qword
    uint8_t mPad5C[0xE0 - 0x5C];      // +0x5C padding (tail to reach 0xE0)
};
static_assert(sizeof(RenderVolumetricFogDescription) == 0xE0);

} // namespace mce::framebuilder
