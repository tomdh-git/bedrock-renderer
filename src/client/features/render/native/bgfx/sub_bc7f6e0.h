#pragma once
#include <cstdint>

namespace native {

// Chunk c00 of sub_bc7f6e0 ("VV frame-graph builder", 1.26.62.01):
// range 0xbc7f6e0..0xbc80ed3. Chunk c01 (0xbc80ed3..0xbc81162) is another unit.
//
// Live state handed to the chunk step function. The original keeps a 0x3E8-byte
// stack frame (sub rsp,0x3E8; lea rbp,[rsp+0x80]) and all callee-saved registers
// plus rax/rcx/rdx/r8/r9/r10/r11 across the chunk boundary (docs/data/native_chunks/
// bc7f6e0.tsv). This struct is that snapshot: the 15 GP registers followed by the
// 0x3E8-byte frame, so the next chunk can resume exactly where this one stopped.
struct ChunkState_bc7f6e0 {
    std::uint64_t rax;   // 0x00
    std::uint64_t rcx;   // 0x08
    std::uint64_t rdx;   // 0x10
    std::uint64_t r8;    // 0x18
    std::uint64_t r9;    // 0x20
    std::uint64_t r10;   // 0x28
    std::uint64_t r11;   // 0x30
    void* rbx;           // 0x38
    void* rsi;           // 0x40
    void* rdi;           // 0x48
    void* r12;           // 0x50
    void* r13;           // 0x58
    void* r14;           // 0x60
    void* r15;           // 0x68
    void* rbp;           // 0x70
    std::uint8_t stack[0x3E8];  // 0x78..0x460
};

} // namespace native