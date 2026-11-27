// LIFT 0x114360 size 0x115 1.26.62.01 sub_114360
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_114360.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_114360, "sub_114360", 0x114360, sub_114360, nullptr);

// 0xE951550 is the CRT __report_gsfailure boundary (docs/data/native_boundary.tsv).
// It returns nothing; the wrapper's result type is the register-wide value, ignored here.
Boundary<std::uintptr_t, std::uintptr_t> sub_e951550("sub_e951550");

// Layout assertions (mirrored from the header for liftcheck)
static_assert(offsetof(sub_114360_rsp, pivot_first) == 0x20, "sub_114360 rsp+0x20 pivot slot");
static_assert(offsetof(sub_114360_rsp, pivot_second) == 0x28, "sub_114360 rsp+0x28 pivot slot");
static_assert(offsetof(sub_114360_rsp, cookie) == 0x30, "sub_114360 rsp+0x30 cookie slot");
static_assert(sizeof(sub_114360_rsp) >= 0x38, "sub_114360 rsp size lower bound");

// Verbatim call instructions from the disassembly of [0x114360, 0x114475) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x114392  call 0x114480
0x1143b6  call 0x114360
0x1143dc  call 0x114910
0x11440f  call 0x114360
0x114421  call 0x1147E0
0x114436  call 0x1152E0
0x11446f  call 0xE951550
#endif

std::uintptr_t sub_114360(std::uint8_t* first, std::uint8_t* last, std::intptr_t ideal) {
    // 0x114360..0x11438c: prologue, stack cookie, small-range dispatch
    // 0x114360  push r14
    // 0x114362  push rsi
    // 0x114363  push rdi
    // 0x114364  push rbx
    // 0x114365  sub rsp,0x38
    // 0x114369  mov rsi,rdx
    // 0x11436c  mov rdi,rcx
    // 0x11436f  mov rax,[0x1230A0C0]
    // 0x114376  xor rax,rsp
    // 0x114379  mov [rsp+0x30],rax
    // 0x11437e  mov rax,rdx
    // 0x114381  sub rax,rcx
    // 0x114384  cmp rax,0x401
    // 0x11438a  jge short 0x11439C
    std::uint8_t* rsi = last;
    std::uint8_t* rdi = first;
    std::intptr_t rbx = ideal;
    std::uint8_t* pivot[2] = {nullptr, nullptr};   // [rsp+0x20], [rsp+0x28]
    std::uintptr_t cookie_stored = 0;              // [rsp+0x30]
    const std::uintptr_t rsp_proxy = reinterpret_cast<std::uintptr_t>(&cookie_stored);
    cookie_stored = __security_cookie ^ rsp_proxy;
    if (static_cast<std::ptrdiff_t>(rsi - rdi) < 0x401) goto L_0x11438c;

    // 0x11439c..0x1143a6: large-range entry, budget and pivot-slot address
    // 0x11439c  mov rbx,r8
    // 0x11439f  lea r14,[rsp+0x20]
    // 0x1143a4  jmp short 0x1143CE
    rbx = ideal;
    // 0x1143a6..0x1143b0: two-byte alignment filler
    // 0x1143a6  nop [rax+rax]
    goto L_0x1143ce;

L_0x11438c:
    // 0x11438c..0x114397: at most 32 records left, order them and leave
    // 0x11438c  mov rcx,rdi
    // 0x11438f  mov rdx,rsi
    // 0x114392  call 0x114480
    // 0x114397  jmp 0x114449
    sub_114480(rdi, rsi);
    goto L_0x114449;

L_0x1143b0:
    // 0x1143b0..0x1143c0: sort the upper half [pivot_second, rsi), continue on [rdi, pivot_first)
    // 0x1143b0  mov rdx,rsi
    // 0x1143b3  mov r8,rbx
    // 0x1143b6  call 0x114360
    // 0x1143bb  mov rsi,[rsp+0x20]
    sub_114360(pivot[1], rsi, rbx);
    rsi = pivot[0];

L_0x1143c0:
    // 0x1143c0..0x1143ce: loop tail, fall back to the small-range sort when <= 32 records remain
    // 0x1143c0  mov rax,rsi
    // 0x1143c3  sub rax,rdi
    // 0x1143c6  cmp rax,0x401
    // 0x1143cc  jl short 0x11438C
    if (static_cast<std::ptrdiff_t>(rsi - rdi) < 0x401) goto L_0x11438c;

L_0x1143ce:
    // 0x1143ce..0x1143d3: depth budget test
    // 0x1143ce  test rbx,rbx
    // 0x1143d1  jle short 0x11441B
    if (rbx <= 0) goto L_0x11441b;

    // 0x1143d3..0x114409: partition, cut the budget by a quarter, recurse into the smaller half
    // 0x1143d3  mov rcx,r14
    // 0x1143d6  mov rdx,rdi
    // 0x1143d9  mov r8,rsi
    // 0x1143dc  call 0x114910
    // 0x1143e1  mov rax,rbx
    // 0x1143e4  shr rax,1
    // 0x1143e7  shr rbx,2
    // 0x1143eb  add rbx,rax
    // 0x1143ee  mov rdx,[rsp+0x20]
    // 0x1143f3  mov rcx,[rsp+0x28]
    // 0x1143f8  mov rax,rdx
    // 0x1143fb  sub rax,rdi
    // 0x1143fe  mov r8,rsi
    // 0x114401  sub r8,rcx
    // 0x114404  cmp rax,r8
    // 0x114407  jge short 0x1143B0
    sub_114910(pivot, rdi, rsi);
    rbx = static_cast<std::intptr_t>((static_cast<std::uint64_t>(rbx) >> 1) +
                                     (static_cast<std::uint64_t>(rbx) >> 2));
    if (static_cast<std::ptrdiff_t>(pivot[0] - rdi) >=
        static_cast<std::ptrdiff_t>(rsi - pivot[1]))
        goto L_0x1143b0;

    // 0x114409..0x11441b: left half is the smaller one, sort it and loop on the right half
    // 0x114409  mov rcx,rdi
    // 0x11440c  mov r8,rbx
    // 0x11440f  call 0x114360
    // 0x114414  mov rdi,[rsp+0x28]
    // 0x114419  jmp short 0x1143C0
    sub_114360(rdi, pivot[0], rbx);
    rdi = pivot[1];
    goto L_0x1143c0;

L_0x11441b:
    // 0x11441b..0x114430: depth budget exhausted, build the heap over the whole range
    // 0x11441b  mov rcx,rdi
    // 0x11441e  mov rdx,rsi
    // 0x114421  call 0x1147E0
    // 0x114426  mov rbx,rsi
    // 0x114429  sub rbx,rdi
    // 0x11442c  nop [rax]
    sub_1147e0(rdi, rsi);
    rbx = static_cast<std::intptr_t>(rsi - rdi);

L_0x114430:
    // 0x114430..0x114449: pop the heap top and shrink the range by one 0x20-byte record
    // 0x114430  mov rcx,rdi
    // 0x114433  mov rdx,rsi
    // 0x114436  call 0x1152E0
    // 0x11443b  add rsi,0xFFFFFFFFFFFFFFE0
    // 0x11443f  add rbx,0xFFFFFFFFFFFFFFE0
    // 0x114443  cmp rbx,0x20
    // 0x114447  jg short 0x114430
    sub_1152e0(rdi, rsi);
    rsi -= 0x20;
    rbx -= 0x20;
    if (rbx > 0x20) goto L_0x114430;

L_0x114449:
    // 0x114449..0x11445d: stack cookie verification
    // 0x114449  mov rax,[rsp+0x30]
    // 0x11444e  xor rax,rsp
    // 0x114451  mov rcx,[0x1230A0C0]
    // 0x114458  cmp rcx,rax
    // 0x11445b  jne short 0x114467
    if (__security_cookie == (cookie_stored ^ rsp_proxy)) {
        // 0x11445d..0x114467: normal epilogue
        // 0x11445d  add rsp,0x38
        // 0x114461  pop rbx
        // 0x114462  pop rdi
        // 0x114463  pop rsi
        // 0x114464  pop r14
        // 0x114466  ret
        return cookie_stored ^ rsp_proxy;   // rax as left by 0x114449..0x11445b
    }

    // 0x114467..0x114475: cookie mismatch, report through the CRT boundary
    // 0x114467  mov rcx,[rsp+0x30]
    // 0x11446c  xor rcx,rsp
    // 0x11446f  call 0xE951550
    // 0x114474  int3
    sub_e951550(cookie_stored ^ rsp_proxy);
}

} // namespace native::helpers
