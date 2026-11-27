// LIFT 0xbc5e120 size 0xc1 1.26.62.01 lift0
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

extern "C" uint64_t lift0_bc5e120(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
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
    
    // 0xbc5e120  sub rsp,0x28
    // FLAGS: rsp - 40 (size=8)
    cf = (rsp < 40) ? 1 : 0;
    zf = ((rsp - 40) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 40) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 40) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-40)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 40);
    // 0xbc5e124  mov rcx,[rcx+8]
    rcx = R64(rcx + 8);
    // 0xbc5e128  mov rax,[rcx+8]
    rax = R64(rcx + 8);
    // 0xbc5e12c  mov rcx,[rcx+0x10]
    rcx = R64(rcx + 16);
    // 0xbc5e130  cmp rax,rcx
    // FLAGS: Cmp rax rcx (size=8)
    cf = (rax < rcx) ? 1 : 0;
    zf = ((rax - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ rcx) & 0x8000000000000000) != 0 && ((rax ^ (rax-rcx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e133  je short 0xBC5E17F
    if (zf) goto loc_bc5e17f;
    // 0xbc5e135  movzx r9d,byte ptr [r8+8]
    r9 = (uint64_t)(uint32_t)((uint64_t)(R8(r8 + 8)));
    // 0xbc5e13a  cmp r9b,0xFF
    // FLAGS: Cmp (uint8_t)r9 255 (size=1)
    cf = ((uint8_t)r9 < 255) ? 1 : 0;
    zf = (((uint8_t)r9 - 255) & 0xFF) == 0 ? 1 : 0;
    sf = (((uint8_t)r9 - 255) & 0x80) != 0 ? 1 : 0;
    of = ((((uint8_t)r9 ^ 255) & 0x8000000000000000) != 0 && (((uint8_t)r9 ^ ((uint8_t)r9-255)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e13e  je short 0xBC5E179
    if (zf) goto loc_bc5e179;
    // 0xbc5e140  mov r8,[r8]
    r8 = R64(r8);
    // 0xbc5e143  jmp short 0xBC5E159
    goto loc_bc5e159;
    // 0xbc5e145  nop [rax+rax]
    // nop
loc_bc5e150:
    // 0xbc5e150  add rax,0x48
    // FLAGS: rax + 72 (size=8)
    cf = (rax + 72 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rax + 72) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax + 72) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ 72) & 0x8000000000000000) == 0 && ((rax ^ (rax+72)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rax = (rax + 72);
    // 0xbc5e154  cmp rax,rcx
    // FLAGS: Cmp rax rcx (size=8)
    cf = (rax < rcx) ? 1 : 0;
    zf = ((rax - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ rcx) & 0x8000000000000000) != 0 && ((rax ^ (rax-rcx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e157  je short 0xBC5E1A8
    if (zf) goto loc_bc5e1a8;
loc_bc5e159:
    // 0xbc5e159  cmp [rax+8],r9b
    // FLAGS: Cmp R8(rax + 8) (uint8_t)r9 (size=1)
    cf = (R8(rax + 8) < (uint8_t)r9) ? 1 : 0;
    zf = ((R8(rax + 8) - (uint8_t)r9) & 0xFF) == 0 ? 1 : 0;
    sf = ((R8(rax + 8) - (uint8_t)r9) & 0x80) != 0 ? 1 : 0;
    of = (((R8(rax + 8) ^ (uint8_t)r9) & 0x8000000000000000) != 0 && ((R8(rax + 8) ^ (R8(rax + 8)-(uint8_t)r9)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e15d  jne short 0xBC5E150
    if (!zf) goto loc_bc5e150;
    // 0xbc5e15f  cmp [rax],r8
    // FLAGS: Cmp R64(rax) r8 (size=8)
    cf = (R64(rax) < r8) ? 1 : 0;
    zf = ((R64(rax) - r8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((R64(rax) - r8) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((R64(rax) ^ r8) & 0x8000000000000000) != 0 && ((R64(rax) ^ (R64(rax)-r8)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e162  jne short 0xBC5E150
    if (!zf) goto loc_bc5e150;
    // 0xbc5e164  jmp short 0xBC5E17F
    goto loc_bc5e17f;
    // 0xbc5e166  nop [rax+rax]
    // nop
loc_bc5e170:
    // 0xbc5e170  add rax,0x48
    // FLAGS: rax + 72 (size=8)
    cf = (rax + 72 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rax + 72) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax + 72) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ 72) & 0x8000000000000000) == 0 && ((rax ^ (rax+72)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rax = (rax + 72);
    // 0xbc5e174  cmp rax,rcx
    // FLAGS: Cmp rax rcx (size=8)
    cf = (rax < rcx) ? 1 : 0;
    zf = ((rax - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ rcx) & 0x8000000000000000) != 0 && ((rax ^ (rax-rcx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e177  je short 0xBC5E1A8
    if (zf) goto loc_bc5e1a8;
loc_bc5e179:
    // 0xbc5e179  cmp byte ptr [rax+8],0xFF
    // FLAGS: Cmp R8(rax + 8) 255 (size=1)
    cf = (R8(rax + 8) < 255) ? 1 : 0;
    zf = ((R8(rax + 8) - 255) & 0xFF) == 0 ? 1 : 0;
    sf = ((R8(rax + 8) - 255) & 0x80) != 0 ? 1 : 0;
    of = (((R8(rax + 8) ^ 255) & 0x8000000000000000) != 0 && ((R8(rax + 8) ^ (R8(rax + 8)-255)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e17d  jne short 0xBC5E170
    if (!zf) goto loc_bc5e170;
loc_bc5e17f:
    // 0xbc5e17f  cmp rax,rcx
    // FLAGS: Cmp rax rcx (size=8)
    cf = (rax < rcx) ? 1 : 0;
    zf = ((rax - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ rcx) & 0x8000000000000000) != 0 && ((rax ^ (rax-rcx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e182  je short 0xBC5E1A8
    if (zf) goto loc_bc5e1a8;
    // 0xbc5e184  movzx r8d,byte ptr [rax+0x30]
    r8 = (uint64_t)(uint32_t)((uint64_t)(R8(rax + 48)));
    // 0xbc5e189  cmp r8,6
    // FLAGS: Cmp r8 6 (size=8)
    cf = (r8 < 6) ? 1 : 0;
    zf = ((r8 - 6) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 - 6) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r8 ^ 6) & 0x8000000000000000) != 0 && ((r8 ^ (r8-6)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e18d  ja short 0xBC5E1DB
    if ((!cf && !zf)) goto loc_bc5e1db;
    // 0xbc5e18f  mov rcx,[rax+0x18]
    rcx = R64(rax + 24);
    // 0xbc5e193  mov rax,[rax+0x20]
    rax = R64(rax + 32);
    // 0xbc5e197  lea r9,[0xF441354]
    r9 = rip + 256119636;
    // 0xbc5e19e  movsxd r8,[r9+r8*4]
    r8 = (int64_t)(int32_t)(R64(r9 + (r8 * 4)));
    // 0xbc5e1a2  add r8,r9
    // FLAGS: r8 + r9 (size=8)
    cf = (r8 + r9 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((r8 + r9) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 + r9) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r8 ^ r9) & 0x8000000000000000) == 0 && ((r8 ^ (r8+r9)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (r8 + r9);
    // 0xbc5e1a5  jmp r8
    // DECISION: indirect jmp through Register
loc_bc5e1a8:
    // 0xbc5e1a8  xor eax,eax
    // FLAGS: rax ^ (uint32_t)rax (size=4)
    cf = 0; of = 0;
    zf = ((rax ^ (uint32_t)rax) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax ^ (uint32_t)rax) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rax = (uint64_t)(uint32_t)((rax ^ (uint32_t)rax));
loc_bc5e1aa:
    // 0xbc5e1aa  mov [rdx+0x10],al
    W8(rdx + 16, (uint8_t)rax);
    // 0xbc5e1ad  mov rax,rdx
    rax = rdx;
    // 0xbc5e1b0  add rsp,0x28
    // FLAGS: rsp + 40 (size=8)
    cf = (rsp + 40 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 40) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 40) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 40) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+40)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 40);
    // 0xbc5e1b4  ret
    return rax;
loc_bc5e1b5:
    // 0xbc5e1b5  test rcx,rcx
    // FLAGS: Test rcx rcx (size=8)
    cf = 0; of = 0;
    zf = ((rcx & rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx & rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e1b8  setne r8b
    // UNMODELED: 0xbc5e1b8 Setne
    // 0xbc5e1bc  test rax,rax
    // FLAGS: Test rax rax (size=8)
    cf = 0; of = 0;
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc5e1bf  sete r9b
    // UNMODELED: 0xbc5e1bf Sete
    // 0xbc5e1c3  or r9b,r8b
    // FLAGS: r9 | (uint8_t)r8 (size=1)
    cf = 0; of = 0;
    zf = ((r9 | (uint8_t)r8) & 0xFF) == 0 ? 1 : 0;
    sf = ((r9 | (uint8_t)r8) & 0x80) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r9 = (uint64_t)(uint8_t)((r9 | (uint8_t)r8));
    // 0xbc5e1c6  je short 0xBC5E1D6
    if (zf) goto loc_bc5e1d6;
    // 0xbc5e1c8  sub rax,rcx
    // FLAGS: rax - rcx (size=8)
    cf = (rax < rcx) ? 1 : 0;
    zf = ((rax - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rax ^ rcx) & 0x8000000000000000) != 0 && ((rax ^ (rax-rcx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rax = (rax - rcx);
    // 0xbc5e1cb  mov [rdx],rax
    W64(rdx, rax);
    // 0xbc5e1ce  mov [rdx+8],rcx
    W64(rdx + 8, rcx);
    // 0xbc5e1d2  mov al,1
    rax = (uint64_t)(uint8_t)(1);
    // 0xbc5e1d4  jmp short 0xBC5E1AA
    goto loc_bc5e1aa;
loc_bc5e1d6:
    // 0xbc5e1d6  call 0x78ED0
    // DECISION: call to sub_78ed0 (0x78ed0) - not yet lifted
    // rax = boundary_call_78ed0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
loc_bc5e1db:
    // 0xbc5e1db  call 0x1166E0
    // DECISION: call to sub_1166e0 (0x1166e0) - not yet lifted
    // rax = boundary_call_1166e0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc5e1e0  int3
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
