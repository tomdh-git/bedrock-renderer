# ctxpack build 0xbcd3f50

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb,data=ctx_facts.tsv:d2352cf1ceb26c34830b966be082a5e21a28f989c09fa2d4ecdfb97458b56aab,data=ctx_deadends.md:298967a276b4b7e4454961297c117289bf5ed3fcdf45c3240615fc10ed423c83

## HEADER
  rva        : 0xbcd3f50
  size       : 0x19f (415 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 2 (direct), depth 1
  callers    : 7

## EXACT LISTING (0xbcd3f50..0xbcd40ef)
```
sub_bcd3f50  [0xbcd3f50..0xbcd5f50)  size 0x2000  11 xrefs in
  bcd3f50  push rsi                                      
  bcd3f51  sub rsp,0x30                                  
  bcd3f55  mov rsi,rcx                                   
  bcd3f58  add rcx,0xB8                                  
  bcd3f5f  call 0x19BBC0                                 ; -> sub_19bbc0
  bcd3f64  cmp byte ptr [rsi+0xB0],1                     ; R a0+0xB0
  bcd3f6b  jne short 0xBCD3FCF                           ; -> loc_bcd3fcf
  bcd3f6d  mov rax,[rsi+0xA0]                            ; R a0+0xA0
  bcd3f74  cmp rax,0x10                                  
  bcd3f78  jb short 0xBCD3FB2                            ; -> loc_bcd3fb2
  bcd3f7a  mov rcx,[rsi+0x88]                            ; R a0+0x88
  bcd3f81  lea rdx,[rax+1]                               ; R *(a0+0xA0)+0x1
  bcd3f85  cmp rdx,0x1000                                
  bcd3f8c  jb short 0xBCD3FAD                            ; -> loc_bcd3fad
  bcd3f8e  mov r8,[rcx-8]                                ; R *(a0+0x88)-0x8
  bcd3f92  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd3f96  sub rcx,r8                                    
  bcd3f99  cmp rcx,0x20                                  
  bcd3f9d  jae 0xBCD40D5                                 ; -> loc_bcd40d5
  bcd3fa3  add rax,0x28                                  
  bcd3fa7  mov rdx,rax                                   
  bcd3faa  mov rcx,r8                                    

loc_bcd3fad:  ; from bcd3f8c
  bcd3fad  call 0xE935700                                ; -> sub_e935700

loc_bcd3fb2:  ; from bcd3f78
  bcd3fb2  mov qword ptr [rsi+0x98],0                    ; W a0+0x98
  bcd3fbd  mov qword ptr [rsi+0xA0],0xF                  ; W a0+0xA0
  bcd3fc8  mov byte ptr [rsi+0x88],0                     ; W a0+0x88

loc_bcd3fcf:  ; from bcd3f6b
  bcd3fcf  cmp byte ptr [rsi+0x80],1                     ; R a0+0x80
  bcd3fd6  jne short 0xBCD402B                           ; -> loc_bcd402b
  bcd3fd8  mov rax,[rsi+0x78]                            ; R a0+0x78
  bcd3fdc  cmp rax,0x10                                  
  bcd3fe0  jb short 0xBCD4017                            ; -> loc_bcd4017
  bcd3fe2  mov rcx,[rsi+0x60]                            ; R a0+0x60
  bcd3fe6  lea rdx,[rax+1]                               ; R *(a0+0x78)+0x1
  bcd3fea  cmp rdx,0x1000                                
  bcd3ff1  jb short 0xBCD4012                            ; -> loc_bcd4012
  bcd3ff3  mov r8,[rcx-8]                                ; R *(a0+0x60)-0x8
  bcd3ff7  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd3ffb  sub rcx,r8                                    
  bcd3ffe  cmp rcx,0x20                                  
  bcd4002  jae 0xBCD40D5                                 ; -> loc_bcd40d5
  bcd4008  add rax,0x28                                  
  bcd400c  mov rdx,rax                                   
  bcd400f  mov rcx,r8                                    

loc_bcd4012:  ; from bcd3ff1
  bcd4012  call 0xE935700                                ; -> sub_e935700

loc_bcd4017:  ; from bcd3fe0
  bcd4017  mov qword ptr [rsi+0x70],0                    ; W a0+0x70
  bcd401f  mov qword ptr [rsi+0x78],0xF                  ; W a0+0x78
  bcd4027  mov byte ptr [rsi+0x60],0                     ; W a0+0x60

loc_bcd402b:  ; from bcd3fd6
  bcd402b  cmp byte ptr [rsi+0x58],1                     ; R a0+0x58
  bcd402f  jne short 0xBCD4080                           ; -> loc_bcd4080
  bcd4031  mov rax,[rsi+0x50]                            ; R a0+0x50
  bcd4035  cmp rax,0x10                                  
  bcd4039  jb short 0xBCD406C                            ; -> loc_bcd406c
  bcd403b  mov rcx,[rsi+0x38]                            ; R a0+0x38
  bcd403f  lea rdx,[rax+1]                               ; R *(a0+0x50)+0x1
  bcd4043  cmp rdx,0x1000                                
  bcd404a  jb short 0xBCD4067                            ; -> loc_bcd4067
  bcd404c  mov r8,[rcx-8]                                ; R *(a0+0x38)-0x8
  bcd4050  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd4054  sub rcx,r8                                    
  bcd4057  cmp rcx,0x20                                  
  bcd405b  jae short 0xBCD40D5                           ; -> loc_bcd40d5
  bcd405d  add rax,0x28                                  
  bcd4061  mov rdx,rax                                   
  bcd4064  mov rcx,r8                                    

loc_bcd4067:  ; from bcd404a
  bcd4067  call 0xE935700                                ; -> sub_e935700

loc_bcd406c:  ; from bcd4039
  bcd406c  mov qword ptr [rsi+0x48],0                    ; W a0+0x48
  bcd4074  mov qword ptr [rsi+0x50],0xF                  ; W a0+0x50
  bcd407c  mov byte ptr [rsi+0x38],0                     ; W a0+0x38

loc_bcd4080:  ; from bcd402f
  bcd4080  mov rax,[rsi+0x28]                            ; R a0+0x28
  bcd4084  cmp rax,0x10                                  
  bcd4088  jb short 0xBCD40BB                            ; -> loc_bcd40bb
  bcd408a  mov rcx,[rsi+0x10]                            ; R a0+0x10
  bcd408e  lea rdx,[rax+1]                               ; R *(a0+0x28)+0x1
  bcd4092  cmp rdx,0x1000                                
  bcd4099  jb short 0xBCD40B6                            ; -> loc_bcd40b6
  bcd409b  mov r8,[rcx-8]                                ; R *(a0+0x10)-0x8
  bcd409f  add rcx,0xFFFFFFFFFFFFFFF8                    
  bcd40a3  sub rcx,r8                                    
  bcd40a6  cmp rcx,0x20                                  
  bcd40aa  jae short 0xBCD40D5                           ; -> loc_bcd40d5
  bcd40ac  add rax,0x28                                  
  bcd40b0  mov rdx,rax                                   
  bcd40b3  mov rcx,r8                                    

loc_bcd40b6:  ; from bcd4099
  bcd40b6  call 0xE935700                                ; -> sub_e935700

loc_bcd40bb:  ; from bcd4088
  bcd40bb  mov qword ptr [rsi+0x20],0                    ; W a0+0x20
  bcd40c3  mov qword ptr [rsi+0x28],0xF                  ; W a0+0x28
  bcd40cb  mov byte ptr [rsi+0x10],0                     ; W a0+0x10
  bcd40cf  add rsp,0x30                                  
  bcd40d3  pop rsi                                       
  bcd40d4  ret                                           

loc_bcd40d5:  ; from bcd3f9d, bcd4002, bcd405b, bcd40aa
  bcd40d5  mov qword ptr [rsp+0x20],0                    
  bcd40de  xor ecx,ecx                                   
  bcd40e0  xor edx,edx                                   
  bcd40e2  xor r8d,r8d                                   
  bcd40e5  xor r9d,r9d                                   
  bcd40e8  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  bcd40ee  int3                                          
  bcd40ef  int3                                          
  bcd40f0  push rsi                                      
  bcd40f1  push rdi                                      
  bcd40f2  push rbx                                      
  bcd40f3  sub rsp,0x30                                  
  bcd40f7  mov rsi,rcx                                   
  bcd40fa  mov rax,[rcx]                                 
  bcd40fd  mov rcx,[rax+8]                               
  bcd4101  mov qword ptr [rcx],0                         
  bcd4108  mov rdi,[rax]                                 
  bcd410b  test rdi,rdi                                  
  bcd410e  jne short 0xBCD415E                           ; -> loc_bcd415e

loc_bcd4110:  ; from bcd415c
  bcd4110  mov rcx,[rsi]                                 
  bcd4113  mov edx,0x80                                  
  bcd4118  add rsp,0x30                                  
  bcd411c  pop rbx                                       
  bcd411d  pop rdi                                       
  bcd411e  pop rsi                                       
  bcd411f  jmp 0xE935700                                 ; -> sub_e935700
  bcd4124  nop [rax+rax]                                 

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
  ... (--max 400)
```

## CALLERS
```
  0xbcc7f20 sub_bcc7f20 size 0x7421
  0xbcd3ea0 sub_bcd3ea0 size 0xac
  0xbcd6270 sub_bcd6270 size 0x4fb
  0xbcd6770 sub_bcd6770 size 0xcc
  0xe870870 sub_e870870 size 0x2d7a
  0xe873f00 sub_e873f00 size 0x4d
  0xe8778b0 sub_e8778b0 size 0xa4
  -- 7 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0x19bbc0    sub_19bbc0        set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_19bbc0.cpp;src\client\features\render\native\helpers\sub_19bbc0.h
  0xe935700   sub_e935700       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_e935700.cpp;src\client\features\render\native\helpers\sub_e935700.h

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
  - UNRESOLVED CALL: - 0xe935700 (sub_e935700): `call 0xE935700` at 0xbc3c6f8 and 0xbc3c741. sub_e935700 is a thunk (`jmp sub_392960` @0xe935700). Neither sub_e935700 nor sub_392960 appears in docs/data/native_functions.tsv or docs/data/native_boundary.tsv. Declared as `extern "C" void sub_e935700(uint64_t, uint64_t, void*, void*)` matching register usage; no wrapper invented. (from docs\progress\oc_U-EX1.bc3c6b0.md)
  - UNRESOLVED CALL: 0xE935700 at 0xbc56577: `0xbc56577  call 0xE935700` — direct call target neither in the lift set (callees_in_set empty per unit data) nor in docs/data/native_boundary.tsv. Checked docs/data/native_functions.tsv, native_boundary.tsv, function_classes.tsv, native_deps.tsv, native_roots.txt, native_unresolved_indirect.tsv: no entry. Not emitted in lifted code (no wrapper per unit rules); quoted verbatim in source for coverage. (from docs\progress\oc_U-EX1.bc56190_r1.md)
  - UNRESOLVED CALL: 0xE935700 at 0xbc56577 (direct call 0xE935700: target neither lifted nor boundary); import-slot call qword ptr [0xF9A8C78] at 0xbc56600 likewise outside both tables (from docs\progress\oc_U-EX1.bc56190_r1.md)
  - UNRESOLVED CALL: none. All six calls resolved: `call 0xE935700` x2 (lift callee sub_e935700, forward-declared and called directly), `call qword ptr [0xF99FFA0]` x3 (vtable slots 4/0/1 through the jmp-rax thunk, no static target by design), `call qword ptr [0xF9A8C78]` x1 (data-slot function-pointer call, rule 69, documented with slot RVA). (from docs\progress\oc_U-EX1.bc97070.md)

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

