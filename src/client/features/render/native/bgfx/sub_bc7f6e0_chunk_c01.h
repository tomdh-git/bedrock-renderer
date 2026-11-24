// LIFT 0xbc7f6e0 size 0x1a82 1.26.62.01 VV frame-graph builder
// Chunk 2/2: 0xbc80ed3..0xbc81162
// Chunk state documented in docs/functions/bc7f6e0.md section 'Chunk state'

#pragma once

#include <cstdint>
#include <cstddef>

namespace native::bgfx {

// Forward declarations for lift-set callees
extern "C" void sub_bc7f920(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bc7f945(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bc7f96a(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
extern "C" void sub_bc7f98f(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);

// Boundary wrappers (stl/os/alloc/crt)
namespace boundary {
void sub_73150(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
void sub_e938d70(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);
} // namespace boundary

// Data slot RVAs
static constexpr uintptr_t kDataSlot_12AE1868 = 0x12AE1868;  // global hash slot
static constexpr uintptr_t kDataSlot_12AE1870 = 0x12AE1870;
static constexpr uintptr_t kDataSlot_12AE1878 = 0x12AE1878;
static constexpr uintptr_t kDataSlot_12AE1880 = 0x12AE1880;
static constexpr uintptr_t kDataSlot_12AE1888 = 0x12AE1888;
static constexpr uintptr_t kDataSlot_12AE1890 = 0x12AE1890;
static constexpr uintptr_t kDataSlot_12AE1898 = 0x12AE1898;
static constexpr uintptr_t kDataSlot_12AE18A0 = 0x12AE18A0;

// FNV-1a constants observed in the disassembly
static constexpr uint64_t kFnvPrime  = 0x100000001B3ULL;
static constexpr uint64_t kFnvOffset = 0xCBF29CE484222325ULL;

// Chunk state struct matching the live register/stack state at chunk entry (0xbc80ed3)
// Per docs/functions/bc7f6e0.md and docs/data/native_chunks/bc7f6e0.tsv
struct ChunkState_bc7f6e0_c01 {
    // rbp frame base (rbp = rsp + 0x80 at function entry)
    uintptr_t rbp;
    // rsi = scratch buffer pointer (passed in from chunk 1)
    uintptr_t rsi;
    // rdx = length of the scratch buffer (byte count)
    uintptr_t rdx;
    // rax = remaining count for the tail loop
    uintptr_t rax;
    // rcx = running FNV hash accumulator (input to the loop)
    uintptr_t rcx;
    // r8 = current index into rsi buffer (input)
    uintptr_t r8;
    // r9 = FNV prime (input)
    uintptr_t r9;
    // rdi = [rbp+0x308] saved across the chunk (context pointer)
    uintptr_t rdi;
};

} // namespace native::bgfx