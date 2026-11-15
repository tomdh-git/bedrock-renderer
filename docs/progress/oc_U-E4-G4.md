# U-E4-G4: Chunk builder at 0x670e955 — continuation of U-E4-G3

Unit: U-E4-G4
Function: sub_670e955 (chunk builder) — continuation
RVAs: 0x670e955 .. 0x670f92b (800 instructions)
Source: `rdis dis 0x670e955 800` on Minecraft.Windows.exe 1.26.62.01
Sibling: docs/progress/oc_U-E4-G3.md (sub_670b6e0)
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Resume at 0x670f92b (after `mov rax,[rcx]` = phase 27's last instr, TLS #2 setup). Phases 1-27 (800 instructions, 0x670e955..0x670f92b) written below.

---

## Phase 1 — preamble + item write + grow loc_670edb4 + count [rbp+0x422]/[rbp+0x408] + TLS + item-slot write + bump [r12+0x770] (0x670e955..0x670ea62)

```
0x670e955  mov [rbp+0x848],al                            
0x670e95b  lea rcx,[r12+0x648]                           
0x670e963  lea rdx,[rbp+0x6B8]                           
0x670e96a  call 0x675FB30                       ; -> sub_675fb30
0x670e96f  nop                                           
0x670e970  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e977  mov rax,[rcx]                                 
0x670e97a  mov rax,[rax+0x10]                            
0x670e97e  movzx edx,byte ptr [rbp+0x848]                
0x670e985  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e98b  nop                                           
0x670e98c  mov eax,[r12+0x650]                           
0x670e994  sub eax,[r12+0x648]                           
0x670e99c  shr eax,3                                     
0x670e99f  imul eax,0xFFFF8E39                           
0x670e9a5  dec eax                                       
0x670e9a7  mov [rbp+0x422],ax                            
0x670e9ae  lea rcx,[r12+0x780]                           
0x670e9b6  lea rdx,[rbp+0x660]                           
0x670e9bd  call 0x675F3B0                       ; -> sub_675f3b0
0x670e9c2  nop                                           
0x670e9c3  mov qword ptr [rbp+0x3E0],0xA005009           
0x670e9ce  mov eax,[r12+0x788]                           
0x670e9d6  sub eax,[r12+0x780]                           
0x670e9de  shr eax,3                                     
0x670e9e1  imul eax,0xFFFF8BA3                           
0x670e9e7  dec eax                                       
0x670e9e9  mov [rbp+0x408],ax                            
0x670e9f0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e9f7  mov rax,[rcx]                                 
0x670e9fa  mov rax,[rax+0x10]                            
0x670e9fe  mov dl,0x4A                                   
0x670ea00  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ea06  mov [rbp+0x848],al                            
0x670ea0c  mov rsi,[r12+0x770]                           
0x670ea14  cmp rsi,[r12+0x778]                           
0x670ea1c  je 0x670EDB4                                  ; -> loc_670edb4
0x670ea22  mov rax,[rbp+0x5D8]                           
0x670ea29  mov [rsi],rax                                 
0x670ea2c  lea rcx,[rsi+8]                               
0x670ea30  lea rdx,[rbp+0x5E0]                           
0x670ea37  call 0xE869FF0                       ; -> sub_e869ff0
0x670ea3c  nop                                           
0x670ea3d  mov rax,[rbp+0x658]                           
0x670ea44  mov [rsi+0x80],rax                            
0x670ea4b  mov qword ptr [rbp+0x658],0                   
0x670ea56  add qword ptr [r12+0x770],0x88                
0x670ea62  jmp 0x670EDCC                                 ; -> loc_670edcc
```

Interpretation: mov [rbp+0x848]=al (TLS #2 store continuing from previous unit). lea rcx,[r12+0x648]; lea rdx,[rbp+0x6B8]; call 0x675FB30; nop. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]. eax=[r12+0x650]-[r12+0x648]; shr eax,3; imul eax,0xFFFF8E39; dec eax; [rbp+0x422]=ax. lea rcx,[r12+0x780]; lea rdx,[rbp+0x660]; call 0x675F3B0; nop. [rbp+0x3E0]=0xA005009. eax=[r12+0x788]-[r12+0x780]; shr eax,3; imul eax,0xFFFF8BA3; dec eax; [rbp+0x408]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rsi=[r12+0x770]; cmp [r12+0x778]; if equal → loc_670edb4 (grow). Otherwise rax=[rbp+0x5D8]; [rsi]=rax; rcx=[rsi+8]; rdx=&[rbp+0x5E0]; call 0xE869FF0. rax=[rbp+0x658]; [rsi+0x80]=rax; [rbp+0x658]=0; [r12+0x770]+=0x88; jmp loc_670edcc.

Callees: 0x675FB30 (sub_675fb30), [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675F3B0 (sub_675f3b0), 0xE869FF0 (sub_e869ff0).
Fields read: [rbp+0x848], [r12+0x648], [rbp+0x6B8], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x650], [r12+0x648], [rbp+0x422], [r12+0x780], [rbp+0x660], [rbp+0x3E0], [r12+0x788], [r12+0x780], [rbp+0x408], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x770], [r12+0x778], [rbp+0x5D8], [rsi], [rbp+0x658], [r12+0x770]. Fields written: [rbp+0x848], [rbp+0x422], [rbp+0x660], [rbp+0x3E0], [rbp+0x408], [rbp+0x848], [rsi], [rsi+0x80], [rbp+0x658], [r12+0x770].
Matches F2 Phase? New idiom: [rbp+0x3E0]=0xA005009 + call 0x675FB30 + call 0x675F3B0 + count magic 0xFFFF8E39/0xFFFF8BA3. No exact F2 counterpart.

---

## Phase 2 — grow loc_670ea67 + TLS + count [rbp+0x40A] + cursor/end [r15+0x68]/[r15+0x70] + grow loc_670ee71 + not-eax count + bump [r15+0x68] (0x670ea67..0x670eaf7)

```
0x670ea67  lea rcx,[r15+0x768]                           
0x670ea6e  mov rdx,rsi                                   
0x670ea71  lea r8,[rbp+0x588]                            
0x670ea78  call 0x6760710                       ; -> sub_6760710
0x670ea7d  nop                                           
0x670ea7e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ea85  mov rax,[rcx]                                 
0x670ea88  mov rax,[rax+0x10]                            
0x670ea8c  movzx edx,byte ptr [rbp+0x848]                
0x670ea93  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ea99  nop                                           
0x670ea9a  mov qword ptr [rbp+0x3E0],0xA007009           
0x670eaa5  mov eax,[r15+0x770]                           
0x670eaac  sub eax,[r15+0x768]                           
0x670eab3  shr eax,3                                     
0x670eab6  imul eax,0xFFFFF0F1                           
0x670eabc  dec eax                                       
0x670eabe  mov [rbp+0x40A],ax                            
0x670eac5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670eacc  mov rax,[rcx]                                 
0x670eacf  mov rax,[rax+0x10]                            
0x670ead3  mov dl,0x4A                                   
0x670ead5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670eadb  nop                                           
0x670eadc  mov [rbp+0x848],al                            
0x670eae2  mov rdx,[r15+0x68]                            
0x670eae6  cmp rdx,[r15+0x70]                            
0x670eaea  je 0x670EE71                                  ; -> loc_670ee71
0x670eaf0  inc rdx                                       
0x670eaf3  mov [r15+0x68],rdx                            
0x670eaf7  jmp 0x670EE7E                                 ; -> loc_670ee7e
```

Interpretation: Grow loc_670ea67: lea rcx,[r15+0x768]; mov rdx,rsi; lea r8,[rbp+0x588]; call 0x6760710; nop. loc_670ea7e: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x848]=al. [rbp+0x3E0]=0xA007009. eax=[r15+0x770]-[r15+0x768]; shr eax,3; imul eax,0xFFFFF0F1; dec eax; [rbp+0x40A]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x68]; cmp [r15+0x70]; if equal → loc_670ee71 (grow). Otherwise inc rdx; [r15+0x68]=rdx; jmp loc_670ee7e.

Callees: 0x6760710 (sub_6760710), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x768], [rsi], [rbp+0x588], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r15+0x770], [r15+0x768], [rbp+0x40A], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x68], [r15+0x70]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x40A], [rbp+0x848], [r15+0x68].
Matches F2 Phase? Same grow/TLS/count/0x6760710 idiom as Phase 1's grow path. The `[rbp+0x3E0]=0xA007009` store is new. No exact F2 counterpart.

---

## Phase 3 — grow loc_670eafc + TLS + count [rbp+0x40A] + cursor/end [r15+0x818]/[r15+0x820] + grow loc_670eb9a + count + TLS + movss write (0x670eafc..0x670ec4c)

```
0x670eafc  lea rcx,[r15+0x768]                           
0x670eb03  mov rdx,rsi                                   
0x670eb06  lea r8,[rbp+0x590]                            
0x670eb0d  call 0x6760710                       ; -> sub_6760710
0x670eb12  nop                                           
0x670eb13  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670eb1a  mov rax,[rcx]                                 
0x670eb1d  mov rax,[rax+0x10]                            
0x670eb21  movzx edx,byte ptr [rbp+0x848]                
0x670eb28  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670eb2e  nop                                           
0x670eb2f  mov qword ptr [rbp+0x3E0],0xA007009           
0x670eb3a  mov eax,[r15+0x770]                           
0x670eb41  sub eax,[r15+0x768]                           
0x670eb48  shr eax,3                                     
0x670eb4b  imul eax,0xFFFFF0F1                           
0x670eb51  dec eax                                       
0x670eb53  mov [rbp+0x40A],ax                            
0x670eb5a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670eb61  mov rax,[rcx]                                 
0x670eb64  mov rax,[rax+0x10]                            
0x670eb68  mov dl,0x4A                                   
0x670eb6a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670eb70  nop                                           
0x670eb71  mov [rbp+0x848],al                            
0x670eb77  mov rdx,[r15+0x818]                           
0x670eb7e  cmp rdx,[r15+0x820]                           
0x670eb85  je 0x670EEFF                                  ; -> loc_670eeff
0x670eb8b  inc rdx                                       
0x670eb8e  mov [r15+0x818],rdx                           
0x670eb95  jmp 0x670EF0C                                 ; -> loc_670ef0c
0x670eb9a  lea rcx,[r15+0x768]                           
0x670eba1  mov rdx,rsi                                   
0x670eba4  lea r8,[rbp+0x590]                            
0x670ebab  call 0x6760710                       ; -> sub_6760710
0x670ebb0  nop                                           
0x670ebb1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ebb8  mov rax,[rcx]                                 
0x670ebbb  mov rax,[rax+0x10]                            
0x670ebbf  movzx edx,byte ptr [rbp+0x848]                
0x670ebc6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ebcc  nop                                           
0x670ebcd  mov eax,[r15+0x770]                           
0x670ebd4  sub eax,[r15+0x768]                           
0x670ebdb  shr eax,3                                     
0x670ebde  imul eax,0xFFFFF0F1                           
0x670ebe4  dec eax                                       
0x670ebe6  mov [rbp+0x40A],ax                            
0x670ebed  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ebf4  mov rax,[rcx]                                 
0x670ebf7  mov rax,[rax+0x10]                            
0x670ebfb  mov dl,0x4A                                   
0x670ebfd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ec03  nop                                           
0x670ec04  mov [rbp+0x848],al                            
0x670ec0a  mov rdx,[r15+0x680]                           
0x670ec11  cmp rdx,[r15+0x688]                           
0x670ec18  je 0x670EF7F                                  ; -> loc_670ef7f
0x670ec1e  movss xmm0,[rbp+0x584]                        
0x670ec26  movss [rdx],xmm0                              
0x670ec2a  movss xmm0,[rbp+0x588]                        
0x670ec32  movss [rdx+4],xmm0                            
0x670ec37  movss xmm0,[rbp+0x58C]                        
0x670ec3f  movss [rdx+8],xmm0                            
0x670ec44  add qword ptr [r15+0x680],0xC                 
0x670ec4c  jmp 0x670EF93                                 ; -> loc_670ef93
```

Interpretation: Grow loc_670eafc: lea rcx,[r15+0x768]; mov rdx,rsi; lea r8,[rbp+0x590]; call 0x6760710; nop. loc_670ebb1: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E0]=0xA007009; eax=[r15+0x770]-[r15+0x768]; shr eax,3; imul eax,0xFFFFF0F1; dec eax; [rbp+0x40A]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x818]; cmp [r15+0x820]; if equal → loc_670eeff (grow). Otherwise inc rdx; [r15+0x818]=rdx; jmp loc_670ef0c. Grow loc_670eb9a: lea rcx,[r15+0x768]; mov rdx,rsi; lea r8,[rbp+0x590]; call 0x6760710; nop. loc_670ebcd: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; eax=[r15+0x770]-[r15+0x768]; shr eax,3; imul eax,0xFFFFF0F1; dec eax; [rbp+0x40A]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x680]; cmp [r15+0x688]; if equal → loc_670ef7f (grow). Otherwise movss xmm0,[rbp+0x584]→[rdx]; [rbp+0x588]→[rdx+4]; [rbp+0x58C]→[rdx+8]; [r15+0x680]+=0xC; jmp loc_670ef93.

Callees: 0x6760710 (sub_6760710, twice), [0xF99FFA0] = sub_eea6040 (indirect, four times).
Fields read: [r15+0x768], [rsi], [rbp+0x590], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r15+0x770], [r15+0x768], [rbp+0x40A], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x818], [r15+0x820], [r15+0x768], [rsi], [rbp+0x590], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x770], [r15+0x768], [rbp+0x40A], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x680], [r15+0x688], [rbp+0x584], [rbp+0x588], [rbp+0x58C], [r15+0x680]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x40A], [rbp+0x848], [r15+0x818], [rbp+0x848], [rbp+0x40A], [rbp+0x848], [rdx], [rdx+4], [rdx+8], [r15+0x680].
Matches F2 Phase? Same grow/TLS/count/0x6760710 idiom. The `[rbp+0x3E0]=0xA007009` store is new. No exact F2 counterpart.

---

## Phase 4 — grow loc_670ec51 + TLS + count [rbp+0x40A] + cursor/end [r15+0x680]/[r15+0x688] + movss write + bump (0x670ec51..0x670ed03)

```
0x670ec51  lea rcx,[r15+0x768]                           
0x670ec58  mov rdx,rsi                                   
0x670ec5b  lea r8,[rbp+0x5A0]                            
0x670ec62  call 0x6760710                       ; -> sub_6760710
0x670ec67  nop                                           
0x670ec68  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ec6f  mov rax,[rcx]                                 
0x670ec72  mov rax,[rax+0x10]                            
0x670ec76  movzx edx,byte ptr [rbp+0x848]                
0x670ec7d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ec83  nop                                           
0x670ec84  mov eax,[r15+0x770]                           
0x670ec8b  sub eax,[r15+0x768]                           
0x670ec92  shr eax,3                                     
0x670ec95  imul eax,0xFFFFF0F1                           
0x670ec9b  dec eax                                       
0x670ec9d  mov [rbp+0x40A],ax                            
0x670eca4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ecab  mov rax,[rcx]                                 
0x670ecae  mov rax,[rax+0x10]                            
0x670ecb2  mov dl,0x4A                                   
0x670ecb4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ecba  nop                                           
0x670ecbb  mov [rbp+0x848],al                            
0x670ecc1  mov rdx,[r15+0x680]                           
0x670ecc8  cmp rdx,[r15+0x688]                           
0x670eccf  je 0x670F011                                  ; -> loc_670f011
0x670ecd5  movss xmm0,[rbp+0x590]                        
0x670ecdd  movss [rdx],xmm0                              
0x670ece1  movss xmm0,[rbp+0x594]                        
0x670ece9  movss [rdx+4],xmm0                            
0x670ecee  movss xmm0,[rbp+0x598]                        
0x670ecf6  movss [rdx+8],xmm0                            
0x670ecfb  add qword ptr [r15+0x680],0xC                 
0x670ed03  jmp 0x670F025                                 ; -> loc_670f025
```

Interpretation: Grow loc_670ec51: lea rcx,[r15+0x768]; mov rdx,rsi; lea r8,[rbp+0x5A0]; call 0x6760710; nop. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r15+0x770]-[r15+0x768]; shr eax,3; imul eax,0xFFFFF0F1; dec eax; [rbp+0x40A]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x680]; cmp [r15+0x688]; if equal → loc_670f011 (grow). Otherwise movss xmm0,[rbp+0x590]→[rdx]; [rbp+0x594]→[rdx+4]; [rbp+0x598]→[rdx+8]; [r15+0x680]+=0xC; jmp loc_670f025.

Callees: 0x6760710 (sub_6760710), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x768], [rsi], [rbp+0x5A0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x770], [r15+0x768], [rbp+0x40A], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x680], [r15+0x688], [rbp+0x590], [rbp+0x594], [rbp+0x598], [r15+0x680]. Fields written: [rbp+0x848], [rbp+0x40A], [rbp+0x848], [rdx], [rdx+4], [rdx+8], [r15+0x680].
Matches F2 Phase? Same grow/TLS/count/0x6760710 idiom. No exact F2 counterpart.

---

## Phase 5 — grow loc_670ed08 + TLS + count [rbp+0x40A] + cursor/end [r12+0x698]/[r12+0x6A0] + word write + bump +2 (0x670ed08..0x670edaf)

```
0x670ed08  lea rcx,[r12+0x768]                           
0x670ed10  mov rdx,rsi                                   
0x670ed13  lea r8,[rbp+0x5C8]                            
0x670ed1a  call 0x6760710                       ; -> sub_6760710
0x670ed1f  nop                                           
0x670ed20  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ed27  mov rax,[rcx]                                 
0x670ed2a  mov rax,[rax+0x10]                            
0x670ed2e  movzx edx,byte ptr [rbp+0x848]                
0x670ed35  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ed3b  nop                                           
0x670ed3c  mov qword ptr [rbp+0x3E0],0xA007009           
0x670ed47  mov eax,[r12+0x770]                           
0x670ed4f  sub eax,[r12+0x768]                           
0x670ed57  shr eax,3                                     
0x670ed5a  imul eax,0xFFFFF0F1                           
0x670ed60  dec eax                                       
0x670ed62  mov [rbp+0x40A],ax                            
0x670ed69  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ed70  mov rax,[rcx]                                 
0x670ed73  mov rax,[rax+0x10]                            
0x670ed77  mov dl,0x4A                                   
0x670ed79  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ed7f  nop                                           
0x670ed80  mov [rbp+0x848],al                            
0x670ed86  mov rdx,[r12+0x698]                           
0x670ed8e  cmp rdx,[r12+0x6A0]                           
0x670ed96  je 0x670F0AC                                  ; -> loc_670f0ac
0x670ed9c  movzx eax,word ptr [rbp+0x5C0]                
0x670eda3  mov [rdx],ax                                  
0x670eda6  add qword ptr [r12+0x698],2                   
0x670edaf  jmp 0x670F0C1                                 ; -> loc_670f0c1
```

Interpretation: Grow loc_670ed08: lea rcx,[r12+0x768]; mov rdx,rsi; lea r8,[rbp+0x5C8]; call 0x6760710; nop. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E0]=0xA007009; eax=[r12+0x770]-[r12+0x768]; shr eax,3; imul eax,0xFFFFF0F1; dec eax; [rbp+0x40A]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x698]; cmp [r12+0x6A0]; if equal → loc_670f0ac (grow). Otherwise movzx eax,word ptr [rbp+0x5C0]; [rdx]=ax; [r12+0x698]+=2; jmp loc_670f0c1.

Callees: 0x6760710 (sub_6760710), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r12+0x768], [rsi], [rbp+0x5C8], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r12+0x770], [r12+0x768], [rbp+0x40A], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x698], [r12+0x6A0], [rbp+0x5C0], [r12+0x698]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x40A], [rbp+0x848], [rdx], [r12+0x698].
Matches F2 Phase? Same grow/TLS/count/0x6760710 idiom. The `[rbp+0x3E0]=0xA007009` store is new. No exact F2 counterpart.

---

## Phase 6 — grow loc_670edb4 + TLS + count [rbp+0x40A] + cursor/end [r12+0x680]/[r12+0x688] + movss write + bump (0x670edb4..0x670ee6c)

```
0x670edb4  lea rcx,[r12+0x768]                           
0x670edbc  mov rdx,rsi                                   
0x670edbf  lea r8,[rbp+0x5D8]                            
0x670edc6  call 0x6760710                       ; -> sub_6760710
0x670edcb  nop                                           
0x670edcc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670edd3  mov rax,[rcx]                                 
0x670edd6  mov rax,[rax+0x10]                            
0x670edda  movzx edx,byte ptr [rbp+0x848]                
0x670ede1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ede7  nop                                           
0x670ede8  mov eax,[r12+0x770]                           
0x670edf0  sub eax,[r12+0x768]                           
0x670edf8  shr eax,3                                     
0x670edfb  imul eax,0xFFFFF0F1                           
0x670ee01  dec eax                                       
0x670ee03  mov [rbp+0x40A],ax                            
0x670ee0a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ee11  mov rax,[rcx]                                 
0x670ee14  mov rax,[rax+0x10]                            
0x670ee18  mov dl,0x4A                                   
0x670ee1a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ee20  nop                                           
0x670ee21  mov [rbp+0x848],al                            
0x670ee27  mov rdx,[r12+0x680]                           
0x670ee2f  cmp rdx,[r12+0x688]                           
0x670ee37  je 0x670F141                                  ; -> loc_670f141
0x670ee3d  movss xmm0,[rbp+0x5C8]                        
0x670ee45  movss [rdx],xmm0                              
0x670ee49  movss xmm0,[rbp+0x5CC]                        
0x670ee51  movss [rdx+4],xmm0                            
0x670ee56  movss xmm0,[rbp+0x5D0]                        
0x670ee5e  movss [rdx+8],xmm0                            
0x670ee63  add qword ptr [r12+0x680],0xC                 
0x670ee6c  jmp 0x670F156                                 ; -> loc_670f156
```

Interpretation: Grow loc_670edb4: lea rcx,[r12+0x768]; mov rdx,rsi; lea r8,[rbp+0x5D8]; call 0x6760710; nop. loc_670edcc: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r12+0x770]-[r12+0x768]; shr eax,3; imul eax,0xFFFFF0F1; dec eax; [rbp+0x40A]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x680]; cmp [r12+0x688]; if equal → loc_670f141 (grow). Otherwise movss xmm0,[rbp+0x5C8]→[rdx]; [rbp+0x5CC]→[rdx+4]; [rbp+0x5D0]→[rdx+8]; [r12+0x680]+=0xC; jmp loc_670f156.

Callees: 0x6760710 (sub_6760710), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r12+0x768], [rsi], [rbp+0x5D8], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x770], [r12+0x768], [rbp+0x40A], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x680], [r12+0x688], [rbp+0x5C8], [rbp+0x5CC], [rbp+0x5D0], [r12+0x680]. Fields written: [rbp+0x848], [rbp+0x40A], [rbp+0x848], [rdx], [rdx+4], [rdx+8], [r12+0x680].
Matches F2 Phase? Same grow/TLS/count/0x6760710 idiom. No exact F2 counterpart.

---

## Phase 7 — grow loc_670ee71 + [rbp+0x3E8]=0x1000000 + not-eax count [rbp+0x4A0] + TLS + grow path [r15+8]/[r15+0x10] + call 0xEEC6EC0 + bump 0xC8 (0x670ee71..0x670eefa)

```
0x670ee71  mov rcx,r15                                   
0x670ee74  add rcx,0x60                                  
0x670ee78  call 0x6760E60                       ; -> sub_6760e60
0x670ee7d  nop                                           
0x670ee7e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ee85  mov rax,[rcx]                                 
0x670ee88  mov rax,[rax+0x10]                            
0x670ee8c  movzx edx,byte ptr [rbp+0x848]                
0x670ee93  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ee99  nop                                           
0x670ee9a  mov qword ptr [rbp+0x3E8],0x1000000           
0x670eea5  mov eax,[r15+0x60]                            
0x670eea9  not eax                                       
0x670eeab  add eax,[r15+0x68]                            
0x670eeaf  mov [rbp+0x4A0],ax                            
0x670eeb6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670eebd  mov rax,[rcx]                                 
0x670eec0  mov rax,[rax+0x10]                            
0x670eec4  mov dl,0x4A                                   
0x670eec6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670eecc  nop                                           
0x670eecd  mov [rbp+0x848],al                            
0x670eed3  mov rdx,[r15+8]                               
0x670eed7  cmp rdx,[r15+0x10]                            
0x670eedb  je 0x670F1EA                                  ; -> loc_670f1ea
0x670eee1  mov r8d,0xC8                                  
0x670eee7  mov rcx,rdx                                   
0x670eeea  mov rdx,r12                                   
0x670eeed  call 0xEEC6EC0                       ; -> sub_eec6ec0
0x670eef2  add qword ptr [r15+8],0xC8                    
0x670eefa  jmp 0x670F1F6                                 ; -> loc_670f1f6
```

Interpretation: Grow loc_670ee71: mov rcx,r15; add rcx,0x60; call 0x6760E60; nop. loc_670ee7e: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E8]=0x1000000. eax=[r15+0x60]; not eax; add eax,[r15+0x68]; [rbp+0x4A0]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+8]; cmp [r15+0x10]; if equal → loc_670f1ea (grow). Otherwise r8d=0xC8; rcx=rdx; rdx=r12; call 0xEEC6EC0; [r15+8]+=0xC8; jmp loc_670f1f6.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [r15], [r15+0x60], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E8], [r15+0x60], [r15+0x68], [rbp+0x4A0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+8], [r15+0x10], [rdx], [r12], [r15+8]. Fields written: [rbp+0x848], [rbp+0x3E8], [rbp+0x4A0], [rbp+0x848], [r15+8].
Matches F2 Phase? New idiom: `not eax` (not `not eax; add`) with [r15+0x60]/[r15+0x68] → [rbp+0x4A0] + `[rbp+0x3E8]=0x1000000` + call 0xEEC6EC0 + bump 0xC8. No exact F2 counterpart.

---

## Phase 8 — grow loc_670eeff + not-eax count [rbp+0x3FC] + TLS + cursor/end [r15+0x368]/[r15+0x370] + bump [r15+0x368] (0x670eeff..0x670ef7a)

```
0x670eeff  lea rcx,[r15+0x810]                           
0x670ef06  call 0x6760E60                       ; -> sub_6760e60
0x670ef0b  nop                                           
0x670ef0c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ef13  mov rax,[rcx]                                 
0x670ef16  mov rax,[rax+0x10]                            
0x670ef1a  movzx edx,byte ptr [rbp+0x848]                
0x670ef21  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ef27  nop                                           
0x670ef28  mov eax,[r15+0x810]                           
0x670ef2f  not eax                                       
0x670ef31  add eax,[r15+0x818]                           
0x670ef38  mov [rbp+0x3FC],ax                            
0x670ef3f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ef46  mov rax,[rcx]                                 
0x670ef49  mov rax,[rax+0x10]                            
0x670ef4d  mov dl,0x4A                                   
0x670ef4f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ef55  nop                                           
0x670ef56  mov [rbp+0x848],al                            
0x670ef5c  mov rdx,[r15+0x368]                           
0x670ef63  cmp rdx,[r15+0x370]                           
0x670ef6a  je 0x670F226                                  ; -> loc_670f226
0x670ef70  inc rdx                                       
0x670ef73  mov [r15+0x368],rdx                           
0x670ef7a  jmp 0x670F233                                 ; -> loc_670f233
```

Interpretation: Grow loc_670eeff: lea rcx,[r15+0x810]; call 0x6760E60; nop. loc_670ef0c: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r15+0x810]; not eax; add eax,[r15+0x818]; [rbp+0x3FC]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x368]; cmp [r15+0x370]; if equal → loc_670f226 (grow). Otherwise inc rdx; [r15+0x368]=rdx; jmp loc_670f233.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x810], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x810], [r15+0x818], [rbp+0x3FC], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x368], [r15+0x370]. Fields written: [rbp+0x848], [rbp+0x3FC], [rbp+0x848], [r15+0x368].
Matches F2 Phase? Same grow/not-eax-count/TLS/bump idiom. No exact F2 counterpart.

---

## Phase 9 — grow loc_670ef7f + [rbp+0x3E0]=0xA807009 + count [rbp+0x41E] + TLS + cursor/end [r15+0x68]/[r15+0x70] + bump [r15+0x68] (0x670ef7f..0x670f00c)

```
0x670ef7f  lea rcx,[r15+0x678]                           
0x670ef86  lea r8,[rbp+0x584]                            
0x670ef8d  call 0x1770A70                       ; -> sub_1770a70
0x670ef92  nop                                           
0x670ef93  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ef9a  mov rax,[rcx]                                 
0x670ef9d  mov rax,[rax+0x10]                            
0x670efa1  movzx edx,byte ptr [rbp+0x848]                
0x670efa8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670efae  nop                                           
0x670efaf  mov qword ptr [rbp+0x3E0],0xA807009           
0x670efba  mov eax,[r15+0x680]                           
0x670efc1  sub eax,[r15+0x678]                           
0x670efc8  shr eax,2                                     
0x670efcb  imul eax,0xFFFFAAAB                           
0x670efd1  dec eax                                       
0x670efd3  mov [rbp+0x41E],ax                            
0x670efda  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670efe1  mov rax,[rcx]                                 
0x670efe4  mov rax,[rax+0x10]                            
0x670efe8  mov dl,0x4A                                   
0x670efea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670eff0  nop                                           
0x670eff1  mov [rbp+0x848],al                            
0x670eff7  mov rdx,[r15+0x68]                            
0x670effb  cmp rdx,[r15+0x70]                            
0x670efff  je 0x670F2BF                                  ; -> loc_670f2bf
0x670f005  inc rdx                                       
0x670f008  mov [r15+0x68],rdx                            
0x670f00c  jmp 0x670F2CC                                 ; -> loc_670f2cc
```

Interpretation: Grow loc_670ef7f: lea rcx,[r15+0x678]; lea r8,[rbp+0x584]; call 0x1770A70; nop. loc_670ef93: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E0]=0xA807009; eax=[r15+0x680]-[r15+0x678]; shr eax,2; imul eax,0xFFFFAAAB; dec eax; [rbp+0x41E]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x68]; cmp [r15+0x70]; if equal → loc_670f2bf (grow). Otherwise inc rdx; [r15+0x68]=rdx; jmp loc_670f2cc.

Callees: 0x1770A70 (sub_1770a70), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x678], [rbp+0x584], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r15+0x680], [r15+0x678], [rbp+0x41E], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x68], [r15+0x70]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x41E], [rbp+0x848], [r15+0x68].
Matches F2 Phase? New idiom: shr eax,2 + imul 0xFFFFAAAB + `[rbp+0x3E0]=0xA807009` + count → [rbp+0x41E]. No exact F2 counterpart.

---

## Phase 10 — grow loc_670f011 + [rbp+0x3E0]=0xA807009 + count [rbp+0x41E] + TLS + cursor/end [r15+0x818]/[r15+0x820] + bump [r15+0x818] (0x670f011..0x670f0a7)

```
0x670f011  lea rcx,[r15+0x678]                           
0x670f018  lea r8,[rbp+0x590]                            
0x670f01f  call 0x1770A70                       ; -> sub_1770a70
0x670f024  nop                                           
0x670f025  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f02c  mov rax,[rcx]                                 
0x670f02f  mov rax,[rax+0x10]                            
0x670f033  movzx edx,byte ptr [rbp+0x848]                
0x670f03a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f040  nop                                           
0x670f041  mov qword ptr [rbp+0x3E0],0xA807009           
0x670f04c  mov eax,[r15+0x680]                           
0x670f053  sub eax,[r15+0x678]                           
0x670f05a  shr eax,2                                     
0x670f05d  imul eax,0xFFFFAAAB                           
0x670f063  dec eax                                       
0x670f065  mov [rbp+0x41E],ax                            
0x670f06c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f073  mov rax,[rcx]                                 
0x670f076  mov rax,[rax+0x10]                            
0x670f07a  mov dl,0x4A                                   
0x670f07c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f082  nop                                           
0x670f083  mov [rbp+0x848],al                            
0x670f089  mov rdx,[r15+0x818]                           
0x670f090  cmp rdx,[r15+0x820]                           
0x670f097  je 0x670F34D                                  ; -> loc_670f34d
0x670f09d  inc rdx                                       
0x670f0a0  mov [r15+0x818],rdx                           
0x670f0a7  jmp 0x670F35A                                 ; -> loc_670f35a
```

Interpretation: Grow loc_670f011: lea rcx,[r15+0x678]; lea r8,[rbp+0x590]; call 0x1770A70; nop. loc_670f025: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E0]=0xA807009; eax=[r15+0x680]-[r15+0x678]; shr eax,2; imul eax,0xFFFFAAAB; dec eax; [rbp+0x41E]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x818]; cmp [r15+0x820]; if equal → loc_670f34d (grow). Otherwise inc rdx; [r15+0x818]=rdx; jmp loc_670f35a.

Callees: 0x1770A70 (sub_1770a70), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x678], [rbp+0x590], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r15+0x680], [r15+0x678], [rbp+0x41E], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x818], [r15+0x820]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x41E], [rbp+0x848], [r15+0x818].
Matches F2 Phase? Same shr/imul/count idiom as Phase 9. No exact F2 counterpart.

---

## Phase 11 — grow loc_670f0ac + word count [rbp+0x41C] + TLS + dword write [r12+0x638] + bump +4 (0x670f0ac..0x670f13c)

```
0x670f0ac  lea rcx,[r12+0x690]                           
0x670f0b4  lea r8,[rbp+0x5C0]                            
0x670f0bb  call 0x1EF6F90                       ; -> sub_1ef6f90
0x670f0c0  nop                                           
0x670f0c1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f0c8  mov rax,[rcx]                                 
0x670f0cb  mov rax,[rax+0x10]                            
0x670f0cf  movzx edx,byte ptr [rbp+0x848]                
0x670f0d6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f0dc  nop                                           
0x670f0dd  mov eax,[r12+0x698]                           
0x670f0e5  sub eax,[r12+0x690]                           
0x670f0ed  shr eax,1                                     
0x670f0ef  dec eax                                       
0x670f0f1  mov [rbp+0x41C],ax                            
0x670f0f8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f0ff  mov rax,[rcx]                                 
0x670f102  mov rax,[rax+0x10]                            
0x670f106  mov dl,0x4A                                   
0x670f108  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f10e  nop                                           
0x670f10f  mov [rbp+0x848],al                            
0x670f115  mov rdx,[r12+0x638]                           
0x670f11d  cmp rdx,[r12+0x640]                           
0x670f125  je 0x670F3CD                                  ; -> loc_670f3cd
0x670f12b  mov eax,[rbp+0x5B8]                           
0x670f131  mov [rdx],eax                                 
0x670f133  add qword ptr [r12+0x638],4                   
0x670f13c  jmp 0x670F3E2                                 ; -> loc_670f3e2
```

Interpretation: Grow loc_670f0ac: lea rcx,[r12+0x690]; lea r8,[rbp+0x5C0]; call 0x1EF6F90; nop. loc_670f0c1: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r12+0x698]-[r12+0x690]; shr eax,1; dec eax; [rbp+0x41C]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x638]; cmp [r12+0x640]; if equal → loc_670f3cd (grow). Otherwise eax=[rbp+0x5B8]; [rdx]=eax; [r12+0x638]+=4; jmp loc_670f3e2.

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r12+0x690], [rbp+0x5C0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x698], [r12+0x690], [rbp+0x41C], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x638], [r12+0x640], [rbp+0x5B8], [r12+0x638]. Fields written: [rbp+0x848], [rbp+0x41C], [rbp+0x848], [rdx], [r12+0x638].
Matches F2 Phase? New idiom: shr eax,1 + dec (word count) → [rbp+0x41C] + call 0x1EF6F90 + dword write + bump +4. No exact F2 counterpart.

---

## Phase 12 — grow loc_670f141 + [rbp+0x3E0]=0xA807009 + count [rbp+0x41E] + TLS + word write [r12+0x698] + bump +2 (0x670f141..0x670f1e5)

```
0x670f141  lea rcx,[r12+0x678]                           
0x670f149  lea r8,[rbp+0x5C8]                            
0x670f150  call 0x1770A70                       ; -> sub_1770a70
0x670f155  nop                                           
0x670f156  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f15d  mov rax,[rcx]                                 
0x670f160  mov rax,[rax+0x10]                            
0x670f164  movzx edx,byte ptr [rbp+0x848]                
0x670f16b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f171  nop                                           
0x670f172  mov qword ptr [rbp+0x3E0],0xA807009           
0x670f17d  mov eax,[r12+0x680]                           
0x670f185  sub eax,[r12+0x678]                           
0x670f18d  shr eax,2                                     
0x670f190  imul eax,0xFFFFAAAB                           
0x670f196  dec eax                                       
0x670f198  mov [rbp+0x41E],ax                            
0x670f19f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f1a6  mov rax,[rcx]                                 
0x670f1a9  mov rax,[rax+0x10]                            
0x670f1ad  mov dl,0x4A                                   
0x670f1af  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f1b5  nop                                           
0x670f1b6  mov [rbp+0x848],al                            
0x670f1bc  mov rdx,[r12+0x698]                           
0x670f1c4  cmp rdx,[r12+0x6A0]                           
0x670f1cc  je 0x670F4B5                                  ; -> loc_670f4b5
0x670f1d2  movzx eax,word ptr [rbp+0x5C0]                
0x670f1d9  mov [rdx],ax                                  
0x670f1dc  add qword ptr [r12+0x698],2                   
0x670f1e5  jmp 0x670F4CA                                 ; -> loc_670f4ca
```

Interpretation: Grow loc_670f141: lea rcx,[r12+0x678]; lea r8,[rbp+0x5C8]; call 0x1770A70; nop. loc_670f156: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E0]=0xA807009; eax=[r12+0x680]-[r12+0x678]; shr eax,2; imul eax,0xFFFFAAAB; dec eax; [rbp+0x41E]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x698]; cmp [r12+0x6A0]; if equal → loc_670f4b5 (grow). Otherwise movzx eax,word ptr [rbp+0x5C0]; [rdx]=ax; [r12+0x698]+=2; jmp loc_670f4ca.

Callees: 0x1770A70 (sub_1770a70), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r12+0x678], [rbp+0x5C8], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r12+0x680], [r12+0x678], [rbp+0x41E], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x698], [r12+0x6A0], [rbp+0x5C0], [r12+0x698]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x41E], [rbp+0x848], [rdx], [r12+0x698].
Matches F2 Phase? Same shr/imul/count + word write idiom as Phase 11. No exact F2 counterpart.

---

## Phase 13 — grow loc_670f1ea + call 0x5ABA6D0 + TLS + call 0x67E1840 + jmp sub_67139a0 (0x670f1ea..0x670f221)

```
0x670f1ea  mov rcx,r15                                   
0x670f1ed  mov r8,r12                                    
0x670f1f0  call 0x5ABA6D0                       ; -> sub_5aba6d0
0x670f1f5  nop                                           
0x670f1f6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f1fd  mov rax,[rcx]                                 
0x670f200  mov rax,[rax+0x10]                            
0x670f204  movzx edx,byte ptr [rbp+0x848]                
0x670f20b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f211  nop                                           
0x670f212  mov rcx,r13                                   
0x670f215  call 0x67E1840                       ; -> sub_67e1840
0x670f21a  lea rcx,[rbp+0x120]                           
0x670f221  jmp qword ptr 0x67139A0                        ; -> sub_67139a0
```

Interpretation: Grow loc_670f1ea: mov rcx,r15; mov r8,r12; call 0x5ABA6D0; nop. loc_670f1f6: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]. mov rcx,r13; call 0x67E1840. lea rcx,[rbp+0x120]; jmp sub_67139a0. This phase terminates the branch — control leaves the function via indirect jump.

Callees: 0x5ABA6D0 (sub_5aba6d0), [0xF99FFA0] = sub_eea6040 (indirect), 0x67E1840 (sub_67e1840), sub_67139a0 (indirect jmp target).
Fields read: [r15], [r12], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r13], [rbp+0x120]. Fields written: none new (TLS al result not stored before call).
Matches F2 Phase? New idiom: call 0x5ABA6D0 + TLS + call 0x67E1840 + jmp sub_67139a0. No exact F2 counterpart.

---

## Phase 14 — grow loc_670f226 + mov qword [rbp+0x3E0]=0x10000000A007049 + not-eax count [rbp+0x460] + TLS + word write [r15+0x698] + bump +2 (0x670f226..0x670f2ba)

```
0x670f226  lea rcx,[r15+0x360]                           
0x670f22d  call 0x6760E60                       ; -> sub_6760e60
0x670f232  nop                                           
0x670f233  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f23a  mov rax,[rcx]                                 
0x670f23d  mov rax,[rax+0x10]                            
0x670f241  movzx edx,byte ptr [rbp+0x848]                
0x670f248  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f24e  nop                                           
0x670f24f  mov rax,0x10000000A007049                     
0x670f259  mov [rbp+0x3E0],rax                           
0x670f260  mov eax,[r15+0x360]                           
0x670f267  not eax                                       
0x670f269  add eax,[r15+0x368]                           
0x670f270  mov [rbp+0x460],ax                            
0x670f277  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f27e  mov rax,[rcx]                                 
0x670f281  mov rax,[rax+0x10]                            
0x670f285  mov dl,0x4A                                   
0x670f287  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f28d  nop                                           
0x670f28e  mov [rbp+0x848],al                            
0x670f294  mov rdx,[r15+0x698]                           
0x670f29b  cmp rdx,[r15+0x6A0]                           
0x670f2a2  je 0x670F54A                                  ; -> loc_670f54a
0x670f2a8  movzx eax,word ptr [rbp+0x584]                
0x670f2af  mov [rdx],ax                                  
0x670f2b2  add qword ptr [r15+0x698],2                   
0x670f2ba  jmp 0x670F55E                                 ; -> loc_670f55e
```

Interpretation: Grow loc_670f226: lea rcx,[r15+0x360]; call 0x6760E60; nop. loc_670f233: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]. mov rax,0x10000000A007049; [rbp+0x3E0]=rax. eax=[r15+0x360]; not eax; add eax,[r15+0x368]; [rbp+0x460]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x698]; cmp [r15+0x6A0]; if equal → loc_670f54a (grow). Otherwise movzx eax,word ptr [rbp+0x584]; [rdx]=ax; [r15+0x698]+=2; jmp loc_670f55e.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x360], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r15+0x360], [r15+0x368], [rbp+0x460], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x698], [r15+0x6A0], [rbp+0x584], [r15+0x698]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x460], [rbp+0x848], [rdx], [r15+0x698].
Matches F2 Phase? New idiom: mov rax,imm64 → [rbp+0x3E0] + `not eax; add` with [r15+0x360]/[r15+0x368] → [rbp+0x460]. No exact F2 counterpart.

---

## Phase 15 — grow loc_670f2bf + [rbp+0x3E8]=0x1000000 + not-eax count [rbp+0x4A0] + TLS + grow path [r15+8]/[r15+0x10] + call 0xEEC6EC0 + bump 0xC8 (0x670f2bf..0x670f348)

```
0x670f2bf  mov rcx,r15                                   
0x670f2c2  add rcx,0x60                                  
0x670f2c6  call 0x6760E60                       ; -> sub_6760e60
0x670f2cb  nop                                           
0x670f2cc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f2d3  mov rax,[rcx]                                 
0x670f2d6  mov rax,[rax+0x10]                            
0x670f2da  movzx edx,byte ptr [rbp+0x848]                
0x670f2e1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f2e7  nop                                           
0x670f2e8  mov qword ptr [rbp+0x3E8],0x1000000           
0x670f2f3  mov eax,[r15+0x60]                            
0x670f2f7  not eax                                       
0x670f2f9  add eax,[r15+0x68]                            
0x670f2fd  mov [rbp+0x4A0],ax                            
0x670f304  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f30b  mov rax,[rcx]                                 
0x670f30e  mov rax,[rax+0x10]                            
0x670f312  mov dl,0x4A                                   
0x670f314  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f31a  nop                                           
0x670f31b  mov [rbp+0x848],al                            
0x670f321  mov rdx,[r15+8]                               
0x670f325  cmp rdx,[r15+0x10]                            
0x670f329  je 0x670F5D9                                  ; -> loc_670f5d9
0x670f32f  mov r8d,0xC8                                  
0x670f335  mov rcx,rdx                                   
0x670f338  mov rdx,r12                                   
0x670f33b  call 0xEEC6EC0                       ; -> sub_eec6ec0
0x670f340  add qword ptr [r15+8],0xC8                    
0x670f348  jmp 0x670F5E5                                 ; -> loc_670f5e5
```

Interpretation: Grow loc_670f2bf: mov rcx,r15; add rcx,0x60; call 0x6760E60; nop. loc_670f2cc: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E8]=0x1000000. eax=[r15+0x60]; not eax; add eax,[r15+0x68]; [rbp+0x4A0]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+8]; cmp [r15+0x10]; if equal → loc_670f5d9 (grow). Otherwise r8d=0xC8; rcx=rdx; rdx=r12; call 0xEEC6EC0; [r15+8]+=0xC8; jmp loc_670f5e5.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [r15], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E8], [r15+0x60], [r15+0x68], [rbp+0x4A0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+8], [r15+0x10], [rdx], [r12], [r15+8]. Fields written: [rbp+0x848], [rbp+0x3E8], [rbp+0x4A0], [rbp+0x848], [r15+8].
Matches F2 Phase? Same idiom as Phase 7. No exact F2 counterpart.

---

## Phase 16 — grow loc_670f34d + not-eax count [rbp+0x3FC] + TLS + cursor/end [r15+0x368]/[r15+0x370] + bump [r15+0x368] (0x670f34d..0x670f3c8)

```
0x670f34d  lea rcx,[r15+0x810]                           
0x670f354  call 0x6760E60                       ; -> sub_6760e60
0x670f359  nop                                           
0x670f35a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f361  mov rax,[rcx]                                 
0x670f364  mov rax,[rax+0x10]                            
0x670f368  movzx edx,byte ptr [rbp+0x848]                
0x670f36f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f375  nop                                           
0x670f376  mov eax,[r15+0x810]                           
0x670f37d  not eax                                       
0x670f37f  add eax,[r15+0x818]                           
0x670f386  mov [rbp+0x3FC],ax                            
0x670f38d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f394  mov rax,[rcx]                                 
0x670f397  mov rax,[rax+0x10]                            
0x670f39b  mov dl,0x4A                                   
0x670f39d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f3a3  nop                                           
0x670f3a4  mov [rbp+0x848],al                            
0x670f3aa  mov rdx,[r15+0x368]                           
0x670f3b1  cmp rdx,[r15+0x370]                           
0x670f3b8  je 0x670F60E                                  ; -> loc_670f60e
0x670f3be  inc rdx                                       
0x670f3c1  mov [r15+0x368],rdx                           
0x670f3c8  jmp 0x670F61B                                 ; -> loc_670f61b
```

Interpretation: Grow loc_670f34d: lea rcx,[r15+0x810]; call 0x6760E60; nop. loc_670f35a: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r15+0x810]; not eax; add eax,[r15+0x818]; [rbp+0x3FC]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x368]; cmp [r15+0x370]; if equal → loc_670f60e (grow). Otherwise inc rdx; [r15+0x368]=rdx; jmp loc_670f61b.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x810], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x810], [r15+0x818], [rbp+0x3FC], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x368], [r15+0x370]. Fields written: [rbp+0x848], [rbp+0x3FC], [rbp+0x848], [r15+0x368].
Matches F2 Phase? Same grow/not-eax-count/TLS/bump idiom as Phase 8. No exact F2 counterpart.

---

## Phase 17 — grow loc_670f60e + mov qword [rbp+0x3E0]=0x10000000A807049 + not-eax count [rbp+0x460] + TLS + word write [r15+0x698] + bump +2 (0x670f60e..0x670f6a2)

```
0x670f60e  lea rcx,[r15+0x360]                           
0x670f615  call 0x6760E60                       ; -> sub_6760e60
0x670f61a  nop                                           
0x670f61b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f622  mov rax,[rcx]                                 
0x670f625  mov rax,[rax+0x10]                            
0x670f629  movzx edx,byte ptr [rbp+0x848]                
0x670f630  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f636  nop                                           
0x670f637  mov rax,0x10000000A807049                     
0x670f641  mov [rbp+0x3E0],rax                           
0x670f648  mov eax,[r15+0x360]                           
0x670f64f  not eax                                       
0x670f651  add eax,[r15+0x368]                           
0x670f658  mov [rbp+0x460],ax                            
0x670f65f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f666  mov rax,[rcx]                                 
0x670f669  mov rax,[rax+0x10]                            
0x670f66d  mov dl,0x4A                                   
0x670f66f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f675  nop                                           
0x670f676  mov [rbp+0x848],al                            
0x670f67c  mov rdx,[r15+0x698]                           
0x670f683  cmp rdx,[r15+0x6A0]                           
0x670f68a  je 0x670F8DB                                  ; -> loc_670f8db
0x670f690  movzx eax,word ptr [rbp+0x584]                
0x670f697  mov [rdx],ax                                  
0x670f69a  add qword ptr [r15+0x698],2                   
0x670f6a2  jmp 0x670F8EF                                 ; -> loc_670f8ef
```

Interpretation: Grow loc_670f60e: lea rcx,[r15+0x360]; call 0x6760E60; nop. loc_670f61b: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]. mov rax,0x10000000A807049; [rbp+0x3E0]=rax. eax=[r15+0x360]; not eax; add eax,[r15+0x368]; [rbp+0x460]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x698]; cmp [r15+0x6A0]; if equal → loc_670f8db (grow). Otherwise movzx eax,word ptr [rbp+0x584]; [rdx]=ax; [r15+0x698]+=2; jmp loc_670f8ef.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x360], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r15+0x360], [r15+0x368], [rbp+0x460], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x698], [r15+0x6A0], [rbp+0x584], [r15+0x698]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x460], [rbp+0x848], [rdx], [r15+0x698].
Matches F2 Phase? Same idiom as Phase 14. No exact F2 counterpart.

---

## Phase 18 — grow loc_670f3cd tail: [rbp+0x3E8]=0x20000 + count [rbp+0x492] + TLS + grow path [r12+8]/[r12+0x10] + call 0xEEC6EC0 + bump 0xC8 + jmp loc_670f6b7 (0x670f438..0x670f4b0)

```
0x670f438  mov qword ptr [rbp+0x3E8],0x20000             
0x670f443  mov eax,[r12+0x110]                           
0x670f44b  sub eax,[r12+0x108]                           
0x670f453  shr eax,3                                     
0x670f456  imul eax,0x6DB7                               
0x670f45c  dec eax                                       
0x670f45e  mov [rbp+0x492],ax                            
0x670f465  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f46c  mov rax,[rcx]                                 
0x670f46f  mov rax,[rax+0x10]                            
0x670f473  mov dl,0x4A                                   
0x670f475  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f47b  nop                                           
0x670f47c  mov [rbp+0x848],al                            
0x670f482  mov rdx,[r12+8]                               
0x670f487  cmp rdx,[r12+0x10]                            
0x670f48c  je 0x670F6A7                                  ; -> loc_670f6a7
0x670f492  mov r8d,0xC8                                  
0x670f498  mov rcx,rdx                                   
0x670f49b  lea rdx,[rbp+0x3E0]                           
0x670f4a2  call 0xEEC6EC0                       ; -> sub_eec6ec0
0x670f4a7  add qword ptr [r12+8],0xC8                    
0x670f4b0  jmp 0x670F6B7                                 ; -> loc_670f6b7
```

Interpretation: [rbp+0x3E8]=0x20000. eax=[r12+0x110]-[r12+0x108]; shr eax,3; imul eax,0x6DB7; dec eax; [rbp+0x492]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+8]; cmp [r12+0x10]; if equal → loc_670f6a7 (grow). Otherwise r8d=0xC8; rcx=rdx; lea rdx,[rbp+0x3E0]; call 0xEEC6EC0; [r12+8]+=0xC8; jmp loc_670f6b7.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [rbp+0x3E8], [r12+0x110], [r12+0x108], [rbp+0x492], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+8], [r12+0x10], [rbp+0x3E0], [r12+8]. Fields written: [rbp+0x3E8], [rbp+0x492], [rbp+0x848], [r12+8].
Matches F2 Phase? New idiom: shr eax,3 + imul 0x6DB7 + `[rbp+0x3E8]=0x20000` + count → [rbp+0x492] + call 0xEEC6EC0 with rdx=&[rbp+0x3E0]. No exact F2 counterpart.

---

## Phase 19 — grow loc_670f4b5: TLS #2 + word count [rbp+0x41C] + TLS + dword write [r12+0x638] + bump +4 + jmp loc_670f765 (0x670f4b5..0x670f545)

```
0x670f4b5  lea rcx,[r12+0x690]                           
0x670f4bd  lea r8,[rbp+0x5C0]                            
0x670f4c4  call 0x1EF6F90                       ; -> sub_1ef6f90
0x670f4c9  nop                                           
0x670f4ca  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f4d1  mov rax,[rcx]                                 
0x670f4d4  mov rax,[rax+0x10]                            
0x670f4d8  movzx edx,byte ptr [rbp+0x848]                
0x670f4df  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f4e5  nop                                           
0x670f4e6  mov eax,[r12+0x698]                           
0x670f4ee  sub eax,[r12+0x690]                           
0x670f4f6  shr eax,1                                     
0x670f4f8  dec eax                                       
0x670f4fa  mov [rbp+0x41C],ax                            
0x670f501  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f508  mov rax,[rcx]                                 
0x670f50b  mov rax,[rax+0x10]                            
0x670f50f  mov dl,0x4A                                   
0x670f511  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f517  nop                                           
0x670f518  mov [rbp+0x848],al                            
0x670f51e  mov rdx,[r12+0x638]                           
0x670f526  cmp rdx,[r12+0x640]                           
0x670f52e  je 0x670F750                                  ; -> loc_670f750
0x670f534  mov eax,[rbp+0x5B8]                           
0x670f53a  mov [rdx],eax                                 
0x670f53c  add qword ptr [r12+0x638],4                   
0x670f545  jmp 0x670F765                                 ; -> loc_670f765
```

Interpretation: Grow loc_670f4b5: lea rcx,[r12+0x690]; lea r8,[rbp+0x5C0]; call 0x1EF6F90; nop. loc_670f4ca: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r12+0x698]-[r12+0x690]; shr eax,1; dec eax; [rbp+0x41C]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x638]; cmp [r12+0x640]; if equal → loc_670f750 (grow). Otherwise eax=[rbp+0x5B8]; [rdx]=eax; [r12+0x638]+=4; jmp loc_670f765.

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r12+0x690], [rbp+0x5C0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x698], [r12+0x690], [rbp+0x41C], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x638], [r12+0x640], [rbp+0x5B8], [r12+0x638]. Fields written: [rbp+0x848], [rbp+0x41C], [rbp+0x848], [rdx], [r12+0x638].
Matches F2 Phase? Same idiom as Phase 11. No exact F2 counterpart.

---

## Phase 20 — grow loc_670f54a: call 0x1EF6F90 + TLS #2 + word count [rbp+0x41C] + TLS + dword write [r15+0x638] + bump +4 + jmp loc_670f84b (0x670f54a..0x670f5d4)

```
0x670f54a  lea rcx,[r15+0x690]                           
0x670f551  lea r8,[rbp+0x584]                            
0x670f558  call 0x1EF6F90                       ; -> sub_1ef6f90
0x670f55d  nop                                           
0x670f55e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f565  mov rax,[rcx]                                 
0x670f568  mov rax,[rax+0x10]                            
0x670f56c  movzx edx,byte ptr [rbp+0x848]                
0x670f573  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f579  nop                                           
0x670f57a  mov eax,[r15+0x698]                           
0x670f581  sub eax,[r15+0x690]                           
0x670f588  shr eax,1                                     
0x670f58a  dec eax                                       
0x670f58c  mov [rbp+0x41C],ax                            
0x670f593  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f59a  mov rax,[rcx]                                 
0x670f59d  mov rax,[rax+0x10]                            
0x670f5a1  mov dl,0x4A                                   
0x670f5a3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f5a9  nop                                           
0x670f5aa  mov [rbp+0x848],al                            
0x670f5b0  mov rdx,[r15+0x638]                           
0x670f5b7  cmp rdx,[r15+0x640]                           
0x670f5be  je 0x670F838                                  ; -> loc_670f838
0x670f5c4  mov eax,[rbp+0x580]                           
0x670f5ca  mov [rdx],eax                                 
0x670f5cc  add qword ptr [r15+0x638],4                   
0x670f5d4  jmp 0x670F84B                                 ; -> loc_670f84b
```

Interpretation: Grow loc_670f54a: lea rcx,[r15+0x690]; lea r8,[rbp+0x584]; call 0x1EF6F90; nop. loc_670f55e: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r15+0x698]-[r15+0x690]; shr eax,1; dec eax; [rbp+0x41C]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x638]; cmp [r15+0x640]; if equal → loc_670f838 (grow). Otherwise eax=[rbp+0x580]; [rdx]=eax; [r15+0x638]+=4; jmp loc_670f84b.

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x690], [rbp+0x584], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x698], [r15+0x690], [rbp+0x41C], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x638], [r15+0x640], [rbp+0x580], [r15+0x638]. Fields written: [rbp+0x848], [rbp+0x41C], [rbp+0x848], [rdx], [r15+0x638].
Matches F2 Phase? Same idiom as Phase 20's twin (Phase 19) but with [r15] registers. No exact F2 counterpart.

---

## Phase 21 — grow loc_670f5d9: call 0x5ABA6D0 + call 0x67E1660 + jmp sub_6710c20 (0x670f5d9..0x670f609)

```
0x670f5d9  mov rcx,r15                                   
0x670f5dc  mov r8,r12                                    
0x670f5df  call 0x5ABA6D0                       ; -> sub_5aba6d0
0x670f5e4  nop                                           
0x670f5e5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f5ec  mov rax,[rcx]                                 
0x670f5ef  mov rax,[rax+0x10]                            
0x670f5f3  movzx edx,byte ptr [rbp+0x848]                
0x670f5fa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f600  nop                                           
0x670f601  mov rcx,r13                                   
0x670f604  call 0x67E1660                       ; -> sub_67e1660
0x670f609  jmp qword ptr 0x6710C20                        ; -> sub_6710c20
```

Interpretation: Grow loc_670f5d9: mov rcx,r15; mov r8,r12; call 0x5ABA6D0; nop. loc_670f5e5: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]. mov rcx,r13; call 0x67E1660. jmp sub_6710c20. This phase terminates the branch — control leaves the function via indirect jump.

Callees: 0x5ABA6D0 (sub_5aba6d0), [0xF99FFA0] = sub_eea6040 (indirect), 0x67E1660 (sub_67e1660), sub_6710c20 (indirect jmp target).
Fields read: [r15], [r12], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r13]. Fields written: none new.
Matches F2 Phase? Same call-0x5ABA6D0 + TLS + call-0x67EXXXX + jmp idiom as Phase 13. No exact F2 counterpart.

---

## Phase 22 — grow loc_670f60e tail: mov qword [rbp+0x3E0]=0x10000000A807049 + not-eax count [rbp+0x460] + TLS + word write [r15+0x698] + bump +2 + jmp loc_670f8ef (0x670f637..0x670f6a2)

```
0x670f637  mov rax,0x10000000A807049                     
0x670f641  mov [rbp+0x3E0],rax                           
0x670f648  mov eax,[r15+0x360]                           
0x670f64f  not eax                                       
0x670f651  add eax,[r15+0x368]                           
0x670f658  mov [rbp+0x460],ax                            
0x670f65f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f666  mov rax,[rcx]                                 
0x670f669  mov rax,[rax+0x10]                            
0x670f66d  mov dl,0x4A                                   
0x670f66f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f675  nop                                           
0x670f676  mov [rbp+0x848],al                            
0x670f67c  mov rdx,[r15+0x698]                           
0x670f683  cmp rdx,[r15+0x6A0]                           
0x670f68a  je 0x670F8DB                                  ; -> loc_670f8db
0x670f690  movzx eax,word ptr [rbp+0x584]                
0x670f697  mov [rdx],ax                                  
0x670f69a  add qword ptr [r15+0x698],2                   
0x670f6a2  jmp 0x670F8EF                                 ; -> loc_670f8ef
```

Interpretation: mov rax,0x10000000A807049; [rbp+0x3E0]=rax. eax=[r15+0x360]; not eax; add eax,[r15+0x368]; [rbp+0x460]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x698]; cmp [r15+0x6A0]; if equal → loc_670f8db (grow). Otherwise movzx eax,word ptr [rbp+0x584]; [rdx]=ax; [r15+0x698]+=2; jmp loc_670f8ef.

Callees: [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [rbp+0x3E0], [r15+0x360], [rbp+0x460], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x698], [r15+0x6A0], [rbp+0x584], [r15+0x698]. Fields written: [rbp+0x3E0], [rbp+0x460], [rbp+0x848], [rdx], [r15+0x698].
Matches F2 Phase? Same imm64-store + not-eax-count + TLS + word write idiom as Phase 17's tail. No exact F2 counterpart.

---

## Phase 23 — grow loc_670f6a7: call 0x5ABA6D0 + TLS #2 + heap/metadata checks + call 0xE935700 + movups write + call 0x6791DD0 + call 0x67E23F0 + test r15 + jmp (0x670f6a7..0x670f74b)

```
0x670f6a7  mov rcx,r12                                   
0x670f6aa  lea r8,[rbp+0x3E0]                            
0x670f6b1  call 0x5ABA6D0                       ; -> sub_5aba6d0
0x670f6b6  nop                                           
0x670f6b7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f6be  mov rax,[rcx]                                 
0x670f6c1  mov rax,[rax+0x10]                            
0x670f6c5  movzx edx,byte ptr [rbp+0x848]                
0x670f6cc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f6d2  nop                                           
0x670f6d3  cmp byte ptr [rbp+0x6E8],1                    
0x670f6da  jne short 0x670F72E                            ; -> loc_670f72e
0x670f6dc  mov rcx,[rbp+0x6A8]                           
0x670f6e3  test rcx,rcx                                  
0x670f6e6  je short 0x670F72E                            ; -> loc_670f72e
0x670f6e8  mov rdx,[rbp+0x6B8]                           
0x670f6ef  sub rdx,rcx                                   
0x670f6f2  cmp rdx,0x1000                                
0x670f6f9  jb short 0x670F717                            ; -> loc_670f717
0x670f6fb  mov rax,[rcx-8]                               
0x670f6ff  add rcx,0xFFFFFFFFFFFFFFF8                    
0x670f703  sub rcx,rax                                   
0x670f706  cmp rcx,0x20                                  
0x670f70a  jae 0x6713B37                                 ; -> sub_6713b37
0x670f710  or rdx,0x27                                   
0x670f714  mov rcx,rax                                   
0x670f717  call 0xE935700                       ; -> sub_e935700
0x670f71c  lea rax,[rbp+0x6A8]                           
0x670f723  movups [rax],xmm6                             
0x670f726  mov qword ptr [rax+0x10],0                    
0x670f72e  mov rcx,r13                                   
0x670f731  call 0x6791DD0                       ; -> sub_6791dd0
0x670f736  lea rcx,[rbp+0x120]                           
0x670f73d  call 0x67E23F0                       ; -> sub_67e23f0
0x670f742  test r15,r15                                  
0x670f745  jne 0x670FA46                                 ; -> loc_670fa46
0x670f74b  jmp 0x670FA73                                 ; -> loc_670fa73
```

Interpretation: Grow loc_670f6a7: mov rcx,r12; lea r8,[rbp+0x3E0]; call 0x5ABA6D0; nop. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]. cmp byte ptr [rbp+0x6E8],1; if not equal → loc_670f72e. Otherwise mov rcx,[rbp+0x6A8]; test rcx,rcx; if zero → loc_670f72e. Otherwise rdx=[rbp+0x6B8]-rcx; cmp rdx,0x1000; if below → loc_670f717. Otherwise mov rax,[rcx-8]; rcx-=8; rcx-=rax; cmp rcx,0x20; if above/equal → sub_6713b37. Otherwise rdx|=0x27; rcx=rax. loc_670f717: call 0xE935700. lea rax,[rbp+0x6A8]; movups [rax],xmm6; [rax+0x10]=0. loc_670f72e: mov rcx,r13; call 0x6791DD0. lea rcx,[rbp+0x120]; call 0x67E23F0. test r15,r15; if not equal → loc_670fa46. Otherwise jmp loc_670fa73.

Callees: 0x5ABA6D0 (sub_5aba6d0), [0xF99FFA0] = sub_eea6040 (indirect), 0xE935700 (sub_e935700), 0x6791DD0 (sub_6791dd0), 0x67E23F0 (sub_67e23f0), sub_6713b37 (indirect jump target), loc_670fa46/loc_670fa73 (jump targets outside range).
Fields read: [rbp+0x3E0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x6E8], [rbp+0x6A8], [rbp+0x6B8], [rcx-8], [rax], [xmm6], [r13], [rbp+0x120], [r15]. Fields written: [rbp+0x848], [rdx], [rcx], [rax], [rax+0x10], [rcx], [rcx-8], [rbp+0x6A8].
Matches F2 Phase? New idiom: heap metadata validation (cmp byte, test, sub, cmp with 0x1000/0x20, or 0x27) + call 0xE935700 + movups write. No exact F2 counterpart.

---

## Phase 24 — grow loc_670f750: call 0x14DB710 + TLS #2 + [rbp+0x3E0]=0xEC07009 + count [rbp+0x424] + call 0x67693F0 + [rbp+0x3E8]=0x20000 + count [rbp+0x492] + TLS #2 + grow path [r12+8]/[r12+0x10] + call 0xEEC6EC0 + bump + jmp loc_670f9b6 (0x670f750..0x670f833)

```
0x670f750  lea rcx,[r12+0x630]                           
0x670f758  lea r8,[rbp+0x5B8]                            
0x670f75f  call 0x14DB710                       ; -> sub_14db710
0x670f764  nop                                           
0x670f765  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f76c  mov rax,[rcx]                                 
0x670f76f  mov rax,[rax+0x10]                            
0x670f773  movzx edx,byte ptr [rbp+0x848]                
0x670f77a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f780  nop                                           
0x670f781  mov qword ptr [rbp+0x3E0],0xEC07009           
0x670f78c  mov eax,[r12+0x638]                           
0x670f794  sub eax,[r12+0x630]                           
0x670f79c  shr eax,2                                     
0x670f79f  dec eax                                       
0x670f7a1  mov [rbp+0x424],ax                            
0x670f7a8  mov rcx,r12                                   
0x670f7ab  add rcx,0x108                                 
0x670f7b2  mov rdx,r13                                   
0x670f7b5  call 0x67693F0                       ; -> sub_67693f0
0x670f7ba  nop                                           
0x670f7bb  mov qword ptr [rbp+0x3E8],0x20000             
0x670f7c6  mov eax,[r12+0x110]                           
0x670f7ce  sub eax,[r12+0x108]                           
0x670f7d6  shr eax,3                                     
0x670f7d9  imul eax,0x6DB7                               
0x670f7df  dec eax                                       
0x670f7e1  mov [rbp+0x492],ax                            
0x670f7e8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f7ef  mov rax,[rcx]                                 
0x670f7f2  mov rax,[rax+0x10]                            
0x670f7f6  mov dl,0x4A                                   
0x670f7f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f7fe  nop                                           
0x670f7ff  mov [rbp+0x848],al                            
0x670f805  mov rdx,[r12+8]                               
0x670f80a  cmp rdx,[r12+0x10]                            
0x670f80f  je 0x670F9A6                                  ; -> loc_670f9a6
0x670f815  mov r8d,0xC8                                  
0x670f81b  mov rcx,rdx                                   
0x670f81e  lea rdx,[rbp+0x3E0]                           
0x670f825  call 0xEEC6EC0                       ; -> sub_eec6ec0
0x670f82a  add qword ptr [r12+8],0xC8                    
0x670f833  jmp 0x670F9B6                                 ; -> loc_670f9b6
```

Interpretation: Grow loc_670f750: lea rcx,[r12+0x630]; lea r8,[rbp+0x5B8]; call 0x14DB710; nop. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E0]=0xEC07009; eax=[r12+0x638]-[r12+0x630]; shr eax,2; dec eax; [rbp+0x424]=ax. mov rcx,r12; add rcx,0x108; mov rdx,r13; call 0x67693F0; nop. [rbp+0x3E8]=0x20000. eax=[r12+0x110]-[r12+0x108]; shr eax,3; imul eax,0x6DB7; dec eax; [rbp+0x492]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+8]; cmp [r12+0x10]; if equal → loc_670f9a6 (grow). Otherwise r8d=0xC8; rcx=rdx; lea rdx,[rbp+0x3E0]; call 0xEEC6EC0; [r12+8]+=0xC8; jmp loc_670f9b6.

Callees: 0x14DB710 (sub_14db710), [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x67693F0 (sub_67693f0), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [r12+0x630], [rbp+0x5B8], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r12+0x638], [r12+0x630], [rbp+0x424], [r12], [r13], [rbp+0x3E8], [r12+0x110], [r12+0x108], [rbp+0x492], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+8], [r12+0x10], [rbp+0x3E0], [r12+8]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x424], [rbp+0x3E8], [rbp+0x492], [rbp+0x848], [r12+8].
Matches F2 Phase? Same idiom as Phase 18 but with count [rbp+0x424] (shr eax,2) inserted before call 0x67693F0. No exact F2 counterpart.

---

## Phase 25 — grow loc_670f838: call 0x14DB710 + mov qword [rbp+0x3E0]=0x10000000E407049 + count [rbp+0x424] + TLS #2 + grow path [r15+8]/[r15+0x10] + call 0xEEC6EC0 + bump + jmp loc_670f976 (0x670f838..0x670f8d6)

```
0x670f838  mov rcx,r15                                   
0x670f83b  add rcx,0x630                                 
0x670f842  mov r8,r13                                    
0x670f845  call 0x14DB710                       ; -> sub_14db710
0x670f84a  nop                                           
0x670f84b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f852  mov rax,[rcx]                                 
0x670f855  mov rax,[rax+0x10]                            
0x670f859  movzx edx,byte ptr [rbp+0x848]                
0x670f860  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f866  nop                                           
0x670f867  mov rax,0x10000000E407049                     
0x670f871  mov [rbp+0x3E0],rax                           
0x670f878  mov eax,[r15+0x638]                           
0x670f87f  sub eax,[r15+0x630]                           
0x670f886  shr eax,2                                     
0x670f889  dec eax                                       
0x670f88b  mov [rbp+0x424],ax                            
0x670f892  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f899  mov rax,[rcx]                                 
0x670f89c  mov rax,[rax+0x10]                            
0x670f8a0  mov dl,0x4A                                   
0x670f8a2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f8a8  nop                                           
0x670f8a9  mov [rbp+0x848],al                            
0x670f8af  mov rdx,[r15+8]                               
0x670f8b3  cmp rdx,[r15+0x10]                            
0x670f8b7  je 0x670F96A                                  ; -> loc_670f96a
0x670f8bd  mov r8d,0xC8                                  
0x670f8c3  mov rcx,rdx                                   
0x670f8c6  mov rdx,r12                                   
0x670f8c9  call 0xEEC6EC0                       ; -> sub_eec6ec0
0x670f8ce  add qword ptr [r15+8],0xC8                    
0x670f8d6  jmp 0x670F976                                 ; -> loc_670f976
```

Interpretation: Grow loc_670f838: mov rcx,r15; add rcx,0x630; mov r8,r13; call 0x14DB710; nop. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; mov rax,0x10000000E407049; [rbp+0x3E0]=rax; eax=[r15+0x638]-[r15+0x630]; shr eax,2; dec eax; [rbp+0x424]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+8]; cmp [r15+0x10]; if equal → loc_670f96a (grow). Otherwise r8d=0xC8; rcx=rdx; rdx=r12; call 0xEEC6EC0; [r15+8]+=0xC8; jmp loc_670f976.

Callees: 0x14DB710 (sub_14db710), [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [r15], [r15+0x630], [r13], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [rbp+0x3E0], [r15+0x638], [r15+0x630], [rbp+0x424], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+8], [r15+0x10], [rdx], [r12], [r15+8]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x424], [rbp+0x848], [r15+8].
Matches F2 Phase? Same idiom as Phase 25's twin but with imm64-store and [r15] registers. No exact F2 counterpart.

---

## Phase 26 — grow loc_670f8db: call 0x1EF6F90 + TLS #2 + word count [rbp+0x41C] + TLS #2 setup (0x670f8db..0x670f92b)

```
0x670f8db  lea rcx,[r15+0x690]                           
0x670f8e2  lea r8,[rbp+0x584]                            
0x670f8e9  call 0x1EF6F90                       ; -> sub_1ef6f90
0x670f8ee  nop                                           
0x670f8ef  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f8f6  mov rax,[rcx]                                 
0x670f8f9  mov rax,[rax+0x10]                            
0x670f8fd  movzx edx,byte ptr [rbp+0x848]                
0x670f904  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670f90a  nop                                           
0x670f90b  mov eax,[r15+0x698]                           
0x670f912  sub eax,[r15+0x690]                           
0x670f919  shr eax,1                                     
0x670f91b  dec eax                                       
0x670f91d  mov [rbp+0x41C],ax                            
0x670f924  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670f92b  mov rax,[rcx]                                 
```

Interpretation: Grow loc_670f8db: lea rcx,[r15+0x690]; lea r8,[rbp+0x584]; call 0x1EF6F90; nop. loc_670f8ef: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r15+0x698]-[r15+0x690]; shr eax,1; dec eax; [rbp+0x41C]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx] (unit ends here; next would be mov rax,[rax+0x10] etc.).

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r15+0x690], [rbp+0x584], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x698], [r15+0x690], [rbp+0x41C], [0x1233E1B0], [rcx]. Fields written: [rbp+0x848], [rbp+0x41C].
Matches F2 Phase? Same idiom as Phase 21's twin. Unit ends mid-TLS-#2 at instruction 800 (0x670f92b mov rax,[rcx]).




