# U-E4-F8: sub_67762e0 chunk builder — continuation from 0x677cdb6 to 0x677e166

Unit: U-E4-F8
Function: sub_67762e0 (chunk builder, called by chunk extractor 0x66ea3d0) — continuation of U-E4-F7
RVAs: continuation from 0x677cdb6 (Phase 1), function span [0x67762e0..0x677e166)
Source: `rdis dis` on Minecraft.Windows.exe 1.26.62.01 (version 1.26.62.01), RVAs relative to image base
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Resume continuation at RVA 0x677cf26 (Phase 3). Function end boundary: 0x677e166 (exclusive).

## Phase 1 — [0x677cdb6..0x677ce78) 40 instructions (`rdis dis 0x677cdb6 40`)

Exact rdis lines:

```
  677cdb6  movzx edx,byte ptr [rbp+0x847]                
  677cdbd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cdc3  nop                                           
  677cdc4  mov eax,[r14+0x6A8]                           
  677cdcb  not eax                                       
  677cdcd  add eax,[r14+0x6B0]                           
  677cdd4  mov [rbp+0x4DA],ax                            
  677cddb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677cde2  mov rax,[rcx]                                 
  677cde5  mov rax,[rax+0x10]                            
  677cde9  mov dl,0x4A                                   
  677cdeb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cdf1  nop                                           
  677cdf2  mov [rbp+0x847],al                            
  677cdf8  mov rdx,[r14+0x590]                           
  677cdff  cmp rdx,[r14+0x598]                           
  677ce06  je 0x677D5D1                                  ; -> loc_677d5d1
  677ce0c  lea rax,[rdx+0x10]                            
  677ce10  mov [rdx],rax                                 
  677ce13  mov rax,0x100000000                           
  677ce1d  mov [rdx+8],rax                               
  677ce21  mov rcx,rdx                                   
  677ce24  mov rdx,r12                                   
  677ce27  call 0x6764990                                ; -> sub_6764990
  677ce2c  add qword ptr [r14+0x590],0x30                
  677ce34  jmp 0x677D5E4                                 ; -> loc_677d5e4
  677ce39  mov rcx,r14                                   
  677ce3c  lea r8,[rbp+0x4A0]                            
  677ce43  call 0x5ABA6D0                                ; -> sub_5aba6d0
  677ce48  nop                                           
  677ce49  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677ce50  mov rax,[rcx]                                 
  677ce53  mov rax,[rax+0x10]                            
  677ce57  movzx edx,byte ptr [rbp+0x847]                
  677ce5e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677ce64  nop                                           
  677ce65  cmp byte ptr [rbp+0x6C8],1                    
  677ce6c  jne short 0x677CEC0                           ; -> loc_677cec0
  677ce6e  mov rcx,[rbp+0x688]                           
  677ce75  test rcx,rcx                                  
```

// Interpretation: Completes Phase 4's final TLS flag read: `movzx edx,byte ptr [rbp+0x847]` → `call qword ptr [0xF99FFA0]` (= sub_eea6040 [V]) → `nop`. State tag/checksum: `eax=[r14+0x6A8]`; `not eax`; `add eax,[r14+0x6B0]`; `mov [rbp+0x4DA]=ax`. TLS flag again → `mov [rbp+0x847],al`. Append slot cursor `rdx=[r14+0x590]`; `cmp [r14+0x598]`; `je loc_677d5d1` (grow); else fast path `lea rax,[rdx+0x10]`; `mov [rdx],rax`; `mov rax,0x100000000`; `mov [rdx+8],rax` (u64 0x100000000 at +8 [I]); `mov rcx,rdx`; `mov rdx,r12`; `call 0x6764990` (sub_6764990 — copy/finalize helper [I]); `add qword ptr [r14+0x590],0x30` (cursor += 0x30 [I]); `jmp loc_677d5e4`. Grow target loc_677ce39: `mov rcx,r14`; `lea r8,[rbp+0x4A0]`; `call 0x5ABA6D0` (sub_5aba6d0 — grow/copy helper [I]); `nop`. loc_677ce49 (Phase 4's jmp target): TLS flag read `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x847]`→`call [0xF99FFA0]`→`nop`; `cmp byte ptr [rbp+0x6C8],1`; `jne short loc_677cec0`; `mov rcx,[rbp+0x688]`; `test rcx,rcx` continues at 0x677ce78 (excluded). Range ends at `test rcx,rcx` (0x677ce75, 3 bytes → next instruction at 0x677ce78).
// tag: [V] all lines; calls [0xF99FFA0]=sub_eea6040 [V] x2, call 0x6764990 [V], call 0x5ABA6D0 [V].

## Phase 2 — [0x677ce78..0x677cf26) 40 instructions (`rdis dis 0x677ce78 40`)

Exact rdis lines:

```
  677ce78  je short 0x677CEC0                            ; -> loc_677cec0
  677ce7a  mov rdx,[rbp+0x698]                           
  677ce81  sub rdx,rcx                                   
  677ce84  cmp rdx,0x1000                                
  677ce8b  jb short 0x677CEA9                            ; -> loc_677cea9
  677ce8d  mov rax,[rcx-8]                               ; R a0-0x8
  677ce91  add rcx,0xFFFFFFFFFFFFFFF8                    
  677ce95  sub rcx,rax                                   
  677ce98  cmp rcx,0x20                                  
  677ce9c  jae 0x677E039                                 ; -> loc_677e039
  677cea2  or rdx,0x27                                   
  677cea6  mov rcx,rax                                   

loc_677cea9:  ; from 677ce8b
  677cea9  call 0xE935700                                ; -> sub_e935700
  677ceae  lea rax,[rbp+0x688]                           
  677ceb5  movups [rax],xmm6                             
  677ceb8  mov qword ptr [rax+0x10],0                    

loc_677cec0:  ; from 677ce78
  677cec0  mov rcx,r12                                   
  677cec3  call 0x6792C20                                ; -> sub_6792c20
  677cec8  mov r14,[rbp+0x780]                           
  677cecf  mov r15d,[rbp+0x788]                          
  677ced6  test r15,r15                                  
  677ced9  je short 0x677CF26                            ; -> loc_677cf26
  677cedb  shl r15,5                                     
  677cedf  xor r13d,r13d                                 
  677cee2  jmp short 0x677CEF9                           ; -> loc_677cef9
  677cee4  nop [rax+rax]                                 ; R ret@6792c20+0x0+idx

loc_677cef0:  ; from 677cf01, 677cf07, 677cf16
  677cef0  add r13,0x20                                  
  677cef4  cmp r15,r13                                   
  677cef7  je short 0x677CF18                            ; -> loc_677cf18

loc_677cef9:  ; from 677cee2
  677cef9  mov rcx,[r14+r13+8]                           
  677cefe  test rcx,rcx                                  
  677cf01  je short 0x677CEF0                            ; -> loc_677cef0
  677cf03  lock dec dword ptr [rcx+0xC]                  
  677cf07  jne short 0x677CEF0                           ; -> loc_677cef0
  677cf09  mov rax,[rcx]                                 
  677cf0c  mov rax,[rax+8]                               
  677cf10  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cf16  jmp short 0x677CEF0                           ; -> loc_677cef0

loc_677cf18:  ; from 677cef7
  677cf18  mov r14,[rbp+0x780]                           
  677cf1f  lea r13,[rbp+0x300]                           
```

// Interpretation: Branch on phase-1 `test rcx,rcx`: `je short loc_677cec0`; else fall-through size check `mov rdx,[rbp+0x698]`; `sub rdx,rcx`; `cmp rdx,0x1000`; `jb short loc_677cea9`; else `mov rax,[rcx-8]`; `add rcx,0xFFFFFFFFFFFFFFF8` (rcx -= 8); `sub rcx,rax`; `cmp rcx,0x20`; `jae loc_677e039`; else `or rdx,0x27`; `mov rcx,rax`. loc_677cea9: `call 0xE935700` (sub_e935700 — shrink/copy helper [I]); `lea rax,[rbp+0x688]`; `movups [rax],xmm6`; `mov qword ptr [rax+0x10],0`. loc_677cec0: `mov rcx,r12`; `call 0x6792C20` (sub_6792c20 — destructor/release helper [I]); `mov r14,[rbp+0x780]`; `mov r15d,[rbp+0x788]`; `test r15,r15`; `je short loc_677cf26`; else `shl r15,5` (r15 *= 32); `xor r13d,r13d`; `jmp short loc_677cef9`. Padding `nop [rax+rax]` at 0x677cee4 ([?]). loc_677cef0 loop tail: `add r13,0x20`; `cmp r15,r13`; `je short loc_677cf18`. loc_677cef9 release loop: `mov rcx,[r14+r13+8]`; `test rcx,rcx`; `je short loc_677cef0`; else `lock dec dword ptr [rcx+0xC]` (refcount-- [I]); `jne short loc_677cef0`; else `mov rax,[rcx]`; `mov rax,[rax+8]`; `call qword ptr [0xF99FFA0]` (= sub_eea6040 — virtual dtor/finalizer [V]); `jmp short loc_677cef0`. loc_677cf18: `mov r14,[rbp+0x780]`; `lea r13,[rbp+0x300]` continues at 0x677cf26 (excluded). Range ends at `lea r13,[rbp+0x300]` (0x677cf1f, 7 bytes → next instruction at 0x677cf26).
// tag: [V] all lines; calls 0xE935700 [V], 0x6792C20 [V], [0xF99FFA0]=sub_eea6040 [V].
