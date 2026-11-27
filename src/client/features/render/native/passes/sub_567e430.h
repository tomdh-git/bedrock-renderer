#pragma once
#include <cstddef>
#include <cstdint>

// sub_567e430 (0x567e430, size 0xdd, 1.26.62.01): pass-tasks inline-buffer release.
//
//   0x567e430  push rsi                                             ; prologue
//   ... (every instruction of [0x567e430, 0x567e50d) is cited beside
//     the corresponding statement in sub_567e430.cpp)
//   0x567e50c  int3                                                 ; fail path, noreturn
//
// x64 Microsoft ABI: RCX = a0 (this), return void. No null guards and no SEH
// exist in the original; none are added.
//
// Layout of the a0 object at the offsets the function accesses [V: rdis dis 0x567e430]:
//   +0x100 (R, 1 byte): flag byte; the second buffer is handled only when == 1
//   +0x240 (R/W, 8 bytes): inline buffer #1 begin pointer
//   +0x248 (W, 8 bytes): zeroed by the 16-byte clear at +0x240 (movups [rdi])
//   +0x250 (R/W, 8 bytes): inline buffer #1 end pointer
//   +0xE8  (R/W, 8 bytes): inline buffer #2 begin pointer
//   +0xF0  (W, 8 bytes): zeroed by the 16-byte clear at +0xE8
//   +0xF8  (R/W, 8 bytes): inline buffer #2 end pointer
// Heap block at begin/begin2: -0x8 (R, 8 bytes): block size header read on the large-buffer path.
//
// Callees [V]:
//   - sub_655cea0 (boundary/stl, docs/data/native_boundary.tsv line 289): call at 0x567e440,
//     argument &a0+0x258, through native::Boundary<void, void*>("sub_655cea0"); return ignored.
//   - sub_e935700 (lift set, docs/data/native_functions.tsv 0xe935700): calls at 0x567e483 and
//     0x567e4d9 through its native symbol (brief rule 66); forward-declared below.
//   - data slot 0xF9A8C78 (0x567e506 call qword ptr [0xF9A8C78]): target read from the slot at
//     call time per brief rule 69 (fail handler, 4 zero args, then int3 noreturn); not a static callee.

// Data-slot RVA of the fail handler (call qword ptr [slot]; pointer read at call time).
static constexpr std::uintptr_t kRvaFailSlot = 0xF9A8C78;
static_assert(kRvaFailSlot == 0xF9A8C78, "sub_567e430: fail-handler data slot RVA 0xF9A8C78");

// Offset constants for the a0 object.
struct Sub567e430Layout {
    static constexpr std::size_t kOffFlag0x100 = 0x100;
    static constexpr std::size_t kOffBegin1Ptr = 0x240;
    static constexpr std::size_t kOffBegin1Mid = 0x248;
    static constexpr std::size_t kOffEnd1Ptr = 0x250;
    static constexpr std::size_t kOffBegin2Ptr = 0xE8;
    static constexpr std::size_t kOffBegin2Mid = 0xF0;
    static constexpr std::size_t kOffEnd2Ptr = 0xF8;
    static_assert(sizeof(void*) == 8, "sub_567e430: x64 pointers are 8 bytes");
};
static_assert(sizeof(Sub567e430Layout) > 0, "sub_567e430: layout constant block");

// Mirror of the a0 object at the accessed offsets (byte-exact; no semantics assumed beyond the accesses).
struct Sub567e430This {
    std::uint8_t pad0x00[0xE8];            // +0x00..0xE7
    void* begin2;                          // +0xE8 [R/W] inline buffer #2 begin pointer
    std::uint8_t pad0xF0[0x8];             // +0xF0 [W] zeroed by movups clear at +0xE8
    void* end2;                            // +0xF8 [R/W] inline buffer #2 end pointer
    std::uint8_t flag0x100;                // +0x100 [R] flag byte
    std::uint8_t pad0x101[0x13F];          // +0x101..0x23F
    void* begin1;                          // +0x240 [R/W] inline buffer #1 begin pointer
    std::uint8_t pad0x248[0x8];            // +0x248 [W] zeroed by movups clear at +0x240
    void* end1;                            // +0x250 [R/W] inline buffer #1 end pointer
};

static_assert(offsetof(Sub567e430This, begin2) == Sub567e430Layout::kOffBegin2Ptr,
              "sub_567e430: begin2 at +0xE8");
static_assert(offsetof(Sub567e430This, end2) == Sub567e430Layout::kOffEnd2Ptr,
              "sub_567e430: end2 at +0xF8");
static_assert(offsetof(Sub567e430This, flag0x100) == Sub567e430Layout::kOffFlag0x100,
              "sub_567e430: flag byte at +0x100");
static_assert(offsetof(Sub567e430This, begin1) == Sub567e430Layout::kOffBegin1Ptr,
              "sub_567e430: begin1 at +0x240");
static_assert(offsetof(Sub567e430This, end1) == Sub567e430Layout::kOffEnd1Ptr,
              "sub_567e430: end1 at +0x250");
static_assert(sizeof(Sub567e430This) == 0x258, "sub_567e430: this mirror size");

namespace native {

// sub_e935700 (0xe935700, size 0x5): lift-set callee (tail jump to sub_392960).
// Forward-declared here and called through its native symbol (brief rule 66): never a boundary wrapper.
// ABI recovered from its disassembly: single argument in RCX, result in RAX; no other input register read.
void* sub_e935700(void* a0);

// sub_567e430 (0x567e430, size 0xdd, 1.26.62.01).
void sub_567e430(void* a0);

} // namespace native
