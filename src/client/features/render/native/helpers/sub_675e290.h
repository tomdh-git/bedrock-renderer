#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout for sub_675e290, reverse-engineered from the disassembly
// of [0x675e290, 0x675e384), Minecraft Windows 1.26.62.01.
// Offsets/widths are [proven] from instruction operands; field NAMES and MEANINGS
// are chosen by the lift to make the C++ match the reads/writes/calls in order.
//
// 'ref' is a reference-counted object: fields at +0x8 (strong refcount) and +0xC
// (weak refcount). The destructor path is:
//   vtable[0](self)   -- slot 0, called when strong refcount hits 0
//   vtable[1](self)   -- slot 1, called when weak refcount hits 0

// Field access base rcx/self (+0x00..+0x60 observed). Packed so offsetof matches
// exactly; the real object may have more/padding, so sizeof is a lower bound.
#pragma pack(push, 1)
struct sub_675e290_state {
    void* f0;                                    // +0x00: vtable (R: slot0 call at 0x675e34e/0x675e363)
    std::uint64_t next_ptr;                      // +0x08: u64 R (mov rsi,[rsi+8]) / next strong-refcount RW (lock dec at 0x675e348)
    std::uint8_t pad0x10[0x20];                  // +0x10..+0x2f (no observed access)
    void* f30;                                   // +0x30: pointer R (read at 0x675e30b)
    std::uint8_t pad0x38[0x8];                   // +0x38..+0x3f
    void* f40;                                   // +0x40: pointer R (read at 0x675e2d7)
    std::uint8_t pad0x48[0x8];                   // +0x48..+0x4f
    void* f50;                                   // +0x50: pointer R (read at 0x675e2a3)
    std::uint8_t pad0x58[0x8];                   // +0x58..+0x5f
    std::uint8_t flag60;                         // +0x60: u8 R (cmp at 0x675e296)
};
#pragma pack(pop)

// Ref-counted child object pointed at by f30/f40/f50. Fields at +0x0 vtable,
// +0x8 strong refcount (lock dec), +0xC weak refcount (lock dec).
#pragma pack(push, 1)
struct sub_675e290_ref {
    void* f0;                                    // +0x00: vtable (R)
    std::uint32_t strong_refcount;               // +0x08: u32 RW (lock dec)
    std::uint32_t weak_refcount;                 // +0x0C: u32 RW (lock dec)
};
#pragma pack(pop)

static_assert(offsetof(sub_675e290_state, f0) == 0x00, "");
static_assert(offsetof(sub_675e290_state, next_ptr) == 0x08, "");
static_assert(offsetof(sub_675e290_state, f30) == 0x30, "");
static_assert(offsetof(sub_675e290_state, f40) == 0x40, "");
static_assert(offsetof(sub_675e290_state, f50) == 0x50, "");
static_assert(offsetof(sub_675e290_state, flag60) == 0x60, "");
static_assert(sizeof(sub_675e290_state) >= 0x61, "");

static_assert(offsetof(sub_675e290_ref, f0) == 0x00, "");
static_assert(offsetof(sub_675e290_ref, strong_refcount) == 0x08, "");
static_assert(offsetof(sub_675e290_ref, weak_refcount) == 0x0c, "");
static_assert(sizeof(sub_675e290_ref) >= 0x10, "");

// x64 Microsoft ABI. Returns the result of the tail-jumped vtable[1] call on the
// last non-null child (+0x8 path), or 0 on every early/exit path.
uintptr_t sub_675e290(sub_675e290_state* self);

} // namespace native::helpers
