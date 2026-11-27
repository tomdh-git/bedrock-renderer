# ctxpack build 0xebd18f0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=data=native_functions.tsv:4aa79c0fe0403206218642539e682a39a0af5f62d67d032bda989fd61bce04cd,data=native_deps.tsv:1fe4952061656732bfc6db3f2d9fd9cab2b08869dc95b7037670b5bec4910ae4,data=native_boundary.tsv:6e7ad029f069c6b1fb5e2798ef91f760a7586073ba5e6351050cf30070171607,data=native_boundary_candidates.tsv:8bb54e181419c9c42374be3142e4291934993a869d499a2b80e595610c86b8d9

## HEADER
  rva        : 0xebd18f0
  size       : 0xb9 (185 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 0 (direct), depth 1
  callers    : 6

## EXACT LISTING (0xebd18f0..0xebd19a9)
```
sub_ebd18f0  [0xebd18f0..0xebd38f0)  size 0x2000  8 xrefs in
  chained fragments: 0xebd19a9..0xebd1a1b, 0xebd1a1b..0xebd1a23

loc_ebd18f0:  ; from ebd329b, ebd32f9
  ebd18f0  mov [rsp+0x20],rbx                            
  ebd18f5  push rsi                                      
  ebd18f6  push rdi                                      
  ebd18f7  mov r11,[rsp+0x38]                            
  ebd18fc  mov rbx,rcx                                   
  ebd18ff  mov esi,r8d                                   
  ebd1902  test r8b,3                                    
  ebd1906  jne 0xEBD19A4                                 ; -> loc_ebd19a4
  ebd190c  cmp esi,4                                     
  ebd190f  jb 0xEBD19A4                                  ; -> loc_ebd19a4
  ebd1915  test r11b,0xF                                 
  ebd1919  jne 0xEBD19A4                                 ; -> loc_ebd19a4
  ebd191f  test cl,0xF                                   
  ebd1922  jne 0xEBD19A4                                 ; -> loc_ebd19a4
  ebd1928  movdqa xmm3,[0xEECB5D0]                       ; [data_eecb5d0]
  ebd1930  movdqa xmm4,[0xEF40D90]                       ; [data_ef40d90]
  ebd1938  shr esi,2                                     
  ebd193b  test r9d,r9d                                  
  ebd193e  je 0xEBD1A1B                                  ; -> loc_ebd1a1b
  ebd1944  mov r10d,[rsp+0x40]                           
  ebd1949  mov edi,edx                                   
  ebd194b  mov r8d,r9d                                   
  ebd194e  xchg ax,ax                                    

loc_ebd1950:  ; from ebd199a
  ebd1950  mov rax,r11                                   
  ebd1953  test esi,esi                                  
  ebd1955  je short 0xEBD1990                            ; -> loc_ebd1990
  ebd1957  mov rcx,rbx                                   
  ebd195a  mov edx,esi                                   
  ebd195c  sub rcx,r11                                   
  ebd195f  nop                                           

loc_ebd1960:  ; from ebd198e
  ebd1960  movups xmm1,[rax]                             
  ebd1963  lea rax,[rax+0x10]                            
  ebd1967  movdqa xmm2,xmm1                              
  ebd196b  movdqa xmm0,xmm1                              
  ebd196f  pslld xmm2,0x10                               
  ebd1974  andps xmm1,xmm3                               
  ebd1977  psrld xmm0,0x10                               
  ebd197c  orps xmm2,xmm0                                
  ebd197f  andps xmm2,xmm4                               
  ebd1982  orps xmm2,xmm1                                
  ebd1985  movups [rcx+rax-0x10],xmm2                    
  ebd198a  sub rdx,1                                     
  ebd198e  jne short 0xEBD1960                           ; -> loc_ebd1960

loc_ebd1990:  ; from ebd1955
  ebd1990  add r11,r10                                   
  ebd1993  add rbx,rdi                                   
  ebd1996  sub r8,1                                      
  ebd199a  jne short 0xEBD1950                           ; -> loc_ebd1950
  ebd199c  mov rbx,[rsp+0x30]                            
  ebd19a1  pop rdi                                       
  ebd19a2  pop rsi                                       
  ebd19a3  ret                                           

loc_ebd19a4:  ; from ebd1906, ebd190f, ebd1919, ebd1922
  ebd19a4  test r9d,r9d                                  
  ebd19a7  je short 0xEBD1A1B                            ; -> loc_ebd1a1b
  ebd19a9  mov [rsp+0x18],rbp                            
  ebd19ae  mov [rsp+0x20],r14                            
  ebd19b3  mov r14d,[rsp+0x40]                           
  ebd19b8  mov [rsp+0x28],r15                            
  ebd19bd  mov r15d,edx                                  
  ebd19c0  mov ebp,r9d                                   

loc_ebd19c3:  ; from ebd1a0a
  ebd19c3  test esi,esi                                  
  ebd19c5  je short 0xEBD1A00                            ; -> loc_ebd1a00
  ebd19c7  mov rdi,r11                                   
  ebd19ca  lea rax,[rbx+2]                               
  ebd19ce  sub rdi,rbx                                   
  ebd19d1  mov r10,rsi                                   

loc_ebd19d4:  ; from ebd19fe
  ebd19d4  movzx r9d,byte ptr [rdi+rax-2]                
  ebd19da  movzx edx,byte ptr [rdi+rax-1]                
  ebd19df  movzx r8d,byte ptr [rdi+rax+1]                
  ebd19e5  movzx ecx,byte ptr [rdi+rax]                  
  ebd19e9  mov [rax-2],cl                                
  ebd19ec  mov [rax-1],dl                                
  ebd19ef  mov [rax],r9b                                 
  ebd19f2  mov [rax+1],r8b                               
  ebd19f6  lea rax,[rax+4]                               
  ebd19fa  sub r10,1                                     
  ebd19fe  jne short 0xEBD19D4                           ; -> loc_ebd19d4

loc_ebd1a00:  ; from ebd19c5
  ebd1a00  add r11,r14                                   
  ebd1a03  add rbx,r15                                   
  ebd1a06  sub rbp,1                                     
  ebd1a0a  jne short 0xEBD19C3                           ; -> loc_ebd19c3
  ebd1a0c  mov r15,[rsp+0x28]                            
  ebd1a11  mov r14,[rsp+0x20]                            
  ebd1a16  mov rbp,[rsp+0x18]                            

loc_ebd1a1b:  ; from ebd193e, ebd19a7
  ebd1a1b  mov rbx,[rsp+0x30]                            
  ebd1a20  pop rdi                                       
  ebd1a21  pop rsi                                       
  ebd1a22  ret                                           
  ebd1a23  int3                                          
  ebd1a24  int3                                          
  ebd1a25  int3                                          
  ebd1a26  int3                                          
  ebd1a27  int3                                          
  ebd1a28  int3                                          
  ebd1a29  int3                                          
  ebd1a2a  int3                                          
  ebd1a2b  int3                                          
  ebd1a2c  int3                                          
  ebd1a2d  int3                                          
  ebd1a2e  int3                                          
  ebd1a2f  int3                                          
  ebd1a30  mov [rsp+0x18],rbx                            
  ebd1a35  push rbp                                      
  ebd1a36  push rdi                                      
  ebd1a37  push r12                                      
  ebd1a39  push r14                                      
  ebd1a3b  push r15                                      
  ebd1a3d  sub rsp,0x30                                  
  ebd1a41  mov r14d,[rsp+0x88]                           
  ebd1a49  mov r12d,r8d                                  
  ebd1a4c  mov rbx,[rsp+0x80]                            
  ebd1a54  cmp r8d,r14d                                  
  ebd1a57  mov ebp,r8d                                   
  ebd1a5a  mov r15d,edx                                  
  ebd1a5d  cmova r12d,r14d                               
  ebd1a61  mov rdi,rcx                                   
  ebd1a64  test r9d,r9d                                  
  ebd1a67  je short 0xEBD1AC5                            ; -> loc_ebd1ac5
  ebd1a69  mov [rsp+0x60],rsi                            
  ebd1a6e  mov eax,edx                                   
  ebd1a70  mov [rsp+0x68],r13                            
  ebd1a75  mov r13d,edx                                  
  ebd1a78  imul r13d,ebp                                 
  ebd1a7c  imul eax,r14d                                 
  ebd1a80  mov esi,r9d                                   
  ebd1a83  mov [rsp+0x80],rax                            
  ebd1a8b  nop [rax+rax]                                 

loc_ebd1a90:  ; from ebd1ab9
  ebd1a90  mov [rsp+0x28],r14d                           
  ebd1a95  mov r9d,r15d                                  
  ebd1a98  mov r8d,r12d                                  
  ebd1a9b  mov [rsp+0x20],ebp                            
  ebd1a9f  mov rdx,rbx                                   
  ebd1aa2  mov rcx,rdi                                   
  ebd1aa5  call 0xEBCE3A0                                ; -> sub_ebce3a0
  ebd1aaa  add rdi,[rsp+0x80]                            
  ebd1ab2  add rbx,r13                                   
  ebd1ab5  sub rsi,1                                     
  ebd1ab9  jne short 0xEBD1A90                           ; -> loc_ebd1a90
  ebd1abb  mov r13,[rsp+0x68]                            
  ebd1ac0  mov rsi,[rsp+0x60]                            

loc_ebd1ac5:  ; from ebd1a67
  ebd1ac5  mov rbx,[rsp+0x70]                            
  ebd1aca  add rsp,0x30                                  
  ebd1ace  pop r15                                       
  ebd1ad0  pop r14                                       
  ebd1ad2  pop r12                                       
  ebd1ad4  pop rdi                                       
  ebd1ad5  pop rbp                                       
  ebd1ad6  ret                                           
  ebd1ad7  int3                                          
  ebd1ad8  int3                                          
  ebd1ad9  int3                                          
  ebd1ada  int3                                          
  ebd1adb  int3                                          
  ebd1adc  int3                                          
  ebd1add  int3                                          
  ebd1ade  int3                                          
  ebd1adf  int3                                          
  ebd1ae0  movsxd rax,ecx                                
  ebd1ae3  lea rcx,[0xEF3F5A0]                           ; [data_ef3f5a0]
  ebd1aea  add rax,rax                                   
  ebd1aed  cmp qword ptr [rcx+rax*8],0                   
  ebd1af2  je short 0xEBD1B05                            ; -> loc_ebd1b05
  ebd1af4  movsxd rax,edx                                
  ebd1af7  add rax,rax                                   
  ebd1afa  cmp qword ptr [rcx+rax*8+8],0                 
  ebd1b00  je short 0xEBD1B05                            ; -> loc_ebd1b05
  ebd1b02  mov al,1                                      
  ebd1b04  ret                                           

loc_ebd1b05:  ; from ebd1af2, ebd1b00
  ebd1b05  xor al,al                                     
  ebd1b07  ret                                           
  ebd1b08  int3                                          
  ebd1b09  int3                                          
  ebd1b0a  int3                                          
  ebd1b0b  int3                                          
  ebd1b0c  int3                                          
  ebd1b0d  int3                                          
  ebd1b0e  int3                                          
  ebd1b0f  int3                                          
  ebd1b10  mov [rsp+8],rbx                               
  ebd1b15  mov [rsp+0x10],edx                            
  ebd1b19  push rbp                                      
  ebd1b1a  push rsi                                      
  ebd1b1b  push rdi                                      
  ebd1b1c  push r12                                      
  ebd1b1e  push r13                                      
  ebd1b20  push r14                                      
  ebd1b22  push r15                                      
  ebd1b24  sub rsp,0x50                                  
  ebd1b28  movsxd r15,edx                                
  ebd1b2b  mov rsi,rcx                                   
  ebd1b2e  imul r10,r15,0xD                              
  ebd1b32  lea rcx,[0xEF3F0E0]                           ; [data_ef3f0e0]
  ebd1b39  movzx eax,r8w                                 
  ebd1b3d  dec eax                                       
  ebd1b3f  movzx r12d,byte ptr [r10+rcx+2]               
  ebd1b45  movzx ebx,byte ptr [r10+rcx+1]                
  ebd1b4b  movzx r11d,byte ptr [r10+rcx+5]               
  ebd1b51  add eax,ebx                                   
  ebd1b53  movzx r8d,byte ptr [r10+rcx+4]                
  ebd1b59  cdq                                           
  ebd1b5a  idiv ebx                                      
  ebd1b5c  mov r10d,r8d                                  
  ebd1b5f  mov edx,ebx                                   
  ebd1b61  movzx ecx,ax                                  
  ebd1b64  imul edx,ecx                                  
  ebd1b67  movzx ecx,r8w                                 
  ebd1b6b  imul r10d,ebx                                 
  ebd1b6f  cmp r10w,dx                                   
  ebd1b73  cmovbe cx,ax                                  
  ebd1b77  movzx eax,r9w                                 
  ebd1b7b  dec eax                                       
  ebd1b7d  movzx ecx,cx                                  
  ebd1b80  add eax,r12d                                  
  ebd1b83  imul ecx,ebx                                  
  ebd1b86  mov r9d,r11d                                  
  ebd1b89  cdq                                           
  ebd1b8a  idiv r12d                                     
  ebd1b8d  imul r9d,r12d                                 
  ebd1b91  mov edx,r12d                                  
  ebd1b94  movzx ebp,cx                                  
  ebd1b97  movzx ecx,ax                                  
  ebd1b9a  imul edx,ecx                                  
  ebd1b9d  mov [rsp+0xA0],ebp                            
  ebd1ba4  cmp r9w,dx                                    
  ebd1ba8  cmovbe r11w,ax                                
  ebd1bad  movzx edi,r11w                                
  ebd1bb1  mov r11d,1                                    
  ebd1bb7  imul edi,r12d                                 
  ebd1bbb  mov r14d,r11d                                 
  ebd1bbe  cmp r11w,[rsp+0xB0]                           
  ebd1bc7  mov r13d,r11d                                 
  ebd1bca  cmovbe r13w,[rsp+0xB0]                        
  ebd1bd4  cmp r11w,[rsp+0xB8]                           
  ebd1bdd  mov [rsp+0xA8],edi                            
  ebd1be4  cmovbe r14w,[rsp+0xB8]                        
  ebd1bee  cmp byte ptr [rsp+0xC8],0                     
  ebd1bf6  mov [rsp+0xB0],r14d                           
  ebd1bfe  je short 0xEBD1C79                            ; -> loc_ebd1c79
  ebd1c00  lea eax,[rbx-1]                               
  ebd1c03  add eax,ebp                                   
  ebd1c05  cdq                                           
  ebd1c06  idiv ebx                                      
  ebd1c08  movzx edx,ax                                  
  ebd1c0b  imul edx,ebx                                  
  ebd1c0e  cmp r10w,dx                                   
  ebd1c12  cmovbe r8w,ax                                 
  ebd1c17  movzx eax,di                                  
  ebd1c1a  dec eax                                       
  ebd1c1c  movzx r8d,r8w                                 
  ebd1c20  add eax,r12d                                  
  ebd1c23  imul r8d,ebx                                  
  ebd1c27  cdq                                           
  ebd1c28  idiv r12d                                     
  ebd1c2b  movzx edx,ax                                  
  ebd1c2e  movzx eax,r13w                                
  ebd1c32  imul edx,r12d                                 
  ebd1c36  cmp r9w,dx                                    
  ebd1c3a  cmova dx,r9w                                  
  ebd1c3f  cmp r11w,r13w                                 
  ebd1c43  cmova ax,r11w                                 
  ebd1c48  cmp r8w,dx                                    
  ebd1c4c  cmova dx,r8w                                  
  ebd1c51  cmp dx,ax                                     
  ebd1c54  cmova ax,dx                                   
  ebd1c58  movzx eax,ax                                  
  ebd1c5b  movd xmm0,eax                                 
  ebd1c5f  cvtdq2ps xmm0,xmm0                            
  ebd1c62  call 0xEBCD6F0                                ; -> sub_ebcd6f0
  ebd1c67  mulss xmm0,[0xEF3EF9C]                        ; [data_ef3ef9c]
  ebd1c6f  cvttss2si r12,xmm0                            
  ebd1c74  inc r12b                                      
  ebd1c77  jmp short 0xEBD1C7D                           ; -> loc_ebd1c7d

loc_ebd1c79:  ; from ebd1bfe
  ebd1c79  movzx r12d,r11b                               

loc_ebd1c7d:  ; from ebd1c77
  ebd1c7d  movzx eax,byte ptr [rsp+0xC8]                 
  ebd1c85  movzx r9d,r13w                                
  ebd1c89  mov byte ptr [rsp+0x40],0xFF                  
  ebd1c8e  movzx r8d,di                                  
  ebd1c92  mov [rsp+0x38],r15d                           
  ebd1c97  movzx edx,bp                                  
  ebd1c9a  mov [rsp+0x30],r14w                           
  ebd1ca0  xor ecx,ecx                                   
  ebd1ca2  movzx r14d,byte ptr [rsp+0xC0]                
  ebd1cab  mov [rsp+0x28],al                             
  ebd1caf  mov [rsp+0x20],r14b                           
  ebd1cb4  call 0xEBD15B0                                ; -> sub_ebd15b0
  ebd1cb9  xor edi,edi                                   
  ebd1cbb  mov r15d,eax                                  
  ebd1cbe  test rsi,rsi                                  
  ebd1cc1  jne short 0xEBD1CC7                           ; -> loc_ebd1cc7
  ebd1cc3  mov ebx,edi                                   
  ebd1cc5  jmp short 0xEBD1CE8                           ; -> loc_ebd1ce8

loc_ebd1cc7:  ; from ebd1cc1
  ebd1cc7  mov rax,[rsi]                                 
  ebd1cca  lea r8,[r15+0x40]                             
  ebd1cce  mov [rsp+0x28],edi                            
  ebd1cd2  xor edx,edx                                   
  ebd1cd4  mov r9d,0x10                                  
  ebd1cda  mov [rsp+0x20],rdi                            
  ebd1cdf  mov rcx,rsi                                   
  ebd1ce2  call qword ptr [rax+8]                        ; vcall slot 1 (+0x8)
  ebd1ce5  mov rbx,rax                                   

loc_ebd1ce8:  ; from ebd1cc5
  ebd1ce8  mov eax,[rsp+0x98]                            
  ebd1cef  lea rcx,[rbx+0x47]                            
  ebd1cf3  mov edx,[rsp+0xA8]                            
  ebd1cfa  and rcx,0xFFFFFFFFFFFFFFF0                    
  ebd1cfe  mov [rbx+0x10],eax                            
  ebd1d01  mov eax,[rsp+0xA0]                            
  ebd1d08  mov [rbx+0x20],eax                            
  ebd1d0b  movzx eax,dx                                  
  ebd1d0e  mov rdx,[rsp+0xD0]                            
  ebd1d16  mov [rbx+0x24],eax                            
  ebd1d19  movzx eax,r13w                                
  ebd1d1d  mov [rbx+0x28],eax                            
  ebd1d20  mov eax,[rsp+0xB0]                            
  ebd1d27  mov [rbx+0x2C],ax                             
  ebd1d2b  mov [rbx],rsi                                 
  ebd1d2e  mov [rbx+8],rcx                               
  ebd1d32  mov [rbx+0x14],edi                            
  ebd1d35  mov [rbx+0x18],r15d                           
  ebd1d39  mov [rbx+0x1C],edi                            
  ebd1d3c  mov [rbx+0x2E],r12b                           
  ebd1d40  mov byte ptr [rbx+0x2F],0                     
  ebd1d44  mov [rbx+0x30],r14b                           
  ebd1d48  mov word ptr [rbx+0x31],0                     
  ebd1d4e  mov byte ptr [rbx+0x33],0                     
  ebd1d52  test rdx,rdx                                  
  ebd1d55  je short 0xEBD1D5F                            ; -> loc_ebd1d5f
  ebd1d57  mov r8,r15                                    
  ebd1d5a  call 0xEBCE390                                ; -> sub_ebce390

loc_ebd1d5f:  ; from ebd1d55
  ebd1d5f  mov rax,rbx                                   
  ebd1d62  mov rbx,[rsp+0x90]                            
  ebd1d6a  add rsp,0x50                                  
  ebd1d6e  pop r15                                       
  ebd1d70  pop r14                                       
  ebd1d72  pop r13                                       
  ebd1d74  pop r12                                       
  ebd1d76  pop rdi                                       
  ebd1d77  pop rsi                                       
  ebd1d78  pop rbp                                       
  ebd1d79  ret                                           
  ebd1d7a  int3                                          
  ebd1d7b  int3                                          
  ebd1d7c  int3                                          
  ebd1d7d  int3                                          
  ebd1d7e  int3                                          
  ebd1d7f  int3                                          
  ebd1d80  push rbp                                      
  ebd1d82  push rbx                                      
  ebd1d83  push rsi                                      
  ebd1d84  push rdi                                      
  ebd1d85  push r12                                      
  ebd1d87  push r13                                      
  ebd1d89  push r14                                      
  ebd1d8b  push r15                                      
  ebd1d8d  lea rbp,[rsp-7]                               
  ebd1d92  sub rsp,0x88                                  
  ebd1d99  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
  ebd1da0  xor rax,rsp                                   
  ebd1da3  mov [rbp-0x11],rax                            
  ebd1da7  mov rax,[rbp+0x87]                            
  ebd1dae  lea rbx,[rbp-0x41]                            
  ebd1db2  mov r12,[rbp+0x6F]                            
  ebd1db6  mov r15d,r8d                                  
  ebd1db9  xor r8d,r8d                                   
  ebd1dbc  mov [rbp-0x61],r9d                            
  ebd1dc0  test rax,rax                                  
  ebd1dc3  mov [rbp-0x39],r8d                            
  ebd1dc7  mov r14,rcx                                   
  ebd1dca  mov [rbp-0x31],r8d                            
  ebd1dce  movzx ecx,byte ptr [rbp+0x77]                 
  ebd1dd2  lea r9,[0xF847A07]                            ; [data_f847a07]
  ebd1dd9  cmovne rbx,rax                                
  ebd1ddd  mov [rbp-0x41],r9                             
  ebd1de1  test cl,cl                                    
  ebd1de3  mov [rbp-0x59],r9                             
  ebd1de7  mov edi,edx                                   
  ebd1de9  mov [rbp-0x51],r8d                            
  ebd1ded  mov eax,0x20                                  
  ebd1df2  mov [rbp-0x49],r8d                            
  ebd1df6  mov edx,8                                     
  ebd1dfb  lea r9,[rbp-0x59]                             
  ebd1dff  cmovne eax,edx                                
  ebd1e02  xorps xmm0,xmm0                               
  ebd1e05  movzx r13d,al                                 
  ebd1e09  lea rdx,[rbp-0x29]                            
  ebd1e0d  xor eax,eax                                   
  ebd1e0f  add cl,2                                      
  ebd1e12  mov [rbp-0x19],ax                             
  ebd1e16  mov r8d,0x12                                  
  ebd1e1c  movups [rbp-0x29],xmm0                        
  ebd1e20  mov eax,edi                                   
  ebd1e22  mov [rbp-0x27],cl                             
  ebd1e25  shr eax,8                                     
  ebd1e28  mov rcx,r14                                   
  ebd1e2b  mov [rbp-0x1C],al                             
  ebd1e2e  mov eax,r15d                                  
  ebd1e31  shr eax,8                                     
  ebd1e34  mov [rbp-0x1A],al                             
  ebd1e37  test rbx,rbx                                  
  ebd1e3a  mov rax,[r14]                                 
  ebd1e3d  cmovne r9,rbx                                 
  ebd1e41  mov [rbp-0x1D],dil                            
  ... (--max 400)
```

## CALLERS
```
  0xe7f5380 sub_e7f5380 size 0x7b92
  0xe803640 sub_e803640 size 0x2fb
  0xe818050 sub_e818050 size 0x438
  0xe85e5c0 sub_e85e5c0 size 0x79cc
  0xe868120 sub_e868120 size 0x1b0
  0xebd21c0 sub_ebd21c0 size 0x495
  -- 6 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier

## STRINGS AND RIP REFS
  (none)

## FIELD ACCESS TABLE (descscan2, regs rdi,rsi,r9,r15)
  (no [reg+off] description reads detected; register unknown -> [open])

## KNOWN STRUCT LAYOUTS TOUCHED
  (none detected)

## CLOSEST FINISHED LIFT (style example, same size band + call shape)
  56c85c0.md  size 0x95  callees~60  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\56c85c0.md

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

