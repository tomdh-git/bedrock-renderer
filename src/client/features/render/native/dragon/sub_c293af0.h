#pragma once
#include <cstddef>
#include <cstdint>

namespace native {

// sub_c293af0 (0xc293af0, size 0xd6, 1.26.62.01, "BgfxFrameBuilder slot 16").
//
// Releases the refcounted object at a0+0x8+0x38 (strong then weak interlocked
// decrement; destroy via vtable[0], dealloc via vtable[8], both through data
// slot 0xF99FFA0 / sub_eea6040), then releases the heap string at a0+0x8+0x10
// via sub_e935700, resets the string to SSO state (cap=0, size=0xF, data=0),
// and tail-calls sub_e935700(a0+0x8).
//
// Layout of the context object (a0 = RCX):
//   a0+0x08  SubObject*  (rbx)                       c293af7  mov rbx,[rcx+8]
//
// Layout of the sub-object (rbx):
//   rbx+0x10  char*       string data pointer         c293b45  mov rcx,[rbx+0x10]
//   rbx+0x20  size_t      string capacity             c293b76  mov [rbx+0x20],0
//   rbx+0x28  size_t      string size                 c293b3b  mov rax,[rbx+0x28]
//   rbx+0x38  RefCounted* refcounted object           c293b07  mov rdi,[rbx+0x38]
//
// Layout of RefCounted (rdi):
//   rdi+0x00  void*       vtable                      c293b16/0x2b  mov rax,[rdi]
//   rdi+0x08  int32_t     strong count                c293b10  lock dec [rdi+8]
//   rdi+0x0C  int32_t     weak count                  c293b25  lock dec [rdi+0xC]
//   vtable[0]  destructor  -> data slot 0xF99FFA0     c293b1f  call qword ptr [0xF99FFA0]
//   vtable[8]  deallocator -> data slot 0xF99FFA0     c293b35  call qword ptr [0xF99FFA0]
struct RefCounted {
    void* vtable;        // +0x00
    std::int32_t strong; // +0x08
    std::int32_t weak;   // +0x0C
};

struct SubObject {
    std::uint8_t _pad_0x00[0x10];
    char* data;          // +0x10
    std::uint8_t _pad_0x18[0x20 - 0x18];
    std::uint64_t cap;   // +0x20
    std::uint64_t size;  // +0x28
    std::uint8_t _pad_0x30[0x38 - 0x30];
    RefCounted* ref;     // +0x38
};

struct Context {
    std::uint8_t _pad_0x00[0x08];
    SubObject* sub;      // +0x08
};

static_assert(offsetof(RefCounted, vtable) == 0x00, "sub_c293af0: RefCounted::vtable at +0x00");
static_assert(offsetof(RefCounted, strong) == 0x08, "sub_c293af0: RefCounted::strong at +0x08");
static_assert(offsetof(RefCounted, weak) == 0x0C, "sub_c293af0: RefCounted::weak at +0x0C");
static_assert(offsetof(SubObject, data) == 0x10, "sub_c293af0: SubObject::data at +0x10");
static_assert(offsetof(SubObject, cap) == 0x20, "sub_c293af0: SubObject::cap at +0x20");
static_assert(offsetof(SubObject, size) == 0x28, "sub_c293af0: SubObject::size at +0x28");
static_assert(offsetof(SubObject, ref) == 0x38, "sub_c293af0: SubObject::ref at +0x38");
static_assert(offsetof(Context, sub) == 0x08, "sub_c293af0: Context::sub at +0x08");
static_assert(sizeof(void*) == 8, "sub_c293af0: x64 ABI, pointer-sized address space");

// sub_e935700 (lift/set): void* sub_e935700(void*) — forward-declared here
// (called via its native symbol, never through a boundary wrapper).
void* sub_e935700(void* a0);

// sub_c293af0: x64 Microsoft ABI, arg1 (RCX) = context pointer a0, returns void.
// Tail-calls sub_e935700(a0+0x8) on the non-null path; returns with RAX unchanged
// when a0+0x8 is null.
void sub_c293af0(void* a0);

} // namespace native
