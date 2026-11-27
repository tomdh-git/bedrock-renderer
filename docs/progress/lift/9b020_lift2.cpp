// LIFT 0x9b020 size 0x181 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_9b020 ([0x9b020, 0x9b1a1)):
0x9b020  push rbp
0x9b021  push rsi
0x9b022  push rdi
0x9b023  push rbx
0x9b024  sub rsp,0x58
0x9b028  lea rbp,[rsp+0x50]
0x9b02d  movaps [rbp-0x10],xmm6
0x9b031  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
0x9b039  mov rsi,rcx
0x9b03c  mov eax,[rdx]
0x9b03e  mov [rcx],eax
0x9b040  xorps xmm6,xmm6
0x9b043  movups [rcx+8],xmm6
0x9b047  mov rcx,[0x1233E1A8]
0x9b04e  mov rax,[rcx]
0x9b051  mov rax,[rax+8]
0x9b055  mov edx,0x50
0x9b05a  call qword ptr [0xF99FFA0]
0x9b060  mov rdi,rax
0x9b063  test rax,rax
0x9b066  je 0x9B168
0x9b06c  lea rax,[rsi+8]
0x9b070  mov [rbp-0x28],rax
0x9b074  mov [rdi],rdi
0x9b077  mov [rdi+8],rdi
0x9b07b  mov [rsi+8],rdi
0x9b07f  lea rax,[rsi+0x18]
0x9b083  mov [rbp-0x20],rax
0x9b087  movups [rsi+0x18],xmm6
0x9b08b  mov qword ptr [rsi+0x28],0
0x9b093  mov qword ptr [rsi+0x30],7
0x9b09b  mov qword ptr [rsi+0x38],8
0x9b0a3  mov dword ptr [rsi],0x3F800000
0x9b0a9  mov rcx,[0x1233E1A8]
0x9b0b0  mov rax,[rcx]
0x9b0b3  mov rax,[rax+8]
0x9b0b7  mov edx,0x80
0x9b0bc  call qword ptr [0xF99FFA0]
0x9b0c2  nop
0x9b0c3  mov rbx,rax
0x9b0c6  test rax,rax
0x9b0c9  je 0x9B177
0x9b0cf  mov rcx,[rsi+0x18]
0x9b0d3  mov rdx,[rsi+0x28]
0x9b0d7  sub rdx,rcx
0x9b0da  je short 0x9B106
0x9b0dc  cmp rdx,0x1000
0x9b0e3  jb short 0x9B101
0x9b0e5  mov rax,[rcx-8]
0x9b0e9  add rcx,0xFFFFFFFFFFFFFFF8
0x9b0ed  sub rcx,rax
0x9b0f0  cmp rcx,0x20
0x9b0f4  jae 0x9B187
0x9b0fa  add rdx,0x27
0x9b0fe  mov rcx,rax
0x9b101  call 0xE935700
0x9b106  mov [rsi+0x18],rbx
0x9b10a  mov rax,rbx
0x9b10d  sub rax,0xFFFFFFFFFFFFFF80
0x9b111  mov [rsi+0x20],rax
0x9b115  mov [rsi+0x28],rax
0x9b119  mov [rbx],rdi
0x9b11c  mov [rbx+8],rdi
0x9b120  mov [rbx+0x10],rdi
0x9b124  mov [rbx+0x18],rdi
0x9b128  mov [rbx+0x20],rdi
0x9b12c  mov [rbx+0x28],rdi
0x9b130  mov [rbx+0x30],rdi
0x9b134  mov [rbx+0x38],rdi
0x9b138  mov [rbx+0x40],rdi
0x9b13c  mov [rbx+0x48],rdi
0x9b140  mov [rbx+0x50],rdi
0x9b144  mov [rbx+0x58],rdi
0x9b148  mov [rbx+0x60],rdi
0x9b14c  mov [rbx+0x68],rdi
0x9b150  mov [rbx+0x70],rdi
0x9b154  mov [rbx+0x78],rdi
0x9b158  mov rax,rsi
0x9b15b  movaps xmm6,[rbp-0x10]
0x9b15f  add rsp,0x58
0x9b163  pop rbx
0x9b164  pop rdi
0x9b165  pop rsi
0x9b166  pop rbp
0x9b167  ret
0x9b168  mov ecx,0x50
0x9b16d  call 0x9BC830
0x9b172  jmp 0x9B06C
0x9b177  mov ecx,0x80
0x9b17c  call 0x9BC830
0x9b181  nop
0x9b182  jmp 0x9B0CF
0x9b187  mov qword ptr [rsp+0x20],0
0x9b190  xor ecx,ecx
0x9b192  xor edx,edx
0x9b194  xor r8d,r8d
0x9b197  xor r9d,r9d
0x9b19a  call qword ptr [0xF9A8C78]
0x9b1a0  int3
#endif

namespace native {
    // forward declarations for lift-class callees
        uint64_t sub_e935700(uint64_t, uint64_t, uint64_t, uint64_t);
    namespace boundary {
        uint64_t sub_9bc830(uint64_t, uint64_t, uint64_t, uint64_t);
    }
    static inline uint8_t  R8(uint64_t a)  { (void)a; return 0; }
    static inline uint16_t R16(uint64_t a) { (void)a; return 0; }
    static inline uint32_t R32(uint64_t a) { (void)a; return 0; }
    static inline uint64_t R64(uint64_t a) { (void)a; return 0; }
    static inline void     W8(uint64_t a, uint8_t  v) { (void)a; (void)v; }
    static inline void     W16(uint64_t a, uint16_t v) { (void)a; (void)v; }
    static inline void     W32(uint64_t a, uint32_t v) { (void)a; (void)v; }
    static inline void     W64(uint64_t a, uint64_t v) { (void)a; (void)v; }

    extern "C" uint64_t raw_call_via_mem(uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t sub_9b020(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, rip = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0x9b028  lea rbp,[rsp+0x50]
    rbp = rsp + 80;
    // 0x9b02d  movaps [rbp-0x10],xmm6
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x9b031  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
    W64(rbp + -24, 18446744073709551614);
    // 0x9b039  mov rsi,rcx
    rsi = rcx;
    // 0x9b03c  mov eax,[rdx]
    rax = R32(rdx);
    // 0x9b03e  mov [rcx],eax
    W32(rcx, (uint32_t)rax);
    // 0x9b040  xorps xmm6,xmm6
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x9b043  movups [rcx+8],xmm6
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x9b047  mov rcx,[0x1233E1A8]
    rcx = R64(rip + 305389992);
    // 0x9b04e  mov rax,[rcx]
    rax = R64(rcx);
    // 0x9b051  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0x9b055  mov edx,0x50
    rdx = 80;
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(0, a2, a3, 0);
    // 0x9b060  mov rdi,rax
    rdi = rax;
    // 0x9b063  test rax,rax
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x9b066  je 0x9B168
    if (zf) goto loc_9b168;
    loc_9b06c:
    // 0x9b06c  lea rax,[rsi+8]
    rax = rsi + 8;
    // 0x9b070  mov [rbp-0x28],rax
    W64(rbp + -40, rax);
    // 0x9b074  mov [rdi],rdi
    W64(rdi, rdi);
    // 0x9b077  mov [rdi+8],rdi
    W64(rdi + 8, rdi);
    // 0x9b07b  mov [rsi+8],rdi
    W64(rsi + 8, rdi);
    // 0x9b07f  lea rax,[rsi+0x18]
    rax = rsi + 24;
    // 0x9b083  mov [rbp-0x20],rax
    W64(rbp + -32, rax);
    // 0x9b087  movups [rsi+0x18],xmm6
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x9b08b  mov qword ptr [rsi+0x28],0
    W64(rsi + 40, 0);
    // 0x9b093  mov qword ptr [rsi+0x30],7
    W64(rsi + 48, 7);
    // 0x9b09b  mov qword ptr [rsi+0x38],8
    W64(rsi + 56, 8);
    // 0x9b0a3  mov dword ptr [rsi],0x3F800000
    W32(rsi, (uint32_t)1065353216);
    // 0x9b0a9  mov rcx,[0x1233E1A8]
    rcx = R64(rip + 305389992);
    // 0x9b0b0  mov rax,[rcx]
    rax = R64(rcx);
    // 0x9b0b3  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0x9b0b7  mov edx,0x80
    rdx = 128;
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(0, 0, 0, 0);
    // 0x9b0c3  mov rbx,rax
    rbx = rax;
    // 0x9b0c6  test rax,rax
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x9b0c9  je 0x9B177
    if (zf) goto loc_9b177;
    loc_9b0cf:
    // 0x9b0cf  mov rcx,[rsi+0x18]
    rcx = R64(rsi + 24);
    // 0x9b0d3  mov rdx,[rsi+0x28]
    rdx = R64(rsi + 40);
    // 0x9b0d7  sub rdx,rcx
    rdx = (rdx - rcx);
    zf = ((rdx - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < rcx) ? 1 : 0;
    // 0x9b0da  je short 0x9B106
    if (zf) goto loc_9b106;
    // 0x9b0dc  cmp rdx,0x1000
    zf = ((rdx - 4096) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 4096) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < 4096) ? 1 : 0;
    of = 0; // approximate
    // 0x9b0e3  jb short 0x9B101
    if (cf) goto loc_9b101;
    // 0x9b0e5  mov rax,[rcx-8]
    rax = R64(rcx + -8);
    // 0x9b0e9  add rcx,0xFFFFFFFFFFFFFFF8
    rcx = (rcx + 18446744073709551608);
    zf = ((rcx + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x9b0ed  sub rcx,rax
    rcx = (rcx - rax);
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx < rax) ? 1 : 0;
    // 0x9b0f0  cmp rcx,0x20
    zf = ((rcx - 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - 32) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx < 32) ? 1 : 0;
    of = 0; // approximate
    // 0x9b0f4  jae 0x9B187
    if (!cf) goto loc_9b187;
    // 0x9b0fa  add rdx,0x27
    rdx = (rdx + 39);
    zf = ((rdx + 39) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx + 39) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx + 39 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x9b0fe  mov rcx,rax
    rcx = rax;
    loc_9b101:
    rax = native::sub_e935700(rax, 0, 0, 0);
    loc_9b106:
    // 0x9b106  mov [rsi+0x18],rbx
    W64(rsi + 24, rbx);
    // 0x9b10a  mov rax,rbx
    rax = rbx;
    // 0x9b10d  sub rax,0xFFFFFFFFFFFFFF80
    rax = (rax - 18446744073709551488);
    zf = ((rax - 18446744073709551488) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - 18446744073709551488) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rax < 18446744073709551488) ? 1 : 0;
    // 0x9b111  mov [rsi+0x20],rax
    W64(rsi + 32, rax);
    // 0x9b115  mov [rsi+0x28],rax
    W64(rsi + 40, rax);
    // 0x9b119  mov [rbx],rdi
    W64(rbx, rdi);
    // 0x9b11c  mov [rbx+8],rdi
    W64(rbx + 8, rdi);
    // 0x9b120  mov [rbx+0x10],rdi
    W64(rbx + 16, rdi);
    // 0x9b124  mov [rbx+0x18],rdi
    W64(rbx + 24, rdi);
    // 0x9b128  mov [rbx+0x20],rdi
    W64(rbx + 32, rdi);
    // 0x9b12c  mov [rbx+0x28],rdi
    W64(rbx + 40, rdi);
    // 0x9b130  mov [rbx+0x30],rdi
    W64(rbx + 48, rdi);
    // 0x9b134  mov [rbx+0x38],rdi
    W64(rbx + 56, rdi);
    // 0x9b138  mov [rbx+0x40],rdi
    W64(rbx + 64, rdi);
    // 0x9b13c  mov [rbx+0x48],rdi
    W64(rbx + 72, rdi);
    // 0x9b140  mov [rbx+0x50],rdi
    W64(rbx + 80, rdi);
    // 0x9b144  mov [rbx+0x58],rdi
    W64(rbx + 88, rdi);
    // 0x9b148  mov [rbx+0x60],rdi
    W64(rbx + 96, rdi);
    // 0x9b14c  mov [rbx+0x68],rdi
    W64(rbx + 104, rdi);
    // 0x9b150  mov [rbx+0x70],rdi
    W64(rbx + 112, rdi);
    // 0x9b154  mov [rbx+0x78],rdi
    W64(rbx + 120, rdi);
    // 0x9b158  mov rax,rsi
    rax = rsi;
    // 0x9b15b  movaps xmm6,[rbp-0x10]
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x9b15f  add rsp,0x58
    rsp = (rsp + 88);
    zf = ((rsp + 88) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 88) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rsp + 88 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x9b167  ret
    return rsi;
    loc_9b168:
    // 0x9b168  mov ecx,0x50
    rcx = 80;
    rax = native::boundary::sub_9bc830(0, 0, 0, 0);
    // 0x9b172  jmp 0x9B06C
    goto loc_9b06c;
    loc_9b177:
    // 0x9b177  mov ecx,0x80
    rcx = 128;
    rax = native::boundary::sub_9bc830(0, 0, 0, 0);
    // 0x9b182  jmp 0x9B0CF
    goto loc_9b0cf;
    loc_9b187:
    // 0x9b187  mov qword ptr [rsp+0x20],0
    W64(rsp + 32, 0);
    // DECISION: indirect call through [rip + 261786744]
    rax = raw_call_via_mem(0, 0, 0, 0);
    // 0x9b1a0  int3
    // DECISIONS: int3/ud2 traps; modeled as returning rax (does not return normally).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
