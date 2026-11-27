// LIFT 0x6639bc0 size 0x24 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_6639bc0 ([0x6639bc0, 0x6639be4)):
0x6639bc0  push rsi
0x6639bc1  sub rsp,0x20
0x6639bc5  mov rsi,rdx
0x6639bc8  lea rcx,[0x12AE0E90]
0x6639bcf  mov [rdx],rcx
0x6639bd2  call 0xEEC7570
0x6639bd7  mov [rsi+8],rax
0x6639bdb  mov rax,rsi
0x6639bde  add rsp,0x20
0x6639be2  pop rsi
0x6639be3  ret
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

    extern "C" uint64_t raw_call_eec7570(uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t sub_6639bc0(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x6639bc5  mov rsi,rdx
    rsi = rdx;
    // 0x6639bc8  lea rcx,[0x12AE0E90]
    rcx = 313396880;
    // 0x6639bcf  mov [rdx],rcx
    W64(rdx, rcx);
    // DECISION: call to 0xeec7570 unknown - modeled as external call raw_call_eec7570(rcx, rdx, r8, r9)
    rax = raw_call_eec7570(313396880, a2, a3, 0);
    // 0x6639bd7  mov [rsi+8],rax
    W64(rsi + 8, rax);
    // 0x6639bdb  mov rax,rsi
    rax = rsi;
    // 0x6639be3  ret
    return rsi;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
