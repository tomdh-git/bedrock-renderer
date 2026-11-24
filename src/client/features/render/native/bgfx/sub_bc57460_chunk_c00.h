#pragma once
#include <cstdint>

namespace native::bgfx {

// Chunk c00 of sub_bc57460: frame-graph builder prologue + main loop
// Range 0xbc57460..0xbc58a85 (1.26.62.01)
//
// Live state handed to the chunk step function. x64 ABI args:
//   rcx = void* ctx (stored to r12 at 0xbc574d4)
//   rdx = void* arg1 (stored to [rbp+0x8A0])
//   r8  = void* arg2 (moved to rdi)
//   r9  = void* arg3 (moved to r15)
// Stack args (shadow space + 4 args):
//   [rsp+0x20] / [rbp+0x9E8] = void* arg4 (moved to r14)
//   [rsp+0x28] / [rbp+0x9F0] = void* arg5 (moved to rsi)
//   [rsp+0x30] / [rbp+0x9F8] = void* arg6 (moved to rbx)
//   [rsp+0x38] / [rbp+0xA00] = uint8_t guard_byte (checked at 0xbc574d7)
//
// Prologue saves: rbp, r15, r14, r13, r12, rsi, rdi, rbx
// Frame: sub rsp, 0x9E8; lea rbp, [rsp+0x80]
// XMM spill: xmm6..xmm15 at [rbp+0x8C0..0x950]
// Guard: [rbp+0x8B8] = 0xFFFFFFFFFFFFFFFE
struct Sub_bc57460_ChunkC00State {
    // Preserved registers across chunk boundary (live at 0xbc58a85)
    void* rbp_frame_base;   // rbp after prologue
    void* r12_ctx;          // ctx argument (rcx)
    void* r15_scratch;      // r9 argument
    void* rsi_scratch;      // stack arg5
    void* rdi_scratch;      // r8 argument
    void* rbx_scratch;      // stack arg6

    // Frame locals (rbp-relative, allocated on this chunk's stack)
    // Total frame ~0xA68 bytes. We only declare what the chunk reads/writes.
    // Offsets from rbp (which = rsp+0x80 after prologue)
    std::uint8_t frame[0xA68];

    // Helper to get rbp-relative address
    template <typename T>
    T* at(std::uint32_t offset) {
        return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(rbp_frame_base) + offset);
    }
    template <typename T>
    const T* at(std::uint32_t offset) const {
        return reinterpret_cast<const T*>(reinterpret_cast<std::uintptr_t>(rbp_frame_base) + offset);
    }
};

// Chunk step function - implements 0xbc57460..0xbc58a85
void sub_bc57460_chunk_c00_step(Sub_bc57460_ChunkC00State* state);

} // namespace native::bgfx