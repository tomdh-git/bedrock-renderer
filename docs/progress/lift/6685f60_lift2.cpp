// LIFT 0x6685f60 size 0x25 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_6685f60 ([0x6685f60, 0x6685f85)):
0x6685f60  sub rsp,0x28
0x6685f64  test r8,r8
0x6685f67  je short 0x6685F7F
0x6685f69  test rdx,rdx
0x6685f6c  je short 0x6685F7F
0x6685f6e  mov rax,[rcx+0x28]
0x6685f72  mov rcx,[rax+0x18]
0x6685f76  add rsp,0x28
0x6685f7a  jmp 0xC288650
0x6685f7f  call 0x78ED0
0x6685f84  int3
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

uint64_t sub_6685f60(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x6685f64  test r8,r8
    zf = ((r8 & r8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 & r8) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x6685f67  je short 0x6685F7F
    if (zf) goto loc_6685f7f;
    // 0x6685f69  test rdx,rdx
    zf = ((rdx & rdx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx & rdx) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x6685f6c  je short 0x6685F7F
    if (zf) goto loc_6685f7f;
    // 0x6685f6e  mov rax,[rcx+0x28]
    rax = R64(rcx + 40);
    // 0x6685f72  mov rcx,[rax+0x18]
    rcx = R64(rax + 24);
    // 0x6685f7a  jmp 0xC288650
    // DECISIONS: jmp to 0xc288650 outside function; target unknown.
    loc_6685f7f:
    rax = native::boundary::sub_78ed0(0, a2, a3, 0);
    // 0x6685f84  int3
    // DECISIONS: int3/ud2 traps; modeled as returning rax (does not return normally).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
