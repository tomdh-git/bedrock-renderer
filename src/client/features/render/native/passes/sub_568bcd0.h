#pragma once
#include <cstddef>
#include <cstdint>

#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// sub_568bcd0 (0x568bcd0, size 0xc4, 1.26.62.01, "common pass task render-thread body").
//
// Full instruction-by-instruction reversal:
//   0x568bcd0..0x568bce3  push rbp; push rsi; sub rsp,0x48; lea rbp,[rsp+0x40]; mov [rbp],-2
//   0x568bce3             mov r8,rcx                              ; r8 = task (a0)
//   0x568bce6             mov rax,[rcx+0x2E0]                     ; rax = task->arg0
//   0x568bced             mov [rbp-0x18],rax                      ; args.a = arg0
//   0x568bcf1             xorps xmm0,xmm0                         ; zero args (16 bytes)
//   0x568bcf4             movups [rbp-0x10],xmm0
//   0x568bcf8             mov rax,[rcx+0x2F0]                     ; rax = task->ctrl
//   0x568bcff             test rax,rax
//   0x568bd02             je short 0x568BD11                      ; if null, skip addref
//   0x568bd04             lock inc dword ptr [rax+8]              ; ctrl->uses += 1
//   0x568bd08             mov rax,[r8+0x2F0]                      ; rax = task->ctrl (same)
//   0x568bd0f             jmp short 0x568BD13
// loc_568bd11:
//   0x568bd11             xor eax,eax                             ; rax = 0 (null ctrl)
// loc_568bd13:
//   0x568bd13             mov rcx,[r8+0x2E8]                      ; rcx = task->viewRef
//   0x568bd1a             mov [rbp-0x10],rcx                      ; args.view = viewRef
//   0x568bd1e             mov [rbp-8],rax                         ; args.ctrl = ctrl
//   0x568bd22             mov [rcx+0x18],rdx                      ; view->execCtx = ctx
//   0x568bd26             mov rcx,[r8+0x70]                       ; rcx = task->body
//   0x568bd2a             test rcx,rcx
//   0x568bd2d             je short 0x568BD8D                      ; if null -> _Xbad_function_call
//   0x568bd2f             add r8,0x78                             ; r8 = task + 0x78
//   0x568bd33             mov rax,[rcx]                           ; rax = *body (vfptr)
//   0x568bd36             mov rax,[rax+0x10]                      ; rax = vfptr[0x10] = _Do_call
//   0x568bd3a             lea rdx,[rbp-0x18]                      ; rdx = &args
//   0x568bd3e             call qword ptr [0xF99FFA0]              ; _Do_call(body, &args, task+0x78)
//   0x568bd44             nop
//   0x568bd45             mov rax,[rbp-0x10]                      ; rax = args.view
//   0x568bd49             mov qword ptr [rax+0x18],0              ; view->execCtx = nullptr
//   0x568bd51             mov rsi,[rbp-8]                         ; rsi = args.ctrl
//   0x568bd55             test rsi,rsi
//   0x568bd58             je short 0x568BD86                      ; if null, skip release
//   0x568bd5a             lock dec dword ptr [rsi+8]              ; ctrl->uses -= 1
//   0x568bd5e             jne short 0x568BD86                     ; if not zero, skip dispose
//   0x568bd60             mov rax,[rsi]                           ; rax = *ctrl (vfptr)
//   0x568bd63             mov rax,[rax]                           ; rax = vfptr[0] = dispose
//   0x568bd66             mov rcx,rsi                             ; RCX = ctrl
//   0x568bd69             call qword ptr [0xF99FFA0]              ; dispose(ctrl)
//   0x568bd6f             lock dec dword ptr [rsi+0xC]            ; ctrl->weaks -= 1
//   0x568bd73             jne short 0x568BD86                     ; if not zero, skip destroy
//   0x568bd75             mov rax,[rsi]                           ; rax = *ctrl (vfptr)
//   0x568bd78             mov rax,[rax+8]                         ; rax = vfptr[8] = destroy
//   0x568bd7c             mov rcx,rsi                             ; RCX = ctrl
//   0x568bd7f             call qword ptr [0xF99FFA0]              ; destroy(ctrl)
//   0x568bd85             nop
// loc_568bd86:
//   0x568bd86             add rsp,0x48
//   0x568bd8a             pop rsi
//   0x568bd8b             pop rbp
//   0x568bd8c             ret
// loc_568bd8d:
//   0x568bd8d             call 0xEEC59E0                          ; std::_Xbad_function_call (noreturn)
//   0x568bd92             nop
//   0x568bd93             int3
//
// x64 Microsoft ABI: RCX = task (PassTask*), RDX = ctx (ExecCtx*), return void.
//
// Layout of fields in 'task' object (a0/RCX) [V]:
//   +0x2E0 (R, 8 bytes): arg0 (void* functor argument)
//   +0x2E8 (R, 8 bytes): viewRef (ViewRef*)
//   +0x2F0 (R/W, 8 bytes): shared_ptr control block (_RefCountBase*)
//   +0x70 (R, 8 bytes): body (std::function* vfptr)
//   +0x78 (R): functor args area (_Do_call r8 argument)
// Layout of fields in 'ViewRef' (pointed to by task+0x2E8) [V]:
//   +0x18 (W, 8 bytes): execCtx (ExecCtx*)
// Layout of fields in control block (pointed to by task+0x2F0) [V]:
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
static constexpr std::size_t kTaskOffsetArg0    = 0x2E0;
static constexpr std::size_t kTaskOffsetViewRef = 0x2E8;
static constexpr std::size_t kTaskOffsetCtrl    = 0x2F0;
static constexpr std::size_t kTaskOffsetBody    = 0x70;
static constexpr std::size_t kTaskOffsetFunctor = 0x78;

// Offset constants for the ViewRef object (pointed to by task+0x2E8).
static constexpr std::size_t kViewOffsetExecCtx = 0x18;

// Offset constants for the shared_ptr control block (pointed to by task+0x2F0).
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

struct sub_568bcd0Layout {
    static_assert(offsetof(ViewRef, execCtx) == kViewOffsetExecCtx,
                  "sub_568bcd0_ViewRef: execCtx at +0x18");
    static_assert(offsetof(RefCountCtrl, vfptr) == kCtrlOffsetVfptr,
                  "sub_568bcd0_RefCountCtrl: vfptr at +0x00");
    static_assert(offsetof(RefCountCtrl, uses) == kCtrlOffsetUses,
                  "sub_568bcd0_RefCountCtrl: uses at +0x08");
    static_assert(offsetof(RefCountCtrl, weaks) == kCtrlOffsetWeaks,
                  "sub_568bcd0_RefCountCtrl: weaks at +0x0C");
    static_assert(sizeof(void*) == 8, "sub_568bcd0: x64 pointers are 8 bytes");
};

namespace native {

// sub_eec59e0 (0xeec59e0, lift set): jmp qword ptr [0xF9A7310] -> std::_Xbad_function_call; never returns.
[[noreturn]] void sub_eec59e0(void);

// sub_568bcd0(void* task, void* ctx) -> void
void sub_568bcd0(void* task, void* ctx);

} // namespace native
