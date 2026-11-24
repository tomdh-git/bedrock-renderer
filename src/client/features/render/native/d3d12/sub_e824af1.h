// LIFT 0xe824af1 size 0x89f2 1.26.62.01 sub_e824af1
#pragma once

#include <cstdint>
#include <cstddef>
#include <immintrin.h>

namespace native {
namespace d3d12 {

// ============================================================================
// Forward declarations for all callees (lift set and boundary)
// ============================================================================

// Vendor thunk via data_f99ffa0 (0xEEA6040) - boundary:vendor
using Thunk_eea6040_t = void(*)(void* rcx, uint32_t edx, void* r8, void* r9, void* stack_rsp20);
extern Thunk_eea6040_t g_thunk_eea6040;

// Lift callees (forward declared)
void sub_e82d960(void* rcx, void* rdx, uint32_t r8d, void* r9);
void sub_ebce390(void* rcx, void* rdx, uint32_t r8d);
void sub_e82dcc0(void* rcx, uint32_t r8d);
void sub_ebd1560(void* rcx);
void sub_e82de90(void* rcx, void* rdx, void* r8);
void sub_e935700(void* rcx);
void sub_e835b50(void* rcx, uint32_t edx);
void sub_eec6ed0(void* rcx, uint32_t r8d, uint32_t edx); // boundary:crt
void sub_e820500(void* rcx, void* rdx, void* r8, void* r9); // lift
void sub_e83ace0(void* rcx); // lift
void sub_e82306e(void* state); // jump target in parent
void sub_e823066(void* state); // jump target in parent
void sub_e827c85(void* state); // jump target
void sub_e82d4c4(void* state); // jump target

// Chunk 2 callees (0xe826261..0xe827a40)
void sub_bc5f110(int32_t, const char*, ...); // RendererContextD3D12 base slot 59
void sub_e835f00(void*, uint32_t);            // D3D12 draw executor wrapper
void sub_e83aed0(void*, uint32_t);            // RendererContextD3D12 base slot 26
void sub_e83abb0(void*, uint32_t);            // RendererContextD3D12 base slot 59
void sub_e83ace0_chunk2(void*, uint32_t);     // D3D12 draw executor wrapper

// Chunk 3 callees (0xe827a40..0xe829235)
void sub_bc6a9d0(void* rcx, void* rdx, void* r8, void* r9, void* rsp20, void* rsp28);
void sub_47e8f0(void* rcx, void* r8);
void sub_e81e1c0(void* rcx, void* rdx, void* r8, void* r9, uint8_t rsp20);
void sub_eec6ed0_chunk3(void* rcx, void* rdx); // memset-like

// Chunk 4 callees (0xe829235..0xe82a912)
void sub_e8360f0(void* rcx, void* r8); // lift
void sub_e81b4d0(void* rcx, void* rdx, void* r8); // lift
void sub_e81b720(void* rcx, void* rdx, void* r8); // lift
void sub_ebdb740(void* rcx); // lift
void sub_e81d850(void* rcx, void* rdx); // lift

// Chunk 5 callees (0xe82c101..0xe82d4be)
// (already included above)

// Chunk 6/7 callees (0xe82d4be..0xe82d4e3)
void sub_eec59e0(void* rcx, void* rdx, void* r8, void* r9); // lift

// ============================================================================
// Stack frame layout constants (relative to rbx = rsp after alignment)
// ============================================================================

constexpr std::size_t kStackFrameSize = 0xE238;
constexpr std::size_t kRbpOffsetFromRsp = 0x80;

// Stack slots (relative to rbx) - from dossier
constexpr std::ptrdiff_t kSlot_JobContext            = 0xA0;    // 8 bytes - saved rcx (parent a0)
constexpr std::ptrdiff_t kSlot_SavedR8               = 0x168;   // 8 bytes - saved r8 (parent a2)
constexpr std::ptrdiff_t kSlot_SavedR9               = 0x3A8;   // 8 bytes - saved r9 (parent a3)
constexpr std::ptrdiff_t kSlot_LoopIndex             = 0xF0;    // 4 bytes - loop index / counter
constexpr std::ptrdiff_t kSlot_LoopLimit             = 0x150;   // 4 bytes - loop limit / bound
constexpr std::ptrdiff_t kSlot_ItemArrayBase         = 0x1C0;   // 8 bytes - pointer to item array base
constexpr std::ptrdiff_t kSlot_SecondPtrLimit        = 0x110;   // 8 bytes - second pointer / limit
constexpr std::ptrdiff_t kSlot_OutputBuffer          = 0xB8;    // 8 bytes - pointer to output buffer
constexpr std::ptrdiff_t kSlot_OutputIndexArray      = 0x2C0;   // 8 bytes - pointer to output index array
constexpr std::ptrdiff_t kSlot_PerItemStructsBase    = 0x3A0;   // 8 bytes - base for per-item structs
constexpr std::ptrdiff_t kSlot_ResourceTable         = 0x90;    // 8 bytes - pointer to resource table
constexpr std::ptrdiff_t kSlot_SimdConstantTableBase = 0x90A0;  // 8 bytes - SIMD constant table base
constexpr std::ptrdiff_t kSlot_SavedWord             = 0xE174;  // 2 bytes - saved word
constexpr std::ptrdiff_t kSlot_LoadedWordFromItem    = 0x5F0;   // 2 bytes - loaded word from item
constexpr std::ptrdiff_t kSlot_Const_Neg100000000    = 0x4C0;   // 8 bytes - constant -0x100000000
constexpr std::ptrdiff_t kSlot_XmmScratch0           = 0x4E0;   // 16 bytes - zeroed XMM scratch
constexpr std::ptrdiff_t kSlot_XmmScratch1           = 0x4F0;   // 16 bytes - zeroed XMM scratch
constexpr std::ptrdiff_t kSlot_CopiedFromDataEfc6ae0 = 0x504;   // 16 bytes - copied from data_efc6ae0
constexpr std::ptrdiff_t kSlot_InitializedTo1        = 0x514;   // 4 bytes - initialized to 1
constexpr std::ptrdiff_t kSlot_Const_1FFFF00000000   = 0x518;   // 8 bytes - constant 0x1FFFF00000000
constexpr std::ptrdiff_t kSlot_Const_FFFF            = 0x520;   // 2 bytes - constant 0xFFFF
constexpr std::ptrdiff_t kSlot_Zeroed1               = 0x522;   // 1 byte - zeroed
constexpr std::ptrdiff_t kSlot_Const_FF00            = 0x523;   // 2 bytes - constant 0xFF00
constexpr std::ptrdiff_t kSlot_Const_7FFFFFFF        = 0x528;   // 4 bytes - constant 0x7FFFFFFF
constexpr std::ptrdiff_t kSlot_Zeroed2               = 0x52C;   // 8 bytes - zeroed
constexpr std::ptrdiff_t kSlot_Const_Neg1            = 0x534;   // 8 bytes - constant -1
constexpr std::ptrdiff_t kSlot_BufferStart           = 0x678;   // 8 bytes - pointer to buffer start
constexpr std::ptrdiff_t kSlot_BufferEnd             = 0x680;   // 8 bytes - pointer to buffer end
constexpr std::ptrdiff_t kSlot_SavedPointer          = 0x688;   // 8 bytes - saved pointer
constexpr std::ptrdiff_t kSlot_Const_FFFFFFFF_3F003E = 0x690;   // 4 bytes - 0xFFFFFFFF / 0x3F003E
constexpr std::ptrdiff_t kSlot_SimdConstants         = 0x794;   // 16*7 bytes - copied constants from data_f441720..data_f441790
constexpr std::ptrdiff_t kSlot_Const_3F003E          = 0x814;   // 4 bytes - constant 0x3F003E
constexpr std::ptrdiff_t kSlot_ComputedPerItemAddr   = 0x90A8;  // 8 bytes - computed per-item address
constexpr std::ptrdiff_t kSlot_ShadowSpace8          = 0x20;    // 8 bytes - zeroed (shadow space for vcall)
constexpr std::ptrdiff_t kSlot_ShadowSpace4          = 0x28;    // 4 bytes - zeroed (shadow space for vcall)

// Additional slots used across chunks
constexpr std::ptrdiff_t kSlot_10C                   = 0x10C;   // 2 bytes - saved di
constexpr std::ptrdiff_t kSlot_130                   = 0x130;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_160                   = 0x160;   // 4 bytes - value & 0x7FF
constexpr std::ptrdiff_t kSlot_178                   = 0x178;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_190                   = 0x190;   // 2 bytes - word
constexpr std::ptrdiff_t kSlot_1B0                   = 0x1B0;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_1E8                   = 0x1E8;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_220                   = 0x220;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_230                   = 0x230;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_260                   = 0x260;   // 8 bytes - parameter block
constexpr std::ptrdiff_t kSlot_2B0                   = 0x2B0;   // 4 bytes
constexpr std::ptrdiff_t kSlot_2B4                   = 0x2B4;   // 4 bytes
constexpr std::ptrdiff_t kSlot_2B8                   = 0x2B8;   // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_2F0                   = 0x2F0;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_2F8                   = 0x2F8;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_310                   = 0x310;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_340                   = 0x340;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_348                   = 0x348;   // 4 bytes
constexpr std::ptrdiff_t kSlot_34C                   = 0x34C;   // 4 bytes
constexpr std::ptrdiff_t kSlot_350                   = 0x350;   // 1 byte
constexpr std::ptrdiff_t kSlot_358                   = 0x358;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_360                   = 0x360;   // 4 bytes
constexpr std::ptrdiff_t kSlot_364                   = 0x364;   // 4 bytes
constexpr std::ptrdiff_t kSlot_368                   = 0x368;   // 1 byte
constexpr std::ptrdiff_t kSlot_3B0                   = 0x3B0;   // 64 bytes - SIMD matrix (4x4 floats)
constexpr std::ptrdiff_t kSlot_3C0                   = 0x3C0;   // 16 bytes
constexpr std::ptrdiff_t kSlot_3D0                   = 0x3D0;   // 16 bytes
constexpr std::ptrdiff_t kSlot_3E0                   = 0x3E0;   // 16 bytes
constexpr std::ptrdiff_t kSlot_5B0                   = 0x5B0;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_5B8                   = 0x5B8;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_5C8                   = 0x5C8;   // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_670                   = 0x670;   // parameter block
constexpr std::ptrdiff_t kSlot_694                   = 0x694;   // word array
constexpr std::ptrdiff_t kSlot_696                   = 0x696;   // word array
constexpr std::ptrdiff_t kSlot_8A8                   = 0x8A8;   // word array
constexpr std::ptrdiff_t kSlot_90AC                  = 0x90AC;  // 4 bytes
constexpr std::ptrdiff_t kSlot_90B0                  = 0x90B0;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_90C0                  = 0x90C0;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_90D0                  = 0x90D0;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_90E0                  = 0x90E0;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_90F0                  = 0x90F0;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9100                  = 0x9100;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9110                  = 0x9110;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9120                  = 0x9120;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9130                  = 0x9130;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9140                  = 0x9140;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9150                  = 0x9150;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_9160                  = 0x9160;  // 16 bytes - XMM
constexpr std::ptrdiff_t kSlot_A8                    = 0xA8;    // 8 bytes - pointer
constexpr std::ptrdiff_t kSlot_C0                    = 0xC0;    // 8 bytes - parameter block
constexpr std::ptrdiff_t kSlot_C8                    = 0xC8;    // 2 bytes - parameter block
constexpr std::ptrdiff_t kSlot_E176                  = 0xE176;  // 2 bytes - saved word
constexpr std::ptrdiff_t kSlot_E178                  = 0xE178;  // 2 bytes - saved word

// ============================================================================
// Data addresses (RIP-relative)
// ============================================================================

constexpr std::uintptr_t kData_F99FFA0   = 0xF99FFA0;  // sub_eea6040 (vendor thunk)
constexpr std::uintptr_t kData_F4EE798   = 0xF4EE798;  // jump table (14 cases)
constexpr std::uintptr_t kData_F4EE7D0   = 0xF4EE7D0;  // jump table (10 cases)
constexpr std::uintptr_t kData_F4EE774   = 0xF4EE774;  // jump table (9 cases)
constexpr std::uintptr_t kData_F08C710   = 0xF08C710;  // SIMD constant
constexpr std::uintptr_t kData_F4ED2B0   = 0xF4ED2B0;  // SIMD constant
constexpr std::uintptr_t kData_F441630   = 0xF441630;  // SIMD constant
constexpr std::uintptr_t kData_F08ED30   = 0xF08ED30;  // SIMD constant
constexpr std::uintptr_t kData_F441650   = 0xF441650;  // SIMD constant
constexpr std::uintptr_t kData_EF40DE0   = 0xEF40DE0;  // SIMD constant
constexpr std::uintptr_t kData_EFD3400   = 0xEFD3400;  // SIMD constant
constexpr std::uintptr_t kData_EFC6AE0   = 0xEFC6AE0;  // source for kSlot_CopiedFromDataEfc6ae0
constexpr std::uintptr_t kData_F441720   = 0xF441720;  // SIMD constants source
constexpr std::uintptr_t kData_12BB4910  = 0x12BB4910; // global data
constexpr std::uintptr_t kData_F9A8C78   = 0xF9A8C78;  // indirect call target

// ============================================================================
// External function addresses
// ============================================================================

constexpr std::uintptr_t kFn_Sub_EEA6040  = 0xEEA6040;  // vendor thunk
constexpr std::uintptr_t kFn_Sub_47E8F0   = 0x47E8F0;   // boundary
constexpr std::uintptr_t kFn_Sub_E81E1C0  = 0xE81E1C0;  // boundary
constexpr std::uintptr_t kFn_Sub_EEC6ED0  = 0xEEC6ED0;  // boundary: crt (memset-like)
constexpr std::uintptr_t kFn_Sub_EEC6EC0  = 0xEEC6EC0;  // boundary: crt (memset-like)
constexpr std::uintptr_t kFn_Sub_E8360F0  = 0xE8360F0;  // lift
constexpr std::uintptr_t kFn_Sub_E81B4D0  = 0xE81B4D0;  // lift
constexpr std::uintptr_t kFn_Sub_E81B720  = 0xE81B720;  // lift
constexpr std::uintptr_t kFn_Sub_EBDB740  = 0xEBDB740;  // lift
constexpr std::uintptr_t kFn_Sub_E81D850  = 0xE81D850;  // lift
constexpr std::uintptr_t kFn_Sub_EBCE430  = 0xEBCE430;  // boundary: stl
constexpr std::uintptr_t kFn_Sub_EEC59E0  = 0xEEC59E0;  // lift
constexpr std::uintptr_t kFn_Sub_E82DE90  = 0xE82DE90;  // lift
constexpr std::uintptr_t kFn_Sub_E935700  = 0xE935700;  // lift
constexpr std::uintptr_t kFn_Sub_BC6A9D0  = 0xBC6A9D0;  // boundary

// ============================================================================
// Main chunk state structure (full function state)
// ============================================================================

struct ChunkState_e824af1 {
    // Live GPRs at function entry (0xe824af1)
    std::uintptr_t rbx;  // frame base (rsp after alignment), job-state base for stack slots
    std::uintptr_t rbp;  // rsp + 0x80, saved XMM area at rbp+0xE110..rbp+0xE1A0
    std::uintptr_t r12;
    std::uintptr_t r13;
    std::uintptr_t r14;
    std::uintptr_t r15;
    std::uintptr_t rsi;  // draw item list base (from parent's rdx/a1)
    std::uintptr_t rdi;  // loop counter / index

    // Live XMMs at function entry (preserved across function)
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

    // Arguments at parent entry (sub_e821120)
    std::uintptr_t a0_job_context;  // rcx
    std::uintptr_t a1_draw_items;   // rdx
    std::uintptr_t a2_saved_r8;     // r8
    std::uintptr_t a3_saved_r9;     // r9

    // Stack frame (0xE238 bytes) - accessed via rbx
    alignas(16) std::byte stack_frame[kStackFrameSize];
};

// ============================================================================
// Helper functions for stack access
// ============================================================================

inline std::uintptr_t& Slot64(ChunkState_e824af1& s, std::ptrdiff_t off) {
    return *reinterpret_cast<std::uintptr_t*>(s.stack_frame.data() + off);
}
inline std::uint32_t& Slot32(ChunkState_e824af1& s, std::ptrdiff_t off) {
    return *reinterpret_cast<std::uint32_t*>(s.stack_frame.data() + off);
}
inline std::uint16_t& Slot16(ChunkState_e824af1& s, std::ptrdiff_t off) {
    return *reinterpret_cast<std::uint16_t*>(s.stack_frame.data() + off);
}
inline std::uint8_t& Slot8(ChunkState_e824af1& s, std::ptrdiff_t off) {
    return *reinterpret_cast<std::uint8_t*>(s.stack_frame.data() + off);
}
inline __m128& SlotXmm(ChunkState_e824af1& s, std::ptrdiff_t off) {
    return *reinterpret_cast<__m128*>(s.stack_frame.data() + off);
}
inline void* SlotPtr(ChunkState_e824af1& s, std::ptrdiff_t off) {
    return reinterpret_cast<void*>(Slot64(s, off));
}

// Stack pointer for shadow space (rsp+0x20 relative to rbp-0x80)
inline void* StackRsp20(ChunkState_e824af1& s) {
    return reinterpret_cast<void*>(s.rbx - 0x80 + 0x20);
}

// ============================================================================
// Chunk entry functions
// ============================================================================

// Chunk 0: 0xe824af1..0xe826261
extern "C" void sub_e824af1_chunk_0(ChunkState_e824af1& state);

// Chunk 1: 0xe826261..0xe827a40
extern "C" void sub_e824af1_chunk_1(ChunkState_e824af1& state);

// Chunk 2: 0xe827a40..0xe829235
extern "C" void sub_e824af1_chunk_2(ChunkState_e824af1& state);

// Chunk 3: 0xe829235..0xe82a912
extern "C" void sub_e824af1_chunk_3(ChunkState_e824af1& state);

// Chunk 4: 0xe82a912..0xe82c101
extern "C" void sub_e824af1_chunk_4(ChunkState_e824af1& state);

// Chunk 5: 0xe82c101..0xe82d4be
extern "C" void sub_e824af1_chunk_5(ChunkState_e824af1& state);

// Chunk 6 (tail): 0xe82d4be..0xe82d4e3
extern "C" void sub_e824af1_chunk_6(ChunkState_e824af1& state);

// ============================================================================
// Full function entry point (with prologue/epilogue)
// ============================================================================

// x64 Microsoft ABI: arguments in rcx, rdx, r8, r9
// This is the lifted version of sub_e824af1 (case 8 of sub_e821120 switch)
extern "C" void sub_e824af1(
    void* rcx,   // a0: job context
    void* rdx,   // a1: draw item list
    void* r8,    // a2
    void* r9     // a3
);

// Registry entry via LIFT_FN
#define LIFT_FN_E824AF1 \
    LIFT_FN(sub_e824af1, "sub_e824af1", 0xe824af1, 0x89f2, NativeMode::Shadow)

} // namespace d3d12
} // namespace native

// Static assertions for layout verification
static_assert(sizeof(native::d3d12::ChunkState_e824af1) >= 0x100, "ChunkState size check");
static_assert(offsetof(native::d3d12::ChunkState_e824af1, stack_frame) == 0xA0, "stack_frame offset");
static_assert(native::d3d12::kStackFrameSize == 0xE238, "Frame size mismatch");