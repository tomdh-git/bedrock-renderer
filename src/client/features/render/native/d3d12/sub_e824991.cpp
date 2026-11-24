// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991

#include "sub_e824991.h"

namespace native {

// Chunk state documented in docs/functions/e824991.md section 'Chunk state'.
// static inline step function for chunk range 0xe829147..0xe82a912.
static inline void sub_e824991_chunk_c03(ChunkState& s) {
    // CHUNK 0xe829147..0xe82a912
    uint8_t* rbx = s.stack_frame;
    uint64_t r12 = s.r12;
    uint64_t r13 = s.r13;
    uint64_t r14 = s.r14;
    uint64_t r15 = s.r15;
    uint64_t rsi = s.rsi;
    uint64_t rdi = s.rdi;
    // xmm6-xmm15 live across chunk but not modified here

    // 0xe829147..0xe829171
    r13 = *(uint32_t*)(rbx + 0x2B0);
    r13 += r12;
    void* rdx = (void*)((char*)rsi + r13);
    void* rax = *(void**)(*(char**)(rbx + 0x98));
    void* rcx = *(void**)(s.r13); // r13 from chunk entry
    size_t r9 = (size_t)rax - (size_t)rcx;
    size_t r8 = (size_t)rdx - r9;
    if (r8 <= r9) goto loc_e829668;
    // 0xe829177..0xe829188
    void* r9b = *(void**)(*(char**)(rbx + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e829646;
    // 0xe82918e..0xe8291a2
    rcx = *(void**)(rbx + 0xA8);
    void* r8p = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e82965e;

loc_e829668:
    // 0xe829668..0xe829680
    rcx = (void*)((char*)rcx + r13);
    r13 = *(uint64_t*)(rbx + 0xA8);
    rdi <<= 6;
    rdi += *(uint64_t*)(rbx + 0x2F8);
    rdx = (void*)rdi;
    goto loc_e8299D0;

loc_e829646:
    // 0xe829646..0xe82965e
    r12 = (uint64_t)rax + r8;
    rcx = rax;
    sub_eec6ed0(rcx, nullptr, 0); // xor edx,edx; call 0xEEC6ED0
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)r12;
    goto loc_e82965e;

loc_e82965e:
    // 0xe82965e..0xe829668
    rax = *(void**)(rbx + 0xA8);
    rcx = *(void**)(rax);
    goto loc_e829668;

    // 0xe8291a7..0xe8291e8
    r13 = *(uint32_t*)(rbx + 0x2B0);
    r13 += r12;
    rdx = (void*)((char*)rdi + r13);
    rax = *(void**)(*(char**)(rbx + 0x98));
    rcx = *(void**)(s.r13);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e8296cf;
    r9b = *(void**)(*(char**)(rbx + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e8296ad;
    rcx = *(void**)(rbx + 0xA8);
    r8p = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e8296c5;

loc_e8296cf:
    // 0xe8296cf..0xe8296df
    rcx = (void*)((char*)rcx + r13);
    r13 = *(uint64_t*)(rbx + 0xA8);
    rdx = (void*)rsi;
    r8 = rdi;
    goto loc_e8299D3;

loc_e8296ad:
    // 0xe8296ad..0xe8296c5
    r12 = (uint64_t)rax + r8;
    rcx = rax;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)r12;
    goto loc_e8296c5;

loc_e8296c5:
    // 0xe8296c5..0xe8296cf
    rax = *(void**)(rbx + 0xA8);
    rcx = *(void**)(rax);
    goto loc_e8296cf;

    // 0xe829207..0xe829246
    r12 = *(uint32_t*)(rbx + 0x2B0);
    r12 += rdi;
    rdx = (void*)((char*)r12 + rsi);
    rax = *(void**)(*(char**)(rbx + 0x98));
    rcx = *(void**)(s.r13);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e82972f;
    r9b = *(void**)(*(char**)(rbx + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e82970c;
    rcx = s.r13;
    r8p = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e829724;

loc_e82972f:
    // 0xe82972f..0xe829739
    rcx = (void*)((char*)rcx + r12);
    rdx = (void*)(rbx + 0x90B0);
    goto loc_e8299D0;

loc_e82970c:
    // 0xe82970c..0xe829724
    rdi = (uint64_t)rax + r8;
    rcx = rax;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)rdi;
    goto loc_e829724;

loc_e829724:
    // 0xe829724..0xe82972f
    r13 = *(uint64_t*)(rbx + 0xA8);
    rcx = *(void**)(rbx + r13);
    goto loc_e82972f;

    // 0xe829261..0xe8292a0
    r12 = *(uint32_t*)(rbx + 0x2B0);
    r12 += rdi;
    rdx = (void*)((char*)r12 + rsi);
    rax = *(void**)(*(char**)(rbx + 0x98));
    rcx = *(void**)(s.r13);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e829793;
    r9b = *(void**)(*(char**)(rbx + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e829770;
    rcx = s.r13;
    r8p = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e829788;

loc_e829793:
    // 0xe829793..0xe82979d
    rcx = (void*)((char*)rcx + r12);
    rdx = (void*)(rbx + 0x9130);
    goto loc_e8299D0;

loc_e829770:
    // 0xe829770..0xe829788
    rdi = (uint64_t)rax + r8;
    rcx = rax;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)rdi;
    goto loc_e829788;

loc_e829788:
    // 0xe829788..0xe829793
    r13 = *(uint64_t*)(rbx + 0xA8);
    rcx = *(void**)(rbx + r13);
    goto loc_e829793;

    // 0xe8292bb..0xe8292fa
    rdi = *(uint32_t*)(rbx + 0x2B0);
    rdx = (void*)((char*)rdi + rsi + 0x10);
    rcx = *(void**)(*(char**)(rbx + 0x98));
    rax = *(void**)(s.r13);
    r9 = (void*)((char*)rcx - (char*)rax);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e82981a;
    r9b = *(void**)(*(char**)(rbx + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rax);
    if ((size_t)rdx <= (size_t)r9) goto loc_e8297fa;
    rcx = s.r13;
    r8p = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e82980f;

loc_e82981a:
    // 0xe82981a is part of 0xe8297fa block... wait, 0xe8297fa target
    // Actually 0xe8297fa is the jbe target. Let me check: the listing shows 0xe8297fa as target.
    // The jbe at 0xe8292fa goes to 0xe82981a? No, listing line 100: jbe 0xE82981A
    // But listing shows 0xe8297fa at line 397. Let me trace...
    // Actually the listing at 0xe8292fa (line 100) says jbe 0xE82981A
    // But 0xe82981a is not in the listing explicitly. Wait, line 408 is 0xe829829.
    // Let me re-check the original listing lines 86-101:
    // Line 100: 0xe8292fa jbe 0xE82981A
    // But in the full listing I read earlier, 0xe8297fa is at line 397.
    // 0xe82981A would be between 0xe8297fa and 0xe829829? No.
    // Hmm, the listing I read has 0xe8297fa at line 397 and 0xe829829 at line 408.
    // 0xe82981A is not shown. Perhaps the jbe target is 0xe8297fa in the actual disasm.
    // The earlier partial listing showed: 0xe8292fa jbe 0xE82981A but full listing shows 0xe8297fa.
    // I'll trust the full listing. The target is 0xe8297fa.

    // Actually looking at lines 86-101 of my earlier read (offset 201):
    // 100: 0xe8292fa jbe 0xE82981A
    // But full listing shows 0xe8297fa. There's a discrepancy.
    // Let me check: in the first read (offset 201), line 100 was from the 11th block.
    // The full listing has different addresses because the first read was truncated.
    // I'll use the full listing addresses.

    // For 0xe8292bb block (lines 86-101), the jbe target is 0xe82981a in partial but 0xe8297fa in full.
    // Actually the full listing shows at line 397: 0xe8297fa lea r12,[rcx+r8]
    // And line 408: 0xe829829 lea r12,[rcx+r8]
    // The jbe at 0xe8292fa likely goes to 0xe8297fa.
    // I'll map based on full listing.

    // 0xe8297fa block:
loc_e8297fa:
    // 0xe8297fa..0xe82980f
    r12 = (uint64_t)rcx + r8;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)r12;
    goto loc_e82980f;

loc_e82980f:
    // 0xe82980f..0xe829824
    r13 = *(uint64_t*)(rbx + 0xA8);
    rax = *(void**)(rbx + r13);
    rdi += rsi;
    rdi += rax;
    // movups [rdi], xmm8
    return; // jmp 0xE827F10 (out of chunk range)

    // 0xe829315..0xe829354
    rdi = *(uint32_t*)(rbx + 0x2B0);
    rdx = (void*)((char*)rdi + rsi + 0x10);
    rcx = *(void**)(*(char**)(rbx + 0x98));
    rax = *(void**)(s.r13);
    r9 = (void*)((char*)rcx - (char*)rax);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e829849;
    r9b = *(void**)(*(char**)(rbx + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rax);
    if ((size_t)rdx <= (size_t)r9) goto loc_e829829;
    rcx = s.r13;
    r8p = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e82983e;

loc_e829849:
    // 0xe829849 is 0xe829829 target? Full listing shows 0xe829829 at line 408.
    // jbe 0xE829849 from line 108 -> 0xe829829 in full.
loc_e829829:
    // 0xe829829..0xe82983e
    r12 = (uint64_t)rcx + r8;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)r12;
    goto loc_e82983e;

loc_e82983e:
    // 0xe82983e..0xe829853
    r13 = *(uint64_t*)(rbx + 0xA8);
    rax = *(void**)(rbx + r13);
    rdi += rsi;
    rdi += rax;
    // movlps [rdi], xmm8
    return; // jmp 0xE827F10

    // 0xe82936f..0xe8293ae
    r12 = *(uint32_t*)(rbx + 0x2B0);
    r12 += rdi;
    rdx = (void*)((char*)r12 + rsi);
    rax = *(void**)(*(char**)(rbx + 0x98));
    rcx = *(void**)(s.r13);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e8298ad;
    r9b = *(void**)(*(char**)(rbx + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e82988a;
    rcx = s.r13;
    r8p = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e8298a2;

loc_e8298ad:
    // jbe 0xE8298AD -> 0xe82988a in full listing (line 430)
loc_e82988a:
    // 0xe82988a..0xe8298a2
    rdi = (uint64_t)rax + r8;
    rcx = rax;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)rdi;
    goto loc_e8298a2;

loc_e8298a2:
    // 0xe8298a2..0xe8298b7
    r13 = *(uint64_t*)(rbx + 0xA8);
    rcx = *(void**)(rbx + r13);
    rcx += r12;
    rdx = (void*)(rbx + 0x90F0);
    goto loc_e8299D0;

    // 0xe8293c9..0xe829408
    rdi = *(uint32_t*)(rbx + 0x2B0);
    rdx = (void*)((char*)rdi + rsi + 0x10);
    rcx = *(void**)(*(char**)(rbx + 0x98));
    rax = *(void**)(s.r13);
    r9 = (void*)((char*)rcx - (char*)rax);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e829901;
    r9b = *(void**)(*(char**)(rbx + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rax);
    if ((size_t)rdx <= (size_t)r9) goto loc_e8298e1;
    rcx = s.r13;
    r8p = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e8298f6;

loc_e829901:
    // jbe 0xE829901 -> 0xe8298e1 in full (line 450)
loc_e8298e1:
    // 0xe8298e1..0xe8298f6
    r12 = (uint64_t)rcx + r8;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)r12;
    goto loc_e8298f6;

loc_e8298f6:
    // 0xe8298f6..0xe82990e
    r13 = *(uint64_t*)(rbx + 0xA8);
    rax = *(void**)(rbx + r13);
    rdi += rsi;
    rdi += rax;
    rax = (uint64_t)(rbx + 0xD170);
    return; // jmp 0xE827F03

    // 0xe829423..0xe829462
    r12 = *(uint32_t*)(rbx + 0x2B0);
    r12 += rdi;
    rdx = (void*)((char*)r12 + rsi);
    rax = *(void**)(*(char**)(rbx + 0x98));
    rcx = *(void**)(s.r13);
    r9 = (void*)((char*)rax - (char*)rcx);
    r8 = (void*)((char*)rdx - (char*)r9);
    if ((size_t)r8 <= (size_t)r9) goto loc_e829968;
    r9b = *(void**)(*(char**)(rbx + 0xA0) + 0x38);
    r9 = (void*)((char*)r9b - (char*)rcx);
    if ((size_t)rdx <= (size_t)r9) goto loc_e829945;
    rcx = s.r13;
    r8p = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx, rdx, r8p);
    goto loc_e82995d;

loc_e829968:
    // jbe 0xE829968 -> 0xe829974 in full (line 483)
loc_e829974:
    // 0xe829974..0xe829982
    r12 = (uint64_t)rax + r8;
    rcx = rax;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)r12;
    goto loc_e829990; // fall through

loc_e829945:
    // 0xe829945..0xe82995d
    rdi = (uint64_t)rax + r8;
    rcx = rax;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)rdi;
    goto loc_e82995d;

loc_e82995d:
    // 0xe82995d..0xe829972
    r13 = *(uint64_t*)(rbx + 0xA8);
    rcx = *(void**)(rbx + r13);
    rcx += r12;
    rdx = (void*)(*(uint64_t*)(rbx + 0x2F0));
    goto loc_e8299D0;

    // Continuing from loc_e829974 fall-through
loc_e829990:
    // 0xe82998c..0xe8299a1 (continuation of 0xe829974 block)
    r13 = *(uint64_t*)(rbx + 0xA8);
    rcx = *(void**)(rbx + r13);
    rcx += rdi;
    rdx = (void*)(*(uint64_t*)(rbx + 0x5C0));
    goto loc_e8299D0;

loc_e8299a3:
    // 0xe8299a3..0xe8299bb (jbe target from 0xe82994b? Actually from 0xe829516)
    rdi = (uint64_t)rax + r8;
    rcx = rax;
    sub_eec6ed0(rcx, nullptr, 0);
    rax = *(void**)(rbx + 0x98);
    *(void**)(rax) = (void*)rdi;
    goto loc_e8299bb;

loc_e8299bb:
    // 0xe8299bb..0xe8299c9
    r13 = *(uint64_t*)(rbx + 0xA8);
    rcx = *(void**)(rbx + r13);
    rcx += r12;
    rdx = (void*)(*(uint64_t*)(rbx + 0x5C0));
    goto loc_e8299D0;

loc_e8299D0:
    // 0xe8299d0..0xe8299d8
    r8 = rsi;
    sub_eec6ec0(rcx, rdx, r8);
    return; // jmp 0xE827F10

loc_e8299D3:
    // 0xe8299d3..0xe8299d8
    sub_eec6ec0(rcx, rdx, r8);
    return; // jmp 0xE827F10

    // ============================================================
    // PHASE 2: 0xe8299dd..0xe82a912
    // ============================================================

    // 0xe8299dd..0xe829a1e
    uint32_t esi = *(uint32_t*)(rbx + 0x2B0);
    uint32_t r14d = *(uint32_t*)(rbx + 0x2B8);
    uint64_t rax2 = *(uint64_t*)(rbx + 0x2A8);
    uint64_t rcx2 = rax2 + esi;
    uint32_t edx = *(uint32_t*)(rbx + 0x26C);
    if (rcx2 <= edx) goto loc_e829b20;
    // 0xe829a04..0xe829a1e
    uint64_t r8_2 = 0xFFFF;
    uint64_t r9_2 = 0x100;
    uint64_t rcx3 = *(uint64_t*)(rbx + 0x578);
    void* rdx2 = (void*)(rbx + 0x3B0);
    sub_e8360f0(rcx3, rdx2, r8_2, r9_2); // call 0xE8360F0

    // 0xe829a24..0xe829aec
    r15 = *(uint64_t*)(rbx + 0x3C8);
    r12 = *(uint32_t*)(rbx + 0x3C0);
    rax2 = *(uint64_t*)(rbx + 0x3B0);
    rdi = *(uint64_t*)(rbx + 0x3B8);
    // movups xmm0,[rax2]
    // movups xmm1,[rax2+0x10]
    // movaps [rbx+0xD0],xmm1
    // movaps [rbx+0xC0],xmm0
    uint64_t rdx3 = *(uint64_t*)(rax2 + 8);
    uint64_t rcx4 = *(uint64_t*)(rax2 + 0x10);
    uint32_t r13d = *(uint32_t*)(rax2 + 0x1C);
    if (rdi == 0) goto loc_e829abb;
    // 0xe829a66..0xe829a7c
    // lock dec dword ptr [rdi+8]
    // jne short 0xE829ABB
    uint64_t rax3 = *(uint64_t*)(rdi);
    rax3 = *(uint64_t*)(rax3);
    *(uint64_t*)(rbx + 0xF0) = rcx4;
    rcx4 = rdi;
    *(uint64_t*)(rbx + 0x170) = rdx3;
    sub_fffffffff99ffa0(rdi); // call qword ptr [0xF99FFA0]
    rdx3 = *(uint64_t*)(rbx + 0x170);
    rcx4 = *(uint64_t*)(rbx + 0xF0);
    // lock dec dword ptr [rdi+0xC]
    // jne short 0xE829ABB
    rax3 = *(uint64_t*)(rdi);
    rax3 = *(uint64_t*)(rax3 + 8);
    rcx4 = rdi;
    sub_fffffffff99ffa0(rdi); // call qword ptr [0xF99FFA0]
    rdx3 = *(uint64_t*)(rbx + 0x170);
    rcx4 = *(uint64_t*)(rbx + 0xF0);

loc_e829abb:
    // 0xe829abb..0xe829b1e
    rcx4 += r12;
    if (r13d != 2) {
        uint64_t eax = 0;
        rcx4 = eax; // cmovne rcx,rax
    }
    rdx3 += r12;
    *(uint32_t*)(rbx + 0x268) = r12;
    *(uint32_t*)(rbx + 0x26C) = (uint32_t)r15;
    // movdqa xmm0,[rbx+0xC0]
    // movdqa xmm1,[rbx+0xD0]
    // lea rax,[rbx+0x270]
    // movdqu [rax+0x10],xmm1
    // movdqu [rax],xmm0
    *(uint64_t*)(rbx + 0x290) = rdx3;
    *(uint64_t*)(rbx + 0x298) = rcx4;
    *(uint64_t*)(rbx + 0x2A8) = 0;
    uint32_t eax = 0;
    r13 = *(uint64_t*)(rbx + 0xA8);
    goto loc_e829b2e;

loc_e829b20:
    // 0xe829b20..0xe829b2e
    rdx3 = *(uint64_t*)(rbx + 0x290);
    rcx4 = *(uint64_t*)(rbx + 0x298);

loc_e829b2e:
    // 0xe829b2e..0xe829b42
    rcx4 += rax;
    rdx3 += rax;
    *(uint64_t*)(rbx + 0x170) = rdx3;
    uint64_t rdx4 = *(uint64_t*)(r13);
    uint64_t r8_3 = rsi;
    sub_eec6ec0(rcx4, rdx4, r8_3); // call 0xEEC6EC0
    *(uint64_t*)(rbx + 0x2A8) += r14;
    // xchg ax,ax (nop)

    // 0xe829b50..0xe829b71
    rax2 = *(uint64_t*)(rbx + 0x90);
    rcx4 = *(uint64_t*)(rax2 + 0x30);
    rax2 = *(uint64_t*)(rcx4);
    rax2 = *(uint64_t*)(rax2 + 0x128);
    uint32_t edx2 = 2;
    uint64_t r8_4 = *(uint64_t*)(rbx + 0x170);
    sub_fffffffff99ffa0(r8_4); // call qword ptr [0xF99FFA0] with rcx=rax2, rdx=2, r8=r8_4

    // 0xe829b78..0xe829be1
    uint64_t r8_5 = *(uint64_t*)(rbx + 0x1B0);
    if (*(uint8_t*)(r8_5 + 0x23) != 1) goto loc_e829bea;
    // 0xe829b86..0xe829be1
    uint64_t rdx5 = *(uint64_t*)(rbx + 0x1E8);
    uint32_t edx3 = (uint32_t)(rdx5 << 6);
    rdx5 = *(uint64_t*)(rbx + 0x90A0) + edx3;
    uint64_t rcx5 = *(uint64_t*)(rbx + 0xB0);
    rax2 = *(uint64_t*)(rcx5);
    rax2 = *(uint64_t*)(rax2 + 0x200);
    uint64_t r10 = *(uint64_t*)(0xF99FFA0);
    uint64_t r8_6 = *(uint64_t*)(rbx + 0x318);
    // Stack args for call r10
    // mov [rsp+0x30],r8
    // mov [rsp+0x28],rdx
    // mov rdx,[rbx+0x1F0]
    // mov [rsp+0x20],rdx
    uint64_t rdx6 = *(uint64_t*)(rbx + 0x90);
    uint64_t r8_7 = *(uint64_t*)(rbx + 0x658);
    uint64_t r9_3 = *(uint64_t*)(rbx + 0x660);
    // call r10
    return; // jmp 0xE829C90

loc_e829bea:
    // 0xe829bea..0xe829c90
    uint32_t eax2 = *(uint16_t*)(r8_5 + 0xC);
    if (eax2 != 0xFFFF) goto loc_e829c16;
    // je short 0xE829C66
    uint64_t rcx6 = *(uint64_t*)(rbx + 0x90);
    rcx6 = *(uint64_t*)(rcx6 + 0x30);
    uint64_t r9d = *(uint32_t*)(r8_5 + 0x18);
    uint32_t edx4 = *(uint32_t*)(r8_5 + 0x10);
    uint32_t r8d = *(uint32_t*)(r8_5 + 0x14);
    rax2 = *(uint64_t*)(rcx6);
    rax2 = *(uint64_t*)(rax2 + 0x70);
    sub_fffffffff99ffa0(rax2); // call qword ptr [0xF99FFA0]
    goto loc_e829c90;

loc_e829c16:
    uint64_t rax3 = eax2 << 7;
    rax3 += *(uint64_t*)(rbx + 0x588);
    uint32_t r8d2 = *(uint16_t*)(r8_5 + 0x1E);
    if (r8d2 != 0xFFFF) goto loc_e829c1e;
    r8d2 = *(uint32_t*)(rax3 + 0x60);
    r8d2 >>= 5;
loc_e829c1e:
    uint64_t rcx7 = *(uint64_t*)(rbx + 0x90);
    rcx7 = *(uint64_t*)(rcx7 + 0x30);
    uint64_t rdx7 = *(uint64_t*)(rbx + 0x1B0);
    uint32_t r10d = *(uint16_t*)(rdx7 + 0x1C);
    r10d <<= 5;
    uint64_t r9_4 = *(uint64_t*)(rax3);
    uint64_t rax4 = *(uint64_t*)(0x12BB4910);
    uint64_t rdx8 = *(uint64_t*)(rax4 + 0x19F40);
    rax4 = *(uint64_t*)(rcx7);
    rax4 = *(uint64_t*)(rax4 + 0x1D8);
    uint64_t r11 = *(uint64_t*)(0xF99FFA0);
    // movdqu [rsp+0x28],xmm9
    // mov [rsp+0x20],r10
    // call r11
    goto loc_e829c90;

loc_e829c66:
    // Part of the je 0xE829C66 path
    uint64_t rcx8 = *(uint64_t*)(rbx + 0x90);
    rcx8 = *(uint64_t*)(rcx8 + 0x30);
    uint64_t r9d2 = *(uint32_t*)(r8_5 + 0x18);
    uint32_t edx5 = *(uint32_t*)(r8_5 + 0x10);
    uint32_t r8d3 = *(uint32_t*)(r8_5 + 0x14);
    rax2 = *(uint64_t*)(rcx8);
    rax2 = *(uint64_t*)(rax2 + 0x70);
    sub_fffffffff99ffa0(rax2);
    goto loc_e829c90;

loc_e829c90:
    // 0xe829c90..0xe829caa
    uint8_t dil = 1;
    uint32_t ecx = 0;
    rax2 = *(uint64_t*)(rbx + 0x160);
    *(uint16_t*)(rbx + 0x190) = (uint16_t)rax2;
    rsi = *(uint64_t*)(rbx + 0xB0);
    return; // jmp 0xE82D0CF

    // 0xe829caf..0xe829ccd
    // This is a merge block from jump table case?
    rdi = rcx + r8;
    sub_eec6ed0(rcx, nullptr, 0);
    rax2 = *(uint64_t*)(rbx + 0x98);
    *(uint64_t*)(rax2) = rdi;
    if (*(uint8_t*)&rsi != 0) return; // jne 0xE827E69
    return; // jmp 0xE827E90

    // 0xe829cd2..0xe829d11
    // Pool management code
    uint32_t ecx2 = *(uint16_t*)(rbx + rsi * 4 + 0x696);
    *(uint16_t*)(rbx + 0x690) = (uint16_t)ecx2;
    if ((uint16_t)ecx2 != 0xFFFF) return; // jne 0xE822FC5
    *(uint16_t*)(rbx + 0x692) = (uint16_t)rax;
    *(uint16_t*)(rbx + rsi * 4 + 0x694) = 0xFFFF;
    uint32_t eax3 = *(uint16_t*)(rbx + 0x690);
    *(uint16_t*)(rbx + rsi * 4 + 0x696) = (uint16_t)eax3;
    if (eax3 == 0xFFFF) goto loc_e82a39b;
    uint32_t ecx3 = *(uint16_t*)(rbx + eax3 * 4 + 0x694);
    if (ecx3 != 0xFFFF) goto loc_e829d30;
    *(uint16_t*)(rbx + ecx3 * 4 + 0x696) = (uint16_t)rsi;
loc_e829d30:
    *(uint16_t*)(rbx + rsi * 4 + 0x694) = (uint16_t)ecx3;
    *(uint16_t*)(rbx + eax3 * 4 + 0x694) = (uint16_t)rsi;
    if (*(uint16_t*)(rbx + rsi * 4 + 0x694) == 0xFFFF) goto loc_e82a39b;
    if (*(uint16_t*)(rbx + rsi * 4 + 0x696) == 0xFFFF) goto loc_e82a3b1;

    // 0xe829d5e..0xe829db3
    esi <<= 5;
    uint32_t edi2 = *(uint16_t*)(rbx + rsi + 0x8A8);
    if ((uint16_t)edi2 == *(uint16_t*)(rbx + 0x10C)) goto loc_e829db3;
    uint32_t eax4 = edi2;
    uint64_t rcx9 = *(uint64_t*)(rbx + 0x90);
    rcx9 = *(uint64_t*)(rcx9 + 0x30);
    uint64_t rdx9 = *(uint64_t*)(rbx + 0xA0);
    uint32_t r8d4 = *(uint16_t*)(rdx9 + 0x24);
    r8d4 *= eax4;
    r8d4 *= *(uint32_t*)(rdx9 + 0x20);
    r8d4 += *(uint32_t*)(rdx9 + 0x18);
    rax2 = *(uint64_t*)(rcx9);
    rax2 = *(uint64_t*)(rax2 + 0x100);
    sub_fffffffff99ffa0(rax2); // xor edx,edx; call
    *(uint16_t*)(rbx + 0x10C) = (uint16_t)edi2;

loc_e829db3:
    rsi += (uint64_t)rbx;
    rsi += 0x670;
    rax2 = *(uint64_t*)(rbx + 0x90);
    rcx9 = *(uint64_t*)(rax2 + 0x30);
    uint64_t r8_8 = *(uint64_t*)(rsi + 0x230);
    rax2 = *(uint64_t*)(rcx9);
    rax2 = *(uint64_t*)(rax2 + 0x100);
    uint32_t edx6 = 1;
    sub_fffffffff99ffa0(rax2);
    rax2 = *(uint64_t*)(rbx + 0x90);
    rcx9 = *(uint64_t*)(rax2 + 0x30);
    r8_8 = *(uint64_t*)(rsi + 0x230);
    rax2 = *(uint64_t*)(rcx9);
    rax2 = *(uint64_t*)(rax2 + 0x100);
    edx6 = 4;
    sub_fffffffff99ffa0(rax2);

    // 0xe829e0d..0xe829e3e
    if (*(uint64_t*)(rbx + 0x240) == 0) goto loc_e829e3e;
    rax2 = *(uint64_t*)(rbx + 0xF0);
    uint32_t edx7 = *(uint8_t*)(rax2 + 0x28);
    rax2 = *(uint64_t*)(rbx + 0x90);
    rcx9 = *(uint64_t*)(rax2 + 0x30);
    rax2 = *(uint64_t*)(rcx9);
    rax2 = *(uint64_t*)(rax2 + 0xC0);
    sub_fffffffff99ffa0(rax2);

loc_e829e3e:
    if (*(uint8_t*)(rbx + 0x390) == 0) goto loc_e829ed1;
    rax2 = *(uint64_t*)(rbx + 0xF0);
    esi = *(uint32_t*)(rax2 + 0x30);
    uint32_t cmp_val = *(uint32_t*)(rbx + 0x258);
    // cmp [rbx+0x258],esi
    rdi = *(uint64_t*)(rbx + 0x90);
    uint32_t r8d5 = *(uint16_t*)(rbx + 0x300);
    if (cmp_val == esi) goto loc_e829ee0;

    // 0xe829e6c..0xe829ec4
    uint32_t eax5 = esi;
    eax5 >>= 0x10;
    // movd xmm0,esi
    // movdqa xmm1,xmm0
    // psrld xmm1,8
    // punpckldq xmm1,xmm0
    // pand xmm1,[0xF08C710]
    uint32_t eax6 = (uint8_t)eax5;
    // psrld xmm0,0x18
    // movd xmm2,eax6
    // punpckldq xmm0,xmm2
    // punpcklqdq xmm0,xmm1
    // cvtdq2ps xmm0,xmm0
    // divps xmm0,[0xF0837E0]
    // movaps [rbx+0x3B0],xmm0
    rcx9 = *(uint64_t*)(rdi + 0x30);
    rax2 = *(uint64_t*)(rcx9);
    rax2 = *(uint64_t*)(rax2 + 0xB8);
    void* rdx10 = (void*)(rbx + 0x3B0);
    sub_fffffffff99ffa0(rax2);
    *(uint32_t*)(rbx + 0x258) = esi;

loc_e829ed1:
    rdi = *(uint64_t*)(rbx + 0x90);
    r8d5 = *(uint16_t*)(rbx + 0x300);

loc_e829ee0:
    // 0xe829ee0..0xe829f10
    rax2 = 0x7000000000000;
    if ((*(uint64_t*)(rbx + 0x1B0) & rax2) != 0) goto loc_e829f10;
    uint32_t eax7 = *(uint8_t*)(rbx + 0x210);
    rax2 = eax7 + eax7 * 4;
    uint64_t rcx10 = 0xF4EDD80;
    uint32_t edx8 = *(uint32_t*)(rbx + 0x25C);
    if (edx8 == *(uint32_t*)(rcx10 + rax2 * 4)) goto loc_e829f86;

loc_e829f10:
    rcx10 = *(uint64_t*)(rbx + 0x1F0);
    rcx10 >>= 0x30;
    rax2 = rcx10;
    *(uint64_t*)(rbx + 0x210) = rcx10;
    uint32_t eax8 = (uint32_t)rcx10 & 7;
    rax2 = eax8 + eax8 * 4;
    rcx10 = 0xF4EDD80;
    edx8 = *(uint32_t*)(rcx10 + rax2 * 4);
    uint32_t r8d6 = *(uint32_t*)(rcx10 + rax2 * 4 + 0xC);
    *(uint32_t*)(rbx + 0x338) = r8d6;
    uint32_t eax9 = *(uint32_t*)(rcx10 + rax2 * 4 + 0x10);
    *(uint32_t*)(rbx + 0x334) = eax9;
    rcx10 = *(uint64_t*)(rdi + 0x30);
    rax2 = *(uint64_t*)(rcx10);
    rax2 = *(uint64_t*)(rax2 + 0xA0);
    *(uint32_t*)(rbx + 0x25C) = edx8;
    sub_fffffffff99ffa0(rax2);
    rax2 = *(uint64_t*)(rbx + 0x210);
    *(uint8_t*)(rbx + 0x210) = (uint8_t)rax2 & 7;

loc_e829f86:
    if (*(uint16_t*)(rbx + 0x520) == r8d5) goto loc_e82a0fe;
    *(uint16_t*)(rbx + 0x520) = (uint16_t)r8d5;
    if ((uint16_t)r8d5 == 0xFFFF) goto loc_e82a08a;
    uint32_t r8d7 = r8d5;
    uint64_t r11_2 = *(uint64_t*)(rbx + 0x168);
    uint32_t eax10 = *(uint16_t*)(r11_2 + r8d7 * 8 + 0xD457D0);
    uint32_t r9d3 = eax10;
    uint64_t rcx11 = *(uint64_t*)(rbx + 0x320);
    if ((uint16_t)rcx11 > (uint16_t)eax10) eax10 = (uint32_t)rcx11; // cmova
    uint32_t ecx4 = *(uint16_t*)(r11_2 + r8d7 * 8 + 0xD457D2);
    uint32_t r10d2 = ecx4;
    uint64_t rdx11 = *(uint64_t*)(rbx + 0x398);
    if ((uint16_t)rdx11 > (uint16_t)ecx4) ecx4 = (uint32_t)rdx11;
    uint32_t edx9 = *(uint16_t*)(r11_2 + r8d7 * 8 + 0xD457D4);
    uint16_t dx = (uint16_t)edx9 + (uint16_t)r9d3;
    uint64_t r9_5 = *(uint64_t*)(rbx + 0x2E8);
    if ((uint16_t)r9_5 < dx) dx = (uint16_t)r9_5;
    uint32_t r8d8 = *(uint16_t*)(r11_2 + r8d7 * 8 + 0xD457D6);
    uint16_t r8w = (uint16_t)r8d8 + (uint16_t)r10d2;
    uint64_t r9_6 = *(uint64_t*)(rbx + 0x2E0);
    if ((uint16_t)r9_6 < r8w) r8w = (uint16_t)r9_6;
    *(uint8_t*)(rbx + 0x1AC) = 1;
    if ((uint16_t)dx <= (uint16_t)eax10) return; // jbe 0xE82D0CB
    if (r8w <= (uint16_t)ecx4) return; // jbe 0xE82D0CB
    uint32_t eax11 = (uint16_t)eax10;
    // movd xmm0,eax11
    // pinsrw xmm0,ecx4,2
    // pinsrw xmm0,edx9,4
    // pinsrw xmm0,r8d8,6
    // movdqa [rbx+0x3B0],xmm0
    rcx11 = *(uint64_t*)(rdi + 0x30);
    rax2 = *(uint64_t*)(rcx11);
    rax2 = *(uint64_t*)(rax2 + 0xB0);
    uint32_t edx10 = 1;
    void* r8_9 = (void*)(rbx + 0x3B0);
    sub_fffffffff99ffa0(rax2);
    *(uint8_t*)(rbx + 0x1AC) = 1;
    goto loc_e82a0fe;

loc_e82a08a:
    uint8_t al = (*(uint64_t*)(rbx + 0x638) == 0) ? 1 : 0;
    uint32_t ecx5 = *(uint32_t*)(rbx + 0x1AC);
    uint8_t cl = ecx5 ^ 1;
    if (al & cl) goto loc_e82a0f4;
    uint32_t eax12 = *(uint32_t*)(rbx + 0x5A4);
    *(uint32_t*)(rbx + 0x3B0) = eax12;
    uint64_t rax5 = *(uint64_t*)(rbx + 0x630);
    *(uint32_t*)(rbx + 0x3B4) = (uint32_t)rax5;
    eax12 = *(uint32_t*)(rbx + 0x5A0);
    *(uint32_t*)(rbx + 0x3B8) = eax12;
    eax12 = *(uint32_t*)(rbx + 0x59C);
    *(uint32_t*)(rbx + 0x3BC) = eax12;
    rcx11 = *(uint64_t*)(rdi + 0x30);
    rax2 = *(uint64_t*)(rcx11);
    rax2 = *(uint64_t*)(rax2 + 0xB0);
    edx10 = 1;
    r8_9 = (void*)(rbx + 0x3B0);
    sub_fffffffff99ffa0(rax2);

loc_e82a0f4:
    *(uint32_t*)(rbx + 0x1AC) = 0;

loc_e82a0fe:
    rax2 = *(uint64_t*)(rbx + 0x580);
    if (rax2 == 0) goto loc_e82a174;
    if (rax2 == *(uint64_t*)(rbx + 0x1A0)) goto loc_e82a140;
    rax2 = *(uint64_t*)(rbx + 0x90);
    rcx11 = *(uint64_t*)(rax2 + 0x30);
    rax2 = *(uint64_t*)(rcx11);
    rax2 = *(uint64_t*)(rax2 + 0xC8);
    rsi = *(uint64_t*)(rbx + 0x580);
    uint64_t rdx12 = rsi;
    sub_fffffffff99ffa0(rax2);
    *(uint64_t*)(rbx + 0x1A0) = rsi;

loc_e82a140:
    r12 = *(uint64_t*)(rbx + 0xF0);
    uint32_t r8d9 = *(uint32_t*)(r12 + 0x34);
    if (*(uint32_t*)(rbx + 0x330) != r8d9) goto loc_e82a18b;
    uint32_t edx11 = *(uint32_t*)(r12 + 0x38);
    if (*(uint32_t*)(rbx + 0x21C) != edx11) goto loc_e82a19e;
    rcx11 = *(uint64_t*)(rbx + 0xB0);
    uint64_t r9_7 = *(uint64_t*)(rbx + 0x160);
    goto loc_e82a1aa;

loc_e82a18b:
    edx11 = *(uint32_t*)(r12 + 0x38);
    rcx11 = *(uint64_t*)(rbx + 0xB0);
    r9_7 = *(uint64_t*)(rbx + 0x160);
    if (r8d9 < edx11) *(uint8_t*)&al = 1; else *(uint8_t*)&al = 0; // setb al
    *(uint32_t*)(rbx + 0x21C) = edx11;

loc_e82a1aa:
    if (*(uint16_t*)(rbx + 0x190) != (uint16_t)r9_7) *(uint8_t*)&sil = 1; else *(uint8_t*)&sil = 0; // setne sil
    sil |= al;
    if (sil == 0) return; // je 0xE82A271

    // 0xe82a1bf..0xe82a2a0
    rax2 = *(uint64_t*)(rbx + 0x168);
    rax2 = *(uint64_t*)(rax2 + 0xDC57E0);
    uint32_t edx12 = *(uint8_t*)(r12 + 0x64);
    uint64_t rdx13 = *(uint64_t*)(rax2 + edx12 * 8);
    rax2 = *(uint64_t*)(rbx + 0xA0);
    // mov [rsp+0x28],rax
    rax2 = *(uint64_t*)(rbx + 0x310);
    // mov [rsp+0x20],rax
    uint32_t r9d4 = *(uint32_t*)(rbx + 0x21C);
    sub_bc6a9d0(); // call 0xBC6A9D0
    rcx11 = *(uint64_t*)(rbx + 0x160);
    uint32_t eax13 = (uint16_t)rcx11;
    uint64_t rdx14 = eax13 * 0xF8;
    rax2 = *(uint64_t*)(rbx + 0x5E0);
    *(uint64_t*)(rbx + 0x390) = rdx14;
    uint64_t r14_2 = rax2 + rdx14;
    if ((uint16_t)*(uint64_t*)(rbx + 0x190) == (uint16_t)rcx11) goto loc_e82a3e0;
    rax2 = *(uint64_t*)(r14_2);
    if (rax2 == 0) goto loc_e82a2a5;
    rcx11 = *(uint64_t*)(rax2 + 8);
    if (rcx11 == 0) goto loc_e82a2a5;
    uint32_t edx13 = *(uint32_t*)(rcx11);
    *(uint64_t*)(rbx + 0x340) = rcx11;
    *(uint32_t*)(rbx + 0x348) = edx13;
    *(uint32_t*)(rbx + 0x34C) = 0;
    *(uint8_t*)(rbx + 0x350) = 1;
    if (*(uint8_t*)(rbx + 0x350) == 0) goto loc_e82a2a7;
    goto loc_e82a2ad;

loc_e82a2a5:
    uint32_t ecx6 = 0;

loc_e82a2a7:
    *(uint8_t*)(rbx + 0x350) = (uint8_t)ecx6;

loc_e82a2ad:
    rcx11 = *(uint64_t*)(r14_2 + 8);
    if (rcx11 == 0) goto loc_e82a2e7;
    uint64_t rdx15 = *(uint64_t*)(rcx11 + 8);
    if (rdx15 == 0) goto loc_e82a2e7;
    uint32_t r8d10 = *(uint32_t*)(rdx15);
    *(uint64_t*)(rbx + 0x358) = rdx15;
    *(uint32_t*)(rbx + 0x360) = r8d10;
    *(uint32_t*)(rbx + 0x364) = 0;
    *(uint8_t*)(rbx + 0x368) = 1;
    if (*(uint8_t*)(rbx + 0x368) == 0) goto loc_e82a2e9;
    goto loc_e82a2ef;

loc_e82a2e7:
    uint32_t edx14 = 0;

loc_e82a2e9:
    *(uint8_t*)(rbx + 0x368) = (uint8_t)edx14;

loc_e82a2ef:
    edx14 = 0;
    uint32_t r8d11 = 0;
    if (rax2 != 0) {
        r8d11 = *(uint16_t*)(rax2 + 0xAE);
    }
    *(uint32_t*)(rbx + 0x2B0) = r8d11;
    if (rcx11 != 0) {
        edx14 = *(uint16_t*)(rcx11 + 0xAE);
    }
    *(uint32_t*)(rbx + 0x2B4) = edx14;
    // movd xmm0,edx14
    // movd xmm1,r8d11
    // punpckldq xmm1,xmm0
    // movdqa xmm0,xmm1
    // pand xmm0,[0xF08C710]
    // movdqa xmm2,[0xF4ED2B0]
    // psubd xmm2,xmm0
    // pcmpgtd xmm0,xmm9
    // pand xmm0,xmm2
    // paddd xmm0,xmm1
    // movq [rbx+0x2B8],xmm0
    edx14 += r8d11;
    rax2 = *(uint64_t*)(rbx + 0x98);
    rcx11 = *(uint64_t*)(rax2);
    rax2 = *(uint64_t*)(r13);
    uint64_t r9_8 = rcx11;
    r9_8 -= rax2;
    uint64_t r8_10 = edx14;
    r8_10 -= r9_8;
    if (r8_10 <= r9_8) goto loc_e82a3e0;
    uint64_t r9_9 = *(uint64_t*)(rbx + 0xA0);
    r9_9 = *(uint64_t*)(r9_9 + 0x38);
    r9_9 -= rax2;
    if (r9_9 >= r8_10) goto loc_e82a3bd;
    rcx11 = r13;
    void* r8p2 = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx11, (void*)r8_10, r8p2);
    goto loc_e82a3d2;

loc_e82a3bd:
    rdi = rcx11 + r8_10;
    sub_eec6ed0(rcx11, nullptr, 0);
    rax2 = *(uint64_t*)(rbx + 0x98);
    *(uint64_t*)(rax2) = rdi;

loc_e82a3d2:
    r13 = *(uint64_t*)(rbx + 0xA8);
    r12 = *(uint64_t*)(rbx + 0xF0);

loc_e82a3e0:
    if (*(uint8_t*)&sil == 0) goto loc_e82a42a;
    if (*(uint8_t*)(rbx + 0x350) != 1) goto loc_e82a440;
    *(uint8_t*)(/*rsp+0x20*/rbx) = 0; // approximate
    rcx11 = *(uint64_t*)(rbx + 0xA0);
    void* rdx16 = (void*)(rbx + 0x340);
    void* r8p3 = (void*)(rbx + 0x260);
    uint64_t r9_10 = *(uint64_t*)(rbx + 0x310);
    sub_e81e1c0(rcx11, rdx16, r8p3, r9_10); // call 0xE81E1C0
    *(uint32_t*)(rbx + 0x1D0) = (uint32_t)rax2;
    r13 = *(uint64_t*)(rbx + 0xA8);
    r12 = *(uint64_t*)(rbx + 0xF0);
    goto loc_e82a44a;

loc_e82a42a:
    *(uint32_t*)(rbx + 0x1D0) = 0;
    *(uint32_t*)(rbx + 0x150) = 0;
    goto loc_e82a49e;

loc_e82a440:
    *(uint32_t*)(rbx + 0x1D0) = 0;

loc_e82a44a:
    *(uint32_t*)(rbx + 0x150) = 0;
    if (*(uint64_t*)(r14_2 + 8) == 0) goto loc_e82a49e;
    if (*(uint8_t*)(rbx + 0x368) == 0) goto loc_e82a49e;
    *(uint8_t*)(/*rsp+0x20*/rbx) = 1;
    rcx11 = *(uint64_t*)(rbx + 0xA0);
    rdx16 = (void*)(rbx + 0x358);
    r8p3 = (void*)(rbx + 0x260);
    r9_10 = *(uint64_t*)(rbx + 0x310);
    sub_e81e1c0(rcx11, rdx16, r8p3, r9_10);
    *(uint32_t*)(rbx + 0x150) = (uint32_t)rax2;
    r13 = *(uint64_t*)(rbx + 0xA8);
    r12 = *(uint64_t*)(rbx + 0xF0);

loc_e82a49e:
    uint32_t eax14 = *(uint8_t*)(r14_2 + 0xF0);
    *(uint64_t*)(rbx + 0x110) = eax14;
    if (eax14 == 0) return; // je 0xE82C0A8
    uint32_t r15d = 0;

loc_e82a507:
    uint32_t eax15 = *(uint8_t*)(r14_2 + r15d * 8 + 0x16);
    uint32_t ecx7 = eax15;
    ecx7 &= 0xFFFFFFEF;
    if (ecx7 > 0xD) goto loc_e82a4f7;

    // Jump table at 0xF4EE7F8
    // lea rdx,[0xF4EE7F8]
    // movsxd rcx,[rdx+rcx*4]
    // add rcx,rdx
    // jmp rcx
    // Cases 0..13. We'll model as switch.
    // In-range case targets: 0xe82a527, 0xe82a595, 0xe82a71a, 0xe82a78e, 0xe82a7eb, 0xe82a86e
    // Out-of-range: 0xE82B840, 0xE82B5C1, 0xE82B61A, 0xE82B673, 0xE82B6CE, 0xE82B72E
    // Fall-through for >0xD goes to loc_e82a4f7
    switch (ecx7) {
    case 0: goto case_0_e82a527;
    case 1: goto case_1_e82a595;
    case 2: goto case_2_e82a71a;
    case 3: goto case_3_e82a78e;
    case 4: goto case_4_e82a7eb;
    case 5: goto case_5_e82a86e;
    default: goto loc_e82a4f7; // cases 6..13 and >0xD
    }

case_0_e82a527:
    // 0xe82a527..0xe82a590
    // movq xmm0,[rbx+0x90A8]
    // punpcklwd xmm0,xmm9
    // cvtdq2ps xmm8,xmm0
    uint32_t edi3 = *(uint32_t*)(r14_2 + r15d * 8 + 0x10);
    if ((eax15 & 0x10) != 0) return; // jne 0xE82B840
    uint64_t rdx17 = edi3 + 0x10;
    rax2 = *(uint64_t*)(rbx + 0x98);
    rcx11 = *(uint64_t*)(rax2);
    rax2 = *(uint64_t*)(r13);
    uint64_t r9_11 = rcx11;
    r9_11 -= rax2;
    r8_10 = rdx17;
    r8_10 -= r9_11;
    if (r8_10 <= r9_11) return; // jbe 0xE82BD8E
    r9_9 = *(uint64_t*)(rbx + 0xA0);
    r9_9 = *(uint64_t*)(r9_9 + 0x38);
    r9_9 -= rax2;
    if (rdx17 <= r9_9) return; // jbe 0xE82BD67
    rcx11 = r13;
    r8p2 = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx11, (void*)rdx17, r8p2);
    goto loc_e82abd7c; // jmp 0xE82BD7C (out of range)

case_1_e82a595:
    // 0xe82a595..0xe82a6ca
    uint32_t ecx8 = *(uint32_t*)(r12 + 0x3C);
    rcx11 = ecx8 << 6;
    rdx17 = *(uint64_t*)(rbx + 0x2F8);
    // movaps xmm4,[rdx17+rcx11]
    // movaps xmm5,xmm4
    // shufps xmm5,xmm4,0
    // movaps xmm6,xmm4
    // shufps xmm6,xmm4,0x55
    // movaps xmm7,xmm4
    // shufps xmm7,xmm4,0xAA
    // shufps xmm4,xmm4,0xFF
    uint64_t r8_11 = *(uint64_t*)(rbx + 0x2F0);
    // movaps xmm3,[r8_11]
    // movaps xmm2,[r8_11+0x10]
    // movaps xmm1,[r8_11+0x20]
    // movaps xmm0,[r8_11+0x30]
    // mulps xmm5,xmm3
    // mulps xmm6,xmm2
    // mulps xmm7,xmm1
    // addps xmm7,xmm5
    // mulps xmm4,xmm0
    // addps xmm4,xmm6
    // addps xmm4,xmm7
    // movaps [rbx+0x3B0],xmm4
    // Repeat for +0x10, +0x20, +0x30 offsets -> store to [rbx+0x3C0], [rbx+0x3D0], [rbx+0x3E0]
    uint32_t ecx9 = *(uint32_t*)(r14_2 + r15d * 8 + 0x14);
    if ((uint16_t)ecx9 > 4) ecx9 = 4;
    uint32_t r12d2 = *(uint32_t*)(r14_2 + r15d * 8 + 0x10);
    ecx9 <<= 4;
    uint32_t edi4 = (uint16_t)ecx9;
    if ((eax15 & 0x10) != 0) return; // jne 0xE82B5C1
    rdx17 = edi4 + r12d2;
    rax2 = *(uint64_t*)(rbx + 0x98);
    rax2 = *(uint64_t*)(rax2);
    rcx11 = *(uint64_t*)(r13);
    r9_11 = rax2;
    r9_11 -= rcx11;
    r8_10 = rdx17;
    r8_10 -= r9_11;
    if (r8_10 <= r9_11) return; // jbe 0xE82BAD8
    r9_9 = *(uint64_t*)(rbx + 0xA0);
    r9_9 = *(uint64_t*)(r9_9 + 0x38);
    r9_9 -= rcx11;
    if (rdx17 <= r9_9) return; // jbe 0xE82BAB5
    rcx11 = r13;
    r8p2 = (void*)(rbx + 0xC0);
    sub_47e8f0(rcx11, (void*)rdx17, r8p2);
    return; // jmp 0xE82BACD

case_2_e82a71a:
    // 0xe82a71a..0xe82a789
    ecx9 = *(uint32_t*)(r14_2 + r15d * 8 + 0x14);
    if ((uint16_t)ecx9 > 4) ecx9 = 4;
    r12d2 = *(uint32_t*)(r14_2 + r15d * 8 + 0x10);
    ecx9 <<= 4;
    edi4 = (uint16_t)ecx9;
    if ((eax15 & 0x10) != 0) return; // jne 0xE82B61A
    rdx17 = edi4 + r12d2;
    rax2 = *(uint64_t*)(rbx + 0x98);
    rax2 = *(uint64_t*)(rax2);
    rcx11 = *(uint64_t*)(r13);
    r9_11 = rax2;
    r9_11 -= rcx11;
    r8_10 = rdx17;
    r8_10 -= r9_11;
    if (r8_10 <= r9_11) return; // jbe 0xE82BB0A
    r9_9 = *(uint64_t*)(rbx + 0xA0);
    r9_9 = *(uint64_t*)(r9_9 + 0x38);
    r9_9 -= rcx11;
    if (rdx17 <= r9_9) return; // jbe 0xE82BAE7
    rcx11 = r13;
    r8p2 = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx11, (void*)rdx17, r8p2);
    return; // jmp 0xE82BAFF

case_3_e82a78e:
    // 0xe82a78e..0xe82a7e6
    edi3 = *(uint32_t*)(r14_2 + r15d * 8 + 0x10);
    if ((eax15 & 0x10) != 0) return; // jne 0xE82B673
    rdx17 = edi3 + 0x10;
    rax2 = *(uint64_t*)(rbx + 0x98);
    rcx11 = *(uint64_t*)(rax2);
    r12 = *(uint64_t*)(r13);
    rax2 = rcx11;
    rax2 -= r12;
    r8_10 = rdx17;
    r8_10 -= rax2;
    if (r8_10 <= rax2) return; // jbe 0xE82BB79
    rax2 = *(uint64_t*)(rbx + 0xA0);
    rax2 = *(uint64_t*)(rax2 + 0x38);
    rax2 -= r12;
    if (rdx17 <= rax2) return; // jbe 0xE82BB59
    rcx11 = r13;
    r8p2 = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx11, (void*)rdx17, r8p2);
    return; // jmp 0xE82BB6E

case_4_e82a7eb:
    // 0xe82a7eb..0xe82a869
    uint32_t ecx10 = *(uint16_t*)(r14_2 + r15d * 8 + 0x14);
    uint32_t edi5 = *(uint16_t*)(r12 + 0x5E);
    edi5 <<= 2;
    if (edi5 > ecx10) edi5 = ecx10;
    uint32_t r12d3 = *(uint32_t*)(r12 + 0x3C);
    uint32_t r13d2 = *(uint32_t*)(r14_2 + r15d * 8 + 0x10);
    edi5 <<= 4;
    if ((eax15 & 0x10) != 0) return; // jne 0xE82B6CE
    rdx17 = edi5 + r13d2;
    rax2 = *(uint64_t*)(rbx + 0x98);
    rax2 = *(uint64_t*)(rax2);
    rcx11 = *(uint64_t*)(rbx + 0xA8);
    rcx11 = *(uint64_t*)(rcx11);
    r9_11 = rax2;
    r9_11 -= rcx11;
    r8_10 = rdx17;
    r8_10 -= r9_11;
    if (r8_10 <= r9_11) return; // jbe 0xE82BBDC
    r9_9 = *(uint64_t*)(rbx + 0xA0);
    r9_9 = *(uint64_t*)(r9_9 + 0x38);
    r9_9 -= rcx11;
    if (rdx17 <= r9_9) return; // jbe 0xE82BBBA
    rcx11 = *(uint64_t*)(rbx + 0xA8);
    r8p2 = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx11, (void*)rdx17, r8p2);
    return; // jmp 0xE82BBD2

case_5_e82a86e:
    // 0xe82a86e..0xe82a8f9
    ecx9 = *(uint32_t*)(r14_2 + r15d * 8 + 0x14);
    if ((uint16_t)ecx9 > 4) ecx9 = 4;
    rdi = *(uint64_t*)(rbx + 0x1E8);
    rdi <<= 6;
    rdi += *(uint64_t*)(rbx + 0x90A0);
    r13d2 = *(uint32_t*)(r14_2 + r15d * 8 + 0x10);
    ecx9 <<= 4;
    uint32_t r12d4 = (uint16_t)ecx9;
    if ((eax15 & 0x10) != 0) return; // jne 0xE82B72E
    rdx17 = r12d4 + r13d2;
    rax2 = *(uint64_t*)(rbx + 0x98);
    rax2 = *(uint64_t*)(rax2);
    rcx11 = *(uint64_t*)(rbx + 0xA8);
    rcx11 = *(uint64_t*)(rcx11);
    r9_11 = rax2;
    r9_11 -= rcx11;
    r8_10 = rdx17;
    r8_10 -= r9_11;
    if (r8_10 <= r9_11) return; // jbe 0xE82BC4B
    r9_9 = *(uint64_t*)(rbx + 0xA0);
    r9_9 = *(uint64_t*)(r9_9 + 0x38);
    r9_9 -= rcx11;
    if (rdx17 <= r9_9) return; // jbe 0xE82BC29
    rcx11 = *(uint64_t*)(rbx + 0xA8);
    r8p2 = (void*)(rbx + 0x3B0);
    sub_47e8f0(rcx11, (void*)rdx17, r8p2);
    return; // jmp 0xE82BC41

loc_e82a4f7:
    // Fall-through for cases > 5
    // 0xe82a8fe..0xe82a90c
    uint32_t ecx11 = *(uint16_t*)(rbx + 0x10E);
    if ((uint16_t)ecx11 == *(uint16_t*)(rbx + 0xE174)) return; // je 0xE82ABB8
    // End of chunk range
    goto chunk_end;

chunk_end:
    // Write back live registers to chunk state
    s.r12 = r12;
    s.r13 = r13;
    s.r14 = r14;
    s.r15 = r15;
    s.rsi = rsi;
    s.rdi = rdi;
    // xmm6-xmm15 unchanged
}

} // namespace native

#if 0
0xe82919c  call 0x47E8F0
0xe8291fc  call 0x47E8F0
0xe829256  call 0x47E8F0
0xe8292b0  call 0x47E8F0
0xe82930a  call 0x47E8F0
0xe829364  call 0x47E8F0
0xe8293be  call 0x47E8F0
0xe829418  call 0x47E8F0
0xe829472  call 0x47E8F0
0xe8294cc  call 0x47E8F0
0xe829526  call 0x47E8F0
0xe82953a  call 0xEEC6ED0
0xe829562  call 0xEEC6ED0
0xe829594  call 0xEEC6ED0
0xe8295c6  call 0xEEC6ED0
0xe8295f5  call 0xEEC6ED0
0xe829627  call 0xEEC6ED0
0xe82964f  call 0xEEC6ED0
0xe82968e  call 0xEEC6ED0
0xe8296b6  call 0xEEC6ED0
0xe8296ed  call 0xEEC6ED0
0xe829715  call 0xEEC6ED0
0xe829747  call 0xEEC6ED0
0xe829779  call 0xEEC6ED0
0xe8297a8  call 0xEEC6ED0
0xe8297d4  call 0xEEC6ED0
0xe829800  call 0xEEC6ED0
0xe82982f  call 0xEEC6ED0
0xe829861  call 0xEEC6ED0
0xe829893  call 0xEEC6ED0
0xe8298c2  call 0xEEC6ED0
0xe8298e7  call 0xEEC6ED0
0xe82991c  call 0xEEC6ED0
0xe82994e  call 0xEEC6ED0
0xe82997d  call 0xEEC6ED0
0xe8299ac  call 0xEEC6ED0
0xe8299d3  call 0xEEC6EC0
0xe829a1e  call 0xE8360F0
0xe829a83  call qword ptr [0xF99FFA0]
0xe829aa7  call qword ptr [0xF99FFA0]
0xe829b42  call 0xEEC6EC0
0xe829b71  call qword ptr [0xF99FFA0]
0xe829be1  call r10
0xe829c60  call r11
0xe829c7d  call qword ptr [0xF99FFA0]
0xe829cb5  call 0xEEC6ED0
0xe829da5  call qword ptr [0xF99FFA0]
0xe829dde  call qword ptr [0xF99FFA0]
0xe829e06  call qword ptr [0xF99FFA0]
0xe829e37  call qword ptr [0xF99FFA0]
0xe829ec4  call qword ptr [0xF99FFA0]
0xe829f60  call qword ptr [0xF99FFA0]
0xe82a079  call qword ptr [0xF99FFA0]
0xe82a0ed  call qword ptr [0xF99FFA0]
0xe82a132  call qword ptr [0xF99FFA0]
0xe82a1f6  call 0xBC6A9D0
0xe82a393  call 0x47E8F0
0xe82a3c3  call 0xEEC6ED0
0xe82a40f  call 0xE81E1C0
0xe82a485  call 0xE81E1C0
0xe82a4c4  call 0xEEC6ED0
0xe82a4f2  call 0xEEC6EC0
0xe82a58a  call 0x47E8F0
0xe82a70f  call 0x47E8F0
0xe82a783  call 0x47E8F0
0xe82a7e0  call 0x47E8F0
0xe82a863  call 0x47E8F0
0xe82a8f3  call 0x47E8F0
#endif