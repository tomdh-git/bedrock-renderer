#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_1d3b70, reverse-engineered from the disassembly
// of [0x1d3b70, 0x1d3c8a), Minecraft Windows 1.26.62.01. [proven] offsets/widths/signedness
// come straight from the instruction operands; field NAMES and MEANINGS are [open].
// One struct per base register that is dereferenced (rcx/rdx/r8/r9 this/a1/a2 and
// any other register used as a memory base). Field f<hex> is at offset 0x<hex>.
// The structs are packed (#pragma pack(1)) so every declared field sits exactly at its
// observed offset and offsetof() matches it. The real object may have compiler-inserted
// alignment padding, so sizeof is a lower bound, not an exact size.
// Field meanings below are the best-effort reversal derived from how each field is used:

// rcx base: the 'this' pointer passed as the first argument (rcx).
// f18 is the beginning of a managed element range; f20 is one-past-the-end (or the
// end of the range). Elements are 0x10 bytes: element->f0 = vtable pointer,
// element->f8 = strong refcount, element->f0c = weak refcount.
// f00/f10 are the beginning/end of a second managed range (the fallback path when
// f18 is null).
#pragma pack(push, 1)
struct sub_1d3b70_rcx {
    void* f0[2];        // +0x00: void*[2] R/W (range 2 begin/end)
    std::uint64_t f10;  // +0x10: std::uint64_t R/W (range 2 end)
    void* f18;          // +0x18: void* R  (range 1 begin)
    std::uint64_t f20;  // +0x20: std::uint64_t R  (range 1 end)
    std::uint64_t f28;  // +0x28: std::uint64_t R  (range 1 capacity/end fallback)
};
#pragma pack(pop)

// r14 base: &rcx->f18, i.e. the address of the range-1 begin pointer.
// f00 is the begin pointer (R/W); f10 is the end pointer (W).
#pragma pack(push, 1)
struct sub_1d3b70_r14 {
    void* f0[2];        // +0x00: void*[2] R/W (r14 itself points at f18 of rcx)
    std::uint64_t f10;  // +0x10: std::uint64_t W (range 1 end)
};
#pragma pack(pop)

// rax base: vtable pointer + first slot read of an element (f00 = vtable, f08 = slot 1).
#pragma pack(push, 1)
struct sub_1d3b70_rax {
    void* f0;           // +0x00: void* R (vtable)
    std::uint64_t f8;   // +0x08: std::uint64_t R (vtable slot 1)
};
#pragma pack(pop)

// rbx base: an element (0x10 bytes): f00 = vtable, f08 = strong refcount, f0c = weak refcount.
#pragma pack(push, 1)
struct sub_1d3b70_rbx {
    void* f0;           // +0x00: void* R (vtable)
    std::uint32_t f8;   // +0x08: std::uint32_t RW (strong refcount)
    std::uint32_t fc;   // +0x0c: std::uint32_t RW (weak refcount)
};
#pragma pack(pop)

// rdi base: an element pointer (offset 8 is the vtable slot 0 read at 0x1d3ba9).
#pragma pack(push, 1)
struct sub_1d3b70_rdi {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 padding (no observed access)
    void* f8;                    // +0x08: void* R (vtable slot 0)
};
#pragma pack(pop)

// rsp base: the stack frame; only [rsp+0x20] is written (to 0) before the failing call.
#pragma pack(push, 1)
struct sub_1d3b70_rsp {
    std::uint8_t pad0x00[0x20];   // +0x00..+0x1f padding (no observed access)
    std::uint64_t f20;            // +0x20: std::uint64_t W
};
#pragma pack(pop)

static_assert(offsetof(sub_1d3b70_rcx, f0) == 0x0, "sub_0x1d3b70 rcx+0x0 field");
static_assert(offsetof(sub_1d3b70_rcx, f10) == 0x10, "sub_0x1d3b70 rcx+0x10 field");
static_assert(offsetof(sub_1d3b70_rcx, f18) == 0x18, "sub_0x1d3b70 rcx+0x18 field");
static_assert(offsetof(sub_1d3b70_rcx, f20) == 0x20, "sub_0x1d3b70 rcx+0x20 field");
static_assert(offsetof(sub_1d3b70_rcx, f28) == 0x28, "sub_0x1d3b70 rcx+0x28 field");
static_assert(sizeof(sub_1d3b70_rcx) >= 0x30, "sub_0x1d3b70 rcx sizeof lower bound");

static_assert(offsetof(sub_1d3b70_r14, f0) == 0x0, "sub_0x1d3b70 r14+0x0 field");
static_assert(offsetof(sub_1d3b70_r14, f10) == 0x10, "sub_0x1d3b70 r14+0x10 field");
static_assert(sizeof(sub_1d3b70_r14) >= 0x18, "sub_0x1d3b70 r14 sizeof lower bound");

static_assert(offsetof(sub_1d3b70_rax, f0) == 0x0, "sub_0x1d3b70 rax+0x0 field");
static_assert(offsetof(sub_1d3b70_rax, f8) == 0x8, "sub_0x1d3b70 rax+0x8 field");
static_assert(sizeof(sub_1d3b70_rax) >= 0x10, "sub_0x1d3b70 rax sizeof lower bound");

static_assert(offsetof(sub_1d3b70_rbx, f0) == 0x0, "sub_0x1d3b70 rbx+0x0 field");
static_assert(offsetof(sub_1d3b70_rbx, f8) == 0x8, "sub_0x1d3b70 rbx+0x8 field");
static_assert(offsetof(sub_1d3b70_rbx, fc) == 0xc, "sub_0x1d3b70 rbx+0xc field");
static_assert(sizeof(sub_1d3b70_rbx) >= 0x10, "sub_0x1d3b70 rbx sizeof lower bound");

static_assert(offsetof(sub_1d3b70_rdi, f8) == 0x8, "sub_0x1d3b70 rdi+0x8 field");
static_assert(sizeof(sub_1d3b70_rdi) >= 0x10, "sub_0x1d3b70 rdi sizeof lower bound");

static_assert(offsetof(sub_1d3b70_rsp, f20) == 0x20, "sub_0x1d3b70 rsp+0x20 field");
static_assert(sizeof(sub_1d3b70_rsp) >= 0x28, "sub_0x1d3b70 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI). Argument rcx = 'this'. Returns void.
// Callee conventions used inside:
//   native::sub_e935700(void*)               -- rcx = argument, result in RAX (ignored)
//   call [0xF99FFA0](void*)                  -- rcx = element pointer (this-call vtable slot)
//   call [0xF9A8C78](void*, void*, void*, void*)  -- four zeroed args, noreturn (then int3)
void sub_1d3b70(void* self);

} // namespace native::helpers
