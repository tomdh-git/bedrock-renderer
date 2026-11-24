#pragma once
#include <cstdint>

namespace native::d3d12 {

// LIFT 0xe84c7d0 size 0x62f 1.26.62.01 sub_e84c7d0
struct SubE84C7D0Args {
    // rcx = this (rsi in body)
};

std::uint32_t sub_e84c7d0(void* self);

// Registry entry
struct NativeEntry_e84c7d0 { const char* name = "sub_e84c7d0"; std::uint64_t rva = 0xe84c7d0; };
#define LIFT_FN(e84c7d0)

} // namespace native::d3d12