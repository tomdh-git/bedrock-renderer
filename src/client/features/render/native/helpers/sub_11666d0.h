#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Typed state layout(s) for sub_11666d0, reverse-engineered from the disassembly
// of [0x11666d0, 0x11667e5). [proven] offsets/widths come straight from the
// instruction operands; field NAMES and MEANINGS are reverse-engineered.
// One struct per base register that is dereferenced. The structs are packed so
// every declared field sits exactly at its observed offset; sizeof is a lower
// bound because the real object may have compiler-inserted alignment padding.

// Base register rcx (the `this`/self pointer, dereferenced in this function).
#pragma pack(push, 1)
struct sub_11666d0_rcx {
    void* f0_vtable;                // +0x00: void*   vtable pointer
    std::uint8_t pad0x08[0x38];     // +0x08..0x3f padding (no observed access)
    void* f40_listHead;             // +0x40: void*   list head; sentinel storage is &f40_listHead
    std::uint8_t pad0x48[0x8];      // +0x48..0x4f padding (no observed access)
    std::uint8_t f50_mutex;         // +0x50: start of the _Mtx mutex object
    std::uint8_t pad0x51[0x4b];     // +0x51..0x9b remainder of the mutex object (no observed access)
    std::uint32_t f9c_state;        // +0x9c: std::uint32_t
};
#pragma pack(pop)

// Base register rbx (a node of the main list, dereferenced in this function).
#pragma pack(push, 1)
struct sub_11666d0_rbx {
    void* f0_prev;                  // +0x00: void*   doubly-linked prev
    void* f8_next;                  // +0x08: void*   doubly-linked next
    std::uint8_t pad0x10[0x8];      // +0x10..0x17 padding (no observed access)
    void* f18_subListHead;          // +0x18: void*   sub-list head
    void* f20_subListEnd;           // +0x20: void*   sub-list end
    std::uint64_t f28;              // +0x28: std::uint64_t (cleared to 0)
    std::uint8_t f30_flag;          // +0x30: std::uint8_t
};
#pragma pack(pop)

// Base register r14 (a sub-list entry, dereferenced in this function).
#pragma pack(push, 1)
struct sub_11666d0_r14 {
    std::uint8_t pad0x00[0x8];      // +0x00..0x07 padding (no observed access)
    void* f8_object;                // +0x08: void*   refcounted object
};
#pragma pack(pop)

// Base register rax (used as &node+0x18 to clear the sub-list head/end/extra).
#pragma pack(push, 1)
struct sub_11666d0_rax {
    std::uint64_t f0_headEnd[2];    // +0x00: std::uint64_t[2]  (f18, f20 of the node)
    std::uint64_t f10_extra;        // +0x10: std::uint64_t     (f28 of the node)
};
#pragma pack(pop)

// Base register rsp (stack slot saving xmm6).
#pragma pack(push, 1)
struct sub_11666d0_rsp {
    std::uint8_t pad0x00[0x20];     // +0x00..0x1f padding (no observed access)
    std::uint8_t f20;               // +0x20: std::uint8_t
};
#pragma pack(pop)

static_assert(offsetof(sub_11666d0_rcx, f0_vtable) == 0x0, "sub_0x11666d0 rcx+0x0 field");
static_assert(offsetof(sub_11666d0_rcx, f40_listHead) == 0x40, "sub_0x11666d0 rcx+0x40 field");
static_assert(offsetof(sub_11666d0_rcx, f50_mutex) == 0x50, "sub_0x11666d0 rcx+0x50 field");
static_assert(offsetof(sub_11666d0_rcx, f9c_state) == 0x9c, "sub_0x11666d0 rcx+0x9c field");
static_assert(sizeof(sub_11666d0_rcx) >= 0xa0, "sub_0x11666d0 rcx sizeof lower bound");

static_assert(offsetof(sub_11666d0_rbx, f0_prev) == 0x0, "sub_0x11666d0 rbx+0x0 field");
static_assert(offsetof(sub_11666d0_rbx, f8_next) == 0x8, "sub_0x11666d0 rbx+0x8 field");
static_assert(offsetof(sub_11666d0_rbx, f18_subListHead) == 0x18, "sub_0x11666d0 rbx+0x18 field");
static_assert(offsetof(sub_11666d0_rbx, f20_subListEnd) == 0x20, "sub_0x11666d0 rbx+0x20 field");
static_assert(offsetof(sub_11666d0_rbx, f28) == 0x28, "sub_0x11666d0 rbx+0x28 field");
static_assert(offsetof(sub_11666d0_rbx, f30_flag) == 0x30, "sub_0x11666d0 rbx+0x30 field");
static_assert(sizeof(sub_11666d0_rbx) >= 0x31, "sub_0x11666d0 rbx sizeof lower bound");

static_assert(offsetof(sub_11666d0_r14, f8_object) == 0x8, "sub_0x11666d0 r14+0x8 field");
static_assert(sizeof(sub_11666d0_r14) >= 0x10, "sub_0x11666d0 r14 sizeof lower bound");

static_assert(offsetof(sub_11666d0_rax, f0_headEnd) == 0x0, "sub_0x11666d0 rax+0x0 field");
static_assert(offsetof(sub_11666d0_rax, f10_extra) == 0x10, "sub_0x11666d0 rax+0x10 field");
static_assert(sizeof(sub_11666d0_rax) >= 0x18, "sub_0x11666d0 rax sizeof lower bound");

static_assert(offsetof(sub_11666d0_rsp, f20) == 0x20, "sub_0x11666d0 rsp+0x20 field");
static_assert(sizeof(sub_11666d0_rsp) >= 0x21, "sub_0x11666d0 rsp sizeof lower bound");

// Signature (x64 Microsoft ABI). The function never returns a value: its normal
// exit is a tail jump to sub_eec5a10 (_Mtx_unlock, void) and its error exits
// throw via sub_eec5a00 (std::_Throw_Cpp_error, noreturn).
void sub_11666d0(void* self);

} // namespace native::helpers
