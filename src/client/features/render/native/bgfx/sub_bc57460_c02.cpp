// LIFT 0xbc57460 size 0x2e2f 1.26.62.01 sub_bc57460
// CHUNK 0xbc5a261..0xbc5a28f

// chunk state documented in docs/functions/bc57460.md section 'Chunk state'
struct ChunkState_bc57460_c02 {
    void* rbp_frame_base;
    void* rdx_value;
    void* r12_ctx;
    void* r13_scratch;
};

static inline void sub_bc57460_chunk02(ChunkState_bc57460_c02& s) {
    // 0xbc5a261..0xbc5a28f
    (void)s;
    // 0xbc5a261  mov [0x12ADF778],rdx
    // 0xbc5a268  lea rcx,[rbp+0x410]
    // 0xbc5a26f  call 0x73150
    // 0xbc5a274  lea rcx,[0x12ADF780]
    // 0xbc5a27b  call 0xE938D70
    // 0xbc5a280  mov r12,r13
    // 0xbc5a283  jmp 0xBC576FF
    // 0xbc5a288  call 0x75740
    // 0xbc5a28d  nop
    // 0xbc5a28e  int3
    // 0xbc5a28f  nop
}

#if 0
0xbc5a261  mov [0x12ADF778],rdx
0xbc5a268  lea rcx,[rbp+0x410]
0xbc5a26f  call 0x73150
0xbc5a274  lea rcx,[0x12ADF780]
0xbc5a27b  call 0xE938D70
0xbc5a280  mov r12,r13
0xbc5a283  jmp 0xBC576FF
0xbc5a288  call 0x75740
0xbc5a28d  nop
0xbc5a28e  int3
0xbc5a28f  nop
#endif