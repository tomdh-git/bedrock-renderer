#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// Layout constants for StringPair (derived from sub_1d3cb0 field accesses)
struct StringPairLayout {
    // First string (std::string-like, 32 bytes with 16-byte SSO)
    static constexpr std::uintptr_t kPtr0Offset     = 0x00;  // char* or SSO buffer
    static constexpr std::uintptr_t kSize0Offset    = 0x10;  // uint64_t
    static constexpr std::uintptr_t kCapacity0Offset = 0x18; // uint64_t

    // Second string (same layout at +0x20)
    static constexpr std::uintptr_t kPtr1Offset      = 0x20; // char* or SSO buffer
    static constexpr std::uintptr_t kSize1Offset     = 0x30; // uint64_t
    static constexpr std::uintptr_t kCapacity1Offset = 0x38; // uint64_t

    // Initialization flag
    static constexpr std::uintptr_t kInitializedOffset = 0x40; // uint8_t

    // SSO threshold (capacity < 0x10 means SSO)
    static constexpr std::uint64_t kSsoCapacityMax = 0xF;

    // Total size at least 0x41
    static constexpr std::size_t kMinSize = 0x41;

    static_assert(sizeof(void*) == 8, "StringPairLayout: x64 ABI");
    static_assert(kPtr0Offset == 0x00, "StringPairLayout: ptr0 at +0x00");
    static_assert(kSize0Offset == 0x10, "StringPairLayout: size0 at +0x10");
    static_assert(kCapacity0Offset == 0x18, "StringPairLayout: capacity0 at +0x18");
    static_assert(kPtr1Offset == 0x20, "StringPairLayout: ptr1 at +0x20");
    static_assert(kSize1Offset == 0x30, "StringPairLayout: size1 at +0x30");
    static_assert(kCapacity1Offset == 0x38, "StringPairLayout: capacity1 at +0x38");
    static_assert(kInitializedOffset == 0x40, "StringPairLayout: initialized at +0x40");
};

// Opaque type for StringPair (layout asserted above, actual definition in game)
struct StringPair;

// Forward declarations for callees
namespace native {

// sub_eec6de0 (0xeec6de0) - already lifted, memmove tail call
void* sub_eec6de0(void* dst, const void* src, std::uint64_t size);

// sub_9d6d0 (0x9d6d0) - boundary (stl), called with varying signatures
// First call: sub_9d6d0(StringPair* this_, std::uint64_t new_size)
// Tail call: sub_9d6d0(char* dest_ptr, std::uint64_t new_size, const char* src_ptr)
// Declared as a boundary wrapper target; actual call goes through native::boundary::
void sub_9d6d0_boundary_1(StringPair* this_, std::uint64_t new_size);
void sub_9d6d0_boundary_2(char* dest_ptr, std::uint64_t new_size, const char* src_ptr);

// sub_aad30 (0xaad30) - UNRESOLVED CALL, not in boundary or lift tables
// Called as: sub_aad30(StringPair* this_)
void sub_aad30_unresolved(StringPair* this_);

// sub_1d3cb0 (0x1d3cb0) - this function
void sub_1d3cb0(StringPair* this_, const StringPair* src);

} // namespace native