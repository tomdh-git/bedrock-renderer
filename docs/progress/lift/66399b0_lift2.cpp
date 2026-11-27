// LIFT 0x66399b0 size 0x34 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_66399b0 ([0x66399b0, 0x66399e4)):
0x66399b0  push rsi
0x66399b1  sub rsp,0x20
0x66399b5  mov rsi,rcx
0x66399b8  mov rax,[rcx]
0x66399bb  mov rax,[rax+0x230]
0x66399c2  call qword ptr [0xF99FFA0]
0x66399c8  mov ecx,eax
0x66399ca  mov al,2
0x66399cc  test cl,cl
0x66399ce  je short 0x66399DE
0x66399d0  mov rax,[rsi+0x358]
0x66399d7  movzx eax,byte ptr [rax+0x7E6]
0x66399de  add rsp,0x20
0x66399e2  pop rsi
0x66399e3  ret
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

uint64_t sub_66399b0(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x66399b5  mov rsi,rcx
    rsi = rcx;
    // 0x66399b8  mov rax,[rcx]
    rax = R64(rcx);
    // 0x66399bb  mov rax,[rax+0x230]
    rax = R64(rax + 560);
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(a1, a2, a3, 0);
    // 0x66399c8  mov ecx,eax
    rcx = (uint32_t)rax;
    // 0x66399ca  mov al,2
    rax = 2;
    // 0x66399cc  test cl,cl
    zf = (((uint8_t)rcx & (uint8_t)rcx) & 0xFF) == 0 ? 1 : 0;
    sf = (((uint8_t)rcx & (uint8_t)rcx) & 0x80) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x66399ce  je short 0x66399DE
    if (zf) goto loc_66399de;
    // 0x66399d0  mov rax,[rsi+0x358]
    rax = R64(rsi + 856);
    // 0x66399d7  movzx eax,byte ptr [rax+0x7E6]
    rax = R64(rax + 2022);
    loc_66399de:
    // 0x66399e3  ret
    // DECISIONS: return value not statically known; returning rax local (not a guessed constant).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
