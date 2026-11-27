# ctxpack build 0xbc6ef50

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=data=native_functions.tsv:07ea6058496f3c9340e582f2f9bc57b61494694303373d3389ba71c5842a53a6,data=native_deps.tsv:118356f1f1ba724d2eb40c7fc481ea24319c1aeba9f482039b865d6efece1f8b,data=native_boundary.tsv:058a56d8016eceaff394a955dc2a241d4a8a7d44663fc4cd9102ea82d9ec7315,data=native_boundary_candidates.tsv:b2db6e93be378325c9c8b370ea57463e6e4d762ef5f0a1cae81562abc4635b8c,data=ctx_facts.tsv:d2352cf1ceb26c34830b966be082a5e21a28f989c09fa2d4ecdfb97458b56aab,data=ctx_deadends.md:298967a276b4b7e4454961297c117289bf5ed3fcdf45c3240615fc10ed423c83

## HEADER
  rva        : 0xbc6ef50
  size       : 0xf1 (241 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 5 (direct), depth 1
  callers    : 1

## EXACT LISTING (0xbc6ef50..0xbc6f041)
```
sub_bc6ef50  [0xbc6ef50..0xbc70f50)  size 0x2000  1 xrefs in
  bc6ef50  push rbp                                      
  bc6ef51  push r15                                      
  bc6ef53  push r14                                      
  bc6ef55  push r12                                      
  bc6ef57  push rsi                                      
  bc6ef58  push rdi                                      
  bc6ef59  push rbx                                      
  bc6ef5a  sub rsp,0x40                                  
  bc6ef5e  lea rbp,[rsp+0x40]                            
  bc6ef63  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE      
  bc6ef6b  mov rdi,r8                                    
  bc6ef6e  mov r14d,edx                                  
  bc6ef71  mov rbx,rcx                                   
  bc6ef74  lea r15,[rcx+0x3D0]                           ; R a0+0x3D0
  bc6ef7b  mov rcx,r15                                   
  bc6ef7e  call 0xEBDBF10                                ; -> sub_ebdbf10
  bc6ef83  movzx esi,word ptr [rbx+0x4E8]                ; R a0+0x4E8
  bc6ef8a  test rdi,rdi                                  
  bc6ef8d  je 0xBC6F027                                  ; -> loc_bc6f027
  bc6ef93  cmp r14w,si                                   
  bc6ef97  cmovb esi,r14d                                
  bc6ef9b  test si,si                                    
  bc6ef9e  je 0xBC6F025                                  ; -> loc_bc6f025
  bc6efa4  mov [rbp-0x10],r15                            
  bc6efa8  add rbx,0x4F0                                 
  bc6efaf  movzx r15d,si                                 
  bc6efb3  lea r12,[0xF847A07]                           ; [data_f847a07]
  bc6efba  lea r14,[rbp-0x20]                            
  bc6efbe  xchg ax,ax                                    

loc_bc6efc0:  ; from bc6f01d
  bc6efc0  mov r8d,0x138                                 
  bc6efc6  mov rcx,rdi                                   
  bc6efc9  mov rdx,rbx                                   
  bc6efcc  call 0xEEC6EC0                                ; -> sub_eec6ec0
  bc6efd1  mov [rbp-0x20],r12                            
  bc6efd5  mov dword ptr [rbp-0x18],0                    
  bc6efdc  mov rcx,rbx                                   
  bc6efdf  mov edx,0x7FFFFFFF                            
  bc6efe4  call 0xEBCE5E0                                ; -> sub_ebce5e0
  bc6efe9  nop                                           
  bc6efea  test eax,eax                                  
  bc6efec  je short 0xBC6EFF5                            ; -> loc_bc6eff5
  bc6efee  mov [rbp-0x18],eax                            
  bc6eff1  mov [rbp-0x20],rbx                            

loc_bc6eff5:  ; from bc6efec
  bc6eff5  mov rcx,rdi                                   
  bc6eff8  mov edx,0x100                                 
  bc6effd  mov r8,r14                                    
  bc6f000  mov r9d,0x7FFFFFFF                            
  bc6f006  call 0xEBCE650                                ; -> sub_ebce650
  bc6f00b  nop                                           
  bc6f00c  add rdi,0x138                                 
  bc6f013  add rbx,0x138                                 
  bc6f01a  dec r15                                       
  bc6f01d  jne short 0xBC6EFC0                           ; -> loc_bc6efc0
  bc6f01f  mov r15,[rbp-0x10]                            
  bc6f023  jmp short 0xBC6F027                           ; -> loc_bc6f027

loc_bc6f025:  ; from bc6ef9e
  bc6f025  xor esi,esi                                   

loc_bc6f027:  ; from bc6ef8d, bc6f023
  bc6f027  mov rcx,r15                                   
  bc6f02a  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc6f02f  nop                                           
  bc6f030  mov eax,esi                                   
  bc6f032  add rsp,0x40                                  
  bc6f036  pop rbx                                       
  bc6f037  pop rdi                                       
  bc6f038  pop rsi                                       
  bc6f039  pop r12                                       
  bc6f03b  pop r14                                       
  bc6f03d  pop r15                                       
  bc6f03f  pop rbp                                       
  bc6f040  ret                                           
  bc6f041  nop [rax+rax]                                 
  bc6f050  mov [rsp+0x10],rdx                            
  bc6f055  push rbp                                      
  bc6f056  push r15                                      
  bc6f058  push r14                                      
  bc6f05a  push r12                                      
  bc6f05c  push rsi                                      
  bc6f05d  push rdi                                      
  bc6f05e  push rbx                                      
  bc6f05f  sub rsp,0x20                                  
  bc6f063  lea rbp,[rdx+0x40]                            
  bc6f067  mov rcx,[rbp-0x10]                            
  bc6f06b  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc6f070  nop                                           
  bc6f071  add rsp,0x20                                  
  bc6f075  pop rbx                                       
  bc6f076  pop rdi                                       
  bc6f077  pop rsi                                       
  bc6f078  pop r12                                       
  bc6f07a  pop r14                                       
  bc6f07c  pop r15                                       
  bc6f07e  pop rbp                                       
  bc6f07f  ret                                           
  bc6f080  mov [rsp+0x10],rdx                            
  bc6f085  push rbp                                      
  bc6f086  push r15                                      
  bc6f088  push r14                                      
  bc6f08a  push r12                                      
  bc6f08c  push rsi                                      
  bc6f08d  push rdi                                      
  bc6f08e  push rbx                                      
  bc6f08f  sub rsp,0x20                                  
  bc6f093  lea rbp,[rdx+0x40]                            
  bc6f097  call 0xEEC6E40                                ; -> sub_eec6e40
  bc6f09c  int3                                          
  bc6f09d  int3                                          
  bc6f09e  int3                                          
  bc6f09f  int3                                          
  bc6f0a0  push rbp                                      
  bc6f0a1  push rsi                                      
  bc6f0a2  push rdi                                      
  bc6f0a3  push rbx                                      
  bc6f0a4  sub rsp,0x58                                  
  bc6f0a8  lea rbp,[rsp+0x50]                            
  bc6f0ad  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE        
  bc6f0b5  mov rdi,r8                                    
  bc6f0b8  mov rsi,rdx                                   
  bc6f0bb  mov rbx,rcx                                   
  bc6f0be  mov [rbp-4],r9w                               
  bc6f0c3  mov [rbp-0x18],r8                             
  bc6f0c7  add rcx,0x1C0                                 
  bc6f0ce  mov [rbp-0x10],rcx                            
  bc6f0d2  call 0xEBDBF10                                ; -> sub_ebdbf10
  bc6f0d7  movzx eax,word ptr [rbx+0x1DE534C]            
  bc6f0de  movzx ecx,word ptr [rbx+0x1DE534E]            
  bc6f0e5  cmp ax,cx                                     
  bc6f0e8  jae 0xBC6F1D7                                 ; -> loc_bc6f1d7
  bc6f0ee  movzx edx,ax                                  
  bc6f0f1  lea r8d,[rax+1]                               
  bc6f0f5  mov [rbx+0x1DE534C],r8w                       
  bc6f0fd  movzx edx,word ptr [rbx+rdx*2+0x1DE5350]      
  bc6f105  lea rcx,[rbx+rcx*2]                           
  bc6f109  add rcx,0x1DE5350                             
  bc6f110  mov [rcx+rdx*2],ax                            
  bc6f114  mov [rsi],dx                                  
  bc6f117  cmp edx,0xFFFF                                
  bc6f11d  je 0xBC6F1DC                                  ; -> loc_bc6f1dc
  bc6f123  mov eax,[rdi+8]                               
  bc6f126  mov [rbx+rdx*4+0x1D9D0C8],eax                 
  bc6f12d  mov rbx,[rbx+0x1CFD0C8]                       
  bc6f134  mov byte ptr [rbp-1],3                        
  bc6f138  mov eax,[rbx+0xDC5818]                        
  bc6f13e  lea rcx,[rbx+rax+0xDC5820]                    
  bc6f146  lea rdx,[rbp-1]                               
  bc6f14a  mov r8d,1                                     
  bc6f150  call 0xEBCE390                                ; -> sub_ebce390
  bc6f155  nop                                           
  bc6f156  lea rdi,[rbx+0xDC5820]                        
  bc6f15d  mov ecx,[rbx+0xDC5818]                        
  bc6f163  and ecx,0xFFFFFFFE                            
  bc6f166  add ecx,2                                     
  bc6f169  mov [rbx+0xDC5818],ecx                        
  bc6f16f  add rcx,rdi                                   
  bc6f172  mov r8d,2                                     
  bc6f178  mov rdx,rsi                                   
  bc6f17b  call 0xEBCE390                                ; -> sub_ebce390
  bc6f180  nop                                           
  bc6f181  mov ecx,[rbx+0xDC5818]                        
  bc6f187  add ecx,9                                     
  bc6f18a  and ecx,0xFFFFFFF8                            
  bc6f18d  mov [rbx+0xDC5818],ecx                        
  bc6f193  add rcx,rdi                                   
  bc6f196  lea rdx,[rbp-0x18]                            
  bc6f19a  mov r8d,8                                     
  bc6f1a0  call 0xEBCE390                                ; -> sub_ebce390
  bc6f1a5  nop                                           
  bc6f1a6  mov eax,[rbx+0xDC5818]                        
  bc6f1ac  add eax,9                                     
  bc6f1af  and eax,0xFFFFFFFE                            
  bc6f1b2  mov [rbx+0xDC5818],eax                        
  bc6f1b8  add rdi,rax                                   
  bc6f1bb  lea rdx,[rbp-4]                               
  bc6f1bf  mov r8d,2                                     
  bc6f1c5  mov rcx,rdi                                   
  bc6f1c8  call 0xEBCE390                                ; -> sub_ebce390
  bc6f1cd  nop                                           
  bc6f1ce  add dword ptr [rbx+0xDC5818],2                
  bc6f1d5  jmp short 0xBC6F233                           ; -> loc_bc6f233

loc_bc6f1d7:  ; from bc6f0e8
  bc6f1d7  mov word ptr [rsi],0xFFFF                     

loc_bc6f1dc:  ; from bc6f11d
  bc6f1dc  mov rcx,[rdi]                                 
  bc6f1df  lea rax,[rdi+0x10]                            
  bc6f1e3  cmp rcx,rax                                   
  bc6f1e6  je short 0xBC6F1FB                            ; -> loc_bc6f1fb
  bc6f1e8  mov rax,[rax]                                 
  bc6f1eb  test rax,rax                                  
  bc6f1ee  je short 0xBC6F1FB                            ; -> loc_bc6f1fb
  bc6f1f0  mov rdx,[rdi+0x18]                            
  bc6f1f4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc6f1fa  nop                                           

loc_bc6f1fb:  ; from bc6f1e6, bc6f1ee
  bc6f1fb  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc6f202  test rcx,rcx                                  
  bc6f205  je short 0xBC6F233                            ; -> loc_bc6f233
  bc6f207  mov rax,[rcx]                                 
  bc6f20a  mov rax,[rax+8]                               
  bc6f20e  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc6f215  mov dword ptr [rsp+0x28],0                    
  bc6f21d  mov qword ptr [rsp+0x20],0                    
  bc6f226  mov rdx,rdi                                   
  bc6f229  xor r8d,r8d                                   
  bc6f22c  xor r9d,r9d                                   
  bc6f22f  call r10                                      
  bc6f232  nop                                           

loc_bc6f233:  ; from bc6f1d5, bc6f205
  bc6f233  mov rcx,[rbp-0x10]                            
  bc6f237  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc6f23c  nop                                           
  bc6f23d  mov rax,rsi                                   
  bc6f240  add rsp,0x58                                  
  bc6f244  pop rbx                                       
  bc6f245  pop rdi                                       
  bc6f246  pop rsi                                       
  bc6f247  pop rbp                                       
  bc6f248  ret                                           
  bc6f249  nop [rax]                                     
  bc6f250  mov [rsp+0x10],rdx                            
  bc6f255  push rbp                                      
  bc6f256  push rsi                                      
  bc6f257  push rdi                                      
  bc6f258  push rbx                                      
  bc6f259  sub rsp,0x38                                  
  bc6f25d  lea rbp,[rdx+0x50]                            
  bc6f261  mov rcx,[rbp-0x10]                            
  bc6f265  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc6f26a  nop                                           
  bc6f26b  add rsp,0x38                                  
  bc6f26f  pop rbx                                       
  bc6f270  pop rdi                                       
  bc6f271  pop rsi                                       
  bc6f272  pop rbp                                       
  bc6f273  ret                                           
  bc6f274  nop [rax+rax]                                 ; R ret@ebdbf20+0x0+idx
  bc6f280  mov [rsp+0x10],rdx                            
  bc6f285  push rbp                                      
  bc6f286  push rsi                                      
  bc6f287  push rdi                                      
  bc6f288  push rbx                                      
  bc6f289  sub rsp,0x38                                  
  bc6f28d  lea rbp,[rdx+0x50]                            
  bc6f291  call 0xEEC6E40                                ; -> sub_eec6e40
  bc6f296  int3                                          
  bc6f297  int3                                          
  bc6f298  int3                                          
  bc6f299  int3                                          
  bc6f29a  int3                                          
  bc6f29b  int3                                          
  bc6f29c  int3                                          
  bc6f29d  int3                                          
  bc6f29e  int3                                          
  bc6f29f  int3                                          
  bc6f2a0  push rbp                                      
  bc6f2a1  push rsi                                      
  bc6f2a2  push rdi                                      
  bc6f2a3  sub rsp,0x40                                  
  bc6f2a7  lea rbp,[rsp+0x40]                            
  bc6f2ac  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE      
  bc6f2b4  mov esi,edx                                   
  bc6f2b6  mov rdi,rcx                                   
  bc6f2b9  mov [rbp-0xC],dx                              
  bc6f2bd  add rcx,0x1C0                                 
  bc6f2c4  mov [rbp-0x18],rcx                            
  bc6f2c8  call 0xEBDBF10                                ; -> sub_ebdbf10
  bc6f2cd  mov rax,[rdi+0x1CFD0C8]                       
  bc6f2d4  movzx ecx,word ptr [rax+0xE47828]             
  bc6f2db  mov [rax+rcx*2+0xE45828],si                   
  bc6f2e3  inc word ptr [rax+0xE47828]                   
  bc6f2ea  mov rsi,[rdi+0x1CFD0C8]                       
  bc6f2f1  mov byte ptr [rbp-9],0x1C                     
  bc6f2f5  mov eax,[rsi+0xE05820]                        
  bc6f2fb  lea rcx,[rsi+rax]                             
  bc6f2ff  add rcx,0xE05828                              
  bc6f306  lea rdx,[rbp-9]                               
  bc6f30a  mov r8d,1                                     
  bc6f310  call 0xEBCE390                                ; -> sub_ebce390
  bc6f315  nop                                           
  bc6f316  lea rax,[rsi+0xE05828]                        
  bc6f31d  mov ecx,[rsi+0xE05820]                        
  bc6f323  and ecx,0xFFFFFFFE                            
  bc6f326  add ecx,2                                     
  bc6f329  mov [rsi+0xE05820],ecx                        
  bc6f32f  add rcx,rax                                   
  bc6f332  lea rdx,[rbp-0xC]                             
  bc6f336  mov r8d,2                                     
  bc6f33c  call 0xEBCE390                                ; -> sub_ebce390
  bc6f341  nop                                           
  bc6f342  add dword ptr [rsi+0xE05820],2                
  bc6f349  mov rcx,[rbp-0x18]                            
  bc6f34d  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc6f352  nop                                           
  bc6f353  add rsp,0x40                                  
  bc6f357  pop rdi                                       
  bc6f358  pop rsi                                       
  bc6f359  pop rbp                                       
  bc6f35a  ret                                           
  bc6f35b  nop [rax+rax]                                 ; R ret@ebdbf20+0x0+idx
  bc6f360  mov [rsp+0x10],rdx                            
  bc6f365  push rbp                                      
  bc6f366  push rsi                                      
  bc6f367  push rdi                                      
  bc6f368  sub rsp,0x20                                  
  bc6f36c  lea rbp,[rdx+0x40]                            
  bc6f370  mov rcx,[rbp-0x18]                            
  bc6f374  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc6f379  nop                                           
  bc6f37a  add rsp,0x20                                  
  bc6f37e  pop rdi                                       
  bc6f37f  pop rsi                                       
  bc6f380  pop rbp                                       
  bc6f381  ret                                           
  bc6f382  nop [rax+rax]                                 ; R ret@ebdbf20+0x0+idx
  bc6f390  mov [rsp+0x10],rdx                            
  bc6f395  push rbp                                      
  bc6f396  push rsi                                      
  bc6f397  push rdi                                      
  bc6f398  sub rsp,0x20                                  
  bc6f39c  lea rbp,[rdx+0x40]                            
  bc6f3a0  call 0xEEC6E40                                ; -> sub_eec6e40
  bc6f3a5  int3                                          
  bc6f3a6  int3                                          
  bc6f3a7  int3                                          
  bc6f3a8  int3                                          
  bc6f3a9  int3                                          
  bc6f3aa  int3                                          
  bc6f3ab  int3                                          
  bc6f3ac  int3                                          
  bc6f3ad  int3                                          
  bc6f3ae  int3                                          
  bc6f3af  int3                                          
  bc6f3b0  push rbp                                      
  bc6f3b1  push rsi                                      
  bc6f3b2  push rdi                                      
  bc6f3b3  push rbx                                      
  bc6f3b4  sub rsp,0x38                                  
  bc6f3b8  lea rbp,[rsp+0x30]                            
  bc6f3bd  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE        
  bc6f3c5  mov rbx,r8                                    
  bc6f3c8  mov rsi,rdx                                   
  bc6f3cb  mov rdi,rcx                                   
  bc6f3ce  add rcx,0x1C0                                 
  bc6f3d5  mov [rbp-8],rcx                               
  bc6f3d9  call 0xEBDBF10                                ; -> sub_ebdbf10
  bc6f3de  nop                                           
  bc6f3df  mov rcx,rdi                                   
  bc6f3e2  mov rdx,rsi                                   
  bc6f3e5  mov r8,rbx                                    
  bc6f3e8  call 0xBC76490                                ; -> sub_bc76490
  bc6f3ed  nop                                           
  bc6f3ee  mov eax,[rbx]                                 
  bc6f3f0  movzx ecx,word ptr [rsi]                      
  bc6f3f3  inc word ptr [rdi+rcx*2+0x1EA69E0]            
  bc6f3fb  cmp ecx,0xFFFF                                
  bc6f401  je short 0xBC6F45E                            ; -> loc_bc6f45e
  bc6f403  imul edx,eax,0x1EBCA77                        
  bc6f409  shr edx,0x13                                  
  bc6f40c  imul edx,0x31                                 
  bc6f40f  and edx,0x7F                                  
  bc6f412  mov r8d,edx                                   
  bc6f415  nop [rax+rax]                                 

loc_bc6f420:  ; from bc6f443
  bc6f420  mov r9d,r8d                                   
  bc6f423  cmp word ptr [rdi+r9*2+0x1EA68E0],0xFFFF      
  bc6f42d  je short 0xBC6F447                            ; -> loc_bc6f447
  bc6f42f  cmp [rdi+r9*4+0x1EA66E0],eax                  
  bc6f437  je short 0xBC6F45E                            ; -> loc_bc6f45e
  bc6f439  inc r8d                                       
  bc6f43c  and r8d,0x7F                                  
  bc6f440  cmp r8d,edx                                   
  bc6f443  jne short 0xBC6F420                           ; -> loc_bc6f420
  bc6f445  jmp short 0xBC6F45E                           ; -> loc_bc6f45e

loc_bc6f447:  ; from bc6f42d
  bc6f447  mov [rdi+r9*4+0x1EA66E0],eax                  
  bc6f44f  mov [rdi+r9*2+0x1EA68E0],cx                   
  bc6f458  inc dword ptr [rdi+0x1EA66DC]                 

loc_bc6f45e:  ; from bc6f401, bc6f437, bc6f445
  bc6f45e  mov rcx,[rbp-8]                               
  bc6f462  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc6f467  nop                                           
  bc6f468  mov rax,rsi                                   
  bc6f46b  add rsp,0x38                                  
  bc6f46f  pop rbx                                       
  bc6f470  pop rdi                                       
  bc6f471  pop rsi                                       
  bc6f472  pop rbp                                       
  bc6f473  ret                                           
  bc6f474  nop [rax+rax]                                 
  bc6f480  mov [rsp+0x10],rdx                            
  bc6f485  push rbp                                      
  bc6f486  push rsi                                      
  bc6f487  push rdi                                      
  bc6f488  push rbx                                      
  bc6f489  sub rsp,0x28                                  
  bc6f48d  lea rbp,[rdx+0x30]                            
  bc6f491  mov rcx,[rbp-8]                               
  bc6f495  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc6f49a  nop                                           
  bc6f49b  add rsp,0x28                                  
  bc6f49f  pop rbx                                       
  bc6f4a0  pop rdi                                       
  bc6f4a1  pop rsi                                       
  bc6f4a2  pop rbp                                       
  bc6f4a3  ret                                           
  bc6f4a4  nop [rax+rax]                                 ; R ret@ebdbf20+0x0+idx
  bc6f4b0  mov [rsp+0x10],rdx                            
  bc6f4b5  push rbp                                      
  bc6f4b6  push rsi                                      
  bc6f4b7  push rdi                                      
  ... (--max 400)
```

## CALLERS
```
  0xc26b060 sub_c26b060 size 0xeda
  -- 1 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0xebce5e0   sub_ebce5e0       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_ebce5e0.cpp;src\client\features\render\native\helpers\sub_ebce5e0.h
  0xebce650   sub_ebce650       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_ebce650.cpp;src\client\features\render\native\helpers\sub_ebce650.h
  0xebdbf10   sub_ebdbf10       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_ebdbf10.cpp;src\client\features\render\native\helpers\sub_ebdbf10.h
  0xebdbf20   sub_ebdbf20       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_ebdbf20.cpp;src\client\features\render\native\helpers\sub_ebdbf20.h
  0xeec6ec0   sub_eec6ec0       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_eec6ec0.cpp;src\client\features\render\native\helpers\sub_eec6ec0.h

## STRINGS AND RIP REFS
  (none)

## FIELD ACCESS TABLE (descscan2, regs rdi,rsi,r9,r15)
  (no [reg+off] description reads detected; register unknown -> [open])

## KNOWN STRUCT LAYOUTS TOUCHED
  (none detected)

## CLOSEST FINISHED LIFT (style example, same size band + call shape)
  5667e70.md  size 0xe6  callees~25  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\5667e70.md

## KNOWN FACTS [derived]
  (none in ctx_facts.tsv for target or its direct callees/callers)

## DEAD ENDS [open]
  Unverified questions from oc_U-E*.md for target or its direct callees/callers.
  - UNRESOLVED CALL: - 0xEBCE5E0 at `0xbc5f80b  call 0xEBCE5E0` (rcx=0xF59FECD, edx=0x7FFFFFFF, eax tested) and at `0xbc5f832  call 0xEBCE5E0` (rcx=rdi=*a0+1, edx=0x7FFFFFFF, eax tested). Target not in CALLEES list (only 0xbc76380); docs/data/native_boundary.tsv does not exist; no wrapper invented. (from docs\progress\oc_U-EX1.bc5f7b0_r1.md)
  - UNRESOLVED CALL: - 0xEBDBF10 sub_ebdbf10 — caller instruction: `0xbc6ee27  call 0xEBDBF10` (preceded by 0xbc6ee24  mov rcx,rdi; rcx = a0 + 0x1C0; return value in rax unused). Seen verbatim in the disassembly at 0xbc6ee27. Absent from docs/data/native_functions.tsv, docs/data/native_boundary.tsv, docs/data/function_classes.tsv and Sigs.json → no sanctioned call mechanism (no native symbol, no boundary wrapper, not lift-classified). (from docs\progress\oc_U-EX1.bc6ee00_r1.md)
  - UNRESOLVED CALL: calls to 0xEBDBF10 (0xbc6ee27), 0xEEC6EC0 (0xbc6ee43) and 0xEBDBF20 (0xbc6ef0e) have targets in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv (also absent from Sigs.json and function_classes.tsv), so they cannot be called from lifted code through a native symbol or a boundary wrapper and no wrapper may be invented; the lift is statically complete except for these 3 calls. (from docs\progress\oc_U-EX1.bc6ee00_r1.md)
  - UNRESOLVED CALL: 0xebdbf10 — called at 0xbc6f2c8 `0xbc6f2c8  call 0xEBDBF10` (lock; argument is the address of the ctx+0x1C0 lock field): not in native_functions.tsv, not in native_boundary.tsv. (from docs\progress\oc_U-EX1.bc6f2a0_r1.md)
  - UNRESOLVED CALL: 0xebdbf10, 0xebce390, 0xebdbf20 (called at 0xbc6f2c8 / 0xbc6f310+0xbc6f33c / 0xbc6f34d) are in neither native_functions.tsv nor native_boundary.tsv, so the calls cannot be bound from lifted code and no wrapper may be invented. (from docs\progress\oc_U-EX1.bc6f2a0_r1.md)
  - UNRESOLVED CALL: 0xebdbf10 — called at 0xbc6f828 `0xbc6f828  call 0xEBDBF10` (lock; argument is the address of the ctx+0x1C0 lock field): target is `jmp qword ptr [0xF9A7B10]`; not in native_functions.tsv, not in native_boundary.tsv. (from docs\progress\oc_U-EX1.bc6f800_r1.md)
  - UNRESOLVED CALL: 0xebdbf10, 0xebce390, 0xebdbf20 (called at 0xbc6f828 / 0xbc6f870+0xbc6f89c / 0xbc6f8ad) are in neither native_functions.tsv nor native_boundary.tsv, so the calls cannot be bound from lifted code and no wrapper may be invented. (from docs\progress\oc_U-EX1.bc6f800_r1.md)
  - UNRESOLVED CALL: none — all 6 calls target lift-classified functions (0xEBDBF10 sub_ebdbf10, 0xEBCE390 x4 sub_ebce390, 0xEBDBF20 sub_ebdbf20), forward-declared in sub_bc70ff0.h per hard rule 66 (native_functions.tsv depth-0 root rows; native_boundary.tsv `lift`/`auto-unresolved->lift`). (from docs\progress\oc_U-EX1.bc70ff0.md)

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

