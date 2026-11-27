#pragma once
#include <cstddef>
#include <cstdint>

// sub_56b67f0 (0x56b67f0, size 0xc8, 1.26.62.01).
//
//   0x56b67f0  push rsi                                            ; prologue
//   ... (all instructions of [0x56b67f0, 0x56b68b8))
//   0x56b68b7  ret                                                ; epilogue
//
// x64 Microsoft ABI: RCX = this (a0), return void.
//
// Layout of fields in 'this' object (a0/RCX) [V]:
//   +0x30 (R, 8 bytes): pointer to refcounted object (slot 0)
//   +0x50 (R, 8 bytes): pointer to refcounted object (slot 1)
//   +0x70 (R, 8 bytes): pointer to refcounted object (slot 2)
//   +0x90 (R, 8 bytes): pointer to refcounted object (slot 3)
//   +0xB0 (R, 8 bytes): pointer to refcounted object (slot 4)
//   +0xD0 (R, 8 bytes): pointer to refcounted object (slot 5)
//
// Layout of refcounted object [V]:
//   +0x00 (R, 8 bytes): vfptr
//   +0x08 (R/W, 4 bytes): uint32_t refcount (not used here)
//   +0x0C (R/W, 4 bytes): uint32_t count0xC (lock dec on release)
//
// Callees [V]:
//   - sub_eea6040 (boundary/vendor, via data slot 0xF99FFA0): 5 calls + 1 tail call
//     (virtual deallocator vfptr[1])
//
// No null guards or SEH beyond the original's own tests.

// Offset constants for the 'this' object (a0/RCX).
static constexpr std::size_t kThisOffset0x30 = 0x30;
static constexpr std::size_t kThisOffset0x50 = 0x50;
static constexpr std::size_t kThisOffset0x70 = 0x70;
static constexpr std::size_t kThisOffset0x90 = 0x90;
static constexpr std::size_t kThisOffset0xB0 = 0xB0;
static constexpr std::size_t kThisOffset0xD0 = 0xD0;

// Offset constants for the refcounted object.
static constexpr std::size_t kRefcountedOffsetVfptr = 0x00;
static constexpr std::size_t kRefcountedOffsetCount0xC = 0x0C;

struct sub_56b67f0_this {
    std::uint8_t pad0x00[0x30];
    void* field0x30;  // +0x30 [R] refcounted object pointer (slot 0)
    std::uint8_t pad0x38[0x18];
    void* field0x50;  // +0x50 [R] refcounted object pointer (slot 1)
    std::uint8_t pad0x58[0x18];
    void* field0x70;  // +0x70 [R] refcounted object pointer (slot 2)
    std::uint8_t pad0x78[0x18];
    void* field0x90;  // +0x90 [R] refcounted object pointer (slot 3)
    std::uint8_t pad0x98[0x18];
    void* field0xB0;  // +0xB0 [R] refcounted object pointer (slot 4)
    std::uint8_t pad0xB8[0x18];
    void* field0xD0;  // +0xD0 [R] refcounted object pointer (slot 5)
};

struct sub_56b67f0_refcounted {
    void* vfptr;              // +0x00 [R] vfptr
    std::uint32_t refcount;   // +0x08 [R/W] (not used by this function)
    std::uint32_t count0xC;   // +0x0C [R/W] lock dec
};

struct sub_56b67f0Layout {
    static_assert(offsetof(sub_56b67f0_this, field0x30) == kThisOffset0x30,
                  "sub_56b67f0_this: field0x30 at +0x30");
    static_assert(offsetof(sub_56b67f0_this, field0x50) == kThisOffset0x50,
                  "sub_56b67f0_this: field0x50 at +0x50");
    static_assert(offsetof(sub_56b67f0_this, field0x70) == kThisOffset0x70,
                  "sub_56b67f0_this: field0x70 at +0x70");
    static_assert(offsetof(sub_56b67f0_this, field0x90) == kThisOffset0x90,
                  "sub_56b67f0_this: field0x90 at +0x90");
    static_assert(offsetof(sub_56b67f0_this, field0xB0) == kThisOffset0xB0,
                  "sub_56b67f0_this: field0xB0 at +0xB0");
    static_assert(offsetof(sub_56b67f0_this, field0xD0) == kThisOffset0xD0,
                  "sub_56b67f0_this: field0xD0 at +0xD0");
    static_assert(offsetof(sub_56b67f0_refcounted, vfptr) == kRefcountedOffsetVfptr,
                  "sub_56b67f0_refcounted: vfptr at +0x00");
    static_assert(offsetof(sub_56b67f0_refcounted, count0xC) == kRefcountedOffsetCount0xC,
                  "sub_56b67f0_refcounted: count0xC at +0x0C");
    static_assert(sizeof(void*) == 8, "sub_56b67f0: x64 pointers are 8 bytes");
};

namespace native {

// sub_56b67f0(void* a0) -> void
void sub_56b67f0(void* a0);

} // namespace native