#pragma once
#include <cstdint>

namespace native {

// LIFT 0xe870630 size 0x7b 1.26.62.01 BgfxFrameBuilder slot 16 (sub_e870630)
// FrameBuilder slot 16 description-size verifier; ignores its two args.

constexpr uintptr_t kCookieGlobal = 0x1230A0C0;
constexpr uintptr_t kIndirectSlot  = 0xF9A7480;
constexpr uintptr_t kErrStrRef     = 0xF08E738;
constexpr uintptr_t kErrCtxRef     = 0xFB3B080;
constexpr int64_t   kExpectedSize  = 8;

namespace e870630 {
    constexpr int kCookieStackOff  = 0x40; // [rsp+0x40] cookie guard
    constexpr int kErrStructAOff   = 0x28; // [rsp+0x28] err.a
    constexpr int kErrStructBOff   = 0x30; // [rsp+0x30] err.b
    constexpr int kRetSizeField    = 8;    // [ret+8] size field
}

static_assert(kCookieStackOff + sizeof(uintptr_t) <= 0x48, "cookie slot within frame");
static_assert(kErrStructAOff + sizeof(void*) <= 0x48, "err.a within frame");
static_assert(kErrStructBOff + sizeof(uint64_t) <= 0x48, "err.b within frame");
static_assert(sizeof(void*) == 8, "x64");

// Forward-declared lift-set callee (native_boundary.tsv line 521: 0xeec6d80 = lift)
extern "C" void sub_eec6d80(void* ctx, const void* src);

extern "C" bool sub_e870630(void* rcx, const void* rdx);

} // namespace native