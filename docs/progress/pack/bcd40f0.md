# ctxpack build 0xbcd40f0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=data=native_functions.tsv:4aa79c0fe0403206218642539e682a39a0af5f62d67d032bda989fd61bce04cd,data=native_deps.tsv:1fe4952061656732bfc6db3f2d9fd9cab2b08869dc95b7037670b5bec4910ae4,data=native_boundary.tsv:6e7ad029f069c6b1fb5e2798ef91f760a7586073ba5e6351050cf30070171607,data=native_boundary_candidates.tsv:8bb54e181419c9c42374be3142e4291934993a869d499a2b80e595610c86b8d9

## HEADER
  rva        : 0xbcd40f0
  size       : 0xc3 (195 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 1 (direct), depth 1
  callers    : 3

## EXACT LISTING (0xbcd40f0..0xbcd41b3)
```
sub_bcd40f0  [0xbcd40f0..0xbcd60f0)  size 0x2000  4 xrefs in
  bcd40f0  push rsi                                      
  bcd40f1  push rdi                                      
  bcd40f2  push rbx                                      
  bcd40f3  sub rsp,0x30                                  
  bcd40f7  mov rsi,rcx                                   
  bcd40fa  mov rax,[rcx]                                 ; R a0+0x0
  bcd40fd  mov rcx,[rax+8]                               ; R *(a0+0x0)+0x8
  bcd4101  mov qword ptr [rcx],0                         ; W *(*(a0+0x0)+0x8)+0x0
  bcd4108  mov rdi,[rax]                                 ; R *(a0+0x0)+0x0
  bcd410b  test rdi,rdi                                  
  bcd410e  jne short 0xBCD415E                           ; -> loc_bcd415e

loc_bcd4110:  ; from bcd415c
  bcd4110  mov rcx,[rsi]                                 ; R a0+0x0
  bcd4113  mov edx,0x80                                  
  bcd4118  add rsp,0x30                                  
  bcd411c  pop rbx                                       
  bcd411d  pop rdi                                       
  bcd411e  pop rsi                                       
  bcd411f  jmp 0xE935700                                 ; -> sub_e935700
  bcd4124  nop [rax+rax]                                 ; R *(a0+0x0)+0x0+idx

loc_bcd4130:  ; from bcd417a, bcd4197
  bcd4130  call 0xE935700                                ; -> sub_e935700

loc_bcd4135:  ; from bcd4169
  bcd4135  mov qword ptr [rdi+0x20],0                    
  bcd413d  mov qword ptr [rdi+0x28],0xF                  
  bcd4145  mov byte ptr [rdi+0x10],0                     
  bcd4149  mov edx,0x80                                  
  bcd414e  mov rcx,rdi                                   
  bcd4151  call 0xE935700                                ; -> sub_e935700
  bcd4156  mov rdi,rbx                                   
  bcd4159  test rbx,rbx                                  
  bcd415c  je short 0xBCD4110                            ; -> loc_bcd4110

loc_bcd415e:  ; from bcd410e
  bcd415e  mov rbx,[rdi]                                 
  bcd4161  mov rax,[rdi+0x28]                            
  bcd4165  cmp rax,0x10                                  
  bcd4169  jb short 0xBCD4135                            ; -> loc_bcd4135
  bcd416b  mov rcx,[rdi+0x10]                            
  bcd416f  lea rdx,[rax+1]                               
  bcd4173  cmp rdx,0x1000                                
  bcd417a  jb short 0xBCD4130                            ; -> loc_bcd4130
  bcd417c  mov r8,[rcx-8]                                
  bcd4180  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd4184  sub rcx,r8                                    
  bcd4187  cmp rcx,0x20                                  
  bcd418b  jae short 0xBCD4199                           ; -> loc_bcd4199
  bcd418d  add rax,0x28                                  
  bcd4191  mov rdx,rax                                   
  bcd4194  mov rcx,r8                                    
  bcd4197  jmp short 0xBCD4130                           ; -> loc_bcd4130

loc_bcd4199:  ; from bcd418b
  bcd4199  mov qword ptr [rsp+0x20],0                    
  bcd41a2  xor ecx,ecx                                   
  bcd41a4  xor edx,edx                                   
  bcd41a6  xor r8d,r8d                                   
  bcd41a9  xor r9d,r9d                                   
  bcd41ac  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcd41b2  int3                                          
  bcd41b3  int3                                          
  bcd41b4  int3                                          
  bcd41b5  int3                                          
  bcd41b6  int3                                          
  bcd41b7  int3                                          
  bcd41b8  int3                                          
  bcd41b9  int3                                          
  bcd41ba  int3                                          
  bcd41bb  int3                                          
  bcd41bc  int3                                          
  bcd41bd  int3                                          
  bcd41be  int3                                          
  bcd41bf  int3                                          
  bcd41c0  push r14                                      
  bcd41c2  push rsi                                      
  bcd41c3  push rdi                                      
  bcd41c4  push rbx                                      
  bcd41c5  sub rsp,0x28                                  
  bcd41c9  mov rdi,[rcx]                                 
  bcd41cc  test rdi,rdi                                  
  bcd41cf  je short 0xBCD4249                            ; -> loc_bcd4249
  bcd41d1  mov rsi,rcx                                   
  bcd41d4  mov r14,[rcx+8]                               
  bcd41d8  cmp rdi,r14                                   
  bcd41db  jne short 0xBCD41E9                           ; -> loc_bcd41e9
  bcd41dd  jmp short 0xBCD420B                           ; -> loc_bcd420b
  bcd41df  nop                                           

loc_bcd41e0:  ; from bcd41ef, bcd4206
  bcd41e0  add rdi,8                                     
  bcd41e4  cmp rdi,r14                                   
  bcd41e7  je short 0xBCD4208                            ; -> loc_bcd4208

loc_bcd41e9:  ; from bcd41db
  bcd41e9  mov rbx,[rdi]                                 
  bcd41ec  test rbx,rbx                                  
  bcd41ef  je short 0xBCD41E0                            ; -> loc_bcd41e0
  bcd41f1  mov rcx,rbx                                   
  bcd41f4  call 0xE87C6D0                                ; -> sub_e87c6d0
  bcd41f9  mov edx,0x38                                  
  bcd41fe  mov rcx,rbx                                   
  bcd4201  call 0xE935700                                ; -> sub_e935700
  bcd4206  jmp short 0xBCD41E0                           ; -> loc_bcd41e0

loc_bcd4208:  ; from bcd41e7
  bcd4208  mov rdi,[rsi]                                 

loc_bcd420b:  ; from bcd41dd
  bcd420b  mov rdx,[rsi+0x10]                            
  bcd420f  sub rdx,rdi                                   
  bcd4212  cmp rdx,0x1000                                
  bcd4219  jb short 0xBCD4233                            ; -> loc_bcd4233
  bcd421b  mov rax,[rdi-8]                               
  bcd421f  add rdi,0xFFFFFFFFFFFFFFF8                    
  bcd4223  sub rdi,rax                                   
  bcd4226  cmp rdi,0x20                                  
  bcd422a  jae short 0xBCD4253                           ; -> loc_bcd4253
  bcd422c  add rdx,0x27                                  
  bcd4230  mov rdi,rax                                   

loc_bcd4233:  ; from bcd4219
  bcd4233  mov rcx,rdi                                   
  bcd4236  call 0xE935700                                ; -> sub_e935700
  bcd423b  xorps xmm0,xmm0                               
  bcd423e  movups [rsi],xmm0                             
  bcd4241  mov qword ptr [rsi+0x10],0                    

loc_bcd4249:  ; from bcd41cf
  bcd4249  add rsp,0x28                                  
  bcd424d  pop rbx                                       
  bcd424e  pop rdi                                       
  bcd424f  pop rsi                                       
  bcd4250  pop r14                                       
  bcd4252  ret                                           

loc_bcd4253:  ; from bcd422a
  bcd4253  mov qword ptr [rsp+0x20],0                    
  bcd425c  xor ecx,ecx                                   
  bcd425e  xor edx,edx                                   
  bcd4260  xor r8d,r8d                                   
  bcd4263  xor r9d,r9d                                   
  bcd4266  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcd426c  int3                                          
  bcd426d  int3                                          
  bcd426e  int3                                          
  bcd426f  int3                                          
  bcd4270  push rsi                                      
  bcd4271  push rdi                                      
  bcd4272  push rbx                                      
  bcd4273  sub rsp,0x30                                  
  bcd4277  mov rsi,rcx                                   
  bcd427a  mov rcx,[rcx+0x18]                            
  bcd427e  test rcx,rcx                                  
  bcd4281  je short 0xBCD42C2                            ; -> loc_bcd42c2
  bcd4283  mov rdx,[rsi+0x28]                            
  bcd4287  sub rdx,rcx                                   
  bcd428a  cmp rdx,0x1000                                
  bcd4291  jb short 0xBCD42AB                            ; -> loc_bcd42ab
  bcd4293  mov rax,[rcx-8]                               
  bcd4297  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd429b  sub rcx,rax                                   
  bcd429e  cmp rcx,0x20                                  
  bcd42a2  jae short 0xBCD4316                           ; -> loc_bcd4316
  bcd42a4  add rdx,0x27                                  
  bcd42a8  mov rcx,rax                                   

loc_bcd42ab:  ; from bcd4291
  bcd42ab  lea rdi,[rsi+0x18]                            
  bcd42af  call 0xE935700                                ; -> sub_e935700
  bcd42b4  xorps xmm0,xmm0                               
  bcd42b7  movups [rdi],xmm0                             
  bcd42ba  mov qword ptr [rdi+0x10],0                    

loc_bcd42c2:  ; from bcd4281
  bcd42c2  mov rax,[rsi+8]                               
  bcd42c6  mov rcx,[rax+8]                               
  bcd42ca  mov qword ptr [rcx],0                         
  bcd42d1  mov rdi,[rax]                                 
  bcd42d4  test rdi,rdi                                  
  bcd42d7  je short 0xBCD4301                            ; -> loc_bcd4301
  bcd42d9  nop [rax]                                     

loc_bcd42e0:  ; from bcd42ff
  bcd42e0  mov rbx,[rdi]                                 
  bcd42e3  lea rcx,[rdi+0x10]                            
  bcd42e7  call 0xBCD4560                                ; -> sub_bcd4560
  bcd42ec  mov edx,0xC0                                  
  bcd42f1  mov rcx,rdi                                   
  bcd42f4  call 0xE935700                                ; -> sub_e935700
  bcd42f9  mov rdi,rbx                                   
  bcd42fc  test rbx,rbx                                  
  bcd42ff  jne short 0xBCD42E0                           ; -> loc_bcd42e0

loc_bcd4301:  ; from bcd42d7
  bcd4301  mov rcx,[rsi+8]                               
  bcd4305  mov edx,0xC0                                  
  bcd430a  add rsp,0x30                                  
  bcd430e  pop rbx                                       
  bcd430f  pop rdi                                       
  bcd4310  pop rsi                                       
  bcd4311  jmp 0xE935700                                 ; -> sub_e935700

loc_bcd4316:  ; from bcd42a2
  bcd4316  mov qword ptr [rsp+0x20],0                    
  bcd431f  xor ecx,ecx                                   
  bcd4321  xor edx,edx                                   
  bcd4323  xor r8d,r8d                                   
  bcd4326  xor r9d,r9d                                   
  bcd4329  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcd432f  int3                                          
  bcd4330  push rbp                                      
  bcd4331  push rsi                                      
  bcd4332  push rdi                                      
  bcd4333  push rbx                                      
  bcd4334  sub rsp,0x58                                  
  bcd4338  lea rbp,[rsp+0x50]                            
  bcd433d  movaps [rbp-0x10],xmm6                        
  bcd4341  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE   
  bcd4349  mov rsi,rcx                                   
  bcd434c  mov eax,[rdx]                                 
  bcd434e  mov [rcx],eax                                 
  bcd4350  xorps xmm6,xmm6                               
  bcd4353  movups [rcx+8],xmm6                           
  bcd4357  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bcd435e  mov rax,[rcx]                                 
  bcd4361  mov rax,[rax+8]                               
  bcd4365  mov edx,0xC0                                  
  bcd436a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcd4370  mov rdi,rax                                   
  bcd4373  test rax,rax                                  
  bcd4376  je 0xBCD4478                                  ; -> loc_bcd4478

loc_bcd437c:  ; from bcd4482
  bcd437c  lea rax,[rsi+8]                               
  bcd4380  mov [rbp-0x28],rax                            
  bcd4384  mov [rdi],rdi                                 
  bcd4387  mov [rdi+8],rdi                               
  bcd438b  mov [rsi+8],rdi                               
  bcd438f  lea rax,[rsi+0x18]                            
  bcd4393  mov [rbp-0x20],rax                            
  bcd4397  movups [rsi+0x18],xmm6                        
  bcd439b  mov qword ptr [rsi+0x28],0                    
  bcd43a3  mov qword ptr [rsi+0x30],7                    
  bcd43ab  mov qword ptr [rsi+0x38],8                    
  bcd43b3  mov dword ptr [rsi],0x3F800000                
  bcd43b9  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bcd43c0  mov rax,[rcx]                                 
  bcd43c3  mov rax,[rax+8]                               
  bcd43c7  mov edx,0x80                                  
  bcd43cc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bcd43d2  nop                                           
  bcd43d3  mov rbx,rax                                   
  bcd43d6  test rax,rax                                  
  bcd43d9  je 0xBCD4487                                  ; -> loc_bcd4487

loc_bcd43df:  ; from bcd4492
  bcd43df  mov rcx,[rsi+0x18]                            
  bcd43e3  mov rdx,[rsi+0x28]                            
  bcd43e7  sub rdx,rcx                                   
  bcd43ea  je short 0xBCD4416                            ; -> loc_bcd4416
  bcd43ec  cmp rdx,0x1000                                
  bcd43f3  jb short 0xBCD4411                            ; -> loc_bcd4411
  bcd43f5  mov rax,[rcx-8]                               
  bcd43f9  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd43fd  sub rcx,rax                                   
  bcd4400  cmp rcx,0x20                                  
  bcd4404  jae 0xBCD4497                                 ; -> loc_bcd4497
  bcd440a  add rdx,0x27                                  
  bcd440e  mov rcx,rax                                   

loc_bcd4411:  ; from bcd43f3
  bcd4411  call 0xE935700                                ; -> sub_e935700

loc_bcd4416:  ; from bcd43ea
  bcd4416  mov [rsi+0x18],rbx                            
  bcd441a  mov rax,rbx                                   
  bcd441d  sub rax,0xFFFFFFFFFFFFFF80                    
  bcd4421  mov [rsi+0x20],rax                            
  bcd4425  mov [rsi+0x28],rax                            
  bcd4429  mov [rbx],rdi                                 
  bcd442c  mov [rbx+8],rdi                               
  bcd4430  mov [rbx+0x10],rdi                            
  bcd4434  mov [rbx+0x18],rdi                            
  bcd4438  mov [rbx+0x20],rdi                            
  bcd443c  mov [rbx+0x28],rdi                            
  bcd4440  mov [rbx+0x30],rdi                            
  bcd4444  mov [rbx+0x38],rdi                            
  bcd4448  mov [rbx+0x40],rdi                            
  bcd444c  mov [rbx+0x48],rdi                            
  bcd4450  mov [rbx+0x50],rdi                            
  bcd4454  mov [rbx+0x58],rdi                            
  bcd4458  mov [rbx+0x60],rdi                            
  bcd445c  mov [rbx+0x68],rdi                            
  bcd4460  mov [rbx+0x70],rdi                            
  bcd4464  mov [rbx+0x78],rdi                            
  bcd4468  mov rax,rsi                                   
  bcd446b  movaps xmm6,[rbp-0x10]                        
  bcd446f  add rsp,0x58                                  
  bcd4473  pop rbx                                       
  bcd4474  pop rdi                                       
  bcd4475  pop rsi                                       
  bcd4476  pop rbp                                       
  bcd4477  ret                                           

loc_bcd4478:  ; from bcd4376
  bcd4478  mov ecx,0xC0                                  
  bcd447d  call 0x9BC830                                 ; -> sub_9bc830
  bcd4482  jmp 0xBCD437C                                 ; -> loc_bcd437c

loc_bcd4487:  ; from bcd43d9
  bcd4487  mov ecx,0x80                                  
  bcd448c  call 0x9BC830                                 ; -> sub_9bc830
  bcd4491  nop                                           
  bcd4492  jmp 0xBCD43DF                                 ; -> loc_bcd43df

loc_bcd4497:  ; from bcd4404
  bcd4497  mov qword ptr [rsp+0x20],0                    
  bcd44a0  xor ecx,ecx                                   
  bcd44a2  xor edx,edx                                   
  bcd44a4  xor r8d,r8d                                   
  bcd44a7  xor r9d,r9d                                   
  bcd44aa  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcd44b0  int3                                          
  bcd44b1  nop [rax+rax]                                 
  bcd44c0  mov [rsp+0x10],rdx                            
  bcd44c5  push rbp                                      
  bcd44c6  push rsi                                      
  bcd44c7  push rdi                                      
  bcd44c8  push rbx                                      
  bcd44c9  sub rsp,0x38                                  
  bcd44cd  lea rbp,[rdx+0x50]                            
  bcd44d1  movaps [rsp+0x20],xmm6                        
  bcd44d6  mov rcx,[rbp-0x20]                            
  bcd44da  call 0x75D00                                  ; -> sub_75d00
  bcd44df  mov rcx,[rbp-0x28]                            
  bcd44e3  call 0xBCD4500                                ; -> sub_bcd4500
  bcd44e8  movaps xmm6,[rsp+0x20]                        
  bcd44ed  add rsp,0x38                                  
  bcd44f1  pop rbx                                       
  bcd44f2  pop rdi                                       
  bcd44f3  pop rsi                                       
  bcd44f4  pop rbp                                       
  bcd44f5  ret                                           
  bcd44f6  int3                                          
  bcd44f7  int3                                          
  bcd44f8  int3                                          
  bcd44f9  int3                                          
  bcd44fa  int3                                          
  bcd44fb  int3                                          
  bcd44fc  int3                                          
  bcd44fd  int3                                          
  bcd44fe  int3                                          
  bcd44ff  int3                                          
  bcd4500  push rsi                                      
  bcd4501  push rdi                                      
  bcd4502  push rbx                                      
  bcd4503  sub rsp,0x20                                  
  bcd4507  mov rsi,rcx                                   
  bcd450a  mov rax,[rcx]                                 
  bcd450d  mov rcx,[rax+8]                               
  bcd4511  mov qword ptr [rcx],0                         
  bcd4518  mov rdi,[rax]                                 
  bcd451b  test rdi,rdi                                  
  bcd451e  je short 0xBCD4541                            ; -> loc_bcd4541

loc_bcd4520:  ; from bcd453f
  bcd4520  mov rbx,[rdi]                                 
  bcd4523  lea rcx,[rdi+0x10]                            
  bcd4527  call 0xBCD4560                                ; -> sub_bcd4560
  bcd452c  mov edx,0xC0                                  
  bcd4531  mov rcx,rdi                                   
  bcd4534  call 0xE935700                                ; -> sub_e935700
  bcd4539  mov rdi,rbx                                   
  bcd453c  test rbx,rbx                                  
  bcd453f  jne short 0xBCD4520                           ; -> loc_bcd4520

loc_bcd4541:  ; from bcd451e
  bcd4541  mov rcx,[rsi]                                 
  bcd4544  mov edx,0xC0                                  
  bcd4549  add rsp,0x20                                  
  bcd454d  pop rbx                                       
  bcd454e  pop rdi                                       
  bcd454f  pop rsi                                       
  bcd4550  jmp 0xE935700                                 ; -> sub_e935700
  bcd4555  int3                                          
  bcd4556  int3                                          
  bcd4557  int3                                          
  bcd4558  int3                                          
  bcd4559  int3                                          
  bcd455a  int3                                          
  bcd455b  int3                                          
  bcd455c  int3                                          
  bcd455d  int3                                          
  bcd455e  int3                                          
  bcd455f  int3                                          
  bcd4560  push rsi                                      
  bcd4561  sub rsp,0x30                                  
  bcd4565  mov rsi,rcx                                   
  bcd4568  add rcx,0x48                                  
  bcd456c  call 0xBCD4630                                ; -> sub_bcd4630
  bcd4571  mov rax,[rsi+0x40]                            
  bcd4575  cmp rax,0x10                                  
  bcd4579  jb short 0xBCD45AC                            ; -> loc_bcd45ac
  bcd457b  mov rcx,[rsi+0x28]                            
  bcd457f  lea rdx,[rax+1]                               
  bcd4583  cmp rdx,0x1000                                
  bcd458a  jb short 0xBCD45A7                            ; -> loc_bcd45a7
  bcd458c  mov r8,[rcx-8]                                
  bcd4590  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd4594  sub rcx,r8                                    
  bcd4597  cmp rcx,0x20                                  
  bcd459b  jae short 0xBCD4613                           ; -> loc_bcd4613
  bcd459d  add rax,0x28                                  
  bcd45a1  mov rdx,rax                                   
  bcd45a4  mov rcx,r8                                    

loc_bcd45a7:  ; from bcd458a
  bcd45a7  call 0xE935700                                ; -> sub_e935700

loc_bcd45ac:  ; from bcd4579
  bcd45ac  mov qword ptr [rsi+0x38],0                    
  bcd45b4  mov qword ptr [rsi+0x40],0xF                  
  bcd45bc  mov byte ptr [rsi+0x28],0                     
  bcd45c0  mov rax,[rsi+0x18]                            
  bcd45c4  cmp rax,0x10                                  
  bcd45c8  jb short 0xBCD45FA                            ; -> loc_bcd45fa
  bcd45ca  mov rcx,[rsi]                                 
  bcd45cd  lea rdx,[rax+1]                               
  bcd45d1  cmp rdx,0x1000                                
  bcd45d8  jb short 0xBCD45F5                            ; -> loc_bcd45f5
  bcd45da  mov r8,[rcx-8]                                
  bcd45de  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd45e2  sub rcx,r8                                    
  bcd45e5  cmp rcx,0x20                                  
  bcd45e9  jae short 0xBCD4613                           ; -> loc_bcd4613
  bcd45eb  add rax,0x28                                  
  bcd45ef  mov rdx,rax                                   
  bcd45f2  mov rcx,r8                                    

loc_bcd45f5:  ; from bcd45d8
  bcd45f5  call 0xE935700                                ; -> sub_e935700

loc_bcd45fa:  ; from bcd45c8
  bcd45fa  mov qword ptr [rsi+0x10],0                    
  bcd4602  mov qword ptr [rsi+0x18],0xF                  
  bcd460a  mov byte ptr [rsi],0                          
  bcd460d  add rsp,0x30                                  
  bcd4611  pop rsi                                       
  bcd4612  ret                                           

loc_bcd4613:  ; from bcd459b, bcd45e9
  bcd4613  mov qword ptr [rsp+0x20],0                    
  bcd461c  xor ecx,ecx                                   
  bcd461e  xor edx,edx                                   
  bcd4620  xor r8d,r8d                                   
  bcd4623  xor r9d,r9d                                   
  bcd4626  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcd462c  int3                                          
  bcd462d  int3                                          
  ... (--max 400)
```

## CALLERS
```
  0xbcd2930 sub_bcd2930 size 0x3a0
  0xbcd5730 sub_bcd5730 size 0x36
  0xe86c820 sub_e86c820 size 0x687
  -- 3 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0xe935700   sub_e935700       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_e935700.cpp;src\client\features\render\native\helpers\sub_e935700.h

## STRINGS AND RIP REFS
  (none)

## FIELD ACCESS TABLE (descscan2, regs rdi,rsi,r9,r15)
  (no [reg+off] description reads detected; register unknown -> [open])

## KNOWN STRUCT LAYOUTS TOUCHED
  (none detected)

## CLOSEST FINISHED LIFT (style example, same size band + call shape)
  bc75b20.md  size 0xb9  callees~77  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\bc75b20.md

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

