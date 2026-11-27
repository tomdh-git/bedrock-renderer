#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_56aeff0, reverse-engineered from the disassembly
// of [0x56aeff0, 0x56af0ef), Minecraft Windows 1.26.62.01. Offsets, widths and
// signedness come straight from the instruction operands.
//
// sub_56aeff0 tears down an open-addressed hash table:
//   +0x08  pointer to the array of element pointers
//   +0x10  capacity (power of two; used as `capacity - 1` mask)
//   +0x18  hash bias (set to 0 once the live elements have been released)
//   +0x20  live element count
// Every element is a 0x60-byte record; its byte at +0x58 is the selector that is
// handed to sub_56aea80 (0x56af02c..0x56af037).

struct sub_56aeff0_r8;   // one table element (0x60-byte record)

// Struct for base register rcx (the table object, `self`) [proven offsets]
#pragma pack(push, 1)
struct sub_56aeff0_rcx {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    sub_56aeff0_r8** elements;   // +0x08: element-pointer array base (R at 0x56af01a/0x56af051/0x56af092, W at 0x56af0ca)
    std::uint64_t capacity;      // +0x10: capacity in elements (R at 0x56af01e/0x56af05e/0x56af096, W at 0x56af0ca)
    std::uint64_t hash_bias;     // +0x18: hash bias (R at 0x56af010, W at 0x56af049)
    std::uint64_t count;         // +0x20: live element count (R at 0x56aeffa/0x56af03c, W at 0x56af043)
};
#pragma pack(pop)

// Struct for base register r8: one hash-table element [proven offsets]
#pragma pack(push, 1)
struct sub_56aeff0_r8 {
    std::uint8_t pad0x00[0x58];  // +0x00..+0x57 padding (no observed access)
    std::int8_t dispatch_state;  // +0x58: signed selector byte, read at 0x56af02c and incremented at 0x56af031
    std::uint8_t pad0x59[0x7];   // +0x59..+0x5f tail of the 0x60-byte allocation (size passed to free at 0x56af08b)
};
#pragma pack(pop)

// Struct for base register rax: the multi-byte NOP at 0x56af06c is `nop [rax]`;
// the operand is never dereferenced, so this layout records the operand only.
#pragma pack(push, 1)
struct sub_56aeff0_rax {
    std::uint8_t f0;   // +0x00: NOP operand (no memory access at 0x56af06c)
};
#pragma pack(pop)

// Struct for base register rbx: rbx = self + 8, the elements/capacity pair.
// `mov rax,[rbx]` at 0x56af079 reads the array base; `movups [rbx],xmm0` at
// 0x56af0ca zeroes both words.
#pragma pack(push, 1)
struct sub_56aeff0_rbx {
    sub_56aeff0_r8** elements;   // +0x00: same word as self+0x08 (R at 0x56af079, W at 0x56af0ca)
    std::uint64_t capacity;      // +0x08: same word as self+0x10 (W at 0x56af0ca)
};
#pragma pack(pop)

// Struct for base register rsp (the 0x30-byte local frame) [proven offsets]
#pragma pack(push, 1)
struct sub_56aeff0_rsp {
    std::uint8_t pad0x00[0x20];  // +0x00..+0x1f padding (shadow space)
    std::uint64_t arg5;          // +0x20: 5th outgoing argument slot, zeroed at 0x56af0d5 on the failure path
    std::uint8_t pad0x28[0x7];   // +0x28..+0x2e padding
    std::uint8_t out_byte;       // +0x2f: local byte whose address is passed to sub_56aea80 in rdx (0x56af003, 0x56af034)
};
#pragma pack(pop)

static_assert(offsetof(sub_56aeff0_rcx, elements) == 0x8, "sub_56aeff0: rcx+0x8 field");
static_assert(offsetof(sub_56aeff0_rcx, capacity) == 0x10, "sub_56aeff0: rcx+0x10 field");
static_assert(offsetof(sub_56aeff0_rcx, hash_bias) == 0x18, "sub_56aeff0: rcx+0x18 field");
static_assert(offsetof(sub_56aeff0_rcx, count) == 0x20, "sub_56aeff0: rcx+0x20 field");
static_assert(sizeof(sub_56aeff0_rcx) >= 0x28, "sub_56aeff0: rcx sizeof lower bound");

static_assert(offsetof(sub_56aeff0_r8, dispatch_state) == 0x58, "sub_56aeff0: r8+0x58 field");
static_assert(sizeof(sub_56aeff0_r8) == 0x60, "sub_56aeff0: element record is the 0x60-byte allocation freed at 0x56af08b");

static_assert(offsetof(sub_56aeff0_rax, f0) == 0x0, "sub_56aeff0: rax+0x0 NOP operand");

static_assert(offsetof(sub_56aeff0_rbx, elements) == 0x0, "sub_56aeff0: rbx+0x0 field");
static_assert(offsetof(sub_56aeff0_rbx, capacity) == 0x8, "sub_56aeff0: rbx+0x8 field");
static_assert(sizeof(sub_56aeff0_rbx) >= 0x10, "sub_56aeff0: rbx sizeof lower bound");

static_assert(offsetof(sub_56aeff0_rsp, arg5) == 0x20, "sub_56aeff0: rsp+0x20 field");
static_assert(offsetof(sub_56aeff0_rsp, out_byte) == 0x2f, "sub_56aeff0: rsp+0x2f field");
static_assert(sizeof(sub_56aeff0_rsp) >= 0x30, "sub_56aeff0: rsp sizeof lower bound");

// 0x56aeff0..0x56af0d4: rcx = self, no other incoming register is read; the
// function writes no return value (the value in rax at 0x56af0d4 is the leftover
// of the last call), so it is declared void.
void sub_56aeff0(void* self);

// 0x56af037  call 0x56AEA80. Register assignment at the call site:
//   rcx = element->dispatch_state (sign-extended) + 1   -- jump-table selector
//   rdx = address of the caller's local byte at rsp+0x2F (not read by the callee)
//   r8  = element pointer
// Declared with three parameters so the emitted call places the element in r8.
uintptr_t sub_56aea80(std::uint64_t selector, void* rdx_dead, void* element);

} // namespace native::helpers
