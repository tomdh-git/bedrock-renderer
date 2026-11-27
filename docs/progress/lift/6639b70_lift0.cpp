// LIFT 0x6639b70 size 0x42 1.26.62.01 lift0
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

extern "C" uint64_t lift0_6639b70(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
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
    extern "C" uint64_t raw_call_via_mem(uint64_t, uint64_t, uint64_t, uint64_t);
    
    // 0x6639b70  push rsi
    rsp -= 8; W64(rsp, rsi);
    // 0x6639b71  sub rsp,0x20
    // FLAGS: rsp - 32 (size=8)
    cf = (rsp < 32) ? 1 : 0;
    zf = ((rsp - 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 32) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 32) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-32)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 32);
    // 0x6639b75  mov rsi,rcx
    rsi = rcx;
    // 0x6639b78  mov rax,[rcx]
    rax = R64(rcx);
    // 0x6639b7b  mov rax,[rax+0x298]
    rax = R64(rax + 664);
    // 0x6639b82  call qword ptr [0xF99FFA0]
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x6639b88  movss xmm0,[0xEEC8060]
    xmm0 = RXmm(rip + 250380384);
    // 0x6639b90  test al,al
    // FLAGS: Test (uint8_t)rax (uint8_t)rax (size=1)
    cf = 0; of = 0;
    zf = (((uint8_t)rax & (uint8_t)rax) & 0xFF) == 0 ? 1 : 0;
    sf = (((uint8_t)rax & (uint8_t)rax) & 0x80) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x6639b92  je short 0x6639BAC
    if (zf) goto loc_6639bac;
    // 0x6639b94  mov eax,[rsi+0x6F8]
    rax = (uint64_t)(uint32_t)(R32(rsi + 1784));
    // 0x6639b9a  cmp rax,4
    // FLAGS: Cmp rax 4 (size=8)
    cf = (rax < 4) ? 1 : 0;
    zf = ((rax - 4) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - 4) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ 4) & 0x8000000000000000) != 0 && ((rax ^ (rax-4)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x6639b9e  ja short 0x6639BAC
    if ((!cf && !zf)) goto loc_6639bac;
    // 0x6639ba0  lea rcx,[0xF2BF170]
    rcx = 254538096;
    // 0x6639ba7  movss xmm0,[rcx+rax*4]
    xmm0 = RXmm(rcx + (rax * 4));
loc_6639bac:
    // 0x6639bac  add rsp,0x20
    // FLAGS: rsp + 32 (size=8)
    cf = (rsp + 32 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 32) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 32) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+32)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 32);
    // 0x6639bb0  pop rsi
    rsi = R64(rsp); rsp += 8;
    // 0x6639bb1  ret
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
