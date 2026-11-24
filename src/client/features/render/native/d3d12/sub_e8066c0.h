#pragma once
#include <cstddef>
#include <cstdint>

namespace native::d3d12 {

// Layout of the 32-byte scratch string object filled by sub_e8066c0
// (rbp-0x20 in the original frame):
//   +0x00 char data[16]
//   +0x10 std::size_t size
//   +0x18 std::size_t cap
struct Str32 {
    char data[16];
    std::size_t size;
    std::size_t cap;
};

static constexpr std::size_t kStrData = 0x00;
static constexpr std::size_t kStrSize = 0x10;
static constexpr std::size_t kStrCap  = 0x18;
static constexpr std::size_t kStrBytes = 0x20;

static_assert(sizeof(Str32) == kStrBytes, "e8066c0: Str32 size");
static_assert(offsetof(Str32, data) == kStrData, "e8066c0: Str32 data offset");
static_assert(offsetof(Str32, size) == kStrSize, "e8066c0: Str32 size offset");
static_assert(offsetof(Str32, cap) == kStrCap, "e8066c0: Str32 cap offset");

// Exact x64 ABI signature of 0xe8066c0 (rcx=out, rdx=src, rax=out).
extern "C" void* sub_e8066c0(void* out, const void* src);

// Forward declarations for lift-set callees called by sub_e8066c0.
// sub_e834330 is defined at global scope in sub_e834330.cpp (lift, size 0x1ee).
extern "C" void* sub_e834330(void* self, std::size_t add, void* r8, void* r9);
// 0xeec6de0 / 0xeec6ec0 are lift-set IAT thunks (size 6 each:
// jmp qword ptr [0xF9A8AA0] / jmp qword ptr [0xF9A8A98]).
extern "C" void sub_eec6de0(void* a1, void* a2, std::uint64_t a3);
extern "C" void* sub_eec6ec0(void* dst, const void* src, std::size_t n);

} // namespace native::d3d12
