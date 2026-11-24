// LIFT 0xe874f20 size 0x127 1.26.62.01 BgfxFrameBuilder slot 16
#pragma once

#include <cstdint>

namespace native::d3d12 {

struct FrameSlot16 {
    uint32_t field_00;        // +0x00
    float field_04[16];       // +0x04 .. +0x43 (16 floats = 64 bytes)
    uint8_t field_44;         // +0x44 - flag
    uint16_t field_48;        // +0x48 - word
    uint8_t field_4A;         // +0x4A - byte
    uint8_t field_4C;         // +0x4C - state
    // size = 0x4D, padded to 0x50
};
static_assert(sizeof(FrameSlot16) == 0x50, "FrameSlot16 size mismatch");
static_assert(offsetof(FrameSlot16, field_00) == 0x00, "FrameSlot16::field_00 offset mismatch");
static_assert(offsetof(FrameSlot16, field_04) == 0x04, "FrameSlot16::field_04 offset mismatch");
static_assert(offsetof(FrameSlot16, field_44) == 0x44, "FrameSlot16::field_44 offset mismatch");
static_assert(offsetof(FrameSlot16, field_48) == 0x48, "FrameSlot16::field_48 offset mismatch");
static_assert(offsetof(FrameSlot16, field_4A) == 0x4A, "FrameSlot16::field_4A offset mismatch");
static_assert(offsetof(FrameSlot16, field_4C) == 0x4C, "FrameSlot16::field_4C offset mismatch");

// Callee at 0x53d5c20 (not in lift set, not in native_boundary.tsv)
// Signature inferred from usage: void sub_53d5c20(float* dst, const float* src);
extern "C" void sub_53d5c20(float* dst, const float* src);

void sub_e874f20(FrameSlot16* dst, const FrameSlot16* src);

} // namespace native::d3d12