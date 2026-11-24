## NEXT
DONE

## UNIT
U-EX1.bc7a3d0 | sub_bc7a3d0 | 0xbc7a3d0 size 0x3cc bytes | depth 2 | milestone 1 | region bgfx | status D0 | 0 callees in set | name: bgfx shutdown

## PLAN
1. [x] Write progress file with ## NEXT / step 2
2. [x] Disassemble 0xbc7a3d0..0xbc7a79c fully (fn + dis), capture every instruction verbatim
3. [x] Identify every call target: sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0, native_boundary.tsv row 506) x3; sub_eec6ed0 (0xeec6ed0, crt boundary IAT thunk, row 507) x1. 0 callees in lift set. UNRESOLVED CALL = none.
4. [ ] Read existing dossier docs/functions/bc7a3d0.md if present (input, not proof) — none exists
5. [x] Write C++ lift: src/client/features/render/native/bgfx/sub_bc7a3d0.cpp + .h (LIFT marker first line, // 0xA..0xB cites, verbatim call quotes)
6. [x] Write dossier docs/functions/bc7a3d0.md with Reversed source (complete)
7. [ ] Run liftcheck.py 0xbc7a3d0, fix failures, paste output under ## LIFTCHECK
8. [ ] CLOSES? YES iff LIFTCHECK OK printed, else NO + single blocking fact

## FILES
docs/progress/oc_U-EX1.bc7a3d0.md (progress)
src/client/features/render/native/bgfx/sub_bc7a3d0.h (new)
src/client/features/render/native/bgfx/sub_bc7a3d0.cpp (new)
docs/functions/bc7a3d0.md (new dossier)

## LIFTCHECK
LIFTCHECK OK 0xbc7a3d0

## UNRESOLVED CALL
none

## EVIDENCE (verbatim rdis fn 0xbc7a3d0, [0xbc7a3d0..0xbc7a79c) size 0x3cc)
sub_bc7a3d0  [0xbc7a3d0..0xbc7a79c)  size 0x3cc  17 xrefs in
  bc7a3d0  push rbp                                      
  bc7a3d1  push r15                                      
  bc7a3d3  push r14                                      
  bc7a3d5  push r13                                      
  bc7a3d7  push r12                                      
  bc7a3d9  push rsi                                      
  bc7a3da  push rdi                                      
  bc7a3db  push rbx                                      
  bc7a3dc  sub rsp,0x38                                  
  bc7a3e0  lea rbp,[rsp+0x30]                            
  bc7a3e5  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE        
  bc7a3ed  mov rdi,rdx                                   
  bc7a3f0  mov rsi,rcx                                   
  bc7a3f3  mov rcx,[rcx+0x28008]                         ; R a0+0x28008
  bc7a3fa  mov r15,0xCCCCCCCCCCCCCCD                    
  bc7a404  mov rax,rcx                                   
  bc7a407  mul r15                                       
  bc7a40a  shr rdx,5                                     
  bc7a40e  cmp rdi,rdx                                   
  bc7a411  jae 0xBC7A504                                 ; -> loc_bc7a504
  bc7a417  lea rbx,[0xF847A07]                           ; [data_f847a07]
  bc7a41e  mov r14,rdi                                   
  bc7a421  jmp short 0xBC7A45A                           ; -> loc_bc7a45a
  bc7a423  nop [rax+rax]                                 ; R *(a0+0x28008)+0x0+idx

loc_bc7a430:  ; from bc7a4cc, bc7a4ff
  bc7a430  mov [r12],rbx                                 
  bc7a434  mov dword ptr [r12+8],0                       
  bc7a43d  mov rcx,[rsi+0x28008]                         ; R a0+0x28008

loc_bc7a444:  ; from bc7a47a, bc7a4c0
  bc7a444  mov rax,rcx                                   
  bc7a447  mul r15                                       
  bc7a44a  inc r14                                       
  bc7a44d  shr rdx,5                                     
  bc7a451  cmp r14,rdx                                   
  bc7a454  jae 0xBC7A504                                 ; -> loc_bc7a504

loc_bc7a45a:  ; from bc7a421
  bc7a45a  lea rax,[r14*8]                               
  bc7a462  lea r12,[rax+rax*4]                           
  bc7a466  cmp r14,0xFFF                                 
  bc7a46d  ja short 0xBC7A480                            ; -> loc_bc7a480
  bc7a46f  add r12,rsi                                   
  bc7a472  cmp dword ptr [r12+8],0                       
  bc7a478  jne short 0xBC7A4C2                           ; -> loc_bc7a4c2
  bc7a47a  jmp short 0xBC7A444                           ; -> loc_bc7a444
  bc7a47c  nop [rax]                                     

loc_bc7a480:  ; from bc7a46d
  bc7a480  add r12,0xFFFFFFFFFFFD8000                    
  bc7a487  mov rax,[rsi+0x28000]                         ; R a0+0x28000
  bc7a48e  mov rax,[rax]                                 ; R *(a0+0x28000)+0x0
  bc7a491  cmp r12,0x28000                               
  bc7a498  jb short 0xBC7A4B7                            ; -> loc_bc7a4b7
  bc7a49a  nop [rax+rax]                                 ; R *(*(a0+0x28000)+0x0)+0x0+idx

loc_bc7a4a0:  ; from bc7a4b5
  bc7a4a0  add r12,0xFFFFFFFFFFFD8000                    
  bc7a4a7  mov rax,[rax+0x28000]                         ; R *(*(a0+0x28000)+0x0)+0x28000
  bc7a4ae  cmp r12,0x27FFF                               
  bc7a4b5  ja short 0xBC7A4A0                            ; -> loc_bc7a4a0

loc_bc7a4b7:  ; from bc7a498
  bc7a4b7  add r12,rax                                   
  bc7a4ba  cmp dword ptr [r12+8],0                       
  bc7a4c0  je short 0xBC7A444                            ; -> loc_bc7a444

loc_bc7a4c2:  ; from bc7a478
  bc7a4c2  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc7a4c9  test rcx,rcx                                  
  bc7a4cc  je 0xBC7A430                                  ; -> loc_bc7a430
  bc7a4d2  mov rdx,[r12]                                 
  bc7a4d6  mov rax,[rcx]                                 
  bc7a4d9  mov rax,[rax+8]                               
  bc7a4dd  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc7a4e4  mov dword ptr [rsp+0x28],0                    
  bc7a4ec  mov qword ptr [rsp+0x20],0                    
  bc7a4f5  xor r8d,r8d                                   
  bc7a4f8  xor r9d,r9d                                   
  bc7a4fb  call r10                                      
  bc7a4fe  nop                                           
  bc7a4ff  jmp 0xBC7A430                                 ; -> loc_bc7a430

loc_bc7a504:  ; from bc7a411, bc7a454
  bc7a504  cmp rdi,0x1001                                
  bc7a50b  jb 0xBC7A683                                  ; -> loc_bc7a683
  bc7a511  mov rbx,0xCCCCCCCCCCCCCCD                    
  bc7a51b  mov rax,rbx                                   
  bc7a51e  mul qword ptr [rsi+0x28010]                   
  bc7a525  mov rax,rdx                                   
  bc7a528  shr rax,5                                     
  bc7a52c  mov rdx,rdi                                   
  bc7a52f  cmp rdi,rax                                   
  bc7a532  jbe 0xBC7A6BE                                 ; -> loc_bc7a6be
  bc7a538  lea r12,[rdi+rdi*4]                           
  bc7a53c  shl r12,3                                     
  bc7a540  mov rax,[rsi+0x28000]                         
  bc7a547  add r12,0xFFFFFFFFFFFD8000                    
  bc7a54e  je 0xBC7A688                                  ; -> loc_bc7a688
  bc7a554  test rax,rax                                  
  bc7a557  jne short 0xBC7A5A4                           ; -> loc_bc7a5a4
  bc7a559  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc7a560  mov rax,[rcx]                                 
  bc7a563  mov rax,[rax+8]                               
  bc7a567  lea rdx,[0xF7CC762]                           ; [data_f7cc762] "NOFILE"
  bc7a56e  mov [rsp+0x20],rdx                            
  bc7a573  mov dword ptr [rsp+0x28],0                    
  bc7a57b  mov r8d,0x18                                  
  bc7a581  mov r9d,8                                     
  bc7a587  xor edx,edx                                   
  bc7a589  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7a58f  xorps xmm0,xmm0                               
  bc7a592  movups [rax],xmm0                             
  bc7a595  mov qword ptr [rax+0x10],0                    
  bc7a59d  mov [rsi+0x28000],rax                         

loc_bc7a5a4:  ; from bc7a557
  bc7a5a4  mov rcx,[rax+0x10]                            
  bc7a5a8  sub r12,rcx                                   
  bc7a5ab  jbe 0xBC7A6A6                                 ; -> loc_bc7a6a6
  bc7a5b1  mov rcx,[rax+8]                               
  bc7a5b5  add rax,8                                     
  bc7a5b9  lea r13,[rcx+0x28000]                         
  bc7a5c0  test rcx,rcx                                  
  bc7a5c3  cmove r13,rax                                 
  bc7a5c7  mov ebx,0x28000                               
  bc7a5cc  cmp qword ptr [r13],0                         
  bc7a5d1  jne 0xBC7A660                                 ; -> loc_bc7a660
  bc7a5d7  nop [rax+rax]                                 

loc_bc7a5e0:  ; from bc7a67e
  bc7a5e0  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc7a5e7  mov rax,[rcx]                                 
  bc7a5ea  mov rax,[rax+8]                               
  bc7a5ee  lea rdx,[0xF7CC762]                           ; [data_f7cc762] "NOFILE"
  bc7a5f5  mov [rsp+0x20],rdx                            
  bc7a5fa  mov dword ptr [rsp+0x28],0                    
  bc7a602  mov r8d,0x28008                               
  bc7a608  mov r9d,8                                     
  bc7a60e  xor edx,edx                                   
  bc7a610  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7a616  mov r14,rax                                   
  bc7a619  mov r8d,0x28008                               
  bc7a61f  mov rcx,rax                                   
  bc7a622  xor edx,edx                                   
  bc7a624  call 0xEEC6ED0                                ; -> sub_eec6ed0
  bc7a629  mov [r13],r14                                 
  bc7a62d  mov rax,[rsi+0x28000]                         
  bc7a634  mov [rax+8],r14                               
  bc7a638  mov rax,[rsi+0x28000]                         
  bc7a63f  add qword ptr [rax+0x10],0x28000              
  bc7a647  mov rax,[rsi+0x28000]                         
  bc7a64e  cmp qword ptr [rax],0                         
  bc7a652  jne short 0xBC7A660                           ; -> loc_bc7a660
  bc7a654  mov rcx,[r13]                                 
  bc7a658  mov [rax],rcx                                 
  bc7a65b  nop [rax+rax]                                 

loc_bc7a660:  ; from bc7a5d1, bc7a652, bc7a67c
  bc7a660  cmp r12,0x28001                               
  bc7a667  jb short 0xBC7A691                            ; -> loc_bc7a691
  bc7a669  mov r13,[r13]                                 
  bc7a66d  add r13,rbx                                   
  bc7a670  add r12,0xFFFFFFFFFFFD8000                    
  bc7a677  cmp qword ptr [r13],0                         
  bc7a67c  jne short 0xBC7A660                           ; -> loc_bc7a660
  bc7a67e  jmp 0xBC7A5E0                                 ; -> loc_bc7a5e0

loc_bc7a683:  ; from bc7a50b
  bc7a683  mov rdx,rdi                                   
  bc7a686  jmp short 0xBC7A6BE                           ; -> loc_bc7a6be

loc_bc7a688:  ; from bc7a54e
  bc7a688  test rax,rax                                  
  bc7a68b  jne short 0xBC7A6A2                           ; -> loc_bc7a6a2
  bc7a68d  xor ecx,ecx                                   
  bc7a68f  jmp short 0xBC7A6A6                           ; -> loc_bc7a6a6

loc_bc7a691:  ; from bc7a667
  bc7a691  mov rax,[rsi+0x28000]                         
  bc7a698  mov rbx,0xCCCCCCCCCCCCCCD                    

loc_bc7a6a2:  ; from bc7a68b
  bc7a6a2  mov rcx,[rax+0x10]                            

loc_bc7a6a6:  ; from bc7a5ab, bc7a68f
  bc7a6a6  mov rax,rcx                                   
  bc7a6a9  mul rbx                                       
  bc7a6ac  shr rdx,5                                     
  bc7a6b0  add rdx,0x1000                                
  bc7a6b7  mov rcx,[rsi+0x28008]                         

loc_bc7a6be:  ; from bc7a532, bc7a686
  bc7a6be  shl rdx,3                                     
  bc7a6c2  lea r8,[rdx+rdx*4]                            
  bc7a6c6  mov rax,[rsi+0x28010]                         
  bc7a6cd  cmp rax,r8                                    
  bc7a6d0  cmova r8,rax                                  
  bc7a6d4  mov rax,rcx                                   
  bc7a6d7  mul r15                                       
  bc7a6da  mov [rsi+0x28010],r8                          
  bc7a6e1  shr rdx,5                                     
  bc7a6e5  cmp rdx,rdi                                   
  bc7a6e8  jae 0xBC7A77C                                 ; -> loc_bc7a77c
  bc7a6ee  lea rax,[0xF847A07]                           ; [data_f847a07]
  bc7a6f5  xorps xmm0,xmm0                               
  bc7a6f8  jmp short 0xBC7A728                           ; -> loc_bc7a728
  bc7a6fa  nop [rax+rax]                                 

loc_bc7a700:  ; from bc7a73b
  bc7a700  add rcx,rsi                                   

loc_bc7a703:  ; from bc7a77a
  bc7a703  mov [rcx],rax                                 
  bc7a706  mov dword ptr [rcx+8],0                       
  bc7a70d  inc rdx                                       
  bc7a710  movups [rcx+0x10],xmm0                        
  bc7a714  mov byte ptr [rcx+0x20],0                     
  bc7a718  mov dword ptr [rcx+0x22],0                    
  bc7a71f  mov byte ptr [rcx+0x26],0                     
  bc7a723  cmp rdx,rdi                                   
  bc7a726  je short 0xBC7A77C                            ; -> loc_bc7a77c

loc_bc7a728:  ; from bc7a6f8
  bc7a728  lea rcx,[rdx*8]                               
  bc7a730  lea rcx,[rcx+rcx*4]                           
  bc7a734  cmp rdx,0xFFF                                 
  bc7a73b  jbe short 0xBC7A700                           ; -> loc_bc7a700
  bc7a73d  add rcx,0xFFFFFFFFFFFD8000                    
  bc7a744  mov r8,[rsi+0x28000]                          
  bc7a74b  mov r8,[r8]                                   
  bc7a74e  cmp rcx,0x28000                               
  bc7a755  jb short 0xBC7A777                            ; -> loc_bc7a777
  bc7a757  nop [rax+rax]                                 

loc_bc7a760:  ; from bc7a775
  bc7a760  add rcx,0xFFFFFFFFFFFD8000                    
  bc7a767  mov r8,[r8+0x28000]                           
  bc7a76e  cmp rcx,0x27FFF                               
  bc7a775  ja short 0xBC7A760                            ; -> loc_bc7a760

loc_bc7a777:  ; from bc7a775
  bc7a777  add rcx,r8                                    
  bc7a77a  jmp short 0xBC7A703                           ; -> loc_bc7a703

loc_bc7a77c:  ; from bc7a6e8, bc7a726
  bc7a77c  shl rdi,3                                     
  bc7a780  lea rax,[rdi+rdi*4]                           
  bc7a784  mov [rsi+0x28008],rax                         
  bc7a78b  add rsp,0x38                                  
  bc7a78f  pop rbx                                       
  bc7a790  pop rdi                                       
  bc7a791  pop rsi                                       
  bc7a792  pop r12                                       
  bc7a794  pop r13                                       
  bc7a796  pop r14                                       
  bc7a798  pop r15                                       
  bc7a79a  pop rbp                                       
  bc7a79b  ret

CLOSES? YES
