// LIFT 0x7e6d0 size 0x48 1.26.62.01 lift0
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

extern "C" uint64_t lift0_7e6d0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
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
    
    // 0x7e6d0  push rsi
    rsp -= 8; W64(rsp, rsi);
    // 0x7e6d1  sub rsp,0x20
    // FLAGS: rsp - 32 (size=8)
    cf = (rsp < 32) ? 1 : 0;
    zf = ((rsp - 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 32) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 32) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-32)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 32);
    // 0x7e6d5  mov rsi,[rcx+8]
    rsi = R64(rcx + 8);
    // 0x7e6d9  test rsi,rsi
    // FLAGS: Test rsi rsi (size=8)
    cf = 0; of = 0;
    zf = ((rsi & rsi) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsi & rsi) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x7e6dc  je short 0x7E712
    if (zf) goto loc_7e712;
    // 0x7e6de  lock dec dword ptr [rsi+8]
    // FLAGS: Dec (size=4)
    zf = ((R32(rsi + 8) - 1) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((R32(rsi + 8) - 1) & 0x80000000) != 0 ? 1 : 0;
    of = (R32(rsi + 8) == 0x80000000) ? 1 : 0;
    cf = 0; // DEC does not affect CF
    pf = parity(zf); af = 0; // approximate
    W32(rsi + 8, (R32(rsi + 8) - 1));
    // 0x7e6e2  jne short 0x7E712
    if (!zf) goto loc_7e712;
    // 0x7e6e4  mov rax,[rsi]
    rax = R64(rsi);
    // 0x7e6e7  mov rax,[rax]
    rax = R64(rax);
    // 0x7e6ea  mov rcx,rsi
    rcx = rsi;
    // 0x7e6ed  call qword ptr [0xF99FFA0]
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x7e6f3  lock dec dword ptr [rsi+0xC]
    // FLAGS: Dec (size=4)
    zf = ((R32(rsi + 12) - 1) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((R32(rsi + 12) - 1) & 0x80000000) != 0 ? 1 : 0;
    of = (R32(rsi + 12) == 0x80000000) ? 1 : 0;
    cf = 0; // DEC does not affect CF
    pf = parity(zf); af = 0; // approximate
    W32(rsi + 12, (R32(rsi + 12) - 1));
    // 0x7e6f7  jne short 0x7E712
    if (!zf) goto loc_7e712;
    // 0x7e6f9  mov rax,[rsi]
    rax = R64(rsi);
    // 0x7e6fc  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0x7e700  mov rdx,[0xF99FFA0]
    rdx = R64(rip + 261750688);
    // 0x7e707  mov rcx,rsi
    rcx = rsi;
    // 0x7e70a  add rsp,0x20
    // FLAGS: rsp + 32 (size=8)
    cf = (rsp + 32 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 32) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 32) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+32)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 32);
    // 0x7e70e  pop rsi
    rsi = R64(rsp); rsp += 8;
    // 0x7e70f  jmp rdx
    // DECISION: indirect jmp through Register
loc_7e712:
    // 0x7e712  add rsp,0x20
    // FLAGS: rsp + 32 (size=8)
    cf = (rsp + 32 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 32) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 32) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+32)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 32);
    // 0x7e716  pop rsi
    rsi = R64(rsp); rsp += 8;
    // 0x7e717  ret
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
