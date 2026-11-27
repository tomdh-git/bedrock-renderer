// LIFT 0x4e00c00 size 0x132 1.26.62.01 sub_4e00c00
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_4e00c00.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

namespace native::helpers {

static_assert(offsetof(sub_4e00c00_rcx, vtable) == 0x0, "sub_4e00c00 rcx+0x0 field");
static_assert(offsetof(sub_4e00c00_rcx, strong_refcount) == 0x8, "sub_4e00c00 rcx+0x8 field");
static_assert(offsetof(sub_4e00c00_rcx, weak_refcount) == 0xc, "sub_4e00c00 rcx+0xc field");
static_assert(offsetof(sub_4e00c00_rcx, type_tag) == 0x18, "sub_4e00c00 rcx+0x18 field");
static_assert(sizeof(sub_4e00c00_rcx) >= 0x19, "sub_4e00c00 rcx sizeof lower bound");

static_assert(offsetof(sub_4e00c00_rdx, target) == 0x0, "sub_4e00c00 rdx+0x0 field");
static_assert(offsetof(sub_4e00c00_rdx, next) == 0x8, "sub_4e00c00 rdx+0x8 field");
static_assert(sizeof(sub_4e00c00_rdx) >= 0x10, "sub_4e00c00 rdx sizeof lower bound");

static_assert(offsetof(sub_4e00c00_r8, source) == 0x0, "sub_4e00c00 r8+0x0 field");
static_assert(offsetof(sub_4e00c00_r8, refcounted) == 0x8, "sub_4e00c00 r8+0x8 field");
static_assert(offsetof(sub_4e00c00_r8, slots) == 0x10, "sub_4e00c00 r8+0x10 field");
static_assert(sizeof(sub_4e00c00_r8) >= 0x20, "sub_4e00c00 r8 sizeof lower bound");

static_assert(offsetof(sub_4e00c00_rax, slots0) == 0x0, "sub_4e00c00 rax+0x0 field");
static_assert(offsetof(sub_4e00c00_rax, slots1) == 0x10, "sub_4e00c00 rax+0x10 field");
static_assert(sizeof(sub_4e00c00_rax) >= 0x20, "sub_4e00c00 rax sizeof lower bound");

static_assert(offsetof(sub_4e00c00_rbx, byte0) == 0x0, "sub_4e00c00 rbx+0x0 field");
static_assert(sizeof(sub_4e00c00_rbx) >= 0x1, "sub_4e00c00 rbx sizeof lower bound");

LIFT_FN(sub_4e00c00, "sub_4e00c00", 0x4e00c00, sub_4e00c00, nullptr);

// Verbatim call instructions from the disassembly of [0x4e00c00, 0x4e00d32) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x4e00c70  call qword ptr [0xF99FFA0]
0x4e00cc6  call qword ptr [0xF99FFA0]
0x4e00d25  call 0x9BC830
#endif

extern "C" uintptr_t sub_eea6040(void* a1, uint64_t a2);
extern "C" uintptr_t sub_9bc830(uint32_t size);

uintptr_t sub_4e00c00(uintptr_t self, void* a1, void* a2) {
    uintptr_t rax = 0;
    uintptr_t rcx = 0;
    uintptr_t rdx = 0;
    void* rbx = nullptr;
    void* rsi = nullptr;
    void* rdi = nullptr;
    void* r8 = nullptr;
    void* r9 = nullptr;
    std::uint8_t al = 0;

    // 0x4e00c00..0x4e00c19: basic block 0 (switch)
    // lea rax,[0xF215890]; movsxd rcx,[rax+rcx*4]; add rcx,rax; jmp rcx
    {
        uintptr_t table_base = 0xF215890ULL;
        std::int32_t* table = (std::int32_t*)table_base;
        std::int32_t off = table[(std::uint32_t)self];
        uintptr_t target = table_base + (uintptr_t)off;
        switch (target) {
            case 0x4E00C19: goto L_0x4e00c19;
            case 0x4E00C20: goto L_0x4e00c20;
            case 0x4E00C54: goto L_0x4e00c54;
            case 0x4E00CDE: goto L_0x4e00cde;
            case 0x4E00D13: goto L_0x4e00d13;
            default: __assume(0);
        }
    }

    // 0x4e00c19..0x4e00c20: basic block 1
    // xor eax,eax; jmp 0x4E00D0D
L_0x4e00c19:
    rax = 0;
    al = 0;
    goto L_0x4e00d0d;

    // 0x4e00c20..0x4e00c39: basic block 2
    // mov rax,[rdx]; mov rcx,[r8]; mov [rax],rcx; xorps; movups [rax+8],xmm0;
    // mov rcx,[r8+0x10]; test rcx,rcx; je L_0x4e00c3d / jne L_0x4e00c39
L_0x4e00c20:
    {
        auto* a1_rdx = (sub_4e00c00_rdx*)a1;
        auto* a2_r8 = (sub_4e00c00_r8*)a2;
        rax = (uintptr_t)a1_rdx->target;
        rcx = (uintptr_t)a2_r8->source;
        *(void***)(rax) = (void**)rcx;
        *(uint64_t*)(rax + 8) = 0;
        rcx = (uintptr_t)a2_r8->slots[0];
        if (rcx == 0) goto L_0x4e00c3d;
        goto L_0x4e00c39;
    }

    // 0x4e00c39..0x4e00c3d: basic block 3
    // lock inc dword ptr [rcx+8]
L_0x4e00c39:
    {
        auto* obj = (sub_4e00c00_rcx*)rcx;
        _InterlockedIncrement((volatile long*)&obj->strong_refcount);
        goto L_0x4e00c3d;
    }

    // 0x4e00c3d..0x4e00c54: basic block 4
    // mov rcx,[r8+8]; mov [rax+8],rcx; mov rcx,[r8+0x10]; mov [rax+0x10],rcx;
    // mov al,3; jmp 0x4E00D0D
L_0x4e00c3d:
    {
        auto* a2_r8 = (sub_4e00c00_r8*)a2;
        auto* rax_struct = (sub_4e00c00_rax*)rax;
        rcx = (uintptr_t)a2_r8->refcounted;
        rax_struct->slots0[1] = (void*)rcx;
        rcx = (uintptr_t)a2_r8->slots[0];
        rax_struct->slots1[0] = (void*)rcx;
        al = 3;
        rax = (rax & ~0xFFui64) | (uintptr_t)al;
        goto L_0x4e00d0d;
    }

    // 0x4e00c54..0x4e00c7f: basic block 5
    // mov rdi,r8; mov rsi,rdx; mov rbx,[rdx]; mov rcx,[0x1233E1A8];
    // mov rax,[rcx]; mov rax,[rax+8]; mov edx,0x20; call sub_eea6040;
    // test rax,rax; je L_0x4e00d1d / jne L_0x4e00c7f
L_0x4e00c54:
    {
        void* global = *(void**)0x1233E1A8ULL;
        rdi = a2;
        rsi = a1;
        rbx = *(void**)a1;
        rax = (uintptr_t)*(void**)global;
        rax = (uintptr_t)*(void**)(rax + 8);
        rax = (uintptr_t)sub_eea6040(global, 0x20ULL);
        if (rax == 0) goto L_0x4e00d1d;
        goto L_0x4e00c7f;
    }

    // 0x4e00c7f..0x4e00c9b: basic block 6
    // xorps; movups [rax+0x10],xmm0; movups [rax],xmm0; mov [rbx],rax;
    // mov rdi,[rdi]; mov r8,[rdi+8]; test r8,r8; je L_0x4e00cd2 / jne L_0x4e00c9b
L_0x4e00c7f:
    {
        auto* rax_struct = (sub_4e00c00_rax*)rax;
        rax_struct->slots1[0] = 0;
        rax_struct->slots1[1] = 0;
        rax_struct->slots0[0] = 0;
        rax_struct->slots0[1] = 0;
        *(void**)rbx = (void*)rax;
        rdi = *(void**)rdi;
        r8 = *(void**)((uintptr_t)rdi + 8);
        if (r8 == nullptr) goto L_0x4e00cd2;
        goto L_0x4e00c9b;
    }

    // 0x4e00c9b..0x4e00cb3: basic block 7
    // mov r9,[rdi]; lock inc dword ptr [r8+0xC]; mov rcx,[rax+8];
    // mov [rax],r9; mov [rax+8],r8; test rcx,rcx; je L_0x4e00cd2 / jne L_0x4e00cb3
L_0x4e00c9b:
    {
        auto* r8_obj = (sub_4e00c00_rcx*)r8;
        auto* rax_struct = (sub_4e00c00_rax*)rax;
        r9 = *(void**)rdi;
        _InterlockedIncrement((volatile long*)((uintptr_t)r8_obj + 0xC));
        rcx = (uintptr_t)rax_struct->slots0[1];
        rax_struct->slots0[0] = r9;
        rax_struct->slots0[1] = r8;
        if (rcx == 0) goto L_0x4e00cd2;
        goto L_0x4e00cb3;
    }

    // 0x4e00cb3..0x4e00cb9: basic block 8
    // lock dec dword ptr [rcx+0xC]; jne L_0x4e00cd2 / je L_0x4e00cb9
L_0x4e00cb3:
    {
        auto* obj = (sub_4e00c00_rcx*)rcx;
        if (_InterlockedDecrement((volatile long*)&obj->weak_refcount) != 0)
            goto L_0x4e00cd2;
        goto L_0x4e00cb9;
    }

    // 0x4e00cb9..0x4e00cd2: basic block 9
    // mov rdx,[rcx]; mov rdx,[rdx+8]; mov rbx,rax; mov rax,rdx; call sub_eea6040;
    // mov rax,rbx; mov rdx,rsi; fallthrough L_0x4e00cd2
L_0x4e00cb9:
    {
        auto* obj = (sub_4e00c00_rcx*)rcx;
        void* vt = *(void**)obj;
        void* dtor = *(void**)((uintptr_t)vt + 8);
        rbx = (void*)rax;
        rax = (uintptr_t)sub_eea6040(obj, 0ULL);
        rax = (uintptr_t)rbx;
        rdx = (uintptr_t)rsi;
        goto L_0x4e00cd2;
    }

    // 0x4e00cd2..0x4e00cde: basic block 10
    // movups xmm0,[rdi+0x10]; movups [rax+0x10],xmm0; mov al,1; jmp short 0x4E00D0D
L_0x4e00cd2:
    {
        auto* rax_struct = (sub_4e00c00_rax*)rax;
        rax_struct->slots1[0] = *(void**)((uintptr_t)rdi + 0x10);
        rax_struct->slots1[1] = *(void**)((uintptr_t)rdi + 0x18);
        al = 1;
        rax = (rax & ~0xFFui64) | (uintptr_t)al;
        goto L_0x4e00d0d;
    }

    // 0x4e00cde..0x4e00cf7: basic block 11
    // mov rax,[rdx]; mov rcx,[r8]; mov [rax],rcx; xorps; movups [rax+8],xmm0;
    // mov rcx,[r8+0x10]; test rcx,rcx; je L_0x4e00cfb / jne L_0x4e00cf7
L_0x4e00cde:
    {
        auto* a1_rdx = (sub_4e00c00_rdx*)a1;
        auto* a2_r8 = (sub_4e00c00_r8*)a2;
        rax = (uintptr_t)a1_rdx->target;
        rcx = (uintptr_t)a2_r8->source;
        *(void***)(rax) = (void**)rcx;
        *(uint64_t*)(rax + 8) = 0;
        rcx = (uintptr_t)a2_r8->slots[0];
        if (rcx == 0) goto L_0x4e00cfb;
        goto L_0x4e00cf7;
    }

    // 0x4e00cf7..0x4e00cfb: basic block 12
    // lock inc dword ptr [rcx+8]
L_0x4e00cf7:
    {
        auto* obj = (sub_4e00c00_rcx*)rcx;
        _InterlockedIncrement((volatile long*)&obj->strong_refcount);
        goto L_0x4e00cfb;
    }

    // 0x4e00cfb..0x4e00d0d: basic block 13
    // mov rcx,[r8+8]; mov [rax+8],rcx; mov rcx,[r8+0x10]; mov [rax+0x10],rcx;
    // mov al,2; fallthrough L_0x4e00d0d
L_0x4e00cfb:
    {
        auto* a2_r8 = (sub_4e00c00_r8*)a2;
        auto* rax_struct = (sub_4e00c00_rax*)rax;
        rcx = (uintptr_t)a2_r8->refcounted;
        rax_struct->slots0[1] = (void*)rcx;
        rcx = (uintptr_t)a2_r8->slots[0];
        rax_struct->slots1[0] = (void*)rcx;
        al = 2;
        rax = (rax & ~0xFFui64) | (uintptr_t)al;
        goto L_0x4e00d0d;
    }

    // 0x4e00d0d..0x4e00d13: basic block 14
    // mov rcx,[rdx]; mov [rcx+0x18],al; fallthrough L_0x4e00d13
L_0x4e00d0d:
    {
        auto* a1_rdx = (sub_4e00c00_rdx*)a1;
        auto* rcx_obj = (sub_4e00c00_rcx*)a1_rdx->target;
        rcx_obj->type_tag = al;
        goto L_0x4e00d13;
    }

    // 0x4e00d13..0x4e00d1d: basic block 15 (epilogue)
    // ret (return rax)
L_0x4e00d13:
    return rax;

    // 0x4e00d1d..0x4e00d32: basic block 16
    // mov ecx,0x20; mov r14,rax; call sub_9bc830; mov rax,r14; jmp L_0x4e00c7f
L_0x4e00d1d:
    {
        uintptr_t saved_rax = rax;
        (void)sub_9bc830(0x20u);
        rax = saved_rax;
        goto L_0x4e00c7f;
    }
}

} // namespace native::helpers
