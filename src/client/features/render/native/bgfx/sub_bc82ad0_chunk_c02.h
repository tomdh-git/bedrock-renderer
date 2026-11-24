#pragma once
// LIFT 0xbc82ad0 chunk c02
// Chunk state for sub_bc82ad0 range 0xbc85abd..0xbc864bb
// Mirrors the rbp-frame locals live across this chunk boundary.

#include <cstdint>
#include <cstddef>

// Forward declarations for lifted callees in this chunk (jump targets within the same function)
namespace native {
    void sub_bc82db0(void* frame);   // 0xbc82db0
    void sub_bc82dd5(void* frame);   // 0xbc82dd5
    void sub_bc82dfa(void* frame);   // 0xbc82dfa
    void sub_bc82e1f(void* frame);   // 0xbc82e1f
    void sub_bc82e44(void* frame);   // 0xbc82e44
    void sub_bc831c4(void* frame);   // 0xbc831c4
    void sub_bc831e9(void* frame);   // 0xbc831e9
    void sub_bc8320e(void* frame);   // 0xbc8320e
    void sub_bc83233(void* frame);   // 0xbc83233
    void sub_bc83258(void* frame);   // 0xbc83258
    void sub_bc8327d(void* frame);   // 0xbc8327d
    void sub_bc83422(void* frame);   // 0xbc83422
    void sub_bc83a7f(void* frame);   // 0xbc83a7f
    void sub_bc83aa4(void* frame);   // 0xbc83aa4
    void sub_bc83ac9(void* frame);   // 0xbc83ac9
    void sub_bc83aee(void* frame);   // 0xbc83aee
}

// Boundary callees (via native::boundary)
namespace native::boundary {
    void sub_73150(void* a1);        // 0x73150 (stl)
    void sub_e938d70(void* a1);      // 0xe938d70 (os)
}

// Frame layout constants (rbp-relative offsets from the function prologue)
// rbp = rsp + 0x80 after prologue; frame size 0x938
// Offsets are from rbp. Verified against disassembly.

// Saved XMM registers
static constexpr ptrdiff_t kOffXmm6   = 0x810;
static constexpr ptrdiff_t kOffXmm7   = 0x820;
static constexpr ptrdiff_t kOffXmm8   = 0x830;
static constexpr ptrdiff_t kOffXmm9   = 0x840;
static constexpr ptrdiff_t kOffXmm10  = 0x850;
static constexpr ptrdiff_t kOffXmm11  = 0x860;
static constexpr ptrdiff_t kOffXmm12  = 0x870;
static constexpr ptrdiff_t kOffXmm13  = 0x880;
static constexpr ptrdiff_t kOffXmm14  = 0x890;
static constexpr ptrdiff_t kOffXmm15  = 0x8A0;

// Argument spill slots
static constexpr ptrdiff_t kOffArg1   = 0x670;  // rcx at entry
static constexpr ptrdiff_t kOffArg2   = 0x760;  // rdx at entry
static constexpr ptrdiff_t kOffArg3   = 0x768;  // r8 at entry
static constexpr ptrdiff_t kOffArg4   = 0x0;    // r9 -> r14 (passed in register)

// Key locals used in chunk c02 (0xbc85abd..0xbc864bb)
static constexpr ptrdiff_t kOff4A0    = 0x4A0;  // 16-byte buffer (used for sub_73150)
static constexpr ptrdiff_t kOff6B0    = 0x6B0;  // qword (used for sub_73150)
static constexpr ptrdiff_t kOff770    = 0x770;  // qword (used for sub_73150)

// Data addresses referenced in this chunk (FNV-1a hash results)
static constexpr uintptr_t kData12AE19D0 = 0x12AE19D0;
static constexpr uintptr_t kData12AE19D8 = 0x12AE19D8;
static constexpr uintptr_t kData12AE19E0 = 0x12AE19E0;
static constexpr uintptr_t kData12AE19E8 = 0x12AE19E8;
static constexpr uintptr_t kData12AE19F0 = 0x12AE19F0;
static constexpr uintptr_t kData12AE19F8 = 0x12AE19F8;
static constexpr uintptr_t kData12AE1A00 = 0x12AE1A00;
static constexpr uintptr_t kData12AE1A08 = 0x12AE1A08;
static constexpr uintptr_t kData12AE1A10 = 0x12AE1A10;
static constexpr uintptr_t kData12AE1A18 = 0x12AE1A18;
static constexpr uintptr_t kData12AE1A20 = 0x12AE1A20;
static constexpr uintptr_t kData12AE1A28 = 0x12AE1A28;
static constexpr uintptr_t kData12AE1A30 = 0x12AE1A30;
static constexpr uintptr_t kData12AE1A38 = 0x12AE1A38;
static constexpr uintptr_t kData12AE1A40 = 0x12AE1A40;
static constexpr uintptr_t kData12AE1A48 = 0x12AE1A48;
static constexpr uintptr_t kData12AE1A50 = 0x12AE1A50;
static constexpr uintptr_t kData12AE1A58 = 0x12AE1A58;
static constexpr uintptr_t kData12AE1A60 = 0x12AE1A60;
static constexpr uintptr_t kData12AE1A68 = 0x12AE1A68;
static constexpr uintptr_t kData12AE1A70 = 0x12AE1A70;
static constexpr uintptr_t kData12AE1A78 = 0x12AE1A78;
static constexpr uintptr_t kData12AE1A80 = 0x12AE1A80;
static constexpr uintptr_t kData12AE1A88 = 0x12AE1A88;
static constexpr uintptr_t kData12AE1A90 = 0x12AE1A90;
static constexpr uintptr_t kData12AE1A98 = 0x12AE1A98;
static constexpr uintptr_t kData12AE1AA0 = 0x12AE1AA0;
static constexpr uintptr_t kData12AE1AA8 = 0x12AE1AA8;
static constexpr uintptr_t kData12AE1AB0 = 0x12AE1AB0;
static constexpr uintptr_t kData12AE1AB8 = 0x12AE1AB8;
static constexpr uintptr_t kData12AE1AC0 = 0x12AE1AC0;
static constexpr uintptr_t kData12AE1AC8 = 0x12AE1AC8;

// FNV-1a constants
static constexpr uint64_t kFnvOffsetBasis = 0xCBF29CE484222325ULL;
static constexpr uint64_t kFnvPrime       = 0x100000001B3ULL;

// Chunk state struct - contains the frame pointer (rbp) and callee-saved registers
// At chunk boundary 0xbc85abd, the live state includes:
// - rbp (frame base)
// - r14 (4th argument, held in r14)
// - rbx, rsi, rdi, r12, r13, r15 (callee-saved)
// - xmm6-xmm15 (saved at rbp+0x810..0x8A0)
// All frame locals are accessed via rbp, so we pass rbp as the frame pointer.
struct ChunkState_bc82ad0_c02 {
    uint8_t* rbp;           // Frame base pointer (rbp value)
    uint64_t r14;           // 4th argument (r9 at entry, saved in r14)
    uint64_t rbx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r12;
    uint64_t r13;
    uint64_t r15;
    // xmm6-xmm15 are accessed via rbp offsets, no need to store separately
};

// Layout assertions
static_assert(sizeof(ChunkState_bc82ad0_c02) == 8 * 8, "ChunkState_bc82ad0_c02 size");