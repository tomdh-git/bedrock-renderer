// LIFT 0xbcd3530 size 0x109 1.26.62.01 sub_bcd3530
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_bcd3530.h"

#include <cstdint>
#include <cstddef>

namespace native {

// Lift-set callee 0xe935700 (header: helpers/sub_e935700.h). Declared here with the ABI
// recovered in that header: argument in RCX, result in RAX, body is `jmp 0x392960`.
void* sub_e935700(void* a0);

} // namespace native

namespace native::helpers {

// Boundary STL routine at 0x9b250 (destroys the object whose address arrives in RCX); other
// lifts that call it declare it the same way (bgfx/sub_bc82ad0_chunk_c01.cpp).
extern "C" void sub_9b250(void* a1);

namespace {

// 0xbcd361f..0xbcd3639: basic block 14
// 0xbcd361f  mov qword ptr [rsp+0x20],0
// 0xbcd3628  xor ecx,ecx
// 0xbcd362a  xor edx,edx
// 0xbcd362c  xor r8d,r8d
// 0xbcd362f  xor r9d,r9d
// 0xbcd3632  call qword ptr [0xF9A8C78]
// 0xbcd3638  int3
// All five arguments are zero (the fifth occupies the caller's [rsp+0x20] stack slot) and
// the callee is the function pointer held in data slot 0xF9A8C78 [data_f9a8c78]. It does
// not return, so the int3 at 0xbcd3638 is never reached.
[[noreturn]] void bcd3530_deallocation_failure() {
    using FailureFn = void (*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t);
    FailureFn const fn = *reinterpret_cast<FailureFn*>(static_cast<std::uintptr_t>(0xF9A8C78));
    fn(0, 0, 0, 0, 0);
}

} // namespace

LIFT_FN(sub_bcd3530, "sub_bcd3530", 0xbcd3530, sub_bcd3530, nullptr);

// Verbatim call instructions from the disassembly of [0xbcd3530, 0xbcd3639) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xbcd3573  call 0xE935700
0xbcd35a7  call 0x9B250
0xbcd35b4  call 0xE935700
0xbcd35ca  call 0xE935700
0xbcd3604  call 0xE935700
0xbcd3632  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0xbcd3530, 0xbcd3639) is covered by a block range comment
// and its verbatim quotes below.

void sub_bcd3530(void* self_) {
    auto* const self = static_cast<sub_bcd3530_rcx*>(self_);

    // 0xbcd3530..0xbcd3543: basic block 0
    // 0xbcd3530  push rsi
    // 0xbcd3531  push rdi
    // 0xbcd3532  push rbx
    // 0xbcd3533  sub rsp,0x30
    // 0xbcd3537  mov rsi,rcx
    // 0xbcd353a  mov rcx,[rcx+0x38]
    // 0xbcd353e  test rcx,rcx
    // 0xbcd3541  je short 0xBCD3586
    // -> if *(a0+0x38) == 0 goto L_0xbcd3586
    // -> if *(a0+0x38) != 0 goto L_0xbcd3543
    {
        void* p = self->bufferBBegin;
        if (p != nullptr) {
            // 0xbcd3543..0xbcd3553: basic block 1
            // 0xbcd3543  mov rdx,[rsi+0x48]
            // 0xbcd3547  sub rdx,rcx
            // 0xbcd354a  cmp rdx,0x1000
            // 0xbcd3551  jb short 0xBCD356F
            // -> if (*(a0+0x48) - *(a0+0x38)) <u 0x1000 goto L_0xbcd356f
            // -> if (*(a0+0x48) - *(a0+0x38)) >=u 0x1000 goto L_0xbcd3553
            std::uint64_t bytes =
                reinterpret_cast<std::uint64_t>(self->bufferBCap) - reinterpret_cast<std::uint64_t>(p);
            if (bytes >= 0x1000) {
                // 0xbcd3553..0xbcd3568: basic block 2
                // 0xbcd3553  mov rax,[rcx-8]
                // 0xbcd3557  add rcx,0xFFFFFFFFFFFFFFF8
                // 0xbcd355b  sub rcx,rax
                // 0xbcd355e  cmp rcx,0x20
                // 0xbcd3562  jae 0xBCD361F
                // -> if (*(a0+0x38)-0x8 - *(*(a0+0x38)-0x8)) >=u 0x20 goto L_0xbcd361f
                // -> if (*(a0+0x38)-0x8 - *(*(a0+0x38)-0x8)) <u 0x20 goto L_0xbcd3568
                std::uint64_t* const allocHeader =
                    reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(p) - 8);
                std::uint64_t const allocationBase = *allocHeader;
                if (reinterpret_cast<std::uint64_t>(allocHeader) - allocationBase >= 0x20) {
                    goto L_0xbcd361f;
                }
                // 0xbcd3568..0xbcd356f: basic block 3
                // 0xbcd3568  add rdx,0x27
                // 0xbcd356c  mov rcx,rax
                // -> if fallthrough goto L_0xbcd356f
                bytes += 0x27;
                p = reinterpret_cast<void*>(allocationBase);
            }
            // 0xbcd356f..0xbcd3586: basic block 4
            // 0xbcd356f  lea rdi,[rsi+0x38]
            // 0xbcd3573  call 0xE935700
            // 0xbcd3578  xorps xmm0,xmm0
            // 0xbcd357b  movups [rdi],xmm0
            // 0xbcd357e  mov qword ptr [rdi+0x10],0
            // -> if fallthrough goto L_0xbcd3586
            native::sub_e935700(p);
            self->bufferBBegin = nullptr;
            self->bufferBEnd = nullptr;
            self->bufferBCap = nullptr;
        }
    }

L_0xbcd3586:
    {
        // 0xbcd3586..0xbcd359d: basic block 5
        // 0xbcd3586  mov rax,[rsi+0x28]
        // 0xbcd358a  mov rcx,[rax+8]
        // 0xbcd358e  mov qword ptr [rcx],0
        // 0xbcd3595  mov rdi,[rax]
        // 0xbcd3598  test rdi,rdi
        // 0xbcd359b  je short 0xBCD35C1
        // -> if *(*(a0+0x28)) == 0 goto L_0xbcd35c1
        // -> if *(*(a0+0x28)) != 0 goto L_0xbcd359d
        sub_bcd3530_rax* const header = self->listHeader;
        *header->clearSlot = 0;
        sub_bcd3530_rdi* node = header->first;
        // 0xbcd35a0..0xbcd35c1: basic block 7 (entered at 0xbcd35a0; 0xbcd359d is the
        // one-byte nop of block 6 and has no effect)
        // 0xbcd35a0  mov rbx,[rdi]
        // 0xbcd35a3  lea rcx,[rdi+0x10]
        // 0xbcd35a7  call 0x9B250
        // 0xbcd35ac  mov edx,0x50
        // 0xbcd35b1  mov rcx,rdi
        // 0xbcd35b4  call 0xE935700
        // 0xbcd35b9  mov rdi,rbx
        // 0xbcd35bc  test rbx,rbx
        // 0xbcd35bf  jne short 0xBCD35A0
        // -> if next != 0 goto L_0xbcd35a0
        // -> if next == 0 goto L_0xbcd35c1
        while (node != nullptr) {
            sub_bcd3530_rdi* const next = node->next;
            sub_9b250(&node->payload);
            native::sub_e935700(node);
            node = next;
        }
        // 0xbcd35c1..0xbcd35d8: basic block 8
        // 0xbcd35c1  mov rcx,[rsi+0x28]
        // 0xbcd35c5  mov edx,0x50
        // 0xbcd35ca  call 0xE935700
        // 0xbcd35cf  mov rcx,[rsi+8]
        // 0xbcd35d3  test rcx,rcx
        // 0xbcd35d6  je short 0xBCD3617
        // -> if *(a0+0x8) == 0 goto L_0xbcd3617
        // -> if *(a0+0x8) != 0 goto L_0xbcd35d8
        native::sub_e935700(header);
        void* q = self->bufferABegin;
        if (q != nullptr) {
            // 0xbcd35d8..0xbcd35e8: basic block 9
            // 0xbcd35d8  mov rdx,[rsi+0x18]
            // 0xbcd35dc  sub rdx,rcx
            // 0xbcd35df  cmp rdx,0x1000
            // 0xbcd35e6  jb short 0xBCD3600
            // -> if (*(a0+0x18) - *(a0+0x8)) <u 0x1000 goto L_0xbcd3600
            // -> if (*(a0+0x18) - *(a0+0x8)) >=u 0x1000 goto L_0xbcd35e8
            std::uint64_t bytes =
                reinterpret_cast<std::uint64_t>(self->bufferACap) - reinterpret_cast<std::uint64_t>(q);
            if (bytes >= 0x1000) {
                // 0xbcd35e8..0xbcd35f9: basic block 10
                // 0xbcd35e8  mov rax,[rcx-8]
                // 0xbcd35ec  add rcx,0xFFFFFFFFFFFFFFF8
                // 0xbcd35f0  sub rcx,rax
                // 0xbcd35f3  cmp rcx,0x20
                // 0xbcd35f7  jae short 0xBCD361F
                // -> if (*(a0+0x8)-0x8 - *(*(a0+0x8)-0x8)) >=u 0x20 goto L_0xbcd361f
                // -> if (*(a0+0x8)-0x8 - *(*(a0+0x8)-0x8)) <u 0x20 goto L_0xbcd35f9
                std::uint64_t* const allocHeader =
                    reinterpret_cast<std::uint64_t*>(static_cast<std::uint8_t*>(q) - 8);
                std::uint64_t const allocationBase = *allocHeader;
                if (reinterpret_cast<std::uint64_t>(allocHeader) - allocationBase >= 0x20) {
                    goto L_0xbcd361f;
                }
                // 0xbcd35f9..0xbcd3600: basic block 11
                // 0xbcd35f9  add rdx,0x27
                // 0xbcd35fd  mov rcx,rax
                // -> if fallthrough goto L_0xbcd3600
                bytes += 0x27;
                q = reinterpret_cast<void*>(allocationBase);
            }
            // 0xbcd3600..0xbcd3617: basic block 12
            // 0xbcd3600  add rsi,8
            // 0xbcd3604  call 0xE935700
            // 0xbcd3609  xorps xmm0,xmm0
            // 0xbcd360c  movups [rsi],xmm0
            // 0xbcd360f  mov qword ptr [rsi+0x10],0
            // -> if fallthrough goto L_0xbcd3617
            native::sub_e935700(q);
            self->bufferABegin = nullptr;
            self->bufferAEnd = nullptr;
            self->bufferACap = nullptr;
        }
    }

L_0xbcd3617:
    // 0xbcd3617..0xbcd361f: basic block 13
    // 0xbcd3617  add rsp,0x30
    // 0xbcd361b  pop rbx
    // 0xbcd361c  pop rdi
    // 0xbcd361d  pop rsi
    // 0xbcd361e  ret
    return;

L_0xbcd361f:
    // 0xbcd361f..0xbcd3639: basic block 14 (shared failure path of blocks 2 and 10)
    bcd3530_deallocation_failure();
}

} // namespace native::helpers
