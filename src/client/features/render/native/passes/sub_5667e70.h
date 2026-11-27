#pragma once
#include <cstddef>
#include <cstdint>

// sub_5667e70 (0x5667e70, size 0xe6, 1.26.62.01): pass-tasks inline-buffer release.
//
//   0x5667e70  push rsi                                             ; prologue
//   ... (every instruction of [0x5667e70, 0x5667f56) is cited beside
//     the corresponding statement in sub_5667e70.cpp)
//   0x5667f55  int3                                                 ; fail path, noreturn
//
// x64 Microsoft ABI: RCX = a0 (this), return void. No null guards and no SEH
// exist in the original; none are added.
//
// Layout of the a0 object at the offsets the function accesses [V: rdis dis 0x5667e70]:
//   +0xE8  (R/W, 8 bytes): inline buffer #2 begin pointer            0x5667eef  mov rcx,[rdi]
//   +0xF0  (W, 8 bytes): zeroed by the 16-byte clear at +0xE8        0x5667f2a  movups [rdi],xmm0
//   +0xF8  (R/W, 8 bytes): inline buffer #2 end pointer              0x5667ef7  mov rdx,[rsi+0xF8]
//   +0x100 (R, 1 byte):  flag byte; buffer #2 handled only when == 1 0x5667edf  cmp byte ptr [rsi+0x100],1
//   +0x118 (R/W, 8 bytes): inline buffer #1 begin pointer            0x5667e8e  mov rcx,[rsi+0x118]
//   +0x120 (W, 8 bytes): zeroed by the 16-byte clear at +0x118       0x5667ed4  movups [rdi],xmm0
//   +0x128 (R/W, 8 bytes): inline buffer #1 end pointer              0x5667e9a  mov rdx,[rsi+0x128]
//   +0x130 (R, 8 bytes): address passed as RCX to sub_655cea0        0x5667e82  lea rcx,[rsi+0x130]
//   +0x168 (R, 1 byte):  flag byte; sub_655cea0 called only when == 1 0x5667e79  cmp byte ptr [rcx+0x168],1
// Heap block at begin/begin2: -0x8 (R, 8 bytes): block size header read on the large-buffer path.
//
// Callees [V]:
//   - sub_655cea0 (boundary/stl, docs/data/native_boundary.tsv line 289): call at 0x5667e89,
//     argument &a0+0x130, through native::Boundary<std::uint64_t, void*>("sub_655cea0");
//     return ignored. Guarded by byte[a0+0x168] == 1.
//   - sub_e935700 (lift set, docs/data/native_functions.tsv 0xe935700): calls at 0x5667ecc and
//     0x5667f22 through its native symbol (brief rule 66); forward-declared below.
//   - data slot 0xF9A8C78 (0x5667f4f call qword ptr [0xF9A8C78]): target read from the slot at
//     call time per brief rule 69 (fail handler, 4 zero args, then int3 noreturn); not a static callee.

// Data-slot RVA of the fail handler (call qword ptr [slot]; pointer read at call time).
static constexpr std::uintptr_t kRvaFailSlot = 0xF9A8C78;
static_assert(kRvaFailSlot == 0xF9A8C78, "sub_5667e70: fail-handler data slot RVA 0xF9A8C78");

// Offset constants for the a0 object.
struct Sub5667e70Layout {
    static constexpr std::size_t kOffBegin2Ptr = 0xE8;
    static constexpr std::size_t kOffBegin2Mid = 0xF0;
    static constexpr std::size_t kOffEnd2Ptr = 0xF8;
    static constexpr std::size_t kOffFlag0x100 = 0x100;
    static constexpr std::size_t kOffBegin1Ptr = 0x118;
    static constexpr std::size_t kOffBegin1Mid = 0x120;
    static constexpr std::size_t kOffEnd1Ptr = 0x128;
    static constexpr std::size_t kOffStlArg = 0x130;
    static constexpr std::size_t kOffFlag0x168 = 0x168;
    static_assert(sizeof(void*) == 8, "sub_5667e70: x64 pointers are 8 bytes");
};
static_assert(sizeof(Sub5667e70Layout) > 0, "sub_5667e70: layout constant block");

// Mirror of the a0 object at the accessed offsets (byte-exact; no semantics assumed beyond the accesses).
struct Sub5667e70This {
    std::uint8_t pad0x00[0xE8];            // +0x00..0xE7
    void* begin2;                          // +0xE8 [R/W] inline buffer #2 begin pointer
    std::uint8_t pad0xF0[0x8];             // +0xF0 [W] zeroed by movups clear at +0xE8
    void* end2;                            // +0xF8 [R/W] inline buffer #2 end pointer
    std::uint8_t flag0x100;                // +0x100 [R] flag byte
    std::uint8_t pad0x101[0x17];           // +0x101..0x117
    void* begin1;                          // +0x118 [R/W] inline buffer #1 begin pointer
    std::uint8_t pad0x120[0x8];            // +0x120 [W] zeroed by movups clear at +0x118
    void* end1;                            // +0x128 [R/W] inline buffer #1 end pointer
    std::uint8_t stlArg[8];                // +0x130 [R] address passed to sub_655cea0
    std::uint8_t pad0x138[0x30];           // +0x138..0x167
    std::uint8_t flag0x168;                // +0x168 [R] flag byte
};

static_assert(offsetof(Sub5667e70This, begin2) == Sub5667e70Layout::kOffBegin2Ptr,
              "sub_5667e70: begin2 at +0xE8");
static_assert(offsetof(Sub5667e70This, end2) == Sub5667e70Layout::kOffEnd2Ptr,
              "sub_5667e70: end2 at +0xF8");
static_assert(offsetof(Sub5667e70This, flag0x100) == Sub5667e70Layout::kOffFlag0x100,
              "sub_5667e70: flag byte at +0x100");
static_assert(offsetof(Sub5667e70This, begin1) == Sub5667e70Layout::kOffBegin1Ptr,
              "sub_5667e70: begin1 at +0x118");
static_assert(offsetof(Sub5667e70This, end1) == Sub5667e70Layout::kOffEnd1Ptr,
              "sub_5667e70: end1 at +0x128");
static_assert(offsetof(Sub5667e70This, stlArg) == Sub5667e70Layout::kOffStlArg,
              "sub_5667e70: stlArg at +0x130");
static_assert(offsetof(Sub5667e70This, flag0x168) == Sub5667e70Layout::kOffFlag0x168,
              "sub_5667e70: flag byte at +0x168");
static_assert(sizeof(Sub5667e70This) == 0x170, "sub_5667e70: this mirror size (8-byte aligned)");

namespace native {

// sub_e935700 (0xe935700, lift set): forward-declared here and called through its native symbol
// (brief rule 66): never a boundary wrapper. ABI recovered from its disassembly: single argument
// in RCX, result in RAX; no other input register read.
void* sub_e935700(void* a0);

// sub_5667e70 (0x5667e70, size 0xe6, 1.26.62.01).
void sub_5667e70(void* a0);

} // namespace native
