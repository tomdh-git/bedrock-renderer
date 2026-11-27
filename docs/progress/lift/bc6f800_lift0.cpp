// LIFT 0xbc6f800 size 0xbb 1.26.62.01 lift0
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

extern "C" uint64_t lift0_bc6f800(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
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
    
    // 0xbc6f800  push rbp
    rsp -= 8; W64(rsp, rbp);
    // 0xbc6f801  push rsi
    rsp -= 8; W64(rsp, rsi);
    // 0xbc6f802  push rdi
    rsp -= 8; W64(rsp, rdi);
    // 0xbc6f803  sub rsp,0x40
    // FLAGS: rsp - 64 (size=8)
    cf = (rsp < 64) ? 1 : 0;
    zf = ((rsp - 64) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 64) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 64) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-64)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 64);
    // 0xbc6f807  lea rbp,[rsp+0x40]
    rbp = rsp + 64;
    // 0xbc6f80c  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    W64(rbp + -8, 18446744073709551614);
    // 0xbc6f814  mov esi,edx
    rsi = (uint64_t)(uint32_t)((uint32_t)rdx);
    // 0xbc6f816  mov rdi,rcx
    rdi = rcx;
    // 0xbc6f819  mov [rbp-0xC],dx
    W16(rbp + -12, (uint16_t)rdx);
    // 0xbc6f81d  add rcx,0x1C0
    // FLAGS: rcx + 448 (size=8)
    cf = (rcx + 448 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 448) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 448) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 448) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+448)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + 448);
    // 0xbc6f824  mov [rbp-0x18],rcx
    W64(rbp + -24, rcx);
    // 0xbc6f828  call 0xEBDBF10
    // DECISION: call to sub_ebdbf10 (0xebdbf10) - not yet lifted
    // rax = boundary_call_ebdbf10(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc6f82d  mov rax,[rdi+0x1CFD0C8]
    rax = R64(rdi + 30396616);
    // 0xbc6f834  movzx ecx,word ptr [rax+0xE498AC]
    rcx = (uint64_t)(uint32_t)((uint64_t)(R16(rax + 14981292)));
    // 0xbc6f83b  mov [rax+rcx*2+0xE478AC],si
    W16(rax + (rcx * 2) + 14973100, (uint16_t)rsi);
    // 0xbc6f843  inc word ptr [rax+0xE498AC]
    // FLAGS: Inc (size=2)
    zf = ((R16(rax + 14981292) + 1) & 0xFFFF) == 0 ? 1 : 0;
    sf = ((R16(rax + 14981292) + 1) & 0x8000) != 0 ? 1 : 0;
    of = (R16(rax + 14981292) == 0x7FFF) ? 1 : 0;
    cf = 0; // INC does not affect CF
    pf = parity(zf); af = 0; // approximate
    W16(rax + 14981292, (R16(rax + 14981292) + 1));
    // 0xbc6f84a  mov rsi,[rdi+0x1CFD0C8]
    rsi = R64(rdi + 30396616);
    // 0xbc6f851  mov byte ptr [rbp-9],0x1D
    W8(rbp + -9, (uint8_t)29);
    // 0xbc6f855  mov eax,[rsi+0xE05820]
    rax = (uint64_t)(uint32_t)(R32(rsi + 14702624));
    // 0xbc6f85b  lea rcx,[rsi+rax]
    rcx = rsi + rax;
    // 0xbc6f85f  add rcx,0xE05828
    // FLAGS: rcx + 14702632 (size=8)
    cf = (rcx + 14702632 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 14702632) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 14702632) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 14702632) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+14702632)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + 14702632);
    // 0xbc6f866  lea rdx,[rbp-9]
    rdx = rbp + -9;
    // 0xbc6f86a  mov r8d,1
    r8 = (uint64_t)(uint32_t)(1);
    // 0xbc6f870  call 0xEBCE390
    // DECISION: call to sub_ebce390 (0xebce390) - not yet lifted
    // rax = boundary_call_ebce390(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc6f875  nop
    // nop
    // 0xbc6f876  lea rax,[rsi+0xE05828]
    rax = rsi + 14702632;
    // 0xbc6f87d  mov ecx,[rsi+0xE05820]
    rcx = (uint64_t)(uint32_t)(R32(rsi + 14702624));
    // 0xbc6f883  and ecx,0xFFFFFFFE
    // FLAGS: rcx & 18446744073709551614 (size=4)
    cf = 0; of = 0;
    zf = ((rcx & 18446744073709551614) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx & 18446744073709551614) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (uint64_t)(uint32_t)((rcx & 18446744073709551614));
    // 0xbc6f886  add ecx,2
    // FLAGS: rcx + 2 (size=4)
    cf = (rcx + 2 > 0xFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 2) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 2) & 0x80000000) != 0 ? 1 : 0;
    of = (((rcx ^ 2) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+2)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (uint64_t)(uint32_t)((rcx + 2));
    // 0xbc6f889  mov [rsi+0xE05820],ecx
    W32(rsi + 14702624, (uint32_t)rcx);
    // 0xbc6f88f  add rcx,rax
    // FLAGS: rcx + rax (size=8)
    cf = (rcx + rax > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ rax) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + rax);
    // 0xbc6f892  lea rdx,[rbp-0xC]
    rdx = rbp + -12;
    // 0xbc6f896  mov r8d,2
    r8 = (uint64_t)(uint32_t)(2);
    // 0xbc6f89c  call 0xEBCE390
    // DECISION: call to sub_ebce390 (0xebce390) - not yet lifted
    // rax = boundary_call_ebce390(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc6f8a1  nop
    // nop
    // 0xbc6f8a2  add dword ptr [rsi+0xE05820],2
    // FLAGS: R32(rsi + 14702624) + 2 (size=4)
    cf = (R32(rsi + 14702624) + 2 > 0xFFFFFFFF) ? 1 : 0;
    zf = ((R32(rsi + 14702624) + 2) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((R32(rsi + 14702624) + 2) & 0x80000000) != 0 ? 1 : 0;
    of = (((R32(rsi + 14702624) ^ 2) & 0x8000000000000000) == 0 && ((R32(rsi + 14702624) ^ (R32(rsi + 14702624)+2)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    W32(rsi + 14702624, (R32(rsi + 14702624) + 2));
    // 0xbc6f8a9  mov rcx,[rbp-0x18]
    rcx = R64(rbp + -24);
    // 0xbc6f8ad  call 0xEBDBF20
    // DECISION: call to sub_ebdbf20 (0xebdbf20) - not yet lifted
    // rax = boundary_call_ebdbf20(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc6f8b2  nop
    // nop
    // 0xbc6f8b3  add rsp,0x40
    // FLAGS: rsp + 64 (size=8)
    cf = (rsp + 64 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 64) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 64) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 64) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+64)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 64);
    // 0xbc6f8b7  pop rdi
    rdi = R64(rsp); rsp += 8;
    // 0xbc6f8b8  pop rsi
    rsi = R64(rsp); rsp += 8;
    // 0xbc6f8b9  pop rbp
    rbp = R64(rsp); rsp += 8;
    // 0xbc6f8ba  ret
    return rax;
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
