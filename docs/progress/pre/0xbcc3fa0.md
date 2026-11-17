# preflight 0xbcc3fa0

## fn
```
sub_bcc3fa0  [0xbcc3fa0..0xbcc414f)  size 0x1af  2 xrefs in
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
  ... (--max 40)

```

## callers
```
  sub_bcc38e0                  1 call site(s)
  sub_bcc39b0                  1 call site(s)
-- 2 calling function(s)

```

## callees
```
sub_bcc3fa0  [0xbcc3fa0..0xbcc414f)
  call sub_1a2800                   x1
  call sub_bc60740                  x1
  call sub_e951550                  x1
  call sub_ebce390                  x1
  call sub_eec6d80                  x1

```

## stores into [reg+off] (non-stack)
```
  bcc40aa  mov [rsi+0x7C],edi                            
  bcc40ad  mov word ptr [rsi+0x9E],1                     
  bcc40bf  mov [rsi+0x94],r12d                           
  bcc4235  mov [r15+0x7C],r12d                           
  bcc4239  mov word ptr [r15+0x9E],1                     
  bcc43e2  mov [rbx+0x7C],r12d                           
  bcc43e6  mov word ptr [rbx+0x9E],1                     
  bcc44fc  mov [rax+0xDC57F4],ecx                        
  bcc4575  mov [r15+0x7C],r12d                           
  bcc4579  mov word ptr [r15+0x9E],1                     
  bcc469d  movups [rsi+0x20],xmm3                        
  bcc46a1  movups [rsi+0x10],xmm1                        
  bcc46b8  mov [rbx+0x90],r12d                           
  bcc46bf  mov word ptr [rbx+0x98],0x30                  
  bcc46c8  mov [rbx+0x94],r15d                           
  bcc46cf  mov [rbx+0xB6],di                             
```

## listing (600 instr)
```
sub_bcc3fa0  [0xbcc3fa0..0xbcc5fa0)  size 0x2000  2 xrefs in
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
  bcc429e  mov r8,[r15]                                  
  bcc42a1  lea rcx,[r8+0x9457C0]                         
  bcc42a8  mov eax,[r8+0xD457C0]                         
  bcc42af  nop                                           

loc_bcc42b0:  ; from bcc42e5
  bcc42b0  mov r12d,eax                                  
  bcc42b3  lea r9d,[r12+1]                               
  bcc42b8  cmp r9d,0xFFFF                                
  bcc42bf  cmovae r9d,ebx                                
  bcc42c3  cmp eax,0xFFFF                                
  bcc42c8  cmovae r9d,ebx                                
  bcc42cc  lock cmpxchg [r8+0xD457C0],r9d                
  bcc42d5  cmp r12d,0xFFFF                               
  bcc42dc  je 0xBCC4210                                  ; -> loc_bcc4210
  bcc42e2  cmp r12d,eax                                  
  bcc42e5  jne short 0xBCC42B0                           ; -> loc_bcc42b0
  bcc42e7  jmp 0xBCC4210                                 ; -> loc_bcc4210

loc_bcc42ec:  ; from bcc41b5
  bcc42ec  lea r8,[0x12AE2888]                           ; [data_12ae2888]
  bcc42f3  mov rdx,rbp                                   
  bcc42f6  mov rcx,r12                                   
  bcc42f9  call 0xBCC7CE0                                ; -> sub_bcc7ce0
  bcc42fe  cmp byte ptr [rbp+0x10],1                     
  bcc4302  jne 0xBCC41BB                                 ; -> loc_bcc41bb
  bcc4308  cmp byte ptr [rbp+2],0                        
  bcc430c  je 0xBCC41BB                                  ; -> loc_bcc41bb
  bcc4312  cmp word ptr [rbp],0xFFFF                     
  bcc4317  je 0xBCC41BB                                  ; -> loc_bcc41bb
  bcc431d  movzx ecx,byte ptr [r12+0xF8]                 
  bcc4326  mov word ptr [rbp+0x2C],0xFFFF                
  bcc432c  test cl,cl                                    
  bcc432e  je short 0xBCC433D                            ; -> loc_bcc433d
  bcc4330  movzx eax,word ptr [r12+0xE8]                 
  bcc4339  mov [rbp+0x2C],ax                             

loc_bcc433d:  ; from bcc432e
  bcc433d  test byte ptr [0x12ADFA51],8                  ; [data_12adfa51]
  bcc4344  jne short 0xBCC434D                           ; -> loc_bcc434d

loc_bcc4346:  ; from bcc41c4, bcc41f6, bcc453c
  bcc4346  xor eax,eax                                   
  bcc4348  jmp 0xBCC470A                                 ; -> loc_bcc470a

loc_bcc434d:  ; from bcc4344
  bcc434d  xor cl,1                                      
  bcc4350  or cl,[r12+0xEA]                              
  bcc4358  mov [rbp+0x29],cl                             
  bcc435b  mov r14,[r15]                                 
  bcc435e  mov r13,[r15+8]                               
  bcc4362  mov rax,[rbp+0x20]                            
  bcc4366  mov rax,[rax]                                 
  bcc4369  mov rbx,[rax+0x10]                            
  bcc436d  mov rcx,[rbx]                                 
  bcc4370  mov eax,[rcx+0xD457C0]                        
  bcc4376  mov edx,0xFFFF                                
  bcc437b  nop [rax+rax]                                 

loc_bcc4380:  ; from bcc43b1
  bcc4380  mov r12d,eax                                  
  bcc4383  lea r8d,[r12+1]                               
  bcc4388  cmp r8d,0xFFFF                                
  bcc438f  cmovae r8d,edx                                
  bcc4393  cmp eax,0xFFFF                                
  bcc4398  cmovae r8d,edx                                
  bcc439c  lock cmpxchg [rcx+0xD457C0],r8d               
  bcc43a5  cmp r12d,0xFFFF                               
  bcc43ac  je short 0xBCC43B3                            ; -> loc_bcc43b3
  bcc43ae  cmp r12d,eax                                  
  bcc43b1  jne short 0xBCC4380                           ; -> loc_bcc4380

loc_bcc43b3:  ; from bcc43ac
  bcc43b3  xor r8d,r8d                                   
  bcc43b6  cmp r12d,0xFFFF                               
  bcc43bd  setne r8b                                     
  bcc43c1  shl r8d,6                                     
  bcc43c5  mov eax,r12d                                  
  bcc43c8  shl rax,6                                     
  bcc43cc  add rcx,rax                                   
  bcc43cf  add rcx,0x9457C0                              
  bcc43d6  lea rdx,[0xF44C050]                           ; [data_f44c050]
  bcc43dd  call 0xEBCE390                                ; -> sub_ebce390
  bcc43e2  mov [rbx+0x7C],r12d                           
  bcc43e6  mov word ptr [rbx+0x9E],1                     
  bcc43ef  mov rsi,[0x12AE1748]                          ; [data_12ae1748]
  bcc43f6  lea r12,[rsi+0x1C0]                           
  bcc43fd  mov rcx,r12                                   
  bcc4400  call 0xEBDBF10                                ; -> sub_ebdbf10
  bcc4405  mov rax,[rsi+0x1CFD0C8]                       
  bcc440c  mov edi,[rax+0xDC57F4]                        
  bcc4412  mov esi,[0x12AE0DB0]                          ; [data_12ae0db0]
  bcc4418  mov rcx,r12                                   
  bcc441b  call 0xEBDBF20                                ; -> sub_ebdbf20
  bcc4420  nop                                           
  bcc4421  mov ecx,edi                                   
  bcc4423  mov eax,0xAAAAAAAB                            
  bcc4428  imul rcx,rax                                  
  bcc442c  shr rcx,0x25                                  
  bcc4430  shl ecx,4                                     
  bcc4433  lea ecx,[rcx+rcx*2]                           
  bcc4436  mov edx,edi                                   
  bcc4438  sub edx,ecx                                   
  bcc443a  mov ecx,0x30                                  
  bcc443f  sub ecx,edx                                   
  bcc4441  test edx,edx                                  
  bcc4443  cmove ecx,edx                                 
  bcc4446  add ecx,edi                                   
  bcc4448  lea edi,[r14+r14*2]                           
  bcc444c  shl edi,4                                     
  bcc444f  add edi,ecx                                   
  bcc4451  cmp edi,esi                                   
  bcc4453  cmovae edi,esi                                
  bcc4456  mov rdx,r14                                   
  bcc4459  shr rdx,0x20                                  
  bcc445d  jne 0xBCC47D3                                 ; -> loc_bcc47d3
  bcc4463  sub edi,ecx                                   
  bcc4465  imul rdi,rax                                  
  bcc4469  shr rdi,0x25                                  
  bcc446d  cmp edi,r14d                                  
  bcc4470  jae short 0xBCC447A                           ; -> loc_bcc447a
  bcc4472  xor r15d,r15d                                 
  bcc4475  jmp 0xBCC4524                                 ; -> loc_bcc4524

loc_bcc447a:  ; from bcc4470
  bcc447a  mov rsi,[0x12AE1748]                          ; [data_12ae1748]
  bcc4481  lea rcx,[rsi+0x1C0]                           
  bcc4488  mov [rbp+0x18],rcx                            
  bcc448c  call 0xEBDBF10                                ; -> sub_ebdbf10
  bcc4491  mov rax,[rsi+0x1CFD0C8]                       
  bcc4498  mov edx,[rax+0xDC57F4]                        
  bcc449e  mov ecx,0xAAAAAAAB                            
  bcc44a3  mov r8,rdx                                    
  bcc44a6  imul r8,rcx                                   
  bcc44aa  shr r8,0x25                                   
  bcc44ae  shl r8d,4                                     
  bcc44b2  lea r8d,[r8+r8*2]                             
  bcc44b6  mov r9d,edx                                   
  bcc44b9  sub r9d,r8d                                   
  bcc44bc  mov r12d,0x30                                 
  bcc44c2  sub r12d,r9d                                  
  bcc44c5  test r9d,r9d                                  
  bcc44c8  cmove r12d,r9d                                
  bcc44cc  add r12d,edx                                  
  bcc44cf  lea r15d,[rdi+rdi*2]                          
  bcc44d3  shl r15d,4                                    
  bcc44d7  add r15d,r12d                                 
  bcc44da  mov edx,[0x12AE0DB0]                          ; [data_12ae0db0]
  bcc44e0  cmp r15d,edx                                  
  bcc44e3  cmovae r15d,edx                               
  bcc44e7  sub r15d,r12d                                 
  bcc44ea  imul r15,rcx                                  
  bcc44ee  shr r15,0x25                                  
  bcc44f2  lea ecx,[r15+r15*2]                           
  bcc44f6  shl ecx,4                                     
  bcc44f9  add ecx,r12d                                  
  bcc44fc  mov [rax+0xDC57F4],ecx                        
  bcc4502  mov rax,[rsi+0x1CFD0C8]                       
  bcc4509  mov rax,[rax+0xDC5800]                        
  bcc4510  mov rsi,[rax]                                 
  bcc4513  add rsi,r12                                   
  bcc4516  mov di,[rax+0x12]                             
  bcc451a  mov rcx,[rbp+0x18]                            
  bcc451e  call 0xEBDBF20                                ; -> sub_ebdbf20
  bcc4523  nop                                           

loc_bcc4524:  ; from bcc4475
  bcc4524  test byte ptr [rbp+0x29],1                    
  bcc4528  je 0xBCC47CE                                  ; -> loc_bcc47ce
  bcc452e  cmp r15d,r14d                                 
  bcc4531  jae 0xBCC462C                                 ; -> loc_bcc462c
  bcc4537  cmp word ptr [rbp+0x2C],0xFFFF                
  bcc453c  je 0xBCC4346                                  ; -> loc_bcc4346
  bcc4542  xor eax,eax                                   
  bcc4544  mov esi,0xFFFF                                
  bcc4549  jmp short 0xBCC45B4                           ; -> loc_bcc45b4
  bcc454b  nop [rax+rax]                                 

loc_bcc4550:  ; from bcc461c, bcc4627
  bcc4550  xor r8d,r8d                                   
  bcc4553  cmp r12d,0xFFFF                               
  bcc455a  setne r8b                                     
  bcc455e  shl r8d,6                                     
  bcc4562  mov eax,r12d                                  
  bcc4565  shl rax,6                                     
  bcc4569  add rcx,rax                                   
  bcc456c  call 0xEBCE390                                ; -> sub_ebce390

loc_bcc4571:  ; from bcc45d3
  bcc4571  or dil,[rbp+0x2F]                             
  bcc4575  mov [r15+0x7C],r12d                           
  bcc4579  mov word ptr [r15+0x9E],1                     
  bcc4583  mov [rsp+0x28],dil                            
  bcc4588  mov eax,[rbp+0xA8]                            
  bcc458e  mov [rsp+0x20],eax                            
  bcc4592  mov rcx,r15                                   
  bcc4595  movzx edx,word ptr [rbp+0x2A]                 
  bcc4599  movzx r8d,word ptr [rbp+0x2C]                 
  bcc459e  mov r9w,0xFFFF                                
  bcc45a3  call 0xBC60740                                ; -> sub_bc60740
  bcc45a8  mov rax,rbx                                   
  bcc45ab  cmp rbx,r14                                   
  bcc45ae  je 0xBCC4708                                  ; -> loc_bcc4708

loc_bcc45b4:  ; from bcc4549
  bcc45b4  lea rbx,[rax+1]                               
  bcc45b8  cmp rbx,r14                                   
  bcc45bb  setb dil                                      
  bcc45bf  mov rcx,[rbp+0x20]                            
  bcc45c3  mov rcx,[rcx]                                 
  bcc45c6  mov r15,[rcx+0x10]                            
  bcc45ca  mov r12d,0                                    
  bcc45d0  test r13,r13                                  
  bcc45d3  je short 0xBCC4571                            ; -> loc_bcc4571
  bcc45d5  mov edx,eax                                   
  bcc45d7  shl rdx,6                                     
  bcc45db  add rdx,r13                                   
  bcc45de  mov r8,[r15]                                  
  bcc45e1  lea rcx,[r8+0x9457C0]                         
  bcc45e8  mov eax,[r8+0xD457C0]                         
  bcc45ef  nop                                           

loc_bcc45f0:  ; from bcc4625
  bcc45f0  mov r12d,eax                                  
  bcc45f3  lea r9d,[r12+1]                               
  bcc45f8  cmp r9d,0xFFFF                                
  bcc45ff  cmovae r9d,esi                                
  bcc4603  cmp eax,0xFFFF                                
  bcc4608  cmovae r9d,esi                                
  bcc460c  lock cmpxchg [r8+0xD457C0],r9d                
  bcc4615  cmp r12d,0xFFFF                               
  bcc461c  je 0xBCC4550                                  ; -> loc_bcc4550
  bcc4622  cmp r12d,eax                                  
  bcc4625  jne short 0xBCC45F0                           ; -> loc_bcc45f0
  bcc4627  jmp 0xBCC4550                                 ; -> loc_bcc4550

loc_bcc462c:  ; from bcc4531
  bcc462c  test r15d,r15d                                
  bcc462f  je 0xBCC46B8                                  ; -> loc_bcc46b8
  bcc4635  mov eax,r15d                                  
  bcc4638  add r13,0x38                                  
  bcc463c  xor ecx,ecx                                   
  bcc463e  xchg ax,ax                                    

loc_bcc4640:  ; from bcc46b6
  bcc4640  cmp r14,rcx                                   
  bcc4643  je 0xBCC471E                                  ; -> loc_bcc471e
  bcc4649  movsd xmm0,[r13-0x38]                         
  bcc464f  movsd xmm1,[r13-0x28]                         
  bcc4655  movsd xmm2,[r13-0x18]                         
  bcc465b  movsd xmm3,[r13-8]                            
  bcc4661  movaps xmm4,xmm3                              
  bcc4664  movlhps xmm4,xmm2                             
  bcc4667  movaps xmm5,xmm0                              
  bcc466a  unpcklps xmm5,xmm1                            
  bcc466d  shufps xmm5,xmm4,0x24                         
  bcc4671  unpcklps xmm2,xmm3                            
  bcc4674  shufps xmm1,xmm0,0x11                         
  bcc4678  shufps xmm1,xmm2,0xE2                         
  bcc467c  movss xmm0,[r13]                              
  bcc4682  movss xmm2,[r13-0x10]                         
  bcc4688  unpcklps xmm2,xmm0                            
  bcc468b  movss xmm0,[r13-0x20]                         
  bcc4691  movss xmm3,[r13-0x30]                         
  bcc4697  unpcklps xmm3,xmm0                            
  bcc469a  movlhps xmm3,xmm2                             
  bcc469d  movups [rsi+0x20],xmm3                        
  bcc46a1  movups [rsi+0x10],xmm1                        
  bcc46a5  movups [rsi],xmm5                             
  bcc46a8  inc rcx                                       
  bcc46ab  add r13,0x40                                  
  bcc46af  add rsi,0x30                                  
  bcc46b3  cmp rax,rcx                                   
  bcc46b6  jne short 0xBCC4640                           ; -> loc_bcc4640

loc_bcc46b8:  ; from bcc462f
  bcc46b8  mov [rbx+0x90],r12d                           
  bcc46bf  mov word ptr [rbx+0x98],0x30                  
  bcc46c8  mov [rbx+0x94],r15d                           
  bcc46cf  mov [rbx+0xB6],di                             
  bcc46d6  cmp byte ptr [rbp+2],0                        
  bcc46da  je 0xBCC47CE                                  ; -> loc_bcc47ce
  bcc46e0  movzx r8d,word ptr [rbp]                      
  bcc46e5  movzx eax,byte ptr [rbp+0x2F]                 
  bcc46e9  mov [rsp+0x28],al                             
  bcc46ed  mov eax,[rbp+0xA8]                            
  bcc46f3  mov [rsp+0x20],eax                            
  bcc46f7  mov rcx,rbx                                   
  bcc46fa  movzx edx,word ptr [rbp+0x2A]                 
  bcc46fe  mov r9w,0xFFFF                                
  bcc4703  call 0xBC60740                                ; -> sub_bc60740

loc_bcc4708:  ; from bcc426e, bcc45ae
  bcc4708  mov al,1                                      

loc_bcc470a:  ; from bcc41d2, bcc4348
  bcc470a  add rsp,0xB8                                  
  bcc4711  pop rbx                                       
  bcc4712  pop rdi                                       
  bcc4713  pop rsi                                       
  bcc4714  pop r12                                       
  bcc4716  pop r13                                       
  bcc4718  pop r14                                       
  bcc471a  pop r15                                       
  bcc471c  pop rbp                                       
  bcc471d  ret                                           

loc_bcc471e:  ; from bcc4643
  bcc471e  call 0x78ED0                                  ; -> sub_78ed0

loc_bcc4723:  ; from bcc41a1
  bcc4723  lea rcx,[0x12AE28C8]                          ; [data_12ae28c8]
  bcc472a  call 0xE938CB0                                ; -> sub_e938cb0
  bcc472f  cmp dword ptr [0x12AE28C8],0xFFFFFFFF         ; [data_12ae28c8]
  bcc4736  jne 0xBCC41A7                                 ; -> loc_bcc41a7
  bcc473c  mov qword ptr [rbp-0x38],0                    
  bcc4744  mov qword ptr [rbp-0x30],0xA                  
  bcc474c  mov qword ptr [rbp-0x28],0xF                  
  bcc4754  mov rax,[0xF5B7EC7]                           ; [data_f5b7ec7] "Instancing"
  bcc475b  mov [rbp-0x40],rax                            
  bcc475f  movzx eax,word ptr [0xF5B7ECF]                ; [data_f5b7ecf]
  bcc4766  mov [rbp-0x38],ax                             
  bcc476a  xorps xmm0,xmm0                               
  bcc476d  movups [rbp-0x20],xmm0                        
  bcc4771  mov qword ptr [rbp-0x10],2                    
  bcc4779  mov qword ptr [rbp-8],0xF                     
  bcc4781  mov word ptr [rbp-0x20],0x6E4F                
  bcc4787  lea rax,[rbp-0x40]                            
  bcc478b  mov [rbp-0x50],rax                            
  bcc478f  lea rax,[rbp]                                 
  bcc4793  mov [rbp-0x48],rax                            
  bcc4797  lea rcx,[0x12AE2888]                          ; [data_12ae2888]
  bcc479e  lea rdx,[rbp-0x50]                            
  bcc47a2  call 0x7D7890                                 ; -> sub_7d7890
  bcc47a7  nop                                           
  bcc47a8  lea rcx,[rbp-0x40]                            
  bcc47ac  call 0x9B250                                  ; -> sub_9b250
  bcc47b1  lea rcx,[0xBCC48B0]                           ; [sub_bcc48b0]
  bcc47b8  call 0xE935740                                ; -> sub_e935740
  bcc47bd  lea rcx,[0x12AE28C8]                          ; [data_12ae28c8]
  bcc47c4  call 0xE938D70                                ; -> sub_e938d70
  bcc47c9  jmp 0xBCC41A7                                 ; -> loc_bcc41a7

loc_bcc47ce:  ; from bcc4528, bcc46da
  bcc47ce  call 0x1A2800                                 ; -> sub_1a2800

loc_bcc47d3:  ; from bcc445d
  bcc47d3  xorps xmm0,xmm0                               
  bcc47d6  movups [rbp-0x38],xmm0                        
  bcc47da  lea rax,[0xF08E738]                           ; [data_f08e738]
  bcc47e1  mov [rbp-0x40],rax                            
  bcc47e5  lea rdx,[0xFB3B080]                           ; [data_fb3b080]
  bcc47ec  lea rcx,[rbp-0x40]                            
  bcc47f0  call 0xEEC6D80                                ; -> sub_eec6d80
  bcc47f5  int3                                          
  bcc47f6  nop [rax+rax]                                 ; R ret@eec6d80+0x0+idx
  bcc4800  mov [rsp+0x10],rdx                            
  bcc4805  push rbp                                      
  bcc4806  push r15                                      
  bcc4808  push r14                                      
  bcc480a  push r13                                      
  bcc480c  push r12                                      
  bcc480e  push rsi                                      
  bcc480f  push rdi                                      
  bcc4810  push rbx                                      
  bcc4811  sub rsp,0x38                                  
  bcc4815  lea rbp,[rdx+0x80]                            
  bcc481c  lea rcx,[rbp-0x40]                            
  bcc4820  call 0x9B250                                  ; -> sub_9b250
  bcc4825  lea rcx,[0x12AE28C8]                          ; [data_12ae28c8]
  bcc482c  call 0xE938D30                                ; -> sub_e938d30
  bcc4831  nop                                           
  bcc4832  add rsp,0x38                                  
  bcc4836  pop rbx                                       
  bcc4837  pop rdi                                       
  bcc4838  pop rsi                                       
  bcc4839  pop r12                                       
  bcc483b  pop r13                                       
  bcc483d  pop r14                                       
  bcc483f  pop r15                                       
  bcc4841  pop rbp                                       
  bcc4842  ret                                           
  bcc4843  nop [rax+rax]                                 ; R ret@e938d30+0x0+idx
  bcc4850  mov [rsp+0x10],rdx                            
  bcc4855  push rbp                                      
  bcc4856  push r15                                      
  bcc4858  push r14                                      
  bcc485a  push r13                                      
  bcc485c  push r12                                      
  bcc485e  push rsi                                      
  bcc485f  push rdi                                      
  bcc4860  push rbx                                      
  bcc4861  sub rsp,0x38                                  
  bcc4865  lea rbp,[rdx+0x80]                            
  bcc486c  call 0xEEC6E40                                ; -> sub_eec6e40
  bcc4871  int3                                          
  bcc4872  nop [rax+rax]                                 ; R ret@eec6e40+0x0+idx
  bcc4880  mov [rsp+0x10],rdx                            
  bcc4885  push rbp                                      
  bcc4886  push r15                                      
  bcc4888  push r14                                      
  bcc488a  push r13                                      
  bcc488c  push r12                                      
  bcc488e  push rsi                                      
  bcc488f  push rdi                                      
  bcc4890  push rbx                                      
  bcc4891  sub rsp,0x38                                  
  bcc4895  lea rbp,[rdx+0x80]                            
  bcc489c  call 0xEEC6E40                                ; -> sub_eec6e40
  bcc48a1  int3                                          
  bcc48a2  int3                                          
  bcc48a3  int3                                          
  bcc48a4  int3                                          
  bcc48a5  int3                                          
  bcc48a6  int3                                          
  bcc48a7  int3                                          
  bcc48a8  int3                                          
  bcc48a9  int3                                          
  bcc48aa  int3                                          
  bcc48ab  int3                                          
  bcc48ac  int3                                          
  bcc48ad  int3                                          
  bcc48ae  int3                                          
  bcc48af  int3                                          
  bcc48b0  push rsi                                      
  bcc48b1  push rdi                                      
  bcc48b2  sub rsp,0x28                                  
  bcc48b6  mov rcx,[0x12AE28A0]                          ; [data_12ae28a0]
  bcc48bd  test rcx,rcx                                  
  bcc48c0  je short 0xBCC490B                            ; -> loc_bcc490b
  bcc48c2  mov rdx,[0x12AE28B0]                          ; [data_12ae28b0]
  bcc48c9  sub rdx,rcx                                   
  bcc48cc  cmp rdx,0x1000                                
  bcc48d3  jb short 0xBCC48F1                            ; -> loc_bcc48f1
  bcc48d5  mov rax,[rcx-8]                               
  bcc48d9  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcc48dd  sub rcx,rax                                   
  bcc48e0  cmp rcx,0x20                                  
  bcc48e4  jae 0xBCC4968                                 ; -> loc_bcc4968
  bcc48ea  add rdx,0x27                                  
  bcc48ee  mov rcx,rax                                   

loc_bcc48f1:  ; from bcc48d3
  bcc48f1  call 0xE935700                                ; -> sub_e935700
  bcc48f6  xorps xmm0,xmm0                               
  bcc48f9  movups [0x12AE28A0],xmm0                      ; [data_12ae28a0]
  bcc4900  mov qword ptr [0x12AE28B0],0                  ; [data_12ae28b0]

loc_bcc490b:  ; from bcc48c0
  bcc490b  mov rax,[0x12AE2890]                          ; [data_12ae2890]
  bcc4912  mov rcx,[rax+8]                               
  bcc4916  mov qword ptr [rcx],0                         
  bcc491d  mov rsi,[rax]                                 
  bcc4920  test rsi,rsi                                  
  bcc4923  je short 0xBCC4951                            ; -> loc_bcc4951
  bcc4925  nop [rax+rax]                                 

loc_bcc4930:  ; from bcc494f
  bcc4930  mov rdi,[rsi]                                 
  bcc4933  lea rcx,[rsi+0x10]                            
  bcc4937  call 0x9B250                                  ; -> sub_9b250
  bcc493c  mov edx,0x50                                  
  bcc4941  mov rcx,rsi                                   
  bcc4944  call 0xE935700                                ; -> sub_e935700
  bcc4949  mov rsi,rdi                                   
  bcc494c  test rdi,rdi                                  
  bcc494f  jne short 0xBCC4930                           ; -> loc_bcc4930

loc_bcc4951:  ; from bcc4923
  bcc4951  mov rcx,[0x12AE2890]                          ; [data_12ae2890]
  bcc4958  mov edx,0x50                                  
  bcc495d  add rsp,0x28                                  
  bcc4961  pop rdi                                       
  ... (--max 600)

```
