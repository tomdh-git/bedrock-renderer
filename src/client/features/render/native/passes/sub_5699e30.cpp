// LIFT 0x5699e30 size 0xc4 1.26.62.01 sub_5699e30
#include "sub_5699e30.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_5699e30 (0x5699e30, size 0xc4, 1.26.62.01, "pass task render-thread body (class B)").
//
// Same template as sub_568bcd0 (0x568bcd0, size 0xc4): publishes the executor context
// through the task's ViewRef, invokes the task's stored std::function (the pass body),
// then clears execCtx and releases the shared_ptr control block.
// Differs from sub_568bcd0 only in task-object field offsets:
//   sub_568bcd0: arg0 +0x2E0, viewRef +0x2E8, ctrl +0x2F0, body +0x70
//   sub_5699e30: arg0 +0xA8,   viewRef +0xB0,   ctrl +0xB8,   body +0x70
//
// Reads: task+0xA8 (arg0), task+0xB0 (viewRef), task+0xB8 (ctrl), *ctrl (vfptr),
//   ctrl+0x08 (uses), ctrl+0x0C (weaks), *ctrl vfptr[0] (dispose), *ctrl vfptr[1] (destroy),
//   task+0x70 (body), *body (vfptr), *body vfptr[0x10] (_Do_call), view+0x18 (execCtx).
// Writes: view+0x18 (execCtx = ctx, then nullptr), ctrl+0x08 (lock dec), ctrl+0x0C (lock dec).
// Calls: sub_eec59e0 (lift set, noreturn); 3x indirect via data slot 0xF99FFA0
//   (_Do_call, dispose, destroy through sub_eea6040 thunk).
// Return: void.
// Same reads, same writes, same calls in the same order, same return. Nothing else
// happens in [0x5699e30, 0x5699ef4).

// PassArgs layout on the stack at [rbp-0x18, rbp): { arg0, view, ctrl } = 0x18 bytes.
// Matches task tail { arg0 at +0xA8, viewRef* at +0xB0, ctrl* at +0xB8 }.
struct PassArgs {
    void* a;               // +0x00 = task->arg0
    void* view;            // +0x08 = task->viewRef
    RefCountCtrl* ctrl;    // +0x10 = task->ctrl
};

// 0x5699e30..0x5699ef4
void sub_5699e30(void* task, void* ctx)
{
    static_assert(sizeof(void*) == 8, "sub_5699e30: x64 pointers and arguments are 8 bytes");

    // 0x5699e30..0x5699e36  prologue: push rbp; push rsi; sub rsp,0x48; lea rbp,[rsp+0x40]; mov [rbp],-2
    void* const a0 = task;   // RCX = task object
    void* const a1 = ctx;    // RDX = ctx (ExecCtx*)

    // 0x5699e43  mov r8,rcx   (r8 == a0 throughout)

    // PassArgs on the stack at [rbp-0x18, rbp): { arg0, view, ctrl }
    PassArgs args;

    // 0x5699e46  mov rax,[rcx+0xA8]      ; rax = task->arg0
    // 0x5699e4d  mov [rbp-0x18],rax       ; args.a = arg0
    args.a = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetArg0);   // 0x5699e46  mov rax,[rcx+0xA8]
                                                                   // 0x5699e4d  mov [rbp-0x18],rax

    // 0x5699e51  xorps xmm0,xmm0
    // 0x5699e54  movups [rbp-0x10],xmm0   ; zero args.view and args.ctrl (16 bytes)
    args.view = nullptr;     // 0x5699e51  xorps xmm0,xmm0
                             // 0x5699e54  movups [rbp-0x10],xmm0  (low qword)
    args.ctrl = nullptr;     // 0x5699e54  movups [rbp-0x10],xmm0  (high qword)

    // 0x5699e58  mov rax,[rcx+0xB8]      ; rax = task->ctrl
    // 0x5699e5f  test rax,rax
    // 0x5699e62  je short 0x5699E71       ; if null, skip addref
    // 0x5699e64  lock inc dword ptr [rax+8]   ; ctrl->uses += 1
    // 0x5699e68  mov rax,[r8+0xB8]       ; rax = task->ctrl (same value)
    // 0x5699e6f  jmp short 0x5699E73
    RefCountCtrl* const ctrl =
        *reinterpret_cast<RefCountCtrl**>(
            reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetCtrl);  // 0x5699e58  mov rax,[rcx+0xB8]
    if (ctrl != nullptr) {                                             // 0x5699e5f  test rax,rax
                                                                       // 0x5699e62  je short 0x5699E71
        _InterlockedIncrement(                                         // 0x5699e64  lock inc dword ptr [rax+8]
            reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(ctrl) + kCtrlOffsetUses));
    }
    // 0x5699e68  mov rax,[r8+0xB8]   ; reload (same value as ctrl)
    // 0x5699e6f  jmp short 0x5699E73

    // loc_5699e71:  (ctrl == null path, rax = 0)
    // loc_5699e73:
    // 0x5699e73  mov rcx,[r8+0xB0]      ; rcx = task->viewRef
    // 0x5699e7a  mov [rbp-0x10],rcx      ; args.view = viewRef
    // 0x5699e7e  mov [rbp-8],rax         ; args.ctrl = ctrl
    // 0x5699e82  mov [rcx+0x18],rdx      ; view->execCtx = ctx
    ViewRef* const view =
        *reinterpret_cast<ViewRef**>(
            reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetViewRef);  // 0x5699e73  mov rcx,[r8+0xB0]
    args.view = view;                                                    // 0x5699e7a  mov [rbp-0x10],rcx
    args.ctrl = ctrl;                                                    // 0x5699e7e  mov [rbp-8],rax
    view->execCtx = a1;                                                  // 0x5699e82  mov [rcx+0x18],rdx

    // 0x5699e86  mov rcx,[r8+0x70]        ; rcx = task->body
    // 0x5699e8a  test rcx,rcx
    // 0x5699e8d  je short 0x5699EED       ; if null -> sub_eec59e0 (_Xbad_function_call)
    void* const body =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetBody);   // 0x5699e86  mov rcx,[r8+0x70]
    if (body == nullptr) {                                             // 0x5699e8a  test rcx,rcx
                                                                       // 0x5699e8d  je short 0x5699EED
        // 0x5699eed  call 0xEEC59E0        ; std::_Xbad_function_call (noreturn)
        sub_eec59e0();                                                  // 0x5699eed  call 0xEEC59E0
        // unreachable (sub_eec59e0 is [[noreturn]])
    }

    // 0x5699e8f  add r8,0x78              ; r8 = task + 0x78
    // 0x5699e93  mov rax,[rcx]            ; rax = *body (vfptr)
    // 0x5699e96  mov rax,[rax+0x10]       ; rax = vfptr[0x10] = _Do_call
    // 0x5699e9a  lea rdx,[rbp-0x18]       ; rdx = &args
    // 0x5699e9e  call qword ptr [0xF99FFA0]  ; _Do_call(body, &args, task+0x78)
    void** const bodyVfptr =
        *reinterpret_cast<void***>(body);                            // 0x5699e93  mov rax,[rcx]
                                                                     // 0x5699e96  mov rax,[rax+0x10]
    using DoCallFn = void (__cdecl*)(void* body, void* args, void* taskArgs);
    DoCallFn const doCall =
        reinterpret_cast<DoCallFn>(bodyVfptr[4]);                    // vfptr[0x10] = _Do_call
    doCall(body, &args,                                              // 0x5699e9a  lea rdx,[rbp-0x18]
           reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetFunctor); // 0x5699e8f  add r8,0x78
                                                                      // 0x5699e9e  call qword ptr [0xF99FFA0]

    // 0x5699ea5  mov rax,[rbp-0x10]       ; rax = args.view
    // 0x5699ea9  mov qword ptr [rax+0x18],0   ; view->execCtx = nullptr
    view->execCtx = nullptr;                                           // 0x5699ea5  mov rax,[rbp-0x10]
                                                                        // 0x5699ea9  mov qword ptr [rax+0x18],0

    // 0x5699eb1  mov rsi,[rbp-8]          ; rsi = args.ctrl
    // 0x5699eb5  test rsi,rsi
    // 0x5699eb8  je short 0x5699EE6       ; if null, skip release
    // 0x5699eba  lock dec dword ptr [rsi+8]   ; ctrl->uses -= 1
    // 0x5699ebe  jne short 0x5699EE6      ; if not zero, skip dispose
    if (ctrl != nullptr) {                                             // 0x5699eb5  test rsi,rsi
                                                                       // 0x5699eb8  je short 0x5699EE6
        if (_InterlockedDecrement(                                     // 0x5699eba  lock dec dword ptr [rsi+8]
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(ctrl) +
                    kCtrlOffsetUses)) == 0) {                          // 0x5699ebe  jne short 0x5699EE6
            // 0x5699ec0  mov rax,[rsi]        ; rax = *ctrl (vfptr)
            // 0x5699ec3  mov rax,[rax]        ; rax = vfptr[0] = dispose
            // 0x5699ec6  mov rcx,rsi          ; RCX = ctrl
            // 0x5699ec9  call qword ptr [0xF99FFA0]   ; dispose(ctrl)
            void** const ctrlVfptr =
                *reinterpret_cast<void***>(ctrl);                    // 0x5699ec0  mov rax,[rsi]
                                                                     // 0x5699ec3  mov rax,[rax]
            using DisposeFn = void (__cdecl*)(void* ctrl);
            DisposeFn const dispose =
                reinterpret_cast<DisposeFn>(ctrlVfptr[0]);           // vfptr[0] = dispose
            dispose(ctrl);                                           // 0x5699ec6  mov rcx,rsi
                                                                     // 0x5699ec9  call qword ptr [0xF99FFA0]

            // 0x5699ecf  lock dec dword ptr [rsi+0xC]   ; ctrl->weaks -= 1
            // 0x5699ed3  jne short 0x5699EE6      ; if not zero, skip destroy
            if (_InterlockedDecrement(                                // 0x5699ecf  lock dec dword ptr [rsi+0xC]
                    reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(ctrl) +
                        kCtrlOffsetWeaks)) == 0) {                    // 0x5699ed3  jne short 0x5699EE6
                // 0x5699ed5  mov rax,[rsi]        ; rax = *ctrl (vfptr)
                // 0x5699ed8  mov rax,[rax+8]      ; rax = vfptr[8] = destroy
                // 0x5699edc  mov rcx,rsi          ; RCX = ctrl
                // 0x5699edf  call qword ptr [0xF99FFA0]   ; destroy(ctrl)
                using DestroyFn = void (__cdecl*)(void* ctrl);
                DestroyFn const destroy =
                    reinterpret_cast<DestroyFn>(ctrlVfptr[1]);       // vfptr[1] = destroy
                destroy(ctrl);                                       // 0x5699edc  mov rcx,rsi
                                                                     // 0x5699edf  call qword ptr [0xF99FFA0]
            }
        }
    }

    // 0x5699ee6  add rsp,0x48
    // 0x5699eea  pop rsi
    // 0x5699eeb  pop rbp
    // 0x5699eec  ret
}

LIFT_FN(sub_5699e30, "sub_5699e30", 0x5699E30, ::native::sub_5699e30, nullptr);

// Verbatim instructions of [0x5699e30, 0x5699ef4) (rdis dis 0x5699e30 0xc4);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x5699e30  push rbp
0x5699e31  push rsi
0x5699e32  sub rsp,0x48
0x5699e36  lea rbp,[rsp+0x40]
0x5699e3b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x5699e43  mov r8,rcx
0x5699e46  mov rax,[rcx+0xA8]
0x5699e4d  mov [rbp-0x18],rax
0x5699e51  xorps xmm0,xmm0
0x5699e54  movups [rbp-0x10],xmm0
0x5699e58  mov rax,[rcx+0xB8]
0x5699e5f  test rax,rax
0x5699e62  je short 0x5699E71
0x5699e64  lock inc dword ptr [rax+8]
0x5699e68  mov rax,[r8+0xB8]
0x5699e6f  jmp short 0x5699E73
0x5699e71  xor eax,eax
0x5699e73  mov rcx,[r8+0xB0]
0x5699e7a  mov [rbp-0x10],rcx
0x5699e7e  mov [rbp-8],rax
0x5699e82  mov [rcx+0x18],rdx
0x5699e86  mov rcx,[r8+0x70]
0x5699e8a  test rcx,rcx
0x5699e8d  je short 0x5699EED
0x5699e8f  add r8,0x78
0x5699e93  mov rax,[rcx]
0x5699e96  mov rax,[rax+0x10]
0x5699e9a  lea rdx,[rbp-0x18]
0x5699e9e  call qword ptr [0xF99FFA0]
0x5699ea4  nop
0x5699ea5  mov rax,[rbp-0x10]
0x5699ea9  mov qword ptr [rax+0x18],0
0x5699eb1  mov rsi,[rbp-8]
0x5699eb5  test rsi,rsi
0x5699eb8  je short 0x5699EE6
0x5699eba  lock dec dword ptr [rsi+8]
0x5699ebe  jne short 0x5699EE6
0x5699ec0  mov rax,[rsi]
0x5699ec3  mov rax,[rax]
0x5699ec6  mov rcx,rsi
0x5699ec9  call qword ptr [0xF99FFA0]
0x5699ecf  lock dec dword ptr [rsi+0xC]
0x5699ed3  jne short 0x5699EE6
0x5699ed5  mov rax,[rsi]
0x5699ed8  mov rax,[rax+8]
0x5699edc  mov rcx,rsi
0x5699edf  call qword ptr [0xF99FFA0]
0x5699ee5  nop
0x5699ee6  add rsp,0x48
0x5699eea  pop rsi
0x5699eeb  pop rbp
0x5699eec  ret
0x5699eed  call 0xEEC59E0
0x5699ef2  nop
0x5699ef3  int3
#endif

} // namespace native
