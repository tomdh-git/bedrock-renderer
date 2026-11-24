#pragma once
// LIFT 0xe82326d size 0xa276 1.26.62.01 sub_e82326d
// CHUNK 0xe82c101..0xe82d4be

#include <cstddef>
#include <cstdint>

struct ChunkState_e82326d_c06 {
    void* rbx_base;   // 'this' pointer, base object
    void* rsi_base;   // callee-saved, used as secondary pointer
    void* rdi_base;   // callee-saved, used as secondary pointer
    void* r12_base;   // callee-saved
    void* r13_base;   // callee-saved
    void* r14_base;   // callee-saved
    void* r15_base;   // callee-saved
    void* rbp_base;   // frame pointer
};

static inline void sub_e82326d_chunk_c06(ChunkState_e82326d_c06& s);

// Layout assertions
static_assert(sizeof(void*) == 8, "x64");
static_assert(offsetof(ChunkState_e82326d_c06, rbx_base) == 0x00, "rbx_base at +0x00");
static_assert(offsetof(ChunkState_e82326d_c06, rsi_base) == 0x08, "rsi_base at +0x08");
static_assert(offsetof(ChunkState_e82326d_c06, rdi_base) == 0x10, "rdi_base at +0x10");
static_assert(offsetof(ChunkState_e82326d_c06, r12_base) == 0x18, "r12_base at +0x18");
static_assert(offsetof(ChunkState_e82326d_c06, r13_base) == 0x20, "r13_base at +0x20");
static_assert(offsetof(ChunkState_e82326d_c06, r14_base) == 0x28, "r14_base at +0x28");
static_assert(offsetof(ChunkState_e82326d_c06, r15_base) == 0x30, "r15_base at +0x30");
static_assert(offsetof(ChunkState_e82326d_c06, rbp_base) == 0x38, "rbp_base at +0x38");
static_assert(sizeof(ChunkState_e82326d_c06) == 0x40, "ChunkState_e82326d_c06 size 0x40");