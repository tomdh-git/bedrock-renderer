# ctxpack build 0xaaa6e0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb

## HEADER
  rva        : 0xaaa6e0
  size       : 0xd7 (215 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 2 (direct), depth 1
  callers    : 6

## EXACT LISTING (0xaaa6e0..0xaaa7b7)
```
sub_aaa6e0  [0xaaa6e0..0xaac6e0)  size 0x2000  8 xrefs in
  aaa6e0  push r14                                      
  aaa6e2  push rsi                                      
  aaa6e3  push rdi                                      
  aaa6e4  push rbx                                      
  aaa6e5  sub rsp,0x48                                  
  aaa6e9  movaps [rsp+0x30],xmm6                        
  aaa6ee  mov rsi,rcx                                   
  aaa6f1  mov rax,[rcx]                                 ; R a0+0x0
  aaa6f4  mov rcx,[rax+8]                               ; R *(a0+0x0)+0x8
  aaa6f8  mov qword ptr [rcx],0                         ; W *(*(a0+0x0)+0x8)+0x0
  aaa6ff  mov rdi,[rax]                                 ; R *(a0+0x0)+0x0
  aaa702  test rdi,rdi                                  
  aaa705  je short 0xAAA782                             ; -> loc_aaa782
  aaa707  xorps xmm6,xmm6                               
  aaa70a  jmp short 0xAAA746                            ; -> loc_aaa746
  aaa70c  nop [rax]                                     ; R *(a0+0x0)+0x0

loc_aaa710:  ; from aaa766, aaa780
  aaa710  lea r14,[rdi+0x178]                           ; R *(*(a0+0x0)+0x0)+0x178
  aaa717  call 0xE935700                                ; -> sub_e935700
  aaa71c  movups [r14],xmm6                             ; W *(*(a0+0x0)+0x0)+0x178+0x0
  aaa720  mov qword ptr [r14+0x10],0                    ; W *(*(a0+0x0)+0x0)+0x178+0x10

loc_aaa728:  ; from aaa753
  aaa728  lea rcx,[rdi+0x18]                            ; R *(*(a0+0x0)+0x0)+0x18
  aaa72c  call 0xA89240                                 ; -> sub_a89240
  aaa731  mov edx,0x190                                 
  aaa736  mov rcx,rdi                                   
  aaa739  call 0xE935700                                ; -> sub_e935700
  aaa73e  mov rdi,rbx                                   
  aaa741  test rbx,rbx                                  
  aaa744  je short 0xAAA782                             ; -> loc_aaa782

loc_aaa746:  ; from aaa70a
  aaa746  mov rbx,[rdi]                                 
  aaa749  mov rcx,[rdi+0x178]                           
  aaa750  test rcx,rcx                                  
  aaa753  je short 0xAAA728                             ; -> loc_aaa728
  aaa755  mov rdx,[rdi+0x188]                           
  aaa75c  sub rdx,rcx                                   
  aaa75f  cmp rdx,0x1000                                
  aaa766  jb short 0xAAA710                             ; -> loc_aaa710
  aaa768  mov rax,[rcx-8]                               
  aaa76c  add rcx,0xFFFFFFFFFFFFFFF8                    
  aaa770  sub rcx,rax                                   
  aaa773  cmp rcx,0x20                                  
  aaa777  jae short 0xAAA79D                            ; -> loc_aaa79d
  aaa779  add rdx,0x27                                  
  aaa77d  mov rcx,rax                                   
  aaa780  jmp short 0xAAA710                            ; -> loc_aaa710

loc_aaa782:  ; from aaa705, aaa744
  aaa782  mov rcx,[rsi]                                 
  aaa785  mov edx,0x190                                 
  aaa78a  movaps xmm6,[rsp+0x30]                        
  aaa78f  add rsp,0x48                                  
  aaa793  pop rbx                                       
  aaa794  pop rdi                                       
  aaa795  pop rsi                                       
  aaa796  pop r14                                       
  aaa798  jmp 0xE935700                                 ; -> sub_e935700

loc_aaa79d:  ; from aaa777
  aaa79d  mov qword ptr [rsp+0x20],0                    
  aaa7a6  xor ecx,ecx                                   
  aaa7a8  xor edx,edx                                   
  aaa7aa  xor r8d,r8d                                   
  aaa7ad  xor r9d,r9d                                   
  aaa7b0  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  aaa7b6  int3                                          
  aaa7b7  int3                                          
  aaa7b8  int3                                          
  aaa7b9  int3                                          
  aaa7ba  int3                                          
  aaa7bb  int3                                          
  aaa7bc  int3                                          
  aaa7bd  int3                                          
  aaa7be  int3                                          
  aaa7bf  int3                                          
  aaa7c0  push rsi                                      
  aaa7c1  push rdi                                      
  aaa7c2  push rbx                                      
  aaa7c3  sub rsp,0x30                                  
  aaa7c7  mov rsi,rcx                                   
  aaa7ca  mov rcx,[rcx+0x479B8]                         
  aaa7d1  test rcx,rcx                                  
  aaa7d4  je short 0xAAA81F                             ; -> loc_aaa81f
  aaa7d6  mov rdx,[rsi+0x479C8]                         
  aaa7dd  sub rdx,rcx                                   
  aaa7e0  cmp rdx,0x1000                                
  aaa7e7  jb short 0xAAA805                             ; -> loc_aaa805
  aaa7e9  mov rax,[rcx-8]                               
  aaa7ed  add rcx,0xFFFFFFFFFFFFFFF8                    
  aaa7f1  sub rcx,rax                                   
  aaa7f4  cmp rcx,0x20                                  
  aaa7f8  jae 0xAAAAB0                                  ; -> loc_aaaab0
  aaa7fe  add rdx,0x27                                  
  aaa802  mov rcx,rax                                   

loc_aaa805:  ; from aaa7e7
  aaa805  lea rdi,[rsi+0x479B8]                         
  aaa80c  call 0xE935700                                ; -> sub_e935700
  aaa811  xorps xmm0,xmm0                               
  aaa814  movups [rdi],xmm0                             
  aaa817  mov qword ptr [rdi+0x10],0                    

loc_aaa81f:  ; from aaa7d4
  aaa81f  lea rcx,[rsi+0x479A8]                         
  aaa826  call 0x3079D0                                 ; -> sub_3079d0
  aaa82b  lea rcx,[rsi+0x47900]                         
  aaa832  call 0xAAAAD0                                 ; -> sub_aaaad0
  aaa837  lea rax,[0xF0A4C60]                           ; [data_f0a4c60]
  aaa83e  mov [rsi+0x42D90],rax                         
  aaa845  mov rcx,[rsi+0x478D0]                         
  aaa84c  test rcx,rcx                                  
  aaa84f  je short 0xAAA89A                             ; -> loc_aaa89a
  aaa851  mov rdx,[rsi+0x478E0]                         
  aaa858  sub rdx,rcx                                   
  aaa85b  cmp rdx,0x1000                                
  aaa862  jb short 0xAAA880                             ; -> loc_aaa880
  aaa864  mov rax,[rcx-8]                               
  aaa868  add rcx,0xFFFFFFFFFFFFFFF8                    
  aaa86c  sub rcx,rax                                   
  aaa86f  cmp rcx,0x20                                  
  aaa873  jae 0xAAAAB0                                  ; -> loc_aaaab0
  aaa879  add rdx,0x27                                  
  aaa87d  mov rcx,rax                                   

loc_aaa880:  ; from aaa862
  aaa880  lea rdi,[rsi+0x478D0]                         
  aaa887  call 0xE935700                                ; -> sub_e935700
  aaa88c  xorps xmm0,xmm0                               
  aaa88f  movups [rdi],xmm0                             
  aaa892  mov qword ptr [rdi+0x10],0                    

loc_aaa89a:  ; from aaa84f
  aaa89a  mov rcx,[rsi+0x42D88]                         
  aaa8a1  test rcx,rcx                                  
  aaa8a4  je short 0xAAA8CB                             ; -> loc_aaa8cb
  aaa8a6  lea rax,[rsi+0x42D50]                         
  aaa8ad  cmp rcx,rax                                   
  aaa8b0  setne dl                                      
  aaa8b3  mov rax,[rcx]                                 
  aaa8b6  mov rax,[rax+0x20]                            
  aaa8ba  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  aaa8c0  mov qword ptr [rsi+0x42D88],0                 

loc_aaa8cb:  ; from aaa8a4
  aaa8cb  mov rcx,[rsi+0x688]                           
  aaa8d2  test rcx,rcx                                  
  aaa8d5  je short 0xAAA920                             ; -> loc_aaa920
  aaa8d7  mov rdx,[rsi+0x698]                           
  aaa8de  sub rdx,rcx                                   
  aaa8e1  cmp rdx,0x1000                                
  aaa8e8  jb short 0xAAA906                             ; -> loc_aaa906
  aaa8ea  mov rax,[rcx-8]                               
  aaa8ee  add rcx,0xFFFFFFFFFFFFFFF8                    
  aaa8f2  sub rcx,rax                                   
  aaa8f5  cmp rcx,0x20                                  
  aaa8f9  jae 0xAAAAB0                                  ; -> loc_aaaab0
  aaa8ff  add rdx,0x27                                  
  aaa903  mov rcx,rax                                   

loc_aaa906:  ; from aaa8e8
  aaa906  lea rdi,[rsi+0x688]                           
  aaa90d  call 0xE935700                                ; -> sub_e935700
  aaa912  xorps xmm0,xmm0                               
  aaa915  movups [rdi],xmm0                             
  aaa918  mov qword ptr [rdi+0x10],0                    

loc_aaa920:  ; from aaa8d5
  aaa920  mov rax,[rsi+0x678]                           
  aaa927  mov rcx,[rax+8]                               
  aaa92b  mov qword ptr [rcx],0                         
  aaa932  mov rdi,[rax]                                 
  aaa935  test rdi,rdi                                  
  aaa938  je short 0xAAA961                             ; -> loc_aaa961
  aaa93a  nop [rax+rax]                                 

loc_aaa940:  ; from aaa95f
  aaa940  mov rbx,[rdi]                                 
  aaa943  lea rcx,[rdi+0x30]                            
  aaa947  call 0x4DEA990                                ; -> sub_4dea990
  aaa94c  mov edx,0x290                                 
  aaa951  mov rcx,rdi                                   
  aaa954  call 0xE935700                                ; -> sub_e935700
  aaa959  mov rdi,rbx                                   
  aaa95c  test rbx,rbx                                  
  aaa95f  jne short 0xAAA940                            ; -> loc_aaa940

loc_aaa961:  ; from aaa938
  aaa961  mov rcx,[rsi+0x678]                           
  aaa968  mov edx,0x290                                 
  aaa96d  call 0xE935700                                ; -> sub_e935700
  aaa972  mov rcx,[rsi+0x648]                           
  aaa979  test rcx,rcx                                  
  aaa97c  je short 0xAAA9C7                             ; -> loc_aaa9c7
  aaa97e  mov rdx,[rsi+0x658]                           
  aaa985  sub rdx,rcx                                   
  aaa988  cmp rdx,0x1000                                
  aaa98f  jb short 0xAAA9AD                             ; -> loc_aaa9ad
  aaa991  mov rax,[rcx-8]                               
  aaa995  add rcx,0xFFFFFFFFFFFFFFF8                    
  aaa999  sub rcx,rax                                   
  aaa99c  cmp rcx,0x20                                  
  aaa9a0  jae 0xAAAAB0                                  ; -> loc_aaaab0
  aaa9a6  add rdx,0x27                                  
  aaa9aa  mov rcx,rax                                   

loc_aaa9ad:  ; from aaa98f
  aaa9ad  lea rdi,[rsi+0x648]                           
  aaa9b4  call 0xE935700                                ; -> sub_e935700
  aaa9b9  xorps xmm0,xmm0                               
  aaa9bc  movups [rdi],xmm0                             
  aaa9bf  mov qword ptr [rdi+0x10],0                    

loc_aaa9c7:  ; from aaa97c
  aaa9c7  mov rax,[rsi+0x638]                           
  aaa9ce  mov rcx,[rax+8]                               
  aaa9d2  mov qword ptr [rcx],0                         
  aaa9d9  mov rdi,[rax]                                 
  aaa9dc  test rdi,rdi                                  
  aaa9df  je short 0xAAAA11                             ; -> loc_aaaa11
  aaa9e1  nop [rax+rax]                                 

loc_aaa9f0:  ; from aaaa0f
  aaa9f0  mov rbx,[rdi]                                 
  aaa9f3  lea rcx,[rdi+0x18]                            
  aaa9f7  call 0x4DEA990                                ; -> sub_4dea990
  aaa9fc  mov edx,0x278                                 
  aaaa01  mov rcx,rdi                                   
  aaaa04  call 0xE935700                                ; -> sub_e935700
  aaaa09  mov rdi,rbx                                   
  aaaa0c  test rbx,rbx                                  
  aaaa0f  jne short 0xAAA9F0                            ; -> loc_aaa9f0

loc_aaaa11:  ; from aaa9df
  aaaa11  mov rcx,[rsi+0x638]                           
  aaaa18  mov edx,0x278                                 
  aaaa1d  call 0xE935700                                ; -> sub_e935700
  aaaa22  mov rdi,[rsi+0x5F0]                           
  aaaa29  test rdi,rdi                                  
  aaaa2c  je short 0xAAAA59                             ; -> loc_aaaa59
  aaaa2e  lock dec dword ptr [rdi+8]                    
  aaaa32  jne short 0xAAAA59                            ; -> loc_aaaa59
  aaaa34  mov rax,[rdi]                                 
  aaaa37  mov rax,[rax]                                 
  aaaa3a  mov rcx,rdi                                   
  aaaa3d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  aaaa43  lock dec dword ptr [rdi+0xC]                  
  aaaa47  jne short 0xAAAA59                            ; -> loc_aaaa59
  aaaa49  mov rax,[rdi]                                 
  aaaa4c  mov rax,[rax+8]                               
  aaaa50  mov rcx,rdi                                   
  aaaa53  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_aaaa59:  ; from aaaa2c, aaaa32, aaaa47
  aaaa59  mov rax,[rsi+0x58]                            
  aaaa5d  cmp rax,0x10                                  
  aaaa61  jb short 0xAAAA94                             ; -> loc_aaaa94
  aaaa63  mov rcx,[rsi+0x40]                            
  aaaa67  lea rdx,[rax+1]                               
  aaaa6b  cmp rdx,0x1000                                
  aaaa72  jb short 0xAAAA8F                             ; -> loc_aaaa8f
  aaaa74  mov r8,[rcx-8]                                
  aaaa78  add rcx,0xFFFFFFFFFFFFFFF8                    
  aaaa7c  sub rcx,r8                                    
  aaaa7f  cmp rcx,0x20                                  
  aaaa83  jae short 0xAAAAB0                            ; -> loc_aaaab0
  aaaa85  add rax,0x28                                  
  aaaa89  mov rdx,rax                                   
  aaaa8c  mov rcx,r8                                    

loc_aaaa8f:  ; from aaaa72
  aaaa8f  call 0xE935700                                ; -> sub_e935700

loc_aaaa94:  ; from aaaa61
  aaaa94  mov qword ptr [rsi+0x50],0                    
  aaaa9c  mov qword ptr [rsi+0x58],0xF                  
  aaaaa4  mov byte ptr [rsi+0x40],0                     
  aaaaa8  add rsp,0x30                                  
  aaaaac  pop rbx                                       
  aaaaad  pop rdi                                       
  aaaaae  pop rsi                                       
  aaaaaf  ret                                           

loc_aaaab0:  ; from aaa7f8, aaa873, aaa8f9, aaa9a0, aaaa83
  aaaab0  mov qword ptr [rsp+0x20],0                    
  aaaab9  xor ecx,ecx                                   
  aaaabb  xor edx,edx                                   
  aaaabd  xor r8d,r8d                                   
  aaaac0  xor r9d,r9d                                   
  aaaac3  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  aaaac9  int3                                          
  aaaaca  int3                                          
  aaaacb  int3                                          
  aaaacc  int3                                          
  aaaacd  int3                                          
  aaaace  int3                                          
  aaaacf  int3                                          
  aaaad0  push rsi                                      
  aaaad1  push rdi                                      
  aaaad2  sub rsp,0x28                                  
  aaaad6  mov rsi,rcx                                   
  aaaad9  mov rcx,[rcx+0x58]                            
  aaaadd  test rcx,rcx                                  
  aaaae0  je short 0xAAAB25                             ; -> loc_aaab25
  aaaae2  mov rdx,[rsi+0x68]                            
  aaaae6  sub rdx,rcx                                   
  aaaae9  cmp rdx,0x1000                                
  aaaaf0  jb short 0xAAAB0E                             ; -> loc_aaab0e
  aaaaf2  mov rax,[rcx-8]                               
  aaaaf6  add rcx,0xFFFFFFFFFFFFFFF8                    
  aaaafa  sub rcx,rax                                   
  aaaafd  cmp rcx,0x20                                  
  aaab01  jae 0xAAABF9                                  ; -> loc_aaabf9
  aaab07  add rdx,0x27                                  
  aaab0b  mov rcx,rax                                   

loc_aaab0e:  ; from aaaaf0
  aaab0e  lea rdi,[rsi+0x58]                            
  aaab12  call 0xE935700                                ; -> sub_e935700
  aaab17  xorps xmm0,xmm0                               
  aaab1a  movups [rdi],xmm0                             
  aaab1d  mov qword ptr [rdi+0x10],0                    

loc_aaab25:  ; from aaaae0
  aaab25  mov rax,[rsi+0x48]                            
  aaab29  mov rcx,[rax+8]                               
  aaab2d  mov qword ptr [rcx],0                         
  aaab34  mov rcx,[rax]                                 
  aaab37  test rcx,rcx                                  
  aaab3a  je short 0xAAAB55                             ; -> loc_aaab55
  aaab3c  nop [rax]                                     

loc_aaab40:  ; from aaab53
  aaab40  mov rdi,[rcx]                                 
  aaab43  mov edx,0x28                                  
  aaab48  call 0xE935700                                ; -> sub_e935700
  aaab4d  mov rcx,rdi                                   
  aaab50  test rdi,rdi                                  
  aaab53  jne short 0xAAAB40                            ; -> loc_aaab40

loc_aaab55:  ; from aaab3a
  aaab55  mov rcx,[rsi+0x48]                            
  aaab59  mov edx,0x28                                  
  aaab5e  call 0xE935700                                ; -> sub_e935700
  aaab63  mov rcx,[rsi+0x18]                            
  aaab67  test rcx,rcx                                  
  aaab6a  je short 0xAAABAB                             ; -> loc_aaabab
  aaab6c  mov rdx,[rsi+0x28]                            
  aaab70  sub rdx,rcx                                   
  aaab73  cmp rdx,0x1000                                
  aaab7a  jb short 0xAAAB94                             ; -> loc_aaab94
  aaab7c  mov rax,[rcx-8]                               
  aaab80  add rcx,0xFFFFFFFFFFFFFFF8                    
  aaab84  sub rcx,rax                                   
  aaab87  cmp rcx,0x20                                  
  aaab8b  jae short 0xAAABF9                            ; -> loc_aaabf9
  aaab8d  add rdx,0x27                                  
  aaab91  mov rcx,rax                                   

loc_aaab94:  ; from aaab7a
  aaab94  lea rdi,[rsi+0x18]                            
  aaab98  call 0xE935700                                ; -> sub_e935700
  aaab9d  xorps xmm0,xmm0                               
  aaaba0  movups [rdi],xmm0                             
  aaaba3  mov qword ptr [rdi+0x10],0                    

loc_aaabab:  ; from aaab6a
  aaabab  mov rax,[rsi+8]                               
  aaabaf  mov rcx,[rax+8]                               
  aaabb3  mov qword ptr [rcx],0                         
  aaabba  mov rcx,[rax]                                 
  aaabbd  test rcx,rcx                                  
  aaabc0  je short 0xAAABE5                             ; -> loc_aaabe5
  aaabc2  nop [rax+rax]                                 

loc_aaabd0:  ; from aaabe3
  aaabd0  mov rdi,[rcx]                                 
  aaabd3  mov edx,0x38                                  
  aaabd8  call 0xE935700                                ; -> sub_e935700
  aaabdd  mov rcx,rdi                                   
  aaabe0  test rdi,rdi                                  
  aaabe3  jne short 0xAAABD0                            ; -> loc_aaabd0

loc_aaabe5:  ; from aaabc0
  aaabe5  mov rcx,[rsi+8]                               
  aaabe9  mov edx,0x38                                  
  aaabee  add rsp,0x28                                  
  aaabf2  pop rdi                                       
  aaabf3  pop rsi                                       
  aaabf4  jmp 0xE935700                                 ; -> sub_e935700

loc_aaabf9:  ; from aaab01, aaab8b
  aaabf9  mov qword ptr [rsp+0x20],0                    
  aaac02  xor ecx,ecx                                   
  aaac04  xor edx,edx                                   
  aaac06  xor r8d,r8d                                   
  aaac09  xor r9d,r9d                                   
  aaac0c  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  aaac12  int3                                          
  aaac13  int3                                          
  aaac14  int3                                          
  aaac15  int3                                          
  aaac16  int3                                          
  aaac17  int3                                          
  aaac18  int3                                          
  aaac19  int3                                          
  aaac1a  int3                                          
  aaac1b  int3                                          
  aaac1c  int3                                          
  aaac1d  int3                                          
  aaac1e  int3                                          
  aaac1f  int3                                          
  aaac20  push rsi                                      
  aaac21  push rdi                                      
  aaac22  push rbx                                      
  aaac23  sub rsp,0x30                                  
  aaac27  mov edi,edx                                   
  aaac29  mov rsi,rcx                                   
  aaac2c  lea rax,[0xF0A4C60]                           ; [data_f0a4c60]
  aaac33  mov [rcx],rax                                 
  aaac36  mov rcx,[rcx+0x4B40]                          
  aaac3d  test rcx,rcx                                  
  aaac40  je short 0xAAAC87                             ; -> loc_aaac87
  aaac42  mov rdx,[rsi+0x4B50]                          
  aaac49  sub rdx,rcx                                   
  aaac4c  cmp rdx,0x1000                                
  aaac53  jb short 0xAAAC6D                             ; -> loc_aaac6d
  aaac55  mov rax,[rcx-8]                               
  aaac59  add rcx,0xFFFFFFFFFFFFFFF8                    
  aaac5d  sub rcx,rax                                   
  aaac60  cmp rcx,0x20                                  
  aaac64  jae short 0xAAACA5                            ; -> loc_aaaca5
  aaac66  add rdx,0x27                                  
  aaac6a  mov rcx,rax                                   

loc_aaac6d:  ; from aaac53
  aaac6d  lea rbx,[rsi+0x4B40]                          
  aaac74  call 0xE935700                                ; -> sub_e935700
  aaac79  xorps xmm0,xmm0                               
  aaac7c  movups [rbx],xmm0                             
  aaac7f  mov qword ptr [rbx+0x10],0                    

loc_aaac87:  ; from aaac40
  aaac87  test dil,1                                    
  aaac8b  je short 0xAAAC9A                             ; -> loc_aaac9a
  aaac8d  mov edx,0x4B58                                
  aaac92  mov rcx,rsi                                   
  aaac95  call 0xE935700                                ; -> sub_e935700

loc_aaac9a:  ; from aaac8b
  aaac9a  mov rax,rsi                                   
  aaac9d  add rsp,0x30                                  
  aaaca1  pop rbx                                       
  aaaca2  pop rdi                                       
  aaaca3  pop rsi                                       
  aaaca4  ret                                           

loc_aaaca5:  ; from aaac64
  aaaca5  mov qword ptr [rsp+0x20],0                    
  aaacae  xor ecx,ecx                                   
  aaacb0  xor edx,edx                                   
  aaacb2  xor r8d,r8d                                   
  aaacb5  xor r9d,r9d                                   
  aaacb8  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  aaacbe  int3                                          
  aaacbf  int3                                          
  aaacc0  push rsi                                      
  ... (--max 400)
```

## CALLERS
```
  0xa8cee0 sub_a8cee0 size 0x2bd
  0x539b7c0 sub_539b7c0 size 0x1c00
  0x539e420 sub_539e420 size 0x17ef
  0x53d4160 sub_53d4160 size 0x36
  0x6adf430 sub_6adf430 size 0x899
  0x6e78d90 sub_6e78d90 size 0x10cc
  -- 6 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0xa89240    sub_a89240        unknown     [open]     [proven]  unresolved
  0xe935700   sub_e935700       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_e935700.cpp;src\client\features\render\native\helpers\sub_e935700.h

## STRINGS AND RIP REFS
  (none)

## FIELD ACCESS TABLE (descscan2, regs rdi,rsi,r9,r15)
  (no [reg+off] description reads detected; register unknown -> [open])

## KNOWN STRUCT LAYOUTS TOUCHED
  (none detected)

## CLOSEST FINISHED LIFT (style example, same size band + call shape)
  56b67f0.md  size 0xc8  callees~22  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\56b67f0.md

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

