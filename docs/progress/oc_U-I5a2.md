## NEXT
Unit COMPLETE: Function 0x6664a00 fully reversed (0x6664a00..0x6668106 hot path + 0x6668107..0x6668510 cold blocks). 68 phases + 5 gaps + cold blocks documented. verify_oc.py: 2907/2907 match.

## Step 0 Complete: Preflight and BGFX_MAP 6ce
- Ran `PYTHONUTF8=1 python tools/preflight.py 0x6664a00 --n 300`
- Output written to `docs/progress/pre/0x6664a00.md` (320 lines)
- BGFX_MAP 6ce read: UI+ImGui frame function 0x6664a00 (0x3b10 bytes) handles `Debug/ImGui` (tag 4) and `UI/Blit` passes; sole caller of UI group extractor 0x674a3a0 (called twice, at 0x6664d46 and 0x6664f4a); UIImGui tag handler at 0x6664aab per docs/progress/oc_U-D8b-imgui2.md (reuse, do not redo)
- Callees identified: sub_73150, sub_75720, sub_75740, sub_75b60, sub_79580, sub_a0850, sub_1166e0, sub_11d1f0, sub_9bc830, sub_a77be0, sub_aa6580, sub_14db710, sub_1771500, sub_1ef6f90, sub_4dedd00, sub_4e69050, sub_4e69370, sub_5668ac0, sub_5679db0, sub_567db00, sub_56d55e0, sub_5aba5c0, sub_5aba6d0, sub_66a0f60, sub_66a65b0, sub_66b2730, sub_66e74b0, sub_674a3a0 (x2), sub_675e440 (x2), sub_675f3b0, sub_675fb30, sub_6760710, sub_6760a80, sub_6760e60, sub_bbd7c70, sub_bcaba00, sub_e869ff0, sub_e86b370, sub_e935700, sub_e935740, sub_e938cb0, sub_e938d70, sub_eec6d80, sub_eec6de0, sub_eec6e70, sub_eec6ec0, sub_eec7570
- Strings referenced (from preflight callees section): "Debug/ImGui" at 0x6664ae9/0x6668252, "UI/Blit" at 0x6664d8f/0x66682b7, "ImGuiProj" at 0x66683f6, "Unnamed Transaction" at 0x666597d/0x6666429

## Step 1 Complete: Instruction-complete listing of 0x6664a00 (first 500 instructions, 13 phases)
Full function size: 0x3b10 bytes (15,120 bytes). Listing saved to `docs/data/listings/ui_imgui_frame_fn.lst`. First 500 instructions below in phases of ≤40 instructions.

### Phase 0: Prologue & Switch Dispatch (0x6664a00..0x6664aab, 40 ins)
```
0x6664a00  push rbp
0x6664a01  push r15
0x6664a03  push r14
0x6664a05  push r13
0x6664a07  push r12
0x6664a09  push rsi
0x6664a0a  push rdi
0x6664a0b  push rbx
0x6664a0c  sub rsp,0x5F8
0x6664a13  lea rbp,[rsp+0x80]
0x6664a1b  movaps [rbp+0x560],xmm9
0x6664a23  movaps [rbp+0x550],xmm8
0x6664a2b  movaps [rbp+0x540],xmm7
0x6664a32  movaps [rbp+0x530],xmm6
0x6664a39  mov qword ptr [rbp+0x528],0xFFFFFFFFFFFFFFFE
0x6664a44  movzx eax,byte ptr [r8+8]                     ; R a2+0x8
0x6664a49  cmp rax,4
0x6664a4d  ja 0x66682F3                                  ; -> sub_66682f3
0x6664a53  mov r14,rdx                                   
0x6664a56  mov r13,rcx                                   
0x6664a59  mov r9,[r8]                                   ; R a2+0x0
0x6664a5c  lea rcx,[0xF2BF468]                           ; [data_f2bf468]
0x6664a63  movsxd rax,[rcx+rax*4]                        
0x6664a67  add rax,rcx                                   
0x6664a6a  jmp rax                                       
0x6664a6c  mov rcx,r13                                   
0x6664a6f  mov rdx,r14                                   
0x6664a72  mov r8,r9                                     
0x6664a75  movaps xmm6,[rbp+0x530]                       
0x6664a7c  movaps xmm7,[rbp+0x540]                       
0x6664a83  movaps xmm8,[rbp+0x550]                       
0x6664a8b  movaps xmm9,[rbp+0x560]                       
0x6664a93  add rsp,0x5F8                                 
0x6664a9a  pop rbx                                       
0x6664a9b  pop rdi                                       
0x6664a9c  pop rsi                                       
0x6664a9d  pop r12                                       
0x6664a9f  pop r13                                       
0x6664aa1  pop r14                                       
0x6664aa3  pop r15                                       
0x6664aa5  pop rbp                                       
0x6664aa6  jmp 0x66ADE80                                 ; -> sub_66ade80
0x6664aab  mov [rbp+0x520],r9                            
```
Purpose: Standard prologue saving non-volatile registers, allocating 0x5F8 bytes stack, setting up rbp frame pointer at rsp+0x80. Saves xmm6-xmm9. Initializes stack cookie at [rbp+0x528]. Argument 3 (r8) byte at +0x8 is a switch index (0-4): cmp rax,4 / ja 0x66682F3 (invalid -> error). Saves args: r13=rcx (this), r14=rdx (arg1), r9=[r8] (arg2+0x0). Jump table at 0xF2BF468 (4-byte relative offsets) dispatches on the index. Case 0 (index 0): falls through to 0x6664aab (UIImGui tag handler, desc base = r9 saved at [rbp+0x520]). Cases 1-4 at 0x6664a6c..0x6664aa6 jump to sub_66ade80 (Gameface/UI editor path). Index 4 at 0x6664a6c is the UI/Blit case (per preflight, case 4 jumps to UI/Blit handler at 0x6664d51).

### Phase 1: UIImGui (Tag 4) - Debug/ImGui Pass Setup (0x6664aab..0x6664b6f, 40 ins)
```
0x6664aab  mov [rbp+0x520],r9                            
0x6664ab2  mov eax,[0x129F8F50]                          ; [data_129f8f50]
0x6664ab8  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6664abe  mov rdx,gs:[0x58]                             
0x6664ac7  mov rcx,[rdx+rcx*8]                           
0x6664acb  cmp eax,[rcx+4]                               
0x6664ad1  jg 0x6668232                                  ; -> sub_6668232
0x6664ad7  mov r9,[r14+0x40]                             
0x6664adb  mov rcx,[r14+0x68]                            
0x6664adf  xorps xmm0,xmm0                               
0x6664ae2  movaps [rbp+0x1E0],xmm0                       
0x6664ae9  lea rax,[0xF5AD096]                           ; [data_f5ad096] "Debug/ImGui"
0x6664af0  mov [rbp+0x400],rax                           
0x6664af7  mov qword ptr [rbp+0x408],0xB                 
0x6664b02  lea rsi,[rbp+0x1E0]                           
0x6664b09  mov [rsp+0x28],rsi                            
0x6664b0e  lea rax,[rbp+0x400]                           
0x6664b15  mov [rsp+0x20],rax                            
0x6664b1a  lea r8,[0x129F8F40]                           ; [data_129f8f40]
0x6664b21  lea rdx,[rbp+0x4D0]                           
0x6664b28  call 0x675E440                                ; -> sub_675e440
0x6664b2d  mov rax,[rbp+0x4D0]                           
0x6664b34  mov rdi,[rax]                                 
0x6664b37  test rdi,rdi                                  
0x6664b3a  je 0x6667935                                  ; -> sub_6667935
0x6664b40  mov eax,[0x129CA5E0]                          ; [data_129ca5e0]
0x6664b46  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6664b4c  mov rdx,gs:[0x58]                             
0x6664b55  mov rcx,[rdx+rcx*8]                           
0x6664b59  cmp eax,[rcx+4]                               
0x6664b5f  jg 0x66682FF                                  ; -> sub_66682ff
0x6664b65  cmp byte ptr [rdi+0x10],1                     
0x6664b69  jne 0x6667935                                 ; -> sub_6667935
```
Purpose: UIImGui case (tag 4). Saves description pointer r9 (from arg2+0x0) at [rbp+0x520]. TLS guard check via gs:[0x58] against global 0x129F8F50. Loads r9=[r14+0x40], rcx=[r14+0x68] from arg1. Sets up string "Debug/ImGui" (RVA 0xF5AD096, length 0xB) at [rbp+0x400]/[rbp+0x408]. Calls sub_675e440 (pass lookup by name) with args (r8=0x129F8F40, rdx=&[rbp+0x4D0], rsi=&[rbp+0x1E0], stack args). On return, rax=[rbp+0x4D0] holds pass object, rdi=*rax. If null or [rdi+0x10]!=1, jumps to error cleanup at 0x6667935. Second TLS guard check against global 0x129CA5E0.

### Phase 2: UIImGui - Resource Refcount & Validation (0x6664b6f..0x6664bd6, 40 ins)
```
0x6664b6f  mov rax,[rbp+0x4D0]                           
0x6664b76  mov rcx,[rax+8]                               
0x6664b7a  test rcx,rcx                                  
0x6664b7d  je 0x6664F65                                  ; -> loc_6664f65
0x6664b83  lock inc dword ptr [rcx+8]                    
0x6664b87  mov rcx,[rax]                                 
0x6664b8a  mov rdi,[rax+8]                               
0x6664b8e  mov rax,[rcx+0x18]                            
0x6664b92  mov rbx,[rax]                                 
0x6664b95  test rdi,rdi                                  
0x6664b98  je 0x6664F6F                                  ; -> loc_6664f6f
0x6664b9e  lock dec dword ptr [rdi+8]                    
0x6664ba2  jne 0x6664F6F                                 ; -> loc_6664f6f
0x6664ba8  mov rax,[rdi]                                 
0x6664bab  mov rax,[rax]                                 
0x6664bae  mov rcx,rdi                                   
0x6664bb1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6664bb7  lock dec dword ptr [rdi+0xC]                  
0x6664bbb  jne 0x6664F6F                                 ; -> loc_6664f6f
0x6664bc1  mov rax,[rdi]                                 
0x6664bc4  mov rax,[rax+8]                               
0x6664bc8  mov rcx,rdi                                   
0x6664bcb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6664bd1  jmp 0x6664F6F                                 ; -> loc_6664f6f
```
Purpose: Refcount management for the pass object. Loads [rax+8] (refcounted resource), increments its refcount at +0x8. If null, jumps to loc_6664f65 (sets up rbx from desc). Loads rdi=[rax+8] (resource), rbx=[[rcx+0x18]] (desc field). If rdi null, jumps to loc_6664f6f. Decrements rdi refcount at +0x8; if not zero, jumps to loc_6664f6f. Calls sub_eea6040 (via [0xF99FFA0]) for resource destruction (first vtable slot 0, then slot 1 at +8). Decrements rdi+0xC; if not zero, jumps to loc_6664f6f. This is shared_ptr-like destruction logic.

### Phase 3: UIImGui - Desc Field Extraction (0x6664bd6..0x6664c58, 40 ins)
```
0x6664bd6  movzx ecx,byte ptr [r9+0x82]                  
0x6664bde  movzx r12d,byte ptr [r9+0x83]                 
0x6664be6  movzx edx,byte ptr [r9+0x84]                  
0x6664bee  test cl,cl                                    
0x6664bf0  mov r8d,1                                     
0x6664bf6  cmove r8d,edx                                 
0x6664bfa  test r12b,r12b                                
0x6664bfd  mov r10d,2                                    
0x6664c03  cmove r10d,r8d                                
0x6664c07  lea rbx,[r9+0x88]                             
0x6664c0e  mov byte ptr [rbp+0x224],0                    
0x6664c15  movzx esi,byte ptr [r9+0x85]                  
0x6664c1d  movzx r8d,byte ptr [r9+0x81]                  
0x6664c25  movss xmm0,[r9+0x70]                          
0x6664c2b  mov r11,[r9+0x60]                             
0x6664c2f  mov rdx,[r9+0x68]                             
0x6664c33  movzx edi,byte ptr [r9+0x80]                  
0x6664c3b  lea rax,[r9+0x18]                             
0x6664c3f  cmp qword ptr [r9+0x58],2                     
0x6664c44  mov [rbp+0x520],cl                            
0x6664c4a  mov [rbp+0x518],r12b                          
0x6664c51  mov [rbp+0x510],dil                           
0x6664c58  jb 0x6664E7C                                  ; -> loc_6664e7c
```
Purpose: Extracts multiple byte fields from the description object at r9 (which is the source object pointer, NOT the desc - see oc_U-D8b-imgui2.md rebinding caveat). Reads bytes at +0x80..+0x85, +0x70 (float), +0x60/+0x68 (pointers). Conditional logic: if [r9+0x58] < 2 (unsigned), jumps to loc_6664e7c (alternate path). Saves extracted bytes to stack locals [rbp+0x520], [rbp+0x518], [rbp+0x510], [rbp+0x224]. Sets up rbx=r9+0x88, rax=r9+0x18 for later use.

### Phase 4: UIImGui - Primary Resource Path ([r9+0x58] >= 2) (0x6664c5e..0x6664d46, 40 ins)
```
0x6664c5e  xorps xmm1,xmm1                               
0x6664c61  movaps [rbp+0x400],xmm1                       
0x6664c68  mov r15,[r9+0x30]                             
0x6664c6c  test r15,r15                                  
0x6664c6f  je 0x6664E8E                                  ; -> loc_6664e8e
0x6664c75  lock inc dword ptr [r15+8]                    
0x6664c7a  mov r15,[r9+0x30]                             
0x6664c7e  jmp 0x6664E91                                 ; -> loc_6664e91
0x6664c83  lea rax,[r9+0x40]                             
0x6664c87  mov rcx,[r9+0x30]                             
0x6664c8b  movzx edx,byte ptr [r9+0x3A]                  
0x6664c90  movaps xmm0,[0xEF40DE0]                       ; [data_ef40de0]
0x6664c97  movaps [rbp+0x1E0],xmm0                       
0x6664c9e  mov r8,[r9+0x20]                              
0x6664ca2  lea rdi,[r9+0x10]                             
0x6664ca6  xorps xmm0,xmm0                               
0x6664ca9  movaps [rbp+0x400],xmm0                       
0x6664cb0  mov r10,[r9+0x28]                             
0x6664cb4  mov r11,[r9]                                  
0x6664cb7  mov rsi,[r9+8]                                
0x6664cbb  add r9,0x38                                   
0x6664cbf  mov [rsp+0xA0],rax                            
0x6664cc7  mov [rsp+0x98],rcx                            
0x6664ccf  mov [rsp+0x70],dl                             
0x6664cd3  lea rax,[rbp+0x1E0]                           
0x6664cda  mov [rsp+0x60],rax                            
0x6664cdf  mov [rsp+0x58],r8                             
0x6664ce4  lea rax,[rbp+0x400]                           
0x6664ceb  mov [rsp+0x48],rax                            
0x6664cf0  mov [rsp+0x40],rdi                            
0x6664cf5  mov [rsp+0x38],r10                            
0x6664cfa  mov [rsp+0x30],rsi                            
0x6664cff  mov [rsp+0x20],r11                            
0x6664d04  mov dword ptr [rsp+0x90],0                    
0x6664d0f  mov byte ptr [rsp+0x88],0                     
0x6664d17  mov byte ptr [rsp+0x80],0                     
0x6664d1f  mov byte ptr [rsp+0x78],0                     
0x6664d24  mov dword ptr [rsp+0x68],0x3F800000           
0x6664d2c  mov byte ptr [rsp+0x50],0                     
0x6664d31  mov qword ptr [rsp+0x28],0                    
0x6664d3a  mov rcx,r13                                   
0x6664d3d  mov rdx,r14                                   
0x6664d40  mov r8d,1                                     
0x6664d46  call 0x674A3A0                                ; -> sub_674a3a0
```
Purpose: When [r9+0x58] >= 2, takes the primary resource path. Loads r15=[r9+0x30] (resource pointer), increments its refcount. Sets up extensive stack argument block for call to sub_674a3a0 (UI group extractor): loads constant xmm from 0xEF40DE0 to [rbp+0x1E0], prepares pointers from r9+0x10..+0x40, sets stack args including float 1.0 (0x3F800000) at [rsp+0x68]. Calls sub_674a3a0 (UI group extractor) with rcx=r13 (this), rdx=r14 (arg1), r8d=1. This is the FIRST call to the UI group extractor (for Debug/ImGui pass).

### Phase 5: UIImGui - Post-Extractor Join (0x6664d4b..0x6664d51, 5 ins)
```
0x6664d4b  nop                                           
0x6664d4c  jmp 0x6664F50                                 ; -> loc_6664f50
```
Purpose: After UI group extractor returns, jumps to common join point at loc_6664f50.

### Phase 6: Case 4 - UI/Blit Pass Setup (0x6664d51..0x6664e0b, 40 ins)
```
0x6664d51  mov [rbp+0x520],r9                            
0x6664d58  mov eax,[0x129F9398]                          ; [data_129f9398]
0x6664d5e  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6664d64  mov rdx,gs:[0x58]                             
0x6664d6d  mov rcx,[rdx+rcx*8]                           
0x6664d71  cmp eax,[rcx+4]                               
0x6664d77  jg 0x6668294                                  ; -> sub_6668294
0x6664d7d  mov r9,[r14+0x40]                             
0x6664d81  mov rcx,[r14+0x68]                            
0x6664d85  xorps xmm0,xmm0                               
0x6664d88  movaps [rbp+0x1E0],xmm0                       
0x6664d8f  lea rax,[0xF539A95]                           ; [data_f539a95] "UI/Blit"
0x6664d96  mov [rbp+0x400],rax                           
0x6664d9d  mov qword ptr [rbp+0x408],7                   
0x6664da8  lea rsi,[rbp+0x1E0]                           
0x6664daf  mov [rsp+0x28],rsi                            
0x6664db4  lea rax,[rbp+0x400]                           
0x6664dbb  mov [rsp+0x20],rax                            
0x6664dc0  lea r8,[0x129F9388]                           ; [data_129f9388]
0x6664dc7  lea rdx,[rbp+0x390]                           
0x6664dce  call 0x675E440                                ; -> sub_675e440
0x6664dd3  mov rax,[rbp+0x390]                           
0x6664dda  mov rdi,[rax]                                 
0x6664ddd  test rdi,rdi                                  
0x6664de0  je 0x666809E                                  ; -> sub_666809e
0x6664de6  mov eax,[0x129CA5E0]                          ; [data_129ca5e0]
0x6664dec  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6664df2  mov rdx,gs:[0x58]                             
0x6664dfb  mov rcx,[rdx+rcx*8]                           
0x6664dff  cmp eax,[rcx+4]                               
0x6664e05  jg 0x6668342                                  ; -> sub_6668342
0x6664e0b  cmp byte ptr [rdi+0x10],1                     
```
Purpose: Case 4 (index 4) - UI/Blit pass. Nearly identical structure to Phase 1 but for "UI/Blit" string (RVA 0xF539A95, length 7). TLS guard checks against globals 0x129F9398 and 0x129CA5E0. Calls sub_675e440 for pass lookup. Error jumps to 0x666809E (different from UIImGui's 0x6667935).

### Phase 7: UI/Blit - Resource Refcount & Validation (0x6664e0f..0x6664e7c, 40 ins)
```
0x6664e0f  jne 0x666809E                                 ; -> sub_666809e
0x6664e15  mov rax,[rbp+0x390]                           
0x6664e1c  mov rcx,[rax+8]                               
0x6664e20  test rcx,rcx                                  
0x6664e23  je 0x6664FAF                                  ; -> loc_6664faf
0x6664e29  lock inc dword ptr [rcx+8]                    
0x6664e2d  mov rcx,[rax]                                 
0x6664e30  mov rdi,[rax+8]                               
0x6664e34  mov rax,[rcx+0x18]                            
0x6664e38  mov rbx,[rax]                                 
0x6664e3b  test rdi,rdi                                  
0x6664e3e  je 0x6664FB9                                  ; -> loc_6664fb9
0x6664e44  lock dec dword ptr [rdi+8]                    
0x6664e48  jne 0x6664FB9                                 ; -> loc_6664fb9
0x6664e4e  mov rax,[rdi]                                 
0x6664e51  mov rax,[rax]                                 
0x6664e54  mov rcx,rdi                                   
0x6664e57  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6664e5d  lock dec dword ptr [rdi+0xC]                  
0x6664e61  jne 0x6664FB9                                 ; -> loc_6664fb9
0x6664e67  mov rax,[rdi]                                 
0x6664e6a  mov rax,[rax+8]                               
0x6664e6e  mov rcx,rdi                                   
0x6664e71  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6664e77  jmp 0x6664FB9                                 ; -> loc_6664fb9
```
Purpose: Identical refcount/destruction logic as Phase 2 but for UI/Blit pass object. Jumps to loc_6664faf (null [rax+8] path) or loc_6664fb9 (shared destruction path).

### Phase 8: UIImGui Alternate Path - [r9+0x58] < 2 (0x6664e7c..0x6664ea9, 30 ins)
```
0x6664e7c  mov rcx,r13                                   
0x6664e7f  mov rdi,r14                                   
0x6664e82  xorps xmm1,xmm1                               
0x6664e85  movaps [rbp+0x400],xmm1                       
0x6664e8c  jmp short 0x6664EA9                           ; -> loc_6664ea9
0x6664e8e  xor r15d,r15d                                 
0x6664e91  mov rcx,r13                                   
0x6664e94  mov rdi,r14                                   
0x6664e97  mov r12,[r9+0x28]                             
0x6664e9b  mov [rbp+0x400],r12                           
0x6664ea2  mov [rbp+0x408],r15                           
0x6664ea9  mov r15,[r9+0x10]                             
0x6664ead  mov r12,[r9+0x78]                             
0x6664eb1  mov r13,[r9]                                  
0x6664eb4  mov r14,[r9+8]                                
0x6664eb8  add r9,0x86                                   
0x6664ebf  mov [rsp+0xA0],rbx                            
0x6664ec7  lea rbx,[rbp+0x1E0]                           
0x6664ece  mov [rsp+0x98],rbx                            
0x6664ed6  mov [rsp+0x90],r10d                           
0x6664ede  mov [rsp+0x60],rdx                            
0x6664ee3  mov [rsp+0x58],r11                            
0x6664ee8  lea r10,[rbp+0x400]                           
0x6664eef  mov [rsp+0x48],r10                            
0x6664ef4  mov [rsp+0x40],rax                            
0x6664ef9  mov [rsp+0x38],r13                            
0x6664efe  mov [rsp+0x30],r15                            
0x6664f03  mov [rsp+0x28],r12                            
0x6664f08  mov [rsp+0x20],r14                            
0x6664f0d  mov [rsp+0x88],sil                            
0x6664f15  movzx eax,byte ptr [rbp+0x520]                
0x6664f1c  mov [rsp+0x80],al                             
0x6664f23  movzx eax,byte ptr [rbp+0x518]                
0x6664f2a  mov [rsp+0x78],al                             
0x6664f2e  mov [rsp+0x70],r8b                            
0x6664f33  movzx eax,byte ptr [rbp+0x510]                
0x6664f3a  mov [rsp+0x50],al                             
0x6664f3e  movss [rsp+0x68],xmm0                         
0x6664f44  mov rdx,rdi                                   
0x6664f47  xor r8d,r8d                                   
0x6664f4a  call 0x674A3A0                                ; -> sub_674a3a0
```
Purpose: Alternate path for UIImGui when [r9+0x58] < 2 (taken from Phase 3 jb). Sets up different stack argument block for sub_674a3a0: zeroes [rbp+0x400], loads r15=[r9+0x10], r12=[r9+0x78], r13=[r9], r14=[r9+8], advances r9 by 0x86. Prepares stack args from saved bytes ([rbp+0x520], [rbp+0x518], [rbp+0x510], [rbp+0x224] via sil) and xmm0. Calls sub_674a3a0 SECOND time (for UIImGui alternate path) with r8d=0.

### Phase 9: Common Join & Error Dispatch (0x6664f4f..0x6664fb9, 40 ins)
```
0x6664f4f  nop                                           
0x6664f50  mov rsi,[rbp+0x408]                           
0x6664f57  test rsi,rsi                                  
0x6664f5a  jne 0x66680AA                                 ; -> sub_66680aa
0x6664f60  jmp 0x66680D5                                 ; -> sub_66680d5
0x6664f65  mov rax,[rax]                                 
0x6664f68  mov rax,[rax+0x18]                            
0x6664f6c  mov rbx,[rax]                                 
0x6664f6f  test rbx,rbx                                  
0x6664f72  je 0x6667935                                  ; -> sub_6667935
0x6664f78  mov rax,[rbp+0x520]                           
0x6664f7f  mov r9,[rax]                                  
0x6664f82  mov r15,[rax+8]                               
0x6664f86  movzx r8d,word ptr [r9+0x80]                  
0x6664f8e  movzx ecx,r8w                                 
0x6664f92  mov rax,r15                                   
0x6664f95  shr rax,0x20                                  
0x6664f99  je 0x6665032                                  ; -> loc_6665032
0x6664f9f  mov rax,r15                                   
0x6664fa2  xor edx,edx                                   
0x6664fa4  div rcx                                       
0x6664fa7  mov r12,rax                                   
0x6664faa  jmp 0x666503C                                 ; -> loc_666503c
0x6664faf  mov rax,[rax]                                 
0x6664fb2  mov rax,[rax+0x18]                            
0x6664fb6  mov rbx,[rax]                                 
0x6664fb9  test rbx,rbx                                  
```
Purpose: Common join at loc_6664f50 checks [rbp+0x408] (return value from sub_674a3a0?); if non-zero jumps to 0x66680AA else 0x66680D5. Error paths: loc_6664f65 (from Phase 2 null [rax+8]) loads rbx from desc+0x18. loc_6664f6f (shared destruction join) tests rbx, loads desc from [rbp+0x520], then **rebinds r9 = [rax] (desc+0x00 = source object)** per oc_U-D8b-imgui2.md caveat. Loads r15=[rax+8], reads word at [r9+0x80], divides r15>>32 by that word. loc_6664faf (UI/Blit null [rax+8] path) similar rbx load. loc_6664fb9 (shared destruction join for UI/Blit) tests rbx.

### Phase 10: UI/Blit Destruction Join - Resource Cleanup (0x6664fbc..0x66650c6, 40 ins)
```
0x6664fbc  je 0x666809E                                  ; -> sub_666809e
0x6664fc2  mov rbx,[r14]                                 
0x6664fc5  mov rax,[rbp+0x390]                           
0x6664fcc  xorps xmm0,xmm0                               
0x6664fcf  movaps [rbp+0x1E0],xmm0                       
0x6664fd6  mov rcx,[rax+8]                               
0x6664fda  test rcx,rcx                                  
0x6664fdd  je 0x6665085                                  ; -> loc_6665085
0x6664fe3  lock inc dword ptr [rcx+8]                    
0x6664fe7  mov rdi,[rbp+0x1E8]                           
0x6664fee  movups xmm0,[rax]                             
0x6664ff1  movaps [rbp+0x1E0],xmm0                       
0x6664ff8  test rdi,rdi                                  
0x6664ffb  je 0x666509A                                  ; -> loc_666509a
0x6665001  lock dec dword ptr [rdi+8]                    
0x6665005  jne 0x666509A                                 ; -> loc_666509a
0x666500b  mov rax,[rdi]                                 
0x666500e  mov rax,[rax]                                 
0x6665011  mov rcx,rdi                                   
0x6665014  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666501a  lock dec dword ptr [rdi+0xC]                  
0x666501e  jne short 0x666509A                           ; -> loc_666509a
0x6665020  mov rax,[rdi]                                 
0x6665023  mov rax,[rax+8]                               
0x6665027  mov rcx,rdi                                   
0x666502a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665030  jmp short 0x666509A                           ; -> loc_666509a
```
Purpose: UI/Blit destruction path. If rbx null, jumps to error 0x666809E. Loads rbx=[r14] (arg1). Zeroes [rbp+0x1E0]. Loads rcx=[rax+8] from pass object. If null, jumps to loc_6665085. Increments refcount, loads rdi=[rbp+0x1E8], copies xmm from [rax] to [rbp+0x1E0]. If rdi null, jumps to loc_666509a. Standard shared_ptr destruction: dec refcount at +8, if zero call sub_eea6040 (vtable slot 0), dec refcount at +0xC, if zero call sub_eea6040 (vtable slot 1 at +8). Jumps to loc_666509a.

### Phase 11: Division Helper & Setup (0x6665032..0x66650c6, 40 ins)
```
0x6665032  mov eax,r15d                                  
0x6665035  xor edx,edx                                   
0x6665037  div ecx                                       
0x6665039  mov r12d,eax                                  
0x666503c  mov rbx,[r14+0x10]                            
0x6665040  mov qword ptr [rbp+0x258],0                   
0x666504b  mov rax,[r9+0x78]                             
0x666504f  test rax,rax                                  
0x6665052  je 0x666581E                                  ; -> loc_666581e
0x6665058  lea rax,[rax+rax*2]                           
0x666505c  lea rcx,[rax*2-6]                             
0x6665064  mov rdx,0xAAAAAAAAAAAAAAAB                    
0x666506e  mov rax,rcx                                   
0x6665071  mul rdx                                       
0x6665074  cmp rcx,6                                     
0x6665078  jae 0x6665776                                 ; -> loc_6665776
0x666507e  xor ecx,ecx                                   
0x6665080  jmp 0x66657FC                                 ; -> loc_66657fc
0x6665085  mov rax,[rax]                                 
0x6665088  mov [rbp+0x1E0],rax                           
0x666508f  mov qword ptr [rbp+0x1E8],0                   
0x666509a  mov rax,[rbp+0x1E0]                           
0x66650a1  mov rax,[rax+0x18]                            
0x66650a5  mov rax,[rax]                                 
0x66650a8  mov [rbp+0xE0],rax                            
0x66650af  lea rcx,[rbp+0xE8]                            
0x66650b6  mov r8,[rbx]                                  
0x66650b9  mov rdx,[rax+0x170]                           
0x66650c0  call 0xE86B370                                ; -> sub_e86b370
```
Purpose: Division helper at loc_6665032 (r15d / ecx -> r12d). loc_666503c: rbx=[r14+0x10], zeroes [rbp+0x258]. Loads rax=[r9+0x78]; if null jumps to loc_666581e. Computes rax*3*2-6 = rax*6-6, multiplies by magic constant 0xAAAAAAAAAAAAAAAB (division by 3), compares rcx>=6. loc_6665085: null [rax+8] path, stores [rax] and 0. loc_666509a: loads [rbp+0xE0] = [[rbp+0x1E0]+0x18], sets up call to sub_e86b370 with rcx=&[rbp+0xE8], r8=[rbx], rdx=[rax+0x170].

### Phase 12: Refcount Cleanup & Loop Setup (0x66650c5..0x66651ae, 40 ins)
```
0x66650c5  nop                                           
0x66650c6  mov [rbp+0x160],rbx                           
0x66650cd  mov rdi,[rbp+0x1E8]                           
0x66650d4  test rdi,rdi                                  
0x66650d7  je short 0x6665104                            ; -> loc_6665104
0x66650d9  lock dec dword ptr [rdi+8]                    
0x66650dd  jne short 0x6665104                           ; -> loc_6665104
0x66650df  mov rax,[rdi]                                 
0x66650e2  mov rax,[rax]                                 
0x66650e5  mov rcx,rdi                                   
0x66650e8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66650ee  lock dec dword ptr [rdi+0xC]                  
0x66650f2  jne short 0x6665104                           ; -> loc_6665104
0x66650f4  mov rax,[rdi]                                 
0x66650f7  mov rax,[rax+8]                               
0x66650fb  mov rcx,rdi                                   
0x66650fe  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665104  mov rax,[rbp+0x520]                           
0x666510b  mov r8,[rax]                                  
0x666510e  mov rax,[rbp+0x128]                           
0x6665115  movzx r9d,word ptr [rbp+0x132]                
0x666511d  mov ecx,r9d                                   
0x6665120  shl ecx,4                                     
0x6665123  lea rdx,[rcx+rcx*2]                           
0x6665127  mov rcx,rax                                   
0x666512a  test r9,r9                                    
0x666512d  je short 0x6665155                            ; -> loc_6665155
0x666512f  mov r9,[0x129F8318]                           ; [data_129f8318]
0x6665136  mov r10,rdx                                   
0x6665139  mov rcx,rax                                   
0x666513c  nop [rax]                                     
0x6665140  mov r11,[rcx]                                 
0x6665143  cmp [r11+0x28],r9                             
0x6665147  je short 0x6665155                            ; -> loc_6665155
0x6665149  add rcx,0x30                                  
0x666514d  add r10,0xFFFFFFFFFFFFFFD0                    
0x6665151  jne short 0x6665140                           ; -> loc_6665140
0x6665153  jmp short 0x66651AE                           ; -> loc_66651ae
```
Purpose: Standard shared_ptr cleanup for rdi=[rbp+0x1E8]. Then loads desc from [rbp+0x520], r8=[rax] (source object). Loads rax=[rbp+0x128], word at [rbp+0x132] -> r9d (count). Computes rdx = count*6 (shl 4 + lea rdx,[rcx+rcx*2] = count*16 + count*2 = count*18? Wait: shl ecx,4 = count*16, lea rdx,[rcx+rcx*2] = count*16 + count*32 = count*48? No: lea rdx,[rcx+rcx*2] with rcx=count*16 gives rdx=count*16 + count*32 = count*48. But then loop uses stride 0x30 (48). So rdx = count * 48 = total byte size. Loop at 0x6665140 searches array at rcx (rax) with stride 0x30 for entry matching [0x129F8318] at +0x28.

### Phase 13: Array Search & Per-Element Call (0x6665155..0x6665354, 40 ins)
```
0x6665155  add rdx,rax                                   
0x6665158  cmp rcx,rdx                                   
0x666515b  jae short 0x66651AE                           ; -> loc_66651ae
0x666515d  add r8,8                                      
0x6665161  sub ecx,eax                                   
0x6665163  shr ecx,4                                     
0x6665166  imul eax,ecx,0xFFFFAAAB                       
0x666516c  mov [rbp+0x400],ax                            
0x6665173  mov byte ptr [rbp+0x402],1                    
0x666517a  mov byte ptr [rbp+0x1EC],0                    
0x6665181  mov dword ptr [rsp+0x20],0                    
0x6665189  lea rcx,[rbp+0xE0]                            
0x6665190  lea rdx,[rbp+0x400]                           
0x6665197  lea r9,[rbp+0x1E0]                            
0x666519e  call 0xBCABA00                                ; -> sub_bcaba00
0x66651a3  nop                                           
0x66651a4  mov rax,[rbp+0x520]                           
0x66651ab  mov r8,[rax]                                  
0x66651ae  movss xmm0,[r8+0x28]                          
0x66651b4  shufps xmm0,xmm0,0                            
0x66651b8  movaps [rbp+0x1E0],xmm0                       
0x66651bf  mov qword ptr [rbp+0x400],1                   
0x66651ca  mov [rbp+0x408],rsi                           
0x66651d1  mov rax,[rbp+0x118]                           
0x66651d8  movzx r9d,word ptr [rbp+0x122]                
0x66651e0  mov edx,r9d                                   
0x66651e3  shl edx,4                                     
0x66651e6  mov rcx,rax                                   
0x66651e9  test r9d,r9d                                  
0x66651ec  je short 0x6665215                            ; -> loc_6665215
0x66651ee  mov r9,[0x129F8358]                           ; [data_129f8358]
0x66651f5  mov r10,rdx                                   
0x66651f8  mov rcx,rax                                   
0x66651fb  nop [rax+rax]                                 
0x6665200  mov r11,[rcx]                                 
0x6665203  cmp [r11+0x28],r9                             
0x6665207  je short 0x6665215                            ; -> loc_6665215
0x6665209  add rcx,0x10                                  
0x666520d  add r10,0xFFFFFFFFFFFFFFF0                    
0x6665211  jne short 0x6665200                           ; -> loc_6665200
0x6665213  jmp short 0x666524C                           ; -> loc_666524c
```
Purpose: If search loop found match (rcx < rdx), computes element index: (r8 - base) / 8? Actually r8 was advanced by 8 per iteration, then sub ecx,eax / shr ecx,4 / imul eax,ecx,0xFFFFAAAB (divide by 16? 0xFFFFAAAB = -1/16 approx). Result in ax stored at [rbp+0x400]. Sets flag [rbp+0x402]=1, [rbp+0x1EC]=0. Calls sub_bcaba00 (Item group visitor) with rcx=&[rbp+0xE0], rdx=&[rbp+0x400], r9=&[rbp+0x1E0]. Then loads float from [r8+0x28] (source object +0x28), broadcasts via shufps, stores to [rbp+0x1E0]. Sets [rbp+0x400]=1, [rbp+0x408]=rsi. Second array search at [rbp+0x118] with count at [rbp+0x122], stride 0x10, matching [0x129F8358] at +0x28.

---

## Running String Reference Table (Phase 0-13)

| String RVA | Text | Call Site RVA | Callee After |
|------------|------|---------------|--------------|
| 0xF5AD096 | "Debug/ImGui" | 0x6664ae9 (lea rax) | 0x675E440 (sub_675e440) |
| 0xF539A95 | "UI/Blit" | 0x6664d8f (lea rax) | 0x675E440 (sub_675e440) |

## Running [reg+off] Write Table (Non-Stack, Output Descriptions/Records)

| Offset | Size | Source | Instruction (RVA) | Meaning | Tag |
|--------|------|--------|-------------------|---------|-----|
| [rbp+0x520] | 8 | r9 (arg2+0x0) | 0x6664aab | UIImGui: desc base pointer (source object) | [V] |
| [rbp+0x520] | 8 | r9 | 0x6664d51 | UI/Blit: desc base pointer | [V] |
| [rbp+0x400] | 8 | string RVA | 0x6664af0 | "Debug/ImGui" string pointer | [V] |
| [rbp+0x408] | 8 | 0xB | 0x6664af7 | "Debug/ImGui" length | [V] |
| [rbp+0x400] | 8 | string RVA | 0x6664d96 | "UI/Blit" string pointer | [V] |
| [rbp+0x408] | 8 | 7 | 0x6664d9d | "UI/Blit" length | [V] |
| [rbp+0x4D0] | 8 | call result | 0x6664b2d | Pass object from sub_675e440 (Debug/ImGui) | [V] |
| [rbp+0x390] | 8 | call result | 0x6664dd3 | Pass object from sub_675e440 (UI/Blit) | [V] |
| [rbp+0x520] | 1 | cl | 0x6664c44 | Byte from [r9+0x82] | [V] |
| [rbp+0x518] | 1 | r12b | 0x6664c4a | Byte from [r9+0x83] | [V] |
| [rbp+0x510] | 1 | dil | 0x6664c51 | Byte from [r9+0x80] | [V] |
| [rbp+0x224] | 1 | 0 | 0x6664c0e | Zero init | [V] |
| [rbp+0x400] | 16 | xmm1 (zero) | 0x6664c61 | Zero xmm | [V] |
| [rbp+0x1E0] | 16 | [0xEF40DE0] | 0x6664c97 | Constant xmm load | [V] |
| [rbp+0x400] | 16 | xmm0 (zero) | 0x6664ca9 | Zero xmm | [V] |
| [rbp+0x400] | 16 | xmm1 (zero) | 0x6664e85 | Zero xmm (alt path) | [V] |
| [rbp+0x400] | 8 | r12 | 0x6664e9b | [r9+0x28] (alt path) | [V] |
| [rbp+0x408] | 8 | r15 | 0x6664ea2 | [r9+0x30] refcounted (alt path) | [V] |
| [rbp+0x1E0] | 16 | xmm0 (zero) | 0x6664fcf | Zero xmm (UI/Blit destroy) | [V] |
| [rbp+0xE0] | 8 | rax | 0x66650a8 | [[rbp+0x1E0]+0x18] | [V] |
| [rbp+0x160] | 8 | rbx | 0x66650c6 | Save rbx | [V] |
| [rbp+0x258] | 8 | 0 | 0x6665040 | Zero init | [V] |
| [rbp+0x400] | 2 | ax | 0x666516c | Computed element index | [V] |
| [rbp+0x402] | 1 | 1 | 0x6665173 | Flag | [V] |
| [rbp+0x1EC] | 1 | 0 | 0x666517a | Flag | [V] |
| [rbp+0x1E0] | 16 | [r8+0x28] broadcast | 0x66651b8 | Float from source+0x28 | [V] |
| [rbp+0x400] | 8 | 1 | 0x66651bf | Constant 1 | [V] |
| [rbp+0x408] | 8 | rsi | 0x66651ca | Save rsi | [V] |

---

## Verification
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-I5a2.md` after each chunk.

## TOOL REQUESTS
None.

---

## Step 2 Complete: Instruction-complete listing of 0x6664a00 (next 500 instructions: 0x6665354..0x6665d6e, 14 phases)
Next chunk: continue from 0x6665d6e.

### Phase 14: Matrix Write Loop - First Variant (0x6665354..0x666543e, 40 ins)
```
0x6665354  nop [rax+rax]                                 
0x6665360  movss xmm0,[rbp+0x1E0]                        
0x6665368  movss [rdx],xmm0                              ; W a1+0x0
0x666536c  movss xmm0,[rbp+0x1E4]                        
0x6665374  movss [rdx+4],xmm0                            ; W a1+0x4
0x6665379  movss xmm0,[rbp+0x1E8]                        
0x6665381  movss [rdx+8],xmm0                            ; W a1+0x8
0x6665386  movss xmm0,[rbp+0x1EC]                        
0x666538e  movss [rdx+0xC],xmm0                          ; W a1+0xC
0x6665393  movss xmm0,[rbp+0x1F0]                        
0x666539b  movss [rdx+0x10],xmm0                         ; W a1+0x10
0x66653a0  movss xmm0,[rbp+0x1F4]                        
0x66653a8  movss [rdx+0x14],xmm0                         ; W a1+0x14
0x66653ad  movss xmm0,[rbp+0x1F8]                        
0x66653b5  movss [rdx+0x18],xmm0                         ; W a1+0x18
0x66653ba  movss xmm0,[rbp+0x1FC]                        
0x66653c2  movss [rdx+0x1C],xmm0                         ; W a1+0x1C
0x66653c7  movss xmm0,[rbp+0x200]                        
0x66653cf  movss [rdx+0x20],xmm0                         ; W a1+0x20
0x66653d4  movss xmm0,[rbp+0x204]                        
0x66653dc  movss [rdx+0x24],xmm0                         ; W a1+0x24
0x66653e1  movss xmm0,[rbp+0x208]                        
0x66653e9  movss [rdx+0x28],xmm0                         ; W a1+0x28
0x66653ee  movss xmm0,[rbp+0x20C]                        
0x66653f6  movss [rdx+0x2C],xmm0                         ; W a1+0x2C
0x66653fb  movss xmm0,[rbp+0x210]                        
0x6665403  movss [rdx+0x30],xmm0                         ; W a1+0x30
0x6665408  movss xmm0,[rbp+0x214]                        
0x6665410  movss [rdx+0x34],xmm0                         ; W a1+0x34
0x6665415  movss xmm0,[rbp+0x218]                        
0x666541d  movss [rdx+0x38],xmm0                         ; W a1+0x38
0x6665422  movss xmm0,[rbp+0x21C]                        
0x666542a  movss [rdx+0x3C],xmm0                         ; W a1+0x3C
0x666542f  add qword ptr [rbp+0x198],0x40                
0x6665437  add r15,0xC                                   
0x666543b  cmp r15,rsi                                   
0x666543e  je 0x66654F4                                  ; -> loc_66654f4
```
Purpose: Writes 16 consecutive floats (4x4 matrix) from stack [rbp+0x1E0..0x21C] to output buffer at rdx (arg1), advancing rdx by 0x40 per iteration (tracked via [rbp+0x198]). r15 is a source pointer advanced by 0xC (3 floats) per iteration. Loop exits when r15 == rsi (end pointer). This is the first variant of a matrix/vertex write loop.

### Phase 15: Matrix Write Loop - Second Variant / Per-Iteration Compute (0x6665444..0x66654f4, 40 ins)
```
0x6665444  mov dword ptr [rbp+0x400],0x3F800000          
0x666544e  movups [rbx],xmm6                             
0x6665451  mov dword ptr [rbp+0x414],0x3F800000          
0x666545b  movups [rbx+0x14],xmm6                        
0x666545f  movsd xmm0,[r15]                              
0x6665464  movaps xmm1,xmm0                              
0x6665467  mulps xmm1,xmm6                               
0x666546a  movaps xmm2,xmm1                              
0x666546d  shufps xmm2,xmm1,0xE1                         
0x6665471  addps xmm2,xmm0                               
0x6665474  movss xmm0,[r15+8]                            
0x666547a  shufps xmm0,xmm0,0                            
0x666547e  mulps xmm0,xmm7                               
0x6665481  movaps xmm3,xmm1                              
0x6665484  shufps xmm3,xmm1,0x55                         
0x6665488  unpcklps xmm1,xmm1                            
0x666548b  addps xmm1,xmm3                               
0x666548e  addps xmm1,xmm0                               
0x6665491  addps xmm1,xmm8                               
0x6665495  shufps xmm0,xmm0,0x55                         
0x6665499  addps xmm0,xmm2                               
0x666549c  movaps xmm2,xmm9                              
0x66654a0  movlhps xmm2,xmm0                             
0x66654a3  addps xmm2,xmm7                               
0x66654a6  movups [rbp+0x428],xmm2                       
0x66654ad  movlps [rbp+0x438],xmm1                       
0x66654b4  mov rcx,r12                                   
0x66654b7  mov rdx,rdi                                   
0x66654ba  mov r8,r13                                    
0x66654bd  call 0xAA6580                                 ; -> sub_aa6580
0x66654c2  nop                                           
0x66654c3  mov rdx,[rbp+0x198]                           
0x66654ca  cmp rdx,[rbp+0x1A0]                           
0x66654d1  jne 0x6665360                                 ; -> loc_6665360
0x66654d7  lea rcx,[rbp+0x190]                           
0x66654de  mov r8,r12                                    
0x66654e1  call 0x4E69370                                ; -> sub_4e69370
0x66654e6  nop                                           
0x66654e7  add r15,0xC                                   
0x66654eb  cmp r15,rsi                                   
0x66654ee  jne 0x6665444                                 ; -> loc_6665444
```
Purpose: Alternate loop body (entered when r15 != rsi at Phase 14 exit). Sets up constants 1.0 (0x3F800000) at [rbp+0x400] and [rbp+0x414], stores xmm6 to [rbx] and [rbx+0x14]. Complex SIMD computation on data at [r15] (3 floats: xmm0=[r15], [r15+8]) using constants xmm6, xmm7, xmm8, xmm9. Results stored to [rbp+0x428] and [rbp+0x438]. Calls sub_aa6580 with (rcx=r12, rdx=rdi, r8=r13). Checks [rbp+0x198] vs [rbp+0x1A0]; if not equal, jumps back to Phase 14 (loc_6665360). Calls sub_4e69370 with (rcx=&[rbp+0x190], r8=r12). Loop continues while r15 != rsi.

### Phase 16: Loop Exit - State Capture & Refcount Setup (0x66654f4..0x666556c, 40 ins)
```
0x66654f4  mov rcx,[rbp+0x518]                           
0x66654fb  movzx r12d,byte ptr [rcx+0x1D4]               
0x6665503  mov r15d,[rcx+0x1D0]                          
0x666550a  mov r13,[rbp+0x1D8]                           
0x6665511  mov ebx,[r13+0x3B0]                           
0x6665518  inc ebx                                       
0x666551a  mov [r13+0x3B0],bx                            
0x6665522  mov rax,[rbp+0x1A0]                           
0x6665529  mov qword ptr [rbp+0x1A0],0                   
0x6665534  movaps xmm0,[rbp+0x190]                       
0x666553b  xorps xmm1,xmm1                               
0x666553e  movaps [rbp+0x190],xmm1                       
0x6665545  movaps [rbp+0x3A0],xmm0                       
0x666554c  mov [rbp+0x3B0],rax                           
0x6665553  mov byte ptr [rbp+0x3E0],1                    
0x666555a  mov rax,[rbp+0x520]                           
0x6665561  movzx esi,word ptr [rax+0x48]                 
0x6665565  movaps [rbp+0x4D0],xmm1                       
0x666556c  mov rax,[rcx+0x1B0]                           
```
Purpose: After matrix loop exits (r15==rsi). Loads rcx=[rbp+0x518] (saved rsi from Phase 8, which is the source object). Reads byte at [rcx+0x1D4] -> r12b, dword at [rcx+0x1D0] -> r15d. Loads r13=[rbp+0x1D8] (saved r13 from Phase 8). Increments word at [r13+0x3B0] (counter). Saves [rbp+0x1A0] to [rbp+0x3B0], zeros [rbp+0x1A0]. Moves xmm from [rbp+0x190] to [rbp+0x3A0], zeros [rbp+0x190]. Sets flag [rbp+0x3E0]=1. **Rebinds rax=[rbp+0x520] (desc base)**, reads word at [rax+0x48] -> esi (this is desc+0x48, per oc_U-D8b-imgui2.md first use unknown). Zeros [rbp+0x4D0]. Loads rax=[rcx+0x1B0] (source object +0x1B0).

### Phase 17: Resource Refcount Management (Source Object +0x1B0/+0x1B8) (0x6665573..0x66655e3, 40 ins)
```
0x6665573  test rax,rax                                  
0x6665576  je short 0x666557C                            ; -> loc_666557c
0x6665578  movzx eax,word ptr [rax+0x10]                 
0x666557c  mov rax,[rcx+0x1B8]                           
0x6665583  test rax,rax                                  
0x6665586  je short 0x6665595                            ; -> loc_6665595
0x6665588  lock inc dword ptr [rax+8]                    
0x666558c  mov rax,[rcx+0x1B8]                           
0x6665593  jmp short 0x6665597                           ; -> loc_6665597
0x6665595  xor eax,eax                                   
0x6665597  mov rcx,[rcx+0x1B0]                           
0x666559e  mov [rbp+0x4D0],rcx                           
0x66655a5  mov rdi,[rbp+0x4D8]                           
0x66655ac  mov [rbp+0x4D8],rax                           
0x66655b3  test rdi,rdi                                  
0x66655b6  je short 0x66655E3                            ; -> loc_66655e3
0x66655b8  lock dec dword ptr [rdi+8]                    
0x66655bc  jne short 0x66655E3                           ; -> loc_66655e3
0x66655be  mov rax,[rdi]                                 
0x66655c1  mov rax,[rax]                                 
0x66655c4  mov rcx,rdi                                   
0x66655c7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66655cd  lock dec dword ptr [rdi+0xC]                  
0x66655d1  jne short 0x66655E3                           ; -> loc_66655e3
0x66655d3  mov rax,[rdi]                                 
0x66655d6  mov rax,[rax+8]                               
0x66655da  mov rcx,rdi                                   
0x66655dd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
Purpose: Standard shared_ptr refcount dance for two resources at source+0x1B0 and source+0x1B8. If [rcx+0x1B0] non-null, reads word at +0x10. For [rcx+0x1B8]: if non-null, increments refcount at +8, saves to [rbp+0x4D0]. Swaps [rbp+0x4D8] with rax (new resource). If old rdi non-null, decrements refcounts and calls sub_eea6040 (vtable slots 0 and 1) for destruction.

### Phase 18: Call sub_66a0f60 & sub_e869ff0 (0x66655e3..0x6665659, 40 ins)
```
0x66655e3  xor eax,eax                                   
0x66655e5  test r12b,r12b                                
0x66655e8  cmovne eax,r15d                               
0x66655ec  mov r8,[r13+0x3B8]                            
0x66655f3  mov rdx,[r14]                                 
0x66655f6  mov [rsp+0x20],eax                            
0x66655fa  mov dword ptr [rsp+0x30],0                    
0x6665602  mov dword ptr [rsp+0x28],0                    
0x666560a  lea rcx,[rbp+0x50]                            
0x666560e  lea r9,[rbp+0x4D0]                            
0x6665615  call 0x66A0F60                                ; -> sub_66a0f60
0x666561a  nop                                           
0x666561b  mov rax,[rbp+0xE0]                            
0x6665622  mov [rbp+0x1E0],rax                           
0x6665629  lea rdi,[rbp+0x1E8]                           
0x6665630  mov rcx,rdi                                   
0x6665633  lea rdx,[rbp+0xE8]                            
0x666563a  call 0xE869FF0                                ; -> sub_e869ff0
0x666563f  nop                                           
0x6665640  mov rax,[rbp+0x160]                           
0x6665647  mov [rbp+0x260],rax                           
0x666564e  mov qword ptr [rbp+0x160],0                   
0x6665659  mov dword ptr [rbp+0x278],3                   
```
Purpose: Conditional mov: if r12b (byte from source+0x1D4) != 0, eax=r15d (dword from source+0x1D0). Sets up call to sub_66a0f60 with rcx=&[rbp+0x50], r8=[r13+0x3B8], rdx=[r14], r9=&[rbp+0x4D0], stack args (eax, 0, 0). Then calls sub_e869ff0 with rcx=&[rbp+0x1E8], rdx=&[rbp+0xE8]. Saves [rbp+0x160] to [rbp+0x260], zeros [rbp+0x160]. Sets [rbp+0x278]=3.

### Phase 19: Large Structure Initialization (0x6665659..0x666571d, 40 ins)
```
0x6665659  mov dword ptr [rbp+0x278],3                   
0x6665663  mov byte ptr [rbp+0x27C],7                    
0x666566a  mov dword ptr [rbp+0x280],1                   
0x6665674  mov word ptr [rbp+0x284],0                    
0x666567d  mov byte ptr [rbp+0x286],2                    
0x6665684  mov dword ptr [rbp+0x288],0                   
0x666568e  mov byte ptr [rbp+0x28C],0                    
0x6665695  xorps xmm0,xmm0                               
0x6665698  movups [rbp+0x290],xmm0                       
0x666569f  movups [rbp+0x29C],xmm0                       
0x66656a6  mov byte ptr [rbp+0x2AC],8                    
0x66656ad  mov qword ptr [rbp+0x2B0],0                   
0x66656b8  mov dword ptr [rbp+0x2B8],0                   
0x66656c2  mov byte ptr [rbp+0x2BC],8                    
0x66656c9  mov qword ptr [rbp+0x2C0],0                   
0x66656d4  mov dword ptr [rbp+0x2C8],0                   
0x66656de  mov word ptr [rbp+0x2CC],1                    
0x66656e7  mov byte ptr [rbp+0x2CE],0xF0                 
0x66656ee  mov [rbp+0x2D0],bx                            
0x66656f5  mov dword ptr [rbp+0x2D8],0                   
0x66656ff  mov byte ptr [rbp+0x320],0xFF                 
0x6665706  movzx eax,byte ptr [rbp+0x3E0]                
0x666570d  movzx ecx,al                                  
0x6665710  cmp ecx,1                                     
0x6665713  jg short 0x666575A                            ; -> loc_666575a
0x6665715  test ecx,ecx                                  
0x6665717  jne 0x6665C09                                 ; -> loc_6665c09
0x666571d  movaps xmm0,[rbp+0x3A0]                       
0x6665724  movaps xmm1,[rbp+0x3B0]                       
0x666572b  movaps xmm2,[rbp+0x3C0]                       
0x6665732  movaps xmm3,[rbp+0x3D0]                       
0x6665739  movups [rbp+0x2E0],xmm0                       
0x6665740  movups [rbp+0x2F0],xmm1                       
0x6665747  movups [rbp+0x300],xmm2                       
0x666574e  movups [rbp+0x310],xmm3                       
0x6665755  jmp 0x6665C3A                                 ; -> loc_6665c3a
```
Purpose: Initializes a large structure at [rbp+0x278..0x320] (likely a draw/batch descriptor). Sets fields: +0x278=3, +0x27C=7, +0x280=1, +0x284=0, +0x286=2, +0x288=0, +0x28C=0, +0x290..0x2AC=zero, +0x2AC=8, +0x2B0=0, +0x2B8=0, +0x2BC=8, +0x2C0=0, +0x2C8=0, +0x2CC=1, +0x2CE=0xF0, +0x2D0=bx (counter from [r13+0x3B0]), +0x2D8=0, +0x320=0xFF. Then branches on [rbp+0x3E0] (flag set to 1 in Phase 16): if 0 -> loc_6665c09; if 1 -> copies matrix from [rbp+0x3A0..0x3D0] to [rbp+0x2E0..0x310], jumps to loc_6665c3a; if >1 -> loc_666575a.

### Phase 20: Flag=2 Path - Matrix Copy Variant (0x666575a..0x6665776, 10 ins)
```
0x666575a  cmp ecx,2                                     
0x666575d  jne 0x6665C40                                 ; -> loc_6665c40
0x6665763  mov rcx,[rbp+0x3A0]                           
0x666576a  mov [rbp+0x2E0],rcx                           
0x6665771  jmp 0x6665C3A                                 ; -> loc_6665c3a
```
Purpose: If flag == 2, copies only first qword of matrix ([rbp+0x3A0] -> [rbp+0x2E0]), jumps to loc_6665c3a. If flag > 2, jumps to loc_6665c40.

### Phase 21: Data Packing Loop (0x6665776..0x666581e, 40 ins)
```
0x6665776  shr rdx,2                                     
0x666577a  inc rdx                                       
0x666577d  mov rax,rdx                                   
0x6665780  and rax,0xFFFFFFFFFFFFFFFE                    
0x6665784  xor ecx,ecx                                   
0x6665786  nop [rax+rax]                                 
0x6665790  lea rcx,[rcx+rcx*2]                           
0x6665794  movzx r10d,word ptr [r9+4]                    
0x6665799  mov [rbp+rcx*2+0x1E4],r10w                    
0x66657a2  mov r10d,[r9]                                 
0x66657a5  mov [rbp+rcx*2+0x1E0],r10d                    
0x66657ad  mov rcx,[rbp+0x258]                           
0x66657b4  inc rcx                                       
0x66657b7  mov [rbp+0x258],rcx                           
0x66657be  lea rcx,[rcx+rcx*2]                           
0x66657c2  movzx r10d,word ptr [r9+0xA]                  
0x66657c7  mov [rbp+rcx*2+0x1E4],r10w                    
0x66657d0  mov r10d,[r9+6]                               
0x66657d4  mov [rbp+rcx*2+0x1E0],r10d                    
0x66657dc  mov rcx,[rbp+0x258]                           
0x66657e3  inc rcx                                       
0x66657e6  mov [rbp+0x258],rcx                           
0x66657ed  add r9,0xC                                    
0x66657f1  add rax,0xFFFFFFFFFFFFFFFE                    
0x66657f5  jne short 0x6665790                           ; -> loc_6665790
0x66657f7  test dl,1                                     
0x66657fa  je short 0x666581E                            ; -> loc_666581e
0x66657fc  lea rax,[rcx+rcx*2]                           
0x6665800  movzx ecx,word ptr [r9+4]                     
0x6665805  mov [rbp+rax*2+0x1E4],cx                      
0x666580d  mov ecx,[r9]                                  
0x6665810  mov [rbp+rax*2+0x1E0],ecx                     
0x6665817  inc qword ptr [rbp+0x258]                     
```
Purpose: Packing loop processing data at r9 (source pointer). rdx = count (from earlier computation). Loop processes pairs of elements: each iteration reads word at [r9+4] and dword at [r9] -> stores to [rbp+0x1E0] and [rbp+0x1E4] at index rcx*2 (interleaved). Then reads word at [r9+0xA] and dword at [r9+6] -> next index. Advances r9 by 0xC (12 bytes = 3 dwords) per 2 output elements. Counter at [rbp+0x258] tracks output count. Handles odd count via test dl,1.

### Phase 22: Allocation & Memcpy for Large Buffer (0x666581e..0x6665922, 40 ins)
```
0x666581e  mov [rbp+0x260],r8w                           
0x6665826  mov rax,r12                                   
0x6665829  shr rax,0x20                                  
0x666582d  jne 0x6668385                                 ; -> sub_6668385
0x6665833  mov [rbp+0x268],r12d                          
0x666583a  mov rax,[rbp+0x520]                           
0x6665841  mov rdi,[rax+0x10]                            
0x6665845  xorps xmm0,xmm0                               
0x6665848  movups [rbp+0x270],xmm0                       
0x666584f  mov qword ptr [rbp+0x280],0                   
0x666585a  test r15,r15                                  
0x666585d  mov [rbp+0x508],r12                           
0x6665864  je 0x6665922                                  ; -> loc_6665922
0x666586a  mov [rbp+0x518],rbx                           
0x6665871  js 0x666844F                                  ; -> sub_666844f
0x6665877  mov rbx,r13                                   
0x666587a  cmp r15,0x1000                                
0x6665881  jb short 0x66658C0                            ; -> loc_66658c0
0x6665883  lea r13,[r15+0x27]                            
0x6665887  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x666588e  mov rax,[rcx]                                 
0x6665891  mov rax,[rax+8]                               
0x6665895  mov rdx,r13                                   
0x6665898  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666589e  nop                                           
0x666589f  mov r12,rax                                   
0x66658a2  test rax,rax                                  
0x66658a5  je 0x6668197                                  ; -> sub_6668197
0x66658ab  mov r13,r14                                   
0x66658ae  mov rax,r12                                   
0x66658b1  add r12,0x27                                  
0x66658b5  and r12,0xFFFFFFFFFFFFFFE0                    
0x66658b9  mov [r12-8],rax                               
0x66658be  jmp short 0x66658E7                           ; -> loc_66658e7
```
Purpose: Saves r8w to [rbp+0x260]. Checks r12 high dword == 0 (error to 0x6668385 if not). Saves r12d to [rbp+0x268]. **Rebinds rax=[rbp+0x520] (desc)**, loads rdi=[rax+0x10] (desc+0x10 = copySrcA per oc_U-D8b-imgui2.md). Zeros [rbp+0x270], [rbp+0x280]. If r15 (size) == 0, jumps to loc_6665922. If r15 negative, error to 0x666844f. For r15 >= 0x1000: allocates via sub_eea6040 (allocator at 0x1233E1A8) with size r15+0x27 aligned to 0x20, stores original pointer at [r12-8]. For r15 < 0x1000: similar alloc at 0x66658c0..0x66658e1. Then memcpy via sub_eec6de0 (dst=r12, src=rdi, count=r15). Updates pointers.

### Phase 23: Conditional Transaction Object Creation (0x6665922..0x6665af2, 40 ins)
```
0x6665922  cmp byte ptr [rbx+0x9C8],0                    
0x6665929  je 0x66659E4                                  ; -> loc_66659e4
0x666592f  mov qword ptr [rbp+0x408],0                   
0x666593a  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6665941  mov rax,[rcx]                                 
0x6665944  mov rax,[rax+8]                               
0x6665948  mov edx,0x20                                  
0x666594d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665953  nop                                           
0x6665954  mov rdi,rax                                   
0x6665957  test rax,rax                                  
0x666595a  je 0x6668107                                  ; -> sub_6668107
0x6665960  mov [rbp+0x400],rdi                           
0x6665967  mov qword ptr [rbp+0x410],0x13                
0x6665972  mov qword ptr [rbp+0x418],0x1F                
0x666597d  mov eax,[0xF58B3C5]                           ; [data_f58b3c5] "tion"
0x6665983  mov [rdi+0xF],eax                             
0x6665986  movups xmm0,[0xF58B3B6]                       ; [data_f58b3b6] "Unnamed Transaction"
0x666598d  movups [rdi],xmm0                             
0x6665990  mov byte ptr [rdi+0x13],0                     
0x6665994  lea rcx,[0x123BB1D8]                          ; [data_123bb1d8]
0x666599b  lea rdx,[0x1287EBE0]                          ; [data_1287ebe0]
0x66659a2  call 0xEEC6E70                                ; -> sub_eec6e70
0x66659a7  mov rdi,rax                                   
0x66659aa  xorps xmm0,xmm0                               
0x66659ad  movaps [rbp+0x3A0],xmm0                       
0x66659b4  mov rcx,rax                                   
0x66659b7  call 0xEEC7570                                ; -> sub_eec7570
0x66659bc  test rax,rax                                  
0x66659bf  js 0x666845B                                  ; -> sub_666845b
0x66659c5  mov rbx,rax                                   
0x66659c8  cmp rax,0x10                                  
0x66659cc  jae 0x6665BAA                                 ; -> loc_6665baa
0x66659d2  lea r15,[rbp+0x3A0]                           
0x66659d9  mov r12d,0xF                                  
0x66659df  jmp 0x6665D0B                                 ; -> loc_6665d0b
```
Purpose: If byte at [rbx+0x9C8] != 0 (rbx = saved r13 from Phase 16, which is the FrameBuilder or context object), creates a transaction object. Allocates 0x20 bytes via sub_eea6040. Writes "Unnamed Transaction" string (16 bytes from 0xF58B3B6) + "tion" (4 bytes from 0xF58B3C5) to the object. Sets fields at +0x10=0x13, +0x18=0x1F, +0x13=0. Calls sub_eec6e70 (transaction init?) with globals 0x123BB1D8, 0x1287EBE0. Calls sub_eec7570. If result >= 0x10, jumps to loc_6665baa; else sets up small buffer at [rbp+0x3A0] with size 0xF, jumps to loc_6665d0b.

### Phase 24: Alternate Transaction Path (No [rbx+0x9C8]) (0x66659e4..0x6665af2, 40 ins)
```
0x66659e4  xorps xmm0,xmm0                               
0x66659e7  movaps [rbp+0xE0],xmm0                        
0x66659ee  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x66659f5  mov rax,[rcx]                                 
0x66659f8  mov rax,[rax+8]                               
0x66659fc  mov edx,0x30                                  
0x6665a01  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665a07  nop                                           
0x6665a08  mov rdi,rax                                   
0x6665a0b  test rax,rax                                  
0x6665a0e  je 0x6668127                                  ; -> sub_6668127
0x6665a14  mov rax,0x100000001                           
0x6665a1e  mov [rdi+8],rax                               
0x6665a22  lea rax,[0xF0F9C30]                           ; [data_f0f9c30]
0x6665a29  mov [rdi],rax                                 
0x6665a2c  mov rax,rdi                                   
0x6665a2f  add rax,0x10                                  
0x6665a33  mov [rbp+0x510],rax                           
0x6665a3a  xorps xmm0,xmm0                               
0x6665a3d  movups [rdi+0x10],xmm0                        
0x6665a41  mov [rbp+0x518],rdi                           
0x6665a48  mov byte ptr [rdi+0x20],0                     
0x6665a4c  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6665a53  mov rax,[rcx]                                 
0x6665a56  mov rax,[rax+8]                               
0x6665a5a  mov edx,0x70                                  
0x6665a5f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665a65  nop                                           
0x6665a66  mov rdi,rax                                   
0x6665a69  test rax,rax                                  
0x6665a6c  je 0x6668137                                  ; -> sub_6668137
0x6665a72  xorps xmm0,xmm0                               
0x6665a75  movaps [rdi],xmm0                             
0x6665a78  movaps [rdi+0x60],xmm0                        
0x6665a7c  movaps [rdi+0x50],xmm0                        
0x6665a80  movaps [rdi+0x40],xmm0                        
0x6665a84  movaps [rdi+0x30],xmm0                        
0x6665a88  movaps [rdi+0x20],xmm0                        
0x6665a8c  movaps [rdi+0x10],xmm0                        
0x6665a90  mov word ptr [rdi],0xFFFF                     
0x6665a95  mov word ptr [rdi+0xC],0xFFFF                 
0x6665a9b  mov rax,[rbp+0x518]                           
0x6665aa2  mov [rax+0x28],rdi                            
0x6665aad  mov [rbp+0xE0],rcx                            
0x6665ab4  mov rdi,[rbp+0xE8]                            
0x6665abb  mov [rbp+0xE8],rax                            
0x6665ac2  test rdi,rdi                                  
0x6665ac5  je short 0x6665AF2                            ; -> loc_6665af2
0x6665ac7  lock dec dword ptr [rdi+8]                    
0x6665acb  jne short 0x6665AF2                           ; -> loc_6665af2
0x6665acd  mov rax,[rdi]                                 
0x6665ad0  mov rax,[rax]                                 
0x6665ad3  mov rcx,rdi                                   
0x6665ad6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665adc  lock dec dword ptr [rdi+0xC]                  
0x6665ae0  jne short 0x6665AF2                           ; -> loc_6665af2
0x6665ae2  mov rax,[rdi]                                 
0x6665ae5  mov rax,[rax+8]                               
0x6665ae9  mov rcx,rdi                                   
0x6665aec  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
Purpose: Alternate path when [rbx+0x9C8] == 0. Allocates 0x30 bytes via sub_eea6040, sets vtable to 0xF0F9C30, initializes fields. Allocates second object 0x70 bytes, zeroes it, sets words at +0 and +0xC to 0xFFFF. Links first object's +0x28 to second. Stores pointer at [rbp+0xE0]. Cleans up old resource at [rbp+0xE8] via shared_ptr destruction.

### Phase 25: More Allocations & Large Buffer Path (0x6665af2..0x6665baa, 40 ins)
```
0x6665af2  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6665af9  mov rax,[rcx]                                 
0x6665afc  mov rax,[rax+8]                               
0x6665b00  mov edx,0x128                                 
0x6665b05  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665b0b  nop                                           
0x6665b0c  mov rdi,rax                                   
0x6665b0f  test rax,rax                                  
0x6665b12  je 0x6668147                                  ; -> sub_6668147
0x6665b18  mov [rbp+0x518],rdi                           
0x6665b1f  mov qword ptr [rbp+0x408],0                   
0x6665b2a  lea rax,[0xF2BEE70]                           ; [data_f2bee70]
0x6665b31  mov [rbp+0x400],rax                           
0x6665b38  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6665b3f  mov rax,[rcx]                                 
0x6665b42  mov rax,[rax+8]                               
0x6665b46  mov edx,0xA8                                  
0x6665b4b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665b51  nop                                           
0x6665b52  mov rdi,rax                                   
0x6665b55  test rax,rax                                  
0x6665b58  je 0x6668157                                  ; -> sub_6668157
0x6665b5e  mov qword ptr [rdi+0x78],0                    
0x6665b66  mov rax,[rbp+0x258]                           
0x6665b6d  test rax,rax                                  
0x6665b70  mov r15,[rbp+0x518]                           
0x6665b77  je 0x6666061                                  ; -> loc_6666061
0x6665b7d  lea rax,[rax+rax*2]                           
0x6665b81  lea rcx,[rax*2-6]                             
0x6665b89  mov rdx,0xAAAAAAAAAAAAAAAB                    
0x6665b93  mov rax,rcx                                   
0x6665b96  mul rdx                                       
0x6665b99  cmp rcx,6                                     
0x6665b9d  jae 0x6665FE2                                 ; -> loc_6665fe2
0x6665ba3  xor ecx,ecx                                   
0x6665ba5  jmp 0x666604B                                 ; -> loc_666604b
```
Purpose: Allocates 0x128 bytes (vtable 0xF2BEE70) -> [rbp+0x518]. Allocates 0xA8 bytes, sets [rdi+0x78]=0. Uses [rbp+0x258] (packed count from Phase 21) to compute allocation size: rax*3*2-6 = rax*6-6, divide by 3 via magic constant. If count >= 6, jumps to loc_6665fe2; else zero ecx, jump to loc_666604b.

### Phase 26: Large Transaction Buffer Handling (0x6665baa..0x6665d0b, 40 ins)
```
0x6665baa  mov rdx,rbx                                   
0x6665bad  or rdx,0xF                                    
0x6665bb1  cmp rdx,0x17                                  
0x6665bb5  mov r12d,0x16                                 
0x6665bbb  cmovae r12,rdx                                
0x6665bbf  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6665bc6  mov rax,[rcx]                                 
0x6665bc9  mov rax,[rax+8]                               
0x6665bcd  cmp rdx,0xFFF                                 
0x6665bd4  jb 0x6665CE9                                  ; -> loc_6665ce9
0x6665bda  lea rsi,[r12+0x28]                            
0x6665bdf  mov rdx,rsi                                   
0x6665be2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665be8  nop                                           
0x6665be9  mov r15,rax                                   
0x6665bec  test rax,rax                                  
0x6665bef  je 0x66681D5                                  ; -> sub_66681d5
0x6665bf5  mov rax,r15                                   
0x6665bf8  add r15,0x27                                  
0x6665bfc  and r15,0xFFFFFFFFFFFFFFE0                    
0x6665c00  mov [r15-8],rax                               
0x6665c04  jmp 0x6665D04                                 ; -> loc_6665d04
0x6665c09  mov rcx,[rbp+0x3B0]                           
0x6665c10  mov qword ptr [rbp+0x3B0],0                   
0x6665c1b  movaps xmm0,[rbp+0x3A0]                       
0x6665c22  xorps xmm1,xmm1                               
0x6665c25  movaps [rbp+0x3A0],xmm1                       
0x6665c2c  movups [rbp+0x2E0],xmm0                       
0x6665c33  mov [rbp+0x2F0],rcx                           

loc_6665c3a:  ; from 6665755, 6665771
0x6665c3a  mov [rbp+0x320],al                            

loc_6665c40:  ; from 666575d
0x6665c40  mov [rbp+0x328],si                            
0x6665c47  movaps xmm0,[rbp+0x50]                        
0x6665c4b  movaps xmm1,[rbp+0x60]                        
0x6665c4f  mov qword ptr [rbp+0x58],0                    
0x6665c57  movups [rbp+0x330],xmm0                       
0x6665c5e  xorps xmm0,xmm0                               
0x6665c61  movaps [rbp+0x60],xmm0                        
0x6665c65  movups [rbp+0x340],xmm1                       
0x6665c6c  mov rax,[rbp+0x70]                            
0x6665c70  mov [rbp+0x350],rax                           
0x6665c77  mov byte ptr [rbp+0x368],0xFF                 
0x6665c7e  movzx eax,byte ptr [rbp+0x88]                 
0x6665c85  cmp rax,3                                     
0x6665c89  ja 0x6667964                                  ; -> sub_6667964
0x6665c8f  lea rcx,[rbp+0x358]                           
0x6665c96  lea rdx,[0xF2BF48C]                           ; [data_f2bf48c]
0x6665c9d  movsxd r8,[rdx+rax*4]                         
0x6665ca1  add r8,rdx                                    
0x6665ca4  jmp r8                                        
```
Purpose: For large transaction (rbx >= 0x10): computes size = max(0x16, rbx|0xF). If size >= 0xFFF, allocates via sub_eea6040 with size+0x28 aligned. Jumps to loc_6665d04. Flag=0 path (loc_6665c09): moves matrix from [rbp+0x3A0] to [rbp+0x2E0], saves [rbp+0x3B0] to [rbp+0x2F0]. Flag>2 path (loc_6665c40): saves si to [rbp+0x328], copies xmm from [rbp+0x50]/[rbp+0x60] to [rbp+0x330]/[rbp+0x340], zeros [rbp+0x58]/[rbp+0x60], saves [rbp+0x70] to [rbp+0x350], sets [rbp+0x368]=0xFF. Then switch on byte [rbp+0x88] (0-3) via jump table at 0xF2BF48C.

### Phase 27: Jump Table Cases 0-3 & Refcount (0x6665ca7..0x6665d0b, 40 ins)
```
0x6665ca7  mov rcx,[rbp+0x78]                            
0x6665cab  mov [rbp+0x358],rcx                           
0x6665cb2  jmp 0x666795E                                 ; -> sub_666795e
0x6665cb7  lea rdx,[rbp+0x78]                            
0x6665cbb  movups xmm0,[rdx]                             
0x6665cbe  movups [rcx],xmm0                             
0x6665cc1  jmp 0x666795E                                 ; -> sub_666795e
0x6665cc6  movups [rcx],xmm0                             
0x6665cc9  mov rcx,[rbp+0x80]                            
0x6665cd0  test rcx,rcx                                  
0x6665cd3  je 0x666794A                                  ; -> sub_666794a
0x6665cd9  lock inc dword ptr [rcx+8]                    
0x6665cdd  mov rcx,[rbp+0x80]                            
0x6665ce4  jmp 0x666794C                                 ; -> sub_666794c
0x6665ce9  lea rsi,[r12+1]                               
0x6665cee  mov rdx,rsi                                   
0x6665cf1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6665cf7  nop                                           
0x6665cf8  mov r15,rax                                   
0x6665cfb  test rax,rax                                  
0x6665cfe  je 0x66681E3                                  ; -> sub_66681e3

loc_6665d04:  ; from 6665c04
0x6665d04  mov [rbp+0x3A0],r15                           

loc_6665d0b:  ; from 66659df
0x6665d0b  mov [rbp+0x3B0],rbx                           
0x6665d12  mov [rbp+0x3B8],r12                           
0x6665d19  mov rcx,r15                                   
0x6665d1c  mov rdx,rdi                                   
0x6665d1f  mov r8,rbx                                    
0x6665d22  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x6665d27  mov byte ptr [r15+rbx],0                      
0x6665d2c  xorps xmm0,xmm0                               
0x6665d2f  movaps [rbp+0x190],xmm0                       
0x6665d36  mov qword ptr [rbp+0x1A0],1                   
0x6665d41  mov qword ptr [rbp+0x1A8],0xF                 
0x6665d4c  mov byte ptr [rbp+0x190],0x3C                 
0x6665d53  lea rdi,[rbp+0x50]                            
0x6665d57  lea r8,[rbp+0x190]                            
0x6665d5e  lea r9,[rbp+0x3A0]                            
0x6665d65  mov rcx,rdi                                   
0x6665d68  call 0x11D1F0                                 ; -> sub_11d1f0
0x6665d6d  nop                                           
0x6665d6e  mov rax,[rbp+0x60]                            
```
Purpose: Jump table cases: case 0 (0x6665ca7): mov [rbp+0x78] -> [rbp+0x358], jump to sub_666795e. Case 1 (0x6665cb7): copy 16 bytes from [rbp+0x78] to rcx, jump to sub_666795e. Case 2 (0x6665cc6): movups xmm0 -> [rcx], jump to sub_666795e. Case 3 (0x6665cc9): if [rbp+0x80] null -> sub_666794a; else inc refcount, jump to sub_666794c. loc_6665ce9 (large alloc < 0xFFF): allocates r12+1 bytes via sub_eea6040. loc_6665d04: saves r15 to [rbp+0x3A0]. loc_6665d0b: saves rbx, r12 to [rbp+0x3B0], [rbp+0x3B8]. Calls sub_eec6ec0 (memcpy-like: dst=r15, src=rdi, count=rbx). Null-terminates at [r15+rbx]. Sets up [rbp+0x190] with 0x3C at byte 0, [rbp+0x1A0]=1, [rbp+0x1A8]=0xF. Calls sub_11d1f0 with rcx=&[rbp+0x50], r8=&[rbp+0x190], r9=&[rbp+0x3A0].

---

## Updated String Reference Table (Phase 0-27)

| String RVA | Text | Call Site RVA | Callee After |
|------------|------|---------------|--------------|
| 0xF5AD096 | "Debug/ImGui" | 0x6664ae9 (lea rax) | 0x675E440 (sub_675e440) |
| 0xF539A95 | "UI/Blit" | 0x6664d8f (lea rax) | 0x675E440 (sub_675e440) |
| 0xF58B3B6 | "Unnamed Transaction" | 0x6665986 (movups xmm0) | 0xEEC6E70 (sub_eec6e70) |
| 0xF58B3C5 | "tion" | 0x666597d (mov eax) | 0xEEC6E70 (sub_eec6e70) |

## Updated [reg+off] Write Table (Non-Stack, Output Descriptions/Records)

| Offset | Size | Source | Instruction (RVA) | Meaning | Tag |
|--------|------|--------|-------------------|---------|-----|
| [rdx+0x00..0x3C] | 16x4 | [rbp+0x1E0..0x21C] | 0x6665368..0x666542a | Matrix write (16 floats) to output buffer | [V] |
| [rbx+0x00] | 16 | xmm6 | 0x666544e | Constant xmm6 store | [V] |
| [rbx+0x14] | 16 | xmm6 | 0x666545b | Constant xmm6 store | [V] |
| [rbp+0x428] | 16 | xmm2 | 0x66654a6 | Computed SIMD result | [V] |
| [rbp+0x438] | 8 | xmm1 (low) | 0x66654ad | Computed SIMD result | [V] |
| [r13+0x3B0] | 2 | bx+1 | 0x666551a | Increment counter | [V] |
| [rbp+0x1A0] | 8 | 0 | 0x6665529 | Zero | [V] |
| [rbp+0x3A0] | 16 | [rbp+0x190] | 0x6665545 | Matrix save | [V] |
| [rbp+0x190] | 16 | 0 | 0x666553e | Zero | [V] |
| [rbp+0x3B0] | 8 | [rbp+0x1A0] | 0x666554c | Save previous | [V] |
| [rbp+0x3E0] | 1 | 1 | 0x6665553 | Flag = 1 | [V] |
| [rbp+0x4D0] | 16 | 0 | 0x6665565 | Zero | [V] |
| [rbp+0x4D0] | 8 | [rcx+0x1B8] | 0x666559e | Resource pointer | [V] |
| [rbp+0x4D8] | 8 | rax | 0x66655ac | Resource swap | [V] |
| [rbp+0x260] | 2 | r8w | 0x666581e | Save | [V] |
| [rbp+0x268] | 4 | r12d | 0x6665833 | Save | [V] |
| [rbp+0x270] | 16 | 0 | 0x6665848 | Zero | [V] |
| [rbp+0x280] | 8 | 0 | 0x666584f | Zero | [V] |
| [rbp+0x270] | 8 | r12 (alloc) | 0x66658e7 | Allocated buffer | [V] |
| [rbp+0x280] | 8 | r14 (end) | 0x66658f2 | Buffer end | [V] |
| [rbp+0x278] | 8 | r14 | 0x6665907 | Buffer end (dup) | [V] |
| [rbp+0x260] | 2 | r8w | 0x666581e | (dup) | [V] |
| [rdi+0x00..0x0F] | 16 | "Unnamed Transaction" | 0x666598d | Transaction name | [V] |
| [rdi+0x0F] | 4 | "tion" | 0x6665983 | Transaction name suffix | [V] |
| [rdi+0x10] | 8 | 0x13 | 0x6665967 | Transaction field | [V] |
| [rdi+0x18] | 8 | 0x1F | 0x6665972 | Transaction field | [V] |
| [rdi+0x13] | 1 | 0 | 0x6665990 | Transaction field | [V] |
| [rbp+0x3A0] | 16 | 0 | 0x66659ad | Zero | [V] |
| [rdi+0x08] | 8 | 0x100000001 | 0x6665a1e | Refcount init | [V] |
| [rdi+0x00] | 8 | 0xF0F9C30 | 0x6665a29 | Vtable pointer | [V] |
| [rdi+0x10..0x6F] | 96 | 0 | 0x6665a3d..0x6665a8c | Zero init | [V] |
| [rdi+0x00] | 2 | 0xFFFF | 0x6665a90 | Word init | [V] |
| [rdi+0x0C] | 2 | 0xFFFF | 0x6665a95 | Word init | [V] |
| [rax+0x28] | 8 | rdi | 0x6665aa2 | Link objects | [V] |
| [rbp+0xE0] | 8 | rcx | 0x6665ab4 | Save pointer | [V] |
| [rbp+0xE8] | 8 | rax | 0x6665abb | Swap | [V] |
| [rbp+0x518] | 8 | rdi (0x128 alloc) | 0x6665b18 | Large alloc | [V] |
| [rbp+0x400] | 8 | 0xF2BEE70 | 0x6665b31 | Vtable | [V] |
| [rbp+0x408] | 8 | 0 | 0x6665b1f | Zero | [V] |
| [rdi+0x78] | 8 | 0 | 0x6665b5e | Zero field | [V] |
| [rbp+0x3A0] | 8 | r15 | 0x6665d04 | Large alloc result | [V] |
| [rbp+0x3B0] | 8 | rbx | 0x6665d0b | Size | [V] |
| [rbp+0x3B8] | 8 | r12 | 0x6665d12 | Capacity | [V] |
| [r15+rbx] | 1 | 0 | 0x6665d27 | Null terminator | [V] |
| [rbp+0x190] | 16 | 0 | 0x6665d2f | Zero | [V] |
| [rbp+0x190] | 1 | 0x3C | 0x6665d4c | Byte init | [V] |
| [rbp+0x1A0] | 8 | 1 | 0x6665d36 | Init | [V] |
| [rbp+0x1A8] | 8 | 0xF | 0x6665d41 | Init | [V] |

---

## Verification
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-I5a2.md` after each chunk.

## TOOL REQUESTS
None.

---

## Step 3 Complete: Instruction-complete listing of 0x6664a00 (next 500 instructions: 0x6665d6e..0x6666696, 15 phases)
Next chunk: continue from 0x6666696.

### Phase 28: String Buffer Management & Formatting (0x6665d6e..0x6665eac, 40 ins)
```
0x6665d6e  mov rax,[rbp+0x60]                            
0x6665d72  mov rcx,[rbp+0x68]                            
0x6665d76  mov rdx,rcx                                   
0x6665d79  sub rdx,rax                                   
0x6665d7c  cmp rdx,2                                     
0x6665d80  mov r12,[rbp+0x508]                           
0x6665d87  jae short 0x6665DAD                           ; -> loc_6665dad
0x6665d89  mov qword ptr [rsp+0x20],2                    
0x6665d92  lea r9,[0xF8407B6]                            ; [data_f8407b6]
0x6665d99  lea rcx,[rbp+0x50]                            
0x6665d9d  mov edx,2                                     
0x6665da2  call 0xA0850                                  ; -> sub_a0850
0x6665da7  nop                                           
0x6665da8  mov rdi,rax                                   
0x6665dab  jmp short 0x6665DCD                           ; -> loc_6665dcd
0x6665dad  lea rdx,[rax+2]                               
0x6665db1  mov [rbp+0x60],rdx                            
0x6665db5  mov rdx,rdi                                   
0x6665db8  cmp rcx,0x10                                  
0x6665dbc  jb short 0x6665DC2                            ; -> loc_6665dc2
0x6665dbe  mov rdx,[rbp+0x50]                            
0x6665dc2  mov word ptr [rdx+rax],0x203E                 
0x6665dc8  mov byte ptr [rdx+rax+2],0                    
0x6665dcd  movups xmm0,[rdi]                             
0x6665dd0  movups xmm1,[rdi+0x10]                        
0x6665dd4  movaps [rbp+0xF0],xmm1                        
0x6665ddb  movaps [rbp+0xE0],xmm0                        
0x6665de2  mov qword ptr [rdi+0x10],0                    
0x6665dea  mov qword ptr [rdi+0x18],0xF                  
0x6665df2  mov byte ptr [rdi],0                          
0x6665df5  lea rcx,[rbp+0x4E0]                           
0x6665dfc  lea r8,[rbp+0xE0]                             
0x6665e03  lea r9,[rbp+0x400]                            
0x6665e0a  call 0x11D1F0                                 ; -> sub_11d1f0
0x6665e0f  nop                                           
0x6665e10  mov rax,[rbp+0xF8]                            
0x6665e17  cmp rax,0x10                                  
0x6665e1b  jb short 0x6665E55                            ; -> loc_6665e55
0x6665e1d  mov rcx,[rbp+0xE0]                            
0x6665e24  lea rdx,[rax+1]                               
0x6665e28  cmp rdx,0x1000                                
0x6665e2f  jb short 0x6665E50                            ; -> loc_6665e50
0x6665e31  mov r8,[rcx-8]                                
0x6665e35  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6665e39  sub rcx,r8                                    
0x6665e3c  cmp rcx,0x20                                  
0x6665e40  jae 0x6668219                                 ; -> sub_6668219
0x6665e46  add rax,0x28                                  
0x6665e4a  mov rdx,rax                                   
0x6665e4d  mov rcx,r8                                    
0x6665e50  call 0xE935700                                ; -> sub_e935700
```
Purpose: Manages a string buffer at [rbp+0x50] (capacity at [rbp+0x68], length at [rbp+0x60]). If remaining space < 2, calls sub_a0850 (string append/format) with format string at 0xF8407B6. Otherwise writes ">" (0x203E = '>' + ' '? Actually 0x3E='>', 0x20=' ') and null terminator directly. Saves xmm0/xmm1 from rdi to [rbp+0xE0]/[rbp+0xF0], resets rdi to empty string (len=0, cap=0xF). Calls sub_11d1f0 with rcx=&[rbp+0x4E0], r8=&[rbp+0xE0], r9=&[rbp+0x400]. Then standard string buffer cleanup pattern: if [rbp+0xF8] >= 0x10, checks if heap allocated (cap >= 0x1000), validates allocation header, calls sub_e935700 (deallocator). Else zeros [rbp+0xF0]/[rbp+0xF8]/[rbp+0xE0].

### Phase 29: Three More String Buffer Cleanups (0x6665e55..0x6665fdd, 40 ins)
```
0x6665e55  mov qword ptr [rbp+0xF0],0                    
0x6665e60  mov qword ptr [rbp+0xF8],0xF                  
0x6665e6b  mov byte ptr [rbp+0xE0],0                     
0x6665e72  mov rax,[rbp+0x68]                            
0x6665e76  cmp rax,0x10                                  
0x6665e7a  jb short 0x6665EB1                            ; -> loc_6665eb1
0x6665e7c  mov rcx,[rbp+0x50]                            
0x6665e80  lea rdx,[rax+1]                               
0x6665e84  cmp rdx,0x1000                                
0x6665e8b  jb short 0x6665EAC                            ; -> loc_6665eac
0x6665e8d  mov r8,[rcx-8]                                
0x6665e91  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6665e95  sub rcx,r8                                    
0x6665e98  cmp rcx,0x20                                  
0x6665e9c  jae 0x6668219                                 ; -> sub_6668219
0x6665ea2  add rax,0x28                                  
0x6665ea6  mov rdx,rax                                   
0x6665ea9  mov rcx,r8                                    
0x6665eac  call 0xE935700                                ; -> sub_e935700
0x6665eb1  mov qword ptr [rbp+0x60],0                    
0x6665eb9  mov qword ptr [rbp+0x68],0xF                  
0x6665ec1  mov byte ptr [rbp+0x50],0                     
0x6665ec5  mov rax,[rbp+0x1A8]                           
0x6665ecc  cmp rax,0x10                                  
0x6665ed0  jb short 0x6665F0A                            ; -> loc_6665f0a
0x6665ed2  mov rcx,[rbp+0x190]                           
0x6665ed9  lea rdx,[rax+1]                               
0x6665edd  cmp rdx,0x1000                                
0x6665ee4  jb short 0x6665F05                            ; -> loc_6665f05
0x6665ee6  mov r8,[rcx-8]                                
0x6665eea  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6665eee  sub rcx,r8                                    
0x6665ef1  cmp rcx,0x20                                  
0x6665ef5  jae 0x6668219                                 ; -> sub_6668219
0x6665efb  add rax,0x28                                  
0x6665eff  mov rdx,rax                                   
0x6665f02  mov rcx,r8                                    
0x6665f05  call 0xE935700                                ; -> sub_e935700
0x6665f0a  mov rax,[rbp+0x3B8]                           
0x6665f11  cmp rax,0x10                                  
0x6665f15  jb short 0x6665F4F                            ; -> loc_6665f4f
0x6665f17  mov rcx,[rbp+0x3A0]                           
0x6665f1e  lea rdx,[rax+1]                               
0x6665f22  cmp rdx,0x1000                                
0x6665f29  jb short 0x6665F4A                            ; -> loc_6665f4a
0x6665f2b  mov r8,[rcx-8]                                
0x6665f2f  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6665f33  sub rcx,r8                                    
0x6665f36  cmp rcx,0x20                                  
0x6665f3a  jae 0x6668219                                 ; -> sub_6668219
0x6665f40  add rax,0x28                                  
0x6665f44  mov rdx,rax                                   
0x6665f47  mov rcx,r8                                    
0x6665f4a  call 0xE935700                                ; -> sub_e935700
```
Purpose: Repeats the string buffer cleanup pattern for three more buffers: [rbp+0x50] (main string), [rbp+0x190] (buffer at +0x1A8 len, +0x190 ptr), [rbp+0x3A0] (buffer at +0x3B8 len, +0x3A0 ptr). Each follows: if len >= 0x10, check if heap allocated (cap >= 0x1000), validate header (rcx-8, check sub <= 0x20), call sub_e935700. Else reset to SSO state (len=0, cap=0xF, first byte=0).

### Phase 30: Final String Buffer Cleanup & Jump (0x6665f4f..0x6665fdd, 20 ins)
```
0x6665f4f  mov rax,[rbp+0x418]                           
0x6665f56  cmp rax,0x10                                  
0x6665f5a  jb short 0x6665F94                            ; -> loc_6665f94
0x6665f5c  mov rcx,[rbp+0x400]                           
0x6665f63  lea rdx,[rax+1]                               
0x6665f67  cmp rdx,0x1000                                
0x6665f6e  jb short 0x6665F8F                            ; -> loc_6665f8f
0x6665f70  mov r8,[rcx-8]                                
0x6665f74  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6665f78  sub rcx,r8                                    
0x6665f7b  cmp rcx,0x20                                  
0x6665f7f  jae 0x6668219                                 ; -> sub_6668219
0x6665f85  add rax,0x28                                  
0x6665f89  mov rdx,rax                                   
0x6665f8c  mov rcx,r8                                    
0x6665f8f  call 0xE935700                                ; -> sub_e935700
0x6665f94  mov rax,[rbp+0x4F8]                           
0x6665f9b  cmp rax,0x10                                  
0x6665f9f  jb short 0x6665FD9                            ; -> loc_6665fd9
0x6665fa1  mov rcx,[rbp+0x4E0]                           
0x6665fa8  lea rdx,[rax+1]                               
0x6665fac  cmp rdx,0x1000                                
0x6665fb3  jb short 0x6665FD4                            ; -> loc_6665fd4
0x6665fb5  mov r8,[rcx-8]                                
0x6665fb9  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6665fbd  sub rcx,r8                                    
0x6665fc0  cmp rcx,0x20                                  
0x6665fc4  jae 0x6668219                                 ; -> sub_6668219
0x6665fca  add rax,0x28                                  
0x6665fce  mov rdx,rax                                   
0x6665fd1  mov rcx,r8                                    
0x6665fd4  call 0xE935700                                ; -> sub_e935700
0x6665fd9  xor eax,eax                                   
0x6665fdb  xor edi,edi                                   
0x6665fdd  jmp 0x666629B                                 ; -> loc_666629b
```
Purpose: Two more buffer cleanups: [rbp+0x400] (len at +0x418) and [rbp+0x4E0] (len at +0x4F8). Then zeros eax/edi, jumps to loc_666629b (common exit path).

### Phase 31: Large Buffer Packing Loop (Alternate Path from Phase 25) (0x6665fe2..0x6666061, 40 ins)
```
0x6665fe2  shr rdx,2                                     
0x6665fe6  inc rdx                                       
0x6665fe9  mov rax,rdx                                   
0x6665fec  and rax,0xFFFFFFFFFFFFFFFE                    
0x6665ff0  lea rsi,[rbp+0x1E0]                           
0x6665ff7  xor ecx,ecx                                   
0x6665ff9  lea rcx,[rcx+rcx*2]                           
0x6665ffd  movzx r8d,word ptr [rsi+4]                    
0x6666002  mov [rdi+rcx*2+4],r8w                         
0x6666008  mov r8d,[rsi]                                 
0x666600b  mov [rdi+rcx*2],r8d                           
0x666600f  mov rcx,[rdi+0x78]                            
0x6666013  inc rcx                                       
0x6666016  mov [rdi+0x78],rcx                            
0x666601a  lea rcx,[rcx+rcx*2]                           
0x666601e  movzx r8d,word ptr [rsi+0xA]                  
0x6666023  mov [rdi+rcx*2+4],r8w                         
0x6666029  mov r8d,[rsi+6]                               
0x666602d  mov [rdi+rcx*2],r8d                           
0x6666031  mov rcx,[rdi+0x78]                            
0x6666035  inc rcx                                       
0x6666038  mov [rdi+0x78],rcx                            
0x666603c  add rsi,0xC                                   
0x6666040  add rax,0xFFFFFFFFFFFFFFFE                    
0x6666044  jne short 0x6665FF9                           ; -> loc_6665ff9
0x6666046  test dl,1                                     
0x6666049  je short 0x6666061                            ; -> loc_6666061
0x666604b  lea rax,[rcx+rcx*2]                           
0x666604f  movzx ecx,word ptr [rsi+4]                    
0x6666053  mov [rdi+rax*2+4],cx                          
0x6666058  mov ecx,[rsi]                                 
0x666605a  mov [rdi+rax*2],ecx                           
0x666605d  inc qword ptr [rdi+0x78]                      
0x6666061  mov qword ptr [rbp+0x258],0                   
```
Purpose: Alternate packing loop (from Phase 25 when count >= 6). Processes data at [rbp+0x1E0] (source) into rdi (destination buffer). Same interleaved pattern as Phase 21: reads word at +4 and dword at +0, stores to [rdi+rcx*2+4] and [rdi+rcx*2]. Uses [rdi+0x78] as element counter. Handles odd count. Zeros [rbp+0x258] after.

### Phase 32: Buffer Finalization & Transaction Object Setup (0x6666061..0x6666139, 40 ins)
```
0x666606c  movzx eax,word ptr [rbp+0x260]                
0x6666073  mov [rdi+0x80],ax                             
0x666607a  mov eax,[rbp+0x268]                           
0x6666080  mov [rdi+0x88],eax                            
0x6666086  mov rax,[rbp+0x280]                           
0x666608d  mov qword ptr [rbp+0x280],0                   
0x6666098  movups xmm1,[rbp+0x270]                       
0x666609f  xorps xmm0,xmm0                               
0x66660a2  movups [rbp+0x270],xmm0                       
0x66660a9  movups [rdi+0x90],xmm1                        
0x66660b0  mov [rdi+0xA0],rax                            
0x66660b7  mov [rbp+0x408],rdi                           
0x66660be  mov rdi,[rbp+0xE8]                            
0x66660c5  test rdi,rdi                                  
0x66660c8  je short 0x66660ED                            ; -> loc_66660ed
0x66660ca  mov rax,[rbp+0xE0]                            
0x66660d1  lock inc dword ptr [rdi+0xC]                  
0x66660d5  lea rcx,[0xF0F9C50]                           ; [data_f0f9c50]
0x66660dc  mov [r15],rcx                                 
0x66660df  mov [r15+8],rax                               
0x66660e3  mov [r15+0x10],rdi                            
0x66660e7  lock inc dword ptr [rdi+0xC]                  
0x66660eb  jmp short 0x66660FC                           ; -> loc_66660fc
0x66660ed  lea rax,[0xF0F9C50]                           ; [data_f0f9c50]
0x66660f4  mov [r15],rax                                 
0x66660f7  movups [r15+8],xmm0                           
0x66660fc  lea rsi,[rbx+0x9B0]                           
0x6666103  xorps xmm6,xmm6                               
0x6666106  movups [r15+0x18],xmm6                        
0x666610b  mov rax,[rbp+0x400]                           
0x6666112  test rax,rax                                  
0x6666115  je short 0x6666137                            ; -> loc_6666137
0x6666117  mov rdx,r15                                   
0x666611a  add rdx,0x18                                  
0x666611e  mov rax,[rax]                                 
0x6666121  lea rcx,[rbp+0x400]                           
0x6666128  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666612e  mov rax,[rbp+0x400]                           
0x6666135  jmp short 0x6666139                           ; -> loc_6666139
0x6666137  xor eax,eax                                   
0x6666139  mov qword ptr [rbp+0x400],0                   
```
Purpose: Finalizes the buffer at rdi: writes [rbp+0x260] (word) to +0x80, [rbp+0x268] (dword) to +0x88, [rbp+0x280] to +0xA0. Moves xmm from [rbp+0x270] to [rdi+0x90], zeros [rbp+0x270]. Sets [rbp+0x408]=rdi. Then sets up a shared_ptr-like structure at r15: if [rbp+0xE8] non-null, increments refcounts, sets vtable 0xF0F9C50, stores pointers. Else sets vtable and zeros data. Zeros [r15+0x18] (xmm6). If [rbp+0x400] non-null, calls sub_eea6040 (vtable slot?) with rdx=r15+0x18. Zeros [rbp+0x400].

### Phase 33: Large Zero Initialization & Refcount Linking (0x6666139..0x6666249, 40 ins)
```
0x6666144  mov [r15+0x18],rax                            
0x6666148  movups [r15+0x58],xmm6                        
0x666614d  movups [r15+0x68],xmm6                        
0x6666152  movups [r15+0x78],xmm6                        
0x6666157  mov qword ptr [r15+0x88],0                    
0x6666162  mov qword ptr [r15+0x90],0xF                  
0x666616d  movups [r15+0x98],xmm6                        
0x6666175  movups [r15+0xA8],xmm6                        
0x666617d  movups [r15+0xB8],xmm6                        
0x6666185  movups [r15+0xC8],xmm6                        
0x666618d  movups [r15+0xD8],xmm6                        
0x6666195  movups [r15+0xE8],xmm6                        
0x666619d  movups [r15+0xF8],xmm6                        
0x66661a5  movups [r15+0x108],xmm6                       
0x66661ad  mov qword ptr [r15+0x118],0                   
0x66661b8  mov [r15+0x120],rsi                           
0x66661bf  test rdi,rdi                                  
0x66661c2  je short 0x66661DA                            ; -> loc_66661da
0x66661c4  lock dec dword ptr [rdi+0xC]                  
0x66661c8  jne short 0x66661DA                           ; -> loc_66661da
0x66661ca  mov rax,[rdi]                                 
0x66661cd  mov rax,[rax+8]                               
0x66661d1  mov rcx,rdi                                   
0x66661d4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66661da  add rbx,0x788                                 
0x66661e1  mov rax,[rbp+0x400]                           
0x66661e8  test rax,rax                                  
0x66661eb  je short 0x66661FE                            ; -> loc_66661fe
0x66661ed  mov rax,[rax+8]                               
0x66661f1  lea rcx,[rbp+0x400]                           
0x66661f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66661fe  mov [rbp+0x400],r15                           
0x6666205  lea rdx,[rbp+0xE0]                            
0x666620c  mov rcx,rbx                                   
0x666620f  call 0xA77BE0                                 ; -> sub_a77be0
0x6666214  nop                                           
0x6666215  lea rdx,[rbp+0xE0]                            
0x666621c  lea r8,[rbp+0x400]                            
0x6666223  mov rcx,rbx                                   
0x6666226  call 0x1771500                                ; -> sub_1771500
0x666622b  nop                                           
0x666622c  mov rcx,[rbp+0x400]                           
0x6666233  test rcx,rcx                                  
0x6666236  je short 0x6666249                            ; -> loc_6666249
0x6666238  mov rax,[rcx]                                 
0x666623b  mov rax,[rax]                                 
0x666623e  mov edx,1                                     
0x6666243  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
Purpose: Extensive zero initialization of structure at r15 (+0x18 through +0x118, 16-byte chunks via xmm6). Sets [r15+0x90]=0xF (SSO capacity), [r15+0x120]=rsi (pointer to rbx+0x9B0). If rdi non-null, decrements refcount at +0xC, destroys via sub_eea6040 if zero. Advances rbx by 0x788. If [rbp+0x400] non-null, destroys via sub_eea6040 (vtable slot 1). Sets [rbp+0x400]=r15. Calls sub_a77be0 with rdx=&[rbp+0xE0], rcx=rbx. Calls sub_1771500 with rdx=&[rbp+0xE0], r8=&[rbp+0x400], rcx=rbx. If [rbp+0x400] non-null, calls sub_eea6040 (vtable slot 0) with edx=1.

### Phase 34: Final Resource Cleanup & Exit (0x6666249..0x66662e9, 40 ins)
```
0x6666249  mov rdi,[rbp+0xE0]                            
0x6666250  test rdi,rdi                                  
0x6666253  je short 0x6666262                            ; -> loc_6666262
0x6666255  mov byte ptr [rdi+0x10],1                     
0x6666259  mov rax,[rbp+0xE8]                            
0x6666260  jmp short 0x666629B                           ; -> loc_666629b
0x6666262  mov rsi,[rbp+0xE8]                            
0x6666269  test rsi,rsi                                  
0x666626c  je short 0x6666299                            ; -> loc_6666299
0x666626e  lock dec dword ptr [rsi+8]                    
0x6666272  jne short 0x6666299                           ; -> loc_6666299
0x6666274  mov rax,[rsi]                                 
0x6666277  mov rax,[rax]                                 
0x666627a  mov rcx,rsi                                   
0x666627d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666283  lock dec dword ptr [rsi+0xC]                  
0x6666287  jne short 0x6666299                           ; -> loc_6666299
0x6666289  mov rax,[rsi]                                 
0x666628c  mov rax,[rax+8]                               
0x6666290  mov rcx,rsi                                   
0x6666293  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666299  xor eax,eax                                   
0x666629b  mov [rbp+0x170],rdi                           
0x66662a2  mov [rbp+0x178],rax                           
0x66662a9  mov rcx,[rbp+0x270]                           
0x66662b0  test rcx,rcx                                  
0x66662b3  je short 0x66662E9                            ; -> loc_66662e9
0x66662b5  mov rdx,[rbp+0x280]                           
0x66662bc  sub rdx,rcx                                   
0x66662bf  cmp rdx,0x1000                                
0x66662c6  jb short 0x66662E4                            ; -> loc_66662e4
0x66662c8  mov rax,[rcx-8]                               
0x66662cc  add rcx,0xFFFFFFFFFFFFFFF8                    
0x66662d0  sub rcx,rax                                   
0x66662d3  cmp rcx,0x20                                  
0x66662d7  jae 0x6668219                                 ; -> sub_6668219
0x66662dd  add rdx,0x27                                  
0x66662e1  mov rcx,rax                                   
0x66662e4  call 0xE935700                                ; -> sub_e935700
```
Purpose: Cleanup path. If [rbp+0xE0] non-null, sets byte at +0x10=1, saves [rbp+0xE8] to rax, jumps to exit. Else cleans up [rbp+0xE8] via shared_ptr destruction (dec +8, call sub_eea6040 slot 0, dec +0xC, call slot 1). Saves rdi/rax to [rbp+0x170]/[rbp+0x178]. Then checks [rbp+0x270] (allocated buffer from Phase 22): if non-null, computes size ([rbp+0x280] - [rbp+0x270]), if >= 0x1000 validates header and calls sub_e935700 (deallocator).

### Phase 35: UIImGui Desc Field Reads - copySrcB Path (0x66662e9..0x66663ce, 40 ins)
```
0x66662e9  mov rdx,[rbp+0x520]                           
0x66662f0  mov rax,[rdx+0x18]                            
0x66662f4  mov rcx,rax                                   
0x66662f7  shr rcx,0x20                                  
0x66662fb  jne 0x66683B1                                 ; -> sub_66683b1
0x6666301  mov rdi,[rdx+0x20]                            
0x6666305  mov rbx,[r14+0x10]                            
0x6666309  mov [rbp+0x4E0],eax                           
0x666630f  xorps xmm0,xmm0                               
0x6666312  movups [rbp+0x4E8],xmm0                       
0x6666319  mov qword ptr [rbp+0x4F8],0                   
0x6666324  test rax,rax                                  
0x6666327  je 0x66663CE                                  ; -> loc_66663ce
0x666632d  lea r15,[rax+rax]                             
0x6666331  mov rsi,r13                                   
0x6666334  cmp rax,0x800                                 
0x666633a  jb short 0x6666379                            ; -> loc_6666379
0x666633c  lea r13,[r15+0x27]                            
0x6666340  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6666347  mov rax,[rcx]                                 
0x666634a  mov rax,[rax+8]                               
0x666634e  mov rdx,r13                                   
0x6666351  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666357  nop                                           
0x6666358  mov r12,rax                                   
0x666635b  test rax,rax                                  
0x666635e  je 0x66681B6                                  ; -> sub_66681b6
0x6666364  mov rax,r12                                   
0x6666367  add r12,0x27                                  
0x666636b  and r12,0xFFFFFFFFFFFFFFE0                    
0x666636f  mov [r12-8],rax                               
0x6666374  mov r13,rsi                                   
0x6666377  jmp short 0x66663A0                           ; -> loc_66663a0
```
Purpose: **Rebinds rdx=[rbp+0x520] (desc base)** per oc_U-D8b-imgui2.md. Reads desc+0x18 (length, high dword must be 0), desc+0x20 -> rdi (copySrcB per oc_U-D8b-imgui2.md). Reads rbx=[r14+0x10] (arg1+0x10). Zeros [rbp+0x4E8]/[rbp+0x4F8]. If length (eax) == 0, jumps to loc_66663ce. Else allocates buffer for copy: r15 = length*2 bytes. If length >= 0x800, allocates via sub_eea6040 with size+0x27 aligned; stores original ptr at [r12-8]. Else smaller alloc at 0x6666379.

### Phase 36: Small Allocation & Memcpy for copySrcB (0x6666379..0x666648a, 40 ins)
```
0x6666379  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6666380  mov rax,[rcx]                                 
0x6666383  mov rax,[rax+8]                               
0x6666387  mov rdx,r15                                   
0x666638a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666390  nop                                           
0x6666391  mov r12,rax                                   
0x6666394  test rax,rax                                  
0x6666397  mov r13,rsi                                   
0x666639a  je 0x66681C4                                  ; -> sub_66681c4
0x66663a0  mov [rbp+0x4E8],r12                           
0x66663a7  lea rsi,[r12+r15]                             
0x66663ab  mov [rbp+0x4F8],rsi                           
0x66663b2  mov rcx,r12                                   
0x66663b5  mov rdx,rdi                                   
0x66663b8  mov r8,r15                                    
0x66663bb  call 0xEEC6DE0                                ; -> sub_eec6de0
0x66663c0  mov [rbp+0x4F0],rsi                           
0x66663c7  mov r12,[rbp+0x508]                           
0x66663ce  cmp byte ptr [rbx+0x780],0                    
0x66663d5  je 0x666648A                                  ; -> loc_666648a
0x66663db  mov qword ptr [rbp+0x1E8],0                   
0x66663e6  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x66663ed  mov rax,[rcx]                                 
0x66663f0  mov rax,[rax+8]                               
0x66663f4  mov edx,0x20                                  
0x66663f9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66663ff  nop                                           
0x6666400  mov rdi,rax                                   
0x6666403  test rax,rax                                  
0x6666406  je 0x6668117                                  ; -> sub_6668117
0x666640c  mov [rbp+0x1E0],rdi                           
0x6666413  mov qword ptr [rbp+0x1F0],0x13                
0x666641e  mov qword ptr [rbp+0x1F8],0x1F                
0x6666429  mov eax,[0xF58B3C5]                           ; [data_f58b3c5] "tion"
0x666642f  mov [rdi+0xF],eax                             
0x6666432  movups xmm0,[0xF58B3B6]                       ; [data_f58b3b6] "Unnamed Transaction"
0x6666439  movups [rdi],xmm0                             
0x666643c  mov byte ptr [rdi+0x13],0                     
0x6666440  lea rcx,[0x123BB218]                          ; [data_123bb218]
0x6666447  lea rdx,[0x1287EBE0]                          ; [data_1287ebe0]
0x666644e  call 0xEEC6E70                                ; -> sub_eec6e70
```
Purpose: Small allocation path for copySrcB. Allocates via sub_eea6040, checks result. Stores allocated ptr to [rbp+0x4E8], end to [rbp+0x4F8]. Calls sub_eec6de0 (memcpy) to copy from rdi (copySrcB) to r12, count r15. Stores result to [rbp+0x4F0]. Then checks byte at [rbx+0x780] (rbx = [r14+0x10] from Phase 35). If non-zero, creates another "Unnamed Transaction" object (same pattern as Phase 23): allocates 0x20, writes string, calls sub_eec6e70 with globals 0x123BB218, 0x1287EBE0.

### Phase 37: Transaction Object Creation & Processing (0x6666453..0x666658c, 40 ins)
```
0x6666453  mov rdi,rax                                   
0x6666456  xorps xmm0,xmm0                               
0x6666459  movaps [rbp+0x50],xmm0                        
0x666645d  mov rcx,rax                                   
0x6666460  call 0xEEC7570                                ; -> sub_eec7570
0x6666465  test rax,rax                                  
0x6666468  js 0x6668461                                  ; -> sub_6668461
0x666646e  mov rbx,rax                                   
0x6666471  cmp rax,0x10                                  
0x6666475  jae 0x6666640                                 ; -> loc_6666640
0x666647b  lea r15,[rbp+0x50]                            
0x666647f  mov r12d,0xF                                  
0x6666485  jmp 0x66666B7                                 ; -> loc_66666b7
0x666648a  xorps xmm0,xmm0                               
0x666648d  movaps [rbp+0x400],xmm0                       
0x6666494  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x666649b  mov rax,[rcx]                                 
0x666649e  mov rax,[rax+8]                               
0x66664a2  mov edx,0x30                                  
0x66664a7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66664ad  nop                                           
0x66664ae  mov rsi,rax                                   
0x66664b1  test rax,rax                                  
0x66664b4  je 0x6668167                                  ; -> sub_6668167
0x66664ba  mov rax,0x100000001                           
0x66664c4  mov [rsi+8],rax                               
0x66664c8  lea rax,[0xF0F9C60]                           ; [data_f0f9c60]
0x66664cf  mov [rsi],rax                                 
0x66664d2  mov rax,rsi                                   
0x66664d5  add rax,0x10                                  
0x66664d9  mov [rbp+0x510],rax                           
0x66664e0  xorps xmm0,xmm0                               
0x66664e3  movups [rsi+0x10],xmm0                        
0x66664e7  mov [rbp+0x518],rsi                           
0x66664ee  mov byte ptr [rsi+0x20],0                     
0x66664f2  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x66664f9  mov rax,[rcx]                                 
0x66664fc  mov rax,[rax+8]                               
0x6666500  mov edx,0x18                                  
0x6666505  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666650b  nop                                           
0x666650c  mov rdi,rax                                   
0x666650f  test rax,rax                                  
0x6666512  je 0x6668177                                  ; -> sub_6668177
0x6666518  mov byte ptr [rdi+2],0                        
0x666651c  mov qword ptr [rdi+0x10],0                    
0x6666524  mov qword ptr [rdi+4],0                       
0x666652c  mov byte ptr [rdi+0xC],0                      
0x6666530  mov word ptr [rdi],0xFFFF                     
0x6666535  mov rax,[rbp+0x518]                           
0x666653c  mov [rax+0x28],rdi                            
0x6666540  mov rcx,[rbp+0x510]                           
0x6666547  mov [rbp+0x400],rcx                           
0x666654e  mov rdi,[rbp+0x408]                           
0x6666555  mov [rbp+0x408],rax                           
0x666655c  test rdi,rdi                                  
0x666655f  je short 0x666658C                            ; -> loc_666658c
0x6666561  lock dec dword ptr [rdi+8]                    
0x6666565  jne short 0x666658C                           ; -> loc_666658c
```
Purpose: Calls sub_eec7570 on transaction object. If result >= 0x10, jumps to large handling at loc_6666640; else sets up small buffer at [rbp+0x50] with size 0xF, jumps to loc_66666b7. Alternate path (loc_666648a, when [rbx+0x780]==0): allocates 0x30 bytes (vtable 0xF0F9C60), initializes, allocates 0x18 bytes, zeroes, sets words to 0xFFFF, links objects. Cleans up old [rbp+0x408] via shared_ptr destruction.

### Phase 38: More Allocations & Large Transaction Path (0x666658c..0x6666696, 40 ins)
```
0x666658c  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6666593  mov rax,[rcx]                                 
0x6666596  mov rax,[rax+8]                               
0x666659a  mov edx,0xA0                                  
0x666659f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66665a5  nop                                           
0x66665a6  mov rdi,rax                                   
0x66665a9  test rax,rax                                  
0x66665ac  je 0x6668187                                  ; -> sub_6668187
0x66665b2  mov qword ptr [rbp+0x1E8],0                   
0x66665bd  lea rax,[0xF2BEE88]                           ; [data_f2bee88]
0x66665c4  mov [rbp+0x1E0],rax                           
0x66665cb  mov eax,[rbp+0x4E0]                           
0x66665d1  mov [rbp+0x1E8],eax                           
0x66665d7  mov rax,[rbp+0x4F8]                           
0x66665de  mov qword ptr [rbp+0x4F8],0                   
0x66665e9  movups xmm1,[rbp+0x4E8]                       
0x66665f0  xorps xmm0,xmm0                               
0x66665f3  movups [rbp+0x4E8],xmm0                       
0x66665fa  movups [rbp+0x1F0],xmm1                       
0x6666601  mov [rbp+0x200],rax                           
0x6666608  mov r15,[rbp+0x408]                           
0x666660f  lea rax,[0xF0F9C80]                           ; [data_f0f9c80]
0x6666616  test r15,r15                                  
0x6666619  je 0x66669A0                                  ; -> loc_66669a0
0x666661f  mov rcx,[rbp+0x400]                           
0x6666626  lock inc dword ptr [r15+0xC]                  
0x666662b  mov [rdi],rax                                 
0x666662e  mov [rdi+8],rcx                               
0x6666632  mov [rdi+0x10],r15                            
0x6666636  lock inc dword ptr [r15+0xC]                  
0x666663b  jmp 0x66669A7                                 ; -> loc_66669a7
0x6666640  mov rdx,rbx                                   
0x6666643  or rdx,0xF                                    
0x6666647  cmp rdx,0x17                                  
0x666664b  mov r12d,0x16                                 
0x6666651  cmovae r12,rdx                                
0x6666655  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x666665c  mov rax,[rcx]                                 
0x666665f  mov rax,[rax+8]                               
0x6666663  cmp rdx,0xFFF                                 
0x666666a  jb short 0x6666698                            ; -> loc_6666698
0x666666c  lea rsi,[r12+0x28]                            
0x6666671  mov rdx,rsi                                   
0x6666674  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666667a  nop                                           
0x666667b  mov r15,rax                                   
0x666667e  test rax,rax                                  
0x6666681  je 0x66681F4                                  ; -> sub_66681f4
0x6666687  mov rax,r15                                   
0x666668a  add r15,0x27                                  
0x666668e  and r15,0xFFFFFFFFFFFFFFE0                    
0x6666692  mov [r15-8],rax                               
0x6666696  jmp short 0x66666B3                           ; -> loc_66666b3
```
Purpose: Allocates 0xA0 bytes (vtable 0xF2BEE88). Moves data from [rbp+0x4E8] (copied copySrcB) to [rbp+0x1F0]. Sets up shared_ptr at rdi pointing to [rbp+0x400] and r15 ([rbp+0x408]). Increments refcounts. Jumps to loc_66669a7. Large transaction path (from Phase 37): computes size = max(0x16, rbx|0xF). If >= 0xFFF, allocates r12+0x28 via sub_eea6040, stores original ptr at [r15-8]. Jumps to loc_66666b3.

---

## Updated String Reference Table (Phase 0-38)

| String RVA | Text | Call Site RVA | Callee After |
|------------|------|---------------|--------------|
| 0xF5AD096 | "Debug/ImGui" | 0x6664ae9 (lea rax) | 0x675E440 (sub_675e440) |
| 0xF539A95 | "UI/Blit" | 0x6664d8f (lea rax) | 0x675E440 (sub_675e440) |
| 0xF58B3B6 | "Unnamed Transaction" | 0x6665986, 0x6666432 (movups xmm0) | 0xEEC6E70 (sub_eec6e70) |
| 0xF58B3C5 | "tion" | 0x666597d, 0x6666429 (mov eax) | 0xEEC6E70 (sub_eec6e70) |
| 0xF8407B6 | (format string) | 0x6665d92 (lea r9) | 0xA0850 (sub_a0850) |

## Updated [reg+off] Write Table (Non-Stack, Output Descriptions/Records)

| Offset | Size | Source | Instruction (RVA) | Meaning | Tag |
|--------|------|--------|-------------------|---------|-----|
| [rdi+0x00] | 2 | 0x203E | 0x6665dc2 | Write "> " to string buffer | [V] |
| [rdi+0x02] | 1 | 0 | 0x6665dc8 | Null terminator | [V] |
| [rbp+0xE0] | 16 | [rdi] | 0x6665ddb | Save xmm0 | [V] |
| [rbp+0xF0] | 16 | [rdi+0x10] | 0x6665dd4 | Save xmm1 | [V] |
| [rdi+0x10] | 8 | 0 | 0x6665de2 | Reset string len | [V] |
| [rdi+0x18] | 8 | 0xF | 0x6665dea | Reset string cap | [V] |
| [rdi+0x00] | 1 | 0 | 0x6665df2 | Reset first char | [V] |
| [rbp+0xF0] | 8 | 0 | 0x6665e55 | Zero buffer ptr | [V] |
| [rbp+0xF8] | 8 | 0xF | 0x6665e60 | Reset cap | [V] |
| [rbp+0xE0] | 1 | 0 | 0x6665e6b | Zero first char | [V] |
| [rbp+0x60] | 8 | 0 | 0x6665eb1 | Zero len | [V] |
| [rbp+0x68] | 8 | 0xF | 0x6665eb9 | Reset cap | [V] |
| [rbp+0x50] | 1 | 0 | 0x6665ec1 | Zero first char | [V] |
| [r15+0x00] | 8 | 0xF0F9C50 | 0x66660dc/0x66660f4 | Vtable | [V] |
| [r15+0x08] | 8 | [rbp+0xE0] | 0x66660df | Ptr | [V] |
| [r15+0x10] | 8 | rdi | 0x66660e3 | Ptr | [V] |
| [r15+0x18] | 16 | 0 | 0x6666106 | Zero | [V] |
| [r15+0x18..0x118] | 16x10 | 0 | 0x6666148..0x66661a5 | Zero init | [V] |
| [r15+0x90] | 8 | 0xF | 0x6666162 | SSO cap | [V] |
| [r15+0x118] | 8 | 0 | 0x66661ad | Zero | [V] |
| [r15+0x120] | 8 | rsi | 0x66661b8 | Link to rbx+0x9B0 | [V] |
| [rbp+0x400] | 8 | r15 | 0x66661fe | Save transaction | [V] |
| [rdi+0x10] | 1 | 1 | 0x6666255 | Flag | [V] |
| [rbp+0x170] | 8 | rdi | 0x666629b | Save | [V] |
| [rbp+0x178] | 8 | rax | 0x66662a2 | Save | [V] |
| [rbp+0x4E8] | 8 | r12 (alloc) | 0x66663a0 | copySrcB buffer | [V] |
| [rbp+0x4F8] | 8 | rsi (end) | 0x66663ab | Buffer end | [V] |
| [rbp+0x4F0] | 8 | rsi | 0x66663c0 | memcpy result | [V] |
| [rdi+0x00..0x0F] | 16 | "Unnamed Transaction" | 0x6666439 | Transaction name | [V] |
| [rdi+0x0F] | 4 | "tion" | 0x666642f | Suffix | [V] |
| [rdi+0x10] | 8 | 0x13 | 0x6666413 | Field | [V] |
| [rdi+0x18] | 8 | 0x1F | 0x666641e | Field | [V] |
| [rdi+0x13] | 1 | 0 | 0x666643c | Field | [V] |
| [rbp+0x50] | 16 | 0 | 0x6666459 | Zero | [V] |
| [rsi+0x08] | 8 | 0x100000001 | 0x66664c4 | Refcount | [V] |
| [rsi+0x00] | 8 | 0xF0F9C60 | 0x66664cf | Vtable | [V] |
| [rsi+0x10..0x1F] | 16 | 0 | 0x66664e3 | Zero | [V] |
| [rsi+0x20] | 1 | 0 | 0x66664ee | Zero | [V] |
| [rdi+0x00] | 8 | 0xF0F9C60 | 0x66664cf | Vtable (dup) | [V] |
| [rdi+0x02] | 1 | 0 | 0x6666518 | Zero | [V] |
| [rdi+0x10] | 8 | 0 | 0x666651c | Zero | [V] |
| [rdi+0x04] | 8 | 0 | 0x6666524 | Zero | [V] |
| [rdi+0x0C] | 1 | 0 | 0x666652c | Zero | [V] |
| [rdi+0x00] | 2 | 0xFFFF | 0x6666530 | Word init | [V] |
| [rax+0x28] | 8 | rdi | 0x666653c | Link | [V] |
| [rbp+0x400] | 8 | [rbp+0x510] | 0x6666547 | Ptr | [V] |
| [rbp+0x408] | 8 | rax | 0x6666555 | Swap | [V] |
| [rbp+0x1E0] | 8 | 0xF2BEE88 | 0x66665c4 | Vtable | [V] |
| [rbp+0x1E8] | 4 | [rbp+0x4E0] | 0x66665d1 | Copied length | [V] |
| [rbp+0x1F0] | 16 | [rbp+0x4E8] | 0x66665fa | Copied data | [V] |
| [rbp+0x200] | 8 | [rbp+0x4F8] | 0x6666601 | End ptr | [V] |
| [rdi+0x00] | 8 | 0xF0F9C80 | 0x666662b | Vtable | [V] |
| [rdi+0x08] | 8 | [rbp+0x400] | 0x666662e | Ptr | [V] |
| [rdi+0x10] | 8 | r15 | 0x6666632 | Ptr | [V] |
| [r15+0x0C] | 4 | +1 | 0x6666626/0x6666636 | Refcount inc | [V] |

---

## Verification
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-I5a2.md` after each chunk.

## TOOL REQUESTS
None.

---

## Step 4 Complete: Instruction-complete listing of 0x6664a00 (next 500 instructions: 0x6666696..0x6667047, 12 phases)
Next chunk: continue from 0x6667047.

### Phase 39: Large Transaction Buffer Setup & Memcpy (0x6666696..0x6666782, 40 ins)
```
0x6666696  jmp short 0x66666B3                           ; -> loc_66666b3
0x6666698  lea rsi,[r12+1]                               
0x666669d  mov rdx,rsi                                   
0x66666a0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66666a6  nop                                           
0x66666a7  mov r15,rax                                   
0x66666aa  test rax,rax                                  
0x66666ad  je 0x6668202                                  ; -> loc_6668202
0x66666b3  mov [rbp+0x50],r15                            
0x66666b7  mov [rbp+0x60],rbx                            
0x66666bb  mov [rbp+0x68],r12                            
0x66666bf  mov rcx,r15                                   
0x66666c2  mov rdx,rdi                                   
0x66666c5  mov r8,rbx                                    
0x66666c8  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x66666cd  mov byte ptr [r15+rbx],0                      
0x66666d2  xorps xmm0,xmm0                               
0x66666d5  movaps [rbp+0x3A0],xmm0                       
0x66666dc  mov qword ptr [rbp+0x3B0],1                   
0x66666e7  mov qword ptr [rbp+0x3B8],0xF                 
0x66666f2  mov byte ptr [rbp+0x3A0],0x3C                 
0x66666f9  lea rdi,[rbp+0xE0]                            
0x6666700  lea r8,[rbp+0x3A0]                            
0x6666707  lea r9,[rbp+0x50]                             
0x666670b  mov rcx,rdi                                   
0x666670e  call 0x11D1F0                                 ; -> sub_11d1f0
0x6666713  nop                                           
0x6666714  mov rax,[rbp+0xF0]                            
0x666671b  mov rcx,[rbp+0xF8]                            
0x6666722  mov rdx,rcx                                   
0x6666725  sub rdx,rax                                   
0x6666728  cmp rdx,2                                     
0x666672c  mov r12,[rbp+0x508]                           
0x6666733  jae short 0x666675C                           ; -> loc_666675c
0x6666735  mov qword ptr [rsp+0x20],2                    
0x666673e  lea r9,[0xF8407B6]                            ; [data_f8407b6]
0x6666745  lea rcx,[rbp+0xE0]                            
0x666674c  mov edx,2                                     
0x6666751  call 0xA0850                                  ; -> sub_a0850
0x6666756  nop                                           
0x6666757  mov rdi,rax                                   
0x666675a  jmp short 0x6666782                           ; -> loc_6666782
0x666675c  lea rdx,[rax+2]                               
0x6666760  mov [rbp+0xF0],rdx                            
0x6666767  mov rdx,rdi                                   
0x666676a  cmp rcx,0x10                                  
0x666676e  jb short 0x6666777                            ; -> loc_6666777
0x6666770  mov rdx,[rbp+0xE0]                            
0x6666777  mov word ptr [rdx+rax],0x203E                 
0x666677d  mov byte ptr [rdx+rax+2],0                    
0x6666782  movups xmm0,[rdi]                             
0x6666785  movups xmm1,[rdi+0x10]                        
0x6666789  movaps [rbp+0x410],xmm1                       
0x6666790  movaps [rbp+0x400],xmm0                       
0x6666797  mov qword ptr [rdi+0x10],0                    
0x666679f  mov qword ptr [rdi+0x18],0xF                  
0x66667a7  mov byte ptr [rdi],0                          
```
Purpose: Large transaction path (from Phase 38). Jumps to loc_66666b3 (or from 0x666820e). Sets up buffer at [rbp+0x50]=r15 (allocated), [rbp+0x60]=rbx (size), [rbp+0x68]=r12 (capacity). Calls sub_eec6ec0 (memcpy: dst=r15, src=rdi, count=rbx). Null-terminates at [r15+rbx]. Sets up string descriptor at [rbp+0x3A0] with byte 0x3C, len=1, cap=0xF. Calls sub_11d1f0 with rcx=&[rbp+0xE0], r8=&[rbp+0x3A0], r9=&[rbp+0x50]. Then string buffer management at [rbp+0xE0]: if space < 2, calls sub_a0850 with format 0xF8407B6; else writes "> " (0x203E) and null. Saves rdi xmm0/xmm1 to [rbp+0x400]/[rbp+0x410], resets rdi to empty SSO string.

### Phase 40: String Buffer Cleanup (First Buffer) (0x66667aa..0x666686c, 40 ins)
```
0x66667aa  lea rcx,[rbp+0x190]                           
0x66667b1  lea r8,[rbp+0x400]                            
0x66667b8  lea r9,[rbp+0x1E0]                            
0x66667bf  call 0x11D1F0                                 ; -> sub_11d1f0
0x66667c4  nop                                           
0x66667c5  mov rax,[rbp+0x418]                           
0x66667cc  cmp rax,0x10                                  
0x66667d0  jb short 0x666680A                            ; -> loc_666680a
0x66667d2  mov rcx,[rbp+0x400]                           
0x66667d9  lea rdx,[rax+1]                               
0x66667dd  cmp rdx,0x1000                                
0x66667e4  jb short 0x6666805                            ; -> loc_6666805
0x66667e6  mov r8,[rcx-8]                                
0x66667ea  add rcx,0xFFFFFFFFFFFFFFF8                    
0x66667ee  sub rcx,r8                                    
0x66667f1  cmp rcx,0x20                                  
0x66667f5  jae 0x6668219                                 ; -> loc_6668219
0x66667fb  add rax,0x28                                  
0x66667ff  mov rdx,rax                                   
0x6666802  mov rcx,r8                                    
0x6666805  call 0xE935700                                ; -> sub_e935700
0x666680a  mov qword ptr [rbp+0x410],0                   
0x6666815  mov qword ptr [rbp+0x418],0xF                 
0x6666820  mov byte ptr [rbp+0x400],0                    
0x6666827  mov rax,[rbp+0xF8]                            
0x666682e  cmp rax,0x10                                  
0x6666832  jb short 0x666686C                            ; -> loc_666686c
0x6666834  mov rcx,[rbp+0xE0]                            
0x666683b  lea rdx,[rax+1]                               
0x666683f  cmp rdx,0x1000                                
0x6666846  jb short 0x6666867                            ; -> loc_6666867
0x6666848  mov r8,[rcx-8]                                
0x666684c  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6666850  sub rcx,r8                                    
0x6666853  cmp rcx,0x20                                  
0x6666857  jae 0x6668219                                 ; -> loc_6668219
0x666685d  add rax,0x28                                  
0x6666861  mov rdx,rax                                   
0x6666864  mov rcx,r8                                    
0x6666867  call 0xE935700                                ; -> sub_e935700
0x666686c  mov qword ptr [rbp+0xF0],0                    
0x6666877  mov qword ptr [rbp+0xF8],0xF                  
0x6666882  mov byte ptr [rbp+0xE0],0                     
```
Purpose: Calls sub_11d1f0 with rcx=&[rbp+0x190], r8=&[rbp+0x400], r9=&[rbp+0x1E0]. Then standard string buffer cleanup for two buffers: [rbp+0x400] (len at +0x418) and [rbp+0xE0] (len at +0xF8). Each: if len >= 0x10, check heap allocation (cap >= 0x1000), validate header, call sub_e935700; else reset to SSO (len=0, cap=0xF, first byte=0).

### Phase 41: Three More String Buffer Cleanups (0x666686c..0x666699b, 40 ins)
```
0x6666889  mov rax,[rbp+0x3B8]                           
0x6666890  cmp rax,0x10                                  
0x6666894  jb short 0x66668CE                            ; -> loc_66668ce
0x6666896  mov rcx,[rbp+0x3A0]                           
0x666689d  lea rdx,[rax+1]                               
0x66668a1  cmp rdx,0x1000                                
0x66668a8  jb short 0x66668C9                            ; -> loc_66668c9
0x66668aa  mov r8,[rcx-8]                                
0x66668ae  add rcx,0xFFFFFFFFFFFFFFF8                    
0x66668b2  sub rcx,r8                                    
0x66668b5  cmp rcx,0x20                                  
0x66668b9  jae 0x6668219                                 ; -> loc_6668219
0x66668bf  add rax,0x28                                  
0x66668c3  mov rdx,rax                                   
0x66668c6  mov rcx,r8                                    
0x66668c9  call 0xE935700                                ; -> sub_e935700
0x66668ce  mov rax,[rbp+0x68]                            
0x66668d2  cmp rax,0x10                                  
0x66668d6  jb short 0x666690D                            ; -> loc_666690d
0x66668d8  mov rcx,[rbp+0x50]                            
0x66668dc  lea rdx,[rax+1]                               
0x66668e0  cmp rdx,0x1000                                
0x66668e7  jb short 0x6666908                            ; -> loc_6666908
0x66668e9  mov r8,[rcx-8]                                
0x66668ed  add rcx,0xFFFFFFFFFFFFFFF8                    
0x66668f1  sub rcx,r8                                    
0x66668f4  cmp rcx,0x20                                  
0x66668f8  jae 0x6668219                                 ; -> loc_6668219
0x66668fe  add rax,0x28                                  
0x6666902  mov rdx,rax                                   
0x6666905  mov rcx,r8                                    
0x6666908  call 0xE935700                                ; -> sub_e935700
0x666690d  mov rax,[rbp+0x1F8]                           
0x6666914  cmp rax,0x10                                  
0x6666918  jb short 0x6666952                            ; -> loc_6666952
0x666691a  mov rcx,[rbp+0x1E0]                           
0x6666921  lea rdx,[rax+1]                               
0x6666925  cmp rdx,0x1000                                
0x666692c  jb short 0x666694D                            ; -> loc_666694d
0x666692e  mov r8,[rcx-8]                                
0x6666932  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6666936  sub rcx,r8                                    
0x6666939  cmp rcx,0x20                                  
0x666693d  jae 0x6668219                                 ; -> loc_6668219
0x6666943  add rax,0x28                                  
0x6666947  mov rdx,rax                                   
0x666694a  mov rcx,r8                                    
0x666694d  call 0xE935700                                ; -> sub_e935700
0x6666952  mov rax,[rbp+0x1A8]                           
0x6666959  cmp rax,0x10                                  
0x666695d  jb short 0x6666997                            ; -> loc_6666997
0x666695f  mov rcx,[rbp+0x190]                           
0x6666966  lea rdx,[rax+1]                               
0x666696a  cmp rdx,0x1000                                
0x6666971  jb short 0x6666992                            ; -> loc_6666992
0x6666973  mov r8,[rcx-8]                                
0x6666977  add rcx,0xFFFFFFFFFFFFFFF8                    
0x666697b  sub rcx,r8                                    
0x666697e  cmp rcx,0x20                                  
0x6666982  jae 0x6668219                                 ; -> loc_6668219
0x6666988  add rax,0x28                                  
0x666698c  mov rdx,rax                                   
0x666698f  mov rcx,r8                                    
0x6666992  call 0xE935700                                ; -> sub_e935700
0x6666997  xor eax,eax                                   
0x6666999  xor edi,edi                                   
0x666699b  jmp 0x6666AF8                                 ; -> loc_6666af8
```
Purpose: Three more string buffer cleanups: [rbp+0x3A0] (len at +0x3B8), [rbp+0x50] (len at +0x68), [rbp+0x1E0] (len at +0x1F8), [rbp+0x190] (len at +0x1A8). Each follows the same pattern. Then zeros eax/edi, jumps to common exit at loc_6666af8.

### Phase 42: Alternate Path - Small Transaction Object (0x66669a0..0x6666a37, 40 ins)
```
0x66669a0  mov [rdi],rax                                 
0x66669a3  movups [rdi+8],xmm0                           
0x66669a7  lea rsi,[rbx+0x768]                           
0x66669ae  xorps xmm6,xmm6                               
0x66669b1  movups [rdi+0x18],xmm6                        
0x66669b5  mov rax,[rbp+0x1E0]                           
0x66669bc  test rax,rax                                  
0x66669bf  je short 0x66669E1                            ; -> loc_66669e1
0x66669c1  mov rdx,rdi                                   
0x66669c4  add rdx,0x18                                  
0x66669c8  mov rax,[rax]                                 
0x66669cb  lea rcx,[rbp+0x1E0]                           
0x66669d2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66669d8  mov rax,[rbp+0x1E0]                           
0x66669df  jmp short 0x66669E3                           ; -> loc_66669e3
0x66669e1  xor eax,eax                                   
0x66669e3  mov qword ptr [rbp+0x1E0],0                   
0x66669ee  mov [rdi+0x18],rax                            
0x66669f2  movups [rdi+0x58],xmm6                        
0x66669f6  movups [rdi+0x68],xmm6                        
0x66669fa  movups [rdi+0x78],xmm6                        
0x66669fe  mov qword ptr [rdi+0x88],0                    
0x6666a09  mov qword ptr [rdi+0x90],0xF                  
0x6666a14  mov [rdi+0x98],rsi                            
0x6666a1b  test r15,r15                                  
0x6666a1e  je short 0x6666A37                            ; -> loc_6666a37
0x6666a20  lock dec dword ptr [r15+0xC]                  
0x6666a25  jne short 0x6666A37                           ; -> loc_6666a37
0x6666a27  mov rax,[r15]                                 
0x6666a2a  mov rax,[rax+8]                               
0x6666a2e  mov rcx,r15                                   
0x6666a31  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
Purpose: Alternate path from Phase 38 (when r15 null at 0x6666616). Sets vtable at rdi (rax=0xF0F9C80 from Phase 38), zeros [rdi+8]. Sets up shared_ptr-like object at rdi: rsi=rbx+0x768, zeros [rdi+0x18]. If [rbp+0x1E0] non-null, calls sub_eea6040 (vtable slot?) with rdx=rdi+0x18. Zeros [rbp+0x1E0]. Extensive zero init of rdi (+0x58 through +0x90). Sets [rdi+0x90]=0xF (SSO cap), [rdi+0x98]=rsi. If r15 non-null, decrements refcount at +0xC, destroys via sub_eea6040 if zero.

### Phase 43: Object Finalization & Cleanup (0x6666a37..0x6666af8, 40 ins)
```
0x6666a37  add rbx,0x540                                 
0x6666a3e  mov rax,[rbp+0x1E0]                           
0x6666a45  test rax,rax                                  
0x6666a48  je short 0x6666A5B                            ; -> loc_6666a5b
0x6666a4a  mov rax,[rax+8]                               
0x6666a4e  lea rcx,[rbp+0x1E0]                           
0x6666a55  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666a5b  mov [rbp+0x1E0],rdi                           
0x6666a62  lea rdx,[rbp+0x400]                           
0x6666a69  mov rcx,rbx                                   
0x6666a6c  call 0xA77BE0                                 ; -> sub_a77be0
0x6666a71  nop                                           
0x6666a72  lea rdx,[rbp+0x400]                           
0x6666a79  lea r8,[rbp+0x1E0]                            
0x6666a80  mov rcx,rbx                                   
0x6666a83  call 0x1771500                                ; -> sub_1771500
0x6666a88  nop                                           
0x6666a89  mov rcx,[rbp+0x1E0]                           
0x6666a90  test rcx,rcx                                  
0x6666a93  je short 0x6666AA6                            ; -> loc_6666aa6
0x6666a95  mov rax,[rcx]                                 
0x6666a98  mov rax,[rax]                                 
0x6666a9b  mov edx,1                                     
0x6666aa0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666aa6  mov rdi,[rbp+0x400]                           
0x6666aad  test rdi,rdi                                  
0x6666ab0  je short 0x6666ABF                            ; -> loc_6666abf
0x6666ab2  mov byte ptr [rdi+0x10],1                     
0x6666ab6  mov rax,[rbp+0x408]                           
0x6666abd  jmp short 0x6666AF8                           ; -> loc_6666af8
0x6666abf  mov rsi,[rbp+0x408]                           
0x6666ac6  test rsi,rsi                                  
0x6666ac9  je short 0x6666AF6                            ; -> loc_6666af6
0x6666acb  lock dec dword ptr [rsi+8]                    
0x6666acf  jne short 0x6666AF6                           ; -> loc_6666af6
0x6666ad1  mov rax,[rsi]                                 
0x6666ad4  mov rax,[rax]                                 
0x6666ad7  mov rcx,rsi                                   
0x6666ada  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666ae0  lock dec dword ptr [rsi+0xC]                  
0x6666ae4  jne short 0x6666AF6                           ; -> loc_6666af6
0x6666ae6  mov rax,[rsi]                                 
0x6666ae9  mov rax,[rax+8]                               
0x6666aed  mov rcx,rsi                                   
0x6666af0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666af6  xor eax,eax                                   
0x6666af8  mov [rbp+0x180],rdi                           
0x6666aff  mov [rbp+0x188],rax                           
```
Purpose: Advances rbx by 0x540. Cleans up [rbp+0x1E0] if non-null via sub_eea6040. Sets [rbp+0x1E0]=rdi. Calls sub_a77be0 (rdx=&[rbp+0x400], rcx=rbx). Calls sub_1771500 (rdx=&[rbp+0x400], r8=&[rbp+0x1E0], rcx=rbx). If [rbp+0x1E0] non-null, calls sub_eea6040 (vtable slot 0) with edx=1. Then cleans up [rbp+0x400]: if non-null, sets byte +0x10=1, saves [rbp+0x408] to rax, jumps to exit. Else cleans up [rbp+0x408] via shared_ptr destruction. Saves rdi/rax to [rbp+0x180]/[rbp+0x188].

### Phase 44: Buffer Deallocation & Next Section (0x6666af8..0x6666c4e, 40 ins)
```
0x6666af8  mov [rbp+0x180],rdi                           
0x6666aff  mov [rbp+0x188],rax                           
0x6666b06  mov rcx,[rbp+0x4E8]                           
0x6666b0d  test rcx,rcx                                  
0x6666b10  je short 0x6666B46                            ; -> loc_6666b46
0x6666b12  mov rdx,[rbp+0x4F8]                           
0x6666b19  sub rdx,rcx                                   
0x6666b1c  cmp rdx,0x1000                                
0x6666b23  jb short 0x6666B41                            ; -> loc_6666b41
0x6666b25  mov rax,[rcx-8]                               
0x6666b29  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6666b2d  sub rcx,rax                                   
0x6666b30  cmp rcx,0x20                                  
0x6666b34  jae 0x6668219                                 ; -> loc_6668219
0x6666b3a  add rdx,0x27                                  
0x6666b3e  mov rcx,rax                                   
0x6666b41  call 0xE935700                                ; -> sub_e935700
0x6666b46  mov rsi,[r14]                                 
0x6666b49  mov rax,[rbp+0x4D0]                           
0x6666b50  xorps xmm0,xmm0                               
0x6666b53  movaps [rbp+0x1E0],xmm0                       
0x6666b5a  mov rcx,[rax+8]                               
0x6666b5e  test rcx,rcx                                  
0x6666b61  je short 0x6666BAA                            ; -> loc_6666baa
0x6666b63  lock inc dword ptr [rcx+8]                    
0x6666b67  mov rdi,[rbp+0x1E8]                           
0x6666b6e  movups xmm0,[rax]                             
0x6666b71  movaps [rbp+0x1E0],xmm0                       
0x6666b78  test rdi,rdi                                  
0x6666b7b  je short 0x6666BBF                            ; -> loc_6666bbf
0x6666b7d  lock dec dword ptr [rdi+8]                    
0x6666b81  jne short 0x6666BBF                           ; -> loc_6666bbf
0x6666b83  mov rax,[rdi]                                 
0x6666b86  mov rax,[rax]                                 
0x6666b89  mov rcx,rdi                                   
0x6666b8c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666b92  lock dec dword ptr [rdi+0xC]                  
0x6666b96  jne short 0x6666BBF                           ; -> loc_6666bbf
0x6666b98  mov rax,[rdi]                                 
0x6666b9b  mov rax,[rax+8]                               
0x6666b9f  mov rcx,rdi                                   
0x6666ba2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666ba8  jmp short 0x6666BBF                           ; -> loc_6666bbf
0x6666baa  mov rax,[rax]                                 
0x6666bad  mov [rbp+0x1E0],rax                           
0x6666bb4  mov qword ptr [rbp+0x1E8],0                   
```
Purpose: Checks [rbp+0x4E8] (copySrcB buffer from Phase 35): if non-null, computes size, if >= 0x1000 validates header, calls sub_e935700 (deallocator). Then loads rsi=[r14] (arg1), rax=[rbp+0x4D0] (resource from Phase 17). Zeros [rbp+0x1E0]. Loads rcx=[rax+8] (refcounted resource). If null, jumps to loc_6666baa (sets [rbp+0x1E0]=[rax], zeros [rbp+0x1E8]). Else increments refcount, loads rdi=[rbp+0x1E8], copies xmm from [rax] to [rbp+0x1E0]. Standard shared_ptr cleanup for rdi.

### Phase 45: Shared Resource Cleanup & Call (0x6666bbf..0x6666c4e, 40 ins)
```
0x6666bbf  mov rax,[rbp+0x1E0]                           
0x6666bc6  mov rax,[rax+0x18]                            
0x6666bca  mov rax,[rax]                                 
0x6666bcd  mov [rbp+0xE0],rax                            
0x6666bd4  lea rcx,[rbp+0xE8]                            
0x6666bdb  mov r8,[rsi]                                  
0x6666bde  mov rdx,[rax+0x170]                           
0x6666be5  call 0xE86B370                                ; -> sub_e86b370
0x6666bea  nop                                           
0x6666beb  mov [rbp+0x160],rsi                           
0x6666bf2  mov rdi,[rbp+0x1E8]                           
0x6666bf9  test rdi,rdi                                  
0x6666bfc  je short 0x6666C29                            ; -> loc_6666c29
0x6666bfe  lock dec dword ptr [rdi+8]                    
0x6666c02  jne short 0x6666C29                           ; -> loc_6666c29
0x6666c04  mov rax,[rdi]                                 
0x6666c07  mov rax,[rax]                                 
0x6666c0a  mov rcx,rdi                                   
0x6666c0d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666c13  lock dec dword ptr [rdi+0xC]                  
0x6666c17  jne short 0x6666C29                           ; -> loc_6666c29
0x6666c19  mov rax,[rdi]                                 
0x6666c1c  mov rax,[rax+8]                               
0x6666c20  mov rcx,rdi                                   
0x6666c23  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666c29  mov eax,[0x129F8F60]                          ; [data_129f8f60]
0x6666c2f  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6666c35  mov rdx,gs:[0x58]                             
0x6666c3e  mov rcx,[rdx+rcx*8]                           
0x6666c42  cmp eax,[rcx+4]                               
0x6666c48  jg 0x66683DD                                  ; -> loc_66683dd
```
Purpose: Loads rax=[[rbp+0x1E0]+0x18] (resource), stores to [rbp+0xE0]. Calls sub_e86b370 with rcx=&[rbp+0xE8], r8=[rsi], rdx=[rax+0x170]. Saves rsi to [rbp+0x160]. Cleans up [rbp+0x1E8] via shared_ptr destruction (dec +8, call sub_eea6040 slot 0, dec +0xC, call slot 1). TLS guard check against global 0x129F8F60.

### Phase 46: UIImGui Element Array Iteration Setup (0x6666c4e..0x6666d74, 40 ins)
```
0x6666c4e  mov rsi,[rbp+0x520]                           
0x6666c55  lea r9,[rsi+0x38]                             
0x6666c59  lea r8,[0x129F8F58]                           ; [data_129f8f58]
0x6666c60  lea rdx,[rbp+0x1E0]                           
0x6666c67  lea rcx,[rbp+0xE8]                            
0x6666c6e  call 0x56D55E0                                ; -> sub_56d55e0
0x6666c73  nop                                           
0x6666c74  mov rax,[rsi+0x28]                            
0x6666c78  mov r15,[rsi+0x30]                            
0x6666c7c  lea rax,[rax+rax*4]                           
0x6666c80  lea rax,[r15+rax*8]                           
0x6666c84  mov [rbp+0x518],rax                           
0x6666c8b  lea rdi,[rbp+0x1E2]                           
0x6666c92  lea rbx,[rbp+0x58]                            
0x6666c96  xorps xmm6,xmm6                               
0x6666c99  mov [rbp+0x28],r14                            
0x6666c9d  mov [rbp+0x1D8],r13                           
0x6666ca4  jmp short 0x6666CBF                           ; -> loc_6666cbf
0x6666cb0  add r15,0x28                                  
0x6666cb4  lea rdi,[rbp+0x1E2]                           
0x6666cbb  lea rbx,[rbp+0x58]                            
0x6666cbf  cmp r15,[rbp+0x518]                           
0x6666cc6  je 0x66678C7                                  ; -> loc_66678c7
0x6666ccc  movups xmm7,[r15]                             
0x6666cd0  mov eax,[r15+0x10]                            
0x6666cd4  mov ecx,[r15+0x14]                            
0x6666cd8  movaps [rbp+0x4E0],xmm6                       
0x6666cdf  mov rdx,[rbp+0x188]                           
0x6666ce6  test rdx,rdx                                  
0x6666ce9  je short 0x6666D00                            ; -> loc_6666d00
0x6666ceb  lock inc dword ptr [rdx+8]                    
0x6666cef  mov rdx,[rbp+0x188]                           
0x6666cf6  jmp short 0x6666D02                           ; -> loc_6666d02
```
Purpose: **Rebinds rsi=[rbp+0x520] (desc base)** per oc_U-D8b-imgui2.md. Calls sub_56d55e0 with r9=&desc+0x38, r8=0x129F8F58, rdx=&[rbp+0x1E0], rcx=&[rbp+0xE8]. Then reads desc+0x28 (elemCount) -> rax, desc+0x30 (elemArray) -> r15. Computes end = r15 + rax*5*8 = r15 + rax*40, stores to [rbp+0x518]. This matches oc_U-D8b-imgui2.md: element size 0x28 (40 bytes), count at +0x28, array at +0x30. Sets up loop: r15=cursor, rdi=&[rbp+0x1E2], rbx=&[rbp+0x58]. Loop head at 0x6666cbf: cmp r15,[rbp+0x518] / je exit. Per element: loads xmm7=[r15], eax=[r15+0x10], ecx=[r15+0x14]. Zeros [rbp+0x4E0]. Increments refcount of [rbp+0x188] if non-null.

### Phase 47: Per-Element Refcount & Call Setup (0x6666d00..0x6666e1f, 40 ins)
```
0x6666d00  xor edx,edx                                   
0x6666d02  mov r8,[rbp+0x180]                            
0x6666d09  mov [rbp+0x4E0],r8                            
0x6666d10  mov [rbp+0x4E8],rdx                           
0x6666d17  movaps [rbp+0x30],xmm6                        
0x6666d1b  mov rdx,[rbp+0x178]                           
0x6666d22  test rdx,rdx                                  
0x6666d25  je short 0x6666D40                            ; -> loc_6666d40
0x6666d27  lock inc dword ptr [rdx+8]                    
0x6666d2b  mov rdx,[rbp+0x178]                           
0x6666d32  jmp short 0x6666D42                           ; -> loc_6666d42
0x6666d40  xor edx,edx                                   
0x6666d42  mov r8,[rbp+0x170]                            
0x6666d49  mov [rbp+0x30],r8                             
0x6666d4d  mov [rbp+0x38],rdx                            
0x6666d51  mov rdx,[r14]                                 
0x6666d54  mov [rsp+0x30],eax                            
0x6666d58  mov [rsp+0x28],rcx                            
0x6666d5d  mov [rsp+0x20],r12                            
0x6666d62  lea rcx,[rbp+0x3A0]                           
0x6666d69  lea r8,[rbp+0x30]                             
0x6666d6d  lea r9,[rbp+0x4E0]                            
0x6666d74  call 0x66B2730                                ; -> sub_66b2730
```
Purpose: Sets up per-element call to sub_66b2730. If [rbp+0x188] was non-null, stores it to [rbp+0x4E0]/[rbp+0x4E8]; else zeros. Zeros [rbp+0x30]. If [rbp+0x178] non-null, increments refcount. Stores [rbp+0x170] to [rbp+0x30], [rbp+0x178] to [rbp+0x38]. Loads rdx=[r14] (arg1). Stack args: eax (element+0x10), rcx (element+0x14), r12. Calls sub_66b2730 with rcx=&[rbp+0x3A0], r8=&[rbp+0x30], r9=&[rbp+0x4E0].

### Phase 48: Array Search & Per-Element bcaba00 Call (0x6666d79..0x6666f58, 40 ins)
```
0x6666d79  nop                                           
0x6666d7a  mov rax,[rbp+0x128]                           
0x6666d81  movzx r8d,word ptr [rbp+0x132]                
0x6666d89  mov ecx,r8d                                   
0x6666d8c  shl ecx,4                                     
0x6666d8f  lea rdx,[rcx+rcx*2]                           
0x6666d93  mov rcx,rax                                   
0x6666d96  test r8,r8                                    
0x6666d99  je short 0x6666DD0                            ; -> loc_6666dd0
0x6666d9b  mov r8,[0x129F8318]                           ; [data_129f8318]
0x6666da2  mov r9,rdx                                    
0x6666da5  mov rcx,rax                                   
0x6666da8  nop [rax+rax]                                 
0x6666db0  mov r10,[rcx]                                 
0x6666db3  cmp [r10+0x28],r8                             
0x6666db7  je short 0x6666DD0                            ; -> loc_6666dd0
0x6666db9  add rcx,0x30                                  
0x6666dbd  add r9,0xFFFFFFFFFFFFFFD0                     
0x6666dc1  jne short 0x6666DB0                           ; -> loc_6666db0
0x6666dc3  jmp short 0x6666E1F                           ; -> loc_6666e1f
0x6666dd0  add rdx,rax                                   
0x6666dd3  cmp rcx,rdx                                   
0x6666dd6  jae short 0x6666E1F                           ; -> loc_6666e1f
0x6666dd8  lea r8,[r15+0x18]                             
0x6666ddc  sub ecx,eax                                   
0x6666dde  shr ecx,4                                     
0x6666de1  imul eax,ecx,0xFFFFAAAB                       
0x6666de7  mov [rbp+0x400],ax                            
0x6666dee  mov byte ptr [rbp+0x402],1                    
0x6666df5  mov byte ptr [rbp+0x1EC],0                    
0x6666dfc  mov dword ptr [rsp+0x20],0                    
0x6666e04  lea rcx,[rbp+0xE0]                            
0x6666e0b  lea rdx,[rbp+0x400]                           
0x6666e12  lea r9,[rbp+0x1E0]                            
0x6666e19  call 0xBCABA00                                ; -> sub_bcaba00
0x6666e1e  nop                                           
0x6666e1f  mov esi,[r13+0x3B0]                           
0x6666e26  inc esi                                       
0x6666e28  mov [r13+0x3B0],si                            
0x6666e30  mov rax,[rbp+0xE0]                            
0x6666e37  mov r8,[rbp+0xE8]                             
0x6666e3e  mov [rbp+0x50],rax                            
0x6666e42  mov rcx,rbx                                   
0x6666e45  lea rdx,[rbp+0xE8]                            
0x6666e4c  call 0xE86B370                                ; -> sub_e86b370
```
Purpose: Searches array at [rbp+0x128] (count at [rbp+0x132], stride 0x30) for entry matching [0x129F8318] at +0x28. If found, computes index: (rcx - rax) / 0x30? Actually sub ecx,eax / shr ecx,4 / imul eax,ecx,0xFFFFAAAB (divide by 16). Stores index to [rbp+0x400]. Sets flags. Calls sub_bcaba00 (Item visitor) with rcx=&[rbp+0xE0], rdx=&[rbp+0x400], r9=&[rbp+0x1E0]. Then increments counter at [r13+0x3B0]. Calls sub_e86b370 with rcx=rbx, rdx=&[rbp+0xE8], r8=[rbp+0xE0].

### Phase 49: Large Structure Initialization & Call (0x6666f58..0x6667047, 40 ins)
```
0x6666f58  nop                                           
0x6666f59  mov rax,[rbp+0xD0]                            
0x6666f60  mov [rbp+0x2C0],rax                           
0x6666f67  mov qword ptr [rbp+0xD0],0                    
0x6666f72  mov dword ptr [rbp+0x2C8],0x3F800000          
0x6666f7c  movups [rdi+0xEA],xmm6                        
0x6666f83  mov dword ptr [rbp+0x2DC],0x3F800000          
0x6666f8d  movups [rdi+0xFE],xmm6                        
0x6666f94  mov dword ptr [rbp+0x2F0],0x3F800000          
0x6666f9e  movups [rdi+0x112],xmm6                       
0x6666fa5  mov dword ptr [rbp+0x304],0x3F800000          
0x6666faf  mov byte ptr [rbp+0x308],0                    
0x6666fb6  movaps xmm0,[rbp+0x3A0]                       
0x6666fbd  movaps xmm1,[rbp+0x3B0]                       
0x6666fc4  mov qword ptr [rbp+0x3A8],0                   
0x6666fcf  movups [rbp+0x310],xmm0                       
0x6666fd6  movaps [rbp+0x3B0],xmm6                       
0x6666fdd  movups [rbp+0x320],xmm1                       
0x6666fe4  mov rax,[rbp+0x3C0]                           
0x6666feb  mov [rbp+0x330],rax                           
0x6666ff2  mov byte ptr [rbp+0x348],0xFF                 
0x6666ff9  movzx eax,byte ptr [rbp+0x3D8]                
0x6667000  cmp rax,3                                     
0x6667004  ja short 0x6667076                            ; -> loc_6667076
0x6667006  lea rdx,[0xF2BF47C]                           ; [data_f2bf47c]
0x666700d  movsxd rcx,[rdx+rax*4]                        
0x6667011  add rcx,rdx                                   
0x6667014  jmp rcx                                       
0x6667016  mov rcx,[rbp+0x3C8]                           
0x666701d  mov [rbp+0x338],rcx                           
0x6667024  jmp short 0x6667070                           ; -> loc_6667070
0x6667026  lea rcx,[rbp+0x3C8]                           
0x666702d  movups xmm0,[rcx]                             
0x6667030  movups [rdi+0x156],xmm0                       
0x6667037  jmp short 0x6667070                           ; -> loc_6667070
0x6667039  movups [rdi+0x156],xmm6                       
0x6667040  mov rcx,[rbp+0x3D0]                           
0x6667047  test rcx,rcx                                  
```
Purpose: Initializes large structure at [rbp+0x2C0..0x348]. Sets [rbp+0x2C0]=[rbp+0xD0], zeros [rbp+0xD0]. Sets multiple dwords to 1.0 (0x3F800000) at +0x2C8, +0x2DC, +0x2F0, +0x304. Stores xmm6 (zero) to rdi+0xEA, rdi+0xFE, rdi+0x112. Sets [rbp+0x308]=0. Moves matrix from [rbp+0x3A0]/[rbp+0x3B0] to [rbp+0x310]/[rbp+0x320], zeros [rbp+0x3A8]/[rbp+0x3B0]. Sets [rbp+0x330]=[rbp+0x3C0], [rbp+0x348]=0xFF. Switch on byte [rbp+0x3D8] (0-3) via jump table at 0xF2BF47C. Cases: 0: mov [rbp+0x3C8] -> [rbp+0x338]; 1: copy 16 bytes from [rbp+0x3C8] to rdi+0x156; 2: store xmm6 to rdi+0x156; 3: test [rbp+0x3D0].

---

## Updated String Reference Table (Phase 0-49)

| String RVA | Text | Call Site RVA | Callee After |
|------------|------|---------------|--------------|
| 0xF5AD096 | "Debug/ImGui" | 0x6664ae9 (lea rax) | 0x675E440 (sub_675e440) |
| 0xF539A95 | "UI/Blit" | 0x6664d8f (lea rax) | 0x675E440 (sub_675e440) |
| 0xF58B3B6 | "Unnamed Transaction" | 0x6665986, 0x6666432 (movups xmm0) | 0xEEC6E70 (sub_eec6e70) |
| 0xF58B3C5 | "tion" | 0x666597d, 0x6666429 (mov eax) | 0xEEC6E70 (sub_eec6e70) |
| 0xF8407B6 | (format string) | 0x6665d92, 0x666673e (lea r9) | 0xA0850 (sub_a0850) |

## Updated [reg+off] Write Table (Non-Stack, Output Descriptions/Records)

| Offset | Size | Source | Instruction (RVA) | Meaning | Tag |
|--------|------|--------|-------------------|---------|-----|
| [rbp+0x50] | 8 | r15 | 0x66666b3 | Large alloc ptr | [V] |
| [rbp+0x60] | 8 | rbx | 0x66666b7 | Size | [V] |
| [rbp+0x68] | 8 | r12 | 0x66666bb | Capacity | [V] |
| [r15+rbx] | 1 | 0 | 0x66666cd | Null terminator | [V] |
| [rbp+0x3A0] | 16 | 0 | 0x66666d5 | Zero | [V] |
| [rbp+0x3B0] | 8 | 1 | 0x66666dc | Len | [V] |
| [rbp+0x3B8] | 8 | 0xF | 0x66666e7 | Cap | [V] |
| [rbp+0x3A0] | 1 | 0x3C | 0x66666f2 | Byte init | [V] |
| [rdi+0x10] | 8 | 0 | 0x6666797 | Reset len | [V] |
| [rdi+0x18] | 8 | 0xF | 0x666679f | Reset cap | [V] |
| [rdi+0x00] | 1 | 0 | 0x66667a7 | Reset char | [V] |
| [rbp+0x410] | 16 | [rdi+0x10] | 0x6666789 | Save xmm1 | [V] |
| [rbp+0x400] | 16 | [rdi] | 0x6666790 | Save xmm0 | [V] |
| [rdx+rax] | 2 | 0x203E | 0x6666777 | Write "> " | [V] |
| [rdx+rax+2] | 1 | 0 | 0x666677d | Null | [V] |
| [rbp+0xF0] | 8 | rdx | 0x6666760 | Updated len | [V] |
| [rbp+0x410] | 8 | 0 | 0x666680a | Zero | [V] |
| [rbp+0x418] | 8 | 0xF | 0x6666815 | Cap | [V] |
| [rbp+0x400] | 1 | 0 | 0x6666820 | Char | [V] |
| [rbp+0xF0] | 8 | 0 | 0x666686c | Zero | [V] |
| [rbp+0xF8] | 8 | 0xF | 0x6666877 | Cap | [V] |
| [rbp+0xE0] | 1 | 0 | 0x6666882 | Char | [V] |
| [rdi] | 8 | 0xF0F9C80 | 0x66669a0 | Vtable | [V] |
| [rdi+0x08] | 16 | 0 | 0x66669a3 | Zero | [V] |
| [rdi+0x18] | 16 | 0 | 0x66669b1 | Zero | [V] |
| [rdi+0x18] | 8 | rax | 0x66669ee | Ptr | [V] |
| [rdi+0x58..0x90] | 16x3 | 0 | 0x66669f2..0x66669fe | Zero init | [V] |
| [rdi+0x88] | 8 | 0 | 0x66669fe | Zero | [V] |
| [rdi+0x90] | 8 | 0xF | 0x6666a09 | SSO cap | [V] |
| [rdi+0x98] | 8 | rsi | 0x6666a14 | Link | [V] |
| [rbp+0x1E0] | 8 | 0 | 0x66669e3 | Zero | [V] |
| [rbp+0x1E0] | 8 | rdi | 0x6666a5b | Save object | [V] |
| [rdi+0x10] | 1 | 1 | 0x6666ab2 | Flag | [V] |
| [rbp+0x180] | 8 | rdi | 0x6666af8 | Save | [V] |
| [rbp+0x188] | 8 | rax | 0x6666aff | Save | [V] |
| [rbp+0xE0] | 8 | [[rbp+0x1E0]+0x18] | 0x6666bcd | Resource ptr | [V] |
| [rbp+0x518] | 8 | r15+rax*40 | 0x6666c84 | Array end | [V] |
| [rbp+0x4E0] | 16 | 0 | 0x6666cd8 | Zero | [V] |
| [rbp+0x4E0] | 8 | [rbp+0x180] | 0x6666d09 | Ptr | [V] |
| [rbp+0x4E8] | 8 | [rbp+0x188] | 0x6666d10 | Ptr | [V] |
| [rbp+0x30] | 16 | 0 | 0x6666d17 | Zero | [V] |
| [rbp+0x30] | 8 | [rbp+0x170] | 0x6666d49 | Ptr | [V] |
| [rbp+0x38] | 8 | [rbp+0x178] | 0x6666d4d | Ptr | [V] |
| [rbp+0x50] | 8 | [rbp+0xE0] | 0x6666e3e | Ptr | [V] |
| [rbp+0x2C0] | 8 | [rbp+0xD0] | 0x6666f60 | Ptr | [V] |
| [rbp+0xD0] | 8 | 0 | 0x6666f67 | Zero | [V] |
| [rbp+0x2C8] | 4 | 1.0 | 0x6666f72 | Float | [V] |
| [rdi+0xEA] | 16 | 0 | 0x6666f7c | Zero | [V] |
| [rbp+0x2DC] | 4 | 1.0 | 0x6666f83 | Float | [V] |
| [rdi+0xFE] | 16 | 0 | 0x6666f8d | Zero | [V] |
| [rbp+0x2F0] | 4 | 1.0 | 0x6666f94 | Float | [V] |
| [rdi+0x112] | 16 | 0 | 0x6666f9e | Zero | [V] |
| [rbp+0x304] | 4 | 1.0 | 0x6666fa5 | Float | [V] |
| [rbp+0x308] | 1 | 0 | 0x6666faf | Byte | [V] |
| [rbp+0x310] | 16 | [rbp+0x3A0] | 0x6666fcf | Matrix | [V] |
| [rbp+0x3B0] | 16 | 0 | 0x6666fd6 | Zero | [V] |
| [rbp+0x320] | 16 | [rbp+0x3B0] | 0x6666fdd | Matrix | [V] |
| [rbp+0x330] | 8 | [rbp+0x3C0] | 0x6666feb | Ptr | [V] |
| [rbp+0x348] | 1 | 0xFF | 0x6666ff2 | Byte | [V] |
| [rbp+0x338] | 8 | [rbp+0x3C8] | 0x666701d | Ptr | [V] |
| [rdi+0x156] | 16 | [rbp+0x3C8] | 0x6667030 | Copy | [V] |
| [rdi+0x156] | 16 | 0 | 0x6667039 | Zero | [V] |

---

## Verification
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-I5a2.md` after each chunk.

## TOOL REQUESTS
None.

---

## Step 5 Complete: Instruction-complete listing of 0x6664a00 (next 500 instructions: 0x6667047..0x666792c, 15 phases)
Next chunk: continue from 0x666792c.

### Phase 50: Switch Case Completion & ImGui Context Call (0x6667047..0x66670fd, 40 ins)
```
0x6667047  test rcx,rcx                                  
0x666704a  je short 0x6667059                            ; -> loc_6667059
0x666704c  lock inc dword ptr [rcx+8]                    ; W a0+0x8
0x6667050  mov rcx,[rbp+0x3D0]                           
0x6667057  jmp short 0x666705B                           ; -> loc_666705b
0x6667059  xor ecx,ecx                                   
0x666705b  mov rdx,[rbp+0x3C8]                           
0x6667062  mov [rbp+0x338],rdx                           
0x6667069  mov [rbp+0x340],rcx                           
0x6667070  mov [rbp+0x348],al                            
0x6667076  lea rcx,[rbp+0x3C8]                           
0x666707d  mov rax,[rcx+0x28]                            
0x6667081  mov [rdi+0x17E],rax                           
0x6667088  movups xmm0,[rcx+0x18]                        
0x666708c  movups [rdi+0x16E],xmm0                       
0x6667093  mov rcx,[r14+0x10]                            
0x6667097  mov eax,0x9D0                                 
0x666709c  add rcx,rax                                   
0x666709f  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x66670a4  nop                                           
0x66670a5  mov rbx,rax                                   
0x66670a8  lea rax,[rbp+0x408]                           
0x66670af  movups [rax+0xB0],xmm6                        
0x66670b6  movups [rax+0xA0],xmm6                        
0x66670bd  movups [rax+0x90],xmm6                        
0x66670c4  movups [rax+0x80],xmm6                        
0x66670cb  movups [rax+0x70],xmm6                        
0x66670cf  movups [rax+0x60],xmm6                        
0x66670d3  movups [rax+0x50],xmm6                        
0x66670d7  movups [rax+0x40],xmm6                        
0x66670db  movups [rax+0x30],xmm6                        
0x66670df  movups [rax+0x20],xmm6                        
0x66670e3  movups [rax+0x10],xmm6                        
0x66670e7  movups [rax],xmm6                             
0x66670ea  lea rcx,[rbx+0x780]                           ; R ret@5aba5c0+0x780
0x66670f1  lea rdx,[rbp+0x310]                           
0x66670f8  call 0x675F3B0                                ; -> sub_675f3b0
0x66670fd  nop                                           
```
Purpose: Completes the switch from Phase 49 (case 3 at 0x6667040). If [rbp+0x3D0] non-null, increments refcount at +8. Stores [rbp+0x3C8] to [rbp+0x338], rcx to [rbp+0x340], al to [rbp+0x348]. Loads rax=[rbp+0x3C8+0x28] -> [rdi+0x17E], xmm0=[rbp+0x3C8+0x18] -> [rdi+0x16E]. Calls sub_5aba5c0 (ImGui context) with rcx=[r14+0x10]+0x9D0. Result in rbx. Zeros large area at [rbp+0x408] through [rbp+0x408+0xB0] (12 xmm registers). Calls sub_675f3b0 with rcx=rbx+0x780, rdx=&[rbp+0x310].

### Phase 51: ImGui Draw List Processing - First Section (0x66670fe..0x66671fd, 40 ins)
```
0x66670fe  mov eax,[rbx+0x788]                           ; R ret@5aba5c0+0x788
0x6667104  sub eax,[rbx+0x780]                           ; R ret@5aba5c0+0x780
0x666710a  shr eax,3                                     
0x666710d  imul eax,0xFFFF8BA3                           
0x6667113  dec eax                                       
0x6667115  mov [rbp+0x428],ax                            
0x666711c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667123  mov rax,[rcx]                                 
0x6667126  mov rax,[rax+0x10]                            
0x666712a  mov dl,0x4A                                   
0x666712c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667132  mov [rbp+0x520],al                            
0x6667138  lea rcx,[rbx+0x648]                           ; R ret@5aba5c0+0x648
0x666713f  lea rdx,[rbp+0x2C8]                           
0x6667146  call 0x675FB30                                ; -> sub_675fb30
0x666714b  nop                                           
0x666714c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667153  mov rax,[rcx]                                 
0x6667156  mov rax,[rax+0x10]                            
0x666715a  movzx edx,byte ptr [rbp+0x520]                
0x6667161  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667167  nop                                           
0x6667168  mov qword ptr [rbp+0x400],0x2001000           
0x6667173  mov eax,[rbx+0x650]                           ; R ret@5aba5c0+0x650
0x6667179  sub eax,[rbx+0x648]                           ; R ret@5aba5c0+0x648
0x666717f  shr eax,3                                     
0x6667182  imul eax,0xFFFF8E39                           
0x6667188  dec eax                                       
0x666718a  mov [rbp+0x442],ax                            
0x6667191  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667198  mov rax,[rcx]                                 
0x666719b  mov rax,[rax+0x10]                            
0x666719f  mov dl,0x4A                                   
0x66671a1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66671a7  nop                                           
0x66671a8  mov [rbp+0x520],al                            
0x66671ae  mov rdi,[rbx+0x770]                           ; R ret@5aba5c0+0x770
0x66671b5  cmp rdi,[rbx+0x778]                           ; R ret@5aba5c0+0x778
0x66671bc  je short 0x6667200                            ; -> loc_6667200
0x66671be  mov rax,[rbp+0x240]                           
0x66671c5  mov [rdi],rax                                 ; W *(ret@5aba5c0+0x770)+0x0
0x66671c8  lea rcx,[rdi+8]                               ; R *(ret@5aba5c0+0x770)+0x8
0x66671cc  lea rdx,[rbp+0x248]                           
0x66671d3  call 0xE869FF0                                ; -> sub_e869ff0
0x66671d8  nop                                           
0x66671d9  mov rax,[rbp+0x2C0]                           
0x66671e0  mov [rdi+0x80],rax                            ; W *(ret@5aba5c0+0x770)+0x80
0x66671e7  mov qword ptr [rbp+0x2C0],0                   
0x66671f2  add qword ptr [rbx+0x770],0x88                ; W ret@5aba5c0+0x770
0x66671fd  jmp short 0x6667217                           ; -> loc_6667217
```
Purpose: Processes ImGui draw list data from sub_5aba5c0 result (rbx). Computes count: ([rbx+0x788] - [rbx+0x780]) >> 3, multiplies by magic constant 0xFFFF8BA3 (division), dec, stores to [rbp+0x428]. Allocates via sub_eea6040 (0x4A=74 decimal, likely ImDrawCmd). Calls sub_675fb30 with rcx=rbx+0x648, rdx=&[rbp+0x2C8]. Another allocation (0x4A). Sets [rbp+0x400]=0x2001000. Computes second count: ([rbx+0x650]-[rbx+0x648])>>3 * 0xFFFF8E39, dec, stores to [rbp+0x442]. Third allocation (0x4A). If [rbx+0x770] < [rbx+0x778] (has space), writes [rbp+0x240] to *rdi, calls sub_e869ff0 with rcx=rdi+8, rdx=&[rbp+0x248], writes [rbp+0x2C0] to rdi+0x80, zeros [rbp+0x2C0], advances [rbx+0x770] by 0x88. Else jumps to loc_6667200.

### Phase 52: ImGui Draw List - Alternate Path (0x6667200..0x66672fa, 40 ins)
```
0x6667200  lea rcx,[rbx+0x768]                           ; R ret@5aba5c0+0x768
0x6667207  mov rdx,rdi                                   
0x666720a  lea r8,[rbp+0x240]                            
0x6667211  call 0x6760710                                ; -> sub_6760710
0x6667216  nop                                           
0x6667217  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666721e  mov rax,[rcx]                                 
0x6667221  mov rax,[rax+0x10]                            
0x6667225  movzx edx,byte ptr [rbp+0x520]                
0x666722c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667232  nop                                           
0x6667233  mov eax,[rbx+0x770]                           ; R ret@5aba5c0+0x770
0x6667239  sub eax,[rbx+0x768]                           ; R ret@5aba5c0+0x768
0x666723f  shr eax,3                                     
0x6667242  imul eax,0xFFFFF0F1                           
0x6667248  dec eax                                       
0x666724a  mov [rbp+0x42A],ax                            
0x6667251  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667258  mov rax,[rcx]                                 
0x666725b  mov rax,[rax+0x10]                            
0x666725f  mov dl,0x4A                                   
0x6667261  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667267  nop                                           
0x6667268  mov [rbp+0x520],al                            
0x666726e  mov rdx,[rbx+0x758]                           ; R ret@5aba5c0+0x758
0x6667275  cmp rdx,[rbx+0x760]                           ; R ret@5aba5c0+0x760
0x666727c  je 0x6667300                                  ; -> loc_6667300
0x6667282  lea rcx,[rbp+0x1E8]                           
0x6667289  mov eax,[rcx+0x10]                            
0x666728c  mov [rdx+0x10],eax                            ; W *(ret@5aba5c0+0x758)+0x10
0x666728f  movups xmm0,[rcx]                             
0x6667292  movups [rdx],xmm0                             ; W *(ret@5aba5c0+0x758)+0x0
0x6667295  movzx eax,byte ptr [rbp+0x1FC]                
0x666729c  mov [rdx+0x14],al                             ; W *(ret@5aba5c0+0x758)+0x14
0x66672a7  movss [rdx+0x18],xmm0                         ; W *(ret@5aba5c0+0x758)+0x18
0x66672ac  movss xmm0,[rbp+0x204]                        
0x66672b4  movss [rdx+0x1C],xmm0                         ; W *(ret@5aba5c0+0x758)+0x1C
0x66672b9  movss xmm0,[rbp+0x208]                        
0x66672c1  movss [rdx+0x20],xmm0                         ; W *(ret@5aba5c0+0x758)+0x20
0x66672c6  movss xmm0,[rbp+0x20C]                        
0x66672ce  movss [rdx+0x24],xmm0                         ; W *(ret@5aba5c0+0x758)+0x24
0x66672d3  lea rax,[rbp+0x1E2]                           
0x66672da  movups xmm0,[rax+0x2E]                        
0x66672de  movups xmm1,[rax+0x3E]                        
0x66672e2  movups xmm2,[rax+0x4D]                        
0x66672e6  movups [rdx+0x28],xmm0                        ; W *(ret@5aba5c0+0x758)+0x28
0x66672ea  movups [rdx+0x38],xmm1                        ; W *(ret@5aba5c0+0x758)+0x38
0x66672ee  movups [rdx+0x47],xmm2                        ; W *(ret@5aba5c0+0x758)+0x47
0x66672f2  add qword ptr [rbx+0x758],0x58                ; W ret@5aba5c0+0x758
0x66672fa  jmp short 0x6667314                           ; -> loc_6667314
```
Purpose: Alternate path when [rbx+0x770] == [rbx+0x778] (full). Calls sub_6760710 with rcx=rbx+0x768, rdx=rdi, r8=&[rbp+0x240]. Allocation (0x4A). Computes count: ([rbx+0x770]-[rbx+0x768])>>3 * 0xFFFFF0F1, dec, stores to [rbp+0x42A]. Allocation (0x4A). If [rbx+0x758] < [rbx+0x760], writes vertex data: [rbp+0x1E8+0x10] to +0x10, xmm from [rbp+0x1E8] to +0x0, byte [rbp+0x1FC] to +0x14, floats from [rbp+0x200]/[rbp+0x204]/[rbp+0x208]/[rbp+0x20C] to +0x18/+0x1C/+0x20/+0x24. Then xmm from [rbp+0x1E2+0x2E]/[rbp+0x1E2+0x3E]/[rbp+0x1E2+0x4D] to +0x28/+0x38/+0x47. Advances [rbx+0x758] by 0x58. Else jumps to loc_6667300.

### Phase 53: ImGui Draw List - Third Section (0x6667300..0x66673fa, 40 ins)
```
0x6667300  lea rcx,[rbx+0x750]                           ; R ret@5aba5c0+0x750
0x6667307  lea r8,[rbp+0x1E8]                            
0x666730e  call 0x6760A80                                ; -> sub_6760a80
0x6667313  nop                                           
0x6667314  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666731b  mov rax,[rcx]                                 
0x666731e  mov rax,[rax+0x10]                            
0x6667322  movzx edx,byte ptr [rbp+0x520]                
0x6667329  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666732f  nop                                           
0x6667330  mov qword ptr [rbp+0x400],0x2007000           
0x666733b  mov eax,[rbx+0x758]                           ; R ret@5aba5c0+0x758
0x6667341  sub eax,[rbx+0x750]                           ; R ret@5aba5c0+0x750
0x6667347  shr eax,3                                     
0x666734a  imul eax,0xFFFF8BA3                           
0x6667350  dec eax                                       
0x6667352  mov [rbp+0x42C],ax                            
0x6667359  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667360  mov rax,[rcx]                                 
0x6667363  mov rax,[rax+0x10]                            
0x6667367  mov dl,0x4A                                   
0x6667369  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666736f  nop                                           
0x6667370  mov [rbp+0x520],al                            
0x6667376  mov rdx,[rbx+0x638]                           ; R ret@5aba5c0+0x638
0x666737d  cmp rdx,[rbx+0x640]                           ; R ret@5aba5c0+0x640
0x6667384  je short 0x66673A0                            ; -> loc_66673a0
0x6667386  mov eax,[rbp+0x1E4]                           
0x666738c  mov [rdx],eax                                 ; W *(ret@5aba5c0+0x638)+0x0
0x666738e  add qword ptr [rbx+0x638],4                   ; W ret@5aba5c0+0x638
0x6667396  jmp short 0x66673B4                           ; -> loc_66673b4
0x66673a0  lea rcx,[rbx+0x630]                           ; R ret@5aba5c0+0x630
0x66673a7  lea r8,[rbp+0x1E4]                            
0x66673ae  call 0x14DB710                                ; -> sub_14db710
0x66673b3  nop                                           
0x66673b4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x66673bb  mov rax,[rcx]                                 
0x66673be  mov rax,[rax+0x10]                            
0x66673c2  movzx edx,byte ptr [rbp+0x520]                
0x66673c9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66673cf  nop                                           
0x66673d0  mov eax,[rbx+0x638]                           ; R ret@5aba5c0+0x638
0x66673d6  sub eax,[rbx+0x630]                           ; R ret@5aba5c0+0x630
0x66673dc  shr eax,2                                     
0x66673df  dec eax                                       
0x66673e1  mov [rbp+0x444],ax                            
0x66673e8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x66673ef  mov rax,[rcx]                                 
0x66673f2  mov rax,[rax+0x10]                            
0x66673f6  mov dl,0x4A                                   
0x66673f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66673fe  nop                                           
0x66673ff  mov [rbp+0x520],al                            
```
Purpose: Calls sub_6760a80 with rcx=rbx+0x750, r8=&[rbp+0x1E8]. Allocation (0x4A), sets [rbp+0x400]=0x2007000. Computes count: ([rbx+0x758]-[rbx+0x750])>>3 * 0xFFFF8BA3, dec, stores to [rbp+0x42C]. Allocation (0x4A). If [rbx+0x638] < [rbx+0x640], writes [rbp+0x1E4] to *rdx, advances [rbx+0x638] by 4. Else calls sub_14db710 with rcx=rbx+0x630, r8=&[rbp+0x1E4]. Allocation (0x4A). Computes count: ([rbx+0x638]-[rbx+0x630])>>2, dec, stores to [rbp+0x444]. Allocation (0x4A).

### Phase 54: ImGui Draw List - Fourth Section (0x66673ff..0x66674eb, 40 ins)
```
0x66673ff  mov [rbp+0x520],al                            
0x6667405  mov rdx,[rbx+0x698]                           ; R ret@5aba5c0+0x698
0x666740c  cmp rdx,[rbx+0x6A0]                           ; R ret@5aba5c0+0x6A0
0x6667413  je short 0x6667430                            ; -> loc_6667430
0x6667415  movzx eax,word ptr [rbp+0x1E2]                
0x666741c  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x698)+0x0
0x666741f  add qword ptr [rbx+0x698],2                   ; W ret@5aba5c0+0x698
0x6667427  jmp short 0x6667444                           ; -> loc_6667444
0x6667430  lea rcx,[rbx+0x690]                           ; R ret@5aba5c0+0x690
0x6667437  lea r8,[rbp+0x1E2]                            
0x666743e  call 0x1EF6F90                                ; -> sub_1ef6f90
0x6667443  nop                                           
0x6667444  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666744b  mov rax,[rcx]                                 
0x666744e  mov rax,[rax+0x10]                            
0x6667452  movzx edx,byte ptr [rbp+0x520]                
0x6667459  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666745f  nop                                           
0x6667460  mov qword ptr [rbp+0x400],0x6407000           
0x666746b  mov eax,[rbx+0x698]                           ; R ret@5aba5c0+0x698
0x6667471  sub eax,[rbx+0x690]                           ; R ret@5aba5c0+0x690
0x6667477  shr eax,1                                     
0x6667479  dec eax                                       
0x666747b  mov [rbp+0x43C],ax                            
0x6667482  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667489  mov rax,[rcx]                                 
0x666748c  mov rax,[rax+0x10]                            
0x6667490  mov dl,0x4A                                   
0x6667492  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667498  nop                                           
0x6667499  mov [rbp+0x520],al                            
0x666749f  mov rdx,[rbx+0x818]                           ; R ret@5aba5c0+0x818
0x66674a6  cmp rdx,[rbx+0x820]                           ; R ret@5aba5c0+0x820
0x66674ad  je short 0x66674C0                            ; -> loc_66674c0
0x66674af  inc rdx                                       
0x66674b2  mov [rbx+0x818],rdx                           ; W ret@5aba5c0+0x818
0x66674b9  jmp short 0x66674D0                           ; -> loc_66674d0
0x66674c0  mov rcx,rbx                                   
0x66674c3  add rcx,0x810                                 
0x66674ca  call 0x6760E60                                ; -> sub_6760e60
0x66674cf  nop                                           
0x66674d0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x66674d7  mov rax,[rcx]                                 
0x66674da  mov rax,[rax+0x10]                            
0x66674de  movzx edx,byte ptr [rbp+0x520]                
0x66674e5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66674eb  nop                                           
```
Purpose: If [rbx+0x698] < [rbx+0x6A0], writes word [rbp+0x1E2] to *rdx, advances [rbx+0x698] by 2. Else calls sub_1ef6f90 with rcx=rbx+0x690, r8=&[rbp+0x1E2]. Sets [rbp+0x400]=0x6407000. Computes count: ([rbx+0x698]-[rbx+0x690])>>1, dec, stores to [rbp+0x43C]. Allocation (0x4A). If [rbx+0x818] < [rbx+0x820], increments [rbx+0x818]. Else calls sub_6760e60 with rcx=rbx+0x810. Allocation (0x4A).

### Phase 55: Buffer Management & Loop Setup (0x66674eb..0x66675e0, 40 ins)
```
0x66674ec  mov eax,[rbx+0x810]                           ; R ret@5aba5c0+0x810
0x66674f2  not eax                                       
0x66674f4  add eax,[rbx+0x818]                           ; R ret@5aba5c0+0x818
0x66674fa  mov [rbp+0x41C],ax                            
0x6667501  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667508  mov rax,[rcx]                                 
0x666750b  mov rax,[rax+0x10]                            
0x666750f  mov dl,0x4A                                   
0x6667511  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667517  nop                                           
0x6667518  mov edx,eax                                   
0x666751a  mov rax,r14                                   
0x666751d  mov r14,r15                                   
0x6667520  mov r15,[rbx+0x3B0]                           ; R ret@5aba5c0+0x3B0
0x6667527  cmp r15,[rbx+0x3B8]                           ; R ret@5aba5c0+0x3B8
0x666752e  je short 0x6667550                            ; -> loc_6667550
0x6667530  inc r15                                       
0x6667533  mov [rbx+0x3B0],r15                           ; W ret@5aba5c0+0x3B0
0x666753a  mov r15,r14                                   
0x666753d  mov r14,rax                                   
0x6667540  jmp 0x66676F8                                 ; -> loc_66676f8
0x6667550  mov r12,r15                                   
0x6667553  sub r12,[rbx+0x3A8]                           ; R ret@5aba5c0+0x3A8
0x666755a  mov rcx,0x7FFFFFFFFFFFFFFF                    
0x6667564  cmp r12,rcx                                   
0x6667567  mov [rbp+0x520],dl                            
0x666756d  je 0x6668213                                  ; -> loc_6668213
0x6667573  lea r8,[r12+1]                                
0x6667578  mov r13,r12                                   
0x666757b  shr r13,1                                     
0x666757e  mov rax,r13                                   
0x6667581  xor rax,rcx                                   
0x6667584  add r13,r12                                   
0x6667587  cmp r13,r8                                    
0x666758a  mov [rbp+0x510],r8                            
0x6667591  cmovbe r13,r8                                 
0x6667595  cmp r12,rax                                   
0x6667598  cmova r13,rcx                                 
0x666759c  test r13,r13                                  
0x666759f  je 0x666765A                                  ; -> loc_666765a
0x66675a5  cmp r13,0x1000                                
0x66675ac  jb short 0x66675FA                            ; -> loc_66675fa
0x66675ae  cmp r13,0xFFFFFFFFFFFFFFD9                    
0x66675b2  jae 0x66682F9                                 ; -> loc_66682f9
0x66675b8  lea rsi,[r13+0x27]                            
0x66675bc  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x66675c3  mov rax,[rcx]                                 
0x66675c6  mov rax,[rax+8]                               
0x66675ca  mov rdx,rsi                                   
0x66675cd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66675d3  nop                                           
0x66675d4  mov rdi,rax                                   
0x66675d7  test rax,rax                                  
0x66675da  je 0x66678B9                                  ; -> loc_66678b9
0x66675e0  mov rax,rdi                                   
0x66675e3  add rdi,0x27                                  
0x66675e7  and rdi,0xFFFFFFFFFFFFFFE0                    
0x66675eb  mov [rdi-8],rax                               
```
Purpose: Computes [rbp+0x41C] = ~[rbx+0x810] + [rbx+0x818]. Allocation (0x4A). Saves r14->r15, loads r15=[rbx+0x3B0]. If r15 < [rbx+0x3B8], increments [rbx+0x3B0], swaps r15/r14/rax, jumps to loc_66676f8. Else (r15 == [rbx+0x3B8]): computes r12 = r15 - [rbx+0x3A8]. If r12 == MAX_INT64, error. Computes growth: r8=r12+1, r13=r12/2, checks overflow, stores r8 to [rbp+0x510]. If r13==0, jumps to loc_666765a. If r13 >= 0x1000, allocates via sub_eea6040 with size+0x27 aligned; stores original ptr at [rdi-8]. Else smaller alloc at 0x66675fa.

### Phase 56: Buffer Growth & Copy (0x66675e0..0x66676f8, 40 ins)
```
0x66675e0  mov rax,rdi                                   
0x66675e3  add rdi,0x27                                  
0x66675e7  and rdi,0xFFFFFFFFFFFFFFE0                    
0x66675eb  mov [rdi-8],rax                               
0x66675ef  cmp r15,[rbx+0x3B0]                           ; R ret@5aba5c0+0x3B0
0x66675f6  jne short 0x6667623                           ; -> loc_6667623
0x66675f8  jmp short 0x6667665                           ; -> loc_6667665
0x66675fa  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6667601  mov rax,[rcx]                                 
0x6667604  mov rax,[rax+8]                               
0x6667608  mov rdx,r13                                   
0x666760b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667611  nop                                           
0x6667612  mov rdi,rax                                   
0x6667615  test rax,rax                                  
0x6667618  je short 0x6667651                            ; -> loc_6667651
0x666761a  cmp r15,[rbx+0x3B0]                           
0x6667621  je short 0x6667665                            ; -> loc_6667665
0x6667623  lea rsi,[rdi+r12]                             
0x6667627  inc rsi                                       
0x666762a  mov rdx,[rbx+0x3A8]                           
0x6667631  mov r8,r15                                    
0x6667634  sub r8,rdx                                    
0x6667637  mov rcx,rdi                                   
0x666763a  call 0xEEC6DE0                                ; -> sub_eec6de0
0x666763f  mov r8,[rbx+0x3B0]                            
0x6667646  sub r8,r15                                    
0x6667649  mov rcx,rsi                                   
0x666764c  mov rdx,r15                                   
0x666764f  jmp short 0x6667675                           ; -> loc_6667675
0x6667651  mov rcx,r13                                   
0x6667654  call 0x9BC830                                 ; -> sub_9bc830
0x6667659  nop                                           
0x666765a  xor edi,edi                                   
0x666765c  cmp r15,[rbx+0x3B0]                           
0x6667663  jne short 0x6667623                           ; -> loc_6667623
0x6667665  mov rdx,[rbx+0x3A8]                           
0x666766c  sub r15,rdx                                   
0x666766f  mov rcx,rdi                                   
0x6667672  mov r8,r15                                    
0x6667675  call 0xEEC6DE0                                ; -> sub_eec6de0
0x666767a  mov r12,[rbp+0x508]                           
0x6667681  mov rcx,[rbx+0x3A8]                           
0x6667688  test rcx,rcx                                  
0x666768b  mov r15,r14                                   
0x666768e  je short 0x66676C4                            ; -> loc_66676c4
0x6667690  mov rdx,[rbx+0x3B8]                           
0x6667697  sub rdx,rcx                                   
0x666769a  cmp rdx,0x1000                                
0x66676a1  jb short 0x66676BF                            ; -> loc_66676bf
0x66676a3  mov rax,[rcx-8]                               
0x66676a7  add rcx,0xFFFFFFFFFFFFFFF8                    
0x66676ab  sub rcx,rax                                   
0x66676ae  cmp rcx,0x20                                  
0x66676b2  jae 0x6668219                                 ; -> loc_6668219
0x66676b8  add rdx,0x27                                  
0x66676bc  mov rcx,rax                                   
0x66676bf  call 0xE935700                                ; -> sub_e935700
0x66676c4  mov [rbx+0x3A8],rdi                           
0x66676cb  mov rax,[rbp+0x510]                           
0x66676d2  add rax,rdi                                   
0x66676d5  mov [rbx+0x3B0],rax                           
0x66676dc  add r13,rdi                                   
0x66676df  mov [rbx+0x3B8],r13                           
0x66676e6  mov r14,[rbp+0x28]                            
0x66676ea  mov r13,[rbp+0x1D8]                           
0x66676f1  movzx edx,byte ptr [rbp+0x520]                
0x66676f8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```
Purpose: After allocation, stores original ptr at [rdi-8]. If [rbx+0x3B0] changed, jumps to copy path. Else jumps to loc_6667665. Small alloc path at 0x66675fa. Allocation failure -> sub_9bc830. If alloc succeeded but [rbx+0x3B0] changed, copies old data: rsi=rdi+r12+1, calls sub_eec6de0 (memcpy). Then copies remaining: r8=[rbx+0x3B0]-r15, rcx=rsi, rdx=r15, calls sub_eec6de0. If old buffer existed ([rbx+0x3A8]!=0), deallocates via sub_e935700. Updates [rbx+0x3A8]=rdi, [rbx+0x3B0]=rdi+r8, [rbx+0x3B8]=r13+rdi. Restores r14=[rbp+0x28], r13=[rbp+0x1D8]. Loads byte [rbp+0x520] to edx.

### Phase 57: Final Allocations & Buffer Write (0x66676f8..0x66677fc, 40 ins)
```
0x66676f8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x66676ff  mov rax,[rcx]                                 
0x6667702  mov rax,[rax+0x10]                            
0x6667706  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666770c  nop                                           
0x666770d  mov rax,0x20000006407040                      
0x6667717  mov [rbp+0x400],rax                           
0x666771e  mov eax,[rbx+0x3A8]                           
0x6667724  not eax                                       
0x6667726  add eax,[rbx+0x3B0]                           
0x666772c  mov [rbp+0x47A],ax                            
0x6667733  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x666773a  mov rax,[rcx]                                 
0x666773d  mov rax,[rax+0x10]                            
0x6667741  mov dl,0x4A                                   
0x6667743  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667749  nop                                           
0x666774a  mov [rbp+0x520],al                            
0x6667750  mov rdx,[rbx+8]                               
0x6667754  cmp rdx,[rbx+0x10]                            
0x6667758  je short 0x6667780                            ; -> loc_6667780
0x666775a  mov r8d,0xC8                                  
0x6667760  mov rcx,rdx                                   
0x6667763  lea rdx,[rbp+0x400]                           
0x666776a  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x666776f  add qword ptr [rbx+8],0xC8                    
0x6667777  jmp short 0x6667790                           ; -> loc_6667790
0x6667780  mov rcx,rbx                                   
0x6667783  lea r8,[rbp+0x400]                            
0x666778a  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x666778f  nop                                           
0x6667790  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667797  mov rax,[rcx]                                 
0x666779a  mov rax,[rax+0x10]                            
0x666779e  movzx edx,byte ptr [rbp+0x520]                
0x66677a5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66677ab  nop                                           
0x66677ac  lea rcx,[rbp+0x1E0]                           
0x66677b3  call 0x66A65B0                                ; -> sub_66a65b0
0x66677b8  cmp byte ptr [rbp+0x1D0],1                    
0x66677bf  jne short 0x6667801                           ; -> loc_6667801
0x66677c1  mov rcx,[rbp+0x190]                           
0x66677c8  test rcx,rcx                                  
0x66677cb  je short 0x6667801                            ; -> loc_6667801
0x66677cd  mov rdx,[rbp+0x1A0]                           
0x66677d4  sub rdx,rcx                                   
0x66677d7  cmp rdx,0x1000                                
0x66677de  jb short 0x66677FC                            ; -> loc_66677fc
0x66677e0  mov rax,[rcx-8]                               
0x66677e4  add rcx,0xFFFFFFFFFFFFFFF8                    
0x66677e8  sub rcx,rax                                   
0x66677eb  cmp rcx,0x20                                  
0x66677ef  jae 0x6668219                                 ; -> loc_6668219
0x66677f5  or rdx,0x27                                   
0x66677f9  mov rcx,rax                                   
0x66677fc  call 0xE935700                                ; -> sub_e935700
```
Purpose: Allocation (no args). Sets [rbp+0x400]=0x20000006407040. Computes [rbp+0x47A] = ~[rbx+0x3A8] + [rbx+0x3B0]. Allocation (0x4A). If [rbx+8] < [rbx+0x10], calls sub_eec6ec0 (memcpy) with r8d=0xC8, src=&[rbp+0x400], dst=[rbx+8], advances [rbx+8] by 0xC8. Else calls sub_5aba6d0 with rcx=rbx, r8=&[rbp+0x400]. Allocation (0x520 byte). Calls sub_66a65b0 with rcx=&[rbp+0x1E0]. If [rbp+0x1D0]==1 and [rbp+0x190] non-null, deallocates [rbp+0x190] buffer via sub_e935700.

### Phase 58: ImGui Resource Cleanup (0x6667801..0x66678fe, 40 ins)
```
0x6667801  cmp byte ptr [rbp+0x3D8],3                    
0x6667808  jne short 0x6667850                           ; -> loc_6667850
0x666780a  mov rdi,[rbp+0x3D0]                           
0x6667811  test rdi,rdi                                  
0x6667814  je short 0x6667850                            ; -> loc_6667850
0x6667816  lock dec dword ptr [rdi+8]                    
0x666781a  jne short 0x6667850                           -> loc_6667850
0x666781c  mov rax,[rdi]                                 
0x666781f  mov rax,[rax]                                 
0x6667822  mov rcx,rdi                                   
0x6667825  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666782b  lock dec dword ptr [rdi+0xC]                  
0x666782f  jne short 0x6667850                           -> loc_6667850
0x6667831  mov rax,[rdi]                                 
0x6667834  mov rax,[rax+8]                               
0x6667838  mov rcx,rdi                                   
0x666783b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667841  nop [rax+rax]                                 
0x6667850  mov rsi,[rbp+0x3A8]                           
0x6667857  test rsi,rsi                                  
0x666785a  je 0x6666CB0                                  ; -> sub_6666cb0
0x6667860  mov rbx,[rbp+0x3B0]                           
0x6667867  jmp short 0x6667874                           -> loc_6667874
0x6667870  add rsi,0x28                                  
0x6667874  cmp rsi,rbx                                   
0x6667877  je 0x6666CB0                                  ; -> sub_6666cb0
0x666787d  cmp byte ptr [rsi+0x18],2                     
0x6667881  jne short 0x6667870                           -> loc_6667870
0x6667883  mov rdi,[rsi+8]                               
0x6667887  test rdi,rdi                                  
0x666788a  je short 0x6667870                            -> loc_6667870
0x666788c  lock dec dword ptr [rdi+8]                    
0x6667890  jne short 0x6667870                           -> loc_6667870
0x6667892  mov rax,[rdi]                                 
0x6667895  mov rax,[rax]                                 
0x6667898  mov rcx,rdi                                   
0x666789b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66678a1  lock dec dword ptr [rdi+0xC]                  
0x66678a5  jne short 0x6667870                           -> loc_6667870
0x66678a7  mov rax,[rdi]                                 
0x66678aa  mov rax,[rax+8]                               
0x66678ae  mov rcx,rdi                                   
0x66678b1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66678b7  jmp short 0x6667870                           -> loc_6667870
0x66678b9  mov rcx,rsi                                   
0x66678bc  call 0x9BC830                                 ; -> sub_9bc830
0x66678c1  nop                                           
0x66678c2  jmp 0x66675E0                                 ; -> loc_66675e0
0x66678c7  mov rsi,[rbp+0x188]                           
0x66678ce  test rsi,rsi                                  
0x66678d1  je short 0x66678FE                            ; -> loc_66678fe
0x66678d3  lock dec dword ptr [rsi+8]                    
0x66678d7  jne short 0x66678FE                           -> loc_66678fe
0x66678d9  mov rax,[rsi]                                 
0x66678dc  mov rax,[rax]                                 
0x66678df  mov rcx,rsi                                   
0x66678e2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66678e8  lock dec dword ptr [rsi+0xC]                  
0x66678ec  jne short 0x66678FE                           -> loc_66678fe
0x66678ee  mov rax,[rsi]                                 
0x66678f1  mov rax,[rax+8]                               
0x66678f5  mov rcx,rsi                                   
0x66678f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66678fe  mov rsi,[rbp+0x178]                           
```
Purpose: If switch case was 3 ([rbp+0x3D8]==3), cleans up [rbp+0x3D0] via shared_ptr destruction. Then iterates array at [rbp+0x3A8] to [rbp+0x3B0] (stride 0x28), for elements where byte +0x18 == 2, cleans up pointer at +8 via shared_ptr destruction. Jumps back to loop at 0x6666cb0 (Phase 46). Allocation failure path at 0x66678b9 calls sub_9bc830, jumps back to 0x66675e0. Cleans up [rbp+0x188] and [rbp+0x178] via shared_ptr destruction.

### Phase 59: Final Cleanup & Loop Return (0x66678fe..0x666792c, 20 ins)
```
0x66678fe  mov rsi,[rbp+0x178]                           
0x6667905  test rsi,rsi                                  
0x6667908  je short 0x6667935                            ; -> loc_6667935
0x666790a  lock dec dword ptr [rsi+8]                    
0x666790e  jne short 0x6667935                           -> loc_6667935
0x6667910  mov rax,[rsi]                                 
0x6667913  mov rax,[rax]                                 
0x6667916  mov rcx,rsi                                   
0x6667919  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x666791f  lock dec dword ptr [rsi+0xC]                  
0x6667923  jne short 0x6667935                           -> loc_6667935
0x6667925  mov rax,[rsi]                                 
0x6667928  mov rax,[rax+8]                               
0x666792c  mov rcx,rsi                                   
```
Purpose: Cleans up [rbp+0x178] via shared_ptr destruction (dec +8, call sub_eea6040 slot 0, dec +0xC, call slot 1). Continues to loc_6667935.

---

## Updated String Reference Table (Phase 0-59)

| String RVA | Text | Call Site RVA | Callee After |
|------------|------|---------------|--------------|
| 0xF5AD096 | "Debug/ImGui" | 0x6664ae9 (lea rax) | 0x675E440 (sub_675e440) |
| 0xF539A95 | "UI/Blit" | 0x6664d8f (lea rax) | 0x675E440 (sub_675e440) |
| 0xF58B3B6 | "Unnamed Transaction" | 0x6665986, 0x6666432 (movups xmm0) | 0xEEC6E70 (sub_eec6e70) |
| 0xF58B3C5 | "tion" | 0x666597d, 0x6666429 (mov eax) | 0xEEC6E70 (sub_eec6e70) |
| 0xF8407B6 | (format string) | 0x6665d92, 0x666673e (lea r9) | 0xA0850 (sub_a0850) |

## Updated [reg+off] Write Table (Non-Stack, Output Descriptions/Records)

| Offset | Size | Source | Instruction (RVA) | Meaning | Tag |
|--------|------|--------|-------------------|---------|-----|
| [rdi+0x17E] | 8 | [rbp+0x3C8+0x28] | 0x6667081 | ImGui field | [V] |
| [rdi+0x16E] | 16 | [rbp+0x3C8+0x18] | 0x666708c | ImGui field | [V] |
| [rbp+0x408..0x4B8] | 16x12 | 0 | 0x66670af..0x66670e7 | Zero ImGui state | [V] |
| [rbp+0x428] | 2 | ax | 0x6667115 | Draw cmd count | [V] |
| [rbp+0x520] | 1 | al | 0x6667132 | Alloc result | [V] |
| [rbp+0x400] | 8 | 0x2001000 | 0x6667168 | ImGui flags | [V] |
| [rbp+0x442] | 2 | ax | 0x666718a | Vertex count | [V] |
| [rbp+0x520] | 1 | al | 0x66671a8 | Alloc result | [V] |
| [rdi] | 8 | [rbp+0x240] | 0x66671c5 | Draw cmd write | [V] |
| [rdi+0x80] | 8 | [rbp+0x2C0] | 0x66671e0 | Draw cmd field | [V] |
| [rbp+0x2C0] | 8 | 0 | 0x66671e7 | Zero | [V] |
| [rbx+0x770] | 8 | +0x88 | 0x66671f2 | Advance pointer | [V] |
| [rbp+0x520] | 1 | al | 0x6667232 | Alloc result | [V] |
| [rbp+0x42A] | 2 | ax | 0x666724a | Draw cmd count | [V] |
| [rbp+0x520] | 1 | al | 0x6667268 | Alloc result | [V] |
| [rdx+0x10] | 4 | [rbp+0x1E8+0x10] | 0x666728c | Vertex field | [V] |
| [rdx+0x00] | 16 | [rbp+0x1E8] | 0x6667292 | Vertex data | [V] |
| [rdx+0x14] | 1 | [rbp+0x1FC] | 0x666729c | Vertex byte | [V] |
| [rdx+0x18] | 4 | [rbp+0x200] | 0x66672a7 | Vertex float | [V] |
| [rdx+0x1C] | 4 | [rbp+0x204] | 0x66672b4 | Vertex float | [V] |
| [rdx+0x20] | 4 | [rbp+0x208] | 0x66672c1 | Vertex float | [V] |
| [rdx+0x24] | 4 | [rbp+0x20C] | 0x66672ce | Vertex float | [V] |
| [rdx+0x28] | 16 | [rbp+0x1E2+0x2E] | 0x66672e6 | Vertex xmm | [V] |
| [rdx+0x38] | 16 | [rbp+0x1E2+0x3E] | 0x66672ea | Vertex xmm | [V] |
| [rdx+0x47] | 16 | [rbp+0x1E2+0x4D] | 0x66672ee | Vertex xmm | [V] |
| [rbx+0x758] | 8 | +0x58 | 0x66672f2 | Advance pointer | [V] |
| [rbp+0x42C] | 2 | ax | 0x6667352 | Draw cmd count | [V] |
| [rbp+0x400] | 8 | 0x2007000 | 0x6667330 | ImGui flags | [V] |
| [rbp+0x520] | 1 | al | 0x6667370 | Alloc result | [V] |
| [rdx] | 4 | [rbp+0x1E4] | 0x666738c | Index write | [V] |
| [rbx+0x638] | 8 | +4 | 0x666738e | Advance pointer | [V] |
| [rbp+0x444] | 2 | ax | 0x66673e1 | Index count | [V] |
| [rbp+0x520] | 1 | al | 0x66673ff | Alloc result | [V] |
| [rdx] | 2 | [rbp+0x1E2] | 0x666741c | Vertex attr | [V] |
| [rbx+0x698] | 8 | +2 | 0x666741f | Advance pointer | [V] |
| [rbp+0x43C] | 2 | ax | 0x666747b | Attr count | [V] |
| [rbp+0x400] | 8 | 0x6407000 | 0x6667460 | ImGui flags | [V] |
| [rbp+0x520] | 1 | al | 0x6667499 | Alloc result | [V] |
| [rbx+0x818] | 8 | +1 | 0x66674b2 | Advance pointer | [V] |
| [rbp+0x41C] | 2 | ax | 0x66674fa | Buffer calc | [V] |
| [rbp+0x520] | 1 | al | 0x6667517 | Alloc result | [V] |
| [rbx+0x3B0] | 8 | r15+1 | 0x6667533 | Inc counter | [V] |
| [rbp+0x520] | 1 | dl | 0x6667567 | Save byte | [V] |
| [rbp+0x510] | 8 | r8 | 0x666758a | Growth size | [V] |
| [rdi-8] | 8 | rax | 0x66675eb | Alloc header | [V] |
| [rbx+0x3A8] | 8 | rdi | 0x66676c4 | New buffer | [V] |
| [rbx+0x3B0] | 8 | rdi+r8 | 0x66676d5 | New end | [V] |
| [rbx+0x3B8] | 8 | r13+rdi | 0x66676df | New cap | [V] |
| [rbp+0x400] | 8 | 0x20000006407040 | 0x6667717 | ImGui flags | [V] |
| [rbp+0x47A] | 2 | ax | 0x666772c | Buffer calc | [V] |
| [rbp+0x520] | 1 | al | 0x666774a | Alloc result | [V] |
| [rbx+0x08] | 8 | +0xC8 | 0x666776f | Advance | [V] |

---

## Verification
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-I5a2.md` after each chunk.

## TOOL REQUESTS
None.

---

## Step 6 Complete: Instruction-complete listing of 0x6664a00 (final chunk: 0x666792c..0x6668106, 12 phases)
Function END reached at 0x6668106 (ret). Total function size: 0x3b10 bytes (15,120 bytes).

### Phase 60: ImGui Cleanup & Second ImGui Context (0x666792c..0x6667a08, 40 ins)
```
0x666792c  mov rcx,rsi                                   
0x666792f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667935  mov rsi,[rbp+0x4D8]                           
0x666793c  test rsi,rsi                                  
0x666793f  jne 0x66680AA                                 ; -> loc_66680aa
0x6667945  jmp 0x66680D5                                 ; -> loc_66680d5
0x666794a  xor ecx,ecx                                   
0x666794c  mov rdx,[rbp+0x78]                            
0x6667950  mov [rbp+0x358],rdx                           
0x6667957  mov [rbp+0x360],rcx                           
0x666795e  mov [rbp+0x368],al                            
0x6667964  mov rax,[rbp+0xA0]                            
0x666796b  mov [rbp+0x380],rax                           
0x6667972  movaps xmm0,[rbp+0x90]                        
0x6667979  movups [rbp+0x370],xmm0                       
0x6667980  mov ecx,0x9D0                                 
0x6667985  add rcx,[r14+0x10]                            
0x6667989  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x666798e  nop                                           
0x666798f  mov rsi,rax                                   
0x6667992  lea rdx,[rbp+0x330]                           
0x6667999  xorps xmm0,xmm0                               
0x666799c  movaps [rbp+0x4B0],xmm0                       
0x66679a3  movaps [rbp+0x4A0],xmm0                       
0x66679aa  movaps [rbp+0x490],xmm0                       
0x66679b1  movaps [rbp+0x480],xmm0                       
0x66679b8  movaps [rbp+0x470],xmm0                       
0x66679bf  movaps [rbp+0x460],xmm0                       
0x66679c6  movaps [rbp+0x450],xmm0                       
0x66679cd  movaps [rbp+0x440],xmm0                       
0x66679d4  movaps [rbp+0x430],xmm0                       
0x66679db  movaps [rbp+0x420],xmm0                       
0x66679e2  movaps [rbp+0x410],xmm0                       
0x66679e9  movaps [rbp+0x400],xmm0                       
0x66679f0  mov qword ptr [rbp+0x4C0],0                   
0x66679fb  lea rcx,[rax+0x780]                           ; R ret@5aba5c0+0x780
0x6667a02  call 0x675F3B0                                ; -> sub_675f3b0
0x6667a07  nop                                           
0x6667a08  mov eax,[rsi+0x788]                           ; R ret@5aba5c0+0x788
```
Purpose: Cleans up [rbp+0x178] via sub_eea6040 (slot 1). Loads rsi=[rbp+0x4D8]; if non-null jumps to error handler 0x66680aa, else to success exit 0x66680d5. Switch case 0 at 0x666794a: zeros ecx, moves [rbp+0x78] to [rbp+0x358], etc. Sets up ImGui context again: calls sub_5aba5c0 with rcx=[r14+0x10]+0x9D0. Zeros large area at [rbp+0x400..0x4B0] (12 xmm). Calls sub_675f3b0 with rcx=rax+0x780, rdx=&[rbp+0x330].

### Phase 61: ImGui Draw List - Vertex Index Section (0x6667a08..0x6667afa, 40 ins)
```
0x6667a08  mov eax,[rsi+0x788]                           ; R ret@5aba5c0+0x788
0x6667a0e  sub eax,[rsi+0x780]                           ; R ret@5aba5c0+0x780
0x6667a14  shr eax,3                                     
0x6667a17  imul eax,0xFFFF8BA3                           
0x6667a1d  dec eax                                       
0x6667a1f  mov [rbp+0x428],ax                            
0x6667a26  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667a2d  mov rax,[rcx]                                 
0x6667a30  mov rax,[rax+0x10]                            
0x6667a34  mov dl,0x4A                                   
0x6667a36  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667a3c  nop                                           
0x6667a3d  mov [rbp+0x520],al                            
0x6667a43  mov rdx,[rsi+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6667a4a  cmp rdx,[rsi+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6667a51  je short 0x6667A67                            ; -> loc_6667a67
0x6667a53  movzx eax,word ptr [rbp+0x328]                
0x6667a5a  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x6667a5d  add qword ptr [rsi+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6667a65  jmp short 0x6667A7B                           ; -> loc_6667a7b
0x6667a67  lea r8,[rbp+0x328]                            
0x6667a6e  lea rcx,[rsi+0x8A0]                           
0x6667a75  call 0x1EF6F90                                ; -> sub_1ef6f90
0x6667a7a  nop                                           
0x6667a7b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667a82  mov rax,[rcx]                                 
0x6667a85  mov rax,[rax+0x10]                            
0x6667a89  movzx edx,byte ptr [rbp+0x520]                
0x6667a90  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667a96  nop                                           
0x6667a97  mov eax,[rsi+0x8A8]                           
0x6667a9d  sub eax,[rsi+0x8A0]                           
0x6667aa3  shr eax,1                                     
0x6667aa5  dec eax                                       
0x6667aa7  mov [rbp+0x410],ax                            
0x6667aae  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667ab5  mov rax,[rcx]                                 
0x6667ab8  mov rax,[rax+0x10]                            
0x6667abc  mov dl,0x4A                                   
0x6667abe  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667ac4  mov [rbp+0x520],al                            
```
Purpose: Computes vertex count: ([rsi+0x788]-[rsi+0x780])>>3 * 0xFFFF8BA3, dec, stores to [rbp+0x428]. Allocation (0x4A). If [rsi+0x8A8] < [rsi+0x8B0], writes word [rbp+0x328] to *rdx, advances [rsi+0x8A8] by 2. Else calls sub_1ef6f90. Allocation (0x4A). Computes index count: ([rsi+0x8A8]-[rsi+0x8A0])>>1, dec, stores to [rbp+0x410]. Allocation (0x4A). Calls sub_675fb30 with rdx=&[rbp+0x2E0], rcx=rsi+0x648.

### Phase 62: ImGui Draw List - Vertex Buffer Section (0x6667ad1..0x6667bff, 40 ins)
```
0x6667ad1  lea rcx,[rsi+0x648]                          
```                           
0x6667ad1  lea rcx,[rsi+0x648]                           
0x6667ad8  call 0x675FB30                                ; -> sub_675fb30
0x6667add  nop                                           
0x6667ade  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667ae5  mov rax,[rcx]                                 
0x6667ae8  mov rax,[rax+0x10]                            
0x6667aec  movzx edx,byte ptr [rbp+0x520]                
0x6667af3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667af9  nop                                           
0x6667afa  mov qword ptr [rbp+0x400],0x2001001           
0x6667b05  mov eax,[rsi+0x650]                           
0x6667b0b  sub eax,[rsi+0x648]                           
0x6667b11  shr eax,3                                     
0x6667b14  imul eax,0xFFFF8E39                           
0x6667b1a  dec eax                                       
0x6667b1c  mov [rbp+0x442],ax                            
0x6667b23  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667b2a  mov rax,[rcx]                                 
0x6667b2d  mov rax,[rax+0x10]                            
0x6667b31  mov dl,0x4A                                   
0x6667b33  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667b39  nop                                           
0x6667b3a  mov [rbp+0x520],al                            
0x6667b40  mov rdx,[rsi+0x638]                           
0x6667b47  cmp rdx,[rsi+0x640]                           
0x6667b4e  je short 0x6667B62                            ; -> loc_6667b62
0x6667b50  mov eax,[rbp+0x2D8]                           
0x6667b56  mov [rdx],eax                                 
0x6667b58  add qword ptr [rsi+0x638],4                   
0x6667b60  jmp short 0x6667B76                           ; -> loc_6667b76
0x6667b62  lea r8,[rbp+0x2D8]                            
0x6667b69  lea rcx,[rsi+0x630]                           
0x6667b70  call 0x14DB710                                ; -> sub_14db710
0x6667b75  nop                                           
0x6667b76  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667b7d  mov rax,[rcx]                                 
0x6667b80  mov rax,[rax+0x10]                            
0x6667b84  movzx edx,byte ptr [rbp+0x520]                
0x6667b8b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667b91  nop                                           
0x6667b92  mov eax,[rsi+0x638]                           
0x6667b98  sub eax,[rsi+0x630]                           
0x6667b9e  shr eax,2                                     
0x6667ba1  dec eax                                       
0x6667ba3  mov [rbp+0x444],ax                            
0x6667baa  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667bb1  mov rax,[rcx]                                 
0x6667bb4  mov rax,[rax+0x10]                            
0x6667bb8  mov dl,0x4A                                   
0x6667bba  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667bc0  nop                                           
0x6667bc1  mov [rbp+0x520],al                            
0x6667bc7  mov rdx,[rsi+0x698]                           
0x6667bce  cmp rdx,[rsi+0x6A0]                           
0x6667bd5  je short 0x6667BEB                            ; -> loc_6667beb
0x6667bd7  movzx eax,word ptr [rbp+0x2D0]                
0x6667bde  mov [rdx],ax                                  
0x6667be1  add qword ptr [rsi+0x698],2                   
0x6667be9  jmp short 0x6667BFF                           ; -> loc_6667bff
```
Purpose: Sets [rbp+0x400]=0x2001001. Computes vertex count: ([rsi+0x650]-[rsi+0x648])>>3 * 0xFFFF8E39, dec, stores to [rbp+0x442]. Allocation (0x4A). If [rsi+0x638] < [rsi+0x640], writes [rbp+0x2D8] to *rdx, advances [rsi+0x638] by 4. Else calls sub_14db710. Allocation (0x4A). Computes index count: ([rsi+0x638]-[rsi+0x630])>>2, dec, stores to [rbp+0x444]. Allocation (0x4A). If [rsi+0x698] < [rsi+0x6A0], writes word [rbp+0x2D0] to *rdx, advances [rsi+0x698] by 2. Else calls sub_1ef6f90.

### Phase 63: ImGui Draw List - Vertex Attribute Section (0x6667bff..0x6667ce8, 40 ins)
```
0x6667bff  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667c06  mov rax,[rcx]                                 
0x6667c09  mov rax,[rax+0x10]                            
0x6667c0d  movzx edx,byte ptr [rbp+0x520]                
0x6667c14  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667c1a  nop                                           
0x6667c1b  mov qword ptr [rbp+0x400],0x6401001           
0x6667c26  mov eax,[rsi+0x698]                           
0x6667c2c  sub eax,[rsi+0x690]                           
0x6667c32  shr eax,1                                     
0x6667c34  dec eax                                       
0x6667c36  mov [rbp+0x43C],ax                            
0x6667c3d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667c44  mov rax,[rcx]                                 
0x6667c47  mov rax,[rax+0x10]                            
0x6667c4b  mov dl,0x4A                                   
0x6667c4d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667c53  nop                                           
0x6667c54  mov [rbp+0x520],al                            
0x6667c5a  lea r8,[rbp+0x278]                            
0x6667c61  mov rdx,[rsi+0x758]                           
0x6667c68  cmp rdx,[rsi+0x760]                           
0x6667c6f  je short 0x6667CE8                            ; -> loc_6667ce8
0x6667c71  mov eax,[r8+0x10]                             
0x6667c75  mov [rdx+0x10],eax                            
0x6667c78  movups xmm0,[r8]                              
0x6667c7c  movups [rdx],xmm0                             
0x6667c7f  movzx eax,byte ptr [rbp+0x28C]                
0x6667c86  mov [rdx+0x14],al                             
0x6667c89  movss xmm0,[rbp+0x290]                        
0x6667c91  movss [rdx+0x18],xmm0                         
0x6667c96  movss xmm0,[rbp+0x294]                        
0x6667c9e  movss [rdx+0x1C],xmm0                         
0x6667ca3  movss xmm0,[rbp+0x298]                        
0x6667cab  movss [rdx+0x20],xmm0                         
0x6667cb0  movss xmm0,[rbp+0x29C]                        
0x6667cb8  movss [rdx+0x24],xmm0                         
0x6667cbd  movups xmm0,[rbp+0x2A0]                       
0x6667cc4  movups xmm1,[rbp+0x2B0]                       
0x6667ccb  movups xmm2,[rbp+0x2BF]                       
0x6667cd2  movups [rdx+0x28],xmm0                        
0x6667cd6  movups [rdx+0x38],xmm1                        
0x6667cda  movups [rdx+0x47],xmm2                        
0x6667cde  add qword ptr [rsi+0x758],0x58                
0x6667ce6  jmp short 0x6667CF5                           ; -> loc_6667cf5
```
Purpose: Sets [rbp+0x400]=0x6401001. Computes attr count: ([rsi+0x698]-[rsi+0x690])>>1, dec, stores to [rbp+0x43C]. Allocation (0x4A). If [rsi+0x758] < [rsi+0x760], writes vertex data from [rbp+0x278]: [r8+0x10] to +0x10, xmm from [r8] to +0x0, byte [rbp+0x28C] to +0x14, floats from [rbp+0x290]/[rbp+0x294]/[rbp+0x298]/[rbp+0x29C] to +0x18/+0x1C/+0x20/+0x24. Then xmm from [rbp+0x2A0]/[rbp+0x2B0]/[rbp+0x2BF] to +0x28/+0x38/+0x47. Advances [rsi+0x758] by 0x58. Else jumps to loc_6667ce8.

### Phase 64: ImGui Draw List - Final Vertex Section (0x6667ce8..0x6667d68, 40 ins)
```
0x6667ce8  lea rcx,[rsi+0x750]                           
0x6667cef  call 0x6760A80                                ; -> sub_6760a80
0x6667cf4  nop                                           
0x6667cf5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667cfc  mov rax,[rcx]                                 
0x6667cff  mov rax,[rax+0x10]                            
0x6667d03  movzx edx,byte ptr [rbp+0x520]                
0x6667d0a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667d10  nop                                           
0x6667d11  mov eax,[rsi+0x758]                           
0x6667d17  sub eax,[rsi+0x750]                           
0x6667d1d  shr eax,3                                     
0x6667d20  imul eax,0xFFFF8BA3                           
0x6667d26  dec eax                                       
0x6667d28  mov [rbp+0x42C],ax                            
0x6667d2f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667d36  mov rax,[rcx]                                 
0x6667d39  mov rax,[rax+0x10]                            
0x6667d3d  mov dl,0x4A                                   
0x6667d3f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667d45  nop                                           
0x6667d46  mov [rbp+0x520],al                            
0x6667d4c  mov rdx,[rsi+0x818]                           
0x6667d53  cmp rdx,[rsi+0x820]                           
0x6667d5a  je short 0x6667D68                            ; -> loc_6667d68
0x6667d5c  inc rdx                                       
0x6667d5f  mov [rsi+0x818],rdx                           
0x6667d66  jmp short 0x6667D75                           ; -> loc_6667d75
0x6667d68  lea rcx,[rsi+0x810]                           
0x6667d6f  call 0x6760E60                                ; -> sub_6760e60
0x6667d74  nop                                           
0x6667d75  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667d7c  mov rax,[rcx]                                 
0x6667d7f  mov rax,[rax+0x10]                            
0x6667d83  movzx edx,byte ptr [rbp+0x520]                
0x6667d8a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667d90  nop                                           
0x6667d91  mov qword ptr [rbp+0x400],0x6405041           
0x6667d9c  mov eax,[rsi+0x810]                           
0x6667da2  not eax                                       
0x6667da4  add eax,[rsi+0x818]                           
0x6667daa  mov [rbp+0x41C],ax                            
0x6667db1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667db8  mov rax,[rcx]                                 
0x6667dbb  mov rax,[rax+0x10]                            
0x6667dbf  mov dl,0x4A                                   
0x6667dc1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667dc7  nop                                           
0x6667dc8  mov [rbp+0x520],al                            
```
Purpose: Calls sub_6760a80 with rcx=rsi+0x750. Allocation (0x4A). Computes count: ([rsi+0x758]-[rsi+0x750])>>3 * 0xFFFF8BA3, dec, stores to [rbp+0x42C]. Allocation (0x4A). If [rsi+0x818] < [rsi+0x820], increments [rsi+0x818]. Else calls sub_6760e60. Allocation (0x4A). Sets [rbp+0x400]=0x6405041. Computes [rbp+0x41C] = ~[rsi+0x810] + [rsi+0x818]. Allocation (0x4A).

### Phase 65: ImGui Draw List - Command Buffer (0x6667dce..0x6667eac, 40 ins)
```
0x6667dce  mov rdx,[rsi+0x368]                           
0x6667dd5  cmp rdx,[rsi+0x370]                           
0x6667ddc  je short 0x6667DEA                            ; -> loc_6667dea
0x6667dde  inc rdx                                       
0x6667de1  mov [rsi+0x368],rdx                           
0x6667de8  jmp short 0x6667DF7                           ; -> loc_6667df7
0x6667dea  lea rcx,[rsi+0x360]                           
0x6667df1  call 0x6760E60                                ; -> sub_6760e60
0x6667df6  nop                                           
0x6667df7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667dfe  mov rax,[rcx]                                 
0x6667e01  mov rax,[rax+0x10]                            
0x6667e05  movzx edx,byte ptr [rbp+0x520]                
0x6667e0c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667e12  nop                                           
0x6667e13  mov eax,[rsi+0x360]                           
0x6667e19  not eax                                       
0x6667e1b  add eax,[rsi+0x368]                           
0x6667e21  mov [rbp+0x480],ax                            
0x6667e28  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667e2f  mov rax,[rcx]                                 
0x6667e32  mov rax,[rax+0x10]                            
0x6667e36  mov dl,0x4A                                   
0x6667e38  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667e3e  nop                                           
0x6667e3f  mov [rbp+0x520],al                            
0x6667e45  mov rbx,[rsi+0x770]                           
0x6667e4c  cmp rbx,[rsi+0x778]                           
0x6667e53  je short 0x6667E92                            ; -> loc_6667e92
0x6667e55  mov rax,[rbp+0x1E0]                           
0x6667e5c  mov [rbx],rax                                 
0x6667e5f  lea rcx,[rbx+8]                               
0x6667e63  mov rdx,rdi                                   
0x6667e66  call 0xE869FF0                                ; -> sub_e869ff0
0x6667e6b  nop                                           
0x6667e6c  mov rax,[rbp+0x260]                           
0x6667e73  mov [rbx+0x80],rax                            
0x6667e7a  mov qword ptr [rbp+0x260],0                   
0x6667e85  add qword ptr [rsi+0x770],0x88                
0x6667e90  jmp short 0x6667EAC                           ; -> loc_6667eac
```
Purpose: If [rsi+0x368] < [rsi+0x370], increments [rsi+0x368]. Else calls sub_6760e60. Allocation (0x4A). Computes [rbp+0x480] = ~[rsi+0x360] + [rsi+0x368]. Allocation (0x4A). If [rsi+0x770] < [rsi+0x778], writes [rbp+0x1E0] to *rbx, calls sub_e869ff0 with rcx=rbx+8, rdx=rdi, writes [rbp+0x260] to rbx+0x80, zeros [rbp+0x260], advances [rsi+0x770] by 0x88. Else jumps to loc_6667e92.

### Phase 66: ImGui Draw List - Alternate Command Path (0x6667e92..0x6667f50, 40 ins)
```
0x6667e92  mov rcx,rsi                                   
0x6667e95  add rcx,0x768                                 
0x6667e9c  lea r8,[rbp+0x1E0]                            
0x6667ea3  mov rdx,rbx                                   
0x6667ea6  call 0x6760710                                ; -> sub_6760710
0x6667eab  nop                                           
0x6667eac  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667eb3  mov rax,[rcx]                                 
0x6667eb6  mov rax,[rax+0x10]                            
0x6667eba  movzx edx,byte ptr [rbp+0x520]                
0x6667ec1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667ec7  nop                                           
0x6667ec8  mov rax,0x100000006407041                     
0x6667ed2  mov [rbp+0x400],rax                           
0x6667ed9  mov eax,[rsi+0x770]                           
0x6667edf  sub eax,[rsi+0x768]                           
0x6667ee5  shr eax,3                                     
0x6667ee8  imul eax,0xFFFFF0F1                           
0x6667eee  dec eax                                       
0x6667ef0  mov [rbp+0x42A],ax                            
0x6667ef7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667efe  mov rax,[rcx]                                 
0x6667f01  mov rax,[rax+0x10]                            
0x6667f05  mov dl,0x4A                                   
0x6667f07  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667f0d  nop                                           
0x6667f0e  mov [rbp+0x520],al                            
0x6667f14  mov rax,[rsi+8]                               
0x6667f18  cmp rax,[rsi+0x10]                            
0x6667f1c  je short 0x6667F3D                            ; -> loc_6667f3d
0x6667f1e  lea rdx,[rbp+0x400]                           
0x6667f25  mov r8d,0xC8                                  
0x6667f2b  mov rcx,rax                                   
0x6667f2e  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x6667f33  add qword ptr [rsi+8],0xC8                    
0x6667f3b  jmp short 0x6667F50                           ; -> loc_6667f50
0x6667f3d  lea r8,[rbp+0x400]                            
0x6667f44  mov rcx,rsi                                   
0x6667f47  mov rdx,rax                                   
0x6667f4a  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x6667f4f  nop                                           
0x6667f50  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```
Purpose: Alternate path when [rsi+0x770] == [rsi+0x778]. Calls sub_6760710 with rcx=rsi+0x768, r8=&[rbp+0x1E0], rdx=rbx. Allocation (0x4A). Sets [rbp+0x400]=0x100000006407041. Computes count: ([rsi+0x770]-[rsi+0x768])>>3 * 0xFFFFF0F1, dec, stores to [rbp+0x42A]. Allocation (0x4A). If [rsi+8] < [rsi+0x10], calls sub_eec6ec0 (memcpy) with r8d=0xC8, src=&[rbp+0x400], dst=[rsi+8], advances [rsi+8] by 0xC8. Else calls sub_5aba6d0 with rcx=rsi, r8=&[rbp+0x400]. Allocation (0x520 byte).

### Phase 67: Final ImGui Call & Switch on [rbp+0x88] (0x6667f50..0x6667fb8, 40 ins)
```
0x6667f50  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6667f57  mov rax,[rcx]                                 
0x6667f5a  mov rax,[rax+0x10]                            
0x6667f5e  movzx edx,byte ptr [rbp+0x520]                
0x6667f65  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667f6b  nop                                           
0x6667f6c  lea rcx,[rbp+0x1E0]                           
0x6667f73  call 0x66E74B0                                ; -> sub_66e74b0
0x6667f78  cmp byte ptr [rbp+0x88],3                     
0x6667f7f  jne short 0x6667FB8                           ; -> loc_6667fb8
0x6667f81  mov rsi,[rbp+0x80]                            
0x6667f88  test rsi,rsi                                  
0x6667f8b  je short 0x6667FB8                            ; -> loc_6667fb8
0x6667f8d  lock dec dword ptr [rsi+8]                    
0x6667f91  jne short 0x6667FB8                           ; -> loc_6667fb8
0x6667f93  mov rax,[rsi]                                 
0x6667f96  mov rax,[rax]                                 
0x6667f99  mov rcx,rsi                                   
0x6667f9c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667fa2  lock dec dword ptr [rsi+0xC]                  
0x6667fa6  jne short 0x6667FB8                           ; -> loc_6667fb8
0x6667fa8  mov rax,[rsi]                                 
0x6667fab  mov rax,[rax+8]                               
0x6667faf  mov rcx,rsi                                   
0x6667fb2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6667fb8  mov rdi,[rbp+0x58]                            
0x6667fbc  test rdi,rdi                                  
0x6667fbf  je short 0x6668015                            ; -> loc_6668015
0x6667fc1  mov rbx,[rbp+0x60]                            
0x6667fc5  jmp short 0x6667FD4                           ; -> loc_6667fd4
0x6667fd0  add rdi,0x28                                  
0x6667fd4  cmp rdi,rbx                                   
0x6667fd7  je short 0x6668015                            ; -> loc_6668015
0x6667fd9  cmp byte ptr [rdi+0x18],2                     
0x6667fdd  jne short 0x6667FD0                           ; -> loc_6667fd0
0x6667fdf  mov rsi,[rdi+8]                               
0x6667fe3  test rsi,rsi                                  
0x6667fe6  je short 0x6667FD0                            ; -> loc_6667fd0
0x6667fe8  lock dec dword ptr [rsi+8]                    
0x6667fec  jne short 0x6667FD0                           ; -> loc_6667fd0
0x6667fee  mov rax,[rsi]                                 
0x6667ff1  mov rax,[rax]                                 
0x6667ff4  mov rcx,rsi                                   
0x6667ff7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
Purpose: Allocation (0x520). Calls sub_66e74b0 with rcx=&[rbp+0x1E0]. Switch on byte [rbp+0x88]: if ==3, cleans up [rbp+0x80] via shared_ptr destruction. Then iterates array at [rbp+0x58] to [rbp+0x60] (stride 0x28), for elements where byte +0x18 == 2, cleans up pointer at +8 via shared_ptr destruction.

### Phase 68: Final Array Cleanup & Buffer Deallocation (0x6667fb8..0x66680d5, 40 ins)
```
0x6667ffd  lock dec dword ptr [rsi+0xC]                  
0x6668001  jne short 0x6667FD0                           ; -> loc_6667fd0
0x6668003  mov rax,[rsi]                                 
0x6668006  mov rax,[rax+8]                               
0x666800a  mov rcx,rsi                                   
0x666800d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6668013  jmp short 0x6667FD0                           ; -> loc_6667fd0
0x6668015  cmp byte ptr [rbp+0x3E0],1                    
0x666801c  jne short 0x666805E                           ; -> loc_666805e
0x666801e  mov rcx,[rbp+0x3A0]                           
0x6668025  test rcx,rcx                                  
0x6668028  je short 0x666805E                            ; -> loc_666805e
0x666802a  mov rdx,[rbp+0x3B0]                           
0x6668031  sub rdx,rcx                                   
0x6668034  cmp rdx,0x1000                                
0x666803b  jb short 0x6668059                            ; -> loc_6668059
0x666803d  mov rax,[rcx-8]                               
0x6668041  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6668045  sub rcx,rax                                   
0x6668048  cmp rcx,0x20                                  
0x666804c  jae 0x6668219                                 ; -> loc_6668219
0x6668052  or rdx,0x27                                   
0x6668056  mov rcx,rax                                   
0x6668059  call 0xE935700                                ; -> sub_e935700
0x666805e  mov rcx,[rbp+0x190]                           
0x6668065  test rcx,rcx                                  
0x6668068  je short 0x666809E                            ; -> loc_666809e
0x666806a  mov rdx,[rbp+0x1A0]                           
0x6668071  sub rdx,rcx                                   
0x6668074  cmp rdx,0x1000                                
0x666807b  jb short 0x6668099                            ; -> loc_6668099
0x666807d  mov rax,[rcx-8]                               
0x6668081  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6668085  sub rcx,rax                                   
0x6668088  cmp rcx,0x20                                  
0x666808c  jae 0x6668219                                 ; -> loc_6668219
0x6668092  or rdx,0x27                                   
0x6668096  mov rcx,rax                                   
0x6668099  call 0xE935700                                ; -> sub_e935700
0x666809e  mov rsi,[rbp+0x398]                           
0x66680a5  test rsi,rsi                                  
0x66680a8  je short 0x66680D5                            ; -> loc_66680d5
0x66680aa  lock dec dword ptr [rsi+8]                    
0x66680ae  jne short 0x66680D5                           ; -> loc_66680d5
0x66680b0  mov rax,[rsi]                                 
0x66680b3  mov rax,[rax]                                 
0x66680b6  mov rcx,rsi                                   
0x66680b9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66680bf  lock dec dword ptr [rsi+0xC]                  
0x66680c3  jne short 0x66680D5                           ; -> loc_66680d5
0x66680c5  mov rax,[rsi]                                 
0x66680c8  mov rax,[rax+8]                               
0x66680cc  mov rcx,rsi                                   
0x66680cf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66680d5  movaps xmm6,[rbp+0x530]                       
0x66680dc  movaps xmm7,[rbp+0x540]                       
0x66680e3  movaps xmm8,[rbp+0x550]                       
0x66680eb  movaps xmm9,[rbp+0x560]                       
0x66680f3  add rsp,0x5F8                                 
0x66680fa  pop rbx                                       
0x66680fb  pop rdi                                       
0x66680fc  pop rsi                                       
0x66680fd  pop r12                                       
0x66680ff  pop r13                                       
0x6668101  pop r14                                       
0x6668103  pop r15                                       
0x6668105  pop rbp                                       
0x6668106  ret                                           
```
Purpose: Continues array cleanup loop. If [rbp+0x3E0]==1, deallocates [rbp+0x3A0] buffer via sub_e935700. Deallocates [rbp+0x190] buffer via sub_e935700. If [rbp+0x398] non-null, cleans up via shared_ptr destruction. Error handlers at 0x66680aa, 0x66680d5. Epilogue: restores xmm6-xmm9, adds rsp, pops registers, RET at 0x6668106. Function END.

---

## Final String Reference Table (Phase 0-68)

| String RVA | Text | Call Site RVA | Callee After |
|------------|------|---------------|--------------|
| 0xF5AD096 | "Debug/ImGui" | 0x6664ae9 (lea rax) | 0x675E440 (sub_675e440) |
| 0xF539A95 | "UI/Blit" | 0x6664d8f (lea rax) | 0x675E440 (sub_675e440) |
| 0xF58B3B6 | "Unnamed Transaction" | 0x6665986, 0x6666432 (movups xmm0) | 0xEEC6E70 (sub_eec6e70) |
| 0xF58B3C5 | "tion" | 0x666597d, 0x6666429 (mov eax) | 0xEEC6E70 (sub_eec6e70) |
| 0xF8407B6 | (format string) | 0x6665d92, 0x666673e (lea r9) | 0xA0850 (sub_a0850) |

## Final [reg+off] Write Table (Non-Stack, Output Descriptions/Records)

| Offset | Size | Source | Instruction (RVA) | Meaning | Tag |
|--------|------|--------|-------------------|---------|-----|
| [rbp+0x358] | 8 | [rbp+0x78] | 0x6667950 | Switch case save | [V] |
| [rbp+0x360] | 8 | rcx | 0x6667957 | Switch case save | [V] |
| [rbp+0x368] | 1 | al | 0x666795e | Switch case save | [V] |
| [rbp+0x380] | 8 | [rbp+0xA0] | 0x666796b | Switch case save | [V] |
| [rbp+0x370] | 16 | [rbp+0x90] | 0x6667979 | Switch case save | [V] |
| [rbp+0x400..0x4B0] | 16x12 | 0 | 0x666799c..0x66679e9 | Zero ImGui state | [V] |
| [rbp+0x4C0] | 8 | 0 | 0x66679f0 | Zero | [V] |
| [rbp+0x428] | 2 | ax | 0x6667a1f | Vertex count | [V] |
| [rbp+0x520] | 1 | al | 0x6667a3d | Alloc result | [V] |
| [rdx] | 2 | [rbp+0x328] | 0x6667a5a | Index write | [V] |
| [rsi+0x8A8] | 8 | +2 | 0x6667a5d | Advance pointer | [V] |
| [rbp+0x410] | 2 | ax | 0x6667aa7 | Index count | [V] |
| [rbp+0x520] | 1 | al | 0x6667ac4 | Alloc result | [V] |
| [rbp+0x400] | 8 | 0x2001001 | 0x6667afa | ImGui flags | [V] |
| [rbp+0x442] | 2 | ax | 0x6667b1c | Vertex count | [V] |
| [rbp+0x520] | 1 | al | 0x6667b3a | Alloc result | [V] |
| [rdx] | 4 | [rbp+0x2D8] | 0x6667b56 | Index write | [V] |
| [rsi+0x638] | 8 | +4 | 0x6667b58 | Advance pointer | [V] |
| [rbp+0x444] | 2 | ax | 0x6667ba3 | Index count | [V] |
| [rbp+0x520] | 1 | al | 0x6667bc1 | Alloc result | [V] |
| [rdx] | 2 | [rbp+0x2D0] | 0x6667bde | Vertex attr | [V] |
| [rsi+0x698] | 8 | +2 | 0x6667be1 | Advance pointer | [V] |
| [rbp+0x43C] | 2 | ax | 0x6667c36 | Attr count | [V] |
| [rbp+0x400] | 8 | 0x6401001 | 0x6667c1b | ImGui flags | [V] |
| [rdx+0x10] | 4 | [r8+0x10] | 0x6667c75 | Vertex field | [V] |
| [rdx] | 16 | [r8] | 0x6667c7c | Vertex data | [V] |
| [rdx+0x14] | 1 | [rbp+0x28C] | 0x6667c86 | Vertex byte | [V] |
| [rdx+0x18] | 4 | [rbp+0x290] | 0x6667c91 | Vertex float | [V] |
| [rdx+0x1C] | 4 | [rbp+0x294] | 0x6667c9e | Vertex float | [V] |
| [rdx+0x20] | 4 | [rbp+0x298] | 0x6667cab | Vertex float | [V] |
| [rdx+0x24] | 4 | [rbp+0x29C] | 0x6667cb8 | Vertex float | [V] |
| [rdx+0x28] | 16 | [rbp+0x2A0] | 0x6667cd2 | Vertex xmm | [V] |
| [rdx+0x38] | 16 | [rbp+0x2B0] | 0x6667cd6 | Vertex xmm | [V] |
| [rdx+0x47] | 16 | [rbp+0x2BF] | 0x6667cda | Vertex xmm | [V] |
| [rsi+0x758] | 8 | +0x58 | 0x6667cde | Advance pointer | [V] |
| [rbp+0x42C] | 2 | ax | 0x6667d28 | Draw cmd count | [V] |
| [rbp+0x520] | 1 | al | 0x6667d46 | Alloc result | [V] |
| [rsi+0x818] | 8 | +1 | 0x6667d5f | Advance pointer | [V] |
| [rbp+0x41C] | 2 | ax | 0x6667daa | Buffer calc | [V] |
| [rbp+0x400] | 8 | 0x6405041 | 0x6667d91 | ImGui flags | [V] |
| [rbp+0x520] | 1 | al | 0x6667dc8 | Alloc result | [V] |
| [rsi+0x368] | 8 | +1 | 0x6667de1 | Advance pointer | [V] |
| [rbp+0x480] | 2 | ax | 0x6667e21 | Buffer calc | [V] |
| [rbp+0x400] | 8 | 0x100000006407041 | 0x6667ec8 | ImGui flags | [V] |
| [rbp+0x42A] | 2 | ax | 0x6667ef0 | Draw cmd count | [V] |
| [rbp+0x520] | 1 | al | 0x6667f0e | Alloc result | [V] |
| [rsi+8] | 8 | +0xC8 | 0x6667f33 | Advance | [V] |

---

## Gap Fill-ins (Strictly Between Quoted Addresses)

### Gap 1: 0x6665213..0x6665354 (between Phase 12 end 0x6665213 and Phase 13 start 0x6665354)
```
0x6665213  jmp short 0x666524C                           ; -> loc_666524c
0x6665215  add rdx,rax                                   
0x6665218  cmp rcx,rdx                                   
0x666521b  jae short 0x666524C                           ; -> loc_666524c
0x666521d  sub ecx,eax                                   
0x666521f  shr ecx,4                                     
0x6665222  mov [rbp+0x50],cx                             
0x6665226  mov byte ptr [rbp+0x52],1                     
0x666522a  lea rdx,[rbp+0x50]                            
0x666522e  lea r8,[rbp+0x400]                            
0x6665235  lea rcx,[rbp+0xE8]                            
0x666523c  call 0x5679DB0                                ; -> sub_5679db0
0x6665241  nop                                           
0x6665242  mov rax,[rbp+0x520]                           
0x6665249  mov r8,[rax]                                  
0x666524c  mov rsi,[r8]                                  
0x666524f  mov rax,[rsi+0x60]                            
0x6665253  sub rax,[rsi+0x58]                            
0x6665257  shr rax,2                                     
0x666525b  imul eax,0xAAAAAAAB                           
0x6665261  test eax,eax                                  
0x6665263  je short 0x666529B                            ; -> loc_666529b
0x6665265  mov edx,0x250                                 
0x666526a  add rdx,[rbp+0xE0]                            
0x6665271  lea rcx,[rbp+0x1E0]                           
0x6665278  xor r8d,r8d                                   
0x666527b  call 0xBBD7C70                                ; -> sub_bbd7c70
0x6665280  nop                                           
0x6665281  lea rdx,[rbp+0x1E0]                           
0x6665288  mov rcx,rsi                                   
0x666528b  call 0x4DEDD00                                ; -> sub_4dedd00
0x6665290  nop                                           
0x6665291  mov rax,[rbp+0x520]                           
0x6665298  mov r8,[rax]                                  
0x666529b  xorps xmm6,xmm6                               
0x666529e  movaps [rbp+0x190],xmm6                       
0x66652a5  mov qword ptr [rbp+0x1A0],0                   
0x66652b0  mov rax,[r8+0x18]                             
0x66652b4  mov [rbp+0x1E0],rax                           
0x66652bb  test rax,rax                                  
0x66652be  mov [rbp+0x1D8],r13                           
0x66652c5  mov [rbp+0x518],rsi                           
0x66652cc  je short 0x6665304                            ; -> loc_6665304
0x66652ce  shr rax,0x3A                                  
0x66652d2  jne 0x6668455                                 ; -> sub_6668455
0x66652d8  lea rcx,[rbp+0x190]                           
0x66652df  lea rdx,[rbp+0x1E0]                           
0x66652e6  call 0x4E69050                                ; -> sub_4e69050
0x66652eb  nop                                           
0x66652ec  mov rcx,[rbp+0x520]                           
0x66652f3  mov r8,[rcx]                                  
0x66652f6  mov rax,[r8+0x18]                             
0x66652fa  shl rax,2                                     
0x66652fe  lea rsi,[rax+rax*2]                           
0x6665302  jmp short 0x666530D                           ; -> loc_666530d
0x6665304  xor esi,esi                                   
0x6665306  mov rcx,[rbp+0x520]                           
0x666530d  mov r15,[r8+0x20]                             
0x6665311  add rsi,r15                                   
0x6665314  lea rbx,[rbp+0x404]                           
0x666531b  lea rdi,[rcx+8]                               
0x666531f  movss xmm7,[0xEEC8060]                        ; [data_eec8060]
0x6665327  movsd xmm8,[0xEFD32F0]                        ; [data_efd32f0]
0x6665330  movaps xmm9,[0xF0A4080]                       ; [data_f0a4080]
0x6665338  lea r12,[rbp+0x1E0]                           
0x666533f  lea r13,[rbp+0x400]                           
0x6665346  cmp r15,rsi                                   
0x6665349  jne 0x6665444                                 ; -> loc_6665444
0x666534f  jmp 0x66654F4                                 ; -> loc_66654f4
```

### Gap 2: 0x66658be..0x6665922 (between Phase 21 end 0x66658be and Phase 22 start 0x6665922)
```
0x66658be  jmp short 0x66658E7                           ; -> loc_66658e7
0x66658c0  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x66658c7  mov rax,[rcx]                                 
0x66658ca  mov rax,[rax+8]                               
0x66658ce  mov rdx,r15                                   
0x66658d1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66658d7  nop                                           
0x66658d8  mov r12,rax                                   
0x66658db  mov r13,r14                                   
0x66658de  test rax,rax                                  
0x66658e1  je 0x66681A5                                  ; -> sub_66681a5
0x66658e7  mov [rbp+0x270],r12                           
0x66658ee  lea r14,[r12+r15]                             
0x66658f2  mov [rbp+0x280],r14                           
0x66658f9  mov rcx,r12                                   
0x66658fc  mov rdx,rdi                                   
0x66658ff  mov r8,r15                                    
0x6665902  call 0xEEC6DE0                                ; -> sub_eec6de0
0x6665907  mov [rbp+0x278],r14                           
0x666590e  mov r14,r13                                   
0x6665911  mov r13,rbx                                   
0x6665914  mov r12,[rbp+0x508]                           
0x666591b  mov rbx,[rbp+0x518]                           
```

### Gap 3: 0x6666565..0x666658c (between Phase 23 end 0x6666565 and Phase 24 start 0x666658c)
```
0x6666565  jne short 0x666658C                           ; -> loc_666658c
0x6666567  mov rax,[rdi]                                 
0x666656a  mov rax,[rax]                                 
0x666656d  mov rcx,rdi                                   
0x6666570  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6666576  lock dec dword ptr [rdi+0xC]                  
0x666657a  jne short 0x666658C                           ; -> loc_666658c
0x666657c  mov rax,[rdi]                                 
0x666657f  mov rax,[rax+8]                               
0x6666583  mov rcx,rdi                                   
0x6666586  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

### Gap 4: 0x6666e4c..0x6666f58 (between Phase 47 end 0x6666e4c and Phase 48 start 0x6666f58)
```
0x6666e4c  call 0xE86B370                                ; -> sub_e86b370
0x6666e51  nop                                           
0x6666e52  mov qword ptr [rbp+0xD0],0                    
0x6666e5d  mov dword ptr [rbp+0x190],0x3F800000          
0x6666e67  lea rax,[rbp+0x194]                           
0x6666e6e  movups [rax],xmm6                             
0x6666e71  mov dword ptr [rbp+0x1A4],0x3F800000          
0x6666e7b  movups [rax+0x14],xmm6                        
0x6666e7f  mov dword ptr [rbp+0x1B8],0x3F800000          
0x6666e89  movups [rax+0x28],xmm6                        
0x6666e8d  mov dword ptr [rbp+0x1CC],0x3F800000          
0x6666e97  mov byte ptr [rbp+0x1D0],0                    
0x6666e9e  mov [rbp+0x1E2],si                            
0x6666ea5  mov rax,0x200000000                           
0x6666eaf  mov [rbp+0x1E4],rax                           
0x6666eb6  mov byte ptr [rbp+0x1EC],7                    
0x6666ebd  mov dword ptr [rbp+0x1F0],0                   
0x6666ec7  mov word ptr [rbp+0x1F4],0                    
0x6666ed0  mov byte ptr [rbp+0x1F6],8                    
0x6666ed7  mov dword ptr [rbp+0x1F8],0                   
0x6666ee1  mov byte ptr [rbp+0x1FC],1                    
0x6666ee8  movups [rbp+0x200],xmm7                       
0x6666eef  mov dword ptr [rbp+0x210],0                   
0x6666ef9  mov qword ptr [rbp+0x214],0                   
0x6666f04  mov byte ptr [rbp+0x21C],8                    
0x6666f0b  mov qword ptr [rbp+0x220],0                   
0x6666f16  mov dword ptr [rbp+0x228],0                   
0x6666f20  mov byte ptr [rbp+0x22C],8                    
0x6666f27  mov qword ptr [rdi+0x54],0                    
0x6666f2f  mov qword ptr [rdi+0x4E],0                    
0x6666f37  mov byte ptr [rbp+0x23E],0xFF                 
0x6666f3e  mov rax,[rbp+0x50]                            
0x6666f42  mov [rbp+0x240],rax                           
0x6666f49  lea rcx,[rbp+0x248]                           
0x6666f50  mov rdx,rbx                                   
0x6666f53  call 0xE869FF0                                ; -> sub_e869ff0
```

### Gap 5: 0x6667be9..0x6667bff (between Phase 62 end 0x6667be9 and Phase 63 start 0x6667bff)
```
0x6667be9  jmp short 0x6667BFF                           ; -> loc_6667bff
0x6667beb  lea r8,[rbp+0x2D0]                            
0x6667bf2  lea rcx,[rsi+0x690]                           
0x6667bf9  call 0x1EF6F90                                ; -> sub_1ef6f90
0x6667bfe  nop                                           
```

---

## Cold Blocks: 0x6668107..0x6668510 (Out-of-line error/allocation-failure paths after main ret at 0x6668106)

Each block: sets ECX=allocation size → calls sub_9BC830 (allocator failure handler) → jmp back to hot-path site.

```
0x6668107  mov ecx,0x20                                  
0x666810c  call 0x9BC830                                 ; -> sub_9bc830
0x6668111  nop                                           
0x6668112  jmp 0x6665960                                 ; -> sub_6665960  (hot: 0x6665960 alloc 0x20 fail)
0x6668117  mov ecx,0x20                                  
0x666811c  call 0x9BC830                                 ; -> sub_9bc830
0x6668121  nop                                           
0x6668122  jmp 0x666640C                                 ; -> sub_666640c  (hot: 0x666640c alloc 0x20 fail)
0x6668127  mov ecx,0x30                                  
0x666812c  call 0x9BC830                                 ; -> sub_9bc830
0x6668131  nop                                           
0x6668132  jmp 0x6665A14                                 ; -> sub_6665a14  (hot: 0x6665a14 alloc 0x30 fail)
0x6668137  mov ecx,0x70                                  
0x666813c  call 0x9BC830                                 ; -> sub_9bc830
0x6668141  nop                                           
0x6668142  jmp 0x6665A72                                 ; -> sub_6665a72  (hot: 0x6665a72 alloc 0x70 fail)
0x6668147  mov ecx,0x128                                 
0x666814c  call 0x9BC830                                 ; -> sub_9bc830
0x6668151  nop                                           
0x6668152  jmp 0x6665B18                                 ; -> sub_6665b18  (hot: 0x6665b18 alloc 0x128 fail)
0x6668157  mov ecx,0xA8                                  
0x666815c  call 0x9BC830                                 ; -> sub_9bc830
0x6668161  nop                                           
0x6668162  jmp 0x6665B5E                                 ; -> sub_6665b5e  (hot: 0x6665b5e alloc 0xA8 fail)
0x6668167  mov ecx,0x30                                  
0x666816c  call 0x9BC830                                 ; -> sub_9bc830
0x6668171  nop                                           
0x6668172  jmp 0x66664BA                                 ; -> sub_66664ba  (hot: 0x66664ba alloc 0x30 fail)
0x6668177  mov ecx,0x18                                  
0x666817c  call 0x9BC830                                 ; -> sub_9bc830
0x6668181  nop                                           
0x6668182  jmp 0x6666518                                 ; -> sub_6666518  (hot: 0x6666518 alloc 0x18 fail)
0x6668187  mov ecx,0xA0                                  
0x666818c  call 0x9BC830                                 ; -> sub_9bc830
0x6668191  nop                                           
0x6668192  jmp 0x66665B2                                 ; -> sub_66665b2  (hot: 0x66665b2 alloc 0xA0 fail)
0x6668197  mov rcx,r13                                   
0x666819a  call 0x9BC830                                 ; -> sub_9bc830
0x666819f  nop                                           
0x66681a0  jmp 0x66658AB                                 ; -> sub_66658ab  (hot: 0x66658ab alloc 0xA8? fail, rcx=r13)
0x66681a5  mov rcx,r15                                   
0x66681a8  call 0x9BC830                                 ; -> sub_9bc830
0x66681ad  nop                                           
0x66681ae  xor r12d,r12d                                 
0x66681b1  jmp 0x66658E7                                 ; -> sub_66658e7  (hot: 0x66658e7 alloc fail, rcx=r15)
0x66681b6  mov rcx,r13                                   
0x66681b9  call 0x9BC830                                 ; -> sub_9bc830
0x66681be  nop                                           
0x66681bf  jmp 0x6666364                                 ; -> sub_6666364  (hot: 0x6666364 alloc 0xA0? fail, rcx=r13)
0x66681c4  mov rcx,r15                                   
0x66681c7  call 0x9BC830                                 ; -> sub_9bc830
0x66681cc  nop                                           
0x66681cd  xor r12d,r12d                                 
0x66681d0  jmp 0x6666374                                 ; -> sub_6666374  (hot: 0x6666374 alloc fail, rcx=r15)
0x66681d5  mov rcx,rsi                                   
0x66681d8  call 0x9BC830                                 ; -> sub_9bc830
0x66681dd  nop                                           
0x66681de  jmp 0x6665BF5                                 ; -> sub_6665bf5  (hot: 0x6665bf5 alloc 0x18? fail, rcx=rsi)
0x66681e3  mov rcx,rsi                                   
0x66681e6  call 0x9BC830                                 ; -> sub_9bc830
0x66681eb  nop                                           
0x66681ec  xor r15d,r15d                                 
0x66681ef  jmp 0x6665D04                                 ; -> sub_6665d04  (hot: 0x6665d04 alloc fail, rcx=rsi)
0x66681f4  mov rcx,rsi                                   
0x66681f7  call 0x9BC830                                 ; -> sub_9bc830
0x66681fc  nop                                           
0x66681fd  jmp 0x6666687                                 ; -> sub_6666687  (hot: 0x6666687 alloc fail, rcx=rsi)
0x6668202  mov rcx,rsi                                   
0x6668205  call 0x9BC830                                 ; -> sub_9bc830
0x666820a  nop                                           
0x666820b  xor r15d,r15d                                 
0x666820e  jmp 0x66666B3                                 ; -> sub_66666b3  (hot: 0x66666b3 alloc fail, rcx=rsi)
0x6668213  call 0x75B60                                  ; -> sub_75b60  (no return to hot path)
0x6668218  nop                                           
0x6668219  mov qword ptr [rsp+0x20],0                    
0x6668222  xor ecx,ecx                                   
0x6668224  xor edx,edx                                   
0x6668226  xor r8d,r8d                                   
0x6668229  xor r9d,r9d                                   
0x666822c  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
0x6668232  lea rcx,[0x129F8F50]                          ; [data_129f8f50]
0x6668239  call 0xE938CB0                                ; -> sub_e938cb0
0x666823e  cmp dword ptr [0x129F8F50],0xFFFFFFFF         ; [data_129f8f50]
0x6668245  jne 0x6664AD7                                 ; -> sub_6664ad7  (rejoin UIImGui)
0x666824b  xorps xmm0,xmm0                               
0x666824e  movaps [rbp+0x40],xmm0                        
0x6668252  lea rax,[0xF5AD096]                           ; [data_f5ad096] "Debug/ImGui"
0x6668259  mov [rbp+0x390],rax                           
0x6668260  mov qword ptr [rbp+0x398],0xB                 
0x666826b  lea rcx,[0x129F8F40]                          ; [data_129f8f40]
0x6668272  lea rdx,[rbp+0x390]                           
0x6668279  lea r8,[rbp+0x40]                             
0x666827d  call 0x5668AC0                                ; -> sub_5668ac0
0x6668282  nop                                           
0x6668283  lea rcx,[0x129F8F50]                          ; [data_129f8f50]
0x666828a  call 0xE938D70                                ; -> sub_e938d70
0x666828f  jmp 0x6664AD7                                 ; -> sub_6664ad7
0x6668294  lea rcx,[0x129F9398]                          ; [data_129f9398]
0x666829b  call 0xE938CB0                                ; -> sub_e938cb0
0x66682a0  cmp dword ptr [0x129F9398],0xFFFFFFFF         ; [data_129f9398]
0x66682a7  jne 0x6664D7D                                 ; -> sub_6664d7d  (rejoin UI/Blit)
0x66682ad  xorps xmm0,xmm0                               
0x66682b0  movaps [rbp+0x4E0],xmm0                       
0x66682b7  lea rax,[0xF539A95]                           ; [data_f539a95] "UI/Blit"
0x66682be  mov [rbp+0x40],rax                            
0x66682c2  mov qword ptr [rbp+0x48],7                    
0x66682ca  lea rcx,[0x129F9388]                          ; [data_129f9388]
0x66682d1  lea rdx,[rbp+0x40]                            
0x66682d5  lea r8,[rbp+0x4E0]                            
0x66682dc  call 0x5668AC0                                ; -> sub_5668ac0
0x66682e1  nop                                           
0x66682e2  lea rcx,[0x129F9398]                          ; [data_129f9398]
0x66682e9  call 0xE938D70                                ; -> sub_e938d70
0x66682ee  jmp 0x6664D7D                                 ; -> sub_6664d7d
0x66682f3  call 0x1166E0                                 ; -> sub_1166e0
0x66682f8  nop                                           
0x66682f9  call 0x75740                                  ; -> sub_75740
0x66682fe  nop                                           
0x66682ff  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
0x6668306  call 0xE938CB0                                ; -> sub_e938cb0
0x666830b  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
0x6668312  jne 0x6664B65                                 ; -> sub_6664b65  (rejoin UI/Blit alt)
0x6668318  lea rcx,[0x129CA568]                          ; [data_129ca568]
0x666831f  call 0x567DB00                                ; -> sub_567db00
0x6668324  nop                                           
0x6668325  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
0x666832c  call 0xE935740                                ; -> sub_e935740
0x6668331  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
0x6668338  call 0xE938D70                                ; -> sub_e938d70
0x666833d  jmp 0x6664B65                                 ; -> sub_6664b65
0x6668342  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
0x6668349  call 0xE938CB0                                ; -> sub_e938cb0
0x666834e  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
0x6668355  jne 0x6664E0B                                 ; -> sub_6664e0b  (rejoin UI/Blit alt2)
0x666835b  lea rcx,[0x129CA568]                          ; [data_129ca568]
0x6668362  call 0x567DB00                                ; -> sub_567db00
0x6668367  nop                                           
0x6668368  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
0x666836f  call 0xE935740                                ; -> sub_e935740
0x6668374  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
0x666837b  call 0xE938D70                                ; -> sub_e938d70
0x6668380  jmp 0x6664E0B                                 ; -> sub_6664e0b
0x6668385  xorps xmm0,xmm0                               
0x6668388  movups [rbp+0x408],xmm0                       
0x666838f  lea rax,[0xF08E738]                           ; [data_f08e738]
0x6668396  mov [rbp+0x400],rax                           
0x666839d  lea rdx,[0xFB3B080]                           ; [data_fb3b080]
0x66683a4  lea rcx,[rbp+0x400]                           
0x66683ab  call 0xEEC6D80                                ; -> sub_eec6d80
0x66683b0  nop                                           
0x66683b1  xorps xmm0,xmm0                               
0x66683b4  movups [rbp+0x1E8],xmm0                       
0x66683bb  lea rax,[0xF08E738]                           ; [data_f08e738]
0x66683c2  mov [rbp+0x1E0],rax                           
0x66683c9  lea rdx,[0xFB3B080]                           ; [data_fb3b080]
0x66683d0  lea rcx,[rbp+0x1E0]                           
0x66683d7  call 0xEEC6D80                                ; -> sub_eec6d80
0x66683dc  nop                                           
0x66683dd  lea rcx,[0x129F8F60]                          ; [data_129f8f60]
0x66683e4  call 0xE938CB0                                ; -> sub_e938cb0
0x66683e9  cmp dword ptr [0x129F8F60],0xFFFFFFFF         ; [data_129f8f60]
0x66683f0  jne 0x6666C4E                                 ; -> sub_6666c4e  (rejoin UIImGui element loop)
0x66683f6  lea rdx,[0xF5ACD53]                           ; [data_f5acd53] "ImGuiProj"
0x66683fd  lea rdi,[rbp+0x1E0]                           
0x6668404  mov rcx,rdi                                   
0x6668407  call 0x79580                                  ; -> sub_79580
0x666840c  nop                                           
0x666840d  mov r8,[rbp+0x1F0]                            
0x6668414  cmp qword ptr [rbp+0x1F8],0x10                
0x666841c  jb short 0x6668425                            ; -> loc_6668425
0x666841e  mov rdi,[rbp+0x1E0]                           
0x6668425  test r8,r8                                    
0x6668428  je short 0x6668467                            ; -> loc_6668467
0x666842a  mov eax,r8d                                   
0x666842d  and eax,3                                     
0x6668430  mov rcx,0x100000001B3                         
0x666843a  cmp r8,4                                      
0x666843e  jae short 0x6668473                           ; -> loc_6668473
0x6668440  mov rdx,0xCBF29CE484222325                    
0x666844a  xor r9d,r9d                                   
0x666844d  jmp short 0x66684C5                           ; -> loc_66684c5
0x666844f  call 0x75B60                                  ; -> sub_75b60
0x6668454  nop                                           
0x6668455  call 0x75B60                                  ; -> sub_75b60
0x666845a  nop                                           
0x666845b  call 0x75720                                  ; -> sub_75720
0x6668460  nop                                           
0x6668461  call 0x75720                                  ; -> sub_75720
0x6668466  nop                                           
0x6668467  mov rdx,0xCBF29CE484222325                    
0x6668471  jmp short 0x66684E5                           ; -> loc_66684e5
0x6668473  and r8,0xFFFFFFFFFFFFFFFC                     
0x6668477  mov rdx,0xCBF29CE484222325                    
0x6668481  xor r9d,r9d                                   
0x6668484  movzx r10d,byte ptr [rdi+r9]                  
0x6668489  xor r10,rdx                                   
0x666848c  imul r10,rcx                                  
0x6668490  movzx edx,byte ptr [rdi+r9+1]                 
0x6668496  xor rdx,r10                                   
0x6668499  imul rdx,rcx                                  
0x666849d  movzx r10d,byte ptr [rdi+r9+2]                
0x66684a3  xor r10,rdx                                   
0x66684a6  imul r10,rcx                                  
0x66684aa  movzx edx,byte ptr [rdi+r9+3]                 
0x66684b0  xor rdx,r10                                   
0x66684b3  imul rdx,rcx                                  
0x66684b7  add r9,4                                      
0x66684bb  cmp r8,r9                                     
0x66684be  jne short 0x6668484                           ; -> loc_6668484
0x66684c0  test rax,rax                                  
0x66684c3  je short 0x66684E5                            ; -> loc_66684e5
0x66684c5  add rdi,r9                                    
0x66684c8  xor r8d,r8d                                   
0x66684cb  mov r9,rdx                                    
0x66684ce  movzx edx,byte ptr [rdi+r8]                   
0x66684d3  xor rdx,r9                                    
0x66684d6  imul rdx,rcx                                  
0x66684da  inc r8                                        
0x66684dd  mov r9,rdx                                    
0x66684e0  cmp rax,r8                                    
0x66684e3  jne short 0x66684CE                           ; -> loc_66684ce
0x66684e5  mov [0x129F8F58],rdx                          ; [data_129f8f58]
0x66684ec  lea rcx,[rbp+0x1E0]                           
0x66684f3  call 0x73150                                  ; -> sub_73150
0x66684f8  lea rcx,[0x129F8F60]                          ; [data_129f8f60]
0x66684ff  call 0xE938D70                                ; -> sub_e938d70
0x6668504  mov r12,[rbp+0x508]                           
0x666850b  jmp 0x6666C4E                                 ; -> sub_6666c4e  (rejoin UIImGui element loop)
```

---

## Final String Reference Table (All Phases + Gaps + Cold)

| String RVA | Text | Call Site RVA | Callee After |
|------------|------|---------------|--------------|
| 0xF5AD096 | "Debug/ImGui" | 0x6664ae9, 0x6668252, 0x6668322, 0x66683e8, 0x66684b5 (lea rax) | 0x675E440, 0x5668AC0 (sub_675e440, sub_5668ac0) |
| 0xF539A95 | "UI/Blit" | 0x6664d8f, 0x66682b7, 0x6668387, 0x6668456 (lea rax) | 0x675E440, 0x5668AC0 (sub_675e440, sub_5668ac0) |
| 0xF58B3B6 | "Unnamed Transaction" | 0x6665986, 0x6666432 (movups xmm0) | 0xEEC6E70 (sub_eec6e70) |
| 0xF58B3C5 | "tion" | 0x666597d, 0x6666429 (mov eax) | 0xEEC6E70 (sub_eec6e70) |
| 0xF8407B6 | (format string) | 0x6665d92, 0x666673e (lea r9) | 0xA0850 (sub_a0850) |
| 0xF5BF71C | "ImGuiProj" | 0x66683f6 (lea rax) | 0x5668AC0 (sub_5668ac0) |
| 0xF0F9C30 | (vtable) | 0x6665a29, 0x66660dc, 0x66660f4 (lea rax) | — |
| 0xF0F9C50 | (vtable) | 0x66660dc, 0x66660f4 (lea rax) | — |
| 0xF0F9C60 | (vtable) | 0x66664cf (lea rax) | — |
| 0xF0F9C80 | (vtable) | 0x666660f, 0x666662b (lea rax) | — |
| 0xF2BEE70 | (vtable) | 0x6665b2a (lea rax) | — |
| 0xF2BEE88 | (vtable) | 0x66665bd (lea rax) | — |
| 0xF2BF468 | (jump table) | 0x6664a5c (lea rcx) | — |
| 0xF2BF47C | (jump table) | 0x6667006, 0x6667076 (lea rdx) | — |
| 0xF2BF48C | (jump table) | 0x6665c96 (lea rdx) | — |
| 0xEF40DE0 | (xmm const) | 0x6664c90 (movaps xmm0) | — |

---

## Final [reg+off] Write Table (Non-Stack, Output Descriptions/Records)

| Offset | Size | Source | Instruction (RVA) | Meaning | Tag |
|--------|------|--------|-------------------|---------|-----|
| [rbp+0x520] | 8 | r9 (arg2+0x0) | 0x6664aab, 0x6664d51 | UIImGui/UI/Blit: desc base pointer | [V] |
| [rbp+0x400] | 8 | string RVA | 0x6664af0, 0x6664d96 | Pass name string pointer | [V] |
| [rbp+0x408] | 8 | length | 0x6664af7, 0x6664d9d | Pass name length | [V] |
| [rbp+0x4D0] | 8 | call result | 0x6664b2d | Pass object (Debug/ImGui) | [V] |
| [rbp+0x390] | 8 | call result | 0x6664dd3 | Pass object (UI/Blit) | [V] |
| [rbp+0x520] | 1 | cl/r12b/dil | 0x6664c44, 0x6664c4a, 0x6664c51 | Extracted desc bytes | [V] |
| [rbp+0x224] | 1 | 0 | 0x6664c0e | Zero init | [V] |
| [rbp+0x400] | 16 | xmm/const | 0x6664c61, 0x6664c97, 0x6664ca9, 0x6664e85 | SIMD init | [V] |
| [rbp+0x1E0] | 16 | [0xEF40DE0] | 0x6664c97 | Constant xmm load | [V] |
| [rbp+0x400] | 8 | r12/r15 | 0x6664e9b, 0x6664ea2 | Alt path resource | [V] |
| [rbp+0x1E0] | 16 | xmm0 | 0x6664fcf | Zero xmm | [V] |
| [rbp+0xE0] | 8 | rax | 0x66650a8 | Resource ptr | [V] |
| [rbp+0x160] | 8 | rbx | 0x66650c6 | Save rbx | [V] |
| [rbp+0x258] | 8 | 0 | 0x6665040 | Zero init | [V] |
| [rbp+0x400] | 2 | ax | 0x666516c | Computed element index | [V] |
| [rbp+0x402] | 1 | 1 | 0x6665173 | Flag | [V] |
| [rbp+0x1EC] | 1 | 0 | 0x666517a | Flag | [V] |
| [rbp+0x1E0] | 16 | [r8+0x28] broadcast | 0x66651b8 | Float from source+0x28 | [V] |
| [rbp+0x400] | 8 | 1 | 0x66651bf | Constant 1 | [V] |
| [rbp+0x408] | 8 | rsi | 0x66651ca | Save rsi | [V] |
| [rdx+0x00..0x3C] | 16x4 | [rbp+0x1E0..0x21C] | 0x6665368..0x666542a | Matrix write (16 floats) | [V] |
| [rbx+0x00] | 16 | xmm6 | 0x666544e | Constant xmm6 store | [V] |
| [rbx+0x14] | 16 | xmm6 | 0x666545b | Constant xmm6 store | [V] |
| [rbp+0x428] | 16 | xmm2 | 0x66654a6 | Computed SIMD result | [V] |
| [rbp+0x438] | 8 | xmm1 (low) | 0x66654ad | Computed SIMD result | [V] |
| [r13+0x3B0] | 2 | bx+1 | 0x666551a | Increment counter | [V] |
| [rbp+0x1A0] | 8 | 0 | 0x6665529 | Zero | [V] |
| [rbp+0x3A0] | 16 | [rbp+0x190] | 0x6665545 | Matrix save | [V] |
| [rbp+0x190] | 16 | 0 | 0x666553e | Zero | [V] |
| [rbp+0x3B0] | 8 | [rbp+0x1A0] | 0x666554c | Save previous | [V] |
| [rbp+0x3E0] | 1 | 1 | 0x6665553 | Flag = 1 | [V] |
| [rbp+0x4D0] | 16 | 0 | 0x6665565 | Zero | [V] |
| [rbp+0x4D0] | 8 | [rcx+0x1B8] | 0x666559e | Resource pointer | [V] |
| [rbp+0x4D8] | 8 | rax | 0x66655ac | Resource swap | [V] |
| [rbp+0x260] | 2 | r8w | 0x666581e | Save | [V] |
| [rbp+0x268] | 4 | r12d | 0x6665833 | Save | [V] |
| [rbp+0x270] | 16 | 0 | 0x6665848 | Zero | [V] |
| [rbp+0x280] | 8 | 0 | 0x666584f | Zero | [V] |
| [rbp+0x270] | 8 | r12 (alloc) | 0x66658e7 | Allocated buffer | [V] |
| [rbp+0x280] | 8 | r14 (end) | 0x66658f2 | Buffer end | [V] |
| [rbp+0x278] | 8 | r14 | 0x6665907 | Buffer end (dup) | [V] |
| [rdi+0x00..0x0F] | 16 | "Unnamed Transaction" | 0x666598d, 0x6666439 | Transaction name | [V] |
| [rdi+0x0F] | 4 | "tion" | 0x6665983, 0x666642f | Transaction name suffix | [V] |
| [rdi+0x10] | 8 | 0x13 | 0x6665967, 0x6666413 | Transaction field | [V] |
| [rdi+0x18] | 8 | 0x1F | 0x6665972, 0x666641e | Transaction field | [V] |
| [rdi+0x13] | 1 | 0 | 0x6665990, 0x666643c | Transaction field | [V] |
| [rbp+0x3A0] | 16 | 0 | 0x66659ad, 0x6666459 | Zero | [V] |
| [rdi+0x08] | 8 | 0x100000001 | 0x6665a1e, 0x66664c4 | Refcount init | [V] |
| [rdi+0x00] | 8 | 0xF0F9C30 | 0x6665a29, 0x66660dc, 0x66660f4 | Vtable pointer | [V] |
| [rdi+0x10..0x6F] | 96 | 0 | 0x6665a3d..0x6665a8c, 0x66669a3 | Zero init | [V] |
| [rdi+0x00] | 2 | 0xFFFF | 0x6665a90, 0x6666530 | Word init | [V] |
| [rdi+0x0C] | 2 | 0xFFFF | 0x6665a95, 0x6666535 | Word init | [V] |
| [rax+0x28] | 8 | rdi | 0x6665aa2, 0x666653c | Link objects | [V] |
| [rbp+0xE0] | 8 | rcx | 0x6665ab4, 0x6666bcd | Save pointer | [V] |
| [rbp+0xE8] | 8 | rax | 0x6665abb, 0x6666b6e | Swap | [V] |
| [rbp+0x518] | 8 | rdi (alloc) | 0x6665b18, 0x6666b18 | Large alloc | [V] |
| [rbp+0x400] | 8 | 0xF2BEE70 | 0x6665b31, 0x66665c4 | Vtable | [V] |
| [rbp+0x408] | 8 | 0 | 0x6665b1f, 0x6666555 | Zero | [V] |
| [rdi+0x78] | 8 | 0 | 0x6665b5e, 0x666662e | Zero field | [V] |
| [rbp+0x3A0] | 8 | r15 | 0x6665d04, 0x6666d04 | Large alloc result | [V] |
| [rbp+0x3B0] | 8 | rbx | 0x6665d0b, 0x6666d0b | Size | [V] |
| [rbp+0x3B8] | 8 | r12 | 0x6665d12, 0x6666d12 | Capacity | [V] |
| [r15+rbx] | 1 | 0 | 0x6665d27, 0x6666d27 | Null terminator | [V] |
| [rbp+0x190] | 16 | 0 | 0x6665d2f, 0x6666d2f | Zero | [V] |
| [rbp+0x190] | 1 | 0x3C | 0x6665d4c, 0x6666d4c | Byte init | [V] |
| [rbp+0x1A0] | 8 | 1 | 0x6665d36, 0x6666d36 | Init | [V] |
| [rbp+0x1A8] | 8 | 0xF | 0x6665d41, 0x6666d41 | Init | [V] |
| [rdi+0x00] | 2 | 0x203E | 0x6665dc2, 0x6666777 | Write "> " | [V] |
| [rdi+0x02] | 1 | 0 | 0x6665dc8, 0x666677d | Null terminator | [V] |
| [rbp+0xE0] | 16 | [rdi] | 0x6665ddb, 0x6666ddb | Save xmm0 | [V] |
| [rbp+0xF0] | 16 | [rdi+0x10] | 0x6665dd4, 0x6666dd4 | Save xmm1 | [V] |
| [rdi+0x10] | 8 | 0 | 0x6665de2, 0x6666797 | Reset string len | [V] |
| [rdi+0x18] | 8 | 0xF | 0x6665dea, 0x666679f | Reset string cap | [V] |
| [rdi+0x00] | 1 | 0 | 0x6665df2, 0x66667a7 | Reset first char | [V] |
| [rbp+0xF0] | 8 | 0 | 0x6665e55, 0x666686c | Zero buffer ptr | [V] |
| [rbp+0xF8] | 8 | 0xF | 0x6665e60, 0x6666877 | Reset cap | [V] |
| [rbp+0xE0] | 1 | 0 | 0x6665e6b, 0x6666882 | Zero first char | [V] |
| [rbp+0x60] | 8 | 0 | 0x6665eb1, 0x66668b1 | Zero len | [V] |
| [rbp+0x68] | 8 | 0xF | 0x6665eb9, 0x666687f | Reset cap | [V] |
| [rbp+0x50] | 1 | 0 | 0x6665ec1, 0x66668c1 | Zero first char | [V] |
| [r15+0x00] | 8 | 0xF0F9C50 | 0x66660dc/0x66660f4 | Vtable | [V] |
| [r15+0x08] | 8 | [rbp+0xE0] | 0x66660df | Ptr | [V] |
| [r15+0x10] | 8 | rdi | 0x66660e3 | Ptr | [V] |
| [r15+0x18] | 16 | 0 | 0x6666106 | Zero | [V] |
| [r15+0x18..0x118] | 16x10 | 0 | 0x6666148..0x66661a5 | Zero init | [V] |
| [r15+0x90] | 8 | 0xF | 0x6666162 | SSO cap | [V] |
| [r15+0x118] | 8 | 0 | 0x66661ad | Zero | [V] |
| [r15+0x120] | 8 | rsi | 0x66661b8 | Link to rbx+0x9B0 | [V] |
| [rbp+0x400] | 8 | r15 | 0x66661fe | Save transaction | [V] |
| [rdi+0x10] | 1 | 1 | 0x6666255 | Flag | [V] |
| [rbp+0x170] | 8 | rdi | 0x666629b | Save | [V] |
| [rbp+0x178] | 8 | rax | 0x66662a2 | Save | [V] |
| [rbp+0x4E8] | 8 | r12 (alloc) | 0x66663a0 | copySrcB buffer | [V] |
| [rbp+0x4F8] | 8 | rsi (end) | 0x66663ab | Buffer end | [V] |
| [rbp+0x4F0] | 8 | rsi | 0x66663c0 | memcpy result | [V] |
| [rbp+0x50] | 8 | r15 | 0x66666b3 | Large alloc ptr | [V] |
| [rbp+0x60] | 8 | rbx | 0x66666b7 | Size | [V] |
| [rbp+0x68] | 8 | r12 | 0x66666bb | Capacity | [V] |
| [r15+rbx] | 1 | 0 | 0x66666cd | Null terminator | [V] |
| [rbp+0x3A0] | 16 | 0 | 0x66666d5 | Zero | [V] |
| [rbp+0x3B0] | 8 | 1 | 0x66666dc | Len | [V] |
| [rbp+0x3B8] | 8 | 0xF | 0x66666e7 | Cap | [V] |
| [rbp+0x3A0] | 1 | 0x3C | 0x66666f2 | Byte init | [V] |
| [rdx+rax] | 2 | 0x203E | 0x6666777 | Write "> " | [V] |
| [rdx+rax+2] | 1 | 0 | 0x666677d | Null | [V] |
| [rbp+0xF0] | 8 | rdx | 0x6666760 | Updated len | [V] |
| [rbp+0x410] | 8 | 0 | 0x666680a | Zero | [V] |
| [rbp+0x418] | 8 | 0xF | 0x6666815 | Cap | [V] |
| [rbp+0x400] | 1 | 0 | 0x6666820 | Char | [V] |
| [rbp+0xF0] | 8 | 0 | 0x666686c | Zero | [V] |
| [rbp+0xF8] | 8 | 0xF | 0x6666877 | Cap | [V] |
| [rbp+0xE0] | 1 | 0 | 0x6666882 | Char | [V] |
| [rdi] | 8 | 0xF0F9C80 | 0x66669a0 | Vtable | [V] |
| [rdi+0x08] | 16 | 0 | 0x66669a3 | Zero | [V] |
| [rdi+0x18] | 16 | 0 | 0x66669b1 | Zero | [V] |
| [rdi+0x18] | 8 | rax | 0x66669ee | Ptr | [V] |
| [rdi+0x58..0x90] | 16x3 | 0 | 0x66669f2..0x66669fe | Zero init | [V] |
| [rdi+0x88] | 8 | 0 | 0x66669fe | Zero | [V] |
| [rdi+0x90] | 8 | 0xF | 0x6666a09 | SSO cap | [V] |
| [rdi+0x98] | 8 | rsi | 0x6666a14 | Link | [V] |
| [rbp+0x1E0] | 8 | 0 | 0x66669e3 | Zero | [V] |
| [rbp+0x1E0] | 8 | rdi | 0x6666a5b | Save object | [V] |
| [rdi+0x10] | 1 | 1 | 0x6666ab2 | Flag | [V] |
| [rbp+0x180] | 8 | rdi | 0x6666af8 | Save | [V] |
| [rbp+0x188] | 8 | rax | 0x6666aff | Save | [V] |
| [rbp+0xE0] | 8 | [[rbp+0x1E0]+0x18] | 0x6666bcd | Resource ptr | [V] |
| [rbp+0x518] | 8 | r15+rax*40 | 0x6666c84 | Array end | [V] |
| [rbp+0x4E0] | 16 | 0 | 0x6666cd8 | Zero | [V] |
| [rbp+0x4E0] | 8 | [rbp+0x180] | 0x6666d09 | Ptr | [V] |
| [rbp+0x4E8] | 8 | [rbp+0x188] | 0x6666d10 | Ptr | [V] |
| [rbp+0x30] | 16 | 0 | 0x6666d17 | Zero | [V] |
| [rbp+0x30] | 8 | [rbp+0x170] | 0x6666d49 | Ptr | [V] |
| [rbp+0x38] | 8 | [rbp+0x178] | 0x6666d4d | Ptr | [V] |
| [rbp+0x50] | 8 | [rbp+0xE0] | 0x6666e3e | Ptr | [V] |
| [rbp+0x2C0] | 8 | [rbp+0xD0] | 0x6666f60 | Ptr | [V] |
| [rbp+0xD0] | 8 | 0 | 0x6666f67 | Zero | [V] |
| [rbp+0x2C8] | 4 | 1.0 | 0x6666f72 | Float | [V] |
| [rdi+0xEA] | 16 | 0 | 0x6666f7c | Zero | [V] |
| [rbp+0x2DC] | 4 | 1.0 | 0x6666f83 | Float | [V] |
| [rdi+0xFE] | 16 | 0 | 0x6666f8d | Zero | [V] |
| [rbp+0x2F0] | 4 | 1.0 | 0x6666f94 | Float | [V] |
| [rdi+0x112] | 16 | 0 | 0x6666f9e | Zero | [V] |
| [rbp+0x304] | 4 | 1.0 | 0x6666fa5 | Float | [V] |
| [rbp+0x308] | 1 | 0 | 0x6666faf | Byte | [V] |
| [rbp+0x310] | 16 | [rbp+0x3A0] | 0x6666fcf | Matrix | [V] |
| [rbp+0x3B0] | 16 | 0 | 0x6666fd6 | Zero | [V] |
| [rbp+0x320] | 16 | [rbp+0x3B0] | 0x6666fdd | Matrix | [V] |
| [rbp+0x330] | 8 | [rbp+0x3C0] | 0x6666feb | Ptr | [V] |
| [rbp+0x348] | 1 | 0xFF | 0x6666ff2 | Byte | [V] |
| [rbp+0x338] | 8 | [rbp+0x3C8] | 0x666701d | Ptr | [V] |
| [rdi+0x156] | 16 | [rbp+0x3C8] | 0x6667030 | Copy | [V] |
| [rdi+0x156] | 16 | 0 | 0x6667039 | Zero | [V] |
| [rdi+0x17E] | 8 | [rbp+0x3C8+0x28] | 0x6667081 | ImGui field | [V] |
| [rdi+0x16E] | 16 | [rbp+0x3C8+0x18] | 0x666708c | ImGui field | [V] |
| [rbp+0x408..0x4B8] | 16x12 | 0 | 0x66670af..0x66670e7 | Zero ImGui state | [V] |
| [rbp+0x428] | 2 | ax | 0x6667115 | Draw cmd count | [V] |
| [rbp+0x520] | 1 | al | 0x6667132, 0x66671a8, 0x6667232, 0x6667268, 0x6667370, 0x66673ff, 0x6667499, 0x6667517, 0x6667567, 0x666774a, 0x6667a3d, 0x6667ac4, 0x6667b3a, 0x6667c14, 0x6667c54, 0x6667d46, 0x6667dc8, 0x6667e0c, 0x6667ec1, 0x6667f0e, 0x6667f65 | Alloc result byte | [V] |
| [rbp+0x400] | 8 | flags | 0x6667168, 0x6667330, 0x6667460, 0x6667717, 0x6667c1b, 0x6667d91, 0x6667ec8 | ImGui flags | [V] |
| [rbp+0x442] | 2 | ax | 0x666718a | Vertex count | [V] |
| [rbp+0x42A] | 2 | ax | 0x666724a | Draw cmd count | [V] |
| [rbp+0x42C] | 2 | ax | 0x6667352 | Draw cmd count | [V] |
| [rbp+0x444] | 2 | ax | 0x66673e1 | Index count | [V] |
| [rbp+0x43C] | 2 | ax | 0x666747b | Attr count | [V] |
| [rbp+0x41C] | 2 | ax | 0x66674fa | Buffer calc | [V] |
| [rbp+0x480] | 2 | ax | 0x6667e21 | Buffer calc | [V] |
| [rbp+0x410] | 2 | ax | 0x6667aa7 | Index count | [V] |
| [rbp+0x42A] | 2 | ax | 0x6667ef0 | Draw cmd count | [V] |
| [rdx] | 2 | [rbp+0x328] | 0x6667a5a | Index write | [V] |
| [rdx] | 4 | [rbp+0x2D8] | 0x6667b56 | Index write | [V] |
| [rdx] | 2 | [rbp+0x2D0] | 0x6667bde | Vertex attr | [V] |
| [rsi+0x8A8] | 8 | +2 | 0x6667a5d | Advance pointer | [V] |
| [rsi+0x638] | 8 | +4 | 0x6667b58 | Advance pointer | [V] |
| [rsi+0x698] | 8 | +2 | 0x6667be1 | Advance pointer | [V] |
| [rsi+0x758] | 8 | +0x58 | 0x66672f2, 0x6667cde | Advance pointer | [V] |
| [rsi+0x818] | 8 | +1 | 0x6667d5f | Advance pointer | [V] |
| [rsi+0x368] | 8 | +1 | 0x6667de1 | Advance pointer | [V] |
| [rsi+0x770] | 8 | +0x88 | 0x66671f2, 0x6667e85 | Advance pointer | [V] |
| [rsi+8] | 8 | +0xC8 | 0x666776f, 0x6667f33 | Advance | [V] |
| [rbx+0x770] | 8 | +0x88 | 0x66671f2, 0x6667e85 | Advance pointer | [V] |
| [rbx+0x758] | 8 | +0x58 | 0x66672f2, 0x6667cde | Advance pointer | [V] |
| [rbx+0x638] | 8 | +4 | 0x666738e | Advance pointer | [V] |
| [rbx+0x698] | 8 | +2 | 0x666741f | Advance pointer | [V] |
| [rbx+0x818] | 8 | +1 | 0x66674b2 | Advance pointer | [V] |
| [rbx+0x3B0] | 8 | r15+1 | 0x6667533 | Inc counter | [V] |
| [rbx+0x3A8] | 8 | rdi | 0x66676c4 | New buffer | [V] |
| [rbx+0x3B0] | 8 | rdi+r8 | 0x66676d5 | New end | [V] |
| [rbx+0x3B8] | 8 | r13+rdi | 0x66676df | New cap | [V] |
| [rbx+0x08] | 8 | +0xC8 | 0x666776f | Advance | [V] |
| [rdi] | 8 | [rbp+0x240] | 0x66671c5, 0x6667e5c | Draw cmd write | [V] |
| [rdi+0x80] | 8 | [rbp+0x2C0] | 0x66671e0, 0x6667e73 | Draw cmd field | [V] |
| [rdi+0x00] | 8 | [rbp+0x1E0] | 0x6667e5c | Draw cmd write | [V] |
| [rdi+0x10] | 4 | [r8+0x10] | 0x666728c, 0x6667c75 | Vertex field | [V] |
| [rdi+0x00] | 16 | [r8] | 0x6667292, 0x6667c7c | Vertex data | [V] |
| [rdi+0x14] | 1 | [rbp+0x1FC] | 0x666729c, 0x6667c86 | Vertex byte | [V] |
| [rdi+0x18] | 4 | [rbp+0x200] | 0x66672a7, 0x6667c91 | Vertex float | [V] |
| [rdi+0x1C] | 4 | [rbp+0x204] | 0x66672b4, 0x6667c9e | Vertex float | [V] |
| [rdi+0x20] | 4 | [rbp+0x208] | 0x66672c1, 0x6667cab | Vertex float | [V] |
| [rdi+0x24] | 4 | [rbp+0x20C] | 0x66672ce, 0x6667cb8 | Vertex float | [V] |
| [rdi+0x28] | 16 | [rbp+0x1E2+0x2E] | 0x66672e6, 0x6667cd2 | Vertex xmm | [V] |
| [rdi+0x38] | 16 | [rbp+0x1E2+0x3E] | 0x66672ea, 0x6667cd6 | Vertex xmm | [V] |
| [rdi+0x47] | 16 | [rbp+0x1E2+0x4D] | 0x66672ee, 0x6667cda | Vertex xmm | [V] |
| [rdi+0x10] | 4 | [rbp+0x1E8+0x10] | 0x666728c | Vertex field | [V] |
| [rdi+0x00] | 16 | [rbp+0x1E8] | 0x6667292 | Vertex data | [V] |
| [rdi+0x14] | 1 | [rbp+0x1FC] | 0x666729c | Vertex byte | [V] |
| [rdi+0x18] | 4 | [rbp+0x200] | 0x66672a7 | Vertex float | [V] |
| [rdi+0x1C] | 4 | [rbp+0x204] | 0x66672b4 | Vertex float | [V] |
| [rdi+0x20] | 4 | [rbp+0x208] | 0x66672c1 | Vertex float | [V] |
| [rdi+0x24] | 4 | [rbp+0x20C] | 0x66672ce | Vertex float | [V] |
| [rdi+0x28] | 16 | [rbp+0x1E2+0x2E] | 0x66672e6 | Vertex xmm | [V] |
| [rdi+0x38] | 16 | [rbp+0x1E2+0x3E] | 0x66672ea | Vertex xmm | [V] |
| [rdi+0x47] | 16 | [rbp+0x1E2+0x4D] | 0x66672ee | Vertex xmm | [V] |

---

## Verification
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-I5a2.md` after each chunk.

## TOOL REQUESTS
None.