// LIFT 0x66a17c0 size 0x51 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_66a17c0 ([0x66a17c0, 0x66a1811)):
0x66a17c0  sub rsp,0x28
0x66a17c4  mov r8,[rdx]
0x66a17c7  mov rax,[rdx+8]
0x66a17cb  mov rdx,rax
0x66a17ce  sub rdx,r8
0x66a17d1  mov r9,rdx
0x66a17d4  sar r9,4
0x66a17d8  mov r10,0xAAAAAAAAAAAAAAAB
0x66a17e2  imul r10,r9
0x66a17e6  mov [rcx],r10
0x66a17e9  cmp rdx,0xFFFFFFFFFFFFFFD0
0x66a17ed  je short 0x66A180B
0x66a17ef  mov [rcx+8],r8
0x66a17f3  test r8,r8
0x66a17f6  setne dl
0x66a17f9  test rax,rax
0x66a17fc  sete al
0x66a17ff  or al,dl
0x66a1801  je short 0x66A180B
0x66a1803  mov rax,rcx
0x66a1806  add rsp,0x28
0x66a180a  ret
0x66a180b  call 0x78ED0
0x66a1810  int3
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

uint64_t sub_66a17c0(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x66a17c4  mov r8,[rdx]
    r8 = R64(rdx);
    // 0x66a17c7  mov rax,[rdx+8]
    rax = R64(rdx + 8);
    // 0x66a17cb  mov rdx,rax
    rdx = rax;
    // 0x66a17ce  sub rdx,r8
    rdx = (rdx - r8);
    zf = ((rdx - r8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - r8) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < r8) ? 1 : 0;
    // 0x66a17d1  mov r9,rdx
    r9 = rdx;
    // 0x66a17d4  sar r9,4
    // DECISIONS: shift not fully modeled; register local left untouched.
    // 0x66a17d8  mov r10,0xAAAAAAAAAAAAAAAB
    r10 = 12297829382473034411;
    // 0x66a17e2  imul r10,r9
    // DECISIONS: imul not fully modeled; register local left untouched.
    // 0x66a17e6  mov [rcx],r10
    W64(rcx, r10);
    // 0x66a17e9  cmp rdx,0xFFFFFFFFFFFFFFD0
    zf = ((rdx - 18446744073709551568) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 18446744073709551568) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < 18446744073709551568) ? 1 : 0;
    of = 0; // approximate
    // 0x66a17ed  je short 0x66A180B
    if (zf) goto loc_66a180b;
    // 0x66a17ef  mov [rcx+8],r8
    W64(rcx + 8, r8);
    // 0x66a17f3  test r8,r8
    zf = ((r8 & r8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 & r8) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x66a17f6  setne dl
    // DECISIONS: unhandled instruction; no state change (never guessed).
    // 0x66a17f9  test rax,rax
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x66a17fc  sete al
    // DECISIONS: unhandled instruction; no state change (never guessed).
    // 0x66a17ff  or al,dl
    rax = (uint64_t)(uint8_t)((rax | (uint8_t)rdx));
    zf = ((rax | (uint8_t)rdx) & 0xFF) == 0 ? 1 : 0;
    sf = ((rax | (uint8_t)rdx) & 0x80) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x66a1801  je short 0x66A180B
    if (zf) goto loc_66a180b;
    // 0x66a1803  mov rax,rcx
    rax = rcx;
    // 0x66a180a  ret
    return rcx;
    loc_66a180b:
    rax = native::boundary::sub_78ed0(a1, 0, 0, rdx);
    // 0x66a1810  int3
    // DECISIONS: int3/ud2 traps; modeled as returning rax (does not return normally).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
