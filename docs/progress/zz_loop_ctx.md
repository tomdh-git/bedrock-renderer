  562b471  call 0xE935700                                ; -> sub_e935700

loc_562b476:  ; from 562b43c
  562b476  mov qword ptr [rbp+0x2C10],0                  
  562b481  mov qword ptr [rbp+0x2C18],0xF                
  562b48c  mov byte ptr [rbp+0x2C00],0                   
  562b493  mov rax,[rbp+0x2608]                          
  562b49a  cmp rax,0x10                                  
  562b49e  jb short 0x562B4D8                            ; -> loc_562b4d8
  562b4a0  mov rcx,[rbp+0x25F0]                          
  562b4a7  lea rdx,[rax+1]                               
  562b4ab  cmp rdx,0x1000                                
  562b4b2  jb short 0x562B4D3                            ; -> loc_562b4d3
  562b4b4  mov r8,[rcx-8]                                
  562b4b8  add rcx,0xFFFFFFFFFFFFFFF8                    
  562b4bc  sub rcx,r8                                    
  562b4bf  cmp rcx,0x20                                  
  562b4c3  jae 0x563E938                                 ; -> loc_563e938
  562b4c9  add rax,0x28                                  
  562b4cd  mov rdx,rax                                   
  562b4d0  mov rcx,r8                                    

loc_562b4d3:  ; from 562b4b2
  562b4d3  call 0xE935700                                ; -> sub_e935700

loc_562b4d8:  ; from 562b49e
  562b4d8  mov rax,[rbp+0x3128]                          
  562b4df  cmp rax,0x10                                  
  562b4e3  jb short 0x562B51D                            ; -> loc_562b51d
  562b4e5  mov rcx,[rbp+0x3110]                          
  562b4ec  lea rdx,[rax+1]                               
  562b4f0  cmp rdx,0x1000                                
  562b4f7  jb short 0x562B518                            ; -> loc_562b518
  562b4f9  mov r8,[rcx-8]                                
  562b4fd  add rcx,0xFFFFFFFFFFFFFFF8                    
  562b501  sub rcx,r8                                    
  562b504  cmp rcx,0x20                                  
  562b508  jae 0x563E938                                 ; -> loc_563e938
  562b50e  add rax,0x28                                  
  562b512  mov rdx,rax                                   
  562b515  mov rcx,r8                                    

loc_562b518:  ; from 562b4f7
  562b518  call 0xE935700                                ; -> sub_e935700

loc_562b51d:  ; from 562b4e3
  562b51d  mov qword ptr [rbp+0x3120],0                  
  562b528  mov qword ptr [rbp+0x3128],0xF                
  562b533  mov byte ptr [rbp+0x3110],0                   
  562b53a  cmp byte ptr [rbp+0x2F50],1                   
  562b541  jne 0x562A274                                 ; -> loc_562a274
  562b547  cmp qword ptr [rbp+0x2F38],0                  
  562b54f  je 0x562A274                                  ; -> loc_562a274
  562b555  lea rax,[rbp+0x3108]                          
  562b55c  movdqu [rax-0x1D0],xmm15                      
  562b565  mov qword ptr [rax-0x1C0],0                   
  562b570  jmp 0x562A274                                 ; -> loc_562a274

loc_562b575:  ; from 562a744
  562b575  mov rcx,r14                                   
  562b578  call 0x9BC830                                 ; -> sub_9bc830
  562b57d  nop                                           
  562b57e  jmp 0x562A74A                                 ; -> loc_562a74a

loc_562b583:  ; from 562a770
  562b583  mov rcx,r14                                   
  562b586  call 0x9BC830                                 ; -> sub_9bc830
  562b58b  nop                                           
  562b58c  xor r12d,r12d                                 
  562b58f  jmp 0x562A776                                 ; -> loc_562a776

loc_562b594:  ; from 562a292
  562b594  mov rax,[rbp+0x31A0]                          
  562b59b  cmp rax,0x10                                  
  562b59f  jb 0x562A0C4                                  ; -> loc_562a0c4
  562b5a5  mov rcx,[rbp+0x3188]                          
  562b5ac  lea rdx,[rax+1]                               
  562b5b0  cmp rdx,0x1000                                
  562b5b7  jb short 0x562B5D8                            ; -> loc_562b5d8
  562b5b9  mov r8,[rcx-8]                                
  562b5bd  add rcx,0xFFFFFFFFFFFFFFF8                    
  562b5c1  sub rcx,r8                                    
  562b5c4  cmp rcx,0x20                                  
  562b5c8  jae 0x563E938                                 ; -> loc_563e938
  562b5ce  add rax,0x28                                  
  562b5d2  mov rdx,rax                                   
  562b5d5  mov rcx,r8                                    

loc_562b5d8:  ; from 562b5b7
  562b5d8  call 0xE935700                                ; -> sub_e935700
  562b5dd  add r15,0x290                                 
  562b5e4  cmp r15,[rbp+0x3250]                          
  562b5eb  jne 0x562A0D8                                 ; -> loc_562a0d8
  562b5f1  jmp 0x56270E9                                 ; -> loc_56270e9

loc_562b5f6:  ; from 562a124
  562b5f6  mov rcx,[rbp+0x2688]                          
  562b5fd  test rcx,rcx                                  
  562b600  je 0x562A0C4                                  ; -> loc_562a0c4
  562b606  mov rax,[rcx]                                 
  562b609  lea rdx,[rbp+0x2650]                          
  562b610  cmp rcx,rdx                                   
  562b613  setne dl                                      
  562b616  mov rax,[rax+0x20]                            
  562b61a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  562b620  jmp 0x562A0C4                                 ; -> loc_562a0c4

loc_562b625:  ; from 562754e, 562755c
  562b625  mov r15,[rbp+0x1FD8]                          
  562b62c  mov r12,[rbp+0x1FF8]                          
  562b633  jmp 0x562CB23                                 ; -> loc_562cb23

loc_562b638:  ; from 5627586
  562b638  xor eax,eax                                   

loc_562b63a:  ; from 5627597
  562b63a  mov rcx,[rbp+0x2300]                          
  562b641  mov [rbp+0x2108],rcx                          
  562b648  mov [rbp+0x2110],rax                          
  562b64f  lea rax,[rbp+0x2108]                          
  562b656  movdqu [rax+0x10],xmm15                       
  562b65c  mov qword ptr [rax+0x20],0                    
  562b664  mov byte ptr [rbp+0x2130],1                   
  562b66b  mov rax,[0x129C9888]                          ; [data_129c9888]
  562b672  mov [rbp+0x2EF0],rax                          
  562b679  mov byte ptr [rbp+0x2EF8],0                   
  562b680  movdqa [rbp+0x27A0],xmm15                     
  562b689  mov qword ptr [rbp+0x2C00],1                  
  562b694  lea rax,[rbp+0x27A0]                          
  562b69b  mov [rbp+0x2C08],rax                          
  562b6a2  lea rcx,[rbp+0x2100]                          
  562b6a9  lea rdx,[rbp+0x2EF0]                          
  562b6b0  lea r8,[rbp+0x2C00]                           
  562b6b7  call 0x567B570                                ; -> sub_567b570
  562b6bc  nop                                           
  562b6bd  xorps xmm0,xmm0                               
  562b6c0  mov rax,[rbp+0x3258]                          
  562b6c7  cmp byte ptr [rax+0x382],1                    
  562b6ce  jne short 0x562B6E5                           ; -> loc_562b6e5
  562b6d0  movss xmm1,[rax+0x378]                        
  562b6d8  ucomiss xmm1,xmm0                             
  562b6db  jbe short 0x562B6E5                           ; -> loc_562b6e5
  562b6dd  movss xmm0,[0xEEC8060]                        ; [data_eec8060]

loc_562b6e5:  ; from 562b6ce, 562b6db
  562b6e5  xorps xmm1,xmm1                               
  562b6e8  cvtsi2ss xmm1,dword ptr [rax+0x2D4]           
  562b6f0  mov rax,[0x129C9878]                          ; [data_129c9878]
  562b6f7  mov [rbp+0x2EF0],rax                          
  562b6fe  mov byte ptr [rbp+0x2EF8],0                   
  562b705  movss [rbp+0x27A0],xmm1                       
  562b70d  movss [rbp+0x27A4],xmm0                       
  562b715  mov qword ptr [rbp+0x27A8],0                  
  562b720  mov qword ptr [rbp+0x2C00],1                  
  562b72b  lea rax,[rbp+0x27A0]                          
  562b732  mov [rbp+0x2C08],rax                          
  562b739  lea rcx,[rbp+0x2100]                          
  562b740  lea rdx,[rbp+0x2EF0]                          
  562b747  lea r8,[rbp+0x2C00]                           
  562b74e  call 0x567B570                                ; -> sub_567b570
  562b753  nop                                           
  562b754  mov eax,[0x129C9D78]                          ; [data_129c9d78]
  562b75a  mov ecx,[0x128767C8]                          ; [data_128767c8]
  562b760  mov rdx,gs:[0x58]                             
  562b769  mov rcx,[rdx+rcx*8]                           
  562b76d  cmp eax,[rcx+4]                               
  562b773  jg 0x563D361                                  ; -> loc_563d361

loc_562b779:  ; from 563d374, 563dab1
  562b779  mov rax,[0x129C9D70]                          ; [data_129c9d70]
  562b780  mov [rbp+0x2EF0],rax                          
  562b787  mov byte ptr [rbp+0x2EF8],0                   
  562b78e  movdqa [rbp+0x27A0],xmm15                     
  562b797  mov qword ptr [rbp+0x2C00],1                  
  562b7a2  lea rax,[rbp+0x27A0]                          
