#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_114360, reverse-engineered from the disassembly
// of [0x114360, 0x114475), Minecraft Windows 1.26.62.01. Offsets, widths and
// signedness come from the instruction operands; field names follow the role the
// code proves. The records being ordered are 0x20 bytes wide: 0x11443b and
// 0x11443f step both range ends by 0x20, and callee 0x114480 reads the record
// length at +0x10 and the capacity at +0x18 (MSVC std::string layout).

// Base register rcx (and rdx) on entry address the 0x20-byte records. This
// function only forwards those pointers (0x11436c mov rdi,rcx; 0x11438c mov rcx,rdi;
// 0x1143d6 mov rdx,rdi) and never dereferences them itself; the struct pins the
// record's first byte at offset 0.
#pragma pack(push, 1)
struct sub_114360_rcx {
    std::uint8_t f0;   // +0x00: first byte of a 0x20-byte record (forwarded, not dereferenced here)
};
#pragma pack(pop)

// Stack slots of this frame. +0x20/+0x28 hold the two range ends produced by
// sub_114910 (0x11439f lea r14,[rsp+0x20] passes their address); +0x30 holds the
// stack cookie value __security_cookie ^ rsp.
#pragma pack(push, 1)
struct sub_114360_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f saved registers and shadow space (no direct access)
    std::uint8_t* pivot_first;    // +0x20: 0x1143bb R, 0x1143ee R; written by sub_114910 via r14
    std::uint8_t* pivot_second;   // +0x28: 0x1143f3 R, 0x114414 R; written by sub_114910 via r14
    std::uintptr_t cookie;        // +0x30: 0x114379 W, 0x114449 R, 0x114467 R
};
#pragma pack(pop)

static_assert(offsetof(sub_114360_rcx, f0) == 0x0, "sub_0x114360 rcx+0x0 field");
static_assert(sizeof(sub_114360_rcx) >= 0x1, "sub_0x114360 rcx sizeof lower bound");

static_assert(offsetof(sub_114360_rsp, pivot_first) == 0x20, "sub_0x114360 rsp+0x20 field");
static_assert(offsetof(sub_114360_rsp, pivot_second) == 0x28, "sub_0x114360 rsp+0x28 field");
static_assert(offsetof(sub_114360_rsp, cookie) == 0x30, "sub_0x114360 rsp+0x30 field");
static_assert(sizeof(sub_114360_rsp) >= 0x38, "sub_0x114360 rsp sizeof lower bound");

// Stack cookie global read at 0x11436f and 0x114451 (absolute [0x1230A0C0]).
extern "C" std::uintptr_t __security_cookie;

// Callees outside the lift set, declared with the ABI their call sites in
// [0x114360, 0x114475) require (all three arguments of 0x114910 are live).
void sub_114480(std::uint8_t* first, std::uint8_t* last);                             // 0x114480: orders a range of at most 32 records
void sub_1147e0(std::uint8_t* first, std::uint8_t* last);                             // 0x1147e0: heap construction over the range
void sub_114910(std::uint8_t** pivot_pair, std::uint8_t* first, std::uint8_t* last);  // 0x114910: partition, writes both half ends
void sub_1152e0(std::uint8_t* first, std::uint8_t* last);                             // 0x1152e0: one heap-pop step

// x64 Microsoft ABI: rcx = first record, rdx = one past the last record,
// r8 = remaining depth budget (signed, 64-bit). rax on both exits holds the
// stack cookie value (cookie ^ rsp), which is what the epilogue leaves behind.
std::uintptr_t sub_114360(std::uint8_t* first, std::uint8_t* last, std::intptr_t ideal);

} // namespace native::helpers
