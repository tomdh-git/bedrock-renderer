# ctxpack build 0xbc70ff0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=bc70ff0.md:e96863c7e23291cb306bb3a43364acedba1cba3a7b84d5c8172de08afbf2e393,liftsrc=sub_bc70ff0.cpp:dfa38f3de35c6ce2bf734fb23b25ca7f4c49d6204006d19dd6061dc02ac0420c,liftsrc=sub_bc70ff0.h:66db4cba15904ecd9c9a39fa62b922afabc83f222ac6091a988da982e2416860,data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb

## HEADER
  rva        : 0xbc70ff0
  size       : 0xf1 (241 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 3 (direct), depth 1
  callers    : 6

## EXACT LISTING (0xbc70ff0..0xbc710e1)
```
sub_bc70ff0  [0xbc70ff0..0xbc72ff0)  size 0x2000  8 xrefs in
  bc70ff0  push rbp                                      
  bc70ff1  push rsi                                      
  bc70ff2  push rdi                                      
  bc70ff3  sub rsp,0x40                                  
  bc70ff7  lea rbp,[rsp+0x40]                            
  bc70ffc  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE      
  bc71004  mov rsi,rcx                                   
  bc71007  mov [rbp-0xC],dx                              
  bc7100b  mov [rbp-0x20],r9                             
  bc7100f  mov [rbp-0x10],r8d                            
  bc71013  add rcx,0x1C0                                 
  bc7101a  mov [rbp-0x18],rcx                            
  bc7101e  call 0xEBDBF10                                ; -> sub_ebdbf10
  bc71023  mov rdi,[rsi+0x1CFD0C8]                       ; R a0+0x1CFD0C8
  bc7102a  mov byte ptr [rbp-9],0x13                     
  bc7102e  mov eax,[rdi+0xDC5818]                        ; R *(a0+0x1CFD0C8)+0xDC5818
  bc71034  lea rcx,[rdi+rax]                             ; R *(a0+0x1CFD0C8)+0x0+idx
  bc71038  add rcx,0xDC5820                              
  bc7103f  lea rdx,[rbp-9]                               
  bc71043  mov r8d,1                                     
  bc71049  call 0xEBCE390                                ; -> sub_ebce390
  bc7104e  nop                                           
  bc7104f  lea rsi,[rdi+0xDC5820]                        ; R *(a0+0x1CFD0C8)+0xDC5820
  bc71056  mov ecx,[rdi+0xDC5818]                        ; R *(a0+0x1CFD0C8)+0xDC5818
  bc7105c  and ecx,0xFFFFFFFE                            
  bc7105f  add ecx,2                                     
  bc71062  mov [rdi+0xDC5818],ecx                        ; W *(a0+0x1CFD0C8)+0xDC5818
  bc71068  add rcx,rsi                                   
  bc7106b  lea rdx,[rbp-0xC]                             
  bc7106f  mov r8d,2                                     
  bc71075  call 0xEBCE390                                ; -> sub_ebce390
  bc7107a  nop                                           
  bc7107b  mov ecx,[rdi+0xDC5818]                        ; R *(a0+0x1CFD0C8)+0xDC5818
  bc71081  add ecx,5                                     
  bc71084  and ecx,0xFFFFFFFC                            
  bc71087  mov [rdi+0xDC5818],ecx                        ; W *(a0+0x1CFD0C8)+0xDC5818
  bc7108d  add rcx,rsi                                   
  bc71090  lea rdx,[rbp-0x10]                            
  bc71094  mov r8d,4                                     
  bc7109a  call 0xEBCE390                                ; -> sub_ebce390
  bc7109f  nop                                           
  bc710a0  mov eax,[rdi+0xDC5818]                        ; R *(a0+0x1CFD0C8)+0xDC5818
  bc710a6  add eax,0xB                                   
  bc710a9  and eax,0xFFFFFFF8                            
  bc710ac  mov [rdi+0xDC5818],eax                        ; W *(a0+0x1CFD0C8)+0xDC5818
  bc710b2  add rsi,rax                                   
  bc710b5  lea rdx,[rbp-0x20]                            
  bc710b9  mov r8d,8                                     
  bc710bf  mov rcx,rsi                                   
  bc710c2  call 0xEBCE390                                ; -> sub_ebce390
  bc710c7  nop                                           
  bc710c8  add dword ptr [rdi+0xDC5818],8                ; W *(a0+0x1CFD0C8)+0xDC5818
  bc710cf  mov rcx,[rbp-0x18]                            
  bc710d3  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc710d8  nop                                           
  bc710d9  add rsp,0x40                                  
  bc710dd  pop rdi                                       
  bc710de  pop rsi                                       
  bc710df  pop rbp                                       
  bc710e0  ret                                           
  bc710e1  nop [rax+rax]                                 ; R ret@ebdbf20+0x0+idx
  bc710f0  mov [rsp+0x10],rdx                            
  bc710f5  push rbp                                      
  bc710f6  push rsi                                      
  bc710f7  push rdi                                      
  bc710f8  sub rsp,0x20                                  
  bc710fc  lea rbp,[rdx+0x40]                            
  bc71100  mov rcx,[rbp-0x18]                            
  bc71104  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc71109  nop                                           
  bc7110a  add rsp,0x20                                  
  bc7110e  pop rdi                                       
  bc7110f  pop rsi                                       
  bc71110  pop rbp                                       
  bc71111  ret                                           
  bc71112  nop [rax+rax]                                 ; R ret@ebdbf20+0x0+idx
  bc71120  mov [rsp+0x10],rdx                            
  bc71125  push rbp                                      
  bc71126  push rsi                                      
  bc71127  push rdi                                      
  bc71128  sub rsp,0x20                                  
  bc7112c  lea rbp,[rdx+0x40]                            
  bc71130  call 0xEEC6E40                                ; -> sub_eec6e40
  bc71135  int3                                          
  bc71136  int3                                          
  bc71137  int3                                          
  bc71138  int3                                          
  bc71139  int3                                          
  bc7113a  int3                                          
  bc7113b  int3                                          
  bc7113c  int3                                          
  bc7113d  int3                                          
  bc7113e  int3                                          
  bc7113f  int3                                          
  bc71140  push rbp                                      
  bc71141  push r15                                      
  bc71143  push r14                                      
  bc71145  push r13                                      
  bc71147  push r12                                      
  bc71149  push rsi                                      
  bc7114a  push rdi                                      
  bc7114b  push rbx                                      
  bc7114c  sub rsp,0x48                                  
  bc71150  lea rbp,[rsp+0x40]                            
  bc71155  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE        
  bc7115d  mov rsi,r8                                    
  bc71160  mov ebx,edx                                   
  bc71162  mov rdi,rcx                                   
  bc71165  add rcx,0x1C0                                 
  bc7116c  mov [rbp-0x10],rcx                            
  bc71170  call 0xEBDBF10                                ; -> sub_ebdbf10
  bc71175  movzx eax,bx                                  
  bc71178  lea rax,[rax+rax*4]                           
  bc7117c  lea r13,[rdi+rax*8]                           
  bc71180  add r13,0x1E7DAD8                             
  bc71187  cmp dword ptr [rdi+rax*8+0x1E7DAE0],0         
  bc7118f  je short 0xBC711DD                            ; -> loc_bc711dd
  bc71191  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc71198  test rcx,rcx                                  
  bc7119b  je short 0xBC711CA                            ; -> loc_bc711ca
  bc7119d  mov rdx,[r13]                                 
  bc711a1  mov rax,[rcx]                                 
  bc711a4  mov rax,[rax+8]                               
  bc711a8  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc711af  mov dword ptr [rsp+0x28],0                    
  bc711b7  mov qword ptr [rsp+0x20],0                    
  bc711c0  xor r8d,r8d                                   
  bc711c3  xor r9d,r9d                                   
  bc711c6  call r10                                      
  bc711c9  nop                                           

loc_bc711ca:  ; from bc7119b
  bc711ca  lea rax,[0xF847A07]                           ; [data_f847a07]
  bc711d1  mov [r13],rax                                 
  bc711d5  mov dword ptr [r13+8],0                       

loc_bc711dd:  ; from bc7118f
  bc711dd  cmp dword ptr [rsi+8],0                       
  bc711e1  je 0xBC7126A                                  ; -> loc_bc7126a
  bc711e7  mov rcx,rsi                                   
  bc711ea  mov edx,0x7FFFFFFF                            
  bc711ef  call 0xEBCE610                                ; -> sub_ebce610
  bc711f4  nop                                           
  bc711f5  mov r14d,eax                                  
  bc711f8  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc711ff  test rcx,rcx                                  
  bc71202  je short 0xBC71246                            ; -> loc_bc71246
  bc71204  cmp dword ptr [r13+8],0                       
  bc71209  mov edx,0                                     
  bc7120e  je short 0xBC71214                            ; -> loc_bc71214
  bc71210  mov rdx,[r13]                                 

loc_bc71214:  ; from bc7120e
  bc71214  lea r15d,[r14+1]                              ; R ret@ebce610+0x1
  bc71218  movsxd r8,r15d                                
  bc7121b  mov rax,[rcx]                                 
  bc7121e  mov rax,[rax+8]                               
  bc71222  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc71229  mov dword ptr [rsp+0x28],0                    
  bc71231  mov qword ptr [rsp+0x20],0                    
  bc7123a  xor r9d,r9d                                   
  bc7123d  call r10                                      
  bc71240  nop                                           
  bc71241  mov r12,rax                                   
  bc71244  jmp short 0xBC7124D                           ; -> loc_bc7124d

loc_bc71246:  ; from bc71202
  bc71246  lea r15d,[r14+1]                              
  bc7124a  xor r12d,r12d                                 

loc_bc7124d:  ; from bc71244
  bc7124d  mov [r13+8],r14d                              
  bc71251  mov rcx,r12                                   
  bc71254  mov edx,r15d                                  
  bc71257  mov r8,rsi                                    
  bc7125a  mov r9d,0x7FFFFFFF                            
  bc71260  call 0xEBCE650                                ; -> sub_ebce650
  bc71265  nop                                           
  bc71266  mov [r13],r12                                 

loc_bc7126a:  ; from bc711e1
  bc7126a  shl ebx,0x10                                  
  bc7126d  or ebx,2                                      
  bc71270  mov [rbp-8],ebx                               
  bc71273  mov r14,[rdi+0x1CFD0C8]                       
  bc7127a  mov byte ptr [rbp-2],0x18                     
  bc7127e  mov eax,[r14+0xDC5818]                        
  bc71285  lea rcx,[r14+rax+0xDC5820]                    
  bc7128d  lea rdx,[rbp-2]                               
  bc71291  mov r8d,1                                     
  bc71297  call 0xEBCE390                                ; -> sub_ebce390
  bc7129c  nop                                           
  bc7129d  lea rdi,[r14+0xDC5820]                        
  bc712a4  mov ecx,[r14+0xDC5818]                        
  bc712ab  and ecx,0xFFFFFFFE                            
  bc712ae  add ecx,2                                     
  bc712b1  mov [r14+0xDC5818],ecx                        
  bc712b8  add rcx,rdi                                   
  bc712bb  lea rdx,[rbp-8]                               
  bc712bf  mov r8d,4                                     
  bc712c5  call 0xEBCE390                                ; -> sub_ebce390
  bc712ca  nop                                           
  bc712cb  mov ecx,[r14+0xDC5818]                        
  bc712d2  lea eax,[rcx+4]                               
  bc712d5  mov [r14+0xDC5818],eax                        
  bc712dc  mov eax,[rsi+8]                               
  bc712df  inc eax                                       
  bc712e1  mov [rbp-4],ax                                
  bc712e5  add ecx,5                                     
  bc712e8  and ecx,0xFFFFFFFE                            
  bc712eb  mov [r14+0xDC5818],ecx                        
  bc712f2  add rcx,rdi                                   
  bc712f5  lea rdx,[rbp-4]                               
  bc712f9  mov r8d,2                                     
  bc712ff  call 0xEBCE390                                ; -> sub_ebce390
  bc71304  nop                                           
  bc71305  mov ecx,[r14+0xDC5818]                        
  bc7130c  add ecx,2                                     
  bc7130f  mov [r14+0xDC5818],ecx                        
  bc71316  movzx ebx,word ptr [rbp-4]                    
  bc7131a  dec ebx                                       
  bc7131c  mov rdx,[rsi]                                 
  bc7131f  add rcx,rdi                                   
  bc71322  mov r8,rbx                                    
  bc71325  call 0xEBCE390                                ; -> sub_ebce390
  bc7132a  nop                                           
  bc7132b  add ebx,[r14+0xDC5818]                        
  bc71332  mov [r14+0xDC5818],ebx                        
  bc71339  mov byte ptr [rbp-1],0                        
  bc7133d  add rdi,rbx                                   
  bc71340  lea rdx,[rbp-1]                               
  bc71344  mov r8d,1                                     
  bc7134a  mov rcx,rdi                                   
  bc7134d  call 0xEBCE390                                ; -> sub_ebce390
  bc71352  nop                                           
  bc71353  inc dword ptr [r14+0xDC5818]                  
  bc7135a  mov rcx,[rbp-0x10]                            
  bc7135e  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc71363  nop                                           
  bc71364  add rsp,0x48                                  
  bc71368  pop rbx                                       
  bc71369  pop rdi                                       
  bc7136a  pop rsi                                       
  bc7136b  pop r12                                       
  bc7136d  pop r13                                       
  bc7136f  pop r14                                       
  bc71371  pop r15                                       
  bc71373  pop rbp                                       
  bc71374  ret                                           
  bc71375  nop [rax+rax]                                 ; R ret@ebdbf20+0x0+idx
  bc71380  mov [rsp+0x10],rdx                            
  bc71385  push rbp                                      
  bc71386  push r15                                      
  bc71388  push r14                                      
  bc7138a  push r13                                      
  bc7138c  push r12                                      
  bc7138e  push rsi                                      
  bc7138f  push rdi                                      
  bc71390  push rbx                                      
  bc71391  sub rsp,0x38                                  
  bc71395  lea rbp,[rdx+0x40]                            
  bc71399  mov rcx,[rbp-0x10]                            
  bc7139d  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc713a2  nop                                           
  bc713a3  add rsp,0x38                                  
  bc713a7  pop rbx                                       
  bc713a8  pop rdi                                       
  bc713a9  pop rsi                                       
  bc713aa  pop r12                                       
  bc713ac  pop r13                                       
  bc713ae  pop r14                                       
  bc713b0  pop r15                                       
  bc713b2  pop rbp                                       
  bc713b3  ret                                           
  bc713b4  nop [rax+rax]                                 ; R ret@ebdbf20+0x0+idx
  bc713c0  mov [rsp+0x10],rdx                            
  bc713c5  push rbp                                      
  bc713c6  push r15                                      
  bc713c8  push r14                                      
  bc713ca  push r13                                      
  bc713cc  push r12                                      
  bc713ce  push rsi                                      
  bc713cf  push rdi                                      
  bc713d0  push rbx                                      
  bc713d1  sub rsp,0x38                                  
  bc713d5  lea rbp,[rdx+0x40]                            
  bc713d9  call 0xEEC6E40                                ; -> sub_eec6e40
  bc713de  int3                                          
  bc713df  int3                                          
  bc713e0  push rbp                                      
  bc713e1  push r15                                      
  bc713e3  push r14                                      
  bc713e5  push r13                                      
  bc713e7  push r12                                      
  bc713e9  push rsi                                      
  bc713ea  push rdi                                      
  bc713eb  push rbx                                      
  bc713ec  sub rsp,0x78                                  
  bc713f0  lea rbp,[rsp+0x70]                            
  bc713f5  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE        
  bc713fd  mov edi,r9d                                   
  bc71400  mov esi,edx                                   
  bc71402  mov r14,[rbp+0x88]                            
  bc71409  movzx r11d,word ptr [rbp+0x70]                
  bc7140e  mov rax,[0x12AE1748]                          ; [data_12ae1748]
  bc71415  movzx ecx,cx                                  
  bc71418  lea rdx,[rcx+rcx*8]                           
  bc7141c  lea rdx,[rdx+rdx*2]                           
  bc71420  add rdx,rcx                                   
  bc71423  lea r12,[rax+rdx]                             
  bc71427  add r12,0x1DBD0C8                             
  bc7142e  movzx ecx,r8w                                 
  bc71432  lea rdx,[rcx+rcx*8]                           
  bc71436  lea rdx,[rdx+rdx*2]                           
  bc7143a  add rdx,rcx                                   
  bc7143d  lea r13,[rax+rdx]                             
  bc71441  add r13,0x1DBD0C8                             
  bc71448  mov rbx,[rax+0x1EBF2D0]                       
  bc7144f  lea r15,[0xF847A07]                           ; [data_f847a07]
  bc71456  mov [rbp-0x28],r15                            
  bc7145a  mov dword ptr [rbp-0x20],0                    
  bc71461  test r14,r14                                  
  bc71464  je short 0xBC714CF                            ; -> loc_bc714cf
  bc71466  mov rcx,r14                                   
  bc71469  mov edx,0x7FFFFFFF                            
  bc7146e  call 0xEBCE5E0                                ; -> sub_ebce5e0
  bc71473  test eax,eax                                  
  bc71475  je short 0xBC714DC                            ; -> loc_bc714dc
  bc71477  mov [rbp-0x20],eax                            
  bc7147a  mov [rbp-0x28],r14                            
  bc7147e  lea rcx,[rbp-0x28]                            
  bc71482  mov edx,0x7FFFFFFF                            
  bc71487  call 0xEBCE610                                ; -> sub_ebce610
  bc7148c  mov r14d,eax                                  
  bc7148f  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc71496  inc r14d                                      
  bc71499  test rcx,rcx                                  
  bc7149c  je short 0xBC714E9                            ; -> loc_bc714e9
  bc7149e  movsxd r8,r14d                                
  bc714a1  mov [rbp-0x14],eax                            
  bc714a4  mov rax,[rcx]                                 
  bc714a7  mov rax,[rax+8]                               
  bc714ab  mov dword ptr [rsp+0x28],0                    
  bc714b3  mov qword ptr [rsp+0x20],0                    
  bc714bc  xor edx,edx                                   
  bc714be  xor r9d,r9d                                   
  bc714c1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc714c7  mov r15,rax                                   
  bc714ca  mov eax,[rbp-0x14]                            
  bc714cd  jmp short 0xBC714EC                           ; -> loc_bc714ec

loc_bc714cf:  ; from bc71464
  bc714cf  mov [rbp-0x10],r15                            
  bc714d3  mov dword ptr [rbp-8],0                       
  bc714da  jmp short 0xBC7150D                           ; -> loc_bc7150d

loc_bc714dc:  ; from bc71475
  bc714dc  mov [rbp-0x10],r15                            
  bc714e0  mov dword ptr [rbp-8],0                       
  bc714e7  jmp short 0xBC71508                           ; -> loc_bc71508

loc_bc714e9:  ; from bc7149c
  bc714e9  xor r15d,r15d                                 

loc_bc714ec:  ; from bc714cd
  bc714ec  mov [rbp-8],eax                               
  bc714ef  lea r8,[rbp-0x28]                             
  bc714f3  mov rcx,r15                                   
  bc714f6  mov edx,r14d                                  
  bc714f9  mov r9d,0x7FFFFFFF                            
  bc714ff  call 0xEBCE650                                ; -> sub_ebce650
  bc71504  mov [rbp-0x10],r15                            

loc_bc71508:  ; from bc714e7
  bc71508  movzx r11d,word ptr [rbp+0x70]                

loc_bc7150d:  ; from bc714da
  bc7150d  movzx r9d,word ptr [r13]                      
  bc71512  movzx edx,word ptr [r12]                      
  bc71517  mov rax,[rbx]                                 
  bc7151a  mov rax,[rax+0x1B0]                           
  bc71521  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc71528  lea rcx,[rbp-0x10]                            
  bc7152c  mov [rsp+0x40],rcx                            
  bc71531  mov rcx,[rbp+0x80]                            
  bc71538  mov [rsp+0x38],rcx                            
  bc7153d  mov ecx,[rbp+0x78]                            
  bc71540  mov [rsp+0x30],ecx                            
  bc71544  mov [rsp+0x28],r11w                           
  bc7154a  mov [rsp+0x20],edi                            
  bc7154e  mov rcx,rbx                                   
  bc71551  mov r8d,esi                                   
  bc71554  call r10                                      
  bc71557  nop                                           
  bc71558  cmp dword ptr [rbp-8],0                       
  bc7155c  je short 0xBC7159E                            ; -> loc_bc7159e
  bc7155e  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc71565  test rcx,rcx                                  
  bc71568  je short 0xBC71597                            ; -> loc_bc71597
  bc7156a  mov rdx,[rbp-0x10]                            
  bc7156e  mov rax,[rcx]                                 
  bc71571  mov rax,[rax+8]                               
  bc71575  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc7157c  mov dword ptr [rsp+0x28],0                    
  bc71584  mov qword ptr [rsp+0x20],0                    
  bc7158d  xor r8d,r8d                                   
  bc71590  xor r9d,r9d                                   
  bc71593  call r10                                      
  bc71596  nop                                           

loc_bc71597:  ; from bc71568
  bc71597  mov dword ptr [rbp-8],0                       

loc_bc7159e:  ; from bc7155c
  bc7159e  add rsp,0x78                                  
  bc715a2  pop rbx                                       
  bc715a3  pop rdi                                       
  bc715a4  pop rsi                                       
  bc715a5  pop r12                                       
  bc715a7  pop r13                                       
  bc715a9  pop r14                                       
  bc715ab  pop r15                                       
  bc715ad  pop rbp                                       
  bc715ae  ret                                           
  bc715af  nop                                           
  bc715b0  mov [rsp+0x10],rdx                            
  bc715b5  push rbp                                      
  bc715b6  push r15                                      
  ... (--max 400)
```

## CALLERS
```
  0x8b9e5f0 sub_8b9e5f0 size 0x2bf
  0x8b9e9e0 sub_8b9e9e0 size 0x2c6
  0x8b9ef00 sub_8b9ef00 size 0x12c
  0xbc5bad0 sub_bc5bad0 size 0x19d1
  0xbc70ea0 sub_bc70ea0 size 0xf2
  0xbcc23a0 sub_bcc23a0 size 0x149
  -- 6 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0xebce390   sub_ebce390       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_ebce390.cpp;src\client\features\render\native\helpers\sub_ebce390.h
  0xebdbf10   sub_ebdbf10       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_ebdbf10.cpp;src\client\features\render\native\helpers\sub_ebdbf10.h
  0xebdbf20   sub_ebdbf20       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_ebdbf20.cpp;src\client\features\render\native\helpers\sub_ebdbf20.h

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

