# ctxpack build 0x56aeff0

STAMP exe=758bacdeef3ede55d45da4418bf0fcdc319dd9992cda79d50560d9a08536f9d8 inputs=data=native_functions.tsv:07ea6058496f3c9340e582f2f9bc57b61494694303373d3389ba71c5842a53a6,data=native_deps.tsv:118356f1f1ba724d2eb40c7fc481ea24319c1aeba9f482039b865d6efece1f8b,data=native_boundary.tsv:058a56d8016eceaff394a955dc2a241d4a8a7d44663fc4cd9102ea82d9ec7315,data=native_boundary_candidates.tsv:b2db6e93be378325c9c8b370ea57463e6e4d762ef5f0a1cae81562abc4635b8c,data=ctx_facts.tsv:d2352cf1ceb26c34830b966be082a5e21a28f989c09fa2d4ecdfb97458b56aab,data=ctx_deadends.md:298967a276b4b7e4454961297c117289bf5ed3fcdf45c3240615fc10ed423c83

## HEADER
  rva        : 0x56aeff0
  size       : 0xff (255 bytes)
  depth      : 
  D-rank     : [open] (not derivable from static data)
  callees    : 2 (direct), depth 1
  callers    : 5

## EXACT LISTING (0x56aeff0..0x56af0ef)
```
sub_56aeff0  [0x56aeff0..0x56b0ff0)  size 0x2000  7 xrefs in
  56aeff0  push rsi                                      
  56aeff1  push rdi                                      
  56aeff2  push rbx                                      
  56aeff3  sub rsp,0x30                                  
  56aeff7  mov rsi,rcx                                   
  56aeffa  mov rax,[rcx+0x20]                            ; R a0+0x20
  56aeffe  test rax,rax                                  
  56af001  je short 0x56AF051                            ; -> loc_56af051
  56af003  lea rdi,[rsp+0x2F]                            
  56af008  nop [rax+rax]                                 ; R *(a0+0x20)+0x0+idx

loc_56af010:  ; from 56af047
  56af010  mov rcx,[rsi+0x18]                            ; R a0+0x18
  56af014  add rax,rcx                                   
  56af017  dec rax                                       
  56af01a  mov rcx,[rsi+8]                               ; R a0+0x8
  56af01e  mov rdx,[rsi+0x10]                            ; R a0+0x10
  56af022  dec rdx                                       
  56af025  and rdx,rax                                   
  56af028  mov r8,[rcx+rdx*8]                            ; R *(a0+0x8)+0x0+idx
  56af02c  movsx rcx,byte ptr [r8+0x58]                  ; R *(*(a0+0x8)+0x0+idx)+0x58
  56af031  inc rcx                                       
  56af034  mov rdx,rdi                                   
  56af037  call 0x56AEA80                                ; -> sub_56aea80
  56af03c  mov rax,[rsi+0x20]                            ; R a0+0x20
  56af040  dec rax                                       
  56af043  mov [rsi+0x20],rax                            ; W a0+0x20
  56af047  jne short 0x56AF010                           ; -> loc_56af010
  56af049  mov qword ptr [rsi+0x18],0                    ; W a0+0x18

loc_56af051:  ; from 56af001
  56af051  mov rcx,[rsi+8]                               ; R a0+0x8
  56af055  test rcx,rcx                                  
  56af058  je short 0x56AF0CD                            ; -> loc_56af0cd
  56af05a  lea rbx,[rsi+8]                               ; R a0+0x8
  56af05e  mov rdi,[rsi+0x10]                            ; R a0+0x10
  56af062  test rdi,rdi                                  
  56af065  jle short 0x56AF09A                           ; -> loc_56af09a
  56af067  inc rdi                                       
  56af06a  jmp short 0x56AF079                           ; -> loc_56af079
  56af06c  nop [rax]                                     

loc_56af070:  ; from 56af084, 56af090
  56af070  dec rdi                                       
  56af073  cmp rdi,1                                     
  56af077  jbe short 0x56AF092                           ; -> loc_56af092

loc_56af079:  ; from 56af06a
  56af079  mov rax,[rbx]                                 ; R a0+0x8+0x0
  56af07c  mov rcx,[rax+rdi*8-0x10]                      ; R *(a0+0x8+0x0)-0x10+idx
  56af081  test rcx,rcx                                  
  56af084  je short 0x56AF070                            ; -> loc_56af070
  56af086  mov edx,0x60                                  
  56af08b  call 0xE935700                                ; -> sub_e935700
  56af090  jmp short 0x56AF070                           ; -> loc_56af070

loc_56af092:  ; from 56af077
  56af092  mov rcx,[rsi+8]                               
  56af096  mov rdi,[rsi+0x10]                            

loc_56af09a:  ; from 56af065
  56af09a  shl rdi,3                                     
  56af09e  cmp rdi,0x1000                                
  56af0a5  jb short 0x56AF0BF                            ; -> loc_56af0bf
  56af0a7  mov rax,[rcx-8]                               
  56af0ab  add rcx,0xFFFFFFFFFFFFFFF8                    
  56af0af  sub rcx,rax                                   
  56af0b2  cmp rcx,0x20                                  
  56af0b6  jae short 0x56AF0D5                           ; -> loc_56af0d5
  56af0b8  add rdi,0x27                                  
  56af0bc  mov rcx,rax                                   

loc_56af0bf:  ; from 56af0a5
  56af0bf  mov rdx,rdi                                   
  56af0c2  call 0xE935700                                ; -> sub_e935700
  56af0c7  xorps xmm0,xmm0                               
  56af0ca  movups [rbx],xmm0                             

loc_56af0cd:  ; from 56af058
  56af0cd  add rsp,0x30                                  
  56af0d1  pop rbx                                       
  56af0d2  pop rdi                                       
  56af0d3  pop rsi                                       
  56af0d4  ret                                           

loc_56af0d5:  ; from 56af0b6
  56af0d5  mov qword ptr [rsp+0x20],0                    
  56af0de  xor ecx,ecx                                   
  56af0e0  xor edx,edx                                   
  56af0e2  xor r8d,r8d                                   
  56af0e5  xor r9d,r9d                                   
  56af0e8  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  56af0ee  int3                                          
  56af0ef  int3                                          
  56af0f0  push rbp                                      
  56af0f1  push r15                                      
  56af0f3  push r14                                      
  56af0f5  push r13                                      
  56af0f7  push r12                                      
  56af0f9  push rsi                                      
  56af0fa  push rdi                                      
  56af0fb  push rbx                                      
  56af0fc  sub rsp,0xA18                                 
  56af103  lea rbp,[rsp+0x80]                            
  56af10b  movaps [rbp+0x980],xmm7                       
  56af112  movaps [rbp+0x970],xmm6                       
  56af119  mov qword ptr [rbp+0x968],0xFFFFFFFFFFFFFFFE  
  56af124  mov [rbp+0x8B8],rcx                           
  56af12b  mov r12,[rbp+0xA00]                           
  56af132  mov r14,[rdx+0x10]                            
  56af136  mov rax,[rdx+0x18]                            
  56af13a  mov [rbp+0x8E0],rax                           
  56af141  lea rax,[rdx+0x28]                            
  56af145  mov [rbp+0x8D0],rax                           
  56af14c  lea r15,[rbp+0x7B8]                           
  56af153  add r9,8                                      
  56af157  mov [rbp+0x8E8],r9                            
  56af15e  xorps xmm6,xmm6                               
  56af161  mov [rbp+0x958],rdx                           
  56af168  lea rax,[rdx+0x60]                            
  56af16c  mov [rbp+0x8D8],rax                           
  56af173  lea rax,[rbp+0x560]                           
  56af17a  mov [rbp+0x964],r8d                           
  56af181  jmp short 0x56AF1A7                           ; -> loc_56af1a7

loc_56af183:  ; from 56b0568
  56af183  add rax,0x28                                  
  56af187  mov rdx,rax                                   
  56af18a  mov rcx,r8                                    

loc_56af18d:  ; from 56b0553
  56af18d  call 0xE935700                                ; -> sub_e935700

loc_56af192:  ; from 56af2d4, 56af2fa, 56b053b
  56af192  add r14,0x290                                 
  56af199  mov r8d,[rbp+0x964]                           
  56af1a0  lea rax,[rbp+0x560]                           

loc_56af1a7:  ; from 56af181
  56af1a7  cmp r14,[rbp+0x8E0]                           
  56af1ae  je 0x56B0577                                  ; -> loc_56b0577
  56af1b4  lea rsi,[r14+0x240]                           
  56af1bb  cmp byte ptr [rbp+0xA08],0                    
  56af1c2  je 0x56AF2D0                                  ; -> loc_56af2d0
  56af1c8  mov rcx,rax                                   
  56af1cb  mov rax,[rbp+0x958]                           
  56af1d2  mov rdi,[rax+8]                               
  56af1d6  lea rax,[0xF25C0D0]                           ; [data_f25c0d0]
  56af1dd  mov [rbp+0x560],rax                           
  56af1e4  mov [rbp+0x568],rsi                           
  56af1eb  mov [rbp+0x598],rcx                           
  56af1f2  mov rbx,[rdi+0xA10]                           
  56af1f9  add rdi,0xA10                                 
  56af200  cmp rbx,rdi                                   
  56af203  jne short 0x56AF23C                           ; -> loc_56af23c
  56af205  xor edi,edi                                   
  56af207  lea rax,[0xF25C0D0]                           ; [data_f25c0d0]
  56af20e  lea rdx,[rbp+0x560]                           
  56af215  mov rcx,rdx                                   
  56af218  lea r15,[rbp+0x7B8]                           
  56af21f  mov r12,[rbp+0xA00]                           
  56af226  jmp 0x56AF2B9                                 ; -> loc_56af2b9
  56af22b  nop [rax+rax]                                 

loc_56af230:  ; from 56af247, 56af25a
  56af230  mov rbx,[rbx]                                 
  56af233  cmp rbx,rdi                                   
  56af236  je 0x56B0570                                  ; -> loc_56b0570

loc_56af23c:  ; from 56af203
  56af23c  mov r15,[rbx+0x10]                            
  56af240  mov r12,[rbx+0x18]                            
  56af244  cmp r15,r12                                   
  56af247  je short 0x56AF230                            ; -> loc_56af230
  56af249  lea r13,[rbx+0x28]                            
  56af24d  jmp short 0x56AF25C                           ; -> loc_56af25c
  56af24f  nop                                           

loc_56af250:  ; from 56af266, 56af290
  56af250  add r15,0xC8                                  
  56af257  cmp r15,r12                                   
  56af25a  je short 0x56AF230                            ; -> loc_56af230

loc_56af25c:  ; from 56af24d
  56af25c  mov eax,[r15]                                 
  56af25f  not eax                                       
  56af261  test eax,0x10000008                           
  56af266  jne short 0x56AF250                           ; -> loc_56af250
  56af268  mov rcx,[rbp+0x598]                           
  56af26f  test rcx,rcx                                  
  56af272  je short 0x56AF2DC                            ; -> loc_56af2dc
  56af274  mov [rbp-0x50],r15                            
  56af278  mov [rbp-0x48],r13                            
  56af27c  mov rax,[rcx]                                 
  56af27f  mov rax,[rax+0x10]                            
  56af283  lea rdx,[rbp-0x50]                            
  56af287  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  56af28d  nop                                           
  56af28e  test al,al                                    
  56af290  je short 0x56AF250                            ; -> loc_56af250
  56af292  mov dil,1                                     

loc_56af295:  ; from 56b0572
  56af295  mov rcx,[rbp+0x598]                           
  56af29c  test rcx,rcx                                  
  56af29f  lea r15,[rbp+0x7B8]                           
  56af2a6  mov r12,[rbp+0xA00]                           
  56af2ad  je short 0x56AF2ED                            ; -> loc_56af2ed
  56af2af  mov rax,[rcx]                                 
  56af2b2  lea rdx,[rbp+0x560]                           

loc_56af2b9:  ; from 56af226
  56af2b9  cmp rcx,rdx                                   
  56af2bc  setne dl                                      
  56af2bf  mov rax,[rax+0x20]                            
  56af2c3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  56af2c9  jmp short 0x56AF2ED                           ; -> loc_56af2ed
  56af2cb  nop [rax+rax]                                 

loc_56af2d0:  ; from 56af1c2
  56af2d0  cmp r8d,2                                     
  56af2d4  ja 0x56AF192                                  ; -> loc_56af192
  56af2da  jmp short 0x56AF300                           ; -> loc_56af300

loc_56af2dc:  ; from 56af272
  56af2dc  mov dil,1                                     
  56af2df  lea r15,[rbp+0x7B8]                           
  56af2e6  mov r12,[rbp+0xA00]                           

loc_56af2ed:  ; from 56af2ad, 56af2c9
  56af2ed  cmp dword ptr [rbp+0x964],3                   
  56af2f4  setb al                                       
  56af2f7  test al,dil                                   
  56af2fa  je 0x56AF192                                  ; -> loc_56af192

loc_56af300:  ; from 56af2da
  56af300  mov rax,[rbp+0x958]                           
  56af307  mov rax,[rax+8]                               
  56af30b  lea r8,[rax+0x9D0]                            
  56af312  mov ecx,[rbp+0x964]                           
  56af318  cmp ecx,1                                     
  56af31b  je short 0x56AF354                            ; -> loc_56af354
  56af31d  test ecx,ecx                                  
  56af31f  jne short 0x56AF387                           ; -> loc_56af387
  56af321  mov [rbp+0x2B0],rsi                           
  56af328  mov rax,[rax+0xA78]                           
  56af32f  mov rdx,[rax]                                 
  56af332  add rdx,0x40                                  
  56af336  lea rax,[rbp+0x5A0]                           
  56af33d  mov [rsp+0x20],rax                            
  56af342  lea rcx,[rbp-0x50]                            
  56af346  lea r9,[rbp+0x2B0]                            
  56af34d  call 0x56B3A10                                ; -> sub_56b3a10
  56af352  jmp short 0x56AF3BF                           ; -> loc_56af3bf

loc_56af354:  ; from 56af31b
  56af354  mov [rbp+0x2B0],rsi                           
  56af35b  mov rax,[rax+0xA78]                           
  56af362  mov rdx,[rax]                                 
  56af365  add rdx,0x40                                  
  56af369  lea rax,[rbp+0x5A0]                           
  56af370  mov [rsp+0x20],rax                            
  56af375  lea rcx,[rbp-0x50]                            
  56af379  lea r9,[rbp+0x2B0]                            
  56af380  call 0x56B3EB0                                ; -> sub_56b3eb0
  56af385  jmp short 0x56AF3BF                           ; -> loc_56af3bf

loc_56af387:  ; from 56af31f
  56af387  mov [rbp+0x5A0],rsi                           
  56af38e  mov [rbp+0x2B0],r14                           
  56af395  mov rax,[rax+0xA78]                           
  56af39c  mov rdx,[rax]                                 
  56af39f  add rdx,0x40                                  
  56af3a3  lea rax,[rbp+0x2B0]                           
  56af3aa  mov [rsp+0x20],rax                            
  56af3af  lea rcx,[rbp-0x50]                            
  56af3b3  lea r9,[rbp+0x5A0]                            
  56af3ba  call 0x56B4360                                ; -> sub_56b4360

loc_56af3bf:  ; from 56af352, 56af385
  56af3bf  mov rdi,[rbp-0x38]                            
  56af3c3  mov rsi,[rbp-0x40]                            
  56af3c7  mov rax,[rbp-0x48]                            
  56af3cb  mov [rbp+0x8C8],rax                           
  56af3d2  movaps xmm7,[rbp-0x50]                        
  56af3d6  mov rax,rdi                                   
  56af3d9  sub rax,rsi                                   
  56af3dc  mov [rbp+0x950],rax                           
  56af3e3  mov rcx,rax                                   
  56af3e6  sar rcx,3                                     
  56af3ea  mov rax,0xAAAAAAAAAAAAAAAB                    
  56af3f4  imul rcx,rax                                  
  56af3f8  mov [rbp+0x8C0],rcx                           
  56af3ff  lea rcx,[rbp+0x7F0]                           
  56af406  mov rdx,[rbp+0x8E8]                           
  56af40d  call 0x76A8A0                                 ; -> sub_76a8a0
  56af412  mov rcx,rsi                                   
  56af415  mov [rbp+0x8B0],rdi                           
  56af41c  mov [rbp+0x948],rsi                           
  56af423  jmp short 0x56AF455                           ; -> loc_56af455
  56af425  nop [rax+rax]                                 ; R ret@76a8a0+0x0+idx

loc_56af430:  ; from 56b04e1, 56b04ef, 56b0508
  56af430  lea rax,[r13*2]                               
  56af438  add rax,r13                                   
  56af43b  mov rbx,[rbp+0x940]                           
  56af442  lea rbx,[rbx+rax*8]                           
  56af446  lea rcx,[rbp+0x5A0]                           
  56af44d  call 0x655CEA0                                ; -> sub_655cea0
  56af452  mov rcx,rbx                                   

loc_56af455:  ; from 56af423
  56af455  cmp rcx,rdi                                   
  56af458  je 0x56B0530                                  ; -> loc_56b0530
  56af45e  mov r13,rdi                                   
  56af461  sub r13,rcx                                   
  56af464  sar r13,3                                     
  56af468  mov rax,0xAAAAAAAAAAAAAAAB                    
  56af472  imul r13,rax                                  
  56af476  cmp r13,0x200                                 
  56af47d  mov eax,0x200                                 
  56af482  cmovae r13,rax                                
  56af486  mov rax,[r14+0x258]                           
  56af48d  mov [rbp+0x5A0],rax                           
  56af494  movups [r15-0x210],xmm6                       
  56af49c  mov rax,[r14+0x268]                           
  56af4a3  test rax,rax                                  
  56af4a6  mov [rbp+0x940],rcx                           
  56af4ad  je short 0x56AF4C0                            ; -> loc_56af4c0
  56af4af  lock inc dword ptr [rax+8]                    
  56af4b3  mov rax,[r14+0x268]                           
  56af4ba  jmp short 0x56AF4C2                           ; -> loc_56af4c2
  56af4bc  nop [rax]                                     

loc_56af4c0:  ; from 56af4ad
  56af4c0  xor eax,eax                                   

loc_56af4c2:  ; from 56af4ba
  56af4c2  mov rcx,[r14+0x260]                           
  56af4c9  mov [rbp+0x5A8],rcx                           
  56af4d0  mov [rbp+0x5B0],rax                           
  56af4d7  movups [r15-0x200],xmm6                       
  56af4df  mov qword ptr [r15-0x1F0],0                   
  56af4ea  mov byte ptr [rbp+0x5D0],1                    
  56af4f1  mov byte ptr [rbp+0x600],0                    
  56af4f8  movups [rbp+0x5D8],xmm7                       
  56af4ff  movups [r15-0x1D0],xmm6                       
  56af507  mov qword ptr [r15-0x1C0],0                   
  56af512  cmp rdi,rsi                                   
  56af515  je 0x56AF5DC                                  ; -> loc_56af5dc
  56af51b  mov rax,0xAAAAAAAAAAAAAAB                     
  56af525  cmp [rbp+0x8C0],rax                           
  56af52c  jae 0x56B05BE                                 ; -> loc_56b05be
  56af532  mov rax,[rbp+0x8C8]                           
  56af539  mov rcx,[rax]                                 
  56af53c  mov r9d,1                                     
  56af542  lea rdx,[rbp-0x50]                            
  56af546  mov r8,[rbp+0x950]                            
  56af54d  call 0xA78940                                 ; -> sub_a78940
  56af552  nop                                           
  56af553  mov rbx,[rbp-0x40]                            
  56af557  mov rax,[rbp-0x50]                            
  56af55b  mov rdi,[rbp-0x48]                            
  56af55f  mov rsi,[rax]                                 
  56af562  test rdi,rdi                                  
  56af565  je short 0x56AF5A0                            ; -> loc_56af5a0
  56af567  lock dec dword ptr [rdi+8]                    
  56af56b  jne short 0x56AF5A0                           ; -> loc_56af5a0
  56af56d  mov rax,[rdi]                                 
  56af570  mov rax,[rax]                                 
  56af573  mov rcx,rdi                                   
  56af576  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  56af57c  lock dec dword ptr [rdi+0xC]                  
  56af580  jne short 0x56AF5A0                           ; -> loc_56af5a0
  56af582  mov rax,[rdi]                                 
  56af585  mov rax,[rax+8]                               
  56af589  mov rcx,rdi                                   
  56af58c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  56af592  nop [rax+rax]                                 

loc_56af5a0:  ; from 56af565, 56af56b, 56af580
  56af5a0  add rsi,rbx                                   
  56af5a3  mov [rbp+0x5E8],rsi                           
  56af5aa  mov [rbp+0x5F0],rsi                           
  56af5b1  mov r8,[rbp+0x950]                            
  56af5b8  lea rdi,[rsi+r8]                              
  56af5bc  mov [rbp+0x5F8],rdi                           
  56af5c3  mov rcx,rsi                                   
  56af5c6  mov rsi,[rbp+0x948]                           
  56af5cd  mov rdx,rsi                                   
  56af5d0  call 0xEEC6DE0                                ; -> sub_eec6de0
  56af5d5  mov [rbp+0x5F0],rdi                           

loc_56af5dc:  ; from 56af515
  56af5dc  mov rax,[rbp+0x940]                           
  56af5e3  sub rax,rsi                                   
  56af5e6  sar rax,3                                     
  56af5ea  mov rcx,0xAAAAAAAAAAAAAAAB                    
  56af5f4  imul rax,rcx                                  
  56af5f8  mov byte ptr [rbp+0x600],1                    
  56af5ff  mov [rbp+0x608],rax                           
  56af606  movups xmm0,[r14+0x118]                       
  56af60e  movups [rbp+0x618],xmm0                       
  56af615  movups xmm0,[r14+0x128]                       
  56af61d  movups [rbp+0x628],xmm0                       
  56af624  movups xmm0,[r14+0x138]                       
  56af62c  movups [rbp+0x638],xmm0                       
  56af633  movups xmm0,[r14+0x148]                       
  56af63b  movups [rbp+0x648],xmm0                       
  56af642  movups xmm0,[r14+0x158]                       
  56af64a  movups [rbp+0x658],xmm0                       
  56af651  movups xmm0,[r14+0x168]                       
  56af659  movups [rbp+0x668],xmm0                       
  56af660  movups xmm0,[r14+0x178]                       
  56af668  movups [rbp+0x678],xmm0                       
  56af66f  movups xmm0,[r14+0x188]                       
  56af677  movups [rbp+0x688],xmm0                       
  56af67e  lea rcx,[r14+0x198]                           
  56af685  mov eax,[rcx+0x10]                            
  56af688  mov [r15-0x110],eax                           
  56af68f  movups xmm0,[rcx]                             
  56af692  movups [r15-0x120],xmm0                       
  56af69a  movups xmm0,[r14+0x1AC]                       
  56af6a2  movups [rbp+0x6AC],xmm0                       
  56af6a9  movups xmm0,[r14+0x1BC]                       
  56af6b1  movups [rbp+0x6BC],xmm0                       
  56af6b8  movups xmm0,[r14+0x1CC]                       
  56af6c0  movups [rbp+0x6CC],xmm0                       
  56af6c7  movups xmm0,[r14+0x1DC]                       
  56af6cf  movups [rbp+0x6DC],xmm0                       
  56af6d6  movups xmm0,[r14+0x1EC]                       
  56af6de  movups [rbp+0x6EC],xmm0                       
  56af6e5  movups xmm0,[r14+0x1FC]                       
  56af6ed  movups [rbp+0x6FC],xmm0                       
  56af6f4  movups xmm0,[r14+0x20C]                       
  56af6fc  movups [rbp+0x70C],xmm0                       
  56af703  movups xmm0,[r14+0x21C]                       
  56af70b  movups [rbp+0x71C],xmm0                       
  56af712  lea rax,[r14+0x22C]                           
  56af719  movups xmm0,[rax]                             
  56af71c  movups [r15-0x8C],xmm0                        
  56af724  mov byte ptr [rbp+0x7B4],0                    
  56af72b  mov rax,[rbp+0x958]                           
  56af732  cmp byte ptr [rax+0xA0],1                     
  56af739  jne 0x56AF7BF                                 ; -> loc_56af7bf
  56af73f  mov rax,[rbp+0x8D0]                           
  56af746  movups xmm0,[rax]                             
  56af749  movups xmm1,[rax+0x10]                        
  56af74d  movups [r15-0x6C],xmm1                        
  56af752  movups [r15-0x7C],xmm0                        
  56af757  mov byte ptr [rbp+0x770],0                    
  56af75e  mov rax,[rbp+0x958]                           
  56af765  cmp byte ptr [rax+0x5C],1                     
  56af769  jne short 0x56AF78E                           ; -> loc_56af78e
  56af76b  mov rcx,[rbp+0x958]                           
  56af772  movzx eax,byte ptr [rcx+0x48]                 
  56af776  mov [rbp+0x75C],al                            
  56af77c  movups xmm0,[rcx+0x4C]                        
  56af780  movaps [rbp+0x760],xmm0                       
  56af787  mov byte ptr [rbp+0x770],1                    

loc_56af78e:  ; from 56af769
  56af78e  mov rax,[rbp+0x8D8]                           
  56af795  movups xmm0,[rax]                             
  56af798  movups xmm1,[rax+0x10]                        
  56af79c  movups xmm2,[rax+0x20]                        
  ... (--max 400)
```

## CALLERS
```
  0x55f1450 sub_55f1450 size 0x4e144
  0x56a0670 sub_56a0670 size 0x26
  0x668ef10 sub_668ef10 size 0x164
  0x668f080 sub_668f080 size 0x1c4a
  0x67c7e10 sub_67c7e10 size 0x248
  -- 5 calling function(s)
```

## CALLEES (signature + status, trust [proven] from exe)
  rva        name               status     signature  trust     boundary  source/dossier
  0x56aea80   sub_56aea80       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_56aea80.cpp;src\client\features\render\native\helpers\sub_56aea80.h
  0xe935700   sub_e935700       set         [open]     [proven]  src=src\client\features\render\native\helpers\sub_e935700.cpp;src\client\features\render\native\helpers\sub_e935700.h

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
  - 0x55f1450 exact call site to 0xbc9ada0 per frame (from docs\progress\oc_U-EM1e_r19.md)
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

