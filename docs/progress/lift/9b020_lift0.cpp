// LIFT 0x9b020 size 0x181 1.26.62.01 lift0
#include <cstdint>
#include <cstring>
#include <intrin.h>
#include <immintrin.h>

// Explicit memory model (indexed by linear address).
static uint8_t mem[1<<24]; // 16MB
static inline uint8_t  R8(uint64_t a)  { return mem[a & 0xFFFFFF]; }
static inline void     W8(uint64_t a, uint8_t  v) { mem[a & 0xFFFFFF] = v; }
static inline uint16_t R16(uint64_t a) { uint16_t v; std::memcpy(&v, &mem[a & 0xFFFFFF], 2); return v; }
static inline void     W16(uint64_t a, uint16_t v) { std::memcpy(&mem[a & 0xFFFFFF], &v, 2); }
static inline uint32_t R32(uint64_t a) { uint32_t v; std::memcpy(&v, &mem[a & 0xFFFFFF], 4); return v; }
static inline void     W32(uint64_t a, uint32_t v) { std::memcpy(&mem[a & 0xFFFFFF], &v, 4); }
static inline uint64_t R64(uint64_t a) { uint64_t v; std::memcpy(&v, &mem[a & 0xFFFFFF], 8); return v; }
static inline void     W64(uint64_t a, uint64_t v) { std::memcpy(&mem[a & 0xFFFFFF], &v, 8); }
static inline __m128i  RXmm(uint64_t a) { __m128i v; std::memcpy(&v, &mem[a & 0xFFFFFF], 16); return v; }
static inline void     WXmm(uint64_t a, __m128i v) { std::memcpy(&mem[a & 0xFFFFFF], &v, 16); }
static inline int parity(uint64_t v) { v ^= v >> 32; v ^= v >> 16; v ^= v >> 8; v ^= v >> 4; v &= 0xF; return (0x6996 >> v) & 1; }

extern "C" uint64_t lift0_9b020(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    // GPRs
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, rip = 0;
    // XMMs
    __m128i xmm0 = _mm_setzero_si128(), xmm1 = _mm_setzero_si128(), xmm2 = _mm_setzero_si128(), xmm3 = _mm_setzero_si128();
    __m128i xmm4 = _mm_setzero_si128(), xmm5 = _mm_setzero_si128(), xmm6 = _mm_setzero_si128(), xmm7 = _mm_setzero_si128();
    __m128i xmm8 = _mm_setzero_si128(), xmm9 = _mm_setzero_si128(), xmm10 = _mm_setzero_si128(), xmm11 = _mm_setzero_si128();
    __m128i xmm12 = _mm_setzero_si128(), xmm13 = _mm_setzero_si128(), xmm14 = _mm_setzero_si128(), xmm15 = _mm_setzero_si128();
    // RFLAGS
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    
    // Stack frame tracking (relative to entry rsp)
    uint64_t frame_base = rsp; // entry rsp
    
    // External-call stubs (not yet lifted):
    extern "C" uint64_t raw_call_e935700(uint64_t, uint64_t, uint64_t, uint64_t);
    extern "C" uint64_t raw_call_9bc830(uint64_t, uint64_t, uint64_t, uint64_t);
    extern "C" uint64_t raw_call_via_mem(uint64_t, uint64_t, uint64_t, uint64_t);
    
    // 0x9b020  push rbp
    rsp -= 8; W64(rsp, rbp);
    // 0x9b021  push rsi
    rsp -= 8; W64(rsp, rsi);
    // 0x9b022  push rdi
    rsp -= 8; W64(rsp, rdi);
    // 0x9b023  push rbx
    rsp -= 8; W64(rsp, rbx);
    // 0x9b024  sub rsp,0x58
    // FLAGS: rsp - 88 (size=8)
    cf = (rsp < 88) ? 1 : 0;
    zf = ((rsp - 88) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 88) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 88) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-88)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 88);
    // 0x9b028  lea rbp,[rsp+0x50]
    rbp = rsp + 80;
    // 0x9b02d  movaps [rbp-0x10],xmm6
    WXmm(rbp + -16, xmm6);
    // 0x9b031  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
    W64(rbp + -24, 18446744073709551614);
    // 0x9b039  mov rsi,rcx
    rsi = rcx;
    // 0x9b03c  mov eax,[rdx]
    rax = (uint64_t)(uint32_t)(R32(rdx));
    // 0x9b03e  mov [rcx],eax
    W32(rcx, (uint32_t)rax);
    // 0x9b040  xorps xmm6,xmm6
    xmm6 = xmm6;
    // 0x9b043  movups [rcx+8],xmm6
    WXmm(rcx + 8, xmm6);
    // 0x9b047  mov rcx,[0x1233E1A8]
    rcx = R64(rip + 305389992);
    // 0x9b04e  mov rax,[rcx]
    rax = R64(rcx);
    // 0x9b051  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0x9b055  mov edx,0x50
    rdx = (uint64_t)(uint32_t)(80);
    // 0x9b05a  call qword ptr [0xF99FFA0]
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x9b060  mov rdi,rax
    rdi = rax;
    // 0x9b063  test rax,rax
    // FLAGS: Test rax rax (size=8)
    cf = 0; of = 0;
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
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
    WXmm(rsi + 24, xmm6);
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
    rdx = (uint64_t)(uint32_t)(128);
    // 0x9b0bc  call qword ptr [0xF99FFA0]
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x9b0c2  nop
    // nop
    // 0x9b0c3  mov rbx,rax
    rbx = rax;
    // 0x9b0c6  test rax,rax
    // FLAGS: Test rax rax (size=8)
    cf = 0; of = 0;
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x9b0c9  je 0x9B177
    if (zf) goto loc_9b177;
loc_9b0cf:
    // 0x9b0cf  mov rcx,[rsi+0x18]
    rcx = R64(rsi + 24);
    // 0x9b0d3  mov rdx,[rsi+0x28]
    rdx = R64(rsi + 40);
    // 0x9b0d7  sub rdx,rcx
    // FLAGS: rdx - rcx (size=8)
    cf = (rdx < rcx) ? 1 : 0;
    zf = ((rdx - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ rcx) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-rcx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (rdx - rcx);
    // 0x9b0da  je short 0x9B106
    if (zf) goto loc_9b106;
    // 0x9b0dc  cmp rdx,0x1000
    // FLAGS: Cmp rdx 4096 (size=8)
    cf = (rdx < 4096) ? 1 : 0;
    zf = ((rdx - 4096) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 4096) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 4096) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-4096)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x9b0e3  jb short 0x9B101
    if (cf) goto loc_9b101;
    // 0x9b0e5  mov rax,[rcx-8]
    rax = R64(rcx + -8);
    // 0x9b0e9  add rcx,0xFFFFFFFFFFFFFFF8
    // FLAGS: rcx + 18446744073709551608 (size=8)
    cf = (rcx + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 18446744073709551608) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+18446744073709551608)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + 18446744073709551608);
    // 0x9b0ed  sub rcx,rax
    // FLAGS: rcx - rax (size=8)
    cf = (rcx < rax) ? 1 : 0;
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ rax) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx - rax);
    // 0x9b0f0  cmp rcx,0x20
    // FLAGS: Cmp rcx 32 (size=8)
    cf = (rcx < 32) ? 1 : 0;
    zf = ((rcx - 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - 32) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 32) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-32)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x9b0f4  jae 0x9B187
    if (!cf) goto loc_9b187;
    // 0x9b0fa  add rdx,0x27
    // FLAGS: rdx + 39 (size=8)
    cf = (rdx + 39 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rdx + 39) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx + 39) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 39) & 0x8000000000000000) == 0 && ((rdx ^ (rdx+39)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (rdx + 39);
    // 0x9b0fe  mov rcx,rax
    rcx = rax;
loc_9b101:
    // 0x9b101  call 0xE935700
    // DECISION: call to sub_e935700 (0xe935700) - not yet lifted; modeled as external call
    rax = raw_call_e935700(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
loc_9b106:
    // 0x9b106  mov [rsi+0x18],rbx
    W64(rsi + 24, rbx);
    // 0x9b10a  mov rax,rbx
    rax = rbx;
    // 0x9b10d  sub rax,0xFFFFFFFFFFFFFF80
    // FLAGS: rax - 18446744073709551488 (size=8)
    cf = (rax < 18446744073709551488) ? 1 : 0;
    zf = ((rax - 18446744073709551488) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - 18446744073709551488) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ 18446744073709551488) & 0x8000000000000000) != 0 && ((rax ^ (rax-18446744073709551488)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rax = (rax - 18446744073709551488);
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
    xmm6 = RXmm(rbp + -16);
    // 0x9b15f  add rsp,0x58
    // FLAGS: rsp + 88 (size=8)
    cf = (rsp + 88 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 88) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 88) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 88) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+88)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 88);
    // 0x9b163  pop rbx
    rbx = R64(rsp); rsp += 8;
    // 0x9b164  pop rdi
    rdi = R64(rsp); rsp += 8;
    // 0x9b165  pop rsi
    rsi = R64(rsp); rsp += 8;
    // 0x9b166  pop rbp
    rbp = R64(rsp); rsp += 8;
    // 0x9b167  ret
    return rax;
loc_9b168:
    // 0x9b168  mov ecx,0x50
    rcx = (uint64_t)(uint32_t)(80);
    // 0x9b16d  call 0x9BC830
    // DECISION: call to sub_9bc830 (0x9bc830) - not yet lifted; modeled as external call
    rax = raw_call_9bc830(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x9b172  jmp 0x9B06C
    goto loc_9b06c;
loc_9b177:
    // 0x9b177  mov ecx,0x80
    rcx = (uint64_t)(uint32_t)(128);
    // 0x9b17c  call 0x9BC830
    // DECISION: call to sub_9bc830 (0x9bc830) - not yet lifted; modeled as external call
    rax = raw_call_9bc830(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x9b181  nop
    // nop
    // 0x9b182  jmp 0x9B0CF
    goto loc_9b0cf;
loc_9b187:
    // 0x9b187  mov qword ptr [rsp+0x20],0
    W64(rsp + 32, 0);
    // 0x9b190  xor ecx,ecx
    // FLAGS: rcx ^ (uint32_t)rcx (size=4)
    cf = 0; of = 0;
    zf = ((rcx ^ (uint32_t)rcx) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx ^ (uint32_t)rcx) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (uint64_t)(uint32_t)((rcx ^ (uint32_t)rcx));
    // 0x9b192  xor edx,edx
    // FLAGS: rdx ^ (uint32_t)rdx (size=4)
    cf = 0; of = 0;
    zf = ((rdx ^ (uint32_t)rdx) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx ^ (uint32_t)rdx) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (uint64_t)(uint32_t)((rdx ^ (uint32_t)rdx));
    // 0x9b194  xor r8d,r8d
    // FLAGS: r8 ^ (uint32_t)r8 (size=4)
    cf = 0; of = 0;
    zf = ((r8 ^ (uint32_t)r8) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 ^ (uint32_t)r8) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (uint64_t)(uint32_t)((r8 ^ (uint32_t)r8));
    // 0x9b197  xor r9d,r9d
    // FLAGS: r9 ^ (uint32_t)r9 (size=4)
    cf = 0; of = 0;
    zf = ((r9 ^ (uint32_t)r9) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 ^ (uint32_t)r9) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r9 = (uint64_t)(uint32_t)((r9 ^ (uint32_t)r9));
    // 0x9b19a  call qword ptr [0xF9A8C78]
    // DECISION: indirect call through [rip + 261786744]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x9b1a0  int3
    __debugbreak();
    // function end
    return rax;
}

// DECISIONS
// - Stack frame base unknown: rsp initial value not modeled.
// - Memory model wraps at 16MB: addresses >0xFFFFFF alias.
// - XMM operations partially modeled (mov, xorps only).
// - Flag computations exact for ADD/SUB/CMP/TEST/AND/OR/XOR/INC/DEC/NEG/SHL/SHR/SAR; approximate for others.
// - Call targets: direct calls to known lift-set callees use lifted names; others marked DECISION.
// - Indirect calls/jumps: target unknown at lift time (DECISION).
