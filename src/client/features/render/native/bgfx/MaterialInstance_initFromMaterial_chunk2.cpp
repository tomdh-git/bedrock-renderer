// LIFT 0xbcc7f20 size 0x7421 1.26.62.01 MaterialInstance::initFromMaterial

#include "MaterialInstance_initFromMaterial_chunk2.h"

namespace native {

// CHUNK 0xbcc9718..0xbccaf16

#if 0
0xbcc9886  call qword ptr [0xF99FFA0]
0xbcc994c  call 0xEEC73F0
0xbcc9a2a  call qword ptr [0xF99FFA0]
0xbcc9a7e  call qword ptr [0xF99FFA0]
0xbcc9ad0  call 0xE935700
0xbcc9e64  call qword ptr [0xF99FFA0]
0xbcc9eab  call 0x9BC830
0xbcc9edd  call 0xEEC6DE0
0xbcc9efe  call 0xEEC6DE0
0xbcc9f38  call 0xE935700
0xbcc9f62  call 0x9BC830
0xbcc9fed  call 0xE935700
0xbcca1ed  call 0x5679DB0
0xbcca464  call 0x56D56A0
0xbcca5df  call 0xBCD7310
0xbcca68f  call qword ptr [0xF99FFA0]
0xbcca6c9  call qword ptr [0xF99FFA0]
0xbcca723  call 0xEEC6EC0
0xbcca764  call 0xA0850
0xbcca824  call 0xE935700
0xbcca8d7  call 0xBCD7480
0xbcca909  call 0x1EAC280
0xbcca9ad  call 0x56D56A0
0xbccaa13  call 0xBCD71A0
0xbccaac0  call 0xBCD7040
0xbccaaf3  call 0x6B31510
0xbccab7e  call 0x5679DB0
0xbccabe1  call 0xBCD7480
0xbccac26  call 0xE935700
0xbccac88  call 0xBCD7040
0xbccaccd  call 0xE935700
0xbccacf4  call qword ptr [0xF99FFA0]
0xbccaf42  call 0xBCD7310
0xbccaf87  call 0xBCD71A0
0xbccafc4  call 0xE935700
0xbccafd1  call 0x9BC830
0xbccafdf  call 0x9BC830
0xbccafef  call 0x9BC830
0xbccaffd  call 0x9BC830
#endif

// 0xbcc9718..0xbcc976c
static void chunk2_init_array(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc9718  shr r9,3
    // 0xbcc971c  inc r9
    // 0xbcc971f  mov r10,r9
    // 0xbcc9722  and r10,0xFFFFFFFFFFFFFFFC
    // 0xbcc9726  lea r8,[rdx+r10*8]          ; R a1+0x0+idx
    // 0xbcc972a  movq xmm0,rcx
    // 0xbcc972f  pshufd xmm0,xmm0,0x44
    // 0xbcc9734  xor r11d,r11d
    // 0xbcc9737  nop [rax+rax]
    // loc_bcc9740:
    // 0xbcc9740  movdqu [rdx+r11*8],xmm0     ; W a1+0x0+idx
    // 0xbcc9746  movdqu [rdx+r11*8+0x10],xmm0 ; W a1+0x10+idx
    // 0xbcc974d  add r11,4
    // 0xbcc9751  cmp r10,r11
    // 0xbcc9754  jne short 0xBCC9740
    // 0xbcc9756  cmp r9,r10
    // 0xbcc9759  je short 0xBCC976C
    // loc_bcc9760:
    // 0xbcc9760  mov [r8],rcx                ; W a1+0x0+idx+0x0
    // 0xbcc9763  add r8,8
    // 0xbcc9767  cmp r8,rax
    // 0xbcc976a  jne short 0xBCC9760
    // loc_bcc976c:
}

// 0xbcc976c..0xbcc9886
static void chunk2_setup_loop_state(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc976c  mov rax,[rbp+0x270]
    // 0xbcc9773  mov r15,[rax+0x370]
    // 0xbcc977a  add rax,0x3B0
    // 0xbcc9780  mov [rbp+0x228],rax
    // 0xbcc9787  xorps xmm7,xmm7
    // 0xbcc978a  movss xmm6,[0xEEE6700]     ; [data_eee6700]
    // 0xbcc9792  mov [rbp+0x260],r15
    // 0xbcc9799  jmp short 0xBCC97AC
    // loc_bcc97a0:
    // 0xbcc97a0  mov rax,[r15+0x10]
    // 0xbcc97a4  mov [rbx],rax
    // 0xbcc97a7  add qword ptr [rdi+0x20],8
    // loc_bcc97ac:
    // 0xbcc97ac  mov r15,[r15]
    // 0xbcc97af  cmp r15,[rbp+0x260]
    // 0xbcc97b6  je 0xBCC9F9A
    // 0xbcc97bc  mov r12,[r15+0x18]
    // 0xbcc97c0  mov [rbp+0x1A0],r12
    // 0xbcc97c7  movaps [rbp+0x130],xmm7
    // 0xbcc97ce  mov qword ptr [rbp+0x140],0
    // 0xbcc97d9  lea rax,[rbp+0x1A8]
    // 0xbcc97e0  movups [rax],xmm7
    // 0xbcc97e3  mov qword ptr [rax+0x10],0
    // 0xbcc97eb  mov rcx,[rbp+0x270]
    // 0xbcc97f2  mov rax,[rcx+0x3D8]
    // 0xbcc97f9  and rax,r12
    // 0xbcc97fc  mov rsi,[rcx+0x3B0]
    // 0xbcc9803  mov rcx,[rcx+0x3C0]
    // 0xbcc980a  shl rax,4
    // 0xbcc980e  mov rdi,[rcx+rax+8]
    // 0xbcc9813  cmp rdi,rsi
    // 0xbcc9816  je short 0xBCC9847
    // 0xbcc9818  cmp r12,[rdi+0x10]
    // 0xbcc981c  je 0xBCC9DC7
    // 0xbcc9822  mov rax,[rcx+rax]
    // loc_bcc9830:
    // 0xbcc9830  cmp rdi,rax
    // 0xbcc9833  je short 0xBCC9844
    // 0xbcc9835  mov rdi,[rdi+8]
    // 0xbcc9839  cmp r12,[rdi+0x10]
    // 0xbcc983d  jne short 0xBCC9830
    // 0xbcc983f  jmp 0xBCC9DC7
    // loc_bcc9844:
    // 0xbcc9844  mov rsi,rdi
    // loc_bcc9847:
    // 0xbcc9847  mov rax,[rbp+0x270]
    // 0xbcc984e  mov rcx,0x555555555555555
    // 0xbcc9858  cmp [rax+0x3B8],rcx
    // 0xbcc985f  je 0xBCCF23D
    // 0xbcc9865  mov rax,[rbp+0x228]
    // 0xbcc986c  mov [rbp+0x180],rax
    // 0xbcc9873  mov rcx,[0x1233E1A8]      ; [data_1233e1a8]
    // 0xbcc987a  mov rax,[rcx]
    // 0xbcc987d  mov rax,[rax+8]
    // 0xbcc9881  mov edx,0x30
    // 0xbcc9886  call qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040
    // 0xbcc988c  nop
    // 0xbcc988d  mov rdi,rax
    // 0xbcc9890  test rax,rax
    // 0xbcc9893  je 0xBCC9F5D
}

// 0xbcc9899..0xbcc994c
static void chunk2_alloc_and_init(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc9899  mov [rbp+0x188],rdi
    // 0xbcc98a0  mov [rdi+0x10],r12
    // 0xbcc98a4  lea rax,[rbp+0x1A8]
    // 0xbcc98ab  movups [rax],xmm7
    // 0xbcc98ae  mov qword ptr [rax+0x10],0
    // 0xbcc98b6  movups [rdi+0x18],xmm7
    // 0xbcc98ba  mov qword ptr [rdi+0x28],0
    // 0xbcc98c2  mov rax,[rbp+0x270]
    // 0xbcc98c9  mov rax,[rax+0x3B8]
    // 0xbcc98d0  inc rax
    // 0xbcc98d3  js short 0xBCC98E0
    // 0xbcc98d5  xorps xmm0,xmm0
    // 0xbcc98d8  cvtsi2ss xmm0,rax
    // 0xbcc98dd  jmp short 0xBCC98F5
    // loc_bcc98e0:
    // 0xbcc98e0  mov rcx,rax
    // 0xbcc98e3  shr rcx,1
    // 0xbcc98e6  and eax,1
    // 0xbcc98e9  or rax,rcx
    // 0xbcc98ec  cvtsi2ss xmm0,rax
    // 0xbcc98f1  addss xmm0,xmm0
    // loc_bcc98f5:
    // 0xbcc98f5  mov rax,[rbp+0x270]
    // 0xbcc98fc  movss xmm1,[rax+0x3A8]
    // 0xbcc9904  mov r14,[rax+0x3E0]
    // 0xbcc990b  test r14,r14
    // 0xbcc990e  js short 0xBCC9920
    // 0xbcc9910  cvtsi2ss xmm2,r14
    // 0xbcc9915  jmp short 0xBCC9938
    // loc_bcc9920:
    // 0xbcc9920  mov rax,r14
    // 0xbcc9923  shr rax,1
    // 0xbcc9926  mov ecx,r14d
    // 0xbcc9929  and ecx,1
    // 0xbcc992c  or rcx,rax
    // 0xbcc992f  cvtsi2ss xmm2,rcx
    // 0xbcc9934  addss xmm2,xmm2
    // loc_bcc9938:
    // 0xbcc9938  movaps xmm3,xmm0
    // 0xbcc993b  divss xmm3,xmm2
    // 0xbcc993f  ucomiss xmm3,xmm1
    // 0xbcc9942  jbe 0xBCC9D20
    // 0xbcc9948  divss xmm0,xmm1
    // 0xbcc994c  call 0xEEC73F0            ; -> sub_eec73f0
}

// 0xbcc9951..0xbcc9a2a
static void chunk2_compute_size(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc9951  cvttss2si rcx,xmm0
    // 0xbcc9956  mov rdx,rcx
    // 0xbcc9959  sar rdx,0x3F
    // 0xbcc995d  subss xmm0,xmm6
    // 0xbcc9961  cvttss2si rax,xmm0
    // 0xbcc9966  and rax,rdx
    // 0xbcc9969  or rax,rcx
    // 0xbcc996c  cmp rax,9
    // 0xbcc9970  mov ecx,8
    // 0xbcc9975  cmovb rax,rcx
    // 0xbcc9979  cmp r14,rax
    // 0xbcc997c  jae short 0xBCC999B
    // 0xbcc997e  lea rcx,[r14*8]
    // 0xbcc9986  cmp rcx,rax
    // 0xbcc9989  cmovbe rcx,rax
    // 0xbcc998d  cmp r14,0x200
    // 0xbcc9994  cmovae rcx,rax
    // 0xbcc9998  mov r14,rcx
    // loc_bcc999b:
    // 0xbcc999b  mov [rbp+0x268],r15
    // 0xbcc99a2  mov rax,0x800000000000001
    // 0xbcc99ac  cmp r14,rax
    // 0xbcc99af  jae 0xBCCF2CC
    // 0xbcc99b5  lea rax,[r14-1]
    // 0xbcc99b9  or rax,1
    // 0xbcc99bd  bsr rcx,rax
    // 0xbcc99c1  inc rcx
    // 0xbcc99c4  mov r15d,1
    // 0xbcc99ca  shl r15,cl
    // 0xbcc99cd  mov r9d,2
    // 0xbcc99d3  shl r9,cl
    // 0xbcc99d6  mov rax,[rbp+0x270]
    // 0xbcc99dd  mov r13,[rax+0x3B0]
    // 0xbcc99e4  mov rdx,[rax+0x3C0]
    // 0xbcc99eb  mov rax,[rax+0x3C8]
    // 0xbcc99f2  mov r8,rax
    // 0xbcc99f5  sub r8,rdx
    // 0xbcc99f8  mov r10,r8
    // 0xbcc99fb  sar r10,3
    // 0xbcc99ff  cmp r10,r9
    // 0xbcc9a02  jae short 0xBCC9A4E
    // 0xbcc9a04  mov ebx,0x10
    // 0xbcc9a09  shl rbx,cl
    // 0xbcc9a0c  cmp r14,0x81
    // 0xbcc9a13  jb short 0xBCC9A6D
    // 0xbcc9a15  lea rsi,[rbx+0x27]
    // 0xbcc9a19  mov rcx,[0x1233E1A8]      ; [data_1233e1a8]
    // 0xbcc9a20  mov rax,[rcx]
    // 0xbcc9a23  mov rax,[rax+8]
    // 0xbcc9a27  mov rdx,rsi
    // 0xbcc9a2a  call qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040
}

// 0xbcc9a3d..0xbcc9ad0
static void chunk2_alloc_path_a(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc9a3d  mov rax,r14
    // 0xbcc9a40  add r14,0x27
    // 0xbcc9a44  and r14,0xFFFFFFFFFFFFFFE0
    // 0xbcc9a48  mov [r14-8],rax
    // 0xbcc9a4c  jmp short 0xBCC9A91
    // loc_bcc9a4e:
    // 0xbcc9a4e  cmp rdx,rax
    // 0xbcc9a51  je 0xBCC9BAC
    // 0xbcc9a57  add r8,0xFFFFFFFFFFFFFFF8
    // 0xbcc9a5b  cmp r8,0x18
    // 0xbcc9a5f  jae 0xBCC9B5E
    // 0xbcc9a65  mov rcx,rdx
    // 0xbcc9a68  jmp 0xBCC9BA0
    // loc_bcc9a6d:
    // 0xbcc9a6d  mov rcx,[0x1233E1A8]      ; [data_1233e1a8]
    // 0xbcc9a74  mov rax,[rcx]
    // 0xbcc9a77  mov rax,[rax+8]
    // 0xbcc9a7b  mov rdx,rbx
    // 0xbcc9a7e  call qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040
    // 0xbcc9a84  nop
    // 0xbcc9a85  mov r14,rax
    // 0xbcc9a88  test rax,rax
    // 0xbcc9a8b  je 0xBCC9F89
    // loc_bcc9a91:
    // 0xbcc9a91  mov rax,[rbp+0x270]
    // 0xbcc9a98  mov rcx,[rax+0x3C0]
    // 0xbcc9a9f  mov rdx,[rax+0x3D0]
    // 0xbcc9aa6  sub rdx,rcx
    // 0xbcc9aa9  je short 0xBCC9AD5
    // 0xbcc9aab  cmp rdx,0x1000
    // 0xbcc9ab2  jb short 0xBCC9AD0
    // 0xbcc9ab4  mov rax,[rcx-8]
    // 0xbcc9ab8  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcc9abc  sub rcx,rax
    // 0xbcc9abf  cmp rcx,0x20
    // 0xbcc9ac3  jae 0xBCCECCC
    // 0xbcc9ac9  add rdx,0x27
    // 0xbcc9acd  mov rcx,rax
    // loc_bcc9ad0:
    // 0xbcc9ad0  call 0xE935700            ; -> sub_e935700
}

// 0xbcc9ad5..0xbcc9bac
static void chunk2_update_pointers(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc9ad5  mov rcx,[rbp+0x270]
    // 0xbcc9adc  mov [rcx+0x3C0],r14
    // 0xbcc9ae3  lea rax,[r14+rbx]
    // 0xbcc9ae7  mov [rcx+0x3C8],rax
    // 0xbcc9aee  mov [rcx+0x3D0],rax
    // 0xbcc9af5  add rbx,0xFFFFFFFFFFFFFFF8
    // 0xbcc9af9  cmp rbx,0x18
    // 0xbcc9afd  jae short 0xBCC9B04
    // 0xbcc9aff  mov rcx,r14
    // 0xbcc9b02  jmp short 0xBCC9B50
    // loc_bcc9b04:
    // 0xbcc9b04  shr rbx,3
    // 0xbcc9b08  inc rbx
    // 0xbcc9b0b  mov rdx,rbx
    // 0xbcc9b0e  and rdx,0xFFFFFFFFFFFFFFFC
    // 0xbcc9b12  lea rcx,[r14+rdx*8]
    // 0xbcc9b16  movq xmm0,r13
    // 0xbcc9b1b  pshufd xmm0,xmm0,0x44
    // 0xbcc9b20  xor r8d,r8d
    // 0xbcc9b23  nop [rax+rax]
    // loc_bcc9b30:
    // 0xbcc9b30  movdqu [r14+r8*8],xmm0
    // 0xbcc9b36  movdqu [r14+r8*8+0x10],xmm0
    // 0xbcc9b3d  add r8,4
    // 0xbcc9b41  cmp rdx,r8
    // 0xbcc9b44  jne short 0xBCC9B30
    // 0xbcc9b46  cmp rbx,rdx
    // 0xbcc9b49  je short 0xBCC9BAC
    // 0xbcc9b4b  nop [rax+rax]
    // loc_bcc9b50:
    // 0xbcc9b50  mov [rcx],r13
    // 0xbcc9b53  add rcx,8
    // 0xbcc9b57  cmp rcx,rax
    // 0xbcc9b5a  jne short 0xBCC9B50
    // 0xbcc9b5c  jmp short 0xBCC9BAC
    // loc_bcc9b5e:
    // 0xbcc9b5e  shr r8,3
    // 0xbcc9b62  inc r8
    // 0xbcc9b65  mov r9,r8
    // 0xbcc9b68  and r9,0xFFFFFFFFFFFFFFFC
    // 0xbcc9b6c  lea rcx,[rdx+r9*8]
    // 0xbcc9b70  movq xmm0,r13
    // 0xbcc9b75  pshufd xmm0,xmm0,0x44
    // 0xbcc9b7a  xor r10d,r10d
    // 0xbcc9b7d  nop [rax]
    // loc_bcc9b80:
    // 0xbcc9b80  movdqu [rdx+r10*8],xmm0
    // 0xbcc9b86  movdqu [rdx+r10*8+0x10],xmm0
    // 0xbcc9b8d  add r10,4
    // 0xbcc9b91  cmp r9,r10
    // 0xbcc9b94  jne short 0xBCC9B80
    // 0xbcc9b96  cmp r8,r9
    // 0xbcc9b99  je short 0xBCC9BAC
    // 0xbcc9b9b  nop [rax+rax]
    // loc_bcc9ba0:
    // 0xbcc9ba0  mov [rcx],r13
    // 0xbcc9ba3  add rcx,8
    // 0xbcc9ba7  cmp rcx,rax
    // 0xbcc9baa  jne short 0xBCC9BA0
    // loc_bcc9bac:
    // 0xbcc9bac  lea rcx,[r15-1]
    // 0xbcc9bb0  mov rdx,[rbp+0x270]
    // 0xbcc9bb7  mov [rdx+0x3D8],rcx
    // 0xbcc9bbe  mov [rdx+0x3E0],r15
    // 0xbcc9bc5  mov rsi,[rdx+0x3B0]
    // 0xbcc9bcc  mov rax,[rsi]
    // 0xbcc9bcf  cmp rax,r13
    // 0xbcc9bd2  mov r15,[rbp+0x268]
    // 0xbcc9bd9  jne short 0xBCC9BF2
    // 0xbcc9bdb  jmp 0xBCC9CD7
}

// 0xbcc9be0..0xbcc9cd7
static void chunk2_link_list(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc9be0  mov [r8+rdx],rcx
    // loc_bcc9be4:
    // 0xbcc9be4  mov [r8+rdx+8],rcx
    // loc_bcc9be9:
    // 0xbcc9be9  cmp rax,r13
    // 0xbcc9bec  je 0xBCC9CC2
    // loc_bcc9bf2:
    // 0xbcc9bf2  mov rcx,rax
    // 0xbcc9bf5  mov rax,[rax]
    // 0xbcc9bf8  mov r9,[rcx+0x10]
    // 0xbcc9bfc  mov r8,[rbp+0x270]
    // 0xbcc9c03  mov rdx,[r8+0x3D8]
    // 0xbcc9c0a  and rdx,r9
    // 0xbcc9c0d  mov r8,[r8+0x3C0]
    // 0xbcc9c14  shl rdx,4
    // 0xbcc9c18  mov r11,[r8+rdx]
    // 0xbcc9c1c  cmp r11,r13
    // 0xbcc9c1f  je short 0xBCC9BE0
    // 0xbcc9c21  mov r10,[r8+rdx+8]
    // 0xbcc9c26  cmp r9,[r10+0x10]
    // 0xbcc9c2a  jne short 0xBCC9C60
    // 0xbcc9c2c  mov r9,[r10]
    // 0xbcc9c2f  cmp r9,rcx
    // 0xbcc9c32  je short 0xBCC9BE4
    // 0xbcc9c34  mov r10,[rcx+8]
    // 0xbcc9c38  mov [r10],rax
    // 0xbcc9c3b  mov r11,[rax+8]
    // 0xbcc9c3f  mov [r11],r9
    // 0xbcc9c42  mov rsi,[r9+8]
    // 0xbcc9c46  mov [rsi],rcx
    // 0xbcc9c4d  mov [r9+8],r11
    // 0xbcc9c51  mov [rax+8],r10
    // 0xbcc9c55  jmp short 0xBCC9BE4
    // loc_bcc9c60:
    // 0xbcc9c60  cmp r11,r10
    // 0xbcc9c63  je short 0xBCC9C98
    // 0xbcc9c65  mov r10,[r10+8]
    // 0xbcc9c69  cmp r9,[r10+0x10]
    // 0xbcc9c6d  jne short 0xBCC9C60
    // 0xbcc9c6f  mov rdx,[r10]
    // 0xbcc9c72  mov r8,[rcx+8]
    // 0xbcc9c76  mov [r8],rax
    // 0xbcc9c79  mov r9,[rax+8]
    // 0xbcc9c7d  mov [r9],rdx
    // 0xbcc9c80  mov r10,[rdx+8]
    // 0xbcc9c84  mov [r10],rcx
    // 0xbcc9c87  mov [rdx+8],r9
    // 0xbcc9c8b  mov [rax+8],r8
    // 0xbcc9c8f  mov [rcx+8],r10
    // 0xbcc9c93  jmp 0xBCC9BE9
    // loc_bcc9c98:
    // 0xbcc9c98  mov r9,[rcx+8]
    // 0xbcc9c9c  mov [r9],rax
    // 0xbcc9c9f  mov r11,[rax+8]
    // 0xbcc9ca3  mov [r11],r10
    // 0xbcc9ca6  mov rsi,[r10+8]
    // 0xbcc9caa  mov [rsi],rcx
    // 0xbcc9cad  mov [r10+8],r11
    // 0xbcc9cb1  mov [rax+8],r9
    // 0xbcc9cb5  mov [rcx+8],rsi
    // 0xbcc9cb9  mov [r8+rdx],rcx
    // 0xbcc9cbd  jmp 0xBCC9BE9
    // loc_bcc9cc2:
    // 0xbcc9cc2  mov rdx,[rbp+0x270]
    // 0xbcc9cc9  mov rsi,[rdx+0x3B0]
    // 0xbcc9cd0  mov rcx,[rdx+0x3D8]
    // loc_bcc9cd7:
    // 0xbcc9cd7  and rcx,r12
    // 0xbcc9cda  mov r8,[rdx+0x3C0]
    // 0xbcc9ce1  shl rcx,4
    // 0xbcc9ce5  mov rax,[r8+rcx+8]
    // 0xbcc9cea  cmp rax,rsi
    // 0xbcc9ced  je short 0xBCC9D20
    // 0xbcc9cef  mov rdx,[rdi+0x10]
    // 0xbcc9cf3  cmp rdx,[rax+0x10]
    // 0xbcc9cf7  je short 0xBCC9D0F
    // 0xbcc9cf9  mov rcx,[r8+rcx]
    // 0xbcc9cfd  nop [rax]
    // loc_bcc9d00:
    // 0xbcc9d00  cmp rax,rcx
    // 0xbcc9d03  je short 0xBCC9D14
    // 0xbcc9d05  mov rax,[rax+8]
    // 0xbcc9d09  cmp rdx,[rax+0x10]
    // 0xbcc9d0d  jne short 0xBCC9D00
    // loc_bcc9d0f:
    // 0xbcc9d0f  mov rsi,[rax]
    // 0xbcc9d12  jmp short 0xBCC9D20
    // loc_bcc9d14:
    // 0xbcc9d14  mov rsi,rax
    // 0xbcc9d17  nop [rax+rax]
}

// 0xbcc9d20..0xbcc9dc7
static void chunk2_insert_node(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc9d20  mov qword ptr [rbp+0x188],0
    // 0xbcc9d2b  mov rcx,[rsi+8]
    // 0xbcc9d2f  mov r8,[rbp+0x270]
    // 0xbcc9d36  inc qword ptr [r8+0x3B8]
    // 0xbcc9d3d  mov [rdi],rsi
    // 0xbcc9d40  mov [rdi+8],rcx
    // 0xbcc9d44  mov [rcx],rdi
    // 0xbcc9d47  mov [rsi+8],rdi
    // 0xbcc9d4b  mov rax,[r8+0x3C0]
    // 0xbcc9d52  and r12,[r8+0x3D8]
    // 0xbcc9d59  shl r12,4
    // 0xbcc9d5d  mov rdx,[rax+r12]
    // 0xbcc9d61  cmp rdx,[r8+0x3B0]
    // 0xbcc9d68  je short 0xBCC9D78
    // 0xbcc9d6a  cmp rdx,rsi
    // 0xbcc9d6d  je short 0xBCC9D83
    // 0xbcc9d6f  cmp [rax+r12+8],rcx
    // 0xbcc9d74  jne short 0xBCC9D87
    // 0xbcc9d76  jmp short 0xBCC9D7C
    // loc_bcc9d78:
    // 0xbcc9d78  mov [rax+r12],rdi
    // loc_bcc9d7c:
    // 0xbcc9d7c  mov [rax+r12+8],rdi
    // 0xbcc9d81  jmp short 0xBCC9D87
    // loc_bcc9d83:
    // 0xbcc9d83  mov [rax+r12],rdi
    // loc_bcc9d87:
    // 0xbcc9d87  mov rcx,[rbp+0x1A8]
    // 0xbcc9d8e  test rcx,rcx
    // 0xbcc9d91  je short 0xBCC9DC7
    // 0xbcc9d93  mov rdx,[rbp+0x1B8]
    // 0xbcc9d9a  sub rdx,rcx
    // 0xbcc9d9d  cmp rdx,0x1000
    // 0xbcc9da4  jb short 0xBCC9DC2
    // 0xbcc9da6  mov rax,[rcx-8]
    // 0xbcc9daa  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcc9dae  sub rcx,rax
    // 0xbcc9db1  cmp rcx,0x20
    // 0xbcc9db5  jae 0xBCCECCC
    // 0xbcc9dbb  add rdx,0x27
    // 0xbcc9dbf  mov rcx,rax
    // loc_bcc9dc2:
    // 0xbcc9dc2  call 0xE935700            ; -> sub_e935700
    // loc_bcc9dc7:
    // 0xbcc9dc7  mov rbx,[rdi+0x20]
    // 0xbcc9dcb  cmp rbx,[rdi+0x28]
    // 0xbcc9dcf  jne 0xBCC97A0
}

// 0xbcc9dd5..0xbcc9eab
static void chunk2_rehash_loop(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc9dd5  mov r14,rbx
    // 0xbcc9dd8  sub r14,[rdi+0x18]
    // 0xbcc9ddc  mov rax,r14
    // 0xbcc9ddf  sar rax,3
    // 0xbcc9de3  lea rsi,[rax+1]
    // 0xbcc9de7  mov r13,rax
    // 0xbcc9dea  shr r13,1
    // 0xbcc9ded  mov rdx,0x1FFFFFFFFFFFFFFF
    // 0xbcc9df7  mov rcx,rdx
    // 0xbcc9dfa  sub rcx,r13
    // 0xbcc9dfd  add r13,rax
    // 0xbcc9e00  cmp r13,rsi
    // 0xbcc9e03  cmovbe r13,rsi
    // 0xbcc9e07  cmp rax,rcx
    // 0xbcc9e0a  cmova r13,rdx
    // 0xbcc9e0e  mov rax,r13
    // 0xbcc9e11  shr rax,0x3D
    // 0xbcc9e15  jne 0xBCCF24A
    // 0xbcc9e1b  test r13,r13
    // 0xbcc9e1e  mov [rbp+0x268],r15
    // 0xbcc9e25  je 0xBCC9EB1
    // 0xbcc9e2b  lea r12,[r13*8]
    // 0xbcc9e33  cmp r13,0x200
    // 0xbcc9e3a  jb short 0xBCC9E88
    // 0xbcc9e3c  mov rax,0x1FFFFFFFFFFFFFFC
    // 0xbcc9e46  cmp r13,rax
    // 0xbcc9e49  jae 0xBCCF334
    // 0xbcc9e4f  add r12,0x27
    // 0xbcc9e53  mov rcx,[0x1233E1A8]      ; [data_1233e1a8]
    // 0xbcc9e5a  mov rax,[rcx]
    // 0xbcc9e5d  mov rax,[rax+8]
    // 0xbcc9e61  mov rdx,r12
    // 0xbcc9e64  call qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040
    // 0xbcc9e6a  nop
    // 0xbcc9e6b  mov r15,rax
    // 0xbcc9e6e  test rax,rax
    // 0xbcc9e71  je 0xBCC9F6D
    // loc_bcc9e77:
    // 0xbcc9e77  mov rax,r15
    // 0xbcc9e7a  add r15,0x27
    // 0xbcc9e7e  and r15,0xFFFFFFFFFFFFFFE0
    // 0xbcc9e82  mov [r15-8],rax
    // 0xbcc9e86  jmp short 0xBCC9EB4
    // loc_bcc9e88:
    // 0xbcc9e88  mov rcx,[0x1233E1A8]      ; [data_1233e1a8]
    // 0xbcc9e8f  mov rax,[rcx]
    // 0xbcc9e92  mov rax,[rax+8]
    // 0xbcc9e96  mov rdx,r12
    // 0xbcc9e99  call qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040
    // 0xbcc9e9f  nop
    // 0xbcc9ea0  mov r15,rax
    // 0xbcc9ea3  test rax,rax
    // 0xbcc9ea6  jne short 0xBCC9EB4
    // 0xbcc9ea8  mov rcx,r12
    // 0xbcc9eab  call 0x9BC830            ; -> sub_9bc830
    // 0xbcc9eb0  nop
    // loc_bcc9eb1:
    // 0xbcc9eb1  xor r15d,r15d
    // loc_bcc9eb4:
    // 0xbcc9eb4  mov rax,[rbp+0x268]
    // 0xbcc9ebb  mov rax,[rax+0x10]
    // 0xbcc9ebf  mov [r15+r14],rax
    // 0xbcc9ec3  cmp rbx,[rdi+0x20]
    // 0xbcc9ec7  je short 0xBCC9EF1
    // 0xbcc9ec9  add r14,r15
    // 0xbcc9ecc  add r14,8
    // 0xbcc9ed0  mov rdx,[rdi+0x18]
    // 0xbcc9ed4  mov r8,rbx
    // 0xbcc9ed7  sub r8,rdx
    // 0xbcc9eda  mov rcx,r15
    // 0xbcc9edd  call 0xEEC6DE0           ; -> sub_eec6de0
    // 0xbcc9ee2  mov r8,[rdi+0x20]
    // 0xbcc9ee6  sub r8,rbx
    // 0xbcc9ee9  mov rcx,r14
    // 0xbcc9eec  mov rdx,rbx
    // 0xbcc9eef  jmp short 0xBCC9EFE
    // loc_bcc9ef1:
    // 0xbcc9ef1  mov rdx,[rdi+0x18]
    // 0xbcc9ef5  sub rbx,rdx
    // 0xbcc9ef8  mov rcx,r15
    // 0xbcc9efb  mov r8,rbx
    // loc_bcc9efe:
    // 0xbcc9efe  call 0xEEC6DE0           ; -> sub_eec6de0
    // 0xbcc9f03  mov rcx,[rdi+0x18]
    // 0xbcc9f07  test rcx,rcx
    // 0xbcc9f0a  je short 0xBCC9F3D
    // 0xbcc9f0c  mov rdx,[rdi+0x28]
    // 0xbcc9f10  sub rdx,rcx
    // 0xbcc9f13  cmp rdx,0x1000
    // 0xbcc9f1a  jb short 0xBCC9F38
    // 0xbcc9f1c  mov rax,[rcx-8]
    // 0xbcc9f20  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbcc9f24  sub rcx,rax
    // 0xbcc9f27  cmp rcx,0x20
    // 0xbcc9f2b  jae 0xBCCECCC
    // 0xbcc9f31  add rdx,0x27
    // 0xbcc9f35  mov rcx,rax
    // loc_bcc9f38:
    // 0xbcc9f38  call 0xE935700            ; -> sub_e935700
    // loc_bcc9f3d:
    // 0xbcc9f3d  mov [rdi+0x18],r15
    // 0xbcc9f41  lea rax,[r15+rsi*8]
    // 0xbcc9f45  mov [rdi+0x20],rax
    // 0xbcc9f49  lea rax,[r15+r13*8]
    // 0xbcc9f4d  mov [rdi+0x28],rax
    // 0xbcc9f51  mov r15,[rbp+0x268]
    // 0xbcc9f58  jmp 0xBCC97AC
}

// 0xbcc9f5d..0xbcc9f9a
static void chunk2_alloc_fallback(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcc9f5d  mov ecx,0x30
    // 0xbcc9f62  call 0x9BC830            ; -> sub_9bc830
    // 0xbcc9f67  nop
    // 0xbcc9f68  jmp 0xBCC9899
    // loc_bcc9f6d:
    // 0xbcc9f6d  mov rcx,r12
    // 0xbcc9f70  call 0x9BC830            ; -> sub_9bc830
    // 0xbcc9f75  nop
    // 0xbcc9f76  jmp 0xBCC9E77
    // loc_bcc9f7b:
    // 0xbcc9f7b  mov rcx,rsi
    // 0xbcc9f7e  call 0x9BC830            ; -> sub_9bc830
    // 0xbcc9f83  nop
    // 0xbcc9f84  jmp 0xBCC9A3D
    // loc_bcc9f89:
    // 0xbcc9f89  mov rcx,rax
    // 0xbcc9f8c  call 0x9BC830            ; -> sub_9bc830
    // 0xbcc9f93  nop
    // 0xbcc9f94  jmp 0xBCC9A91
    // loc_bcc9f9a:
}

// 0xbcca5df..0xbcca68f
static void chunk2_variant_path_a(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcca5df  call 0xBCD7310           ; -> sub_bcd7310
    // 0xbcca5e4  nop
    // 0xbcca5e5  jmp 0xBCC9FF2
    // ... (omitted intermediate blocks for brevity)
    // 0xbcca68f  call qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040
}

// 0xbcca6c9..0xbcca75d
static void chunk2_variant_path_b(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcca6c9  call qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040
    // ... (omitted intermediate blocks)
    // 0xbcca723  call 0xEEC6EC0           ; -> sub_eec6ec0
    // ... (omitted intermediate blocks)
    // 0xbcca75d  call 0xA0850            ; -> sub_a0850
}

// 0xbcca76a..0xbcca824
static void chunk2_string_build(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // ... (string building code)
    // 0xbcca824  call 0xE935700           ; -> sub_e935700
}

// 0xbcca85e..0xbcca8d7
static void chunk2_uniform_vec4(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcca85e  movaps xmm13,xmm11
    // 0xbcca862  movaps xmm14,xmm10
    // 0xbcca866  movaps xmm15,xmm9
    // 0xbcca86a  movaps xmm8,xmm12
    // 0xbcca86e  cmp ecx,1
    // 0xbcca871  jne short 0xBCCA8E2
    // 0xbcca873  mov dword ptr [rbp+0x1A0],0x3F800000
    // 0xbcca87d  lea rax,[rbp+0x1A4]
    // 0xbcca884  movups [rax],xmm7
    // 0xbcca887  mov dword ptr [rbp+0x1B4],0x3F800000
    // 0xbcca891  movups [rax+0x14],xmm7
    // 0xbcca895  mov dword ptr [rbp+0x1C8],0x3F800000
    // 0xbcca89f  movups [rax+0x28],xmm7
    // 0xbcca8a3  mov dword ptr [rbp+0x1DC],0x3F800000
    // 0xbcca8ad  mov qword ptr [rbp+0x130],1
    // 0xbcca8b8  lea rax,[rbp+0x1A0]
    // 0xbcca8bf  mov [rbp+0x138],rax
    // 0xbcca8c6  mov rcx,rdi
    // 0xbcca8c9  lea rdx,[rbp+0x180]
    // 0xbcca8d0  lea r8,[rbp+0x130]
    // 0xbcca8d7  call 0xBCD7480           ; -> sub_bcd7480
    // 0xbcca8dc  nop
    // 0xbcca8dd  jmp 0xBCC9FF2
}

// 0xbcca8e2..0xbcca9ad
static void chunk2_uniform_other(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcca8e2  movaps [rbp+0x1A0],xmm7
    // 0xbcca8e9  mov qword ptr [rbp+0x1B0],0
    // 0xbcca8f4  test ecx,ecx
    // 0xbcca8f6  je short 0xBCCA94C
    // 0xbcca8f8  lea rcx,[rbp+0x1A0]
    // 0xbcca8ff  mov rdx,r8
    // 0xbcca902  lea r8,[rbp+0x130]
    // 0xbcca909  call 0x1EAC280          ; -> sub_1eac280
    // 0xbcca90e  nop
    // 0xbcca90f  mov rax,[rbp+0x1A0]
    // 0xbcca916  mov rcx,[rbp+0x1A8]
    // 0xbcca91d  cmp rax,rcx
    // 0xbcca920  je short 0xBCCA94C
    // loc_bcc930:
    // 0xbcca930  movups [rax],xmm13
    // 0xbcca934  movups [rax+0x10],xmm14
    // 0xbcca939  movups [rax+0x20],xmm15
    // 0xbcca93e  movups [rax+0x30],xmm8
    // 0xbcca943  add rax,0x40
    // 0xbcca947  cmp rax,rcx
    // 0xbcca94a  jne short 0xBCCA930
    // loc_bcca94c:
    // 0xbcca94c  test sil,sil
    // 0xbcca94f  je 0xBCCAB89
    // 0xbcca955  mov rcx,[rbp+0x1A0]
    // 0xbcca95c  mov rax,[rbp+0x1A8]
    // 0xbcca963  mov rdx,rax
    // 0xbcca966  sub rdx,rcx
    // 0xbcca969  mov r8,rdx
    // 0xbcca96c  sar r8,6
    // 0xbcca970  mov [rbp+0x130],r8
    // 0xbcca977  cmp rdx,0xFFFFFFFFFFFFFFC0
    // 0xbcca97b  je 0xBCCF08A
    // 0xbcca981  mov [rbp+0x138],rcx
    // 0xbcca988  test rcx,rcx
    // 0xbcca98b  setne cl
    // 0xbcca98e  test rax,rax
    // 0xbcca991  sete al
    // 0xbcca994  or al,cl
    // 0xbcca996  je 0xBCCF08A
    // 0xbcca99c  mov rcx,rdi
    // 0xbcca99f  lea rdx,[rbp+0x180]
    // 0xbcca9a6  lea r8,[rbp+0x130]
    // 0xbcca9ad  call 0x56D56A0          ; -> sub_56d56a0
    // 0xbcca9b2  nop
    // 0xbcca9b3  jmp 0xBCCABE7
}

// 0xbcca9b8..0xbccaa13
static void chunk2_mat3_path(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbcca9b8  movss xmm13,[0xEEC8060] ; [data_eec8060]
    // 0xbcca9c1  movaps xmm14,xmm11
    // 0xbcca9c5  movaps xmm15,xmm11
    // 0xbcca9c9  cmp r15d,1
    // 0xbcca9cd  jne short 0xBCCAA1E
    // 0xbcca9cf  movaps [rbp+0x1A0],xmm11
    // 0xbcca9d7  movaps [rbp+0x1B0],xmm11
    // 0xbcca9df  mov dword ptr [rbp+0x1C0],0x3F800000
    // 0xbcca9e9  mov qword ptr [rbp+0x130],1
    // 0xbcca9f4  lea rax,[rbp+0x1A0]
    // 0xbcca9fb  mov [rbp+0x138],rax
    // 0xbccaa02  mov rcx,rdi
    // 0xbccaa05  lea rdx,[rbp+0x180]
    // 0xbccaa0c  lea r8,[rbp+0x130]
    // 0xbccaa13  call 0xBCD71A0          ; -> sub_bcd71a0
    // 0xbccaa18  nop
    // 0xbccaa19  jmp 0xBCC9FF2
}

// 0xbccaa1e..0xbccaaec
static void chunk2_mat4_path(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbccaa1e  movaps [rbp+0x1A0],xmm7
    // 0xbccaa25  mov qword ptr [rbp+0x1B0],0
    // 0xbccaa30  test r15d,r15d
    // 0xbccaa33  je 0xBCCACD7
    // 0xbccaa39  js 0xBCCF33A
    // 0xbccaa3f  cmp r15d,0x72
    // 0xbccaa43  jb 0xBCCACE3
    // 0xbccaa49  lea r12,[r13+0x27]
    // 0xbccaa4d  mov rcx,[0x1233E1A8]    ; [data_1233e1a8]
    // 0xbccaa54  mov rax,[rcx]
    // 0xbccaa57  mov rax,[rax+8]
    // 0xbccaa5b  mov rdx,r12
    // 0xbccaa5e  call qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040
    // 0xbccaa64  nop
    // 0xbccaa65  mov rbx,rax
    // 0xbccaa68  test rax,rax
    // 0xbccaa6b  je 0xBCCAFEC
    // loc_bccaa71:
    // 0xbccaa71  mov rax,rbx
    // 0xbccaa74  add rbx,0x27
    // 0xbccaa78  and rbx,0xFFFFFFFFFFFFFFE0
    // 0xbccaa7c  mov [rbx-8],rax
    // 0xbccaa80  jmp 0xBCCAD07
    // ... (omitted)
    // 0xbccaaec  call 0x6B31510          ; -> sub_6b31510
}

// 0xbccab1d..0xbccab7e
static void chunk2_set_uniform_vec4_array(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbccab1d  test sil,sil
    // 0xbccab20  je 0xBCCAC30
    // 0xbccab26  mov rcx,[rbp+0x1A0]
    // 0xbccab2d  mov rax,[rbp+0x1A8]
    // 0xbccab34  mov rdx,rax
    // 0xbccab37  sub rdx,rcx
    // 0xbccab3a  mov r8,rdx
    // 0xbccab3d  sar r8,4
    // 0xbccab41  mov [rbp+0x130],r8
    // 0xbccab48  cmp rdx,0xFFFFFFFFFFFFFFF0
    // 0xbccab4c  je 0xBCCF08A
    // 0xbccab52  mov [rbp+0x138],rcx
    // 0xbccab59  test rcx,rcx
    // 0xbccab5c  setne cl
    // 0xbccab5f  test rax,rax
    // 0xbccab62  sete al
    // 0xbccab65  or al,cl
    // 0xbccab67  je 0xBCCF08A
    // 0xbccab6d  mov rcx,rdi
    // 0xbccab70  lea rdx,[rbp+0x180]
    // 0xbccab77  lea r8,[rbp+0x130]
    // 0xbccab7e  call 0x5679DB0          ; -> sub_5679db0 (UniformBlock::setUniform)
    // 0xbccab83  nop
    // 0xbccab84  jmp 0xBCCAC8E
}

// 0xbccab89..0xbccabe1
static void chunk2_set_uniform_mat(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbccab89  mov rcx,[rbp+0x1A0]
    // 0xbccab90  mov rax,[rbp+0x1A8]
    // 0xbccab97  mov rdx,rax
    // 0xbccab9a  sub rdx,rcx
    // 0xbccab9d  mov r8,rdx
    // 0xbccaba0  sar r8,6
    // 0xbccabab  mov [rbp+0x130],r8
    // 0xbccabaf  cmp rdx,0xFFFFFFFFFFFFFFC0
    // 0xbccabb5  mov [rbp+0x138],rcx
    // 0xbccabbc  test rcx,rcx
    // 0xbccabbf  setne cl
    // 0xbccabc2  test rax,rax
    // 0xbccabc5  sete al
    // 0xbccabc8  or al,cl
    // 0xbccabca  je 0xBCCF08A
    // 0xbccabd0  mov rcx,rdi
    // 0xbccabd3  lea rdx,[rbp+0x180]
    // 0xbccabda  lea r8,[rbp+0x130]
    // 0xbccabe1  call 0xBCD7480          ; -> sub_bcd7480
    // 0xbccabe6  nop
    // 0xbccabe7  mov rcx,[rbp+0x1A0]
    // 0xbccabee  test rcx,rcx
    // 0xbccabf1  je 0xBCC9FF2
    // 0xbccabf7  mov rdx,[rbp+0x1B0]
    // 0xbccabfe  sub rdx,rcx
    // 0xbccac01  cmp rdx,0x1000
    // 0xbccac08  jb short 0xBCCAC26
    // 0xbccac0a  mov rax,[rcx-8]
    // 0xbccac0e  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbccac12  sub rcx,rax
    // 0xbccac15  cmp rcx,0x20
    // 0xbccac19  jae 0xBCCECCC
    // 0xbccac1f  or rdx,0x27
    // 0xbccac23  mov rcx,rax
    // loc_bccac26:
    // 0xbccac26  call 0xE935700          ; -> sub_e935700
    // 0xbccac2b  jmp 0xBCC9FF2
}

// 0xbccac30..0xbccac88
static void chunk2_set_uniform_other(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbccac30  mov rcx,[rbp+0x1A0]
    // 0xbccac37  mov rax,[rbp+0x1A8]
    // 0xbccac3e  mov rdx,rax
    // 0xbccac41  sub rdx,rcx
    // 0xbccac44  mov r8,rdx
    // 0xbccac47  sar r8,4
    // 0xbccac4b  mov [rbp+0x130],r8
    // 0xbccac52  cmp rdx,0xFFFFFFFFFFFFFFF0
    // 0xbccac56  je 0xBCCF08A
    // 0xbccac5c  mov [rbp+0x138],rcx
    // 0xbccac63  test rcx,rcx
    // 0xbccac66  setne cl
    // 0xbccac69  test rax,rax
    // 0xbccac6c  sete al
    // 0xbccac6f  or al,cl
    // 0xbccac71  je 0xBCCF08A
    // 0xbccac77  mov rcx,rdi
    // 0xbccac7a  lea rdx,[rbp+0x180]
    // 0xbccac81  lea r8,[rbp+0x130]
    // 0xbccac88  call 0xBCD7040          ; -> sub_bcd7040
    // 0xbccac8d  nop
    // 0xbccac8e  mov rcx,[rbp+0x1A0]
    // 0xbccac95  test rcx,rcx
    // 0xbccac98  je 0xBCC9FF2
    // 0xbccac9e  mov rdx,[rbp+0x1B0]
    // 0xbccaca5  sub rdx,rcx
    // 0xbccaca8  cmp rdx,0x1000
    // 0xbccacaf  jb short 0xBCCACCD
    // 0xbccacb1  mov rax,[rcx-8]
    // 0xbccacb5  add rcx,0xFFFFFFFFFFFFFFF8
    // 0xbccacb9  sub rcx,rax
    // 0xbccacbc  cmp rcx,0x20
    // 0xbccacc0  jae 0xBCCECCC
    // 0xbccacc6  add rdx,0x27
    // 0xbccacca  mov rcx,rax
    // loc_bccaccd:
    // 0xbccaccd  call 0xE935700          ; -> sub_e935700
    // 0xbccacd2  jmp 0xBCC9FF2
}

// 0xbccacd7..0xbccaf16
static void chunk2_fill_defaults(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    // 0xbccacd7  xor r15d,r15d
    // 0xbccacda  xor ecx,ecx
    // 0xbccacdc  xor ebx,ebx
    // 0xbccacde  jmp 0xBCCAEE5
    // loc_bccace3:
    // 0xbccace3  mov rcx,[0x1233E1A8]    ; [data_1233e1a8]
    // 0xbccacea  mov rax,[rcx]
    // 0xbccaced  mov rax,[rax+8]
    // 0xbccacf1  mov rdx,r13
    // 0xbccacf4  call qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040
    // 0xbccacfa  nop
    // 0xbccacfb  mov rbx,rax
    // 0xbccacfe  test rax,rax
    // 0xbccad01  je 0xBCCAFFA
    // loc_bccad07:
    // 0xbccad07  mov rcx,r14
    // 0xbccad0a  mov rax,rbx
    // 0xbccad0d  test r15b,3
    // 0xbccad11  je short 0xBCCAD42
    // 0xbccad13  mov ecx,r15d
    // 0xbccad16  and ecx,3
    // 0xbccad19  mov rax,rbx
    // 0xbccad1c  xor edx,edx
    // 0xbccad1e  xchg ax,ax
    // loc_bccad20:
    // 0xbccad20  movups [rax],xmm11
    // 0xbccad24  movups [rax+0x10],xmm11
    // 0xbccad29  mov dword ptr [rax+0x20],0x3F800000
    // 0xbccad30  add rax,0x24
    // 0xbccad34  inc rdx
    // 0xbccad37  cmp rcx,rdx
    // 0xbccad3a  jne short 0xBCCAD20
    // 0xbccad3c  mov rcx,r14
    // 0xbccad3f  sub rcx,rdx
    // loc_bccad42:
    // 0xbccad42  cmp r15d,4
    // 0xbccad46  jb short 0xBCCADA2
    // loc_bccad50:
    // 0xbccad50  movups [rax],xmm11
    // 0xbccad54  movups [rax+0x10],xmm11
    // 0xbccad59  mov dword ptr [rax+0x20],0x3F800000
    // 0xbccad60  movups [rax+0x24],xmm11
    // 0xbccad65  movups [rax+0x34],xmm11
    // 0xbccad6a  mov dword ptr [rax+0x44],0x3F800000
    // 0xbccad71  movups [rax+0x48],xmm11
    // 0xbccad76  movups [rax+0x58],xmm11
    // 0xbccad7b  mov dword ptr [rax+0x68],0x3F800000
    // 0xbccad82  movups [rax+0x6C],xmm11
    // 0xbccad87  movups [rax+0x7C],xmm11
    // 0xbccad8c  mov dword ptr [rax+0x8C],0x3F800000
    // 0xbccad96  add rax,0x90
    // 0xbccad9c  add rcx,0xFFFFFFFFFFFFFFFC
    // 0xbccada0  jne short 0xBCCAD50
    // loc_bccada2:
    // 0xbccada2  mov [rbp+0x1A0],rbx
    // 0xbccada9  lea rcx,[rbx+r13]
    // 0xbccadad  mov [rbp+0x1A8],rcx
    // 0xbccadb4  lea rax,[r14+r14*8]
    // 0xbccadb8  lea r15,[rbx+rax*4]
    // 0xbccadbc  mov [rbp+0x1B0],r15
    // 0xbccadc3  add r13,0xFFFFFFFFFFFFFFDC
    // 0xbccadc7  mov rax,r13
    // 0xbccadca  mov rdx,0xE38E38E38E38E38F
    // 0xbccadd4  mul rdx
    // 0xbccadd7  shr rdx,5
    // 0xbccaddb  mov r8d,edx
    // 0xbccadde  not r8d
    // 0xbccade1  mov rax,rbx
    // 0xbccade4  test r8b,7
    // 0xbccade8  je short 0xBCCAE18
    // 0xbccadea  inc edx
    // 0xbccadec  and edx,7
    // 0xbccadef  mov rax,rbx
    // loc_bccae00:
    // 0xbccae00  movups [rax],xmm14
    // 0xbccae04  movups [rax+0x10],xmm15
    // 0xbccae09  movss [rax+0x20],xmm13
    // 0xbccae0f  add rax,0x24
    // 0xbccae13  dec rdx
    // 0xbccae16  jne short 0xBCCAE00
    // loc_bccae18:
    // 0xbccae18  cmp r13d,0xFC
    // 0xbccae1f  jb 0xBCCAEE5
    // loc_bccae30:
    // 0xbccae30  movups [rax],xmm14
    // 0xbccae34  movups [rax+0x10],xmm15
    // 0xbccae39  movss [rax+0x20],xmm13
    // 0xbccae3f  movups [rax+0x24],xmm14
    // 0xbccae44  movups [rax+0x34],xmm15
    // 0xbccae49  movss [rax+0x44],xmm13
    // 0xbccae4f  movups [rax+0x48],xmm14
    // 0xbccae54  movups [rax+0x58],xmm15
    // 0xbccae59  movss [rax+0x68],xmm13
    // 0xbccae5f  movups [rax+0x6C],xmm14
    // 0xbccae64  movups [rax+0x7C],xmm15
    // 0xbccae69  movss [rax+0x8C],xmm13
    // 0xbccae72  movups [rax+0x90],xmm14
    // 0xbccae7a  movups [rax+0xA0],xmm15
    // 0xbccae82  movss [rax+0xB0],xmm13
    // 0xbccae8b  movups [rax+0xB4],xmm14
    // 0xbccae93  movups [rax+0xC4],xmm15
    // 0xbccae9b  movss [rax+0xD4],xmm13
    // 0xbccaea4  movups [rax+0xD8],xmm14
    // 0xbccaeac  movups [rax+0xE8],xmm15
    // 0xbccaeb4  movss [rax+0xF8],xmm13
    // 0xbccaebd  movups [rax+0xFC],xmm14
    // 0xbccaec5  movups [rax+0x10C],xmm15
    // 0xbccaecd  movss [rax+0x11C],xmm13
    // 0xbccaed6  add rax,0x120
    // 0xbccaedc  cmp rax,rcx
    // 0xbccaedf  jne 0xBCCAE30
    // loc_bccaee5:
    // 0xbccaee5  mov rax,rcx
    // 0xbccaee8  sub rax,rbx
    // 0xbccaeeb  mov rdx,rax
    // 0xbccaeee  sar rdx,2
    // 0xbccaef2  mov r8,0x8E38E38E38E38E39
    // 0xbccaefc  imul rdx,r8
    // 0xbccaf00  test sil,sil
    // 0xbccaf03  je short 0xBCCAF4A
    // 0xbccaf05  mov [rbp+0x130],rdx
    // 0xbccaf0c  cmp rax,0xFFFFFFFFFFFFFFDC
    // 0xbccaf10  je 0xBCCF08A
    // 0xbccaf16  mov [rbp+0x138],rbx
}

// Orchestrator for chunk 2
void MaterialInstance_initFromMaterial_chunk2(MaterialInstance* this_ptr, const Material* m, Chunk2State& state) {
    chunk2_init_array(this_ptr, m, state);
    chunk2_setup_loop_state(this_ptr, m, state);
    chunk2_alloc_and_init(this_ptr, m, state);
    chunk2_compute_size(this_ptr, m, state);
    chunk2_alloc_path_a(this_ptr, m, state);
    chunk2_update_pointers(this_ptr, m, state);
    chunk2_link_list(this_ptr, m, state);
    chunk2_insert_node(this_ptr, m, state);
    chunk2_rehash_loop(this_ptr, m, state);
    chunk2_alloc_fallback(this_ptr, m, state);
    chunk2_variant_path_a(this_ptr, m, state);
    chunk2_variant_path_b(this_ptr, m, state);
    chunk2_string_build(this_ptr, m, state);
    chunk2_uniform_vec4(this_ptr, m, state);
    chunk2_uniform_other(this_ptr, m, state);
    chunk2_mat3_path(this_ptr, m, state);
    chunk2_mat4_path(this_ptr, m, state);
    chunk2_set_uniform_vec4_array(this_ptr, m, state);
    chunk2_set_uniform_mat(this_ptr, m, state);
    chunk2_set_uniform_other(this_ptr, m, state);
    chunk2_fill_defaults(this_ptr, m, state);
}

} // namespace native