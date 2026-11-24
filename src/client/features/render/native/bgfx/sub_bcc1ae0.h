#pragma once
#include <cstddef>
#include <cstdint>

namespace native::bgfx {

// Object passed to sub_bcc1ae0 in rcx (this). Layout reverse-engineered from the disassembly of
// [0xbcc1ae0, 0xbcc1bef), Minecraft Windows 1.26.62.01. Only offsets the function touches are
// declared; the rest is padding.
struct sub_bcc1ae0_state {
    uint8_t  pad_0x00[0x38];       // +0x00
    void*    field_0x38;           // +0x38  std::function factory (vtable[2] call)
    void*    field_0x40;           // +0x40  intrusive list head (node*), written on push
    void*    field_0x48;           // +0x48  intrusive list tail (node*), read + written
    uint8_t  pad_0x50[0x4C];       // +0x50  mutex at +0x50 (sub_eec59f0/sub_eec5a10)
    int32_t  field_0x9C;           // +0x9C  flag; 0x7FFFFFFF means "uninitialised", set to 0x7FFFFFFE
    uint32_t slot_0xA0;            // +0xA0  thread-local slot index (sub_9bd4a0 get / sub_9bd6d0 set)
};

// Node allocated by sub_bcc1ae0 (0x18 bytes). +0x10 is the value pointer the factory fills in.
struct sub_bcc1ae0_node {
    void*  prev;                   // +0x00
    void*  next;                   // +0x08
    void*  value;                  // +0x10
};

static_assert(offsetof(sub_bcc1ae0_state, field_0x38) == 0x38, "sub_bcc1ae0 reads/writes this+0x38 (factory)");
static_assert(offsetof(sub_bcc1ae0_state, field_0x40) == 0x40, "sub_bcc1ae0 reads/writes this+0x40 (list head)");
static_assert(offsetof(sub_bcc1ae0_state, field_0x48) == 0x48, "sub_bcc1ae0 reads/writes this+0x48 (list tail)");
static_assert(offsetof(sub_bcc1ae0_state, field_0x9C) == 0x9C, "sub_bcc1ae0 reads/writes this+0x9C (flag)");
static_assert(offsetof(sub_bcc1ae0_state, slot_0xA0) == 0xA0, "sub_bcc1ae0 reads/writes this+0xA0 (TLS slot)");
static_assert(sizeof(sub_bcc1ae0_node) == 0x18, "sub_bcc1ae0 node size 0x18");
static_assert(offsetof(sub_bcc1ae0_node, prev) == 0x00, "sub_bcc1ae0 node prev at +0x00");
static_assert(offsetof(sub_bcc1ae0_node, next) == 0x08, "sub_bcc1ae0 node next at +0x08");
static_assert(offsetof(sub_bcc1ae0_node, value) == 0x10, "sub_bcc1ae0 node value at +0x10");

// sub_bcc1ae0(sub_bcc1ae0_state* this = rcx) -> void* (rax), Minecraft 1.26.62.01.
// Returns &node->value (node+0x10) for the calling thread's slot; allocates and initialises the
// node on first use per thread.
void* sub_bcc1ae0(sub_bcc1ae0_state* self);

} // namespace native::bgfx