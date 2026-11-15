# oc_U-SK1c — unit U-SK1c (join-3 sub_665b624 residual tail + cold range 0x665cf64..0x665d7e5)

Target: Minecraft.Windows.exe 1.26.62.01
Task: continue from docs/progress/oc_U-SK1b.md NEXT block — residual tail after 0x665c251/0x665c272 up to cold range head 0x665cf64, then cold range 0x665cf64..0x665d7e5 — using `rdis dis` in 40-instruction steps; append each phase with exact rdis lines, then // interpretation tagged [V]/[I]/[?].
Static analysis only; no builds/commits; only create docs/progress/oc_U-SK1c.md; tag claims [V]/[I]/[?].
Note: oc_U-SK1b.md phase 28 (main-range tail) already listed 0x665c251..0x665c26f; I re-verified those exact lines via my own rdis run (they match) and resume the residual tail at 0x665c276 (instruction boundary after 0x665c26f's 7-byte mov rcx,[rbp+0x230]); 0x665c272 itself falls inside that instruction and is not a boundary.

## NEXT
- [x] Residual tail 0x665c276..0x665cf64 — COMPLETE (cold-range head 0x665cf64 reached, clean instruction boundary)
- [x] Cold range 0x665cf64..0x665d7e5 — in progress (next rdis: dis 0x665d5d1 40)
- [ ] Cold range 0x665cf64..0x665d7e5 — not started

---

## PHASES — residual tail 0x665c276..0x665cf64 (continuation of rdis sub_665c251 header: `sub_665c251  [0x665c251..0x665e251)  size 0x2000  0 xrefs in`, seen via `rdis dis 0x665c251 40`)

### Residual Phase 1 — 0x665c276..0x665c31b  [V]
; from rdis `dis 0x665c276 40` (40 instructions)
  665c276  mov [rbp+0x4C8],rcx                           
  665c27d  movaps xmm0,[rbp+0x220]                       
  665c284  movups [rbp+0x4B8],xmm0                       
  665c28b  mov ecx,0x9D0                                 
  665c290  add rcx,[rsi+0x10]                            
  665c294  mov [rsp+0x28],rax                            
  665c299  mov [rsp+0x20],r10                            
  665c29e  call 0x67B40D0                                ; -> sub_67b40d0
  665c2a3  nop                                           
  665c2a4  lea rcx,[rbp+0x340]                           
  665c2ab  call 0x66A9AD0                                ; -> sub_66a9ad0
  665c2b0  cmp byte ptr [rbp+0x218],3                    
  665c2b7  jne short 0x665C2F0                           ; -> loc_665c2f0
  665c2b9  mov rsi,[rbp+0x210]                           
  665c2c0  test rsi,rsi                                  
  665c2c3  je short 0x665C2F0                            ; -> loc_665c2f0
  665c2c5  lock dec dword ptr [rsi+8]                    
  665c2c9  jne short 0x665C2F0                           ; -> loc_665c2f0
  665c2cb  mov rax,[rsi]                                 
  665c2ce  mov rax,[rax]                                 
  665c2d1  mov rcx,rsi                                   
  665c2d4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c2da  lock dec dword ptr [rsi+0xC]                  
  665c2de  jne short 0x665C2F0                           ; -> loc_665c2f0
  665c2e0  mov rax,[rsi]                                 
  665c2e3  mov rax,[rax+8]                               
  665c2e7  mov rcx,rsi                                   
  665c2ea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665c2f0:  ; from 665c2b7, 665c2c3, 665c2c9, 665c2de
  665c2f0  mov rdi,[rbp+0x1E8]                           
  665c2f7  test rdi,rdi                                  
  665c2fa  je short 0x665C34A                            ; -> loc_665c34a
  665c2fc  mov rbx,[rbp+0x1F0]                           
  665c303  jmp short 0x665C309                           ; -> loc_665c309

loc_665c305:  ; from 665c312, 665c31b, 665c321, 665c336, 665c348
  665c305  add rdi,0x28                                  

loc_665c309:  ; from 665c303
  665c309  cmp rdi,rbx                                   
  665c30c  je short 0x665C34A                            ; -> loc_665c34a
  665c30e  cmp byte ptr [rdi+0x18],2                     
  665c312  jne short 0x665C305                           ; -> loc_665c305
  665c314  mov rsi,[rdi+8]                               
  665c318  test rsi,rsi                                  

// Interpretation [V]: exact rdis lines above. Straight-line stores finishing the 0x665c251-block frame ([rbp+0x4C8]=rcx; [rbp+0x4B8]=xmm0 loaded from [rbp+0x220]), then rcx=0x9D0+[rsi+0x10] with rax/r10 spilled to [rsp+0x28]/[rsp+0x20], calls sub_67b40d0 and sub_66a9ad0(rcx=&[rbp+0x340]). [I]: first ref-counted object-release loop over objects at [rbp+0x210] (same pattern as oc_U-SK1b phases 22-26: test, lock dec [rsi+8], jne skip, dtors via [0xF99FFA0]=sub_eea6040, lock dec [rsi+0xC]); then second scan loop: rdi walks from [rbp+0x1E8] in 0x28 steps to rbx=[rbp+0x1F0], skipping entries with byte [rdi+0x18]!=2, releasing object [rdi+8] via the same ref-count/dtor pattern.

### Residual Phase 2 — 0x665c31b..0x665c3dd  [V]
; from rdis `dis 0x665c31b 40` (40 instructions)
  665c31b  je short 0x665C305                            ; -> sub_665c305
  665c31d  lock dec dword ptr [rsi+8]                    
  665c321  jne short 0x665C305                           ; -> sub_665c305
  665c323  mov rax,[rsi]                                 
  665c326  mov rax,[rax]                                 
  665c329  mov rcx,rsi                                   
  665c32c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c332  lock dec dword ptr [rsi+0xC]                  
  665c336  jne short 0x665C305                           ; -> sub_665c305
  665c338  mov rax,[rsi]                                 
  665c33b  mov rax,[rax+8]                               
  665c33f  mov rcx,rsi                                   
  665c342  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c348  jmp short 0x665C305                           ; -> sub_665c305
  665c34a  cmp byte ptr [rbp+0x520],1                    
  665c351  jne 0x665D11D                                 ; -> loc_665d11d
  665c357  mov rcx,[rbp+0x4E0]                           
  665c35e  test rcx,rcx                                  
  665c361  je 0x665D11D                                  ; -> loc_665d11d
  665c367  mov rdx,[rbp+0x4F0]                           
  665c36e  jmp 0x665CA9C                                 ; -> loc_665ca9c
  665c373  xor ecx,ecx                                   
  665c375  mov rdx,[rbp+0x508]                           
  665c37c  mov [rbp+0x4A0],rdx                           
  665c383  mov [rbp+0x4A8],rcx                           
  665c38a  mov [rbp+0x4B0],al                            
  665c390  mov rax,[rbp+0x530]                           
  665c397  mov [rbp+0x4C8],rax                           
  665c39e  movaps xmm0,[rbp+0x520]                       
  665c3a5  movups [rbp+0x4B8],xmm0                       
  665c3ac  mov ecx,0x9D0                                 
  665c3b1  add rcx,[rsi+0x10]                            
  665c3b5  call 0x5ABA5C0                                ; -> sub_5aba5c0
  665c3ba  nop                                           
  665c3bb  mov rsi,rax                                   
  665c3be  lea rdx,[rbp+0x478]                           
  665c3c5  xorps xmm0,xmm0                               
  665c3c8  movaps [rbp+0x290],xmm0                       
  665c3cf  movaps [rbp+0x280],xmm0                       
  665c3d6  movaps [rbp+0x270],xmm0                       

// Interpretation [V]: exact rdis lines above. Completes the second scan loop's release path (je back to loop at 0x665c305; lock dec [rsi+8]; dtors via [0xF99FFA0]; jmp back to loop). Then: if byte [rbp+0x520]!=1 → 0x665d11d (inside cold range); rcx=[rbp+0x4E0]; test; if zero → 0x665d11d; rdx=[rbp+0x4F0]; jmp 0x665ca9c (jumps forward into cold-range region 0x665cf64..0x665d7e5 — target not yet disassembled in this unit [?]). Fall-through at 0x665c373: zeroes rcx; [rbp+0x4A0]=[rbp+0x508]; [rbp+0x4A8]=0; [rbp+0x4B0]=al; [rbp+0x4C8]=[rbp+0x530]; xmm0=[rbp+0x520]→[rbp+0x4B8]; rcx=0x9D0+[rsi+0x10]; call sub_5aba5c0 → rsi=rax; rdx=&[rbp+0x478]; zero xmm0 stored to [rbp+0x290],[rbp+0x280],[rbp+0x270].

### Residual Phase 3 — 0x665c3dd..0x665c4ae  [V]
; from rdis `dis 0x665c3dd 40` (40 instructions)
  665c3dd  movaps [rbp+0x260],xmm0                       
  665c3e4  movaps [rbp+0x250],xmm0                       
  665c3eb  movaps [rbp+0x240],xmm0                       
  665c3f2  movaps [rbp+0x230],xmm0                       
  665c3f9  movaps [rbp+0x220],xmm0                       
  665c400  movaps [rbp+0x210],xmm0                       
  665c407  movaps [rbp+0x200],xmm0                       
  665c40e  movaps [rbp+0x1F0],xmm0                       
  665c415  movaps [rbp+0x1E0],xmm0                       
  665c41c  mov qword ptr [rbp+0x2A0],0                   
  665c427  lea rcx,[rax+0x780]                           
  665c42e  call 0x675F3B0                                ; -> sub_675f3b0
  665c433  nop                                           
  665c434  mov eax,[rsi+0x788]                           
  665c43a  sub eax,[rsi+0x780]                           
  665c440  shr eax,3                                     
  665c443  imul eax,0xFFFF8BA3                           
  665c449  dec eax                                       
  665c44b  mov [rbp+0x208],ax                            
  665c452  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c459  mov rax,[rcx]                                 
  665c45c  mov rax,[rax+0x10]                            
  665c460  mov dl,0x4A                                   
  665c462  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c468  nop                                           
  665c469  mov [rbp+0x540],al                            
  665c46f  mov rdx,[rsi+0x8A8]                           
  665c476  cmp rdx,[rsi+0x8B0]                           
  665c47d  je short 0x665C493                            ; -> loc_665c493
  665c47f  movzx eax,word ptr [rbp+0x470]                
  665c486  mov [rdx],ax                                  
  665c489  add qword ptr [rsi+0x8A8],2                   
  665c491  jmp short 0x665C4A7                           ; -> loc_665c4a7

loc_665c493:  ; from 665c47d
  665c493  lea r8,[rbp+0x470]                            
  665c49a  lea rcx,[rsi+0x8A0]                           
  665c4a1  call 0x1EF6F90                                ; -> sub_1ef6f90
  665c4a6  nop                                           

loc_665c4a7:  ; from 665c491
  665c4a7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c4ae  mov rax,[rcx]                                 

// Interpretation [V]: exact rdis lines above. Zeroes xmm0 into frame slots [rbp+0x260]..[rbp+0x1E0] and [rbp+0x2A0]=0; lea rcx=[rax+0x780]; call sub_675f3b0; count=(([rsi+0x788]-[rsi+0x780])>>3)*0xFFFF8BA3-1 → [rbp+0x208] (same element-count idiom as oc_U-SK1b phases 2/5/9/13); then the standard [0x1233E1B0]-vt deref + call qword ptr [0xF99FFA0] (sub_eea6040) with dl=0x4A → [rbp+0x540]=al. Branch: if [rsi+0x8A8]==[rsi+0x8B0] → loc_665c493: lea r8=&[rbp+0x470], lea rcx=[rsi+0x8A0], call sub_1ef6f90; else movzx ax,[rbp+0x470] → [rdx], [rsi+0x8A8]+=2, jmp loc_665c4a7 which repeats the vtable/dl=0x4A pattern.

### Residual Phase 4 — 0x665c4ae..0x665c56c  [V]
; from rdis `dis 0x665c4ae 40` (40 instructions; rdis adds "; R a0+0x0" annotations on the first two lines)
  665c4ae  mov rax,[rcx]                                 ; R a0+0x0
  665c4b1  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  665c4b5  movzx edx,byte ptr [rbp+0x540]                
  665c4bc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c4c2  nop                                           
  665c4c3  mov eax,[rsi+0x8A8]                           
  665c4c9  sub eax,[rsi+0x8A0]                           
  665c4cf  shr eax,1                                     
  665c4d1  dec eax                                       
  665c4d3  mov [rbp+0x1F0],ax                            
  665c4da  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c4e1  mov rax,[rcx]                                 
  665c4e4  mov rax,[rax+0x10]                            
  665c4e8  mov dl,0x4A                                   
  665c4ea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c4f0  mov [rbp+0x540],al                            
  665c4f6  lea rdx,[rbp+0x428]                           
  665c4fd  lea rcx,[rsi+0x648]                           
  665c504  call 0x675FB30                                ; -> sub_675fb30
  665c509  nop                                           
  665c50a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c511  mov rax,[rcx]                                 
  665c514  mov rax,[rax+0x10]                            
  665c518  movzx edx,byte ptr [rbp+0x540]                
  665c51f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c525  nop                                           
  665c526  mov qword ptr [rbp+0x1E0],0x2001001           
  665c531  mov eax,[rsi+0x650]                           
  665c537  sub eax,[rsi+0x648]                           
  665c53d  shr eax,3                                     
  665c540  imul eax,0xFFFF8E39                           
  665c546  dec eax                                       
  665c548  mov [rbp+0x222],ax                            
  665c54f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c556  mov rax,[rcx]                                 
  665c559  mov rax,[rax+0x10]                            
  665c55d  mov dl,0x4A                                   
  665c55f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c565  nop                                           
  665c566  mov [rbp+0x540],al                            

// Interpretation [V]: exact rdis lines above. Third consecutive [0x1233E1B0]-vt deref + call qword ptr [0xF99FFA0] (sub_eea6040) with dl=0x4A → [rbp+0x540]=al; count=(([rsi+0x8A8]-[rsi+0x8A0])>>1)-1 → [rbp+0x1F0] (word-sized element variant); vtable/dl=0x4A pattern again → [rbp+0x540]=al; lea rdx=&[rbp+0x428], lea rcx=[rsi+0x648], call sub_675fb30; vtable pattern again; [rbp+0x1E0]=0x2001001; count=(([rsi+0x650]-[rsi+0x648])>>3)*0xFFFF8E39-1 → [rbp+0x222]; vtable pattern again → [rbp+0x540]=al.

### Residual Phase 5 — 0x665c56c..0x665c635  [V]
; from rdis `dis 0x665c56c 40` (40 instructions)
  665c56c  mov rbx,[rsi+0x770]                           
  665c573  cmp rbx,[rsi+0x778]                           
  665c57a  je short 0x665C5B9                            ; -> loc_665c5b9
  665c57c  mov rax,[rbp+0x3A0]                           
  665c583  mov [rbx],rax                                 
  665c586  lea rcx,[rbx+8]                               
  665c58a  mov rdx,rdi                                   
  665c58d  call 0xE869FF0                                ; -> sub_e869ff0
  665c592  nop                                           
  665c593  mov rax,[rbp+0x420]                           
  665c59a  mov [rbx+0x80],rax                            
  665c5a1  mov qword ptr [rbp+0x420],0                   
  665c5ac  add qword ptr [rsi+0x770],0x88                
  665c5b7  jmp short 0x665C5D0                           ; -> loc_665c5d0

loc_665c5b9:  ; from 665c57a
  665c5b9  lea r8,[rbp+0x3A0]                            
  665c5c0  lea rcx,[rsi+0x768]                           
  665c5c7  mov rdx,rbx                                   
  665c5ca  call 0x6760710                                ; -> sub_6760710
  665c5cf  nop                                           

loc_665c5d0:  ; from 665c5b7
  665c5d0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c5d7  mov rax,[rcx]                                 
  665c5da  mov rax,[rax+0x10]                            
  665c5de  movzx edx,byte ptr [rbp+0x540]                
  665c5e5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c5eb  nop                                           
  665c5ec  mov eax,[rsi+0x770]                           
  665c5f2  sub eax,[rsi+0x768]                           
  665c5f8  shr eax,3                                     
  665c5fb  imul eax,0xFFFFF0F1                           
  665c601  dec eax                                       
  665c603  mov [rbp+0x20A],ax                            
  665c60a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c611  mov rax,[rcx]                                 
  665c614  mov rax,[rax+0x10]                            
  665c618  mov dl,0x4A                                   
  665c61a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c620  nop                                           
  665c621  mov [rbp+0x540],al                            
  665c627  mov rdx,[rsi+0x860]                           
  665c62e  cmp rdx,[rsi+0x868]                           

// Interpretation [V]: exact rdis lines above. If [rsi+0x770] != [rsi+0x778]: rax=[rbp+0x3A0]→[rbx]; rcx=rbx+8; rdx=rdi; call sub_e869ff0; rax=[rbp+0x420]→[rbx+0x80]; [rbp+0x420]=0; [rsi+0x770]+=0x88; jmp loc_665c5d0. Else loc_665c5b9: lea r8=&[rbp+0x3A0], lea rcx=[rsi+0x768], rdx=rbx, call sub_6760710 (mirrors oc_U-SK1b phase 1). loc_665c5d0: vtable deref + call [0xF99FFA0] (sub_eea6040) dl=0x4A → [rbp+0x540]=al; count=(([rsi+0x770]-[rsi+0x768])>>3)*0xFFFFF0F1-1 → [rbp+0x20A]; vtable pattern again → [rbp+0x540]=al; rdx=[rsi+0x860]; cmp rdx,[rsi+0x868] (continues next phase).

### Residual Phase 6 — 0x665c635..0x665c6ed  [V]
; from rdis `dis 0x665c635 40` (38 instructions shown before --max 40 cut; last shown starts at 0x665c6e5, size 8 → phase end 0x665c6ed)
  665c635  je short 0x665C643                            ; -> loc_665c643
  665c637  inc rdx                                       
  665c63a  mov [rsi+0x860],rdx                           
  665c641  jmp short 0x665C650                           ; -> loc_665c650

loc_665c643:  ; from 665c635
  665c643  lea rcx,[rsi+0x858]                           
  665c64a  call 0x6760E60                                ; -> sub_6760e60
  665c64f  nop                                           

loc_665c650:  ; from 665c641
  665c650  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c657  mov rax,[rcx]                                 
  665c65a  mov rax,[rax+0x10]                            
  665c65e  movzx edx,byte ptr [rbp+0x540]                
  665c665  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c66b  nop                                           
  665c66c  mov qword ptr [rbp+0x1E0],0x2003009           
  665c677  mov eax,[rsi+0x858]                           
  665c67d  not eax                                       
  665c67f  add eax,[rsi+0x860]                           
  665c685  mov [rbp+0x1F6],ax                            
  665c68c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c693  mov rax,[rcx]                                 
  665c696  mov rax,[rax+0x10]                            
  665c69a  mov dl,0x4A                                   
  665c69c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c6a2  nop                                           
  665c6a3  mov [rbp+0x540],al                            
  665c6a9  lea r8,[rbp+0x344]                            
  665c6b0  mov rdx,[rsi+0x758]                           
  665c6b7  cmp rdx,[rsi+0x760]                           
  665c6be  je short 0x665C737                            ; -> loc_665c737
  665c6c0  mov eax,[r8+0x10]                             
  665c6c4  mov [rdx+0x10],eax                            
  665c6c7  movups xmm0,[r8]                              
  665c6cb  movups [rdx],xmm0                             
  665c6ce  movzx eax,byte ptr [rbp+0x358]                
  665c6d5  mov [rdx+0x14],al                             
  665c6d8  movss xmm0,[rbp+0x35C]                        
  665c6e0  movss [rdx+0x18],xmm0                         
  665c6e5  movss xmm0,[rbp+0x360]                        

// Interpretation [V]: exact rdis lines above. If rdx==[rsi+0x868] → loc_665c643: lea rcx=[rsi+0x858], call sub_6760e60 (mirrors oc_U-SK1b phase 8/16 grow-path). Else inc rdx, [rsi+0x860]=rdx, jmp loc_665c650. loc_665c650: vtable deref + call [0xF99FFA0] (sub_eea6040) dl=0x4A → [rbp+0x540]=al; [rbp+0x1E0]=0x2003009; eax=[rsi+0x858]; not eax; eax+=[rsi+0x860] → [rbp+0x1F6] (same not/add count idiom as oc_U-SK1b phase 9); vtable pattern → [rbp+0x540]=al; lea r8=&[rbp+0x344]; rdx=[rsi+0x758]; if rdx==[rsi+0x760] → loc_665c737 (grow path); else copy entry: eax=[r8+0x10]→[rdx+0x10], movups [r8]→[rdx], byte [rbp+0x358]→[rdx+0x14], floats [rbp+0x35C/0x360/0x364...]→[rdx+0x18/0x1C/0x20...] (mirrors oc_U-SK1b phase 11 entry copy).

### Residual Phase 8 — 0x665c7ad..0x665c84e  [V]
; from rdis `dis 0x665c7ad 40` (40 instructions)
  665c7ad  mov [rsi+0x710],rbx                           
  665c7b4  jmp 0x665C928                                 ; -> loc_665c928
  665c7b9  mov [rbp+0x540],dl                            
  665c7bf  mov r13,rbx                                   
  665c7c2  sub r13,[rsi+0x708]                           
  665c7c9  mov rax,0x7FFFFFFFFFFFFFFF                    
  665c7d3  cmp r13,rax                                   
  665c7d6  je 0x665E41C                                  ; -> loc_665e41c
  665c7dc lea r12,[r13+1]                               
  665c7e0  mov rdi,r13                                   
  665c7e3  shr rdi,1                                     
  665c7e6  mov rcx,rdi                                   
  665c7e9  xor rcx,rax                                   
  665c7ec add rdi,r13                                   
  665c7ef  cmp rdi,r12                                   
  665c7f2  cmovbe rdi,r12                                
  665c7f6  cmp r13,rcx                                   
  665c7f9  cmova rdi,rax                                 
  665c7fd  test rdi,rdi                                  
  665c800  je short 0x665C877                            ; -> loc_665c877
  665c802  cmp rdi,0x1000                                
  665c809  jb short 0x665C84E                            ; -> loc_665c84e
  665c80b  cmp rdi,0xFFFFFFFFFFFFFFD9                    
  665c80f  jae 0x665E7A7                                 ; -> loc_665e7a7
  665c815  lea r15,[rdi+0x27]                            
  665c819  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  665c820  mov rax,[rcx]                                 
  665c823  mov rax,[rax+8]                               
  665c827  mov rdx,r15                                   
  665c82a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c830  nop                                           
  665c831  mov r14,rax                                   
  665c834  test rax,rax                                  
  665c837  je 0x665D42C                                  ; -> loc_665d42c

loc_665c83d:  ; from 665d435
  665c83d  mov rax,r14                                   
  665c840  add r14,0x27                                  
  665c844  and r14,0xFFFFFFFFFFFFFFE0                    
  665c848  mov [r14-8],rax                               
  665c84c  jmp short 0x665C87A                           ; -> loc_665c87a

// Interpretation [V]: exact rdis lines above. [rsi+0x710]=rbx; jmp 0x665c928 (forward within residual-tail region, < 0x665cf64). Else-path: [rbp+0x540]=dl; r13=rbx-[rsi+0x708]; cap size at 0x7FFFFFFFFFFFFFFF; r12=r13+1; compute next power-of-two-ish clamp: rdi=r13>>1; rcx=rdi xor max; rdi+=r13; cmovbe rdi=r12 (round up to at least r13+1); cmova rdi=max if r13>rcx (clamp to max). test rdi,rdi; je → loc_665c877; if rdi<0x1000 → loc_665c84e; if rdi>=0xFFFFFFFFFFFFFFD9 → loc_665e7a7 (both > cold-range head, targets not disassembled here [?]). lea r15=rdi+0x27; allocator fast path: rcx=[0x1233E1A8] (DIFFERENT global than [0x1233E1B0]); rax=[rcx]; rax=[rax+8]; rdx=r15; call [0xF99FFA0] (sub_eea6040); r14=rax; if rax==0 → loc_665d42c (INSIDE cold range 0x665cf64..0x665d7e5 — cold allocator path, [?]). loc_665c83d (target of cold-range 665d435's jmp): rax=r14; r14=(r14+0x27)&~0x1F (32-byte align); [r14-8]=rax (store size header); jmp loc_665c87a (continues next phase).

### Residual Phase 9 — 0x665c84e..0x665c8e9  [V]
; from rdis `dis 0x665c84e 40` (40 instructions)
  665c84e  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  665c855  mov rax,[rcx]                                 
  665c858  mov rax,[rax+8]                               
  665c85c  mov rdx,rdi                                   
  665c85f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c865  nop                                           
  665c866  mov r14,rax                                   
  665c869  test rax,rax                                  
  665c86c  jne short 0x665C87A                           ; -> loc_665c87a
  665c86e  mov rcx,rdi                                   
  665c871  call 0x9BC830                                 ; -> sub_9bc830
  665c876  nop                                           
  665c877  xor r14d,r14d                                 

loc_665c87a:  ; from 665c86c
  665c87a  cmp rbx,[rsi+0x710]                           
  665c881  je short 0x665C8B1                            ; -> loc_665c8b1
  665c883  lea r15,[r14+r13]                             
  665c887  inc r15                                       
  665c88a  mov rdx,[rsi+0x708]                           
  665c891  mov r8,rbx                                    
  665c894  sub r8,rdx                                    
  665c897  mov rcx,r14                                   
  665c89a  call 0xEEC6DE0                                ; -> sub_eec6de0
  665c89f  mov r8,[rsi+0x710]                            
  665c8a6  sub r8,rbx                                    
  665c8a9  mov rcx,r15                                   
  665c8ac  mov rdx,rbx                                   
  665c8af  jmp short 0x665C8C1                           ; -> loc_665c8c1

loc_665c8b1:  ; from 665c881
  665c8b1  mov rdx,[rsi+0x708]                           
  665c8b8  sub rbx,rdx                                   
  665c8bb  mov rcx,r14                                   
  665c8be  mov r8,rbx                                    

loc_665c8c1:  ; from 665c8af
  665c8c1  call 0xEEC6DE0                                ; -> sub_eec6de0
  665c8c6  mov rcx,[rsi+0x708]                           
  665c8cd  test rcx,rcx                                  
  665c8d0  je short 0x665C906                            ; -> loc_665c906
  665c8d2  mov rdx,[rsi+0x718]                           
  665c8d9  sub rdx,rcx                                   
  665c8dc  cmp rdx,0x1000                                
  665c8e3  jb short 0x665C901                            ; -> loc_665c901
  665c8e5  mov rax,[rcx-8]                               

// Interpretation [V]: exact rdis lines above. Allocator continuation: rcx=[0x1233E1A8]; rax=[rcx]; rax=[rax+8]; rdx=rdi; call [0xF99FFA0] (sub_eea6040); r14=rax; if rax!=0 → loc_665c87a else rcx=rdi, call sub_9bc830 (fallback allocator seen at cold-tail 665d19e/665d1ad/...). loc_665c877: r14d=0. loc_665c87a: if rbx==[rsi+0x710] → loc_665c8b1 else r15=r14+r13+1; rdx=[rsi+0x708]; r8=rbx-rdx; rcx=r14; call sub_eec6de0; r8=[rsi+0x710]-rbx; rcx=r15; rdx=rbx; jmp loc_665c8c1. loc_665c8b1: rdx=[rsi+0x708]; rbx-=rdx; rcx=r14; r8=rbx. loc_665c8c1: call sub_eec6de0; rcx=[rsi+0x708]; if zero → loc_665c906; rdx=[rsi+0x718]-rcx; if rdx<0x1000 → loc_665c901; rax=[rcx-8] (reads preceding heap chunk's size/header — continues next phase).

### Residual Phase 10 — 0x665c8e9..0x665c9aa  [V]
; from rdis `dis 0x665c8e9 40` (40 instructions; last shown starts at 0x665c9a3, lea r8,[rbp+0x1E0] = 7 bytes → phase end 0x665c9aa)
  665c8e9  add rcx,0xFFFFFFFFFFFFFFF8                    
  665c8ed  sub rcx,rax                                   
  665c8f0  cmp rcx,0x20                                  
  665c8f4  jae 0x665D43A                                 ; -> loc_665d43a
  665c8fa  add rdx,0x27                                  
  665c8fe  mov rcx,rax                                   
  665c901  call 0xE935700                                ; -> sub_e935700
  665c906  mov [rsi+0x708],r14                           
  665c90d  add r12,r14                                   
  665c910  mov [rsi+0x710],r12                           
  665c917  add rdi,r14                                   
  665c91a  mov [rsi+0x718],rdi                           
  665c921  movzx edx,byte ptr [rbp+0x540]                
  665c928  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c92f  mov rax,[rcx]                                 
  665c932  mov rax,[rax+0x10]                            
  665c936  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c93c  nop                                           
  665c93d  mov qword ptr [rbp+0x1E0],0x2027009           
  665c948  mov eax,[rsi+0x708]                           
  665c94e  not eax                                       
  665c950  add eax,[rsi+0x710]                           
  665c956  mov [rbp+0x212],ax                            
  665c95d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c964  mov rax,[rcx]                                 
  665c967  mov rax,[rax+0x10]                            
  665c96b  mov dl,0x4A                                   
  665c96d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c973  nop                                           
  665c974  mov [rbp+0x540],al                            
  665c97a  mov rax,[rsi+8]                               
  665c97e  cmp rax,[rsi+0x10]                            
  665c982  je short 0x665C9A3                            ; -> loc_665c9a3
  665c984  lea rdx,[rbp+0x1E0]                           
  665c98b  mov r8d,0xC8                                  
  665c991  mov rcx,rax                                   
  665c994  call 0xEEC6EC0                                ; -> sub_eec6ec0
  665c999  add qword ptr [rsi+8],0xC8                    
  665c9a1  jmp short 0x665C9B6                           ; -> loc_665c9b6

loc_665c9a3:  ; from 665c982
  665c9a3  lea r8,[rbp+0x1E0]                            

// Interpretation [V]: exact rdis lines above. rcx+=0xFFFFFFFFFFFFFFF8; rcx-=rax; if rcx>=0x20 → loc_665d43a (INSIDE cold range — cold-tail phase 8 target, [?]); else rdx+=0x27; rcx=rax; call sub_e935700; [rsi+0x708]=r14; r12+=r14; [rsi+0x710]=r12; rdi+=r14; [rsi+0x718]=rdi (bump allocator cursor). movzx edx,[rbp+0x540]; vtable deref + call [0xF99FFA0] dl=0x4A; [rbp+0x1E0]=0x2027009; not eax; eax+=[rsi+0x710] → [rbp+0x212] (count idiom); vtable pattern again → [rbp+0x540]=al. Buffer tail check: rax=[rsi+8]; if rax==[rsi+0x10] → loc_665c9a3 (lea r8=&[rbp+0x1E0], continues) else lea rdx=&[rbp+0x1E0]; r8d=0xC8; rcx=rax; call sub_eec6ec0 (mirrors oc_U-SK1b phase 18's 0xC8 copy); [rsi+8]+=0xC8; jmp loc_665c9b6 (continues next phase).

### Residual Phase 11 — 0x665c9aa..0x665ca49  [V]
; from rdis `dis 0x665c9aa 40` (40 instructions; last shown starts at 0x665ca42, mov rsi,[rdi+8] = 7 bytes → phase end 0x665ca49)
  665c9aa  mov rcx,rsi                                   
  665c9ad  mov rdx,rax                                   
  665c9b0  call 0x5ABA6D0                                ; -> sub_5aba6d0
  665c9b5  nop                                           
  665c9b6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c9bd  mov rax,[rcx]                                 
  665c9c0  mov rax,[rax+0x10]                            
  665c9c4  movzx edx,byte ptr [rbp+0x540]                
  665c9cb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c9d1  nop                                           
  665c9d2  lea rcx,[rbp+0x340]                           
  665c9d9  call 0x66A9AD0                                ; -> sub_66a9ad0
  665c9de  cmp byte ptr [rbp+0x518],3                    
  665c9e5  jne short 0x665CA1E                           ; -> loc_665ca1e
  665c9e7  mov rsi,[rbp+0x510]                           
  665c9ee  test rsi,rsi                                  
  665c9f1  je short 0x665CA1E                            ; -> loc_665ca1e
  665c9f3  lock dec dword ptr [rsi+8]                    
  665c9f7  jne short 0x665CA1E                           ; -> loc_665ca1e
  665c9f9  mov rax,[rsi]                                 
  665c9fc  mov rax,[rax]                                 
  665c9ff  mov rcx,rsi                                   
  665ca02  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ca08  lock dec dword ptr [rsi+0xC]                  
  665ca0c  jne short 0x665CA1E                           ; -> loc_665ca1e
  665ca0e  mov rax,[rsi]                                 
  665ca11  mov rax,[rax+8]                               
  665ca15  mov rcx,rsi                                   
  665ca18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ca1e:  ; from 665c9e5, 665c9f1, 665c9f7, 665ca0c
  665ca1e  mov rdi,[rbp+0x4E8]                           
  665ca25  test rdi,rdi                                  
  665ca28  je short 0x665CA78                            ; -> loc_665ca78
  665ca2a  mov rbx,[rbp+0x4F0]                           
  665ca31  jmp short 0x665CA37                           ; -> loc_665ca37

loc_665ca33:  ; from 665ca40, 665ca49, 665ca4f, 665ca64, 665ca76
  665ca33  add rdi,0x28                                  

loc_665ca37:  ; from 665ca31
  665ca37  cmp rdi,rbx                                   
  665ca3a  je short 0x665CA78                            ; -> loc_665ca78
  665ca3c  cmp byte ptr [rdi+0x18],2                     
  665ca40  jne short 0x665CA33                           ; -> loc_665ca33
  665ca42  mov rsi,[rdi+8]                               

// Interpretation [V]: exact rdis lines above. rcx=rsi; rdx=rax; call sub_5aba6d0 (buffer-full path, mirrors oc_U-SK1b phase 19). vtable deref + call [0xF99FFA0] dl=0x4A → [rbp+0x540]=al; lea rcx=&[rbp+0x340]; call sub_66a9ad0. If byte [rbp+0x518]!=3 → loc_665ca1e; else rsi=[rbp+0x510]; ref-counted release loop over [rbp+0x510] objects (test; lock dec [rsi+8]; dtors via [0xF99FFA0]; lock dec [rsi+0xC]) — same as oc_U-SK1b cold phases 5/6. loc_665ca1e: scan loop rdi=[rbp+0x4E8]→rbx=[rbp+0x4F0] in 0x28 steps, skip byte [rdi+0x18]!=2, release object [rdi+8] (same as cold phase 5 / residual phase 2's second loop; release continues past 0x665ca49).

### Residual Phase 12 — 0x665ca49..0x665cb00  [V]
; from rdis `dis 0x665ca49 40` (40 instructions; last shown starts at 0x665caf9, mov rax,[rbp+0x1C0] = 7 bytes → phase end 0x665cb00)
  665ca49  je short 0x665CA33                            ; -> sub_665ca33
  665ca4b  lock dec dword ptr [rsi+8]                    
  665ca4f  jne short 0x665CA33                           ; -> sub_665ca33
  665ca51  mov rax,[rsi]                                 
  665ca54  mov rax,[rax]                                 
  665ca57  mov rcx,rsi                                   
  665ca5a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ca60  lock dec dword ptr [rsi+0xC]                  
  665ca64  jne short 0x665CA33                           ; -> sub_665ca33
  665ca66  mov rax,[rsi]                                 
  665ca69  mov rax,[rax+8]                               
  665ca6d  mov rcx,rsi                                   
  665ca70  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ca76  jmp short 0x665CA33                           ; -> sub_665ca33
  665ca78  cmp byte ptr [rbp+0x1B0],1                    
  665ca7f  jne 0x665D11D                                 ; -> loc_665d11d
  665ca85  mov rcx,[rbp+0x170]                           
  665ca8c  test rcx,rcx                                  
  665ca8f  je 0x665D11D                                  ; -> loc_665d11d
  665ca95  mov rdx,[rbp+0x180]                           
  665ca9c  sub rdx,rcx                                   
  665ca9f  cmp rdx,0x1000                                
  665caa6  jb short 0x665CAC4                            ; -> loc_665cac4
  665caa8  mov rax,[rcx-8]                               
  665caac  add rcx,0xFFFFFFFFFFFFFFF8                    
  665cab0  sub rcx,rax                                   
  665cab3  cmp rcx,0x20                                  
  665cab7  jae 0x665D43A                                 ; -> loc_665d43a
  665cabd  or rdx,0x27                                   
  665cac1  mov rcx,rax                                   

loc_665cac4:  ; from 665caa6
  665cac4  call 0xE935700                                ; -> sub_e935700
  665cac9  jmp 0x665D11D                                 ; -> loc_665d11d
  665cace  xor ecx,ecx                                   
  665cad0  mov rdx,[rbp+0x198]                           
  665cad7  mov [rbp+0x3D0],rdx                           
  665cade  mov [rbp+0x3D8],rcx                           
  665cae5  mov [rbp+0x3E0],al                            
  665caeb  lea r9,[rbp+0x3A0]                            
  665caf2  lea r8,[rbp+0x3A8]                            
  665caf9  mov rax,[rbp+0x1C0]                           

// Interpretation [V]: exact rdis lines above. Completes release loop (je → 0x665ca33 add rdi,0x28 scan back). Then: if byte [rbp+0x1B0]!=1 → 0x665d11d (cold-range head region); rcx=[rbp+0x170]; test; je → 0x665d11d; rdx=[rbp+0x180]; rdx-=rcx; if rdx<0x1000 → loc_665cac4; rax=[rcx-8]; rcx-=0x8; rcx-=rax; if rcx>=0x20 → loc_665d43a (INSIDE cold range, cold-tail phase 8); or rdx,0x27; rcx=rax. loc_665cac4: call sub_e935700; jmp 0x665d11d (cold range — [?] whether 0x665d11d resumes within cold range head). Note 0x665ca9c is the target residual Phase 2 jumped to. Then: ecx=0; rdx=[rbp+0x198]; [rbp+0x3D0]=rdx; [rbp+0x3D8]=rcx; [rbp+0x3E0]=al; lea r9=&[rbp+0x3A0]; lea r8=&[rbp+0x3A8]; rax=[rbp+0x1C0] (memcpy-ish setup, r8/r9 = frame src/dst refs — continues next phase).

### Residual Phase 13 — 0x665cb00..0x665cbda  [V]
; from rdis `dis 0x665cb00 40` (44 lines shown incl. loc labels; last instruction starts at 0x665cbd3, cmp byte ptr [rbp+0x440],1 = 7 bytes → phase end 0x665cbda)
  665cb00  mov [rbp+0x3F8],rax                           
  665cb07  movaps xmm0,[rbp+0x1B0]                       
  665cb0e  movups [rbp+0x3E8],xmm0                       
  665cb15  lea rdi,[rbp+0x400]                           
  665cb1c  mov byte ptr [rbp+0x440],0xFF                 
  665cb23  movzx ebx,byte ptr [rbp+0x160]                
  665cb2a  movzx eax,bl                                  
  665cb2d  cmp eax,1                                     
  665cb30  jg short 0x665CB70                            ; -> loc_665cb70
  665cb32  test eax,eax                                  
  665cb34  jne short 0x665CB85                           ; -> loc_665cb85
  665cb36  movaps xmm0,[rbp+0x120]                       
  665cb3d  movaps xmm1,[rbp+0x130]                       
  665cb44  movaps xmm2,[rbp+0x140]                       
  665cb4b  movaps xmm3,[rbp+0x150]                       
  665cb52  movaps [rbp+0x400],xmm0                       
  665cb59  movaps [rbp+0x410],xmm1                       
  665cb60  movaps [rbp+0x420],xmm2                       
  665cb67  movaps [rbp+0x430],xmm3                       
  665cb6e  jmp short 0x665CBB6                           ; -> loc_665cbb6

loc_665cb70:  ; from 665cb30
  665cb70  cmp eax,2                                     
  665cb73  jne short 0x665CBBC                           ; -> loc_665cbbc
  665cb75  mov rax,[rbp+0x120]                           
  665cb7c  mov [rbp+0x400],rax                           
  665cb83  jmp short 0x665CBB6                           ; -> loc_665cbb6

loc_665cb85:  ; from 665cb34
  665cb85  mov rax,[rbp+0x130]                           
  665cb8c  mov qword ptr [rbp+0x130],0                   
  665cb97  movaps xmm0,[rbp+0x120]                       
  665cb9e  xorps xmm1,xmm1                               
  665cba1  movaps [rbp+0x120],xmm1                       
  665cba8  movaps [rbp+0x400],xmm0                       
  665cbaf  mov [rbp+0x410],rax                           

loc_665cbb6:  ; from 665cb6e, 665cb83
  665cbb6  mov [rbp+0x440],bl                            

loc_665cbbc:  ; from 665cb73
  665cbbc  mov ecx,0x9D0                                 
  665cbc1  add rcx,[rsi+0x10]                            
  665cbc5  mov [rsp+0x20],r12                            
  665cbca  mov rdx,rdi                                   
  665cbcd  call 0x67E6730                                ; -> sub_67e6730
  665cbd2  nop                                           
  665cbd3  cmp byte ptr [rbp+0x440],1                    

// Interpretation [V]: exact rdis lines above. [rbp+0x3F8]=rax; xmm0=[rbp+0x1B0]→[rbp+0x3E8]; rdi=&[rbp+0x400]; [rbp+0x440]=0xFF; bl=[rbp+0x160]; eax=bl; if eax>1 → loc_665cb70; if eax!=0 → loc_665cb85; else eax==0 path: xmm0..xmm3 = [rbp+0x120/0x130/0x140/0x150] stored to [rbp+0x400..0x430], jmp loc_665cbb6. loc_665cb70: if eax!=2 → loc_665cbbc; else rax=[rbp+0x120]→[rbp+0x400]; jmp loc_665cbb6. loc_665cb85: rax=[rbp+0x130]; [rbp+0x130]=0; xmm0=[rbp+0x120]; xmm1=0; [rbp+0x120]=0; [rbp+0x400]=xmm0; [rbp+0x410]=rax (string/object descriptor move — [I]); jmp into loc_665cbb6; [rbp+0x440]=bl. loc_665cbbc: ecx=0x9D0; rcx=0x9D0+[rsi+0x10]; [rsp+0x20]=r12; rdx=rdi; call sub_67e6730; cmp byte [rbp+0x440],1 (continues next phase).

### Residual Phase 14 — 0x665cbda..0x665cc82  [V]
; from rdis `dis 0x665cbda 40` (39 instructions shown before --max 40; last shown starts at 0x665cc7b, cmp byte ptr [rbp+0x1A8],3 = 7 bytes → phase end 0x665cc82)
  665cbda  jne short 0x665CC2A                           ; -> loc_665cc2a
  665cbdc  mov rcx,[rbp+0x400]                           
  665cbe3  test rcx,rcx                                  
  665cbe6  je short 0x665CC2A                            ; -> loc_665cc2a
  665cbe8  mov rdx,[rbp+0x410]                           
  665cbef  sub rdx,rcx                                   
  665cbf2  cmp rdx,0x1000                                
  665cbf9  jb short 0x665CC17                            ; -> loc_665cc17
  665cbfb  mov rax,[rcx-8]                               
  665cbff  add rcx,0xFFFFFFFFFFFFFFF8                    
  665cc03  sub rcx,rax                                   
  665cc06  cmp rcx,0x20                                  
  665cc0a  jae 0x665D43A                                 ; -> loc_665d43a
  665cc10  or rdx,0x27                                   
  665cc14  mov rcx,rax                                   

loc_665cc17:  ; from 665cbf9
  665cc17  call 0xE935700                                ; -> sub_e935700
  665cc1c  xorps xmm0,xmm0                               
  665cc1f  movups [rdi],xmm0                             
  665cc22  mov qword ptr [rdi+0x10],0                    

loc_665cc2a:  ; from 665cbda, 665cbe6
  665cc2a  lea rcx,[rbp+0x340]                           
  665cc31  call 0x67B5160                                ; -> sub_67b5160
  665cc36  cmp bl,1                                      
  665cc39  jne short 0x665CC7B                           ; -> loc_665cc7b
  665cc3b  mov rcx,[rbp+0x120]                           
  665cc42  test rcx,rcx                                  
  665cc45  je short 0x665CC7B                           ; -> loc_665cc7b
  665cc47  mov rdx,[rbp+0x130]                           
  665cc4e  sub rdx,rcx                                   
  665cc51  cmp rdx,0x1000                                
  665cc58  jb short 0x665CC76                            ; -> loc_665cc76
  665cc5a  mov rax,[rcx-8]                               
  665cc5e  add rcx,0xFFFFFFFFFFFFFFF8                    
  665cc62  sub rcx,rax                                   
  665cc65  cmp rcx,0x20                                  
  665cc69  jae 0x665D43A                                 ; -> loc_665d43a
  665cc6f  or rdx,0x27                                   
  665cc73  mov rcx,rax                                   

loc_665cc76:  ; from 665cc58
  665cc76  call 0xE935700                                ; -> sub_e935700

loc_665cc7b:  ; from 665cc39, 665cc45
  665cc7b  cmp byte ptr [rbp+0x1A8],3                    

// Interpretation [V]: exact rdis lines above. Continues phase 13: cmp byte [rbp+0x440],1; jne → loc_665cc2a; rcx=[rbp+0x400]; test; je → loc_665cc2a; rdx=[rbp+0x410]-rcx; if rdx<0x1000 → loc_665cc17; rax=[rcx-8]; rcx-=0x8; rcx-=rax; if rcx>=0x20 → loc_665d43a (INSIDE cold range); or rdx,0x27; rcx=rax. loc_665cc17: call sub_e935700; xmm0=0; [rdi]=0; [rdi+0x10]=0. loc_665cc2a: lea rcx=&[rbp+0x340]; call sub_67b5160; if bl!=1 → loc_665cc7b; rcx=[rbp+0x120]; test; je → loc_665cc7b; rdx=[rbp+0x130]-rcx; if rdx<0x1000 → loc_665cc76; rax=[rcx-8]; rcx-=0x8; rcx-=rax; if rcx>=0x20 → loc_665d43a (INSIDE cold range); or rdx,0x27; rcx=rax. loc_665cc76: call sub_e935700 (falls through to loc_665cc7b). loc_665cc7b: cmp byte [rbp+0x1A8],3 (continues next phase).


### Residual Phase 15 — 0x665cc82..0x665cd0d  [V]
; from rdis `dis 0x665cc82 40` (40 instructions; --max 40 cut at last shown instruction 0x665cd0a, 3 bytes → phase end 0x665cd0d)
  665cc82  jne short 0x665CCBB                           ; -> loc_665ccbb
  665cc84  mov rsi,[rbp+0x1A0]                           
  665cc8b  test rsi,rsi                                  
  665cc8e  je short 0x665CCBB                            ; -> loc_665ccbb
  665cc90  lock dec dword ptr [rsi+8]                    
  665cc94  jne short 0x665CCBB                           ; -> loc_665ccbb
  665cc96  mov rax,[rsi]                                 
  665cc99  mov rax,[rax]                                 
  665cc9c  mov rcx,rsi                                   
  665cc9f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cca5  lock dec dword ptr [rsi+0xC]                  
  665cca9  jne short 0x665CCBB                           ; -> loc_665ccbb
  665ccab  mov rax,[rsi]                                 
  665ccae  mov rax,[rax+8]                               
  665ccb2  mov rcx,rsi                                   
  665ccb5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ccbb:  ; from 665cc82, 665cc8e, 665cc94, 665cca9
  665ccbb  mov rdi,[rbp+0x178]                           
  665ccc2  test rdi,rdi                                  
  665ccc5  je short 0x665CD15                            ; -> loc_665cd15
  665ccc7  mov rbx,[rbp+0x180]                           
  665ccce  jmp short 0x665CCD4                           ; -> loc_665ccd4

loc_665ccd0:  ; from 665ccdd, 665cce6, 665ccec, 665cd01, 665cd13
  665ccd0  add rdi,0x28                                  

loc_665ccd4:  ; from 665ccce
  665ccd4  cmp rdi,rbx                                   
  665ccd7  je short 0x665CD15                            ; -> loc_665cd15
  665ccd9  cmp byte ptr [rdi+0x18],2                     
  665ccdd  jne short 0x665CCD0                           ; -> loc_665ccd0
  665ccdf  mov rsi,[rdi+8]                               
  665cce3  test rsi,rsi                                  
  665cce6  je short 0x665CCD0                           ; -> loc_665ccd0
  665cce8  lock dec dword ptr [rsi+8]                    
  665ccec  jne short 0x665CCD0                           ; -> loc_665ccd0
  665ccee  mov rax,[rsi]                                 
  665ccf1  mov rax,[rax]                                 
  665ccf4  mov rcx,rsi                                   
  665ccf7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ccfd  lock dec dword ptr [rsi+0xC]                  
  665cd01  jne short 0x665CCD0                           ; -> loc_665ccd0
  665cd03  mov rax,[rsi]                                 
  665cd06  mov rax,[rax+8]                               
  665cd0a  mov rcx,rsi                                   

// Interpretation [V]: exact rdis lines above. Ref-counted object release at [rbp+0x1A0] (same pattern as oc_U-SK1b phases 22-26 and residual phases 2/5/11/12): rsi=[rbp+0x1A0]; test; je → skip loc_665ccbb; lock dec [rsi+8]; jne → skip; dtor1 via call qword ptr [0xF99FFA0] (sub_eea6040); lock dec [rsi+0xC]; jne → skip; dtor2 via same helper; jmp loc_665ccbb. Then second scan loop loc_665ccbb→0x665CD15: rdi=[rbp+0x178] walks in 0x28 steps to rbx=[rbp+0x180], skipping entries with byte [rdi+0x18]!=2, releasing object [rdi+8] via the same ref-count/dtor pair; je exits forward to 0x665CD15 (still inside residual-tail region < 0x665cf64, not disassembled here [?]). Loop-back loc_665ccd0 is the branch target of 665ccdd/665cce6/665ccec/665cd01 plus 665cd13 (from next phase). All line/RVA claims [V]: exact rdis output; anything beyond 0x665cd0d [?].


### Residual Phase 16 — 0x665cd0d..0x665cd9e  [V]
; from rdis `dis 0x665cd0d 40` (40 instructions; --max 40 cut at last shown instruction 0x665cd9b, 3 bytes → phase end 0x665cd9e)
  665cd0d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cd13  jmp short 0x665CCD0                           ; -> sub_665ccd0
  665cd15  mov rsi,[rbp+0x530]                           
  665cd1c  test rsi,rsi                                  
  665cd1f  je short 0x665CD4C                            ; -> loc_665cd4c
  665cd21  lock dec dword ptr [rsi+8]                    
  665cd25  jne short 0x665CD4C                           ; -> loc_665cd4c
  665cd27  mov rax,[rsi]                                 
  665cd2a  mov rax,[rax]                                 
  665cd2d  mov rcx,rsi                                   
  665cd30  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cd36  lock dec dword ptr [rsi+0xC]                  
  665cd3a  jne short 0x665CD4C                           ; -> loc_665cd4c
  665cd3c  mov rax,[rsi]                                 
  665cd3f  mov rax,[rax+8]                               
  665cd43  mov rcx,rsi                                   
  665cd46  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cd4c:  ; from 665cd1f, 665cd25, 665cd3a
  665cd4c  mov rsi,[rbp+0x520]                           
  665cd53  test rsi,rsi                                  
  665cd56  je short 0x665CD83                            ; -> loc_665cd83
  665cd58  lock dec dword ptr [rsi+8]                    
  665cd5c  jne short 0x665CD83                           ; -> loc_665cd83
  665cd5e  mov rax,[rsi]                                 
  665cd61  mov rax,[rax]                                 
  665cd64  mov rcx,rsi                                   
  665cd67  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cd6d  lock dec dword ptr [rsi+0xC]                  
  665cd71  jne short 0x665CD83                           ; -> loc_665cd83
  665cd73  mov rax,[rsi]                                 
  665cd76  mov rax,[rax+8]                               
  665cd7a  mov rcx,rsi                                   
  665cd7d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cd83:  ; from 665cd56, 665cd5c, 665cd71
  665cd83  mov rsi,[rbp+0x510]                           
  665cd8a  test rsi,rsi                                  
  665cd8d  je short 0x665CDBA                            ; -> loc_665cdba
  665cd8f  lock dec dword ptr [rsi+8]                    
  665cd93  jne short 0x665CDBA                           ; -> loc_665cdba
  665cd95  mov rax,[rsi]                                 
  665cd98  mov rax,[rax]                                 
  665cd9b  mov rcx,rsi                                   

// Interpretation [V]: exact rdis lines above. Completes phase 15's second ref-counted release (dtor2 via call [0xF99FFA0]=sub_eea6040 at 0x665cd0d; jmp back to loop-back loc_665ccd0). Then three more ref-counted object releases, same pattern as oc_U-SK1b phases 22-26 and residual phases 2/5/11/12/15: each object (rsi=[rbp+0x530] → loc_665cd4c; rsi=[rbp+0x520] → loc_665cd83; rsi=[rbp+0x510] → loc_665cdba) released via test; lock dec [rsi+8]; jne skip; dtor1 via [0xF99FFA0]; lock dec [rsi+0xC]; jne skip; dtor2 via same helper. Loop targets loc_665cd4c/loc_665cd83/loc_665cdba (each from its own je/jne/jne set). Release at [rbp+0x510] continues past 0x665cd9e (dtor2 call at 0x665cd9e, next phase). All line/RVA claims [V]: exact rdis output; anything beyond 0x665cd9e [?].


### Residual Phase 17 — 0x665cd9e..0x665ce2e  [V]
; from rdis `dis 0x665cd9e 40` (40 instructions; --max 40 cut at last shown instruction 0x665ce2c, 2 bytes → phase end 0x665ce2e)
  665cd9e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cda4  lock dec dword ptr [rsi+0xC]                  
  665cda8  jne short 0x665CDBA                           ; -> loc_665cdba
  665cdaa  mov rax,[rsi]                                 
  665cdad  mov rax,[rax+8]                               
  665cdb1  mov rcx,rsi                                   
  665cdb4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cdba:  ; from 665cda8
  665cdba  mov rsi,[rbp+0x4E8]                           
  665cdc1  test rsi,rsi                                  
  665cdc4  je short 0x665CDF1                            ; -> loc_665cdf1
  665cdc6  lock dec dword ptr [rsi+8]                    
  665cdca  jne short 0x665CDF1                           ; -> loc_665cdf1
  665cdcc  mov rax,[rsi]                                 
  665cdcf  mov rax,[rax]                                 
  665cdd2  mov rcx,rsi                                   
  665cdd5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cddb  lock dec dword ptr [rsi+0xC]                  
  665cddf  jne short 0x665CDF1                           ; -> loc_665cdf1
  665cde1  mov rax,[rsi]                                 
  665cde4  mov rax,[rax+8]                               
  665cde8  mov rcx,rsi                                   
  665cdeb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cdf1:  ; from 665cdc4, 665cdca, 665cddf
  665cdf1  mov rsi,[rbp+0x18]                            
  665cdf5  test rsi,rsi                                  
  665cdf8  je short 0x665CE25                            ; -> loc_665ce25
  665cdfa  lock dec dword ptr [rsi+8]                    
  665cdfe  jne short 0x665CE25                           ; -> loc_665ce25
  665ce00  mov rax,[rsi]                                 
  665ce03  mov rax,[rax]                                 
  665ce06  mov rcx,rsi                                   
  665ce09  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ce0f  lock dec dword ptr [rsi+0xC]                  
  665ce13  jne short 0x665CE25                           ; -> loc_665ce25
  665ce15  mov rax,[rsi]                                 
  665ce18  mov rax,[rax+8]                               
  665ce1c  mov rcx,rsi                                   
  665ce1f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ce25:  ; from 665cdf8, 665cdfe, 665ce13
  665ce25  mov rsi,[rbp-8]                               
  665ce29  test rsi,rsi                                  
  665ce2c  je short 0x665CE59                            ; -> loc_665ce59

// Interpretation [V]: exact rdis lines above. Completes phase 16's [rbp+0x510] dtor2 (call [0xF99FFA0]=sub_eea6040 at 0x665cd9e; lock dec [rsi+0xC]; jne → loc_665cdba; dtor2 call at 0x665cdb4). Then three more ref-counted object releases, same pattern as oc_U-SK1b phases 22-26 and residual phases 2/5/11/12/15/16: each object (rsi=[rbp+0x4E8] → loc_665cdf1; rsi=[rbp+0x18] → loc_665ce25; rsi=[rbp-8] → loc_665ce59) released via test; lock dec [rsi+8]; jne skip; dtor1 via [0xF99FFA0]; lock dec [rsi+0xC]; jne skip; dtor2 via same helper. Loop targets loc_665cdba/loc_665cdf1/loc_665ce25/loc_665ce59 (each from its own je/jne/jne set). Release at [rbp-8] continues past 0x665ce2e: lock dec [rsi+8] at 0x665ce2e is dtor1's pre-decrement; jne → loc_665ce59; dtor1 call [0xF99FFA0] at 0x665ce3d; lock dec [rsi+0xC]; jne → loc_665ce59; dtor2 call at 0x665ce53. All line/RVA claims [V]: exact rdis output; anything beyond 0x665ce2e [?].


### Residual Phase 18 — 0x665ce2e..0x665ceb8  [V]
; from rdis `dis 0x665ce2e 40` (40 instructions; --max 40 cut at last shown instruction 0x665ceb4, 4 bytes → phase end 0x665ceb8)
  665ce2e  lock dec dword ptr [rsi+8]                    
  665ce32  jne short 0x665CE59                           ; -> loc_665ce59
  665ce34  mov rax,[rsi]                                 
  665ce37  mov rax,[rax]                                 
  665ce3a  mov rcx,rsi                                   
  665ce3d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ce43  lock dec dword ptr [rsi+0xC]                  
  665ce47  jne short 0x665CE59                           ; -> loc_665ce59
  665ce49  mov rax,[rsi]                                 
  665ce4c  mov rax,[rax+8]                               
  665ce50  mov rcx,rsi                                   
  665ce53  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ce59:  ; from 665ce32, 665ce47
  665ce59  mov rsi,[rbp-0x18]                            
  665ce5d  test rsi,rsi                                  
  665ce60  je short 0x665CE8D                            ; -> loc_665ce8d
  665ce62  lock dec dword ptr [rsi+8]                    
  665ce66  jne short 0x665CE8D                           ; -> loc_665ce8d
  665ce68  mov rax,[rsi]                                 
  665ce6b  mov rax,[rax]                                 
  665ce6e  mov rcx,rsi                                   
  665ce71  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ce77  lock dec dword ptr [rsi+0xC]                  
  665ce7b  jne short 0x665CE8D                           ; -> loc_665ce8d
  665ce7d  mov rax,[rsi]                                 
  665ce80  mov rax,[rax+8]                               
  665ce84  mov rcx,rsi                                   
  665ce87  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ce8d:  ; from 665ce60, 665ce66, 665ce7b
  665ce8d  mov rsi,[rbp+0x38]                            
  665ce91  test rsi,rsi                                  
  665ce94  je short 0x665CEC1                            ; -> loc_665cec1
  665ce96  lock dec dword ptr [rsi+8]                    
  665ce9a  jne short 0x665CEC1                           ; -> loc_665cec1
  665ce9c  mov rax,[rsi]                                 
  665ce9f  mov rax,[rax]                                 
  665cea2  mov rcx,rsi                                   
  665cea5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ceab  lock dec dword ptr [rsi+0xC]                  
  665ceaf  jne short 0x665CEC1                           ; -> loc_665cec1
  665ceb1  mov rax,[rsi]                                 
  665ceb4  mov rax,[rax+8]                               

// Interpretation [V]: exact rdis lines above. Completes phase 17's [rbp-8] release (lock dec [rsi+8] at 0x665ce2e; jne → loc_665ce59; dtor1 call [0xF99FFA0]=sub_eea6040 at 0x665ce3d; lock dec [rsi+0xC]; jne → loc_665ce59; dtor2 call at 0x665ce53). Then two more ref-counted object releases, same pattern as oc_U-SK1b phases 22-26 and residual phases 2/5/11/12/15/16/17: each object (rsi=[rbp-0x18] → loc_665ce8d; rsi=[rbp+0x38] → loc_665cec1) released via test; lock dec [rsi+8]; jne skip; dtor1 via [0xF99FFA0]; lock dec [rsi+0xC]; jne skip; dtor2 via same helper. Loop targets loc_665ce59/loc_665ce8d/loc_665cec1 (each from its own je/jne/jne set). Release at [rbp+0x38] continues past 0x665ceb8 (dtor2 call at next phase). All line/RVA claims [V]: exact rdis output; anything beyond 0x665ceb8 [?].


### Residual Phase 19 — 0x665ceb8..0x665cf46  [V]
; from rdis `dis 0x665ceb8 40` (40 instructions; --max 40 cut at last shown instruction 0x665cf43, 3 bytes → phase end 0x665cf46)
  665ceb8  mov rcx,rsi                                   
  665cebb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cec1  movzx eax,byte ptr [rbp+0xA8]                 
  665cec8  test al,al                                    
  665ceca  je 0x665CF64                                  ; -> loc_665cf64
  665ced0  cmp byte ptr [rbp+0x88],3                     
  665ced7  jne short 0x665CF10                           ; -> loc_665cf10
  665ced9  mov rsi,[rbp+0x80]                            
  665cee0  test rsi,rsi                                  
  665cee3  je short 0x665CF10                           ; -> loc_665cf10
  665cee5  lock dec dword ptr [rsi+8]                    
  665cee9  jne short 0x665CF10                           ; -> loc_665cf10
  665ceeb  mov rax,[rsi]                                 
  665ceee  mov rax,[rax]                                 
  665cef1  mov rcx,rsi                                   
  665cef4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cefa  lock dec dword ptr [rsi+0xC]                  
  665cefe  jne short 0x665CF10                           ; -> loc_665cf10
  665cf00  mov rax,[rsi]                                 
  665cf03  mov rax,[rax+8]                               
  665cf07  mov rcx,rsi                                   
  665cf0a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cf10:  ; from 665ced7, 665cee3, 665cee9, 665cefe
  665cf10  mov rdi,[rbp+0x58]                            
  665cf14  test rdi,rdi                                  
  665cf17  je short 0x665CF64                            ; -> loc_665cf64
  665cf19  mov rbx,[rbp+0x60]                            
  665cf1d  jmp short 0x665CF23                           ; -> loc_665cf23

loc_665cf1f:  ; from 665cf2c, 665cf35, 665cf3b, 665cf50, 665cf62
  665cf1f  add rdi,0x28                                  

loc_665cf23:  ; from 665cf1d
  665cf23  cmp rdi,rbx                                   
  665cf26  je short 0x665CF64                            ; -> loc_665cf64
  665cf28  cmp byte ptr [rdi+0x18],2                     
  665cf2c  jne short 0x665CF1F                           ; -> loc_665cf1f
  665cf2e  mov rsi,[rdi+8]                               
  665cf32  test rsi,rsi                                  
  665cf35  je short 0x665CF1F                           ; -> loc_665cf1f
  665cf37  lock dec dword ptr [rsi+8]                    
  665cf3b  jne short 0x665CF1F                           ; -> loc_665cf1f
  665cf3d  mov rax,[rsi]                                 
  665cf40  mov rax,[rax]                                 
  665cf43  mov rcx,rsi                                   

// Interpretation [V]: exact rdis lines above. Completes phase 18's [rbp+0x38] release (mov rcx,rsi at 0x665ceb8; dtor2 call [0xF99FFA0]=sub_eea6040 at 0x665cebb). Then a final scan-loop setup: movzx eax,[rbp+0xA8]; if al==0 → 0x665cf64 (COLD RANGE HEAD [V]); cmp byte [rbp+0x88],3; jne → loc_665cf10; else rsi=[rbp+0x80]; ref-counted release (test; lock dec [rsi+8]; jne; dtor1 [0xF99FFA0]; lock dec [rsi+0xC]; jne; dtor2) → loc_665cf10. loc_665cf10: rdi=[rbp+0x58]; test rdi,rdi; je → 0x665cf64 (COLD RANGE HEAD [V]); rbx=[rbp+0x60]; jmp loc_665cf23. Scan loop loc_665cf1f→loc_665cf23: add rdi,0x28; cmp rdi,rbx; je → 0x665cf64 (COLD RANGE HEAD [V] — loop-exit path); else cmp byte [rdi+0x18],2; jne → loc_665cf1f (skip non-matching); rsi=[rdi+8]; test; je → loc_665cf1f; lock dec [rsi+8]; jne → loc_665cf1f; mov rax,[rsi]; mov rax,[rax]; mov rcx,rsi (dtor setup continues into phase 20). Three exits to cold-range head 0x665cf64 (at 0x665ceca, 0x665cf17, 0x665cf26 — all [V], exact rdis lines). All line/RVA claims [V]: exact rdis output; cold range itself not yet disassembled.


### Residual Phase 20 (final) — 0x665cf46..0x665cf64  [V]
; from rdis `dis 0x665cf46 16` (8 residual-tail instructions ending exactly at cold-range head 0x665cf64; lines at/after 0x665cf64 belong to cold range)
  665cf46  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cf4c  lock dec dword ptr [rsi+0xC]                  
  665cf50  jne short 0x665CF1F                           ; -> sub_665cf1f
  665cf52  mov rax,[rsi]                                 
  665cf55  mov rax,[rax+8]                               
  665cf59  mov rcx,rsi                                   
  665cf5c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cf62  jmp short 0x665CF1F                           ; -> sub_665cf1f

// Interpretation [V]: exact rdis lines above. Completes the scan-loop object release from phase 19 (dtor1 call [0xF99FFA0]=sub_eea6040 at 0x665cf46; lock dec [rsi+0xC]; jne → loc_665cf1f; dtor2 call at 0x665cf5c; jmp back to loc_665cf1f). All three scan-loop exits (je 0x665cf64 at 0x665ceca/0x665cf17/0x665cf26 in phase 19) funnel to 0x665cf64, which IS the cold-range head and a clean instruction boundary (mov rsi,[rbp+0x28]). Residual tail 0x665c276..0x665cf64 is now COMPLETE. Cold range 0x665cf64..0x665d7e5 begins next. All line/RVA claims [V]: exact rdis output; cold range itself not yet disassembled.


## PHASES — cold range 0x665cf64..0x665d7e5 (header: `sub_665cf64  [0x665cf64..0x665ef64)  size 0x2000  1 xrefs in`, seen via `rdis dis 0x665cf64 40`; end exclusive 0x665d7e5)

### Cold-Range Phase 1 — 0x665cf64..0x665d03d  [V]
; from rdis `dis 0x665cf64 40` (40 instructions; --max 40 cut at last shown instruction 0x665d036, 7 bytes → phase end 0x665d03d)
  665cf64  mov rsi,[rbp+0x28]                            
  665cf68  jmp 0x665D124                                 ; -> loc_665d124
  665cf6d  xor r11d,r11d                                 
  665cf70  mov rdi,[rbp+0x508]                           
  665cf77  mov [rbp+0x4A0],rdi                           
  665cf7e  mov [rbp+0x4A8],r11                           
  665cf85  mov [rbp+0x4B0],cl                            
  665cf8b  mov rcx,[rbp+0x530]                           
  665cf92  mov [rbp+0x4C8],rcx                           
  665cf99  movaps xmm0,[rbp+0x520]                       
  665cfa0  movups [rbp+0x4B8],xmm0                       
  665cfa7  mov ecx,0x9D0                                 
  665cfac  add rcx,[rsi+0x10]                            
  665cfb0  mov [rsp+0x28],rax                            
  665cfb5  mov [rsp+0x20],r10                            
  665cfba  call 0x67B40D0                                ; -> sub_67b40d0
  665cfbf  nop                                           
  665cfc0  lea rcx,[rbp+0x340]                           
  665cfc7  call 0x66A9AD0                                ; -> sub_66a9ad0
  665cfcc  jmp short 0x665D02D                           ; -> loc_665d02d
  665cfce  xor r11d,r11d                                 
  665cfd1  mov rdi,[rbp+0x508]                           
  665cfd8  mov [rbp+0x4A0],rdi                           
  665cfdf  mov [rbp+0x4A8],r11                           
  665cfe6  mov [rbp+0x4B0],cl                            
  665cfec  mov rcx,[rbp+0x530]                           
  665cff3  mov [rbp+0x4C8],rcx                           
  665cffa  movaps xmm0,[rbp+0x520]                       
  665d001  movups [rbp+0x4B8],xmm0                       
  665d008  mov ecx,0x9D0                                 
  665d00d  add rcx,[rsi+0x10]                            
  665d011  mov [rsp+0x28],rax                            
  665d016  mov [rsp+0x20],r10                            
  665d01b  call 0x67B47D0                                ; -> sub_67b47D0
  665d020  nop                                           
  665d021  lea rcx,[rbp+0x340]                           
  665d028  call 0x66A9AD0                                ; -> sub_66a9ad0

loc_665d02d:  ; from 665cfcc
  665d02d  cmp byte ptr [rbp+0x220],1                    
  665d034  jne short 0x665D076                           ; -> loc_665d076
  665d036  mov rcx,[rbp+0x1E0]                           

// Interpretation [V]: exact rdis lines above. Cold-range entry at 0x665cf64: mov rsi,[rbp+0x28]; jmp 0x665d124 (forward within cold range, [?] target). Fall-through frame-store block (mirrors residual phase 1 tail at 0x665c276): xor r11d,r11d; [rbp+0x4A0]=[rbp+0x508]; [rbp+0x4A8]=0; [rbp+0x4B0]=cl; [rbp+0x4C8]=[rbp+0x530]; movaps xmm0=[rbp+0x520]→[rbp+0x4B8]; rcx=0x9D0+[rsi+0x10]; spill rax/r10 to [rsp+0x28]/[rsp+0x20]; call sub_67b40d0; lea rcx=&[rbp+0x340]; call sub_66a9ad0; jmp → loc_665d02d. Second near-identical block calls sub_67b47D0 (DIFFERENT function) then same sub_66a9ad0, also jmp → loc_665d02d (suggests a two-variant path merged at loc_665d02d). loc_665d02d: cmp byte [rbp+0x220],1; jne → 0x665d076; rcx=[rbp+0x1E0] (continues next phase). All line/RVA claims [V]: exact rdis output; targets 0x665d124/0x665d02d/0x665d076 [V] as rdis line targets, contents [?] until next phases.


### Cold-Range Phase 2 — 0x665d03d..0x665d0df  [V]
; from rdis `dis 0x665d03d 40` (40 instructions; --max 40 cut at last shown instruction 0x665d0dc, 3 bytes → phase end 0x665d0df)
  665d03d  test rcx,rcx                                  
  665d040  je short 0x665D076                            ; -> loc_665d076
  665d042  mov rdx,[rbp+0x1F0]                           
  665d049  sub rdx,rcx                                   
  665d04c  cmp rdx,0x1000                                
  665d053  jb short 0x665D071                            ; -> loc_665d071
  665d055  mov rax,[rcx-8]                               ; R a0-0x8
  665d059  add rcx,0xFFFFFFFFFFFFFFF8                    
  665d05d  sub rcx,rax                                   
  665d060  cmp rcx,0x20                                  
  665d064  jae 0x665D43A                                 ; -> loc_665d43a
  665d06a  or rdx,0x27                                   
  665d06e  mov rcx,rax                                   

loc_665d071:  ; from 665d053
  665d071  call 0xE935700                                ; -> sub_e935700

loc_665d076:  ; from 665d040
  665d076  cmp byte ptr [rbp+0x538],1                    
  665d07d  jne 0x665D11D                                 ; -> loc_665d11d
  665d083  cmp byte ptr [rbp+0x518],3                    
  665d08a  jne short 0x665D0C3                           ; -> loc_665d0c3
  665d08c  mov rsi,[rbp+0x510]                           
  665d093  test rsi,rsi                                  
  665d096  je short 0x665D0C3                           ; -> loc_665d0c3
  665d098  lock dec dword ptr [rsi+8]                    
  665d09c  jne short 0x665D0C3                           ; -> loc_665d0c3
  665d09e  mov rax,[rsi]                                 
  665d0a1  mov rax,[rax]                                 
  665d0a4  mov rcx,rsi                                   
  665d0a7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665d0ad  lock dec dword ptr [rsi+0xC]                  
  665d0b1  jne short 0x665D0C3                           ; -> loc_665d0c3
  665d0b3  mov rax,[rsi]                                 
  665d0b6  mov rax,[rax+8]                               
  665d0ba  mov rcx,rsi                                   
  665d0bd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665d0c3:  ; from 665d08a, 665d096, 665d09c, 665d0b1
  665d0c3  mov rdi,[rbp+0x4E8]                           
  665d0ca  test rdi,rdi                                  
  665d0cd  je short 0x665D11D                            ; -> loc_665d11d
  665d0cf  mov rbx,[rbp+0x4F0]                           
  665d0d6  jmp short 0x665D0DC                           ; -> loc_665d0dc

loc_665d0d8:  ; from 665d0e5, 665d0ee, 665d0f4, 665d109, 665d11b
  665d0d8  add rdi,0x28                                  

loc_665d0dc:  ; from 665d0d6
  665d0dc  cmp rdi,rbx                                   

// Interpretation [V]: exact rdis lines above. Continues cold phase 1 at loc_665d02d: test rcx,rcx; je → loc_665d076; the familiar heap-tail idiom: rdx=[rbp+0x1F0]-rcx; if rdx<0x1000 → loc_665d071; rax=[rcx-8] ("R a0-0x8"); rcx-=0x8; rcx-=rax; if rcx>=0x20 → loc_665d43a (cold-tail target reached earlier in residual phases 10/14, [?]); or rdx,0x27; rcx=rax. loc_665d071: call sub_e935700 (merges into loc_665d076). loc_665d076: cmp byte [rbp+0x538],1; jne → 0x665d11d (cold-range region); cmp byte [rbp+0x518],3; jne → loc_665d0c3; else rsi=[rbp+0x510]; ref-counted release (test; lock dec [rsi+8]; jne skip loc_665d0c3; dtor1 [0xF99FFA0]=sub_eea6040; lock dec [rsi+0xC]; jne skip; dtor2) → loc_665d0c3. loc_665d0c3: scan loop rdi=[rbp+0x4E8]→rbx=[rbp+0x4F0]; test rdi,rdi; je → 0x665d11d; rbx=[rbp+0x4F0]; jmp loc_665d0dc. loc_665d0d8: add rdi,0x28 (loop back). loc_665d0dc: cmp rdi,rbx; je → 0x665d11d (continues next phase at 0x665d0df). All line/RVA claims [V]: exact rdis output; targets 0x665d11d/0x665d43a/loc_665d154 [V] as rdis line targets, contents [?] until next phases.


### Cold-Range Phase 3 — 0x665d0df..0x665d182  [V]
; from rdis `dis 0x665d0df 40` (40 instructions; --max 40 cut at last shown instruction 0x665d17a, 8 bytes → phase end 0x665d182)
  665d0df  je short 0x665D11D                            ; -> loc_665d11d
  665d0e1  cmp byte ptr [rdi+0x18],2                     
  665d0e5  jne short 0x665D0D8                           ; -> sub_665d0d8
  665d0e7  mov rsi,[rdi+8]                               
  665d0eb  test rsi,rsi                                  
  665d0ee  je short 0x665D0D8                            ; -> sub_665d0d8
  665d0f0  lock dec dword ptr [rsi+8]                    
  665d0f4  jne short 0x665D0D8                           ; -> sub_665d0d8
  665d0f6  mov rax,[rsi]                                 
  665d0f9  mov rax,[rax]                                 
  665d0fc  mov rcx,rsi                                   
  665d0ff  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665d105  lock dec dword ptr [rsi+0xC]                  
  665d109  jne short 0x665D0D8                           ; -> sub_665d0d8
  665d10b  mov rax,[rsi]                                 
  665d10e  mov rax,[rax+8]                               
  665d112  mov rcx,rsi                                   
  665d115  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665d11b  jmp short 0x665D0D8                           ; -> sub_665d0d8

loc_665d11d:  ; from 665d0df
  665d11d  mov rsi,[rbp+0x338]                           
  665d124  test rsi,rsi                                  
  665d127  je short 0x665D154                            ; -> loc_665d154
  665d129  lock dec dword ptr [rsi+8]                    
  665d12d  jne short 0x665D154                           ; -> loc_665d154
  665d12f  mov rax,[rsi]                                 
  665d132  mov rax,[rax]                                 
  665d135  mov rcx,rsi                                   
  665d138  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665d13e  lock dec dword ptr [rsi+0xC]                  
  665d142  jne short 0x665D154                           ; -> loc_665d154
  665d144  mov rax,[rsi]                                 
  665d147  mov rax,[rax+8]                               
  665d14b  mov rcx,rsi                                   
  665d14e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665d154:  ; from 665d127, 665d12d, 665d142
  665d154  movaps xmm6,[rbp+0x550]                       
  665d15b  movaps xmm7,[rbp+0x560]                       
  665d162  movaps xmm8,[rbp+0x570]                       
  665d16a  movaps xmm9,[rbp+0x580]                       
  665d172  movaps xmm10,[rbp+0x590]                      
  665d17a  movaps xmm11,[rbp+0x5A0]                      

// Interpretation [V]: exact rdis lines above. Completes cold phase 2's scan loop: cmp rdi,rbx (0x665d0dc); je → 0x665d11d (loop exit); else cmp byte [rdi+0x18],2; jne → loc_665d0d8 (skip non-matching); rsi=[rdi+8]; test; je → loc_665d0d8; lock dec [rsi+8]; jne → loc_665d0d8; dtor1 [0xF99FFA0]=sub_eea6040; lock dec [rsi+0xC]; jne → loc_665d0d8; dtor2 [0xF99FFA0]; jmp → loc_665d0d8 (loop back via add rdi,0x28). loc_665d11d: rsi=[rbp+0x338]; test; je → loc_665d154; ref-counted release over [rbp+0x338] (same pattern) → loc_665d154. loc_665d154: movaps xmm6=[rbp+0x550] … xmm11=[rbp+0x5A0] (saves six XMM registers — mirrored by the xmm12-load/epilogue at 0x665d182). Loop targets loc_665d0d8 (from 665d0e5/665d0ee/665d0f4/665d109/665d11b). All line/RVA claims [V]: exact rdis output; targets 0x665d11d/loc_665d0d8/loc_665d154 [V] as targets, contents [?] until next phases.


### Cold-Range Phase 4 — 0x665d182..0x665d231  [V]
; from rdis `dis 0x665d182 40` (40 instructions; --max 40 cut at last shown instruction 0x665d230, 1 byte → phase end 0x665d231)
  665d182  movaps xmm12,[rbp+0x5B0]                      
  665d18a  add rsp,0x648                                 
  665d191  pop rbx                                       
  665d192  pop rdi                                       
  665d193  pop rsi                                       
  665d194  pop r12                                       
  665d196  pop r13                                       
  665d198  pop r14                                       
  665d19a  pop r15                                       
  665d19c  pop rbp                                       
  665d19d  ret                                           
  665d19e  mov ecx,0x20                                  
  665d1a3  call 0x9BC830                                 ; -> sub_9bc830
  665d1a8  jmp 0x66564FF                                 ; -> sub_66564ff
  665d1ad  lea rcx,[rdi+0x27]                            
  665d1b1  call 0x9BC830                                 ; -> sub_9bc830
  665d1b6  nop                                           
  665d1b7  jmp 0x6657223                                 ; -> sub_6657223
  665d1bc  lea rcx,[r13+0x27]                            
  665d1c0  call 0x9BC830                                 ; -> sub_9bc830
  665d1c5  nop                                           
  665d1c6  jmp 0x66572E2                                 ; -> sub_66572e2
  665d1cb  mov rcx,[rbp+0x48]                            
  665d1cf  call 0x9BC830                                 ; -> sub_9bc830
  665d1d4  nop                                           
  665d1d5  jmp 0x66573AF                                 ; -> sub_66573af
  665d1da  lea rcx,[0x129F9C50]                          ; [data_129f9c50]
  665d1e1  call 0xE938CB0                                ; -> sub_e938cb0
  665d1e6  cmp dword ptr [0x129F9C50],0xFFFFFFFF         ; [data_129f9c50]
  665d1ed  jne 0x66561F1                                 ; -> sub_66561f1
  665d1f3  xorps xmm0,xmm0                               
  665d1f6  movaps [rbp+0x120],xmm0                       
  665d1fd  lea rax,[0xF57DBCE]                           ; [data_f57dbce] "LegacyCubemap"
  665d204  mov [rbp+0x1D0],rax                           
  665d20b  mov qword ptr [rbp+0x1D8],0xD                 
  665d216  lea rcx,[0x129F9C40]                          ; [data_129f9c40]
  665d21d  lea rdx,[rbp+0x1D0]                           
  665d224  lea r8,[rbp+0x120]                            
  665d22b  call 0x5668AC0                                ; -> sub_5668ac0
  665d230  nop                                           

// Interpretation [V]: exact rdis lines above. Completes cold phase 3's xmm-save block: movaps xmm12=[rbp+0x5B0]; add rsp,0x648; pop rbx/rdi/rsi/r12/r13/r14/r15/rbp; ret — function epilogue at 0x665d182–0x665d19d, i.e. END of the cold-range function entered at 0x665cf64. Then cold-range allocator/error paths: mov ecx,0x20; call sub_9bc830 (fallback allocator seen earlier); jmp 0x66564FF (OUTSIDE cold range, main function body [?]); three more sub_9bc830 calls with size args ([rdi+0x27]/[r13+0x27]/[rbp+0x48]) each followed by jmp to sub_6657223/sub_66572e2/sub_66573AF (all outside cold range [?]). Then lea rcx=[0x129F9C50]; call sub_e938cb0; cmp dword [0x129F9C50],0xFFFFFFFF; jne → 0x66561F1 (outside [?]); xorps xmm0; [rbp+0x120]=0; lea rax=[0xF57DBCE] ("LegacyCubemap" string [data_f57dbce]); [rbp+0x1D0]=rax; [rbp+0x1D8]=0xD (string len); lea rcx=[0x129F9C40]; lea rdx=&[rbp+0x1D0]; lea r8=&[rbp+0x120]; call sub_5668ac0; nop (continues next phase). All line/RVA claims [V]: exact rdis output; jmp targets outside cold range [V] as targets, contents [?].


### Cold-Range Phase 5 — 0x665d231..0x665d32a  [V]
; from rdis `dis 0x665d231 40` (40 instructions; --max 40 cut at last shown instruction 0x665d31f, 11 bytes → phase end 0x665d32a)
  665d231  lea rcx,[0x129F9C50]                          ; [data_129f9c50]
  665d238  call 0xE938D70                                ; -> sub_e938d70
  665d23d  jmp 0x66561F1                                 ; -> sub_66561f1
  665d242  lea rcx,[0x129F9C68]                          ; [data_129f9c68]
  665d249  call 0xE938CB0                                ; -> sub_e938cb0
  665d24e  cmp dword ptr [0x129F9C68],0xFFFFFFFF         ; [data_129f9c68]
  665d255  jne 0x6656216                                 ; -> sub_6656216
  665d25b  xorps xmm0,xmm0                               
  665d25e  movaps [rbp+0x310],xmm0                       
  665d265  lea rax,[0xF7CA1F7]                           ; [data_f7ca1f7] "LegacyCubemapForwardPBR"
  665d26c  mov [rbp+0x320],rax                           
  665d273  mov qword ptr [rbp+0x328],0x17                
  665d27e  lea rcx,[0x129F9C58]                          ; [data_129f9c58]
  665d285  lea rdx,[rbp+0x320]                           
  665d28c  lea r8,[rbp+0x310]                            
  665d293  call 0x5668AC0                                ; -> sub_5668ac0
  665d298  nop                                           
  665d299  lea rcx,[0x129F9C68]                          ; [data_129f9c68]
  665d2a0  call 0xE938D70                                ; -> sub_e938d70
  665d2a5  jmp 0x6656216                                 ; -> sub_6656216
  665d2aa  lea rcx,[0x129F9D00]                          ; [data_129f9d00]
  665d2b1  call 0xE938CB0                                ; -> sub_e938cb0
  665d2b6  cmp dword ptr [0x129F9D00],0xFFFFFFFF         ; [data_129f9d00]
  665d2bd  jne 0x6656C32                                 ; -> sub_6656c32
  665d2c3  xorps xmm0,xmm0                               
  665d2c6  movaps [rbp+0x1D0],xmm0                       
  665d2cd  mov rax,[rbp+0x130]                           
  665d2d4  cmp qword ptr [rbp+0x138],0x10                
  665d2dc  jb 0x665DAD4                                 ; -> loc_665dad4
  665d2e2  mov rcx,[rbp+0x120]                           
  665d2e9  jmp 0x665DADB                                 ; -> loc_665dadb
  665d2ee  lea rcx,[0x129F9F28]                          ; [data_129f9f28]
  665d2f5  call 0xE938CB0                                ; -> sub_e938cb0
  665d2fa  cmp dword ptr [0x129F9F28],0xFFFFFFFF         ; [data_129f9f28]
  665d301  jne 0x6656713                                 ; -> sub_6656713
  665d307  xorps xmm0,xmm0                               
  665d30a  movaps [rbp+0x1D0],xmm0                       
  665d311  lea rax,[0xF51B964]                           ; [data_f51b964]
  665d318  mov [rbp+0x310],rax                           
  665d31f  mov qword ptr [rbp+0x318],3                   

// Interpretation [V]: exact rdis lines above. Continues cold phase 4's legacy-cubemap resource pattern: repeated lea rcx=[data_*]; call sub_e938cb0/sub_e938d70; cmp dword [data_*],0xFFFFFFFF; jne → outside cold range (0x66561F1/0x6656216/0x6656C32/0x6656713 — all [V] targets, contents [?]). On success: xorps xmm0; zero a frame slot; lea rax=[data_* string] ("LegacyCubemapForwardPBR" [data_f7ca1f7] at 0x665d265, string at [data_f51b964] at 0x665d311); store pointer+length ([rbp+0x320]/0x328=0x17; [rbp+0x1D0]/0x318=3); lea rcx=[data_*]; lea rdx=&slot; lea r8=&zero-slot; call sub_5668ac0 (resource loader); nop. Also: mov rax,[rbp+0x130]; cmp qword [rbp+0x138],0x10; jb → 0x665DAD4 (BEYOND cold-range end 0x665d7e5, [?]); jmp → 0x665DADB (also beyond end, [?]) — cold-range control exits the defined range here. All line/RVA claims [V]: exact rdis output; targets outside cold range [V] as targets, contents [?].


### Cold-Range Phase 6 — 0x665d32a..0x665d41c  [V]
; from rdis `dis 0x665d32a 40` (40 instructions; --max 40 cut at last shown instruction 0x665d415, 7 bytes → phase end 0x665d41c)
  665d32a  lea rcx,[0x129F9F18]                          ; [data_129f9f18]
  665d331  lea rdx,[rbp+0x310]                           
  665d338  lea r8,[rbp+0x1D0]                            
  665d33f  call 0x5668AC0                                ; -> sub_5668ac0
  665d344  nop                                           
  665d345  lea rcx,[0x129F9F28]                          ; [data_129f9f28]
  665d34c  call 0xE938D70                                ; -> sub_e938d70
  665d351  jmp 0x6656713                                 ; -> sub_6656713
  665d356  lea rcx,[0x129F9F60]                          ; [data_129f9f60]
  665d35d  call 0xE938CB0                                ; -> sub_e938cb0
  665d362  cmp dword ptr [0x129F9F60],0xFFFFFFFF         ; [data_129f9f60]
  665d369  jne 0x6656837                                 ; -> sub_6656837
  665d36f  xorps xmm0,xmm0                               
  665d372  movaps [rbp+0x170],xmm0                       
  665d379  lea rax,[0xF54C3E1]                           ; [data_f54c3e1] "Stars"
  665d380  mov [rbp+0x120],rax                           
  665d387  mov qword ptr [rbp+0x128],5                   
  665d392  lea rcx,[0x129F9F50]                          ; [data_129f9f50]
  665d399  lea rdx,[rbp+0x120]                           
  665d3a0  lea r8,[rbp+0x170]                            
  665d3a7  call 0x5668AC0                                ; -> sub_5668ac0
  665d3ac  nop                                           
  665d3ad  lea rcx,[0x129F9F60]                          ; [data_129f9f60]
  665d3b4  call 0xE938D70                                ; -> sub_e938d70
  665d3b9  jmp 0x6656837                                 ; -> sub_6656837
  665d3be  lea rcx,[0x129F9F78]                          ; [data_129f9f78]
  665d3c5  call 0xE938CB0                                ; -> sub_e938cb0
  665d3ca  cmp dword ptr [0x129F9F78],0xFFFFFFFF         ; [data_129f9f78]
  665d3d1  jne 0x665685C                                 ; -> sub_665685c
  665d3d7  xorps xmm0,xmm0                               
  665d3da  movaps [rbp+0x1D0],xmm0                       
  665d3e1  lea rax,[0xF7CA19E]                           ; [data_f7ca19e] "StarsForwardPBR"
  665d3e8  mov [rbp+0x310],rax                           
  665d3ef  mov qword ptr [rbp+0x318],0xF                 
  665d3fa  lea rcx,[0x129F9F68]                          ; [data_129f9f68]
  665d401  lea rdx,[rbp+0x310]                           
  665d408  lea r8,[rbp+0x1D0]                            
  665d40f  call 0x5668AC0                                ; -> sub_5668ac0
  665d414  nop                                           
  665d415  lea rcx,[0x129F9F78]                          ; [data_129f9f78]

// Interpretation [V]: exact rdis lines above. Continues cold phase 5's legacy-cubemap resource pattern: call sub_5668ac0 (data_129f9f18 path); lea/call sub_e938d70 (data_129f9f28); jmp 0x6656713 (outside cold range [?]); then lea/call sub_e938cb0 (data_129f9f60); cmp dword [data_129f9f60],0xFFFFFFFF; jne → 0x6656837 (outside [?]); success path: xorps xmm0; [rbp+0x170]=0; lea rax=[data_f54c3e1] "Stars"; [rbp+0x120]=rax; [rbp+0x128]=5; lea rcx=[data_129f9f50]; lea rdx=&[rbp+0x120]; lea r8=&[rbp+0x170]; call sub_5668ac0; nop; lea/call sub_e938d70 (data_129f9f60); jmp 0x6656837 (outside [?]); lea/call sub_e938cb0 (data_129f9f78); cmp dword [data_129f9f78],0xFFFFFFFF; jne → 0x665685C (outside [?]); success: xorps xmm0; [rbp+0x1D0]=0; lea rax=[data_f7ca19e] "StarsForwardPBR"; [rbp+0x310]=rax; [rbp+0x318]=0xF; lea rcx=[data_129f9f68]; lea rdx=&[rbp+0x310]; lea r8=&[rbp+0x1D0]; call sub_5668ac0; nop; lea rcx=[data_129f9f78] (continues next phase). All line/RVA claims [V]: exact rdis output; jmp targets outside cold range [V] as targets, contents [?].


### Cold-Range Phase 7 — 0x665d41c..0x665d4ec  [V]
; from rdis `dis 0x665d41c 40` (40 instructions; --max 40 cut at last shown instruction 0x665d4e5, 7 bytes → phase end 0x665d4ec)
  665d41c  call 0xE938D70                                ; -> sub_e938d70
  665d421  jmp 0x665685C                                 ; -> sub_665685c
  665d426  call 0x1166E0                                 ; -> sub_1166e0
  665d42b  nop                                           
  665d42c  mov rcx,r15                                   
  665d42f  call 0x9BC830                                 ; -> sub_9bc830
  665d434  nop                                           
  665d435  jmp 0x665C83D                                 ; -> sub_665c83d
  665d43a  mov qword ptr [rsp+0x20],0                    
  665d443  xor ecx,ecx                                   
  665d445  xor edx,edx                                   
  665d447  xor r8d,r8d                                   
  665d44a  xor r9d,r9d                                   
  665d44d  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  665d453  lea rcx,[0x129C13C0]                          ; [data_129c13c0]
  665d45a  call 0xE938CB0                                ; -> sub_e938cb0
  665d45f  cmp dword ptr [0x129C13C0],0xFFFFFFFF         ; [data_129c13c0]
  665d466  jne 0x6656306                                 ; -> sub_6656306
  665d46c  lea rcx,[0x4E05030]                           ; [sub_4e05030]
  665d473  call 0xE935740                                ; -> sub_e935740
  665d478  lea rcx,[0x129C13C0]                          ; [data_129c13c0]
  665d47f  call 0xE938D70                                ; -> sub_e938d70
  665d484  jmp 0x6656306                                 ; -> sub_6656306
  665d489  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  665d490  call 0xE938CB0                                ; -> sub_e938cb0
  665d495  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
  665d49c  jne 0x6656B6F                                 ; -> sub_6656b6f
  665d4a2  lea rcx,[0x129CA568]                          ; [data_129ca568]
  665d4a9  call 0x567DB00                                ; -> sub_567db00
  665d4ae  nop                                           
  665d4af  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
  665d4b6  call 0xE935740                                ; -> sub_e935740
  665d4bb  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  665d4c2  call 0xE938D70                                ; -> sub_e938d70
  665d4c7  jmp 0x6656B6F                                 ; -> sub_6656b6f
  665d4cc  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  665d4d3  call 0xE938CB0                                ; -> sub_e938cb0
  665d4d8  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
  665d4df  jne 0x66567A1                                 ; -> sub_66567a1
  665d4e5  lea rcx,[0x129CA568]                          ; [data_129ca568]

// Interpretation [V]: exact rdis lines above. Completes cold phase 6's data_129f9f78 path: call sub_e938d70 (data_129f9f78); jmp 0x665685C (outside cold range [?]). Then: call 0x1166E0 (sub_1166e0); nop; mov rcx,r15; call sub_9bc830 (fallback allocator); nop; jmp 0x665C83D — jumps BACK into residual-tail region (0x665c83d, residual phase 8's allocator continuation, [V] as target, content [?]). Then cold-tail entry 0x665d43a (target of residual phases 10/14's jae): mov qword ptr [rsp+0x20],0; xor ecx/edx/r8d/r9d; call qword ptr [0xF9A8C78] (DIFFERENT global [data_f9a8c78]); then repeated lea/call sub_e938cb0 (data_129C13C0, data_129CA5E0); cmp dword [data_*],0xFFFFFFFF; jne → outside cold range (0x6656306/0x6656B6F/0x66567A1 — all [V] targets, contents [?]); success: lea rcx=[sub_4e05030]/[sub_567dba0]/[data_129CA568]; call sub_e935740/sub_567DB00; lea/call sub_e938d70; jmp outside. All line/RVA claims [V]: exact rdis output; the jmp 0x665C83D back to residual tail [V] as target; contents [?]. Cold range nears end 0x665d7e5 (~0x2F9 bytes remain).


### Cold-Range Phase 8 — 0x665d4ec..0x665d5d1  [V]
; from rdis `dis 0x665d4ec 40` (40 instructions; --max 40 cut at last shown instruction 0x665d5c6, 11 bytes → phase end 0x665d5d1)
  665d4ec  call 0x567DB00                                ; -> sub_567db00
  665d4f1  nop                                           
  665d4f2  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
  665d4f9  call 0xE935740                                ; -> sub_e935740
  665d4fe  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  665d505  call 0xE938D70                                ; -> sub_e938d70
  665d50a  jmp 0x66567A1                                 ; -> sub_66567a1
  665d50f  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  665d516  call 0xE938CB0                                ; -> sub_e938cb0
  665d51b  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
  665d522  jne 0x665690F                                 ; -> sub_665690f
  665d528  lea rcx,[0x129CA568]                          ; [data_129ca568]
  665d52f  call 0x567DB00                                ; -> sub_567db00
  665d534  nop                                           
  665d535  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
  665d53c  call 0xE935740                                ; -> sub_e935740
  665d541  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  665d548  call 0xE938D70                                ; -> sub_e938d70
  665d54d  jmp 0x665690F                                 ; -> sub_665690f
  665d552  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  665d559  call 0xE938CB0                                ; -> sub_e938cb0
  665d55e  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
  665d565  jne 0x6656CD7                                 ; -> sub_6656cd7
  665d56b  lea rcx,[0x129CA568]                          ; [data_129ca568]
  665d572  call 0x567DB00                                ; -> sub_567db00
  665d577  nop                                           
  665d578  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
  665d57f  call 0xE935740                                ; -> sub_e935740
  665d584  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  665d58b  call 0xE938D70                                ; -> sub_e938d70
  665d590  jmp 0x6656CD7                                 ; -> sub_6656cd7
  665d595  lea rcx,[0x129F9FA0]                          ; [data_129f9fa0]
  665d59c  call 0xE938CB0                                ; -> sub_e938cb0
  665d5a1  cmp dword ptr [0x129F9FA0],0xFFFFFFFF         ; [data_129f9fa0]
  665d5a8  jne 0x6656554                                 ; -> sub_6656554
  665d5ae  xorps xmm0,xmm0                               
  665d5b1  movaps [rbp+0x1D0],xmm0                       
  665d5b8  lea rax,[0xF584D1D]                           ; [data_f584d1d] "SunMoon"
  665d5bf  mov [rbp+0x310],rax                           
  665d5c6  mov qword ptr [rbp+0x318],7                   

// Interpretation [V]: exact rdis lines above. Completes cold phase 7's data_129CA568 path: call sub_567db00; nop; lea rcx=[sub_567dba0]; call sub_e935740; lea/call sub_e938d70 (data_129CA5E0); jmp 0x66567A1 (outside cold range [?]). Then repeated lea/call sub_e938cb0 (data_129CA5E0); cmp dword [data_129CA5E0],0xFFFFFFFF; jne → outside (0x665690F/0x6656CD7/0x6656554 — all [V] targets, contents [?]); success: lea rcx=[data_129CA568]; call sub_567db00; nop; lea rcx=[sub_567dba0]; call sub_e935740; lea/call sub_e938d70; jmp outside. Finally lea rcx=[data_129F9FA0]; call sub_e938cb0; cmp dword [data_129F9FA0],0xFFFFFFFF; jne → 0x6656554 (outside [?]); success: xorps xmm0; [rbp+0x1D0]=0; lea rax=[data_f584d1d] "SunMoon"; [rbp+0x310]=rax; [rbp+0x318]=7 (continues next phase). All line/RVA claims [V]: exact rdis output; jmp targets outside cold range [V] as targets, contents [?]. Cold range ~0x214 bytes remain to 0x665d7e5.











