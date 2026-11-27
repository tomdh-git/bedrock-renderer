// LIFT 0xbb47d30 size 0x11f 1.26.62.01 sub_bb47d30
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_bb47d30.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

LIFT_FN(sub_bb47d30, "sub_bb47d30", 0xbb47d30, sub_bb47d30, nullptr);

// Callee sub_bc0e8f0 (0xbc0e8f0): signature not recoverable from static data.
// Modelled from the call site at 0xbb47dad:
//   rcx = out base (+0x10 = begin, +0x18 = end), rdx = base+0x40,
//   r8  = self+0x9D0, r9 = pointer to a single byte.
// Return value is unused by this function; the callee writes [out+0x10] and [out+0x18].
void sub_bc0e8f0(void* out_base, void* rdx, void* r8, void* r9);

// Verbatim call instructions from the disassembly of [0xbb47d30, 0xbb47e4f) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0xbb47dad  call 0xBC0E8F0
#endif

uintptr_t sub_bb47d30(void* self) {
    // 0xbb47d30..0xbb47d4a: basic block 0
    // 0xbb47d30  sub rsp,0x58
    // 0xbb47d34  mov r8,rcx
    // 0xbb47d37  lea rax,[rcx+0xA10]
    // 0xbb47d3e  mov rcx,[rcx+0xA10]
    // 0xbb47d45  cmp rcx,rax
    // 0xbb47d48  jne short 0xBB47D5C
    uint8_t* a0 = (uint8_t*)self;
    uint8_t* rax = a0 + 0xA10;
    uint8_t* rcx = *(uint8_t**)(a0 + 0xA10);
    uint8_t* r8 = (uint8_t*)self;
    uint8_t* rdx = nullptr;
    uint8_t* r9 = nullptr;
    uint8_t* r10 = nullptr;
    uint8_t* cur_r9 = nullptr;
    uint8_t r8b = 0;
    uint8_t dl = 0;
    if (rcx != rax) goto L_0xbb47d5c;
    goto L_0xbb47e37;

    // 0xbb47d4a..0xbb47d4f: basic block 1
    // 0xbb47d4a  jmp 0xBB47E37
    // -> if jmp goto L_0xbb47e37
    L_0xbb47d4a:;
    goto L_0xbb47e37;

    // 0xbb47d4f..0xbb47d50: basic block 2
    // 0xbb47d4f  nop
    // -> if fallthrough goto L_0xbb47d50
    L_0xbb47d4f:;
    goto L_0xbb47d50;

    // 0xbb47d50..0xbb47d5c: basic block 3
    // 0xbb47d50  mov rcx,[rcx]
    // 0xbb47d53  cmp rcx,rax
    // 0xbb47d56  je 0xBB47E37
    // -> if ? == a0+0xA10 goto L_0xbb47e37
    // -> if ? != a0+0xA10 goto L_0xbb47d5c
    L_0xbb47d50:;
    rcx = *(uint8_t**)rcx;
    if (rcx == rax) goto L_0xbb47e37;
    goto L_0xbb47d5c;

    // 0xbb47d5c..0xbb47d69: basic block 4
    // 0xbb47d5c  mov rdx,[rcx+0x10]
    // 0xbb47d60  mov r9,[rcx+0x18]
    // 0xbb47d64  cmp rdx,r9
    // 0xbb47d67  je short 0xBB47D50
    // -> if ? == ? goto L_0xbb47d50
    // -> if ? != ? goto L_0xbb47d69
    L_0xbb47d5c:;
    rdx = *(uint8_t**)(rcx + 0x10);
    r9 = *(uint8_t**)(rcx + 0x18);
    if (rdx == r9) goto L_0xbb47d50;
    goto L_0xbb47d70;

    // 0xbb47d69..0xbb47d70: basic block 5
    // 0xbb47d69  nop [rax]
    // -> if fallthrough goto L_0xbb47d70
    L_0xbb47d69:;
    goto L_0xbb47d70;

    // 0xbb47d70..0xbb47d76: basic block 6
    // 0xbb47d70  test byte ptr [rdx+0xA],8
    // 0xbb47d74  jne short 0xBB47D84
    // -> if (? & 0x8) != 0 goto L_0xbb47d84
    // -> if (? & 0x8) == 0 goto L_0xbb47d76
    L_0xbb47d70:;
    if ((*(uint8_t*)(rdx + 0xA) & 0x8) != 0) goto L_0xbb47d84;
    rdx += 0xC8;
    if (rdx != r9) goto L_0xbb47d70;
    goto L_0xbb47d82;

    // 0xbb47d76..0xbb47d82: basic block 7
    // 0xbb47d76  add rdx,0xC8
    // 0xbb47d7d  cmp rdx,r9
    // 0xbb47d80  jne short 0xBB47D70
    // -> if ? != ? goto L_0xbb47d70
    // -> if ? == ? goto L_0xbb47d82
    L_0xbb47d76:;
    rdx += 0xC8;
    if (rdx != r9) goto L_0xbb47d70;
    goto L_0xbb47d82;

    // 0xbb47d82..0xbb47d84: basic block 8
    // 0xbb47d82  jmp short 0xBB47D50
    // -> if jmp goto L_0xbb47d50
    L_0xbb47d82:;
    goto L_0xbb47d50;

    // 0xbb47d84..0xbb47dc1: basic block 9
    // 0xbb47d84  mov rax,[r8+0xA78]
    // 0xbb47d8b  add r8,0x9D0
    // 0xbb47d92  mov rdx,[rax]
    // 0xbb47d95  add rdx,0x40
    // 0xbb47d99  lea rax,[rsp+0x2F]
    // 0xbb47d9e  mov [rsp+0x20],rax
    // 0xbb47da3  lea rcx,[rsp+0x30]
    // 0xbb47da8  lea r9,[rsp+0x2E]
    // 0xbb47dad  call 0xBC0E8F0
    // 0xbb47db2  mov rax,[rsp+0x40]
    // 0xbb47db7  mov rcx,[rsp+0x48]
    // 0xbb47dbc  cmp rax,rcx
    // 0xbb47dbf  je short 0xBB47E37
    // -> if ? == ? goto L_0xbb47e37
    // -> if ? != ? goto L_0xbb47dc1
    L_0xbb47d84:;
    {
        uint8_t* rax_b = *(uint8_t**)((uint8_t*)r8 + 0xA78);
        r8 = (uint8_t*)((uint8_t*)r8 + 0x9D0);
        uint8_t* rdx_b = rax_b;
        rdx_b += 0x40;

        uint8_t local_2e = 0;
        uintptr_t local_30 = 0;
        uintptr_t local_38 = 0;
        sub_bc0e8f0(&local_30, (void*)rdx_b, (void*)r8, (void*)&local_2e);

        rax = (uint8_t*)(uintptr_t)local_30;
        rcx = (uint8_t*)(uintptr_t)local_38;
    }
    if (rax == rcx) goto L_0xbb47e37;

    // 0xbb47dc1..0xbb47dc8: basic block 10
    // 0xbb47dc1  xor r8d,r8d
    // 0xbb47dc4  xor edx,edx
    // 0xbb47dc6  jmp short 0xBB47DE9
    // -> if jmp goto L_0xbb47de9
    L_0xbb47dc1:;
    r8b = 0;
    dl = 0;
    goto L_0xbb47de9;

    // 0xbb47dc8..0xbb47de0: basic block 11
    // 0xbb47dc8  cmp dword ptr [r9+0x38],1
    // 0xbb47dcd  sete r8b
    // 0xbb47dd1  nop [rax+rax]
    // -> if fallthrough goto L_0xbb47de0
    L_0xbb47dc8:;
    r8b = (*(uint32_t*)(cur_r9 + 0x38) == 1) ? 1u : 0u;
    goto L_0xbb47de0;

    // 0xbb47de0..0xbb47de9: basic block 12
    // 0xbb47de0  add rax,0x18
    // 0xbb47de4  cmp rax,rcx
    // 0xbb47de7  je short 0xBB47E3E
    // -> if ? == ? goto L_0xbb47e3e
    // -> if ? != ? goto L_0xbb47de9
    L_0xbb47de0:;
    rax += 0x18;
    if (rax == rcx) goto L_0xbb47e3e;
    goto L_0xbb47de9;

    // 0xbb47de9..0xbb47df2: basic block 13
    // 0xbb47de9  mov r10,[rax+8]
    // 0xbb47ded  test r10,r10
    // 0xbb47df0  je short 0xBB47DE0
    // -> if ? == 0 goto L_0xbb47de0
    // -> if ? != 0 goto L_0xbb47df2
    L_0xbb47de9:;
    r10 = *(uint8_t**)(rax + 8);
    if (r10 == 0) goto L_0xbb47de0;
    cur_r9 = *(uint8_t**)(rax + 0x10);
    // 0xbb47df2..0xbb47dfb: basic block 14
    // 0xbb47df2  mov r9,[rax+0x10]
    // 0xbb47df6  test r9,r9
    // 0xbb47df9  je short 0xBB47DE0
    // -> if ? == 0 goto L_0xbb47de0
    // -> if ? != 0 goto L_0xbb47dfb
    L_0xbb47df2:;
    if (cur_r9 == 0) goto L_0xbb47de0;
    // 0xbb47dfb..0xbb47e02: basic block 15
    // 0xbb47dfb  test byte ptr [r10+0xA],8
    // 0xbb47e00  je short 0xBB47DE0
    // -> if (? & 0x8) == 0 goto L_0xbb47de0
    // -> if (? & 0x8) != 0 goto L_0xbb47e02
    L_0xbb47dfb:;
    if ((*(uint8_t*)(r10 + 0xA) & 0x8) == 0) goto L_0xbb47de0;
    // 0xbb47e02..0xbb47e0e: basic block 16
    // 0xbb47e02  mov r9,[r9+0xC0]
    // 0xbb47e09  test r9,r9
    // 0xbb47e0c  je short 0xBB47DE0
    // -> if ? == 0 goto L_0xbb47de0
    // -> if ? != 0 goto L_0xbb47e0e
    L_0xbb47e02:;
    cur_r9 = *(uint8_t**)(cur_r9 + 0xC0);
    if (cur_r9 == 0) goto L_0xbb47de0;
    // 0xbb47e0e..0xbb47e24: basic block 17
    // 0xbb47e0e  movzx r10d,word ptr [r10+0xB6]
    // 0xbb47e16  shl r10d,6
    // 0xbb47e1a  add r9,r10
    // 0xbb47e1d  test dl,1
    // 0xbb47e20  mov dl,1
    // 0xbb47e22  jne short 0xBB47E2C
    // -> if (? & 0x1) != 0 goto L_0xbb47e2c
    // -> if (? & 0x1) == 0 goto L_0xbb47e24
    L_0xbb47e0e:;
    {
        uintptr_t r10d = *(uint16_t*)(r10 + 0xB6);
        r10d <<= 6;
        cur_r9 += r10d;
        bool dl_odd = (dl & 1u) != 0u;
        dl = 1u;
        if (dl_odd) goto L_0xbb47e2c;
        goto L_0xbb47e24;
    }

    // 0xbb47e24..0xbb47e2c: basic block 18
    // 0xbb47e24  cmp dword ptr [r9+0x38],0
    // 0xbb47e29  sete dl
    // -> if fallthrough goto L_0xbb47e2c
    L_0xbb47e24:;
    dl = (*(uint32_t*)(cur_r9 + 0x38) == 0) ? 1u : 0u;
    goto L_0xbb47e2c;

    // 0xbb47e2c..0xbb47e32: basic block 19
    // 0xbb47e2c  test r8b,1
    // 0xbb47e30  je short 0xBB47DC8
    // -> if (? & 0x1) == 0 goto L_0xbb47dc8
    // -> if (? & 0x1) != 0 goto L_0xbb47e32
    L_0xbb47e2c:;
    if ((r8b & 1u) == 0u) goto L_0xbb47dc8;
    // 0xbb47e32..0xbb47e37: basic block 20
    // 0xbb47e32  mov r8b,1
    // 0xbb47e35  jmp short 0xBB47DE0
    // -> if jmp goto L_0xbb47de0
    L_0xbb47e32:;
    r8b = 1u;
    goto L_0xbb47de0;

    // 0xbb47e37..0xbb47e3e: basic block 21
    // 0xbb47e37  xor eax,eax
    // 0xbb47e39  add rsp,0x58
    // 0xbb47e3d  ret
    // -> (fall-through / ret / end)
    L_0xbb47e37:;
    return 0;

    // 0xbb47e3e..0xbb47e4f: basic block 22
    // 0xbb47e3e  movzx ecx,r8b
    // 0xbb47e42  shl ecx,8
    // 0xbb47e45  movzx eax,dl
    // 0xbb47e48  or eax,ecx
    // 0xbb47e4a  add rsp,0x58
    // 0xbb47e4e  ret
    // -> (fall-through / ret / end)
    L_0xbb47e3e:;
    return (uintptr_t)(dl | (r8b << 8));

    return 0;   // unreachable
}

// Layout assertions for the state structs used by this lift (offsetof matches the
// observed offsets in the disassembly; widths per the field access table).
static_assert(offsetof(sub_bb47d30_rcx, f0) == 0x0, "sub_0xbb47d30 rcx+0x0 field");
static_assert(offsetof(sub_bb47d30_rcx, f10) == 0x10, "sub_0xbb47d30 rcx+0x10 field");
static_assert(offsetof(sub_bb47d30_rcx, f18) == 0x18, "sub_0xbb47d30 rcx+0x18 field");
static_assert(offsetof(sub_bb47d30_rcx, fa10) == 0xa10, "sub_0xbb47d30 rcx+0xa10 field");
static_assert(offsetof(sub_bb47d30_rcx, fa78) == 0xa78, "sub_0xbb47d30 rcx+0xa78 field");
static_assert(sizeof(sub_bb47d30_rcx) >= 0xa80, "sub_0xbb47d30 rcx sizeof lower bound");

static_assert(offsetof(sub_bb47d30_rdx, fa) == 0xa, "sub_0xbb47d30 rdx+0xa field");
static_assert(sizeof(sub_bb47d30_rdx) >= 0xb, "sub_0xbb47d30 rdx sizeof lower bound");

static_assert(offsetof(sub_bb47d30_r9, f38) == 0x38, "sub_0xbb47d30 r9+0x38 field");
static_assert(offsetof(sub_bb47d30_r9, fc0) == 0xc0, "sub_0xbb47d30 r9+0xc0 field");
static_assert(sizeof(sub_bb47d30_r9) >= 0xc8, "sub_0xbb47d30 r9 sizeof lower bound");

static_assert(offsetof(sub_bb47d30_r10, fa) == 0xa, "sub_0xbb47d30 r10+0xa field");
static_assert(offsetof(sub_bb47d30_r10, fb6) == 0xb6, "sub_0xbb47d30 r10+0xb6 field");
static_assert(sizeof(sub_bb47d30_r10) >= 0xb8, "sub_0xbb47d30 r10 sizeof lower bound");

static_assert(offsetof(sub_bb47d30_rax, f0) == 0x0, "sub_0xbb47d30 rax+0x0 field");
static_assert(offsetof(sub_bb47d30_rax, f8) == 0x8, "sub_0xbb47d30 rax+0x8 field");
static_assert(offsetof(sub_bb47d30_rax, f10) == 0x10, "sub_0xbb47d30 rax+0x10 field");
static_assert(sizeof(sub_bb47d30_rax) >= 0x18, "sub_0xbb47d30 rax sizeof lower bound");

static_assert(offsetof(sub_bb47d30_rsp, f20) == 0x20, "sub_0xbb47d30 rsp+0x20 field");
static_assert(offsetof(sub_bb47d30_rsp, f2e) == 0x2e, "sub_0xbb47d30 rsp+0x2e field");
static_assert(offsetof(sub_bb47d30_rsp, f2f) == 0x2f, "sub_0xbb47d30 rsp+0x2f field");
static_assert(offsetof(sub_bb47d30_rsp, f30) == 0x30, "sub_0xbb47d30 rsp+0x30 field");
static_assert(offsetof(sub_bb47d30_rsp, f40) == 0x40, "sub_0xbb47d30 rsp+0x40 field");
static_assert(offsetof(sub_bb47d30_rsp, f48) == 0x48, "sub_0xbb47d30 rsp+0x48 field");
static_assert(sizeof(sub_bb47d30_rsp) >= 0x50, "sub_0xbb47d30 rsp sizeof lower bound");

} // namespace native::helpers
