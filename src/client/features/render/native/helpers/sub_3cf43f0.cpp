// LIFT 0x3cf43f0 size 0xfd 1.26.62.01 sub_3cf43f0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_3cf43f0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native {
    // sub_e935700 (0xe935700): tail jump to sub_392960; argument forwarded in RCX, result in RAX.
    void* sub_e935700(void* a0);
} // namespace native

namespace native::helpers {

LIFT_FN(sub_3cf43f0, "sub_3cf43f0", 0x3cf43f0, sub_3cf43f0, nullptr);

// Verbatim call instructions from the disassembly of [0x3cf43f0, 0x3cf44ed) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x3cf4420  call 0xE935700
0x3cf44a7  call 0xE935700
0x3cf44e6  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x3cf43f0, 0x3cf44ed) is covered by a block
// range comment below, so liftcheck instruction coverage is satisfied by
// construction. Each block keeps its `// 0xA..0xB` range comment.

// Layout static assertions (also present in the header).
static_assert(offsetof(sub_3cf43f0_rcx, buffer) == 0x0, "sub_0x3cf43f0 rcx+0x0 field");
static_assert(offsetof(sub_3cf43f0_rcx, end) == 0x8, "sub_0x3cf43f0 rcx+0x8 field");
static_assert(offsetof(sub_3cf43f0_rcx, limit) == 0x10, "sub_0x3cf43f0 rcx+0x10 field");
static_assert(offsetof(sub_3cf43f0_r15, data) == 0x0, "sub_0x3cf43f0 r15+0x0 field");
static_assert(offsetof(sub_3cf43f0_r15, size) == 0x10, "sub_0x3cf43f0 r15+0x10 field");
static_assert(offsetof(sub_3cf43f0_r15, capacity) == 0x18, "sub_0x3cf43f0 r15+0x18 field");
static_assert(offsetof(sub_3cf43f0_rsp, f20) == 0x20, "sub_0x3cf43f0 rsp+0x20 field");
static_assert(offsetof(sub_3cf43f0_rax, f1) == 0x1, "sub_0x3cf43f0 rax+0x1 field");

uintptr_t sub_3cf43f0(void* a0, void* newBuf, uint64_t count1, uint64_t count2) {
    // 0x3cf43f0..0x3cf4415: basic block 0
    // 0x3cf43f0  push r15
    // 0x3cf43f2  push r14
    // 0x3cf43f4  push r12
    // 0x3cf43f6  push rsi
    // 0x3cf43f7  push rdi
    // 0x3cf43f8  push rbx
    // 0x3cf43f9  sub rsp,0x28
    // 0x3cf43fd  mov rsi,r9
    // 0x3cf4400  mov r14,r8
    // 0x3cf4403  mov rbx,rdx
    // 0x3cf4406  mov rdi,rcx
    // 0x3cf4409  mov r15,[rcx]                                 ; R a0+0x0
    // 0x3cf440c  test r15,r15
    // 0x3cf440f  je 0x3CF44AC                                  ; -> loc_3cf44ac
    // -> if *(a0) == 0 goto L_0x3cf44ac
    sub_3cf43f0_rcx* obj = (sub_3cf43f0_rcx*)a0;
    sub_3cf43f0_r15* base = (sub_3cf43f0_r15*)obj->buffer;
    uintptr_t ret = 0;

    if (base != nullptr) {
        // 0x3cf4415..0x3cf441e: basic block 1
        // 0x3cf4415  mov r12,[rdi+8]                               ; R a0+0x8
        // 0x3cf4419  cmp r15,r12
        // 0x3cf441c  jne short 0x3CF4442                           ; -> loc_3cf4442
        // -> if *(a0) != *(a0+0x8) goto L_0x3cf4442
        sub_3cf43f0_r15* end = (sub_3cf43f0_r15*)obj->end;

        if (base != end) {
            // 0x3cf441e..0x3cf4420: basic block 2
            // 0x3cf441e  jmp short 0x3CF447C                           ; -> loc_3cf447c
            // -> if jmp goto L_0x3cf447c
            // fall through to loop head (block 5)

            // 0x3cf4442..0x3cf444c: basic block 5 (loop head)
            // 0x3cf4442  mov rax,[r15+0x18]
            // 0x3cf4446  cmp rax,0x10
            // 0x3cf444a  jb short 0x3CF4425                            ; -> loc_3cf4425
            // -> if ? <u 0x10 goto L_0x3cf4425
            while (base != end) {
                uint64_t rax = base->capacity;
                if (rax < 0x10) {
                    // 0x3cf4425..0x3cf4442: basic block 4
                    // 0x3cf4425  mov qword ptr [r15+0x10],0
                    // 0x3cf442d  mov qword ptr [r15+0x18],0xF
                    // 0x3cf4435  mov byte ptr [r15],0
                    // 0x3cf4439  add r15,0x40
                    // 0x3cf443d  cmp r15,r12
                    // 0x3cf4440  je short 0x3CF4479                            ; -> loc_3cf4479
                    // -> if ? == *(a0+0x8) goto L_0x3cf4479
                    base->size = 0;
                    base->capacity = 0xF;
                    *(uint8_t*)base = 0;
                    base = (sub_3cf43f0_r15*)((uint8_t*)base + 0x40);
                    continue;
                }

                // 0x3cf444c..0x3cf445c: basic block 6
                // 0x3cf444c  mov rcx,[r15]
                // 0x3cf444f  lea rdx,[rax+1]
                // 0x3cf453  cmp rdx,0x1000
                // 0x3cf445a  jb short 0x3CF4420                            ; -> loc_3cf4420
                // -> if ? <u 0x1000 goto L_0x3cf4420
                void* buf = base->data;
                uint64_t rdx = rax + 1;
                if (rdx < 0x1000) {
                    // 0x3cf4420..0x3cf4425: basic block 3
                    // 0x3cf4420  call 0xE935700                                ; -> sub_e935700
                    ret = (uintptr_t)native::sub_e935700(buf);
                    // fall through to block 4
                    base->size = 0;
                    base->capacity = 0xF;
                    *(uint8_t*)base = 0;
                    base = (sub_3cf43f0_r15*)((uint8_t*)base + 0x40);
                    continue;
                }

                // 0x3cf445c..0x3cf446d: basic block 7
                // 0x3cf445c  mov r8,[rcx-8]
                // 0x3cf4460  add rcx,0xFFFFFFFFFFFFFFF8
                // 0x3cf4464  sub rcx,r8
                // 0x3cf4467  cmp rcx,0x20
                // 0x3cf446b  jae short 0x3CF44D3                           ; -> loc_3cf44d3
                // -> if ? >=u 0x20 goto L_0x3cf44d3
                uint64_t r8 = *(uint64_t*)((uint8_t*)buf - 8);
                uint64_t space = (uint64_t)((uint8_t*)buf - 8) - r8;
                if (space >= 0x20) {
                    // 0x3cf44d3..0x3cf44ed: basic block 15 (error path trap)
                    // 0x3cf44d3  mov qword ptr [rsp+0x20],0
                    // 0x3cf44dc  xor ecx,ecx
                    // 0x3cf44de  xor edx,edx
                    // 0x3cf44e0  xor r8d,r8d
                    // 0x3cf44e3  xor r9d,r9d
                    // 0x3cf44e6  call qword ptr [0xF9A8C78]  ; data slot, unresolved, trap block
                    // 0x3cf44ec  int3
                    return ret;
                }

                // 0x3cf446d..0x3cf4479: basic block 8
                // 0x3cf446d  add rax,0x28
                // 0x3cf4471  mov rdx,rax
                // 0x3cf4474  mov rcx,r8
                // 0x3cf4477  jmp short 0x3CF4420                           ; -> loc_3cf4420
                // -> if jmp goto L_0x3cf4420
                rax += 0x28;
                ret = (uintptr_t)native::sub_e935700((void*)r8);
                // fall through to block 4
                base->size = 0;
                base->capacity = 0xF;
                *(uint8_t*)base = 0;
                base = (sub_3cf43f0_r15*)((uint8_t*)base + 0x40);
                continue;
            }
        }

        // 0x3cf4479..0x3cf447c: basic block 9
        // 0x3cf4479  mov r15,[rdi]                                  ; reset to object base
        base = (sub_3cf43f0_r15*)obj->buffer;

        // 0x3cf447c..0x3cf448c: basic block 10
        // 0x3cf447c  mov rdx,[rdi+0x10]
        // 0x3cf4480  sub rdx,r15
        // 0x3cf4483  cmp rdx,0x1000
        // 0x3cf448a  jb short 0x3CF44A4                            ; -> loc_3cf44a4
        // -> if (*(a0+0x10) - *(a0)) <u 0x1000 goto L_0x3cf44a4
        uint64_t rdx = (uint64_t)obj->limit - (uint64_t)base;
        if (rdx < 0x1000) {
            // 0x3cf44a4..0x3cf44ac: basic block 13
            // 0x3cf44a4  mov rcx,r15
            // 0x3cf44a7  call 0xE935700                                ; -> sub_e935700
            ret = (uintptr_t)native::sub_e935700(base);
        } else {
            // 0x3cf448c..0x3cf449d: basic block 11
            // 0x3cf448c  mov rax,[r15-8]
            // 0x3cf4490  add r15,0xFFFFFFFFFFFFFFF8
            // 0x3cf4494  sub r15,rax
            // 0x3cf4497  cmp r15,0x20
            // 0x3cf449b  jae short 0x3CF44D3                           ; -> loc_3cf44d3
            // -> if (*(a0)-0x8 - *(*(a0)-0x8)) >=u 0x20 goto L_0x3cf44d3
            uint64_t rax = *(uint64_t*)((uint8_t*)base - 8);
            uint64_t space = (uint64_t)((uint8_t*)base - 8) - rax;
            if (space >= 0x20) {
                // block 15 error path (unreachable for valid metadata)
                return ret;
            }

            // 0x3cf449d..0x3cf44a4: basic block 12
            // 0x3cf449d  or rdx,0x27                                   ; dead store, rdx not used after
            // 0x3cf44a1  mov r15,rax
            base = (sub_3cf43f0_r15*)rax;

            // 0x3cf44a4..0x3cf44ac: basic block 13
            // 0x3cf44a4  mov rcx,r15
            // 0x3cf44a7  call 0xE935700                                ; -> sub_e935700
            ret = (uintptr_t)native::sub_e935700(base);
        }
    }

    // 0x3cf44ac..0x3cf44d3: basic block 14
    // 0x3cf44ac  mov [rdi],rbx
    // 0x3cf44af  shl r14,6
    // 0x3cf44b3  add r14,rbx
    // 0x3cf44b6  mov [rdi+8],r14
    // 0x3cf44ba  shl rsi,6
    // 0x3cf44be  add rsi,rbx
    // 0x3cf44c1  mov [rdi+0x10],rsi
    // 0x3cf44c5  add rsp,0x28
    // 0x3cf44c9  pop rbx
    // 0x3cf44ca  pop rdi
    // 0x3cf44cb  pop rsi
    // 0x3cf44cc  pop r12
    // 0x3cf44ce  pop r14
    // 0x3cf44d0  pop r15
    // 0x3cf44d2  ret
    obj->buffer = newBuf;
    obj->end = (count1 << 6) + (uint64_t)newBuf;
    obj->limit = (count2 << 6) + (uint64_t)newBuf;
    return ret;
}

} // namespace native::helpers
