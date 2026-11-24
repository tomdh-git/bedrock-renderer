// LIFT 0xe876420 size 0xc5 1.26.62.01 BgfxFrameBuilder slot 16
#include "sub_e876420.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

// Layout constants live in sub_e876420.h; cross-check the target model here [V].
static_assert(sizeof(void*) == 8, "e876420: x64 target");

namespace native {

namespace {

// 0xE951550: __security_check_cookie (crt boundary, noreturn on failure) [V].
// Called at 0xe8764df with rcx = cookieStored ^ frame when the /GS cookie check fails.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// 0xEEC6D80: forward-declared lift callee (native_boundary.tsv class 'lift').
// Called at 0xe8764d2 with rcx = &errorRecord, rdx = 0xFB3B080.
// Defined in MaterialInstance_initFromMaterial_chunk5.cpp with signature (a0,a1,a2,a3).
// We pass a2=a3=0 as the original does not set them.
extern "C" void sub_eec6d80(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3);

// Indirect call target through slot 0xF9A7480.
// The slot holds a function pointer at call time; we read it and call with the same args.
// ABI [V from callers]: rcx=obj, rdx=dst, r8d=size -> returns void* (result), [result+8]=status.
using SlotFn = void* (*)(void* obj, void* dst, std::uint32_t size);

} // namespace

extern "C" bool sub_e876420(void* obj, void* dst) {
    // 0xe876420..0xe876436: push cookie frame (sub rsp,0x48; cookie setup)
    //   push rsi
    //   push rdi
    //   sub rsp,0x48
    //   mov rsi,rdx
    //   mov rdi,rcx
    //   mov rax,[0x1230A0C0]
    //   xor rax,rsp
    //   mov [rsp+0x40],rax
    std::uintptr_t cookieSlot = 0;
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);

    // 0xe87643b..0xe876446: first slot call with size=1
    //   lea rdx,[rsp+0x27]
    //   mov r8d,1
    //   call qword ptr [0xF9A7480]                   ; [data_f9a7480]
    SlotFn slot = *reinterpret_cast<SlotFn*>(kSlotAddr);
    void* result1 = slot(obj, dst, 1);                              // 0xe876446  call qword ptr [0xF9A7480]
    std::int64_t status1 = *reinterpret_cast<std::int64_t*>(result1 + 8); // 0xe87644c  mov rax,[rax+8]

    // 0xe876450..0xe876453: test status, branch on negative
    //   test rax,rax
    //   js short 0xE8764B2
    if (status1 < 0) {                                              // 0xe876450  test rax,rax  ; 0xe876453  js
        // 0xe8764b2..0xe8764d2: error path (status < 0)
        //   xorps xmm0,xmm0
        //   movups [rsp+0x30],xmm0
        //   lea rax,[0xF08E738]
        //   mov [rsp+0x28],rax
        //   lea rdx,[0xFB3B080]
        //   lea rcx,[rsp+0x28]
        //   call 0xEEC6D80
        E876420ErrorRecord rec{};
        rec.file = reinterpret_cast<void*>(kErrFilePtr);           // 0xe8764ba  lea rax,[0xF08E738] ; 0xe8764c1  mov [rsp+0x28],rax
        sub_eec6d80(reinterpret_cast<uintptr_t>(&rec), kErrDataPtr, 0, 0); // 0xe8764c6..0xe8764d2

        // Fall through to cookie check failure path (0xe8764d7..0xe8764e5)
        // 0xe8764d7..0xe8764e5: cookie mismatch -> call __security_check_cookie + int3
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot)); // 0xe8764df  call 0xE951550
        __assume(false);                                           // 0xe8764e4  int3
    }

    // 0xe876455..0xe876459: cmp status,1; jne 0xE876495
    //   cmp rax,1
    //   jne short 0xE876495
    if (status1 != 1) {                                             // 0xe876455  cmp rax,1  ; 0xe876459  jne
        // 0xe876495: xor eax,eax  (return false)
        // 0xe876497..0xe8764a9: /GS cookie check
        //   mov rcx,[rsp+0x40]
        //   xor rcx,rsp
        //   mov rdx,[0x1230A0C0]
        //   cmp rdx,rcx
        //   jne short 0xE8764D7
        if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
            (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
            // 0xe8764d7..0xe8764e5: cookie mismatch -> call __security_check_cookie + int3
            sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot)); // 0xe8764df  call 0xE951550
            __assume(false);                                       // 0xe8764e4  int3
        }
        // 0xe8764ab..0xe8764b1: add rsp,0x48; pop rdi; pop rsi; ret
        return false;
    }

    // 0xe87645b..0xe876463: movzx ecx,byte ptr [rsp+0x27]; cmp cl,2; jae 0xE876495
    //   movzx ecx,byte ptr [rsp+0x27]
    //   cmp cl,2
    //   jae short 0xE876495
    std::uint8_t byteVal = *reinterpret_cast<std::uint8_t*>(reinterpret_cast<uintptr_t>(dst) + 0x27);
    if (byteVal >= 2) {                                             // 0xe87645b  movzx ecx,byte ptr [rsp+0x27] ; 0xe876460  cmp cl,2 ; 0xe876463  jae
        // 0xe876495: xor eax,eax  (return false)
        // 0xe876497..0xe8764a9: /GS cookie check
        if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
            (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
            sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));
            __assume(false);
        }
        return false;
    }

    // 0xe876465..0xe87646a: mov al,1; cmp cl,1; jne 0xE876497
    //   mov al,1
    //   cmp cl,1
    //   jne short 0xE876497
    bool ok = true;
    if (byteVal != 1) {                                             // 0xe876467  cmp cl,1  ; 0xe87646a  jne
        // 0xe876497..0xe8764a9: /GS cookie check
        if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
            (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
            sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));
            __assume(false);
        }
        return ok; // true, since al was set to 1
    }

    // 0xe87646c..0xe87647d: byteVal == 1 path
    //   mov word ptr [rsi],0x100                      ; W a1+0x0
    //   mov r8d,1
    //   mov rcx,rdi
    //   mov rdx,rsi
    //   call qword ptr [0xF9A7480]                    ; [data_f9a7480]
    *reinterpret_cast<std::uint16_t*>(dst) = 0x100;                 // 0xe87646c  mov word ptr [rsi],0x100
    void* result2 = slot(obj, dst, 1);                              // 0xe87647d  call qword ptr [0xF9A7480]
    std::int64_t status2 = *reinterpret_cast<std::int64_t*>(result2 + 8); // 0xe876483  mov rax,[rax+8]

    // 0xe876487..0xe87648a: test status2, branch on negative
    //   test rax,rax
    //   js short 0xE8764B2
    if (status2 < 0) {                                              // 0xe876487  test rax,rax  ; 0xe87648a  js
        // 0xe8764b2..0xe8764d2: error path (status < 0)
        E876420ErrorRecord rec{};
        rec.file = reinterpret_cast<void*>(kErrFilePtr);
        sub_eec6d80(reinterpret_cast<uintptr_t>(&rec), kErrDataPtr, 0, 0);

        // Fall through to cookie check failure path
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));
        __assume(false);
    }

    // 0xe87648c..0xe876493: cmp status2,1; sete al
    //   cmp rax,1
    //   sete al
    ok = (status2 == 1);                                            // 0xe87648c  cmp rax,1  ; 0xe876490  sete al

    // 0xe876493: jmp short 0xE876497
    // 0xe876497..0xe8764a9: /GS cookie check
    //   mov rcx,[rsp+0x40]
    //   xor rcx,rsp
    //   mov rdx,[0x1230A0C0]
    //   cmp rdx,rcx
    //   jne short 0xE8764D7
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
        // 0xe8764d7..0xe8764e5: cookie mismatch -> call __security_check_cookie + int3
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot)); // 0xe8764df  call 0xE951550
        __assume(false);                                           // 0xe8764e4  int3
    }

    // 0xe8764ab..0xe8764b1: add rsp,0x48; pop rdi; pop rsi; ret
    return ok;
}

// Verbatim call instructions in [0xe876420, 0xe8764e5) (rdis dis output, two spaces after address):
#if 0
0xe876446  call qword ptr [0xF9A7480]                    ; [data_f9a7480]
0xe87647d  call qword ptr [0xF9A7480]                    ; [data_f9a7480]
0xe8764d2  call 0xEEC6D80                                ; -> sub_eec6d80
0xe8764df  call 0xE951550                                ; -> sub_e951550
#endif

LIFT_FN(e876420, "sub_e876420", 0xE876420, sub_e876420, nullptr);

} // namespace native