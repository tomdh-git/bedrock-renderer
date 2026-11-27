#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// Layout of the fields used by sub_c27ebd0 (Frame renderer lambda,
// 0xc27ebd0, size 0x8b, 1.26.62.01), observed in the disassembly of
// [0xc27ebd0, 0xc27ec5b):
//   0xc27ec06  mov rcx,[rsi+0x10]    (recursive call argument)
//   0xc27ec0f  mov rsi,[rsi]          (next pointer at +0x00)
//   0xc27ebd7  cmp byte ptr [rcx+0x19],0  (flag byte)
//   0xc27ec12  movzx eax,byte ptr [rdi+0x50]  (type byte)
//   0xc27ec25  mov rbx,[rdi+0x48]     (RefCountBase* object)
//   0xc27ec2e  lock dec dword ptr [rbx+0x08]  (strong ref count)
//   0xc27ec34  mov rax,[rbx]          (vtable pointer)
//   0xc27ec37  mov rax,[rax]          (vtable[0] = destructor)
//   0xc27ec3d  call qword ptr [0xF99FFA0]  (via data slot -> sub_eea6040)
//   0xc27ec43  lock dec dword ptr [rbx+0x0C]  (weak ref count)
//   0xc27ec49  mov rax,[rbx]          (vtable pointer)
//   0xc27ec4c  mov rax,[rax+0x08]     (vtable[8] = deallocator)
//   0xc27ec53  call qword ptr [0xF99FFA0]  (via data slot -> sub_eea6040)
// Only the fields used by this function are declared; nothing else about the
// class layout is assumed.

struct RefCountBase {
    void* vtable;            // +0x00  vtable pointer; [0] = destructor, [8] = deallocator
    std::int32_t strong;     // +0x08  interlocked strong reference count
    std::int32_t weak;       // +0x0C  interlocked weak reference count
};

struct FrameRendererNode {
    FrameRendererNode* next;            // +0x00  next node in list
    std::uint8_t _pad_0x08[0x08];       // +0x08  unused by this function
    void* recursiveArg;                 // +0x10  argument for recursive call
    std::uint8_t _pad_0x18[0x01];       // +0x18  unused
    std::uint8_t flag;                  // +0x19  early-exit flag
    std::uint8_t _pad_0x1A[0x2E];       // +0x1A  unused
    RefCountBase* refCountedObject;     // +0x48  object with ref counts
    std::uint8_t type;                  // +0x50  node type (0, 1, 2, ...)
};

// Layout assertions for RefCountBase
static_assert(offsetof(RefCountBase, vtable) == 0x00, "c27ebd0: RefCountBase::vtable at +0x00");
static_assert(offsetof(RefCountBase, strong) == 0x08, "c27ebd0: RefCountBase::strong at +0x08");
static_assert(offsetof(RefCountBase, weak) == 0x0C, "c27ebd0: RefCountBase::weak at +0x0C");
static_assert(sizeof(RefCountBase) == 0x10, "c27ebd0: RefCountBase size 0x10");

// Layout assertions for FrameRendererNode
static_assert(offsetof(FrameRendererNode, next) == 0x00, "c27ebd0: FrameRendererNode::next at +0x00");
static_assert(offsetof(FrameRendererNode, recursiveArg) == 0x10, "c27ebd0: FrameRendererNode::recursiveArg at +0x10");
static_assert(offsetof(FrameRendererNode, flag) == 0x19, "c27ebd0: FrameRendererNode::flag at +0x19");
static_assert(offsetof(FrameRendererNode, refCountedObject) == 0x48, "c27ebd0: FrameRendererNode::refCountedObject at +0x48");
static_assert(offsetof(FrameRendererNode, type) == 0x50, "c27ebd0: FrameRendererNode::type at +0x50");

// Forward declarations of callees
// sub_e935700 (0xE935700) is classified 'lift' in native_boundary.tsv;
// it will be lifted by its own unit. Signature observed at call sites:
// rcx = node pointer (FrameRendererNode*), rdx = 0x58.
// Returns void.
void sub_e935700(FrameRendererNode* node, std::uint32_t arg2);

// sub_eea6040 (vendor thunk via data slot 0xF99FFA0).
// Called with rcx = RefCountBase*, returns void (result ignored).
// The thunk is a `jmp rax` forwarder; the real target is the vtable entry
// preloaded into RAX by the caller (vtable[0] or vtable[8]).
void sub_eea6040(RefCountBase* obj);

// Recursive self-call: sub_c27ebd0 calls itself with the recursiveArg pointer.
void sub_c27ebd0(FrameRendererNode* node);

} // namespace native