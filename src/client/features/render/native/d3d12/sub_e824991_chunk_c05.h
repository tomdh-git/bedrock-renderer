#pragma once
// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991
// CHUNK 0xe82c101..0xe82d4dd

#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

static constexpr uint32_t kFrameSize = 0xE238;

struct ChunkState_e824991_c05 {
    uint64_t rbx;
    uint64_t rbp;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rsi;
    uint64_t rdi;
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
    uint8_t* stack_frame;
};

static_assert(sizeof(ChunkState_e824991_c05) == 8*8 + 16*10 + 8, "ChunkState_e824991_c05 size mismatch");
static_assert(offsetof(ChunkState_e824991_c05, rbx) == 0);
static_assert(offsetof(ChunkState_e824991_c05, stack_frame) == 224);

void sub_e824991_chunk_c05(ChunkState_e824991_c05& state);

} // namespace d3d12
} // namespace native