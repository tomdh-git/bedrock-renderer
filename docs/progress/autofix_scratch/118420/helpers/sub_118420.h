#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/RewriteRegistry.h"
#include "client/features/render/native/RewriteVerify.h"
#include "sdk/SigManager.h"
#include "sub_e935700.h"

// sub_118420 (0x118420, size 0x53, 1.26.62.01): recursive child/sibling walk over

// a node list headed at argument 3 (R8). Layout recovered from the disassembly

// of 0x118420; every field below is only READ by the function [V]:

//   +0x00  void* next        R  mov r14,[rbx]                    (0x11844f)

//   +0x10  void* child       R  mov r8,[rbx+0x10]                (0x118440)

//   +0x19  u8    flag        R  cmp byte ptr [r8+0x19],0 ; cmp byte ptr [r14+0x19],0

//                                                               (0x118429, 0x11845f)

// The function performs no writes of its own; it releases each node via

// native::sub_e935700 (lift set, declared in sub_e935700.h).

struct sub_118420_node {
    void* next;                    // +0x00 [R]

    std::uint8_t pad_0x08[0x10 - 0x08];
    void* child;                   // +0x10 [R]

    std::uint8_t pad_0x18[0x19 - 0x18];
    std::uint8_t flag;             // +0x19 [R]

};

struct sub_118420Layout {
    static_assert(offsetof(sub_118420_node, next) == 0x00, "sub_118420_node: next at +0x00");
    static_assert(offsetof(sub_118420_node, child) == 0x10, "sub_118420_node: child at +0x10");
    static_assert(offsetof(sub_118420_node, flag) == 0x19, "sub_118420_node: flag at +0x19");
    static_assert(sizeof(void*) == 8, "sub_118420: x64 pointer-sized arguments (Microsoft x64 ABI)");
};

namespace native {

// sub_118420(void* a1, void* a2, void* a3, void* a4) -> void

//   x64 Microsoft ABI: a1 in RCX, a2 in RDX, a3 in R8, a4 in R9; rax is never

//   written in [0x118420, 0x118473), so the return type is void [V].

//   a3 is the list head (dereferenced at +0x00/+0x10/+0x19). Pointee types of

//   a1..a4 are not recoverable from this function alone [I].

void sub_118420(void* a1, void* a2, void* a3, void* a4);

} // namespace native

