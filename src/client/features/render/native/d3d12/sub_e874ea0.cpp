// LIFT 0xe874ea0 size 0x7b 1.26.62.01 BgfxFrameBuilder slot 16
#include "sub_e874ea0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

// Layout constants live in sub_e874ea0.h; cross-check the target model here [V].
static_assert(sizeof(void*) == 8, "e874ea0: x64 target");

namespace native {

namespace {

// 0xE951550: __security_check_cookie (crt boundary, noreturn on failure) [V].
// Called at 0xe874f15 with rcx = cookieStored ^ frame when the /GS cookie check fails.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// 0xEEC6D80: forward-declared lift callee (native_boundary.tsv class 'lift').
// Called at 0xe874f08 with rcx = &errorRecord, rdx = 0xFB3B080.
// Defined in its own unit with signature (a0,a1,a2,a3).
// We pass a2=a3=0 as the original does not set them.
extern "C" void sub_eec6d80(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);

// Indirect call target through slot 0xF9A7480.
// The slot holds a function pointer at call time; we read it and call with the same args.
// ABI [V from callers]: rcx=obj, rdx=dst, r8d=size -> returns void* (result), [result+8]=status.
using SlotFn = void* (*)(void* obj, void* dst, std::uint32_t size);

} // namespace

extern "C" bool sub_e874ea0(void* obj, void* dst) {
    // 0xe874ea0..0xe874eae: push cookie frame (sub rsp,0x48; cookie setup)
    //   sub rsp,0x48
    //   mov rax,[0x1230A0C0]
    //   xor rax,rsp
    //   mov [rsp+0x40],rax
    std::uintptr_t cookieSlot = 0;
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);

    // 0xe874eb3..0xe874eb9: mov r8d,2; call qword ptr [0xF9A7480]
    //   mov r8d,2
    //   call qword ptr [0xF9A7480]                   ; [data_f9a7480]
    // 0xe874ebf..0xe874ecc: mov rax,[rax+8]; test rax,rax; js 0xE874EE8; cmp rax,2; sete al
    //   mov rax,[rax+8]
    //   test rax,rax
    //   js short 0xE874EE8
    //   cmp rax,2
    //   sete al
    SlotFn slot = *reinterpret_cast<SlotFn*>(kSlotAddr);
    void* result = slot(obj, dst, 2);                              // 0xe874eb9  call qword ptr [0xF9A7480]
    std::int64_t status = *reinterpret_cast<std::int64_t*>(result + 8); // 0xe874ebf  mov rax,[rax+8]
    bool ok;
    if (status < 0) {                                              // 0xe874ec3  test rax,rax  ; 0xe874ec6  js
        // 0xe874ee8..0xe874f08: error path (status < 0)
        //   xorps xmm0,xmm0
        //   movups [rsp+0x30],xmm0
        //   lea rax,[0xF08E738]
        //   mov [rsp+0x28],rax
        //   lea rdx,[0xFB3B080]
        //   lea rcx,[rsp+0x28]
        //   call 0xEEC6D80
        E874EA0ErrorRecord rec{};
        rec.file = reinterpret_cast<void*>(kErrFilePtr);           // 0xe874ef0  lea rax,[0xF08E738] ; 0xe874ef7  mov [rsp+0x28],rax
        sub_eec6d80(reinterpret_cast<uintptr_t>(&rec), kErrDataPtr, 0, 0); // 0xe874efc..0xe874f08

        // Fall through to cookie check failure path (0xe874f0d..0xe874f1a)
        ok = false; // unreachable; original hits int3 after sub_e951550
    } else {
        ok = (status == 2);                                         // 0xe874ec8  cmp rax,2  ; 0xe874ecc  sete al
    }

    // 0xe874ecf..0xe874ee1: /GS cookie check
    //   mov rcx,[rsp+0x40]
    //   xor rcx,rsp
    //   mov rdx,[0x1230A0C0]
    //   cmp rdx,rcx
    //   jne short 0xE874F0D
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
        // 0xe874f0d..0xe874f1a: cookie mismatch -> call __security_check_cookie + int3
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot)); // 0xe874f15  call 0xE951550
        __assume(false);                                           // 0xe874f1a  int3
    }

    // 0xe874ee3 add rsp,0x48 ; 0xe874ee7 ret
    return ok;
}

// Verbatim call instructions in [0xe874ea0, 0xe874f1b) (rdis dis output, two spaces after address):
#if 0
0xe874eb9  call qword ptr [0xF9A7480]                    ; [data_f9a7480]
0xe874f08  call 0xEEC6D80                                ; -> sub_eec6d80
0xe874f15  call 0xE951550                                ; -> sub_e951550
#endif

LIFT_FN(e874ea0, "sub_e874ea0", 0xE874EA0, sub_e874ea0, nullptr);

} // namespace native