# Unit U-Sx3 — effect_shadow_extractor_66a9d50 slice 0x66aa758..0x66aac42 (chunk 3 of 6)

## NEXT
DONE

## Source
Input data: docs/progress/_part_Sx3.txt (250 instructions, 0x66aa758..0x66aac42), the shadow-extractor slice inside effect_shadow_extractor_66a9d50_66ab74e. Every quoted instruction line was checked against the exe with rdis (`dis 0x66aa758 800`) and matches [V]. Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01); RVAs are image-relative [V]. All sizes are taken from the instruction mnemonic (movups=16, qword/mov rax=8, dword/mov eax/movss=4, word=2, byte=1) [V].

## Phase 1: 0x66aa758..0x66aa832
Derive a jump index from [rbp+0x3A8] (sub, sar 3, imul by 0xCCCCCCCCCCCCCCCD) and indirect-jump through the table at [0xF2BF848]; case targets store [rbp+0x3C0] or [rbp+0x3C8] to [rbp+0x310], set byte [rbp+0x320]=0xFF, copy 16 bytes [rcx+0x20] to [r14+0x15C] in two cases, or lock-increment the dword at [rcx+8] for the [rbp+0x3D0] pointer cases.
0x66aa758  sub rdx,[rbp+0x3A8]
0x66aa75f  sar rdx,3
0x66aa763  mov rax,0xCCCCCCCCCCCCCCCD
0x66aa76d  imul rdx,rax
0x66aa771  lea rcx,[rbp+0x2E8]
0x66aa778  lea r8,[rbp+0x3A8]
0x66aa77f  lea r9,[rbp+0x3B0]
0x66aa786  call 0x56B8630
0x66aa78b  nop
0x66aa78c  mov rax,[rbp+0x3C0]
0x66aa793  mov [rbp+0x308],rax
0x66aa79a  mov byte ptr [rbp+0x320],0xFF
0x66aa7a1  movzx eax,byte ptr [rbp+0x3D8]
0x66aa7a8  cmp rax,3
0x66aa7ac  ja 0x66AADAE
0x66aa7b2  lea rdx,[0xF2BF848]
0x66aa7b9  movsxd rcx,[rdx+rax*4]
0x66aa7bd  add rcx,rdx
0x66aa7c0  jmp rcx
0x66aa7c2  mov rcx,[rbp+0x3C8]
0x66aa7c9  mov [rbp+0x310],rcx
0x66aa7d0  jmp 0x66AADA8
0x66aa7d5  lea rcx,[rbp+0x3A8]
0x66aa7dc  movups xmm0,[rcx+0x20]
0x66aa7e0  movups [r14+0x15C],xmm0
0x66aa7e8  jmp short 0x66AA862
0x66aa7ea  lea rcx,[rbp+0x3A8]
0x66aa7f1  movups xmm0,[rcx+0x20]
0x66aa7f5  movups [r14+0x15C],xmm0
0x66aa7fd  jmp 0x66AADA8
0x66aa802  movups [r14+0x15C],xmm6
0x66aa80a  mov rcx,[rbp+0x3D0]
0x66aa811  test rcx,rcx
0x66aa814  je short 0x66AA84B
0x66aa816  lock inc dword ptr [rcx+8]
0x66aa81a  mov rcx,[rbp+0x3D0]
0x66aa821  jmp short 0x66AA84D
0x66aa823  movups [r14+0x15C],xmm6
0x66aa82b  mov rcx,[rbp+0x3D0]
0x66aa832  test rcx,rcx

## Phase 2: 0x66aa835..0x66aa902
Complete the [rbp+0x3D0] cases (xor ecx=0 on the je target; store [rbp+0x3C8] to [rbp+0x310] and rcx to [rbp+0x318] on fall-through), set byte [rbp+0x320]=al, then copy [rcx+0x48] to [r14+0x184] and [rcx+0x38] to [r14+0x174], compute [r15+0x10]+0x9D0 and call sub_5aba5c0, and zero a 192-byte block at [rbp+0xD8] with twelve xmm6 movups stores ([rax+0x00]..[rax+0xB0]).
0x66aa835  je 0x66AAD91
0x66aa83b  lock inc dword ptr [rcx+8]
0x66aa83f  mov rcx,[rbp+0x3D0]
0x66aa846  jmp 0x66AAD93
0x66aa84b  xor ecx,ecx
0x66aa84d  mov rdx,[rbp+0x3C8]
0x66aa854  mov [rbp+0x310],rdx
0x66aa85b  mov [rbp+0x318],rcx
0x66aa862  mov [rbp+0x320],al
0x66aa868  lea rcx,[rbp+0x3A8]
0x66aa86f  mov rax,[rcx+0x48]
0x66aa873  mov [r14+0x184],rax
0x66aa87a  movups xmm0,[rcx+0x38]
0x66aa87e  movups [r14+0x174],xmm0
0x66aa886  mov rcx,[r15+0x10]
0x66aa88a  mov eax,0x9D0
0x66aa88f  add rcx,rax
0x66aa892  call 0x5ABA5C0
0x66aa897  nop
0x66aa898  mov rbx,rax
0x66aa89b  lea rax,[rbp+0xD8]
0x66aa8a2  movups [rax+0xB0],xmm6
0x66aa8a9  movups [rax+0xA0],xmm6
0x66aa8b0  movups [rax+0x90],xmm6
0x66aa8b7  movups [rax+0x80],xmm6
0x66aa8be  movups [rax+0x70],xmm6
0x66aa8c2  movups [rax+0x60],xmm6
0x66aa8c6  movups [rax+0x50],xmm6
0x66aa8ca  movups [rax+0x40],xmm6
0x66aa8ce  movups [rax+0x30],xmm6
0x66aa8d2  movups [rax+0x20],xmm6
0x66aa8d6  movups [rax+0x10],xmm6
0x66aa8da  movups [rax],xmm6
0x66aa8dd  lea rcx,[rbx+0x780]
0x66aa8e4  lea rdx,[rbp+0x2E8]
0x66aa8eb  call 0x675F3B0
0x66aa8f0  nop
0x66aa8f1  mov qword ptr [rbp+0xD0],0x1000
0x66aa8fc  mov eax,[rbx+0x788]
0x66aa902  sub eax,[rbx+0x780]

## Phase 3: 0x66aa908..0x66aa9be
Finish word field [rbp+0xF8]=(([rbx+0x788]-[rbx+0x780])>>3*0xFFFF8BA3-1), then run the global data_1233e1b0->[0x10] indirect-call idiom (dl=0x4A, store al to [rbp+0x437]); branch on [rbx+0x8A8] vs [rbx+0x8B0]: if unequal store word [rbp+0x2E0] to [rdx] and add 2 to [rbx+0x8A8], else call sub_1ef6f90([rbx+0x8A0],[rbp+0x2E0]); repeat the global idiom storing al to [rbp+0x437], then lea rcx,[rbx+0x648].
0x66aa908  shr eax,3
0x66aa90b  imul eax,0xFFFF8BA3
0x66aa911  dec eax
0x66aa913  mov [rbp+0xF8],ax
0x66aa91a  mov rcx,[0x1233E1B0]
0x66aa921  mov rax,[rcx]
0x66aa924  mov rax,[rax+0x10]
0x66aa928  mov dl,0x4A
0x66aa92a  call qword ptr [0xF99FFA0]
0x66aa930  nop
0x66aa931  mov [rbp+0x437],al
0x66aa937  mov rdx,[rbx+0x8A8]
0x66aa93e  cmp rdx,[rbx+0x8B0]
0x66aa945  je short 0x66AA95B
0x66aa947  movzx eax,word ptr [rbp+0x2E0]
0x66aa94e  mov [rdx],ax
0x66aa951  add qword ptr [rbx+0x8A8],2
0x66aa959  jmp short 0x66AA96F
0x66aa95b  lea rcx,[rbx+0x8A0]
0x66aa962  lea r8,[rbp+0x2E0]
0x66aa969  call 0x1EF6F90
0x66aa96e  nop
0x66aa96f  mov rcx,[0x1233E1B0]
0x66aa976  mov rax,[rcx]
0x66aa979  mov rax,[rax+0x10]
0x66aa97d  movzx edx,byte ptr [rbp+0x437]
0x66aa984  call qword ptr [0xF99FFA0]
0x66aa98a  nop
0x66aa98b  mov eax,[rbx+0x8A8]
0x66aa991  sub eax,[rbx+0x8A0]
0x66aa997  shr eax,1
0x66aa999  dec eax
0x66aa99b  mov [rbp+0xE0],ax
0x66aa9a2  mov rcx,[0x1233E1B0]
0x66aa9a9  mov rax,[rcx]
0x66aa9ac  mov rax,[rax+0x10]
0x66aa9b0  mov dl,0x4A
0x66aa9b2  call qword ptr [0xF99FFA0]
0x66aa9b8  mov [rbp+0x437],al
0x66aa9be  lea rcx,[rbx+0x648]

## Phase 4: 0x66aa9c5..0x66aaa8f
lea rdx,[rbp+0x298] and call sub_675FB30([rbx+0x648],[rbp+0x298]); run the global indirect-call idiom; compute word [rbp+0xE0]=(([rbx+0x8A8]-[rbx+0x8A0])>>1-1); run the global idiom again; compute word [rbp+0x112]=(([rbx+0x650]-[rbx+0x648])>>3*0xFFFF8E39-1); run the global idiom again; then if [rbx+0x770] != [rbx+0x778] store [rbp+0x210] to [rsi], call sub_e869ff0(rsi+8, rbp+0x218), store [rbp+0x290] to [rsi+0x80], zero [rbp+0x290], add 0x88 to [rbx+0x770]; else call sub_6760710([rbx+0x768], rsi, rbp+0x210).
0x66aa9c5  lea rdx,[rbp+0x298]
0x66aa9cc  call 0x675FB30
0x66aa9d1  nop
0x66aa9d2  mov rcx,[0x1233E1B0]
0x66aa9d9  mov rax,[rcx]
0x66aa9dc  mov rax,[rax+0x10]
0x66aa9e0  movzx edx,byte ptr [rbp+0x437]
0x66aa9e7  call qword ptr [0xF99FFA0]
0x66aa9ed  nop
0x66aa9ee  mov eax,[rbx+0x650]
0x66aa9f4  sub eax,[rbx+0x648]
0x66aa9fa  shr eax,3
0x66aa9fd  imul eax,0xFFFF8E39
0x66aaa03  dec eax
0x66aaa05  mov [rbp+0x112],ax
0x66aaa0c  mov rcx,[0x1233E1B0]
0x66aaa13  mov rax,[rcx]
0x66aaa16  mov rax,[rax+0x10]
0x66aaa1a  mov dl,0x4A
0x66aaa1c  call qword ptr [0xF99FFA0]
0x66aaa22  mov [rbp+0x437],al
0x66aaa28  mov rsi,[rbx+0x770]
0x66aaa2f  cmp rsi,[rbx+0x778]
0x66aaa36  je short 0x66AAA79
0x66aaa38  mov rax,[rbp+0x210]
0x66aaa3f  mov [rsi],rax
0x66aaa42  lea rcx,[rsi+8]
0x66aaa46  lea rdx,[rbp+0x218]
0x66aaa4d  call 0xE869FF0
0x66aaa52  nop
0x66aaa53  mov rax,[rbp+0x290]
0x66aaa5a  mov [rsi+0x80],rax
0x66aaa61  mov qword ptr [rbp+0x290],0
0x66aaa6c  add qword ptr [rbx+0x770],0x88
0x66aaa77  jmp short 0x66AAA90
0x66aaa79  lea rcx,[rbx+0x768]
0x66aaa80  mov rdx,rsi
0x66aaa83  lea r8,[rbp+0x210]
0x66aaa8a  call 0x6760710
0x66aaa8f  nop
## Phase 5: 0x66aaa90..0x66aab4c
Run the global indirect-call idiom (store al to [rbp+0x437]); store qword [rbp+0xD0]=0x2003001; compute word [rbp+0xFA]=(([rbx+0x770]-[rbx+0x768])>>3*0xFFFFF0F1-1); run the global idiom; if [rbx+0x860] != [rbx+0x868] then inc rdx and store to [rbx+0x860] else call sub_6760E60([rbx+0x858]); run the global idiom; compute word [rbp+0xE6]=(~[rbx+0x858] + [rbx+0x860]); run the global idiom.
0x66aaa90  mov rcx,[0x1233E1B0]
0x66aaa97  mov rax,[rcx]
0x66aaa9a  mov rax,[rax+0x10]
0x66aaa9e  movzx edx,byte ptr [rbp+0x437]
0x66aaaa5  call qword ptr [0xF99FFA0]
0x66aaaab  nop
0x66aaaac  mov qword ptr [rbp+0xD0],0x2003001
0x66aaab7  mov eax,[rbx+0x770]
0x66aaabd  sub eax,[rbx+0x768]
0x66aaac3  shr eax,3
0x66aaac6  imul eax,0xFFFFF0F1
0x66aaacc  dec eax
0x66aaace  mov [rbp+0xFA],ax
0x66aaad5  mov rcx,[0x1233E1B0]
0x66aaadc  mov rax,[rcx]
0x66aaadf  mov rax,[rax+0x10]
0x66aaae3  mov dl,0x4A
0x66aaae5  call qword ptr [0xF99FFA0]
0x66aaaeb  nop
0x66aaaec  mov [rbp+0x437],al
0x66aaaf2  mov rdx,[rbx+0x860]
0x66aaaf9  cmp rdx,[rbx+0x868]
0x66aab00  je short 0x66AAB0E
0x66aab02  inc rdx
0x66aab05  mov [rbx+0x860],rdx
0x66aab0c  jmp short 0x66AAB1B
0x66aab0e  lea rcx,[rbx+0x858]
0x66aab15  call 0x6760E60
0x66aab1a  nop
0x66aab1b  mov rcx,[0x1233E1B0]
0x66aab22  mov rax,[rcx]
0x66aab25  mov rax,[rax+0x10]
0x66aab29  movzx edx,byte ptr [rbp+0x437]
0x66aab30  call qword ptr [0xF99FFA0]
0x66aab36  nop
0x66aab37  mov eax,[rbx+0x858]
0x66aab3d  not eax
0x66aab3f  add eax,[rbx+0x860]
0x66aab45  mov [rbp+0xE6],ax
0x66aab4c  mov rcx,[0x1233E1B0]

## Phase 6: 0x66aab53..0x66aabfc
Run the global idiom; store qword [rbp+0xD0]=0x2007009; if [rbx+0x758] != [rbx+0x760]: store dword [r14+0x10] to [rdx+0x10], movups [r14] to [rdx] (16 B), byte [rbp+0x1C8] to [rdx+0x14], movss [rbp+0x1CC/0x1D0/0x1D4/0x1D8] to [rdx+0x18/0x1C/0x20/0x24], movups [r14+0x28/0x38/0x47] to [rdx+0x28/0x38/0x47], add 0x58 to [rbx+0x758]; else call sub_6760A80(rbx+0x750, r14).
0x66aab53  mov rax,[rcx]
0x66aab56  mov rax,[rax+0x10]
0x66aab5a  mov dl,0x4A
0x66aab5c  call qword ptr [0xF99FFA0]
0x66aab62  nop
0x66aab63  mov [rbp+0x437],al
0x66aab69  mov rdx,[rbx+0x758]
0x66aab70  cmp rdx,[rbx+0x760]
0x66aab77  je short 0x66AABEA
0x66aab79  mov eax,[r14+0x10]
0x66aab7d  mov [rdx+0x10],eax
0x66aab80  movups xmm0,[r14]
0x66aab84  movups [rdx],xmm0
0x66aab87  movzx eax,byte ptr [rbp+0x1C8]
0x66aab8e  mov [rdx+0x14],al
0x66aab91  movss xmm0,[rbp+0x1CC]
0x66aab99  movss [rdx+0x18],xmm0
0x66aab9e  movss xmm0,[rbp+0x1D0]
0x66aaba6  movss [rdx+0x1C],xmm0
0x66aabab  movss xmm0,[rbp+0x1D4]
0x66aabb3  movss [rdx+0x20],xmm0
0x66aabb8  movss xmm0,[rbp+0x1D8]
0x66aabc0  movss [rdx+0x24],xmm0
0x66aabc5  movups xmm0,[r14+0x28]
0x66aabca  movups xmm1,[r14+0x38]
0x66aabcf  movups xmm2,[r14+0x47]
0x66aabd4  movups [rdx+0x28],xmm0
0x66aabd8  movups [rdx+0x38],xmm1
0x66aabdc  movups [rdx+0x47],xmm2
0x66aabe0  add qword ptr [rbx+0x758],0x58
0x66aabe8  jmp short 0x66AABFD
0x66aabea  mov rcx,rbx
0x66aabed  add rcx,0x750
0x66aabf4  mov r8,r14
0x66aabf7  call 0x6760A80
0x66aabfc  nop

## Phase 7: 0x66aac19..0x66aac42
Run the global idiom; store qword [rbp+0xD0]=0x2007009; compute word [rbp+0xFC]=(([rbx+0x758]-[rbx+0x750])>>3*0xFFFF8BA3-1); end at mov rcx,[0x1233E1B0] (slice boundary).
0x66aabfd  mov rcx,[0x1233E1B0]
0x66aac04  mov rax,[rcx]
0x66aac07  mov rax,[rax+0x10]
0x66aac0b  movzx edx,byte ptr [rbp+0x437]
0x66aac12  call qword ptr [0xF99FFA0]
0x66aac18  nop
0x66aac19  mov qword ptr [rbp+0xD0],0x2007009
0x66aac24  mov eax,[rbx+0x758]
0x66aac2a  sub eax,[rbx+0x750]
0x66aac30  shr eax,3
0x66aac33  imul eax,0xFFFF8BA3
0x66aac39  dec eax
0x66aac3b  mov [rbp+0xFC],ax
0x66aac42  mov rcx,[0x1233E1B0]

## Field map (offset | size | direction | verbatim line(s) | meaning)
| offset | size | direction | verbatim line | meaning |
| rbp+0x1C8 | 1 | R | 0x66aab87  movzx eax,byte ptr [rbp+0x1C8] | - |
| rbp+0x1CC | 4 | R | 0x66aab91  movss xmm0,[rbp+0x1CC] | - |
| rbp+0x1D0 | 4 | R | 0x66aab9e  movss xmm0,[rbp+0x1D0] | - |
| rbp+0x1D4 | 4 | R | 0x66aabab  movss xmm0,[rbp+0x1D4] | - |
| rbp+0x1D8 | 4 | R | 0x66aabb8  movss xmm0,[rbp+0x1D8] | - |
| rbp+0x210 | 8 | R | 0x66aaa38  mov rax,[rbp+0x210] | - |
| rbp+0x290 | 8 | R/W | 0x66aaa53  mov rax,[rbp+0x290] ; 0x66aaa61  mov qword ptr [rbp+0x290],0 | read then cleared |
| rbp+0x2E0 | 2 | R | 0x66aa947  movzx eax,word ptr [rbp+0x2E0] | - |
| rbp+0x308 | 8 | W | 0x66aa793  mov [rbp+0x308],rax | - |
| rbp+0x310 | 8 | W | 0x66aa7c9  mov [rbp+0x310],rcx ; 0x66aa854  mov [rbp+0x310],rdx | - |
| rbp+0x318 | 8 | W | 0x66aa85b  mov [rbp+0x318],rcx | - |
| rbp+0x320 | 1 | W | 0x66aa79a  mov byte ptr [rbp+0x320],0xFF ; 0x66aa862  mov [rbp+0x320],al | byte flag: 0xFF then al |
| rbp+0x3A8 | 8 | R | 0x66aa758  sub rdx,[rbp+0x3A8] | - |
| rbp+0x3C0 | 8 | R | 0x66aa78c  mov rax,[rbp+0x3C0] | - |
| rbp+0x3C8 | 8 | R | 0x66aa7c2  mov rcx,[rbp+0x3C8] ; 0x66aa84d  mov rdx,[rbp+0x3C8] | - |
| rbp+0x3D0 | 8 | R | 0x66aa80a  mov rcx,[rbp+0x3D0] ; 0x66aa81a  mov rcx,[rbp+0x3D0] ; 0x66aa82b  mov rcx,[rbp+0x3D0] | pointer tested and refcounted |
| rbp+0x3D8 | 1 | R | 0x66aa7a1  movzx eax,byte ptr [rbp+0x3D8] | - |
| rbp+0x437 | 1 | R/W | 0x66aa931  mov [rbp+0x437],al ; 0x66aa97d  movzx edx,byte ptr [rbp+0x437] ; 0x66aa9b8  mov [rbp+0x437],al ; 0x66aa9e0  movzx edx,byte ptr [rbp+0x437] ; 0x66aaa22  mov [rbp+0x437],al ; 0x66aaa9e  movzx edx,byte ptr [rbp+0x437] ; 0x66aaaec  mov [rbp+0x437],al ; 0x66aab29  movzx edx,byte ptr [rbp+0x437] ; 0x66aab63  mov [rbp+0x437],al ; 0x66aac0b  movzx edx,byte ptr [rbp+0x437] | al = low byte of indirect-call result [0xF99FFA0]=sub_eea6040 |
| rbp+0xD0 | 8 | W | 0x66aa8f1  mov qword ptr [rbp+0xD0],0x1000 ; 0x66aaaac  mov qword ptr [rbp+0xD0],0x2003001 ; 0x66aac19  mov qword ptr [rbp+0xD0],0x2007009 | state/type tag written before each idiom |
| rbp+0xE0 | 2 | W | 0x66aa99b  mov [rbp+0xE0],ax | (([rbx+0x8A8]-[rbx+0x8A0])>>1-1) |
| rbp+0xE6 | 2 | W | 0x66aab45  mov [rbp+0xE6],ax | (~[rbx+0x858] + [rbx+0x860]) |
| rbp+0xF8 | 2 | W | 0x66aa913  mov [rbp+0xF8],ax | (([rbx+0x788]-[rbx+0x780])>>3*0xFFFF8BA3-1) |
| rbp+0xFA | 2 | W | 0x66aaace  mov [rbp+0xFA],ax | (([rbx+0x770]-[rbx+0x768])>>3*0xFFFFF0F1-1) |
| rbp+0xFC | 2 | W | 0x66aac3b  mov [rbp+0xFC],ax | (([rbx+0x758]-[rbx+0x750])>>3*0xFFFF8BA3-1) |
| rbp+0x112 | 2 | W | 0x66aaa05  mov [rbp+0x112],ax | (([rbx+0x650]-[rbx+0x648])>>3*0xFFFF8E39-1) |
| rbx+0x648 | 4 | R | 0x66aa9f4  sub eax,[rbx+0x648] | base for count |
| rbx+0x650 | 4 | R | 0x66aa9ee  mov eax,[rbx+0x650] | end for count |
| rbx+0x750 | 4 | R | 0x66aac2a  sub eax,[rbx+0x750] | base for count |
| rbx+0x758 | 4/8 | R/W | 0x66aab69  mov rdx,[rbx+0x758] ; 0x66aabe0  add qword ptr [rbx+0x758],0x58 ; 0x66aac24  mov eax,[rbx+0x758] | cursor, advanced by 0x58 per entry |
| rbx+0x760 | 8 | R | 0x66aab70  cmp rdx,[rbx+0x760] | end bound |
| rbx+0x768 | 4 | R | 0x66aaabd  sub eax,[rbx+0x768] | base for count |
| rbx+0x770 | 4/8 | R/W | 0x66aaa28  mov rsi,[rbx+0x770] ; 0x66aaa6c  add qword ptr [rbx+0x770],0x88 ; 0x66aaab7  mov eax,[rbx+0x770] | cursor, advanced by 0x88 |
| rbx+0x778 | 8 | R | 0x66aaa2f  cmp rsi,[rbx+0x778] | end bound |
| rbx+0x780 | 4 | R | 0x66aa902  sub eax,[rbx+0x780] | base for count |
| rbx+0x788 | 4 | R | 0x66aa8fc  mov eax,[rbx+0x788] | end for count |
| rbx+0x858 | 4 | R | 0x66aab37  mov eax,[rbx+0x858] | - |
| rbx+0x860 | 4/8 | R/W | 0x66aaaf2  mov rdx,[rbx+0x860] ; 0x66aab05  mov [rbx+0x860],rdx ; 0x66aab3f  add eax,[rbx+0x860] | cursor, incremented then used |
| rbx+0x868 | 8 | R | 0x66aaaf9  cmp rdx,[rbx+0x868] | end bound |
| rbx+0x8A0 | 4 | R | 0x66aa991  sub eax,[rbx+0x8A0] | base for count |
| rbx+0x8A8 | 4/8 | R/W | 0x66aa937  mov rdx,[rbx+0x8A8] ; 0x66aa951  add qword ptr [rbx+0x8A8],2 ; 0x66aa98b  mov eax,[rbx+0x8A8] | cursor, advanced by 2 |
| rbx+0x8B0 | 8 | R | 0x66aa93e  cmp rdx,[rbx+0x8B0] | end bound |
| rcx+0x0 | 8 | R | 0x66aa921  mov rax,[rcx] ; 0x66aa9a9  mov rax,[rcx] ; 0x66aa9d9  mov rax,[rcx] ; 0x66aaa13  mov rax,[rcx] ; 0x66aaa97  mov rax,[rcx] ; 0x66aab22  mov rax,[rcx] ; 0x66aac04  mov rax,[rcx] | global pointer data_1233e1b0 dereference |
| rcx+0x8 | 4 | W | 0x66aa816  lock inc dword ptr [rcx+8] ; 0x66aa83b  lock inc dword ptr [rcx+8] | refcount dword |
| rcx+0x10 | 8 | R | 0x66aa924  mov rax,[rax+0x10] ; 0x66aa9ac  mov rax,[rax+0x10] ; 0x66aa9dc  mov rax,[rax+0x10] ; 0x66aaa16  mov rax,[rax+0x10] ; 0x66aaa9a  mov rax,[rax+0x10] ; 0x66aab25  mov rax,[rax+0x10] ; 0x66aac07  mov rax,[rax+0x10] | indirect-call target from global |
| rcx+0x20 | 16 | R | 0x66aa7dc  movups xmm0,[rcx+0x20] ; 0x66aa7f1  movups xmm0,[rcx+0x20] | 16 bytes copied to [r14+0x15C] |
| rcx+0x38 | 16 | R | 0x66aa87a  movups xmm0,[rcx+0x38] | 16 bytes copied to [r14+0x174] |
| rcx+0x48 | 8 | R | 0x66aa86f  mov rax,[rcx+0x48] | qword copied to [r14+0x184] |
| rdx+0x0 | 16 | W | 0x66aa94e  mov [rdx],ax ; 0x66aab84  movups [rdx],xmm0 | word then 16-byte store at destination cursor |
| rdx+0x10 | 4 | W | 0x66aab7d  mov [rdx+0x10],eax | dword [r14+0x10] |
| rdx+0x14 | 1 | W | 0x66aab8e  mov [rdx+0x14],al | byte [rbp+0x1C8] |
| rdx+0x18 | 4 | W | 0x66aab99  movss [rdx+0x18],xmm0 | float [rbp+0x1CC] |
| rdx+0x1C | 4 | W | 0x66aaba6  movss [rdx+0x1C],xmm0 | float [rbp+0x1D0] |
| rdx+0x20 | 4 | W | 0x66aabb3  movss [rdx+0x20],xmm0 | float [rbp+0x1D4] |
| rdx+0x24 | 4 | W | 0x66aabc0  movss [rdx+0x24],xmm0 | float [rbp+0x1D8] |
| rdx+0x28 | 16 | W | 0x66aabd4  movups [rdx+0x28],xmm0 | 16 bytes [r14+0x28] |
| rdx+0x38 | 16 | W | 0x66aabd8  movups [rdx+0x38],xmm1 | 16 bytes [r14+0x38] |
| rdx+0x47 | 16 | W | 0x66aabdc  movups [rdx+0x47],xmm2 | 16 bytes [r14+0x47] |
| r14+0x0 | 16 | R | 0x66aab80  movups xmm0,[r14] | 16 bytes copied to [rdx] |
| r14+0x10 | 4 | R | 0x66aab79  mov eax,[r14+0x10] | dword stored to [rdx+0x10] |
| r14+0x28 | 16 | R | 0x66aabc5  movups xmm0,[r14+0x28] | - |
| r14+0x38 | 16 | R | 0x66aabca  movups xmm1,[r14+0x38] | - |
| r14+0x47 | 16 | R | 0x66aabcf  movups xmm2,[r14+0x47] | - |
| r14+0x15C | 16 | W | 0x66aa7e0  movups [r14+0x15C],xmm0 ; 0x66aa7f5  movups [r14+0x15C],xmm0 ; 0x66aa802  movups [r14+0x15C],xmm6 ; 0x66aa823  movups [r14+0x15C],xmm6 | copied from [rcx+0x20] or zeroed by xmm6 |
| r14+0x174 | 16 | W | 0x66aa87e  movups [r14+0x174],xmm0 | 16 bytes [rcx+0x38] |
| r14+0x184 | 8 | W | 0x66aa873  mov [r14+0x184],rax | qword [rcx+0x48] |
| rax+0x0 | 16 | W | 0x66aa8da  movups [rax],xmm6 | zeroed block at [rbp+0xD8] |
| rax+0x10 | 16 | R/W | 0x66aa8d6  movups [rax+0x10],xmm6 ; 0x66aa924  mov rax,[rax+0x10] ; 0x66aa9ac  mov rax,[rax+0x10] ; 0x66aa9dc  mov rax,[rax+0x10] ; 0x66aaa16  mov rax,[rax+0x10] ; 0x66aaa9a  mov rax,[rax+0x10] ; 0x66aab25  mov rax,[rax+0x10] ; 0x66aac07  mov rax,[rax+0x10] | zeroed then used as global->[0x10] load source |
| rax+0x20 | 16 | W | 0x66aa8d2  movups [rax+0x20],xmm6 | zeroed block |
| rax+0x30 | 16 | W | 0x66aa8ce  movups [rax+0x30],xmm6 | zeroed block |
| rax+0x40 | 16 | W | 0x66aa8ca  movups [rax+0x40],xmm6 | zeroed block |
| rax+0x50 | 16 | W | 0x66aa8c6  movups [rax+0x50],xmm6 | zeroed block |
| rax+0x60 | 16 | W | 0x66aa8c2  movups [rax+0x60],xmm6 | zeroed block |
| rax+0x70 | 16 | W | 0x66aa8be  movups [rax+0x70],xmm6 | zeroed block |
| rax+0x80 | 16 | W | 0x66aa8b7  movups [rax+0x80],xmm6 | zeroed block |
| rax+0x90 | 16 | W | 0x66aa8b0  movups [rax+0x90],xmm6 | zeroed block |
| rax+0xA0 | 16 | W | 0x66aa8a9  movups [rax+0xA0],xmm6 | zeroed block |
| rax+0xB0 | 16 | W | 0x66aa8a2  movups [rax+0xB0],xmm6 | zeroed block |
| r15+0x10 | 8 | R | 0x66aa886  mov rcx,[r15+0x10] | base for sub_5aba5c0 argument |
| rsi+0x0 | 8 | W | 0x66aaa3f  mov [rsi],rax | qword [rbp+0x210] |
| rsi+0x80 | 8 | W | 0x66aaa5a  mov [rsi+0x80],rax | qword [rbp+0x290] |

## Notes
- Pure LEA address computations ([rbp+0x2E8], [rbp+0x3A8], [rbp+0x3B0], [rbp+0xD8], [rbp+0x218], [rbp+0x298], [rbx+0x780], [rbx+0x8A0], [rbx+0x648], [rbx+0x768], [rbx+0x858], [rsi+8]) compute addresses but do not load/store the field value, so they are excluded from the load/store table; they appear in the phase descriptions. [rbp+0x3A8], [rbx+0x780], [rbx+0x8A0], [rbx+0x648], [rbx+0x768], [rbx+0x858] are also loaded/stored elsewhere and are included above.
- [rdx+rax*4] at 0x66aa7b9 (movsxd) is an indexed jump-table load, not a [reg+off] field; described in Phase 1 only.
- The repeated idiom `mov rcx,[0x1233E1B0]; mov rax,[rcx]; mov rax,[rax+0x10]; mov dl,0x4A; call qword ptr [0xF99FFA0]` (sub_eea6040 via IAT slot) reads the global pointer's [0x10] field each time; stored result byte goes to [rbp+0x437].
