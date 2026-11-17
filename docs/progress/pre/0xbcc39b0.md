# preflight 0xbcc39b0

## fn
```
sub_bcc39b0  [0xbcc39b0..0xbcc3b81)  size 0x1d1  3 xrefs in
  bcc39b0  push r15                                      
  bcc39b2  push r14                                      
  bcc39b4  push rsi                                      
  bcc39b5  push rdi                                      
  bcc39b6  push rbp                                      
  bcc39b7  push rbx                                      
  bcc39b8  sub rsp,0x48                                  
  bcc39bc  mov ebp,[rsp+0xB0]                            
  bcc39c3  mov rax,[rsp+0xA0]                            
  bcc39cb  movzx r10d,byte ptr [r9+0x40]                 ; R a3+0x40
  bcc39d0  cmp r10d,1                                    
  bcc39d4  jg 0xBCC3ADA                                  ; -> loc_bcc3ada
  bcc39da  test r10d,r10d                                
  bcc39dd  jne 0xBCC3B16                                 ; -> loc_bcc3b16
  bcc39e3  mov rbx,rcx                                   
  bcc39e6  mov rdi,r9                                    
  bcc39e9  mov r15d,edx                                  
  bcc39ec  mov esi,r8d                                   
  bcc39ef  mov r8,[rsp+0xA8]                             
  bcc39f7  lea rdx,[rsp+0x30]                            
  bcc39fc  mov rcx,rax                                   
  bcc39ff  call 0xBCC7CE0                                ; -> sub_bcc7ce0
  bcc3a04  cmp byte ptr [rsp+0x40],1                     
  bcc3a09  jne 0xBCC3B62                                 ; -> loc_bcc3b62
  bcc3a0f  xor eax,eax                                   
  bcc3a11  cmp byte ptr [rsp+0x32],1                     
  bcc3a16  jne 0xBCC3B64                                 ; -> loc_bcc3b64
  bcc3a1c  cmp word ptr [rsp+0x30],0xFFFF                
  bcc3a22  je 0xBCC3B64                                  ; -> loc_bcc3b64
  bcc3a28  mov rax,[rbx]                                 ; R a0+0x0
  bcc3a2b  mov rbx,[rax+0x10]                            ; R *(a0+0x0)+0x10
  bcc3a2f  mov rcx,[rbx]                                 ; R *(*(a0+0x0)+0x10)+0x0
  bcc3a32  mov eax,[rcx+0xD457C0]                        ; R *(*(*(a0+0x0)+0x10)+0x0)+0xD457C0
  bcc3a38  mov edx,0xFFFF                                
  bcc3a3d  nop [rax]                                     ; R *(*(*(*(a0+0x0)+0x10)+0x0)+0xD457C0)+0x0

loc_bcc3a40:  ; from bcc3a70
  bcc3a40  mov r14d,eax                                  
  bcc3a43  lea r8d,[r14+1]                               ; R *(*(*(*(a0+0x0)+0x10)+0x0)+0xD457C0)+0x1
  bcc3a47  cmp r8d,0xFFFF                                
  bcc3a4e  cmovae r8d,edx                                
  bcc3a52  cmp eax,0xFFFF                                
  ... (--max 40)

```

## callers
```
  sub_bc2f4a0                  1 call site(s)
  sub_bc36140                  1 call site(s)
  sub_bc82400                  1 call site(s)
-- 3 calling function(s)

```

## callees
```
sub_bcc39b0  [0xbcc39b0..0xbcc3b81)
  call sub_78ed0                    x1
  call sub_1a2800                   x1
  call sub_b432e0                   x1
  call sub_bc60740                  x1
  call sub_bcc3fa0                  x1
  call sub_bcc4150                  x1
  call sub_bcc7ce0                  x1
  call sub_ebce390                  x1

```

## stores into [reg+off] (non-stack)
```
  bcc3a9d  mov [rbx+0x7C],r14d                           ; W *(*(a0+0x0)+0x10)+0x7C
  bcc3aa1  mov word ptr [rbx+0x9E],1                     ; W *(*(a0+0x0)+0x10)+0x9E
  bcc3c8d  mov [r14+0x7C],r15d                           
  bcc3c91  mov word ptr [r14+0x9E],1                     
  bcc3f2d  mov [r14+0x7C],r15d                           
  bcc3f31  mov word ptr [r14+0x9E],1                     
  bcc40aa  mov [rsi+0x7C],edi                            
  bcc40ad  mov word ptr [rsi+0x9E],1                     
  bcc40bf  mov [rsi+0x94],r12d                           
  bcc4235  mov [r15+0x7C],r12d                           
  bcc4239  mov word ptr [r15+0x9E],1                     
```

## listing (600 instr)
```
sub_bcc39b0  [0xbcc39b0..0xbcc59b0)  size 0x2000  3 xrefs in
  bcc39b0  push r15                                      
  bcc39b2  push r14                                      
  bcc39b4  push rsi                                      
  bcc39b5  push rdi                                      
  bcc39b6  push rbp                                      
  bcc39b7  push rbx                                      
  bcc39b8  sub rsp,0x48                                  
  bcc39bc  mov ebp,[rsp+0xB0]                            
  bcc39c3  mov rax,[rsp+0xA0]                            
  bcc39cb  movzx r10d,byte ptr [r9+0x40]                 ; R a3+0x40
  bcc39d0  cmp r10d,1                                    
  bcc39d4  jg 0xBCC3ADA                                  ; -> loc_bcc3ada
  bcc39da  test r10d,r10d                                
  bcc39dd  jne 0xBCC3B16                                 ; -> loc_bcc3b16
  bcc39e3  mov rbx,rcx                                   
  bcc39e6  mov rdi,r9                                    
  bcc39e9  mov r15d,edx                                  
  bcc39ec  mov esi,r8d                                   
  bcc39ef  mov r8,[rsp+0xA8]                             
  bcc39f7  lea rdx,[rsp+0x30]                            
  bcc39fc  mov rcx,rax                                   
  bcc39ff  call 0xBCC7CE0                                ; -> sub_bcc7ce0
  bcc3a04  cmp byte ptr [rsp+0x40],1                     
  bcc3a09  jne 0xBCC3B62                                 ; -> loc_bcc3b62
  bcc3a0f  xor eax,eax                                   
  bcc3a11  cmp byte ptr [rsp+0x32],1                     
  bcc3a16  jne 0xBCC3B64                                 ; -> loc_bcc3b64
  bcc3a1c  cmp word ptr [rsp+0x30],0xFFFF                
  bcc3a22  je 0xBCC3B64                                  ; -> loc_bcc3b64
  bcc3a28  mov rax,[rbx]                                 ; R a0+0x0
  bcc3a2b  mov rbx,[rax+0x10]                            ; R *(a0+0x0)+0x10
  bcc3a2f  mov rcx,[rbx]                                 ; R *(*(a0+0x0)+0x10)+0x0
  bcc3a32  mov eax,[rcx+0xD457C0]                        ; R *(*(*(a0+0x0)+0x10)+0x0)+0xD457C0
  bcc3a38  mov edx,0xFFFF                                
  bcc3a3d  nop [rax]                                     ; R *(*(*(*(a0+0x0)+0x10)+0x0)+0xD457C0)+0x0

loc_bcc3a40:  ; from bcc3a70
  bcc3a40  mov r14d,eax                                  
  bcc3a43  lea r8d,[r14+1]                               ; R *(*(*(*(a0+0x0)+0x10)+0x0)+0xD457C0)+0x1
  bcc3a47  cmp r8d,0xFFFF                                
  bcc3a4e  cmovae r8d,edx                                
  bcc3a52  cmp eax,0xFFFF                                
  bcc3a57  cmovae r8d,edx                                
  bcc3a5b  lock cmpxchg [rcx+0xD457C0],r8d               ; R *(*(*(a0+0x0)+0x10)+0x0)+0xD457C0
  bcc3a64  cmp r14d,0xFFFF                               
  bcc3a6b  je short 0xBCC3A72                            ; -> loc_bcc3a72
  bcc3a6d  cmp r14d,eax                                  
  bcc3a70  jne short 0xBCC3A40                           ; -> loc_bcc3a40

loc_bcc3a72:  ; from bcc3a6b
  bcc3a72  xor r8d,r8d                                   
  bcc3a75  cmp r14d,0xFFFF                               
  bcc3a7c  setne r8b                                     
  bcc3a80  shl r8d,6                                     
  bcc3a84  mov eax,r14d                                  
  bcc3a87  shl rax,6                                     
  bcc3a8b  add rcx,rax                                   
  bcc3a8e  add rcx,0x9457C0                              
  bcc3a95  mov rdx,rdi                                   
  bcc3a98  call 0xEBCE390                                ; -> sub_ebce390
  bcc3a9d  mov [rbx+0x7C],r14d                           ; W *(*(a0+0x0)+0x10)+0x7C
  bcc3aa1  mov word ptr [rbx+0x9E],1                     ; W *(*(a0+0x0)+0x10)+0x9E
  bcc3aaa  cmp byte ptr [rsp+0x32],0                     
  bcc3aaf  je 0xBCC3B7B                                  ; -> loc_bcc3b7b
  bcc3ab5  movzx r8d,word ptr [rsp+0x30]                 
  bcc3abb  mov [rsp+0x28],r15b                           
  bcc3ac0  mov [rsp+0x20],ebp                            
  bcc3ac4  mov rcx,rbx                                   
  bcc3ac7  mov edx,esi                                   
  bcc3ac9  mov r9w,0xFFFF                                
  bcc3ace  call 0xBC60740                                ; -> sub_bc60740
  bcc3ad3  mov al,1                                      
  bcc3ad5  jmp 0xBCC3B64                                 ; -> loc_bcc3b64

loc_bcc3ada:  ; from bcc39d4
  bcc3ada  cmp r10d,2                                    
  bcc3ade  jne 0xBCC3B76                                 ; -> loc_bcc3b76
  bcc3ae4  cmp byte ptr [rax+0xF8],1                     
  bcc3aeb  jne short 0xBCC3B62                           ; -> loc_bcc3b62
  bcc3aed  mov r9,[r9]                                   
  bcc3af0  movups xmm0,[rax+0xE8]                        
  bcc3af7  movaps [rsp+0x30],xmm0                        
  bcc3afc  mov byte ptr [rsp+0x40],1                     
  bcc3b01  mov [rsp+0x28],ebp                            
  bcc3b05  lea rax,[rsp+0x30]                            
  bcc3b0a  mov [rsp+0x20],rax                            
  bcc3b0f  call 0xBCC3FA0                                ; -> sub_bcc3fa0
  bcc3b14  jmp short 0xBCC3B60                           ; -> loc_bcc3b60

loc_bcc3b16:  ; from bcc39dd
  bcc3b16  mov r10,[r9]                                  
  bcc3b19  mov r9,[r9+8]                                 
  bcc3b1d  mov r11,r9                                    
  bcc3b20  sub r11,r10                                   
  bcc3b23  mov rsi,r11                                   
  bcc3b26  sar rsi,6                                     
  bcc3b2a  mov [rsp+0x30],rsi                            
  bcc3b2f  cmp r11,0xFFFFFFFFFFFFFFC0                    
  bcc3b33  je short 0xBCC3B71                            ; -> loc_bcc3b71
  bcc3b35  mov [rsp+0x38],r10                            
  bcc3b3a  test r10,r10                                  
  bcc3b3d  setne r10b                                    
  bcc3b41  test r9,r9                                    
  bcc3b44  sete r9b                                      
  bcc3b48  or r9b,r10b                                   
  bcc3b4b  je short 0xBCC3B71                            ; -> loc_bcc3b71
  bcc3b4d  mov [rsp+0x28],ebp                            
  bcc3b51  mov [rsp+0x20],rax                            
  bcc3b56  lea r9,[rsp+0x30]                             
  bcc3b5b  call 0xBCC4150                                ; -> sub_bcc4150

loc_bcc3b60:  ; from bcc3b14
  bcc3b60  jmp short 0xBCC3B64                           ; -> loc_bcc3b64

loc_bcc3b62:  ; from bcc3a09, bcc3aeb
  bcc3b62  xor eax,eax                                   

loc_bcc3b64:  ; from bcc3a16, bcc3a22, bcc3ad5, bcc3b60
  bcc3b64  add rsp,0x48                                  
  bcc3b68  pop rbx                                       
  bcc3b69  pop rbp                                       
  bcc3b6a  pop rdi                                       
  bcc3b6b  pop rsi                                       
  bcc3b6c  pop r14                                       
  bcc3b6e  pop r15                                       
  bcc3b70  ret                                           

loc_bcc3b71:  ; from bcc3b33, bcc3b4b
  bcc3b71  call 0x78ED0                                  ; -> sub_78ed0

loc_bcc3b76:  ; from bcc3ade
  bcc3b76  call 0xB432E0                                 ; -> sub_b432e0

loc_bcc3b7b:  ; from bcc3aaf
  bcc3b7b  call 0x1A2800                                 ; -> sub_1a2800
  bcc3b80  int3                                          
  bcc3b81  int3                                          
  bcc3b82  int3                                          
  bcc3b83  int3                                          
  bcc3b84  int3                                          
  bcc3b85  int3                                          
  bcc3b86  int3                                          
  bcc3b87  int3                                          
  bcc3b88  int3                                          
  bcc3b89  int3                                          
  bcc3b8a  int3                                          
  bcc3b8b  int3                                          
  bcc3b8c  int3                                          
  bcc3b8d  int3                                          
  bcc3b8e  int3                                          
  bcc3b8f  int3                                          
  bcc3b90  push rbp                                      
  bcc3b91  push r15                                      
  bcc3b93  push r14                                      
  bcc3b95  push r12                                      
  bcc3b97  push rsi                                      
  bcc3b98  push rdi                                      
  bcc3b99  push rbx                                      
  bcc3b9a  sub rsp,0x60                                  
  bcc3b9e  lea rbp,[rsp+0x60]                            
  bcc3ba3  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE      
  bcc3bab  mov rdi,r9                                    
  bcc3bae  mov esi,r8d                                   
  bcc3bb1  mov ebx,edx                                   
  bcc3bb3  mov r14,rcx                                   
  bcc3bb6  mov eax,[0x12AE2880]                          ; [data_12ae2880]
  bcc3bbc  mov ecx,[0x128767C8]                          ; [data_128767c8]
  bcc3bc2  mov rdx,gs:[0x58]                             
  bcc3bcb  mov rcx,[rdx+rcx*8]                           
  bcc3bcf  cmp eax,[rcx+4]                               
  bcc3bd5  jg 0xBCC3CD7                                  ; -> loc_bcc3cd7

loc_bcc3bdb:  ; from bcc3cea, bcc3d24
  bcc3bdb  mov rcx,[rbp+0x60]                            
  bcc3bdf  lea r8,[0x12AE2840]                           ; [data_12ae2840]
  bcc3be6  lea rdx,[rbp-0x28]                            
  bcc3bea  call 0xBCC7CE0                                ; -> sub_bcc7ce0
  bcc3bef  cmp byte ptr [rbp-0x18],1                     
  bcc3bf3  jne 0xBCC3CC6                                 ; -> loc_bcc3cc6
  bcc3bf9  xor eax,eax                                   
  bcc3bfb  cmp byte ptr [rbp-0x26],1                     
  bcc3bff  jne 0xBCC3CC8                                 ; -> loc_bcc3cc8
  bcc3c05  cmp word ptr [rbp-0x28],0xFFFF                
  bcc3c0a  je 0xBCC3CC8                                  ; -> loc_bcc3cc8
  bcc3c10  mov r12d,[rbp+0x68]                           
  bcc3c14  mov rax,[r14]                                 
  bcc3c17  mov r14,[rax+0x10]                            
  bcc3c1b  mov rcx,[r14]                                 
  bcc3c1e  mov eax,[rcx+0xD457C0]                        
  bcc3c24  mov edx,0xFFFF                                
  bcc3c29  nop [rax]                                     

loc_bcc3c30:  ; from bcc3c60
  bcc3c30  mov r15d,eax                                  
  bcc3c33  lea r8d,[r15+1]                               
  bcc3c37  cmp r8d,0xFFFF                                
  bcc3c3e  cmovae r8d,edx                                
  bcc3c42  cmp eax,0xFFFF                                
  bcc3c47  cmovae r8d,edx                                
  bcc3c4b  lock cmpxchg [rcx+0xD457C0],r8d               
  bcc3c54  cmp r15d,0xFFFF                               
  bcc3c5b  je short 0xBCC3C62                            ; -> loc_bcc3c62
  bcc3c5d  cmp r15d,eax                                  
  bcc3c60  jne short 0xBCC3C30                           ; -> loc_bcc3c30

loc_bcc3c62:  ; from bcc3c5b
  bcc3c62  xor r8d,r8d                                   
  bcc3c65  cmp r15d,0xFFFF                               
  bcc3c6c  setne r8b                                     
  bcc3c70  shl r8d,6                                     
  bcc3c74  mov eax,r15d                                  
  bcc3c77  shl rax,6                                     
  bcc3c7b  add rcx,rax                                   
  bcc3c7e  add rcx,0x9457C0                              
  bcc3c85  mov rdx,rdi                                   
  bcc3c88  call 0xEBCE390                                ; -> sub_ebce390
  bcc3c8d  mov [r14+0x7C],r15d                           
  bcc3c91  mov word ptr [r14+0x9E],1                     
  bcc3c9b  cmp byte ptr [rbp-0x26],0                     
  bcc3c9f  je 0xBCC3D29                                  ; -> loc_bcc3d29
  bcc3ca5  movzx r8d,word ptr [rbp-0x28]                 
  bcc3caa  mov [rsp+0x28],bl                             
  bcc3cae  mov [rsp+0x20],r12d                           
  bcc3cb3  mov rcx,r14                                   
  bcc3cb6  mov edx,esi                                   
  bcc3cb8  mov r9w,0xFFFF                                
  bcc3cbd  call 0xBC60740                                ; -> sub_bc60740
  bcc3cc2  mov al,1                                      
  bcc3cc4  jmp short 0xBCC3CC8                           ; -> loc_bcc3cc8

loc_bcc3cc6:  ; from bcc3bf3
  bcc3cc6  xor eax,eax                                   

loc_bcc3cc8:  ; from bcc3bff, bcc3c0a, bcc3cc4
  bcc3cc8  add rsp,0x60                                  
  bcc3ccc  pop rbx                                       
  bcc3ccd  pop rdi                                       
  bcc3cce  pop rsi                                       
  bcc3ccf  pop r12                                       
  bcc3cd1  pop r14                                       
  bcc3cd3  pop r15                                       
  bcc3cd5  pop rbp                                       
  bcc3cd6  ret                                           

loc_bcc3cd7:  ; from bcc3bd5
  bcc3cd7  lea rcx,[0x12AE2880]                          ; [data_12ae2880]
  bcc3cde  call 0xE938CB0                                ; -> sub_e938cb0
  bcc3ce3  cmp dword ptr [0x12AE2880],0xFFFFFFFF         ; [data_12ae2880]
  bcc3cea  jne 0xBCC3BDB                                 ; -> loc_bcc3bdb
  bcc3cf0  mov dword ptr [rbp-0x28],0                    
  bcc3cf7  lea rcx,[0x12AE2840]                          ; [data_12ae2840]
  bcc3cfe  lea rdx,[rbp-0x28]                            
  bcc3d02  lea r8,[rbp-9]                                
  bcc3d06  call 0x9B020                                  ; -> sub_9b020
  bcc3d0b  nop                                           
  bcc3d0c  lea rcx,[0xBCC3D70]                           ; [sub_bcc3d70]
  bcc3d13  call 0xE935740                                ; -> sub_e935740
  bcc3d18  lea rcx,[0x12AE2880]                          ; [data_12ae2880]
  bcc3d1f  call 0xE938D70                                ; -> sub_e938d70
  bcc3d24  jmp 0xBCC3BDB                                 ; -> loc_bcc3bdb

loc_bcc3d29:  ; from bcc3c9f
  bcc3d29  call 0x1A2800                                 ; -> sub_1a2800
  bcc3d2e  int3                                          
  bcc3d2f  nop                                           
  bcc3d30  mov [rsp+0x10],rdx                            
  bcc3d35  push rbp                                      
  bcc3d36  push r15                                      
  bcc3d38  push r14                                      
  bcc3d3a  push r12                                      
  bcc3d3c  push rsi                                      
  bcc3d3d  push rdi                                      
  bcc3d3e  push rbx                                      
  bcc3d3f  sub rsp,0x30                                  
  bcc3d43  lea rbp,[rdx+0x60]                            
  bcc3d47  lea rcx,[0x12AE2880]                          ; [data_12ae2880]
  bcc3d4e  call 0xE938D30                                ; -> sub_e938d30
  bcc3d53  nop                                           
  bcc3d54  add rsp,0x30                                  
  bcc3d58  pop rbx                                       
  bcc3d59  pop rdi                                       
  bcc3d5a  pop rsi                                       
  bcc3d5b  pop r12                                       
  bcc3d5d  pop r14                                       
  bcc3d5f  pop r15                                       
  bcc3d61  pop rbp                                       
  bcc3d62  ret                                           
  bcc3d63  int3                                          
  bcc3d64  int3                                          
  bcc3d65  int3                                          
  bcc3d66  int3                                          
  bcc3d67  int3                                          
  bcc3d68  int3                                          
  bcc3d69  int3                                          
  bcc3d6a  int3                                          
  bcc3d6b  int3                                          
  bcc3d6c  int3                                          
  bcc3d6d  int3                                          
  bcc3d6e  int3                                          
  bcc3d6f  int3                                          
  bcc3d70  push rsi                                      
  bcc3d71  push rdi                                      
  bcc3d72  sub rsp,0x28                                  
  bcc3d76  mov rcx,[0x12AE2858]                          ; [data_12ae2858]
  bcc3d7d  test rcx,rcx                                  
  bcc3d80  je short 0xBCC3DCB                            ; -> loc_bcc3dcb
  bcc3d82  mov rdx,[0x12AE2868]                          ; [data_12ae2868]
  bcc3d89  sub rdx,rcx                                   
  bcc3d8c  cmp rdx,0x1000                                
  bcc3d93  jb short 0xBCC3DB1                            ; -> loc_bcc3db1
  bcc3d95  mov rax,[rcx-8]                               
  bcc3d99  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcc3d9d  sub rcx,rax                                   
  bcc3da0  cmp rcx,0x20                                  
  bcc3da4  jae 0xBCC3E28                                 ; -> loc_bcc3e28
  bcc3daa  add rdx,0x27                                  
  bcc3dae  mov rcx,rax                                   

loc_bcc3db1:  ; from bcc3d93
  bcc3db1  call 0xE935700                                ; -> sub_e935700
  bcc3db6  xorps xmm0,xmm0                               
  bcc3db9  movups [0x12AE2858],xmm0                      ; [data_12ae2858]
  bcc3dc0  mov qword ptr [0x12AE2868],0                  ; [data_12ae2868]

loc_bcc3dcb:  ; from bcc3d80
  bcc3dcb  mov rax,[0x12AE2848]                          ; [data_12ae2848]
  bcc3dd2  mov rcx,[rax+8]                               
  bcc3dd6  mov qword ptr [rcx],0                         
  bcc3ddd  mov rsi,[rax]                                 
  bcc3de0  test rsi,rsi                                  
  bcc3de3  je short 0xBCC3E11                            ; -> loc_bcc3e11
  bcc3de5  nop [rax+rax]                                 

loc_bcc3df0:  ; from bcc3e0f
  bcc3df0  mov rdi,[rsi]                                 
  bcc3df3  lea rcx,[rsi+0x10]                            
  bcc3df7  call 0x9B250                                  ; -> sub_9b250
  bcc3dfc  mov edx,0x50                                  
  bcc3e01  mov rcx,rsi                                   
  bcc3e04  call 0xE935700                                ; -> sub_e935700
  bcc3e09  mov rsi,rdi                                   
  bcc3e0c  test rdi,rdi                                  
  bcc3e0f  jne short 0xBCC3DF0                           ; -> loc_bcc3df0

loc_bcc3e11:  ; from bcc3de3
  bcc3e11  mov rcx,[0x12AE2848]                          ; [data_12ae2848]
  bcc3e18  mov edx,0x50                                  
  bcc3e1d  add rsp,0x28                                  
  bcc3e21  pop rdi                                       
  bcc3e22  pop rsi                                       
  bcc3e23  jmp 0xE935700                                 ; -> sub_e935700

loc_bcc3e28:  ; from bcc3da4
  bcc3e28  mov qword ptr [rsp+0x20],0                    
  bcc3e31  xor ecx,ecx                                   
  bcc3e33  xor edx,edx                                   
  bcc3e35  xor r8d,r8d                                   
  bcc3e38  xor r9d,r9d                                   
  bcc3e3b  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcc3e41  int3                                          
  bcc3e42  int3                                          
  bcc3e43  int3                                          
  bcc3e44  int3                                          
  bcc3e45  int3                                          
  bcc3e46  int3                                          
  bcc3e47  int3                                          
  bcc3e48  int3                                          
  bcc3e49  int3                                          
  bcc3e4a  int3                                          
  bcc3e4b  int3                                          
  bcc3e4c  int3                                          
  bcc3e4d  int3                                          
  bcc3e4e  int3                                          
  bcc3e4f  int3                                          
  bcc3e50  push r15                                      
  bcc3e52  push r14                                      
  bcc3e54  push rsi                                      
  bcc3e55  push rdi                                      
  bcc3e56  push rbp                                      
  bcc3e57  push rbx                                      
  bcc3e58  sub rsp,0x58                                  
  bcc3e5c  mov rdi,r9                                    
  bcc3e5f  mov esi,r8d                                   
  bcc3e62  mov ebx,edx                                   
  bcc3e64  mov r14,rcx                                   
  bcc3e67  mov rcx,[rsp+0xB0]                            
  bcc3e6f  mov r8,[rsp+0xB8]                             
  bcc3e77  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
  bcc3e7e  xor rax,rsp                                   
  bcc3e81  mov [rsp+0x50],rax                            
  bcc3e86  lea rdx,[rsp+0x38]                            
  bcc3e8b  call 0xBCC7CE0                                ; -> sub_bcc7ce0
  bcc3e90  cmp byte ptr [rsp+0x48],1                     
  bcc3e95  jne 0xBCC3F63                                 ; -> loc_bcc3f63
  bcc3e9b  xor eax,eax                                   
  bcc3e9d  cmp byte ptr [rsp+0x3A],1                     
  bcc3ea2  jne 0xBCC3F65                                 ; -> loc_bcc3f65
  bcc3ea8  cmp word ptr [rsp+0x38],0xFFFF                
  bcc3eae  je 0xBCC3F65                                  ; -> loc_bcc3f65
  bcc3eb4  mov ebp,[rsp+0xC0]                            
  bcc3ebb  mov rax,[r14]                                 
  bcc3ebe  mov r14,[rax+0x10]                            
  bcc3ec2  mov rcx,[r14]                                 
  bcc3ec5  mov eax,[rcx+0xD457C0]                        
  bcc3ecb  mov edx,0xFFFF                                

loc_bcc3ed0:  ; from bcc3f00
  bcc3ed0  mov r15d,eax                                  
  bcc3ed3  lea r8d,[r15+1]                               
  bcc3ed7  cmp r8d,0xFFFF                                
  bcc3ede  cmovae r8d,edx                                
  bcc3ee2  cmp eax,0xFFFF                                
  bcc3ee7  cmovae r8d,edx                                
  bcc3eeb  lock cmpxchg [rcx+0xD457C0],r8d               
  bcc3ef4  cmp r15d,0xFFFF                               
  bcc3efb  je short 0xBCC3F02                            ; -> loc_bcc3f02
  bcc3efd  cmp r15d,eax                                  
  bcc3f00  jne short 0xBCC3ED0                           ; -> loc_bcc3ed0

loc_bcc3f02:  ; from bcc3efb
  bcc3f02  xor r8d,r8d                                   
  bcc3f05  cmp r15d,0xFFFF                               
  bcc3f0c  setne r8b                                     
  bcc3f10  shl r8d,6                                     
  bcc3f14  mov eax,r15d                                  
  bcc3f17  shl rax,6                                     
  bcc3f1b  add rcx,rax                                   
  bcc3f1e  add rcx,0x9457C0                              
  bcc3f25  mov rdx,rdi                                   
  bcc3f28  call 0xEBCE390                                ; -> sub_ebce390
  bcc3f2d  mov [r14+0x7C],r15d                           
  bcc3f31  mov word ptr [r14+0x9E],1                     
  bcc3f3b  cmp byte ptr [rsp+0x3A],0                     
  bcc3f40  je short 0xBCC3F93                            ; -> loc_bcc3f93
  bcc3f42  movzx r8d,word ptr [rsp+0x38]                 
  bcc3f48  mov [rsp+0x28],bl                             
  bcc3f4c  mov [rsp+0x20],ebp                            
  bcc3f50  mov rcx,r14                                   
  bcc3f53  mov edx,esi                                   
  bcc3f55  mov r9w,0xFFFF                                
  bcc3f5a  call 0xBC60740                                ; -> sub_bc60740
  bcc3f5f  mov al,1                                      
  bcc3f61  jmp short 0xBCC3F65                           ; -> loc_bcc3f65

loc_bcc3f63:  ; from bcc3e95
  bcc3f63  xor eax,eax                                   

loc_bcc3f65:  ; from bcc3ea2, bcc3eae, bcc3f61
  bcc3f65  mov rcx,[rsp+0x50]                            
  bcc3f6a  xor rcx,rsp                                   
  bcc3f6d  mov rdx,[0x1230A0C0]                          ; [data_1230a0c0]
  bcc3f74  cmp rdx,rcx                                   
  bcc3f77  jne short 0xBCC3F86                           ; -> loc_bcc3f86
  bcc3f79  add rsp,0x58                                  
  bcc3f7d  pop rbx                                       
  bcc3f7e  pop rbp                                       
  bcc3f7f  pop rdi                                       
  bcc3f80  pop rsi                                       
  bcc3f81  pop r14                                       
  bcc3f83  pop r15                                       
  bcc3f85  ret                                           

loc_bcc3f86:  ; from bcc3f77
  bcc3f86  mov rcx,[rsp+0x50]                            
  bcc3f8b  xor rcx,rsp                                   
  bcc3f8e  call 0xE951550                                ; -> sub_e951550

loc_bcc3f93:  ; from bcc3f40
  bcc3f93  call 0x1A2800                                 ; -> sub_1a2800
  bcc3f98  int3                                          
  bcc3f99  int3                                          
  bcc3f9a  int3                                          
  bcc3f9b  int3                                          
  bcc3f9c  int3                                          
  bcc3f9d  int3                                          
  bcc3f9e  int3                                          
  bcc3f9f  int3                                          
  bcc3fa0  push r15                                      
  bcc3fa2  push r14                                      
  bcc3fa4  push r12                                      
  bcc3fa6  push rsi                                      
  bcc3fa7  push rdi                                      
  bcc3fa8  push rbp                                      
  bcc3fa9  push rbx                                      
  bcc3faa  sub rsp,0x90                                  
  bcc3fb1  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
  bcc3fb8  xor rax,rsp                                   
  bcc3fbb  mov [rsp+0x88],rax                            
  bcc3fc3  test byte ptr [0x12ADFA51],8                  ; [data_12adfa51]
  bcc3fca  jne short 0xBCC3FD3                           ; -> loc_bcc3fd3
  bcc3fcc  xor eax,eax                                   
  bcc3fce  jmp 0xBCC40EB                                 ; -> loc_bcc40eb

loc_bcc3fd3:  ; from bcc3fca
  bcc3fd3  mov rbx,[rsp+0xF0]                            
  bcc3fdb  xor eax,eax                                   
  bcc3fdd  cmp byte ptr [rbx+2],1                        
  bcc3fe1  jne 0xBCC40EB                                 ; -> loc_bcc40eb
  bcc3fe7  cmp word ptr [rbx],0xFFFF                     
  bcc3feb  je 0xBCC40EB                                  ; -> loc_bcc40eb
  bcc3ff1  mov r12,r9                                    
  bcc3ff4  mov r14d,edx                                  
  bcc3ff7  mov r15d,r8d                                  
  bcc3ffa  mov ebp,[rsp+0xF8]                            
  bcc4001  mov rax,[rcx]                                 
  bcc4004  mov rsi,[rax+0x10]                            
  bcc4008  mov dword ptr [rsp+0x48],0x3F800000           
  bcc4010  xorps xmm0,xmm0                               
  bcc4013  movups [rsp+0x4C],xmm0                        
  bcc4018  mov dword ptr [rsp+0x5C],0x3F800000           
  bcc4020  movups [rsp+0x60],xmm0                        
  bcc4025  mov dword ptr [rsp+0x70],0x3F800000           
  bcc402d  movups [rsp+0x74],xmm0                        
  bcc4032  mov dword ptr [rsp+0x84],0x3F800000           
  bcc403d  mov rcx,[rsi]                                 
  bcc4040  mov eax,[rcx+0xD457C0]                        
  bcc4046  mov edx,0xFFFF                                
  bcc404b  nop [rax+rax]                                 

loc_bcc4050:  ; from bcc407d
  bcc4050  mov edi,eax                                   
  bcc4052  lea r8d,[rdi+1]                               
  bcc4056  cmp r8d,0xFFFF                                
  bcc405d  cmovae r8d,edx                                
  bcc4061  cmp eax,0xFFFF                                
  bcc4066  cmovae r8d,edx                                
  bcc406a  lock cmpxchg [rcx+0xD457C0],r8d               
  bcc4073  cmp edi,0xFFFF                                
  bcc4079  je short 0xBCC407F                            ; -> loc_bcc407f
  bcc407b  cmp edi,eax                                   
  bcc407d  jne short 0xBCC4050                           ; -> loc_bcc4050

loc_bcc407f:  ; from bcc4079
  bcc407f  xor r8d,r8d                                   
  bcc4082  cmp edi,0xFFFF                                
  bcc4088  setne r8b                                     
  bcc408c  shl r8d,6                                     
  bcc4090  mov eax,edi                                   
  bcc4092  shl rax,6                                     
  bcc4096  add rcx,rax                                   
  bcc4099  add rcx,0x9457C0                              
  bcc40a0  lea rdx,[rsp+0x48]                            
  bcc40a5  call 0xEBCE390                                ; -> sub_ebce390
  bcc40aa  mov [rsi+0x7C],edi                            
  bcc40ad  mov word ptr [rsi+0x9E],1                     
  bcc40b6  mov rax,r12                                   
  bcc40b9  shr rax,0x20                                  
  bcc40bd  jne short 0xBCC4124                           ; -> loc_bcc4124
  bcc40bf  mov [rsi+0x94],r12d                           
  bcc40c6  cmp byte ptr [rbx+2],0                        
  bcc40ca  je short 0xBCC4149                            ; -> loc_bcc4149
  bcc40cc  mov edx,r15d                                  
  bcc40cf  movzx r8d,word ptr [rbx]                      
  bcc40d3  mov [rsp+0x28],r14b                           
  bcc40d8  mov [rsp+0x20],ebp                            
  bcc40dc  mov rcx,rsi                                   
  bcc40df  mov r9w,0xFFFF                                
  bcc40e4  call 0xBC60740                                ; -> sub_bc60740
  bcc40e9  mov al,1                                      

loc_bcc40eb:  ; from bcc3fce, bcc3fe1, bcc3feb
  bcc40eb  mov rcx,[rsp+0x88]                            
  bcc40f3  xor rcx,rsp                                   
  bcc40f6  mov rdx,[0x1230A0C0]                          ; [data_1230a0c0]
  bcc40fd  cmp rdx,rcx                                   
  bcc4100  jne short 0xBCC4114                           ; -> loc_bcc4114
  bcc4102  add rsp,0x90                                  
  bcc4109  pop rbx                                       
  bcc410a  pop rbp                                       
  bcc410b  pop rdi                                       
  bcc410c  pop rsi                                       
  bcc410d  pop r12                                       
  bcc410f  pop r14                                       
  bcc4111  pop r15                                       
  bcc4113  ret                                           

loc_bcc4114:  ; from bcc4100
  bcc4114  mov rcx,[rsp+0x88]                            
  bcc411c  xor rcx,rsp                                   
  bcc411f  call 0xE951550                                ; -> sub_e951550

loc_bcc4124:  ; from bcc40bd
  bcc4124  xorps xmm0,xmm0                               
  bcc4127  movups [rsp+0x38],xmm0                        
  bcc412c  lea rax,[0xF08E738]                           ; [data_f08e738]
  bcc4133  mov [rsp+0x30],rax                            
  bcc4138  lea rdx,[0xFB3B080]                           ; [data_fb3b080]
  bcc413f  lea rcx,[rsp+0x30]                            
  bcc4144  call 0xEEC6D80                                ; -> sub_eec6d80

loc_bcc4149:  ; from bcc40ca
  bcc4149  call 0x1A2800                                 ; -> sub_1a2800
  bcc414e  int3                                          
  bcc414f  int3                                          
  bcc4150  push rbp                                      
  bcc4151  push r15                                      
  bcc4153  push r14                                      
  bcc4155  push r13                                      
  bcc4157  push r12                                      
  bcc4159  push rsi                                      
  bcc415a  push rdi                                      
  bcc415b  push rbx                                      
  bcc415c  sub rsp,0xB8                                  
  bcc4163  lea rbp,[rsp+0x80]                            
  bcc416b  mov qword ptr [rbp+0x30],0xFFFFFFFFFFFFFFFE   
  bcc4173  mov r15,r9                                    
  bcc4176  mov [rbp+0x2A],r8w                            
  bcc417b  mov [rbp+0x2F],dl                             
  bcc417e  mov [rbp+0x20],rcx                            
  bcc4182  mov eax,[0x12AE28C8]                          ; [data_12ae28c8]
  bcc4188  mov ecx,[0x128767C8]                          ; [data_128767c8]
  bcc418e  mov rdx,gs:[0x58]                             
  bcc4197  mov rcx,[rdx+rcx*8]                           
  bcc419b  cmp eax,[rcx+4]                               
  bcc41a1  jg 0xBCC4723                                  ; -> loc_bcc4723

loc_bcc41a7:  ; from bcc4736, bcc47c9
  bcc41a7  mov r12,[rbp+0xA0]                            
  bcc41ae  test byte ptr [0x12ADFA51],8                  ; [data_12adfa51]
  bcc41b5  jne 0xBCC42EC                                 ; -> loc_bcc42ec

loc_bcc41bb:  ; from bcc4302, bcc430c, bcc4317
  bcc41bb  cmp byte ptr [r12+0xF8],1                     
  bcc41c4  jne 0xBCC4346                                 ; -> loc_bcc4346
  bcc41ca  mov r13,[r15]                                 
  bcc41cd  mov al,1                                      
  bcc41cf  test r13,r13                                  
  bcc41d2  je 0xBCC470A                                  ; -> loc_bcc470a
  bcc41d8  movzx eax,word ptr [r12+0xE8]                 
  bcc41e1  mov [rbp+0x2C],ax                             
  bcc41e5  cmp ax,0xFFFF                                 
  bcc41e9  setne al                                      
  bcc41ec  and al,[r12+0xEA]                             
  bcc41f4  cmp al,1                                      
  bcc41f6  jne 0xBCC4346                                 ; -> loc_bcc4346
  bcc41fc  mov rsi,[r15+8]                               
  bcc4200  xor eax,eax                                   
  bcc4202  mov ebx,0xFFFF                                
  bcc4207  jmp short 0xBCC4274                           ; -> loc_bcc4274
  bcc4209  nop [rax]                                     

loc_bcc4210:  ; from bcc42dc, bcc42e7
  bcc4210  xor r8d,r8d                                   
  bcc4213  cmp r12d,0xFFFF                               
  bcc421a  setne r8b                                     
  bcc421e  shl r8d,6                                     
  bcc4222  mov eax,r12d                                  
  bcc4225  shl rax,6                                     
  bcc4229  add rcx,rax                                   
  bcc422c  call 0xEBCE390                                ; -> sub_ebce390

loc_bcc4231:  ; from bcc4293
  bcc4231  or r14b,[rbp+0x2F]                            
  bcc4235  mov [r15+0x7C],r12d                           
  bcc4239  mov word ptr [r15+0x9E],1                     
  bcc4243  mov [rsp+0x28],r14b                           
  bcc4248  mov eax,[rbp+0xA8]                            
  bcc424e  mov [rsp+0x20],eax                            
  bcc4252  mov rcx,r15                                   
  bcc4255  movzx edx,word ptr [rbp+0x2A]                 
  bcc4259  movzx r8d,word ptr [rbp+0x2C]                 
  bcc425e  mov r9w,0xFFFF                                
  bcc4263  call 0xBC60740                                ; -> sub_bc60740
  bcc4268  mov rax,rdi                                   
  bcc426b  cmp rdi,r13                                   
  bcc426e  je 0xBCC4708                                  ; -> loc_bcc4708

loc_bcc4274:  ; from bcc4207
  bcc4274  lea rdi,[rax+1]                               
  bcc4278  cmp rdi,r13                                   
  bcc427b  setb r14b                                     
  bcc427f  mov rcx,[rbp+0x20]                            
  bcc4283  mov rcx,[rcx]                                 
  bcc4286  mov r15,[rcx+0x10]                            
  bcc428a  mov r12d,0                                    
  bcc4290  test rsi,rsi                                  
  bcc4293  je short 0xBCC4231                            ; -> loc_bcc4231
  bcc4295  mov edx,eax                                   
  bcc4297  shl rdx,6                                     
  bcc429b  add rdx,rsi                                   
  ... (--max 600)

```
