#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the item object reached through the slot pointer (*slot) in sub 0xbcac8b0
// ("Item group visitor", size 0x248, 1.26.62.01). Every offset below is read or written
// by the disassembly [V]:
//   +0x00 field0 - first qword of the 16-byte payload slot (overwritten by movups stores)
//   +0x08 control - refcounted control-block pointer (loaded, released, overwritten)
//   +0x10 state - byte state machine (values 0..4 are tabled; anything else -> 0xFF)
struct Item {
    std::uintptr_t field0;  // +0x00
    void* control;          // +0x08
    std::uint8_t state;     // +0x10
};
static_assert(offsetof(Item, field0) == 0x00, "sub_bcac8b0: Item::field0 is at +0x00");
static_assert(offsetof(Item, control) == 0x08, "sub_bcac8b0: Item::control is at +0x08");
static_assert(offsetof(Item, state) == 0x10, "sub_bcac8b0: Item::state is at +0x10");
static_assert(sizeof(Item) == 0x18, "sub_bcac8b0: Item is 0x18 bytes");

// Layout of the refcounted control block reached through Item::control:
//   +0x08 strong refcount (lock inc/dec; when it hits 0 -> sub_eea6040)
//   +0x0C weak  refcount (lock inc/dec; when it hits 0 -> sub_eea6040)
struct ControlBlock {
    std::uintptr_t vtable;   // +0x00 (only dead loads in the disassembly)
    std::int32_t strong;     // +0x08
    std::int32_t weak;       // +0x0C
};
static_assert(offsetof(ControlBlock, strong) == 0x08, "sub_bcac8b0: ControlBlock::strong is at +0x08");
static_assert(offsetof(ControlBlock, weak) == 0x0C, "sub_bcac8b0: ControlBlock::weak is at +0x0C");
static_assert(sizeof(ControlBlock) == 0x10, "sub_bcac8b0: ControlBlock is 0x10 bytes");

// sub 0xbcac8b0: Item group visitor. x64 Microsoft ABI:
//   rcx = idx   (std::uint32_t; jump-table index into 6 entries at data 0xF44B728,
//                no bounds check - matches the bare `jmp rcx` at entry)
//   rdx = slot  (void**; the visited object pointer is *slot)
//   r8  = src   (std::uintptr_t const[2]; payload fields src[0] and src[1])
// return: void (eax holds the last state-byte load; the sole caller ignores it) [V 0xbcac5f7]
void sub_bcac8b0(std::uint32_t idx, void** slot, std::uintptr_t const* src);

// Footprint of sub 0xbcac8b0: the item object reached through *slot, payload plus state
// byte (+0x00..+0x10). Control-block refcount writes go through a dynamically loaded
// pointer and are not part of the static footprint.
std::uint32_t sub_bcac8b0_footprint(void** slot, std::uintptr_t const* src);

} // namespace native
