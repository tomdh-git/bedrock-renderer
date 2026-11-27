// LIFT 0x66e6da0 size 0x11b 1.26.62.01 sub_66e6da0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_66e6da0.h"
#include "client/features/render/native/helpers/sub_67d0ff0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_66e6da0, "sub_66e6da0", 0x66e6da0, sub_66e6da0, nullptr);

// Verbatim call instructions from the disassembly of [0x66e6da0, 0x66e6ebb) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x66e6e25  call 0x67D0FF0
0x66e6e3e  call qword ptr [0xF99FFA0]
0x66e6e54  call qword ptr [0xF99FFA0]
0x66e6e73  call qword ptr [0xF99FFA0]
0x66e6e89  call qword ptr [0xF99FFA0]
0x66e6eb5  call 0xE951550
#endif

// 0xE951550 is the CRT __report_gsfailure boundary (docs/data/native_boundary.tsv: class crt),
// noreturn on stack-cookie mismatch. It takes the cookie ^ rsp probe value in RCX.
Boundary<std::uintptr_t, std::uintptr_t> sub_e951550("sub_e951550");

// 0xF99FFA0 holds the sub_eea6040 vendor thunk (a single `jmp rax`, docs/data/native_boundary.tsv:
// "0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)"). The caller loads RAX with
// the vtable slot to invoke and RCX with the refcounted object. Modelled here as a two-argument
// call sub_eea6040(obj, vfptr[N]), matching the pattern used by sub_568b9e0/sub_5699be0.
Boundary<std::uintptr_t, void*, void*> sub_eea6040("sub_eea6040");

// Layout assertions (mirrored from the header for liftcheck)
static_assert(offsetof(sub_66e6da0_rsp, f20) == 0x20, "sub_66e6da0 rsp+0x20 field");
static_assert(offsetof(sub_66e6da0_rsp, f28) == 0x28, "sub_66e6da0 rsp+0x28 field");
static_assert(offsetof(sub_66e6da0_rsp, f60) == 0x60, "sub_66e6da0 rsp+0x60 field");
static_assert(offsetof(sub_66e6da0_rdx, f0) == 0x0, "sub_66e6da0 rdx+0x0 field");
static_assert(offsetof(sub_66e6da0_rdx, f8) == 0x8, "sub_66e6da0 rdx+0x8 field");
static_assert(offsetof(sub_66e6da0_r8, f0) == 0x0, "sub_66e6da0 r8+0x0 field");
static_assert(offsetof(sub_66e6da0_r8, f8) == 0x8, "sub_66e6da0 r8+0x8 field");
static_assert(offsetof(sub_66e6da0_r8, f10) == 0x10, "sub_66e6da0 r8+0x10 field");
static_assert(offsetof(sub_66e6da0_r8, f20) == 0x20, "sub_66e6da0 r8+0x20 field");
static_assert(offsetof(sub_66e6da0_rdi, f0) == 0x0, "sub_66e6da0 rdi+0x0 field");
static_assert(offsetof(sub_66e6da0_rdi, f8) == 0x8, "sub_66e6da0 rdi+0x8 field");
static_assert(offsetof(sub_66e6da0_rdi, fc) == 0xc, "sub_66e6da0 rdi+0xc field");

// Releases one reference on a refcounted object, mirroring the release sequence at
// 0x66e6e2f..0x66e6e5a and 0x66e6e64..0x66e6e8f:
//   lock dec [obj+0x8]          (strong refcount)
//   if result == 0:
//       sub_eea6040(obj, *(void**)obj->f0)    // vfptr[0] = destructor
//       lock dec [obj+0xc]      (secondary refcount)
//       if result == 0:
//           sub_eea6040(obj, *(void**)(obj->f0 + 8))  // vfptr[1] = deallocator
static void release_refcounted(sub_66e6da0_rdi* obj) {
    if (obj == nullptr) {
        return;
    }
    if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj->f8)) == 0) {
        void* vtable = obj->f0;                                 // mov rax,[rdi]
        sub_eea6040(obj, *reinterpret_cast<void**>(vtable));    // mov rax,[rax] = vfptr[0]; call thunk
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(&obj->fc)) == 0) {
            sub_eea6040(obj, *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(vtable) + 8));  // vfptr[1]
        }
    }
}

void* sub_66e6da0(void* self, sub_66e6da0_rdx* a1, sub_66e6da0_r8* a2) {
    // 0x66e6da0..0x66e6dc0: prologue, stack cookie
    // 0x66e6da0  push rsi
    // 0x66e6da1  push rdi
    // 0x66e6da2  sub rsp,0x68
    // 0x66e6da6  mov rsi,rcx
    // 0x66e6da9  mov rax,[0x1230A0C0]
    // 0x66e6db0  xor rax,rsp
    // 0x66e6db3  mov [rsp+0x60],rax
    // 0x66e6db8  xorps xmm0,xmm0
    // 0x66e6dbb  movaps [rsp+0x20],xmm0
    std::uintptr_t cookie_stored;                              // [rsp+0x60]
    const std::uintptr_t rsp_proxy = reinterpret_cast<std::uintptr_t>(&cookie_stored);
    cookie_stored = __security_cookie ^ rsp_proxy;

    // 0x66e6dc0..0x66e6dd5: a1->f8 addref
    // 0x66e6dc0  mov rax,[rdx+8]       ; rax = a1->f8 (refcounted referent)
    // 0x66e6dc4  test rax,rax
    // 0x66e6dc7  je short 0x66E6DD3
    // 0x66e6dc9  lock inc dword ptr [rax+8]
    // 0x66e6dcd  mov rax,[rdx+8]
    sub_66e6da0_rdi* a1_obj = reinterpret_cast<sub_66e6da0_rdi*>(a1->f8);
    if (a1_obj != nullptr) {
        _InterlockedIncrement(reinterpret_cast<volatile long*>(&a1_obj->f8));
    }

    // 0x66e6dd5..0x66e6df0: store src.f0/f8 from a1; a2->f8 addref
    // 0x66e6dd5  mov rcx,[rdx]          ; [rsp+0x20] = a1->f0
    // 0x66e6dd8  mov [rsp+0x20],rcx
    // 0x66e6ddd  mov [rsp+0x28],rax     ; [rsp+0x28] = a1->f8
    // 0x66e6de2  movaps [rsp+0x30],xmm0
    // 0x66e6de7  mov rax,[r8+8]         ; rax = a2->f8
    // 0x66e6deb  test rax,rax
    // 0x66e6dee  je short 0x66E6DFA
    // 0x66e6df0  lock inc dword ptr [rax+8]
    // 0x66e6df4  mov rdi,[r8+8]         ; rdi = a2->f8
    sub_66e6da0_rdi* a2_obj = reinterpret_cast<sub_66e6da0_rdi*>(a2->f8);
    if (a2_obj != nullptr) {
        _InterlockedIncrement(reinterpret_cast<volatile long*>(&a2_obj->f8));
    }
    void* rdi = a2_obj;

    // 0x66e6dfc..0x66e6e25: build src object (sub_67d0ff0_rdx layout at [rsp+0x20]) from a2,
    // then call sub_67d0ff0(dest=self+8, src=&src).
    // 0x66e6dfc  mov rax,[r8]           ; [rsp+0x30] = a2->f0
    // 0x66e6dff  mov [rsp+0x30],rax
    // 0x66e6e04  mov [rsp+0x38],rdi     ; [rsp+0x38] = a2->f8
    // 0x66e6e09  movups xmm0,[r8+0x10]  ; [rsp+0x40..0x4f] = a2->f10[2]
    // 0x66e6e0e  movaps [rsp+0x40],xmm0
    // 0x66e6e13  mov rax,[r8+0x20]      ; [rsp+0x50] = a2->f20
    // 0x66e6e17  mov [rsp+0x50],rax
    // 0x66e6e1c  lea rcx,[rsi+8]        ; dest = self+8
    // 0x66e6e20  lea rdx,[rsp+0x20]     ; src = &stack object
    // 0x66e6e25  call 0x67D0FF0
    sub_67d0ff0_rdx src{};
    src.f0 = a1->f0;                                               // [rsp+0x20]
    src.f8 = a1_obj;                                               // [rsp+0x28]
    src.f10 = a2->f0;                                              // [rsp+0x30]
    src.f18 = a2_obj;                                              // [rsp+0x38]
    src.f20[0] = a2->f10[0];                                       // [rsp+0x40..0x47]
    src.f20[1] = a2->f10[1];                                       // [rsp+0x48..0x4f]
    src.f30 = a2->f20;                                             // [rsp+0x50]
    sub_67d0ff0(reinterpret_cast<sub_67d0ff0_rcx*>(reinterpret_cast<std::uint8_t*>(self) + 8), &src);

    // 0x66e6e2a..0x66e6e5a: release temp ref on a2->f8 (rdi)
    // 0x66e6e2a  test rdi,rdi
    // 0x66e6e2d  je short 0x66E6E5A
    // 0x66e6e2f  lock dec dword ptr [rdi+8]
    // 0x66e6e33  jne short 0x66E6E5A
    // 0x66e6e35..0x66e6e54: destructor/deallocator via sub_eea6040
    release_refcounted(reinterpret_cast<sub_66e6da0_rdi*>(rdi));

    // 0x66e6e5a..0x66e6e8f: release temp ref on a1->f8 ([rsp+0x28] = a1_obj)
    // 0x66e6e5a  mov rdi,[rsp+0x28]
    // 0x66e6e5f  test rdi,rdi
    // 0x66e6e62  je short 0x66E6E8F
    // 0x66e6e64  lock dec dword ptr [rdi+8]
    // 0x66e6e68  jne short 0x66E6E8F
    // 0x66e6e6a..0x66e6e89: destructor/deallocator via sub_eea6040
    release_refcounted(a1_obj);

    // 0x66e6e8f..0x66e6ea3: stack cookie verification, normal return
    // 0x66e6e8f  mov rax,[rsp+0x60]
    // 0x66e6e94  xor rax,rsp
    // 0x66e6e97  mov rcx,[0x1230A0C0]
    // 0x66e6e9e  cmp rcx,rax
    // 0x66e6ea1  jne short 0x66E6EAD
    // 0x66e6ea3  mov rax,rsi            ; rax = self
    // 0x66e6ea6  add rsp,0x68
    // 0x66e6eaa  pop rdi
    // 0x66e6eab  pop rsi
    // 0x66e6eac  ret
    if (__security_cookie == (cookie_stored ^ rsp_proxy)) {
        return self;
    }

    // 0x66e6ead..0x66e6ebb: cookie mismatch -> __report_gsfailure (noreturn)
    // 0x66e6ead  mov rcx,[rsp+0x60]
    // 0x66e6eb2  xor rcx,rsp
    // 0x66e6eb5  call 0xE951550
    sub_e951550(cookie_stored ^ rsp_proxy);
}

} // namespace native::helpers
