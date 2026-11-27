#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layouts for sub_56bbb60, reversed from the disassembly of
// [0x56bbb60, 0x56bbc7d), Minecraft Windows 1.26.62.01. Every offset, width and
// signedness below comes from the instruction operands; the field names describe the
// role proven by the reads and writes. Structs are packed so each field sits at its
// observed offset; sizeof is a lower bound because the real object may have padding.

// a0 (RCX) points at a slot whose qword at +0x00 is the target object pointer.
#pragma pack(push, 1)
struct sub_56bbb60_rcx {
    void* selfPtr;               // +0x00 target object pointer (R 0x56bbb69, 0x56bbb8d, 0x56bbbba)
    std::uint8_t pad0x08[0x8];   // +0x08..+0x0f padding
    std::uint16_t f10;           // +0x10 u16 layout slot (the u16 read at 0x56bbc70 is through rbx, not this base)
};
#pragma pack(pop)

// a1 (RDX) points at a slot whose qword at +0x00 is the source object pointer. From
// 0x56bbb8d RDX is reused as the target object base; this layout covers the qword pair
// at +0x00/+0x08 and the u16 tag at +0x10 written through that base.
#pragma pack(push, 1)
struct sub_56bbb60_rdx {
    void* f0[2];                 // +0x00 value pointer, +0x08 control-block pointer (R/W 0x56bbb8a, 0x56bbb93, 0x56bbba7, 0x56bbbcb)
    std::uint16_t f10;           // +0x10 tag u16 (W 0x56bbbb6)
};
#pragma pack(pop)

// Control block at source->ctrl / target->ctrl: vtable, two 32-bit counters.
#pragma pack(push, 1)
struct sub_56bbb60_r8 {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding
    std::uint32_t f8;            // +0x08 reference counter (lock inc/dec)
};
#pragma pack(pop)

// Source object pointer (RAX) and target object pointer after reload (RAX = *a0).
#pragma pack(push, 1)
struct sub_56bbb60_rax {
    void* value;                 // +0x00 value pointer (R 0x56bbba4, 0x56bbbf3, 0x56bbc4e)
    void* ctrl;                  // +0x08 control-block pointer (R 0x56bbb96, 0x56bbbaa, 0x56bbbd7, 0x56bbc18, 0x56bbc63)
    std::uint16_t tag;           // +0x10 tag u16 (R 0x56bbbb2)
    std::uint8_t pad0x12[0x6];   // +0x12..+0x17 padding
    std::uint8_t state;          // +0x18 state byte (W 0x56bbbbd)
};
#pragma pack(pop)

// Source object pointer (RBX) dereferenced in the case-2 path.
#pragma pack(push, 1)
struct sub_56bbb60_rbx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding
    void* ctrl;                  // +0x08 control-block pointer (R 0x56bbbce, 0x56bbbdb)
};
#pragma pack(pop)

// Target object (RDI = *a0): value, control block, tag, state.
#pragma pack(push, 1)
struct sub_56bbb60_rdi {
    void* value;                 // +0x00 value pointer (W 0x56bbc35)
    void* ctrl;                  // +0x08 control-block pointer (R/W 0x56bbbe1, 0x56bbc38, 0x56bbc3c)
    std::uint16_t tag;           // +0x10 tag u16 (W 0x56bbc74)
    std::uint8_t pad0x12[0x6];   // +0x12..+0x17 padding
    std::uint8_t state;          // +0x18 state byte (R/W 0x56bbb6c, 0x56bbb86)
};
#pragma pack(pop)

// Control block (RSI): vtable pointer and two 32-bit counters.
#pragma pack(push, 1)
struct sub_56bbb60_rsi {
    void* vfptr;                 // +0x00 vtable pointer (R 0x56bbbf0, 0x56bbc15, 0x56bbc4b, 0x56bbc60)
    std::uint32_t refcount;      // +0x08 reference counter (lock dec 0x56bbbea, 0x56bbc45)
    std::uint32_t count0xC;      // +0x0c second counter (lock dec 0x56bbc0b, 0x56bbc5a)
};
#pragma pack(pop)

static_assert(offsetof(sub_56bbb60_rcx, selfPtr) == 0x0, "sub_0x56bbb60 rcx+0x0 field");
static_assert(offsetof(sub_56bbb60_rcx, f10) == 0x10, "sub_0x56bbb60 rcx+0x10 field");
static_assert(sizeof(sub_56bbb60_rcx) >= 0x12, "sub_0x56bbb60 rcx sizeof lower bound");

static_assert(offsetof(sub_56bbb60_rdx, f0) == 0x0, "sub_0x56bbb60 rdx+0x0 field");
static_assert(offsetof(sub_56bbb60_rdx, f10) == 0x10, "sub_0x56bbb60 rdx+0x10 field");
static_assert(sizeof(sub_56bbb60_rdx) >= 0x12, "sub_0x56bbb60 rdx sizeof lower bound");

static_assert(offsetof(sub_56bbb60_r8, f8) == 0x8, "sub_0x56bbb60 r8+0x8 field");
static_assert(sizeof(sub_56bbb60_r8) >= 0xc, "sub_0x56bbb60 r8 sizeof lower bound");

static_assert(offsetof(sub_56bbb60_rax, value) == 0x0, "sub_0x56bbb60 rax+0x0 field");
static_assert(offsetof(sub_56bbb60_rax, ctrl) == 0x8, "sub_0x56bbb60 rax+0x8 field");
static_assert(offsetof(sub_56bbb60_rax, tag) == 0x10, "sub_0x56bbb60 rax+0x10 field");
static_assert(offsetof(sub_56bbb60_rax, state) == 0x18, "sub_0x56bbb60 rax+0x18 field");
static_assert(sizeof(sub_56bbb60_rax) >= 0x19, "sub_0x56bbb60 rax sizeof lower bound");

static_assert(offsetof(sub_56bbb60_rbx, ctrl) == 0x8, "sub_0x56bbb60 rbx+0x8 field");
static_assert(sizeof(sub_56bbb60_rbx) >= 0x10, "sub_0x56bbb60 rbx sizeof lower bound");

static_assert(offsetof(sub_56bbb60_rdi, value) == 0x0, "sub_0x56bbb60 rdi+0x0 field");
static_assert(offsetof(sub_56bbb60_rdi, ctrl) == 0x8, "sub_0x56bbb60 rdi+0x8 field");
static_assert(offsetof(sub_56bbb60_rdi, tag) == 0x10, "sub_0x56bbb60 rdi+0x10 field");
static_assert(offsetof(sub_56bbb60_rdi, state) == 0x18, "sub_0x56bbb60 rdi+0x18 field");
static_assert(sizeof(sub_56bbb60_rdi) >= 0x19, "sub_0x56bbb60 rdi sizeof lower bound");

static_assert(offsetof(sub_56bbb60_rsi, vfptr) == 0x0, "sub_0x56bbb60 rsi+0x0 field");
static_assert(offsetof(sub_56bbb60_rsi, refcount) == 0x8, "sub_0x56bbb60 rsi+0x8 field");
static_assert(offsetof(sub_56bbb60_rsi, count0xC) == 0xc, "sub_0x56bbb60 rsi+0xc field");
static_assert(sizeof(sub_56bbb60_rsi) >= 0x10, "sub_0x56bbb60 rsi sizeof lower bound");

// Layout constant block binding the unit to RVA 0x56bbb60.
struct sub_56bbb60Layout {
    static_assert(sizeof(void*) == 8, "sub_56bbb60 0x56bbb60: x64 pointer-sized fields are 8 bytes");
};
static_assert(sizeof(sub_56bbb60Layout) > 0, "sub_56bbb60 0x56bbb60: layout constant block");

// x64 Microsoft ABI: RCX = a0 (target slot pointer), RDX = a1 (source slot pointer);
// RAX carries the return value. First instructions cited at 0x56bbb60..0x56bbb64.
std::uintptr_t sub_56bbb60(void* a0, void* a1);

} // namespace native::helpers
