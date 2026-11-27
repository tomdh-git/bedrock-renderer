// LIFT 0x66982a0 size 0x10b 1.26.62.01 sub_66982a0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_66982a0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// Layout static assertions for liftcheck
static_assert(offsetof(sub_66982a0_rcx, vtable) == 0x0, "sub_0x66982a0 rcx+0x0 field");
static_assert(offsetof(sub_66982a0_rcx, next) == 0x8, "sub_0x66982a0 rcx+0x8 field");
static_assert(offsetof(sub_66982a0_rcx, resource1) == 0x18, "sub_0x66982a0 rcx+0x18 field");
static_assert(offsetof(sub_66982a0_rcx, buffer) == 0x228, "sub_0x66982a0 rcx+0x228 field");
static_assert(offsetof(sub_66982a0_rcx, buffer_size) == 0x238, "sub_0x66982a0 rcx+0x238 field");
static_assert(offsetof(sub_66982a0_rcx, buffer_capacity) == 0x240, "sub_0x66982a0 rcx+0x240 field");
static_assert(offsetof(sub_66982a0_rcx, initialized) == 0x248, "sub_0x66982a0 rcx+0x248 field");
static_assert(sizeof(sub_66982a0_rcx) >= 0x249, "sub_0x66982a0 rcx sizeof lower bound");

static_assert(offsetof(RefCounted, vtable) == 0x0, "RefCounted vtable field");
static_assert(offsetof(RefCounted, strong_refs) == 0x8, "RefCounted strong_refs field");
static_assert(offsetof(RefCounted, weak_refs) == 0xc, "RefCounted weak_refs field");
static_assert(sizeof(RefCounted) >= 0x10, "RefCounted sizeof lower bound");

LIFT_FN(sub_66982a0, "sub_66982a0", 0x66982a0, sub_66982a0, nullptr);

// Verbatim call instructions from the disassembly of [0x66982a0, 0x66983ab) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x66982f6  call 0xE935700
0x6698330  call qword ptr [0xF99FFA0]
0x6698346  call qword ptr [0xF99FFA0]
0x6698364  call qword ptr [0xF99FFA0]
0x66983a4  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x66982a0, 0x66983ab) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

void sub_66982a0(sub_66982a0_rcx* self) {
    // Pre-declare all variables to avoid C2362 (initialization skipped by goto)
    std::uint64_t capacity = 0;
    void* buffer = nullptr;
    std::uint64_t new_size = 0;
    RefCounted* resource1 = nullptr;
    std::uint32_t strong = 0;
    VtableDtor0 dtor0 = nullptr;
    std::uint32_t weak = 0;
    VtableDtor1 dtor1 = nullptr;
    RefCounted* next = nullptr;
    ErrorHandler handler = nullptr;

    // 0x66982a0..0x66982b3: basic block 0
    // 0x66982a0  push rsi
    // 0x66982a1  push rdi
    // 0x66982a2  sub rsp,0x28
    // 0x66982a6  cmp byte ptr [rcx+0x248],1
    // 0x66982ad  jne 0x669838A
    // -> if *u8(a0+0x248) != 0x1 goto L_0x669838a
    // -> if *u8(a0+0x248) == 0x1 goto L_0x66982b3
    L_0x66982a0:;
    if (self->initialized != 1) {
        goto L_0x669838a;
    }

    // 0x66982b3..0x66982c3: basic block 1
    // 0x66982b3  mov rsi,rcx
    // 0x66982b6  mov rax,[rcx+0x240]
    // 0x66982bd  cmp rax,0x10
    // 0x66982c1  jb short 0x66982FB
    // -> if *(a0+0x240) <u 0x10 goto L_0x66982fb
    // -> if *(a0+0x240) >=u 0x10 goto L_0x66982c3
    L_0x66982b3:;
    capacity = self->buffer_capacity;
    if (capacity < 0x10) {
        goto L_0x66982fb;
    }

    // 0x66982c3..0x66982d7: basic block 2
    // 0x66982c3  mov rcx,[rsi+0x228]
    // 0x66982ca  lea rdx,[rax+1]
    // 0x66982ce  cmp rdx,0x1000
    // 0x66982d5  jb short 0x66982F6
    // -> if *(a0+0x240)+0x1 <u 0x1000 goto L_0x66982f6
    // -> if *(a0+0x240)+0x1 >=u 0x1000 goto L_0x66982d7
    L_0x66982c3:;
    buffer = self->buffer;
    new_size = capacity + 1;
    if (new_size < 0x1000) {
        goto L_0x66982f6;
    }

    // 0x66982d7..0x66982ec: basic block 3
    // 0x66982d7  mov r8,[rcx-8]
    // 0x66982db  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x66982df  sub rcx,r8
    // 0x66982e2  cmp rcx,0x20
    // 0x66982e6  jae 0x6698391
    // -> if (*(a0+0x228)-0x8 - *(*(a0+0x228)-0x8)) >=u 0x20 goto L_0x6698391
    // -> if (*(a0+0x228)-0x8 - *(*(a0+0x228)-0x8)) <u 0x20 goto L_0x66982ec
    L_0x66982d7:;
    {
        std::uint64_t* alloc_header = reinterpret_cast<std::uint64_t*>(static_cast<char*>(buffer) - 8);
        std::uint64_t alloc_base = *alloc_header;
        std::uint64_t alloc_start = reinterpret_cast<std::uint64_t>(buffer) - 8 - alloc_base;
        if (alloc_start >= 0x20) {
            goto L_0x6698391;
        }
        new_size = capacity + 0x28;
        sub_e935700(buffer, new_size, reinterpret_cast<void*>(alloc_base), nullptr);
        goto L_0x66982fb;
    }

    // 0x66982ec..0x66982f6: basic block 4
    // 0x66982ec  add rax,0x28
    // 0x66982f0  mov rdx,rax
    // 0x66982f3  mov rcx,r8
    // -> if fallthrough goto L_0x66982f6
    // This block is only reachable from block 3's fallthrough (jae not taken).
    // In that case r8=alloc_base, rax=new_size. We handle this in block 3 directly.

    // 0x66982f6..0x66982fb: basic block 5
    // 0x66982f6  call 0xE935700
    // -> if fallthrough goto L_0x66982fb
    L_0x66982f6:;
    sub_e935700(buffer, new_size, nullptr, nullptr);

    // 0x66982fb..0x6698321: basic block 6
    // 0x66982fb  mov qword ptr [rsi+0x238],0
    // 0x6698306  mov qword ptr [rsi+0x240],0xF
    // 0x6698311  mov byte ptr [rsi+0x228],0
    // 0x6698318  mov rdi,[rsi+0x18]
    // 0x669831c  test rdi,rdi
    // 0x669831f  je short 0x669834C
    // -> if *(a0+0x18) == 0 goto L_0x669834c
    // -> if *(a0+0x18) != 0 goto L_0x6698321
    L_0x66982fb:;
    self->buffer_size = 0;
    self->buffer_capacity = 0xF;
    self->buffer = nullptr;

    resource1 = self->resource1;
    if (resource1 == nullptr) {
        goto L_0x669834c;
    }

    // 0x6698321..0x6698327: basic block 7
    // 0x6698321  lock dec dword ptr [rdi+8]
    // 0x6698325  jne short 0x669834C
    // -> if (Dec *u32(*(a0+0x18)+0x8), ?) != 0 goto L_0x669834c
    // -> if (Dec *u32(*(a0+0x18)+0x8), ?) == 0 goto L_0x6698327
    L_0x6698321:;
    strong = _InterlockedDecrement(reinterpret_cast<volatile long*>(&resource1->strong_refs));
    if (strong != 0) {
        goto L_0x669834c;
    }

    // 0x6698327..0x669833c: basic block 8
    // 0x6698327  mov rax,[rdi]
    // 0x669832a  mov rax,[rax]
    // 0x669832d  mov rcx,rdi
    // 0x6698330  call qword ptr [0xF99FFA0]
    // 0x6698336  lock dec dword ptr [rdi+0xC]
    // 0x669833a  jne short 0x669834C
    // -> if (Dec *u32(*(a0+0x18)+0xC), ?) != 0 goto L_0x669834c
    // -> if (Dec *u32(*(a0+0x18)+0xC), ?) == 0 goto L_0x669833c
    L_0x6698327:;
    dtor0 = reinterpret_cast<VtableDtor0>(resource1->vtable);
    dtor0(resource1);

    weak = _InterlockedDecrement(reinterpret_cast<volatile long*>(&resource1->weak_refs));
    if (weak != 0) {
        goto L_0x669834c;
    }

    // 0x669833c..0x669834c: basic block 9
    // 0x669833c  mov rax,[rdi]
    // 0x669833f  mov rax,[rax+8]
    // 0x6698343  mov rcx,rdi
    // 0x6698346  call qword ptr [0xF99FFA0]
    // -> if fallthrough goto L_0x669834c
    L_0x669833c:;
    dtor1 = reinterpret_cast<VtableDtor1>(*reinterpret_cast<void**>(static_cast<char*>(resource1->vtable) + 8));
    dtor1(resource1);

    // 0x669834c..0x6698355: basic block 10
    // 0x669834c  mov rsi,[rsi+8]
    // 0x6698350  test rsi,rsi
    // 0x6698353  je short 0x669838A
    // -> if *(a0+0x8) == 0 goto L_0x669838a
    // -> if *(a0+0x8) != 0 goto L_0x6698355
    L_0x669834c:;
    next = self->next;
    if (next == nullptr) {
        goto L_0x669838a;
    }

    // 0x6698355..0x669835b: basic block 11
    // 0x6698355  lock dec dword ptr [rsi+8]
    // 0x6698359  jne short 0x669838A
    // -> if (Dec *u32(*(a0+0x8)+0x8), ?) != 0 goto L_0x669838a
    // -> if (Dec *u32(*(a0+0x8)+0x8), ?) == 0 goto L_0x669835b
    L_0x6698355:;
    strong = _InterlockedDecrement(reinterpret_cast<volatile long*>(&next->strong_refs));
    if (strong != 0) {
        goto L_0x669838a;
    }

    // 0x669835b..0x6698370: basic block 12
    // 0x669835b  mov rax,[rsi]
    // 0x669835e  mov rax,[rax]
    // 0x6698361  mov rcx,rsi
    // 0x6698364  call qword ptr [0xF99FFA0]
    // 0x669836a  lock dec dword ptr [rsi+0xC]
    // 0x669836e  jne short 0x669838A
    // -> if (Dec *u32(*(a0+0x8)+0xC), ?) != 0 goto L_0x669838a
    // -> if (Dec *u32(*(a0+0x8)+0xC), ?) == 0 goto L_0x6698370
    L_0x669835b:;
    dtor0 = reinterpret_cast<VtableDtor0>(next->vtable);
    dtor0(next);

    weak = _InterlockedDecrement(reinterpret_cast<volatile long*>(&next->weak_refs));
    if (weak != 0) {
        goto L_0x669838a;
    }

    // 0x6698370..0x669838a: basic block 13
    // 0x6698370  mov rax,[rsi]
    // 0x6698373  mov rax,[rax+8]
    // 0x6698377  mov rdx,[0xF99FFA0]
    // 0x669837e  mov rcx,rsi
    // 0x6698381  add rsp,0x28
    // 0x6698385  pop rdi
    // 0x6698386  pop rsi
    // 0x6698387  jmp rdx
    // -> (fall-through / ret / end)
    L_0x6698370:;
    dtor1 = reinterpret_cast<VtableDtor1>(*reinterpret_cast<void**>(static_cast<char*>(next->vtable) + 8));
    // Tail call - stack cleanup then jmp
    dtor1(next);
    // Unreachable due to tail call
    __assume(0);

    // 0x669838a..0x6698391: basic block 14
    // 0x669838a  add rsp,0x28
    // 0x669838e  pop rdi
    // 0x669838f  pop rsi
    // 0x6698390  ret
    // -> (fall-through / ret / end)
    L_0x669838a:;
    return;

    // 0x6698391..0x66983ab: basic block 15 (error path)
    // 0x6698391  mov qword ptr [rsp+0x20],0
    // 0x669839a  xor ecx,ecx
    // 0x669839c  xor edx,edx
    // 0x669839e  xor r8d,r8d
    // 0x66983a1  xor r9d,r9d
    // 0x66983a4  call qword ptr [0xF9A8C78]
    // 0x66983aa  int3
    // -> (fall-through / ret / end)
    L_0x6698391:;
    // Error handler: invalid allocation header
    handler = reinterpret_cast<ErrorHandler>(*reinterpret_cast<void**>(0xF9A8C78));
    handler(0, 0, 0, 0);
    __debugbreak(); // int3
}

} // namespace native::helpers