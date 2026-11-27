// LIFT 0x6ae330 size 0xd4 1.26.62.01 sub_6ae330
#include "sub_6ae330.h"

#include <intrin.h>

#include "client/features/render/native/Lift.h"

namespace native {

// sub_6ae330 (0x6ae330, size 0xd4, 1.26.62.01): walks the element range [a0+0x00..a0+0x08) in steps
// of 0x18. For each element it releases the vfptr object at [elem+0x10] through the eea6040 thunk
// with flag 1, then lock-dec's the refcount at [elem+8+0xC] and, when it reaches zero, releases
// [elem+8] through the eea6040 thunk. After the loop it calls sub_e935700 on a derived pointer and
// clears [a0+0x00..0x17]. If the derived size check fails it calls the fatal thunk at data slot
// 0xF9A8C78 with four null arguments and does not return (int3). RCX = a0, return void
// [V: rdis dis 0x6ae330 0xd4].

using Eea6040Callee = void (*)(void* object, int flag);
using FatalCallee = void (*)(void* a, void* b, void* c, void* d);

static void callEea6040(void* object, int flag)
{
    auto fn = reinterpret_cast<Eea6040Callee>(
        *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + kEea6040SlotRva));
    fn(object, flag);
}

static void callFatalSlot(void* a, void* b, void* c, void* d)
{
    auto fn = reinterpret_cast<FatalCallee>(
        *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + kFatalSlotRva));
    fn(a, b, c, d);
}

void sub_6ae330(void* a0)
{
    // 0x6ae330..0x6ae351
    //   0x6ae330  push rsi
    //   0x6ae331  push rdi
    //   0x6ae332  push rbx
    //   0x6ae333  sub rsp,0x30
    //   0x6ae337  mov rdi,[rcx]           ; rdi = [a0+0x00] start
    //   0x6ae33a  test rdi,rdi
    //   0x6ae33d  je 0x6AE3E2              ; start == 0 -> epilogue (ret)
    //   0x6ae343  mov rsi,rcx              ; rsi = a0
    //   0x6ae346  mov rbx,[rcx+8]          ; rbx = [a0+0x08] iteration end
    //   0x6ae34a  cmp rdi,rbx
    //   0x6ae34d  jne short 0x6AE369       ; start != end -> process element at rdi (no increment yet)
    //   0x6ae34f jmp short 0x6AE3A4        ; start == end -> post loop
    //   0x6ae351 nop [rax+rax]
    Sub6ae330This* thisObj = reinterpret_cast<Sub6ae330This*>(a0);
    uintptr_t rdi = reinterpret_cast<uintptr_t>(thisObj->field00);
    void* rsi = a0;
    uintptr_t rbx = reinterpret_cast<uintptr_t>(thisObj->field08);
    Sub6ae330Elem* elem = nullptr;
    void* rcx = nullptr;
    (void)rsi;
    if (rdi == 0) {
        // 0x6ae33d je short 0x6AE3E2
        return;
    }
    if (rdi != rbx) {
        // 0x6ae34d jne short 0x6AE369 -> process element at current rdi
        goto process_element;
    }
    // 0x6ae34f jmp short 0x6AE3A4
    goto post_loop;

loop_increment:
    // 0x6ae360..0x6ae367
    //   0x6ae360  add rdi,0x18
    //   0x6ae364  cmp rdi,rbx
    //   0x6ae367  je short 0x6AE3A1         ; rdi == end -> loop done
    rdi += 0x18;
    if (rdi == rbx) {
        goto loop_done;
    }
    goto process_element;

process_element:
    // 0x6ae369..0x6ae37d
    //   0x6ae369  mov rcx,[rdi+0x10]           ; rcx = element[0x10] vfptr object
    //   0x6ae36d  test rcx,rcx
    //   0x6ae370  je short 0x6AE383          ; null -> skip vfptr release
    //   0x6ae372  mov rax,[rcx]              ; rax = object->vfptr
    //   0x6ae375  mov rax,[rax]              ; rax = vfptr[0]
    //   0x6ae378  mov edx,1                  ; flag = 1
    //   0x6ae37d  call qword ptr [0xF99FFA0]  ; sub_eea6040(object, 1)  [vendor boundary via data slot]
    // 0x6ae383..0x6ae39f
    //   0x6ae383  mov rcx,[rdi+8]              ; rcx = element[8] refcounted object
    //   0x6ae387  test rcx,rcx
    //   0x6ae38a  je short 0x6AE360          ; null -> increment
    //   0x6ae38c  lock dec dword ptr [rcx+0xC]  ; --object->count
    //   0x6ae390  jne short 0x6AE360         ; count != 0 -> increment
    //   0x6ae392  mov rax,[rcx]              ; rax = object->vfptr
    //   0x6ae395  mov rax,[rax+8]            ; rax = vfptr[8]
    //   0x6ae399  call qword ptr [0xF99FFA0]  ; sub_eea6040(object)      [vendor boundary via data slot]
    //   0x6ae39f  jmp short 0x6AE360         ; increment
    elem = reinterpret_cast<Sub6ae330Elem*>(rdi);
    rcx = elem->field10;
    if (rcx != nullptr) {
        // 0x6ae378 mov edx,1 ; 0x6ae37d call qword ptr [0xF99FFA0]
        callEea6040(rcx, 1);
    }
    rcx = elem->field08;
    if (rcx != nullptr) {
        // 0x6ae38c lock dec dword ptr [rcx+0xC]
        volatile long* count = reinterpret_cast<volatile long*>(reinterpret_cast<char*>(rcx) + 0xC);
        if (InterlockedDecrement(count) == 0) {
            // 0x6ae392 mov rax,[rcx] ; 0x6ae395 mov rax,[rax+8] ; 0x6ae399 call qword ptr [0xF99FFA0]
            // RDX is not reloaded before this call; it holds whatever the previous call left.
            callEea6040(rcx, 1);
        }
    }
    goto loop_increment;

loop_done:
    // 0x6ae3a1..0x6ae3a1
    //   0x6ae3a1  mov rdi,[rsi]               ; rdi = [a0+0x00] = start (reloaded)
    rdi = reinterpret_cast<uintptr_t>(thisObj->field00);

post_loop:
    // 0x6ae3a4..0x6ae3c9
    //   0x6ae3a4  mov rdx,[rsi+0x10]           ; rdx = [a0+0x10]
    //   0x6ae3a8  sub rdx,rdi                  ; rdx = [a0+0x10] - start   (byte difference)
    //   0x6ae3ab  cmp rdx,0x1000
    //   0x6ae3b2  jb short 0x6AE3CC         ; size < 0x1000 -> call sub_e935700(rdi)
    {
        uintptr_t rdx = reinterpret_cast<uintptr_t>(thisObj->field10) - rdi;
        if (rdx < 0x1000) {
            // 0x6ae3cc mov rcx,rdi ; 0x6ae3cf call 0xE935700
            native::sub_e935700(reinterpret_cast<void*>(rdi));
            goto cleared;
        }
        // 0x6ae3b4 mov rax,[rdi-8]         ; rax = *(start - 8)
        // 0x6ae3b8 add rdi,0xFFFFFFFFFFFFFFF8   ; rdi -= 8
        // 0x6ae3bc sub rdi,rax             ; rdi = (start-8) - *(start-8)
        // 0x6ae3bf cmp rdi,0x20
        //   0x6ae3c3 jae short 0x6AE3EA    ; rdi >= 0x20 -> fatal path
        //   0x6ae3c5 add rdx,0x27
        //   0x6ae3c9 mov rdi,rax           ; rdi = *(start-8)
        uintptr_t rax = reinterpret_cast<uintptr_t>(*reinterpret_cast<void**>(rdi - 8));
        uintptr_t rdi2 = rdi - 8;
        rdi2 = rdi2 - rax;
        if (rdi2 >= 0x20) {
            // 0x6ae3c3 jae short 0x6AE3EA
            goto error_path;
        }
        rdx += 0x27;
        rdi = rax;
        // 0x6ae3cc mov rcx,rdi ; 0x6ae3cf call 0xE935700
        native::sub_e935700(reinterpret_cast<void*>(rdi));
    }

cleared:
    // 0x6ae3cc..0x6ae3da
    //   0x6ae3d4  xorps xmm0,xmm0
    //   0x6ae3d7  movups [rsi],xmm0           ; [a0+0x00..0x0F] = 0
    //   0x6ae3da  mov qword ptr [rsi+0x10],0  ; [a0+0x10..0x17] = 0
    *reinterpret_cast<uint64_t*>(a0) = 0;
    *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(a0) + 0x10) = 0;
    goto epilogue;

error_path:
    // 0x6ae3ea..0x6ae403
    //   0x6ae3ea  mov qword ptr [rsp+0x20],0
    //   0x6ae3f3  xor ecx,ecx
    //   0x6ae3f5  xor edx,edx
    //   0x6ae3f7  xor r8d,r8d
    //   0x6ae3fa  xor r9d,r9d
    //   0x6ae3fd  call qword ptr [0xF9A8C78]   ; fatal via data slot, all four args zero
    //   0x6ae403  int3                          ; does not return
    callFatalSlot(nullptr, nullptr, nullptr, nullptr);
    __assume(false);   // original: int3, control never continues

epilogue:
    // 0x6ae3e2..0x6ae3e9
    //   0x6ae3e2  add rsp,0x30
    //   0x6ae3e6  pop rbx
    //   0x6ae3e7  pop rdi
    //   0x6ae3e8  pop rsi
    //   0x6ae3e9  ret
    return;
}

// Verbatim call quotes for liftcheck verification (every `call` in the function).
#if 0
0x6ae37d  call qword ptr [0xF99FFA0]
0x6ae399  call qword ptr [0xF99FFA0]
0x6ae3cf  call 0xE935700
0x6ae3fd  call qword ptr [0xF9A8C78]
#endif

static_assert(kEea6040SlotRva == 0xF99FFA0, "sub_6ae330: eea6040 thunk slot at RVA 0xF99FFA0");
static_assert(kFatalSlotRva == 0xF9A8C78, "sub_6ae330: fatal thunk slot at RVA 0xF9A8C78");

LIFT_FN(sub_6ae330, "sub_6ae330", 0x6AE330, native::sub_6ae330, nullptr);

} // namespace native
