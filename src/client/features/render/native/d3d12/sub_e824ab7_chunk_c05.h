// LIFT 0xe824ab7 size 0x8a2c 1.26.62.01 sub_e824ab7
// CHUNK 0xe82c2ab..0xe82d4e3
#pragma once

#include <cstdint>
#include <immintrin.h>

namespace native {
namespace d3d12 {

// Forward declarations for lift-set callees with exact ABI from dossiers
extern "C" void sub_e83aed0(void* rcx, void* rdx);                              // 0xe83aed0
extern "C" void sub_e83abb0(void* rcx, void* rdx);                              // 0xe83abb0
extern "C" void sub_bc5f110(void* rcx, const char* rdx);                        // 0xbc5f110
extern "C" void sub_e81b4d0(void* rcx, void* rdx, void* r8, void* r9);          // 0xe81b4d0
extern "C" void sub_e81b720(void* rcx, void* rdx, void* r8, uint32_t r9d);      // 0xe81b720
extern "C" void sub_e81d850(void* rcx, void* rdx, void* r8, uint32_t r9d);      // 0xe81d850
extern "C" void sub_e805e50(void* rcx, void* rdx, void* r8);                    // 0xe805e50
extern "C" void sub_e806410(void* rcx, void* rdx);                              // 0xe806410
extern "C" void sub_e951550(void* rcx);                                         // 0xe951550
extern "C" void sub_e9e7970(void* rcx);                                         // 0xe9e7970
extern "C" void sub_ebdb740(void* rcx);                                         // 0xebdb740
extern "C" void sub_e8221f5(void* rcx, void* rdx, void* r8, void* r9);          // 0xe8221f5
extern "C" void sub_e83b0e0(void* rcx, void* rdx, void* r8, void* r9);          // 0xe83b0e0
extern "C" void sub_e832cee(void* rcx, void* rdx, void* r8, void* r9);          // 0xe832cee

// Boundary callees (not in lift set)
namespace boundary {
    // Vendor allocator thunk (sub_eea6040) - jmp rax via data slot [0xF99FFA0]
    extern "C" void vendor_alloc(void* rcx, void* rdx, void* r8, void* r9);
    // CRT memcpy/memmove (sub_eec59e0)
    extern "C" void* crt_init_0(void* rcx, void* rdx, void* r8, void* r9);
    extern "C" void* crt_init_1(void* rcx, void* rdx, void* r8, void* r9);
    // CRT memset (sub_eec6e40)
    extern "C" void* crt_memset(void* rcx, int value, size_t count);
    // STL vector grow (sub_47e8f0)
    extern "C" void stl_vector_grow(void* rcx);
    // Unknown boundary (sub_75d00)
    extern "C" void sub_75d00(void* rcx);
    // Stack check failure (sub_e951550 is lift, but this is the __security_check_cookie path)
    extern "C" void security_check_cookie(uintptr_t cookie);
}

// Data slot addresses
static constexpr uintptr_t kData_F99FFA0   = 0xF99FFA0;    // -> sub_eea6040 (vendor alloc)
static constexpr uintptr_t kData_F9A8C78   = 0xF9A8C78;    // -> sub_eec59e0 (crt init)
static constexpr uintptr_t kData_1230A0C0  = 0x1230A0C0;   // security cookie
static constexpr uintptr_t kData_12ADF800  = 0x12ADF800;   // global allocator
static constexpr uintptr_t kData_F7F68E3   = 0xF7F68E3;    // error string
static constexpr uintptr_t kData_F7CC762   = 0xF7CC762;    // "NOFILE" string

// Chunk state passed to the step function (documented in docs/functions/e824ab7.md 'Chunk state')
struct ChunkState_e824ab7_c05 {
    // Live general-purpose registers at chunk entry (0xe82c2ab)
    // The chunk is entered via jump, so all callee-saved registers are live
    uint64_t rbx;   // [V] frame base pointer (all [rbx+off] accesses)
    uint64_t rbp;   // [V] callee-saved frame pointer
    uint64_t r12;   // [V] callee-saved
    uint64_t r13;   // [V] callee-saved
    uint64_t r14;   // [V] callee-saved
    uint64_t r15;   // [V] callee-saved
    uint64_t rsi;   // [V] callee-saved
    uint64_t rdi;   // [V] callee-saved

    // Live XMM registers (xmm6-xmm15 are callee-saved, saved at rbp+0xE110..0xE1A0)
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

    // Stack frame base (== rbx) for [rbx+off] access
    uint8_t* stack_frame;
};

// Static assertions for struct layout
static_assert(sizeof(ChunkState_e824ab7_c05) == 8*8 + 16*10 + 8, "ChunkState_e824ab7_c05 size mismatch");
static_assert(offsetof(ChunkState_e824ab7_c05, rbx) == 0);
static_assert(offsetof(ChunkState_e824ab7_c05, rbp) == 8);
static_assert(offsetof(ChunkState_e824ab7_c05, r12) == 16);
static_assert(offsetof(ChunkState_e824ab7_c05, r13) == 24);
static_assert(offsetof(ChunkState_e824ab7_c05, r14) == 32);
static_assert(offsetof(ChunkState_e824ab7_c05, r15) == 40);
static_assert(offsetof(ChunkState_e824ab7_c05, rsi) == 48);
static_assert(offsetof(ChunkState_e824ab7_c05, rdi) == 56);
static_assert(offsetof(ChunkState_e824ab7_c05, xmm6) == 64);
static_assert(offsetof(ChunkState_e824ab7_c05, xmm15) == 208);
static_assert(offsetof(ChunkState_e824ab7_c05, stack_frame) == 224);

// Helpers
static inline uint8_t* SF(ChunkState_e824ab7_c05& s, uint32_t off) {
    return s.stack_frame + off;
}
static inline uint64_t* SF_Q(ChunkState_e824ab7_c05& s, uint32_t off) {
    return reinterpret_cast<uint64_t*>(s.stack_frame + off);
}
static inline uint32_t* SF_D(ChunkState_e824ab7_c05& s, uint32_t off) {
    return reinterpret_cast<uint32_t*>(s.stack_frame + off);
}
static inline uint16_t* SF_W(ChunkState_e824ab7_c05& s, uint32_t off) {
    return reinterpret_cast<uint16_t*>(s.stack_frame + off);
}
static inline uint8_t* SF_B(ChunkState_e824ab7_c05& s, uint32_t off) {
    return s.stack_frame + off;
}
static inline void* LoadDataSlot(uintptr_t addr) {
    return *reinterpret_cast<void**>(addr);
}
static inline void CallVendorAlloc(void* rcx, void* rdx, void* r8, void* r9) {
    using Fn = void(*)(void*, void*, void*, void*);
    Fn fn = reinterpret_cast<Fn>(LoadDataSlot(kData_F99FFA0));
    fn(rcx, rdx, r8, r9);
}

// Chunk entry function (static inline step)
void sub_e824ab7_chunk_c05(ChunkState_e824ab7_c05& state);

} // namespace d3d12
} // namespace native