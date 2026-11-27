// LIFT 0x56d03a0 size 0x12a 1.26.62.01 sub_56d03a0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_56d03a0.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_56d03a0, "sub_56d03a0", 0x56d03a0, sub_56d03a0, nullptr);

// Verbatim call instructions from the disassembly of [0x56d03a0, 0x56d04ca) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x56d03e8  call 0xE935700
0x56d042a  call qword ptr [0xF99FFA0]
0x56d0458  call 0x655CEA0
0x56d0492  call 0xE935700
0x56d04c3  call qword ptr [0xF9A8C78]
#endif

// Layout assertions mirroring the header so liftcheck finds them in source.
static_assert(offsetof(sub_56d03a0_rcx, f0) == 0x0, "sub_0x56d03a0 rcx+0x0 field");
static_assert(offsetof(sub_56d03a0_rcx, f10) == 0x10, "sub_0x56d03a0 rcx+0x10 field");
static_assert(offsetof(sub_56d03a0_rcx, f18) == 0x18, "sub_0x56d03a0 rcx+0x18 field");
static_assert(offsetof(sub_56d03a0_rcx, f20) == 0x20, "sub_0x56d03a0 rcx+0x20 field");
static_assert(offsetof(sub_56d03a0_rcx, f68) == 0x68, "sub_0x56d03a0 rcx+0x68 field");
static_assert(offsetof(sub_56d03a0_rcx, f90) == 0x90, "sub_0x56d03a0 rcx+0x90 field");
static_assert(offsetof(sub_56d03a0_rcx, fc8) == 0xc8, "sub_0x56d03a0 rcx+0xc8 field");
static_assert(offsetof(sub_56d03a0_rcx, fd8) == 0xd8, "sub_0x56d03a0 rcx+0xd8 field");
static_assert(offsetof(sub_56d03a0_rcx, fe8) == 0xe8, "sub_0x56d03a0 rcx+0xe8 field");
static_assert(offsetof(sub_56d03a0_rcx, ff0) == 0xf0, "sub_0x56d03a0 rcx+0xf0 field");
static_assert(sizeof(sub_56d03a0_rcx) >= 0xf8, "sub_0x56d03a0 rcx sizeof lower bound");

static_assert(offsetof(sub_56d03a0_r8, f0) == 0x0, "sub_0x56d03a0 r8+0x0 field");
static_assert(sizeof(sub_56d03a0_r8) >= 0x8, "sub_0x56d03a0 r8 sizeof lower bound");

static_assert(offsetof(sub_56d03a0_rax, f0) == 0x0, "sub_0x56d03a0 rax+0x0 field");
static_assert(offsetof(sub_56d03a0_rax, f10) == 0x10, "sub_0x56d03a0 rax+0x10 field");
static_assert(offsetof(sub_56d03a0_rax, f20) == 0x20, "sub_0x56d03a0 rax+0x20 field");
static_assert(sizeof(sub_56d03a0_rax) >= 0x28, "sub_0x56d03a0 rax sizeof lower bound");

static_assert(offsetof(sub_56d03a0_rsp, f20) == 0x20, "sub_0x56d03a0 rsp+0x20 field");
static_assert(sizeof(sub_56d03a0_rsp) >= 0x28, "sub_0x56d03a0 rsp sizeof lower bound");

std::uintptr_t sub_56d03a0(void* self) {
    auto* a0 = static_cast<sub_56d03a0_rcx*>(self);

    // Register values tracked across blocks (x64 ABI scratch registers).
    std::uint64_t rax = 0;
    std::uint64_t rcx = 0;
    std::uint64_t rdx = 0;
    std::uint64_t r8 = 0;

    // 0x56d03a0..0x56d03b5: basic block 0
    // 0x56d03a0  push rsi
    // 0x56d03a1  sub rsp,0x30
    // 0x56d03a5  mov rsi,rcx
    // 0x56d03a8  mov rax,[rcx+0xF0]
    // 0x56d03af  cmp rax,0x10
    // 0x56d03b3  jb short 0x56D03ED   -> if a0->ff0 <u 0x10 goto L_0x56d03ed
    //            -> if a0->ff0 >=u 0x10 goto L_0x56d03b5
    L_0x56d03a0:;
    rax = a0->ff0;
    if (rax < 0x10ULL) goto L_0x56d03ed;
    goto L_0x56d03b5;

    // 0x56d03b5..0x56d03c9: basic block 1
    // 0x56d03b5  mov rcx,[rsi+0xD8]
    // 0x56d03bc  lea rdx,[rax+1]
    // 0x56d03c0  cmp rdx,0x1000
    // 0x56d03c7  jb short 0x56D03E8   -> if a0->ff0+1 <u 0x1000 goto L_0x56d03e8
    //            -> if a0->ff0+1 >=u 0x1000 goto L_0x56d03c9
    L_0x56d03b5:;
    rcx = reinterpret_cast<std::uint64_t>(a0->fd8);
    rdx = rax + 1;
    if (rdx < 0x1000ULL) goto L_0x56d03e8;
    goto L_0x56d03c9;

    // 0x56d03c9..0x56d03de: basic block 2
    // 0x56d03c9  mov r8,[rcx-8]
    // 0x56d03cd  add rcx,0xFFFFFFFFFFFFFFF8   (rcx -= 8)
    // 0x56d03d1  sub rcx,r8
    // 0x56d03d4  cmp rcx,0x20
    // 0x56d03d8  jae 0x56D04B0          -> if (a0->fd8 - 8 - *(a0->fd8-8)) >=u 0x20 goto L_0x56d04b0
    //            -> if <u 0x20 goto L_0x56d03de
    L_0x56d03c9:;
    r8 = *reinterpret_cast<const std::uint64_t*>(rcx - 8);
    rcx = rcx - 8;
    rcx = rcx - r8;
    if (rcx >= 0x20ULL) goto L_0x56d04b0;
    goto L_0x56d03de;

    // 0x56d03de..0x56d03e8: basic block 3
    // 0x56d03de  add rax,0x28
    // 0x56d03e2  mov rdx,rax
    // 0x56d03e5  mov rcx,r8
    //            -> fallthrough goto L_0x56d03e8
    L_0x56d03de:;
    rax = rax + 0x28;
    rdx = rax;
    rcx = r8;
    goto L_0x56d03e8;

    // 0x56d03e8..0x56d03ed: basic block 4
    // 0x56d03e8  call 0xE935700         sub_e935700(rcx, rdx, r8, r9)
    //            -> fallthrough goto L_0x56d03ed
    L_0x56d03e8:;
    rax = sub_e935700(rcx, rdx, r8, 0);
    goto L_0x56d03ed;

    // 0x56d03ed..0x56d0416: basic block 5
    // 0x56d03ed  mov qword ptr [rsi+0xE8],0
    // 0x56d03f8  mov qword ptr [rsi+0xF0],0xF
    // 0x56d0403  mov byte ptr [rsi+0xD8],0
    // 0x56d040a  mov rcx,[rsi+0xC8]
    // 0x56d0411  test rcx,rcx
    // 0x56d0414  je short 0x56D043B     -> if a0->fc8 == 0 goto L_0x56d043b
    //            -> if a0->fc8 != 0 goto L_0x56d0416
    L_0x56d03ed:;
    a0->fe8 = 0;
    a0->ff0 = 0xF;
    *reinterpret_cast<std::uint8_t*>(&a0->fd8) = 0;
    rcx = reinterpret_cast<std::uint64_t>(a0->fc8);
    if (rcx == 0) goto L_0x56d043b;
    goto L_0x56d0416;

    // 0x56d0416..0x56d043b: basic block 6
    // 0x56d0416  lea rax,[rsi+0x90]     (dead: address only, no value read)
    // 0x56d041d  cmp rcx,rax            (dead)
    // 0x56d0420  setne dl               (dead)
    // 0x56d0423  mov rax,[rcx]
    // 0x56d0426  mov rax,[rax+0x20]     (dead loads, results unused)
    // 0x56d042a  call qword ptr [0xF99FFA0]  sub_eea6040(a0->fc8)
    // 0x56d0430  mov qword ptr [rsi+0xC8],0
    //            -> fallthrough goto L_0x56d043b
    L_0x56d0416:;
    sub_eea6040(reinterpret_cast<void*>(rcx));
    a0->fc8 = nullptr;
    goto L_0x56d043b;

    // 0x56d043b..0x56d0446: basic block 7
    // 0x56d043b  lea rcx,[rsi+0x20]     rcx = &a0->f20
    // 0x56d043f  cmp qword ptr [rsi+0x68],0
    // 0x56d0444  je short 0x56D0458     -> if a0->f68 == 0 goto L_0x56d0458
    //            -> if a0->f68 != 0 goto L_0x56d0446
    L_0x56d043b:;
    rcx = reinterpret_cast<std::uint64_t>(&a0->f20);
    if (a0->f68 == 0) goto L_0x56d0458;
    goto L_0x56d0446;

    // 0x56d0446..0x56d0458: basic block 8
    // 0x56d0446  lea rax,[rsi+0x68]     rax = &a0->f68
    // 0x56d044a  xorps xmm0,xmm0
    // 0x56d044d  movups [rax],xmm0      zero 16 bytes at &a0->f68
    // 0x56d0450  mov qword ptr [rax+0x10],0   zero 8 bytes at &a0->f68+0x10
    //            -> fallthrough goto L_0x56d0458
    L_0x56d0446:; {
        std::uint64_t* f68p = reinterpret_cast<std::uint64_t*>(&a0->f68);
        f68p[0] = 0;
        f68p[1] = 0;
        f68p[2] = 0;
    }
    goto L_0x56d0458;

    // 0x56d0458..0x56d0467: basic block 9
    // 0x56d0458  call 0x655CEA0         sub_655cea0(&a0->f20)
    // 0x56d045d  mov rax,[rsi+0x18]
    // 0x56d0461  cmp rax,0x10
    // 0x56d0465  jb short 0x56D0497     -> if a0->f18 <u 0x10 goto L_0x56d0497
    //            -> if a0->f18 >=u 0x10 goto L_0x56d0467
    L_0x56d0458:;
    sub_655cea0(reinterpret_cast<void*>(rcx));
    rax = a0->f18;
    if (rax < 0x10ULL) goto L_0x56d0497;
    goto L_0x56d0467;

    // 0x56d0467..0x56d0477: basic block 10
    // 0x56d0467  mov rcx,[rsi]
    // 0x56d046a  lea rdx,[rax+1]
    // 0x56d046e  cmp rdx,0x1000
    // 0x56d0475  jb short 0x56D0492     -> if a0->f18+1 <u 0x1000 goto L_0x56d0492
    //            -> if a0->f18+1 >=u 0x1000 goto L_0x56d0477
    L_0x56d0467:;
    rcx = reinterpret_cast<std::uint64_t>(a0->f0);
    rdx = rax + 1;
    if (rdx < 0x1000ULL) goto L_0x56d0492;
    goto L_0x56d0477;

    // 0x56d0477..0x56d0488: basic block 11
    // 0x56d0477  mov r8,[rcx-8]
    // 0x56d047b  add rcx,0xFFFFFFFFFFFFFFF8   (rcx -= 8)
    // 0x56d047f  sub rcx,r8
    // 0x56d0482  cmp rcx,0x20
    // 0x56d0486  jae short 0x56D04B0    -> if (a0->f0 - 8 - *(a0->f0-8)) >=u 0x20 goto L_0x56d04b0
    //            -> if <u 0x20 goto L_0x56d0488
    L_0x56d0477:;
    r8 = *reinterpret_cast<const std::uint64_t*>(rcx - 8);
    rcx = rcx - 8;
    rcx = rcx - r8;
    if (rcx >= 0x20ULL) goto L_0x56d04b0;
    goto L_0x56d0488;

    // 0x56d0488..0x56d0492: basic block 12
    // 0x56d0488  add rax,0x28
    // 0x56d048c  mov rdx,rax
    // 0x56d048f  mov rcx,r8
    //            -> fallthrough goto L_0x56d0492
    L_0x56d0488:;
    rax = rax + 0x28;
    rdx = rax;
    rcx = r8;
    goto L_0x56d0492;

    // 0x56d0492..0x56d0497: basic block 13
    // 0x56d0492  call 0xE935700         sub_e935700(rcx, rdx, r8, r9); return value -> rax
    //            -> fallthrough goto L_0x56d0497
    L_0x56d0492:;
    rax = sub_e935700(rcx, rdx, r8, 0);
    goto L_0x56d0497;

    // 0x56d0497..0x56d04b0: basic block 14
    // 0x56d0497  mov qword ptr [rsi+0x10],0
    // 0x56d049f  mov qword ptr [rsi+0x18],0xF
    // 0x56d04a7  mov byte ptr [rsi],0
    // 0x56d04aa  add rsp,0x30
    // 0x56d04ae  pop rsi
    // 0x56d04af  ret
    L_0x56d0497:;
    a0->f10 = 0;
    a0->f18 = 0xF;
    *reinterpret_cast<std::uint8_t*>(&a0->f0) = 0;
    return static_cast<std::uintptr_t>(rax);

    // 0x56d04b0..0x56d04ca: basic block 15
    // 0x56d04b0  mov qword ptr [rsp+0x20],0   (stack home slot, no observable effect)
    // 0x56d04b9  xor ecx,ecx
    // 0x56d04bb  xor edx,edx
    // 0x56d04bd  xor r8d,r8d
    // 0x56d04c0  xor r9d,r9d
    // 0x56d04c3  call qword ptr [0xF9A8C78]   sub_slot_f9a8c78(0,0,0,0)
    // 0x56d04c9  int3                         (no return; unreachable)
    L_0x56d04b0:; {
        // mov qword ptr [rsp+0x20],0  -- stack home slot; no observable effect outside this frame.
        sub_slot_f9a8c78(0, 0, 0, 0);
        __assume(false);  // original hits int3 here; control never returns
    }
}

} // namespace native::helpers
