#pragma once

#include <cstdint>
#include <cstddef>

// LIFT 0xbc8a380 size 0x1afc 1.26.62.01 sub_bc8a380
// CHUNK 0xbc8bb76..0xbc8be7c

// Forward declarations for boundary callees
namespace native {
    namespace boundary {
        void sub_73150(void* rcx);
        void sub_75740(void* rcx, void* rdx);
        void sub_e938d70(void* rcx);
    }
}

struct ChunkState_bc8a380_c01 {
    void* rbp_frame_base;
    void* rsi_scratch;
    void* rdx_scratch;
    void* rax_scratch;
    void* rcx_scratch;
    void* r8_scratch;
    void* r9_scratch;
    void* r15_scratch;
    void* r10_scratch;
};

static inline void sub_bc8a380_chunk_c01(ChunkState_bc8a380_c01& s);