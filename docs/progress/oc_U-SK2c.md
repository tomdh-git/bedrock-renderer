# Progress: U-SK2c sky Cubemap case instruction-complete 0x6659a75 -> 0x665aee8

## NEXT
Unit U-SK2c COMPLETE. Phases 1-49 cover 0x6659a75..0x665aee8 instruction-complete. Cubemap case exit reached at 0x665aee8.

## Method
- `rdis ... dis <rva> <n>` linear disassembly; each phase <= 40 instructions; every instruction quoted exactly as rdis prints it (`0xRVA  mnemonic operands`); interpretation on separate `//` lines after each fence. Instruction-complete: no instruction in 0x6659a75..0x665aee8 is skipped.
- Tags: [V]=seen in disassembly, [I]=inferred, [?]=unknown. All RVAs relative to image base; exe = Minecraft.Windows 1.26.62.01.
- Boundary: 0x6659a75 is a valid instruction start (confirmed by rdis and matches oc_U-SK2b.md Phase C7 start). End boundary 0x665aee8 confirmed by rdis output (`mov rsi,[rbp+0x328]` / `jmp 0x665D124`).

## Phase 1 — Cubemap case start + first switch setup 0x6659a75..0x6659b86 (32 instr) [V]
```
0x6659a75  mov byte ptr [rbp+0x388],8                    
0x6659a7c  mov qword ptr [rbp+0x38C],0                   
0x6659a87  mov qword ptr [rbp+0x392],0                   
0x6659a92  mov byte ptr [rbp+0x39A],0xFF                 
0x6659a99  mov rax,[rbp+0x50]                            
0x6659a9d  mov [rbp+0x3A0],rax                           
0x6659aa4  lea rcx,[rbp+0x3A8]                           
0x6659aab  mov rdx,rbx                                   
0x6659aae  call 0xE869FF0                                ; -> sub_e869ff0
0x6659ab3  nop                                           
0x6659ab4  lea rax,[rbp+0x344]                           
0x6659abb  lea r10,[rbp+0x3A0]                           
0x6659ac2  mov rcx,[rbp+0xD0]                            
0x6659ac9  mov [rbp+0x420],rcx                           
0x6659ad0  mov qword ptr [rbp+0xD0],0                    
0x6659adb  lea r9,[rbp+0x428]                            
0x6659ae2  movups [rbp+0x428],xmm6                       
0x6659ae9  movups [rbp+0x438],xmm7                       
0x6659af0  movups [rbp+0x448],xmm8                       
0x6659af8  movups [rbp+0x458],xmm9                       
0x6659b00  mov byte ptr [rbp+0x468],0                    
0x6659b07  lea r8,[rbp+0x470]                            
0x6659b0e  mov [rbp+0x470],di                            
0x6659b15  lea rdx,[rbp+0x478]                           
0x6659b1c  movaps xmm0,[rbp+0x4E0]                       
0x6659b23  movaps xmm1,[rbp+0x4F0]                       
0x6659b2a  mov qword ptr [rbp+0x4E8],0                   
0x6659b35  movups [rbp+0x478],xmm0                       
0x6659b3c  movaps [rbp+0x4F0],xmm10                      
0x6659b44  movups [rbp+0x488],xmm1                       
0x6659b4b  mov rcx,[rbp+0x500]                           
0x6659b52  mov [rbp+0x498],rcx                           
0x6659b59  mov byte ptr [rbp+0x4B0],0xFF                 
0x6659b60  movzx ecx,byte ptr [rbp+0x518]                
0x6659b67  cmp rcx,3                                     
0x6659b6b  ja 0x665CF8B                                  ; -> sub_665cf8b
0x6659b71  lea r11,[rbp+0x4A0]                           
0x6659b78  lea rdi,[0xF2BF428]                           ; [data_f2bf428]
0x6659b7f  movsxd rbx,[rdi+rcx*4]                        
0x6659b83  add rbx,rdi                                   
0x6659b86  jmp rbx                                       
```
// INTERPRETATION [V]: Finishes fixed descriptor at rbp+0x388..0x39A ([rbp+0x388]=8,[rbp+0x38C]=0,[rbp+0x392]=0,[rbp+0x39A]=0xFF). rax=[rbp+0x50] stored at [rbp+0x3A0] [V]. call 0xE869FF0(rcx=&rbp+0x3A8, rdx=rbx) [V]. Builds args block rbp+0x420..0x4B0: [rbp+0x420]=[rbp+0xD0], [rbp+0xD0]=0, xmm6..xmm9 -> [rbp+0x428..0x468], [rbp+0x470]=di, [rbp+0x4F0]=xmm10, [rbp+0x488]=xmm1, [rbp+0x498]=[rbp+0x500], [rbp+0x4B0]=0xFF [V]. First switch on byte [rbp+0x518] (`cmp rcx,3; ja 0x665CF8B`) with jump table [0xF2BF428] (8 entries, rel32): [0]=0x665cf85, [1]=0x6659b88, [2]=0x6659b9b, [3]=0x665bacc, [4]=0x665aefb, [5]=0x6659553, [6]=0x66595d0, [7]=0x66595e2 [V]. `jmp rbx` dispatches [V]. Cases 5..7 and default are outside 0x6659a75..0x665aee8 or earlier in the function [I].

## Phase 2 — First switch case 1 0x6659b88..0x6659b96 (3 instr) [V]
```
0x6659b88  mov r11,[rbp+0x508]                           
0x6659b8f  mov [rbp+0x4A0],r11                           
0x6659b96  jmp 0x665CF85                                 ; -> sub_665cf85
```
// INTERPRETATION [V]: case 1 (table[1]=0x6659b88): stores [rbp+0x508] into [rbp+0x4A0], jumps to cold join 0x665CF85 (outside unit range) [V].

## Phase 3 — First switch case 2 0x6659b9b..0x6659cad (40 instr) [V]
```
0x6659b9b  movsd xmm0,[rdi+0x30]                         
0x6659ba0  movss xmm1,[rdi+0x38]                         
0x6659ba5  mov rax,[rdi+0x18]                            
0x6659ba9  movups xmm6,[rax]                             
0x6659bac  movaps [rbp+0x170],xmm6                       
0x6659bb3  movups xmm7,[rax+0x10]                        
0x6659bb7  movaps [rbp+0x180],xmm7                       
0x6659bbe  movups xmm8,[rax+0x20]                        
0x6659bc3  movaps [rbp+0x190],xmm8                       
0x6659bcb  movups xmm9,[rax+0x30]                        
0x6659bd0  movaps [rbp+0x1A0],xmm9                       
0x6659bd8  mov byte ptr [rbp+0x1B0],0                    
0x6659bdf  cmp byte ptr [rbp+0x538],0                    
0x6659be6  je 0x665DE4A                                  ; -> sub_665de4a
0x6659bec  mov r14w,[rdi+0x3C]                           
0x6659bf1  mov dword ptr [rbp+0x344],3                   
0x6659bfb  mov byte ptr [rbp+0x348],7                    
0x6659c02  mov dword ptr [rbp+0x34C],1                   
0x6659c0c  mov word ptr [rbp+0x350],1                    
0x6659c15  mov byte ptr [rbp+0x352],2                    
0x6659c1c  mov dword ptr [rbp+0x354],0                   
0x6659c26  mov byte ptr [rbp+0x358],0                    
0x6659c2d  xorps xmm10,xmm10                             
0x6659c31  movups [rbp+0x35C],xmm10                      
0x6659c39  movups [rbp+0x368],xmm10                      
0x6659c41  mov byte ptr [rbp+0x378],8                    
0x6659c48  mov qword ptr [rbp+0x37C],0                   
0x6659c53  mov dword ptr [rbp+0x384],0                   
0x6659c5d  mov byte ptr [rbp+0x388],8                    
0x6659c64  mov qword ptr [rbp+0x38C],0                   
0x6659c6f  mov qword ptr [rbp+0x392],0                   
0x6659c7a  mov byte ptr [rbp+0x39A],0xFF                 
0x6659c81  movlps [rbp+0x3A0],xmm0                       
0x6659c88  movss [rbp+0x3A8],xmm1                        
0x6659c90  mov rax,[rbp+0x50]                            
0x6659c94  mov [rbp+0x3B0],rax                           
0x6659c9b  lea rdi,[rbp+0x3B8]                           
0x6659ca2  mov rcx,rdi                                   
0x6659ca5  mov rdx,rbx                                   
0x6659ca8  call 0xE869FF0                                ; -> sub_e869ff0
0x6659cad  nop                                           
```
// INTERPRETATION [V]: case 2 (table[2]=0x6659b9b): rdi still = jump-table base 0xF2BF428; loads global data [rdi+0x30],[rdi+0x38],[rdi+0x18] [V]. rax=[rdi+0x18]=[0xF2BF440] (pointer in .rdata); copies 64-byte block [rax]..[rax+0x30] into xmm6..xmm9 -> [rbp+0x170],[rbp+0x180],[rbp+0x190],[rbp+0x1A0] (matrix/transform) [V]. [rbp+0x1B0]=0; `cmp byte [rbp+0x538],0; je 0x665DE4A` [V,I]. r14w=[rdi+0x3C] [V]. Rebuilds fixed descriptor rbp+0x344..0x39A (same field values as Phase 1) [V]. movlps [rbp+0x3A0]=xmm0; movss [rbp+0x3A8]=xmm1; rax=[rbp+0x50]; [rbp+0x3B0]=rax [V]. lea rdi,[rbp+0x3B8]; call 0xE869FF0(rcx=&rbp+0x3B8, rdx=rbx=jump-table-target addr) [V].

## Phase 4 — Second switch setup 0x6659cae..0x6659d5e (25 instr) [V]
```
0x6659cae  mov rax,[rbp+0xD0]                            
0x6659cb5  mov [rbp+0x430],rax                           
0x6659cbc  mov qword ptr [rbp+0xD0],0                    
0x6659cc7  movups [rbp+0x438],xmm6                       
0x6659cce  movups [rbp+0x448],xmm7                       
0x6659cd5  movups [rbp+0x458],xmm8                       
0x6659cdd  movups [rbp+0x468],xmm9                       
0x6659ce5  mov byte ptr [rbp+0x478],0                    
0x6659cec  mov [rbp+0x480],r14w                          
0x6659cf4  movaps xmm0,[rbp+0x4E0]                       
0x6659cfb  movaps xmm1,[rbp+0x4F0]                       
0x6659d02  mov qword ptr [rbp+0x4E8],0                   
0x6659d0d  movups [rbp+0x488],xmm0                       
0x6659d14  movaps [rbp+0x4F0],xmm10                      
0x6659d1c  movups [rbp+0x498],xmm1                       
0x6659d23  mov rax,[rbp+0x500]                           
0x6659d2a  mov [rbp+0x4A8],rax                           
0x6659d31  mov byte ptr [rbp+0x4C0],0xFF                 
0x6659d38  movzx eax,byte ptr [rbp+0x518]                
0x6659d3f  cmp rax,3                                     
0x6659d43  ja 0x665BB39                                  ; -> sub_665bb39
0x6659d49  lea rcx,[rbp+0x4B0]                           
0x6659d50  lea rdx,[0xF2BF408]                           ; [data_f2bf408]
0x6659d57  movsxd r8,[rdx+rax*4]                         
0x6659d5b  add r8,rdx                                    
0x6659d5e  jmp r8                                        
```
// INTERPRETATION [V]: Builds second args block rbp+0x430..0x4C0 ([rbp+0x430]=[rbp+0xD0], [rbp+0xD0]=0, xmm6..xmm9 -> [rbp+0x438..0x468], [rbp+0x480]=r14w, [rbp+0x4F0]=xmm10, [rbp+0x498]=[rbp+0x500], [rbp+0x4C0]=0xFF) [V]. Second switch on byte [rbp+0x518] (`cmp rax,3; ja 0x665BB39`) with jump table [0xF2BF408]: [0]=0x665bb33, [1]=0x6659d61, [2]=0x665b6cc, [3]=0x665b6de, [4]=0x665cfd6, [5]=0x665a097, [6]=0x665baa9, [7]=0x665bae4 [V]. `jmp r8` dispatches [V]. Case 0 = 0x665bb33 (outside unit range, >0x665aee8), case 1 = 0x6659d61 (inside), cases 2..3 outside range, default 0x665BB39 outside range [I].

## Phase 5 — Second switch case 1 0x6659d61..0x6659d6f (3 instr) [V]
```
0x6659d61  mov rcx,[rbp+0x508]                           
0x6659d68  mov [rbp+0x4B0],rcx                           
0x6659d6f  jmp 0x665BB33                                 ; -> sub_665bb33
```
// INTERPRETATION [V]: case 1 of second switch: stores [rbp+0x508] into [rbp+0x4B0], jumps to common join 0x665BB33 (outside unit range, >0x665aee8) [V].

## Phase 6 — Fall-through after case-1 jmp 0x6659d74..0x6659db9 (15 instr) [V]
```
0x6659d74  add rdx,rax                                   
0x6659d77  cmp rcx,rdx                                   
0x6659d7a  jae short 0x6659DBA                           ; -> loc_6659dba
0x6659d7c  lea r8,[rdi+8]                                
0x6659d80  sub ecx,eax                                   
0x6659d82  shr ecx,4                                     
0x6659d85  imul eax,ecx,0xFFFFAAAB                       
0x6659d8b  mov [rbp+0x50],ax                             
0x6659d8f  mov byte ptr [rbp+0x52],1                     
0x6659d93  mov byte ptr [rbp+0x34C],0                    
0x6659d9a  mov dword ptr [rsp+0x20],0                    
0x6659da2  lea rcx,[rbp+0x1E0]                           
0x6659da9  lea rdx,[rbp+0x50]                            
0x6659dad  lea r9,[rbp+0x340]                            
0x6659db4  call 0xBCABA00                                ; -> sub_bcaba00
0x6659db9  nop                                           
```
// INTERPRETATION [V]: Linear code after Phase 5's unconditional jmp (not reachable from Phase 5, but within address range). `cmp rcx,rdx; jae short 0x6659DBA` bounds check; if in range, computes index via `sub ecx,eax; shr ecx,4; imul eax,ecx,0xFFFFAAAB` (divide by 16), stores ax at [rbp+0x50], sets [rbp+0x52]=1, [rbp+0x34C]=0, [rsp+0x20]=0, then call 0xBCABA00(rcx=&rbp+0x1E0, rdx=&rbp+0x50, r9=&rbp+0x340) [V,I]. `nop` at 0x6659db9 [V].

## Phase 7 — Search loop result block 0x6659dba..0x6659e14 (13 instr) [V]
```
loc_6659dba:  ; from 6659d7a
0x6659dba  movss xmm0,[rdi+0x80]                         
0x6659dc2  movss [rbp+0x340],xmm0                        
0x6659dca  mov qword ptr [rbp+0x344],0                   
0x6659dd5  mov dword ptr [rbp+0x34C],0                   
0x6659ddf  mov qword ptr [rbp+0x50],1                    
0x6659de7  mov [rbp+0x58],r12                            
0x6659deb  mov rax,[rbp+0x218]                           
0x6659df2  movzx r8d,word ptr [rbp+0x222]                
0x6659dfa  mov edx,r8d                                   
0x6659dfd  shl edx,4                                     
0x6659e00  mov rcx,rax                                   
0x6659e03  test r8d,r8d                                  
0x6659e06  je short 0x6659E2A                            ; -> loc_6659e2a
```
// INTERPRETATION [V]: Jump target from Phase 6's `jae`. Loads float [rdi+0x80] -> xmm0 -> [rbp+0x340] [V]. Zeroes [rbp+0x344],[rbp+0x34C]; [rbp+0x50]=1 [V]. [rbp+0x58]=r12; rax=[rbp+0x218]; r8d=[rbp+0x222] (u16 count); edx=r8d<<4; rcx=rax; `test r8d,r8d; je short 0x6659E2A` — if count==0 skip search loop [V,I].

## Phase 8 — Search loop 0x6659e15..0x6659e29 (7 instr) [V]
```
loc_6659e15:  ; from 6659e26
0x6659e15  mov r10,[rcx]                                 
0x6659e18  cmp [r10+0x28],r8                             
0x6659e1c  je short 0x6659E2A                            ; -> loc_6659e2a
0x6659e1e  add rcx,0x10                                  
0x6659e22  add r9,0xFFFFFFFFFFFFFFF0                     
0x6659e26  jne short 0x6659E15                           ; -> loc_6659e15
0x6659e28  jmp short 0x6659E59                           ; -> loc_6659e59
```
// INTERPRETATION [V]: Search loop (from Phase 7 fall-through when r8d!=0): iterates array at rcx (stride 0x10), comparing [r10+0x28] with r8 (data_129f9fe0 pointer). r9 decrements by 0x10 each iteration (remaining count). `je short 0x6659E2A` on match; `jne short 0x6659E15` loops; `jmp short 0x6659E59` on exhaustion (no match) [V,I].

## Phase 9 — Search loop result 0x6659e2a..0x6659e58 (13 instr) [V]
```
loc_6659e2a:  ; from 6659e06, 6659e1c
0x6659e2a  add rdx,rax                                   
0x6659e2d  cmp rcx,rdx                                   
0x6659e30  jae short 0x6659E59                           ; -> loc_6659e59
0x6659e32  sub ecx,eax                                   
0x6659e34  shr ecx,4                                     
0x6659e37  mov [rbp+0x4E0],cx                            
0x6659e3e  mov byte ptr [rbp+0x4E2],1                    
0x6659e45  lea rdx,[rbp+0x4E0]                           
0x6659e4c  lea r8,[rbp+0x50]                             
0x6659e50  mov rcx,r14                                   
0x6659e53  call 0x5679DB0                                ; -> sub_5679db0
0x6659e58  nop                                           
```
// INTERPRETATION [V]: `add rdx,rax` (rdx=end pointer); `cmp rcx,rdx; jae short 0x6659E59` — if past end, no match. Otherwise `sub ecx,eax; shr ecx,4` computes index, stores cx at [rbp+0x4E0], sets [rbp+0x4E2]=1 [V]. Then call 0x5679DB0(rcx=r14, rdx=&rbp+0x4E0, r8=&rbp+0x50) [V,I]. `nop` [V].

## Phase 10 — Load globals + refcount setup 0x6659e59..0x6659ebc (32 instr) [V]
```
loc_6659e59:  ; from 6659e28, 6659e30
0x6659e59  movsd xmm6,[rdi+0x58]                         
0x6659e5e  movups xmm0,[rdi+0x28]                        
0x6659e62  movaps [rbp+0x4E0],xmm0                       
0x6659e69  movups xmm0,[rdi+0x38]                        
0x6659e6d  movaps [rbp+0x4F0],xmm0                       
0x6659e74  movups xmm0,[rdi+0x48]                        
0x6659e78  movaps [rbp+0x500],xmm0                       
0x6659e7f  movsd [rbp+0x510],xmm6                        
0x6659e87  movsd xmm7,[rdi+0x60]                         
0x6659e8c  movsd [rbp+0x518],xmm7                        
0x6659e94  mov byte ptr [rbp+0x520],0                    
0x6659e9b  movzx r15d,word ptr [rdi+0x68]                
0x6659ea0  mov rax,[rdi]                                 
0x6659ea3  xorps xmm0,xmm0                               
0x6659ea6  movaps [rbp+0x170],xmm0                       
0x6659ead  mov rcx,[rax+0x1B0]                           
0x6659eb4  test rcx,rcx                                  
0x6659eb7  je short 0x6659EBD                            ; -> loc_6659ebd
0x6659eb9  movzx ecx,word ptr [rcx+0x10]                 
```
// INTERPRETATION [V]: Jump target from Phase 8/9 on match or exhaustion. Loads [rdi+0x58]->xmm6->[rbp+0x510]; [rdi+0x28]->xmm0->[rbp+0x4E0]; [rdi+0x38]->xmm0->[rbp+0x4F0]; [rdi+0x48]->xmm0->[rbp+0x500] (vector globals) [V]. [rdi+0x60]->xmm7->[rbp+0x518]; [rbp+0x520]=0; r15d=[rdi+0x68] (u16); rax=[rdi] (object pointer); xmm0=0 -> [rbp+0x170] [V]. rcx=[rax+0x1B0]; `test rcx,rcx; je short 0x6659EBD` — if null skip; else `movzx ecx,word ptr [rcx+0x10]` reads refcount [V,I].

## Phase 11 — Refcount inc / release path 0x6659ebd..0x6659ed8 (7 instr) [V]
```
loc_6659ebd:  ; from 6659eb7
0x6659ebd  mov rcx,[rax+0x1B8]                           
0x6659ec4  test rcx,rcx                                  
0x6659ec7  je 0x665A5DB                                  ; -> loc_665a5db
0x6659ecd  lock inc dword ptr [rcx+8]                    
0x6659ed1  mov rcx,[rax+0x1B8]                           
0x6659ed8  jmp 0x665A5DD                                 ; -> loc_665a5dd
```
// INTERPRETATION [V]: Jump target from Phase 10 when [rax+0x1B0]!=0. rcx=[rax+0x1B8]; `test rcx,rcx; je 0x665A5DB` — if null go to release path. Otherwise `lock inc dword ptr [rcx+8]` (refcount inc), reload rcx=[rax+0x1B8], `jmp 0x665A5DD` (release/decrement path) [V,I].

## Phase 12 — Dead code after unconditional jmp / matrix load 0x6659edd..0x6659f1e (21 instr) [V]
```
0x6659edd  mov rax,[rdi+0x18]                            
0x6659ee1  movups xmm6,[rax]                             
0x6659ee4  movaps [rbp+0x1E0],xmm6                       
0x6659eeb  movups xmm7,[rax+0x10]                        
0x6659eef  movaps [rbp+0x1F0],xmm7                       
0x6659ef6  movups xmm8,[rax+0x20]                        
0x6659efb  movaps [rbp+0x200],xmm8                       
0x6659f03  movups xmm9,[rax+0x30]                        
0x6659f08  movaps [rbp+0x210],xmm9                       
0x6659f10  mov byte ptr [rbp+0x220],0                    
0x6659f17  cmp byte ptr [rbp+0x538],0                    
0x6659f1e  je 0x665DEB0                                  ; -> sub_665deb0
```
// INTERPRETATION [V]: Linear code after Phase 11's unconditional `jmp 0x665A5DD` (not reachable from Phase 11, but within address range). rax=[rdi+0x18]; copies 64-byte block [rax]..[rax+0x30] into xmm6..xmm9 -> [rbp+0x1E0],[rbp+0x1F0],[rbp+0x200],[rbp+0x210] (matrix) [V]. [rbp+0x220]=0; `cmp byte [rbp+0x538],0; je 0x665DEB0` [V,I].

## Phase 13 — Descriptor rebuild + call 0xE869FF0 0x6659f24..0x6659fd2 (38 instr) [V]
```
0x6659f24  mov di,[rdi+0x3C]                             
0x6659f28  mov dword ptr [rbp+0x344],3                   
0x6659f32  mov byte ptr [rbp+0x348],7                    
0x6659f39  mov dword ptr [rbp+0x34C],1                   
0x6659f43  mov word ptr [rbp+0x350],1                    
0x6659f4c  mov byte ptr [rbp+0x352],2                    
0x6659f53  mov dword ptr [rbp+0x354],0                   
0x6659f5d  mov byte ptr [rbp+0x358],0                    
0x6659f64  xorps xmm10,xmm10                             
0x6659f68  movups [rbp+0x35C],xmm10                      
0x6659f70  movups [rbp+0x368],xmm10                      
0x6659f78  mov byte ptr [rbp+0x378],8                    
0x6659f7f  mov qword ptr [rbp+0x37C],0                   
0x6659f8a  mov dword ptr [rbp+0x384],0                   
0x6659f94  mov byte ptr [rbp+0x388],8                    
0x6659f9b  mov qword ptr [rbp+0x38C],0                   
0x6659fa6  mov qword ptr [rbp+0x392],0                   
0x6659fb1  mov byte ptr [rbp+0x39A],0xFF                 
0x6659fb8  mov rax,[rbp+0x50]                            
0x6659fbc  mov [rbp+0x3A0],rax                           
0x6659fc3  lea rcx,[rbp+0x3A8]                           
0x6659fca  mov rdx,rbx                                   
0x6659fcd  call 0xE869FF0                                ; -> sub_e869ff0
0x6659fd2  nop                                           
```
// INTERPRETATION [V]: Jump target from Phase 12's `je 0x665DEB0` fall-through path (when [rbp+0x538]!=0). di=[rdi+0x3C] (u16); rebuilds fixed descriptor rbp+0x344..0x39A (same field values as Phases 1/3) [V]. rax=[rbp+0x50] -> [rbp+0x3A0]; lea rcx,[rbp+0x3A8]; mov rdx,rbx; call 0xE869FF0(rcx=&rbp+0x3A8, rdx=rbx) [V]. `nop` [V].

## Phase 14 — Args block build + third switch setup 0x6659fd3..0x665a0a5 (37 instr) [V]
```
0x6659fd3  lea rax,[rbp+0x344]                           
0x6659fda  lea r10,[rbp+0x3A0]                           
0x6659fe1  mov rcx,[rbp+0xD0]                            
0x6659fe8  mov [rbp+0x420],rcx                           
0x6659fef  mov qword ptr [rbp+0xD0],0                    
0x6659ffa  lea r9,[rbp+0x428]                            
0x665a001  movups [rbp+0x428],xmm6                       
0x665a008  movups [rbp+0x438],xmm7                       
0x665a00f  movups [rbp+0x448],xmm8                       
0x665a017  movups [rbp+0x458],xmm9                       
0x665a01f  mov byte ptr [rbp+0x468],0                    
0x665a026  lea r8,[rbp+0x470]                            
0x665a02d  mov [rbp+0x470],di                            
0x665a034  lea rdx,[rbp+0x478]                           
0x665a03b  movaps xmm0,[rbp+0x4E0]                       
0x665a042  movaps xmm1,[rbp+0x4F0]                       
0x665a049  mov qword ptr [rbp+0x4E8],0                   
0x665a054  movups [rbp+0x478],xmm0                       
0x665a05b  movaps [rbp+0x4F0],xmm10                      
0x665a063  movups [rbp+0x488],xmm1                       
0x665a06a  mov rcx,[rbp+0x500]                           
0x665a071  mov [rbp+0x498],rcx                           
0x665a078  mov byte ptr [rbp+0x4B0],0xFF                 
0x665a07f  movzx ecx,byte ptr [rbp+0x518]                
0x665a086  cmp rcx,3                                     
0x665a08a  ja 0x665CFEC                                  ; -> sub_665cfec
0x665a090  lea r11,[rbp+0x4A0]                           
0x665a097  lea rdi,[0xF2BF418]                           ; [data_f2bf418]
0x665a09e  movsxd rbx,[rdi+rcx*4]                        
0x665a0a2  add rbx,rdi                                   
0x665a0a5  jmp rbx                                       
```
// INTERPRETATION [V]: Builds args block rbp+0x420..0x4B0 ([rbp+0x420]=[rbp+0xD0], [rbp+0xD0]=0, xmm6..xmm9 -> [rbp+0x428..0x468], [rbp+0x470]=di, [rbp+0x4F0]=xmm10, [rbp+0x488]=xmm1, [rbp+0x498]=[rbp+0x500], [rbp+0x4B0]=0xFF) [V]. Third switch on byte [rbp+0x518] (`cmp rcx,3; ja 0x665CFEC`) with jump table [0xF2BF418] (8 entries, rel32): table at 0xF2BF418, entries not individually resolved in this unit [?]. `jmp rbx` dispatches [V]. Case 0 target = 0x665a0a7 (inside range), default = 0x665CFEC (outside range) [I].

## Phase 15 — Third switch case 0 0x665a0a7..0x665a0b5 (3 instr) [V]
```
0x665a0a7  mov r11,[rbp+0x508]                           
0x665a0ae  mov [rbp+0x4A0],r11                           
0x665a0b5  jmp 0x665CFE6                                 ; -> sub_665cfe6
```
// INTERPRETATION [V]: case 0 of third switch: stores [rbp+0x508] into [rbp+0x4A0], jumps to cold join 0x665CFE6 (outside unit range) [V].

## Phase 16 — Shared_ptr release + field reload 0x665a0ba..0x665a137 (23 instr) [V]
```
0x665a0ba  mov rax,[rax]                                 
0x665a0bd  mov [rbp+0x340],rax                           
0x665a0c4  mov qword ptr [rbp+0x348],0                   
0x665a0cf  mov rax,[rbp+0x340]                           
0x665a0d6  mov rax,[rax+0x18]                            
0x665a0da  mov rax,[rax]                                 
0x665a0dd  mov [rbp+0x50],rax                            
0x665a0e1  lea r14,[rbp+0x58]                            
0x665a0e5  mov r8,[r15]                                  
0x665a0e8  mov rdx,[rax+0x170]                           
0x665a0ef  mov rcx,r14                                   
0x665a0f2  call 0xE86B370                                ; -> sub_e86b370
0x665a0f7  nop                                           
0x665a0f8  mov [rbp+0xD0],r15                            
0x665a0ff  mov r15,[rbp+0x348]                           
0x665a106  test r15,r15                                  
0x665a109  je short 0x665A138                            ; -> loc_665a138
0x665a10b  lock dec dword ptr [r15+8]                    
0x665a110  jne short 0x665A138                           ; -> loc_665a138
0x665a112  mov rax,[r15]                                 
0x665a115  mov rax,[rax]                                 
0x665a118  mov rcx,r15                                   
0x665a11b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665a121  lock dec dword ptr [r15+0xC]                  
0x665a126  jne short 0x665A138                           ; -> loc_665a138
0x665a128  mov rax,[r15]                                 
0x665a12b  mov rax,[rax+8]                               
0x665a12f  mov rcx,r15                                   
0x665a132  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
// INTERPRETATION [V]: rax=[rax] (deref); [rbp+0x340]=rax; [rbp+0x348]=0; rax=[rbp+0x340]; rax=[rax+0x18]; rax=[rax]; [rbp+0x50]=rax (chain of pointer loads) [V]. lea r14,[rbp+0x58]; r8=[r15]; rdx=[rax+0x170]; rcx=r14; call 0xE86B370(rcx=&rbp+0x58, rdx=[rax+0x170], r8=r15) [V,I]. `nop` [V]. [rbp+0xD0]=r15; r15=[rbp+0x348]; `test r15,r15; je short 0x665A138` — if r15==0 skip release. Otherwise `lock dec dword ptr [r15+8]` (refcount dec); `jne short 0x665A138` — if not zero skip destructor. Otherwise call qword ptr [0xF99FFA0] (sub_eea6040, destructor) on r15, then `lock dec dword ptr [r15+0xC]` (weak ref dec), `jne short 0x665A138`, else call sub_eea6040 again (deallocate) [V,I].

## Phase 17 — Search loop setup 0x665a138..0x665a17a (17 instr) [V]
```
loc_665a138:  ; from 665a109, 665a110, 665a126
0x665a138  mov rax,[rbp+0x98]                            
0x665a13f  movzx r8d,word ptr [rbp+0xA2]                 
0x665a147  mov ecx,r8d                                   
0x665a14a  shl ecx,4                                     
0x665a14d  lea rdx,[rcx+rcx*2]                           
0x665a151  mov rcx,rax                                   
0x665a154  test r8,r8                                    
0x665a157  je short 0x665A17B                            ; -> loc_665a17b
0x665a159  mov r8,[0x129F8318]                           ; [data_129f8318]
0x665a160  mov r9,rdx                                    
0x665a163  mov rcx,rax                                   
```
```
// INTERPRETATION [V]: Jump target from Phase 16 release paths. rax=[rbp+0x98]; r8d=[rbp+0xA2] (u16 count); ecx=r8d<<4; rdx=rcx+rcx*2 (=rcx*3, byte stride 48); rcx=rax; `test r8,r8; je short 0x665A17B` — if count==0 skip search. Otherwise r8=[0x129F8318] (search key pointer), r9=rdx (remaining bytes), rcx=rax (array base) [V,I].
```

## Phase 18 — Search loop 0x665a166..0x665a17a (5 instr) [V]
```
loc_665a166:  ; from 665a177
0x665a166  mov r10,[rcx]                                 
0x665a169  cmp [r10+0x28],r8                             
0x665a16d  je short 0x665A17B                            ; -> loc_665a17b
0x665a16f  add rcx,0x30                                  
0x665a173  add r9,0xFFFFFFFFFFFFFFD0                     
0x665a177  jne short 0x665A166                           ; -> loc_665a166
0x665a179  jmp short 0x665A1E0                           ; -> loc_665a1e0
```
```
// INTERPRETATION [V]: Search loop (stride 0x30): iterates array at rcx, comparing [r10+0x28] with r8 (data_129f8318). r9 decrements by 0xFFFFFFD0 (= -48) each iteration. `je short 0x665A17B` on match; `jne short 0x665A166` loops; `jmp short 0x665A1E0` on exhaustion [V,I].
```

## Phase 19 — Search loop result 0x665a17b..0x665a1df (21 instr) [V]
```
loc_665a17b:  ; from 665a157, 665a16d
0x665a17b  add rdx,rax                                   
0x665a17e  cmp rcx,rdx                                   
0x665a181  jae short 0x665A1E0                           ; -> loc_665a1e0
0x665a183  sub ecx,eax                                   
0x665a185  shr ecx,4                                     
0x665a188  imul eax,ecx,0xFFFFAAAB                       
0x665a18e  mov [rbp+0x1E0],ax                            
0x665a195  mov byte ptr [rbp+0x1E2],1                    
0x665a19c  mov word ptr [rbp+0x340],5                    
0x665a1a5  mov dword ptr [rbp+0x344],0                   
0x665a1af  mov byte ptr [rbp+0x348],0                    
0x665a1b6  mov byte ptr [rbp+0x34C],1                    
0x665a1bd  mov dword ptr [rsp+0x20],0                    
0x665a1c5  lea rcx,[rbp+0x50]                            
0x665a1c9  lea rdx,[rbp+0x1E0]                           
0x665a1d0  lea r9,[rbp+0x340]                            
0x665a1d7  mov r8,rdi                                    
0x665a1da  call 0xBCABA00                                ; -> sub_bcaba00
0x665a1df  nop                                           
```
```
// INTERPRETATION [V]: `add rdx,rax` (rdx=end); `cmp rcx,rdx; jae short 0x665A1E0` — if past end, no match. Otherwise computes index `sub ecx,eax; shr ecx,4; imul eax,ecx,0xFFFFAAAB` -> [rbp+0x1E0]=ax; [rbp+0x1E2]=1; [rbp+0x340]=5 (word); [rbp+0x344]=0; [rbp+0x348]=0; [rbp+0x34C]=1; [rsp+0x20]=0; call 0xBCABA00(rcx=&rbp+0x50, rdx=&rbp+0x1E0, r9=&rbp+0x340, r8=rdi) [V,I]. `nop` [V].
```

## Phase 20 — Global read + call 0x56D55E0 0x665a1e0..0x665a21f (16 instr) [V]
```
loc_665a1e0:  ; from 665a179, 665a181
0x665a1e0  mov eax,[0x129F9C38]                          ; [data_129f9c38]
0x665a1e6  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x665a1ec  mov rdx,gs:[0x58]                             
0x665a1f5  mov rcx,[rdx+rcx*8]                           
0x665a1f9  cmp eax,[rcx+4]                               
0x665a1ff  jg 0x665DC05                                  ; -> sub_665dc05
0x665a205  lea r9,[rdi+0x10]                             
0x665a209  lea r8,[0x129F9C30]                           ; [data_129f9c30]
0x665a210  lea rdx,[rbp+0x340]                           
0x665a217  mov rcx,r14                                   
0x665a21a  call 0x56D55E0                                ; -> sub_56d55e0
0x665a21f  nop                                           
```
// INTERPRETATION [V]: Jump target from Phase 18/19 on exhaustion or no match. eax=[0x129F9C38] (global counter); ecx=[0x128767C8] (global index); rdx=gs:[0x58] (TEB); rcx=[rdx+rcx*8] (array element); `cmp eax,[rcx+4]; jg 0x665DC05` — bounds check against cold path. Otherwise lea r9,[rdi+0x10]; lea r8,[0x129F9C30]; lea rdx,[rbp+0x340]; rcx=r14; call 0x56D55E0(rcx=r14, rdx=&rbp+0x340, r8=&0x129F9C30, r9=&rdi+0x10) [V,I]. `nop` [V].

## Phase 21 — Branch on [rdi+0x52] 0x665a220..0x665a27e (16 instr) [V]
```
0x665a220  cmp byte ptr [rdi+0x52],1                     
0x665a224  jne 0x665A411                                 ; -> loc_665a411
0x665a22a  movups xmm6,[rdi+0x10]                        
0x665a22e  movaps [rbp+0x4E0],xmm6                       
0x665a235  movups xmm7,[rdi+0x20]                        
0x665a239  movaps [rbp+0x4F0],xmm7                       
0x665a240  movups xmm8,[rdi+0x30]                        
0x665a245  movaps [rbp+0x500],xmm8                       
0x665a24d  movups xmm9,[rdi+0x40]                        
0x665a252  movaps [rbp+0x510],xmm9                       
0x665a25a  mov byte ptr [rbp+0x520],0                    
0x665a261  mov di,[rdi+0x50]                             
0x665a265  add rbx,0x358                                 
0x665a26c  mov rdx,[rsi]                                 
0x665a26f  lea rcx,[rbp+0x1E0]                           
0x665a276  mov r8,rbx                                    
0x665a279  call 0x66A6190                                ; -> sub_66a6190
0x665a27e  nop                                           
```
// INTERPRETATION [V]: `cmp byte [rdi+0x52],1; jne 0x665A411` — if flag != 1, go to alternate path (Phase 25). If == 1: loads [rdi+0x10],[rdi+0x20],[rdi+0x30],[rdi+0x40] -> xmm6..xmm9 -> [rbp+0x4E0],[rbp+0x4F0],[rbp+0x500],[rbp+0x510] (vector globals) [V]. [rbp+0x520]=0; di=[rdi+0x50] (u16); rbx += 0x358; rdx=[rsi]; rcx=&rbp+0x1E0; r8=rbx; call 0x66A6190(rcx=&rbp+0x1E0, rdx=[rsi], r8=rbx+0x358) [V,I]. `nop` [V].

## Phase 22 — Descriptor rebuild (path 1) 0x665a27f..0x665a3fc (56 instr) — split into two phases
```
0x665a27f  mov dword ptr [rbp+0x344],0                   
0x665a289  mov byte ptr [rbp+0x348],7                    
0x665a290  mov dword ptr [rbp+0x34C],2                   
0x665a29a  mov word ptr [rbp+0x350],1                    
0x665a2a3  mov byte ptr [rbp+0x352],2                    
0x665a2aa  mov dword ptr [rbp+0x354],0                   
0x665a2b4  mov byte ptr [rbp+0x358],0                    
0x665a2bb  xorps xmm10,xmm10                             
0x665a2bf  movups [rbp+0x35C],xmm10                      
0x665a2c7  movups [rbp+0x368],xmm10                      
0x665a2cf  mov byte ptr [rbp+0x378],8                    
0x665a2d6  mov qword ptr [rbp+0x37C],0                   
0x665a2e1  mov dword ptr [rbp+0x384],0                   
0x665a2eb  mov byte ptr [rbp+0x388],8                    
0x665a2f2  mov qword ptr [rbp+0x38C],0                   
0x665a2fd  mov qword ptr [rbp+0x392],0                   
0x665a308  mov byte ptr [rbp+0x39A],0xFF                 
0x665a30f  mov rax,[rbp+0x50]                            
0x665a313  mov [rbp+0x3A0],rax                           
0x665a31a  lea rcx,[rbp+0x3A8]                           
0x665a321  mov rdx,r14                                   
0x665a324  call 0xE869FF0                                ; -> sub_e869ff0
0x665a329  nop                                           
```
```
// INTERPRETATION [V]: Rebuilds descriptor rbp+0x344..0x39A (variant: [rbp+0x344]=0,[rbp+0x34C]=2 instead of 3/1) [V]. rax=[rbp+0x50] -> [rbp+0x3A0]; lea rcx,[rbp+0x3A8]; mov rdx,r14; call 0xE869FF0(rcx=&rbp+0x3A8, rdx=r14) [V]. `nop` [V].
```

## Phase 23 — Args block build + fourth switch setup 0x665a32a..0x665a3fc (25 instr) [V]
```
0x665a32a  lea rax,[rbp+0x344]                           
0x665a331  lea r10,[rbp+0x3A0]                           
0x665a338  mov rcx,[rbp+0xD0]                            
0x665a33f  mov [rbp+0x420],rcx                           
0x665a346  mov qword ptr [rbp+0xD0],0                    
0x665a351  lea r9,[rbp+0x428]                            
0x665a358  movups [rbp+0x428],xmm6                       
0x665a35f  movups [rbp+0x438],xmm7                       
0x665a366  movups [rbp+0x448],xmm8                       
0x665a36e  movups [rbp+0x458],xmm9                       
0x665a376  mov byte ptr [rbp+0x468],0                    
0x665a37d  lea r8,[rbp+0x470]                            
0x665a384  mov [rbp+0x470],di                            
0x665a38b  lea rdx,[rbp+0x478]                           
0x665a392  movaps xmm0,[rbp+0x1E0]                       
0x665a399  movaps xmm1,[rbp+0x1F0]                       
0x665a3a0  mov qword ptr [rbp+0x1E8],0                   
0x665a3ab  movups [rbp+0x478],xmm0                       
0x665a3b2  movaps [rbp+0x1F0],xmm10                      
0x665a3ba  movups [rbp+0x488],xmm1                       
0x665a3c1  mov rcx,[rbp+0x200]                           
0x665a3c8  mov [rbp+0x498],rcx                           
0x665a3cf  mov byte ptr [rbp+0x4B0],0xFF                 
0x665a3d6  movzx ecx,byte ptr [rbp+0x218]                
0x665a3dd  cmp rcx,3                                     
0x665a3e1  ja 0x665C26F                                  ; -> sub_665c26f
0x665a3e7  lea r11,[rbp+0x4A0]                           
0x665a3ee  lea rdi,[0xF2BF458]                           ; [data_f2bf458]
0x665a3f5  movsxd rbx,[rdi+rcx*4]                        
0x665a3f9  add rbx,rdi                                   
0x665a3fc  jmp rbx                                       
```
// INTERPRETATION [V]: Builds args block rbp+0x420..0x4B0 (variant: uses xmm0=[rbp+0x1E0], xmm1=[rbp+0x1F0] instead of [rbp+0x4E0],[rbp+0x4F0]; [rbp+0x498]=[rbp+0x200] instead of [rbp+0x500]) [V]. Fourth switch on byte [rbp+0x218] (`cmp rcx,3; ja 0x665C26F`) with jump table [0xF2BF458]: table entries not individually resolved [?]. `jmp rbx` dispatches [V]. Case 0 target = 0x665a3fe (inside range), default = 0x665C26F (outside range) [I].

## Phase 24 — Fourth switch case 0 0x665a3fe..0x665a40c (3 instr) [V]
```
0x665a3fe  mov r11,[rbp+0x208]                           
0x665a405  mov [rbp+0x4A0],r11                           
0x665a40c  jmp 0x665C269                                 ; -> sub_665c269
```
// INTERPRETATION [V]: case 0 of fourth switch: stores [rbp+0x208] into [rbp+0x4A0], jumps to cold join 0x665C269 (outside unit range) [V].

## Phase 25 — Alternate path ([rdi+0x52]!=1) 0x665a411..0x665a466 (18 instr) [V]
```
loc_665a411:  ; from 665a224
0x665a411  movups xmm6,[rdi+0x10]                        
0x665a415  movaps [rbp+0x170],xmm6                       
0x665a41c  movups xmm7,[rdi+0x20]                        
0x665a420  movaps [rbp+0x180],xmm7                       
0x665a427  movups xmm8,[rdi+0x30]                        
0x665a42c  movaps [rbp+0x190],xmm8                       
0x665a434  movups xmm9,[rdi+0x40]                        
0x665a439  movaps [rbp+0x1A0],xmm9                       
0x665a441  mov byte ptr [rbp+0x1B0],0                    
0x665a448  mov r15w,[rdi+0x50]                           
0x665a44d  add rbx,0x358                                 
0x665a454  mov rdx,[rsi]                                 
0x665a457  lea rcx,[rbp+0x4E0]                           
0x665a45e  mov r8,rbx                                    
0x665a461  call 0x66A6190                                ; -> sub_66a6190
0x665a466  nop                                           
```
// INTERPRETATION [V]: Jump target from Phase 21's `jne 0x665A411`. Loads [rdi+0x10..0x40] -> xmm6..xmm9 -> [rbp+0x170],[rbp+0x180],[rbp+0x190],[rbp+0x1A0] (matrix) [V]. [rbp+0x1B0]=0; r15w=[rdi+0x50] (u16); rbx += 0x358; rdx=[rsi]; rcx=&rbp+0x4E0; r8=rbx; call 0x66A6190(rcx=&rbp+0x4E0, rdx=[rsi], r8=rbx+0x358) [V,I]. `nop` [V].

## Phase 26 — Descriptor rebuild (path 2) 0x665a467..0x665a5c5 (39 instr) [V]
```
0x665a467  mov dword ptr [rbp+0x344],0                   
0x665a471  mov byte ptr [rbp+0x348],7                    
0x665a478  mov dword ptr [rbp+0x34C],2                   
0x665a482  mov word ptr [rbp+0x350],1                    
0x665a48b  mov byte ptr [rbp+0x352],2                    
0x665a492  mov dword ptr [rbp+0x354],0                   
0x665a49c  mov byte ptr [rbp+0x358],0                    
0x665a4a3  xorps xmm10,xmm10                             
0x665a4a7  movups [rbp+0x35C],xmm10                      
0x665a4af  movups [rbp+0x368],xmm10                      
0x665a4b7  mov byte ptr [rbp+0x378],8                    
0x665a4be  mov qword ptr [rbp+0x37C],0                   
0x665a4c9  mov dword ptr [rbp+0x384],0                   
0x665a4d3  mov byte ptr [rbp+0x388],8                    
0x665a4da  mov qword ptr [rbp+0x38C],0                   
0x665a4e5  mov qword ptr [rbp+0x392],0                   
0x665a4f0  mov byte ptr [rbp+0x39A],0xFF                 
0x665a4f7  mov rax,[rbp+0x50]                            
0x665a4fb  mov [rbp+0x3A0],rax                           
0x665a502  lea rdi,[rbp+0x3A8]                           
0x665a509  mov rcx,rdi                                   
0x665a50c  mov rdx,r14                                   
0x665a50f  call 0xE869FF0                                ; -> sub_e869ff0
0x665a514  nop                                           
0x665a515  mov rax,[rbp+0xD0]                            
0x665a51c  mov [rbp+0x420],rax                           
0x665a523  mov qword ptr [rbp+0xD0],0                    
0x665a52e  movups [rbp+0x428],xmm6                       
0x665a535  movups [rbp+0x438],xmm7                       
0x665a53c  movups [rbp+0x448],xmm8                       
0x665a544  movups [rbp+0x458],xmm9                       
0x665a54c  mov byte ptr [rbp+0x468],0                    
0x665a553  mov [rbp+0x470],r15w                          
0x665a55b  movaps xmm0,[rbp+0x4E0]                       
0x665a562  movaps xmm1,[rbp+0x4F0]                       
0x665a569  mov qword ptr [rbp+0x4E8],0                   
0x665a574  movups [rbp+0x478],xmm0                       
0x665a57b  movaps [rbp+0x4F0],xmm10                      
0x665a583  movups [rbp+0x488],xmm1                       
0x665a58a  mov rax,[rbp+0x500]                           
0x665a591  mov [rbp+0x498],rax                           
0x665a598  mov byte ptr [rbp+0x4B0],0xFF                 
0x665a59f  movzx eax,byte ptr [rbp+0x518]                
0x665a5a6  cmp rax,3                                     
0x665a5aa  ja 0x665C390                                  ; -> sub_665c390
0x665a5b0  lea rcx,[rbp+0x4A0]                           
0x665a5b7  lea rdx,[0xF2BF448]                           ; [data_f2bf448]
0x665a5be  movsxd r8,[rdx+rax*4]                         
0x665a5c2  add r8,rdx                                    
0x665a5c5  jmp r8                                        
```
// INTERPRETATION [V]: Rebuilds descriptor rbp+0x344..0x39A (variant: [rbp+0x344]=0,[rbp+0x34C]=2) [V]. rax=[rbp+0x50] -> [rbp+0x3A0]; lea rdi,[rbp+0x3A8]; rcx=rdi; rdx=r14; call 0xE869FF0(rcx=&rbp+0x3A8, rdx=r14) [V]. `nop` [V]. Builds args block rbp+0x420..0x4B0 ([rbp+0x420]=[rbp+0xD0], [rbp+0xD0]=0, xmm6..xmm9 -> [rbp+0x428..0x468], [rbp+0x470]=r15w, [rbp+0x4F0]=xmm10, [rbp+0x488]=xmm1, [rbp+0x498]=[rbp+0x500], [rbp+0x4B0]=0xFF) [V]. Fifth switch on byte [rbp+0x518] (`cmp rax,3; ja 0x665C390`) with jump table [0xF2BF448]: case 0 target = 0x665a5c8 (inside range), default = 0x665C390 (outside range) [V,I]. `jmp r8` dispatches [V].

## Phase 27 — Fifth switch case 0 0x665a5c8..0x665a5d6 (3 instr) [V]
```
0x665a5c8  mov rcx,[rbp+0x508]                           
0x665a5cf  mov [rbp+0x4A0],rcx                           
0x665a5d6  jmp 0x665C38A                                 ; -> sub_665c38a
```
// INTERPRETATION [V]: case 0 of fifth switch: stores [rbp+0x508] into [rbp+0x4A0], jumps to cold join 0x665C38A (outside unit range) [V].

## Phase 28 — Shared_ptr release + refcount path 0x665a5db..0x665a628 (24 instr) [V]
```
loc_665a5db:  ; from 6659ec7
0x665a5db  xor ecx,ecx                                   
loc_665a5dd:  ; from 6659ed8
0x665a5dd  mov rax,[rax+0x1B0]                           
0x665a5e4  mov [rbp+0x170],rax                           
0x665a5eb  mov rdi,[rbp+0x178]                           
0x665a5f2  mov [rbp+0x178],rcx                           
0x665a5f9  test rdi,rdi                                  
0x665a5fc  je short 0x665A629                            ; -> loc_665a629
0x665a5fe  lock dec dword ptr [rdi+8]                    
0x665a602  jne short 0x665A629                           ; -> loc_665a629
0x665a604  mov rax,[rdi]                                 
0x665a607  mov rax,[rax]                                 
0x665a60a  mov rcx,rdi                                   
0x665a60d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665a613  lock dec dword ptr [rdi+0xC]                  
0x665a617  jne short 0x665A629                           ; -> loc_665a629
0x665a619  mov rax,[rdi]                                 
0x665a61c  mov rax,[rax+8]                               
0x665a620  mov rcx,rdi                                   
0x665a623  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
```
// INTERPRETATION [V]: Jump target from Phase 11 (`je 0x665A5DB`) and Phase 11 (`jmp 0x665A5DD`). ecx=0; rax=[rax+0x1B0]; [rbp+0x170]=rax; rdi=[rbp+0x178]; [rbp+0x178]=rcx (0) [V]. `test rdi,rdi; je short 0x665A629` — if rdi==0 skip release. Otherwise `lock dec dword ptr [rdi+8]` (refcount dec); `jne short 0x665A629` — if not zero skip destructor. Otherwise call qword ptr [0xF99FFA0] (sub_eea6040, destructor) on rdi, then `lock dec dword ptr [rdi+0xC]` (weak ref dec), `jne short 0x665A629`, else call sub_eea6040 again (deallocate) [V,I].
```

## Phase 29 — Call 0x66A0F60 + descriptor rebuild 0x665a629..0x665a712 (38 instr) [V]
```
loc_665a629:  ; from 665a5fc, 665a602, 665a617
0x665a629  mov r8,[rbx+0x3B8]                            
0x665a630  mov rdx,[rsi]                                 
0x665a633  mov [rsp+0x20],r13d                           
0x665a638  mov dword ptr [rsp+0x30],0                    
0x665a640  mov dword ptr [rsp+0x28],0                    
0x665a648  lea rcx,[rbp+0x50]                            
0x665a64c  lea r9,[rbp+0x170]                            
0x665a653  call 0x66A0F60                                ; -> sub_66a0f60
0x665a658  nop                                           
0x665a659  mov dword ptr [rbp+0x344],7                   
0x665a663  mov byte ptr [rbp+0x348],7                    
0x665a66a  mov dword ptr [rbp+0x34C],1                   
0x665a674  mov word ptr [rbp+0x350],1                    
0x665a67d  mov byte ptr [rbp+0x352],2                    
0x665a684  mov dword ptr [rbp+0x354],0                   
0x665a68e  mov byte ptr [rbp+0x358],0                    
0x665a695  xorps xmm0,xmm0                               
0x665a698  movups [rbp+0x35C],xmm0                       
0x665a69f  movups [rbp+0x368],xmm0                       
0x665a6a6  mov byte ptr [rbp+0x378],8                    
0x665a6ad  mov qword ptr [rbp+0x37C],0                   
0x665a6b8  mov dword ptr [rbp+0x384],0                   
0x665a6c2  mov byte ptr [rbp+0x388],8                    
0x665a6c9  mov qword ptr [rbp+0x38C],0                   
0x665a6d4  mov qword ptr [rbp+0x392],0                   
0x665a6df  mov byte ptr [rbp+0x39A],0xFF                 
0x665a6e6  movlps [rbp+0x39C],xmm6                       
0x665a6ed  movss [rbp+0x3A4],xmm7                        
0x665a6f5  mov rax,[rbp+0x1E0]                           
0x665a6fc  mov [rbp+0x3A8],rax                           
0x665a703  lea rcx,[rbp+0x3B0]                           
0x665a70a  mov rdx,r14                                   
0x665a70d  call 0xE869FF0                                ; -> sub_e869ff0
0x665a712  nop                                           
```
// INTERPRETATION [V]: Jump target from Phase 28 release paths. r8=[rbx+0x3B8]; rdx=[rsi]; [rsp+0x20]=r13d; [rsp+0x30]=0; [rsp+0x28]=0; lea rcx,[rbp+0x50]; lea r9,[rbp+0x170]; call 0x66A0F60(rcx=&rbp+0x50, rdx=[rsi], r9=&rbp+0x170, r8=[rbx+0x3B8]) [V,I]. `nop` [V]. Rebuilds descriptor rbp+0x344..0x39A (variant: [rbp+0x344]=7,[rbp+0x34C]=1; movlps [rbp+0x39C]=xmm6; movss [rbp+0x3A4]=xmm7; [rbp+0x3A8]=[rbp+0x1E0]) [V]. lea rcx,[rbp+0x3B0]; rdx=r14; call 0xE869FF0(rcx=&rbp+0x3B0, rdx=r14) [V]. `nop` [V].

## Phase 30 — Select on [rbp+0x520] 0x665a713..0x665a782 (19 instr) [V]
```
0x665a713  mov rax,[rbp+0x260]                           
0x665a71a  mov [rbp+0x428],rax                           
0x665a721  mov qword ptr [rbp+0x260],0                   
0x665a72c  mov byte ptr [rbp+0x470],0xFF                 
0x665a733  movzx eax,byte ptr [rbp+0x520]                
0x665a73a  movzx ecx,al                                  
0x665a73d  cmp ecx,1                                     
0x665a740  jg short 0x665A787                            ; -> loc_665a787
0x665a742  test ecx,ecx                                  
0x665a744  jne 0x665B5F3                                 ; -> loc_665b5f3
0x665a74a  movaps xmm0,[rbp+0x4E0]                       
0x665a751  movaps xmm1,[rbp+0x4F0]                       
0x665a758  movaps xmm2,[rbp+0x500]                       
0x665a75f  movaps xmm3,[rbp+0x510]                       
0x665a766  movups [rbp+0x430],xmm0                       
0x665a76d  movups [rbp+0x440],xmm1                       
0x665a774  movups [rbp+0x450],xmm2                       
0x665a77b  movups [rbp+0x460],xmm3                       
0x665a782  jmp 0x665B624                                 ; -> loc_665b624
```
// INTERPRETATION [V]: rax=[rbp+0x260]; [rbp+0x428]=rax; [rbp+0x260]=0; [rbp+0x470]=0xFF; eax=[rbp+0x520] (byte); ecx=eax; `cmp ecx,1; jg short 0x665A787` — if >1 go to Phase 31. `test ecx,ecx; jne 0x665B5F3` — if ==1 go to cold (outside range). If ==0: loads xmm0=[rbp+0x4E0], xmm1=[rbp+0x4F0], xmm2=[rbp+0x500], xmm3=[rbp+0x510] -> [rbp+0x430],[rbp+0x440],[rbp+0x450],[rbp+0x460] (vector copy) [V]. `jmp 0x665B624` (outside unit range) [V].

## Phase 31 — Select case 2 0x665a787..0x665a79e (6 instr) [V]
```
loc_665a787:  ; from 665a740
0x665a787  cmp ecx,2                                     
0x665a78a  jne 0x665B62A                                 ; -> loc_665b62a
0x665a790  mov rcx,[rbp+0x4E0]                           
0x665a797  mov [rbp+0x430],rcx                           
0x665a79e  jmp 0x665B624                                 ; -> loc_665b624
```
// INTERPRETATION [V]: Jump target from Phase 30's `jg short 0x665A787` (when [rbp+0x520] > 1). `cmp ecx,2; jne 0x665B62A` — if !=2 go to cold (outside range). If ==2: rcx=[rbp+0x4E0]; [rbp+0x430]=rcx (qword copy, scalar variant of Phase 30's vector copy) [V]. `jmp 0x665B624` (outside unit range) [V].

## Phase 32 — Shared setup + call 0x67EA0D0 0x665a7a3..0x665a842 (32 instr) [V]
```
0x665a7a3  xor edi,edi                                   
0x665a7a5  mov rbx,[rbp+0x78]                            
0x665a7a9  mov [rbp+0x4A8],rbx                           
0x665a7b0  mov [rbp+0x4B0],rdi                           
0x665a7b7  mov [rbp+0x4B8],cl                            
0x665a7bd  mov rcx,[rbp+0xA0]                            
0x665a7c4  mov [rbp+0x4D0],rcx                           
0x665a7cb  movaps xmm0,[rbp+0x90]                        
0x665a7d2  movups [rbp+0x4C0],xmm0                       
0x665a7d9  mov ecx,0x9D0                                 
0x665a7de  add rcx,[rsi+0x10]                            
0x665a7e2  mov [rsp+0x30],rax                            
0x665a7e7  mov [rsp+0x28],r10                            
0x665a7ec  mov [rsp+0x20],r11                            
0x665a7f1  call 0x67EA0D0                                ; -> sub_67ea0d0
0x665a7f6  nop                                           
0x665a7f7  lea rcx,[rbp+0x340]                           
0x665a7fe  call 0x673CB40                                ; -> sub_673cb40
0x665a803  cmp byte ptr [rbp+0x88],3                     
0x665a80a  jne short 0x665A843                           ; -> loc_665a843
0x665a80c  mov rsi,[rbp+0x80]                            
0x665a813  test rsi,rsi                                  
0x665a816  je short 0x665A843                            ; -> loc_665a843
0x665a818  lock dec dword ptr [rsi+8]                    
0x665a81c  jne short 0x665A843                           ; -> loc_665a843
0x665a81e  mov rax,[rsi]                                 
0x665a821  mov rax,[rax]                                 
0x665a824  mov rcx,rsi                                   
0x665a827  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665a82d  lock dec dword ptr [rsi+0xC]                  
0x665a831  jne short 0x665A843                           ; -> loc_665a843
0x665a833  mov rax,[rsi]                                 
0x665a836  mov rax,[rax+8]                               
0x665a83a  mov rcx,rsi                                   
0x665a83d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
// INTERPRETATION [V]: Fall-through from Phase 31's `jne 0x665B62A` (when [rbp+0x520]!=2) and from Phase 30's fall-through paths. edi=0; rbx=[rbp+0x78]; [rbp+0x4A8]=rbx; [rbp+0x4B0]=rdi (0); [rbp+0x4B8]=cl; rcx=[rbp+0xA0]; [rbp+0x4D0]=rcx; xmm0=[rbp+0x90]; [rbp+0x4C0]=xmm0; ecx=0x9D0; rcx += [rsi+0x10] (component type hash + entity offset); [rsp+0x30]=rax; [rsp+0x28]=r10; [rsp+0x20]=r11; call 0x67EA0D0(...) [V,I]. `nop` [V]. lea rcx,[rbp+0x340]; call 0x673CB40(rcx=&rbp+0x340) [V,I]. `cmp byte [rbp+0x88],3; jne short 0x665A843` — if flag != 3 skip release. Otherwise rsi=[rbp+0x80]; `test rsi,rsi; je short 0x665A843` — if null skip. `lock dec dword ptr [rsi+8]` (refcount dec); `jne short 0x665A843` — if not zero skip destructor. Otherwise call sub_eea6040 (destructor), then `lock dec dword ptr [rsi+0xC]` (weak ref dec), `jne short 0x665A843`, else call sub_eea6040 again (deallocate) [V,I].

## Phase 33 — Refcount release loop 0x665a843..0x665a8a4 (31 instr) [V]
```
loc_665a843:  ; from 665a80a, 665a816, 665a81c, 665a831
0x665a843  mov rdi,[rbp+0x58]                            
0x665a847  test rdi,rdi                                  
0x665a84a  je short 0x665A8A5                            ; -> loc_665a8a5
0x665a84c  mov rbx,[rbp+0x60]                            
0x665a850  jmp short 0x665A864                           ; -> loc_665a864
0x665a852  nop [rax+rax]                                 
loc_665a860:  ; from 665a86d, 665a876, 665a87c, 665a891, 665a8a3
0x665a860  add rdi,0x28                                  
loc_665a864:  ; from 665a850
0x665a864  cmp rdi,rbx                                   
0x665a867  je short 0x665A8A5                            ; -> loc_665a8a5
0x665a869  cmp byte ptr [rdi+0x18],2                     
0x665a86d  jne short 0x665A860                           ; -> loc_665a860
0x665a86f  mov rsi,[rdi+8]                               
0x665a873  test rsi,rsi                                  
0x665a876  je short 0x665A860                            ; -> loc_665a860
0x665a878  lock dec dword ptr [rsi+8]                    
0x665a87c  jne short 0x665A860                           ; -> loc_665a860
0x665a87e  mov rax,[rsi]                                 
0x665a881  mov rax,[rax]                                 
0x665a884  mov rcx,rsi                                   
0x665a887  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665a88d  lock dec dword ptr [rsi+0xC]                  
0x665a891  jne short 0x665A860                           ; -> loc_665a860
0x665a893  mov rax,[rsi]                                 
0x665a896  mov rax,[rax+8]                               
0x665a89a  mov rcx,rsi                                   
0x665a89d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665a8a3  jmp short 0x665A860                           ; -> loc_665a860
```
// INTERPRETATION [V]: Jump target from Phase 32's `jne short 0x665A843`. rdi=[rbp+0x58] (list head); `test rdi,rdi; je short 0x665A8A5` — if null skip loop. rbx=[rbp+0x60] (list end); `jmp short 0x665A864`. Loop: `add rdi,0x28` (advance by 0x28 stride); `cmp rdi,rbx; je short 0x665A8A5` — if at end exit. `cmp byte [rdi+0x18],2; jne short 0x665A860` — if type != 2 skip. rsi=[rdi+8]; `test rsi,rsi; je short 0x665A860` — if null skip. `lock dec dword ptr [rsi+8]` (refcount dec); `jne short 0x665A860` — if not zero skip destructor. Otherwise call sub_eea6040 (destructor), then `lock dec dword ptr [rsi+0xC]` (weak ref dec), `jne short 0x665A860`, else call sub_eea6040 again (deallocate); `jmp short 0x665A860` continue loop [V,I]. `nop [rax+rax]` padding at 0x665a852 [V].

## Phase 34 — Exit check 0x665a8a5..0x665a8c9 (5 instr) [V]
```
loc_665a8a5:  ; from 665a84a, 665a867
0x665a8a5  cmp byte ptr [rbp+0x520],1                    
0x665a8ac  jne 0x665AEE8                                 ; -> loc_665aee8
0x665a8b2  mov rcx,[rbp+0x4E0]                           
0x665a8b9  test rcx,rcx                                  
0x665a8bc  je 0x665AEE8                                  ; -> loc_665aee8
0x665a8c2  mov rdx,[rbp+0x4F0]                           
0x665a8c9  jmp 0x665AEBB                                 ; -> loc_665aebb
```
// INTERPRETATION [V]: Jump target from Phase 33 release loop end. `cmp byte [rbp+0x520],1; jne 0x665AEE8` — if flag != 1 exit to 0x665aee8. Otherwise rcx=[rbp+0x4E0]; `test rcx,rcx; je 0x665AEE8` — if null exit. Otherwise rdx=[rbp+0x4F0]; `jmp 0x665AEBB` (heap/alloc bounds check, outside unit range but target within 0x6659a75..0x665aee8? 0x665AEBB > 0x665aee8? 0x665AEBB - 0x665aee8 = 0x1D3, so yes outside range) [V].

## Phase 35 — SKY-PUSH setup (dead code after jmp) 0x665a8ce..0x665a915 (15 instr) [V]
```
0x665a8ce  xor ecx,ecx                                   
0x665a8d0  mov rdx,[rbp+0x508]                           
0x665a8d7  mov [rbp+0x4A0],rdx                           
0x665a8de  mov [rbp+0x4A8],rcx                           
0x665a8e5  mov [rbp+0x4B0],al                            
0x665a8eb  mov rax,[rbp+0x530]                           
0x665a8f2  mov [rbp+0x4C8],rax                           
0x665a8f9  movaps xmm0,[rbp+0x520]                       
0x665a900  movups [rbp+0x4B8],xmm0                       
0x665a907  mov ecx,0x9D0                                 
0x665a90c  add rcx,[rsi+0x10]                            
0x665a910  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x665a915  nop                                           
```
// INTERPRETATION [V]: Linear code after Phase 34's unconditional `jmp 0x665AEBB` (not reachable from Phase 34, but within address range). ecx=0; rdx=[rbp+0x508]; [rbp+0x4A0]=rdx; [rbp+0x4A8]=rcx (0); [rbp+0x4B0]=al (0); rax=[rbp+0x530]; [rbp+0x4C8]=rax; xmm0=[rbp+0x520]; [rbp+0x4B8]=xmm0; ecx=0x9D0; rcx += [rsi+0x10]; call 0x5ABA5C0(rcx=0x9D0+[rsi+0x10]) — shared SKY-PUSH submit call (component type hash + entity offset) [V,I]. `nop` [V].

## Phase 36 — Clear push slots + call 0x675F3B0 0x665a916..0x665a983 (19 instr) [V]
```
0x665a916  mov rsi,rax                                   
0x665a919  lea rdx,[rbp+0x478]                           
0x665a920  xorps xmm0,xmm0                               
0x665a923  movups [rbp+0x298],xmm0                       
0x665a92a  movups [rbp+0x288],xmm0                       
0x665a931  movups [rbp+0x278],xmm0                       
0x665a938  movups [rbp+0x268],xmm0                       
0x665a93f  movups [rbp+0x258],xmm0                       
0x665a946  movups [rbp+0x248],xmm0                       
0x665a94d  movups [rbp+0x238],xmm0                       
0x665a954  movups [rbp+0x228],xmm0                       
0x665a95b  movups [rbp+0x218],xmm0                       
0x665a962  movups [rbp+0x208],xmm0                       
0x665a969  movups [rbp+0x1F8],xmm0                       
0x665a970  movups [rbp+0x1E8],xmm0                       
0x665a977  lea rcx,[rax+0x780]                           ; R ret@5aba5c0+0x780
0x665a97e  call 0x675F3B0                                ; -> sub_675f3b0
0x665a983  nop                                           
```
// INTERPRETATION [V]: rsi=rax (return from 0x5ABA5C0); lea rdx,[rbp+0x478] begins push command build; xmm0=0; zeroes [rbp+0x298],[rbp+0x288],[rbp+0x278],[rbp+0x268],[rbp+0x258],[rbp+0x248],[rbp+0x238],[rbp+0x228],[rbp+0x218],[rbp+0x208],[rbp+0x1F8],[rbp+0x1E8] (12 slots, 16 bytes each = 0xC0 bytes cleared) [V]. lea rcx,[rax+0x780]; call 0x675F3B0(rcx=ret@5aba5c0+0x780) [V,I]. `nop` [V].

## Phase 37 — Compute count + refcount + write u16 0x665a984..0x665a9e4 (23 instr) [V]
```
0x665a984  mov qword ptr [rbp+0x1E0],0x1000              
0x665a98f  mov eax,[rsi+0x788]                           ; R ret@5aba5c0+0x788
0x665a995  sub eax,[rsi+0x780]                           ; R ret@5aba5c0+0x780
0x665a99b  shr eax,3                                     
0x665a99e  imul eax,0xFFFF8BA3                           
0x665a9a4  dec eax                                       
0x665a9a6  mov [rbp+0x208],ax                            
0x665a9ad  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665a9b4  mov rax,[rcx]                                 
0x665a9b7  mov rax,[rax+0x10]                            
0x665a9bb  mov dl,0x4A                                   
0x665a9bd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665a9c3  nop                                           
0x665a9c4  mov [rbp+0x540],al                            
0x665a9ca  mov rdx,[rsi+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x665a9d1  cmp rdx,[rsi+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x665a9d8  je short 0x665A9EE                            ; -> loc_665a9ee
0x665a9da  movzx eax,word ptr [rbp+0x470]                
0x665a9e1  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x665a9e4  add qword ptr [rsi+0x8A8],2                   ; W ret@5aba5c0+0x8A8
```
// INTERPRETATION [V]: [rbp+0x1E0]=0x1000; eax=[rsi+0x788]-[rsi+0x780] (range diff from 0x5ABA5C0 return); `shr eax,3` (/8); `imul eax,0xFFFF8BA3` (magic multiply); `dec eax` -> [rbp+0x208] (u16 item count) [V]. Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword ptr [0xF99FFA0] (sub_eea6040, refcount acquire) [V,I]. `nop`; [rbp+0x540]=al (refcount result) [V]. rdx=[rsi+0x8A8] (write cursor); `cmp rdx,[rsi+0x8B0]` (end); `je short 0x665A9EE` — if full go to fallback. Otherwise `movzx eax,word ptr [rbp+0x470]`; `mov [rdx],ax` (write u16 item to buffer); `add qword ptr [rsi+0x8A8],2` (advance cursor by 2) [V,I]. `jmp short 0x665AA02` [V].

## Phase 38 — Fallback refcount call 0x665a9ee..0x665aa01 (6 instr) [V]
```
loc_665a9ee:  ; from 665a9d8
0x665a9ee  lea r8,[rbp+0x470]                            
0x665a9f5  lea rcx,[rsi+0x8A0]                           
0x665a9fc  call 0x1EF6F90                                ; -> sub_1ef6f90
0x665aa01  nop                                           
```
// INTERPRETATION [V]: Jump target from Phase 37's `je short 0x665A9EE` (buffer full). lea r8,[rbp+0x470]; lea rcx,[rsi+0x8A0]; call 0x1EF6F90(rcx=&rsi+0x8A0, r8=&rbp+0x470) — fallback insert when buffer full [V,I]. `nop` [V].

## Phase 39 — Refcount + compute u16 count 0x665aa02..0x665aa2e (18 instr) [V]
```
loc_665aa02:  ; from 665a9ec
0x665aa02  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665aa09  mov rax,[rcx]                                 
0x665aa0c  mov rax,[rax+0x10]                            
0x665aa10  movzx edx,byte ptr [rbp+0x540]                
0x665aa17  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665aa1d  nop                                           
0x665aa1e  mov eax,[rsi+0x8A8]                           
0x665aa24  sub eax,[rsi+0x8A0]                           
0x665aa2a  shr eax,1                                     
0x665aa2c  dec eax                                       
0x665aa2e  mov [rbp+0x1F0],ax                            
```
// INTERPRETATION [V]: Jump target from Phase 37's `jmp short 0x665AA02`. Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=[rbp+0x540] (byte); call qword ptr [0xF99FFA0] (sub_eea6040, refcount release/acquire) [V,I]. `nop`; eax=[rsi+0x8A8]-[rsi+0x8A0] (bytes written); `shr eax,1` (/2); `dec eax` -> [rbp+0x1F0] (u16 count) [V].

## Phase 40 — Refcount + call 0x675FB30 0x665aa35..0x665aa64 (16 instr) [V]
```
0x665aa35  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665aa3c  mov rax,[rcx]                                 
0x665aa3f  mov rax,[rax+0x10]                            
0x665aa43  mov dl,0x4A                                   
0x665aa45  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665aa4b  mov [rbp+0x540],al                            
0x665aa51  lea rdx,[rbp+0x428]                           
0x665aa58  lea rcx,[rsi+0x648]                           
0x665aa5f  call 0x675FB30                                ; -> sub_675fb30
0x665aa64  nop                                           
```
// INTERPRETATION [V]: Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. [rbp+0x540]=al; lea rdx,[rbp+0x428]; lea rcx,[rsi+0x648]; call 0x675FB30(rcx=&rsi+0x648, rdx=&rbp+0x428) [V,I]. `nop` [V].

## Phase 41 — Refcount + compute u16 count 2 0x665aa65..0x665aa98 (16 instr) [V]
```
0x665aa65  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665aa6c  mov rax,[rcx]                                 
0x665aa6f  mov rax,[rax+0x10]                            
0x665aa73  movzx edx,byte ptr [rbp+0x540]                
0x665aa7a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665aa80  nop                                           
0x665aa81  mov eax,[rsi+0x650]                           
0x665aa87  sub eax,[rsi+0x648]                           
0x665aa8d  shr eax,3                                     
0x665aa90  imul eax,0xFFFF8E39                           
0x665aa96  dec eax                                       
0x665aa98  mov [rbp+0x222],ax                            
```
// INTERPRETATION [V]: Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=[rbp+0x540] (byte); call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; eax=[rsi+0x650]-[rsi+0x648] (range diff); `shr eax,3` (/8); `imul eax,0xFFFF8E39` (magic multiply); `dec eax` -> [rbp+0x222] (u16 count) [V].

## Phase 42 — Refcount + push command write 0x665aa9f..0x665aab5 (12 instr) [V]
```
0x665aa9f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665aaa6  mov rax,[rcx]                                 
0x665aaa9  mov rax,[rax+0x10]                            
0x665aaad  mov dl,0x4A                                   
0x665aaaf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665aab5  nop                                           
```
// INTERPRETATION [V]: Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; [rbp+0x540]=al (result) [V]. Falls through to 0x665aab6 (next phase).

## Phase 43 — Push command slot write 0x665aab6..0x665ab1f (19 instr) [V]
```
0x665aab6  mov [rbp+0x540],al                            
0x665aabc  mov rbx,[rsi+0x770]                           
0x665aac3  cmp rbx,[rsi+0x778]                           
0x665aaca  je short 0x665AB09                            ; -> loc_665ab09
0x665aacc  mov rax,[rbp+0x3A0]                           
0x665aad3  mov [rbx],rax                                 
0x665aad6  lea rcx,[rbx+8]                               
0x665aada  mov rdx,rdi                                   
0x665aadd  call 0xE869FF0                                ; -> sub_e869ff0
0x665aae2  nop                                           
0x665aae3  mov rax,[rbp+0x420]                           
0x665aaea  mov [rbx+0x80],rax                            
0x665aaf1  mov qword ptr [rbp+0x420],0                   
0x665aafc  add qword ptr [rsi+0x770],0x88                
0x665ab07  jmp short 0x665AB20                           ; -> loc_665ab20
loc_665ab09:  ; from 665aaca
0x665ab09  lea r8,[rbp+0x3A0]                            
0x665ab10  lea rcx,[rsi+0x768]                           
0x665ab17  mov rdx,rbx                                   
0x665ab1a  call 0x6760710                                ; -> sub_6760710
0x665ab1f  nop                                           
```
// INTERPRETATION [V]: [rbp+0x540]=al (from Phase 42's refcount result); rbx=[rsi+0x770] (write cursor); `cmp rbx,[rsi+0x778]` (end); `je short 0x665AB09` — if full go to fallback call 0x6760710. Otherwise rax=[rbp+0x3A0]; `mov [rbx],rax` (write qword to push command slot); lea rcx,[rbx+8]; rdx=rdi; call 0xE869FF0(rcx=&rbx+8, rdx=rdi) — material-pair setter on push command [V,I]. `nop`; rax=[rbp+0x420]; `mov [rbx+0x80],rax` (write qword at slot+0x80); [rbp+0x420]=0; `add qword ptr [rsi+0x770],0x88` (advance cursor by 0x88 = 136 bytes per push command) [V,I]. `jmp short 0x665AB20`. Fallback (0x665AB09): lea r8,[rbp+0x3A0]; lea rcx,[rsi+0x768]; rdx=rbx; call 0x6760710(rcx=&rsi+0x768, rdx=rbx, r8=&rbp+0x3A0) — fallback insert when slot buffer full [V,I]. `nop` [V].

## Phase 44 — Refcount + push command slot fill 0x665ab20..0x665abf4 (40 instr) [V]
```
0x665ab20  mov rcx,[0x1233E1B0]                         
0x665ab27  mov rax,[rcx]                                 
0x665ab2a  mov rax,[rax+0x10]                            
0x665ab2e  movzx edx,byte ptr [rbp+0x540]                
0x665ab35  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ab3b  nop                                           
0x665ab3c  mov qword ptr [rbp+0x1E0],0x2003001           
0x665ab47  mov eax,[rsi+0x770]                           
0x665ab4d  sub eax,[rsi+0x768]                           
0x665ab53  shr eax,3                                     
0x665ab56  imul eax,0xFFFFF0F1                           
0x665ab5c  dec eax                                       
0x665ab5e  mov [rbp+0x20A],ax                            
0x665ab65  mov rcx,[0x1233E1B0]                         
0x665ab6c  mov rax,[rcx]                                 
0x665ab6f  mov rax,[rax+0x10]                            
0x665ab73  mov dl,0x4A                                   
0x665ab75  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ab7b  nop                                           
0x665ab7c  mov [rbp+0x540],al                            
0x665ab82  lea r8,[rbp+0x344]                            
0x665ab89  mov rdx,[rsi+0x758]                           
0x665ab90  cmp rdx,[rsi+0x760]                           
0x665ab97  je short 0x665AC10                            ; -> loc_665ac10
0x665ab99  mov eax,[r8+0x10]                             
0x665ab9d  mov [rdx+0x10],eax                            
0x665aba0  movups xmm0,[r8]                              
0x665aba4  movups [rdx],xmm0                             
0x665aba7  movzx eax,byte ptr [rbp+0x358]                
0x665abae  mov [rdx+0x14],al                             
0x665abb1  movss xmm0,[rbp+0x35C]                        
0x665abb9  movss [rdx+0x18],xmm0                         
0x665abbe  movss xmm0,[rbp+0x360]                        
0x665abc6  movss [rdx+0x1C],xmm0                         
0x665abcb  movss xmm0,[rbp+0x364]                        
0x665abd3  movss [rdx+0x20],xmm0                         
0x665abd8  movss xmm0,[rbp+0x368]                        
0x665abe0  movss [rdx+0x24],xmm0                         
0x665abe5  movups xmm0,[rbp+0x36C]                       
0x665abec  movups xmm1,[rbp+0x37C]                       
```
// INTERPRETATION [V]: Jump target from Phase 43 convergence (0x665ab20). Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=[rbp+0x540]; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; [rbp+0x1E0]=0x2003001 [V]. eax=[rsi+0x770]-[rsi+0x768] (byte cursor diff); `shr eax,3` (/8); `imul eax,0xFFFFF0F1` (magic multiply); `dec eax` -> [rbp+0x20A] (u16 count) [V]. Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; [rbp+0x540]=al [V]. lea r8,[rbp+0x344]; rdx=[rsi+0x758] (slot cursor); `cmp rdx,[rsi+0x760]` (end); `je short 0x665AC10` — if full go to fallback [V,I]. Otherwise: mov eax,[r8+0x10] -> [rdx+0x10]; movups xmm0,[r8] -> [rdx] (copy 16 bytes from [rbp+0x344] descriptor to slot) [V]. movzx eax,byte [rbp+0x358] -> [rdx+0x14]; movss [rdx+0x18]=[rbp+0x35C]; [rdx+0x1C]=[rbp+0x360]; [rdx+0x20]=[rbp+0x364]; [rdx+0x24]=[rbp+0x368] (write float fields to slot) [V]. movups xmm0,[rbp+0x36C]; movups xmm1,[rbp+0x37C] (load remaining vector fields) [V].

## Phase 45 — Slot fill continuation + refcount + cursor advance 0x665abf4..0x665acab (40 instr) [V]
```
0x665abf4  adc [rbp+0x38B],dl                            
0x665abfa  movups [rdx+0x28],xmm0                        ; W a1+0x28
0x665abfe  movups [rdx+0x38],xmm1                        ; W a1+0x38
0x665ac02  movups [rdx+0x47],xmm2                        ; W a1+0x47
0x665ac06 add qword ptr [rsi+0x758],0x58                
0x665ac0e jmp short 0x665AC1D                           ; -> loc_665ac1d
0x665ac10 lea rcx,[rsi+0x750]                           
0x665ac17 call 0x6760A80                                ; -> sub_6760a80
0x665ac1c nop                                           
loc_665ac1d:  ; from 665ac0e
0x665ac1d mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665ac24 mov rax,[rcx]                                 
0x665ac27 mov rax,[rax+0x10]                            
0x665ac2b movzx edx,byte ptr [rbp+0x540]                
0x665ac32 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ac38 nop                                           
0x665ac39 mov eax,[rsi+0x758]                           
0x665ac3f sub eax,[rsi+0x750]                           
0x665ac45 shr eax,3                                     
0x665ac48 imul eax,0xFFFF8BA3                           
0x665ac4e dec eax                                       
0x665ac50 mov [rbp+0x20C],ax                            
0x665ac57 mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665ac5e mov rax,[rcx]                                 
0x665ac61 mov rax,[rax+0x10]                            
0x665ac65 mov dl,0x4A                                   
0x665ac67 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ac6d nop                                           
0x665ac6e mov [rbp+0x540],al                            
0x665ac74 mov rdx,[rsi+0x860]                           
0x665ac7b cmp rdx,[rsi+0x868]                           
0x665ac82 je short 0x665AC90                            ; -> loc_665ac90
0x665ac84 inc rdx                                       
0x665ac87 mov [rsi+0x860],rdx                           
0x665ac8e jmp short 0x665AC9D                           ; -> loc_665ac9d
loc_665ac90:  ; from 665ac82
0x665ac90 lea rcx,[rsi+0x858]                           
0x665ac97 call 0x6760E60                                ; -> sub_6760e60
0x665ac9c nop                                           
loc_665ac9d:  ; from 665ac8e
0x665ac9d mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665aca4 mov rax,[rcx]                                 
0x665aca7 mov rax,[rax+0x10]                            
```
// INTERPRETATION [V]: Continuation of Phase 44's slot fill path (fall-through from `je short 0x665AC10` not taken). `adc [rbp+0x38B],dl` (add with carry to flag byte) [V]. `movups [rdx+0x28]=xmm0; [rdx+0x38]=xmm1; [rdx+0x47]=xmm2` (write remaining vector fields to slot) [V]. `add qword ptr [rsi+0x758],0x58` (advance slot cursor by 0x58 = 88 bytes) [V]. `jmp short 0x665AC1D` (join point) [V]. Fallback path (0x665ac10, taken when buffer was full): `lea rcx,[rsi+0x750]; call 0x6760A80(rcx=&rsi+0x750)` — fallback insert [V,I]. `nop` [V]. Join point loc_665ac1d: Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=[rbp+0x540]; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; eax=[rsi+0x758]-[rsi+0x750] (byte diff); `shr eax,3` (/8); `imul eax,0xFFFF8BA3` (magic multiply); `dec eax` -> [rbp+0x20C] (u16 count) [V]. Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; [rbp+0x540]=al [V]. rdx=[rsi+0x860] (cursor); `cmp rdx,[rsi+0x868]` (end); `je short 0x665AC90` — if full go to fallback. Otherwise `inc rdx`; [rsi+0x860]=rdx (advance cursor by 1); `jmp short 0x665AC9D` [V,I]. Fallback (0x665ac90): `lea rcx,[rsi+0x858]; call 0x6760E60(rcx=&rsi+0x858)` — fallback insert [V,I]. `nop` [V]. Join loc_665ac9d: Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10] [V].

## Phase 46 — Refcount + cursor increment + count compute 0x665acab..0x665ad6e (40 instr) [V]
```
0x665acab  movzx edx,byte ptr [rbp+0x540]                
0x665acb2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665acb8  nop                                           
0x665acb9  mov qword ptr [rbp+0x1E0],0x2007009           
0x665acc4  mov eax,[rsi+0x858]                           
0x665acca  not eax                                       
0x665accc  add eax,[rsi+0x860]                           
0x665acd2  mov [rbp+0x1F6],ax                            
0x665acd9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665ace0  mov rax,[rcx]                                 
0x665ace3  mov rax,[rax+0x10]                            
0x665ace7  mov dl,0x4A                                   
0x665ace9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665acef  nop                                           
0x665acf0  mov [rbp+0x540],al                            
0x665acf6  mov rdx,[rsi+0x2A8]                           
0x665acfd  cmp rdx,[rsi+0x2B0]                           
0x665ad04  je short 0x665AD12                            ; -> loc_665ad12
0x665ad06  inc rdx                                       
0x665ad09  mov [rsi+0x2A8],rdx                           
0x665ad10  jmp short 0x665AD22                           ; -> loc_665ad22
loc_665ad12:  ; from 665ad04
0x665ad12  mov rcx,rsi                                   
0x665ad15  add rcx,0x2A0                                 
0x665ad1c  call 0x6760E60                                ; -> sub_6760e60
0x665ad21  nop                                           
loc_665ad22:  ; from 665ad10
0x665ad22  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665ad29  mov rax,[rcx]                                 
0x665ad2c mov rax,[rax+0x10]                            
0x665ad30  movzx edx,byte ptr [rbp+0x540]                
0x665ad37  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ad3d  nop                                           
0x665ad3e  mov qword ptr [rbp+0x1E8],1                   
0x665ad49  mov eax,[rsi+0x2A0]                           
0x665ad4f  not eax                                       
0x665ad51  add eax,[rsi+0x2A8]                           
0x665ad57  mov [rbp+0x270],ax                            
0x665ad5e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665ad65  mov rax,[rcx]                                 
0x665ad68  mov rax,[rax+0x10]                            
0x665ad6c  mov dl,0x4A                                   
```
// INTERPRETATION [V]: Join from Phase 45's `jmp short 0x665AC9D`. Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=[rbp+0x540]; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; [rbp+0x1E0]=0x2007009 [V]. eax=[rsi+0x858]; `not eax` (bitwise NOT); `add eax,[rsi+0x860]` (end - ~start = count of 8-byte items); `mov [rbp+0x1F6],ax` (u16 count) [V]. Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; [rbp+0x540]=al [V]. rdx=[rsi+0x2A8] (cursor); `cmp rdx,[rsi+0x2B0]` (end); `je short 0x665AD12` — if full go to fallback. Otherwise `inc rdx`; [rsi+0x2A8]=rdx (advance cursor by 1); `jmp short 0x665AD22` [V,I]. Fallback (0x665ad12): `mov rcx,rsi; add rcx,0x2A0; call 0x6760E60(rcx=&rsi+0x2A0)` — fallback insert [V,I]. `nop` [V]. Join loc_665ad22: Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=[rbp+0x540]; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; [rbp+0x1E8]=1 (qword) [V]. eax=[rsi+0x2A0]; `not eax`; `add eax,[rsi+0x2A8]` -> [rbp+0x270] (u16 count) [V]. Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A [V].

## Phase 47 — Refcount + cursor write + refcount + call + release 0x665ad6e..0x665ae16 (40 instr) [V]
```
0x665ad6e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ad74  nop                                           
0x665ad75  mov [rbp+0x540],al                            
0x665ad7b  mov rax,[rsi+8]                               
0x665ad7f  cmp rax,[rsi+0x10]                            
0x665ad83  je short 0x665ADA4                            ; -> loc_665ada4
0x665ad85  lea rdx,[rbp+0x1E0]                           
0x665ad8c  mov r8d,0xC8                                  
0x665ad92  mov rcx,rax                                   
0x665ad95  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x665ad9a  add qword ptr [rsi+8],0xC8                    
0x665ada2  jmp short 0x665ADB7                           ; -> loc_665adb7
loc_665ada4:  ; from 665ad83
0x665ada4  lea r8,[rbp+0x1E0]                            
0x665adab  mov rcx,rsi                                   
0x665adae  mov rdx,rax                                   
0x665adb1  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x665adb6  nop                                           
loc_665adb7:  ; from 665ada2
0x665adb7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665adbe  mov rax,[rcx]                                 
0x665adc1  mov rax,[rax+0x10]                            
0x665adc5  movzx edx,byte ptr [rbp+0x540]                
0x665adcc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665add2  nop                                           
0x665add3  lea rcx,[rbp+0x340]                           
0x665adda  call 0x66A9AD0                                ; -> sub_66a9ad0
0x665addf  cmp byte ptr [rbp+0x518],3                    
0x665ade6  jne short 0x665AE1F                           ; -> loc_665ae1f
0x665ade8  mov rsi,[rbp+0x510]                           
0x665adef  test rsi,rsi                                  
0x665adf2  je short 0x665AE1F                            ; -> loc_665ae1f
0x665adf4  lock dec dword ptr [rsi+8]                    
0x665adf8  jne short 0x665AE1F                           ; -> loc_665ae1f
0x665adfa  mov rax,[rsi]                                 
0x665adfd  mov rax,[rax]                                 
0x665ae00  mov rcx,rsi                                   
0x665ae03  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ae09  lock dec dword ptr [rsi+0xC]                  
0x665ae0d  jne short 0x665AE1F                           ; -> loc_665ae1f
0x665ae0f  mov rax,[rsi]                                 
0x665ae12  mov rax,[rax+8]                               
```
// INTERPRETATION [V]: Join from Phase 46's `jmp short 0x665AD22`. Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=[rbp+0x540]; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; [rbp+0x540]=al [V]. rax=[rsi+8] (cursor); `cmp rax,[rsi+0x10]` (end); `je short 0x665ADA4` — if full go to fallback. Otherwise: lea rdx,[rbp+0x1E0]; mov r8d,0xC8 (200); rcx=rax; call 0xEEC6EC0(rcx=cursor, rdx=&rbp+0x1E0, r8=0xC8) — write 0xC8 bytes to buffer [V,I]. `add qword ptr [rsi+8],0xC8` (advance cursor by 200) [V]. `jmp short 0x665ADB7` [V]. Fallback (0x665ada4): lea r8,[rbp+0x1E0]; rcx=rsi; rdx=rax; call 0x5ABA6D0(rcx=rsi, rdx=cursor, r8=&rbp+0x1E0) — fallback insert [V,I]. `nop` [V]. Join loc_665adb7: Refcount: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=[rbp+0x540]; call qword ptr [0xF99FFA0] (sub_eea6040) [V,I]. `nop`; lea rcx,[rbp+0x340]; call 0x66A9AD0(rcx=&rbp+0x340) [V,I]. `cmp byte [rbp+0x518],3; jne short 0x665AE1F` — if byte != 3 go to release/exit. Otherwise: rsi=[rbp+0x510]; `test rsi,rsi; je short 0x665AE1F` — if null skip release. `lock dec dword ptr [rsi+8]` (refcount dec); `jne short 0x665AE1F` — if not zero skip destructor. Otherwise: call sub_eea6040 (destructor); `lock dec dword ptr [rsi+0xC]` (weak ref dec); `jne short 0x665AE1F` — if not zero skip deallocate. Otherwise: call sub_eea6040 again (deallocate); `mov rax,[rax+8]` (load dealloc function pointer) [V,I].

## Phase 48 — Refcount + release loop + exit check 0x665ae16..0x665aeb4 (40 instr) [V]
```
0x665ae16  mov rcx,rsi                                   
0x665ae19  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ae1f  mov rdi,[rbp+0x4E8]                           
0x665ae26  test rdi,rdi                                  
0x665ae29  je short 0x665AE93                            ; -> loc_665ae93
0x665ae2b  lea rbx,[rbp+0x4E8]                           
0x665ae32  mov r14,[rbp+0x4F0]                           
0x665ae39  jmp short 0x665AE44                           ; -> loc_665ae44
0x665ae3b  nop [rax+rax]                                 
loc_665ae40:  ; from 665ae4d, 665ae56, 665ae5c, 665ae71, 665ae83
0x665ae40  add rdi,0x28                                  
loc_665ae44:  ; from 665ae39
0x665ae44  cmp rdi,r14                                   
0x665ae47  je short 0x665AE85                            ; -> loc_665ae85
0x665ae49  cmp byte ptr [rdi+0x18],2                     
0x665ae4d  jne short 0x665AE40                           ; -> loc_665AE40
0x665ae4f  mov rsi,[rdi+8]                               
0x665ae53  test rsi,rsi                                  
0x665ae56  je short 0x665AE40                           ; -> loc_665AE40
0x665ae58  lock dec dword ptr [rsi+8]                    
0x665ae5c  jne short 0x665AE40                           ; -> loc_665AE40
0x665ae5e  mov rax,[rsi]                                 
0x665ae61  mov rax,[rax]                                 
0x665ae64  mov rcx,rsi                                   
0x665ae67  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ae6d  lock dec dword ptr [rsi+0xC]                  
0x665ae71  jne short 0x665AE40                           ; -> loc_665AE40
0x665ae73  mov rax,[rsi]                                 
0x665ae76  mov rax,[rax+8]                               
0x665ae7a  mov rcx,rsi                                   
0x665ae7d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ae83  jmp short 0x665AE40                           ; -> loc_665ae40
loc_665ae85:  ; from 665ae47
0x665ae85  xorps xmm0,xmm0                               
0x665ae88  movups [rbx],xmm0                             
0x665ae8b  mov qword ptr [rbx+0x10],0                    
loc_665ae93:  ; from 665ae29
0x665ae93  lea rcx,[rbp+0x170]                           
0x665ae9a  call 0x1751590                                ; -> sub_1751590
0x665ae9f  cmp byte ptr [rbp+0x160],1                    
0x665aea6  jne short 0x665AEE8                           ; -> loc_665aee8
0x665aea8  mov rcx,[rbp+0x120]                           
0x665aeaf  test rcx,rcx                                  
0x665aeb2  je short 0x665AEE8                           ; -> loc_665aee8
```
// INTERPRETATION [V]: Join from Phase 47's `jmp short 0x665AE1F` fall-through (when [rbp+0x518]==3 and rsi!=0 and refcount reached 0). `mov rcx,rsi; call qword ptr [0xF99FFA0]` (sub_eea6040, final deallocate on rsi) [V,I]. Then `mov rdi,[rbp+0x4E8]` (release list head); `test rdi,rdi; je short 0x665AE93` — if null skip release loop [V]. `lea rbx,[rbp+0x4E8]` (list head addr); `mov r14,[rbp+0x4F0]` (list end); `jmp short 0x665AE44` [V]. `nop [rax+rax]` padding [V]. Release loop loc_665ae40: `add rdi,0x28` (advance entry by 0x28 stride); loc_665ae44: `cmp rdi,r14; je short 0x665AE85` — if at end, exit loop. `cmp byte [rdi+0x18],2; jne short 0x665AE40` — if type != 2 skip. `rsi=[rdi+8]; test rsi,rsi; je short 0x665AE40` — if null skip. `lock dec dword ptr [rsi+8]` (refcount dec); `jne short 0x665AE40` — if not zero skip destructor. Otherwise: call sub_eea6040 (destructor); `lock dec dword ptr [rsi+0xC]` (weak ref dec); `jne short 0x665AE40` — if not zero skip deallocate. Otherwise: call sub_eea6040 again (deallocate); `jmp short 0x665AE40` continue loop [V,I]. loc_665ae85: `xorps xmm0,xmm0; movups [rbx],xmm0; mov qword ptr [rbx+0x10],0` — clear list head entry (16 bytes zeroed) [V]. loc_665ae93: `lea rcx,[rbp+0x170]; call 0x1751590(rcx=&rbp+0x170)` [V,I]. `cmp byte [rbp+0x160],1; jne short 0x665AEE8` — if flag != 1, exit to 0x665aee8 (UNIT END) [V]. `mov rcx,[rbp+0x120]; test rcx,rcx; je short 0x665AEE8` — if null, exit to 0x665aee8 [V]. Both exit paths reach 0x665aee8 = Cubemap case exit boundary.

## Phase 49 — Final exit sequence 0x665aeb4..0x665aee8 (14 instr) [V]
```
0x665aeb4  mov rdx,[rbp+0x130]                           
0x665aebb  sub rdx,rcx                                   
0x665aebe  cmp rdx,0x1000                                
0x665aec5  jb short 0x665AEE3                            ; -> loc_665aee3
0x665aec7  mov rax,[rcx-8]                               ; R a0-0x8
0x665aecb  add rcx,0xFFFFFFFFFFFFFFF8                    
0x665aecf  sub rcx,rax                                   
0x665aed2  cmp rcx,0x20                                  
0x665aed6  jae 0x665D43A                                 ; -> sub_665d43a
0x665aedc  or rdx,0x27                                   
0x665aee0  mov rcx,rax                                   
loc_665aee3:  ; from 665aec5
0x665aee3  call 0xE935700                                ; -> sub_e935700
0x665aee8  mov rsi,[rbp+0x328]                           
0x665aeef  jmp 0x665D124                                 ; -> sub_665d124
```
// INTERPRETATION [V]: Final exit sequence from Cubemap case. Fall-through from Phase 48's `je short 0x665AEE8` (not taken when rcx != 0). rdx=[rbp+0x130]; `sub rdx,rcx` (delta); `cmp rdx,0x1000; jb short 0x665AEE3` — if delta < 0x1000 skip to call. Otherwise: rax=[rcx-8] (chunk header size); `add rcx,0xFFFFFFFFFFFFFFF8` (rcx -= 8); `sub rcx,rax` (remaining); `cmp rcx,0x20; jae 0x665D43A` — if >= 0x20 go to dealloc path. Otherwise: `or rdx,0x27` (set flags); `mov rcx,rax`. loc_665aee3: `call 0xE935700` (sub_e935700, dealloc/free) [V,I]. UNIT END at 0x665aee8: `mov rsi,[rbp+0x328]`; `jmp 0x665D124` (sub_665d124) — jump to next case handler [V,I]. Cubemap case instruction-complete through 0x665aee8.
