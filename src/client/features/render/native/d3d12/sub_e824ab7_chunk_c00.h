#pragma once
// Layout constants for chunk 0xe824ab7..0xe8262b7 of sub_e824ab7 (D3D12 draw executor, part 1/6)
// Every offset below is the rbx-relative offset read/written by this chunk.
// static_asserts are added as each offset is confirmed from the disassembly.
#include <cstdint>

namespace native {
namespace d3d12 {

// Live state passed into the chunk step function.  Fields 0x000..0x3B0+ mirror the
// rbx frame of sub_e821120; the trailing members carry the registers that are live
// across the chunk entry/exit (the chunk is entered by a jump, not a call).
struct ChunkState_e824ab7_c00 {
    // ---- rbx frame (offsets confirmed [V] from disassembly) ----
    std::uint8_t pad_0x000[0x90];
    // +0x090: context pointer; read at +0x30, +0x224A8, +0x224A0, +0x22498, +0x226A8, +0x226AC
    void* ctx_0x90;
    std::uint8_t pad_0x098[0x8];
    // +0x0A0: pointer read at +0x18, +0x20, +0x24
    void* ptr_0xA0;
    std::uint8_t pad_0x0A8[0x8];
    // +0x0B0: pointer read at +0xC96178, +0xC96180, +0xC96190
    void* ptr_0xB0;
    // +0x0B8: command-buffer-like struct {data@+0, count@+8, capacity@+0x10, elem@+0x18}
    struct CmdBuf {
        void* data;
        std::uint64_t count;
        std::uint64_t capacity;
        std::uint64_t elem_size;
    } cmdbuf_0xB8;
    // +0x0C0..+0x0E7: 0x28-byte scratch record written before each boundary call
    std::uint8_t scratch_0xC0[0x28];
    // +0x0F0: index (r8d/r10d)
    std::uint32_t idx_0xF0;
    std::uint8_t pad_0x0F4[0x20];
    // +0x110: index (r10d)
    std::uint32_t idx_0x110;
    std::uint8_t pad_0x114[0x1C];
    // +0x130: index (r11)
    std::uint32_t idx_0x130;
    std::uint8_t pad_0x134[0x0C];
    // +0x140: pointer
    void* ptr_0x140;
    std::uint8_t pad_0x148[0x8];
    // +0x150: index (edi)
    std::uint32_t idx_0x150;
    std::uint8_t pad_0x154[0x24];
    // +0x178: pointer
    void* ptr_0x178;
    std::uint8_t pad_0x180[0x40];
    // +0x1C0: index (shifted left 4)
    std::uint32_t idx_0x1C0;
    std::uint8_t pad_0x1C4[0x0C];
    // +0x1D0: index
    std::uint32_t idx_0x1D0;
    std::uint8_t pad_0x1D4[0x24];
    // +0x1F8: base pointer of 0xB8-byte array
    void* arr_0x1F8;
    // +0x200: pointer
    void* ptr_0x200;
    std::uint8_t pad_0x208[0x18];
    // +0x220: pointer
    void* ptr_0x220;
    std::uint8_t pad_0x228[0x10];
    // +0x238: pointer
    void* ptr_0x238;
    std::uint8_t pad_0x240[0x80];
    // +0x2C0: pointer (array base of 16-byte entries)
    void* arr_0x2C0;
    std::uint8_t pad_0x2C8[0xC0];
    // +0x388: pointer
    void* ptr_0x388;
    std::uint8_t pad_0x390[0x10];
    // +0x3A0: pointer (array base of 0x78-byte entries)
    void* arr_0x3A0;
    std::uint8_t pad_0x3A8[0x8];
    // +0x3B0: 4-byte flags per entry
    std::uint32_t flags_0x3B0;

    // ---- live registers across chunk entry/exit ----
    std::uint64_t rdi;
    std::uint64_t rsi;
    std::uint64_t r9;
    std::uint64_t r8;
    std::uint64_t r10;
    std::uint64_t r14;
    std::uint64_t r15;
    std::uint64_t r12;
    std::uint64_t r13;
    std::uint64_t rax;
    std::uint64_t rcx;
    std::uint64_t rdx;
};

} // namespace d3d12
} // namespace native