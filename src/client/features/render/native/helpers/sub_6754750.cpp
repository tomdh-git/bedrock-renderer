// LIFT 0x6754750 size 0x12f 1.26.62.01 sub_6754750
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_6754750.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

// Callee lifted by its own unit, declared in sub_e935700.h as
// `namespace native { void* sub_e935700(void* a0); }` and called here as
// native::sub_e935700. (The header itself is not included because its layout
// static_assert references a not-yet-complete type and breaks cppsyntax in this TU;
// the forward declaration below matches the definition's exact signature.)
namespace native {
void* sub_e935700(void* a0);
}

namespace native::helpers {

static native::Footprint sub_6754750_footprint(void* self) {
    // Writes only inside *self: f8 (+0x08), f10 (+0x10), f18 (+0x18), f20 (+0x20).
    // Refcount/object writes and sub_e935700's effects are outside *self and cannot be
    // declared statically (same convention as sub_130ee0).
    return {{self, 0x28ull}};
}

// Layout static_assert for 0x6754750 (source side).
static_assert(offsetof(sub_6754750_state, f20) == 0x20, "sub_6754750: layout static_assert");

// Verbatim call instructions from the disassembly of [0x6754750, 0x675487f) (rdis `fn` output).
// Preprocessor-excluded so the skeleton stays valid C++; parsed by tools/sigs/verify_oc.py.
// All calls resolved:
//   0x67547b1 / 0x67547c7  call qword ptr [0xF99FFA0]  -> vtable[0]=destroy / vtable[1]=dealloc
//                            of the refcounted object (rdi), called directly via the vptr
//                            (same convention as sub_130ee0); the thunk [0xF99FFA0]=sub_eea6040
//                            is a jmp-rax forwarder with no static target.
//   0x675481b / 0x6754852  call 0xE935700              -> native::sub_e935700 (lift set, called directly)
//   0x6754878              call qword ptr [0xF9A8C78]  -> noreturn fail handler (5 zeroed args)
// All calls resolved (no open callee).
#if 0
0x67547b1  call qword ptr [0xF99FFA0]
0x67547c7  call qword ptr [0xF99FFA0]
0x675481b  call 0xE935700
0x6754852  call 0xE935700
0x6754878  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x6754750, 0x675487f) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

namespace {

// 0x6754865..0x675487f: block 22 (validation failure, noreturn)
//   mov qword ptr [rsp+0x20],0      ; 5th stack argument = 0
//   xor ecx,ecx                     ; arg1 = 0
//   xor edx,edx                     ; arg2 = 0
//   xor r8d,r8d                     ; arg3 = 0
//   xor r9d,r9d                     ; arg4 = 0
//   call qword ptr [0xF9A8C78]      ; loader-patched fail handler (noreturn), 5 zeroed args
//   int3                            ; padding after the noreturn call (unreachable)
[[noreturn]] static void failfast() {
    using FailFn = std::uintptr_t(__cdecl*)(void*, void*, void*, void*, std::uintptr_t);
    reinterpret_cast<FailFn>(*reinterpret_cast<std::uintptr_t*>(
        RewriteRegistry::imageBase() + 0xF9A8C78ULL))(nullptr, nullptr, nullptr, nullptr, 0);
    __assume(false);
}

} // namespace

uintptr_t sub_6754750(void* self) {
    // x64 Microsoft ABI: rcx = self (state pointer). 0x6754757 mov rsi,rcx copies it to rsi.
    // Return value: RAX, maintained in the local `rax` and returned at block 21.
    auto* a0 = reinterpret_cast<sub_6754750_state*>(self);

    // All locals declared up front so that no goto jumps over an initialization
    // (same convention as sub_130ee0). These mirror the original register usage.
    std::uintptr_t rax = 0;
    std::uintptr_t rcx = 0;
    std::uintptr_t rdx = 0;
    std::uintptr_t rdi = 0;
    std::uintptr_t rbx = 0;
    sub_6754750_elem* elem = nullptr;
    sub_6754750_obj* obj = nullptr;

L_0x6754750:
    // 0x6754750..0x6754763: block 0 (prologue + count test)
    //   mov rsi,rcx
    //   mov rax,[rcx+0x20]   ; rax = a0->f20 (count)
    //   test rax,rax
    //   jne short 0x675477D  ; if count != 0 goto block 4
    //   jmp short 0x67547D7  ; else goto block 1
    rax = a0->f20;
    if (rax != 0) goto L_0x675477d;
    goto L_0x6754763;

L_0x6754763:
    // 0x6754763..0x6754765: block 1
    //   jmp short 0x67547D7
    // -> if jmp goto L_0x67547d7
    goto L_0x67547d7;

L_0x6754765:
    // 0x6754765..0x6754770: block 2 (unreachable padding)
    //   nop [rax+rax]
    // -> if fallthrough goto L_0x6754770
    goto L_0x6754770;

L_0x6754770:
    // 0x6754770..0x675477d: block 3 (count--)
    //   mov rax,[rsi+0x20]   ; rax = a0->f20
    //   dec rax
    //   mov [rsi+0x20],rax   ; a0->f20 = rax
    //   je short 0x67547CF   ; if rax == 0 goto block 8
    //   ... goto block 4
    rax = a0->f20;
    rax -= 1;
    a0->f20 = rax;
    if (rax == 0) goto L_0x67547cf;
    goto L_0x675477d;

L_0x675477d:
    // 0x675477d..0x67547a2: block 4 (fetch element, bump refcount object)
    //   mov rcx,[rsi+0x18]   ; rcx = a0->f18
    //   add rax,rcx; dec rax ; rax = count + f18 - 1
    //   mov rcx,[rsi+8]      ; rcx = a0->f8 (array base)
    //   mov rdx,[rsi+0x10]   ; rdx = a0->f10 (capacity)
    //   dec rdx; and rdx,rax ; rdx = (capacity-1) & (count+f18-1)
    //   mov rax,[rcx+rdx*8]  ; rax = array[idx] (element pointer)
    //   mov rdi,[rax+0x10]   ; rdi = element->f10 (refcounted object)
    //   test rdi,rdi
    //   je short 0x6754770   ; if obj == 0 goto block 3
    //   ... goto block 5
    rcx = a0->f18;
    rax += rcx;
    rax -= 1;
    rcx = reinterpret_cast<std::uintptr_t>(a0->f8);
    rdx = a0->f10;
    rdx -= 1;
    rdx &= rax;
    rax = reinterpret_cast<std::uintptr_t>(
        reinterpret_cast<sub_6754750_elem**>(rcx)[rdx]);
    elem = reinterpret_cast<sub_6754750_elem*>(rax);
    rdi = reinterpret_cast<std::uintptr_t>(elem->f10);
    if (rdi == 0) goto L_0x6754770;
    goto L_0x67547a2;

L_0x67547a2:
    // 0x67547a2..0x67547a8: block 5 (strong refcount--)
    //   lock dec dword ptr [rdi+8]   ; obj->f8 (strong)--
    //   jne short 0x6754770          ; if result != 0 goto block 3
    //   ... goto block 6
    obj = reinterpret_cast<sub_6754750_obj*>(rdi);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&obj->f8)) != 0)
        goto L_0x6754770;
    goto L_0x67547a8;

L_0x67547a8:
    // 0x67547a8..0x67547bd: block 6 (vtable[0] = destroy)
    //   mov rax,[rdi]; mov rax,[rax]   ; vtable[0]
    //   mov rcx,rdi
    //   call qword ptr [0xF99FFA0]     ; vtable[0](obj) = destroy, via jmp-rax thunk
    //   lock dec dword ptr [rdi+0xC]   ; obj->fc (weak)--
    //   jne short 0x6754770            ; if result != 0 goto block 3
    //   ... goto block 7
    {
        void** vt = reinterpret_cast<void**>(obj->f0);
        using DestroyFn = void (*)(void*);
        reinterpret_cast<DestroyFn>(vt[0])(obj);
    }
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(&obj->fc)) != 0)
        goto L_0x6754770;
    goto L_0x67547bd;

L_0x67547bd:
    // 0x67547bd..0x67547cf: block 7 (vtable[1] = dealloc)
    //   mov rax,[rdi]; mov rax,[rax+8]   ; vtable[1]
    //   mov rcx,rdi
    //   call qword ptr [0xF99FFA0]       ; vtable[1](obj) = dealloc, via jmp-rax thunk
    //   jmp short 0x6754770              ; goto block 3
    {
        void** vt = reinterpret_cast<void**>(obj->f0);
        using DeallocFn = void (*)(void*);
        reinterpret_cast<DeallocFn>(vt[1])(obj);
    }
    goto L_0x6754770;

L_0x67547cf:
    // 0x67547cf..0x67547d7: block 8
    //   mov qword ptr [rsi+0x18],0   ; a0->f18 = 0
    // -> if fallthrough goto L_0x67547d7
    a0->f18 = 0;
    goto L_0x67547d7;

L_0x67547d7:
    // 0x67547d7..0x67547e0: block 9 (array base test)
    //   mov rcx,[rsi+8]      ; rcx = a0->f8 (array base)
    //   test rcx,rcx
    //   je short 0x675485D   ; if array base == 0 goto block 21 (return)
    //   ... goto block 10
    rcx = reinterpret_cast<std::uintptr_t>(a0->f8);
    if (rcx == 0) goto L_0x675485d;
    goto L_0x67547e0;

L_0x67547e0:
    // 0x67547e0..0x67547ed: block 10 (capacity signed test)
    //   lea rbx,[rsi+8]      ; rbx = &a0->f8
    //   mov rdi,[rsi+0x10]   ; rdi = a0->f10 (capacity)
    //   test rdi,rdi
    //   jle short 0x675482A  ; if (int64)capacity <= 0 goto block 16
    //   ... goto block 11
    rbx = reinterpret_cast<std::uintptr_t>(&a0->f8);
    rdi = a0->f10;
    if (static_cast<std::int64_t>(rdi) <= 0) goto L_0x675482a;
    goto L_0x67547ed;

L_0x67547ed:
    // 0x67547ed..0x67547f2: block 11
    //   inc rdi
    //   jmp short 0x6754809
    // -> if jmp goto L_0x6754809
    rdi += 1;
    goto L_0x6754809;

L_0x67547f2:
    // 0x67547f2..0x6754800: block 12 (fallthrough padding)
    //   nop [rax+rax]
    // -> if fallthrough goto L_0x6754800
    goto L_0x6754800;

L_0x6754800:
    // 0x6754800..0x6754809: block 13 (loop decrement)
    //   dec rdi
    //   cmp rdi,1
    //   jbe short 0x6754822  ; if rdi <=u 1 goto block 16
    //   ... goto block 14
    rdi -= 1;
    if (rdi <= 1ull) goto L_0x6754822;
    goto L_0x6754809;

L_0x6754809:
    // 0x6754809..0x6754816: block 14 (fetch element to release)
    //   mov rax,[rbx]        ; rax = a0->f8 (array base)
    //   mov rcx,[rax+rdi*8-0x10]  ; rcx = arr[rdi-1] (element pointer)
    //   test rcx,rcx
    //   je short 0x6754800   ; if element == 0 goto block 13
    //   ... goto block 15
    rax = reinterpret_cast<std::uintptr_t>(a0->f8);
    {
        auto** arr = reinterpret_cast<sub_6754750_elem**>(rax);
        rcx = reinterpret_cast<std::uintptr_t>(arr[rdi - 1]);
    }
    if (rcx == 0) goto L_0x6754800;
    goto L_0x6754816;

L_0x6754816:
    // 0x6754816..0x6754822: block 15 (sub_e935700 on element)
    //   mov edx,0x18
    //   call 0xE935700       ; native::sub_e935700(element)  (RDX=0x18 not read by callee)
    //   jmp short 0x6754800  ; goto block 13
    native::sub_e935700(reinterpret_cast<void*>(rcx));
    goto L_0x6754800;

L_0x6754822:
    // 0x6754822..0x675482a: block 16 (re-read array base and capacity)
    //   mov rcx,[rsi+8]      ; rcx = a0->f8 (array base, re-read)
    //   mov rdi,[rsi+0x10]   ; rdi = a0->f10 (capacity, re-read)
    // -> if fallthrough goto L_0x675482a
    rcx = reinterpret_cast<std::uintptr_t>(a0->f8);
    rdi = a0->f10;
    goto L_0x675482a;

L_0x675482a:
    // 0x675482a..0x6754837: block 17 (capacity*8 vs 0x1000)
    //   shl rdi,3            ; rdi = capacity*8
    //   cmp rdi,0x1000
    //   jb short 0x675484F   ; if rdi <u 0x1000 goto block 20
    //   ... goto block 18
    rdi <<= 3;
    if (rdi < 0x1000ull) goto L_0x675484f;
    goto L_0x6754837;

L_0x6754837:
    // 0x6754837..0x6754848: block 18 (heap-header corruption check)
    //   mov rax,[rcx-8]      ; rax = *(arrayBase - 8) (heap header)
    //   add rcx,0xFFFFFFFFFFFFFFF8  ; rcx -= 8
    //   sub rcx,rax          ; rcx = (arrayBase-8) - *(arrayBase-8) = delta
    //   cmp rcx,0x20
    //   jae short 0x6754865  ; if delta >=u 0x20 goto block 22 (failfast)
    //   ... goto block 19
    rax = *reinterpret_cast<std::uintptr_t*>(rcx - 8);
    rcx += 0xFFFFFFFFFFFFFFF8ull;
    rcx -= rax;
    if (rcx >= 0x20ull) goto L_0x6754865;
    goto L_0x6754848;

L_0x6754848:
    // 0x6754848..0x675484f: block 19
    //   add rdi,0x27         ; rdi = size + 0x27
    //   mov rcx,rax          ; rcx = heap header
    // -> if fallthrough goto L_0x675484f
    rdi += 0x27;
    rcx = rax;
    goto L_0x675484f;

L_0x675484f:
    // 0x675484f..0x675485d: block 20 (sub_e935700 on heap, zero array base)
    //   mov rdx,rdi          ; rdx = size
    //   call 0xE935700       ; native::sub_e935700(rcx=heapHeader, rdx=size) -> rax
    //   xorps xmm0,xmm0
    //   movups [rbx],xmm0    ; *(u128*)(&a0->f8) = 0  -> a0->f8 = 0, a0->f10 = 0
    // -> if fallthrough goto L_0x675485d
    rdx = rdi;
    rax = reinterpret_cast<std::uintptr_t>(
        native::sub_e935700(reinterpret_cast<void*>(rcx)));
    a0->f8 = nullptr;
    a0->f10 = 0;
    goto L_0x675485d;

L_0x675485d:
    // 0x675485d..0x6754865: block 21 (epilogue)
    //   add rsp,0x30; pop rbx; pop rdi; pop rsi; ret
    // -> return rax
    return rax;

L_0x6754865:
    // 0x6754865..0x675487f: block 22 (validation failure, noreturn)
    //   mov qword ptr [rsp+0x20],0
    //   xor ecx,ecx; xor edx,edx; xor r8d,r8d; xor r9d,r9d
    //   call qword ptr [0xF9A8C78]   ; fail handler (noreturn)
    //   int3 (padding)
    failfast();
    __assume(false);
}

LIFT_FN(sub_6754750, "sub_6754750", 0x6754750, sub_6754750, &sub_6754750_footprint);

} // namespace native::helpers
