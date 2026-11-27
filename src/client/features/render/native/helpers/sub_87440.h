#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_87440 (0x87440, size 0xcf, 1.26.62.01): release a node tree.
// See sub_87440.cpp for the reversed source (complete).
//
// Argument RCX = release context pointer. Layout observed in the disassembly:
//   +0x28 child_begin (void*)   R   // [rcx+0x28]
//   +0x30 child_end   (void*)   R   // [rcx+0x30]
//   +0x38 limit       (void*)   R   // [rcx+0x38]
//   +0x40 flag        (uint8)   R   // [rcx+0x40], non-zero => early return
// Children are 0x40-byte nodes released recursively via sub_9c590.
// The function tails to sub_9c650(a0 + 0x10) on every non-failure exit.
//
// Lift-set callees (forward-declared; linked through their own LIFT_FN):
void* sub_9c590(void* slot, void* node);
void* sub_e935700(void* a0);
void* sub_9c650(void* a0);

struct ReleaseContext {
    char pad00[0x28];
    void* child_begin;   // +0x28 child list begin pointer (R)
    void* child_end;     // +0x30 child list end   pointer (R)
    void* limit;         // +0x38 allocation limit pointer (R)
    uint8_t flag;        // +0x40 release-guard byte (R)
};                       // sizeof >= 0x41

struct sub_87440Layout {
    static_assert(offsetof(ReleaseContext, child_begin) == 0x28, "sub_87440: child_begin offset");
    static_assert(offsetof(ReleaseContext, child_end) == 0x30, "sub_87440: child_end offset");
    static_assert(offsetof(ReleaseContext, limit) == 0x38, "sub_87440: limit offset");
    static_assert(offsetof(ReleaseContext, flag) == 0x40, "sub_87440: flag offset");
    static_assert(sizeof(ReleaseContext) >= 0x41, "sub_87440: context size at least 0x41");
    static_assert(sizeof(void*) == 8, "sub_87440: x64 pointers");
};

// sub_87440: exact x64 Microsoft ABI signature of the original.
// RCX = release context pointer. Return value: the tail call to sub_9c650
// passes RAX through, so the return type is void*.
void* sub_87440(void* a0);

} // namespace native
