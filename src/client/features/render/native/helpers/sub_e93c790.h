#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_e93c790, reverse-engineered from the disassembly
// of [0xe93c790, 0xe93c891), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/r9 read/write the byte stream,
// rsp holds the callee-saved scratch slot). Field f<hex> is at offset 0x<hex>.
//
// The structs are packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.

// Struct for base register rcx (the source byte stream, read at +0x0 in 32/16/4-byte chunks)
// rcx is only read, never written, by this function.
//   0xe93c7d1  vpcmpeqd ymm0,ymm3,[rcx]      R +0x0 32B
//   0xe93c7e3  vpermd   ymm2,ymm1,[rcx]      R +0x0 32B (index operand)
//   0xe93c830  movdqu   xmm1,[rcx]           R +0x0 16B
//   0xe93c872  mov      eax,[rcx]            R +0x0 4B
#pragma pack(push, 1)
struct sub_e93c790_rcx {
    std::uint8_t f0[32];   // +0x00: byte stream source; read at +0x0 (32B, 16B, 4B)
};
#pragma pack(pop)

// Struct for base register r9 (the destination byte stream, written at +0x0 in 32/16/4-byte chunks)
// r9 starts as a copy of rcx and is advanced as bytes are written; it is the return value.
//   0xe93c7e8  vmovdqu [r9],ymm2             W +0x0 32B
//   0xe93c857  movdqu   [r9],xmm1            W +0x0 16B
//   0xe93c878  mov      [r9],eax             W +0x0 4B
#pragma pack(push, 1)
struct sub_e93c790_r9 {
    std::uint8_t f0[32];   // +0x00: byte stream destination; written at +0x0 (32B, 16B, 4B)
};
#pragma pack(pop)

// Struct for base register rsp (callee-saved scratch slot at +0x8)
//   0xe93c790  mov [rsp+8],rbx               W +0x8 8B   (prologue spill)
//   0xe93c888  mov rbx,[rsp+8]               R +0x8 8B   (epilogue reload)
#pragma pack(push, 1)
struct sub_e93c790_rsp {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    std::uint64_t f8;            // +0x08: callee-saved rbx scratch (R/W cited: 0xe93c790:W, 0xe93c888:R)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_e93c790_rcx, f0) == 0x0, "sub_e93c790: rcx f0 at +0x0");
static_assert(sizeof(sub_e93c790_rcx) >= 0x20, "sub_e93c790: rcx sizeof lower bound (32B reads at +0x0)");

static_assert(offsetof(sub_e93c790_r9, f0) == 0x0, "sub_e93c790: r9 f0 at +0x0");
static_assert(sizeof(sub_e93c790_r9) >= 0x20, "sub_e93c790: r9 sizeof lower bound (32B writes at +0x0)");

static_assert(offsetof(sub_e93c790_rsp, f8) == 0x8, "sub_e93c790: rsp f8 at +0x8");
static_assert(sizeof(sub_e93c790_rsp) >= 0x10, "sub_e93c790: rsp sizeof lower bound");

// Data tables referenced by RIP-relative addressing inside the function (game image RVAs).
// Contents are owned by the exe; this lift reads them at the same RVAs the original does.
//   0xEECAA20 : 8-byte shuffle-control entries, indexed mask*8   (0xe93c7d9)
//   0xEECB220 : 1-byte advance entries, indexed mask             (0xe93c7ed)
//   0xEECA910 : 16-byte shuffle-control entries, indexed mask*16 (0xe93c848)
//   0xEECAA10 : 1-byte advance entries, indexed mask             (0xe93c85c)
//   0x1230A11C: 4-byte flag dword; low byte tested for phases    (0xe93c795)

// Signature (x64 Microsoft ABI):
//   RCX = a0  (source/start pointer, std::uint8_t*)
//   RDX = a1  (end pointer, std::uint8_t*)
//   R8  = fill (32-bit fill value, std::uint32_t; used via R8D zero-extended)
//   Return: RAX = r9 (destination pointer after processing, std::uintptr_t)
// The function is a leaf: it makes no calls and touches no callee-saved registers
// other than spilling/restoring RBX through [rsp+8].
// [open] exact semantic meaning of the data tables and the fill operation; the
// translation below reproduces the instruction-level reads/writes verbatim.
std::uintptr_t sub_e93c790(std::uint8_t* a0, std::uint8_t* a1, std::uint32_t fill);

} // namespace native::helpers
