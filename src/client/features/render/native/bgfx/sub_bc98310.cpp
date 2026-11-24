// LIFT 0xbc98310 size 0x1b2a 1.26.62.01 VV frame-graph builder
// CHUNK 0xbc99adb..0xbc99e3a
#include "sub_bc98310.h"

#if 0
0xbc99adb  movzx r10d,byte ptr [rsi+r8]
0xbc99b52  call 0x73150
0xbc99b5e  call 0xE938D70
0xbc99c01  call 0x73150
0xbc99c0d  call 0xE938D70
0xbc99ca2  mov [0x12AE1E28],rcx
0xbc99cb0  call 0x73150
0xbc99cbc  call 0xE938D70
0xbc99d51  mov [0x12AE1E38],rcx
0xbc99d5f  call 0x73150
0xbc99d6b  call 0xE938D70
0xbc99e0f  mov [0x12AE1E48],rdx
0xbc99e1d  call 0x73150
0xbc99e29  call 0xE938D70
#endif

// 0xbc99adb..0xbc99b16
// hashing loop (FNV-like) over rsi..rdx
// 0xbc99b17..0xbc99b44
// tail hash over remainder
// 0xbc99b44..0xbc99b6a
native::boundary::sub_73150(/*rcx*/); // 0xbc99b52  call 0x73150
native::boundary::sub_e938d70(/*rcx*/); // 0xbc99b5e  call 0xE938D70
// 0xbc99b6f..0xbc99bf3
// 0xbc99bf3..0xbc99c19
native::boundary::sub_73150(/*rcx*/); // 0xbc99c01  call 0x73150
native::boundary::sub_e938d70(/*rcx*/); // 0xbc99c0d  call 0xE938D70
// 0xbc99c1e..0xbc99ca2
// 0xbc99ca2..0xbc99cc8
native::boundary::sub_73150(/*rcx*/); // 0xbc99cb0  call 0x73150
native::boundary::sub_e938d70(/*rcx*/); // 0xbc99cbc  call 0xE938D70
// 0xbc99ccd..0xbc99d51
// 0xbc99d51..0xbc99d77
native::boundary::sub_73150(/*rcx*/); // 0xbc99d5f  call 0x73150
native::boundary::sub_e938d70(/*rcx*/); // 0xbc99d6b  call 0xE938D70
// 0xbc99d7c..0xbc99e0f
// 0xbc99e0f..0xbc99e3a
native::boundary::sub_73150(/*rcx*/); // 0xbc99e1d  call 0x73150
native::boundary::sub_e938d70(/*rcx*/); // 0xbc99e29  call 0xE938D70

namespace native {
static inline void chunk_bc99adb(void* state) {}
}
