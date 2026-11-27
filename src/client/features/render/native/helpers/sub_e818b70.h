#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout for sub_e818b70, reverse-engineered from the disassembly
// of [0xe818b70, 0xe818bbc), Minecraft Windows 1.26.62.01. Offsets and widths
// come straight from the instruction operands:
//   0xe818b9d: cmp byte ptr [rsi+0xC96190],0   (R, std::uint8_t)
// One struct per base register that is dereferenced (rcx here). Field f<hex> is
// at offset 0x<hex>. The struct is packed (#pragma pack(1)) so every declared
// field sits exactly at its observed offset and offsetof() matches it. The real
// object may have compiler-inserted alignment padding, so sizeof is a lower
// bound, not an exact size.

#pragma pack(push, 1)
struct sub_e818b70_rcx {
    std::uint8_t pad0x00[0xc96190];   // +0x00..+0xc9618f padding (no observed access)
    std::uint8_t fc96190;             // +0xc96190: std::uint8_t R  (R/W cited: 0xe818b9d:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_e818b70_rcx, fc96190) == 0xc96190, "sub_e818b70 rcx+0xc96190 field");
static_assert(sizeof(sub_e818b70_rcx) >= 0xc96191, "sub_e818b70 rcx sizeof lower bound");

// Signature (x64 Microsoft ABI), proven from the prologue and operand widths:
//   0xe818b70  push rsi; 0xe818b71  push rdi; 0xe818b72  sub rsp,0x28; 0xe818b76  cmp dx,1
// rcx = self, edx = a2 (std::uint32_t): u16(a2) compared with 1, bits 16..31 of a2
// forwarded as the size argument of sub_e83abb0, full u32(a2) compared with 0x10000000.
// Return value is rax: the 0xe818b90 call result where reached, otherwise the
// entry value of rax (not modeled, like the real register).
uintptr_t sub_e818b70(void* self, std::uint32_t a2);

} // namespace native::helpers
