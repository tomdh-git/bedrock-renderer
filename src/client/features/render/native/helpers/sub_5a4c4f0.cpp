// LIFT 0x5a4c4f0 size 0x108 1.26.62.01 sub_5a4c4f0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_5a4c4f0.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

LIFT_FN(sub_5a4c4f0, "sub_5a4c4f0", 0x5a4c4f0, sub_5a4c4f0, nullptr);

// Verbatim call instructions from the disassembly of [0x5a4c4f0, 0x5a4c5f8) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x5a4c539  call qword ptr [0xF99FFA0]
0x5a4c552  call qword ptr [0xF99FFA0]
0x5a4c57f  call qword ptr [0xF99FFA0]
0x5a4c5cc  call qword ptr [0xF99FFA0]
0x5a4c5e3  call qword ptr [0xF99FFA0]
#endif

// Ranges: every instruction of [0x5a4c4f0, 0x5a4c5f8) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

Slot* sub_5a4c4f0(Slot* a0, Slot* a1) {
    // 0x5a4c4f0..0x5a4c561: basic block 0 (prologue, a0 init, two global calls, compare)
    // 0x5a4c4f0  push rbp
    // 0x5a4c4f1  push r14
    // 0x5a4c4f3  push rsi
    // 0x5a4c4f4  push rdi
    // 0x5a4c4f5  push rbx
    // 0x5a4c4f6  sub rsp,0x30
    // 0x5a4c4fa  lea rbp,[rsp+0x30]
    // 0x5a4c4ff  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
    // 0x5a4c507  mov rdi,rdx                ; rdi = a1
    // 0x5a4c50a  mov rsi,rcx                ; rsi = a0
    // 0x5a4c50d  lea rax,[0x3C7B10]         ; vtable for Slot initialization
    // 0x5a4c514  mov [rcx],rax              ; a0->vtable = 0x3C7B10
    // 0x5a4c517  xorps xmm0,xmm0
    // 0x5a4c51a  movups [rcx+8],xmm0        ; zero a0->object, a0->field10 (16 bytes at +0x8)
    // 0x5a4c51e  movups [rcx+0x17],xmm0     ; zero a0->field10 (last 8), data18 (16 bytes at +0x17)
    // 0x5a4c522  mov dword ptr [rcx+0x28],1 ; a0->field28 = 1
    // 0x5a4c529  mov rcx,[0x1233E1B0]       ; rcx = global manager pointer
    // 0x5a4c530  mov rax,[rcx]              ; rax = global->vtable
    // 0x5a4c533  mov rax,[rax+0x10]         ; rax = global->vtable[2]
    // 0x5a4c537  mov dl,0x53                ; arg = 0x53
    // 0x5a4c539  call qword ptr [0xF99FFA0] ; sub_eea6040 thunk -> global->vtable[2](global, 0x53)
    // 0x5a4c53f  nop
    // 0x5a4c540  mov bl,al                  ; save low byte of return
    // 0x5a4c542  mov rcx,[0x1233E1B0]       ; rcx = global manager pointer
    // 0x5a4c549  mov rax,[rcx]              ; rax = global->vtable
    // 0x5a4c54c  mov rax,[rax+0x10]         ; rax = global->vtable[2]
    // 0x5a4c550  mov dl,0x53                ; arg = 0x53
    // 0x5a4c552  call qword ptr [0xF99FFA0] ; sub_eea6040 thunk -> global->vtable[2](global, 0x53)
    // 0x5a4c558  nop
    // 0x5a4c559  mov r14d,eax               ; save full return
    // 0x5a4c55c  cmp rdi,rsi                ; compare a1 vs a0
    // 0x5a4c55f  je short 0x5A4C5BB         ; -> if a1 == a0 goto L_0x5a4c5bb
    // -> if a1 == a0 goto L_0x5a4c5bb
    // -> if a1 != a0 goto L_0x5a4c561
    L_0x5a4c4f0:;

    // Initialize a0 with vtable 0x3C7B10, zeroed fields, field28 = 1
    a0->vtable = reinterpret_cast<void**>(0x3C7B10);
    a0->object = nullptr;
    a0->field10 = nullptr;
    a0->data18[0] = 0;
    a0->data18[1] = 0;
    a0->field28 = 1;

    // Variables that persist across blocks (mirroring RBX, R14 registers)
    std::uint8_t bl = 0;
    std::uint32_t r14d = 0;
    void* old_object = nullptr;

    // First global call: global->vtable[2](global, 0x53)
    GlobalManager* global = get_global_manager();
    GlobalVTable2Fn vtable2 = reinterpret_cast<GlobalVTable2Fn>(global->vtable[2]);
    std::uint32_t r1 = vtable2(global, 0x53);
    bl = static_cast<std::uint8_t>(r1);  // mov bl, al

    // Second global call: same
    r14d = vtable2(global, 0x53);        // mov r14d, eax

    if (a1 == a0) {
        goto L_0x5a4c5bb;
    }

    // 0x5a4c561..0x5a4c57c: basic block 1 (a0 != a1, swap object pointers)
    // 0x5a4c561  lea rax,[rsi+8]          ; rax = &a0->object
    // 0x5a4c565  mov rdx,[rdi+8]          ; rdx = a1->object
    // 0x5a4c569  mov qword ptr [rdi+8],0  ; a1->object = nullptr
    // 0x5a4c571  mov rcx,[rax]            ; rcx = a0->object (old)
    // 0x5a4c574  mov [rax],rdx            ; a0->object = a1->object
    // 0x5a4c577  test rcx,rcx
    // 0x5a4c57a  je short 0x5A4C586       ; -> if old object == 0 goto L_0x5a4c586
    // -> if a0->object (old) == 0 goto L_0x5a4c586
    // -> if a0->object (old) != 0 goto L_0x5a4c57c
    L_0x5a4c561:;
    {
        old_object = a0->object;
        a0->object = a1->object;
        a1->object = nullptr;

        if (old_object == nullptr) {
            goto L_0x5a4c586;
        }
    }

    // 0x5a4c57c..0x5a4c586: basic block 2 (release old object via vtable[0])
    // 0x5a4c57c  mov rax,[rsi]            ; rax = a0->vtable
    // 0x5a4c57f  call qword ptr [0xF99FFA0] ; sub_eea6040 thunk -> a0->vtable[0](old_object)
    // 0x5a4c585  nop
    // -> fallthrough goto L_0x5a4c586
    L_0x5a4c57c:;
    {
        // The thunk is called with RAX = a0->vtable[0], RCX = old_object.
        // Model as direct virtual call: a0->vtable[0](old_object)
        RefCountedVTable0Fn vtable0 = reinterpret_cast<RefCountedVTable0Fn>(a0->vtable[0]);
        vtable0(old_object);
    }

    // 0x5a4c586..0x5a4c5bb: basic block 3 (copy remaining fields from a1 to a0, zero a1)
    // 0x5a4c586  lea rax,[rsi+0x18]       ; rax = &a0->data18
    // 0x5a4c58a  mov rcx,[rdi]            ; rcx = a1->vtable
    // 0x5a4c58d  mov [rsi],rcx            ; a0->vtable = a1->vtable
    // 0x5a4c590  mov rcx,[rdi+0x10]       ; rcx = a1->field10
    // 0x5a4c594  mov [rsi+0x10],rcx       ; a0->field10 = a1->field10
    // 0x5a4c598  mov qword ptr [rdi+0x10],0 ; a1->field10 = 0
    // 0x5a4c5a0  mov ecx,[rdi+0x28]       ; ecx = a1->field28
    // 0x5a4c5a3  mov [rax+0x10],ecx       ; a0->field28 = a1->field28 (rax = &a0->data18, +0x10 = +0x28)
    // 0x5a4c5a6  movups xmm0,[rdi+0x18]   ; xmm0 = a1->data18 (16 bytes)
    // 0x5a4c5aa  movups [rax],xmm0        ; a0->data18 = a1->data18
    // 0x5a4c5ad  xorps xmm0,xmm0
    // 0x5a4c5b0  movups [rdi+0x18],xmm0   ; a1->data18 = 0
    // 0x5a4c5b4  mov dword ptr [rdi+0x28],1 ; a1->field28 = 1
    // -> fallthrough goto L_0x5a4c5bb
    L_0x5a4c586:;
    {
        a0->vtable = a1->vtable;
        a0->field10 = a1->field10;
        a1->field10 = nullptr;
        a0->field28 = a1->field28;
        a0->data18[0] = a1->data18[0];
        a0->data18[1] = a1->data18[1];
        a1->data18[0] = 0;
        a1->data18[1] = 0;
        a1->field28 = 1;
    }

    // 0x5a4c5bb..0x5a4c5f8: basic block 4 (epilogue, two global calls with saved returns, return a0)
    // 0x5a4c5bb  mov rcx,[0x1233E1B0]       ; rcx = global manager pointer
    // 0x5a4c5c2  mov rax,[rcx]              ; rax = global->vtable
    // 0x5a4c5c5  mov rax,[rax+0x10]         ; rax = global->vtable[2]
    // 0x5a4c5c9  mov edx,r14d               ; edx = r14d (second call return)
    // 0x5a4c5cc  call qword ptr [0xF99FFA0] ; sub_eea6040 thunk -> global->vtable[2](global, r14d)
    // 0x5a4c5d2  nop
    // 0x5a4c5d3  mov rcx,[0x1233E1B0]       ; rcx = global manager pointer
    // 0x5a4c5da  mov rax,[rcx]              ; rax = global->vtable
    // 0x5a4c5dd  mov rax,[rax+0x10]         ; rax = global->vtable[2]
    // 0x5a4c5e1  mov edx,ebx                ; edx = ebx (first call return in bl, zero-extended)
    // 0x5a4c5e3  call qword ptr [0xF99FFA0] ; sub_eea6040 thunk -> global->vtable[2](global, ebx)
    // 0x5a4c5e9  nop
    // 0x5a4c5ea  mov rax,rsi                ; return a0
    // 0x5a4c5ed  add rsp,0x30
    // 0x5a4c5f1  pop rbx
    // 0x5a4c5f2  pop rdi
    // 0x5a4c5f3  pop rsi
    // 0x5a4c5f4  pop r14
    // 0x5a4c5f5  pop rbp
    // 0x5a4c5f6  ret
    // -> (fall-through / ret / end)
    L_0x5a4c5bb:;
    {
        GlobalManager* global = get_global_manager();
        GlobalVTable2Fn vtable2 = reinterpret_cast<GlobalVTable2Fn>(global->vtable[2]);

        // Third global call: arg = r14d (from second call)
        vtable2(global, r14d);

        // Fourth global call: arg = ebx (bl from first call, zero-extended to 32-bit in edx)
        // Original: mov edx,ebx where ebx has bl = first_return_low_byte, upper bits from caller's rbx.
        // We pass the low byte zero-extended (semantically equivalent for the callee which only used dl=0x53 before).
        std::uint32_t ebx_arg = static_cast<std::uint32_t>(bl);
        vtable2(global, ebx_arg);

        return a0;
    }
}

} // namespace native::helpers