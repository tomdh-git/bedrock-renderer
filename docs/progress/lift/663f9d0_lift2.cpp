// LIFT 0x663f9d0 size 0x54 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_663f9d0 ([0x663f9d0, 0x663fa24)):
0x663f9d0  push rsi
0x663f9d1  push rdi
0x663f9d2  sub rsp,0x28
0x663f9d6  cmp byte ptr [rdx+0x50],1
0x663f9da  jne short 0x663FA1D
0x663f9dc  mov rsi,[rdx+0x48]
0x663f9e0  test rsi,rsi
0x663f9e3  je short 0x663FA19
0x663f9e5  lock dec dword ptr [rsi+8]
0x663f9e9  jne short 0x663FA19
0x663f9eb  mov rax,[rsi]
0x663f9ee  mov rax,[rax]
0x663f9f1  mov rcx,rsi
0x663f9f4  mov rdi,rdx
0x663f9f7  call qword ptr [0xF99FFA0]
0x663f9fd  mov rdx,rdi
0x663fa00  lock dec dword ptr [rsi+0xC]
0x663fa04  jne short 0x663FA19
0x663fa06  mov rax,[rsi]
0x663fa09  mov rax,[rax+8]
0x663fa0d  mov rcx,rsi
0x663fa10  call qword ptr [0xF99FFA0]
0x663fa16  mov rdx,rdi
0x663fa19  mov byte ptr [rdx+0x50],0
0x663fa1d  add rsp,0x28
0x663fa21  pop rdi
0x663fa22  pop rsi
0x663fa23  ret
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

uint64_t sub_663f9d0(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x663f9d6  cmp byte ptr [rdx+0x50],1
    // DECISIONS: cmp/test unhandled operands.
    // 0x663f9da  jne short 0x663FA1D
    if (!zf) goto loc_663fa1d;
    // 0x663f9dc  mov rsi,[rdx+0x48]
    rsi = R64(rdx + 72);
    // 0x663f9e0  test rsi,rsi
    zf = ((rsi & rsi) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsi & rsi) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x663f9e3  je short 0x663FA19
    if (zf) goto loc_663fa19;
    // 0x663f9e5  lock dec dword ptr [rsi+8]
    // DECISIONS: unary alu not fully modeled; register local left untouched.
    // 0x663f9e9  jne short 0x663FA19
    if (!zf) goto loc_663fa19;
    // 0x663f9eb  mov rax,[rsi]
    rax = R64(rsi);
    // 0x663f9ee  mov rax,[rax]
    rax = R64(rax);
    // 0x663f9f1  mov rcx,rsi
    rcx = rsi;
    // 0x663f9f4  mov rdi,rdx
    rdi = rdx;
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rsi, a2, a3, 0);
    // 0x663f9fd  mov rdx,rdi
    rdx = rdi;
    // 0x663fa00  lock dec dword ptr [rsi+0xC]
    // DECISIONS: unary alu not fully modeled; register local left untouched.
    // 0x663fa04  jne short 0x663FA19
    if (!zf) goto loc_663fa19;
    // 0x663fa06  mov rax,[rsi]
    rax = R64(rsi);
    // 0x663fa09  mov rax,[rax+8]
    rax = R64(rax + 8);
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(0, rdi, 0, 0);
    // 0x663fa16  mov rdx,rdi
    rdx = rdi;
    loc_663fa19:
    // 0x663fa19  mov byte ptr [rdx+0x50],0
    W8(rdx + 80, (uint8_t)0);
    loc_663fa1d:
    // 0x663fa23  ret
    // DECISIONS: return value not statically known; returning rax local (not a guessed constant).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
