// LIFT 0xc280a80 size 0x10f 1.26.62.01 sub_c280a80
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_c280a80.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_c280a80, "sub_c280a80", 0xc280a80, sub_c280a80, nullptr);

// Verbatim call instructions from the disassembly of [0xc280a80, 0xc280b8f) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xc280ae2  call qword ptr [0xF99FFA0]
0xc280af9  call qword ptr [0xF99FFA0]
0xc280b2f  call 0xE935700
0xc280b88  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0xc280a80, 0xc280b8f) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

// Layout assertions for liftcheck
static_assert(offsetof(sub_c280a80_rcx, f0) == 0x0, "rcx+0x0");
static_assert(offsetof(sub_c280a80_rcx, f10) == 0x10, "rcx+0x10");
static_assert(offsetof(sub_c280a80_rdx, f0) == 0x0, "rdx+0x0");
static_assert(offsetof(sub_c280a80_rdx, f10) == 0x10, "rdx+0x10");
static_assert(offsetof(sub_c280a80_r14, f0) == 0x0, "r14+0x0");
static_assert(offsetof(sub_c280a80_r14, f8) == 0x8, "r14+0x8");
static_assert(offsetof(sub_c280a80_r14, fc) == 0xc, "r14+0xc");
static_assert(offsetof(sub_c280a80_rax, f0) == 0x0, "rax+0x0");
static_assert(offsetof(sub_c280a80_rax, f8) == 0x8, "rax+0x8");
static_assert(offsetof(sub_c280a80_rbx, f10) == 0x10, "rbx+0x10");
static_assert(offsetof(sub_c280a80_rsp, f20) == 0x20, "rsp+0x20");

// Type for the vtable call thunk at 0xF99FFA0 (jmp to sub_eea6040)
using vtable_call_t = void(*)(sub_c280a80_r14* obj, void* vtable_fn);

// Type for the error handler at 0xF9A8C78
using error_handler_t = void(*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t);

sub_c280a80_rcx* sub_c280a80(sub_c280a80_rcx* dest, sub_c280a80_rdx* src) {
    // Pre-declare all variables to avoid goto skipping initialization
    sub_c280a80_rdx* rdi = nullptr;
    void* rbx = nullptr;
    void* r15 = nullptr;
    std::uintptr_t header = 0;
    char* alloc_base = nullptr;
    std::uintptr_t alloc_size = 0;
    std::uintptr_t size = 0;

    // 0xc280a80..0xc280a97: basic block 0
    // 0xc280a80  push r15
    // 0xc280a82  push r14
    // 0xc280a84  push rsi
    // 0xc280a85  push rdi
    // 0xc280a86  push rbx
    // 0xc280a87  sub rsp,0x30
    // 0xc280a8b  mov rsi,rcx
    // 0xc280a8e  cmp rcx,rdx
    // 0xc280a91  je 0xC280B66
    // -> if dest == src goto L_0xc280b66 (return dest)
    // -> if dest != src goto L_0xc280a97
    L_0xc280a80:;
    if (reinterpret_cast<void*>(dest) == reinterpret_cast<void*>(src)) {
        goto L_0xc280b66;
    }

    // 0xc280a97..0xc280aa6: basic block 1
    // 0xc280a97  mov rdi,rdx
    // 0xc280a9a  mov rbx,[rsi]
    // 0xc280a9d  test rbx,rbx
    // 0xc280aa0  je 0xC280B42
    // -> if dest->begin == nullptr goto L_0xc280b42 (copy from src)
    // -> if dest->begin != nullptr goto L_0xc280aa6
    L_0xc280a97:;
    rdi = src;
    rbx = dest->f0[0];  // dest->begin
    if (rbx == nullptr) {
        goto L_0xc280b42;
    }

    // 0xc280aa6..0xc280aaf: basic block 2
    // 0xc280aa6  mov r15,[rsi+8]
    // 0xc280aaa  cmp rbx,r15
    // 0xc280aad  jne short 0xC280AC9
    // -> if dest->begin != dest->end goto L_0xc280ac9 (iterate elements)
    // -> if dest->begin == dest->end goto L_0xc280aaf (jump to deallocate)
    L_0xc280aa6:;
    r15 = dest->f0[1];  // dest->end
    if (rbx != r15) {
        goto L_0xc280ac9;
    }

    // 0xc280aaf..0xc280ab1: basic block 3
    // 0xc280aaf  jmp short 0xC280B04
    // -> if jmp goto L_0xc280b04 (deallocate storage)
    L_0xc280aaf:;
    goto L_0xc280b04;

    // 0xc280ab1..0xc280ac0: basic block 4
    // 0xc280ab1  nop [rax+rax]
    // -> if fallthrough goto L_0xc280ac0
    L_0xc280ab1:;
    // fallthrough

    // 0xc280ac0..0xc280ac9: basic block 5
    // 0xc280ac0  add rbx,0x28
    // 0xc280ac4  cmp rbx,r15
    // 0xc280ac7  je short 0xC280B01
    // -> if next_element == dest->end goto L_0xc280b01 (reset rbx to begin)
    // -> if next_element != dest->end goto L_0xc280ac9 (process element)
    L_0xc280ac0:;
    rbx = static_cast<char*>(rbx) + 0x28;
    if (rbx == r15) {
        goto L_0xc280b01;
    }

    // 0xc280ac9..0xc280ad2: basic block 6
    // 0xc280ac9  mov r14,[rbx+0x10]
    // 0xc280acd  test r14,r14
    // 0xc280ad0  je short 0xC280AC0
    // -> if element->ptr == nullptr goto L_0xc280ac0 (continue loop)
    // -> if element->ptr != nullptr goto L_0xc280ad2 (release reference)
    L_0xc280ac9:;
    {
        sub_c280a80_r14* r14 = *reinterpret_cast<sub_c280a80_r14**>(static_cast<char*>(rbx) + 0x10);
        if (r14 == nullptr) {
            goto L_0xc280ac0;
        }

        // 0xc280ad2..0xc280ad9: basic block 7
        // 0xc280ad2  lock dec dword ptr [r14+8]
        // 0xc280ad7  jne short 0xC280AC0
        // -> if (--strong_refcount) != 0 goto L_0xc280ac0 (continue loop)
        // -> if (--strong_refcount) == 0 goto L_0xc280ad9 (destroy object)
        L_0xc280ad2:;
        long strong_ref = _InterlockedDecrement(reinterpret_cast<volatile long*>(&r14->f8));
        if (strong_ref != 0) {
            goto L_0xc280ac0;
        }

        // 0xc280ad9..0xc280aef: basic block 8
        // 0xc280ad9  mov rax,[r14]
        // 0xc280adc  mov rax,[rax]
        // 0xc280adf  mov rcx,r14
        // 0xc280ae2  call qword ptr [0xF99FFA0]
        // 0xc280ae8  lock dec dword ptr [r14+0xC]
        // 0xc280aed  jne short 0xC280AC0
        // -> if (--weak_refcount) != 0 goto L_0xc280ac0 (continue loop)
        // -> if (--weak_refcount) == 0 goto L_0xc280aef (delete object)
        L_0xc280ad9:;
        {
            sub_c280a80_rax* vtable = reinterpret_cast<sub_c280a80_rax*>(r14->f0);
            void* destructor = vtable->f0;
            auto thunk = reinterpret_cast<vtable_call_t>(0xF99FFA0);
            thunk(r14, destructor);
        }
        long weak_ref = _InterlockedDecrement(reinterpret_cast<volatile long*>(&r14->fc));
        if (weak_ref != 0) {
            goto L_0xc280ac0;
        }

        // 0xc280aef..0xc280b01: basic block 9
        // 0xc280aef  mov rax,[r14]
        // 0xc280af2  mov rax,[rax+8]
        // 0xc280af6  mov rcx,r14
        // 0xc280af9  call qword ptr [0xF99FFA0]
        // 0xc280aff  jmp short 0xC280AC0
        // -> if jmp goto L_0xc280ac0 (continue loop)
        L_0xc280aef:;
        {
            sub_c280a80_rax* vtable = reinterpret_cast<sub_c280a80_rax*>(r14->f0);
            void* deleter = vtable->f8;
            auto thunk = reinterpret_cast<vtable_call_t>(0xF99FFA0);
            thunk(r14, deleter);
        }
        goto L_0xc280ac0;
    }

    // 0xc280b01..0xc280b04: basic block 10
    // 0xc280b01  mov rbx,[rsi]
    // -> if fallthrough goto L_0xc280b04
    L_0xc280b01:;
    rbx = dest->f0[0];  // reset to begin

    // 0xc280b04..0xc280b14: basic block 11
    // 0xc280b04  mov rdx,[rsi+0x10]
    // 0xc280b08  sub rdx,rbx
    // 0xc280b0b  cmp rdx,0x1000
    // 0xc280b12  jb short 0xC280B2C
    // -> if (capacity - begin) < 0x1000 goto L_0xc280b2c (skip deallocation)
    // -> if (capacity - begin) >= 0x1000 goto L_0xc280b14 (deallocate)
    L_0xc280b04:;
    {
        char* capacity_ptr = static_cast<char*>(dest->f10);
        size = capacity_ptr - static_cast<char*>(rbx);
        if (size < 0x1000) {
            goto L_0xc280b2c;
        }

        // 0xc280b14..0xc280b25: basic block 12
        // 0xc280b14  mov rax,[rbx-8]
        // 0xc280b18  add rbx,0xFFFFFFFFFFFFFFF8
        // 0xc280b1c  sub rbx,rax
        // 0xc280b1f  cmp rbx,0x20
        // 0xc280b23  jae short 0xC280B75
        // -> if (alloc_size - header) >= 0x20 goto L_0xc280b75 (error)
        // -> if (alloc_size - header) < 0x20 goto L_0xc280b25
        L_0xc280b14:;
        header = *reinterpret_cast<std::uintptr_t*>(static_cast<char*>(rbx) - 8);
        alloc_base = static_cast<char*>(rbx) - 8;
        alloc_size = alloc_base - reinterpret_cast<char*>(header);
        if (alloc_size >= 0x20) {
            goto L_0xc280b75;
        }

        // 0xc280b25..0xc280b2c: basic block 13
        // 0xc280b25  add rdx,0x27
        // 0xc280b29  mov rbx,rax
        // -> if fallthrough goto L_0xc280b2c
        L_0xc280b25:;
        size += 0x27;
        rbx = reinterpret_cast<void*>(header);

        // 0xc280b2c..0xc280b42: basic block 14
        // 0xc280b2c  mov rcx,rbx
        // 0xc280b2f  call 0xE935700
        // 0xc280b34  xorps xmm0,xmm0
        // 0xc280b37  movups [rsi],xmm0
        // 0xc280b3a  mov qword ptr [rsi+0x10],0
        // -> if fallthrough goto L_0xc280b42
        L_0xc280b2c:;
        sub_e935700(rbx, size);
        dest->f0[0] = nullptr;  // begin = nullptr
        dest->f0[1] = nullptr;  // end = nullptr
        dest->f10 = nullptr;    // capacity = nullptr
    }

    // 0xc280b42..0xc280b66: basic block 15
    // 0xc280b42  mov rax,[rdi]
    // 0xc280b45  mov [rsi],rax
    // 0xc280b48  mov rax,[rdi+8]
    // 0xc280b4c  mov [rsi+8],rax
    // 0xc280b50  mov rax,[rdi+0x10]
    // 0xc280b54  mov [rsi+0x10],rax
    // 0xc280b58  xorps xmm0,xmm0
    // 0xc280b5b  movups [rdi],xmm0
    // 0xc280b5e  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0xc280b66
    L_0xc280b42:;
    dest->f0[0] = rdi->f0[0];  // begin
    dest->f0[1] = rdi->f0[1];  // end
    dest->f10 = rdi->f10;      // capacity
    rdi->f0[0] = nullptr;
    rdi->f0[1] = nullptr;
    rdi->f10 = nullptr;

    // 0xc280b66..0xc280b75: basic block 16
    // 0xc280b66  mov rax,rsi
    // 0xc280b69  add rsp,0x30
    // 0xc280b6d  pop rbx
    // 0xc280b6e  pop rdi
    // 0xc280b6f  pop rsi
    // 0xc280b70  pop r14
    // 0xc280b72  pop r15
    // 0xc280b74  ret
    // -> (fall-through / ret / end)
    L_0xc280b66:;
    return dest;

    // 0xc280b75..0xc280b8f: basic block 17
    // 0xc280b75  mov qword ptr [rsp+0x20],0
    // 0xc280b7e  xor ecx,ecx
    // 0xc280b80  xor edx,edx
    // 0xc280b82  xor r8d,r8d
    // 0xc280b85  xor r9d,r9d
    // 0xc280b88  call qword ptr [0xF9A8C78]
    // 0xc280b8e  int3
    // -> (fall-through / ret / end)
    L_0xc280b75:;
    auto error_handler = reinterpret_cast<error_handler_t>(*reinterpret_cast<void**>(0xF9A8C78));
    error_handler(0, 0, 0, 0);
    __debugbreak();  // int3
    __debugbreak();  // int3
    // Unreachable
    return nullptr;
}

} // namespace native::helpers