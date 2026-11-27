#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_9c650, reverse-engineered from the disassembly
// of [0x9c650, 0x9c743), Minecraft Windows 1.26.62.01. [proven] offsets/widths
// come straight from the instruction operands; field NAMES and MEANINGS are
// the lifter's decision.
// One struct per base register that is dereferenced (rcx, rdi, rsp). The struct
// is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have
// compiler-inserted alignment padding, so sizeof is a lower bound, not an exact
// size.

// Struct for base register rcx (dereferenced in this function) [proven base]
// rcx points to a release context: block pointer, end pointer, and a size field.
//   +0x0 block (void*)   R   // 0x9c657:R, 0x9c6e0:R
//   +0x8 end   (void*)   R   // 0x9c666:R
//   +0x10 cap  (u64)     R/W // 0x9c6e3:R, 0x9c719:W
#pragma pack(push, 1)
struct sub_9c650_rcx {
    void* block;      // +0x0: block pointer (R)
    void* end;        // +0x8: end pointer   (R)
    std::uint64_t cap;// +0x10: size field   (R/W)
};
#pragma pack(pop)

// Struct for base register rdi (dereferenced in this function) [proven base]
// rdi walks a 0x58-byte array of sub-block headers from block to end.
//   +0x20 ptr  (void*)   R/W // 0x9c695:W, 0x9c6b2:R
//   +0x30 field(u64)     W   // 0x9c685:W
//   +0x38 size (u64)     R/W // 0x9c68d:W, 0x9c6a8:R
//   +0x50 flag (u8)      R   // 0x9c6a2:R
#pragma pack(push, 1)
struct sub_9c650_rdi {
    std::uint8_t pad0x00[0x20];
    void* ptr;       // +0x20: child slot pointer (R/W)
    std::uint8_t pad0x28[0x8];
    std::uint64_t field30; // +0x30: cleared to 0 (W)
    std::uint64_t size;    // +0x38: block size/cap  (R/W)
    std::uint8_t pad0x40[0x10];
    std::uint8_t flag;     // +0x50: ==1 selects release path (R)
};
#pragma pack(pop)

// Struct for base register rsp (dereferenced in this function) [proven base]
//   +0x20 home slot (u64) W  // 0x9c729:W (dead store before the fail call)
#pragma pack(push, 1)
struct sub_9c650_rsp {
    std::uint8_t pad0x00[0x20];
    std::uint64_t home20; // +0x20: home slot cleared on the fail path (W)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_9c650_rcx, block) == 0x0, "sub_0x9c650 rcx+0x0 block field");
static_assert(offsetof(sub_9c650_rcx, end) == 0x8, "sub_0x9c650 rcx+0x8 end field");
static_assert(offsetof(sub_9c650_rcx, cap) == 0x10, "sub_0x9c650 rcx+0x10 cap field");
static_assert(sizeof(sub_9c650_rcx) >= 0x18, "sub_0x9c650 rcx sizeof lower bound");

static_assert(offsetof(sub_9c650_rdi, ptr) == 0x20, "sub_0x9c650 rdi+0x20 ptr field");
static_assert(offsetof(sub_9c650_rdi, field30) == 0x30, "sub_0x9c650 rdi+0x30 field30 field");
static_assert(offsetof(sub_9c650_rdi, size) == 0x38, "sub_0x9c650 rdi+0x38 size field");
static_assert(offsetof(sub_9c650_rdi, flag) == 0x50, "sub_0x9c650 rdi+0x50 flag field");
static_assert(sizeof(sub_9c650_rdi) >= 0x51, "sub_0x9c650 rdi sizeof lower bound");

static_assert(offsetof(sub_9c650_rsp, home20) == 0x20, "sub_0x9c650 rsp+0x20 home20 field");
static_assert(sizeof(sub_9c650_rsp) >= 0x28, "sub_0x9c650 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI). RCX = release context pointer; return value is
// the result of sub_e935700 forwarded in RAX (same pointer-sized return).
// 0x9c650  push rsi; 0x9c651  push rdi; 0x9c652  push rbx; 0x9c653  sub rsp,0x30
void* sub_9c650(void* a0);

} // namespace native::helpers
