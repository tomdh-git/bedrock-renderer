#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Layout of the object passed to sub_0xbc2bca0 in rcx (this), reverse-engineered from the
// disassembly of [0xbc2bca0, 0xbc2be12), Minecraft Windows 1.26.62.01. Only offsets the
// function touches are declared; the rest is padding. Verified against the disassembly.
struct sub_bc2bca0_state {
    uint64_t field_0x00;          // +0x00  buffer pointer (read, written 0)
    uint64_t field_0x10;          // +0x10  size-like field (written 0)
    uint64_t field_0x18;          // +0x18  capacity (read)
    uint8_t field_0x20[0x40];     // +0x20  container destroyed via sub_655cea0(&field_0x20); [0x20,0x60)
    uint64_t field_0x60;          // +0x60  list head pointer (entry array, stride 0x28)
    uint64_t field_0x68;          // +0x68  list end pointer
    uint64_t field_0x70;          // +0x70  written 0
    uint8_t pad_0x78[0x10];       // +0x78
    uint64_t field_0x88;          // +0x88  refcounted object A
    uint8_t field_0x90;           // +0x90  u8 flag, compared with 3
    uint8_t pad_0x91[0x267];      // +0x91 .. 0x2F7
    uint64_t field_0x2F8;         // +0x2F8 refcounted object B
};                                // sizeof == 0x300

// List entry layout (buffer at [field_0x60, field_0x68), stride 0x28).
struct sub_bc2bca0_entry {
    uint8_t pad_0x00[8];          // +0x00
    void* field_0x08;             // +0x08  refcounted object pointer
    uint8_t pad_0x10[0x7];        // +0x10
    uint8_t field_0x18;           // +0x18  type byte; == 2 releases the object
};                                // sizeof == 0x28

static_assert(offsetof(sub_bc2bca0_state, field_0x00) == 0x00, "sub_0xbc2bca0 reads/writes self+0x00");
static_assert(offsetof(sub_bc2bca0_state, field_0x10) == 0x10, "sub_0xbc2bca0 writes self+0x10");
static_assert(offsetof(sub_bc2bca0_state, field_0x18) == 0x18, "sub_0xbc2bca0 reads self+0x18");
static_assert(offsetof(sub_bc2bca0_state, field_0x20) == 0x20, "sub_0xbc2bca0 passes &self+0x20 to sub_655cea0");
static_assert(offsetof(sub_bc2bca0_state, field_0x60) == 0x60, "sub_0xbc2bca0 reads self+0x60 (list head)");
static_assert(offsetof(sub_bc2bca0_state, field_0x68) == 0x68, "sub_0xbc2bca0 reads self+0x68 (list end)");
static_assert(offsetof(sub_bc2bca0_state, field_0x70) == 0x70, "sub_0xbc2bca0 writes self+0x70");
static_assert(offsetof(sub_bc2bca0_state, field_0x88) == 0x88, "sub_0xbc2bca0 reads self+0x88");
static_assert(offsetof(sub_bc2bca0_state, field_0x90) == 0x90, "sub_0xbc2bca0 reads byte self+0x90");
static_assert(offsetof(sub_bc2bca0_state, field_0x2F8) == 0x2F8, "sub_0xbc2bca0 reads/writes self+0x2F8");
static_assert(offsetof(sub_bc2bca0_entry, field_0x08) == 0x08, "list entry object at +0x08");
static_assert(offsetof(sub_bc2bca0_entry, field_0x18) == 0x18, "list entry type byte at +0x18");
static_assert(sizeof(sub_bc2bca0_state) == 0x300, "sub_0xbc2bca0 object size");
static_assert(sizeof(sub_bc2bca0_entry) == 0x28, "list entry stride");

// sub_bc2bca0(sub_bc2bca0_state* this = rcx) -> uintptr_t (rax), Minecraft 1.26.62.01.
uintptr_t sub_bc2bca0(sub_bc2bca0_state* self);

} // namespace native::bgfx
