// LIFT 0x76b30 size 0x218 1.26.62.01 lift0
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

extern "C" uint64_t lift0_76b30(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
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
    extern "C" uint64_t raw_call_75740(uint64_t, uint64_t, uint64_t, uint64_t);
    extern "C" uint64_t raw_call_via_mem(uint64_t, uint64_t, uint64_t, uint64_t);
    
    // 0x76b30  push r14
    rsp -= 8; W64(rsp, r14);
    // 0x76b32  push rsi
    rsp -= 8; W64(rsp, rsi);
    // 0x76b33  push rdi
    rsp -= 8; W64(rsp, rdi);
    // 0x76b34  push rbx
    rsp -= 8; W64(rsp, rbx);
    // 0x76b35  sub rsp,0x28
    // FLAGS: rsp - 40 (size=8)
    cf = (rsp < 40) ? 1 : 0;
    zf = ((rsp - 40) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 40) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 40) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-40)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 40);
    // 0x76b39  mov rsi,r8
    rsi = r8;
    // 0x76b3c  mov rbx,rcx
    rbx = rcx;
    // 0x76b3f  mov rcx,[rcx]
    rcx = R64(rcx);
    // 0x76b42  mov rax,[rbx+8]
    rax = R64(rbx + 8);
    // 0x76b46  mov r8,rax
    r8 = rax;
    // 0x76b49  sub r8,rcx
    // FLAGS: r8 - rcx (size=8)
    cf = (r8 < rcx) ? 1 : 0;
    zf = ((r8 - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r8 ^ rcx) & 0x8000000000000000) != 0 && ((r8 ^ (r8-rcx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (r8 - rcx);
    // 0x76b4c  mov r9,r8
    r9 = r8;
    // 0x76b4f  sar r9,3
    // SHIFT flags approximate
    cf = 0; // approximate
    r9 = (r9 >> 3);
    // 0x76b53  cmp r9,rdx
    // FLAGS: Cmp r9 rdx (size=8)
    cf = (r9 < rdx) ? 1 : 0;
    zf = ((r9 - rdx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 - rdx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r9 ^ rdx) & 0x8000000000000000) != 0 && ((r9 ^ (r9-rdx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76b56  jae short 0x76BBE
    if (!cf) goto loc_76bbe;
    // 0x76b58  mov rax,rdx
    rax = rdx;
    // 0x76b5b  shr rax,0x3D
    // SHIFT flags approximate
    cf = 0; // approximate
    rax = (rax >> 61);
    // 0x76b5f  jne 0x76D29
    if (!zf) goto loc_76d29;
    // 0x76b65  lea rdi,[rdx*8]
    rdi = (rdx * 8);
    // 0x76b6d  cmp rdx,0x200
    // FLAGS: Cmp rdx 512 (size=8)
    cf = (rdx < 512) ? 1 : 0;
    zf = ((rdx - 512) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 512) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 512) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-512)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76b74  jb short 0x76BDD
    if (cf) goto loc_76bdd;
    // 0x76b76  mov rax,0x1FFFFFFFFFFFFFFC
    rax = 2305843009213693948;
    // 0x76b80  cmp rdx,rax
    // FLAGS: Cmp rdx rax (size=8)
    cf = (rdx < rax) ? 1 : 0;
    zf = ((rdx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ rax) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76b83  jae 0x76D29
    if (!cf) goto loc_76d29;
    // 0x76b89  lea r14,[rdi+0x27]
    r14 = rdi + 39;
    // 0x76b8d  mov rcx,[0x1233E1A8]
    rcx = R64(rip + 305389992);
    // 0x76b94  mov rax,[rcx]
    rax = R64(rcx);
    // 0x76b97  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0x76b9b  mov rdx,r14
    rdx = r14;
    // 0x76b9e  call qword ptr [0xF99FFA0]
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x76ba4  test rax,rax
    // FLAGS: Test rax rax (size=8)
    cf = 0; of = 0;
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76ba7  je 0x76D16
    if (zf) goto loc_76d16;
loc_76bad:
    // 0x76bad  mov r14,rax
    r14 = rax;
    // 0x76bb0  add r14,0x27
    // FLAGS: r14 + 39 (size=8)
    cf = (r14 + 39 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((r14 + 39) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r14 + 39) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r14 ^ 39) & 0x8000000000000000) == 0 && ((r14 ^ (r14+39)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r14 = (r14 + 39);
    // 0x76bb4  and r14,0xFFFFFFFFFFFFFFE0
    // FLAGS: r14 & 18446744073709551584 (size=8)
    cf = 0; of = 0;
    zf = ((r14 & 18446744073709551584) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r14 & 18446744073709551584) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r14 = (r14 & 18446744073709551584);
    // 0x76bb8  mov [r14-8],rax
    W64(r14 + -8, rax);
    // 0x76bbc  jmp short 0x76C00
    goto loc_76c00;
loc_76bbe:
    // 0x76bbe  cmp rcx,rax
    // FLAGS: Cmp rcx rax (size=8)
    cf = (rcx < rax) ? 1 : 0;
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ rax) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76bc1  je 0x76CFC
    if (zf) goto loc_76cfc;
    // 0x76bc7  add r8,0xFFFFFFFFFFFFFFF8
    // FLAGS: r8 + 18446744073709551608 (size=8)
    cf = (r8 + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((r8 + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r8 ^ 18446744073709551608) & 0x8000000000000000) == 0 && ((r8 ^ (r8+18446744073709551608)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (r8 + 18446744073709551608);
    // 0x76bcb  cmp r8,0x18
    // FLAGS: Cmp r8 24 (size=8)
    cf = (r8 < 24) ? 1 : 0;
    zf = ((r8 - 24) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 - 24) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r8 ^ 24) & 0x8000000000000000) != 0 && ((r8 ^ (r8-24)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76bcf  jae 0x76CAE
    if (!cf) goto loc_76cae;
    // 0x76bd5  mov rdx,rcx
    rdx = rcx;
    // 0x76bd8  jmp 0x76CF0
    goto loc_76cf0;
loc_76bdd:
    // 0x76bdd  mov rcx,[0x1233E1A8]
    rcx = R64(rip + 305389992);
    // 0x76be4  mov rax,[rcx]
    rax = R64(rcx);
    // 0x76be7  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0x76beb  mov rdx,rdi
    rdx = rdi;
    // 0x76bee  call qword ptr [0xF99FFA0]
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x76bf4  mov r14,rax
    r14 = rax;
    // 0x76bf7  test rax,rax
    // FLAGS: Test rax rax (size=8)
    cf = 0; of = 0;
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76bfa  je 0x76D06
    if (zf) goto loc_76d06;
loc_76c00:
    // 0x76c00  mov rcx,[rbx]
    rcx = R64(rbx);
    // 0x76c03  mov rdx,[rbx+0x10]
    rdx = R64(rbx + 16);
    // 0x76c07  sub rdx,rcx
    // FLAGS: rdx - rcx (size=8)
    cf = (rdx < rcx) ? 1 : 0;
    zf = ((rdx - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ rcx) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-rcx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (rdx - rcx);
    // 0x76c0a  je short 0x76C36
    if (zf) goto loc_76c36;
    // 0x76c0c  cmp rdx,0x1000
    // FLAGS: Cmp rdx 4096 (size=8)
    cf = (rdx < 4096) ? 1 : 0;
    zf = ((rdx - 4096) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 4096) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 4096) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-4096)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76c13  jb short 0x76C31
    if (cf) goto loc_76c31;
    // 0x76c15  mov rax,[rcx-8]
    rax = R64(rcx + -8);
    // 0x76c19  add rcx,0xFFFFFFFFFFFFFFF8
    // FLAGS: rcx + 18446744073709551608 (size=8)
    cf = (rcx + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 18446744073709551608) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+18446744073709551608)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + 18446744073709551608);
    // 0x76c1d  sub rcx,rax
    // FLAGS: rcx - rax (size=8)
    cf = (rcx < rax) ? 1 : 0;
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ rax) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx - rax);
    // 0x76c20  cmp rcx,0x20
    // FLAGS: Cmp rcx 32 (size=8)
    cf = (rcx < 32) ? 1 : 0;
    zf = ((rcx - 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - 32) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 32) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-32)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76c24  jae 0x76D2E
    if (!cf) goto loc_76d2e;
    // 0x76c2a  add rdx,0x27
    // FLAGS: rdx + 39 (size=8)
    cf = (rdx + 39 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rdx + 39) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx + 39) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 39) & 0x8000000000000000) == 0 && ((rdx ^ (rdx+39)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (rdx + 39);
    // 0x76c2e  mov rcx,rax
    rcx = rax;
loc_76c31:
    // 0x76c31  call 0xE935700
    // DECISION: call to sub_e935700 (0xe935700) - not yet lifted; modeled as external call
    rax = raw_call_e935700(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
loc_76c36:
    // 0x76c36  mov [rbx],r14
    W64(rbx, r14);
    // 0x76c39  lea rax,[r14+rdi]
    rax = r14 + rdi;
    // 0x76c3d  mov [rbx+8],rax
    W64(rbx + 8, rax);
    // 0x76c41  mov [rbx+0x10],rax
    W64(rbx + 16, rax);
    // 0x76c45  add rdi,0xFFFFFFFFFFFFFFF8
    // FLAGS: rdi + 18446744073709551608 (size=8)
    cf = (rdi + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rdi + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdi + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdi ^ 18446744073709551608) & 0x8000000000000000) == 0 && ((rdi ^ (rdi+18446744073709551608)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdi = (rdi + 18446744073709551608);
    // 0x76c49  cmp rdi,0x18
    // FLAGS: Cmp rdi 24 (size=8)
    cf = (rdi < 24) ? 1 : 0;
    zf = ((rdi - 24) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdi - 24) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdi ^ 24) & 0x8000000000000000) != 0 && ((rdi ^ (rdi-24)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76c4d  jae short 0x76C54
    if (!cf) goto loc_76c54;
    // 0x76c4f  mov rcx,r14
    rcx = r14;
    // 0x76c52  jmp short 0x76CA0
    goto loc_76ca0;
loc_76c54:
    // 0x76c54  shr rdi,3
    // SHIFT flags approximate
    cf = 0; // approximate
    rdi = (rdi >> 3);
    // 0x76c58  inc rdi
    // FLAGS: Inc (size=8)
    zf = ((rdi + 1) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdi + 1) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (rdi == 0x7FFFFFFFFFFFFFFF) ? 1 : 0;
    cf = 0; // INC does not affect CF
    pf = parity(zf); af = 0; // approximate
    rdi = (rdi + 1);
    // 0x76c5b  mov rdx,rdi
    rdx = rdi;
    // 0x76c5e  and rdx,0xFFFFFFFFFFFFFFFC
    // FLAGS: rdx & 18446744073709551612 (size=8)
    cf = 0; of = 0;
    zf = ((rdx & 18446744073709551612) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx & 18446744073709551612) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (rdx & 18446744073709551612);
    // 0x76c62  lea rcx,[r14+rdx*8]
    rcx = r14 + (rdx * 8);
    // 0x76c66  movq xmm0,rsi
    xmm0 = rsi;
    // 0x76c6b  pshufd xmm0,xmm0,0x44
    // UNMODELED: 0x76c6b Pshufd
    // 0x76c70  xor r8d,r8d
    // FLAGS: r8 ^ (uint32_t)r8 (size=4)
    cf = 0; of = 0;
    zf = ((r8 ^ (uint32_t)r8) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 ^ (uint32_t)r8) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (uint64_t)(uint32_t)((r8 ^ (uint32_t)r8));
    // 0x76c73  nop [rax+rax]
    // nop
loc_76c80:
    // 0x76c80  movdqu [r14+r8*8],xmm0
    WXmm(r14 + (r8 * 8), xmm0);
    // 0x76c86  movdqu [r14+r8*8+0x10],xmm0
    WXmm(r14 + (r8 * 8) + 16, xmm0);
    // 0x76c8d  add r8,4
    // FLAGS: r8 + 4 (size=8)
    cf = (r8 + 4 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((r8 + 4) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 + 4) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r8 ^ 4) & 0x8000000000000000) == 0 && ((r8 ^ (r8+4)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (r8 + 4);
    // 0x76c91  cmp rdx,r8
    // FLAGS: Cmp rdx r8 (size=8)
    cf = (rdx < r8) ? 1 : 0;
    zf = ((rdx - r8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - r8) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ r8) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-r8)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76c94  jne short 0x76C80
    if (!zf) goto loc_76c80;
    // 0x76c96  cmp rdi,rdx
    // FLAGS: Cmp rdi rdx (size=8)
    cf = (rdi < rdx) ? 1 : 0;
    zf = ((rdi - rdx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdi - rdx) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdi ^ rdx) & 0x8000000000000000) != 0 && ((rdi ^ (rdi-rdx)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76c99  je short 0x76CFC
    if (zf) goto loc_76cfc;
    // 0x76c9b  nop [rax+rax]
    // nop
loc_76ca0:
    // 0x76ca0  mov [rcx],rsi
    W64(rcx, rsi);
    // 0x76ca3  add rcx,8
    // FLAGS: rcx + 8 (size=8)
    cf = (rcx + 8 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 8) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 8) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+8)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + 8);
    // 0x76ca7  cmp rcx,rax
    // FLAGS: Cmp rcx rax (size=8)
    cf = (rcx < rax) ? 1 : 0;
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ rax) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76caa  jne short 0x76CA0
    if (!zf) goto loc_76ca0;
    // 0x76cac  jmp short 0x76CFC
    goto loc_76cfc;
loc_76cae:
    // 0x76cae  shr r8,3
    // SHIFT flags approximate
    cf = 0; // approximate
    r8 = (r8 >> 3);
    // 0x76cb2  inc r8
    // FLAGS: Inc (size=8)
    zf = ((r8 + 1) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 + 1) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (r8 == 0x7FFFFFFFFFFFFFFF) ? 1 : 0;
    cf = 0; // INC does not affect CF
    pf = parity(zf); af = 0; // approximate
    r8 = (r8 + 1);
    // 0x76cb5  mov r9,r8
    r9 = r8;
    // 0x76cb8  and r9,0xFFFFFFFFFFFFFFFC
    // FLAGS: r9 & 18446744073709551612 (size=8)
    cf = 0; of = 0;
    zf = ((r9 & 18446744073709551612) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 & 18446744073709551612) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r9 = (r9 & 18446744073709551612);
    // 0x76cbc  lea rdx,[rcx+r9*8]
    rdx = rcx + (r9 * 8);
    // 0x76cc0  movq xmm0,rsi
    xmm0 = rsi;
    // 0x76cc5  pshufd xmm0,xmm0,0x44
    // UNMODELED: 0x76cc5 Pshufd
    // 0x76cca  xor r10d,r10d
    // FLAGS: r10 ^ (uint32_t)r10 (size=4)
    cf = 0; of = 0;
    zf = ((r10 ^ (uint32_t)r10) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r10 ^ (uint32_t)r10) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r10 = (uint64_t)(uint32_t)((r10 ^ (uint32_t)r10));
    // 0x76ccd  nop [rax]
    // nop
loc_76cd0:
    // 0x76cd0  movdqu [rcx+r10*8],xmm0
    WXmm(rcx + (r10 * 8), xmm0);
    // 0x76cd6  movdqu [rcx+r10*8+0x10],xmm0
    WXmm(rcx + (r10 * 8) + 16, xmm0);
    // 0x76cdd  add r10,4
    // FLAGS: r10 + 4 (size=8)
    cf = (r10 + 4 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((r10 + 4) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r10 + 4) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r10 ^ 4) & 0x8000000000000000) == 0 && ((r10 ^ (r10+4)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r10 = (r10 + 4);
    // 0x76ce1  cmp r9,r10
    // FLAGS: Cmp r9 r10 (size=8)
    cf = (r9 < r10) ? 1 : 0;
    zf = ((r9 - r10) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 - r10) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r9 ^ r10) & 0x8000000000000000) != 0 && ((r9 ^ (r9-r10)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76ce4  jne short 0x76CD0
    if (!zf) goto loc_76cd0;
    // 0x76ce6  cmp r8,r9
    // FLAGS: Cmp r8 r9 (size=8)
    cf = (r8 < r9) ? 1 : 0;
    zf = ((r8 - r9) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 - r9) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((r8 ^ r9) & 0x8000000000000000) != 0 && ((r8 ^ (r8-r9)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76ce9  je short 0x76CFC
    if (zf) goto loc_76cfc;
    // 0x76ceb  nop [rax+rax]
    // nop
loc_76cf0:
    // 0x76cf0  mov [rdx],rsi
    W64(rdx, rsi);
    // 0x76cf3  add rdx,8
    // FLAGS: rdx + 8 (size=8)
    cf = (rdx + 8 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rdx + 8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx + 8) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ 8) & 0x8000000000000000) == 0 && ((rdx ^ (rdx+8)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (rdx + 8);
    // 0x76cf7  cmp rdx,rax
    // FLAGS: Cmp rdx rax (size=8)
    cf = (rdx < rax) ? 1 : 0;
    zf = ((rdx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rdx ^ rax) & 0x8000000000000000) != 0 && ((rdx ^ (rdx-rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0x76cfa  jne short 0x76CF0
    if (!zf) goto loc_76cf0;
loc_76cfc:
    // 0x76cfc  add rsp,0x28
    // FLAGS: rsp + 40 (size=8)
    cf = (rsp + 40 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 40) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 40) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 40) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+40)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 40);
    // 0x76d00  pop rbx
    rbx = R64(rsp); rsp += 8;
    // 0x76d01  pop rdi
    rdi = R64(rsp); rsp += 8;
    // 0x76d02  pop rsi
    rsi = R64(rsp); rsp += 8;
    // 0x76d03  pop r14
    r14 = R64(rsp); rsp += 8;
    // 0x76d05  ret
    return rax;
loc_76d06:
    // 0x76d06  mov rcx,rdi
    rcx = rdi;
    // 0x76d09  call 0x9BC830
    // DECISION: call to sub_9bc830 (0x9bc830) - not yet lifted; modeled as external call
    rax = raw_call_9bc830(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x76d0e  xor r14d,r14d
    // FLAGS: r14 ^ (uint32_t)r14 (size=4)
    cf = 0; of = 0;
    zf = ((r14 ^ (uint32_t)r14) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r14 ^ (uint32_t)r14) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r14 = (uint64_t)(uint32_t)((r14 ^ (uint32_t)r14));
    // 0x76d11  jmp 0x76C00
    goto loc_76c00;
loc_76d16:
    // 0x76d16  mov rcx,r14
    rcx = r14;
    // 0x76d19  mov r14,rax
    r14 = rax;
    // 0x76d1c  call 0x9BC830
    // DECISION: call to sub_9bc830 (0x9bc830) - not yet lifted; modeled as external call
    rax = raw_call_9bc830(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x76d21  mov rax,r14
    rax = r14;
    // 0x76d24  jmp 0x76BAD
    goto loc_76bad;
loc_76d29:
    // 0x76d29  call 0x75740
    // DECISION: call to sub_75740 (0x75740) - not yet lifted; modeled as external call
    rax = raw_call_75740(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
loc_76d2e:
    // 0x76d2e  mov qword ptr [rsp+0x20],0
    W64(rsp + 32, 0);
    // 0x76d37  xor ecx,ecx
    // FLAGS: rcx ^ (uint32_t)rcx (size=4)
    cf = 0; of = 0;
    zf = ((rcx ^ (uint32_t)rcx) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx ^ (uint32_t)rcx) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (uint64_t)(uint32_t)((rcx ^ (uint32_t)rcx));
    // 0x76d39  xor edx,edx
    // FLAGS: rdx ^ (uint32_t)rdx (size=4)
    cf = 0; of = 0;
    zf = ((rdx ^ (uint32_t)rdx) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx ^ (uint32_t)rdx) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (uint64_t)(uint32_t)((rdx ^ (uint32_t)rdx));
    // 0x76d3b  xor r8d,r8d
    // FLAGS: r8 ^ (uint32_t)r8 (size=4)
    cf = 0; of = 0;
    zf = ((r8 ^ (uint32_t)r8) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 ^ (uint32_t)r8) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (uint64_t)(uint32_t)((r8 ^ (uint32_t)r8));
    // 0x76d3e  xor r9d,r9d
    // FLAGS: r9 ^ (uint32_t)r9 (size=4)
    cf = 0; of = 0;
    zf = ((r9 ^ (uint32_t)r9) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 ^ (uint32_t)r9) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r9 = (uint64_t)(uint32_t)((r9 ^ (uint32_t)r9));
    // 0x76d41  call qword ptr [0xF9A8C78]
    // DECISION: indirect call through [rip + 261786744]
    rax = raw_call_via_mem(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0x76d47  int3
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
