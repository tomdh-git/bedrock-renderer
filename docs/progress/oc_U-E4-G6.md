# U-E4-G6 — Unit 6 of builder 0x670b6e0 (ends 0x6713c64)

## NEXT block at TOP — resume at 0x6711806

Unit range covered: 0x67108da .. 0x6711800 (800 instructions, phases 1-20)
Resume address after this unit: 0x6711806 (fallthrough after instr #800 `6711800 jae 0x6713b37`, 6 bytes)

Method: linear `rdis dis` listing, 40-instruction steps per phase.
Tags: [V] = saw in disasm (cite RVA), [I] = inferred, [?] = unknown.
Direct jumps written as `jmp <addr>` (not `jmp qword ptr`).

---
### Phase 1 — instructions #1-#40 (0x67108da .. 0x67109ab)

  67108da  nop
  67108db  mov qword ptr [rbp+0x3E0],0xA007009
  67108e6  mov eax,[r15+0x770]
  67108ed  sub eax,[r15+0x768]
  67108f4  shr eax,3
  67108f7  imul eax,0xFFFFF0F1
  67108fd  dec eax
  67108ff  mov [rbp+0x40A],ax
  6710906  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671090d  mov rax,[rcx]
  6710910  mov rax,[rax+0x10]
  6710914  mov dl,0x4A
  6710916  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671091c  nop
  671091d  mov [rbp+0x848],al
  6710923  mov rdx,[r15+0x680]
  671092a  cmp rdx,[r15+0x688]
  6710931  je 0x67109FA                                  ; -> loc_67109fa
  6710937  movss xmm0,[rbp+0x584]
  671093f  movss [rdx],xmm0
  6710943  movss xmm0,[rbp+0x588]
  671094b  movss [rdx+4],xmm0
  6710950  movss xmm0,[rbp+0x58C]
  6710958  movss [rdx+8],xmm0
  671095d  add qword ptr [r15+0x680],0xC
  6710965  jmp 0x6710A0E                                 ; -> loc_6710a0e
  671096a  lea rcx,[r15+0x678]
  6710971  lea r8,[rbp+0x584]
  6710978  call 0x1770A70                                ; -> sub_1770a70
  671097d  nop
  671097e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710985  mov rax,[rcx]
  6710988  mov rax,[rax+0x10]
  671098c  movzx edx,byte ptr [rbp+0x848]
  6710993  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710999  nop
  671099a  mov eax,[r15+0x680]
  67109a1  sub eax,[r15+0x678]
  67109a8  shr eax,2
  67109ab  imul eax,0xFFFFAAAB


### Phase 2 — instructions #41-#80 (0x67109b1 .. 0x6710a6e)

  67109b1  dec eax
  67109b3  mov [rbp+0x41E],ax
  67109ba  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67109c1  mov rax,[rcx]
  67109c4  mov rax,[rax+0x10]
  67109c8  mov dl,0x4A
  67109ca  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67109d0  nop
  67109d1  mov [rbp+0x848],al
  67109d7  mov rdx,[r15+0x518]
  67109de  cmp rdx,[r15+0x520]
  67109e5  je 0x6710A8A                                  ; -> loc_6710a8a
  67109eb  inc rdx
  67109ee  mov [r15+0x518],rdx
  67109f5  jmp 0x6710A9A                                 ; -> loc_6710a9a
loc_67109fa:  ; from 6710931
  67109fa  lea rcx,[r15+0x678]
  6710a01  lea r8,[rbp+0x584]
  6710a08  call 0x1770A70                                ; -> sub_1770a70
  6710a0d  nop
loc_6710a0e:  ; from 6710965
  6710a0e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710a15  mov rax,[rcx]
  6710a18  mov rax,[rax+0x10]
  6710a1c  movzx edx,byte ptr [rbp+0x848]
  6710a23  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710a29  nop
  6710a2a  mov eax,[r15+0x680]
  6710a31  sub eax,[r15+0x678]
  6710a38  shr eax,2
  6710a3b  imul eax,0xFFFFAAAB
  6710a41  dec eax
  6710a43  mov [rbp+0x41E],ax
  6710a4a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710a51  mov rax,[rcx]
  6710a54  mov rax,[rax+0x10]
  6710a58  mov dl,0x4A
  6710a5a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710a60  nop
  6710a61  mov [rbp+0x848],al
  6710a67  mov rdx,[r15+0x2D8]
  6710a6e  cmp rdx,[r15+0x2E0]


### Phase 3 — instructions #81-#120 (0x6710a75 .. 0x6710b36)

  6710a75  je 0x6710B27                                  ; -> loc_6710b27
  6710a7b  inc rdx
  6710a7e  mov [r15+0x2D8],rdx
  6710a85  jmp 0x6710B37                                 ; -> loc_6710b37
loc_6710a8a:  ; from 67109e5
  6710a8a  mov rcx,r15
  6710a8d  add rcx,0x510
  6710a94  call 0x6760E60                                ; -> sub_6760e60
  6710a99  nop
loc_6710a9a:  ; from 67109f5
  6710a9a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710aa1  mov rax,[rcx]
  6710aa4  mov rax,[rax+0x10]
  6710aa8  movzx edx,byte ptr [rbp+0x848]
  6710aaf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710ab5  nop
  6710ab6  mov rax,0x400A807009
  6710ac0  mov [rbp+0x3E0],rax
  6710ac7  mov eax,[r15+0x510]
  6710ace  not eax
  6710ad0  add eax,[r15+0x518]
  6710ad7  mov [rbp+0x43C],ax
  6710ade  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710ae5  mov rax,[rcx]
  6710ae8  mov rax,[rax+0x10]
  6710aec  mov dl,0x4A
  6710aee  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710af4  nop
  6710af5  mov [rbp+0x848],al
  6710afb  mov rdx,[r15+8]
  6710aff  cmp rdx,[r15+0x10]
  6710b03  je 0x6710BBD                                  ; -> loc_6710bbd
  6710b09  mov r8d,0xC8
  6710b0f  mov rcx,rdx
  6710b12  mov rdx,r12
  6710b15  call 0xEEC6EC0                                ; -> sub_eec6ec0
  6710b1a  add qword ptr [r15+8],0xC8
  6710b22  jmp 0x6710BC9                                 ; -> loc_6710bc9
loc_6710b27:  ; from 6710a75
  6710b27  mov rcx,r15
  6710b2a  add rcx,0x2D0
  6710b31  call 0x6760E60                                ; -> sub_6760e60
  6710b36  nop
loc_6710b37:  ; from 6710a85


### Phase 4 — instructions #121-#160 (0x6710b37 .. 0x6710be8)

  6710b37  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710b3e  mov rax,[rcx]
  6710b41  mov rax,[rax+0x10]
  6710b45  movzx edx,byte ptr [rbp+0x848]
  6710b4c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710b52  nop
  6710b53  mov rax,0x400000000A807009
  6710b5d  mov [rbp+0x3E0],rax
  6710b64  mov eax,[r15+0x2D0]
  6710b6b  not eax
  6710b6d  add eax,[r15+0x2D8]
  6710b74  mov [rbp+0x46C],ax
  6710b7b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710b82  mov rax,[rcx]
  6710b85  mov rax,[rax+0x10]
  6710b89  mov dl,0x4A
  6710b8b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710b91  nop
  6710b92  mov [rbp+0x848],al
  6710b98  mov rdx,[r15+8]
  6710b9c  cmp rdx,[r15+0x10]
  6710ba0  je short 0x6710BEF                            ; -> loc_6710bef
  6710ba2  mov r8d,0xC8
  6710ba8  mov rcx,rdx
  6710bab  mov rdx,r12
  6710bae  call 0xEEC6EC0                                ; -> sub_eec6ec0
  6710bb3  add qword ptr [r15+8],0xC8
  6710bbb  jmp short 0x6710BFB                           ; -> loc_6710bfb
loc_6710bbd:  ; from 6710b03
  6710bbd  mov rcx,r15
  6710bc0  mov r8,r12
  6710bc3  call 0x5ABA6D0                                ; -> sub_5aba6d0
  6710bc8  nop
loc_6710bc9:  ; from 6710b22
  6710bc9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710bd0  mov rax,[rcx]
  6710bd3  mov rax,[rax+0x10]
  6710bd7  movzx edx,byte ptr [rbp+0x848]
  6710bde  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710be4  nop
  6710be5  mov rcx,r13
  6710be8  call 0x67E1660                                ; -> sub_67e1660


### Phase 5 — instructions #161-#200 (0x6710bed .. 0x6710c9e)

  6710bed  jmp short 0x6710C20                           ; -> loc_6710c20
loc_6710bef:  ; from 6710ba0
  6710bef  mov rcx,r15
  6710bf2  mov r8,r12
  6710bf5  call 0x5ABA6D0                                ; -> sub_5aba6d0
  6710bfa  nop
loc_6710bfb:  ; from 6710bbb
  6710bfb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710c02  mov rax,[rcx]
  6710c05  mov rax,[rax+0x10]
  6710c09  movzx edx,byte ptr [rbp+0x848]
  6710c10  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710c16  nop
  6710c17  mov rcx,r13
  6710c1a  call 0x67E1660                                ; -> sub_67e1660
  6710c1f  nop
loc_6710c20:  ; from 6710bed
  6710c20  lea rcx,[rbp+0x120]
  6710c27  call 0x67E1660                                ; -> sub_67e1660
  6710c2c  cmp byte ptr [rbp+0x80],3
  6710c33  je 0x67139AE                                  ; -> sub_67139ae
  6710c39  jmp 0x67139F0                                 ; -> sub_67139f0
  6710c3e  lea rcx,[rbp+0x2D0]
  6710c45  mov rdx,r12
  6710c48  call 0x67E2190                                ; -> sub_67e2190
  6710c4d  nop
  6710c4e  lea rcx,[rbp+0x120]
  6710c55  lea rsi,[rbp+0x4C0]
  6710c5c  mov rdx,rsi
  6710c5f  lea r8,[rbp+0x468]
  6710c66  mov r9,r12
  6710c69  call 0x678F640                                ; -> sub_678f640
  6710c6e  nop
  6710c6f  mov eax,[rsi+0x68]
  6710c72  lea rcx,[rbp+0x260]
  6710c79  mov [rcx+0x10],eax
  6710c7c  movups xmm0,[rsi+0x58]
  6710c80  movups [rcx],xmm0
  6710c83  movzx eax,byte ptr [rbp+0x52C]
  6710c8a  mov [rbp+0x274],al
  6710c90  movups xmm0,[rbp+0x530]
  6710c97  movups [rbp+0x278],xmm0
  6710c9e  movups xmm0,[rsi+0x80]


### Phase 6 — instructions #201-#240 (0x6710ca5 .. 0x6710d7e)

  6710ca5  movups xmm1,[rsi+0x90]
  6710cac  movups xmm2,[rsi+0x9F]
  6710cb3  movups [r14+0xA7],xmm2
  6710cbb  movups [r14+0x98],xmm1
  6710cc3  movups [r14+0x88],xmm0
  6710ccb  movzx eax,word ptr [rbp+0x570]
  6710cd2  mov [rbp+0x2B8],ax
  6710cd9  mov rax,[rbp+0x778]
  6710ce0  mov r8,[rax+0x480]
  6710ce7  mov rax,[rax+0x488]
  6710cee  mov rdx,rax
  6710cf1  sub rdx,r8
  6710cf4  cmp rdx,0xFFFFFFFFFFFFFFD0
  6710cf8  je 0x6713B0F                                  ; -> sub_6713b0f
  6710cfe  test r8,r8
  6710d01  setne cl
  6710d04  test rax,rax
  6710d07  sete r9b
  6710d0b  or r9b,cl
  6710d0e  je 0x6713B0F                                  ; -> sub_6713b0f
  6710d14  cmp rax,r8
  6710d17  je 0x67133A9                                  ; -> sub_67133a9
  6710d1d  mov rax,[rbp+0x788]
  6710d24  cmp qword ptr [rax],0
  6710d28  je 0x67133A9                                  ; -> sub_67133a9
  6710d2e  sar rdx,4
  6710d32  mov rax,0xAAAAAAAAAAAAAAAB
  6710d3c  imul rdx,rax
  6710d40  mov dword ptr [rsp+0x20],0x41800000
  6710d48  lea rcx,[rbp+0x810]
  6710d4f  lea r9,[rbp+0x2F0]
  6710d56  call 0x6769EE0                                ; -> sub_6769ee0
  6710d5b  nop
  6710d5c  mov rax,[rbp+0x810]
  6710d63  mov rcx,[rbp+0x818]
  6710d6a  mov r15,rax
  6710d6d  mov [rbp+0x848],rax
  6710d74  mov [rbp+0x578],rcx
  6710d7b  cmp rax,rcx
  6710d7e  je 0x6713316                                  ; -> sub_6713316


### Phase 7 — instructions #241-#280 (0x6710d84 .. 0x6710e2a)

  6710d84  mov rax,[rbp+0x788]
  6710d8b  mov rcx,[rax]
  6710d8e  mov rax,[rcx]
  6710d91  mov rax,[rax+0x48]
  6710d95  lea rdx,[rbp+0x310]
  6710d9c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710da2  nop
  6710da3  mov r15,[rbp+0x810]
  6710daa  mov rsi,[rbp+0x818]
  6710db1  mov rax,rsi
  6710db4  sub rax,r15
  6710db7  cmp rax,0xFFFFFFFFFFFFFFE0
  6710dbb  je 0x6713B0F                                  ; -> sub_6713b0f
  6710dc1  test r15,r15
  6710dc4  setne al
  6710dc7  test rsi,rsi
  6710dca  sete cl
  6710dcd  or cl,al
  6710dcf  je 0x6713B0F                                  ; -> sub_6713b0f
  6710dd5  test r15,r15
  6710dd8  setne al
  6710ddb  cmp rsi,r15
  6710dde  sete cl
  6710de1  or cl,al
  6710de3  je 0x6713B0F                                  ; -> sub_6713b0f
  6710de9  lea rax,[rbp+0x7E0]
  6710df0  mov [rbp+0x7D0],rax
  6710df7  mov rax,0x100000000
  6710e01  mov [rbp+0x7D8],rax
  6710e08  cmp rsi,r15
  6710e0b  je short 0x6710E2C                            ; -> loc_6710e2c
  6710e0d  nop [rax]
loc_6710e10:  ; from 6710e2a
  6710e10  lea rcx,[rbp+0x7D0]
  6710e17  mov rdx,r13
  6710e1a  mov r8,r15
  6710e1d  call 0x676A670                                ; -> sub_676a670
  6710e22  nop
  6710e23  add r15,0x20
  6710e27  cmp r15,rsi
  6710e2a  jne short 0x6710E10                           ; -> loc_6710e10
loc_6710e2c:  ; from 6710e0b


### Phase 8 — instructions #281-#320 (0x6710e2c .. 0x6710f0f)

  6710e2c  lea rax,[rbp+0x7A0]
  6710e33  mov [rbp+0x790],rax
  6710e3a  mov rax,0x100000000
  6710e44  mov [rbp+0x798],rax
  6710e4b  lea rsi,[rbp+0x790]
  6710e52  mov rcx,rsi
  6710e55  lea rdx,[rbp+0x7D0]
  6710e5c  call 0x6764990                                ; -> sub_6764990
  6710e61  nop
  6710e62  mov [rsp+0x20],rsi
  6710e67  mov rcx,r13
  6710e6a  lea rdx,[rbp+0x208]
  6710e71  lea r8,[rbp+0x1B0]
  6710e78  lea r9,[rbp+0x128]
  6710e7f  call 0x6792160                                ; -> sub_6792160
  6710e84  nop
  6710e85  lea rcx,[rbp+0x260]
  6710e8c  mov eax,[rcx+0x10]
  6710e8f  lea rdx,[rbp+0x6F8]
  6710e96  mov [rdx+0x10],eax
  6710e99  movups xmm0,[rcx]
  6710e9c  movups [rdx],xmm0
  6710e9f  movzx eax,byte ptr [rbp+0x274]
  6710ea6  mov [rbp+0x70C],al
  6710eac  movups xmm0,[rbp+0x278]
  6710eb3  movups [rbp+0x710],xmm0
  6710eba  movups xmm0,[r14+0x88]
  6710ec2  movups xmm1,[r14+0x98]
  6710eca  movups xmm2,[r14+0xA7]
  6710ed2  lea rax,[rbp+0x584]
  6710ed9  movups [rax+0x1BB],xmm2
  6710ee0  movups [rax+0x1AC],xmm1
  6710ee7  movups [rax+0x19C],xmm0
  6710eee  movzx eax,word ptr [rbp+0x2B8]
  6710ef5  mov [rbp+0x750],ax
  6710efc  mov rax,[rbp+0x838]
  6710f03  mov rcx,[rax+0x10]
  6710f07  mov eax,0x9D0
  6710f0c  add rcx,rax
  6710f0f  call 0x5ABA5C0                                ; -> sub_5aba5c0


### Phase 9 — instructions #321-#360 (0x6710f14 .. 0x6710fef)

  6710f14  nop
  6710f15  mov r15,rax
  6710f18  movaps [rbp+0x3C0],xmm6
  6710f1f  movaps [rbp+0x3B0],xmm6
  6710f26  movaps [rbp+0x3A0],xmm6
  6710f2d  movaps [rbp+0x390],xmm6
  6710f34  movaps [rbp+0x380],xmm6
  6710f3b  movaps [rbp+0x370],xmm6
  6710f42  movaps [rbp+0x360],xmm6
  6710f49  movaps [rbp+0x350],xmm6
  6710f50  movaps [rbp+0x340],xmm6
  6710f57  movaps [rbp+0x330],xmm6
  6710f5e  movaps [rbp+0x320],xmm6
  6710f65  movaps [rbp+0x310],xmm6
  6710f6c  mov qword ptr [rbp+0x3D0],0
  6710f77  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710f7e  mov rax,[rcx]
  6710f81  mov rax,[rax+0x10]
  6710f85  mov dl,0x4A
  6710f87  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710f8d  nop
  6710f8e  mov [rbp+0x857],al
  6710f94  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
  6710f9b  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
  6710fa2  je 0x6711F9D                                  ; -> loc_6711f9d
  6710fa8  movzx eax,word ptr [rbp+0x750]
  6710faf  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
  6710fb2  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
  6710fba  jmp 0x6711FB1                                 ; -> loc_6711fb1
  6710fbf  lea rcx,[r15+0x8A0]                           ; R ret@5aba5c0+0x8A0
  6710fc6  lea r8,[rbp+0x758]
  6710fcd  call 0x1EF6F90                                ; -> sub_1ef6f90
  6710fd2  nop
  6710fd3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6710fda  mov rax,[rcx]
  6710fdd  mov rax,[rax+0x10]
  6710fe1  movzx edx,byte ptr [rbp+0x857]
  6710fe8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6710fee  nop
  6710fef  mov eax,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8


### Phase 10 — instructions #361-#400 (0x6710ff6 .. 0x67110c3)

  6710ff6  sub eax,[r15+0x8A0]                           ; R ret@5aba5c0+0x8A0
  6710ffd  shr eax,1
  6710fff  dec eax
  6711001  mov [rbp+0x320],ax
  6711008  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671100f  mov rax,[rcx]
  6711012  mov rax,[rax+0x10]
  6711016  mov dl,0x4A
  6711018  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671101e  nop
  671101f  mov [rbp+0x857],al
  6711025  mov rdx,[r15+0x758]                           ; R ret@5aba5c0+0x758
  671102c  cmp rdx,[r15+0x760]                           ; R ret@5aba5c0+0x760
  6711033  je 0x67110BC                                  ; -> loc_67110bc
  6711039  lea rcx,[rbp+0x700]
  6711040  mov eax,[rcx+0x10]
  6711043  mov [rdx+0x10],eax                            ; W *(ret@5aba5c0+0x758)+0x10
  6711046  movups xmm0,[rcx]
  6711049  movups [rdx],xmm0                             ; W *(ret@5aba5c0+0x758)+0x0
  671104c  movzx eax,byte ptr [rbp+0x714]
  6711053  mov [rdx+0x14],al                             ; W *(ret@5aba5c0+0x758)+0x14
  6711056  movss xmm0,[rbp+0x718]
  671105e  movss [rdx+0x18],xmm0                         ; W *(ret@5aba5c0+0x758)+0x18
  6711063  movss xmm0,[rbp+0x71C]
  671106b  movss [rdx+0x1C],xmm0                         ; W *(ret@5aba5c0+0x758)+0x1C
  6711070  movss xmm0,[rbp+0x720]
  6711078  movss [rdx+0x20],xmm0                         ; W *(ret@5aba5c0+0x758)+0x20
  671107d  movss xmm0,[rbp+0x724]
  6711085  movss [rdx+0x24],xmm0                         ; W *(ret@5aba5c0+0x758)+0x24
  671108a  lea rax,[rbp+0x584]
  6711091  movups xmm0,[rax+0x1A4]
  6711098  movups xmm1,[rax+0x1B4]
  671109f  movups xmm2,[rax+0x1C3]
  67110a6  movups [rdx+0x28],xmm0                        ; W *(ret@5aba5c0+0x758)+0x28
  67110aa  movups [rdx+0x38],xmm1                        ; W *(ret@5aba5c0+0x758)+0x38
  67110ae  movups [rdx+0x47],xmm2                        ; W *(ret@5aba5c0+0x758)+0x47
  67110b2  add qword ptr [r15+0x758],0x58                ; W ret@5aba5c0+0x758
  67110ba  jmp short 0x67110D0                           ; -> loc_67110d0
loc_67110bc:  ; from 6711033
  67110bc  lea rcx,[r15+0x750]
  67110c3  lea r8,[rbp+0x700]


### Phase 11 — instructions #401-#440 (0x67110ca .. 0x6711182)

  67110ca  call 0x6760A80                                ; -> sub_6760a80
  67110cf  nop
loc_67110d0:  ; from 67110ba
  67110d0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67110d7  mov rax,[rcx]
  67110da  mov rax,[rax+0x10]
  67110de  movzx edx,byte ptr [rbp+0x857]
  67110e5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67110eb  nop
  67110ec  mov qword ptr [rbp+0x310],0x4001
  67110f7  mov eax,[r15+0x758]
  67110fe  sub eax,[r15+0x750]
  6711105  shr eax,3
  6711108  imul eax,0xFFFF8BA3
  671110e  dec eax
  6711110  mov [rbp+0x33C],ax
  6711117  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671111e  mov rax,[rcx]
  6711121  mov rax,[rax+0x10]
  6711125  mov dl,0x4A
  6711127  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671112d  nop
  671112e  mov [rbp+0x857],al
  6711134  mov rdx,[r15+0x860]
  671113b  cmp rdx,[r15+0x868]
  6711142  je short 0x6711150                            ; -> loc_6711150
  6711144  inc rdx
  6711147  mov [r15+0x860],rdx
  671114e  jmp short 0x671115D                           ; -> loc_671115d
loc_6711150:  ; from 6711142
  6711150  lea rcx,[r15+0x858]
  6711157  call 0x6760E60                                ; -> sub_6760e60
  671115c  nop
loc_671115d:  ; from 671114e
  671115d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711164  mov rax,[rcx]
  6711167  mov rax,[rax+0x10]
  671116b  movzx edx,byte ptr [rbp+0x857]
  6711172  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711178  nop
  6711179  mov eax,[r15+0x858]
  6711180  not eax
  6711182  add eax,[r15+0x860]


### Phase 12 — instructions #441-#480 (0x6711189 .. 0x671124b)

  6711189  mov [rbp+0x326],ax
  6711190  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711197  mov rax,[rcx]
  671119a  mov rax,[rax+0x10]
  671119e  mov dl,0x4A
  67111a0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67111a6  nop
  67111a7  mov [rbp+0x857],al
  67111ad  mov rdx,[r15+0x620]
  67111b4  cmp rdx,[r15+0x628]
  67111bb  je short 0x67111C9                            ; -> loc_67111c9
  67111bd  inc rdx
  67111c0  mov [r15+0x620],rdx
  67111c7  jmp short 0x67111D6                           ; -> loc_67111d6
loc_67111c9:  ; from 67111bb
  67111c9  lea rcx,[r15+0x618]
  67111d0  call 0x6760E60                                ; -> sub_6760e60
  67111d5  nop
loc_67111d6:  ; from 67111c7
  67111d6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67111dd  mov rax,[rcx]
  67111e0  mov rax,[rax+0x10]
  67111e4  movzx edx,byte ptr [rbp+0x857]
  67111eb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67111f1  nop
  67111f2  mov qword ptr [rbp+0x310],0x8004009
  67111fd  mov eax,[r15+0x618]
  6711204  not eax
  6711206  add eax,[r15+0x620]
  671120d  mov [rbp+0x356],ax
  6711214  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671121b  mov rax,[rcx]
  671121e  mov rax,[rax+0x10]
  6711222  mov dl,0x4A
  6711224  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671122a  mov [rbp+0x857],al
  6711230  lea rcx,[r15+0x648]
  6711237  lea rdx,[rbp+0x6A8]
  671123e  call 0x675FB30                                ; -> sub_675fb30
  6711243  nop
  6711244  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671124b  mov rax,[rcx]


### Phase 13 — instructions #481-#520 (0x671124e .. 0x671131f)

  671124e  mov rax,[rax+0x10]
  6711252  movzx edx,byte ptr [rbp+0x857]
  6711259  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671125f  nop
  6711260  mov eax,[r15+0x650]
  6711267  sub eax,[r15+0x648]
  671126e  shr eax,3
  6711271  imul eax,0xFFFF8E39
  6711277  dec eax
  6711279  mov [rbp+0x352],ax
  6711280  lea rcx,[r15+0x780]
  6711287  lea rdx,[rbp+0x650]
  671128e  call 0x675F3B0                                ; -> sub_675f3b0
  6711293  nop
  6711294  mov eax,[r15+0x788]
  671129b  sub eax,[r15+0x780]
  67112a2  shr eax,3
  67112a5  imul eax,0xFFFF8BA3
  67112ab  dec eax
  67112ad  mov [rbp+0x338],ax
  67112b4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67112bb  mov rax,[rcx]
  67112be  mov rax,[rax+0x10]
  67112c2  mov dl,0x4A
  67112c4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67112ca  mov [rbp+0x857],al
  67112d0  mov rsi,[r15+0x770]
  67112d7  cmp rsi,[r15+0x778]
  67112de  je short 0x6711321                            ; -> loc_6711321
  67112e0  mov rax,[rbp+0x5C8]
  67112e7  mov [rsi],rax
  67112ea  lea rcx,[rsi+8]
  67112ee  lea rdx,[rbp+0x5D0]
  67112f5  call 0xE869FF0                                ; -> sub_e869ff0
  67112fa  nop
  67112fb  mov rax,[rbp+0x648]
  6711302  mov [rsi+0x80],rax
  6711309  mov qword ptr [rbp+0x648],0
  6711314  add qword ptr [r15+0x770],0x88
  671131f  jmp short 0x6711338                           ; -> loc_6711338
loc_6711321:  ; from 67112de


### Phase 14 — instructions #521-#560 (0x6711321 .. 0x67113e0)

  6711321  lea rcx,[r15+0x768]
  6711328  mov rdx,rsi
  671132b  lea r8,[rbp+0x5C8]
  6711332  call 0x6760710                                ; -> sub_6760710
  6711337  nop
loc_6711338:  ; from 671131f
  6711338  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671133f  mov rax,[rcx]
  6711342  mov rax,[rax+0x10]
  6711346  movzx edx,byte ptr [rbp+0x857]
  671134d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711353  nop
  6711354  mov qword ptr [rbp+0x310],0xA007009
  671135f  mov eax,[r15+0x770]
  6711366  sub eax,[r15+0x768]
  671136d  shr eax,3
  6711370  imul eax,0xFFFFF0F1
  6711376  dec eax
  6711378  mov [rbp+0x33A],ax
  671137f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711386  mov rax,[rcx]
  6711389  mov rax,[rax+0x10]
  671138d  mov dl,0x4A
  671138f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711395  nop
  6711396  mov [rbp+0x857],al
  671139c  mov rdx,[r15+0x2D8]
  67113a3  cmp rdx,[r15+0x2E0]
  67113aa  je short 0x67113B8                            ; -> loc_67113b8
  67113ac  inc rdx
  67113af  mov [r15+0x2D8],rdx
  67113b6  jmp short 0x67113C5                           ; -> loc_67113c5
loc_67113b8:  ; from 67113aa
  67113b8  lea rcx,[r15+0x2D0]
  67113bf  call 0x6760E60                                ; -> sub_6760e60
  67113c4  nop
loc_67113c5:  ; from 67113b6
  67113c5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67113cc  mov rax,[rcx]
  67113cf  mov rax,[rax+0x10]
  67113d3  movzx edx,byte ptr [rbp+0x857]
  67113da  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67113e0  nop


### Phase 15 — instructions #561-#600 (0x67113e1 .. 0x671149f)

  67113e1  mov eax,[r15+0x2D0]
  67113e8  not eax
  67113ea  add eax,[r15+0x2D8]
  67113f1  mov [rbp+0x39C],ax
  67113f8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67113ff  mov rax,[rcx]
  6711402  mov rax,[rax+0x10]
  6711406  mov dl,0x4A
  6711408  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671140e  nop
  671140f  mov [rbp+0x857],al
  6711415  mov rdx,[r15+0x6C8]
  671141c  cmp rdx,[r15+0x6D0]
  6711423  je short 0x6711431                            ; -> loc_6711431
  6711425  inc rdx
  6711428  mov [r15+0x6C8],rdx
  671142f  jmp short 0x671143E                           ; -> loc_671143e
loc_6711431:  ; from 6711423
  6711431  lea rcx,[r15+0x6C0]
  6711438  call 0x6760E60                                ; -> sub_6760e60
  671143d  nop
loc_671143e:  ; from 671142f
  671143e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711445  mov rax,[rcx]
  6711448  mov rax,[rax+0x10]
  671144c  movzx edx,byte ptr [rbp+0x857]
  6711453  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711459  nop
  671145a  mov rax,0x400000000A107009
  6711464  mov [rbp+0x310],rax
  671146b  mov eax,[r15+0x6C0]
  6711472  not eax
  6711474  add eax,[r15+0x6C8]
  671147b  mov [rbp+0x348],ax
  6711482  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711489  mov rax,[rcx]
  671148c  mov rax,[rax+0x10]
  6711490  mov dl,0x4A
  6711492  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711498  nop
  6711499  mov [rbp+0x857],al
  671149f  mov rdx,[r15+0x6B0]


### Phase 16 — instructions #601-#640 (0x67114a6 .. 0x671155c)

  67114a6  cmp rdx,[r15+0x6B8]
  67114ad  je short 0x67114BB                            ; -> loc_67114bb
  67114af  inc rdx
  67114b2  mov [r15+0x6B0],rdx
  67114b9  jmp short 0x67114C8                           ; -> loc_67114c8
loc_67114bb:  ; from 67114ad
  67114bb  lea rcx,[r15+0x6A8]
  67114c2  call 0x6760E60                                ; -> sub_6760e60
  67114c7  nop
loc_67114c8:  ; from 67114b9
  67114c8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67114cf  mov rax,[rcx]
  67114d2  mov rax,[rax+0x10]
  67114d6  movzx edx,byte ptr [rbp+0x857]
  67114dd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67114e3  nop
  67114e4  mov eax,[r15+0x6A8]
  67114eb  not eax
  67114ed  add eax,[r15+0x6B0]
  67114f4  mov [rbp+0x34A],ax
  67114fb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711502  mov rax,[rcx]
  6711505  mov rax,[rax+0x10]
  6711509  mov dl,0x4A
  671150b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711511  nop
  6711512  mov [rbp+0x857],al
  6711518  mov rdx,[r15+0x590]
  671151f  cmp rdx,[r15+0x598]
  6711526  je short 0x6711552                            ; -> loc_6711552
  6711528  lea rax,[rdx+0x10]
  671152c  mov [rdx],rax
  671152f  mov rax,0x100000000
  6711539  mov [rdx+8],rax
  671153d  mov rcx,rdx
  6711540  mov rdx,r13
  6711543  call 0x6764990                                ; -> sub_6764990
  6711548  add qword ptr [r15+0x590],0x30
  6711550  jmp short 0x6711565                           ; -> loc_6711565
loc_6711552:  ; from 6711526
  6711552  mov rcx,r15
  6711555  add rcx,0x588
  671155c  mov r8,r13


### Phase 17 — instructions #641-#680 (0x671155f .. 0x6711616)

  671155f  call 0x6765870                                ; -> sub_6765870
  6711564  nop
loc_6711565:  ; from 6711550
  6711565  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671156c  mov rax,[rcx]
  671156f  mov rax,[rax+0x10]
  6711573  movzx edx,byte ptr [rbp+0x857]
  671157a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711580  nop
  6711581  mov rax,0x400000020A307009
  671158b  mov [rbp+0x310],rax
  6711592  mov eax,[r15+0x590]
  6711599  sub eax,[r15+0x588]
  67115a0  shr eax,4
  67115a3  imul eax,0xFFFFAAAB
  67115a9  dec eax
  67115ab  mov [rbp+0x362],ax
  67115b2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67115b9  mov rax,[rcx]
  67115bc  mov rax,[rax+0x10]
  67115c0  mov dl,0x4A
  67115c2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67115c8  nop
  67115c9  mov [rbp+0x857],al
  67115cf  mov rdx,[r15+8]
  67115d3  cmp rdx,[r15+0x10]
  67115d7  je short 0x67115F8                            ; -> loc_67115f8
  67115d9  mov r8d,0xC8
  67115df  mov rcx,rdx
  67115e2  lea rdx,[rbp+0x310]
  67115e9  call 0xEEC6EC0                                ; -> sub_eec6ec0
  67115ee  add qword ptr [r15+8],0xC8
  67115f6  jmp short 0x6711608                           ; -> loc_6711608
loc_67115f8:  ; from 67115d7
  67115f8  mov rcx,r15
  67115fb  lea r8,[rbp+0x310]
  6711602  call 0x5ABA6D0                                ; -> sub_5aba6d0
  6711607  nop
loc_6711608:  ; from 67115f6
  6711608  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671160f  mov rax,[rcx]
  6711612  mov rax,[rax+0x10]
  6711616  movzx edx,byte ptr [rbp+0x857]


### Phase 18 — instructions #681-#720 (0x671161d .. 0x67116c7)

  671161d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711623  nop
  6711624  cmp byte ptr [rbp+0x6E8],1
  671162b  jne short 0x671167F                           ; -> loc_671167f
  671162d  mov rcx,[rbp+0x6A8]
  6711634  test rcx,rcx
  6711637  je short 0x671167F                            ; -> loc_671167f
  6711639  mov rdx,[rbp+0x6B8]
  6711640  sub rdx,rcx
  6711643  cmp rdx,0x1000
  671164a  jb short 0x6711668                            ; -> loc_6711668
  671164c  mov rax,[rcx-8]
  6711650  add rcx,0xFFFFFFFFFFFFFFF8
  6711654  sub rcx,rax
  6711657  cmp rcx,0x20
  671165b  jae 0x6713B37                                 ; -> sub_6713b37
  6711661  or rdx,0x27
  6711665  mov rcx,rax
loc_6711668:  ; from 671164a
  6711668  call 0xE935700                                ; -> sub_e935700
  671166d  lea rax,[rbp+0x6A8]
  6711674  movups [rax],xmm6
  6711677  mov qword ptr [rax+0x10],0
loc_671167f:  ; from 671162b, 6711637
  671167f  mov rcx,r13
  6711682  call 0x6792810                                ; -> sub_6792810
  6711687  mov r15,[rbp+0x790]
  671168e  mov esi,[rbp+0x798]
  6711694  test rsi,rsi
  6711697  je short 0x67116E6                            ; -> loc_67116e6
  6711699  shl rsi,5
  671169d  xor r12d,r12d
  67116a0  jmp short 0x67116B9                           ; -> loc_67116b9
  67116a2  nop [rax+rax]                                 ; R ret@6792810+0x0+idx
loc_67116b0:  ; from 67116c1, 67116c7, 67116d6
  67116b0  add r12,0x20
  67116b4  cmp rsi,r12
  67116b7  je short 0x67116D8                            ; -> loc_67116d8
loc_67116b9:  ; from 67116a0
  67116b9  mov rcx,[r15+r12+8]
  67116be  test rcx,rcx
  67116c1  je short 0x67116B0                            ; -> loc_67116b0
  67116c3  lock dec dword ptr [rcx+0xC]
  67116c7  jne short 0x67116B0                           ; -> loc_67116b0


### Phase 19 — instructions #721-#760 (0x67116c9 .. 0x6711766)

  67116c9  mov rax,[rcx]
  67116cc  mov rax,[rax+8]
  67116d0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67116d6  jmp short 0x67116B0                           ; -> loc_67116b0
loc_67116d8:  ; from 67116b7
  67116d8  mov r15,[rbp+0x790]
  67116df  lea r12,[rbp+0x3E0]
loc_67116e6:  ; from 6711697
  67116e6  lea rax,[rbp+0x7A0]
  67116ed  cmp rax,r15
  67116f0  je short 0x671170F                            ; -> loc_671170f
  67116f2  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  67116f9  test r15,r15
  67116fc  je short 0x671170F                            ; -> loc_671170f
  67116fe  mov rax,[rcx]
  6711701  mov rax,[rax+0x10]
  6711705  mov rdx,r15
  6711708  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671170e  nop
loc_671170f:  ; from 67116f0, 67116fc
  671170f  mov r15,[rbp+0x7D0]
  6711716  mov esi,[rbp+0x7D8]
  671171c  test rsi,rsi
  671171f  je short 0x6711766                            ; -> loc_6711766
  6711721  shl rsi,5
  6711725  xor r12d,r12d
  6711728  jmp short 0x6711739                           ; -> loc_6711739
  671172a  nop [rax+rax]
loc_6711730:  ; from 6711741, 6711747, 6711756
  6711730  add r12,0x20
  6711734  cmp rsi,r12
  6711737  je short 0x6711758                            ; -> loc_6711758
loc_6711739:  ; from 6711728
  6711739  mov rcx,[r15+r12+8]
  671173e  test rcx,rcx
  6711741  je short 0x6711730                            ; -> loc_6711730
  6711743  lock dec dword ptr [rcx+0xC]
  6711747  jne short 0x6711730                           ; -> loc_6711730
  6711749  mov rax,[rcx]
  671174c  mov rax,[rax+8]
  6711750  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711756  jmp short 0x6711730                           ; -> loc_6711730
loc_6711758:  ; from 6711737
  6711758  mov r15,[rbp+0x7D0]
  671175f  lea r12,[rbp+0x3E0]
loc_6711766:  ; from 671171f
  6711766  lea rax,[rbp+0x7E0]


### Phase 20 — instructions #761-#800 (0x671176d .. 0x6711800)

  671176d  cmp rax,r15
  6711770  je short 0x671178F                            ; -> loc_671178f
  6711772  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  6711779  test r15,r15
  671177c  je short 0x671178F                            ; -> loc_671178f
  671177e  mov rax,[rcx]
  6711781  mov rax,[rax+0x10]
  6711785  mov rdx,r15
  6711788  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671178e  nop
loc_671178f:  ; from 6711770, 671177c
  671178f  mov r15,[rbp+0x810]
  6711796  test r15,r15
  6711799  je short 0x6711815                            ; -> loc_6711815
  671179b  mov rsi,[rbp+0x818]
  67117a2  cmp r15,rsi
  67117a5  jne short 0x67117B9                           ; -> loc_67117b9
  67117a7  jmp short 0x67117DE                           ; -> loc_67117de
  67117a9  nop [rax]
loc_67117b0:  ; from 67117c0, 67117c6, 67117d5
  67117b0  add r15,0x20
  67117b4  cmp r15,rsi
  67117b7  je short 0x67117D7                            ; -> loc_67117d7
loc_67117b9:  ; from 67117a5
  67117b9  mov rcx,[r15+8]
  67117bd  test rcx,rcx
  67117c0  je short 0x67117B0                            ; -> loc_67117b0
  67117c2  lock dec dword ptr [rcx+0xC]
  67117c6  jne short 0x67117B0                           ; -> loc_67117b0
  67117c8  mov rax,[rcx]
  67117cb  mov rax,[rax+8]
  67117cf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67117d5  jmp short 0x67117B0                           ; -> loc_67117b0
loc_67117d7:  ; from 67117b7
  67117d7  mov r15,[rbp+0x810]
loc_67117de:  ; from 67117a7
  67117de  mov rdx,[rbp+0x820]
  67117e5  sub rdx,r15
  67117e8  cmp rdx,0x1000
  67117ef  jb short 0x671180D                            ; -> loc_671180d
  67117f1  mov rax,[r15-8]
  67117f5  add r15,0xFFFFFFFFFFFFFFF8
  67117f9  sub r15,rax
  67117fc  cmp r15,0x20
  6711800  jae 0x6713B37                                 ; -> sub_6713b37


