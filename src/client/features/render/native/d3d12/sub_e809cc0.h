#pragma once
#include <cstddef>
#include <cstdint>

namespace native::d3d12 {

// Layout of the two stack objects created and released by sub_e809cc0 (0xe809cc0, size 0xa1, 1.26.62.01).
// Offsets are taken verbatim from the disassembly stores ([V] 0xe809cd2..0xe809d08):
//   +0x00 vptr (vtable address), +0x08 copied 2nd argument, +0x38 back-pointer to the object itself.
// ObjB additionally stores at +0x40 and +0x48. Exact C++ type names are unknown; the layout below is
// asserted statically so any drift from the exe layout fails the build.
struct SlotObjA {
    void* vptr;     // 0x00  vtable address, written 0xF4EE1D0  (0xe809cda..0xe809ce1)
    void* unk08;    // 0x08  copy of the function's 2nd argument (0xe809ce5)
    // 0x10..0x37 not written by this function
    void* self;     // 0x38  back-pointer, written &objA (0xe809ce9..0xe809ced); read at 0xe809d39
};                  // sizeof == 0x40: objB begins 0x40 bytes after objA on the stack

struct SlotObjB {
    void* vptr;     // 0x00  vtable address, written 0xF4EE200 (0xe809cf5..0xe809cfc)
    void* unk08;    // 0x08  copy of the function's 2nd argument (0xe809d00)
    // 0x10..0x37 not written by this function
    void* self;     // 0x38  back-pointer, written &objB (0xe809cf1..0xe809d04); read at 0xe809d15, cleared at 0xe809d31
    void* unk40;    // 0x40  copy of the function's 2nd argument (0xe809d08)
    __int64 state;  // 0x48  written -2 (0xe809cd2)
};                  // sizeof == 0x50: fills the rest of the 0xB0 stack frame

static_assert(sizeof(SlotObjA) == 0x40, "SlotObjA layout must match the disassembly");
static_assert(offsetof(SlotObjA, vptr) == 0x00, "SlotObjA vptr offset");
static_assert(offsetof(SlotObjA, unk08) == 0x08, "SlotObjA unk08 offset");
static_assert(offsetof(SlotObjA, self) == 0x38, "SlotObjA self offset");
static_assert(sizeof(SlotObjB) == 0x50, "SlotObjB layout must match the disassembly");
static_assert(offsetof(SlotObjB, vptr) == 0x00, "SlotObjB vptr offset");
static_assert(offsetof(SlotObjB, unk08) == 0x08, "SlotObjB unk08 offset");
static_assert(offsetof(SlotObjB, self) == 0x38, "SlotObjB self offset");
static_assert(offsetof(SlotObjB, unk40) == 0x40, "SlotObjB unk40 offset");
static_assert(offsetof(SlotObjB, state) == 0x48, "SlotObjB state offset");

// Callee already in the lift set (docs/data/native_functions.tsv X2.e839020): call through its native symbol.
extern "C" void sub_e839020(void* a0, void* a1);

// Exact x64 Microsoft ABI signature of 0xe809cc0: (ctx in rcx, arg2 in rdx), returns void.
// rcx is never spilled to the stack; rdx is reloaded with &objA right before the call to sub_e839020.
extern "C" void sub_e809cc0(void* ctx, void* arg2);

} // namespace native::d3d12
