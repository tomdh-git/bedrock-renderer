#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_eec6ec0 (RVA 0xeec6ec0): lift-classified callee
//   (docs/data/native_boundary.tsv class lift; docs/data/native_functions.tsv size 0x6,
//    root D0, added 0xeec6ec0).
// It is the IAT thunk `jmp qword ptr [0xF9A8A98]`, i.e. memcpy. Forward-declared here with its
// exact x64 ABI signature; defined by its own lift unit, called like any lifted function.
// Called as (rcx = dst, rdx = src, r8 = count); sub_0xbc964d0 ignores its return value.
void* sub_eec6ec0(void* dst, const void* src, size_t count);

} // namespace native

namespace native::bgfx {

// Layout of the object built by sub_0xbc964d0 (this/self in rcx, returned in rax),
// reverse-engineered from the disassembly of [0xbc964d0, 0xbc966b0), Minecraft Windows 1.26.62.01.
// Only offsets the function touches are declared; the rest is padding.
struct sub_bc964d0_state {
    void* field_0x00;               // +0x00  VA of rodata slot data_f44b350 (stored verbatim)
    uint8_t pad_0x08[0x18];         // +0x08..0x27  zeroed
    uint64_t field_0x28;            // +0x28  = 0xF
    uint64_t field_0x30;            // +0x30  = 0
    void* field_0x38;               // +0x38  &field_0x38 passed as vtable-call argument
    uint8_t pad_0x40[0x30];         // +0x40..0x6F
    void* field_0x70;               // +0x70  refcounted object moved in from a1+0x38
    void* field_0x78;               // +0x78  pointer moved in from a3/r9+0x00
    void* field_0x80;               // +0x80  qword moved in from a3/r9+0x08
    void* field_0x88;               // +0x88  string data pointer (inline buffer or heap alloc)
    uint8_t pad_0x90[8];            // +0x90  zeroed together with field_0x88
    uint64_t field_0x98;            // +0x98  string size
    uint64_t field_0xA0;            // +0xA0  string capacity
};                                  // sizeof == 0xA8

// The rdx/argument-2 object; only field_0x38 (a refcounted object pointer) is touched: moved
// into self+0x70 (with an addref when it references itself), then cleared.
struct sub_bc964d0_source {
    uint8_t pad_0x00[0x38];
    void* field_0x38;
};                                  // sizeof == 0x40

// The r8/a2 and r9/a3 string-like objects: { pointer at +0x00, size at +0x08 }.
// a3 is moved into self+0x78/+0x80 and then zeroed; a2 is copied into the string buffer
// at self+0x88 (inline when its signed size field is < 0x10, heap-allocated otherwise;
// bit 63 of the size field means "inline source string" -> length error).
struct sub_bc964d0_str {
    void* field_0x00;
    uint64_t field_0x08;
};                                  // sizeof == 0x10

static_assert(offsetof(sub_bc964d0_state, field_0x00) == 0x00, "sub_0xbc964d0 writes self+0x00");
static_assert(offsetof(sub_bc964d0_state, field_0x28) == 0x28, "sub_0xbc964d0 writes self+0x28");
static_assert(offsetof(sub_bc964d0_state, field_0x30) == 0x30, "sub_0xbc964d0 writes self+0x30");
static_assert(offsetof(sub_bc964d0_state, field_0x38) == 0x38, "sub_0xbc964d0 takes &self+0x38");
static_assert(offsetof(sub_bc964d0_state, field_0x70) == 0x70, "sub_0xbc964d0 writes self+0x70");
static_assert(offsetof(sub_bc964d0_state, field_0x78) == 0x78, "sub_0xbc964d0 writes self+0x78");
static_assert(offsetof(sub_bc964d0_state, field_0x80) == 0x80, "sub_0xbc964d0 writes self+0x80");
static_assert(offsetof(sub_bc964d0_state, field_0x88) == 0x88, "sub_0xbc964d0 writes self+0x88");
static_assert(offsetof(sub_bc964d0_state, field_0x98) == 0x98, "sub_0xbc964d0 writes self+0x98");
static_assert(offsetof(sub_bc964d0_state, field_0xA0) == 0xA0, "sub_0xbc964d0 writes self+0xA0");
static_assert(sizeof(sub_bc964d0_state) == 0xA8, "sub_0xbc964d0 object size");
static_assert(offsetof(sub_bc964d0_source, field_0x38) == 0x38, "sub_0xbc964d0 reads/writes a1+0x38");
static_assert(sizeof(sub_bc964d0_source) == 0x40, "a1 object size");
static_assert(offsetof(sub_bc964d0_str, field_0x00) == 0x00, "a2/a3 pointer at +0x00");
static_assert(offsetof(sub_bc964d0_str, field_0x08) == 0x08, "a2/a3 size at +0x08");
static_assert(sizeof(sub_bc964d0_str) == 0x10, "a2/a3 object size");

// sub_0xbc964d0(self = rcx, a1 = rdx, a2 = r8, a3 = r9) -> self (rax), Minecraft 1.26.62.01.
sub_bc964d0_state* sub_bc964d0(sub_bc964d0_state* self, sub_bc964d0_source* a1,
                               sub_bc964d0_str* a2, sub_bc964d0_str* a3);

} // namespace native::bgfx
