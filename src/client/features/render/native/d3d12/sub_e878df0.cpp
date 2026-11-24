// LIFT 0xe878df0 size 0x1e2 1.26.62.01 sub_e878df0
#include <atomic>
#include <cstdint>
#include <string>
#include <vector>
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e878df0.h"

static_assert(sizeof(native::d3d12::Slot16State) == 0x40, "e878df0: Slot16State size must be 0x40");

namespace native {
namespace d3d12 {

extern "C" void* sub_e878df0(void* a0, void* a1) {
    // a0 = rcx (state 0), a1 = rdx (state 1); both are Slot16State (0x40 bytes)
    // Return: rax = a0
    Slot16State* s0 = reinterpret_cast<Slot16State*>(a0);
    Slot16State* s1 = reinterpret_cast<Slot16State*>(a1);

    // 0xe878df0..0xe878e3c : Prologue + allocate 0x48 node
    // push rbp; push r14; push rsi; push rdi; push rbx; sub rsp,0x50;
    // lea rbp,[rsp+0x50]; movaps [rbp-0x10],xmm6;
    // mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE;   (EH cookie, not observable)
    // mov rdi,rdx; mov rsi,rcx;
    // mov eax,[rdx]; mov [rcx],eax;                   // a0+0x00 = a1+0x00 (dword)
    // xorps xmm6,xmm6;
    // movups [rcx+8],xmm6;                            // a0+0x08 = 0, a0+0x10 = 0 (16 bytes)
    s0->field00 = s1->field00;                        // 0xe878e11  mov eax,[rdx]
                                                      // 0xe878e13  mov [rcx],eax
    s0->field08 = nullptr;                            // 0xe878e15  xorps xmm6,xmm6
    s0->field10 = nullptr;                            // 0xe878e18  movups [rcx+8],xmm6

    // Allocate node: 0x48 bytes via vendor thunk [0xF99FFA0]
    // mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; mov edx,0x48;
    // call qword ptr [0xF99FFA0];                     // 0xe878e2f  call qword ptr [0xF99FFA0]
    void* allocator = *reinterpret_cast<void**>(kDataSlotAllocator);
    allocator = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(allocator) + 8);
    void* rbx = boundary::thunk_f99ffa0(allocator, 0x48);

    // 0xe878e38  test rax,rax / 0xe878e3b  je 0xE878F99
    if (rbx == nullptr) {
        // loc_e878f99: 0xe878f99  mov ecx,0x48 / 0xe878f9e  call 0x9BC830 / 0xe878fa3  jmp 0xE878E41
        boundary::sub_9bc830(0x48);                   // 0xe878f9e  call 0x9BC830  (noreturn)
    }

    // 0xe878e41 : loc_e878e41
    // lea rax,[rsi+8]; mov [rbp-0x28],rax;            // save &a0+0x8
    // mov [rbx],rbx; mov [rbx+8],rbx;                 // node self-link +0x0,+0x8
    // mov [rsi+8],rbx;                                // a0+0x08 = rbx
    // lea rax,[rsi+0x18]; mov [rbp-0x20],rax;         // save &a0+0x18
    *reinterpret_cast<void**>(rbx) = rbx;             // 0xe878e49  mov [rbx],rbx
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(rbx) + 8) = rbx; // 0xe878e4c  mov [rbx+8],rbx
    s0->field08 = rbx;                                // 0xe878e50  mov [rsi+8],rbx

    // 0xe878e5c  movups [rsi+0x18],xmm6;              // a0+0x18 = 0, a0+0x20 = 0 (16 bytes)
    // 0xe878e60  mov qword ptr [rsi+0x28],0;          // a0+0x28 = 0
    s0->field18 = nullptr;                            // 0xe878e5c  movups [rsi+0x18],xmm6
    s0->field20 = nullptr;                            // 0xe878e5c  movups [rsi+0x18],xmm6
    s0->field28 = nullptr;                            // 0xe878e60  mov qword ptr [rsi+0x28],0

    // Allocate buffer: 0x80 bytes via vendor thunk [0xF99FFA0]
    // mov rcx,[0x1233E1A8]; mov rax,[rcx]; mov rax,[rax+8]; mov edx,0x80;
    // call qword ptr [0xF99FFA0];                     // 0xe878e7b  call qword ptr [0xF99FFA0]
    // nop
    // mov r14,rax
    allocator = *reinterpret_cast<void**>(kDataSlotAllocator);
    allocator = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(allocator) + 8);
    void* r14 = boundary::thunk_f99ffa0(allocator, 0x80);

    // 0xe878e85  test rax,rax / 0xe878e88  je 0xE878FA8
    if (r14 == nullptr) {
        // loc_e878fa8: 0xe878fa8  mov ecx,0x80 / 0xe878fad  call 0x9BC830 / 0xe878fb3  jmp 0xE878E8E
        boundary::sub_9bc830(0x80);                   // 0xe878fad  call 0x9BC830  (noreturn)
    }

    // 0xe878e8e : loc_e878e8e — grow check
    // mov rcx,[rsi+0x18]; mov rdx,[rsi+0x28]; sub rdx,rcx;   // used = a0+0x28 - a0+0x18 = 0
    // je short 0xE878EC5                                      // used == 0 -> skip grow
    uint64_t used = reinterpret_cast<uintptr_t>(s0->field28) - reinterpret_cast<uintptr_t>(s0->field18); // = 0

    if (used != 0) {
        // Dead path (used is always 0): 0xe878e9b..0xe878ec0
        if (used < 0x1000) {
            // 0xe878e9b  cmp rdx,0x1000 / 0xe878ea2  jb short 0xE878EC0
            // 0xe878ec0: call 0xE935700 (rcx=a0+0x18=0, rdx=used)
            sub_e935700(s0->field18, used);           // 0xe878ec0  call 0xE935700
        } else {
            // 0xe878ea4..0xe878eb3: complex grow path
            // mov rax,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,rax; cmp rcx,0x20; jae 0xE878FB8
            uintptr_t rcx_val = reinterpret_cast<uintptr_t>(s0->field18) - 8;
            uintptr_t rax_val = *reinterpret_cast<uintptr_t*>(rcx_val);
            rcx_val = rcx_val - rax_val;
            if (rcx_val >= 0x20) {
                // 0xe878eb3  jae 0xE878FB8 — inline fail path
                // 0xe878fb8  mov qword ptr [rsp+0x20],0;
                // 0xe878fc1  xor ecx,ecx; 0xe878fc3  xor edx,edx;
                // 0xe878fc5  xor r8d,r8d; 0xe878fc8  xor r9d,r9d;
                // 0xe878fcb  call qword ptr [0xF9A8C78];   // std::terminate (IAT, noreturn)
                // 0xe878fd1  int3
                boundary::terminate_f9a8c78();        // 0xe878fcb  call qword ptr [0xF9A8C78] (noreturn)
            }
            // 0xe878eb9  add rdx,0x27; 0xe878ebd  mov rcx,rax;
            // 0xe878ec0: call 0xE935700 (rcx=rax, rdx=used+0x27)
            used += 0x27;
            sub_e935700(reinterpret_cast<void*>(rax_val), used); // 0xe878ec0  call 0xE935700
        }
    }

    // 0xe878ec5 : loc_e878ec5 — install new buffer
    // mov [rsi+0x18],r14;                     // a0+0x18 = r14
    // mov rax,r14; sub rax,0xFFFFFFFFFFFFFF80; // rax = r14 + 0x80
    // mov [rsi+0x20],rax; mov [rsi+0x28],rax;  // a0+0x20 = r14+0x80, a0+0x28 = r14+0x80
    s0->field18 = r14;                            // 0xe878ec5  mov [rsi+0x18],r14
    void* r14_end = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(r14) + 0x80);
    s0->field20 = r14_end;                        // 0xe878ed0  mov [rsi+0x20],rax  (rax = r14+0x80)
    s0->field28 = r14_end;                        // 0xe878ed4  mov [rsi+0x28],rax

    // 0xe878ed8..0xe878f13: poison fill [r14+0x00..0x78] = rbx (16 qwords)
    for (int i = 0; i < 16; ++i) {
        *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(r14) + i * 8) = rbx;
    }                                               // 0xe878ed8..0xe878f13  mov [r14+off],rbx x16

    // 0xe878f17..0xe878f83: swap/copy state fields between a0 and a1
    // +0x08 swap, +0x10 swap, +0x18 swap, +0x20 swap, +0x28 swap
    void* tmp;
    tmp = s0->field08; s0->field08 = s1->field08; s1->field08 = tmp; // 0xe878f17..0xe878f23
    tmp = s0->field10; s0->field10 = s1->field10; s1->field10 = tmp; // 0xe878f27..0xe878f33
    tmp = s0->field18; s0->field18 = s1->field18; s1->field18 = tmp; // 0xe878f37..0xe878f43
    tmp = s0->field20; s0->field20 = s1->field20; s1->field20 = tmp; // 0xe878f47..0xe878f53
    tmp = s0->field28; s0->field28 = s1->field28; s1->field28 = tmp; // 0xe878f57..0xe878f63

    // +0x30: a0+0x30 = a1+0x30 (old); a1+0x30 = 7
    // +0x38: a0+0x38 = a1+0x38 (old); a1+0x38 = 8
    uint64_t v30 = s1->field30;                   // 0xe878f67  mov rax,[rdi+0x30]
    s1->field30 = 7;                              // 0xe878f6b  mov qword ptr [rdi+0x30],7
    s0->field30 = v30;                            // 0xe878f73  mov [rsi+0x30],rax
    uint64_t v38 = s1->field38;                   // 0xe878f77  mov rax,[rdi+0x38]
    s1->field38 = 8;                              // 0xe878f7b  mov qword ptr [rdi+0x38],8
    s0->field38 = v38;                            // 0xe878f83  mov [rsi+0x38],rax

    // 0xe878f87  mov rax,rsi  ; return a0
    // 0xe878f8a..0xe878f98: epilogue (movaps xmm6,[rbp-0x10]; add rsp,0x50; pop rbx,rdi,rsi,r14,rbp; ret)
    return a0;                                      // 0xe878f87  mov rax,rsi / ... / 0xe878f98  ret
}

// LIFT_FN registry entry
LIFT_FN(sub_e878df0, "sub_e878df0", 0xe878df0, sub_e878df0, nullptr);

} // namespace d3d12
} // namespace native

#if 0
// Verbatim call quotes for liftcheck (verify_oc parses plain lines)
0xe878e2f  call qword ptr [0xF99FFA0]
0xe878e7b  call qword ptr [0xF99FFA0]
0xe878ec0  call 0xE935700
0xe878f9e  call 0x9BC830
0xe878fad  call 0x9BC830
0xe878fcb  call qword ptr [0xF9A8C78]
#endif
