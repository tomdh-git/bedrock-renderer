#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Context of sub 0xbc5b720 (VV frame-graph builder, size 0x136, 1.26.62.01); the lifted function keeps

// the original's context pointer (arg1, rcx -> rsi) [V]. Offsets below are the ones the disassembly reads

// and writes through that pointer [V].

static_assert(sizeof(std::uintptr_t) == 8, "bc5b720: uintptr_t is 8 bytes on x64");
static_assert(sizeof(std::uint32_t) == 4, "bc5b720: uint32_t is 4 bytes on x64");

// sub 0xbc5b720: VV frame-graph builder. x64 Microsoft ABI: rcx = ctx (arg1, moved to rsi), return in eax.

std::uint32_t sub_bc5b720(std::uintptr_t* ctx);

// Footprint of sub 0xbc5b720: the context object the original writes through [V].

std::uint32_t sub_bc5b720_footprint(std::uintptr_t* ctx);

} // namespace native

