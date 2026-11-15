# U-E4-H4 — sub_6722cb0 continuation (builder 0x6722cb0)

H3 = docs/progress/oc_U-E4-H3.md covered phases 1-7, instructions 0x6724a4d..0x6725004.
H4 resumes at 0x6725004 per H3 NEXT block (instruction after 0x6724fff `movss [rdx+0x1C],xmm0`). Target: 800 instructions = 20 phases of 40.
Static analysis only. Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe 1.26.62.01. RVAs image-relative.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown.
WARNING: H3 Phase 3 addresses 0x6724bf0..0x6724c00 are unreliable (garbled line `adc [rbp+0x6C0],al`); re-verified with rdis below. All other H4 content is fresh rdis output.

## NEXT
COMPLETE: 20 phases / 800 instructions done (0x6725004..0x672604d). Phase 20 ended at 0x6726047 `mov [rbp+0x818],al`; next instruction would be 0x672604d `mov rdx,[r14+8]` (beyond target). No further steps required.

---

## Re-disassembly of garbled range 0x6724bf0..0x6724c00 [V]

`rdis dis 0x6724bf0 40`. Exact rdis lines for instructions starting in [0x6724bf0, 0x6724c00):

```
  6724bf0  add bl,dh                                    
  6724bf2  movups [rdx+0x1C],xmm0                        ; W a1+0x1C
  6724bf6  movss xmm0,[rbp+0x6C0]                        
  6724bfe  movss [rdx+0x20],xmm0                         ; W a1+0x20
  6724c03  movss xmm0,[rbp+0x6C4]                        
```
Next instruction after range: `  6724c0b  movss [rdx+0x24],xmm0` (starts at 0x6724c0b, outside the range).

Interpretation: `add bl,dh` at 0x6724bf0 [V]. `movups [rdx+0x1C],xmm0` at 0x6724bf2 [V] (ends 0x6724bf6; H3 mis-dated/mis-mnemoniced this store). `movss xmm0,[rbp+0x6C0]` at 0x6724bf6 [V] — this is the line H3 garbled as `0x6724bf8 adc [rbp+0x6C0],al`; rdis places it at 0x6724bf6. `movss [rdx+0x20],xmm0` at 0x6724bfe [V]; `movss xmm0,[rbp+0x6C4]` at 0x6724c03 [V]. Tail of the [rbp+0x6A0..0x6C4] -> [rdx+0x10..0x24] struct-copy pattern (H3 Phases 2-3), continuing into the xmm block from [rbp+0x6C8] at 0x6724c10 [V] (matches H3 exactly, confirming alignment).

Callees: none.
Fields read: [rbp+0x6C0] [R], [rbp+0x6C4] [R]. Fields written: [rdx+0x1C] [W], [rdx+0x20] [W].

---

## Phase 1 — copy block tail ([rbp+0x708/0x70C] -> [rdx+0x20/0x24], xmm block [rbp+0x564+0x1AC/0x1BC/0x1CB] -> [rdx+0x28/0x38/0x47]) + add qword + jmp loc_6725337; fall-through: lea rcx=[r14+0x750], lea r8=[rbp+0x698], call 0x6760A80, TLS seq, count calc >>3 + imul 0xFFFF8BA3 -> [rbp+0x13C], second TLS call dl=0x4A, [r14+0x860] vs [r14+0x868] compare + inc rdx (0x6725004..0x67250d7)

```
  6725004  movss xmm0,[rbp+0x708]                        
  672500c  movss [rdx+0x20],xmm0                         ; W a1+0x20
  6725011  movss xmm0,[rbp+0x70C]                        
  6725019  movss [rdx+0x24],xmm0                         ; W a1+0x24
  672501e  lea rax,[rbp+0x564]                           
  6725025  movups xmm0,[rax+0x1AC]                       
  672502c  movups xmm1,[rax+0x1BC]                       
  6725033  movups xmm2,[rax+0x1CB]                       
  672503a  movups [rdx+0x28],xmm0                        ; W a1+0x28
  672503e  movups [rdx+0x38],xmm1                        ; W a1+0x38
  6725042  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6725046  add qword ptr [r15+0x758],0x58                
  672504e  jmp 0x6725337                                 ; -> loc_6725337
  6725053  lea rcx,[r14+0x750]                           
  672505a  lea r8,[rbp+0x698]                            
  6725061  call 0x6760A80                                ; -> sub_6760a80
  6725066  nop                                           
  6725067  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672506e  mov rax,[rcx]                                 
  6725071  mov rax,[rax+0x10]                            
  6725075  movzx edx,byte ptr [rbp+0x818]                
  672507c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725082  nop                                           
  6725083  mov eax,[r14+0x758]                           
  672508a  sub eax,[r14+0x750]                           
  6725091  shr eax,3                                     
  6725094  imul eax,0xFFFF8BA3                           
  672509a  dec eax                                       
  672509c  mov [rbp+0x13C],ax                            
  67250a3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67250aa  mov rax,[rcx]                                 
  67250ad  mov rax,[rax+0x10]                            
  67250b1  mov dl,0x4A                                   
  67250b3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67250b9  nop                                           
  67250ba  mov [rbp+0x818],al                            
  67250c0  mov rdx,[r14+0x860]                           
  67250c7  cmp rdx,[r14+0x868]                           
  67250ce  je 0x67253B3                                  ; -> loc_67253b3
  67250d4  inc rdx                                       
```

Interpretation: `movss xmm0,[rbp+0x708]`; `movss [rdx+0x20],xmm0`; `movss xmm0,[rbp+0x70C]`; `movss [rdx+0x24],xmm0`. `lea rax,[rbp+0x564]`; `movups xmm0=[rax+0x1AC]`, `xmm1=[rax+0x1BC]`, `xmm2=[rax+0x1CB]`; `movups [rdx+0x28]=xmm0`, `[rdx+0x38]=xmm1`, `[rdx+0x47]=xmm2`. `add qword ptr [r15+0x758],0x58`. `jmp 0x6725337` (-> loc_6725337).
Fall-through block at 0x6725053: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x698]`; `call 0x6760A80` (rcx=&[r14+0x750], r8=&[rbp+0x698], rdx carries the copy-destination pointer [I]). TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). Count calc: `eax=[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x13C],ax`. Second TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; if equal `je 0x67253B3` (-> loc_67253b3). `inc rdx` (continues next phase: 0x67250d7 `mov [r14+0x860],rdx`).

Callees: 0x6760A80 (sub_6760a80, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rbp+0x708] [R], [rdx+0x20] [R/W], [rbp+0x70C] [R], [rdx+0x24] [R/W], [rbp+0x564] [R], [rax+0x1AC] [R], [rax+0x1BC] [R], [rax+0x1CB] [R], [rdx+0x28] [W], [rdx+0x38] [W], [rdx+0x47] [W], [r15+0x758] [R/W], [r14+0x750] [R], [rbp+0x698] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x758] [R], [r14+0x860] [R], [r14+0x868] [R]. Fields written: [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r15+0x758], [rbp+0x13C], [rbp+0x818], [r14+0x860] [W at 0x67250d7, next phase].

---

## Phase 2 — mov [r14+0x860],rdx + jmp loc_67253c0; fall-through block: lea rcx=[r14+0x750], lea r8=[rbp+0x6A0], call 0x6760A80, TLS seq, count calc >>3 + imul 0xFFFF8BA3 -> [rbp+0x13C], second TLS call dl=0x4A, [r14+0x860] vs [r14+0x868] compare + inc rdx, jmp loc_672551f; third lea/call block start (0x67250d7..0x67251a2)

```
  67250d7  mov [r14+0x860],rdx                           
  67250de  jmp 0x67253C0                                 ; -> loc_67253c0
  67250e3  lea rcx,[r14+0x750]                           
  67250ea  lea r8,[rbp+0x6A0]                            
  67250f1  call 0x6760A80                                ; -> sub_6760a80
  67250f6  nop                                           
  67250f7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67250fe  mov rax,[rcx]                                 
  6725101  mov rax,[rax+0x10]                            
  6725105  movzx edx,byte ptr [rbp+0x818]                
  672510c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725112  nop                                           
  6725113  mov eax,[r14+0x758]                           
  672511a  sub eax,[r14+0x750]                           
  6725121  shr eax,3                                     
  6725124  imul eax,0xFFFF8BA3                           
  672512a  dec eax                                       
  672512c  mov [rbp+0x13C],ax                            
  6725133  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672513a  mov rax,[rcx]                                 
  672513d  mov rax,[rax+0x10]                            
  6725141  mov dl,0x4A                                   
  6725143  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725149  nop                                           
  672514a  mov [rbp+0x818],al                            
  6725150  mov rdx,[r14+0x860]                           
  6725157  cmp rdx,[r14+0x868]                           
  672515e  je 0x6725512                                  ; -> loc_6725512
  6725164  inc rdx                                       
  6725167  mov [r14+0x860],rdx                           
  672516e  jmp 0x672551F                                 ; -> loc_672551f
  6725173  lea rcx,[r14+0x750]                           
  672517a  lea r8,[rbp+0x6A0]                            
  6725181  call 0x6760A80                                ; -> sub_6760a80
  6725186  nop                                           
  6725187  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672518e  mov rax,[rcx]                                 
  6725191  mov rax,[rax+0x10]                            
  6725195  movzx edx,byte ptr [rbp+0x818]                
  672519c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

Interpretation: `mov [r14+0x860],rdx`. `jmp 0x67253C0` (-> loc_67253c0).
Fall-through block at 0x67250e3: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x6A0]`; `call 0x6760A80` (rcx=&[r14+0x750], r8=&[rbp+0x6A0], rdx carries the copy-destination pointer [I]). TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). Count calc: `eax=[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x13C],ax`. Second TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; if equal `je 0x6725512` (-> loc_6725512). `inc rdx`; `mov [r14+0x860],rdx`. `jmp 0x672551F` (-> loc_672551f).
Third block at 0x6725173: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x6A0]`; `call 0x6760A80`; ...continues (next phase: 0x67251a2 `nop`).

Callees: 0x6760A80 (sub_6760a80, direct, twice), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r14+0x860] [R], [r14+0x750] [R], [rbp+0x6A0] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x758] [R], [r14+0x868] [R]. Fields written: [r14+0x860], [rbp+0x13C], [rbp+0x818].

---

## Phase 3 — nop; count calc >>3 + imul 0xFFFF8BA3 -> [rbp+0x13C]; TLS call dl=0x4A; mov [rbp+0x818],al; [r14+0x860] vs [r14+0x868] compare + inc rdx, jmp loc_672567e; fall-through: lea rcx=[r14+0x750], lea r8=[rbp+0x6B0], call 0x6760A80, TLS seq, count calc >>3 + imul 0xFFFF8BA3 -> [rbp+0x13C], second TLS call dl=0x4A (continues) (0x67251a2..0x6725263)

```
  67251a2  nop                                           
  67251a3  mov eax,[r14+0x758]                           
  67251aa  sub eax,[r14+0x750]                           
  67251b1  shr eax,3                                     
  67251b4  imul eax,0xFFFF8BA3                           
  67251ba  dec eax                                       
  67251bc  mov [rbp+0x13C],ax                            
  67251c3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67251ca  mov rax,[rcx]                                 
  67251cd  mov rax,[rax+0x10]                            
  67251d1  mov dl,0x4A                                   
  67251d3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67251d9  nop                                           
  67251da  mov [rbp+0x818],al                            
  67251e0  mov rdx,[r14+0x860]                           
  67251e7  cmp rdx,[r14+0x868]                           
  67251ee  je 0x6725671                                  ; -> loc_6725671
  67251f4  inc rdx                                       
  67251f7  mov [r14+0x860],rdx                           
  67251fe  jmp 0x672567E                                 ; -> loc_672567e
  6725203  lea rcx,[r14+0x750]                           
  672520a  lea r8,[rbp+0x6B0]                            
  6725211  call 0x6760A80                                ; -> sub_6760a80
  6725216  nop                                           
  6725217  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672521e  mov rax,[rcx]                                 
  6725221  mov rax,[rax+0x10]                            
  6725225  movzx edx,byte ptr [rbp+0x818]                
  672522c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725232  nop                                           
  6725233  mov eax,[r14+0x758]                           
  672523a  sub eax,[r14+0x750]                           
  6725241  shr eax,3                                     
  6725244  imul eax,0xFFFF8BA3                           
  672524a  dec eax                                       
  672524c  mov [rbp+0x13C],ax                            
  6725253  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672525a  mov rax,[rcx]                                 
  672525d  mov rax,[rax+0x10]                            
  6725261  mov dl,0x4A                                   
  6725263  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

Interpretation: `nop`. Count calc: `eax=[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x13C],ax`. TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `mov [rbp+0x818],al`. `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; if equal `je 0x6725671` (-> loc_6725671). `inc rdx`; `mov [r14+0x860],rdx`. `jmp 0x672567E` (-> loc_672567e).
Fall-through block at 0x6725203: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x6B0]`; `call 0x6760A80` (rcx=&[r14+0x750], r8=&[rbp+0x6B0]). TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`. Count calc: `eax=[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x13C],ax`. Second TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al` (continues next phase).

Callees: 0x6760A80 (sub_6760a80, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r14+0x758] [R], [r14+0x750] [R], [rbp+0x13C] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x860] [R], [r14+0x868] [R], [rbp+0x6B0] [R]. Fields written: [rbp+0x13C], [rbp+0x818], [r14+0x860].

---

## Phase 4 — call qword ptr [0xF99FFA0] (tail of Phase 3's second TLS call), nop, mov [rbp+0x818],al; [r14+0x860] vs [r14+0x868] compare + inc rdx, jmp loc_67257dd; fall-through switch to r15 context: lea rcx=[r15+0x750], lea r8=[rbp+0x6D8], call 0x6760A80, TLS seq, count calc (r15) >>3 + imul 0xFFFF8BA3 -> [rbp+0x13C], second TLS call dl=0x4A, mov [rbp+0x818],al; [r15+0x860] vs [r15+0x868] compare + inc rdx, jmp loc_672593c; third lea/call block start (0x6725263..0x672532a)

```
  6725263  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725269  nop                                           
  672526a  mov [rbp+0x818],al                            
  6725270  mov rdx,[r14+0x860]                           
  6725277  cmp rdx,[r14+0x868]                           
  672527e  je 0x67257D0                                  ; -> loc_67257d0
  6725284  inc rdx                                       
  6725287  mov [r14+0x860],rdx                           
  672528e  jmp 0x67257DD                                 ; -> loc_67257dd
  6725293  lea rcx,[r15+0x750]                           
  672529a  lea r8,[rbp+0x6D8]                            
  67252a1  call 0x6760A80                                ; -> sub_6760a80
  67252a6  nop                                           
  67252a7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67252ae  mov rax,[rcx]                                 
  67252b1  mov rax,[rax+0x10]                            
  67252b5  movzx edx,byte ptr [rbp+0x818]                
  67252bc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67252c2  nop                                           
  67252c3  mov eax,[r15+0x758]                           
  67252ca  sub eax,[r15+0x750]                           
  67252d1  shr eax,3                                     
  67252d4  imul eax,0xFFFF8BA3                           
  67252da  dec eax                                       
  67252dc  mov [rbp+0x13C],ax                            
  67252e3  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  67252ea  mov rax,[rcx]                                 
  67252ed  mov rax,[rax+0x10]                            
  67252f1  mov dl,0x4A                                   
  67252f3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67252f9  nop                                           
  67252fa  mov [rbp+0x818],al                            
  6725300  mov rdx,[r15+0x860]                           
  6725307  cmp rdx,[r15+0x868]                           
  672530e  je 0x672592F                                  ; -> loc_672592f
  6725314  inc rdx                                       
  6725317  mov [r15+0x860],rdx                           
  672531e  jmp 0x672593C                                 ; -> loc_672593c
  6725323  lea rcx,[r15+0x750]                           
  672532a  lea r8,[rbp+0x6E8]                            
```

Interpretation: `call qword ptr [0xF99FFA0]` (sub_eea6040; tail of the call that started at 0x6725261 in Phase 3). `nop`. `mov [rbp+0x818],al`. `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; if equal `je 0x67257D0` (-> loc_67257d0). `inc rdx`; `mov [r14+0x860],rdx`. `jmp 0x67257DD` (-> loc_67257dd).
Fall-through block at 0x6725293 (switch to r15 context): `lea rcx,[r15+0x750]`; `lea r8,[rbp+0x6D8]`; `call 0x6760A80` (rcx=&[r15+0x750], r8=&[rbp+0x6D8]). TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). Count calc (r15): `eax=[r15+0x758]`; `sub eax,[r15+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x13C],ax`. Second TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rdx=[r15+0x860]`; `cmp rdx,[r15+0x868]`; if equal `je 0x672592F` (-> loc_672592f). `inc rdx`; `mov [r15+0x860],rdx`. `jmp 0x672593C` (-> loc_672593c).
Third block at 0x6725323: `lea rcx,[r15+0x750]`; `lea r8,[rbp+0x6E8]`; ...continues (next phase: 0x6725331 `call 0x6760A80`).

Callees: 0x6760A80 (sub_6760a80, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r14+0x860] [R], [r14+0x868] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r15+0x750] [R], [rbp+0x6D8] [R], [r15+0x758] [R], [r15+0x750] [R], [r15+0x860] [R], [r15+0x868] [R], [rbp+0x6E8] [R]. Fields written: [rbp+0x818], [r14+0x860], [rbp+0x13C], [r15+0x860].

---

## Phase 5 — call 0x6760A80 (tail of Phase 4's third block), TLS seq, count calc (r15) >>3 + imul 0xFFFF8BA3 -> [rbp+0x13C], second TLS call dl=0x4A, mov [rbp+0x818],al; [r15+0x860] vs [r15+0x868] compare + inc rdx, jmp loc_672593c; block at 0x67253b3: lea rcx=[r14+0x858], call 0x6760E60, TLS seq, mov qword ptr [rbp+0x110],0x4009, not eax + add [r14+0x860] (continues) (0x672532a..0x67253f0)

```
  672532a  lea r8,[rbp+0x6E8]                            
  6725331  call 0x6760A80                                ; -> sub_6760a80
  6725336  nop                                           
  6725337  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]   (target of Phase 1's jmp 0x6725337)
  672533e  mov rax,[rcx]                                 
  6725341  mov rax,[rax+0x10]                            
  6725345  movzx edx,byte ptr [rbp+0x818]                
  672534c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725352  nop                                           
  6725353  mov eax,[r15+0x758]                           
  672535a  sub eax,[r15+0x750]                           
  6725361  shr eax,3                                     
  6725364  imul eax,0xFFFF8BA3                           
  672536a  dec eax                                       
  672536c  mov [rbp+0x13C],ax                            
  6725373  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672537a  mov rax,[rcx]                                 
  672537d  mov rax,[rax+0x10]                            
  6725381  mov dl,0x4A                                   
  6725383  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725389  nop                                           
  672538a  mov [rbp+0x818],al                            
  6725390  mov rdx,[r15+0x860]                           
  6725397  cmp rdx,[r15+0x868]                           
  672539e  je 0x6725A8E                                  ; -> loc_6725a8e
  67253a4  inc rdx                                       
  67253a7  mov [r15+0x860],rdx                           
  67253ae  jmp 0x6725A9B                                 ; -> loc_6725a9b
  67253b3  lea rcx,[r14+0x858]                           
  67253ba  call 0x6760E60                                ; -> sub_6760e60
  67253bf  nop                                           
  67253c0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]   (target of Phase 2's jmp 0x67253C0)
  67253c7  mov rax,[rcx]                                 
  67253ca  mov rax,[rax+0x10]                            
  67253ce  movzx edx,byte ptr [rbp+0x818]                
  67253d5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67253db  nop                                           
  67253dc  mov qword ptr [rbp+0x110],0x4009              
  67253e7  mov eax,[r14+0x858]                           
  67253ee  not eax                                       
  67253f0  add eax,[r14+0x860]                           
```

Interpretation: `lea r8,[rbp+0x6E8]`; `call 0x6760A80` (sub_6760a80; rcx=[r15+0x750] set in previous phase, r8=&[rbp+0x6E8]). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). Count calc (r15): `eax=[r15+0x758]`; `sub eax,[r15+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x13C],ax`. Second TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rdx=[r15+0x860]`; `cmp rdx,[r15+0x868]`; if equal `je 0x6725A8E` (-> loc_6725a8e). `inc rdx`; `mov [r15+0x860],rdx`. `jmp 0x6725A9B` (-> loc_6725a9b).
Block at 0x67253b3: `lea rcx,[r14+0x858]`; `call 0x6760E60` (sub_6760e60; new callee). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`. `nop`. `mov qword ptr [rbp+0x110],0x4009`. `eax=[r14+0x858]`; `not eax`; `add eax,[r14+0x860]`; `mov [rbp+0x126],ax`.

Callees: 0x6760A80 (sub_6760a80, direct), 0x6760E60 (sub_6760e60, direct), [0xF99FFA0] = sub_eea6040 (indirect, three times).
Fields read: [rbp+0x6E8] [R], [r15+0x750] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r15+0x758] [R], [r15+0x750] [R], [r15+0x860] [R], [r15+0x868] [R], [r14+0x858] [R], [rbp+0x110] [W], [r14+0x860] [R]. Fields written: [rbp+0x13C], [rbp+0x818], [r15+0x860], [rbp+0x110], [rbp+0x126].

---

## Phase 6 — add [r14+0x860] -> [rbp+0x126]; TLS call dl=0x4A, mov [rbp+0x818],al; lea rcx=[r14+0x648], lea rdx=[rbp+0x648], call 0x675FB30; TLS seq; [r14+0x650]-[r14+0x648] count calc >>3 + imul 0xFFFF8E39 -> [rbp+0x152]; lea rcx=[r14+0x780], lea rdx=[rbp+0x5F0], call 0x675F3B0; [r14+0x788]-[r14+0x780] count calc >>3 + imul 0xFFFF8BA3 -> [rbp+0x138]; TLS call dl=0x4A, mov [rbp+0x818],al; mov rdi,[r14+0x770] (continues) (0x67253f0..0x67254ba)

```
  67253f0  add eax,[r14+0x860]                           
  67253f7  mov [rbp+0x126],ax                            
  67253fe  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725405  mov rax,[rcx]                                 
  6725408  mov rax,[rax+0x10]                            
  672540c  mov dl,0x4A                                   
  672540e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725414  mov [rbp+0x818],al                            
  672541a  lea rcx,[r14+0x648]                           
  6725421  lea rdx,[rbp+0x648]                           
  6725428  call 0x675FB30                                ; -> sub_675fb30
  672542d  nop                                           
  672542e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725435  mov rax,[rcx]                                 
  6725438  mov rax,[rax+0x10]                            
  672543c  movzx edx,byte ptr [rbp+0x818]                
  6725443  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725449  nop                                           
  672544a  mov eax,[r14+0x650]                           
  6725451  sub eax,[r14+0x648]                           
  6725458  shr eax,3                                     
  672545b  imul eax,0xFFFF8E39                           
  6725461  dec eax                                       
  6725463  mov [rbp+0x152],ax                            
  672546a  lea rcx,[r14+0x780]                           
  6725471  lea rdx,[rbp+0x5F0]                           
  6725478  call 0x675F3B0                                ; -> sub_675f3b0
  672547d  nop                                           
  672547e  mov eax,[r14+0x788]                           
  6725485  sub eax,[r14+0x780]                           
  672548c  shr eax,3                                     
  672548f  imul eax,0xFFFF8BA3                           
  6725495  dec eax                                       
  6725497  mov [rbp+0x138],ax                            
  672549e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67254a5  mov rax,[rcx]                                 
  67254a8  mov rax,[rax+0x10]                            
  67254ac  mov dl,0x4A                                   
  67254ae  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67254b4  mov [rbp+0x818],al                            
  67254ba  mov rdi,[r14+0x770]                           
```

Interpretation: `eax += [r14+0x860]`; `mov [rbp+0x126],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `mov [rbp+0x818],al`. `rcx=&[r14+0x648]`; `rdx=&[rbp+0x648]`; `call 0x675FB30` (sub_675fb30; new callee). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop`. Count calc: `eax=[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39` (new magic constant); `dec eax`; `mov [rbp+0x152],ax`. `rcx=&[r14+0x780]`; `rdx=&[rbp+0x5F0]`; `call 0x675F3B0` (sub_675f3b0; new callee). `nop`. Count calc: `eax=[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x138],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rdi=[r14+0x770]` (continues next phase).

Callees: 0x675FB30 (sub_675fb30, direct), 0x675F3B0 (sub_675f3b0, direct), [0xF99FFA0] = sub_eea6040 (indirect, three times).
Fields read: [r14+0x860] [R], [rbp+0x126] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x648] [R], [r14+0x650] [R], [rbp+0x152] [W], [r14+0x780] [R], [rbp+0x5F0] [R], [r14+0x788] [R], [rbp+0x138] [W], [r14+0x770] [R]. Fields written: [rbp+0x126], [rbp+0x818], [rbp+0x152], [rbp+0x138].

---

## Phase 7 — mov rdi=[r14+0x770]; cmp [r14+0x778] + je loc_6725bed; copy [rbp+0x568]->[rdi], lea rcx=[rdi+8], lea rdx=[rbp+0x570], call 0xE869FF0; [rbp+0x5E8]->[rdi+0x80], zero [rbp+0x5E8], add qword [r14+0x770],0x88, jmp loc_6725c04; je-target block at 0x6725512: lea rcx=[r14+0x858], call 0x6760E60, TLS seq, mov qword ptr [rbp+0x110],0x4009, not/add eax -> [rbp+0x126], TLS call dl=0x4A, mov [rbp+0x818],al; lea rcx=[r14+0x648], lea rdx=[rbp+0x650], call 0x675FB30, TLS seq start (0x67254ba..0x6725597)

```
  67254ba  mov rdi,[r14+0x770]                           
  67254c1  cmp rdi,[r14+0x778]                           
  67254c8  je 0x6725BED                                  ; -> loc_6725bed
  67254ce  mov rax,[rbp+0x568]                           
  67254d5  mov [rdi],rax                                 
  67254d8  lea rcx,[rdi+8]                               
  67254dc  lea rdx,[rbp+0x570]                           
  67254e3  call 0xE869FF0                                ; -> sub_e869ff0
  67254e8  nop                                           
  67254e9  mov rax,[rbp+0x5E8]                           
  67254f0  mov [rdi+0x80],rax                            
  67254f7  mov qword ptr [rbp+0x5E8],0                   
  6725502  add qword ptr [r14+0x770],0x88                
  672550d  jmp 0x6725C04                                 ; -> loc_6725c04
  6725512  lea rcx,[r14+0x858]                           
  6725519  call 0x6760E60                                ; -> sub_6760e60
  672551e  nop                                           
  672551f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725526  mov rax,[rcx]                                 
  6725529  mov rax,[rax+0x10]                            
  672552d  movzx edx,byte ptr [rbp+0x818]                
  6725534  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672553a  nop                                           
  672553b  mov qword ptr [rbp+0x110],0x4009              
  6725546  mov eax,[r14+0x858]                           
  672554d  not eax                                       
  672554f  add eax,[r14+0x860]                           
  6725556  mov [rbp+0x126],ax                            
  672555d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725564  mov rax,[rcx]                                 
  6725567  mov rax,[rax+0x10]                            
  672556b  mov dl,0x4A                                   
  672556d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725573  mov [rbp+0x818],al                            
  6725579  lea rcx,[r14+0x648]                           
  6725580  lea rdx,[rbp+0x650]                           
  6725587  call 0x675FB30                                ; -> sub_675fb30
  672558c  nop                                           
  672558d  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  6725594  mov rax,[rcx]                                 
  6725597  mov rax,[rax+0x10]                            
```

Interpretation: `rdi=[r14+0x770]`; `cmp rdi,[r14+0x778]`; if equal `je 0x6725BED` (-> loc_6725bed). Else: `rax=[rbp+0x568]`; `mov [rdi],rax`; `rcx=rdi+8`; `rdx=&[rbp+0x570]`; `call 0xE869FF0` (sub_e869ff0; new direct callee); `nop`. `rax=[rbp+0x5E8]`; `mov [rdi+0x80],rax`. `mov qword ptr [rbp+0x5E8],0`. `add qword ptr [r14+0x770],0x88`. `jmp 0x6725C04` (-> loc_6725c04).
Je-target block at 0x6725512 (referenced by Phase 2's `je 0x6725512`): `lea rcx,[r14+0x858]`; `call 0x6760E60` (sub_6760e60). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. `mov qword ptr [rbp+0x110],0x4009`. `eax=[r14+0x858]`; `not eax`; `add eax,[r14+0x860]`; `mov [rbp+0x126],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rcx=&[r14+0x648]`; `rdx=&[rbp+0x650]`; `call 0x675FB30` (sub_675fb30). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]` (continues next phase).

Callees: 0xE869FF0 (sub_e869ff0, direct), 0x6760E60 (sub_6760e60, direct), 0x675FB30 (sub_675fb30, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r14+0x770] [R], [r14+0x778] [R], [rbp+0x568] [R], [rbp+0x5E8] [R], [r14+0x770] [R/W], [rbp+0x5E8] [W], [r14+0x858] [R], [rbp+0x110] [W], [rbp+0x818] [R/W], [r14+0x860] [R], [rbp+0x126] [W], [r14+0x648] [R], [rbp+0x650] [R]. Fields written: [rdi] [W], [rdi+0x80] [W], [rbp+0x5E8], [r14+0x770], [rbp+0x110], [rbp+0x126].

---

## Phase 8 — TLS seq tail (mov rax=[rax+0x10], movzx edx,byte [rbp+0x818], call [0xF99FFA0]), nop; [r14+0x650]-[r14+0x648] count calc >>3 + imul 0xFFFF8E39 -> [rbp+0x152]; lea rcx=[r14+0x780], lea rdx=[rbp+0x5F8], call 0x675F3B0; [r14+0x788]-[r14+0x780] count calc >>3 + imul 0xFFFF8BA3 -> [rbp+0x138]; TLS call dl=0x4A, mov [rbp+0x818],al; mov rdi=[r14+0x770]; cmp [r14+0x778] + je loc_6725c82; copy [rbp+0x570]->[rdi], lea rcx=[rdi+8], lea rdx=[rbp+0x578], call 0xE869FF0; [rbp+0x5F0]->[rdi+0x80], zero [rbp+0x5F0], add qword [r14+0x770],0x88, jmp loc_6725c99 (0x6725597..0x6725671)

```
  6725597  mov rax,[rax+0x10]                            
  672559b  movzx edx,byte ptr [rbp+0x818]                
  67255a2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67255a8  nop                                           
  67255a9  mov eax,[r14+0x650]                           
  67255b0  sub eax,[r14+0x648]                           
  67255b7  shr eax,3                                     
  67255ba  imul eax,0xFFFF8E39                           
  67255c0  dec eax                                       
  67255c2  mov [rbp+0x152],ax                            
  67255c9  lea rcx,[r14+0x780]                           
  67255d0  lea rdx,[rbp+0x5F8]                           
  67255d7  call 0x675F3B0                                ; -> sub_675f3b0
  67255dc  nop                                           
  67255dd  mov eax,[r14+0x788]                           
  67255e4  sub eax,[r14+0x780]                           
  67255eb  shr eax,3                                     
  67255ee  imul eax,0xFFFF8BA3                           
  67255f4  dec eax                                       
  67255f6  mov [rbp+0x138],ax                            
  67255fd  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725604  mov rax,[rcx]                                 
  6725607  mov rax,[rax+0x10]                            
  672560b  mov dl,0x4A                                   
  672560d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725613  mov [rbp+0x818],al                            
  6725619  mov rdi,[r14+0x770]                           
  6725620  cmp rdi,[r14+0x778]                           
  6725627  je 0x6725C82                                  ; -> loc_6725c82
  672562d  mov rax,[rbp+0x570]                           
  6725634  mov [rdi],rax                                 
  6725637  lea rcx,[rdi+8]                               
  672563b  lea rdx,[rbp+0x578]                           
  6725642  call 0xE869FF0                                ; -> sub_e869ff0
  6725647  nop                                           
  6725648  mov rax,[rbp+0x5F0]                           
  672564f  mov [rdi+0x80],rax                            
  6725656  mov qword ptr [rbp+0x5F0],0                   
  6725661  add qword ptr [r14+0x770],0x88                
  672566c  jmp 0x6725C99                                 ; -> loc_6725c99
```

Interpretation: continuation of Phase 7's TLS seq at 0x672558d: `mov rax,[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. Count calc: `eax=[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x152],ax`. `rcx=&[r14+0x780]`; `rdx=&[rbp+0x5F8]`; `call 0x675F3B0` (sub_675f3b0). `nop`. Count calc: `eax=[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x138],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rdi=[r14+0x770]`; `cmp rdi,[r14+0x778]`; if equal `je 0x6725C82` (-> loc_6725c82). Else: `mov rax=[rbp+0x570]`; `mov [rdi],rax`; `rcx=rdi+8`; `rdx=&[rbp+0x578]`; `call 0xE869FF0`; `nop`. `mov rax=[rbp+0x5F0]`; `mov [rdi+0x80],rax`. `mov qword ptr [rbp+0x5F0],0`. `add qword ptr [r14+0x770],0x88`. `jmp 0x6725C99` (-> loc_6725c99). Je-target block at 0x6725671: `lea rcx,[r14+0x858]` (continues next phase).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675F3B0 (sub_675f3b0, direct), 0xE869FF0 (sub_e869ff0, direct).
Fields read: [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x650] [R], [r14+0x648] [R], [rbp+0x152] [W], [r14+0x780] [R], [rbp+0x5F8] [R], [r14+0x788] [R], [rbp+0x138] [W], [0x1233E1B0] [R], [rcx] [R], [rbp+0x570] [R], [rbp+0x578] [R], [rbp+0x5F0] [R/W], [r14+0x770] [R/W], [r14+0x778] [R]. Fields written: [rbp+0x818], [rbp+0x152], [rbp+0x138], [rbp+0x5F0], [r14+0x770], [rdi] [W], [rdi+0x80] [W].

---

## Phase 9 — TLS seq (lea rcx=[r14+0x858], call 0x6760E60; rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; movzx edx,byte [rbp+0x818]; call [0xF99FFA0]); not/add eax -> [rbp+0x126]; second TLS call dl=0x4A, mov [rbp+0x818],al; lea rcx=[r14+0x648], lea rdx=[rbp+0x650], call 0x675FB30; TLS seq (mov rax=[rax+0x10], movzx edx,byte [rbp+0x818], call [0xF99FFA0]); [r14+0x650]-[r14+0x648] count calc >>3 + imul 0xFFFF8E39 -> [rbp+0x152]; lea rcx=[r14+0x780], lea rdx=[rbp+0x5F8], call 0x675F3B0; mov qword ptr [rbp+0x110],0x2005009 (0x6725671..0x672573c)

```
  6725671  lea rcx,[r14+0x858]                           
  6725678  call 0x6760E60                                ; -> sub_6760e60
  672567d  nop                                           
  672567e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725685  mov rax,[rcx]                                 
  6725688  mov rax,[rax+0x10]                            
  672568c  movzx edx,byte ptr [rbp+0x818]                
  6725693  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725699  nop                                           
  672569a  mov eax,[r14+0x858]                           
  67256a1  not eax                                       
  67256a3  add eax,[r14+0x860]                           
  67256aa  mov [rbp+0x126],ax                            
  67256b1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67256b8  mov rax,[rcx]                                 
  67256bb  mov rax,[rax+0x10]                            
  67256bf  mov dl,0x4A                                   
  67256c1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67256c7  mov [rbp+0x818],al                            
  67256cd  lea rcx,[r14+0x648]                           
  67256d4  lea rdx,[rbp+0x650]                           
  67256db  call 0x675FB30                                ; -> sub_675fb30
  67256e0  nop                                           
  67256e1  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  67256e8  mov rax,[rcx]                                 
  67256eb  mov rax,[rax+0x10]                            
  67256ef  movzx edx,byte ptr [rbp+0x818]                
  67256f6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67256fc  nop                                           
  67256fd  mov eax,[r14+0x650]                           
  6725704  sub eax,[r14+0x648]                           
  672570b  shr eax,3                                     
  672570e  imul eax,0xFFFF8E39                           
  6725714  dec eax                                       
  6725716  mov [rbp+0x152],ax                            
  672571d  lea rcx,[r14+0x780]                           
  6725724  lea rdx,[rbp+0x5F8]                           
  672572b  call 0x675F3B0                                ; -> sub_675f3b0
  6725730  nop                                           
  6725731  mov qword ptr [rbp+0x110],0x2005009           
```

Interpretation: `lea rcx,[r14+0x858]`; `call 0x6760E60` (sub_6760e60). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. `eax=[r14+0x858]`; `not eax`; `add eax,[r14+0x860]`; `mov [rbp+0x126],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rcx=&[r14+0x648]`; `rdx=&[rbp+0x650]`; `call 0x675FB30` (sub_675fb30). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`. `nop`. Count calc: `eax=[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x152],ax`. `rcx=&[r14+0x780]`; `rdx=&[rbp+0x5F8]`; `call 0x675F3B0` (sub_675f3b0). `nop`. `mov qword ptr [rbp+0x110],0x2005009` (continues next phase: 0x672573c `mov eax,[r14+0x788]`).

Callees: 0x6760E60 (sub_6760e60, direct), [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x675FB30 (sub_675fb30, direct).
Fields read: [r14+0x858] [R], [rbp+0x818] [R/W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [r14+0x860] [R], [r14+0x648] [R], [rbp+0x650] [R], [r14+0x650] [R]. Fields written: [rbp+0x126], [rbp+0x818], [rbp+0x152], [rbp+0x110].

---

## Phase 10 — count calc [r14+0x788]-[r14+0x780] >>3 + imul 0xFFFF8BA3 -> [rbp+0x138]; TLS call dl=0x4A, mov [rbp+0x818],al; mov rdi=[r14+0x770]; cmp [r14+0x778] + je loc_6725d20; copy [rbp+0x570]->[rdi], lea rcx=[rdi+8], lea rdx=[rbp+0x578], call 0xE869FF0; [rbp+0x5F0]->[rdi+0x80], zero [rbp+0x5F0], add qword [r14+0x770],0x88, jmp loc_6725d37; follow block 0x67257d0: lea rcx=[r14+0x858], call 0x6760E60, TLS seq, mov eax=[r14+0x858], not eax, add eax,[r14+0x860], mov [rbp+0x126],ax, TLS seq start mov rax=[rax+0x10] (0x672573c..0x6725817)

```
  672573c  mov eax,[r14+0x788]                           
  6725743  sub eax,[r14+0x780]                           
  672574a  shr eax,3                                     
  672574d  imul eax,0xFFFF8BA3                           
  6725753  dec eax                                       
  6725755  mov [rbp+0x138],ax                            
  672575c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725763  mov rax,[rcx]                                 
  6725766  mov rax,[rax+0x10]                            
  672576a  mov dl,0x4A                                   
  672576c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725772  mov [rbp+0x818],al                            
  6725778  mov rdi,[r14+0x770]                           
  672577f  cmp rdi,[r14+0x778]                           
  6725786  je 0x6725D20                                  ; -> loc_6725d20
  672578c  mov rax,[rbp+0x570]                           
  6725793  mov [rdi],rax                                 
  6725796  lea rcx,[rdi+8]                               
  672579a  lea rdx,[rbp+0x578]                           
  67257a1  call 0xE869FF0                                ; -> sub_e869ff0
  67257a6  nop                                           
  67257a7  mov rax,[rbp+0x5F0]                           
  67257ae  mov [rdi+0x80],rax                            
  67257b5  mov qword ptr [rbp+0x5F0],0                   
  67257c0  add qword ptr [r14+0x770],0x88                
  67257cb  jmp 0x6725D37                                 ; -> loc_6725d37
  67257d0  lea rcx,[r14+0x858]                           
  67257d7  call 0x6760E60                                ; -> sub_6760e60
  67257dc  nop                                           
  67257dd  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67257e4  mov rax,[rcx]                                 
  67257e7  mov rax,[rax+0x10]                            
  67257eb  movzx edx,byte ptr [rbp+0x818]                
  67257f2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67257f8  nop                                           
  67257f9  mov eax,[r14+0x858]                           
  6725800  not eax                                       
  6725802  add eax,[r14+0x860]                           
  6725809  mov [rbp+0x126],ax                            
  6725810  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725817  mov rax,[rcx]                                 
```

Interpretation: Count calc: `eax=[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x138],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rdi=[r14+0x770]`; `cmp rdi,[r14+0x778]`; if equal `je 0x6725D20` (-> loc_6725d20). Else: `mov rax=[rbp+0x570]`; `mov [rdi],rax`; `rcx=rdi+8`; `rdx=&[rbp+0x578]`; `call 0xE869FF0`; `nop`. `mov rax=[rbp+0x5F0]`; `mov [rdi+0x80],rax`. `mov qword ptr [rbp+0x5F0],0`. `add qword ptr [r14+0x770],0x88`. `jmp 0x6725D37` (-> loc_6725d37).
Follow block at 0x67257d0 (sequential after `jmp 0x6725D37`): `lea rcx,[r14+0x858]`; `call 0x6760E60` (sub_6760e60). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. `eax=[r14+0x858]`; `not eax`; `add eax,[r14+0x860]`; `mov [rbp+0x126],ax`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]` (continues next phase: 0x6725817).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xE869FF0 (sub_e869ff0, direct), 0x6760E60 (sub_6760e60, direct).
Fields read: [r14+0x788] [R], [r14+0x780] [R], [rbp+0x138] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x770] [R], [r14+0x778] [R], [rbp+0x570] [R], [rbp+0x578] [R], [rbp+0x5F0] [R/W], [r14+0x770] [R/W], [r14+0x858] [R], [r14+0x860] [R]. Fields written: [rbp+0x138], [rbp+0x818], [rbp+0x126], [rbp+0x5F0], [r14+0x770], [rdi] [W], [rdi+0x80] [W].

---

## Phase 11 — TLS seq tail (mov rax=[rax+0x10], mov dl=0x4A, call [0xF99FFA0], mov [rbp+0x818],al); lea rcx=[r14+0x648], lea rdx=[rbp+0x660], call 0x675FB30; TLS seq; count calc [r14+0x650]-[r14+0x648] >>3 + imul 0xFFFF8E39 -> [rbp+0x152]; lea rcx=[r14+0x780], lea rdx=[rbp+0x608], call 0x675F3B0; mov qword ptr [rbp+0x110],0x2005009; count calc [r14+0x788]-[r14+0x780] >>3 + imul 0xFFFF8BA3 -> [rbp+0x138]; TLS call dl=0x4A, mov [rbp+0x818],al; mov rdi=[r14+0x770]; cmp [r14+0x778] + je loc_6725dd7 (0x6725817..0x67258ec)

```
  6725817  mov rax,[rcx]                                 ; R a0+0x0
  672581a  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  672581e  mov dl,0x4A                                   
  6725820  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725826  mov [rbp+0x818],al                            
  672582c  lea rcx,[r14+0x648]                           
  6725833  lea rdx,[rbp+0x660]                           
  672583a  call 0x675FB30                                ; -> sub_675fb30
  672583f  nop                                           
  6725840  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725847  mov rax,[rcx]                                 
  672584a  mov rax,[rax+0x10]                            
  672584e  movzx edx,byte ptr [rbp+0x818]                
  6725855  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672585b  nop                                           
  672585c  mov eax,[r14+0x650]                           
  6725863  sub eax,[r14+0x648]                           
  672586a  shr eax,3                                     
  672586d  imul eax,0xFFFF8E39                           
  6725873  dec eax                                       
  6725875  mov [rbp+0x152],ax                            
  672587c  lea rcx,[r14+0x780]                           
  6725883  lea rdx,[rbp+0x608]                           
  672588a  call 0x675F3B0                                ; -> sub_675f3b0
  672588f  nop                                           
  6725890  mov qword ptr [rbp+0x110],0x2005009           
  672589b  mov eax,[r14+0x788]                           
  67258a2  sub eax,[r14+0x780]                           
  67258a9  shr eax,3                                     
  67258ac  imul eax,0xFFFF8BA3                           
  67258b2  dec eax                                       
  67258b4  mov [rbp+0x138],ax                            
  67258bb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67258c2  mov rax,[rcx]                                 
  67258c5  mov rax,[rax+0x10]                            
  67258c9  mov dl,0x4A                                   
  67258cb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67258d1  mov [rbp+0x818],al                            
  67258d7  mov rdi,[r14+0x770]                           
  67258de  cmp rdi,[r14+0x778]                           
  67258e5  je 0x6725DD7                                  ; -> loc_6725dd7
```

Interpretation: continuation of Phase 10's TLS seq at 0x6725810: `mov rax,[rcx]`; `mov rax,[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `mov [rbp+0x818],al`. `rcx=&[r14+0x648]`; `rdx=&[rbp+0x660]`; `call 0x675FB30` (sub_675fb30). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. Count calc: `eax=[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x152],ax`. `rcx=&[r14+0x780]`; `rdx=&[rbp+0x608]`; `call 0x675F3B0` (sub_675f3b0). `nop`. `mov qword ptr [rbp+0x110],0x2005009`. Count calc: `eax=[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x138],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rdi=[r14+0x770]`; `cmp rdi,[r14+0x778]`; if equal `je 0x6725DD7` (-> loc_6725dd7). Je-target not yet seen in H4.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675FB30 (sub_675fb30, direct), 0x675F3B0 (sub_675f3b0, direct).
Fields read: [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x648] [R], [rbp+0x660] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R], [r14+0x650] [R], [r14+0x648] [R], [rbp+0x152] [W], [r14+0x780] [R], [rbp+0x608] [R], [rbp+0x110] [W], [r14+0x788] [R], [r14+0x780] [R], [rbp+0x138] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x770] [R], [r14+0x778] [R]. Fields written: [rbp+0x818], [rbp+0x152], [rbp+0x110], [rbp+0x138], [rbp+0x818].

---

## Phase 13 — TLS seq tail continues: add [rax],al; count calc [r15+0x648]... wait: `add [rax],al`, then `sub eax,[r15+0x648]`? No: phase 13 starts `add [rax],al`; `sub eax,[r15+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x152],ax`; lea rcx=[r15+0x780], lea rdx=[rbp+0x630], call 0x675F3B0; count calc [r15+0x788]-[r15+0x780] >>3 + imul 0xFFFF8BA3 -> [rbp+0x138]; TLS call dl=0x4A, mov [rbp+0x818],al; mov rdi=[r15+0x770]; cmp [r15+0x778] + je loc_6725e8e; copy [rbp+0x5A8]->[rdi], lea rcx=[rdi+8], lea rdx=[rbp+0x5B0], call 0xE869FF0; [rbp+0x628]->[rdi+0x80], zero [rbp+0x628], add qword [r15+0x770],0x88, jmp loc_6725ea5; fall-through block at 0x6725a8e: lea rcx=[r15+0x858], call 0x6760E60, TLS seq start mov rax=[rax+0x10] (0x67259cb..0x6725aa5)

```
  67259cb  add [rax],al                                  
  67259cd  sub eax,[r15+0x648]                           
  67259d4  shr eax,3                                     
  67259d7  imul eax,0xFFFF8E39                           
  67259dd  dec eax                                       
  67259df  mov [rbp+0x152],ax                            
  67259e6  lea rcx,[r15+0x780]                           
  67259ed  lea rdx,[rbp+0x630]                           
  67259f4  call 0x675F3B0                                ; -> sub_675f3b0
  67259f9  nop                                           
  67259fa  mov eax,[r15+0x788]                           
  6725a01  sub eax,[r15+0x780]                           
  6725a08  shr eax,3                                     
  6725a0b  imul eax,0xFFFF8BA3                           
  6725a11  dec eax                                       
  6725a13  mov [rbp+0x138],ax                            
  6725a1a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725a21  mov rax,[rcx]                                 
  6725a24  mov rax,[rax+0x10]                            
  6725a28  mov dl,0x4A                                   
  6725a2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725a30  mov [rbp+0x818],al                            
  6725a36  mov rdi,[r15+0x770]                           
  6725a3d  cmp rdi,[r15+0x778]                           
  6725a44  je 0x6725E8E                                  ; -> loc_6725e8e
  6725a4a  mov rax,[rbp+0x5A8]                           
  6725a51  mov [rdi],rax                                 
  6725a54  lea rcx,[rdi+8]                               
  6725a58  lea rdx,[rbp+0x5B0]                           
  6725a5f  call 0xE869FF0                                ; -> sub_e869ff0
  6725a64  nop                                           
  6725a65  mov rax,[rbp+0x628]                           
  6725a6c  mov [rdi+0x80],rax                            
  6725a73  mov qword ptr [rbp+0x628],0                   
  6725a7e  add qword ptr [r15+0x770],0x88                
  6725a89  jmp 0x6725EA5                                 ; -> loc_6725ea5
  6725a8e  lea rcx,[r15+0x858]                           
  6725a95  call 0x6760E60                                ; -> sub_6760e60
  6725a9a  nop                                           
  6725a9b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725aa2  mov rax,[rcx]                                 
```

Interpretation: continuation of Phase 12's TLS seq tail at 0x67259cb: `add [rax],al` (rax = [rcx] from phase 12's `mov rax,[rcx]`). Then `sub eax,[r15+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x152],ax`. `rcx=&[r15+0x780]`; `rdx=&[rbp+0x630]`; `call 0x675F3B0` (sub_675f3b0). `nop`. Count calc: `eax=[r15+0x788]`; `sub eax,[r15+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x138],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `mov [rbp+0x818],al`. `rdi=[r15+0x770]`; `cmp rdi,[r15+0x778]`; if equal `je 0x6725E8E` (-> loc_6725e8e). Else: `mov rax=[rbp+0x5A8]`; `mov [rdi],rax`; `rcx=rdi+8`; `rdx=&[rbp+0x5B0]`; `call 0xE869FF0`. `nop`. `mov rax=[rbp+0x628]`; `mov [rdi+0x80],rax`. `mov qword ptr [rbp+0x628],0`. `add qword ptr [r15+0x770],0x88`. `jmp 0x6725EA5` (-> loc_6725ea5).
Fall-through block at 0x6725a8e (follows `jmp 0x6725EA5`; r15-based block): `lea rcx,[r15+0x858]`; `call 0x6760E60` (sub_6760e60). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]` (continues next phase: 0x6725aa5).

Callees: 0x675F3B0 (sub_675f3b0, direct), [0xF99FFA0] = sub_eea6040 (indirect), 0xE869FF0 (sub_e869ff0, direct), 0x6760E60 (sub_6760e60, direct).
Fields read: [rax] [R/W], [r15+0x648] [R], [rbp+0x152] [W], [r15+0x780] [R], [rbp+0x630] [R], [r15+0x788] [R], [r15+0x780] [R], [rbp+0x138] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r15+0x770] [R], [r15+0x778] [R], [rbp+0x5A8] [R], [rbp+0x5B0] [R], [rbp+0x628] [R/W], [r15+0x770] [R/W], [r15+0x858] [R]. Fields written: [rax] [W], [rbp+0x152], [rbp+0x138], [rbp+0x818], [rdi] [W], [rdi+0x80] [W], [rbp+0x628], [r15+0x770].

---

## Phase 14 — TLS seq tail (mov rax=[rax+0x10], movzx edx,byte [rbp+0x818], call [0xF99FFA0]); eax=[r15+0x858], not eax, add eax,[r15+0x860], mov [rbp+0x126],ax; TLS call dl=0x4A, mov [rbp+0x818],al; lea rcx=[r15+0x648], lea rdx=[rbp+0x698], call 0x675FB30; TLS seq; count calc [r15+0x650]-[r15+0x648] >>3 + imul 0xFFFF8E39 -> [rbp+0x152]; lea rcx=[r15+0x780], lea rdx=[rbp+0x640], call 0x675F3B0; mov qword ptr [rbp+0x110],0x2005009; count calc [r15+0x788]-[r15+0x780] >>3 + imul 0xFFFF8BA3 -> [rbp+0x138] (0x6725aa5..0x6725b79)

```
  6725aa5  mov rax,[rax+0x10]                            
  6725aa9  movzx edx,byte ptr [rbp+0x818]                
  6725ab0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725ab6  nop                                           
  6725ab7  mov eax,[r15+0x858]                           
  6725abe  not eax                                       
  6725ac0  add eax,[r15+0x860]                           
  6725ac7  mov [rbp+0x126],ax                            
  6725ace  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725ad5  mov rax,[rcx]                                 
  6725ad8  mov rax,[rax+0x10]                            
  6725adc  mov dl,0x4A                                   
  6725ade  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725ae4  mov [rbp+0x818],al                            
  6725aea  lea rcx,[r15+0x648]                           
  6725af1  lea rdx,[rbp+0x698]                           
  6725af8  call 0x675FB30                                ; -> sub_675fb30
  6725afd  nop                                           
  6725afe  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725b05  mov rax,[rcx]                                 
  6725b08  mov rax,[rax+0x10]                            
  6725b0c  movzx edx,byte ptr [rbp+0x818]                
  6725b13  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725b19  nop                                           
  6725b1a  mov eax,[r15+0x650]                           
  6725b21  sub eax,[r15+0x648]                           
  6725b28  shr eax,3                                     
  6725b2b  imul eax,0xFFFF8E39                           
  6725b31  dec eax                                       
  6725b33  mov [rbp+0x152],ax                            
  6725b3a  lea rcx,[r15+0x780]                           
  6725b41  lea rdx,[rbp+0x640]                           
  6725b48  call 0x675F3B0                                ; -> sub_675f3b0
  6725b4d  nop                                           
  6725b4e  mov qword ptr [rbp+0x110],0x2005009           
  6725b59  mov eax,[r15+0x788]                           
  6725b60  sub eax,[r15+0x780]                           
  6725b67  shr eax,3                                     
  6725b6a  imul eax,0xFFFF8BA3                           
  6725b70  dec eax                                       
  6725b72  mov [rbp+0x138],ax                            
```

Interpretation: continuation of Phase 13's TLS seq at 0x6725aa5: `mov rax,[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. `eax=[r15+0x858]`; `not eax`; `add eax,[r15+0x860]`; `mov [rbp+0x126],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rcx=&[r15+0x648]`; `rdx=&[rbp+0x698]`; `call 0x675FB30` (sub_675fb30). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. Count calc: `eax=[r15+0x650]`; `sub eax,[r15+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x152],ax`. `rcx=&[r15+0x780]`; `rdx=&[rbp+0x640]`; `call 0x675F3B0` (sub_675f3b0). `nop`. `mov qword ptr [rbp+0x110],0x2005009`. Count calc: `eax=[r15+0x788]`; `sub eax,[r15+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x138],ax` (continues next phase: 0x6725b79).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x675FB30 (sub_675fb30, direct), 0x675F3B0 (sub_675f3b0, direct).
Fields read: [rax+0x10] [R], [rbp+0x818] [R/W], [r15+0x858] [R], [r15+0x860] [R], [rbp+0x126] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r15+0x648] [R], [rbp+0x698] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R], [r15+0x650] [R], [r15+0x648] [R], [rbp+0x152] [W], [r15+0x780] [R], [rbp+0x640] [R], [rbp+0x110] [W], [r15+0x788] [R], [r15+0x780] [R], [rbp+0x138] [W]. Fields written: [rbp+0x818], [rbp+0x126], [rbp+0x818], [rbp+0x152], [rbp+0x110], [rbp+0x138].

---

## Phase 15 — TLS call dl=0x4A, mov [rbp+0x818],al; mov rdi=[r15+0x770]; cmp [r15+0x778] + je loc_6725f34; copy [rbp+0x5B8]->[rdi], lea rcx=[rdi+8], lea rdx=[rbp+0x5C0], call 0xE869FF0; [rbp+0x638]->[rdi+0x80], zero [rbp+0x638], add qword [r15+0x770],0x88, jmp loc_6725f4b; je-target block at 0x6725bed: lea rcx=[r14+0x768], mov rdx,rdi, lea r8=[rbp+0x568], call 0x6760710 (NEW direct callee sub_6760710), nop; TLS seq, mov qword ptr [rbp+0x110],0x2007009, count calc [r14+0x770]-[r14+0x768] >>3 + imul 0xFFFFF0F1 -> [rbp+0x13A], TLS seq start mov rax=[rax+0x10] (0x6725b79..0x6725c58)

```
  6725b79  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725b80  mov rax,[rcx]                                 
  6725b83  mov rax,[rax+0x10]                            
  6725b87  mov dl,0x4A                                   
  6725b89  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725b8f  mov [rbp+0x818],al                            
  6725b95  mov rdi,[r15+0x770]                           
  6725b9c  cmp rdi,[r15+0x778]                           
  6725ba3  je 0x6725F34                                  ; -> loc_6725f34
  6725ba9  mov rax,[rbp+0x5B8]                           
  6725bb0  mov [rdi],rax                                 
  6725bb3  lea rcx,[rdi+8]                               
  6725bb7  lea rdx,[rbp+0x5C0]                           
  6725bbe  call 0xE869FF0                                ; -> sub_e869ff0
  6725bc3  nop                                           
  6725bc4  mov rax,[rbp+0x638]                           
  6725bcb  mov [rdi+0x80],rax                            
  6725bd2  mov qword ptr [rbp+0x638],0                   
  6725bdd  add qword ptr [r15+0x770],0x88                
  6725be8  jmp 0x6725F4B                                 ; -> loc_6725f4b
  6725bed  lea rcx,[r14+0x768]                           
  6725bf4  mov rdx,rdi                                   
  6725bf7  lea r8,[rbp+0x568]                            
  6725bfe  call 0x6760710                                ; -> sub_6760710
  6725c03  nop                                           
  6725c04  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725c0b  mov rax,[rcx]                                 
  6725c0e  mov rax,[rax+0x10]                            
  6725c12  movzx edx,byte ptr [rbp+0x818]                
  6725c19  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725c1f  nop                                           
  6725c20  mov qword ptr [rbp+0x110],0x2007009           
  6725c2b  mov eax,[r14+0x770]                           
  6725c32  sub eax,[r14+0x768]                           
  6725c39  shr eax,3                                     
  6725c3c  imul eax,0xFFFFF0F1                           
  6725c42  dec eax                                       
  6725c44  mov [rbp+0x13A],ax                            
  6725c4b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725c52  mov rax,[rcx]                                 
  6725c55  mov rax,[rax+0x10]                            
```

Interpretation: TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `mov [rbp+0x818],al`. `rdi=[r15+0x770]`; `cmp rdi,[r15+0x778]`; if equal `je 0x6725F34` (-> loc_6725f34). Else: `mov rax=[rbp+0x5B8]`; `mov [rdi],rax`; `rcx=rdi+8`; `rdx=&[rbp+0x5C0]`; `call 0xE869FF0`. `nop`. `mov rax=[rbp+0x638]`; `mov [rdi+0x80],rax`. `mov qword ptr [rbp+0x638],0`. `add qword ptr [r15+0x770],0x88`. `jmp 0x6725F4B` (-> loc_6725f4b).
Je-target block at 0x6725bed (target of Phase 15's `je 0x6725F34`? No — this block at 0x6725bed follows `jmp 0x6725F4B`; it is the target of Phase 7's `je 0x6725BED`!). Content: `lea rcx,[r14+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x568]`; `call 0x6760710` (sub_6760710; new direct callee; args: rcx=&[r14+0x768], rdx=rdi=[r15+0x770], r8=&[rbp+0x568]). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. `mov qword ptr [rbp+0x110],0x2007009`. `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x13A],ax`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]` (continues next phase: 0x6725c58).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xE869FF0 (sub_e869ff0, direct), 0x6760710 (sub_6760710, direct, NEW).
Fields read: [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r15+0x770] [R], [r15+0x778] [R], [rbp+0x5B8] [R], [rbp+0x5C0] [R], [rbp+0x638] [R/W], [r15+0x770] [R/W], [r14+0x768] [R], [rdi] [R], [rbp+0x568] [R], [rbp+0x110] [W], [r14+0x770] [R], [r14+0x768] [R], [rbp+0x13A] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R]. Fields written: [rbp+0x818], [rdi] [W], [rbp+0x638], [rdi+0x80] [W], [r15+0x770], [rbp+0x110], [rbp+0x13A].

---

## Phase 16 — mixed block: adc [rdx+0x3F15FF4A],dh; mov [0x8188588900927],eax; add [rcx-0x75],cl; push rsi; push 0x70563B49; je loc_6725feb; inc rdx; mov [r14+0x68],rdx; jmp loc_6725ff8; je-target block at 0x6725c82 (Phase 8's je target): lea rcx=[r14+0x768], mov rdx,rdi, lea r8=[rbp+0x570], call 0x6760710; nop; TLS seq; mov qword ptr [rbp+0x110],0x2007009; count calc [r14+0x770]-[r14+0x768] >>3 + imul 0xFFFFF0F1 -> [rbp+0x13A]; TLS call dl=0x4A, mov [rbp+0x818],al; rdx=[r14+0x818]; cmp [r14+0x820] + je loc_6726079; inc rdx; mov [r14+0x818],rdx; jmp loc_6726086; block at 0x6725d20: lea rcx=[r14+0x768] (0x6725c58..0x6725d27)

```
  6725c58  adc [rdx+0x3F15FF4A],dh                       ; W a1+0x3F15FF4A
  6725c5e  mov [0x8188588900927],eax                     
  6725c67  add [rcx-0x75],cl                             ; W a0-0x75
  6725c6a  push rsi                                      
  6725c6b  push 0x70563B49                               
  6725c70  je 0x6725FEB                                  ; -> loc_6725feb
  6725c76  inc rdx                                       
  6725c79  mov [r14+0x68],rdx                            
  6725c7d  jmp 0x6725FF8                                 ; -> loc_6725ff8
  6725c82  lea rcx,[r14+0x768]                           
  6725c89  mov rdx,rdi                                   
  6725c8c  lea r8,[rbp+0x570]                            
  6725c93  call 0x6760710                                ; -> sub_6760710
  6725c98  nop                                           
  6725c99  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725ca0  mov rax,[rcx]                                 
  6725ca3  mov rax,[rax+0x10]                            
  6725ca7  movzx edx,byte ptr [rbp+0x818]                
  6725cae  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725cb4  nop                                           
  6725cb5  mov qword ptr [rbp+0x110],0x2007009           
  6725cc0  mov eax,[r14+0x770]                           
  6725cc7  sub eax,[r14+0x768]                           
  6725cce  shr eax,3                                     
  6725cd1  imul eax,0xFFFFF0F1                           
  6725cd7  dec eax                                       
  6725cd9  mov [rbp+0x13A],ax                            
  6725ce0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725ce7  mov rax,[rcx]                                 
  6725cea  mov rax,[rax+0x10]                            
  6725cee  mov dl,0x4A                                   
  6725cf0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725cf6  nop                                           
  6725cf7  mov [rbp+0x818],al                            
  6725cfd  mov rdx,[r14+0x818]                           
  6725d04  cmp rdx,[r14+0x820]                           
  6725d0b  je 0x6726079                                  ; -> loc_6726079
  6725d11  inc rdx                                       
  6725d14  mov [r14+0x818],rdx                           
  6725d1b  jmp 0x6726086                                 ; -> loc_6726086
  6725d20  lea rcx,[r14+0x768]                           
```

Interpretation: `adc [rdx+0x3F15FF4A],dh`; `mov [0x8188588900927],eax`; `add [rcx-0x75],cl`; `push rsi`; `push 0x70563B49`; `je 0x6725FEB` (-> loc_6725feb). `inc rdx`; `mov [r14+0x68],rdx`. `jmp 0x6725FF8` (-> loc_6725ff8). The opening `adc/mov/add/push/push/je` block looks like rdis stepping through embedded data or a separate path; coherent control flow resumes at 0x6725c82, the je-target of Phase 8's `je 0x6725C82`.
Block at 0x6725c82: `lea rcx,[r14+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x570]`; `call 0x6760710` (sub_6760710; args: rcx=&[r14+0x768], rdx=rdi=[r15+0x770], r8=&[rbp+0x570]). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. `mov qword ptr [rbp+0x110],0x2007009`. `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x13A],ax`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`. `nop`. `mov [rbp+0x818],al`. `rdx=[r14+0x818]`; `cmp rdx,[r14+0x820]`; if equal `je 0x6726079` (-> loc_6726079). `inc rdx`; `mov [r14+0x818],rdx`. `jmp 0x6726086` (-> loc_6726086). Block at 0x6725d20: `lea rcx,[r14+0x768]` (continues next phase: 0x6725d27).

Callees: 0x6760710 (sub_6760710, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rdx+0x3F15FF4A] [R/W], [0x8188588900927] [W], [rcx-0x75] [R/W], [r14+0x68] [W], [r14+0x768] [R], [rdi] [R], [rbp+0x570] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [rbp+0x110] [W], [r14+0x770] [R], [r14+0x768] [R], [rbp+0x13A] [W], [rbp+0x818] [R], [r14+0x818] [R/W], [r14+0x820] [R]. Fields written: [rdx+0x3F15FF4A] [W], [0x8188588900927] [W], [rcx-0x75] [W], [r14+0x68] [W], [rbp+0x110], [rbp+0x13A], [rbp+0x818], [r14+0x818].

---

## Phase 17 — block at 0x6725d27 (Phase 16's block tail): mov rdx,rdi, lea r8=[rbp+0x570], call 0x6760710; nop; TLS seq; count calc [r14+0x770]-[r14+0x768] >>3 + imul 0xFFFFF0F1 -> [rbp+0x13A]; TLS call dl=0x4A, mov [rbp+0x818],al; rdx=[r14+0x680]; cmp [r14+0x688] + je loc_67260f9; movss [rbp+0x564/0x568/0x56C]->[rdx/rdx+4/rdx+8]; add qword [r14+0x680],0xC; jmp loc_672610d; je-target block at 0x6725dd7 (Phases 11/15 target): lea rcx=[r14+0x768], mov rdx,rdi, lea r8=[rbp+0x580], call 0x6760710; nop; TLS seq start mov rax=[rax+0x10] (0x6725d27..0x6725df8)

```
  6725d27  mov rdx,rdi                                   
  6725d2a  lea r8,[rbp+0x570]                            
  6725d31  call 0x6760710                                ; -> sub_6760710
  6725d36  nop                                           
  6725d37  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725d3e  mov rax,[rcx]                                 
  6725d41  mov rax,[rax+0x10]                            
  6725d45  movzx edx,byte ptr [rbp+0x818]                
  6725d4c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725d52  nop                                           
  6725d53  mov eax,[r14+0x770]                           
  6725d5a  sub eax,[r14+0x768]                           
  6725d61  shr eax,3                                     
  6725d64  imul eax,0xFFFFF0F1                           
  6725d6a  dec eax                                       
  6725d6c  mov [rbp+0x13A],ax                            
  6725d73  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725d7a  mov rax,[rcx]                                 
  6725d7d  mov rax,[rax+0x10]                            
  6725d81  mov dl,0x4A                                   
  6725d83  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725d89  nop                                           
  6725d8a  mov [rbp+0x818],al                            
  6725d90  mov rdx,[r14+0x680]                           
  6725d97  cmp rdx,[r14+0x688]                           
  6725d9e  je 0x67260F9                                  ; -> loc_67260f9
  6725da4  movss xmm0,[rbp+0x564]                        
  6725dac  movss [rdx],xmm0                              
  6725db0  movss xmm0,[rbp+0x568]                        
  6725db8  movss [rdx+4],xmm0                            
  6725dbd  movss xmm0,[rbp+0x56C]                        
  6725dc5  movss [rdx+8],xmm0                            
  6725dca  add qword ptr [r14+0x680],0xC                 
  6725dd2  jmp 0x672610D                                 ; -> loc_672610d
  6725dd7  lea rcx,[r14+0x768]                           
  6725dde  mov rdx,rdi                                   
  6725de1  lea r8,[rbp+0x580]                            
  6725de8  call 0x6760710                                ; -> sub_6760710
  6725ded  nop                                           
  6725dee  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725df5  mov rax,[rcx]                                 
```

Interpretation: block at 0x6725d27 continues Phase 16's block tail (from `lea rcx,[r14+0x768]` at 0x6725d20): `mov rdx,rdi`; `lea r8,[rbp+0x570]`; `call 0x6760710` (sub_6760710; args: rcx=&[r14+0x768], rdx=rdi=[r15+0x770], r8=&[rbp+0x570]). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. Count calc: `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x13A],ax`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`. `nop`. `mov [rbp+0x818],al`. `rdx=[r14+0x680]`; `cmp rdx,[r14+0x688]`; if equal `je 0x67260F9` (-> loc_67260f9). Else: `movss xmm0,[rbp+0x564]`; `movss [rdx],xmm0`; `movss xmm0,[rbp+0x568]`; `movss [rdx+4],xmm0`; `movss xmm0,[rbp+0x56C]`; `movss [rdx+8],xmm0`. `add qword ptr [r14+0x680],0xC`. `jmp 0x672610D` (-> loc_672610d).
Block at 0x6725dd7 (je-target of Phase 11's `je 0x6725DD7` and Phase 15's `je 0x6725F34`? No — Phase 15's je was 0x6725F34; Phase 11's je was 0x6725DD7): `lea rcx,[r14+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x580]`; `call 0x6760710` (args: r8=&[rbp+0x580]). `nop`. `mov rcx=[0x1233E1B0]`; `rax=[rcx]` (continues next phase: 0x6725df8).

Callees: 0x6760710 (sub_6760710, direct, twice), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rdi] [R], [rbp+0x570] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R], [r14+0x770] [R], [r14+0x768] [R], [rbp+0x13A] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x680] [R/W], [r14+0x688] [R], [rbp+0x564] [R], [rbp+0x568] [R], [rbp+0x56C] [R], [r14+0x768] [R], [rdi] [R], [rbp+0x580] [R], [0x1233E1B0] [R], [rcx] [R]. Fields written: [rbp+0x13A], [rbp+0x818], [r14+0x680], [rdx] [W], [rdx+4] [W], [rdx+8] [W].

---

## Phase 18 — TLS seq tail (mov rax=[rax+0x10], movzx edx,byte [rbp+0x818], call [0xF99FFA0]); count calc [r14+0x770]-[r14+0x768] >>3 + imul 0xFFFFF0F1 -> [rbp+0x13A]; TLS call dl=0x4A, mov [rbp+0x818],al; rdx=[r14+0x680]; cmp [r14+0x688] + je loc_672618b; movss [rbp+0x570/0x574/0x578]->[rdx/rdx+4/rdx+8]; add qword [r14+0x680],0xC; jmp loc_672619f; je-target block at 0x6725e8e (Phase 13 target): lea rcx=[r15+0x768], mov rdx,rdi, lea r8=[rbp+0x5A8], call 0x6760710; nop; block at 0x6725ea5 (Phases 12/16 target): TLS seq, mov qword ptr [rbp+0x110],0x2007009, count calc start eax=[r15+0x770] (0x6725df8..0x6725ed2)

```
  6725df8  mov rax,[rax+0x10]                            
  6725dfc  movzx edx,byte ptr [rbp+0x818]                
  6725e03  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725e09  nop                                           
  6725e0a  mov eax,[r14+0x770]                           
  6725e11  sub eax,[r14+0x768]                           
  6725e18  shr eax,3                                     
  6725e1b  imul eax,0xFFFFF0F1                           
  6725e21  dec eax                                       
  6725e23  mov [rbp+0x13A],ax                            
  6725e2a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725e31  mov rax,[rcx]                                 
  6725e34  mov rax,[rax+0x10]                            
  6725e38  mov dl,0x4A                                   
  6725e3a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725e40  nop                                           
  6725e41  mov [rbp+0x818],al                            
  6725e47  mov rdx,[r14+0x680]                           
  6725e4e  cmp rdx,[r14+0x688]                           
  6725e55  je 0x672618B                                  ; -> loc_672618b
  6725e5b  movss xmm0,[rbp+0x570]                        
  6725e63  movss [rdx],xmm0                              
  6725e67  movss xmm0,[rbp+0x574]                        
  6725e6f  movss [rdx+4],xmm0                            
  6725e74  movss xmm0,[rbp+0x578]                        
  6725e7c  movss [rdx+8],xmm0                            
  6725e81  add qword ptr [r14+0x680],0xC                 
  6725e89  jmp 0x672619F                                 ; -> loc_672619f
  6725e8e  lea rcx,[r15+0x768]                           
  6725e95  mov rdx,rdi                                   
  6725e98  lea r8,[rbp+0x5A8]                            
  6725e9f  call 0x6760710                                ; -> sub_6760710
  6725ea4  nop                                           
  6725ea5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725eac  mov rax,[rcx]                                 
  6725eaf  mov rax,[rax+0x10]                            
  6725eb3  movzx edx,byte ptr [rbp+0x818]                
  6725eba  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725ec0  nop                                           
  6725ec1  mov qword ptr [rbp+0x110],0x2007009           
  6725ecc  mov eax,[r15+0x770]                           
```

Interpretation: continuation of Phase 17's block at 0x6725dd7 at 0x6725df8: `mov rax,[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. Count calc: `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x13A],ax`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `nop`. `mov [rbp+0x818],al`. `rdx=[r14+0x680]`; `cmp rdx,[r14+0x688]`; if equal `je 0x672618B` (-> loc_672618b). Else: `movss xmm0,[rbp+0x570]`; `movss [rdx],xmm0`; `movss xmm0,[rbp+0x574]`; `movss [rdx+4],xmm0`; `movss xmm0,[rbp+0x578]`; `movss [rdx+8],xmm0`. `add qword ptr [r14+0x680],0xC`. `jmp 0x672619F` (-> loc_672619f).
Block at 0x6725e8e (je-target of Phase 13's `je 0x6725E8E`): `lea rcx,[r15+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x5A8]`; `call 0x6760710` (sub_6760710; args: r8=&[rbp+0x5A8]). `nop`. Block at 0x6725ea5 (je-target of Phase 12's `je 0x6725EA5` / Phase 16 fall-through): `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. `mov qword ptr [rbp+0x110],0x2007009`. `eax=[r15+0x770]` (continues next phase: 0x6725ed2).

Callees: 0x6760710 (sub_6760710, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x770] [R], [r14+0x768] [R], [rbp+0x13A] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r14+0x680] [R/W], [r14+0x688] [R], [rbp+0x570] [R], [rbp+0x574] [R], [rbp+0x578] [R], [r15+0x768] [R], [rdi] [R], [rbp+0x5A8] [R], [rbp+0x110] [W], [r15+0x770] [R]. Fields written: [rbp+0x818], [rbp+0x13A], [rbp+0x818], [rdx] [W], [rdx+4] [W], [rdx+8] [W], [r14+0x680], [rbp+0x110].

---

## Phase 12 — [rbp+0x580]->[rdi], lea rcx=[rdi+8], lea rdx=[rbp+0x588], call 0xE869FF0; [rbp+0x600]->[rdi+0x80], zero [rbp+0x600], add qword [r14+0x770],0x88, jmp loc_6725dee; fall-through block at 0x672592f: lea rcx=[r15+0x858], call 0x6760E60, TLS seq, mov qword ptr [rbp+0x110],0x4009, not/add eax [r15+0x858]+[r15+0x860] -> [rbp+0x126], TLS call dl=0x4A, mov [rbp+0x818],al; lea rcx=[r15+0x648], lea rdx=[rbp+0x688], call 0x675FB30; TLS seq tail (0x67258ec..0x67259cb)

```
  67258ec  mov eax,[rbp+0x580]                           
  67258f2  mov [rdi],rax                                 
  67258f5  lea rcx,[rdi+8]                               
  67258f9  lea rdx,[rbp+0x588]                           
  6725900  call 0xE869FF0                                ; -> sub_e869ff0
  6725905  nop                                           
  6725906  mov rax,[rbp+0x600]                           
  672590d  mov [rdi+0x80],rax                            
  6725914  mov qword ptr [rbp+0x600],0                   
  672591f  add qword ptr [r14+0x770],0x88                
  672592a  jmp 0x6725DEE                                 ; -> loc_6725dee
  672592f  lea rcx,[r15+0x858]                           
  6725936  call 0x6760E60                                ; -> sub_6760e60
  672593b  nop                                           
  672593c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725943  mov rax,[rcx]                                 
  6725946  mov rax,[rax+0x10]                            
  672594a  movzx edx,byte ptr [rbp+0x818]                
  6725951  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725957  nop                                           
  6725958  mov qword ptr [rbp+0x110],0x4009              
  6725963  mov eax,[r15+0x858]                           
  672596a  not eax                                       
  672596c  add eax,[r15+0x860]                           
  6725973  mov [rbp+0x126],ax                            
  672597a  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  6725981  mov rax,[rcx]                                 
  6725984  mov rax,[rax+0x10]                            
  6725988  mov dl,0x4A                                   
  672598a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725990  mov [rbp+0x818],al                            
  6725996  lea rcx,[r15+0x648]                           
  672599d  lea rdx,[rbp+0x688]                           
  67259a4  call 0x675FB30                                ; -> sub_675fb30
  67259a9  nop                                           
  67259aa  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67259b1  mov rax,[rcx]                                 
  67259b4  mov rax,[rax+0x10]                            
  67259b8  movzx edx,byte ptr [rbp+0x818]                
  67259bf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67259c5  nop                                           
```

Interpretation: `eax=[rbp+0x580]`; `mov [rdi],rax`; `rcx=rdi+8`; `rdx=&[rbp+0x588]`; `call 0xE869FF0` (sub_e869ff0); `nop`. `rax=[rbp+0x600]`; `mov [rdi+0x80],rax`. `mov qword ptr [rbp+0x600],0`. `add qword ptr [r14+0x770],0x88`. `jmp 0x6725DEE` (-> loc_6725dee).
Fall-through block at 0x672592f (the `je 0x6725dd7` from Phase 11 targets a block not yet disassembled in H4; this 0x672592f block follows `jmp 0x6725DEE` sequentially): `lea rcx,[r15+0x858]`; `call 0x6760E60` (sub_6760e60; switches to base r15). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `nop`. `mov qword ptr [rbp+0x110],0x4009`. `eax=[r15+0x858]`; `not eax`; `add eax,[r15+0x860]`; `mov [rbp+0x126],ax`. TLS call: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. `rcx=&[r15+0x648]`; `rdx=&[rbp+0x688]`; `call 0x675FB30` (sub_675fb30). `nop`. TLS seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (continues next phase: 0x67259cb).

Callees: 0xE869FF0 (sub_e869ff0, direct), 0x6760E60 (sub_6760e60, direct), [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x675FB30 (sub_675fb30, direct).
Fields read: [rbp+0x580] [R], [rbp+0x588] [R], [rbp+0x600] [R/W], [r14+0x770] [R/W], [r15+0x858] [R], [rbp+0x110] [W], [rbp+0x818] [R/W], [r15+0x860] [R], [rbp+0x126] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R], [r15+0x648] [R], [rbp+0x688] [R]. Fields written: [rdi] [W], [rbp+0x600], [rdi+0x80] [W], [r14+0x770], [rbp+0x110], [rbp+0x126], [rbp+0x818].

---