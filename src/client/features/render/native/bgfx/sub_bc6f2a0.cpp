// LIFT 0xbc6f2a0 size 0xbb 1.26.62.01 sub_bc6f2a0
#include "sub_bc6f2a0.h"

// Lifted body of sub 0xbc6f2a0 (bgfx destroy-handle enqueue, post-cmd 0x1C), size 0xbb, 1.26.62.01.
// Same reads, same writes (value and order), same calls in the same order, same return (void)
// as the exe function at 0xbc6f2a0. Each block carries the instruction range it implements.
// Calls are quoted verbatim beside the call site.
namespace native {

// Layout assertions (canonical constants live in sub_bc6f2a0.h; repeated here so the lift
// is self-checking per docs/RENDER_NATIVE_SPEC.md item 3).
static_assert(offsetof(Context, bgfxLock) == 0x1C0, "sub_bc6f2a0: Context+0x1C0");
static_assert(offsetof(Context, fillFrame) == 0x1CFD0C8, "sub_bc6f2a0: Context+0x1CFD0C8");
static_assert(offsetof(Frame, cmdPostCursor) == 0xE05820, "sub_bc6f2a0: Frame+0xE05820");
static_assert(offsetof(Frame, cmdPostData) == 0xE05828, "sub_bc6f2a0: Frame+0xE05828");
static_assert(offsetof(Frame, handleList) == 0xE45828, "sub_bc6f2a0: Frame+0xE45828");
static_assert(offsetof(Frame, handleListCount) == 0xE47828, "sub_bc6f2a0: Frame+0xE47828");

void sub_bc6f2a0(Context* ctx, std::uint16_t handle)
{
    // 0xbc6f2a0..0xbc6f2c9
    //   0xbc6f2a0  push rbp        0xbc6f2a1  push rsi        0xbc6f2a2  push rdi
    //   0xbc6f2a3  sub rsp,0x40    0xbc6f2a7  lea rbp,[rsp+0x40]
    //   0xbc6f2ac  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    //   0xbc6f2b4  mov esi,edx     0xbc6f2b6  mov rdi,rcx     0xbc6f2b9  mov [rbp-0xC],dx
    //   0xbc6f2bd  add rcx,0x1C0   0xbc6f2c4  mov [rbp-0x18],rcx
    std::uint64_t stackCookie = 0xFFFFFFFFFFFFFFFEULL;  // [rbp-8] (stored, never read back in this function)
    std::uint16_t handleSlot = handle;                  // [rbp-0xC] = dx
    std::uint8_t opcode = 0x1C;                         // [rbp-9] = 0x1C
    void* lockPtr = &ctx->bgfxLock;                     // ctx + 0x1C0
    sub_ebdbf10(lockPtr);                               // 0xbc6f2c8  call 0xEBDBF10  ; lock   [`0xbc6f2c8  call 0xEBDBF10`]

    // 0xbc6f2c9..0xbc6f2ea
    //   0xbc6f2cd  mov rax,[rdi+0x1CFD0C8]     0xbc6f2d4  movzx ecx,word ptr [rax+0xE47828]
    //   0xbc6f2db  mov [rax+rcx*2+0xE45828],si 0xbc6f2e3  inc word ptr [rax+0xE47828]
    Frame* f = ctx->fillFrame;
    std::uint16_t idx = f->handleListCount;
    f->handleList[idx] = handleSlot;
    f->handleListCount = static_cast<std::uint16_t>(idx + 1);

    // 0xbc6f2ea..0xbc6f311
    //   0xbc6f2ea  mov rsi,[rdi+0x1CFD0C8]     0xbc6f2f1  mov byte ptr [rbp-9],0x1C
    //   0xbc6f2f5  mov eax,[rsi+0xE05820]      0xbc6f2fb  lea rcx,[rsi+rax]
    //   0xbc6f2ff  add rcx,0xE05828            0xbc6f306  lea rdx,[rbp-9]
    //   0xbc6f30a  mov r8d,1                   0xbc6f310  call 0xEBCE390
    f = ctx->fillFrame;                                  // 0xbc6f2ea  mov rsi,[rdi+0x1CFD0C8] (reloaded after lock)
    std::uint32_t cursor0 = f->cmdPostCursor;            // 0xbc6f2f5  mov eax,[rsi+0xE05820]
    sub_ebce390(f->cmdPostData + cursor0, &opcode, 1u);  // dst=f+0xE05828+cursor0, src=&opcode, size=1  [`0xbc6f310  call 0xEBCE390`]

    // 0xbc6f311..0xbc6f32a
    //   0xbc6f315  nop               0xbc6f316  lea rax,[rsi+0xE05828]
    //   0xbc6f31d  mov ecx,[rsi+0xE05820]   0xbc6f323  and ecx,0xFFFFFFFE
    //   0xbc6f326  add ecx,2         0xbc6f329  mov [rsi+0xE05820],ecx
    std::uint32_t aligned = (cursor0 & 0xFFFFFFFEu) + 2u;  // 0xbc6f31d  mov ecx,[rsi+0xE05820] / 0xbc6f323  and ecx,0xFFFFFFFE / 0xbc6f326  add ecx,2
    f->cmdPostCursor = aligned;                          // 0xbc6f329  mov [rsi+0xE05820],ecx

    // 0xbc6f32a..0xbc6f343
    //   0xbc6f32f  add rcx,rax       0xbc6f332  lea rdx,[rbp-0xC]
    //   0xbc6f336  mov r8d,2         0xbc6f33c  call 0xEBCE390
    //   0xbc6f341  nop               0xbc6f342  add dword ptr [rsi+0xE05820],2
    sub_ebce390(f->cmdPostData + aligned, &handleSlot, 2u);  // dst=f+0xE05828+aligned, src=&handleSlot, size=2  [`0xbc6f33c  call 0xEBCE390`]
    f->cmdPostCursor = aligned + 2u;                   // 0xbc6f342  add dword ptr [rsi+0xE05820],2

    // 0xbc6f343..0xbc6f35b
    //   0xbc6f349  mov rcx,[rbp-0x18] 0xbc6f34d  call 0xEBDBF20
    //   0xbc6f352  nop               0xbc6f353  add rsp,0x40
    //   0xbc6f357  pop rdi            0xbc6f358  pop rsi
    //   0xbc6f359  pop rbp            0xbc6f35a  ret
    sub_ebdbf20(lockPtr);                               // 0xbc6f34d  call 0xEBDBF20  ; unlock   [`0xbc6f34d  call 0xEBDBF20`]
}

} // namespace native

LIFT_FN(bc6f2a0, "bgfx destroy-handle enqueue (cmd 0x1C)", 0xBC6F2A0, sub_bc6f2a0, nullptr);
