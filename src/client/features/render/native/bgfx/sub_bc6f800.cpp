// LIFT 0xbc6f800 size 0xbb 1.26.62.01 sub_bc6f800
#include "sub_bc6f800.h"

namespace native {

// Lifted body of sub 0xbc6f800 (bgfx destroy-handle enqueue, cmd 0x1D).
// Body span 0xbc6f800..0xbc6f8bb, size 0xbb, 1.26.62.01.
//
// Locks ctx->bgfxLock (sub_ebdbf10), appends handle to fillFrame->handleList
// at index fillFrame->handleListCount and increments the count, then posts
// opcode byte 0x1D and the handle (2 bytes) to fillFrame->cmdPost, advancing
// cmdPostCursor by 1, aligning it up to 2, then adding 2, and releases the
// lock (sub_ebdbf20). Same structure as sub_bc6f2a0, other opcode and tail
// list.
//
// Calls, in order: sub_ebdbf10(lock), sub_ebce390(cmdPost+cursor0,&opcode,1),
// sub_ebce390(cmdPost+aligned,&handleSlot,2), sub_ebdbf20(lock). All three are
// lift-classified callees (native::sub_*) declared in sub_bc6f800.h and called
// directly like any lifted function.
//
// Every block below carries the instruction range it implements; every call is
// quoted verbatim (two spaces after the address), copied from the exe's
// disassembly.
void sub_bc6f800(Context* ctx, std::uint16_t handle)
{
    // 0xbc6f800..0xbc6f829 — prologue: stack sentinel, stash handle, build
    // &ctx->bgfxLock (ctx+0x1C0), call sub_ebdbf10(lock) to take the lock.
    //   0xbc6f800  push rbp
    //   0xbc6f801  push rsi
    //   0xbc6f802  push rdi
    //   0xbc6f803  sub rsp,0x40
    //   0xbc6f807  lea rbp,[rsp+0x40]
    //   0xbc6f80c  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    //   0xbc6f814  mov esi,edx
    //   0xbc6f816  mov rdi,rcx
    //   0xbc6f819  mov [rbp-0xC],dx
    //   0xbc6f81d  add rcx,0x1C0
    //   0xbc6f824  mov [rbp-0x18],rcx
    //   0xbc6f828  call 0xEBDBF10   ; -> sub_ebdbf10   [`0xbc6f828  call 0xEBDBF10`]
    std::uint64_t stackSentinel = 0xFFFFFFFFFFFFFFFEui64;   // [rbp-8]: written, never read in this function
    std::uint16_t handleSlot = handle;                       // [rbp-0xC]
    std::uint32_t* lockPtr = &ctx->bgfxLock;                 // [rbp-0x18] = ctx + 0x1C0
    native::sub_ebdbf10(lockPtr);                            // 0xbc6f828  call 0xEBDBF10   ; -> sub_ebdbf10

    // 0xbc6f829..0xbc6f84a — enqueue the handle on fillFrame->handleList:
    // idx = handleListCount; handleList[idx] = handle; handleListCount++.
    //   0xbc6f82d  mov rax,[rdi+0x1CFD0C8]
    //   0xbc6f834  movzx ecx,word ptr [rax+0xE498AC]
    //   0xbc6f83b  mov [rax+rcx*2+0xE478AC],si
    //   0xbc6f843  inc word ptr [rax+0xE498AC]
    Frame* f = ctx->fillFrame;                      // 0xbc6f82d
    f->handleList[f->handleListCount] = handleSlot;  // 0xbc6f834: idx = handleListCount; 0xbc6f83b: handleList[idx] = handle
    ++f->handleListCount;                            // 0xbc6f843

    // 0xbc6f84a..0xbc6f876 — reload fillFrame, store opcode 0x1D, read
    // cmdPostCursor, append the opcode byte at cmdPostData[cursor0].
    //   0xbc6f84a  mov rsi,[rdi+0x1CFD0C8]
    //   0xbc6f851  mov byte ptr [rbp-9],0x1D
    //   0xbc6f855  mov eax,[rsi+0xE05820]
    //   0xbc6f85b  lea rcx,[rsi+rax]
    //   0xbc6f85f  add rcx,0xE05828
    //   0xbc6f866  lea rdx,[rbp-9]
    //   0xbc6f86a  mov r8d,1
    //   0xbc6f870  call 0xEBCE390   ; -> sub_ebce390   [`0xbc6f870  call 0xEBCE390`]
    //   0xbc6f875  nop
    f = ctx->fillFrame;                               // 0xbc6f84a (fillFrame reloaded after the handle list)
    std::uint8_t opcode = 0x1D;                       // 0xbc6f851
    std::uint32_t cursor0 = f->cmdPostCursor;         // 0xbc6f855
    std::uint8_t* post0 = f->cmdPostData + cursor0;   // 0xbc6f85b: lea rcx,[rsi+rax]; 0xbc6f85f: +0xE05828
    native::sub_ebce390(post0, &opcode, 1);           // 0xbc6f870  call 0xEBCE390   ; -> sub_ebce390 (rdx=&opcode, r8d=1)

    // 0xbc6f876..0xbc6f89d — aligned cursor = (cmdPostCursor & ~1) + 2, stored
    // back, then append the handle (2 bytes) at cmdPostData[aligned].
    //   0xbc6f876  lea rax,[rsi+0xE05828]
    //   0xbc6f87d  mov ecx,[rsi+0xE05820]
    //   0xbc6f883  and ecx,0xFFFFFFFE
    //   0xbc6f886  add ecx,2
    //   0xbc6f889  mov [rsi+0xE05820],ecx
    //   0xbc6f88f  add rcx,rax
    //   0xbc6f892  lea rdx,[rbp-0xC]
    //   0xbc6f896  mov r8d,2
    //   0xbc6f89c  call 0xEBCE390   ; -> sub_ebce390   [`0xbc6f89c  call 0xEBCE390`]
    std::uint8_t* postBase = f->cmdPostData;          // 0xbc6f876
    std::uint32_t cursor1 = f->cmdPostCursor;         // 0xbc6f87d (cursor reloaded after the first call)
    std::uint32_t aligned = (cursor1 & 0xFFFFFFFEu) + 2u;  // 0xbc6f883..0xbc6f886
    f->cmdPostCursor = aligned;                       // 0xbc6f889
    native::sub_ebce390(postBase + aligned, &handleSlot, 2);  // 0xbc6f89c  call 0xEBCE390   ; -> sub_ebce390 (rdx=&handleSlot, r8d=2)

    // 0xbc6f89d..0xbc6f8bb — cmdPostCursor += 2 (aligned+2), release the lock,
    // epilogue.
    //   0xbc6f8a1  nop
    //   0xbc6f8a2  add dword ptr [rsi+0xE05820],2
    //   0xbc6f8a9  mov rcx,[rbp-0x18]
    //   0xbc6f8ad  call 0xEBDBF20   ; -> sub_ebdbf20   [`0xbc6f8ad  call 0xEBDBF20`]
    //   0xbc6f8b2  nop
    //   0xbc6f8b3  add rsp,0x40
    //   0xbc6f8b7  pop rdi
    //   0xbc6f8b8  pop rsi
    //   0xbc6f8b9  pop rbp
    //   0xbc6f8ba  ret
    f->cmdPostCursor = aligned + 2u;                  // 0xbc6f8a2  add dword ptr [rsi+0xE05820],2
    native::sub_ebdbf20(lockPtr);                     // 0xbc6f8ad  call 0xEBDBF20   ; -> sub_ebdbf20
}

} // namespace native

LIFT_FN(bc6f800, "bgfx destroy-handle enqueue (cmd 0x1D)", 0xBC6F800, ::native::sub_bc6f800, nullptr);
