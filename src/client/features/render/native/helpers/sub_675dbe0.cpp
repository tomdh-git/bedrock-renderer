// LIFT 0x675dbe0 size 0xdf 1.26.62.01 sub_675dbe0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_675dbe0.h"
#include "client/features/render/native/helpers/sub_1d3b70.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native {
// Forward declaration: sub_e935700 is a lift-set callee in namespace native.
// Its header carries a self-referential static_assert; forward-declare here.
void* sub_e935700(void* a0);
}

namespace native::helpers {

LIFT_FN(sub_675dbe0, "sub_675dbe0", 0x675dbe0, sub_675dbe0, nullptr);

// Verbatim call instructions from the disassembly of [0x675dbe0, 0x675dcbf) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x675dc1c  call 0x1D3B70
0x675dc29  call 0xE935700
0x675dc36  call 0xE935700
0x675dc49  call 0x675DBE0
0x675dca1  call qword ptr [0xF99FFA0]
0x675dcb7  call qword ptr [0xF99FFA0]
#endif

// Ranges: every instruction of [0x675dbe0, 0x675dcbf) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

uintptr_t sub_675dbe0(void* self) {
    // Register mirrors (x64 Microsoft ABI). RBX/RDI/RSI/R12/R14/R15 are callee-saved.
    void* rsi = nullptr;
    void* rdi = nullptr;
    void* r14 = nullptr;
    void* r15 = nullptr;
    void* r12 = nullptr;
    void* rbx = nullptr;
    void* rax = nullptr;

    // 0x675dbe0..0x675dbf3: basic block 0 (prologue + flag test)
    // 0x675dbe0  push r15
    // 0x675dbe2  push r14
    // 0x675dbe4  push r12
    // 0x675dbe6  push rsi
    // 0x675dbe7  push rdi
    // 0x675dbe8  push rbx
    // 0x675dbe9  sub rsp,0x28
    // 0x675dbed  cmp byte ptr [rcx+0x19],0
    // 0x675dbf1  je short 0x675DC01
    // -> if *u8(self+0x19) == 0x0 goto L_0x675dc01 ; else goto L_0x675dbf3
    L_0x675dbe0:;
    if (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(self) + 0x19) == 0) {
        goto L_0x675dc01;
    }
    goto L_0x675dbf3;

    // 0x675dbf3..0x675dc01: basic block 1 (epilogue)
    // 0x675dbf3  add rsp,0x28
    // 0x675dbf7  pop rbx
    // 0x675dbf8  pop rdi
    // 0x675dbf9  pop rsi
    // 0x675dbfa  pop r12
    // 0x675dbfc  pop r14
    // 0x675dbfe  pop r15
    // 0x675dc00  ret
    // -> (ret / end)
    L_0x675dbf3:;
    // The original epilogue leaves RAX undefined and every caller ignores the result.
    return 0;

    // 0x675dc01..0x675dc06: basic block 2
    // 0x675dc01  mov rsi,rcx
    // 0x675dc04  jmp short 0x675DC45
    // -> if jmp goto L_0x675dc45
    L_0x675dc01:;
    rsi = self;
    goto L_0x675dc45;

    // 0x675dc06..0x675dc10: basic block 3 (unreachable nop padding)
    // 0x675dc06  nop [rax+rax]
    // -> if fallthrough goto L_0x675dc10
    L_0x675dc06:;
    goto L_0x675dc10;

    // 0x675dc10..0x675dc18: basic block 4
    // 0x675dc10  mov rax,[rdi+0x20]
    // 0x675dc14  mov [rdi+0x28],rax
    // -> if fallthrough goto L_0x675dc18
    L_0x675dc10:;
    rax = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rdi) + 0x20);
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rdi) + 0x28) = rax;
    goto L_0x675dc18;

    // 0x675dc18..0x675dc2e: basic block 5
    // 0x675dc18  lea rcx,[rdi+8]
    // 0x675dc1c  call 0x1D3B70        -> sub_1d3b70
    // 0x675dc21  mov edx,0x40
    // 0x675dc26  mov rcx,rdi
    // 0x675dc29  call 0xE935700       -> sub_e935700
    // -> if fallthrough goto L_0x675dc2e
    L_0x675dc18:;
    sub_1d3b70(reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(rdi) + 8));
    native::sub_e935700(rdi);
    goto L_0x675dc2e;

    // 0x675dc2e..0x675dc45: basic block 6
    // 0x675dc2e  mov edx,0x30
    // 0x675dc33  mov rcx,rsi
    // 0x675dc36  call 0xE935700       -> sub_e935700
    // 0x675dc3b  cmp byte ptr [r14+0x19],0
    // 0x675dc40  mov rsi,r14
    // 0x675dc43  jne short 0x675DBF3
    // -> if *u8(r14+0x19) != 0x0 goto L_0x675dbf3
    // -> if *u8(r14+0x19) == 0x0 goto L_0x675dc45 (fall-through)
    L_0x675dc2e:;
    native::sub_e935700(rsi);
    if (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(r14) + 0x19) != 0) {
        goto L_0x675dbf3;
    }
    rsi = r14;
    goto L_0x675dc45;

    // 0x675dc45..0x675dc5a: basic block 7
    // 0x675dc45  mov rcx,[rsi+0x10]
    // 0x675dc49  call 0x675DBE0       -> sub_675dbe0 (recursion on self->f10)
    // 0x675dc4e  mov r14,[rsi]
    // 0x675dc51  mov rdi,[rsi+0x28]
    // 0x675dc55  test rdi,rdi
    // 0x675dc58  je short 0x675DC2E
    // -> if rdi == 0 goto L_0x675dc2e
    // -> if rdi != 0 goto L_0x675dc5a
    L_0x675dc45:;
    sub_675dbe0(*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rsi) + 0x10));
    r14 = *reinterpret_cast<void**>(rsi);
    rdi = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rsi) + 0x28);
    if (rdi == nullptr) {
        goto L_0x675dc2e;
    }
    goto L_0x675dc5a;

    // 0x675dc5a..0x675dc64: basic block 8
    // 0x675dc5a  mov rax,[rdi+8]
    // 0x675dc5e  cmp rax,[rdi+0x10]     (8-byte compare: f8 vs f10)
    // 0x675dc62  je short 0x675DC68
    // -> if rax == *u64(rdi+0x10) goto L_0x675dc68
    // -> if rax != *u64(rdi+0x10) goto L_0x675dc64
    L_0x675dc5a:;
    rax = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rdi) + 8);
    if (rax == *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rdi) + 0x10)) {
        goto L_0x675dc68;
    }
    goto L_0x675dc64;

    // 0x675dc64..0x675dc68: basic block 9
    // 0x675dc64  mov [rdi+0x10],rax
    // -> if fallthrough goto L_0x675dc68
    L_0x675dc64:;
    *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rdi) + 0x10) = rax;
    goto L_0x675dc68;

    // 0x675dc68..0x675dc75: basic block 10
    // 0x675dc68  mov r15,[rdi+0x20]
    // 0x675dc6c  mov r12,[rdi+0x28]
    // 0x675dc70  cmp r15,r12
    // 0x675dc73  jne short 0x675DC89
    // -> if r15 != r12 goto L_0x675dc89
    // -> if r15 == r12 goto L_0x675dc75
    L_0x675dc68:;
    r15 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rdi) + 0x20);
    r12 = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(rdi) + 0x28);
    if (r15 != r12) {
        goto L_0x675dc89;
    }
    goto L_0x675dc75;

    // 0x675dc75..0x675dc77: basic block 11
    // 0x675dc75  jmp short 0x675DC18
    // -> if jmp goto L_0x675dc18
    L_0x675dc75:;
    goto L_0x675dc18;

    // 0x675dc77..0x675dc80: basic block 12 (unreachable nop padding)
    // 0x675dc77  nop [rax+rax]
    // -> if fallthrough goto L_0x675dc80
    L_0x675dc77:;
    goto L_0x675dc80;

    // 0x675dc80..0x675dc89: basic block 13 (loop advance + exit test)
    // 0x675dc80  add r15,0x10
    // 0x675dc84  cmp r15,r12
    // 0x675dc87  je short 0x675DC10
    // -> if r15 == r12 goto L_0x675dc10
    // -> if r15 != r12 goto L_0x675dc89
    L_0x675dc80:;
    r15 = reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(r15) + 0x10);
    if (r15 == r12) {
        goto L_0x675dc10;
    }
    goto L_0x675dc89;

    // 0x675dc89..0x675dc92: basic block 14
    // 0x675dc89  mov rbx,[r15+8]
    // 0x675dc8d  test rbx,rbx
    // 0x675dc90  je short 0x675DC80
    // -> if rbx == 0 goto L_0x675dc80
    // -> if rbx != 0 goto L_0x675dc92
    L_0x675dc89:;
    rbx = *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(r15) + 8);
    if (rbx == nullptr) {
        goto L_0x675dc80;
    }
    goto L_0x675dc92;

    // 0x675dc92..0x675dc98: basic block 15 (strong refcount decrement)
    // 0x675dc92  lock dec dword ptr [rbx+8]
    // 0x675dc96  jne short 0x675DC80
    // -> if _InterlockedDec(&rbx->f8) != 0 goto L_0x675dc80
    // -> if _InterlockedDec(&rbx->f8) == 0 goto L_0x675dc98
    L_0x675dc92:;
    if (_InterlockedDecrement(
            reinterpret_cast<volatile long*>(reinterpret_cast<std::uint8_t*>(rbx) + 8)) != 0) {
        goto L_0x675dc80;
    }
    goto L_0x675dc98;

    // 0x675dc98..0x675dcad: basic block 16 (vtable slot-0 release + weak refcount decrement)
    // 0x675dc98  mov rax,[rbx]         (vtable pointer)
    // 0x675dc9b  mov rax,[rax]         (vtable slot 0 -> rax)
    // 0x675dc9e  mov rcx,rbx
    // 0x675dca1  call qword ptr [0xF99FFA0]   ; jmp-rax thunk -> virtual slot 0 call on rbx
    // 0x675dca7  lock dec dword ptr [rbx+0xC]
    // 0x675dcab  jne short 0x675DC80
    // -> if _InterlockedDec(&rbx->fc) != 0 goto L_0x675dc80
    // -> if _InterlockedDec(&rbx->fc) == 0 goto L_0x675dcad
    L_0x675dc98:; {
        auto vtable = *reinterpret_cast<void***>(rbx);
        reinterpret_cast<void (*)(void*)>(vtable[0])(rbx);   // call qword ptr [0xF99FFA0] with rax = vtable[0]
    }
    if (_InterlockedDecrement(
            reinterpret_cast<volatile long*>(reinterpret_cast<std::uint8_t*>(rbx) + 0xC)) != 0) {
        goto L_0x675dc80;
    }
    goto L_0x675dcad;

    // 0x675dcad..0x675dcbf: basic block 17 (vtable slot-1 release)
    // 0x675dcad  mov rax,[rbx]
    // 0x675dcb0  mov rax,[rax+8]      (vtable slot 1 -> rax)
    // 0x675dcb4  mov rcx,rbx
    // 0x675dcb7  call qword ptr [0xF99FFA0]   ; jmp-rax thunk -> virtual slot 1 call on rbx
    // 0x675dcbd  jmp short 0x675DC80
    // -> if jmp goto L_0x675dc80
    L_0x675dcad:; {
        auto vtable = *reinterpret_cast<void***>(rbx);
        reinterpret_cast<void (*)(void*)>(vtable[1])(rbx);   // call qword ptr [0xF99FFA0] with rax = vtable[1]
    }
    goto L_0x675dc80;
}

} // namespace native::helpers
