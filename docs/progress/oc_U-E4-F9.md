# U-E4-F9: sub_67762e0 chunk builder — continuation from 0x677cf26 to 0x677e166

Unit: U-E4-F9
Function: sub_67762e0 (chunk builder, called by chunk extractor 0x66ea3d0) — continuation of U-E4-F8
RVAs: continuation from 0x677cf26 (Phase 3), function span [0x67762e0..0x677e166)
Source: `rdis dis` on Minecraft.Windows.exe 1.26.62.01 (version 1.26.62.01), RVAs relative to image base
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
DONE — function end boundary 0x677e166 reached. All phases 3-27 written.

## Phase 27 — [0x677e0d7..0x677e166) 38 instructions (`rdis dis 0x677e0d7 40`, truncated at function boundary 0x677e166)

Exact rdis lines:

```
  677e0d7  and esp,[rdx]                                 ; R a1+0x0
  677e0d9  test ah,ah                                    
  677e0db  pushfq                                        
  677e0dc  ret far                                       
  677e0de  xor r9d,r9d                                   

loc_677e0e1:  ; from 677e11b
  677e0e1  movzx r10d,byte ptr [r14+r9]                  
  677e0e6  xor r10,rdx                                   
  677e0e9  imul r10,rcx                                  
  677e0ed  movzx edx,byte ptr [r14+r9+1]                 
  677e0f3  xor rdx,r10                                   
  677e0f6  imul rdx,rcx                                  
  677e0fa  movzx r10d,byte ptr [r14+r9+2]                
  677e100  xor r10,rdx                                   
  677e103  imul r10,rcx                                  
  677e107  movzx edx,byte ptr [r14+r9+3]                 
  677e10d  xor rdx,r10                                   
  677e110  imul rdx,rcx                                  
  677e114  add r9,4                                      
  677e118  cmp r8,r9                                     
  677e11b  jne short 0x677E0E1                           ; -> loc_677e0e1
  677e11d  test rax,rax                                  
  677e120  je short 0x677E142                            ; -> loc_677e142
  677e122  add r14,r9                                    
  677e125  xor r8d,r8d                                   
  677e128  mov r9,rdx                                    

loc_677e12b:  ; from 677e140
  677e12b  movzx edx,byte ptr [r14+r8]                   
  677e130  xor rdx,r9                                    
  677e133  imul rdx,rcx                                  
  677e137  inc r8                                        
  677e13a  mov r9,rdx                                    
  677e13d  cmp rax,r8                                    
  677e140  jne short 0x677E12B                           ; -> loc_677e12b

loc_677e142:  ; from 677e120
  677e142  mov [0x129FB1F0],rdx                          ; [data_129fb1f0]
  677e149  lea rcx,[rbp+0x570]                           
  677e150  call 0x73150                                  ; -> sub_73150
  677e155  lea rcx,[0x129FB1F8]                          ; [data_129fb1f8]
  677e15c  call 0xE938D70                                ; -> sub_e938d70
  677e161  jmp 0x67763A9                                 ; -> sub_67763a9
```

// Interpretation: FNV-1a hash computation (error handler tail from loc_677e039). The first 4 instructions (`and esp,[rdx]`, `test ah,ah`, `pushfq`, `ret far`) appear to be misaligned/data bytes [?]. Hash loop (4 bytes at a time): `xor r9d,r9d` (idx=0); loc_677e0e1: `movzx r10d,byte [r14+r9]`; `xor r10,rdx`; `imul r10,rcx` (FNV prime multiply [I]); `movzx edx,byte [r14+r9+1]`; `xor rdx,r10`; `imul rdx,rcx`; `movzx r10d,byte [r14+r9+2]`; `xor r10,rdx`; `imul r10,rcx`; `movzx edx,byte [r14+r9+3]`; `xor rdx,r10`; `imul rdx,rcx`; `add r9,4`; `cmp r8,r9`; `jne loc_677e0e1` (loop while idx < len). Remainder: `test rax,rax`; `je loc_677e142` (skip if zero); else `add r14,r9`; `xor r8d,r8d` (idx=0); `mov r9,rdx`; loc_677e12b: `movzx edx,byte [r14+r8]`; `xor rdx,r9`; `imul rdx,rcx`; `inc r8`; `mov r9,rdx`; `cmp rax,r8`; `jne loc_677e12b` (byte-by-byte remainder loop). Final: loc_677e142: `mov [0x129FB1F0],rdx` (store hash result [I]); `lea rcx,[rbp+0x570]`; `call 0x73150` (sub_73150 — hash finalize/commit [I]); `lea rcx,[0x129FB1F8]`; `call 0xE938D70` (sub_e938d70 — cleanup [I]); `jmp 0x67763A9` (sub_67763a9 — function end/error handler [I]). `jmp` ends at 0x677e166 = function boundary. Next instruction `nop [rax+rax]` at 0x677e166 is past boundary (excluded).
// tag: [V] all lines; calls 0x73150 [V], 0xE938D70 [V].

## Phase 26 — [0x677e021..0x677e0d7) 40 instructions (`rdis dis 0x677e021 40`)

Exact rdis lines:

```
  677e021  nop                                           
  677e022  jmp 0x6776522                                 ; -> sub_6776522
  677e027  call 0xB432E0                                 ; -> sub_b432e0
  677e02c  nop                                           
  677e02d  call 0x1166E0                                 ; -> sub_1166e0
  677e032  nop                                           
  677e033  call 0x1166E0                                 ; -> sub_1166e0
  677e038  nop                                           
  677e039  mov qword ptr [rsp+0x20],0                    
  677e042  xor ecx,ecx                                   
  677e044  xor edx,edx                                   
  677e046  xor r8d,r8d                                   
  677e049  xor r9d,r9d                                   
  677e04c  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  677e052  lea rcx,[0x129FB1F8]                          ; [data_129fb1f8]
  677e059  call 0xE938CB0                                ; -> sub_e938cb0
  677e05e  cmp dword ptr [0x129FB1F8],0xFFFFFFFF         ; [data_129fb1f8]
  677e065  jne 0x67763A9                                 ; -> sub_67763a9
  677e06b  lea rdx,[0xF60E1A3]                           ; [data_f60e1a3] "RenderChunkFogAlpha"
  677e072  lea r14,[rbp+0x570]                           
  677e079  mov rcx,r14                                   
  677e07c  call 0x79580                                  ; -> sub_79580
  677e081  nop                                           
  677e082  mov r8,[rbp+0x580]                            
  677e089  cmp qword ptr [rbp+0x588],0x10                
  677e091  jb short 0x677E09A                            ; -> loc_677e09a
  677e093  mov r14,[rbp+0x570]                           

loc_677e09a:  ; from 677e091
  677e09a  test r8,r8                                    
  677e09d  je short 0x677E0C4                            ; -> loc_677e0c4
  677e09f  mov eax,r8d                                   
  677e0a2  and eax,3                                     
  677e0a5  mov rcx,0x100000001B3                         
  677e0af  cmp r8,4                                      
  677e0b3  jae short 0x677E0D0                           ; -> loc_677e0d0
  677e0b5  mov rdx,0xCBF29CE484222325                    
  677e0bf  xor r9d,r9d                                   
  677e0c2  jmp short 0x677E122                           ; -> loc_677e122

loc_677e0c4:  ; from 677e09d
  677e0c4  mov rdx,0xCBF29CE484222325                    
  677e0ce  jmp short 0x677E142                           ; -> loc_677e142

loc_677e0d0:  ; from 677e0b3
  677e0d0  and r8,0xFFFFFFFFFFFFFFFC                     
```

// Interpretation: Trailing code after Phase 25's `ret`: `nop`; `jmp 0x6776522` (sub_6776522 — likely next function [I]); `call 0xB432E0` (sub_b432e0 [I]); `nop`; `call 0x1166E0` (sub_1166e0 [I]); `nop`; `call 0x1166E0` (sub_1166e0 [I]); `nop`. These appear to be padding/thunks between functions [?]. loc_677e039 (error handler, jump target from many phases): `mov qword ptr [rsp+0x20],0`; `xor ecx,ecx`; `xor edx,edx`; `xor r8d,r8d`; `xor r9d,r9d`; `call qword ptr [0xF9A8C78]` (data_f9a8c78 — likely RaiseException/SEH [I]); `lea rcx,[0x129FB1F8]`; `call 0xE938CB0` (sub_e938cb0 [I]); `cmp dword ptr [0x129FB1F8],0xFFFFFFFF`; `jne 0x67763A9` (sub_67763a9 [I]); `lea rdx,[0xF60E1A3]` ("RenderChunkFogAlpha" string [V]); `lea r14,[rbp+0x570]`; `mov rcx,r14`; `call 0x79580` (sub_79580 [I]); `nop`; `mov r8,[rbp+0x580]`; `cmp qword ptr [rbp+0x588],0x10`; `jb loc_677e09a`; else `mov r14,[rbp+0x570]`. loc_677e09a: `test r8,r8`; `je loc_677e0c4`; else `mov eax,r8d`; `and eax,3`; `mov rcx,0x100000001B3`; `cmp r8,4`; `jae loc_677e0d0`; else `mov rdx,0xCBF29CE484222325` (FNV offset basis [I]); `xor r9d,r9d`; `jmp loc_677e122`. loc_677e0c4: `mov rdx,0xCBF29CE484222325`; `jmp loc_677e142`. loc_677e0d0: `and r8,0xFFFFFFFFFFFFFFFC` continues at 0x677e0d7 (excluded). Range ends at `and r8,0xFFFFFFFFFFFFFFFC` (0x677e0d0, 7 bytes → next instruction at 0x677e0d7).
// tag: [V] all lines; calls 0xB432E0 [V], 0x1166E0 [V] x2, [0xF9A8C78] [V], 0xE938CB0 [V], 0x79580 [V].

## Phase 25 — [0x677df6e..0x677e021) 40 instructions (`rdis dis 0x677df6e 40`)

Exact rdis lines:

```
  677df6e  mov rax,[rsi]                                 
  677df71  mov rax,[rax]                                 
  677df74  mov rcx,rsi                                   
  677df77  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677df7d  lock dec dword ptr [rsi+0xC]                  
  677df81  jne short 0x677DF93                           ; -> loc_677df93
  677df83  mov rax,[rsi]                                 
  677df86  mov rax,[rax+8]                               
  677df8a  mov rcx,rsi                                   
  677df8d  call qword ptr [0xF99FFA0]                    ; [data_f99FFA0]
loc_677df93:  ; from 677df81
  677df93  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677df9a  mov rax,[rcx]                                 
  677df9d  mov rax,[rax+0x10]                            
  677dfa1  movzx edx,byte ptr [rbp+0x837]                
  677dfa8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dfae  nop                                           
  677dfaf  movaps xmm6,[rbp+0x850]                       
  677dfb6  movaps xmm7,[rbp+0x860]                       
  677dfbd  movaps xmm8,[rbp+0x870]                       
  677dfc5  movaps xmm9,[rbp+0x880]                       
  677dfcd  movaps xmm10,[rbp+0x890]                      
  677dfd5  movaps xmm11,[rbp+0x8A0]                      
  677dfdd  movaps xmm12,[rbp+0x8B0]                      
  677dfe5  movaps xmm13,[rbp+0x8C0]                      
  677dfed  movaps xmm14,[rbp+0x8D0]                      
  677dff5  movaps xmm15,[rbp+0x8E0]                      
  677dffd  add rsp,0x978                                 
  677e004  pop rbx                                       
  677e005  pop rdi                                       
  677e006  pop rsi                                       
  677e007  pop r12                                       
  677e009  pop r13                                       
  677e00b  pop r14                                       
  677e00d  pop r15                                       
  677e00f  pop rbp                                       
  677e010  ret                                           
  677e011  call 0x78ED0                                  ; -> sub_78ed0
  677e016  nop                                           
  677e017  mov ecx,0x30                                  
  677e01c  call 0x9BC830                                 ; -> sub_9bc830
```

// Interpretation: Tail of Phase 24's release: `mov rax,[rsi]`; `mov rax,[rax]` (vtable dtor [I]); `mov rcx,rsi`; `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `lock dec dword ptr [rsi+0xC]` (refcount-- [I]); `jne loc_677df93`; else `mov rax,[rsi]`; `mov rax,[rax+8]` (vtable dtor [I]); `mov rcx,rsi`; `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]). loc_677df93: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x837]`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`. Register restore: `movaps xmm6..xmm15,[rbp+0x850..0x8E0]` (restore callee-saved XMM regs [I]); `add rsp,0x978` (stack dealloc [I]); `pop rbx`,`rdi`,`rsi`,`r12`,`r13`,`r14`,`r15`,`rbp`; `ret` (function epilogue end [V]). Trailing code after ret: `call 0x78ED0` (sub_78ed0 — likely next function or alignment [?]); `nop`; `mov ecx,0x30`; `call 0x9BC830` (sub_9bc830 — likely next function or alignment [?]). Function effectively ends at `ret` (0x677e010).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x4, 0x78ED0 [V], 0x9BC830 [V].

## Phase 24 — [0x677dece..0x677df6e) 40 instructions (`rdis dis 0x677dece 40`)

Exact rdis lines:

```
  677dece  dec dword ptr [r14+0xC]                       
  677ded2  jne short 0x677DEF0                           ; -> loc_677def0
  677ded4  mov rax,[r14]                                 
  677ded7  mov rax,[rax+8]                               
  677dedb  mov rcx,r14                                   
  677dede  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dee4  nop [rax+rax]                                 

loc_677def0:  ; from 677ded2
  677def0  mov r15,[rbp+0x50]                            
  677def4  test r15,r15                                  
  677def7  je 0x67766C0                                  ; -> sub_67766c0
  677defd  mov r13,[rbp+0x58]                            
  677df01  jmp short 0x677DF14                           ; -> loc_677df14
  677df03  nop [rax+rax]                                 

loc_677df10:  ; from 677df22, 677df2b, 677df32, 677df48, 677df5a
  677df10  add r15,0x28                                  

loc_677df14:  ; from 677df01
  677df14  cmp r15,r13                                   
  677df17  je 0x67766C0                                  ; -> sub_67766c0
  677df1d  cmp byte ptr [r15+0x18],2                     
  677df22  jne short 0x677DF10                           ; -> loc_677df10
  677df24  mov r14,[r15+8]                               
  677df28  test r14,r14                                  
  677df2b  je short 0x677DF10                            ; -> loc_677df10
  677df2d  lock dec dword ptr [r14+8]                    
  677df32  jne short 0x677DF10                           ; -> loc_677df10
  677df34  mov rax,[r14]                                 
  677df37  mov rax,[rax]                                 
  677df3a  mov rcx,r14                                   
  677df3d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677df43  lock dec dword ptr [r14+0xC]                  
  677df48  jne short 0x677DF10                           ; -> loc_677df10
  677df4a  mov rax,[r14]                                 
  677df4d  mov rax,[rax+8]                               
  677df51  mov rcx,r14                                   
  677df54  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677df5a  jmp short 0x677DF10                           ; -> loc_677df10
  677df5c  mov rsi,[rbp+0x2F8]                           
  677df63  test rsi,rsi                                  
  677df66  je short 0x677DF93                            ; -> loc_677df93
  677df68  lock dec dword ptr [rsi+8]                    
  677df6c  jne short 0x677DF93                           ; -> loc_677df93
  677df6e  mov rax,[rsi]                                 
```

// Interpretation: Tail of Phase 23's release: `dec dword ptr [r14+0xC]` (refcount-- [I]); `jne loc_677def0`; else `mov rax,[r14]`; `mov rax,[rax+8]` (vtable dtor [I]); `mov rcx,r14`; `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `nop [rax+rax]` [?]. loc_677def0 (final cleanup): `mov r15,[rbp+0x50]`; `test r15,r15`; `je sub_67766c0` (skip to function end); else `mov r13,[rbp+0x58]`; `jmp loc_677df14`. Padding `nop [rax+rax]` at 0x677df03 [?]. Release loop loc_677df14: `cmp r15,r13`; `je sub_67766c0`; `cmp byte ptr [r15+0x18],2`; `jne loc_677df10` (next); else `mov r14,[r15+8]`; `test r14,r14`; `je loc_677df10`; else `lock dec dword ptr [r14+8]`; `jne loc_677df10`; else `mov rax,[r14]`; `mov rax,[rax]` (vtable dtor [I]); `mov rcx,r14`; `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `lock dec dword ptr [r14+0xC]`; `jne loc_677df10`; else `mov rax,[r14]`; `mov rax,[rax+8]` (vtable dtor [I]); `mov rcx,r14`; `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `jmp loc_677df10`. Loop tail loc_677df10: `add r15,0x28`. After loop: `mov rsi,[rbp+0x2F8]`; `test rsi,rsi`; `je loc_677df93`; else `lock dec dword ptr [rsi+8]`; `jne loc_677df93`; else `mov rax,[rsi]` continues at 0x677df6e (excluded). Range ends at `mov rax,[rsi]` (0x677df6e, 3 bytes → next instruction at 0x677df6e).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x3, 0x67766C0 [V] x2 (function end), 0x5ABA6D0 [V] referenced in grow target from prev phase.

## Phase 23 — [0x677de2e..0x677dece) 40 instructions (`rdis dis 0x677de2e 40`)

Exact rdis lines:

```
  677de2e  mov dl,0x4A                                   
  677de30  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677de36  nop                                           
  677de37  mov [rbp+0x838],al                            
  677de3d  mov rdx,[r14+8]                               
  677de41  cmp rdx,[r14+0x10]                            
  677de45  je short 0x677DE62                            ; -> loc_677de62
  677de47  mov r8d,0xC8                                  
  677de4d  mov rcx,rdx                                   
  677de50  mov rdx,r12                                   
  677de53  call 0xEEC6EC0                                ; -> sub_eec6ec0
  677de58  add qword ptr [r14+8],0xC8                    
  677de60  jmp short 0x677DE6E                           ; -> loc_677de6e

loc_677de62:  ; from 677de45
  677de62  mov rcx,r14                                   
  677de65  mov r8,r12                                    
  677de68  call 0x5ABA6D0                                ; -> sub_5aba6d0
  677de6d  nop                                           

loc_677de6e:  ; from 677de60
  677de6e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677de75  mov rax,[rcx]                                 
  677de78  mov rax,[rax+0x10]                            
  677de7c  movzx edx,byte ptr [rbp+0x838]                
  677de83  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677de89  nop                                           
  677de8a  lea rcx,[rbp+0x110]                           
  677de91  call 0x67E1840                                ; -> sub_67e1840
  677de96  mov rcx,r13                                   
  677de99  nop [rax]                                     ; R ret@67e1840+0x0
  677dea0  call 0x67E23F0                                ; -> sub_67e23f0
  677dea5  cmp byte ptr [rbp+0x80],3                     
  677deac  jne short 0x677DEF0                           ; -> loc_677def0
  677deae  mov r14,[rbp+0x78]                            
  677deb2  test r14,r14                                  
  677deb5  je short 0x677DEF0                           ; -> loc_677def0
  677deb7  lock dec dword ptr [r14+8]                    
  677debc  jne short 0x677DEF0                           ; -> loc_677DEF0
  677debe  mov rax,[r14]                                 
  677dec1  mov rax,[rax]                                 
  677dec4  mov rcx,r14                                   
  677dec7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677decd  lock dec dword ptr [r14+0xC]                  
```

// Interpretation: TLS-flag chain continuation from Phase 22: `mov dl,0x4A`; `call [0xF99FFA0]` (sub_eea6040 [V]); `nop`; `mov [rbp+0x838],al`. List append: `mov rdx,[r14+8]` (cursor [I]); `cmp [r14+0x10]` (end [I]); `je loc_677de62` (grow); else fast path: `mov r8d,0xC8` (size 200 [I]); `mov rcx,rdx`; `mov rdx,r12`; `call 0xEEC6EC0` (sub_eec6ec0 — memcpy/copy helper [I]); `add qword ptr [r14+8],0xC8` (cursor += 0xC8 [I]); `jmp loc_677de6e`. Grow target loc_677de62: `mov rcx,r14`; `mov r8,r12`; `call 0x5ABA6D0` (sub_5aba6d0 — grow/copy helper [I]); `nop`. loc_677de6e: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]`→`nop`; `lea rcx,[rbp+0x110]`; `call 0x67E1840` (sub_67e1840 — finalizer/commit helper [I]); `mov rcx,r13`; `nop [rax]` [?]; `call 0x67E23F0` (sub_67e23f0 — cleanup/helper [I]); flag check `cmp byte ptr [rbp+0x80],3`; `jne short loc_677def0`; `mov r14,[rbp+0x78]`; `test r14,r14`; `je loc_677def0` (skip if null); else `lock dec dword ptr [r14+8]` (refcount-- [I]); `jne loc_677def0`; else `mov rax,[r14]`; `mov rax,[rax]` (vtable dtor [I]); `mov rcx,r14`; `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `lock dec dword ptr [r14+0xC]` continues at 0x677dece (excluded). Range ends at `lock dec dword ptr [r14+0xC]` (0x677decd, 4 bytes → next instruction at 0x677dece).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x3, 0xEEC6EC0 [V], 0x5ABA6D0 [V], 0x67E1840 [V], 0x67E23F0 [V].

## Phase 22 — [0x677dd6a..0x677de2e) 40 instructions (`rdis dis 0x677dd6a 40`)

Exact rdis lines:

```
  677dd6a  mov rax,[rax+0x10]                            
  677dd6e  movzx edx,byte ptr [rbp+0x838]                
  677dd75  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dd7b  nop                                           
  677dd7c  mov eax,[r14+0x2D0]                           
  677dd83  not eax                                       
  677dd85  add eax,[r14+0x2D8]                           
  677dd8c  mov [rbp+0x5FC],ax                            
  677dd93  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677dd9a  mov rax,[rcx]                                 
  677dd9d  mov rax,[rax+0x10]                            
  677dda1  mov dl,0x4A                                   
  677dda3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dda9  nop                                           
  677ddaa  mov [rbp+0x838],al                            
  677ddb0  mov rdx,[r14+0x6B0]                           
  677ddb7  cmp rdx,[r14+0x6B8]                           
  677ddbe  je short 0x677DDCC                            ; -> loc_677ddcc
  677ddc0  inc rdx                                       
  677ddc3  mov [r14+0x6B0],rdx                           
  677ddca  jmp short 0x677DDDC                           ; -> loc_677dddc

loc_677ddcc:  ; from 677ddbe
  677ddcc  mov rcx,r14                                   
  677ddcf  add rcx,0x6A8                                 
  677ddd6  call 0x6760E60                                ; -> sub_6760e60
  677dddb  nop                                           

loc_677dddc:  ; from 677ddca
  677dddc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677dde3  mov rax,[rcx]                                 
  677dde6  mov rax,[rax+0x10]                            
  677ddea  movzx edx,byte ptr [rbp+0x838]                
  677ddf1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677ddf7  nop                                           
  677ddf8  mov rax,0x4000000002207803                    
  677de02  mov [rbp+0x570],rax                           
  677de09  mov eax,[r14+0x6A8]                           
  677de10  not eax                                       
  677de12  add eax,[r14+0x6B0]                           
  677de19  mov [rbp+0x5AA],ax                            
  677de20  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677de27  mov rax,[rcx]                                 
  677de2a  mov rax,[rax+0x10]                            
```

// Interpretation: TLS-flag chain continuation from Phase 21: `mov rax,[rax+0x10]`; `movzx edx,byte [rbp+0x838]`; `call [0xF99FFA0]` (sub_eea6040 [V]); `nop`. Checksum: `mov eax,[r14+0x2D0]`; `not eax`; `add eax,[r14+0x2D8]`; `mov [rbp+0x5FC],ax` (checksum [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`→`mov [rbp+0x838],al`. Counter increment: `mov rdx,[r14+0x6B0]`; `cmp [r14+0x6B8]`; `je loc_677ddcc` (grow); else `inc rdx`; `mov [r14+0x6B0],rdx`; `jmp loc_677dddc`. Grow target loc_677ddcc: `mov rcx,r14`; `add rcx,0x6A8`; `call 0x6760E60` (sub_6760e60 — grow helper [I]); `nop`. loc_677dddc: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]`→`nop`; `mov rax,0x4000000002207803`; `mov [rbp+0x570],rax` (u64 tag at +0x570 [I]); `mov eax,[r14+0x6A8]`; `not eax`; `add eax,[r14+0x6B0]`; `mov [rbp+0x5AA],ax` (checksum [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]` continues at 0x677de2e (excluded). Range ends at `mov rax,[rax+0x10]` (0x677de2a, 4 bytes → next instruction at 0x677de2e).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x3, 0x6760E60 [V].

## Phase 21 — [0x677dcab..0x677dd6a) 40 instructions (`rdis dis 0x677dcab 40`)

Exact rdis lines:

```
  677dcab  add [rax],al                                  
  677dcad  add [rax],al                                  
  677dcaf  add qword ptr [r14+0x770],0x88                
  677dcba  jmp short 0x677DCD3                           ; -> loc_677dcd3
  677dcbc  lea rcx,[r14+0x768]                           
  677dcc3  mov rdx,r15                                   
  677dcc6  lea r8,[rbp+0x118]                            
  677dccd  call 0x6760710                                ; -> sub_6760710
  677dcd2  nop                                           

loc_677dcd3:  ; from 677dcba
  677dcd3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677dcda  mov rax,[rcx]                                 
  677dcdd  mov rax,[rax+0x10]                            
  677dce1  movzx edx,byte ptr [rbp+0x838]                
  677dce8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dcee  nop                                           
  677dcef  mov qword ptr [rbp+0x570],0x2007803           
  677dcfa  mov eax,[r14+0x770]                           
  677dd01  sub eax,[r14+0x768]                           
  677dd08  shr eax,3                                     
  677dd0b  imul eax,0xFFFFF0F1                           
  677dd11  dec eax                                       
  677dd13  mov [rbp+0x59A],ax                            
  677dd1a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677dd21  mov rax,[rcx]                                 
  677dd24  mov rax,[rax+0x10]                            
  677dd28  mov dl,0x4A                                   
  677dd2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dd30  nop                                           
  677dd31  mov [rbp+0x838],al                            
  677dd37  mov rdx,[r14+0x2D8]                           
  677dd3e  cmp rdx,[r14+0x2E0]                           
  677dd45  je short 0x677DD53                            ; -> loc_677dd53
  677dd47  inc rdx                                       
  677dd4a  mov [r14+0x2D8],rdx                           
  677dd51  jmp short 0x677DD60                           ; -> loc_677dd60

loc_677dd53:  ; from 677dd45
  677dd53  lea rcx,[r14+0x2D0]                           
  677dd5a  call 0x6760E60                                ; -> sub_6760e60
  677dd5f  nop                                           

loc_677dd60:  ; from 677dd51
  677dd60  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677dd67  mov rax,[rcx]                                 
```

// Interpretation: Fall-through from Phase 20's fast path: `add [rax],al`; `add [rax],al` (2× byte add to [rax] [I]/?); `add qword ptr [r14+0x770],0x88` (cursor += 0x88 [I]); `jmp short loc_677dcd3`. Grow target loc_677dcbc (from Phase 20's je): `lea rcx,[r14+0x768]`; `mov rdx,r15`; `lea r8,[rbp+0x118]`; `call 0x6760710` (sub_6760710 — grow helper [I]); `nop`. loc_677dcd3: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`; `mov qword ptr [rbp+0x570],0x2007803` (tag/flags [I]); cursor delta `mov eax,[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3` (/8 [I]); `imul eax,0xFFFFF0F1` (magic multiply [I]); `dec eax`; `mov [rbp+0x59A],ax` (count [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`→`mov [rbp+0x838],al`. Counter increment: `mov rdx,[r14+0x2D8]`; `cmp [r14+0x2E0]`; `je loc_677dd53` (grow); else `inc rdx`; `mov [r14+0x2D8],rdx`; `jmp loc_677dd60`. Grow target loc_677dd53: `lea rcx,[r14+0x2D0]`; `call 0x6760E60` (sub_6760e60 — grow helper [I]); `nop`. loc_677dd60: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]` continues at 0x677dd6a (excluded). Range ends at `mov rax,[rcx]` (0x677dd67, 3 bytes → next instruction at 0x677dd6a).
// tag: [V] all lines; calls 0x6760710 [V], [0xF99FFA0]=sub_eea6040 [V] x2, 0x6760E60 [V].

## Phase 20 — [0x677dbdf..0x677dcab) 40 instructions (`rdis dis 0x677dbdf 40`)

Exact rdis lines:

```
  677dbdf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677dbe6  mov rax,[rcx]                                 
  677dbe9  mov rax,[rax+0x10]                            
  677dbed  movzx edx,byte ptr [rbp+0x838]                
  677dbf4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dbfa  nop                                           
  677dbfb  mov eax,[r14+0x650]                           
  677dc02  sub eax,[r14+0x648]                           
  677dc09  shr eax,3                                     
  677dc0c  imul eax,0xFFFF8E39                           
  677dc12  dec eax                                       
  677dc14  mov [rbp+0x5B2],ax                            
  677dc1b  lea rcx,[r14+0x780]                           
  677dc22  lea rdx,[rbp+0x1A0]                           
  677dc29  call 0x675F3B0                                ; -> sub_675f3b0
  677dc2e  nop                                           
  677dc2f  mov eax,[r14+0x788]                           
  677dc36  sub eax,[r14+0x780]                           
  677dc3d  shr eax,3                                     
  677dc40  imul eax,0xFFFF8BA3                           
  677dc46  dec eax                                       
  677dc48  mov [rbp+0x598],ax                            
  677dc4f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677dc56  mov rax,[rcx]                                 
  677dc59  mov rax,[rax+0x10]                            
  677dc5d  mov dl,0x4A                                   
  677dc5f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dc65  mov [rbp+0x838],al                            
  677dc6b  mov r15,[r14+0x770]                           
  677dc72  cmp r15,[r14+0x778]                           
  677dc79  je short 0x677DCBC                            ; -> loc_677dcbc
  677dc7b  mov rax,[rbp+0x118]                           
  677dc82  mov [r15],rax                                 
  677dc85  lea rcx,[r15+8]                               
  677dc89  lea rdx,[rbp+0x120]                           
  677dc90  call 0xE869FF0                                ; -> sub_e869ff0
  677dc95  nop                                           
  677dc96  mov rax,[rbp+0x198]                           
  677dc9d  mov [r15+0x80],rax                            
  677dca4  mov qword ptr [rbp+0x198],0                   
```

// Interpretation: TLS-flag chain continuation from Phase 19: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`. Cursor delta: `mov eax,[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3` (/8 [I]); `imul eax,0xFFFF8E39` (magic multiply [I]); `dec eax`; `mov [rbp+0x5B2],ax` (count [I]). Sub-call: `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x1A0]`; `call 0x675F3B0` (sub_675f3b0 — copy helper [I]); `nop`. Cursor delta: `mov eax,[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x598],ax` (count [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`→`mov [rbp+0x838],al`. List append: `mov r15,[r14+0x770]` (cursor [I]); `cmp [r14+0x778]` (end [I]); `je loc_677dcbc` (grow); else fast path: `mov rax,[rbp+0x118]`; `mov [r15],rax` (ptr store [I]); `lea rcx,[r15+8]`; `lea rdx,[rbp+0x120]`; `call 0xE869FF0` (sub_e869ff0 — copy helper [I]); `nop`; `mov rax,[rbp+0x198]`; `mov [r15+0x80],rax` (ptr store [I]); `mov qword ptr [rbp+0x198],0` (clear [I]). Range ends at `mov qword ptr [rbp+0x198],0` (0x677dca4, ~7 bytes → next instruction at 0x677dcab).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x2, 0x675F3B0 [V], 0xE869FF0 [V].

## Phase 19 — [0x677db1b..0x677dbdf) 40 instructions (`rdis dis 0x677db1b 40`)

Exact rdis lines:

```
  677db1b  not eax                                       
  677db1d  add eax,[r14+0x890]                           
  677db24  mov [rbp+0x582],ax                            
  677db2b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677db32  mov rax,[rcx]                                 
  677db35  mov rax,[rax+0x10]                            
  677db39  mov dl,0x4A                                   
  677db3b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677db41  nop                                           
  677db42  mov [rbp+0x838],al                            
  677db48  mov rdx,[r14+0x7A0]                           
  677db4f  cmp rdx,[r14+0x7A8]                           
  677db56  je short 0x677DB64                            ; -> loc_677db64
  677db58  inc rdx                                       
  677db5b  mov [r14+0x7A0],rdx                           
  677db62  jmp short 0x677DB71                           ; -> loc_677db71

loc_677db64:  ; from 677db56
  677db64  lea rcx,[r14+0x798]                           
  677db6b  call 0x6760E60                                ; -> sub_6760e60
  677db70  nop                                           

loc_677db71:  ; from 677db62
  677db71  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677db78  mov rax,[rcx]                                 
  677db7b  mov rax,[rax+0x10]                            
  677db7f  movzx edx,byte ptr [rbp+0x838]                
  677db86  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677db8c  nop                                           
  677db8d  mov qword ptr [rbp+0x570],0x4803              
  677db98  mov eax,[r14+0x798]                           
  677db9f  not eax                                       
  677dba1  add eax,[r14+0x7A0]                           
  677dba8  mov [rbp+0x596],ax                            
  677dbaf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677dbb6  mov rax,[rcx]                                 
  677dbb9  mov rax,[rax+0x10]                            
  677dbbd  mov dl,0x4A                                   
  677dbbf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dbc5  mov [rbp+0x838],al                            
  677dbcb  lea rcx,[r14+0x648]                           
  677dbd2  lea rdx,[rbp+0x1F8]                           
  677dbd9  call 0x675FB30                                ; -> sub_675fb30
  677dbde  nop                                           
```

// Interpretation: Tail of Phase 18: `not eax`; `add eax,[r14+0x890]`; `mov [rbp+0x582],ax` (checksum [I]). TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`→`mov [rbp+0x838],al`. Counter increment: `mov rdx,[r14+0x7A0]`; `cmp [r14+0x7A8]`; `je loc_677db64` (grow); else `inc rdx`; `mov [r14+0x7A0],rdx`; `jmp loc_677db71`. Grow target loc_677db64: `lea rcx,[r14+0x798]`; `call 0x6760E60` (sub_6760e60 — grow helper [I]); `nop`. loc_677db71: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]`→`nop`; `mov qword ptr [rbp+0x570],0x4803` (tag/flags [I]); `mov eax,[r14+0x798]`; `not eax`; `add eax,[r14+0x7A0]`; `mov [rbp+0x596],ax` (checksum [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`→`mov [rbp+0x838],al`. Sub-call setup: `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x1F8]`; `call 0x675FB30` (sub_675fb30 — copy helper [I]); `nop`. Range ends at `nop` (0x677dbde, 1 byte → next instruction at 0x677dbdf).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x3, 0x6760E60 [V], 0x675FB30 [V].

## Phase 18 — [0x677da57..0x677db1b) 40 instructions (`rdis dis 0x677da57 40`)

Exact rdis lines:

```
  677da57 lea rcx,[r14+0x750]                           
  677da5e lea r8,[rbp+0x250]                            
  677da65 call 0x6760A80                                ; -> sub_6760a80
  677da6a nop                                           
  677da6b mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677da72 mov rax,[rcx]                                 
  677da75 mov rax,[rax+0x10]                            
  677da79 movzx edx,byte ptr [rbp+0x838]                
  677da80 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677da86 nop                                           
  677da87 mov qword ptr [rbp+0x570],0x4001              
  677da92 mov eax,[r14+0x758]                           
  677da99 sub eax,[r14+0x750]                           
  677daa0 shr eax,3                                     
  677daa3 imul eax,0xFFFF8BA3                           
  677daa9 dec eax                                       
  677daab mov [rbp+0x59C],ax                            
  677dab2 mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  677dab9 mov rax,[rcx]                                 
  677dabc mov rax,[rax+0x10]                            
  677dac0 mov dl,0x4A                                   
  677dac2 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677dac8 nop                                           
  677dac9 mov [rbp+0x838],al                            
  677dacf mov rdx,[r14+0x890]                           
  677dad6 cmp rdx,[r14+0x898]                           
  677dadd je short 0x677DAEB                            ; -> loc_677daeb
  677dadf inc rdx                                       
  677dae2 mov [r14+0x890],rdx                           
  677dae9 jmp short 0x677DAF8                           ; -> loc_677daf8

loc_677daeb:  ; from 677dadd
  677daeb lea rcx,[r14+0x888]                           
  677daf2 call 0x6760E60                                ; -> sub_6760e60
  677daf7 nop                                           

loc_677daf8:  ; from 677dae9
  677daf8 mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  677daff mov rax,[rcx]                                 
  677db02 mov rax,[rax+0x10]                            
  677db06 movzx edx,byte ptr [rbp+0x838]                
  677db0d call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677db13 nop                                           
  677db14 mov eax,[r14+0x888]                           
```

// Interpretation: Grow target from Phase 17's `je`: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x250]`; `call 0x6760A80` (sub_6760a80 — grow helper [I]); `nop`. loc_677da6b (jmp target from Phase 17): TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`; `mov qword ptr [rbp+0x570],0x4001` (tag/flags [I]); cursor delta `mov eax,[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3` (/8 [I]); `imul eax,0xFFFF8BA3` (magic multiply [I]); `dec eax`; `mov [rbp+0x59C],ax` (count [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`→`mov [rbp+0x838],al`. Counter increment: `mov rdx,[r14+0x890]`; `cmp [r14+0x898]`; `je loc_677daeb` (grow); else `inc rdx`; `mov [r14+0x890],rdx`; `jmp loc_677daf8`. Grow target loc_677daeb: `lea rcx,[r14+0x888]`; `call 0x6760E60` (sub_6760e60 — grow helper [I]); `nop`. loc_677daf8: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]`→`nop`; `mov eax,[r14+0x888]` continues at 0x677db1b (excluded). Range ends at `mov eax,[r14+0x888]` (0x677db14, 7 bytes → next instruction at 0x677db1b).
// tag: [V] all lines; calls 0x6760A80 [V], [0xF99FFA0]=sub_eea6040 [V] x3, 0x6760E60 [V].

## Phase 17 — [0x677d98e..0x677da57) 40 instructions (`rdis dis 0x677d98e 40`)

Exact rdis lines:

```
  677d98e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d994  nop                                           
  677d995  mov eax,[r14+0x8A8]                           
  677d99c  sub eax,[r14+0x8A0]                           
  677d9a3  shr eax,1                                     
  677d9a5  dec eax                                       
  677d9a7  mov [rbp+0x580],ax                            
  677d9ae  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d9b5  mov rax,[rcx]                                 
  677d9b8  mov rax,[rax+0x10]                            
  677d9bc  mov dl,0x4A                                   
  677d9be  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d9c4  nop                                           
  677d9c5  mov [rbp+0x838],al                            
  677d9cb  mov rdx,[r14+0x758]                           
  677d9d2  cmp rdx,[r14+0x760]                           
  677d9d9  je short 0x677DA57                            ; -> loc_677da57
  677d9db  lea rcx,[rbp+0x250]                           
  677d9e2  mov eax,[rcx+0x10]                            
  677d9e5  mov [rdx+0x10],eax                            
  677d9e8  movups xmm0,[rcx]                             
  677d9eb  movups [rdx],xmm0                             
  677d9ee  movzx eax,byte ptr [rbp+0x264]                
  677d9f5  mov [rdx+0x14],al                             
  677d9f8  movss xmm0,[rbp+0x268]                        
  677da00  movss [rdx+0x18],xmm0                         
  677da05  movss xmm0,[rbp+0x26C]                        
  677da0d  movss [rdx+0x1C],xmm0                         
  677da12  movss xmm0,[rbp+0x270]                        
  677da1a  movss [rdx+0x20],xmm0                         
  677da1f  movss xmm0,[rbp+0x274]                        
  677da27  movss [rdx+0x24],xmm0                         
  677da2c  movups xmm0,[rbx+0x88]                        
  677da33  movups xmm1,[rbx+0x98]                        
  677da3a  movups xmm2,[rbx+0xA7]                        
  677da41  movups [rdx+0x28],xmm0                        
  677da45  movups [rdx+0x38],xmm1                        
  677da49  movups [rdx+0x47],xmm2                        
  677da4d  add qword ptr [r14+0x758],0x58                
  677da55  jmp short 0x677DA6B                           ; -> loc_677da6b
```

// Interpretation: TLS-flag chain continuation from Phase 16: `call [0xF99FFA0]` (sub_eea6040 [V]); `nop`. Cursor delta: `mov eax,[r14+0x8A8]`; `sub eax,[r14+0x8A0]`; `shr eax,1` (/2 [I]); `dec eax`; `mov [rbp+0x580],ax` (count [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`→`mov [rbp+0x838],al`. Record append: `mov rdx,[r14+0x758]` (cursor [I]); `cmp [r14+0x760]` (end [I]); `je loc_677da57` (grow); else fast path: `lea rcx,[rbp+0x250]`; `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0` (16-byte copy [I]); `movzx eax,byte ptr [rbp+0x264]`; `mov [rdx+0x14],al`; `movss xmm0,[rbp+0x268]`; `movss [rdx+0x18],xmm0`; `movss xmm0,[rbp+0x26C]`; `movss [rdx+0x1C],xmm0`; `movss xmm0,[rbp+0x270]`; `movss [rdx+0x20],xmm0`; `movss xmm0,[rbp+0x274]`; `movss [rdx+0x24],xmm0` (float fields [I]); `movups xmm0,[rbx+0x88]`; `movups xmm1,[rbx+0x98]`; `movups xmm2,[rbx+0xA7]`; `movups [rdx+0x28],xmm0`; `movups [rdx+0x38],xmm1`; `movups [rdx+0x47],xmm2`; `add qword ptr [r14+0x758],0x58` (cursor += 0x58 [I]); `jmp short loc_677da6b` (unconditional jump [V]). Grow target loc_677da57: referenced by `je` but not reached in this phase (unreachable after jmp). Range ends at `jmp short 0x677DA6B` (0x677da55, 2 bytes → next instruction at 0x677da57).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x2.

## Phase 16 — [0x677d89c..0x677d98e) 40 instructions (`rdis dis 0x677d89c 40`)

Exact rdis lines:

```
  677d89c  cmp [rbp+0x838],rax                           
  677d8a3  jne 0x677DE8A                                 ; -> loc_677de8a
  677d8a9  mov rax,[rbp+0x828]                           
  677d8b0  mov rcx,[rax+0x10]                            
  677d8b4  mov eax,0x9D0                                 
  677d8b9 add rcx,rax                                   
  677d8bc call 0x5ABA5C0                                ; -> sub_5aba5c0
  677d8c1 nop                                           
  677d8c2 mov r14,rax                                   
  677d8c5 movaps [rbp+0x620],xmm6                       
  677d8cc movaps [rbp+0x610],xmm6                       
  677d8d3 movaps [rbp+0x600],xmm6                       
  677d8da movaps [rbp+0x5F0],xmm6                       
  677d8e1 movaps [rbp+0x5E0],xmm6                       
  677d8e8 movaps [rbp+0x5D0],xmm6                       
  677d8ef movaps [rbp+0x5C0],xmm6                       
  677d8f6 movaps [rbp+0x5B0],xmm6                       
  677d8fd movaps [rbp+0x5A0],xmm6                       
  677d904 movaps [rbp+0x590],xmm6                       
  677d90b movaps [rbp+0x580],xmm6                       
  677d912 movaps [rbp+0x570],xmm6                       
  677d919 mov qword ptr [rbp+0x630],0                   
  677d924 mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d92b mov rax,[rcx]                                 
  677d92e mov rax,[rax+0x10]                            
  677d932 mov dl,0x4A                                   
  677d934 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d93a nop                                           
  677d93b mov [rbp+0x838],al                            
  677d941 mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
  677d948 cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
  677d94f je short 0x677D965                            ; -> loc_677d965

loc_677d965:  ; from 677d94f
  677d965 lea rcx,[r14+0x8A0]                           
  677d96c lea r8,[rbp+0x2A8]                            
  677d973 call 0x1EF6F90                                ; -> sub_1ef6f90
  677d978 nop                                           

loc_677d979:  ; from 677d978
  677d979 mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d980 mov rax,[rcx]                                 
  677d983 mov rax,[rax+0x10]                            
  677d987 movzx edx,byte ptr [rbp+0x838]                
```

// Interpretation: Guard: `cmp [rbp+0x838],rax`; `jne loc_677de8a` (skip if TLS flag mismatch [I]). Alloc block: `mov rax,[rbp+0x828]`; `mov rcx,[rax+0x10]`; `mov eax,0x9D0`; `add rcx,rax` (dest = [rbp+0x828]+0x10 + 0x9D0 [I]); `call 0x5ABA5C0` (sub_5aba5c0 — alloc/serialize helper [I]); `nop`; `mov r14,rax` (r14 = new block). Zero-out: 13× `movaps [rbp+0x620..0x570],xmm6` (zero 13 stack slots, 0x570..0x62F [I]); `mov qword ptr [rbp+0x630],0`. TLS-flag chain: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`→`mov [rbp+0x838],al`. Slot full check: `mov rdx,[r14+0x8A8]`; `cmp [r14+0x8B0]`; `je loc_677d965` (grow if full). Grow target loc_677d965: `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x2A8]`; `call 0x1EF6F90` (sub_1ef6f90 — grow helper [I]); `nop`. loc_677d979 (fall-through from grow): TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]` continues at 0x677d98e (excluded). Range ends at `movzx edx,byte ptr [rbp+0x838]` (0x677d987, 7 bytes → next instruction at 0x677d98e).
// tag: [V] all lines; calls 0x5ABA5C0 [V], [0xF99FFA0]=sub_eea6040 [V] x2, 0x1EF6F90 [V].

## Phase 15 — [0x677d7fe..0x677d89c) 40 instructions (`rdis dis 0x677d7fe 40`)

Exact rdis lines:

```
  677d7fe  mov rax,[rcx]                                 ; R a0+0x0
  677d801  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  677d805  mov rdx,r14                                   
  677d808  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d80e  nop                                           
  677d80f  mov r14,[rbp+0x800]                           
  677d816  test r14,r14                                  
  677d819  je short 0x677D895                            ; -> loc_677d895
  677d81b  mov r15,[rbp+0x808]                           
  677d822  cmp r14,r15                                   
  677d825  jne short 0x677D839                           ; -> loc_677d839
  677d827  jmp short 0x677D85E                           ; -> loc_677d85e
  677d829  nop [rax]                                     

loc_677d830:  ; from 677d840, 677d846, 677d855
  677d830  add r14,0x20                                  
  677d834  cmp r14,r15                                   
  677d837  je short 0x677D857                            ; -> loc_677d857

loc_677d839:  ; from 677d825
  677d839  mov rcx,[r14+8]                               
  677d83d  test rcx,rcx                                  
  677d840  je short 0x677D830                            ; -> loc_677d830
  677d842  lock dec dword ptr [rcx+0xC]                  
  677d846  jne short 0x677D830                           ; -> loc_677d830
  677d848  mov rax,[rcx]                                 
  677d84b  mov rax,[rax+8]                               
  677d84f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d855  jmp short 0x677D830                           ; -> loc_677d830

loc_677d857:  ; from 677d837
  677d857  mov r14,[rbp+0x800]                           

loc_677d85e:  ; from 677d827
  677d85e  mov rdx,[rbp+0x810]                           
  677d865  sub rdx,r14                                   
  677d868  cmp rdx,0x1000                                
  677d86f  jb short 0x677D88D                            ; -> loc_677d88d
  677d871  mov rax,[r14-8]                               
  677d875  add r14,0xFFFFFFFFFFFFFFF8                    
  677d879  sub r14,rax                                   
  677d87c  cmp r14,0x20                                  
  677d880  jae 0x677E039                                 ; -> loc_677e039
  677d886  add rdx,0x27                                  
  677d88a  mov r14,rax                                   

loc_677d88d:  ; from 677d86f
  677d88d  mov rcx,r14                                   
  677d890  call 0xE935700                                ; -> sub_e935700

loc_677d895:  ; from 677d819
  677d895  mov rax,[rbp+0x568]                           
```

// Interpretation: Tail of Phase 14's second cleanup: `mov rax,[rcx]`; `mov rax,[rax+0x10]` (vtable dtor [I]); `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `nop`. Second release loop for block at [rbp+0x800] (count [rbp+0x808]): `mov r14,[rbp+0x800]`; `test r14,r14`; `je loc_677d895` (skip if null); else `mov r15,[rbp+0x808]`; `cmp r14,r15`; `jne loc_677d839` (non-empty); else `jmp loc_677d85e` (empty → size check). Padding `nop [rax]` at 0x677d829 ([?]). Loop tail loc_677d830: `add r14,0x20`; `cmp r14,r15`; `je loc_677d857`. Release loop loc_677d839: `mov rcx,[r14+8]`; `test rcx,rcx`; `je loc_677d830`; else `lock dec dword ptr [rcx+0xC]` (refcount-- [I]); `jne loc_677d830`; else `mov rax,[rcx]`; `mov rax,[rax+8]` (vtable dtor [I]); `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `jmp loc_677d830`. loc_677d857: `mov r14,[rbp+0x800]`; loc_677d85e: `mov rdx,[rbp+0x810]`; `sub rdx,r14`; `cmp rdx,0x1000`; `jb loc_677d88d`; else `mov rax,[r14-8]`; `add r14,0xFFFFFFFFFFFFFFF8` (r14 -= 8); `sub r14,rax`; `cmp r14,0x20`; `jae loc_677e039`; else `add rdx,0x27`; `mov r14,rax`. loc_677d88d: `mov rcx,r14`; `call 0xE935700` (sub_e935700 — shrink/copy helper [I]). loc_677d895: `mov rax,[rbp+0x568]` continues at 0x677d89c (excluded). Range ends at `mov rax,[rbp+0x568]` (0x677d895, 7 bytes → next instruction at 0x677d89c).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x2, call 0xE935700 [V].

## Phase 14 — [0x677d75f..0x677d7fe) 40 instructions (`rdis dis 0x677d75f 40`)

Exact rdis lines:

```
  677d75f  lea r13,[rbp+0x300]                           
  677d766  lea rax,[rbp+0x790]                           
  677d76d  cmp rax,r14                                   
  677d770  je short 0x677D78F                            ; -> loc_677d78f
  677d772  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  677d779  test r14,r14                                  
  677d77c  je short 0x677D78F                            ; -> loc_677d78f
  677d77e  mov rax,[rcx]                                 
  677d781  mov rax,[rax+0x10]                            
  677d785  mov rdx,r14                                   
  677d788  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d78e  nop                                           

loc_677d78f:  ; from 677d770, 677d77c
  677d78f  mov r14,[rbp+0x7C0]                           
  677d796  mov r15d,[rbp+0x7C8]                          
  677d79d  test r15,r15                                  
  677d7a0  je short 0x677D7E6                            ; -> loc_677d7e6
  677d7a2  shl r15,5                                     
  677d7a6  xor r13d,r13d                                 
  677d7a9  jmp short 0x677D7B9                           ; -> loc_677d7b9
  677d7ab  nop [rax+rax]                                 

loc_677d7b0:  ; from 677d7c1, 677d7c7, 677d7d6
  677d7b0  add r13,0x20                                  
  677d7b4  cmp r15,r13                                   
  677d7b7  je short 0x677D7D8                            ; -> loc_677d7d8

loc_677d7b9:  ; from 677d7a9
  677d7b9  mov rcx,[r14+r13+8]                           
  677d7be  test rcx,rcx                                  
  677d7c1  je short 0x677D7B0                            ; -> loc_677d7b0
  677d7c3  lock dec dword ptr [rcx+0xC]                  
  677d7c7  jne short 0x677D7B0                           ; -> loc_677d7b0
  677d7c9  mov rax,[rcx]                                 
  677d7cc  mov rax,[rax+8]                               
  677d7d0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d7d6  jmp short 0x677D7B0                           ; -> loc_677d7b0

loc_677d7d8:  ; from 677d7b7
  677d7d8  mov r14,[rbp+0x7C0]                           
  677d7df  lea r13,[rbp+0x300]                           

loc_677d7e6:  ; from 677d7a0
  677d7e6  lea rax,[rbp+0x7D0]                           
  677d7ed  cmp rax,r14                                   
  677d7f0  je short 0x677D80F                            ; -> loc_677d80f
  677d7f2  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  677d7f9  test r14,r14                                  
  677d7fc  je short 0x677D80F                            ; -> loc_677d80f
```

// Interpretation: Release loop for slot block at [rbp+0x7C0] (count [rbp+0x7C8]): first cleanup of [rbp+0x790] via `lea rax,[rbp+0x790]`; `cmp rax,r14`; `je loc_677d78f`; else TLS-flag chain `mov rcx,[0x1233E1A8]`→`[rax]`→`[rax+0x10]`→`mov rdx,r14`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`. loc_677d78f: loads `r14=[rbp+0x7C0]` (array base), `r15d=[rbp+0x7C8]` (count); `test r15,r15`; `je loc_677d7e6` (skip if zero); else `shl r15,5` (count *= 32); `xor r13d,r13d` (idx=0); `jmp loc_677d7b9`. Padding `nop [rax+rax]` at 0x677d7ab ([?]). Loop tail loc_677d7b0: `add r13,0x20`; `cmp r15,r13`; `je loc_677d7d8`. Release loop loc_677d7b9: `mov rcx,[r14+r13+8]` (element ptr [I]); `test rcx,rcx`; `je loc_677d7b0` (skip null); else `lock dec dword ptr [rcx+0xC]` (refcount-- [I]); `jne loc_677d7b0` (skip if nonzero); else `mov rax,[rcx]`; `mov rax,[rax+8]` (vtable dtor [I]); `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `jmp loc_677d7b0`. loc_677d7d8: `mov r14,[rbp+0x7C0]`; `lea r13,[rbp+0x300]`; continues at loc_677d7e6: `lea rax,[rbp+0x7D0]`; `cmp rax,r14`; `je loc_677d80f`; else TLS-flag chain `mov rcx,[0x1233E1A8]`→`[rax]`→`[rax+0x10]`→`test r14,r14`; `je loc_677d80f`; `je short loc_677d80f` continues at 0x677d7fe (excluded). Range ends at `je short 0x677D80F` (0x677d7fc, 2 bytes → next instruction at 0x677d7fe).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x2.

## Phase 13 — [0x677d6b3..0x677d75f) 40 instructions (`rdis dis 0x677d6b3 40`)

Exact rdis lines:

```
  677d6b3  test rcx,rcx                                  
  677d6b6  je short 0x677D6FE                            ; -> loc_677d6fe
  677d6b8  mov rdx,[rbp+0x6A0]                           
  677d6bf  sub rdx,rcx                                   
  677d6c2  cmp rdx,0x1000                                
  677d6c9  jb short 0x677D6E7                            ; -> loc_677d6e7
  677d6cb  mov rax,[rcx-8]                               ; R a0-0x8
  677d6cf  add rcx,0xFFFFFFFFFFFFFFF8                    
  677d6d3  sub rcx,rax                                   
  677d6d6  cmp rcx,0x20                                  
  677d6da  jae 0x677E039                                 ; -> loc_677e039
  677d6e0  or rdx,0x27                                   
  677d6e4  mov rcx,rax                                   

loc_677d6e7:  ; from 677d6c9
  677d6e7  call 0xE935700                                ; -> sub_e935700
  677d6ec  lea rax,[rbp+0x690]                           
  677d6f3  movups [rax],xmm6                             
  677d6f6  mov qword ptr [rax+0x10],0                    

loc_677d6fe:  ; from 677d6b6
  677d6fe  mov rcx,r12                                   
  677d701  call 0x6792400                                ; -> sub_6792400
  677d706  mov r14,[rbp+0x780]                           
  677d70d  mov r15d,[rbp+0x788]                          
  677d714  test r15,r15                                  
  677d717  je short 0x677D766                            ; -> loc_677d766
  677d719  shl r15,5                                     
  677d71d  xor r13d,r13d                                 
  677d720  jmp short 0x677D739                           ; -> loc_677d739
  677d722  nop [rax+rax]                                 ; R ret@6792400+0x0+idx

loc_677d730:  ; from 677d741, 677d747, 677d756
  677d730  add r13,0x20                                  
  677d734  cmp r15,r13                                   
  677d737  je short 0x677D758                            ; -> loc_677d758

loc_677d739:  ; from 677d720
  677d739  mov rcx,[r14+r13+8]                           
  677d73e  test rcx,rcx                                  
  677d741  je short 0x677D730                            ; -> loc_677d730
  677d743  lock dec dword ptr [rcx+0xC]                  
  677d747  jne short 0x677D730                           ; -> loc_677d730
  677d749  mov rax,[rcx]                                 
  677d74c  mov rax,[rax+8]                               
  677d750  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d756  jmp short 0x677D730                           ; -> loc_677d730

loc_677d758:  ; from 677d737
  677d758  mov r14,[rbp+0x780]                           
```

// Interpretation: Branch on Phase 12's `test rcx,rcx`: `je loc_677d6fe`; else fall-through size check `mov rdx,[rbp+0x6A0]`; `sub rdx,rcx`; `cmp rdx,0x1000`; `jb loc_677d6e7`; else `mov rax,[rcx-8]`; `add rcx,0xFFFFFFFFFFFFFFF8` (rcx -= 8); `sub rcx,rax`; `cmp rcx,0x20`; `jae loc_677e039`; else `or rdx,0x27`; `mov rcx,rax`. loc_677d6e7: `call 0xE935700` (sub_e935700 — shrink/copy helper [I]); `lea rax,[rbp+0x690]`; `movups [rax],xmm6`; `mov qword ptr [rax+0x10],0`. loc_677d6fe: `mov rcx,r12`; `call 0x6792400` (sub_6792400 — destructor/release helper [I]); `mov r14,[rbp+0x780]`; `mov r15d,[rbp+0x788]`; `test r15,r15`; `je loc_677d766` (skip if zero); else `shl r15,5` (count *= 32); `xor r13d,r13d` (idx=0); `jmp loc_677d739`. Padding `nop [rax+rax]` at 0x677d722 ([?]). Loop tail loc_677d730: `add r13,0x20`; `cmp r15,r13`; `je loc_677d758`. Release loop loc_677d739: `mov rcx,[r14+r13+8]` (element ptr [I]); `test rcx,rcx`; `je loc_677d730`; else `lock dec dword ptr [rcx+0xC]` (refcount-- [I]); `jne loc_677d730`; else `mov rax,[rcx]`; `mov rax,[rax+8]` (vtable dtor [I]); `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `jmp loc_677d730`. loc_677d758: `mov r14,[rbp+0x780]` continues at 0x677d75f (excluded). Range ends at `mov r14,[rbp+0x780]` (0x677d758, 7 bytes → next instruction at 0x677d75f).
// tag: [V] all lines; calls 0xE935700 [V], 0x6792400 [V], [0xF99FFA0]=sub_eea6040 [V].

## Phase 12 — [0x677d5f2..0x677d6b3) 40 instructions (`rdis dis 0x677d5f2 40`)

Exact rdis lines:

```
  677d5f2  movzx edx,byte ptr [rbp+0x847]                
  677d5f9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d5ff  nop                                           
  677d600  mov rax,0x4000000202207803                    
  677d60a  mov [rbp+0x4A0],rax                           
  677d611  mov eax,[r14+0x590]                           
  677d618  sub eax,[r14+0x588]                           
  677d61f  shr eax,4                                     
  677d622  imul eax,0xFFFFAAAB                           
  677d628  dec eax                                       
  677d62a  mov [rbp+0x4F2],ax                            
  677d631  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d638  mov rax,[rcx]                                 
  677d63b  mov rax,[rax+0x10]                            
  677d63f  mov dl,0x4A                                   
  677d641  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d647  nop                                           
  677d648  mov [rbp+0x847],al                            
  677d64e  mov rdx,[r14+8]                               
  677d652  cmp rdx,[r14+0x10]                            
  677d656  je short 0x677D677                            ; -> loc_677d677
  677d658  mov r8d,0xC8                                  
  677d65e  mov rcx,rdx                                   
  677d661  lea rdx,[rbp+0x4A0]                           
  677d668  call 0xEEC6EC0                                ; -> sub_eec6ec0
  677d66d  add qword ptr [r14+8],0xC8                    
  677d675  jmp short 0x677D687                           ; -> loc_677d687

loc_677d677:  ; from 677d656
  677d677  mov rcx,r14                                   
  677d67a  lea r8,[rbp+0x4A0]                            
  677d681  call 0x5ABA6D0                                ; -> sub_5aba6d0
  677d686  nop                                           

loc_677d687:  ; from 677d675
  677d687  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d68e  mov rax,[rcx]                                 
  677d691  mov rax,[rax+0x10]                            
  677d695  movzx edx,byte ptr [rbp+0x847]                
  677d69c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d6a2  nop                                           
  677d6a3  cmp byte ptr [rbp+0x6D0],1                    
  677d6aa  jne short 0x677D6FE                           ; -> loc_677d6fe
  677d6ac  mov rcx,[rbp+0x690]                           
```

// Interpretation: TLS-flag chain `movzx edx,byte [rbp+0x847]`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`. Tag store: `mov rax,0x4000000202207803`; `mov [rbp+0x4A0],rax` (u64 tag at +0x4A0 [I]). Cursor delta: `mov eax,[r14+0x590]`; `sub eax,[r14+0x588]`; `shr eax,4` (/16 [I]); `imul eax,0xFFFFAAAB` (magic multiply [I]); `dec eax`; `mov [rbp+0x4F2],ax` (count [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`; `mov [rbp+0x847],al`. List append: `mov rdx,[r14+8]` (cursor [I]); `cmp [r14+0x10]` (end [I]); `je loc_677d677` (grow); else fast path: `mov r8d,0xC8` (size 200 [I]); `mov rcx,rdx`; `lea rdx,[rbp+0x4A0]`; `call 0xEEC6EC0` (sub_eec6ec0 — memcpy/copy helper [I]); `add qword ptr [r14+8],0xC8` (cursor += 0xC8 [I]); `jmp loc_677d687`. Grow target loc_677d677: `mov rcx,r14`; `lea r8,[rbp+0x4A0]`; `call 0x5ABA6D0` (sub_5aba6d0 — grow/copy helper [I]); `nop`. loc_677d687: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x847]`→`call [0xF99FFA0]`→`nop`; flag check `cmp byte ptr [rbp+0x6D0],1`; `jne short loc_677d6fe`; `mov rcx,[rbp+0x690]` continues at 0x677d6b3 (excluded). Range ends at `mov rcx,[rbp+0x690]` (0x677d6ac, 7 bytes → next instruction at 0x677d6b3).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x3, 0xEEC6EC0 [V], 0x5ABA6D0 [V].

## Phase 11 — [0x677d546..0x677d5f2) 40 instructions (`rdis dis 0x677d546 40`)

Exact rdis lines:

```
  677d546  not eax                                       
  677d548  add eax,[r14+0x6B0]                           
  677d54f  mov [rbp+0x5AA],ax                            
  677d556  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d55d  mov rax,[rcx]                                 
  677d560  mov rax,[rax+0x10]                            
  677d564  mov dl,0x4A                                   
  677d566  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d56c  nop                                           
  677d56d  mov [rbp+0x838],al                            
  677d573  mov rdx,[r14+8]                               
  677d577  cmp rdx,[r14+0x10]                            
  677d57b  je short 0x677D598                            ; -> loc_677d598
  677d57d  mov r8d,0xC8                                  
  677d583  mov rcx,rdx                                   
  677d586  mov rdx,r12                                   
  677d589  call 0xEEC6EC0                                ; -> sub_eec6ec0
  677d58e  add qword ptr [r14+8],0xC8                    
  677d596  jmp short 0x677D5A4                           ; -> loc_677d5a4

loc_677d598:  ; from 677d57b
  677d598  mov rcx,r14                                   
  677d59b  mov r8,r12                                    
  677d59e  call 0x5ABA6D0                                ; -> sub_5aba6d0
  677d5a3  nop                                           

loc_677d5a4:  ; from 677d596
  677d5a4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d5ab  mov rax,[rcx]                                 
  677d5ae  mov rax,[rax+0x10]                            
  677d5b2  movzx edx,byte ptr [rbp+0x838]                
  677d5b9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d5bf  nop                                           
  677d5c0  lea rcx,[rbp+0x110]                           
  677d5c7  call 0x67E1840                                ; -> sub_67e1840
  677d5cc  jmp 0x677DE96                                 ; -> loc_677de96
  677d5d1  mov rcx,r14                                   
  677d5d4  add rcx,0x588                                 
  677d5db  mov r8,r12                                    
  677d5de  call 0x6765870                                ; -> sub_6765870
  677d5e3  nop                                           

loc_677d5e4:  ; from 677ce34, 677ce43
  677d5e4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d5eb  mov rax,[rcx]                                 
  677d5ee  mov rax,[rax+0x10]                            
```

// Interpretation: Tail of Phase 10: `not eax`; `add eax,[r14+0x6B0]`; `mov [rbp+0x5AA],ax` (checksum [I]). TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`; `mov [rbp+0x838],al`. List append: `mov rdx,[r14+8]` (cursor [I]); `cmp [r14+0x10]` (end [I]); `je loc_677d598` (grow); else fast path: `mov r8d,0xC8` (size 200 [I]); `mov rcx,rdx`; `mov rdx,r12`; `call 0xEEC6EC0` (sub_eec6ec0 — memcpy/copy helper [I]); `add qword ptr [r14+8],0xC8` (cursor += 0xC8 [I]); `jmp loc_677d5a4`. Grow target loc_677d598: `mov rcx,r14`; `mov r8,r12`; `call 0x5ABA6D0` (sub_5aba6d0 — grow/copy helper [I]); `nop`. loc_677d5a4: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]`→`nop`; `lea rcx,[rbp+0x110]`; `call 0x67E1840` (sub_67e1840 — finalizer/commit helper [I]); `jmp loc_677de96` (function tail jump [I]). Jump targets from earlier phases: loc_677d5d1: `mov rcx,r14`; `add rcx,0x588`; `mov r8,r12`; `call 0x6765870` (sub_6765870 — grow helper [I]); `nop`. loc_677d5e4: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]` continues at 0x677d5f2 (excluded). Range ends at `mov rax,[rax+0x10]` (0x677d5ee, 4 bytes → next instruction at 0x677d5f2).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x3, 0xEEC6EC0 [V], 0x5ABA6D0 [V], 0x67E1840 [V], 0x6765870 [V].

## Phase 10 — [0x677d486..0x677d546) 40 instructions (`rdis dis 0x677d486 40`)

Exact rdis lines:

```
  677d486  lea r8,[rbp+0x118]                            
  677d48d  call 0x6760710                                ; -> sub_6760710
  677d492  nop                                           
  677d493  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d49a  mov rax,[rcx]                                 
  677d49d  mov rax,[rax+0x10]                            
  677d4a1  movzx edx,byte ptr [rbp+0x838]                
  677d4a8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d4ae  nop                                           
  677d4af  mov eax,[r14+0x770]                           
  677d4b6  sub eax,[r14+0x768]                           
  677d4bd  shr eax,3                                     
  677d4c0  imul eax,0xFFFFF0F1                           
  677d4c6  dec eax                                       
  677d4c8  mov [rbp+0x59A],ax                            
  677d4cf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d4d6  mov rax,[rcx]                                 
  677d4d9  mov rax,[rax+0x10]                            
  677d4dd  mov dl,0x4A                                   
  677d4df  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d4e5  nop                                           
  677d4e6  mov [rbp+0x838],al                            
  677d4ec  mov rdx,[r14+0x6B0]                           
  677d4f3  cmp rdx,[r14+0x6B8]                           
  677d4fa  je short 0x677D508                            ; -> loc_677d508
  677d4fc  inc rdx                                       
  677d4ff  mov [r14+0x6B0],rdx                           
  677d506  jmp short 0x677D518                           ; -> loc_677d518

loc_677d508:  ; from 677d4fa
  677d508  mov rcx,r14                                   
  677d50b  add rcx,0x6A8                                 
  677d512  call 0x6760E60                                ; -> sub_6760e60
  677d517  nop                                           

loc_677d518:  ; from 677d506
  677d518  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d51f  mov rax,[rcx]                                 
  677d522  mov rax,[rax+0x10]                            
  677d526  movzx edx,byte ptr [rbp+0x838]                
  677d52d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d533  nop                                           
  677d534  mov qword ptr [rbp+0x570],0x2207803           
  677d53f  mov eax,[r14+0x6A8]                           
```

// Interpretation: Grow target tail from Phase 9: `lea r8,[rbp+0x118]`; `call 0x6760710` (sub_6760710 — grow helper [I]); `nop`. loc_677d493 (jmp target from Phase 9): TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`. Cursor delta: `mov eax,[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3` (/8 [I]); `imul eax,0xFFFFF0F1` (magic multiply [I]); `dec eax`; `mov [rbp+0x59A],ax` (count [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`; `mov [rbp+0x838],al`. Counter increment: `mov rdx,[r14+0x6B0]`; `cmp [r14+0x6B8]`; `je loc_677d508` (grow); else `inc rdx`; `mov [r14+0x6B0],rdx`; `jmp loc_677d518`. Grow target loc_677d508: `mov rcx,r14`; `add rcx,0x6A8`; `call 0x6760E60` (sub_6760e60 — grow helper [I]); `nop`. loc_677d518: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]`→`nop`; `mov qword ptr [rbp+0x570],0x2207803` (tag/flags [I]); `mov eax,[r14+0x6A8]` continues at 0x677d546 (excluded). Range ends at `mov eax,[r14+0x6A8]` (0x677d53f, 7 bytes → next instruction at 0x677d546).
// tag: [V] all lines; calls 0x6760710 [V], [0xF99FFA0]=sub_eea6040 [V] x3, 0x6760E60 [V].

## Phase 9 — [0x677d3af..0x677d486) 40 instructions (`rdis dis 0x677d3af 40`)

Exact rdis lines:

```
  677d3af  nop                                           
  677d3b0  mov eax,[r14+0x650]                           
  677d3b7  sub eax,[r14+0x648]                           
  677d3be  shr eax,3                                     
  677d3c1  imul eax,0xFFFF8E39                           
  677d3c7  dec eax                                       
  677d3c9  mov [rbp+0x5B2],ax                            
  677d3d0  lea rcx,[r14+0x780]                           
  677d3d7  lea rdx,[rbp+0x1A0]                           
  677d3de  call 0x675F3B0                                ; -> sub_675f3b0
  677d3e3  nop                                           
  677d3e4  mov qword ptr [rbp+0x570],0x2005803           
  677d3ef  mov eax,[r14+0x788]                           
  677d3f6  sub eax,[r14+0x780]                           
  677d3fd  shr eax,3                                     
  677d400  imul eax,0xFFFF8BA3                           
  677d406  dec eax                                       
  677d408  mov [rbp+0x598],ax                            
  677d40f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d416  mov rax,[rcx]                                 
  677d419  mov rax,[rax+0x10]                            
  677d41d  mov dl,0x4A                                   
  677d41f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d425  mov [rbp+0x838],al                            
  677d42b  mov r15,[r14+0x770]                           
  677d432  cmp r15,[r14+0x778]                           
  677d439  je short 0x677D47C                            ; -> loc_677d47c
  677d43b  mov rax,[rbp+0x118]                           
  677d442  mov [r15],rax                                 
  677d445  lea rcx,[r15+8]                               
  677d449  lea rdx,[rbp+0x120]                           
  677d450  call 0xE869FF0                                ; -> sub_e869ff0
  677d455  nop                                           
  677d456  mov rax,[rbp+0x198]                           
  677d45d  mov [r15+0x80],rax                            
  677d464  mov qword ptr [rbp+0x198],0                   
  677d46f  add qword ptr [r14+0x770],0x88                
  677d47a  jmp short 0x677D493                           ; -> loc_677d493

loc_677d47c:  ; from 677d439
  677d47c  lea rcx,[r14+0x768]                           
  677d483  mov rdx,r15                                   
```

// Interpretation: Tail of Phase 8's TLS chain: `nop` at 0x677d3af (no `mov [rbp+0x838],al` after this call — value consumed differently [?]). Cursor delta: `mov eax,[r14+0x650]`; `sub eax,[r14+0x648]`; `shr eax,3` (/8 [I]); `imul eax,0xFFFF8E39` (magic multiply [I]); `dec eax`; `mov [rbp+0x5B2],ax` (count [I]). Sub-call: `lea rcx,[r14+0x780]`; `lea rdx,[rbp+0x1A0]`; `call 0x675F3B0` (sub_675f3b0 — copy helper [I]); `nop`. Tag/store: `mov qword ptr [rbp+0x570],0x2005803` (tag/flags [I]). Cursor delta: `mov eax,[r14+0x788]`; `sub eax,[r14+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x598],ax` (count [I]). TLS-flag chain: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`; `mov [rbp+0x838],al`. List append: `mov r15,[r14+0x770]` (cursor [I]); `cmp [r14+0x778]` (end [I]); `je loc_677d47c` (grow); else fast path: `mov rax,[rbp+0x118]`; `mov [r15],rax` (ptr store [I]); `lea rcx,[r15+8]`; `lea rdx,[rbp+0x120]`; `call 0xE869FF0` (sub_e869ff0 — copy helper [I]); `nop`; `mov rax,[rbp+0x198]`; `mov [r15+0x80],rax` (ptr store [I]); `mov qword ptr [rbp+0x198],0` (clear [I]); `add qword ptr [r14+0x770],0x88` (cursor += 0x88 [I]); `jmp loc_677d493`. Grow target loc_677d47c: `lea rcx,[r14+0x768]`; `mov rdx,r15` continues at 0x677d486 (excluded). Range ends at `mov rdx,r15` (0x677d483, 3 bytes → next instruction at 0x677d486).
// tag: [V] all lines; calls 0x675F3B0 [V], [0xF99FFA0]=sub_eea6040 [V], 0xE869FF0 [V].

## Phase 8 — [0x677d2dd..0x677d3af) 40 instructions (`rdis dis 0x677d2dd 40`)

Exact rdis lines:

```
  677d2dd  add eax,[r14+0x890]                           
  677d2e4  mov [rbp+0x582],ax                            
  677d2eb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d2f2  mov rax,[rcx]                                 
  677d2f5  mov rax,[rax+0x10]                            
  677d2f9  mov dl,0x4A                                   
  677d2fb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d301  nop                                           
  677d302  mov [rbp+0x838],al                            
  677d308  mov rdx,[r14+0x7A0]                           
  677d30f  cmp rdx,[r14+0x7A8]                           
  677d316  je short 0x677D324                            ; -> loc_677d324
  677d318  inc rdx                                       
  677d31b  mov [r14+0x7A0],rdx                           
  677d322  jmp short 0x677D331                           ; -> loc_677d331

loc_677d324:  ; from 677d316
  677d324  lea rcx,[r14+0x798]                           
  677d32b  call 0x6760E60                                ; -> sub_6760e60
  677d330  nop                                           

loc_677d331:  ; from 677d322
  677d331  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d338  mov rax,[rcx]                                 
  677d33b  mov rax,[rax+0x10]                            
  677d33f  movzx edx,byte ptr [rbp+0x838]                
  677d346  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d34c  nop                                           
  677d34d  mov eax,[r14+0x798]                           
  677d354  not eax                                       
  677d356  add eax,[r14+0x7A0]                           
  677d35d  mov [rbp+0x596],ax                            
  677d364  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d36b  mov rax,[rcx]                                 
  677d36e  mov rax,[rax+0x10]                            
  677d372  mov dl,0x4A                                   
  677d374  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d37a  mov [rbp+0x838],al                            
  677d380  lea rcx,[r14+0x648]                           
  677d387  lea rdx,[rbp+0x1F8]                           
  677d38e  call 0x675FB30                                ; -> sub_675fb30
  677d393  nop                                           
  677d394  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d39b  mov rax,[rcx]                                 
  677d39e  mov rax,[rax+0x10]                            
  677d3a2  movzx edx,byte ptr [rbp+0x838]                
  677d3a9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

// Interpretation: Tail of Phase 7: `add eax,[r14+0x890]`; `mov [rbp+0x582],ax` (checksum [I]). TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`; `mov [rbp+0x838],al`. Counter increment: `mov rdx,[r14+0x7A0]`; `cmp [r14+0x7A8]`; `je loc_677d324` (grow); else `inc rdx`; `mov [r14+0x7A0],rdx`; `jmp loc_677d331`. Grow target loc_677d324: `lea rcx,[r14+0x798]`; `call 0x6760E60` (sub_6760e60 — grow helper [I]); `nop`. loc_677d331: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]`→`nop`; `mov eax,[r14+0x798]`; `not eax`; `add eax,[r14+0x7A0]`; `mov [rbp+0x596],ax` (checksum [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`; `mov [rbp+0x838],al`. Sub-call setup: `lea rcx,[r14+0x648]`; `lea rdx,[rbp+0x1F8]`; `call 0x675FB30` (sub_675fb30 — copy helper [I]); `nop`. TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]` continues at 0x677d3af (excluded). Range ends at `call [0xF99FFA0]` (0x677d3a9, 6 bytes → next instruction at 0x677d3af).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x4, 0x6760E60 [V], 0x675FB30 [V].

## Phase 7 — [0x677d209..0x677d2dd) 40 instructions (`rdis dis 0x677d209 40`)

Exact rdis lines:

```
  677d209  movups [rdx+0x47],xmm2                        
  677d20d  add qword ptr [r14+0x758],0x58                
  677d215  jmp short 0x677D22B                           ; -> loc_677d22b

loc_677d217:  ; from 677d199
  677d217  lea rcx,[r14+0x750]                           
  677d21e  lea r8,[rbp+0x250]                            
  677d225  call 0x6760A80                                ; -> sub_6760a80
  677d22a  nop                                           

loc_677d22b:  ; from 677d215
  677d22b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d232  mov rax,[rcx]                                 
  677d235  mov rax,[rax+0x10]                            
  677d239  movzx edx,byte ptr [rbp+0x838]                
  677d240  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d246  nop                                           
  677d247  mov qword ptr [rbp+0x570],0x4001              
  677d252  mov eax,[r14+0x758]                           
  677d259  sub eax,[r14+0x750]                           
  677d260  shr eax,3                                     
  677d263  imul eax,0xFFFF8BA3                           
  677d269  dec eax                                       
  677d26b  mov [rbp+0x59C],ax                            
  677d272  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d279  mov rax,[rcx]                                 
  677d27c  mov rax,[rax+0x10]                            
  677d280  mov dl,0x4A                                   
  677d282  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d288  nop                                           
  677d289  mov [rbp+0x838],al                            
  677d28f  mov rdx,[r14+0x890]                           
  677d296  cmp rdx,[r14+0x898]                           
  677d29d  je short 0x677D2AB                            ; -> loc_677d2ab
  677d29f  inc rdx                                       
  677d2a2  mov [r14+0x890],rdx                           
  677d2a9  jmp short 0x677D2B8                           ; -> loc_677d2b8

loc_677d2ab:  ; from 677d29d
  677d2ab  lea rcx,[r14+0x888]                           
  677d2b2  call 0x6760E60                                ; -> sub_6760e60
  677d2b7  nop                                           

loc_677d2b8:  ; from 677d2a9
  677d2b8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d2bf  mov rax,[rcx]                                 
  677d2c2  mov rax,[rax+0x10]                            
  677d2c6  movzx edx,byte ptr [rbp+0x838]                
  677d2cd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d2d3  nop                                           
  677d2d4  mov eax,[r14+0x888]                           
  677d2db  not eax                                       
```

// Interpretation: Tail of Phase 6 fast path: `movups [rdx+0x47],xmm2`; `add qword ptr [r14+0x758],0x58` (cursor += 0x58 [I]); `jmp loc_677d22b`. Grow target loc_677d217: `lea rcx,[r14+0x750]`; `lea r8,[rbp+0x250]`; `call 0x6760A80` (sub_6760a80 — grow helper [I]); `nop`. loc_677d22b: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`; `mov qword ptr [rbp+0x570],0x4001` (tag/flags [I]); cursor delta `mov eax,[r14+0x758]`; `sub eax,[r14+0x750]`; `shr eax,3` (/8 [I]); `imul eax,0xFFFF8BA3` (magic multiply [I]); `dec eax`; `mov [rbp+0x59C],ax` (count [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`; `mov [rbp+0x838],al`. Counter increment: `mov rdx,[r14+0x890]`; `cmp [r14+0x898]`; `je loc_677d2ab` (grow); else `inc rdx`; `mov [r14+0x890],rdx`; `jmp loc_677d2b8`. Grow target loc_677d2ab: `lea rcx,[r14+0x888]`; `call 0x6760E60` (sub_6760e60 — grow helper [I]); `nop`. loc_677d2b8: TLS-flag chain `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x838]`→`call [0xF99FFA0]`→`nop`; `mov eax,[r14+0x888]`; `not eax` continues at 0x677d2dd (excluded). Range ends at `not eax` (0x677d2db, 2 bytes → next instruction at 0x677d2dd).
// tag: [V] all lines; calls 0x6760A80 [V], [0xF99FFA0]=sub_eea6040 [V] x3, 0x6760E60 [V].

## Phase 6 — [0x677d140..0x677d209) 40 instructions (`rdis dis 0x677d140 40`)

Exact rdis lines:

```
  677d140  mov rax,[rcx]                                 
  677d143  mov rax,[rax+0x10]                            
  677d147  movzx edx,byte ptr [rbp+0x838]                
  677d14e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d154  nop                                           
  677d155  mov eax,[r14+0x8A8]                           
  677d15c  sub eax,[r14+0x8A0]                           
  677d163  shr eax,1                                     
  677d165  dec eax                                       
  677d167  mov [rbp+0x580],ax                            
  677d16e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d175  mov rax,[rcx]                                 
  677d178  mov rax,[rax+0x10]                            
  677d17c  mov dl,0x4A                                   
  677d17e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d184  nop                                           
  677d185  mov [rbp+0x838],al                            
  677d18b  mov rdx,[r14+0x758]                           
  677d192  cmp rdx,[r14+0x760]                           
  677d199  je short 0x677D217                            ; -> loc_677d217
  677d19b  lea rcx,[rbp+0x250]                           
  677d1a2  mov eax,[rcx+0x10]                            
  677d1a5  mov [rdx+0x10],eax                            
  677d1a8  movups xmm0,[rcx]                             
  677d1ab  movups [rdx],xmm0                             
  677d1ae  movzx eax,byte ptr [rbp+0x264]                
  677d1b5  mov [rdx+0x14],al                             
  677d1b8  movss xmm0,[rbp+0x268]                        
  677d1c0  movss [rdx+0x18],xmm0                         
  677d1c5  movss xmm0,[rbp+0x26C]                        
  677d1cd  movss [rdx+0x1C],xmm0                         
  677d1d2  movss xmm0,[rbp+0x270]                        
  677d1da  movss [rdx+0x20],xmm0                         
  677d1df  movss xmm0,[rbp+0x274]                        
  677d1e7  movss [rdx+0x24],xmm0                         
  677d1ec  movups xmm0,[rbx+0x88]                        
  677d1f3  movups xmm1,[rbx+0x98]                        
  677d1fa  movups xmm2,[rbx+0xA7]                        
  677d201  movups [rdx+0x28],xmm0                        
  677d205  movups [rdx+0x38],xmm1                        
```

// Interpretation: TLS-flag chain continuation: `mov rax,[rcx]`; `mov rax,[rax+0x10]`; `movzx edx,byte ptr [rbp+0x838]`; `call [0xF99FFA0]` (sub_eea6040 [V]); `nop`. Cursor delta: `mov eax,[r14+0x8A8]`; `sub eax,[r14+0x8A0]`; `shr eax,1` (bytes→chars /2 [I]); `dec eax`; `mov [rbp+0x580],ax` (count [I]). TLS-flag chain again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`; `mov [rbp+0x838],al`. Record append: `mov rdx,[r14+0x758]` (cursor [I]); `cmp [r14+0x760]` (end [I]); `je loc_677d217` (grow); else fast path: `lea rcx,[rbp+0x250]`; `mov eax,[rcx+0x10]`; `mov [rdx+0x10],eax`; `movups xmm0,[rcx]`; `movups [rdx],xmm0` (16-byte copy [I]); `movzx eax,byte ptr [rbp+0x264]`; `mov [rdx+0x14],al`; `movss xmm0,[rbp+0x268]`; `movss [rdx+0x18],xmm0`; `movss xmm0,[rbp+0x26C]`; `movss [rdx+0x1C],xmm0`; `movss xmm0,[rbp+0x270]`; `movss [rdx+0x20],xmm0`; `movss xmm0,[rbp+0x274]`; `movss [rdx+0x24],xmm0` (float fields at +0x18,+0x1C,+0x20,+0x24 [I]); `movups xmm0,[rbx+0x88]`; `movups xmm1,[rbx+0x98]`; `movups xmm2,[rbx+0xA7]`; `movups [rdx+0x28],xmm0`; `movups [rdx+0x38],xmm1` continues at 0x677d209 (excluded). Range ends at `movups [rdx+0x38],xmm1` (0x677d205, 4 bytes → next instruction at 0x677d209).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x2.

## Phase 5 — [0x677d063..0x677d140) 40 instructions (`rdis dis 0x677d063 40`)

Exact rdis lines:

```
  677d063  jne 0x677D5C0                                 ; -> loc_677d5c0
  677d069  mov rax,[rbp+0x828]                           
  677d070  mov rcx,[rax+0x10]                            
  677d074  mov eax,0x9D0                                 
  677d079  add rcx,rax                                   
  677d07c  call 0x5ABA5C0                                ; -> sub_5aba5c0
  677d081  nop                                           
  677d082  mov r14,rax                                   
  677d085  movaps [rbp+0x620],xmm6                       
  677d08c  movaps [rbp+0x610],xmm6                       
  677d093  movaps [rbp+0x600],xmm6                       
  677d09a  movaps [rbp+0x5F0],xmm6                       
  677d0a1  movaps [rbp+0x5E0],xmm6                       
  677d0a8  movaps [rbp+0x5D0],xmm6                       
  677d0af  movaps [rbp+0x5C0],xmm6                       
  677d0b6  movaps [rbp+0x5B0],xmm6                       
  677d0bd  movaps [rbp+0x5A0],xmm6                       
  677d0c4  movaps [rbp+0x590],xmm6                       
  677d0cb  movaps [rbp+0x580],xmm6                       
  677d0d2  movaps [rbp+0x570],xmm6                       
  677d0d9  mov qword ptr [rbp+0x630],0                   
  677d0e4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677d0eb  mov rax,[rcx]                                 
  677d0ee  mov rax,[rax+0x10]                            
  677d0f2  mov dl,0x4A                                   
  677d0f4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d0fa  nop                                           
  677d0fb  mov [rbp+0x838],al                            
  677d101  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
  677d108  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
  677d10f  je short 0x677D125                            ; -> loc_677d125
  677d111  movzx eax,word ptr [rbp+0x2A8]                
  677d118  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
  677d11b  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
  677d123  jmp short 0x677D139                           ; -> loc_677d139

loc_677d125:  ; from 677d10f
  677d125  lea rcx,[r14+0x8A0]                           
  677d12c  lea r8,[rbp+0x2A8]                            
  677d133  call 0x1EF6F90                                ; -> sub_1ef6f90
  677d138  nop                                           

loc_677d139:  ; from 677d123
  677d139  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```

// Interpretation: Branch from Phase 4 `cmp [rbp+0x838],[rbp+0x568]`: `jne loc_677d5c0` (skip); else fall-through: `mov rax,[rbp+0x828]`; `mov rcx,[rax+0x10]`; `mov eax,0x9D0`; `add rcx,rax`; `call 0x5ABA5C0` (sub_5aba5c0 — alloc/serialize helper [I]); `nop`; `mov r14,rax` (result). Zero-out block: `movaps [rbp+0x620..0x570],xmm6` (14× 16-byte zero stores from 0x570 to 0x620 [I]); `mov qword ptr [rbp+0x630],0`. TLS-flag chain: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`; `mov [rbp+0x838],al`. Slot append: `mov rdx,[r14+0x8A8]`; `cmp [r14+0x8B0]`; `je loc_677d125` (grow); else fast path `movzx eax,word ptr [rbp+0x2A8]`; `mov [rdx],ax` (u16 store [I]); `add qword ptr [r14+0x8A8],2` (cursor += 2 [I]); `jmp loc_677d139`. Grow target loc_677d125: `lea rcx,[r14+0x8A0]`; `lea r8,[rbp+0x2A8]`; `call 0x1EF6F90` (sub_1ef6f90 — grow helper [I]); `nop`. loc_677d139: `mov rcx,[0x1233E1B0]` continues at 0x677d140 (excluded). Range ends at `mov rcx,[0x1233E1B0]` (0x677d139, 7 bytes → next instruction at 0x677d140).
// tag: [V] all lines; calls 0x5ABA5C0 [V], [0xF99FFA0]=sub_eea6040 [V], 0x1EF6F90 [V].

## Phase 4 — [0x677cfc1..0x677d063) 40 instructions (`rdis dis 0x677cfc1 40`)

Exact rdis lines:

```
  677cfc1  mov rax,[rax+0x10]                            
  677cfc5  mov rdx,r14                                   
  677cfc8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cfce  nop                                           
  677cfcf  mov r14,[rbp+0x800]                           
  677cfd6  test r14,r14                                  
  677cfd9  je short 0x677D055                            ; -> loc_677d055
  677cfdb  mov r15,[rbp+0x808]                           
  677cfe2  cmp r14,r15                                   
  677cfe5  jne short 0x677CFF9                           ; -> loc_677cff9
  677cfe7  jmp short 0x677D01E                           ; -> loc_677d01e
  677cfe9  nop [rax]                                     

loc_677cff0:  ; from 677d000, 677d006, 677d015
  677cff0  add r14,0x20                                  
  677cff4  cmp r14,r15                                   
  677cff7  je short 0x677D017                            ; -> loc_677d017

loc_677cff9:  ; from 677cfe5
  677cff9  mov rcx,[r14+8]                               
  677cffd  test rcx,rcx                                  
  677d000  je short 0x677CFF0                            ; -> loc_677cff0
  677d002  lock dec dword ptr [rcx+0xC]                  
  677d006  jne short 0x677CFF0                           ; -> loc_677cff0
  677d008  mov rax,[rcx]                                 
  677d00b  mov rax,[rax+8]                               
  677d00f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677d015  jmp short 0x677CFF0                           ; -> loc_677cff0

loc_677d017:  ; from 677cff7
  677d017  mov r14,[rbp+0x800]                           

loc_677d01e:  ; from 677cfe7
  677d01e  mov rdx,[rbp+0x810]                           
  677d025  sub rdx,r14                                   
  677d028  cmp rdx,0x1000                                
  677d02f  jb short 0x677D04D                            ; -> loc_677d04d
  677d031  mov rax,[r14-8]                               
  677d035  add r14,0xFFFFFFFFFFFFFFF8                    
  677d039  sub r14,rax                                   
  677d03c  cmp r14,0x20                                  
  677d040  jae 0x677E039                                 ; -> loc_677e039
  677d046  add rdx,0x27                                  
  677d04a  mov r14,rax                                   

loc_677d04d:  ; from 677d02f
  677d04d  mov rcx,r14                                   
  677d050  call 0xE935700                                ; -> sub_e935700

loc_677d055:  ; from 677cfd9
  677d055  mov rax,[rbp+0x568]                           
  677d05c  cmp [rbp+0x838],rax                           
```

// Interpretation: Tail of Phase 3's second cleanup: `mov rax,[rax+0x10]`; `mov rdx,r14`; `call [0xF99FFA0]` (sub_eea6040 [V]); `nop`. Second release loop for block at [rbp+0x800] (count [rbp+0x808]): `mov r14,[rbp+0x800]`; `test r14,r14`; `je loc_677d055` (skip if null); else `mov r15,[rbp+0x808]`; `cmp r14,r15`; `jne loc_677cff9` (non-empty); else `jmp loc_677d01e` (empty → size check). Padding `nop [rax]` at 0x677cfe9 ([?]). Loop tail loc_677cff0: `add r14,0x20`; `cmp r14,r15`; `je loc_677d017`. Release loop loc_677cff9: `mov rcx,[r14+8]`; `test rcx,rcx`; `je loc_677cff0`; else `lock dec dword ptr [rcx+0xC]` (refcount-- [I]); `jne loc_677cff0`; else `mov rax,[rcx]`; `mov rax,[rax+8]` (vtable dtor [I]); `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `jmp loc_677cff0`. loc_677d017: `mov r14,[rbp+0x800]`; loc_677d01e: `mov rdx,[rbp+0x810]`; `sub rdx,r14`; `cmp rdx,0x1000`; `jb loc_677d04d`; else `mov rax,[r14-8]`; `add r14,0xFFFFFFFFFFFFFFF8` (r14 -= 8); `sub r14,rax`; `cmp r14,0x20`; `jae loc_677e039`; else `add rdx,0x27`; `mov r14,rax`. loc_677d04d: `mov rcx,r14`; `call 0xE935700` (sub_e935700 — shrink/copy helper [I]). loc_677d055: `mov rax,[rbp+0x568]`; `cmp [rbp+0x838],rax` continues at 0x677d063 (excluded). Range ends at `cmp [rbp+0x838],rax` (0x677d05c, 7 bytes → next instruction at 0x677d063).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x2, call 0xE935700 [V].

## Phase 3 — [0x677cf26..0x677cfc1) 40 instructions (`rdis dis 0x677cf26 40`)

Exact rdis lines:

```
  677cf26  lea rax,[rbp+0x790]                           
  677cf2d  cmp rax,r14                                   
  677cf30  je short 0x677CF4F                            ; -> loc_677cf4f
  677cf32  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  677cf39  test r14,r14                                  
  677cf3c  je short 0x677CF4F                            ; -> loc_677cf4f
  677cf3e  mov rax,[rcx]                                 
  677cf41  mov rax,[rax+0x10]                            
  677cf45  mov rdx,r14                                   
  677cf48  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cf4e  nop                                           

loc_677cf4f:  ; from 677cf30, 677cf3c
  677cf4f  mov r14,[rbp+0x7C0]                           
  677cf56  mov r15d,[rbp+0x7C8]                          
  677cf5d  test r15,r15                                  
  677cf60  je short 0x677CFA6                            ; -> loc_677cfa6
  677cf62  shl r15,5                                     
  677cf66  xor r13d,r13d                                 
  677cf69  jmp short 0x677CF79                           ; -> loc_677cf79
  677cf6b  nop [rax+rax]                                 

loc_677cf70:  ; from 677cf81, 677cf87, 677cf96
  677cf70  add r13,0x20                                  
  677cf74  cmp r15,r13                                   
  677cf77  je short 0x677CF98                            ; -> loc_677cf98

loc_677cf79:  ; from 677cf69
  677cf79  mov rcx,[r14+r13+8]                           
  677cf7e  test rcx,rcx                                  
  677cf81  je short 0x677CF70                            ; -> loc_677cf70
  677cf83  lock dec dword ptr [rcx+0xC]                  
  677cf87  jne short 0x677CF70                           ; -> loc_677cf70
  677cf89  mov rax,[rcx]                                 
  677cf8c  mov rax,[rax+8]                               
  677cf90  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cf96  jmp short 0x677CF70                           ; -> loc_677cf70

loc_677cf98:  ; from 677cf77
  677cf98  mov r14,[rbp+0x7C0]                           
  677cf9f  lea r13,[rbp+0x300]                           

loc_677cfa6:  ; from 677cf60
  677cfa6  lea rax,[rbp+0x7D0]                           
  677cfad  cmp rax,r14                                   
  677cfb0  je short 0x677CFCF                            ; -> loc_677cfcf
  677cfb2  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  677cfb9  test r14,r14                                  
  677cfbc  je short 0x677CFCF                            ; -> loc_677cfcf
  677cfbe  mov rax,[rcx]                                 
```

// Interpretation: Release loop for slot block at [rbp+0x7C0] (count [rbp+0x7C8]): first cleanup of [rbp+0x790] via `lea rax,[rbp+0x790]`; `cmp rax,r14`; `je loc_677cf4f`; else TLS-flag call chain `mov rcx,[0x1233E1A8]`→`[rax]`→`[rax+0x10]`→`mov rdx,r14`→`call [0xF99FFA0]` (sub_eea6040 [V])→`nop`. loc_677cf4f: loads `r14=[rbp+0x7C0]` (array base), `r15d=[rbp+0x7C8]` (count); `test r15,r15`; `je loc_677cfa6` (skip if zero); else `shl r15,5` (count *= 32); `xor r13d,r13d` (idx=0); `jmp loc_677cf79`. Padding `nop [rax+rax]` at 0x677cf6b ([?]). Loop tail loc_677cf70: `add r13,0x20`; `cmp r15,r13`; `je loc_677cf98`. Release loop loc_677cf79: `mov rcx,[r14+r13+8]` (element ptr [I]); `test rcx,rcx`; `je loc_677cf70` (skip null); else `lock dec dword ptr [rcx+0xC]` (refcount-- [I]); `jne loc_677cf70` (skip if nonzero); else `mov rax,[rcx]`; `mov rax,[rax+8]` (vtable dtor [I]); `call [0xF99FFA0]` (sub_eea6040 — virtual dtor [V]); `jmp loc_677cf70`. loc_677cf98: `mov r14,[rbp+0x7C0]`; `lea r13,[rbp+0x300]`; continues at loc_677cfa6: `lea rax,[rbp+0x7D0]`; `cmp rax,r14`; `je loc_677cfcf`; else TLS-flag chain `mov rcx,[0x1233E1A8]`→`[rax]`→`[rax+0x10]`→`mov rdx,r14`→`call [0xF99FFA0]`→`nop`; `test r14,r14`; `je loc_677cfcf`; `mov rax,[rcx]` continues at 0x677cfc1 (excluded). Range ends at `mov rax,[rcx]` (0x677cfbe, 3 bytes → next instruction at 0x677cfc1).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x3.