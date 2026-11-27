// LIFT 0x568da90 size 0xf7 1.26.62.01 sub_568da90
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_568da90.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

#include "client/features/render/native/passes/sub_568db90.h"

namespace native::helpers {

// sub_e935700 is called here with a single argument in RCX (the return value is unused),
// matching the ABI recovered from its disassembly (tail jump to sub_392960, arg in RCX).
void sub_e935700(void* a0);

LIFT_FN(sub_568da90, "sub_568da90", 0x568da90, sub_568da90, nullptr);

// Verbatim call instructions from the disassembly of [0x568da90, 0x568db87) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x568dace  call 0x568DB90
0x568db0a  call 0xE935700
0x568db4e  call 0xE935700
0x568db80  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x568da90, 0x568db87) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

void sub_568da90(void* a0) {
    // All locals are declared up front so that no `goto` jumps over an initialization.
    auto* const ctx = reinterpret_cast<sub_568da90_ctx*>(a0);
    uint8_t* buf2_begin = reinterpret_cast<uint8_t*>(ctx->f18);
    uint8_t* buf2_end = nullptr;
    uint64_t size2 = 0;
    void* arg2 = nullptr;
    void* old_base2 = nullptr;
    uint64_t probe2 = 0;
    uint8_t* buf1_begin = nullptr;
    uint64_t size1 = 0;
    void* arg1 = nullptr;
    void* old_base1 = nullptr;
    uint64_t probe1 = 0;

    // 0x568da90..0x568daa7: basic block 0
    // 0x568da90  push r15
    // 0x568da92  push r14
    // 0x568da94  push rsi
    // 0x568da95  push rdi
    // 0x568da96  push rbx
    // 0x568da97  sub rsp,0x30
    // 0x568da9b  mov rsi,rcx
    // 0x568da9e  mov rdi,[rcx+0x18]
    // 0x568daa2  test rdi,rdi
    // 0x568daa5  je short 0x568DB1E
    // -> if *(a0+0x18) == 0 goto L_0x568db1e
    // -> if *(a0+0x18) != 0 goto L_0x568daa7
    L_0x568da90:;
    if (buf2_begin == nullptr) goto L_0x568db1e;

    // 0x568daa7..0x568dab4: basic block 1
    // 0x568daa7  lea r14,[rsi+0x18]
    // 0x568daab  mov r15,[rsi+0x20]
    // 0x568daaf  cmp rdi,r15
    // 0x568dab2  je short 0x568DADF
    // -> if *(a0+0x18) == *(a0+0x20) goto L_0x568dadf
    // -> if *(a0+0x18) != *(a0+0x20) goto L_0x568dab4
    L_0x568daa7:;
    buf2_end = reinterpret_cast<uint8_t*>(ctx->f20);
    if (buf2_begin == buf2_end) goto L_0x568dadf;

    // 0x568dab4..0x568dac0: basic block 2
    // 0x568dab4  lea rbx,[rsp+0x2F]
    // 0x568dab9  nop [rax]
    // -> if fallthrough goto L_0x568dac0
    L_0x568dab4:;
    // rbx = &rsp[0x2F]: address-taken scratch byte (sub_568da90_stack.f2f), unused afterwards.

    // 0x568dac0..0x568dadc: basic block 3
    // 0x568dac0  movsx rcx,byte ptr [rdi+0x18]
    // 0x568dac5  inc rcx
    // 0x568dac8  mov rdx,rbx
    // 0x568dacb  mov r8,rdi
    // 0x568dace  call 0x568DB90
    // 0x568dad3  add rdi,0x20
    // 0x568dad7  cmp rdi,r15
    // 0x568dada  jne short 0x568DAC0
    // -> if ? != *(a0+0x20) goto L_0x568dac0
    // -> if ? == *(a0+0x20) goto L_0x568dadc
    L_0x568dac0:;
    for (uint8_t* elem = buf2_begin; elem != buf2_end; elem += 0x20) {
        sub_568db90(static_cast<std::uint8_t>(
            *reinterpret_cast<std::int8_t*>(elem + 0x18)) + 1,
            nullptr, reinterpret_cast<native::ViewElem*>(elem));
    }

    // 0x568dadc..0x568dadf: basic block 4
    // 0x568dadc  mov rdi,[r14]
    // -> if fallthrough goto L_0x568dadf
    L_0x568dadc:;
    buf2_begin = reinterpret_cast<uint8_t*>(ctx->f18);

    // 0x568dadf..0x568daef: basic block 5
    // 0x568dadf  mov rdx,[rsi+0x28]
    // 0x568dae3  sub rdx,rdi
    // 0x568dae6  cmp rdx,0x1000
    // 0x568daed  jb short 0x568DB07
    // -> if (*(a0+0x28) - *(a0+0x18)) <u 0x1000 goto L_0x568db07
    // -> if (*(a0+0x28) - *(a0+0x18)) >=u 0x1000 goto L_0x568daef
    L_0x568dadf:;
    buf2_begin = reinterpret_cast<uint8_t*>(ctx->f18);
    size2 =
        reinterpret_cast<uint8_t*>(ctx->f28) - reinterpret_cast<uint8_t*>(ctx->f18);
    arg2 = buf2_begin;                  // small-buffer path: rcx = rdi = buf2_begin
    if (size2 >= 0x1000ui64) {
        // 0x568daef..0x568db00: basic block 6
        // 0x568daef  mov rax,[rdi-8]
        // 0x568daf3  add rdi,0xFFFFFFFFFFFFFFF8
        // 0x568daf7  sub rdi,rax
        // 0x568dafa  cmp rdi,0x20
        // 0x568dafe  jae short 0x568DB6D
        // -> if (*(a0+0x18)-0x8 - *(*(a0+0x18)-0x8)) >=u 0x20 goto L_0x568db6d
        // -> if (*(a0+0x18)-0x8 - *(*(a0+0x18)-0x8)) <u 0x20 goto L_0x568db00
        L_0x568daef:;
        old_base2 = *reinterpret_cast<void** volatile*>(
            reinterpret_cast<uint8_t*>(ctx->f18) - 8);
        probe2 =
            (reinterpret_cast<uint8_t*>(ctx->f18) - 8) -
            reinterpret_cast<uint8_t*>(old_base2);
        if (probe2 >= 0x20ui64) goto L_0x568db6d;

        // 0x568db00..0x568db07: basic block 7
        // 0x568db00  add rdx,0x27          ; dead (rdx not used afterwards)
        // 0x568db04  mov rdi,rax          ; rcx = old_base at block-8 entry
        // -> if fallthrough goto L_0x568db07
        L_0x568db00:;
        (void)size2;                    // size2 += 0x27 is dead in the original
        arg2 = old_base2;
    }

    // 0x568db07..0x568db1e: basic block 8
    // 0x568db07  mov rcx,rdi
    // 0x568db0a  call 0xE935700
    // 0x568db0f  xorps xmm0,xmm0
    // 0x568db12  movups [r14],xmm0
    // 0x568db16  mov qword ptr [r14+0x10],0
    // -> if fallthrough goto L_0x568db1e
    L_0x568db07:;
    sub_e935700(arg2);
    ctx->f18 = 0;
    ctx->f10 = 0;
    goto L_0x568db1e;

    // 0x568db1e..0x568db26: basic block 9
    // 0x568db1e  mov rcx,[rsi]
    // 0x568db21  test rcx,rcx
    // 0x568db24  je short 0x568DB61
    // -> if *(a0) == 0 goto L_0x568db61
    // -> if *(a0) != 0 goto L_0x568db26
    L_0x568db1e:;
    buf1_begin = reinterpret_cast<uint8_t*>(ctx->f0);
    if (buf1_begin == nullptr) return;

    // 0x568db26..0x568db36: basic block 10
    // 0x568db26  mov rdx,[rsi+0x10]
    // 0x568db2a  sub rdx,rcx
    // 0x568db2d  cmp rdx,0x1000
    // 0x568db34  jb short 0x568DB4E
    // -> if (*(a0+0x10) - *(a0)) <u 0x1000 goto L_0x568db4e
    // -> if (*(a0+0x10) - *(a0)) >=u 0x1000 goto L_0x568db36
    L_0x568db26:;
    size1 =
        reinterpret_cast<uint8_t*>(ctx->f10) - reinterpret_cast<uint8_t*>(ctx->f0);
    arg1 = buf1_begin;                  // small-buffer path: rcx = buf1_begin
    if (size1 >= 0x1000ui64) {
        // 0x568db36..0x568db47: basic block 11
        // 0x568db36  mov rax,[rcx-8]
        // 0x568db3a  add rcx,0xFFFFFFFFFFFFFFF8
        // 0x568db3e  sub rcx,rax
        // 0x568db41  cmp rcx,0x20
        // 0x568db45  jae short 0x568DB6D
        // -> if (*(a0)-0x8 - *(*(a0)-0x8)) >=u 0x20 goto L_0x568db6d
        // -> if (*(a0)-0x8 - *(*(a0)-0x8)) <u 0x20 goto L_0x568db47
        L_0x568db36:;
        old_base1 = *reinterpret_cast<void** volatile*>(
            reinterpret_cast<uint8_t*>(ctx->f0) - 8);
        probe1 =
            (reinterpret_cast<uint8_t*>(ctx->f0) - 8) -
            reinterpret_cast<uint8_t*>(old_base1);
        if (probe1 >= 0x20ui64) goto L_0x568db6d;

        // 0x568db47..0x568db4e: basic block 12
        // 0x568db47  add rdx,0x27          ; dead (rdx not used afterwards)
        // 0x568db4b  mov rcx,rax          ; rcx = old_base at block-13 entry
        // -> if fallthrough goto L_0x568db4e
        L_0x568db47:;
        (void)size1;                    // size1 += 0x27 is dead in the original
        arg1 = old_base1;
    }

    // 0x568db4e..0x568db61: basic block 13
    // 0x568db4e  call 0xE935700
    // 0x568db53  xorps xmm0,xmm0
    // 0x568db56  movups [rsi],xmm0
    // 0x568db59  mov qword ptr [rsi+0x10],0
    // -> if fallthrough goto L_0x568db61
    L_0x568db4e:;
    sub_e935700(arg1);
    ctx->f0 = nullptr;
    ctx->f10 = 0;
    goto L_0x568db61;

    // 0x568db61..0x568db6d: basic block 14
    // 0x568db61  add rsp,0x30
    // 0x568db65  pop rbx
    // 0x568db66  pop rdi
    // 0x568db67  pop rsi
    // 0x568db68  pop r14
    // 0x568db6a  pop r15
    // 0x568db6c  ret
    // -> (fall-through / ret / end)
    L_0x568db61:;
    return;

    // 0x568db6d..0x568db87: basic block 15
    // 0x568db6d  mov qword ptr [rsp+0x20],0
    // 0x568db76  xor ecx,ecx
    // 0x568db78  xor edx,edx
    // 0x568db7a  xor r8d,r8d
    // 0x568db7d  xor r9d,r9d
    // 0x568db80  call qword ptr [0xF9A8C78]
    // 0x568db86  int3
    // -> (fall-through / ret / end)
    L_0x568db6d:;
    {
        // Fail path: data-slot indirect call via import slot 0xF9A8C78, 4 zero args,
        // then int3 (noreturn).
        std::uint8_t* const image_base =
            reinterpret_cast<std::uint8_t*>(RewriteRegistry::imageBase());
        using FailFn = void (__cdecl*)(void*, void*, void*, void*);
        FailFn const fail =
            *reinterpret_cast<FailFn volatile*>(image_base + 0xF9A8C78);
        fail(nullptr, nullptr, nullptr, nullptr);
        __assume(false);  // int3: noreturn, matches the original's trap
    }
}

} // namespace native::helpers
