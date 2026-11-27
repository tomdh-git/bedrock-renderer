// LIFT 0x392960 size 0x35 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_392960 ([0x392960, 0x392995)):
0x392960  push rbp
0x392961  sub rsp,0x30
0x392965  lea rbp,[rsp+0x30]
0x39296a  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
0x392972  mov rdx,rcx
0x392975  mov rcx,[0x1233E1A8]
0x39297c  test rdx,rdx
0x39297f  je short 0x39298F
0x392981  mov rax,[rcx]
0x392984  mov rax,[rax+0x10]
0x392988  call qword ptr [0xF99FFA0]
0x39298e  nop
0x39298f  add rsp,0x30
0x392993  pop rbp
0x392994  ret
#endif

namespace native {
    static inline uint8_t  R8(uint64_t a)  { (void)a; return 0; }
    static inline uint16_t R16(uint64_t a) { (void)a; return 0; }
    static inline uint32_t R32(uint64_t a) { (void)a; return 0; }
    static inline uint64_t R64(uint64_t a) { (void)a; return 0; }
    static inline void     W8(uint64_t a, uint8_t  v) { (void)a; (void)v; }
    static inline void     W16(uint64_t a, uint16_t v) { (void)a; (void)v; }
    static inline void     W32(uint64_t a, uint32_t v) { (void)a; (void)v; }
    static inline void     W64(uint64_t a, uint64_t v) { (void)a; (void)v; }

    extern "C" uint64_t raw_call_via_mem(uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t sub_392960(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, rip = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x392965  lea rbp,[rsp+0x30]
    rbp = rsp + 48;
    // 0x39296a  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    W64(rbp + -8, 18446744073709551614);
    // 0x392972  mov rdx,rcx
    rdx = rcx;
    // 0x392975  mov rcx,[0x1233E1A8]
    rcx = R64(rip + 305389992);
    // 0x39297c  test rdx,rdx
    zf = ((rdx & rdx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx & rdx) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x39297f  je short 0x39298F
    if (zf) goto loc_39298f;
    // 0x392981  mov rax,[rcx]
    rax = R64(rcx);
    // 0x392984  mov rax,[rax+0x10]
    rax = R64(rax + 16);
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(0, rcx, a3, 0);
    loc_39298f:
    // 0x392994  ret
    // DECISIONS: return value not statically known; returning rax local (not a guessed constant).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
