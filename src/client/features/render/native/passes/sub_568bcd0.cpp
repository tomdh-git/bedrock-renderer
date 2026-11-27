// LIFT 0x568bcd0 size 0xc4 1.26.62.01 sub_568bcd0
#include "sub_568bcd0.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_568bcd0 (0x568bcd0, size 0xc4, 1.26.62.01, "common pass task render-thread body").
//
// Called by the D3D12 executor for a custom render item. Publishes the executor context
// through the task's ViewRef, invokes the task's stored std::function (the pass body),
// then clears execCtx and releases the shared_ptr control block.
//
// Reads: task+0x2E0 (arg0), task+0x2E8 (viewRef), task+0x2F0 (ctrl), *ctrl (vfptr),
//   ctrl+0x08 (uses), ctrl+0x0C (weaks), *ctrl vfptr[0] (dispose), *ctrl vfptr[1] (destroy),
//   task+0x70 (body), *body (vfptr), *body vfptr[0x10] (_Do_call), view+0x18 (execCtx).
// Writes: view+0x18 (execCtx = ctx, then nullptr), ctrl+0x08 (lock dec), ctrl+0x0C (lock dec).
// Calls: sub_eec59e0 (lift set, noreturn); 3x indirect via data slot 0xF99FFA0
//   (_Do_call, dispose, destroy through sub_eea6040 thunk).
// Return: void.
// Same reads, same writes, same calls in the same order, same return. Nothing else
// happens in [0x568bcd0, 0x568bd94).

// PassArgs layout on the stack at [rbp-0x18, rbp): { arg0, view, ctrl } = 0x18 bytes.
// Matches task tail { arg0 at +0x2E0, viewRef* at +0x2E8, ctrl* at +0x2F0 }.
struct PassArgs {
    void* a;               // +0x00 = task->arg0
    void* view;            // +0x08 = task->viewRef
    RefCountCtrl* ctrl;    // +0x10 = task->ctrl
};

// 0x568bcd0..0x568bd94
void sub_568bcd0(void* task, void* ctx)
{
    static_assert(sizeof(void*) == 8, "sub_568bcd0: x64 pointers and arguments are 8 bytes");

    // 0x568bcd0..0x568bce3  prologue: push rbp; push rsi; sub rsp,0x48; lea rbp,[rsp+0x40]; mov [rbp],-2
    void* const a0 = task;   // RCX = task object
    void* const a1 = ctx;    // RDX = ctx (ExecCtx*)

    // 0x568bce3  mov r8,rcx   (r8 == a0 throughout)

    // PassArgs on the stack at [rbp-0x18, rbp): { arg0, view, ctrl }
    PassArgs args;

    // 0x568bce6  mov rax,[rcx+0x2E0]      ; rax = task->arg0
    // 0x568bced  mov [rbp-0x18],rax       ; args.a = arg0
    args.a = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetArg0);   // 0x568bce6  mov rax,[rcx+0x2E0]
                                                                   // 0x568bced  mov [rbp-0x18],rax

    // 0x568bcf1  xorps xmm0,xmm0
    // 0x568bcf4  movups [rbp-0x10],xmm0   ; zero args.view and args.ctrl (16 bytes)
    args.view = nullptr;     // 0x568bcf1  xorps xmm0,xmm0
                             // 0x568bcf4  movups [rbp-0x10],xmm0  (low qword)
    args.ctrl = nullptr;     // 0x568bcf4  movups [rbp-0x10],xmm0  (high qword)

    // 0x568bcf8  mov rax,[rcx+0x2F0]      ; rax = task->ctrl
    // 0x568bcff  test rax,rax
    // 0x568bd02  je short 0x568BD11       ; if null, skip addref
    // 0x568bd04  lock inc dword ptr [rax+8]   ; ctrl->uses += 1
    // 0x568bd08  mov rax,[r8+0x2F0]       ; rax = task->ctrl (same value)
    // 0x568bd0f  jmp short 0x568BD13
    RefCountCtrl* const ctrl =
        *reinterpret_cast<RefCountCtrl**>(
            reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetCtrl);  // 0x568bcf8  mov rax,[rcx+0x2F0]
    if (ctrl != nullptr) {                                             // 0x568bcff  test rax,rax
                                                                       // 0x568bd02  je short 0x568BD11
        _InterlockedIncrement(                                         // 0x568bd04  lock inc dword ptr [rax+8]
            reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(ctrl) + kCtrlOffsetUses));
    }
    // 0x568bd08  mov rax,[r8+0x2F0]   ; reload (same value as ctrl)
    // 0x568bd0f  jmp short 0x568BD13

    // loc_568bd11:  (ctrl == null path, rax = 0)
    // loc_568bd13:
    // 0x568bd13  mov rcx,[r8+0x2E8]      ; rcx = task->viewRef
    // 0x568bd1a  mov [rbp-0x10],rcx      ; args.view = viewRef
    // 0x568bd1e  mov [rbp-8],rax         ; args.ctrl = ctrl
    // 0x568bd22  mov [rcx+0x18],rdx      ; view->execCtx = ctx
    ViewRef* const view =
        *reinterpret_cast<ViewRef**>(
            reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetViewRef);  // 0x568bd13  mov rcx,[r8+0x2E8]
    args.view = view;                                                    // 0x568bd1a  mov [rbp-0x10],rcx
    args.ctrl = ctrl;                                                    // 0x568bd1e  mov [rbp-8],rax
    view->execCtx = a1;                                                  // 0x568bd22  mov [rcx+0x18],rdx

    // 0x568bd26  mov rcx,[r8+0x70]        ; rcx = task->body
    // 0x568bd2a  test rcx,rcx
    // 0x568bd2d  je short 0x568BD8D       ; if null -> _Xbad_function_call
    void* const body =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetBody);   // 0x568bd26  mov rcx,[r8+0x70]
    if (body == nullptr) {                                             // 0x568bd2a  test rcx,rcx
                                                                       // 0x568bd2d  je short 0x568BD8D
        // 0x568bd8d  call 0xEEC59E0        ; std::_Xbad_function_call (noreturn)
        sub_eec59e0();                                                  // 0x568bd8d  call 0xEEC59E0
        // unreachable (sub_eec59e0 is [[noreturn]])
    }

    // 0x568bd2f  add r8,0x78              ; r8 = task + 0x78
    // 0x568bd33  mov rax,[rcx]            ; rax = *body (vfptr)
    // 0x568bd36  mov rax,[rax+0x10]       ; rax = vfptr[0x10] = _Do_call
    // 0x568bd3a  lea rdx,[rbp-0x18]       ; rdx = &args
    // 0x568bd3e  call qword ptr [0xF99FFA0]  ; _Do_call(body, &args, task+0x78)
    void** const bodyVfptr =
        *reinterpret_cast<void***>(body);                            // 0x568bd33  mov rax,[rcx]
                                                                     // 0x568bd36  mov rax,[rax+0x10]
    using DoCallFn = void (__cdecl*)(void* body, void* args, void* taskArgs);
    DoCallFn const doCall =
        reinterpret_cast<DoCallFn>(bodyVfptr[4]);                    // vfptr[0x10] = _Do_call
    doCall(body, &args,                                              // 0x568bd3a  lea rdx,[rbp-0x18]
           reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetFunctor); // 0x568bd2f  add r8,0x78
                                                                     // 0x568bd3e  call qword ptr [0xF99FFA0]

    // 0x568bd45  mov rax,[rbp-0x10]       ; rax = args.view
    // 0x568bd49  mov qword ptr [rax+0x18],0   ; view->execCtx = nullptr
    view->execCtx = nullptr;                                           // 0x568bd45  mov rax,[rbp-0x10]
                                                                       // 0x568bd49  mov qword ptr [rax+0x18],0

    // 0x568bd51  mov rsi,[rbp-8]          ; rsi = args.ctrl
    // 0x568bd55  test rsi,rsi
    // 0x568bd58  je short 0x568BD86       ; if null, skip release
    // 0x568bd5a  lock dec dword ptr [rsi+8]   ; ctrl->uses -= 1
    // 0x568bd5e  jne short 0x568BD86      ; if not zero, skip dispose
    if (ctrl != nullptr) {                                             // 0x568bd55  test rsi,rsi
                                                                       // 0x568bd58  je short 0x568BD86
        if (_InterlockedDecrement(                                     // 0x568bd5a  lock dec dword ptr [rsi+8]
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(ctrl) +
                    kCtrlOffsetUses)) == 0) {                          // 0x568bd5e  jne short 0x568BD86
            // 0x568bd60  mov rax,[rsi]        ; rax = *ctrl (vfptr)
            // 0x568bd63  mov rax,[rax]        ; rax = vfptr[0] = dispose
            // 0x568bd66  mov rcx,rsi          ; RCX = ctrl
            // 0x568bd69  call qword ptr [0xF99FFA0]   ; dispose(ctrl)
            void** const ctrlVfptr =
                *reinterpret_cast<void***>(ctrl);                    // 0x568bd60  mov rax,[rsi]
                                                                     // 0x568bd63  mov rax,[rax]
            using DisposeFn = void (__cdecl*)(void* ctrl);
            DisposeFn const dispose =
                reinterpret_cast<DisposeFn>(ctrlVfptr[0]);           // vfptr[0] = dispose
            dispose(ctrl);                                           // 0x568bd66  mov rcx,rsi
                                                                     // 0x568bd69  call qword ptr [0xF99FFA0]

            // 0x568bd6f  lock dec dword ptr [rsi+0xC]   ; ctrl->weaks -= 1
            // 0x568bd73  jne short 0x568BD86      ; if not zero, skip destroy
            if (_InterlockedDecrement(                                // 0x568bd6f  lock dec dword ptr [rsi+0xC]
                    reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(ctrl) +
                        kCtrlOffsetWeaks)) == 0) {                    // 0x568bd73  jne short 0x568BD86
                // 0x568bd75  mov rax,[rsi]        ; rax = *ctrl (vfptr)
                // 0x568bd78  mov rax,[rax+8]      ; rax = vfptr[8] = destroy
                // 0x568bd7c  mov rcx,rsi          ; RCX = ctrl
                // 0x568bd7f  call qword ptr [0xF99FFA0]   ; destroy(ctrl)
                using DestroyFn = void (__cdecl*)(void* ctrl);
                DestroyFn const destroy =
                    reinterpret_cast<DestroyFn>(ctrlVfptr[1]);       // vfptr[1] = destroy
                destroy(ctrl);                                       // 0x568bd7c  mov rcx,rsi
                                                                     // 0x568bd7f  call qword ptr [0xF99FFA0]
            }
        }
    }

    // 0x568bd86  add rsp,0x48
    // 0x568bd8a  pop rsi
    // 0x568bd8b  pop rbp
    // 0x568bd8c  ret
}

LIFT_FN(sub_568bcd0, "sub_568bcd0", 0x568BCD0, ::native::sub_568bcd0, nullptr);

// Verbatim instructions of [0x568bcd0, 0x568bd94) (rdis dis 0x568bcd0 0xc4);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x568bcd0  push rbp
0x568bcd1  push rsi
0x568bcd2  sub rsp,0x48
0x568bcd6  lea rbp,[rsp+0x40]
0x568bcdb  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x568bce3  mov r8,rcx
0x568bce6  mov rax,[rcx+0x2E0]
0x568bced  mov [rbp-0x18],rax
0x568bcf1  xorps xmm0,xmm0
0x568bcf4  movups [rbp-0x10],xmm0
0x568bcf8  mov rax,[rcx+0x2F0]
0x568bcff  test rax,rax
0x568bd02  je short 0x568BD11
0x568bd04  lock inc dword ptr [rax+8]
0x568bd08  mov rax,[r8+0x2F0]
0x568bd0f  jmp short 0x568BD13
0x568bd11  xor eax,eax
0x568bd13  mov rcx,[r8+0x2E8]
0x568bd1a  mov [rbp-0x10],rcx
0x568bd1e  mov [rbp-8],rax
0x568bd22  mov [rcx+0x18],rdx
0x568bd26  mov rcx,[r8+0x70]
0x568bd2a  test rcx,rcx
0x568bd2d  je short 0x568BD8D
0x568bd2f  add r8,0x78
0x568bd33  mov rax,[rcx]
0x568bd36  mov rax,[rax+0x10]
0x568bd3a  lea rdx,[rbp-0x18]
0x568bd3e  call qword ptr [0xF99FFA0]
0x568bd44  nop
0x568bd45  mov rax,[rbp-0x10]
0x568bd49  mov qword ptr [rax+0x18],0
0x568bd51  mov rsi,[rbp-8]
0x568bd55  test rsi,rsi
0x568bd58  je short 0x568BD86
0x568bd5a  lock dec dword ptr [rsi+8]
0x568bd5e  jne short 0x568BD86
0x568bd60  mov rax,[rsi]
0x568bd63  mov rax,[rax]
0x568bd66  mov rcx,rsi
0x568bd69  call qword ptr [0xF99FFA0]
0x568bd6f  lock dec dword ptr [rsi+0xC]
0x568bd73  jne short 0x568BD86
0x568bd75  mov rax,[rsi]
0x568bd78  mov rax,[rax+8]
0x568bd7c  mov rcx,rsi
0x568bd7f  call qword ptr [0xF99FFA0]
0x568bd85  nop
0x568bd86  add rsp,0x48
0x568bd8a  pop rsi
0x568bd8b  pop rbp
0x568bd8c  ret
0x568bd8d  call 0xEEC59E0
0x568bd92  nop
0x568bd93  int3
#endif

} // namespace native
