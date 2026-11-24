#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub 0xbc7b3a0 — VV frame-graph builder (bgfx), size 0x425, 1.26.62.01.
// Range: [0xbc7b3a0, 0xbc7b7c5) [V] (docs/data/native_functions.tsv line 1111).
//
// x64 Microsoft ABI:
//   rcx = out float*   (the original copies it to rsi; rax = out on return, 0xbc7b7be ret)
//   rdx = in const float*   (the original copies it to rdi)
//   Reads in[+0,+4,+8,+0xC,+0x10,+0x18] [V]. Writes out[0..8) via movlps (0xbc7b753)
//   and out[8..0xC) via movss (0xbc7b756) [V]. No class members or globals — args and
//   stack only [V].
//   Error path: 0xbc7b7bf  call 0x78ED0 then 0xbc7b7c4  int3 (trap block, reached by all
//   six idx >= 0x65 branches) [V].
//
// Callee table [V]:
//   0xEEC75A0 = jmp qword ptr [0xF9A8E60], float (float) — class lift in
//     docs/data/native_boundary.tsv line 514 and docs/data/native_functions.tsv line 1638:
//     declared here as sub_eec75a0 and called directly like any lifted function.
//   0xEEC73F0 = jmp qword ptr [0xF9A8E08], float (float) — class lift in
//     native_boundary.tsv line 513 and native_functions.tsv line 1637:
//     declared here as sub_eec73f0 and called directly like any lifted function.
//   0x78ed0   = sub rsp,0x28 / call qword ptr [0xF9A8CF0] / int3 (noreturn crt, class crt
//     in native_boundary.tsv line 11); entered through the trap block at 0xbc7b7bf via a
//     slot read at 0xF9A8CF0 (hard rule 69) — see the .cpp.
//
// Data-table row layout (tables at 0xF449730 / 0xF44A0A8 / 0xF44A564, stride 0x0c, 3
// rows per index) [V]:
//   +0x00 float f0     (read by movsd: low lane multiplies the splatted scale)
//   +0x04 uint32 pad04 (high lane of the same movsd multiply - bit pattern reused as float)
//   +0x08 float f8     (read by movss)
struct TableRow {
    float f0;                          // +0x00
    std::uint32_t pad04;               // +0x04
    float f8;                          // +0x08
};
static_assert(offsetof(TableRow, f0) == 0x00, "sub_bc7b3a0: table row f0 at +0x00");
static_assert(offsetof(TableRow, pad04) == 0x04, "sub_bc7b3a0: table row pad at +0x04");
static_assert(offsetof(TableRow, f8) == 0x08, "sub_bc7b3a0: table row f8 at +0x08");
static_assert(sizeof(TableRow) == 0x0c, "sub_bc7b3a0: table row stride 0x0c");

// Data RVAs read by the function, one named constant per read instruction [V]:
static constexpr std::uintptr_t kRvaDivC1   = 0xEFD32AC;  // 0xbc7b409  divss xmm6,[0xEFD32AC]
static constexpr std::uintptr_t kRvaMulC2   = 0xEFC6CF8;  // 0xbc7b411  mulss xmm6,[0xEFC6CF8]
static constexpr std::uintptr_t kRvaK       = 0xEEE6700;  // 0xbc7b424  movss xmm15,[0xEEE6700]
static constexpr std::uintptr_t kRvaC3      = 0xEFC2540;  // 0xbc7b4af  movss xmm1,[0xEFC2540]
static constexpr std::uintptr_t kRvaC4      = 0xF0C8C88;  // 0xbc7b4bb  addss xmm1,[0xF0C8C88]
static constexpr std::uintptr_t kRvaC5      = 0xF1527C8;  // 0xbc7b4c3  divss xmm1,[0xF1527C8]
static constexpr std::uintptr_t kRvaC6      = 0xEF40D44;  // 0xbc7b4d9  movss xmm8,[0xEF40D44]
static constexpr std::uintptr_t kRvaC7      = 0xF10D440;  // 0xbc7b5ab  movss xmm9,[0xF10D440]
static constexpr std::uintptr_t kRvaC8      = 0xEEC8060;  // 0xbc7b63c  movss xmm0,[0xEEC8060]
static constexpr std::uintptr_t kRvaC9      = 0xEFD3410;  // 0xbc7b6ae  movss xmm5,[0xEFD3410]
static constexpr std::uintptr_t kRvaC10     = 0xF246F60;  // 0xbc7b6c2  addss xmm12,[0xF246F60]
static constexpr std::uintptr_t kRvaC11     = 0xF0A9660;  // 0xbc7b72c  movaps xmm5,[0xF0A9660]
static constexpr std::uintptr_t kRvaC12     = 0xF449700;  // 0xbc7b743  addps  xmm2,[0xF449700]
static constexpr std::uintptr_t kRvaTable0  = 0xF449730;  // 0xbc7b485  lea rdx,[0xF449730]
static constexpr std::uintptr_t kRvaTable1  = 0xF44A0A8;  // 0xbc7b56e  lea rdx,[0xF44A0A8]
static constexpr std::uintptr_t kRvaTable2  = 0xF44A564;  // 0xbc7b67b  lea rcx,[0xF44A564]
static constexpr std::uintptr_t kRvaSlot78ed0 = 0xF9A8CF0;  // 0x78ed0 calls qword ptr [0xF9A8CF0]

static constexpr std::uint64_t kIndexLimit = 0x65;  // 0xbc7b451  cmp rbx,0x65 ; jae trap

// Callee import-thunk data slots (documented; the calls in this function are direct
// calls to the thunk stubs, whose bodies live in their own lift units):
//   0xEEC75A0 = jmp qword ptr [0xF9A8E60]   (slot 0xF9A8E60)
//   0xEEC73F0 = jmp qword ptr [0xF9A8E08]   (slot 0xF9A8E08)
//   0x78ed0   = sub rsp,0x28 / call [0xF9A8CF0] / int3   (slot 0xF9A8CF0, noreturn)

// Lift callees (class lift in native_boundary.tsv): forward-declared here with the exact
// x64 ABI signature seen at the call sites (float in xmm0, float out in xmm0) and called
// directly, like any lifted function (hard rule 66).
float sub_eec75a0(float x);
float sub_eec73f0(float x);

float* sub_bc7b3a0(float* out, const float* in);

// Footprint of sub 0xbc7b3a0: [out, out+0xC) written directly (movlps + movss) [V].
std::size_t sub_bc7b3a0_footprint(float* out, const float* in);

static_assert(sizeof(std::uintptr_t) == 8, "sub_bc7b3a0: uintptr_t is 8 bytes on x64");
static_assert(sizeof(float) == 4, "sub_bc7b3a0: float is 4 bytes");

} // namespace native
