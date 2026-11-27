#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_c283ce0 (0xc283ce0, size 0x6b, 1.26.62.01, "Frame renderer lambda").
//
// Layout of the node object the function walks, every offset observed in the
// disassembly of [0xc283ce0, 0xc283d4b):
//   0xc283ce6 / 0xc283d00  cmp byte ptr [reg+0x19],0        (renderFlag)
//   0xc283d09              mov rcx,[rsi+0x10]               (child)
//   0xc283d12              mov rsi,[rsi]                    (nextSibling)
//   0xc283d15              mov rdi,[rdi+0x30]               (refCount)
//   0xc283d1e              lock dec dword ptr [rdi+8]       (strong)
//   0xc283d33              lock dec dword ptr [rdi+0xC]     (weak)
struct RenderNode {
    RenderNode* nextSibling;      // [node + 0x00]
    std::uint8_t _pad_0x8[0x10 - sizeof(void*)];
    RenderNode* child;            // [node + 0x10]
    std::uint8_t _pad_0x18[0x19 - (0x10 + sizeof(void*))];
    std::uint8_t renderFlag;      // [node + 0x19]
    std::uint8_t _pad_0x1a[0x30 - (0x19 + 1)];
    class RefCountBase* refCount; // [node + 0x30]
};

// Layout of the ref-counted control block pointed at by RenderNode::refCount:
//   0xc283d24 / 0xc283d39  mov rax,[rdi]   (vtable, dead load before each thunk call)
//   0xc283d27              mov rax,[rax]   (vtable[0] = destructor)
//   0xc283d3c              mov rax,[rax+8] (vtable[8] = deallocator)
struct RefCountBase {
    void* vtable;        // [rc + 0x00]
    std::int32_t strong; // [rc + 0x08]  interlocked decrement
    std::int32_t weak;   // [rc + 0x0C]  interlocked decrement
    // vtable[0] (destructor) and vtable[8] (deallocator) are invoked through
    // loader-resolved data slot 0xF99FFA0 (sub_eea6040, a `jmp rax` thunk,
    // docs/data/native_boundary.tsv class vendor); rcx = rc on entry.
};

static_assert(offsetof(RenderNode, nextSibling) == 0x00, "sub_c283ce0: RenderNode::nextSibling at +0x00");
static_assert(offsetof(RenderNode, child) == 0x10, "sub_c283ce0: RenderNode::child at +0x10");
static_assert(offsetof(RenderNode, renderFlag) == 0x19, "sub_c283ce0: RenderNode::renderFlag at +0x19");
static_assert(offsetof(RenderNode, refCount) == 0x30, "sub_c283ce0: RenderNode::refCount at +0x30");
static_assert(offsetof(RefCountBase, vtable) == 0x00, "sub_c283ce0: RefCountBase::vtable at +0x00");
static_assert(offsetof(RefCountBase, strong) == 0x08, "sub_c283ce0: RefCountBase::strong at +0x08");
static_assert(offsetof(RefCountBase, weak) == 0x0C, "sub_c283ce0: RefCountBase::weak at +0x0C");
static_assert(sizeof(void*) == 8, "sub_c283ce0: x64 ABI, pointer-sized address space");

// Signature of sub_c283ce0 itself: x64 Microsoft ABI, node in RCX, returns void.
void sub_c283ce0(RenderNode* node);

} // namespace native
