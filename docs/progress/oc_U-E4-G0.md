# U-E4-G0: Chunk builder at 0x670b6e0

Unit: U-E4-G0
Function: sub_670b6e0 (chunk builder, called by chunk extractor)
RVAs: 0x670b6e0 .. 0x670bea9 (ends just before G1 Phase 27 at 0x670beaa)
Source: `rdis dis 0x670b6e0 <n>` on Minecraft.Windows.exe 1.26.62.01
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown
Template: docs/progress/oc_U-E4-F1.md (builder 0x67762e0, verified)

## NEXT
Resume at 0x670beaa (Phase 28 — Call 0x67E23F0 + call 0x678E420, continues from G1).

Register/offset mapping G0 vs F1:
- G0 rdi = F1 rsi (4th/2nd arg respectively)
- G0 [rbp+0x108] = saved r9; F1 rsi = r9 directly
- G0 [rbp+0x838] = saved rdx; F1 [rbp+0x828] = saved rdx
- G0 [rbp+0x778] = saved rcx; F1 [rbp+0x768] = saved rcx
- G0 [rbp+0x970] = search-table object; F1 [rbp+0x968]
- G0 [rbp+0x580] = vector base; F1 [rbp+0x570]
- G0 [rbp+0x120] = u64 one/flag; F1 [rbp+0x110]
- G0 [rbp+0x828] = found index; F1 [rbp+0x81C]
- G0 [rbp+0x82A] = found flag; F1 [rbp+0x81E]
- G0 [rbp+0x846] = al from [rdi+0xD8]; F1 [rbp+0x835]
- G0 [rbp+0x837] = byte [rbp+0x978] & cl; F1 [rbp+0x836]
- G0 [rbp+0x980] = object for struct copy; F1 [rbp+0x980]
- G0 [rbp+0x990] = object for struct copy (al==0 path); F1 [rbp+0x990]?

---

## Phase 1 — Prologue (0x670b6e0..0x670b6ec)

Same instruction sequence as F1 Phase 1 (different stack size: 0x988 vs 0x978).

```
0x670b6e0  push rbp                                      
0x670b6e1  push r15                                      
0x670b6e3  push r14                                      
0x670b6e5  push r13                                      
0x670b6e7  push r12                                      
0x670b6e9  push rsi                                      
0x670b6ea  push rdi                                      
0x670b6eb  push rbx                                      
0x670b6ec  sub rsp,0x988                                 
```

Interpretation: Standard function prologue, saving rbp, r15, r14, r13, r12, rsi, rdi, rbx; allocating 0x988 bytes of local stack space.

Callees: none.
Fields: none.

---

## Phase 2 — Frame pointer setup + XMM register saves + stack cookie (0x670b6f3..0x670b749)

Same instruction sequence as F1 Phase 2 (different offsets: xmm15 at [rbp+0x8F0] vs [rbp+0x8E0], cookie at [rbp+0x858] vs [rbp+0x848]).

```
0x670b6f3  lea rbp,[rsp+0x80]                            
0x670b6fb  movaps [rbp+0x8F0],xmm15                      
0x670b703  movaps [rbp+0x8E0],xmm14                      
0x670b70b  movaps [rbp+0x8D0],xmm13                      
0x670b713  movaps [rbp+0x8C0],xmm12                      
0x670b71b  movaps [rbp+0x8B0],xmm11                      
0x670b723  movaps [rbp+0x8A0],xmm10                      
0x670b72b  movaps [rbp+0x890],xmm9                       
0x670b733  movaps [rbp+0x880],xmm8                       
0x670b73b  movaps [rbp+0x870],xmm7                       
0x670b742  movaps [rbp+0x860],xmm6                       
0x670b749  mov qword ptr [rbp+0x858],0xFFFFFFFFFFFFFFFE  
```

Interpretation: rbp = rsp+0x80 (frame base). Save xmm15 down to xmm6 at [rbp+0x8F0]..[rbp+0x860]. Store 0xFFFFFFFFFFFFFFFE at [rbp+0x858] (stack cookie/sentinel).

Callees: none.
Fields written: [rbp+0x8F0] xmm15, [rbp+0x8E0] xmm14, [rbp+0x8D0] xmm13, [rbp+0x8C0] xmm12, [rbp+0x8B0] xmm11, [rbp+0x8A0] xmm10, [rbp+0x890] xmm9, [rbp+0x880] xmm8, [rbp+0x870] xmm7, [rbp+0x860] xmm6, [rbp+0x858] = 0xFFFFFFFFFFFFFFFE.

---

## Phase 3 — Argument save + TLS/cookie read (0x670b754..0x670b782)

Same instruction sequence as F1 Phase 3 (different offsets: [rbp+0x108]=r9 vs F1 rsi=r9, [rbp+0x838]=rdx vs [rbp+0x828], [rbp+0x778]=rcx vs [rbp+0x768], result at [rbp+0x847] vs [rbp+0x837]).

```
0x670b754  mov [rbp+0x108],r9                            
0x670b75b  mov rdi,r8                                    
0x670b75e  mov [rbp+0x838],rdx                           
0x670b765  mov [rbp+0x778],rcx                           
0x670b76c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670b773  mov rax,[rcx]                                 
0x670b776  mov rax,[rax+0x10]                            
0x670b77a  mov dl,0x3E                                   
0x670b77c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670b782  mov [rbp+0x847],al                            
```

Interpretation: Save incoming args: [rbp+0x108]=r9 (vec3*), rdi=r8 (Obj**), [rbp+0x838]=rdx (BuilderSpan*), [rbp+0x778]=rcx (FrameCtx*). Load TLS base from [0x1233E1B0], deref to get TEB, read [rax+0x10], call via [0xF99FFA0] (sub_eea6040) with dl=0x3E, store result al at [rbp+0x847].

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10]. Fields written: [rbp+0x108], [rbp+0x838], [rbp+0x778], [rbp+0x847].

---

## Phase 4 — Data section loads + GS cookie range check (0x670b788..0x670b7a7)

Same instruction sequence as F1 Phase 4 (different data addresses: [0x129FB398] vs [0x129FB1F8], jump target 0x6713B50 vs 0x677E052).

```
0x670b788  mov eax,[0x129FB398]                          ; [data_129fb398]
0x670b78e  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x670b794  mov rdx,gs:[0x58]                             
0x670b79d  mov rcx,[rdx+rcx*8]                           
0x670b7a1  cmp eax,[rcx+4]                               
0x670b7a7  jg 0x6713B50                                  ; -> sub_6713b50
```

Interpretation: Load two globals [0x129FB398] and [0x128767C8]. Read gs:[0x58] (TEB), use ecx as index into an array at [rdx+rcx*8], compare eax against [rcx+4]. If greater, jump to 0x6713B50 (error handler).

Callees: none.
Fields read: [0x129FB398], [0x128767C8], gs:[0x58], [rdx+rcx*8], [rcx+4].

---

## Phase 5 — Vector init + search table setup (0x670b7ad..0x670b7f7)

Same instruction sequence as F1 Phase 5 (different offsets: [rbp+0x970] vs [rbp+0x968], [rbp+0x2C8] vs [rbp+0x2B8], [rbp+0x580] vs [rbp+0x570], [rbp+0x120] vs [rbp+0x110], r13 vs r12).

```
0x670b7ad  mov rcx,[rbp+0x970]                           
0x670b7b4  lea rax,[rcx+8]                               
0x670b7b8  mov [rbp+0x2C8],rax                           
0x670b7bf  xorps xmm0,xmm0                               
0x670b7c2  movaps [rbp+0x580],xmm0                       
0x670b7c9  mov qword ptr [rbp+0x120],1                   
0x670b7d4  lea r13,[rbp+0x580]                           
0x670b7db  mov [rbp+0x128],r13                           
0x670b7e2  mov rax,[rcx+0x38]                            
0x670b7e6  movzx r8d,word ptr [rcx+0x42]                 
0x670b7eb  mov edx,r8d                                   
0x670b7ee  shl edx,4                                     
0x670b7f1  mov rcx,rax                                   
0x670b7f4  test r8d,r8d                                  
0x670b7f7  je short 0x670B825                            ; -> loc_670b825
```

Interpretation: rcx = [rbp+0x970] (search-table object). rax = rcx+8 stored at [rbp+0x2C8]. Zero xmm0, store at [rbp+0x580]. Set [rbp+0x120]=1 (u64), r13 = &[rbp+0x580], [rbp+0x128]=r13. rax = [rcx+0x38] (search table base). r8d = word [rcx+0x42] (entry count). edx = r8d << 4 (stride 0x10). rcx = rax. If count==0 jump to notfound path.

Callees: none.
Fields read: [rbp+0x970], [rcx+0x38], [rcx+0x42]. Fields written: [rbp+0x2C8], [rbp+0x580], [rbp+0x120], [rbp+0x128].

---

## Phase 6 — Search loop (0x670b7f9..0x670b823)

Same instruction sequence as F1 Phase 6 (different data address: [0x129FB390] vs [0x129FB1F0], jump targets 0x670B825/0x670B85D vs 0x6776425/0x677645D).

```
0x670b7f9  mov r8,[0x129FB390]                           ; [data_129fb390]
0x670b800  mov r9,rdx                                    
0x670b803  mov rcx,rax                                   
0x670b806  nop [rax+rax]                                 

loc_670b810:  ; from 670b821
0x670b810  mov r10,[rcx]                                 
0x670b813  cmp [r10+0x28],r8                             
0x670b817  je short 0x670B825                            ; -> loc_670b825
0x670b819  add rcx,0x10                                  
0x670b81d  add r9,0xFFFFFFFFFFFFFFF0                     
0x670b821  jne short 0x670B810                           ; -> loc_670b810
0x670b823  jmp short 0x670B85D                           ; -> loc_670b85d
```

Interpretation: r8 = [0x129FB390] (search key). r9 = rdx (remaining count, decremented by 0x10 each iteration). Loop: r10 = [rcx] (entry ptr), compare [r10+0x28] with r8. If equal, jump to found path. Otherwise advance rcx by 0x10, decrement r9 by 0x10, continue if not zero. If exhausted, jump to notfound path.

Callees: none.
Fields read: [0x129FB390], [rcx], [r10+0x28]. Fields written: none (registers only).

---

## Phase 7 — Found path: call 0x5679DB0 (0x670b825..0x670b85b)

Same instruction sequence as F1 Phase 7 (different offsets: [rbp+0x828] vs [rbp+0x81C], [rbp+0x82A] vs [rbp+0x81E], [rbp+0x120] vs [rbp+0x110], [rbp+0x2C8] vs [rbp+0x2B8]).

```
loc_670b825:  ; from 670b7f7, 670b817
0x670b825  add rdx,rax                                   
0x670b828  cmp rcx,rdx                                   
0x670b82b  jae short 0x670B85D                           ; -> loc_670b85d
0x670b82d  sub ecx,eax                                   
0x670b82f  shr ecx,4                                     
0x670b832  mov [rbp+0x828],cx                            
0x670b839  mov byte ptr [rbp+0x82A],1                    
0x670b840  lea rdx,[rbp+0x828]                           
0x670b847  lea r8,[rbp+0x120]                            
0x670b84e  mov rcx,[rbp+0x2C8]                           
0x670b855  call 0x5679DB0                                ; -> sub_5679db0
0x670b85a  nop                                           
0x670b85b  jmp short 0x670B864                           ; -> loc_670b864
```

Interation: rdx += rax (end of table). If rcx >= rdx, go to notfound. Otherwise compute index = (rcx - rax) >> 4 (entry index), store cx at [rbp+0x828], set flag byte [rbp+0x82A]=1. Call 0x5679DB0(rcx=[rbp+0x2C8], rdx=&[rbp+0x828], r8=&[rbp+0x120]). Jump to common code.

Callees: 0x5679DB0 (sub_5679db0).
Fields read: [rbp+0x2C8]. Fields written: [rbp+0x828], [rbp+0x82A].

---

## Phase 8 — Not found path + second call setup (0x670b85d..0x670b892)

Same instruction sequence as F1 Phase 8 (different offsets: [rbp+0x82A] vs [rbp+0x81E], [rbp+0x970] vs [rbp+0x968], [rbp+0x2C8] vs [rbp+0x2B8], [rbp+0x40] vs [rbp+0x40], [rbp+0x300] vs [rbp+0x2F0]).

```
loc_670b85d:  ; from 670b823, 670b82b
0x670b85d  mov byte ptr [rbp+0x82A],0                    

loc_670b864:  ; from 670b85b
0x670b864  mov rdx,[rbp+0x970]                           
0x670b86b  mov rax,[rdx]                                 
0x670b86e  mov [rbp-0x40],rax                            
0x670b872  lea rcx,[rbp-0x38]                            
0x670b876  mov r8,[rdx+8]                                
0x670b87a  mov rdx,[rbp+0x2C8]                           
0x670b881  call 0xE86B370                                ; -> sub_e86b370
0x670b886  nop                                           
0x670b887  mov qword ptr [rbp+0x40],0                    
0x670b88f  xorps xmm6,xmm6                               
0x670b892  movaps [rbp+0x300],xmm6                       
```

Interpretation: Not found: set [rbp+0x82A]=0. Common: rdx = [rbp+0x970], rax = [rdx] stored at [rbp-0x40]. lea rcx = [rbp-0x38]. r8 = [rdx+8]. rdx = [rbp+0x2C8]. Call 0xE86B370. Then [rbp+0x40]=0, xmm6=0, store xmm6 at [rbp+0x300].

Callees: 0xE86B370 (sub_e86b370).
Fields read: [rbp+0x970], [rdx], [rdx+8], [rbp+0x2C8]. Fields written: [rbp-0x40], [rbp+0x40], [rbp+0x300].

---

## Phase 9 — Byte branch on [rdi+0xD8] + al==3 path setup (0x670b899..0x670b8d3)

Same instruction sequence as F1 Phase 9 (different offsets: [rbp+0x784] vs [rbp+0x774], [rbp+0x846] vs [rbp+0x835], [rbp+0x82C] vs [rbp+0x820], [rbp+0x830] vs [rbp+0x824]; G0 uses rdi instead of rsi for the second arg).

```
0x670b899  movzx eax,byte ptr [rdi+0xD8]                 
0x670b8a0  mov dword ptr [rbp+0x784],0                   
0x670b8aa  mov [rbp+0x846],al                            
0x670b8b0  cmp al,3                                      
0x670b8b2  jne 0x670BA0C                                 ; -> loc_670ba0c
0x670b8b8  cmp byte ptr [rdi+0xB8],0                     
0x670b8bf  mov dword ptr [rbp+0x82C],0                   
0x670b8c9  mov dword ptr [rbp+0x830],0                   
0x670b8d3  je 0x670BA20                                  ; -> loc_670ba20
```

Interpretation: al = byte [rdi+0xD8]. [rbp+0x784]=0. [rbp+0x846]=al. If al != 3, jump to loc_670BA0C. If al == 3: check byte [rdi+0xB8]. Zero [rbp+0x82C] and [rbp+0x830]. If [rdi+0xB8] == 0, jump to loc_670BA20.

Callees: none.
Fields read: [rdi+0xD8], [rdi+0xB8]. Fields written: [rbp+0x784], [rbp+0x846], [rbp+0x82C], [rbp+0x830].

---

## Phase 10 — al==3 with [rdi+0xB8]!=0: load u32 pair + allocator call (0x670b8d9..0x670b91c)

Same instruction sequence as F1 Phase 10, different displacements/registers (G0 stores [rdi+0xC0] at [rbp+0x830] vs F1 [rbp+0x824], [rdi+0xC4] at [rbp+0x82C] vs [rbp+0x820]; G0 uses [rbp+0x838] vs F1 [rbp+0x828]; G0 keeps alloc pointer in rsi then r14 vs F1 r14 then r15; je target 0x6713B15 vs 0x677E017).

```
0x670b8d9  mov eax,[rdi+0xC0]                            
0x670b8df  mov [rbp+0x830],eax                           
0x670b8e5  mov eax,[rdi+0xC4]                            
0x670b8eb  mov [rbp+0x82C],eax                           
0x670b8f1  mov rax,[rbp+0x838]                           
0x670b8f8  mov rsi,[rax+0x48]                            
0x670b8fc  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x670b903  mov rax,[rcx]                                 
0x670b906  mov rax,[rax+8]                               
0x670b90a  mov edx,0x30                                  
0x670b90f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670b915  nop                                           
0x670b916  mov r14,rax                                   
0x670b919  test rax,rax                                  
0x670b91c  je 0x6713B15                                  ; -> sub_6713b15
```

Interpretation: eax = [rdi+0xC0] stored at [rbp+0x830]. eax = [rdi+0xC4] stored at [rbp+0x82C]. rax = [rbp+0x838], rsi = [rax+0x48]. rcx = [0x1233E1A8] (allocator vtable). rax = [rcx], rax = [rax+8] (allocate method). edx = 0x30 (size). Call via [0xF99FFA0]. rax = result stored in r14. If null, jump to 0x6713B15 (null handler).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, allocator vcall+8).
Fields read: [rdi+0xC0], [rdi+0xC4], [rbp+0x838], [rax+0x48], [0x1233E1A8], [rcx], [rax+8]. Fields written: [rbp+0x830], [rbp+0x82C].

---

## Phase 11 — Initialize allocated 0x30-byte buffer + SmallVector setup (0x670b922..0x670b99d)

Same instruction sequence as F1 Phase 11, different offsets (G0 [rbp+0x580] vs [rbp+0x570], [rbp+0x584] vs [rbp+0x574], [rbp+0x588] vs [rbp+0x578], [rbp+0x598] vs [rbp+0x588], [rbp+0x5A0] vs [rbp+0x590], [rbp+0x5A8] vs [rbp+0x598], [rbp+0x5B0] vs [rbp+0x5A0]; G0 rcx=rsi vs F1 rcx=r14; call target 0x5AB9970 same).

```
0x670b922  movups xmm0,[0xF5C6AE8]                       ; [data_f5c6ae8] "eCapture texture"
0x670b929  movups [r14+0x10],xmm0                        
0x670b92e  movups xmm0,[0xF5C6AD8]                       ; [data_f5c6ad8] "UIStructureVolumeCapture texture"
0x670b935  movups [r14],xmm0                             
0x670b939  mov byte ptr [r14+0x20],0                     
0x670b93e  mov eax,[rbp+0x830]                           
0x670b944  mov [rbp+0x580],eax                           
0x670b94a  mov eax,[rbp+0x82C]                           
0x670b950  mov [rbp+0x584],eax                           
0x670b956  movaps xmm0,[0xF275E70]                       ; [data_f275e70]
0x670b95d  movups [rbp+0x588],xmm0                       
0x670b964  mov [rbp+0x598],r14                           
0x670b96b  mov qword ptr [rbp+0x5A0],0                   
0x670b976  mov qword ptr [rbp+0x5A8],0x20                
0x670b981  mov qword ptr [rbp+0x5B0],0x2F                
0x670b98c  lea rdx,[rbp+0x120]                           
0x670b993  lea r8,[rbp+0x580]                            
0x670b99a  mov rcx,rsi                                   
0x670b99d  call 0x5AB9970                                ; -> sub_5ab9970
```

Interpretation: Copy 16 bytes from [0xF5C6AE8] to [r14+0x10], 16 bytes from [0xF5C6AD8] to [r14]. [r14+0x20]=0. Store [rbp+0x830] at [rbp+0x580], [rbp+0x82C] at [rbp+0x584]. Copy xmm from [0xF275E70] to [rbp+0x588]. [rbp+0x598]=r14 (pointer to new buffer). [rbp+0x5A0]=0 (size). [rbp+0x5A8]=0x20 (capacity). [rbp+0x5B0]=0x2F. Call 0x5AB9970(rcx=rsi, rdx=&[rbp+0x120], r8=&[rbp+0x580]).

Callees: 0x5AB9970 (sub_5ab9970).
Fields read: [0xF5C6AE8], [0xF5C6AD8], [rbp+0x830], [rbp+0x82C], [0xF275E70], [rbp+0x120], [rbp+0x580]. Fields written: [r14+0x10], [r14], [r14+0x20], [rbp+0x580], [rbp+0x584], [rbp+0x588], [rbp+0x598], [rbp+0x5A0], [rbp+0x5A8], [rbp+0x5B0].

---

## Phase 12 — After call 0x5AB9970: reset xmm + string buffer cleanup (0x670b9a3..0x670ba0a)

Same instruction sequence as F1 Phase 12 (different offsets: [rbp+0x120] vs [rbp+0x110], [rbp+0x300] vs [rbp+0x2F0], [rbp+0x5B0] vs [rbp+0x5A0], [rbp+0x598] vs [rbp+0x588], [rbp+0x784] vs [rbp+0x774]; jump targets 0x6713B37/0x670BA00 vs F1 0x677E039/0x6776600).

```
0x670b9a3  movaps xmm0,[rbp+0x120]                       
0x670b9aa  xorps xmm1,xmm1                               
0x670b9ad  movaps [rbp+0x120],xmm1                       
0x670b9b4  movaps [rbp+0x300],xmm0                       
0x670b9bb  mov rax,[rbp+0x5B0]                           
0x670b9c2  cmp rax,0x10                                  
0x670b9c6  jb short 0x670BA00                            ; -> loc_670ba00
0x670b9c8  mov rcx,[rbp+0x598]                           
0x670b9cf  lea rdx,[rax+1]                               
0x670b9d3  cmp rdx,0x1000                                
0x670b9da  jb short 0x670B9FB                            ; -> loc_670b9fb
0x670b9dc  mov r8,[rcx-8]                                
0x670b9e0  add rcx,0xFFFFFFFFFFFFFFF8                    
0x670b9e4  sub rcx,r8                                    
0x670b9e7  cmp rcx,0x20                                  
0x670b9eb  jae 0x6713B37                                 ; -> sub_6713b37
0x670b9f1  add rax,0x28                                  
0x670b9f5  mov rdx,rax                                   
0x670b9f8  mov rcx,r8                                    

loc_670b9fb:  ; from 670b9da
0x670b9fb  call 0xE935700                                ; -> sub_e935700

loc_670ba00:  ; from 670b9c6
0x670ba00  mov dword ptr [rbp+0x784],0x1C                
0x670ba0a  jmp short 0x670BA20                           ; -> loc_670ba20
```

Interpretation: xmm0 = [rbp+0x120]. xmm1 = 0. [rbp+0x120]=0. [rbp+0x300]=xmm0 (save previous value). rax = [rbp+0x5B0]. If rax < 0x10, skip cleanup. Otherwise: rcx = [rbp+0x598] (buffer ptr), rdx = rax+1, if rdx >= 0x1000: r8 = [rcx-8], rcx -= 8, sub rcx, r8 (compute allocation size), if >= 0x20 jump to 0x6713B37. rax += 0x28, rdx = rax, rcx = r8. Call 0xE935700 (likely free). Then [rbp+0x784] = 0x1C and jump to loc_670BA20.

Callees: 0xE935700 (sub_e935700).
Fields read: [rbp+0x120], [rbp+0x5B0], [rbp+0x598], [rcx-8]. Fields written: [rbp+0x120], [rbp+0x300], [rbp+0x784].

---

## Phase 13 — al!=3 path + loop entry computation (0x670ba0c..0x670bac6)

DIFFERENT from F1 Phase 13. F1 Phase 13 computes a boolean flag from two comparisons (cmp [rsi+0x48]==1 AND cmp ebx==1) and uses rdi as the loop iterator; G0 instead uses rbx directly as the loop iterator, stores a dereferenced qword at [rbp+0x118], and computes [rbp+0x837] = byte [rbp+0x980] & byte [rbp+0x978]. The loop-end pointer is at [rbp+0x100] in both. Pointer setup differs: G0 r14=&[rbp+0x200] (F1 rbx=&[rbp+0x1F0]), G0 rsi=&[rbp+0xA0]/r12=&[rbp+0x3E0] (F1 r14=&[rbp+0xA0]/r13=&[rbp+0x300]).

```
loc_670ba0c:  ; from 670b8b2
0x670ba0c  mov dword ptr [rbp+0x82C],0                   
0x670ba16  mov dword ptr [rbp+0x830],0                   

loc_670ba20:  ; from 670b8d3, 670ba0a
0x670ba20  movzx ecx,byte ptr [rbp+0x980]                
0x670ba27  mov rbx,[rdi+0x40]                            
0x670ba2b  mov rax,[rdi+0x48]                            
0x670ba2f  mov rax,[rax]                                 
0x670ba32  mov [rbp+0x118],rax                           
0x670ba39  imul rax,[rdi+0x38],0x58                      
0x670ba3e  add rax,rbx                                   
0x670ba41  mov [rbp+0x100],rax                           
0x670ba48  and cl,[rbp+0x978]                            
0x670ba4e  mov [rbp+0x837],cl                            
0x670ba54  lea r14,[rbp+0x200]                           
0x670ba5b  mov rax,[rbp+0x778]                           
0x670ba62  add rax,0x470                                 
0x670ba68  mov [rbp+0x788],rax                           
0x670ba6f  movss xmm7,[0xEEC8060]                        ; [data_eec8060]
0x670ba77  movsd xmm8,[0xEFD32F0]                        ; [data_efd32f0]
0x670ba80  movaps xmm9,[0xF0A4080]                       ; [data_f0a4080]
0x670ba88  movss xmm10,[0xEEC8060]                       ; [data_eec8060]
0x670ba91  movsd xmm11,[0xEFD32F0]                       ; [data_efd32f0]
0x670ba9a  movss xmm13,[0xEFC13A4]                       ; [data_efc13a4] = sub_1000000
0x670baa3  movaps xmm14,[0xF0B8740]                      ; [data_f0b8740] = sub_1000000
0x670baab  movzx eax,byte ptr [rbp+0x988]                
0x670bab2  mov [rbp+0x7CC],eax                           
0x670bab8  lea rsi,[rbp+0xA0]                            
0x670babf  lea r12,[rbp+0x3E0]                           
0x670bac6  jmp short 0x670BAE2                           ; -> loc_670bae2
```

Interpretation: [rbp+0x82C]=0, [rbp+0x830]=0. ecx = byte [rbp+0x980]. rbx = [rdi+0x40] (loop iterator start). rax = [rdi+0x48], rax = [rax] stored at [rbp+0x118]. rax = [rdi+0x38] * 0x58 + rbx -> [rbp+0x100] (loop end). cl = byte [rbp+0x980] & [rbp+0x978] -> [rbp+0x837]. r14 = &[rbp+0x200]. rax = [rbp+0x778] + 0x470 -> [rbp+0x788] (loop start). Load constants into xmm7-xmm14 from data sections. eax = byte [rbp+0x988] -> [rbp+0x7CC]. rsi = &[rbp+0xA0], r12 = &[rbp+0x3E0]. Jump to loop head.

Callees: none.
Fields read: [rbp+0x980], [rdi+0x40], [rdi+0x48], [rax], [rdi+0x38], [rbp+0x978], [rbp+0x778], [rbp+0x988]. Fields written: [rbp+0x82C], [rbp+0x830], [rbp+0x118], [rbp+0x100], [rbp+0x837], [rbp+0x788], [rbp+0x7CC].

---

## Phase 14 — Loop head + per-entry dispatch (0x670bad0..0x670bae9)

Same instruction sequence as F1 Phase 14 (G0 uses rbx as iterator and 0x6713A5A as exit target vs F1 rdi and 0x677DF5C; G0 re-loads rsi=&[rbp+0xA0] and r12=&[rbp+0x3E0] on back-edge vs F1 r14/r13).

```
0x670bac8  nop [rax+rax]                                 
0x670bad0  lea rsi,[rbp+0xA0]                            
0x670bad7  lea r12,[rbp+0x3E0]                           

loc_670bade:  ; from 670bb0a, 670bb18
0x670bade  add rbx,0x58                                  

loc_670bae2:  ; from 670bac6
0x670bae2  cmp rbx,[rbp+0x100]                           
0x670bae9  je 0x6713A5A                                  ; -> sub_6713a5a
```

Interpretation: Loop back edge: rsi=&[rbp+0xA0], r12=&[rbp+0x3E0]. Advance rbx by 0x58 (next entry). If rbx == [rbp+0x100] (end), exit to 0x6713A5A.

Callees: none.
Fields read: [rbp+0x100]. Fields written: none.

---

## Phase 15 — Per-entry dispatch + xmm15 load (0x670baef..0x670bb20)

Same instruction sequence as F1 Phase 15 (G0 uses rbx as iterator vs F1 rdi; jump targets 0x6713B25/0x670BB10/0x670BB1A vs F1 0x677E027/0x6776700/0x677670A).

```
0x670baef  movzx eax,byte ptr [rbx+0x28]                 
0x670baf3  test eax,eax                                  
0x670baf5  je short 0x670BB10                            ; -> loc_670bb10
0x670baf7  cmp eax,1                                     
0x670bafa  jne 0x6713B25                                 ; -> sub_6713b25
0x670bb00  lea rax,[rbx+0x18]                            
0x670bb04  cmp qword ptr [rax],0                         
0x670bb08  jne short 0x670BB1A                           ; -> loc_670bb1a
0x670bb0a  jmp short 0x670BADE                           ; -> loc_670bade
0x670bb0c  nop [rax]                                     

loc_670bb10:  ; from 670baf5
0x670bb10  lea rax,[rbx+0x10]                            
0x670bb14  cmp qword ptr [rax],0                         
0x670bb18  je short 0x670BADE                            ; -> loc_670bade

loc_670bb1a:  ; from 670bb08
0x670bb1a  movsd xmm15,[rbx+0x3C]                        
0x670bb20  movsd [rbp+0x2F0],xmm15                       
```

Interpretation: eax = byte [rbx+0x28]. If 0, jump to loc_670BB10 (check [rbx+0x10]). If !=1, jump to 0x6713B25 (error). If ==1: rax = &[rbx+0x18], if [rax] != 0 go to body; else skip to loop increment. At loc_670BB10: rax = &[rbx+0x10], if [rax] == 0 skip. Body: xmm15 = [rbx+0x3C] (double), store at [rbp+0x2F0].

Callees: none.
Fields read: [rbx+0x28], [rbx+0x18], [rbx+0x10], [rbx+0x3C]. Fields written: [rbp+0x2F0].

---
