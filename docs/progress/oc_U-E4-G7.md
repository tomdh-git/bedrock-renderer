# U-E4-G7 — Unit 7 of builder 0x670b6e0 (ends 0x6713c64)

## NEXT block at TOP — resume at 0x6711806

Unit range covered: none yet
Resume address after this unit: 0x6711806 (start; continuation from U-E4-G6 which covered 0x67108da .. 0x6711800)

Method: linear `rdis dis` listing, 40-instruction steps per phase.
Tags: [V] = saw in disasm (cite RVA), [I] = inferred, [?] = unknown.
Direct jumps written as `jmp <addr>` (not `jmp qword ptr`).

---

### Phase 1 — instructions #1-#40 (0x6711806 .. 0x67118e3)

  6711806  add rdx,0x27
  671180a  mov r15,rax
  671180d  mov rcx,r15
  6711810  call 0xE935700                                ; -> sub_e935700
  6711815  mov rax,[rbp+0x578]
  671181c  cmp [rbp+0x848],rax
  6711823  jne 0x6711E8C                                 ; -> loc_6711e8c
  6711829  mov rax,[rbp+0x838]
  6711830  mov rcx,[rax+0x10]
  6711834  mov eax,0x9D0
  6711839  add rcx,rax
  671183c  call 0x5ABA5C0                                ; -> sub_5aba5c0
  6711841  nop
  6711842  mov r15,rax
  6711845  movaps [rbp+0x630],xmm6
  671184c  movaps [rbp+0x620],xmm6
  6711853  movaps [rbp+0x610],xmm6
  671185a  movaps [rbp+0x600],xmm6
  6711861  movaps [rbp+0x5F0],xmm6
  6711868  movaps [rbp+0x5E0],xmm6
  671186f  movaps [rbp+0x5D0],xmm6
  6711876  movaps [rbp+0x5C0],xmm6
  671187d  movaps [rbp+0x5B0],xmm6
  6711884  movaps [rbp+0x5A0],xmm6
  671188b  movaps [rbp+0x590],xmm6
  6711892  movaps [rbp+0x580],xmm6
  6711899  mov qword ptr [rbp+0x640],0
  67118a4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67118ab  mov rax,[rcx]
  67118ae  mov rax,[rax+0x10]
  67118b2  mov dl,0x4A
  67118b4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67118ba  nop
  67118bb  mov [rbp+0x848],al
  67118c1  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
  67118c8  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
  67118cf  je short 0x67118E5                            ; -> loc_67118e5
  67118d1  movzx eax,word ptr [rbp+0x2B8]
  67118d8  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
  67118db  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8


### Phase 2 — instructions #41-#80 (0x67118e3 .. 0x67119a7)

  67118e3  jmp short 0x67118F9                           ; -> loc_67118f9
  67118e5  lea rcx,[r15+0x8A0]
  67118ec  lea r8,[rbp+0x2B8]
  67118f3  call 0x1EF6F90                                ; -> sub_1ef6f90
  67118f8  nop

loc_67118f9:  ; from 67118e3
  67118f9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711900  mov rax,[rcx]
  6711903  mov rax,[rax+0x10]
  6711907  movzx edx,byte ptr [rbp+0x848]
  671190e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711914  nop
  6711915  mov eax,[r15+0x8A8]
  671191c  sub eax,[r15+0x8A0]
  6711923  shr eax,1
  6711925  dec eax
  6711927  mov [rbp+0x590],ax
  671192e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711935  mov rax,[rcx]
  6711938  mov rax,[rax+0x10]
  671193c  mov dl,0x4A
  671193e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711944  nop
  6711945  mov [rbp+0x848],al
  671194b  mov rdx,[r15+0x758]
  6711952  cmp rdx,[r15+0x760]
  6711959  je short 0x67119DA                            ; -> loc_67119da
  671195b  lea rcx,[rbp+0x260]
  6711962  mov eax,[rcx+0x10]
  6711965  mov [rdx+0x10],eax
  6711968  movups xmm0,[rcx]
  671196b  movups [rdx],xmm0
  671196e  movzx eax,byte ptr [rbp+0x274]
  6711975  mov [rdx+0x14],al
  6711978  movss xmm0,[rbp+0x278]
  6711980  movss [rdx+0x18],xmm0
  6711985  movss xmm0,[rbp+0x27C]
  671198d  movss [rdx+0x1C],xmm0
  6711992  movss xmm0,[rbp+0x280]
  671199a  movss [rdx+0x20],xmm0
  671199f  movss xmm0,[rbp+0x284]


### Phase 3 — instructions #81-#120 (0x67119a7 .. 0x6711a75)

  67119a7  movss [rdx+0x24],xmm0                         ; W a1+0x24
  67119ac  movups xmm0,[r14+0x88]
  67119b4  movups xmm1,[r14+0x98]
  67119bc  movups xmm2,[r14+0xA7]
  67119c4  movups [rdx+0x28],xmm0                        ; W a1+0x28
  67119c8  movups [rdx+0x38],xmm1                        ; W a1+0x38
  67119cc  movups [rdx+0x47],xmm2                        ; W a1+0x47
  67119d0  add qword ptr [r15+0x758],0x58
  67119d8  jmp short 0x67119EE                           ; -> loc_67119ee
  67119da  lea rcx,[r15+0x750]
  67119e1  lea r8,[rbp+0x260]
  67119e8  call 0x6760A80                                ; -> sub_6760a80
  67119ed  nop

loc_67119ee:  ; from 67119d8
  67119ee  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67119f5  mov rax,[rcx]
  67119f8  mov rax,[rax+0x10]
  67119fc  movzx edx,byte ptr [rbp+0x848]
  6711a03  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711a09  nop
  6711a0a  mov qword ptr [rbp+0x580],0x4001
  6711a15  mov eax,[r15+0x758]
  6711a1c  sub eax,[r15+0x750]
  6711a23  shr eax,3
  6711a26  imul eax,0xFFFF8BA3
  6711a2c  dec eax
  6711a2e  mov [rbp+0x5AC],ax
  6711a35  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711a3c  mov rax,[rcx]
  6711a3f  mov rax,[rax+0x10]
  6711a43  mov dl,0x4A
  6711a45  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711a4b  nop
  6711a4c  mov [rbp+0x848],al
  6711a52  mov rdx,[r15+0x860]
  6711a59  cmp rdx,[r15+0x868]
  6711a60  je short 0x6711A6E                            ; -> loc_6711a6e
  6711a62  inc rdx
  6711a65  mov [r15+0x860],rdx
  6711a6c  jmp short 0x6711A7B                           ; -> loc_6711a7b
  6711a6e  lea rcx,[r15+0x858]


### Phase 4 — instructions #121-#160 (0x6711a75 .. 0x6711b31)

  6711a75  call 0x6760E60                                ; -> sub_6760e60
  6711a7a  nop
  6711a7b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711a82  mov rax,[rcx]
  6711a85  mov rax,[rax+0x10]
  6711a89  movzx edx,byte ptr [rbp+0x848]
  6711a90  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711a96  nop
  6711a97  mov eax,[r15+0x858]
  6711a9e  not eax
  6711aa0  add eax,[r15+0x860]
  6711aa7  mov [rbp+0x596],ax
  6711aae  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711ab5  mov rax,[rcx]
  6711ab8  mov rax,[rax+0x10]
  6711abc  mov dl,0x4A
  6711abe  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711ac4  nop
  6711ac5  mov [rbp+0x848],al
  6711acb  mov rdx,[r15+0x620]
  6711ad2  cmp rdx,[r15+0x628]
  6711ad9  je short 0x6711AE7                            ; -> loc_6711ae7
  6711adb  inc rdx
  6711ade  mov [r15+0x620],rdx
  6711ae5  jmp short 0x6711AF4                           ; -> loc_6711af4

loc_6711ae7:  ; from 6711ad9
  6711ae7  lea rcx,[r15+0x618]
  6711aee  call 0x6760E60                                ; -> sub_6760e60
  6711af3  nop

loc_6711af4:  ; from 6711ae5
  6711af4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711afb  mov rax,[rcx]
  6711afe  mov rax,[rax+0x10]
  6711b02  movzx edx,byte ptr [rbp+0x848]
  6711b09  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711b0f  nop
  6711b10  mov eax,[r15+0x618]
  6711b17  not eax
  6711b19  add eax,[r15+0x620]
  6711b20  mov [rbp+0x5C6],ax
  6711b27  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711b2e  mov rax,[rcx]


### Phase 5 — instructions #161-#200 (0x6711b31 .. 0x6711c03)

  6711b31  mov rax,[rax+0x10]
  6711b35  mov dl,0x4A
  6711b37  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711b3d  mov [rbp+0x848],al
  6711b43  lea rcx,[r15+0x648]
  6711b4a  lea rdx,[rbp+0x208]
  6711b51  call 0x675FB30                                ; -> sub_675fb30
  6711b56  nop
  6711b57  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711b5e  mov rax,[rcx]
  6711b61  mov rax,[rax+0x10]
  6711b65  movzx edx,byte ptr [rbp+0x848]
  6711b6c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711b72  nop
  6711b73  mov eax,[r15+0x650]
  6711b7a  sub eax,[r15+0x648]
  6711b81  shr eax,3
  6711b84  imul eax,0xFFFF8E39
  6711b8a  dec eax
  6711b8c  mov [rbp+0x5C2],ax
  6711b93  lea rcx,[r15+0x780]
  6711b9a  lea rdx,[rbp+0x1B0]
  6711ba1  call 0x675F3B0                                ; -> sub_675f3b0
  6711ba6  nop
  6711ba7  mov qword ptr [rbp+0x580],0xA005009
  6711bb2  mov eax,[r15+0x788]
  6711bb9  sub eax,[r15+0x780]
  6711bc0  shr eax,3
  6711bc3  imul eax,0xFFFF8BA3
  6711bc9  dec eax
  6711bcb  mov [rbp+0x5A8],ax
  6711bd2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711bd9  mov rax,[rcx]
  6711bdc  mov rax,[rax+0x10]
  6711be0  mov dl,0x4A
  6711be2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711be8  mov [rbp+0x848],al
  6711bee  mov rsi,[r15+0x770]
  6711bf5  cmp rsi,[r15+0x778]
  6711bfc  je short 0x6711C3F                            ; -> loc_6711c3f

