#pragma once
// LIFT 0xe824991 size 0x8b52 1.26.62.01 sub_e824991_chunk_c02

#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

// Forward declarations for callees in the lift set / boundary
void sub_47e8f0(void* rcx, void* rdx, void* r8);                              // 0x47e8f0
void sub_eec6ed0(void* rcx, void* rdx);                                       // 0xeec6ed0 (CRT)
void sub_bc6a9d0(void* rcx, void* rdx, void* r8, void* r9);                   // 0xbc6a9d0
void sub_e81e1c0(void* rcx, void* rdx, void* r8, void* r9);                   // 0xe81e1c0
void sub_e820500(void* rcx, void* rdx, void* r8, void* r9);                   // 0xe820500
void sub_e82de90(void* rcx, void* rdx, void* r8);                             // 0xe82de90
void sub_e935700(void* rcx);                                                  // 0xe935700
void sub_e822f83(void* rcx);                                                  // 0xe822f83
void sub_e82d4c4(void* rcx);                                                  // 0xe82d4c4
void sub_e829e0d(void* rcx);                                                  // 0xe829e0d
void sub_e829b50(void* rcx);                                                  // 0xe829b50
void sub_e829caf(void* rcx);                                                  // 0xe829caf
void sub_e8299dd(void* rcx);                                                  // 0xe8299dd

// Vendor allocator via data slot 0xF99FFA0 -> sub_eea6040
void sub_eea6040(void* rcx, void* rdx, void* r8, void* r9);

// Data slot addresses
static constexpr uintptr_t kData_F99FFA0 = 0xF99FFA0;
static constexpr uintptr_t kData_12BB4910 = 0x12BB4910;
static constexpr uintptr_t kData_F08C710 = 0xF08C710;
static constexpr uintptr_t kData_F4ED2B0 = 0xF4ED2B0;
static constexpr uintptr_t kData_F4EE798 = 0xF4EE798;
static constexpr uintptr_t kData_EFD3400 = 0xEFD3400;
static constexpr uintptr_t kData_EF40DE0 = 0xEF40DE0;
static constexpr uintptr_t kData_F441630 = 0xF441630;
static constexpr uintptr_t kData_F08ED30 = 0xF08ED30;
static constexpr uintptr_t kData_F441650 = 0xF441650;

static constexpr uint32_t kFrameSize = 0xE238;

// Chunk state: live registers at chunk entry (per docs/data/native_chunks/e824991.tsv)
struct ChunkState_e824991 {
    uint64_t rbx;   // aligned frame base
    uint64_t rbp;   // original frame pointer + 0x80
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rsi;
    uint64_t rdi;
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
    uint8_t* stack_frame;  // == rbx, size kFrameSize
};

static_assert(sizeof(ChunkState_e824991) == 8*8 + 16*10 + 8, "ChunkState_e824991 size mismatch");
static_assert(offsetof(ChunkState_e824991, rbx) == 0);
static_assert(offsetof(ChunkState_e824991, rbp) == 8);
static_assert(offsetof(ChunkState_e824991, r12) == 16);
static_assert(offsetof(ChunkState_e824991, r13) == 24);
static_assert(offsetof(ChunkState_e824991, r14) == 32);
static_assert(offsetof(ChunkState_e824991, r15) == 40);
static_assert(offsetof(ChunkState_e824991, rsi) == 48);
static_assert(offsetof(ChunkState_e824991, rdi) == 56);
static_assert(offsetof(ChunkState_e824991, xmm6) == 64);
static_assert(offsetof(ChunkState_e824991, xmm15) == 208);
static_assert(offsetof(ChunkState_e824991, stack_frame) == 224);

// Helper to access stack frame slots
inline uint64_t& slot64(ChunkState_e824991& s, uint32_t offset) {
    return *reinterpret_cast<uint64_t*>(s.stack_frame + offset);
}
inline uint32_t& slot32(ChunkState_e824991& s, uint32_t offset) {
    return *reinterpret_cast<uint32_t*>(s.stack_frame + offset);
}
inline uint16_t& slot16(ChunkState_e824991& s, uint32_t offset) {
    return *reinterpret_cast<uint16_t*>(s.stack_frame + offset);
}
inline uint8_t& slot8(ChunkState_e824991& s, uint32_t offset) {
    return *reinterpret_cast<uint8_t*>(s.stack_frame + offset);
}
inline __m128i& slot128(ChunkState_e824991& s, uint32_t offset) {
    return *reinterpret_cast<__m128i*>(s.stack_frame + offset);
}

void sub_e824991_chunk_c02(ChunkState_e824991& s);

} // namespace d3d12
} // namespace native