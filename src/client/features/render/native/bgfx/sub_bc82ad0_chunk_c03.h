#pragma once
// LIFT 0xbc82ad0 chunk c03
// Chunk state for sub_bc82ad0 range 0xbc864bb..0xbc864df
// Final chunk of sub_bc82ad0 - tail of 7th FNV-1a hash iteration.

#include <cstdint>
#include <cstddef>

// Forward declaration for the jump target (continuation in same function)
namespace native {
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

// Key locals used in chunk c03 (0xbc864bb..0xbc864df)
static constexpr ptrdiff_t kOff770    = 0x770;  // qword (used for sub_73150)

// Data addresses referenced in this chunk (FNV-1a hash results)
static constexpr uintptr_t kData12AE1AC0 = 0x12AE1AC0;
static constexpr uintptr_t kData12AE1AC8 = 0x12AE1AC8;

// Chunk state struct - minimal for this tail chunk
// At chunk boundary 0xbc864bb, live state:
// - rbp (frame base)
// - rdx (incoming value to store at data_12ae1ac0)
// - rsi, rdi, rbx, r12, r13, r14, r15 (callee-saved, preserved for tail jump)
struct ChunkState_bc82ad0_c03 {
    uint8_t* rbp;           // Frame base pointer (rbp value)
    uint64_t rdx;           // Value to store at data_12ae1ac0
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbx;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
};

// Layout assertions
static_assert(sizeof(ChunkState_bc82ad0_c03) == 9 * 8, "ChunkState_bc82ad0_c03 size");