#pragma once
// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991
// CHUNK 0xe829147..0xe82a912

#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

// Forward declarations for callees in the lift set
void sub_47e8f0(void* rcx);                                          // 0x47e8f0
void sub_eec6ed0(void* rcx, void* rdx);                              // 0xeec6ed0
void sub_eec6ec0(void* rcx);                                         // 0xeec6ec0
void sub_e8360f0(void* rcx, void* rdx);                              // 0xe8360f0
void sub_bc6a9d0(void* rcx);                                         // 0xbc6a9d0
void sub_e81e1c0(void* rcx, void* rdx);                              // 0xe81e1c0
void sub_eea6040(void* rcx, void* rdx, void* r8, void* r9);          // 0xeea6040 (via [0xF99FFA0])

struct ChunkState_e824991 {
    // Live general-purpose registers at chunk entry
    uint64_t rbx;
    uint64_t rbp;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rsi;
    uint64_t rdi;

    // Live XMM registers (xmm6-xmm15)
    __m128i xmm6;
    __m128i xmm7;
    __m128i xmm8;
    __m128i xmm9;
    __m128i xmm10;
    __m128i xmm11;
    __m128i xmm12;
    __m128i xmm13;
    __m128i xmm14;
    __m128i xmm15;

    // Stack frame pointer
    uint8_t* stack_frame;
};

static inline void Chunk_e824991_c03(ChunkState_e824991& s);

} // namespace d3d12
} // namespace native