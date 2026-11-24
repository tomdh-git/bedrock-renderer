#pragma once
// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991
// CHUNK 0xe829147..0xe82a912

#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

struct ChunkState_e824991 {
    uint8_t* stack_frame;
    void* rbx;
    void* rbp;
};

static inline void Chunk_e824991_c03(ChunkState_e824991& s);

} // namespace d3d12
} // namespace native
