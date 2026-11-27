// LIFT 0x34d640 size 0x39 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_34d640 ([0x34d640, 0x34d679)):
0x34d640  push rsi
0x34d641  push rdi
0x34d642  sub rsp,0x28
0x34d646  cmp byte ptr [rcx+0x19],0
0x34d64a  jne short 0x34D672
0x34d64c  mov rsi,rcx
0x34d64f  nop
0x34d650  mov rcx,[rsi+0x10]
0x34d654  call 0x34D640
0x34d659  mov rdi,[rsi]
0x34d65c  mov edx,0x30
0x34d661  mov rcx,rsi
0x34d664  call 0xE935700
0x34d669  cmp byte ptr [rdi+0x19],0
0x34d66d  mov rsi,rdi
0x34d670  je short 0x34D650
0x34d672  add rsp,0x28
0x34d676  pop rdi
0x34d677  pop rsi
0x34d678  ret
#endif

namespace native {
    // forward declarations for lift-class callees
        uint64_t sub_34d640(uint64_t, uint64_t, uint64_t, uint64_t);
        uint64_t sub_e935700(uint64_t, uint64_t, uint64_t, uint64_t);
    static inline uint8_t  R8(uint64_t a)  { (void)a; return 0; }
    static inline uint16_t R16(uint64_t a) { (void)a; return 0; }
    static inline uint32_t R32(uint64_t a) { (void)a; return 0; }
    static inline uint64_t R64(uint64_t a) { (void)a; return 0; }
    static inline void     W8(uint64_t a, uint8_t  v) { (void)a; (void)v; }
    static inline void     W16(uint64_t a, uint16_t v) { (void)a; (void)v; }
    static inline void     W32(uint64_t a, uint32_t v) { (void)a; (void)v; }
    static inline void     W64(uint64_t a, uint64_t v) { (void)a; (void)v; }

uint64_t sub_34d640(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, rip = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x34d646  cmp byte ptr [rcx+0x19],0
    // DECISIONS: cmp/test unhandled operands.
    // 0x34d64a  jne short 0x34D672
    if (!zf) goto loc_34d672;
    // 0x34d64c  mov rsi,rcx
    rsi = rcx;
    loc_34d650:
    // 0x34d650  mov rcx,[rsi+0x10]
    rcx = R64(rsi + 16);
    rax = native::sub_34d640(0, a2, a3, 0);
    // 0x34d659  mov rdi,[rsi]
    rdi = R64(rsi);
    rax = native::sub_e935700(0, 0, 0, 0);
    // 0x34d669  cmp byte ptr [rdi+0x19],0
    // DECISIONS: cmp/test unhandled operands.
    // 0x34d66d  mov rsi,rdi
    rsi = rdi;
    // 0x34d670  je short 0x34D650
    if (zf) goto loc_34d650;
    loc_34d672:
    // 0x34d678  ret
    // DECISIONS: return value not statically known; returning rax local (not a guessed constant).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
