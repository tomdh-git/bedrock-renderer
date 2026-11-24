// LIFT 0xbc82ad0 size 0x3a0f 1.26.62.01 sub_bc82ad0
// CHUNK 0xbc864bb..0xbc864df

#include "sub_bc82ad0_chunk_c03.h"

static inline void sub_bc82ad0_chunk_c03(ChunkState_bc82ad0_c03& s) {
    uint8_t* rbp = s.rbp;

    // 0xbc864bb..0xbc864df
    // 0xbc864bb  mov [0x12AE1AC0],rdx
    *reinterpret_cast<uint64_t*>(0x12AE1AC0) = s.rdx;

    // 0xbc864c2  lea rcx,[rbp+0x770]
    // 0xbc864c9  call 0x73150
    native::boundary::sub_73150(rbp + 0x770);

    // 0xbc864ce  lea rcx,[0x12AE1AC8]
    // 0xbc864d5  call 0xE938D70
    native::boundary::sub_e938d70(reinterpret_cast<void*>(0x12AE1AC8));

    // 0xbc864da  jmp 0xBC83AEE
    // 0xbc864df  nop
    // Tail jump to sub_bc83aee (chunk c00 entry point 0xbc83aee)
    native::sub_bc83aee(s.rbp);

    // unreachable - the jmp transfers control
    __builtin_unreachable();
}

#if 0
0xbc864bb  mov [0x12AE1AC0],rdx
0xbc864c2  lea rcx,[rbp+0x770]
0xbc864c9  call 0x73150
0xbc864ce  lea rcx,[0x12AE1AC8]
0xbc864d5  call 0xE938D70
0xbc864da  jmp 0xBC83AEE
0xbc864df  nop
#endif