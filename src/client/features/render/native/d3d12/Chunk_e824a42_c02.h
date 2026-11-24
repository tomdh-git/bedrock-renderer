#pragma once
// LIFT 0xe824a42 size 0x8aa1 1.26.62.01 sub_e824a42
// CHUNK 0xe827a1a..0xe829207

#include <cstdint>
#include <emmintrin.h>

namespace native {

// Chunk state for 0xe827a1a..0xe829207 (job frame at rbx).
// Offsets are relative to the job state base rbx; documented in docs/functions/e824a42.md.
struct ChunkState_e824a42_c02 {
    // [rbx+0xA0] frame context pointer (ctx)
    void* ctx_a0;
    // [rbx+0x90] renderer context
    void* r90;
    // [rbx+0x220] descriptor handle array base (tables vector)
    void* tables_base_220;
    // [rbx+0x230] tables size
    uint64_t tables_size_230;
    // [rbx+0x388] / [rbx+0x310] frame state fields
    void* field_388;
    void* field_310;
    // [rbx+0x130] uniform state array
    void* uniform_state_130;
    // [rbx+0xA8] vertex buffer record
    void* vtx_rec_a8;
    // [rbx+0x98] allocation base pointer
    void* alloc_base_98;
    // [rbx+0x1B0] binding table
    void* binding_table_1b0;
    // [rbx+0x1E8] stage index
    uint32_t stage_idx_1e8;
    // [rbx+0x2F0] matrix base
    void* matrix_base_2f0;
    // [rbx+0x5B0] matrix base 2
    void* matrix_base_5b0;
    // [rbx+0x90A0] matrix base 3
    void* matrix_base_90a0;
    // [rbx+0x90A8] vector components
    uint32_t vec_90a8;
    // [rbx+0x90AC] divisor
    uint32_t divisor_90ac;
    // [rbx+0x10C] last sampler index
    uint16_t last_sampler_10c;
    // [rbx+0x160] flags
    uint16_t flags_160;
    // [rbx+0x190] last flags
    uint16_t last_flags_190;
    // [rbx+0x168] slot 58 base
    void* slot58_168;
    // [rbx+0x3B0] 0x60-byte output block (SRV state)
    float out_block_3b0[0x18];
    // [rbx+0xC0] descriptor write record
    uint64_t desc_rec_c0;
    uint32_t desc_rec_c4;
    uint64_t desc_rec_c8;
    uint32_t desc_rec_cc;
    uint32_t desc_rec_d0;
    uint32_t desc_rec_d4;
    uint32_t desc_rec_d8;
    uint32_t desc_rec_dc;
    uint32_t desc_rec_e0;
    // [rbx+0x670] buffer transition record
    uint64_t buf_trans_670;
    // [rbx+0x260] constant commit record
    uint32_t const_rec_260[0x28];
    // [rbx+0x340] uniform buffer 1
    void* ubuf1_340;
    uint32_t ubuf1_size_348;
    uint32_t ubuf1_off_34c;
    uint8_t ubuf1_valid_350;
    // [rbx+0x358] uniform buffer 2
    void* ubuf2_358;
    uint32_t ubuf2_size_360;
    uint32_t ubuf2_off_364;
    uint8_t ubuf2_valid_368;
    // [rbx+0x2B0] counts
    uint32_t count_2b0;
    uint32_t count_2b4;
    // [rbx+0x2B8] packed counts
    uint64_t counts_packed_2b8;
    // [rbx+0x690] LRU cursor
    uint16_t lru_cur_690;
    // [rbx+0x692] LRU head
    uint16_t lru_head_692;
    // [rbx+0xE174] cached stage 1
    uint16_t cached_stage_e174;
    // [rbx+0xE176] cached stage 2
    uint16_t cached_stage_e176;
    // [rbx+0xE178] cached stage 3
    uint16_t cached_stage_e178;
    // [rbx+0x90B0..0x90E0] tangent basis rows
    float basis_90b0[0x10];
    // [rbx+0x90F0..0x9120] tangent basis rows 2
    float basis_90f0[0x10];
    // [rbx+0x9130..0x9160] tangent basis rows 3
    float basis_9130[0x10];

    static inline ChunkState_e824a42_c02& from_frame(void* frame_base) {
        return *reinterpret_cast<ChunkState_e824a42_c02*>(frame_base);
    }
};

void chunk_e824a42_c02(void* state);

} // namespace native