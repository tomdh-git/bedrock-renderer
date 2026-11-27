// LIFT 0x67c7020 size 0x11f 1.26.62.01 sub_67c7020
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/helpers/sub_67c7020.h"

#include <cstdint>
#include <cstddef>
#include <intrin.h>

static_assert(sizeof(native::helpers::sub_67c7020_rdx) >= 0x30,
              "sub_0x67c7020 node layout covers the 0x30-byte allocation");
static_assert(offsetof(native::helpers::sub_67c7020_rsi, f8) == 0x8,
              "sub_0x67c7020 result-pair inserted flag at +0x8");

namespace native::helpers {

LIFT_FN(sub_67c7020, "sub_67c7020", 0x67c7020, sub_67c7020, nullptr);

// Boundary callees from the disassembly of [0x67c7020, 0x67c713f).
// 0xa4c70  (stl)   : links the new node; rcx=map, rdx=hint, r8=node, void return.
// 0xa4ea0  (stl)   : _Tree length-error handler; rcx=map, does not return.
// 0x9bc830 (alloc) : allocation-failure handler; rcx=size, does not return.
extern "C" void sub_a4c70(void* map, void* hint, void* node);
extern "C" __declspec(noreturn) void sub_a4ea0(void* map);
Boundary<std::uint64_t, std::uint64_t> sub_9bc830("sub_9bc830");

// 0xeea6040 is the vendor thunk held in the data slot at 0xF99FFA0; the
// allocator object comes from the global at 0x1233E1A8. Args: rcx=allocator,
// rdx=0x30. The two vtable reads before the call are dead reads.
using Eea6040Fn = void* (*)(void*, std::uint32_t);
static constexpr std::uintptr_t kAllocatorGlobal = 0x1233E1A8;
static constexpr std::uintptr_t kAllocatorSlot   = 0xF99FFA0;
static constexpr std::uint64_t  kTreeMaxSize     = 0x0555555555555555ull;
static constexpr std::uint32_t  kNodeSize        = 0x30;

// Verbatim call instructions (rdis `fn` output).
#if 0
0x67c70c1  call qword ptr [0xF99FFA0]
0x67c710a  call 0xA4C70
0x67c7132  call 0x9BC830
0x67c7139  call 0xA4EA0
#endif

sub_67c7020_rsi* sub_67c7020(sub_67c7020_rcx* a0, sub_67c7020_rsi* a1,
                             const std::uint8_t* a2) {
    sub_67c7020_rdx* r15 = nullptr;   // head
    sub_67c7020_rdx* rdx = nullptr;   // cursor
    sub_67c7020_rdx* r12 = nullptr;   // last node
    sub_67c7020_rdx* rbx = nullptr;   // candidate, then new node
    std::uint32_t ebp = 0;
    std::uint32_t idx = 0;
    std::uint8_t al = 0;
    std::uint8_t cl = 0;
    bool inserted = false;
    std::uint64_t oomRet = 0;
    sub_67c7020_rsp stk{};

    // 0x67c7020..0x67c7046: basic block 0
    // 0x67c702e mov r14,r8 / 0x67c7031 mov rsi,rdx / 0x67c7034 mov rdi,rcx
    // 0x67c7037 mov r15,[rcx] / 0x67c703a mov rdx,[r15+8] / 0x67c703e xor ebp,ebp
    // 0x67c7040 cmp byte ptr [rdx+0x19],0 / 0x67c7044 je short 0x67C7054
    L_0x67c7020:;
    r15 = reinterpret_cast<sub_67c7020_rdx*>(a0->f0);
    rdx = reinterpret_cast<sub_67c7020_rdx*>(r15->f8);
    ebp = 0;
    if (rdx->f19 == 0) goto L_0x67c7054;

    // 0x67c7046..0x67c7052: basic block 1
    // 0x67c7046 mov r12,rdx / 0x67c7049 mov rbx,r15
    // 0x67c704c cmp byte ptr [rbx+0x19],0 / 0x67c7050 jne short 0x67C709A
    L_0x67c7046:;
    r12 = rdx;
    rbx = r15;
    if (r15->f19 != 0) goto L_0x67c709a;

    // 0x67c7052..0x67c7054: basic block 2
    // 0x67c7052 jmp short 0x67C708D
    L_0x67c7052:;
    goto L_0x67c708d;

    // 0x67c7054..0x67c7060: basic block 3
    // 0x67c7054 movzx eax,byte ptr [r14] / 0x67c7058 mov rbx,r15 / 0x67c705b nop
    L_0x67c7054:;
    al = *a2;
    rbx = r15;

    // 0x67c7060..0x67c707f: basic block 4
    // 0x67c7060 mov r12,rdx / 0x67c7063 movzx ecx,byte ptr [rdx+0x1C]
    // 0x67c7067 xor edx,edx / 0x67c7069 cmp cl,al / 0x67c706b setb dl
    // 0x67c706e cmovae rbx,r12 / 0x67c7072 shl edx,4 / 0x67c7075 mov rdx,[r12+rdx]
    // 0x67c7079 cmp byte ptr [rdx+0x19],0 / 0x67c707d je short 0x67C7060
    L_0x67c7060:;
    r12 = rdx;
    cl = r12->f1c;
    idx = (cl < al) ? 1u : 0u;
    if (cl >= al) rbx = r12;
    rdx = *reinterpret_cast<sub_67c7020_rdx**>(
        reinterpret_cast<std::uint8_t*>(r12) + (idx << 4));
    if (rdx->f19 == 0) goto L_0x67c7060;

    // 0x67c707f..0x67c708d: basic block 5
    // 0x67c707f xor ebp,ebp / 0x67c7081 cmp cl,al / 0x67c7083 setae bpl
    // 0x67c7087 cmp byte ptr [rbx+0x19],0 / 0x67c708b jne short 0x67C709A
    L_0x67c707f:;
    ebp = (cl >= al) ? 1u : 0u;
    if (rbx->f19 != 0) goto L_0x67c709a;

    // 0x67c708d..0x67c709a: basic block 6
    // 0x67c708d movzx eax,byte ptr [r14] / 0x67c7091 cmp al,[rbx+0x1C]
    // 0x67c7094 jae 0x67C7129
    L_0x67c708d:;
    al = *a2;
    if (al >= rbx->f1c) goto L_0x67c7129;

    // 0x67c709a..0x67c70ae: basic block 7
    // 0x67c709a mov rax,0x555555555555555 / 0x67c70a4 cmp [rdi+8],rax
    // 0x67c70a8 je 0x67C7139
    L_0x67c709a:;
    if (a0->f8 == kTreeMaxSize) goto L_0x67c7139;

    // 0x67c70ae..0x67c70cf: basic block 8
    // 0x67c70ae mov rcx,[0x1233E1A8] / 0x67c70b5 mov rax,[rcx]
    // 0x67c70b8 mov rax,[rax+8] / 0x67c70bc mov edx,0x30
    // 0x67c70c1 call qword ptr [0xF99FFA0] / 0x67c70c7 mov rbx,rax
    // 0x67c70ca test rax,rax / 0x67c70cd je short 0x67C712D
    L_0x67c70ae:;
    {
        void* allocator = *reinterpret_cast<void**>(
            reinterpret_cast<void*>(kAllocatorGlobal));
        void* vtable = *reinterpret_cast<void**>(allocator);
        std::uint64_t deadSlot = *reinterpret_cast<std::uint64_t*>(
            reinterpret_cast<std::uint8_t*>(vtable) + 8);
        (void)deadSlot;
        Eea6040Fn allocFn = reinterpret_cast<Eea6040Fn>(
            *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<void*>(kAllocatorSlot)));
        rbx = reinterpret_cast<sub_67c7020_rdx*>(
            allocFn(allocator, static_cast<std::uint32_t>(kNodeSize)));
    }
    if (rbx == nullptr) goto L_0x67c712d;

    // 0x67c70cf..0x67c7111: basic block 9
    // 0x67c70cf movzx eax,byte ptr [r14] / 0x67c70d3 mov [rbx+0x1C],al
    // 0x67c70d6 mov qword ptr [rbx+0x20],0 / 0x67c70de mov dword ptr [rbx+0x28],0
    // 0x67c70e5 mov [rbx],r15 / 0x67c70e8 mov [rbx+8],r15 / 0x67c70ec mov [rbx+0x10],r15
    // 0x67c70f0 mov word ptr [rbx+0x18],0 / 0x67c70f6 mov [rsp+0x20],r12
    // 0x67c70fb mov [rsp+0x28],ebp / 0x67c70ff lea rdx,[rsp+0x20]
    // 0x67c7104 mov rcx,rdi / 0x67c7107 mov r8,rbx / 0x67c710a call 0xA4C70
    // 0x67c710f mov al,1
    L_0x67c70cf:;
    al = *a2;
    rbx->f1c = al;
    rbx->f20 = 0;
    rbx->f28 = 0;
    rbx->f0 = r15;
    rbx->f8 = r15;
    rbx->f10 = r15;
    rbx->f18 = 0;
    rbx->f19 = 0;
    stk.f20 = r12;
    stk.f28 = ebp;
    sub_a4c70(a0, &stk.f20, rbx);
    inserted = true;

    // 0x67c7111..0x67c7129: basic block 10
    // 0x67c7111 mov [rsi],rbx / 0x67c7114 mov [rsi+8],al / 0x67c7117 mov rax,rsi
    // 0x67c711a add rsp,0x30 / 0x67c711e pop rbx / 0x67c711f pop rbp / 0x67c7120 pop rdi
    // 0x67c7121 pop rsi / 0x67c7122 pop r12 / 0x67c7124 pop r14 / 0x67c7126 pop r15
    // 0x67c7128 ret
    L_0x67c7111:;
    a1->f0 = rbx;
    a1->f8 = inserted ? std::uint8_t{1} : std::uint8_t{0};
    return a1;

    // 0x67c7129..0x67c712d: basic block 11
    // 0x67c7129 xor eax,eax / 0x67c712b jmp short 0x67C7111
    L_0x67c7129:;
    inserted = false;
    goto L_0x67c7111;

    // 0x67c712d..0x67c7139: basic block 12
    // 0x67c712d mov ecx,0x30 / 0x67c7132 call 0x9BC830 / 0x67c7137 jmp short 0x67C70CF
    L_0x67c712d:;
    oomRet = sub_9bc830(static_cast<std::uint64_t>(kNodeSize));
    (void)oomRet;
    goto L_0x67c70cf;

    // 0x67c7139..0x67c713f: basic block 13
    // 0x67c7139 call 0xA4EA0 / 0x67c713e int3 / 0x67c713f int3
    L_0x67c7139:;
    sub_a4ea0(a0);
    __assume(false);
}

} // namespace native::helpers
