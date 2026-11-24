#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// sub_bc7b7d0 ("VV frame-graph builder") - lifted from [0xbc7b7d0, 0xbc7ba5b),
// size 0x28b, Minecraft Windows 1.26.62.01, region bgfx.
// Exact x64 Microsoft ABI signature of the original:
//   rcx = out   (float[3]: [out,out+8) written by movlps, [out+8,out+0xC) by movss)
//   rdx = in    (const float; reads in[0x0] and in[0x0C])
//   rax = out   (return value)
// No game structs are touched; the only layout assumption is the 0x0c-byte row of
// the two const data tables at 0xF449BEC / 0xF44AA20:
//   +0x00 float f0    (read by movsd: low float lane of the multiply)
//   +0x04 uint32 pad  (high float lane of the movsd multiply - bit pattern reused as float)
//   +0x08 float f8    (read by movss)
struct CascadedTableRow {
    float f0;                          // +0x00
    std::uint32_t pad04;               // +0x04
    float f8;                          // +0x08
};
static_assert(offsetof(CascadedTableRow, f0) == 0x00, "sub_bc7b7d0: table row f0 at +0x00");
static_assert(offsetof(CascadedTableRow, pad04) == 0x04, "sub_bc7b7d0: table row pad at +0x04");
static_assert(offsetof(CascadedTableRow, f8) == 0x08, "sub_bc7b7d0: table row f8 at +0x08");
static_assert(sizeof(CascadedTableRow) == 0x0c, "sub_bc7b7d0: table row stride 0x0c");

// Data RVAs referenced by the function, one per read instruction [V]:
static constexpr std::uintptr_t kRvaDivC1    = 0xEFD32AC;  // 0xbc7b826 divss xmm6,[0xEFD32AC]
static constexpr std::uintptr_t kRvaMulC2    = 0xEFC6CF8;  // 0xbc7b82e mulss xmm6,[0xEFC6CF8]
static constexpr std::uintptr_t kRvaHalfK    = 0xEEE6700;  // 0xbc7b842 movss xmm13,[0xEEE6700]
static constexpr std::uintptr_t kRvaC3       = 0xF10D440;  // 0xbc7b8d0 movss xmm7,[0xF10D440]
static constexpr std::uintptr_t kRvaC4       = 0xEEC8060;  // 0xbc7b95f movss xmm1,[0xEEC8060]
static constexpr std::uintptr_t kRvaC5       = 0xF449710;  // 0xbc7b9b2 addss xmm10,[0xF449710]
static constexpr std::uintptr_t kRvaC6       = 0xF449720;  // 0xbc7b9f1 addps  xmm0,[0xF449720]
static constexpr std::uintptr_t kRvaTable1   = 0xF449BEC;  // 0xbc7b8ae etc., stride 0x0c
static constexpr std::uintptr_t kRvaTable2   = 0xF44AA20;  // 0xbc7b991 etc., stride 0x0c
// Callee import-thunk data slots (hard rule 69: call [0xRVA] through a forwarder is not
// a blocker; the pointer is read from the slot at every call):
static constexpr std::uintptr_t kRvaSlotEec75a0 = 0xF9A8E60;  // 0xEEC75A0 = jmp qword ptr [0xF9A8E60]
static constexpr std::uintptr_t kRvaSlotEec73f0 = 0xF9A8E08;  // 0xEEC73F0 = jmp qword ptr [0xF9A8E08]
static constexpr std::uintptr_t kRvaSlot78ed0   = 0xF9A8CF0;  // 0x78ed0  = sub rsp,0x28 / call [0xF9A8CF0] / int3 (noreturn crt)

static constexpr std::uint64_t kIndexLimit = 0x65;  // 101: cmp reg,0x65 ; jae -> error path

float* sub_bc7b7d0(float* out, const float* in);
native::Footprint sub_bc7b7d0_footprint(float* out, const float* in);

} // namespace native::bgfx
