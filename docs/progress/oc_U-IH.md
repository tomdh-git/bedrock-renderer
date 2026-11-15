# U-IH: ItemInHand extractor 0x6698e30 — disassembly decode

## NEXT
Resume at: nothing remains. Callee 0x67d14e0 remaining (0x67d1d2b..ret 0x67d253a) and range 0x669c8f9..0x669c9e2 documented below; all ranges instruction-complete; unit DONE.

---

## Callee 0x67d14e0 — remaining instructions 0x67d1d2b..ret 0x67d253a

### Phase A (0x67d1d2b..0x67d1d67) — reload cookie, finalize +0x180 region counter
```
67d1d2b  movzx edx,byte ptr [rbp+0x7F]                 
67d1d2f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1d36  mov rax,[rcx]                                 
67d1d39  mov rax,[rax+0x10]                            
67d1d3d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1d43  nop                                           
67d1d44  mov qword ptr [rbp-0x48],0x1000               
67d1d4c  mov eax,[rsi+0x180]                           
67d1d52  not eax                                       
67d1d54  add eax,[rsi+0x188]                           
67d1d5a  mov [rbp+0x58],ax                             
67d1d5e  mov r14b,1                                    
67d1d61  mov r15d,0x1000                               
```
Reloads cookie dl=[rbp+0x7F], cookie call via [0xF99FFA0]; [rbp-0x48]=0x1000; eax=(~[rsi+0x180])+[rsi+0x188] → [rbp+0x58] (slot count for +0x180 region); r14b=1, r15d=0x1000 (alloc min size).

### Phase B (0x67d1d67..0x67d1df9) — counter region [rbp+0x138] / slot region +0x408/+0x410
```
67d1d67  mov rax,[rbp+0x138]                           
67d1d6e  cmp byte ptr [rax+1],1                        
67d1d72  jne 0x67D1DF9                                 ; -> loc_67d1df9
67d1d78  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1d7f  mov rax,[rcx]                                 
67d1d82  mov rax,[rax+0x10]                            
67d1d86  mov dl,0x4A                                   
67d1d88  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1d8e  mov [rbp+0x7F],al                             
67d1d91  mov rdx,[rsi+0x410]                           
67d1d98  cmp rdx,[rsi+0x418]                           
67d1d9f  je short 0x67D1DAD                            ; -> loc_67d1dad
67d1da1  inc rdx                                       
67d1da4  mov [rsi+0x410],rdx                           
67d1dab  jmp short 0x67D1DBA                           ; -> loc_67d1dba
loc_67d1dad:
67d1dad  lea rcx,[rsi+0x408]                           
67d1db4  call 0x6760E60                                ; -> sub_6760e60
67d1db9  nop                                           
loc_67d1dba:
67d1dba  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1dc1  mov rax,[rcx]                                 
67d1dc4  mov rax,[rax+0x10]                            
67d1dc8  movzx edx,byte ptr [rbp+0x7F]                 
67d1dcc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1dd2  nop                                           
67d1dd3  mov rax,0x2000000000000                       
67d1ddd  or r12,rax                                    
67d1de0  mov [rbp-0x50],r12                            
67d1de4  mov eax,[rsi+0x408]                           
67d1dea  not eax                                       
67d1dec  add eax,[rsi+0x410]                           
67d1df2  mov [rbp+0x22],ax                             
67d1df6  mov r14b,1                                    
```
If byte [rax+1]==1 (rax=[rbp+0x138]): cookie call; if cursor [rsi+0x410]!=end [rsi+0x418]: increment cursor; else grow via 0x6760e60(&rsi+0x408). Then cookie call; or r12,0x2000000000000; [rbp-0x50]=r12; eax=(~[rsi+0x408])+[rsi+0x410] → [rbp+0x22] (slot count); r14b=1.

### Phase C (0x67d1df9..0x67d1ec7) — counter region [rbp+0x140] / slot region +0x198/+0x1A0/+0x1A8 (grow path)
```
67d1df9  mov rax,[rbp+0x140]                           
67d1e00  cmp byte ptr [rax+1],1                        
67d1e04  jne 0x67D2008                                 ; -> loc_67d2008
67d1e0a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1e11  mov rax,[rcx]                                 
67d1e14  mov rax,[rax+0x10]                            
67d1e18  mov dl,0x4A                                   
67d1e1a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1e20  mov edx,eax                                   
67d1e22  mov rbx,[rsi+0x1A0]                           
67d1e29  cmp rbx,[rsi+0x1A8]                           
67d1e30  je short 0x67D1E41                            ; -> loc_67d1e41
67d1e32  inc rbx                                       
67d1e35  mov [rsi+0x1A0],rbx                           
67d1e3c  jmp 0x67D1FD3                                 ; -> loc_67d1fd3
loc_67d1e41:
67d1e41  mov [rbp+0x7F],dl                             
67d1e44  mov [rbp-0x58],r15                            
67d1e48  mov r15,rbx                                   
67d1e4b  sub r15,[rsi+0x198]                           
67d1e52  mov rax,0x7FFFFFFFFFFFFFFF                    
67d1e5c  cmp r15,rax                                   
67d1e5f  je 0x67D2550                                  ; -> loc_67d2550
67d1e65  lea r13,[r15+1]                               
67d1e69  mov rdi,r15                                   
67d1e6c  shr rdi,1                                     
67d1e6f  mov rcx,rdi                                   
67d1e72  xor rcx,rax                                   
67d1e75  add rdi,r15                                   
67d1e78  cmp rdi,r13                                   
67d1e7b  cmovbe rdi,r13                                
67d1e7f  cmp r15,rcx                                   
67d1e82  cmova rdi,rax                                 
67d1e86  test rdi,rdi                                  
67d1e89  je 0x67D1F4F                                  ; -> loc_67d1f4f
67d1e8f  cmp rdi,0x1000                                
67d1e96  jb short 0x67D1EE1                            ; -> loc_67d1ee1
67d1e98  cmp rdi,0xFFFFFFFFFFFFFFD9                    
67d1e9c  jae 0x67D2576                                 ; -> loc_67d2576
67d1ea2  lea rdx,[rdi+0x27]                            
67d1ea6  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
67d1ead  mov rax,[rcx]                                 
67d1eb0  mov rax,[rax+8]                               
67d1eb4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1eba  nop                                           
67d1ebb  mov r14,rax                                   
67d1ebe  test rax,rax                                  
67d1ec1  je 0x67D253B                                  ; -> loc_67d253b
```
If byte [rax+1]==1 (rax=[rbp+0x140]): cookie call (dl=cookie saved to [rbp+0x7F]); rbx=cursor [rsi+0x1A0]; if cursor==end [rsi+0x1A8] goto grow path (0x67d1e41), else increment cursor and jump to 0x67d1fd3 (finalize). Grow path: r15=cursor-begin([rsi+0x198]); compute new size (clamp min 0x1000, max 0xFFFFFFFFFFFFFFD9); alloc via [0xF99FFA0] (+0x27 overhead, 0x20-align); if alloc fails jump to 0x67d253b (retry path).

### Phase D (0x67d1ec7..0x67d1fd3) — grow path memcpy + finalize (shared with earlier +0x180 region grow)
```
loc_67d1ec7:
67d1ec7  mov rax,r14                                   
67d1eca  add r14,0x27                                  
67d1ece  and r14,0xFFFFFFFFFFFFFFE0                    
67d1ed2  mov [r14-8],rax                               
67d1ed6  cmp rbx,[rsi+0x1A0]                           
67d1edd  jne short 0x67D1F0A                           ; -> loc_67d1f0a
67d1edf  jmp short 0x67D1F5B                           ; -> loc_67d1f5b
loc_67d1ee1:
67d1ee1  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
67d1ee8  mov rax,[rcx]                                 
67d1eeb  mov rax,[rax+8]                               
67d1eef  mov rdx,rdi                                   
67d1ef2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1ef8  nop                                           
67d1ef9  mov r14,rax                                   
67d1efc  test rax,rax                                  
67d1eff  je short 0x67D1F46                            ; -> loc_67d1f46
67d1f01  cmp rbx,[rsi+0x1A0]                           
67d1f08  je short 0x67D1F5B                            ; -> loc_67d1f5b
loc_67d1f0a:
67d1f0a  add r15,r14                                   
67d1f0d  inc r15                                       
67d1f10  mov rdx,[rsi+0x198]                           
67d1f17  mov r8,rbx                                    
67d1f1a  sub r8,rdx                                    
67d1f1d  mov rcx,r14                                   
67d1f20  call 0xEEC6DE0                                ; -> sub_eec6de0
67d1f25  mov r8,[rsi+0x1A0]                            
67d1f2c  sub r8,rbx                                    
67d1f2f  mov rcx,r15                                   
67d1f32  mov rdx,rbx                                   
67d1f35  jmp short 0x67D1F6B                           ; -> loc_67d1f6b
loc_67d1f37:
67d1f37  lea rcx,[rdi+0x27]                            
67d1f3b  call 0x9BC830                                 ; -> sub_9bc830
67d1f40  nop                                           
67d1f41  jmp 0x67D1C36                                 ; -> sub_67d1c36   (note: target lies outside this function range)
loc_67d1f46:
67d1f46  mov rcx,rdi                                   
67d1f49  call 0x9BC830                                 ; -> sub_9bc830
67d1f4e  nop                                           
loc_67d1f4f:
67d1f4f  xor r14d,r14d                                 
67d1f52  cmp rbx,[rsi+0x1A0]                           
67d1f59  jne short 0x67D1F0A                           ; -> loc_67d1f0a
loc_67d1f5b:
67d1f5b  mov rdx,[rsi+0x198]                           
67d1f62  sub rbx,rdx                                   
67d1f65  mov rcx,r14                                   
67d1f68  mov r8,rbx                                    
loc_67d1f6b:
67d1f6b  call 0xEEC6DE0                                ; -> sub_eec6de0
67d1f70  mov rcx,[rsi+0x198]                           
67d1f77  test rcx,rcx                                  
67d1f7a  je short 0x67D1FB0                            ; -> loc_67d1fb0
67d1f7c  mov rdx,[rsi+0x1A8]                           
67d1f83  sub rdx,rcx                                   
67d1f86  cmp rdx,0x1000                                
67d1f8d  jb short 0x67D1FAB                            ; -> loc_67d1fab
67d1f8f  mov rax,[rcx-8]                               
67d1f93  add rcx,0xFFFFFFFFFFFFFFF8                    
67d1f97  sub rcx,rax                                   
67d1f9a  cmp rcx,0x20                                  
67d1f9e  jae 0x67D2556                                 ; -> loc_67d2556
67d1fa4  add rdx,0x27                                  
67d1fa8  mov rcx,rax                                   
loc_67d1fab:
67d1fab  call 0xE935700                                ; -> sub_e935700
loc_67d1fb0:
67d1fb0  mov [rsi+0x198],r14                           
67d1fb7  add r13,r14                                   
67d1fba  mov [rsi+0x1A0],r13                           
67d1fc1  add rdi,r14                                   
67d1fc4  mov [rsi+0x1A8],rdi                           
67d1fcb  mov r15,[rbp-0x58]                            
67d1fcf  movzx edx,byte ptr [rbp+0x7F]                 
```
Grow-path continuation: stores old begin rax at [r14-8] (header); if cursor==end skip memcpy else memcpy old→new via 0xEEC6DE0 (dst=r14, src=begin, len=cursor-begin); second 0xEEC6DE0 (zero/move tail); validate remaining space (end-begin >= 0x1000 and >= 0x20 slack); corruption → 0xE935700; finalize: [rsi+0x198]=r14(new begin), [rsi+0x1A0]=r13(new cursor), [rsi+0x1A8]=rdi(new end); restore r15=[rbp-0x58], reload cookie.

### Phase E (0x67d1fd3..0x67d2008) — [rbp+0x140] region finalize + [rbp+0x148] region header
```
loc_67d1fd3:
67d1fd3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1fda  mov rax,[rcx]                                 
67d1fdd  mov rax,[rax+0x10]                            
67d1fe1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1fe7  nop                                           
67d1fe8  or r15,0x800                                  
67d1fef  mov [rbp-0x48],r15                            
67d1ff3  mov eax,[rsi+0x198]                           
67d1ff9  not eax                                       
67d1ffb  add eax,[rsi+0x1A0]                           
67d2001  mov [rbp+0x56],ax                             
67d2005  mov r14b,1                                    
loc_67d2008:
67d2008  mov rax,[rbp+0x148]                           
67d200f  cmp byte ptr [rax+1],1                        
67d2013  jne 0x67D209A                                 ; -> loc_67d209a
```
Cookie call; cursor [rsi+0x3F8]!=end [rsi+0x400] → inc cursor; else grow via 0x6760e60(&rsi+0x3F0). Then cookie call; or r12,0x4000000000000; [rbp-0x50]=r12; eax=(~[rsi+0x3F0])+[rsi+0x3F8] → [rbp+0x24] (slot count); r14b=1.

### Phase G (0x67d209a..0x67d212c) — counter region [rbp+0x150] / slot region +0x360/+0x368
```
67d209a  mov rax,[rbp+0x150]                           
67d20a1  cmp byte ptr [rax+1],1                        
67d20a5  jne 0x67D212C                                 ; -> loc_67d212c
67d20ab  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d20b2  mov rax,[rcx]                                 
67d20b5  mov rax,[rax+0x10]                            
67d20b9  mov dl,0x4A                                   
67d20bb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d20c1  mov [rbp+0x7F],al                             
67d20c4  mov rdx,[rsi+0x368]                           
67d20cb  cmp rdx,[rsi+0x370]                           
67d20d2  je short 0x67D20E0                            ; -> loc_67d20e0
67d20d4  inc rdx                                       
67d20d7  mov [rsi+0x368],rdx                           
67d20de  jmp short 0x67D20ED                           ; -> loc_67d20ed
loc_67d20e0:
67d20e0  lea rcx,[rsi+0x360]                           
67d20e7  call 0x6760E60                                ; -> sub_6760e60
67d20ec  nop                                           
loc_67d20ed:
67d20ed  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d20f4  mov rax,[rcx]                                 
67d20f7  mov rax,[rax+0x10]                            
67d20fb  movzx edx,byte ptr [rbp+0x7F]                 
67d20ff  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2105  nop                                           
67d2106  mov rax,0x100000000000000                     
67d2110  or r12,rax                                    
67d2113  mov [rbp-0x50],r12                            
67d2117  mov eax,[rsi+0x360]                           
67d211d  not eax                                       
67d211f  add eax,[rsi+0x368]                           
67d2125  mov [rbp+0x30],ax                             
67d2129  mov r14b,1                                    
loc_67d212c:
67d212c  mov rdi,[rbp+0x158]                           
67d2133  cmp byte ptr [rdi+4],1                        
67d2137  jne 0x67D21C0                                 ; -> loc_67d21c0
67d213d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d2144  mov rax,[rcx]                                 
67d2147  mov rax,[rax+0x10]                            
67d214b  mov dl,0x4A                                   
67d214d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2153  mov [rbp+0x7F],al                             
67d2156  mov rdx,[rsi+0x638]                           
67d215d  cmp rdx,[rsi+0x640]                           
67d2164  je short 0x67D2174                            ; -> loc_67d2174
67d2166  mov eax,[rdi]                                 
67d2168  mov [rdx],eax                                 
67d216a  add qword ptr [rsi+0x638],4                   
67d2172  jmp short 0x67D2184                           ; -> loc_67d2184
loc_67d2174:
67d2174  lea rcx,[rsi+0x630]                           
67d217b  mov r8,rdi                                    
67d217e  call 0x14DB710                                ; -> sub_14db710
67d2183  nop                                           
loc_67d2184:
67d2184  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d218b  mov rax,[rcx]                                 
67d218e  mov rax,[rax+0x10]                            
67d2192  movzx edx,byte ptr [rbp+0x7F]                 
67d2196  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d219c  nop                                           
67d219d  or r12,0x4000000                              
67d21a4  mov [rbp-0x50],r12                            
67d21a8  mov eax,[rsi+0x638]                           
67d21ae  sub eax,[rsi+0x630]                           
67d21b4  shr eax,2                                     
67d21b7  dec eax                                       
67d21b9  mov [rbp-0xC],ax                              
67d21bd  mov r14b,1                                    
loc_67d21c0:
```
If byte [rax+1]==1 (rax=[rbp+0x150]): cookie call; if cursor [rsi+0x368]!=end [rsi+0x370] increment cursor; else grow via 0x6760e60(&rsi+0x360). Then cookie call; or r12,0x100000000000000; [rbp-0x50]=r12; eax=(~[rsi+0x360])+[rsi+0x368] → [rbp+0x30] (slot count); r14b=1.

### Phase H (0x67d212c..0x67d2209) — counter region [rbp+0x158] / dword slot region +0x630/+0x638/+0x640
```
67d212c  mov rdi,[rbp+0x158]                           
67d2133  cmp byte ptr [rdi+4],1                        
67d2137  jne 0x67D21C0                                 ; -> loc_67d21c0
67d213d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d2144  mov rax,[rcx]                                 
67d2147  mov rax,[rax+0x10]                            
67d214b  mov dl,0x4A                                   
67d214d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2153  mov [rbp+0x7F],al                             
67d2156  mov rdx,[rsi+0x638]                           
67d215d  cmp rdx,[rsi+0x640]                           
67d2164  je short 0x67D2174                            ; -> loc_67d2174
67d2166  mov eax,[rdi]                                 
67d2168  mov [rdx],eax                                 
67d216a  add qword ptr [rsi+0x638],4                   
67d2172  jmp short 0x67D2184                           ; -> loc_67d2184
loc_67d2174:
67d2174  lea rcx,[rsi+0x630]                           
67d217b  mov r8,rdi                                    
67d217e  call 0x14DB710                                ; -> sub_14db710
67d2183  nop                                           
loc_67d2184:
67d2184  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d218b  mov rax,[rcx]                                 
67d218e  mov rax,[rax+0x10]                            
67d2192  movzx edx,byte ptr [rbp+0x7F]                 
67d2196  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d219c  nop                                           
67d219d  or r12,0x4000000                              
67d21a4  mov [rbp-0x50],r12                            
67d21a8  mov eax,[rsi+0x638]                           
67d21ae  sub eax,[rsi+0x630]                           
67d21b4  shr eax,2                                     
67d21b7  dec eax                                       
67d21b9  mov [rbp-0xC],ax                              
67d21bd  mov r14b,1                                    
loc_67d21c0:
67d21c0  mov rdi,[rbp+0x168]                           
67d21c7  mov rdx,[rbp+0x160]                           
67d21ce  cmp byte ptr [rdx+0x60],1                     
67d21d2  jne short 0x67D2209                           ; -> loc_67d2209
67d21d4  lea rcx,[rsi+0x5D0]                           
67d21db  call 0x678D690                                ; -> sub_678d690
67d21e0  or r12,0x40000000                             
67d21e7  mov [rbp-0x50],r12                            
67d21eb  mov eax,[rsi+0x5D8]                           
67d21f1  sub eax,[rsi+0x5D0]                           
67d21f7  shr eax,5                                     
67d21fa  imul eax,0xFFFFAAAB                           
67d2200  dec eax                                       
67d2202  mov [rbp-4],ax                                
67d2206  mov r14b,1                                    
loc_67d2209:
```
If byte [rdi+4]==1 (rdi=[rbp+0x158]): cookie call; if cursor [rsi+0x638]!=end [rsi+0x640]: copy dword [rdi]→slot, bump cursor by 4; else grow via 0x14db710(&rsi+0x630, rdi). Then cookie call; or r12,0x4000000; [rbp-0x50]=r12; eax=([rsi+0x638]-[rsi+0x630])>>2, dec → [rbp-0xC] (slot count); r14b=1.

### Phase I (0x67d2209..0x67d228a) — counter region [rbp+0x168]/[rbp+0x160] / slot region +0x5D0/+0x5D8
```
67d21c0  mov rdi,[rbp+0x168]                           
67d21c7  mov rdx,[rbp+0x160]                           
67d21ce  cmp byte ptr [rdx+0x60],1                     
67d21d2  jne short 0x67D2209                           ; -> loc_67d2209
67d21d4  lea rcx,[rsi+0x5D0]                           
67d21db  call 0x678D690                                ; -> sub_678d690
67d21e0  or r12,0x40000000                             
67d21e7  mov [rbp-0x50],r12                            
67d21eb  mov eax,[rsi+0x5D8]                           
67d21f1  sub eax,[rsi+0x5D0]                           
67d21f7  shr eax,5                                     
67d21fa  imul eax,0xFFFFAAAB                           
67d2200  dec eax                                       
67d2202  mov [rbp-4],ax                                
67d2206  mov r14b,1                                    
loc_67d2209:
67d2209  cmp byte ptr [rdi+1],1                        
67d220d  jne short 0x67D228A                           ; -> loc_67d228a
67d220f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d2216  mov rax,[rcx]                                 
67d2219  mov rax,[rax+0x10]                            
67d221d  mov dl,0x4A                                   
67d221f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2225  mov [rbp+0x7F],al                             
67d2228  mov rdx,[rsi+0x6E0]                           
67d222f  cmp rdx,[rsi+0x6E8]                           
67d2236  je short 0x67D2244                            ; -> loc_67d2244
67d2238  inc rdx                                       
67d223b  mov [rsi+0x6E0],rdx                           
67d2242  jmp short 0x67D2251                           ; -> loc_67d2251
loc_67d2244:
67d2244  lea rcx,[rsi+0x6D8]                           
67d224b  call 0x6760E60                                ; -> sub_6760e60
67d2250  nop                                           
loc_67d2251:
67d2251  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d2258  mov rax,[rcx]                                 
67d225b  mov rax,[rax+0x10]                            
67d225f  movzx edx,byte ptr [rbp+0x7F]                 
67d2263  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2269  nop                                           
67d226a  or r12,0x80000                                
67d2271  mov [rbp-0x50],r12                            
67d2275  mov eax,[rsi+0x6D8]                           
67d227b  not eax                                       
67d227d  add eax,[rsi+0x6E0]                           
67d2283  mov [rbp-0x1A],ax                             
67d2287  mov r14b,1                                    
loc_67d228a:
```
If byte [rdx+0x60]==1 (rdx=[rbp+0x160]): call 0x678d690(&rsi+0x5D0); or r12,0x40000000; [rbp-0x50]=r12; eax=([rsi+0x5D8]-[rsi+0x5D0])>>5, imul 0xFFFFAAAB (=/32), dec → [rbp-4] (slot count); r14b=1. Then if byte [rdi+1]==1 (rdi=[rbp+0x168]): cookie call; if cursor [rsi+0x6E0]!=end [rsi+0x6E8] increment cursor; else grow via 0x6760e60(&rsi+0x6D8). Then cookie call; or r12,0x80000; [rbp-0x50]=r12; eax=(~[rsi+0x6D8])+[rsi+0x6E0] → [rbp-0x1A]; r14b=1.

### Phase J (0x67d228a..0x67d2346) — counter region [rbp+0x170] / slot region +0x6D8/+0x6E0/+0x6E8
```
67d228a  mov rdi,[rbp+0x170]                           
67d2291  cmp byte ptr [rdi+0x30],1                     
67d2295  jne 0x67D2346                                 ; -> loc_67d2346
67d229b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d22a2  mov rax,[rcx]                                 
67d22a5  mov rax,[rax+0x10]                            
67d22a9  mov dl,0x4A                                   
67d22ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d22b1  mov [rbp+0x7F],al                             
67d22b4  mov rdx,[rsi+0x590]                           
67d22bb  cmp rdx,[rsi+0x598]                           
67d22c2  je short 0x67D22EE                            ; -> loc_67d22ee
67d22c4  lea rax,[rdx+0x10]                            
67d22c8  mov [rdx],rax                                 
67d22cb  mov rax,0x100000000                           
67d22d5  mov [rdx+8],rax                               
67d22d9  mov rcx,rdx                                   
67d22dc  mov rdx,rdi                                   
67d22df  call 0x6764990                                ; -> sub_6764990
67d22e4  add qword ptr [rsi+0x590],0x30                
67d22ec  jmp short 0x67D22FE                           ; -> loc_67d22fe
loc_67d22ee:
67d22ee  lea rcx,[rsi+0x588]                           
67d22f5  mov r8,rdi                                    
67d22f8  call 0x6765870                                ; -> sub_6765870
67d22fd  nop                                           
loc_67d22fe:
67d22fe  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
67d2305  mov rax,[rcx]                                 
67d2308  mov rax,[rax+0x10]                            
67d230c  movzx edx,byte ptr [rbp+0x7F]                 
67d2310  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2316  nop                                           
67d2317  mov rax,0x200000000                           
67d2321  or r12,rax                                    
67d2324  mov [rbp-0x50],r12                            
67d2328  mov eax,[rsi+0x590]                           
67d232e  sub eax,[rsi+0x588]                           
67d2334  shr eax,4                                     
67d2337  imul eax,0xFFFFAAAB                           
67d233d  dec eax                                       
67d233f  mov [rbp+2],ax                                
67d2343  mov r14b,1                                    
loc_67d2346:
67d2346  mov rax,[rbp+0x178]                           
67d234d  cmp byte ptr [rax+1],1                        
67d2351  jne 0x67D23D8                                 ; -> loc_67d23d8
67d2357  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d235e  mov rax,[rcx]                                 
67d2361  mov rax,[rax+0x10]                            
67d2365  mov dl,0x4A                                   
67d2367  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d236d  mov [rbp+0x7F],al                             
67d2370  mov rdx,[rsi+0x2D8]                           
67d2377  cmp rdx,[rsi+0x2E0]                           
67d237e  je short 0x67D238C                            ; -> loc_67d238c
67d2380  inc rdx                                       
67d2383  mov [rsi+0x2D8],rdx                           
67d238a  jmp short 0x67D2399                           ; -> loc_67d2399
loc_67d238c:
67d238c  lea rcx,[rsi+0x2D0]                           
67d2393  call 0x6760E60                                ; -> sub_6760e60
67d2398  nop                                           
loc_67d2399:
67d2399  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d23a0  mov rax,[rcx]                                 
67d23a3  mov rax,[rax+0x10]                            
67d23a7  movzx edx,byte ptr [rbp+0x7F]                 
67d23ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d23b1  nop                                           
67d23b2  mov rax,0x4000000000000000                    
67d23bc  or r12,rax                                    
67d23bf  mov [rbp-0x50],r12                            
67d23c3  mov eax,[rsi+0x2D0]                           
67d23c9  not eax                                       
67d23cb  add eax,[rsi+0x2D8]                           
67d23d1  mov [rbp+0x3C],ax                             
67d23d5  mov r14b,1                                    
loc_67d23d8:
```
If byte [rdi+0x30]==1 (rdi=[rbp+0x170]): cookie call; if cursor [rsi+0x590]!=end [rsi+0x598]: store [rdx]=[rdx+0x10] (self-link), [rdx+8]=0x100000000 (capacity), then small-vector append via 0x6764990(rdx, rdi), bump cursor by 0x30; else grow via 0x6765870(&rsi+0x588, rdi). Then cookie call; or r12,0x200000000; [rbp-0x50]=r12; eax=([rsi+0x590]-[rsi+0x588])>>4, imul 0xFFFFAAAB (=/16), dec → [rbp+2] (slot count); r14b=1.

### Phase K (0x67d2346..0x67d23d8) — counter region [rbp+0x178] / slot region +0x2D0/+0x2D8/+0x2E0
```
67d2346  mov rax,[rbp+0x178]                           
67d234d  cmp byte ptr [rax+1],1                        
67d2351  jne 0x67D23D8                                 ; -> loc_67d23d8
67d2357  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d235e  mov rax,[rcx]                                 
67d2361  mov rax,[rax+0x10]                            
67d2365  mov dl,0x4A                                   
67d2367  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d236d  mov [rbp+0x7F],al                             
67d2370  mov rdx,[rsi+0x2D8]                           
67d2377  cmp rdx,[rsi+0x2E0]                           
67d237e  je short 0x67D238C                            ; -> loc_67d238c
67d2380  inc rdx                                       
67d2383  mov [rsi+0x2D8],rdx                           
67d238a  jmp short 0x67D2399                           ; -> loc_67d2399
loc_67d238c:
67d238c  lea rcx,[rsi+0x2D0]                           
67d2393  call 0x6760E60                                ; -> sub_6760e60
67d2398  nop                                           
loc_67d2399:
67d2399  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d23a0  mov rax,[rcx]                                 
67d23a3  mov rax,[rax+0x10]                            
67d23a7  movzx edx,byte ptr [rbp+0x7F]                 
67d23ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d23b1  nop                                           
67d23b2  mov rax,0x4000000000000000                    
67d23bc  or r12,rax                                    
67d23bf  mov [rbp-0x50],r12                            
67d23c3  mov eax,[rsi+0x2D0]                           
67d23c9  not eax                                       
67d23cb  add eax,[rsi+0x2D8]                           
67d23d1  mov [rbp+0x3C],ax                             
67d23d5  mov r14b,1                                    
loc_67d23d8:
```
67d2346  mov rax,[rbp+0x178]                           
67d234d  cmp byte ptr [rax+1],1                        
67d2351  jne 0x67D23D8                                 ; -> loc_67d23d8
67d2357  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d235e  mov rax,[rcx]                                 
67d2361  mov rax,[rax+0x10]                            
67d2365  mov dl,0x4A                                   
67d2367  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d236d  mov [rbp+0x7F],al                             
67d2370  mov rdx,[rsi+0x2D8]                           
67d2377  cmp rdx,[rsi+0x2E0]                           
67d237e  je short 0x67D238C                            ; -> loc_67d238c
67d2380  inc rdx                                       
67d2383  mov [rsi+0x2D8],rdx                           
67d238a  jmp short 0x67D2399                           ; -> loc_67d2399
loc_67d238c:
67d238c  lea rcx,[rsi+0x2D0]                           
67d2393  call 0x6760E60                                ; -> sub_6760e60
67d2398  nop                                           
loc_67d2399:
67d2399  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d23a0  mov rax,[rcx]                                 
67d23a3  mov rax,[rax+0x10]                            
67d23a7  movzx edx,byte ptr [rbp+0x7F]                 
67d23ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d23b1  nop                                           
67d23b2  mov rax,0x4000000000000000                    
67d23bc  or r12,rax                                    
67d23bf  mov [rbp-0x50],r12                            
67d23c3  mov eax,[rsi+0x2D0]                           
67d23c9  not eax                                       
67d23cb  add eax,[rsi+0x2D8]                           
67d23d1  mov [rbp+0x3C],ax                             
67d23d5  mov r14b,1                                    
loc_67d23d8:
67d23d8  mov rdi,[rbp+0x188]                           
67d23df  mov rbx,[rbp+0x180]                           
67d23e6  cmp byte ptr [rbx+2],1                        
67d23ea  jne short 0x67D2425                           ; -> loc_67d2425
67d23ec  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d23f3  mov rax,[rcx]                                 
67d23f6  mov rax,[rax+0x10]                            
67d23fa  mov dl,0x4A                                   
67d23fc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2402  mov [rbp+0x7F],al                             
67d2405  mov rdx,[rsi+0x698]                           
67d240c  cmp rdx,[rsi+0x6A0]                           
67d2413  je short 0x67D2439                            ; -> loc_67d2439
67d2415  movzx eax,word ptr [rbx]                      
67d2418  mov [rdx],ax                                  
67d241b  add qword ptr [rsi+0x698],2                   
67d2423  jmp short 0x67D2449                           ; -> loc_67d2449
loc_67d2439:
67d2439  lea rcx,[rsi+0x690]                           
67d2440  mov r8,rbx                                    
67d2443  call 0x1EF6F90                                ; -> sub_1ef6f90
67d2448  nop                                           
loc_67d2449:
67d2449  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d2450  mov rax,[rcx]                                 
67d2453  mov rax,[rax+0x10]                            
67d2457  movzx edx,byte ptr [rbp+0x7F]                 
67d245b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2461  nop                                           
67d2462  or r12,0x400000                               
67d2469  mov [rbp-0x50],r12                            
67d246d  mov eax,[rsi+0x698]                           
67d2473  sub eax,[rsi+0x690]                           
67d2479  shr eax,1                                     
67d247b  dec eax                                       
67d247d  mov [rbp-0x14],ax                             
67d2481  cmp byte ptr [rdi+0x38],1                     
67d2485  jne short 0x67D24BF                           ; -> loc_67d24bf
loc_67d2487:
```
If byte [rax+1]==1 (rax=[rbp+0x178]): cookie call; if cursor [rsi+0x2D8]!=end [rsi+0x2E0] increment cursor; else grow via 0x6760e60(&rsi+0x2D0). Then cookie call; or r12,0x4000000000000000; [rbp-0x50]=r12; eax=(~[rsi+0x2D0])+[rsi+0x2D8] → [rbp+0x3C]; r14b=1.

### Phase L (0x67d23d8..0x67d2487) — counter region [rbp+0x188]/[rbp+0x180] / word slot region +0x690/+0x698/+0x6A0
```
67d23d8  mov rdi,[rbp+0x188]                           
67d23df  mov rbx,[rbp+0x180]                           
67d23e6  cmp byte ptr [rbx+2],1                        
67d23ea  jne short 0x67D2425                           ; -> loc_67d2425
67d23ec  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d23f3  mov rax,[rcx]                                 
67d23f6  mov rax,[rax+0x10]                            
67d23fa  mov dl,0x4A                                   
67d23fc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2402  mov [rbp+0x7F],al                             
67d2405  mov rdx,[rsi+0x698]                           
67d240c  cmp rdx,[rsi+0x6A0]                           
67d2413  je short 0x67D2439                            ; -> loc_67d2439
67d2415  movzx eax,word ptr [rbx]                      
67d2418  mov [rdx],ax                                  
67d241b  add qword ptr [rsi+0x698],2                   
67d2423  jmp short 0x67D2449                           ; -> loc_67d2449
loc_67d2439:
67d2439  lea rcx,[rsi+0x690]                           
67d2440  mov r8,rbx                                    
67d2443  call 0x1EF6F90                                ; -> sub_1ef6f90
67d2448  nop                                           
loc_67d2449:
67d2449  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d2450  mov rax,[rcx]                                 
67d2453  mov rax,[rax+0x10]                            
67d2457  movzx edx,byte ptr [rbp+0x7F]                 
67d245b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2461  nop                                           
67d2462  or r12,0x400000                               
67d2469  mov [rbp-0x50],r12                            
67d246d  mov eax,[rsi+0x698]                           
67d2473  sub eax,[rsi+0x690]                           
67d2479  shr eax,1                                     
67d247b  dec eax                                       
67d247d  mov [rbp-0x14],ax                             
67d2481  cmp byte ptr [rdi+0x38],1                     
67d2485  jne short 0x67D24BF                           ; -> loc_67d24bf
loc_67d2487:
67d2487  mov rcx,rsi                                   
67d248a  add rcx,0x108                                 
67d2491  mov rdx,rdi                                   
67d2494  call 0x67693F0                                ; -> sub_67693f0
67d2499  or r15,0x20000                                
67d24a0  mov [rbp-0x48],r15                            
67d24a4  mov eax,[rsi+0x110]                           
67d24aa  sub eax,[rsi+0x108]                           
67d24b0  shr eax,3                                     
67d24b3  imul eax,0x6DB7                               
67d24b9  dec eax                                       
67d24bb  mov [rbp+0x62],ax                             
loc_67d24bf:
67d24bf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d24c6  mov rax,[rcx]                                 
67d24c9  mov rax,[rax+0x10]                            
67d24cd  mov dl,0x4A                                   
67d24cf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d24d5  mov [rbp+0x7F],al                             
67d24d8  mov rax,[rsi+8]                               
67d24dc  cmp rax,[rsi+0x10]                            
67d24e0  je short 0x67D24FE                            ; -> loc_67d24fe
67d24e2  lea rdx,[rbp-0x50]                            
67d24e6  mov r8d,0xC8                                  
67d24ec  mov rcx,rax                                   
67d24ef  call 0xEEC6EC0                                ; -> sub_eec6ec0
67d24f4  add qword ptr [rsi+8],0xC8                    
67d24fc  jmp short 0x67D250E                           ; -> loc_67d250e
loc_67d24fe:
67d24fe  lea r8,[rbp-0x50]                             
67d2502  mov rcx,rsi                                   
67d2505  mov rdx,rax                                   
67d2508  call 0x5ABA6D0                                ; -> sub_5aba6d0
67d250d  nop                                           
loc_67d250e:
67d250e  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
67d2515  mov rax,[rcx]                                 
67d2518  mov rax,[rax+0x10]                            
67d251c  movzx edx,byte ptr [rbp+0x7F]                 
67d2520  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d2526  nop                                           
loc_67d2527:
67d2527  add rsp,0x108                                 
67d252e  pop rbx                                       
67d252f  pop rdi                                       
67d2530  pop rsi                                       
67d2531  pop r12                                       
67d2533  pop r13                                       
67d2535  pop r14                                       
67d2537  pop r15                                       
67d2539  pop rbp                                       
67d253a  ret                                           
```
If byte [rdi+0x38]==1: call 0x67693f0(&rsi+0x108, rdi); or r15,0x20000; [rbp-0x48]=r15; eax=([rsi+0x110]-[rsi+0x108])>>3, imul 0x6DB7, dec → [rbp+0x62]. Convergence at 0x67d24bf: cookie call; rax=[rsi+8]; if !=end [rsi+0x10]: lea rdx=[rbp-0x50], r8d=0xC8, rcx=rax, call 0xeec6ec0; [rsi+8]+=0xC8; else call 0x5aba6d0(rcx=rsi, rdx=rax). Then cookie call. Epilogue: add rsp,0x108; pop rbx,rdi,rsi,r12,r13,r14,r15,rbp; ret at 0x67d253a. Dead-end size-clamp paths (0x67d254a/0x67d2550/0x67d2576 → sub_75b60/sub_75740; 0x67d2556 → call [0xF9A8C78]) and alloc-retry 0x67d253b→0x9BC830→0x67d1ec7 are unreachable from the linear flow but present in the function range.

## Range 3: 0x669c8f9..0x669c9e2 — call setup, call 0x67d14e0, and teardown start
```
669c8f9  mov [rsp+0xB0],r10                            
669c901  mov [rsp+0xA8],r11                            
669c909  mov [rsp+0xA0],rbx                            
669c911  mov [rsp+0x98],rax                            
669c919  lea rax,[rbp+0x1C48]                          
669c920  mov [rsp+0x90],rax                            
669c928  lea rax,[rbp+0x1CB0]                          
669c92f  mov [rsp+0x88],rax                            
669c937  lea rax,[rbp+0x1CB8]                          
669c93e  mov [rsp+0x80],rax                            
669c946  lea rax,[rbp+0x1CC0]                          
669c94d  mov [rsp+0x78],rax                            
669c952  lea rax,[rbp+0x1CC8]                          
669c959  mov [rsp+0x70],rax                            
669c95e  lea rax,[rbp+0x1CD0]                          
669c965  mov [rsp+0x68],rax                            
669c96a  lea rax,[rbp+0x1CD8]                          
669c971  mov [rsp+0x60],rax                            
669c976  lea rax,[rbp+0x1CE0]                          
669c97d  mov [rsp+0x58],rax                            
669c982  mov [rsp+0x50],r12                            
669c987  mov [rsp+0x48],r13                            
669c98c  lea rax,[rbp+0x1CF8]                          
669c993  mov [rsp+0x40],rax                            
669c998  mov [rsp+0x38],rsi                            
669c99d  mov [rsp+0x30],rdi                            
669c9a2  mov [rsp+0x28],r14                            
669c9a7  mov [rsp+0x20],r15                            
669c9ac  lea rax,[rbp+0x1BB8]                          
669c9b3  mov [rsp+0xB8],rax                            
669c9bb  call 0x67D14E0                                ; -> sub_67d14e0
669c9c0  nop                                           
669c9c1  lea rax,[0xF2BEDD0]                           ; [data_f2bedd0]
669c9c8  mov [rbp+0x1BB0],rax                          
669c9cf  lea rcx,[rbp+0x1BB8]                          
669c9d6  call 0x675DF40                                ; -> sub_675df40
669c9db  lea rcx,[rbp+0x1880]                          
669c9e2  call 0x675DF40                                ; -> sub_675df40
```
Spills callee-args/registers to stack frame (r10,r11,rbx,rax and lea pointers to local structs at [rbp+0x1C48..0x1CF8], plus r12,r13,rsi,rdi,r14,r15 and [rbp+0x1BB8] at [rsp+0xB8]); calls sub_67d14e0 (draw-list submit); stores global [data_f2bedd0]→[rbp+0x1BB0]; calls sub_675df40(&rbp+0x1BB8) then sub_675df40(&rbp+0x1880). Ends at 0x669c9e2 where the post-call epilogue (movaps xmm6..xmm9, add rsp,0x2158, pop rbx/rdi/rsi/r12/r13/r14/r15/rbp, ret at 0x669ca18) begins — outside this range.

## Range 1: 0x669c35f..0x669c8f9 — draw packet field copies (G phase)

### Phase 1 (0x669c35f..0x669c389)
```
669c35f  mov eax,[rbp+0x18C0]                           
669c365  mov [rbp+0x1BF8],eax                           
669c36b  movzx eax,word ptr [rbp+0x18C8]               
669c372  mov [rbp+0x1C00],ax                           
669c379  mov byte ptr [rbp+0x1C38],0                   
669c380  cmp byte ptr [rbp+0x1900],1                   
669c387  jne short 0x669C3C2                           ; -> loc_669c3c2
```
Copies dword [rbp+0x18C0]→[rbp+0x1BF8], zero-extends word [rbp+0x18C8]→[rbp+0x1C00], initialises byte [rbp+0x1C38]=0, branches on byte [rbp+0x1900]==1.

### Phase 2 (0x669c389..0x669c3c2)
```
669c389  lea rdx,[rbp+0x18D0]                          
669c390  lea rcx,[rbp+0x1C08]                          
669c397  lea rax,[rbp+0x1C18]                          
669c39e  mov [rbp+0x1C08],rax                          
669c3a5  mov rax,0x100000000                           
669c3af  mov [rbp+0x1C10],rax                          
669c3b6  call 0x6764990                                ; -> sub_6764990
669c3bb  mov byte ptr [rbp+0x1C38],1                   
```
When [rbp+0x1900]==1: small-vector append via `0x6764990(&rbp+0x1C08, &rbp+0x18D0)` with capacity 0x100000000 at [rbp+0x1C10], then sets [rbp+0x1C38]=1.

### Phase 3 (0x669c3c2..0x669c3eb)
```
669c3c2  movzx eax,word ptr [rbp+0x1908]               
669c3c9  mov [rbp+0x1C40],ax                           
669c3d0  lea rax,[rbp+0x1C48]                          
669c3d7  mov byte ptr [rbp+0x1CA8],0                   
669c3de  cmp byte ptr [rbp+0x1970],1                   
669c3e5  jne 0x669C4F7                                 ; -> loc_669c4f7
```
Copies word [rbp+0x1908]→[rbp+0x1C40], initialises byte [rbp+0x1CA8]=0, branches on byte [rbp+0x1970]==1.

### Phase 4 (0x669c3eb..0x669c40c)
```
669c3eb  xorps xmm0,xmm0                               
669c3ee  movups [rax],xmm0                             
669c3f1  mov rax,[rbp+0x1918]                          
669c3f8  test rax,rax                                  
669c3fb  je short 0x669C40A                            ; -> loc_669c40a
669c3fd  lock inc dword ptr [rax+8]                    
669c401  mov rax,[rbp+0x1918]                          
669c408  jmp short 0x669C40C                           ; -> loc_669c40c
669c40a  xor eax,eax                                   
669c40c  mov rcx,[rbp+0x1910]                          
```
When [rbp+0x1970]!=1: zeroes xmm0, stores 16 bytes to [rbp+0x1C48]; loads shared_ptr from [rbp+0x1918], lock-increments refcount if non-null, stores ptr to [rbp+0x1C48] and refcount-ptr to [rbp+0x1C50].

### Phase 5 (0x669c40c..0x669c444)
```
669c40c  mov rcx,[rbp+0x1910]                          
669c413  mov [rbp+0x1C48],rcx                          
669c41a  mov [rbp+0x1C50],rax                          
669c421  movaps xmm1,[rbp+0x1920]                      
669c428  movups [rbp+0x1C58],xmm1                      
669c42f  movzx eax,word ptr [rbp+0x1930]               
669c436  mov [rbp+0x1C68],ax                           
669c43d  movups [rbp+0x1C70],xmm0                      
669c444  mov rax,[rbp+0x1940]                          
```
Stores [rbp+0x1910]→[rbp+0x1C48], [rbp+0x1918]→[rbp+0x1C50], xmm [rbp+0x1920]→[rbp+0x1C58], word [rbp+0x1930]→[rbp+0x1C68], xmm0→[rbp+0x1C70], loads [rbp+0x1940].

### Phase 6 (0x669c444..0x669c46d)
```
669c444  mov rax,[rbp+0x1940]                          
669c44b  test rax,rax                                  
669c44e  je short 0x669C45D                            ; -> loc_669c45d
669c450  lock inc dword ptr [rax+8]                    
669c454  mov rax,[rbp+0x1940]                          
669c45b  jmp short 0x669C45F                           ; -> loc_669c45f
669c45d  xor eax,eax                                   
669c45f  mov rdx,[rbp+0x1938]                          
669c466  mov rcx,[rbp+0x1950]                          
```
If [rbp+0x1940] non-null: lock-increments its refcount; stores [rbp+0x1938]→rdx, [rbp+0x1950]→rcx.

### Phase 7 (0x669c45f..0x669c496)
```
669c45f  mov rdx,[rbp+0x1938]                          
669c466  mov rcx,[rbp+0x1950]                          
669c46d  mov [rbp+0x1C70],rdx                          
669c474  mov [rbp+0x1C78],rax                          
669c47b  movups [rbp+0x1C80],xmm0                      
669c482  test rcx,rcx                                  
669c485  je short 0x669C494                            ; -> loc_669c494
669c487  lock inc dword ptr [rcx+8]                    
669c48b  mov rax,[rbp+0x1950]                          
669c492  jmp short 0x669C496                           ; -> loc_669c496
669c494  xor eax,eax                                   
669c496  mov rdx,[rbp+0x1948]                          
```
Stores rdx→[rbp+0x1C70], rax→[rbp+0x1C78], xmm0→[rbp+0x1C80]; if rcx=[rbp+0x1950] non-null: lock-inc, stores to [rbp+0x1C88]; loads [rbp+0x1948]→rdx.

### Phase 8 (0x669c496..0x669c4cd)
```
669c496  mov rdx,[rbp+0x1948]                          
669c49d  mov rcx,[rbp+0x1960]                          
669c4a4  mov [rbp+0x1C80],rdx                          
669c4ab  mov [rbp+0x1C88],rax                          
669c4b2  movups [rbp+0x1C90],xmm0                      
669c4b9  test rcx,rcx                                  
669c4bc  je short 0x669C4CB                            ; -> loc_669c4cb
669c4be  lock inc dword ptr [rcx+8]                    
669c4c2  mov rax,[rbp+0x1960]                          
669c4c9  jmp short 0x669C4CD                           ; -> loc_669c4cd
669c4cb  xor eax,eax                                   
669c4cd  mov rcx,[rbp+0x1958]                          
```
Stores rdx→[rbp+0x1C80], rax→[rbp+0x1C88], xmm0→[rbp+0x1C90]; if rcx=[rbp+0x1960] non-null: lock-inc, stores to [rbp+0x1C98]; loads [rbp+0x1958]→rcx.

### Phase 9 (0x669c4cd..0x669c4f7)
```
669c4cd  mov rcx,[rbp+0x1958]                          
669c4d4  mov rdx,[rbp+0x1968]                          
669c4db  mov [rbp+0x1C90],rcx                          
669c4e2  mov [rbp+0x1C98],rax                          
669c4e9  mov [rbp+0x1CA0],rdx                          
669c4f0  mov byte ptr [rbp+0x1CA8],1                   
669c4f7  mov rax,[rbp+0x1978]                          
```
Stores rcx→[rbp+0x1C90], rax→[rbp+0x1C98], rdx→[rbp+0x1CA0], sets byte [rbp+0x1CA8]=1, loads [rbp+0x1978]→rax.

### Phase 10 (0x669c4f7..0x669c58a)
```
669c4f7  mov rax,[rbp+0x1978]                          
669c4fe  mov [rbp+0x1CB0],rax                          
669c505  movzx eax,word ptr [rbp+0x1980]               
669c50c  mov [rbp+0x1CB8],ax                           
669c513  movzx eax,word ptr [rbp+0x1988]               
669c51a  mov [rbp+0x1CC0],ax                           
669c521  movzx eax,word ptr [rbp+0x1990]               
669c528  mov [rbp+0x1CC8],ax                           
669c52f  movzx eax,word ptr [rbp+0x1998]               
669c536  mov [rbp+0x1CD0],ax                           
669c53d  movzx eax,word ptr [rbp+0x19A0]               
669c544  mov [rbp+0x1CD8],ax                           
669c54b  movzx eax,word ptr [rbp+0x19A8]               
669c552  mov [rbp+0x1CE0],ax                           
669c559  movzx eax,word ptr [rbp+0x19B0]               
669c560  mov [rbp+0x1CE8],ax                           
669c567  movzx eax,word ptr [rbp+0x19B8]               
669c56e  mov [rbp+0x1CF0],ax                           
669c575  movzx eax,word ptr [rbp+0x19C0]               
669c57c  mov [rbp+0x1CF8],ax                           
669c583  mov byte ptr [rbp+0x1D2C],0                   
```
Copies words [rbp+0x1978]→[rbp+0x1CB0], [0x1980]→[0x1CB8], [0x1988]→[0x1CC0], [0x1990]→[0x1CC8], [0x1998]→[0x1CD0], [0x19A0]→[0x1CD8], [0x19A8]→[0x1CE0], [0x19B0]→[0x1CE8], [0x19B8]→[0x1CF0], [0x19C0]→[0x1CF8]; initialises byte [rbp+0x1D2C]=0.

### Phase 11 (0x669c58a..0x669c5a3)
```
669c58a  cmp byte ptr [rbp+0x19F4],1                   
669c591  jne short 0x669C5DD                           ; -> loc_669c5dd
669c593  mov byte ptr [rbp+0x1D18],0xFF                
669c59a  cmp byte ptr [rbp+0x19E0],0xFF                
669c5a1  je short 0x669C5C8                            ; -> loc_669c5c8
```
If byte [rbp+0x19F4]==1: sets byte [rbp+0x1D18]=0xFF; if byte [rbp+0x19E0]==0xFF jumps to 0x669c5c8.

### Phase 12 (0x669c5a3..0x669c5dd)
```
669c5a3  movups xmm0,[rbp+0x19C8]                      
669c5aa  movups [rbp+0x1D00],xmm0                      
669c5b1  movsd xmm0,[rbp+0x19D8]                       
669c5b9  movsd [rbp+0x1D10],xmm0                       
669c5c1  mov byte ptr [rbp+0x1D18],0                   
669c5c8  movups xmm0,[rbp+0x19E4]                      
669c5cf  movups [rbp+0x1D1C],xmm0                      
669c5d6  mov byte ptr [rbp+0x1D2C],1                   
669c5dd  mov eax,[rbp+0x19F8]                          
```
If [rbp+0x19E0]!=0xFF: copies xmm [rbp+0x19C8]→[rbp+0x1D00], sd [rbp+0x19D8]→[rbp+0x1D10], sets byte [rbp+0x1D18]=0. Then copies xmm [rbp+0x19E4]→[rbp+0x1D1C], sets byte [rbp+0x1D2C]=1, loads dword [rbp+0x19F8]→eax.

### Phase 13 (0x669c5dd..0x669c5f9)
```
669c5dd  mov eax,[rbp+0x19F8]                          
669c5e3  mov [rbp+0x1D30],eax                          
669c5e9  mov byte ptr [rbp+0x1D44],0                   
669c5f0  cmp byte ptr [rbp+0x1A0C],1                   
669c5f7  jne short 0x669C620                           ; -> loc_669c620
```
Stores dword [rbp+0x19F8]→[rbp+0x1D30], initialises byte [rbp+0x1D44]=0, branches on byte [rbp+0x1A0C]==1.

### Phase 14 (0x669c5f9..0x669c620)
```
669c5f9  movsd xmm0,[rbp+0x1A00]                       
669c601  movsd [rbp+0x1D38],xmm0                       
669c609  movss xmm0,[rbp+0x1A08]                       
669c611  movss [rbp+0x1D40],xmm0                       
669c619  mov byte ptr [rbp+0x1D44],1                   
669c620  mov byte ptr [rbp+0x1DA0],0                   
```
If [rbp+0x1A0C]==1: copies sd [rbp+0x1A00]→[rbp+0x1D38], ss [rbp+0x1A08]→[rbp+0x1D40], sets byte [rbp+0x1D44]=1. Initialises byte [rbp+0x1DA0]=0.

### Phase 15 (0x669c620..0x669c68d)
```
669c620  mov byte ptr [rbp+0x1DA0],0                   
669c627  cmp byte ptr [rbp+0x1A68],1                   
669c62e  jne short 0x669C68D                           ; -> loc_669c68d
669c630  lea rax,[rbp+0x1A38]                          
669c637  mov ecx,[rax-0x18]                            
669c63a  mov [rbp+0x1D58],ecx                          
669c640  movups xmm0,[rax-0x28]                        
669c644  movups [rbp+0x1D48],xmm0                      
669c64b  movzx ecx,byte ptr [rbp+0x1A24]               
669c652  mov [rbp+0x1D5C],cl                           
669c658  movups xmm0,[rbp+0x1A28]                      
669c65f  movups [rbp+0x1D60],xmm0                      
669c666  movups xmm0,[rax]                             
669c669  movups xmm1,[rax+0x10]                        
669c66d  movups xmm2,[rax+0x1F]                        
669c671  movups [rbp+0x1D70],xmm0                      
669c678  movups [rbp+0x1D80],xmm1                      
669c67f  movups [rbp+0x1D8F],xmm2                      
669c686  mov byte ptr [rbp+0x1DA0],1                   
669c68d  mov byte ptr [rbp+0x1DF0],0                   
```
If byte [rbp+0x1A68]==1: lea rax=[rbp+0x1A38]; dword [rax-0x18]→[rbp+0x1D58]; xmm [rax-0x28]→[rbp+0x1D48]; byte [rbp+0x1A24]→[rbp+0x1D5C]; xmm [rbp+0x1A28]→[rbp+0x1D60]; xmm [rax],[rax+0x10],[rax+0x1F]→[rbp+0x1D70],[rbp+0x1D80],[rbp+0x1D8F]; sets byte [rbp+0x1DA0]=1. Initialises byte [rbp+0x1DF0]=0.

### Phase 16 (0x669c68d..0x669c70a)
```
669c68d  mov byte ptr [rbp+0x1DF0],0                   
669c694  cmp byte ptr [rbp+0x1AB8],1                   
669c69b  jne 0x669C748                                 ; -> loc_669c748
669c6a1  mov byte ptr [rbp+0x1DE8],0xFF                
669c6a8  movzx eax,byte ptr [rbp+0x1AB0]               
669c6af  movzx ecx,al                                  
669c6b2  cmp ecx,1                                     
669c6b5  jg short 0x669C6F5                            ; -> loc_669c6f5
669c6b7  test ecx,ecx                                  
669c6b9  jne short 0x669C70A                           ; -> loc_669c70a
669c6bb  movaps xmm0,[rbp+0x1A70]                      
669c6c2  movaps xmm1,[rbp+0x1A80]                      
669c6c9  movaps xmm2,[rbp+0x1A90]                      
669c6d0  movaps xmm3,[rbp+0x1AA0]                      
669c6d7  movups [rbp+0x1DA8],xmm0                      
669c6de  movups [rbp+0x1DB8],xmm1                      
669c6e5  movups [rbp+0x1DC8],xmm2                      
669c6ec  movups [rbp+0x1DD8],xmm3                      
669c6f3  jmp short 0x669C73B                           ; -> loc_669c73b
```
If byte [rbp+0x1AB8]==1: sets byte [rbp+0x1DE8]=0xFF; zero-extends byte [rbp+0x1AB0]→ecx; if ecx>1 jumps to 0x669c6f5; if ecx!=0 jumps to 0x669c70a; else (ecx==0) copies four xmm regs from [rbp+0x1A70..0x1AA0] to [rbp+0x1DA8..0x1DD8].

### Phase 17 (0x669c70a..0x669c748)
```
669c70a  mov rcx,[rbp+0x1A80]                          
669c711  mov qword ptr [rbp+0x1A80],0                  
669c71c  movaps xmm0,[rbp+0x1A70]                      
669c723  xorps xmm1,xmm1                               
669c726  movaps [rbp+0x1A70],xmm1                      
669c72d  movups [rbp+0x1DA8],xmm0                      
669c734  mov [rbp+0x1DB8],rcx                          
669c73b  mov [rbp+0x1DE8],al                           
669c741  mov byte ptr [rbp+0x1DF0],1                   
669c748  mov byte ptr [rbp+0x1E80],0                   
```
If ecx==1: moves qword [rbp+0x1A80]→rcx, zeroes [rbp+0x1A80], xmm [rbp+0x1A70]→xmm0, zeroes xmm1, stores xmm1 to [rbp+0x1A70], xmm0 to [rbp+0x1DA8], rcx to [rbp+0x1DB8], al to [rbp+0x1DE8]. Sets byte [rbp+0x1DF0]=1, initialises byte [rbp+0x1E80]=0.

### Phase 18 (0x669c748..0x669c79a)
```
669c748  mov byte ptr [rbp+0x1E80],0                   
669c74f  cmp byte ptr [rbp+0x1B48],1                   
669c756  jne short 0x669C79A                           ; -> loc_669c79a
669c758  mov rax,[rbp+0x1AC0]                          
669c75f  mov [rbp+0x1DF8],rax                          
669c766  lea rcx,[rbp+0x1E00]                          
669c76d  lea rdx,[rbp+0x1AC8]                          
669c774  call 0xE869FF0                                ; -> sub_e869ff0
669c779  nop                                           
669c77a  mov rax,[rbp+0x1B40]                          
669c781  mov [rbp+0x1E78],rax                          
669c788  mov qword ptr [rbp+0x1B40],0                  
669c793  mov byte ptr [rbp+0x1E80],1                   
```
If byte [rbp+0x1B48]==1: copies qword [rbp+0x1AC0]→[rbp+0x1DF8]; calls `0xe869ff0(&rbp+0x1E00, &rbp+0x1AC8)` (transform copy); copies qword [rbp+0x1B40]→[rbp+0x1E78], zeroes [rbp+0x1B40]; sets byte [rbp+0x1E80]=1.

### Phase 19 (0x669c79a..0x669c7e6)
```
669c79a  lea r10,[rbp+0x1BF8]                          
669c7a1  lea r11,[rbp+0x1C00]                          
669c7a8  lea rax,[rbp+0x1C40]                          
669c7af  lea r12,[rbp+0x1CE8]                          
669c7b6  lea r13,[rbp+0x1CF0]                          
669c7bd  cmp byte ptr [rbp+0x1BA8],1                   
669c7c4  mov byte ptr [rbp+0x1EE0],0                   
669c7cb  lea rsi,[rbp+0x1D00]                          
669c7d2  lea rdi,[rbp+0x1D30]                          
669c7d9  lea r9,[rbp+0x1DA8]                           
669c7e0  jne 0x669C8CD                                 ; -> loc_669c8cd
```
Lea address table: r10=[rbp+0x1BF8], r11=[rbp+0x1C00], rax=[rbp+0x1C40], r12=[rbp+0x1CE8], r13=[rbp+0x1CF0]; initialises byte [rbp+0x1EE0]=0; lea rsi=[rbp+0x1D00], rdi=[rbp+0x1D30], r9=[rbp+0x1DA8]; if byte [rbp+0x1BA8]==1 jumps to 0x669c8cd.

### Phase 20 (0x669c7e6..0x669c84e)
```
669c7e6  movaps xmm0,[rbp+0x1B50]                      
669c7ed  movaps xmm1,[rbp+0x1B60]                      
669c7f4  mov qword ptr [rbp+0x1B58],0                  
669c7ff  movups [rbp+0x1E88],xmm0                      
669c806  xorps xmm0,xmm0                               
669c809  movaps [rbp+0x1B60],xmm0                      
669c810  movups [rbp+0x1E98],xmm1                      
669c817  mov rcx,[rbp+0x1B70]                          
669c81e  mov [rbp+0x1EA8],rcx                          
669c825  mov byte ptr [rbp+0x1EC0],0xFF                
669c82c  movzx ecx,byte ptr [rbp+0x1B88]               
669c833  cmp rcx,3                                     
669c837  ja short 0x669C8AA                            ; -> loc_669c8aa
669c839  lea r14,[rbp+0x1EB0]                          
669c840  lea r8,[0xF2BF7B8]                            ; [data_f2bf7b8]
669c847  movsxd rdx,[r8+rcx*4]                         
669c84b  add rdx,r8                                    
669c84e  jmp rdx                                       
```
If [rbp+0x1BA8]!=1: xmm [rbp+0x1B50]→[rbp+0x1E88], zeroes [rbp+0x1B58]/[rbp+0x1B60], xmm [rbp+0x1B60]→[rbp+0x1E98], qword [rbp+0x1B70]→[rbp+0x1EA8], byte [rbp+0x1EC0]=0xFF; zero-extends byte [rbp+0x1B88]; if >3 jumps to 0x669c8aa; else jump-table via [0xF2BF7B8+rcx*4].

### Phase 21 (0x669c850..0x669c8aa)
```
669c850  mov rdx,[rbp+0x1B78]                          
669c857  mov [rbp+0x1EB0],rdx                          
669c85e  jmp short 0x669C8A4                           ; -> loc_669c8a4
669c860  lea rdx,[rbp+0x1B78]                          
669c867  movups xmm0,[rdx]                             
669c86a  movups [r14],xmm0                             
669c86e  jmp short 0x669C8A4                           ; -> loc_669c8a4
669c870  movups [r14],xmm0                             
669c874  mov rdx,[rbp+0x1B80]                          
669c87b  test rdx,rdx                                  
669c87e  je short 0x669C88D                            ; -> loc_669c88d
669c880  lock inc dword ptr [rdx+8]                    
669c884  mov rdx,[rbp+0x1B80]                          
669c88b  jmp short 0x669C88F                           ; -> loc_669c88f
669c88d  xor edx,edx                                   
669c88f  mov r8,[rbp+0x1B78]                           
669c896  mov [rbp+0x1EB0],r8                           
669c89d  mov [rbp+0x1EB8],rdx                          
```
Jump-table targets: case 0 → [rbp+0x1B78]→[rbp+0x1EB0]; case 1 → xmm [rbp+0x1B78]→[r14]; case 2 → xmm0→[r14], qword [rbp+0x1B80]→rdx with lock-inc refcount if non-null, then [rbp+0x1B78]→[rbp+0x1EB0], rdx→[rbp+0x1EB8].

### Phase 22 (0x669c8aa..0x669c8f9)
```
669c8aa  mov rcx,[rbp+0x1BA0]                          
669c8b1  mov [rbp+0x1ED8],rcx                          
669c8b8  movaps xmm0,[rbp+0x1B90]                      
669c8bf  movups [rbp+0x1EC8],xmm0                      
669c8c6  mov byte ptr [rbp+0x1EE0],1                   
669c8cd  mov ecx,0x9D0                                 
669c8d2  add rcx,[rbx+0x10]                            
669c8d6  lea rbx,[rbp+0x1C08]                          
669c8dd  lea r14,[rbp+0x1D38]                          
669c8e4  lea r15,[rbp+0x1D48]                          
669c8eb  lea r8,[rbp+0x1DF8]                           
669c8f2  lea rdx,[rbp+0x1E88]                          
669c8f9  mov [rsp+0xB0],r10                            
```
Common post-switch: qword [rbp+0x1BA0]→[rbp+0x1ED8], xmm [rbp+0x1B90]→[rbp+0x1EC8], byte [rbp+0x1EE0]=1; ecx=0x9D0, add rcx,[rbx+0x10]; lea rbx=[rbp+0x1C08], r14=[rbp+0x1D38], r15=[rbp+0x1D48], r8=[rbp+0x1DF8], rdx=[rbp+0x1E88]; stores r10 to [rsp+0xB0] (call-argument setup for 0x67d14e0).

---

## Range 2: 0x669be56..0x669bef8 — pass-kind leaf selection

### Phase A (0x669be56..0x669be8a)
```
669be56  cmp byte ptr [rbp+0x19A9],0                   
669be5d  jne short 0x669BE66                           ; -> loc_669be66
669be5f  mov byte ptr [rbp+0x19A9],1                   
669be66  test byte ptr [r8+0x78],0x20                  ; R a2+0x78
669be6b  jne 0x669CA19                                 ; -> loc_669ca19
669be71  cmp byte ptr [rbp+0x18C9],0                   
669be78  jne 0x669CA29                                 ; -> loc_669ca29
669be7e  mov byte ptr [rbp+0x18C9],1                   
669be85  jmp 0x669CA29                                 ; -> loc_669ca29
```
One-time guard: sets byte [rbp+0x19A9]=1; tests byte [r8+0x78]&0x20 (desc flag) — if set jumps to 0x669ca19; checks byte [rbp+0x18C9] — if non-zero jumps to 0x669ca29, else sets it to 1 and jumps to 0x669ca29.

### Phase B (0x669be8a..0x669beaa)
```
669be8a  mov r14b,2                                    
669be8d  mov si,0x8800                                 
669be91  cmp byte ptr [rbp+0x1991],0                   
669be98  jne 0x669BD5D                                 ; -> sub_669bd5d
669be9e  mov byte ptr [rbp+0x1991],1                   
669bea5  jmp 0x669BD5D                                 ; -> sub_669bd5d
```
Sets pass kind r14b=2, state mask si=0x8800; one-time guard on byte [rbp+0x1991], then jumps to secondary geometry at 0x669bd5d.

### Phase C (0x669beaa..0x669bed6)
```
669beaa  cmp eax,2                                     
669bead  setae dl                                      
669beb0  or dl,cl                                      
669beb2  movsd xmm0,[r8+0x6C]                          ; R a2+0x6C
669beb8  movss xmm1,[r8+0x68]                          ; R a2+0x68
669bebe  movzx eax,byte ptr [rbp+0x1A0C]               
669bec5  movss [rbp+0x1A00],xmm1                       
669becd  test dl,1                                     
669bed0  je 0x669CAD5                                  ; -> loc_669cad5
```
Compares eax>=2 (setae dl), ors dl with cl; loads xmm0=[r8+0x6C], xmm1=[r8+0x68]; stores xmm1 to [rbp+0x1A00]; zero-extends byte [rbp+0x1A0C]→eax; tests bit0 of dl, if zero jumps to 0x669cad5.

### Phase D (0x669bed6..0x669bee1)
```
669bed6  test al,al                                    
669bed8  jne short 0x669BEE1                           ; -> loc_669bee1
669beda  mov byte ptr [rbp+0x1A0C],1                   
669bee1  movlps [rbp+0x1A04],xmm0                      
```
If al==0: sets byte [rbp+0x1A0C]=1; stores xmm0 low quad to [rbp+0x1A04].

### Phase E (0x669bee1..0x669bef8)
```
669bee1  movlps [rbp+0x1A04],xmm0                      
669bee8  cmp byte ptr [rbp+0x19B9],0                   
669beef  jne short 0x669BEF8                           ; -> loc_669bef8
669bef1  mov byte ptr [rbp+0x19B9],1                   
669bef8  mov si,0x8000                                 
```
If byte [rbp+0x19B9]==0: sets it to 1; falls to 0x669bef8 where state mask si=0x8000.

---

## Callee 0x67d14e0 — first 120 instructions

### Phase 1 (0x67d14e0..0x67d1560)
```
67d14e0  push rbp                                      
67d14e1  push r15                                      
67d14e3  push r14                                      
67d14e5  push r13                                      
67d14e7  push r12                                      
67d14e9  push rsi                                      
67d14ea  push rdi                                      
67d14eb  push rbx                                      
67d14ec  sub rsp,0x108                                 
67d14f3  lea rbp,[rsp+0x80]                            
67d14fb  mov qword ptr [rbp+0x80],0xFFFFFFFFFFFFFFFE   
67d1506  mov rdi,r9                                    
67d1509  mov rbx,r8                                    
67d150c  mov rsi,rdx                                   
67d150f  call 0x5ABA5C0                                ; -> sub_5aba5c0
67d1514  mov rdx,rsi                                   
67d1517  mov rsi,rax                                   
67d151a  xorps xmm0,xmm0                               
67d151d  movaps [rbp+0x60],xmm0                        
67d1521  movaps [rbp+0x50],xmm0                        
67d1525  movaps [rbp+0x40],xmm0                        
67d1529  movaps [rbp+0x30],xmm0                        
67d152d  movaps [rbp+0x20],xmm0                        
67d1531  movaps [rbp+0x10],xmm0                        
67d1535  movaps [rbp],xmm0                             
67d1539  movaps [rbp-0x10],xmm0                        
67d153d  movaps [rbp-0x20],xmm0                        
67d1541  movaps [rbp-0x30],xmm0                        
67d1545  movaps [rbp-0x40],xmm0                        
67d1549  movaps [rbp-0x50],xmm0                        
67d154d  mov qword ptr [rbp+0x70],0                    
```
Prologue: pushes rbp,r15,r14,r13,r12,rsi,rdi,rbx; sub rsp,0x108; rbp=rsp+0x80; [rbp+0x80]=-2 (try-level); rdi=r9, rbx=r8, rsi=rdx; calls 0x5aba5c0; rdx=rsi, rsi=rax; zeroes 11 xmm slots at [rbp+0x60..rbp-0x50]; [rbp+0x70]=0.

### Phase 2 (0x67d154d..0x67d15ad)
```
67d154d  mov qword ptr [rbp+0x70],0                    
67d1555  movzx r14d,byte ptr [rdx+0x58]                ; R a1+0x58
67d155a  cmp r14b,1                                    
67d155e  jne short 0x67D15AD                           ; -> loc_67d15ad
67d1560  lea rcx,[rsi+0x780]                           ; R ret@5aba5c0+0x780
67d1567  call 0x675F3B0                                ; -> sub_675f3b0
67d156c  mov qword ptr [rbp-0x50],0x1000               
67d1574  mov eax,[rsi+0x788]                           ; R ret@5aba5c0+0x788
67d157a  sub eax,[rsi+0x780]                           ; R ret@5aba5c0+0x780
67d1580  shr eax,3                                     
67d1583  imul eax,0xFFFF8BA3                           
67d1589  dec eax                                       
67d158b  mov [rbp-0x28],ax                             
67d158f  mov r12d,0x1000                               
67d1595  cmp byte ptr [rbx+0x88],1                     ; R a2+0x88
67d159c  je short 0x67D15B9                            ; -> loc_67d15b9
67d159e  cmp byte ptr [rdi+0x48],1                     ; R a3+0x48
67d15a2  je 0x67D1677                                  ; -> loc_67d1677
67d15a8  jmp 0x67D16E5                                 ; -> loc_67d16e5
67d15ad  xor r12d,r12d                                 
67d15b0  cmp byte ptr [rbx+0x88],1                     
67d15b7  jne short 0x67D159E                           ; -> loc_67d159e
```
Loads byte [rdx+0x58]→r14d; if r14b==1: calls 0x675f3b0(&rsi+0x780); [rbp-0x50]=0x1000; eax=([rsi+0x788]-[rsi+0x780])>>3, imul 0xFFFF8BA3, dec → [rbp-0x28]; r12d=0x1000; if byte [rbx+0x88]==1 jumps to 0x67d15b9 else to 0x67d159e. If r14b!=1: r12d=0; if [rbx+0x88]==1 jumps to 0x67d15b9 else to 0x67d159e.

### Phase 3 (0x67d159e..0x67d162f)
```
67d159e  cmp byte ptr [rdi+0x48],1                     ; R a3+0x48
67d15a2  je 0x67D1677                                  ; -> loc_67d1677
67d15a8  jmp 0x67D16E5                                 ; -> loc_67d16e5
67d15b9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d15c0  mov rax,[rcx]                                 
67d15c3  mov rax,[rax+0x10]                            
67d15c7  mov dl,0x4A                                   
67d15c9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d15cf  mov [rbp+0x7F],al                             
67d15d2  mov r14,[rsi+0x770]                           
67d15d9  cmp r14,[rsi+0x778]                           
67d15e0  je short 0x67D161C                            ; -> loc_67d161c
67d15e2  mov rax,[rbx]                                 
67d15e5  mov [r14],rax                                 
67d15e8  lea rcx,[r14+8]                               
67d15ec  lea rdx,[rbx+8]                               
67d15f0  call 0xE869FF0                                ; -> sub_e869ff0
67d15f5  nop                                           
67d15f6  mov rax,[rbx+0x80]                            
67d15fd  mov [r14+0x80],rax                            
67d1604  mov qword ptr [rbx+0x80],0                    
67d160f  add qword ptr [rsi+0x770],0x88                
67d161a  jmp short 0x67D162F                           ; -> loc_67d162f
67d161c  lea rcx,[rsi+0x768]                           
67d1623  mov rdx,r14                                   
67d1626  mov r8,rbx                                    
67d1629  call 0x6760710                                ; -> sub_6760710
67d162e  nop                                           
```
If [rdi+0x48]==1 jumps to 0x67d1677, else to 0x67d16e5. Otherwise (from [rbx+0x88]==1): rcx=global [0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, calls qword [0xF99FFA0] (=sub_eea6040); [rbp+0x7F]=al; r14=[rsi+0x770]; if r14==[rsi+0x778] calls 0x6760710(&rsi+0x768, r14, rbx); else: [r14]=[rbx], calls 0xe869ff0(&r14+8, &rbx+8), [r14+0x80]=[rbx+0x80], [rbx+0x80]=0, [rsi+0x770]+=0x88.

### Phase 4 (0x67d162f..0x67d1677)
```
67d162f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1636  mov rax,[rcx]                                 
67d1639  mov rax,[rax+0x10]                            
67d163d  movzx edx,byte ptr [rbp+0x7F]                 
67d1641  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1647  nop                                           
67d1648  or r12,0x2000                                 
67d164f  mov [rbp-0x50],r12                            
67d1653  mov eax,[rsi+0x770]                           
67d1659  sub eax,[rsi+0x768]                           
67d165f  shr eax,3                                     
67d1662  imul eax,0xFFFFF0F1                           
67d1668  dec eax                                       
67d166a  mov [rbp-0x26],ax                             
67d166e  mov r14b,1                                    
67d1671  cmp byte ptr [rdi+0x48],1                     
67d1675  jne short 0x67D16E5                           ; -> loc_67d16e5
67d1677  lea rbx,[rsi+0x648]                           
```
Calls qword [0xF99FFA0] with dl=[rbp+0x7F] (cookie); or r12,0x2000; [rbp-0x50]=r12; eax=([rsi+0x770]-[rsi+0x768])>>3, imul 0xFFFFF0F1, dec → [rbp-0x26]; r14b=1; if [rdi+0x48]!=1 jumps to 0x67d16e5; else rbx=[rsi+0x648].

### Phase 5 (0x67d1677..0x67d16e2)
```
67d1677  lea rbx,[rsi+0x648]                           
67d167e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1685  mov rax,[rcx]                                 
67d1688  mov rax,[rax+0x10]                            
67d168c  mov dl,0x4A                                   
67d168e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1694  mov [rbp+0x7F],al                             
67d1697  mov rcx,rbx                                   
67d169a  mov rdx,rdi                                   
67d169d  call 0x675FB30                                ; -> sub_675fb30
67d16a2  nop                                           
67d16a3  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
67d16aa  mov rax,[rcx]                                 
67d16ad  mov rax,[rax+0x10]                            
67d16b1  movzx edx,byte ptr [rbp+0x7F]                 
67d16b5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d16bb  nop                                           
67d16bc  or r12,0x2000000                              
67d16c3  mov [rbp-0x50],r12                            
67d16c7  mov eax,[rsi+0x650]                           
67d16cd  sub eax,[rsi+0x648]                           
67d16d3  shr eax,3                                     
67d16d6  imul eax,0xFFFF8E39                           
67d16dc  dec eax                                       
67d16de  mov [rbp-0xE],ax                              
67d16e2  mov r14b,1                                    
```
Calls qword [0xF99FFA0] (cookie); rcx=rbx, rdx=rdi, calls 0x675fb30; calls qword [0xF99FFA0] again (cookie); or r12,0x2000000; [rbp-0x50]=r12; eax=([rsi+0x650]-[rsi+0x648])>>3, imul 0xFFFF8E39, dec → [rbp-0xE]; r14b=1.

---

## Callee 0x67d14e0 — remaining instructions after 0x67d16e2

### Phase 6 (0x67d16e5..0x67d178b)
```
67d16e5  mov rdi,[rbp+0xF0]                            
67d16ec  cmp byte ptr [rdi+0x58],1                     
67d16f0  jne 0x67D17CE                                 ; -> loc_67d17ce
67d16f6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d16fd  mov rax,[rcx]                                 
67d1700  mov rax,[rax+0x10]                            
67d1704  mov dl,0x4A                                   
67d1706  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d170c  mov [rbp+0x7F],al                             
67d170f  mov rdx,[rsi+0x758]                           
67d1716  cmp rdx,[rsi+0x760]                           
67d171d  je short 0x67D177C                            ; -> loc_67d177c
67d171f  mov eax,[rdi+0x10]                            
67d1722  mov [rdx+0x10],eax                            
67d1725  movups xmm0,[rdi]                             
67d1728  movups [rdx],xmm0                             
67d172b  movzx eax,byte ptr [rdi+0x14]                 
67d172f  mov [rdx+0x14],al                             
67d1732  movss xmm0,[rdi+0x18]                         
67d1737  movss [rdx+0x18],xmm0                         
67d173c  movss xmm0,[rdi+0x1C]                         
67d1741  movss [rdx+0x1C],xmm0                         
67d1746  movss xmm0,[rdi+0x20]                         
67d174b  movss [rdx+0x20],xmm0                         
67d1750  movss xmm0,[rdi+0x24]                         
67d1755  movss [rdx+0x24],xmm0                         
67d175a  movups xmm0,[rdi+0x28]                        
67d175e  movups xmm1,[rdi+0x38]                        
67d1762  movups xmm2,[rdi+0x47]                        
67d1766  movups [rdx+0x28],xmm0                        
67d176a  movups [rdx+0x38],xmm1                        
67d176e  movups [rdx+0x47],xmm2                        
67d1772  add qword ptr [rsi+0x758],0x58                
67d177a  jmp short 0x67D178C                           ; -> loc_67d178c
67d177c  lea rcx,[rsi+0x750]                           
67d1783  mov r8,rdi                                    
67d1786  call 0x6760A80                                ; -> sub_6760a80
67d178b  nop                                           
```
If byte [rdi+0x58]==1 (rdi=[rbp+0xF0]): cookie call via [0xF99FFA0]; if slot cursor [rsi+0x758]!=end [rsi+0x760]: copies dword [rdi+0x10], xmm [rdi], byte [rdi+0x14], float [rdi+0x18/0x1C/0x20/0x24], xmm [rdi+0x28/0x38/0x47] into slot at [rdx], bumps [rsi+0x758] by 0x58; else fallback calls 0x6760a80(&rsi+0x750, rdi). Falls through to cookie call + slot-count computation.

### Phase 7 (0x67d178c..0x67d17cb)
```
67d178c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1793  mov rax,[rcx]                                 
67d1796  mov rax,[rax+0x10]                            
67d179a  movzx edx,byte ptr [rbp+0x7F]                 
67d179e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d17a4  nop                                           
67d17a5  or r12,0x4000                                 
67d17ac  mov [rbp-0x50],r12                            
67d17b0  mov eax,[rsi+0x758]                           
67d17b6  sub eax,[rsi+0x750]                           
67d17bc  shr eax,3                                     
67d17bf  imul eax,0xFFFF8BA3                           
67d17c5  dec eax                                       
67d17c7  mov [rbp-0x24],ax                             
67d17cb  mov r14b,1                                    
```
Cookie call via [0xF99FFA0] with dl=[rbp+0x7F]; or r12,0x4000; [rbp-0x50]=r12; eax=([rsi+0x758]-[rsi+0x750])>>3, imul 0xFFFF8BA3, dec → [rbp-0x24] (slot count for the +0x750 region); r14b=1.

### Phase 8 (0x67d17ce..0x67d183d)
```
67d17ce  mov rdi,[rbp+0xF8]                            
67d17d5  cmp byte ptr [rdi+0xC],1                      
67d17d9  jne 0x67D1880                                 ; -> loc_67d1880
67d17df  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d17e6  mov rax,[rcx]                                 
67d17e9  mov rax,[rax+0x10]                            
67d17ed  mov dl,0x4A                                   
67d17ef  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d17f5  mov [rbp+0x7F],al                             
67d17f8  mov rdx,[rsi+0x680]                           
67d17ff  cmp rdx,[rsi+0x688]                           
67d1806  je short 0x67D182E                            ; -> loc_67d182e
67d1808  movss xmm0,[rdi]                              
67d180c  movss [rdx],xmm0                              
67d1810  movss xmm0,[rdi+4]                            
67d1815  movss [rdx+4],xmm0                            
67d181a  movss xmm0,[rdi+8]                            
67d181f  movss [rdx+8],xmm0                            
67d1824  add qword ptr [rsi+0x680],0xC                 
67d182c  jmp short 0x67D183E                           ; -> loc_67d183e
67d182e  lea rcx,[rsi+0x678]                           
67d1835  mov r8,rdi                                    
67d1838  call 0x1770A70                                ; -> sub_1770a70
67d183d  nop                                           
```
If byte [rdi+0xC]==1 (rdi=[rbp+0xF8]): cookie call; if slot cursor [rsi+0x680]!=end [rsi+0x688]: copies 3 floats ([rdi],[rdi+4],[rdi+8]) into slot at [rdx], bumps [rsi+0x680] by 0xC; else fallback calls 0x1770a70(&rsi+0x678, rdi). Falls through to cookie call + slot-count computation.

### Phase 10 (0x67d1880..0x67d190f)
```
67d1880  mov rdi,[rbp+0x100]                           
67d1887  cmp byte ptr [rdi+2],1                        
67d188b  jne 0x67D1912                                 ; -> loc_67d1912
67d1891  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
67d1898  mov rax,[rcx]                                 
67d189b  mov rax,[rax+0x10]                            
67d189f  mov dl,0x4A                                   
67d18a1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d18a7  mov [rbp+0x7F],al                             
67d18aa  mov rdx,[rsi+0x8A8]                           
67d18b1  cmp rdx,[rsi+0x8B0]                           
67d18b8  je short 0x67D18CA                            ; -> loc_67d18ca
67d18ba  movzx eax,word ptr [rdi]                      
67d18bd  mov [rdx],ax                                  
67d18c0  add qword ptr [rsi+0x8A8],2                   
67d18c8  jmp short 0x67D18DA                           ; -> loc_67d18da
67d18ca  lea rcx,[rsi+0x8A0]                           
67d18d1  mov r8,rdi                                    
67d18d4  call 0x1EF6F90                                ; -> sub_1ef6f90
67d18d9  nop                                           
67d18da  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d18e1  mov rax,[rcx]                                 
67d18e4  mov rax,[rax+0x10]                            
67d18e8  movzx edx,byte ptr [rbp+0x7F]                 
67d18ec  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d18f2  nop                                           
67d18f3  or r12,1                                      
67d18f7  mov [rbp-0x50],r12                            
67d18fb  mov eax,[rsi+0x8A8]                           
67d1901  sub eax,[rsi+0x8A0]                           
67d1907  shr eax,1                                     
67d1909  dec eax                                       
67d190b  mov [rbp-0x40],ax                             
67d190f  mov r14b,1                                    
```
If byte [rdi+2]==1 (rdi=[rbp+0x100]): cookie call; if slot cursor [rsi+0x8A8]!=end [rsi+0x8B0]: copies word [rdi] into slot at [rdx], bumps [rsi+0x8A8] by 2; else fallback calls 0x1ef6f90(&rsi+0x8A0, rdi). Then cookie call; or r12,1; [rbp-0x50]=r12; eax=([rsi+0x8A8]-[rsi+0x8A0])>>1, dec → [rbp-0x40] (slot count for +0x8A0 region); r14b=1.

### Phase 11 (0x67d1912..0x67d19d6)
```
67d1912  mov rdi,[rbp+0x110]                           
67d1919  mov rdx,[rbp+0x108]                           
67d1920  cmp byte ptr [rdx+0x2C],1                     
67d1924  jne short 0x67D195B                           ; -> loc_67d195b
67d1926  lea rcx,[rsi+0x660]                           
67d192d  call 0x6762270                                ; -> sub_6762270
67d1932  or r12,0x1000000                              
67d1939  mov [rbp-0x50],r12                            
67d193d  mov eax,[rsi+0x668]                           
67d1943  sub eax,[rsi+0x660]                           
67d1949  shr eax,2                                     
67d194c  imul eax,0xFFFF8BA3                           
67d1952  dec eax                                       
67d1954  mov [rbp-0x10],ax                             
67d1958  mov r14b,1                                    
67d195b  cmp byte ptr [rdi+1],1                        
67d195f  jne short 0x67D19D9                           ; -> loc_67d19d9
67d1961  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1968  mov rax,[rcx]                                 
67d196b  mov rax,[rax+0x10]                            
67d196f  mov dl,0x4A                                   
67d1971  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1977  mov [rbp+0x7F],al                             
67d197a  mov rdx,[rsi+0x860]                           
67d1981  cmp rdx,[rsi+0x868]                           
67d1988  je short 0x67D1996                            ; -> loc_67d1996
67d198a  inc rdx                                       
67d198d  mov [rsi+0x860],rdx                           
67d1994  jmp short 0x67D19A3                           ; -> loc_67d19a3
67d1996  lea rcx,[rsi+0x858]                           
67d199d  call 0x6760E60                                ; -> sub_6760e60
67d19a2  nop                                           
67d19a3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d19aa  mov rax,[rcx]                                 
67d19ad  mov rax,[rax+0x10]                            
67d19b1  movzx edx,byte ptr [rbp+0x7F]                 
67d19b5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d19bb  nop                                           
67d19bc  or r12,8                                      
67d19c0  mov [rbp-0x50],r12                            
67d19c4  mov eax,[rsi+0x858]                           
67d19ca  not eax                                       
67d19cc  add eax,[rsi+0x860]                           
67d19d2  mov [rbp-0x3A],ax                             
67d19d6  mov r14b,1                                    
```
If byte [rdx+0x2C]==1 (rdx=[rbp+0x108]): calls 0x6762270(&rsi+0x660); or r12,0x1000000; [rbp-0x50]=r12; eax=([rsi+0x668]-[rsi+0x660])>>2, imul 0xFFFF8BA3, dec → [rbp-0x10]; r14b=1. Then if byte [rdi+1]==1 (rdi=[rbp+0x110]): cookie call; if cursor [rsi+0x860]!=end [rsi+0x868]: increments cursor; else calls 0x6760e60(&rsi+0x858). Then cookie call; or r12,8; eax=(~[rsi+0x858])+[rsi+0x860] → [rbp-0x3A]; r14b=1.

### Phase 12 (0x67d19d9..0x67d1b65)
```
67d19d9  mov rax,[rbp+0x118]                           
67d19e0  cmp byte ptr [rax+1],1                        
67d19e4  jne short 0x67D1A5E                           ; -> loc_67d1a5e
67d19e6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d19ed  mov rax,[rcx]                                 
67d19f0  mov rax,[rax+0x10]                            
67d19f4  mov dl,0x4A                                   
67d19f6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d19fc  mov [rbp+0x7F],al                             
67d19ff  mov rdx,[rsi+0x830]                           
67d1a06  cmp rdx,[rsi+0x838]                           
67d1a0d  je short 0x67D1A1B                            ; -> loc_67d1a1b
67d1a0f  inc rdx                                       
67d1a12  mov [rsi+0x830],rdx                           
67d1a19  jmp short 0x67D1A28                           ; -> loc_67d1a28
67d1a1b  lea rcx,[rsi+0x828]                           
67d1a22  call 0x6760E60                                ; -> sub_6760e60
67d1a27  nop                                           
67d1a28  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1a2f  mov rax,[rcx]                                 
67d1a32  mov rax,[rax+0x10]                            
67d1a36  movzx edx,byte ptr [rbp+0x7F]                 
67d1a3a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1a40  nop                                           
67d1a41  or r12,0x20                                   
67d1a45  mov [rbp-0x50],r12                            
67d1a49  mov eax,[rsi+0x828]                           
67d1a4f  not eax                                       
67d1a51  add eax,[rsi+0x830]                           
67d1a57  mov [rbp-0x36],ax                             
67d1a5b  mov r14b,1                                    
67d1a5e  mov rax,[rbp+0x120]                           
67d1a65  cmp byte ptr [rax+1],1                        
67d1a69  jne short 0x67D1AE3                           ; -> loc_67d1ae3
67d1a6b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1a72  mov rax,[rcx]                                 
67d1a75  mov rax,[rax+0x10]                            
67d1a79  mov dl,0x4A                                   
67d1a7b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1a81  mov [rbp+0x7F],al                             
67d1a84  mov rdx,[rsi+0x818]                           
67d1a8b  cmp rdx,[rsi+0x820]                           
67d1a92  je short 0x67D1AA0                            ; -> loc_67d1aa0
67d1a94  inc rdx                                       
67d1a97  mov [rsi+0x818],rdx                           
67d1a9e  jmp short 0x67D1AAD                           ; -> loc_67d1aad
67d1aa0  lea rcx,[rsi+0x810]                           
67d1aa7  call 0x6760E60                                ; -> sub_6760e60
67d1aac  nop                                           
67d1aad  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1ab4  mov rax,[rcx]                                 
67d1ab7  mov rax,[rax+0x10]                            
67d1abb  movzx edx,byte ptr [rbp+0x7F]                 
67d1abf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1ac5  nop                                           
67d1ac6  or r12,0x40                                   
67d1aca  mov [rbp-0x50],r12                            
67d1ace  mov eax,[rsi+0x810]                           
67d1ad4  not eax                                       
67d1ad6  add eax,[rsi+0x818]                           
67d1adc  mov [rbp-0x34],ax                             
67d1ae0  mov r14b,1                                    
67d1ae3  mov rax,[rbp+0x128]                           
67d1aea  cmp byte ptr [rax+1],1                        
67d1aee  jne short 0x67D1B68                           ; -> loc_67d1b68
67d1af0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1af7  mov rax,[rcx]                                 
67d1afa  mov rax,[rax+0x10]                            
67d1afe  mov dl,0x4A                                   
67d1b00  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1b06  mov [rbp+0x7F],al                             
67d1b09  mov rdx,[rsi+0x890]                           
67d1b10  cmp rdx,[rsi+0x898]                           
67d1b17  je short 0x67D1B25                            ; -> loc_67d1b25
67d1b19  inc rdx                                       
67d1b1c  mov [rsi+0x890],rdx                           
67d1b23  jmp short 0x67D1B32                           ; -> loc_67d1b32
67d1b25  lea rcx,[rsi+0x888]                           
67d1b2c  call 0x6760E60                                ; -> sub_6760e60
67d1b31  nop                                           
67d1b32  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1b39  mov rax,[rcx]                                 
67d1b3c  mov rax,[rax+0x10]                            
67d1b40  movzx edx,byte ptr [rbp+0x7F]                 
67d1b44  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1b4a  nop                                           
67d1b4b  or r12,2                                      
67d1b4f  mov [rbp-0x50],r12                            
67d1b53  mov eax,[rsi+0x888]                           
67d1b59  not eax                                       
67d1b5b  add eax,[rsi+0x890]                           
67d1b61  mov [rbp-0x3E],ax                             
67d1b65  mov r14b,1                                    
```
Three repeated counter-region patterns for [rbp+0x118], [rbp+0x120], [rbp+0x128]: each checks byte [rax+1]==1; if so cookie call, then if cursor!=end increment cursor else call 0x6760e60(&base), then cookie call, or r12 (flags 0x20 / 0x40 / 2), [rbp-0x50]=r12, eax=(~base)+cursor → [rbp-0x36/-0x34/-0x3E], r14b=1.

### Phase 13 (0x67d1b68..0x67d1d24)
```
67d1b68  mov rax,[rbp+0x130]                           
67d1b6f  cmp byte ptr [rax+1],1                        
67d1b73  jne short 0x67D1BAC                           ; -> loc_67d1bac
67d1b75  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
67d1b7c  mov rax,[rcx]                                 
67d1b7f  mov rax,[rax+0x10]                            
67d1b83  mov dl,0x4A                                   
67d1b85  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1b8b  mov edx,eax                                   
67d1b8d  mov rbx,[rsi+0x188]                           
67d1b94  cmp rbx,[rsi+0x190]                           
67d1b9b  je short 0x67D1BB4                            ; -> loc_67d1bb4
67d1b9d  inc rbx                                       
67d1ba0  mov [rsi+0x188],rbx                           
67d1ba7  jmp 0x67D1D2F                                 ; -> loc_67d1d2f
67d1bac  xor r15d,r15d                                 
67d1baf  jmp 0x67D1D67                                 ; -> loc_67d1d67
67d1bb4  mov r15,rbx                                   
67d1bb7  sub r15,[rsi+0x180]                           
67d1bbe  mov rax,0x7FFFFFFFFFFFFFFF                    
67d1bc8  cmp r15,rax                                   
67d1bcb  mov [rbp+0x7F],dl                             
67d1bce  je 0x67D254A                                  ; -> loc_67d254a
67d1bd4  lea r13,[r15+1]                               
67d1bd8  mov rdi,r15                                   
67d1bdb  shr rdi,1                                     
67d1bde  mov rcx,rdi                                   
67d1be1  xor rcx,rax                                   
67d1be4  add rdi,r15                                   
67d1be7  cmp rdi,r13                                   
67d1bea  cmovbe rdi,r13                                
67d1bee  cmp r15,rcx                                   
67d1bf1  cmova rdi,rax                                 
67d1bf5  test rdi,rdi                                  
67d1bf8  je 0x67D1CAF                                  ; -> loc_67d1caf
67d1bfe  cmp rdi,0x1000                                
67d1c05  jb short 0x67D1C50                            ; -> loc_67d1c50
67d1c07  cmp rdi,0xFFFFFFFFFFFFFFD9                    
67d1c0b  jae 0x67D2570                                 ; -> loc_67d2570
67d1c11  lea rdx,[rdi+0x27]                            
67d1c15  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
67d1c1c  mov rax,[rcx]                                 
67d1c1f  mov rax,[rax+8]                               
67d1c23  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1c29  nop                                           
67d1c2a  mov r14,rax                                   
67d1c2d  test rax,rax                                  
67d1c30  je 0x67D1F37                                  ; -> loc_67d1f37
67d1c36  mov rax,r14                                   
67d1c39  add r14,0x27                                  
67d1c3d  and r14,0xFFFFFFFFFFFFFFE0                    
67d1c41  mov [r14-8],rax                               
67d1c45  cmp rbx,[rsi+0x188]                           
67d1c4c  jne short 0x67D1C79                           ; -> loc_67d1c79
67d1c4e  jmp short 0x67D1CBB                           ; -> loc_67d1cbb
67d1c50  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
67d1c57  mov rax,[rcx]                                 
67d1c5a  mov rax,[rax+8]                               
67d1c5e  mov rdx,rdi                                   
67d1c61  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
67d1c67  nop                                           
67d1c68  mov r14,rax                                   
67d1c6b  test rax,rax                                  
67d1c6e  je short 0x67D1CA6                            ; -> loc_67d1ca6
67d1c70  cmp rbx,[rsi+0x188]                           
67d1c77  je short 0x67D1CBB                            ; -> loc_67d1cbb
67d1c79  add r15,r14                                   
67d1c7c  inc r15                                       
67d1c7f  mov rdx,[rsi+0x180]                           
67d1c86  mov r8,rbx                                    
67d1c89  sub r8,rdx                                    
67d1c8c  mov rcx,r14                                   
67d1c8f  call 0xEEC6DE0                                ; -> sub_eec6de0
67d1c94  mov r8,[rsi+0x188]                            
67d1c9b  sub r8,rbx                                    
67d1c9e  mov rcx,r15                                   
67d1ca1  mov rdx,rbx                                   
67d1ca4  jmp short 0x67D1CCB                           ; -> loc_67d1ccb
67d1ca6  mov rcx,rdi                                   
67d1ca9  call 0x9BC830                                 ; -> sub_9bc830
67d1cae  nop                                           
67d1caf  xor r14d,r14d                                 
67d1cb2  cmp rbx,[rsi+0x188]                           
67d1cb9  jne short 0x67D1C79                           ; -> loc_67d1c79
67d1cbb  mov rdx,[rsi+0x180]                           
67d1cc2  sub rbx,rdx                                   
67d1cc5  mov rcx,r14                                   
67d1cc8  mov r8,rbx                                    
67d1ccb  call 0xEEC6DE0                                ; -> sub_eec6de0
67d1cd0  mov rcx,[rsi+0x180]                           
67d1cd7  test rcx,rcx                                  
67d1cda  je short 0x67D1D10                            ; -> loc_67d1d10
67d1cdc  mov rdx,[rsi+0x190]                           
67d1ce3  sub rdx,rcx                                   
67d1ce6  cmp rdx,0x1000                                
67d1ced  jb short 0x67D1D0B                            ; -> loc_67d1d0b
67d1cef  mov rax,[rcx-8]                               
67d1cf3  add rcx,0xFFFFFFFFFFFFFFF8                    
67d1cf7  sub rcx,rax                                   
67d1cfa  cmp rcx,0x20                                  
67d1cfe  jae 0x67D2556                                 ; -> loc_67d2556
67d1d04  add rdx,0x27                                  
67d1d08  mov rcx,rax                                   
67d1d0b  call 0xE935700                                ; -> sub_e935700
67d1d10  mov [rsi+0x180],r14                           
67d1d17  add r13,r14                                   
67d1d1a  mov [rsi+0x188],r13                           
67d1d21  add rdi,r14                                   
67d1d24  mov [rsi+0x190],rdi                           
```
If byte [rax+1]==1 (rax=[rbp+0x130]): cookie call (dl=cookie saved); rbx=[rsi+0x188] (cursor); if rbx==end [rsi+0x190] goto grow-path (0x67d1bb4), else increment cursor and jump to 0x67d1d2f (finalize). If not taken: r15d=0, jump to 0x67d1d67. Grow path: r15=cursor-begin([rsi+0x180]); compute new size (clamp, min 0x1000, max 0xFFFFFFFFFFFFFFD9); alloc via [0xF99FFA0] or sub_9bc830 on failure; if alloc fails and cursor==begin set r14=0 else memcpy old→new via 0xEEC6DE0; then second 0xEEC6DE0 (zero/move tail); validate remaining space; call 0xE935700 on corruption; finalize: [rsi+0x180]=r14(new begin), [rsi+0x188]=r13(new cursor), [rsi+0x190]=rdi(new end).

---

## Callee 0x67d14e0 — remaining after 0x67d1d24 (SUPERSEDED — see the section above)
Continues at 0x67d1d2b and proceeds through counter regions for [rbp+0x138], [rbp+0x140], [rbp+0x148], [rbp+0x150], [rbp+0x158], [rbp+0x168]/[rbp+0x160], [rbp+0x170], [rbp+0x178], [rbp+0x188]/[rbp+0x180], ending at `ret` 0x67d253a. The full decode (Phases A–M) is in the section above. The Phases 1..4 below are actually the **0x673cc80** geometry-packet builder (mislabelled in the earlier pass); retained here for completeness.

### Phase 1 (0x673cc80..0x673ccd9)
```
673cc80  push r14                                      
673cc82  push rsi                                      
673cc83  push rdi                                      
673cc84  push rbp                                      
673cc85  push rbx                                      
673cc86  sub rsp,0x20                                  
673cc8a  mov rsi,rcx                                   
673cc8d  movzx ecx,word ptr [rsp+0x78]                 
673cc92  mov rax,[rsp+0x70]                            
673cc97  xorps xmm0,xmm0                               
673cc9a  movups [rsi],xmm0                             ; W a0+0x0
673cc9d  mov r10,[rdx+8]                               ; R a1+0x8
673cca1  test r10,r10                                  
673cca4  je short 0x673CCAB                            ; -> loc_673ccab
673cca6  lock inc dword ptr [r10+8]                    ; W *(a1+0x8)+0x8
673ccab  mov rbx,[rsp+0x80]                            
673ccb3  mov r10,[rdx]                                 ; R a1+0x0
673ccb6  mov [rsi],r10                                 ; W a0+0x0
673ccb9  mov rdx,[rdx+8]                               ; R a1+0x8
673ccbd  mov [rsi+8],rdx                               ; W a0+0x8
673ccc1  mov [rsi+0x10],r8b                            ; W a0+0x10
673ccc5  mov [rsi+0x18],r9                             ; W a0+0x18
673ccc9  mov [rsi+0x20],cx                             ; W a0+0x20
673cccd  movups [rsi+0x28],xmm0                        ; W a0+0x28
673ccd1  movups [rsi+0x38],xmm0                        ; W a0+0x38
673ccd5  movups [rsi+0x48],xmm0                        ; W a0+0x48
```
Prologue: push r14,rsi,rdi,rbp,rbx; sub rsp,0x20; rsi=rcx (out); ecx=word [rsp+0x78]; rax=[rsp+0x70]; zeroes xmm0; [rsi]=0; r10=[rdx+8], if non-null lock-inc refcount; rbx=[rsp+0x80]; r10=[rdx]; [rsi]=r10, [rsi+8]=[rdx+8], [rsi+0x10]=r8b, [rsi+0x18]=r9, [rsi+0x20]=cx; zeroes xmm [rsi+0x28],[rsi+0x38],[rsi+0x48].

### Phase 2 (0x673ccd9..0x673cd32)
```
673ccd9  mov rcx,[rax+8]                               
673ccdd  test rcx,rcx                                  
673cce0  je short 0x673CD23                            ; -> loc_673cd23
673cce2  lock inc dword ptr [rcx+8]                    
673cce6  mov rdi,[rsi+0x30]                            ; R a0+0x30
673ccea  movups xmm0,[rax]                             
673cced  movups [rsi+0x28],xmm0                        ; W a0+0x28
673ccf1  test rdi,rdi                                  
673ccf4  je short 0x673CD32                            ; -> loc_673cd32
673ccf6  lock dec dword ptr [rdi+8]                    ; W *(a0+0x30)+0x8
673ccfa  jne short 0x673CD32                           ; -> loc_673cd32
673ccfc  mov rax,[rdi]                                 ; R *(a0+0x30)+0x0
673ccff  mov rax,[rax]                                 ; R *(*(a0+0x30)+0x0)+0x0
673cd02  mov rcx,rdi                                   
673cd05  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
673cd0b  lock dec dword ptr [rdi+0xC]                  ; W *(a0+0x30)+0xC
673cd0f  jne short 0x673CD32                           ; -> loc_673cd32
673cd11  mov rax,[rdi]                                 ; R *(a0+0x30)+0x0
673cd14  mov rax,[rax+8]                               ; R *(*(a0+0x30)+0x0)+0x8
673cd18  mov rcx,rdi                                   
673cd1b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
673cd21  jmp short 0x673CD32                           ; -> loc_673cd32
673cd23  mov rax,[rax]                                 
673cd26  mov [rsi+0x28],rax                            
673cd2a  mov qword ptr [rsi+0x30],0                    
```
rcx=[rax+8]; if non-null lock-inc refcount; rdi=[rsi+0x30]; xmm0=[rax], [rsi+0x28]=xmm0; if rdi non-null: lock-dec [rdi+8]; if zero: release shared_ptr (dtor + dealloc via [0xF99FFA0]); else (rcx null): [rax]→[rsi+0x28], [rsi+0x30]=0.

### Phase 3 (0x673cd32..0x673cd8e)
```
673cd32  mov rax,[rbx+8]                               
673cd36  test rax,rax                                  
673cd39  je short 0x673CD45                            ; -> loc_673cd45
673cd3b  lock inc dword ptr [rax+8]                    
673cd3f  mov rax,[rbx+8]                               
673cd43  jmp short 0x673CD47                           ; -> loc_673cd47
673cd45  xor eax,eax                                   
673cd47  mov r14,[rsp+0x88]                            
673cd4f  mov rcx,[rbx]                                 
673cd52  mov [rsi+0x38],rcx                            
673cd56  mov rdi,[rsi+0x40]                            
673cd5a  mov [rsi+0x40],rax                            
673cd5e  test rdi,rdi                                  
673cd61  je short 0x673CD8E                            ; -> loc_673cd8e
673cd63  lock dec dword ptr [rdi+8]                    
673cd67  jne short 0x673CD8E                           ; -> loc_673cd8e
673cd69  mov rax,[rdi]                                 
673cd6c  mov rax,[rax]                                 
673cd6f  mov rcx,rdi                                   
673cd72  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
673cd78  lock dec dword ptr [rdi+0xC]                  
673cd7c  jne short 0x673CD8E                           ; -> loc_673cd8e
673cd7e  mov rax,[rdi]                                 
673cd81  mov rax,[rax+8]                               
673cd85  mov rcx,rdi                                   
673cd88  call qword ptr [0xF99FFA0]                    ; [data_f99FFA0] = sub_eea6040
```
rax=[rbx+8], lock-inc if non-null else eax=0; r14=[rsp+0x88]; rcx=[rbx], [rsi+0x38]=rcx; rdi=[rsi+0x40], [rsi+0x40]=rax; if rdi non-null: lock-dec [rdi+8]; if zero: release shared_ptr.

### Phase 4 (0x673cd8e..0x673cdfd)
```
673cd8e  mov rax,[r14+8]                               
673cd92  test rax,rax                                  
673cd95  je short 0x673CDA1                            ; -> loc_673cda1
673cd97  lock inc dword ptr [rax+8]                    
673cd9b  mov rax,[r14+8]                               
673cd9f  jmp short 0x673CDA3                           ; -> loc_673cda3
673cda1  xor eax,eax                                   
673cda3  mov ebx,[rsp+0x98]                            
673cdaa  mov ebp,[rsp+0x90]                            
673cdb1  mov rcx,[r14]                                 
673cdb4  mov [rsi+0x48],rcx                            
673cdb8  mov rdi,[rsi+0x50]                            
673cdbc  mov [rsi+0x50],rax                            
673cdc0  test rdi,rdi                                  
673cdc3  je short 0x673CDF0                            ; -> loc_673cdf0
673cdc5  lock dec dword ptr [rdi+8]                    
673cdc9  jne short 0x673CDF0                           ; -> loc_673cdf0
673cdcb  mov rax,[rdi]                                 
673cdce  mov rax,[rax]                                 
673cdd1  mov rcx,rdi                                   
673cdd4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
673cdda  lock dec dword ptr [rdi+0xC]                  
673cdde  jne short 0x673CDF0                           ; -> loc_673cdf0
673cde0  mov rax,[rdi]                                 
673cde3  mov rax,[rax+8]                               
673cde7  mov rcx,rdi                                   
673cdea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
673cdf0  mov [rsi+0x58],ebp                            
673cdf3  mov [rsi+0x5C],ebx                            
673cdf6  mov rax,rsi                                   
673cdf9  add rsp,0x20                                  
673cdfd  pop rbx                                       
673cdfe  pop rbp                                       
673cdff  pop rdi                                       
673ce00  pop rsi                                       
673ce01  pop r14                                       
673ce03  ret                                           
```
rax=[r14+8], lock-inc if non-null else eax=0; ebx=[rsp+0x98], ebp=[rsp+0x90]; rcx=[r14], [rsi+0x48]=rcx; rdi=[rsi+0x50], [rsi+0x50]=rax; if rdi non-null: lock-dec [rdi+8]; if zero: release shared_ptr; [rsi+0x58]=ebp, [rsi+0x5C]=ebx; rax=rsi; epilogue; ret.

---

## Callee summary

| Callee | RVA | Role (inferred from disassembly) | First-120 status |
|---|---|---|---|
| `sub_67d14e0` | 0x67d14e0 | Draw-list submit: builds per-draw record via 0x5aba5c0, manages ring-buffer slots at [rsi+0x768/0x770] and [rsi+0x648/0x650] with cookie calls to sub_eea6040 via [0xF99FFA0] | COMPLETE — read 0x67d14e0..ret 0x67d253a (Phases 1–5 + Phases A–M) |
| `sub_673cc80` | 0x673cc80 | Geometry-packet builder: copies {ptr,refcount,kind,shared pairs} into out struct [rsi], releases old shared_ptr refs at +0x30/+0x40/+0x50 | 120 instr read through 0x673ce03 (ret) |

## Verification notes
- All disassembly lines quoted exactly from `rdis dis` output for exe `Minecraft.Windows.exe` 1.26.62.01.
- Range 0x669c35f..0x669c8f9 is instruction-complete: every instruction belongs to a phase.
- Range 0x669be56..0x669bef8 is instruction-complete.
- Callee 0x673cc80: complete function read (ret at 0x673ce03), within first 120 instructions.
- Callee 0x67d14e0: complete function read from 0x67d14e0 through ret 0x67d253a (phases A–M cover 0x67d1d2b..0x67d253a; Phases 1–5 cover 0x67d14e0..0x67d16e2). No gap at 0x67d1d24..0x67d1d2b: `mov [rsi+0x190],rdi` is 7 bytes ending exactly at 0x67d1d2b.
- Range 0x669c8f9..0x669c9e2 documented (call setup + call 0x67d14e0 + teardown start). Post-call epilogue (0x669c9e2..ret 0x669ca18) lies outside this range and is not part of this unit.
- Unit U-IH: DONE. No remaining work.
