#pragma once
#include <cstdint>
#include <cstddef>
#include <immintrin.h>

namespace native {

// Chunk state for sub_bc8eb90 chunk 2 (0xbc9037e..0xbc91b7c)
// Captures all live registers and stack frame pointer at chunk entry
struct ChunkState_bc8eb90_c01 {
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
extern "C" void sub_130ee0(void*, void*, uint64_t, uint64_t);
extern "C" void sub_56939c0(void*, void*);
extern "C" void sub_5693a80(void*, void*);
extern "C" void sub_9d6d0(void*, void*, void*, uint64_t);
extern "C" void sub_eec6de0(void*, void*, uint64_t);
extern "C" void sub_eec6ec0(void*, void*, uint64_t);
extern "C" void sub_bc97070(void*);
extern "C" void sub_568ad40(void*, void*);
extern "C" void sub_76a8a0(void*, void*);
extern "C" void sub_e935700(void*, uint64_t);

// Boundary callees (via function pointers from data slots)
using AllocFn = void*(*)(void*, uint64_t);
using FreeFn = void(*)(void*);

} // namespace native

#define LIFT_FN(name, fn) (void)0