#pragma once
#include <cstdint>
#include <cstddef>
#include <immintrin.h>

namespace native {

// Chunk state for sub_bc8eb90 chunk 3 (0xbc93379..0xbc94737)
// Captures all live registers and stack frame pointer at chunk entry
struct ChunkState_bc8eb90_c03 {
    // Callee-saved general purpose registers
    uint64_t rbx;
    uint64_t rbp;      // Frame pointer (points to rbp in original frame)
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;

    // Saved XMM registers
    __m128i xmm6;
    __m128i xmm7;

    // Stack frame base (original rbp value) for [rbp+offset] access
    // The actual stack memory is accessed via this pointer
    uint8_t* stack_base;  // == rbp

    // Arguments (preserved in registers per ABI mapping)
    // rcx -> r12 (arg0), rdx -> rsi (arg1), r8 -> rbx (arg2), r9 -> rdi (arg3)
    // These are already in r12, rsi, rbx, rdi above

    // Helper to access stack slots at [rbp+offset]
    template<typename T>
    T& slot(uint32_t offset) {
        return *reinterpret_cast<T*>(stack_base + offset);
    }
    template<typename T>
    const T& slot(uint32_t offset) const {
        return *reinterpret_cast<const T*>(stack_base + offset);
    }
};

// Forward declarations for callees in the lift set
extern "C" void sub_9d6d0(void*, void*, void*, uint64_t);
extern "C" void sub_eec6de0(void*, void*, uint64_t);
extern "C" void sub_e935700(void*, uint64_t);
extern "C" void sub_eea6040(void*);
extern "C" void sub_9bc830(uint64_t);
extern "C" void sub_e938cb0(void*);
extern "C" void sub_79580(void*, void*);
extern "C" void sub_bc95db0(void*, void*);
extern "C" void sub_73150(void*);
extern "C" void sub_e935740(void*);
extern "C" void sub_e938d70(void*);
extern "C" void sub_5668ac0(void*, void*, void*);
extern "C" void sub_bc8ef87(void*);
extern "C" void sub_bc8efdd(void*);
extern "C" void sub_bc8f002(void*);
extern "C" void sub_bc8f027(void*);
extern "C" void sub_bc8f04c(void*);
extern "C" void sub_bc8f071(void*);
extern "C" void sub_bc8f096(void*);
extern "C" void sub_bc8f0bb(void*);
extern "C" void sub_bc8f0e0(void*);
extern "C" void sub_bc8f105(void*);
extern "C" void sub_75720(void*);
extern "C" void sub_75740(void*, void*);
extern "C" void sub_bc8ee87(void*);
extern "C" void sub_bc8f61e(void*);
extern "C" void sub_bc8f766(void*);
extern "C" void sub_bc8fa93(void*);
extern "C" void sub_bc8fe6f(void*);
extern "C" void sub_bc8ff96(void*);
extern "C" void sub_bc90247(void*);
extern "C" void sub_bc90a4e(void*);
extern "C" void sub_bc90bb0(void*);
extern "C" void sub_bc90f45(void*);
extern "C" void sub_bc916e4(void*);
extern "C" void sub_bc91812(void*);
extern "C" void sub_bc91abc(void*);
extern "C" void sub_bc922a5(void*);
extern "C" void sub_bc9240f(void*);
extern "C" void sub_bc9272d(void*);
extern "C" void sub_bc92b2a(void*);
extern "C" void sub_bc92c58(void*);
extern "C" void sub_bc92f23(void*);
extern "C" void sub_bc90398(void*);
extern "C" void sub_bc903c3(void*);
extern "C" void sub_bc910b3(void*);
extern "C" void sub_bc910de(void*);
extern "C" void sub_bc91c10(void*);
extern "C" void sub_bc91c3b(void*);
extern "C" void sub_bc93075(void*);
extern "C" void sub_bc9309e(void*);
extern "C" void sub_bc904f4(void*);
extern "C" void sub_bc904e5(void*);
extern "C" void sub_bc91211(void*);
extern "C" void sub_bc91202(void*);
extern "C" void sub_bc91d6c(void*);
extern "C" void sub_bc91d5d(void*);
extern "C" void sub_bc931bf(void*);

// Boundary callees (via function pointers from data slots)
using AllocFn = void*(*)(void*, uint64_t);
using FreeFn = void(*)(void*);

} // namespace native

#define LIFT_FN(name, fn) (void)0