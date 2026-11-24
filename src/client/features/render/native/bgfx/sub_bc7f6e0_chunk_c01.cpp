// LIFT 0xbc7f6e0 size 0x1a82 1.26.62.01 VV frame-graph builder
// CHUNK 0xbc80ed3..0xbc81162

#include "client/features/render/native/bgfx/sub_bc7f6e0_chunk_c01.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

// Forward declarations for lift-set callees (tail functions)
extern "C" void sub_bc7f920(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bc7f945(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bc7f96a(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bc7f98f(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);

// Boundary callees (not in lift set)
namespace boundary {
void sub_73150(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_e938d70(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
} // namespace boundary

// Verbatim call quotes for liftcheck verification
#if 0
0xbc80f4a  call 0x73150
0xbc80f56  call 0xE938D70
0xbc80ff9  call 0x73150
0xbc80ffe  call 0xE938D70
0xbc810a8  call 0x73150
0xbc810b4  call 0xE938D70
0xbc81145  call 0x73150
0xbc81151  call 0xE938D70
#endif

static inline void sub_bc7f6e0_chunk_c01(ChunkState_bc7f6e0_c01& s) {
    // 0xbc80ed3..0xbc81162: FNV-1a hash computation (4 variants)

    // Map state to local variables matching the disassembly register allocation
    uintptr_t rsi = s.rsi;  // buffer pointer
    uintptr_t rdx = s.rdx;  // buffer length (bytes)
    uintptr_t rax = s.rax;  // remaining count for tail loop
    uintptr_t rcx = s.rcx;  // running FNV hash accumulator (input)
    uintptr_t r8  = s.r8;   // current index (input)
    uintptr_t r9  = s.r9;   // FNV prime (input)
    uintptr_t rdi = s.rdi;  // [rbp+0x308] saved context pointer

    // Variant 1: 0xbc80ed3..0xbc80f62
    // 0xbc80ed3..0xbc80f0d: main 4-byte FNV-1a loop
    while (r8 < rdx) {
        uintptr_t r10 = *(uint8_t*)(rsi + r8); r10 ^= rcx; r10 *= r9;
        rcx = *(uint8_t*)(rsi + r8 + 1); rcx ^= r10; rcx *= r9;
        r10 = *(uint8_t*)(rsi + r8 + 2); r10 ^= rcx; r10 *= r9;
        rcx = *(uint8_t*)(rsi + r8 + 3); rcx ^= r10; rcx *= r9;
        r8 += 4;
    }
    // 0xbc80f0f..0xbc80f12: test rax,rax; je 0xBC80F3C
    if (rax != 0) {
        // 0xbc80f14..0xbc80f3a: tail byte loop
        rsi += r8;
        rdx = 0;
        r8 = kFnvPrime;   // 0x100000001B3
        r9 = rcx;
        while (rdx < rax) {
            rcx = *(uint8_t*)(rsi + rdx); rcx ^= r9; rcx *= r8; rdx++; r9 = rcx;
        }
    }
    // 0xbc80f3c: mov [0x12AE1868],rcx
    *reinterpret_cast<uintptr_t*>(kDataSlot_12AE1868) = rcx;
    // 0xbc80f43..0xbc80f4a: lea rcx,[rbp+0x90]; call 0x73150
    boundary::sub_73150(s.rbp + 0x90, 0, 0, 0);
    // 0xbc80f4f..0xbc80f56: lea rcx,[0x12AE1870]; call 0xE938D70
    boundary::sub_e938d70(kDataSlot_12AE1870, 0, 0, 0);
    // 0xbc80f5b..0xbc80f62: mov rdi,[rbp+0x308]; jmp 0xBC7F920
    rdi = *reinterpret_cast<uintptr_t*>(s.rbp + 0x308);
    sub_bc7f920(rcx, rdx, r8, r9);  // tail call, does not return

    // Variant 2: 0xbc80f67..0xbc81010
    // 0xbc80f67..0xbc80fbc: main 4-byte loop (rdx masked to 4-byte boundary)
    rdx &= ~3ULL;
    rcx = kFnvOffset;   // 0xCBF29CE484222325
    r8 = 0;
    r9 = kFnvPrime;
    while (r8 < rdx) {
        uintptr_t r10 = *(uint8_t*)(rsi + r8); r10 ^= rcx; r10 *= r9;
        rcx = *(uint8_t*)(rsi + r8 + 1); rcx ^= r10; rcx *= r9;
        r10 = *(uint8_t*)(rsi + r8 + 2); r10 ^= rcx; r10 *= r9;
        rcx = *(uint8_t*)(rsi + r8 + 3); rcx ^= r10; rcx *= r9;
        r8 += 4;
    }
    // 0xbc80fbe..0xbc80fc1: test rax,rax; je 0xBC80FEB
    if (rax != 0) {
        // 0xbc80fc3..0xbc80fe9: tail byte loop
        rsi += r8;
        rdx = 0;
        r8 = kFnvPrime;
        r9 = rcx;
        while (rdx < rax) {
            rcx = *(uint8_t*)(rsi + rdx); rcx ^= r9; rcx *= r8; rdx++; r9 = rcx;
        }
    }
    // 0xbc80feb: mov [0x12AE1878],rcx
    *reinterpret_cast<uintptr_t*>(kDataSlot_12AE1878) = rcx;
    // 0xbc80ff2..0xbc80ff9: lea rcx,[rbp+0x90]; call 0x73150
    boundary::sub_73150(s.rbp + 0x90, 0, 0, 0);
    // 0xbc80ffe..0xbc81005: lea rcx,[0x12AE1880]; call 0xE938D70
    boundary::sub_e938d70(kDataSlot_12AE1880, 0, 0, 0);
    // 0xbc8100a..0xbc81011: mov rdi,[rbp+0x308]; jmp 0xBC7F945
    rdi = *reinterpret_cast<uintptr_t*>(s.rbp + 0x308);
    sub_bc7f945(rcx, rdx, r8, r9);

    // Variant 3: 0xbc81016..0xbc810bf
    // 0xbc81016..0xbc8106b: main 4-byte loop
    rdx &= ~3ULL;
    rcx = kFnvOffset;
    r8 = 0;
    r9 = kFnvPrime;
    while (r8 < rdx) {
        uintptr_t r10 = *(uint8_t*)(rsi + r8); r10 ^= rcx; r10 *= r9;
        rcx = *(uint8_t*)(rsi + r8 + 1); rcx ^= r10; rcx *= r9;
        r10 = *(uint8_t*)(rsi + r8 + 2); r10 ^= rcx; r10 *= r9;
        rcx = *(uint8_t*)(rsi + r8 + 3); rcx ^= r10; rcx *= r9;
        r8 += 4;
    }
    // 0xbc8106d..0xbc81070: test rax,rax; je 0xBC8109A
    if (rax != 0) {
        // 0xbc81072..0xbc81098: tail byte loop
        rsi += r8;
        rdx = 0;
        r8 = kFnvPrime;
        r9 = rcx;
        while (rdx < rax) {
            rcx = *(uint8_t*)(rsi + rdx); rcx ^= r9; rcx *= r8; rdx++; r9 = rcx;
        }
    }
    // 0xbc8109a: mov [0x12AE1888],rcx
    *reinterpret_cast<uintptr_t*>(kDataSlot_12AE1888) = rcx;
    // 0xbc810a1..0xbc810a8: lea rcx,[rbp+0x90]; call 0x73150
    boundary::sub_73150(s.rbp + 0x90, 0, 0, 0);
    // 0xbc810ad..0xbc810b4: lea rcx,[0x12AE1890]; call 0xE938D70
    boundary::sub_e938d70(kDataSlot_12AE1890, 0, 0, 0);
    // 0xbc810b9..0xbc810c0: mov rdi,[rbp+0x308]; jmp 0xBC7F96A
    rdi = *reinterpret_cast<uintptr_t*>(s.rbp + 0x308);
    sub_bc7f96a(rcx, rdx, r8, r9);

    // Variant 4: 0xbc810c5..0xbc8115d
    // 0xbc810c5..0xbc81110: main 4-byte loop (registers swapped: r8=len, r9=hash, rcx=prime)
    r8 &= ~3ULL;
    rdx = kFnvOffset;
    r9 = 0;
    while (r9 < r8) {
        uintptr_t r10 = *(uint8_t*)(rsi + r9); r10 ^= rdx; r10 *= rcx;
        rdx = *(uint8_t*)(rsi + r9 + 1); rdx ^= r10; rdx *= rcx;
        r10 = *(uint8_t*)(rsi + r9 + 2); r10 ^= rdx; r10 *= rcx;
        rdx = *(uint8_t*)(rsi + r9 + 3); rdx ^= r10; rdx *= rcx;
        r9 += 4;
    }
    // 0xbc81112..0xbc81115: test rax,rax; je 0xBC81137
    if (rax != 0) {
        // 0xbc81117..0xbc81135: tail byte loop
        rsi += r9;
        r8 = 0;
        r9 = rdx;
        while (r8 < rax) {
            rdx = *(uint8_t*)(rsi + r8); rdx ^= r9; rdx *= rcx; r8++; r9 = rdx;
        }
    }
    // 0xbc81137: mov [0x12AE1898],rdx
    *reinterpret_cast<uintptr_t*>(kDataSlot_12AE1898) = rdx;
    // 0xbc8113e..0xbc81145: lea rcx,[rbp+0x90]; call 0x73150
    boundary::sub_73150(s.rbp + 0x90, 0, 0, 0);
    // 0xbc8114a..0xbc81151: lea rcx,[0x12AE18A0]; call 0xE938D70
    boundary::sub_e938d70(kDataSlot_12AE18A0, 0, 0, 0);
    // 0xbc81156..0xbc8115d: mov rdi,[rbp+0x308]; jmp 0xBC7F98F
    rdi = *reinterpret_cast<uintptr_t*>(s.rbp + 0x308);
    sub_bc7f98f(rcx, rdx, r8, r9);
}

} // namespace native::bgfx