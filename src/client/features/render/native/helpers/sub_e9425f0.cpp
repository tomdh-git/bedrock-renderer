// LIFT 0xe9425f0 size 0x13 1.26.62.01 sub_e9425f0
#include "sub_e9425f0.h"

#include "client/features/render/native/Lift.h"

#if 0
// Verbatim instructions of sub_e9425f0 ([0xe9425f0, 0xe942603)):
0xe9425f0  sub rsp,0x28
0xe9425f4  call 0x392920          ; -> sub_392920   (boundary: alloc)
0xe9425f9  jmp short 0xE9425FD    ; -> loc_e9425fd
0xe9425fb  xor eax,eax            ; unreachable after the unconditional jmp
0xe9425fd  add rsp,0x28
0xe942601  ret
0xe942602  int3                   ; padding inside the declared size 0x13
#endif

namespace native {

// sub_e9425f0 (0xe9425f0, size 0x13, 1.26.62.01): transparent allocator forwarder.
// Same reads, writes, calls, and return as the exe function; the disassembly is cited in
// the header (sub_e9425f0.h) and below.
// Citation: 0xe9425f0..0xe942602
void* sub_e9425f0(std::uint64_t size) {
    static_assert(sizeof(void*) == 8, "sub_e9425f0: x64 ABI, pointer-sized address space");
    // 0xe9425f0..0xe942602: sub rsp,0x28 ; call 0x392920 ; jmp short 0xE9425FD ; add rsp,0x28 ; ret
    //   dead xor eax,eax at 0xe9425fb (after the unconditional jmp); padding int3 at 0xe942602
    return native::boundary::sub_392920(size);   // 0xe9425f4  call 0x392920
}

} // namespace native

LIFT_FN(sub_e9425f0, "sub_e9425f0", 0xE9425F0, sub_e9425f0, nullptr);
