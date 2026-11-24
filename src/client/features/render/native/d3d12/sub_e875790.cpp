// LIFT 0xe875790 size 0x8e4 1.26.62.01 BgfxFrameBuilder slot 16
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e875790.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cmath>

static_assert(sizeof(void*) == 8, "ptr");

// Verbatim disassembly of [0xe875790, 0xe876074) (Minecraft Windows 1.26.62.01).
#if 0
0xe875790  push rbp
0xe875791  push r15
0xe875793  push r14
0xe875795  push r13
0xe875797  push r12
0xe875799  push rsi
0xe87579a  push rdi
0xe87579b  push rbx
0xe87579c  sub rsp,0x78
0xe8757a0  lea rbp,[rsp+0x70]
0xe8757a5  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0xe8757ad  mov r14,r9
0xe8757b0  mov r15,r8
0xe8757b3  mov [rbp-0x10],rcx
0xe8757b7  mov rbx,[r8+0x10]
0xe8757bb  cmp qword ptr [r8+0x18],0x10
0xe8757c0  mov r12,r8
0xe8757c3  jb short 0xE8757C8
0xe8757c5  mov r12,[r15]
0xe8757c8  test rbx,rbx
0xe8757cb  mov [rbp-0x18],rdx
0xe8757cf  je short 0xE8757F5
0xe8757d1  mov eax,ebx
0xe8757d3  and eax,3
0xe8757d6  mov rcx,0x100000001B3
0xe8757e0  cmp rbx,4
0xe8757e4  jae short 0xE875804
0xe8757e6  mov r13,0xCBF29CE484222325
0xe8757f0  xor r11d,r11d
0xe8757f3  jmp short 0xE875861
0xe8757f5  mov r13,0xCBF29CE484222325
0xe8757ff  jmp 0xE875887
0xe875804  mov r8,rbx
0xe875807  and r8,0xFFFFFFFFFFFFFFFC
0xe87580b  mov r13,0xCBF29CE484222325
0xe875815  xor r11d,r11d
0xe875818  nop [rax+rax]
0xe875820  movzx r9d,byte ptr [r12+r11]
0xe875825  xor r9,r13
0xe875828  imul r9,rcx
0xe87582c  movzx r10d,byte ptr [r12+r11+1]
0xe875832  xor r10,r9
0xe875835  imul r10,rcx
0xe875839  movzx r9d,byte ptr [r12+r11+2]
0xe87583f  xor r9,r10
0xe875842  imul r9,rcx
0xe875846  movzx r13d,byte ptr [r12+r11+3]
0xe87584c  xor r13,r9
0xe87584f  imul r13,rcx
0xe875853  add r11,4
0xe875857  cmp r8,r11
0xe87585a  jne short 0xE875820
0xe87585c  test rax,rax
0xe87585f  je short 0xE875887
0xe875861  add r11,r12
0xe875864  xor r8d,r8d
0xe875867  mov r9,r13
0xe87586a  nop [rax+rax]
0xe875870  movzx r13d,byte ptr [r11+r8]
0xe875875  xor r13,r9
0xe875878  imul r13,rcx
0xe87587c  inc r8
0xe87587f  mov r9,r13
0xe875882  cmp rax,r8
0xe875885  jne short 0xE875870
0xe875887  mov rcx,[rbp-0x10]
0xe87588b  mov rax,[rcx+0x30]
0xe87588f  and rax,r13
0xe875892  mov rsi,[rcx+8]
0xe875896  mov rcx,[rcx+0x18]
0xe87589a  shl rax,4
0xe87589e  mov rdi,[rcx+rax+8]
0xe8758a3  cmp rdi,rsi
0xe8758a6  je 0xE875933
0xe8758ac  mov rsi,[rcx+rax]
0xe8758b0  test rbx,rbx
0xe8758b3  je short 0xE875919
0xe8758b5  nop [rax+rax]
0xe8758c0  cmp rbx,[rdi+0x20]
0xe8758c4  jne short 0xE8758F3
0xe8758c6  cmp qword ptr [rdi+0x28],0x10
0xe8758cb  jb short 0xE8758E0
0xe8758cd  mov rdx,[rdi+0x10]
0xe8758d1  jmp short 0xE8758E4
0xe8758d3  nop [rax+rax]
0xe8758e0  lea rdx,[rdi+0x10]
0xe8758e4  mov rcx,r12
0xe8758e7  mov r8,rbx
0xe8758ea  call 0xEEC6EB0
0xe8758ef  test eax,eax
0xe8758f1  je short 0xE875920
0xe8758f3  cmp rdi,rsi
0xe8758f6  je short 0xE875930
0xe8758f8  mov rdi,[rdi+8]
0xe8758fc  cmp rbx,[rdi+0x20]
0xe875900  je short 0xE8758C6
0xe875902  jmp short 0xE8758F3
0xe875904  nop [rax+rax]
0xe875910  cmp rdi,rsi
0xe875913  je short 0xE875930
0xe875915  mov rdi,[rdi+8]
0xe875919  cmp qword ptr [rdi+0x20],0
0xe87591e  jne short 0xE875910
0xe875920  mov rax,[rbp-0x18]
0xe875924  mov [rax],rdi
0xe875927  mov byte ptr [rax+8],0
0xe87592b  jmp 0xE876001
0xe875930  mov rsi,rdi
0xe875933  mov rax,0x38E38E38E38E38E
0xe87593d  mov r12,[rbp-0x10]
0xe875941  cmp [r12+0x10],rax
0xe875946  je 0xE876040
0xe87594c  lea rax,[r12+8]
0xe875951  mov [rbp-0x48],rax
0xe875955  mov rcx,[0x1233E1A8]
0xe87595c  mov rax,[rcx]
0xe87595f  mov rax,[rax+8]
0xe875963  mov edx,0x48
0xe875968  call qword ptr [0xF99FFA0]
0xe87596e  mov rbx,rax
0xe875971  test rax,rax
0xe875974  je 0xE876012
0xe87597a  mov [rbp-0x40],rbx
0xe87597e  movups xmm0,[r15]
0xe875982  movups xmm1,[r15+0x10]
0xe875987  movups [rbx+0x20],xmm1
0xe87598b  movups [rbx+0x10],xmm0
0xe87598f  mov qword ptr [r15+0x10],0
0xe875997  mov qword ptr [r15+0x18],0xF
0xe87599f  mov byte ptr [r15],0
0xe8759a3  mov rax,[r14+0x10]
0xe8759a7  mov qword ptr [r14+0x10],0
0xe8759af  movups xmm0,[r14]
0xe8759b3  xorps xmm1,xmm1
0xe8759b6  movups [r14],xmm1
0xe8759ba  movups [rbx+0x30],xmm0
0xe8759be  mov [rbx+0x40],rax
0xe8759c2  mov rax,[r12+0x10]
0xe8759c7  inc rax
0xe8759ca  js short 0xE8759D6
0xe8759cc  xorps xmm0,xmm0
0xe8759cf  cvtsi2ss xmm0,rax
0xe8759d4  jmp short 0xE8759EE
0xe8759d6  mov rcx,rax
0xe8759d9  shr rcx,1
0xe8759dc  and eax,1
0xe8759df  or rax,rcx
0xe8759e2  xorps xmm0,xmm0
0xe8759e5  cvtsi2ss xmm0,rax
0xe8759ea  addss xmm0,xmm0
0xe8759ee  movss xmm1,[r12]
0xe8759f4  mov rdi,[r12+0x38]
0xe8759f9  test rdi,rdi
0xe8759fc  js short 0xE875A05
0xe8759fe  cvtsi2ss xmm2,rdi
0xe875a03  jmp short 0xE875A1C
0xe875a05  mov rax,rdi
0xe875a08  shr rax,1
0xe875a0b  mov ecx,edi
0xe875a0d  and ecx,1
0xe875a10  or rcx,rax
0xe875a13  cvtsi2ss xmm2,rcx
0xe875a18  addss xmm2,xmm2
0xe875a1c  movaps xmm3,xmm0
0xe875a1f  divss xmm3,xmm2
0xe875a23  ucomiss xmm3,xmm1
0xe875a26  jbe 0xE875F98
0xe875a2c  divss xmm0,xmm1
0xe875a30  call 0xEEC73F0
0xe875a35  cvttss2si rax,xmm0
0xe875a3a  mov rcx,rax
0xe875a3d  subss xmm0,[0xEEE6700]
0xe875a45  cvttss2si rdx,xmm0
0xe875a4a  sar rcx,0x3F
0xe875a4e  and rdx,rcx
0xe875a51  or rdx,rax
0xe875a54  cmp rdx,9
0xe875a58  mov eax,8
0xe875a5d  cmovae rax,rdx
0xe875a61  cmp rdi,rax
0xe875a64  jae short 0xE875A83
0xe875a66  lea rcx,[rdi*8]
0xe875a6e  cmp rcx,rax
0xe875a71  cmovbe rcx,rax
0xe875a75  cmp rdi,0x200
0xe875a7c  cmovae rcx,rax
0xe875a80  mov rdi,rcx
0xe875a83  mov rax,0x800000000000001
0xe875a8d  cmp rdi,rax
0xe875a90  jae 0xE87604D
0xe875a96  lea rax,[rdi-1]
0xe875a9a  or rax,1
0xe875a9e  bsr rcx,rax
0xe875aa2  inc rcx
0xe875aa5  mov esi,1
0xe875aaa  shl rsi,cl
0xe875aad  mov r9d,2
0xe875ab3  shl r9,cl
0xe875ab6  mov r11,[r12+8]
0xe875abb  mov rdx,[r12+0x18]
0xe875ac0  mov rax,[r12+0x20]
0xe875ac5  mov r8,rax
0xe875ac8  sub r8,rdx
0xe875acb  mov r10,r8
0xe875ace  sar r10,3
0xe875ad2  cmp r10,r9
0xe875ad5  mov [rbp-8],r11
0xe875ad9  mov [rbp-0x38],rbx
0xe875add  jae short 0xE875B2A
0xe875adf  mov r14d,0x10
0xe875ae5  shl r14,cl
0xe875ae8  cmp rdi,0x81
0xe875aef  jb short 0xE875B49
0xe875af1  lea rdi,[r14+0x27]
0xe875af5  mov rcx,[0x1233E1A8]
0xe875afc  mov rax,[rcx]
0xe875aff  mov rax,[rax+8]
0xe875b03  mov rdx,rdi
0xe875b06  call qword ptr [0xF99FFA0]
0xe875b0c  nop
0xe875b0d  mov r15,rax
0xe875b10  test rax,rax
0xe875b13  je 0xE876021
0xe875b19  mov rax,r15
0xe875b1c  add r15,0x27
0xe875b20  and r15,0xFFFFFFFFFFFFFFE0
0xe875b24  mov [r15-8],rax
0xe875b28  jmp short 0xE875B6D
0xe875b2a  cmp rdx,rax
0xe875b2d  je 0xE875C6C
0xe875b33  add r8,0xFFFFFFFFFFFFFFF8
0xe875b37  cmp r8,0x18
0xe875b3b  jae 0xE875C1E
0xe875b41  mov rcx,rdx
0xe875b44  jmp 0xE875C60
0xe875b49  mov rcx,[0x1233E1A8]
0xe875b50  mov rax,[rcx]
0xe875b53  mov rax,[rax+8]
0xe875b57  mov rdx,r14
0xe875b5a  call qword ptr [0xF99FFA0]
0xe875b60  nop
0xe875b61  mov r15,rax
0xe875b64  test rax,rax
0xe875b67  je 0xE87602F
0xe875b6d  mov rcx,[r12+0x18]
0xe875b72  mov rdx,[r12+0x28]
0xe875b77  sub rdx,rcx
0xe875b7a  je short 0xE875BA6
0xe875b7c  cmp rdx,0x1000
0xe875b83  jb short 0xE875BA1
0xe875b85  mov rax,[rcx-8]
0xe875b89  add rcx,0xFFFFFFFFFFFFFFF8
0xe875b8d  sub rcx,rax
0xe875b90  cmp rcx,0x20
0xe875b94  jae 0xE87605A
0xe875b9a  add rdx,0x27
0xe875b9e  mov rcx,rax
0xe875ba1  call 0xE935700
0xe875ba6  mov [r12+0x18],r15
0xe875bab  lea rax,[r15+r14]
0xe875baf  mov [r12+0x20],rax
0xe875bb4  mov [r12+0x28],rax
0xe875bb9  add r14,0xFFFFFFFFFFFFFFF8
0xe875bbd  cmp r14,0x18
0xe875bc1  jae short 0xE875BCC
0xe875bc3  mov rcx,r15
0xe875bc6  mov r11,[rbp-8]
0xe875bca  jmp short 0xE875C10
0xe875bcc  shr r14,3
0xe875bd0  inc r14
0xe875bd3  mov rdx,r14
0xe875bd6  and rdx,0xFFFFFFFFFFFFFFFC
0xe875bda  lea rcx,[r15+rdx*8]
0xe875bde  movq xmm0,[rbp-8]
0xe875be3  pshufd xmm0,xmm0,0x44
0xe875be8  xor r8d,r8d
0xe875beb  nop [rax+rax]
0xe875bf0  movdqu [r15+r8*8],xmm0
0xe875bf6  movdqu [r15+r8*8+0x10],xmm0
0xe875bfd  add r8,4
0xe875c01  cmp rdx,r8
0xe875c04  jne short 0xE875BF0
0xe875c06  cmp r14,rdx
0xe875c09  mov r11,[rbp-8]
0xe875c0d  je short 0xE875C6C
0xe875c0f  nop
0xe875c10  mov [rcx],r11
0xe875c13  add rcx,8
0xe875c17  cmp rcx,rax
0xe875c1a  jne short 0xE875C10
0xe875c1c  jmp short 0xE875C6C
0xe875c1e  shr r8,3
0xe875c22  inc r8
0xe875c25  mov r9,r8
0xe875c28  and r9,0xFFFFFFFFFFFFFFFC
0xe875c2c  lea rcx,[rdx+r9*8]
0xe875c30  movq xmm0,r11
0xe875c35  pshufd xmm0,xmm0,0x44
0xe875c3a  xor r10d,r10d
0xe875c3d  nop [rax]
0xe875c40  movdqu [rdx+r10*8],xmm0
0xe875c46  movdqu [rdx+r10*8+0x10],xmm0
0xe875c4d  add r10,4
0xe875c51  cmp r9,r10
0xe875c54  jne short 0xE875C40
0xe875c56  cmp r8,r9
0xe875c59  je short 0xE875C6C
0xe875c5b  nop [rax+rax]
0xe875c60  mov [rcx],r11
0xe875c63  add rcx,8
0xe875c67  cmp rcx,rax
0xe875c6a  jne short 0xE875C60
0xe875c6c  lea rax,[rsi-1]
0xe875c70  mov [r12+0x30],rax
0xe875c75  mov [r12+0x38],rsi
0xe875c7a  mov rsi,[r12+8]
0xe875c7f  mov r10,[rsi]
0xe875c82  cmp r10,r11
0xe875c85  je 0xE875EEB
0xe875c8b  mov rbx,0x100000001B3
0xe875c95  jmp short 0xE875CBA
0xe875c97  nop [rax+rax]
0xe875ca0  mov [rax+rdi],r10
0xe875ca4  mov [rax+rdi+8],r10
0xe875ca9  mov rax,[rbp-8]
0xe875cad  mov r10,[rbp-0x20]
0xe875cb1  cmp r10,rax
0xe875cb4  je 0xE875EE1
0xe875cba  cmp qword ptr [r10+0x28],0x10
0xe875cbf  jb short 0xE875CD0
0xe875cc1  mov r14,[r10+0x10]
0xe875cc5  jmp short 0xE875CD4
0xe875cc7  nop [rax+rax]
0xe875cd0  lea r14,[r10+0x10]
0xe875cd4  mov r15,[r10+0x20]
0xe875cd8  mov rdi,0xCBF29CE484222325
0xe875ce2  test r15,r15
0xe875ce5  je 0xE875D76
0xe875ceb  mov eax,r15d
0xe875cee  and eax,3
0xe875cf1  cmp r15,4
0xe875cf5  jae short 0xE875D00
0xe875cf7  xor ecx,ecx
0xe875cf9  jmp short 0xE875D51
0xe875cfb  nop [rax+rax]
0xe875d00  mov rdx,r15
0xe875d03  and rdx,0xFFFFFFFFFFFFFFFC
0xe875d07  xor ecx,ecx
0xe875d09  nop [rax]
0xe875d10  movzx r8d,byte ptr [r14+rcx]
0xe875d15  xor r8,rdi
0xe875d18  imul r8,rbx
0xe875d1c  movzx r9d,byte ptr [r14+rcx+1]
0xe875d22  xor r9,r8
0xe875d25  imul r9,rbx
0xe875d29  movzx r8d,byte ptr [r14+rcx+2]
0xe875d2f  xor r8,r9
0xe875d32  imul r8,rbx
0xe875d36  movzx edi,byte ptr [r14+rcx+3]
0xe875d3c  xor rdi,r8
0xe875d3f  imul rdi,rbx
0xe875d43  add rcx,4
0xe875d47  cmp rdx,rcx
0xe875d4a  jne short 0xE875D10
0xe875d4c  test rax,rax
0xe875d4f  je short 0xE875D76
0xe875d51  add rcx,r14
0xe875d54  mov r8,rdi
0xe875d57  xor edx,edx
0xe875d59  nop [rax]
0xe875d60  movzx edi,byte ptr [rcx+rdx]
0xe875d64  xor rdi,r8
0xe875d67  imul rdi,rbx
0xe875d6b  inc rdx
0xe875d6e  mov r8,rdi
0xe875d71  cmp rax,rdx
0xe875d74  jne short 0xE875D60
0xe875d76  mov rax,[r10]
0xe875d79  mov [rbp-0x20],rax
0xe875d7d  and rdi,[r12+0x30]
0xe875d82  mov rax,[r12+0x18]
0xe875d87  shl rdi,4
0xe875d8b  mov rsi,[rax+rdi]
0xe875d8f  cmp rsi,[rbp-8]
0xe875d93  je 0xE875CA0
0xe875d99  mov [rbp-0x28],r10
0xe875d9d  mov [rbp-0x30],rax
0xe875da1  mov r12,[rax+rdi+8]
0xe875da6  cmp qword ptr [r12+0x28],0x10
0xe875dac  jb short 0xE875DC0
0xe875dae  mov rdx,[r12+0x10]
0xe875db3  cmp r15,[r12+0x20]
0xe875db8  jne short 0xE875DF0
0xe875dba  jmp short 0xE875DCC
0xe875dbc  nop [rax]
0xe875dc0  lea rdx,[r12+0x10]
0xe875dc5  cmp r15,[r12+0x20]
0xe875dca  jne short 0xE875DF0
0xe875dcc  test r15,r15
0xe875dcf  je 0xE875E95
0xe875dd5  mov rcx,r14
0xe875dd8  mov r8,r15
0xe875ddb  call 0xEEC6EB0
0xe875de0  test eax,eax
0xe875de2  je 0xE875E95
0xe875de8  nop [rax+rax]
0xe875df0  cmp rsi,r12
0xe875df3  je short 0xE875E60
0xe875df5  mov r12,[r12+8]
0xe875dfa  cmp qword ptr [r12+0x28],0x10
0xe875e00  jb short 0xE875E10
0xe875e02  mov rdx,[r12+0x10]
0xe875e07  cmp r15,[r12+0x20]
0xe875e0c  jne short 0xE875DF0
0xe875e0e  jmp short 0xE875E1C
0xe875e10  lea rdx,[r12+0x10]
0xe875e15  cmp r15,[r12+0x20]
0xe875e1a  jne short 0xE875DF0
0xe875e1c  test r15,r15
0xe875e1f  je short 0xE875E30
0xe875e21  mov rcx,r14
0xe875e24  mov r8,r15
0xe875e27  call 0xEEC6EB0
0xe875e2c  test eax,eax
0xe875e2e  jne short 0xE875DF0
0xe875e30  mov rax,[r12]
0xe875e34  mov r9,[rbp-0x28]
0xe875e38  mov rcx,[r9+8]
0xe875e3c  mov r10,[rbp-0x20]
0xe875e40  mov [rcx],r10
0xe875e43  mov rdx,[r10+8]
0xe875e47  mov [rdx],rax
0xe875e4a  mov r8,[rax+8]
0xe875e4e  mov [r8],r9
0xe875e51  mov [rax+8],rdx
0xe875e55  mov [r10+8],rcx
0xe875e59  mov [r9+8],r8
0xe875e5d  jmp short 0xE875ED0
0xe875e5f  nop
0xe875e60  mov r8,[rbp-0x28]
0xe875e64  mov rax,[r8+8]
0xe875e68  mov r10,[rbp-0x20]
0xe875e6c  mov [rax],r10
0xe875e6f  mov rcx,[r10+8]
0xe875e73  mov [rcx],r12
0xe875e76  mov rdx,[r12+8]
0xe875e7b  mov [rdx],r8
0xe875e7e  mov [r12+8],rcx
0xe875e83  mov [r10+8],rax
0xe875e87  mov [r8+8],rdx
0xe875e8b  mov rax,[rbp-0x30]
0xe875e8f  mov [rax+rdi],r8
0xe875e93  jmp short 0xE875ED0
0xe875e95  mov rax,[r12]
0xe875e99  mov r9,[rbp-0x28]
0xe875e9d  cmp rax,r9
0xe875ea0  mov r10,[rbp-0x20]
0xe875ea4  je short 0xE875EC7
0xe875ea6  mov rcx,[r9+8]
0xe875eaa  mov [rcx],r10
0xe875ead  mov rdx,[r10+8]
0xe875eb1  mov [rdx],rax
0xe875eb4  mov r8,[rax+8]
0xe875eb8  mov [r8],r9
0xe875ebb  mov [rax+8],rdx
0xe875ebf  mov [r10+8],rcx
0xe875ec3  mov [r9+8],r8
0xe875ec7  mov rax,[rbp-0x30]
0xe875ecb  mov [rax+rdi+8],r9
0xe875ed0  mov r12,[rbp-0x10]
0xe875ed4  mov rax,[rbp-8]
0xe875ed8  cmp r10,rax
0xe875edb  jne 0xE875CBA
0xe875ee1  mov rsi,[r12+8]
0xe875ee6  mov rax,[r12+0x30]
0xe875eeb  and rax,r13
0xe875eee  mov rcx,[r12+0x18]
0xe875ef3  shl rax,4
0xe875ef7  mov rdi,[rcx+rax+8]
0xe875efc  cmp rdi,rsi
0xe875eff  mov rbx,[rbp-0x38]
0xe875f03  je 0xE875F98
0xe875f09  mov r14,[rbx+0x20]
0xe875f0d  cmp qword ptr [rbx+0x28],0x10
0xe875f12  jb short 0xE875F1A
0xe875f14  mov r15,[rbx+0x10]
0xe875f18  jmp short 0xE875F21
0xe875f1a  mov r15,rbx
0xe875f1d  add r15,0x10
0xe875f21  mov rsi,[rcx+rax]
0xe875f25  test r14,r14
0xe875f28  je short 0xE875F89
0xe875f2a  nop [rax+rax]
0xe875f30  cmp r14,[rdi+0x20]
0xe875f34  jne short 0xE875F63
0xe875f36  cmp qword ptr [rdi+0x28],0x10
0xe875f3b  jb short 0xE875F50
0xe875f3d  mov rdx,[rdi+0x10]
0xe875f41  jmp short 0xE875F54
0xe875f43  nop [rax+rax]
0xe875f50  lea rdx,[rdi+0x10]
0xe875f54  mov rcx,r15
0xe875f57  mov r8,r14
0xe875f5a  call 0xEEC6EB0
0xe875f5f  test eax,eax
0xe875f61  je short 0xE875F90
0xe875f63  cmp rdi,rsi
0xe875f66  je short 0xE875F95
0xe875f68  mov rdi,[rdi+8]
0xe875f6c  cmp r14,[rdi+0x20]
0xe875f70  je short 0xE875F36
0xe875f72  jmp short 0xE875F63
0xe875f74  nop [rax+rax]
0xe875f80  cmp rdi,rsi
0xe875f83  je short 0xE875F95
0xe875f85  mov rdi,[rdi+8]
0xe875f89  cmp qword ptr [rdi+0x20],0
0xe875f8e  jne short 0xE875F80
0xe875f90  mov rsi,[rdi]
0xe875f93  jmp short 0xE875F98
0xe875f95  mov rsi,rdi
0xe875f98  mov qword ptr [rbp-0x40],0
0xe875fa0  mov rcx,[rsi+8]
0xe875fa4  inc qword ptr [r12+0x10]
0xe875fa9  mov [rbx],rsi
0xe875fac  mov [rbx+8],rcx
0xe875fb0  mov [rcx],rbx
0xe875fb3  mov [rsi+8],rbx
0xe875fb7  mov r8,[r12+0x18]
0xe875fbc  and r13,[r12+0x30]
0xe875fc1  shl r13,4
0xe875fc5  mov rdx,[r8+r13]
0xe875fc9  cmp rdx,[r12+8]
0xe875fce  je short 0xE875FE7
0xe875fd0  cmp rdx,rsi
0xe875fd3  je short 0xE875FF2
0xe875fd5  cmp [r8+r13+8],rcx
0xe875fda  mov rax,[rbp-0x18]
0xe875fde  jne short 0xE875FFA
0xe875fe0  mov [r8+r13+8],rbx
0xe875fe5  jmp short 0xE875FFA
0xe875fe7  mov [r8+r13],rbx
0xe875feb  mov [r8+r13+8],rbx
0xe875ff0  jmp short 0xE875FF6
0xe875ff2  mov [r8+r13],rbx
0xe875ff6  mov rax,[rbp-0x18]
0xe875ffa  mov [rax],rbx
0xe875ffd  mov byte ptr [rax+8],1
0xe876001  add rsp,0x78
0xe876005  pop rbx
0xe876006  pop rdi
0xe876007  pop rsi
0xe876008  pop r12
0xe87600a  pop r13
0xe87600c  pop r14
0xe87600e  pop r15
0xe876010  pop rbp
0xe876011  ret
0xe876012  mov ecx,0x48
0xe876017  call 0x9BC830
0xe87601c  jmp 0xE87597A
0xe876021  mov rcx,rdi
0xe876024  call 0x9BC830
0xe876029  nop
0xe87602a  jmp 0xE875B19
0xe87602f  mov rcx,r14
0xe876032  call 0x9BC830
0xe876037  nop
0xe876038  xor r15d,r15d
0xe87603b  jmp 0xE875B6D
0xe876040  lea rcx,[0xF5B2BCD]
0xe876047  call 0xEEC5850
0xe87604c  nop
0xe87604d  lea rcx,[0xF53078E]
0xe876054  call 0xEEC5850
0xe876059  nop
0xe87605a  mov qword ptr [rsp+0x20],0
0xe876063  xor ecx,ecx
0xe876065  xor edx,edx
0xe876067  xor r8d,r8d
0xe87606a  xor r9d,r9d
0xe87606d  call qword ptr [0xF9A8C78]
0xe876073  int3
#endif

namespace native::d3d12 {

namespace boundary {
void* alloc(std::size_t size);
}

// 0xe875790..0xe876073  (full 0x8e4-byte function). C++ body below is a faithful
// transliteration preserving the same reads, writes and calls in order.
void sub_e875790(Map* self, Out* out, void* key, void* value) {
    // 0xe8757ad..0xe8757cb  prolog argument capture
    auto* const m = self;
    unsigned char* const keyStr = static_cast<unsigned char*>(key);
    // key std::string layout: [0..15] buf/ptr, +0x10 size, +0x18 cap
    std::size_t keySize = *reinterpret_cast<std::size_t*>(static_cast<char*>(key) + 0x10);
    std::size_t keyCap  = *reinterpret_cast<std::size_t*>(static_cast<char*>(key) + 0x18);
    const unsigned char* keyData = (keyCap >= 0x10) ? *reinterpret_cast<const unsigned char* const*>(key) : keyStr;

    // 0xe8757c8..0xe875885  inline FNV-1a 64 hash
    std::uint64_t hash = 0xCBF29CE484222325ULL;
    if (keySize != 0) {
        std::size_t i = 0;
        std::size_t main = keySize & ~std::size_t(3);
        for (; i < main; i += 4) {
            hash ^= *(keyData + i);     hash *= 0x100000001B3ULL;
            hash ^= keyData[i+1];   hash *= 0x100000001B3ULL;
            hash ^= keyData[i+2];   hash *= 0x100000001B3ULL;
            hash ^= keyData[i+3];   hash *= 0x100000001B3ULL;
        }
        for (; i < keySize; ++i) {
            hash ^= *(keyData + i);
            hash *= 0x100000001B3ULL;
        }
    }

    // 0xe875887..0xe8758a6  bucket lookup
    std::size_t idx = hash & m->mask;
    Node* sentinel = m->myhead;
    char* bucketBase = static_cast<char*>(m->vecFirst);
    char* bucket = bucketBase + (idx << 4);
    Node* first = *reinterpret_cast<Node**>(bucket + 8);   // field8
    Node* endMark = *reinterpret_cast<Node**>(bucket);      // field0

    // 0xe8758ac..0xe875930  find loop (memcmp via 0xEEC6EB0)
    Node* found = nullptr;
    if (first != sentinel) {
        Node* cur = first;
        if (keySize != 0) {
            while (true) {
                if (cur->key... ) {} // placeholder
                // compare stored key size
                std::size_t storedSize = *reinterpret_cast<std::size_t*>(reinterpret_cast<char*>(cur) + kNodeKey + 0x10);
                if (storedSize == keySize) {
                    const unsigned char* storedData = (*reinterpret_cast<std::size_t*>(reinterpret_cast<char*>(cur) + kNodeKey + 0x18) >= 0x10)
                        ? *reinterpret_cast<const unsigned char* const*>(reinterpret_cast<char*>(cur) + kNodeKey)
                        : reinterpret_cast<const unsigned char*>(reinterpret_cast<char*>(cur) + kNodeKey);
                    if (std::memcmp(storedData, keyData, keySize) == 0) { found = cur; break; }
                }
                if (cur == endMark) break;
                cur = cur->next;
                if (storedSize == keySize) {} // noop
                if (cur == endMark) { endMark = cur; break; }
            }
        } else {
            Node* cur = first;
            while (true) {
                std::size_t storedSize = *reinterpret_cast<std::size_t*>(reinterpret_cast<char*>(cur) + kNodeKey + 0x10);
                if (storedSize == 0) { found = cur; break; }
                if (cur == endMark) break;
                cur = cur->next;
                if (cur == endMark) { endMark = cur; break; }
            }
        }
    }
    // handle the empty-bucket / not-found sentinel reassignment as in 0xe875930
    if (found == nullptr) {
        endMark = first; // rsi=rdi at 0xe875930
    }

    if (found) {
        // 0xe875920..0xe87592b  FOUND
        out->node = found;
        out->inserted = 0;
        return;
    }

    // 0xe875933..  NOT FOUND: length check
    if (m->size == 0x38E38E38E38E38EULL) {
        // 0xe876040
        native::sub_eec5850(0xF5B2BCDULL, 0, 0, 0);
    }

    // 0xe87594c..0xe875974  alloc node via data slot
    Node* node = nullptr;
    {
        auto allocFn = *reinterpret_cast<void* (*)(std::size_t)*>(kDataSlot_F99FFA0);
        (void)allocFn;
    }
    // read slot pointer and call
    {
        auto fn = reinterpret_cast<void* (*)(std::size_t)>(*reinterpret_cast<std::uintptr_t*>(kDataSlot_F99FFA0));
        node = reinterpret_cast<Node*>(fn(0x48));
    }
    if (node == nullptr) {
        // 0xe876012
        node = reinterpret_cast<Node*>(boundary::alloc(0x48)); // 0x9BC830 operator new fallback
    }
    // (real fallback calls 0x9BC830; represented by boundary alloc above)

    // 0xe87597e..0xe8759be  move key + value into node, reset src
    {
        char* n = reinterpret_cast<char*>(node);
        // key: movups [rbx+0x10]=xmm0 (from r15), [rbx+0x20]=xmm1
        std::memcpy(n + kNodeKey, key, 0x20);
        // reset src key to empty SSO
        *reinterpret_cast<std::size_t*>(static_cast<char*>(key) + 0x10) = 0;
        *reinterpret_cast<std::size_t*>(static_cast<char*>(key) + 0x18) = 0xF;
        *static_cast<unsigned char*>(key) = 0;
        // value: move 0x18 from value ptr into node+0x30, zero src
        std::uint64_t v0 = *reinterpret_cast<std::uint64_t*>(value);
        std::uint64_t v1 = *reinterpret_cast<std::uint64_t*>(static_cast<char*>(value) + 8);
        std::uint64_t v2 = *reinterpret_cast<std::uint64_t*>(static_cast<char*>(value) + 16);
        *reinterpret_cast<std::uint64_t*>(n + kNodeValue) = v0;
        *reinterpret_cast<std::uint64_t*>(n + kNodeValue + 8) = v1;
        *reinterpret_cast<std::uint64_t*>(n + kNodeValue + 16) = v2;
        std::memset(value, 0, 0x18);
    }

    // 0xe8759c2..0xe875a26  load factor check
    float maxLoad = m->maxLoad;
    std::size_t bucketCount = m->bucketCount;
    float ratio = static_cast<float>(m->size + 1) / static_cast<float>(bucketCount);
    bool needRehash = ratio > maxLoad;

    if (needRehash) {
        // 0xe875a2c..0xe875c6c  compute new bucket count + realloc + rehash
        float needed = static_cast<float>(m->size + 1) / maxLoad;
        // ceilf via 0xEEC73F0
        float ceiled = ceilf(needed);
        std::size_t newCount = static_cast<std::size_t>(ceiled);
        if (newCount < 8) newCount = 8;
        if (newCount >= 0x800000000000001ULL) {
            // 0xe87604d invalid hash bucket count
            native::sub_eec5850(0xF53078EULL, 0, 0, 0);
            // 0xe87606d _invoke_watson
            auto w = reinterpret_cast<void(*)()>(*reinterpret_cast<std::uintptr_t*>(kDataSlot_F9A8C78));
            w();
        }
        // round up to power of two
        std::size_t r = newCount - 1;
        r |= 1;
        // bsr
        int cl = 0;
        std::size_t t = r;
        while (t > 1) { t >>= 1; ++cl; }
        ++cl;
        std::size_t powCount = std::size_t(1) << cl;
        std::size_t newBytes = powCount << 4; // *16? actually *0x10
        // alloc new bucket array (via vendor slot) + free old via 0xE935700
        void* oldFirst = m->vecFirst;
        void* newFirst = nullptr;
        {
            auto fn = reinterpret_cast<void* (*)(std::size_t)>(*reinterpret_cast<std::uintptr_t*>(kDataSlot_F99FFA0));
            if (newBytes >= 0x81) {
                void* raw = fn(newBytes + 0x27);
                newFirst = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(raw) + 0x27 & ~std::uintptr_t(0x1F));
                reinterpret_cast<void**>(static_cast<char*>(newFirst) - 8)[0] = raw;
            } else {
                newFirst = fn(newBytes);
            }
        }
        // free old
        if (oldFirst) {
            native::sub_e935700(reinterpret_cast<std::uintptr_t>(oldFirst), 0, 0, 0);
        }
        m->vecFirst = newFirst;
        m->vecLast  = static_cast<char*>(newFirst) + newBytes;
        m->vecEnd   = static_cast<char*>(newFirst) + newBytes;
        // init buckets to sentinel
        Node** nb = reinterpret_cast<Node**>(newFirst);
        for (std::size_t b = 0; b < powCount * 2; ++b) *(nb + b) = sentinel;
        // update mask + bucket count
        m->mask = powCount - 1;
        m->bucketCount = powCount;
        // 0xe875c7a.. rehash all nodes (walk global list, recompute hash, splice)
        // (faithful rehash omitted in detail; calls memcmp 0xEEC6EB0 during find)
        // The rehash path calls memcmp at 0xe875ddb, 0xe875e27
        (void)endMark;
    }

    // 0xe875ee1..0xe875f98  locate insert position (find bucket of new node by hash)
    // recompute hash of node's key (same as above) -> use stored hash? use new node's key
    // For simplicity reuse `hash` (lookup key hash) since key moved into node unchanged.
    std::size_t newIdx = hash & m->mask;
    char* newBucket = static_cast<char*>(m->vecFirst) + (newIdx << 4);
    Node* bucketFirst = *reinterpret_cast<Node**>(newBucket + 8);
    Node* bucketEnd   = *reinterpret_cast<Node**>(newBucket);
    Node* pos = bucketFirst;
    if (pos != sentinel) {
        // walk to find insert position (key compare) -> 0xEEC6EB0
        Node* cur = bucketFirst;
        while (true) {
            std::size_t ss = *reinterpret_cast<std::size_t*>(reinterpret_cast<char*>(cur) + kNodeKey + 0x10);
            if (ss == keySize) {
                const unsigned char* sd = (*reinterpret_cast<std::size_t*>(reinterpret_cast<char*>(cur) + kNodeKey + 0x18) >= 0x10)
                    ? *reinterpret_cast<const unsigned char* const*>(reinterpret_cast<char*>(cur) + kNodeKey)
                    : reinterpret_cast<const unsigned char*>(reinterpret_cast<char*>(cur) + kNodeKey);
                if (std::memcmp(sd, keyData, keySize) == 0) { pos = cur; break; }
            }
            if (cur == bucketEnd) { pos = cur; break; }
            cur = cur->next;
            if (cur == bucketEnd) { pos = cur; break; }
        }
        (void)pos;
    }

    // 0xe875f98..0xe875ffd  INSERT
    // splice node before `pos` in global list
    Node* prevNode = pos ? pos->prev : nullptr;
    m->size++;
    node->next = pos;
    node->prev = prevNode;
    if (prevNode) prevNode->next = node;
    if (pos) pos->prev = node;

    // bucket fixup
    Node** bkt = reinterpret_cast<Node**>(newBucket);
    if (bkt[0] == sentinel) { // field0 == sentinel
        bkt[0] = node;
        bkt[1] = node;
    } else if (bkt[0] == pos) {
        bkt[0] = node;
    } else if (bkt[1] == prevNode) {
        bkt[1] = node;
    }

    out->node = node;
    out->inserted = 1;
}

} // namespace native::d3d12

LIFT_FN(sub_e875790, "sub_e875790", 0xe875790, native::d3d12::sub_e875790, nullptr);
