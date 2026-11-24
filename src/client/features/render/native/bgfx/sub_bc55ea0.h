#pragma once

#include <cstddef>
#include <cstdint>
#include <atomic>

namespace native {

// Layout recovered from the disassembly of 0xbc55ea0 (size 0x105).
// Every offset below is read or written by that function at the stated offset [V];
// role names are inferred from the access pattern [I].
//
// Slot:  +0x00 void* raw      copied between slots, never refcounted
//        +0x08 RefCounted* ref  addrefed when acquired, released when replaced
//
// RefCounted (the object pointed at by Slot::ref):
//        +0x00 void* vptr
//        +0x08 std::uint32_t strong  lock inc on acquire, lock dec on release
//        +0x0C std::uint32_t weak    lock dec after destroy; dealloc when it reaches 0
//        vtable[0]: destroy (run when strong reaches 0)
//        vtable[1]: dealloc (run when weak reaches 0)
// The two virtual calls are indirect (call qword ptr [0xF99FFA0] = jmp-rax slot,
// rax holds the vtable entry at call time): there is no static callee target.
struct RefCounted {
    void* vptr;                                              // +0x00
    std::atomic<std::uint32_t> strong;                       // +0x08
    std::atomic<std::uint32_t> weak;                         // +0x0C
};

struct Slot {
    void* raw;                                               // +0x00
    RefCounted* ref;                                         // +0x08
};

static constexpr std::size_t kSlotRawOffset = 0x00;
static constexpr std::size_t kSlotRefOffset = 0x08;
static constexpr std::size_t kRefVptrOffset = 0x00;
static constexpr std::size_t kRefStrongOffset = 0x08;
static constexpr std::size_t kRefWeakOffset = 0x0C;

static_assert(offsetof(Slot, raw) == kSlotRawOffset, "Slot::raw must be at +0x00");
static_assert(offsetof(Slot, ref) == kSlotRefOffset, "Slot::ref must be at +0x08");
static_assert(sizeof(Slot) == 0x10, "Slot must be 0x10 bytes");
static_assert(offsetof(RefCounted, vptr) == kRefVptrOffset, "RefCounted::vptr must be at +0x00");
static_assert(offsetof(RefCounted, strong) == kRefStrongOffset, "RefCounted::strong must be at +0x08");
static_assert(offsetof(RefCounted, weak) == kRefWeakOffset, "RefCounted::weak must be at +0x0C");
static_assert(sizeof(RefCounted) == 0x10, "RefCounted must be 0x10 bytes");

// Lifted function: 0xbc55ea0, size 0x105, returns void.
// x64 ABI: rcx = a (Slot*), rdx = b (Slot*).
extern "C" void sub_bc55ea0(Slot* a, Slot* b);

} // namespace native
