#pragma once
// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991
// CHUNK 0xe826168..0xe827960

#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

// Forward declarations for callees in the lift set
void sub_bc5f110(void* rcx, void* rdx);                              // 0xbc5f110
void sub_e835f00(void* rcx, void* rdx);                              // 0xe835f00
void sub_e83aed0(void* rcx, void* rdx, void* r8, void* r9);          // 0xe83aed0
void sub_e83abb0(void* rcx, void* rdx);                              // 0xe83abb0
void sub_e83ace0(void* rcx, void* rdx);                              // 0xe83ace0
void sub_e835f00(void* rcx, void* rdx);                              // 0xe835f00 (duplicate)

// Boundary callees (called via data slots or direct)
void sub_eea6040(void* rcx, void* rdx, void* r8, void* r9);          // 0xeea6040 (vendor, via [0xF99FFA0])
void sub_eec6ed0(void* rcx, void* rdx);                              // 0xeec6ed0 (CRT)
void sub_ebce430(void* rcx, void* rdx);                              // 0xebce430 (CRT memset thunk)
void sub_e82dcc0(void* rcx, uint32_t r8d);                           // 0xe82dcc0
void sub_e82d960(void* rcx, void* rdx, uint32_t r8d, uint32_t r9d);  // 0xe82d960
void sub_ebd1560(uint8_t cl);                                        // 0xebd1560
void sub_e935700(void* rcx);                                         // 0xe935700
void sub_bc6a9d0(void* rcx);                                         // 0xbc6a9d0
void sub_e820500(void* rcx, void* rdx, uint32_t r8d, void* r9);      // 0xe820500
void sub_e82de90(void* rcx, void* rdx, void* r8);                    // 0xe82de90
void sub_47e8f0(void* rcx);                                          // 0x47e8f0
void sub_e81e1c0(void* rcx, void* rdx);                              // 0xe81e1c0

// Layout constants for stack frame offsets (from rbx = aligned frame base)
static constexpr uint32_t kFrameSize = 0xE238;

// rbx-relative offsets used in this chunk
static constexpr uint32_t kOff_B0   = 0xB0;    // GlobalChunkState*
static constexpr uint32_t kOff_90   = 0x90;    // ChunkAllocator*
static constexpr uint32_t kOff_B8   = 0xB8;    // HeapHeader*
static constexpr uint32_t kOff_1F8  = 0x1F8;   // chunk pool base
static constexpr uint32_t kOff_128  = 0x128;   // secondary pool base
static constexpr uint32_t kOff_C0   = 0xC0;    // temp arg0
static constexpr uint32_t kOff_C8   = 0xC8;    // temp arg1
static constexpr uint32_t kOff_D0   = 0xD0;    // temp arg2
static constexpr uint32_t kOff_D4   = 0xD4;    // temp arg3
static constexpr uint32_t kOff_D8   = 0xD8;    // temp arg4
static constexpr uint32_t kOff_DC   = 0xDC;    // temp arg5
static constexpr uint32_t kOff_E0   = 0xE0;    // temp arg6
static constexpr uint32_t kOff_110  = 0x110;   // counter
static constexpr uint32_t kOff_130  = 0x130;   // index
static constexpr uint32_t kOff_180  = 0x180;   // saved index
static constexpr uint32_t kOff_388  = 0x388;   // ptr
static constexpr uint32_t kOff_3B0  = 0x3B0;   // array
static constexpr uint32_t kOff_10C  = 0x10C;   // word
static constexpr uint32_t kOff_178  = 0x178;   // ptr
static constexpr uint32_t kOff_220  = 0x220;   // ptr
static constexpr uint32_t kOff_230  = 0x230;   // ptr
static constexpr uint32_t kOff_238  = 0x238;   // ResourceHeap*
static constexpr uint32_t kOff_3A0  = 0x3A0;   // ptr
static constexpr uint32_t kOff_670  = 0x670;   // ptr
static constexpr uint32_t kOff_5D8  = 0x5D8;   // ptr
static constexpr uint32_t kOff_588  = 0x588;   // ptr
static constexpr uint32_t kOff_2C0  = 0x2C0;   // ptr
static constexpr uint32_t kOff_F0   = 0xF0;    // dword
static constexpr uint32_t kOff_150  = 0x150;   // dword
static constexpr uint32_t kOff_1C0  = 0x1C0;   // qword
static constexpr uint32_t kOff_1D0  = 0x1D0;   // dword
static constexpr uint32_t kOff_200  = 0x200;   // ptr
static constexpr uint32_t kOff_2D0  = 0x2D0;   // ptr

// GlobalChunkState offsets (at rbx+0xB0)
static constexpr uint32_t kGCS_PoolPtr   = 0xC96178;
static constexpr uint32_t kGCS_PoolSize  = 0xC96180;
static constexpr uint32_t kGCS_PoolCap   = 0xC96188;
static constexpr uint32_t kGCS_PoolFlags = 0xC96190;

// ChunkAllocator offsets (at rbx+0x90)
static constexpr uint32_t kCA_DataPtr        = 0x20460;
static constexpr uint32_t kCA_DataSize       = 0x20468;
static constexpr uint32_t kCA_CapLimit       = 0x20470;
static constexpr uint32_t kCA_Flags          = 0x20478;
static constexpr uint32_t kCA_Field22480     = 0x22480;
static constexpr uint32_t kCA_Field22488     = 0x22488;
static constexpr uint32_t kCA_Field22490     = 0x22490;
static constexpr uint32_t kCA_Field22498     = 0x22498;
static constexpr uint32_t kCA_Field224A0     = 0x224A0;
static constexpr uint32_t kCA_Field224A8     = 0x224A8;
static constexpr uint32_t kCA_Field226AC     = 0x226AC;
static constexpr uint32_t kCA_Field226A8     = 0x226A8;

// HeapHeader offsets (at rbx+0xB8)
static constexpr uint32_t kHH_Field8  = 0x8;
static constexpr uint32_t kHH_Field10 = 0x10;
static constexpr uint32_t kHH_Field18 = 0x18;

// ResourceHeap offsets (at rbx+0x238)
static constexpr uint32_t kRH_BlockPtr  = 0xB8000;
static constexpr uint32_t kRH_BlockSize = 0xB8008;
static constexpr uint32_t kRH_BlockFlags = 0xB8018;

// Chunk entry constants
static constexpr size_t kChunkEntrySize = 0xB8;
static constexpr size_t kChunkPoolBlockSize = 0xB8000;
static constexpr size_t kChunkEntriesPerBlock = kChunkPoolBlockSize / kChunkEntrySize; // 0x1000
static constexpr size_t kChunkPool2BlockSize = 0xC000;
static constexpr size_t kChunkPool3BlockSize = 0x2000;

// Data slot addresses
static constexpr uintptr_t kData_F99FFA0   = 0xF99FFA0;    // -> sub_eea6040
static constexpr uintptr_t kData_12BB4910  = 0x12BB4910;
static constexpr uintptr_t kData_12ADF800  = 0x12ADF800;
static constexpr uintptr_t kData_F7F68E3   = 0xF7F68E3;    // error string
static constexpr uintptr_t kData_F7CC762   = 0xF7CC762;    // "NOFILE"
static constexpr uintptr_t kData_12BB4910_GlobalDevice = 0x12BB4910;

// Magic constants from disassembly
static constexpr uint64_t kMagicDivisor1 = 0x1642C8590B21642D;
static constexpr uint64_t kMagicDivisor2 = 0xB21642C8590B217;
static constexpr uint64_t kMagicDivisor3 = 0xAAAAAAAAAAAAAAAB;

// Chunk state passed to the step function (same live regs as chunk c00)
struct ChunkState_e824991_c01 {
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
static_assert(sizeof(ChunkState_e824991_c01) == 8*8 + 16*10 + 8, "ChunkState_e824991_c01 size mismatch");
static_assert(offsetof(ChunkState_e824991_c01, rbx) == 0);
static_assert(offsetof(ChunkState_e824991_c01, rbp) == 8);
static_assert(offsetof(ChunkState_e824991_c01, r12) == 16);
static_assert(offsetof(ChunkState_e824991_c01, r13) == 24);
static_assert(offsetof(ChunkState_e824991_c01, r14) == 32);
static_assert(offsetof(ChunkState_e824991_c01, r15) == 40);
static_assert(offsetof(ChunkState_e824991_c01, rsi) == 48);
static_assert(offsetof(ChunkState_e824991_c01, rdi) == 56);
static_assert(offsetof(ChunkState_e824991_c01, xmm6) == 64);
static_assert(offsetof(ChunkState_e824991_c01, xmm15) == 208);
static_assert(offsetof(ChunkState_e824991_c01, stack_frame) == 224);

// Chunk entry function (static inline step)
void sub_e824991_chunk_c01(ChunkState_e824991_c01& state);

} // namespace d3d12
} // namespace native