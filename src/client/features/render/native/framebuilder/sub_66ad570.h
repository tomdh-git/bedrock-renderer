#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// sub_66ad570 (0x66ad570, size 0xc5, 1.26.62.01) = BgfxFrameBuilder::endFrame
// [V] = verified against the disassembly for 0x66ad570..0x66ad635.
//
// Layout of fields in 'this' object (a0 / RCX) [V]:
//   +0x10 (R, 8 bytes): member released last (tail-called path)
//   +0x30 (R, 8 bytes): member
//   +0x50 (R, 8 bytes): member
//   +0x70 (R, 8 bytes): member
//   +0x90 (R, 8 bytes): member
//   +0xB0 (R, 8 bytes): member released first
//
// Layout of each released object [V]:
//   +0x00 (R, 8 bytes): vfptr  (vfptr[1] == vfptr[8] == deallocator called)
//   +0x0C (R/W, 4 bytes): count0xC (lock dec dword)
//
// Callees [V]:
//   - sub_eea6040 (vendor boundary, reached through loader-resolved data slot 0xF99FFA0):
//     5 direct calls (deallocator path, members 0xB0..0x30) + 1 tail call (member 0x10)
//
// No null guards or SEH beyond the original's own tests.

static constexpr std::size_t kObjOffset0x10 = 0x10;
static constexpr std::size_t kObjOffset0x30 = 0x30;
static constexpr std::size_t kObjOffset0x50 = 0x50;
static constexpr std::size_t kObjOffset0x70 = 0x70;
static constexpr std::size_t kObjOffset0x90 = 0x90;
static constexpr std::size_t kObjOffset0xB0 = 0xB0;

static constexpr std::size_t kReleasedOffsetVfptr = 0x00;
static constexpr std::size_t kReleasedOffsetCount0xC = 0x0C;

struct sub_66ad570_this {
    std::uint8_t pad0x00[0x10];
    void* field0x10;     // +0x10 [R] member
    std::uint8_t pad0x18[0x18];
    void* field0x30;     // +0x30 [R] member
    std::uint8_t pad0x38[0x18];
    void* field0x50;     // +0x50 [R] member
    std::uint8_t pad0x58[0x18];
    void* field0x70;     // +0x70 [R] member
    std::uint8_t pad0x78[0x18];
    void* field0x90;     // +0x90 [R] member
    std::uint8_t pad0x98[0x18];
    void* field0xB0;     // +0xB0 [R] member
};

struct sub_66ad570_released {
    void* vfptr;                     // +0x00 [R] vfptr (vfptr[1] = deallocator)
    std::uint8_t pad0x08[0x04];
    std::uint32_t count0xC;          // +0x0C [R/W] lock dec dword
};

struct sub_66ad570Layout {
    static_assert(offsetof(sub_66ad570_this, field0x10) == kObjOffset0x10,
                  "sub_66ad570: field0x10 must be at +0x10");
    static_assert(offsetof(sub_66ad570_this, field0x30) == kObjOffset0x30,
                  "sub_66ad570: field0x30 must be at +0x30");
    static_assert(offsetof(sub_66ad570_this, field0x50) == kObjOffset0x50,
                  "sub_66ad570: field0x50 must be at +0x50");
    static_assert(offsetof(sub_66ad570_this, field0x70) == kObjOffset0x70,
                  "sub_66ad570: field0x70 must be at +0x70");
    static_assert(offsetof(sub_66ad570_this, field0x90) == kObjOffset0x90,
                  "sub_66ad570: field0x90 must be at +0x90");
    static_assert(offsetof(sub_66ad570_this, field0xB0) == kObjOffset0xB0,
                  "sub_66ad570: field0xB0 must be at +0xB0");
    static_assert(offsetof(sub_66ad570_released, vfptr) == kReleasedOffsetVfptr,
                  "sub_66ad570: vfptr must be at +0x00");
    static_assert(offsetof(sub_66ad570_released, count0xC) == kReleasedOffsetCount0xC,
                  "sub_66ad570: count0xC must be at +0x0C");
};

void sub_66ad570(void* a0);

} // namespace native
