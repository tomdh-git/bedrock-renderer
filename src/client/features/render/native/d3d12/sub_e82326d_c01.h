#pragma once
// LIFT 0xe82326d size 0xa276 1.26.62.01 sub_e82326d
// CHUNK 0xe824a6a..0xe826261
#include <cstdint>

namespace native::d3d12 {

// Chunk state for sub_e82326d chunk c01 (0xe824a6a..0xe826261).
// Live x64 registers at chunk entry/exit, carried in this struct.
struct ChunkState_e82326d_c01 {
    void* rbx;    // base object pointer (this)
    void* rdi;    // arg2 pointer
    void* rsi;    // arg1 pointer / loop cursor
    void* r14;
    void* r15;
    void* r12;
    void* r13;
    void* r9;
    void* r10;
    void* r11;
    std::uint32_t eax;
    std::uint32_t ecx;
    std::uint32_t edx;
    std::uint32_t r8d;
};

static inline void sub_e82326d_chunk_c01(ChunkState_e82326d_c01& s);

} // namespace native::d3d12