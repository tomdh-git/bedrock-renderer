#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_0xe935700 (0xE935700 = jmp 0x392960 -> sub_392960) is a lift-set callee
// (docs/data/native_boundary.tsv class lift). Forward-declared here per the lift
// convention (name sub_<rva>, namespace native); called as plain C++, lifted by its
// own unit. Signature [V] from sub_392960: rcx = x, returns rax; x==0 -> 0, else
// reads global at VA 0x15233E1A8 and calls its vtable slot 2 (+0x10), returns rax.
uintptr_t sub_e935700(uint64_t x);

} // namespace native

namespace native::bgfx {

// Layout of the object passed to sub_0xbc8c720 in rcx (this), reverse-engineered from
// the disassembly of [0xbc8c720, 0xbc8c887), Minecraft Windows 1.26.62.01. Only offsets
// the function touches are declared; the rest is padding. Verified against the
// disassembly (rdis dis output, docs/progress/pre/bc8c720_dis.txt).
struct sub_bc8c720_state {
    uint64_t field_0x00;           // +0x00  buffer pointer (read, written 0)
    uint8_t pad_0x08[0x8];         // +0x08
    uint64_t field_0x10;           // +0x10  size-like field (written 0)
    uint64_t field_0x18;           // +0x18  capacity (read)
    uint8_t pad_0x20[0x8];         // +0x20
    uint64_t field_0x28;           // +0x28  list head pointer (entry array, stride 0x28)
    uint64_t field_0x30;           // +0x30  list end pointer
    uint64_t field_0x38;           // +0x38  written 0
    uint8_t pad_0x40[0x10];        // +0x40
    void* field_0x50;              // +0x50  refcounted object A
    uint8_t field_0x58;            // +0x58  u8 flag, compared with 3
    uint8_t pad_0x59[0x1F];        // +0x59
    void* field_0x78;              // +0x78  passed to sub_e935700 (rcx)
    uint8_t pad_0x80[0x270];       // +0x80
    void* field_0x2F0;             // +0x2F0 refcounted object B (vtable slot 4)
};                                 // sizeof == 0x2F8

// List entry layout (buffer at [field_0x28, field_0x30), stride 0x28).
struct sub_bc8c720_entry {
    uint8_t pad_0x00[8];           // +0x00
    void* field_0x08;              // +0x08  refcounted object pointer
    uint8_t pad_0x10[0x7];         // +0x10
    uint8_t field_0x18;            // +0x18  type byte; == 2 releases the object
};                                 // sizeof == 0x28

static_assert(offsetof(sub_bc8c720_state, field_0x00) == 0x00, "sub_0xbc8c720: self+0x00");
static_assert(offsetof(sub_bc8c720_state, field_0x10) == 0x10, "sub_0xbc8c720: self+0x10");
static_assert(offsetof(sub_bc8c720_state, field_0x18) == 0x18, "sub_0xbc8c720: self+0x18");
static_assert(offsetof(sub_bc8c720_state, field_0x28) == 0x28, "sub_0xbc8c720: self+0x28");
static_assert(offsetof(sub_bc8c720_state, field_0x30) == 0x30, "sub_0xbc8c720: self+0x30");
static_assert(offsetof(sub_bc8c720_state, field_0x38) == 0x38, "sub_0xbc8c720: self+0x38");
static_assert(offsetof(sub_bc8c720_state, field_0x50) == 0x50, "sub_0xbc8c720: self+0x50");
static_assert(offsetof(sub_bc8c720_state, field_0x58) == 0x58, "sub_0xbc8c720: self+0x58");
static_assert(offsetof(sub_bc8c720_state, field_0x78) == 0x78, "sub_0xbc8c720: self+0x78");
static_assert(offsetof(sub_bc8c720_state, field_0x2F0) == 0x2F0, "sub_0xbc8c720: self+0x2F0");
static_assert(sizeof(sub_bc8c720_state) == 0x2F8, "sub_0xbc8c720 object size");
static_assert(offsetof(sub_bc8c720_entry, field_0x08) == 0x08, "list entry object at +0x08");
static_assert(offsetof(sub_bc8c720_entry, field_0x18) == 0x18, "list entry type byte at +0x18");
static_assert(sizeof(sub_bc8c720_entry) == 0x28, "list entry stride");

// sub_0xbc8c720(sub_bc8c720_state* self = rcx) -> uintptr_t (rax), Minecraft 1.26.62.01.
// Depth 2, D0, bgfx. Frees the field_0x2F0 refcounted object, notifies sub_e935700 on
// field_0x78, releases field_0x50 when byte[0x58]==3, releases refcounted list entries
// of type 2, then resets the buffer (field_0x10/0x18/0x00) and returns either the old
// capacity or sub_e935700's result (or _invoke_watson when the heap header is corrupt).
uintptr_t sub_bc8c720(sub_bc8c720_state* self);

} // namespace native::bgfx
