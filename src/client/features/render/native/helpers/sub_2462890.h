#pragma once
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_2462890 (0x2462890, size 0xc5, 1.26.62.01).
//
// The argument `a0` (an object pointer) arrives in RCX; the result leaves in RAX.
// object+0x00 is the vtable pointer:
//   vtable+0x00: head of a node list (void*);
//   vtable+0x08: pointer to a state qword that this function writes as 0.
// Each node is { next@0x00, start@0x18, end@0x28 } (all void*, offsets [V] from the disassembly).
// The function releases nodes via the lift-set callee native::sub_e935700(void*) and escapes
// through the data slot at RVA 0xF9A8C78 on detected corruption. Every offset below is
// cited with the instruction that uses it.
struct sub_2462890Layout {
    // vtable slots of the argument object
    static constexpr std::size_t vtable_listHead = 0x00;   // 0x24628af  mov rdi,[rax]   ; vtable[0] = node list head
    static constexpr std::size_t vtable_statePtr = 0x08;   // 0x24628a4  mov rcx,[rax+8] ; vtable[1] = pointer to state qword
    static_assert(vtable_listHead == 0x00, "sub_2462890: vtable+0x00 is the node list head");
    static_assert(vtable_statePtr == 0x08, "sub_2462890: vtable+0x08 is the state-qword pointer");
    // node fields
    static constexpr std::size_t node_next = 0x00;         // 0x24628ea  mov rbx,[rdi]
    static constexpr std::size_t node_start = 0x18;        // 0x24628ed  mov rcx,[rdi+0x18]
    static constexpr std::size_t node_end = 0x28;          // 0x24628f6  mov rdx,[rdi+0x28]
    static_assert(node_next == 0x00, "sub_2462890: node+0x00 is the next-node pointer");
    static_assert(node_start == 0x18, "sub_2462890: node+0x18 is the start cursor");
    static_assert(node_end == 0x28, "sub_2462890: node+0x28 is the end limit");
    static_assert(sizeof(void*) == 8, "sub_2462890: x64 ABI, pointer-sized fields");
};

namespace native {

// Lift-set callee (0xE935700, size 0x5, 1.26.62.01). Forward-declared per rule 66 (brief).
void* sub_e935700(void* a0);

// sub_2462890 (0x2462890, size 0xc5, 1.26.62.01): argument `a0` arrives in RCX, result leaves in RAX.
// Full reversal with per-instruction citations: src/client/features/render/native/helpers/sub_2462890.cpp
void* sub_2462890(void* a0);

} // namespace native