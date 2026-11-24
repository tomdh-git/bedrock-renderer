#pragma once
#include <cstdint>
#include <cstddef>

namespace native {
namespace d3d12 {

// Chunk c02 of sub_e824fbe: 0xe827fa3..0xe8297a2 (part 3/7).
// Live registers at chunk entry 0xe827fa3: rbx, rbp, rcx, rsi, rdi, rax, rdx, r13, r15.
// r13/r15 are live-in (read before write in this chunk); added to the state so the
// lifted body compiles against the declared chunk state.
struct ChunkState_e824fbe_c02 {
    void* rbx = nullptr;
    void* rbp = nullptr;
    uint64_t rcx = 0;
    uint64_t rsi = 0;
    uint64_t rdi = 0;
    uint64_t rax = 0;
    uint64_t rdx = 0;
    uint64_t r13 = 0;
    uint64_t r15 = 0;
    unsigned char al_flags = 0;
};

// Layout constants used by this chunk (offsets into the rbx frame), with asserts.
namespace Chunk_e824fbe_c02_layout {
    constexpr ptrdiff_t k3B0 = 0x3B0;  // [rbx+0x3B0] destination row 0 (16 bytes)
    constexpr ptrdiff_t k3C0 = 0x3C0;  // [rbx+0x3C0] row 1
    constexpr ptrdiff_t k3D0 = 0x3D0;  // [rbx+0x3D0] row 2
    constexpr ptrdiff_t k3E0 = 0x3E0;  // [rbx+0x3E0] row 3
    constexpr ptrdiff_t k1B0 = 0x1B0;  // pointer to per-primitive data
    constexpr ptrdiff_t k2F0 = 0x2F0;  // pointer to matrix/transform base
    constexpr ptrdiff_t k2F8 = 0x2F8;  // pointer to matrix array
    constexpr ptrdiff_t k130 = 0x130;  // pointer to per-shader table (element size info)
    constexpr ptrdiff_t k98  = 0x98;   // pointer to vector begin (data ptr)
    constexpr ptrdiff_t kA0  = 0xA0;   // pointer to vector control block
    constexpr ptrdiff_t kA8  = 0xA8;   // pointer to second vector begin
    constexpr ptrdiff_t k90A0= 0x90A0; // matrix source base (row-major 4x4)
    constexpr ptrdiff_t k90B0= 0x90B0; // output column 0
    constexpr ptrdiff_t k90C0= 0x90C0; // output column 1
    constexpr ptrdiff_t k90D0= 0x90D0; // output column 2
    constexpr ptrdiff_t k90E0= 0x90E0; // output column 3
    constexpr ptrdiff_t k90F0= 0x90F0; // output column 0 (variant 2)
    constexpr ptrdiff_t k9100= 0x9100;
    constexpr ptrdiff_t k9110= 0x9110;
    constexpr ptrdiff_t k9120= 0x9120;
    constexpr ptrdiff_t k9130= 0x9130;
    constexpr ptrdiff_t k9140= 0x9140;
    constexpr ptrdiff_t k9150= 0x9150;
    constexpr ptrdiff_t k9160= 0x9160;
    constexpr ptrdiff_t k2B0 = 0x2B0;  // instance offset (dword)
    constexpr ptrdiff_t k1E8 = 0x1E8;  // index (dword) into 0x90A0
    constexpr ptrdiff_t k10E = 0x10E;  // word tag for cache
    constexpr ptrdiff_t kE174= 0xE174; // cached tag slot 1
    constexpr ptrdiff_t kE176= 0xE176; // cached tag slot 2
    constexpr ptrdiff_t kE178= 0xE178; // cached tag slot 3
    constexpr ptrdiff_t k5B0 = 0x5B0;  // pointer to transform source (+0x360..0x390)
    constexpr ptrdiff_t k5B8 = 0x5B8;
    constexpr ptrdiff_t k5C8 = 0x5C8;
    constexpr ptrdiff_t k0AC = 0x90AC; // dword scale source
    constexpr ptrdiff_t k0x14 = 0x14;  // [r8+r15*8+0x14] count
    constexpr ptrdiff_t k0x10 = 0x10;  // [r8+r15*8+0x10] size
}
static_assert(Chunk_e824fbe_c02_layout::k3B0 == 0x3B0, "k3B0");
static_assert(Chunk_e824fbe_c02_layout::k90B0 == 0x90B0, "k90B0");
static_assert(Chunk_e824fbe_c02_layout::k9130 == 0x9130, "k9130");
static_assert(sizeof(ChunkState_e824fbe_c02) >= 8*8, "ChunkState_e824fbe_c02 size");

} // namespace d3d12
} // namespace native