#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_e935700 is lift set; forward-declared here rather than including sub_e935700.h
// (that unit's header has a static_assert on its own layout type that MSVC rejects).
// Signature matches sub_e935700.h exactly: void* sub_e935700(void* a0).
namespace native {
void* sub_e935700(void* a0);
} // namespace native

// sub_1a1e80 (0x1a1e80, size 0xd2 bytes, 1.26.62.01).
// Clears both sub-buffers of the object passed in RCX and releases their heap
// allocations through native::sub_e935700. All offsets below are [V] from the
// disassembly of 0x1a1e80 ([0x1a1e80, 0x1a1f52)):
//   this + 0x40 u8 flag   [R] must equal 1, otherwise the function returns without
//                        touching anything; [W] = 0 at the final reset
//   this + 0x20 void* bufferA  [R] heap buffer pointer A; [W] low byte = 0 at reset
//   this + 0x30 u64       [W] = 0 at reset
//   this + 0x38 u64       [R] compared to 0x10 (heap threshold); [W] = 0xF at reset
//   this + 0x00 void* bufferB  [R] heap buffer pointer B; [W] low byte = 0 at reset
//   this + 0x10 u64       [W] = 0 at reset
//   this + 0x18 u64       [R] compared to 0x10; [W] = 0xF at reset
// Calls [V]:
//   0x1a1ec8  call 0xE935700              -> native::sub_e935700 (lift set, forward-declared above)
//   0x1a1f16  call 0xE935700              -> native::sub_e935700
//   0x1a1f4b  call qword ptr [0xF9A8C78]  -> failfast path; target read from the data slot at call time
//                                                      (brief rule 68: indirect call through a data slot)
// x64 Microsoft ABI: argument (this) arrives in RCX; return type: void. Every path
// ends at 0x1a1f37 ret without storing a return value.
struct sub_1a1e80_this {
    void* bufferB;                    // + 0x00 [R] heap buffer pointer B; [W] low byte = 0 at reset
    std::uint8_t pad0x08[0x10 - 0x08];
    std::uint64_t fieldB0x10;         // + 0x10 [W] = 0 at reset
    std::uint64_t fieldB0x18;         // + 0x18 [R] vs 0x10; [W] = 0xF at reset
    void* bufferA;                    // + 0x20 [R] heap buffer pointer A; [W] low byte = 0 at reset
    std::uint8_t pad0x28[0x30 - 0x28];
    std::uint64_t fieldA0x30;         // + 0x30 [W] = 0 at reset
    std::uint64_t fieldA0x38;         // + 0x38 [R] vs 0x10; [W] = 0xF at reset
    std::uint8_t flag0x40;            // + 0x40 [R] == 1 required; [W] = 0 at reset
};

struct sub_1a1e80Layout {
    static_assert(offsetof(sub_1a1e80_this, bufferB) == 0x00, "sub_1a1e80_this: bufferB at +0x00");
    static_assert(offsetof(sub_1a1e80_this, fieldB0x10) == 0x10, "sub_1a1e80_this: fieldB0x10 at +0x10");
    static_assert(offsetof(sub_1a1e80_this, fieldB0x18) == 0x18, "sub_1a1e80_this: fieldB0x18 at +0x18");
    static_assert(offsetof(sub_1a1e80_this, bufferA) == 0x20, "sub_1a1e80_this: bufferA at +0x20");
    static_assert(offsetof(sub_1a1e80_this, fieldA0x30) == 0x30, "sub_1a1e80_this: fieldA0x30 at +0x30");
    static_assert(offsetof(sub_1a1e80_this, fieldA0x38) == 0x38, "sub_1a1e80_this: fieldA0x38 at +0x38");
    static_assert(offsetof(sub_1a1e80_this, flag0x40) == 0x40, "sub_1a1e80_this: flag0x40 at +0x40");
    static_assert(sizeof(void*) == 8, "sub_1a1e80: x64 pointer-sized fields (Microsoft x64 ABI)");
    static constexpr std::uintptr_t kFailfastSlotRva = 0xF9A8C78; // call qword ptr [0xF9A8C78] slot
    static_assert(kFailfastSlotRva == 0xF9A8C78, "sub_1a1e80: failfast data slot RVA 0xF9A8C78");
};

namespace native {

// sub_1a1e80(void* a0) -> void
//   a0 (this) arrives in RCX. If *(u8*)(a0 + 0x40) != 1 the function returns
//   immediately. Otherwise both sub-buffers (A at +0x20/+0x30/+0x38, B at
//   +0x00/+0x10/+0x18) are released through native::sub_e935700 when their size
//   field exceeds 0x10, then reset to the empty state (ptr low byte 0, size
//   field 0, second field 0xF, flag 0).
void sub_1a1e80(void* a0);

} // namespace native
