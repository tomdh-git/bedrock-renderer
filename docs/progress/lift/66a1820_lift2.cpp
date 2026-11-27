// LIFT 0x66a1820 size 0x36 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_66a1820 ([0x66a1820, 0x66a1856)):
0x66a1820  sub rsp,0x28
0x66a1824  mov rax,[rdx]
0x66a1827  cmp rax,0xFFFFFFFFFFFFFFFF
0x66a182b  je short 0x66A1850
0x66a182d  mov rdx,[rdx+8]
0x66a1831  mov [rcx],rax
0x66a1834  mov [rcx+8],rdx
0x66a1838  test rdx,rdx
0x66a183b  setne dl
0x66a183e  test rax,rax
0x66a1841  sete al
0x66a1844  or al,dl
0x66a1846  je short 0x66A1850
0x66a1848  mov rax,rcx
0x66a184b  add rsp,0x28
0x66a184f  ret
0x66a1850  call 0x78ED0
0x66a1855  int3
#endif

namespace native {
    namespace boundary {
        uint64_t sub_78ed0(uint64_t, uint64_t, uint64_t, uint64_t);
    }
    static inline uint8_t  R8(uint64_t a)  { (void)a; return 0; }
    static inline uint16_t R16(uint64_t a) { (void)a; return 0; }
    static inline uint32_t R32(uint64_t a) { (void)a; return 0; }
    static inline uint64_t R64(uint64_t a) { (void)a; return 0; }
    static inline void     W8(uint64_t a, uint8_t  v) { (void)a; (void)v; }
    static inline void     W16(uint64_t a, uint16_t v) { (void)a; (void)v; }
    static inline void     W32(uint64_t a, uint32_t v) { (void)a; (void)v; }
    static inline void     W64(uint64_t a, uint64_t v) { (void)a; (void)v; }

uint64_t sub_66a1820(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x66a1824  mov rax,[rdx]
    rax = R64(rdx);
    // 0x66a1827  cmp rax,0xFFFFFFFFFFFFFFFF
    zf = ((rax - 18446744073709551615) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - 18446744073709551615) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rax < 18446744073709551615) ? 1 : 0;
    of = 0; // approximate
    // 0x66a182b  je short 0x66A1850
    if (zf) goto loc_66a1850;
    // 0x66a182d  mov rdx,[rdx+8]
    rdx = R64(rdx + 8);
    // 0x66a1831  mov [rcx],rax
    W64(rcx, rax);
    // 0x66a1834  mov [rcx+8],rdx
    W64(rcx + 8, rdx);
    // 0x66a1838  test rdx,rdx
    zf = ((rdx & rdx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx & rdx) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x66a183b  setne dl
    // DECISIONS: unhandled instruction; no state change (never guessed).
    // 0x66a183e  test rax,rax
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x66a1841  sete al
    // DECISIONS: unhandled instruction; no state change (never guessed).
    // 0x66a1844  or al,dl
    rax = (uint64_t)(uint8_t)((rax | (uint8_t)rdx));
    zf = ((rax | (uint8_t)rdx) & 0xFF) == 0 ? 1 : 0;
    sf = ((rax | (uint8_t)rdx) & 0x80) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x66a1846  je short 0x66A1850
    if (zf) goto loc_66a1850;
    // 0x66a1848  mov rax,rcx
    rax = rcx;
    // 0x66a184f  ret
    return rcx;
    loc_66a1850:
    rax = native::boundary::sub_78ed0(a1, 0, a3, 0);
    // 0x66a1855  int3
    // DECISIONS: int3/ud2 traps; modeled as returning rax (does not return normally).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
