// LIFT 0xbc8a380 size 0x1afc 1.26.62.01 VV frame-graph builder
// CHUNK 0xbc8bb76..0xbc8be7c
#include "sub_bc8a380_chunk1.h"

namespace native {

// Chunk state struct documented in docs/functions/bc8a380.md section 'Chunk state'.
// State fields used by this chunk (live at boundary):
//   rbp frame (locals), rsi (data ptr), rdx (len), r8 (index), rcx (hash),
//   rax (remainder), r15 (data ptr for tail hash).

static inline void chunk_bc8bb76(State& s) {
// 0xbc8bb76..0xbc8bb7d
    s.saved_rcx = s.rcx;
    s.saved_r9  = s.r9;
// 0xbc8bb7d
    (void)0;
// 0xbc8bb84
#if 0
0xbc8bb84  call 0x75740
#endif
    sub_75740(s);
// 0xbc8bb89..0xbc8bb94
    s.rcx = 0xCBF29CE484222325ULL;
// 0xbc8bb94
    goto loc_bc8bc4a;
// 0xbc8bb99..0xbc8bba3
    s.rcx = 0xCBF29CE484222325ULL;
    goto loc_bc8bcf2;
// 0xbc8bba8..0xbc8bbb2
    s.rcx = 0xCBF29CE484222325ULL;
    goto loc_bc8bd9a;
// 0xbc8bbb7..0xbc8bbc1
    s.rdx = 0xCBF29CE484222325ULL;
    goto loc_bc8be51;
// 0xbc8bbc6..0xbc8bbd7
    s.rdx &= ~3ULL;
    s.rcx = 0xCBF29CE484222325ULL;
    s.r8 = 0;
    s.r9 = 0x100000001B3ULL;
// main 4-byte block loop
loc_bc8bbe1:
    for (; s.rdx != s.r8; ) {
// 0xbc8bbe1..0xbc8bc18
        uint64_t t = (uint8_t)s.mem[s.rsi + s.r8];
        t ^= s.rcx;
        t *= s.r9;
        uint64_t t2 = (uint8_t)s.mem[s.rsi + s.r8 + 1];
        t2 ^= t;
        t2 *= s.r9;
        uint64_t t3 = (uint8_t)s.mem[s.rsi + s.r8 + 2];
        t3 ^= t2;
        t3 *= s.r9;
        uint64_t t4 = (uint8_t)s.mem[s.rsi + s.r8 + 3];
        t4 ^= t3;
        t4 *= s.r9;
        s.rcx = t4;
        s.r8 += 4;
        if (s.rdx == s.r8) break;
    }
// 0xbc8bc1d..0xbc8bc20
    if (s.rax == 0) goto loc_bc8bc4a;
// 0xbc8bc22..0xbc8bc31
    s.rsi += s.r8;
    s.rdx = 0;
    s.r8 = 0x100000001B3ULL;
    s.r9 = s.rcx;
loc_bc8bc34:
    for (; s.rax != s.rdx; ) {
// 0xbc8bc34..0xbc8bc48
        uint64_t t = (uint8_t)s.mem[s.rsi + s.rdx];
        t ^= s.r9;
        t *= s.r8;
        s.rdx += 1;
        s.r9 = t;
        if (s.rax == s.rdx) break;
    }
    s.rcx = s.r9;
loc_bc8bc4a:
// 0xbc8bc4a
    s.mem_store64(0x12AE1B58ULL, s.rcx);
// 0xbc8bc51..0xbc8bc58
#if 0
0xbc8bc58  call 0x73150
#endif
    sub_73150(s, &s.frame[0x330]);
// 0xbc8bc5d..0xbc8bc64
#if 0
0xbc8bc64  call 0xE938D70
#endif
    sub_e938d70(s, (void*)0x12AE1B60ULL);
// 0xbc8bc69
    // jmp 0xBC8A3E2
    return;
// second hash variant (same structure, different store)
loc_bc8bc6e:
    s.rdx &= ~3ULL;
    s.rcx = 0xCBF29CE484222325ULL;
    s.r8 = 0;
    s.r9 = 0x100000001B3ULL;
    for (; s.rdx != s.r8; ) {
        uint64_t t = (uint8_t)s.mem[s.rsi + s.r8];
        t ^= s.rcx; t *= s.r9;
        uint64_t t2 = (uint8_t)s.mem[s.rsi + s.r8 + 1];
        t2 ^= t; t2 *= s.r9;
        uint64_t t3 = (uint8_t)s.mem[s.rsi + s.r8 + 2];
        t3 ^= t2; t3 *= s.r9;
        uint64_t t4 = (uint8_t)s.mem[s.rsi + s.r8 + 3];
        t4 ^= t3; t4 *= s.r9;
        s.rcx = t4;
        s.r8 += 4;
        if (s.rdx == s.r8) break;
    }
    if (s.rax != 0) {
        s.rsi += s.r8;
        s.rdx = 0;
        s.r8 = 0x100000001B3ULL;
        s.r9 = s.rcx;
        for (; s.rax != s.rdx; ) {
            uint64_t t = (uint8_t)s.mem[s.rsi + s.rdx];
            t ^= s.r9; t *= s.r8;
            s.rdx += 1;
            s.r9 = t;
            if (s.rax == s.rdx) break;
        }
        s.rcx = s.r9;
    }
    s.mem_store64(0x12AE1B68ULL, s.rcx);
#if 0
0xbc8bd00  call 0x73150
#endif
    sub_73150(s, &s.frame[0x330]);
#if 0
0xbc8bd0c  call 0xE938D70
#endif
    sub_e938d70(s, (void*)0x12AE1B70ULL);
    return;
// third variant
loc_bc8bd16:
    s.rdx &= ~3ULL;
    s.rcx = 0xCBF29CE484222325ULL;
    s.r8 = 0;
    s.r9 = 0x100000001B3ULL;
    for (; s.rdx != s.r8; ) {
        uint64_t t = (uint8_t)s.mem[s.rsi + s.r8];
        t ^= s.rcx; t *= s.r9;
        uint64_t t2 = (uint8_t)s.mem[s.rsi + s.r8 + 1];
        t2 ^= t; t2 *= s.r9;
        uint64_t t3 = (uint8_t)s.mem[s.rsi + s.r8 + 2];
        t3 ^= t2; t3 *= s.r9;
        uint64_t t4 = (uint8_t)s.mem[s.rsi + s.r8 + 3];
        t4 ^= t3; t4 *= s.r9;
        s.rcx = t4;
        s.r8 += 4;
        if (s.rdx == s.r8) break;
    }
    if (s.rax != 0) {
        s.rsi += s.r8;
        s.rdx = 0;
        s.r8 = 0x100000001B3ULL;
        s.r9 = s.rcx;
        for (; s.rax != s.rdx; ) {
            uint64_t t = (uint8_t)s.mem[s.rsi + s.rdx];
            t ^= s.r9; t *= s.r8;
            s.rdx += 1;
            s.r9 = t;
            if (s.rax == s.rdx) break;
        }
        s.rcx = s.r9;
    }
    s.mem_store64(0x12AE1B78ULL, s.rcx);
#if 0
0xbc8bda8  call 0x73150
#endif
    sub_73150(s, &s.frame[0x330]);
#if 0
0xbc8bdb4  call 0xE938D70
#endif
    sub_e938d70(s, (void*)0x12AE1B80ULL);
    return;
// fourth variant (8-byte block)
loc_bc8bdbe:
    s.r8 &= ~7ULL;
    s.rdx = 0xCBF29CE484222325ULL;
    for (; s.r8 != 0; ) {
        uint8_t b0 = (uint8_t)s.mem[s.r15];
        s.rdx *= s.rcx;
        s.rdx ^= b0;
        uint8_t b1 = (uint8_t)s.mem[s.r15+1];
        s.rdx *= s.rcx;
        s.rdx ^= b1;
        uint8_t b2 = (uint8_t)s.mem[s.r15+2];
        s.rdx *= s.rcx;
        s.rdx ^= b2;
        uint8_t b3 = (uint8_t)s.mem[s.r15+3];
        s.rdx *= s.rcx;
        s.rdx ^= b3;
        uint8_t b4 = (uint8_t)s.mem[s.r15+4];
        s.rdx *= s.rcx;
        s.rdx ^= b4;
        uint8_t b5 = (uint8_t)s.mem[s.r15+5];
        s.rdx *= s.rcx;
        s.rdx ^= b5;
        uint8_t b6 = (uint8_t)s.mem[s.r15+6];
        s.rdx *= s.rcx;
        s.rdx ^= b6;
        uint8_t b7 = (uint8_t)s.mem[s.r15+7];
        s.rdx *= s.rcx;
        s.rdx ^= b7;
        s.r15 += 8;
        s.r8 -= 8;
        if (s.r8 == 0) break;
    }
    if (s.rax != 0) {
        s.r8 = 0;
        for (; s.rax != s.r8; ) {
            uint8_t b = (uint8_t)s.mem[s.r15 + s.r8];
            s.rdx *= s.rcx;
            s.rdx ^= b;
            s.r8 += 1;
            if (s.rax == s.r8) break;
        }
    }
    s.mem_store64(0x12AE1BA0ULL, s.rdx);
#if 0
0xbc8be5f  call 0x73150
#endif
    sub_73150(s, &s.frame[0x330]);
#if 0
0xbc8be6b  call 0xE938D70
#endif
    sub_e938d70(s, (void*)0x12AE1BA8ULL);
    return;
#if 0
0xbc8be75  call 0x75740
#endif
}

} // namespace native
