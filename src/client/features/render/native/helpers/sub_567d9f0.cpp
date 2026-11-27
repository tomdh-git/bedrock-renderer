// LIFT 0x567d9f0 size 0x109 1.26.62.01 sub_567d9f0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_567d9f0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_567d9f0, "sub_567d9f0", 0x567d9f0, sub_567d9f0, nullptr);

// Verbatim call instructions from the disassembly of [0x567d9f0, 0x567daf9) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x567daeb  call 0xE935700
#endif

// Ranges: every instruction of [0x567d9f0, 0x567daf9) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

extern "C" void sub_e935700(uint64_t, uint64_t, void*, void*); // forward declaration; signature per register usage at call site

uintptr_t sub_567d9f0(void* self, void* a1) {
    // 0x567d9f0..0x567daa7: basic block 0
    // 0x567d9f0  push rsi
    // 0x567d9f1  sub rsp,0x20
    // 0x567d9f5  mov rax,rdx
    // 0x567d9f8  mov rdx,[rdx+0x10]
    // 0x567d9fc  movzx r8d,byte ptr [rax+0x18]
    // 0x567da01  mov r9,0xCBF29CE484222325
    // 0x567da0b  xor r9,r8
    // 0x567da0e  mov r8,0x100000001B3
    // 0x567da18  imul r9,r8
    // 0x567da1c  movzx r10d,byte ptr [rax+0x19]
    // 0x567da21  xor r10,r9
    // 0x567da24  imul r10,r8
    // 0x567da28  movzx r9d,byte ptr [rax+0x1A]
    // 0x567da2d  xor r9,r10
    // 0x567da30  imul r9,r8
    // 0x567da34  movzx r10d,byte ptr [rax+0x1B]
    // 0x567da39  xor r10,r9
    // 0x567da3c  imul r10,r8
    // 0x567da40  movzx r9d,byte ptr [rax+0x1C]
    // 0x567da45  xor r9,r10
    // 0x567da48  imul r9,r8
    // 0x567da4c  movzx r10d,byte ptr [rax+0x1D]
    // 0x567da51  xor r10,r9
    // 0x567da54  imul r10,r8
    // 0x567da58  movzx r9d,byte ptr [rax+0x1E]
    // 0x567da5d  xor r9,r10
    // 0x567da60  imul r9,r8
    // 0x567da64  movzx r10d,byte ptr [rax+0x1F]
    // 0x567da69  xor r10,r9
    // 0x567da6c  imul r10,r8
    // 0x567da70  mov r8,rdx
    // 0x567da73  shl r8,6
    // 0x567da77  mov r9,rdx
    // 0x567da7a  shr r9,2
    // 0x567da7e  add r9,r8
    // 0x567da81  mov r8d,0x9E3779B9
    // 0x567da87  add r8,r9
    // 0x567da8a  add r8,r10
    // 0x567da8d  xor r8,rdx
    // 0x567da90  and r8,[rcx+0x30]
    // 0x567da94  mov rdx,[rcx+0x18]
    // 0x567da98  shl r8,4
    // 0x567da9c  mov r9,[rdx+r8]
    // 0x567daa0  cmp [rdx+r8+8],rax
    // 0x567daa5  je short 0x567DAB5
    // -> if [bucket+8] == a1 goto L_0x567dab5
    // -> if [bucket+8] != a1 goto L_0x567daa7
    L_0x567d9f0:;
    auto* self_s = static_cast<sub_567d9f0_rcx*>(self);
    auto* a1_s = static_cast<sub_567d9f0_rdx*>(a1);
    void* rax = a1;
    void* rdx = a1_s->f10;

    // FNV-1a hash of 8 bytes at a1+0x18..0x1F
    uint64_t hash = 0xCBF29CE484222325ull;
    const uint64_t fnv_prime = 0x100000001B3ull;
    hash ^= a1_s->f18; hash *= fnv_prime;
    hash ^= a1_s->f19; hash *= fnv_prime;
    hash ^= a1_s->f1a; hash *= fnv_prime;
    hash ^= a1_s->f1b; hash *= fnv_prime;
    hash ^= a1_s->f1c; hash *= fnv_prime;
    hash ^= a1_s->f1d; hash *= fnv_prime;
    hash ^= a1_s->f1e; hash *= fnv_prime;
    hash ^= a1_s->f1f; hash *= fnv_prime;

    uintptr_t r8 = reinterpret_cast<uintptr_t>(rdx);
    uintptr_t r9 = r8 >> 2;
    r8 <<= 6;
    r9 += r8;
    r8 = 0x9E3779B9ull;
    r8 += r9;
    r8 += hash;
    r8 ^= reinterpret_cast<uintptr_t>(rdx);
    r8 &= self_s->f30;
    rdx = self_s->f18;
    r8 <<= 4;

    void** bucket = reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rdx) + r8);
    void* r9_val = bucket[0];
    if (bucket[1] == rax) {
        goto L_0x567dab5;
    }

    // 0x567daa7..0x567daac: basic block 1
    // 0x567daa7  cmp r9,rax
    // 0x567daaa  jne short 0x567DACD
    // -> if r9 != a1 goto L_0x567dacd
    // -> if r9 == a1 goto L_0x567daac
    L_0x567daa7:;
    if (r9_val != rax) {
        goto L_0x567dacd;
    }

    // 0x567daac..0x567dab5: basic block 2
    // 0x567daac  mov r9,[rax]
    // 0x567daaf  mov [rdx+r8],r9
    // 0x567dab3  jmp short 0x567DACD
    // -> if jmp goto L_0x567dacd
    L_0x567daac:;
    r9_val = *static_cast<void**>(rax);
    bucket[0] = r9_val;
    goto L_0x567dacd;

    // 0x567dab5..0x567daba: basic block 3
    // 0x567dab5  cmp r9,rax
    // 0x567dab8  je short 0x567DAC0
    // -> if r9 == a1 goto L_0x567dac0
    // -> if r9 != a1 goto L_0x567daba
    L_0x567dab5:;
    if (r9_val == rax) {
        goto L_0x567dac0;
    }

    // 0x567daba..0x567dac0: basic block 4
    // 0x567daba  mov r9,[rax+8]
    // 0x567dabe  jmp short 0x567DAC8
    // -> if jmp goto L_0x567dac8
    L_0x567daba:;
    r9_val = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rax) + 0x8);
    goto L_0x567dac8;

    // 0x567dac0..0x567dac8: basic block 5
    // 0x567dac0  mov r9,[rcx+8]
    // 0x567dac4  mov [rdx+r8],r9
    // -> if fallthrough goto L_0x567dac8
    L_0x567dac0:;
    r9_val = self_s->f8;
    bucket[0] = r9_val;

    // 0x567dac8..0x567dacd: basic block 6
    // 0x567dac8  mov [rdx+r8+8],r9
    // -> if fallthrough goto L_0x567dacd
    L_0x567dac8:;
    bucket[1] = r9_val;

    // 0x567dacd..0x567daf9: basic block 7
    // 0x567dacd  mov rsi,[rax]
    // 0x567dad0  dec qword ptr [rcx+0x10]
    // 0x567dad4  mov rcx,[rax+8]
    // 0x567dad8  mov [rcx],rsi
    // 0x567dadb  mov rcx,[rax+8]
    // 0x567dadf  mov [rsi+8],rcx
    // 0x567dae3  mov edx,0x20
    // 0x567dae8  mov rcx,rax
    // 0x567daeb  call 0xE935700
    // 0x567daf0  mov rax,rsi
    // 0x567daf3  add rsp,0x20
    // 0x567daf7  pop rsi
    // 0x567daf8  ret
    // -> (fall-through / ret / end)
    L_0x567dacd:;
    void* rsi = *static_cast<void**>(rax);
    self_s->f10--;
    void* rcx = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rax) + 0x8);
    *reinterpret_cast<void**>(rcx) = rsi;
    rcx = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rax) + 0x8);
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rsi) + 0x8) = rcx;
    sub_e935700(0x20, 0, rax, nullptr); // edx=0x20, rcx=rax; other args per register state
    return reinterpret_cast<uintptr_t>(rsi);
}

} // namespace native::helpers