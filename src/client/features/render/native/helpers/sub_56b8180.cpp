// LIFT 0x56b8180 size 0xfc 1.26.62.01 sub_56b8180
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56b8180.h"

#include <cstdint>
#include <cstddef>
#include <emmintrin.h>
#include <intrin.h>

namespace native::helpers {

// sub_56b8180 (0x56b8180, size 0xfc, 1.26.62.01). x64 Microsoft ABI:
//   rcx = self (a0): a range object { entries begin@+0x0, entries end@+0x8, outer end@+0x10 }.
// Walks the entries [begin, end) with stride 0x118. For each entry whose flag byte at
// +0x100 equals 1, releases the inline buffer described by the entry (begin2@entry+0xe8,
// end2@entry+0xf8) via sub_e935700 (argument in rcx, result in rax), then zeroes the
// 16 bytes at entry+0xe8..+0xf8 and the qword at entry+0xf8. When the walk is exhausted
// (or when the entry range is empty), releases the outer range [begin, outer end) the
// same way and zeroes self+0x0..self+0x10. Returns the value sub_e935700 leaves in rax
// on the last release path (0 on the null-a0 path; RAX is unwritten there by the original).

// Verbatim call instructions from the disassembly of [0x56b8180, 0x56b827c) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x56b81b0  call 0xE935700
0x56b8240  call 0xE935700
0x56b8275  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x56b8180, 0x56b827c) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

static_assert(sizeof(std::uintptr_t) == 8, "56b8180: uintptr_t is 8 bytes on x64");

uintptr_t sub_56b8180(void* self) {
    // Locals mirror the register state. All are declared up front without
    // initializers so the block-to-block goto flow matches the CFG exactly.
    void** a0;
    void* rdi;
    void* rsi;
    void* rbx;
    __m128i xmm6;
    void** r14;
    void* rcx;
    void* rdx;
    void* rax;
    std::uintptr_t rdx_u;
    std::uintptr_t rcx_u;
    std::uintptr_t rdi_u;
    std::uintptr_t result;

    a0 = reinterpret_cast<void**>(self);

    // 0x56b8180..0x56b819a: basic block 0
    // 0x56b8180  push r14
    // 0x56b8182  push rsi
    // 0x56b8183  push rdi
    // 0x56b8184  push rbx
    // 0x56b8185  sub rsp,0x48
    // 0x56b8189  movaps [rsp+0x30],xmm6
    // 0x56b818e  mov rdi,[rcx]                                 ; R a0+0x0
    // 0x56b8191  test rdi,rdi
    // 0x56b8194  je 0x56B8253                                  ; -> if *(a0) == 0 goto L_0x56b8253
    // -> if *(a0) != 0 goto L_0x56b819a
    L_0x56b8180:;
    rdi = a0[0];
    if (rdi == nullptr) return 0;   // block 0 -> block 16 (rax is dead on this path; return 0)

    // 0x56b819a..0x56b81a6: basic block 1
    // 0x56b819a  mov rsi,rcx
    // 0x56b819d  mov rbx,[rcx+8]                               ; R a0+0x8
    // 0x56b81a1  cmp rdi,rbx
    // 0x56b81a4  je short 0x56B8215                            ; -> if *(a0) == *(a0+0x8) goto L_0x56b8215
    // -> if *(a0) != *(a0+0x8) goto L_0x56b81a6
    L_0x56b819a:;
    rsi = self;
    rbx = a0[1];
    if (rdi == rbx) goto L_0x56b8215;

    // 0x56b81a6..0x56b81ab: basic block 2
    // 0x56b81a6  xorps xmm6,xmm6
    // 0x56b81a9  jmp short 0x56B81CD                           ; -> if jmp goto L_0x56b81cd
    L_0x56b81a6:;
    xmm6 = _mm_setzero_si128();
    goto L_0x56b81cd;

    // 0x56b81ab..0x56b81b0: basic block 3
    // 0x56b81ab  nop [rax+rax]                                 ; -> if fallthrough goto L_0x56b81b0
    L_0x56b81ab:;
    goto L_0x56b81b0;

    // 0x56b81b0..0x56b81c1: basic block 4
    // 0x56b81b0  call 0xE935700                                ; -> sub_e935700 (rcx holds the argument)
    // 0x56b81b5  movups [r14],xmm6                             ; W r14+0x0 (16 bytes)
    // 0x56b81b9  mov qword ptr [r14+0x10],0                    ; W r14+0x10
    // -> if fallthrough goto L_0x56b81c1
    L_0x56b81b0:;
    result = reinterpret_cast<std::uintptr_t>(native::sub_e935700(rcx));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(r14), xmm6);
    *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<char*>(r14) + 0x10) = 0;
    goto L_0x56b81c1;

    // 0x56b81c1..0x56b81cd: basic block 5
    // 0x56b81c1  add rdi,0x118
    // 0x56b81c8  cmp rdi,rbx
    // 0x56b81cb  je short 0x56B8212                            ; -> if rdi == *(a0+0x8) goto L_0x56b8212
    // -> if rdi != *(a0+0x8) goto L_0x56b81cd
    L_0x56b81c1:;
    rdi = reinterpret_cast<char*>(rdi) + 0x118;
    if (rdi == rbx) goto L_0x56b8212;
    goto L_0x56b81cd;

    // 0x56b81cd..0x56b81d6: basic block 6
    // 0x56b81cd  cmp byte ptr [rdi+0x100],1                    ; R rdi+0x100
    // 0x56b81d4  jne short 0x56B81C1                           ; -> if *(rdi+0x100) != 0x1 goto L_0x56b81c1
    // -> if *(rdi+0x100) == 0x1 goto L_0x56b81d6
    L_0x56b81cd:;
    if (reinterpret_cast<std::uint8_t*>(rdi)[0x100] != 1) goto L_0x56b81c1;

    // 0x56b81d6..0x56b81e5: basic block 7
    // 0x56b81d6  lea r14,[rdi+0xE8]
    // 0x56b81dd  mov rcx,[r14]                                 ; R r14+0x0
    // 0x56b81e0  test rcx,rcx
    // 0x56b81e3  je short 0x56B81C1                            ; -> if rcx == 0 goto L_0x56b81c1
    // -> if rcx != 0 goto L_0x56b81e5
    L_0x56b81d6:;
    r14 = reinterpret_cast<void**>(reinterpret_cast<char*>(rdi) + 0xe8);
    rcx = *r14;
    if (rcx == nullptr) goto L_0x56b81c1;

    // 0x56b81e5..0x56b81f8: basic block 8
    // 0x56b81e5  mov rdx,[rdi+0xF8]                            ; R rdi+0xf8
    // 0x56b81ec  sub rdx,rcx
    // 0x56b81ef  cmp rdx,0x1000
    // 0x56b81f6  jb short 0x56B81B0                            ; -> if rdx-rcx <u 0x1000 goto L_0x56b81b0
    // -> if rdx-rcx >=u 0x1000 goto L_0x56b81f8
    L_0x56b81e5:;
    rdx = *reinterpret_cast<void**>(reinterpret_cast<char*>(rdi) + 0xf8);
    rdx_u = reinterpret_cast<std::uintptr_t>(rdx) - reinterpret_cast<std::uintptr_t>(rcx);
    if (rdx_u < 0x1000ull) goto L_0x56b81b0;

    // 0x56b81f8..0x56b8209: basic block 9
    // 0x56b81f8  mov rax,[rcx-8]                               ; R rcx-8
    // 0x56b81fc  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x56b8200  sub rcx,rax
    // 0x56b8203  cmp rcx,0x20
    // 0x56b8207  jae short 0x56B8262                           ; -> if rcx-8-*(rcx-8) >=u 0x20 goto L_0x56b8262
    // -> if rcx-8-*(rcx-8) <u 0x20 goto L_0x56b8209
    L_0x56b81f8:;
    rax = *reinterpret_cast<void**>(reinterpret_cast<char*>(rcx) - 8);
    rcx_u = reinterpret_cast<std::uintptr_t>(rcx) - 8 - reinterpret_cast<std::uintptr_t>(rax);
    if (rcx_u >= 0x20ull) goto L_0x56b8262;

    // 0x56b8209..0x56b8212: basic block 10
    // 0x56b8209  add rdx,0x27
    // 0x56b820d  mov rcx,rax
    // 0x56b8210  jmp short 0x56B81B0                           ; -> if jmp goto L_0x56b81b0
    L_0x56b8209:;
    rdx_u += 0x27;
    rcx = rax;
    goto L_0x56b81b0;

    // 0x56b8212..0x56b8215: basic block 11
    // 0x56b8212  mov rdi,[rsi]                                 ; R rsi+0x0
    // -> if fallthrough goto L_0x56b8215
    L_0x56b8212:;
    rdi = reinterpret_cast<void**>(rsi)[0];
    goto L_0x56b8215;

    // 0x56b8215..0x56b8225: basic block 12
    // 0x56b8215  mov rdx,[rsi+0x10]                            ; R rsi+0x10
    // 0x56b8219  sub rdx,rdi
    // 0x56b821c  cmp rdx,0x1000
    // 0x56b8223  jb short 0x56B823D                            ; -> if (rsi+0x10)-rdi <u 0x1000 goto L_0x56b823d
    // -> if (rsi+0x10)-rdi >=u 0x1000 goto L_0x56b8225
    L_0x56b8215:;
    rdx = *reinterpret_cast<void**>(reinterpret_cast<char*>(rsi) + 0x10);
    rdx_u = reinterpret_cast<std::uintptr_t>(rdx) - reinterpret_cast<std::uintptr_t>(rdi);
    if (rdx_u < 0x1000ull) goto L_0x56b823d;

    // 0x56b8225..0x56b8236: basic block 13
    // 0x56b8225  mov rax,[rdi-8]                               ; R rdi-8
    // 0x56b8229  add rdi,0xFFFFFFFFFFFFFFF8
    // 0x56b822d  sub rdi,rax
    // 0x56b8230  cmp rdi,0x20
    // 0x56b8234  jae short 0x56B8262                           ; -> if rdi-8-*(rdi-8) >=u 0x20 goto L_0x56b8262
    // -> if rdi-8-*(rdi-8) <u 0x20 goto L_0x56b8236
    L_0x56b8225:;
    rax = *reinterpret_cast<void**>(reinterpret_cast<char*>(rdi) - 8);
    rdi_u = reinterpret_cast<std::uintptr_t>(rdi) - 8 - reinterpret_cast<std::uintptr_t>(rax);
    if (rdi_u >= 0x20ull) goto L_0x56b8262;

    // 0x56b8236..0x56b823d: basic block 14
    // 0x56b8236  add rdx,0x27
    // 0x56b823a  mov rdi,rax
    // -> if fallthrough goto L_0x56b823d
    L_0x56b8236:;
    rdx_u += 0x27;
    rdi = rax;

    // 0x56b823d..0x56b8253: basic block 15
    // 0x56b823d  mov rcx,rdi
    // 0x56b8240  call 0xE935700                                ; -> sub_e935700 (rcx=rdi)
    // 0x56b8245  xorps xmm0,xmm0
    // 0x56b8248  movups [rsi],xmm0                             ; W rsi+0x0 (16 bytes)
    // 0x56b824b  mov qword ptr [rsi+0x10],0                    ; W rsi+0x10
    // -> if fallthrough goto L_0x56b8253
    L_0x56b823d:;
    rcx = rdi;
    result = reinterpret_cast<std::uintptr_t>(native::sub_e935700(rcx));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(rsi), _mm_setzero_si128());
    *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<char*>(rsi) + 0x10) = 0;
    goto L_0x56b8253;

    // 0x56b8253..0x56b8262: basic block 16
    // 0x56b8253  movaps xmm6,[rsp+0x30]                        ; R rsp+0x30 (register restore)
    // 0x56b8258  add rsp,0x48
    // 0x56b825c  pop rbx
    // 0x56b825d  pop rdi
    // 0x56b825e  pop rsi
    // 0x56b825f  pop r14
    // 0x56b8261  ret
    // -> (fall-through / ret / end)
    L_0x56b8253:;
    return result;

    // 0x56b8262..0x56b827c: basic block 17
    // 0x56b8262  mov qword ptr [rsp+0x20],0
    // 0x56b826b  xor ecx,ecx
    // 0x56b826d  xor edx,edx
    // 0x56b826f  xor r8d,r8d
    // 0x56b8272  xor r9d,r9d
    // 0x56b8275  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
    // 0x56b827b  int3   (noreturn; unreachable)
    // -> (fall-through / ret / end)
    L_0x56b8262:;
    {
        // The data slot at 0xF9A8C78 holds the invalid-parameter handler invoked on the
        // heap-corruption path (block 17). It is loader-patched at runtime; reading it via
        // imageBase + offset matches the disassembly's absolute address 0xF9A8C78.
        using Fn = void(__cdecl*)(void*, void*, void*, void*);
        reinterpret_cast<Fn>(*reinterpret_cast<std::uintptr_t*>(
            RewriteRegistry::imageBase() + 0xF9A8C78))(nullptr, nullptr, nullptr, nullptr);
    }
    // 0x56b827b  int3  (noreturn; unreachable)
    __assume(false);
}

LIFT_FN(sub_56b8180, "sub_56b8180", 0x56b8180, sub_56b8180, nullptr);

} // namespace native::helpers
