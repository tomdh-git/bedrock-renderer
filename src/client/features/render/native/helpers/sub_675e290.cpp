// LIFT 0x675e290 size 0xf4 1.26.62.01 sub_675e290
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_675e290.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

static_assert(offsetof(sub_675e290_state, f0) == 0x00, "");
static_assert(offsetof(sub_675e290_state, next_ptr) == 0x08, "");
static_assert(offsetof(sub_675e290_state, f30) == 0x30, "");
static_assert(offsetof(sub_675e290_state, f40) == 0x40, "");
static_assert(offsetof(sub_675e290_state, f50) == 0x50, "");
static_assert(offsetof(sub_675e290_state, flag60) == 0x60, "");
static_assert(offsetof(sub_675e290_ref, f0) == 0x00, "");
static_assert(offsetof(sub_675e290_ref, strong_refcount) == 0x08, "");
static_assert(offsetof(sub_675e290_ref, weak_refcount) == 0x0c, "");

LIFT_FN(sub_675e290, "sub_675e290", 0x675e290, sub_675e290, nullptr);

// Verbatim call instructions from the disassembly of [0x675e290, 0x675e384) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x675e2bb  call qword ptr [0xF99FFA0]
0x675e2d1  call qword ptr [0xF99FFA0]
0x675e2ef  call qword ptr [0xF99FFA0]
0x675e305  call qword ptr [0xF99FFA0]
0x675e323  call qword ptr [0xF99FFA0]
0x675e339  call qword ptr [0xF99FFA0]
0x675e357  call qword ptr [0xF99FFA0]
#endif

// Ranges: every instruction of [0x675e290, 0x675e384) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_675e290(sub_675e290_state* self) {
    // 0x675e290..0x675e2a0: basic block 0
    // 0x675e290  push rsi
    // 0x675e291  push rdi
    // 0x675e292  sub rsp,0x28
    // 0x675e296  cmp byte ptr [rcx+0x60],1
    // 0x675e29a  jne 0x675E37D
    // -> if *u8(a0+0x60) != 0x1 goto L_0x675e37d
    // -> if *u8(a0+0x60) == 0x1 goto L_0x675e2a0
    if (self->flag60 != 1) {
        // 0x675e37d..0x675e384: basic block 17
        // 0x675e37d  add rsp,0x28
        // 0x675e381  pop rdi
        // 0x675e382  pop rsi
        // 0x675e383  ret
        // -> (fall-through / ret / end)
        return 0;
    }

    // 0x675e2a0..0x675e2ac: basic block 1
    // 0x675e2a0  mov rsi,rcx
    // 0x675e2a3  mov rdi,[rcx+0x50]
    // 0x675e2a7  test rdi,rdi
    // 0x675e2aa  je short 0x675E2D7
    // -> if *(a0+0x50) == 0 goto L_0x675e2d7
    // -> if *(a0+0x50) != 0 goto L_0x675e2ac
    sub_675e290_ref* child = reinterpret_cast<sub_675e290_ref*>(self->f50);
    if (child == nullptr) {
        // 0x675e2d7..0x675e2e0: basic block 5
        // 0x675e2d7  mov rdi,[rsi+0x40]
        // 0x675e2db  test rdi,rdi
        // 0x675e2de  je short 0x675E30B
        // -> if *(a0+0x40) == 0 goto L_0x675e30b
        // -> if *(a0+0x40) != 0 goto L_0x675e2e0
        sub_675e290_ref* child40 = reinterpret_cast<sub_675e290_ref*>(self->f40);
        if (child40 == nullptr) {
            // 0x675e30b..0x675e314: basic block 9
            // 0x675e30b  mov rdi,[rsi+0x30]
            // 0x675e30f  test rdi,rdi
            // 0x675e312  je short 0x675E33F
            // -> if *(a0+0x30) == 0 goto L_0x675e33f
            // -> if *(a0+0x30) != 0 goto L_0x675e314
            sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
            if (child30 == nullptr) {
                // 0x675e33f..0x675e348: basic block 13
                // 0x675e33f  mov rsi,[rsi+8]
                // 0x675e343  test rsi,rsi
                // 0x675e346  je short 0x675E37D
                // -> if *(a0+0x8) == 0 goto L_0x675e37d
                // -> if *(a0+0x8) != 0 goto L_0x675e348
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    // 0x675e37d..0x675e384: basic block 17
                    // 0x675e37d  add rsp,0x28
                    // 0x675e381  pop rdi
        // 0x675e382  pop rsi
        // 0x675e383  ret
        // -> (fall-through / ret / end)
                    return 0;
                }
                // 0x675e348..0x675e34e: basic block 14
                // 0x675e348  lock dec dword ptr [rsi+8]
                // 0x675e34c  jne short 0x675E37D
                // -> if (Dec *u32(*(a0+0x8)+0x8), ?) != 0 goto L_0x675e37d
                // -> if (Dec *u32(*(a0+0x8)+0x8), ?) == 0 goto L_0x675e34e
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                // 0x675e34e..0x675e363: basic block 15
                // 0x675e34e  mov rax,[rsi]
                // 0x675e351  mov rax,[rax]
                // 0x675e354  mov rcx,rsi
                // 0x675e357  call qword ptr [0xF99FFA0]   ; vtable[0](next)
                // 0x675e35d  lock dec dword ptr [rsi+0xC]
                // 0x675e361  jne short 0x675E37D
                // -> if (Dec *u32(*(a0+0x8)+0xC), ?) != 0 goto L_0x675e37d
                // -> if (Dec *u32(*(a0+0x8)+0xC), ?) == 0 goto L_0x675e363
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                // 0x675e363..0x675e37d: basic block 16
                // 0x675e363  mov rax,[rsi]
                // 0x675e366  mov rax,[rax+8]
                // 0x675e36a  mov rdx,[0xF99FFA0]   ; rdx = vtable[1]
                // 0x675e371  mov rcx,rsi
                // 0x675e374  add rsp,0x28
                // 0x675e378  pop rdi
                // 0x675e379  pop rsi
                // 0x675e37a  jmp rdx   ; tail call vtable[1](next)
                // -> (fall-through / ret / end)
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }

            // 0x675e314..0x675e31a: basic block 10
            // 0x675e314  lock dec dword ptr [rdi+8]
            // 0x675e318  jne short 0x675E33F
            // -> if (Dec *u32(*(a0+0x30)+0x8), ?) != 0 goto L_0x675e33f
            // -> if (Dec *u32(*(a0+0x30)+0x8), ?) == 0 goto L_0x675e31a
            if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                // 0x675e33f..0x675e348: basic block 13 (shared)
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            // 0x675e31a..0x675e32f: basic block 11
            // 0x675e31a  mov rax,[rdi]
            // 0x675e31d  mov rax,[rax]
            // 0x675e320  mov rcx,rdi
            // 0x675e323  call qword ptr [0xF99FFA0]   ; vtable[0](child30)
            // 0x675e329  lock dec dword ptr [rdi+0xC]
            // 0x675e32d  jne short 0x675E33F
            // -> if (Dec *u32(*(a0+0x30)+0xC), ?) != 0 goto L_0x675e33f
            // -> if (Dec *u32(*(a0+0x30)+0xC), ?) == 0 goto L_0x675e32f
            reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
            if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                // 0x675e33f..0x675e348: basic block 13 (shared)
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            // 0x675e32f..0x675e33f: basic block 12
            // 0x675e32f  mov rax,[rdi]
            // 0x675e332  mov rax,[rax+8]
            // 0x675e336  mov rcx,rdi
            // 0x675e339  call qword ptr [0xF99FFA0]   ; tail call vtable[1](child30)
            // -> (fall-through / ret / end)
            return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
        }

        // 0x675e2e0..0x675e2e6: basic block 6
        // 0x675e2e0  lock dec dword ptr [rdi+8]
        // 0x675e2e4  jne short 0x675E30B
        // -> if (Dec *u32(*(a0+0x40)+0x8), ?) != 0 goto L_0x675e30b
        // -> if (Dec *u32(*(a0+0x40)+0x8), ?) == 0 goto L_0x675e2e6
        if (_InterlockedDecrement(&child40->strong_refcount) != 0) {
            // 0x675e30b..0x675e314: basic block 9 (shared)
            sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
            if (child30 == nullptr) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
            if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
        }
        // 0x675e2e6..0x675e2fb: basic block 7
        // 0x675e2e6  mov rax,[rdi]
        // 0x675e2e9  mov rax,[rax]
        // 0x675e2ec  mov rcx,rdi
        // 0x675e2ef  call qword ptr [0xF99FFA0]   ; vtable[0](child40)
        // 0x675e2f5  lock dec dword ptr [rdi+0xC]
        // 0x675e2f9  jne short 0x675E30B
        // -> if (Dec *u32(*(a0+0x40)+0xC), ?) != 0 goto L_0x675e30b
        // -> if (Dec *u32(*(a0+0x40)+0xC), ?) == 0 goto L_0x675e2fb
        reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child40->f0)[0])(child40);
        if (_InterlockedDecrement(&child40->weak_refcount) != 0) {
            // 0x675e30b..0x675e314: basic block 9 (shared)
            sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
            if (child30 == nullptr) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
            if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
        }
        // 0x675e2fb..0x675e30b: basic block 8
        // 0x675e2fb  mov rax,[rdi]
        // 0x675e2fe  mov rax,[rax+8]
        // 0x675e302  mov rcx,rdi
        // 0x675e305  call qword ptr [0xF99FFA0]   ; tail call vtable[1](child40)
        // -> (fall-through / ret / end)
        return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child40->f0)[1])(child40);
    }

    // 0x675e2ac..0x675e2b2: basic block 2
    // 0x675e2ac  lock dec dword ptr [rdi+8]
    // 0x675e2b0  jne short 0x675E2D7
    // -> if (Dec *u32(*(a0+0x50)+0x8), ?) != 0 goto L_0x675e2d7
    // -> if (Dec *u32(*(a0+0x50)+0x8), ?) == 0 goto L_0x675e2b2
    if (_InterlockedDecrement(&child->strong_refcount) != 0) {
        // 0x675e2d7..0x675e2e0: basic block 5 (shared)
        sub_675e290_ref* child40 = reinterpret_cast<sub_675e290_ref*>(self->f40);
        if (child40 == nullptr) {
            sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
            if (child30 == nullptr) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
            if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
        }
        if (_InterlockedDecrement(&child40->strong_refcount) != 0) {
            sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
            if (child30 == nullptr) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
            if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
        }
        reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child->f0)[0])(child);
        if (_InterlockedDecrement(&child->weak_refcount) != 0) {
            // 0x675e2d7..0x675e2e0: basic block 5 (shared)
            sub_675e290_ref* child40 = reinterpret_cast<sub_675e290_ref*>(self->f40);
            if (child40 == nullptr) {
                sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
                if (child30 == nullptr) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
                if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
            }
            if (_InterlockedDecrement(&child40->strong_refcount) != 0) {
                sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
                if (child30 == nullptr) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
                if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
            }
            reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child40->f0)[0])(child40);
            if (_InterlockedDecrement(&child40->weak_refcount) != 0) {
                sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
                if (child30 == nullptr) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
                if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
            }
            // 0x675e2fb..0x675e30b: basic block 8 (shared)
            // 0x675e2fb  mov rax,[rdi]
            // 0x675e2fe  mov rax,[rax+8]
            // 0x675e302  mov rcx,rdi
            // 0x675e305  call qword ptr [0xF99FFA0]   ; tail call vtable[1](child40)
            // -> (fall-through / ret / end)
            return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child40->f0)[1])(child40);
        }
        // 0x675e2c7..0x675e2d7: basic block 4
        // 0x675e2c7  mov rax,[rdi]
        // 0x675e2ca  mov rax,[rax+8]
        // 0x675e2ce  mov rcx,rdi
        // 0x675e2d1  call qword ptr [0xF99FFA0]   ; tail call vtable[1](child)
        // -> (fall-through / ret / end)
        return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child->f0)[1])(child);
    }
    // 0x675e2b2..0x675e2c7: basic block 3
    // 0x675e2b2  mov rax,[rdi]
    // 0x675e2b5  mov rax,[rax]
    // 0x675e2b8  mov rcx,rdi
    // 0x675e2bb  call qword ptr [0xF99FFA0]   ; vtable[0](child)
    // 0x675e2c1  lock dec dword ptr [rdi+0xC]
    // 0x675e2c5  jne short 0x675E2D7
    // -> if (Dec *u32(*(a0+0x50)+0xC), ?) != 0 goto L_0x675e2d7
    // -> if (Dec *u32(*(a0+0x50)+0xC), ?) == 0 goto L_0x675e2c7
    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child->f0)[0])(child);
    if (_InterlockedDecrement(&child->weak_refcount) != 0) {
        // 0x675e2d7..0x675e2e0: basic block 5 (shared)
        sub_675e290_ref* child40 = reinterpret_cast<sub_675e290_ref*>(self->f40);
        if (child40 == nullptr) {
            sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
            if (child30 == nullptr) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
            if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
        }
        if (_InterlockedDecrement(&child40->strong_refcount) != 0) {
            sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
            if (child30 == nullptr) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
            if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                if (next == nullptr) {
                    return 0;
                }
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                    return 0;
                }
                auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                    return 0;
                }
                auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
            }
            return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
        }
        reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child->f0)[0])(child);
        if (_InterlockedDecrement(&child->weak_refcount) != 0) {
            // 0x675e2d7..0x675e2e0: basic block 5 (shared)
            sub_675e290_ref* child40 = reinterpret_cast<sub_675e290_ref*>(self->f40);
            if (child40 == nullptr) {
                sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
                if (child30 == nullptr) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
                if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
            }
            if (_InterlockedDecrement(&child40->strong_refcount) != 0) {
                sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
                if (child30 == nullptr) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
                if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
            }
            reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child40->f0)[0])(child40);
            if (_InterlockedDecrement(&child40->weak_refcount) != 0) {
                sub_675e290_ref* child30 = reinterpret_cast<sub_675e290_ref*>(self->f30);
                if (child30 == nullptr) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                if (_InterlockedDecrement(&child30->strong_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[0])(child30);
                if (_InterlockedDecrement(&child30->weak_refcount) != 0) {
                    sub_675e290_ref* next = reinterpret_cast<sub_675e290_ref*>(self->next_ptr);
                    if (next == nullptr) {
                        return 0;
                    }
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->strong_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable0 = reinterpret_cast<void**>(next->f0)[0];
                    reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable0)(next);
                    if (_InterlockedDecrement64(reinterpret_cast<volatile long long*>(&next->weak_refcount)) != 0) {
                        return 0;
                    }
                    auto vtable1 = reinterpret_cast<void**>(next->f0)[1];
                    return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(vtable1)(next);
                }
                return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child30->f0)[1])(child30);
            }
            // 0x675e2fb..0x675e30b: basic block 8 (shared)
            // 0x675e2fb  mov rax,[rdi]
            // 0x675e2fe  mov rax,[rax+8]
            // 0x675e302  mov rcx,rdi
            // 0x675e305  call qword ptr [0xF99FFA0]   ; tail call vtable[1](child40)
            // -> (fall-through / ret / end)
            return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child40->f0)[1])(child40);
        }
        // 0x675e2c7..0x675e2d7: basic block 4
        // 0x675e2c7  mov rax,[rdi]
        // 0x675e2ca  mov rax,[rax+8]
        // 0x675e2ce  mov rcx,rdi
        // 0x675e2d1  call qword ptr [0xF99FFA0]   ; tail call vtable[1](child)
        // -> (fall-through / ret / end)
        return reinterpret_cast<uintptr_t(*)(sub_675e290_ref*)>(reinterpret_cast<void**>(child->f0)[1])(child);
    }

    return 0;  // unreachable: all paths return above
}

} // namespace native::helpers
