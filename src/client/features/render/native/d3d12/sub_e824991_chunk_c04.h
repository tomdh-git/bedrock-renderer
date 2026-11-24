#pragma once
// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991
// CHUNK 0xe82a912..0xe82c101

#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

void sub_47e8f0(void* rcx);                                          // 0x47e8f0
void sub_eec6ed0(void* rcx, uint32_t r8d, uint32_t edx);        // 0xEEC6ED0 (CRT boundary)
void sub_eec6ec0(void* rcx, uint32_t r8d, uint32_t edx);        // 0xEEC6EC0 (CRT boundary)

static constexpr uint32_t kFrameSize = 0xE238;

struct ChunkState_e824991_c04 {
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

static_assert(sizeof(ChunkState_e824991_c04) == 8*8 + 16*10 + 8, "ChunkState_e824991_c04 size mismatch");
static_assert(offsetof(ChunkState_e824991_c04, rbx) == 0);
static_assert(offsetof(ChunkState_e824991_c04, rbp) == 8);
static_assert(offsetof(ChunkState_e824991_c04, r12) == 16);
static_assert(offsetof(ChunkState_e824991_c04, r13) == 24);
static_assert(offsetof(ChunkState_e824991_c04, r14) == 32);
static_assert(offsetof(ChunkState_e824991_c04, r15) == 40);
static_assert(offsetof(ChunkState_e824991_c04, rsi) == 48);
static_assert(offsetof(ChunkState_e824991_c04, rdi) == 56);
static_assert(offsetof(ChunkState_e824991_c04, xmm6) == 64);
static_assert(offsetof(ChunkState_e824991_c04, xmm15) == 208);
static_assert(offsetof(ChunkState_e824991_c04, stack_frame) == 224);

void sub_e824991_chunk_c04(ChunkState_e824991_c04& state);

} // namespace d3d12
} // namespace native