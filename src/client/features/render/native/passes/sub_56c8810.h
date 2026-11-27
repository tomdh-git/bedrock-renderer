#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_56c8810 (0x56c8810, size 0xc4, 1.26.62.01, "pass task render-thread body (class C, same template)").
//
// Full instruction-by-instruction reversal:
//   0x56c8810..0x56c8823  push rbp; push rsi; sub rsp,0x48; lea rbp,[rsp+0x40]; mov [rbp],-2
//   0x56c8823             mov r8,rcx                              ; r8 = task (a0)
//   0x56c8826             mov rax,[rcx+0x100]                     ; rax = task->arg0
//   0x56c882d             mov [rbp-0x18],rax                      ; args.a = arg0
//   0x56c8831             xorps xmm0,xmm0                         ; zero args (16 bytes)
//   0x56c8834             movups [rbp-0x10],xmm0
//   0x56c8838             mov rax,[rcx+0x110]                     ; rax = task->ctrl
//   0x56c883f             test rax,rax
//   0x56c8842             je short 0x56C8851                      ; if null, skip addref
//   0x56c8844             lock inc dword ptr [rax+8]              ; ctrl->uses += 1
//   0x56c8848             mov rax,[r8+0x110]                      ; rax = task->ctrl (same)
//   0x56c884f             jmp short 0x56C8853
// loc_56c8851:
//   0x56c8851             xor eax,eax                             ; rax = 0 (null ctrl)
// loc_56c8853:
//   0x56c8853             mov rcx,[r8+0x108]                      ; rcx = task->viewRef
//   0x56c885a             mov [rbp-0x10],rcx                      ; args.view = viewRef
//   0x56c885e             mov [rbp-8],rax                         ; args.ctrl = ctrl
//   0x56c8862             mov [rcx+0x18],rdx                      ; view->execCtx = ctx
//   0x56c8866             mov rcx,[r8+0x70]                       ; rcx = task->body
//   0x56c886a             test rcx,rcx
//   0x56c886d             je short 0x56C88CD                      ; if null -> _Xbad_function_call
//   0x56c886f             add r8,0x78                             ; r8 = task + 0x78
//   0x56c8873             mov rax,[rcx]                           ; rax = *body (vfptr)
//   0x56c8876             mov rax,[rax+0x10]                      ; rax = vfptr[0x10] = _Do_call
//   0x56c887a             lea rdx,[rbp-0x18]                      ; rdx = &args
//   0x56c887e             call qword ptr [0xF99FFA0]              ; _Do_call(body, &args, task+0x78)
//   0x56c8884             nop
//   0x56c8885             mov rax,[rbp-0x10]                      ; rax = args.view
//   0x56c8889             mov qword ptr [rax+0x18],0              ; view->execCtx = nullptr
//   0x56c8891             mov rsi,[rbp-8]                         ; rsi = args.ctrl
//   0x56c8895             test rsi,rsi
//   0x56c8898             je short 0x56C88C6                      ; if null, skip release
//   0x56c889a             lock dec dword ptr [rsi+8]              ; ctrl->uses -= 1
//   0x56c889e             jne short 0x56C88C6                     ; if not zero, skip dispose
//   0x56c88a0             mov rax,[rsi]                           ; rax = *ctrl (vfptr)
//   0x56c88a3             mov rax,[rax]                           ; rax = vfptr[0] = dispose
//   0x56c88a6             mov rcx,rsi                             ; RCX = ctrl
//   0x56c88a9             call qword ptr [0xF99FFA0]              ; dispose(ctrl)
//   0x56c88af             lock dec dword ptr [rsi+0xC]            ; ctrl->weaks -= 1
//   0x56c88b3             jne short 0x56C88C6                     ; if not zero, skip destroy
//   0x56c88b5             mov rax,[rsi]                           ; rax = *ctrl (vfptr)
//   0x56c88b8             mov rax,[rax+8]                         ; rax = vfptr[8] = destroy
//   0x56c88bc             mov rcx,rsi                             ; RCX = ctrl
//   0x56c88bf             call qword ptr [0xF99FFA0]              ; destroy(ctrl)
//   0x56c88c5             nop
// loc_56c88c6:
//   0x56c88c6             add rsp,0x48
//   0x56c88ca             pop rsi
//   0x56c88cb             pop rbp
//   0x56c88cc             ret
// loc_56c88cd:
//   0x56c88cd             call 0xEEC59E0                          ; std::_Xbad_function_call (noreturn)
//   0x56c88d2             nop
//   0x56c88d3             int3
//
// x64 Microsoft ABI: RCX = task (PassTask*), RDX = ctx (ExecCtx*), return void.
//
// Layout of fields in 'task' object (a0/RCX) [V]:
//   +0x100 (R, 8 bytes): arg0 (void* functor argument)
//   +0x108 (R, 8 bytes): viewRef (ViewRef*)
//   +0x110 (R/W, 8 bytes): shared_ptr control block (_RefCountBase*)
//   +0x70 (R, 8 bytes): body (std::function* vfptr)
//   +0x78 (R): functor args area (_Do_call r8 argument)
// Layout of fields in 'ViewRef' (pointed to by task+0x108) [V]:
//   +0x18 (W, 8 bytes): execCtx (ExecCtx*)
// Layout of fields in control block (pointed to by task+0x110) [V]:
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
//
// No null guards or SEH beyond the original's own tests.

// Offset constants for the task object (a0/RCX).
static constexpr std::size_t kTaskOffsetArg0    = 0x100;
static constexpr std::size_t kTaskOffsetViewRef = 0x108;
static constexpr std::size_t kTaskOffsetCtrl    = 0x110;
static constexpr std::size_t kTaskOffsetBody    = 0x70;
static constexpr std::size_t kTaskOffsetFunctor = 0x78;

// Offset constants for the ViewRef object (pointed to by task+0x108).
static constexpr std::size_t kViewOffsetExecCtx = 0x18;

// Offset constants for the shared_ptr control block (pointed to by task+0x110).
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

struct sub_56c8810Layout {
    static_assert(offsetof(ViewRef, execCtx) == kViewOffsetExecCtx,
                  "sub_56c8810_ViewRef: execCtx at +0x18");
    static_assert(offsetof(RefCountCtrl, vfptr) == kCtrlOffsetVfptr,
                  "sub_56c8810_RefCountCtrl: vfptr at +0x00");
    static_assert(offsetof(RefCountCtrl, uses) == kCtrlOffsetUses,
                  "sub_56c8810_RefCountCtrl: uses at +0x08");
    static_assert(offsetof(RefCountCtrl, weaks) == kCtrlOffsetWeaks,
                  "sub_56c8810_RefCountCtrl: weaks at +0x0C");
    static_assert(sizeof(void*) == 8, "sub_56c8810: x64 pointers are 8 bytes");
};

namespace native {

// sub_eec59e0 (0xeec59e0, lift set): jmp qword ptr [0xF9A7310] -> std::_Xbad_function_call; never returns.
[[noreturn]] void sub_eec59e0(void);

// sub_56c8810(void* task, void* ctx) -> void
void sub_56c8810(void* task, void* ctx);

} // namespace native
