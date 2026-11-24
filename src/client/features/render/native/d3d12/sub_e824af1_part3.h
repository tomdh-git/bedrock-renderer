// LIFT 0xe824af1 size 0x89f2 1.26.62.01 sub_e824af1
// CHUNK 0xe827a40..0xe829235

#pragma once

#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

// Stack frame offsets relative to rbx (frame base)
constexpr std::uintptr_t kFrameSize = 0xE238;

// Stack slots (relative to rbx)
constexpr std::ptrdiff_t kSlot_JobContext        = 0xA0;   // 8 bytes - saved rcx (parent a0)
constexpr std::ptrdiff_t kSlot_SavedR8           = 0x168;  // 8 bytes - saved r8 (parent a2)
constexpr std::ptrdiff_t kSlot_SavedR9           = 0x3A8;  // 8 bytes - saved r9 (parent a3)
constexpr std::ptrdiff_t kSlot_LoopIndex         = 0xF0;   // 4 bytes - loop index / counter
constexpr std::ptrdiff_t kSlot_LoopLimit         = 0x150;  // 4 bytes - loop limit / bound
constexpr std::ptrdiff_t kSlot_ItemArrayBase     = 0x1C0;  // 8 bytes - pointer to item array base
constexpr std::ptrdiff_t kSlot_SecondPtrLimit    = 0x110;  // 8 bytes - second pointer / limit
constexpr std::ptrdiff_t kSlot_OutputBuffer      = 0xB8;   // 8 bytes - pointer to output buffer
constexpr std::ptrdiff_t kSlot_OutputIndexArray  = 0x2C0;  // 8 bytes - pointer to output index array
constexpr std::ptrdiff_t kSlot_PerItemStructsBase = 0x3A0; // 8 bytes - base for per-item structs
constexpr std::ptrdiff_t kSlot_ResourceTable     = 0x90;   // 8 bytes - pointer to resource table
constexpr std::ptrdiff_t kSlot_SimdConstantTableBase = 0x90A0; // 8 bytes - SIMD constant table base
constexpr std::ptrdiff_t kSlot_SavedWord         = 0xE174; // 2 bytes - saved word
constexpr std::ptrdiff_t kSlot_LoadedWordFromItem = 0x5F0; // 2 bytes - loaded word from item
constexpr std::ptrdiff_t kSlot_Const_Neg100000000 = 0x4C0; // 8 bytes - constant -0x100000000
constexpr std::ptrdiff_t kSlot_XmmScratch0       = 0x4E0;  // 16 bytes - zeroed XMM scratch
constexpr std::ptrdiff_t kSlot_XmmScratch1       = 0x4F0;  // 16 bytes - zeroed XMM scratch
constexpr std::ptrdiff_t kSlot_CopiedFromDataEfc6ae0 = 0x504; // 16 bytes - copied from data_efc6ae0
constexpr std::ptrdiff_t kSlot_InitializedTo1    = 0x514;  // 4 bytes - initialized to 1
constexpr std::ptrdiff_t kSlot_Const_1FFFF00000000 = 0x518; // 8 bytes - constant 0x1FFFF00000000
constexpr std::ptrdiff_t kSlot_Const_FFFF        = 0x520;  // 2 bytes - constant 0xFFFF
constexpr std::ptrdiff_t kSlot_Zeroed1           = 0x522;  // 1 byte - zeroed
constexpr std::ptrdiff_t kSlot_Const_FF00        = 0x523;  // 2 bytes - constant 0xFF00
constexpr std::ptrdiff_t kSlot_Const_7FFFFFFF    = 0x528;  // 4 bytes - constant 0x7FFFFFFF
constexpr std::ptrdiff_t kSlot_Zeroed2           = 0x52C;  // 8 bytes - zeroed
constexpr std::ptrdiff_t kSlot_Const_Neg1        = 0x534;  // 8 bytes - constant -1
constexpr std::ptrdiff_t kSlot_BufferStart       = 0x678;  // 8 bytes - pointer to buffer start
constexpr std::ptrdiff_t kSlot_BufferEnd         = 0x680;  // 8 bytes - pointer to buffer end
constexpr std::ptrdiff_t kSlot_SavedPointer      = 0x688;  // 8 bytes - saved pointer
constexpr std::ptrdiff_t kSlot_Const_FFFFFFFF_3F003E = 0x690; // 4 bytes - 0xFFFFFFFF / 0x3F003E
constexpr std::ptrdiff_t kSlot_SimdConstants     = 0x794;  // 16*7 bytes - copied constants from data_f441720..data_f441790
constexpr std::ptrdiff_t kSlot_Const_3F003E      = 0x814;  // 4 bytes - constant 0x3F003E
constexpr std::ptrdiff_t kSlot_ComputedPerItemAddr = 0x90A8; // 8 bytes - computed per-item address
constexpr std::ptrdiff_t kSlot_ShadowSpace8      = 0x20;   // 8 bytes - zeroed (shadow space for vcall)
constexpr std::ptrdiff_t kSlot_ShadowSpace4      = 0x28;   // 4 bytes - zeroed (shadow space for vcall)

// Additional slots used in this chunk
constexpr std::ptrdiff_t kSlot_10C               = 0x10C;  // 2 bytes - saved di
constexpr std::ptrdiff_t kSlot_130               = 0x130;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_160               = 0x160;  // 4 bytes - value & 0x7FF
constexpr std::ptrdiff_t kSlot_178               = 0x178;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_190               = 0x190;  // 2 bytes - word
constexpr std::ptrdiff_t kSlot_1B0               = 0x1B0;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_1E8               = 0x1E8;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_220               = 0x220;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_230               = 0x230;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_260               = 0x260;  // 8 bytes - parameter block
constexpr std::ptrdiff_t kSlot_2B0               = 0x2B0;  // 4 bytes
constexpr std::ptrdiff_t kSlot_2B4               = 0x2B4;  // 4 bytes
constexpr std::ptrdiff_t kSlot_2B8               = 0x2B8;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_2F0               = 0x2F0;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_2F8               = 0x2F8;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_310               = 0x310;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_340               = 0x340;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_348               = 0x348;  // 4 bytes
constexpr std::ptrdiff_t kSlot_34C               = 0x34C;  // 4 bytes
constexpr std::ptrdiff_t kSlot_350               = 0x350;  // 1 byte
constexpr std::ptrdiff_t kSlot_358               = 0x358;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_360               = 0x360;  // 4 bytes
constexpr std::ptrdiff_t kSlot_364               = 0x364;  // 4 bytes
constexpr std::ptrdiff_t kSlot_368               = 0x368;  // 1 byte
constexpr std::ptrdiff_t kSlot_3A8               = 0x3A8;  // already defined as kSlot_SavedR9
constexpr std::ptrdiff_t kSlot_3B0               = 0x3B0;  // 64 bytes - SIMD matrix (4x4 floats)
constexpr std::ptrdiff_t kSlot_3C0               = 0x3C0;  // 16 bytes
constexpr std::ptrdiff_t kSlot_3D0               = 0x3D0;  // 16 bytes
constexpr std::ptrdiff_t kSlot_3E0               = 0x3E0;  // 16 bytes
constexpr std::ptrdiff_t kSlot_5B0               = 0x5B0;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_5B8               = 0x5B8;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_5C8               = 0x5C8;  // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_670               = 0x670;  // parameter block
constexpr std::ptrdiff_t kSlot_694               = 0x694;  // word array
constexpr std::ptrdiff_t kSlot_696               = 0x696;  // word array
constexpr std::ptrdiff_t kSlot_8A8               = 0x8A8;  // word array
constexpr std::ptrdiff_t kSlot_90AC              = 0x90AC; // 4 bytes
constexpr std::ptrdiff_t kSlot_90B0              = 0x90B0; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_90C0              = 0x90C0; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_90D0              = 0x90D0; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_90E0              = 0x90E0; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_90F0              = 0x90F0; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9100              = 0x9100; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9110              = 0x9110; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9120              = 0x9120; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9130              = 0x9130; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9140              = 0x9140; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9150              = 0x9150; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9160              = 0x9160; // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_A8                = 0xA8;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_C0                = 0xC0;   // 8 bytes - parameter block
constexpr std::ptrdiff_t kSlot_C8                = 0xC8;   // 2 bytes - parameter block
constexpr std::ptrdiff_t kSlot_E174              = 0xE174; // 2 bytes - saved word (same as kSlot_SavedWord)
constexpr std::ptrdiff_t kSlot_E176              = 0xE176; // 2 bytes - saved word
constexpr std::ptrdiff_t kSlot_E178              = 0xE178; // 2 bytes - saved word

// Data addresses (RIP-relative)
constexpr std::uintptr_t kData_F99FFA0 = 0xF99FFA0; // sub_eea6040 (vendor thunk)
constexpr std::uintptr_t kData_F4EE798 = 0xF4EE798; // jump table (14 cases)
constexpr std::uintptr_t kData_F08C710 = 0xF08C710; // SIMD constant
constexpr std::uintptr_t kData_F4ED2B0 = 0xF4ED2B0; // SIMD constant
constexpr std::uintptr_t kData_F441630 = 0xF441630; // SIMD constant
constexpr std::uintptr_t kData_F08ED30 = 0xF08ED30; // SIMD constant
constexpr std::uintptr_t kData_F441650 = 0xF441650; // SIMD constant
constexpr std::uintptr_t kData_EF40DE0 = 0xEF40DE0; // SIMD constant
constexpr std::uintptr_t kData_EFD3400 = 0xEFD3400; // SIMD constant
constexpr std::uintptr_t kData_EFC6AE0 = 0xEFC6AE0; // source for kSlot_CopiedFromDataEfc6ae0
constexpr std::uintptr_t kData_F441720 = 0xF441720; // SIMD constants source

// External function addresses
constexpr std::uintptr_t kFn_Sub_EEA6040 = 0xEEA6040; // vendor thunk
constexpr std::uintptr_t kFn_Sub_E82DE90 = 0xE82DE90; // lift
constexpr std::uintptr_t kFn_Sub_E935700 = 0xE935700; // lift (boundary: crt)
constexpr std::uintptr_t kFn_Sub_BC6A9D0 = 0xBC6A9D0; // boundary
constexpr std::uintptr_t kFn_Sub_47E8F0  = 0x47E8F0;  // boundary
constexpr std::uintptr_t kFn_Sub_E81E1C0 = 0xE81E1C0; // boundary
constexpr std::uintptr_t kFn_Sub_EEC6ED0 = 0xEEC6ED0; // boundary: crt (memset-like)
constexpr std::uintptr_t kFn_Sub_E822F83 = 0xE822F83; // jump target
constexpr std::uintptr_t kFn_Sub_E82D4C4 = 0xE82D4C4; // jump target
constexpr std::uintptr_t kFn_Sub_E829E0D = 0xE829E0D; // jump target
constexpr std::uintptr_t kFn_Sub_E827F03 = 0xE827F03; // jump target (sub_e827f03)
constexpr std::uintptr_t kFn_Sub_E827F10 = 0xE827F10; // jump target (loc_e827f10)
constexpr std::uintptr_t kFn_Sub_E8299D0 = 0xE8299D0; // jump target (loc_e8299d0)
constexpr std::uintptr_t kFn_Sub_E8299D3 = 0xE8299D3; // jump target (loc_e8299d3)
constexpr std::uintptr_t kFn_Sub_E8299DD = 0xE8299DD; // jump target (loc_e8299dd)

// Forward declarations for lift callees
extern "C" void sub_e82de90(void* rcx, void* rdx, void* r8);
extern "C" void sub_e935700(void* rcx); // boundary: crt

// Forward declarations for boundary callees
using Fn_Sub_BC6A9D0 = void(*)(void* rcx, void* rdx, void* r8, void* r9, void* rsp20, void* rsp28);
using Fn_Sub_47E8F0  = void(*)(void* rcx, void* r8);
using Fn_Sub_E81E1C0 = void(*)(void* rcx, void* rdx, void* r8, void* r9, uint8_t rsp20);
using Fn_Sub_EEC6ED0 = void(*)(void* rcx, void* rdx); // memset-like

// Chunk state structure passed to the lifted chunk function
struct ChunkState_e824af1_part3 {
    // Live GPRs at chunk entry (0xe827a40)
    std::uintptr_t rbx;  // frame base (rsp after alignment), job-state base for stack slots
    std::uintptr_t rbp;  // rsp + 0x80, saved XMM area at rbp+0xE110..rbp+0xE1A0
    std::uintptr_t r12;
    std::uintptr_t r13;
    std::uintptr_t r14;
    std::uintptr_t r15;
    std::uintptr_t rsi;  // draw item list base (from parent's rdx/a1)
    std::uintptr_t rdi;  // loop counter / index

    // Live XMMs at chunk entry (preserved across chunk)
    __m128 xmm6;
    __m128 xmm7;
    __m128 xmm8;
    __m128 xmm9;
    __m128 xmm10;
    __m128 xmm11;
    __m128 xmm12;
    __m128 xmm13;
    __m128 xmm14;
    __m128 xmm15;

    // Stack frame (0xE238 bytes) - accessed via rbx
    alignas(16) std::byte stack_frame[kFrameSize];
};

// Lifted chunk function signature
extern "C" void sub_e824af1_chunk_3(ChunkState_e824af1_part3& state);

// Registry entry macro (to be used in .cpp)
#define LIFT_FN_E824AF1_PART3 \
    LIFT_FN(sub_e824af1, 3, 0xe827a40, 0xe829235, sub_e824af1_chunk_3)

} // namespace d3d12
} // namespace native

// Static assertions for layout verification
static_assert(sizeof(native::d3d12::ChunkState_e824af1_part3) >= 0x100, "ChunkState size check");
static_assert(offsetof(native::d3d12::ChunkState_e824af1_part3, stack_frame) == 0x80, "stack_frame offset");
static_assert(native::d3d12::kFrameSize == 0xE238, "Frame size mismatch");