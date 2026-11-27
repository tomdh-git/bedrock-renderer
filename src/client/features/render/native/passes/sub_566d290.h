#pragma once
#include <cstddef>
#include <cstdint>

// sub_566d290 (0x566d290, size 0xbd, 1.26.62.01).
//
//   0x566d290  push r14                                            ; prologue
//   ... (all instructions of [0x566d290, 0x566d34d))
//   0x566d34c  ret                                                ; epilogue
//
// x64 Microsoft ABI: RCX = this (a0), return void.
//
// Layout of fields in 'this' object (a0/RCX) [V]:
//   +0x08 (R, 8 bytes): start of object array (iterator begin)
//   +0x10 (R, 8 bytes): end of object array (iterator end)
//   +0x30 (R, 8 bytes): pointer to refcounted object (released if +0x38 == 3)
//   +0x38 (R, 1 byte): flag byte (compared to 3)
//
// Layout of each array element (stride 0x28) [V]:
//   +0x08 (R, 8 bytes): pointer to refcounted object (released if +0x18 == 2)
//   +0x18 (R, 1 byte): flag byte (compared to 2)
//
// Layout of refcounted object [V]:
//   +0x00 (R, 8 bytes): vfptr (vtable[0] = destructor, vtable[8] = deallocator)
//   +0x08 (R/W, 4 bytes): uint32_t refcount (lock dec on release)
//   +0x0C (R/W, 4 bytes): uint32_t count0xC (lock dec on release)
//
// Callees [V]:
//   - sub_eea6040 (boundary/vendor, via data slot 0xF99FFA0): 4 calls
//     (virtual destructor vfptr[0] and virtual deallocator vfptr[8])
//
// No null guards or SEH beyond the original's own tests.

// Offset constants for the 'this' object (a0/RCX).
static constexpr std::size_t kThisOffset0x08 = 0x08;
static constexpr std::size_t kThisOffset0x10 = 0x10;
static constexpr std::size_t kThisOffset0x30 = 0x30;
static constexpr std::size_t kThisOffset0x38 = 0x38;

// Offset constants for each array element (stride 0x28).
static constexpr std::size_t kElemOffset0x08 = 0x08;
static constexpr std::size_t kElemOffset0x18 = 0x18;

// Offset constants for the refcounted object.
static constexpr std::size_t kRefcountedOffsetVfptr = 0x00;
static constexpr std::size_t kRefcountedOffsetRefcount = 0x08;
static constexpr std::size_t kRefcountedOffsetCount0xC = 0x0C;

struct sub_566d290_this {
    std::uint8_t pad0x00[0x08];
    void* field0x08;       // +0x08 [R] start of object array
    void* field0x10;       // +0x10 [R] end of object array
    std::uint8_t pad0x18[0x18];
    void* field0x30;       // +0x30 [R] refcounted object pointer
    std::uint8_t field0x38; // +0x38 [R] flag byte
};

struct sub_566d290_elem {
    std::uint8_t pad0x00[0x08];
    void* field0x08;   // +0x08 [R] refcounted object pointer
    std::uint8_t pad0x10[0x08];
    std::uint8_t field0x18; // +0x18 [R] flag byte
};

struct sub_566d290_refcounted {
    void* vfptr;              // +0x00 [R] vfptr
    std::uint32_t refcount;   // +0x08 [R/W] lock dec
    std::uint32_t count0xC;   // +0x0C [R/W] lock dec
};

struct sub_566d290Layout {
    static_assert(offsetof(sub_566d290_this, field0x08) == kThisOffset0x08,
                  "sub_566d290_this: field0x08 at +0x08");
    static_assert(offsetof(sub_566d290_this, field0x10) == kThisOffset0x10,
                  "sub_566d290_this: field0x10 at +0x10");
    static_assert(offsetof(sub_566d290_this, field0x30) == kThisOffset0x30,
                  "sub_566d290_this: field0x30 at +0x30");
    static_assert(offsetof(sub_566d290_this, field0x38) == kThisOffset0x38,
                  "sub_566d290_this: field0x38 at +0x38");
    static_assert(offsetof(sub_566d290_elem, field0x08) == kElemOffset0x08,
                  "sub_566d290_elem: field0x08 at +0x08");
    static_assert(offsetof(sub_566d290_elem, field0x18) == kElemOffset0x18,
                  "sub_566d290_elem: field0x18 at +0x18");
    static_assert(offsetof(sub_566d290_refcounted, vfptr) == kRefcountedOffsetVfptr,
                  "sub_566d290_refcounted: vfptr at +0x00");
    static_assert(offsetof(sub_566d290_refcounted, refcount) == kRefcountedOffsetRefcount,
                  "sub_566d290_refcounted: refcount at +0x08");
    static_assert(offsetof(sub_566d290_refcounted, count0xC) == kRefcountedOffsetCount0xC,
                  "sub_566d290_refcounted: count0xC at +0x0C");
    static_assert(sizeof(void*) == 8, "sub_566d290: x64 pointers are 8 bytes");
};

namespace native {

// sub_566d290(void* a0) -> void
void sub_566d290(void* a0);

} // namespace native
