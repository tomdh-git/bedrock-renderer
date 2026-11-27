#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_5699be0 (0x5699be0, size 0x95, 1.26.62.01, "pass encode B").
//
//   0x5699be0  push rsi                                            ; prologue
//   0x5699be1  push rdi                                            ; prologue
//   0x5699be2  sub rsp,0x28                                        ; prologue
//   0x5699be6  mov rsi,rcx                                         ; rsi = pass object (a0)
//   0x5699be9  mov rax,[rdx]                                       ; rax = *item (+0x0)
//   0x5699bec  mov [rcx+0xA8],rax                                  ; pass+0xA8 = *item
//   0x5699bf3  mov rax,[rdx+0x10]                                  ; rax = item+0x10 (refcounted obj ptr)
//   0x5699bf7  test rax,rax
//   0x5699bfa  je short 0x5699C06                                  ; if null, skip addref
//   0x5699bfc  lock inc dword ptr [rax+8]                          ; *(item+0x10)+0x8 refcount +1
//   0x5699c00  mov rax,[rdx+0x10]                                  ; rax = item+0x10 again
//   0x5699c04  jmp short 0x5699C08
//   0x5699c06  xor eax,eax                                         ; rax = 0
//   0x5699c08  mov rcx,[rdx+8]                                     ; rcx = item+0x8 (obj8 pointer)
//   0x5699c0c  mov [rsi+0xB0],rcx                                  ; pass+0xB0 = obj8
//   0x5699c13  mov rdi,[rsi+0xB8]                                  ; rdi = pass+0xB8 (old obj)
//   0x5699c1a  mov [rsi+0xB8],rax                                  ; pass+0xB8 = new obj
//   0x5699c21  test rdi,rdi                                        ; old obj != null?
//   0x5699c24  je short 0x5699C51                                  ; if null, skip release
//   0x5699c26  lock dec dword ptr [rdi+8]                          ; *(oldObj)+0x8 refcount -1
//   0x5699c2a  jne short 0x5699C51                                 ; if not zero, skip delete
//   0x5699c2c  mov rax,[rdi]                                       ; rax = *oldObj (vfptr)
//   0x5699c2f  mov rax,[rax]                                       ; rax = vfptr[0] (destructor)
//   0x5699c32  mov rcx,rdi                                         ; RCX = oldObj
//   0x5699c35  call qword ptr [0xF99FFA0]                          ; -> sub_eea6040 (boundary/vendor thunk: jmp rax) -> vfptr[0](oldObj)
//   0x5699c3b  lock dec dword ptr [rdi+0xC]                        ; *(oldObj)+0xC count0xC -1
//   0x5699c3f  jne short 0x5699C51                                 ; if not zero, skip delete
//   0x5699c41  mov rax,[rdi]                                       ; rax = *oldObj (vfptr)
//   0x5699c44  mov rax,[rax+8]                                     ; rax = vfptr[1] (operator delete)
//   0x5699c48  mov rcx,rdi                                         ; RCX = oldObj
//   0x5699c4b  call qword ptr [0xF99FFA0]                          ; -> sub_eea6040 (boundary/vendor thunk: jmp rax) -> vfptr[1](oldObj)
//   0x5699c51  mov rax,[rsi+0xB0]                                  ; rax = pass+0xB0 = obj8
//   0x5699c58  mov rcx,[rax+0x10]                                  ; rcx = obj8+0x10 (pointer)
//   0x5699c5c  movzx edx,word ptr [rax+8]                          ; edx = obj8+8 as u16
//   0x5699c60  lea r8,[0x5699E30]                                  ; r8 = &sub_5699e30 (pass body B, NOT called here)
//   0x5699c67  mov r9,rsi                                          ; r9 = passObj
//   0x5699c6a  add rsp,0x28                                        ; epilogue
//   0x5699c6e  pop rdi                                             ; epilogue
//   0x5699c6f  pop rsi                                             ; epilogue
//   0x5699c70  jmp 0xBC61560                                       ; tail call to sub_bc61560
//
// x64 Microsoft ABI: RCX = pass object, RDX = item object, return void (tail call to sub_bc61560).
//
// Layout of fields in 'pass object' (a0, RCX) [V]:
//   +0xA8 (W, 8 bytes): pointer from item+0x0
//   +0xB0 (W, 8 bytes): pointer from item+0x8 (obj8/viewRef object)
//   +0xB8 (R/W, 8 bytes): refcounted object pointer (old released, new stored)
//
// Layout of fields in 'item object' (a1, RDX) [V]:
//   +0x00 (R, 8 bytes): pointer -> pass+0xA8
//   +0x08 (R, 8 bytes): pointer to obj8 object -> pass+0xB0
//   +0x10 (R, 8 bytes): pointer to refcounted object (addref on set, release on replace)
//
// Layout of fields in 'obj8 object' (pointed to by item+0x8 / pass+0xB0) [V]:
//   +0x08 (R, 2 bytes): u16 flags -> rdx arg of sub_bc61560
//   +0x10 (R, 8 bytes): pointer -> rcx arg of sub_bc61560
//
// Layout of refcounted object [V]:
//   +0x00 (R, 8 bytes): vfptr
//   +0x08 (R/W, 4 bytes): uint32_t refcount (_InterlockedIncrement on addref, _InterlockedDecrement on release)
//   +0x0C (R/W, 4 bytes): uint32_t count0xC (_InterlockedDecrement on release)
//
// Callees [V]:
//   - sub_eea6040 (boundary/vendor, via data slot 0xF99FFA0): 2 calls
//     0x5699c35  call qword ptr [0xF99FFA0]   (virtual destructor vfptr[0](oldObj))
//     0x5699c4b  call qword ptr [0xF99FFA0]   (virtual delete vfptr[1](oldObj))
//   - sub_5699e30 (lift set, pass body B, 0x5699e30): address taken as r8 function pointer,
//     passed to sub_bc61560; NOT called by this function.
//   - sub_bc61560 (lift set, custom item submit, 0xbc61560): tail jump at 0x5699c70.
//
// Offset constants for the pass object (a0/RCX).
static constexpr std::size_t kPassOffset0xA8 = 0xA8;
static constexpr std::size_t kPassOffset0xB0 = 0xB0;
static constexpr std::size_t kPassOffset0xB8 = 0xB8;

// Offset constants for the item object (a1/RDX).
static constexpr std::size_t kItemOffset0x00 = 0x00;
static constexpr std::size_t kItemOffset0x08 = 0x08;
static constexpr std::size_t kItemOffset0x10 = 0x10;

// Offset constants for the obj8 object (pointed to by item+0x8 / pass+0xB0).
static constexpr std::size_t kObj8Offset0x08 = 0x08;
static constexpr std::size_t kObj8Offset0x10 = 0x10;

// Offset constants for the refcounted object.
static constexpr std::size_t kRefcountedOffsetVfptr = 0x00;
static constexpr std::size_t kRefcountedOffsetRefcount = 0x08;
static constexpr std::size_t kRefcountedOffsetCount0xC = 0x0C;

struct sub_5699be0_pass {
    std::uint8_t pad0x00[0xA8];   // padding to reach +0xA8
    void* field0xA8;              // +0xA8 [W] pointer from item+0x0
    void* field0xB0;              // +0xB0 [W] pointer to obj8 object
    void* field0xB8;              // +0xB8 [R/W] refcounted object pointer
};

struct sub_5699be0_item {
    void* field0x00;     // +0x00 [R] pointer
    void* field0x08;     // +0x08 [R] pointer to obj8 object
    void* refCounted;    // +0x10 [R] pointer to refcounted object
};

struct sub_5699be0_obj8 {
    std::uint8_t pad0x00[0x08];
    std::uint16_t field0x08;   // +0x08 [R] u16 flags
    std::uint8_t pad0x0a[0x10 - 0x0a];
    void* field0x10;     // +0x10 [R] pointer
};

struct sub_5699be0_refcounted {
    void* vfptr;             // +0x00 [R] vfptr
    std::uint32_t refcount;  // +0x08 [R/W] _InterlockedIncrement / _InterlockedDecrement
    std::uint32_t count0xC;  // +0x0C [R/W] _InterlockedDecrement
};

struct sub_5699be0Layout {
    static_assert(offsetof(sub_5699be0_pass, field0xA8) == kPassOffset0xA8,
                  "sub_5699be0_pass: field0xA8 at +0xA8");
    static_assert(offsetof(sub_5699be0_pass, field0xB0) == kPassOffset0xB0,
                  "sub_5699be0_pass: field0xB0 at +0xB0");
    static_assert(offsetof(sub_5699be0_pass, field0xB8) == kPassOffset0xB8,
                  "sub_5699be0_pass: field0xB8 at +0xB8");
    static_assert(offsetof(sub_5699be0_item, field0x00) == kItemOffset0x00,
                  "sub_5699be0_item: field0x00 at +0x00");
    static_assert(offsetof(sub_5699be0_item, field0x08) == kItemOffset0x08,
                  "sub_5699be0_item: field0x08 at +0x08");
    static_assert(offsetof(sub_5699be0_item, refCounted) == kItemOffset0x10,
                  "sub_5699be0_item: refCounted at +0x10");
    static_assert(offsetof(sub_5699be0_obj8, field0x08) == kObj8Offset0x08,
                  "sub_5699be0_obj8: field0x08 at +0x08");
    static_assert(offsetof(sub_5699be0_obj8, field0x10) == kObj8Offset0x10,
                  "sub_5699be0_obj8: field0x10 at +0x10");
    static_assert(offsetof(sub_5699be0_refcounted, vfptr) == kRefcountedOffsetVfptr,
                  "sub_5699be0_refcounted: vfptr at +0x00");
    static_assert(offsetof(sub_5699be0_refcounted, refcount) == kRefcountedOffsetRefcount,
                  "sub_5699be0_refcounted: refcount at +0x08");
    static_assert(offsetof(sub_5699be0_refcounted, count0xC) == kRefcountedOffsetCount0xC,
                  "sub_5699be0_refcounted: count0xC at +0x0C");
    static_assert(sizeof(void*) == 8, "sub_5699be0: x64 pointers are 8 bytes");

    static_assert(sizeof(sub_5699be0_pass) == 0xC0, "sub_5699be0_pass: size reaches +0xC0");
    static_assert(sizeof(sub_5699be0_item) == 0x18, "sub_5699be0_item: size is 0x18");
    static_assert(sizeof(sub_5699be0_obj8) == 0x18, "sub_5699be0_obj8: size is 0x18");
    static_assert(sizeof(sub_5699be0_refcounted) == 0x10, "sub_5699be0_refcounted: size is 0x10");
};

namespace native {

// sub_5699e30 (lift set, pass body B, 0x5699e30, size 0xc4): forward-declared here.
// Its address is taken (lea r8,[0x5699E30]) and passed to sub_bc61560 as r8;
// it is NOT called by this function. Signature recovered from its disassembly:
// rcx = pass object, returns void [V].
void sub_5699e30(void* passObject);

namespace bgfx {

// sub_bc61560 (lift set, custom item submit, 0xbc61560, size 0x372): forward-declared here.
// Called via tail jump (jmp 0xBC61560) at the end of this function.
// Signature: rcx = obj8+0x10 pointer, rdx = u16 flags at obj8+8, r8 = callback (&sub_5699e30),
// r9 = pass object; returns void [V].
extern "C" void sub_bc61560(void* rcxArg, std::uint16_t rdxArg, void* callback, void* passObject);

} // namespace bgfx

// sub_5699be0(void* passObj, void* item) -> void
void sub_5699be0(void* passObj, void* item);

} // namespace native
