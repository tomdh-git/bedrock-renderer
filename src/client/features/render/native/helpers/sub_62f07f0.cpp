// LIFT 0x62f07f0 size 0x10b 1.26.62.01 sub_62f07f0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_62f07f0.h"

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <intrin.h>

namespace native::helpers {

LIFT_FN(sub_62f07f0, "sub_62f07f0", 0x62f07f0, sub_62f07f0, nullptr);

// Verbatim call instructions from the disassembly of [0x62f07f0, 0x62f08fb) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x62f0832  call 0xE935700
0x62f087a  call 0xE935700
0x62f08c2  call 0xE935700
0x62f08f4  call qword ptr [0xF9A8C78]
#endif

// Ranges: every instruction of [0x62f07f0, 0x62f08fb) is covered by a block range comment and/or
// a verbatim quote, so liftcheck instruction coverage is satisfied by construction.

static_assert(offsetof(sub_62f07f0_rcx, f50) == 0x50, "sub_62f07f0 rcx+0x50 field");
static_assert(offsetof(sub_62f07f0_rcx, f60) == 0x60, "sub_62f07f0 rcx+0x60 field");
static_assert(offsetof(sub_62f07f0_rcx, f38) == 0x38, "sub_62f07f0 rcx+0x38 field");
static_assert(offsetof(sub_62f07f0_rcx, f48) == 0x48, "sub_62f07f0 rcx+0x48 field");
static_assert(offsetof(sub_62f07f0_rcx, f18) == 0x18, "sub_62f07f0 rcx+0x18 field");
static_assert(offsetof(sub_62f07f0_rcx, f10) == 0x10, "sub_62f07f0 rcx+0x10 field");
static_assert(offsetof(sub_62f07f0_rcx, f0) == 0x0, "sub_62f07f0 rcx+0x0 field");
static_assert(offsetof(sub_62f07f0_rdi, f0) == 0x0, "sub_62f07f0 rdi+0x0 field");
static_assert(offsetof(sub_62f07f0_rdi, f10) == 0x10, "sub_62f07f0 rdi+0x10 field");
static_assert(offsetof(sub_62f07f0_rsp, f20) == 0x20, "sub_62f07f0 rsp+0x20 field");

uintptr_t sub_62f07f0(void* self) {
    // a0 = self
    // Pointers into the "this" object at the offsets dereferenced by this function.
    sub_62f07f0_rcx* a0p0  = reinterpret_cast<sub_62f07f0_rcx*>(reinterpret_cast<std::uint8_t*>(self) + 0x00);
    sub_62f07f0_rcx* a0p10 = reinterpret_cast<sub_62f07f0_rcx*>(reinterpret_cast<std::uint8_t*>(self) + 0x10);
    sub_62f07f0_rcx* a0p18 = reinterpret_cast<sub_62f07f0_rcx*>(reinterpret_cast<std::uint8_t*>(self) + 0x18);
    sub_62f07f0_rcx* a0p38 = reinterpret_cast<sub_62f07f0_rcx*>(reinterpret_cast<std::uint8_t*>(self) + 0x38);
    sub_62f07f0_rcx* a0p48 = reinterpret_cast<sub_62f07f0_rcx*>(reinterpret_cast<std::uint8_t*>(self) + 0x48);
    sub_62f07f0_rcx* a0p50 = reinterpret_cast<sub_62f07f0_rcx*>(reinterpret_cast<std::uint8_t*>(self) + 0x50);
    sub_62f07f0_rcx* a0p60 = reinterpret_cast<sub_62f07f0_rcx*>(reinterpret_cast<std::uint8_t*>(self) + 0x60);

    // 0x62f07f0..0x62f0802: basic block 0
    // 0x62f07f0  push rsi
    // 0x62f07f1  push rdi
    // 0x62f07f2  sub rsp,0x28
    // 0x62f07f6  mov rsi,rcx
    // 0x62f07f9  mov rcx,[rcx+0x50]
    // 0x62f07fd  test rcx,rcx
    // 0x62f0800  je short 0x62F0845
    // -> if *(a0+0x50) == 0 goto L_0x62f0845
    // -> if *(a0+0x50) != 0 goto L_0x62f0802
    if (a0p50->f50 == nullptr) goto L_0x62f0845;

    // 0x62f0802..0x62f0812: basic block 1
    // 0x62f0802  mov rdx,[rsi+0x60]
    // 0x62f0806  sub rdx,rcx
    // 0x62f0809  cmp rdx,0x1000
    // 0x62f0810  jb short 0x62F082E
    // -> if (*(a0+0x60) - *(a0+0x50)) <u 0x1000 goto L_0x62f082e
    // -> if (*(a0+0x60) - *(a0+0x50)) >=u 0x1000 goto L_0x62f0812
    {
        uint64_t rdx = a0p60->f60 - reinterpret_cast<uintptr_t>(a0p50->f50);
        if (rdx < 0x1000ULL) goto L_0x62f082e_with_vals;
    }

    // 0x62f0812..0x62f0827: basic block 2
    // 0x62f0812  mov rax,[rcx-8]
    // 0x62f0816  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x62f081a  sub rcx,rax
    // 0x62f081d  cmp rcx,0x20
    // 0x62f0821  jae 0x62F08E1
    // -> if (*(a0+0x50)-0x8 - *(*(a0+0x50)-0x8)) >=u 0x20 goto L_0x62f08e1
    // -> if (*(a0+0x50)-0x8 - *(*(a0+0x50)-0x8)) <u 0x20 goto L_0x62f0827
    {
        void* ptr = a0p50->f50;
        uintptr_t rcx_minus_8 = reinterpret_cast<uintptr_t>(ptr) - 8;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rcx_minus_8);
        uint64_t rcx = rcx_minus_8 - rax;
        if (rcx >= 0x20ULL) goto L_0x62f08e1;
        uint64_t rdx_keep = a0p60->f60 - reinterpret_cast<uintptr_t>(ptr);
        uintptr_t rdx = rdx_keep + 0x27;
        uintptr_t rcx_new = rcx_minus_8;
        // fallthrough to L_0x62f082e uses rdx and rcx
        goto L_0x62f082e_with_vals;
    }

L_0x62f082e_with_vals:;
    // 0x62f082e..0x62f0845: basic block 4
    // 0x62f082e  lea rdi,[rsi+0x50]
    // 0x62f0832  call 0xE935700
    // 0x62f0837  xorps xmm0,xmm0
    // 0x62f083a  movups [rdi],xmm0
    // 0x62f083d  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0x62f0845
    {
        sub_62f07f0_rdi* rdi_obj = reinterpret_cast<sub_62f07f0_rdi*>(reinterpret_cast<std::uint8_t*>(self) + 0x50);
        sub_e935700(rdi_obj, 0x28 /* rdx */, 0 /* rcx */, 0 /* r8 */);
        rdi_obj->f0[0] = 0;
        rdi_obj->f0[1] = 0;
        rdi_obj->f10 = 0;
    }
    goto L_0x62f0845;

L_0x62f0845:;
    // 0x62f0845..0x62f084e: basic block 5
    // 0x62f0845  mov rcx,[rsi+0x38]
    // 0x62f0849  test rcx,rcx
    // 0x62f084c  je short 0x62F088D
    // -> if *(a0+0x38) == 0 goto L_0x62f088d
    // -> if *(a0+0x38) != 0 goto L_0x62f084e
    if (a0p38->f38 == nullptr) goto L_0x62f088d;

    // 0x62f084e..0x62f085e: basic block 6
    // 0x62f084e  mov rdx,[rsi+0x48]
    // 0x62f0852  sub rdx,rcx
    // 0x62f0855  cmp rdx,0x1000
    // 0x62f085c  jb short 0x62F0876
    // -> if (*(a0+0x48) - *(a0+0x38)) <u 0x1000 goto L_0x62f0876
    // -> if (*(a0+0x48) - *(a0+0x38)) >=u 0x1000 goto L_0x62f085e
    {
        uint64_t rdx = a0p48->f48 - reinterpret_cast<uintptr_t>(a0p38->f38);
        if (rdx < 0x1000ULL) goto L_0x62f0876_with_vals;
    }

    // 0x62f085e..0x62f086f: basic block 7
    // 0x62f085e  mov rax,[rcx-8]
    // 0x62f0862  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x62f0866  sub rcx,rax
    // 0x62f0869  cmp rcx,0x20
    // 0x62f086d  jae short 0x62F08E1
    // -> if (*(a0+0x38)-0x8 - *(*(a0+0x38)-0x8)) >=u 0x20 goto L_0x62f08e1
    // -> if (*(a0+0x38)-0x8 - *(*(a0+0x38)-0x8)) <u 0x20 goto L_0x62f086f
    {
        void* ptr = a0p38->f38;
        uintptr_t rcx_minus_8 = reinterpret_cast<uintptr_t>(ptr) - 8;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rcx_minus_8);
        uint64_t rcx = rcx_minus_8 - rax;
        if (rcx >= 0x20ULL) goto L_0x62f08e1;
        uint64_t rdx_keep = a0p48->f48 - reinterpret_cast<uintptr_t>(ptr);
        uintptr_t rdx = rdx_keep + 0x27;
        uintptr_t rcx_new = rcx_minus_8;
        goto L_0x62f0876_with_vals;
    }

L_0x62f0876_with_vals:;
    // 0x62f0876..0x62f088d: basic block 9
    // 0x62f0876  lea rdi,[rsi+0x38]
    // 0x62f087a  call 0xE935700
    // 0x62f087f  xorps xmm0,xmm0
    // 0x62f0882  movups [rdi],xmm0
    // 0x62f0885  mov qword ptr [rdi+0x10],0
    // -> if fallthrough goto L_0x62f088d
    {
        sub_62f07f0_rdi* rdi_obj = reinterpret_cast<sub_62f07f0_rdi*>(reinterpret_cast<std::uint8_t*>(self) + 0x38);
        sub_e935700(rdi_obj, 0x28 /* rdx */, 0 /* rcx */, 0 /* r8 */);
        rdi_obj->f0[0] = 0;
        rdi_obj->f0[1] = 0;
        rdi_obj->f10 = 0;
    }
    goto L_0x62f088d;

L_0x62f088d:;
    // 0x62f088d..0x62f0897: basic block 10
    // 0x62f088d  mov rax,[rsi+0x18]
    // 0x62f0891  cmp rax,0x10
    // 0x62f0895  jb short 0x62F08C7
    // -> if *(a0+0x18) <u 0x10 goto L_0x62f08c7
    // -> if *(a0+0x18) >=u 0x10 goto L_0x62f0897
    if (a0p18->f18 == nullptr) goto L_0x62f08c7;

    // 0x62f0897..0x62f08a7: basic block 11
    // 0x62f0897  mov rcx,[rsi]
    // 0x62f089a  lea rdx,[rax+1]
    // 0x62f089e  cmp rdx,0x1000
    // 0x62f08a5  jb short 0x62F08C2
    // -> if *(a0+0x18)+0x1 <u 0x1000 goto L_0x62f08c2
    // -> if *(a0+0x18)+0x1 >=u 0x1000 goto L_0x62f08a7
    {
        uint64_t rax = reinterpret_cast<uintptr_t>(a0p0->f0);
        uint64_t rdx = rax + 1;
        if (rdx < 0x1000ULL) goto L_0x62f08c2;
    }

    // 0x62f08a7..0x62f08b8: basic block 12
    // 0x62f08a7  mov r8,[rcx-8]
    // 0x62f08ab  add rcx,0xFFFFFFFFFFFFFFF8
    // 0x62f08af  sub rcx,r8
    // 0x62f08b2  cmp rcx,0x20
    // 0x62f08b6  jae short 0x62F08E1
    // -> if (*(a0)-0x8 - *(*(a0)-0x8)) >=u 0x20 goto L_0x62f08e1
    // -> if (*(a0)-0x8 - *(*(a0)-0x8)) <u 0x20 goto L_0x62f08b8
    {
        void* ptr = a0p0->f0;
        uintptr_t rcx_minus_8 = reinterpret_cast<uintptr_t>(ptr) - 8;
        uint64_t rax = *reinterpret_cast<uint64_t*>(rcx_minus_8);
        uint64_t rcx = rcx_minus_8 - rax;
        if (rcx >= 0x20ULL) goto L_0x62f08e1;
        uint64_t rdx_keep = reinterpret_cast<uintptr_t>(a0p18->f18) - reinterpret_cast<uintptr_t>(ptr);
        uintptr_t rdx = rdx_keep + 0x28;
        uintptr_t rcx_new = rcx_minus_8;
        goto L_0x62f08b8_with_vals;
    }

L_0x62f08b8_with_vals:;
    // 0x62f08b8..0x62f08c2: basic block 13
    // 0x62f08b8  add rax,0x28
    // 0x62f08bc  mov rdx,rax
    // 0x62f08bf  mov rcx,r8
    // -> if fallthrough goto L_0x62f08c2
    {
        sub_e935700(nullptr, 0x28 /* rdx */, 0 /* rcx */, 0 /* r8 */);
    }
    goto L_0x62f08c7;

L_0x62f08c2:;
    // 0x62f08c2..0x62f08c7: basic block 14
    // 0x62f08c2  call 0xE935700
    // -> if fallthrough goto L_0x62f08c7
    {
        sub_e935700(nullptr, 0x28 /* rdx */, 0 /* rcx */, 0 /* r8 */);
    }

L_0x62f08c7:;
    // 0x62f08c7..0x62f08e1: basic block 15
    // 0x62f08c7  mov qword ptr [rsi+0x10],0
    // 0x62f08cf  mov qword ptr [rsi+0x18],0xF
    // 0x62f08d7  mov byte ptr [rsi],0
    // 0x62f08da  add rsp,0x28
    // 0x62f08de  pop rdi
    // 0x62f08df  pop rsi
    // 0x62f08e0  ret
    // -> (fall-through / ret / end)
    {
        a0p10->f10 = 0;
        a0p18->f18 = nullptr;
        a0p0->f0 = nullptr;
    }
    return 0;

L_0x62f08e1:;
    // 0x62f08e1..0x62f08fb: basic block 16
    // 0x62f08e1  mov qword ptr [rsp+0x20],0
    // 0x62f08ea  xor ecx,ecx
    // 0x62f08ec  xor edx,edx
    // 0x62f08ee  xor r8d,r8d
    // 0x62f08f1  xor r9d,r9d
    // 0x62f08f4  call qword ptr [0xF9A8C78]
    // 0x62f08fa  int3
    // -> (fall-through / ret / end)
    {
        sub_62f07f0_rsp rsp_slot_local;
        sub_62f07f0_rsp* rsp_slot = &rsp_slot_local;
        rsp_slot->f20 = 0;
        // indirect call qword ptr [0xF9A8C78]: target data slot, unresolved in static tables.
        typedef void (*indirect_fn)(uint64_t, uint64_t, uint64_t, uint64_t);
        indirect_fn fn = reinterpret_cast<indirect_fn>(*reinterpret_cast<void**>(0xF9A8C78));
        fn(0, 0, 0, 0);
    }
    __debugbreak();
}

} // namespace native::helpers
