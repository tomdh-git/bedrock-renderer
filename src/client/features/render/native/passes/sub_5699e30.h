#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_5699e30 (0x5699e30, size 0xc4, 1.26.62.01, "pass task render-thread body (class B)").
//
// Same template as sub_568bcd0: publishes the executor context through the task's ViewRef,
// invokes the task's stored std::function (the pass body), then clears execCtx and releases
// the shared_ptr control block.
//
//   0x5699e30  push rbp                                   ; prologue
//   0x5699e31  push rsi                                   ; prologue
//   0x5699e32  sub rsp,0x48                               ; prologue
//   0x5699e36  lea rbp,[rsp+0x40]                         ; frame pointer
//   0x5699e3b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE   ; frame marker
//   0x5699e43  mov r8,rcx                                 ; r8 = task (a0)
//   0x5699e46  mov rax,[rcx+0xA8]                         ; rax = task->arg0
//   0x5699e4d  mov [rbp-0x18],rax                         ; args.a = arg0
//   0x5699e51  xorps xmm0,xmm0                            ; zero args.view/args.ctrl
//   0x5699e54  movups [rbp-0x10],xmm0
//   0x5699e58  mov rax,[rcx+0xB8]                         ; rax = task->ctrl
//   0x5699e5f  test rax,rax
//   0x5699e62  je short 0x5699E71                         ; if null skip addref
//   0x5699e64  lock inc dword ptr [rax+8]               ; ctrl->uses += 1
//   0x5699e68  mov rax,[r8+0xB8]                          ; rax = task->ctrl (same)
//   0x5699e6f  jmp short 0x5699E73
//   0x5699e71  xor eax,eax                                ; rax = 0 (null ctrl)
//   0x5699e73  mov rcx,[r8+0xB0]                          ; rcx = task->viewRef
//   0x5699e7a  mov [rbp-0x10],rcx                         ; args.view = viewRef
//   0x5699e7e  mov [rbp-8],rax                            ; args.ctrl = ctrl
//   0x5699e82  mov [rcx+0x18],rdx                         ; view->execCtx = ctx (arg1)
//   0x5699e86  mov rcx,[r8+0x70]                          ; rcx = task->body
//   0x5699e8a  test rcx,rcx
//   0x5699e8d  je short 0x5699EED                         ; if null -> sub_eec59e0 (_Xbad_function_call)
//   0x5699e8f  add r8,0x78                                ; r8 = task + 0x78
//   0x5699e93  mov rax,[rcx]                              ; rax = *body (vfptr)
//   0x5699e96  mov rax,[rax+0x10]                         ; rax = vfptr[0x10] = _Do_call
//   0x5699e9a  lea rdx,[rbp-0x18]                         ; rdx = &args
//   0x5699e9e  call qword ptr [0xF99FFA0]               ; _Do_call(body, &args, task+0x78)
//   0x5699ea4  nop
//   0x5699ea5  mov rax,[rbp-0x10]                         ; rax = args.view
//   0x5699ea9  mov qword ptr [rax+0x18],0               ; view->execCtx = nullptr
//   0x5699eb1  mov rsi,[rbp-8]                            ; rsi = args.ctrl
//   0x5699eb5  test rsi,rsi
//   0x5699eb8  je short 0x5699EE6                         ; if null skip release
//   0x5699eba  lock dec dword ptr [rsi+8]               ; ctrl->uses -= 1
//   0x5699ebe  jne short 0x5699EE6                        ; if not zero skip dispose
//   0x5699ec0  mov rax,[rsi]                              ; rax = *ctrl (vfptr)
//   0x5699ec3  mov rax,[rax]                              ; rax = vfptr[0] = dispose
//   0x5699ec6  mov rcx,rsi                                ; RCX = ctrl
//   0x5699ec9  call qword ptr [0xF99FFA0]               ; dispose(ctrl)
//   0x5699ecf  lock dec dword ptr [rsi+0xC]             ; ctrl->weaks -= 1
//   0x5699ed3  jne short 0x5699EE6                        ; if not zero skip destroy
//   0x5699ed5  mov rax,[rsi]                              ; rax = *ctrl (vfptr)
//   0x5699ed8  mov rax,[rax+8]                            ; rax = vfptr[8] = destroy
//   0x5699edc  mov rcx,rsi                                ; RCX = ctrl
//   0x5699edf  call qword ptr [0xF99FFA0]               ; destroy(ctrl)
//   0x5699ee5  nop
//   0x5699ee6  add rsp,0x48                               ; epilogue
//   0x5699eea  pop rsi                                    ; epilogue
//   0x5699eeb  pop rbp                                    ; epilogue
//   0x5699eec  ret                                       ; epilogue
//   0x5699eed  call 0xEEC59E0                             ; sub_eec59e0() (_Xbad_function_call, noreturn)
//   0x5699ef2  nop
//   0x5699ef3  int3
//
// x64 Microsoft ABI: RCX = task (PassTask*), RDX = ctx (ExecCtx*), return void.
//
// Layout of fields in 'task' object (a0/RCX) [V]:
//   +0x70 (R, 8 bytes): body (std::function* vfptr; vfptr[0x10] = _Do_call)
//   +0x78 (R): functor args area (_Do_call r8 argument)
//   +0xA8 (R, 8 bytes): arg0 (void* functor argument)
//   +0xB0 (R, 8 bytes): viewRef (ViewRef*)
//   +0xB8 (R/W, 8 bytes): shared_ptr control block (_RefCountBase*)
// Layout of fields in 'ViewRef' (pointed to by task+0xB0) [V]:
//   +0x18 (W, 8 bytes): execCtx (ExecCtx*)
// Layout of fields in control block (pointed to by task+0xB8) [V]:
//   +0x00 (R, 8 bytes): vfptr (vfptr[0]=dispose, vfptr[1]=destroy)
//   +0x08 (R/W, 4 bytes): _Uses shared count (lock inc/dec)
//   +0x0C (R/W, 4 bytes): _Weaks weak count (lock dec)
// Layout of std::function vfptr [V]:
//   +0x10 (R, 8 bytes): _Do_call(body, &args, task+0x78)
// Callees [V]:
//   - sub_eec59e0 (lift set, 0xeec59e0): 1 direct call when body == null
//     (std::_Xbad_function_call via data slot 0xF9A7310, noreturn)
//   - 3x indirect calls through data slot 0xF99FFA0 (sub_eea6040, boundary/vendor):
//     _Do_call (body vfptr[0x10]), dispose (ctrl vfptr[0]), destroy (ctrl vfptr[1])
//     sub_eea6040 is a `jmp rax` thunk (0xeea6040); the caller loads RAX with the target
//     function pointer and the call through the slot forwards RCX/RDX/R8 to it. In the lift
//     the same target is invoked directly through the loaded function pointer (equivalent
//     because the thunk only tail-jumps to RAX).
//
// No null guards or SEH beyond the original's own tests.

// Offset constants for the task object (a0/RCX).
static constexpr std::size_t kTaskOffsetArg0    = 0xA8;
static constexpr std::size_t kTaskOffsetViewRef = 0xB0;
static constexpr std::size_t kTaskOffsetCtrl    = 0xB8;
static constexpr std::size_t kTaskOffsetBody    = 0x70;
static constexpr std::size_t kTaskOffsetFunctor = 0x78;

// Offset constants for the ViewRef object (pointed to by task+0xB0).
static constexpr std::size_t kViewOffsetExecCtx = 0x18;

// Offset constants for the shared_ptr control block (pointed to by task+0xB8).
static constexpr std::size_t kCtrlOffsetVfptr = 0x00;
static constexpr std::size_t kCtrlOffsetUses  = 0x08;
static constexpr std::size_t kCtrlOffsetWeaks = 0x0C;

struct ExecCtx;  // opaque; only the pointer is stored/copied

struct ViewRef {
    std::uint8_t pad0x00[0x18];
    void* execCtx;   // +0x18 [W] execCtx = ctx, then nullptr
};

struct RefCountCtrl {
    void* vfptr;             // +0x00 [R] vfptr (vfptr[0]=dispose, vfptr[1]=destroy)
    std::uint32_t uses;      // +0x08 [R/W] _Uses shared count (lock inc/dec)
    std::uint32_t weaks;     // +0x0C [R/W] _Weaks weak count (lock dec)
};

struct sub_5699e30Layout {
    static_assert(offsetof(ViewRef, execCtx) == kViewOffsetExecCtx,
                  "sub_5699e30_ViewRef: execCtx at +0x18");
    static_assert(offsetof(RefCountCtrl, vfptr) == kCtrlOffsetVfptr,
                  "sub_5699e30_RefCountCtrl: vfptr at +0x00");
    static_assert(offsetof(RefCountCtrl, uses) == kCtrlOffsetUses,
                  "sub_5699e30_RefCountCtrl: uses at +0x08");
    static_assert(offsetof(RefCountCtrl, weaks) == kCtrlOffsetWeaks,
                  "sub_5699e30_RefCountCtrl: weaks at +0x0C");
    static_assert(sizeof(void*) == 8, "sub_5699e30: x64 pointers are 8 bytes");
};

namespace native {

// sub_eec59e0 (0xeec59e0, lift set): jmp qword ptr [0xF9A7310] -> std::_Xbad_function_call; never returns.
[[noreturn]] void sub_eec59e0(void);

// sub_5699e30(void* task, void* ctx) -> void
void sub_5699e30(void* task, void* ctx);

} // namespace native
