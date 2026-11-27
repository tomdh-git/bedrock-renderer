# ctxpack build 0x5aba5c0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=5aba5c0.md:165303e8d5bad7409f8132d908cec458b792e038550c1bc8280429d9022d81e9,data=native_functions.tsv:07ea6058496f3c9340e582f2f9bc57b61494694303373d3389ba71c5842a53a6,data=native_deps.tsv:118356f1f1ba724d2eb40c7fc481ea24319c1aeba9f482039b865d6efece1f8b,data=native_boundary.tsv:058a56d8016eceaff394a955dc2a241d4a8a7d44663fc4cd9102ea82d9ec7315,data=native_boundary_candidates.tsv:b2db6e93be378325c9c8b370ea57463e6e4d762ef5f0a1cae81562abc4635b8c,data=ctx_facts.tsv:d2352cf1ceb26c34830b966be082a5e21a28f989c09fa2d4ecdfb97458b56aab,data=ctx_deadends.md:298967a276b4b7e4454961297c117289bf5ed3fcdf45c3240615fc10ed423c83

## HEADER
  rva        : 0x5aba5c0
  size       : 0x10f (271 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 7 (direct), depth 1
  callers    : 95

## EXACT LISTING (0x5aba5c0..0x5aba6cf)
```
sub_5aba5c0  [0x5aba5c0..0x5abc5c0)  size 0x2000  200 xrefs in
  5aba5c0  push r14                                      
  5aba5c2  push rsi                                      
  5aba5c3  push rdi                                      
  5aba5c4  push rbx                                      
  5aba5c5  sub rsp,0x28                                  
  5aba5c9  mov rsi,rcx                                   
  5aba5cc  lea rbx,[rcx+0xA0]                            ; R a0+0xA0
  5aba5d3  mov rcx,rbx                                   
  5aba5d6  call 0x9BD4A0                                 ; -> sub_9bd4a0
  5aba5db  test rax,rax                                  
  5aba5de  je short 0x5ABA5E9                            ; -> loc_5aba5e9
  5aba5e0  add rax,0x10                                  
  5aba5e4  jmp 0x5ABA68C                                 ; -> loc_5aba68c

loc_5aba5e9:  ; from 5aba5de
  5aba5e9  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  5aba5f0  mov rax,[rcx]                                 
  5aba5f3  mov rax,[rax+8]                               
  5aba5f7  mov edx,0x8C8                                 
  5aba5fc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  5aba602  mov rdi,rax                                   
  5aba605  test rax,rax                                  
  5aba608  je 0x5ABA696                                  ; -> loc_5aba696

loc_5aba60e:  ; from 5aba6a6
  5aba60e  mov [rdi],rdi                                 
  5aba611  mov [rdi+8],rdi                               
  5aba615  add rax,0x10                                  
  5aba619  mov qword ptr [rdi+0x10],0                    
  5aba621  mov [rsp+0x20],rax                            
  5aba626  mov rcx,[rsi+0x38]                            
  5aba62a  test rcx,rcx                                  
  5aba62d  je short 0x5ABA6AB                            ; -> loc_5aba6ab
  5aba62f  mov r14,rax                                   
  5aba632  mov rax,[rcx]                                 
  5aba635  mov rax,[rax+0x10]                            
  5aba639  lea rdx,[rsp+0x20]                            
  5aba63e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  5aba644  mov rcx,rbx                                   
  5aba647  mov rdx,rdi                                   
  5aba64a  call 0x9BD6D0                                 ; -> sub_9bd6d0
  5aba64f  lea rbx,[rsi+0x50]                            
  5aba653  mov rcx,rbx                                   
  5aba656  call 0xEEC59F0                                ; -> sub_eec59f0
  5aba65b  test eax,eax                                  
  5aba65d  jne short 0x5ABA6B0                           ; -> loc_5aba6b0
  5aba65f  cmp dword ptr [rsi+0x9C],0x7FFFFFFF           
  5aba669  je short 0x5ABA6BA                            ; -> loc_5aba6ba
  5aba66b  lea rax,[rsi+0x40]                            
  5aba66f  mov rcx,[rsi+0x48]                            
  5aba673  mov [rdi+8],rcx                               
  5aba677  mov [rdi],rax                                 
  5aba67a  mov [rcx],rdi                                 
  5aba67d  mov [rsi+0x48],rdi                            
  5aba681  mov rcx,rbx                                   
  5aba684  call 0xEEC5A10                                ; -> sub_eec5a10
  5aba689  mov rax,r14                                   

loc_5aba68c:  ; from 5aba5e4
  5aba68c  add rsp,0x28                                  
  5aba690  pop rbx                                       
  5aba691  pop rdi                                       
  5aba692  pop rsi                                       
  5aba693  pop r14                                       
  5aba695  ret                                           

loc_5aba696:  ; from 5aba608
  5aba696  mov ecx,0x8C8                                 
  5aba69b  mov r14,rax                                   
  5aba69e  call 0x9BC830                                 ; -> sub_9bc830
  5aba6a3  mov rax,r14                                   
  5aba6a6  jmp 0x5ABA60E                                 ; -> loc_5aba60e

loc_5aba6ab:  ; from 5aba62d
  5aba6ab  call 0xEEC59E0                                ; -> sub_eec59e0

loc_5aba6b0:  ; from 5aba65d
  5aba6b0  mov ecx,5                                     
  5aba6b5  call 0xEEC5A00                                ; -> sub_eec5a00

loc_5aba6ba:  ; from 5aba669
  5aba6ba  mov dword ptr [rsi+0x9C],0x7FFFFFFE           
  5aba6c4  mov ecx,6                                     
  5aba6c9  call 0xEEC5A00                                ; -> sub_eec5a00
  5aba6ce  int3                                          
  5aba6cf  int3                                          
  5aba6d0  push r15                                      
  5aba6d2  push r14                                      
  5aba6d4  push r13                                      
  5aba6d6  push r12                                      
  5aba6d8  push rsi                                      
  5aba6d9  push rdi                                      
  5aba6da  push rbp                                      
  5aba6db  push rbx                                      
  5aba6dc  sub rsp,0x28                                  
  5aba6e0  mov rsi,rcx                                   
  5aba6e3  mov rbp,[rcx]                                 
  5aba6e6  mov r13,[rcx+8]                               
  5aba6ea  sub r13,rbp                                   
  5aba6ed  sar r13,3                                     
  5aba6f1  mov rax,0x8F5C28F5C28F5C29                    
  5aba6fb  imul r13,rax                                  
  5aba6ff  inc r13                                       
  5aba702  mov r9,[rcx+0x10]                             
  5aba706  sub r9,rbp                                    
  5aba709  sar r9,3                                      
  5aba70d  imul r9,rax                                   
  5aba711  mov rax,r9                                    
  5aba714  shr rax,1                                     
  5aba717  mov rcx,0x147AE147AE147AE                     
  5aba721  mov r10,rcx                                   
  5aba724  sub r10,rax                                   
  5aba727  add rax,r9                                    
  5aba72a  cmp rax,r13                                   
  5aba72d  cmovbe rax,r13                                
  5aba731  cmp r9,r10                                    
  5aba734  cmova rax,rcx                                 
  5aba738  mov rbx,rdx                                   
  5aba73b  mov rdx,0x147AE147AE147AF                     
  5aba745  cmp rax,rdx                                   
  5aba748  jae 0x5ABA897                                 ; -> loc_5aba897
  5aba74e  mov r12,r8                                    
  5aba751  imul rdi,rax,0xC8                             
  5aba758  test rax,rax                                  
  5aba75b  je short 0x5ABA7C8                            ; -> loc_5aba7c8
  5aba75d  cmp rax,0x15                                  
  5aba761  jb short 0x5ABA7A1                            ; -> loc_5aba7a1
  5aba763  cmp rax,rcx                                   
  5aba766  je 0x5ABA897                                  ; -> loc_5aba897
  5aba76c  lea r14,[rdi+0x27]                            
  5aba770  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  5aba777  mov rax,[rcx]                                 
  5aba77a  mov rax,[rax+8]                               
  5aba77e  mov rdx,r14                                   
  5aba781  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  5aba787  test rax,rax                                  
  5aba78a  je 0x5ABA884                                  ; -> loc_5aba884

loc_5aba790:  ; from 5aba892
  5aba790  mov r14,rax                                   
  5aba793  add r14,0x27                                  
  5aba797  and r14,0xFFFFFFFFFFFFFFE0                    
  5aba79b  mov [r14-8],rax                               
  5aba79f  jmp short 0x5ABA7CB                           ; -> loc_5aba7cb

loc_5aba7a1:  ; from 5aba761
  5aba7a1  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  5aba7a8  mov rax,[rcx]                                 
  5aba7ab  mov rax,[rax+8]                               
  5aba7af  mov rdx,rdi                                   
  5aba7b2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  5aba7b8  mov r14,rax                                   
  5aba7bb  test rax,rax                                  
  5aba7be  jne short 0x5ABA7CB                           ; -> loc_5aba7cb
  5aba7c0  mov rcx,rdi                                   
  5aba7c3  call 0x9BC830                                 ; -> sub_9bc830

loc_5aba7c8:  ; from 5aba75b
  5aba7c8  xor r14d,r14d                                 

loc_5aba7cb:  ; from 5aba79f, 5aba7be
  5aba7cb  mov r15,rbx                                   
  5aba7ce  sub r15,rbp                                   
  5aba7d1  add r15,r14                                   
  5aba7d4  mov r8d,0xC8                                  
  5aba7da  mov rcx,r15                                   
  5aba7dd  mov rdx,r12                                   
  5aba7e0  call 0xEEC6EC0                                ; -> sub_eec6ec0
  5aba7e5  cmp rbx,[rsi+8]                               
  5aba7e9  je short 0x5ABA812                            ; -> loc_5aba812
  5aba7eb  lea r12,[r15+0xC8]                            
  5aba7f2  mov rdx,[rsi]                                 
  5aba7f5  mov r8,rbx                                    
  5aba7f8  sub r8,rdx                                    
  5aba7fb  mov rcx,r14                                   
  5aba7fe  call 0xEEC6DE0                                ; -> sub_eec6de0
  5aba803  mov r8,[rsi+8]                                
  5aba807  sub r8,rbx                                    
  5aba80a  mov rcx,r12                                   
  5aba80d  mov rdx,rbx                                   
  5aba810  jmp short 0x5ABA81E                           ; -> loc_5aba81e

loc_5aba812:  ; from 5aba7e9
  5aba812  mov rdx,[rsi]                                 
  5aba815  sub rbx,rdx                                   
  5aba818  mov rcx,r14                                   
  5aba81b  mov r8,rbx                                    

loc_5aba81e:  ; from 5aba810
  5aba81e  call 0xEEC6DE0                                ; -> sub_eec6de0
  5aba823  mov rcx,[rsi]                                 
  5aba826  test rcx,rcx                                  
  5aba829  je short 0x5ABA858                            ; -> loc_5aba858
  5aba82b  mov rdx,[rsi+0x10]                            
  5aba82f  sub rdx,rcx                                   
  5aba832  cmp rdx,0x1000                                
  5aba839  jb short 0x5ABA853                            ; -> loc_5aba853
  5aba83b  mov rax,[rcx-8]                               
  5aba83f  add rcx,0xFFFFFFFFFFFFFFF8                    
  5aba843  sub rcx,rax                                   
  5aba846  cmp rcx,0x20                                  
  5aba84a  jae short 0x5ABA89C                           ; -> loc_5aba89c
  5aba84c  add rdx,0x27                                  
  5aba850  mov rcx,rax                                   

loc_5aba853:  ; from 5aba839
  5aba853  call 0xE935700                                ; -> sub_e935700

loc_5aba858:  ; from 5aba829
  5aba858  mov [rsi],r14                                 
  5aba85b  imul rax,r13,0xC8                             
  5aba862  add rax,r14                                   
  5aba865  mov [rsi+8],rax                               
  5aba869  add rdi,r14                                   
  5aba86c  mov [rsi+0x10],rdi                            
  5aba870  mov rax,r15                                   
  5aba873  add rsp,0x28                                  
  5aba877  pop rbx                                       
  5aba878  pop rbp                                       
  5aba879  pop rdi                                       
  5aba87a  pop rsi                                       
  5aba87b  pop r12                                       
  5aba87d  pop r13                                       
  5aba87f  pop r14                                       
  5aba881  pop r15                                       
  5aba883  ret                                           

loc_5aba884:  ; from 5aba78a
  5aba884  mov rcx,r14                                   
  5aba887  mov r14,rax                                   
  5aba88a  call 0x9BC830                                 ; -> sub_9bc830
  5aba88f  mov rax,r14                                   
  5aba892  jmp 0x5ABA790                                 ; -> loc_5aba790

loc_5aba897:  ; from 5aba748, 5aba766
  5aba897  call 0x75740                                  ; -> sub_75740

loc_5aba89c:  ; from 5aba84a
  5aba89c  mov qword ptr [rsp+0x20],0                    
  5aba8a5  xor ecx,ecx                                   
  5aba8a7  xor edx,edx                                   
  5aba8a9  xor r8d,r8d                                   
  5aba8ac  xor r9d,r9d                                   
  5aba8af  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  5aba8b5  int3                                          
  5aba8b6  int3                                          
  5aba8b7  int3                                          
  5aba8b8  int3                                          
  5aba8b9  int3                                          
  5aba8ba  int3                                          
  5aba8bb  int3                                          
  5aba8bc  int3                                          
  5aba8bd  int3                                          
  5aba8be  int3                                          
  5aba8bf  int3                                          
  5aba8c0  add rcx,0x10                                  
  5aba8c4  jmp 0x6C0B2B0                                 ; -> sub_6c0b2b0
  5aba8c9  int3                                          
  5aba8ca  int3                                          
  5aba8cb  int3                                          
  5aba8cc  int3                                          
  5aba8cd  int3                                          
  5aba8ce  int3                                          
  5aba8cf  int3                                          
  5aba8d0  push rbp                                      
  5aba8d1  push r14                                      
  5aba8d3  push rsi                                      
  5aba8d4  push rdi                                      
  5aba8d5  push rbx                                      
  5aba8d6  sub rsp,0x40                                  
  5aba8da  lea rbp,[rsp+0x40]                            
  5aba8df  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE      
  5aba8e7  mov rsi,rcx                                   
  5aba8ea  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  5aba8f1  mov rax,[rcx]                                 
  5aba8f4  mov rax,[rax+8]                               
  5aba8f8  mov edx,0x90                                  
  5aba8fd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  5aba903  mov r14,rax                                   
  5aba906  mov rdi,rax                                   
  5aba909  test rax,rax                                  
  5aba90c  je 0x5ABAAC6                                  ; -> loc_5abaac6

loc_5aba912:  ; from 5abaad0
  5aba912  lea rax,[0xF275B00]                           ; [data_f275b00]
  5aba919  mov [rdi],rax                                 
  5aba91c  xorps xmm0,xmm0                               
  5aba91f  movups [rdi+8],xmm0                           
  5aba923  mov rax,[rsi+0x10]                            
  5aba927  test rax,rax                                  
  5aba92a  je short 0x5ABA936                            ; -> loc_5aba936
  5aba92c  lock inc dword ptr [rax+8]                    
  5aba930  mov rax,[rsi+0x10]                            
  5aba934  jmp short 0x5ABA938                           ; -> loc_5aba938

loc_5aba936:  ; from 5aba92a
  5aba936  xor eax,eax                                   

loc_5aba938:  ; from 5aba934
  5aba938  mov rcx,[rsi+8]                               
  5aba93c  mov [rdi+8],rcx                               
  5aba940  mov [rdi+0x10],rax                            
  5aba944  mov byte ptr [rdi+0x30],0xFF                  
  5aba948  movzx ebx,byte ptr [rsi+0x30]                 
  5aba94c  cmp rbx,3                                     
  5aba950  ja 0x5ABAA36                                  ; -> loc_5abaa36
  5aba956  lea rax,[0xF275E48]                           ; [data_f275e48]
  5aba95d  movsxd rcx,[rax+rbx*4]                        
  5aba961  add rcx,rax                                   
  5aba964  jmp rcx                                       
  5aba966  mov rax,[rsi+0x18]                            
  5aba96a  mov [rdi+0x18],rax                            
  5aba96e  add r14,0x20                                  
  5aba972  movups [rdi+0x20],xmm0                        
  5aba976  mov rax,[rsi+0x28]                            
  5aba97a  test rax,rax                                  
  5aba97d  je short 0x5ABA983                            ; -> loc_5aba983
  5aba97f  lock inc dword ptr [rax+8]                    

loc_5aba983:  ; from 5aba97d
  5aba983  lea rax,[rsi+0x28]                            
  5aba987  mov rcx,[rsi+0x20]                            
  5aba98b  mov [r14],rcx                                 
  5aba98e  mov rax,[rax]                                 
  5aba991  mov [rdi+0x28],rax                            
  5aba995  jmp 0x5ABAA33                                 ; -> loc_5abaa33
  5aba99a  mov [rbp-0x18],rdi                            
  5aba99e  lea rax,[r14+8]                               
  5aba9a2  mov [rbp-0x20],rax                            
  5aba9a6  add r14,0x18                                  
  5aba9aa  mov [rbp-0x10],r14                            
  5aba9ae  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  5aba9b5  mov rax,[rcx]                                 
  5aba9b8  mov rax,[rax+8]                               
  5aba9bc  mov edx,0x20                                  
  5aba9c1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  5aba9c7  nop                                           
  5aba9c8  mov rdi,rax                                   
  5aba9cb  test rax,rax                                  
  5aba9ce  je 0x5ABAAD5                                  ; -> loc_5abaad5

loc_5aba9d4:  ; from 5abaae0
  5aba9d4  xorps xmm0,xmm0                               
  5aba9d7  movups [rdi+0x10],xmm0                        
  5aba9db  movups [rdi],xmm0                             
  5aba9de  mov rax,[rbp-0x10]                            
  5aba9e2  mov [rax],rdi                                 
  5aba9e5  mov r14,[rsi+0x18]                            
  5aba9e9  mov rax,[r14+8]                               
  5aba9ed  test rax,rax                                  
  5aba9f0  je short 0x5ABAA1E                            ; -> loc_5abaa1e
  5aba9f2  mov rdx,[r14]                                 
  5aba9f5  lock inc dword ptr [rax+0xC]                  
  5aba9f9  mov rcx,[rdi+8]                               
  5aba9fd  mov [rdi],rdx                                 
  5abaa00  mov [rdi+8],rax                               
  5abaa04  test rcx,rcx                                  
  5abaa07  je short 0x5ABAA26                            ; -> loc_5abaa26
  5abaa09  lock dec dword ptr [rcx+0xC]                  
  5abaa0d  jne short 0x5ABAA26                           ; -> loc_5abaa26
  5abaa0f  mov rax,[rcx]                                 
  5abaa12  mov rax,[rax+8]                               
  5abaa16  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  5abaa1c  jmp short 0x5ABAA26                           ; -> loc_5abaa26

loc_5abaa1e:  ; from 5aba9f0
  5abaa1e  mov qword ptr [rdi+8],0                       

loc_5abaa26:  ; from 5abaa07, 5abaa0d, 5abaa1c
  5abaa26  movups xmm0,[r14+0x10]                        
  5abaa2b  movups [rdi+0x10],xmm0                        
  5abaa2f  mov rdi,[rbp-0x18]                            

loc_5abaa33:  ; from 5aba995
  5abaa33  mov [rdi+0x30],bl                             

loc_5abaa36:  ; from 5aba950
  5abaa36  xorps xmm0,xmm0                               
  5abaa39  movups [rdi+0x38],xmm0                        
  5abaa3d  mov rax,[rsi+0x40]                            
  5abaa41  test rax,rax                                  
  5abaa44  je short 0x5ABAA50                            ; -> loc_5abaa50
  5abaa46  lock inc dword ptr [rax+8]                    
  5abaa4a  mov rax,[rsi+0x40]                            
  5abaa4e  jmp short 0x5ABAA52                           ; -> loc_5abaa52

loc_5abaa50:  ; from 5abaa44
  5abaa50  xor eax,eax                                   

loc_5abaa52:  ; from 5abaa4e
  5abaa52  mov rcx,[rsi+0x38]                            
  5abaa56  mov [rdi+0x38],rcx                            
  5abaa5a  mov [rdi+0x40],rax                            
  5abaa5e  movss xmm0,[rsi+0x48]                         
  5abaa63  movss [rdi+0x48],xmm0                         
  5abaa68  movss xmm0,[rsi+0x4C]                         
  5abaa6d  movss [rdi+0x4C],xmm0                         
  5abaa72  movss xmm0,[rsi+0x50]                         
  5abaa77  movss [rdi+0x50],xmm0                         
  5abaa7c  movss xmm0,[rsi+0x54]                         
  5abaa81  movss [rdi+0x54],xmm0                         
  5abaa86  movss xmm0,[rsi+0x58]                         
  5abaa8b  movss [rdi+0x58],xmm0                         
  5abaa90  movss xmm0,[rsi+0x5C]                         
  5abaa95  movss [rdi+0x5C],xmm0                         
  5abaa9a  movups xmm0,[rsi+0x60]                        
  5abaa9e  movups xmm1,[rsi+0x6C]                        
  5abaaa2  movups [rdi+0x60],xmm0                        
  5abaaa6  movups [rdi+0x6C],xmm1                        
  5abaaaa  movups xmm0,[rsi+0x80]                        
  5abaab1  movups [rdi+0x80],xmm0                        
  5abaab8  mov rax,rdi                                   
  5abaabb  add rsp,0x40                                  
  5abaabf  pop rbx                                       
  5abaac0  pop rdi                                       
  5abaac1  pop rsi                                       
  5abaac2  pop r14                                       
  5abaac4  pop rbp                                       
  5abaac5  ret                                           

loc_5abaac6:  ; from 5aba90c
  5abaac6  mov ecx,0x90                                  
  5abaacb  call 0x9BC830                                 ; -> sub_9bc830
  5abaad0  jmp 0x5ABA912                                 ; -> loc_5aba912

loc_5abaad5:  ; from 5aba9ce
  5abaad5  mov ecx,0x20                                  
  5abaada  call 0x9BC830                                 ; -> sub_9bc830
  5abaadf  nop                                           
  5abaae0  jmp 0x5ABA9D4                                 ; -> loc_5aba9d4
  5abaae5  nop [rax+rax]                                 ; R ret@9bc830+0x0+idx
  5abaaf0  mov [rsp+0x10],rdx                            
  5abaaf5  push rbp                                      
  5abaaf6  push r14                                      
  5abaaf8  push rsi                                      
  5abaaf9  push rdi                                      
  5abaafa  push rbx                                      
  5abaafb  sub rsp,0x20                                  
  5abaaff  lea rbp,[rdx+0x40]                            
  5abab03  mov rcx,[rbp-0x10]                            
  5abab07  call 0x6A04B0                                 ; -> sub_6a04b0
  5abab0c  mov rcx,[rbp-0x20]                            
  5abab10  call 0x7E6D0                                  ; -> sub_7e6d0
  5abab15  mov edx,0x90                                  
  5abab1a  mov rcx,[rbp-0x18]                            
  5abab1e  call 0xE935700                                ; -> sub_e935700
  5abab23  nop                                           
  5abab24  add rsp,0x20                                  
  5abab28  pop rbx                                       
  5abab29  pop rdi                                       
  5abab2a  pop rsi                                       
  5abab2b  pop r14                                       
  5abab2d  pop rbp                                       
  5abab2e  ret                                           
  5abab2f  int3                                          
  5abab30  sub rsp,0x78                                  
  5abab34  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
  5abab3b  xor rax,rsp                                   
  5abab3e  mov [rsp+0x70],rax                            
  5abab43  mov rax,[rcx+8]                               
  5abab47  movups xmm0,[rcx+0x48]                        
  5abab4b  movaps [rsp+0x30],xmm0                        
  ... (--max 400)
```

## CALLERS
```
  0x5ab8e20 sub_5ab8e20 size 0x97e
  0x66232b0 sub_66232b0 size 0xb3d0
  0x6640d80 sub_6640d80 size 0x401a
  0x6646980 sub_6646980 size 0x9425
  0x66560f0 sub_66560f0 size 0x86be
  0x6664a00 sub_6664a00 size 0x3b10
  0x666aca0 sub_666aca0 size 0x6c7c
  0x66742f0 sub_66742f0 size 0x9f91
  0x66a6830 sub_66a6830 size 0x2097
  0x66a9d50 sub_66a9d50 size 0x19fd
  0x66ade80 sub_66ade80 size 0x3025
  0x66bb7b0 sub_66bb7b0 size 0x114f
  0x66bd430 sub_66bd430 size 0x11f0
  0x66bf290 sub_66bf290 size 0x12e6
  0x66c1920 sub_66c1920 size 0x12e6
  0x66c3840 sub_66c3840 size 0x12e6
  0x66c5760 sub_66c5760 size 0x12e6
  0x66c7680 sub_66c7680 size 0x13f2
  0x66c98e0 sub_66c98e0 size 0x13f2
  0x66cba10 sub_66cba10 size 0x62d
  0x66cc7a0 sub_66cc7a0 size 0x13f2
  0x66ce8d0 sub_66ce8d0 size 0x13f2
  0x66ea3d0 sub_66ea3d0 size 0xf430
  0x670b6e0 sub_670b6e0 size 0x8584
  0x6722cb0 sub_6722cb0 size 0x77b4
  0x67375a0 sub_67375a0 size 0x3dfb
  0x673d150 sub_673d150 size 0x3251
  0x6745440 sub_6745440 size 0x3a5a
  0x675eae0 sub_675eae0 size 0x56a
  0x6761970 sub_6761970 size 0x593
  0x6765020 sub_6765020 size 0x550
  0x6768c70 sub_6768c70 size 0x4d5
  0x676abe0 sub_676abe0 size 0x70d
  0x676bab0 sub_676bab0 size 0x667
  0x676c7d0 sub_676c7d0 size 0x70d
  0x676d360 sub_676d360 size 0x667
  0x676e120 sub_676e120 size 0x7ad
  0x676f120 sub_676f120 size 0x709
  0x676ff60 sub_676ff60 size 0x70d
  0x6770af0 sub_6770af0 size 0x667
  0x6771580 sub_6771580 size 0x70d
  0x6772110 sub_6772110 size 0x667
  0x6772ba0 sub_6772ba0 size 0x7ad
  0x6773830 sub_6773830 size 0x709
  0x67758c0 sub_67758c0 size 0x4b9
  0x67762e0 sub_67762e0 size 0x7e86
  0x678e670 sub_678e670 size 0x569
  0x678f950 sub_678f950 size 0xfe0
  0x6792d90 sub_6792d90 size 0x7794
  0x67a7830 sub_67a7830 size 0x4f4
  0x67a8030 sub_67a8030 size 0x44c
  0x67a8720 sub_67a8720 size 0x452
  0x67a8e20 sub_67a8e20 size 0xee5
  0x67aa700 sub_67aa700 size 0x2cae
  0x67b1a70 sub_67b1a70 size 0x4ee
  0x67b2260 sub_67b2260 size 0x4f4
  0x67b2a60 sub_67b2a60 size 0x480
  0x67b3180 sub_67b3180 size 0x44c
  0x67b3870 sub_67b3870 size 0x452
  0x67b40d0 sub_67b40d0 size 0x456
  0x67b47d0 sub_67b47d0 size 0x60f
  0x67b5550 sub_67b5550 size 0x456
  0x67baa90 sub_67baa90 size 0x763
  0x67bb9f0 sub_67bb9f0 size 0x56b
  0x67bcc80 sub_67bcc80 size 0x525
  0x67bdb70 sub_67bdb70 size 0x9cf
  0x67beb70 sub_67beb70 size 0x4aa
  0x67cf410 sub_67cf410 size 0x73f
  0x67d14e0 sub_67d14e0 size 0x109d
  0x67d2f80 sub_67d2f80 size 0x56a
  0x67d3850 sub_67d3850 size 0x4d0
  0x67d4020 sub_67d4020 size 0x4d0
  0x67d47f0 sub_67d47f0 size 0x56a
  0x67d50c0 sub_67d50c0 size 0x819
  0x67d7e70 sub_67d7e70 size 0x717
  0x67d9080 sub_67d9080 size 0xa1b
  0x67daa20 sub_67daa20 size 0x59a
  0x67db7a0 sub_67db7a0 size 0xab2
  0x67dc7e0 sub_67dc7e0 size 0x4f8
  0x67dcfe0 sub_67dcfe0 size 0x56b
  0x67dd8b0 sub_67dd8b0 size 0x4f6
  0x67de380 sub_67de380 size 0x161d
  0x67e07c0 sub_67e07c0 size 0x4f6
  0x67e0fc0 sub_67e0fc0 size 0x373
  0x67e1990 sub_67e1990 size 0x4f4
  0x67e2540 sub_67e2540 size 0xfe0
  0x67e4280 sub_67e4280 size 0xee5
  0x67e5f00 sub_67e5f00 size 0x524
  0x67e6730 sub_67e6730 size 0x214
  0x67e6a70 sub_67e6a70 size 0x60f
  0x67e7400 sub_67e7400 size 0x6a9
  0x67e8020 sub_67e8020 size 0x577
  0x67e8900 sub_67e8900 size 0x4cf
  0x67ea0d0 sub_67ea0d0 size 0x6ab
  0x67eab80 sub_67eab80 size 0x564
  -- 95 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0x9bc830    sub_9bc830        unknown     [open]     [proven]  boundary=alloc
  0x9bd4a0    sub_9bd4a0        unknown     [open]     [proven]  boundary=os
  0x9bd6d0    sub_9bd6d0        unknown     [open]     [proven]  boundary=os
  0xeec59e0   sub_eec59e0       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_eec59e0.cpp;src\client\features\render\native\helpers\sub_eec59e0.h
  0xeec59f0   sub_eec59f0       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_eec59f0.cpp;src\client\features\render\native\helpers\sub_eec59f0.h
  0xeec5a00   sub_eec5a00       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_eec5a00.cpp;src\client\features\render\native\helpers\sub_eec5a00.h
  0xeec5a10   sub_eec5a10       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_eec5a10.cpp;src\client\features\render\native\helpers\sub_eec5a10.h

## STRINGS AND RIP REFS
  (none)

## FIELD ACCESS TABLE (descscan2, regs rdi,rsi,r9,r15)
  (no [reg+off] description reads detected; register unknown -> [open])

## KNOWN STRUCT LAYOUTS TOUCHED
  (none detected)

## CLOSEST FINISHED LIFT (style example, same size band + call shape)
  e93c790.md  size 0x101  callees~20  trust [derived]
  dossier: C:\Users\Atomi\Desktop\BlueySenseV2\docs\functions\e93c790.md

## KNOWN FACTS [derived]
  (none in ctx_facts.tsv for target or its direct callees/callers)

## DEAD ENDS [open]
  Unverified questions from oc_U-E*.md for target or its direct callees/callers.
  - UNRESOLVED CALL: 0xeec59e0/0xeec59f0/0xeec5a00/0xeec5a10 not in boundary or lift set (from docs\progress\oc_U-EX1.bcc1ae0_r1.md)
  - UNRESOLVED CALL: 0xeec59e0 (at 0xbcc1bcb), 0xeec59f0 (at 0xbcc1b76), 0xeec5a00 (at 0xbcc1bd0, 0xbcc1be9), 0xeec5a10 (at 0xbcc1ba4) -- none in native_boundary.tsv or native_functions.tsv (from docs\progress\oc_U-EX1.bcc1ae0_r1.md)
  - UNRESOLVED CALL: 0xeec59e0 (and 0xeec59f0/0xeec5a00/0xeec5a10) neither lifted nor boundary (from docs\progress\oc_U-EX1.bcc1ae0_r1.md)
  - UNRESOLVED CALL: 0x9bc830 (caller 0xe838560), 0x6b35400 (caller 0xe838560) - not classified lifted/boundary; classification unknown (from docs\progress\oc_U-EX2.e838560_r1.md)
  - UNRESOLVED CALL: s to 0x9bc830 and 0x6b35400 need classification before any lift. (from docs\progress\oc_U-EX2.e838560_r1.md)
  - UNRESOLVED CALL: none (all callees boundary: 0x9bc830 alloc @ native_boundary.tsv:149; 0xeea6040 vendor thunk via slot 0xF99FFA0 @ line 506; 0xeec6ed0 crt IAT import thunk @ line 507; 0 callees in lift set). (from docs\progress\oc_U-EX7.3c75f0.md)

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

