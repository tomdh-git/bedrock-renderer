#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_0xe935700 (0xE935700 = jmp 0x392960 -> sub_392960) is a lift-set callee
// (docs/data/native_boundary.tsv class lift). Forward-declared here per the lift
// convention (name sub_<rva>, namespace native); called as plain C++, lifted by its
// own unit. Signature [V] from the call sites below: rcx = arg, rdx = size argument.
extern "C" uintptr_t sub_e935700(std::uint64_t x, std::uint64_t arg2);

} // namespace native

namespace native::bgfx {

// Layout of the object passed to sub_0xbcaa640 in rcx (this), reverse-engineered from
// the disassembly of [0xbcaa640, 0xbcaa775), Minecraft Windows 1.26.62.01. Only
// offsets the function touches are declared; the rest is padding. Verified against the
// disassembly (rdis dis output).
struct sub_bcaa640_state {
    uint64_t field_0x00;           // +0x00  buffer B pointer (byte[0x00] written 0)
    uint8_t  pad_0x08[0x8];        // +0x08
    uint64_t field_0x10;           // +0x10  buffer B size-like field (written 0)
    uint64_t field_0x18;           // +0x18  buffer B capacity (read)
    uint8_t  pad_0x20[0x8];        // +0x20
    void*    field_0x28;           // +0x28  refcounted object A (strong release)
    uint8_t  pad_0x30[0x48];       // +0x30 (0x40 = SSO inline buffer address; used as &self+0x40)
    void*    field_0x78;           // +0x78  refcounted object B (vtable slot 4 release)
    uint8_t  pad_0x80[0x8];        // +0x80
    uint64_t field_0x88;           // +0x88  buffer A pointer (byte[0x88] written 0)
    uint64_t field_0x98;           // +0x98  buffer A size (written 0)
    uint64_t field_0xA0;           // +0xA0  buffer A capacity (read)
};                                 // sizeof == 0xA8

static_assert(offsetof(sub_bcaa640_state, field_0x00) == 0x00, "sub_0xbcaa640: self+0x00");
static_assert(offsetof(sub_bcaa640_state, field_0x10) == 0x10, "sub_0xbcaa640: self+0x10");
static_assert(offsetof(sub_bcaa640_state, field_0x18) == 0x18, "sub_0xbcaa640: self+0x18");
static_assert(offsetof(sub_bcaa640_state, field_0x28) == 0x28, "sub_0xbcaa640: self+0x28");
static_assert(offsetof(sub_bcaa640_state, field_0x78) == 0x78, "sub_0xbcaa640: self+0x78");
static_assert(offsetof(sub_bcaa640_state, field_0x88) == 0x88, "sub_0xbcaa640: self+0x88");
static_assert(offsetof(sub_bcaa640_state, field_0x98) == 0x98, "sub_0xbcaa640: self+0x98");
static_assert(offsetof(sub_bcaa640_state, field_0xA0) == 0xA0, "sub_0xbcaa640: self+0xA0");
static_assert(sizeof(sub_bcaa640_state) == 0xA8, "sub_0xbcaa640 object size");

// sub_0xbcaa640(sub_bcaa640_state* self = rcx) -> void, Minecraft 1.26.62.01.
// Depth 2, D0, bgfx. Frees buffer A (0x88/0x98/0xA0) and buffer B (0x00/0x10/0x18),
// releases the refcounted object at 0x78 (vtable slot 4) and the strong-refcounted
// object at 0x28 (vtable slots 0/1), then resets both buffers to SSO.
void sub_bcaa640(sub_bcaa640_state* self);

} // namespace native::bgfx