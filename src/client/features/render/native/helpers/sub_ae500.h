#pragma once
#include <cstddef>
#include <cstdint>

namespace native::helpers {

// Layouts for sub_ae500, taken from the disassembly of [0xae500, 0xae60a),
// Minecraft Windows 1.26.62.01. Offsets, widths and signedness are the instruction
// operands. The structs are packed so offsetof() matches those offsets exactly;
// sizeof is a lower bound because the real object can carry compiler padding past
// the last observed field.

// Linked-list node. Used through rax during the first walk (0xae530..0xae586) and
// through rdi/rbx for the remembered node and the second walk.
#pragma pack(push, 1)
struct sub_ae500_node {
    std::uint8_t pad0x00[0x8];   // +0x00..+0x07 no observed access
    std::uint64_t link;          // +0x08 raw link; nonzero encodes next as link - 8
                                 //       R at 0xae571 (mov r11,[rax+8]) and 0xae5df (mov rax,[rbx+8])
    std::uint8_t pad0x10[0x10];  // +0x10..+0x1f no observed access
    std::uint64_t seqEnd;        // +0x20 R at 0xae539 (mov r15,[rax+0x20])
    std::uint64_t seqStart;      // +0x28 R at 0xae53d (mov r10,[rax+0x28])
    std::uint8_t pad0x30[0x18];  // +0x30..+0x47 no observed access
    std::uint8_t mode48;         // +0x48 R at 0xae590 and 0xae5f1 (cmp byte ptr [..+0x48],1)
};
#pragma pack(pop)

// Head slot passed in rcx. Only +0x00 is touched here: read before the first walk
// (0xae50d) and re-read after the first callee call (0xae5b6).
#pragma pack(push, 1)
struct sub_ae500_head {
    sub_ae500_node* node;        // +0x00 current head node pointer
};
#pragma pack(pop)

static_assert(offsetof(sub_ae500_node, link) == 0x8, "sub_ae500 node+0x8 link field");
static_assert(offsetof(sub_ae500_node, seqEnd) == 0x20, "sub_ae500 node+0x20 seqEnd field");
static_assert(offsetof(sub_ae500_node, seqStart) == 0x28, "sub_ae500 node+0x28 seqStart field");
static_assert(offsetof(sub_ae500_node, mode48) == 0x48, "sub_ae500 node+0x48 mode48 field");
static_assert(sizeof(sub_ae500_node) >= 0x49, "sub_ae500 node sizeof lower bound");

static_assert(offsetof(sub_ae500_head, node) == 0x0, "sub_ae500 head+0x0 node field");
static_assert(sizeof(sub_ae500_head) >= 0x8, "sub_ae500 head sizeof lower bound");

// Callees outside the lift set. Signatures follow from the register contents at the
// call sites below; both return their boolean result in al and take (node, context).
// They are linked directly to the game code, as the other lifted helpers do for
// non-lift-set callees.
bool sub_ae610(sub_ae500_node* node, void* context);   // 0xae59c, 0xae5fd
bool sub_ae770(sub_ae500_node* node, void* context);   // 0xae5a9, 0xae5d6

// x64 Microsoft ABI: RCX = head slot pointer, RDX = context; returns AL = bool.
bool sub_ae500(sub_ae500_head* head, void* context);

} // namespace native::helpers
