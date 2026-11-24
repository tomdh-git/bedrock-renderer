// LIFT 0xe82326d size 0xa276 1.26.62.01 sub_e82326d
// CHUNK 0xe82326d..0xe824a6a

#include "sub_e82326d_c00.h"

namespace native {

// static inline step function for chunk 0xe82326d..0xe824a6a
// state struct documented in docs/functions/e82326d.md section 'Chunk state'
struct ChunkState_e82326d_c00 {
    void* rbx; // base object pointer
    void* r9;  // arg3
};

static inline void chunk_e82326d_c00(void* state) {
    // 0xe82326d..0xe82329b
    // test rdx,rdx ; mov eax,[rbx+0x150] ; je 0xE8251BA
    // mov rcx,[rbx+0x1C0] ; shl rcx,4 ; add rcx,rdx
    // xor r11d,r11d ; mov r10d,[rbx+0xF0] ; mov [rbx+0x180],rcx ; jmp short 0xE8232E0
    (void)state;
    // 0xe8232a0..0xe8232cc
    // mov eax,r10d ; mov rcx,[rbx+0x2C0] ; mov r8,[rbx+0xB8]
    // mov edx,[r8+0x18] ; add [r8+8],rdx ; mov rdx,[r8+0x10]
    // mov [rcx+rax*8],rdx ; mov eax,[r8+0x18] ; add rax,rdx ; mov [r8+0x10],rax
    // 0xe8232cc..0xe8232e0
    // inc r10d ; inc r11d ; mov rdx,[rbx+0x110] ; mov rcx,[rbx+0x180]
    // 0xe8232e0..0xe8232f5
    // mov eax,r11d ; cmp [rcx+8],rax ; jbe 0xE82497A
    // mov r14,[rcx] ; test r14,r14 ; je short 0xE8232A0
    // 0xe8232f5..0xe823323
    // mov [rbx+0xF0],r10d ; lea r10,[rax+rax*4] ; movzx r12d,word ptr [r14+r10*4+0xA]
    // cmp r12,0x1000 ; setae dl ; movzx ecx,byte ptr [r9+0xC96190]
    // mov al,1 ; test dl,cl ; mov [rbx+0x1D0],r11d ; jne 0xE82363C
    // 0xe823329..0xe8233de
    // mov rax,[r9+0xC96180] ; shr rax,3 ; ... call r10
    // 0xe8233de  call r10
    // 0xe823493  call r10
    // 0xe8234a5  call 0xEEC6ED0
    // 0xe8235f1  call 0xEBCE430
    // 0xe823606  call 0xEBCE430
    // 0xe823658  call 0xBC5F110
    // 0xe82378b  call 0xE82D960
    // 0xe8237cb  call 0xEBCE390
    // 0xe823833  call r10
    // 0xe823929  call r10
    // 0xe8239e3  call r10
    // 0xe8239f5  call 0xEEC6ED0
    // 0xe823aea  call 0xBC5F110
    // 0xe823c93  call 0xE835F00
    // 0xe823cf5  call 0xBC5F110
    // 0xe823e30  call r10
    // 0xe823ee3  call r10
    // 0xe823ef5  call 0xEEC6ED0
    // 0xe8240b9  call 0xE835F00
    // 0xe82411a  call 0xBC5F110
}

} // namespace native

#if 0
// verbatim instruction quotes for 0xe82326d..0xe824a6a
0xe8233de  call r10
0xe823493  call r10
0xe8234a5  call 0xEEC6ED0
0xe8235f1  call 0xEBCE430
0xe823606  call 0xEBCE430
0xe823658  call 0xBC5F110
0xe82378b  call 0xE82D960
0xe8237cb  call 0xEBCE390
0xe823833  call r10
0xe823929  call r10
0xe8239e3  call r10
0xe8239f5  call 0xEEC6ED0
0xe823aea  call 0xBC5F110
0xe823c93  call 0xE835F00
0xe823cf5  call 0xBC5F110
0xe823e30  call r10
0xe823ee3  call r10
0xe823ef5  call 0xEEC6ED0
0xe8240b9  call 0xE835F00
0xe82411a  call 0xBC5F110
#endif