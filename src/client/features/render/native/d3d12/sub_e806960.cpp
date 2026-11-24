// LIFT 0xe806960 size 0x11c 1.26.62.01 sub_e806960
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e806960.h"
#include "client/features/render/native/d3d12/sub_e834520.h"

#include <cstdint>
#include <cstddef>
#include <cstring>

static_assert(sizeof(void*) == 8, "e806960 x64");

// verbatim call quotes (plain lines for verify_oc)
#if 0
0xe806986  call 0xE834520
0xe8069b5  call 0xE834330
0xe806a2c  call 0xEEC6DE0
0xe806a3e  call 0xEEC6EC0
0xe806a58  call 0xEEC6EC0
#endif

namespace native::d3d12 {

native::Footprint sub_e806960_footprint(void* out, const void*) {
    return native::Footprint{{out, 0x20}};
}

LIFT_FN(sub_e806960, "sub_e806960", 0xe806960, sub_e806960, sub_e806960_footprint);

} // namespace native::d3d12

extern "C" void* sub_e806960(void* out, const void* src) {
    // 0xe806960..0xe806986
    // push rbp; push r15; push r14; push rsi; push rdi; push rbx; sub rsp,0x48;
    // lea rbp,[rsp+0x40]; mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE (frame cookie);
    // mov rsi,rcx (out -> rsi); movzx edx,word ptr [rdx] (uint16 at src+0x0, zero-extended);
    // lea rdi,[rbp-0x20]; mov rcx,rdi
    native::d3d12::Str32 tmp;                                                    // scratch string at rbp-0x20
    std::uint32_t v = *reinterpret_cast<const std::uint16_t*>(src);              // 0xe80697c movzx edx,word ptr [rdx]
    // 0xe806986 call 0xE834520 -> native::d3d12::sub_e834520(&tmp, v)
    native::d3d12::sub_e834520(&tmp, v);                                         // writes tmp.data[16], tmp.size, tmp.cap

    // 0xe80698b..0xe8069bb
    // mov rax,[rbp-0x10] (tmp.size); mov rcx,[rbp-8] (tmp.cap); mov rdx,rcx; sub rdx,rax; cmp rdx,5; jae loc_e8069c0
    std::size_t size = tmp.size;                                                 // 0xe80698b mov rax,[rbp-0x10]
    std::size_t cap = tmp.cap;                                                   // 0xe80698f mov rcx,[rbp-8]
    if (cap - size < 5u) {                                                       // 0xe806999 cmp rdx,5 ; 0xe80699d jae loc_e8069c0
        // 0xe80699f lea r8,[0xF848D0E] ("LIbo: ");
        // 0xe8069a6 lea rcx,[rbp-0x20]; 0xe8069aa mov edx,5; 0xe8069af mov r9d,5
        // 0xe8069b5 call 0xE834330 -> sub_e834330(&tmp, 5, (void*)0xF848D0E, (void*)5) ; updates tmp in place
        native::d3d12::sub_e834330(&tmp, 5, reinterpret_cast<void*>(0xF848D0Eui64), reinterpret_cast<void*>(5)); // 0xe8069b5 call 0xE834330
        // 0xe8069ba nop ; 0xe8069bb jmp loc_e806a5d -> falls into the store below
    } else {
        // 0xe8069c0..0xe806a58
        // lea rdx,[rax+5]; mov [rbp-0x10],rdx  (tmp.size = size + 5)
        tmp.size = size + 5;                                                     // 0xe8069c0 lea rdx,[rax+5] ; 0xe8069c4 mov [rbp-0x10],rdx
        std::uintptr_t r15;
        // mov rdx,[rbp-0x20] (tmp.data); mov rbx,rdi (rbp-0x20 == &tmp); cmovae rbx,rdx -> base
        char* base = reinterpret_cast<char*>(&tmp);                              // 0xe8069d0 mov rbx,rdi  (rbx = &tmp when cap < 8)
        if (cap >= 8) base = tmp.data;                                           // 0xe8069d3 cmovae rbx,rdx
        // lea r8,[0xF848D18]; cmp rbx,r8; setae r8b
        // lea r14,[0xF848D0E] ("LIbo: "); lea r9,[rbx+rax*2]; cmp r9,r14; setb r9b
        // or r9b,r8b; mov r15d,5; jne loc_e806a12
        if (((std::uintptr_t)base >= 0xF848D18ui64) ||                           // 0xe8069de cmp rbx,[0xF848D18] ; 0xe8069e1 setae r8b
            ((std::uintptr_t)base + size * 2 < 0xF848D0Eui64)) {                 // 0xe8069f0 cmp r9,r14 ; 0xe8069f3 setb r9b ; 0xe8069f7 or
            r15 = 5;                                                             // 0xe8069fa mov r15d,5 ; 0xe806a00 jne loc_e806a12
        } else {
            // mov r15,rbx; sub r15,r14; jbe loc_e806a0f; sar r15,1
            std::uintptr_t t = (std::uintptr_t)base - 0xF848D0Eui64;             // 0xe806a02 mov r15,rbx ; 0xe806a05 sub r15,r14
            r15 = ((std::uintptr_t)base <= 0xF848D0Eui64) ? 0ui64 : (t >> 1);    // 0xe806a08 jbe loc_e806a0f ; 0xe806a0a sar r15,1
        }
        // cmp rcx,8; cmovae rdi,rdx; add rdi,0xA  -> p = base + 0xA
        char* p = base + 0xA;                                                    // 0xe806a1a add rdi,0xA
        // lea r8,[rax*2+2] (rax = size)
        // 0xe806a2c call 0xEEC6DE0 -> sub_eec6de0(base + 0xA, base, size*2+2)
        native::d3d12::sub_eec6de0(p, base, static_cast<std::uint64_t>(size * 2 + 2)); // 0xe806a2c call 0xEEC6DE0
        // lea rdi,[r15+r15]; mov rcx,rbx; mov rdx,r14; mov r8,rdi
        // 0xe806a3e call 0xEEC6EC0 -> sub_eec6ec0(base, 0xF848D0E, r15*2)
        native::d3d12::sub_eec6ec0(base, reinterpret_cast<const void*>(0xF848D0Eui64), r15 * 2); // 0xe806a3e call 0xEEC6EC0
        // lea rdx,[r14+r15*2]; add rdx,0xA; lea rcx,[rbx+r15*2]; mov r8d,0xA; sub r8,rdi
        // 0xe806a58 call 0xEEC6EC0 -> sub_eec6ec0(base + r15*2, 0xF848D0E + r15*2 + 0xA, 0xA - r15*2)
        native::d3d12::sub_eec6ec0(base + r15 * 2,
                                   reinterpret_cast<const void*>(0xF848D0Eui64 + r15 * 2 + 0xAui64),
                                   0xAui64 - r15 * 2);                           // 0xe806a58 call 0xEEC6EC0
    }

    // 0xe806a5d..0xe806a7b
    // movups xmm0,[rbp-0x20] (tmp.data); movups xmm1,[rbp-0x10] (tmp.size,tmp.cap);
    // movups [rsi+0x10],xmm1 (out->size,out->cap FIRST); movups [rsi],xmm0 (out->data);
    // mov rax,rsi; ret
    native::d3d12::Str32* o = static_cast<native::d3d12::Str32*>(out);
    o->size = tmp.size;                                                          // 0xe806a65 movups [rsi+0x10],xmm1 (size,cap)
    o->cap = tmp.cap;
    std::memcpy(o->data, tmp.data, 16);                                          // 0xe806a69 movups [rsi],xmm0 (data)
    return out;                                                                  // 0xe806a6c mov rax,rsi ; 0xe806a7b ret
}
