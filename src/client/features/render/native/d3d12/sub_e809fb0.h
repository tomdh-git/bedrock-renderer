#pragma once
#include <cstddef>
#include <cstdint>

namespace native::d3d12 {

// Stack-frame layout reconstructed from sub_e809fb0 (0xe809fb0..0xe80a051).
// The function builds two 16-byte contexts on its own stack frame:
//
//   context A ([rbp-0x60]): { base = 0xF4EE230, ptr = rdx }
//   context B ([rbp-0x20]): { base = 0xF4EE260, ptr = rdx }
//
// Offsets are into each context object. Every offset the function reads or
// writes is a named constant and asserted below. The contexts are the
// function's own stack objects; no game struct fields are touched directly.

struct SlotContextA {
    void* base; // 0x00  loaded with immediate 0xF4EE230 (0xe809fca lea rax,[0xF4EE230])
    void* ptr;  // 0x08  copy of the rdx argument (0xe809fd5 mov [rbp-0x58],rdx)
};

struct SlotContextB {
    void* base; // 0x00  loaded with immediate 0xF4EE260 (0xe809fe5 lea rax,[0xF4EE260])
    void* ptr;  // 0x08  copy of the rdx argument (0xe809ff0 mov [rbp-0x18],rdx)
};

static constexpr std::uintptr_t kContextBaseA = 0xF4EE230ULL; // 0xe809fca
static constexpr std::uintptr_t kContextBaseB = 0xF4EE260ULL; // 0xe809fe5
static constexpr std::uintptr_t kMethodSlot   = 0x20;           // 0xe80a017 / 0xe80a03b mov rax,[rax+0x20]

static_assert(offsetof(SlotContextA, base) == 0x00, "sub_e809fb0: context A base offset");
static_assert(offsetof(SlotContextA, ptr)  == 0x08, "sub_e809fb0: context A ptr offset");
static_assert(sizeof(SlotContextA) == 0x10,  "sub_e809fb0: context A size");
static_assert(offsetof(SlotContextB, base) == 0x00, "sub_e809fb0: context B base offset");
static_assert(offsetof(SlotContextB, ptr)  == 0x08, "sub_e809fb0: context B ptr offset");
static_assert(sizeof(SlotContextB) == 0x10,  "sub_e809fb0: context B size");
static_assert(kMethodSlot % sizeof(void*) == 0, "sub_e809fb0: method slot is pointer-sized");

// Exact x64 Microsoft ABI signature of the original:
//   rcx = a0 (this), rdx = a1 (argument stored into both contexts), void return.
extern "C" void sub_e809fb0(void* a0, void* a1);

} // namespace native::d3d12
