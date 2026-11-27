// LIFT 0x8f1e10 size 0x118 1.26.62.01 lift0
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

extern "C" uint64_t lift0_8f1e10(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
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
    extern "C" uint64_t raw_call_ae500(uint64_t, uint64_t, uint64_t, uint64_t);
    extern "C" uint64_t raw_call_eec59f0(uint64_t, uint64_t, uint64_t, uint64_t);
    extern "C" uint64_t raw_call_eec5b90(uint64_t, uint64_t, uint64_t, uint64_t);
    extern "C" uint64_t raw_call_eec5a10(uint64_t, uint64_t, uint64_t, uint64_t);
    extern "C" uint64_t raw_call_eec59e0(uint64_t, uint64_t, uint64_t, uint64_t);
    extern "C" uint64_t raw_call_eec5a00(uint64_t, uint64_t, uint64_t, uint64_t);
    extern "C" uint64_t raw_call_via_mem(uint64_t, uint64_t, uint64_t, uint64_t);
    
    // 0x8f1e10  push rbp
    rsp -= 8; W64(rsp, rbp);
    // 0x8f1e11  push rsi
    rsp -= 8; W64(rsp, rsi);
    // 0x8f1e12  push rdi
    rsp -= 8; W64(rsp, rdi);
    // 0x8f1e13  push rbx
    rsp -= 8; W64(rsp, rbx);
    // 0x8f1e14  sub rsp,0x68
    // FLAGS: rsp - 104 (size=8)
    cf = (rsp < 104) ? 1 : 0;
    zf = ((rsp - 104) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 104) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 104) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-104)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 104);
    // 0x8f1e18  lea rbp,[rsp+0x60]
    rbp = rsp + 96;
    // 0x8f1e1d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    W64(rbp, 18446744073709551614);
    // 0x8f1e25  mov rsi,rdx
    rsi = rdx;
    // 0x8f1e28  mov rdi,rcx
    rdi = rcx;
    // 0x8f1e2b  mov qword ptr [rbp-8],0
    W64(rbp + -8, 0);
    // 0x8f1e33  add rcx,0x98
    // FLAGS: rcx + 152 (size=8)
    cf = (rcx + 152 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 152) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 152) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 152) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+152)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + 152);
    // 0x8f1e3a  lea rdx,[rbp-0x40]
    rdx = rbp + -64;
    // 0x8f1e3e  call 0xAE500
    // DECISION: call to sub_ae500 (0xae500) - not yet lifted; modeled as external call
    rax = raw_call_ae500(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x8f1e43  nop
    // nop
    // 0x8f1e44  mov ebx,eax
    rbx = (uint64_t)(uint32_t)((uint32_t)rax);
    // 0x8f1e46  test al,al
    // FLAGS: Test (uint8_t)rax (uint8_t)rax (size=1)
    cf = 0; of = 0;
    zf = (((uint8_t)rax & (uint8_t)rax) & 0xFF) == 0 ? 1 : 0;
    sf = (((uint8_t)rax & (uint8_t)rax) & 0x80) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x8f1e48  je short 0x8F1E6E
    if (zf) goto loc_8f1e6e;
    // 0x8f1e4a  mov rcx,[rdi+0x88]
    rcx = R64(rdi + 136);
    // 0x8f1e51  test rcx,rcx
    // FLAGS: Test rcx rcx (size=8)
    cf = 0; of = 0;
    zf = ((rcx & rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx & rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x8f1e54  je 0x8F1F03
    if (zf) goto loc_8f1f03;
    // 0x8f1e5a  mov rax,[rcx]
    rax = R64(rcx);
    // 0x8f1e5d  mov rax,[rax+0x10]
    rax = R64(rax + 16);
    // 0x8f1e61  lea rdx,[rbp-0x40]
    rdx = rbp + -64;
    // 0x8f1e65  call qword ptr [0xF99FFA0]
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x8f1e6b  nop
    // nop
    // 0x8f1e6c  jmp short 0x8F1E78
    goto loc_8f1e78;
loc_8f1e6e:
    // 0x8f1e6e  movups xmm0,[0x128D4558]
    xmm0 = RXmm(rip + 311248216);
    // 0x8f1e75  movups [rsi],xmm0
    WXmm(rsi, xmm0);
loc_8f1e78:
    // 0x8f1e78  mov rcx,[rbp-8]
    rcx = R64(rbp + -8);
    // 0x8f1e7c  test rcx,rcx
    // FLAGS: Test rcx rcx (size=8)
    cf = 0; of = 0;
    zf = ((rcx & rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx & rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x8f1e7f  je short 0x8F1E98
    if (zf) goto loc_8f1e98;
    // 0x8f1e81  lea rax,[rbp-0x40]
    rax = rbp + -64;
    // 0x8f1e85  cmp rcx,rax
    // FLAGS: Cmp rcx rax (size=8)
    cf = (rcx < rax) ? 1 : 0;
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ rax) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x8f1e88  setne dl
    // UNMODELED: 0x8f1e88 Setne
    // 0x8f1e8b  mov rax,[rcx]
    rax = R64(rcx);
    // 0x8f1e8e  mov rax,[rax+0x20]
    rax = R64(rax + 32);
    // 0x8f1e92  call qword ptr [0xF99FFA0]
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
loc_8f1e98:
    // 0x8f1e98  test bl,bl
    // FLAGS: Test (uint8_t)rbx (uint8_t)rbx (size=1)
    cf = 0; of = 0;
    zf = (((uint8_t)rbx & (uint8_t)rbx) & 0xFF) == 0 ? 1 : 0;
    sf = (((uint8_t)rbx & (uint8_t)rbx) & 0x80) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x8f1e9a  je short 0x8F1EF7
    if (zf) goto loc_8f1ef7;
    // 0x8f1e9c  lock dec qword ptr [rdi+0x90]
    // FLAGS: Dec (size=8)
    zf = ((R64(rdi + 144) - 1) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((R64(rdi + 144) - 1) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (R64(rdi + 144) == 0x8000000000000000) ? 1 : 0;
    cf = 0; // DEC does not affect CF
    pf = parity(zf); af = 0; // approximate
    W64(rdi + 144, (R64(rdi + 144) - 1));
    // 0x8f1ea4  jne short 0x8F1EDE
    if (!zf) goto loc_8f1ede;
    // 0x8f1ea6  lea rbx,[rdi+0x300]
    rbx = rdi + 768;
    // 0x8f1ead  mov rcx,rbx
    rcx = rbx;
    // 0x8f1eb0  call 0xEEC59F0
    // DECISION: call to sub_eec59f0 (0xeec59f0) - not yet lifted; modeled as external call
    rax = raw_call_eec59f0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x8f1eb5  test eax,eax
    // FLAGS: Test (uint32_t)rax (uint32_t)rax (size=4)
    cf = 0; of = 0;
    zf = (((uint32_t)rax & (uint32_t)rax) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = (((uint32_t)rax & (uint32_t)rax) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x8f1eb7  jne short 0x8F1F09
    if (!zf) goto loc_8f1f09;
    // 0x8f1eb9  cmp dword ptr [rdi+0x34C],0x7FFFFFFF
    // FLAGS: Cmp R32(rdi + 844) 2147483647 (size=4)
    cf = (R32(rdi + 844) < 2147483647) ? 1 : 0;
    zf = ((R32(rdi + 844) - 2147483647) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((R32(rdi + 844) - 2147483647) & 0x80000000) != 0 ? 1 : 0;
    of = (((R32(rdi + 844) ^ 2147483647) & 0x8000000000000000) != 0 && ((R32(rdi + 844) ^ (R32(rdi + 844)-2147483647)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x8f1ec3  je short 0x8F1F13
    if (zf) goto loc_8f1f13;
    // 0x8f1ec5  add rdi,0x350
    // FLAGS: rdi + 848 (size=8)
    cf = (rdi + 848 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rdi + 848) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdi + 848) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdi ^ 848) & 0x8000000000000000) == 0 && ((rdi ^ (rdi+848)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdi = (rdi + 848);
    // 0x8f1ecc  mov rcx,rdi
    rcx = rdi;
    // 0x8f1ecf  call 0xEEC5B90
    // DECISION: call to sub_eec5b90 (0xeec5b90) - not yet lifted; modeled as external call
    rax = raw_call_eec5b90(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x8f1ed4  mov rcx,rbx
    rcx = rbx;
    // 0x8f1ed7  call 0xEEC5A10
    // DECISION: call to sub_eec5a10 (0xeec5a10) - not yet lifted; modeled as external call
    rax = raw_call_eec5a10(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x8f1edc  jmp short 0x8F1EED
    goto loc_8f1eed;
loc_8f1ede:
    // 0x8f1ede  add rdi,0x350
    // FLAGS: rdi + 848 (size=8)
    cf = (rdi + 848 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rdi + 848) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdi + 848) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdi ^ 848) & 0x8000000000000000) == 0 && ((rdi ^ (rdi+848)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdi = (rdi + 848);
    // 0x8f1ee5  mov rcx,rdi
    rcx = rdi;
    // 0x8f1ee8  call 0xEEC5B90
    // DECISION: call to sub_eec5b90 (0xeec5b90) - not yet lifted; modeled as external call
    rax = raw_call_eec5b90(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
loc_8f1eed:
    // 0x8f1eed  movups xmm0,[0x128D4248]
    xmm0 = RXmm(rip + 311247432);
    // 0x8f1ef4  movups [rsi],xmm0
    WXmm(rsi, xmm0);
loc_8f1ef7:
    // 0x8f1ef7  mov rax,rsi
    rax = rsi;
    // 0x8f1efa  add rsp,0x68
    // FLAGS: rsp + 104 (size=8)
    cf = (rsp + 104 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 104) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 104) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 104) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+104)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 104);
    // 0x8f1efe  pop rbx
    rbx = R64(rsp); rsp += 8;
    // 0x8f1eff  pop rdi
    rdi = R64(rsp); rsp += 8;
    // 0x8f1f00  pop rsi
    rsi = R64(rsp); rsp += 8;
    // 0x8f1f01  pop rbp
    rbp = R64(rsp); rsp += 8;
    // 0x8f1f02  ret
    return rax;
loc_8f1f03:
    // 0x8f1f03  call 0xEEC59E0
    // DECISION: call to sub_eec59e0 (0xeec59e0) - not yet lifted; modeled as external call
    rax = raw_call_eec59e0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x8f1f08  nop
    // nop
loc_8f1f09:
    // 0x8f1f09  mov ecx,5
    rcx = (uint64_t)(uint32_t)(5);
    // 0x8f1f0e  call 0xEEC5A00
    // DECISION: call to sub_eec5a00 (0xeec5a00) - not yet lifted; modeled as external call
    rax = raw_call_eec5a00(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
loc_8f1f13:
    // 0x8f1f13  mov dword ptr [rdi+0x34C],0x7FFFFFFE
    W32(rdi + 844, (uint32_t)2147483646);
    // 0x8f1f1d  mov ecx,6
    rcx = (uint64_t)(uint32_t)(6);
    // 0x8f1f22  call 0xEEC5A00
    // DECISION: call to sub_eec5a00 (0xeec5a00) - not yet lifted; modeled as external call
    rax = raw_call_eec5a00(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x8f1f27  int3
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
