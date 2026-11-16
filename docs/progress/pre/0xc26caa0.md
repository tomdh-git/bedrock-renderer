# preflight 0xc26caa0

## fn
```
sub_c26caa0  [0xc26caa0..0xc26f21a)  size 0x277a  2 xrefs in
  c26caa0  push rbp                                      
  c26caa1  push r15                                      
  c26caa3  push r14                                      
  c26caa5  push r13                                      
  c26caa7  push r12                                      
  c26caa9  push rsi                                      
  c26caaa  push rdi                                      
  c26caab  push rbx                                      
  c26caac  sub rsp,0x598                                 
  c26cab3  lea rbp,[rsp+0x80]                            
  c26cabb  movdqa [rbp+0x500],xmm7                       
  c26cac3  movaps [rbp+0x4F0],xmm6                       
  c26caca  mov qword ptr [rbp+0x4E8],0xFFFFFFFFFFFFFFFE  
  c26cad5  mov [rbp+0x1D8],rdx                           
  c26cadc  mov rdi,rcx                                   
  c26cadf  lea r14,[rbp+0x228]                           
  c26cae6  lea rax,[r8+0xB0]                             ; R a2+0xB0
  c26caed  mov [rbp+0x3C8],rax                           
  c26caf4  lea rax,[r8+0x30]                             ; R a2+0x30
  c26caf8  mov [rbp+0x1A0],rax                           
  c26caff  lea rax,[r8+0x170]                            ; R a2+0x170
  c26cb06  mov [rbp+0x1D0],rax                           
  c26cb0d  xorps xmm6,xmm6                               
  c26cb10  pcmpeqd xmm7,xmm7                             
  c26cb14  lea rax,[r8+0x68]                             ; R a2+0x68
  c26cb18  mov [rbp+0x478],rax                           
  c26cb1f  lea rax,[r8+0x118]                            ; R a2+0x118
  c26cb26  mov [rbp+0x1C8],rax                           
  c26cb2d  mov [rbp+0x4D8],r8                            
  c26cb34  movzx eax,byte ptr [r8+0x1C8]                 ; R a2+0x1C8
  c26cb3c  nop [rax]                                     
  c26cb40  cmp al,3                                      
  c26cb42  ja 0xC26F1DB                                  ; -> loc_c26f1db
  c26cb48  movzx eax,al                                  
  c26cb4b  lea rcx,[0xF478D70]                           ; [data_f478d70]
  c26cb52  movsxd rax,[rcx+rax*4]                        
  c26cb56  add rax,rcx                                   
  c26cb59  jmp rax                                       
  c26cb5b  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  c26cb62  mov rax,[rcx]                                 
  ... (--max 40)

```

## callers
```
  sub_66117f0                  1 call site(s)
  sub_c269790                  1 call site(s)
-- 2 calling function(s)

```

## callees
```
sub_c26caa0  [0xc26caa0..0xc26f21a)
  call sub_75720                    x1
  call sub_9d6d0                    x4
  call sub_b2450                    x1
  call sub_1166e0                   x2
  call sub_393660                   x2
  call sub_3946b0                   x1
  call sub_58f1b0                   x4
  call sub_6ae330                   x1
  call sub_9bc830                   x16
  call sub_9bd2e0                   x9
  call sub_b432e0                   x1
  call sub_1751590                  x1
  call sub_24af560                  x1
  call sub_6611410                  x5
  call sub_6755280                  x2
  call sub_6755820                  x2
  call sub_67559d0                  x3
  call sub_6755b50                  x2
  call sub_6755c40                  x4
  call sub_67580d0                  x1
  call sub_bc5f110                  x1
  call sub_bcbf640                  x1
  call sub_c25cb40                  x1
  call sub_c25cd00                  x1
  call sub_c272e10                  x1
  call sub_c273060                  x1
  call sub_c283d50                  x1
  call sub_c283f10                  x1
  call sub_c284020                  x1
  call sub_c284720                  x1
  call sub_c287b30                  x1
  call sub_e8fc640                  x1
  call sub_e903290                  x1
  call sub_e903360                  x1
  call sub_e9045b0                  x1
  call sub_e935700                  x15
  call sub_ebce390                  x1
  call sub_eec5870                  x10
  call sub_eec6d80                  x1
  call sub_eec6de0                  x2
  call sub_eec6ec0                  x1
  str  c26d178  "materials.index.json"
  str  c26d213  "materials.index.json"
  str  c26d241  ".material.bin"
  str  c26d3ca  "Only backbuffer pointer and native window handle can be chan..."

```

## stores into [reg+off] (non-stack)
```
  c26cb81  movups [rsi+0xE0],xmm6                        
  c26cb88  movups [rsi+0xD0],xmm6                        
  c26cb8f  movups [rsi+0xC0],xmm6                        
  c26cb96  movups [rsi+0xB0],xmm6                        
  c26cb9d  movups [rsi+0xA0],xmm6                        
  c26cba4  movups [rsi+0x90],xmm6                        
  c26cbab  movups [rsi+0x80],xmm6                        
  c26cbb2  movups [rsi+0x70],xmm6                        
  c26cbb6  movups [rsi+0x60],xmm6                        
  c26cbba  movups [rsi+0x50],xmm6                        
  c26cbbe  movups [rsi+0x40],xmm6                        
  c26cbc2  movups [rsi+0x30],xmm6                        
  c26cbc6  movups [rsi+0x20],xmm6                        
  c26cbca  movups [rsi+0x10],xmm6                        
  c26cbde  mov byte ptr [rsi+0x50],0                     
  c26cbed  movups [rsi+0x58],xmm6                        
  c26cbf1  mov qword ptr [rsi+0x68],0                    
  c26cbf9  mov qword ptr [rsi+0x70],0xF                  
  c26cc01  movups [rsi+0x78],xmm6                        
  c26cc05  mov qword ptr [rsi+0x88],0x200000             
  c26cc1a  mov [rsi+0x90],rax                            
  c26cc57  mov word ptr [r13+0xD8],0                     
  c26cc61  movups [r13+0xE0],xmm6                        
  c26cd2c  mov [r12+8],rax                               
  c26cd31  mov [r12+0x40],rsi                            
  c26cd3b  mov [r12+0x48],rax                            
  c26cd40  mov [r12+0x50],rax                            
  c26cd4a  mov dword ptr [r12+0x58],0                    
  c26cd53  movups [r12+0x60],xmm6                        
  c26cd59  movups [r12+0x70],xmm6                        
  c26cd5f  movups [r12+0x80],xmm6                        
  c26cd68  movups [r12+0x90],xmm6                        
  c26cd71  mov qword ptr [r12+0xA0],0                    
  c26cda3  mov [r12+0xB0],rax                            
  c26cdab  mov [r12+0xE8],r15                            
  c26cdbb  mov [r12+0xF0],rax                            
  c26cdc3  mov [r12+0xF8],rax                            
  c26cdd3  mov dword ptr [r12+0x100],0                   
  c26cddf  movups [r12+0x108],xmm6                       
  c26cde8  movups [r12+0x118],xmm6                       
  c26cdf1  movups [r12+0x128],xmm6                       
  c26cdfa  movups [r12+0x138],xmm6                       
  c26ce03  mov qword ptr [r12+0x148],0                   
  c26ce26  mov [r12+0x158],rbx                           
  c26ce2e  mov [r12+0x160],rdi                           
  c26ce36  mov [r12+0x168],r13                           
  c26ce4d  mov [r12+0x170],rax                           
  c26ce55  mov [r12+0x1A8],rbx                           
  c26ce65  mov [r12+0x1B0],rax                           
  c26ce6d  mov [r12+0x1B8],rax                           
  c26ce7d  mov dword ptr [r12+0x1C0],0                   
  c26ce89  movups [r12+0x1C8],xmm6                       
  c26ce92  movups [r12+0x1D8],xmm6                       
  c26ce9b  movups [r12+0x1E8],xmm6                       
  c26cea4  movups [r12+0x1F8],xmm6                       
  c26cead  mov qword ptr [r12+0x208],0                   
  c26ced0  mov qword ptr [r12+0x250],0                   
  c26cfc4  mov [rdi+8],r12                               ; W a0+0x8
  c26cfe8  mov [rdi+0x28],eax                            ; W a0+0x28
  c26cfee  mov [rdi+0x2C],eax                            ; W a0+0x2C
  c26cff1  mov dword ptr [rdi+0x30],0x80                 ; W a0+0x30
  c26d03c  movups [rax+0x18],xmm6                        
  c26d040  mov qword ptr [rax+0x28],0                    
  c26d117  mov qword ptr [rax+0x10],0                    
  c26d21d  mov dword ptr [rax+0x10],0x6E6F736A           
  c26d224  mov byte ptr [rax+0x14],0                     
  c26d279  mov [rax+5],rcx                               
  c26d28a  mov byte ptr [rax+0xD],0                      
  c26d383  mov qword ptr [rdx+0x10],0                    
  c26d40f  mov [rcx+4],eax                               
  c26d695  movups [rax+0x10],xmm6                        
  c26d7f4  mov [rdx+0x90],rax                            
  c26d7ff  movups [rdx+0x80],xmm0                        
  c26d816  movups [rdx+0xA8],xmm1                        
  c26d81d  movups [rdx+0x98],xmm0                        
  c26d84f  mov [rdx+0xBE],rcx                            
  c26d856  mov [rdx+0xB8],rax                            
  c26d864  mov [rdx+0xE8],rax                            
  c26d87b  movups [rdx+0xD8],xmm1                        
  c26d882  movups [rdx+0xC8],xmm0                        
  c26d9a2  mov byte ptr [r15+rbx],0                      
  c26d9e5  mov [r8+8],edx                                
  c26da1d  mov [r8+8],edx                                
  c26da27  movups [r8+0x10],xmm6                         
  c26da63  movups [rdx+0x20],xmm6                        
  c26dcb8  mov [r14+0x170],ecx                           
  c26dcc3  mov [r14+0x168],rcx                           
  c26dcfa  mov [r14+0x170],ecx                           
  c26dd05  mov [r14+0x168],rcx                           
  c26dd2b  movaps [rdx+0x10],xmm6                        
  c26de1d  mov [rdx+0x90],rax                            
  c26de27  movups [rdx+0x80],xmm0                        
  c26de3e  movups [rdx+0xA8],xmm1                        
  c26de45  movups [rdx+0x98],xmm0                        
  c26de77  mov [rdx+0xBE],rcx                            
  c26de7e  mov [rdx+0xB8],rax                            
  c26de8c  mov [rdx+0xE8],rax                            
  c26dea3  movups [rdx+0xD8],xmm1                        
  c26deaa  movups [rdx+0xC8],xmm0                        
  c26e21d  mov byte ptr [r15+rbx],0                      
  c26e22e  movups [rax+0x48],xmm0                        
  c26e379  mov [rdi+0x18],r12                            
```

## listing (1200 instr)
```
sub_c26caa0  [0xc26caa0..0xc26eaa0)  size 0x2000  2 xrefs in
  c26caa0  push rbp                                      
  c26caa1  push r15                                      
  c26caa3  push r14                                      
  c26caa5  push r13                                      
  c26caa7  push r12                                      
  c26caa9  push rsi                                      
  c26caaa  push rdi                                      
  c26caab  push rbx                                      
  c26caac  sub rsp,0x598                                 
  c26cab3  lea rbp,[rsp+0x80]                            
  c26cabb  movdqa [rbp+0x500],xmm7                       
  c26cac3  movaps [rbp+0x4F0],xmm6                       
  c26caca  mov qword ptr [rbp+0x4E8],0xFFFFFFFFFFFFFFFE  
  c26cad5  mov [rbp+0x1D8],rdx                           
  c26cadc  mov rdi,rcx                                   
  c26cadf  lea r14,[rbp+0x228]                           
  c26cae6  lea rax,[r8+0xB0]                             ; R a2+0xB0
  c26caed  mov [rbp+0x3C8],rax                           
  c26caf4  lea rax,[r8+0x30]                             ; R a2+0x30
  c26caf8  mov [rbp+0x1A0],rax                           
  c26caff  lea rax,[r8+0x170]                            ; R a2+0x170
  c26cb06  mov [rbp+0x1D0],rax                           
  c26cb0d  xorps xmm6,xmm6                               
  c26cb10  pcmpeqd xmm7,xmm7                             
  c26cb14  lea rax,[r8+0x68]                             ; R a2+0x68
  c26cb18  mov [rbp+0x478],rax                           
  c26cb1f  lea rax,[r8+0x118]                            ; R a2+0x118
  c26cb26  mov [rbp+0x1C8],rax                           
  c26cb2d  mov [rbp+0x4D8],r8                            
  c26cb34  movzx eax,byte ptr [r8+0x1C8]                 ; R a2+0x1C8
  c26cb3c  nop [rax]                                     
  c26cb40  cmp al,3                                      
  c26cb42  ja 0xC26F1DB                                  ; -> sub_c26f1db
  c26cb48  movzx eax,al                                  
  c26cb4b  lea rcx,[0xF478D70]                           ; [data_f478d70]
  c26cb52  movsxd rax,[rcx+rax*4]                        
  c26cb56  add rax,rcx                                   
  c26cb59  jmp rax                                       
  c26cb5b  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  c26cb62  mov rax,[rcx]                                 
  c26cb65  mov rax,[rax+8]                               
  c26cb69  mov edx,0xF0                                  
  c26cb6e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26cb74  nop                                           
  c26cb75  mov rsi,rax                                   
  c26cb78  test rax,rax                                  
  c26cb7b  je 0xC26F028                                  ; -> sub_c26f028
  c26cb81  movups [rsi+0xE0],xmm6                        
  c26cb88  movups [rsi+0xD0],xmm6                        
  c26cb8f  movups [rsi+0xC0],xmm6                        
  c26cb96  movups [rsi+0xB0],xmm6                        
  c26cb9d  movups [rsi+0xA0],xmm6                        
  c26cba4  movups [rsi+0x90],xmm6                        
  c26cbab  movups [rsi+0x80],xmm6                        
  c26cbb2  movups [rsi+0x70],xmm6                        
  c26cbb6  movups [rsi+0x60],xmm6                        
  c26cbba  movups [rsi+0x50],xmm6                        
  c26cbbe  movups [rsi+0x40],xmm6                        
  c26cbc2  movups [rsi+0x30],xmm6                        
  c26cbc6  movups [rsi+0x20],xmm6                        
  c26cbca  movups [rsi+0x10],xmm6                        
  c26cbce  movups [rsi],xmm6                             
  c26cbd1  mov rcx,rsi                                   
  c26cbd4  mov edx,2                                     
  c26cbd9  call 0xEEC5870                                ; -> sub_eec5870
  c26cbde  mov byte ptr [rsi+0x50],0                     
  c26cbe2  lea rax,[rsi+0x58]                            
  c26cbe6  mov [rbp+0x4D0],rax                           
  c26cbed  movups [rsi+0x58],xmm6                        
  c26cbf1  mov qword ptr [rsi+0x68],0                    
  c26cbf9  mov qword ptr [rsi+0x70],0xF                  
  c26cc01  movups [rsi+0x78],xmm6                        
  c26cc05  mov qword ptr [rsi+0x88],0x200000             
  c26cc10  mov rax,0x2540BE400                           
  c26cc1a  mov [rsi+0x90],rax                            
  c26cc21  mov rcx,rsi                                   
  c26cc24  add rcx,0x98                                  
  c26cc2b  mov dword ptr [rbp+0x220],0                   
  c26cc35  lea rdx,[rbp+0x220]                           
  c26cc3c  lea r8,[rbp+0x3D0]                            
  c26cc43  mov [rbp+0x4E0],rsi                           
  c26cc4a  call 0x24AF560                                ; -> sub_24af560
  c26cc4f  nop                                           
  c26cc50  mov r13,[rbp+0x4E0]                           
  c26cc57  mov word ptr [r13+0xD8],0                     
  c26cc61  movups [r13+0xE0],xmm6                        
  c26cc69  mov rbx,[rdi]                                 ; R a0+0x0
  c26cc6c  mov [rdi],r13                                 ; W a0+0x0
  c26cc6f  test rbx,rbx                                  
  c26cc72  je short 0xC26CC8C                            ; -> loc_c26cc8c
  c26cc74  mov rcx,rbx                                   
  c26cc77  call 0xE8FC640                                ; -> sub_e8fc640
  c26cc7c  mov edx,0xF0                                  
  c26cc81  mov rcx,rbx                                   
  c26cc84  call 0xE935700                                ; -> sub_e935700
  c26cc89  mov r13,[rdi]                                 ; R a0+0x0

loc_c26cc8c:  ; from c26cc72
  c26cc8c  mov rbx,[rdi+0x20]                            ; R a0+0x20
  c26cc90  mov rax,[rbp+0x4D8]                           
  c26cc97  mov r15,[rax+0x58]                            
  c26cc9b  mov sil,[rax+0x60]                            
  c26cc9f  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  c26cca6  mov rax,[rcx]                                 
  c26cca9  mov rax,[rax+8]                               
  c26ccad  mov edx,0x258                                 
  c26ccb2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26ccb8  nop                                           
  c26ccb9  mov r12,rax                                   
  c26ccbc  test rax,rax                                  
  c26ccbf  je 0xC26F038                                  ; -> sub_c26f038
  c26ccc5  mov byte ptr [rbp+0x260],0                    
  c26cccc  cmp sil,1                                     
  c26ccd0  jne short 0xC26CD15                           ; -> loc_c26cd15
  c26ccd2  mov qword ptr [rbp+0x258],0                   
  c26ccdd  test r15,r15                                  
  c26cce0  je short 0xC26CD0E                            ; -> loc_c26cd0e
  c26cce2  mov [rbp+0x4E0],r12                           
  c26cce9  mov rax,[r15]                                 
  c26ccec  mov rax,[rax]                                 
  c26ccef  mov rcx,r15                                   
  c26ccf2  lea rdx,[rbp+0x220]                           
  c26ccf9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26ccff  nop                                           
  c26cd00  mov [rbp+0x258],rax                           
  c26cd07  mov r12,[rbp+0x4E0]                           

loc_c26cd0e:  ; from c26cce0
  c26cd0e  mov byte ptr [rbp+0x260],1                    

loc_c26cd15:  ; from c26ccd0
  c26cd15  lea rax,[0xF478980]                           ; [data_f478980]
  c26cd1c  mov [r12],rax                                 
  c26cd20  lea rsi,[r12+8]                               
  c26cd25  lea rax,[0xF478A50]                           ; [data_f478a50]
  c26cd2c  mov [r12+8],rax                               
  c26cd31  mov [r12+0x40],rsi                            
  c26cd36  lea rax,[r12+0x48]                            
  c26cd3b  mov [r12+0x48],rax                            
  c26cd40  mov [r12+0x50],rax                            
  c26cd45  lea rcx,[r12+0x58]                            
  c26cd4a  mov dword ptr [r12+0x58],0                    
  c26cd53  movups [r12+0x60],xmm6                        
  c26cd59  movups [r12+0x70],xmm6                        
  c26cd5f  movups [r12+0x80],xmm6                        
  c26cd68  movups [r12+0x90],xmm6                        
  c26cd71  mov qword ptr [r12+0xA0],0                    
  c26cd7d  mov edx,2                                     
  c26cd82  call 0xEEC5870                                ; -> sub_eec5870
  c26cd87  lea rcx,[r12+0xA8]                            
  c26cd8f  call 0x9BD2E0                                 ; -> sub_9bd2e0
  c26cd94  lea r15,[r12+0xB0]                            
  c26cd9c  lea rax,[0xF478A80]                           ; [data_f478a80]
  c26cda3  mov [r12+0xB0],rax                            
  c26cdab  mov [r12+0xE8],r15                            
  c26cdb3  lea rax,[r12+0xF0]                            
  c26cdbb  mov [r12+0xF0],rax                            
  c26cdc3  mov [r12+0xF8],rax                            
  c26cdcb  lea rcx,[r12+0x100]                           
  c26cdd3  mov dword ptr [r12+0x100],0                   
  c26cddf  movups [r12+0x108],xmm6                       
  c26cde8  movups [r12+0x118],xmm6                       
  c26cdf1  movups [r12+0x128],xmm6                       
  c26cdfa  movups [r12+0x138],xmm6                       
  c26ce03  mov qword ptr [r12+0x148],0                   
  c26ce0f  mov edx,2                                     
  c26ce14  call 0xEEC5870                                ; -> sub_eec5870
  c26ce19  lea rcx,[r12+0x150]                           
  c26ce21  call 0x9BD2E0                                 ; -> sub_9bd2e0
  c26ce26  mov [r12+0x158],rbx                           
  c26ce2e  mov [r12+0x160],rdi                           
  c26ce36  mov [r12+0x168],r13                           
  c26ce3e  lea rbx,[r12+0x170]                           
  c26ce46  lea rax,[0xF478AB0]                           ; [data_f478ab0]
  c26ce4d  mov [r12+0x170],rax                           
  c26ce55  mov [r12+0x1A8],rbx                           
  c26ce5d  lea rax,[r12+0x1B0]                           
  c26ce65  mov [r12+0x1B0],rax                           
  c26ce6d  mov [r12+0x1B8],rax                           
  c26ce75  lea rcx,[r12+0x1C0]                           
  c26ce7d  mov dword ptr [r12+0x1C0],0                   
  c26ce89  movups [r12+0x1C8],xmm6                       
  c26ce92  movups [r12+0x1D8],xmm6                       
  c26ce9b  movups [r12+0x1E8],xmm6                       
  c26cea4  movups [r12+0x1F8],xmm6                       
  c26cead  mov qword ptr [r12+0x208],0                   
  c26ceb9  mov edx,2                                     
  c26cebe  call 0xEEC5870                                ; -> sub_eec5870
  c26cec3  lea rcx,[r12+0x210]                           
  c26cecb  call 0x9BD2E0                                 ; -> sub_9bd2e0
  c26ced0  mov qword ptr [r12+0x250],0                   
  c26cedc  cmp byte ptr [rbp+0x260],1                    
  c26cee3  jne 0xC26CFC0                                 ; -> loc_c26cfc0
  c26cee9  mov rdx,r12                                   
  c26ceec  add rdx,0x218                                 
  c26cef3  mov qword ptr [rbp+0x408],0                   
  c26cefe  mov rcx,[rbp+0x258]                           
  c26cf05  test rcx,rcx                                  
  c26cf08  je short 0xC26CF56                            ; -> loc_c26cf56
  c26cf0a  mov [rbp+0x4D0],rdx                           
  c26cf11  mov [rbp+0x1B0],rbx                           
  c26cf18  mov [rbp+0x1A8],r15                           
  c26cf1f  mov [rbp+0x4C8],rsi                           
  c26cf26  mov [rbp+0x4E0],r12                           
  c26cf2d  mov rax,[rcx]                                 
  c26cf30  mov rax,[rax]                                 
  c26cf33  lea rdx,[rbp+0x3D0]                           
  c26cf3a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26cf40  nop                                           
  c26cf41  mov [rbp+0x408],rax                           
  c26cf48  mov r12,[rbp+0x4E0]                           
  c26cf4f  mov rdx,[rbp+0x4D0]                           

loc_c26cf56:  ; from c26cf08
  c26cf56  lea rsi,[rbp+0x3D0]                           
  c26cf5d  mov rcx,rsi                                   
  c26cf60  call 0xB2450                                  ; -> sub_b2450
  c26cf65  mov rcx,[rbp+0x408]                           
  c26cf6c  test rcx,rcx                                  
  c26cf6f  je short 0xC26CF84                            ; -> loc_c26cf84
  c26cf71  cmp rcx,rsi                                   
  c26cf74  setne dl                                      
  c26cf77  mov rax,[rcx]                                 
  c26cf7a  mov rax,[rax+0x20]                            
  c26cf7e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_c26cf84:  ; from c26cf6f
  c26cf84  cmp byte ptr [rbp+0x260],1                    
  c26cf8b  jne short 0xC26CFC0                           ; -> loc_c26cfc0
  c26cf8d  mov rcx,[rbp+0x258]                           
  c26cf94  test rcx,rcx                                  
  c26cf97  je short 0xC26CFC0                            ; -> loc_c26cfc0
  c26cf99  lea rax,[rbp+0x220]                           
  c26cfa0  cmp rcx,rax                                   
  c26cfa3  setne dl                                      
  c26cfa6  mov rax,[rcx]                                 
  c26cfa9  mov rax,[rax+0x20]                            
  c26cfad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26cfb3  nop [rax+rax]                                 

loc_c26cfc0:  ; from c26cee3, c26cf8b, c26cf97
  c26cfc0  mov rcx,[rdi+8]                               ; R a0+0x8
  c26cfc4  mov [rdi+8],r12                               ; W a0+0x8
  c26cfc8  test rcx,rcx                                  
  c26cfcb  je short 0xC26CFDE                            ; -> loc_c26cfde
  c26cfcd  mov rax,[rcx]                                 ; R *(a0+0x8)+0x0
  c26cfd0  mov rax,[rax]                                 ; R *(*(a0+0x8)+0x0)+0x0
  c26cfd3  mov edx,1                                     
  c26cfd8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_c26cfde:  ; from c26cfcb
  c26cfde  mov rcx,[rbp+0x4D8]                           
  c26cfe5  mov eax,[rcx+0x14]                            
  c26cfe8  mov [rdi+0x28],eax                            ; W a0+0x28
  c26cfeb  mov eax,[rcx+0x18]                            
  c26cfee  mov [rdi+0x2C],eax                            ; W a0+0x2C
  c26cff1  mov dword ptr [rdi+0x30],0x80                 ; W a0+0x30
  c26cff8  movaps [rbp+0x200],xmm6                       
  c26cfff  movaps [rbp+0x1F0],xmm6                       
  c26d006  movaps [rbp+0x1E0],xmm6                       
  c26d00d  lea rax,[rbp+0x490]                           
  c26d014  mov word ptr [rax-8],0                        
  c26d01a  mov dword ptr [rax-0xC],0                     
  c26d021  mov rdx,0x2D000000500                         
  c26d02b  mov [rbp+0x48C],rdx                           
  c26d032  mov dword ptr [rbp+0x494],0                   
  c26d03c  movups [rax+0x18],xmm6                        
  c26d040  mov qword ptr [rax+0x28],0                    
  c26d048  mov word ptr [rbp+0x498],8                    
  c26d051  mov rax,0x20000000600000                      
  c26d05b  mov [rbp+0x49C],rax                           
  c26d062  mov byte ptr [rbp+0x4A4],1                    
  c26d069  movzx edx,word ptr [rcx+0x10]                 
  c26d06d  lea rcx,[rbp+0x1B8]                           
  c26d074  call 0xE903290                                ; -> sub_e903290
  c26d079  nop                                           
  c26d07a  movzx ebx,word ptr [rbp+0x1B8]                
  c26d081  mov r15d,3                                    
  c26d087  test ebx,0x100                                
  c26d08d  je short 0xC26D0C0                            ; -> loc_c26d0c0
  c26d08f  mov ecx,ebx                                   
  c26d091  call 0xE903360                                ; -> sub_e903360
  c26d096  nop                                           
  c26d097  test al,al                                    
  c26d099  je short 0xC26D0C0                            ; -> loc_c26d0c0
  c26d09b  dec bl                                        
  c26d09d  xor r15d,r15d                                 
  c26d0a0  cmp bl,0xA                                    
  c26d0a3  ja short 0xC26D0C0                            ; -> loc_c26d0c0
  c26d0a5  movzx eax,bl                                  
  c26d0a8  lea rcx,[0xF440E10]                           ; [data_f440e10]
  c26d0af  mov r15d,[rcx+rax*4]                          
  c26d0b3  nop [rax+rax]                                 

loc_c26d0c0:  ; from c26d08d, c26d099, c26d0a3
  c26d0c0  mov rcx,[rbp+0x4D8]                           
  c26d0c7  movzx eax,byte ptr [rcx+8]                    
  c26d0cb  test eax,eax                                  
  c26d0cd  je 0xC26D371                                  ; -> loc_c26d371
  c26d0d3  cmp eax,1                                     
  c26d0d6  jne 0xC26F20D                                 ; -> sub_c26f20d
  c26d0dc  xor eax,eax                                   
  c26d0de  xor ecx,ecx                                   
  c26d0e0  xor r15d,r15d                                 
  c26d0e3  jmp 0xC26D379                                 ; -> loc_c26d379
  c26d0e8  nop [rax+rax]                                 
  c26d0f0  movaps [rbp+0x3D0],xmm6                       
  c26d0f7  mov qword ptr [rbp+0x3E0],0                   
  c26d102  mov qword ptr [rbp+0x3E8],0xF                 
  c26d10d  lea rax,[rbp+0x3F0]                           
  c26d114  movups [rax],xmm6                             
  c26d117  mov qword ptr [rax+0x10],0                    
  c26d11f  mov qword ptr [rbp+0x408],0xF                 
  c26d12a  lea rax,[0xEFD2D90]                           ; [data_efd2d90]
  c26d131  mov [rbp+0x220],rax                           
  c26d138  mov qword ptr [rbp+0x228],0                   
  c26d143  lea rcx,[rbp+0x410]                           
  c26d14a  lea rdx,[rbp+0x220]                           
  c26d151  call 0x3946B0                                 ; -> sub_3946b0
  c26d156  nop                                           
  c26d157  mov byte ptr [rbp+0x470],0                    
  c26d15e  cmp qword ptr [rbp+0x408],0x14                
  c26d166  jae 0xC26D201                                 ; -> loc_c26d201
  c26d16c  mov edx,0x14                                  
  c26d171  lea rcx,[rbp+0x3F0]                           
  c26d178  lea r9,[0xF5831EB]                            ; [data_f5831eb] "materials.index.json"
  c26d17f  call 0x9D6D0                                  ; -> sub_9d6d0
  c26d184  nop                                           
  c26d185  jmp 0xC26D228                                 ; -> loc_c26d228
  c26d18a  nop [rax+rax]                                 ; R ret@9d6d0+0x0+idx
  c26d190  mov byte ptr [rbp+0x188],3                    
  c26d197  jmp 0xC26EF8F                                 ; -> sub_c26ef8f
  c26d19c  nop [rax]                                     ; R ret@9d6d0+0x0
  c26d1a0  mov rcx,[rdi+0x20]                            ; R a0+0x20
  c26d1a4  mov byte ptr [rbp+0x4C0],0xFF                 
  c26d1ab  mov rax,[rbp+0x4D8]                           
  c26d1b2  movzx eax,byte ptr [rax+0x1A0]                
  c26d1b9  cmp rax,4                                     
  c26d1bd  ja 0xC26DAA6                                  ; -> loc_c26daa6
  c26d1c3  lea r8,[0xF478D80]                            ; [data_f478d80]
  c26d1ca  movsxd rdx,[r8+rax*4]                         
  c26d1ce  add rdx,r8                                    
  c26d1d1  jmp rdx                                       
  c26d1d3  movaps [rbp+0x480],xmm6                       
  c26d1da  mov r8,[rbp+0x4D8]                            
  c26d1e1  mov rdx,[r8+0x168]                            
  c26d1e8  test rdx,rdx                                  
  c26d1eb  je 0xC26D9BC                                  ; -> loc_c26d9bc
  c26d1f1  lock inc dword ptr [rdx+8]                    
  c26d1f5  mov rdx,[r8+0x168]                            
  c26d1fc  jmp 0xC26D9BE                                 ; -> loc_c26d9be

loc_c26d201:  ; from c26d166
  c26d201  mov rax,[rbp+0x3F0]                           
  c26d208  mov qword ptr [rbp+0x400],0x14                
  c26d213  movups xmm0,[0xF5831EB]                       ; [data_f5831eb] "materials.index.json"
  c26d21a  movups [rax],xmm0                             
  c26d21d  mov dword ptr [rax+0x10],0x6E6F736A           
  c26d224  mov byte ptr [rax+0x14],0                     

loc_c26d228:  ; from c26d185
  c26d228  mov rcx,[rbp+0x3E8]                           
  c26d22f  cmp rcx,0xD                                   
  c26d233  jae short 0xC26D250                           ; -> loc_c26d250
  c26d235  mov edx,0xD                                   
  c26d23a  lea rcx,[rbp+0x3D0]                           
  c26d241  lea r9,[0xF593224]                            ; [data_f593224] ".material.bin"
  c26d248  call 0x9D6D0                                  ; -> sub_9d6d0
  c26d24d  nop                                           
  c26d24e  jmp short 0xC26D28E                           ; -> loc_c26d28e

loc_c26d250:  ; from c26d233
  c26d250  lea rax,[rbp+0x3D0]                           
  c26d257  cmp rcx,0x10                                  
  c26d25b  jb short 0xC26D264                            ; -> loc_c26d264
  c26d25d  mov rax,[rbp+0x3D0]                           

loc_c26d264:  ; from c26d25b
  c26d264  mov qword ptr [rbp+0x3E0],0xD                 
  c26d26f  mov rcx,0x6E69622E6C616972                    
  c26d279  mov [rax+5],rcx                               
  c26d27d  mov rcx,0x6169726574616D2E                    
  c26d287  mov [rax],rcx                                 
  c26d28a  mov byte ptr [rax+0xD],0                      

loc_c26d28e:  ; from c26d24e
  c26d28e  movzx eax,byte ptr [rbp+0x470]                
  c26d295  mov rcx,[rbp+0x4D8]                           
  c26d29c  cmp byte ptr [rcx+0x28],1                     
  c26d2a0  jne short 0xC26D2FB                           ; -> loc_c26d2fb
  c26d2a2  cmp al,1                                      
  c26d2a4  jne 0xC26D68E                                 ; -> loc_c26d68e
  c26d2aa  lea rax,[rbp+0x448]                           
  c26d2b1  cmp rax,[rbp+0x4D8]                           
  c26d2b8  je 0xC26D9A7                                  ; -> loc_c26d9a7
  c26d2be  mov rax,[rbp+0x4D8]                           
  c26d2c5  cmp qword ptr [rax+0x18],0x10                 
  c26d2ca  mov r9,rax                                    
  c26d2cd  jb short 0xC26D2D2                            ; -> loc_c26d2d2
  c26d2cf  mov r9,[rax]                                  

loc_c26d2d2:  ; from c26d2cd
  c26d2d2  mov rbx,[rax+0x10]                            
  c26d2d6  mov rax,[rbp+0x460]                           
  c26d2dd  cmp rbx,rax                                   
  c26d2e0  jbe 0xC26D979                                 ; -> loc_c26d979
  c26d2e6  lea rcx,[rbp+0x448]                           
  c26d2ed  mov rdx,rbx                                   
  c26d2f0  call 0x9D6D0                                  ; -> sub_9d6d0
  c26d2f5  nop                                           
  c26d2f6  jmp 0xC26D9A7                                 ; -> loc_c26d9a7

loc_c26d2fb:  ; from c26d2a0
  c26d2fb  cmp al,1                                      
  c26d2fd  jne 0xC26DFB5                                 ; -> loc_c26dfb5
  c26d303  mov rax,[rbp+0x460]                           
  c26d30a  cmp rax,0x10                                  
  c26d30e  jb short 0xC26D348                            ; -> loc_c26d348
  c26d310  mov rcx,[rbp+0x448]                           
  c26d317  lea rdx,[rax+1]                               
  c26d31b  cmp rdx,0x1000                                
  c26d322  jb short 0xC26D343                            ; -> loc_c26d343
  c26d324  mov r8,[rcx-8]                                
  c26d328  add rcx,0xFFFFFFFFFFFFFFF8                    
  c26d32c  sub rcx,r8                                    
  c26d32f  cmp rcx,0x20                                  
  c26d333  jae 0xC26F1C1                                 ; -> sub_c26f1c1
  c26d339  add rax,0x28                                  
  c26d33d  mov rdx,rax                                   
  c26d340  mov rcx,r8                                    

loc_c26d343:  ; from c26d322
  c26d343  call 0xE935700                                ; -> sub_e935700

loc_c26d348:  ; from c26d30e
  c26d348  mov qword ptr [rbp+0x458],0                   
  c26d353  mov qword ptr [rbp+0x460],0xF                 
  c26d35e  mov byte ptr [rbp+0x448],0                    
  c26d365  mov byte ptr [rbp+0x470],0                    
  c26d36c  jmp 0xC26DFB5                                 ; -> loc_c26dfb5

loc_c26d371:  ; from c26d0cd
  c26d371  mov rax,[rcx]                                 
  c26d374  mov ecx,2                                     

loc_c26d379:  ; from c26d0e3
  c26d379  lea rdx,[rbp+0x1F0]                           
  c26d380  movups [rdx],xmm6                             
  c26d383  mov qword ptr [rdx+0x10],0                    
  c26d38b  mov qword ptr [rbp+0x1E0],0                   
  c26d396  mov [rbp+0x1E8],rax                           
  c26d39d  mov [rbp+0x208],rcx                           
  c26d3a4  mov [rbp+0x480],r15d                          
  c26d3ab  cmp qword ptr [0x12AE1748],0                  ; [data_12ae1748]
  c26d3b3  je short 0xC26D3D7                            ; -> loc_c26d3d7
  c26d3b5  mov rax,[0x12AE16D0]                          ; [data_12ae16d0]
  c26d3bc  or rax,[0x12AE16C0]                           ; [data_12ae16c0]
  c26d3c3  je short 0xC26D3D7                            ; -> loc_c26d3d7
  c26d3c5  mov ecx,2                                     
  c26d3ca  lea rdx,[0xF83E118]                           ; [data_f83e118] "Only backbuffer pointer and native window handle can be chan..."
  c26d3d1  call 0xBC5F110                                ; -> sub_bc5f110
  c26d3d6  nop                                           

loc_c26d3d7:  ; from c26d3b3, c26d3c3
  c26d3d7  mov r8d,0x30                                  
  c26d3dd  lea rcx,[0x12AE16C0]                          ; [data_12ae16c0]
  c26d3e4  lea rdx,[rbp+0x1E0]                           
  c26d3eb  call 0xEBCE390                                ; -> sub_ebce390
  c26d3f0  nop                                           
  c26d3f1  mov byte ptr [0x12AE1740],1                   ; [data_12ae1740]
  c26d3f8  mov word ptr [rbp+0x484],0                    
  c26d401  lea rdx,[rdi+0x28]                            
  c26d405  mov eax,[rdx+8]                               
  c26d408  lea rcx,[rbp+0x490]                           
  c26d40f  mov [rcx+4],eax                               
  c26d412  mov rax,[rdx]                                 
  c26d415  mov [rcx-4],rax                               
  c26d419  mov rcx,[rdi+0x20]                            
  c26d41d  mov rax,[rcx+0x148]                           
  c26d424  inc rax                                       
  c26d427  cmp rax,0x10000                               
  c26d42d  jae 0xC26F1E1                                 ; -> sub_c26f1e1
  c26d433  mov [rbp+0x498],ax                            
  c26d43a  cmp rax,0x10                                  
  c26d43e  mov edx,0x10                                  
  c26d443  cmovae rax,rdx                                
  c26d447  mov [rbp+0x4A4],al                            
  c26d44d  mov rax,[rdi+8]                               
  c26d451  mov [rbp+0x4A8],rax                           
  c26d458  mov rax,[rbp+0x4D8]                           
  c26d45f  movzx eax,byte ptr [rax+0x1C]                 
  c26d463  mov [rbp+0x488],al                            
  c26d469  test r15d,r15d                                
  c26d46c  je short 0xC26D4B4                            ; -> loc_c26d4b4
  c26d46e  mov qword ptr [rsp+0x20],0                    
  c26d477  lea rdx,[rbp+0x3D0]                           
  c26d47e  lea r8,[rbp+0x480]                            
  c26d485  xor r9d,r9d                                   
  c26d488  call 0xC25CB40                                ; -> sub_c25cb40
  c26d48d  nop                                           
  c26d48e  cmp byte ptr [rbp+0x410],4                    
  c26d495  jne 0xC26D5CC                                 ; -> loc_c26d5cc
  c26d49b  mov ecx,5                                     
  c26d4a0  lea rdx,[rbp+0x220]                           
  c26d4a7  lea r8,[rbp+0x3D0]                            
  c26d4ae  call 0x6755B50                                ; -> sub_6755b50
  c26d4b3  nop                                           

loc_c26d4b4:  ; from c26d46c
  c26d4b4  lea rcx,[rbp+0x220]                           
  c26d4bb  mov rdx,[rbp+0x478]                           
  c26d4c2  call 0x58F1B0                                 ; -> sub_58f1b0
  c26d4c7  nop                                           
  c26d4c8  mov qword ptr [rbp+0x288],0                   
  c26d4d3  mov rax,[rbp+0x4D8]                           
  c26d4da  mov rcx,[rax+0xD0]                            
  c26d4e1  test rcx,rcx                                  
  c26d4e4  je short 0xC26D501                            ; -> loc_c26d501
  c26d4e6  mov rax,[rcx]                                 
  c26d4e9  mov rax,[rax]                                 
  c26d4ec  lea rdx,[rbp+0x250]                           
  c26d4f3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26d4f9  nop                                           
  c26d4fa  mov [rbp+0x288],rax                           

loc_c26d501:  ; from c26d4e4
  c26d501  mov qword ptr [rbp+0x2C8],0                   
  c26d50c  mov rax,[rbp+0x4D8]                           
  c26d513  mov rcx,[rax+0x110]                           
  c26d51a  test rcx,rcx                                  
  c26d51d  je short 0xC26D53A                            ; -> loc_c26d53a
  c26d51f  mov rax,[rcx]                                 
  c26d522  mov rax,[rax]                                 
  c26d525  lea rdx,[rbp+0x290]                           
  c26d52c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26d532  nop                                           
  c26d533  mov [rbp+0x2C8],rax                           

loc_c26d53a:  ; from c26d51d
  c26d53a  lea rcx,[rbp+0x2D0]                           
  c26d541  mov rdx,[rbp+0x1C8]                           
  c26d548  call 0x6611410                                ; -> sub_6611410
  c26d54d  nop                                           
  c26d54e  mov byte ptr [rbp-0x18],0                     
  c26d552  cmp byte ptr [rbp+0x248],1                    
  c26d559  jne short 0xC26D59B                           ; -> loc_c26d59b
  c26d55b  movups xmm0,[rbp+0x220]                       
  c26d562  movups xmm1,[rbp+0x230]                       
  c26d569  movaps [rbp-0x30],xmm1                        
  c26d56d  movaps [rbp-0x40],xmm0                        
  c26d571  mov qword ptr [rbp+0x230],0                   
  c26d57c  mov qword ptr [rbp+0x238],0xF                 
  c26d587  mov byte ptr [rbp+0x220],0                    
  c26d58e  mov eax,[rbp+0x240]                           
  c26d594  mov [rbp-0x20],eax                            
  c26d597  mov byte ptr [rbp-0x18],1                     

loc_c26d59b:  ; from c26d559
  c26d59b  mov qword ptr [rbp+0x28],0                    
  c26d5a3  mov rcx,[rbp+0x288]                           
  c26d5aa  test rcx,rcx                                  
  c26d5ad  je 0xC26D779                                  ; -> loc_c26d779
  c26d5b3  lea rax,[rbp+0x250]                           
  c26d5ba  cmp rcx,rax                                   
  c26d5bd  je 0xC26D733                                  ; -> loc_c26d733
  c26d5c3  mov [rbp+0x28],rcx                            
  c26d5c7  jmp 0xC26D76E                                 ; -> loc_c26d76e

loc_c26d5cc:  ; from c26d495
  c26d5cc  lea rcx,[rbp+0x220]                           
  c26d5d3  mov rdx,[rbp+0x478]                           
  c26d5da  call 0x58F1B0                                 ; -> sub_58f1b0
  c26d5df  nop                                           
  c26d5e0  mov qword ptr [rbp+0x288],0                   
  c26d5eb  mov rax,[rbp+0x4D8]                           
  c26d5f2  mov rcx,[rax+0xD0]                            
  c26d5f9  test rcx,rcx                                  
  c26d5fc  je short 0xC26D619                            ; -> loc_c26d619
  c26d5fe  mov rax,[rcx]                                 
  c26d601  mov rax,[rax]                                 
  c26d604  lea rdx,[rbp+0x250]                           
  c26d60b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26d611  nop                                           
  c26d612  mov [rbp+0x288],rax                           

loc_c26d619:  ; from c26d5fc
  c26d619  mov qword ptr [rbp+0x2C8],0                   
  c26d624  mov rax,[rbp+0x4D8]                           
  c26d62b  mov rcx,[rax+0x110]                           
  c26d632  test rcx,rcx                                  
  c26d635  je short 0xC26D652                            ; -> loc_c26d652
  c26d637  mov rax,[rcx]                                 
  c26d63a  mov rax,[rax]                                 
  c26d63d  lea rdx,[rbp+0x290]                           
  c26d644  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26d64a  nop                                           
  c26d64b  mov [rbp+0x2C8],rax                           

loc_c26d652:  ; from c26d635
  c26d652  lea rcx,[rbp+0x2D0]                           
  c26d659  mov rdx,[rbp+0x1C8]                           
  c26d660  call 0x6611410                                ; -> sub_6611410
  c26d665  nop                                           
  c26d666  mov byte ptr [rbp+0x3C0],0xFF                 
  c26d66d  movzx eax,byte ptr [rbp+0x410]                
  c26d674  cmp rax,4                                     
  c26d678  ja 0xC26DD35                                  ; -> loc_c26dd35
  c26d67e  lea rdx,[0xF478DA8]                           ; [data_f478da8]
  c26d685  movsxd rcx,[rdx+rax*4]                        
  c26d689  add rcx,rdx                                   
  c26d68c  jmp rcx                                       

loc_c26d68e:  ; from c26d2a4
  c26d68e  lea rax,[rbp+0x448]                           
  c26d695  movups [rax+0x10],xmm6                        
  c26d699  movups [rax],xmm6                             
  c26d69c  mov rax,[rbp+0x4D8]                           
  c26d6a3  cmp qword ptr [rax+0x18],0x10                 
  c26d6a8  mov r15,rax                                   
  c26d6ab  jb short 0xC26D6B0                            ; -> loc_c26d6b0
  c26d6ad  mov r15,[rax]                                 

loc_c26d6b0:  ; from c26d6ab
  c26d6b0  mov r12,[rax+0x10]                            
  c26d6b4  test r12,r12                                  
  c26d6b7  js 0xC26F213                                  ; -> sub_c26f213
  c26d6bd  cmp r12,0xF                                   
  c26d6c1  ja 0xC26D91C                                  ; -> loc_c26d91c
  c26d6c7  mov [rbp+0x458],r12                           
  c26d6ce  mov qword ptr [rbp+0x460],0xF                 
  c26d6d9  movups xmm0,[r15]                             
  c26d6dd  lea rax,[rbp+0x448]                           
  c26d6e4  movups [rax],xmm0                             
  c26d6e7  jmp 0xC26DF9E                                 ; -> loc_c26df9e
  c26d6ec  mov rdx,[rbp+0x4D8]                           
  c26d6f3  movzx edx,byte ptr [rdx+0x160]                
  c26d6fa  mov [rbp+0x480],dl                            
  c26d700  jmp 0xC26DAA0                                 ; -> loc_c26daa0
  c26d705  movaps [rbp+0x480],xmm6                       
  c26d70c  mov r9,[rbp+0x4D8]                            
  c26d713  mov rdx,[r9+0x168]                            
  c26d71a  test rdx,rdx                                  
  c26d71d  je 0xC26D9F4                                  ; -> loc_c26d9f4
  c26d723  lock inc dword ptr [rdx+8]                    
  c26d727  mov rdx,[r9+0x168]                            
  c26d72e  jmp 0xC26D9F6                                 ; -> loc_c26d9f6

loc_c26d733:  ; from c26d5bd
  c26d733  mov rax,[rcx]                                 
  c26d736  mov rax,[rax+8]                               
  c26d73a  lea rdx,[rbp-0x10]                            
  c26d73e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26d744  mov [rbp+0x28],rax                            
  c26d748  mov rcx,[rbp+0x288]                           
  c26d74f  test rcx,rcx                                  
  c26d752  je short 0xC26D779                            ; -> loc_c26d779
  c26d754  lea rax,[rbp+0x250]                           
  c26d75b  cmp rcx,rax                                   
  c26d75e  setne dl                                      
  c26d761  mov rax,[rcx]                                 
  c26d764  mov rax,[rax+0x20]                            
  c26d768  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_c26d76e:  ; from c26d5c7
  c26d76e  mov qword ptr [rbp+0x288],0                   

loc_c26d779:  ; from c26d5ad, c26d752
  c26d779  mov qword ptr [rbp+0x68],0                    
  c26d781  mov rcx,[rbp+0x2C8]                           
  c26d788  test rcx,rcx                                  
  c26d78b  je short 0xC26D7E5                            ; -> loc_c26d7e5
  c26d78d  lea rax,[rbp+0x290]                           
  c26d794  cmp rcx,rax                                   
  c26d797  je short 0xC26D79F                            ; -> loc_c26d79f
  c26d799  mov [rbp+0x68],rcx                            
  c26d79d  jmp short 0xC26D7DA                           ; -> loc_c26d7da

loc_c26d79f:  ; from c26d797
  c26d79f  mov rax,[rcx]                                 
  c26d7a2  mov rax,[rax+8]                               
  c26d7a6  lea rdx,[rbp+0x30]                            
  c26d7aa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26d7b0  mov [rbp+0x68],rax                            
  c26d7b4  mov rcx,[rbp+0x2C8]                           
  c26d7bb  test rcx,rcx                                  
  c26d7be  je short 0xC26D7E5                            ; -> loc_c26d7e5
  c26d7c0  lea rax,[rbp+0x290]                           
  c26d7c7  cmp rcx,rax                                   
  c26d7ca  setne dl                                      
  c26d7cd  mov rax,[rcx]                                 
  c26d7d0  mov rax,[rax+0x20]                            
  c26d7d4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_c26d7da:  ; from c26d79d
  c26d7da  mov qword ptr [rbp+0x2C8],0                   

loc_c26d7e5:  ; from c26d78b, c26d7be
  c26d7e5  lea r8,[rbp+0x2D0]                            
  c26d7ec  mov rax,[r8+0x10]                             
  c26d7f0  lea rdx,[rbp-0x10]                            
  c26d7f4  mov [rdx+0x90],rax                            
  c26d7fb  movups xmm0,[r8]                              
  c26d7ff  movups [rdx+0x80],xmm0                        
  c26d806  movups xmm0,[r14+0xC0]                        
  c26d80e  movups xmm1,[r14+0xD0]                        
  c26d816  movups [rdx+0xA8],xmm1                        
  c26d81d  movups [rdx+0x98],xmm0                        
  c26d824  mov qword ptr [rbp+0x2F8],0                   
  c26d82f  mov qword ptr [rbp+0x300],0xF                 
  c26d83a  mov byte ptr [rbp+0x2E8],0                    
  c26d841  mov rax,[r14+0xE0]                            
  c26d848  mov rcx,[r14+0xE6]                            
  c26d84f  mov [rdx+0xBE],rcx                            
  c26d856  mov [rdx+0xB8],rax                            
  c26d85d  mov rax,[r14+0x110]                           
  c26d864  mov [rdx+0xE8],rax                            
  c26d86b  movups xmm0,[r14+0xF0]                        
  c26d873  movups xmm1,[r14+0x100]                       
  c26d87b  movups [rdx+0xD8],xmm1                        
  c26d882  movups [rdx+0xC8],xmm0                        
  c26d889  mov qword ptr [rbp+0x118],0                   
  c26d894  mov rcx,[rbp+0x378]                           
  c26d89b  test rcx,rcx                                  
  c26d89e  je short 0xC26D901                            ; -> loc_c26d901
  c26d8a0  lea rax,[rbp+0x340]                           
  c26d8a7  cmp rcx,rax                                   
  c26d8aa  je short 0xC26D8B5                            ; -> loc_c26d8b5
  c26d8ac  mov [rbp+0x118],rcx                           
  c26d8b3  jmp short 0xC26D8F6                           ; -> loc_c26d8f6

loc_c26d8b5:  ; from c26d8aa
  c26d8b5  mov rax,[rcx]                                 
  c26d8b8  mov rax,[rax+8]                               
  c26d8bc  lea rdx,[rbp+0xE0]                            
  c26d8c3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26d8c9  mov [rbp+0x118],rax                           
  c26d8d0  mov rcx,[rbp+0x378]                           
  c26d8d7  test rcx,rcx                                  
  c26d8da  je short 0xC26D901                            ; -> loc_c26d901
  c26d8dc  lea rax,[rbp+0x340]                           
  c26d8e3  cmp rcx,rax                                   
  c26d8e6  setne dl                                      
  c26d8e9  mov rax,[rcx]                                 
  c26d8ec  mov rax,[rax+0x20]                            
  c26d8f0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_c26d8f6:  ; from c26d8b3
  c26d8f6  mov qword ptr [rbp+0x378],0                   

loc_c26d901:  ; from c26d89e, c26d8da
  c26d901  mov byte ptr [rbp+0x188],2                    
  c26d908  lea rsi,[rbp+0x220]                           
  c26d90f  mov rcx,rsi                                   
  c26d912  call 0x6755C40                                ; -> sub_6755c40
  c26d917  jmp 0xC26EF96                                 ; -> sub_c26ef96

loc_c26d91c:  ; from c26d6c1
  c26d91c  mov rdx,r12                                   
  c26d91f  or rdx,0xF                                    
  c26d923  cmp rdx,0x17                                  
  c26d927  mov esi,0x16                                  
  c26d92c  cmovae rsi,rdx                                
  c26d930  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  c26d937  mov rax,[rcx]                                 
  c26d93a  mov rax,[rax+8]                               
  c26d93e  cmp rdx,0xFFF                                 
  c26d945  jb 0xC26DF5E                                  ; -> loc_c26df5e
  c26d94b  lea r13,[rsi+0x28]                            
  c26d94f  mov rdx,r13                                   
  c26d952  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26d958  nop                                           
  c26d959  mov rbx,rax                                   
  c26d95c  test rax,rax                                  
  c26d95f  je 0xC26F108                                  ; -> sub_c26f108
  c26d965  mov rax,rbx                                   
  c26d968  add rbx,0x27                                  
  c26d96c  and rbx,0xFFFFFFFFFFFFFFE0                    
  c26d970  mov [rbx-8],rax                               
  c26d974  jmp 0xC26DF78                                 ; -> loc_c26df78

loc_c26d979:  ; from c26d2e0
  c26d979  lea r15,[rbp+0x448]                           
  c26d980  cmp rax,0x10                                  
  c26d984  jb short 0xC26D98D                            ; -> loc_c26d98d
  c26d986  mov r15,[rbp+0x448]                           

loc_c26d98d:  ; from c26d984
  c26d98d  mov [rbp+0x458],rbx                           
  c26d994  mov rcx,r15                                   
  c26d997  mov rdx,r9                                    
  c26d99a  mov r8,rbx                                    
  c26d99d  call 0xEEC6DE0                                ; -> sub_eec6de0
  c26d9a2  mov byte ptr [r15+rbx],0                      

loc_c26d9a7:  ; from c26d2b8, c26d2f6
  c26d9a7  mov rax,[rbp+0x4D8]                           
  c26d9ae  mov eax,[rax+0x20]                            
  c26d9b1  mov [rbp+0x468],eax                           
  c26d9b7  jmp 0xC26DFB5                                 ; -> loc_c26dfb5

loc_c26d9bc:  ; from c26d1eb
  c26d9bc  xor edx,edx                                   

loc_c26d9be:  ; from c26d1fc
  c26d9be  mov r8,[r8+0x160]                             
  c26d9c5  mov [rbp+0x480],r8                            
  c26d9cc  mov [rbp+0x488],rdx                           
  c26d9d3  mov r9,[rbp+0x1D0]                            
  c26d9da  mov edx,[r9+8]                                
  c26d9de  lea r8,[rbp+0x490]                            
  c26d9e5  mov [r8+8],edx                                
  c26d9e9  mov rdx,[r9]                                  
  c26d9ec  mov [r8],rdx                                  
  c26d9ef  jmp 0xC26DAA0                                 ; -> loc_c26daa0

loc_c26d9f4:  ; from c26d71d
  c26d9f4  xor edx,edx                                   

loc_c26d9f6:  ; from c26d72e
  c26d9f6  mov r8,[r9+0x160]                             
  c26d9fd  mov [rbp+0x480],r8                            
  c26da04  mov [rbp+0x488],rdx                           
  c26da0b  mov r10,[rbp+0x1D0]                           
  c26da12  mov edx,[r10+8]                               
  c26da16  lea r8,[rbp+0x490]                            
  c26da1d  mov [r8+8],edx                                
  c26da21  mov rdx,[r10]                                 
  c26da24  mov [r8],rdx                                  
  c26da27  movups [r8+0x10],xmm6                         
  c26da2c  mov rdx,[r9+0x188]                            
  c26da33  test rdx,rdx                                  
  c26da36  je short 0xC26DA45                            ; -> loc_c26da45
  c26da38  lock inc dword ptr [rdx+8]                    
  c26da3c  mov rdx,[r9+0x188]                            
  c26da43  jmp short 0xC26DA47                           ; -> loc_c26da47

loc_c26da45:  ; from c26da36
  c26da45  xor edx,edx                                   

loc_c26da47:  ; from c26da43
  c26da47  mov r8,[r9+0x180]                             
  c26da4e  mov [rbp+0x4A0],r8                            
  c26da55  mov [rbp+0x4A8],rdx                           
  c26da5c  lea rdx,[rbp+0x490]                           
  c26da63  movups [rdx+0x20],xmm6                        
  c26da67  mov rdx,[r9+0x198]                            
  c26da6e  test rdx,rdx                                  
  c26da71  je short 0xC26DA80                            ; -> loc_c26da80
  c26da73  lock inc dword ptr [rdx+8]                    
  c26da77  mov rdx,[r9+0x198]                            
  c26da7e  jmp short 0xC26DA82                           ; -> loc_c26da82

loc_c26da80:  ; from c26da71
  c26da80  xor edx,edx                                   

loc_c26da82:  ; from c26da7e
  c26da82  mov r8,[r9+0x190]                             
  c26da89  mov [rbp+0x4B0],r8                            
  c26da90  mov [rbp+0x4B8],rdx                           
  c26da97  nop [rax+rax]                                 

loc_c26daa0:  ; from c26d700, c26d9ef
  c26daa0  mov [rbp+0x4C0],al                            

loc_c26daa6:  ; from c26d1bd
  c26daa6  lea rdx,[rbp+0x3D0]                           
  c26daad  lea r8,[rbp+0x480]                            
  c26dab4  call 0xC25CD00                                ; -> sub_c25cd00
  c26dab9  nop                                           
  c26daba  cmp byte ptr [rbp+0x410],4                    
  c26dac1  jne 0xC26DBDB                                 ; -> loc_c26dbdb
  c26dac7  lea rcx,[rbp+0x220]                           
  c26dace  mov rdx,[rbp+0x4D8]                           
  c26dad5  call 0x58F1B0                                 ; -> sub_58f1b0
  c26dada  nop                                           
  c26dadb  mov qword ptr [rbp+0x288],0                   
  c26dae6  mov rax,[rbp+0x478]                           
  c26daed  mov rcx,[rax]                                 
  c26daf0  test rcx,rcx                                  
  c26daf3  je short 0xC26DB10                            ; -> loc_c26db10
  c26daf5  mov rax,[rcx]                                 
  c26daf8  mov rax,[rax]                                 
  c26dafb  lea rdx,[rbp+0x250]                           
  c26db02  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26db08  nop                                           
  c26db09  mov [rbp+0x288],rax                           

loc_c26db10:  ; from c26daf3
  c26db10  mov qword ptr [rbp+0x2C8],0                   
  c26db1b  mov rax,[rbp+0x4D8]                           
  c26db22  mov rcx,[rax+0xA8]                            
  c26db29  test rcx,rcx                                  
  c26db2c  je short 0xC26DB49                            ; -> loc_c26db49
  c26db2e  mov rax,[rcx]                                 
  c26db31  mov rax,[rax]                                 
  c26db34  lea rdx,[rbp+0x290]                           
  c26db3b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26db41  nop                                           
  c26db42  mov [rbp+0x2C8],rax                           

loc_c26db49:  ; from c26db2c
  c26db49  lea rcx,[rbp+0x2D0]                           
  c26db50  mov rdx,[rbp+0x3C8]                           
  c26db57  call 0x6611410                                ; -> sub_6611410
  c26db5c  nop                                           
  c26db5d  mov byte ptr [rbp-0x18],0                     
  c26db61  cmp byte ptr [rbp+0x248],1                    
  c26db68  jne short 0xC26DBAA                           ; -> loc_c26dbaa
  c26db6a  movups xmm0,[rbp+0x220]                       
  c26db71  movups xmm1,[rbp+0x230]                       
  c26db78  movaps [rbp-0x30],xmm1                        
  c26db7c  movaps [rbp-0x40],xmm0                        
  c26db80  mov qword ptr [rbp+0x230],0                   
  c26db8b  mov qword ptr [rbp+0x238],0xF                 
  c26db96  mov byte ptr [rbp+0x220],0                    
  c26db9d  mov eax,[rbp+0x240]                           
  c26dba3  mov [rbp-0x20],eax                            
  c26dba6  mov byte ptr [rbp-0x18],1                     

loc_c26dbaa:  ; from c26db68
  c26dbaa  mov qword ptr [rbp+0x28],0                    
  c26dbb2  mov rcx,[rbp+0x288]                           
  c26dbb9  test rcx,rcx                                  
  c26dbbc  je 0xC26DDA2                                  ; -> loc_c26dda2
  c26dbc2  lea rax,[rbp+0x250]                           
  c26dbc9  cmp rcx,rax                                   
  c26dbcc  je 0xC26DD5C                                  ; -> loc_c26dd5c
  c26dbd2  mov [rbp+0x28],rcx                            
  c26dbd6  jmp 0xC26DD97                                 ; -> loc_c26dd97

loc_c26dbdb:  ; from c26dac1
  c26dbdb  lea rcx,[rbp+0x220]                           
  c26dbe2  mov rdx,[rbp+0x4D8]                           
  c26dbe9  call 0x58F1B0                                 ; -> sub_58f1b0
  c26dbee  nop                                           
  c26dbef  mov qword ptr [rbp+0x288],0                   
  c26dbfa  mov rax,[rbp+0x478]                           
  c26dc01  mov rcx,[rax]                                 
  c26dc04  test rcx,rcx                                  
  c26dc07  je short 0xC26DC24                            ; -> loc_c26dc24
  c26dc09  mov rax,[rcx]                                 
  c26dc0c  mov rax,[rax]                                 
  c26dc0f  lea rdx,[rbp+0x250]                           
  c26dc16  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26dc1c  nop                                           
  c26dc1d  mov [rbp+0x288],rax                           

loc_c26dc24:  ; from c26dc07
  c26dc24  mov qword ptr [rbp+0x2C8],0                   
  c26dc2f  mov rax,[rbp+0x4D8]                           
  c26dc36  mov rcx,[rax+0xA8]                            
  c26dc3d  test rcx,rcx                                  
  c26dc40  je short 0xC26DC5D                            ; -> loc_c26dc5d
  c26dc42  mov rax,[rcx]                                 
  c26dc45  mov rax,[rax]                                 
  c26dc48  lea rdx,[rbp+0x290]                           
  c26dc4f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26dc55  nop                                           
  c26dc56  mov [rbp+0x2C8],rax                           

loc_c26dc5d:  ; from c26dc40
  c26dc5d  lea rcx,[rbp+0x2D0]                           
  c26dc64  mov rdx,[rbp+0x3C8]                           
  c26dc6b  call 0x6611410                                ; -> sub_6611410
  c26dc70  nop                                           
  c26dc71  mov byte ptr [rbp+0x3C0],0xFF                 
  c26dc78  movzx eax,byte ptr [rbp+0x410]                
  c26dc7f  cmp rax,4                                     
  c26dc83  ja 0xC26DD35                                  ; -> loc_c26dd35
  c26dc89  lea rdx,[0xF478D94]                           ; [data_f478d94]
  c26dc90  movsxd rcx,[rdx+rax*4]                        
  c26dc94  add rcx,rdx                                   
  c26dc97  jmp rcx                                       
  c26dc99  movaps xmm0,[rbp+0x3D0]                       
  c26dca0  movups [rbp+0x380],xmm0                       
  c26dca7  movaps [rbp+0x3D0],xmm6                       
  c26dcae  lea rdx,[rbp+0x3F0]                           
  c26dcb5  mov ecx,[rdx-8]                               
  c26dcb8  mov [r14+0x170],ecx                           
  c26dcbf  mov rcx,[rdx-0x10]                            
  c26dcc3  mov [r14+0x168],rcx                           
  c26dcca  jmp short 0xC26DD2F                           ; -> loc_c26dd2f
  c26dccc  movzx ecx,byte ptr [rbp+0x3D0]                
  c26dcd3  mov [rbp+0x380],cl                            
  c26dcd9  jmp short 0xC26DD2F                           ; -> loc_c26dd2f
  c26dcdb  movaps xmm0,[rbp+0x3D0]                       
  c26dce2  movups [rbp+0x380],xmm0                       
  c26dce9  movaps [rbp+0x3D0],xmm6                       
  c26dcf0  lea rdx,[rbp+0x3F0]                           
  c26dcf7  mov ecx,[rdx-8]                               
  c26dcfa  mov [r14+0x170],ecx                           
  c26dd01  mov rcx,[rdx-0x10]                            
  c26dd05  mov [r14+0x168],rcx                           
  c26dd0c  movaps xmm0,[rbp+0x3F0]                       
  c26dd13  movups [rbp+0x3A0],xmm0                       
  c26dd1a  movaps [rdx],xmm6                             
  c26dd1d  movaps xmm0,[rbp+0x400]                       
  c26dd24  movups [rbp+0x3B0],xmm0                       
  c26dd2b  movaps [rdx+0x10],xmm6                        

loc_c26dd2f:  ; from c26dcca, c26dcd9
  c26dd2f  mov [rbp+0x3C0],al                            

loc_c26dd35:  ; from c26d678, c26dc83
  c26dd35  lea rcx,[rbp-0x40]                            
  c26dd39  lea rsi,[rbp+0x220]                           
  c26dd40  mov rdx,rsi                                   
  c26dd43  call 0x6755280                                ; -> sub_6755280
  c26dd48  mov byte ptr [rbp+0x188],1                    
  c26dd4f  mov rcx,rsi                                   
  c26dd52  call 0x67559D0                                ; -> sub_67559d0
  c26dd57  jmp 0xC26DF3F                                 ; -> loc_c26df3f

loc_c26dd5c:  ; from c26dbcc
  c26dd5c  mov rax,[rcx]                                 
  c26dd5f  mov rax,[rax+8]                               
  c26dd63  lea rdx,[rbp-0x10]                            
  c26dd67  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26dd6d  mov [rbp+0x28],rax                            
  c26dd71  mov rcx,[rbp+0x288]                           
  c26dd78  test rcx,rcx                                  
  c26dd7b  je short 0xC26DDA2                            ; -> loc_c26dda2
  c26dd7d  lea rax,[rbp+0x250]                           
  c26dd84  cmp rcx,rax                                   
  c26dd87  setne dl                                      
  c26dd8a  mov rax,[rcx]                                 
  c26dd8d  mov rax,[rax+0x20]                            
  c26dd91  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_c26dd97:  ; from c26dbd6
  c26dd97  mov qword ptr [rbp+0x288],0                   

loc_c26dda2:  ; from c26dbbc, c26dd7b
  c26dda2  mov qword ptr [rbp+0x68],0                    
  c26ddaa  mov rcx,[rbp+0x2C8]                           
  c26ddb1  test rcx,rcx                                  
  c26ddb4  je short 0xC26DE0E                            ; -> loc_c26de0e
  c26ddb6  lea rax,[rbp+0x290]                           
  c26ddbd  cmp rcx,rax                                   
  c26ddc0  je short 0xC26DDC8                            ; -> loc_c26ddc8
  c26ddc2  mov [rbp+0x68],rcx                            
  c26ddc6  jmp short 0xC26DE03                           ; -> loc_c26de03

loc_c26ddc8:  ; from c26ddc0
  c26ddc8  mov rax,[rcx]                                 
  c26ddcb  mov rax,[rax+8]                               
  c26ddcf  lea rdx,[rbp+0x30]                            
  c26ddd3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26ddd9  mov [rbp+0x68],rax                            
  c26dddd  mov rcx,[rbp+0x2C8]                           
  c26dde4  test rcx,rcx                                  
  c26dde7  je short 0xC26DE0E                            ; -> loc_c26de0e
  c26dde9  lea rax,[rbp+0x290]                           
  c26ddf0  cmp rcx,rax                                   
  c26ddf3  setne dl                                      
  c26ddf6  mov rax,[rcx]                                 
  c26ddf9  mov rax,[rax+0x20]                            
  c26ddfd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_c26de03:  ; from c26ddc6
  c26de03  mov qword ptr [rbp+0x2C8],0                   

loc_c26de0e:  ; from c26ddb4, c26dde7
  c26de0e  lea rcx,[rbp+0x2D0]                           
  c26de15  mov rax,[rcx+0x10]                            
  c26de19  lea rdx,[rbp-0x10]                            
  c26de1d  mov [rdx+0x90],rax                            
  c26de24  movups xmm0,[rcx]                             
  c26de27  movups [rdx+0x80],xmm0                        
  c26de2e  movups xmm0,[r14+0xC0]                        
  c26de36  movups xmm1,[r14+0xD0]                        
  c26de3e  movups [rdx+0xA8],xmm1                        
  c26de45  movups [rdx+0x98],xmm0                        
  c26de4c  mov qword ptr [rbp+0x2F8],0                   
  c26de57  mov qword ptr [rbp+0x300],0xF                 
  c26de62  mov byte ptr [rbp+0x2E8],0                    
  c26de69  mov rax,[r14+0xE0]                            
  c26de70  mov rcx,[r14+0xE6]                            
  c26de77  mov [rdx+0xBE],rcx                            
  c26de7e  mov [rdx+0xB8],rax                            
  c26de85  mov rax,[r14+0x110]                           
  c26de8c  mov [rdx+0xE8],rax                            
  c26de93  movups xmm0,[r14+0xF0]                        
  c26de9b  movups xmm1,[r14+0x100]                       
  c26dea3  movups [rdx+0xD8],xmm1                        
  c26deaa  movups [rdx+0xC8],xmm0                        
  c26deb1  mov qword ptr [rbp+0x118],0                   
  c26debc  mov rcx,[rbp+0x378]                           
  c26dec3  test rcx,rcx                                  
  c26dec6  je short 0xC26DF29                            ; -> loc_c26df29
  c26dec8  lea rax,[rbp+0x340]                           
  c26decf  cmp rcx,rax                                   
  c26ded2  je short 0xC26DEDD                            ; -> loc_c26dedd
  c26ded4  mov [rbp+0x118],rcx                           
  c26dedb  jmp short 0xC26DF1E                           ; -> loc_c26df1e

loc_c26dedd:  ; from c26ded2
  c26dedd  mov rax,[rcx]                                 
  c26dee0  mov rax,[rax+8]                               
  c26dee4  lea rdx,[rbp+0xE0]                            
  c26deeb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26def1  mov [rbp+0x118],rax                           
  c26def8  mov rcx,[rbp+0x378]                           
  c26deff  test rcx,rcx                                  
  c26df02  je short 0xC26DF29                            ; -> loc_c26df29
  c26df04  lea rax,[rbp+0x340]                           
  c26df0b  cmp rcx,rax                                   
  c26df0e  setne dl                                      
  c26df11  mov rax,[rcx]                                 
  c26df14  mov rax,[rax+0x20]                            
  c26df18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_c26df1e:  ; from c26dedb
  c26df1e  mov qword ptr [rbp+0x378],0                   

loc_c26df29:  ; from c26dec6, c26df02
  c26df29  mov byte ptr [rbp+0x188],2                    
  c26df30  lea rsi,[rbp+0x220]                           
  c26df37  mov rcx,rsi                                   
  c26df3a  call 0x6755C40                                ; -> sub_6755c40

loc_c26df3f:  ; from c26dd57
  c26df3f  movsx rcx,byte ptr [rbp+0x410]                
  c26df47  inc rcx                                       
  c26df4a  mov rdx,rsi                                   
  c26df4d  lea r8,[rbp+0x3D0]                            
  c26df54  call 0x6755B50                                ; -> sub_6755b50
  c26df59  jmp 0xC26EF96                                 ; -> sub_c26ef96

loc_c26df5e:  ; from c26d945
  c26df5e  lea r13,[rsi+1]                               
  c26df62  mov rdx,r13                                   
  c26df65  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26df6b  nop                                           
  c26df6c  mov rbx,rax                                   
  c26df6f  test rax,rax                                  
  c26df72  je 0xC26F1B2                                  ; -> sub_c26f1b2

loc_c26df78:  ; from c26d974
  c26df78  mov [rbp+0x448],rbx                           
  c26df7f  mov [rbp+0x458],r12                           
  c26df86  mov [rbp+0x460],rsi                           
  c26df8d  inc r12                                       
  c26df90  mov rcx,rbx                                   
  c26df93  mov rdx,r15                                   
  c26df96  mov r8,r12                                    
  c26df99  call 0xEEC6EC0                                ; -> sub_eec6ec0

loc_c26df9e:  ; from c26d6e7
  c26df9e  mov rax,[rbp+0x4D8]                           
  c26dfa5  mov eax,[rax+0x20]                            
  c26dfa8  mov [rbp+0x468],eax                           
  c26dfae  mov byte ptr [rbp+0x470],1                    

loc_c26dfb5:  ; from c26d2fd, c26d36c, c26d9b7
  c26dfb5  movaps [rbp+0x480],xmm6                       
  c26dfbc  mov qword ptr [rbp+0x490],0                   
  c26dfc7  mov qword ptr [rbp+0x498],0xF                 
  c26dfd2  lea rax,[rbp+0x480]                           
  c26dfd9  mov [rbp+0x1B8],rax                           
  c26dfe0  mov qword ptr [rbp+0x1C0],0                   
  c26dfeb  lea rcx,[rbp+0x220]                           
  c26dff2  lea rdx,[rbp+0x1B8]                           
  c26dff9  mov r8d,0xB                                   
  c26dfff  call 0x393660                                 ; -> sub_393660
  c26e004  nop                                           
  c26e005  mov rcx,[0x128CBC00]                          ; [data_128cbc00]
  c26e00c  mov rdx,[rcx+8]                               
  c26e010  cmp byte ptr [rdx+0x19],0                     
  c26e014  mov rax,rcx                                   
  c26e017  jne short 0xC26E04D                           ; -> loc_c26e04d
  c26e019  mov r8d,[rbp+0x220]                           
  c26e020  mov rax,rcx                                   
  c26e023  nop [rax+rax]                                 

loc_c26e030:  ; from c26e04b
  c26e030  xor r9d,r9d                                   
  c26e033  cmp [rdx+0x20],r8d                            
  c26e037  setl r9b                                      
  c26e03b  cmovge rax,rdx                                
  c26e03f  shl r9d,4                                     
  c26e043  mov rdx,[rdx+r9]                              
  c26e047  cmp byte ptr [rdx+0x19],0                     
  c26e04b  je short 0xC26E030                            ; -> loc_c26e030

loc_c26e04d:  ; from c26e017
  c26e04d  cmp byte ptr [rax+0x19],0                     
  c26e051  je 0xC26E1B7                                  ; -> loc_c26e1b7

loc_c26e057:  ; from c26e1ba, c26e1c9
  c26e057  mov qword ptr [rbp+0x1F0],0                   
  c26e062  mov qword ptr [rbp+0x1F8],0xF                 
  c26e06d  movups xmm0,[0xEFD2D90]                       ; [data_efd2d90]
  c26e074  movaps [rbp+0x1E0],xmm0                       

loc_c26e07b:  ; from c26e1ef
  c26e07b  mov rax,[rbp+0x240]                           
  c26e082  cmp rax,0x10                                  
  c26e086  jb short 0xC26E0C0                            ; -> loc_c26e0c0
  c26e088  mov rcx,[rbp+0x228]                           
  c26e08f  lea rdx,[rax+1]                               
  c26e093  cmp rdx,0x1000                                
  c26e09a  jb short 0xC26E0BB                            ; -> loc_c26e0bb
  c26e09c  mov r8,[rcx-8]                                
  c26e0a0  add rcx,0xFFFFFFFFFFFFFFF8                    
  c26e0a4  sub rcx,r8                                    
  c26e0a7  cmp rcx,0x20                                  
  c26e0ab  jae 0xC26F1C1                                 ; -> sub_c26f1c1
  c26e0b1  add rax,0x28                                  
  c26e0b5  mov rdx,rax                                   
  c26e0b8  mov rcx,r8                                    

loc_c26e0bb:  ; from c26e09a
  c26e0bb  call 0xE935700                                ; -> sub_e935700

loc_c26e0c0:  ; from c26e086
  c26e0c0  mov qword ptr [rbp+0x238],0                   
  c26e0cb  mov qword ptr [rbp+0x240],0xF                 
  c26e0d6  mov byte ptr [rbp+0x228],0                    
  c26e0dd  mov rax,[rbp+0x498]                           
  c26e0e4  cmp rax,0x10                                  
  c26e0e8  jb short 0xC26E122                            ; -> loc_c26e122
  c26e0ea  mov rcx,[rbp+0x480]                           
  c26e0f1  lea rdx,[rax+1]                               
  c26e0f5  cmp rdx,0x1000                                
  c26e0fc  jb short 0xC26E11D                            ; -> loc_c26e11d
  c26e0fe  mov r8,[rcx-8]                                
  c26e102  add rcx,0xFFFFFFFFFFFFFFF8                    
  c26e106  sub rcx,r8                                    
  c26e109  cmp rcx,0x20                                  
  c26e10d  jae 0xC26F1C1                                 ; -> sub_c26f1c1
  c26e113  add rax,0x28                                  
  c26e117  mov rdx,rax                                   
  c26e11a  mov rcx,r8                                    

loc_c26e11d:  ; from c26e0fc
  c26e11d  call 0xE935700                                ; -> sub_e935700

loc_c26e122:  ; from c26e0e8
  c26e122  mov rax,[rbp+0x1F0]                           
  c26e129  test rax,rax                                  
  c26e12c  je 0xC26E277                                  ; -> loc_c26e277
  c26e132  cmp qword ptr [rbp+0x1F8],0x10                
  c26e13a  lea rcx,[rbp+0x1E0]                           
  c26e141  jb short 0xC26E14A                            ; -> loc_c26e14a
  c26e143  mov rcx,[rbp+0x1E0]                           

loc_c26e14a:  ; from c26e141
  c26e14a  mov [rbp+0x190],rcx                           
  c26e151  mov [rbp+0x198],rax                           
  c26e158  lea rcx,[rbp+0x220]                           
  c26e15f  lea rdx,[rbp+0x190]                           
  c26e166  mov r8d,0xB                                   
  c26e16c  call 0x393660                                 ; -> sub_393660
  c26e171  nop                                           
  c26e172  mov eax,[rbp+0x220]                           
  c26e178  mov [rbp+0x410],eax                           
  c26e17e  cmp qword ptr [rbp+0x240],0x10                
  c26e186  mov r9,r14                                    
  c26e189  jb short 0xC26E192                            ; -> loc_c26e192
  c26e18b  mov r9,[rbp+0x228]                            

loc_c26e192:  ; from c26e189
  c26e192  mov rbx,[rbp+0x238]                           
  c26e199  mov rax,[rbp+0x430]                           
  c26e1a0  cmp rbx,rax                                   
  c26e1a3  jbe short 0xC26E1F4                           ; -> loc_c26e1f4
  c26e1a5  lea rcx,[rbp+0x418]                           
  c26e1ac  mov rdx,rbx                                   
  c26e1af  call 0x9D6D0                                  ; -> sub_9d6d0
  c26e1b4  nop                                           
  c26e1b5  jmp short 0xC26E222                           ; -> loc_c26e222

loc_c26e1b7:  ; from c26e051
  c26e1b7  cmp rax,rcx                                   
  c26e1ba  je 0xC26E057                                  ; -> loc_c26e057
  c26e1c0  mov ecx,[rax+0x20]                            
  c26e1c3  cmp [rbp+0x220],ecx                           
  c26e1c9  jl 0xC26E057                                  ; -> loc_c26e057
  c26e1cf  mov rcx,[rax+0x28]                            
  c26e1d3  mov rax,[rcx]                                 
  c26e1d6  mov rax,[rax+0x30]                            
  c26e1da  lea rdx,[rbp+0x1E0]                           
  c26e1e1  lea r8,[rbp+0x220]                            
  c26e1e8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26e1ee  nop                                           
  c26e1ef  jmp 0xC26E07B                                 ; -> loc_c26e07b

loc_c26e1f4:  ; from c26e1a3
  c26e1f4  lea r15,[rbp+0x418]                           
  c26e1fb  cmp rax,0x10                                  
  c26e1ff  jb short 0xC26E208                            ; -> loc_c26e208
  c26e201  mov r15,[rbp+0x418]                           

loc_c26e208:  ; from c26e1ff
  c26e208  mov [rbp+0x428],rbx                           
  c26e20f  mov rcx,r15                                   
  c26e212  mov rdx,r9                                    
  c26e215  mov r8,rbx                                    
  c26e218  call 0xEEC6DE0                                ; -> sub_eec6de0
  c26e21d  mov byte ptr [r15+rbx],0                      

loc_c26e222:  ; from c26e1b5
  c26e222  movups xmm0,[r14+0x20]                        
  c26e227  lea rax,[rbp+0x3F0]                           
  c26e22e  movups [rax+0x48],xmm0                        
  c26e232  mov rax,[rbp+0x240]                           
  c26e239  cmp rax,0x10                                  
  c26e23d  jb short 0xC26E277                            ; -> loc_c26e277
  c26e23f  mov rcx,[rbp+0x228]                           
  c26e246  lea rdx,[rax+1]                               
  c26e24a  cmp rdx,0x1000                                
  c26e251  jb short 0xC26E272                            ; -> loc_c26e272
  c26e253  mov r8,[rcx-8]                                
  c26e257  add rcx,0xFFFFFFFFFFFFFFF8                    
  c26e25b  sub rcx,r8                                    
  c26e25e  cmp rcx,0x20                                  
  c26e262  jae 0xC26F1C1                                 ; -> sub_c26f1c1
  c26e268  add rax,0x28                                  
  c26e26c  mov rdx,rax                                   
  c26e26f  mov rcx,r8                                    

loc_c26e272:  ; from c26e251
  c26e272  call 0xE935700                                ; -> sub_e935700

loc_c26e277:  ; from c26e12c, c26e23d
  c26e277  mov eax,[0x12ADF818]                          ; [data_12adf818]
  c26e27d  mov byte ptr [rbp+0x214],0                    
  c26e284  mov byte ptr [rbp+0x21C],0                    
  c26e28b  cmp eax,2                                     
  c26e28e  jne short 0xC26E2B2                           ; -> loc_c26e2b2
  c26e290  mov byte ptr [rbp+0x214],1                    
  c26e297  mov dword ptr [rbp+0x210],0x20000000          
  c26e2a1  mov byte ptr [rbp+0x21C],1                    
  c26e2a8  mov dword ptr [rbp+0x218],0x8000000           

loc_c26e2b2:  ; from c26e28e
  c26e2b2  mov r15,[rdi+0x20]                            
  c26e2b6  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  c26e2bd  mov rax,[rcx]                                 
  c26e2c0  mov rax,[rax+8]                               
  c26e2c4  mov edx,0x1590                                
  c26e2c9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26e2cf  nop                                           
  c26e2d0  mov rsi,rax                                   
  c26e2d3  test rax,rax                                  
  c26e2d6  je 0xC26F048                                  ; -> sub_c26f048
  c26e2dc  mov [rbp+0x4E0],rsi                           
  c26e2e3  mov qword ptr [rbp+0x4B8],0                   
  c26e2ee  mov rax,[rbp+0x4D8]                           
  c26e2f5  mov rcx,[rax+0xA8]                            
  c26e2fc  test rcx,rcx                                  
  c26e2ff  je short 0xC26E31C                            ; -> loc_c26e31c
  c26e301  mov rax,[rcx]                                 
  c26e304  mov rax,[rax]                                 
  c26e307  lea rdx,[rbp+0x480]                           
  c26e30e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c26e314  nop                                           
  c26e315  mov [rbp+0x4B8],rax                           

loc_c26e31c:  ; from c26e2ff
  c26e31c  lea rsi,[rbp+0x220]                           
  c26e323  mov rcx,rsi                                   
  c26e326  mov rdx,[rbp+0x3C8]                           
  c26e32d  call 0x6611410                                ; -> sub_6611410
  c26e332  nop                                           
  c26e333  lea rax,[rbp+0x480]                           
  c26e33a  mov [rsp+0x30],rax                            
  c26e33f  mov rax,[rbp+0x1A0]                           
  c26e346  mov [rsp+0x28],rax                            
  c26e34b  mov [rsp+0x20],rsi                            
  c26e350  mov rcx,[rbp+0x4E0]                           
  c26e357  mov rdx,r15                                   
  c26e35a  lea r8,[rbp+0x210]                            
  c26e361  lea r9,[rbp+0x3D0]                            
  c26e368  call 0xC284720                                ; -> sub_c284720
  c26e36d  nop                                           
  c26e36e  mov rbx,[rdi+0x18]                            
  c26e372  mov r12,[rbp+0x4E0]                           
  c26e379  mov [rdi+0x18],r12                            
  c26e37d  test rbx,rbx                                  
  c26e380  je short 0xC26E39B                            ; -> loc_c26e39b
  c26e382  mov rcx,rbx                                   
  c26e385  call 0xC287B30                                ; -> sub_c287b30
  ... (--max 1200)

```
