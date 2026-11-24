#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout constants for the bgfx context struct (this/rdi) used by sub_bc73000.
struct bc73000_ctx {
    // Critical section (Enter/Leave) is taken via a 0x1C0-byte object at this+0x1C0.
    static constexpr std::size_t kCS = 0x1C0;
    // Open-addressing hash: keys uint32[0x1000], indices uint16[0x1000], count uint32.
    static constexpr std::size_t kHashKeys = 0x1E4CAB8;
    static constexpr std::size_t kHashIdx = 0x1E50AB8;
    static constexpr std::size_t kHashCount = 0x1E4CAB4;
    // Free list: count uint16, capacity uint16, array uint16[].
    static constexpr std::size_t kFreeCount = 0x1DF145C;
    static constexpr std::size_t kFreeCap = 0x1DF145E;
    static constexpr std::size_t kFreeArr = 0x1DF1460;
    // Per-shader usage counters.
    static constexpr std::size_t kShaderUse = 0x1E2CACC;
    // Per-program arrays (stride 6 bytes = 2+4).
    static constexpr std::size_t kProgIdx = 0x1E52AB8;
    static constexpr std::size_t kProgFlags = 0x1E52ABA;
    static constexpr std::size_t kProgUse = 0x1E52ABC;
    // Logger object pointer and its ring buffer.
    static constexpr std::size_t kLogger = 0x1CFD0C8;
    static constexpr std::size_t kLogWriteIdx = 0xDC5818;
    static constexpr std::size_t kLogBuf = 0xDC5820;
};
static_assert(bc73000_ctx::kCS == 0x1C0);
static_assert(bc73000_ctx::kHashKeys == 0x1E4CAB8);
static_assert(bc73000_ctx::kHashIdx == 0x1E50AB8);
static_assert(bc73000_ctx::kHashCount == 0x1E4CAB4);
static_assert(bc73000_ctx::kFreeCount == 0x1DF145C);
static_assert(bc73000_ctx::kFreeCap == 0x1DF145E);
static_assert(bc73000_ctx::kFreeArr == 0x1DF1460);
static_assert(bc73000_ctx::kShaderUse == 0x1E2CACC);
static_assert(bc73000_ctx::kProgIdx == 0x1E52AB8);
static_assert(bc73000_ctx::kProgFlags == 0x1E52ABA);
static_assert(bc73000_ctx::kProgUse == 0x1E52ABC);
static_assert(bc73000_ctx::kLogger == 0x1CFD0C8);
static_assert(bc73000_ctx::kLogWriteIdx == 0xDC5818);
static_assert(bc73000_ctx::kLogBuf == 0xDC5820);

// Boundary thunks (class lift in native_boundary.tsv, forward-declared here).
extern "C" void sub_ebdbf10(void* cs);   // EnterCriticalSection
extern "C" void sub_ebdbf20(void* cs);   // LeaveCriticalSection
extern "C" void sub_ebce390(void* dst, const void* src, std::size_t n); // memcpy
extern "C" void sub_bc79790(void* ctx, std::uint16_t handle, std::uint16_t destroy); // destroy/unbind shader

// sub_bc73000: bgfx::createProgram(ShaderHandle, destroy)
// ABI: rcx=this, rdx=out handle*, r8=ShaderHandle, r9=destroy(bool)
extern "C" std::uint16_t sub_bc73000(void* ctx, std::uint16_t* out, std::uint16_t shader, bool destroy);

} // namespace native::bgfx