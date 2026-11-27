#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout constants for the struct pointed to by rsi (error-report slot).

struct bc735b0_state {
    static constexpr std::size_t kMsgPtr = 0x0;   // [rsi] char*

    static constexpr std::size_t kLen = 0x8;      // [rsi+0x8] int

    static constexpr std::size_t kCode = 0x10;    // [rsi+0x10] int

};
static_assert(bc735b0_state::kMsgPtr == 0x0);
static_assert(bc735b0_state::kLen == 0x8);
static_assert(bc735b0_state::kCode == 0x10);

extern "C" void sub_ebce5e0(char* s, int n); // strlen-ish

void sub_bc76330(void* self, int code, void* slot);

// signature: cx (format flags), dl (bool), r8w (layers?), r9d (format), stack: flags at +0x70, rsi at +0x78

void sub_bc735b0(std::uint16_t cx, std::uint8_t dl, std::uint16_t r8w, std::int32_t r9d, std::uint32_t stackFlags, void* errSlot);

} // namespace native::bgfx