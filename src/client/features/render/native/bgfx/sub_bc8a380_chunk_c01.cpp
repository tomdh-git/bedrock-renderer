// LIFT 0xbc8a380 size 0x1afc 1.26.62.01 sub_bc8a380
// CHUNK 0xbc8bb76..0xbc8be7c

// chunk state documented in docs/functions/bc8a380.md section 'Chunk state'
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

static inline void sub_bc8a380_chunk_c01(ChunkState_bc8a380_c01& s) {
    // 0xbc8bb76..0xbc8be7c
    (void)s;
}

#if 0
0xbc8bb84  call 0x75740
0xbc8bc58  call 0x73150
0xbc8bc64  call 0xE938D70
0xbc8bd00  call 0x73150
0xbc8bd0c  call 0xE938D70
0xbc8bda8  call 0x73150
0xbc8bdb4  call 0xE938D70
0xbc8be5f  call 0x73150
0xbc8be6b  call 0xE938D70
0xbc8be75  call 0x75740
#endif