// LIFT 0x7e6d0 size 0x48 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_7e6d0 ([0x7e6d0, 0x7e718)):
0x7e6d0  push rsi
0x7e6d1  sub rsp,0x20
0x7e6d5  mov rsi,[rcx+8]
0x7e6d9  test rsi,rsi
0x7e6dc  je short 0x7E712
0x7e6de  lock dec dword ptr [rsi+8]
0x7e6e2  jne short 0x7E712
0x7e6e4  mov rax,[rsi]
0x7e6e7  mov rax,[rax]
0x7e6ea  mov rcx,rsi
0x7e6ed  call qword ptr [0xF99FFA0]
0x7e6f3  lock dec dword ptr [rsi+0xC]
0x7e6f7  jne short 0x7E712
0x7e6f9  mov rax,[rsi]
0x7e6fc  mov rax,[rax+8]
0x7e700  mov rdx,[0xF99FFA0]
0x7e707  mov rcx,rsi
0x7e70a  add rsp,0x20
0x7e70e  pop rsi
0x7e70f  jmp rdx
0x7e712  add rsp,0x20
0x7e716  pop rsi
0x7e717  ret
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

uint64_t sub_7e6d0(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, rip = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x7e6d5  mov rsi,[rcx+8]
    rsi = R64(rcx + 8);
    // 0x7e6d9  test rsi,rsi
    zf = ((rsi & rsi) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsi & rsi) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x7e6dc  je short 0x7E712
    if (zf) goto loc_7e712;
    // 0x7e6de  lock dec dword ptr [rsi+8]
    // DECISIONS: unary alu not fully modeled; register local left untouched.
    // 0x7e6e2  jne short 0x7E712
    if (!zf) goto loc_7e712;
    // 0x7e6e4  mov rax,[rsi]
    rax = R64(rsi);
    // 0x7e6e7  mov rax,[rax]
    rax = R64(rax);
    // 0x7e6ea  mov rcx,rsi
    rcx = rsi;
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rsi, a2, a3, 0);
    // 0x7e6f3  lock dec dword ptr [rsi+0xC]
    // DECISIONS: unary alu not fully modeled; register local left untouched.
    // 0x7e6f7  jne short 0x7E712
    if (!zf) goto loc_7e712;
    // 0x7e6f9  mov rax,[rsi]
    rax = R64(rsi);
    // 0x7e6fc  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0x7e700  mov rdx,[0xF99FFA0]
    rdx = R64(rip + 261750688);
    // 0x7e70e  pop rsi
    rsi = R64(rsp); rsp = (rsp + 8);
    // 0x7e70f  jmp rdx
    // DECISIONS: indirect jmp target unknown.
    loc_7e712:
    // 0x7e717  ret
    // DECISIONS: return value not statically known; returning rax local (not a guessed constant).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
