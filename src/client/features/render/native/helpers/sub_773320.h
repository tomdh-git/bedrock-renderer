#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/native/Lift.h"
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_773320 (0x773320, size 0xc9, 1.26.62.01).
//
//   0x773320  push rbp                                           ; prologue
//   0x773321  push rsi                                           ; prologue
//   0x773322  sub rsp,0x48                                       ; prologue
//   0x773326  lea rbp,[rsp+0x40]                                 ; frame
//   0x77332b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE             ; cookie slot marker (dead store)
//   0x773333  mov [rbp-8],rdx                                    ; spill a2
//   0x773337  mov eax,[rcx+0xB0]                                 ; state = a0+0xB0
//   0x77333d  cmp eax,1
//   0x773340  je short 0x7733A9                                  ; state==1 -> release
//   0x773342  mov rdx,[rbp-8]                                    ; rdx = a2
//   0x773346  cmp eax,3
//   0x773349  je short 0x773363                                  ; state==3 -> zero obj+0x30, then block build
//   0x77334b  cmp eax,2
//   0x77334e  jne short 0x77336D                                 ; state!=2 -> block build
//   0x773350  mov rcx,[rdx]                                      ; obj = [a2]
//   0x773353  mov rax,[rcx]                                      ; obj vfptr -> rax
//   0x773356  mov rax,[rax+8]                                    ; rax = obj->vfptr[1]
//   0x77335a  call qword ptr [0xF99FFA0]                         ; obj->vfptr[1](obj, a2)
//   0x773360  nop
//   0x773361  jmp short 0x7733A9                                 ; state==2 -> release (skip block/call2)
//   0x773363  mov rax,[rdx]                                      ; obj = [a2]
//   0x773366  mov dword ptr [rax+0x30],0                         ; obj+0x30 = 0
//   0x77336d  xorps xmm0,xmm0                                    ; zero block
//   0x773370  movaps [rbp-0x20],xmm0
//   0x773374  mov rax,[rdx+8]                                    ; cb = [a2+8]
//   0x773378  test rax,rax
//   0x77337b  je short 0x773387                                  ; cb==0 -> rax = 0
//   0x77337d  lock inc dword ptr [rax+8]                         ; cb->strong++
//   0x773381  mov rax,[rdx+8]                                    ; cb = [a2+8]
//   0x773385  jmp short 0x773389
//   0x773387  xor eax,eax                                        ; rax = 0
//   0x773389  mov rdx,[rdx]                                      ; rdx = [a2] = obj
//   0x77338c  mov [rbp-0x20],rdx                                 ; block.obj = obj
//   0x773390  mov [rbp-0x18],rax                                 ; block.cb = cb (or 0)
//   0x773394  mov rax,[rcx]                                      ; a0 vfptr -> rax
//   0x773397  mov rax,[rax+0x20]                                 ; rax = a0->vfptr[4]
//   0x77339b  lea rdx,[rbp-0x20]                                 ; rdx = &block
//   0x77339f  xor r8d,r8d                                        ; r8 = 0
//   0x7733a2  call qword ptr [0xF99FFA0]                         ; a0->vfptr[4](a0, &block, 0)
//   0x7733a8  nop
//   0x7733a9  mov rax,[rbp-8]                                    ; rax = a2
//   0x7733ad  mov rsi,[rax+8]                                    ; rsi = cb = [a2+8]
//   0x7733b1  test rsi,rsi
//   0x7733b4  je short 0x7733E2                                  ; cb==0 -> done
//   0x7733b6  lock dec dword ptr [rsi+8]                         ; cb->strong--
//   0x7733ba  jne short 0x7733E2                                 ; strong!=0 -> done
//   0x7733bc  mov rax,[rsi]                                      ; cb vfptr -> rax
//   0x7733bf  mov rax,[rax]                                      ; rax = cb->vfptr[0] (dtor)
//   0x7733c2  mov rcx,rsi                                        ; rcx = cb
//   0x7733c5  call qword ptr [0xF99FFA0]                         ; cb->vfptr[0](cb) dtor
//   0x7733cb  lock dec dword ptr [rsi+0xC]                       ; cb->weak--
//   0x7733cf  jne short 0x7733E2                                 ; weak!=0 -> done
//   0x7733d1  mov rax,[rsi]                                      ; cb vfptr -> rax
//   0x7733d4  mov rax,[rax+8]                                    ; rax = cb->vfptr[8] (dealloc)
//   0x7733d8  mov rcx,rsi                                        ; rcx = cb
//   0x7733db  call qword ptr [0xF99FFA0]                         ; cb->vfptr[8](cb) dealloc
//   0x7733e1  nop
//   0x7733e2  add rsp,0x48                                       ; epilogue
//   0x7733e6  pop rsi                                            ; epilogue
//   0x7733e7  pop rbp                                            ; epilogue
//   0x7733e8  ret                                                ; return void
//
// x64 Microsoft ABI: RCX = a0, RDX = a2, return void.
// Reads: a0+0xB0 (state); a2+0 (obj), a2+8 (cb); obj+0x30 (write when state==3); cb+8 (strong),
//   cb+0xC (weak); obj vfptr+8; a0 vfptr+0x20; cb vfptr+0, cb vfptr+8.
// Writes: obj+0x30 (state==3); block at [rbp-0x20] (stack); cb+8 (strong inc/dec), cb+0xC (weak dec).
// Calls: 4x sub_eea6040 via data slot 0xF99FFA0 (boundary/vendor thunk, jmp rax).

// Offset constants for 'a0' (RCX): object with state at +0xB0 and vfptr[0x20] method.
static constexpr std::size_t kA0StateOffset = 0xB0;       // std::uint32_t state at a0+0xB0
static constexpr std::size_t kA0VfptrSlotIndex = 4;       // a0->vfptr[4] (slot bytes 0x20)

// Offset constants for 'a2' (RDX): handle { obj at +0, cb at +8 }.
static constexpr std::size_t kA2ObjOffset = 0x00;         // void* obj = [a2]
static constexpr std::size_t kA2CbOffset = 0x08;          // void* cb  = [a2+8]

// Offset constants for 'obj' = [a2]: obj+0x30 is a u32 flag zeroed when state==3.
static constexpr std::size_t kObjFlagOffset = 0x30;       // std::uint32_t at obj+0x30

// Offset constants for 'cb' = [a2+8]: control block { vfptr, strong@+8, weak@+0xC }.
static constexpr std::size_t kCbStrongOffset = 0x08;      // std::uint32_t strong refcount
static constexpr std::size_t kCbWeakOffset = 0x0C;        // std::uint32_t weak refcount
static constexpr std::size_t kCbVfptrSlotDtor = 0;        // cb->vfptr[0] : destructor(cb)
static constexpr std::size_t kCbVfptrSlotDealloc = 1;     // cb->vfptr[8] : deallocator(cb)

// Block argument { obj, cb } at [rbp-0x20] (16 bytes).
static constexpr std::size_t kBlockObjOffset = 0x00;      // void* obj = [a2]
static constexpr std::size_t kBlockCbOffset = 0x08;       // void* cb  = [a2+8] (or 0)

// Indirect call slot (sub_eea6040, boundary/vendor thunk via data slot).
static constexpr std::uintptr_t kEea6040SlotRva = 0xF99FFA0;

struct sub_773320_a0 {
    std::uint8_t pad0x00[kA0StateOffset];
    std::uint32_t state;        // +0xB0 [R]
};

struct sub_773320_a2 {
    void* obj;                  // +0x00 [R] obj = [a2]
    void* cb;                   // +0x08 [R] cb  = [a2+8]
};

struct sub_773320_obj {
    std::uint8_t pad0x00[kObjFlagOffset];
    std::uint32_t field0x30;    // +0x30 [W when state==3] zeroed
};

struct sub_773320_cb {
    void* vfptr;                // +0x00 [R] cb->vfptr
    std::uint32_t strong;       // +0x08 [R/W] strong refcount
    std::uint32_t weak;         // +0x0C [R/W] weak refcount
};

struct sub_773320_block {
    void* obj;                  // +0x00 [W] = [a2]
    void* cb;                   // +0x08 [W] = [a2+8] or 0
};

struct sub_773320Layout {
    static_assert(offsetof(sub_773320_a0, state) == kA0StateOffset,
                  "sub_773320: a0 state at +0xB0");
    static_assert(offsetof(sub_773320_a2, obj) == kA2ObjOffset,
                  "sub_773320: a2 obj at +0x00");
    static_assert(offsetof(sub_773320_a2, cb) == kA2CbOffset,
                  "sub_773320: a2 cb at +0x08");
    static_assert(offsetof(sub_773320_obj, field0x30) == kObjFlagOffset,
                  "sub_773320: obj field at +0x30");
    static_assert(offsetof(sub_773320_cb, strong) == kCbStrongOffset,
                  "sub_773320: cb strong at +0x08");
    static_assert(offsetof(sub_773320_cb, weak) == kCbWeakOffset,
                  "sub_773320: cb weak at +0x0C");
    static_assert(offsetof(sub_773320_block, obj) == kBlockObjOffset,
                  "sub_773320: block obj at +0x00");
    static_assert(offsetof(sub_773320_block, cb) == kBlockCbOffset,
                  "sub_773320: block cb at +0x08");
    static_assert(kEea6040SlotRva == 0xF99FFA0, "sub_773320: indirect call slot at 0xF99FFA0");
    static_assert(sizeof(void*) == 8, "sub_773320: x64 pointers are 8 bytes");
};

namespace native {

// sub_eea6040 (0xeea6040, boundary/vendor): `jmp rax` thunk reached through data slot 0xF99FFA0.
// The caller loads RAX with the target function pointer (a vfptr slot) just before the call;
// RCX and RDX are forwarded by the `jmp rax` tail jump. (docs/data/native_boundary.tsv line 506.)
Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// sub_773320 (0x773320, 0xc9 bytes, 1.26.62.01): argument `a0` in RCX, `a2` in RDX, returns void.
// See the instruction block above for the instruction-by-instruction reversal.
void sub_773320(void* a0, void* a2);

} // namespace native
