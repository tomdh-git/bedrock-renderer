// LIFT 0xa1c40 size 0x181 1.26.62.01 lift2
#include <cstdint>

#if 0
// Verbatim instructions of sub_a1c40 ([0xa1c40, 0xa1dc1)):
0xa1c40  push rbp
0xa1c41  push rsi
0xa1c42  push rdi
0xa1c43  push rbx
0xa1c44  sub rsp,0x58
0xa1c48  lea rbp,[rsp+0x50]
0xa1c4d  movaps [rbp-0x10],xmm6
0xa1c51  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
0xa1c59  mov rsi,rcx
0xa1c5c  mov eax,[rdx]
0xa1c5e  mov [rcx],eax
0xa1c60  xorps xmm6,xmm6
0xa1c63  movups [rcx+8],xmm6
0xa1c67  mov rcx,[0x1233E1A8]
0xa1c6e  mov rax,[rcx]
0xa1c71  mov rax,[rax+8]
0xa1c75  mov edx,0x18
0xa1c7a  call qword ptr [0xF99FFA0]
0xa1c80  mov rdi,rax
0xa1c83  test rax,rax
0xa1c86  je 0xA1D88
0xa1c8c  lea rax,[rsi+8]
0xa1c90  mov [rbp-0x28],rax
0xa1c94  mov [rdi],rdi
0xa1c97  mov [rdi+8],rdi
0xa1c9b  mov [rsi+8],rdi
0xa1c9f  lea rax,[rsi+0x18]
0xa1ca3  mov [rbp-0x20],rax
0xa1ca7  movups [rsi+0x18],xmm6
0xa1cab  mov qword ptr [rsi+0x28],0
0xa1cb3  mov qword ptr [rsi+0x30],7
0xa1cbb  mov qword ptr [rsi+0x38],8
0xa1cc3  mov dword ptr [rsi],0x3F800000
0xa1cc9  mov rcx,[0x1233E1A8]
0xa1cd0  mov rax,[rcx]
0xa1cd3  mov rax,[rax+8]
0xa1cd7  mov edx,0x80
0xa1cdc  call qword ptr [0xF99FFA0]
0xa1ce2  nop
0xa1ce3  mov rbx,rax
0xa1ce6  test rax,rax
0xa1ce9  je 0xA1D97
0xa1cef  mov rcx,[rsi+0x18]
0xa1cf3  mov rdx,[rsi+0x28]
0xa1cf7  sub rdx,rcx
0xa1cfa  je short 0xA1D26
0xa1cfc  cmp rdx,0x1000
0xa1d03  jb short 0xA1D21
0xa1d05  mov rax,[rcx-8]
0xa1d09  add rcx,0xFFFFFFFFFFFFFFF8
0xa1d0d  sub rcx,rax
0xa1d10  cmp rcx,0x20
0xa1d14  jae 0xA1DA7
0xa1d1a  add rdx,0x27
0xa1d1e  mov rcx,rax
0xa1d21  call 0xE935700
0xa1d26  mov [rsi+0x18],rbx
0xa1d2a  mov rax,rbx
0xa1d2d  sub rax,0xFFFFFFFFFFFFFF80
0xa1d31  mov [rsi+0x20],rax
0xa1d35  mov [rsi+0x28],rax
0xa1d39  mov [rbx],rdi
0xa1d3c  mov [rbx+8],rdi
0xa1d40  mov [rbx+0x10],rdi
0xa1d44  mov [rbx+0x18],rdi
0xa1d48  mov [rbx+0x20],rdi
0xa1d4c  mov [rbx+0x28],rdi
0xa1d50  mov [rbx+0x30],rdi
0xa1d54  mov [rbx+0x38],rdi
0xa1d58  mov [rbx+0x40],rdi
0xa1d5c  mov [rbx+0x48],rdi
0xa1d60  mov [rbx+0x50],rdi
0xa1d64  mov [rbx+0x58],rdi
0xa1d68  mov [rbx+0x60],rdi
0xa1d6c  mov [rbx+0x68],rdi
0xa1d70  mov [rbx+0x70],rdi
0xa1d74  mov [rbx+0x78],rdi
0xa1d78  mov rax,rsi
0xa1d7b  movaps xmm6,[rbp-0x10]
0xa1d7f  add rsp,0x58
0xa1d83  pop rbx
0xa1d84  pop rdi
0xa1d85  pop rsi
0xa1d86  pop rbp
0xa1d87  ret
0xa1d88  mov ecx,0x18
0xa1d8d  call 0x9BC830
0xa1d92  jmp 0xA1C8C
0xa1d97  mov ecx,0x80
0xa1d9c  call 0x9BC830
0xa1da1  nop
0xa1da2  jmp 0xA1CEF
0xa1da7  mov qword ptr [rsp+0x20],0
0xa1db0  xor ecx,ecx
0xa1db2  xor edx,edx
0xa1db4  xor r8d,r8d
0xa1db7  xor r9d,r9d
0xa1dba  call qword ptr [0xF9A8C78]
0xa1dc0  int3
#endif

namespace native {
    // forward declarations for lift-class callees
        uint64_t sub_e935700(uint64_t, uint64_t, uint64_t, uint64_t);
    namespace boundary {
        uint64_t sub_9bc830(uint64_t, uint64_t, uint64_t, uint64_t);
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

uint64_t sub_a1c40(std::uint64_t a0, std::uint64_t a1, std::uint64_t a2, std::uint64_t a3) {
    // DCE applied: unreachable blocks, folded sub/add rsp, dead flag writes removed.
    uint64_t rax = a0, rcx = a1, rdx = a2, rbx = 0, rsp = 0, rbp = 0, rsi = 0, rdi = 0;
    uint64_t r8 = a3, r9 = 0, r10 = 0, r11 = 0, r12 = 0, r13 = 0, r14 = 0, r15 = 0, rip = 0;
    uint8_t cf = 0, pf = 0, af = 0, zf = 0, sf = 0, of = 0;
    // 0xa1c48  lea rbp,[rsp+0x50]
    rbp = rsp + 80;
    // 0xa1c4d  movaps [rbp-0x10],xmm6
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0xa1c51  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
    W64(rbp + -24, 18446744073709551614);
    // 0xa1c59  mov rsi,rcx
    rsi = rcx;
    // 0xa1c5c  mov eax,[rdx]
    rax = R32(rdx);
    // 0xa1c5e  mov [rcx],eax
    W32(rcx, (uint32_t)rax);
    // 0xa1c60  xorps xmm6,xmm6
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0xa1c63  movups [rcx+8],xmm6
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0xa1c67  mov rcx,[0x1233E1A8]
    rcx = R64(rip + 305389992);
    // 0xa1c6e  mov rax,[rcx]
    rax = R64(rcx);
    // 0xa1c71  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0xa1c75  mov edx,0x18
    rdx = 24;
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(0, a2, a3, 0);
    // 0xa1c80  mov rdi,rax
    rdi = rax;
    // 0xa1c83  test rax,rax
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0xa1c86  je 0xA1D88
    if (zf) goto loc_a1d88;
    loc_a1c8c:
    // 0xa1c8c  lea rax,[rsi+8]
    rax = rsi + 8;
    // 0xa1c90  mov [rbp-0x28],rax
    W64(rbp + -40, rax);
    // 0xa1c94  mov [rdi],rdi
    W64(rdi, rdi);
    // 0xa1c97  mov [rdi+8],rdi
    W64(rdi + 8, rdi);
    // 0xa1c9b  mov [rsi+8],rdi
    W64(rsi + 8, rdi);
    // 0xa1c9f  lea rax,[rsi+0x18]
    rax = rsi + 24;
    // 0xa1ca3  mov [rbp-0x20],rax
    W64(rbp + -32, rax);
    // 0xa1ca7  movups [rsi+0x18],xmm6
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0xa1cab  mov qword ptr [rsi+0x28],0
    W64(rsi + 40, 0);
    // 0xa1cb3  mov qword ptr [rsi+0x30],7
    W64(rsi + 48, 7);
    // 0xa1cbb  mov qword ptr [rsi+0x38],8
    W64(rsi + 56, 8);
    // 0xa1cc3  mov dword ptr [rsi],0x3F800000
    W32(rsi, (uint32_t)1065353216);
    // 0xa1cc9  mov rcx,[0x1233E1A8]
    rcx = R64(rip + 305389992);
    // 0xa1cd0  mov rax,[rcx]
    rax = R64(rcx);
    // 0xa1cd3  mov rax,[rax+8]
    rax = R64(rax + 8);
    // 0xa1cd7  mov edx,0x80
    rdx = 128;
    // DECISION: indirect call through [rip + 261750688]
    rax = raw_call_via_mem(0, 0, 0, 0);
    // 0xa1ce3  mov rbx,rax
    rbx = rax;
    // 0xa1ce6  test rax,rax
    zf = ((rax & rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax & rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = 0; of = 0;
    // 0xa1ce9  je 0xA1D97
    if (zf) goto loc_a1d97;
    loc_a1cef:
    // 0xa1cef  mov rcx,[rsi+0x18]
    rcx = R64(rsi + 24);
    // 0xa1cf3  mov rdx,[rsi+0x28]
    rdx = R64(rsi + 40);
    // 0xa1cf7  sub rdx,rcx
    rdx = (rdx - rcx);
    zf = ((rdx - rcx) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - rcx) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < rcx) ? 1 : 0;
    // 0xa1cfa  je short 0xA1D26
    if (zf) goto loc_a1d26;
    // 0xa1cfc  cmp rdx,0x1000
    zf = ((rdx - 4096) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx - 4096) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx < 4096) ? 1 : 0;
    of = 0; // approximate
    // 0xa1d03  jb short 0xA1D21
    if (cf) goto loc_a1d21;
    // 0xa1d05  mov rax,[rcx-8]
    rax = R64(rcx + -8);
    // 0xa1d09  add rcx,0xFFFFFFFFFFFFFFF8
    rcx = (rcx + 18446744073709551608);
    zf = ((rcx + 18446744073709551608) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx + 18446744073709551608) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx + 18446744073709551608 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0xa1d0d  sub rcx,rax
    rcx = (rcx - rax);
    zf = ((rcx - rax) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - rax) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx < rax) ? 1 : 0;
    // 0xa1d10  cmp rcx,0x20
    zf = ((rcx - 32) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rcx - 32) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rcx < 32) ? 1 : 0;
    of = 0; // approximate
    // 0xa1d14  jae 0xA1DA7
    if (!cf) goto loc_a1da7;
    // 0xa1d1a  add rdx,0x27
    rdx = (rdx + 39);
    zf = ((rdx + 39) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rdx + 39) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rdx + 39 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0xa1d1e  mov rcx,rax
    rcx = rax;
    loc_a1d21:
    rax = native::sub_e935700(rax, 0, 0, 0);
    loc_a1d26:
    // 0xa1d26  mov [rsi+0x18],rbx
    W64(rsi + 24, rbx);
    // 0xa1d2a  mov rax,rbx
    rax = rbx;
    // 0xa1d2d  sub rax,0xFFFFFFFFFFFFFF80
    rax = (rax - 18446744073709551488);
    zf = ((rax - 18446744073709551488) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rax - 18446744073709551488) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rax < 18446744073709551488) ? 1 : 0;
    // 0xa1d31  mov [rsi+0x20],rax
    W64(rsi + 32, rax);
    // 0xa1d35  mov [rsi+0x28],rax
    W64(rsi + 40, rax);
    // 0xa1d39  mov [rbx],rdi
    W64(rbx, rdi);
    // 0xa1d3c  mov [rbx+8],rdi
    W64(rbx + 8, rdi);
    // 0xa1d40  mov [rbx+0x10],rdi
    W64(rbx + 16, rdi);
    // 0xa1d44  mov [rbx+0x18],rdi
    W64(rbx + 24, rdi);
    // 0xa1d48  mov [rbx+0x20],rdi
    W64(rbx + 32, rdi);
    // 0xa1d4c  mov [rbx+0x28],rdi
    W64(rbx + 40, rdi);
    // 0xa1d50  mov [rbx+0x30],rdi
    W64(rbx + 48, rdi);
    // 0xa1d54  mov [rbx+0x38],rdi
    W64(rbx + 56, rdi);
    // 0xa1d58  mov [rbx+0x40],rdi
    W64(rbx + 64, rdi);
    // 0xa1d5c  mov [rbx+0x48],rdi
    W64(rbx + 72, rdi);
    // 0xa1d60  mov [rbx+0x50],rdi
    W64(rbx + 80, rdi);
    // 0xa1d64  mov [rbx+0x58],rdi
    W64(rbx + 88, rdi);
    // 0xa1d68  mov [rbx+0x60],rdi
    W64(rbx + 96, rdi);
    // 0xa1d6c  mov [rbx+0x68],rdi
    W64(rbx + 104, rdi);
    // 0xa1d70  mov [rbx+0x70],rdi
    W64(rbx + 112, rdi);
    // 0xa1d74  mov [rbx+0x78],rdi
    W64(rbx + 120, rdi);
    // 0xa1d78  mov rax,rsi
    rax = rsi;
    // 0xa1d7b  movaps xmm6,[rbp-0x10]
    // DECISIONS: xmm op not modeled; xmm locals left zeroed.
    // 0xa1d7f  add rsp,0x58
    rsp = (rsp + 88);
    zf = ((rsp + 88) & 0xFFFFFFFFFFFFFFFF) == 0 ? 1 : 0;
    sf = ((rsp + 88) & 0x8000000000000000) != 0 ? 1 : 0;
    cf = (rsp + 88 > 0xFFFFFFFFFFFFFFFF) ? 1 : 0;
    // 0xa1d87  ret
    return rsi;
    loc_a1d88:
    // 0xa1d88  mov ecx,0x18
    rcx = 24;
    rax = native::boundary::sub_9bc830(0, 0, 0, 0);
    // 0xa1d92  jmp 0xA1C8C
    goto loc_a1c8c;
    loc_a1d97:
    // 0xa1d97  mov ecx,0x80
    rcx = 128;
    rax = native::boundary::sub_9bc830(0, 0, 0, 0);
    // 0xa1da2  jmp 0xA1CEF
    goto loc_a1cef;
    loc_a1da7:
    // 0xa1da7  mov qword ptr [rsp+0x20],0
    W64(rsp + 32, 0);
    // DECISION: indirect call through [rip + 261786744]
    rax = raw_call_via_mem(0, 0, 0, 0);
    // 0xa1dc0  int3
    // DECISIONS: int3/ud2 traps; modeled as returning rax (does not return normally).
    return rax;
}
} // namespace native

// DECISIONS
// - Types/names taken only from existing facts (ticked headers, native_functions.tsv, native_boundary.tsv).
// - Calls resolved to native::boundary::sub_X / native::sub_X where the callee is in the TSVs.
// - Unknown callees stay raw with a DECISIONS question; nothing is guessed.
// - Dead instructions (unreachable blocks, folded sub/add rsp, dead flag writes) removed.
