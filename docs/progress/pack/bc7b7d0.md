# ctxpack build 0xbc7b7d0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=bc7b7d0.md:07ec6886a947c623156f00e74bafadce6235b4a9b5da8f4dd84ed0305e6bfed8,liftsrc=sub_bc7b7d0.cpp:9786004b5dd4c53583601246da0a4328f00300d652d9553edc6320a8e92bc93a,liftsrc=sub_bc7b7d0.h:a28a41192708c93dbca1ab3fad2b4dc1b8364a018f85cebffdb92db6f4e64982,data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb

## HEADER
  rva        : 0xbc7b7d0
  size       : 0x28b (651 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 3 (direct), depth 1
  callers    : 2

## EXACT LISTING (0xbc7b7d0..0xbc7ba5b)
```
sub_bc7b7d0  [0xbc7b7d0..0xbc7d7d0)  size 0x2000  2 xrefs in
  bc7b7d0  push rsi                                      
  bc7b7d1  push rdi                                      
  bc7b7d2  push rbx                                      
  bc7b7d3  sub rsp,0xB0                                  
  bc7b7da  movaps [rsp+0xA0],xmm14                       
  bc7b7e3  movaps [rsp+0x90],xmm13                       
  bc7b7ec  movaps [rsp+0x80],xmm12                       
  bc7b7f5  movaps [rsp+0x70],xmm11                       
  bc7b7fb  movaps [rsp+0x60],xmm10                       
  bc7b801  movaps [rsp+0x50],xmm9                        
  bc7b807  movaps [rsp+0x40],xmm8                        
  bc7b80d  movaps [rsp+0x30],xmm7                        
  bc7b812  movaps [rsp+0x20],xmm6                        
  bc7b817  mov rdi,rdx                                   
  bc7b81a  mov rsi,rcx                                   
  bc7b81d  movss xmm9,[rdx]                              ; R a1+0x0
  bc7b822  movaps xmm6,xmm9                              
  bc7b826  divss xmm6,[0xEFD32AC]                        ; [data_efd32ac] = sub_1200000
  bc7b82e  mulss xmm6,[0xEFC6CF8]                        ; [data_efc6cf8] = sub_2c80000
  bc7b836  movaps xmm0,xmm6                              
  bc7b839  call 0xEEC75A0                                ; -> sub_eec75a0
  bc7b83e  movaps xmm8,xmm0                              
  bc7b842  movss xmm13,[0xEEE6700]                       ; [data_eee6700]
  bc7b84b  subss xmm0,xmm13                              
  bc7b850  cvttss2si rax,xmm0                            
  bc7b855  cvttss2si rcx,xmm8                            
  bc7b85a  mov rbx,rcx                                   
  bc7b85d  sar rbx,0x3F                                  
  bc7b861  and rbx,rax                                   
  bc7b864  or rbx,rcx                                    
  bc7b867  movaps xmm0,xmm6                              
  bc7b86a  call 0xEEC73F0                                ; -> sub_eec73f0
  bc7b86f  cmp rbx,0x65                                  
  bc7b873  jae 0xBC7BA55                                 ; -> loc_bc7ba55
  bc7b879  cvttss2si rcx,xmm0                            
  bc7b87e  subss xmm0,xmm13                              
  bc7b883  cvttss2si rdx,xmm0                            
  bc7b888  mov rax,rcx                                   
  bc7b88b  sar rax,0x3F                                  
  bc7b88f  and rax,rdx                                   
  bc7b892  or rax,rcx                                    
  bc7b895  cmp rax,0x65                                  
  bc7b899  jae 0xBC7BA55                                 ; -> loc_bc7ba55
  bc7b89f  lea rcx,[rbx+rbx*2]                           
  bc7b8a3  lea rdx,[0xF449BEC]                           ; [data_f449bec]
  bc7b8aa  lea rax,[rax+rax*2]                           
  bc7b8ae  movss xmm14,[rdx+rax*4+8]                     
  bc7b8b5  movsd xmm12,[rdx+rax*4]                       
  bc7b8bb  movsd xmm11,[rdx+rcx*4]                       
  bc7b8c1  movss xmm10,[rdx+rcx*4+8]                     
  bc7b8c8  xorps xmm0,xmm0                               
  bc7b8cb  maxss xmm0,xmm9                               
  bc7b8d0  movss xmm7,[0xF10D440]                        ; [data_f10d440] = sub_3960000
  bc7b8d8  divss xmm0,xmm7                               
  bc7b8dc  movss xmm1,[0xEFC6CF8]                        ; [data_efc6cf8] = sub_2c80000
  bc7b8e4  mulss xmm0,xmm1                               
  bc7b8e8  cmpltss xmm7,xmm9                             
  bc7b8ee  movaps xmm2,xmm7                              
  bc7b8f1  andnps xmm2,xmm0                              
  bc7b8f4  andps xmm7,xmm1                               
  bc7b8f7  orps xmm7,xmm2                                
  bc7b8fa  movaps xmm0,xmm7                              
  bc7b8fd  call 0xEEC75A0                                ; -> sub_eec75a0
  bc7b902  movaps xmm9,xmm0                              
  bc7b906  cvttss2si rax,xmm0                            
  bc7b90b  mov rcx,rax                                   
  bc7b90e  sar rcx,0x3F                                  
  bc7b912  subss xmm0,xmm13                              
  bc7b917  cvttss2si rbx,xmm0                            
  bc7b91c  and rbx,rcx                                   
  bc7b91f  or rbx,rax                                    
  bc7b922  movaps xmm0,xmm7                              
  bc7b925  call 0xEEC73F0                                ; -> sub_eec73f0
  bc7b92a  cmp rbx,0x65                                  
  bc7b92e  jae 0xBC7BA55                                 ; -> loc_bc7ba55
  bc7b934  cvttss2si rax,xmm0                            
  bc7b939  mov rcx,rax                                   
  bc7b93c  subss xmm0,xmm13                              
  bc7b941  cvttss2si rdx,xmm0                            
  bc7b946  sar rcx,0x3F                                  
  bc7b94a  and rdx,rcx                                   
  bc7b94d  or rdx,rax                                    
  bc7b950  cmp rdx,0x65                                  
  bc7b954  jae 0xBC7BA55                                 ; -> loc_bc7ba55
  bc7b95a  subss xmm6,xmm8                               
  bc7b95f  movss xmm1,[0xEEC8060]                        ; [data_eec8060]
  bc7b967  movaps xmm0,xmm1                              
  bc7b96a  subss xmm0,xmm6                               
  bc7b96e  mulss xmm14,xmm6                              
  bc7b973  mulss xmm10,xmm0                              
  bc7b978  addss xmm10,xmm14                             
  bc7b97d  lea rax,[rbx+rbx*2]                           
  bc7b981  lea rcx,[0xF44AA20]                           ; [data_f44aa20]
  bc7b988  lea rdx,[rdx+rdx*2]                           
  bc7b98c  subss xmm7,xmm9                               
  bc7b991  movss xmm2,[rcx+rdx*4+8]                      
  bc7b997  mulss xmm2,xmm7                               
  bc7b99b  subss xmm1,xmm7                               
  bc7b99f  movss xmm3,[rcx+rax*4+8]                      
  bc7b9a5  mulss xmm3,xmm1                               
  bc7b9a9  addss xmm3,xmm2                               
  bc7b9ad  movss xmm2,[rdi+0xC]                          ; R a1+0xC
  bc7b9b2  addss xmm10,[0xF449710]                       ; [data_f449710]
  bc7b9bb  addss xmm10,xmm3                              
  bc7b9c0  addss xmm10,xmm2                              
  bc7b9c5  shufps xmm6,xmm6,0                            
  bc7b9c9  mulps xmm6,xmm12                              
  bc7b9cd  shufps xmm0,xmm0,0                            
  bc7b9d1  mulps xmm0,xmm11                              
  bc7b9d5  addps xmm0,xmm6                               
  bc7b9d8  movsd xmm3,[rcx+rdx*4]                        
  bc7b9dd  unpcklps xmm7,xmm7                            
  bc7b9e0  mulps xmm7,xmm3                               
  bc7b9e3  movsd xmm3,[rcx+rax*4]                        
  bc7b9e8  unpcklps xmm1,xmm1                            
  bc7b9eb  mulps xmm1,xmm3                               
  bc7b9ee  addps xmm1,xmm7                               
  bc7b9f1  addps xmm0,[0xF449720]                        ; [data_f449720]
  bc7b9f8  addps xmm0,xmm1                               
  bc7b9fb  unpcklps xmm2,xmm2                            
  bc7b9fe  addps xmm2,xmm0                               
  bc7ba01  movlps [rsi],xmm2                             ; W a0+0x0
  bc7ba04  movss [rsi+8],xmm10                           ; W a0+0x8
  bc7ba0a  mov rax,rsi                                   
  bc7ba0d  movaps xmm6,[rsp+0x20]                        
  bc7ba12  movaps xmm7,[rsp+0x30]                        
  bc7ba17  movaps xmm8,[rsp+0x40]                        
  bc7ba1d  movaps xmm9,[rsp+0x50]                        
  bc7ba23  movaps xmm10,[rsp+0x60]                       
  bc7ba29  movaps xmm11,[rsp+0x70]                       
  bc7ba2f  movaps xmm12,[rsp+0x80]                       
  bc7ba38  movaps xmm13,[rsp+0x90]                       
  bc7ba41  movaps xmm14,[rsp+0xA0]                       
  bc7ba4a  add rsp,0xB0                                  
  bc7ba51  pop rbx                                       
  bc7ba52  pop rdi                                       
  bc7ba53  pop rsi                                       
  bc7ba54  ret                                           

loc_bc7ba55:  ; from bc7b873, bc7b899, bc7b92e, bc7b954
  bc7ba55  call 0x78ED0                                  ; -> sub_78ed0
  bc7ba5a  int3                                          
  bc7ba5b  int3                                          
  bc7ba5c  int3                                          
  bc7ba5d  int3                                          
  bc7ba5e  int3                                          
  bc7ba5f  int3                                          
  bc7ba60  push rbp                                      
  bc7ba61  push r15                                      
  bc7ba63  push r14                                      
  bc7ba65  push r13                                      
  bc7ba67  push r12                                      
  bc7ba69  push rsi                                      
  bc7ba6a  push rdi                                      
  bc7ba6b  push rbx                                      
  bc7ba6c  sub rsp,0x158                                 
  bc7ba73  lea rbp,[rsp+0x80]                            
  bc7ba7b  mov qword ptr [rbp+0xD0],0xFFFFFFFFFFFFFFFE   
  bc7ba86  mov [rbp+0x88],r9                             
  bc7ba8d  mov r9,rdx                                    
  bc7ba90  mov rsi,rcx                                   
  bc7ba93  movzx eax,word ptr [r8+4]                     
  bc7ba98  mov ecx,[rdx]                                 
  bc7ba9a  mov r10d,[rdx+4]                              
  bc7ba9e  add eax,ecx                                   
  bc7baa0  dec eax                                       
  bc7baa2  cdq                                           
  bc7baa3  idiv ecx                                      
  bc7baa5  mov ecx,eax                                   
  bc7baa7  movzx eax,word ptr [r8+6]                     
  bc7baac  add eax,r10d                                  
  bc7baaf  dec eax                                       
  bc7bab1  cdq                                           
  bc7bab2  idiv r10d                                     
  bc7bab5  mov edx,[r9+8]                                
  bc7bab9  cmp byte ptr [rsi+0x20],1                     
  bc7babd  jne short 0xBC7BAEF                           ; -> loc_bc7baef
  bc7babf  cmp byte ptr [rsi+0x38],1                     
  bc7bac3  jne short 0xBC7BAEF                           ; -> loc_bc7baef
  bc7bac5  cmp byte ptr [rsi+0x50],1                     
  bc7bac9  jne short 0xBC7BAEF                           ; -> loc_bc7baef
  bc7bacb  cmp [rsi],ecx                                 
  bc7bacd  jne short 0xBC7BAEF                           ; -> loc_bc7baef
  bc7bacf  cmp [rsi+4],eax                               
  bc7bad2  jne short 0xBC7BAEF                           ; -> loc_bc7baef
  bc7bad4  cmp [rsi+8],edx                               
  bc7bad7  jne short 0xBC7BAEF                           ; -> loc_bc7baef
  bc7bad9  lea rcx,[rsi+0x28]                            
  bc7badd  lea rdx,[rsi+0x40]                            
  bc7bae1  call 0xBC7C4E0                                ; -> sub_bc7c4e0
  bc7bae6  mov byte ptr [rsi+0x58],1                     
  bc7baea  jmp 0xBC7C2DD                                 ; -> loc_bc7c2dd

loc_bc7baef:  ; from bc7babd, bc7bac3, bc7bac9, bc7bacd, bc7bad2, bc7bad7
  bc7baef  mov [rsi],ecx                                 
  bc7baf1  mov [rsi+4],eax                               
  bc7baf4  mov [rsi+8],edx                               
  bc7baf7  mov dword ptr [rbp+0xB],0                     
  bc7bafe  mov dword ptr [rbp+8],0                       
  bc7bb05  mov dword ptr [rbp+0x14],1                    
  bc7bb0c  lea r14,[rbp+0x18]                            
  bc7bb10  xorps xmm0,xmm0                               
  bc7bb13  movups [rbp+0x18],xmm0                        
  bc7bb17  mov qword ptr [rbp+0x28],0                    
  bc7bb1f  mov qword ptr [rbp+0x30],0xF                  
  bc7bb27  mov dword ptr [rbp+0x38],0                    
  bc7bb2e  mov byte ptr [rbp+0x3D],0                     
  bc7bb32  mov [rbp],ecx                                 
  bc7bb35  mov [rbp+4],eax                               
  bc7bb38  mov [rbp+0x10],edx                            
  bc7bb3b  mov dword ptr [rbp+8],0xA                     
  bc7bb42  lea r9,[0xF56EDF0]                            ; [data_f56edf0] "Scattering Buffer"
  bc7bb49  mov edx,0x11                                  
  bc7bb4e  mov rcx,r14                                   
  bc7bb51  call 0x9D6D0                                  ; -> sub_9d6d0
  bc7bb56  nop                                           
  bc7bb57  mov dword ptr [rbp+0x38],8                    
  bc7bb5e  lea rcx,[rbp+0x90]                            
  bc7bb65  mov rdx,rbp                                   
  bc7bb68  call 0xBC431B0                                ; -> sub_bc431b0
  bc7bb6d  nop                                           
  bc7bb6e  lea rdx,[rbp+0x40]                            
  bc7bb72  lea r8,[rbp+0x90]                             
  bc7bb79  mov rcx,[rbp+0x88]                            
  bc7bb80  call 0x56BD700                                ; -> sub_56bd700
  bc7bb85  nop                                           
  bc7bb86  mov rax,[rbp+0x40]                            
  bc7bb8a  mov rbx,[rbp+0x48]                            
  bc7bb8e  xorps xmm0,xmm0                               
  bc7bb91  movaps [rbp+0x40],xmm0                        
  bc7bb95  cmp byte ptr [rsi+0x20],1                     
  bc7bb99  jne short 0xBC7BBE4                           ; -> loc_bc7bbe4
  bc7bb9b  test rbx,rbx                                  
  bc7bb9e  je short 0xBC7BBA4                            ; -> loc_bc7bba4
  bc7bba0  lock inc dword ptr [rbx+8]                    

loc_bc7bba4:  ; from bc7bb9e
  bc7bba4  mov [rsi+0x10],rax                            
  bc7bba8  mov r15,[rsi+0x18]                            
  bc7bbac  mov [rsi+0x18],rbx                            
  bc7bbb0  test r15,r15                                  
  bc7bbb3  je short 0xBC7BC00                            ; -> loc_bc7bc00
  bc7bbb5  lock dec dword ptr [r15+8]                    
  bc7bbba  jne short 0xBC7BC00                           ; -> loc_bc7bc00
  bc7bbbc  mov rax,[r15]                                 
  bc7bbbf  mov rax,[rax]                                 
  bc7bbc2  mov rcx,r15                                   
  bc7bbc5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7bbcb  lock dec dword ptr [r15+0xC]                  
  bc7bbd0  jne short 0xBC7BC00                           ; -> loc_bc7bc00
  bc7bbd2  mov rax,[r15]                                 
  bc7bbd5  mov rax,[rax+8]                               
  bc7bbd9  mov rcx,r15                                   
  bc7bbdc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7bbe2  jmp short 0xBC7BC00                           ; -> loc_bc7bc00

loc_bc7bbe4:  ; from bc7bb99
  bc7bbe4  lea rcx,[rsi+0x10]                            
  bc7bbe8  movups [rcx],xmm0                             
  bc7bbeb  test rbx,rbx                                  
  bc7bbee  je short 0xBC7BBF4                            ; -> loc_bc7bbf4
  bc7bbf0  lock inc dword ptr [rbx+8]                    

loc_bc7bbf4:  ; from bc7bbee
  bc7bbf4  mov [rsi+0x10],rax                            
  bc7bbf8  mov [rsi+0x18],rbx                            
  bc7bbfc  mov byte ptr [rsi+0x20],1                     

loc_bc7bc00:  ; from bc7bbb3, bc7bbba, bc7bbd0, bc7bbe2
  bc7bc00  test rbx,rbx                                  
  bc7bc03  je short 0xBC7BC30                            ; -> loc_bc7bc30
  bc7bc05  lock dec dword ptr [rbx+8]                    
  bc7bc09  jne short 0xBC7BC30                           ; -> loc_bc7bc30
  bc7bc0b  mov rax,[rbx]                                 
  bc7bc0e  mov rax,[rax]                                 
  bc7bc11  mov rcx,rbx                                   
  bc7bc14  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7bc1a  lock dec dword ptr [rbx+0xC]                  
  bc7bc1e  jne short 0xBC7BC30                           ; -> loc_bc7bc30
  bc7bc20  mov rax,[rbx]                                 
  bc7bc23  mov rax,[rax+8]                               
  bc7bc27  mov rcx,rbx                                   
  bc7bc2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc7bc30:  ; from bc7bc03, bc7bc09, bc7bc1e
  bc7bc30  mov rbx,[rbp+0x48]                            
  bc7bc34  test rbx,rbx                                  
  bc7bc37  je short 0xBC7BC64                            ; -> loc_bc7bc64
  bc7bc39  lock dec dword ptr [rbx+8]                    
  bc7bc3d  jne short 0xBC7BC64                           ; -> loc_bc7bc64
  bc7bc3f  mov rax,[rbx]                                 
  bc7bc42  mov rax,[rax]                                 
  bc7bc45  mov rcx,rbx                                   
  bc7bc48  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7bc4e  lock dec dword ptr [rbx+0xC]                  
  bc7bc52  jne short 0xBC7BC64                           ; -> loc_bc7bc64
  bc7bc54  mov rax,[rbx]                                 
  bc7bc57  mov rax,[rax+8]                               
  bc7bc5b  mov rcx,rbx                                   
  bc7bc5e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc7bc64:  ; from bc7bc37, bc7bc3d, bc7bc52
  bc7bc64  mov rax,[rbp+0xC0]                            
  bc7bc6b  cmp rax,0x10                                  
  bc7bc6f  jb short 0xBC7BCA9                            ; -> loc_bc7bca9
  bc7bc71  mov rcx,[rbp+0xA8]                            
  bc7bc78  lea rdx,[rax+1]                               
  bc7bc7c  cmp rdx,0x1000                                
  bc7bc83  jb short 0xBC7BCA4                            ; -> loc_bc7bca4
  bc7bc85  mov r8,[rcx-8]                                
  bc7bc89  add rcx,0xFFFFFFFFFFFFFFF8                    
  bc7bc8d  sub rcx,r8                                    
  bc7bc90  cmp rcx,0x20                                  
  bc7bc94  jae 0xBC7C333                                 ; -> loc_bc7c333
  bc7bc9a  add rax,0x28                                  
  bc7bc9e  mov rdx,rax                                   
  bc7bca1  mov rcx,r8                                    

loc_bc7bca4:  ; from bc7bc83
  bc7bca4  call 0xE935700                                ; -> sub_e935700

loc_bc7bca9:  ; from bc7bc6f
  bc7bca9  mov rax,[rbp+0x10]                            
  bc7bcad  mov [rbp+0xA0],rax                            
  bc7bcb4  movups xmm0,[rbp]                             
  bc7bcb8  movaps [rbp+0x90],xmm0                        
  bc7bcbf  xorps xmm0,xmm0                               
  bc7bcc2  movups [rbp+0xA8],xmm0                        
  bc7bcc9  movups [rbp+0xB8],xmm0                        
  bc7bcd0  mov r15,[rbp+0x28]                            
  bc7bcd4  cmp qword ptr [rbp+0x30],0x10                 
  bc7bcd9  jb short 0xBC7BCDF                            ; -> loc_bc7bcdf
  bc7bcdb  mov r14,[rbp+0x18]                            

loc_bc7bcdf:  ; from bc7bcd9
  bc7bcdf  test r15,r15                                  
  bc7bce2  js 0xBC7C34D                                  ; -> loc_bc7c34d
  bc7bce8  lea r13,[rbp+0x38]                            
  bc7bcec  lea rbx,[rbp+0xA8]                            
  bc7bcf3  cmp r15,0xF                                   
  bc7bcf7  ja short 0xBC7BD3E                            ; -> loc_bc7bd3e
  bc7bcf9  mov [rbp+0xB8],r15                            
  bc7bd00  mov qword ptr [rbp+0xC0],0xF                  
  bc7bd0b  movups xmm0,[r14]                             
  bc7bd0f  movups [rbx],xmm0                             
  bc7bd12  lea rdi,[rbp+0xC8]                            
  bc7bd19  movzx eax,word ptr [r13+4]                    
  bc7bd1e  mov [rbp+0xCC],ax                             
  bc7bd25  mov eax,[r13]                                 
  bc7bd29  mov [rbp+0xC8],eax                            
  bc7bd2f  mov dword ptr [rbp+0x98],0x29                 
  bc7bd39  jmp 0xBC7BE00                                 ; -> loc_bc7be00

loc_bc7bd3e:  ; from bc7bcf7
  bc7bd3e  mov rdx,r15                                   
  bc7bd41  or rdx,0xF                                    
  bc7bd45  cmp rdx,0x17                                  
  bc7bd49  mov edi,0x16                                  
  bc7bd4e  cmovae rdi,rdx                                
  bc7bd52  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bc7bd59  mov rax,[rcx]                                 
  bc7bd5c  mov rax,[rax+8]                               
  bc7bd60  cmp rdx,0xFFF                                 
  bc7bd67  jb short 0xBC7BD92                            ; -> loc_bc7bd92
  bc7bd69  lea rdx,[rdi+0x28]                            
  bc7bd6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7bd73  nop                                           
  bc7bd74  mov r12,rax                                   
  bc7bd77  test rax,rax                                  
  bc7bd7a  je 0xBC7C2F1                                  ; -> loc_bc7c2f1

loc_bc7bd80:  ; from bc7c2fb
  bc7bd80  mov rax,r12                                   
  bc7bd83  add r12,0x27                                  
  bc7bd87  and r12,0xFFFFFFFFFFFFFFE0                    
  bc7bd8b  mov [r12-8],rax                               
  bc7bd90  jmp short 0xBC7BDA9                           ; -> loc_bc7bda9

loc_bc7bd92:  ; from bc7bd67
  bc7bd92  lea rdx,[rdi+1]                               
  bc7bd96  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7bd9c  nop                                           
  bc7bd9d  mov r12,rax                                   
  bc7bda0  test rax,rax                                  
  bc7bda3  je 0xBC7C300                                  ; -> loc_bc7c300

loc_bc7bda9:  ; from bc7bd90, bc7c30d
  bc7bda9  mov [rbp+0xA8],r12                            
  bc7bdb0  mov [rbp+0xB8],r15                            
  bc7bdb7  mov [rbp+0xC0],rdi                            
  bc7bdbe  inc r15                                       
  bc7bdc1  mov rcx,r12                                   
  bc7bdc4  mov rdx,r14                                   
  bc7bdc7  mov r8,r15                                    
  bc7bdca  call 0xEEC6EC0                                ; -> sub_eec6ec0
  bc7bdcf  cmp qword ptr [rbp+0xC0],0x18                 
  bc7bdd7  lea rdi,[rbp+0xC8]                            
  bc7bdde  mov eax,[r13]                                 
  bc7bde2  mov [rbp+0xC8],eax                            
  bc7bde8  movzx eax,word ptr [r13+4]                    
  bc7bded  mov [rbp+0xCC],ax                             
  bc7bdf4  mov dword ptr [rbp+0x98],0x29                 
  bc7bdfe  jae short 0xBC7BE17                           ; -> loc_bc7be17

loc_bc7be00:  ; from bc7bd39
  bc7be00  lea r9,[0xF7E3FFE]                            ; [data_f7e3ffe] "Cascaded Shadow Buffer 1"
  bc7be07  mov edx,0x18                                  
  bc7be0c  mov rcx,rbx                                   
  bc7be0f  call 0x9D6D0                                  ; -> sub_9d6d0
  bc7be14  nop                                           
  bc7be15  jmp short 0xBC7BE45                           ; -> loc_bc7be45

loc_bc7be17:  ; from bc7bdfe
  bc7be17  mov rax,[rbp+0xA8]                            
  bc7be1e  mov qword ptr [rbp+0xB8],0x18                 
  bc7be29  movups xmm0,[0xF7E3FFE]                       ; [data_f7e3ffe] "Cascaded Shadow Buffer 1"
  bc7be30  movups [rax],xmm0                             
  bc7be33  mov rcx,0x3120726566667542                    
  bc7be3d  mov [rax+0x10],rcx                            
  bc7be41  mov byte ptr [rax+0x18],0                     

loc_bc7be45:  ; from bc7be15
  bc7be45  lea rcx,[rbp+0x40]                            
  bc7be49  lea rdx,[rbp+0x90]                            
  bc7be50  call 0xBC431B0                                ; -> sub_bc431b0
  bc7be55  nop                                           
  bc7be56  lea rdx,[rbp-0x50]                            
  bc7be5a  lea r8,[rbp+0x40]                             
  bc7be5e  mov rcx,[rbp+0x88]                            
  bc7be65  call 0x56BD700                                ; -> sub_56bd700
  bc7be6a  nop                                           
  bc7be6b  mov rax,[rbp-0x50]                            
  bc7be6f  mov r14,[rbp-0x48]                            
  bc7be73  xorps xmm0,xmm0                               
  bc7be76  movaps [rbp-0x50],xmm0                        
  bc7be7a  cmp byte ptr [rsi+0x38],1                     
  ... (--max 400)
```

## CALLERS
```
  0x55f1450 sub_55f1450 size 0x4e144
  0xbb6a1a0 sub_bb6a1a0 size 0x84a
  -- 2 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0x78ed0     sub_78ed0         unknown     [open]     [proven]  boundary=crt
  0xeec73f0   sub_eec73f0       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_eec73f0.cpp;src\client\features\render\native\helpers\sub_eec73f0.h
  0xeec75a0   sub_eec75a0       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_eec75a0.cpp;src\client\features\render\native\helpers\sub_eec75a0.h

## STRINGS AND RIP REFS
  (none)

## FIELD ACCESS TABLE (descscan2, regs rdi,rsi,r9,r15)
  (no [reg+off] description reads detected; register unknown -> [open])

## KNOWN STRUCT LAYOUTS TOUCHED
  (none detected)

## CLOSEST FINISHED LIFT (style example, same size band + call shape)
  e81d850.md  size 0x1cd  callees~72  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\e81d850.md

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

