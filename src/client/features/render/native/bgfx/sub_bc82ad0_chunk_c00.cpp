// LIFT 0xbc82ad0 size 0x3a0f 1.26.62.01 sub_bc82ad0
// CHUNK 0xbc82ad0..0xbc842c9

// Chunk state struct documented in docs/functions/bc82ad0.md section 'Chunk state'.
struct ChunkState_bc82ad0_c00 {};

static inline void sub_bc82ad0_chunk_c00(ChunkState_bc82ad0_c00& s) {
    (void)s;
    // 0xbc82ad0..0xbc842c9
}

#if 0
0xbc82ad0  push rbp
0xbc82ad1  push r15
0xbc82ad3  push r14
0xbc82ad5  push r13
0xbc82ad7  push r12
0xbc82ad9  push rsi
0xbc82ada  push rdi
0xbc82adb  push rbx
0xbc82adc  sub rsp,0x938
0xbc82ae3  lea rbp,[rsp+0x80]
0xbc82aeb  movaps [rbp+0x8A0],xmm15
0xbc82af3  movaps [rbp+0x890],xmm14
0xbc82afb  movaps [rbp+0x880],xmm13
0xbc82b03  movaps [rbp+0x870],xmm12
0xbc82b0b  movaps [rbp+0x860],xmm11
0xbc82b13  movaps [rbp+0x850],xmm10
0xbc82b1b  movaps [rbp+0x840],xmm9
0xbc82b23  movaps [rbp+0x830],xmm8
0xbc82b2b  movaps [rbp+0x820],xmm7
0xbc82b32  movaps [rbp+0x810],xmm6
0xbc82b39  mov qword ptr [rbp+0x808],0xFFFFFFFFFFFFFFFE
0xbc82b44  mov r14,r9
0xbc82b47  mov [rbp+0x768],r8
0xbc82b4e  mov [rbp+0x760],rdx
0xbc82b55  mov [rbp+0x670],rcx
0xbc82b5c  mov eax,[0x12AE18D8]                          ; [data_12ae18d8]
0xbc82b62  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82b68  mov rdx,gs:[0x58]
0xbc82b71  mov rcx,[rdx+rcx*8]
0xbc82b75  cmp eax,[rcx+4]
0xbc82b7b  jg 0xBC84B55                                  ; -> sub_bc84b55
0xbc82b81  mov eax,[0x12AE1910]                          ; [data_12ae1910]
0xbc82b87  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82b8d  mov rdx,gs:[0x58]
0xbc82b96  mov rcx,[rdx+rcx*8]
0xbc82b9a  cmp eax,[rcx+4]
0xbc82ba0  jg 0xBC84BA9                                  ; -> sub_bc84ba9
0xbc82ba6  mov eax,[0x12AE1948]                          ; [data_12ae1948]
0xbc82bac  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82bb2  mov rdx,gs:[0x58]
0xbc82bbb  mov rcx,[rdx+rcx*8]
0xbc82bbf  cmp eax,[rcx+4]
0xbc82bc5  jg 0xBC84BFD                                  ; -> sub_bc84bfd
0xbc82bcb  mov eax,[0x12AE1980]                          ; [data_12ae1980]
0xbc82bd1  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82bd7  mov rdx,gs:[0x58]
0xbc82be0  mov rcx,[rdx+rcx*8]
0xbc82be4  cmp eax,[rcx+4]
0xbc82bea  jg 0xBC84C51                                  ; -> sub_bc84c51
0xbc82bf0  mov eax,[0x12AE1998]                          ; [data_12ae1998]
0xbc82bf6  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82bfc  mov rdx,gs:[0x58]
0xbc82c05  mov rcx,[rdx+rcx*8]
0xbc82c09  cmp eax,[rcx+4]
0xbc82c0f  jg 0xBC84CA5                                  ; -> sub_bc84ca5
0xbc82c15  mov r9,[rbp+0x950]
0xbc82c1c  mov rcx,[rbp+0x948]
0xbc82c23  xorps xmm6,xmm6
0xbc82c26  movaps [rbp+0x4A0],xmm6
0xbc82c2d  lea rax,[0xF54E7B3]                           ; [data_f54e7b3] "ScreenSpaceReflections"
0xbc82c34  mov [rbp+0x6B0],rax
0xbc82c3b  mov qword ptr [rbp+0x6B8],0x16
0xbc82c46  lea rax,[rbp+0x4A0]
0xbc82c4d  mov [rsp+0x28],rax
0xbc82c52  lea rax,[rbp+0x6B0]
0xbc82c59  mov [rsp+0x20],rax
0xbc82c5e  lea r8,[0x12AE1988]                           ; [data_12ae1988]
0xbc82c65  lea rdx,[rbp+0x770]
0xbc82c6c  call 0x567C8B0                                ; -> sub_567c8b0
0xbc82c71  nop
0xbc82c72  mov rax,[rbp+0x770]
0xbc82c79  movaps [rbp+0x690],xmm6
0xbc82c80  mov rcx,[rax+8]
0xbc82c84  test rcx,rcx
0xbc82c87  je short 0xBC82CD0                            ; -> loc_bc82cd0
0xbc82c89  lock inc dword ptr [rcx+8]
0xbc82c8d  mov rsi,[rbp+0x698]
0xbc82c94  movups xmm0,[rax]
0xbc82c97  movaps [rbp+0x690],xmm0
0xbc82c9e  test rsi,rsi
0xbc82ca1  je short 0xBC82CE5                            ; -> loc_bc82ce5
0xbc82ca3  lock dec dword ptr [rsi+8]
0xbc82ca7  jne short 0xBC82CE5                           ; -> loc_bc82ce5
0xbc82ca9  mov rax,[rsi]
0xbc82cac  mov rax,[rax]
0xbc82caf  mov rcx,rsi
0xbc82cb2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc82cb8  lock dec dword ptr [rsi+0xC]
0xbc82cbc  jne short 0xBC82CE5                           ; -> loc_bc82ce5
0xbc82cbe  mov rax,[rsi]
0xbc82cc1  mov rax,[rax+8]
0xbc82cc5  mov rcx,rsi
0xbc82cc8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc82cce  jmp short 0xBC82CE5                           ; -> loc_bc82ce5
0xbc82cd0  mov rax,[rax]
0xbc82cd3  mov [rbp+0x690],rax
0xbc82cda  mov qword ptr [rbp+0x698],0
0xbc82ce5  mov rsi,[rbp+0x778]
0xbc82cec  test rsi,rsi
0xbc82cef  je short 0xBC82D1C                            ; -> loc_bc82d1c
0xbc82cf1  lock dec dword ptr [rsi+8]
0xbc82cf5  jne short 0xBC82D1C                           ; -> loc_bc82d1c
0xbc82cf7  mov rax,[rsi]
0xbc82cfa  mov rax,[rax]
0xbc82cfd  mov rcx,rsi
0xbc82d00  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc82d06  lock dec dword ptr [rsi+0xC]
0xbc82d0a  jne short 0xBC82D1C                           ; -> loc_bc82d1c
0xbc82d0c  mov rax,[rsi]
0xbc82d0f  mov rax,[rax+8]
0xbc82d13  mov rcx,rsi
0xbc82d16  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc82d1c  mov eax,[0x12AE19A8]                          ; [data_12ae19a8]
0xbc82d22  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82d28  mov rdx,gs:[0x58]
0xbc82d31  mov rcx,[rdx+rcx*8]
0xbc82d35  cmp eax,[rcx+4]
0xbc82d3b  jg 0xBC84D0D                                  ; -> sub_bc84d0d
0xbc82d41  mov eax,[0x12AE19B8]                          ; [data_12ae19b8]
0xbc82d47  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82d4d  mov rdx,gs:[0x58]
0xbc82d56  mov rcx,[rdx+rcx*8]
0xbc82d5a  cmp eax,[rcx+4]
0xbc82d60  jg 0xBC84D7F                                  ; -> sub_bc84d7f
0xbc82d66  mov eax,[0x12AE19C8]                          ; [data_12ae19c8]
0xbc82d6c  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82d72  mov rdx,gs:[0x58]
0xbc82d7b  mov rcx,[rdx+rcx*8]
0xbc82d7f  cmp eax,[rcx+4]
0xbc82d85  jg 0xBC84DF1                                  ; -> sub_bc84df1
0xbc82d8b  mov eax,[0x12AE19D8]                          ; [data_12ae19d8]
0xbc82d91  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82d97  mov rdx,gs:[0x58]
0xbc82da0  mov rcx,[rdx+rcx*8]
0xbc82da4  cmp eax,[rcx+4]
0xbc82daa  jg 0xBC84E63                                  ; -> sub_bc84e63
0xbc82db0  mov eax,[0x12AE19E8]                          ; [data_12ae19e8]
0xbc82db6  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82dbc  mov rdx,gs:[0x58]
0xbc82dc5  mov rcx,[rdx+rcx*8]
0xbc82dc9  cmp eax,[rcx+4]
0xbc82dcf  jg 0xBC84ED5                                  ; -> sub_bc84ed5
0xbc82dd5  mov eax,[0x12AE19F8]                          ; [data_12ae19f8]
0xbc82ddb  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82de1  mov rdx,gs:[0x58]
0xbc82dea  mov rcx,[rdx+rcx*8]
0xbc82dee  cmp eax,[rcx+4]
0xbc82df4  jg 0xBC84F47                                  ; -> sub_bc84f47
0xbc82dfa  mov eax,[0x12AE1A08]                          ; [data_12ae1a08]
0xbc82e00  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82e06  mov rdx,gs:[0x58]
0xbc82e0f  mov rcx,[rdx+rcx*8]
0xbc82e13  cmp eax,[rcx+4]
0xbc82e19  jg 0xBC84FB9                                  ; -> sub_bc84fb9
0xbc82e1f  mov eax,[0x12AE1A18]                          ; [data_12ae1a18]
0xbc82e25  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc82e2b  mov rdx,gs:[0x58]
0xbc82e34  mov rcx,[rdx+rcx*8]
0xbc82e38  cmp eax,[rcx+4]
0xbc82e3e  jg 0xBC8502B                                  ; -> sub_bc8502b
0xbc82e44  mov rbx,[rbp+0x920]
0xbc82e4b  xorps xmm0,xmm0
0xbc82e4e  cvtsi2ss xmm0,dword ptr [r14+8]
0xbc82e54  movss [rbp+0x450],xmm0
0xbc82e5c  movsd xmm0,[r14+0x10]
0xbc82e62  movaps [rbp+0x440],xmm0
0xbc82e69  xorps xmm0,xmm0
0xbc82e6c  cvtsi2ss xmm0,dword ptr [r14+0xC]
0xbc82e72  movss [rbp+0x460],xmm0
0xbc82e7a  movsd xmm0,[r14+0x18]
0xbc82e80  movaps [rbp+0x470],xmm0
0xbc82e87  movss xmm0,[r14+0x20]
0xbc82e8d  movss [rbp+0x664],xmm0
0xbc82e95  movss xmm0,[r14+0x40]
0xbc82e9b  movss [rbp+0x668],xmm0
0xbc82ea3  movsd xmm0,[r14+0x24]
0xbc82ea9  movaps [rbp+0x300],xmm0
0xbc82eb0  lea rdx,[rbx+0x18]
0xbc82eb4  movss xmm0,[rbx+0x18]
0xbc82eb9  movss [rbp+0x430],xmm0
0xbc82ec1  movss xmm11,[rbx+0x2C]
0xbc82ec7  mov esi,[0x12ADF818]                          ; [data_12adf818]
0xbc82ecd  lea rcx,[rbp+0x4A0]
0xbc82ed4  call 0xAB49C0                                 ; -> sub_ab49c0
0xbc82ed9  nop
0xbc82eda  mov rcx,[rbp+0x928]
0xbc82ee1  add esi,0xFFFFFFF9
0xbc82ee4  xorps xmm6,xmm6
0xbc82ee7  cmp esi,2
0xbc82eea  jb short 0xBC82EF2                            ; -> loc_bc82ef2
0xbc82eec  xorps xmm14,xmm14
0xbc82ef0  jmp short 0xBC82EFB                           ; -> loc_bc82efb
0xbc82ef2  movss xmm14,[0xEF1D470]                       ; [data_ef1d470]
0xbc82efb  movss xmm13,[rbp+0x4AC]
0xbc82f04  mulss xmm13,xmm6
0xbc82f09  movss xmm12,[rbp+0x4A8]
0xbc82f12  mulss xmm12,xmm6
0xbc82f17  movss xmm0,[rbp+0x4BC]
0xbc82f1f  mulss xmm0,xmm6
0xbc82f23  movss [rbp+0x66C],xmm0
0xbc82f2b  mulss xmm6,[rbp+0x4B8]
0xbc82f33  movsd xmm7,[rbp+0x4C8]
0xbc82f3b  movss xmm9,[rbp+0x4CC]
0xbc82f44  mulss xmm9,xmm14
0xbc82f49  movss xmm15,[rbp+0x4DC]
0xbc82f52  movss xmm10,[rbp+0x4D8]
0xbc82f5b  movd xmm0,[rbx+0xC]
0xbc82f60  pxor xmm2,xmm2
0xbc82f64  punpcklwd xmm0,xmm2
0xbc82f68  cvtdq2ps xmm1,xmm0
0xbc82f6b  movups xmm0,[r14+4]
0xbc82f70  shufps xmm0,xmm0,0
0xbc82f74  movaps [rbp+0x310],xmm1
0xbc82f7b  mulps xmm0,xmm1
0xbc82f7e  cvttps2dq xmm0,xmm0
0xbc82f82  pshuflw xmm1,xmm0,0xE8
0xbc82f87  mov qword ptr [rbp+0x628],0
0xbc82f92  mov dword ptr [rbp+0x630],0
0xbc82f9c  mov qword ptr [rbp+0x682],0
0xbc82fa7  mov qword ptr [rbp+0x688],0
0xbc82fb2  mov rax,0x3F80000000000000
0xbc82fbc  mov [rbp+0x5AC],rax
0xbc82fc3  mov qword ptr [rbp+0x5A4],0
0xbc82fce  mov dword ptr [rbp+0x5C4],0
0xbc82fd8  mov byte ptr [rbp+0x5C8],0xF
0xbc82fdf  mov dword ptr [rbp+0x5CC],1
0xbc82fe9  mov word ptr [rbp+0x5D0],0x100
0xbc82ff2  mov byte ptr [rbp+0x5D2],8
0xbc82ff9  mov dword ptr [rbp+0x5D4],0
0xbc83003  mov byte ptr [rbp+0x5D8],0
0xbc8300a  movdqu [rbp+0x5DC],xmm2
0xbc83012  movdqu [rbp+0x5E8],xmm2
0xbc8301a  mov byte ptr [rbp+0x5F8],8
0xbc83021  mov qword ptr [rbp+0x5FC],0
0xbc8302c  mov dword ptr [rbp+0x604],0
0xbc83036  mov byte ptr [rbp+0x608],8
0xbc8303d  movzx eax,word ptr [rbp+0x67F]
0xbc83044  mov [rbp+0x609],ax
0xbc8304b  movzx eax,byte ptr [rbp+0x681]
0xbc83052  mov [rbp+0x60B],al
0xbc83058  mov rax,[rbp+0x682]
0xbc8305f  mov [rbp+0x60C],rax
0xbc83066  mov eax,[rbp+0x68A]
0xbc8306c  mov [rbp+0x614],eax
0xbc83072  movzx eax,byte ptr [rbp+0x68E]
0xbc83079  mov [rbp+0x618],al
0xbc8307f  movzx eax,byte ptr [rbp+0x68F]
0xbc83086  mov [rbp+0x619],al
0xbc8308c  mov byte ptr [rbp+0x61A],0xFF
0xbc83093  movdqu [rbp+0x5B4],xmm2
0xbc8309b  movups xmm0,[rbx+0x58]
0xbc8309f  movaps [rbp+0x4A0],xmm0
0xbc830a6  movups xmm0,[rbx+0x68]
0xbc830aa  movaps [rbp+0x4B0],xmm0
0xbc830b1  movups xmm0,[rbx+0x78]
0xbc830b5  movaps [rbp+0x4C0],xmm0
0xbc830bc  movups xmm0,[rbx+0x88]
0xbc830c3  movaps [rbp+0x4D0],xmm0
0xbc830ca  movups xmm0,[rbx+0x18]
0xbc830ce  movaps [rbp+0x4E0],xmm0
0xbc830d5  movups xmm0,[rbx+0x28]
0xbc830d9  movss xmm8,[0xEEC8060]                        ; [data_eec8060]
0xbc830e2  movss [rbp+0x73C],xmm8
0xbc830eb  divss xmm8,[rbx+0x2C]
0xbc830f1  movaps [rbp+0x4F0],xmm0
0xbc830f8  movups xmm0,[rbx+0x38]
0xbc830fc  movaps [rbp+0x500],xmm0
0xbc83103  movups xmm0,[rbx+0x48]
0xbc83107  movaps [rbp+0x510],xmm0
0xbc8310e  mov dword ptr [rbp+0x520],0
0xbc83118  movd [rbp+0x524],xmm1
0xbc83120  mov dword ptr [rbp+0x528],0
0xbc8312a  movdqa [rbp+0x650],xmm1
0xbc83132  movd [rbp+0x52C],xmm1
0xbc8313a  mov dword ptr [rbp+0x530],1
0xbc83144  movups xmm0,[rcx+0x58]
0xbc83148  movups [rbp+0x534],xmm0
0xbc8314f  movups xmm0,[rcx+0x68]
0xbc83153  movups [rbp+0x544],xmm0
0xbc8315a  movups xmm0,[rcx+0x78]
0xbc8315e  movups [rbp+0x554],xmm0
0xbc83165  movups xmm0,[rcx+0x88]
0xbc8316c  movups [rbp+0x564],xmm0
0xbc83173  movups xmm0,[rcx+0x18]
0xbc83177  movups [rbp+0x574],xmm0
0xbc8317e  movups xmm0,[rcx+0x28]
0xbc83182  movups [rbp+0x584],xmm0
0xbc83189  movups xmm0,[rcx+0x38]
0xbc8318d  movups [rbp+0x594],xmm0
0xbc83194  movups xmm0,[rcx+0x48]
0xbc83198  movups [rbp+0x5A4],xmm0
0xbc8319f  mov eax,[0x12AE1A28]                          ; [data_12ae1a28]
0xbc831a5  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc831ab  mov rdx,gs:[0x58]
0xbc831b4  mov rcx,[rdx+rcx*8]
0xbc831b8  cmp eax,[rcx+4]
0xbc831be  jg 0xBC8509D                                  ; -> sub_bc8509d
0xbc831c4  mov eax,[0x12AE1A38]                          ; [data_12ae1a38]
0xbc831ca  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc831d0  mov rdx,gs:[0x58]
0xbc831d9  mov rcx,[rdx+rcx*8]
0xbc831dd  cmp eax,[rcx+4]
0xbc831e3  jg 0xBC8510F                                  ; -> sub_bc8510f
0xbc831e9  mov eax,[0x12AE1A48]                          ; [data_12ae1a48]
0xbc831ef  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc831f5  mov rdx,gs:[0x58]
0xbc831fe  mov rcx,[rdx+rcx*8]
0xbc83202  cmp eax,[rcx+4]
0xbc83208  jg 0xBC85181                                  ; -> sub_bc85181
0xbc8320e  mov eax,[0x12AE1A58]                          ; [data_12ae1a58]
0xbc83214  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc8321a  mov rdx,gs:[0x58]
0xbc83223  mov rcx,[rdx+rcx*8]
0xbc83227  cmp eax,[rcx+4]
0xbc8322d  jg 0xBC851F3                                  ; -> sub_bc851f3
0xbc83233  mov eax,[0x12AE1A68]                          ; [data_12ae1a68]
0xbc83239  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc8323f  mov rdx,gs:[0x58]
0xbc83248  mov rcx,[rdx+rcx*8]
0xbc8324c  cmp eax,[rcx+4]
0xbc83252  jg 0xBC85265                                  ; -> sub_bc85265
0xbc83258  mov eax,[0x12AE1A78]                          ; [data_12ae1a78]
0xbc8325e  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc83264  mov rdx,gs:[0x58]
0xbc8326d  mov rcx,[rdx+rcx*8]
0xbc83271  cmp eax,[rcx+4]
0xbc83277  jg 0xBC852D7                                  ; -> sub_bc852d7
0xbc8327d  mov rax,[rbp+0x968]
0xbc83284  mov rcx,[rbp+0x960]
0xbc8328b  mov rdx,[rbp+0x958]
0xbc83292  mov r8,[0x12AE1A40]                           ; [data_12ae1a40]
0xbc83299  mov [rbp+0x3D8],r8
0xbc832a0  movzx r8d,word ptr [0x128C1A58]               ; [data_128c1a58]
0xbc832a8  mov [rbp+0x3E0],r8w
0xbc832b0  mov dword ptr [rbp+0x3E4],0
0xbc832ba  mov byte ptr [rbp+0x3E8],0
0xbc832c1  mov rax,[rax]
0xbc832c4  mov [rbp+0x3F0],rax
0xbc832cb  mov byte ptr [rbp+0x3FA],0
0xbc832d2  mov rax,[0x12AE1A50]                          ; [data_12ae1a50]
0xbc832d9  mov [rbp+0x328],rax
0xbc832e0  mov [rbp+0x330],r8w
0xbc832e8  mov dword ptr [rbp+0x334],0
0xbc832f2  mov byte ptr [rbp+0x338],0
0xbc832f9  mov rax,[rdx+8]
0xbc832fd  mov [rbp+0x340],rax
0xbc83304  mov byte ptr [rbp+0x34A],0
0xbc8330b  mov rax,[0x12AE1A60]                          ; [data_12ae1a60]
0xbc83312  mov [rbp+0x350],rax
0xbc83319  mov [rbp+0x358],r8w
0xbc83321  mov dword ptr [rbp+0x35C],0
0xbc8332b  mov byte ptr [rbp+0x360],0
0xbc83332  mov rax,[rcx+8]
0xbc83336  mov [rbp+0x368],rax
0xbc8333d  mov byte ptr [rbp+0x372],0
0xbc83344  mov byte ptr [rbp+0x3B0],0
0xbc8334b  mov rax,[rbp+0x980]
0xbc83352  movzx eax,byte ptr [rax+0x10]
0xbc83356  mov [rbp+0x801],al
0xbc8335c  cmp al,1
0xbc8335e  jne short 0xBC833B9                           ; -> loc_bc833b9
0xbc83360  mov rsi,[0x12AE1A70]                          ; [data_12ae1a70]
0xbc83367  mov di,[0x128C1A5A]                           ; [data_128c1a5a]
0xbc8336e  mov rcx,[rbp+0x760]
0xbc83375  mov rdx,rcx
0xbc83378  mov r8,[rbp+0x980]
0xbc8337f  call 0x56BA620                                ; -> sub_56ba620
0xbc83384  nop
0xbc83385  mov [rbp+0x388],rsi
0xbc8338c  mov [rbp+0x390],di
0xbc83393  mov dword ptr [rbp+0x394],0
0xbc8339d  mov byte ptr [rbp+0x398],0
0xbc833a4  mov [rbp+0x3A0],rax
0xbc833ab  mov byte ptr [rbp+0x3AA],0
0xbc833b2  mov byte ptr [rbp+0x3B0],1
0xbc833b9  mov dword ptr [rbp+0x490],0
0xbc833c3  mov byte ptr [rbp+0x494],0
0xbc833ca  mov word ptr [rbp+0x48C],0
0xbc833d3  mov rax,0x300000001
0xbc833dd  mov [rbp+0x498],rax
0xbc833e4  movaps xmm0,[rbp+0x650]
0xbc833eb  movss [rbp+0x484],xmm0
0xbc833f3  mov dword ptr [rbp+0x488],0xA
0xbc833fd  mov eax,[0x12AE1A88]                          ; [data_12ae1a88]
0xbc83403  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc83409  mov rdx,gs:[0x58]
0xbc83412  mov rcx,[rdx+rcx*8]
0xbc83416  cmp eax,[rcx+4]
0xbc8341c  jg 0xBC85349                                  ; -> sub_bc85349
0xbc83422  lea r8,[rbp+0x484]
0xbc83429  mov rcx,[rbp+0x760]
0xbc83430  mov rdx,rcx
0xbc83433  call 0x5698290                                ; -> sub_5698290
0xbc83438  nop
0xbc83439  mov rcx,[0x12AE1A80]                          ; [data_12ae1a80]
0xbc83440  mov [rbp+0x418],rcx
0xbc83447  mov [rbp+0x420],rax
0xbc8344e  mov byte ptr [rbp+0x42A],0
0xbc83455  lea r8,[rbp+0x484]
0xbc8345c  mov rcx,[rbp+0x760]
0xbc83463  mov rdx,rcx
0xbc83466  call 0x5698290                                ; -> sub_5698290
0xbc8346b  nop
0xbc8346c  mov r8,[rbp+0x988]
0xbc83473  mov rcx,[0x12AE1A80]                          ; [data_12ae1a80]
0xbc8347a  mov [rbp+0x400],rcx
0xbc83481  mov [rbp+0x408],rax
0xbc83488  mov byte ptr [rbp+0x412],0
0xbc8348f  mov rcx,[rbp+0x760]
0xbc83496  mov rdx,rcx
0xbc83499  call 0x56BA620                                ; -> sub_56ba620
0xbc8349e  nop
0xbc8349f  mov rcx,[0x12AE1A80]                          ; [data_12ae1a80]
0xbc834a6  mov rdx,[rbp+0x670]
0xbc834ad  mov [rdx],rcx
0xbc834b0  mov [rdx+8],rax
0xbc834b4  mov byte ptr [rdx+0x12],0
0xbc834b8  mov rax,[rbp+0x690]
0xbc834bf  mov rax,[rax+0x18]
0xbc834c3  mov rax,[rax]
0xbc834c6  mov [rbp+0x6B0],rax
0xbc834cd  lea r12,[rbp+0x6B8]
0xbc834d4  mov rcx,[rbp+0x768]
0xbc834db  mov r8,[rcx]
0xbc834de  mov rdx,[rax+0x170]
0xbc834e5  mov rcx,r12
0xbc834e8  call 0xE86B370                                ; -> sub_e86b370
0xbc834ed  nop
0xbc834ee  divss xmm11,[rbp+0x430]
0xbc834f7  mulss xmm11,xmm8
0xbc834fc  mov rax,[rbp+0x768]
0xbc83503  mov [rbp+0x730],rax
0xbc8350a  movss [rbp+0x770],xmm11
0xbc83513  movss [rbp+0x774],xmm8
0xbc8351c  mov qword ptr [rbp+0x778],0
0xbc83527  mov qword ptr [rbp+0x7B0],1
0xbc83532  lea rax,[rbp+0x770]
0xbc83539  mov [rbp+0x7B8],rax
0xbc83540  mov rax,[rbp+0x6E8]
0xbc83547  movzx edx,word ptr [rbp+0x6F2]
0xbc8354e  mov ecx,edx
0xbc83550  shl ecx,4
0xbc83553  mov r8,rax
0xbc83556  test edx,edx
0xbc83558  je short 0xBC83588                            ; -> loc_bc83588
0xbc8355a  mov r9,[0x12AE19E0]                           ; [data_12ae19e0]
0xbc83561  xor r8d,r8d
0xbc83564  nop [rax+rax]
0xbc83570  mov r10,[rax+r8]
0xbc83574  cmp [r10+0x28],r9
0xbc83578  je short 0xBC83585                            ; -> loc_bc83585
0xbc8357a  add r8,0x10
0xbc8357e  cmp rcx,r8
0xbc83581  jne short 0xBC83570                           ; -> loc_bc83570
0xbc83583  jmp short 0xBC835D1                           ; -> loc_bc835d1
0xbc83585  add r8,rax
0xbc83588  lea r9,[rax+rcx]
0xbc8358c  cmp r8,r9
0xbc8358f  jae short 0xBC835D1                           ; -> loc_bc835d1
0xbc83591  sub r8d,eax
0xbc83594  shr r8d,4
0xbc83598  mov [rbp+0x7E0],r8w
0xbc835a0  mov byte ptr [rbp+0x7E2],1
0xbc835a7  lea rdx,[rbp+0x7E0]
0xbc835ae  lea r8,[rbp+0x7B0]
0xbc835b5  mov rcx,r12
0xbc835b8  call 0x5679DB0                                ; -> sub_5679db0
0xbc835bd  nop
0xbc835be  mov rax,[rbp+0x6E8]
0xbc835c5  movzx edx,word ptr [rbp+0x6F2]
0xbc835cc  mov ecx,edx
0xbc835ce  shl ecx,4
0xbc835d1  movdqa xmm0,[rbp+0x650]
0xbc835d9  pxor xmm1,xmm1
0xbc835dd  punpcklwd xmm0,xmm1
0xbc835e1  cvtdq2ps xmm8,xmm0
0xbc835e5  movaps xmm0,[0xEFD3400]                       ; [data_efd3400]
0xbc835ec  divps xmm0,xmm8
0xbc835f0  movaps xmm11,xmm8
0xbc835f4  movlhps xmm11,xmm0
0xbc835f8  movaps [rbp+0x770],xmm11
0xbc83600  mov qword ptr [rbp+0x7B0],1
0xbc8360b  lea r8,[rbp+0x770]
0xbc83612  mov [rbp+0x7B8],r8
0xbc83619  mov r8,rax
0xbc8361c  test dx,dx
0xbc8361f  je short 0xBC83648                            ; -> loc_bc83648
0xbc83621  mov r9,[0x12AE19F0]                           ; [data_12ae19f0]
0xbc83628  xor r8d,r8d
0xbc8362b  nop [rax+rax]
0xbc83630  mov r10,[rax+r8]
0xbc83634  cmp [r10+0x28],r9
0xbc83638  je short 0xBC83645                            ; -> loc_bc83645
0xbc8363a  add r8,0x10
0xbc8363e  cmp rcx,r8
0xbc83641  jne short 0xBC83630                           ; -> loc_bc83630
0xbc83643  jmp short 0xBC83691                           ; -> loc_bc83691
0xbc83645  add r8,rax
0xbc83648  lea r9,[rax+rcx]
0xbc8364c  cmp r8,r9
0xbc8364f  jae short 0xBC83691                           ; -> loc_bc83691
0xbc83651  sub r8d,eax
0xbc83654  shr r8d,4
0xbc83658  mov [rbp+0x7E0],r8w
0xbc83660  mov byte ptr [rbp+0x7E2],1
0xbc83667  lea rdx,[rbp+0x7E0]
0xbc8366e  lea r8,[rbp+0x7B0]
0xbc83675  mov rcx,r12
0xbc83678  call 0x5679DB0                                ; -> sub_5679db0
0xbc8367d  nop
0xbc8367e  mov rax,[rbp+0x6E8]
0xbc83685  movzx edx,word ptr [rbp+0x6F2]
0xbc8368c  mov ecx,edx
0xbc8368e  shl ecx,4
0xbc83691  addss xmm13,[rbp+0x66C]
0xbc8369a  addss xmm12,xmm6
0xbc8369f  mulss xmm14,xmm7
0xbc836a4  movaps xmm0,xmm7
0xbc836a7  movss xmm0,xmm9
0xbc836ac  shufps xmm15,xmm15,0
0xbc836b1  addps xmm15,xmm0
0xbc836b5  shufps xmm7,xmm7,0
0xbc836b9  movss xmm7,xmm14
0xbc836be  shufps xmm10,xmm10,0
0xbc836c3  addps xmm10,xmm7
0xbc836c7  shufps xmm13,xmm13,0
0xbc836cc  addps xmm13,xmm15
0xbc836d0  shufps xmm12,xmm12,0
0xbc836d5  addps xmm12,xmm10
0xbc836d9  divps xmm12,xmm13
0xbc836dd  movaps xmm0,xmm8
0xbc836e1  shufps xmm0,xmm8,0x55
0xbc836e6  divss xmm8,xmm0
0xbc836eb  movlps [rbp+0x770],xmm12
0xbc836f3  movss [rbp+0x778],xmm8
0xbc836fc  mov dword ptr [rbp+0x77C],0x3F800000
0xbc83706  mov qword ptr [rbp+0x7B0],1
0xbc83711  lea r8,[rbp+0x770]
0xbc83718  mov [rbp+0x7B8],r8
0xbc8371f  mov r8,rax
0xbc83722  test dx,dx
0xbc83725  je short 0xBC83758                            ; -> loc_bc83758
0xbc83727  mov r9,[0x12AE1A00]                           ; [data_12ae1a00]
0xbc8372e  xor r8d,r8d
0xbc83731  nop [rax+rax]
0xbc83740  mov r10,[rax+r8]
0xbc83744  cmp [r10+0x28],r9
0xbc83748  je short 0xBC83755                            ; -> loc_bc83755
0xbc8374a  add r8,0x10
0xbc8374e  cmp rcx,r8
0xbc83751  jne short 0xBC83740                           ; -> loc_bc83740
0xbc83753  jmp short 0xBC837A1                           ; -> loc_bc837a1
0xbc83755  add r8,rax
0xbc83758  lea r9,[rax+rcx]
0xbc8375c  cmp r8,r9
0xbc8375f  jae short 0xBC837A1                           ; -> loc_bc837a1
0xbc83761  sub r8d,eax
0xbc83764  shr r8d,4
0xbc83768  mov [rbp+0x7E0],r8w
0xbc83770  mov byte ptr [rbp+0x7E2],1
0xbc83777  lea rdx,[rbp+0x7E0]
0xbc8377e  lea r8,[rbp+0x7B0]
0xbc83785  mov rcx,r12
0xbc83788  call 0x5679DB0                                ; -> sub_5679db0
0xbc8378d  nop
0xbc8378e  mov rax,[rbp+0x6E8]
0xbc83795  movzx edx,word ptr [rbp+0x6F2]
0xbc8379c  mov ecx,edx
0xbc8379e  shl ecx,4
0xbc837a1  mov r8,[rbp+0x930]
0xbc837a8  movsd xmm0,[r8]
0xbc837ad  movups [rbp+0x770],xmm0
0xbc837b4  mov qword ptr [rbp+0x7B0],1
0xbc837bf  lea r8,[rbp+0x770]
0xbc837c6  mov [rbp+0x7B8],r8
0xbc837cd  mov r8,rax
0xbc837d0  test dx,dx
0xbc837d3  je short 0xBC837F8                            ; -> loc_bc837f8
0xbc837d5  mov r9,[0x12AE1A10]                           ; [data_12ae1a10]
0xbc837dc  xor r8d,r8d
0xbc837df  nop
0xbc837e0  mov r10,[rax+r8]
0xbc837e4  cmp [r10+0x28],r9
0xbc837e8  je short 0xBC837F5                            ; -> loc_bc837f5
0xbc837ea  add r8,0x10
0xbc837ee  cmp rcx,r8
0xbc837f1  jne short 0xBC837E0                           ; -> loc_bc837e0
0xbc837f3  jmp short 0xBC83841                           ; -> loc_bc83841
0xbc837f5  add r8,rax
0xbc837f8  lea r9,[rax+rcx]
0xbc837fc  cmp r8,r9
0xbc837ff  jae short 0xBC83841                           ; -> loc_bc83841
0xbc83801  sub r8d,eax
0xbc83804  shr r8d,4
0xbc83808  mov [rbp+0x7E0],r8w
0xbc83810  mov byte ptr [rbp+0x7E2],1
0xbc83817  lea rdx,[rbp+0x7E0]
0xbc8381e  lea r8,[rbp+0x7B0]
0xbc83825  mov rcx,r12
0xbc83828  call 0x5679DB0                                ; -> sub_5679db0
0xbc8382d  nop
0xbc8382e  mov rax,[rbp+0x6E8]
0xbc83835  movzx edx,word ptr [rbp+0x6F2]
0xbc8383c  mov ecx,edx
0xbc8383e  shl ecx,4
0xbc83841  movss xmm0,[rbp+0x450]
0xbc83849  movss [rbp+0x770],xmm0
0xbc83851  movaps xmm0,[rbp+0x440]
0xbc83858  movlps [rbp+0x774],xmm0
0xbc8385f  movss xmm0,[rbp+0x460]
0xbc83867  movss [rbp+0x77C],xmm0
0xbc8386f  mov qword ptr [rbp+0x7B0],1
0xbc8387a  lea r8,[rbp+0x770]
0xbc83881  mov [rbp+0x7B8],r8
0xbc83888  mov r8,rax
0xbc8388b  test dx,dx
0xbc8388e  je short 0xBC838B8                            ; -> loc_bc838b8
0xbc83890  mov r9,[0x12AE19A0]                           ; [data_12ae19a0]
0xbc83897  xor r8d,r8d
0xbc8389a  nop [rax+rax]
0xbc838a0  mov r10,[rax+r8]
0xbc838a4  cmp [r10+0x28],r9
0xbc838a8  je short 0xBC838B5                            ; -> loc_bc838b5
0xbc838aa  add r8,0x10
0xbc838ae  cmp rcx,r8
0xbc838b1  jne short 0xBC838A0                           ; -> loc_bc838a0
0xbc838b3  jmp short 0xBC83901                           ; -> loc_bc83901
0xbc838b5  add r8,rax
0xbc838b8  lea r9,[rax+rcx]
0xbc838bc  cmp r8,r9
0xbc838bf  jae short 0xBC83901                           ; -> loc_bc83901
0xbc838c1  sub r8d,eax
0xbc838c4  shr r8d,4
0xbc838c8  mov [rbp+0x7E0],r8w
0xbc838d0  mov byte ptr [rbp+0x7E2],1
0xbc838d7  lea rdx,[rbp+0x7E0]
0xbc838de  lea r8,[rbp+0x7B0]
0xbc838e5  mov rcx,r12
0xbc838e8  call 0x5679DB0                                ; -> sub_5679db0
0xbc838ed  nop
0xbc838ee  mov rax,[rbp+0x6E8]
0xbc838f5  movzx edx,word ptr [rbp+0x6F2]
0xbc838fc  mov ecx,edx
0xbc838fe  shl ecx,4
0xbc83901  movaps xmm0,[rbp+0x470]
0xbc83908  movlps [rbp+0x770],xmm0
0xbc8390f  movss xmm0,[rbp+0x664]
0xbc83917  movss [rbp+0x778],xmm0
0xbc8391f  movss xmm0,[rbp+0x668]
0xbc83927  movss [rbp+0x77C],xmm0
0xbc8392f  mov qword ptr [rbp+0x7B0],1
0xbc8393a  lea r8,[rbp+0x770]
0xbc83941  mov [rbp+0x7B8],r8
0xbc83948  mov r8,rax
0xbc8394b  test dx,dx
0xbc8394e  je short 0xBC8397C                            ; -> loc_bc8397c
0xbc83950  mov r9,[0x12AE19B0]                           ; [data_12ae19b0]
0xbc83957  xor r8d,r8d
0xbc8395a  nop [rax+rax]
0xbc83960  mov r10,[rax+r8]
0xbc83964  cmp [r10+0x28],r9
0xbc83968  je short 0xBC83979                            ; -> loc_bc83979
0xbc8396a  add r8,0x10
0xbc8396e  cmp rcx,r8
0xbc83971  jne short 0xBC83960                           ; -> loc_bc83960
0xbc83973  mov dx,1
0xbc83977  jmp short 0xBC839C5                           ; -> loc_bc839c5
0xbc83979  add r8,rax
0xbc8397c  lea r9,[rax+rcx]
0xbc83980  cmp r8,r9
0xbc83983  jae short 0xBC839C5                           ; -> loc_bc839c5
0xbc83985  sub r8d,eax
0xbc83988  shr r8d,4
0xbc8398c  mov [rbp+0x7E0],r8w
0xbc83994  mov byte ptr [rbp+0x7E2],1
0xbc8399b  lea rdx,[rbp+0x7E0]
0xbc839a2  lea r8,[rbp+0x7B0]
0xbc839a9  mov rcx,r12
0xbc839ac  call 0x5679DB0                                ; -> sub_5679db0
0xbc839b1  nop
0xbc839b2  mov rax,[rbp+0x6E8]
0xbc839b9  movzx edx,word ptr [rbp+0x6F2]
0xbc839c0  mov ecx,edx
0xbc839c2  shl ecx,4
0xbc839c5  movsd xmm0,[rbp+0x300]
0xbc839cd  movups [rbp+0x770],xmm0
0xbc839d4  mov qword ptr [rbp+0x7B0],1
0xbc839df  lea r8,[rbp+0x770]
0xbc839e6  mov [rbp+0x7B8],r8
0xbc839ed  mov r8,rax
0xbc839f0  test dx,dx
0xbc839f3  je short 0xBC83A25                            ; -> loc_bc83a25
0xbc839f5  mov rdx,[0x12AE19C0]                          ; [data_12ae19c0]
0xbc839fc  mov r9,rcx
0xbc839ff  mov r8,rax
0xbc83a02  nop [rax+rax]
0xbc83a10  mov r10,[r8]
0xbc83a13  cmp [r10+0x28],rdx
0xbc83a17  je short 0xBC83A25                            ; -> loc_bc83a25
0xbc83a19  add r8,0x10
0xbc83a1d  add r9,0xFFFFFFFFFFFFFFF0
0xbc83a21  jne short 0xBC83A10                           ; -> loc_bc83a10
0xbc83a23  jmp short 0xBC83A5A                           ; -> loc_bc83a5a
0xbc83a25  add rcx,rax
0xbc83a28  cmp r8,rcx
0xbc83a2b  jae short 0xBC83A5A                           ; -> loc_bc83a5a
0xbc83a2d  sub r8d,eax
0xbc83a30  shr r8d,4
0xbc83a34  mov [rbp+0x7E0],r8w
0xbc83a3c  mov byte ptr [rbp+0x7E2],1
0xbc83a43  lea rdx,[rbp+0x7E0]
0xbc83a4a  lea r8,[rbp+0x7B0]
0xbc83a51  mov rcx,r12
0xbc83a54  call 0x5679DB0                                ; -> sub_5679db0
0xbc83a59  nop
0xbc83a5a  mov eax,[0x12AE1A98]                          ; [data_12ae1a98]
0xbc83a60  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc83a66  mov rdx,gs:[0x58]
0xbc83a6f  mov rcx,[rdx+rcx*8]
0xbc83a73  cmp eax,[rcx+4]
0xbc83a79  jg 0xBC853B8                                  ; -> sub_bc853b8
0xbc83a7f  mov eax,[0x12AE1AA8]                          ; [data_12ae1aa8]
0xbc83a85  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc83a8b  mov rdx,gs:[0x58]
0xbc83a94  mov rcx,[rdx+rcx*8]
0xbc83a98  cmp eax,[rcx+4]
0xbc83a9e  jg 0xBC8542A                                  ; -> sub_bc8542a
0xbc83aa4  mov eax,[0x12AE1AB8]                          ; [data_12ae1ab8]
0xbc83aaa  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc83ab0  mov rdx,gs:[0x58]
0xbc83ab9  mov rcx,[rdx+rcx*8]
0xbc83abd  cmp eax,[rcx+4]
0xbc83ac3  jg 0xBC8549C                                  ; -> sub_bc8549c
0xbc83ac9  mov eax,[0x12AE1AC8]                          ; [data_12ae1ac8]
0xbc83acf  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc83ad5  mov rdx,gs:[0x58]
0xbc83ade  mov rcx,[rdx+rcx*8]
0xbc83ae2  cmp eax,[rcx+4]
0xbc83ae8  jg 0xBC8550E                                  ; -> sub_bc8550e
0xbc83aee  mov rdi,[rbp+0x970]
0xbc83af5  mov byte ptr [rbp+0x798],0
0xbc83afc  cmp byte ptr [rdi+0x18],1
0xbc83b00  jne 0xBC83D2A                                 ; -> loc_bc83d2a
0xbc83b06  mov rax,[0x12AE1A90]                          ; [data_12ae1a90]
0xbc83b0d  movzx ecx,word ptr [0x128C1A58]               ; [data_128c1a58]
0xbc83b14  mov rdx,[rdi]
0xbc83b17  mov [rbp+0x770],rax
0xbc83b1e  mov [rbp+0x778],cx
0xbc83b25  mov dword ptr [rbp+0x77C],0
0xbc83b2f  mov byte ptr [rbp+0x780],0
0xbc83b36  mov [rbp+0x788],rdx
0xbc83b3d  mov byte ptr [rbp+0x792],0
0xbc83b44  mov byte ptr [rbp+0x798],1
0xbc83b4b  movq xmm0,[rdi+8]
0xbc83b50  pxor xmm1,xmm1
0xbc83b54  punpcklwd xmm0,xmm1
0xbc83b58  cvtdq2ps xmm0,xmm0
0xbc83b5b  movaps [rbp+0x7B0],xmm0
0xbc83b62  mov qword ptr [rbp+0x7E0],1
0xbc83b6d  lea rsi,[rbp+0x7B0]
0xbc83b74  mov [rbp+0x7E8],rsi
0xbc83b7b  mov rax,[rbp+0x6E8]
0xbc83b82  movzx edx,word ptr [rbp+0x6F2]
0xbc83b89  mov ecx,edx
0xbc83b8b  shl ecx,4
0xbc83b8e  mov r8,rax
0xbc83b91  test edx,edx
0xbc83b93  je short 0xBC83BB8                            ; -> loc_bc83bb8
0xbc83b95  mov r9,[0x12AE1AA0]                           ; [data_12ae1aa0]
0xbc83b9c  xor r8d,r8d
0xbc83b9f  nop
0xbc83ba0  mov r10,[rax+r8]
0xbc83ba4  cmp [r10+0x28],r9
0xbc83ba8  je short 0xBC83BB5                            ; -> loc_bc83bb5
0xbc83baa  add r8,0x10
0xbc83bae  cmp rcx,r8
0xbc83bb1  jne short 0xBC83BA0                           ; -> loc_bc83ba0
0xbc83bb3  jmp short 0xBC83C01                           ; -> loc_bc83c01
0xbc83bb5  add r8,rax
0xbc83bb8  lea r9,[rax+rcx]
0xbc83bbc  cmp r8,r9
0xbc83bbf  jae short 0xBC83C01                           ; -> loc_bc83c01
0xbc83bc1  sub r8d,eax
0xbc83bc4  shr r8d,4
0xbc83bc8  mov [rbp+0x740],r8w
0xbc83bd0  mov byte ptr [rbp+0x742],1
0xbc83bd7  lea rdx,[rbp+0x740]
0xbc83bde  lea r8,[rbp+0x7E0]
0xbc83be5  mov rcx,r12
0xbc83be8  call 0x5679DB0                                ; -> sub_5679db0
0xbc83bed  nop
0xbc83bee  mov rax,[rbp+0x6E8]
0xbc83bf5  movzx edx,word ptr [rbp+0x6F2]
0xbc83bfc  mov ecx,edx
0xbc83bfe  shl ecx,4
0xbc83c01  movzx r8d,word ptr [rdi+0x10]
0xbc83c06  xorps xmm0,xmm0
0xbc83c09  cvtsi2ss xmm0,r8d
0xbc83c0e  shufps xmm0,xmm0,0
0xbc83c12  movaps [rbp+0x7B0],xmm0
0xbc83c19  mov qword ptr [rbp+0x7E0],1
0xbc83c24  mov [rbp+0x7E8],rsi
0xbc83c2b  mov r8,rax
0xbc83c2e  test dx,dx
0xbc83c31  je short 0xBC83C5C                            ; -> loc_bc83c5c
0xbc83c33  mov r9,[0x12AE1AB0]                           ; [data_12ae1ab0]
0xbc83c3a  xor r8d,r8d
0xbc83c3d  nop [rax]
0xbc83c40  mov r10,[rax+r8]
0xbc83c44  cmp [r10+0x28],r9
0xbc83c48  je short 0xBC83C59                            ; -> loc_bc83c59
0xbc83c4a  add r8,0x10
0xbc83c4e  cmp rcx,r8
0xbc83c51  jne short 0xBC83C40                           ; -> loc_bc83c40
0xbc83c53  mov dx,1
0xbc83c57  jmp short 0xBC83CA5                           ; -> loc_bc83ca5
0xbc83c59  add r8,rax
0xbc83c5c  lea r9,[rax+rcx]
0xbc83c60  cmp r8,r9
0xbc83c63  jae short 0xBC83CA5                           ; -> loc_bc83ca5
0xbc83c65  sub r8d,eax
0xbc83c68  shr r8d,4
0xbc83c6c  mov [rbp+0x740],r8w
0xbc83c74  mov byte ptr [rbp+0x742],1
0xbc83c7b  lea rdx,[rbp+0x740]
0xbc83c82  lea r8,[rbp+0x7E0]
0xbc83c89  mov rcx,r12
0xbc83c8c  call 0x5679DB0                                ; -> sub_5679db0
0xbc83c91  nop
0xbc83c92  mov rax,[rbp+0x6E8]
0xbc83c99  movzx edx,word ptr [rbp+0x6F2]
0xbc83ca0  mov ecx,edx
0xbc83ca2  shl ecx,4
0xbc83ca5  movss xmm0,[r14+0x50]
0xbc83cab  shufps xmm0,xmm0,0
0xbc83caf  movaps [rbp+0x7B0],xmm0
0xbc83cb6  mov qword ptr [rbp+0x7E0],1
0xbc83cc1  mov [rbp+0x7E8],rsi
0xbc83cc8  mov r8,rax
0xbc83ccb  test dx,dx
0xbc83cce  je short 0xBC83CF5                            ; -> loc_bc83cf5
0xbc83cd0  mov rdx,[0x12AE1AC0]                          ; [data_12ae1ac0]
0xbc83cd7  mov r9,rcx
0xbc83cda  mov r8,rax
0xbc83cdd  nop [rax]
0xbc83ce0  mov r10,[r8]
0xbc83ce3  cmp [r10+0x28],rdx
0xbc83ce7  je short 0xBC83CF5                            ; -> loc_bc83cf5
0xbc83ce9  add r8,0x10
0xbc83ced  add r9,0xFFFFFFFFFFFFFFF0
0xbc83cf1  jne short 0xBC83CE0                           ; -> loc_bc83ce0
0xbc83cf3  jmp short 0xBC83D2A                           ; -> loc_bc83d2a
0xbc83cf5  add rcx,rax
0xbc83cf8  cmp r8,rcx
0xbc83cfb  jae short 0xBC83D2A                           ; -> loc_bc83d2a
0xbc83cfd  sub r8d,eax
0xbc83d00  shr r8d,4
0xbc83d04  mov [rbp+0x740],r8w
0xbc83d0c  mov byte ptr [rbp+0x742],1
0xbc83d13  lea rdx,[rbp+0x740]
0xbc83d1a  lea r8,[rbp+0x7E0]
0xbc83d21  mov rcx,r12
0xbc83d24  call 0x5679DB0                                ; -> sub_5679db0
0xbc83d29  nop
0xbc83d2a  mov r8,[rbp+0x940]
0xbc83d31  mov qword ptr [rbp+0x7B8],0
0xbc83d3c  mov qword ptr [rbp+0x7C0],0xC
0xbc83d47  mov qword ptr [rbp+0x7C8],0xF
0xbc83d52  mov rax,0x4D7961525F525353
0xbc83d5c  mov [rbp+0x7B0],rax
0xbc83d63  mov dword ptr [rbp+0x7B8],0x68637261
0xbc83d6d  lea rcx,[0x12AE18E0]                          ; [data_12ae18e0]
0xbc83d74  lea rax,[0x12AE18A8]                          ; [data_12ae18a8]
0xbc83d7b  cmp byte ptr [r14+0x44],0
0xbc83d80  cmovne rax,rcx
0xbc83d84  lea rcx,[rbp+0x520]
0xbc83d8b  mov dword ptr [rbp+0x7E0],0
0xbc83d95  movaps xmm0,[rbp+0x650]
0xbc83d9c  movss [rbp+0x7E4],xmm0
0xbc83da4  movaps xmm0,[rbp+0x4A0]
0xbc83dab  movaps xmm1,[rbp+0x4B0]
0xbc83db2  movaps xmm2,[rbp+0x4C0]
0xbc83db9  movaps xmm3,[rbp+0x4D0]
0xbc83dc0  movaps [rbp-0x20],xmm0
0xbc83dc4  movaps [rbp-0x10],xmm1
0xbc83dc8  movaps [rbp],xmm2
0xbc83dcc  movaps [rbp+0x10],xmm3
0xbc83dd0  movaps xmm0,[rbp+0x4E0]
0xbc83dd7  movaps [rbp+0x20],xmm0
0xbc83ddb  movaps xmm0,[rbp+0x4F0]
0xbc83de2  movaps [rbp+0x30],xmm0
0xbc83de6  movaps xmm0,[rbp+0x500]
0xbc83ded  movaps [rbp+0x40],xmm0
0xbc83df1  movaps xmm0,[rbp+0x510]
0xbc83df8  movaps [rbp+0x50],xmm0
0xbc83dfc  mov edx,[rcx+0x10]
0xbc83dff  mov [rbp+0x70],edx
0xbc83e02  movaps xmm0,[rcx]
0xbc83e05  movaps [rbp+0x60],xmm0
0xbc83e09  movups xmm0,[rbp+0x534]
0xbc83e10  movups [rbp+0x74],xmm0
0xbc83e14  movups xmm0,[rbp+0x544]
0xbc83e1b  movups [rbp+0x84],xmm0
0xbc83e22  movups xmm0,[rbp+0x554]
0xbc83e29  movups [rbp+0x94],xmm0
0xbc83e30  movups xmm0,[rbp+0x564]
0xbc83e37  movups [rbp+0xA4],xmm0
0xbc83e3e  movups xmm0,[rbp+0x574]
0xbc83e45  movups [rbp+0xB4],xmm0
0xbc83e4c  movups xmm0,[rbp+0x584]
0xbc83e53  movups [rbp+0xC4],xmm0
0xbc83e5a  movups xmm0,[rbp+0x594]
0xbc83e61  movups [rbp+0xD4],xmm0
0xbc83e68  movups xmm0,[rbp+0x5A4]
0xbc83e6f  movups [rbp+0xE4],xmm0
0xbc83e76  movups xmm0,[rcx+0x94]
0xbc83e7d  movups [rbp+0xF4],xmm0
0xbc83e84  mov edx,[rcx+0xB4]
0xbc83e8a  mov [rbp+0x114],edx
0xbc83e90  movups xmm0,[rcx+0xA4]
0xbc83e97  movups [rbp+0x104],xmm0
0xbc83e9e  movzx edx,byte ptr [rbp+0x5D8]
0xbc83ea5  mov [rbp+0x118],dl
0xbc83eab  movups xmm0,[rbp+0x5DC]
0xbc83eb2  movups [rbp+0x11C],xmm0
0xbc83eb9  movups xmm0,[rcx+0xCC]
0xbc83ec0  movdqu xmm1,[rcx+0xDC]
0xbc83ec8  movdqu xmm2,[rcx+0xEB]
0xbc83ed0  movdqu [rbp+0x14B],xmm2
0xbc83ed8  movdqu [rbp+0x13C],xmm1
0xbc83ee0  movups [rbp+0x12C],xmm0
0xbc83ee7  mov byte ptr [rbp+0x15C],1
0xbc83eee  lea rcx,[rbp+0x770]
0xbc83ef5  mov [rsp+0x58],rcx
0xbc83efa  lea rcx,[rbp+0x350]
0xbc83f01  mov [rsp+0x50],rcx
0xbc83f06  lea rcx,[rbp+0x328]
0xbc83f0d  mov [rsp+0x48],rcx
0xbc83f12  lea rcx,[rbp+0x3D8]
0xbc83f19  mov [rsp+0x40],rcx
0xbc83f1e  lea rdi,[rbp+0x418]
0xbc83f25  mov [rsp+0x38],rdi
0xbc83f2a  lea rcx,[rbp+0x6B0]
0xbc83f31  mov [rsp+0x30],rcx
0xbc83f36  lea r12,[rbp+0x7B0]
0xbc83f3d  mov [rsp+0x28],r12
0xbc83f42  mov [rsp+0x20],rax
0xbc83f47  lea rdx,[rbp-0x20]
0xbc83f4b  lea r13,[rbp+0x7E0]
0xbc83f52  mov rcx,[rbp+0x760]
0xbc83f59  mov r9,r13
0xbc83f5c  call 0xBC88560                                ; -> sub_bc88560
0xbc83f61  nop
0xbc83f62  mov rax,[rbp+0x7C8]
0xbc83f69  cmp rax,0x10
0xbc83f6d  jb short 0xBC83FA7                            ; -> loc_bc83fa7
0xbc83f6f  mov rcx,[rbp+0x7B0]
0xbc83f76  lea rdx,[rax+1]
0xbc83f7a  cmp rdx,0x1000
0xbc83f81  jb short 0xBC83FA2                            ; -> loc_bc83fa2
0xbc83f83  mov r8,[rcx-8]
0xbc83f87  add rcx,0xFFFFFFFFFFFFFFF8
0xbc83f8b  sub rcx,r8
0xbc83f8e  cmp rcx,0x20
0xbc83f92  jae 0xBC8558B                                 ; -> sub_bc8558b
0xbc83f98  add rax,0x28
0xbc83f9c  mov rdx,rax
0xbc83f9f  mov rcx,r8
0xbc83fa2  call 0xE935700                                ; -> sub_e935700
0xbc83fa7  cmp byte ptr [r14+0x3C],1
0xbc83fac  jne 0xBC843CC                                 ; -> loc_bc843cc
0xbc83fb2  mov eax,[0x12AE1B50]                          ; [data_12ae1b50]
0xbc83fb8  mov ecx,[0x128767C8]                          ; [data_128767c8]
0xbc83fbe  mov rdx,gs:[0x58]
0xbc83fc7  mov rcx,[rdx+rcx*8]
0xbc83fcb  cmp eax,[rcx+4]
0xbc83fd1  jg 0xBC855A4                                  ; -> sub_bc855a4
0xbc83fd7  mov rax,[0x12AE1A20]                          ; [data_12ae1a20]
0xbc83fde  mov [rbp+0x770],rax
0xbc83fe5  movzx eax,word ptr [0x128C1A58]               ; [data_128c1a58]
0xbc83fec  mov [rbp+0x778],ax
0xbc83ff3  mov dword ptr [rbp+0x77C],0
0xbc83ffd  mov byte ptr [rbp+0x780],0
0xbc84004  mov rax,[rbp+0x420]
0xbc8400b  mov [rbp+0x788],rax
0xbc84012  mov byte ptr [rbp+0x792],0
0xbc84019  mov r15,[rbp+0x690]
0xbc84020  mov rax,[r15+0x18]
0xbc84024  mov rax,[rax]
0xbc84027  mov [rbp+0x6B0],rax
0xbc8402e  lea rsi,[rbp+0x6B8]
0xbc84035  mov rcx,[rbp+0x768]
0xbc8403c  mov r8,[rcx]
0xbc8403f  mov rdx,[rax+0x170]
0xbc84046  mov rcx,rsi
0xbc84049  call 0xE86B370                                ; -> sub_e86b370
0xbc8404e  nop
0xbc8404f  mov rax,[rbp+0x768]
0xbc84056  mov [rbp+0x730],rax
0xbc8405d  movaps [rbp+0x7B0],xmm11
0xbc84065  mov qword ptr [rbp+0x7E0],1
0xbc84070  mov [rbp+0x7E8],r12
0xbc84077  mov rax,[rbp+0x6E8]
0xbc8407e  movzx r8d,word ptr [rbp+0x6F2]
0xbc84086  mov edx,r8d
0xbc84089  shl edx,4
0xbc8408c  mov rcx,rax
0xbc8408f  test r8d,r8d
0xbc84092  je short 0xBC840C5                            ; -> loc_bc840c5
0xbc84094  mov r8,[0x12AE19F0]                           ; [data_12ae19f0]
0xbc8409b  mov r9,rdx
0xbc8409e  mov rcx,rax
0xbc840a1  nop [rax+rax]
0xbc840b0  mov r10,[rcx]
0xbc840b3  cmp [r10+0x28],r8
0xbc840b7  je short 0xBC840C5                            ; -> loc_bc840c5
0xbc840b9  add rcx,0x10
0xbc840bd  add r9,0xFFFFFFFFFFFFFFF0
0xbc840c1  jne short 0xBC840B0                           ; -> loc_bc840b0
0xbc840c3  jmp short 0xBC840F7                           ; -> loc_bc840f7
0xbc840c5  add rdx,rax
0xbc840c8  cmp rcx,rdx
0xbc840cb  jae short 0xBC840F7                           ; -> loc_bc840f7
0xbc840cd  sub ecx,eax
0xbc840cf  shr ecx,4
0xbc840d2  mov [rbp+0x740],cx
0xbc840d9  mov byte ptr [rbp+0x742],1
0xbc840e0  lea rdx,[rbp+0x740]
0xbc840e7  lea r8,[rbp+0x7E0]
0xbc840ee  mov rcx,rsi
0xbc840f1  call 0x5679DB0                                ; -> sub_5679db0
0xbc840f6  nop
0xbc840f7  xorps xmm0,xmm0
0xbc840fa  movaps [rbp+0x7C0],xmm0
0xbc84101  movaps [rbp+0x7B0],xmm0
0xbc84108  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0xbc8410f  mov rax,[rcx]
0xbc84112  mov rax,[rax+8]
0xbc84116  mov edx,0x20
0xbc8411b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc84121  nop
0xbc84122  mov rsi,rax
0xbc84125  test rax,rax
0xbc84128  je 0xBC84B45                                  ; -> sub_bc84b45
0xbc8412e  mov [rbp+0x7B0],rsi
0xbc84135  mov qword ptr [rbp+0x7C0],0x13
0xbc84140  mov qword ptr [rbp+0x7C8],0x1F
0xbc8414b  movups xmm0,[0xF5A15B7]                       ; [data_f5a15b7] "SSR_ExtendedGapFill"
0xbc84152  movups [rsi],xmm0
0xbc84155  mov dword ptr [rsi+0xF],0x6C6C6946
0xbc8415c  mov byte ptr [rsi+0x13],0
0xbc84160  lea rax,[rbp+0x770]
0xbc84167  mov [rsp+0x38],rax
0xbc8416c  lea rax,[rbp+0x400]
0xbc84173  mov [rsp+0x30],rax
0xbc84178  lea rax,[rbp+0x6B0]
0xbc8417f  mov [rsp+0x28],rax
0xbc84184  mov [rsp+0x20],r12
0xbc84189  lea r9,[0x12AE1B10]                           ; [data_12ae1b10]
0xbc84190  lea rdx,[rbp+0x4A0]
0xbc84197  mov rcx,[rbp+0x760]
0xbc8419e  mov r8,[rbp+0x940]
0xbc841a5  call 0xBC8A240                                ; -> sub_bc8a240
0xbc841aa  nop
0xbc841ab  mov rax,[rbp+0x7C8]
0xbc841b2  cmp rax,0x10
0xbc841b6  jb short 0xBC841F0                            ; -> loc_bc841f0
0xbc841b8  mov rcx,[rbp+0x7B0]
0xbc841bf  lea rdx,[rax+1]
0xbc841c3  cmp rdx,0x1000
0xbc841ca  jb short 0xBC841EB                            ; -> loc_bc841eb
0xbc841cc  mov r8,[rcx-8]
0xbc841d0  add rcx,0xFFFFFFFFFFFFFFF8
0xbc841d4  sub rcx,r8
0xbc841d7  cmp rcx,0x20
0xbc841db  jae 0xBC8558B                                 ; -> sub_bc8558b
0xbc841e1  add rax,0x28
0xbc841e5  mov rdx,rax
0xbc841e8  mov rcx,r8
0xbc841eb  call 0xE935700                                ; -> sub_e935700
0xbc841f0  mov rax,[0x12AE1A20]                          ; [data_12ae1a20]
0xbc841f7  mov [rbp+0x770],rax
0xbc841fe  movzx eax,word ptr [0x128C1A58]               ; [data_128c1a58]
0xbc84205  mov [rbp+0x778],ax
0xbc8420c  mov dword ptr [rbp+0x77C],0
0xbc84216  mov byte ptr [rbp+0x780],0
0xbc8421d  mov rax,[rbp+0x408]
0xbc84224  mov [rbp+0x788],rax
0xbc8422b  mov byte ptr [rbp+0x792],0
0xbc84232  mov rax,[r15+0x18]
0xbc84236  mov rax,[rax]
0xbc84239  mov [rbp+0x6B0],rax
0xbc84240  lea rsi,[rbp+0x6B8]
0xbc84247  mov rcx,[rbp+0x768]
0xbc8424e  mov r8,[rcx]
0xbc84251  mov rdx,[rax+0x170]
0xbc84258  mov rcx,rsi
0xbc8425b  call 0xE86B370                                ; -> sub_e86b370
0xbc84260  nop
0xbc84261  mov rax,[rbp+0x768]
0xbc84268  mov [rbp+0x730],rax
0xbc8426f  movups [rbp+0x7B0],xmm11
0xbc84277  mov qword ptr [rbp+0x7E0],1
0xbc84282  mov [rbp+0x7E8],r12
0xbc84289  mov rax,[rbp+0x6E8]
0xbc84290  movzx r8d,word ptr [rbp+0x6F2]
0xbc84298  mov edx,r8d
0xbc8429b  shl edx,4
0xbc8429e  mov rcx,rax
0xbc842a1  test r8d,r8d
0xbc842a4  je short 0xBC842D5                            ; -> loc_bc842d5
0xbc842a6  mov r8,[0x12AE19F0]                           ; [data_12ae19f0]
0xbc842ad  mov r9,rdx
0xbc842b0  mov rcx,rax
0xbc842b3  nop [rax+rax]
0xbc842c0  mov r10,[rcx]
0xbc842c3  cmp [r10+0x28],r8
0xbc842c7  je short 0xBC842D5                            ; -> loc_bc842d5
0xbc842c9  add rcx,0x10
#endif
