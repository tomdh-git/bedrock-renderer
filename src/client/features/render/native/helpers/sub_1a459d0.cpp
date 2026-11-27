// LIFT 0x1a459d0 size 0xb9 1.26.62.01 sub_1a459d0
#include "sub_1a459d0.h"

#include "client/features/render/native/Lift.h"
#include <intrin.h>

// sub_e935700 is lift set; forward-declared here rather than including sub_e935700.h
// (that unit's header has a static_assert on its own partial-layout type that MSVC
// rejects). Signature matches sub_e935700.h exactly: void* sub_e935700(void* a0).
namespace native {
void* sub_e935700(void* a0);


// sub_1a459d0 (0x1a459d0, size 0xb9, 1.26.62.01, "sub_1a459d0").
//
// Teardown of the object passed in RCX (a0 = this):
//   0x1a459d9  rdi = *(this + 0x38);  if (rdi != 0) {
//       lock dec dword ptr [rdi + 8];      if it hit 0:  vfptr[0](rdi)  via call qword ptr [0xF99FFA0] (sub_eea6040 thunk: jmp rax)
//       lock dec dword ptr [rdi + 0xC];    if it hit 0:  vfptr[1](rdi)  via call qword ptr [0xF99FFA0]
//   }
//   size = *(u64 *)(this + 0x28);
//   if (size >= 0x10) {
//       buffer = *(void **)(this + 0x10);
//       if ((u64)(size + 1) < 0x1000)        sub_e935700(buffer);
//       else {
//           bias = (u64)buffer - 8 - *(u64 *)(buffer - 8);
//           if (bias >= 0x20)                failfast: call qword ptr [0xF9A8C78] (0,0,0,0); int3;
//           sub_e935700(*(void **)(buffer - 8));
//       }
//   }
//   *(u64 *)(this + 0x20) = 0;
//   *(u64 *)(this + 0x28) = 0xF;
//   *(u8 *)(this + 0x10) = 0;          // one byte only; bytes 0x11..0x17 are not written by the original
//   edx = 0x48;                        // dead store: sub_e935700 -> sub_392960 overwrites RDX first
//   return sub_e935700(this);          // 0x1a45a6a jmp 0xE935700 (tail call; result in RAX)
//
// Calls [V]: 0x1a459f1 call qword ptr [0xF99FFA0]; 0x1a45a07 call qword ptr [0xF99FFA0]
//   (sub_eea6040, boundary/vendor via boundary::g_eea6040_thunk);
//   0x1a45a43 call 0xE935700 and 0x1a45a6a jmp 0xE935700 (native::sub_e935700, lift set);
//   0x1a45a82 call qword ptr [0xF9A8C78] (failfast path, target read from the data slot).
// No null guards or SEH beyond the original's own tests; no stubs; no skipped branches.

void* sub_1a459d0(void* a0) {
    auto* const self = reinterpret_cast<sub_1a459d0_this*>(a0);   // 0x1a459d6 mov rsi,rcx  (a0 arrives in RCX)

    // 0x1a459d0..0x1a459d6: prologue push rsi; push rdi; sub rsp,0x28
    // 0x1a459d6  mov rsi,rcx

    // 0x1a459d9  mov rdi,[rcx+0x38]        R a0+0x38 (refcounted object)
    // 0x1a459dd  test rdi,rdi
    // 0x1a459e0  je short 0x1A45A0D        object == 0 -> skip the release sequence
    void* const object = self->object;   // 0x1a459d9 mov rdi,[rcx+0x38]
    if (object != nullptr) {             // 0x1a459dd test rdi,rdi ; 0x1a459e0 je short 0x1A45A0D
        auto* const obj =
            reinterpret_cast<sub_1a459d0_refcounted*>(object);

        // 0x1a459e2  lock dec dword ptr [rdi+8]      W *(object+0x8)
        // 0x1a459e6  jne short 0x1A45A0D             skip destructor when result != 0
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj->refs0x08)) == 0) {
            // refcount reached 0 -> virtual destructor vfptr[0](object)
            // 0x1a459e8  mov rax,[rdi]        R object+0x00 (vfptr)
            // 0x1a459eb  mov rax,[rax]        R vfptr[0] (destructor) -> RAX
            // 0x1a459ee  mov rcx,rdi          RCX = object
            // 0x1a459f1  call qword ptr [0xF99FFA0]   -> sub_eea6040: jmp rax -> vfptr[0](object)
            void** const vfptr = *reinterpret_cast<void***>(object);   // 0x1a459e8/0x1a459eb vfptr[0] load
            boundary::g_eea6040_thunk(object, vfptr[0]);   // 0x1a459f1 call qword ptr [0xF99FFA0]
        }

        // 0x1a459f7  lock dec dword ptr [rdi+0xC]    W *(object+0xC)
        // 0x1a459fb  jne short 0x1A45A0D             skip operator delete when result != 0
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj->refs0x0c)) == 0) {
            // count0xC reached 0 -> virtual delete vfptr[1](object)
            // 0x1a459fd  mov rax,[rdi]        R object+0x00 (vfptr)
            // 0x1a45a00  mov rax,[rax+8]      R vfptr[1] (operator delete) -> RAX
            // 0x1a45a04  mov rcx,rdi          RCX = object
            // 0x1a45a07  call qword ptr [0xF99FFA0]   -> sub_eea6040: jmp rax -> vfptr[1](object)
            void** const vfptr = *reinterpret_cast<void***>(object);   // 0x1a459fd/0x1a45a00 vfptr[1] load
            boundary::g_eea6040_thunk(object, vfptr[1]);   // 0x1a45a07 call qword ptr [0xF99FFA0]
        }
    }

    // 0x1a45a0d  mov rax,[rsi+0x28]      R a0+0x28 (buffer size)
    std::uint64_t const size = self->size;   // 0x1a45a0d mov rax,[rsi+0x28]

    // 0x1a45a11  cmp rax,0x10
    // 0x1a45a15  jb short 0x1A45A48       size < 0x10 -> small-buffer reset, no free
    if (size >= 0x10) {
        // 0x1a45a17  mov rcx,[rsi+0x10]     R a0+0x10 (heap buffer pointer)
        // 0x1a45a1b  lea rdx,[rax+1]        size + 1
        // 0x1a45a1f  cmp rdx,0x1000
        // 0x1a45a26  jb short 0x1A45A43   size + 1 < 0x1000 -> free path A
        void* const buffer = self->buffer;   // 0x1a45a17 mov rcx,[rsi+0x10]
        if ((size + 1) < 0x1000) {           // 0x1a45a1b lea rdx,[rax+1] ; 0x1a45a1f cmp rdx,0x1000 ; 0x1a45a26 jb short 0x1A45A43
            // 0x1a45a43  call 0xE935700     -> native::sub_e935700(buffer)  (RDX = size + 1, dead inside the callee)
            native::sub_e935700(buffer);     // 0x1a45a43 call 0xE935700
        } else {
            // 0x1a45a28  mov r8,[rcx-8]             R *(buffer - 8)
            // 0x1a45a2c  add rcx,0xFFFFFFFFFFFFFFF8
            // 0x1a45a30  sub rcx,r8
            // 0x1a45a33  cmp rcx,0x20
            // 0x1a45a37  jae short 0x1A45A6F        bias >= 0x20 -> failfast
            uintptr_t const bias = reinterpret_cast<uintptr_t>(buffer) - 8 -
                                   *reinterpret_cast<uintptr_t*>(
                                       reinterpret_cast<char*>(buffer) - 8);
            if (bias >= 0x20) {              // 0x1a45a33 cmp rcx,0x20 ; 0x1a45a37 jae short 0x1A45A6F
                // 0x1a45a6f..0x1a45a89 failfast path:
                //   mov qword ptr [rsp+0x20],0   (dead home-slot store; not observable after return)
                //   xor ecx,ecx ; xor edx,edx ; xor r8d,r8d ; xor r9d,r9d
                //   0x1a45a82  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
                //   0x1a45a88  int3                        trap if the call returns
                using failfast_fn = void(__cdecl*)(void*, void*, void*, void*);
                failfast_fn const failfast = reinterpret_cast<failfast_fn>(
                    *reinterpret_cast<uintptr_t*>(
                        RewriteRegistry::imageBase() + sub_1a459d0Layout::kFailfastSlotRva));
                failfast(nullptr, nullptr, nullptr, nullptr);   // 0x1a45a82 call qword ptr [0xF9A8C78]
                __debugbreak();                                 // 0x1a45a88 int3 (only reached if failfast returns)
                __assume(0);
            }
            // 0x1a45a39  add rax,0x28            size + 0x28 (dead: callee overwrites RDX first)
            // 0x1a45a3d  mov rdx,rax
            // 0x1a45a40  mov rcx,r8              [buffer - 8]
            // 0x1a45a43  call 0xE935700          -> native::sub_e935700(*(buffer - 8))
            native::sub_e935700(
                *reinterpret_cast<void**>(reinterpret_cast<char*>(buffer) - 8));  // 0x1a45a43 call 0xE935700
        }
    }

    // 0x1a45a48  mov qword ptr [rsi+0x20],0     W a0+0x20 = 0
    // 0x1a45a50  mov qword ptr [rsi+0x28],0xF   W a0+0x28 = 0xF
    // 0x1a45a58  mov byte ptr [rsi+0x10],0      W a0+0x10 byte = 0
    self->field0x20 = 0;                     // 0x1a45a48 mov qword ptr [rsi+0x20],0
    self->size = 0x0F;                       // 0x1a45a50 mov qword ptr [rsi+0x28],0xF
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<char*>(self) + 0x10) = 0;  // 0x1a45a58 mov byte ptr [rsi+0x10],0

    // 0x1a45a5c  mov edx,0x48                 dead store: sub_e935700->sub_392960 overwrites RDX
    //              before any read; the value is never observable.
    std::uint32_t const dead_edx = 0x48u;    // 0x1a45a5c mov edx,0x48
    (void)dead_edx;

    // 0x1a45a61  mov rcx,rsi                  RCX = this
    // 0x1a45a64  add rsp,0x28
    // 0x1a45a68  pop rdi
    // 0x1a45a69  pop rsi
    // 0x1a45a6a  jmp 0xE935700                tail call -> native::sub_e935700(this)
    return native::sub_e935700(self);        // 0x1a45a6a jmp 0xE935700 (tail call; result returned in RAX)
}

} // namespace native

LIFT_FN(sub_1a459d0, "sub_1a459d0", 0x1a459d0, ::native::sub_1a459d0, nullptr);

#if 0
// Verbatim instructions of [0x1a459d0, 0x1a45a89) (rdis dis 0x1a459d0 0xb9);
// machine-checked by tools/sigs/verify_oc.py against the exe.
0x1a459d0  push rsi
0x1a459d1  push rdi
0x1a459d2  sub rsp,0x28
0x1a459d6  mov rsi,rcx
0x1a459d9  mov rdi,[rcx+0x38]
0x1a459dd  test rdi,rdi
0x1a459e0  je short 0x1A45A0D
0x1a459e2  lock dec dword ptr [rdi+8]
0x1a459e6  jne short 0x1A45A0D
0x1a459e8  mov rax,[rdi]
0x1a459eb  mov rax,[rax]
0x1a459ee  mov rcx,rdi
0x1a459f1  call qword ptr [0xF99FFA0]
0x1a459f7  lock dec dword ptr [rdi+0xC]
0x1a459fb  jne short 0x1A45A0D
0x1a459fd  mov rax,[rdi]
0x1a45a00  mov rax,[rax+8]
0x1a45a04  mov rcx,rdi
0x1a45a07  call qword ptr [0xF99FFA0]
0x1a45a0d  mov rax,[rsi+0x28]
0x1a45a11  cmp rax,0x10
0x1a45a15  jb short 0x1A45A48
0x1a45a17  mov rcx,[rsi+0x10]
0x1a45a1b  lea rdx,[rax+1]
0x1a45a1f  cmp rdx,0x1000
0x1a45a26  jb short 0x1A45A43
0x1a45a28  mov r8,[rcx-8]
0x1a45a2c  add rcx,0xFFFFFFFFFFFFFFF8
0x1a45a30  sub rcx,r8
0x1a45a33  cmp rcx,0x20
0x1a45a37  jae short 0x1A45A6F
0x1a45a39  add rax,0x28
0x1a45a3d  mov rdx,rax
0x1a45a40  mov rcx,r8
0x1a45a43  call 0xE935700
0x1a45a48  mov qword ptr [rsi+0x20],0
0x1a45a50  mov qword ptr [rsi+0x28],0xF
0x1a45a58  mov byte ptr [rsi+0x10],0
0x1a45a5c  mov edx,0x48
0x1a45a61  mov rcx,rsi
0x1a45a64  add rsp,0x28
0x1a45a68  pop rdi
0x1a45a69  pop rsi
0x1a45a6a  jmp 0xE935700
0x1a45a6f  mov qword ptr [rsp+0x20],0
0x1a45a78  xor ecx,ecx
0x1a45a7a  xor edx,edx
0x1a45a7c  xor r8d,r8d
0x1a45a7f  xor r9d,r9d
0x1a45a82  call qword ptr [0xF9A8C78]
0x1a45a88  int3
#endif
