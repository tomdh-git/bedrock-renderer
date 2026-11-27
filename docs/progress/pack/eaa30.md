# ctxpack build 0xeaa30

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb,data=ctx_facts.tsv:d2352cf1ceb26c34830b966be082a5e21a28f989c09fa2d4ecdfb97458b56aab,data=ctx_deadends.md:298967a276b4b7e4454961297c117289bf5ed3fcdf45c3240615fc10ed423c83

## HEADER
  rva        : 0xeaa30
  size       : 0x182 (386 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 4 (direct), depth 1
  callers    : 444

## EXACT LISTING (0xeaa30..0xeabb2)
```
sub_eaa30  [0xeaa30..0xeca30)  size 0x2000  1098 xrefs in
  eaa30  push rbp                                      
  eaa31  push r15                                      
  eaa33  push r14                                      
  eaa35  push r12                                      
  eaa37  push rsi                                      
  eaa38  push rdi                                      
  eaa39  push rbx                                      
  eaa3a  sub rsp,0x60                                  
  eaa3e  lea rbp,[rsp+0x60]                            
  eaa43  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE      
  eaa4b  mov r14,r9                                    
  eaa4e  mov edi,r8d                                   
  eaa51  mov ebx,edx                                   
  eaa53  mov r15d,ecx                                  
  eaa56  lea r12,[0x128C1EF8]                          ; [data_128c1ef8]
  eaa5d  mov rcx,r12                                   
  eaa60  call 0xE943178                                ; -> sub_e943178
  eaa65  lock inc qword ptr [0x128C1F58]               ; [data_128c1f58]
  eaa6d  mov rcx,r12                                   
  eaa70  call 0xE94319C                                ; -> sub_e94319c
  eaa75  mov rax,[0x128C1F60]                          ; [data_128c1f60]
  eaa7c  test rax,rax                                  
  eaa7f  je short 0xEAAA6                              ; -> loc_eaaa6
  eaa81  cmp byte ptr [rax],1                          
  eaa84  jne short 0xEAAA6                             ; -> loc_eaaa6
  eaa86  mov rcx,[0x128C1F68]                          ; [data_128c1f68]
  eaa8d  test rcx,rcx                                  
  eaa90  je short 0xEAAEA                              ; -> loc_eaaea
  eaa92  lock inc dword ptr [rcx+8]                    
  eaa96  mov rax,[0x128C1F60]                          ; [data_128c1f60]
  eaa9d  mov rsi,[0x128C1F68]                          ; [data_128c1f68]
  eaaa4  jmp short 0xEAAEC                             ; -> loc_eaaec

loc_eaaa6:  ; from eaa7f, eaa84
  eaaa6  mov qword ptr [rbp-0x30],0                    
  eaaae  mov byte ptr [rbp-0x28],0                     
  eaab2  lea rcx,[0x128C1EF8]                          ; [data_128c1ef8]
  eaab9  call 0x3B2020                                 ; -> sub_3b2020

loc_eaabe:  ; from eab38, eab74, eab7e, eab97, eabad
  eaabe  cmp byte ptr [rbp-0x28],1                     
  eaac2  jne short 0xEAADB                             ; -> loc_eaadb
  eaac4  mov rcx,[rbp-0x30]                            
  eaac8  add rsp,0x60                                  
  eaacc  pop rbx                                       
  eaacd  pop rdi                                       
  eaace  pop rsi                                       
  eaacf  pop r12                                       
  eaad1  pop r14                                       
  eaad3  pop r15                                       
  eaad5  pop rbp                                       
  eaad6  jmp 0x3B2020                                  ; -> sub_3b2020

loc_eaadb:  ; from eaac2
  eaadb  add rsp,0x60                                  
  eaadf  pop rbx                                       
  eaae0  pop rdi                                       
  eaae1  pop rsi                                       
  eaae2  pop r12                                       
  eaae4  pop r14                                       
  eaae6  pop r15                                       
  eaae8  pop rbp                                       
  eaae9  ret                                           

loc_eaaea:  ; from eaa90
  eaaea  xor esi,esi                                   

loc_eaaec:  ; from eaaa4
  eaaec  mov rcx,[0x128C1F70]                          ; [data_128c1f70]
  eaaf3  mov [rbp-0x30],r12                            
  eaaf7  mov byte ptr [rbp-0x28],1                     
  eaafb  mov [rbp-0x20],rax                            
  eaaff  mov [rbp-0x18],rsi                            
  eab03  mov [rbp-0x10],rcx                            
  eab07  test rax,rax                                  
  eab0a  je short 0xEAB2B                              ; -> loc_eab2b
  eab0c  cmp byte ptr [rax],1                          
  eab0f  jne short 0xEAB2B                             ; -> loc_eab2b
  eab11  cmp byte ptr [rcx+0x18],1                     
  eab15  jne short 0xEAB2B                             ; -> loc_eab2b
  eab17  mov [rsp+0x20],r14                            
  eab1c  mov edx,r15d                                  
  eab1f  mov r8d,ebx                                   
  eab22  mov r9d,edi                                   
  eab25  call 0x3D0730                                 ; -> sub_3d0730
  eab2a  nop                                           

loc_eab2b:  ; from eab0a, eab0f, eab15
  eab2b  lea rax,[rbp-0x20]                            
  eab2f  xorps xmm0,xmm0                               
  eab32  movups [rax],xmm0                             
  eab35  test rsi,rsi                                  
  eab38  je short 0xEAABE                              ; -> loc_eaabe
  eab3a  lock dec dword ptr [rsi+8]                    
  eab3e  jne short 0xEAB65                             ; -> loc_eab65
  eab40  mov rax,[rsi]                                 
  eab43  mov rax,[rax]                                 
  eab46  mov rcx,rsi                                   
  eab49  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  eab4f  lock dec dword ptr [rsi+0xC]                  
  eab53  jne short 0xEAB65                             ; -> loc_eab65
  eab55  mov rax,[rsi]                                 
  eab58  mov rax,[rax+8]                               
  eab5c  mov rcx,rsi                                   
  eab5f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_eab65:  ; from eab3e, eab53
  eab65  mov rsi,[rbp-0x18]                            
  eab69  mov qword ptr [rbp-0x10],0                    
  eab71  test rsi,rsi                                  
  eab74  je 0xEAABE                                    ; -> loc_eaabe
  eab7a  lock dec dword ptr [rsi+8]                    
  eab7e  jne 0xEAABE                                   ; -> loc_eaabe
  eab84  mov rax,[rsi]                                 
  eab87  mov rax,[rax]                                 
  eab8a  mov rcx,rsi                                   
  eab8d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  eab93  lock dec dword ptr [rsi+0xC]                  
  eab97  jne 0xEAABE                                   ; -> loc_eaabe
  eab9d  mov rax,[rsi]                                 
  eaba0  mov rax,[rax+8]                               
  eaba4  mov rcx,rsi                                   
  eaba7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  eabad  jmp 0xEAABE                                   ; -> loc_eaabe
  eabb2  nop [rax+rax]                                 
  eabc0  mov [rsp+0x10],rdx                            
  eabc5  push rbp                                      
  eabc6  push r15                                      
  eabc8  push r14                                      
  eabca  push r12                                      
  eabcc  push rsi                                      
  eabcd  push rdi                                      
  eabce  push rbx                                      
  eabcf  sub rsp,0x30                                  
  eabd3  lea rbp,[rdx+0x60]                            
  eabd7  lea rcx,[rbp-0x30]                            
  eabdb  call 0x79280                                  ; -> sub_79280
  eabe0  nop                                           
  eabe1  add rsp,0x30                                  
  eabe5  pop rbx                                       
  eabe6  pop rdi                                       
  eabe7  pop rsi                                       
  eabe8  pop r12                                       
  eabea  pop r14                                       
  eabec  pop r15                                       
  eabee  pop rbp                                       
  eabef  ret                                           
  eabf0  push r15                                      
  eabf2  push r14                                      
  eabf4  push r12                                      
  eabf6  push rsi                                      
  eabf7  push rdi                                      
  eabf8  push rbx                                      
  eabf9  sub rsp,0x28                                  
  eabfd  mov rsi,rcx                                   
  eac00  lea r14,[rcx+0x10]                            
  eac04  mov rdi,[rcx+0x10]                            
  eac08  mov r15,[rcx+0x18]                            
  eac0c  cmp rdi,r15                                   
  eac0f  jne short 0xEAC29                             ; -> loc_eac29
  eac11  test rdi,rdi                                  
  eac14  jne 0xEACAF                                   ; -> loc_eacaf
  eac1a  jmp 0xEACEE                                   ; -> loc_eacee
  eac1f  nop                                           

loc_eac20:  ; from eac3d, eac62, eac75, eaca2
  eac20  add rdi,0x10                                  
  eac24  cmp rdi,r15                                   
  eac27  je short 0xEACA7                              ; -> loc_eaca7

loc_eac29:  ; from eac0f
  eac29  mov rbx,[rdi+8]                               
  eac2d  mov rax,[rsi+0x18]                            
  eac31  cmp rbx,[rax-8]                               
  eac35  je short 0xEAC70                              ; -> loc_eac70
  eac37  mov rax,[rdi]                                 
  eac3a  test rax,rax                                  
  eac3d  je short 0xEAC20                              ; -> loc_eac20
  eac3f  shl rax,4                                     
  eac43  lea r12,[rax+rax*2]                           
  eac47  add rbx,8                                     
  eac4b  nop [rax+rax]                                 

loc_eac50:  ; from eac60
  eac50  mov rcx,rbx                                   
  eac53  call 0x115C80                                 ; -> sub_115c80
  eac58  add rbx,0x30                                  
  eac5c  add r12,0xFFFFFFFFFFFFFFD0                    
  eac60  jne short 0xEAC50                             ; -> loc_eac50
  eac62  jmp short 0xEAC20                             ; -> loc_eac20
  eac64  nop [rax+rax]                                 ; R ret@115c80+0x0+idx

loc_eac70:  ; from eac35
  eac70  cmp qword ptr [rsi+0x28],0                    
  eac75  je short 0xEAC20                              ; -> loc_eac20
  eac77  mov ebx,8                                     
  eac7c  xor r12d,r12d                                 
  eac7f  nop                                           

loc_eac80:  ; from eaca0
  eac80  cmp r12,[rdi]                                 
  eac83  jae 0xEAD41                                   ; -> loc_ead41
  eac89  mov rcx,[rdi+8]                               
  eac8d  add rcx,rbx                                   
  eac90  call 0x115C80                                 ; -> sub_115c80
  eac95  inc r12                                       
  eac98  add rbx,0x30                                  
  eac9c  cmp r12,[rsi+0x28]                            
  eaca0  jb short 0xEAC80                              ; -> loc_eac80
  eaca2  jmp 0xEAC20                                   ; -> loc_eac20

loc_eaca7:  ; from eac27
  eaca7  mov rdi,[r14]                                 
  eacaa  test rdi,rdi                                  
  eacad  je short 0xEACEE                              ; -> loc_eacee

loc_eacaf:  ; from eac14
  eacaf  mov rdx,[rsi+0x20]                            
  eacb3  sub rdx,rdi                                   
  eacb6  cmp rdx,0x1000                                
  eacbd  jb short 0xEACD7                              ; -> loc_eacd7
  eacbf  mov rax,[rdi-8]                               
  eacc3  add rdi,0xFFFFFFFFFFFFFFF8                    
  eacc7  sub rdi,rax                                   
  eacca  cmp rdi,0x20                                  
  eacce  jae short 0xEAD46                             ; -> loc_ead46
  eacd0  add rdx,0x27                                  
  eacd4  mov rdi,rax                                   

loc_eacd7:  ; from eacbd
  eacd7  mov rcx,rdi                                   
  eacda  call 0xE935700                                ; -> sub_e935700
  eacdf  xorps xmm0,xmm0                               
  eace2  movups [r14],xmm0                             
  eace6  mov qword ptr [r14+0x10],0                    

loc_eacee:  ; from eac1a, eacad
  eacee  mov rsi,[rsi+8]                               
  eacf2  test rsi,rsi                                  
  eacf5  je short 0xEAD33                              ; -> loc_ead33
  eacf7  lock dec dword ptr [rsi+8]                    
  eacfb  jne short 0xEAD33                             ; -> loc_ead33
  eacfd  mov rax,[rsi]                                 
  ead00  mov rax,[rax]                                 
  ead03  mov rcx,rsi                                   
  ead06  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  ead0c  lock dec dword ptr [rsi+0xC]                  
  ead10  jne short 0xEAD33                             ; -> loc_ead33
  ead12  mov rax,[rsi]                                 
  ead15  mov rax,[rax+8]                               
  ead19  mov rdx,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  ead20  mov rcx,rsi                                   
  ead23  add rsp,0x28                                  
  ead27  pop rbx                                       
  ead28  pop rdi                                       
  ead29  pop rsi                                       
  ead2a  pop r12                                       
  ead2c  pop r14                                       
  ead2e  pop r15                                       
  ead30  jmp rdx                                       

loc_ead33:  ; from eacf5, eacfb, ead10
  ead33  add rsp,0x28                                  
  ead37  pop rbx                                       
  ead38  pop rdi                                       
  ead39  pop rsi                                       
  ead3a  pop r12                                       
  ead3c  pop r14                                       
  ead3e  pop r15                                       
  ead40  ret                                           

loc_ead41:  ; from eac83
  ead41  call 0x78ED0                                  ; -> sub_78ed0

loc_ead46:  ; from eacce
  ead46  mov qword ptr [rsp+0x20],0                    
  ead4f  xor ecx,ecx                                   
  ead51  xor edx,edx                                   
  ead53  xor r8d,r8d                                   
  ead56  xor r9d,r9d                                   
  ead59  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  ead5f  int3                                          
  ead60  push rbp                                      
  ead61  push r15                                      
  ead63  push r14                                      
  ead65  push r13                                      
  ead67  push r12                                      
  ead69  push rsi                                      
  ead6a  push rdi                                      
  ead6b  push rbx                                      
  ead6c  sub rsp,0xB8                                  
  ead73  lea rbp,[rsp+0x80]                            
  ead7b  movaps [rbp+0x20],xmm6                        
  ead7f  mov qword ptr [rbp+0x18],0xFFFFFFFFFFFFFFFE   
  ead87  mov [rbp+0x10],rdx                            
  ead8b  mov r13,[rcx]                                 
  ead8e  mov r12,[rcx+8]                               
  ead92  xorps xmm6,xmm6                               
  ead95  xor esi,esi                                   
  ead97  cmp r13,r12                                   
  ead9a  jne short 0xEADE9                             ; -> loc_eade9

loc_ead9c:  ; from eade7, eaf2c
  ead9c  mov rax,[rbp+0x10]                            
  eada0  mov rcx,[rax+0x38]                            
  eada4  test rcx,rcx                                  
  eada7  je short 0xEADBC                              ; -> loc_eadbc
  eada9  cmp rcx,rax                                   
  eadac  setne dl                                      
  eadaf  mov rax,[rcx]                                 
  eadb2  mov rax,[rax+0x20]                            
  eadb6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_eadbc:  ; from eada7
  eadbc  mov rax,rsi                                   
  eadbf  movaps xmm6,[rbp+0x20]                        
  eadc3  add rsp,0xB8                                  
  eadca  pop rbx                                       
  eadcb  pop rdi                                       
  eadcc  pop rsi                                       
  eadcd  pop r12                                       
  eadcf  pop r13                                       
  eadd1  pop r14                                       
  eadd3  pop r15                                       
  eadd5  pop rbp                                       
  eadd6  ret                                           
  eadd7  nop [rax+rax]                                 

loc_eade0:  ; from eadf6, eae56
  eade0  add r13,0x30                                  
  eade4  cmp r13,r12                                   
  eade7  je short 0xEAD9C                              ; -> loc_ead9c

loc_eade9:  ; from ead9a, eaf26
  eade9  movzx eax,byte ptr [r13+2]                    
  eadee  cmp eax,4                                     
  eadf1  je short 0xEAE10                              ; -> loc_eae10
  eadf3  cmp eax,5                                     
  eadf6  jne short 0xEADE0                             ; -> loc_eade0
  eadf8  cmp byte ptr [r13+0x28],0                     
  eadfd  je short 0xEAE58                              ; -> loc_eae58

loc_eadff:  ; from eaf3c
  eadff  xor r14d,r14d                                 
  eae02  lea rbx,[0xF847A07]                           ; [data_f847a07]
  eae09  jmp 0xEAE92                                   ; -> loc_eae92
  eae0e  xchg ax,ax                                    

loc_eae10:  ; from eadf1
  eae10  cmp byte ptr [r13+0x28],1                     
  eae15  jne 0xEB006                                   ; -> loc_eb006
  eae1b  mov qword ptr [rbp-0x18],0                    
  eae23  mov rax,[rbp+0x10]                            
  eae27  mov rcx,[rax+0x38]                            
  eae2b  test rcx,rcx                                  
  eae2e  je short 0xEAE45                              ; -> loc_eae45
  eae30  mov rax,[rcx]                                 
  eae33  mov rax,[rax]                                 
  eae36  lea rdx,[rbp-0x50]                            
  eae3a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  eae40  nop                                           
  eae41  mov [rbp-0x18],rax                            

loc_eae45:  ; from eae2e
  eae45  lea rcx,[r13+8]                               
  eae49  lea rdx,[rbp-0x50]                            
  eae4d  call 0xEAD60                                  ; -> sub_ead60
  eae52  nop                                           
  eae53  add rsi,rax                                   
  eae56  jmp short 0xEADE0                             ; -> loc_eade0

loc_eae58:  ; from eadfd
  eae58  lea rbx,[r13+8]                               
  eae5c  mov rcx,rbx                                   
  eae5f  call 0xE932510                                ; -> sub_e932510
  eae64  nop                                           
  eae65  test al,al                                    
  eae67  je 0xEAF31                                    ; -> loc_eaf31
  eae6d  mov rcx,rbx                                   
  eae70  xor edx,edx                                   
  eae72  call 0xE932460                                ; -> sub_e932460
  eae77  nop                                           
  eae78  lea rbx,[0xF5BDE7E]                           ; [data_f5bde7e] "true"
  eae7f  test al,al                                    
  eae81  jne short 0xEAE8A                             ; -> loc_eae8a
  eae83  lea rbx,[0xF5C5A49]                           ; [data_f5c5a49] "false"

loc_eae8a:  ; from eae81
  eae8a  movzx r14d,al                                 
  eae8e  xor r14,5                                     

loc_eae92:  ; from eae09
  eae92  movaps [rbp-0x10],xmm6                        
  eae96  mov edi,0xF                                   

loc_eae9b:  ; from eaf73
  eae9b  lea r15,[rbp-0x10]                            

loc_eae9f:  ; from eafe0
  eae9f  mov [rbp],r14                                 
  eaea3  mov [rbp+8],rdi                               
  eaea7  mov rcx,r15                                   
  eaeaa  mov rdx,rbx                                   
  eaead  mov r8,r14                                    
  eaeb0  call 0xEEC6EC0                                ; -> sub_eec6ec0
  eaeb5  mov byte ptr [r15+r14],0                      
  eaeba  mov rax,[rbp+0x10]                            
  eaebe  mov rcx,[rax+0x38]                            
  eaec2  test rcx,rcx                                  
  eaec5  je 0xEB000                                    ; -> loc_eb000
  eaecb  mov rax,[rcx]                                 
  eaece  mov rax,[rax+0x10]                            
  eaed2  lea rdx,[rbp-0x10]                            
  eaed6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  eaedc  nop                                           
  eaedd  mov rax,[rbp+8]                               
  eaee1  cmp rax,0x10                                  
  eaee5  jb short 0xEAF1C                              ; -> loc_eaf1c
  eaee7  mov rcx,[rbp-0x10]                            
  eaeeb  lea rdx,[rax+1]                               
  eaeef  cmp rdx,0x1000                                
  eaef6  jb short 0xEAF17                              ; -> loc_eaf17
  eaef8  mov r8,[rcx-8]                                
  eaefc  add rcx,0xFFFFFFFFFFFFFFF8                    
  eaf00  sub rcx,r8                                    
  eaf03  cmp rcx,0x20                                  
  eaf07  jae 0xEB00C                                   ; -> loc_eb00c
  eaf0d  add rax,0x28                                  
  eaf11  mov rdx,rax                                   
  eaf14  mov rcx,r8                                    

loc_eaf17:  ; from eaef6
  eaf17  call 0xE935700                                ; -> sub_e935700

loc_eaf1c:  ; from eaee5
  eaf1c  inc rsi                                       
  eaf1f  add r13,0x30                                  
  eaf23  cmp r13,r12                                   
  eaf26  jne 0xEADE9                                   ; -> loc_eade9
  eaf2c  jmp 0xEAD9C                                   ; -> loc_ead9c

loc_eaf31:  ; from eae67
  eaf31  mov rcx,rbx                                   
  eaf34  call 0xE932590                                ; -> sub_e932590
  eaf39  nop                                           
  eaf3a  test al,al                                    
  eaf3c  je 0xEADFF                                    ; -> loc_eadff
  eaf42  mov rcx,rbx                                   
  eaf45  call 0xE932130                                ; -> sub_e932130
  eaf4a  nop                                           
  eaf4b  mov rbx,rax                                   
  eaf4e  mov rcx,rax                                   
  eaf51  call 0xEEC7570                                ; -> sub_eec7570
  eaf56  movaps [rbp-0x10],xmm6                        
  eaf5a  movaps [rbp],xmm6                             
  eaf5e  test rax,rax                                  
  eaf61  js 0xEB026                                    ; -> loc_eb026
  eaf67  mov r14,rax                                   
  eaf6a  mov edi,0xF                                   
  eaf6f  cmp rax,0x10                                  
  eaf73  jb 0xEAE9B                                    ; -> loc_eae9b
  eaf79  mov rdx,r14                                   
  eaf7c  or rdx,0xF                                    
  eaf80  mov rdi,rdx                                   
  eaf83  cmp rdx,0x17                                  
  eaf87  jae short 0xEAF8E                             ; -> loc_eaf8e
  eaf89  mov edi,0x16                                  

loc_eaf8e:  ; from eaf87
  eaf8e  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  ... (--max 400)
```

## CALLERS
```
  0xe5a90 sub_e5a90 size 0x1397
  0xf4330 sub_f4330 size 0x2ed
  0xf4650 sub_f4650 size 0x28c
  0xf4910 sub_f4910 size 0x1fe
  0xf5170 sub_f5170 size 0x371
  0xf5580 sub_f5580 size 0x23e
  0xf5e60 sub_f5e60 size 0x1ea
  0xf6c80 sub_f6c80 size 0x1fb
  0xf7070 sub_f7070 size 0x206
  0xf72b0 sub_f72b0 size 0x1c2
  0xf74b0 sub_f74b0 size 0x262
  0xf7750 sub_f7750 size 0x267
  0xf79f0 sub_f79f0 size 0x1fd
  0xf7c20 sub_f7c20 size 0x134
  0xf7d90 sub_f7d90 size 0x229
  0x5f2900 sub_5f2900 size 0x4f
  0x685050 sub_685050 size 0x156
  0x6851b0 sub_6851b0 size 0x179
  0x6858b0 sub_6858b0 size 0x3d4
  0x685e10 sub_685e10 size 0x36a
  0x686240 sub_686240 size 0x379
  0x686680 sub_686680 size 0x2ad
  0x686ad0 sub_686ad0 size 0x216
  0x686cf0 sub_686cf0 size 0x217
  0x686f10 sub_686f10 size 0x2c8
  0x687390 sub_687390 size 0x1ad
  0x687540 sub_687540 size 0x2bb
  0x6a0840 sub_6a0840 size 0x294
  0x6a0b50 sub_6a0b50 size 0x294
  0x6a0e80 sub_6a0e80 size 0x29e
  0x6a1190 sub_6a1190 size 0x29e
  0x7461f0 sub_7461f0 size 0x19a
  0x7463c0 sub_7463c0 size 0x217
  0x746640 sub_746640 size 0x6c6
  0x747050 sub_747050 size 0x352
  0x7f0240 sub_7f0240 size 0xec3
  0x7f2040 sub_7f2040 size 0x1b0
  0x7f2270 sub_7f2270 size 0x1ad
  0x7f24a0 sub_7f24a0 size 0x1ad
  0x7f8100 sub_7f8100 size 0x131
  0x802e40 sub_802e40 size 0xc8
  0x94cf90 sub_94cf90 size 0x5ae
  0xa9f700 sub_a9f700 size 0x106a
  0xaa4210 sub_aa4210 size 0x136b
  0xae4180 sub_ae4180 size 0xe51
  0xaf4760 sub_af4760 size 0x4009
  0xafafc0 sub_afafc0 size 0x889
  0xafd9e0 sub_afd9e0 size 0x2fda
  0xb0e130 sub_b0e130 size 0x2a68
  0xc13cd0 sub_c13cd0 size 0x26c
  0xc951b0 sub_c951b0 size 0x136
  0x1013730 sub_1013730 size 0x350b
  0x16859a0 sub_16859a0 size 0x1f1
  0x1685ca0 sub_1685ca0 size 0x2a0
  0x16860c0 sub_16860c0 size 0x287
  0x1691150 sub_1691150 size 0x39fa
  0x1695f50 sub_1695f50 size 0x6b
  0x1695fc0 sub_1695fc0 size 0x1ec4
  0x169ba20 sub_169ba20 size 0x837
  0x169ee90 sub_169ee90 size 0x480
  0x169f350 sub_169f350 size 0x190
  0x169fa90 sub_169fa90 size 0x54f
  0x16a2880 sub_16a2880 size 0x3d71
  0x16d5e30 sub_16d5e30 size 0xa8
  0x16d5fb0 sub_16d5fb0 size 0x63
  0x16d61b0 sub_16d61b0 size 0x185
  0x1821de0 sub_1821de0 size 0x1cf6
  0x18295f0 sub_18295f0 size 0x2580
  0x18559d0 sub_18559d0 size 0x5945
  0x1912220 sub_1912220 size 0x993
  0x1919160 sub_1919160 size 0x214
  0x1a55e60 sub_1a55e60 size 0x642
  0x1a72740 sub_1a72740 size 0x305
  0x1c638a0 sub_1c638a0 size 0x71e
  0x1c6cb80 sub_1c6cb80 size 0xe406
  0x1c7ecb0 sub_1c7ecb0 size 0x47ee
  0x1c8b320 sub_1c8b320 size 0xf76
  0x1c8cca0 sub_1c8cca0 size 0x1087
  0x1c8e260 sub_1c8e260 size 0x17e3
  0x1c96b40 sub_1c96b40 size 0x28fe
  0x1e64870 sub_1e64870 size 0x452
  0x1e91660 sub_1e91660 size 0x280
  0x1e9e980 sub_1e9e980 size 0x288
  0x2129350 sub_2129350 size 0x17cc
  0x2141950 sub_2141950 size 0x4817
  0x2170b50 sub_2170b50 size 0x16b
  0x2171030 sub_2171030 size 0x93e
  0x2171f20 sub_2171f20 size 0x460
  0x2172b70 sub_2172b70 size 0xd5
  0x2174020 sub_2174020 size 0xa7
  0x2175290 sub_2175290 size 0x147
  0x2322be0 sub_2322be0 size 0x111
  0x256c5d0 sub_256c5d0 size 0x590
  0x256cfd0 sub_256cfd0 size 0x346
  0x256f850 sub_256f850 size 0x7e4
  0x25708a0 sub_25708a0 size 0x19a6
  0x2958110 sub_2958110 size 0x612
  0x2959740 sub_2959740 size 0x3320
  0x2bc48e0 sub_2bc48e0 size 0x1c5
  0x2c421f0 sub_2c421f0 size 0x237
  0x2c49de0 sub_2c49de0 size 0x109
  0x2cb4140 sub_2cb4140 size 0x1ee
  0x2cb5300 sub_2cb5300 size 0x1dd
  0x2cb5960 sub_2cb5960 size 0x3e3
  0x2cb5ff0 sub_2cb5ff0 size 0x355
  0x2cb63f0 sub_2cb63f0 size 0x3e6
  0x2cb68e0 sub_2cb68e0 size 0x51b
  0x2cb70a0 sub_2cb70a0 size 0x12b
  0x2cb71f0 sub_2cb71f0 size 0x90
  0x2cb72a0 sub_2cb72a0 size 0x12b
  0x2cb73f0 sub_2cb73f0 size 0x257
  0x2cb8520 sub_2cb8520 size 0x103
  0x2cb8650 sub_2cb8650 size 0xe6
  0x2cb8760 sub_2cb8760 size 0xe4
  0x2cb8870 sub_2cb8870 size 0x139
  0x2cb89d0 sub_2cb89d0 size 0x195
  0x2cb9510 sub_2cb9510 size 0x141
  0x2cb9fc0 sub_2cb9fc0 size 0xec
  0x2cba0d0 sub_2cba0d0 size 0xf2
  0x2cba1f0 sub_2cba1f0 size 0x145
  0x2cba3e0 sub_2cba3e0 size 0x1c6
  0x2cbab90 sub_2cbab90 size 0x1fb
  0x2cbadb0 sub_2cbadb0 size 0x19a
  0x2cbaf70 sub_2cbaf70 size 0x198
  0x2cbb130 sub_2cbb130 size 0xcd
  0x2cbb250 sub_2cbb250 size 0x2b1
  0x2cbd830 sub_2cbd830 size 0x46f
  0x2cbdf60 sub_2cbdf60 size 0x3b0
  0x2cbe4d0 sub_2cbe4d0 size 0x334
  0x2cbe9d0 sub_2cbe9d0 size 0x4c7
  0x2cbf870 sub_2cbf870 size 0xc6
  0x2cbfb40 sub_2cbfb40 size 0x88
  0x2cc0420 sub_2cc0420 size 0x175
  0x2cc1360 sub_2cc1360 size 0x4cf
  0x2cc1bf0 sub_2cc1bf0 size 0x37a
  0x2cc1f90 sub_2cc1f90 size 0x350
  0x2cc37e0 sub_2cc37e0 size 0x185
  0x2cc3cd0 sub_2cc3cd0 size 0x2e2
  0x2cc4180 sub_2cc4180 size 0x2d5
  0x2cc4480 sub_2cc4480 size 0x2e7
  0x2cc4930 sub_2cc4930 size 0x1ec
  0x2cc4b40 sub_2cc4b40 size 0x1d5
  0x2cc4d40 sub_2cc4d40 size 0x313
  0x2cc5080 sub_2cc5080 size 0x32d
  0x2cc53d0 sub_2cc53d0 size 0x616
  0x2cc5f90 sub_2cc5f90 size 0x634
  0x2cc6b70 sub_2cc6b70 size 0x293
  0x2cc6fd0 sub_2cc6fd0 size 0x29d
  0x2cc7430 sub_2cc7430 size 0x287
  0x2cc76e0 sub_2cc76e0 size 0x298
  0x2cc79a0 sub_2cc79a0 size 0x278
  0x2cc88a0 sub_2cc88a0 size 0x12d
  0x2cc8ed0 sub_2cc8ed0 size 0x257
  0x2cc9240 sub_2cc9240 size 0x847
  0x2cca050 sub_2cca050 size 0x1dc
  0x2cca250 sub_2cca250 size 0x1aa
  0x2cca420 sub_2cca420 size 0x1aa
  0x2cca5f0 sub_2cca5f0 size 0x214
  0x2cca830 sub_2cca830 size 0x210
  0x2ccaa60 sub_2ccaa60 size 0x1c8
  0x2ccac50 sub_2ccac50 size 0x1b7
  0x2ccae60 sub_2ccae60 size 0x243
  0x2ccb110 sub_2ccb110 size 0x2d7
  0x2ccb480 sub_2ccb480 size 0x308
  0x2ccb830 sub_2ccb830 size 0x221
  0x2ccba80 sub_2ccba80 size 0x23b
  0x2ccbd30 sub_2ccbd30 size 0x1e4
  0x2ccbf80 sub_2ccbf80 size 0x28d
  0x2ccc2d0 sub_2ccc2d0 size 0x272
  0x2ccc610 sub_2ccc610 size 0x1d6
  0x2ccc890 sub_2ccc890 size 0x1fb
  0x2cccb40 sub_2cccb40 size 0x170
  0x2cccdf0 sub_2cccdf0 size 0x2f6
  0x2ccd480 sub_2ccd480 size 0x2c1
  0x2ccdae0 sub_2ccdae0 size 0x36c
  0x2cce5b0 sub_2cce5b0 size 0x122
  0x2d9f900 sub_2d9f900 size 0x5d10
  0x2ea71d0 sub_2ea71d0 size 0x11c
  0x2fb8960 sub_2fb8960 size 0x44c7
  0x31c7ca0 sub_31c7ca0 size 0x29e9
  0x31cb940 sub_31cb940 size 0x3a19
  0x31ea6a0 sub_31ea6a0 size 0x104
  0x31f02d0 sub_31f02d0 size 0x83f
  0x3283460 sub_3283460 size 0xa61
  0x32aae00 sub_32aae00 size 0x1ffb
  0x32e0e90 sub_32e0e90 size 0x281
  0x352bb60 sub_352bb60 size 0xbd8
  0x3536ec0 sub_3536ec0 size 0xc0e
  0x3537f60 sub_3537f60 size 0x10b
  0x3646b00 sub_3646b00 size 0x9fa
  0x36871c0 sub_36871c0 size 0x166d
  0x3689d30 sub_3689d30 size 0x47f7
  0x3690b90 sub_3690b90 size 0x16aa
  0x36cb2b0 sub_36cb2b0 size 0x15c
  0x36d7fe0 sub_36d7fe0 size 0x322f
  0x36dd520 sub_36dd520 size 0xe59e
  0x3795960 sub_3795960 size 0x53b
  0x37b6b40 sub_37b6b40 size 0x241
  0x37fdc50 sub_37fdc50 size 0x8f1
  0x37fe9c0 sub_37fe9c0 size 0x621
  0x38cc710 sub_38cc710 size 0x22d
  0x38debd0 sub_38debd0 size 0x5f8
  0x390d300 sub_390d300 size 0x15f
  0x39405c0 sub_39405c0 size 0x103d
  0x39c4b30 sub_39c4b30 size 0xc9
  0x39ef2b0 sub_39ef2b0 size 0x241
  0x39ef500 sub_39ef500 size 0x194
  0x3d1cf60 sub_3d1cf60 size 0x3b
  0x3eac320 sub_3eac320 size 0x11c
  0x3fc0cf0 sub_3fc0cf0 size 0x74
  0x483b040 sub_483b040 size 0xf05
  0x48f67d0 sub_48f67d0 size 0x222
  0x4acbcd0 sub_4acbcd0 size 0x142f
  0x4acd910 sub_4acd910 size 0x1721
  0x4acf600 sub_4acf600 size 0x12c2
  0x4d4d050 sub_4d4d050 size 0xa80
  0x4e31290 sub_4e31290 size 0x2cee
  0x4e36150 sub_4e36150 size 0x39d1
  0x554d1e0 sub_554d1e0 size 0x22e2
  0x55540e0 sub_55540e0 size 0x889
  0x5555660 sub_5555660 size 0xc4e
  0x55578a0 sub_55578a0 size 0xe2
  0x586f810 sub_586f810 size 0x9ba4
  0x58871b0 sub_58871b0 size 0x3b12
  0x5890a40 sub_5890a40 size 0x2b63
  0x58af6c0 sub_58af6c0 size 0x4798
  0x58b8280 sub_58b8280 size 0x1b5e
  0x594c5c0 sub_594c5c0 size 0x4fa
  0x5964880 sub_5964880 size 0x3138
  0x5a321f0 sub_5a321f0 size 0x3073
  0x5a386f0 sub_5a386f0 size 0x848
  0x5ba5c10 sub_5ba5c10 size 0x4900
  0x5babe80 sub_5babe80 size 0x1e32
  0x5bf8d10 sub_5bf8d10 size 0x25c3
  0x5c57570 sub_5c57570 size 0x487
  0x5c57bb0 sub_5c57bb0 size 0x2ca
  0x5c870b0 sub_5c870b0 size 0x3ca
  0x5cb9cb0 sub_5cb9cb0 size 0x22d
  0x5ced380 sub_5ced380 size 0x6cd
  0x5d45980 sub_5d45980 size 0x13b5
  0x5d6c320 sub_5d6c320 size 0xbd5
  0x5d727a0 sub_5d727a0 size 0xae1
  0x5d74730 sub_5d74730 size 0x13cb
  0x5d8c860 sub_5d8c860 size 0x65d
  0x5da7380 sub_5da7380 size 0x119a
  0x5da89a0 sub_5da89a0 size 0x3ed
  0x5e8e990 sub_5e8e990 size 0x34c
  0x5e8ed30 sub_5e8ed30 size 0x5c9
  0x5e90ba0 sub_5e90ba0 size 0x805
  0x5ed26a0 sub_5ed26a0 size 0x2be
  0x5ed6220 sub_5ed6220 size 0x29f
  0x5ed9bb0 sub_5ed9bb0 size 0x3a2
  0x5edb930 sub_5edb930 size 0x1eb
  0x5ee17a0 sub_5ee17a0 size 0x2e3
  0x5efa3a0 sub_5efa3a0 size 0x2b9
  0x5fe3b80 sub_5fe3b80 size 0x237
  0x5ff0720 sub_5ff0720 size 0x365
  0x6014530 sub_6014530 size 0x2ba
  0x60229a0 sub_60229a0 size 0x365
  0x602e8a0 sub_602e8a0 size 0x725
  0x6038e30 sub_6038e30 size 0x8f4
  0x6086550 sub_6086550 size 0x62c
  0x6097d50 sub_6097d50 size 0x2ea
  0x6173740 sub_6173740 size 0x69d
  0x61742d0 sub_61742d0 size 0x465
  0x6176c50 sub_6176c50 size 0xeb1
  0x617a100 sub_617a100 size 0x2567
  0x617f040 sub_617f040 size 0x2bf8
  0x652ed00 sub_652ed00 size 0x2717
  0x67f1380 sub_67f1380 size 0x322f
  0x68f14e0 sub_68f14e0 size 0xef3
  0x68f30a0 sub_68f30a0 size 0x2ec
  0x69034c0 sub_69034c0 size 0x628
  0x6904e30 sub_6904e30 size 0x61d
  0x69819b0 sub_69819b0 size 0x5f3
  0x698e4c0 sub_698e4c0 size 0x3c0
  0x698ff60 sub_698ff60 size 0xe96
  0x69d0b60 sub_69d0b60 size 0x25b6
  0x69e10d0 sub_69e10d0 size 0xc9
  0x69ee560 sub_69ee560 size 0x200
  0x69fb690 sub_69fb690 size 0x32f
  0x6a13420 sub_6a13420 size 0x4d5
  0x6a1e170 sub_6a1e170 size 0xde
  0x6a22990 sub_6a22990 size 0x12d
  0x6a23180 sub_6a23180 size 0x116
  0x6a24650 sub_6a24650 size 0xc7
  0x6abc640 sub_6abc640 size 0x5b
  0x6abc790 sub_6abc790 size 0x66
  0x6abc800 sub_6abc800 size 0x44
  0x6ac7750 sub_6ac7750 size 0x48e8
  0x6b1df40 sub_6b1df40 size 0x23cf
  0x6b23750 sub_6b23750 size 0x2d1
  0x6b2a2a0 sub_6b2a2a0 size 0x12f8
  0x6b4eb90 sub_6b4eb90 size 0x960
  0x6b58c10 sub_6b58c10 size 0x12ca
  0x6b5e950 sub_6b5e950 size 0x2d8
  0x6b5efe0 sub_6b5efe0 size 0x4d6
  0x6b5f740 sub_6b5f740 size 0x316
  0x6b61420 sub_6b61420 size 0x41d
  0x6b619c0 sub_6b619c0 size 0x133c
  0x6b63f70 sub_6b63f70 size 0x318
  0x6b64410 sub_6b64410 size 0x239
  0x6b648b0 sub_6b648b0 size 0x15a
  0x6b64b70 sub_6b64b70 size 0x175
  0x6b64d20 sub_6b64d20 size 0x15c
  0x6b64ff0 sub_6b64ff0 size 0x15c
  0x6b65270 sub_6b65270 size 0x1e2
  0x6b666b0 sub_6b666b0 size 0x6e1
  0x6b681e0 sub_6b681e0 size 0x3ca
  0x6b692c0 sub_6b692c0 size 0x6e5
  0x6b84e60 sub_6b84e60 size 0x1bf0
  0x6eae270 sub_6eae270 size 0x4c54
  0x6ebb510 sub_6ebb510 size 0x1010a
  0x6eedae0 sub_6eedae0 size 0xa59
  0x6eee750 sub_6eee750 size 0xb2c
  0x6f08450 sub_6f08450 size 0x32aa
  0x6f7cfe0 sub_6f7cfe0 size 0x2be
  0x6ff2960 sub_6ff2960 size 0x21be
  0x712bbb0 sub_712bbb0 size 0xe2f
  0x71ad4a0 sub_71ad4a0 size 0x115
  0x71add00 sub_71add00 size 0x110
  0x71af940 sub_71af940 size 0x114
  0x71afa60 sub_71afa60 size 0x44c
  0x71b07e0 sub_71b07e0 size 0x176
  0x71b0aa0 sub_71b0aa0 size 0x8b3
  0x71da6a0 sub_71da6a0 size 0x921
  0x729fc60 sub_729fc60 size 0x23e
  0x729ffd0 sub_729ffd0 size 0x312
  0x72a7490 sub_72a7490 size 0x62
  0x72a8c20 sub_72a8c20 size 0x29c
  0x72aa540 sub_72aa540 size 0x236
  0x72aff60 sub_72aff60 size 0x157
  0x72b7df0 sub_72b7df0 size 0x249
  0x72b89e0 sub_72b89e0 size 0x261
  0x72b8cf0 sub_72b8cf0 size 0x24c
  0x72bd2f0 sub_72bd2f0 size 0x2f1
  0x72bfd20 sub_72bfd20 size 0x25a
  0x72c0050 sub_72c0050 size 0x247
  0x72c0b90 sub_72c0b90 size 0x167
  0x72d8460 sub_72d8460 size 0x33f
  0x730a0d0 sub_730a0d0 size 0x294
  0x730f990 sub_730f990 size 0x4b
  0x73213e0 sub_73213e0 size 0x336
  0x73288a0 sub_73288a0 size 0x26a
  0x7328c60 sub_7328c60 size 0x319
  0x7347050 sub_7347050 size 0x324
  0x7362e60 sub_7362e60 size 0x312
  0x7369760 sub_7369760 size 0x32c
  0x7370860 sub_7370860 size 0x565
  0x7569210 sub_7569210 size 0x46b
  0x756b120 sub_756b120 size 0x449
  0x7574f00 sub_7574f00 size 0x43b
  0x7587980 sub_7587980 size 0x433
  0x75897b0 sub_75897b0 size 0x456
  0x758b600 sub_758b600 size 0x456
  0x758d500 sub_758d500 size 0x44e
  0x758f3a0 sub_758f3a0 size 0x44e
  0x75911e0 sub_75911e0 size 0x44e
  0x75930e0 sub_75930e0 size 0x465
  0x7594f70 sub_7594f70 size 0x45e
  0x7596e20 sub_7596e20 size 0x453
  0x7598c70 sub_7598c70 size 0x453
  0x759ab20 sub_759ab20 size 0x44e
  0x759c960 sub_759c960 size 0x453
  0x759e7b0 sub_759e7b0 size 0x44e
  0x75e2c90 sub_75e2c90 size 0x4aa
  0x75e51f0 sub_75e51f0 size 0x5a3
  0x75fe160 sub_75fe160 size 0x4d0
  0x760ced0 sub_760ced0 size 0x4a6
  0x7610500 sub_7610500 size 0x4bf
  0x7613be0 sub_7613be0 size 0x4ab
  0x76421a0 sub_76421a0 size 0x4c8
  0x777e640 sub_777e640 size 0xbdb
  0x7799f70 sub_7799f70 size 0x87e
  0x7a553e0 sub_7a553e0 size 0x12c
  0x7a68140 sub_7a68140 size 0x23e
  0x7aaa0b0 sub_7aaa0b0 size 0x331
  0x7ab7510 sub_7ab7510 size 0x340
  0x7bb6be0 sub_7bb6be0 size 0xb6
  0x7bb70a0 sub_7bb70a0 size 0x1c0
  0x7bba700 sub_7bba700 size 0x1d9
  0x7bbce50 sub_7bbce50 size 0x928
  0x7c0c310 sub_7c0c310 size 0x7da4
  0x7c23b50 sub_7c23b50 size 0x1a2
  0x7c255f0 sub_7c255f0 size 0x867
  0x7c27920 sub_7c27920 size 0x5c3
  0x7c66fe0 sub_7c66fe0 size 0x170
  0x7c69800 sub_7c69800 size 0x158
  0x84069d0 sub_84069d0 size 0x1455
  0x84573a0 sub_84573a0 size 0xe9f
  0x851a240 sub_851a240 size 0x13f5
  0x85ffea0 sub_85ffea0 size 0x104
  0x8ef2b00 sub_8ef2b00 size 0x13df
  0x8f670b0 sub_8f670b0 size 0x1cb
  0x990c0a0 sub_990c0a0 size 0x7f
  0x990c590 sub_990c590 size 0xaf
  0x9ac7f30 sub_9ac7f30 size 0x146
  0x9b8e750 sub_9b8e750 size 0x23b
  0x9b91fc0 sub_9b91fc0 size 0xcf4
  0x9b92e70 sub_9b92e70 size 0x17c
  0x9bc3da0 sub_9bc3da0 size 0x315
  0x9bc4820 sub_9bc4820 size 0x428
  0xa29d4e0 sub_a29d4e0 size 0x4e
  0xa29dd80 sub_a29dd80 size 0xdf
  0xa29e610 sub_a29e610 size 0x7a
  0xa2c6080 sub_a2c6080 size 0x302
  0xa2ca3e0 sub_a2ca3e0 size 0x73
  0xa2e33a0 sub_a2e33a0 size 0xc1
  0xa2e3d00 sub_a2e3d00 size 0x77
  0xa2e4250 sub_a2e4250 size 0x12c
  0xb3152c0 sub_b3152c0 size 0x1680
  0xba27340 sub_ba27340 size 0x26f
  0xba2a0a0 sub_ba2a0a0 size 0x46e
  0xbc466b0 sub_bc466b0 size 0xf23
  0xbc48a70 sub_bc48a70 size 0x405
  0xbc514e0 sub_bc514e0 size 0x11ee
  0xbf2f530 sub_bf2f530 size 0x5d5
  0xbf312b0 sub_bf312b0 size 0x56b
  0xbf320c0 sub_bf320c0 size 0x728
  0xbf349a0 sub_bf349a0 size 0x17dd
  0xbf39470 sub_bf39470 size 0x756
  0xbf39dd0 sub_bf39dd0 size 0x6bb
  0xbf3b420 sub_bf3b420 size 0x313
  0xbf3bd20 sub_bf3bd20 size 0x28b
  0xbf3c680 sub_bf3c680 size 0x25d
  0xbf3d630 sub_bf3d630 size 0x41d
  0xbf3dbd0 sub_bf3dbd0 size 0x391
  0xbf3e820 sub_bf3e820 size 0x29a
  0xbf3fa60 sub_bf3fa60 size 0x571
  0xbf429b0 sub_bf429b0 size 0x5f7
  0xbf43900 sub_bf43900 size 0x31e
  0xbf448b0 sub_bf448b0 size 0x12e0
  0xd1ded40 sub_d1ded40 size 0xf7b
  0xd1f81a0 sub_d1f81a0 size 0x67
  0xd3059e0 sub_d3059e0 size 0xc33
  0xd310850 sub_d310850 size 0x1787
  0xd343e10 sub_d343e10 size 0xa9b
  0xd3994c0 sub_d3994c0 size 0x3dd
  0xd3cebe0 sub_d3cebe0 size 0x17e
  0xd3ede70 sub_d3ede70 size 0x2f0
  0xd404230 sub_d404230 size 0x11e
  0xd404350 sub_d404350 size 0x11f
  0xd459ba0 sub_d459ba0 size 0x149
  0xe2fb720 sub_e2fb720 size 0x1adf
  -- 444 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0x3b2020    sub_3b2020        set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_3b2020.cpp;src\client\features\render\native\helpers\sub_3b2020.h
  0x3d0730    sub_3d0730        unknown     [open]     [proven]  unresolved
  0xe943178   sub_e943178       unknown     [open]     [proven]  unresolved
  0xe94319c   sub_e94319c       unknown     [open]     [proven]  unresolved

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
  - UNRESOLVED CALL: The following call targets of 0x3b2020 are in NEITHER docs/data/native_functions.tsv NOR docs/data/native_boundary.tsv (and not in Sigs.json), so they are blockers per the hard rules: the calls are quoted verbatim but not translated into C++, and no wrapper was invented. (from docs\progress\oc_U-EX7.3b2020_r1.md)
  - UNRESOLVED CALL: 0x3b2020 calls 0xE943170 (0x3b2056), 0xE943194 (0x3b206d) and 0xEEC5B90 (0x3b2092); none are in native_functions.tsv or native_boundary.tsv, so the calls cannot be translated (no wrappers invented) per the hard rules. (from docs\progress\oc_U-EX7.3b2020_r1.md)

## DECISIONS
  - D-rank not derivable from static data; needs a model/orchestrator decision [open]
  - description register for descscan2 unknown; tried rdi,rsi,r9,r15, result best-effort [open]
  - callee signatures not available (no Sigs.json); each callee ABI/signature is [open]
  - field offsets above are [derived] from descscan2; struct/meaning is [open]
  - 'closest finished lift' size-band match is [derived], not verified as same call shape [open]

