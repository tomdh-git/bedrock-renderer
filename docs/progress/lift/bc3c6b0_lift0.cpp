// LIFT 0xbc3c6b0 size 0xcb 1.26.62.01 lift0
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

extern "C" uint64_t lift0_bc3c6b0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
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
    
    // 0xbc3c6b0  push rsi
    rsp -= 8; W64(rsp, rsi);
    // 0xbc3c6b1  push rdi
    rsp -= 8; W64(rsp, rdi);
    // 0xbc3c6b2  sub rsp,0x28
    // FLAGS: rsp - 40 (size=8)
    cf = (rsp < 40) ? 1 : 0;
    zf = ((rsp - 40) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 40) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 40) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-40)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 40);
    // 0xbc3c6b6  cmp rcx,1
    // FLAGS: Cmp rcx 1 (size=8)
    cf = (rcx < 1) ? 1 : 0;
    zf = ((rcx - 1) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - 1) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 1) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-1)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc3c6ba  jne 0xBC3C75A
    if (!zf) goto loc_bc3c75a;
    // 0xbc3c6c0  mov rsi,r8
    rsi = r8;
    // 0xbc3c6c3  mov rcx,[r8+0x60]
    rcx = R64(r8 + 96);
    // 0xbc3c6c7  test rcx,rcx
    // FLAGS: Test rcx rcx (size=8)
    cf = 0; of = 0;
    zf = ((rcx & rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx & rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc3c6ca  je short 0xBC3C70B
    if (zf) goto loc_bc3c70b;
    // 0xbc3c6cc  mov rdx,[rsi+0x70]
    rdx = R64(rsi + 112);
    // 0xbc3c6d0  sub rdx,rcx
    // FLAGS: rdx - rcx (size=8)
    cf = (rdx < rcx) ? 1 : 0;
    zf = ((rdx - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ rcx) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-rcx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (rdx - rcx);
    // 0xbc3c6d3  cmp rdx,0x1000
    // FLAGS: Cmp rdx 4096 (size=8)
    cf = (rdx < 4096) ? 1 : 0;
    zf = ((rdx - 4096) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 4096) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 4096) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-4096)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc3c6da  jb short 0xBC3C6F4
    if (cf) goto loc_bc3c6f4;
    // 0xbc3c6dc  mov rax,[rcx-8]
    rax = R64(rcx + -8);
    // 0xbc3c6e0  add rcx,0xFFFFFFFFFFFFFFF8
    // FLAGS: rcx + 18446744073709551608 (size=8)
    cf = (rcx + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 18446744073709551608) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+18446744073709551608)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + 18446744073709551608);
    // 0xbc3c6e4  sub rcx,rax
    // FLAGS: rcx - rax (size=8)
    cf = (rcx < rax) ? 1 : 0;
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ rax) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx - rax);
    // 0xbc3c6e7  cmp rcx,0x20
    // FLAGS: Cmp rcx 32 (size=8)
    cf = (rcx < 32) ? 1 : 0;
    zf = ((rcx - 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - 32) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 32) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-32)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc3c6eb  jae short 0xBC3C761
    if (!cf) goto loc_bc3c761;
    // 0xbc3c6ed  add rdx,0x27
    // FLAGS: rdx + 39 (size=8)
    cf = (rdx + 39 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rdx + 39) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx + 39) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 39) & 0x8000000000000000) == 0 && ((rdx ^ (rdx+39)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (rdx + 39);
    // 0xbc3c6f1  mov rcx,rax
    rcx = rax;
loc_bc3c6f4:
    // 0xbc3c6f4  lea rdi,[rsi+0x60]
    rdi = rsi + 96;
    // 0xbc3c6f8  call 0xE935700
    // DECISION: call to sub_e935700 (0xe935700) - not yet lifted
    // rax = boundary_call_e935700(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc3c6fd  xorps xmm0,xmm0
    xmm0 = xmm0;
    // 0xbc3c700  movups [rdi],xmm0
    WXmm(rdi, xmm0);
    // 0xbc3c703  mov qword ptr [rdi+0x10],0
    W64(rdi + 16, 0);
loc_bc3c70b:
    // 0xbc3c70b  mov rax,[rsi+0x50]
    rax = R64(rsi + 80);
    // 0xbc3c70f  cmp rax,0x10
    // FLAGS: Cmp rax 16 (size=8)
    cf = (rax < 16) ? 1 : 0;
    zf = ((rax - 16) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - 16) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ 16) & 0x8000000000000000) != 0 && ((rax ^ (rax-16)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc3c713  jb short 0xBC3C746
    if (cf) goto loc_bc3c746;
    // 0xbc3c715  mov rcx,[rsi+0x38]
    rcx = R64(rsi + 56);
    // 0xbc3c719  lea rdx,[rax+1]
    rdx = rax + 1;
    // 0xbc3c71d  cmp rdx,0x1000
    // FLAGS: Cmp rdx 4096 (size=8)
    cf = (rdx < 4096) ? 1 : 0;
    zf = ((rdx - 4096) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 4096) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 4096) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-4096)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc3c724  jb short 0xBC3C741
    if (cf) goto loc_bc3c741;
    // 0xbc3c726  mov r8,[rcx-8]
    r8 = R64(rcx + -8);
    // 0xbc3c72a  add rcx,0xFFFFFFFFFFFFFFF8
    // FLAGS: rcx + 18446744073709551608 (size=8)
    cf = (rcx + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 18446744073709551608) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+18446744073709551608)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + 18446744073709551608);
    // 0xbc3c72e  sub rcx,r8
    // FLAGS: rcx - r8 (size=8)
    cf = (rcx < r8) ? 1 : 0;
    zf = ((rcx - r8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - r8) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ r8) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-r8)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx - r8);
    // 0xbc3c731  cmp rcx,0x20
    // FLAGS: Cmp rcx 32 (size=8)
    cf = (rcx < 32) ? 1 : 0;
    zf = ((rcx - 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - 32) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 32) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-32)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc3c735  jae short 0xBC3C761
    if (!cf) goto loc_bc3c761;
    // 0xbc3c737  add rax,0x28
    // FLAGS: rax + 40 (size=8)
    cf = (rax + 40 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rax + 40) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax + 40) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ 40) & 0x8000000000000000) == 0 && ((rax ^ (rax+40)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rax = (rax + 40);
    // 0xbc3c73b  mov rdx,rax
    rdx = rax;
    // 0xbc3c73e  mov rcx,r8
    rcx = r8;
loc_bc3c741:
    // 0xbc3c741  call 0xE935700
    // DECISION: call to sub_e935700 (0xe935700) - not yet lifted
    // rax = boundary_call_e935700(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
loc_bc3c746:
    // 0xbc3c746  mov qword ptr [rsi+0x48],0
    W64(rsi + 72, 0);
    // 0xbc3c74e  mov qword ptr [rsi+0x50],0xF
    W64(rsi + 80, 15);
    // 0xbc3c756  mov byte ptr [rsi+0x38],0
    W8(rsi + 56, (uint8_t)0);
loc_bc3c75a:
    // 0xbc3c75a  add rsp,0x28
    // FLAGS: rsp + 40 (size=8)
    cf = (rsp + 40 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 40) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 40) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 40) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+40)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 40);
    // 0xbc3c75e  pop rdi
    rdi = R64(rsp); rsp += 8;
    // 0xbc3c75f  pop rsi
    rsi = R64(rsp); rsp += 8;
    // 0xbc3c760  ret
    return rax;
loc_bc3c761:
    // 0xbc3c761  mov qword ptr [rsp+0x20],0
    W64(rsp + 32, 0);
    // 0xbc3c76a  xor ecx,ecx
    // FLAGS: rcx ^ (uint32_t)rcx (size=4)
    cf = 0; of = 0;
    zf = ((rcx ^ (uint32_t)rcx) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx ^ (uint32_t)rcx) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (uint64_t)(uint32_t)((rcx ^ (uint32_t)rcx));
    // 0xbc3c76c  xor edx,edx
    // FLAGS: rdx ^ (uint32_t)rdx (size=4)
    cf = 0; of = 0;
    zf = ((rdx ^ (uint32_t)rdx) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx ^ (uint32_t)rdx) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (uint64_t)(uint32_t)((rdx ^ (uint32_t)rdx));
    // 0xbc3c76e  xor r8d,r8d
    // FLAGS: r8 ^ (uint32_t)r8 (size=4)
    cf = 0; of = 0;
    zf = ((r8 ^ (uint32_t)r8) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 ^ (uint32_t)r8) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (uint64_t)(uint32_t)((r8 ^ (uint32_t)r8));
    // 0xbc3c771  xor r9d,r9d
    // FLAGS: r9 ^ (uint32_t)r9 (size=4)
    cf = 0; of = 0;
    zf = ((r9 ^ (uint32_t)r9) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 ^ (uint32_t)r9) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r9 = (uint64_t)(uint32_t)((r9 ^ (uint32_t)r9));
    // 0xbc3c774  call qword ptr [0xF9A8C78]
    // DECISION: indirect call through [rip + 261786744]
    // rax = indirect_call_via_mem(rip + 261786744, rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc3c77a  int3
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
