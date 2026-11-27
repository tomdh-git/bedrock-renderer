#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_568b9e0 (0x568b9e0, size 0x95, 1.26.62.01, "common pass task encode (queues the custom item)").
//
//   0x568b9e0  push rsi                                            ; prologue
//   0x568b9e1  push rdi                                            ; prologue
//   0x568b9e2  sub rsp,0x28                                        ; prologue
//   0x568b9e6  mov rsi,rcx                                         ; rsi = pass object (a0)
//   0x568b9e9  mov rax,[rdx]                                       ; rax = *item (+0x0)
//   0x568b9ec  mov [rcx+0x2E0],rax                                 ; pass+0x2E0 = *item
//   0x568b9f3  mov rax,[rdx+0x10]                                  ; rax = item+0x10 (refcounted obj ptr)
//   0x568b9f7  test rax,rax
//   0x568b9fa  je short 0x568BA06                                  ; if null, skip addref
//   0x568b9fc  lock inc dword ptr [rax+8]                          ; *(item+0x10)+0x8 refcount +1
//   0x568ba00  mov rax,[rdx+0x10]                                  ; rax = item+0x10 again (same value)
//   0x568ba04  jmp short 0x568BA08
//   0x568ba06  xor eax,eax                                         ; rax = 0
//   0x568ba08  mov rcx,[rdx+8]                                     ; rcx = item+0x8 (obj8 ptr)
//   0x568ba0c  mov [rsi+0x2E8],rcx                                 ; pass+0x2E8 = obj8
//   0x568ba13  mov rdi,[rsi+0x2F0]                                 ; rdi = pass+0x2F0 (old obj)
//   0x568ba1a  mov [rsi+0x2F0],rax                                 ; pass+0x2F0 = rax (new obj)
//   0x568ba21  test rdi,rdi                                        ; old obj != null?
//   0x568ba24  je short 0x568BA51                                  ; if null, skip release
//   0x568ba26  lock dec dword ptr [rdi+8]                          ; *(oldObj)+0x8 refcount -1
//   0x568ba2a  jne short 0x568BA51                                 ; if not zero, skip delete
//   0x568ba2c  mov rax,[rdi]                                       ; rax = *oldObj (vfptr)
//   0x568ba2f  mov rax,[rax]                                       ; rax = vfptr[0] (destructor)
//   0x568ba32  mov rcx,rdi                                         ; RCX = oldObj
//   0x568ba35  call qword ptr [0xF99FFA0]                          ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
//   0x568ba3b  lock dec dword ptr [rdi+0xC]                        ; *(oldObj)+0xC count0xC -1
//   0x568ba3f  jne short 0x568BA51                                 ; if not zero, skip delete
//   0x568ba41  mov rax,[rdi]                                       ; rax = *oldObj (vfptr)
//   0x568ba44  mov rax,[rax+8]                                     ; rax = vfptr[1] (operator delete)
//   0x568ba48  mov rcx,rdi                                         ; RCX = oldObj
//   0x568ba4b  call qword ptr [0xF99FFA0]                          ; -> sub_eea6040 (boundary/vendor thunk, jmp rax)
//   0x568ba51  mov rax,[rsi+0x2E8]                                 ; rax = pass+0x2E8 = obj8
//   0x568ba58  mov rcx,[rax+0x10]                                  ; rcx = obj8+0x10 (pointer)
//   0x568ba5c  movzx edx,word ptr [rax+8]                          ; edx = obj8+8 as u16
//   0x568ba60  lea r8,[0x568BCD0]                                  ; r8 = &sub_568bcd0
//   0x568ba67  mov r9,rsi                                          ; r9 = passObj
//   0x568ba6a  add rsp,0x28                                        ; epilogue
//   0x568ba6e  pop rdi                                             ; epilogue
//   0x568ba6f  pop rsi                                             ; epilogue
//   0x568ba70  jmp 0xBC61560                                       ; tail call to sub_bc61560
//
// x64 Microsoft ABI: RCX = pass object, RDX = item object, return void (tail call to sub_bc61560).
//
// Layout of fields in 'pass object' (a0, RCX) [V]:
//   +0x2E0 (W, 8 bytes): pointer from item+0x0
//   +0x2E8 (W, 8 bytes): pointer from item+0x8
//   +0x2F0 (R/W, 8 bytes): refcounted object pointer (old released, new stored)
//
// Layout of fields in 'item object' (a1, RDX) [V]:
//   +0x0 (R, 8 bytes): pointer -> pass+0x2E0
//   +0x8 (R, 8 bytes): pointer to obj8 object -> pass+0x2E8
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
//     0x568ba35  call qword ptr [0xF99FFA0]   (virtual destructor vfptr[0](oldObj))
//     0x568ba4b  call qword ptr [0xF99FFA0]   (virtual delete vfptr[1](oldObj))
//   - sub_568bcd0 (lift set, pass body A, 0x568bcd0): address taken as r8 function pointer,
//     passed to sub_bc61560; NOT called by this function.
//   - sub_bc61560 (lift set, custom item submit, 0xbc61560): tail call at 0x568ba70.
//   0 callees directly called from the lift set; 2 calls to boundary vendor thunk.
//
// No null guards or SEH beyond the original's own tests.

// Offset constants for the pass object (a0/RCX).
static constexpr std::size_t kPassOffset0x2E0 = 0x2E0;
static constexpr std::size_t kPassOffset0x2E8 = 0x2E8;
static constexpr std::size_t kPassOffset0x2F0 = 0x2F0;

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

struct sub_568b9e0_pass {
    std::uint8_t pad0x00[0x2E0];  // padding to reach +0x2E0
    void* field0x2E0;             // +0x2E0 [W] pointer from item+0x0
    void* field0x2E8;             // +0x2E8 [W] pointer from item+0x8
    void* field0x2F0;             // +0x2F0 [R/W] refcounted object pointer
};

struct sub_568b9e0_item {
    void* field0x00;     // +0x00 [R] pointer
    void* field0x08;     // +0x08 [R] pointer to obj8 object
    void* refCounted;    // +0x10 [R] pointer to refcounted object
};

struct sub_568b9e0_obj8 {
    std::uint8_t pad0x00[0x08];
    std::uint16_t field0x08;   // +0x08 [R] u16 flags
    std::uint8_t pad0x0a[0x10 - 0x0a];
    void* field0x10;     // +0x10 [R] pointer
};

struct sub_568b9e0_refcounted {
    void* vfptr;             // +0x00 [R] vfptr
    std::uint32_t refcount;  // +0x08 [R/W] lock inc/dec
    std::uint32_t count0xC;  // +0x0C [R/W] lock dec
};

struct sub_568b9e0Layout {
    static_assert(offsetof(sub_568b9e0_pass, field0x2E0) == kPassOffset0x2E0,
                  "sub_568b9e0_pass: field0x2E0 at +0x2E0");
    static_assert(offsetof(sub_568b9e0_pass, field0x2E8) == kPassOffset0x2E8,
                  "sub_568b9e0_pass: field0x2E8 at +0x2E8");
    static_assert(offsetof(sub_568b9e0_pass, field0x2F0) == kPassOffset0x2F0,
                  "sub_568b9e0_pass: field0x2F0 at +0x2F0");
    static_assert(offsetof(sub_568b9e0_item, field0x00) == kItemOffset0x00,
                  "sub_568b9e0_item: field0x00 at +0x00");
    static_assert(offsetof(sub_568b9e0_item, field0x08) == kItemOffset0x08,
                  "sub_568b9e0_item: field0x08 at +0x08");
    static_assert(offsetof(sub_568b9e0_item, refCounted) == kItemOffset0x10,
                  "sub_568b9e0_item: refCounted at +0x10");
    static_assert(offsetof(sub_568b9e0_obj8, field0x08) == kObj8Offset0x08,
                  "sub_568b9e0_obj8: field0x08 at +0x08");
    static_assert(offsetof(sub_568b9e0_obj8, field0x10) == kObj8Offset0x10,
                  "sub_568b9e0_obj8: field0x10 at +0x10");
    static_assert(offsetof(sub_568b9e0_refcounted, vfptr) == kRefcountedOffsetVfptr,
                  "sub_568b9e0_refcounted: vfptr at +0x00");
    static_assert(offsetof(sub_568b9e0_refcounted, refcount) == kRefcountedOffsetRefcount,
                  "sub_568b9e0_refcounted: refcount at +0x08");
    static_assert(offsetof(sub_568b9e0_refcounted, count0xC) == kRefcountedOffsetCount0xC,
                  "sub_568b9e0_refcounted: count0xC at +0x0C");
    static_assert(sizeof(void*) == 8, "sub_568b9e0: x64 pointers are 8 bytes");

    static_assert(sizeof(sub_568b9e0_pass) == 0x2F8, "sub_568b9e0_pass: size reaches +0x2F8");
    static_assert(sizeof(sub_568b9e0_item) == 0x18, "sub_568b9e0_item: size is 0x18");
    static_assert(sizeof(sub_568b9e0_obj8) == 0x18, "sub_568b9e0_obj8: size is 0x18");
    static_assert(sizeof(sub_568b9e0_refcounted) == 0x10, "sub_568b9e0_refcounted: size is 0x10");
};

namespace native {

// sub_568bcd0 (lift set, pass body A, 0x568bcd0, size 0xc4): forward-declared here.
// Its address is taken (lea r8,[0x568BCD0]) and passed to sub_bc61560 as r8;
// it is NOT called by this function. Signature recovered from its disassembly:
// rcx = pass object, returns void [V].
void sub_568bcd0(void* passObject);

namespace bgfx {

// sub_bc61560 (lift set, custom item submit, 0xbc61560, size 0x372): forward-declared here.
// Called via tail jump (jmp 0xBC61560) at the end of this function.
// Signature: rcx = obj8 pointer, rdx = u16 flags, r8 = callback (&sub_568bcd0),
// r9 = pass object; returns void [V].
extern "C" void sub_bc61560(void* obj8Ptr, std::uint16_t flags, void* callback, void* passObject);

} // namespace bgfx

// sub_568b9e0(void* passObj, void* item) -> void
void sub_568b9e0(void* passObj, void* item);

} // namespace native
