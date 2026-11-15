# U-E4-F10: Gap fill for builder 0x67762e0

Source of gaps: docs/progress/gaps_67762e0.txt (real instruction RVAs not quoted in F1..F9 docs).
Method: for each range `lo..hi`, run `rdis.exe "<exe>" dis <lo-0x10> 40`, confirm printed addresses cover the whole range; if rdis prints (bad), restart at next address after it. Append exact real lines covering the gap (`0xRVA  mnemonic operands`) with a // interpretation.

## NEXT (remaining ranges, in order)
None — all 16 ranges from docs/progress/gaps_67762e0.txt are transcribed; unit U-E4-F10 complete.

## Transcribed gaps

### 0x67765a2..0x67765a2 (done)
Ran `rdis dis 0x6776592 40`; addresses 6776592..6776642 printed, gap covered.
[V] at 0x67765a2 (seen in rdis output):
```
0x67765a2  nop                                           
```
// padding nop between call 0x5AB9970 and movaps xmm0 sequence (alignment filler); no operands, no side effects.

### 0x6776ff1..0x6776ff1 (done)
Ran `rdis dis 0x6776fe1 40`; addresses 6776fe1..67770a3 printed, gap covered.
[V] at 0x6776ff1 (seen in rdis output):
```
0x6776ff1  nop                                           
```
// padding nop between call 0x6791F20 and mov eax,[rbx+0x68] / movups store sequence (alignment filler); no operands, no side effects.

### 0x6777a3d..0x6777ab8 (done)
Ran `rdis dis 0x6777a2d 40`; addresses 6777a2d..6777b05 printed, gap covered (all 22 instruction starts in range transcribed).
[V] at 0x6777a3d..0x6777ab8 (seen in rdis output):
```
0x6777a3d  xor edx,edx                                   
0x6777a3f  mov rcx,[rbp+0x2F0]                           
0x6777a46  mov [rbp+0x780],rcx                           
0x6777a4d  mov [rbp+0x788],rdx                           
0x6777a54  mov ecx,[rbp+0x824]                           
0x6777a5a  mov [rbp+0x790],ecx                           
0x6777a60  mov ecx,[rbp+0x820]                           
0x6777a66  mov [rbp+0x794],ecx                           
0x6777a6c  mov ecx,[rbp+0x774]                           
0x6777a72  mov [rbp+0x798],ecx                           
0x6777a78  mov rcx,0x100000000                           
0x6777a82  mov [rbp+0x79C],rcx                           
0x6777a89  mov dword ptr [rbp+0x7A4],1                   
0x6777a93  movaps [rbp+0x7C0],xmm6                       
0x6777a9a  mov rcx,[rsi+0xD0]                            
0x6777aa1  test rcx,rcx                                  
0x6777aa4  je short 0x6777AF5                            ; -> loc_6777af5
0x6777aa6  lock inc dword ptr [rcx+8]                    
0x6777aaa  mov rcx,[rsi+0xD0]                            
0x6777ab1  mov rdx,[rbp+0x788]                           
0x6777ab8  jmp short 0x6777AF7                           ; -> loc_6777af7
```
// fall-through path of a branch (jmp at 6777a3b skips it to loc_6777abc): zeroes edx, snapshots locals [rbp+0x2F0],[rbp+0x824],[rbp+0x820],[rbp+0x774] into [rbp+0x780..0x798], sets [rbp+0x79C]=0x100000000 and [rbp+0x7A4]=1, clears [rbp+0x7C0]; if [rsi+0xD0] != null does lock inc dword ptr [rcx+8] (addref) then jmp loc_6777af7; else xor ecx,ecx at loc_6777af5 then falls to 6777af7.

### 0x6777b1c..0x6777b2e (done)
Ran `rdis dis 0x6777b0c 40`; addresses 6777b0c..6777bcc printed, gap covered (all 4 instruction starts in range transcribed).
[V] at 0x6777b1c..0x6777b2e (seen in rdis output):
```
0x6777b1c  lock inc dword ptr [rdx+8]                    ; W a1+0x8
0x6777b20  mov rdx,[rbp+0x788]                           
0x6777b27  mov rcx,[rbp+0x7C8]                           
0x6777b2e  jmp short 0x6777B88                           ; -> loc_6777b88
```
// addref path continuation: lock inc dword ptr [rdx+8] (refcount++ on object at rdx), reload rdx=[rbp+0x788] and rcx=[rbp+0x7C8], then jmp loc_6777b88 which stores [rbp+0x780]->[rbp+0x7D0], rdx->[rbp+0x7D8], and copies a 16-byte block [rbp+0x790..0x79F] to [rbp+0x7D0+0x10] via movups; clears [rbp+0x4A0] with xmm6; if rcx != null does lock inc dword ptr [rcx+8].

### 0x6777bc6..0x6777bda (done)
Ran `rdis dis 0x6777bb6 64`; addresses 6777bb6..6777cf6 printed, gap covered (all 5 instruction starts in range transcribed).
[V] at 0x6777bc6..0x6777bda (seen in rdis output):
```
0x6777bc6  je short 0x6777C10                            ; -> loc_6777c10
0x6777bc8  lock inc dword ptr [rcx+8]                    ; W a0+0x8
0x6777bcc  mov rcx,[rbp+0x7C8]                           
0x6777bd3  mov rdx,[rbp+0x7D8]                           
0x6777bda  jmp short 0x6777C12                           ; -> loc_6777c12
```
// mirror addref path: if rcx == 0 jump to loc_6777c10 (xor ecx,ecx); else lock inc dword ptr [rcx+8] (refcount++ on object at rcx), reload rcx=[rbp+0x7C8], rdx=[rbp+0x7D8], jmp loc_6777c12 which stores [rbp+0x7C0]->[rbp+0x4A0], rcx->[rbp+0x4A8], clears [rcx+0xC] where rcx=&[rbp+0x4A4], tests rdx, lock inc dword ptr [rdx+8] if nonzero, mov r14=[rbp+0x7D8], jmp loc_6777c4e.

Ran `rdis dis 0x6776fe1 40`; addresses 6776fe1..67770a3 printed, gap covered.
[V] at 0x6776ff1 (seen in rdis output):
```
0x6776ff1  nop                                           
```
// padding nop between call 0x6791F20 and mov eax,[rbx+0x68] / movups store sequence (alignment filler); no operands, no side effects.

### 0x67766c0..0x67766c7 (done)
Ran `rdis dis 0x67766b0 40`; addresses 67766b0..677676b printed, gap covered (both 67766c0 and 67766c7 are instruction starts).
[V] at 0x67766c0 and 0x67766c7 (seen in rdis output):
```
0x67766c0  lea r14,[rbp+0xA0]                            
0x67766c7  lea r13,[rbp+0x300]                           
```
// loop reentry target: reloads r14 = &locals[0xA0] and r13 = &locals[0x300] before falling into loc_67766ce (add rdi,0x58) / loc_67766d2 loop; no side effects beyond register reload.

Ran `rdis dis 0x6776592 40`; addresses 6776592..6776642 printed, gap covered.
[V] at 0x67765a2 (seen in rdis output):
```
0x67765a2  nop                                           
```
// padding nop between call 0x5AB9970 and movaps xmm0 sequence (alignment filler); no operands, no side effects.

### 0x67780a5..0x67782db (done)
Ran `rdis dis 0x6778095 80` + `rdis dis 0x6778229 40`; addresses 6778095..67782ee printed, gap covered (every instruction start in 0x67780a5..0x67782db is present, last gap instr at 0x67782db).
[V] at 0x67780a5..0x67782db (seen in rdis output):
```
0x67780a5  lea rcx,[r14+0x8A0]                           
0x67780ac  lea r8,[rbp+0x708]                            
0x67780b3  call 0x1EF6F90                                 ; -> sub_1ef6f90
0x67780b8  nop                                           
0x67780b9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67780c0  mov rax,[rcx]                                 
0x67780c3  mov rax,[rax+0x10]                            
0x67780c7  movzx edx,byte ptr [rbp+0x838]                
0x67780ce  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67780d4  nop                                           
0x67780d5  mov eax,[r14+0x8A8]                           
0x67780dc  sub eax,[r14+0x8A0]                           
0x67780e3  shr eax,1                                     
0x67780e5  dec eax                                       
0x67780e7  mov [rbp+0x310],ax                            
0x67780ee  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67780f5  mov rax,[rcx]                                 
0x67780f8  mov rax,[rax+0x10]                            
0x67780fc  mov dl,0x4A                                   
0x67780fe  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778104  nop                                           
0x6778105  mov [rbp+0x838],al                            
0x677810b  mov rdx,[r14+0x758]                           
0x6778112  cmp rdx,[r14+0x760]                           
0x6778119  je short 0x6778687                            ; -> loc_6778687
0x677811f  lea rcx,[rbp+0x6B0]                           
0x6778126  mov eax,[rcx+0x10]                            
0x6778129  mov [rdx+0x10],eax                            
0x677812c  movups xmm0,[rcx]                             
0x677812f  movups [rdx],xmm0                             
0x6778132  movzx eax,byte ptr [rbp+0x6C4]                
0x6778139  mov [rdx+0x14],al                             
0x677813c  movss xmm0,[rbp+0x6C8]                        
0x6778144  movss [rdx+0x18],xmm0                         
0x6778149  movss xmm0,[rbp+0x6CC]                        
0x6778151  movss [rdx+0x1C],xmm0                         
0x6778156  movss xmm0,[rbp+0x6D0]                        
0x677815e  movss [rdx+0x20],xmm0                         
0x6778163  movss xmm0,[rbp+0x6D4]                        
0x677816b  movss [rdx+0x24],xmm0                         
0x6778170  lea rax,[rbp+0x574]                           
0x6778177  movups xmm0,[rax+0x164]                       
0x677817e  movups xmm1,[rax+0x174]                       
0x6778185  movups xmm2,[rax+0x183]                       
0x677818c  movups [rdx+0x28],xmm0                        
0x6778190  movups [rdx+0x38],xmm1                        
0x6778194  movups [rdx+0x47],xmm2                        
0x6778198  add qword ptr [r14+0x758],0x58                
0x67781a0  jmp 0x677869B                                 ; -> loc_677869b
0x67781a5  lea rcx,[r14+0x8A0]                           
0x67781ac  lea r8,[rbp+0x710]                            
0x67781b3  call 0x1EF6F90                                 ; -> sub_1ef6f90
0x67781b8  nop                                           
0x67781b9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67781c0  mov rax,[rcx]                                 
0x67781c3  mov rax,[rax+0x10]                            
0x67781c7  movzx edx,byte ptr [rbp+0x838]                
0x67781ce  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67781d4  nop                                           
0x67781d5  mov eax,[r14+0x8A8]                           
0x67781dc  sub eax,[r14+0x8A0]                           
0x67781e3  shr eax,1                                     
0x67781e5  dec eax                                       
0x67781e7  mov [rbp+0x310],ax                            
0x67781ee  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67781f5  mov rax,[rcx]                                 
0x67781f8  mov rax,[rax+0x10]                            
0x67781fc  mov dl,0x4A                                   
0x67781fe  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778204  nop                                           
0x6778205  mov [rbp+0x838],al                            
0x677820b  mov rdx,[r14+0x758]                           
0x6778212  cmp rdx,[r14+0x760]                           
0x6778219  je short 0x6778722                            ; -> loc_6778722
0x677821f  lea rcx,[rbp+0x6B8]                           
0x6778226  mov eax,[rcx+0x10]                            
0x6778229  mov [rdx+0x10],eax                            
0x677822c  movups xmm0,[rcx]                             
0x677822f  movups [rdx],xmm0                             
0x6778232  movzx eax,byte ptr [rbp+0x6CC]                
0x6778239  mov [rdx+0x14],al                             
0x677823c  movss xmm0,[rbp+0x6D0]                        
0x6778244  movss [rdx+0x18],xmm0                         
0x6778249  movss xmm0,[rbp+0x6D4]                        
0x6778251  movss [rdx+0x1C],xmm0                         
0x6778256  movss xmm0,[rbp+0x6D8]                        
0x677825e  movss [rdx+0x20],xmm0                         
0x6778263  movss xmm0,[rbp+0x6DC]                        
0x677826b  movss [rdx+0x24],xmm0                         
0x6778270  lea rax,[rbp+0x6E0]                           
0x6778277  movups xmm0,[rax]                             
0x677827a  movups xmm1,[rax+0x10]                        
0x677827e  movups xmm2,[rax+0x1F]                        
0x6778282  movups [rdx+0x28],xmm0                        
0x6778286  movups [rdx+0x38],xmm1                        
0x677828a  movups [rdx+0x47],xmm2                        
0x677828e  add qword ptr [r14+0x758],0x58                
0x6778296  jmp 0x6778736                                 ; -> loc_6778736
0x677829b  lea rcx,[r14+0x8A0]                           
0x67782a2  lea r8,[rbp+0x710]                            
0x67782a9  call 0x1EF6F90                                 ; -> sub_1ef6f90
0x67782ae  nop                                           
0x67782af  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67782b6  mov rax,[rcx]                                 
0x67782b9  mov rax,[rax+0x10]                            
0x67782bd  movzx edx,byte ptr [rbp+0x838]                
0x67782c4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67782ca  nop                                           
0x67782cb  mov eax,[r14+0x8A8]                           
0x67782d2  sub eax,[r14+0x8A0]                           
0x67782d9  shr eax,1                                     
0x67782db  dec eax                                       
```
// record-copy loop (two full iterations plus the start of a third): each iteration computes ([r14+0x8A8]-[r14+0x8A0])/2-1 -> [rbp+0x310], does two virtual calls through data_f99ffa0 (sub_eea6040) with a byte argument from [rbp+0x838] (mov dl,0x4A before the second), then if slot [r14+0x758] != limit [r14+0x760] copies a ~0x58-byte record into rdx=[r14+0x758]: dword [src+0x10]->[rdx+0x10], 16 bytes [src]->[rdx] via movups, byte [rbp+0x6C4]/[rbp+0x6CC]->[rdx+0x14], floats [rbp+0x6C8..0x6D4]/[rbp+0x6D0..0x6DC]->[rdx+0x18..0x24], three movups from [rbp+0x574+0x164..]/[rbp+0x6E0+0x0..]->[rdx+0x28/0x38/0x47], then [r14+0x758]+=0x58 and jmp to an exit loc (loc_6778687/loc_677869b/loc_6778722/loc_6778736 depending on iteration); two `nop`s per iteration are alignment fillers; no addref/lock instructions in this range.

### 0x67785be..0x67785e7 (done)
Ran `rdis dis 0x67785ae 40`; addresses 67785ae..6778676 printed, gap covered (all instruction starts in 0x67785be..0x67785e7 present).
[V] at 0x67785be..0x67785e7 (seen in rdis output):
```
0x67785be  sub eax,[r13+0x8A0]                           
0x67785c5  shr eax,1                                     
0x67785c7  dec eax                                       
0x67785c9  mov [rbp+0x310],ax                            
0x67785d0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67785d7  mov rax,[rcx]                                 
0x67785da  mov rax,[rax+0x10]                            
0x67785de  mov dl,0x4A                                   
0x67785e0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67785e6  nop                                           
0x67785e7  mov [rbp+0x838],al                            
```
// same record-copy loop prologue as 0x67780a5 (r13 as base register instead of r14): ([r13+0x8A8]-[r13+0x8A0])/2-1 -> [rbp+0x310], then virtual call through data_f99ffa0 (sub_eea6040) with dl=0x4A, result byte -> [rbp+0x838]; nop alignment filler; no addref/lock instructions.

### 0x6778722..0x6778a24 (done)
Ran `rdis dis 0x6778712 40` + `rdis dis 0x67787c4 40` + `rdis dis 0x677885f 40` + `rdis dis 0x6778958 40` + `rdis dis 0x6778a24 10`; addresses 6778712..6778cb6 printed, gap covered (every instruction start in 0x6778722..0x6778a24 present; last gap instr at 0x6778a24).
[V] at 0x6778722..0x6778a24 (seen in rdis output):
```
0x6778722  lea rcx,[r14+0x750]                           
0x6778729  lea r8,[rbp+0x6B8]                            
0x6778730  call 0x6760A80                                 ; -> sub_6760a80
0x6778735  nop                                           
0x6778736  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677873d  mov rax,[rcx]                                 
0x6778740  mov rax,[rax+0x10]                            
0x6778744  movzx edx,byte ptr [rbp+0x838]                
0x677874b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778751  nop                                           
0x6778752  mov qword ptr [rbp+0x300],0x4001              
0x677875d  mov eax,[r14+0x758]                           
0x6778764  sub eax,[r14+0x750]                           
0x677876b  shr eax,3                                     
0x677876e  imul eax,0xFFFF8BA3                           
0x6778774  dec eax                                       
0x6778776  mov [rbp+0x32C],ax                            
0x677877d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778784  mov rax,[rcx]                                 
0x6778787  mov rax,[rax+0x10]                            
0x677878b  mov dl,0x4A                                   
0x677878d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778793  nop                                           
0x6778794  mov [rbp+0x838],al                            
0x677879a  mov rdx,[r14+0x890]                           
0x67787a1  cmp rdx,[r14+0x898]                           
0x67787a8  je short 0x6778AA9                            ; -> loc_6778aa9
0x67787ae  inc rdx                                       
0x67787b1  mov [r14+0x890],rdx                           
0x67787b8  jmp 0x6778AB6                                 ; -> loc_6778ab6
0x67787bd  lea rcx,[r14+0x750]                           
0x67787c4  lea r8,[rbp+0x6B8]                            
0x67787cb  call 0x6760A80                                 ; -> sub_6760a80
0x67787d0  nop                                           
0x67787d1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67787d8  mov rax,[rcx]                                 
0x67787db  mov rax,[rax+0x10]                            
0x67787df  movzx edx,byte ptr [rbp+0x838]                
0x67787e6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67787ec  nop                                           
0x67787ed  mov qword ptr [rbp+0x300],0x4001              
0x67787f8  mov eax,[r14+0x758]                           
0x67787ff  sub eax,[r14+0x750]                           
0x6778806  shr eax,3                                     
0x6778809  imul eax,0xFFFF8BA3                           
0x677880f  dec eax                                       
0x6778811  mov [rbp+0x32C],ax                            
0x6778818  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677881f  mov rax,[rcx]                                 
0x6778822  mov rax,[rax+0x10]                            
0x6778826  mov dl,0x4A                                   
0x6778828  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677882e  nop                                           
0x677882f  mov [rbp+0x838],al                            
0x6778835  mov rdx,[r14+0x890]                           
0x677883c  cmp rdx,[r14+0x898]                           
0x6778843  je short 0x6778B29                            ; -> loc_6778b29
0x6778849  inc rdx                                       
0x677884c  mov [r14+0x890],rdx                           
0x6778853  jmp 0x6778B36                                 ; -> loc_6778b36
0x6778858  lea rcx,[r14+0x750]                           
0x677885f  lea r8,[rbp+0x6C8]                            
0x6778866  call 0x6760A80                                 ; -> sub_6760a80
0x677886b  nop                                           
0x677886c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778873  mov rax,[rcx]                                 
0x6778876  mov rax,[rax+0x10]                            
0x677887a  movzx edx,byte ptr [rbp+0x838]                
0x6778881  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778887  nop                                           
0x6778888  mov qword ptr [rbp+0x300],0x4001              
0x6778893  mov eax,[r14+0x758]                           
0x677889a  sub eax,[r14+0x750]                           
0x67788a1  shr eax,3                                     
0x67788a4  imul eax,0xFFFF8BA3                           
0x67788aa  dec eax                                       
0x67788ac  mov [rbp+0x32C],ax                            
0x67788b3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67788ba  mov rax,[rcx]                                 
0x67788bd  mov rax,[rax+0x10]                            
0x67788c1  mov dl,0x4A                                   
0x67788c3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67788c9  nop                                           
0x67788ca  mov [rbp+0x838],al                            
0x67788d0  mov rdx,[r14+0x890]                           
0x67788d7  cmp rdx,[r14+0x898]                           
0x67788de  je short 0x6778BA9                            ; -> loc_6778ba9
0x67788e4  inc rdx                                       
0x67788e7  mov [r14+0x890],rdx                           
0x67788ee  jmp 0x6778BB6                                 ; -> loc_6778bb6
0x67788f3  lea rcx,[r13+0x750]                           
0x67788fa  lea r8,[rbp+0x6F0]                            
0x6778901  call 0x6760A80                                 ; -> sub_6760a80
0x6778906  nop                                           
0x6778907  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677890e  mov rax,[rcx]                                 
0x6778911  mov rax,[rax+0x10]                            
0x6778915  movzx edx,byte ptr [rbp+0x838]                
0x677891c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778922  nop                                           
0x6778923  mov qword ptr [rbp+0x300],0x4001              
0x677892e  mov eax,[r13+0x758]                           
0x6778935  sub eax,[r13+0x750]                           
0x677893c  shr eax,3                                     
0x677893f  imul eax,0xFFFF8BA3                           
0x6778945  dec eax                                       
0x6778947  mov [rbp+0x32C],ax                            
0x677894e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778955  mov rax,[rcx]                                 
0x6778958  mov rax,[rax+0x10]                            
0x677895c  mov dl,0x4A                                   
0x677895e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778964  nop                                           
0x6778965  mov [rbp+0x838],al                            
0x677896b  mov rdx,[r13+0x890]                           
0x6778972  cmp rdx,[r13+0x898]                           
0x6778979  je short 0x6778C29                            ; -> loc_6778c29
0x677897f  inc rdx                                       
0x6778982  mov [r13+0x890],rdx                           
0x6778989  jmp 0x6778C36                                 ; -> loc_6778c36
0x677898e  lea rcx,[r13+0x750]                           
0x6778995  lea r8,[rbp+0x700]                            
0x677899c  call 0x6760A80                                 ; -> sub_6760a80
0x67789a1  nop                                           
0x67789a2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67789a9  mov rax,[rcx]                                 
0x67789ac  mov rax,[rax+0x10]                            
0x67789b0  movzx edx,byte ptr [rbp+0x838]                
0x67789b7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67789bd  nop                                           
0x67789be  mov qword ptr [rbp+0x300],0x4001              
0x67789c9  mov eax,[r13+0x758]                           
0x67789d0  sub eax,[r13+0x750]                           
0x67789d7  shr eax,3                                     
0x67789da  imul eax,0xFFFF8BA3                           
0x67789e0  dec eax                                       
0x67789e2  mov [rbp+0x32C],ax                            
0x67789e9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67789f0  mov rax,[rcx]                                 
0x67789f3  mov rax,[rax+0x10]                            
0x67789f7  mov dl,0x4A                                   
0x67789f9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67789ff  nop                                           
0x6778a00  mov [rbp+0x838],al                            
0x6778a06  mov rdx,[r13+0x890]                           
0x6778a0d  cmp rdx,[r13+0x898]                           
0x6778a14  je short 0x6778CA9                            ; -> loc_6778ca9
0x6778a1a  inc rdx                                       
0x6778a1d  mov [r13+0x890],rdx                           
0x6778a24  jmp 0x6778CB6                                 ; -> loc_6778cb6
```
// loop nest, four full iterations plus a fifth started (base register changes r14 -> r13 at the third iteration): each iteration calls sub_6760a80 with rcx=[base+0x750] and r8=[rbp+0x6B8/0x6C8/0x6F0/0x700], does two virtual calls through data_f99ffa0 (sub_eea6040) — first with byte arg [rbp+0x838], second with dl=0x4A, result -> [rbp+0x838] — stores mov qword [rbp+0x300],0x4001, computes ([base+0x758]-[base+0x750])>>3 then imul eax,0xFFFF8BA3 then dec -> [rbp+0x32C] (ax), then slot limiter: rdx=[base+0x890] vs [base+0x898], je short to exit loc (loc_6778aa9/loc_6778b29/loc_6778ba9/loc_6778ca9), else inc rdx, mov [base+0x890],rdx, jmp continuation loc (loc_6778ab6/loc_6778b36/loc_6778bb6/loc_6778c36); `nop`s are alignment fillers; final gap instruction at 0x6778a24 is jmp loc_6778cb6; no addref/lock instructions in this range.

### 0x6778b69..0x6778ba4 (done)
Ran `rdis dis 0x6778b59 40`; addresses 6778b59..6778c1a printed, gap covered (all instruction starts in 0x6778b69..0x6778ba4 present, last gap instr at 0x6778ba4).
[V] at 0x6778b69..0x6778ba4 (seen in rdis output):
```
0x6778b69  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778b70  mov rax,[rcx]                                 
0x6778b73  mov rax,[rax+0x10]                            
0x6778b77  mov dl,0x4A                                   
0x6778b79  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778b7f  nop                                           
0x6778b80  mov [rbp+0x838],al                            
0x6778b86  mov rdx,[r14+0x7A0]                           
0x6778b8d  cmp rdx,[r14+0x7A8]                           
0x6778b94  je short 0x6778FE7                            ; -> loc_6778fe7
0x6778b9a  inc rdx                                       
0x6778b9d  mov [r14+0x7A0],rdx                           
0x6778ba4  jmp short 0x6778FF4                           ; -> loc_6778ff4
```
// loop iteration tail: second virtual call through data_f99ffa0 (sub_eea6040) with dl=0x4A, result byte -> [rbp+0x838] (nop filler after), then slot limiter for a different slot pair: rdx=[r14+0x7A0] vs limit [r14+0x7A8], je short to loc_6778fe7 if equal, else inc rdx, mov [r14+0x7A0],rdx, jmp short loc_6778ff4; no addref/lock instructions.

### 0x6779404..0x6779410 (done)
Ran `rdis dis 0x67793f4 40`; addresses 67793f4..67794be printed, gap covered (all instruction starts in 0x6779404..0x6779410 present, last gap instr at 0x6779410).
[V] at 0x6779404..0x6779410 (seen in rdis output):
```
0x6779404  lea rcx,[r13+0x798]                           
0x677940b  call 0x6760E60                                ; -> sub_6760e60
0x6779410  nop                                           
```
// call sub_6760e60 with rcx=[r13+0x798], then nop alignment filler; no other operands, no side effects beyond the call [V target and annotation from rdis output].

### 0x677a4d3..0x677a4d3 (done)
Ran `rdis dis 0x677a4c3 40`; addresses 677a4c3..677a55d printed, gap covered (single instruction 0x677a4d3 present).
[V] at 0x677a4d3 (seen in rdis output):
```
0x677a4d3  cmp rcx,0x20                                  
```
// bounds check in a size computation: rcx = [rcx-8] - rax (pointer difference), compared against 0x20; `jae` at 0x677a4d7 exits to sub_677e039 if rcx >= 0x20; preceded by `adc [rax],al` / `add [rdx+0x1C],dh` junk-looking prefixes and `add rcx,0xFFFFFFFFFFFFFFF8` (rcx -= 8); no side effects beyond flags.

### 0x677a794..0x677a794 (done)
Ran `rdis dis 0x677a784 40`; addresses 677a784..677a855 printed, gap covered (single instruction 0x677a794 present).
[V] at 0x677a794 (seen in rdis output):
```
0x677a794  movups [rbx+0x98],xmm1                        
```
// store xmm1 to [rbx+0x98]; part of a store sequence: movups xmm2,[rcx+0x9F] -> [rbx+0xA7] (0x677a786/0x677a78d), [rbx+0x98] <- xmm1 (0x677a794), [rbx+0x88] <- xmm0 (0x677a79b); no side effects beyond the memory write.

### 0x677adfe..0x677ae0e (done)
Ran `rdis dis 0x677adee 40`; addresses 677adee..677aeac printed, gap covered (all instruction starts in 0x677adfe..0x677ae0e present, last gap instr at 0x677ae0e).
[V] at 0x677adfe..0x677ae0e (seen in rdis output):
```
0x677adfe  mov eax,[r14+0x798]                           
0x677ae05  not eax                                       
0x677ae07  add eax,[r14+0x7A0]                           
0x677ae0e  mov [rbp+0x326],ax                            
```
// index computation: eax = [r14+0x7A0] - [r14+0x798] (via not+add), truncated to word, stored at [rbp+0x326]; preceded by alignment-area junk (`scasb [rdi]`, `push rcx`, `and cl,[rcx]`, `nop`, `mov qword ptr [rbp+0x300],0x4803`) and followed by a virtual call through data_f99ffa0 (sub_eea6040) with dl=0x4A; no addref/lock instructions.

### 0x677b1e4..0x677b1eb (done)
Ran `rdis dis 0x677b1d4 40`; addresses 677b1d4..677b2a0 printed, gap covered (all instruction starts in 0x677b1e4..0x677b1eb present, last gap instr at 0x677b1eb).
[V] at 0x677b1e4..0x677b1eb (seen in rdis output):
```
0x677b1e4  mov [rbp+0x2A8],ax                            
0x677b1eb  mov rax,[rbp+0x768]                           
```
// same store/setup pattern as range 0x677a794: word [rbp+0x490] zero-extended -> [rbp+0x2A8], then rax=[rbp+0x768] (loads a pointer used in the size/subtract sequence `sub rdx,r8` / `cmp rdx,0xFFFFFFFFFFFFFFD0` / `je sub_677e011` that follows); no side effects beyond the two writes.

### 0x677b5eb..0x677b5f2 (done)
Ran `rdis dis 0x677b5db 40`; addresses 677b5db..677b69d printed, gap covered (all instruction starts in 0x677b5eb..0x677b5f2 present, last gap instr at 0x677b5f2).
[V] at 0x677b5eb..0x677b5f2 (seen in rdis output):
```
0x677b5eb  movzx edx,byte ptr [rbp+0x847]                
0x677b5f2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
// virtual call #1 of an iteration through data_f99ffa0 (sub_eea6040) with byte arg [rbp+0x847]; preceded by `call qword ptr [rax-0x33F274B8]` / `sub edi,[rbx+rcx+0x48018B48]` / `mov eax,[rax+0x10]` setup and followed by nop filler, `mov qword ptr [rbp+0x4A0],0x4001`, index computation ([r14+0x758]-[r14+0x750])>>3*0xFFFF8BA3-1 -> [rbp+0x4CC], virtual call #2 with dl=0x4A -> [rbp+0x847], then slot limiter [r14+0x890] vs [r14+0x898] with je loc_677b65d / inc-store-jmp loc_677b66a; no addref/lock instructions.

### 0x677b9bc..0x677b9bf (done)
Ran `rdis dis 0x677b9ac 40`; addresses 677b9ac..677ba62 printed, gap covered (all instruction starts in 0x677b9bc..0x677b9bf present, last gap instr at 0x677b9bf).
[V] at 0x677b9bc..0x677b9bf (seen in rdis output):
```
0x677b9bc  inc rdx                                       
0x677b9bf  mov [r14+0x6B0],rdx                           
```
// slot limiter for pair [r14+0x6B0] (slot) vs [r14+0x6B8] (limit): rdx=[r14+0x6B0], cmp [r14+0x6B8], je short loc_677b9c8 if equal (exit path calls sub_6760e60 with rcx=[r14+0x6A8]), else inc rdx, mov [r14+0x6B0],rdx, jmp short loc_677b9d5; no addref/lock instructions.

### 0x677ba6c..0x677bb2a (done)
Ran `rdis dis 0x677ba5c 40` + `rdis dis 0x677bb15 20`; addresses 677ba5c..677bb68 printed, gap covered (every instruction start in 0x677ba6c..0x677bb2a present, last gap instr at 0x677bb2a).
[V] at 0x677ba6c..0x677bb2a (seen in rdis output):
```
0x677ba6c  call 0x6765870                                ; -> sub_6765870
0x677ba71  nop                                           
0x677ba72  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677ba79  mov rax,[rcx]                                 
0x677ba7c  mov rax,[rax+0x10]                            
0x677ba80  movzx edx,byte ptr [rbp+0x847]                
0x677ba87  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677ba8d  nop                                           
0x677ba8e  mov rax,0x4000000202307803                    
0x677ba98  mov [rbp+0x4A0],rax                           
0x677ba9f  mov eax,[r14+0x590]                           
0x677baa6  sub eax,[r14+0x588]                           
0x677baad  shr eax,4                                     
0x677bab0  imul eax,0xFFFFAAAB                           
0x677bab6  dec eax                                       
0x677bab8  mov [rbp+0x4F2],ax                            
0x677babf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677bac6  mov rax,[rcx]                                 
0x677bac9  mov rax,[rax+0x10]                            
0x677bacd  mov dl,0x4A                                   
0x677bacf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677bad5  nop                                           
0x677bad6  mov [rbp+0x847],al                            
0x677badc  mov rdx,[r14+8]                               
0x677bae0  cmp rdx,[r14+0x10]                            
0x677bae4  je short 0x677BB05                            ; -> loc_677bb05
0x677bae6  mov r8d,0xC8                                  
0x677baec  mov rcx,rdx                                   
0x677baef  lea rdx,[rbp+0x4A0]                           
0x677baf6  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x677bafb  add qword ptr [r14+8],0xC8                    
0x677bb03  jmp short 0x677BB15                           ; -> loc_677bb15
0x677bb05  mov rcx,r14                                   
0x677bb08  lea r8,[rbp+0x4A0]                            
0x677bb0f  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x677bb14  nop                                           
0x677bb15  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677bb1c  mov rax,[rcx]                                 
0x677bb1f  mov rax,[rax+0x10]                            
0x677bb23  movzx edx,byte ptr [rbp+0x847]                
0x677bb2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
// loop iteration: call sub_6765870 with rcx=r12 (set up by pre-gap `xor bl,ch` / `adc ecx,[rcx+rcx*4-0xF]` / `add rcx,0x588`), virtual call #1 via data_f99ffa0 (sub_eea6040) with byte [rbp+0x847], store imm 0x4000000202307803 -> [rbp+0x4A0], index computation ([r14+0x590]-[r14+0x588])>>4 *0xFFFFAAAB -1 -> [rbp+0x4F2] (ax), virtual call #2 with dl=0x4A -> [rbp+0x847], then append path: rdx=[r14+8] vs [r14+0x10]; if equal je loc_677bb05 (call sub_5aba6d0 with rcx=r14, r8=[rbp+0x4A0]); else r8d=0xC8, call sub_eec6ec0(rcx=rdx, rdx=[rbp+0x4A0]), [r14+8]+=0xC8, jmp loc_677bb15; loc_677bb15 starts next iteration with virtual call #3 at 0x677bb2a; nops are fillers; no addref/lock instructions.

### 0x677c4dc..0x677c4dc (done)
Ran `rdis dis 0x677c4cc 40`; addresses 677c4cc..677c59a printed, gap covered (single instruction 0x677c4dc present).
[V] at 0x677c4dc (seen in rdis output):
```
0x677c4dc  mov [rbp+0x4B0],ax                            
```
// index computation: eax = eax - [rsi+0x8A0] (`sub eax,[rsi+0x8A0]` at 0x677c4d2), shr eax,1, dec eax, ax -> [rbp+0x4B0]; preceded by junk `xchg [rax+0x41000008],ch` and followed by virtual call #1 via data_f99ffa0 (sub_eea6040) with dl=0x4A -> [rbp+0x847], then a record-copy into [r14+0x758] (movups stores, floats [rbp+0x700..0x70C] -> [rdx+0x18..0x24], 3 movups from [rbp+0x574+0x19C..] -> [rdx+0x28/0x38/0x47], [r14+0x758]+=0x58); no addref/lock instructions.

### 0x677c9c9..0x677c9d4 (done)
Ran `rdis dis 0x677c9b9 40`; addresses 677c9b9..677ca89 printed, gap covered; rdis printed `(bad)` at 0x677c9bf (one undecodable pad byte) and decoding resumed at 0x677c9c1; all gap instruction starts in 0x677c9c9..0x677c9d4 are present, last gap instr at 0x677c9d4.
[V] at 0x677c9c9..0x677c9d4 (seen in rdis output):
```
0x677c9c9  shr eax,3                                     
0x677c9cc  imul eax,0xFFFF8E39                           
0x677c9d2  dec eax                                       
0x677c9d4  mov [rbp+0x4E2],ax                            
```
// index computation: shr eax,3, imul eax,0xFFFF8E39, dec eax, ax -> [rbp+0x4E2]; preceded by junk pad bytes (`or [rax+0x50868B41],edx` at 0x677c9b9 then `(bad)` at 0x677c9bf) and `add [rcx+0x2B],al` / `xchg [rax+6],cl` / `add [rax],al`; followed by `lea rcx,[r14+0x780]` / `lea rdx,[rbp+0x638]` / `call sub_675f3b0`, then `mov qword ptr [rbp+0x4A0],0x2005803`, index computation on [r14+0x788]-[r14+0x780] -> [rbp+0x4C8], virtual call via data_f99ffa0, then slot append path [r14+0x770] vs [r14+0x778] with sub_e869ff0 and [r14+0x770]+=0x88; no addref/lock instructions.

### 0x677d951..0x677d963 (done)
Ran `rdis dis 0x677d941 40`; addresses 677d941..677d9f8 printed, gap covered (all instruction starts in 0x677d951..0x677d963 present, last gap instr at 0x677d963).
[V] at 0x677d951..0x677d963 (seen in rdis output):
```
0x677d951  movzx eax,word ptr [rbp+0x2A8]                
0x677d958  mov [rdx],ax                                  
0x677d95b  add qword ptr [r14+0x8A8],2                   
0x677d963  jmp short 0x677D979                           ; -> loc_677d979
```
// slot append: rdx=[r14+0x8A8] vs [r14+0x8B0] (cmp at 0x677d948), je short loc_677d965 if full (exit path calls sub_1ef6f90 with rcx=[r14+0x8A0], r8=[rbp+0x2A8]); else movzx eax,word ptr [rbp+0x2A8] -> [rdx] (word store), [r14+0x8A8]+=2, jmp short loc_677d979; loc_677d979 continues with virtual call via data_f99ffa0 (sub_eea6040) with byte [rbp+0x838], index computation ([r14+0x8A8]-[r14+0x8A0])/2-1 -> [rbp+0x580], virtual call #2 dl=0x4A, then record copy into [r14+0x758] from [rbp+0x250]; no addref/lock instructions.

### 0x677e0d4..0x677e0d4 (done)
Ran `rdis dis 0x677e0c4 40`; addresses 677e0c4..677e170 printed, gap covered (single instruction 0x677e0d4 present).
[V] at 0x677e0d4 (seen in rdis output):
```
0x677e0d4  mov rdx,0xCBF29CE484222325                    
```
// FNV-like byte hash loop: `and r8,0xFFFFFFFFFFFFFFFC` (0x677e0d0, round len down to 4), `mov rdx,0xCBF29CE484222325` (0x677e0d4, hash state), `xor r9d,r9d` (0x677e0de, index), then unrolled per-4-byte loop (loc_677e0e1): xor byte, imul by rcx, 4 bytes per iteration, `jne loc_677e0e1`; tail loop loc_677e12b for remaining bytes; final state stored to data_129fb1f0 (`mov [0x129FB1F0],rdx` at 0x677e142), then calls sub_73150 / sub_e938d70 / sub_67763a9; no addref/lock instructions.
