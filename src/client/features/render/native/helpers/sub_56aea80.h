#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_56aea80, reverse-engineered from the disassembly
// of [0x56aea80, 0x56aeb93), Minecraft Windows 1.26.62.01.
// One struct per base register that is dereferenced. Field f<hex> is at offset 0x<hex>.
// The struct is packed so every declared field sits exactly at its observed offset;
// sizeof is a lower bound (the real object may have compiler-inserted padding).

// Struct for base register r8 (dereferenced in this function).
#pragma pack(push, 1)
struct sub_56aea80_r8 {
    void* f0;   // +0x00: void* R  (vtable-call slot 0, slot 1 via [0xF99FFA0])
    std::uint64_t f8;   // +0x08: refcount (R/RW via lock dec)
    std::uint8_t pad0x10[0x8];   // +0x10..+0x17 padding
    std::uint64_t f18;   // +0x18: owned object pointer (R)
    std::uint8_t pad0x20[0x8];   // +0x20..+0x27 padding
    void* f28;   // +0x28: string/buffer base pointer (R/W)
    std::uint8_t pad0x30[0x8];   // +0x30..+0x37 padding
    std::uint64_t f38;   // +0x38: size/cap word (W)
    void* f40;   // +0x40: length word (R/W)
};
#pragma pack(pop)

// Struct for base register rax (dereferenced in this function).
#pragma pack(push, 1)
struct sub_56aea80_rax {
    void* f0;   // +0x00: void* R  (vtable-call slot 0, slot 1 via [0xF99FFA0])
    void* f8;   // +0x08: void* R  (vtable-call slot 1 via [0xF99FFA0])
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function).
#pragma pack(push, 1)
struct sub_56aea80_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding
    std::uint64_t f20;   // +0x20: scratch slot (W)
};
#pragma pack(pop)

static_assert(offsetof(sub_56aea80_r8, f0) == 0x0, "sub_56aea80: r8+0x0 field");
static_assert(offsetof(sub_56aea80_r8, f8) == 0x8, "sub_56aea80: r8+0x8 field");
static_assert(offsetof(sub_56aea80_r8, f18) == 0x18, "sub_56aea80: r8+0x18 field");
static_assert(offsetof(sub_56aea80_r8, f28) == 0x28, "sub_56aea80: r8+0x28 field");
static_assert(offsetof(sub_56aea80_r8, f38) == 0x38, "sub_56aea80: r8+0x38 field");
static_assert(offsetof(sub_56aea80_r8, f40) == 0x40, "sub_56aea80: r8+0x40 field");
static_assert(sizeof(sub_56aea80_r8) >= 0x48, "sub_56aea80: r8 sizeof lower bound");

static_assert(offsetof(sub_56aea80_rax, f0) == 0x0, "sub_56aea80: rax+0x0 field");
static_assert(offsetof(sub_56aea80_rax, f8) == 0x8, "sub_56aea80: rax+0x8 field");
static_assert(sizeof(sub_56aea80_rax) >= 0x10, "sub_56aea80: rax sizeof lower bound");

static_assert(offsetof(sub_56aea80_rsp, f20) == 0x20, "sub_56aea80: rsp+0x20 field");
static_assert(sizeof(sub_56aea80_rsp) >= 0x28, "sub_56aea80: rsp sizeof lower bound");

// Layout constant block for the gate: asserts the function RVA is bound to this unit.
struct sub_56aea80Layout {
    static_assert(sizeof(void*) == 8, "sub_56aea80 0x56aea80: x64 pointer-sized fields are 8 bytes");
};
static_assert(sizeof(sub_56aea80Layout) > 0, "sub_56aea80 0x56aea80: layout constant block");

// The callee sub_e935700 is lift set; its header declares void* sub_e935700(void* a0).
// The slot call at 0x56aeb8c reads data slot 0xF9A8C78 at call time (rule 69).
using fail_handler_fn = void (*)(std::uintptr_t, std::uintptr_t, std::uintptr_t, std::uintptr_t);

uintptr_t sub_56aea80(void* self);

} // namespace native::helpers
