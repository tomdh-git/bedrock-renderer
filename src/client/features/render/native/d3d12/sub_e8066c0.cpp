// LIFT 0xe8066c0 size 0x11c 1.26.62.01 sub_e8066c0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e8066c0.h"
#include "client/features/render/native/d3d12/sub_e834520.h"

#include <cstdint>
#include <cstddef>
#include <cstring>

static_assert(sizeof(void*) == 8, "e8066c0 x64");

// verbatim call quotes (plain lines for verify_oc)
#if 0
0xe8066e6  call 0xE834520
0xe806715  call 0xE834330
0xe80678c  call 0xEEC6DE0
0xe80679e  call 0xEEC6EC0
0xe8067b8  call 0xEEC6EC0
#endif

namespace native::d3d12 {

native::Footprint sub_e8066c0_footprint(void* out, const void*) {
    return native::Footprint{{out, 0x20}};
}

LIFT_FN(sub_e8066c0, "sub_e8066c0", 0xe8066c0, sub_e8066c0, sub_e8066c0_footprint);

} // namespace native::d3d12

extern "C" void* sub_e8066c0(void* out, const void* src) {
    // 0xe8066c0..0xe8066e6
    // push rbp/r15/r14/rsi/rdi/rbx; sub rsp,0x48; lea rbp,[rsp+0x40]; mov [rbp],-2;
    // mov rsi,rcx; movzx edx,word ptr [rdx] (src+0x0); lea rdi,[rbp-0x20]; mov rcx,rdi
    Str32 tmp;                                                    // scratch string at rbp-0x20
    std::uint32_t v = *reinterpret_cast<const std::uint16_t*>(src); // 0xe8066dc movzx edx,word ptr [rdx]
    // 0xe8066e6 call 0xE834520 -> native::d3d12::sub_e834520(&tmp, v)
    native::d3d12::sub_e834520(&tmp, v);                          // writes tmp.data[16], tmp.size, tmp.cap

    // 0xe8066eb..0xe80671c
    // mov rax,[rbp-0x10] (tmp.size); mov rcx,[rbp-8] (tmp.cap);
    // mov rdx,rcx; sub rdx,rax; cmp rdx,9; jae loc_e806720
    std::size_t size = tmp.size;                                  // 0xe8066eb mov rax,[rbp-0x10]
    std::size_t cap = tmp.cap;                                    // 0xe8066ef mov rcx,[rbp-8]
    if (cap - size < 9u) {                                        // 0xe8066f9 cmp rdx,9 ; 0xe8066fd jae loc_e806720
        // 0xe8066ff lea r8,[0xF848D1A] ("LTexture: ");
        // 0xe806706 lea rcx,[rbp-0x20]; 0xe80670a mov edx,9; 0xe80670f mov r9d,9
        // 0xe806715 call 0xE834330 -> sub_e834330(&tmp, 9, (void*)0xF848D1A, (void*)9)
        sub_e834330(&tmp, 9, reinterpret_cast<void*>(0xF848D1Aui64), reinterpret_cast<void*>(9));
        // 0xe80671a nop ; 0xe80671b jmp loc_e8067bd -> falls into the store below
    } else {
        // 0xe806720..0xe8067bd
        // lea rdx,[rax+9]; mov [rbp-0x10],rdx  (tmp.size = size + 9)
        tmp.size = size + 9;                                      // 0xe806720 lea rdx,[rax+9] ; 0xe806724 mov [rbp-0x10],rdx
        std::uintptr_t r15;
        // lea r8,[0xF848D2C]; cmp rbx,r8; setae r8b   (rbx = tmp.data)
        // lea r14,[0xF848D1A] ("LTexture: ");
        // lea r9,[rbx+rax*2]; cmp r9,r14; setb r9b
        // or r9b,r8b; mov r15d,9; jne loc_e806772
        if (((std::uintptr_t)tmp.data >= 0xF848D2Cui64) ||        // 0xe806741 setae r8b
            ((std::uintptr_t)(tmp.data + size * 2) < 0xF848D1Aui64)) { // 0xe806753 setb r9b
            r15 = 9;                                              // 0xe80675a mov r15d,9
        } else {
            // mov r15,rbx; sub r15,r14; jbe loc_e80676f; sar r15,1
            std::uintptr_t t = (std::uintptr_t)tmp.data - 0xF848D1Aui64; // 0xe806762/0xe806765
            r15 = ((std::uintptr_t)tmp.data <= 0xF848D1Aui64) ? 0ui64 : (t >> 1); // 0xe806768 jbe ; 0xe80676a sar
        }
        // 0xe806772..0xe8067bb
        // cmp rcx,8; cmovae rdi,rdx (both = tmp.data); add rdi,0x12
        char* p = tmp.data + 0x12;                                // 0xe806776 cmovae rdi,rdx ; 0xe80677a add rdi,0x12
        // lea r8,[rax*2+2] (rax = size)
        // 0xe80678c call 0xEEC6DE0 -> sub_eec6de0(tmp.data + 0x12, tmp.data, size*2+2)
        sub_eec6de0(p, tmp.data, static_cast<std::uint64_t>(size * 2 + 2));
        // lea rdi,[r15+r15]; mov rcx,rbx; mov rdx,r14; mov r8,rdi
        // 0xe80679e call 0xEEC6EC0 -> sub_eec6ec0(tmp.data, (const char*)0xF848D1A, r15*2)
        native::d3d12::sub_eec6ec0(tmp.data, reinterpret_cast<const void*>(0xF848D1Aui64), r15 * 2);
        // lea rdx,[r14+r15*2]; add rdx,0x12;
        // lea rcx,[rbx+r15*2]; mov r8d,0x12; sub r8,rdi
        // 0xe8067b8 call 0xEEC6EC0 -> sub_eec6ec0(tmp.data + r15*2, (const char*)0xF848D1A + r15*2 + 0x12, 0x12 - r15*2)
        native::d3d12::sub_eec6ec0(tmp.data + r15 * 2,
                                   reinterpret_cast<const void*>(0xF848D1Aui64 + r15 * 2 + 0x12ui64),
                                   0x12ui64 - r15 * 2);
    }

    // 0xe8067bd..0xe8067dc
    // movups xmm0,[rbp-0x20] (tmp.data); movups xmm1,[rbp-0x10] (tmp.size,tmp.cap);
    // movups [rsi+0x10],xmm1; movups [rsi],xmm0; mov rax,rsi; ret
    Str32* o = static_cast<Str32*>(out);
    o->size = tmp.size;                                           // 0xe8067c5 movups [rsi+0x10],xmm1 (size,cap)
    o->cap = tmp.cap;
    std::memcpy(o->data, tmp.data, 16);                           // 0xe8067c9 movups [rsi],xmm0 (data)
    return out;                                                   // 0xe8067cc mov rax,rsi ; 0xe8067db ret
}
