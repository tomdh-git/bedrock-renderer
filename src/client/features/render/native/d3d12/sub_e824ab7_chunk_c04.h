// CHUNK 0xe82aaab..0xe82c2ab
#pragma once
#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

// Chunk c04 of sub_e824ab7 (0xe82aaab..0xe82c2ab): live x64 registers at entry,
// plus the frame base pointer rbx (the function's stack frame; all [rbx+off]
// accesses are into it) and rbp.
struct ChunkState_e824ab7_c04 {
    void* rbx;          // [V] frame base; read/written throughout chunk
    void* rbp;          // [V] frame pointer (callee-saved; live across the chunk)
    uint64_t r14;       // [V] base pointer for loop data structure (indexed by r15)
    uint64_t r15;       // [V] loop index (0..r14-1)
    uint64_t r13;       // [V] pointer used in bounds checks
    uint64_t r12;       // [V] temporary / stride value
    __m128 xmm0;        // [V] SIMD working register
    __m128 xmm1;        // [V] SIMD working register
    __m128 xmm2;        // [V] SIMD working register
    __m128 xmm3;        // [V] SIMD working register
    __m128 xmm4;        // [V] SIMD working register
    __m128 xmm5;        // [V] SIMD working register
    __m128 xmm6;        // [V] SIMD working register
    __m128 xmm7;        // [V] SIMD working register
    __m128 xmm8;        // [V] SIMD working register
    __m128 xmm9;        // [V] SIMD working register / zero constant
    __m128 xmm10;       // [V] SIMD working register
    __m128 xmm11;       // [V] SIMD working register
    __m128 xmm12;       // [V] SIMD working register
    __m128 xmm13;       // [V] SIMD working register
    __m128 xmm14;       // [V] SIMD working register
    __m128 xmm15;       // [V] SIMD working register
};

// Layout constants for [rbx+off] accesses in this chunk
static constexpr uint32_t kOff_130  = 0x130;
static constexpr uint32_t kOff_140  = 0x140;
static constexpr uint32_t kOff_150  = 0x150;
static constexpr uint32_t kOff_180  = 0x180;
static constexpr uint32_t kOff_190  = 0x190;
static constexpr uint32_t kOff_1B0  = 0x1B0;
static constexpr uint32_t kOff_1C0  = 0x1C0;
static constexpr uint32_t kOff_200  = 0x200;
static constexpr uint32_t kOff_240  = 0x240;
static constexpr uint32_t kOff_268  = 0x268;
static constexpr uint32_t kOff_26C  = 0x26C;
static constexpr uint32_t kOff_270  = 0x270;
static constexpr uint32_t kOff_290  = 0x290;
static constexpr uint32_t kOff_298  = 0x298;
static constexpr uint32_t kOff_2A8  = 0x2A8;
static constexpr uint32_t kOff_2B0  = 0x2B0;
static constexpr uint32_t kOff_2B4  = 0x2B4;
static constexpr uint32_t kOff_2B8  = 0x2B8;
static constexpr uint32_t kOff_2BC  = 0x2BC;
static constexpr uint32_t kOff_2F0  = 0x2F0;
static constexpr uint32_t kOff_2F8  = 0x2F8;
static constexpr uint32_t kOff_300  = 0x300;
static constexpr uint32_t kOff_3B0  = 0x3B0;
static constexpr uint32_t kOff_3B8  = 0x3B8;
static constexpr uint32_t kOff_3C0  = 0x3C0;
static constexpr uint32_t kOff_3C8  = 0x3C8;
static constexpr uint32_t kOff_3D0  = 0x3D0;
static constexpr uint32_t kOff_3E0  = 0x3E0;
static constexpr uint32_t kOff_578  = 0x578;
static constexpr uint32_t kOff_5B0  = 0x5B0;
static constexpr uint32_t kOff_5B8  = 0x5B8;
static constexpr uint32_t kOff_5C0  = 0x5C0;
static constexpr uint32_t kOff_5C8  = 0x5C8;
static constexpr uint32_t kOff_98   = 0x98;
static constexpr uint32_t kOff_A0   = 0xA0;
static constexpr uint32_t kOff_A8   = 0xA8;
static constexpr uint32_t kOff_C0   = 0xC0;
static constexpr uint32_t kOff_C8   = 0xC8;
static constexpr uint32_t kOff_D0   = 0xD0;
static constexpr uint32_t kOff_E176 = 0xE176;
static constexpr uint32_t kOff_E178 = 0xE178;
static constexpr uint32_t kOff_F0   = 0xF0;
static constexpr uint32_t kOff_10E  = 0x10E;
static constexpr uint32_t kOff_110  = 0x110;
static constexpr uint32_t kOff_150  = 0x150;
static constexpr uint32_t kOff_170  = 0x170;
static constexpr uint32_t kOff_1D0  = 0x1D0;
static constexpr uint32_t kOff_1F0  = 0x1F0;
static constexpr uint32_t kOff_390  = 0x390;
static constexpr uint32_t kOff_610  = 0x610;
static constexpr uint32_t kOff_90A0 = 0x90A0;
static constexpr uint32_t kOff_90B0 = 0x90B0;
static constexpr uint32_t kOff_90C0 = 0x90C0;
static constexpr uint32_t kOff_90D0 = 0x90D0;
static constexpr uint32_t kOff_90E0 = 0x90E0;
static constexpr uint32_t kOff_90F0 = 0x90F0;
static constexpr uint32_t kOff_9100 = 0x9100;
static constexpr uint32_t kOff_9110 = 0x9110;
static constexpr uint32_t kOff_9120 = 0x9120;
static constexpr uint32_t kOff_9130 = 0x9130;
static constexpr uint32_t kOff_9140 = 0x9140;
static constexpr uint32_t kOff_9150 = 0x9150;
static constexpr uint32_t kOff_9160 = 0x9160;
static constexpr uint32_t kOff_D170 = 0xD170;

// Data constants referenced in this chunk
extern const __m128 kData_F441630;  // 0xF441630
extern const __m128 kData_F08ED30;  // 0xF08ED30
extern const __m128 kData_EF40DE0;  // 0xEF40DE0
extern const __m128 kData_F441650;  // 0xF441650
extern const __m128 kData_EFD3400;  // 0xEFD3400
extern const float  kData_EF40D58;  // 0xEF40D58

// Boundary function declarations
extern "C" void* boundary_stl_vector_grow(void* rcx, void* r8);  // 0x47E8F0
extern "C" void* boundary_crt_memcpy(void* rsi, void* rcx, size_t rdx);  // 0xEEC6ED0
extern "C" void* boundary_crt_memcpy_ec0(void* rsi, void* rcx, size_t rdx);  // 0xEEC6EC0
extern "C" void  boundary_e8360f0(void* rcx, void* rdx, uint32_t r8d, uint32_t r9d);  // 0xE8360F0
extern "C" void* boundary_vendor_alloc(void* rcx);  // [0xF99FFA0]

// Forward declarations for lifted callees (if any in this chunk)
// None in this chunk - all calls are to boundary functions

// Step function for chunk c04
void step_e824ab7_c04(ChunkState_e824ab7_c04& state);

} // namespace d3d12
} // namespace native