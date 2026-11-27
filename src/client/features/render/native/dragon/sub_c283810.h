#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_c283810 (0xc283810, size 0x8b, 1.26.62.01, "Frame renderer lambda").
//
// Layout of the node object the function walks, every offset observed in the
// disassembly of [0xc283810, 0xc28389b):
//   0xc283816 / 0xc283830  cmp byte ptr [reg+0x19],0        (renderFlag)
//   0xc283839              mov rcx,[rsi+0x10]               (child)
//   0xc283842              mov rsi,[rsi]                    (nextSibling)
//   0xc283845              movzx eax,byte ptr [rdi+0x38]    (type)
//   0xc283865              mov rdi,[rdi+0x30]               (refCount)
//   0xc28386e / 0xc283883   lock dec dword ptr [rdi+8]       (strong)
//   0xc283883 / 0xc283887   lock dec dword ptr [rdi+0xC]     (weak)
struct RenderNode {
    RenderNode* nextSibling;      // [node + 0x00]
    std::uint8_t _pad_0x8[0x10 - sizeof(void*)];
    RenderNode* child;            // [node + 0x10]
    std::uint8_t _pad_0x18[0x19 - (0x10 + sizeof(void*))];
    std::uint8_t renderFlag;      // [node + 0x19]
    std::uint8_t _pad_0x1a[0x30 - (0x19 + 1)];
    class RefCountBase* refCount; // [node + 0x30]
    std::uint8_t type;            // [node + 0x38]
};

// Layout of the ref-counted control block pointed at by RenderNode::refCount:
//   0xc283874 / 0xc283889  mov rax,[rdi]   (vtable, dead load before each thunk call)
//   0xc283877 / 0xc28388c  mov rax,[rax]   (vtable[0] = destructor)
//   0xc28388c              mov rax,[rax+8] (vtable[8] = deallocator)
struct RefCountBase {
    void* vtable;        // [rc + 0x00]
    std::int32_t strong; // [rc + 0x08]  interlocked decrement
    std::int32_t weak;   // [rc + 0x0C]  interlocked decrement
    // vtable[0] (destructor) and vtable[8] (deallocator) are invoked through
    // loader-resolved data slot 0xF99FFA0 (sub_eea6040, a `jmp rax` thunk,
    // docs/data/native_boundary.tsv class vendor); rcx = rc on entry.
};

static_assert(offsetof(RenderNode, nextSibling) == 0x00, "sub_c283810: RenderNode::nextSibling at +0x00");
static_assert(offsetof(RenderNode, child) == 0x10, "sub_c283810: RenderNode::child at +0x10");
static_assert(offsetof(RenderNode, renderFlag) == 0x19, "sub_c283810: RenderNode::renderFlag at +0x19");
static_assert(offsetof(RenderNode, refCount) == 0x30, "sub_c283810: RenderNode::refCount at +0x30");
static_assert(offsetof(RenderNode, type) == 0x38, "sub_c283810: RenderNode::type at +0x38");
static_assert(offsetof(RefCountBase, vtable) == 0x00, "sub_c283810: RefCountBase::vtable at +0x00");
static_assert(offsetof(RefCountBase, strong) == 0x08, "sub_c283810: RefCountBase::strong at +0x08");
static_assert(offsetof(RefCountBase, weak) == 0x0C, "sub_c283810: RefCountBase::weak at +0x0C");
static_assert(sizeof(void*) == 8, "sub_c283810: x64 ABI, pointer-sized address space");

// Forward declarations of callees
// sub_eea6040 (vendor thunk via data slot 0xF99FFA0, class vendor).
// Called with rcx = RefCountBase*, returns void. The thunk is a `jmp rax`
// forwarder; the real target is the vtable entry preloaded into RAX by the
// caller (vtable[0] or vtable[8]).
void sub_eea6040(RefCountBase* obj);

// Recursive self-call: sub_c283810 calls itself with the child pointer.
void sub_c283810(RenderNode* node);

} // namespace native
