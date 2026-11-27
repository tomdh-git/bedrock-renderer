# ctxpack build 0xbc71da0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=dossier=bc71da0.md:5cc045113fcff683f6fec33e0ce40283790c33b641ac168a662b15e546e9a452,liftsrc=sub_bc71da0.cpp:5c5ff2bb19372deff7265bde5e6f5ac3e192efc77b1d3218ed9accf992ac5938,liftsrc=sub_bc71da0.h:3470e6bc6aa0e7dc1e3d5be6c2db4fc590d33bd531099bb49c99d558f3d0b4dc,data=native_functions.tsv:bdcd6148497d9602d8b6e2502f9eeacac70d17f7043d54b487f012c7c593c182,data=native_deps.tsv:3a011b1beb8abc9cee35af6b8def513461bb5c74a237acd078264ae2eeae7369,data=native_boundary.tsv:09d2c7e87589c4874db33822736157330acef9a310eb3c5672cfea2172b1000d,data=native_boundary_candidates.tsv:5dbcc428209895d9e114212ccd83d2cdc3d5e8f37ef0c1a03b1f4d609ef5aebb

## HEADER
  rva        : 0xbc71da0
  size       : 0x167 (359 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 3 (direct), depth 1
  callers    : 2

## EXACT LISTING (0xbc71da0..0xbc71f07)
```
sub_bc71da0  [0xbc71da0..0xbc73da0)  size 0x2000  2 xrefs in
  bc71da0  push rbp                                      
  bc71da1  push r14                                      
  bc71da3  push rsi                                      
  bc71da4  push rdi                                      
  bc71da5  push rbx                                      
  bc71da6  sub rsp,0x40                                  
  bc71daa  lea rbp,[rsp+0x40]                            
  bc71daf  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE      
  bc71db7  mov ebx,r8d                                   
  bc71dba  mov rsi,rdx                                   
  bc71dbd  mov rdi,rcx                                   
  bc71dc0  mov [rbp-0x10],r9d                            
  bc71dc4  lea r14,[rcx+0x1C0]                           ; R a0+0x1C0
  bc71dcb  mov rcx,r14                                   
  bc71dce  call 0xEBDBF10                                ; -> sub_ebdbf10
  bc71dd3  cmp bx,0xFFFF                                 
  bc71dd7  je 0xBC71E9B                                  ; -> loc_bc71e9b
  bc71ddd  mov [rbp-0xA],bx                              

loc_bc71de1:  ; from bc71ee7
  bc71de1  mov [rbp-0x18],r14                            
  bc71de5  mov rbx,[rdi+0x1CFD0C8]                       ; R a0+0x1CFD0C8
  bc71dec  mov byte ptr [rbp-0xB],0xB                    
  bc71df0  mov eax,[rbx+0xDC5818]                        ; R *(a0+0x1CFD0C8)+0xDC5818
  bc71df6  lea rcx,[rbx+rax]                             ; R *(a0+0x1CFD0C8)+0x0+idx
  bc71dfa  add rcx,0xDC5820                              
  bc71e01  lea rdx,[rbp-0xB]                             
  bc71e05  mov r8d,1                                     
  bc71e0b  call 0xEBCE390                                ; -> sub_ebce390
  bc71e10  nop                                           
  bc71e11  lea rdi,[rbx+0xDC5820]                        ; R *(a0+0x1CFD0C8)+0xDC5820
  bc71e18  mov ecx,[rbx+0xDC5818]                        ; R *(a0+0x1CFD0C8)+0xDC5818
  bc71e1e  and ecx,0xFFFFFFFE                            
  bc71e21  add ecx,2                                     
  bc71e24  mov [rbx+0xDC5818],ecx                        ; W *(a0+0x1CFD0C8)+0xDC5818
  bc71e2a  add rcx,rdi                                   
  bc71e2d  lea rdx,[rbp-0xA]                             
  bc71e31  mov r8d,2                                     
  bc71e37  call 0xEBCE390                                ; -> sub_ebce390
  bc71e3c  nop                                           
  bc71e3d  mov ecx,[rbx+0xDC5818]                        ; R *(a0+0x1CFD0C8)+0xDC5818
  bc71e43  add ecx,5                                     
  bc71e46  and ecx,0xFFFFFFFC                            
  bc71e49  mov [rbx+0xDC5818],ecx                        ; W *(a0+0x1CFD0C8)+0xDC5818
  bc71e4f  add rcx,rdi                                   
  bc71e52  lea rdx,[rbp-0x10]                            
  bc71e56  mov r8d,4                                     
  bc71e5c  call 0xEBCE390                                ; -> sub_ebce390
  bc71e61  nop                                           
  bc71e62  mov eax,[rbx+0xDC5818]                        ; R *(a0+0x1CFD0C8)+0xDC5818
  bc71e68  add eax,0xB                                   
  bc71e6b  and eax,0xFFFFFFF8                            
  bc71e6e  mov [rbx+0xDC5818],eax                        ; W *(a0+0x1CFD0C8)+0xDC5818
  bc71e74  add rdi,rax                                   
  bc71e77  lea rdx,[rbp+0x50]                            
  bc71e7b  mov r8d,8                                     
  bc71e81  mov rcx,rdi                                   
  bc71e84  call 0xEBCE390                                ; -> sub_ebce390
  bc71e89  nop                                           
  bc71e8a  add dword ptr [rbx+0xDC5818],8                ; W *(a0+0x1CFD0C8)+0xDC5818
  bc71e91  movzx eax,word ptr [rbp-0xA]                  
  bc71e95  mov r14,[rbp-0x18]                            
  bc71e99  jmp short 0xBC71EED                           ; -> loc_bc71eed

loc_bc71e9b:  ; from bc71dd7
  bc71e9b  movzx ecx,word ptr [rdi+0x1DFC298]            
  bc71ea2  movzx edx,word ptr [rdi+0x1DFC29A]            
  bc71ea9  mov ax,0xFFFF                                 
  bc71ead  cmp cx,dx                                     
  bc71eb0  jae short 0xBC71EED                           ; -> loc_bc71eed
  bc71eb2  movzx r8d,cx                                  
  bc71eb6  lea r9d,[rcx+1]                               
  bc71eba  mov [rdi+0x1DFC298],r9w                       
  bc71ec2  movzx r8d,word ptr [rdi+r8*2+0x1DFC29C]       
  bc71ecb  lea rdx,[rdi+rdx*2]                           
  bc71ecf  add rdx,0x1DFC29C                             
  bc71ed6  mov [rdx+r8*2],cx                             
  bc71edb  mov [rbp-0xA],r8w                             
  bc71ee0  cmp r8d,0xFFFF                                
  bc71ee7  jne 0xBC71DE1                                 ; -> loc_bc71de1

loc_bc71eed:  ; from bc71e99, bc71eb0
  bc71eed  mov [rsi],ax                                  
  bc71ef0  mov rcx,r14                                   
  bc71ef3  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc71ef8  nop                                           
  bc71ef9  mov rax,rsi                                   
  bc71efc  add rsp,0x40                                  
  bc71f00  pop rbx                                       
  bc71f01  pop rdi                                       
  bc71f02  pop rsi                                       
  bc71f03  pop r14                                       
  bc71f05  pop rbp                                       
  bc71f06  ret                                           
  bc71f07  nop [rax+rax]                                 
  bc71f10  mov [rsp+0x10],rdx                            
  bc71f15  push rbp                                      
  bc71f16  push r14                                      
  bc71f18  push rsi                                      
  bc71f19  push rdi                                      
  bc71f1a  push rbx                                      
  bc71f1b  sub rsp,0x20                                  
  bc71f1f  lea rbp,[rdx+0x40]                            
  bc71f23  mov rcx,[rbp-0x18]                            
  bc71f27  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc71f2c  nop                                           
  bc71f2d  add rsp,0x20                                  
  bc71f31  pop rbx                                       
  bc71f32  pop rdi                                       
  bc71f33  pop rsi                                       
  bc71f34  pop r14                                       
  bc71f36  pop rbp                                       
  bc71f37  ret                                           
  bc71f38  nop [rax+rax]                                 ; R ret@ebdbf20+0x0+idx
  bc71f40  mov [rsp+0x10],rdx                            
  bc71f45  push rbp                                      
  bc71f46  push r14                                      
  bc71f48  push rsi                                      
  bc71f49  push rdi                                      
  bc71f4a  push rbx                                      
  bc71f4b  sub rsp,0x20                                  
  bc71f4f  lea rbp,[rdx+0x40]                            
  bc71f53  call 0xEEC6E40                                ; -> sub_eec6e40
  bc71f58  int3                                          
  bc71f59  int3                                          
  bc71f5a  int3                                          
  bc71f5b  int3                                          
  bc71f5c  int3                                          
  bc71f5d  int3                                          
  bc71f5e  int3                                          
  bc71f5f  int3                                          
  bc71f60  push rbp                                      
  bc71f61  push r15                                      
  bc71f63  push r14                                      
  bc71f65  push r13                                      
  bc71f67  push r12                                      
  bc71f69  push rsi                                      
  bc71f6a  push rdi                                      
  bc71f6b  push rbx                                      
  bc71f6c  sub rsp,0x1C8                                 
  bc71f73  lea rbp,[rsp+0x80]                            
  bc71f7b  mov qword ptr [rbp+0x140],0xFFFFFFFFFFFFFFFE  
  bc71f86  mov rbx,r8                                    
  bc71f89  mov [rbp+0x128],rdx                           
  bc71f90  mov [rbp+0x88],r8                             
  bc71f97  mov [rbp+0x108],rcx                           
  bc71f9e  add rcx,0x1C0                                 
  bc71fa5  sub rsp,0x20                                  
  bc71fa9  mov [rbp+0xB8],rcx                            
  bc71fb0  call 0xEBDBF10                                ; -> sub_ebdbf10
  bc71fb5  add rsp,0x20                                  
  bc71fb9  mov edi,[rbx+8]                               
  bc71fbc  mov rdx,[rbx]                                 
  bc71fbf  lea rax,[0xF449520]                           ; [data_f449520]
  bc71fc6  mov [rbp+0xE0],rax                            
  bc71fcd  lea rax,[0xF449530]                           ; [data_f449530]
  bc71fd4  mov [rbp+0xE8],rax                            
  bc71fdb  mov [rbp+0xF0],rdx                            
  bc71fe2  mov [rbp+0x100],rdi                           
  bc71fe9  lea r15,[0xF847A07]                           ; [data_f847a07]
  bc71ff0  mov [rbp+0x110],r15                           
  bc71ff7  mov dword ptr [rbp+0x118],0                   
  bc72001  mov dword ptr [rbp+0x120],0                   
  bc7200b  cmp rdi,0x7FFFFFFF                            
  bc72012  mov eax,0x7FFFFFFF                            
  bc72017  cmovb rax,rdi                                 
  bc7201b  cmp eax,4                                     
  bc7201e  mov esi,4                                     
  bc72023  cmovb esi,eax                                 
  bc72026  sub rsp,0x20                                  
  bc7202a  lea rcx,[rbp+0xD0]                            
  bc72031  mov r8,rsi                                    
  bc72034  call 0xEBCE390                                ; -> sub_ebce390
  bc72039  add rsp,0x20                                  
  bc7203d  mov [rbp+0xF8],rsi                            
  bc72044  cmp edi,3                                     
  bc72047  ja short 0xBC720B2                            ; -> loc_bc720b2
  bc72049  sub rsp,0x20                                  
  bc7204d  lea r14,[0xF80CD25]                           ; [data_f80cd25] "MemoryReader: read truncated."
  bc72054  mov rcx,r14                                   
  bc72057  mov edx,0x7FFFFFFF                            
  bc7205c  call 0xEBCE5E0                                ; -> sub_ebce5e0
  bc72061  add rsp,0x20                                  
  bc72065  test eax,eax                                  
  bc72067  cmove r14,r15                                 
  bc7206b  cmp dword ptr [rbp+0x120],0                   
  bc72072  jne short 0xBC720BF                           ; -> loc_bc720bf
  bc72074  mov dword ptr [rbp+0x120],0x2005752           
  bc7207e  mov [rbp+0x110],r15                           
  bc72085  mov dword ptr [rbp+0x118],0                   
  bc7208f  sub rsp,0x20                                  
  bc72093  mov rcx,r14                                   
  bc72096  mov edx,eax                                   
  bc72098  call 0xEBCE5E0                                ; -> sub_ebce5e0
  bc7209d  add rsp,0x20                                  
  bc720a1  test eax,eax                                  
  bc720a3  je short 0xBC720B2                            ; -> loc_bc720b2
  bc720a5  mov [rbp+0x118],eax                           
  bc720ab  mov [rbp+0x110],r14                           

loc_bc720b2:  ; from bc72047, bc720a3
  bc720b2  cmp dword ptr [rbp+0x120],0                   
  bc720b9  je 0xBC7215F                                  ; -> loc_bc7215f

loc_bc720bf:  ; from bc72072
  bc720bf  mov rcx,[rbx]                                 
  bc720c2  lea rax,[rbx+0x10]                            
  bc720c6  cmp rcx,rax                                   
  bc720c9  je short 0xBC720E5                            ; -> loc_bc720e5
  bc720cb  mov rax,[rax]                                 
  bc720ce  test rax,rax                                  
  bc720d1  je short 0xBC720E5                            ; -> loc_bc720e5
  bc720d3  mov rdx,[rbx+0x18]                            
  bc720d7  sub rsp,0x20                                  
  bc720db  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc720e1  add rsp,0x20                                  

loc_bc720e5:  ; from bc720c9, bc720d1
  bc720e5  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc720ec  test rcx,rcx                                  
  bc720ef  je short 0xBC72124                            ; -> loc_bc72124
  bc720f1  mov rax,[rcx]                                 
  bc720f4  mov rax,[rax+8]                               
  bc720f8  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc720ff  sub rsp,0x30                                  
  bc72103  mov dword ptr [rsp+0x28],0                    
  bc7210b  mov qword ptr [rsp+0x20],0                    
  bc72114  mov rdx,rbx                                   
  bc72117  xor r8d,r8d                                   
  bc7211a  xor r9d,r9d                                   
  bc7211d  call r10                                      
  bc72120  add rsp,0x30                                  

loc_bc72124:  ; from bc720ef, bc722e3, bc7231c, bc72351, bc7238a
  bc72124  mov rax,[rbp+0x128]                           
  bc7212b  mov word ptr [rax],0xFFFF                     

loc_bc72130:  ; from bc723d5, bc7240e, bc72960
  bc72130  sub rsp,0x20                                  
  bc72134  mov rcx,[rbp+0xB8]                            
  bc7213b  call 0xEBDBF20                                ; -> sub_ebdbf20
  bc72140  add rsp,0x20                                  
  bc72144  mov rax,[rbp+0x128]                           
  bc7214b  lea rsp,[rbp+0x148]                           
  bc72152  pop rbx                                       
  bc72153  pop rdi                                       
  bc72154  pop rsi                                       
  bc72155  pop r12                                       
  bc72157  pop r13                                       
  bc72159  pop r14                                       
  bc7215b  pop r15                                       
  bc7215d  pop rbp                                       
  bc7215e  ret                                           

loc_bc7215f:  ; from bc720b9
  bc7215f  mov eax,[rbp+0xD0]                            
  bc72165  cmp eax,0x3485343                             
  bc7216a  je short 0xBC7217E                            ; -> loc_bc7217e
  bc7216c  cmp eax,0x5485346                             
  bc72171  je short 0xBC7217E                            ; -> loc_bc7217e
  bc72173  cmp eax,0x5485356                             
  bc72178  jne 0xBC72321                                 ; -> loc_bc72321

loc_bc7217e:  ; from bc7216a, bc72171
  bc7217e  mov r8d,[rbx+8]                               
  bc72182  mov rdx,[rbx]                                 
  bc72185  xorps xmm0,xmm0                               
  bc72188  movaps [rbp-0x80],xmm0                        
  bc7218c  sub rsp,0x20                                  
  bc72190  lea r14,[rbp-0x80]                            
  bc72194  mov rcx,r14                                   
  bc72197  call 0xBC76610                                ; -> sub_bc76610
  bc7219c  add rsp,0x20                                  
  bc721a0  imul eax,[rbp-0x7C],0x5BD1E995                
  bc721a7  mov ecx,eax                                   
  bc721a9  shr ecx,0x18                                  
  bc721ac  xor ecx,eax                                   
  bc721ae  imul eax,ecx,0x5BD1E995                       
  bc721b4  imul ecx,[rbp-0x80],0x5BD1E995                
  bc721bb  xor ecx,eax                                   
  bc721bd  imul eax,[rbp-0x74],0x5BD1E995                
  bc721c4  mov edx,eax                                   
  bc721c6  shr edx,0x18                                  
  bc721c9  xor edx,eax                                   
  bc721cb  imul eax,edx,0x5BD1E995                       
  bc721d1  imul ecx,0x5BD1E995                           
  bc721d7  xor ecx,eax                                   
  bc721d9  mov eax,ecx                                   
  bc721db  shr eax,0xD                                   
  bc721de  xor eax,ecx                                   
  bc721e0  imul eax,0x5BD1E995                           
  bc721e6  mov esi,eax                                   
  bc721e8  shr esi,0xF                                   
  bc721eb  xor esi,eax                                   
  bc721ed  imul eax,esi,0x85EBCA77                       
  bc721f3  shr eax,0x13                                  
  bc721f6  imul r12d,eax,0x19B1                          
  bc721fd  and r12d,0x1FFF                               
  bc72204  mov eax,r12d                                  
  bc72207  mov r8,[rbp+0x108]                            
  bc7220e  xchg ax,ax                                    

loc_bc72210:  ; from bc7223c
  bc72210  mov edx,eax                                   
  bc72212  movzx ecx,word ptr [r8+rdx*2+0x1E28AB0]       
  bc7221b  cmp rcx,0xFFFF                                
  bc72222  je short 0xBC7223E                            ; -> loc_bc7223e
  bc72224  cmp [r8+rdx*4+0x1E20AB0],esi                  
  bc7222c  je 0xBC7238F                                  ; -> loc_bc7238f
  bc72232  inc eax                                       
  bc72234  and eax,0x1FFF                                
  bc72239  cmp eax,r12d                                  
  bc7223c  jne short 0xBC72210                           ; -> loc_bc72210

loc_bc7223e:  ; from bc72222
  bc7223e  mov rax,[rbp+0xE0]                            
  bc72245  mov rax,[rax+8]                               
  bc72249  sub rsp,0x20                                  
  bc7224d  lea rcx,[rbp+0xE0]                            
  bc72254  lea rdx,[rbp+0xD4]                            
  bc7225b  lea r9,[rbp+0x110]                            
  bc72262  mov r8d,4                                     
  bc72268  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc7226e  add rsp,0x20                                  
  bc72272  mov rax,[rbp+0xE0]                            
  bc72279  mov rax,[rax+8]                               
  bc7227d  sub rsp,0x20                                  
  bc72281  lea rcx,[rbp+0xE0]                            
  bc72288  lea rdx,[rbp+0x13A]                           
  bc7228f  lea r9,[rbp+0x110]                            
  bc72296  mov r8d,2                                     
  bc7229c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc722a2  add rsp,0x20                                  
  bc722a6  cmp dword ptr [rbp+0x120],0                   
  bc722ad  je 0xBC72413                                  ; -> loc_bc72413
  bc722b3  mov rcx,[rbx]                                 
  bc722b6  lea rax,[rbx+0x10]                            
  bc722ba  cmp rcx,rax                                   
  bc722bd  je short 0xBC722D9                            ; -> loc_bc722d9
  bc722bf  mov rax,[rax]                                 
  bc722c2  test rax,rax                                  
  bc722c5  je short 0xBC722D9                            ; -> loc_bc722d9
  bc722c7  mov rdx,[rbx+0x18]                            
  bc722cb  sub rsp,0x20                                  
  bc722cf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc722d5  add rsp,0x20                                  

loc_bc722d9:  ; from bc722bd, bc722c5
  bc722d9  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc722e0  test rcx,rcx                                  
  bc722e3  je 0xBC72124                                  ; -> loc_bc72124
  bc722e9  mov rax,[rcx]                                 
  bc722ec  mov rax,[rax+8]                               
  bc722f0  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc722f7  sub rsp,0x30                                  
  bc722fb  mov dword ptr [rsp+0x28],0                    
  bc72303  mov qword ptr [rsp+0x20],0                    
  bc7230c  mov rdx,rbx                                   
  bc7230f  xor r8d,r8d                                   
  bc72312  xor r9d,r9d                                   
  bc72315  call r10                                      
  bc72318  add rsp,0x30                                  
  bc7231c  jmp 0xBC72124                                 ; -> loc_bc72124

loc_bc72321:  ; from bc72178
  bc72321  mov rcx,[rbx]                                 
  bc72324  lea rax,[rbx+0x10]                            
  bc72328  cmp rcx,rax                                   
  bc7232b  je short 0xBC72347                            ; -> loc_bc72347
  bc7232d  mov rax,[rax]                                 
  bc72330  test rax,rax                                  
  bc72333  je short 0xBC72347                            ; -> loc_bc72347
  bc72335  mov rdx,[rbx+0x18]                            
  bc72339  sub rsp,0x20                                  
  bc7233d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc72343  add rsp,0x20                                  

loc_bc72347:  ; from bc7232b, bc72333
  bc72347  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc7234e  test rcx,rcx                                  
  bc72351  je 0xBC72124                                  ; -> loc_bc72124
  bc72357  mov rax,[rcx]                                 
  bc7235a  mov rax,[rax+8]                               
  bc7235e  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc72365  sub rsp,0x30                                  
  bc72369  mov dword ptr [rsp+0x28],0                    
  bc72371  mov qword ptr [rsp+0x20],0                    
  bc7237a  mov rdx,rbx                                   
  bc7237d  xor r8d,r8d                                   
  bc72380  xor r9d,r9d                                   
  bc72383  call r10                                      
  bc72386  add rsp,0x30                                  
  bc7238a  jmp 0xBC72124                                 ; -> loc_bc72124

loc_bc7238f:  ; from bc7222c
  bc7238f  mov rax,[rbp+0x128]                           
  bc72396  mov [rax],cx                                  
  bc72399  shl ecx,5                                     
  bc7239c  inc word ptr [r8+rcx+0x1E2CACC]               
  bc723a5  mov rcx,[rbx]                                 
  bc723a8  lea rax,[rbx+0x10]                            
  bc723ac  cmp rcx,rax                                   
  bc723af  je short 0xBC723CB                            ; -> loc_bc723cb
  bc723b1  mov rax,[rax]                                 
  bc723b4  test rax,rax                                  
  bc723b7  je short 0xBC723CB                            ; -> loc_bc723cb
  bc723b9  mov rdx,[rbx+0x18]                            
  bc723bd  sub rsp,0x20                                  
  bc723c1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bc723c7  add rsp,0x20                                  

loc_bc723cb:  ; from bc723af, bc723b7
  bc723cb  mov rcx,[0x12ADF800]                          ; [data_12adf800]
  bc723d2  test rcx,rcx                                  
  bc723d5  je 0xBC72130                                  ; -> loc_bc72130
  bc723db  mov rax,[rcx]                                 
  bc723de  mov rax,[rax+8]                               
  bc723e2  mov r10,[0xF99FFA0]                           ; [data_f99ffa0] = sub_eea6040
  bc723e9  sub rsp,0x30                                  
  bc723ed  mov dword ptr [rsp+0x28],0                    
  bc723f5  mov qword ptr [rsp+0x20],0                    
  bc723fe  mov rdx,rbx                                   
  bc72401  xor r8d,r8d                                   
  bc72404  xor r9d,r9d                                   
  bc72407  call r10                                      
  bc7240a  add rsp,0x30                                  
  bc7240e  jmp 0xBC72130                                 ; -> loc_bc72130

loc_bc72413:  ; from bc722ad
  bc72413  mov r9,[rbp+0x108]                            
  bc7241a  movzx ecx,word ptr [r9+0x1DED458]             
  bc72422  movzx edx,word ptr [r9+0x1DED45A]             
  bc7242a  cmp cx,dx                                     
  bc7242d  jae short 0xBC72499                           ; -> loc_bc72499
  bc7242f  movzx eax,cx                                  
  bc72432  lea r8d,[rcx+1]                               
  ... (--max 400)
```

## CALLERS
```
  0xbcc1bf0 sub_bcc1bf0 size 0x738
  0xe9055a0 sub_e9055a0 size 0x2c2
  -- 2 calling function(s)
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

