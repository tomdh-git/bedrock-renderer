# U-E4-H7 (builder 0x6722cb0, function [0x6722cb0..0x672a464))

## NEXT
Phase 28 (0x6728F55..0x672901B, 40 instructions) written. 80 instructions remain in 2 phases of 40; next phase starts at 0x672901B. Continue with `rdis dis 0x672901B 40`.

## Phase 1 (0x6727AD8..0x6727BA9)
```
```
  6727ad8  lea rcx,[r14+0x8A0]                           
  6727adf  lea r8,[rbp+0x730]                            
  6727ae6  call 0x1EF6F90                                ; -> sub_1ef6f90
  6727aeb  nop                                           
  6727aec  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727af3  mov rax,[rcx]                                 
  6727af6  mov rax,[rax+0x10]                            
  6727afa  movzx edx,byte ptr [rbp+0x827]                
  6727b01  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727b07  nop                                           
  6727b08  mov qword ptr [rbp+0x2A0],1                   
  6727b13  mov eax,[r14+0x8A8]                           
  6727b1a  sub eax,[r14+0x8A0]                           
  6727b21  shr eax,1                                     
  6727b23  dec eax                                       
  6727b25  mov [rbp+0x2B0],ax                            
  6727b2c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727b33  mov rax,[rcx]                                 
  6727b36  mov rax,[rax+0x10]                            
  6727b3a  mov dl,0x4A                                   
  6727b3c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727b42  nop                                           
  6727b43  mov [rbp+0x827],al                            
  6727b49  mov rdx,[r14+0x758]                           
  6727b50  cmp rdx,[r14+0x760]                           
  6727b57  je 0x6727BE0                                  ; -> loc_6727be0
  6727b5d  lea rcx,[rbp+0x6D8]                           
  6727b64  mov eax,[rcx+0x10]                            
  6727b67  mov [rdx+0x10],eax                            
  6727b6a  movups xmm0,[rcx]                             
  6727b6d  movups [rdx],xmm0                             
  6727b70  movzx eax,byte ptr [rbp+0x6EC]                
  6727b77  mov [rdx+0x14],al                             
  6727b7a  movss xmm0,[rbp+0x6F0]                        
  6727b82  movss [rdx+0x18],xmm0                         
  6727b87  movss xmm0,[rbp+0x6F4]                        
  6727b8f  movss [rdx+0x1C],xmm0                         
  6727b94  movss xmm0,[rbp+0x6F8]                        
  6727b9c  movss [rdx+0x20],xmm0                         
  6727ba1  movss xmm0,[rbp+0x6FC]                        
```
// Phase 1: loc_6727aec entry (phase 23's `jmp 0x6727AEC` target). `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x730]`; `call 0x1EF6F90` (sub_1ef6f90; same callee as phase 25's loc_6727262 block but different r8 source [I]); `nop`. TLS seq [V]: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte ptr [rbp+0x827]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov qword ptr [rbp+0x2A0],1`. Count calc [V]: `eax=[r14+0x8A8]`; `sub eax,[r14+0x8A0]`; `shr eax,1`; `dec eax`; `mov [rbp+0x2B0],ax` → word-count-minus-1 = ((end-begin)/2)-1 at [rbp+0x2B0]. Second TLS seq [V] dl=0x4A; `mov [rbp+0x827],al`. Cursor loop head [V]: `rdx=[r14+0x758]`; `cmp rdx,[r14+0x760]`; if equal `je 0x6727BE0` (-> loc_6727be0, loop-exit path) else fall through. Record copy (0x58-byte entry, same shape as phase 26's cursor body) [V]: `lea rcx,[rbp+0x6D8]`; `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0` ([rbp+0x6D8..0x6E8]→[rdx..rdx+0x10]); `movzx eax,byte ptr [rbp+0x6EC]`; `mov [rdx+0x14],al`; `movss xmm0,[rbp+0x6F0]`; `movss [rdx+0x18],xmm0`; `movss xmm0,[rbp+0x6F4]`; `movss [rdx+0x1C],xmm0`; `movss xmm0,[rbp+0x6F8]`; `movss [rdx+0x20],xmm0`; `movss xmm0,[rbp+0x6FC]` (final load; store to [rdx+0x24] and the +0x28..+0x47 block from [rbp+0x564] continue in next phase at 0x6727BA9: `lea rax,[rbp+0x564]`).
Callees [V]: 0x1EF6F90 (sub_1ef6f90, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read [V]: [r14+0x8A0] [R], [rbp+0x730] [R via lea], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [R/W], [r14+0x8A8] [R], [rbp+0x2B0] [W], [rbp+0x827] [W], [r14+0x758] [R], [r14+0x760] [R], [rbp+0x6D8] [R], [rcx+0x10] [R], [rbp+0x6EC] [R], [rbp+0x6F0] [R], [rbp+0x6F4] [R], [rbp+0x6F8] [R], [rbp+0x6FC] [R].
Fields written [V]: [rbp+0x2A0], [rbp+0x2B0], [rdx+0x10], [rdx..rdx+0x10] (movups), [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20]; [rdx+0x24] pending in next phase.
```

## NEXT
Phase 2 (0x6727BA9..0x6727C70, 40 instructions) written. 1120 instructions remain in 28 phases of 40; next phase starts at 0x6727C70. Continue with `rdis dis 0x6727C70 40`.

## Phase 2 (0x6727BA9..0x6727C70)
```
  6727ba9  movss [rdx+0x24],xmm0                         ; W a1+0x24
  6727bae  lea rax,[rbp+0x564]                           
  6727bb5  movups xmm0,[rax+0x19C]                       
  6727bbc  movups xmm1,[rax+0x1AC]                       
  6727bc3  movups xmm2,[rax+0x1BB]                       
  6727bca  movups [rdx+0x28],xmm0                        ; W a1+0x28
  6727bce  movups [rdx+0x38],xmm1                        ; W a1+0x38
  6727bd2  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6727bd6  add qword ptr [r14+0x758],0x58                
  6727bde  jmp short 0x6727BF4                           ; -> loc_6727bf4
  6727be0  lea rcx,[r14+0x750]                           
  6727be7  lea r8,[rbp+0x6D8]                            
  6727bee  call 0x6760A80                                ; -> sub_6760a80
  6727bf3  nop                                           
  6727bf4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727bfb  mov rax,[rcx]                                 
  6727bfe  mov rax,[rax+0x10]                            
  6727c02  movzx edx,byte ptr [rbp+0x827]                
  6727c09  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727c0f  nop                                           
  6727c10  mov eax,[r14+0x758]                           
  6727c17  sub eax,[r14+0x750]                           
  6727c1e  shr eax,3                                     
  6727c21  imul eax,0xFFFF8BA3                           
  6727c27  dec eax                                       
  6727c29  mov [rbp+0x2CC],ax                            
  6727c30  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727c37  mov rax,[rcx]                                 
  6727c3a  mov rax,[rax+0x10]                            
  6727c3e  mov dl,0x4A                                   
  6727c40  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727c46  nop                                           
  6727c47  mov [rbp+0x827],al                            
  6727c4d  mov rdx,[r14+0x860]                           
  6727c54  cmp rdx,[r14+0x868]                           
  6727c5b  je short 0x6727C69                            ; -> loc_6727c69
  6727c5d  inc rdx                                       
  6727c60  mov [r14+0x860],rdx                           
  6727c67  jmp short 0x6727C76                           ; -> loc_6727c76
  6727c69  lea rcx,[r14+0x858]                           
```
// Phase 2: completes phase 1's record copy [V]: `movss [rdx+0x24],xmm0` (store to [rdx+0x24]); `lea rax,[rbp+0x564]`; `movups [rdx+0x28],xmm0`; `movups [rdx+0x38],xmm1`; `movups [rdx+0x47],xmm2` ([rbp+0x564+0x19C/0x1AC/0x1BB]→[rdx+0x28/0x38/0x47], completing the 0x58-byte record). `add qword ptr [r14+0x758],0x58` (advance cursor by 88); `jmp short 0x6727BF4` (-> loc_6727bf4, loop tail). Loop-exit block loc_6727be0 (phase 1's `je 0x6727BE0` target) [V]: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x6D8]`; `call 0x6760A80` (sub_6760a80); `nop`; falls into loc_6727bf4. loc_6727bf4: TLS seq [V] `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte ptr [rbp+0x827]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; count calc [V] `eax=[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x2CC],ax`. Second TLS seq dl=0x4A; `mov [rbp+0x827],al`. Cursor loop [V]: `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; if equal `je short 0x6727C69` (-> loc_6727c69) else `inc rdx`; `mov [r14+0x860],rdx`; `jmp short 0x6727C76` (-> loc_6727c76). Je-target loc_6727c69 [V]: `lea rcx,[r14+0x858]` (continues next phase at 0x6727C70: `call 0x6760E60`).
Callees [V]: 0x6760A80 (sub_6760a80, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read [V]: [rbp+0x564] [R], [rax+0x19C] [R], [rax+0x1AC] [R], [rax+0x1BB] [R], [r14+0x758] [R/W], [r14+0x750] [R], [rbp+0x827] [R/W], [r14+0x860] [R/W], [r14+0x868] [R], [r14+0x858] [R via lea], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R].
Fields written [V]: [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758], [rbp+0x2CC], [rbp+0x827], [r14+0x860].
```

## Phase 3 (0x6727C70..0x6727D3B)
```
  6727c70  call 0x6760E60                                ; -> sub_6760e60
  6727c75  nop                                           
  6727c76  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727c7d  mov rax,[rcx]                                 
  6727c80  mov rax,[rax+0x10]                            
  6727c84  movzx edx,byte ptr [rbp+0x827]                
  6727c8b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727c91  nop                                           
  6727c92  mov qword ptr [rbp+0x2A0],0x4009              
  6727c9d  mov eax,[r14+0x858]                           
  6727ca4  not eax                                       
  6727ca6  add eax,[r14+0x860]                           
  6727cad  mov [rbp+0x2B6],ax                            
  6727cb4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727cbb  mov rax,[rcx]                                 
  6727cbe  mov rax,[rax+0x10]                            
  6727cc2  mov dl,0x4A                                   
  6727cc4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727cca  mov [rbp+0x827],al                            
  6727cd0  lea rcx,[r14+0x648]                           
  6727cd7  lea rdx,[rbp+0x688]                           
  6727cde  call 0x675FB30                                ; -> sub_675fb30
  6727ce3  nop                                           
  6727ce4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6727ceb  mov rax,[rcx]                                 
  6727cee  mov rax,[rax+0x10]                            
  6727cf2  movzx edx,byte ptr [rbp+0x827]                
  6727cf9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6727cff  nop                                           
  6727d00  mov eax,[r14+0x650]                           
  6727d07  sub eax,[r14+0x648]                           
  6727d0e  shr eax,3                                     
  6727d11  imul eax,0xFFFF8E39                           
  6727d17  dec eax                                       
  6727d19  mov [rbp+0x2E2],ax                            
  6727d20  lea rcx,[r14+0x780]                           
  6727d27  lea rdx,[rbp+0x630]                           
  6727d2e  call 0x675F3B0                                ; -> sub_675f3b0
  6727d33  nop                                           
  6727d34  mov eax,[r14+0x788]                           
```
// Phase 3: continues phase 2's loop-exit target loc_6727c69 [V]: `call 0x6760E60` (sub_6760e60); `nop`; falls into loc_6727c76. loc_6727c76: TLS seq [V] `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte ptr [rbp+0x827]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov qword ptr [rbp+0x2A0],0x4009`. Fold [rbp+0x2B6] [V] (same ~(begin)+(end) as phase 27's [rbp+0x126]/phase 30's [rbp+0x16C]): `eax=[r14+0x858]`; `not eax`; `add eax,[r14+0x860]`; `mov [rbp+0x2B6],ax`. TLS seq dl=0x4A; `mov [rbp+0x827],al`. `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x688]`; `call 0x675FB30` (sub_675fb30); `nop`. TLS seq again; count calc [V] `eax=[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x2E2],ax` (magic divisor 0xFFFF8E39 = /7 [I], same as phase 27). `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x630]`; `call 0x675F3B0` (sub_675f3b0); `nop`; `mov eax,[r14+0x788]` (continues next phase at 0x6727D3B: `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x138],ax` per phase 28's release-block count).
Callees [V]: 0x6760E60 (sub_6760e60, direct), [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x675FB30 (sub_675fb30, direct), 0x675F3B0 (sub_675f3b0, direct).
Fields read [V]: [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [R/W], [r14+0x858] [R], [rbp+0x2B6] [W], [r14+0x860] [R], [r14+0x648] [R], [rbp+0x688] [W via lea], [r14+0x650] [R], [rbp+0x2E2] [W], [r14+0x780] [R], [rbp+0x630] [W via lea], [r14+0x788] [R].
Fields written [V]: [rbp+0x2A0], [rbp+0x2B6], [rbp+0x827], [rbp+0x2E2], [rbp+0x688] via callee sub_675fb30 (target of lea rdx), [rbp+0x630] via callee sub_675f3b0.
```

## Phase 4 (0x6727D3B..0x6727E10)
```
  6727d3b  sub eax,[r14+0x780]                           
  6727d42  shr eax,3                                     
  6727d45  imul eax,0xFFFF8BA3                           
  6727d4b  dec eax                                       
  6727d4d  mov [rbp+0x2C8],ax                            
  6727d54  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6727d5b  mov rax,[rcx]                                 
  6727d5e  mov rax,[rax+0x10]                            
  6727d62  mov dl,0x4A                                   
  6727d64  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6727d6a  mov [rbp+0x827],al                            
  6727d70  mov rdi,[r14+0x770]                           
  6727d77  cmp rdi,[r14+0x778]                           
  6727d7e  je short 0x6727DC1                            ; -> loc_6727dc1                           
  6727d80  mov rax,[rbp+0x5A8]                           
  6727d87  mov [rdi],rax                                 
  6727d8a  lea rcx,[rdi+8]                               
  6727d8e  lea rdx,[rbp+0x5B0]                           
  6727d95  call 0xE869FF0                                ; -> sub_e869ff0                           
  6727d9a  nop                                           
  6727d9b  mov rax,[rbp+0x628]                           
  6727da2  mov [rdi+0x80],rax                            
  6727da9  mov qword ptr [rbp+0x628],0                   
  6727db4  add qword ptr [r14+0x770],0x88                
  6727dbf  jmp short 0x6727DD8                           ; -> loc_6727dd8                           
  6727dc1  lea rcx,[r14+0x768]                           
  6727dc8  mov rdx,rdi                                   
  6727dcb  lea r8,[rbp+0x5A8]                            
  6727dd2  call 0x6760710                                ; -> sub_6760710                           
  6727dd7  nop                                           
  6727dd8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6727ddf  mov rax,[rcx]                                 
  6727de2  mov rax,[rax+0x10]                            
  6727de6  movzx edx,byte ptr [rbp+0x827]                
  6727ded  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6727df3  nop                                           
  6727df4  mov qword ptr [rbp+0x2A0],0x2007009           
  6727dff  mov eax,[r14+0x770]                           
  6727e06  sub eax,[r14+0x768]                           
  6727e0d  shr eax,3                                     
// Phase 4: completes phase-3's carry-in count for the [r14+0x780] array [V]: `eax=[r14+0x788]` carried from phase 3; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x2C8],ax` (magic-divide count → word at [rbp+0x2C8], divisor [I] per imul 0xFFFF8BA3). TLS seq [V] dl=0x4A: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x827],al`. Cursor append path [V]: `rdi=[r14+0x770]`; `cmp rdi,[r14+0x778]`; if equal `je short 0x6727DC1` → loc_6727dc1 grow path `lea rcx,[r14+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x5A8]`; `call 0x6760710` (sub_6760710); `nop`. Else fall-through: append 0x88-byte record at [rdi] — `mov rax,[rbp+0x5A8]`; `mov [rdi],rax`; `lea rcx,[rdi+8]`; `lea rdx,[rbp+0x5B0]`; `call 0xE869FF0` (sub_e869ff0; fills [rdi+8..0x7F] [I]); `nop`; `mov rax,[rbp+0x628]`; `mov [rdi+0x80],rax`; `mov qword ptr [rbp+0x628],0`; `add qword ptr [r14+0x770],0x88`; `jmp short 0x6727DD8`. loc_6727dd8: second TLS seq [V] (`movzx edx,byte ptr [rbp+0x827]`); `mov qword ptr [rbp+0x2A0],0x2007009`; new count begins [V]: `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3` (continues phase 5 at 0x6727E10: `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x2CA],ax`).
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xE869FF0 (sub_e869ff0, direct), 0x6760710 (sub_6760710, direct).
Fields read [V]: [r14+0x780] [R], [rbp+0x2C8] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [R/W], [r14+0x770] [R/W], [r14+0x778] [R], [rbp+0x5A8] [R], [rdi] [W], [rbp+0x5B0] [R via rdx], [rdi+8] [W via callee], [rbp+0x628] [R/W], [rdi+0x80] [W], [r14+0x768] [R], [rbp+0x2A0] [W].
Fields written [V]: [rbp+0x2C8], [rbp+0x827], [rdi], [rdi+8..0x7F] via sub_e869ff0, [rbp+0x628], [rdi+0x80], [r14+0x770], [rbp+0x2A0].
```

## Phase 5 (0x6727E10..0x6727EC8)
```
  6727e10  imul eax,0xFFFFF0F1                           
  6727e16  dec eax                                       
  6727e18  mov [rbp+0x2CA],ax                            
  6727e1f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6727e26  mov rax,[rcx]                                 
  6727e29  mov rax,[rax+0x10]                            
  6727e2d  mov dl,0x4A                                   
  6727e2f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6727e35  nop                                           
  6727e36  mov [rbp+0x827],al                            
  6727e3c  mov rdx,[r14+0x2D8]                           
  6727e43  cmp rdx,[r14+0x2E0]                           
  6727e4a  je short 0x6727E58                            ; -> loc_6727e58                           
  6727e4c  inc rdx                                       
  6727e4f  mov [r14+0x2D8],rdx                           
  6727e56  jmp short 0x6727E65                           ; -> loc_6727e65                           
  6727e58  lea rcx,[r14+0x2D0]                           
  6727e5f  call 0x6760E60                                ; -> sub_6760e60                           
  6727e64  nop                                           
  6727e65  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6727e6c  mov rax,[rcx]                                 
  6727e6f  mov rax,[rax+0x10]                            
  6727e73  movzx edx,byte ptr [rbp+0x827]                
  6727e7a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6727e80  nop                                           
  6727e81  mov eax,[r14+0x2D0]                           
  6727e88  not eax                                       
  6727e8a  add eax,[r14+0x2D8]                           
  6727e91  mov [rbp+0x32C],ax                            
  6727e98  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6727e9f  mov rax,[rcx]                                 
  6727ea2  mov rax,[rax+0x10]                            
  6727ea6  mov dl,0x4A                                   
  6727ea8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6727eae  nop                                           
  6727eaf  mov [rbp+0x827],al                            
  6727eb5  mov rdx,[r14+0x6C8]                           
  6727ebc  cmp rdx,[r14+0x6D0]                           
  6727ec3  je short 0x6727ED1                            ; -> loc_6727ed1                           
  6727ec5  inc rdx                                       
// Phase 5: completes phase-4's carry-in count [V]: `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x2CA],ax` (magic-divide count → [rbp+0x2CA], divisor [I] per imul 0xFFFFF0F1). TLS seq [V] dl=0x4A; `mov [rbp+0x827],al`. Cursor slot [r14+0x2D8] vs limit [r14+0x2E0] (single-entry, inc by 1) [V]: `mov rdx,[r14+0x2D8]`; `cmp rdx,[r14+0x2E0]`; if full `je short 0x6727E58` → loc_6727e58 `lea rcx,[r14+0x2D0]`; `call 0x6760E60` (sub_6760e60; grow/alloc [I]); `nop`. Else `inc rdx`; `mov [r14+0x2D8],rdx`; `jmp short 0x6727E65`. loc_6727e65: TLS seq [V] again (`movzx edx,byte ptr [rbp+0x827]`); fold pair [rbp+0x32C] [V] (same `not`/`add` fold as phase 3's [rbp+0x2B6]): `eax=[r14+0x2D0]`; `not eax`; `add eax,[r14+0x2D8]`; `mov [rbp+0x32C],ax`. TLS seq [V] dl=0x4A third time; new cursor loop head [V] begins: `mov rdx,[r14+0x6C8]`; `cmp rdx,[r14+0x6D0]`; if equal `je short 0x6727ED1` → loc_6727ed1 else `inc rdx` (continues phase 6 at 0x6727EC8: presumably `mov [r14+0x6C8],rdx`; record body).
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x6760E60 (sub_6760e60, direct).
Fields read [V]: [rbp+0x2CA] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [R/W], [r14+0x2D8] [R/W], [r14+0x2E0] [R], [r14+0x2D0] [R], [rbp+0x32C] [W], [r14+0x6C8] [R], [r14+0x6D0] [R].
Fields written [V]: [rbp+0x2CA], [rbp+0x827], [r14+0x2D8], [rbp+0x32C], [r14+0x6C8] (via inc rdx; store continues phase 6).
```

## Phase 6 (0x6727EC8..0x6727F8A)
```
  6727ec8  mov [r14+0x6C8],rdx                           
  6727ecf  jmp short 0x6727EDE                           ; -> loc_6727ede                           
  6727ed1  lea rcx,[r14+0x6C0]                           
  6727ed8  call 0x6760E60                                ; -> sub_6760e60                           
  6727edd  nop                                           
  6727ede  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6727ee5  mov rax,[rcx]                                 
  6727ee8  mov rax,[rax+0x10]                            
  6727eec  movzx edx,byte ptr [rbp+0x827]                
  6727ef3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6727ef9  nop                                           
  6727efa  mov rax,0x4000000002107009                    
  6727f04  mov [rbp+0x2A0],rax                           
  6727f0b  mov eax,[r14+0x6C0]                           
  6727f12  not eax                                       
  6727f14  add eax,[r14+0x6C8]                           
  6727f1b  mov [rbp+0x2D8],ax                            
  6727f22  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6727f29  mov rax,[rcx]                                 
  6727f2c  mov rax,[rax+0x10]                            
  6727f30  mov dl,0x4A                                   
  6727f32  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6727f38  nop                                           
  6727f39  mov [rbp+0x827],al                            
  6727f3f  mov rdx,[r14+0x6B0]                           
  6727f46  cmp rdx,[r14+0x6B8]                           
  6727f4d  je short 0x6727F5B                            ; -> loc_6727f5b                           
  6727f4f  inc rdx                                       
  6727f52  mov [r14+0x6B0],rdx                           
  6727f59  jmp short 0x6727F68                           ; -> loc_6727f68                           
  6727f5b  lea rcx,[r14+0x6A8]                           
  6727f62  call 0x6760E60                                ; -> sub_6760e60                           
  6727f67  nop                                           
  6727f68  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6727f6f  mov rax,[rcx]                                 
  6727f72  mov rax,[rax+0x10]                            
  6727f76  movzx edx,byte ptr [rbp+0x827]                
  6727f7d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6727f83  nop                                           
  6727f84  mov eax,[r14+0x6A8]                           
// Phase 6: completes phase-5's [r14+0x6C8] cursor increment [V]: `mov [r14+0x6C8],rdx`; `jmp short 0x6727EDE`. If full (phase 5's `je` target): loc_6727ed1 `lea rcx,[r14+0x6C0]`; `call 0x6760E60` (sub_6760e60, grow); `nop`. loc_6727ede: TLS seq [V] dl=0x4A; `mov rax,0x4000000002107009`; `mov [rbp+0x2A0],rax` (tag immediate). Fold [rbp+0x2D8] [V] (`eax=[r14+0x6C0]`; `not eax`; `add eax,[r14+0x6C8]`; `mov [rbp+0x2D8],ax`). TLS seq [V] dl=0x4A. Cursor [r14+0x6B0] vs [r14+0x6B8] (inc by 1) [V]: `mov rdx,[r14+0x6B0]`; `cmp rdx,[r14+0x6B8]`; if equal `je short 0x6727F5B` → loc_6727f5b `lea rcx,[r14+0x6A8]`; `call 0x6760E60`; `nop`. Else `inc rdx`; `mov [r14+0x6B0],rdx`; `jmp short 0x6727F68`. loc_6727f68: TLS seq [V]; `mov eax,[r14+0x6A8]` (continues phase 7 at 0x6727F8A: likely `not eax`; `add eax,[r14+0x6B0]`; `mov [rbp+0x2E0],ax` etc.).
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x6760E60 (sub_6760e60, direct, twice).
Fields read [V]: [r14+0x6C8] [R/W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [R/W], [rbp+0x2A0] [W], [r14+0x6C0] [R], [rbp+0x2D8] [W], [r14+0x6B0] [R/W], [r14+0x6B8] [R], [r14+0x6A8] [R].
Fields written [V]: [r14+0x6C8], [rbp+0x2A0], [rbp+0x2D8], [rbp+0x827], [r14+0x6B0].
```

## Phase 7 (0x6727F8A..0x6728051)
```
  6727f8a  add bh,dh                                     
  6727f8c  rol byte ptr [rcx+3],1                        ; W a0+0x3                           
  6727f8f  xchg [rax+0x66000006],dh                      
  6727f95  mov [rbp+0x2DA],eax                           
  6727f9b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6727fa2  mov rax,[rcx]                                 
  6727fa5  mov rax,[rax+0x10]                            
  6727fa9  mov dl,0x4A                                   
  6727fab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6727fb1  nop                                           
  6727fb2  mov [rbp+0x827],al                            
  6727fb8  mov rdx,[r14+0x590]                           
  6727fbf  cmp rdx,[r14+0x598]                           
  6727fc6  je short 0x6727FF6                            ; -> loc_6727ff6                           
  6727fc8  lea rax,[rdx+0x10]                            
  6727fcc  mov [rdx],rax                                 
  6727fcf  mov rax,0x100000000                           
  6727fd9  mov [rdx+8],rax                               
  6727fdd  mov rcx,rdx                                   
  6727fe0  lea rdx,[rbp+0x560]                           
  6727fe7  call 0x6764990                                ; -> sub_6764990                           
  6727fec  add qword ptr [r14+0x590],0x30                
  6727ff4  jmp short 0x672800D                           ; -> loc_672800d                           
  6727ff6  mov rcx,r14                                   
  6727ff9  add rcx,0x588                                 
  6728000  lea r8,[rbp+0x560]                            
  6728007  call 0x6765870                                ; -> sub_6765870                           
  672800c  nop                                           
  672800d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6728014  mov rax,[rcx]                                 
  6728017  mov rax,[rax+0x10]                            
  672801b  movzx edx,byte ptr [rbp+0x827]                
  6728022  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6728028  nop                                           
  6728029  mov rax,0x4000000202307009                    
  6728033  mov [rbp+0x2A0],rax                           
  672803a  mov eax,[r14+0x590]                           
  6728041  sub eax,[r14+0x588]                           
  6728048  shr eax,4                                     
  672804b  imul eax,0xFFFFAAAB                           
// Phase 7: phase-6 carry-in `mov eax,[r14+0x6A8]` lands, then 3 instructions of embedded data/jump-table slot [?] (`add bh,dh`; `rol byte ptr [rcx+3],1`; `xchg [rax+0x66000006],dh` — do not disturb eax); `mov [rbp+0x2DA],eax` [V]. TLS seq [V] dl=0x4A; `mov [rbp+0x827],al`. Cursor append path [r14+0x590] vs [r14+0x598], 0x30-byte records [V]: `mov rdx,[r14+0x590]`; `cmp rdx,[r14+0x598]`; if full `je short 0x6727FF6` → loc_6727ff6 `mov rcx,r14`; `add rcx,0x588`; `lea r8,[rbp+0x560]`; `call 0x6765870` (sub_6765870, grow [I]); `nop`. Else: `lea rax,[rdx+0x10]`; `mov [rdx],rax` ([rdx] = rdx+0x10 forward link [I]); `mov rax,0x100000000`; `mov [rdx+8],rax` (tag); `mov rcx,rdx`; `lea rdx,[rbp+0x560]`; `call 0x6764990` (sub_6764990; copies/converts [rbp+0x560..] into record [I]); `nop`; `add qword ptr [r14+0x590],0x30`; `jmp short 0x672800D`. loc_672800d: TLS seq [V]; `mov rax,0x4000000202307009`; `mov [rbp+0x2A0],rax` (tag). Count calc begins [V]: `eax=[r14+0x590]`; `sub eax,[r14+0x588]`; `shr eax,4`; `imul eax,0xFFFFAAAB` (continues phase 8 at 0x6728051: `dec eax`; `mov [rbp+0x2??],ax`).
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x6764990 (sub_6764990, direct), 0x6765870 (sub_6765870, direct).
Fields read [V]: [r14+0x6A8] [R] (carry-in), [rbp+0x2DA] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [R/W], [r14+0x590] [R/W], [r14+0x598] [R], [rbp+0x560] [R via rdx], [r14+0x588] [R].
Fields written [V]: [rbp+0x2DA], [rbp+0x827], [rdx+0x0] (=rdx+0x10), [rdx+0x8] (=0x100000000), [r14+0x590], [rbp+0x2A0].
```

## Phase 8 (0x6728051..0x67280FF)
```
  6728051  dec eax                                       
  6728053  mov [rbp+0x2F2],ax                            
  672805a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6728061  mov rax,[rcx]                                 
  6728064  mov rax,[rax+0x10]                            
  6728068  mov dl,0x4A                                   
  672806a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6728070  nop                                           
  6728071  mov [rbp+0x827],al                            
  6728077  mov rdx,[r14+8]                               
  672807b  cmp rdx,[r14+0x10]                           
  672807f  je short 0x67280A0                            ; -> loc_67280a0                           
  6728081  mov r8d,0xC8                                  
  6728087  mov rcx,rdx                                   
  672808a  lea rdx,[rbp+0x2A0]                           
  6728091  call 0xEEC6EC0                                ; -> sub_eec6ec0                           
  6728096  add qword ptr [r14+8],0xC8                    
  672809e  jmp short 0x67280B0                           ; -> loc_67280b0                           
  67280a0  mov rcx,r14                                   
  67280a3  lea r8,[rbp+0x2A0]                            
  67280aa  call 0x5ABA6D0                                ; -> sub_5aba6d0                           
  67280af  nop                                           
  67280b0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  67280b7  mov rax,[rcx]                                 
  67280ba  mov rax,[rax+0x10]                            
  67280be  movzx edx,byte ptr [rbp+0x827]                
  67280c5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  67280cb  nop                                           
  67280cc  cmp byte ptr [rbp+0x6C8],1                    
  67280d3  jne short 0x6728127                           ; -> loc_6728127                           
  67280d5  mov rcx,[rbp+0x688]                           
  67280dc  test rcx,rcx                                  
  67280df  je short 0x6728127                           ; -> loc_6728127                           
  67280e1  mov rdx,[rbp+0x698]                           
  67280e8  sub rdx,rcx                                   
  67280eb  cmp rdx,0x1000                                
  67280f2  jb short 0x6728110                           ; -> loc_6728110                           
  67280f4  mov rax,[rcx-8]                               
  67280f8  add rcx,0xFFFFFFFFFFFFFFF8                    
  67280fc  sub rcx,rax                                   
// Phase 8: completes phase-7's count [V]: `dec eax`; `mov [rbp+0x2F2],ax`. TLS seq [V] dl=0x4A; `mov [rbp+0x827],al`. Cursor append path [r14+8] vs [r14+0x10], 0xC8-byte records [V]: `mov rdx,[r14+8]`; `cmp rdx,[r14+0x10]`; if full `je short 0x67280A0` → loc_67280a0 `mov rcx,r14`; `lea r8,[rbp+0x2A0]`; `call 0x5ABA6D0` (sub_5aba6d0, grow [I]); `nop`. Else: `mov r8d,0xC8` (record size); `mov rcx,rdx` (dest); `lea rdx,[rbp+0x2A0]` (src — [rbp+0x2A0] holds tag 0x4000000202307009 from phase 7 [I]); `call 0xEEC6EC0` (sub_eec6ec0; copies 0xC8 bytes into record [I]); `add qword ptr [r14+8],0xC8`; `jmp short 0x67280B0`. loc_67280b0: TLS seq [V]; allocator fast path [I]: `cmp byte ptr [rbp+0x6C8],1`; `jne short 0x6728127`; `mov rcx,[rbp+0x688]`; `test rcx,rcx`; `je short 0x6728127`; `mov rdx,[rbp+0x698]`; `sub rdx,rcx` (available = end - cursor); `cmp rdx,0x1000`; `jb short 0x6728110`; `mov rax,[rcx-8]`; `add rcx,0xFFFFFFFFFFFFFFF8` (rcx -= 8); `sub rcx,rax` (continues phase 9 at 0x67280FF).
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect, three times), 0xEEC6EC0 (sub_eec6ec0, direct), 0x5ABA6D0 (sub_5aba6d0, direct).
Fields read [V]: [rbp+0x2F2] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [R/W], [r14+8] [R/W], [r14+0x10] [R], [rbp+0x2A0] [R via rdx], [rbp+0x6C8] [R], [rbp+0x688] [R], [rbp+0x698] [R], [rcx-8] [R].
Fields written [V]: [rbp+0x2F2], [rbp+0x827], record at [rdx..rdx+0xC7] via sub_eec6ec0, [r14+8].
```

## Phase 9 (0x67280FF..0x67281A4)
```
  67280ff  cmp rcx,0x20                                  
  6728103  jae 0x672A337                                 ; -> sub_672a337                           
  6728109  or rdx,0x27                                   
  672810d  mov rcx,rax                                   
  6728110  call 0xE935700                                ; -> sub_e935700                           
  6728115  lea rax,[rbp+0x688]                           
  672811c  movups [rax],xmm6                             
  672811f  mov qword ptr [rax+0x10],0                    
  6728127  lea rcx,[rbp+0x560]                           
  672812e  call 0x6792810                                ; -> sub_6792810                           
  6728133  mov r14,[rbp+0x760]                           
  672813a  mov edi,[rbp+0x768]                           
  6728140  test rdi,rdi                                  
  6728143  je short 0x6728186                            ; -> loc_6728186                           
  6728145  shl rdi,5                                     
  6728149  xor r15d,r15d                                 
  672814c  jmp short 0x6728159                           ; -> loc_6728159                           
  672814e  xchg ax,ax                                    
  6728150  add r15,0x20                                  
  6728154  cmp rdi,r15                                   
  6728157  je short 0x6728178                            ; -> loc_6728178                           
  6728159  mov rcx,[r14+r15+8]                           
  672815e  test rcx,rcx                                  
  6728161  je short 0x6728150                            ; -> loc_6728150                           
  6728163  lock dec dword ptr [rcx+0xC]                  
  6728167  jne short 0x6728150                           ; -> loc_6728150                           
  6728169  mov rax,[rcx]                                 
  672816c  mov rax,[rax+8]                               
  6728170  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6728176  jmp short 0x6728150                           ; -> loc_6728150                           
  6728178  mov r14,[rbp+0x760]                           
  672817f  lea r15,[rbp+0x110]                           
  6728186  lea rax,[rbp+0x770]                           
  672818d  cmp rax,r14                                   
  6728190  je short 0x67281AF                            ; -> loc_67281af                           
  6728192  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]                           
  6728199  test r14,r14                                  
  672819c  je short 0x67281AF                            ; -> loc_67281af                           
  672819e  mov rax,[rcx]                                 
  67281a1  mov rax,[rax+0x10]                            
// Phase 9: allocator fast path continuation [I] from phase 8: `cmp rcx,0x20`; if `jae 0x672A337` → sub_672a337 (slow path); `or rdx,0x27`; `mov rcx,rax`; `call 0xE935700` (sub_e935700, alloc [I]); `lea rax,[rbp+0x688]`; `movups [rax],xmm6`; `mov qword ptr [rax+0x10],0`. Then `lea rcx,[rbp+0x560]`; `call 0x6792810` (sub_6792810 [I]); `r14=[rbp+0x760]`; `edi=[rbp+0x768]`; if zero `je loc_6728186` else `shl rdi,5` (×0x20 stride). Entry destroy loop [V]: `r15=0`; loc_6728159 `rcx=[r14+r15+8]`; if null `je loc_6728150`; `lock dec dword ptr [rcx+0xC]` (refcount decrement); if nonzero `jne loc_6728150` else `mov rax,[rcx]`; `mov rax,[rax+8]`; `call qword ptr [0xF99FFA0]` (sub_eea6040 — entry destructor/finalizer); `jmp loc_6728150`; `r15+=0x20`; until `r15==rdi`. loc_6728178: `r14=[rbp+0x760]`; `lea r15,[rbp+0x110]`. loc_6728186 (empty case): `lea rax,[rbp+0x770]`; `cmp rax,r14`; `je loc_67281AF`; `rcx=[0x1233E1A8]` (second TLS slot [V]); `test r14,r14`; `je loc_67281AF`; `mov rax,[rcx]`; `mov rax,[rax+0x10]` (continues phase 10 at 0x67281A4).
Callees [V]: 0xE935700 (sub_e935700, direct), 0x6792810 (sub_6792810, direct), [0xF99FFA0] = sub_eea6040 (indirect, once).
Fields read [V]: rcx carry-in [R], [rbp+0x688] [R/W], xmm6 [R], [rbp+0x560] [R via rcx], [rbp+0x760] [R/W], [rbp+0x768] [R], [r14+r15+8] [R], [rcx+0xC] [R/W] (lock dec), [rcx] [R], [rax+8] [R], [rbp+0x770] [R], [0x1233E1A8] [R], [rcx] [R], [rax+0x10] [R].
Fields written [V]: [rbp+0x688] (xmm6 store + zeroed qword), [rbp+0x560] via sub_6792810, [rcx+0xC] (lock dec), r14, r15.
```

## Phase 10 (0x67281A4..0x672823E)
```
  67281a4  adc [rcx+rcx*4-0xE],cl                        ; W a0-0xE+idx                           
  67281a8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  67281ae  nop                                           
  67281af  mov r14,[rbp+0x7A0]                           
  67281b6  mov edi,[rbp+0x7A8]                           
  67281bc  test rdi,rdi                                  
  67281bf  je short 0x6728206                            ; -> loc_6728206                           
  67281c1  shl rdi,5                                     
  67281c5  xor r15d,r15d                                 
  67281c8  jmp short 0x67281D9                           ; -> loc_67281d9                           
  67281ca  nop [rax+rax]                                 
  67281d0  add r15,0x20                                  
  67281d4  cmp rdi,r15                                   
  67281d7  je short 0x67281F8                            ; -> loc_67281f8                           
  67281d9  mov rcx,[r14+r15+8]                           
  67281de  test rcx,rcx                                  
  67281e1  je short 0x67281D0                            ; -> loc_67281d0                           
  67281e3  lock dec dword ptr [rcx+0xC]                  
  67281e7  jne short 0x67281D0                           ; -> loc_67281d0                           
  67281e9  mov rax,[rcx]                                 
  67281ec  mov rax,[rax+8]                               
  67281f0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  67281f6  jmp short 0x67281D0                           ; -> loc_67281d0                           
  67281f8  mov r14,[rbp+0x7A0]                           
  67281ff  lea r15,[rbp+0x110]                           
  6728206  lea rax,[rbp+0x7B0]                           
  672820d  cmp rax,r14                                   
  6728210  je short 0x672822F                            ; -> loc_672822f                           
  6728212  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]                           
  6728219  test r14,r14                                  
  672821c  je short 0x672822F                            ; -> loc_672822f                           
  672821e  mov rax,[rcx]                                 
  6728221  mov rax,[rax+0x10]                            
  6728225  mov rdx,r14                                   
  6728228  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  672822e  nop                                           
  672822f  mov r14,[rbp+0x7E0]                           
  6728236  test r14,r14                                  
  6728239  je short 0x67282B5                            ; -> loc_67282b5                           
  672823b  mov rdi,[rbp+0x7E8]                           
// Phase 10: phase-9 carry-in rax=[TLS+0x10], then [?] `adc [rcx+rcx*4-0xE],cl` (embedded data slot at boundary, no flow effect); `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. loc_67281af: third destroy loop [V] over base [rbp+0x7A0] / count [rbp+0x7A8] (×0x20 stride via `shl rdi,5`): `r14=[rbp+0x7A0]`; `edi=[rbp+0x7A8]`; if zero `je short 0x6728206`; `r15=0`; loc_67281d9 `rcx=[r14+r15+8]`; if null `je loc_67281d0`; `lock dec dword ptr [rcx+0xC]` (refcount decrement); if nonzero `jne loc_67281d0` else `mov rax,[rcx]`; `mov rax,[rax+8]`; `call qword ptr [0xF99FFA0]` (entry destructor); `jmp loc_67281d0`; `r15+=0x20` until `r15==rdi`. loc_67281f8: `r14=[rbp+0x7A0]`; `lea r15,[rbp+0x110]`. loc_6728206: range-tail call [V]: `lea rax,[rbp+0x7B0]`; `cmp rax,r14`; if equal `je short 0x672822F`; else `rcx=[0x1233E1A8]` (TLS slot 2); `test r14,r14`; `je short 0x672822F`; `mov rax,[rcx]`; `mov rax,[rax+0x10]`; `mov rdx,r14`; `call qword ptr [0xF99FFA0]` (sub_eea6040 with rdx=r14); `nop`. loc_672822f: fourth loop base: `r14=[rbp+0x7E0]`; `test r14,r14`; `je short 0x67282B5`; `rdi=[rbp+0x7E8]` (continues phase 11 at 0x672823E).
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect, three times).
Fields read [V]: rax/rcx carry-in [R], [rbp+0x7A0] [R/W], [rbp+0x7A8] [R], [r14+r15+8] [R], [rcx+0xC] [R/W] (lock dec), [rcx] [R], [rax+8] [R], [rbp+0x7B0] [R via lea], [0x1233E1A8] [R], [rcx] [R], [rax+0x10] [R], r14 [R as rdx], [rbp+0x7E0] [R/W], [rbp+0x7E8] [R].
Fields written [V]: [rcx+0xC] (lock dec), r14, r15, rax.
```

## Phase 11 (0x672823E..0x67282E2)
```
  672823e  call 0x4F72824A                               ; -> data_4f72824a                           
  6728243  cmp esi,edi                                   
  6728245  jne short 0x6728259                           ; -> loc_6728259                           
  6728247  jmp short 0x672827E                           ; -> loc_672827e                           
  6728249  nop [rax]                                     ; R ret@4f72824a+0x0                           
  6728250  add r14,0x20                                  
  6728254  cmp r14,rdi                                   
  6728257  je short 0x6728277                            ; -> loc_6728277                           
  6728259  mov rcx,[r14+8]                               
  672825d  test rcx,rcx                                  
  6728260  je short 0x6728250                            ; -> loc_6728250                           
  6728262  lock dec dword ptr [rcx+0xC]                  
  6728266  jne short 0x6728250                           ; -> loc_6728250                           
  6728268  mov rax,[rcx]                                 
  672826b  mov rax,[rax+8]                               
  672826f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6728275  jmp short 0x6728250                           ; -> loc_6728250                           
  6728277  mov r14,[rbp+0x7E0]                           
  672827e  mov rdx,[rbp+0x7F0]                           
  6728285  sub rdx,r14                                   
  6728288  cmp rdx,0x1000                                
  672828f  jb short 0x67282AD                            ; -> loc_67282ad                           
  6728291  mov rax,[r14-8]                               
  6728295  add r14,0xFFFFFFFFFFFFFFF8                    
  6728299  sub r14,rax                                   
  672829c  cmp r14,0x20                                  
  67282a0  jae 0x672A337                                 ; -> sub_672a337                           
  67282a6  add rdx,0x27                                  
  67282aa  mov r14,rax                                   
  67282ad  mov rcx,r14                                   
  67282b0  call 0xE935700                                ; -> sub_e935700                           
  67282b5  mov rax,[rbp+0x558]                           
  67282bc  cmp [rbp+0x818],rax                           
  67282c3  jne 0x672889B                                 ; -> loc_672889b                           
  67282c9  mov rax,[rbp+0x808]                           
  67282d0  mov rcx,[rax+0x10]                            
  67282d4  mov eax,0x9D0                                 
  67282d9  add rcx,rax                                   
  67282dc  call 0x5ABA5C0                                ; -> sub_5aba5c0                           
  67282e1  nop                                           
// Phase 11: opens with `call 0x4F72824A` (indirect via data_4f72824a [I]) then `cmp esi,edi` — if equal skip to loc_672827E else destroy loop [V] over [r14+8] entries (×0x20 stride): `rcx=[r14+8]`; if null skip; `lock dec dword ptr [rcx+0xC]` (refcount); if nonzero skip else `mov rax,[rcx]`; `mov rax,[rax+8]`; `call qword ptr [0xF99FFA0]` (destructor); `r14+=0x20` until `r14==rdi`. loc_6728277: `r14=[rbp+0x7E0]`. loc_672827e: allocator coalesce [I]: `rdx=[rbp+0x7F0]`; `sub rdx,r14` (available); if <0x1000 `jb loc_67282AD`; else `rax=[r14-8]`; `r14-=8`; `sub r14,rax` (block size); if `r14>=0x20` `jae 0x672A337` (slow path sub_672a337) else `rdx+=0x27`; `r14=rax`. loc_67282ad: `rcx=r14`; `call 0xE935700` (sub_e935700, alloc). Then `rax=[rbp+0x558]`; `cmp [rbp+0x818],rax`; if different `jne 0x672889B` (forward exit to late section). Else `rax=[rbp+0x808]`; `rcx=[rax+0x10]`; `eax=0x9D0`; `rcx+=rax`; `call 0x5ABA5C0` (sub_5aba5c0 — the stream's namesake callee from the brief's entry note [V]); `nop` (continues phase 12 at 0x67282E2).
Callees [V]: call 0x4F72824A (data_4f72824a, indirect [I]), [0xF99FFA0] = sub_eea6040 (indirect, once), 0xE935700 (sub_e935700, direct), 0x5ABA5C0 (sub_5aba5c0, direct).
Fields read [V]: esi/edi carry-in [R], r14 [R], [r14+8] [R], [rcx+0xC] [R/W] (lock dec), [rcx] [R], [rax+8] [R], [rbp+0x7E0] [R/W], [rbp+0x7F0] [R], [r14-8] [R], [rbp+0x558] [R], [rbp+0x818] [R], [rbp+0x808] [R], [rax+0x10] [R].
Fields written [V]: r14, rdx, [rbp+0x818]? no (cmp only), rax (phase 12 carry).
```

## Phase 12 (0x67282E2..0x67283A6)
```
  67282e2  mov r14,rax                                   
  67282e5  lea rax,[rbp+0x568]                           
  67282ec  movups [rax+0xB0],xmm6                        
  67282f3  movups [rax+0xA0],xmm6                        
  67282fa  movups [rax+0x90],xmm6                        
  6728301  movups [rax+0x80],xmm6                        
  6728308  movups [rax+0x70],xmm6                        
  672830c  movups [rax+0x60],xmm6                        
  6728310  movups [rax+0x50],xmm6                        
  6728314  movups [rax+0x40],xmm6                        
  6728318  movups [rax+0x30],xmm6                        
  672831c  movups [rax+0x20],xmm6                        
  6728320  movups [rax+0x10],xmm6                        
  6728324  movups [rax],xmm6                             
  6728327  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  672832e  mov rax,[rcx]                                 
  6728331  mov rax,[rax+0x10]                            
  6728335  mov dl,0x4A                                   
  6728337  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  672833d  nop                                           
  672833e  mov [rbp+0x818],al                            
  6728344  mov rdx,[r14+0x8A8]                           
  672834b  cmp rdx,[r14+0x8B0]                           
  6728352  je short 0x6728368                            ; -> loc_6728368                           
  6728354  movzx eax,word ptr [rbp+0x500]                
  672835b  mov [rdx],ax                                  
  672835e  add qword ptr [r14+0x8A8],2                   
  6728366  jmp short 0x672837C                           ; -> loc_672837c                           
  6728368  lea rcx,[r14+0x8A0]                           
  672836f  lea r8,[rbp+0x500]                            
  6728376  call 0x1EF6F90                                ; -> sub_1ef6f90                           
  672837b  nop                                           
  672837c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  6728383  mov rax,[rcx]                                 
  6728386  mov rax,[rax+0x10]                            
  672838a  movzx edx,byte ptr [rbp+0x818]                
  6728391  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  6728397  nop                                           
  6728398  mov qword ptr [rbp+0x560],1                   
  67283a3  mov eax,[r14+0x8A8]                           
// Phase 12: phase-11 carry-in rax → `mov r14,rax`; zero 0xC0 bytes at [rbp+0x568..0x628] with 13× `movups` (xmm6 presumed zero) [V]. TLS seq [V] dl=0x4A; `mov [rbp+0x818],al`. Word append to [r14+0x8A8] buffer (2-byte records, limit [r14+0x8B0]) [V]: `mov rdx,[r14+0x8A8]`; `cmp rdx,[r14+0x8B0]`; if full `je short 0x6728368` → loc_6728368 `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x500]`; `call 0x1EF6F90` (sub_1ef6f90 — same grow helper as phase 1); `nop`. Else `movzx eax,word ptr [rbp+0x500]`; `mov [rdx],ax`; `add qword ptr [r14+0x8A8],2`; `jmp loc_672837c`. loc_672837c: TLS seq [V] (edx=[rbp+0x818]); `mov qword ptr [rbp+0x560],1`; `mov eax,[r14+0x8A8]` (continues phase 13 at 0x67283A6: likely `sub eax,[r14+0x8A0]`; `shr eax,1`; `dec eax` → word count, echoing phase 1's count at [rbp+0x2B0]).
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x1EF6F90 (sub_1ef6f90, direct).
Fields read [V]: rax carry-in [R], [rbp+0x568] [W via lea], xmm6 [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827]? no — [rbp+0x818] [W], [rbp+0x500] [R], [r14+0x8A8] [R/W], [r14+0x8B0] [R], [r14+0x8A0] [R via rcx].
Fields written [V]: [rbp+0x568..0x628] (13× movups), [rbp+0x818], [rdx] (word), [r14+0x8A8].
```

## Phase 13 (0x67283A6..0x672846C)
```
  67283a6  test al,8                                     
  67283a8  add [rax],al                                  
  67283aa  sub eax,[r14+0x8A0]                           
  67283b1  shr eax,1                                     
  67283b3  dec eax                                       
  67283b5  mov [rbp+0x570],ax                            
  67283bc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]                           
  67283c3  mov rax,[rcx]                                 
  67283c6  mov rax,[rax+0x10]                            
  67283ca  mov dl,0x4A                                   
  67283cc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040                           
  67283d2  nop                                           
  67283d3  mov [rbp+0x818],al                            
  67283d9  mov rdx,[r14+0x758]                           
  67283e0  cmp rdx,[r14+0x760]                           
  67283e7  je short 0x6728465                            ; -> loc_6728465                           
  67283e9  lea rcx,[rbp+0x4A8]                           
  67283f0  mov eax,[rcx+0x10]                            
  67283f3  mov [rdx+0x10],eax                            
  67283f6  movups xmm0,[rcx]                             
  67283f9  movups [rdx],xmm0                             
  67283fc  movzx eax,byte ptr [rbp+0x4BC]                
  6728403  mov [rdx+0x14],al                             
  6728406  movss xmm0,[rbp+0x4C0]                        
  672840e  movss [rdx+0x18],xmm0                         
  6728413  movss xmm0,[rbp+0x4C4]                        
  672841b  movss [rdx+0x1C],xmm0                         
  6728420  movss xmm0,[rbp+0x4C8]                        
  6728428  movss [rdx+0x20],xmm0                         
  672842d  movss xmm0,[rbp+0x4CC]                        
  6728435  movss [rdx+0x24],xmm0                         
  672843a  movups xmm0,[rbx+0x80]                        
  6728441  movups xmm1,[rbx+0x90]                        
  6728448  movups xmm2,[rbx+0x9F]                        
  672844f  movups [rdx+0x28],xmm0                        
  6728453  movups [rdx+0x38],xmm1                        
  6728457  movups [rdx+0x47],xmm2                        
  672845b  add qword ptr [r14+0x758],0x58                
  6728463  jmp short 0x6728479                           ; -> loc_6728479                           
  6728465  lea rcx,[r14+0x750]                           
// Phase 13: phase-12 carry-in eax=[r14+0x8A8]; `test al,8`; `add [rax],al` [?] (boundary flag/mutate slot). Word-count decode echoing phase 1 [V]: `sub eax,[r14+0x8A0]`; `shr eax,1`; `dec eax`; `mov [rbp+0x570],ax`. TLS seq [V] dl=0x4A; `mov [rbp+0x818],al`. Cursor [r14+0x758] vs [r14+0x760], 0x58-byte records [V]: `rdx=[r14+0x758]`; `cmp rdx,[r14+0x760]`; if equal `je short 0x6728465` → loc_6728465 exit (continues phase 14). Else record copy from [rbp+0x4A8] (same shape as phase 1/2's [rbp+0x6D8] record): `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0`; `movzx eax,byte ptr [rbp+0x4BC]`; `mov [rdx+0x14],al`; `movss xmm0,[rbp+0x4C0/4C4/4C8/4CC]` → `[rdx+0x18/0x1C/0x20/0x24]`; then `movups xmm0,[rbx+0x80]`; `movups xmm1,[rbx+0x90]`; `movups xmm2,[rbx+0x9F]`; `movups [rdx+0x28],xmm0`; `movups [rdx+0x38],xmm1`; `movups [rdx+0x47],xmm2` (record complete; sources [rbp+0x4A8..] and [rbx+0x80..] [V]); `add qword ptr [r14+0x758],0x58`; `jmp short 0x6728479`.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect, once).
Fields read [V]: eax/al carry-in [R], [rax] [R/W], [r14+0x8A8] [R], [r14+0x8A0] [R], [rbp+0x570] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [W], [r14+0x758] [R/W], [r14+0x760] [R], [rbp+0x4A8] [R], [rcx+0x10] [R], [rbp+0x4BC] [R], [rbp+0x4C0] [R], [rbp+0x4C4] [R], [rbp+0x4C8] [R], [rbp+0x4CC] [R], [rbx+0x80] [R], [rbx+0x90] [R], [rbx+0x9F] [R].
Fields written [V]: [rbp+0x570], [rbp+0x818], [rdx+0x10], [rdx..rdx+0x10], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758].
```

## Phase 14 (0x672846C..0x6728526)
```
  672846c  lea r8,[rbp+0x4A8]                            
  6728473  call 0x6760A80                                ; -> sub_6760a80
  6728478  nop                                           
  6728479  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728480  mov rax,[rcx]                                 
  6728483  mov rax,[rax+0x10]                            
  6728487  movzx edx,byte ptr [rbp+0x818]                
  672848e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728494  nop                                           
  6728495  mov eax,[r14+0x758]                           
  672849c  sub eax,[r14+0x750]                           
  67284a3  shr eax,3                                     
  67284a6  imul eax,0xFFFF8BA3                           
  67284ac  dec eax                                       
  67284ae  mov [rbp+0x58C],ax                            
  67284b5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67284bc  mov rax,[rcx]                                 
  67284bf  mov rax,[rax+0x10]                            
  67284c3  mov dl,0x4A                                   
  67284c5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67284cb  nop                                           
  67284cc  mov [rbp+0x818],al                            
  67284d2  mov rdx,[r14+0x860]                           
  67284d9  cmp rdx,[r14+0x868]                           
  67284e0  je short 0x67284EE                            ; -> loc_67284ee
  67284e2  inc rdx                                       
  67284e5  mov [r14+0x860],rdx                           
  67284ec  jmp short 0x67284FB                           ; -> loc_67284fb
loc_67284ee:  ; from 67284e0
  67284ee  lea rcx,[r14+0x858]                           
  67284f5  call 0x6760E60                                ; -> sub_6760e60
  67284fa  nop                                           
loc_67284fb:  ; from 67284ec
  67284fb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728502  mov rax,[rcx]                                 
  6728505  mov rax,[rax+0x10]                            
  6728509  movzx edx,byte ptr [rbp+0x818]                
  6728510  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728516  nop                                           
  6728517  mov eax,[r14+0x858]                           
  672851e  not eax                                       
  6728520  add eax,[r14+0x860]                           
// Phase 14: completes phase-13 exit block loc_6728465 [V]: `lea r8,[rbp+0x4A8]`; `call 0x6760A80` (sub_6760A80 processes record [rbp+0x4A8] at cursor [r14+0x750], mirroring phase 2's exit). TLS seq dl=[rbp+0x818] (carry from phase 13) via [0xF99FFA0]=sub_eea6040 [V]. Cursor count [V]: `mov eax,[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x58C],ax` (same shrink-imul-dec idiom as phase 2's [rbp+0x2CC], here → [rbp+0x58C]). TLS seq dl=0x4A → `mov [rbp+0x818],al` [V]. Cursor [r14+0x860] vs [r14+0x868] (inc-by-1 stride, phase-5-style) [V]: `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; if equal `je short 0x67284EE` → loc_67284ee: `lea rcx,[r14+0x858]`; `call 0x6760E60` (grow); falls into loc_67284fb; else `inc rdx`; `mov [r14+0x860],rdx`; `jmp short 0x67284FB` → loc_67284fb. At loc_67284fb: TLS seq dl=[rbp+0x818] via sub_eea6040 [V]; then `mov eax,[r14+0x858]`; `not eax`; `add eax,[r14+0x860]` — fold not/add, result continues into phase 15 [I].
Callees [V]: 0x6760A80 (direct), [0xF99FFA0] = sub_eea6040 (indirect ×3), 0x6760E60 (direct, grow path).
Fields read [V]: [rbp+0x4A8] (lea address only), [0x1233E1B0] [R]×3, [rcx] [R]×3, [rax+0x10] [R]×3, [rbp+0x818] [R]×2 (movzx edx), [r14+0x758] [R], [r14+0x750] [R], [rbp+0x58C] [W], [r14+0x860] [R/W], [r14+0x868] [R], [r14+0x858] [R].
Fields written [V]: [r14+0x750] via call sub_6760A80 [I] (record consumed), [rbp+0x818] [W]×2, [rbp+0x58C] [W], [r14+0x860] [W].
```

## Phase 15 (0x6728526..0x67285E9)
```
  6728526  add [rsi-0x77],ah                             
  6728529  test [rsi+5],esi                              
  672852c  add [rax],al                                  
  672852e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728535  mov rax,[rcx]                                 
  6728538  mov rax,[rax+0x10]                            
  672853c  mov dl,0x4A                                   
  672853e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728544  mov [rbp+0x818],al                            
  672854a  lea rcx,[r14+0x648]                           
  6728551  lea rdx,[rbp+0x458]                           
  6728558  call 0x675FB30                                ; -> sub_675fb30
  672855d  nop                                           
  672855e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728565  mov rax,[rcx]                                 
  6728568  mov rax,[rax+0x10]                            
  672856c  movzx edx,byte ptr [rbp+0x818]                
  6728573  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728579  nop                                           
  672857a  mov eax,[r14+0x650]                           
  6728581  sub eax,[r14+0x648]                           
  6728588  shr eax,3                                     
  672858b  imul eax,0xFFFF8E39                           
  6728591  dec eax                                       
  6728593  mov [rbp+0x5A2],ax                            
  672859a  lea rcx,[r14+0x780]                           
  67285a1  lea rdx,[rbp+0x400]                           
  67285a8  call 0x675F3B0                                ; -> sub_675f3b0
  67285ad  nop                                           
  67285ae  mov qword ptr [rbp+0x560],0x2005009           
  67285b9  mov eax,[r14+0x788]                           
  67285c0  sub eax,[r14+0x780]                           
  67285c7  shr eax,3                                     
  67285ca  imul eax,0xFFFF8BA3                           
  67285d0  dec eax                                       
  67285d2  mov [rbp+0x588],ax                            
  67285d9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67285e0  mov rax,[rcx]                                 
  67285e3  mov rax,[rax+0x10]                            
  67285e7  mov dl,0x4A                                   
// Phase 15: opens with embedded jump-table slot [?]: `add [rsi-0x77],ah`; `test [rsi+5],esi`; `add [rax],al` (same shape as phase 7's slot). TLS seq dl=0x4A via [0xF99FFA0]=sub_eea6040 → `mov [rbp+0x818],al` [V]. `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x458]`; `call 0x675FB30` [V] (mirrors phase 3's [rbp+0x688]/0x675FB30, here dst/src [rbp+0x458] area [I]). TLS seq dl=[rbp+0x818] via sub_eea6040 [V]. Count #1 [V] (phase-3 idiom, imul /7): `mov eax,[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x5A2],ax`. `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x400]`; `call 0x675F3B0` [V] (mirrors phase 3's [rbp+0x630]/0x675F3B0, here [rbp+0x400] area [I]). Tag [V]: `mov qword ptr [rbp+0x560],0x2005009` (phase 3 used 0x4009 at [rbp+0x2A0]). Count #2 [V] (phase-2 idiom): `mov eax,[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x588],ax` (phase 28-style → [rbp+0x588] here). Ends `mov dl,0x4A` → TLS call continues into phase 16.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×2), 0x675FB30 (direct), 0x675F3B0 (direct).
Fields read [V]: [rsi-0x77] [R/W] [?], [rsi+5] [R] [?], [rax] [R/W] [?] (embedded slot), [0x1233E1B0] [R]×2, [rcx] [R]×2, [rax+0x10] [R]×2, [rbp+0x818] [R] (movzx edx, second TLS), [r14+0x650] [R], [r14+0x648] [R], [r14+0x788] [R], [r14+0x780] [R].
Fields written [V]: [rbp+0x818] [W]×2, [rbp+0x5A2] [W], [rbp+0x560] [W] (imm 0x2005009), [rbp+0x588] [W].
```

## Phase 17 (0x67286B3..0x6728768)
```
  67286b3  or [rax],al                                   
  67286b5  add [rcx-0x75],cl                             ; W a0-0x75
  67286b8  xchg esi,eax                                  
  67286b9  fadd st,dword ptr [rdx]                       ; W a1+0x0
  67286bb  add [rax],al                                  
  67286bd  cmp rdx,[r14+0x2E0]                           
  67286c4  je short 0x67286D2                            ; -> loc_67286d2
  67286c6  inc rdx                                       
  67286c9  mov [r14+0x2D8],rdx                           
  67286d0  jmp short 0x67286DF                           ; -> loc_67286df
loc_67286d2:  ; from 67286c4
  67286d2  lea rcx,[r14+0x2D0]                           
  67286d9  call 0x6760E60                                ; -> sub_6760e60
  67286de  nop                                           
loc_67286df:  ; from 67286d0
  67286df  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67286e6  mov rax,[rcx]                                 
  67286e9  mov rax,[rax+0x10]                            
  67286ed  movzx edx,byte ptr [rbp+0x818]                
  67286f4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67286fa  nop                                           
  67286fb  mov rax,0x4000000002007009                    
  6728705  mov [rbp+0x560],rax                           
  672870c  mov eax,[r14+0x2D0]                           
  6728713  not eax                                       
  6728715  add eax,[r14+0x2D8]                           
  672871c  mov [rbp+0x5EC],ax                            
  6728723  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672872a  mov rax,[rcx]                                 
  672872d  mov rax,[rax+0x10]                            
  6728731  mov dl,0x4A                                   
  6728733  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728739  nop                                           
  672873a  mov [rbp+0x818],al                            
  6728740  mov rdx,[r14+0x6C8]                           
  6728747  cmp rdx,[r14+0x6D0]                           
  672874e  je short 0x672875C                            ; -> loc_672875c
  6728750  inc rdx                                       
  6728753  mov [r14+0x6C8],rdx                           
  672875a  jmp short 0x6728769                           ; -> loc_6728769
loc_672875c:  ; from 672874e
  672875c  lea rcx,[r14+0x6C0]                           
  6728763  call 0x6760E60                                ; -> sub_6760e60
// Phase 17: opens with embedded jump-table slot [?] (5 instr): `or [rax],al`; `add [rcx-0x75],cl`; `xchg esi,eax`; `fadd st,dword ptr [rdx]`; `add [rax],al` (mirrors phase 7's slot, here with FPU op). Cursor [r14+0x2D8] vs [r14+0x2E0] inc-by-1 [V] (mirrors phase 5/6): `cmp rdx,[r14+0x2E0]`; if equal `je short 0x67286D2` → loc_67286d2: `lea rcx,[r14+0x2D0]`; `call 0x6760E60` (grow); falls into loc_67286df. Else `inc rdx`; `mov [r14+0x2D8],rdx`; `jmp short 0x67286DF`. TLS seq dl=[rbp+0x818] via [0xF99FFA0]=sub_eea6040 [V]. Tag [V]: `mov rax,0x4000000002007009`; `mov [rbp+0x560],rax` (phase 6 used 0x4000000002107009 at [rbp+0x2A0]). Fold not/add [V]: `mov eax,[r14+0x2D0]`; `not eax`; `add eax,[r14+0x2D8]`; `mov [rbp+0x5EC],ax` (phase 6 folded → [rbp+0x2D8]). TLS seq dl=0x4A → `mov [rbp+0x818],al` [V]. Cursor [r14+0x6C8] vs [r14+0x6D0] inc-by-1 [V] (mirrors phase 5 loop head): `rdx=[r14+0x6C8]`; `cmp rdx,[r14+0x6D0]`; if equal `je short 0x672875C` → loc_672875c: `lea rcx,[r14+0x6C0]`; `call 0x6760E60` (grow; phase ends at the call, nop+tail continue phase 18). Else `inc rdx`; `mov [r14+0x6C8],rdx`; `jmp short 0x6728769` → loc_6728769 (continues phase 18).
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×2), 0x6760E60 (direct ×2, grow paths).
Fields read [V]: embedded slot [rax] [R/W] [?], [rcx-0x75] [R/W] [?], [rdx] [R] [?] (fadd), [0x1233E1B0] [R]×2, [rcx] [R]×2, [rax+0x10] [R]×2, [rbp+0x818] [R]×2 (movzx edx), [r14+0x2E0] [R], [r14+0x2D8] [R/W], [r14+0x2D0] [R], [rbp+0x5EC] [W], [r14+0x6C8] [R/W], [r14+0x6D0] [R], [rbp+0x560] [W].
Fields written [V]: [rbp+0x818] [W]×2, [rbp+0x560] [W] (imm tag), [rbp+0x5EC] [W], [r14+0x2D8] [W].
```

## Phase 18 (0x6728768..0x6728829)
```
  6728768  nop                                           
  6728769  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728770  mov rax,[rcx]                                 
  6728773  mov rax,[rax+0x10]                            
  6728777  movzx edx,byte ptr [rbp+0x818]                
  672877e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728784  nop                                           
  6728785  mov eax,[r14+0x6C0]                           
  672878c  not eax                                       
  672878e  add eax,[r14+0x6C8]                           
  6728795  mov [rbp+0x598],ax                            
  672879c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67287a3  mov rax,[rcx]                                 
  67287a6  mov rax,[rax+0x10]                            
  67287aa  mov dl,0x4A                                   
  67287ac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67287b2  nop                                           
  67287b3  mov [rbp+0x818],al                            
  67287b9  mov rdx,[r14+0x6B0]                           
  67287c0  cmp rdx,[r14+0x6B8]                           
  67287c7  je short 0x67287D5                            ; -> loc_67287d5
  67287c9  inc rdx                                       
  67287cc  mov [r14+0x6B0],rdx                           
  67287d3  jmp short 0x67287E5                           ; -> loc_67287e5
loc_67287d5:  ; from 67287c7
  67287d5  mov rcx,r14                                   
  67287d8  add rcx,0x6A8                                 
  67287df  call 0x6760E60                                ; -> sub_6760e60
  67287e4  nop                                           
loc_67287e5:  ; from 67287d3
  67287e5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67287ec  mov rax,[rcx]                                 
  67287ef  mov rax,[rax+0x10]                            
  67287f3  movzx edx,byte ptr [rbp+0x818]                
  67287fa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728800  nop                                           
  6728801  mov rax,0x4000000002307009                    
  672880b  mov [rbp+0x560],rax                           
  6728812  mov eax,[r14+0x6A8]                           
  6728819  not eax                                       
  672881b  add eax,[r14+0x6B0]                           
  6728822  mov [rbp+0x59A],ax                            
// Phase 18: `nop`; TLS dl=[rbp+0x818] via [0xF99FFA0]=sub_eea6040 → `mov [rbp+0x818],al` [V]. Fold not/add [V]: `mov eax,[r14+0x6C0]`; `not eax`; `add eax,[r14+0x6C8]`; `mov [rbp+0x598],ax` (phase 6 folded → [rbp+0x2D8]). TLS dl=0x4A → [rbp+0x818]=al [V]. Cursor [r14+0x6B0] vs [r14+0x6B8] inc-by-1 [V]: `rdx=[r14+0x6B0]`; `cmp rdx,[r14+0x6B8]`; if equal `je short 0x67287D5` → loc_67287d5: `mov rcx,r14`; `add rcx,0x6A8` (rcx=r14+0x6A8); `call 0x6760E60` (grow). Else `inc rdx`; `mov [r14+0x6B0],rdx`; `jmp short 0x67287E5`. TLS dl=[rbp+0x818] via sub_eea6040 [V]. Tag [V]: `mov rax,0x4000000002307009`; `mov [rbp+0x560],rax` (phase 7 used 0x4000000202307009 at [rbp+0x2A0]). Fold not/add [V]: `mov eax,[r14+0x6A8]`; `not eax`; `add eax,[r14+0x6B0]`; `mov [rbp+0x59A],ax` (phase 7 folded → [rbp+0x2DA]); continues phase 19.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×3), 0x6760E60 (direct, grow path).
Fields read [V]: [0x1233E1B0] [R]×3, [rcx] [R]×3, [rax+0x10] [R]×3, [rbp+0x818] [R]×3 (movzx edx), [r14+0x6C0] [R], [r14+0x6C8] [R], [rbp+0x598] [W], [r14+0x6B0] [R/W], [r14+0x6B8] [R], [rbp+0x560] [W], [r14+0x6A8] [R], [rbp+0x59A] [W].
Fields written [V]: [rbp+0x818] [W]×3, [rbp+0x598] [W], [r14+0x6B0] [W], [rbp+0x560] [W] (imm tag), [rbp+0x59A] [W].
```

## Phase 19 (0x6728829..0x67288E6)
```
  6728829  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728830  mov rax,[rcx]                                 
  6728833  mov rax,[rax+0x10]                            
  6728837  mov dl,0x4A                                   
  6728839  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672883f  nop                                           
  6728840  mov [rbp+0x818],al                            
  6728846  mov rdx,[r14+8]                               
  672884a  cmp rdx,[r14+0x10]                            
  672884e  je short 0x672886F                            ; -> loc_672886f
  6728850  mov r8d,0xC8                                  
  6728856  mov rcx,rdx                                   
  6728859  lea rdx,[rbp+0x560]                           
  6728860  call 0xEEC6EC0                                ; -> sub_eec6ec0
  6728865  add qword ptr [r14+8],0xC8                    
  672886d  jmp short 0x672887F                           ; -> loc_672887f
loc_672886f:  ; from 672884e
  672886f  mov rcx,r14                                   
  6728872  lea r8,[rbp+0x560]                            
  6728879  call 0x5ABA6D0                                ; -> sub_5aba6d0
  672887e  nop                                           
loc_672887f:  ; from 672886d
  672887f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728886  mov rax,[rcx]                                 
  6728889  mov rax,[rax+0x10]                            
  672888d  movzx edx,byte ptr [rbp+0x818]                
  6728894  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672889a  nop                                           
  672889b  lea rcx,[rbp+0x370]                           
  67288a2  call 0x67E1840                                ; -> sub_67e1840
  67288a7  jmp 0x672A198                                 ; -> loc_672a198 (forward, skips following block)
  67288ac  lea rcx,[r14+0x8A0]                           
  67288b3  lea r8,[rbp+0x720]                            
  67288ba  call 0x1EF6F90                                ; -> sub_1ef6f90
  67288bf  nop                                           
  67288c0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67288c7  mov rax,[rcx]                                 
  67288ca  mov rax,[rax+0x10]                            
  67288ce  movzx edx,byte ptr [rbp+0x827]                
  67288d5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67288db  nop                                           
  67288dc  mov qword ptr [rbp+0x2A0],1                   
// Phase 19: completes phase-18 TLS tail [V]: `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. Cursor [r14+8] vs [r14+0x10], 0xC8-byte records [V] (mirrors phase 8): `rdx=[r14+8]`; `cmp rdx,[r14+0x10]`; if equal `je short 0x672886F` → loc_672886f: `mov rcx,r14`; `lea r8,[rbp+0x560]`; `call 0x5ABA6D0` (grow). Else: `mov r8d,0xC8`; `mov rcx,rdx` (dest=cursor); `lea rdx,[rbp+0x560]` (src=tag qword set by phase 18); `call 0xEEC6EC0` (copy 0xC8 bytes [I]); `add qword ptr [r14+8],0xC8`; `jmp short 0x672887F`. TLS dl=[rbp+0x818] via sub_eea6040 → [rbp+0x818]=al [V]. New sequence [V]: `lea rcx,[rbp+0x370]`; `call 0x67E1840` (new callee, target [rbp+0x370] buffer [I]); `jmp 0x672A198` (forward jump to late function region, skips the block below). Linear-follow block (not reached from this phase's flow due to the jmp) [I]: `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x720]`; `call 0x1EF6F90` (sub_1ef6f90 grow); TLS dl=0x827 via sub_eea6040; `mov qword ptr [rbp+0x2A0],1` (mirrors phase 1's tail); phase ends here.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×3), 0xEEC6EC0 (direct), 0x5ABA6D0 (direct, grow), 0x67E1840 (direct, new), 0x1EF6F90 (direct, in skipped block), `jmp 0x672A198`.
Fields read [V]: [0x1233E1B0] [R]×3, [rcx] [R]×3, [rax+0x10] [R]×3, [rbp+0x818] [R]×3 (movzx edx), [r14+8] [R/W], [r14+0x10] [R], [rbp+0x560] [R] (tag src for copy), [rbp+0x827] [R] (movzx edx, skipped block).
Fields written [V]: [rbp+0x818] [W]×3, [r14+8] [W] (+=0xC8), [r14+0x10..+0x10+0xC8] via sub_eec6ec0 [I] (record copy dst), [rbp+0x2A0] [W] =1 (skipped block), [rbp+0x370] via sub_67e1840 [I] (target).
```

## Phase 20 (0x67288E6..0x67289B7)
```
  67288e6  add [rcx-0x75],al                             ; W a0-0x75
  67288e9  xchg [rax+0x41000008],ch                      
  67288ef  sub eax,[rsi+0x8A0]                           
  67288f5  shr eax,1                                     
  67288f7  dec eax                                       
  67288f9  mov [rbp+0x2B0],ax                            
  6728900  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728907  mov rax,[rcx]                                 
  672890a  mov rax,[rax+0x10]                            
  672890e  mov dl,0x4A                                   
  6728910  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728916  nop                                           
  6728917  mov [rbp+0x827],al                            
  672891d  mov rdx,[r14+0x758]                           
  6728924  cmp rdx,[r14+0x760]                           
  672892b  je 0x6728AC2                                  ; -> loc_6728ac2 (near je, forward exit block)
  6728931  lea rcx,[rbp+0x6C8]                           
  6728938  mov eax,[rcx+0x10]                            
  672893b  mov [rdx+0x10],eax                            
  672893e  movups xmm0,[rcx]                             
  6728941  movups [rdx],xmm0                             
  6728944  movzx eax,byte ptr [rbp+0x6DC]                
  672894b  mov [rdx+0x14],al                             
  672894e  movss xmm0,[rbp+0x6E0]                        
  6728956  movss [rdx+0x18],xmm0                         
  672895b  movss xmm0,[rbp+0x6E4]                        
  6728963  movss [rdx+0x1C],xmm0                         
  6728968  movss xmm0,[rbp+0x6E8]                        
  6728970  movss [rdx+0x20],xmm0                         
  6728975  movss xmm0,[rbp+0x6EC]                        
  672897d  movss [rdx+0x24],xmm0                         
  6728982  lea rax,[rbp+0x564]                           
  6728989  movups xmm0,[rax+0x18C]                       
  6728990  movups xmm1,[rax+0x19C]                       
  6728997  movups xmm2,[rax+0x1AB]                       
  672899e  movups [rdx+0x28],xmm0                        
  67289a2  movups [rdx+0x38],xmm1                        
  67289a6  movups [rdx+0x47],xmm2                        
  67289aa  add qword ptr [r14+0x758],0x58                
  67289b2  jmp 0x6728AD6                                 ; -> loc_6728ad6 (near jmp, forward)
// Phase 20: opens with embedded slot [?]: `add [rcx-0x75],al`; `xchg [rax+0x41000008],ch`. Word-count decode [V] (phase 1/13 idiom, eax carry-in [I]): `sub eax,[rsi+0x8A0]`; `shr eax,1`; `dec eax`; `mov [rbp+0x2B0],ax`. TLS seq dl=0x4A via [0xF99FFA0]=sub_eea6040 → `mov [rbp+0x827],al` [V] (phase 1 read [rbp+0x827]). Cursor [r14+0x758] vs [r14+0x760], 0x58-byte records [V]: `rdx=[r14+0x758]`; `cmp rdx,[r14+0x760]`; `je 0x6728AC2` (near je) → loc_6728ac2 exit block (ahead in stream; mirrors phase 2's exit). Else record copy from [rbp+0x6C8] (same shape as phase 1/2's [rbp+0x6D8]): `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0`; `movzx eax,byte ptr [rbp+0x6DC]`; `mov [rdx+0x14],al`; `movss xmm0,[rbp+0x6E0/6E4/6E8/6EC]` → `[rdx+0x18/0x1C/0x20/0x24]`; completion from [rbp+0x564+0x18C/0x19C/0x1AB] → `[rdx+0x28/0x38/0x47]`; `add qword ptr [r14+0x758],0x58`; `jmp 0x6728AD6` (near jmp, forward past the exit block).
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect, once).
Fields read [V]: embedded [rcx-0x75] [R/W] [?], [rax+0x41000008] [R/W] [?], eax carry-in [R] [I], [rsi+0x8A0] [R], [rbp+0x2B0] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [W], [r14+0x758] [R/W], [r14+0x760] [R], [rbp+0x6C8] [R], [rcx+0x10] [R], [rbp+0x6DC] [R], [rbp+0x6E0] [R], [rbp+0x6E4] [R], [rbp+0x6E8] [R], [rbp+0x6EC] [R], [rbp+0x564] [R] (lea rax), [rax+0x18C] [R], [rax+0x19C] [R], [rax+0x1AB] [R].
Fields written [V]: [rbp+0x2B0] [W], [rbp+0x827] [W], [rdx+0x10] [W], [rdx..rdx+0x10] [W], [rdx+0x14] [W], [rdx+0x18] [W], [rdx+0x1C] [W], [rdx+0x20] [W], [rdx+0x24] [W], [rdx+0x28] [W], [rdx+0x38] [W], [rdx+0x47] [W], [r14+0x758] [W].
```

## Phase 21 (0x67289B7..0x6728A88)
```
  67289b7  lea rcx,[r14+0x8A0]                           
  67289be  lea r8,[rbp+0x728]                            
  67289c5  call 0x1EF6F90                                ; -> sub_1ef6f90
  67289ca  nop                                           
  67289cb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67289d2  mov rax,[rcx]                                 
  67289d5  mov rax,[rax+0x10]                            
  67289d9  movzx edx,byte ptr [rbp+0x827]                
  67289e0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67289e6  nop                                           
  67289e7  mov qword ptr [rbp+0x2A0],1                   
  67289f2  mov eax,[r14+0x8A8]                           
  67289f9  sub eax,[r14+0x8A0]                           
  6728a00  shr eax,1                                     
  6728a02  dec eax                                       
  6728a04  mov [rbp+0x2B0],ax                            
  6728a0b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728a12  mov rax,[rcx]                                 
  6728a15  mov rax,[rax+0x10]                            
  6728a19  mov dl,0x4A                                   
  6728a1b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728a21  nop                                           
  6728a22  mov [rbp+0x827],al                            
  6728a28  mov rdx,[r14+0x758]                           
  6728a2f  cmp rdx,[r14+0x760]                           
  6728a36  je 0x6728B52                                  ; -> loc_6728b52 (near je, forward exit block)
  6728a3c  lea rcx,[rbp+0x6D0]                           
  6728a43  mov eax,[rcx+0x10]                            
  6728a46  mov [rdx+0x10],eax                            
  6728a49  movups xmm0,[rcx]                             
  6728a4c  movups [rdx],xmm0                             
  6728a4f  movzx eax,byte ptr [rbp+0x6E4]                
  6728a56  mov [rdx+0x14],al                             
  6728a59  movss xmm0,[rbp+0x6E8]                        
  6728a61  movss [rdx+0x18],xmm0                         
  6728a66  movss xmm0,[rbp+0x6EC]                        
  6728a6e  movss [rdx+0x1C],xmm0                         
  6728a73  movss xmm0,[rbp+0x6F0]                        
  6728a7b  movss [rdx+0x20],xmm0                         
  6728a80  movss xmm0,[rbp+0x6F4]                        
// Phase 21: executes phase-19's skipped block [V]: `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x728]`; `call 0x1EF6F90` (sub_1ef6f90 grow). TLS dl=0x827 via [0xF99FFA0]=sub_eea6040 → `mov [rbp+0x827],al`; `mov qword ptr [rbp+0x2A0],1` (mirrors phase 1's tail) [V]. Word-count decode [V]: `mov eax,[r14+0x8A8]`; `sub eax,[r14+0x8A0]`; `shr eax,1`; `dec eax`; `mov [rbp+0x2B0],ax` (same as phase 20). TLS dl=0x4A → [rbp+0x827]=al [V]. Cursor [r14+0x758] vs [r14+0x760], 0x58-byte records [V]: `rdx=[r14+0x758]`; `cmp rdx,[r14+0x760]`; `je 0x6728B52` (near je) → loc_6728b52 exit block (ahead in stream). Else record copy from [rbp+0x6D0]: `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0`; `movzx eax,byte ptr [rbp+0x6E4]`; `mov [rdx+0x14],al`; `movss xmm0,[rbp+0x6E8/6EC/6F0/6F4]` → `[rdx+0x18/0x1C/0x20/0x24]` (phase ends mid-record; [rdx+0x24] store and [rbp+0x564]-based completion continue phase 22, mirroring phase 2).
Callees [V]: 0x1EF6F90 (direct, grow), [0xF99FFA0] = sub_eea6040 (indirect ×2).
Fields read [V]: [r14+0x8A0] [R] (lea), [rbp+0x728] [R] (lea r8), [0x1233E1B0] [R]×2, [rcx] [R]×2, [rax+0x10] [R]×2, [rbp+0x827] [R/W], [rbp+0x2A0] [W], [r14+0x8A8] [R], [r14+0x8A0] [R], [rbp+0x2B0] [W], [r14+0x758] [R/W], [r14+0x760] [R], [rbp+0x6D0] [R], [rcx+0x10] [R], [rbp+0x6E4] [R], [rbp+0x6E8] [R], [rbp+0x6EC] [R], [rbp+0x6F0] [R], [rbp+0x6F4] [R].
Fields written [V]: [rbp+0x827] [W]×2, [rbp+0x2A0] [W] =1, [rbp+0x2B0] [W], [rdx+0x10] [W], [rdx..rdx+0x10] [W], [rdx+0x14] [W], [rdx+0x18] [W], [rdx+0x1C] [W], [rdx+0x20] [W], [rdx+0x24] [W] (this phase), [r14+0x758] [W] (this phase).
```

## Phase 22 (0x6728A88..0x6728B59)
```
  6728a88  movss [rdx+0x24],xmm0                         ; W a1+0x24
  6728a8d  lea rax,[rbp+0x564]                           
  6728a94  movups xmm0,[rax+0x194]                       
  6728a9b  movups xmm1,[rax+0x1A4]                       
  6728aa2  movups xmm2,[rax+0x1B3]                       
  6728aa9  movups [rdx+0x28],xmm0                        ; W a1+0x28
  6728aad  movups [rdx+0x38],xmm1                        ; W a1+0x38
  6728ab1  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6728ab5  add qword ptr [r14+0x758],0x58                
  6728abd  jmp 0x6728B66                                 ; -> loc_6728b66 (near jmp, forward)
  6728ac2  lea rcx,[r14+0x750]                           
  6728ac9  lea r8,[rbp+0x6C8]                            
  6728ad0  call 0x6760A80                                ; -> sub_6760a80
  6728ad5  nop                                           
  6728ad6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728add  mov rax,[rcx]                                 
  6728ae0  mov rax,[rax+0x10]                            
  6728ae4  movzx edx,byte ptr [rbp+0x827]                
  6728aeb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728af1  nop                                           
  6728af2  mov eax,[r14+0x758]                           
  6728af9  sub eax,[r14+0x750]                           
  6728b00  shr eax,3                                     
  6728b03  imul eax,0xFFFF8BA3                           
  6728b09  dec eax                                       
  6728b0b  mov [rbp+0x2CC],ax                            
  6728b12  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728b19  mov rax,[rcx]                                 
  6728b1c  mov rax,[rax+0x10]                            
  6728b20  mov dl,0x4A                                   
  6728b22  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728b28  nop                                           
  6728b29  mov [rbp+0x827],al                            
  6728b2f  mov rdx,[r14+0x860]                           
  6728b36  cmp rdx,[r14+0x868]                           
  6728b3d  je 0x6728BE2                                  ; -> loc_6728be2 (near je, forward exit block)
  6728b43  inc rdx                                       
  6728b46  mov [r14+0x860],rdx                           
  6728b4d  jmp 0x6728BEF                                 ; -> loc_6728bef (near jmp, forward)
  6728b52  lea rcx,[r14+0x750]                           
// Phase 22: completes phase-21 record [V]: `movss [rdx+0x24],xmm0`; `lea rax,[rbp+0x564]`; `movups xmm0,[rax+0x194]`; `movups xmm1,[rax+0x1A4]`; `movups xmm2,[rax+0x1B3]`; `movups [rdx+0x28/0x38/0x47]` (phase 2 used 0x19C/0x1AC/0x1BB; here 0x194/0x1A4/0x1B3); `add qword ptr [r14+0x758],0x58`; `jmp 0x6728B66` (forward). Exit block loc_6728ac2 (target of phases 20-21 `je` when cursor full) [V]: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x6C8]`; `call 0x6760A80` (sub_6760A80 processes record [rbp+0x6C8] at cursor-base [r14+0x750]); `nop`. Post-append join loc_6728ad6 (target of phase 20-21 `jmp`) [V]: TLS dl=[rbp+0x827] via [0xF99FFA0]=sub_eea6040 → `mov [rbp+0x827],al`; count [V] (mirrors phase 2): `mov eax,[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x2CC],ax`. TLS dl=0x4A → [rbp+0x827]=al [V]. Cursor [r14+0x860] vs [r14+0x868] inc-by-1 [V] (mirrors phase 14): `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; `je 0x6728BE2` → loc_6728be2 exit (ahead). Else `inc rdx`; `mov [r14+0x860],rdx`; `jmp 0x6728BEF`. Stream lands on 0x6728B52 (phase 21's `je` target) at the phase end: `lea rcx,[r14+0x750]` ... continues phase 23.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×2), 0x6760A80 (direct, exit block).
Fields read [V]: [rdx+0x24] [W], [rbp+0x564] [R], [rax+0x194] [R], [rax+0x1A4] [R], [rax+0x1B3] [R], [r14+0x758] [R/W], [r14+0x750] [R] (lea address), [rbp+0x6C8] [R] (lea address, via call), [0x1233E1B0] [R]×2, [rcx] [R]×2, [rax+0x10] [R]×2, [rbp+0x827] [R/W]×2 (movzx edx), [rbp+0x2CC] [W], [r14+0x860] [R/W], [r14+0x868] [R], [rbp+0x750] via lea [I].
Fields written [V]: [rdx+0x24] [W], [rdx+0x28] [W], [rdx+0x38] [W], [rdx+0x47] [W], [r14+0x758] [W] (+=0x58), [rbp+0x827] [W]×2, [rbp+0x2CC] [W], [r14+0x860] [W].
```

## Phase 23 (0x6728B59..0x6728C1F)
```
  6728b59  lea r8,[rbp+0x6D0]                            
  6728b60  call 0x6760A80                                ; -> sub_6760a80
  6728b65  nop                                           
  6728b66  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728b6d  mov rax,[rcx]                                 
  6728b70  mov rax,[rax+0x10]                            
  6728b74  movzx edx,byte ptr [rbp+0x827]                
  6728b7b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728b81  nop                                           
  6728b82  mov eax,[r14+0x758]                           
  6728b89  sub eax,[r14+0x750]                           
  6728b90  shr eax,3                                     
  6728b93  imul eax,0xFFFF8BA3                           
  6728b99  dec eax                                       
  6728b9b  mov [rbp+0x2CC],ax                            
  6728ba2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728ba9  mov rax,[rcx]                                 
  6728bac  mov rax,[rax+0x10]                            
  6728bb0  mov dl,0x4A                                   
  6728bb2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728bb8  nop                                           
  6728bb9  mov [rbp+0x827],al                            
  6728bbf  mov rdx,[r14+0x860]                           
  6728bc6  cmp rdx,[r14+0x868]                           
  6728bcd  je 0x6728D41                                  ; -> loc_6728d41 (near je, forward grow block)
  6728bd3  inc rdx                                       
  6728bd6  mov [r14+0x860],rdx                           
  6728bdd  jmp 0x6728D4E                                 ; -> loc_6728d4e (near jmp, forward)
  6728be2  lea rcx,[r14+0x858]                           
  6728be9  call 0x6760E60                                ; -> sub_6760e60
  6728bee  nop                                           
  6728bef  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728bf6  mov rax,[rcx]                                 
  6728bf9  mov rax,[rax+0x10]                            
  6728bfd  movzx edx,byte ptr [rbp+0x827]                
  6728c04  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728c0a  nop                                           
  6728c0b  mov qword ptr [rbp+0x2A0],0x4009              
  6728c16  mov eax,[r14+0x858]                           
  6728c1d  not eax                                       
// Phase 23: completes phase-22's `je 0x6728B52` target [V]: `lea r8,[rbp+0x6D0]`; `call 0x6760A80` (sub_6760A80 processes record [rbp+0x6D0] — same exit shape as loc_6728ac2 but source [rbp+0x6D0] vs [rbp+0x6C8]); `nop`. Post-append join (mirrors loc_6728ad6) [V]: TLS dl=[rbp+0x827] via [0xF99FFA0]=sub_eea6040 → `mov [rbp+0x827],al`; count [V]: `mov eax,[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x2CC],ax`; TLS dl=0x4A → [rbp+0x827]=al [V]. Cursor [r14+0x860] vs [r14+0x868] inc-by-1 [V]: `rdx=[r14+0x860]`; `cmp rdx,[r14+0x868]`; `je 0x6728D41` → loc_6728d41: `lea rcx,[r14+0x858]`; `call 0x6760E60` (grow). Else `inc rdx`; `mov [r14+0x860],rdx`; `jmp 0x6728D4E`. Join loc_6728bef [V]: TLS dl=[rbp+0x827] via sub_eea6040; tag `mov qword ptr [rbp+0x2A0],0x4009` [V] (mirrors phase 3's [rbp+0x2A0]=0x4009); fold starts `mov eax,[r14+0x858]`; `not eax` (add continues phase 24, mirroring phase 3's fold not/add → [rbp+0x2B6]).
Callees [V]: 0x6760A80 (direct, exit block), [0xF99FFA0] = sub_eea6040 (indirect ×2), 0x6760E60 (direct, grow path at loc_6728d41).
Fields read [V]: [rbp+0x6D0] [R] (lea r8), [0x1233E1B0] [R]×2, [rcx] [R]×2, [rax+0x10] [R]×2, [rbp+0x827] [R/W]×2 (movzx edx), [r14+0x758] [R], [r14+0x750] [R], [rbp+0x2CC] [W], [r14+0x860] [R/W], [r14+0x868] [R], [rbp+0x858] [R] (lea rcx at loc_6728d41 / fold source), [rbp+0x2A0] [W], [r14+0x858] [R] (fold).
Fields written [V]: [rbp+0x827] [W]×2, [rbp+0x2CC] [W], [r14+0x860] [W], [rbp+0x2A0] [W] (imm 0x4009), [rbp+0x858 region] via sub_6760A80 [I], fold result store pending phase 24 [I].
```

## Phase 24 (0x6728C1F..0x6728CE6)
```
  6728c1f  add eax,[r14+0x860]                           
  6728c26  mov [rbp+0x2B6],ax                            
  6728c2d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728c34  mov rax,[rcx]                                 
  6728c37  mov rax,[rax+0x10]                            
  6728c3b  mov dl,0x4A                                   
  6728c3d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728c43  mov [rbp+0x827],al                            
  6728c49  lea rcx,[r14+0x648]                           
  6728c50  lea rdx,[rbp+0x678]                           
  6728c57  call 0x675FB30                                ; -> sub_675fb30
  6728c5c  nop                                           
  6728c5d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728c64  mov rax,[rcx]                                 
  6728c67  mov rax,[rax+0x10]                            
  6728c6b  movzx edx,byte ptr [rbp+0x827]                
  6728c72  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728c78  nop                                           
  6728c79  mov eax,[r14+0x650]                           
  6728c80  sub eax,[r14+0x648]                           
  6728c87  shr eax,3                                     
  6728c8a  imul eax,0xFFFF8E39                           
  6728c90  dec eax                                       
  6728c92  mov [rbp+0x2E2],ax                            
  6728c99  lea rcx,[r14+0x780]                           
  6728ca0  lea rdx,[rbp+0x620]                           
  6728ca7  call 0x675F3B0                                ; -> sub_675f3b0
  6728cac  nop                                           
  6728cad  mov eax,[r14+0x788]                           
  6728cb4  sub eax,[r14+0x780]                           
  6728cbb  shr eax,3                                     
  6728cbe  imul eax,0xFFFF8BA3                           
  6728cc4  dec eax                                       
  6728cc6  mov [rbp+0x2C8],ax                            
  6728ccd  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728cd4  mov rax,[rcx]                                 
  6728cd7  mov rax,[rax+0x10]                            
  6728cdb  mov dl,0x4A                                   
  6728cdd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728ce3  mov [rbp+0x827],al                            
// Phase 24: completes phase-23 fold [V]: `add eax,[r14+0x860]`; `mov [rbp+0x2B6],ax` (mirrors phase 3's fold not/add → [rbp+0x2B6]). TLS dl=0x4A → [rbp+0x827]=al [V]. `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x678]`; `call 0x675FB30` [V] (mirrors phase 3's [rbp+0x688]/0x675FB30; here [rbp+0x678] area [I]). TLS dl=[rbp+0x827] via sub_eea6040 → [rbp+0x827]=al [V]. Count #1 [V] (phase-3 idiom imul /7): `mov eax,[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x2E2],ax`. `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x620]`; `call 0x675F3B0` [V] (mirrors phase 3's [rbp+0x630]/0x675F3B0; here [rbp+0x620] area [I]). Count #2 [V] (phase-2 idiom): `mov eax,[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x2C8],ax` (phase 3/28-era → [rbp+0x2C8] here). TLS dl=0x4A → `mov [rbp+0x827],al`; continues phase 25.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×3), 0x675FB30 (direct), 0x675F3B0 (direct).
Fields read [V]: eax carry-in [R] (from phase 23's not eax), [r14+0x860] [R], [rbp+0x2B6] [W], [0x1233E1B0] [R]×3, [rcx] [R]×3, [rax+0x10] [R]×3, [rbp+0x827] [R/W]×3 (movzx edx), [r14+0x650] [R], [r14+0x648] [R], [rbp+0x678] [R] (lea), [rbp+0x2E2] [W], [r14+0x788] [R], [r14+0x780] [R], [rbp+0x620] [R] (lea), [rbp+0x2C8] [W].
Fields written [V]: [rbp+0x2B6] [W], [rbp+0x827] [W]×3, [rbp+0x2E2] [W], [rbp+0x2C8] [W].
```

## Phase 25 (0x6728CE6..0x6728DBB)
```
  6728ce6  or [rax],al                                   
  6728ce8  add [rcx-0x75],cl                             ; W a0-0x75
  6728ceb  mov esi,0x770                                 
  6728cf0  cmp rdi,[r14+0x778]                           
  6728cf7  je 0x6728EA0                                  ; -> loc_6728ea0 (near je, forward grow block)
  6728cfd  mov rax,[rbp+0x598]                           
  6728d04  mov [rdi],rax                                 
  6728d07  lea rcx,[rdi+8]                               
  6728d0b  lea rdx,[rbp+0x5A0]                           
  6728d12  call 0xE869FF0                                ; -> sub_e869ff0
  6728d17  nop                                           
  6728d18  mov rax,[rbp+0x618]                           
  6728d1f  mov [rdi+0x80],rax                            
  6728d26  mov qword ptr [rbp+0x618],0                   
  6728d31  add qword ptr [r14+0x770],0x88                
  6728d3c  jmp 0x6728EB7                                 ; -> loc_6728eb7 (near jmp, forward)
  6728d41  lea rcx,[r14+0x858]                           
  6728d48  call 0x6760E60                                ; -> sub_6760e60
  6728d4d  nop                                           
  6728d4e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728d55  mov rax,[rcx]                                 
  6728d58  mov rax,[rax+0x10]                            
  6728d5c  movzx edx,byte ptr [rbp+0x827]                
  6728d63  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728d69  nop                                           
  6728d6a  mov eax,[r14+0x858]                           
  6728d71  not eax                                       
  6728d73  add eax,[r14+0x860]                           
  6728d7a  mov [rbp+0x2B6],ax                            
  6728d81  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728d88  mov rax,[rcx]                                 
  6728d8b  mov rax,[rax+0x10]                            
  6728d8f  mov dl,0x4A                                   
  6728d91  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728d97  mov [rbp+0x827],al                            
  6728d9d  lea rcx,[r14+0x648]                           
  6728da4  lea rdx,[rbp+0x680]                           
  6728dab  call 0x675FB30                                ; -> sub_675fb30
  6728db0  nop                                           
  6728db1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
// Phase 25: opens with embedded slot [?]: `or [rax],al`; `add [rcx-0x75],cl`; `mov esi,0x770`. Cursor [r14+0x770] vs [r14+0x778], 0x88-byte records [V] (mirrors phases 4/16): `cmp rdi,[r14+0x778]` (rdi = cursor value [I], set before this phase); if equal `je 0x6728EA0` → loc_6728ea0 grow block (ahead). Else record copy: `mov rax,[rbp+0x598]`; `mov [rdi],rax`; `lea rcx,[rdi+8]`; `lea rdx,[rbp+0x5A0]`; `call 0xE869FF0` ([rdi+8..] copy [I]); `mov rax,[rbp+0x618]`; `mov [rdi+0x80],rax`; `mov qword ptr [rbp+0x618],0` (zero); `add qword ptr [r14+0x770],0x88`; `jmp 0x6728EB7` (forward). Join loc_6728d4e (target of phase 23's `jmp 0x6728D4E`) [V]: TLS dl=[rbp+0x827] via [0xF99FFA0]=sub_eea6040 → `mov [rbp+0x827],al`; fold not/add [V]: `mov eax,[r14+0x858]`; `not eax`; `add eax,[r14+0x860]`; `mov [rbp+0x2B6],ax` (same fold target as phase 24); TLS dl=0x4A → [rbp+0x827]=al [V]. `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x680]`; `call 0x675FB30` [V] (phase 24 used [rbp+0x678] here [rbp+0x680]); continues phase 26.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×2), 0xE869FF0 (direct), 0x6760E60 (direct, grow at loc_6728d41), 0x675FB30 (direct).
Fields read [V]: embedded [rax] [R/W] [?], [rcx-0x75] [R/W] [?], rdi [R] [I] (cursor), [r14+0x778] [R], [rbp+0x598] [R], [rdi] [W], [rbp+0x5A0] [R] (lea), [rbp+0x618] [R/W], [rdi+0x80] [W], [r14+0x770] [R/W], [rbp+0x858] [R], [rbp+0x2B6] [W], [rbp+0x827] [R/W]×2 (movzx edx), [r14+0x648] [R] (lea), [rbp+0x680] [R] (lea).
Fields written [V]: [rbp+0x2B6] [W], [rbp+0x827] [W]×2, [rdi] [W], [rdi+8..] via sub_e869ff0 [I], [rdi+0x80] [W], [rbp+0x618] [W] then zero [W], [r14+0x770] [W] (+=0x88).
```

## Phase 26 (0x6728DBB..0x6728E98)
```
  6728dbb  mov rax,[rax+0x10]                            
  6728dbf  movzx edx,byte ptr [rbp+0x827]                
  6728dc6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728dcc  nop                                           
  6728dcd  mov eax,[r14+0x650]                           
  6728dd4  sub eax,[r14+0x648]                           
  6728ddb  shr eax,3                                     
  6728dde  imul eax,0xFFFF8E39                           
  6728de4  dec eax                                       
  6728de6  mov [rbp+0x2E2],ax                            
  6728ded  lea rcx,[r14+0x780]                           
  6728df4  lea rdx,[rbp+0x628]                           
  6728dfb  call 0x675F3B0                                ; -> sub_675f3b0
  6728e00  nop                                           
  6728e01  mov qword ptr [rbp+0x2A0],0x2005009           
  6728e0c  mov eax,[r14+0x788]                           
  6728e13  sub eax,[r14+0x780]                           
  6728e1a  shr eax,3                                     
  6728e1d  imul eax,0xFFFF8BA3                           
  6728e23  dec eax                                       
  6728e25  mov [rbp+0x2C8],ax                            
  6728e2c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728e33  mov rax,[rcx]                                 
  6728e36  mov rax,[rax+0x10]                            
  6728e3a  mov dl,0x4A                                   
  6728e3c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728e42  mov [rbp+0x827],al                            
  6728e48  mov rdi,[r14+0x770]                           
  6728e4f  cmp rdi,[r14+0x778]                           
  6728e56  je 0x6728F3E                                  ; -> loc_6728f3e (near je, forward grow block)
  6728e5c  mov rax,[rbp+0x5A0]                           
  6728e63  mov [rdi],rax                                 
  6728e66  lea rcx,[rdi+8]                               
  6728e6a  lea rdx,[rbp+0x5A8]                           
  6728e71  call 0xE869FF0                                ; -> sub_e869ff0
  6728e76  nop                                           
  6728e77  mov rax,[rbp+0x620]                           
  6728e7e  mov [rdi+0x80],rax                            
  6728e85  mov qword ptr [rbp+0x620],0                   
  6728e90  add qword ptr [r14+0x770],0x88                
// Phase 26: completes phase-25's call-0x675FB30 tail [V]: TLS dl=[rbp+0x827] via sub_eea6040 → [rbp+0x827]=al [I]; count #1 [V] (phase-3 idiom imul /7): `mov eax,[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x2E2],ax`. `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x628]`; `call 0x675F3B0` [V] (mirrors phase 3/24's [rbp+0x630/0x620]/0x675F3B0; here [rbp+0x628] area [I]). Tag [V]: `mov qword ptr [rbp+0x2A0],0x2005009` (phase 15 used same imm at [rbp+0x560]). Count #2 [V]: `mov eax,[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x2C8],ax`. TLS dl=0x4A → `mov [rbp+0x827],al` [V]. Second 0x88-byte record append [V] (mirrors phases 4/16/25): `rdi=[r14+0x770]`; `cmp rdi,[r14+0x778]`; if equal `je 0x6728F3E` → loc_6728f3e grow block (ahead). Else: `mov rax,[rbp+0x5A0]`; `mov [rdi],rax`; `lea rcx,[rdi+8]`; `lea rdx,[rbp+0x5A8]`; `call 0xE869FF0` ([rdi+8..] copy [I]); `mov rax,[rbp+0x620]`; `mov [rdi+0x80],rax`; `mov qword ptr [rbp+0x620],0` (zero); `add qword ptr [r14+0x770],0x88` — phase ends here; forward jmp continues phase 27.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×2), 0x675F3B0 (direct), 0xE869FF0 (direct).
Fields read [V]: [rax+0x10] [R], [rbp+0x827] [R/W], [r14+0x650] [R], [r14+0x648] [R], [rbp+0x2E2] [W], [rbp+0x780] [R] (lea), [rbp+0x628] [R] (lea), [rbp+0x2A0] [W] (imm tag), [r14+0x788] [R], [r14+0x780] [R], [rbp+0x2C8] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x827] [W], [r14+0x770] [R/W], [r14+0x778] [R], [rbp+0x5A0] [R], [rbp+0x5A8] [R] (lea), [rbp+0x620] [R/W].
Fields written [V]: [rbp+0x827] [W]×2, [rbp+0x2E2] [W], [rbp+0x2A0] [W] (imm 0x2005009), [rbp+0x2C8] [W], [rdi] [W], [rdi+8..] via sub_e869ff0 [I], [rdi+0x80] [W], [rbp+0x620] [W] then zero [W], [r14+0x770] [W] (+=0x88; phase ends at this add).
```

## Phase 27 (0x6728E98..0x6728F55)
```
  6728e98  add [rax],al                                   ; [?] embedded jump-table slot
  6728e9a  add cl,ch                                      ; [?] embedded jump-table slot
  6728e9c  mov ch,0                                       ; [?] embedded jump-table slot
  6728e9e  add [rax],al                                   ; [?] embedded jump-table slot
  6728ea0  lea rcx,[r14+0x768]                            ; phase-26 grow path join (loc_6728ea0)
  6728ea7  mov rdx,rdi                                    ; rdi=cursor old value [I]
  6728eaa  lea r8,[rbp+0x598]                            
  6728eb1  call 0x6760710                                ; -> sub_6760710 (grow block)
  6728eb6  nop                                           
  6728eb7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728ebe  mov rax,[rcx]                                 
  6728ec1  mov rax,[rax+0x10]                            
  6728ec5  movzx edx,byte ptr [rbp+0x827]                
  6728ecc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728ed2  nop                                           
  6728ed3  mov qword ptr [rbp+0x2A0],0x2007009           
  6728ede  mov eax,[r14+0x770]                           
  6728ee5  sub eax,[r14+0x768]                           
  6728eec  shr eax,3                                     
  6728eef  imul eax,0xFFFFF0F1                           
  6728ef5  dec eax                                       
  6728ef7  mov [rbp+0x2CA],ax                            
  6728efe  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728f05  mov rax,[rcx]                                 
  6728f08  mov rax,[rax+0x10]                            
  6728f0c  mov dl,0x4A                                   
  6728f0e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728f14  nop                                           
  6728f15  mov [rbp+0x827],al                            
  6728f1b  mov rdx,[r14+0x6B0]                           
  6728f22  cmp rdx,[r14+0x6B8]                           
  6728f29  je 0x6728FD1                                  ; -> loc_6728fd1 (forward grow block)
  6728f2f  inc rdx                                       
  6728f32  mov [r14+0x6B0],rdx                           
  6728f39  jmp 0x6728FDE                                 ; -> loc_6728fde (forward join)
  6728f3e  lea rcx,[r14+0x768]                            ; phase-26 je 0x6728F3E target
  6728f45  mov rdx,rdi                                   
  6728f48  lea r8,[rbp+0x5A0]                            
  6728f4f  call 0x6760710                                ; -> sub_6760710 (grow block)
  6728f54  nop                                           
// Phase 27: opens with 4-instr embedded jump-table slot [?] (`add [rax],al`; `add cl,ch`; `mov ch,0`; `add [rax],al`). Then linear flow: phase-26's grow path joins at loc_6728ea0 — `lea rcx,[r14+0x768]`; `mov rdx,rdi` (rdi=cursor old value [I]); `lea r8,[rbp+0x598]`; `call 0x6760710` [V] (mirrors phase 25 grow loc_6728ea0 / phase 16 grow loc_6728646); TLS dl=[rbp+0x827] via `movzx edx,byte ptr [rbp+0x827]`; `call [0xF99FFA0]` = sub_eea6040 [V]. Tag [V]: `mov qword ptr [rbp+0x2A0],0x2007009` (phase 15 used 0x2005009 at [rbp+0x560]). Count [V]: `mov eax,[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x2CA],ax` (same idiom as phase 16's [rbp+0x58A] at 0x67285e9..0x672861c). TLS dl=0x4A → `mov [rbp+0x827],al` [V]. Cursor [r14+0x6B0] vs [r14+0x6B8] inc-by-1 [V]: `mov rdx,[r14+0x6B0]`; `cmp rdx,[r14+0x6B8]`; if full `je 0x6728FD1` → loc_6728fd1 grow block (ahead); else `inc rdx`; `mov [r14+0x6B0],rdx`; `jmp 0x6728FDE` → forward join (continues phase 28). Fall-through grow block at 0x6728f3e (phase-26's `je 0x6728F3E` target): `lea rcx,[r14+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x5A0]`; `call 0x6760710` [V]; `nop` — phase ends here; linear continues phase 28 at 0x6728F55.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×2), 0x6760710 (direct ×2).
Fields read [V]: [rbp+0x827] [R/W], [rbp+0x2A0] [W] (imm tag), [r14+0x770] [R], [r14+0x768] [R], [rbp+0x2CA] [W], [0x1233E1B0] [R]×2, [rcx] [R]×2, [rax+0x10] [R]×2, [rbp+0x827] [W], [r14+0x6B0] [R/W], [r14+0x6B8] [R], rdi [R] (cursor old [I]), [rbp+0x598] [R] (lea), [rbp+0x5A0] [R] (lea).
Fields written [V]: [rbp+0x2A0] [W] (imm 0x2007009), [rbp+0x2CA] [W], [rbp+0x827] [W], [r14+0x6B0] [W] (inc-by-1 cursor).
```

## Phase 16 (0x67285E9..0x67286B3)
```
  67285e9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67285ef  mov [rbp+0x818],al                            
  67285f5  mov rdi,[r14+0x770]                           
  67285fc  cmp rdi,[r14+0x778]                           
  6728603  je short 0x6728646                            ; -> loc_6728646
  6728605  mov rax,[rbp+0x378]                           
  672860c  mov [rdi],rax                                 
  672860f  lea rcx,[rdi+8]                               
  6728613  lea rdx,[rbp+0x380]                           
  672861a  call 0xE869FF0                                ; -> sub_e869ff0
  672861f  nop                                           
  6728620  mov rax,[rbp+0x3F8]                           
  6728627  mov [rdi+0x80],rax                            
  672862e  mov qword ptr [rbp+0x3F8],0                   
  6728639  add qword ptr [r14+0x770],0x88                
  6728644  jmp short 0x672865D                           ; -> loc_672865d
loc_6728646:  ; from 6728603
  6728646  lea rcx,[r14+0x768]                           
  672864d  mov rdx,rdi                                   
  6728650  lea r8,[rbp+0x378]                            
  6728657  call 0x6760710                                ; -> sub_6760710
  672865c  nop                                           
loc_672865d:  ; from 6728644
  672865d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6728664  mov rax,[rcx]                                 
  6728667  mov rax,[rax+0x10]                            
  672866b  movzx edx,byte ptr [rbp+0x818]                
  6728672  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6728678  nop                                           
  6728679  mov eax,[r14+0x770]                           
  6728680  sub eax,[r14+0x768]                           
  6728687  shr eax,3                                     
  672868a  imul eax,0xFFFFF0F1                           
  6728690  dec eax                                       
  6728692  mov [rbp+0x58A],ax                            
  6728699  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67286a0  mov rax,[rcx]                                 
  67286a3  mov rax,[rax+0x10]                            
  67286a7  mov dl,0x4A                                   
  67286a9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67286af  nop                                           
  67286b0  mov [rbp+0x818],al                            
// Phase 16: completes phase-15 TLS tail [V]: `call qword ptr [0xF99FFA0]`; `mov [rbp+0x818],al`. Cursor [r14+0x770] vs [r14+0x778], 0x88-byte records [V] (mirrors phase 4): `rdi=[r14+0x770]`; `cmp rdi,[r14+0x778]`; if equal `je short 0x6728646` → loc_6728646 grow path: `lea rcx,[r14+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x378]`; `call 0x6760710` (grow). Else record copy: `mov rax,[rbp+0x378]`; `mov [rdi],rax`; `lea rcx,[rdi+8]`; `lea rdx,[rbp+0x380]`; `call 0xE869FF0` ([rdi+8..] copy [I]); `mov rax,[rbp+0x3F8]`; `mov [rdi+0x80],rax`; `mov qword ptr [rbp+0x3F8],0` (zero); `add qword ptr [r14+0x770],0x88`; `jmp short 0x672865D`. Count [V] (mirrors phase 5): `mov eax,[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x58A],ax`. TLS seq dl=0x4A → `mov [rbp+0x818],al` [V]; continues phase 17.
Callees [V]: [0xF99FFA0] = sub_eea6040 (indirect ×2), 0xE869FF0 (direct), 0x6760710 (direct, grow path).
Fields read [V]: [0x1233E1B0] [R]×2, [rcx] [R]×2, [rax+0x10] [R]×2, [rbp+0x818] [R]×2 (movzx edx), [r14+0x770] [R/W], [r14+0x778] [R], [rbp+0x378] [R], [rbp+0x380] [R] (via call), [rbp+0x3F8] [R/W], [r14+0x768] [R], [rbp+0x58A] [W].
Fields written [V]: [rbp+0x818] [W]×2, [rdi] [W], [rdi+8..] via sub_e869ff0 [I], [rdi+0x80] [W], [rbp+0x3F8] [W] then zero [W], [r14+0x770] [W], [rbp+0x58A] [W].
```

