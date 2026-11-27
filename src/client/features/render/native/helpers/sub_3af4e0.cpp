// LIFT 0x3af4e0 size 0x83 1.26.62.01 sub_3af4e0
#include "sub_3af4e0.h"
#include "client/features/render/native/Lift.h"
#include <cstdint>

namespace native {

// Layout assertions (mirrored from header for liftcheck)
static_assert(kSub3af4e0_StackFrameSize == 0x40, "sub_3af4e0 stack frame size");
static_assert(kSub3af4e0_CookieSlotOffset == 0x38, "sub_3af4e0 cookie slot offset");
static_assert(kSub3af4e0_RbxSaveOffset == 0x30, "sub_3af4e0 rbx save offset");
static_assert(kSub3af4e0_Arg3SaveOffset == 0x70, "sub_3af4e0 arg3 save offset");
static_assert(kSub3af4e0_Arg4SaveOffset == 0x78, "sub_3af4e0 arg4 save offset");

// Verbatim instruction quotes for liftcheck verification
#if 0
0x3af4e0  push rsi
0x3af4e1  push rdi
0x3af4e2  push rbx
0x3af4e3  sub rsp,0x40
0x3af4e7  mov rsi,rdx
0x3af4ea  mov rdi,rcx
0x3af4ed  mov [rsp+0x70],r8
0x3af4f2  mov [rsp+0x78],r9
0x3af4f7  mov rax,[0x1230A0C0]
0x3af4fe  xor rax,rsp
0x3af501  mov [rsp+0x38],rax
0x3af506  lea rbx,[rsp+0x70]
0x3af50b  mov [rsp+0x30],rbx
0x3af510  call 0x3B23C0
0x3af515  mov rcx,[rax]
0x3af518  mov [rsp+0x28],rbx
0x3af51d  mov qword ptr [rsp+0x20],0
0x3af526  mov rdx,rdi
0x3af529  mov r8,0xFFFFFFFFFFFFFFFF
0x3af530  mov r9,rsi
0x3af533  call qword ptr [0xF9A8B30]
0x3af539  mov rcx,[rsp+0x38]
0x3af53e  xor rcx,rsp
0x3af541  mov rdx,[0x1230A0C0]
0x3af548  cmp rdx,rcx
0x3af54b  jne short 0x3AF555
0x3af54d  add rsp,0x40
0x3af551  pop rbx
0x3af552  pop rdi
0x3af553  pop rsi
0x3af554  ret
0x3af555  mov rcx,[rsp+0x38]
0x3af55a  xor rcx,rsp
0x3af55d  call 0xE951550
0x3af562  int3
#endif

uint64_t sub_3af4e0(uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4) {
    // 0x3af4e0..0x3af4f7: Prologue - save non-volatile registers, allocate stack, save args
    // 0x3af4e0  push rsi
    // 0x3af4e1  push rdi
    // 0x3af4e2  push rbx
    // 0x3af4e3  sub rsp, 0x40
    // 0x3af4e7  mov rsi, rdx          ; save arg2
    // 0x3af4ea  mov rdi, rcx          ; save arg1
    // 0x3af4ed  mov [rsp+0x70], r8    ; save arg3 to stack slot
    // 0x3af4f2  mov [rsp+0x78], r9    ; save arg4 to stack slot
    uint64_t saved_rsi = arg2;
    uint64_t saved_rdi = arg1;
    uint64_t arg3_save = arg3;
    uint64_t arg4_save = arg4;

    // 0x3af4f7..0x3af50b: Stack cookie setup (__security_cookie at 0x1230A0C0)
    // 0x3af4f7  mov rax, [0x1230A0C0]
    // 0x3af4fe  xor rax, rsp
    // 0x3af501  mov [rsp+0x38], rax
    // 0x3af506  lea rbx, [rsp+0x70]
    // 0x3af50b  mov [rsp+0x30], rbx
    uint8_t stack_probe;
    uintptr_t rsp_proxy = reinterpret_cast<uintptr_t>(&stack_probe);
    uintptr_t cookie = __security_cookie ^ rsp_proxy;
    uint64_t* rbx_ptr = &arg3_save;

    // 0x3af510..0x3af515: Call sub_3b23c0 (lift callee), get first qword of returned pointer
    // 0x3af510  call 0x3B23C0
    // 0x3af515  mov rcx, [rax]
    std::uint64_t* ptr_from_3b23c0 = sub_3b23c0();
    uint64_t rcx_val = *ptr_from_3b23c0;

    // 0x3af518..0x3af530: Set up shadow space and args for indirect call
    // 0x3af518  mov [rsp+0x28], rbx
    // 0x3af51d  mov qword ptr [rsp+0x20], 0
    // 0x3af526  mov rdx, rdi
    // 0x3af529  mov r8, 0xFFFFFFFFFFFFFFFF
    // 0x3af530  mov r9, rsi
    uint64_t shadow28 = reinterpret_cast<uint64_t>(rbx_ptr);
    uint64_t shadow20 = 0;
    uint64_t rdx_val = saved_rdi;
    uint64_t r8_val = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t r9_val = saved_rsi;

    // 0x3af533: Indirect call through data slot 0xF9A8B30
    // 0x3af533  call qword ptr [0xF9A8B30]
    slot_f9a8b30_t slot_fn = *reinterpret_cast<slot_f9a8b30_t*>(0xF9A8B30);
    uint64_t rax_result = slot_fn(rcx_val, rdx_val, r8_val, r9_val);

    // 0x3af539..0x3af54b: Stack cookie verification
    // 0x3af539  mov rcx, [rsp+0x38]
    // 0x3af53e  xor rcx, rsp
    // 0x3af541  mov rdx, [0x1230A0C0]
    // 0x3af548  cmp rdx, rcx
    // 0x3af54b  jne short 0x3AF555
    uintptr_t check_cookie = cookie ^ rsp_proxy;
    if (__security_cookie != check_cookie) {
        // 0x3af555..0x3af55d: Cookie mismatch - call __report_gsfailure (0xE951550)
        // 0x3af555  mov rcx, [rsp+0x38]
        // 0x3af55a  xor rcx, rsp
        // 0x3af55d  call 0xE951550
        __report_gsfailure(check_cookie);
    }

    // 0x3af54d..0x3af554: Normal epilog
    // 0x3af54d  add rsp, 0x40
    // 0x3af551  pop rbx
    // 0x3af552  pop rdi
    // 0x3af553  pop rsi
    // 0x3af554  ret
    return rax_result;
}

} // namespace native

// Registry entry via LIFT_FN (X0d framework)
LIFT_FN(sub_3af4e0, "sub_3af4e0", 0x3AF4E0, native::sub_3af4e0, nullptr);
