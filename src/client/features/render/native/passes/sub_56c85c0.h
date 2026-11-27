#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_56c85c0 (0x56c85c0, size 0x95, 1.26.62.01, "pass encode C").
//
//   0x56c85c0  push rsi                                            ; prologue
//   0x56c85c1  push rdi                                            ; prologue
//   0x56c85c2  sub rsp,0x28                                        ; prologue
//   0x56c85c6  mov rsi,rcx                                         ; rsi = pass object (a0)
//   0x56c85c9  mov rax,[rdx]                                       ; rax = *item (+0x0)
//   0x56c85cc  mov [rcx+0x100],rax                                 ; pass+0x100 = *item
//   0x56c85d3  mov rax,[rdx+0x10]                                  ; rax = item+0x10 (refcounted obj ptr)
//   0x56c85d7  test rax,rax
//   0x56c85da  je short 0x56C85E6                                  ; if null, skip addref
//   0x56c85dc  lock inc dword ptr [rax+8]                          ; *(item+0x10)+0x8 refcount +1
//   0x56c85e0  mov rax,[rdx+0x10]                                  ; rax = item+0x10 again (same value)
//   0x56c85e4  jmp short 0x56C85E8
//   0x56c85e6  xor eax,eax                                         ; rax = 0
//   0x56c85e8  mov rcx,[rdx+8]                                     ; rcx = item+0x8 (obj8 ptr)
//   0x56c85ec  mov [rsi+0x108],rcx                                 ; pass+0x108 = obj8
//   0x56c85f3  mov rdi,[rsi+0x110]                                 ; rdi = pass+0x110 (old obj)
//   0x56c85fa  mov [rsi+0x110],rax                                 ; pass+0x110 = rax (new obj)
//   0x56c8601  test rdi,rdi                                        ; old obj != null?
//   0x56c8604  je short 0x56C8631                                  ; if null, skip release
//   0x56c8606  lock dec dword ptr [rdi+8]                          ; *(oldObj)+0x8 refcount -1
//   0x56c860a  jne short 0x56C8631                                 ; if not zero, skip delete
//   0x56c860c  mov rax,[rdi]                                       ; rax = *oldObj (vfptr)
//   0x56c860f  mov rax,[rax]                                       ; rax = vfptr[0] (destructor)
//   0x56c8612  mov rcx,rdi                                         ; RCX = oldObj
//   0x56c8615  call qword ptr [0xF99FFA0]                          ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
//   0x56c861b  lock dec dword ptr [rdi+0xC]                        ; *(oldObj)+0xC count0xC -1
//   0x56c861f  jne short 0x56C8631                                 ; if not zero, skip delete
//   0x56c8621  mov rax,[rdi]                                       ; rax = *oldObj (vfptr)
//   0x56c8624  mov rax,[rax+8]                                     ; rax = vfptr[1] (operator delete)
//   0x56c8628  mov rcx,rdi                                         ; RCX = oldObj
//   0x56c862b  call qword ptr [0xF99FFA0]                          ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
//   0x56c8631  mov rax,[rsi+0x108]                                 ; rax = pass+0x108 = obj8
//   0x56c8638  mov rcx,[rax+0x10]                                  ; rcx = obj8+0x10 (pointer)
//   0x56c863c  movzx edx,word ptr [rax+8]                          ; edx = obj8+8 as u16
//   0x56c8640  lea r8,[0x56C8810]                                  ; r8 = &sub_56c8810
//   0x56c8647  mov r9,rsi                                          ; r9 = passObj
//   0x56c864a  add rsp,0x28                                        ; epilogue
//   0x56c864e  pop rdi                                             ; epilogue
//   0x56c864f  pop rsi                                             ; epilogue
//   0x56c8650  jmp 0xBC61560                                       ; tail call to sub_bc61560
//
// x64 Microsoft ABI: RCX = pass object, RDX = item object, return void (tail call to sub_bc61560).
//
// Layout of fields in 'pass object' (a0, RCX) [V]:
//   +0x100 (W, 8 bytes): pointer from item+0x0
//   +0x108 (W, 8 bytes): pointer from item+0x8
//   +0x110 (R/W, 8 bytes): refcounted object pointer (old released, new stored)
//
// Layout of fields in 'item object' (a1, RDX) [V]:
//   +0x0 (R, 8 bytes): pointer -> pass+0x100
//   +0x8 (R, 8 bytes): pointer to obj8 object -> pass+0x108
//   +0x10 (R, 8 bytes): pointer to refcounted object (addref on set, release on replace)
//
// Layout of fields in 'obj8 object' (pointed to by item+0x8) [V]:
//   +0x8 (R, 2 bytes): u16 flags -> rdx arg of sub_bc61560
//   +0x10 (R, 8 bytes): pointer -> rcx arg of sub_bc61560
//
// Layout of refcounted object [V]:
//   +0x00 (R, 8 bytes): vfptr
//   +0x08 (R/W, 4 bytes): uint32_t refcount (lock inc on addref, lock dec on release)
//   +0x0C (R/W, 4 bytes): uint32_t count0xC (lock dec on release)
//
// Callees [V]:
//   - sub_eea6040 (boundary/vendor, via data slot 0xF99FFA0): 2 calls
//     0x56c8615  call qword ptr [0xF99FFA0]   (virtual destructor vfptr[0](oldObj))
//     0x56c862b  call qword ptr [0xF99FFA0]   (virtual delete vfptr[1](oldObj))
//   - sub_56c8810 (lift set, pass body C, 0x56c8810): address taken as r8 function pointer,
//     passed to sub_bc61560; NOT called by this function.
//   - sub_bc61560 (lift set, custom item submit, 0xbc61560): tail call at 0x56c8650.
//   0 callees directly called from the lift set; 2 calls to boundary vendor thunk.
//
// No null guards or SEH beyond the original's own tests.

// Offset constants for the pass object (a0/RCX).
static constexpr std::size_t kPassOffset0x100 = 0x100;
static constexpr std::size_t kPassOffset0x108 = 0x108;
static constexpr std::size_t kPassOffset0x110 = 0x110;

// Offset constants for the item object (a1/RDX).
static constexpr std::size_t kItemOffset0x00 = 0x00;
static constexpr std::size_t kItemOffset0x08 = 0x08;
static constexpr std::size_t kItemOffset0x10 = 0x10;

// Offset constants for the obj8 object (pointed to by item+0x8).
static constexpr std::size_t kObj8Offset0x08 = 0x08;
static constexpr std::size_t kObj8Offset0x10 = 0x10;

// Offset constants for the refcounted object.
static constexpr std::size_t kRefcountedOffsetVfptr = 0x00;
static constexpr std::size_t kRefcountedOffsetRefcount = 0x08;
static constexpr std::size_t kRefcountedOffsetCount0xC = 0x0C;

struct sub_56c85c0_pass {
    std::uint8_t pad0x00[0x100];  // padding to reach +0x100
    void* field0x100;             // +0x100 [W] pointer from item+0x0
    void* field0x108;             // +0x108 [W] pointer from item+0x8
    void* field0x110;             // +0x110 [R/W] refcounted object pointer
};

struct sub_56c85c0_item {
    void* field0x00;     // +0x00 [R] pointer
    void* field0x08;     // +0x08 [R] pointer to obj8 object
    void* refCounted;    // +0x10 [R] pointer to refcounted object
};

struct sub_56c85c0_obj8 {
    std::uint8_t pad0x00[0x08];
    std::uint16_t field0x08;   // +0x08 [R] u16 flags
    std::uint8_t pad0x0a[0x10 - 0x0a];
    void* field0x10;     // +0x10 [R] pointer
};

struct sub_56c85c0_refcounted {
    void* vfptr;             // +0x00 [R] vfptr
    std::uint32_t refcount;  // +0x08 [R/W] lock inc/dec
    std::uint32_t count0xC;  // +0x0C [R/W] lock dec
};

struct sub_56c85c0Layout {
    static_assert(offsetof(sub_56c85c0_pass, field0x100) == kPassOffset0x100,
                  "sub_56c85c0_pass: field0x100 at +0x100");
    static_assert(offsetof(sub_56c85c0_pass, field0x108) == kPassOffset0x108,
                  "sub_56c85c0_pass: field0x108 at +0x108");
    static_assert(offsetof(sub_56c85c0_pass, field0x110) == kPassOffset0x110,
                  "sub_56c85c0_pass: field0x110 at +0x110");
    static_assert(offsetof(sub_56c85c0_item, field0x00) == kItemOffset0x00,
                  "sub_56c85c0_item: field0x00 at +0x00");
    static_assert(offsetof(sub_56c85c0_item, field0x08) == kItemOffset0x08,
                  "sub_56c85c0_item: field0x08 at +0x08");
    static_assert(offsetof(sub_56c85c0_item, refCounted) == kItemOffset0x10,
                  "sub_56c85c0_item: refCounted at +0x10");
    static_assert(offsetof(sub_56c85c0_obj8, field0x08) == kObj8Offset0x08,
                  "sub_56c85c0_obj8: field0x08 at +0x08");
    static_assert(offsetof(sub_56c85c0_obj8, field0x10) == kObj8Offset0x10,
                  "sub_56c85c0_obj8: field0x10 at +0x10");
    static_assert(offsetof(sub_56c85c0_refcounted, vfptr) == kRefcountedOffsetVfptr,
                  "sub_56c85c0_refcounted: vfptr at +0x00");
    static_assert(offsetof(sub_56c85c0_refcounted, refcount) == kRefcountedOffsetRefcount,
                  "sub_56c85c0_refcounted: refcount at +0x08");
    static_assert(offsetof(sub_56c85c0_refcounted, count0xC) == kRefcountedOffsetCount0xC,
                  "sub_56c85c0_refcounted: count0xC at +0x0C");
    static_assert(sizeof(void*) == 8, "sub_56c85c0: x64 pointers are 8 bytes");

    static_assert(sizeof(sub_56c85c0_pass) == 0x118, "sub_56c85c0_pass: size reaches +0x118");
    static_assert(sizeof(sub_56c85c0_item) == 0x18, "sub_56c85c0_item: size is 0x18");
    static_assert(sizeof(sub_56c85c0_obj8) == 0x18, "sub_56c85c0_obj8: size is 0x18");
    static_assert(sizeof(sub_56c85c0_refcounted) == 0x10, "sub_56c85c0_refcounted: size is 0x10");
};

namespace native {

// sub_56c8810 (lift set, pass body C, 0x56c8810, size 0xc4): forward-declared here.
// Its address is taken (lea r8,[0x56C8810]) and passed to sub_bc61560 as r8;
// it is NOT called by this function. Signature recovered from its disassembly:
// rcx = pass object, returns void [V].
void sub_56c8810(void* passObject);

namespace bgfx {

// sub_bc61560 (lift set, custom item submit, 0xbc61560, size 0x372): forward-declared here.
// Called via tail jump (jmp 0xBC61560) at the end of this function.
// Signature: rcx = obj8 pointer, rdx = u16 flags, r8 = callback (&sub_56c8810),
// r9 = pass object; returns void [V].
extern "C" void sub_bc61560(void* obj8Ptr, std::uint16_t flags, void* callback, void* passObject);

} // namespace bgfx

// sub_56c85c0(void* passObj, void* item) -> void
void sub_56c85c0(void* passObj, void* item);

} // namespace native
