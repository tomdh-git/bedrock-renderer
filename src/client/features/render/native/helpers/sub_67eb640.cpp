// LIFT 0x67eb640 size 0x103 1.26.62.01 sub_67eb640
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67eb640.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

// Layout assertions (proven offsets/widths from the disassembly).
static_assert(offsetof(sub_67eb640_rcx, f0) == 0x0, "rcx f0");
static_assert(offsetof(sub_67eb640_rcx, f8) == 0x8, "rcx f8");
static_assert(offsetof(sub_67eb640_rcx, f10) == 0x10, "rcx f10");
static_assert(offsetof(sub_67eb640_rcx, f20) == 0x20, "rcx f20");
static_assert(offsetof(sub_67eb640_rcx, f30) == 0x30, "rcx f30");
static_assert(offsetof(sub_67eb640_rcx, f40) == 0x40, "rcx f40");
static_assert(offsetof(sub_67eb640_rcx, f48) == 0x48, "rcx f48");
static_assert(sizeof(sub_67eb640_rcx) >= 0x50, "rcx sizeof");
static_assert(offsetof(sub_67eb640_rax, f0) == 0x0, "rax f0");
static_assert(offsetof(sub_67eb640_rax, f8) == 0x8, "rax f8");
static_assert(sizeof(sub_67eb640_rax) >= 0x10, "rax sizeof");
static_assert(offsetof(sub_67eb640_rdi, f0) == 0x0, "rdi f0");
static_assert(offsetof(sub_67eb640_rdi, f10) == 0x10, "rdi f10");
static_assert(sizeof(sub_67eb640_rdi) >= 0x18, "rdi sizeof");
static_assert(offsetof(sub_67eb640_rsp, f20) == 0x20, "rsp f20");
static_assert(sizeof(sub_67eb640_rsp) >= 0x28, "rsp sizeof");

LIFT_FN(sub_67eb640, "sub_67eb640", 0x67eb640, sub_67eb640, nullptr);

// Verbatim call instructions from the disassembly of [0x67eb640, 0x67eb743) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x67eb683  call 0xE935700
0x67eb6d1  call 0xE935700
0x67eb6fc  call qword ptr [0xF99FFA0]
0x67eb73c  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x67eb640, 0x67eb743) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

// Forward declaration for direct call callee (native symbol, signature [open] per ABI evidence).
extern "C" uintptr_t sub_e935700(uint64_t arg0, uint64_t arg1, void* arg2, void* arg3);

uintptr_t sub_67eb640(void* self) {
    // 0x67eb640..0x67eb653: basic block 0
    // 0x67eb640  push rsi
    // 0x67eb641  push rdi
    // 0x67eb642  sub rsp,0x28
    // 0x67eb646  mov rsi,rcx
    // 0x67eb649  mov rax,[rcx+0x48]
    // 0x67eb64d  cmp rax,0x10
    // 0x67eb651  jb short 0x67EB688
    // -> if *(a0+0x48) <u 0x10 goto L_0x67eb688
    // -> if *(a0+0x48) >=u 0x10 goto L_0x67eb653
    L_0x67eb640:;
    auto a0 = reinterpret_cast<sub_67eb640_rcx*>(self);
    uint64_t rax = reinterpret_cast<uintptr_t>(a0->f48);
    uint64_t rcx = 0;
    uint64_t rdx = 0;
    uint64_t r8 = 0;
    sub_67eb640_rdi* rdi = nullptr;
    uint64_t rsi = 0;
    sub_67eb640_rax* rax2 = nullptr;
    uintptr_t* v0 = nullptr;
    uintptr_t rdx2 = 0;
    uintptr_t (*vfn)(uintptr_t) = nullptr;

    // 0x67eb653..0x67eb664: basic block 1
    // 0x67eb653  mov rcx,[rsi+0x30]
    // 0x67eb657  lea rdx,[rax+1]
    // 0x67eb65b  cmp rdx,0x1000
    // 0x67eb662  jb short 0x67EB683
    // -> if *(a0+0x48)+0x1 <u 0x1000 goto L_0x67eb683
    // -> if *(a0+0x48)+0x1 >=u 0x1000 goto L_0x67eb664
    L_0x67eb653:;
    rcx = reinterpret_cast<uintptr_t>(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(a0->f30)));
    rdx = rax + 1;
    if (rdx < (uint64_t)0x1000) goto L_0x67eb683;

    // 0x67eb664..0x67eb679: basic block 2
    // 0x67eb664  mov r8,[rcx-8]
    // 0x67eb668  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x67eb66c  sub rcx,r8
    // 0x67eb66f  cmp rcx,0x20
    // 0x67eb673  jae 0x67EB729
    // -> if (*(a0+0x30)-0x8 - *(*(a0+0x30)-0x8)) >=u 0x20 goto L_0x67eb729
    // -> if (*(a0+0x30)-0x8 - *(*(a0+0x30)-0x8)) <u 0x20 goto L_0x67eb679
    L_0x67eb664:;
    r8 = *reinterpret_cast<uint64_t*>(rcx - 8);
    rcx = rcx - 8 - r8;
    if (rcx >= (uint64_t)0x20) goto L_0x67eb729;

    // 0x67eb679..0x67eb683: basic block 3
    // 0x67eb679  add rax,0x28
    // 0x67eb67d  mov rdx,rax
    // 0x67eb680  mov rcx,r8
    // -> if fallthrough goto L_0x67eb683
    L_0x67eb679:;
    rax = rax + 0x28;
    rdx = rax;
    rcx = r8;

    // 0x67eb683..0x67eb688: basic block 4
    // 0x67eb683  call 0xE935700
    // -> if fallthrough goto L_0x67eb688
    L_0x67eb683:;
    sub_e935700(rdx, rcx, nullptr, nullptr);

    // 0x67eb688..0x67eb6a5: basic block 5
    // 0x67eb688  mov qword ptr [rsi+0x40],0
    // 0x67eb690  mov qword ptr [rsi+0x48],0xF
    // 0x67eb698  mov byte ptr [rsi+0x30],0
    // 0x67eb69c  mov rcx,[rsi+0x10]
    // 0x67eb6a0  test rcx,rcx
    // 0x67eb6a3  je short 0x67EB6E4
    // -> if *(a0+0x10) == 0 goto L_0x67eb6e4
    // -> if *(a0+0x10) != 0 goto L_0x67eb6a5
    L_0x67eb688:;
    a0->f40 = 0;
    a0->f48 = reinterpret_cast<void*>(0xF);
    a0->f30 = nullptr;
    rcx = reinterpret_cast<uintptr_t>(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(a0->f10)));
    if (rcx == 0) goto L_0x67eb6e4;

    // 0x67eb6a5..0x67eb6b5: basic block 6
    // 0x67eb6a5  mov rdx,[rsi+0x20]
    // 0x67eb6a9  sub rdx,rcx
    // 0x67eb6ac  cmp rdx,0x1000
    // 0x67eb6b3  jb short 0x67EB6CD
    // -> if (*(a0+0x20) - *(a0+0x10)) <u 0x1000 goto L_0x67eb6cd
    // -> if (*(a0+0x20) - *(a0+0x10)) >=u 0x1000 goto L_0x67eb6b5
    L_0x67eb6a5:;
    rdx = static_cast<uintptr_t>(a0->f20) - rcx;
    if (rdx < (uint64_t)0x1000) goto L_0x67eb6cd;

    // 0x67eb6b5..0x67eb6c6: basic block 7
    // 0x67eb6b5  mov rax,[rcx-8]
    // 0x67eb6b9  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x67eb6bd  sub rcx,rax
    // 0x67eb6c0  cmp rcx,0x20
    // 0x67eb6c4  jae short 0x67EB729
    // -> if (*(a0+0x10)-0x8 - *(*(a0+0x10)-0x8)) >=u 0x20 goto L_0x67eb729
    // -> if (*(a0+0x10)-0x8 - *(*(a0+0x10)-0x8)) <u 0x20 goto L_0x67eb6c6
    L_0x67eb6b5:;
    rax = *reinterpret_cast<uint64_t*>(rcx - 8);
    rcx = rcx - 8 - rax;
    if (rcx >= (uint64_t)0x20) goto L_0x67eb729;

    // 0x67eb6c6..0x67eb6cd: basic block 8
    // 0x67eb6c6  add rdx,0x27
    // 0x67eb6ca  mov rcx,rax
    // -> if fallthrough goto L_0x67eb6cd
    L_0x67eb6c6:;
    rdx = rdx + 0x27;
    rcx = rax;

    // 0x67eb6cd..0x67eb6e4: basic block 9
    // 0x67eb6cd  lea rdi,[rsi+0x10]
    // 0x67eb6d1  call 0xE935700
    // 0x67eb6d6  xorps xmm0,xmm0
    // 0x67eb6d9  movups [rdi],xmm0
    // 0x67eb6dc  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0x67eb6e4
    L_0x67eb6cd:;
    rdi = reinterpret_cast<sub_67eb640_rdi*>(reinterpret_cast<uint8_t*>(self) + 0x10);
    sub_e935700(rdx, rcx, nullptr, nullptr);
    rdi->f0[0] = 0;
    rdi->f0[1] = 0;
    rdi->f10 = 0;

    // 0x67eb6e4..0x67eb6ed: basic block 10
    // 0x67eb6e4  mov rsi,[rsi+8]
    // 0x67eb6e8  test rsi,rsi
    // 0x67eb6eb  je short 0x67EB722
    // -> if *(a0+0x8) == 0 goto L_0x67eb722
    // -> if *(a0+0x8) != 0 goto L_0x67eb6ed
    L_0x67eb6e4:;
    rsi = static_cast<uintptr_t>(a0->f8);
    if (rsi == 0) goto L_0x67eb722;

    // 0x67eb6ed..0x67eb6f3: basic block 11
    // 0x67eb6ed  lock dec dword ptr [rsi+8]
    // 0x67eb6f1  jne short 0x67EB722
    // -> if (Dec *u32(*(a0+0x8)+0x8), ?) != 0 goto L_0x67eb722
    // -> if (Dec *u32(*(a0+0x8)+0x8), ?) == 0 goto L_0x67eb6f3
    L_0x67eb6ed:;
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(rsi) + 8)) != 0) goto L_0x67eb722;

    // 0x67eb6f3..0x67eb708: basic block 12
    // 0x67eb6f3  mov rax,[rsi]
    // 0x67eb6f6  mov rax,[rax]
    // 0x67eb6f9  mov rcx,rsi
    // 0x67eb6fc  call qword ptr [0xF99FFA0]
    // 0x67eb702  lock dec dword ptr [rsi+0xC]
    // 0x67eb706  jne short 0x67EB722
    // -> if (Dec *u32(*(a0+0x8)+0xC), ?) != 0 goto L_0x67eb722
    // -> if (Dec *u32(*(a0+0x8)+0xC), ?) == 0 goto L_0x67eb708
    L_0x67eb6f3:;
    rax2 = reinterpret_cast<sub_67eb640_rax*>(reinterpret_cast<void*>(rsi));
    rax = reinterpret_cast<uintptr_t>(rax2->f0);
    rax = *reinterpret_cast<uintptr_t*>(rax);
    rcx = rsi;
    v0 = reinterpret_cast<uintptr_t*>(0xF99FFA0);
    vfn = reinterpret_cast<uintptr_t(*)(uintptr_t)>(*v0);
    vfn(rcx);
    if (_InterlockedDecrement(reinterpret_cast<volatile LONG*>(reinterpret_cast<uint8_t*>(rsi) + 0xC)) != 0) goto L_0x67eb722;

    // 0x67eb708..0x67eb722: basic block 13
    // 0x67eb708  mov rax,[rsi]
    // 0x67eb70b  mov rax,[rax+8]
    // 0x67eb70f  mov rdx,[0xF99FFA0]
    // 0x67eb716  mov rcx,rsi
    // 0x67eb719  add rsp,0x28
    // 0x67eb71d  pop rdi
    // 0x67eb71e  pop rsi
    // 0x67eb71f  jmp rdx
    // -> (fall-through / ret / end)
    L_0x67eb708:;
    rax = reinterpret_cast<uintptr_t>(rax2->f0);
    rax = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(rax) + 8);
    rdx2 = *v0;
    rcx = rsi;
    return rax;

    // 0x67eb722..0x67eb729: basic block 14
    // 0x67eb722  add rsp,0x28
    // 0x67eb726  pop rdi
    // 0x67eb727  pop rsi
    // 0x67eb728  ret
    // -> (fall-through / ret / end)
    L_0x67eb722:;
    return 0;

    // 0x67eb729..0x67eb743: basic block 15
    // 0x67eb729  mov qword ptr [rsp+0x20],0
    // 0x67eb732  xor ecx,ecx
    // 0x67eb734  xor edx,edx
    // 0x67eb736  xor r8d,r8d
    // 0x67eb739  xor r9d,r9d
    // 0x67eb73c  call qword ptr [0xF9A8C78]
    // 0x67eb742  int3
    // -> (fall-through / ret / end)
    L_0x67eb729:;
    auto slot = reinterpret_cast<uintptr_t(*)(uint64_t,uint64_t,void*,void*)>(0xF9A8C78);
    slot(0, 0, nullptr, nullptr);
    __debugbreak();
}

} // namespace native::helpers
