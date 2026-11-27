#pragma once
#include <cstdint>

// sub_ebd2160 (0xebd2160, size 0x5c, 1.26.62.01): builds a 0x38-byte descriptor on the
// stack and calls sub_ebd1f80 with it; returns sub_ebd1f80's result in rax.
// Full reversal: docs/functions/ebd2160.md (section 'Reversed source (complete)').
//
// Frame: 0xebd2160 mov r11,rsp ; 0xebd2163 sub rsp,0x68.
// Descriptor base = rsp + 0x20 (== r11 - 0x48), written at offsets 0x00..0x38:
//   +0x00 qword 0x000000000F847A07   (0xebd2171)
//   +0x08 dword  0                   (0xebd2178)
//   +0x0c dword  0                   (0xebd217c)
//   +0x10 qword 0x000000000F449520   (0xebd2192)
//   +0x18 qword 0x000000000F449530   (0xebd219d)
//   +0x20 qword arg2 (rdx)           (0xebd21a1)
//   +0x28 qword 0                    (0xebd21a5)
//   +0x30 qword zero_extend(arg3 r8d)(0xebd21a9)
// Call at 0xebd21b1: sub_ebd1f80(rcx = out, rdx = &desc+0x10, r8 = out, r9 = 0xF449530);
// nothing in the descriptor is read by this function (the callee reads it through rcx/rdx).
// Arg a1 (rcx) is never read.

struct sub_ebd2160Layout {
    static_assert(sizeof(void*) == 8, "sub_ebd2160: x64 ABI, pointer-sized address space");
    // Descriptor base relative to rsp after `sub rsp,0x68` (0xebd2180 lea r8,[r11-0x48]).
    static constexpr std::uintptr_t kDescOffsetFromRsp = 0x20;
    static constexpr std::uintptr_t kDescSize = 0x38;
    // Field offsets within the descriptor.
    static constexpr std::uintptr_t kF00_Addr0 = 0x00;   // qword immediate 0x000000000F847A07
    static constexpr std::uintptr_t kF08_Zero1 = 0x08;   // dword 0
    static constexpr std::uintptr_t kF0c_Zero2 = 0x0c;   // dword 0
    static constexpr std::uintptr_t kF10_Addr1 = 0x10;   // qword immediate 0x000000000F449520
    static constexpr std::uintptr_t kF18_Addr2 = 0x18;   // qword immediate 0x000000000F449530
    static constexpr std::uintptr_t kF20_Arg2 = 0x20;    // qword arg2 (rdx)
    static constexpr std::uintptr_t kF28_Zero3 = 0x28;   // qword 0
    static constexpr std::uintptr_t kF30_Arg3 = 0x30;    // qword zero_extend(arg3 r8d)
    // Immediate absolute addresses loaded by the lea instructions.
    static constexpr std::uintptr_t kImm0 = 0x000000000F847A07ui64;   // 0xebd216a lea r8,[0xF847A07]
    static constexpr std::uintptr_t kImm1 = 0x000000000F449520ui64;   // 0xebd218b lea r9,[0xF449520]
    static constexpr std::uintptr_t kImm2 = 0x000000000F449530ui64;   // 0xebd2196 lea r9,[0xF449530]
    static_assert(kDescOffsetFromRsp == 0x20, "sub_ebd2160: descriptor at rsp+0x20");
    static_assert(kDescSize == 0x38, "sub_ebd2160: descriptor size 0x38");
    static_assert(kF00_Addr0 == 0x00, "sub_ebd2160: field 0 at +0x00");
    static_assert(kF08_Zero1 == 0x08, "sub_ebd2160: field 1 at +0x08");
    static_assert(kF0c_Zero2 == 0x0c, "sub_ebd2160: field 2 at +0x0c");
    static_assert(kF10_Addr1 == 0x10, "sub_ebd2160: field 3 at +0x10");
    static_assert(kF18_Addr2 == 0x18, "sub_ebd2160: field 4 at +0x18");
    static_assert(kF20_Arg2 == 0x20, "sub_ebd2160: field 5 at +0x20");
    static_assert(kF28_Zero3 == 0x28, "sub_ebd2160: field 6 at +0x28");
    static_assert(kF30_Arg3 == 0x30, "sub_ebd2160: field 7 at +0x30");
};

namespace native {

// sub_ebd1f80 (0xebd1f80): direct call target of sub_ebd2160 at 0xebd21b1
// (`0xebd21b1  call 0xEBD1F80`). Classification: not in docs/data/native_functions.tsv
// and not in docs/data/native_boundary.tsv (only `?` in native_boundary_candidates.tsv:418).
// Signature below is the observed call site: four pointer-sized register arguments
// (rcx, rdx, r8, r9), return in rax. Forward-declared here so the lifted body can make
// the same call; the callee itself is registered by its own unit once classified
// (blocking fact for this unit: see docs/progress/oc_U-EX7.ebd2160.md).
extern "C" void* sub_ebd1f80(void* a1, void* a2, void* a3, void* a4);

// sub_ebd2160 (0xebd2160, 0x5c bytes, 1.26.62.01): x64 Microsoft ABI.
//   a1 = rcx (never read), a2 = rdx, a3 = r8d, a4 = r9; return = rax = sub_ebd1f80 result.
void* sub_ebd2160(void* a1, void* a2, std::uint32_t a3, void* a4);

} // namespace native
