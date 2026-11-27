#pragma once

#include <cstddef>
#include <cstdint>

#include "client/features/render/native/helpers/sub_ebce650.h"

namespace native::bgfx {

// GroupItem: 24-byte (0x18) element of the group array at ctx + 0x1E1DAA8.

// Offsets [V] from sub_bc75b20 disassembly:

struct GroupItem {
    char* name;               // +0x00  char*  read as qword at [ctx + 0x1E1DAA8 + idx*24 + 0]

    std::uint8_t pad08[8];    // +0x08  not read by this function

    std::int32_t value;       // +0x10  int32  read at [ctx + 0x1E1DAA8 + idx*24 + 0x10]

    std::uint16_t flags;      // +0x14  uint16 read at [ctx + 0x1E1DAA8 + idx*24 + 0x14]

    std::uint8_t pad16[2];    // +0x16  padding to 0x18

};

// Layout constants (one per offset the function touches) with static_asserts.

static constexpr std::size_t kOffGroupItemName  = 0x00;
static constexpr std::size_t kOffGroupItemValue = 0x10;
static constexpr std::size_t kOffGroupItemFlags = 0x14;

static_assert(sizeof(GroupItem) == 0x18, "sub_bc75b20: GroupItem is 24 bytes");
static_assert(offsetof(GroupItem, name)  == kOffGroupItemName,  "sub_bc75b20: GroupItem::name at +0x00");
static_assert(offsetof(GroupItem, value) == kOffGroupItemValue, "sub_bc75b20: GroupItem::value at +0x10");
static_assert(offsetof(GroupItem, flags) == kOffGroupItemFlags, "sub_bc75b20: GroupItem::flags at +0x14");

// Ctx offsets used by sub_bc75b20. The Ctx object is far too large to define in full

// (0x1E1DAA8 bytes of padding before the group array), so only the touched offsets

// are declared as named constants. [V: rdis dis of 0xbc75b20]

struct CtxLayout {
    static constexpr std::size_t kLockOffset       = 0x1C0;       // ctx + 0x1C0: lock address passed to sub_ebdbf10 / sub_ebdbf20

    static constexpr std::size_t kGroupItemsOffset = 0x1E1DAA8;   // ctx + 0x1E1DAA8: base of GroupItem array

};
static_assert(CtxLayout::kLockOffset       == 0x1C0,       "sub_bc75b20: ctx lock offset is 0x1C0");
static_assert(CtxLayout::kGroupItemsOffset == 0x1E1DAA8,   "sub_bc75b20: ctx group array offset is 0x1E1DAA8");

// Default empty-string data address (RVA 0xF847A07, materialized by lea rax,[0xF847A07]).

static constexpr std::uintptr_t kEmptyStringRva = 0xF847A07;

// Callee forward declarations (all classified lift in docs/data/native_boundary.tsv):

//   sub_ebce650(char*, int, SrcDesc*, int) -> int   — declared in sub_ebce650.h (included above)

//   sub_ebdbf10(void* lock) -> void                 — 0xebdbf10, tail jump through data slot 0xF9A7B10

//   sub_ebce5e0(const char*, std::int32_t) -> std::int32_t   — 0xebce5e0, bounded string length

//   sub_ebdbf20(void* a0) -> void                   — 0xebdbf20, tail jump through data slot 0xF9A7B28

extern "C" void sub_ebdbf10(void* lock) noexcept;
extern "C" std::int32_t sub_ebce5e0(const char* str, std::int32_t maxlen) noexcept;
extern "C" void sub_ebdbf20(void* a0) noexcept;

// sub_bc75b20(ctx, idx, out) -> void

//   rcx = ctx (void*), rdx = idx (std::uint32_t), r8 = out (char*)

//   Minecraft Windows 1.26.62.01, function [0xbc75b20, 0xbc75bd9), size 0xb9.

void sub_bc75b20(void* ctx, std::uint32_t idx, char* out) noexcept;

} // namespace native::bgfx

