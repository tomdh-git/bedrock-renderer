#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace native {

// LIFT 0xe806810 size 0x11c 1.26.62.01 sub_e806810
// sub_e806810 converts a u16 value to a UTF-16 decimal string, optionally prefixes "LVbo:",
// and returns the result as a 32-byte string object copied to the out argument.
// Reversed from sub_e806810 (0xe806810, size 0x11c), depth 1, d3d12, "RendererContextD3D12 base slot 14".

// ---- Data slots (RIP-relative immediates) [V] ----
static constexpr std::uintptr_t kData_LVbo     = 0xF848CF6ULL;   // lea r8,[0xF848CF6] "LVbo: "   0xe80684f, 0xe806887
static constexpr std::uintptr_t kSlotF848D00   = 0xF848D00ULL;   // lea r8,[0xF848D00]           0xe806887

// ---- Temporary string object layout (stack frame at rbp-0x20) [V] ----
// As written by sub_e834520: [tmp+0x00] data ptr, [tmp+0x10] size, [tmp+0x18] capacity.
// The whole 32-byte object ([tmp..tmp+0x20)) is copied to the out argument.
static constexpr std::size_t kTmpData       = 0x00;
static constexpr std::size_t kTmpSize       = 0x10;
static constexpr std::size_t kTmpCap        = 0x18;
static constexpr std::size_t kTmpSizeBytes  = 0x20;
static_assert(kTmpSize == 0x10, "e806810: size at +0x10");
static_assert(kTmpCap == 0x18, "e806810: capacity at +0x18");
static_assert(kTmpSizeBytes == 0x20, "e806810: 32-byte object copy");

// ---- Forward declarations for lift-set callees [V] ----
extern "C" void* sub_e834520(void* strObj, std::uint32_t value);          // 0xe834520, lift (in set)
extern "C" void* sub_e834330(void* self, std::size_t add, void* p8, void* p9); // 0xe834330, lift (in set)
extern "C" void* sub_eec6de0(void* dest, const void* src, std::size_t n);  // 0xeec6de0, lift (boundary row: lift)
extern "C" void* sub_eec6ec0(void* dst, const void* src, std::size_t n);   // 0xeec6ec0, lift (in set via sub_e834330.h)

// ---- Lifted function ----
extern "C" void* sub_e806810(void* out, const std::uint16_t* u16Ptr);

} // namespace native
