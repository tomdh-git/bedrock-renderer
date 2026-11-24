#pragma once
#include <cstddef>
#include <cstdint>

namespace native::d3d12 {

// Layout of the 32-byte scratch string object filled by sub_e806960 (rbp-0x20 in the original frame):
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

static_assert(sizeof(Str32) == kStrBytes, "e806960: Str32 size");
static_assert(offsetof(Str32, data) == kStrData, "e806960: Str32 data offset");
static_assert(offsetof(Str32, size) == kStrSize, "e806960: Str32 size offset");
static_assert(offsetof(Str32, cap) == kStrCap, "e806960: Str32 cap offset");

// Exact x64 ABI signature of 0xe806960 (rcx=out, rdx=src, rax=out).
extern "C" void* sub_e806960(void* out, const void* src);

// Forward declarations for callees of 0xe806960.
// 0xe834520 (lift set, header sub_e834520.h): declared there, included by the .cpp.
// 0xe834330 (lift set, header sub_e834330.h): declared in namespace native there.
// 0xeec6de0 / 0xeec6ec0: classed 'lift' in docs/data/native_boundary.tsv (size 6 each,
// IAT thunks `jmp qword ptr [0xF9A8AA0]` / `jmp qword ptr [0xF9A8A98]`); forward-declared here
// per the lift rule for lift-set callees, called like any lifted function.
extern "C" void* sub_e834330(void* self, std::size_t add, void* r8, void* r9);   // 0xe834330, lift
extern "C" void sub_eec6de0(void* a1, void* a2, std::uint64_t a3);               // 0xeec6de0, lift
extern "C" void* sub_eec6ec0(void* dst, const void* src, std::size_t n);         // 0xeec6ec0, lift

} // namespace native::d3d12
