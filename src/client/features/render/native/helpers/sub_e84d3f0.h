#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_e84d3f0, reverse-engineered from the disassembly
// of [0xe84d3f0, 0xe84d51f), Minecraft Windows 1.26.62.01.
// [proven] offsets/widths/signedness come straight from the instruction operands.
// Field NAMES and MEANINGS are reverse-engineered.
// One struct per base register that is dereferenced.
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.

// Input entry: each 0x30-byte record in the [start, end) range.
// Dereferenced base: entry pointer (computed as rdi - 0x20 where rdi = entry + 0x20).
//   [entry+0x00..0x0f] 16 bytes read  (movups [rdi-0x20] at 0xe84d449)
//   [entry+0x10..0x1f] 16 bytes read  (movups [rdi-0x10] at 0xe84d44d)
//   [entry+0x20]    char*  read       (via SrcDesc +0x00 at 0xebce665 through sub_ebce650)
//   [entry+0x28]    int32  read       (flag at 0xe84d466 [rdi+8]; maxlen via SrcDesc +0x08)
#pragma pack(push, 1)
struct InputEntry {
    std::uint64_t data0;   // +0x00
    std::uint64_t data1;   // +0x08
    std::uint64_t data2;   // +0x10
    std::uint64_t data3;   // +0x18
    char* src;             // +0x20
    std::int32_t maxlen;   // +0x28
};
#pragma pack(pop)

// Output entry: each 0x30-byte record written by this function.
// Dereferenced base: output entry pointer (r8).
//   [out+0x00..0x0f] 16 bytes written (movups [r8] at 0xe84d456)
//   [out+0x10..0x1f] 16 bytes written (movups [r8+0x10] at 0xe84d451)
//   [out+0x20]    void*  written      (mov [r8+0x20] at 0xe84d45a with r12; at 0xe84d507 with r15)
//   [out+0x28]    int32  written      (mov [r8+0x28] at 0xe84d45e with 0; at 0xe84d4eb with ebx)
#pragma pack(push, 1)
struct OutputEntry {
    std::uint64_t data0;   // +0x00
    std::uint64_t data1;   // +0x08
    std::uint64_t data2;   // +0x10
    std::uint64_t data3;   // +0x18
    void* dst;             // +0x20
    std::int32_t result;   // +0x28
};
#pragma pack(pop)

static_assert(offsetof(InputEntry, data0) == 0x00, "sub_0xe84d3f0 input+0x0 field");
static_assert(offsetof(InputEntry, data1) == 0x08, "sub_0xe84d3f0 input+0x8 field");
static_assert(offsetof(InputEntry, data2) == 0x10, "sub_0xe84d3f0 input+0x10 field");
static_assert(offsetof(InputEntry, data3) == 0x18, "sub_0xe84d3f0 input+0x18 field");
static_assert(offsetof(InputEntry, src) == 0x20, "sub_0xe84d3f0 input+0x20 field");
static_assert(offsetof(InputEntry, maxlen) == 0x28, "sub_0xe84d3f0 input+0x28 field");
static_assert(sizeof(InputEntry) >= 0x2c, "sub_0xe84d3f0 input sizeof lower bound");

static_assert(offsetof(OutputEntry, data0) == 0x00, "sub_0xe84d3f0 output+0x0 field");
static_assert(offsetof(OutputEntry, data1) == 0x08, "sub_0xe84d3f0 output+0x8 field");
static_assert(offsetof(OutputEntry, data2) == 0x10, "sub_0xe84d3f0 output+0x10 field");
static_assert(offsetof(OutputEntry, data3) == 0x18, "sub_0xe84d3f0 output+0x18 field");
static_assert(offsetof(OutputEntry, dst) == 0x20, "sub_0xe84d3f0 output+0x20 field");
static_assert(offsetof(OutputEntry, result) == 0x28, "sub_0xe84d3f0 output+0x28 field");
static_assert(sizeof(OutputEntry) >= 0x2c, "sub_0xe84d3f0 output sizeof lower bound");

// Callee sub_ebce610 (0xebce610): not in the lift set, called as a native boundary.
// Observed at call site 0xe84d478: rcx=input_entry+0x20, rdx=0x7FFFFFFF, return eax->ebx.
extern "C" int sub_ebce610(void* entry, int maxlen) noexcept;

// Callee sub_eea6040 (0xF99FFA0 global = sub_eea6040): called via indirect call r10 at 0xe84d4c8.
// Observed arguments: rcx=g_12ADF800, rdx=0 or out->dst, r8=(long long)(int)(ebx+1), r9=0,
// stack[0x20]=0, stack[0x28]=0. Return rax->r15 (void*).
extern "C" void* sub_eea6040(void* a1, void* a2, long long a3, int a4, long long a5, int a6) noexcept;

// Signature (x64 Microsoft ABI):
//   rcx = void* start  input range start
//   rdx = void* end    input range end (exclusive; entries are 0x30 bytes)
//   r8  = void* output output base pointer
//   r9  = void* unused saved at [rbp-0x18] but never read
// Return: void (eax is not explicitly set before ret)
void sub_e84d3f0(void* start, void* end, void* output, void* unused) noexcept;

} // namespace native::helpers
