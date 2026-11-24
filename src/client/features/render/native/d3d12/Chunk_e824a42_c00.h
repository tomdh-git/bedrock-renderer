#pragma once
#include <cstdint>
#include <cstddef>

namespace native {

// Chunk state for sub_e824a42 chunk 0 (0xe824a42..0xe826230).
// Mirrors the job-local frame at rbx produced by sub_e821120's prologue.
// Only the slots this chunk reads/writes are named; the full frame is 0xE238 bytes.
struct ChunkState_e824a42_c00 {
    void* rbx = nullptr;   // job state base (frame at rsp+0x80, rbx==rsp after prologue)
    void* rbp = nullptr;   // frame base (rbp = rsp+0x80 .. actually rbp saved value)
    uint64_t rdi = 0;      // binding index / descriptor pointer at entry
    uint64_t rsi = 0;      // binding record pointer at entry
    uint64_t rax = 0;
    uint64_t rcx = 0;
    uint64_t rdx = 0;
    uint64_t r8 = 0;
    uint64_t r9 = 0;
    uint64_t r10 = 0;
    uint64_t r11 = 0;
    uint64_t r12 = 0;
    uint64_t r13 = 0;
    uint64_t r14 = 0;
    uint64_t r15 = 0;
};

} // namespace native