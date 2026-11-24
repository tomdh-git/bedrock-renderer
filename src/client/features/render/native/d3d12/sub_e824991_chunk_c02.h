#pragma once
// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991
// CHUNK 0xe827960..0xe829147

#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

// Forward declarations for callees in the lift set
void sub_eea6040(void* rcx, uint32_t edx, void* r8);           // 0xEEA6040 via [0xF99FFA0]
void sub_e820500(void* rcx, void* rdx, uint32_t r8d, void* r9); // 0xE820500
void sub_e82de90(void* rcx, void* rdx, void* r8);               // 0xE82DE90
void sub_e935700(void* rcx);                                    // 0xE935700
void sub_bc6a9d0(void* rcx);                                    // 0xBC6A9D0
void sub_47e8f0(void* rcx);                                     // 0x47E8F0
void sub_e81e1c0(void* rcx, void* rdx);                         // 0xE81E1C0
void sub_eec6ed0(void* rcx, uint32_t r8d, uint32_t edx);        // 0xEEC6ED0 (CRT boundary)

// Layout constants for stack frame offsets (from rbx = aligned frame base)
static constexpr uint32_t kFrameSize = 0xE238;

// rbx-relative offsets used in this chunk
static constexpr uint32_t kOff_C0    = 0xC0;
static constexpr uint32_t kOff_C8    = 0xC8;
static constexpr uint32_t kOff_D0    = 0xD0;
static constexpr uint32_t kOff_D4    = 0xD4;
static constexpr uint32_t kOff_D8    = 0xD8;
static constexpr uint32_t kOff_DC    = 0xDC;
static constexpr uint32_t kOff_E0    = 0xE0;
static constexpr uint32_t kOff_90    = 0x90;
static constexpr uint32_t kOff_A0    = 0xA0;
static constexpr uint32_t kOff_A8    = 0xA8;
static constexpr uint32_t kOff_B0    = 0xB0;
static constexpr uint32_t kOff_B8    = 0xB8;
static constexpr uint32_t kOff_10C   = 0x10C;
static constexpr uint32_t kOff_10E   = 0x10E;
static constexpr uint32_t kOff_110   = 0x110;
static constexpr uint32_t kOff_130   = 0x130;
static constexpr uint32_t kOff_160   = 0x160;
static constexpr uint32_t kOff_168   = 0x168;
static constexpr uint32_t kOff_178   = 0x178;
static constexpr uint32_t kOff_190   = 0x190;
static constexpr uint32_t kOff_1B0   = 0x1B0;
static constexpr uint32_t kOff_1E8   = 0x1E8;
static constexpr uint32_t kOff_220   = 0x220;
static constexpr uint32_t kOff_230   = 0x230;
static constexpr uint32_t kOff_2B0   = 0x2B0;
static constexpr uint32_t kOff_2B4   = 0x2B4;
static constexpr uint32_t kOff_2B8   = 0x2B8;
static constexpr uint32_t kOff_2F0   = 0x2F0;
static constexpr uint32_t kOff_2F8   = 0x2F8;
static constexpr uint32_t kOff_310   = 0x310;
static constexpr uint32_t kOff_340   = 0x340;
static constexpr uint32_t kOff_348   = 0x348;
static constexpr uint32_t kOff_34C   = 0x34C;
static constexpr uint32_t kOff_350   = 0x350;
static constexpr uint32_t kOff_358   = 0x358;
static constexpr uint32_t kOff_360   = 0x360;
static constexpr uint32_t kOff_364   = 0x364;
static constexpr uint32_t kOff_368   = 0x368;
static constexpr uint32_t kOff_388   = 0x388;
static constexpr uint32_t kOff_3A8   = 0x3A8;
static constexpr uint32_t kOff_3B0   = 0x3B0;
static constexpr uint32_t kOff_3C0   = 0x3C0;
static constexpr uint32_t kOff_3D0   = 0x3D0;
static constexpr uint32_t kOff_3E0   = 0x3E0;
static constexpr uint32_t kOff_588   = 0x588;
static constexpr uint32_t kOff_5B0   = 0x5B0;
static constexpr uint32_t kOff_5C8   = 0x5C8;
static constexpr uint32_t kOff_5D8   = 0x5D8;
static constexpr uint32_t kOff_670   = 0x670;
static constexpr uint32_t kOff_690   = 0x690;
static constexpr uint32_t kOff_692   = 0x692;
static constexpr uint32_t kOff_694   = 0x694;
static constexpr uint32_t kOff_696   = 0x696;
static constexpr uint32_t kOff_8A8   = 0x8A8;
static constexpr uint32_t kOff_98    = 0x98;
static constexpr uint32_t kOff_90A0  = 0x90A0;
static constexpr uint32_t kOff_90A8  = 0x90A8;
static constexpr uint32_t kOff_90AC  = 0x90AC;
static constexpr uint32_t kOff_90B0  = 0x90B0;
static constexpr uint32_t kOff_90C0  = 0x90C0;
static constexpr uint32_t kOff_90D0  = 0x90D0;
static constexpr uint32_t kOff_90E0  = 0x90E0;
static constexpr uint32_t kOff_90F0  = 0x90F0;
static constexpr uint32_t kOff_9100  = 0x9100;
static constexpr uint32_t kOff_9110  = 0x9110;
static constexpr uint32_t kOff_9120  = 0x9120;
static constexpr uint32_t kOff_9130  = 0x9130;
static constexpr uint32_t kOff_9140  = 0x9140;
static constexpr uint32_t kOff_9150  = 0x9150;
static constexpr uint32_t kOff_9160  = 0x9160;
static constexpr uint32_t kOff_1C0   = 0x1C0;
static constexpr uint32_t kOff_F0    = 0xF0;
static constexpr uint32_t kOff_110_2 = 0x110;  // reused
static constexpr uint32_t kOff_140   = 0x140;
static constexpr uint32_t kOff_150   = 0x150;
static constexpr uint32_t kOff_180   = 0x180;
static constexpr uint32_t kOff_190_2 = 0x190;  // reused
static constexpr uint32_t kOff_1D0   = 0x1D0;
static constexpr uint32_t kOff_200   = 0x200;
static constexpr uint32_t kOff_E174  = 0xE174;
static constexpr uint32_t kOff_E176  = 0xE176;
static constexpr uint32_t kOff_E178  = 0xE178;

// Data slot addresses
static constexpr uintptr_t kData_F99FFA0   = 0xF99FFA0;    // -> sub_eea6040
static constexpr uintptr_t kData_12BB4910  = 0x12BB4910;
static constexpr uintptr_t kData_F4EE798   = 0xF4EE798;    // jump table
static constexpr uintptr_t kData_F08C710   = 0xF08C710;
static constexpr uintptr_t kData_F4ED2B0   = 0xF4ED2B0;
static constexpr uintptr_t kData_F441630   = 0xF441630;
static constexpr uintptr_t kData_F08ED30   = 0xF08ED30;
static constexpr uintptr_t kData_EF40DE0   = 0xEF40DE0;
static constexpr uintptr_t kData_F441650   = 0xF441650;
static constexpr uintptr_t kData_EFD3400   = 0xEFD3400;

// Jump table cases (from 0xF4EE798)
static constexpr int32_t kJT_Case0  = 0;   // 0xe827f43
static constexpr int32_t kJT_Case1  = 1;   // 0xe827fb8
static constexpr int32_t kJT_Case2  = 2;   // 0xe828149
static constexpr int32_t kJT_Case3  = 3;   // 0xe8281c4
static constexpr int32_t kJT_Case4  = 4;   // 0xe828228
static constexpr int32_t kJT_Case5  = 5;   // 0xe8282ab
static constexpr int32_t kJT_Case6  = 6;   // 0xe828337
static constexpr int32_t kJT_Case7  = 7;   // 0xe82866c
static constexpr int32_t kJT_Case8  = 8;   // 0xe828a0e
static constexpr int32_t kJT_Case9  = 9;   // 0xe828cc0
static constexpr int32_t kJT_Case10 = 10;  // 0xe828d3b
static constexpr int32_t kJT_Case11 = 11;  // 0xe828d9f
static constexpr int32_t kJT_Case12 = 12;  // 0xe828e1a
static constexpr int32_t kJT_Case13 = 13;  // 0xe828fbe

// Chunk state passed to the step function (same live regs as chunk c00/c01)
struct ChunkState_e824991_c02 {
    // Live general-purpose registers at chunk entry
    uint64_t rbx;   // aligned frame base
    uint64_t rbp;   // original frame pointer + 0x80
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rsi;
    uint64_t rdi;

    // Live XMM registers (xmm6-xmm15)
    __m128i xmm6;
    __m128i xmm7;
    __m128i xmm8;
    __m128i xmm9;
    __m128i xmm10;
    __m128i xmm11;
    __m128i xmm12;
    __m128i xmm13;
    __m128i xmm14;
    __m128i xmm15;

    // Stack frame pointer (rbx value, also provides access to [rbx+offset])
    uint8_t* stack_frame;  // == rbx, size kFrameSize
};

// Static assertions for struct layout
static_assert(sizeof(ChunkState_e824991_c02) == 8*8 + 16*10 + 8, "ChunkState_e824991_c02 size mismatch");
static_assert(offsetof(ChunkState_e824991_c02, rbx) == 0);
static_assert(offsetof(ChunkState_e824991_c02, rbp) == 8);
static_assert(offsetof(ChunkState_e824991_c02, r12) == 16);
static_assert(offsetof(ChunkState_e824991_c02, r13) == 24);
static_assert(offsetof(ChunkState_e824991_c02, r14) == 32);
static_assert(offsetof(ChunkState_e824991_c02, r15) == 40);
static_assert(offsetof(ChunkState_e824991_c02, rsi) == 48);
static_assert(offsetof(ChunkState_e824991_c02, rdi) == 56);
static_assert(offsetof(ChunkState_e824991_c02, xmm6) == 64);
static_assert(offsetof(ChunkState_e824991_c02, xmm15) == 208);
static_assert(offsetof(ChunkState_e824991_c02, stack_frame) == 224);

// Chunk entry function (static inline step)
void sub_e824991_chunk_c02(ChunkState_e824991_c02& state);

} // namespace d3d12
} // namespace native