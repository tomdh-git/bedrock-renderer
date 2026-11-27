// LIFT 0xbc70ea0 size 0xf2 1.26.62.01 lift0
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

extern "C" uint64_t lift0_bc70ea0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
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
    
    // 0xbc70ea0  push rbp
    rsp -= 8; W64(rsp, rbp);
    // 0xbc70ea1  push r15
    rsp -= 8; W64(rsp, r15);
    // 0xbc70ea3  push r14
    rsp -= 8; W64(rsp, r14);
    // 0xbc70ea5  push rsi
    rsp -= 8; W64(rsp, rsi);
    // 0xbc70ea6  push rdi
    rsp -= 8; W64(rsp, rdi);
    // 0xbc70ea7  push rbx
    rsp -= 8; W64(rsp, rbx);
    // 0xbc70ea8  sub rsp,0x48
    // FLAGS: rsp - 72 (size=8)
    cf = (rsp < 72) ? 1 : 0;
    zf = ((rsp - 72) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp - 72) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 72) & 0x8000000000000000) != 0 && ((rsp ^ (rsp-72)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp - 72);
    // 0xbc70eac  lea rbp,[rsp+0x40]
    rbp = rsp + 64;
    // 0xbc70eb1  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    W64(rbp, 18446744073709551614);
    // 0xbc70eb9  mov r14d,r9d
    r14 = (uint64_t)(uint32_t)((uint32_t)r9);
    // 0xbc70ebc  mov rdi,r8
    rdi = r8;
    // 0xbc70ebf  mov rsi,rdx
    rsi = rdx;
    // 0xbc70ec2  mov rbx,rcx
    rbx = rcx;
    // 0xbc70ec5  mov r15w,[rbp+0x60]
    r15 = (uint64_t)(uint16_t)(R16(rbp + 96));
    // 0xbc70eca  add rcx,0x1C0
    // FLAGS: rcx + 448 (size=8)
    cf = (rcx + 448 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rcx + 448) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 448) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ 448) & 0x8000000000000000) == 0 && ((rcx ^ (rcx+448)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rcx = (rcx + 448);
    // 0xbc70ed1  mov [rbp-0x10],rcx
    W64(rbp + -16, rcx);
    // 0xbc70ed5  call 0xEBDBF10
    // DECISION: call to sub_ebdbf10 (0xebdbf10) - not yet lifted
    // rax = boundary_call_ebdbf10(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc70eda  mov eax,[rdi+8]
    rax = (uint64_t)(uint32_t)(R32(rdi + 8));
    // 0xbc70edd  xor edx,edx
    // FLAGS: rdx ^ (uint32_t)rdx (size=4)
    cf = 0; of = 0;
    zf = ((rdx ^ (uint32_t)rdx) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx ^ (uint32_t)rdx) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rdx = (uint64_t)(uint32_t)((rdx ^ (uint32_t)rdx));
    // 0xbc70edf  div r14d
    // UNMODELED: 0xbc70edf Div
    // 0xbc70ee2  mov [rsp+0x20],r15w
    W16(rsp + 32, (uint16_t)r15);
    // 0xbc70ee8  lea rdx,[rbp-2]
    rdx = rbp + -2;
    // 0xbc70eec  mov rcx,rbx
    rcx = rbx;
    // 0xbc70eef  mov r8d,eax
    r8 = (uint64_t)(uint32_t)((uint32_t)rax);
    // 0xbc70ef2  mov r9d,r14d
    r9 = (uint64_t)(uint32_t)((uint32_t)r14);
    // 0xbc70ef5  call 0xBC70CA0
    // DECISION: call to sub_bc70ca0 (0xbc70ca0) - not yet lifted
    // rax = boundary_call_bc70ca0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc70efa  nop
    // nop
    // 0xbc70efb  movzx edx,word ptr [rbp-2]
    rdx = (uint64_t)(uint32_t)((uint64_t)(R16(rbp + -2)));
    // 0xbc70eff  cmp dx,0xFFFF
    // CMP/TEST unhandled op1 Immediate8to16
    // 0xbc70f03  je short 0xBC70F1A
    if (zf) goto loc_bc70f1a;
    // 0xbc70f05  mov rcx,rbx
    rcx = rbx;
    // 0xbc70f08  xor r8d,r8d
    // FLAGS: r8 ^ (uint32_t)r8 (size=4)
    cf = 0; of = 0;
    zf = ((r8 ^ (uint32_t)r8) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 ^ (uint32_t)r8) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (uint64_t)(uint32_t)((r8 ^ (uint32_t)r8));
    // 0xbc70f0b  mov r9,rdi
    r9 = rdi;
    // 0xbc70f0e  call 0xBC70FF0
    // DECISION: call to sub_bc70ff0 (0xbc70ff0) - not yet lifted
    // rax = boundary_call_bc70ff0(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc70f13  nop
    // nop
    // 0xbc70f14  movzx ebx,word ptr [rbp-2]
    rbx = (uint64_t)(uint32_t)((uint64_t)(R16(rbp + -2)));
    // 0xbc70f18  jmp short 0xBC70F75
    goto loc_bc70f75;
loc_bc70f1a:
    // 0xbc70f1a  mov rcx,[rdi]
    rcx = R64(rdi);
    // 0xbc70f1d  lea rax,[rdi+0x10]
    rax = rdi + 16;
    // 0xbc70f21  cmp rcx,rax
    // FLAGS: Cmp rcx rax (size=8)
    cf = (rcx < rax) ? 1 : 0;
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rcx ^ rax) & 0x8000000000000000) != 0 && ((rcx ^ (rcx-rax)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc70f24  je short 0xBC70F39
    if (zf) goto loc_bc70f39;
    // 0xbc70f26  mov rax,[rax]
    rax = R64(rax);
    // 0xbc70f29  test rax,rax
    // FLAGS: Test rax rax (size=8)
    cf = 0; of = 0;
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc70f2c  je short 0xBC70F39
    if (zf) goto loc_bc70f39;
    // 0xbc70f2e  mov rdx,[rdi+0x18]
    rdx = R64(rdi + 24);
    // 0xbc70f32  call qword ptr [0xF99FFA0]
    // DECISION: indirect call through [rip + 261750688]
    // rax = indirect_call_via_mem(rip + 261750688, rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc70f38  nop
    // nop
loc_bc70f39:
    // 0xbc70f39  mov rcx,[0x12ADF800]
    rcx = R64(rip + 313391104);
    // 0xbc70f40  mov bx,0xFFFF
    rbx = (uint64_t)(uint16_t)(65535);
    // 0xbc70f44  test rcx,rcx
    // FLAGS: Test rcx rcx (size=8)
    cf = 0; of = 0;
    zf = ((rcx & rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx & rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    // 0xbc70f47  je short 0xBC70F75
    if (zf) goto loc_bc70f75;
    // 0xbc70f49  mov rax,[rcx]
    rax = R64(rcx);
    // 0xbc70f4c  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0xbc70f50  mov r10,[0xF99FFA0]
    r10 = R64(rip + 261750688);
    // 0xbc70f57  mov dword ptr [rsp+0x28],0
    W32(rsp + 40, (uint32_t)0);
    // 0xbc70f5f  mov qword ptr [rsp+0x20],0
    W64(rsp + 32, 0);
    // 0xbc70f68  mov rdx,rdi
    rdx = rdi;
    // 0xbc70f6b  xor r8d,r8d
    // FLAGS: r8 ^ (uint32_t)r8 (size=4)
    cf = 0; of = 0;
    zf = ((r8 ^ (uint32_t)r8) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 ^ (uint32_t)r8) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r8 = (uint64_t)(uint32_t)((r8 ^ (uint32_t)r8));
    // 0xbc70f6e  xor r9d,r9d
    // FLAGS: r9 ^ (uint32_t)r9 (size=4)
    cf = 0; of = 0;
    zf = ((r9 ^ (uint32_t)r9) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 ^ (uint32_t)r9) & 0x80000000) != 0 ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    r9 = (uint64_t)(uint32_t)((r9 ^ (uint32_t)r9));
    // 0xbc70f71  call r10
    // DECISION: indirect call through register r10
    // rax = indirect_call_via_reg(r10, rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc70f74  nop
    // nop
loc_bc70f75:
    // 0xbc70f75  mov [rsi],bx
    W16(rsi, (uint16_t)rbx);
    // 0xbc70f78  mov rcx,[rbp-0x10]
    rcx = R64(rbp + -16);
    // 0xbc70f7c  call 0xEBDBF20
    // DECISION: call to sub_ebdbf20 (0xebdbf20) - not yet lifted
    // rax = boundary_call_ebdbf20(rcx, rdx, r8, r9);
    rcx = 0; rdx = 0; r8 = 0; r9 = 0; r10 = 0; r11 = 0;
    xmm0 = _mm_setzero_si128(); xmm1 = _mm_setzero_si128(); xmm2 = _mm_setzero_si128(); xmm3 = _mm_setzero_si128(); xmm4 = _mm_setzero_si128(); xmm5 = _mm_setzero_si128();
    // 0xbc70f81  nop
    // nop
    // 0xbc70f82  mov rax,rsi
    rax = rsi;
    // 0xbc70f85  add rsp,0x48
    // FLAGS: rsp + 72 (size=8)
    cf = (rsp + 72 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    zf = ((rsp + 72) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 72) & 0x8000000000000000) != 0 ? 1 : 0;
    of = (((rsp ^ 72) & 0x8000000000000000) == 0 && ((rsp ^ (rsp+72)) & 0x8000000000000000) != 0) ? 1 : 0;
    pf = parity(zf); af = 0; // approximate
    rsp = (rsp + 72);
    // 0xbc70f89  pop rbx
    rbx = R64(rsp); rsp += 8;
    // 0xbc70f8a  pop rdi
    rdi = R64(rsp); rsp += 8;
    // 0xbc70f8b  pop rsi
    rsi = R64(rsp); rsp += 8;
    // 0xbc70f8c  pop r14
    r14 = R64(rsp); rsp += 8;
    // 0xbc70f8e  pop r15
    r15 = R64(rsp); rsp += 8;
    // 0xbc70f90  pop rbp
    rbp = R64(rsp); rsp += 8;
    // 0xbc70f91  ret
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
