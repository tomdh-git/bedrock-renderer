#pragma once

#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// State object of sub_bc769c0 ("bgfx shutdown", size 0x22c, 1.26.62.01).
// The function reads/writes this object's fields at +0x00/+0x08/+0x10/+0x18,
// the 0x48-byte block at self->ptr, and the nodes of the +0x8-linked list
// rooted at *self->ptr. Offsets taken from the disassembly of
// [0xbc769c0, 0xbc76bec). [V]
struct Bc769c0State {
    uint64_t count;   // +0x00  written 0 at the end (mov qword ptr [rsi],0 at 0xbc76ba3)
    uint64_t ptr;     // +0x08  block pointer: read at 0xbc769d7/0xbc76a4c/0xbc76a9c/0xbc76b33/0xbc76b97,
                      // written at 0xbc76b71
    uint64_t end;     // +0x10  written at 0xbc76a50 and 0xbc76b9f; read at 0xbc76aa0
    uint64_t limit;   // +0x18  read at 0xbc76a58, written at 0xbc76b79
};
static_assert(offsetof(Bc769c0State, count) == 0x00, "bc769c0: count at +0x00");
static_assert(offsetof(Bc769c0State, ptr) == 0x08, "bc769c0: ptr at +0x08");
static_assert(offsetof(Bc769c0State, end) == 0x10, "bc769c0: end at +0x10");
static_assert(offsetof(Bc769c0State, limit) == 0x18, "bc769c0: limit at +0x18");

// Node of the +0x8-linked list rooted at *self->ptr: +0x00 tested for zero at 0xbc769e5,
// +0x8 is the link walked by the loop at 0xbc76a0b..0xbc76a03. [V]
struct Bc769c0Node {
    uint64_t field00;  // +0x00
    uint64_t next;     // +0x08
};
static_assert(offsetof(Bc769c0Node, field00) == 0x00, "bc769c0: node field00 at +0x00");
static_assert(offsetof(Bc769c0Node, next) == 0x08, "bc769c0: node next at +0x08");

static constexpr uint32_t kBc769c0BlockSize = 0x48;  // alloc/copy/zero size (mov r8d,0x48 at 0xbc76a8a)
static_assert(kBc769c0BlockSize == 0x48, "bc769c0: block size 0x48");

// void sub_bc769c0(Bc769c0State* self /*rcx*/); no return value is stored on any path. [V]
void sub_bc769c0(Bc769c0State* self);

} // namespace native::bgfx
