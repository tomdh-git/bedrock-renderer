#pragma once

#include <cstddef>
#include <cstdint>

namespace native {

// Layout reconstructed from the disassembly of 0xbc71da0 (size 0x167, "Frame renderer
// lambda", 1.26.62.01; instruction offsets cited in sub_bc71da0.cpp). The structs are
// layout overlays only: no object of these types is instantiated here.
//
// a0 (Ctx) is the renderer context. +0x1C0 is the address of a lock subobject: the original
// computes it by lea (no load) and passes the address to sub_ebdbf10/sub_ebdbf20.
// +0x1CFD0C8 holds a pointer to the fill/pre-command stream frame.
// +0x1DFC298/+0x1DFC29A are a u16 handle-table count/max, with dense u16 slots at +0x1DFC29C
// (context: docs/BGFX_MAP.md row for 0xbc71da0, "destroy texture", same 0x1dfc298).
//
// The stream frame (rbx = ctx->stream) has a u32 write position at +0xDC5818 and the byte
// stream at +0xDC5820 (bgfx-style pre-command buffer: writePos at +0xDC5818, data at +0xDC5820).

struct CommandStream {
    char pad_0x0000[0xDC5818];
    std::uint32_t writePos;                // +0xDC5818  u32 cursor into data[]
    char pad_0xDC581C[0xDC5820 - 0xDC581C];
    std::uint8_t data[1];                  // +0xDC5820
};

struct Ctx {
    char pad_0x0000[0x1C0];
    std::uint32_t lockField;               // +0x1C0  &ctx->lockField == ctx + 0x1C0 (lea, no load)
    char pad_0x1C4[0x1CFD0C8 - 0x1C4];
    CommandStream* stream;                 // +0x1CFD0C8  [ctx+0x1CFD0C8]
    char pad_0x1CFD0D0[0x1DFC298 - 0x1CFD0D0];
    std::uint16_t handleIndex;             // +0x1DFC298  u16 count
    std::uint16_t handleMax;               // +0x1DFC29A  u16 max/limit
    std::uint16_t handleSlots[1];          // +0x1DFC29C  u16 dense slots
};

static constexpr std::size_t kCtxLockFieldOffset = 0x1C0;
static constexpr std::size_t kCtxStreamOffset = 0x1CFD0C8;
static constexpr std::size_t kCtxHandleIndexOffset = 0x1DFC298;
static constexpr std::size_t kCtxHandleMaxOffset = 0x1DFC29A;
static constexpr std::size_t kCtxHandleSlotsOffset = 0x1DFC29C;
static constexpr std::size_t kStreamWritePosOffset = 0xDC5818;
static constexpr std::size_t kStreamDataOffset = 0xDC5820;

static_assert(offsetof(Ctx, lockField) == kCtxLockFieldOffset, "Ctx+0x1C0 lockField");
static_assert(offsetof(Ctx, stream) == kCtxStreamOffset, "Ctx+0x1CFD0C8 stream");
static_assert(offsetof(Ctx, handleIndex) == kCtxHandleIndexOffset, "Ctx+0x1DFC298 handleIndex");
static_assert(offsetof(Ctx, handleMax) == kCtxHandleMaxOffset, "Ctx+0x1DFC29A handleMax");
static_assert(offsetof(Ctx, handleSlots) == kCtxHandleSlotsOffset, "Ctx+0x1DFC29C handleSlots");
static_assert(offsetof(CommandStream, writePos) == kStreamWritePosOffset, "CommandStream+0xDC5818 writePos");
static_assert(offsetof(CommandStream, data) == kStreamDataOffset, "CommandStream+0xDC5820 data");

// Calls out of 0xbc71da0. The callees are classified `lift` in docs/data/native_boundary.tsv
// and are not yet lifted; they are forward-declared here with the ABI signature evidenced by
// the call sites in sub_bc71da0.cpp and called like any other native function. The
// indirection at their own entries (thunks) belongs to their own lift units:
//   sub_ebdbf10 0xebdbf10: jmp qword ptr [0xF9A7B10]; called at 0xbc71dce as
//       sub_ebdbf10(ctx + 0x1C0, out, a2, a3); return value unused.
//   sub_ebce390 0xebce390: jmp 0xEEC6EC0 (memcpy-like); called at 0xbc71e0b/0xbc71e37/
//       0xbc71e5c/0xbc71e84 as sub_ebce390(dst, src, n); return value unused.
//   sub_ebdbf20 0xebdbf20: jmp qword ptr [0xF9A7B28]; called at 0xbc71ef3 as
//       sub_ebdbf20(ctx + 0x1C0); return value unused.
extern "C" void sub_ebdbf10(void* lock, std::uint16_t* out, std::uint32_t a2,
                            std::uint32_t a3);
extern "C" void sub_ebce390(void* dst, const void* src, std::uint32_t n);
extern "C" void sub_ebdbf20(void* lock);

// Lifted function: 0xbc71da0, size 0x167, returns rdx (out).
// x64 Microsoft ABI: rcx = ctx (Ctx*), rdx = out (std::uint16_t*), r8 = a2 (std::uint32_t),
// r9 = a3 (std::uint32_t); return rax = rdx = out.
extern "C" std::uint16_t* sub_bc71da0(Ctx* ctx, std::uint16_t* out, std::uint32_t a2,
                                      std::uint32_t a3);

} // namespace native
