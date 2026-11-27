// LIFT 0x66a17c0 size 0x51 1.26.62.01 lift0
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

extern "C" uint64_t lift0_66a17c0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
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
    extern "C" uint64_t raw_call_78ed0(uint64_t, uint64_t, uint64_t, uint64_t);
    
    // 0x66a17c0  sub rsp,0x28
    // FLAGS: rsp - 40 (size=8)
    cf = (rsp < 40) ? 1 : 0;
    zf = ((rsp - 40) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 40) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 40) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-40)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 40);
    // 0x66a17c4  mov r8,[rdx]
    r8 = R64(rdx);
    // 0x66a17c7  mov rax,[rdx+8]
    rax = R64(rdx + 8);
    // 0x66a17cb  mov rdx,rax
    rdx = rax;
    // 0x66a17ce  sub rdx,r8
    // FLAGS: rdx - r8 (size=8)
    cf = (rdx < r8) ? 1 : 0;
    zf = ((rdx - r8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - r8) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ r8) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-r8)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (rdx - r8);
    // 0x66a17d1  mov r9,rdx
    r9 = rdx;
    // 0x66a17d4  sar r9,4
    // SHIFT flags approximate
    cf = 0; // approximate
    r9 = (r9 >> 4);
    // 0x66a17d8  mov r10,0xAAAAAAAAAAAAAAAB
    r10 = 12297829382473034411;
    // 0x66a17e2  imul r10,r9
    r10 = (r10 * r9);
    cf = of = 0; // approximate
    // 0x66a17e6  mov [rcx],r10
    W64(rcx, r10);
    // 0x66a17e9  cmp rdx,0xFFFFFFFFFFFFFFD0
    // FLAGS: Cmp rdx 18446744073709551568 (size=8)
    cf = (rdx < 18446744073709551568) ? 1 : 0;
    zf = ((rdx - 18446744073709551568) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 18446744073709551568) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 18446744073709551568) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-18446744073709551568)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x66a17ed  je short 0x66A180B
    if (zf) goto loc_66a180b;
    // 0x66a17ef  mov [rcx+8],r8
    W64(rcx + 8, r8);
    // 0x66a17f3  test r8,r8
    // FLAGS: Test r8 r8 (size=8)
    cf = 0; of = 0;
    zf = ((r8 & r8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 & r8) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x66a17f6  setne dl
    // UNMODELED: 0x66a17f6 Setne
    // 0x66a17f9  test rax,rax
    // FLAGS: Test rax rax (size=8)
    cf = 0; of = 0;
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x66a17fc  sete al
    // UNMODELED: 0x66a17fc Sete
    // 0x66a17ff  or al,dl
    // FLAGS: rax | (uint8_t)rdx (size=1)
    cf = 0; of = 0;
    zf = ((rax | (uint8_t)rdx) & 0xFF) == 0 ? 1 : 0;
    sf = ((rax | (uint8_t)rdx) & 0x80) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rax = (uint64_t)(uint8_t)((rax | (uint8_t)rdx));
    // 0x66a1801  je short 0x66A180B
    if (zf) goto loc_66a180b;
    // 0x66a1803  mov rax,rcx
    rax = rcx;
    // 0x66a1806  add rsp,0x28
    // FLAGS: rsp + 40 (size=8)
    cf = (rsp + 40 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 40) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 40) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 40) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+40)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 40);
    // 0x66a180a  ret
    return rax;
loc_66a180b:
    // 0x66a180b  call 0x78ED0
    // DECISION: call to sub_78ed0 (0x78ed0) - not yet lifted; modeled as external call
    rax = raw_call_78ed0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x66a1810  int3
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
