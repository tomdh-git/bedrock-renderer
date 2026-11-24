// LIFT 0xe824af1 size 0x89f2 1.26.62.01 sub_e824af1
// CHUNK 0xe826261..0xe827a40

#pragma once

#include <cstdint>

namespace native {
namespace d3d12 {

// Forward declarations for lifted callees
void sub_bc5f110(int32_t, const char*, ...); // RendererContextD3D12 base slot 59
void sub_e835f00(void*, uint32_t);            // D3D12 draw executor wrapper
void sub_e83aed0(void*, uint32_t);            // RendererContextD3D12 base slot 26
void sub_e83abb0(void*, uint32_t);            // RendererContextD3D12 base slot 59
void sub_e83ace0(void*, uint32_t);            // D3D12 draw executor wrapper
void* native_boundary_thunk_eea6040(void*, const char*, uint32_t, uint32_t, void*, uint32_t, uint64_t); // vendor thunk via data_f99ffa0
void* sub_eec6ed0(void*, uint32_t);           // CRT import thunk (boundary)

// Stack frame layout constants (relative to rbx = rsp after alignment)
static constexpr uint32_t kStackFrameSize = 0xE238;
static constexpr uint32_t kSavedRcx_Offset = 0xA0;      // job context
static constexpr uint32_t kSavedR8_Offset = 0x168;
static constexpr uint32_t kSavedR9_Offset = 0x3A8;
static constexpr uint32_t kLoopIndex_Offset = 0xF0;
static constexpr uint32_t kLimit_Offset = 0x150;
static constexpr uint32_t kItemArrayBase_Offset = 0x1C0;
static constexpr uint32_t kSecondPtr_Offset = 0x110;
static constexpr uint32_t kOutputBuffer_Offset = 0xB8;
static constexpr uint32_t kOutputIndexArray_Offset = 0x2C0;
static constexpr uint32_t kPerItemStructBase_Offset = 0x3A0;
static constexpr uint32_t kResourceTable_Offset = 0x90;
static constexpr uint32_t kSimdConstTableBase_Offset = 0x90A0;
static constexpr uint32_t kSavedWord_Offset = 0xE174;
static constexpr uint32_t kLoadedWord_Offset = 0x5F0;
static constexpr uint32_t kConstNeg1_Offset = 0x4C0;    // -0x100000000
static constexpr uint32_t kZeroedXmmScratch1_Offset = 0x4E0;
static constexpr uint32_t kZeroedXmmScratch2_Offset = 0x4F0;
static constexpr uint32_t kCopiedDataEfc6ae0_Offset = 0x504;
static constexpr uint32_t kInit1_Offset = 0x514;
static constexpr uint32_t kConstLarge_Offset = 0x518;    // 0x1FFFF00000000
static constexpr uint32_t kConstFFFF_Offset = 0x520;
static constexpr uint32_t kZeroedByte_Offset = 0x522;
static constexpr uint32_t kConstFF00_Offset = 0x523;
static constexpr uint32_t kConst7FFFFFFF_Offset = 0x528;
static constexpr uint32_t kZeroedQword_Offset = 0x52C;
static constexpr uint32_t kConstNeg1_Offset2 = 0x534;
static constexpr uint32_t kBufferStart_Offset = 0x678;
static constexpr uint32_t kBufferEnd_Offset = 0x680;
static constexpr uint32_t kSavedPtr_Offset = 0x688;
static constexpr uint32_t kDwordF003E_Offset = 0x690;
static constexpr uint32_t kCopiedConstsF441720_Offset = 0x794;
static constexpr uint32_t kComputedPerItemAddr_Offset = 0x90A8;
static constexpr uint32_t kShadowVCall1_Offset = 0x20;
static constexpr uint32_t kShadowVCall2_Offset = 0x28;
static constexpr uint32_t kPtrAt128_Offset = 0x128;
static constexpr uint32_t kPtrAt1F8_Offset = 0x1F8;
static constexpr uint32_t kPtrAtB0_Offset = 0xB0;
static constexpr uint32_t kPtrAtB8_Offset = 0xB8;
static constexpr uint32_t kPtrAt220_Offset = 0x220;
static constexpr uint32_t kPtrAt238_Offset = 0x238;
static constexpr uint32_t kDwordAt110_Offset = 0x110;
static constexpr uint32_t kDwordAt180_Offset = 0x180;
static constexpr uint32_t kDwordAtD0_Offset = 0xD0;
static constexpr uint32_t kDwordAtD4_Offset = 0xD4;
static constexpr uint32_t kDwordAtD8_Offset = 0xD8;
static constexpr uint32_t kQwordAtC0_Offset = 0xC0;
static constexpr uint32_t kQwordAtC8_Offset = 0xC8;
static constexpr uint32_t kQwordAt648_Offset = 0x648;
static constexpr uint32_t kQwordAt5E8_Offset = 0x5E8;

// Data addresses
static constexpr uint64_t kDataF7F68E3 = 0xF7F68E3;  // "FAILED: accessing a guarded paged heap backed array out of b..."
static constexpr uint64_t kDataF7CC762 = 0xF7CC762;  // "NOFILE"
static constexpr uint64_t kData12ADF800 = 0x12ADF800;
static constexpr uint64_t kDataF99FFA0 = 0xF99FFA0;  // = sub_eea6040 (vendor thunk)
static constexpr uint64_t kData12BB4910 = 0x12BB4910;

// Boundary function pointers (resolved at runtime from Sigs.json)
using SubEbcE430Fn = void(*)(void*, uint32_t, void*); // memset-like
inline SubEbcE430Fn g_sub_ebce430 = reinterpret_cast<SubEbcE430Fn>(0xEBCE430);

// Chunk state: all live registers and stack frame at chunk entry 0xe826261
struct ChunkState {
    uint64_t rbx;   // stack frame base (rsp after alignment)
    uint64_t rbp;   // rbp = rbx + 0x80 (saved XMM area at rbp+0xE110)
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rsi;
    uint64_t rdi;
    // xmm6-xmm15 are caller-saved in this context but live across chunk
    // We don't model XMM registers in the chunk state struct; they're preserved by the caller
    // Stack frame is at rbx, size 0xE238
};

// Lifted chunk function
void sub_e824af1_chunk2(ChunkState& state);

} // namespace d3d12
} // namespace native

// Layout assertions
static_assert(sizeof(native::d3d12::ChunkState) == 8 * 8, "ChunkState must be 8 registers x 8 bytes");