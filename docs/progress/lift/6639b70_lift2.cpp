// LIFT 0x6639b70 size 0x42 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_6639b70 ([0x6639b70, 0x6639bb2)):
0x6639b70  push rsi
0x6639b71  sub rsp,0x20
0x6639b75  mov rsi,rcx
0x6639b78  mov rax,[rcx]
0x6639b7b  mov rax,[rax+0x298]
0x6639b82  call qword ptr [0xF99FFA0]
0x6639b88  movss xmm0,[0xEEC8060]
0x6639b90  test al,al
0x6639b92  je short 0x6639BAC
0x6639b94  mov eax,[rsi+0x6F8]
0x6639b9a  cmp rax,4
0x6639b9e  ja short 0x6639BAC
0x6639ba0  lea rcx,[0xF2BF170]
0x6639ba7  movss xmm0,[rcx+rax*4]
0x6639bac  add rsp,0x20
0x6639bb0  pop rsi
0x6639bb1  ret
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

uint64_t sub_6639b70(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x6639b75  mov rsi,rcx
    rsi = rcx;
    // 0x6639b78  mov rax,[rcx]
    rax = R64(rcx);
    // 0x6639b7b  mov rax,[rax+0x298]
    rax = R64(rax + 664);
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(a1, a2, a3, 0);
    // 0x6639b88  movss xmm0,[0xEEC8060]
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x6639b90  test al,al
    zf = (((uint8_t)rax & (uint8_t)rax) & 0xFF) == 0 ? 1 : 0;
    sf = (((uint8_t)rax & (uint8_t)rax) & 0x80) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x6639b92  je short 0x6639BAC
    if (zf) goto loc_6639bac;
    // 0x6639b94  mov eax,[rsi+0x6F8]
    rax = R32(rsi + 1784);
    // 0x6639b9a  cmp rax,4
    zf = ((rax - 4) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - 4) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rax < 4) ? 1 : 0;
    of = 0; // approximate
    // 0x6639b9e  ja short 0x6639BAC
    if ((!cf && !zf)) goto loc_6639bac;
    // 0x6639ba0  lea rcx,[0xF2BF170]
    rcx = 254538096;
    // 0x6639ba7  movss xmm0,[rcx+rax*4]
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    loc_6639bac:
    // 0x6639bb1  ret
    // DECISIONS: return value not statically known; returning rax local (not a guessed constant).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
