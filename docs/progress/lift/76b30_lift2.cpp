// LIFT 0x76b30 size 0x218 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_76b30 ([0x76b30, 0x76d48)):
0x76b30  push r14
0x76b32  push rsi
0x76b33  push rdi
0x76b34  push rbx
0x76b35  sub rsp,0x28
0x76b39  mov rsi,r8
0x76b3c  mov rbx,rcx
0x76b3f  mov rcx,[rcx]
0x76b42  mov rax,[rbx+8]
0x76b46  mov r8,rax
0x76b49  sub r8,rcx
0x76b4c  mov r9,r8
0x76b4f  sar r9,3
0x76b53  cmp r9,rdx
0x76b56  jae short 0x76BBE
0x76b58  mov rax,rdx
0x76b5b  shr rax,0x3D
0x76b5f  jne 0x76D29
0x76b65  lea rdi,[rdx*8]
0x76b6d  cmp rdx,0x200
0x76b74  jb short 0x76BDD
0x76b76  mov rax,0x1FFFFFFFFFFFFFFC
0x76b80  cmp rdx,rax
0x76b83  jae 0x76D29
0x76b89  lea r14,[rdi+0x27]
0x76b8d  mov rcx,[0x1233E1A8]
0x76b94  mov rax,[rcx]
0x76b97  mov rax,[rax+8]
0x76b9b  mov rdx,r14
0x76b9e  call qword ptr [0xF99FFA0]
0x76ba4  test rax,rax
0x76ba7  je 0x76D16
0x76bad  mov r14,rax
0x76bb0  add r14,0x27
0x76bb4  and r14,0xFFFFFFFFFFFFFFE0
0x76bb8  mov [r14-8],rax
0x76bbc  jmp short 0x76C00
0x76bbe  cmp rcx,rax
0x76bc1  je 0x76CFC
0x76bc7  add r8,0xFFFFFFFFFFFFFFF8
0x76bcb  cmp r8,0x18
0x76bcf  jae 0x76CAE
0x76bd5  mov rdx,rcx
0x76bd8  jmp 0x76CF0
0x76bdd  mov rcx,[0x1233E1A8]
0x76be4  mov rax,[rcx]
0x76be7  mov rax,[rax+8]
0x76beb  mov rdx,rdi
0x76bee  call qword ptr [0xF99FFA0]
0x76bf4  mov r14,rax
0x76bf7  test rax,rax
0x76bfa  je 0x76D06
0x76c00  mov rcx,[rbx]
0x76c03  mov rdx,[rbx+0x10]
0x76c07  sub rdx,rcx
0x76c0a  je short 0x76C36
0x76c0c  cmp rdx,0x1000
0x76c13  jb short 0x76C31
0x76c15  mov rax,[rcx-8]
0x76c19  add rcx,0xFFFFFFFFFFFFFFF8
0x76c1d  sub rcx,rax
0x76c20  cmp rcx,0x20
0x76c24  jae 0x76D2E
0x76c2a  add rdx,0x27
0x76c2e  mov rcx,rax
0x76c31  call 0xE935700
0x76c36  mov [rbx],r14
0x76c39  lea rax,[r14+rdi]
0x76c3d  mov [rbx+8],rax
0x76c41  mov [rbx+0x10],rax
0x76c45  add rdi,0xFFFFFFFFFFFFFFF8
0x76c49  cmp rdi,0x18
0x76c4d  jae short 0x76C54
0x76c4f  mov rcx,r14
0x76c52  jmp short 0x76CA0
0x76c54  shr rdi,3
0x76c58  inc rdi
0x76c5b  mov rdx,rdi
0x76c5e  and rdx,0xFFFFFFFFFFFFFFFC
0x76c62  lea rcx,[r14+rdx*8]
0x76c66  movq xmm0,rsi
0x76c6b  pshufd xmm0,xmm0,0x44
0x76c70  xor r8d,r8d
0x76c73  nop [rax+rax]
0x76c80  movdqu [r14+r8*8],xmm0
0x76c86  movdqu [r14+r8*8+0x10],xmm0
0x76c8d  add r8,4
0x76c91  cmp rdx,r8
0x76c94  jne short 0x76C80
0x76c96  cmp rdi,rdx
0x76c99  je short 0x76CFC
0x76c9b  nop [rax+rax]
0x76ca0  mov [rcx],rsi
0x76ca3  add rcx,8
0x76ca7  cmp rcx,rax
0x76caa  jne short 0x76CA0
0x76cac  jmp short 0x76CFC
0x76cae  shr r8,3
0x76cb2  inc r8
0x76cb5  mov r9,r8
0x76cb8  and r9,0xFFFFFFFFFFFFFFFC
0x76cbc  lea rdx,[rcx+r9*8]
0x76cc0  movq xmm0,rsi
0x76cc5  pshufd xmm0,xmm0,0x44
0x76cca  xor r10d,r10d
0x76ccd  nop [rax]
0x76cd0  movdqu [rcx+r10*8],xmm0
0x76cd6  movdqu [rcx+r10*8+0x10],xmm0
0x76cdd  add r10,4
0x76ce1  cmp r9,r10
0x76ce4  jne short 0x76CD0
0x76ce6  cmp r8,r9
0x76ce9  je short 0x76CFC
0x76ceb  nop [rax+rax]
0x76cf0  mov [rdx],rsi
0x76cf3  add rdx,8
0x76cf7  cmp rdx,rax
0x76cfa  jne short 0x76CF0
0x76cfc  add rsp,0x28
0x76d00  pop rbx
0x76d01  pop rdi
0x76d02  pop rsi
0x76d03  pop r14
0x76d05  ret
0x76d06  mov rcx,rdi
0x76d09  call 0x9BC830
0x76d0e  xor r14d,r14d
0x76d11  jmp 0x76C00
0x76d16  mov rcx,r14
0x76d19  mov r14,rax
0x76d1c  call 0x9BC830
0x76d21  mov rax,r14
0x76d24  jmp 0x76BAD
0x76d29  call 0x75740
0x76d2e  mov qword ptr [rsp+0x20],0
0x76d37  xor ecx,ecx
0x76d39  xor edx,edx
0x76d3b  xor r8d,r8d
0x76d3e  xor r9d,r9d
0x76d41  call qword ptr [0xF9A8C78]
0x76d47  int3
#endif

namespace native {
    // forward declarations for lift-class callees
        uint64_t sub_e935700(uint64_t, uint64_t, uint64_t, uint64_t);
    namespace boundary {
        uint64_t sub_9bc830(uint64_t, uint64_t, uint64_t, uint64_t);
        uint64_t sub_75740(uint64_t, uint64_t, uint64_t, uint64_t);
    }
    static inline uint8_t  R8(uint64_t a)  { (void)a; return 0; }
    static inline uint16_t R16(uint64_t a) { (void)a; return 0; }
    static inline uint32_t R32(uint64_t a) { (void)a; return 0; }
    static inline uint64_t R64(uint64_t a) { (void)a; return 0; }
    static inline void     W8(uint64_t a, uint8_t  v) { (void)a; (void)v; }
    static inline void     W16(uint64_t a, uint16_t v) { (void)a; (void)v; }
    static inline void     W32(uint64_t a, uint32_t v) { (void)a; (void)v; }
    static inline void     W64(uint64_t a, uint64_t v) { (void)a; (void)v; }

    extern "C" uint64_t raw_call_via_mem(uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t sub_76b30(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, rip = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
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
    r8 = (r8 - rcx);
    zf = ((r8 - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (r8 < rcx) ? 1 : 0;
    // 0x76b4c  mov r9,r8
    r9 = r8;
    // 0x76b4f  sar r9,3
    // DECISIONS: shift not fully modeled; register local left untouched.
    // 0x76b53  cmp r9,rdx
    zf = ((r9 - rdx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 - rdx) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (r9 < rdx) ? 1 : 0;
    of = 0; // approximate
    // 0x76b56  jae short 0x76BBE
    if (!cf) goto loc_76bbe;
    // 0x76b58  mov rax,rdx
    rax = rdx;
    // 0x76b5b  shr rax,0x3D
    // DECISIONS: shift not fully modeled; register local left untouched.
    // 0x76b5f  jne 0x76D29
    if (!zf) goto loc_76d29;
    // 0x76b65  lea rdi,[rdx*8]
    rdi = (rdx * 8);
    // 0x76b6d  cmp rdx,0x200
    zf = ((rdx - 512) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 512) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < 512) ? 1 : 0;
    of = 0; // approximate
    // 0x76b74  jb short 0x76BDD
    if (cf) goto loc_76bdd;
    // 0x76b76  mov rax,0x1FFFFFFFFFFFFFFC
    rax = 2305843009213693948;
    // 0x76b80  cmp rdx,rax
    zf = ((rdx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < rax) ? 1 : 0;
    of = 0; // approximate
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
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(0, r14, 0, r8);
    // 0x76ba4  test rax,rax
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x76ba7  je 0x76D16
    if (zf) goto loc_76d16;
    loc_76bad:
    // 0x76bad  mov r14,rax
    r14 = rax;
    // 0x76bb0  add r14,0x27
    r14 = (r14 + 39);
    zf = ((r14 + 39) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r14 + 39) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (r14 + 39 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x76bb4  and r14,0xFFFFFFFFFFFFFFE0
    r14 = (r14 & 18446744073709551584);
    zf = ((r14 & 18446744073709551584) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r14 & 18446744073709551584) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x76bb8  mov [r14-8],rax
    W64(r14 + -8, rax);
    // 0x76bbc  jmp short 0x76C00
    goto loc_76c00;
    loc_76bbe:
    // 0x76bbe  cmp rcx,rax
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx < rax) ? 1 : 0;
    of = 0; // approximate
    // 0x76bc1  je 0x76CFC
    if (zf) goto loc_76cfc;
    // 0x76bc7  add r8,0xFFFFFFFFFFFFFFF8
    r8 = (r8 + 18446744073709551608);
    zf = ((r8 + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (r8 + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x76bcb  cmp r8,0x18
    zf = ((r8 - 24) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 - 24) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (r8 < 24) ? 1 : 0;
    of = 0; // approximate
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
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(0, rdi, 0, 0);
    // 0x76bf4  mov r14,rax
    r14 = rax;
    // 0x76bf7  test rax,rax
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x76bfa  je 0x76D06
    if (zf) goto loc_76d06;
    loc_76c00:
    // 0x76c00  mov rcx,[rbx]
    rcx = R64(rbx);
    // 0x76c03  mov rdx,[rbx+0x10]
    rdx = R64(rbx + 16);
    // 0x76c07  sub rdx,rcx
    rdx = (rdx - rcx);
    zf = ((rdx - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < rcx) ? 1 : 0;
    // 0x76c0a  je short 0x76C36
    if (zf) goto loc_76c36;
    // 0x76c0c  cmp rdx,0x1000
    zf = ((rdx - 4096) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 4096) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < 4096) ? 1 : 0;
    of = 0; // approximate
    // 0x76c13  jb short 0x76C31
    if (cf) goto loc_76c31;
    // 0x76c15  mov rax,[rcx-8]
    rax = R64(rcx + -8);
    // 0x76c19  add rcx,0xFFFFFFFFFFFFFFF8
    rcx = (rcx + 18446744073709551608);
    zf = ((rcx + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x76c1d  sub rcx,rax
    rcx = (rcx - rax);
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx < rax) ? 1 : 0;
    // 0x76c20  cmp rcx,0x20
    zf = ((rcx - 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - 32) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx < 32) ? 1 : 0;
    of = 0; // approximate
    // 0x76c24  jae 0x76D2E
    if (!cf) goto loc_76d2e;
    // 0x76c2a  add rdx,0x27
    rdx = (rdx + 39);
    zf = ((rdx + 39) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx + 39) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx + 39 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x76c2e  mov rcx,rax
    rcx = rax;
    loc_76c31:
    rax = native::sub_e935700(rax, 0, 0, 0);
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
    rdi = (rdi + 18446744073709551608);
    zf = ((rdi + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdi + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdi + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x76c49  cmp rdi,0x18
    zf = ((rdi - 24) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdi - 24) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdi < 24) ? 1 : 0;
    of = 0; // approximate
    // 0x76c4d  jae short 0x76C54
    if (!cf) goto loc_76c54;
    // 0x76c4f  mov rcx,r14
    rcx = r14;
    // 0x76c52  jmp short 0x76CA0
    goto loc_76ca0;
    loc_76c54:
    // 0x76c54  shr rdi,3
    // DECISIONS: shift not fully modeled; register local left untouched.
    // 0x76c58  inc rdi
    // DECISIONS: unary alu not fully modeled; register local left untouched.
    // 0x76c5b  mov rdx,rdi
    rdx = rdi;
    // 0x76c5e  and rdx,0xFFFFFFFFFFFFFFFC
    rdx = (rdx & 18446744073709551612);
    zf = ((rdx & 18446744073709551612) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx & 18446744073709551612) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x76c62  lea rcx,[r14+rdx*8]
    rcx = r14 + (rdx * 8);
    // 0x76c66  movq xmm0,rsi
    xmm0 = rsi;
    // 0x76c6b  pshufd xmm0,xmm0,0x44
    // DECISIONS: unhandled instruction; no state change (never guessed).
    // 0x76c70  xor r8d,r8d
    r8 = (uint64_t)(uint32_t)((r8 ^ (uint32_t)r8));
    zf = ((r8 ^ (uint32_t)r8) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 ^ (uint32_t)r8) & 0x80000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // nop
    loc_76c80:
    // 0x76c80  movdqu [r14+r8*8],xmm0
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x76c86  movdqu [r14+r8*8+0x10],xmm0
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x76c8d  add r8,4
    r8 = (r8 + 4);
    zf = ((r8 + 4) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 + 4) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (r8 + 4 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x76c91  cmp rdx,r8
    zf = ((rdx - r8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - r8) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < r8) ? 1 : 0;
    of = 0; // approximate
    // 0x76c94  jne short 0x76C80
    if (!zf) goto loc_76c80;
    // 0x76c96  cmp rdi,rdx
    zf = ((rdi - rdx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdi - rdx) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdi < rdx) ? 1 : 0;
    of = 0; // approximate
    // 0x76c99  je short 0x76CFC
    if (zf) goto loc_76cfc;
    // nop
    loc_76ca0:
    // 0x76ca0  mov [rcx],rsi
    W64(rcx, rsi);
    // 0x76ca3  add rcx,8
    rcx = (rcx + 8);
    zf = ((rcx + 8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 8) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx + 8 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x76ca7  cmp rcx,rax
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx < rax) ? 1 : 0;
    of = 0; // approximate
    // 0x76caa  jne short 0x76CA0
    if (!zf) goto loc_76ca0;
    // 0x76cac  jmp short 0x76CFC
    goto loc_76cfc;
    loc_76cae:
    // 0x76cae  shr r8,3
    // DECISIONS: shift not fully modeled; register local left untouched.
    // 0x76cb2  inc r8
    // DECISIONS: unary alu not fully modeled; register local left untouched.
    // 0x76cb5  mov r9,r8
    r9 = r8;
    // 0x76cb8  and r9,0xFFFFFFFFFFFFFFFC
    r9 = (r9 & 18446744073709551612);
    zf = ((r9 & 18446744073709551612) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 & 18446744073709551612) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x76cbc  lea rdx,[rcx+r9*8]
    rdx = rcx + (r9 * 8);
    // 0x76cc0  movq xmm0,rsi
    xmm0 = rsi;
    // 0x76cc5  pshufd xmm0,xmm0,0x44
    // DECISIONS: unhandled instruction; no state change (never guessed).
    // 0x76cca  xor r10d,r10d
    r10 = (uint64_t)(uint32_t)((r10 ^ (uint32_t)r10));
    zf = ((r10 ^ (uint32_t)r10) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r10 ^ (uint32_t)r10) & 0x80000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // nop
    loc_76cd0:
    // 0x76cd0  movdqu [rcx+r10*8],xmm0
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x76cd6  movdqu [rcx+r10*8+0x10],xmm0
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0x76cdd  add r10,4
    r10 = (r10 + 4);
    zf = ((r10 + 4) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r10 + 4) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (r10 + 4 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x76ce1  cmp r9,r10
    zf = ((r9 - r10) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r9 - r10) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (r9 < r10) ? 1 : 0;
    of = 0; // approximate
    // 0x76ce4  jne short 0x76CD0
    if (!zf) goto loc_76cd0;
    // 0x76ce6  cmp r8,r9
    zf = ((r8 - r9) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r8 - r9) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (r8 < r9) ? 1 : 0;
    of = 0; // approximate
    // 0x76ce9  je short 0x76CFC
    if (zf) goto loc_76cfc;
    // nop
    loc_76cf0:
    // 0x76cf0  mov [rdx],rsi
    W64(rdx, rsi);
    // 0x76cf3  add rdx,8
    rdx = (rdx + 8);
    zf = ((rdx + 8) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx + 8) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx + 8 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0x76cf7  cmp rdx,rax
    zf = ((rdx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < rax) ? 1 : 0;
    of = 0; // approximate
    // 0x76cfa  jne short 0x76CF0
    if (!zf) goto loc_76cf0;
    loc_76cfc:
    // 0x76d01  pop rdi
    rdi = R64(rsp); rsp = (rsp + 8);
    // 0x76d03  pop r14
    r14 = R64(rsp); rsp = (rsp + 8);
    // 0x76d05  ret
    return 18446744073709551615;
    loc_76d06:
    // 0x76d06  mov rcx,rdi
    rcx = rdi;
    rax = native::boundary::sub_9bc830(rdi, 0, 0, 0);
    // 0x76d0e  xor r14d,r14d
    r14 = (uint64_t)(uint32_t)((r14 ^ (uint32_t)r14));
    zf = ((r14 ^ (uint32_t)r14) & 0xFFFFFFFF) == 0 ? 1 : 0;
    sf = ((r14 ^ (uint32_t)r14) & 0x80000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0x76d11  jmp 0x76C00
    goto loc_76c00;
    loc_76d16:
    // 0x76d16  mov rcx,r14
    rcx = r14;
    // 0x76d19  mov r14,rax
    r14 = rax;
    rax = native::boundary::sub_9bc830(r14, 0, 0, 0);
    // 0x76d24  jmp 0x76BAD
    goto loc_76bad;
    loc_76d29:
    rax = native::boundary::sub_75740(0, 0, 0, 0);
    loc_76d2e:
    // 0x76d2e  mov qword ptr [rsp+0x20],0
    W64(rsp + 32, 0);
    // DECISION: indirect call through [rip + 261786744]
    rax = raw_call_via_mem(0, 0, 0, 0);
    // 0x76d47  int3
    // DECISIONS: int3/ud2 traps; modeled as returning rax (does not return normally).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
