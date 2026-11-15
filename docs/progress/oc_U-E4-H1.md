# U-E4-H1: Chunk builder at 0x6722cb0

Unit: U-E4-H1
Function: sub_6722cb0 (chunk builder at RVA 0x6722cb0; third sibling of builders 0x67762e0 and 0x670b6e0; templates: oc_U-E4-F1.md for 0x67762e0, oc_U-E4-G0.md for 0x670b6e0, both verified)
RVAs: 0x6722cb0 .. (in progress, target 0x800 instructions)
Source: `rdis dis 0x6722cb0 <n>` on Minecraft.Windows.exe 1.26.62.01
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Resume at 0x6723971 (Phase 30 — loc_6723971: al==3 with [rsi+0xD8]!=3 alternate path).

---

## Phase 1 — Prologue (0x6722cb0..0x6722cbc)

Same instruction sequence as F1 Phase 1 (different stack size: 0x958 vs 0x978) and G0 Phase 1 (different stack size: 0x958 vs 0x988).

```
0x6722cb0  push rbp                                      
0x6722cb1  push r15                                      
0x6722cb3  push r14                                      
0x6722cb5  push r13                                      
0x6722cb7  push r12                                      
0x6722cb9  push rsi                                      
0x6722cba  push rdi                                      
0x6722cbb  push rbx                                      
0x6722cbc  sub rsp,0x958                                 
```

Interpretation: Standard function prologue, saving rbp, r15, r14, r13, r12, rsi, rdi, rbx; allocating 0x958 bytes of local stack space.

Callees: none.
Fields: none.

---

## Phase 2 — Frame pointer setup + XMM register saves + stack cookie (0x6722cc3..0x6722d19)

Same instruction sequence as F1 Phase 2 (different offsets: xmm15 at [rbp+0x8C0] vs [rbp+0x8F0], cookie at [rbp+0x828] vs [rbp+0x858], stack size 0x958) and G0 Phase 2 (different offsets: xmm15 at [rbp+0x8C0] vs [rbp+0x8F0], cookie at [rbp+0x828] vs [rbp+0x858]).

```
0x6722cc3  lea rbp,[rsp+0x80]                            
0x6722ccb  movaps [rbp+0x8C0],xmm15                      
0x6722cd3  movaps [rbp+0x8B0],xmm14                      
0x6722cdb  movaps [rbp+0x8A0],xmm13                      
0x6722ce3  movaps [rbp+0x890],xmm12                      
0x6722ceb  movaps [rbp+0x880],xmm11                      
0x6722cf3  movaps [rbp+0x870],xmm10                      
0x6722cfb  movaps [rbp+0x860],xmm9                       
0x6722d03  movaps [rbp+0x850],xmm8                       
0x6722d0b  movaps [rbp+0x840],xmm7                       
0x6722d12  movaps [rbp+0x830],xmm6                       
0x6722d19  mov qword ptr [rbp+0x828],0xFFFFFFFFFFFFFFFE  
```

Interpretation: rbp = rsp+0x80 (frame base). Save xmm15 down to xmm6 at [rbp+0x8C0]..[rbp+0x830]. Store 0xFFFFFFFFFFFFFFFE at [rbp+0x828] (stack cookie/sentinel).

Callees: none.
Fields written: [rbp+0x8C0] xmm15, [rbp+0x8B0] xmm14, [rbp+0x8A0] xmm13, [rbp+0x890] xmm12, [rbp+0x880] xmm11, [rbp+0x870] xmm10, [rbp+0x860] xmm9, [rbp+0x850] xmm8, [rbp+0x840] xmm7, [rbp+0x830] xmm6, [rbp+0x828] = 0xFFFFFFFFFFFFFFFE.

---

## Phase 3 — Argument save + TLS/cookie read (0x6722d24..0x6722d4e)

Same instruction sequence as F1 Phase 3 (different registers: G0/H1 use rsi=r9 for arg 4 vs F1 rdi=r8; different offsets: [rbp+0x808]=rdx vs [rbp+0x838], [rbp+0x748]=rcx vs [rbp+0x778], result at [rbp+0x817] vs [rbp+0x847]).

```
0x6722d24  mov rsi,r9                                    
0x6722d27  mov ebx,r8d                                   
0x6722d2a  mov [rbp+0x808],rdx                           
0x6722d31  mov [rbp+0x748],rcx                           
0x6722d38  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6722d3f  mov rax,[rcx]                                 
0x6722d42  mov rax,[rax+0x10]                            
0x6722d46  mov dl,0x3E                                   
0x6722d48  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6722d4e  mov [rbp+0x817],al                            
```

Interpretation: Save incoming args: rsi=r9 (vec3*), ebx=r8d, [rbp+0x808]=rdx (BuilderSpan*), [rbp+0x748]=rcx (FrameCtx*). Load TLS base from [0x1233E1B0], deref to get TEB, read [rax+0x10], call via [0xF99FFA0] (sub_eea6040) with dl=0x3E, store result al at [rbp+0x817].

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10]. Fields written: [rbp+0x808], [rbp+0x748], [rbp+0x817].

---

## Phase 4 — Data section loads + GS cookie range check (0x6722d54..0x6722d73)

Same instruction sequence as F1 Phase 4 (different data addresses: [0x129FB3A8] vs [0x129FB398], jump target 0x672A350 vs 0x6713B50) and G0 Phase 4 (different data addresses: [0x129FB3A8] vs [0x129FB398], jump target 0x672A350 vs 0x6713B50).

```
0x6722d54  mov eax,[0x129FB3A8]                          ; [data_129fb3a8]
0x6722d5a  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6722d60  mov rdx,gs:[0x58]                             
0x6722d69  mov rcx,[rdx+rcx*8]                           
0x6722d6d  cmp eax,[rcx+4]                               
0x6722d73  jg 0x672A350                                  ; -> sub_672a350
```

Interpretation: Load two globals [0x129FB3A8] and [0x128767C8]. Read gs:[0x58] (TEB), use ecx as index into an array at [rdx+rcx*8], compare eax against [rcx+4]. If greater, jump to 0x672A350 (error handler).

Callees: none.
Fields read: [0x129FB3A8], [0x128767C8], gs:[0x58], [rdx+rcx*8], [rcx+4].

---

## Phase 5 — Vector init + search table setup (0x6722d79..0x6722dc0)

Same instruction sequence as F1 Phase 5 (different offsets: [rbp+0x948] vs [rbp+0x970], [rbp+0x368] vs [rbp+0x2C8], [rbp+0x560] vs [rbp+0x580], [rbp+0x370] vs [rbp+0x120], r13 vs r12) and G0 Phase 5 (different offsets: [rbp+0x948] vs [rbp+0x970], [rbp+0x368] vs [rbp+0x2C8], [rbp+0x560] vs [rbp+0x580], [rbp+0x370] vs [rbp+0x120]).

```
0x6722d79  mov rcx,[rbp+0x948]                           
0x6722d80  lea rax,[rcx+8]                               
0x6722d84  mov [rbp+0x368],rax                           
0x6722d8b  xorps xmm0,xmm0                               
0x6722d8e  movaps [rbp+0x560],xmm0                       
0x6722d95  mov qword ptr [rbp+0x370],1                   
0x6722da0  lea rax,[rbp+0x560]                           
0x6722da7  mov [rbp+0x378],rax                           
0x6722dae  mov rax,[rcx+0x38]                            
0x6722db2  movzx r8d,word ptr [rcx+0x42]                 
0x6722db7  mov edx,r8d                                   
0x6722dba  shl edx,4                                     
0x6722dbd  mov rcx,rax                                   
0x6722dc0  test r8d,r8d                                  
```

Interpretation: rcx = [rbp+0x948] (search-table object). rax = rcx+8 stored at [rbp+0x368]. Zero xmm0, store at [rbp+0x560]. Set [rbp+0x370]=1 (u64), rax = &[rbp+0x560], [rbp+0x378]=rax. rax = [rcx+0x38] (search table base). r8d = word [rcx+0x42] (entry count). edx = r8d << 4 (stride 0x10). rcx = rax. Falls through to Phase 6 (test r8d,r8d at 0x6722dc0).

Callees: none.
Fields read: [rbp+0x948], [rcx+0x38], [rcx+0x42]. Fields written: [rbp+0x368], [rbp+0x560], [rbp+0x370], [rbp+0x378].

---

## Phase 6 — Search loop (0x6722dc0..0x6722df3)

Same instruction sequence as F1 Phase 6 (different data address: [0x129FB3A0] vs [0x129FB390], jump targets 0x6722DF5/0x6722E2D vs 0x670B825/0x670B85D) and G0 Phase 6 (same differences as F1).

```
0x6722dc0  test r8d,r8d                                  
0x6722dc3  je short 0x6722DF5                            ; -> loc_6722df5
0x6722dc5  mov r8,[0x129FB3A0]                           ; [data_129fb3a0]
0x6722dcc  mov r9,rdx                                    
0x6722dcf  mov rcx,rax                                   
0x6722dd2  nop [rax+rax]                                 
0x6722de0  mov r10,[rcx]                                 
0x6722de3  cmp [r10+0x28],r8                             
0x6722de7  je short 0x6722DF5                            ; -> loc_6722df5
0x6722de9  add rcx,0x10                                  
0x6722ded  add r9,0xFFFFFFFFFFFFFFF0                     
0x6722df1  jne short 0x6722DE0                           ; -> loc_6722de0
0x6722df3  jmp short 0x6722E2D                           ; -> loc_6722e2d
```

Interpretation: If count==0 jump to found path. Otherwise: r8 = [0x129FB3A0] (search key). r9 = rdx (remaining count, decremented by 0x10 each iteration). rcx = rax (table base). Loop: r10 = [rcx] (entry ptr), compare [r10+0x28] with r8. If equal, jump to found path. Otherwise advance rcx by 0x10, decrement r9 by 0x10, continue if not zero. If exhausted, jump to notfound path.

Callees: none.
Fields read: [0x129FB3A0], [rcx], [r10+0x28]. Fields written: none.

---

## Phase 7 — Found path: call 0x5679DB0 (0x6722df5..0x6722e2b)

Same instruction sequence as F1 Phase 7 (different offsets: [rbp+0x7F8] vs [rbp+0x828], [rbp+0x7FA] vs [rbp+0x82A], [rbp+0x370] vs [rbp+0x120], [rbp+0x368] vs [rbp+0x2C8]) and G0 Phase 7 (same differences as F1).

```
0x6722df5  add rdx,rax                                   
0x6722df8  cmp rcx,rdx                                   
0x6722dfb  jae short 0x6722E2D                           ; -> loc_6722e2d
0x6722dfd  sub ecx,eax                                   
0x6722dff  shr ecx,4                                     
0x6722e02  mov [rbp+0x7F8],cx                            
0x6722e09  mov byte ptr [rbp+0x7FA],1                    
0x6722e10  lea rdx,[rbp+0x7F8]                           
0x6722e17  lea r8,[rbp+0x370]                            
0x6722e1e  mov rcx,[rbp+0x368]                           
0x6722e25  call 0x5679DB0                                ; -> sub_5679db0
0x6722e2a  nop                                           
0x6722e2b  jmp short 0x6722E34                           ; -> loc_6722e34
```

Interpretation: rdx += rax (end of table). If rcx >= rdx, go to notfound. Otherwise compute index = (rcx - rax) >> 4 (entry index), store cx at [rbp+0x7F8], set flag byte [rbp+0x7FA]=1. Call 0x5679DB0(rcx=[rbp+0x368], rdx=&[rbp+0x7F8], r8=&[rbp+0x370]). Jump to common code.

Callees: 0x5679DB0 (sub_5679db0).
Fields read: [rbp+0x368]. Fields written: [rbp+0x7F8], [rbp+0x7FA].

---

## Phase 8 — Not found path + call 0xE86B370 (0x6722e2d..0x6722e62)

Same instruction sequence as F1 Phase 8 (different offsets: [rbp+0x7FA] vs [rbp+0x82A], [rbp+0x948] vs [rbp+0x970], [rbp+0x368] vs [rbp+0x2C8], [rbp+0x540] vs [rbp+0x300]) and G0 Phase 8 (same differences as F1).

```
0x6722e2d  mov byte ptr [rbp+0x7FA],0                    
0x6722e34  mov rdx,[rbp+0x948]                           
0x6722e3b  mov rax,[rdx]                                 
0x6722e3e  mov [rbp-0x40],rax                            
0x6722e42  lea rcx,[rbp-0x38]                            
0x6722e46  mov r8,[rdx+8]                                
0x6722e4a  mov rdx,[rbp+0x368]                           
0x6722e51  call 0xE86B370                                ; -> sub_e86b370
0x6722e56  nop                                           
0x6722e57  mov qword ptr [rbp+0x40],0                    
0x6722e5f  xorps xmm6,xmm6                               
0x6722e62  movaps [rbp+0x540],xmm6                       
```

Interpretation: Not found: set [rbp+0x7FA]=0. Common: rdx = [rbp+0x948], rax = [rdx] stored at [rbp-0x40]. lea rcx = [rbp-0x38]. r8 = [rdx+8]. rdx = [rbp+0x368]. Call 0xE86B370. Then [rbp+0x40]=0, xmm6=0, store xmm6 at [rbp+0x540].

Callees: 0xE86B370 (sub_e86b370).
Fields read: [rbp+0x948], [rdx], [rdx+8], [rbp+0x368]. Fields written: [rbp-0x40], [rbp+0x40], [rbp+0x540].

---

## Phase 9 — Byte branch on [rsi+0xD8] + al==3 path setup (0x6722e69..0x6722ea3)

Same instruction sequence as F1 Phase 9 (different offsets: [rbp+0x754] vs [rbp+0x784], [rbp+0x815] vs [rbp+0x846], [rbp+0x7FC] vs [rbp+0x82C], [rbp+0x800] vs [rbp+0x830]; H1 uses rsi instead of rdi/rsi for the second arg) and G0 Phase 9 (same differences as F1).

```
0x6722e69  movzx eax,byte ptr [rsi+0xD8]                 
0x6722e70  mov dword ptr [rbp+0x754],0                   
0x6722e7a  mov [rbp+0x815],al                            
0x6722e80  cmp al,3                                      
0x6722e82  jne 0x6722FDC                                 ; -> loc_6722fdc
0x6722e88  cmp byte ptr [rsi+0xB8],0                     
0x6722e8f  mov dword ptr [rbp+0x7FC],0                   
0x6722e99  mov dword ptr [rbp+0x800],0                   
0x6722ea3  je 0x6722FF0                                  ; -> loc_6722ff0
```

Interpretation: al = byte [rsi+0xD8]. [rbp+0x754]=0. [rbp+0x815]=al. If al != 3, jump to loc_6722FDC. If al == 3: check byte [rsi+0xB8]. Zero [rbp+0x7FC] and [rbp+0x800]. If [rsi+0xB8] == 0, jump to loc_6722FF0.

Callees: none.
Fields read: [rsi+0xD8], [rsi+0xB8]. Fields written: [rbp+0x754], [rbp+0x815], [rbp+0x7FC], [rbp+0x800].

---

## Phase 10 — al==3 with [rsi+0xB8]!=0: load u32 pair + allocator call (0x6722ea9..0x6722eec)

Same instruction sequence as F1 Phase 10, different displacements/registers (H1 stores [rsi+0xC0] at [rbp+0x800] vs F1 [rbp+0x824], [rsi+0xC4] at [rbp+0x7FC] vs [rbp+0x820]; H1 uses [rbp+0x808] vs F1 [rbp+0x828]; H1 keeps alloc pointer in r15 vs F1 r14; je target 0x672A315 vs 0x6713B15) and G0 Phase 10 (same differences as F1).

```
0x6722ea9  mov eax,[rsi+0xC0]                            
0x6722eaf  mov [rbp+0x800],eax                           
0x6722eb5  mov eax,[rsi+0xC4]                            
0x6722ebb  mov [rbp+0x7FC],eax                           
0x6722ec1  mov rax,[rbp+0x808]                           
0x6722ec8  mov r14,[rax+0x48]                            
0x6722ecc  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6722ed3  mov rax,[rcx]                                 
0x6722ed6  mov rax,[rax+8]                               
0x6722eda  mov edx,0x30                                  
0x6722edf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6722ee5  nop                                           
0x6722ee6  mov r15,rax                                   
0x6722ee9  test rax,rax                                  
0x6722eec  je 0x672A315                                  ; -> sub_672a315
```

Interpretation: eax = [rsi+0xC0] stored at [rbp+0x800]. eax = [rsi+0xC4] stored at [rbp+0x7FC]. rax = [rbp+0x808], r14 = [rax+0x48]. rcx = [0x1233E1A8] (allocator vtable). rax = [rcx], rax = [rax+8] (allocate method). edx = 0x30 (size). Call via [0xF99FFA0]. rax = result stored in r15. If null, jump to 0x672A315 (null handler).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, allocator vcall+8).
Fields read: [rsi+0xC0], [rsi+0xC4], [rbp+0x808], [rax+0x48], [0x1233E1A8], [rcx], [rax+8]. Fields written: [rbp+0x800], [rbp+0x7FC].

---

## Phase 11 — Initialize allocated 0x30-byte buffer + call 0x5AB9970 (0x6722ef2..0x6722f6d)

Same instruction sequence as F1 Phase 11, different offsets (H1 [rbp+0x560] vs [rbp+0x580], [rbp+0x564] vs [rbp+0x584], [rbp+0x568] vs [rbp+0x588], [rbp+0x578] vs [rbp+0x598], [rbp+0x580] vs [rbp+0x5A0], [rbp+0x588] vs [rbp+0x5A8], [rbp+0x590] vs [rbp+0x5B0]; H1 rcx=r14 vs F1 rcx=rsi; call target 0x5AB9970 same) and G0 Phase 11 (same differences as F1).

```
0x6722ef2  movups xmm0,[0xF5C6AE8]                       ; [data_f5c6ae8] "eCapture texture"
0x6722ef9  movups [r15+0x10],xmm0                        
0x6722efe  movups xmm0,[0xF5C6AD8]                       ; [data_f5c6ad8] "UIStructureVolumeCapture texture"
0x6722f05  movups [r15],xmm0                             
0x6722f09  mov byte ptr [r15+0x20],0                     
0x6722f0e  mov eax,[rbp+0x800]                           
0x6722f14  mov [rbp+0x560],eax                           
0x6722f1a  mov eax,[rbp+0x7FC]                           
0x6722f20  mov [rbp+0x564],eax                           
0x6722f26  movaps xmm0,[0xF275E70]                       ; [data_f275e70]
0x6722f2d  movups [rbp+0x568],xmm0                       
0x6722f34  mov [rbp+0x578],r15                           
0x6722f3b  mov qword ptr [rbp+0x580],0                   
0x6722f46  mov qword ptr [rbp+0x588],0x20                
0x6722f51  mov qword ptr [rbp+0x590],0x2F                
0x6722f5c  lea rdx,[rbp+0x370]                           
0x6722f63  lea r8,[rbp+0x560]                            
0x6722f6a  mov rcx,r14                                   
0x6722f6d  call 0x5AB9970                                ; -> sub_5ab9970
```

Interpretation: Copy 16 bytes from [0xF5C6AE8] to [r15+0x10], 16 bytes from [0xF5C6AD8] to [r15]. [r15+0x20]=0. Store [rbp+0x800] at [rbp+0x560], [rbp+0x7FC] at [rbp+0x564]. Copy xmm from [0xF275E70] to [rbp+0x568]. [rbp+0x578]=r15 (pointer to new buffer). [rbp+0x580]=0 (size). [rbp+0x588]=0x20 (capacity). [rbp+0x590]=0x2F. Call 0x5AB9970(rcx=r14, rdx=&[rbp+0x370], r8=&[rbp+0x560]).

Callees: 0x5AB9970 (sub_5ab9970).
Fields read: [0xF5C6AE8], [0xF5C6AD8], [rbp+0x800], [rbp+0x7FC], [0xF275E70], [rbp+0x370], [rbp+0x560]. Fields written: [r15+0x10], [r15], [r15+0x20], [rbp+0x560], [rbp+0x564], [rbp+0x568], [rbp+0x578], [rbp+0x580], [rbp+0x588], [rbp+0x590].

---

## Phase 12 — After call 0x5AB9970: reset xmm + string buffer cleanup (0x6722f73..0x6722fda)

Same instruction sequence as F1 Phase 12 (different offsets: [rbp+0x370] vs [rbp+0x120], [rbp+0x540] vs [rbp+0x300], [rbp+0x590] vs [rbp+0x5B0], [rbp+0x578] vs [rbp+0x598], [rbp+0x754] vs [rbp+0x784]; jump targets 0x6722FD0/0x6722FCB vs F1 0x670BA00/0x670B9FB) and G0 Phase 12 (same differences as F1).

```
0x6722f72  nop                                           
0x6722f73  movaps xmm0,[rbp+0x370]                       
0x6722f7a  xorps xmm1,xmm1                               
0x6722f7d  movaps [rbp+0x370],xmm1                       
0x6722f84  movaps [rbp+0x540],xmm0                       
0x6722f8b  mov rax,[rbp+0x590]                           
0x6722f92  cmp rax,0x10                                  
0x6722f96  jb short 0x6722FD0                            ; -> loc_6722fd0
0x6722f98  mov rcx,[rbp+0x578]                           
0x6722f9f  lea rdx,[rax+1]                               
0x6722fa3  cmp rdx,0x1000                                
0x6722faa  jb short 0x6722FCB                            ; -> loc_6722fcb
0x6722fac  mov r8,[rcx-8]                                
0x6722fb0  add rcx,0xFFFFFFFFFFFFFFF8                    
0x6722fb4  sub rcx,r8                                    
0x6722fb7  cmp rcx,0x20                                  
0x6722fbb  jae 0x672A337                                 ; -> sub_672a337
0x6722fc1  add rax,0x28                                  
0x6722fc5  mov rdx,rax                                   
0x6722fc8  mov rcx,r8                                    
0x6722fcb  call 0xE935700                                ; -> sub_e935700
0x6722fd0  mov dword ptr [rbp+0x754],0x1C                
0x6722fda  jmp short 0x6722FF0                           ; -> loc_6722ff0
```

Interpretation: xmm0 = [rbp+0x370]. xmm1 = 0. [rbp+0x370]=0. [rbp+0x540]=xmm0 (save previous value). rax = [rbp+0x590]. If rax < 0x10, skip cleanup. Otherwise: rcx = [rbp+0x578] (buffer ptr), rdx = rax+1, if rdx >= 0x1000: r8 = [rcx-8], rcx -= 8, sub rcx, r8 (compute allocation size), if >= 0x20 jump to 0x672A337. rax += 0x28, rdx = rax, rcx = r8. Call 0xE935700 (likely free). Then [rbp+0x754] = 0x1C and jump to loc_6722FF0.

Callees: 0xE935700 (sub_e935700).
Fields read: [rbp+0x370], [rbp+0x590], [rbp+0x578], [rcx-8]. Fields written: [rbp+0x370], [rbp+0x540], [rbp+0x754].

---

## Phase 13 — al!=3 path + loop entry computation (0x6722fdc..0x67230a8)

DIFFERENT from F1 Phase 13. F1 Phase 13 computes a boolean flag from two comparisons and uses rdi as the loop iterator; H1 uses rbx directly as the loop iterator, stores a dereferenced qword at [rbp+0x118], and computes [rbp+0x807] = byte [rbp+0x958] & byte [rbp+0x950]. The loop-end pointer is at [rbp+0x100] in both. Pointer setup differs: H1 rbx=&[rbp+0x450] (F1 rbx=&[rbp+0x1F0]), H1 rdi=&[rbp+0xA0]/r15=&[rbp+0x110] (F1 r14=&[rbp+0xA0]/r13=&[rbp+0x300]).

```
0x6722fdc  mov dword ptr [rbp+0x7FC],0                   
0x6722fe6  mov dword ptr [rbp+0x800],0                   
0x6722ff0  movzx ecx,byte ptr [rbp+0x958]                
0x6722ff7  mov r12,[rsi+0x40]                            
0x6722ffb  mov rax,[rsi+0x48]                            
0x6722fff  cmp qword ptr [rax],1                         
0x6723003  sete al                                       
0x6723006  cmp ebx,1                                     
0x6723009  sete dl                                       
0x672300c  and dl,al                                     
0x672300e  mov [rbp+0x816],dl                            
0x6723014  imul rax,[rsi+0x38],0x58                      
0x6723019  add rax,r12                                   
0x672301c  mov [rbp+0x100],rax                           
0x6723023  and cl,[rbp+0x950]                            
0x6723029  mov [rbp+0x807],cl                            
0x672302f  lea rbx,[rbp+0x450]                           
0x6723036  mov rax,[rbp+0x748]                           
0x672303d  add rax,0x470                                 
0x6723043  mov [rbp+0x758],rax                           
0x672304a  lea r13,[rbp+0x1F0]                           
0x6723051  movss xmm7,[0xEEC8060]                        ; [data_eec8060]
0x6723059  movsd xmm8,[0xEFD32F0]                        ; [data_efd32f0]
0x6723062  movaps xmm9,[0xF0A4080]                       ; [data_f0a4080]
0x672306a  movss xmm10,[0xEEC8060]                       ; [data_eec8060]
0x6723073  movsd xmm11,[0xEFD32F0]                       ; [data_efd32f0]
0x672307c  movss xmm13,[0xEFC13A4]                       ; [data_efc13a4] = sub_1000000
0x6723085  movaps xmm14,[0xF0B8740]                      ; [data_f0b8740] = sub_1000000
0x672308d  movzx eax,byte ptr [rbp+0x960]                
0x6723094  mov [rbp+0x79C],eax                           
0x672309a  lea rdi,[rbp+0xA0]                            
0x67230a1  lea r15,[rbp+0x110]                           
0x67230a8  jmp short 0x67230C2                           ; -> loc_67230c2
```

Interpretation: [rbp+0x7FC]=0, [rbp+0x800]=0. ecx = byte [rbp+0x958]. r12 = [rsi+0x40] (loop iterator start). rax = [rsi+0x48], cmp qword [rax],1 -> sete al. cmp ebx,1 -> sete dl. and dl,al -> [rbp+0x816] (combined flag). rax = [rsi+0x38] * 0x58 + r12 -> [rbp+0x100] (loop end). cl = byte [rbp+0x958] & [rbp+0x950] -> [rbp+0x807]. rbx = &[rbp+0x450] (loop iterator). rax = [rbp+0x748] + 0x470 -> [rbp+0x758] (loop start). r13 = &[rbp+0x1F0]. Load constants into xmm7-xmm14 from data sections. eax = byte [rbp+0x960] -> [rbp+0x79C]. rdi = &[rbp+0xA0], r15 = &[rbp+0x110]. Jump to loop head.

Callees: none.
Fields read: [rbp+0x958], [rsi+0x40], [rsi+0x48], [rax], [rsi+0x38], [rbp+0x950], [rbp+0x748], [rbp+0x960]. Fields written: [rbp+0x7FC], [rbp+0x800], [rbp+0x816], [rbp+0x100], [rbp+0x807], [rbp+0x758], [rbp+0x79C].

---

## Phase 14 — Loop head + per-entry dispatch (0x67230aa..0x67230f0)

Same instruction sequence as F1 Phase 14 (H1 uses rbx as iterator and 0x672A25A as exit target vs F1 rdi and 0x677DF5C; H1 re-loads rdi=&[rbp+0xA0] and r15=&[rbp+0x110] on back-edge vs F1 r14/r13).

```
0x67230aa  nop [rax+rax]                                 
0x67230b0  lea rdi,[rbp+0xA0]                            
0x67230b7  lea r15,[rbp+0x110]                           
0x67230be  add rbx,0x58                                  
0x67230c2  cmp rbx,[rbp+0x100]                           
0x67230c9  je 0x672A25A                                  ; -> sub_672a25a
0x67230cf  movzx eax,byte ptr [rbx+0x28]                 
0x67230d5  test eax,eax                                  
0x67230d7  je short 0x67230F0                            ; -> loc_67230f0
0x67230d9  cmp eax,1                                     
0x67230dc  jne 0x672A325                                 ; -> sub_672a325
0x67230e2  lea rax,[rbx+0x18]                            
0x67230e7  cmp qword ptr [rax],0                         
0x67230eb  jne short 0x67230FB                           ; -> loc_67230fb
0x67230ed  jmp short 0x67230BE                           ; -> loc_67230be
0x67230ef  nop                                           
0x67230f0  lea rax,[rbx+0x10]                            
0x67230f5  cmp qword ptr [rax],0                         
```

Interpretation: Loop back edge: rdi=&[rbp+0xA0], r15=&[rbp+0x110]. Advance rbx by 0x58 (next entry). If rbx == [rbp+0x100] (end), exit to 0x672A25A. Dispatch: eax = byte [rbx+0x28]. If 0, jump to loc_67230F0 (check [rbx+0x10]). If !=1, jump to 0x672A325 (error). If ==1: rax = &[rbx+0x18], if [rax] != 0 go to body; else skip to loop increment. At loc_67230F0: rax = &[rbx+0x10], if [rax] == 0 skip.

Callees: none.
Fields read: [rbx+0x28], [rbx+0x18], [rbx+0x10], [rbp+0x100]. Fields written: none.

---

## Phase 15 — Per-entry dispatch + xmm15 load (0x67230f5..0x6723102)

Same instruction sequence as F1 Phase 15 (H1 uses rbx as iterator vs F1 rdi; jump targets 0x672A325/0x67230FB/0x67230BE vs F1 0x677E027/0x677670A/0x6776700).

```
0x67230f5  cmp qword ptr [rax],0                         
0x67230f9  je short 0x67230BE                            ; -> loc_67230be
0x67230fb  movsd xmm15,[rbx+0x3C]                        
0x6723102  movsd [rbp+0x530],xmm15                       
```

Interpretation: At loc_67230F0: rax = &[rbx+0x10], if [rax] == 0 skip to loop increment. Body: xmm15 = [rbx+0x3C] (double), store at [rbp+0x530].

Callees: none.
Fields read: [rax], [rbx+0x3C]. Fields written: [rbp+0x530].

---

## Phase 16 — xmm math + first call 0xAA6580 (0x672310b..0x672319c)

Same instruction sequence as F1 Phase 16 (same code; call target 0xAA6580 same).

```
0x672310b  mov dword ptr [rbp+0x560],0x3F800000          
0x6723115  lea rax,[rbp+0x564]                           
0x672311c  movups [rax],xmm6                             
0x672311f  mov dword ptr [rbp+0x574],0x3F800000          
0x6723129  movups [rax+0x14],xmm6                        
0x672312d  movaps xmm0,xmm15                             
0x6723131  mulps xmm0,xmm6                               
0x6723134  movaps xmm1,xmm0                              
0x6723137  shufps xmm1,xmm0,0xE1                         
0x672313b  addps xmm1,xmm15                              
0x672313f  movss xmm12,[rbx+0x44]                        
0x6723146  movss [rbp+0x538],xmm12                       
0x672314f  movaps xmm2,xmm12                             
0x6723153  shufps xmm2,xmm12,0                           
0x6723158  mulps xmm2,xmm7                               
0x672315b  movaps xmm3,xmm0                              
0x672315e  shufps xmm3,xmm0,0x55                         
0x6723162  unpcklps xmm0,xmm0                            
0x6723165  addps xmm0,xmm3                               
0x6723168  addps xmm0,xmm2                               
0x672316b  addps xmm0,xmm8                               
0x672316f  shufps xmm2,xmm2,0x55                         
0x6723173  addps xmm2,xmm1                               
0x6723176  movaps xmm1,xmm9                              
0x672317a  movlhps xmm1,xmm2                             
0x672317d  addps xmm1,xmm7                               
0x6723180  movups [rbp+0x588],xmm1                       
0x6723187  movlps [rbp+0x598],xmm0                       
0x672318e  mov rcx,rdi                                   
0x6723191  lea rdx,[rsi+0x78]                            
0x6723195  lea r8,[rbp+0x560]                            
0x672319c  call 0xAA6580                                 ; -> sub_aa6580
```

Interpretation: [rbp+0x560]=0x3F800000 (1.0f). [rbp+0x564]=0 (xmm6). [rbp+0x574]=0x3F800000 (1.0f). [rbp+0x578]=0 (xmm6). Complex SIMD vector math combining xmm15 (double from entry), xmm6 (zero), constants from xmm7-xmm14, and [rbx+0x44]. Then call 0xAA6580(rcx=rdi=&[rbp+0xA0], rdx=[rsi+0x78], r8=&[rbp+0x560]).

Callees: 0xAA6580 (sub_aa6580).
Fields read: [rbx+0x44]. Fields written: [rbp+0x560], [rbp+0x564], [rbp+0x574], [rbp+0x578], [rbp+0x588], [rbp+0x598].

---

## Phase 17 — Second call 0xAA6580 + store results (0x67231a2..0x672323e)

Same instruction sequence as F1 Phase 17 (same code; call target 0xAA6580 same).

```
0x67231a1  nop                                           
0x67231a2  movss xmm0,[rbx+0x48]                         
0x67231a9  ucomiss xmm0,xmm10                            
0x67231ad  jne short 0x67231B5                           ; -> loc_67231b5
0x67231af  jnp 0x6723245                                 ; -> loc_6723245
0x67231b5  movaps xmm1,xmm0                              
0x67231b8  shufps xmm1,xmm0,0                            
0x67231bc  mulps xmm1,xmm7                               
0x67231bf  movss [rbp+0x560],xmm0                        
0x67231c7  movq xmm2,xmm1                                
0x67231cb  shufps xmm1,xmm1,0x55                         
0x67231cf  movups [rbp+0x564],xmm1                       
0x67231d6  movss [rbp+0x574],xmm0                        
0x67231de  movups [rbp+0x578],xmm1                       
0x67231e5  movdqu [rbp+0x588],xmm2                       
0x67231ed  movsd [rbp+0x598],xmm11                       
0x67231f6  lea rcx,[rbp+0x370]                           
0x67231fd  mov rdx,rdi                                   
0x6723200  lea r8,[rbp+0x560]                            
0x6723207  call 0xAA6580                                 ; -> sub_aa6580
0x672320c  nop                                           
0x672320d  movaps xmm0,[rbp+0x370]                       
0x6723214  movaps xmm1,[rbp+0x380]                       
0x672321b  movaps xmm2,[rbp+0x390]                       
0x6723222  movaps xmm3,[rbp+0x3A0]                       
0x6723229  movaps [rbp+0xA0],xmm0                        
0x6723230  movaps [rbp+0xB0],xmm1                        
0x6723237  movaps [rbp+0xC0],xmm2                        
0x672323e  movaps [rbp+0xD0],xmm3                        
```

Interpretation: xmm0 = [rbx+0x48]. ucomiss xmm0, xmm10. If not equal or not ordered: xmm1 = broadcast xmm0, mulps xmm1, xmm7. Store xmm0 at [rbp+0x560], xmm1 at [rbp+0x564], [rbp+0x574], xmm2 (movq from xmm1) at [rbp+0x578]/[rbp+0x588], xmm11 at [rbp+0x598]. Then call 0xAA6580(rcx=&[rbp+0x370], rdx=rdi=&[rbp+0xA0], r8=&[rbp+0x560]). Finally store xmm0-xmm3 from [rbp+0x370]..[rbp+0x3A0] to [rbp+0xA0]..[rbp+0xD0].

Callees: 0xAA6580 (sub_aa6580).
Fields read: [rbx+0x48], [rbp+0x370], [rbp+0x380], [rbp+0x390], [rbp+0x3A0]. Fields written: [rbp+0x560], [rbp+0x564], [rbp+0x574], [rbp+0x578], [rbp+0x588], [rbp+0x598], [rbp+0xA0], [rbp+0xB0], [rbp+0xC0], [rbp+0xD0].

---

## Phase 18 — Call 0x678C4C0 + found path check (0x6723245..0x67232c8)

Same instruction sequence as F1 Phase 18 (same code; call target 0x678C4C0 same).

```
0x6723245  mov rax,[rbp+0x808]                           
0x672324c  mov rdx,[rax]                                 
0x672324f  mov [rsp+0x20],r12                            
0x6723254  lea rcx,[rbp+0x48]                            
0x6723258  mov r8,[rbp+0x940]                            
0x672325f  mov r9,[rbp+0x948]                            
0x6723266  call 0x678C4C0                                ; -> sub_678c4c0
0x672326b  nop                                           
0x672326c  lea rax,[rbp-0x40]                            
0x6723270  mov [rbp+0x108],rax                           
0x6723277  cmp byte ptr [rbp+0x7FA],1                    
0x672327e  jne short 0x67232DC                           ; -> loc_67232dc
0x6723280  movss xmm0,[r12+0x4C]                         
0x6723287  xorps xmm1,xmm1                               
0x672328a  ucomiss xmm0,xmm1                             
0x672328d  jbe short 0x67232DC                           ; -> loc_67232dc
0x672328f  shufps xmm0,xmm0,0                            
0x6723293  movaps [rbp+0x560],xmm0                       
0x672329a  mov qword ptr [rbp+0x370],1                   
0x67232a5  lea rax,[rbp+0x560]                           
0x67232ac  mov [rbp+0x378],rax                           
0x67232b3  mov rcx,[rbp+0x368]                           
0x67232ba  lea rdx,[rbp+0x7F8]                           
0x67232c1  lea r8,[rbp+0x370]                            
0x67232c8  call 0x5679DB0                                ; -> sub_5679db0
```

Interpretation: rax = [rbp+0x808], rdx = [rax]. [rsp+0x20]=r12 (loop iterator saved). Call 0x678C4C0(rcx=&[rbp+0x48], r8=[rbp+0x940], r9=[rbp+0x948]). lea rax = [rbp-0x40], store at [rbp+0x108]. If [rbp+0x7FA] != 1 (found flag), skip. Otherwise: xmm0 = [r12+0x4C], if <= 0 skip. xmm0 broadcast, [rbp+0x560]=xmm0, [rbp+0x370]=1, rax=&[rbp+0x560], [rbp+0x378]=rax. Call 0x5679DB0(rcx=[rbp+0x368], rdx=&[rbp+0x7F8], r8=&[rbp+0x370]).

Callees: 0x678C4C0 (sub_678c4c0), 0x5679DB0 (sub_5679db0).
Fields read: [rbp+0x808], [rax], [rbp+0x7FA], [r12+0x4C], [rbp+0x368], [rbp+0x7F8]. Fields written: [rsp+0x20], [rbp+0x108], [rbp+0x560], [rbp+0x370], [rbp+0x378].

---

## Phase 19 — After call 0x5679DB0: struct copy setup (0x67232cd..0x67232ea)

Same instruction sequence as F1 Phase 19 (same code).

```
0x67232cd  nop                                           
0x67232ce  mov rax,[rbp+0x948]                           
0x67232d5  mov [rbp+0x108],rax                           
0x67232dc  mov rax,[rbp+0x968]                           
0x67232e3  mov [rbp+0x510],rax                           
0x67232ea  mov [rbp+0x518],rdi
```

Interpretation: After second call 0x5679DB0: rax = [rbp+0x948], store at [rbp+0x108]. rax = [rbp+0x968], store at [rbp+0x510]. rdi stored at [rbp+0x518]. End of chunk 1 (300 instructions, last RVA 0x67232ea).

Callees: none.
Fields read: [rbp+0x948], [rbp+0x968]. Fields written: [rbp+0x108], [rbp+0x510], [rbp+0x518].

## NEXT
Resume at 0x67232f1 (Phase 20 — struct copy + dispatch).

---

## Phase 20 — Struct copy + dispatch (0x67232f1..0x6723322)

Same instruction sequence as F1 Phase 20 (same code pattern; different offsets: [rbp+0x520] vs [rbp+0x510], [rbp+0x528] vs [rbp+0x518], [rbp+0x807] vs [rbp+0x837]).

```
0x67232f1  lea rax,[rbp+0x48]                            
0x67232f5  mov [rbp+0x520],rax                           
0x67232fc  lea rax,[rbp+0x108]                           
0x6723303  mov [rbp+0x528],rax                           
0x672330a  movzx eax,byte ptr [rsi+0xB8]                 
0x6723311  cmp byte ptr [rbp+0x807],0                    
0x6723318  je short 0x6723380                            ; -> loc_6723380
0x672331a  test al,al                                    
0x672331c  je 0x67233D9                                  ; -> loc_67233d9
0x6723322  mov rdx,[rbp+0x970]                           
```

Interpretation: rax = &[rbp+0x48], store at [rbp+0x520]. rax = &[rbp+0x108], store at [rbp+0x528]. eax = byte [rsi+0xB8]. If [rbp+0x807] == 0, jump to loc_6723380. If al == 0, jump to loc_67233d9.

Callees: none.
Fields read: [rbp+0x48], [rbp+0x108], [rsi+0xB8], [rbp+0x807]. Fields written: [rbp+0x520], [rbp+0x528].

---

## Phase 21 — Word increment + al==3 path (0x6723322..0x6723373)

Same instruction sequence as F1 Phase 21 (same code pattern; different offsets: [rbp+0x970] vs [rbp+0x968], [rbp+0x815] vs [rbp+0x846], jump targets 0x6723746/0x672A331 vs F1 0x6776746/0x677E031).

```
0x6723322  mov rdx,[rbp+0x970]                           
0x6723329  movzx eax,word ptr [rdx]                      
0x672332c  lea ecx,[rax+1]                               
0x672332f  mov [rdx],cx                                  
0x6723332  cmp byte ptr [rbp+0x815],3                    
0x6723339  jne 0x6723746                                 ; -> loc_6723746
0x672333f  cmp byte ptr [rsi+0xD8],3                     
0x6723346  jne 0x672A331                                 ; -> sub_672a331
0x672334c  movaps [rbp+0x760],xmm6                       
0x6723353  mov rcx,[rbp+0x548]                           
0x672335a  test rcx,rcx                                  
0x672335d  je 0x6724368                                  ; -> loc_6724368
0x6723363  lock inc dword ptr [rcx+8]                    
0x6723367  mov rdx,[rbp+0x548]                           
0x672336e  jmp 0x672436A                                 ; -> loc_672436a
0x6723373  nop [rax+rax]                                 
```

Interpretation: rdx = [rbp+0x970], eax = word [rdx] (counter), increment and store back. If [rbp+0x815] != 3, jump to loc_6723746. If byte [rsi+0xD8] != 3, jump to 0x672A331. [rbp+0x760] = xmm6. rcx = [rbp+0x548], if null jump to 0x6724368, else lock inc dword [rcx+8], rdx = [rbp+0x548], jmp 0x672436A.

Callees: none.
Fields read: [rbp+0x970], [rdx], [rbp+0x815], [rsi+0xD8], [rbp+0x760], [rbp+0x548], [rcx+8]. Fields written: [rdx] (word increment), [rbp+0x760], [rcx+8] (lock inc).

---

## Phase 22 — al==0 path + word increment (0x6723380..0x67233d4)

Same instruction sequence as F1 Phase 22 (same code pattern; different offsets: [rbp+0x970] vs [rbp+0x968], [rbp+0x815] vs [rbp+0x846], jump targets 0x6723971/0x672A32B vs F1 0x6776971/0x677E02B).

```
0x6723380  test al,al                                    
0x6723382  je 0x67235E6                                  ; -> loc_67235e6
0x6723388  mov rdx,[rbp+0x970]                           
0x672338f  movzx eax,word ptr [rdx]                      
0x6723392  lea ecx,[rax+1]                               
0x6723395  mov [rdx],cx                                  
0x6723398  cmp byte ptr [rbp+0x815],3                    
0x672339f  jne 0x6723971                                 ; -> loc_6723971
0x67233a5  cmp byte ptr [rsi+0xD8],3                     
0x67233ac  jne 0x672A32B                                 ; -> sub_672a32b
0x67233b2  movaps [rbp+0x760],xmm6                       
0x67233b9  mov rcx,[rbp+0x548]                           
0x67233c0  test rcx,rcx                                  
0x67233c3  je 0x67243E9                                  ; -> loc_67243e9
0x67233c9  lock inc dword ptr [rcx+8]                    
0x67233cd  mov rdx,[rbp+0x548]                           
0x67233d4  jmp 0x67243EB                                 ; -> loc_67243eb
```

Interpretation: test al,al (from [rsi+0xB8]). If al == 0, jump to loc_67235E6. Otherwise: rdx = [rbp+0x970], increment word [rdx]. If [rbp+0x815] != 3, jump to loc_6723971. If byte [rsi+0xD8] != 3, jump to 0x672A32B. [rbp+0x760] = xmm6. rcx = [rbp+0x548], if null jump to 0x67243E9, else lock inc dword [rcx+8], rdx = [rbp+0x548], jmp 0x67243EB.

Callees: none.
Fields read: [rsi+0xB8], [rbp+0x970], [rdx], [rbp+0x815], [rsi+0xD8], [rbp+0x760], [rbp+0x548], [rcx+8]. Fields written: [rdx] (word increment), [rbp+0x760], [rcx+8] (lock inc).

---

## Phase 23 — al==1 path entry (0x67233d9..0x6723437)

Same instruction sequence as F1 Phase 23 (same code pattern; different offsets: [rbp+0x510] vs [rbp+0x510] same, [rbp+0x370] vs [rbp+0x370] same; call targets 0x67A75D0, 0x678E1D0 same).

```
0x67233d9  cmp byte ptr [rsi+0xE0],1                     
0x67233e0  jne 0x6723AE5                                 ; -> loc_6723ae5
0x67233e6  addss xmm12,xmm13                             
0x67233eb  addps xmm15,xmm14                             
0x67233ef  movlps [rbp+0x2A0],xmm15                      
0x67233f7  movss [rbp+0x2A8],xmm12                       
0x6723400  lea rcx,[rbp+0x510]                           
0x6723407  mov rdx,r15                                   
0x672340a  call 0x67A75D0                                ; -> sub_67a75d0
0x672340f  nop                                           
0x6723410  lea rax,[rbp+0x2A0]                           
0x6723417  mov [rsp+0x20],rax                            
0x672341c  lea rdi,[rbp+0x370]                           
0x6723423  mov rcx,rdi                                   
0x6723426  lea rdx,[rbp+0x1F0]                           
0x672342d  lea r8,[rbp+0x198]                            
0x6723434  mov r9,r15                                    
0x6723437  call 0x678E1D0                                ; -> sub_678e1d0
```

Interpretation: cmp byte [rsi+0xE0], 1. If not 1, jump to loc_6723AE5. addss xmm12, xmm13; addps xmm15, xmm14. movlps [rbp+0x2A0], xmm15; movss [rbp+0x2A8], xmm12. Call 0x67A75D0(rcx=&[rbp+0x510], rdx=r15). [rsp+0x20] = &[rbp+0x2A0]. rdi = &[rbp+0x370], rcx = rdi, rdx = &[rbp+0x1F0], r8 = &[rbp+0x198], r9 = r15. Call 0x678E1D0.

Callees: 0x67A75D0 (sub_67a75d0), 0x678E1D0 (sub_678e1d0).
Fields read: [rsi+0xE0], [rbp+0x510], [rbp+0x2A0], [rbp+0x1F0], [rbp+0x198]. Fields written: [rbp+0x2A0], [rbp+0x2A8], [rsp+0x20].

---

## Phase 24 — Struct copy + calls 0x67E23F0 / 0x678E420 (0x672343d..0x6723514)

Same instruction sequence as F1 Phase 24 (same code pattern; call targets 0x67E23F0, 0x678E420 same).

```
0x672343c  nop                                           
0x672343d  mov eax,[r13+0x60]                            
0x6723441  mov [rbx+0x70],eax                            
0x6723444  movups xmm0,[r13+0x50]                        
0x6723449  movups [rbx+0x60],xmm0                        
0x672344d  movzx eax,byte ptr [rbp+0x254]                
0x6723454  mov [rbp+0x4C4],al                            
0x672345a  movups xmm0,[rbp+0x258]                       
0x6723461  movups [rbp+0x4C8],xmm0                       
0x6723468  movups xmm0,[r13+0x78]                        
0x672346d  movups xmm1,[r13+0x88]                        
0x6723475  movups xmm2,[r13+0x97]                        
0x672347d  movups [rbx+0xA7],xmm2                        
0x6723484  movups [rbx+0x98],xmm1                        
0x672348b  movups [rbx+0x88],xmm0                        
0x6723492  movzx eax,word ptr [rbp+0x298]                
0x6723499  mov [rbp+0x508],ax                            
0x67234a0  mov rcx,r15                                   
0x67234a3  call 0x67E23F0                                ; -> sub_67e23f0
0x67234a8  nop                                           
0x67234a9  mov [rsp+0x20],rdi                            
0x67234ae  lea rcx,[rbp+0x560]                           
0x67234b5  lea rdx,[rbp+0x460]                           
0x67234bc  lea r8,[rbp+0x408]                            
0x67234c3  lea r9,[rbp+0x380]                            
0x67234ca  call 0x678E420                                ; -> sub_678e420
0x67234cf  nop                                           
0x67234d0  mov eax,[rbx+0x70]                            
0x67234d3  lea rcx,[rbp+0x6A0]                           
0x67234da  mov [rcx+0x10],eax                            
0x67234dd  movups xmm0,[rbx+0x60]                        
0x67234e1  movups [rcx],xmm0                             
0x67234e4  movzx eax,byte ptr [rbp+0x4C4]                
0x67234eb  mov [rbp+0x6B4],al                            
0x67234f1  movups xmm0,[rbp+0x4C8]                       
0x67234f8  movups [rbp+0x6B8],xmm0                       
0x67234ff  movups xmm0,[rbx+0x88]                        
0x6723506  movups xmm1,[rbx+0x98]                        
0x672350d  movups xmm2,[rbx+0xA7]                        
0x6723514  lea rax,[rbp+0x6C8]                           
```

Interpretation: eax = [r13+0x60], store at [rbx+0x70]. Copy xmm0 from [r13+0x50] to [rbx+0x60]. eax = byte [rbp+0x254], store at [rbp+0x4C4]. Copy xmm0 from [rbp+0x258] to [rbp+0x4C8]. Copy xmm0-xmm2 from [r13+0x78]/[r13+0x88]/[r13+0x97] to [rbx+0xA7]/[rbx+0x98]/[rbx+0x88]. eax = word [rbp+0x298], store at [rbp+0x508]. Call 0x67E23F0(rcx=r15). [rsp+0x20]=rdi. Call 0x678E420(rcx=&[rbp+0x560], rdx=&[rbp+0x460], r8=&[rbp+0x408], r9=&[rbp+0x380]). eax = [rbx+0x70], rcx = &[rbp+0x6A0], store eax at [rcx+0x10]. Copy xmm0 from [rbx+0x60] to [rcx]. eax = byte [rbp+0x4C4], store at [rbp+0x6B4]. Copy xmm0 from [rbp+0x4C8] to [rbp+0x6B8]. Copy xmm0-xmm2 from [rbx+0x88]/[rbx+0x98]/[rbx+0xA7] to [rbp+0x6C8+0x1F]/[rbp+0x6C8+0x10]/[rbp+0x6C8]. lea rax = &[rbp+0x6C8] (continues in next chunk).

Callees: 0x67E23F0 (sub_67e23f0), 0x678E420 (sub_678e420).
Fields read: [r13+0x60], [r13+0x50], [rbp+0x254], [rbp+0x258], [r13+0x78], [r13+0x88], [r13+0x97], [rbp+0x298], [r15], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0x88], [rbx+0x98], [rbx+0xA7], [rbp+0x560], [rbp+0x460], [rbp+0x408], [rbp+0x380]. Fields written: [rbx+0x70], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0xA7], [rbx+0x98], [rbx+0x88], [rbp+0x508], [rsp+0x20], [rcx+0x10], [rcx], [rbp+0x6B4], [rbp+0x6B8], [rbp+0x6C8+0x1F], [rbp+0x6C8+0x10], [rbp+0x6C8].

## NEXT
Resume at 0x672351b (Phase 25 — finish struct copy + call 0x5ABA5C0 + buffer zeroing + TLS call).

---

## Phase 25 — Finish struct copy + call 0x5ABA5C0 + buffer zeroing + TLS call (0x672351b..0x67235e1)

Same instruction sequence as F1 Phase 25 (same code pattern; different offsets: [rbp+0x6F8] vs [rbp+0x708], [rbp+0x818] vs [rbp+0x828], jump targets 0x6724C3B/0x6724C4F vs F1 0x677B13B/0x677B14F).

```
0x672351b  movups [rax+0x1F],xmm2                        
0x672351f  movups [rax+0x10],xmm1                        
0x6723523  movups [rax],xmm0                             
0x6723526  movzx eax,word ptr [rbp+0x508]                
0x672352d  mov [rbp+0x6F8],ax                            
0x6723534  mov rax,[rbp+0x808]                           
0x672353b  mov rcx,[rax+0x10]                            
0x672353f  mov eax,0x9D0                                 
0x6723544  add rcx,rax                                   
0x6723547  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x672354c  nop                                           
0x672354d  mov r14,rax                                   
0x6723550  movups [r13-0x28],xmm6                        
0x6723555  movups [r13-0x38],xmm6                        
0x672355a  movups [r13-0x48],xmm6                        
0x672355f  movups [r13-0x58],xmm6                        
0x6723564  movups [r13-0x68],xmm6                        
0x6723569  movups [r13-0x78],xmm6                        
0x672356e  movups [r13-0x88],xmm6                        
0x6723576  movups [r13-0x98],xmm6                        
0x672357e  movups [r13-0xA8],xmm6                        
0x6723586  movups [r13-0xB8],xmm6                        
0x672358e  movups [r13-0xC8],xmm6                        
0x6723596  movups [r13-0xD8],xmm6                        
0x672359e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67235a5  mov rax,[rcx]                                 
0x67235a8  mov rax,[rax+0x10]                            
0x67235ac  mov dl,0x4A                                   
0x67235ae  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67235b4  nop                                           
0x67235b5  mov [rbp+0x818],al                            
0x67235bb  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x67235c2  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x67235c9  je 0x6724C3B                                  ; -> loc_6724c3b
0x67235cf  movzx eax,word ptr [rbp+0x6F8]                
0x67235d6  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x67235d9  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x67235e1  jmp 0x6724C4F                                 ; -> loc_6724c4f
```

Interpretation: Finish storing xmm0-xmm2 to [rax+0x1F]/[rax+0x10]/[rax]. eax = word [rbp+0x508], store at [rbp+0x6F8]. rax = [rbp+0x808], rcx = [rax+0x10], rax = 0x9D0, rcx += rax. Call 0x5ABA5C0. r14 = rax (result). Zero xmm6 at [r13-0x28]..[r13-0xD8] (13 stores). rcx = [0x1233E1B0], rax = [rcx], rax = [rax+0x10], dl = 0x4A, call via [0xF99FFA0] (sub_eea6040), store al at [rbp+0x818]. rdx = [r14+0x8A8], cmp with [r14+0x8B0], if equal jump to 0x6724C3B. Otherwise: eax = word [rbp+0x6F8], store at [rdx], add qword [r14+0x8A8], 2, jmp 0x6724C4F.

Callees: 0x5ABA5C0 (sub_5aba5c0), [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [rbp+0x508], [rbp+0x808], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x6F8]. Fields written: [rax+0x1F], [rax+0x10], [rax], [rbp+0x6F8], [r13-0x28]..[r13-0xD8], [rbp+0x818], [rdx] (word store), [r14+0x8A8].

---

## Phase 26 — al==0 path entry + calls + struct copy + word store (0x67235e6..0x6723741)

Same instruction sequence as F1 Phase 26 (same code pattern; different offsets: [rbp+0x6F0] vs [rbp+0x708], jump targets 0x6723CF3/0x6724A2F/0x6724A43 vs F1 0x677B2F3/0x677B52F/0x677B543).

```
0x67235e6  cmp byte ptr [rsi+0xE0],1                     
0x67235ed  jne 0x6723CF3                                 ; -> loc_6723cf3
0x67235f3  lea rcx,[rbp+0x510]                           
0x67235fa  lea rdx,[rbp+0x370]                           
0x6723601  call 0x67A75D0                                ; -> sub_67a75d0
0x6723606  nop                                           
0x6723607  lea rcx,[rbp+0x560]                           
0x672360e  lea rdx,[rbp+0x450]                           
0x6723615  lea r8,[rbp+0x3F8]                            
0x672361c  lea r9,[rbp+0x370]                            
0x6723623  call 0x678F640                                ; -> sub_678f640
0x6723628  nop                                           
0x6723629  mov eax,[rbx+0x60]                            
0x672362c  lea rcx,[rbp+0x698]                           
0x6723633  mov [rcx+0x10],eax                            
0x6723636  movups xmm0,[rbx+0x50]                        
0x672363a  movups [rcx],xmm0                             
0x672363d  movzx eax,byte ptr [rbp+0x4B4]                
0x6723644  mov [rbp+0x6AC],al                            
0x672364a  movups xmm0,[rbp+0x4B8]                       
0x6723651  movups [rbp+0x6B0],xmm0                       
0x6723658  movups xmm0,[rbx+0x78]                        
0x672365c  movups xmm1,[rbx+0x88]                        
0x6723663  movups xmm2,[rbx+0x97]                        
0x672366a  lea rax,[rbp+0x564]                           
0x6723671  movups [rax+0x17B],xmm2                       
0x6723678  movups [rax+0x16C],xmm1                       
0x672367f  movups [rax+0x15C],xmm0                       
0x6723686  movzx eax,word ptr [rbp+0x4F8]                
0x672368d  mov [rbp+0x6F0],ax                            
0x6723694  mov rax,[rbp+0x808]                           
0x672369b  mov rcx,[rax+0x10]                            
0x672369f  mov eax,0x9D0                                 
0x67236a4  add rcx,rax                                   
0x67236a7  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x67236ac  nop                                           
0x67236ad  mov r14,rax                                   
0x67236b0  movups [r13-0x28],xmm6                        
0x67236b5  movups [r13-0x38],xmm6                        
0x67236ba  movups [r13-0x48],xmm6                        
0x67236bf  movups [r13-0x58],xmm6                        
0x67236c4  movups [r13-0x68],xmm6                        
0x67236c9  movups [r13-0x78],xmm6                        
0x67236ce  movups [r13-0x88],xmm6                        
0x67236d6  movups [r13-0x98],xmm6                        
0x67236de  movups [r13-0xA8],xmm6                        
0x67236e6  movups [r13-0xB8],xmm6                        
0x67236ee  movups [r13-0xC8],xmm6                        
0x67236f6  movups [r13-0xD8],xmm6                        
0x67236fe  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6723705  mov rax,[rcx]                                 
0x6723708  mov rax,[rax+0x10]                            
0x672370c  mov dl,0x4A                                   
0x672370e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6723714  nop                                           
0x6723715  mov [rbp+0x818],al                            
0x672371b  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6723722  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6723729  je 0x6724A2F                                  ; -> loc_6724a2f
0x672372f  movzx eax,word ptr [rbp+0x6F0]                
0x6723736  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x6723739  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6723741  jmp 0x6724A43                                 ; -> loc_6724a43
```

Interpretation: cmp byte [rsi+0xE0], 1. If not 1, jump to loc_6723CF3. Call 0x67A75D0(rcx=&[rbp+0x510], rdx=&[rbp+0x370]). Call 0x678F640(rcx=&[rbp+0x560], rdx=&[rbp+0x450], r8=&[rbp+0x3F8], r9=&[rbp+0x370]). eax = [rbx+0x60], rcx = &[rbp+0x698], store at [rcx+0x10]. Copy xmm0 from [rbx+0x50] to [rcx]. eax = byte [rbp+0x4B4], store at [rbp+0x6AC]. Copy xmm0 from [rbp+0x4B8] to [rbp+0x6B0]. Copy xmm0-xmm2 from [rbx+0x78]/[rbx+0x88]/[rbx+0x97] to [rbp+0x564+0x17B]/[rbp+0x564+0x16C]/[rbp+0x564+0x15C]. eax = word [rbp+0x4F8], store at [rbp+0x6F0]. rax = [rbp+0x808], rcx = [rax+0x10], rax = 0x9D0, rcx += rax. Call 0x5ABA5C0. r14 = rax. Zero xmm6 at [r13-0x28]..[r13-0xD8]. rcx = [0x1233E1B0], rax = [rcx], rax = [rax+0x10], dl = 0x4A, call via [0xF99FFA0], store al at [rbp+0x818]. rdx = [r14+0x8A8], cmp with [r14+0x8B0], if equal jump to 0x6724A2F. Otherwise: eax = word [rbp+0x6F0], store at [rdx], add qword [r14+0x8A8], 2, jmp 0x6724A43.

Callees: 0x67A75D0 (sub_67a75d0), 0x678F640 (sub_678f640), 0x5ABA5C0 (sub_5aba5c0), [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [rsi+0xE0], [rbp+0x510], [rbp+0x370], [rbp+0x560], [rbp+0x450], [rbp+0x3F8], [rbx+0x60], [rbx+0x50], [rbp+0x4B4], [rbp+0x4B8], [rbx+0x78], [rbx+0x88], [rbx+0x97], [rbp+0x564], [rbp+0x4F8], [rbp+0x808], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x6F0]. Fields written: [rcx+0x10], [rcx], [rbp+0x6AC], [rbp+0x6B0], [rbp+0x564+0x17B], [rbp+0x564+0x16C], [rbp+0x564+0x15C], [rbp+0x6F0], [r13-0x28]..[r13-0xD8], [rbp+0x818], [rdx] (word store), [r14+0x8A8].

## NEXT
Resume at 0x6723746 (Phase 27 — al==3 with [rsi+0xD8]!=3 path).

---

## Phase 27 — al==3 with [rsi+0xD8]!=3 path + call 0x67A75D0 + call 0x678E1D0 + struct copy + call 0x67E23F0 (0x6723746..0x672381b)

Same instruction sequence as F1 Phase 27 (same code pattern; different offsets: [rbp+0x79C] vs [rbp+0x7CC], [rbp+0x7A0] vs [rbp+0x2A0], [rbp+0x2A4] vs [rbp+0x2A4] same; call targets 0x67A75D0, 0x678E1D0, 0x67E23F0 same).

```
0x6723746  mov ecx,[rbp+0x79C]                           
0x672374c  mov [rbp+0x2A0],ecx                           
0x6723752  mov [rbp+0x2A4],ax                            
0x6723759  addss xmm12,xmm13                             
0x672375e  addps xmm15,xmm14                             
0x6723762  movlps [rbp+0x7A0],xmm15                      
0x672376a  movss [rbp+0x7A8],xmm12                       
0x6723773  lea rcx,[rbp+0x510]                           
0x672377a  mov rdx,r15                                   
0x672377d  call 0x67A75D0                                ; -> sub_67a75d0
0x6723782  nop                                           
0x6723783  lea rax,[rbp+0x7A0]                           
0x672378a  mov [rsp+0x20],rax                            
0x672378f  lea rdi,[rbp+0x370]                           
0x6723796  mov rcx,rdi                                   
0x6723799  lea rdx,[rbp+0x1F0]                           
0x67237a0  lea r8,[rbp+0x198]                            
0x67237a7  mov r9,r15                                    
0x67237aa  call 0x678E1D0                                ; -> sub_678e1d0
0x67237af  nop                                           
0x67237b0  mov eax,[r13+0x60]                            
0x67237b4  mov [rbx+0x70],eax                            
0x67237b7  movups xmm0,[r13+0x50]                        
0x67237bc  movups [rbx+0x60],xmm0                        
0x67237c0  movzx eax,byte ptr [rbp+0x254]                
0x67237c7  mov [rbp+0x4C4],al                            
0x67237cd  movups xmm0,[rbp+0x258]                       
0x67237d4  movups [rbp+0x4C8],xmm0                       
0x67237db  movups xmm0,[r13+0x78]                        
0x67237e0  movups xmm1,[r13+0x88]                        
0x67237e8  movups xmm2,[r13+0x97]                        
0x67237f0  movups [rbx+0xA7],xmm2                        
0x67237f7  movups [rbx+0x98],xmm1                        
0x67237fe  movups [rbx+0x88],xmm0                        
0x6723805  movzx eax,word ptr [rbp+0x298]                
0x672380c  mov [rbp+0x508],ax                            
0x6723813  mov rcx,r15                                   
0x6723816  call 0x67E23F0                                ; -> sub_67e23f0
0x672381b  nop                                           
```

Interpretation: ecx = [rbp+0x79C], store at [rbp+0x2A0]. [rbp+0x2A4] = ax (from previous computation). addss xmm12, xmm13; addps xmm15, xmm14. movlps [rbp+0x7A0], xmm15; movss [rbp+0x7A8], xmm12. Call 0x67A75D0(rcx=&[rbp+0x510], rdx=r15). [rsp+0x20] = &[rbp+0x7A0]. rdi = &[rbp+0x370], rcx = rdi, rdx = &[rbp+0x1F0], r8 = &[rbp+0x198], r9 = r15. Call 0x678E1D0. eax = [r13+0x60], store at [rbx+0x70]. Copy xmm0 from [r13+0x50] to [rbx+0x60]. eax = byte [rbp+0x254], store at [rbp+0x4C4]. Copy xmm0 from [rbp+0x258] to [rbp+0x4C8]. Copy xmm0-xmm2 from [r13+0x78]/[r13+0x88]/[r13+0x97] to [rbx+0xA7]/[rbx+0x98]/[rbx+0x88]. eax = word [rbp+0x298], store at [rbp+0x508]. Call 0x67E23F0(rcx=r15).

Callees: 0x67A75D0 (sub_67a75d0), 0x678E1D0 (sub_678e1d0), 0x67E23F0 (sub_67e23f0).
Fields read: [rbp+0x79C], [rbp+0x510], [rbp+0x7A0], [rbp+0x1F0], [rbp+0x198], [r13+0x60], [r13+0x50], [rbp+0x254], [rbp+0x258], [r13+0x78], [r13+0x88], [r13+0x97], [rbp+0x298], [r15]. Fields written: [rbp+0x2A0], [rbp+0x2A4], [rbp+0x7A0], [rbp+0x7A8], [rsp+0x20], [rbx+0x70], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0xA7], [rbx+0x98], [rbx+0x88], [rbp+0x508].

---

## Phase 28 — Struct copy setup + call 0x6791880 + struct copy + call 0x5ABA5C0 (0x672381c..0x67238d7)

Same instruction sequence as F1 Phase 28 (same code pattern; different offsets: [rbp+0x2A0] vs [rbp+0x2A0] same, [rbp+0x708] vs [rbp+0x708] same; call targets 0x6791880, 0x5ABA5C0 same).

```
0x672381c  lea rax,[rbp+0x2A0]                           
0x6723823  mov [rsp+0x30],rax                            
0x6723828  lea rax,[rbp+0x2A4]                           
0x672382f  mov [rsp+0x28],rax                            
0x6723834  mov [rsp+0x20],rdi                            
0x6723839  lea rcx,[rbp+0x560]                           
0x6723840  lea rdx,[rbp+0x460]                           
0x6723847  lea r8,[rbp+0x408]                            
0x672384e  lea r9,[rbp+0x380]                            
0x6723855  call 0x6791880                                ; -> sub_6791880
0x672385a  nop                                           
0x672385b  mov eax,[rbx+0x70]                            
0x672385e  lea rcx,[rbp+0x6B0]                           
0x6723865  mov [rcx+0x10],eax                            
0x6723868  movups xmm0,[rbx+0x60]                        
0x672386c  movups [rcx],xmm0                             
0x672386f  movzx eax,byte ptr [rbp+0x4C4]                
0x6723876  mov [rbp+0x6C4],al                            
0x672387c  movups xmm0,[rbp+0x4C8]                       
0x6723883  movups [rbp+0x6C8],xmm0                       
0x672388a  movups xmm0,[rbx+0x88]                        
0x6723891  movups xmm1,[rbx+0x98]                        
0x6723898  movups xmm2,[rbx+0xA7]                        
0x672389f  lea rax,[rbp+0x6D8]                           
0x67238a6  movups [rax+0x1F],xmm2                        
0x67238aa  movups [rax+0x10],xmm1                        
0x67238ae  movups [rax],xmm0                             
0x67238b1  movzx eax,word ptr [rbp+0x508]                
0x67238b8  mov [rbp+0x708],ax                            
0x67238bf  mov rax,[rbp+0x808]                           
0x67238c6  mov rcx,[rax+0x10]                            
0x67238ca  mov eax,0x9D0                                 
0x67238cf  add rcx,rax                                   
0x67238d2  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x67238d7  nop                                           
```

Interpretation: [rsp+0x30] = &[rbp+0x2A0]. [rsp+0x28] = &[rbp+0x2A4]. [rsp+0x20] = rdi. Call 0x6791880(rcx=&[rbp+0x560], rdx=&[rbp+0x460], r8=&[rbp+0x408], r9=&[rbp+0x380]). eax = [rbx+0x70], rcx = &[rbp+0x6B0], store at [rcx+0x10]. Copy xmm0 from [rbx+0x60] to [rcx]. eax = byte [rbp+0x4C4], store at [rbp+0x6C4]. Copy xmm0 from [rbp+0x4C8] to [rbp+0x6C8]. Copy xmm0-xmm2 from [rbx+0x88]/[rbx+0x98]/[rbx+0xA7] to [rbp+0x6D8+0x1F]/[rbp+0x6D8+0x10]/[rbp+0x6D8]. eax = word [rbp+0x508], store at [rbp+0x708]. rax = [rbp+0x808], rcx = [rax+0x10], rax = 0x9D0, rcx += rax. Call 0x5ABA5C0.

Callees: 0x6791880 (sub_6791880), 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x2A0], [rbp+0x2A4], [rbp+0x560], [rbp+0x460], [rbp+0x408], [rbp+0x380], [rbx+0x70], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0x88], [rbx+0x98], [rbx+0xA7], [rbp+0x508], [rbp+0x808], [rax+0x10]. Fields written: [rsp+0x30], [rsp+0x28], [rsp+0x20], [rcx+0x10], [rcx], [rbp+0x6C4], [rbp+0x6C8], [rbp+0x6D8+0x1F], [rbp+0x6D8+0x10], [rbp+0x6D8], [rbp+0x708].

---

## Phase 29 — Buffer zeroing + TLS call + word store + jump (0x67238d8..0x672396c)

Same instruction sequence as F1 Phase 29 (same code pattern; different offsets: [rbp+0x708] vs [rbp+0x708] same; jump targets 0x6724D3C/0x6724D50 vs F1 0x677B53C/0x677B550).

```
0x67238d8  mov r14,rax                                   
0x67238db  movups [r13-0x28],xmm6                        
0x67238e0  movups [r13-0x38],xmm6                        
0x67238e5  movups [r13-0x48],xmm6                        
0x67238ea  movups [r13-0x58],xmm6                        
0x67238ef  movups [r13-0x68],xmm6                        
0x67238f4  movups [r13-0x78],xmm6                        
0x67238f9  movups [r13-0x88],xmm6                        
0x6723901  movups [r13-0x98],xmm6                        
0x6723909  movups [r13-0xA8],xmm6                        
0x6723911  movups [r13-0xB8],xmm6                        
0x6723919  movups [r13-0xC8],xmm6                        
0x6723921  movups [r13-0xD8],xmm6                        
0x6723929  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6723930  mov rax,[rcx]                                 
0x6723933  mov rax,[rax+0x10]                            
0x6723937  mov dl,0x4A                                   
0x6723939  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x672393f  nop                                           
0x6723940  mov [rbp+0x818],al                            
0x6723946  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x672394d  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6723954  je 0x6724D3C                                  ; -> loc_6724d3c
0x672395a  movzx eax,word ptr [rbp+0x708]                
0x6723961  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x6723964  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x672396c  jmp 0x6724D50                                 ; -> loc_6724d50
```

Interpretation: r14 = rax (result from 0x5ABA5C0). Zero xmm6 at [r13-0x28]..[r13-0xD8] (13 stores). rcx = [0x1233E1B0], rax = [rcx], rax = [rax+0x10], dl = 0x4A, call via [0xF99FFA0] (sub_eea6040), store al at [rbp+0x818]. rdx = [r14+0x8A8], cmp with [r14+0x8B0], if equal jump to 0x6724D3C. Otherwise: eax = word [rbp+0x708], store at [rdx], add qword [r14+0x8A8], 2, jmp 0x6724D50.

Callees: [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [r13-0x28]..[r13-0xD8], [0x1233E1B0], [rcx], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x708]. Fields written: [rbp+0x818], [rdx] (word store), [r14+0x8A8].

## NEXT
Resume at 0x6723971 (Phase 30 — loc_6723971: al==3 with [rsi+0xD8]!=3 alternate path).

---


