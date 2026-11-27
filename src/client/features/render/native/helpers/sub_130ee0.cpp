// LIFT 0x130ee0 size 0xfb 1.26.62.01 sub_130ee0
#include "client/features/render/native/helpers/sub_130ee0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

static_assert(sizeof(std::uintptr_t) == 8, "130ee0: uintptr_t is 8 bytes on x64");
static_assert(sizeof(std::uint32_t) == 4, "130ee0: uint32_t is 4 bytes on x64");

namespace native::helpers {

// Verbatim call instructions from the disassembly of [0x130ee0, 0x130fdb) (rdis dis output):
//   0x130f44  call qword ptr [0xF99FFA0]  ; vtable[0](obj) = destroy, via jmp-rax thunk, refcounted object at element+0x8
//   0x130f5d  call qword ptr [0xF99FFA0]  ; vtable[1](obj) = dealloc, via jmp-rax thunk, refcounted object at element+0x8
//   0x130f93  call 0xE935700              ; direct, sub_e935700 (lift: `jmp 0x392960`, depth 0)
//   0x130fd4  call qword ptr [0xF9A8C78]  ; data slot, loader-patched invalid-parameter handler (noreturn), 5 zero args
// No lift-set callees other than sub_e935700 (called directly, forward-declared in the header).
// UNRESOLVED CALL = none.

using DestroyFn = void (*)(void*);
using DeallocFn = void (*)(void*);

static DestroyFn vtableDestroy(void* obj) {  // 0x130f3a  mov rax,[r12]; 0x130f3e  mov rax,[rax]   (vtable[0] at +0x00)
    void** vt = reinterpret_cast<void**>(obj);
    return reinterpret_cast<DestroyFn>(vt[0]);
}
static DeallocFn vtableDealloc(void* obj) {  // 0x130f52  mov rax,[r12]; 0x130f56  mov rax,[rax+8] (vtable[1] at +0x08; vptr re-read after destroy)
    void** vt = reinterpret_cast<void**>(obj);
    return reinterpret_cast<DeallocFn>(vt[1]);
}

// 0x130fc1..0x130fdb: the validation-failure path. [rsp+0x20] = 0 (5th stack arg), ecx=edx=r8d=r9d=0
// (first four args), then `0x130fd4  call qword ptr [0xF9A8C78]` -- the data slot is loader-patched
// at runtime; the disassembly follows the call with int3 padding, so the target is noreturn and
// control never continues here.
[[noreturn]] static void reportValidationFailure() {
    //   0x130fc1  mov qword ptr [rsp+0x20],0
    //   0x130fca  xor ecx,ecx
    //   0x130fcc  xor edx,edx
    //   0x130fce  xor r8d,r8d
    //   0x130fd1  xor r9d,r9d
    //   0x130fd4  call qword ptr [0xF9A8C78]
    using Watson = std::uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, std::uintptr_t);
    reinterpret_cast<Watson>(*reinterpret_cast<std::uintptr_t*>(
        RewriteRegistry::imageBase() + 0xF9A8C78))(nullptr, nullptr, nullptr, 0, 0);
    //   0x130fda  int3   (padding after the noreturn call; unreachable)
    __assume(false);
}

void sub_130ee0(sub_130ee0_state* self, std::uintptr_t arg2, std::uintptr_t arg3, std::uintptr_t arg4) {
    // x64 Microsoft ABI: rcx = self, rdx = arg2, r8 = arg3, r9 = arg4.
    // Returns void: no instruction of the range writes rax with a defined value, so the return
    // register is dead at ret.

    // Prologue/epilogue (stack frame only, no observable effect):
    //   0x130ee0..0x130eea  push r15, r14, r13, r12, rsi, rdi, rbx
    //   0x130eeb            sub rsp,0x30
    //   0x130eef  mov rsi,r9         (arg4 saved)
    //   0x130ef2  mov r14,r8         (arg3 saved)
    //   0x130ef5  mov rbx,rdx        (arg2 saved)
    //   0x130ef8  mov rdi,rcx        (self saved)
    //   ...
    //   0x130fb1            add rsp,0x30
    //   0x130fb5..0x130fbe  pop rbx, rdi, rsi, r12, r13, r14, r15
    //   0x130fc0            ret

    // All locals declared up front so that goto never jumps over an initialization.
    std::uintptr_t r15 = self->f0;     // 0x130efb  mov r15,[rcx]      (r15 = self->f0)
    std::uintptr_t r13 = self->f8;     // 0x130f07  mov r13,[rdi+8]    (r13 = self->f8)
    sub_130ee0_refcounted* r12 = nullptr; // 0x130f29  mov r12,[r15+8]  (refcounted object ptr)
    std::uintptr_t rdx = 0;            // 0x130f68  mov rdx,[rdi+0x10] (rdx = self->f10)
    std::uintptr_t rax = 0;            // 0x130f78  mov rax,[r15-8]    (rax = *(r15 - 8))
    std::uintptr_t delta = 0;          // 0x130f80  sub r15,rax        (delta = (r15-8) - *(r15-8))

    // 0x130ee0..0x130f07: block 0
    //   0x130efe  test r15,r15
    //   0x130f01  je 0x130F98        -> if self->f0 == 0 goto L_0x130f98
    if (r15 == 0) goto L_0x130f98;

    // 0x130f07..0x130f10: block 1
    //   0x130f0b  cmp r15,r13
    //   0x130f0e  jne short 0x130F29 -> if self->f0 != self->f8 goto L_0x130f29
    //   0x130f10  jmp short 0x130F68 -> else goto L_0x130f68
    if (r15 != r13) goto L_0x130f29;
    goto L_0x130f68;

L_0x130f20:
    // 0x130f20..0x130f29: block 4 (from 130f30, 130f38, 130f50, 130f63)
    //   0x130f20  add r15,0x10
    //   0x130f24  cmp r15,r13
    //   0x130f27  je short 0x130F65  -> if r15 == self->f8 goto L_0x130f65
    //   0x130f27  jne -> L_0x130f29
    r15 += 0x10;
    if (r15 == r13) goto L_0x130f65;
    goto L_0x130f29;

L_0x130f29:
    // 0x130f29..0x130f32: block 5
    //   0x130f29  mov r12,[r15+8]    (r12 = *(r15 + 8), refcounted object pointer)
    //   0x130f2d  test r12,r12
    //   0x130f30  je short 0x130F20  -> if r12 == 0 goto L_0x130f20
    r12 = reinterpret_cast<sub_130ee0_refcounted*>(
        *reinterpret_cast<std::uintptr_t*>(r15 + 8));
    if (r12 == nullptr) goto L_0x130f20;

    // 0x130f32..0x130f3a: block 6
    //   0x130f32  lock dec dword ptr [r12+8]   (strong refcount--)
    //   0x130f38  jne short 0x130F20         -> if result != 0 goto L_0x130f20
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&r12->strong)) != 0) goto L_0x130f20;

    // 0x130f3a..0x130f52: block 7
    //   0x130f3a  mov rax,[r12]          (vptr)
    //   0x130f3e  mov rax,[rax]          (vtable[0] = destroy)
    //   0x130f41  mov rcx,r12
    //   0x130f44  call qword ptr [0xF99FFA0]  (destroy(r12) via jmp-rax thunk)
    //   0x130f4a  lock dec dword ptr [r12+0xC]   (weak refcount--)
    //   0x130f50  jne short 0x130F20     -> if result != 0 goto L_0x130f20
    vtableDestroy(r12)(r12);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&r12->weak)) != 0) goto L_0x130f20;

    // 0x130f52..0x130f65: block 8
    //   0x130f52  mov rax,[r12]          (vptr re-read after destroy)
    //   0x130f56  mov rax,[rax+8]        (vtable[1] = dealloc)
    //   0x130f5a  mov rcx,r12
    //   0x130f5d  call qword ptr [0xF99FFA0]  (dealloc(r12) via jmp-rax thunk)
    //   0x130f63  jmp short 0x130F20     -> goto L_0x130f20
    vtableDealloc(r12)(r12);
    goto L_0x130f20;

L_0x130f65:
    // 0x130f65..0x130f68: block 9
    //   0x130f65  mov r15,[rdi]        (r15 = self->f0, re-read)
    r15 = self->f0;

L_0x130f68:
    // 0x130f68..0x130f78: block 10
    //   0x130f6c  sub rdx,r15          (rdx = self->f10 - self->f0 = size)
    //   0x130f6f  cmp rdx,0x1000
    //   0x130f76  jb short 0x130F90    -> if size <u 0x1000 goto L_0x130f90
    rdx = self->f10 - r15;
    if (rdx < 0x1000ull) goto L_0x130f90;

    // 0x130f78..0x130f89: block 11
    //   0x130f78  mov rax,[r15-8]      (rax = *(r15 - 8), heap header)
    //   0x130f7c  add r15,0xFFFFFFFFFFFFFFF8   (r15 -= 8)
    //   0x130f80  sub r15,rax          (r15 = (r15 - 8) - *(r15 - 8) = delta)
    //   0x130f83  cmp r15,0x20
    //   0x130f87  jae short 0x130FC1   -> if delta >=u 0x20 goto L_0x130fc1
    rax = *reinterpret_cast<std::uintptr_t*>(r15 - 8);
    delta = (r15 - 8) - rax;
    if (delta >= 0x20ull) goto L_0x130fc1;

    // 0x130f89..0x130f90: block 12
    //   0x130f89  add rdx,0x27         (rdx = size + 0x27)
    //   0x130f8d  mov r15,rax          (r15 = heap header)
    rdx += 0x27;
    r15 = rax;

L_0x130f90:
    // 0x130f90..0x130f98: block 13
    //   0x130f90  mov rcx,r15
    //   0x130f93  call 0xE935700       (sub_e935700(r15, rdx))
    sub_e935700(r15, rdx);

L_0x130f98:
    // 0x130f98..0x130fc1: block 14
    //   0x130f98  mov [rdi],rbx        (self->f0 = arg2)
    //   0x130f9b  shl r14,4            (r14 = arg3 << 4)
    //   0x130f9f  add r14,rbx          (r14 = (arg3 << 4) + arg2)
    //   0x130fa2  mov [rdi+8],r14      (self->f8 = (arg3 << 4) + arg2)
    //   0x130fa6  shl rsi,4            (rsi = arg4 << 4)
    //   0x130faa  add rsi,rbx          (rsi = (arg4 << 4) + arg2)
    //   0x130fad  mov [rdi+0x10],rsi   (self->f10 = (arg4 << 4) + arg2)
    self->f0 = arg2;
    self->f8 = (arg3 << 4) + arg2;
    self->f10 = (arg4 << 4) + arg2;
    return;

L_0x130fc1:
    // 0x130fc1..0x130fdb: block 15 (validation failure, noreturn)
    reportValidationFailure();
    __assume(false);
}

static native::Footprint sub_130ee0_footprint(sub_130ee0_state* self,
                                              std::uintptr_t arg2,
                                              std::uintptr_t arg3,
                                              std::uintptr_t arg4) {
    // The function writes only inside *self ([0x00, 0x18)): the three pointer fields.
    // Refcount writes to objects in the buffer, the virtual-call targets and sub_e935700's
    // frees happen outside the function and cannot be declared statically.
    return {{self, 0x18ull}};
}

LIFT_FN(sub_130ee0, "sub_130ee0", 0x130ee0, sub_130ee0, sub_130ee0_footprint);

} // namespace native::helpers
