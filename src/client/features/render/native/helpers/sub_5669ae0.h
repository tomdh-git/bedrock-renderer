#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_5669ae0, reverse-engineered from the disassembly
// of [0x5669ae0, 0x5669c09), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
//
// The self object (rcx) holds two inline-buffer ranges:
//   range #2: begin +0xB8, end +0xC0, heap cap +0xC8   (processed first)
//   range #1: begin +0x10,  end +0x18,  heap cap +0x20  (processed second)
// Each element is 0x290 bytes and is released by sub_567e430; after each range the
// buffer heap block is freed through sub_e935700 and the begin/end/cap fields are
// zeroed. Field names are the lifter's choice; offsets are fixed by the listing.

// Offset constants for the self object [proven offsets].
struct Sub5669ae0Layout {
    static constexpr std::size_t kOffBegin2 = 0xB8;  // 0x5669aec:R, 0x5669b24:R, 0x5669b61:W
    static constexpr std::size_t kOffEnd2   = 0xC0;  // 0x5669aff:R, 0x5669b61:W
    static constexpr std::size_t kOffCap2   = 0xC8;  // 0x5669b27:R, 0x5669b64:W
    static constexpr std::size_t kOffBegin1 = 0x10;  // 0x5669b6c:R, 0x5669ba4:R, 0x5669bda:W
    static constexpr std::size_t kOffEnd1   = 0x18;  // 0x5669b79:R, 0x5669bda:W
    static constexpr std::size_t kOffCap1   = 0x20;  // 0x5669ba7:R, 0x5669bdd:W
    static constexpr std::size_t kStride    = 0x290; // 0x5669b18, 0x5669b98
    static_assert(sizeof(void*) == 8, "sub_5669ae0: x64 pointers are 8 bytes");
};
static_assert(sizeof(Sub5669ae0Layout) > 0, "sub_5669ae0: layout constant block");

// Struct for base register rcx (the `self` object) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_5669ae0_rcx {
    std::uint8_t pad0x00[0x10];   // +0x00..+0x0f padding (no observed access)
    void* begin1;                 // +0x10: void* R/W  (R/W cited: 0x5669b6c:R, 0x5669ba4:R, 0x5669bda:W)
    void* end1;                   // +0x18: void* R/W  (R/W cited: 0x5669b79:R, 0x5669bda:W)
    void* cap1;                   // +0x20: void* R/W  (R/W cited: 0x5669ba7:R, 0x5669bdd:W)
    std::uint8_t pad0x28[0x90];   // +0x28..+0xb7 padding (no observed access)
    void* begin2;                 // +0xb8: void* R/W  (R/W cited: 0x5669aec:R, 0x5669b24:R, 0x5669b61:W)
    void* end2;                   // +0xc0: void* R/W  (R/W cited: 0x5669aff:R, 0x5669b61:W)
    void* cap2;                   // +0xc8: void* R/W  (R/W cited: 0x5669b27:R, 0x5669b64:W)
};
#pragma pack(pop)

// Struct for base register rbx (dereferenced in this function) [proven base, [open] name/meaning]
// rbx = &self->0xB8 for range #2 and rbx = &self->0x10 for range #1, so its +0x00 field aliases
// the rcx struct's begin field and its +0x10 field aliases the rcx struct's cap field.
#pragma pack(push, 1)
struct sub_5669ae0_rbx {
    void* begin;                  // +0x00: void* R/W  (R/W cited: 0x5669b24:R, 0x5669b61:W, 0x5669ba4:R, 0x5669bda:W)
    std::uint8_t pad0x08[0x8];    // +0x08..+0x0f padding (no observed access)
    std::uint64_t cap;            // +0x10: std::uint64_t W  (R/W cited: 0x5669b64:W, 0x5669bdd:W)
};
#pragma pack(pop)

// (no non-negative-offset fields; base only used for stack/scratch accesses)

// Struct for base register rsp (dereferenced in this function) [proven base, [open] name/meaning]
// The struct is packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size. [open] field meanings.
#pragma pack(push, 1)
struct sub_5669ae0_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t dead20;         // +0x20: std::uint64_t W  (R/W cited: 0x5669bef:W; dead store, never read)
};
#pragma pack(pop)

// sizeof lower bound: the largest observed offset plus its width across all structs.

static_assert(offsetof(sub_5669ae0_rcx, begin1) == 0x10, "sub_0x5669ae0 rcx+0x10 field");
static_assert(offsetof(sub_5669ae0_rcx, end1) == 0x18, "sub_0x5669ae0 rcx+0x18 field");
static_assert(offsetof(sub_5669ae0_rcx, cap1) == 0x20, "sub_0x5669ae0 rcx+0x20 field");
static_assert(offsetof(sub_5669ae0_rcx, begin2) == 0xb8, "sub_0x5669ae0 rcx+0xb8 field");
static_assert(offsetof(sub_5669ae0_rcx, end2) == 0xc0, "sub_0x5669ae0 rcx+0xc0 field");
static_assert(offsetof(sub_5669ae0_rcx, cap2) == 0xc8, "sub_0x5669ae0 rcx+0xc8 field");
static_assert(sizeof(sub_5669ae0_rcx) >= 0xd0, "sub_0x5669ae0 rcx sizeof lower bound");

static_assert(offsetof(sub_5669ae0_rbx, begin) == 0x0, "sub_0x5669ae0 rbx+0x0 field");
static_assert(offsetof(sub_5669ae0_rbx, cap) == 0x10, "sub_0x5669ae0 rbx+0x10 field");
static_assert(sizeof(sub_5669ae0_rbx) >= 0x18, "sub_0x5669ae0 rbx sizeof lower bound");

static_assert(offsetof(sub_5669ae0_rsp, dead20) == 0x20, "sub_0x5669ae0 rsp+0x20 field");
static_assert(sizeof(sub_5669ae0_rsp) >= 0x28, "sub_0x5669ae0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI) [proven from the prologue and the return paths]:
// RCX = a0 (self); no return value is set on any path, so the function returns void.
// 0x5669ae0  push r14; 0x5669ae2  push rsi; 0x5669ae3  push rdi; 0x5669ae4  push rbx
void sub_5669ae0(void* self);

} // namespace native::helpers
