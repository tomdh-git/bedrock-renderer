# ctxpack build 0xc27ebd0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=c27ebd0.md:ed0a94f65810a967c8f3b614b067f081347df9dffc70444aa853ee13adf76fc9,liftsrc=sub_c27ebd0.cpp:6c4ae23584609297356be4583d366bae6681f239b2f623833bccb7e2caedc640,liftsrc=sub_c27ebd0.h:59defd2a0ba49989b5932dc90ed98d6f922398c61a971dc75c01b14494c2a206,data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb

## HEADER
  rva        : 0xc27ebd0
  size       : 0x8b (139 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 2 (direct), depth 1
  callers    : 3

## EXACT LISTING (0xc27ebd0..0xc27ec5b)
```
sub_c27ebd0  [0xc27ebd0..0xc280bd0)  size 0x2000  3 xrefs in
  c27ebd0  push rsi                                      
  c27ebd1  push rdi                                      
  c27ebd2  push rbx                                      
  c27ebd3  sub rsp,0x20                                  
  c27ebd7  cmp byte ptr [rcx+0x19],0                     ; R a0+0x19
  c27ebdb  je short 0xC27EBE5                            ; -> loc_c27ebe5

loc_c27ebdd:  ; from c27ec01
  c27ebdd  add rsp,0x20                                  
  c27ebe1  pop rbx                                       
  c27ebe2  pop rdi                                       
  c27ebe3  pop rsi                                       
  c27ebe4  ret                                           

loc_c27ebe5:  ; from c27ebdb
  c27ebe5  mov rsi,rcx                                   
  c27ebe8  jmp short 0xC27EC03                           ; -> loc_c27ec03
  c27ebea  nop [rax+rax]                                 

loc_c27ebf0:  ; from c27ec23, c27ec2c, c27ec32, c27ec47, c27ec59
  c27ebf0  mov edx,0x58                                  
  c27ebf5  mov rcx,rdi                                   
  c27ebf8  call 0xE935700                                ; -> sub_e935700
  c27ebfd  cmp byte ptr [rsi+0x19],0                     
  c27ec01  jne short 0xC27EBDD                           ; -> loc_c27ebdd

loc_c27ec03:  ; from c27ebe8
  c27ec03  mov rdi,rsi                                   
  c27ec06  mov rcx,[rsi+0x10]                            
  c27ec0a  call 0xC27EBD0                                ; -> sub_c27ebd0
  c27ec0f  mov rsi,[rsi]                                 
  c27ec12  movzx eax,byte ptr [rdi+0x50]                 
  c27ec16  cmp eax,1                                     
  c27ec19  jg short 0xC27EC20                            ; -> loc_c27ec20
  c27ec1b  test eax,eax                                  
  c27ec1d  jmp short 0xC27EC25                           ; -> loc_c27ec25
  c27ec1f  nop                                           

loc_c27ec20:  ; from c27ec19
  c27ec20  cmp eax,2                                     
  c27ec23  jne short 0xC27EBF0                           ; -> loc_c27ebf0

loc_c27ec25:  ; from c27ec1d
  c27ec25  mov rbx,[rdi+0x48]                            
  c27ec29  test rbx,rbx                                  
  c27ec2c  je short 0xC27EBF0                            ; -> loc_c27ebf0
  c27ec2e  lock dec dword ptr [rbx+8]                    
  c27ec32  jne short 0xC27EBF0                           ; -> loc_c27ebf0
  c27ec34  mov rax,[rbx]                                 
  c27ec37  mov rax,[rax]                                 
  c27ec3a  mov rcx,rbx                                   
  c27ec3d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27ec43  lock dec dword ptr [rbx+0xC]                  
  c27ec47  jne short 0xC27EBF0                           ; -> loc_c27ebf0
  c27ec49  mov rax,[rbx]                                 
  c27ec4c  mov rax,[rax+8]                               
  c27ec50  mov rcx,rbx                                   
  c27ec53  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27ec59  jmp short 0xC27EBF0                           ; -> loc_c27ebf0
  c27ec5b  int3                                          
  c27ec5c  int3                                          
  c27ec5d  int3                                          
  c27ec5e  int3                                          
  c27ec5f  int3                                          
  c27ec60  push r15                                      
  c27ec62  push r14                                      
  c27ec64  push r13                                      
  c27ec66  push r12                                      
  c27ec68  push rsi                                      
  c27ec69  push rdi                                      
  c27ec6a  push rbx                                      
  c27ec6b  sub rsp,0x30                                  
  c27ec6f  mov rsi,r9                                    
  c27ec72  mov r14,r8                                    
  c27ec75  mov rbx,rdx                                   
  c27ec78  mov rdi,rcx                                   
  c27ec7b  mov r15,[rcx]                                 
  c27ec7e  test r15,r15                                  
  c27ec81  je 0xC27ED2A                                  ; -> loc_c27ed2a
  c27ec87  mov r13,[rdi+8]                               
  c27ec8b  cmp r15,r13                                   
  c27ec8e  je short 0xC27ECFA                            ; -> loc_c27ecfa
  c27ec90  add r15,0x10                                  
  c27ec94  jmp short 0xC27ECB3                           ; -> loc_c27ecb3
  c27ec96  nop [rax+rax]                                 

loc_c27eca0:  ; from c27ecc2, c27ecca, c27ece2, c27ecf5
  c27eca0  lea rax,[r15+0x80]                            
  c27eca7  add r15,0x70                                  
  c27ecab  cmp r15,r13                                   
  c27ecae  mov r15,rax                                   
  c27ecb1  je short 0xC27ECF7                            ; -> loc_c27ecf7

loc_c27ecb3:  ; from c27ec94
  c27ecb3  mov rcx,r15                                   
  c27ecb6  call 0xC27ED70                                ; -> sub_c27ed70
  c27ecbb  mov r12,[r15-8]                               
  c27ecbf  test r12,r12                                  
  c27ecc2  je short 0xC27ECA0                            ; -> loc_c27eca0
  c27ecc4  lock dec dword ptr [r12+8]                    
  c27ecca  jne short 0xC27ECA0                           ; -> loc_c27eca0
  c27eccc  mov rax,[r12]                                 
  c27ecd0  mov rax,[rax]                                 
  c27ecd3  mov rcx,r12                                   
  c27ecd6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27ecdc  lock dec dword ptr [r12+0xC]                  
  c27ece2  jne short 0xC27ECA0                           ; -> loc_c27eca0
  c27ece4  mov rax,[r12]                                 
  c27ece8  mov rax,[rax+8]                               
  c27ecec  mov rcx,r12                                   
  c27ecef  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27ecf5  jmp short 0xC27ECA0                           ; -> loc_c27eca0

loc_c27ecf7:  ; from c27ecb1
  c27ecf7  mov r15,[rdi]                                 

loc_c27ecfa:  ; from c27ec8e
  c27ecfa  mov rdx,[rdi+0x10]                            
  c27ecfe  sub rdx,r15                                   
  c27ed01  cmp rdx,0x1000                                
  c27ed08  jb short 0xC27ED22                            ; -> loc_c27ed22
  c27ed0a  mov rax,[r15-8]                               
  c27ed0e  add r15,0xFFFFFFFFFFFFFFF8                    
  c27ed12  sub r15,rax                                   
  c27ed15  cmp r15,0x20                                  
  c27ed19  jae short 0xC27ED53                           ; -> loc_c27ed53
  c27ed1b  or rdx,0x27                                   
  c27ed1f  mov r15,rax                                   

loc_c27ed22:  ; from c27ed08
  c27ed22  mov rcx,r15                                   
  c27ed25  call 0xE935700                                ; -> sub_e935700

loc_c27ed2a:  ; from c27ec81
  c27ed2a  mov [rdi],rbx                                 
  c27ed2d  shl r14,7                                     
  c27ed31  add r14,rbx                                   
  c27ed34  mov [rdi+8],r14                               
  c27ed38  shl rsi,7                                     
  c27ed3c  add rsi,rbx                                   
  c27ed3f  mov [rdi+0x10],rsi                            
  c27ed43  add rsp,0x30                                  
  c27ed47  pop rbx                                       
  c27ed48  pop rdi                                       
  c27ed49  pop rsi                                       
  c27ed4a  pop r12                                       
  c27ed4c  pop r13                                       
  c27ed4e  pop r14                                       
  c27ed50  pop r15                                       
  c27ed52  ret                                           

loc_c27ed53:  ; from c27ed19
  c27ed53  mov qword ptr [rsp+0x20],0                    
  c27ed5c  xor ecx,ecx                                   
  c27ed5e  xor edx,edx                                   
  c27ed60  xor r8d,r8d                                   
  c27ed63  xor r9d,r9d                                   
  c27ed66  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  c27ed6c  int3                                          
  c27ed6d  int3                                          
  c27ed6e  int3                                          
  c27ed6f  int3                                          
  c27ed70  push r15                                      
  c27ed72  push r14                                      
  c27ed74  push rsi                                      
  c27ed75  push rdi                                      
  c27ed76  push rbx                                      
  c27ed77  sub rsp,0x30                                  
  c27ed7b  mov rsi,rcx                                   
  c27ed7e  mov rdi,[rcx+0x50]                            
  c27ed82  test rdi,rdi                                  
  c27ed85  je 0xC27EE25                                  ; -> loc_c27ee25
  c27ed8b  lea r14,[rsi+0x50]                            
  c27ed8f  mov r15,[rsi+0x58]                            
  c27ed93  cmp rdi,r15                                   
  c27ed96  jne short 0xC27EDA9                           ; -> loc_c27eda9
  c27ed98  jmp short 0xC27EDE2                           ; -> loc_c27ede2
  c27ed9a  nop [rax+rax]                                 

loc_c27eda0:  ; from c27edb0, c27edb6, c27edcb, c27eddd
  c27eda0  add rdi,0x20                                  
  c27eda4  cmp rdi,r15                                   
  c27eda7  je short 0xC27EDDF                            ; -> loc_c27eddf

loc_c27eda9:  ; from c27ed96
  c27eda9  mov rbx,[rdi+0x10]                            
  c27edad  test rbx,rbx                                  
  c27edb0  je short 0xC27EDA0                            ; -> loc_c27eda0
  c27edb2  lock dec dword ptr [rbx+8]                    
  c27edb6  jne short 0xC27EDA0                           ; -> loc_c27eda0
  c27edb8  mov rax,[rbx]                                 
  c27edbb  mov rax,[rax]                                 
  c27edbe  mov rcx,rbx                                   
  c27edc1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27edc7  lock dec dword ptr [rbx+0xC]                  
  c27edcb  jne short 0xC27EDA0                           ; -> loc_c27eda0
  c27edcd  mov rax,[rbx]                                 
  c27edd0  mov rax,[rax+8]                               
  c27edd4  mov rcx,rbx                                   
  c27edd7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27eddd  jmp short 0xC27EDA0                           ; -> loc_c27eda0

loc_c27eddf:  ; from c27eda7
  c27eddf  mov rdi,[r14]                                 

loc_c27ede2:  ; from c27ed98
  c27ede2  mov rdx,[rsi+0x60]                            
  c27ede6  sub rdx,rdi                                   
  c27ede9  cmp rdx,0x1000                                
  c27edf0  jb short 0xC27EE0E                            ; -> loc_c27ee0e
  c27edf2  mov rax,[rdi-8]                               
  c27edf6  add rdi,0xFFFFFFFFFFFFFFF8                    
  c27edfa  sub rdi,rax                                   
  c27edfd  cmp rdi,0x20                                  
  c27ee01  jae 0xC27EF8D                                 ; -> loc_c27ef8d
  c27ee07  add rdx,0x27                                  
  c27ee0b  mov rdi,rax                                   

loc_c27ee0e:  ; from c27edf0
  c27ee0e  mov rcx,rdi                                   
  c27ee11  call 0xE935700                                ; -> sub_e935700
  c27ee16  xorps xmm0,xmm0                               
  c27ee19  movups [r14],xmm0                             
  c27ee1d  mov qword ptr [r14+0x10],0                    

loc_c27ee25:  ; from c27ed85
  c27ee25  mov rdi,[rsi+0x38]                            
  c27ee29  test rdi,rdi                                  
  c27ee2c  je 0xC27EED5                                  ; -> loc_c27eed5
  c27ee32  lea r14,[rsi+0x38]                            
  c27ee36  mov r15,[rsi+0x40]                            
  c27ee3a  cmp rdi,r15                                   
  c27ee3d  jne short 0xC27EE59                           ; -> loc_c27ee59
  c27ee3f  jmp short 0xC27EE92                           ; -> loc_c27ee92
  c27ee41  nop [rax+rax]                                 ; R ret@e935700+0x0+idx

loc_c27ee50:  ; from c27ee60, c27ee66, c27ee7b, c27ee8d
  c27ee50  add rdi,0x20                                  
  c27ee54  cmp rdi,r15                                   
  c27ee57  je short 0xC27EE8F                            ; -> loc_c27ee8f

loc_c27ee59:  ; from c27ee3d
  c27ee59  mov rbx,[rdi+0x10]                            
  c27ee5d  test rbx,rbx                                  
  c27ee60  je short 0xC27EE50                            ; -> loc_c27ee50
  c27ee62  lock dec dword ptr [rbx+8]                    
  c27ee66  jne short 0xC27EE50                           ; -> loc_c27ee50
  c27ee68  mov rax,[rbx]                                 
  c27ee6b  mov rax,[rax]                                 
  c27ee6e  mov rcx,rbx                                   
  c27ee71  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27ee77  lock dec dword ptr [rbx+0xC]                  
  c27ee7b  jne short 0xC27EE50                           ; -> loc_c27ee50
  c27ee7d  mov rax,[rbx]                                 
  c27ee80  mov rax,[rax+8]                               
  c27ee84  mov rcx,rbx                                   
  c27ee87  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27ee8d  jmp short 0xC27EE50                           ; -> loc_c27ee50

loc_c27ee8f:  ; from c27ee57
  c27ee8f  mov rdi,[r14]                                 

loc_c27ee92:  ; from c27ee3f
  c27ee92  mov rdx,[rsi+0x48]                            
  c27ee96  sub rdx,rdi                                   
  c27ee99  cmp rdx,0x1000                                
  c27eea0  jb short 0xC27EEBE                            ; -> loc_c27eebe
  c27eea2  mov rax,[rdi-8]                               
  c27eea6  add rdi,0xFFFFFFFFFFFFFFF8                    
  c27eeaa  sub rdi,rax                                   
  c27eead  cmp rdi,0x20                                  
  c27eeb1  jae 0xC27EF8D                                 ; -> loc_c27ef8d
  c27eeb7  add rdx,0x27                                  
  c27eebb  mov rdi,rax                                   

loc_c27eebe:  ; from c27eea0
  c27eebe  mov rcx,rdi                                   
  c27eec1  call 0xE935700                                ; -> sub_e935700
  c27eec6  xorps xmm0,xmm0                               
  c27eec9  movups [r14],xmm0                             
  c27eecd  mov qword ptr [r14+0x10],0                    

loc_c27eed5:  ; from c27ee2c
  c27eed5  mov rdi,[rsi+0x20]                            
  c27eed9  test rdi,rdi                                  
  c27eedc  je 0xC27EF81                                  ; -> loc_c27ef81
  c27eee2  lea r14,[rsi+0x20]                            
  c27eee6  mov r15,[rsi+0x28]                            
  c27eeea  cmp rdi,r15                                   
  c27eeed  jne short 0xC27EF09                           ; -> loc_c27ef09
  c27eeef  jmp short 0xC27EF42                           ; -> loc_c27ef42
  c27eef1  nop [rax+rax]                                 ; R ret@e935700+0x0+idx

loc_c27ef00:  ; from c27ef10, c27ef16, c27ef2b, c27ef3d
  c27ef00  add rdi,0x28                                  
  c27ef04  cmp rdi,r15                                   
  c27ef07  je short 0xC27EF3F                            ; -> loc_c27ef3f

loc_c27ef09:  ; from c27eeed
  c27ef09  mov rbx,[rdi+0x10]                            
  c27ef0d  test rbx,rbx                                  
  c27ef10  je short 0xC27EF00                            ; -> loc_c27ef00
  c27ef12  lock dec dword ptr [rbx+8]                    
  c27ef16  jne short 0xC27EF00                           ; -> loc_c27ef00
  c27ef18  mov rax,[rbx]                                 
  c27ef1b  mov rax,[rax]                                 
  c27ef1e  mov rcx,rbx                                   
  c27ef21  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27ef27  lock dec dword ptr [rbx+0xC]                  
  c27ef2b  jne short 0xC27EF00                           ; -> loc_c27ef00
  c27ef2d  mov rax,[rbx]                                 
  c27ef30  mov rax,[rax+8]                               
  c27ef34  mov rcx,rbx                                   
  c27ef37  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c27ef3d  jmp short 0xC27EF00                           ; -> loc_c27ef00

loc_c27ef3f:  ; from c27ef07
  c27ef3f  mov rdi,[r14]                                 

loc_c27ef42:  ; from c27eeef
  c27ef42  mov rdx,[rsi+0x30]                            
  c27ef46  sub rdx,rdi                                   
  c27ef49  cmp rdx,0x1000                                
  c27ef50  jb short 0xC27EF6A                            ; -> loc_c27ef6a
  c27ef52  mov rax,[rdi-8]                               
  c27ef56  add rdi,0xFFFFFFFFFFFFFFF8                    
  c27ef5a  sub rdi,rax                                   
  c27ef5d  cmp rdi,0x20                                  
  c27ef61  jae short 0xC27EF8D                           ; -> loc_c27ef8d
  c27ef63  add rdx,0x27                                  
  c27ef67  mov rdi,rax                                   

loc_c27ef6a:  ; from c27ef50
  c27ef6a  mov rcx,rdi                                   
  c27ef6d  call 0xE935700                                ; -> sub_e935700
  c27ef72  xorps xmm0,xmm0                               
  c27ef75  movups [r14],xmm0                             
  c27ef79  mov qword ptr [r14+0x10],0                    

loc_c27ef81:  ; from c27eedc
  c27ef81  add rsp,0x30                                  
  c27ef85  pop rbx                                       
  c27ef86  pop rdi                                       
  c27ef87  pop rsi                                       
  c27ef88  pop r14                                       
  c27ef8a  pop r15                                       
  c27ef8c  ret                                           

loc_c27ef8d:  ; from c27ee01, c27eeb1, c27ef61
  c27ef8d  mov qword ptr [rsp+0x20],0                    
  c27ef96  xor ecx,ecx                                   
  c27ef98  xor edx,edx                                   
  c27ef9a  xor r8d,r8d                                   
  c27ef9d  xor r9d,r9d                                   
  c27efa0  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  c27efa6  int3                                          
  c27efa7  int3                                          
  c27efa8  int3                                          
  c27efa9  int3                                          
  c27efaa  int3                                          
  c27efab  int3                                          
  c27efac  int3                                          
  c27efad  int3                                          
  c27efae  int3                                          
  c27efaf  int3                                          
  c27efb0  push r15                                      
  c27efb2  push r14                                      
  c27efb4  push r13                                      
  c27efb6  push r12                                      
  c27efb8  push rsi                                      
  c27efb9  push rdi                                      
  c27efba  push rbp                                      
  c27efbb  push rbx                                      
  c27efbc  sub rsp,0x28                                  
  c27efc0  mov rsi,r9                                    
  c27efc3  mov rdi,rdx                                   
  c27efc6  mov r15,rcx                                   
  c27efc9  sub rdx,rcx                                   
  c27efcc  cmp rdx,0x21                                  
  c27efd0  jge 0xC27F081                                 ; -> loc_c27f081
  c27efd6  mov rbx,r15                                   

loc_c27efd9:  ; from c27f0b4
  c27efd9  cmp r15,rdi                                   
  c27efdc  je 0xC27F7E7                                  ; -> loc_c27f7e7
  c27efe2  lea r14,[r15+1]                               
  c27efe6  cmp r14,rdi                                   
  c27efe9  je 0xC27F7E7                                  ; -> loc_c27f7e7
  c27efef  mov r12,r14                                   
  c27eff2  jmp short 0xC27F023                           ; -> loc_c27f023
  c27eff4  nop [rax+rax]                                 

loc_c27f000:  ; from c27f048
  c27f000  mov r8,r12                                    
  c27f003  sub r8,rbx                                    
  c27f006  mov rcx,r14                                   
  c27f009  mov rdx,r15                                   
  c27f00c  call 0xEEC6DE0                                ; -> sub_eec6de0
  c27f011  mov rdx,r15                                   

loc_c27f014:  ; from c27f05c, c27f07f
  c27f014  mov [rdx],bpl                                 
  c27f017  inc r12                                       
  c27f01a  cmp r12,rdi                                   
  c27f01d  je 0xC27F7E7                                  ; -> loc_c27f7e7

loc_c27f023:  ; from c27eff2
  c27f023  movzx ebp,byte ptr [r12]                      
  c27f028  movzx ecx,byte ptr [r15]                      
  c27f02c  mov rax,[rsi]                                 
  c27f02f  mov r8,[rax]                                  
  c27f032  movzx eax,bpl                                 
  c27f036  lea rax,[rax+rax*4]                           
  c27f03a  lea rcx,[rcx+rcx*4]                           
  c27f03e  mov r9,[r8+rax*8+0x20]                        
  c27f043  cmp r9,[r8+rcx*8+0x20]                        
  c27f048  jb short 0xC27F000                            ; -> loc_c27f000
  c27f04a  movzx ecx,byte ptr [r12-1]                    
  c27f050  lea r10,[rcx+rcx*4]                           
  c27f054  mov rdx,r12                                   
  c27f057  cmp r9,[r8+r10*8+0x20]                        
  c27f05c  jae short 0xC27F014                           ; -> loc_c27f014
  c27f05e  xchg ax,ax                                    

loc_c27f060:  ; from c27f07d
  c27f060  mov [rdx],cl                                  
  c27f062  movzx ecx,byte ptr [rdx-2]                    
  c27f066  mov r8,[rsi]                                  
  c27f069  mov r8,[r8]                                   
  c27f06c  lea r9,[rcx+rcx*4]                            
  c27f070  mov r10,[r8+rax*8+0x20]                       
  c27f075  dec rdx                                       
  c27f078  cmp r10,[r8+r9*8+0x20]                        
  c27f07d  jb short 0xC27F060                            ; -> loc_c27f060
  c27f07f  jmp short 0xC27F014                           ; -> loc_c27f014

loc_c27f081:  ; from c27efd0
  c27f081  mov r13,r8                                    
  c27f084  mov rbx,r15                                   
  c27f087  mov rax,rdi                                   
  c27f08a  jmp short 0xC27F0BA                           ; -> loc_c27f0ba
  c27f08c  nop [rax]                                     

loc_c27f090:  ; from c27f5c9
  c27f090  mov rcx,r15                                   
  c27f093  mov rdx,rdi                                   
  c27f096  mov r8,r13                                    
  c27f099  mov r9,rsi                                    
  c27f09c  call 0xC27EFB0                                ; -> sub_c27efb0
  c27f0a1  mov rax,r12                                   
  c27f0a4  mov r15,rbx                                   
  c27f0a7  mov rdi,r12                                   

loc_c27f0aa:  ; from c27f5e6
  c27f0aa  mov rdx,rax                                   
  c27f0ad  sub rdx,rbx                                   
  c27f0b0  cmp rdx,0x21                                  
  c27f0b4  jl 0xC27EFD9                                  ; -> loc_c27efd9

loc_c27f0ba:  ; from c27f08a
  c27f0ba  mov rcx,rdx                                   
  c27f0bd  shr rcx,1                                     
  c27f0c0  test r13,r13                                  
  c27f0c3  jle 0xC27F5EB                                 ; -> loc_c27f5eb
  c27f0c9  lea rdx,[rbx+rcx]                             
  c27f0cd  lea r8,[rdi-1]                                
  c27f0d1  mov r9,r8                                     
  c27f0d4  sub r9,rbx                                    
  c27f0d7  cmp r9,0x29                                   
  c27f0db  jl 0xC27F310                                  ; -> loc_c27f310
  c27f0e1  mov [rsp+0x20],r13                            
  c27f0e6  inc r9                                        
  c27f0e9  shr r9,3                                      
  c27f0ed  movzx r10d,byte ptr [rbx+r9]                  
  c27f0f2  movzx r14d,byte ptr [rbx]                     
  c27f0f6  mov r11,[rsi]                                 
  c27f0f9  mov r11,[r11]                                 
  c27f0fc  lea r15,[r10+r10*4]                           
  c27f100  lea r13,[r14+r14*4]                           
  c27f104  mov r12,[r11+r15*8+0x20]                      
  c27f109  cmp r12,[r11+r13*8+0x20]                      
  c27f10e  jae short 0xC27F12B                           ; -> loc_c27f12b
  ... (--max 400)
```

## CALLERS
```
  0xc273420 sub_c273420 size 0x8a73
  0xc27eb30 sub_c27eb30 size 0x26
  0xc27ebd0 sub_c27ebd0 size 0x8b
  -- 3 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0xc27ebd0   sub_c27ebd0       set         [open]     [proven]  src=src\client\features\render\native\dragon\sub_c27ebd0.cpp;src\client\features\render\native\dragon\sub_c27ebd0.h
  0xe935700   sub_e935700       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_e935700.cpp;src\client\features\render\native\helpers\sub_e935700.h

## STRINGS AND RIP REFS
  (none)

## FIELD ACCESS TABLE (descscan2, regs rdi,rsi,r9,r15)
  (no [reg+off] description reads detected; register unknown -> [open])

## KNOWN STRUCT LAYOUTS TOUCHED
  (none detected)

## CLOSEST FINISHED LIFT (style example, same size band + call shape)
  566d290.md  size 0xbd  callees~21  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\566d290.md

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

