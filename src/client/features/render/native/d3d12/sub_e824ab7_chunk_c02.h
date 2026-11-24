// CHUNK 0xe827ab7..0xe8292b7
#pragma once
#include <cstdint>

namespace native {
namespace d3d12 {

// Chunk c02 of sub_e824ab7 (0xe827ab7..0xe8292b7): live x64 registers at entry,
// plus the frame base pointer rbx (the function's stack frame; all [rbx+off]
// accesses are into it) and rbp.
struct ChunkState_e824ab7_c02 {
    void* rbx;   // [V] frame base; read/written at 0xe827ab7..0xe8292b6
    void* rbp;   // [V] frame pointer (callee-saved; live across the chunk)
    uint64_t rcx; // [V] arg1 at chunk entry (0xe827ab7 mov rax,[rcx])
    uint64_t rsi; // [V] arg2 (0xe827ab7 mov r8,[rsi])
    uint64_t rdi; // [V] arg3 (0xe827ada mov [rbx+0xC8],di)
    uint64_t r9;  // [V] arg4 (0xe827e0a pcmpgtd xmm0,xmm9)
};

} // namespace d3d12
} // namespace native