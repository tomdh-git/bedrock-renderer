#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_9c590 (0x9c590, size 0xb4, 1.26.62.01) - recursive node-tree release.
// See sub_9c590.cpp for the reversed source (complete).
//
// Every callee of sub_9c590 is lift-classified:
//   0x9C5C6  call 0x9C590   - recursive call (this unit). RCX = slot pointer (dead),
//                              RDX = child node; children are 0x40 bytes apart.
//   0x9C602  call 0xE935700 - sub_e935700 (unit X7.e935700, helpers/sub_e935700).
//   0x9C625  jmp 0x9C650    - tail call to sub_9c650 (unit X7.9c650,
//                            lift-classified, native_boundary.tsv line 22).
// Data slot (brief rule 8, not a callee): RVA 0xF9A8C78 (VA = imageBase() + 0xF9A8C78)
//   read at call time by 0x9C63D call qword ptr [0xF9A8C78]; five zero arguments;
//   block ends in int3 (noreturn).

// sub_e935700 (0xe935700, size 0x5): lift-classified tail jump to sub_392960;
// argument in RCX, result in RAX. Forward declaration only (full declaration with
// layout lives in helpers/sub_e935700.h).
void* sub_e935700(void* a0);

// Node layout observed in sub_9c590: the function reads/writes [node+0x28] (child
// list begin), [node+0x30] (child list end) and [node+0x38] (allocation limit).
// Children are packed with stride 0x40, so each child is itself such a node.
// The allocator size prefix is read at [child-8] (0x9C5E7); the three slot fields
// (+0x28, +0x30, +0x38) are cleared at 0x9C60A/0x9C60D.
struct Node {
    char pad00[0x28];
    void* child_begin;   // +0x28 child list begin pointer (R/W)
    void* child_end;     // +0x30 child list end   pointer (R/W)
    void* limit;         // +0x38 allocation limit  pointer (R/W)
};                       // sizeof == 0x40; children are 0x40 apart

struct sub_9c590Layout {
    static_assert(sizeof(Node) == 0x40, "sub_9c590: node size is 0x40 (0x38 + 8)");
    static_assert(offsetof(Node, child_begin) == 0x28, "sub_9c590: child_begin offset");
    static_assert(offsetof(Node, child_end) == 0x30, "sub_9c590: child_end offset");
    static_assert(offsetof(Node, limit) == 0x38, "sub_9c590: limit offset");
    static_assert(sizeof(void*) == 8, "sub_9c590: x64 pointers");
};

// sub_9c650 (0x9c650, size 0xf3): lift-classified, lifted by unit X7.9c650.
// Tail-called from sub_9c590's exit blocks with RCX = node + 0x10; its RAX
// passes through as sub_9c590's result.
void* sub_9c650(void* a0);

// sub_9c590: exact x64 Microsoft ABI signature of the original.
// RCX = slot pointer (dead on entry: written before every read, never read);
// RDX = node pointer. Return value: the tail call to sub_9c650 passes RAX
// through, so the return type is void* like sub_9c650's declaration.
void* sub_9c590(void* slot, void* node);

} // namespace native
