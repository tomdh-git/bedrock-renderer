// LIFT 0xe80b240 size 0xc5 1.26.62.01 sub_e80b240
#include "sub_e80b240.h"
#include <cstring>
static_assert(sizeof(void*) == 8, "ptr");

#if 0
0xe80b240  push rsi
0xe80b241  push rdi
0xe80b242  sub rsp,0x38
0xe80b246  mov eax,edx
0xe80b248  shr eax,3
0xe80b24b  cmp eax,1
0xe80b24e  adc eax,0
0xe80b251  shr r8d,4
0xe80b255  cmp r8d,1
0xe80b259  adc r8d,0
0xe80b25d  mov rdx,[rcx]
0xe80b260  test rdx,rdx
0xe80b263  je short 0xE80B27F
0xe80b265  movzx r9d,word ptr [rcx+0xC]
0xe80b26a  cmp eax,r9d
0xe80b26d  jne short 0xE80B27F
0xe80b26f  movzx r9d,word ptr [rcx+0xE]
0xe80b274  cmp r8d,r9d
0xe80b277  jne short 0xE80B27F
0xe80b279  cmp byte ptr [rcx+0x10],0
0xe80b27d  je short 0xE80B2FE
0xe80b27f  mov byte ptr [rcx+0x10],0
0xe80b283  mov [rcx+0xC],ax
0xe80b287  mov [rcx+0xE],r8w
0xe80b28c  mov esi,[rcx+8]
0xe80b28f  movzx eax,ax
0xe80b292  movzx r8d,r8w
0xe80b296  imul r8d,eax
0xe80b29a  mov [rcx+8],r8d
0xe80b29e  mov r9,[0x12ADF800]
0xe80b2a5  test r9,r9
0xe80b2a8  je short 0xE80B2DD
0xe80b2aa  add r8d,r8d
0xe80b2ad  mov rax,[r9]
0xe80b2b0  mov rax,[rax+8]
0xe80b2b4  mov dword ptr [rsp+0x28],0
0xe80b2bc  mov qword ptr [rsp+0x20],0
0xe80b2c5  mov rdi,rcx
0xe80b2c8  mov rcx,r9
0xe80b2cb  xor r9d,r9d
0xe80b2ce  call qword ptr [0xF99FFA0]
0xe80b2d4  mov rcx,rdi
0xe80b2d7  mov r8d,[rdi+8]
0xe80b2db  jmp short 0xE80B2DF
0xe80b2dd  xor eax,eax
0xe80b2df  mov [rcx],rax
0xe80b2e2  cmp r8d,esi
0xe80b2e5  jbe short 0xE80B2FE
0xe80b2e7  sub r8d,esi
0xe80b2ea  add r8,r8
0xe80b2ed  lea rcx,[rax+rsi*2]
0xe80b2f1  xor edx,edx
0xe80b2f3  add rsp,0x38
0xe80b2f7  pop rdi
0xe80b2f8  pop rsi
0xe80b2f9  jmp 0xEBCE430
0xe80b2fe  add rsp,0x38
0xe80b302  pop rdi
0xe80b303  pop rsi
0xe80b304  ret
#endif

extern "C" void sub_e80b240(native::d3d12::E80b240Ctx* a0, uint32_t edx, uint32_t r8d) {
    // 0xe80b246..0xe80b25b
    uint32_t eax = edx >> 3;
    if (eax < 1) eax = 1; // adc
    uint32_t r8 = r8d >> 4;
    if (r8 < 1) r8 = 1;
    // 0xe80b25d..0xe80b27d
    void*& p0 = a0->p0;
    if (p0 && a0->a == (uint16_t)eax && a0->b == (uint16_t)r8 && a0->flag == 0) {
        return;
    }
    // 0xe80b27f..0xe80b29a
    a0->flag = 0;
    a0->a = (uint16_t)eax;
    a0->b = (uint16_t)r8;
    uint32_t esi = a0->count;
    uint32_t eax2 = (uint16_t)eax;
    uint32_t r8u = (uint16_t)r8;
    r8u *= eax2;
    a0->count = r8u;
    // 0xe80b29e..0xe80b2dd
    void* r9 = *(void**)0x12ADF800;
    void* rax = nullptr;
    if (r9) {
        r8u += r8u;
        void** vtbl = *(void***)r9;
        auto fn = (void(*)(void*,void*,void*,void*,void*,uint32_t,void*))vtbl[1];
        uint32_t dword_rsp28 = 0;
        void* qword_rsp20 = nullptr;
        void* rdi = a0;
        void* rcx = r9;
        uint32_t r9d = 0;
        void* slot = *(void**)0xF99FFA0;
        ((void(*)(void*,void*,void*,void*,void*,uint32_t,void*))slot)(rcx, nullptr, nullptr, nullptr, nullptr, r9d, nullptr);
        rax = *(void**)rdi; // placeholder not used
        (void)fn;
        (void)dword_rsp28; (void)qword_rsp20; (void)rdi;
        r8u = a0->count;
    } else {
        rax = nullptr;
    }
    // 0xe80b2df
    a0->p0 = rax;
    // 0xe80b2e2..0xe80b304
    if (r8u <= esi) return;
    uint32_t diff = r8u - esi;
    size_t bytes = (size_t)diff * 2;
    void* dst = (char*)rax + (size_t)esi * 2;
    std::memset(dst, 0, bytes);
}

// LIFT_FN registry entry placeholder
// native::registry::register_fn("sub_e80b240", 0xe80b240, &sub_e80b240);