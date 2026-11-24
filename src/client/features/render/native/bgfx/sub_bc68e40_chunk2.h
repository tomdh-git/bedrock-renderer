#pragma once
#include <cstdint>
#include <cstring>

namespace native {

// Chunk 2 of sub_bc68e40: bgfx render-thread command buffer interpreter,
// case 0x09 tail + epilogue, range 0xbc6a600..0xbc6a9c3 (1.26.62.01).
//
// Live state handed to the chunk step function. rcx/rdx are the x64 ABI args:
//   rcx = Context*   (ctx)
//   rdx = CommandBuffer*  (cmdbuf); [cmdbuf+0] = position, cmdbuf+8 = data pointer.
// r8/r9 are stored/forwarded only and are not part of the chunk's live state.
struct ChunkState_bc6a600 {
    // rcx: Context*
    void* ctx;
    // [cmdbuf+0x0]  uint32_t position
    std::uint32_t pos;
    // [cmdbuf+0x8]  uint8_t* data
    std::uint8_t* data;
    // rbx: data pointer base (set to rsi+8 at 0xbc6a802)
    std::uint8_t* rbx;
    // r12, r14, r15, rbp: temporaries
    std::uint64_t r12;
    std::uint64_t r14;
    std::uint64_t r15;
    std::uint64_t rbp;
    // Stack frame (rsp+0x00..rsp+0x107, frame 0x108)
    std::uint8_t stack[0x108];
};

// Forward declarations for lift-set callees (each lifted by its own unit).
void sub_ebce390(void* out, const std::uint8_t* src, std::uint32_t count);  // 0xebce390 byte reader
void sub_bc6abd0(void* ctx, void* cmdbuf);                                   // 0xbc6abd0 flush/emit
// 0xbc68840 begin/init step: (rcx=out struct, rdx=cmdbuf, r8=&ctx+0x1EBF2F2, r9d=byte) -> rax
void* sub_bc68840(void* out_struct, void* cmdbuf, void* arg3, std::uint32_t arg4);
// 0xeea6040 is a vendor thunk resolved through data slot 0xF99FFA0; returns int64 in rax.
std::int64_t sub_eea6040(void* self, void* arg1, void* arg2, std::uint32_t arg3, std::uint32_t arg4,
                 void* arg5, void* arg6, void* arg7, void* arg8);

}  // namespace native