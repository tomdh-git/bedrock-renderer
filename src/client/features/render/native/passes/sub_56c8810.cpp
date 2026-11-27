// LIFT 0x56c8810 size 0xc4 1.26.62.01 sub_56c8810
#include "sub_56c8810.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_56c8810 (0x56c8810, size 0xc4, 1.26.62.01, "pass task render-thread body (class C, same template)").
//
// Called by the D3D12 executor for a custom render item. Publishes the executor context
// through the task's ViewRef, invokes the task's stored std::function (the pass body),
// then clears execCtx and releases the shared_ptr control block.
//
// Reads: task+0x100 (arg0), task+0x108 (viewRef), task+0x110 (ctrl), *ctrl (vfptr),
//   ctrl+0x08 (uses), ctrl+0x0C (weaks), *ctrl vfptr[0] (dispose), *ctrl vfptr[1] (destroy),
//   task+0x70 (body), *body (vfptr), *body vfptr[0x10] (_Do_call), view+0x18 (execCtx).
// Writes: view+0x18 (execCtx = ctx, then nullptr), ctrl+0x08 (lock dec), ctrl+0x0C (lock dec).
// Calls: sub_eec59e0 (lift set, noreturn); 3x indirect via data slot 0xF99FFA0
//   (_Do_call, dispose, destroy through sub_eea6040 thunk).
// Return: void.
// Same reads, same writes, same calls in the same order, same return. Nothing else
// happens in [0x56c8810, 0x56c88d4).

// PassArgs layout on the stack at [rbp-0x18, rbp): { arg0, view, ctrl } = 0x18 bytes.
// Matches task tail { arg0 at +0x100, viewRef* at +0x108, ctrl* at +0x110 }.
struct PassArgs {
    void* a;               // +0x00 = task->arg0
    void* view;            // +0x08 = task->viewRef
    RefCountCtrl* ctrl;    // +0x10 = task->ctrl
};

// 0x56c8810..0x56c88d4
void sub_56c8810(void* task, void* ctx)
{
    static_assert(sizeof(void*) == 8, "sub_56c8810: x64 pointers and arguments are 8 bytes");

    // 0x56c8810..0x56c8823  prologue: push rbp; push rsi; sub rsp,0x48; lea rbp,[rsp+0x40]; mov [rbp],-2
    void* const a0 = task;   // RCX = task object
    void* const a1 = ctx;    // RDX = ctx (ExecCtx*)

    // 0x56c8823  mov r8,rcx   (r8 == a0 throughout)

    // PassArgs on the stack at [rbp-0x18, rbp): { arg0, view, ctrl }
    PassArgs args;

    // 0x56c8826  mov rax,[rcx+0x100]      ; rax = task->arg0
    // 0x56c882d  mov [rbp-0x18],rax       ; args.a = arg0
    args.a = *reinterpret_cast<void**>(
        reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetArg0);   // 0x56c8826  mov rax,[rcx+0x100]
                                                                   // 0x56c882d  mov [rbp-0x18],rax

    // 0x56c8831  xorps xmm0,xmm0
    // 0x56c8834  movups [rbp-0x10],xmm0   ; zero args.view and args.ctrl (16 bytes)
    args.view = nullptr;     // 0x56c8831  xorps xmm0,xmm0
                             // 0x56c8834  movups [rbp-0x10],xmm0  (low qword)
    args.ctrl = nullptr;     // 0x56c8834  movups [rbp-0x10],xmm0  (high qword)

    // 0x56c8838  mov rax,[rcx+0x110]      ; rax = task->ctrl
    // 0x56c883f  test rax,rax
    // 0x56c8842  je short 0x56C8851       ; if null, skip addref
    // 0x56c8844  lock inc dword ptr [rax+8]   ; ctrl->uses += 1
    // 0x56c8848  mov rax,[r8+0x110]       ; rax = task->ctrl (same value)
    // 0x56c884f  jmp short 0x56C8853
    RefCountCtrl* const ctrl =
        *reinterpret_cast<RefCountCtrl**>(
            reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetCtrl);  // 0x56c8838  mov rax,[rcx+0x110]
    if (ctrl != nullptr) {                                             // 0x56c883f  test rax,rax
                                                                         // 0x56c8842  je short 0x56C8851
        _InterlockedIncrement(                                         // 0x56c8844  lock inc dword ptr [rax+8]
            reinterpret_cast<volatile long*>(
                reinterpret_cast<std::uint8_t*>(ctrl) + kCtrlOffsetUses));
    }
    // 0x56c8848  mov rax,[r8+0x110]   ; reload (same value as ctrl)
    // 0x56c884f  jmp short 0x56C8853

    // loc_56c8851:  (ctrl == null path, rax = 0)
    // loc_56c8853:
    // 0x56c8853  mov rcx,[r8+0x108]      ; rcx = task->viewRef
    // 0x56c885a  mov [rbp-0x10],rcx      ; args.view = viewRef
    // 0x56c885e  mov [rbp-8],rax         ; args.ctrl = ctrl
    // 0x56c8862  mov [rcx+0x18],rdx      ; view->execCtx = ctx
    ViewRef* const view =
        *reinterpret_cast<ViewRef**>(
            reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetViewRef);  // 0x56c8853  mov rcx,[r8+0x108]
    args.view = view;                                                    // 0x56c885a  mov [rbp-0x10],rcx
    args.ctrl = ctrl;                                                    // 0x56c885e  mov [rbp-8],rax
    view->execCtx = a1;                                                  // 0x56c8862  mov [rcx+0x18],rdx

    // 0x56c8866  mov rcx,[r8+0x70]        ; rcx = task->body
    // 0x56c886a  test rcx,rcx
    // 0x56c886d  je short 0x56C88CD       ; if null -> _Xbad_function_call
    void* const body =
        *reinterpret_cast<void**>(
            reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetBody);   // 0x56c8866  mov rcx,[r8+0x70]
    if (body == nullptr) {                                             // 0x56c886a  test rcx,rcx
                                                                         // 0x56c886d  je short 0x56C88CD
        // 0x56c88cd  call 0xEEC59E0        ; std::_Xbad_function_call (noreturn)
        sub_eec59e0();                                                  // 0x56c88cd  call 0xEEC59E0
        // unreachable (sub_eec59e0 is [[noreturn]])
    }

    // 0x56c886f  add r8,0x78              ; r8 = task + 0x78
    // 0x56c8873  mov rax,[rcx]            ; rax = *body (vfptr)
    // 0x56c8876  mov rax,[rax+0x10]       ; rax = vfptr[0x10] = _Do_call
    // 0x56c887a  lea rdx,[rbp-0x18]       ; rdx = &args
    // 0x56c887e  call qword ptr [0xF99FFA0]  ; _Do_call(body, &args, task+0x78)
    void** const bodyVfptr =
        *reinterpret_cast<void***>(body);                            // 0x56c8873  mov rax,[rcx]
                                                                       // 0x56c8876  mov rax,[rax+0x10]
    using DoCallFn = void (__cdecl*)(void* body, void* args, void* taskArgs);
    DoCallFn const doCall =
        reinterpret_cast<DoCallFn>(bodyVfptr[4]);                    // vfptr[0x10] = _Do_call
    doCall(body, &args,                                              // 0x56c887a  lea rdx,[rbp-0x18]
           reinterpret_cast<std::uint8_t*>(a0) + kTaskOffsetFunctor); // 0x56c886f  add r8,0x78
                                                                       // 0x56c887e  call qword ptr [0xF99FFA0]

    // 0x56c8885  mov rax,[rbp-0x10]       ; rax = args.view
    // 0x56c8889  mov qword ptr [rax+0x18],0   ; view->execCtx = nullptr
    view->execCtx = nullptr;                                           // 0x56c8885  mov rax,[rbp-0x10]
                                                                         // 0x56c8889  mov qword ptr [rax+0x18],0

    // 0x56c8891  mov rsi,[rbp-8]          ; rsi = args.ctrl
    // 0x56c8895  test rsi,rsi
    // 0x56c8898  je short 0x56C88C6       ; if null, skip release
    // 0x56c889a  lock dec dword ptr [rsi+8]   ; ctrl->uses -= 1
    // 0x56c889e  jne short 0x56C88C6      ; if not zero, skip dispose
    if (ctrl != nullptr) {                                             // 0x56c8895  test rsi,rsi
                                                                         // 0x56c8898  je short 0x56C88C6
        if (_InterlockedDecrement(                                     // 0x56c889a  lock dec dword ptr [rsi+8]
                reinterpret_cast<volatile long*>(
                    reinterpret_cast<std::uint8_t*>(ctrl) +
                    kCtrlOffsetUses)) == 0) {                          // 0x56c889e  jne short 0x56C88C6
            // 0x56c88a0  mov rax,[rsi]        ; rax = *ctrl (vfptr)
            // 0x56c88a3  mov rax,[rax]        ; rax = vfptr[0] = dispose
            // 0x56c88a6  mov rcx,rsi          ; RCX = ctrl
            // 0x56c88a9  call qword ptr [0xF99FFA0]   ; dispose(ctrl)
            void** const ctrlVfptr =
                *reinterpret_cast<void***>(ctrl);                    // 0x56c88a0  mov rax,[rsi]
                                                                       // 0x56c88a3  mov rax,[rax]
            using DisposeFn = void (__cdecl*)(void* ctrl);
            DisposeFn const dispose =
                reinterpret_cast<DisposeFn>(ctrlVfptr[0]);           // vfptr[0] = dispose
            dispose(ctrl);                                           // 0x56c88a6  mov rcx,rsi
                                                                     // 0x56c88a9  call qword ptr [0xF99FFA0]

            // 0x56c88af  lock dec dword ptr [rsi+0xC]   ; ctrl->weaks -= 1
            // 0x56c88b3  jne short 0x56C88C6      ; if not zero, skip destroy
            if (_InterlockedDecrement(                                // 0x56c88af  lock dec dword ptr [rsi+0xC]
                    reinterpret_cast<volatile long*>(
                        reinterpret_cast<std::uint8_t*>(ctrl) +
                        kCtrlOffsetWeaks)) == 0) {                    // 0x56c88b3  jne short 0x56C88C6
                // 0x56c88b5  mov rax,[rsi]        ; rax = *ctrl (vfptr)
                // 0x56c88b8  mov rax,[rax+8]      ; rax = vfptr[8] = destroy
                // 0x56c88bc  mov rcx,rsi          ; RCX = ctrl
                // 0x56c88bf  call qword ptr [0xF99FFA0]   ; destroy(ctrl)
                using DestroyFn = void (__cdecl*)(void* ctrl);
                DestroyFn const destroy =
                    reinterpret_cast<DestroyFn>(ctrlVfptr[1]);       // vfptr[1] = destroy
                destroy(ctrl);                                       // 0x56c88bc  mov rcx,rsi
                                                                     // 0x56c88bf  call qword ptr [0xF99FFA0]
            }
        }
    }

    // 0x56c88c6  add rsp,0x48
    // 0x56c88ca  pop rsi
    // 0x56c88cb  pop rbp
    // 0x56c88cc  ret
}

LIFT_FN(sub_56c8810, "sub_56c8810", 0x56C8810, ::native::sub_56c8810, nullptr);

// Verbatim instructions of [0x56c8810, 0x56c88d4) (rdis dis 0x56c8810 0xc4);
// machine-checked by tools/sigs/verify_oc.py against the exe.
#if 0
0x56c8810  push rbp
0x56c8811  push rsi
0x56c8812  sub rsp,0x48
0x56c8816  lea rbp,[rsp+0x40]
0x56c881b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x56c8823  mov r8,rcx
0x56c8826  mov rax,[rcx+0x100]
0x56c882d  mov [rbp-0x18],rax
0x56c8831  xorps xmm0,xmm0
0x56c8834  movups [rbp-0x10],xmm0
0x56c8838  mov rax,[rcx+0x110]
0x56c883f  test rax,rax
0x56c8842  je short 0x56C8851
0x56c8844  lock inc dword ptr [rax+8]
0x56c8848  mov rax,[r8+0x110]
0x56c884f  jmp short 0x56C8853
0x56c8851  xor eax,eax
0x56c8853  mov rcx,[r8+0x108]
0x56c885a  mov [rbp-0x10],rcx
0x56c885e  mov [rbp-8],rax
0x56c8862  mov [rcx+0x18],rdx
0x56c8866  mov rcx,[r8+0x70]
0x56c886a  test rcx,rcx
0x56c886d  je short 0x56C88CD
0x56c886f  add r8,0x78
0x56c8873  mov rax,[rcx]
0x56c8876  mov rax,[rax+0x10]
0x56c887a  lea rdx,[rbp-0x18]
0x56c887e  call qword ptr [0xF99FFA0]
0x56c8884  nop
0x56c8885  mov rax,[rbp-0x10]
0x56c8889  mov qword ptr [rax+0x18],0
0x56c8891  mov rsi,[rbp-8]
0x56c8895  test rsi,rsi
0x56c8898  je short 0x56C88C6
0x56c889a  lock dec dword ptr [rsi+8]
0x56c889e  jne short 0x56C88C6
0x56c88a0  mov rax,[rsi]
0x56c88a3  mov rax,[rax]
0x56c88a6  mov rcx,rsi
0x56c88a9  call qword ptr [0xF99FFA0]
0x56c88af  lock dec dword ptr [rsi+0xC]
0x56c88b3  jne short 0x56C88C6
0x56c88b5  mov rax,[rsi]
0x56c88b8  mov rax,[rax+8]
0x56c88bc  mov rcx,rsi
0x56c88bf  call qword ptr [0xF99FFA0]
0x56c88c5  nop
0x56c88c6  add rsp,0x48
0x56c88ca  pop rsi
0x56c88cb  pop rbp
0x56c88cc  ret
0x56c88cd  call 0xEEC59E0
0x56c88d2  nop
0x56c88d3  int3
#endif

} // namespace native
