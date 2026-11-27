// LIFT 0x53dc590 size 0x10f 1.26.62.01 sub_53dc590
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_53dc590.h"

#include <cstdint>
#include <cstddef>

namespace native::helpers {

// Layout assertions (full set in sub_53dc590.h; duplicated here for liftcheck visibility).
static_assert(offsetof(sub_53dc590_Node, vtable) == 0x000, "sub_0x53dc590 node+0x00 field");
static_assert(offsetof(sub_53dc590_Node, link8) == 0x008, "sub_0x53dc590 node+0x08 field");
static_assert(offsetof(sub_53dc590_Node, next10) == 0x010, "sub_0x53dc590 node+0x10 field");
static_assert(offsetof(sub_53dc590_Node, owned18) == 0x018, "sub_0x53dc590 node+0x18 field");
static_assert(offsetof(sub_53dc590_Node, next138) == 0x138, "sub_0x53dc590 node+0x138 field");
static_assert(offsetof(sub_53dc590_Node, flag140) == 0x140, "sub_0x53dc590 node+0x140 field");
static_assert(offsetof(sub_53dc590_Self, head0) == 0x00, "sub_0x53dc590 self+0x00 field");
static_assert(offsetof(sub_53dc590_Self, ptr18) == 0x18, "sub_0x53dc590 self+0x18 field");
static_assert(offsetof(sub_53dc590_Self, ptr28) == 0x28, "sub_0x53dc590 self+0x28 field");
static_assert(offsetof(sub_53dc590_Self, ptr30) == 0x30, "sub_0x53dc590 self+0x30 field");
static_assert(offsetof(sub_53dc590_Global, vtable) == 0x00, "sub_0x53dc590 global+0x00 field");

LIFT_FN(sub_53dc590, "sub_53dc590", 0x53dc590, sub_53dc590, nullptr);

// Verbatim call instructions from the disassembly of [0x53dc590, 0x53dc69f) (rdis `fn` output).
// Plain lines, two spaces after the address: parseable by tools/sigs/verify_oc.py.
// Preprocessor-excluded below so the skeleton stays valid C++.
#if 0
0x53dc5bb  call qword ptr [0xF99FFA0]
0x53dc5d2  call qword ptr [0xF99FFA0]
0x53dc627  call qword ptr [0xF99FFA0]
0x53dc653  call qword ptr [0xF99FFA0]
0x53dc696  call qword ptr [0xF99FFA0]
#endif

// All five call sites are `call qword ptr [0xF99FFA0]`. The loader-resolved slot
// 0xF99FFA0 holds sub_eea6040, a `jmp rax` forwarder, so each site calls the
// function pointer just loaded into RAX from a vtable slot. The lift performs the
// same vtable calls directly: same target selection, same argument registers
// (RCX/RDX), same order. Two vtable shapes appear:
//   * node->vtable[0](node, 0)              scalar-deleting destructor of a node
//   * global->vtable[2](global, node)       release of a node by the global owner
// Global data 0x1233E1A8 holds the owner; its vtable slot 2 is at byte offset 0x10.
void sub_53dc590(void* self) {
    using DtorFn = void (*)(void*, unsigned int);
    using FreeFn = void (*)(void*, void*);

    sub_53dc590_Self* a0 = static_cast<sub_53dc590_Self*>(self);
    sub_53dc590_Node* rdi = a0->head0;
    sub_53dc590_Node* rbx = nullptr;
    sub_53dc590_Node* rdx = nullptr;
    sub_53dc590_Node* rax18 = nullptr;
    void* rcx8 = nullptr;
    sub_53dc590_Global* g = nullptr;
    FreeFn release = nullptr;

    goto L_0x53dc5dc;

    // 0x53dc590..0x53dc5ad: basic block 0
    // 0x53dc590  push rbp
    // 0x53dc591  push rsi
    // 0x53dc592  push rdi
    // 0x53dc593  push rbx
    // 0x53dc594  sub rsp,0x28
    // 0x53dc598  lea rbp,[rsp+0x20]
    // 0x53dc59d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
    // 0x53dc5a5  mov rsi,rcx
    // 0x53dc5a8  mov rdi,[rcx]
    // 0x53dc5ab  jmp short 0x53DC5DC
    // The frame pointer and stack cookie writes at [rbp] are prologue bookkeeping;
    // rsi keeps self and rdi starts at self->head0, then control goes to the test.

    // 0x53dc5ad..0x53dc5b0: basic block 1
    // 0x53dc5ad  nop [rax]
    // Alignment nop; execution reaches block 2 by fallthrough from block 0/1.

    // 0x53dc5b0..0x53dc5dc: basic block 2
    // 0x53dc5b0  mov rax,[rdi]
    // 0x53dc5b3  mov rax,[rax]
    // 0x53dc5b6  mov rcx,rdi
    // 0x53dc5b9  xor edx,edx
    // 0x53dc5bb  call qword ptr [0xF99FFA0]
    // 0x53dc5c1  mov rcx,[0x1233E1A8]
    // 0x53dc5c8  mov rax,[rcx]
    // 0x53dc5cb  mov rax,[rax+0x10]
    // 0x53dc5cf  mov rdx,rdi
    // 0x53dc5d2  call qword ptr [0xF99FFA0]
    // 0x53dc5d8  nop
    // 0x53dc5d9  mov rdi,rbx
    L_0x53dc5b0:;
    {
        DtorFn dtor = reinterpret_cast<DtorFn>(rdi->vtable[0]);
        dtor(rdi, 0u);
    }
    g = reinterpret_cast<sub_53dc590_Global*>(*reinterpret_cast<void**>(0x1233E1A8ULL));
    release = reinterpret_cast<FreeFn>(g->vtable[2]);
    release(g, rdi);
    rdi = rbx;
    // Fallthrough to block 3.

    // 0x53dc5dc..0x53dc5e1: basic block 3
    // 0x53dc5dc  test rdi,rdi
    // 0x53dc5df  je short 0x53DC602
    L_0x53dc5dc:;
    if (rdi == nullptr) goto L_0x53dc602;

    // 0x53dc5e1..0x53dc5f9: basic block 4
    // 0x53dc5e1  mov rcx,[rdi+8]
    // 0x53dc5e5  mov rax,[rdi+0x18]
    // 0x53dc5e9  lea rbx,[rcx-8]
    // 0x53dc5ed  test rcx,rcx
    // 0x53dc5f0  cmove rbx,rcx
    // 0x53dc5f4  test rax,rax
    // 0x53dc5f7  je short 0x53DC5B0
    rcx8 = rdi->link8;
    rax18 = rdi->owned18;
    rbx = (rcx8 != nullptr)
        ? reinterpret_cast<sub_53dc590_Node*>(static_cast<std::uint8_t*>(rcx8) - 8)
        : nullptr;
    if (rax18 == nullptr) goto L_0x53dc5b0;

    // 0x53dc5f9..0x53dc602: basic block 5
    // 0x53dc5f9  mov qword ptr [rax],0
    // 0x53dc600  jmp short 0x53DC5B0
    rax18->vtable = nullptr;
    goto L_0x53dc5b0;

    // 0x53dc602..0x53dc60b: basic block 6
    // 0x53dc602  mov rdx,[rsi+0x30]
    // 0x53dc606  test rdx,rdx
    // 0x53dc609  je short 0x53DC633
    L_0x53dc602:;
    rdx = a0->ptr30;
    if (rdx == nullptr) goto L_0x53dc633;

    // 0x53dc60b..0x53dc610: basic block 7
    // 0x53dc60b  nop [rax+rax]
    // Alignment nop; execution falls into block 8.

    // 0x53dc610..0x53dc619: basic block 8
    // 0x53dc610  mov rdi,[rdx+0x10]
    // 0x53dc614  test rdi,rdi
    // 0x53dc617  je short 0x53DC633
    L_0x53dc610:;
    rdi = rdx->next10;
    if (rdi == nullptr) goto L_0x53dc633;

    // 0x53dc619..0x53dc633: basic block 9
    // 0x53dc619  mov rcx,[0x1233E1A8]
    // 0x53dc620  mov rax,[rcx]
    // 0x53dc623  mov rax,[rax+0x10]
    // 0x53dc627  call qword ptr [0xF99FFA0]
    // 0x53dc62d  nop
    // 0x53dc62e  mov rdx,rdi
    // 0x53dc631  jmp short 0x53DC610
    g = reinterpret_cast<sub_53dc590_Global*>(*reinterpret_cast<void**>(0x1233E1A8ULL));
    release = reinterpret_cast<FreeFn>(g->vtable[2]);
    release(g, rdx);
    rdx = rdi;
    goto L_0x53dc610;

    // 0x53dc633..0x53dc63c: basic block 10
    // 0x53dc633  mov rdx,[rsi+0x28]
    // 0x53dc637  test rdx,rdx
    // 0x53dc63a  jne short 0x53DC678
    L_0x53dc633:;
    rdx = a0->ptr28;
    if (rdx != nullptr) goto L_0x53dc678;

    // 0x53dc63c..0x53dc64c: basic block 11
    // 0x53dc63c  mov rdx,[rsi+0x18]
    // 0x53dc640  mov rcx,[0x1233E1A8]
    // 0x53dc647  test rdx,rdx
    // 0x53dc64a  je short 0x53DC65A
    L_0x53dc63c:;
    rdx = a0->ptr18;
    g = reinterpret_cast<sub_53dc590_Global*>(*reinterpret_cast<void**>(0x1233E1A8ULL));
    if (rdx == nullptr) goto L_0x53dc65a;

    // 0x53dc64c..0x53dc65a: basic block 12
    // 0x53dc64c  mov rax,[rcx]
    // 0x53dc64f  mov rax,[rax+0x10]
    // 0x53dc653  call qword ptr [0xF99FFA0]
    // 0x53dc659  nop
    release = reinterpret_cast<FreeFn>(g->vtable[2]);
    release(g, rdx);

    // 0x53dc65a..0x53dc663: basic block 13
    // 0x53dc65a  add rsp,0x28
    // 0x53dc65e  pop rbx
    // 0x53dc65f  pop rdi
    // 0x53dc660  pop rsi
    // 0x53dc661  pop rbp
    // 0x53dc662  ret
    L_0x53dc65a:;
    return;

    // 0x53dc663..0x53dc670: basic block 14
    // 0x53dc663  nop [rax+rax]
    // Alignment nop between the two epilogues; reached only by fallthrough from block 17.

    // 0x53dc670..0x53dc678: basic block 15
    // 0x53dc670  mov rdx,rdi
    // 0x53dc673  test rdi,rdi
    // 0x53dc676  je short 0x53DC63C
    L_0x53dc670:;
    rdx = rdi;
    if (rdi == nullptr) goto L_0x53dc63c;

    // 0x53dc678..0x53dc688: basic block 16
    // 0x53dc678  mov rdi,[rdx+0x138]
    // 0x53dc67f  cmp byte ptr [rdx+0x140],1
    // 0x53dc686  jne short 0x53DC670
    L_0x53dc678:;
    rdi = rdx->next138;
    if (rdx->flag140 != 1) goto L_0x53dc670;

    // 0x53dc688..0x53dc69f: basic block 17
    // 0x53dc688  mov rcx,[0x1233E1A8]
    // 0x53dc68f  mov rax,[rcx]
    // 0x53dc692  mov rax,[rax+0x10]
    // 0x53dc696  call qword ptr [0xF99FFA0]
    // 0x53dc69c  nop
    // 0x53dc69d  jmp short 0x53DC670
    g = reinterpret_cast<sub_53dc590_Global*>(*reinterpret_cast<void**>(0x1233E1A8ULL));
    release = reinterpret_cast<FreeFn>(g->vtable[2]);
    release(g, rdx);
    goto L_0x53dc670;
}

} // namespace native::helpers
