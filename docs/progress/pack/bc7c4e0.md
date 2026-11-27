# ctxpack build 0xbc7c4e0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=bc7c4e0.md:3798e4fa0b71af5ef1ddc08c164fe38314707d1837e0847b8a1009505fa7478e,liftsrc=sub_bc7c4e0.cpp:df45c3f49200fb8298eef2f9f72196210e44bd7d422788d6a7843ca065746334,liftsrc=sub_bc7c4e0.h:a6a1655c78a0126999e02fea970e8690e72f3e489cf260691b964597273131cc,data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb

## HEADER
  rva        : 0xbc7c4e0
  size       : 0x95 (149 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 0 (direct), depth 1
  callers    : 1

## EXACT LISTING (0xbc7c4e0..0xbc7c575)
```
sub_bc7c4e0  [0xbc7c4e0..0xbc7e4e0)  size 0x2000  1 xrefs in
  bc7c4e0  push rsi                                      
  bc7c4e1  push rdi                                      
  bc7c4e2  sub rsp,0x28                                  
  bc7c4e6  movzx eax,byte ptr [rcx+0x10]                 ; R a0+0x10
  bc7c4ea  cmp al,[rdx+0x10]                             ; R a1+0x10
  bc7c4ed  jne short 0xBC7C4FE                           ; -> loc_bc7c4fe
  bc7c4ef  test al,al                                    
  bc7c4f1  je short 0xBC7C56E                            ; -> loc_bc7c56e
  bc7c4f3  add rsp,0x28                                  
  bc7c4f7  pop rdi                                       
  bc7c4f8  pop rsi                                       
  bc7c4f9  jmp 0xBC55EA0                                 ; -> sub_bc55ea0

loc_bc7c4fe:  ; from bc7c4ed
  bc7c4fe  test al,al                                    
  bc7c500  mov rdi,rdx                                   
  bc7c503  cmovne rdi,rcx                                
  bc7c507  cmovne rcx,rdx                                
  bc7c50b  xorps xmm0,xmm0                               
  bc7c50e  movups [rcx],xmm0                             
  bc7c511  mov rax,[rdi+8]                               
  bc7c515  test rax,rax                                  
  bc7c518  je short 0xBC7C51E                            ; -> loc_bc7c51e
  bc7c51a  lock inc dword ptr [rax+8]                    

loc_bc7c51e:  ; from bc7c518
  bc7c51e  mov rax,[rdi]                                 
  bc7c521  mov [rcx],rax                                 
  bc7c524  mov rax,[rdi+8]                               
  bc7c528  mov [rcx+8],rax                               
  bc7c52c  mov byte ptr [rcx+0x10],1                     
  bc7c530  cmp byte ptr [rdi+0x10],1                     
  bc7c534  jne short 0xBC7C56E                           ; -> loc_bc7c56e
  bc7c536  mov rsi,[rdi+8]                               
  bc7c53a  test rsi,rsi                                  
  bc7c53d  je short 0xBC7C56A                            ; -> loc_bc7c56a
  bc7c53f  lock dec dword ptr [rsi+8]                    
  bc7c543  jne short 0xBC7C56A                           ; -> loc_bc7c56a
  bc7c545  mov rax,[rsi]                                 
  bc7c548  mov rax,[rax]                                 
  bc7c54b  mov rcx,rsi                                   
  bc7c54e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7c554  lock dec dword ptr [rsi+0xC]                  
  bc7c558  jne short 0xBC7C56A                           ; -> loc_bc7c56a
  bc7c55a  mov rax,[rsi]                                 
  bc7c55d  mov rax,[rax+8]                               
  bc7c561  mov rcx,rsi                                   
  bc7c564  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc7c56a:  ; from bc7c53d, bc7c543, bc7c558
  bc7c56a  mov byte ptr [rdi+0x10],0                     

loc_bc7c56e:  ; from bc7c4f1, bc7c534
  bc7c56e  add rsp,0x28                                  
  bc7c572  pop rdi                                       
  bc7c573  pop rsi                                       
  bc7c574  ret                                           
  bc7c575  int3                                          
  bc7c576  int3                                          
  bc7c577  int3                                          
  bc7c578  int3                                          
  bc7c579  int3                                          
  bc7c57a  int3                                          
  bc7c57b  int3                                          
  bc7c57c  int3                                          
  bc7c57d  int3                                          
  bc7c57e  int3                                          
  bc7c57f  int3                                          
  bc7c580  push rbp                                      
  bc7c581  push r15                                      
  bc7c583  push r14                                      
  bc7c585  push r13                                      
  bc7c587  push r12                                      
  bc7c589  push rsi                                      
  bc7c58a  push rdi                                      
  bc7c58b  push rbx                                      
  bc7c58c  sub rsp,0x478                                 
  bc7c593  lea rbp,[rsp+0x80]                            
  bc7c59b  movaps [rbp+0x3E0],xmm6                       
  bc7c5a2  mov qword ptr [rbp+0x3D8],0xFFFFFFFFFFFFFFFE  
  bc7c5ad  mov rdi,r9                                    
  bc7c5b0  mov rbx,r8                                    
  bc7c5b3  mov r14,rdx                                   
  bc7c5b6  mov [rbp+0x3C8],rcx                           
  bc7c5bd  mov eax,[0x12AE1778]                          ; [data_12ae1778]
  bc7c5c3  mov ecx,[0x128767C8]                          ; [data_128767c8]
  bc7c5c9  mov rdx,gs:[0x58]                             
  bc7c5d2  mov rcx,[rdx+rcx*8]                           
  bc7c5d6  cmp eax,[rcx+4]                               
  bc7c5dc  jg 0xBC7D4D4                                  ; -> loc_bc7d4d4

loc_bc7c5e2:  ; from bc7d4e7, bc7d531
  bc7c5e2  xorps xmm0,xmm0                               
  bc7c5e5  movaps [rbp+0xB0],xmm0                        
  bc7c5ec  lea rax,[0xF5B4987]                           ; [data_f5b4987] "VolumeScattering"
  bc7c5f3  mov [rbp-0x10],rax                            
  bc7c5f7  mov qword ptr [rbp-8],0x10                    
  bc7c5ff  lea rax,[rbp+0xB0]                            
  bc7c606  mov [rsp+0x28],rax                            
  bc7c60b  lea rax,[rbp-0x10]                            
  bc7c60f  mov [rsp+0x20],rax                            
  bc7c614  lea r8,[0x12AE1768]                           ; [data_12ae1768]
  bc7c61b  lea rdx,[rbp+0x370]                           
  bc7c622  mov rcx,r14                                   
  bc7c625  mov r9,rbx                                    
  bc7c628  call 0x567C8B0                                ; -> sub_567c8b0
  bc7c62d  movzx eax,word ptr [0x128C1A5A]               ; [data_128c1a5a]
  bc7c634  mov [rbp+0x3B8],ax                            
  bc7c63b  mov eax,[0x12AE1788]                          ; [data_12ae1788]
  bc7c641  mov ecx,[0x128767C8]                          ; [data_128767c8]
  bc7c647  mov rdx,gs:[0x58]                             
  bc7c650  mov rcx,[rdx+rcx*8]                           
  bc7c654  cmp eax,[rcx+4]                               
  bc7c65a  jg 0xBC7D536                                  ; -> loc_bc7d536

loc_bc7c660:  ; from bc7d549, bc7d6fc
  bc7c660  mov r14,[rbp+0x468]                           
  bc7c667  mov rax,[0x12AE1780]                          ; [data_12ae1780]
  bc7c66e  mov [rbp+0x3B0],rax                           
  bc7c675  mov rax,[r14+0x18]                            
  bc7c679  mov [rbp+0x3C0],rax                           
  bc7c680  mov eax,[0x12AE1798]                          ; [data_12ae1798]
  bc7c686  mov ecx,[0x128767C8]                          ; [data_128767c8]
  bc7c68c  mov rdx,gs:[0x58]                             
  bc7c695  mov rcx,[rdx+rcx*8]                           
  bc7c699  cmp eax,[rcx+4]                               
  bc7c69f  jg 0xBC7D5A8                                  ; -> loc_bc7d5a8

loc_bc7c6a5:  ; from bc7d5bb, bc7d792
  bc7c6a5  mov rax,[rbp+0x460]                           
  bc7c6ac  mov rsi,[0x12AE1790]                          ; [data_12ae1790]
  bc7c6b3  mov r14,[r14+0x18]                            
  bc7c6b7  mov rcx,[rbp+0x378]                           
  bc7c6be  test rcx,rcx                                  
  bc7c6c1  je short 0xBC7C6D0                            ; -> loc_bc7c6d0
  bc7c6c3  lock inc dword ptr [rcx+8]                    
  bc7c6c7  mov rdx,[rbp+0x378]                           
  bc7c6ce  jmp short 0xBC7C6D2                           ; -> loc_bc7c6d2

loc_bc7c6d0:  ; from bc7c6c1
  bc7c6d0  xor edx,edx                                   

loc_bc7c6d2:  ; from bc7c6ce
  bc7c6d2  mov r12,[rbp+0x370]                           
  bc7c6d9  movups xmm0,[rdi]                             
  bc7c6dc  movups xmm1,[rdi+0x10]                        
  bc7c6e0  movups xmm2,[rdi+0x1C]                        
  bc7c6e4  movups [rbp-0x24],xmm2                        
  bc7c6e8  movaps [rbp-0x30],xmm1                        
  bc7c6ec  movaps [rbp-0x40],xmm0                        
  bc7c6f0  mov ebx,[rdi+0x2C]                            
  bc7c6f3  mov r13d,[rdi+0x30]                           
  bc7c6f7  mov r15d,[rdi+0x34]                           
  bc7c6fb  mov rcx,[rdi+0x38]                            
  bc7c6ff  mov [rbp+0x340],rcx                           
  bc7c706  mov ecx,[rdi+0x40]                            
  bc7c709  mov [rbp+0x348],ecx                           
  bc7c70f  mov rcx,[rax]                                 
  bc7c712  mov [rbp+0x350],rcx                           
  bc7c719  mov eax,[rax+8]                               
  bc7c71c  mov [rbp+0x358],eax                           
  bc7c722  xorps xmm0,xmm0                               
  bc7c725  movaps [rbp+0x390],xmm0                       
  bc7c72c  movaps [rbp+0x380],xmm0                       
  bc7c733  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bc7c73a  mov rax,[rcx]                                 
  bc7c73d  mov rax,[rax+8]                               
  bc7c741  mov r8,[0xF99FFA0]                            ; [data_f99ffa0] = sub_eea6040
  bc7c748  mov [rbp+0x3D0],rdx                           
  bc7c74f  mov [rbp+0x3A8],rdx                           
  bc7c756  mov edx,0x20                                  
  bc7c75b  call r8                                       
  bc7c75e  nop                                           
  bc7c75f  test rax,rax                                  
  bc7c762  je 0xBC7D44B                                  ; -> loc_bc7d44b

loc_bc7c768:  ; from bc7d469
  bc7c768  mov [rbp+0x380],rax                           
  bc7c76f  mov qword ptr [rbp+0x390],0x10                
  bc7c77a  mov qword ptr [rbp+0x398],0x1F                
  bc7c785  movups xmm0,[0xF5B4987]                       ; [data_f5b4987] "VolumeScattering"
  bc7c78c  movups [rax],xmm0                             
  bc7c78f  lea r9,[0xF5B4987]                            ; [data_f5b4987] "VolumeScattering"
  bc7c796  mov byte ptr [rax+0x10],0                     
  bc7c79a  lea rcx,[rbp+0x218]                           
  bc7c7a1  xorps xmm0,xmm0                               
  bc7c7a4  movaps [rbp+0x220],xmm0                       
  bc7c7ab  movaps [rbp+0x210],xmm0                       
  bc7c7b2  mov qword ptr [rbp+0x230],0xF                 
  bc7c7bd  mov qword ptr [rbp+0x238],0                   
  bc7c7c8  mov edx,0x10                                  
  bc7c7cd  call 0x9D6D0                                  ; -> sub_9d6d0
  bc7c7d2  nop                                           
  bc7c7d3  mov rax,0xC6733561A9D20C39                    
  bc7c7dd  mov [rbp+0x210],rax                           
  bc7c7e4  mov rax,[rbp+0x390]                           
  bc7c7eb  cmp qword ptr [rbp+0x398],0x10                
  bc7c7f3  jb short 0xBC7C7FE                            ; -> loc_bc7c7fe
  bc7c7f5  mov rcx,[rbp+0x380]                           
  bc7c7fc  jmp short 0xBC7C805                           ; -> loc_bc7c805

loc_bc7c7fe:  ; from bc7c7f3
  bc7c7fe  lea rcx,[rbp+0x380]                           

loc_bc7c805:  ; from bc7c7fc
  bc7c805  mov rdi,[rbp+0x3D0]                           
  bc7c80c  mov [rbp+0x1F0],rcx                           
  bc7c813  mov [rbp+0x1F8],rax                           
  bc7c81a  mov [rbp+0x368],rdi                           
  bc7c821  lea rcx,[rbp+0x320]                           
  bc7c828  lea rdx,[rbp+0x1F0]                           
  bc7c82f  call 0x568AD40                                ; -> sub_568ad40
  bc7c834  nop                                           
  bc7c835  movups xmm0,[rbp+0x320]                       
  bc7c83c  movups xmm1,[rbp+0x330]                       
  bc7c843  movaps [rbp],xmm1                             
  bc7c847  movaps [rbp-0x10],xmm0                        
  bc7c84b  mov qword ptr [rbp+0x330],0                   
  bc7c856  mov qword ptr [rbp+0x338],0xF                 
  bc7c861  mov byte ptr [rbp+0x320],0                    
  bc7c868  mov [rbp+0x10],r12                            
  bc7c86c  mov [rbp+0x18],rdi                            
  bc7c870  movaps xmm0,[rbp-0x40]                        
  bc7c874  movaps xmm1,[rbp-0x30]                        
  bc7c878  movaps [rbp+0x20],xmm0                        
  bc7c87c  movaps [rbp+0x30],xmm1                        
  bc7c880  movups xmm0,[rbp-0x24]                        
  bc7c884  movups [rbp+0x3C],xmm0                        
  bc7c888  mov [rbp+0x4C],ebx                            
  bc7c88b  mov [rbp+0x50],r13d                           
  bc7c88f  mov [rbp+0x54],r15d                           
  bc7c893  mov eax,[rbp+0x348]                           
  bc7c899  mov [rbp+0x60],eax                            
  bc7c89c  mov rax,[rbp+0x340]                           
  bc7c8a3  mov [rbp+0x58],rax                            
  bc7c8a7  mov eax,[rbp+0x358]                           
  bc7c8ad  mov [rbp+0x6C],eax                            
  bc7c8b0  mov rax,[rbp+0x350]                           
  bc7c8b7  mov [rbp+0x64],rax                            
  bc7c8bb  mov qword ptr [rbp+0xA8],0                    
  bc7c8c6  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bc7c8cd  mov rax,[rcx]                                 
  bc7c8d0  mov rax,[rax+8]                               
  bc7c8d4  mov edx,0x130                                 
  bc7c8d9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7c8df  nop                                           
  bc7c8e0  mov rdi,rax                                   
  bc7c8e3  test rax,rax                                  
  bc7c8e6  je 0xBC7D46E                                  ; -> loc_bc7d46e

loc_bc7c8ec:  ; from bc7d479
  bc7c8ec  lea rax,[0xF44B200]                           ; [data_f44b200]
  bc7c8f3  mov [rdi],rax                                 
  bc7c8f6  mov dword ptr [rdi+8],0x3F800000              
  bc7c8fd  xorps xmm6,xmm6                               
  bc7c900  movups [rdi+0xC],xmm6                         
  bc7c904  mov dword ptr [rdi+0x1C],0x3F800000           
  bc7c90b  movups [rdi+0x20],xmm6                        
  bc7c90f  mov dword ptr [rdi+0x30],0x3F800000           
  bc7c916  movups [rdi+0x34],xmm6                        
  bc7c91a  movsd xmm0,[0xEFD3400]                        ; [data_efd3400]
  bc7c922  movsd [rdi+0x44],xmm0                         
  bc7c927  movups [rdi+0x4C],xmm6                        
  bc7c92b  mov dword ptr [rdi+0x5C],0x3F800000           
  bc7c932  movups [rdi+0x60],xmm6                        
  bc7c936  mov dword ptr [rdi+0x70],0x3F800000           
  bc7c93d  movups [rdi+0x74],xmm6                        
  bc7c941  mov dword ptr [rdi+0x84],0x3F800000           
  bc7c94b  movups [rdi+0x88],xmm6                        
  bc7c952  mov rax,0x3F80000000000001                    
  bc7c95c  mov [rdi+0x98],rax                            
  bc7c963  movups [rdi+0xA0],xmm6                        
  bc7c96a  mov dword ptr [rdi+0xB0],0x3F800000           
  bc7c974  movups [rdi+0xB4],xmm6                        
  bc7c97b  mov dword ptr [rdi+0xC4],0x3F800000           
  bc7c985  movups [rdi+0xC8],xmm6                        
  bc7c98c  movsd [rdi+0xD8],xmm0                         
  bc7c994  movups [rdi+0xE0],xmm6                        
  bc7c99b  mov dword ptr [rdi+0xF0],0x3F800000           
  bc7c9a5  movups [rdi+0xF4],xmm6                        
  bc7c9ac  mov dword ptr [rdi+0x104],0x3F800000          
  bc7c9b6  movups [rdi+0x108],xmm6                       
  bc7c9bd  mov dword ptr [rdi+0x118],0x3F800000          
  bc7c9c7  movups [rdi+0x11C],xmm6                       
  bc7c9ce  mov [rbp+0xA8],rdi                            
  bc7c9d5  lea rcx,[rbp+0x270]                           
  bc7c9dc  lea rdx,[rbp+0x380]                           
  bc7c9e3  call 0x76A8A0                                 ; -> sub_76a8a0
  bc7c9e8  nop                                           
  bc7c9e9  mov [rbp+0x2D0],rsi                           
  bc7c9f0  movzx ecx,word ptr [rbp+0x3B8]                
  bc7c9f7  mov [rbp+0x2D8],cx                            
  bc7c9fe  mov dword ptr [rbp+0x2DC],8                   
  bc7ca08  mov byte ptr [rbp+0x2E0],0                    
  bc7ca0f  mov [rbp+0x2E8],r14                           
  bc7ca16  mov byte ptr [rbp+0x2F2],0                    
  bc7ca1d  mov rax,[rbp+0x3B0]                           
  bc7ca24  mov [rbp+0x2F8],rax                           
  bc7ca2b  mov rax,[rbp+0x270]                           
  bc7ca32  mov [rbp+0x300],cx                            
  bc7ca39  mov rcx,[rbp+0x278]                           
  bc7ca40  mov dword ptr [rbp+0x304],8                   
  bc7ca4a  mov byte ptr [rbp+0x308],0                    
  bc7ca51  mov rdx,[rbp+0x3C0]                           
  bc7ca58  mov [rbp+0x310],rdx                           
  bc7ca5f  mov rdx,[rbp+0x280]                           
  bc7ca66  mov qword ptr [rbp+0x268],0                   
  bc7ca71  mov [rbp+0x248],rcx                           
  bc7ca78  mov [rbp+0x250],rdx                           
  bc7ca7f  mov [rbp+0x240],rax                           
  bc7ca86  mov qword ptr [rbp+0x258],0                   
  bc7ca91  mov qword ptr [rbp+0x260],0xF                 
  bc7ca9c  mov byte ptr [rbp+0x248],0                    
  bc7caa3  mov byte ptr [rbp+0x31A],0                    
  bc7caaa  mov qword ptr [rbp+0x2C8],0                   
  bc7cab5  mov [rbp+0x2A8],cl                            
  bc7cabb  mov rcx,[rbp+0x249]                           
  bc7cac2  mov [rbp+0x2A9],rcx                           
  bc7cac9  mov [rbp+0x2B0],rdx                           
  bc7cad0  movaps xmm0,[rbp-0x10]                        
  bc7cad4  movaps xmm1,[rbp]                             
  bc7cad8  movaps [rbp+0xC0],xmm1                        
  bc7cadf  movaps [rbp+0xB0],xmm0                        
  bc7cae6  mov [rbp+0xD0],r12                            
  bc7caed  mov rcx,[rbp+0x3D0]                           
  bc7caf4  mov [rbp+0xD8],rcx                            
  bc7cafb  lea rcx,[rbp+0x10]                            
  bc7caff  mov qword ptr [rbp],0                         
  bc7cb07  mov qword ptr [rbp+8],0xF                     
  bc7cb0f  mov byte ptr [rbp-0x10],0                     
  bc7cb13  movups [rcx],xmm6                             
  bc7cb16  movups xmm0,[rcx+0x10]                        
  bc7cb1a  movups xmm1,[rcx+0x20]                        
  bc7cb1e  movups xmm2,[rcx+0x2C]                        
  bc7cb22  movups [rbp+0xFC],xmm2                        
  bc7cb29  movaps [rbp+0xF0],xmm1                        
  bc7cb30  movaps [rbp+0xE0],xmm0                        
  bc7cb37  mov [rbp+0x10C],ebx                           
  bc7cb3d  mov [rbp+0x110],r13d                          
  bc7cb44  mov [rbp+0x114],r15d                          
  bc7cb4b  mov rdx,[rcx+0x48]                            
  bc7cb4f  mov [rbp+0x118],rdx                           
  bc7cb56  mov edx,[rcx+0x50]                            
  bc7cb59  mov [rbp+0x120],edx                           
  bc7cb5f  mov rdx,[rcx+0x54]                            
  bc7cb63  mov [rbp+0x124],rdx                           
  bc7cb6a  mov ecx,[rcx+0x5C]                            
  bc7cb6d  mov [rbp+0x12C],ecx                           
  bc7cb73  mov byte ptr [rbp+0x278],0                    
  bc7cb7a  movups xmm0,[rbp+0x288]                       
  bc7cb81  mov qword ptr [rbp+0x288],0                   
  bc7cb8c  mov qword ptr [rbp+0x290],0xF                 
  bc7cb97  movups [rbp+0x2B8],xmm0                       
  bc7cb9e  mov [rbp+0x2A0],rax                           
  bc7cba5  mov [rbp+0x168],rdi                           
  bc7cbac  mov qword ptr [rbp+0xA8],0                    
  bc7cbb7  mov qword ptr [rbp+0x198],0                   
  bc7cbc2  movups xmm0,[rbp+0x2A8]                       
  bc7cbc9  movups xmm1,[rbp+0x2B8]                       
  bc7cbd0  movups [rbp+0x178],xmm0                       
  bc7cbd7  movups [rbp+0x188],xmm1                       
  bc7cbde  mov qword ptr [rbp+0x2B8],0                   
  bc7cbe9  mov qword ptr [rbp+0x2C0],0xF                 
  bc7cbf4  mov byte ptr [rbp+0x2A8],0                    
  bc7cbfb  mov [rbp+0x170],rax                           
  bc7cc02  movups xmm0,[rbp+0x2D0]                       
  bc7cc09  movups xmm1,[rbp+0x2E0]                       
  bc7cc10  movaps [rbp+0x1A0],xmm0                       
  bc7cc17  movaps [rbp+0x1B0],xmm1                       
  bc7cc1e  mov rax,[rbp+0x2F0]                           
  bc7cc25  mov [rbp+0x1C0],rax                           
  bc7cc2c  mov rax,[rbp+0x318]                           
  bc7cc33  mov [rbp+0x1E8],rax                           
  bc7cc3a  movups xmm0,[rbp+0x2F8]                       
  bc7cc41  movups xmm1,[rbp+0x308]                       
  bc7cc48  movups [rbp+0x1D8],xmm1                       
  bc7cc4f  movups [rbp+0x1C8],xmm0                       
  bc7cc56  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bc7cc5d  mov rax,[rcx]                                 
  bc7cc60  mov rax,[rax+8]                               
  bc7cc64  mov edx,0x108                                 
  bc7cc69  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7cc6f  nop                                           
  bc7cc70  mov r15,rax                                   
  bc7cc73  test rax,rax                                  
  bc7cc76  je 0xBC7D47E                                  ; -> loc_bc7d47e

loc_bc7cc7c:  ; from bc7d489
  bc7cc7c  lea rbx,[rbp+0xD0]                            
  bc7cc83  mov rax,0x100000001                           
  bc7cc8d  mov [r15+8],rax                               
  bc7cc91  lea rax,[0xEFCBE20]                           ; [data_efcbe20]
  bc7cc98  mov [r15],rax                                 
  bc7cc9b  mov r12,[rbp+0xC8]                            
  bc7cca2  mov rsi,[rbp+0xB0]                            
  bc7cca9  mov rdi,[rbp+0xC0]                            
  bc7ccb0  movups [r15+0x28],xmm6                        
  bc7ccb5  movups [r15+0x18],xmm6                        
  bc7ccba  mov qword ptr [r15+0x38],0xF                  
  bc7ccc2  mov qword ptr [r15+0x40],0                    
  bc7ccca  lea rax,[0xF44B1E0]                           ; [data_f44b1e0]
  bc7ccd1  mov [r15+0x10],rax                            
  bc7ccd5  lea r13,[r15+0x48]                            
  bc7ccd9  mov qword ptr [r15+0x80],0                    
  bc7cce4  mov rcx,[rbp+0x168]                           
  bc7cceb  test rcx,rcx                                  
  bc7ccee  je short 0xBC7CD46                            ; -> loc_bc7cd46
  bc7ccf0  lea r14,[rbp+0x130]                           
  bc7ccf7  cmp rcx,r14                                   
  bc7ccfa  je short 0xBC7CD05                            ; -> loc_bc7cd05
  bc7ccfc  mov [r15+0x80],rcx                            
  bc7cd03  jmp short 0xBC7CD3B                           ; -> loc_bc7cd3b

loc_bc7cd05:  ; from bc7ccfa
  bc7cd05  mov rax,[rcx]                                 
  bc7cd08  mov rax,[rax+8]                               
  bc7cd0c  mov rdx,r13                                   
  bc7cd0f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7cd15  mov [r15+0x80],rax                            
  bc7cd1c  mov rcx,[rbp+0x168]                           
  bc7cd23  test rcx,rcx                                  
  bc7cd26  je short 0xBC7CD46                            ; -> loc_bc7cd46
  bc7cd28  cmp rcx,r14                                   
  bc7cd2b  setne dl                                      
  bc7cd2e  mov rax,[rcx]                                 
  bc7cd31  mov rax,[rax+0x20]                            
  bc7cd35  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_bc7cd3b:  ; from bc7cd03
  bc7cd3b  mov qword ptr [rbp+0x168],0                   

loc_bc7cd46:  ; from bc7ccee, bc7cd26
  bc7cd46  mov [rbp+0x3C0],r13                           
  bc7cd4d  lea rax,[r15+0x10]                            
  ... (--max 400)
```

## CALLERS
```
  0xbc7ba60 sub_bc7ba60 size 0x8fa
  -- 1 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier

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

