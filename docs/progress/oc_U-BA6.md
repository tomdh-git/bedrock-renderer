# Unit U-BA6 — bodyActor function 0x66d0a00 (1.26.62.01), continued from 0x66d4f8d

## NEXT [current]
Resume at RVA 0x66d5904 (RVA of instruction 41 of `dis 0x66d583c 41`: `66d5904 call 0x67D1120` — taken directly from rdis output).
Next call:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d5904 41`
Scope: 12 consecutive phases of 40 instructions each (480 instructions) from 0x66d4f8d; phases 1-12 DONE (0x66d4f8d..0x66d5900, last RVA 0x66d5900; phase-12 I41 at 0x66d5904). Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game is closed.

## Phase 1 — 0x66d4f8d, 40 instructions [V]
```
0x66d4f8d  cmp byte ptr [rbp+0xA4C],0                     
0x66d4f94  je short 0x66D4FB7                             ; -> loc_66d4fb7            
0x66d4f96  movdqu [rbp+0xA3C],xmm0                       
0x66d4f9e  jmp short 0x66D4FC6                           ; -> loc_66d4fc6            
0x66d4fa0  movdqu [rbp+0xA20],xmm2                       
0x66d4fa8  movq [rbp+0xA30],xmm1                         
0x66d4fb0  mov byte ptr [rbp+0xA38],0                    
0x66d4fb7  movdqu [rbp+0xA3C],xmm0                       
0x66d4fbf  mov byte ptr [rbp+0xA4C],1                    
0x66d4fc6  cmp byte ptr [rbp+0x4A8],3                    
0x66d4fcd  jne short 0x66D5006                           ; -> loc_66d5006            
0x66d4fcf  mov rbx,[rbp+0x4A0]                           
0x66d4fd6  test rbx,rbx                                  
0x66d4fd9  je short 0x66D5006                            ; -> loc_66d5006            
0x66d4fdb  lock dec dword ptr [rbx+8]                    
0x66d4fdf  jne short 0x66D5006                           ; -> loc_66d5006            
0x66d4fe1  mov rax,[rbx]                                 
0x66d4fe4  mov rax,[rax]                                 
0x66d4fe7  mov rcx,rbx                                   
0x66d4fea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d4ff0  lock dec dword ptr [rbx+0xC]                  
0x66d4ff4  jne short 0x66D5006                           ; -> loc_66d5006            
0x66d4ff6  mov rax,[rbx]                                 
0x66d4ff9  mov rax,[rax+8]                               
0x66d4ffd  mov rcx,rbx                                   
0x66d5000  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5006  mov r12,[rbp+0x478]                           
0x66d500d  test r12,r12                                  
0x66d5010  je short 0x66D5063                            ; -> loc_66d5063            
0x66d5012  mov r15,[rbp+0x480]                           
0x66d5019  jmp short 0x66D501F                           ; -> loc_66d501f            
0x66d501b  add r12,0x28                                  
0x66d501f  cmp r12,r15                                   
0x66d5022  je short 0x66D5063                            ; -> loc_66d5063            
0x66d5024  cmp byte ptr [r12+0x18],2                     
0x66d502a  jne short 0x66D501B                           ; -> loc_66d501b            
0x66d502c  mov rbx,[r12+8]                               
0x66d5031  test rbx,rbx                                  
0x66d5034  je short 0x66D501B                            ; -> loc_66d501b            
0x66d5036  lock dec dword ptr [rbx+8]                    
0x66d503a  jne short 0x66D501B                           ; -> loc_66d501B            
```
// [V] Phase 1 resumes at verified boundary 0x66d4f8d (oc_U-BA5.md phases from 0x66d4f8d are JUNK — ignored; this phase re-derives the same code from rdis): cmp byte [rbp+0xA4C],0; je short 0x66d4fb7 — if the one-time flag [rbp+0xA4C] is already set, jump straight to 0x66d4fb7 [V]. Fallthrough: movdqu [rbp+0xA3C],xmm0; jmp short 0x66d4fc6 [V]. loc_66d4fb7: movdqu [rbp+0xA3C],xmm0; mov byte [rbp+0xA4C],1 (set flag once) [V]. loc_66d4fc6: cmp byte [rbp+0x4A8],3; jne short 0x66d5006 — type tag 3 enters cleanup [V]. Cleanup: rbx=[rbp+0x4A0]; test rbx,rbx; je 0x66d5006; lock dec dword [rbx+8]; jne 0x66d5006; else rax=[rbx]; rax=[rax] vtable[0]; rcx=rbx; call qword ptr [0xF99FFA0] ([data_f99ffa0]=sub_eea6040) dtor [I]; lock dec dword [rbx+0xC]; jne 0x66d5006; else rax=[rbx]; rax=[rax+8]; rcx=rbx; call qword ptr [0xF99FFA0] free [I] — dtor+free double call on [rbp+0x4A0], same sub_eea6040 pattern as U-BA5 phases 14-18 [V, cited there]. loc_66d5006: node-release loop over list head r12=[rbp+0x478], sentinel r15=[rbp+0x480]: test r12,r12; je 0x66d5063 empty; jmp 0x66d501f [V]. loc_66d501b: add r12,0x28 (0x28-stride nodes) [V]. loc_66d501f: cmp r12,r15; je 0x66d5063 done; cmp byte [r12+0x18],2; jne 0x66d501b skip non-type-2 nodes [V]; rbx=[r12+8] node value; test rbx,rbx; je 0x66d501b skip null; lock dec dword [rbx+8]; jne 0x66d501b refcount nonzero → skip [V] — dtor+free tail continues at next phase (0x66d503c `mov rax,[rbx]` per rdis `dis 0x66d503a 2`) [V]. rdis halted its linear walk at the backward jne 0x66d503a→0x66d501b loop, so instruction 41's RVA (0x66d503c) comes from that peek output, not hand computation [V]. Next address: 0x66d503c.

## Phase 2 — 0x66d503c, 40 instructions [V]
```
0x66d503c  mov rax,[rbx]                                 
0x66d503f  mov rax,[rax]                                 
0x66d5042  mov rcx,rbx                                   
0x66d5045  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d504b  lock dec dword ptr [rbx+0xC]                  
0x66d504f  jne short 0x66D501B                           ; -> sub_66d501b
0x66d5051  mov rax,[rbx]                                 
0x66d5054  mov rax,[rax+8]                               
0x66d5058  mov rcx,rbx                                   
0x66d505b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d5061  jmp short 0x66D501B                           ; -> sub_66d501b
0x66d5063  mov rcx,[rbp+0xD80]                           
0x66d506a  mov rax,[rcx+8]                               
0x66d506e  test rax,rax                                  
0x66d5071  je short 0x66D50B7                            ; -> loc_66d50b7
0x66d5073  lock inc dword ptr [rax+8]                    
0x66d5077  mov r12,[rcx]                                 
0x66d507a  mov rbx,[rcx+8]                               
0x66d507e  test rbx,rbx                                  
0x66d5081  mov r15,[rbp+0xD90]                           
0x66d5088  je short 0x66D50C1                            ; -> loc_66d50c1
0x66d508a  lock dec dword ptr [rbx+8]                    
0x66d508e  jne short 0x66D50C1                           ; -> loc_66d50c1
0x66d5090  mov rax,[rbx]                                 
0x66d5093  mov rax,[rax]                                 
0x66d5096  mov rcx,rbx                                   
0x66d5099  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d509f  lock dec dword ptr [rbx+0xC]                  
0x66d50a3  jne short 0x66D50C1                           ; -> loc_66d50c1
0x66d50a5  mov rax,[rbx]                                 
0x66d50a8  mov rax,[rax+8]                               
0x66d50ac  mov rcx,rbx                                   
0x66d50af  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66d50b5  jmp short 0x66D50C1                           ; -> loc_66d50c1
0x66d50b7  mov r12,[rcx]                                 
0x66d50ba  mov r15,[rbp+0xD90]                           
0x66d50c1  test r12,r12                                  
0x66d50c4  setne cl                                      
0x66d50c7  mov rax,[rdi]                                 
0x66d50ca  cmp byte ptr [rax+0x150],1                    
```
// [V] Phase 2 completes the per-node dtor+free tail from phase 1: rax=[rbx]; rax=[rax] vtable[0]; rcx=rbx; call qword ptr [0xF99FFA0] (sub_eea6040) destroy [I]; lock dec dword [rbx+0xC]; jne short 0x66d501b (loop back); else rax=[rbx]; rax=[rax+8]; rcx=rbx; call qword ptr [0xF99FFA0] free [I]; jmp short 0x66d501b loop — releases each type-2 node's value and loops back to 0x66d501b [V]. Then: rcx=[rbp+0xD80]; rax=[rcx+8]; test rax,rax; je short 0x66d50b7 null case [V]; lock inc dword [rax+8] refcount [V]; r12=[rcx] (node); rbx=[rcx+8] (value); r15=[rbp+0xD90] sentinel [V]; test rbx,rbx; je 0x66d50c1; lock dec dword [rbx+8] (release the inc'd value); jne 0x66d50c1; else rax=[rbx]; rax=[rax] vtable[0]; rcx=rbx; call qword ptr [0xF99FFA0] destroy [I]; lock dec dword [rbx+0xC]; jne 0x66d50c1; else rax=[rbx]; rax=[rax+8]; rcx=rbx; call qword ptr [0xF99FFA0] free [I]; jmp 0x66d50c1 [V] — release old value [rcx+8] after inc (net refcount adjust with free-on-zero) [I]. loc_66d50b7 (null case): r12=[rcx]; r15=[rbp+0xD90] [V]. loc_66d50c1: test r12,r12; setne cl (boolean = r12!=0) [V]; rax=[rdi]; cmp byte [rax+0x150],1; jne short 0x66d5151 — continues phase 3 [V]. Fields touched: [rbp+0xD80] (ptr to node/value pair, R at 0x66d5063), [rbp+0xD90] (list sentinel end, R at 0x66d5081/0x66d50ba), [rax+8] and [rbx+0xC] refcounts (R/W at 0x66d5073/0x66d508a/0x66d509f) [V]. Callee qword ptr [0xF99FFA0]=sub_eea6040 [V], destroy/free roles [I]. Next address: 0x66d50d1.

## Phase 3 — 0x66d50d1, 40 instructions [V]
```
0x66d50d1  jne short 0x66D5151                           ; -> loc_66d5151
0x66d50d3  mov rax,[rbp+0xCE0]                           
0x66d50da  mov [rbp+0xA50],rax                           
0x66d50e1  lea rbx,[rbp+0xA58]                           
0x66d50e8  mov rcx,rbx                                   
0x66d50eb  lea rdx,[rbp+0xCE8]                           
0x66d50f2  call 0xE869FF0                                ; -> sub_e869ff0
0x66d50f7  nop                                           
0x66d50f8  mov rax,[rbp+0xD60]                           
0x66d50ff  mov [rbp+0xAD0],rax                           
0x66d5106  mov qword ptr [rbp+0xD60],0                   
0x66d5111  movzx eax,byte ptr [rbp+0xA18]                
0x66d5118  mov rcx,[rbp+0xA50]                           
0x66d511f  mov [rbp+0x990],rcx                           
0x66d5126  lea rcx,[rbp+0x998]                           
0x66d512d  cmp al,1                                      
0x66d512f  jne 0x66D51D1                                 ; -> loc_66d51d1
0x66d5135  mov rdx,rbx                                   
0x66d5138  call 0xE86A0D0                                ; -> sub_e86a0d0
0x66d513d  nop                                           
0x66d513e  mov rax,[rbp+0xAD0]                           
0x66d5145  mov [rbp+0xA10],rax                           
0x66d514c  jmp 0x66D51EF                                 ; -> loc_66d51ef
0x66d5151  mov esi,ecx                                   
0x66d5153  mov rax,[rbp+0xCE0]                           
0x66d515a  mov [rbp+0xA50],rax                           
0x66d5161  lea rbx,[rbp+0xA58]                           
0x66d5168  mov rcx,rbx                                   
0x66d516b  lea rdx,[rbp+0xCE8]                           
0x66d5172  call 0xE869FF0                                ; -> sub_e869ff0
0x66d5177  nop                                           
0x66d5178  mov rax,[rbp+0xD60]                           
0x66d517f  mov [rbp+0xAD0],rax                           
0x66d5186  mov qword ptr [rbp+0xD60],0                   
0x66d5191  movzx eax,byte ptr [rbp+0xA18]                
0x66d5198  mov rcx,[rbp+0xA50]                           
0x66d519f  mov [rbp+0x990],rcx                           
0x66d51a6  lea rcx,[rbp+0x998]                           
0x66d51ad  cmp al,1                                      
0x66d51af  jne 0x66D5273                                 ; -> loc_66d5273
```
// [V] Phase 3 is the [rax+0x150]==1 fallthrough from phase 2's `cmp byte [rax+0x150],1; jne 0x66d5151`: jne short 0x66d5151 [V]. Fallthrough: rax=[rbp+0xCE0]; [rbp+0xA50]=rax [V]; lea rbx,&rbp+0xA58; rcx=rbx; lea rdx,&rbp+0xCE8; call 0xE869FF0(rcx=&rbp+0xA58, rdx=&rbp+0xCE8) [V] — new callee sub_e869ff0 [V], args/signature [?]; nop [V]; rax=[rbp+0xD60]; [rbp+0xAD0]=rax; mov qword [rbp+0xD60],0 (pointer steal — take field value, null the field) [V]; movzx eax,byte [rbp+0xA18]; rcx=[rbp+0xA50]; [rbp+0x990]=rcx [V]; lea rcx,&rbp+0x998; cmp al,1; jne 0x66d51d1 (byte [rbp+0xA18] switch: case 1 falls through) [V]; rdx=rbx; call 0xE86A0D0(rdx=&rbp+0xA58) [V] — new callee sub_e86a0d0 [V], args/signature [?]; nop; rax=[rbp+0xAD0]; [rbp+0xA10]=rax; jmp 0x66d51ef common join [V]. loc_66d5151 (!=1 path): mov esi,ecx (carries bool cl set at 0x66d50c4) [V]; then identical sequence: rax=[rbp+0xCE0]; [rbp+0xA50]=rax; lea rbx,&rbp+0xA58; call 0xE869FF0(rcx=&rbp+0xA58, rdx=&rbp+0xCE8) [V]; nop; rax=[rbp+0xD60]; [rbp+0xAD0]=rax; [rbp+0xD60]=0 [V]; movzx eax,byte [rbp+0xA18]; rcx=[rbp+0xA50]; [rbp+0x990]=rcx; lea rcx,&rbp+0x998; cmp al,1; jne 0x66d5273 (default/different case target) [V]; rdx=rbx — continues phase 4 (call 0xE86A0D0 expected at 0x66d51b8, not yet decoded) [?]. Fields touched: [rbp+0xCE0] R, [rbp+0xA50] W, [rbp+0xA58] R/out-ptr argument, [rbp+0xCE8] R argument, [rbp+0xD60] R then W=0, [rbp+0xAD0] W, [rbp+0xA18] R (switch byte), [rbp+0x990] W, [rbp+0x998] R/out address, [rbp+0xA10] W [V]. Callees: 0xE869FF0 sub_e869ff0 [V] role [?]; 0xE86A0D0 sub_e86a0d0 [V] role [?]. Next address: 0x66d51b5.

## Phase 4 — 0x66d51b5, 40 instructions [V]
```
0x66d51b5  mov rdx,rbx                                   
0x66d51b8  call 0xE86A0D0                                ; -> sub_e86a0d0
0x66d51bd  nop                                           
0x66d51be  mov rax,[rbp+0xAD0]                           
0x66d51c5  mov [rbp+0xA10],rax                           
0x66d51cc  jmp 0x66D5291                                 ; -> loc_66d5291
0x66d51d1  mov rdx,rbx                                   
0x66d51d4  call 0xE869FF0                                ; -> sub_e869ff0
0x66d51d9  nop                                           
0x66d51da  mov rax,[rbp+0xAD0]                           
0x66d51e1  mov [rbp+0xA10],rax                           
0x66d51e8  mov byte ptr [rbp+0xA18],1                    
0x66d51ef  mov eax,[rbp+0x208]                           
0x66d51f5  movzx r9d,byte ptr [rbp+0x20C]                
0x66d51fd  movzx ecx,byte ptr [rbp+0x21C]                
0x66d5204  movdqu xmm0,[rbp+0x220]                       
0x66d520c  lea r8,[rbp+0x230]                            
0x66d5213  lea rdx,[rbp+0x8F8]                           
0x66d521a  cmp byte ptr [rbp+0x928],1                    
0x66d5221  mov rbx,[rbp+0xD80]                           
0x66d5228  jne 0x66D5315                                 ; -> loc_66d5315
0x66d522e  mov [rbp+0x8D4],r9b                           
0x66d5235  mov r9d,[rbp+0x218]                           
0x66d523c  mov [rbp+0x8E0],r9d                           
0x66d5243  mov r9,[rbp+0x210]                            
0x66d524a  mov [rbp+0x8D8],r9                            
0x66d5251  movdqu xmm1,[r8]                              
0x66d5256  movdqu xmm2,[r8+0x10]                         
0x66d525c  movups xmm3,[r8+0x1F]                         
0x66d5261  movdqu [rdx],xmm1                             
0x66d5265  movups [rdx+0x1F],xmm3                        
0x66d5269  movdqu [rdx+0x10],xmm2                        
0x66d526e  jmp 0x66D535C                                 ; -> loc_66d535c
0x66d5273  mov rdx,rbx                                   
0x66d5276  call 0xE869FF0                                ; -> sub_e869ff0
0x66d527b  nop                                           
0x66d527c  mov rax,[rbp+0xAD0]                           
0x66d5283  mov [rbp+0xA10],rax                           
0x66d528a  mov byte ptr [rbp+0xA18],1                    
0x66d5291  mov eax,[rbp+0x208]                           
0x66d5297  movzx r9d,byte ptr [rbp+0x20C]                
```
// [V] Phase 4 completes the byte-[rbp+0xA18] switch from phase 3: case-1 path at 0x66d51b5: rdx=rbx; call 0xE86A0D0(rdx=&rbp+0xA58) sub_e86a0d0 [V]; nop; rax=[rbp+0xAD0]; [rbp+0xA10]=rax; jmp 0x66d5291 join [V]. Case !=1 at 0x66d51d1 (from 0x66d512f): rdx=rbx; call 0xE869FF0(rdx=&rbp+0xA58) sub_e869ff0 [V]; nop; rax=[rbp+0xAD0]; [rbp+0xA10]=rax; mov byte [rbp+0xA18],1 [V]; fallthrough to 0x66d51ef. Join at 0x66d51ef: eax=[rbp+0x208]; r9d=byte [rbp+0x20C]; ecx=byte [rbp+0x21C]; movdqu xmm0=[rbp+0x220]; lea r8,&rbp+0x230; lea rdx,&rbp+0x8F8; cmp byte [rbp+0x928],1; rbx=[rbp+0xD80]; jne 0x66d5315 if flag != 1 [V]. Fallthrough (flag==1): [rbp+0x8D4]=r9b; r9d=[rbp+0x218]; [rbp+0x8E0]=r9d; r9=[rbp+0x210]; [rbp+0x8D8]=r9 [V]; movdqu xmm1=[r8]=[rbp+0x230]; xmm2=[r8+0x10]; movups xmm3=[r8+0x1F] (unaligned 0x1F load) [V]; movdqu [rdx]=[rbp+0x8F8]=xmm1; movups [rdx+0x1F]=xmm3; movdqu [rdx+0x10]=xmm2 — 0x20-byte struct copy [rbp+0x230..0x24F]→[rbp+0x8F8..0x907] [V]; jmp 0x66d535c [V]. Case 0x66d5273 (from 0x66d51af, [rbp+0xA18]!=1): rdx=rbx; call 0xE869FF0(rdx=&rbp+0xA58) [V]; nop; rax=[rbp+0xAD0]; [rbp+0xA10]=rax; mov byte [rbp+0xA18],1 [V]; fallthrough into loc_66d5291. loc_66d5291 (target of 0x66d51cc jmp): eax=[rbp+0x208]; r9d=byte [rbp+0x20C] — continues phase 5 [V]. Fields touched: [rbp+0xA10] W, [rbp+0xA18] W=1, [rbp+0x208]/[rbp+0x20C]/[rbp+0x21C]/[rbp+0x220]/[rbp+0x230]/[rbp+0x218]/[rbp+0x210] R, [rbp+0x928] R cmp, [rbp+0xD80] R→rbx, [rbp+0x8D4]/[rbp+0x8E0]/[rbp+0x8D8] W, [rbp+0x8F8..0x907] W copy [V]. Callees: 0xE86A0D0 sub_e86a0d0 [V], 0xE869FF0 sub_e869ff0 [V]; roles/signatures [?]. Next address: 0x66d5297.

## Phase 5 — 0x66d5297, 40 instructions [V]
```
0x66d5297  movzx r9d,byte ptr [rbp+0x20C]                
0x66d529f  movzx ecx,byte ptr [rbp+0x21C]                
0x66d52a6  movdqu xmm0,[rbp+0x220]                       
0x66d52ae  lea r8,[rbp+0x230]                            
0x66d52b5  lea rdx,[rbp+0x8F8]                           
0x66d52bc  cmp byte ptr [rbp+0x928],1                    
0x66d52c3  mov rbx,[rbp+0xD80]                           
0x66d52ca  jne 0x66D53E8                                 ; -> loc_66d53e8
0x66d52d0  mov [rbp+0x8D4],r9b                           
0x66d52d7  mov r9d,[rbp+0x218]                           
0x66d52de  mov [rbp+0x8E0],r9d                           
0x66d52e5  mov r9,[rbp+0x210]                            
0x66d52ec  mov [rbp+0x8D8],r9                            
0x66d52f3  movdqu xmm1,[r8]                              
0x66d52f8  movdqu xmm2,[r8+0x10]                         
0x66d52fe  movups xmm3,[r8+0x1F]                         
0x66d5303  movdqu [rdx],xmm1                             
0x66d5307  movups [rdx+0x1F],xmm3                        
0x66d530b  movdqu [rdx+0x10],xmm2                        
0x66d5310  jmp 0x66D542F                                 ; -> loc_66d542f
0x66d5315  mov [rbp+0x8D4],r9b                           
0x66d531c  mov r9,[rbp+0x20D]                            
0x66d5323  mov r10,[rbp+0x214]                           
0x66d532a  mov [rbp+0x8DC],r10                           
0x66d5331  mov [rbp+0x8D5],r9                            
0x66d5338  movdqu xmm1,[r8]                              
0x66d533d  movdqu xmm2,[r8+0x10]                         
0x66d5343  movups xmm3,[r8+0x1F]                         
0x66d5348  movdqu [rdx],xmm1                             
0x66d534c  movups [rdx+0x1F],xmm3                        
0x66d5350  movdqu [rdx+0x10],xmm2                        
0x66d5355  mov byte ptr [rbp+0x928],1                    
0x66d535c  mov [rbp+0x8D0],eax                           
0x66d5362  mov [rbp+0x8E4],cl                            
0x66d5368  movdqu [rbp+0x8E8],xmm0                       
0x66d5370  cmp byte ptr [rbp+0x7E3],0                    
0x66d5377  je 0x66D54DD                                  ; -> loc_66d54dd
0x66d537d  cmp byte ptr [rbp+0x859],0                    
0x66d5384  je 0x66D54F1                                  ; -> loc_66d54f1
0x66d538a  test sil,1                                    
0x66d538e  jne 0x66D5502                                 ; -> loc_66d5502
```
// [V] Phase 5 continues loc_66d5291 (jump target from phase 4's 0x66d51cc): eax=[rbp+0x208] (R) [V]; r9d=byte [rbp+0x20C]; ecx=byte [rbp+0x21C]; movdqu xmm0=[rbp+0x220]; lea r8=&rbp+0x230; lea rdx=&rbp+0x8F8; cmp byte [rbp+0x928],1; rbx=[rbp+0xD80]; jne 0x66d53e8 (flag != 1 → alternate path, target not yet decoded) [V]. Fallthrough (flag==1): [rbp+0x8D4]=r9b; r9d=[rbp+0x218]; [rbp+0x8E0]=r9d; r9=[rbp+0x210]; [rbp+0x8D8]=r9 [V]; movdqu xmm1=[r8]; xmm2=[r8+0x10]; movups xmm3=[r8+0x1F]; movdqu [rdx]=[rbp+0x8F8]=xmm1; movups [rdx+0x1F]=xmm3; movdqu [rdx+0x10]=xmm2; jmp 0x66d542f — 0x20-byte struct copy [rbp+0x230..0x24F]→[rbp+0x8F8..0x907] then join [V]. Alternate path 0x66d5315 (flag != 1): [rbp+0x8D4]=r9b; r9=[rbp+0x20D]; r10=[rbp+0x214]; [rbp+0x8DC]=r10; [rbp+0x8D5]=r9 [V]; same struct copy [rbp+0x230]→[rbp+0x8F8]; mov byte [rbp+0x928],1 (set flag) [V]. Join 0x66d535c: [rbp+0x8D0]=eax; [rbp+0x8E4]=cl; movdqu [rbp+0x8E8]=xmm0 [V]; cmp byte [rbp+0x7E3],0; je 0x66d54dd; cmp byte [rbp+0x859],0; je 0x66d54f1 (two flag-gated fallthrough targets, not yet decoded) [V]. loc_66d538a (branch target from 0x66d54eb, forward edge): test sil,1 (sil=esi low byte set at 0x66d5151) [V]; jne 0x66d5502 — continues phase 6 [V]. Fields touched: [rbp+0x208] R→eax, [rbp+0x20C] R→r9d, [rbp+0x21C] R→ecx→[rbp+0x8E4] W, [rbp+0x220] R→xmm0→[rbp+0x8E8] W, [rbp+0x230]/[rbp+0x218]/[rbp+0x210] R copy src, [rbp+0x20D]/[rbp+0x214] R (alternate path) →[rbp+0x8D5]/[rbp+0x8DC] W, [rbp+0x8D4] W, [rbp+0x8D8] W (fallthrough), [rbp+0x928] R cmp then W=1 (alternate), [rbp+0xD80] R→rbx [V, rbx unused within phase — possibly dead or used at 0x66d53e8] [I], [rbp+0x8D0] W, [rbp+0x8F8..0x907] W copy, [rbp+0x7E3] R, [rbp+0x859] R [V]. Next address: 0x66d538e.

## Phase 6 — 0x66d538e, 40 instructions [V]
```
0x66d538e  jne 0x66D5502                                 ; -> loc_66d5502
0x66d5394  cmp byte ptr [rbp+0xD68],0                    
0x66d539b  je 0x66D5551                                  ; -> loc_66d5551            
0x66d53a1  movq xmm0,[rbp+0x504]                         
0x66d53a9  movd xmm1,[rbp+0x500]                         
0x66d53b1  movd [rbp+0x840],xmm1                         
0x66d53b9  cmp byte ptr [rbp+0x84C],0                    
0x66d53c0  jne short 0x66D53C9                           ; -> loc_66d53c9
0x66d53c2  mov byte ptr [rbp+0x84C],1                    
0x66d53c9  movq [rbp+0x844],xmm0                         
0x66d53d1  cmp byte ptr [rbp+0x7E5],0                    
0x66d53d8  jne short 0x66D53E1                           ; -> loc_66d53e1
0x66d53da  mov byte ptr [rbp+0x7E5],1                    
0x66d53e1  mov al,5                                      
0x66d53e3  jmp 0x66D5563                                 ; -> loc_66d5563
0x66d53e8  mov [rbp+0x8D4],r9b                           
0x66d53ef  mov r9,[rbp+0x20D]                            
0x66d53f6  mov r10,[rbp+0x214]                           
0x66d53fd  mov [rbp+0x8DC],r10                           
0x66d5404  mov [rbp+0x8D5],r9                            
0x66d540b  movdqu xmm1,[r8]                              ; R a2+0x0
0x66d5410  movdqu xmm2,[r8+0x10]                         ; R a2+0x10
0x66d5416  movups xmm3,[r8+0x1F]                         ; R a2+0x1F
0x66d541b  movdqu [rdx],xmm1                             ; W a1+0x0
0x66d541f  movups [rdx+0x1F],xmm3                        ; W a1+0x1F
0x66d5423  movdqu [rdx+0x10],xmm2                        ; W a1+0x10
0x66d5428  mov byte ptr [rbp+0x928],1                    
0x66d542f  mov [rbp+0x8D0],eax                           
0x66d5435  mov [rbp+0x8E4],cl                            
0x66d543b  movdqu [rbp+0x8E8],xmm0                       
0x66d5443  mov rcx,[rdi]                                 
0x66d5446  movzx eax,word ptr [rcx+0x178]                
0x66d544d  cmp byte ptr [rbp+0x852],0                    
0x66d5454  jne short 0x66D545D                           ; -> loc_66d545d
0x66d5456  mov byte ptr [rbp+0x852],1                    
0x66d545d  mov [rbp+0x850],ax                            
0x66d5464  mov rax,[rbp+0xD78]                           
0x66d546b  cmp byte ptr [rax+0x130],1                    
0x66d5472  jne 0x66D5516                                 ; -> loc_66d5516
0x66d5478  test r15b,8                                   
0x66d547c  jne 0x66D557E                                 ; -> loc_66d557e
```
// [V] Phase 6 is a two-entry field-copy region entered at 0x66d538e (`jne 0x66d5502` from prior context's `test sil,1`) [V]. Entry A at 0x66d5394 (target of 0x66d54fc): `cmp byte [rbp+0xD68],0; je 0x66d5551` — if zero exit to 0x66d5551; else fallthrough copies `xmm0=[rbp+0x504]`, `xmm1=[rbp+0x500]`; `movd [rbp+0x840],xmm1` (low dword of [rbp+0x500]) [V]; set-once flag `cmp byte [rbp+0x84C],0; jne 0x66d53c9; else mov byte [rbp+0x84C],1` [V]; `movq [rbp+0x844],xmm0` (qword [rbp+0x504]) [V]; set-once flag `cmp byte [rbp+0x7E5],0; jne 0x66d53e1; else mov byte [rbp+0x7E5],1` [V]; `mov al,5; jmp 0x66d5563` [V] — carry al=5 to join 0x66d5563 [V]. Entry B at 0x66d53e8 (jump target, linear after the jmp): `mov [rbp+0x8D4],r9b; r9=[rbp+0x20D]; r10=[rbp+0x214]; [rbp+0x8DC]=r10; [rbp+0x8D5]=r9` [V]; then 0x20-byte struct copy `[rbp+0x230]`(r8) → `[rbp+0x8F8]`(rdx): `movdqu xmm1=[r8]`; `xmm2=[r8+0x10]`; `movups xmm3=[r8+0x1F]`; `movdqu [rdx]=xmm1`; `movups [rdx+0x1F]=xmm3`; `movdqu [rdx+0x10]=xmm2`; `mov byte [rbp+0x928],1` [V]; common join at 0x66d542f (also target of phase 5's `jmp 0x66d542f`): `[rbp+0x8D0]=eax; [rbp+0x8E4]=cl; movdqu [rbp+0x8E8]=xmm0` [V]; `rcx=[rdi]; movzx eax,word ptr [rcx+0x178]` (vtable field at 0x178) [V]; set-once flag `cmp byte [rbp+0x852],0; jne 0x66d545d; else mov byte [rbp+0x852],1` [V]; loc_66d545d: `[rbp+0x850]=ax` [V]; `rax=[rbp+0xD78]`; `cmp byte [rax+0x130],1; jne 0x66d5516` [V]; `test r15b,8; jne 0x66d557e` [V] — two forward branch targets not yet decoded [?]. Fields touched: [rbp+0xD68] R, [rbp+0x500] R, [rbp+0x504] R, [rbp+0x840] W, [rbp+0x844] W, [rbp+0x84C] W=1 set-once, [rbp+0x7E5] W=1 set-once, [rbp+0x8D4] W, [rbp+0x8D5] W, [rbp+0x8DC] W, [rbp+0x8D0] W, [rbp+0x8E4] W, [rbp+0x8E8] W, [rbp+0x850] W, [rbp+0x852] W=1 set-once, [rbp+0x928] W=1 (entry B), r8/rdx copy src/dst, [rbp+0xD78] R→rax, [rax+0x130] R, r15b R [V]. Callees: none [V]. Next address: 0x66d547c (phase-6 I41, taken directly from rdis output).

## Phase 7 — 0x66d547c, 40 instructions [V]
```
0x66d547c  jne 0x66D557E                                 ; -> loc_66d557e
0x66d5482  movq xmm0,[rbp+0x504]                         
0x66d548a  movd xmm1,[rbp+0x500]                         
0x66d5492  movd [rbp+0x840],xmm1                         
0x66d549a  cmp byte ptr [rbp+0x84C],0                    
0x66d54a1  jne short 0x66D54AA                           ; -> loc_66d54aa
0x66d54a3  mov byte ptr [rbp+0x84C],1                    
0x66d54aa  movq [rbp+0x844],xmm0                         
0x66d54b2  cmp byte ptr [rbp+0x859],0                    
0x66d54b9  jne short 0x66D54C2                           ; -> loc_66d54c2
0x66d54bb  mov byte ptr [rbp+0x859],1                    
0x66d54c2  mov al,2                                      
0x66d54c4  cmp byte ptr [rbp+0x7E5],0                    
0x66d54cb  jne 0x66D55A0                                 ; -> loc_66d55a0
0x66d54d1  mov byte ptr [rbp+0x7E5],1                    
0x66d54d8  jmp 0x66D55A0                                 ; -> loc_66d55a0
0x66d54dd  mov byte ptr [rbp+0x7E3],1                    
0x66d54e4  cmp byte ptr [rbp+0x859],0                    
0x66d54eb  jne 0x66D538A                                 ; -> sub_66d538a
0x66d54f1  mov byte ptr [rbp+0x859],1                    
0x66d54f8  test sil,1                                    
0x66d54fc  je 0x66D5394                                  ; -> sub_66d5394
0x66d5502  cmp byte ptr [rbp+0x7E9],0                    
0x66d5509  jne short 0x66D5512                           ; -> loc_66d5512
0x66d550b  mov byte ptr [rbp+0x7E9],1                    
0x66d5512  mov al,4                                      
0x66d5514  jmp short 0x66D5563                           ; -> loc_66d5563
0x66d5516  test r15d,0x1000                              
0x66d551d  sete al                                       
0x66d5520  mov edx,[rbp+0xD6C]                           
0x66d5526  xor dl,1                                      
0x66d5529  test al,dl                                    
0x66d552b  jne short 0x66D5571                           ; -> loc_66d5571
0x66d552d  cmp byte ptr [rbp+0x7E9],0                    
0x66d5534  jne short 0x66D553D                           ; -> loc_66d553d
0x66d5536  mov byte ptr [rbp+0x7E9],1                    
0x66d553d  mov al,1                                      
0x66d553f  cmp byte ptr [rbp+0x859],0                    
0x66d5546  jne short 0x66D55A0                           ; -> loc_66d55a0
0x66d5548  mov byte ptr [rbp+0x859],1                    
0x66d554f  jmp short 0x66D55A0                           ; -> loc_66d55a0
```
// [V] Phase 7 is the flag-gated join/tail region. Entry at 0x66d547c from phase 6's `test r15b,8; jne 0x66d557e` — if taken, exit to loc_66d557e (not yet decoded) [V]; else fallthrough loc_66d5482 (target of 0x66d5578): `movq xmm0=[rbp+0x504]; movd xmm1=[rbp+0x500]; movd [rbp+0x840],xmm1` [V]; set-once flag `cmp byte [rbp+0x84C],0; jne 0x66d54aa; else mov byte [rbp+0x84C],1` [V]; `movq [rbp+0x844],xmm0` [V]; set-once flag `cmp byte [rbp+0x859],0; jne 0x66d54c2; else mov byte [rbp+0x859],1` [V]; `mov al,2` [V]; `cmp byte [rbp+0x7E5],0; jne 0x66d55a0; else mov byte [rbp+0x7E5],1; jmp 0x66d55a0` [V] — both paths to loc_66d55a0 with al=2. Block at 0x66d54dd (phase-5 je target): `mov byte [rbp+0x7E3],1` [V]; `cmp byte [rbp+0x859],0; jne 0x66d538a` (re-entry jump back to sub start sub_66d538a) [V]; else `mov byte [rbp+0x859],1`; `test sil,1; je 0x66d5394` (entry-A loop back) [V]. Block at 0x66d5502 (phase-6 jne target): `cmp byte [rbp+0x7E9],0; jne 0x66d5512; else mov byte [rbp+0x7E9],1; mov al,4; jmp short 0x66d5563` [V] — al=4 to common join 0x66d5563. Block at 0x66d5516 (phase-6 jne target): `test r15d,0x1000; sete al` (al = bit 12 of r15d) [V]; `mov edx,[rbp+0xD6C]; xor dl,1; test al,dl; jne 0x66d5571` [V]; else `cmp byte [rbp+0x7E9],0; jne 0x66d553d; else mov byte [rbp+0x7E9],1` [V]; `mov al,1` [V]; `cmp byte [rbp+0x859],0; jne 0x66d55a0; else mov byte [rbp+0x859],1; jmp short 0x66d55a0` [V] — al=1 to loc_66d55a0. Summary [I]: al-encoded result dispatch (al∈{1,2,4}) to joins 0x66d5563/0x66d55a0, with re-entry 0x66d538a and exits 0x66d5571/0x66d557e gated on set-once flags [rbp+0x7E3]/[rbp+0x7E5]/[rbp+0x7E9]/[rbp+0x84C]/[rbp+0x859] and bits of r15d/[rbp+0xD6C]. Fields touched: [rbp+0x500] R, [rbp+0x504] R, [rbp+0x840] W, [rbp+0x844] W, [rbp+0x84C] W=1, [rbp+0x859] R/W=1, [rbp+0x7E5] R/W=1, [rbp+0x7E3] W=1, [rbp+0x7E9] R/W=1, sil R, r15d R, [rbp+0xD6C] R, al W (result code 1/2/4) [V]. Callees: none [V]. Next address: 0x66d554f (phase-7 I41, taken directly from rdis output).

## Phase 8 — 0x66d554f, 40 instructions [V]
```
0x66d554f  jmp short 0x66D55A0                           ; -> loc_66d55a0
0x66d5551  cmp byte ptr [rbp+0x7E7],0                    
0x66d5558  jne short 0x66D5561                           ; -> loc_66d5561
0x66d555a  mov byte ptr [rbp+0x7E7],1                    
0x66d5561  mov al,3                                      
0x66d5563  test r12,r12                                  
0x66d5566  jne 0x66D5600                                 ; -> loc_66d5600
0x66d556c  jmp 0x66D5B34                                 ; -> loc_66d5b34
0x66d5571  cmp byte ptr [rbp+0xD68],0                    
0x66d5578  jne 0x66D5482                                 ; -> sub_66d5482
0x66d557e  cmp byte ptr [rbp+0x7E7],0                    
0x66d5585  jne short 0x66D558E                           ; -> loc_66d558e
0x66d5587  mov byte ptr [rbp+0x7E7],1                    
0x66d558e  cmp byte ptr [rbp+0x859],0                    
0x66d5595  jne short 0x66D559E                           ; -> loc_66d559e
0x66d5597  mov byte ptr [rbp+0x859],1                    
0x66d559e  xor eax,eax                                   
0x66d55a0  mov rcx,[rcx+0x140]                           ; R a0+0x140
0x66d55a7  lea rdx,[rcx+0x10]                            ; R *(a0+0x140)+0x10
0x66d55ab  test rcx,rcx                                  
0x66d55ae  cmove rdx,r13                                 
0x66d55b2  mov rcx,0x6FA7846F2C0608BB                    
0x66d55bc  cmp [rdx],rcx                                 
0x66d55bf  jne short 0x66D55EE                           ; -> loc_66d55ee
0x66d55c1  cmp byte ptr [rbp+0x7EB],0                    
0x66d55c8  jne short 0x66D55D1                           ; -> loc_66d55d1
0x66d55ca  mov byte ptr [rbp+0x7EB],1                    
0x66d55d1  xor esi,esi                                   
0x66d55d3  cmp byte ptr [rbp+0x7E1],0                    
0x66d55da  jne short 0x66D55F7                           ; -> loc_66d55f7
0x66d55dc  mov byte ptr [rbp+0x7E1],1                    
0x66d55e3  test sil,sil                                  
0x66d55e6  je 0x66D5B34                                  ; -> loc_66d5b34
0x66d55ec  jmp short 0x66D5600                           ; -> loc_66d5600
0x66d55ee  cmp byte ptr [rbp+0x7E1],0                    
0x66d55f5  je short 0x66D55DC                            ; -> loc_66d55dc
0x66d55f7  test sil,sil                                  
0x66d55fa  je 0x66D5B34                                  ; -> loc_66d5b34
0x66d5600  movss xmm0,[0xEF40D58]                        ; [data_ef40d58] = sub_37f0000
0x66d5608  movss xmm1,[rdi+0x34]                         
0x66d560d  mulss xmm1,xmm0
```
// [V] Phase 8 completes the al-encoded join and starts the object-type check. al sources: al=3 at 0x66d5561 (from 0x66d5551 path: set-once [rbp+0x7E7]); al=0 via `xor eax,eax` at 0x66d559e (set-once [rbp+0x7E7], [rbp+0x859]); al∈{1,2,4} carried from phase 7. Converges at 0x66d5563/0x66d55a0: `test r12,r12; jne 0x66d5600; else jmp 0x66d5b34` [V] — al=3 path exits by r12 test; 0x66d5571 loop-back `cmp byte [rbp+0xD68],0; jne 0x66d5482` (re-enter entry-A of phase 7) else fall into 0x66d557e: set-once [rbp+0x7E7], set-once [rbp+0x859], `xor eax,eax` [V]. Main join loc_66d55a0 (from phase-7 al=1 `jmp 0x66d5563`? no — al=1/2/4 go 0x66d55a0 via 0x66d54cb/0x66d5546/0x66d554f; al=4 went 0x66d5563): `rcx=[rcx+0x140]` (rcx=[rdi] vtable from phase 6; now field at vtable+0x140) [V]; `lea rdx,[rcx+0x10]`; `test rcx,rcx; cmove rdx,r13` (null→sentinel r13) [V]; `mov rcx,0x6FA7846F2C0608BB` (8-byte magic constant) [V]; `cmp [rdx],rcx; jne short 0x66d55ee` [V] — qword compare against magic constant (type/GUID tag) [I]. Equal path: set-once `cmp byte [rbp+0x7EB],0; jne 0x66d55d1; else mov byte [rbp+0x7EB],1` [V]; loc_66d55d1: `xor esi,esi`; `cmp byte [rbp+0x7E1],0; jne 0x66d55f7`; else loc_66d55dc: `mov byte [rbp+0x7E1],1`; `test sil,sil; je 0x66d5b34; else jmp short 0x66d5600` [V]. Unequal path loc_66d55ee: `cmp byte [rbp+0x7E1],0; je short 0x66d55dc`; else loc_66d55f7: `test sil,sil; je 0x66d5b34` [V] — sil!=0 falls through to 0x66d5600. At 0x66d5600 (float math join, reached from r12!=0, sil!=0 paths): `movss xmm0,[0xEF40D58]` (rodata constant, annotated [data_ef40d58] = sub_37f0000) [V]; `movss xmm1,[rdi+0x34]`; `mulss xmm1,xmm0` — scale [rdi+0x34] by rodata float (continues phase 9). Fields touched: [rbp+0x7E7] W=1, [rbp+0x859] R/W=1, [rbp+0xD68] R, [rbp+0x7EB] R/W=1, [rbp+0x7E1] R/W=1, esi W=0, sil R, r12 R, rcx R/W (vtable chain), rdx W, r13 R (sentinel), xmm0/xmm1 W, [rdi+0x34] R, rodata [0xEF40D58] R [V]. Callees: none [V]. Next address: 0x66d560d (phase-8 I41, taken directly from rdis output).

## Phase 9 — 0x66d560d, 40 instructions [V]
```
0x66d560d  mulss xmm1,xmm0                               
0x66d5611  cvttss2si rcx,xmm1                            
0x66d5616  movss xmm1,[rdi+0x30]                         
0x66d561b  mulss xmm1,xmm0                               
0x66d561f  cvttss2si rdx,xmm1                            
0x66d5624  shl edx,8                                     
0x66d5627  movss xmm1,[rdi+0x2C]                         
0x66d562c  mulss xmm1,xmm0                               
0x66d5630  cvttss2si r8,xmm1                             
0x66d5635  or edx,ecx                                    
0x66d5637  shl r8d,0x10                                  
0x66d563b  mulss xmm0,[rdi+0x28]                         
0x66d5640  cvttss2si r9,xmm0                             
0x66d5645  shl r9d,0x18                                  
0x66d5649  or r9d,r8d                                    
0x66d564c  or r9d,edx                                    
0x66d564f  mov ecx,r9d                                   
0x66d5652  or ecx,0xFF                                   
0x66d5658  test r15d,0x4000                              
0x66d565f  cmovne ecx,r9d                                
0x66d5663  mov edx,[rbp+0xCD4]                           
0x66d5669  and edx,8                                     
0x66d566c  mov r8d,r15d                                  
0x66d566f  shr r8d,0xC                                   
0x66d5673  and r8d,0x10                                  
0x66d5677  or r8d,edx                                    
0x66d567a  test r15d,0x600                               
0x66d5681  je short 0x66D56F1                            ; -> loc_66d56f1
0x66d5683  movzx r8d,r8w                                 
0x66d5687  or r8d,0x20                                   
0x66d568b  movups xmm0,[rdi+0x60]                        
0x66d568f  mulps xmm0,[0xF0837E0]                        ; [data_f0837e0] = sub_37f0000
0x66d5696  cvttps2dq xmm1,xmm0                           
0x66d569a  movdqa xmm2,xmm1                              
0x66d569e  psrad xmm2,0x1F                               
0x66d56a3  subps xmm0,[0xF089480]                        ; [data_f089480]
0x66d56aa  cvttps2dq xmm0,xmm0                           
0x66d56ae  pand xmm0,xmm2                                
0x66d56b2  por xmm0,xmm1                                 
0x66d56b6  pshufd xmm1,xmm0,0xF5                         
0x66d56bb  pmuludq xmm0,[0xF0FF260]                      ; [data_f0ff260]
```
// [V] Phase 9 packs 4 scaled floats into a 32-bit color and starts vector float→int conversion. Continuing phase 8 (xmm1=[rdi+0x34]*rodata[0xEF40D58]): `cvttss2si rcx,xmm1`; `[rdi+0x30]*scale → edx <<8`; `[rdi+0x2C]*scale → r8d <<0x10`; `xmm0*[rdi+0x28] → r9d <<0x18`; `or edx,ecx; or r9d,r8d; or r9d,edx` → packed color r9d = A<<24|B<<16|G<<8|R (src fields [rdi+0x28..0x34] in reverse order) [V]; `mov ecx,r9d; or ecx,0xFF` (force alpha 0xFF); `test r15d,0x4000; cmovne ecx,r9d` — if r15d bit 0x4000 set, keep packed alpha else force 0xFF [V]; `edx=[rbp+0xCD4]&8; r8d=(r15d>>12)&0x10; r8d|=edx` — flag byte from [rbp+0xCD4] bit3 and r15d bit 0xC [V]; `test r15d,0x600; je short 0x66d56f1` — if bits 0x600 clear skip vector block [V]. Vector block: `movzx r8d,r8w; or r8d,0x20`; `movups xmm0,[rdi+0x60]`; `mulps xmm0,[0xF0837E0]` (rodata float4 [data_f0837e0]) [V]; `cvttps2dq xmm1,xmm0` (truncate to int); `movdqa xmm2,xmm1; psrad xmm2,0x1F` (sign mask); `subps xmm0,[0xF089480]` (rodata float4 [data_f089480]); `cvttps2dq xmm0,xmm0; pand xmm0,xmm2; por xmm0,xmm1` — floor-with-sign trick (add/sub bias per sign) [I]; `pshufd xmm1,xmm0,0xF5`; `pmuludq xmm0,[0xF0FF260]` (rodata [data_f0ff260]) — continues phase 10. Fields touched: xmm0/xmm1 W, xmm2 W, rcx/rdx/r8/r9d W (packed color), [rdi+0x28]/[rdi+0x2C]/[rdi+0x30]/[rdi+0x34] R, [rbp+0xCD4] R, r15d R (flag bits 0x4000/0x600/0xC), rodata [0xEF40D58]/[0xF0837E0]/[0xF089480]/[0xF0FF260] R [V]; [rdi+0x60] R [V]. Callees: none [V]. Next address: 0x66d56bb (phase-9 I41, taken directly from rdis output).

## Phase 10 — 0x66d56bb, 40 instructions [V]
```
0x66d56bb  pmuludq xmm0,[0xF0FF260]                      ; [data_f0ff260]
0x66d56c3  pmuludq xmm1,[0xF0FF270]                      ; [data_f0ff270]
0x66d56cb  pshufd xmm0,xmm0,0xE8                         
0x66d56d0  pshufd xmm1,xmm1,0xE8                         
0x66d56d5  punpckldq xmm0,xmm1                           
0x66d56d9  pshufd xmm1,xmm0,0xEE                         
0x66d56de  por xmm1,xmm0                                 
0x66d56e2  pshufd xmm0,xmm1,0x55                         
0x66d56e7  por xmm0,xmm1                                 
0x66d56eb  movd edx,xmm0                                 
0x66d56ef  jmp short 0x66D56F6                           ; -> loc_66d56f6
0x66d56f1  mov edx,0xFFFFFF00                            
0x66d56f6  test r15d,0x80000                             
0x66d56fd  je 0x66D578A                                  ; -> loc_66d578a
0x66d5703  movss xmm0,[rdi+0x24]                         
0x66d5708  pxor xmm1,xmm1                                
0x66d570c  ucomiss xmm0,xmm1                             
0x66d570f  jbe short 0x66D578A                           ; -> loc_66d578a
0x66d5711  movzx r8d,r8w                                 
0x66d5715  or r8d,0x40                                   
0x66d5719  movsd xmm1,[rdi+0x1C]                         
0x66d571e  movss xmm2,[rdi+0x18]                         
0x66d5723  unpcklps xmm2,xmm0                            
0x66d5726  shufps xmm1,xmm2,0x41                         
0x66d572a  mulps xmm1,[0xF0837E0]                        ; [data_f0837e0] = sub_37f0000
0x66d5731  cvttps2dq xmm0,xmm1                           
0x66d5735  movdqa xmm2,xmm0                              
0x66d5739  psrad xmm2,0x1F                               
0x66d573e  subps xmm1,[0xF089480]                        ; [data_f089480]
0x66d5745  cvttps2dq xmm1,xmm1                           
0x66d5749  pand xmm1,xmm2                                
0x66d574d  por xmm1,xmm0                                 
0x66d5751  pshufd xmm0,xmm1,0xF5                         
0x66d5756  pmuludq xmm1,[0xF2760C0]                      ; [data_f2760c0]
0x66d575e  pmuludq xmm0,[0xF0FF270]                      ; [data_f0ff270]
0x66d5766  pshufd xmm1,xmm1,0xE8                         
0x66d576b  pshufd xmm0,xmm0,0xE8                         
0x66d5770  punpckldq xmm1,xmm0                           
0x66d5774  pshufd xmm0,xmm1,0xEE                         
0x66d5779  por xmm0,xmm1                                 
0x66d577d  pshufd xmm1,xmm0,0x55
```
// [V] Phase 10 finishes the first packed-color reduction and starts a second conditional vector conversion. Finish block 1 (from phase 9): `pmuludq xmm0,[0xF0FF260]; pmuludq xmm1,[0xF0FF270]; pshufd xmm0,xmm0,0xE8; pshufd xmm1,xmm1,0xE8; punpckldq xmm0,xmm1; pshufd xmm1,xmm0,0xEE; por xmm1,xmm0; pshufd xmm0,xmm1,0x55; por xmm0,xmm1; movd edx,xmm0` — horizontal pack of 4 floored ints into edx via fixed-point pmuludq/shuffle magic constants [data_f0ff260, data_f0ff270] [V]; `jmp short 0x66d56f6`; skip-path loc_66d56f1 (from phase 9's `je 0x66d56f1`): `mov edx,0xFFFFFF00` [V]. loc_66d56f6 (join): `test r15d,0x80000; je 0x66d578a` — if bit 0x80000 clear, skip second conversion [V]; `movss xmm0,[rdi+0x24]; pxor xmm1,xmm1; ucomiss xmm0,xmm1; jbe short 0x66d578a` — if [rdi+0x24] <= 0 skip [V]; else: `movzx r8d,r8w; or r8d,0x40` (flag bit 0x40 set) [V]; second vector group: `movsd xmm1,[rdi+0x1C]; movss xmm2,[rdi+0x18]; unpcklps xmm2,xmm0; shufps xmm1,xmm2,0x41` (build float4 from [rdi+0x18],[rdi+0x1C],[rdi+0x24]) [V]; `mulps xmm1,[0xF0837E0]` (rodata float4 [data_f0837e0]) [V]; same floor trick: `cvttps2dq xmm0,xmm1; movdqa xmm2,xmm0; psrad xmm2,0x1F; subps xmm1,[0xF089480] (rodata [data_f089480]); cvttps2dq xmm1,xmm1; pand xmm1,xmm2; por xmm1,xmm0` [V]; `pshufd xmm0,xmm1,0xF5; pmuludq xmm1,[0xF2760C0] (rodata [data_f2760c0]); pmuludq xmm0,[0xF0FF270] (rodata [data_f0ff270]); pshufd xmm1,xmm1,0xE8; pshufd xmm0,xmm0,0xE8; punpckldq xmm1,xmm0; pshufd xmm0,xmm1,0xEE; por xmm0,xmm1; pshufd xmm1,xmm0,0x55` — pack continues phase 11. Fields touched: edx W (packed result), xmm0/xmm1/xmm2 W, [rdi+0x60] R (phase-9 block), [rdi+0x24] R, [rdi+0x18] R, [rdi+0x1C] R, r15d R (bits 0x80000, plus 0x40/0x20/0x10 flag assembly), r8d W flag assembly [V]. Roadata: [0xF0FF260], [0xF0FF270], [0xF2760C0], [0xF0837E0], [0xF089480] R [V]. Callees: none [V]. Next address: 0x66d577d (phase-10 I41, taken directly from rdis output).

## Phase 11 — 0x66d577d, 40 instructions [V]
```
0x66d577d  pshufd xmm1,xmm0,0x55                         
0x66d5782  por xmm1,xmm0                                 
0x66d5786  movd edx,xmm1                                 
0x66d578a  shl r15d,7                                    
0x66d578e  and r15d,0x4000                               
0x66d5795  movzx r9d,r8w                                 
0x66d5799  or r9d,r15d                                   
0x66d579c  mov r8,[rbp+0xD78]                            
0x66d57a3  cmp byte ptr [r8+0x130],1                     
0x66d57ab  jne short 0x66D5820                           ; -> loc_66d5820
0x66d57ad  movups xmm0,[r8]                              
0x66d57b1  mulps xmm0,[0xF0837E0]                        ; [data_f0837e0] = sub_37f0000
0x66d57b8  cvttps2dq xmm1,xmm0                           
0x66d57bc  movdqa xmm2,xmm1                              
0x66d57c0  psrad xmm2,0x1F                               
0x66d57c5  subps xmm0,[0xF089480]                        ; [data_f089480]
0x66d57cc  cvttps2dq xmm0,xmm0                           
0x66d57d0  pand xmm0,xmm2                                
0x66d57d4  por xmm0,xmm1                                 
0x66d57d8  pshufd xmm1,xmm0,0xF5                         
0x66d57dd  pmuludq xmm0,[0xF0FF260]                      ; [data_f0ff260]
0x66d57e5  pmuludq xmm1,[0xF0FF270]                      ; [data_f0ff270]
0x66d57ed  pshufd xmm0,xmm0,0xE8                         
0x66d57f2  pshufd xmm1,xmm1,0xE8                         
0x66d57f7  punpckldq xmm0,xmm1                           
0x66d57fb  pshufd xmm1,xmm0,0xEE                         
0x66d5800  por xmm1,xmm0                                 
0x66d5804  pshufd xmm0,xmm1,0x55                         
0x66d5809  por xmm0,xmm1                                 
0x66d580d  movd ecx,xmm0                                 
0x66d5811  movzx r9d,r9w                                 
0x66d5815  or r9d,0x2001                                 
0x66d581c  xor eax,eax                                   
0x66d581e  jmp short 0x66D5839                           ; -> loc_66d5839
0x66d5820  cmp al,2                                      
0x66d5822  je 0x66D5F0A                                  ; -> loc_66d5f0a
0x66d5828  movzx r8d,al                                  
0x66d582c  cmp r8d,4                                     
0x66d5830  jne short 0x66d5839                           ; -> loc_66d5839
0x66d5832  mov r10w,0x1000                               
0x66d5837  jmp short 0x66D583C                           ; -> loc_66d583c
```
// [V] Phase 11 assembles final packed colors and flags. Finish phase-10 second vector group: `pshufd xmm1,xmm0,0x55; por xmm1,xmm0; movd edx,xmm1` → edx = packed color #2 [V]; flag assembly: `shl r15d,7; and r15d,0x4000` (extract flag bit from r15d) [V]; `movzx r9d,r8w; or r9d,r15d` (r9d = flags low word | bit) [V]; `mov r8,[rbp+0xD78]; cmp byte [r8+0x130],1; jne short 0x66d5820` — if object field == 1, third packed color: `movups xmm0,[r8]; mulps xmm0,[0xF0837E0]` (rodata [data_f0837e0]) then identical floor+pack trick (`cvttps2dq xmm1,xmm0; movdqa xmm2,xmm1; psrad xmm2,0x1F; subps xmm0,[0xF089480] [data_f089480]; cvttps2dq xmm0,xmm0; pand xmm0,xmm2; por xmm0,xmm1; pshufd xmm1,xmm0,0xF5; pmuludq xmm0,[0xF0FF260] [data_f0ff260]; pmuludq xmm1,[0xF0FF270] [data_f0ff270]; pshufd xmm0,xmm0,0xE8; pshufd xmm1,xmm1,0xE8; punpckldq xmm0,xmm1; pshufd xmm1,xmm0,0xEE; por xmm1,xmm0; pshufd xmm0,xmm1,0x55; por xmm0,xmm1; movd ecx,xmm0`) → ecx = packed color #3 [V]; `movzx r9d,r9w; or r9d,0x2001` (set flag bits 0x2000|1) [V]; `xor eax,eax; jmp short 0x66d5839` (eax=0 result code) [V]. Else loc_66d5820 (field != 1): `cmp al,2; je 0x66d5f0a` (al=2 → jump to 0x66d5f0a, not yet decoded) [V]; `movzx r8d,al; cmp r8d,4; jne short 0x66d5839; else mov r10w,0x1000; jmp short 0x66d583c` — al==4 sets r10w=0x1000 flag [V]; fallthrough/jump target 0x66d583c continues phase 12. Summary [I]: final stage packs up to 3 colors from float groups ([rdi+0x60], [rdi+0x18/0x1C/0x24], [r8]=object data) into edx/ecx via fixed-point pmuludq packing; r9d/r10w/eax are result flags/code; branch on al (2→0x66d5f0a, 4→r10w=0x1000, else join 0x66d5839/0x66d583c). Fields touched: edx W, ecx W, eax W=0, r9d W, r10d/W=0x1000, r15d W, r8 W=[rbp+0xD78], [r8+0x130] R, [r8] R (16 bytes), r8w R [V]. Roadata: [0xF0837E0], [0xF089480], [0xF0FF260], [0xF0FF270] R [V]. Callees: none [V]. Next address: 0x66d583c (phase-11 I41, taken directly from rdis output).

## Phase 12 — 0x66d583c, 40 instructions [V]
```
0x66d583c  xor r11d,r11d                                 
0x66d583f  mov r8,0xC7637522873FF418                     
0x66d5849  cmp r14,r8                                    
0x66d584c  mov r8d,0xFFFFFF00                            
0x66d5852  cmove edx,r8d                                 
0x66d5856  movzx eax,al                                  
0x66d5859  mov r8d,1                                     
0x66d585f  cmovne r8d,eax                                
0x66d5863  cmove r10d,r11d                               
0x66d5867  movzx eax,r9w                                 
0x66d586b  or eax,r10d                                   
0x66d586e  or eax,2                                      
0x66d5871  mov r10,[rdi]                                 
0x66d5874  lea r9,[r10+0xE0]                             
0x66d587b  lea rsi,[r10+0x120]                           
0x66d5882  add r10,0x130                                 
0x66d5889  pxor xmm0,xmm0                                
0x66d588d  movdqa [rbp+0x470],xmm0                       
0x66d5895  mov rdi,[rbx+8]                               
0x66d5899  test rdi,rdi                                  
0x66d589c  je short 0x66D58A6                            ; -> loc_66d58a6
0x66d589e  lock inc dword ptr [rdi+8]                    
0x66d58a2  mov r11,[rbx+8]                               
0x66d58a6  mov rdi,[rbx]                                 
0x66d58a9  mov [rbp+0x470],rdi                           
0x66d58b0  mov [rbp+0x478],r11                           
0x66d58b7  mov [rsp+0x48],edx                            
0x66d58bb  mov [rsp+0x40],ecx                            
0x66d58bf  mov [rsp+0x38],r10                            
0x66d58c4  mov [rsp+0x30],rsi                            
0x66d58c9  mov [rsp+0x28],ax                             
0x66d58ce  mov [rsp+0x20],r9                             
0x66d58d3  lea rcx,[rbp+0xA50]                           
0x66d58da  lea rdx,[rbp+0x470]                           
0x66d58e1  mov r9,0xFFFFFFFFFFFFFFFF                     
0x66d58e8  call 0x673CC80                                ; -> sub_673cc80
0x66d58ed  lea rcx,[rbp+0x868]                           
0x66d58f4  cmp byte ptr [rbp+0x8C8],1                    
0x66d58fb  jne short 0x66D5915                           ; -> loc_66d5915
0x66d58fd  lea rdx,[rbp+0xA50]                           
0x66d5904  call 0x67D1120                                ; -> sub_67d1120
```
// [V] Phase 12 is the final result-assembly block (entered at loc_66d583c, forward edge from 0x66d5f0f — the al==2 target of phase 11): `xor r11d,r11d; mov r8,0xC7637522873FF418` (magic constant) [V]; `cmp r14,r8; mov r8d,0xFFFFFF00; cmove edx,r8d` — if r14 == magic, edx = 0xFFFFFF00 [V]; flag assembly `movzx eax,al; mov r8d,1; cmovne r8d,eax; cmove r10d,r11d` (r8d = al?1:0, r10d = zero unless cmove condition) [V]; `movzx eax,r9w; or eax,r10d; or eax,2` — result code eax = r9w | r10d | 2 [V]; `mov r10,[rdi]; lea r9,[r10+0xE0]; lea rsi,[r10+0x120]; add r10,0x130` — object field addrs [rdi+0xE0]/[rdi+0x120], r10=[rdi]+0x130 [V]; `pxor xmm0,xmm0; movdqa [rbp+0x470],xmm0` (zero [rbp+0x470]) [V]; `mov rdi,[rbx+8]; test rdi,rdi; je 0x66d58a6; else lock inc dword ptr [rdi+8]` (intrusive addref on [rbx+8]) [V]; `mov r11,[rbx+8]; loc_66d58a6: mov rdi,[rbx]; [rbp+0x470]=rdi; [rbp+0x478]=r11` — argument pair {[rbx],[rbx+8]} stored [V]; spill args `[rsp+0x48]=edx; [rsp+0x40]=ecx; [rsp+0x38]=r10; [rsp+0x30]=rsi; [rsp+0x28]=ax; [rsp+0x20]=r9` [V]; `lea rcx,[rbp+0xA50]; lea rdx,[rbp+0x470]; mov r9,0xFFFFFFFFFFFFFFFF; call 0x673CC80(rcx=&rbp+0xA50, rdx=&rbp+0x470, r9=-1)` — new callee sub_673cc80 [V], role/signature [?]; `lea rcx,[rbp+0x868]; cmp byte [rbp+0x8C8],1; jne short 0x66d5915; else lea rdx,[rbp+0xA50]; call 0x67D1120(rcx=&rbp+0x868, rdx=&rbp+0xA50)` — new callee sub_67d1120 [V], gated on [rbp+0x8C8]==1; target 0x66d5915 not decoded (unit ends at 12 phases) [?]. Fields touched: r11d W=0, r8 W magic/R, edx W (conditionally 0xFFFFFF00), eax W result code, r8d W flag, r10d W flag, r9w R→eax, r10 W=[rdi] chain, r9 W, rsi W, rdi W/R, [rdi+0xE0] R, [rdi+0x120] R, [rbx+8] R/W addref, [rbx] R, [rbp+0x470] W (zeroed then pair), [rbp+0x478] W, [rsp+0x20..0x48] W spill slots, [rbp+0xA50] R/out arg, [rbp+0x868] R, [rbp+0x8C8] R cmp [V]. Roadata: none directly; magic imm 0xC7637522873FF418, 0xFFFFFF00 [V]. Callees: 0x673CC80 sub_673cc80 [V] role [?]; 0x67D1120 sub_67d1120 [V] role [?]. Unit U-BA6 ends here: 12 phases complete (0x66d4f8d..0x66d5904). No OPEN questions besides callee roles and the undecoded targets 0x66d557e/0x66d5571/0x66d56f1/0x66d578a/0x66d5839/0x66d5915/0x66d5f0a (all [?]) — forward edges beyond phase-12 scope.
