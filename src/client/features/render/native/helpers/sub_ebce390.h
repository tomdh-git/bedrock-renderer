#pragma once
#include <cstdint>

namespace native {

// sub_ebce390 (0xebce390, size 0x5, 1.26.62.01): the whole function is one instruction,
//   0xebce390  jmp 0xEEC6EC0   ; -> sub_eec6ec0
// a plain tail jump that forwards its three register arguments unchanged to sub_eec6ec0.
// It reads no struct fields and writes no memory, so there are no layout constants
// beyond the x64 ABI itself:
struct SubEbce390Layout {
    static_assert(sizeof(void*) == 8, "sub_ebce390: x64 ABI, pointer-sized register arguments");
    static_assert(sizeof(std::uint32_t) == 4, "sub_ebce390: count argument arrives in r8d");
};

// Lift-set callee: docs/data/native_boundary.tsv classifies 0xeec6ec0 as lift, so it is
// called directly here and linked through its own LIFT_FN registration at the milestone gate.
// Signature from the callers of 0xebce390 (x64 Microsoft ABI, sampled at 0x568ce51, 0x56ae2e8, ...):
//   rcx = pointer argument, rdx = pointer argument, r8d = 32-bit count argument (0x40 / 0x10 seen);
//   rax is unused after the call, so the return type is void.
//   0xebce390  jmp 0xEEC6EC0   (sub_ebce390 itself, 0x5 bytes, tail forwarder)
//   0xeec6ec0  jmp qword ptr [0xF9A8A98]   (sub_eec6ec0, indirect tail jump through data slot)
extern "C" void sub_eec6ec0(void* dst, void* src, std::uint32_t count);

// Signature of sub_ebce390 itself: identical to sub_eec6ec0 (tail forwarder, no register shuffling).
extern "C" void sub_ebce390(void* dst, void* src, std::uint32_t count);

} // namespace native
