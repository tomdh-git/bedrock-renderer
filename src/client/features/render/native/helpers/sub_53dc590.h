#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Layouts for sub_53dc590 (0x53dc590..0x53dc69f), Minecraft Windows 1.26.62.01.
// Every offset, width and signedness below is taken from the instruction operands
// in docs/functions/53dc590.md. A citation names the instruction address and the
// access direction (R = read, W = write).

#pragma pack(push, 1)

// Node of the chains rooted at sub_53dc590_Self::head0 / ptr30 / ptr28. The chain
// links are next10 (offset 0x10) and next138 (offset 0x138); link8 at offset 0x08
// is converted to the base of the next node by subtracting 8 when it is nonzero.
struct sub_53dc590_Node {
    void** vtable;                 // +0x00 R 0x53dc5b0 ([rdi] gives the vtable; slot 0 is called); W 0x53dc5f9 (qword 0 through [rdi+0x18])
    void* link8;                   // +0x08 R 0x53dc5e1
    sub_53dc590_Node* next10;      // +0x10 R 0x53dc610
    sub_53dc590_Node* owned18;     // +0x18 R 0x53dc5e5
    std::uint8_t pad0x20[0x118];   // +0x20..+0x137 not touched
    sub_53dc590_Node* next138;     // +0x138 R 0x53dc678
    std::uint8_t flag140;          // +0x140 R 0x53dc67f (compared with 1)
};

// Owner object received in RCX.
struct sub_53dc590_Self {
    sub_53dc590_Node* head0;   // +0x00 R 0x53dc5a8
    std::uint8_t pad0x08[0x10];// +0x08..+0x17 not touched
    sub_53dc590_Node* ptr18;   // +0x18 R 0x53dc63c (second argument of the global release call)
    std::uint8_t pad0x20[0x8]; // +0x20..+0x27 not touched
    sub_53dc590_Node* ptr28;   // +0x28 R 0x53dc633
    sub_53dc590_Node* ptr30;   // +0x30 R 0x53dc602
};

// Object found through global data 0x1233E1A8. Its vtable slot at +0x10 releases
// the node passed as the second argument.
struct sub_53dc590_Global {
    void** vtable;   // +0x00 R 0x53dc5c8, 0x53dc620, 0x53dc640, 0x53dc68f
};

#pragma pack(pop)

static_assert(offsetof(sub_53dc590_Node, vtable) == 0x000, "sub_0x53dc590 node+0x00 field");
static_assert(offsetof(sub_53dc590_Node, link8) == 0x008, "sub_0x53dc590 node+0x08 field");
static_assert(offsetof(sub_53dc590_Node, next10) == 0x010, "sub_0x53dc590 node+0x10 field");
static_assert(offsetof(sub_53dc590_Node, owned18) == 0x018, "sub_0x53dc590 node+0x18 field");
static_assert(offsetof(sub_53dc590_Node, next138) == 0x138, "sub_0x53dc590 node+0x138 field");
static_assert(offsetof(sub_53dc590_Node, flag140) == 0x140, "sub_0x53dc590 node+0x140 field");
static_assert(sizeof(sub_53dc590_Node) >= 0x141, "sub_0x53dc590 node sizeof lower bound");

static_assert(offsetof(sub_53dc590_Self, head0) == 0x00, "sub_0x53dc590 self+0x00 field");
static_assert(offsetof(sub_53dc590_Self, ptr18) == 0x18, "sub_0x53dc590 self+0x18 field");
static_assert(offsetof(sub_53dc590_Self, ptr28) == 0x28, "sub_0x53dc590 self+0x28 field");
static_assert(offsetof(sub_53dc590_Self, ptr30) == 0x30, "sub_0x53dc590 self+0x30 field");
static_assert(sizeof(sub_53dc590_Self) >= 0x38, "sub_0x53dc590 self sizeof lower bound");

static_assert(offsetof(sub_53dc590_Global, vtable) == 0x00, "sub_0x53dc590 global+0x00 field");
static_assert(sizeof(sub_53dc590_Global) >= 0x8, "sub_0x53dc590 global sizeof lower bound");

// x64 Microsoft ABI: RCX = self. The function has no return value; every path
// reaches a bare `ret` without defining RAX (0x53dc662, 0x53dc65a..0x53dc662).
void sub_53dc590(void* self);

} // namespace native::helpers
