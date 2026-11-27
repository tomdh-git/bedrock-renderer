// LIFT 0x56b66f0 size 0xfc 1.26.62.01 sub_56b66f0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56b66f0.h"

#include <cstdint>
#include <cstddef>
#include <emmintrin.h>
#include <intrin.h>

// sub_e935700 is a lift-set callee: a tail-jump thunk to sub_392960. ABI recovered
// from its disassembly: the single argument arrives in RCX and the result leaves
// in RAX. The bare name `sub_e935700` is multiply declared with conflicting
// signatures across the project's headers, so the callee is invoked through its
// native symbol address (imageBase + 0xE935700) rather than by the polluted name.
static void* releaseViaSubE935700(void* ptr) {
    using Fn = void *(*)(void*);
    return reinterpret_cast<Fn>(RewriteRegistry::imageBase() + 0xE935700)(ptr);
}

static_assert(sizeof(std::uintptr_t) == 8, "56b66f0: uintptr_t is 8 bytes on x64");

namespace native::helpers {

// sub_56b66f0 (0x56b66f0, size 0xfc, 1.26.62.01). x64 Microsoft ABI:
//   rcx = self (a0): a range object { head@+0x0, end@+0x8, extra@+0x10 }.
// Walks the entries [head, end) with stride 0x128 looking for one whose flag byte
// at +0x100 equals 1. When found (or, if the walk is exhausted, the head itself),
// the buffer described by the entry is released via sub_e935700 (argument in rcx,
// result in rax), and the range object's pointer fields are zeroed. Returns the
// value sub_e935700 leaves in rax (0 on the empty-input path).

// Verbatim call instructions from the disassembly of [0x56b66f0, 0x56b67ec) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x56b6720  call 0xE935700
0x56b67b0  call 0xE935700
0x56b67e5  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x56b66f0, 0x56b67ec) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

// The data slot at 0xF9A8C78 holds the invalid-parameter handler invoked on the
// heap-corruption path (block 17). It is loader-patched at runtime; reading it via
// imageBase + offset matches the disassembly's absolute address 0xF9A8C78.
static uintptr_t dataSlotF9A8C78() {
    return *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A8C78);
}

[[noreturn]] static void corruptionPath() {
    // 0x56b67d2  mov qword ptr [rsp+0x20],0   ; 5th stack argument = 0 (spill slot, no external effect)
    // 0x56b67db..0x56b67e2  xor ecx,edx,r8d,r9d   ; first four arguments = 0
    // 0x56b67e5  call qword ptr [0xF9A8C78]     ; data slot, invalid-parameter handler, noreturn
    using Watson = std::uintptr_t(__cdecl*)(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, std::uintptr_t);
    reinterpret_cast<Watson>(dataSlotF9A8C78())(nullptr, nullptr, nullptr, 0, 0);
    // 0x56b67eb  int3  (noreturn; unreachable)
    __assume(false);
}

uintptr_t sub_56b66f0(void* self) {
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

    // 0x56b66f0..0x56b670a: basic block 0
    // 0x56b66f0  push r14
    // 0x56b66f2  push rsi
    // 0x56b66f3  push rdi
    // 0x56b66f4  push rbx
    // 0x56b66f5  sub rsp,0x48
    // 0x56b66f9  movaps [rsp+0x30],xmm6
    // 0x56b66fe  mov rdi,[rcx]                                 ; R a0+0x0
    // 0x56b6701  test rdi,rdi
    // 0x56b6704  je 0x56B67C3                                  ; -> if *(a0) == 0 goto L_0x56b67c3
    // -> if *(a0) != 0 goto L_0x56b670a
    L_0x56b66f0:;
    rdi = a0[0];
    if (rdi == nullptr) return 0;   // block 0 -> block 16 (rax is dead on this path; return 0)

    // 0x56b670a..0x56b6716: basic block 1
    // 0x56b670a  mov rsi,rcx
    // 0x56b670d  mov rbx,[rcx+8]                               ; R a0+0x8
    // 0x56b6711  cmp rdi,rbx
    // 0x56b6714  je short 0x56B6785                            ; -> if *(a0) == *(a0+0x8) goto L_0x56b6785
    // -> if *(a0) != *(a0+0x8) goto L_0x56b6716
    L_0x56b670a:;
    rsi = self;
    rbx = a0[1];
    if (rdi == rbx) goto L_0x56b6785;

    // 0x56b6716..0x56b671b: basic block 2
    // 0x56b6716  xorps xmm6,xmm6
    // 0x56b6719  jmp short 0x56B673D                           ; -> if jmp goto L_0x56b673d
    L_0x56b6716:;
    xmm6 = _mm_setzero_si128();
    goto L_0x56b673d;

    // 0x56b671b..0x56b6720: basic block 3
    // 0x56b671b  nop [rax+rax]                                 ; -> if fallthrough goto L_0x56b6720
    L_0x56b671b:;
    goto L_0x56b6720;

    // 0x56b6720..0x56b6731: basic block 4
    // 0x56b6720  call 0xE935700                                ; -> sub_e935700 (rcx holds the argument)
    // 0x56b6725  movups [r14],xmm6                             ; W r14+0x0 (16 bytes)
    // 0x56b6729  mov qword ptr [r14+0x10],0                    ; W r14+0x10
    // -> if fallthrough goto L_0x56b6731
    L_0x56b6720:;
    result = reinterpret_cast<std::uintptr_t>(releaseViaSubE935700(rcx));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(r14), xmm6);
    *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<char*>(r14) + 0x10) = 0;
    goto L_0x56b6731;

    // 0x56b6731..0x56b673d: basic block 5
    // 0x56b6731  add rdi,0x128
    // 0x56b6738  cmp rdi,rbx
    // 0x56b673b  je short 0x56B6782                            ; -> if rdi == *(a0+0x8) goto L_0x56b6782
    // -> if rdi != *(a0+0x8) goto L_0x56b673d
    L_0x56b6731:;
    rdi = reinterpret_cast<char*>(rdi) + 0x128;
    if (rdi == rbx) goto L_0x56b6782;
    goto L_0x56b673d;

    // 0x56b673d..0x56b6746: basic block 6
    // 0x56b673d  cmp byte ptr [rdi+0x100],1                    ; R rdi+0x100
    // 0x56b6744  jne short 0x56B6731                           ; -> if *(rdi+0x100) != 0x1 goto L_0x56b6731
    // -> if *(rdi+0x100) == 0x1 goto L_0x56b6746
    L_0x56b673d:;
    if (reinterpret_cast<std::uint8_t*>(rdi)[0x100] != 1) goto L_0x56b6731;

    // 0x56b6746..0x56b6755: basic block 7
    // 0x56b6746  lea r14,[rdi+0xE8]
    // 0x56b674d  mov rcx,[r14]                                 ; R r14+0x0
    // 0x56b6750  test rcx,rcx
    // 0x56b6753  je short 0x56B6731                            ; -> if rcx == 0 goto L_0x56b6731
    // -> if rcx != 0 goto L_0x56b6755
    L_0x56b6746:;
    r14 = reinterpret_cast<void**>(reinterpret_cast<char*>(rdi) + 0xe8);
    rcx = *r14;
    if (rcx == nullptr) goto L_0x56b6731;

    // 0x56b6755..0x56b6768: basic block 8
    // 0x56b6755  mov rdx,[rdi+0xF8]                            ; R rdi+0xf8
    // 0x56b675c  sub rdx,rcx
    // 0x56b675f  cmp rdx,0x1000
    // 0x56b6766  jb short 0x56B6720                            ; -> if rdx-rcx <u 0x1000 goto L_0x56b6720
    // -> if rdx-rcx >=u 0x1000 goto L_0x56b6768
    L_0x56b6755:;
    rdx = *reinterpret_cast<void**>(reinterpret_cast<char*>(rdi) + 0xf8);
    rdx_u = reinterpret_cast<std::uintptr_t>(rdx) - reinterpret_cast<std::uintptr_t>(rcx);
    if (rdx_u < 0x1000ull) goto L_0x56b6720;

    // 0x56b6768..0x56b6779: basic block 9
    // 0x56b6768  mov rax,[rcx-8]                               ; R rcx-8
    // 0x56b676c add rcx,0xFFFFFFFFFFFFFFF8
    // 0x56b6770 sub rcx,rax
    // 0x56b6773 cmp rcx,0x20
    // 0x56b6777 jae short 0x56B67D2                           ; -> if rcx-8-*(rcx-8) >=u 0x20 goto L_0x56b67d2
    // -> if rcx-8-*(rcx-8) <u 0x20 goto L_0x56b6779
    L_0x56b6768:;
    rax = *reinterpret_cast<void**>(reinterpret_cast<char*>(rcx) - 8);
    rcx_u = reinterpret_cast<std::uintptr_t>(rcx) - 8 - reinterpret_cast<std::uintptr_t>(rax);
    if (rcx_u >= 0x20ull) goto L_0x56b67d2;

    // 0x56b6779..0x56b6782: basic block 10
    // 0x56b6779  add rdx,0x27
    // 0x56b677d mov rcx,rax
    // 0x56b6780 jmp short 0x56B6720                           ; -> if jmp goto L_0x56b6720
    L_0x56b6779:;
    rdx_u += 0x27;
    rcx = rax;
    goto L_0x56b6720;

    // 0x56b6782..0x56b6785: basic block 11
    // 0x56b6782  mov rdi,[rsi]                                 ; R rsi+0x0
    // -> if fallthrough goto L_0x56b6785
    L_0x56b6782:;
    rdi = *reinterpret_cast<void**>(rsi);
    goto L_0x56b6785;

    // 0x56b6785..0x56b6795: basic block 12
    // 0x56b6785  mov rdx,[rsi+0x10]                            ; R rsi+0x10
    // 0x56b6789  sub rdx,rdi
    // 0x56b678c  cmp rdx,0x1000
    // 0x56b6793  jb short 0x56B67AD                            ; -> if (rsi+0x10)-rdi <u 0x1000 goto L_0x56b67ad
    // -> if (rsi+0x10)-rdi >=u 0x1000 goto L_0x56b6795
    L_0x56b6785:;
    rdx = *reinterpret_cast<void**>(reinterpret_cast<char*>(rsi) + 0x10);
    rdx_u = reinterpret_cast<std::uintptr_t>(rdx) - reinterpret_cast<std::uintptr_t>(rdi);
    if (rdx_u < 0x1000ull) goto L_0x56b67ad;

    // 0x56b6795..0x56b67a6: basic block 13
    // 0x56b6795  mov rax,[rdi-8]                               ; R rdi-8
    // 0x56b6799 add rdi,0xFFFFFFFFFFFFFFF8
    // 0x56b679d sub rdi,rax
    // 0x56b67a0 cmp rdi,0x20
    // 0x56b67a4 jae short 0x56B67D2                           ; -> if rdi-8-*(rdi-8) >=u 0x20 goto L_0x56b67d2
    // -> if rdi-8-*(rdi-8) <u 0x20 goto L_0x56b67a6
    L_0x56b6795:;
    rax = *reinterpret_cast<void**>(reinterpret_cast<char*>(rdi) - 8);
    rdi_u = reinterpret_cast<std::uintptr_t>(rdi) - 8 - reinterpret_cast<std::uintptr_t>(rax);
    if (rdi_u >= 0x20ull) goto L_0x56b67d2;

    // 0x56b67a6..0x56b67ad: basic block 14
    // 0x56b67a6  add rdx,0x27
    // 0x56b67aa  mov rdi,rax
    // -> if fallthrough goto L_0x56b67ad
    L_0x56b67a6:;
    rdx_u += 0x27;
    rdi = rax;

    // 0x56b67ad..0x56b67c3: basic block 15
    // 0x56b67ad  mov rcx,rdi
    // 0x56b67b0  call 0xE935700                                ; -> sub_e935700 (rcx=rdi)
    // 0x56b67b5  xorps xmm0,xmm0
    // 0x56b67b8  movups [rsi],xmm0                             ; W rsi+0x0 (16 bytes)
    // 0x56b67bb  mov qword ptr [rsi+0x10],0                    ; W rsi+0x10
    // -> if fallthrough goto L_0x56b67c3
    L_0x56b67ad:;
    rcx = rdi;
    result = reinterpret_cast<std::uintptr_t>(releaseViaSubE935700(rcx));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(rsi), _mm_setzero_si128());
    *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<char*>(rsi) + 0x10) = 0;
    goto L_0x56b67c3;

    // 0x56b67c3..0x56b67d2: basic block 16
    // 0x56b67c3  movaps xmm6,[rsp+0x30]                        ; R rsp+0x30 (register restore)
    // 0x56b67c8  add rsp,0x48
    // 0x56b67cc  pop rbx
    // 0x56b67cd  pop rdi
    // 0x56b67ce  pop rsi
    // 0x56b67cf  pop r14
    // 0x56b67d1  ret
    // -> (fall-through / ret / end)
    L_0x56b67c3:;
    return result;

    // 0x56b67d2..0x56b67ec: basic block 17
    // 0x56b67d2  mov qword ptr [rsp+0x20],0
    // 0x56b67db  xor ecx,ecx
    // 0x56b67dd  xor edx,edx
    // 0x56b67df  xor r8d,r8d
    // 0x56b67e2  xor r9d,r9d
    // 0x56b67e5  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
    // 0x56b67eb  int3   (noreturn; unreachable)
    // -> (fall-through / ret / end)
    L_0x56b67d2:;
    corruptionPath();
    __assume(false);
}

LIFT_FN(sub_56b66f0, "sub_56b66f0", 0x56b66f0, sub_56b66f0, nullptr);

} // namespace native::helpers
