# preflight 0xEBCE390

## fn
```
sub_ebce390  [0xebce390..0xebd2390)  size 0x4000  843 xrefs in

loc_ebce390:  ; from ebd0a96, ebd0aa6, ebd0d26
  ebce390  jmp 0xEEC6EC0                                 ; -> sub_eec6ec0
  ebce395  int3                                          
  ebce396  int3                                          
  ebce397  int3                                          
  ebce398  int3                                          
  ebce399  int3                                          
  ebce39a  int3                                          
  ebce39b  int3                                          
  ebce39c  int3                                          
  ebce39d  int3                                          
  ebce39e  int3                                          
  ebce39f  int3                                          
  ebce3a0  test r9d,r9d                                  
  ebce3a3  je short 0xEBCE414                            ; -> loc_ebce414
  ebce3a5  push rbx                                      
  ebce3a6  push rdi                                      
  ebce3a7  sub rsp,0x28                                  
  ebce3ab  mov [rsp+0x40],rbp                            
  ebce3b0  mov rdi,rdx                                   
  ebce3b3  mov [rsp+0x48],rsi                            
  ebce3b8  mov rbx,rcx                                   
  ebce3bb  mov [rsp+0x50],r14                            
  ebce3c0  mov r14d,[rsp+0x60]                           
  ebce3c5  mov [rsp+0x20],r15                            
  ebce3ca  mov r15d,[rsp+0x68]                           
  ebce3cf  mov ebp,r8d                                   
  ebce3d2  mov esi,r9d                                   
  ebce3d5  nop [rax+rax]                                 

loc_ebce3e0:  ; from ebce3f8
  ebce3e0  mov r8,rbp                                    
  ebce3e3  mov rdx,rdi                                   
  ebce3e6  mov rcx,rbx                                   
  ebce3e9  call 0xEEC6EC0                                ; -> sub_eec6ec0
  ebce3ee  add rdi,r14                                   
  ebce3f1  add rbx,r15                                   
  ebce3f4  sub rsi,1                                     
  ebce3f8  jne short 0xEBCE3E0                           ; -> loc_ebce3e0
  ebce3fa  mov r15,[rsp+0x20]                            
  ebce3ff  mov r14,[rsp+0x50]                            
  ebce404  mov rsi,[rsp+0x48]                            
  ebce409  mov rbp,[rsp+0x40]                            
  ... (--max 40)

```

## callers
```
  sub_568cd90                  5 call site(s)
  sub_56ae230                  7 call site(s)
  sub_56aeeb0                  5 call site(s)
  sub_56c8dd0                  5 call site(s)
  sub_56ca9c0                  7 call site(s)
  sub_56d1550                  5 call site(s)
  sub_56d3170                  5 call site(s)
  sub_56d5ed0                  5 call site(s)
  sub_8b9d530                  1 call site(s)
  sub_8b9e460                  1 call site(s)
  sub_8b9e5f0                  2 call site(s)
  sub_8b9e9e0                  2 call site(s)
  sub_8b9ef00                  1 call site(s)
  sub_bc02090                  10 call site(s)
  sub_bc04dc0                  7 call site(s)
  sub_bc068f0                  5 call site(s)
  sub_bc07a70                  5 call site(s)
  sub_bc080c0                  5 call site(s)
  sub_bc0ac20                  5 call site(s)
  sub_bc0b240                  5 call site(s)
  sub_bc0f130                  7 call site(s)
  sub_bc2c590                  7 call site(s)
  sub_bc2cd20                  7 call site(s)
  sub_bc2d550                  7 call site(s)
  sub_bc2dd20                  7 call site(s)
  sub_bc2eb50                  7 call site(s)
  sub_bc2f4a0                  7 call site(s)
  sub_bc36140                  7 call site(s)
  sub_bc38c20                  5 call site(s)
  sub_bc5bad0                  5 call site(s)
  sub_bc5f8d0                  4 call site(s)
  sub_bc5fb30                  4 call site(s)
  sub_bc5fce0                  1 call site(s)
  sub_bc60f10                  1 call site(s)
  sub_bc62040                  1 call site(s)
  sub_bc62bc0                  1 call site(s)
  sub_bc63b80                  3 call site(s)
  sub_bc63c80                  6 call site(s)
  sub_bc65180                  3 call site(s)
  sub_bc65800                  1 call site(s)
  sub_bc660a0                  17 call site(s)
  sub_bc66de0                  10 call site(s)
  sub_bc68e40                  105 call site(s)
  sub_bc6a9d0                  1 call site(s)
  sub_bc6abd0                  8 call site(s)
  sub_bc6db00                  6 call site(s)
  sub_bc6e1e0                  2 call site(s)
  sub_bc6f0a0                  4 call site(s)
  sub_bc6f2a0                  2 call site(s)
  sub_bc6f4d0                  5 call site(s)
  sub_bc6f800                  2 call site(s)
  sub_bc6f910                  4 call site(s)
  sub_bc6fdc0                  5 call site(s)
  sub_bc70060                  5 call site(s)
  sub_bc70240                  4 call site(s)
  sub_bc70800                  5 call site(s)
  sub_bc70aa0                  5 call site(s)
  sub_bc70ca0                  5 call site(s)
  sub_bc70ff0                  4 call site(s)
  sub_bc71140                  5 call site(s)
  sub_bc716a0                  12 call site(s)
  sub_bc71990                  12 call site(s)
  sub_bc71c80                  2 call site(s)
  sub_bc71da0                  4 call site(s)
  sub_bc71f60                  5 call site(s)
  s
```

## callees
```
sub_ebce390  [0xebce390..0xebd2390)
  call sub_aa3c0                    x4
  call sub_e951550                  x2
  call sub_e9e7970                  x2
  call sub_ebcd3e0                  x60
  call sub_ebcd590                  x2
  call sub_ebcd6f0                  x4
  call sub_ebce390                  x7
  call sub_ebce3a0                  x1
  call sub_ebce5e0                  x2
  call sub_ebcf430                  x2
  call sub_ebcf4e0                  x1
  call sub_ebd15b0                  x1
  call sub_ebd1f80                  x1
  call sub_ebd3fa0                  x8
  call sub_ebd4110                  x10
  call sub_ebd4650                  x1
  call sub_ebda860                  x1
  call sub_ebdaf30                  x1
  call sub_ebdb4d0                  x1
  call sub_ed35da0                  x1
  call sub_eec6ec0                  x1
  str  ebcf612  "BkMGTPEZY"
  str  ebcf674  "BkMGTPEZY"
  str  ebcf6aa  "%0.2f %c%c%c"
  str  ebd20fc  "Unrecognized image format."

```

## stores into [reg+off] (non-stack)
```
  ebce50f  mov byte ptr [rax+rbx],0                      
  ebce6a5  mov byte ptr [rbx+rsi],0                      
  ebce740  mov byte ptr [rbx+rsi],0                      
```

## listing (600 instr)
```
sub_ebce390  [0xebce390..0xebd0390)  size 0x2000  843 xrefs in
  ebce390  jmp 0xEEC6EC0                                 ; -> sub_eec6ec0
  ebce395  int3                                          
  ebce396  int3                                          
  ebce397  int3                                          
  ebce398  int3                                          
  ebce399  int3                                          
  ebce39a  int3                                          
  ebce39b  int3                                          
  ebce39c  int3                                          
  ebce39d  int3                                          
  ebce39e  int3                                          
  ebce39f  int3                                          
  ebce3a0  test r9d,r9d                                  
  ebce3a3  je short 0xEBCE414                            ; -> loc_ebce414
  ebce3a5  push rbx                                      
  ebce3a6  push rdi                                      
  ebce3a7  sub rsp,0x28                                  
  ebce3ab  mov [rsp+0x40],rbp                            
  ebce3b0  mov rdi,rdx                                   
  ebce3b3  mov [rsp+0x48],rsi                            
  ebce3b8  mov rbx,rcx                                   
  ebce3bb  mov [rsp+0x50],r14                            
  ebce3c0  mov r14d,[rsp+0x60]                           
  ebce3c5  mov [rsp+0x20],r15                            
  ebce3ca  mov r15d,[rsp+0x68]                           
  ebce3cf  mov ebp,r8d                                   
  ebce3d2  mov esi,r9d                                   
  ebce3d5  nop [rax+rax]                                 

loc_ebce3e0:  ; from ebce3f8
  ebce3e0  mov r8,rbp                                    
  ebce3e3  mov rdx,rdi                                   
  ebce3e6  mov rcx,rbx                                   
  ebce3e9  call 0xEEC6EC0                                ; -> sub_eec6ec0
  ebce3ee  add rdi,r14                                   
  ebce3f1  add rbx,r15                                   
  ebce3f4  sub rsi,1                                     
  ebce3f8  jne short 0xEBCE3E0                           ; -> loc_ebce3e0
  ebce3fa  mov r15,[rsp+0x20]                            
  ebce3ff  mov r14,[rsp+0x50]                            
  ebce404  mov rsi,[rsp+0x48]                            
  ebce409  mov rbp,[rsp+0x40]                            
  ebce40e  add rsp,0x28                                  
  ebce412  pop rdi                                       
  ebce413  pop rbx                                       

loc_ebce414:  ; from ebce3a3
  ebce414  ret                                           
  ebce415  int3                                          
  ebce416  int3                                          
  ebce417  int3                                          
  ebce418  int3                                          
  ebce419  int3                                          
  ebce41a  int3                                          
  ebce41b  int3                                          
  ebce41c  int3                                          
  ebce41d  int3                                          
  ebce41e  int3                                          
  ebce41f  int3                                          
  ebce420  jmp 0xEEC6DE0                                 ; -> sub_eec6de0
  ebce425  int3                                          
  ebce426  int3                                          
  ebce427  int3                                          
  ebce428  int3                                          
  ebce429  int3                                          
  ebce42a  int3                                          
  ebce42b  int3                                          
  ebce42c  int3                                          
  ebce42d  int3                                          
  ebce42e  int3                                          
  ebce42f  int3                                          
  ebce430  movzx edx,dl                                  
  ebce433  jmp 0xEEC6ED0                                 ; -> sub_eec6ed0
  ebce438  int3                                          
  ebce439  int3                                          
  ebce43a  int3                                          
  ebce43b  int3                                          
  ebce43c  int3                                          
  ebce43d  int3                                          
  ebce43e  int3                                          
  ebce43f  int3                                          
  ebce440  jmp 0xEEC6EB0                                 ; -> sub_eec6eb0
  ebce445  int3                                          
  ebce446  int3                                          
  ebce447  int3                                          
  ebce448  int3                                          
  ebce449  int3                                          
  ebce44a  int3                                          
  ebce44b  int3                                          
  ebce44c  int3                                          
  ebce44d  int3                                          
  ebce44e  int3                                          
  ebce44f  int3                                          
  ebce450  xchg ax,ax                                    
  ebce452  int3                                          
  ebce453  ret                                           
  ebce454  int3                                          
  ebce455  int3                                          
  ebce456  int3                                          
  ebce457  int3                                          
  ebce458  int3                                          
  ebce459  int3                                          
  ebce45a  int3                                          
  ebce45b  int3                                          
  ebce45c  int3                                          
  ebce45d  int3                                          
  ebce45e  int3                                          
  ebce45f  int3                                          
  ebce460  jmp qword ptr [0xF9A7630]                     ; [data_f9a7630]
  ebce467  int3                                          
  ebce468  int3                                          
  ebce469  int3                                          
  ebce46a  int3                                          
  ebce46b  int3                                          
  ebce46c  int3                                          
  ebce46d  int3                                          
  ebce46e  int3                                          
  ebce46f  int3                                          
  ebce470  push rbp                                      
  ebce472  push rdi                                      
  ebce473  push r14                                      
  ebce475  mov eax,0x2030                                
  ebce47a  call 0xE9E7970                                ; -> sub_e9e7970
  ebce47f  sub rsp,rax                                   
  ebce482  lea rbp,[rsp+0x20]                            
  ebce487  mov [rbp+0x2040],rbx                          
  ebce48e  mov [rbp+0x2048],rsi                          
  ebce495  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
  ebce49c  xor rax,rbp                                   
  ebce49f  mov [rbp+0x2000],rax                          
  ebce4a6  mov r14,rdx                                   
  ebce4a9  lea rbx,[rbp]                                 
  ebce4ad  mov rsi,rcx                                   
  ebce4b0  mov r9,rdx                                    
  ebce4b3  mov r8,rcx                                    
  ebce4b6  mov edx,0x2000                                
  ebce4bb  lea rcx,[rbp]                                 
  ebce4bf  call 0xEBCF430                                ; -> sub_ebcf430
  ebce4c4  mov edi,eax                                   
  ebce4c6  cmp eax,0x2000                                
  ebce4cb  jle short 0xEBCE509                           ; -> loc_ebce509
  ebce4cd  lea ecx,[rax+1]                               ; R ret@ebcf430+0x1
  ebce4d0  movsxd rdx,ecx                                
  ebce4d3  lea rax,[rdx+0xF]                             
  ebce4d7  cmp rax,rdx                                   
  ebce4da  ja short 0xEBCE4E6                            ; -> loc_ebce4e6
  ebce4dc  mov rax,0xFFFFFFFFFFFFFF0                     

loc_ebce4e6:  ; from ebce4da
  ebce4e6  and rax,0xFFFFFFFFFFFFFFF0                    
  ebce4ea  call 0xE9E7970                                ; -> sub_e9e7970
  ebce4ef  sub rsp,rax                                   
  ebce4f2  mov r9,r14                                    
  ebce4f5  mov r8,rsi                                    
  ebce4f8  mov edx,edi                                   
  ebce4fa  lea rbx,[rsp+0x20]                            
  ebce4ff  mov rcx,rbx                                   
  ebce502  call 0xEBCF430                                ; -> sub_ebcf430
  ebce507  mov edi,eax                                   

loc_ebce509:  ; from ebce4cb
  ebce509  movsxd rax,edi                                
  ebce50c  mov rcx,rbx                                   
  ebce50f  mov byte ptr [rax+rbx],0                      
  ebce513  call qword ptr [0xF9A7630]                    ; [data_f9a7630]
  ebce519  mov rcx,[rbp+0x2000]                          
  ebce520  xor rcx,rbp                                   
  ebce523  call 0xE951550                                ; -> sub_e951550
  ebce528  mov rbx,[rbp+0x2040]                          
  ebce52f  mov rsi,[rbp+0x2048]                          
  ebce536  lea rsp,[rbp+0x2010]                          
  ebce53d  pop r14                                       
  ebce53f  pop rdi                                       
  ebce540  pop rbp                                       
  ebce541  ret                                           
  ebce542  int3                                          
  ebce543  int3                                          
  ebce544  int3                                          
  ebce545  int3                                          
  ebce546  int3                                          
  ebce547  int3                                          
  ebce548  int3                                          
  ebce549  int3                                          
  ebce54a  int3                                          
  ebce54b  int3                                          
  ebce54c  int3                                          
  ebce54d  int3                                          
  ebce54e  int3                                          
  ebce54f  int3                                          
  ebce550  movsx eax,cl                                  
  ebce553  xor edx,edx                                   
  ebce555  sub eax,0x61                                  
  ebce558  mov r8d,0x20                                  
  ebce55e  cmp eax,0x19                                  
  ebce561  cmovbe edx,r8d                                
  ebce565  sub cl,dl                                     
  ebce567  movzx eax,cl                                  
  ebce56a  ret                                           
  ebce56b  int3                                          
  ebce56c  int3                                          
  ebce56d  int3                                          
  ebce56e  int3                                          
  ebce56f  int3                                          
  ebce570  cmp [rdx+8],r8d                               
  ebce574  mov r11d,r8d                                  
  ebce577  mov r9,[rdx]                                  
  ebce57a  mov r10d,r8d                                  
  ebce57d  cmovl r11d,[rdx+8]                            
  ebce582  cmp [rcx+8],r8d                               
  ebce586  mov rdx,[rcx]                                 
  ebce589  cmovl r10d,[rcx+8]                            
  ebce58e  cmp r10d,r11d                                 
  ebce591  mov eax,r10d                                  
  ebce594  cmovge eax,r11d                               
  ebce598  test eax,eax                                  
  ebce59a  jle short 0xEBCE5C2                           ; -> loc_ebce5c2
  ebce59c  nop [rax]                                     

loc_ebce5a0:  ; from ebce5c0
  ebce5a0  movzx ecx,byte ptr [r9]                       
  ebce5a4  movzx r8d,byte ptr [rdx]                      
  ebce5a8  cmp r8b,cl                                    
  ebce5ab  jne short 0xEBCE5CC                           ; -> loc_ebce5cc
  ebce5ad  test r8b,r8b                                  
  ebce5b0  je short 0xEBCE5CC                            ; -> loc_ebce5cc
  ebce5b2  test cl,cl                                    
  ebce5b4  je short 0xEBCE5CC                            ; -> loc_ebce5cc
  ebce5b6  inc rdx                                       
  ebce5b9  inc r9                                        
  ebce5bc  dec eax                                       
  ebce5be  test eax,eax                                  
  ebce5c0  jg short 0xEBCE5A0                            ; -> loc_ebce5a0

loc_ebce5c2:  ; from ebce59a
  ebce5c2  jne short 0xEBCE5CC                           ; -> loc_ebce5cc
  ebce5c4  cmp r10d,r11d                                 
  ebce5c7  jne short 0xEBCE5CC                           ; -> loc_ebce5cc
  ebce5c9  xor eax,eax                                   
  ebce5cb  ret                                           

loc_ebce5cc:  ; from ebce5ab, ebce5b0, ebce5b4, ebce5c2, ebce5c7
  ebce5cc  movsx eax,byte ptr [rdx]                      
  ebce5cf  movsx ecx,byte ptr [r9]                       
  ebce5d3  sub eax,ecx                                   
  ebce5d5  ret                                           
  ebce5d6  int3                                          
  ebce5d7  int3                                          
  ebce5d8  int3                                          
  ebce5d9  int3                                          
  ebce5da  int3                                          
  ebce5db  int3                                          
  ebce5dc  int3                                          
  ebce5dd  int3                                          
  ebce5de  int3                                          
  ebce5df  int3                                          
  ebce5e0  test rcx,rcx                                  
  ebce5e3  jne short 0xEBCE5E8                           ; -> loc_ebce5e8
  ebce5e5  xor eax,eax                                   
  ebce5e7  ret                                           

loc_ebce5e8:  ; from ebce5e3
  ebce5e8  mov rax,rcx                                   
  ebce5eb  test edx,edx                                  
  ebce5ed  jle short 0xEBCE5FE                           ; -> loc_ebce5fe
  ebce5ef  nop                                           

loc_ebce5f0:  ; from ebce5fc
  ebce5f0  cmp byte ptr [rax],0                          
  ebce5f3  je short 0xEBCE5FE                            ; -> loc_ebce5fe
  ebce5f5  inc rax                                       
  ebce5f8  dec edx                                       
  ebce5fa  test edx,edx                                  
  ebce5fc  jg short 0xEBCE5F0                            ; -> loc_ebce5f0

loc_ebce5fe:  ; from ebce5ed, ebce5f3
  ebce5fe  sub eax,ecx                                   
  ebce600  ret                                           
  ebce601  int3                                          
  ebce602  int3                                          
  ebce603  int3                                          
  ebce604  int3                                          
  ebce605  int3                                          
  ebce606  int3                                          
  ebce607  int3                                          
  ebce608  int3                                          
  ebce609  int3                                          
  ebce60a  int3                                          
  ebce60b  int3                                          
  ebce60c  int3                                          
  ebce60d  int3                                          
  ebce60e  int3                                          
  ebce60f  int3                                          
  ebce610  cmp [rcx+8],edx                               
  ebce613  mov r8,[rcx]                                  
  ebce616  cmovl edx,[rcx+8]                             
  ebce61a  test r8,r8                                    
  ebce61d  jne short 0xEBCE622                           ; -> loc_ebce622
  ebce61f  xor eax,eax                                   
  ebce621  ret                                           

loc_ebce622:  ; from ebce61d
  ebce622  mov rax,r8                                    
  ebce625  test edx,edx                                  
  ebce627  jle short 0xEBCE63E                           ; -> loc_ebce63e
  ebce629  nop [rax]                                     

loc_ebce630:  ; from ebce63c
  ebce630  cmp byte ptr [rax],0                          
  ebce633  je short 0xEBCE63E                            ; -> loc_ebce63e
  ebce635  inc rax                                       
  ebce638  dec edx                                       
  ebce63a  test edx,edx                                  
  ebce63c  jg short 0xEBCE630                            ; -> loc_ebce630

loc_ebce63e:  ; from ebce627, ebce633
  ebce63e  sub eax,r8d                                   
  ebce641  ret                                           
  ebce642  int3                                          
  ebce643  int3                                          
  ebce644  int3                                          
  ebce645  int3                                          
  ebce646  int3                                          
  ebce647  int3                                          
  ebce648  int3                                          
  ebce649  int3                                          
  ebce64a  int3                                          
  ebce64b  int3                                          
  ebce64c  int3                                          
  ebce64d  int3                                          
  ebce64e  int3                                          
  ebce64f  int3                                          
  ebce650  mov [rsp+8],rbx                               
  ebce655  mov [rsp+0x10],rsi                            
  ebce65a  push rdi                                      
  ebce65b  sub rsp,0x20                                  
  ebce65f  cmp [r8+8],r9d                                
  ebce663  mov edi,edx                                   
  ebce665  mov rdx,[r8]                                  
  ebce668  mov rsi,rcx                                   
  ebce66b  cmovl r9d,[r8+8]                              
  ebce670  test rdx,rdx                                  
  ebce673  jne short 0xEBCE679                           ; -> loc_ebce679
  ebce675  xor eax,eax                                   
  ebce677  jmp short 0xEBCE693                           ; -> loc_ebce693

loc_ebce679:  ; from ebce673
  ebce679  mov rax,rdx                                   
  ebce67c  test r9d,r9d                                  
  ebce67f  jle short 0xEBCE691                           ; -> loc_ebce691

loc_ebce681:  ; from ebce68f
  ebce681  cmp byte ptr [rax],0                          
  ebce684  je short 0xEBCE691                            ; -> loc_ebce691
  ebce686  inc rax                                       
  ebce689  dec r9d                                       
  ebce68c  test r9d,r9d                                  
  ebce68f  jg short 0xEBCE681                            ; -> loc_ebce681

loc_ebce691:  ; from ebce67f, ebce684
  ebce691  sub eax,edx                                   

loc_ebce693:  ; from ebce677
  ebce693  dec edi                                       
  ebce695  cmp eax,edi                                   
  ebce697  cmovl edi,eax                                 
  ebce69a  movsxd rbx,edi                                
  ebce69d  mov r8,rbx                                    
  ebce6a0  call 0xEBCE390                                ; -> sub_ebce390
  ebce6a5  mov byte ptr [rbx+rsi],0                      
  ebce6a9  mov eax,edi                                   
  ebce6ab  mov rbx,[rsp+0x30]                            
  ebce6b0  mov rsi,[rsp+0x38]                            
  ebce6b5  add rsp,0x20                                  
  ebce6b9  pop rdi                                       
  ebce6ba  ret                                           
  ebce6bb  int3                                          
  ebce6bc  int3                                          
  ebce6bd  int3                                          
  ebce6be  int3                                          
  ebce6bf  int3                                          
  ebce6c0  mov [rsp+8],rbx                               
  ebce6c5  mov [rsp+0x10],rsi                            
  ebce6ca  push rdi                                      
  ebce6cb  sub rsp,0x20                                  
  ebce6cf  cmp [r8+8],r9d                                
  ebce6d3  mov edi,edx                                   
  ebce6d5  mov rdx,[r8]                                  
  ebce6d8  mov r10,rcx                                   
  ebce6db  cmovl r9d,[r8+8]                              
  ebce6e0  xor eax,eax                                   
  ebce6e2  mov r8d,edi                                   
  ebce6e5  test rcx,rcx                                  
  ebce6e8  jne short 0xEBCE6EE                           ; -> loc_ebce6ee
  ebce6ea  mov ecx,eax                                   
  ebce6ec  jmp short 0xEBCE704                           ; -> loc_ebce704

loc_ebce6ee:  ; from ebce6e8
  ebce6ee  test edi,edi                                  
  ebce6f0  jle short 0xEBCE701                           ; -> loc_ebce701

loc_ebce6f2:  ; from ebce6ff
  ebce6f2  cmp [rcx],al                                  
  ebce6f4  je short 0xEBCE701                            ; -> loc_ebce701
  ebce6f6  inc rcx                                       
  ebce6f9  dec r8d                                       
  ebce6fc  test r8d,r8d                                  
  ebce6ff  jg short 0xEBCE6F2                            ; -> loc_ebce6f2

loc_ebce701:  ; from ebce6f0, ebce6f4
  ebce701  sub ecx,r10d                                  

loc_ebce704:  ; from ebce6ec
  ebce704  movsxd rsi,ecx                                
  ebce707  add rsi,r10                                   
  ebce70a  test rdx,rdx                                  
  ebce70d  je short 0xEBCE729                            ; -> loc_ebce729
  ebce70f  mov rax,rdx                                   
  ebce712  test r9d,r9d                                  
  ebce715  jle short 0xEBCE727                           ; -> loc_ebce727

loc_ebce717:  ; from ebce725
  ebce717  cmp byte ptr [rax],0                          
  ebce71a  je short 0xEBCE727                            ; -> loc_ebce727
  ebce71c  inc rax                                       
  ebce71f  dec r9d                                       
  ebce722  test r9d,r9d                                  
  ebce725  jg short 0xEBCE717                            ; -> loc_ebce717

loc_ebce727:  ; from ebce715, ebce71a
  ebce727  sub eax,edx                                   

loc_ebce729:  ; from ebce70d
  ebce729  sub edi,ecx                                   
  ebce72b  mov rcx,rsi                                   
  ebce72e  dec edi                                       
  ebce730  cmp eax,edi                                   
  ebce732  cmovl edi,eax                                 
  ebce735  movsxd rbx,edi                                
  ebce738  mov r8,rbx                                    
  ebce73b  call 0xEBCE390                                ; -> sub_ebce390
  ebce740  mov byte ptr [rbx+rsi],0                      
  ebce744  mov eax,edi                                   
  ebce746  mov rbx,[rsp+0x30]                            
  ebce74b  mov rsi,[rsp+0x38]                            
  ebce750  add rsp,0x20                                  
  ebce754  pop rdi                                       
  ebce755  ret                                           
  ebce756  int3                                          
  ebce757  int3                                          
  ebce758  int3                                          
  ebce759  int3                                          
  ebce75a  int3                                          
  ebce75b  int3                                          
  ebce75c  int3                                          
  ebce75d  int3                                          
  ebce75e  int3                                          
  ebce75f  int3                                          
  ebce760  mov r9,[rcx]                                  
  ebce763  movzx r10d,dl                                 
  ebce767  mov r8d,[rcx+8]                               
  ebce76b  test r9,r9                                    
  ebce76e  jne short 0xEBCE774                           ; -> loc_ebce774
  ebce770  xor eax,eax                                   
  ebce772  jmp short 0xEBCE793                           ; -> loc_ebce793

loc_ebce774:  ; from ebce76e
  ebce774  mov rax,r9                                    
  ebce777  test r8d,r8d                                  
  ebce77a  jle short 0xEBCE790                           ; -> loc_ebce790
  ebce77c  nop [rax]                                     

loc_ebce780:  ; from ebce78e
  ebce780  cmp byte ptr [rax],0                          
  ebce783  je short 0xEBCE790                            ; -> loc_ebce790
  ebce785  inc rax                                       
  ebce788  dec r8d                                       
  ebce78b  test r8d,r8d                                  
  ebce78e  jg short 0xEBCE780                            ; -> loc_ebce780

loc_ebce790:  ; from ebce77a, ebce783
  ebce790  sub eax,r9d                                   

loc_ebce793:  ; from ebce772
  ebce793  xor ecx,ecx                                   
  ebce795  movsxd rdx,eax                                
  ebce798  test eax,eax                                  
  ebce79a  jle short 0xEBCE7B0                           ; -> loc_ebce7b0
  ebce79c  xor eax,eax                                   
  ebce79e  xchg ax,ax                                    

loc_ebce7a0:  ; from ebce7ae
  ebce7a0  cmp [r9+rax],r10b                             
  ebce7a4  je short 0xEBCE7B3                            ; -> loc_ebce7b3
  ebce7a6  inc ecx                                       
  ebce7a8  inc rax                                       
  ebce7ab  cmp rax,rdx                                   
  ebce7ae  jl short 0xEBCE7A0                            ; -> loc_ebce7a0

loc_ebce7b0:  ; from ebce79a
  ebce7b0  xor eax,eax                                   
  ebce7b2  ret                                           

loc_ebce7b3:  ; from ebce7a4
  ebce7b3  movsxd rax,ecx                                
  ebce7b6  add rax,r9                                    
  ebce7b9  ret                                           
  ebce7ba  int3                                          
  ebce7bb  int3                                          
  ebce7bc  int3                                          
  ebce7bd  int3                                          
  ebce7be  int3                                          
  ebce7bf  int3                                          
  ebce7c0  push rdi                                      
  ebce7c2  cmp [rdx+8],r8d                               
  ebce7c6  mov r9d,r8d                                   
  ebce7c9  mov rdi,[rdx]                                 
  ebce7cc  cmovl r9d,[rdx+8]                             
  ebce7d1  mov rdx,[rcx]                                 
  ebce7d4  mov r8d,[rcx+8]                               
  ebce7d8  test rdx,rdx                                  
  ebce7db  jne short 0xEBCE7E1                           ; -> loc_ebce7e1
  ebce7dd  xor eax,eax                                   
  ebce7df  jmp short 0xEBCE802                           ; -> loc_ebce802

loc_ebce7e1:  ; from ebce7db
  ebce7e1  mov rax,rdx                                   
  ebce7e4  test r8d,r8d                                  
  ebce7e7  jle short 0xEBCE800                           ; -> loc_ebce800
  ebce7e9  nop [rax]                                     

loc_ebce7f0:  ; from ebce7fe
  ebce7f0  cmp byte ptr [rax],0                          
  ebce7f3  je short 0xEBCE800                            ; -> loc_ebce800
  ebce7f5  inc rax                                       
  ebce7f8  dec r8d                                       
  ebce7fb  test r8d,r8d                                  
  ebce7fe  jg short 0xEBCE7F0                            ; -> loc_ebce7f0

loc_ebce800:  ; from ebce7e7, ebce7f3
  ebce800  sub eax,edx                                   

loc_ebce802:  ; from ebce7df
  ebce802  test rdi,rdi                                  
  ebce805  jne short 0xEBCE80C                           ; -> loc_ebce80c
  ebce807  xor r10d,r10d                                 
  ebce80a  jmp short 0xEBCE828                           ; -> loc_ebce828

loc_ebce80c:  ; from ebce805
  ebce80c  mov r10,rdi                                   
  ebce80f  test r9d,r9d                                  
  ebce812  jle short 0xEBCE825                           ; -> loc_ebce825

loc_ebce814:  ; from ebce823
  ebce814  cmp byte ptr [r10],0                          
  ebce818  je short 0xEBCE825                            ; -> loc_ebce825
  ebce81a  inc r10                                       
  ebce81d  dec r9d                                       
  ebce820  test r9d,r9d                                  
  ebce823  jg short 0xEBCE814                            ; -> loc_ebce814

loc_ebce825:  ; from ebce812, ebce818
  ebce825  sub r10d,edi                                  

loc_ebce828:  ; from ebce80a
  ebce828  mov [rsp+0x10],rbx                            
  ebce82d  cmp eax,r10d                                  
  ebce830  jl short 0xEBCE881                            ; -> loc_ebce881
  ebce832  movzx ebx,byte ptr [rdi]                      

loc_ebce835:  ; from ebce87f
  ebce835  cmp [rdx],bl                                  
  ebce837  je short 0xEBCE84E                            ; -> loc_ebce84e
  ebce839  nop [rax]                                     

loc_ebce840:  ; from ebce84c
  ebce840  inc rdx                                       
  ebce843  dec eax                                       
  ebce845  cmp r10d,eax                                  
  ebce848  jg short 0xEBCE881                            ; -> loc_ebce881
  ebce84a  cmp [rdx],bl                                  
  ebce84c  jne short 0xEBCE840                           ; -> loc_ebce840

loc_ebce84e:  ; from ebce837
  ebce84e  lea rcx,[rdx+1]                               
  ebce852  mov r11,rdi                                   
  ebce855  mov r8,rcx                                    
  ebce858  sub r11,rcx                                   
  ebce85b  nop [rax+rax]                                 

loc_ebce860:  ; from ebce875
  ebce860  movzx r9d,byte ptr [r11+r8+1]                 
  ebce866  test r9b,r9b                                  
  ebce869  je short 0xEBCE88A                            ; -> loc_ebce88a
  ebce86b  movzx ecx,byte ptr [r8]                       
  ebce86f  inc r8                                        
  ebce872  cmp cl,r9b                                    
  ebce875  je short 0xEBCE860                            ; -> loc_ebce860
  ebce877  inc rdx                                       
  ebce87a  dec eax                                       
  ebce87c  cmp eax,r10d                                  
  ebce87f  jge short 0xEBCE835                           ; -> loc_ebce835

loc_ebce881:  ; from ebce830, ebce848
  ebce881  xor eax,eax                                   
  ebce883  mov rbx,[rsp+0x10]                            
  ebce888  pop rdi                                       
  ebce889  ret                                           

loc_ebce88a:  ; from ebce869
  ebce88a  mov rbx,[rsp+0x10]                            
  ebce88f  mov rax,rdx                                   
  ebce892  pop rdi                                       
  ebce893  ret                                           
  ebce894  int3                                          
  ebce895  int3                                          
  ebce896  int3                                          
  ebce897  int3                                          
  ebce898  int3                                          
  ebce899  int3                                          
  ebce89a  int3                                          
  ebce89b  int3                                          
  ebce89c  int3                                          
  ebce89d  int3                                          
  ebce89e  int3                                          
  ebce89f  int3                                          
  ebce8a0  mov [rsp+8],rbx                               
  ebce8a5  mov [rsp+0x10],rbp                            
  ebce8aa  mov [rsp+0x18],rsi                            
  ebce8af  mov [rsp+0x20],rdi                            
  ebce8b4  push r14                                      
  ebce8b6  push r15                                      
  ebce8b8  cmp byte ptr [rcx],0                          
  ebce8bb  mov rsi,rcx                                   
  ebce8be  je 0xEBCEB37                                  ; -> loc_ebceb37
  ebce8c4  lea rbp,[0xF847A07]                           ; [data_f847a07]
  ebce8cb  lea r14,[0xF84B1BC]                           ; [data_f84b1bc]
  ebce8d2  lea r15,[0xF84B1C0]                           ; [data_f84b1c0]
  ebce8d9  nop [rax]                                     

loc_ebce8e0:  ; from ebceb31
  ebce8e0  mov eax,0x7FFFFFFF                            
  ebce8e5  mov rcx,r14                                   

loc_ebce8e8:  ; from ebce8f4
  ebce8e8  cmp byte ptr [rcx],0                          
  ebce8eb  je short 0xEBCE8F6                            ; -> loc_ebce8f6
  ebce8ed  inc rcx                                       
  ebce8f0  dec eax                                       
  ebce8f2  test eax,eax                                  
  ebce8f4  jg short 0xEBCE8E8                            ; -> loc_ebce8e8

loc_ebce8f6:  ; from ebce8eb
  ebce8f6  sub ecx,r14d                                  
  ebce8f9  mov r9,r14                                    
  ebce8fc  mov rdi,r14                                   
  ebce8ff  mov edx,0x400                                 
  ebce904  cmove r9,rbp                                  
  ebce908  mov rax,rsi                                   
  ebce90b  test ecx,ecx                                  
  ebce90d  cmove rdi,rbp                                 

loc_ebce911:  ; from ebce936
  ebce911  cmp byte ptr [rax],0                          
  ebce914  je short 0xEBCE938                            ; -> loc_ebce938
  ebce916  inc rax                                       
  ebce919  cmp byte ptr [rax],0                          
  ebce91c  je short 0xEBCE938                            ; -> loc_ebce938
  ebce91e  inc rax                                       
  ebce921  cmp byte ptr [rax],0                          
  ebce924  je short 0xEBCE938                            ; -> loc_ebce938
  ebce926  inc rax                                       
  ebce929  cmp byte ptr [rax],0                          
  ebce92c  je short 0xEBCE938                            ; -> loc_ebce938
  ebce92e  inc rax                                       
  ebce931  sub edx,4                                     
  ebce934  test edx,edx                                  
  ebce936  jg short 0xEBCE911                            ; -> loc_ebce911

loc_ebce938:  ; from ebce914, ebce91c, ebce924, ebce92c
  ebce938  sub eax,esi                                   
  ebce93a  mov r8d,0x7FFFFFFF                            
  ebce940  mov rdx,rbp                                   
  ebce943  cmovne rdx,rsi                                
  ebce947  cmp ecx,r8d                                   
  ebce94a  cmovl r8d,ecx                                 
  ebce94e  test rdx,rdx                                  
  ebce951  jne short 0xEBCE957                           ; -> loc_ebce957
  ebce953  xor ecx,ecx                                   
  ebce955  jmp short 0xEBCE970                           ; -> loc_ebce970

loc_ebce957:  ; from ebce951
  ebce957  mov rcx,rdx                                   
  ebce95a  test eax,eax                                  
  ebce95c  jle short 0xEBCE96E                           ; -> loc_ebce96e
  ebce95e  xchg ax,ax                                    

loc_ebce960:  ; from ebce96c
  ebce960  cmp byte ptr [rcx],0                          
  ebce963  je short 0xEBCE96E                            ; -> loc_ebce96e
  ebce965  inc rcx                                       
  ebce968  dec eax                                       
  ebce96a  test eax,eax                                  
  ebce96c  jg short 0xEBCE960                            ; -> loc_ebce960

loc_ebce96e:  ; from ebce95c, ebce963
  ebce96e  sub ecx,edx                                   
  ... (--max 600)

```
