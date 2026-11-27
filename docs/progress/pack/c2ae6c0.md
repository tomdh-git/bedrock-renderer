# ctxpack build 0xc2ae6c0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=data=native_functions.tsv:07ea6058496f3c9340e582f2f9bc57b61494694303373d3389ba71c5842a53a6,data=native_deps.tsv:118356f1f1ba724d2eb40c7fc481ea24319c1aeba9f482039b865d6efece1f8b,data=native_boundary.tsv:058a56d8016eceaff394a955dc2a241d4a8a7d44663fc4cd9102ea82d9ec7315,data=native_boundary_candidates.tsv:b2db6e93be378325c9c8b370ea57463e6e4d762ef5f0a1cae81562abc4635b8c,data=ctx_facts.tsv:d2352cf1ceb26c34830b966be082a5e21a28f989c09fa2d4ecdfb97458b56aab,data=ctx_deadends.md:298967a276b4b7e4454961297c117289bf5ed3fcdf45c3240615fc10ed423c83

## HEADER
  rva        : 0xc2ae6c0
  size       : 0x10d (269 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 1 (direct), depth 1
  callers    : 1

## EXACT LISTING (0xc2ae6c0..0xc2ae7cd)
```
sub_c2ae6c0  [0xc2ae6c0..0xc2b06c0)  size 0x2000  1 xrefs in
  c2ae6c0  push rbp                                      
  c2ae6c1  push r14                                      
  c2ae6c3  push rsi                                      
  c2ae6c4  push rdi                                      
  c2ae6c5  push rbx                                      
  c2ae6c6  sub rsp,0x40                                  
  c2ae6ca  lea rbp,[rsp+0x40]                            
  c2ae6cf  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE      
  c2ae6d7  mov rsi,rcx                                   
  c2ae6da  xorps xmm0,xmm0                               
  c2ae6dd  movaps [rbp-0x20],xmm0                        
  c2ae6e1  lea rdi,[rbp-0x20]                            
  c2ae6e5  nop [rax+rax]                                 

loc_c2ae6f0:  ; from c2ae6fe
  c2ae6f0  mov rcx,rsi                                   
  c2ae6f3  mov rdx,rdi                                   
  c2ae6f6  call 0xC2AEA90                                ; -> sub_c2aea90
  c2ae6fb  nop                                           
  c2ae6fc  test al,al                                    
  c2ae6fe  jne short 0xC2AE6F0                           ; -> loc_c2ae6f0
  c2ae700  xorps xmm0,xmm0                               
  c2ae703  movups [rsi+0x278],xmm0                       ; W a0+0x278
  c2ae70a  movups [rsi+0x268],xmm0                       ; W a0+0x268
  c2ae711  mov qword ptr [rsi+0x288],0                   ; W a0+0x288
  c2ae71c  mov rbx,[rsi+0x290]                           ; R a0+0x290
  c2ae723  mov r14,[rsi+0x298]                           ; R a0+0x298
  c2ae72a  cmp rbx,r14                                   
  c2ae72d  jne short 0xC2AE749                           ; -> loc_c2ae749
  c2ae72f  jmp short 0xC2AE78D                           ; -> loc_c2ae78d
  c2ae731  nop [rax+rax]                                 ; R ret@c2aea90+0x0+idx

loc_c2ae740:  ; from c2ae750, c2ae756, c2ae76b, c2ae77d
  c2ae740  add rbx,0x10                                  
  c2ae744  cmp rbx,r14                                   
  c2ae747  je short 0xC2AE77F                            ; -> loc_c2ae77f

loc_c2ae749:  ; from c2ae72d
  c2ae749  mov rdi,[rbx+8]                               
  c2ae74d  test rdi,rdi                                  
  c2ae750  je short 0xC2AE740                            ; -> loc_c2ae740
  c2ae752  lock dec dword ptr [rdi+8]                    
  c2ae756  jne short 0xC2AE740                           ; -> loc_c2ae740
  c2ae758  mov rax,[rdi]                                 
  c2ae75b  mov rax,[rax]                                 
  c2ae75e  mov rcx,rdi                                   
  c2ae761  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c2ae767  lock dec dword ptr [rdi+0xC]                  
  c2ae76b  jne short 0xC2AE740                           ; -> loc_c2ae740
  c2ae76d  mov rax,[rdi]                                 
  c2ae770  mov rax,[rax+8]                               
  c2ae774  mov rcx,rdi                                   
  c2ae777  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c2ae77d  jmp short 0xC2AE740                           ; -> loc_c2ae740

loc_c2ae77f:  ; from c2ae747
  c2ae77f  mov rax,[rsi+0x290]                           
  c2ae786  mov [rsi+0x298],rax                           

loc_c2ae78d:  ; from c2ae72f
  c2ae78d  mov rsi,[rbp-0x18]                            
  c2ae791  test rsi,rsi                                  
  c2ae794  je short 0xC2AE7C2                            ; -> loc_c2ae7c2
  c2ae796  lock dec dword ptr [rsi+8]                    
  c2ae79a  jne short 0xC2AE7C2                           ; -> loc_c2ae7c2
  c2ae79c  mov rax,[rsi]                                 
  c2ae79f  mov rax,[rax]                                 
  c2ae7a2  mov rcx,rsi                                   
  c2ae7a5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c2ae7ab  lock dec dword ptr [rsi+0xC]                  
  c2ae7af  jne short 0xC2AE7C2                           ; -> loc_c2ae7c2
  c2ae7b1  mov rax,[rsi]                                 
  c2ae7b4  mov rax,[rax+8]                               
  c2ae7b8  mov rcx,rsi                                   
  c2ae7bb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c2ae7c1  nop                                           

loc_c2ae7c2:  ; from c2ae794, c2ae79a, c2ae7af
  c2ae7c2  add rsp,0x40                                  
  c2ae7c6  pop rbx                                       
  c2ae7c7  pop rdi                                       
  c2ae7c8  pop rsi                                       
  c2ae7c9  pop r14                                       
  c2ae7cb  pop rbp                                       
  c2ae7cc  ret                                           
  c2ae7cd  nop [rax]                                     
  c2ae7d0  mov [rsp+0x10],rdx                            
  c2ae7d5  push rbp                                      
  c2ae7d6  push r14                                      
  c2ae7d8  push rsi                                      
  c2ae7d9  push rdi                                      
  c2ae7da  push rbx                                      
  c2ae7db  sub rsp,0x20                                  
  c2ae7df  lea rbp,[rdx+0x40]                            
  c2ae7e3  lea rcx,[rbp-0x20]                            
  c2ae7e7  call 0x7E6D0                                  ; -> sub_7e6d0
  c2ae7ec  nop                                           
  c2ae7ed  add rsp,0x20                                  
  c2ae7f1  pop rbx                                       
  c2ae7f2  pop rdi                                       
  c2ae7f3  pop rsi                                       
  c2ae7f4  pop r14                                       
  c2ae7f6  pop rbp                                       
  c2ae7f7  ret                                           
  c2ae7f8  int3                                          
  c2ae7f9  int3                                          
  c2ae7fa  int3                                          
  c2ae7fb  int3                                          
  c2ae7fc  int3                                          
  c2ae7fd  int3                                          
  c2ae7fe  int3                                          
  c2ae7ff  int3                                          
  c2ae800  push r15                                      
  c2ae802  push r14                                      
  c2ae804  push r12                                      
  c2ae806  push rsi                                      
  c2ae807  push rdi                                      
  c2ae808  push rbx                                      
  c2ae809  sub rsp,0x28                                  
  c2ae80d  mov rdi,[rcx+0x20]                            
  c2ae811  mov rbx,rdi                                   
  c2ae814  and rbx,0x1F                                  
  c2ae818  je short 0xC2AE856                            ; -> loc_c2ae856
  c2ae81a  mov rsi,[rcx+0x40]                            

loc_c2ae81e:  ; from c2aea75
  c2ae81e  inc rdi                                       
  c2ae821  shl ebx,4                                     
  c2ae824  lea rax,[rsi+rbx]                             
  c2ae828  xorps xmm0,xmm0                               
  c2ae82b  movups [rsi+rbx],xmm0                         
  c2ae82f  mov r8,[rdx+8]                                
  c2ae833  test r8,r8                                    
  c2ae836  je short 0xC2AE83D                            ; -> loc_c2ae83d
  c2ae838  lock inc dword ptr [r8+8]                     

loc_c2ae83d:  ; from c2ae836
  c2ae83d  mov r8,[rdx]                                  
  c2ae840  mov [rax],r8                                  
  c2ae843  mov rdx,[rdx+8]                               
  c2ae847  mov [rax+8],rdx                               
  c2ae84b  mov [rcx+0x20],rdi                            
  c2ae84f  mov al,1                                      
  c2ae851  jmp 0xC2AE8DE                                 ; -> loc_c2ae8de

loc_c2ae856:  ; from c2ae818
  c2ae856  mov rax,[rcx+0x28]                            
  c2ae85a  sub rax,rdi                                   
  c2ae85d  mov r8,0x7FFFFFFFFFFFFFDF                     
  c2ae867  add rax,r8                                    
  c2ae86a  or r8,0x20                                    
  c2ae86e  cmp rax,r8                                    
  c2ae871  jae short 0xC2AE8DC                           ; -> loc_c2ae8dc
  c2ae873  mov rax,[rcx+0x60]                            
  c2ae877  test rax,rax                                  
  c2ae87a  je short 0xC2AE8DC                            ; -> loc_c2ae8dc
  c2ae87c  mov r9,[rax+8]                                
  c2ae880  inc r9                                        
  c2ae883  mov r8,[rax]                                  
  c2ae886  mov r10,[rax+0x18]                            
  c2ae88a  dec r8                                        
  c2ae88d  and r8,r9                                     
  c2ae890  mov r14,[r10+r8*8]                            
  c2ae894  mov r9,[r14]                                  
  c2ae897  cmp r9,1                                      
  c2ae89b  je short 0xC2AE8EC                            ; -> loc_c2ae8ec
  c2ae89d  mov r9,[r14+8]                                
  c2ae8a1  test r9,r9                                    
  c2ae8a4  je short 0xC2AE8EC                            ; -> loc_c2ae8ec
  c2ae8a6  mov rsi,rcx                                   
  c2ae8a9  mov r14,rdx                                   
  c2ae8ac  call 0x20B330                                 ; -> sub_20b330
  c2ae8b1  mov rdx,r14                                   
  c2ae8b4  mov rcx,rsi                                   
  c2ae8b7  mov rax,[rsi+0x60]                            
  c2ae8bb  mov r8,[rax+8]                                
  c2ae8bf  inc r8                                        
  c2ae8c2  mov r9,[rax]                                  
  c2ae8c5  mov r10,[rax+0x18]                            
  c2ae8c9  dec r9                                        
  c2ae8cc  and r9,r8                                     
  c2ae8cf  mov r14,[r10+r9*8]                            
  c2ae8d3  mov [r14],rdi                                 
  c2ae8d6  mov [rax+8],r9                                
  c2ae8da  jmp short 0xC2AE8F3                           ; -> loc_c2ae8f3

loc_c2ae8dc:  ; from c2ae871, c2ae87a
  c2ae8dc  xor eax,eax                                   

loc_c2ae8de:  ; from c2ae851
  c2ae8de  add rsp,0x28                                  
  c2ae8e2  pop rbx                                       
  c2ae8e3  pop rdi                                       
  c2ae8e4  pop rsi                                       
  c2ae8e5  pop r12                                       
  c2ae8e7  pop r14                                       
  c2ae8e9  pop r15                                       
  c2ae8eb  ret                                           

loc_c2ae8ec:  ; from c2ae89b, c2ae8a4
  c2ae8ec  mov [r14],rdi                                 
  c2ae8ef  mov [rax+8],r8                                

loc_c2ae8f3:  ; from c2ae8da
  c2ae8f3  mov r10,[rcx+0x50]                            
  c2ae8f7  mov rax,[r10+0x10]                            
  c2ae8fb  cmp rax,[r10+0x20]                            
  c2ae8ff  jae short 0xC2AE92C                           ; -> loc_c2ae92c
  c2ae901  mov eax,1                                     
  c2ae906  lock xadd [r10+0x10],rax                      
  c2ae90c  cmp rax,[r10+0x20]                            
  c2ae910  setae r8b                                     
  c2ae914  mov rsi,[r10+0x18]                            
  c2ae918  test rsi,rsi                                  
  c2ae91b  sete r9b                                      
  c2ae91f  or r9b,r8b                                    
  c2ae922  cmp r9b,1                                     
  c2ae926  jne 0xC2AEA4E                                 ; -> loc_c2aea4e

loc_c2ae92c:  ; from c2ae8ff
  c2ae92c  mov r8,[r10+0x28]                             
  c2ae930  test r8,r8                                    
  c2ae933  je 0xC2AE9E3                                  ; -> loc_c2ae9e3
  c2ae939  mov rsi,r8                                    
  c2ae93c  mov r9,r8                                     
  c2ae93f  jmp short 0xC2AE963                           ; -> loc_c2ae963
  c2ae941  nop [rax+rax]                                 

loc_c2ae950:  ; from c2ae96e, c2ae97d
  c2ae950  mov r8,[r10+0x28]                             

loc_c2ae954:  ; from c2ae9aa, c2ae9c7, c2ae9de
  c2ae954  mov rsi,r8                                    
  c2ae957  mov r9,r8                                     
  c2ae95a  test r8,r8                                    
  c2ae95d  je 0xC2AE9E3                                  ; -> loc_c2ae9e3

loc_c2ae963:  ; from c2ae93f
  c2ae963  mov eax,[rsi+0x230]                           
  c2ae969  test eax,0x7FFFFFFF                           
  c2ae96e  je short 0xC2AE950                            ; -> loc_c2ae950
  c2ae970  lea r8d,[rax+1]                               
  c2ae974  lock cmpxchg [rsi+0x230],r8d                  
  c2ae97d  jne short 0xC2AE950                           ; -> loc_c2ae950
  c2ae97f  mov r8,[rsi+0x238]                            
  c2ae986  mov rax,r9                                    
  c2ae989  lock cmpxchg [r10+0x28],r8                    
  c2ae98f  je 0xC2AEA5A                                  ; -> loc_c2aea5a
  c2ae995  mov r8,rax                                    
  c2ae998  mov eax,0xFFFFFFFF                            
  c2ae99d  lock xadd [rsi+0x230],eax                     
  c2ae9a5  cmp eax,0x80000001                            
  c2ae9aa  jne short 0xC2AE954                           ; -> loc_c2ae954
  c2ae9ac  mov rax,[r10+0x28]                            

loc_c2ae9b0:  ; from c2ae9dc
  c2ae9b0  mov [rsi+0x238],rax                           
  c2ae9b7  mov dword ptr [rsi+0x230],1                   
  c2ae9c1  lock cmpxchg [r10+0x28],r9                    
  c2ae9c7  je short 0xC2AE954                            ; -> loc_c2ae954
  c2ae9c9  mov r11d,0x7FFFFFFF                           
  c2ae9cf  lock xadd [rsi+0x230],r11d                    
  c2ae9d8  cmp r11d,1                                    
  c2ae9dc  je short 0xC2AE9B0                            ; -> loc_c2ae9b0
  c2ae9de  jmp 0xC2AE954                                 ; -> loc_c2ae954

loc_c2ae9e3:  ; from c2ae933, c2ae95d
  c2ae9e3  mov rsi,r8                                    
  c2ae9e6  test r8,r8                                    
  c2ae9e9  jne short 0xC2AEA62                           ; -> loc_c2aea62
  c2ae9eb  mov r15,rdx                                   
  c2ae9ee  mov r12,rcx                                   
  c2ae9f1  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  c2ae9f8  mov rax,[rcx]                                 
  c2ae9fb  mov rax,[rax+8]                               
  c2ae9ff  mov edx,0x248                                 
  c2aea04  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  c2aea0a  mov rsi,rax                                   
  c2aea0d  test rax,rax                                  
  c2aea10  je short 0xC2AEA7A                            ; -> loc_c2aea7a

loc_c2aea12:  ; from c2aea84
  c2aea12  mov qword ptr [rsi+0x238],0                   
  c2aea1d  xorps xmm0,xmm0                               
  c2aea20  movups [rsi+0x200],xmm0                       
  c2aea27  movups [rsi+0x210],xmm0                       
  c2aea2e  movups [rsi+0x220],xmm0                       
  c2aea35  mov dword ptr [rsi+0x230],0                   
  c2aea3f  mov byte ptr [rsi+0x240],1                    
  c2aea46  mov rcx,r12                                   
  c2aea49  mov rdx,r15                                   
  c2aea4c  jmp short 0xC2AEA62                           ; -> loc_c2aea62

loc_c2aea4e:  ; from c2ae926
  c2aea4e  imul rax,0x248                                
  c2aea55  add rsi,rax                                   
  c2aea58  jmp short 0xC2AEA62                           ; -> loc_c2aea62

loc_c2aea5a:  ; from c2ae98f
  c2aea5a  lock add dword ptr [rsi+0x230],0xFFFFFFFE     

loc_c2aea62:  ; from c2ae9e9, c2aea4c, c2aea58
  c2aea62  mov qword ptr [rsi+0x208],0                   
  c2aea6d  mov [r14+8],rsi                               
  c2aea71  mov [rcx+0x40],rsi                            
  c2aea75  jmp 0xC2AE81E                                 ; -> loc_c2ae81e

loc_c2aea7a:  ; from c2aea10
  c2aea7a  mov ecx,0x248                                 
  c2aea7f  call 0x9BC830                                 ; -> sub_9bc830
  c2aea84  jmp short 0xC2AEA12                           ; -> loc_c2aea12
  c2aea86  int3                                          
  c2aea87  int3                                          
  c2aea88  int3                                          
  c2aea89  int3                                          
  c2aea8a  int3                                          
  c2aea8b  int3                                          
  c2aea8c  int3                                          
  c2aea8d  int3                                          
  c2aea8e  int3                                          
  c2aea8f  int3                                          
  c2aea90  push r15                                      
  c2aea92  push r14                                      
  c2aea94  push r12                                      
  c2aea96  push rsi                                      
  c2aea97  push rdi                                      
  c2aea98  push rbx                                      
  c2aea99  sub rsp,0x28                                  
  c2aea9d  mov rax,[rcx]                                 
  c2aeaa0  test rax,rax                                  
  c2aeaa3  je 0xC2AEB4E                                  ; -> loc_c2aeb4e
  c2aeaa9  mov rsi,rdx                                   
  c2aeaac  xor edx,edx                                   
  c2aeaae  mov r8,0x8000000000000000                     
  c2aeab8  xor r9d,r9d                                   
  c2aeabb  xor edi,edi                                   
  c2aeabd  xor r10d,r10d                                 

loc_c2aeac0:  ; from c2aeb16
  c2aeac0  mov r11,r10                                   
  c2aeac3  mov rbx,rdi                                   
  c2aeac6  mov r14,r9                                    
  c2aeac9  mov r15,[rax+0x20]                            
  c2aeacd  mov r10,[rax+0x28]                            
  c2aead1  mov r12,r10                                   
  c2aead4  sub r12,r15                                   
  c2aead7  sub r15,r10                                   
  c2aeada  cmp r12,r8                                    
  c2aeadd  cmovbe r15,rdx                                
  c2aeae1  cmp r15,r9                                    
  c2aeae4  cmova r9,r15                                  
  c2aeae8  cmova rdi,rax                                 
  c2aeaec  xor r10d,r10d                                 
  c2aeaef  test r15,r15                                  
  c2aeaf2  setne r10b                                    
  c2aeaf6  cmove rdi,rbx                                 
  c2aeafa  cmove r9,r14                                  
  c2aeafe  add r10,r11                                   
  c2aeb01  mov r11,[rax+8]                               
  c2aeb05  lea rax,[r11-8]                               
  c2aeb09  test r11,r11                                  
  c2aeb0c  cmove rax,r11                                 
  c2aeb10  je short 0xC2AEB18                            ; -> loc_c2aeb18
  c2aeb12  cmp r10,3                                     
  c2aeb16  jb short 0xC2AEAC0                            ; -> loc_c2aeac0

loc_c2aeb18:  ; from c2aeb10
  c2aeb18  test r10,r10                                  
  c2aeb1b  je short 0xC2AEB4E                            ; -> loc_c2aeb4e
  c2aeb1d  mov rbx,rcx                                   
  c2aeb20  cmp byte ptr [rdi+0x48],1                     
  c2aeb24  jne short 0xC2AEB33                           ; -> loc_c2aeb33
  c2aeb26  mov rcx,rdi                                   
  c2aeb29  mov rdx,rsi                                   
  c2aeb2c  call 0xC2AEBA0                                ; -> sub_c2aeba0
  c2aeb31  jmp short 0xC2AEB3E                           ; -> loc_c2aeb3e

loc_c2aeb33:  ; from c2aeb24
  c2aeb33  mov rcx,rdi                                   
  c2aeb36  mov rdx,rsi                                   
  c2aeb39  call 0xC2AECF0                                ; -> sub_c2aecf0

loc_c2aeb3e:  ; from c2aeb31
  c2aeb3e  mov ecx,eax                                   
  c2aeb40  mov al,1                                      
  c2aeb42  test cl,cl                                    
  c2aeb44  jne short 0xC2AEB50                           ; -> loc_c2aeb50
  c2aeb46  mov rbx,[rbx]                                 
  c2aeb49  test rbx,rbx                                  
  c2aeb4c  jne short 0xC2AEB7C                           ; -> loc_c2aeb7c

loc_c2aeb4e:  ; from c2aeaa3, c2aeb1b, c2aeb7a
  c2aeb4e  xor eax,eax                                   

loc_c2aeb50:  ; from c2aeb44, c2aeb98
  c2aeb50  add rsp,0x28                                  
  c2aeb54  pop rbx                                       
  c2aeb55  pop rdi                                       
  c2aeb56  pop rsi                                       
  c2aeb57  pop r12                                       
  c2aeb59  pop r14                                       
  c2aeb5b  pop r15                                       
  c2aeb5d  ret                                           
  c2aeb5e  xchg ax,ax                                    

loc_c2aeb60:  ; from c2aeb85
  c2aeb60  mov rcx,rbx                                   
  c2aeb63  mov rdx,rsi                                   
  c2aeb66  call 0xC2AECF0                                ; -> sub_c2aecf0
  c2aeb6b  test al,al                                    
  c2aeb6d  jne short 0xC2AEB96                           ; -> loc_c2aeb96

loc_c2aeb6f:  ; from c2aeb7f, c2aeb94
  c2aeb6f  mov rax,[rbx+8]                               
  c2aeb73  lea rbx,[rax-8]                               
  c2aeb77  test rax,rax                                  
  c2aeb7a  je short 0xC2AEB4E                            ; -> loc_c2aeb4e

loc_c2aeb7c:  ; from c2aeb4c
  c2aeb7c  cmp rbx,rdi                                   
  c2aeb7f  je short 0xC2AEB6F                            ; -> loc_c2aeb6f
  c2aeb81  cmp byte ptr [rbx+0x48],1                     
  c2aeb85  jne short 0xC2AEB60                           ; -> loc_c2aeb60
  c2aeb87  mov rcx,rbx                                   
  c2aeb8a  mov rdx,rsi                                   
  c2aeb8d  call 0xC2AEBA0                                ; -> sub_c2aeba0
  c2aeb92  test al,al                                    
  c2aeb94  je short 0xC2AEB6F                            ; -> loc_c2aeb6f

loc_c2aeb96:  ; from c2aeb6d
  c2aeb96  mov al,1                                      
  c2aeb98  jmp short 0xC2AEB50                           ; -> loc_c2aeb50
  c2aeb9a  int3                                          
  c2aeb9b  int3                                          
  c2aeb9c  int3                                          
  c2aeb9d  int3                                          
  c2aeb9e  int3                                          
  c2aeb9f  int3                                          
  c2aeba0  push r14                                      
  c2aeba2  push rsi                                      
  c2aeba3  push rdi                                      
  c2aeba4  push rbx                                      
  c2aeba5  sub rsp,0x28                                  
  c2aeba9  mov rax,0x8000000000000000                    
  c2aebb3  mov r9,[rcx+0x20]                             
  c2aebb7  mov r8,[rcx+0x38]                             
  c2aebbb  mov r10,[rcx+0x30]                            
  c2aebbf  add r9,r8                                     
  c2aebc2  sub r10,r9                                    
  c2aebc5  cmp r10,rax                                   
  c2aebc8  jbe 0xC2AEC5B                                 ; -> loc_c2aec5b
  c2aebce  mov edi,1                                     
  c2aebd3  mov r9d,1                                     
  c2aebd9  lock xadd [rcx+0x30],r9                       
  c2aebdf  mov r10,[rcx+0x20]                            
  c2aebe3  add r8,r10                                    
  c2aebe6  sub r9,r8                                     
  c2aebe9  cmp r9,rax                                    
  c2aebec  jbe short 0xC2AEC56                           ; -> loc_c2aec56
  c2aebee  lock xadd [rcx+0x28],rdi                      
  c2aebf4  mov rax,[rcx+0x58]                            
  c2aebf8  mov rcx,[rax+8]                               
  c2aebfc  mov r8,[rax]                                  
  c2aebff  mov rax,[rax+0x10]                            
  c2aec03  mov r9,rcx                                    
  c2aec06  shl r9,4                                      
  c2aec0a  mov r10,rdi                                   
  c2aec0d  and r10,0xFFFFFFFFFFFFFFE0                    
  ... (--max 400)
```

## CALLERS
```
  0x6618810 sub_6618810 size 0x1328
  -- 1 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0xc2aea90   sub_c2aea90       unknown     [open]     [proven]  unresolved

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
  (none in ctx_deadends.md for target or its direct callees/callers)

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

