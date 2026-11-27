// LIFT 0x79950 size 0x11a 1.26.62.01 sub_79950
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_79950.h"
#include "client/features/render/native/helpers/sub_9c650.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native {

// Callees outside native::helpers; the ABI below is the one recovered from the
// exe and recorded in helpers/sub_9c590.h and helpers/sub_e935700.h.
void* sub_9c590(void* slot, void* node);
void* sub_e935700(void* a0);

} // namespace native

namespace native::helpers {

LIFT_FN(sub_79950, "sub_79950", 0x79950, sub_79950, nullptr);

// Layout assertions (also in sub_79950.h; repeated here so the lift source is
// self-contained for the layout check).
static_assert(offsetof(sub_79950_rcx, f0) == 0x0, "sub_79950 rcx+0x0 f0");
static_assert(offsetof(sub_79950_rcx, f10) == 0x10, "sub_79950 rcx+0x10 f10");
static_assert(offsetof(sub_79950_rcx, f20) == 0x20, "sub_79950 rcx+0x20 f20");
static_assert(offsetof(sub_79950_rcx, f30) == 0x30, "sub_79950 rcx+0x30 f30");
static_assert(offsetof(sub_79950_rcx, f40) == 0x40, "sub_79950 rcx+0x40 f40");
static_assert(offsetof(sub_79950_rdx, f0) == 0x0, "sub_79950 rdx+0x0 f0");
static_assert(offsetof(sub_79950_rdx, f10) == 0x10, "sub_79950 rdx+0x10 f10");
static_assert(offsetof(sub_79950_rdx, f20) == 0x20, "sub_79950 rdx+0x20 f20");
static_assert(offsetof(sub_79950_rdx, f30) == 0x30, "sub_79950 rdx+0x30 f30");
static_assert(offsetof(sub_79950_rdx, f30) + 8 == 0x38, "sub_79950 rdx+0x38 limit");
static_assert(offsetof(sub_79950_rbx, f0) == 0x0, "sub_79950 rbx+0x0 f0");
static_assert(offsetof(sub_79950_rbx, f10) == 0x10, "sub_79950 rbx+0x10 f10");
static_assert(offsetof(sub_79950_rsp, f20) == 0x20, "sub_79950 rsp+0x20 f20");
static_assert(offsetof(sub_79950_rsp, f30) == 0x30, "sub_79950 rsp+0x30 f30");
static_assert(offsetof(sub_79950_rsp, f40) == 0x40, "sub_79950 rsp+0x40 f40");
static_assert(offsetof(sub_79950_rsp, f50) == 0x50, "sub_79950 rsp+0x50 f50");
static_assert(offsetof(sub_79950_rsp, f58) == 0x58, "sub_79950 rsp+0x58 f58");
static_assert(offsetof(sub_79950_rsp, f68) == 0x68, "sub_79950 rsp+0x68 f68");

// Verbatim call instructions from the disassembly of [0x79950, 0x79a6a) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x799bd  call 0x9C650
0x799e6  call 0x9C590
0x79a22  call 0xE935700
0x79a3c  call 0x9C650
0x79a63  call qword ptr [0xF9A8C78]
#endif

// Move the four 16-byte slots out of a1 into a0, zero the source slots, build an
// empty temporary release context, then (if a children list survived) release the
// children and the child block, release the a1+0x10 container, and return a0.
uintptr_t sub_79950(void* a0, void* a1) {
    auto* out = reinterpret_cast<sub_79950_rcx*>(a0);
    auto* src = reinterpret_cast<sub_79950_rdx*>(a1);

    // 0x79950..0x799cb: basic block 0
    // 0x79950  push r15
    // 0x79952  push r14
    // 0x79954  push rsi
    // 0x79955  push rdi
    // 0x79956  push rbx
    // 0x79957  sub rsp,0x70
    // 0x7995b  mov rdi,rdx
    // 0x7995e  mov rsi,rcx
    // 0x79961  movups xmm0,[rdx]
    // 0x79964  movaps [rsp+0x30],xmm0
    // 0x79969  lea rcx,[rsp+0x40]
    // 0x7996e  movups xmm0,[rdx+0x10]
    // 0x79972  movups xmm1,[rdx+0x20]
    // 0x79976  movups xmm2,[rdx+0x30]
    // 0x7997a  xorps xmm3,xmm3
    // 0x7997d  movups [rdx+0x10],xmm3
    // 0x79981  movups [rdx+0x20],xmm3
    // 0x79985  movups [rdx+0x30],xmm3
    // 0x79989  mov byte ptr [rsi+0x40],0
    // 0x7998d  movaps xmm4,[rsp+0x30]
    // 0x79992  movups [rsi],xmm4
    // 0x79995  movaps [rsp+0x40],xmm3
    // 0x7999a  mov qword ptr [rsp+0x50],0
    // 0x799a3  movups [rsi+0x10],xmm0
    // 0x799a7  movups [rsp+0x58],xmm3
    // 0x799ac  mov qword ptr [rsp+0x68],0
    // 0x799b5  movups [rsi+0x20],xmm1
    // 0x799b9  movups [rsi+0x30],xmm2
    // 0x799bd  call 0x9C650
    // 0x799c2  mov r14,[rdi+0x28]
    // 0x799c6  test r14,r14
    // 0x799c9  je short 0x79A35
    const std::uint64_t s00 = src->f0[0];
    const std::uint64_t s01 = src->f0[1];
    const std::uint64_t s10 = src->f10[0];
    const std::uint64_t s11 = src->f10[1];
    const std::uint64_t s20 = src->f20[0];
    const std::uint64_t s21 = src->f20[1];
    const std::uint64_t s30 = src->f30[0];
    const std::uint64_t s31 = src->f30[1];

    src->f10[0] = 0;
    src->f10[1] = 0;
    src->f20[0] = 0;
    src->f20[1] = 0;
    src->f30[0] = 0;
    src->f30[1] = 0;

    out->f40 = 0;
    out->f0[0] = s00;
    out->f0[1] = s01;

    // 0x79995..0x799ac: temporary release context at rsp+0x40, zero-filled.
    alignas(16) std::uint64_t scratch[6] = {};

    out->f10[0] = s10;
    out->f10[1] = s11;
    out->f20[0] = s20;
    out->f20[1] = s21;
    out->f30[0] = s30;
    out->f30[1] = s31;

    sub_9c650(scratch);   // 0x799bd  call 0x9C650

    void* r14 = reinterpret_cast<void*>(src->f20[1]);   // 0x799c2  mov r14,[rdi+0x28]
    if (r14 != nullptr) {
        // 0x799cb..0x799d8: basic block 1
        // 0x799cb  lea rbx,[rdi+0x28]
        // 0x799cf  mov r15,[rdi+0x30]
        // 0x799d3  cmp r14,r15
        // 0x799d6  je short 0x799F7
        auto* rbx = reinterpret_cast<sub_79950_rbx*>(&src->f20);
        void* r15 = reinterpret_cast<void*>(src->f30[0]);

        if (r14 != r15) {
            // 0x799d8..0x799e0: basic block 2
            // 0x799d8  nop [rax+rax]

            // 0x799e0..0x799f4: basic block 3
            // 0x799e0  mov rcx,rbx
            // 0x799e3  mov rdx,r14
            // 0x799e6  call 0x9C590
            // 0x799eb  add r14,0x40
            // 0x799ef  cmp r14,r15
            // 0x799f2  jne short 0x799E0
            do {
                native::sub_9c590(rbx, r14);   // 0x799e6  call 0x9C590
                r14 = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(r14) + 0x40);
            } while (r14 != r15);

            // 0x799f4..0x799f7: basic block 4
            // 0x799f4  mov r14,[rbx]
            r14 = rbx->f0[0];
        }

        // 0x799f7..0x79a07: basic block 5
        // 0x799f7  mov rdx,[rdi+0x38]
        // 0x799fb  sub rdx,r14
        // 0x799fe  cmp rdx,0x1000
        // 0x79a05  jb short 0x79A1F
        uintptr_t remaining = static_cast<uintptr_t>(src->f30[1]) -
                              reinterpret_cast<uintptr_t>(r14);
        void* free_ptr = r14;
        if (remaining >= 0x1000) {
            // 0x79a07..0x79a18: basic block 6
            // 0x79a07  mov rax,[r14-8]
            // 0x79a0b  add r14,0xFFFFFFFFFFFFFFF8
            // 0x79a0f  sub r14,rax
            // 0x79a12  cmp r14,0x20
            // 0x79a16  jae short 0x79A50
            std::uint64_t rax = *reinterpret_cast<std::uint64_t*>(
                reinterpret_cast<uintptr_t>(r14) - 8);
            std::uint64_t block_start = (reinterpret_cast<uintptr_t>(r14) - 8) - rax;
            if (block_start >= 0x20) {
                // 0x79a50..0x79a6a: basic block 10
                // 0x79a50  mov qword ptr [rsp+0x20],0
                // 0x79a59  xor ecx,ecx
                // 0x79a5b  xor edx,edx
                // 0x79a5d  xor r8d,r8d
                // 0x79a60  xor r9d,r9d
                // 0x79a63  call qword ptr [0xF9A8C78]
                // 0x79a69  int3
                using FailFn = void (*)(void*, void*, void*, void*, void*);
                FailFn fail = reinterpret_cast<FailFn>(
                    *reinterpret_cast<uintptr_t*>(
                        RewriteRegistry::imageBase() + 0xF9A8C78));
                fail(nullptr, nullptr, nullptr, nullptr, nullptr);
                __assume(false);   // the slot handler does not return
            }

            // 0x79a18..0x79a1f: basic block 7
            // 0x79a18  or rdx,0x27
            // 0x79a1c  mov r14,rax
            remaining |= 0x27;
            free_ptr = reinterpret_cast<void*>(rax);
        }

        // 0x79a1f..0x79a35: basic block 8
        // 0x79a1f  mov rcx,r14
        // 0x79a22  call 0xE935700
        // 0x79a27  xorps xmm0,xmm0
        // 0x79a2a  movups [rbx],xmm0
        // 0x79a2d  mov qword ptr [rbx+0x10],0
        (void)remaining;
        native::sub_e935700(free_ptr);   // 0x79a22  call 0xE935700
        rbx->f0[0] = nullptr;
        rbx->f0[1] = nullptr;
        rbx->f10 = 0;
    }

    // 0x79a35..0x79a50: basic block 9
    // 0x79a35  add rdi,0x10
    // 0x79a39  mov rcx,rdi
    // 0x79a3c  call 0x9C650
    // 0x79a41  mov rax,rsi
    // 0x79a44  add rsp,0x70
    // 0x79a48  pop rbx
    // 0x79a49  pop rdi
    // 0x79a4a  pop rsi
    // 0x79a4b  pop r14
    // 0x79a4d  pop r15
    // 0x79a4f  ret
    sub_9c650(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(src) + 0x10));   // 0x79a3c  call 0x9C650
    return reinterpret_cast<uintptr_t>(a0);
}

} // namespace native::helpers
