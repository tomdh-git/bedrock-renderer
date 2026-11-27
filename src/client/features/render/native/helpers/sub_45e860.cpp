// LIFT 0x45e860 size 0x102 1.26.62.01 sub_45e860
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_45e860.h"
#include "client/features/render/native/helpers/sub_87440.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// Verbatim call instructions from the disassembly of [0x45e860, 0x45e962) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x45e890  call 0x45E5C0
0x45e8a3  call 0x45E9B0
0x45e8fb  call 0x443A80
0x45e93d  call 0x87440
0x45e94c  call 0xEEC5A10
#endif

namespace {

// sub_eec5a10 (0xeec5a10): tail-forwarder to MSVCP140!_Mtx_unlock via IAT slot.
// Declared here to avoid pulling in the heavy sub_eec5a10.h dependencies.
struct _Mtx;
void sub_eec5a10(_Mtx* mtx);

} // namespace

void* sub_45e860(void* self, void* out, void* a2, void* a3) {
    // rcx=self, rdx=out, r8=a2, r9=a3
    // rbx=self, rsi=out, rdi=a3, r14=a2

    auto* self_s = reinterpret_cast<sub_45e860_self*>(self);
    auto* out_o = reinterpret_cast<sub_45e860_out*>(out);

    // Stack frame overlay (rbp = rsp + 0x80):
    //   [rbp-0x60..0x21]  data block (64 bytes, written by sub_45e9b0)
    //   [rbp-0x20]        flag1 (byte, written by sub_45e5c0)
    //   [rbp-0x18]        mutex (qword, written by sub_45e5c0)
    //   [rbp-0x10]        flag2 (byte, read but never written in this function)
    sub_45e860_stack stack = {};

    // 0x45e860..0x45e890: prologue (register saves, stack cookie; no observable effect)

    // 0x45e889  lea rdx,[rbp-0x18]   /   0x45e88d  mov r8b,1
    // 0x45e890  call 0x45E5C0        ; sub_45e5c0(self, &stack.mutex, 1)
    //   writes stack.mutex = [rbp-0x18], stack.flag1 = [rbp-0x20] (via [rdx-8])
    sub_45e5c0(self, &stack.mutex, 1);

    // 0x45e896  lea rdx,[rbp-0x60]   /   0x45e89a  mov rcx,rbx
    // 0x45e89d  mov r8,r14           /   0x45e8a0  mov r9,rdi
    // 0x45e8a3  call 0x45E9B0        ; sub_45e9b0(self, stack.data_block, a2, a3)
    //   writes 64 bytes at stack.data_block = [rbp-0x60..0x21]
    sub_45e9b0(self, reinterpret_cast<void*>(stack.data_block), a2, a3);

    // 0x45e8a9  mov rax,[rbx+0x10]   ; rax = self->node
    // 0x45e8ad  movzx edx,byte ptr [rbp-0x20]   ; flag1 = stack.flag1
    std::uint8_t flag1 = stack.flag1;

    auto* node = reinterpret_cast<sub_45e860_node*>(self_s->node);

    // 0x45e8b1  test dl,dl   /   0x45e8b3  je short 0x45E8D0
    if (flag1 != 0) {
        // Block 1 (0x45e8b5..0x45e8d0): flag != 0 path
        // 0x45e8b5  lock inc qword ptr [rax+0x40]   ; node->refcount++
        _InterlockedIncrement64(reinterpret_cast<volatile LONG64*>(&node->refcount));
        // 0x45e8ba  lock add [rax+0x48],rdi   ; node->total += a3 (rdi = a3)
        _InterlockedExchangeAdd64(
            reinterpret_cast<volatile LONG64*>(&node->total),
            reinterpret_cast<LONG64>(a3));
        // 0x45e8bf  mov ecx,0x20
        // 0x45e8c4  lea r8,[0x128D0A50]
        // 0x45e8cb  mov r9,rdi
        // 0x45e8ce  jmp short 0x45E8DF
        // 0x45e8df  lock inc qword ptr [r8]   ; data_128d0a50[0]++
        _InterlockedIncrement64(
            reinterpret_cast<volatile LONG64*>(&data_128d0a50[0]));
        // 0x45e8e3  lea r8,[0x128D0A38]
        // 0x45e8ea  lock add [rcx+r8],r9   ; data_128d0a38[4] += a3 (ecx = 0x20)
        _InterlockedExchangeAdd64(
            reinterpret_cast<volatile LONG64*>(&data_128d0a38[4]),
            reinterpret_cast<LONG64>(a3));
    } else {
        // Block 2 (0x45e8d0..0x45e8df): flag == 0 path
        // 0x45e8d0  lea r8,[rax+0x50]   ; r8 = &node->counter
        // 0x45e8d4  mov r9d,1
        // 0x45e8da  mov ecx,0x28
        // 0x45e8df  lock inc qword ptr [r8]   ; node->counter++
        _InterlockedIncrement64(
            reinterpret_cast<volatile LONG64*>(&node->counter));
        // 0x45e8e3  lea r8,[0x128D0A38]
        // 0x45e8ea  lock add [rcx+r8],r9   ; data_128d0a38[5] += 1 (ecx = 0x28, r9 = 1)
        _InterlockedExchangeAdd64(
            reinterpret_cast<volatile LONG64*>(&data_128d0a38[5]),
            1);
    }

    // 0x45e8ef  mov rcx,[rax+8]   ; rcx = node->link
    // 0x45e8f3  test rcx,rcx      /   0x45e8f6  je short 0x45E900
    if (node->link != nullptr) {
        // Block 4 (0x45e8f8..0x45e900): node->link != 0 path
        // 0x45e8f8  mov r8,rdi   ; r8 = a3
        // 0x45e8fb  call 0x443A80   ; sub_443a80(node->link, ?, a3)
        sub_443a80(node->link, nullptr, a3);
    }

    // 0x45e900  movzx eax,byte ptr [rbp-0x20]   ; al = flag1
    // 0x45e904  mov [rsi+0x40],al   ; out->flag = flag1
    out_o->flag = flag1;

    // 0x45e907  test al,al   /   0x45e909  jne short 0x45E939
    if (flag1 == 0) {
        // Block 6 (0x45e90b..0x45e939): flag == 0 path
        // 0x45e90b  movups xmm0,[rbp-0x60]   /   0x45e90f  movups [rsi],xmm0
        out_o->data0[0] = *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x00]);
        out_o->data0[1] = *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x08]);
        // 0x45e912  movups xmm0,[rbp-0x50]   /   0x45e916  movups [rsi+0x10],xmm0
        out_o->data1[0] = *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x10]);
        out_o->data1[1] = *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x18]);
        // 0x45e91a  movups xmm0,[rbp-0x40]
        out_o->data2[0] = *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x20]);
        out_o->data2[1] = *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x28]);
        // 0x45e91e  xorps xmm1,xmm1
        // 0x45e921  movups [rbp-0x50],xmm1   ; data_block[0x10..0x17] = 0
        *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x10]) = 0;
        // 0x45e925  movups [rbp-0x40],xmm1   ; data_block[0x20..0x27] = 0
        *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x20]) = 0;
        // 0x45e929  movups [rsi+0x20],xmm0
        // 0x45e92d  movups xmm0,[rbp-0x30]
        out_o->data3[0] = *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x30]);
        out_o->data3[1] = *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x38]);
        // 0x45e931  movups [rbp-0x30],xmm1   ; data_block[0x30..0x37] = 0
        *reinterpret_cast<std::uint64_t*>(&stack.data_block[0x30]) = 0;
    }

    // 0x45e939  lea rcx,[rbp-0x60]   /   0x45e93d  call 0x87440
    native::sub_87440(reinterpret_cast<void*>(stack.data_block));

    // 0x45e942  cmp byte ptr [rbp-0x10],1   /   0x45e946  jne short 0x45E951
    if (stack.flag2 == 1) {
        // Block 8 (0x45e948..0x45e951): flag2 == 1 path
        // 0x45e948  mov rcx,[rbp-0x18]   /   0x45e94c  call 0xEEC5A10
        sub_eec5a10(reinterpret_cast<_Mtx*>(stack.mutex));
    }

    // 0x45e951  mov rax,rsi   ; return out
    return out;
}

LIFT_FN(sub_45e860, "sub_45e860", 0x45e860, sub_45e860, nullptr);

} // namespace native::helpers
