#pragma once
#include <cstdint>
#include <cstring>

namespace native {

// Chunk c00 of sub_bc68e40: bgfx render-thread command buffer interpreter,
// dispatch + 40-way jump table, range 0xbc68e40..0xbc6a600 (1.26.62.01).
//
// Live state handed to the chunk step function. rcx/rdx are the x64 ABI args:
//   rcx = Context*   (ctx)
//   rdx = CommandBuffer*  (cmdbuf); [cmdbuf+0] = position, cmdbuf+8 = data pointer.
// r8/r9 are stored/forwarded only and are not part of the chunk's live state.
struct Bc68e40ChunkC00State {
    // [cmdbuf+0x0]  uint32_t position   (read/written by every case)
    std::uint32_t pos;
    // [cmdbuf+0x8]  uint8_t* data
    std::uint8_t* data;
    // rcx: Context*
    void* ctx;

    // Scratch bytes the original reads/writes on its stack frame
    // (rsp+0x00..rsp+0x107, frame 0x108). Named offsets used by cases:
    //   +0x20 +0x28 +0x30 +0x38 +0x40 +0x48 +0x50   (arg slots for vcall)
    //   +0x60 +0x62 +0x64 +0x6A +0x6C +0x6D +0x6E   (case 0x09/0x15 fields)
    //   +0x70 +0x78 +0x80                            (case 0x09/0x01)
    //   +0x8C                                         (case 0x01 flags)
    //   +0x90 +0x98 +0xA8 +0xB0 +0xB4 +0xB8 +0xC0 +0xC8 +0xD0
    std::uint8_t stack[0x110];
};

// Forward declarations for lift-set callees (each lifted by its own unit).
void sub_ebce390(void* out, const std::uint8_t* src, std::uint32_t count);  // 0xebce390 byte reader
void sub_ebce5e0(const char* s, std::uint32_t n);                            // 0xebce5e0 strlen-like
void sub_bc5f110(std::uint32_t sev, const char* msg, std::uint32_t a, std::uint32_t b);  // 0xbc5f110 fatal
void sub_bc7a3d0(void* self, std::uint32_t idx, std::uint32_t size);         // 0xbc7a3d0 guarded alloc
void sub_bc6abd0(void* ctx, void* cmdbuf);                                   // 0xbc6abd0 flush/emit
void sub_bc68840(void* ctx, void* cmdbuf);                                   // 0xbc68840 begin/init step
// 0xeea6040 is a vendor thunk resolved through data slot 0xF99FFA0.
void sub_eea6040(void* self, void* arg1, void* arg2, std::uint32_t arg3, std::uint32_t arg4,
                 void* arg5, void* arg6, void* arg7, void* arg8);

}  // namespace native