// CHUNK 0xe8292b7..0xe82aaab
#pragma once
#include <cstdint>

namespace native {
namespace d3d12 {

// Chunk c03 of sub_e824ab7 (0xe8292b7..0xe82aaab): live x64 registers at entry,
// plus the frame base pointer rbx (the function's stack frame; all [rbx+off]
// accesses are into it) and rbp.
struct ChunkState_e824ab7_c03 {
    void* rbx;   // [V] frame base; read/written at 0xe8292b7..0xe82aaaa
    void* rbp;   // [V] frame pointer (callee-saved; live across the chunk)
    uint64_t r13; // [V] holds [rbx+0xA8] at chunk entry
    uint64_t r14; // [V] array pointer (r14 from c02)
    uint64_t r15; // [V] loop counter (r15 from c02)
    uint64_t rsi; // [V] index register
    uint64_t rdi; // [V] general purpose
    uint64_t rcx; // [V] arg1 for calls
    uint64_t rdx; // [V] arg2 for calls
    uint64_t r8;  // [V] arg3 for calls
    uint64_t r9;  // [V] arg4 for calls
    // xmm registers: xmm0-xmm15 are caller-saved; xmm9 used as zero vector constant
};

} // namespace d3d12
} // namespace native