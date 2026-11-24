#pragma once

#include <cstddef>
#include <cstdint>

// sub_bca92f0: VV frame-graph builder temp-buffer releaser (size 0x13b, 1.26.62.01).
// Layout of the `this` object, taken from the disassembly of [0xbca92f0, 0xbca942b).
// Field roles describe the observed access pattern; they are not proven type information.
// The function touches: buf_a@0x00, size_a@0x10, cap_a@0x18, shared@0x28, inline_obj@0x50,
// obj_a@0x88, buf_b@0x98, size_b@0xA8, cap_b@0xB0. [V]
namespace native::bgfx {

struct RefCounted {
    std::uintptr_t vtable;   // +0x00  read (dead: calls go through the IAT thunk [0xF99FFA0])
    std::uint32_t strong;    // +0x08  lock dec dword
    std::uint32_t weak;      // +0x0C  lock dec dword
};
static_assert(offsetof(RefCounted, vtable) == 0x00, "sub_bca92f0: RefCounted::vtable at +0x00");
static_assert(offsetof(RefCounted, strong) == 0x08, "sub_bca92f0: RefCounted::strong at +0x08");
static_assert(offsetof(RefCounted, weak) == 0x0C, "sub_bca92f0: RefCounted::weak at +0x0C");
static_assert(sizeof(RefCounted) == 0x10, "sub_bca92f0: RefCounted is 0x10 bytes");

struct alignas(std::uintptr_t) Builder {
    void* buf_a;               // +0x00
    char pad0[0x10 - 0x08];    // +0x08
    std::uint64_t size_a;      // +0x10  written (0), never read by this function
    std::uint64_t cap_a;       // +0x18
    char pad1[0x28 - 0x1C];    // +0x1C
    RefCounted* shared;        // +0x28
    char pad2[0x50 - 0x30];    // +0x30
    char inline_obj[0x38];     // +0x50  embedded object; only its address is compared with obj_a
    RefCounted* obj_a;         // +0x88
    char pad3[0x98 - 0x90];    // +0x90
    void* buf_b;               // +0x98
    char pad4[0xA8 - 0xA0];    // +0xA0
    std::uint64_t size_b;      // +0xA8  written (0), never read by this function
    std::uint64_t cap_b;       // +0xB0
};
static_assert(offsetof(Builder, buf_a) == 0x00, "sub_bca92f0: Builder::buf_a at +0x00");
static_assert(offsetof(Builder, size_a) == 0x10, "sub_bca92f0: Builder::size_a at +0x10");
static_assert(offsetof(Builder, cap_a) == 0x18, "sub_bca92f0: Builder::cap_a at +0x18");
static_assert(offsetof(Builder, shared) == 0x28, "sub_bca92f0: Builder::shared at +0x28");
static_assert(offsetof(Builder, inline_obj) == 0x50, "sub_bca92f0: Builder::inline_obj at +0x50");
static_assert(offsetof(Builder, obj_a) == 0x88, "sub_bca92f0: Builder::obj_a at +0x88");
static_assert(offsetof(Builder, buf_b) == 0x98, "sub_bca92f0: Builder::buf_b at +0x98");
static_assert(offsetof(Builder, size_b) == 0xA8, "sub_bca92f0: Builder::size_b at +0xA8");
static_assert(offsetof(Builder, cap_b) == 0xB0, "sub_bca92f0: Builder::cap_b at +0xB0");
static_assert(sizeof(Builder) == 0xB8, "sub_bca92f0: Builder is 0xB8 bytes");

// Import slot called on the heap-guard failure path: `call qword ptr [0xF9A8C78]`
// with rcx=rdx=r8=r9=0, followed by int3 (noreturn). [V: rdis dis, [data_f9a8c78]]
static constexpr std::uintptr_t kFailSlotAddr = 0xF9A8C78;

// 0xe935700 (size 0x5): `jmp 0x392960` forwarder = sized deallocator entry
// (rcx = pointer to free; the size passed in rdx by the caller is overwritten inside
// sub_392960 and is dead). Classified lift in docs/data/native_boundary.tsv, called
// directly like any lifted function. [V: rdis dis 0xe935700]
extern "C" void sub_e935700(void* ptr);

// 0xbca92f0, size 0x13b, returns void. x64 Microsoft ABI: rcx = this (Builder*).
extern "C" void sub_bca92f0(Builder* self);

} // namespace native::bgfx
