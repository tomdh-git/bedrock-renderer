#pragma once
#include <cstdint>
#include <cstddef>
#include <immintrin.h>

namespace native {
namespace d3d12 {

// Chunk c03 of sub_e824fbe: 0xe8297a2..0xe82af92 (part 4/7).
// Live registers at chunk entry 0xe8297a2 (inferred from disassembly):
// rbx, rcx, rdx, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15, rax, xmm8, xmm9
// Next chunk (c04) expects: rbx, rbp, rcx, rsi, rdi, rax, rdx, r10, r13, r14
struct ChunkState_e824fbe_c03 {
    void* rbx = nullptr;
    void* rbp = nullptr;
    uint64_t rcx = 0;
    uint64_t rdx = 0;
    uint64_t rsi = 0;
    uint64_t rdi = 0;
    uint64_t rax = 0;
    uint64_t r8 = 0;
    uint64_t r9 = 0;
    void* r10 = nullptr;
    void* r11 = nullptr;
    void* r12 = nullptr;
    void* r13 = nullptr;
    void* r14 = nullptr;
    uint64_t r15 = 0;
    __m128 xmm8 = _mm_setzero_ps();
    __m128 xmm9 = _mm_setzero_ps();
    unsigned char al_flags = 0;
};

// Layout constants used by this chunk (offsets into the rbx frame), with asserts.
namespace Chunk_e824fbe_c03_layout {
    constexpr ptrdiff_t k98   = 0x98;    // [rbx+0x98] vector data pointer
    constexpr ptrdiff_t kA0   = 0xA0;    // [rbx+0xA0] vector control block
    constexpr ptrdiff_t kA8   = 0xA8;    // [rbx+0xA8] second vector data pointer
    constexpr ptrdiff_t kF0   = 0xF0;    // [rbx+0xF0] refcounted object pointer
    constexpr ptrdiff_t k130  = 0x130;   // [rbx+0x130] shader table base
    constexpr ptrdiff_t k160  = 0x160;   // [rbx+0x160] device pointer
    constexpr ptrdiff_t k168  = 0x168;   // [rbx+0x168] shader table pointer
    constexpr ptrdiff_t k170  = 0x170;   // [rbx+0x170] temp pointer
    constexpr ptrdiff_t k190  = 0x190;   // [rbx+0x190] matrix/word
    constexpr ptrdiff_t k1A0  = 0x1A0;   // [rbx+0x1A0] cached resource
    constexpr ptrdiff_t k1AC  = 0x1AC;   // [rbx+0x1AC] flags dword
    constexpr ptrdiff_t k1B0  = 0x1B0;   // [rbx+0x1B0] per-primitive data
    constexpr ptrdiff_t k1E8  = 0x1E8;   // [rbx+0x1E8] index
    constexpr ptrdiff_t k210  = 0x210;   // [rbx+0x210] feature level
    constexpr ptrdiff_t k240  = 0x240;   // [rbx+0x240] pointer check
    constexpr ptrdiff_t k258  = 0x258;   // [rbx+0x258] cached dword
    constexpr ptrdiff_t k25C  = 0x25C;   // [rbx+0x25C] cached dword
    constexpr ptrdiff_t k260  = 0x260;   // [rbx+0x260] bounds struct
    constexpr ptrdiff_t k268  = 0x268;   // [rbx+0x268] size dword
    constexpr ptrdiff_t k26C  = 0x26C;   // [rbx+0x26C] limit dword
    constexpr ptrdiff_t k270  = 0x270;   // [rbx+0x270] matrix dest
    constexpr ptrdiff_t k290  = 0x290;   // [rbx+0x290] pointer
    constexpr ptrdiff_t k298  = 0x298;   // [rbx+0x298] pointer
    constexpr ptrdiff_t k2A8  = 0x2A8;   // [rbx+0x2A8] counter
    constexpr ptrdiff_t k2B0  = 0x2B0;   // [rbx+0x2B0] instance offset
    constexpr ptrdiff_t k2B4  = 0x2B4;   // [rbx+0x2B4] instance offset 2
    constexpr ptrdiff_t k2B8  = 0x2B8;   // [rbx+0x2B8] instance count
    constexpr ptrdiff_t k2E0  = 0x2E0;   // [rbx+0x2E0] min bounds
    constexpr ptrdiff_t k2E8  = 0x2E8;   // [rbx+0x2E8] max bounds
    constexpr ptrdiff_t k2F0  = 0x2F0;   // [rbx+0x2F0] matrix base
    constexpr ptrdiff_t k2F8  = 0x2F8;   // [rbx+0x2F8] matrix array
    constexpr ptrdiff_t k300  = 0x300;   // [rbx+0x300] matrix result
    constexpr ptrdiff_t k310  = 0x310;   // [rbx+0x310] shader resource
    constexpr ptrdiff_t k318  = 0x318;   // [rbx+0x318] shader resource
    constexpr ptrdiff_t k320  = 0x320;   // [rbx+0x320] word
    constexpr ptrdiff_t k32C  = 0x32C;   // [rbx+0x32C] dword
    constexpr ptrdiff_t k330  = 0x330;   // [rbx+0x330] dword
    constexpr ptrdiff_t k334  = 0x334;   // [rbx+0x334] dword
    constexpr ptrdiff_t k338  = 0x338;   // [rbx+0x338] dword
    constexpr ptrdiff_t k340  = 0x340;   // [rbx+0x340] pointer
    constexpr ptrdiff_t k348  = 0x348;   // [rbx+0x348] dword
    constexpr ptrdiff_t k34C  = 0x34C;   // [rbx+0x34C] dword
    constexpr ptrdiff_t k350  = 0x350;   // [rbx+0x350] byte flag
    constexpr ptrdiff_t k358  = 0x358;   // [rbx+0x358] pointer
    constexpr ptrdiff_t k360  = 0x360;   // [rbx+0x360] dword
    constexpr ptrdiff_t k364  = 0x364;   // [rbx+0x364] dword
    constexpr ptrdiff_t k368  = 0x368;   // [rbx+0x368] byte flag
    constexpr ptrdiff_t k370  = 0x370;   // [rbx+0x370] matrix row
    constexpr ptrdiff_t k380  = 0x380;   // [rbx+0x380] matrix row
    constexpr ptrdiff_t k390  = 0x390;   // [rbx+0x390] byte flag
    constexpr ptrdiff_t k3B0  = 0x3B0;   // [rbx+0x3B0] matrix dest row 0
    constexpr ptrdiff_t k3C0  = 0x3C0;   // [rbx+0x3C0] matrix dest row 1
    constexpr ptrdiff_t k3D0  = 0x3D0;   // [rbx+0x3D0] matrix dest row 2
    constexpr ptrdiff_t k3E0  = 0x3E0;   // [rbx+0x3E0] matrix dest row 3
    constexpr ptrdiff_t k3B0_2= 0x3B0;   // alias for k3B0
    constexpr ptrdiff_t k578  = 0x578;   // [rbx+0x578] error context
    constexpr ptrdiff_t k580  = 0x580;   // [rbx+0x580] resource pointer
    constexpr ptrdiff_t k59C  = 0x59C;   // [rbx+0x59C] dword
    constexpr ptrdiff_t k5A0  = 0x5A0;   // [rbx+0x5A0] dword
    constexpr ptrdiff_t k5A4  = 0x5A4;   // [rbx+0x5A4] dword
    constexpr ptrdiff_t k5B0  = 0x5B0;   // [rbx+0x5B0] transform source
    constexpr ptrdiff_t k5C0  = 0x5C0;   // [rbx+0x5C0] dword
    constexpr ptrdiff_t k5E0  = 0x5E0;   // [rbx+0x5E0] base pointer
    constexpr ptrdiff_t k630  = 0x630;   // [rbx+0x630] dword
    constexpr ptrdiff_t k638  = 0x638;   // [rbx+0x638] pointer
    constexpr ptrdiff_t k658  = 0x658;   // [rbx+0x658] pointer
    constexpr ptrdiff_t k660  = 0x660;   // [rbx+0x660] pointer
    constexpr ptrdiff_t k670  = 0x670;   // [rbx+0x670] per-vertex data
    constexpr ptrdiff_t k690  = 0x690;   // [rbx+0x690] index buffer
    constexpr ptrdiff_t k692  = 0x692;   // [rbx+0x692] index buffer
    constexpr ptrdiff_t k694  = 0x694;   // [rbx+0x694] index buffer (per-index)
    constexpr ptrdiff_t k696  = 0x696;   // [rbx+0x696] index buffer (per-index)
    constexpr ptrdiff_t k8A8  = 0x8A8;   // [rbx+0x8A8] vertex data
    constexpr ptrdiff_t k90A0 = 0x90A0;  // [rbx+0x90A0] matrix source
    constexpr ptrdiff_t k90AC = 0x90AC;  // [rbx+0x90AC] scale dword
    constexpr ptrdiff_t k90B0 = 0x90B0;  // [rbx+0x90B0] output col 0
    constexpr ptrdiff_t k90C0 = 0x90C0;  // [rbx+0x90C0] output col 1
    constexpr ptrdiff_t k90D0 = 0x90D0;  // [rbx+0x90D0] output col 2
    constexpr ptrdiff_t k90E0 = 0x90E0;  // [rbx+0x90E0] output col 3
    constexpr ptrdiff_t k90F0 = 0x90F0;  // [rbx+0x90F0] output col 0 (alt)
    constexpr ptrdiff_t k9100 = 0x9100;  // [rbx+0x9100] output col 1 (alt)
    constexpr ptrdiff_t k9110 = 0x9110;  // [rbx+0x9110] output col 2 (alt)
    constexpr ptrdiff_t k9120 = 0x9120;  // [rbx+0x9120] output col 3 (alt)
    constexpr ptrdiff_t k9130 = 0x9130;  // [rbx+0x9130] output col 0 (alt2)
    constexpr ptrdiff_t k9140 = 0x9140;  // [rbx+0x9140] output col 1 (alt2)
    constexpr ptrdiff_t k9150 = 0x9150;  // [rbx+0x9150] output col 2 (alt2)
    constexpr ptrdiff_t k9160 = 0x9160;  // [rbx+0x9160] output col 3 (alt2)
    constexpr ptrdiff_t kD0   = 0xD0;    // [rbx+0xD0] xmm temp
    constexpr ptrdiff_t kC0   = 0xC0;    // [rbx+0xC0] xmm temp
    constexpr ptrdiff_t kD170 = 0xD170;  // [rbx+0xD170] pointer
    constexpr ptrdiff_t kE174 = 0xE174;  // [rbx+0xE174] cached word
    constexpr ptrdiff_t kE176 = 0xE176;  // [rbx+0xE176] cached word
    constexpr ptrdiff_t kE178 = 0xE178;  // [rbx+0xE178] cached word
}
static_assert(Chunk_e824fbe_c03_layout::k98 == 0x98, "k98");
static_assert(Chunk_e824fbe_c03_layout::kA8 == 0xA8, "kA8");
static_assert(Chunk_e824fbe_c03_layout::k3B0 == 0x3B0, "k3B0");
static_assert(Chunk_e824fbe_c03_layout::k90B0 == 0x90B0, "k90B0");
static_assert(Chunk_e824fbe_c03_layout::k9130 == 0x9130, "k9130");
static_assert(sizeof(ChunkState_e824fbe_c03) >= 16*8, "ChunkState_e824fbe_c03 size");

} // namespace d3d12
} // namespace native