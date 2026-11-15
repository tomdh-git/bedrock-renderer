# U-E4-F1: Chunk builder at 0x67762e0 — BatchActor variant builder

Unit: U-E4-F1
Function: sub_67762e0 (chunk builder, called by chunk extractor 0x66ea3d0)
RVAs: 0x67762e0 .. (first 800 instructions)
Source: `rdis dis 0x67762e0 <n>` on Minecraft.Windows.exe 1.26.62.01
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Resume at 0x67764e5 (Phase 12) — middle of al==3 branch, after `mov eax,[rsi+0xC4]` / `mov [rbp+0x824],eax`.

---

## Phase 1 — Prologue (0x67762e0..0x67762ec)

Saves all callee-saved registers and allocates 0x978 bytes of stack frame.

```
0x67762e0  push rbp                                      
0x67762e1  push r15                                      
0x67762e3  push r14                                      
0x67762e5  push r13                                      
0x67762e7  push r12                                      
0x67762e9  push rsi                                      
0x67762ea  push rdi                                      
0x67762eb  push rbx                                      
0x67762ec  sub rsp,0x978                                 
```

Interpretation: Standard function prologue, saving rbp, r15, r14, r13, r12, rsi, rdi, rbx; allocating 0x978 bytes of local stack space.

Callees: none.
Fields: none.

---

## Phase 2 — Frame pointer setup + XMM register saves + stack cookie (0x67762f3..0x6776349)

Sets rbp as frame pointer at rsp+0x80, saves xmm15-xmm6, stores stack cookie sentinel.

```
0x67762f3  lea rbp,[rsp+0x80]                            
0x67762fb  movaps [rbp+0x8E0],xmm15                      
0x6776303  movaps [rbp+0x8D0],xmm14                      
0x677630b  movaps [rbp+0x8C0],xmm13                      
0x6776313  movaps [rbp+0x8B0],xmm12                      
0x677631b  movaps [rbp+0x8A0],xmm11                      
0x6776323  movaps [rbp+0x890],xmm10                      
0x677632b  movaps [rbp+0x880],xmm9                       
0x6776333  movaps [rbp+0x870],xmm8                       
0x677633b  movaps [rbp+0x860],xmm7                       
0x6776342  movaps [rbp+0x850],xmm6                       
0x6776349  mov qword ptr [rbp+0x848],0xFFFFFFFFFFFFFFFE  
```

Interpretation: rbp = rsp+0x80 (frame base). Save xmm15 down to xmm6 at [rbp+0x8E0]..[rbp+0x850]. Store 0xFFFFFFFFFFFFFFFE at [rbp+0x848] (likely a stack cookie or sentinel value).

Callees: none.
Fields written: [rbp+0x8E0] xmm15, [rbp+0x8D0] xmm14, [rbp+0x8C0] xmm13, [rbp+0x8B0] xmm12, [rbp+0x8A0] xmm11, [rbp+0x890] xmm10, [rbp+0x880] xmm9, [rbp+0x870] xmm8, [rbp+0x860] xmm7, [rbp+0x850] xmm6, [rbp+0x848] = 0xFFFFFFFFFFFFFFFE.

---

## Phase 3 — Argument save + TLS/cookie read (0x6776354..0x677637e)

Saves rsi=r9, ebx=r8d, [rbp+0x828]=rdx, [rbp+0x768]=rcx. Reads TLS data and calls a function via function pointer table.

```
0x6776354  mov rsi,r9                                    
0x6776357  mov ebx,r8d                                   
0x677635a  mov [rbp+0x828],rdx                           
0x6776361  mov [rbp+0x768],rcx                           
0x6776368  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677636f  mov rax,[rcx]                                 
0x6776372  mov rax,[rax+0x10]                            
0x6776376  mov dl,0x3E                                   
0x6776378  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677637e  mov [rbp+0x837],al                            
```

Interpretation: Save incoming args: rsi=r9 (vec3*), ebx=r8d (Obj**), [rbp+0x828]=rdx (BuilderSpan*), [rbp+0x768]=rcx (FrameCtx*). Load TLS base from [0x1233E1B0], deref to get TEB, read [rax+0x10], call via [0xF99FFA0] (sub_eea6040) with dl=0x3E, store result al at [rbp+0x837].

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10]. Fields written: [rbp+0x828], [rbp+0x768], [rbp+0x837].

---

## Phase 4 — Data section loads + GS cookie range check (0x6776384..0x67763a3)

Loads globals and performs a bounds check against a GS cookie structure.

```
0x6776384  mov eax,[0x129FB1F8]                          ; [data_129fb1f8]
0x677638a  mov ecx,[0x128767C8]                          ; [data_128767c8]
0x6776390  mov rdx,gs:[0x58]                             
0x6776399  mov rcx,[rdx+rcx*8]                           
0x677639d  cmp eax,[rcx+4]                               
0x67763a3  jg 0x677E052                                  ; -> sub_677e052
```

Interpretation: Load two globals [0x129FB1F8] and [0x128767C8]. Read gs:[0x58] (TEB), use ecx as index into an array at [rdx+rcx*8], compare eax against [rcx+4]. If greater, jump to 0x677E052 (error handler).

Callees: none.
Fields read: [0x129FB1F8], [0x128767C8], gs:[0x58], [rdx+rcx*8], [rcx+4].

---

## Phase 5 — Vector init + search table setup (0x67763a9..0x67763f3)

Initializes a vector at [rbp+0x570] to zero, sets up r12 pointer, loads search table base and entry count.

```
0x67763a9  mov rcx,[rbp+0x968]                           
0x67763b0  lea rax,[rcx+8]                               
0x67763b4  mov [rbp+0x2B8],rax                           
0x67763bb  xorps xmm0,xmm0                               
0x67763be  movaps [rbp+0x570],xmm0                       
0x67763c5  mov qword ptr [rbp+0x110],1                   
0x67763d0  lea r12,[rbp+0x570]                           
0x67763d7  mov [rbp+0x118],r12                           
0x67763de  mov rax,[rcx+0x38]                            
0x67763e2  movzx r8d,word ptr [rcx+0x42]                 
0x67763e7  mov edx,r8d                                   
0x67763ea  shl edx,4                                     
0x67763ed  mov rcx,rax                                   
0x67763f0  test r8d,r8d                                  
0x67763f3  je short 0x6776425                            ; -> loc_6776425
```

Interpretation: rcx = [rbp+0x968] (some object). rax = rcx+8 stored at [rbp+0x2B8]. Zero xmm0, store at [rbp+0x570]. Set [rbp+0x110]=1 (u64), r12 = &[rbp+0x570], [rbp+0x118]=r12. rax = [rcx+0x38] (search table base). r8d = word [rcx+0x42] (entry count). edx = r8d << 4 (entry size * count, stride 0x10). rcx = rax. If count==0 jump to notfound path.

Callees: none.
Fields read: [rbp+0x968], [rcx+0x38], [rcx+0x42]. Fields written: [rbp+0x2B8], [rbp+0x570], [rbp+0x110], [rbp+0x118].

---

## Phase 6 — Search loop (0x67763f5..0x6776423)

Linear search through 0x10-byte entries looking for a match on [r10+0x28] == r8.

```
0x67763f5  mov r8,[0x129FB1F0]                           ; [data_129fb1f0]
0x67763fc  mov r9,rdx                                    
0x67763ff  mov rcx,rax                                   
0x6776402  nop [rax+rax]                                 

loc_6776410:  ; from 6776421
0x6776410  mov r10,[rcx]                                 
0x6776413  cmp [r10+0x28],r8                             
0x6776417  je short 0x6776425                            ; -> loc_6776425
0x6776419  add rcx,0x10                                  
0x677641d  add r9,0xFFFFFFFFFFFFFFF0                     
0x6776421  jne short 0x6776410                           ; -> loc_6776410
0x6776423  jmp short 0x677645D                           ; -> loc_677645d
```

Interpretation: r8 = [0x129FB1F0] (search key). r9 = rdx (remaining count, decremented by 0x10 each iteration). Loop: r10 = [rcx] (entry ptr), compare [r10+0x28] with r8. If equal, jump to found path. Otherwise advance rcx by 0x10, decrement r9 by 0x10, continue if not zero. If exhausted, jump to notfound path.

Callees: none.
Fields read: [0x129FB1F0], [rcx], [r10+0x28]. Fields written: none (registers only).

---

## Phase 7 — Found path: call 0x5679DB0 (0x6776425..0x677645b)

Computes index from found position, calls 0x5679DB0 with index, value-1, and base pointer.

```
loc_6776425:  ; from 67763f3, 6776417
0x6776425  add rdx,rax                                   
0x6776428  cmp rcx,rdx                                   
0x677642b  jae short 0x677645D                           ; -> loc_677645d
0x677642d  sub ecx,eax                                   
0x677642f  shr ecx,4                                     
0x6776432  mov [rbp+0x81C],cx                            
0x6776439  mov byte ptr [rbp+0x81E],1                    
0x6776440  lea rdx,[rbp+0x81C]                           
0x6776447  lea r8,[rbp+0x110]                            
0x677644e  mov rcx,[rbp+0x2B8]                           
0x6776455  call 0x5679DB0                                ; -> sub_5679db0
0x677645a  nop                                           
0x677645b  jmp short 0x6776464                           ; -> loc_6776464
```

Interpretation: rdx += rax (end of table). If rcx >= rdx, go to notfound. Otherwise compute index = (rcx - rax) >> 4 (entry index), store cx at [rbp+0x81C], set flag byte [rbp+0x81E]=1. Call 0x5679DB0(rcx=[rbp+0x2B8], rdx=&[rbp+0x81C], r8=&[rbp+0x110]). Jump to common code.

Callees: 0x5679DB0 (sub_5679db0).
Fields read: [rbp+0x2B8]. Fields written: [rbp+0x81C], [rbp+0x81E].

---

## Phase 8 — Not found path + second call setup (0x677645d..0x6776492)

Not found sets flag to 0. Then calls 0xE86B370 and zeroes locals.

```
loc_677645d:  ; from 6776423, 677642b
0x677645d  mov byte ptr [rbp+0x81E],0                    

loc_6776464:  ; from 677645b
0x6776464  mov rdx,[rbp+0x968]                           
0x677646b  mov rax,[rdx]                                 
0x677646e  mov [rbp-0x40],rax                            
0x6776472  lea rcx,[rbp-0x38]                            
0x6776476  mov r8,[rdx+8]                                
0x677647a  mov rdx,[rbp+0x2B8]                           
0x6776481  call 0xE86B370                                ; -> sub_e86b370
0x6776486  nop                                           
0x6776487  mov qword ptr [rbp+0x40],0                    
0x677648f  xorps xmm6,xmm6                               
0x6776492  movaps [rbp+0x2F0],xmm6                       
```

Interpretation: Not found: set [rbp+0x81E]=0. Common: rdx = [rbp+0x968], rax = [rdx] stored at [rbp-0x40]. lea rcx = [rbp-0x38]. r8 = [rdx+8]. rdx = [rbp+0x2B8]. Call 0xE86B370. Then [rbp+0x40]=0, xmm6=0, store xmm6 at [rbp+0x2F0].

Callees: 0xE86B370 (sub_e86b370).
Fields read: [rbp+0x968], [rdx], [rdx+8], [rbp+0x2B8]. Fields written: [rbp-0x40], [rbp+0x40], [rbp+0x2F0].

---

## Phase 9 — Byte branch on [rsi+0xD8] + al==3 path setup (0x6776499..0x67764d3)

Loads byte [rsi+0xD8], compares against 3. If ==3, enters the aligned-string allocation path.

```
0x6776499  movzx eax,byte ptr [rsi+0xD8]                 
0x67764a0  mov dword ptr [rbp+0x774],0                   
0x67764aa  mov [rbp+0x835],al                            
0x67764b0  cmp al,3                                      
0x67764b2  jne 0x677660C                                 ; -> loc_677660c
0x67764b8  cmp byte ptr [rsi+0xB8],0                     
0x67764bf  mov dword ptr [rbp+0x820],0                   
0x67764c9  mov dword ptr [rbp+0x824],0                   
0x67764d3  je 0x6776620                                  ; -> loc_6776620
```

Interpretation: al = byte [rsi+0xD8]. [rbp+0x774]=0. [rbp+0x835]=al. If al != 3, jump to loc_677660c. If al == 3: check byte [rsi+0xB8]. Zero [rbp+0x820] and [rbp+0x824]. If [rsi+0xB8] == 0, jump to loc_6776620.

Callees: none.
Fields read: [rsi+0xD8], [rsi+0xB8]. Fields written: [rbp+0x774], [rbp+0x835], [rbp+0x820], [rbp+0x824].

---

## Phase 10 — al==3 with [rsi+0xB8]!=0: load u32 pair + allocator call (0x67764d9..0x677651c)

Loads u32 from [rsi+0xC0] and [rsi+0xC4], then calls allocator via [0xF99FFA0] with size 0x30.

```
0x67764d9  mov eax,[rsi+0xC0]                            
0x67764df  mov [rbp+0x824],eax                           
0x67764e5  mov eax,[rsi+0xC4]                            
0x67764eb  mov [rbp+0x820],eax                           
0x67764f1  mov rax,[rbp+0x828]                           
0x67764f8  mov r14,[rax+0x48]                            
0x67764fc  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x6776503  mov rax,[rcx]                                 
0x6776506  mov rax,[rax+8]                               
0x677650a  mov edx,0x30                                  
0x677650f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6776515  nop                                           
0x6776516  mov r15,rax                                   
0x6776519  test rax,rax                                  
0x677651c  je 0x677E017                                  ; -> sub_677e017
```

Interpretation: eax = [rsi+0xC0] stored at [rbp+0x824]. eax = [rsi+0xC4] stored at [rbp+0x820]. rax = [rbp+0x828], r14 = [rax+0x48]. rcx = [0x1233E1A8] (allocator vtable). rax = [rcx], rax = [rax+8] (allocate method). edx = 0x30 (size). Call via [0xF99FFA0]. rax = result stored in r15. If null, jump to 0x677E017 (null handler).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, allocator vcall+8).
Fields read: [rsi+0xC0], [rsi+0xC4], [rbp+0x828], [rax+0x48], [0x1233E1A8], [rcx], [rax+8]. Fields written: [rbp+0x824], [rbp+0x820].

---

## Phase 11 — Initialize allocated 0x30-byte buffer + SmallVector setup (0x6776522..0x677659d)

Stores string constants into the new buffer, sets up a SmallVector-like struct at [rbp+0x570], calls 0x5AB9970.

```
0x6776522  movups xmm0,[0xF5C6AE8]                       ; [data_f5c6ae8] "eCapture texture"
0x6776529  movups [r15+0x10],xmm0                        
0x677652e  movups xmm0,[0xF5C6AD8]                       ; [data_f5c6ad8] "UIStructureVolumeCapture texture"
0x6776535  movups [r15],xmm0                             
0x6776539  mov byte ptr [r15+0x20],0                     
0x677653e  mov eax,[rbp+0x824]                           
0x6776544  mov [rbp+0x570],eax                           
0x677654a  mov eax,[rbp+0x820]                           
0x6776550  mov [rbp+0x574],eax                           
0x6776556  movaps xmm0,[0xF275E70]                       ; [data_f275e70]
0x677655d  movups [rbp+0x578],xmm0                       
0x6776564  mov [rbp+0x588],r15                           
0x677656b  mov qword ptr [rbp+0x590],0                   
0x6776576  mov qword ptr [rbp+0x598],0x20                
0x6776581  mov qword ptr [rbp+0x5A0],0x2F                
0x677658c  lea rdx,[rbp+0x110]                           
0x6776593  lea r8,[rbp+0x570]                            
0x677659a  mov rcx,r14                                   
0x677659d  call 0x5AB9970                                ; -> sub_5ab9970
```

Interpretation: Copy 16 bytes from [0xF5C6AE8] to [r15+0x10], 16 bytes from [0xF5C6AD8] to [r15]. [r15+0x20]=0. Store [rbp+0x824] at [rbp+0x570], [rbp+0x820] at [rbp+0x574]. Copy xmm from [0xF275E70] to [rbp+0x578]. [rbp+0x588]=r15 (pointer to new buffer). [rbp+0x590]=0 (size). [rbp+0x598]=0x20 (capacity). [rbp+0x5A0]=0x2F (some size/count value). Call 0x5AB9970(rcx=r14, rdx=&[rbp+0x110], r8=&[rbp+0x570]).

Callees: 0x5AB9970 (sub_5ab9970).
Fields read: [0xF5C6AE8], [0xF5C6AD8], [rbp+0x824], [rbp+0x820], [0xF275E70], [rbp+0x110], [rbp+0x570]. Fields written: [r15+0x10], [r15], [r15+0x20], [rbp+0x570], [rbp+0x574], [rbp+0x578], [rbp+0x588], [rbp+0x590], [rbp+0x598], [rbp+0x5A0].

---

## Phase 12 — After call 0x5AB9970: reset xmm + string buffer cleanup (0x67765a3..0x677660a)

Resets [rbp+0x110] to zero, saves previous xmm0 to [rbp+0x2F0], handles string buffer size check.

```
0x67765a3  movaps xmm0,[rbp+0x110]                       
0x67765aa  xorps xmm1,xmm1                               
0x67765ad  movaps [rbp+0x110],xmm1                       
0x67765b4  movaps [rbp+0x2F0],xmm0                       
0x67765bb  mov rax,[rbp+0x5A0]                           
0x67765c2  cmp rax,0x10                                  
0x67765c6  jb short 0x6776600                            ; -> loc_6776600
0x67765c8  mov rcx,[rbp+0x588]                           
0x67765cf  lea rdx,[rax+1]                               
0x67765d3  cmp rdx,0x1000                                
0x67765da  jb short 0x67765FB                            ; -> loc_67765fb
0x67765dc  mov r8,[rcx-8]                                
0x67765e0  add rcx,0xFFFFFFFFFFFFFFF8                    
0x67765e4  sub rcx,r8                                    
0x67765e7  cmp rcx,0x20                                  
0x67765eb  jae 0x677E039                                 ; -> sub_677e039
0x67765f1  add rax,0x28                                  
0x67765f5  mov rdx,rax                                   
0x67765f8  mov rcx,r8                                    

loc_67765fb:  ; from 67765da
0x67765fb  call 0xE935700                                ; -> sub_e935700

loc_6776600:  ; from 67765c6
0x6776600  mov dword ptr [rbp+0x774],0x1C                
0x677660a  jmp short 0x6776620                           ; -> loc_6776620
```

Interpretation: xmm0 = [rbp+0x110]. xmm1 = 0. [rbp+0x110]=0. [rbp+0x2F0]=xmm0 (save previous value). rax = [rbp+0x5A0]. If rax < 0x10, skip cleanup. Otherwise: rcx = [rbp+0x588] (buffer ptr), rdx = rax+1, if rdx >= 0x1000: r8 = [rcx-8], rcx -= 8, sub rcx, r8 (compute allocation size), if >= 0x20 jump to 0x677E039. rax += 0x28, rdx = rax, rcx = r8. Call 0xE935700 (likely free). Then [rbp+0x774] = 0x1C and jump to loc_6776620.

Callees: 0xE935700 (sub_e935700).
Fields read: [rbp+0x110], [rbp+0x5A0], [rbp+0x588], [rcx-8]. Fields written: [rbp+0x110], [rbp+0x2F0], [rbp+0x774].

---

## Phase 13 — al!=3 path + loop entry computation (0x677660c..0x67766be)

For al!=3: zero [rbp+0x820]/[rbp+0x824]. Then compute loop bounds from [rsi+0x48] and [rsi+0x40].

```
loc_677660c:  ; from 67764b2
0x677660c  mov dword ptr [rbp+0x820],0                   
0x6776616  mov dword ptr [rbp+0x824],0                   

loc_6776620:  ; from 67764d3, 677660a
0x6776620  mov rax,[rsi+0x48]                            
0x6776624  cmp qword ptr [rax],1                         
0x6776628  mov rdi,[rsi+0x40]                            
0x677662c  sete al                                       
0x677662f  cmp ebx,1                                     
0x6776632  sete cl                                       
0x6776635  and cl,al                                     
0x6776637  mov [rbp+0x836],cl                            
0x677663d  imul rax,[rsi+0x38],0x58                      
0x6776642  add rax,rdi                                   
0x6776645  mov [rbp+0x100],rax                           
0x677664c  lea rbx,[rbp+0x1F0]                           
0x6776653  mov rax,[rbp+0x768]                           
0x677665a  add rax,0x470                                 
0x6776660  mov [rbp+0x778],rax                           
0x6776667  movss xmm7,[0xEEC8060]                        ; [data_eec8060]
0x677666f  movsd xmm8,[0xEFD32F0]                        ; [data_efd32f0]
0x6776678  movaps xmm9,[0xF0A4080]                       ; [data_f0a4080]
0x6776680  movss xmm10,[0xEEC8060]                       ; [data_eec8060]
0x6776689  movsd xmm11,[0xEFD32F0]                       ; [data_efd32f0]
0x6776692  movss xmm13,[0xEFC13A4]                       ; [data_efc13a4] = sub_1000000
0x677669b  movaps xmm14,[0xF0B8740]                      ; [data_f0b8740] = sub_1000000
0x67766a3  movzx eax,byte ptr [rbp+0x978]                
0x67766aa  mov [rbp+0x7BC],eax                           
0x67766b0  lea r14,[rbp+0xA0]                            
0x67766b7  lea r13,[rbp+0x300]                           
0x67766be  jmp short 0x67766D2                           ; -> loc_67766d2
```

Interpretation: [rbp+0x820]=0, [rbp+0x824]=0. rax = [rsi+0x48], compare qword [rax] with 1, sete al. rdi = [rsi+0x40]. cmp ebx,1, sete cl. and cl,al -> [rbp+0x836]. rax = [rsi+0x38] * 0x58 + rdi -> [rbp+0x100] (loop end). rbx = &[rbp+0x1F0]. rax = [rbp+0x768] + 0x470 -> [rbp+0x778] (loop start). Load constants into xmm7-xmm14 from data sections. eax = byte [rbp+0x978] -> [rbp+0x7BC]. r14 = &[rbp+0xA0], r13 = &[rbp+0x300]. Jump to loop head.

Callees: none.
Fields read: [rsi+0x48], [rax], [rsi+0x40], [rsi+0x38], [rbp+0x768], [rbp+0x978]. Fields written: [rbp+0x820], [rbp+0x824], [rbp+0x836], [rbp+0x100], [rbp+0x778], [rbp+0x7BC].

---

## Phase 14 — Loop head + per-entry dispatch (0x67766c0..0x67766d9)

Loop entry: advance rdi by 0x58, compare against end, dispatch based on byte [rdi+0x28].

```
loc_67766c0  lea r14,[rbp+0xA0]                            
loc_67766c7  lea r13,[rbp+0x300]                           

loc_67766ce:  ; from 67766fa, 6776708
0x67766ce  add rdi,0x58                                  

loc_67766d2:  ; from 67766be
0x67766d2  cmp rdi,[rbp+0x100]                           
0x67766d9  je 0x677DF5C                                  ; -> sub_677df5c
  ... (--max 100)
```

Interpretation: Loop back edge: r14=&[rbp+0xA0], r13=&[rbp+0x300]. Advance rdi by 0x58 (next entry). If rdi == [rbp+0x100] (end), exit to 0x677DF5C.

Callees: none.
Fields read: [rbp+0x100]. Fields written: none.

---

## Phase 15 — Per-entry dispatch + xmm15 load (0x67766df..0x6776710)

Reads byte [rdi+0x28]: 0=skip, !=1=error, 1=check pointers, then load xmm15 from [rdi+0x3C].

```
0x67766df  movzx eax,byte ptr [rdi+0x28]                 
0x67766e3  test eax,eax                                  
0x67766e5  je short 0x6776700                            ; -> loc_6776700
0x67766e7  cmp eax,1                                     
0x67766ea  jne 0x677E027                                 ; -> sub_677e027
0x67766f0  lea rax,[rdi+0x18]                            
0x67766f4  cmp qword ptr [rax],0                         
0x67766f8  jne short 0x677670A                           ; -> loc_677670a
0x67766fa  jmp short 0x67766CE                           ; -> sub_67766ce
0x67766fc  nop [rax]                                     

loc_6776700:  ; from 67766e5
0x6776700  lea rax,[rdi+0x10]                            
0x6776704  cmp qword ptr [rax],0                         
0x6776708  je short 0x67766CE                            ; -> sub_67766ce

loc_677670a:  ; from 67766f8
0x677670a  movsd xmm15,[rdi+0x3C]                        
0x6776710  movsd [rbp+0x2E0],xmm15                       
```

Interpretation: eax = byte [rdi+0x28]. If 0, jump to loc_6776700 (check [rdi+0x10]). If !=1, jump to 0x677E027 (error). If ==1: rax = &[rdi+0x18], if [rax] != 0 go to body; else skip to loop increment. At loc_6776700: rax = &[rdi+0x10], if [rax] == 0 skip. Body: xmm15 = [rdi+0x3C] (double), store at [rbp+0x2E0].

Callees: none.
Fields read: [rdi+0x28], [rdi+0x18], [rdi+0x10], [rdi+0x3C]. Fields written: [rbp+0x2E0].

---

## Phase 16 — Vector setup + per-element SIMD math (0x6776719..0x6776794)

Initializes float vector, computes SIMD combinations of xmm15 and xmm12 (from [rdi+0x44]), stores results at [rbp+0x598] and [rbp+0x5A8].

```
0x6776719  mov dword ptr [rbp+0x570],0x3F800000          
0x6776723  lea rax,[rbp+0x574]                           
0x677672a  movups [rax],xmm6                             
0x677672d  mov dword ptr [rbp+0x584],0x3F800000          
0x6776737  movups [rax+0x14],xmm6                        
0x677673b  movaps xmm0,xmm15                             
0x677673f  mulps xmm0,xmm6                               
0x6776742  movaps xmm1,xmm0                              
0x6776745  shufps xmm1,xmm0,0xE1                         
0x6776749  addps xmm1,xmm15                              
0x677674d  movss xmm12,[rdi+0x44]                        
0x6776753  movss [rbp+0x2E8],xmm12                       
0x677675c  movaps xmm2,xmm12                             
0x6776760  shufps xmm2,xmm12,0                           
0x6776765  mulps xmm2,xmm7                               
0x6776768  movaps xmm3,xmm0                              
0x677676b  shufps xmm3,xmm0,0x55                         
0x677676f  unpcklps xmm0,xmm0                            
0x6776772  addps xmm0,xmm3                               
0x6776775  addps xmm0,xmm2                               
0x6776778  addps xmm0,xmm8                               
0x677677c  shufps xmm2,xmm2,0x55                         
0x6776780  addps xmm2,xmm1                               
0x6776783  movaps xmm1,xmm9                              
0x6776787  movlhps xmm1,xmm2                             
0x677678a  addps xmm1,xmm7                               
0x677678d  movups [rbp+0x598],xmm1                       
0x6776794  movlps [rbp+0x5A8],xmm0                       
```

Interpretation: [rbp+0x570]=0x3F800000 (1.0f), [rax]=[rbp+0x574] zeroed by xmm6, [rbp+0x584]=0x3F800000 (1.0f), [rax+0x14]=[rbp+0x588] zeroed. xmm0=xmm15*1. xmm1=shuffle(xmm0,0xE1)+xmm15. xmm12=[rdi+0x44], stored at [rbp+0x2E8]. xmm2=xmm12*1*broadcast*xmm7. xmm0 = xmm0 + shuffle(xmm0,0x55) + xmm2 + xmm8 (horizontal-ish sum). xmm2 = shuffle(xmm2,0x55) + xmm1. xmm1 = xmm9; movlhps xmm1,xmm2; xmm1 += xmm7. Store xmm1 at [rbp+0x598], low 64 bits of xmm0 at [rbp+0x5A8].

Callees: none.
Fields read: [rdi+0x44], xmm7, xmm8, xmm9, xmm6. Fields written: [rbp+0x570], [rbp+0x574], [rbp+0x584], [rbp+0x588], [rbp+0x2E8], [rbp+0x598], [rbp+0x5A8].

---

## Phase 17 — Call 0xAA6580 (first) (0x677679b..0x67767aa)

Calls 0xAA6580 with rcx=r14 (&[rbp+0xA0]), rdx=[rsi+0x78], r8=r12 (&[rbp+0x570]).

```
0x677679b  mov rcx,r14                                   
0x677679e  lea rdx,[rsi+0x78]                            
0x67767a2  mov r8,r12                                    
0x67767a5  call 0xAA6580                                 ; -> sub_aa6580
0x67767aa  nop                                           
```

Interpretation: Call 0xAA6580(rcx=r14=&[rbp+0xA0], rdx=&[rsi+0x78], r8=r12=&[rbp+0x570]). This appears to be a vector transform or interpolation function operating on the data just computed.

Callees: 0xAA6580 (sub_aa6580).
Fields read: [rsi+0x78]. Fields written: none (registers only).

---

## Phase 18 — Float compare + second call setup (0x67767ab..0x677680a)

Compares [rdi+0x48] against xmm10. If not equal / not ordered, compute new vector values and call 0xAA6580 again.

```
0x67767ab  movss xmm0,[rdi+0x48]                         
0x67767b0  ucomiss xmm0,xmm10                            
0x67767b4  jne short 0x67767BC                           ; -> loc_67767bc
0x67767b6  jnp 0x6776848                                 ; -> loc_6776848

loc_67767bc:  ; from 67767b4
0x67767bc  movaps xmm1,xmm0                              
0x67767bf  shufps xmm1,xmm0,0                            
0x67767c3  mulps xmm1,xmm7                               
0x67767c6  movss [rbp+0x570],xmm0                        
0x67767ce  movq xmm2,xmm1                                
0x67767d2  shufps xmm1,xmm1,0x55                         
0x67767d6  movups [rbp+0x574],xmm1                       
0x67767dd  movss [rbp+0x584],xmm0                        
0x67767e5  movups [rbp+0x588],xmm1                       
0x67767ec  movdqu [rbp+0x598],xmm2                       
0x67767f4  movsd [rbp+0x5A8],xmm11                       
0x67767fd  lea rcx,[rbp+0x110]                           
0x6776804  mov rdx,r14                                   
0x6776807  mov r8,r12                                    
0x677680a  call 0xAA6580                                 ; -> sub_aa6580
```

Interpretation: xmm0 = [rdi+0x48] (float). ucomiss xmm0, xmm10. If not equal (jne) or unordered (jnp), take different paths. At bc: xmm1 = broadcast(xmm0) * xmm7. Store xmm0 at [rbp+0x570], xmm1 at [rbp+0x574] and [rbp+0x588], xmm0 at [rbp+0x584], xmm2 (movq of xmm1) at [rbp+0x598], xmm11 at [rbp+0x5A8]. Call 0xAA6580(rcx=&[rbp+0x110], rdx=r14, r8=r12).

Callees: 0xAA6580 (sub_aa6580) — second call.
Fields read: [rdi+0x48], xmm10, xmm7, xmm11. Fields written: [rbp+0x570], [rbp+0x574], [rbp+0x584], [rbp+0x588], [rbp+0x598], [rbp+0x5A8].

---

## Phase 19 — Store xmm results to [rbp+0xA0..0xD0] (0x677680f..0x6776841)

Stores the four xmm registers from [rbp+0x110..0x140] into [rbp+0xA0..0xD0].

```
0x677680f  nop                                           
0x6776810  movaps xmm0,[rbp+0x110]                       
0x6776817  movaps xmm1,[rbp+0x120]                       
0x677681e  movaps xmm2,[rbp+0x130]                       
0x6776825  movaps xmm3,[rbp+0x140]                       
0x677682c  movaps [rbp+0xA0],xmm0                        
0x6776833  movaps [rbp+0xB0],xmm1                        
0x677683a  movaps [rbp+0xC0],xmm2                        
0x6776841  movaps [rbp+0xD0],xmm3                        
```

Interpretation: Load xmm0-xmm3 from [rbp+0x110], [rbp+0x120], [rbp+0x130], [rbp+0x140] (results from second 0xAA6580 call). Store them at [rbp+0xA0], [rbp+0xB0], [rbp+0xC0], [rbp+0xD0].

Callees: none.
Fields read: [rbp+0x110], [rbp+0x120], [rbp+0x130], [rbp+0x140]. Fields written: [rbp+0xA0], [rbp+0xB0], [rbp+0xC0], [rbp+0xD0].

---

## Phase 20 — Call 0x678C4C0 + set [rbp+0x108] (0x6776848..0x6776873)

Calls 0x678C4C0 with rdx=[rax] where rax=[rbp+0x828], then sets [rbp+0x108] = &[rbp-0x40].

```
loc_6776848:  ; from 67767b6
0x6776848  mov rax,[rbp+0x828]                           
0x677684f  mov rdx,[rax]                                 
0x6776852  mov [rsp+0x20],rdi                            
0x6776857  lea rcx,[rbp+0x48]                            
0x677685b  mov r8,[rbp+0x960]                            
0x6776862  mov r9,[rbp+0x968]                            
0x6776869  call 0x678C4C0                                ; -> sub_678c4c0
0x677686e  nop                                           
0x677686f  lea rax,[rbp-0x40]                            
0x6776873  mov [rbp+0x108],rax                           
```

Interpretation: rax = [rbp+0x828] (BuilderSpan* saved earlier). rdx = [rax] (first qword of span object). [rsp+0x20]=rdi (save current loop entry). rcx = &[rbp+0x48]. r8 = [rbp+0x960]. r9 = [rbp+0x968]. Call 0x678C4C0. Then [rbp+0x108] = &[rbp-0x40].

Callees: 0x678C4C0 (sub_678c4c0).
Fields read: [rbp+0x828], [rax], [rbp+0x960], [rbp+0x968]. Fields written: [rsp+0x20], [rbp+0x108].

---

## Phase 21 — [rbp+0x81E] flag check + conditional call 0x5679DB0 (0x677687a..0x67768bb)

Checks byte flag [rbp+0x81E]. If 1 and [rdi+0x4C] > 0, call 0x5679DB0 again.

```
0x677687a  cmp byte ptr [rbp+0x81E],1                    
0x6776881  jne short 0x67768D6                           ; -> loc_67768d6
0x6776883  movss xmm0,[rdi+0x4C]                         
0x6776888  xorps xmm1,xmm1                               
0x677688b  ucomiss xmm0,xmm1                             
0x677688e  jbe short 0x67768D6                           ; -> loc_67768d6
0x6776890  shufps xmm0,xmm0,0                            
0x6776894  movaps [rbp+0x570],xmm0                       
0x677689b  mov qword ptr [rbp+0x110],1                   
0x67768a6  mov [rbp+0x118],r12                           
0x67768ad  mov rcx,[rbp+0x2B8]                           
0x67768b4  lea rdx,[rbp+0x81C]                           
0x67768bb  lea r8,[rbp+0x110]                            
```

Interpretation: If [rbp+0x81E] != 1, skip to loc_67768d6. If [rdi+0x4C] <= 0 (ucomiss, jbe), skip. Otherwise: broadcast [rdi+0x4C] to [rbp+0x570], set [rbp+0x110]=1, [rbp+0x118]=r12. Call 0x5679DB0(rcx=[rbp+0x2B8], rdx=&[rbp+0x81C], r8=&[rbp+0x110]).

Callees: 0x5679DB0 (sub_5679db0) — conditional second call.
Fields read: [rbp+0x81E], [rdi+0x4C], [rbp+0x2B8], [rbp+0x110]. Fields written: [rbp+0x570], [rbp+0x110], [rbp+0x118].

---

## Phase 22 — Call 0x5679DB0 (conditional) + store [rbp+0x968] (0x67768bb..0x67768d6)

Completes the conditional call started in Phase 21, then stores [rbp+0x968] at [rbp+0x108].

```
0x67768bb  lea r8,[rbp+0x110]                            
0x67768c2  call 0x5679DB0                                ; -> sub_5679db0
0x67768c7  nop                                           
0x67768c8  mov rax,[rbp+0x968]                           
0x67768cf  mov [rbp+0x108],rax                           
```

Interpretation: Call 0x5679DB0(rcx=[rbp+0x2B8], rdx=&[rbp+0x81C], r8=&[rbp+0x110]). Then [rbp+0x108] = [rbp+0x968].

Callees: 0x5679DB0 (sub_5679db0).
Fields read: [rbp+0x2B8], [rbp+0x81C], [rbp+0x110], [rbp+0x968]. Fields written: [rbp+0x108].

---

## Phase 23 — Store [rbp+0x980] + setup locals + byte branch (0x67768d6..0x6776916)

Stores [rbp+0x980] at [rbp+0x2C0], r14 at [rbp+0x2C8], sets up pointers, then branches on [rsi+0xB8] and [rbp+0x970].

```
0x67768d6  mov rax,[rbp+0x980]                           
0x67768dd  mov [rbp+0x2C0],rax                           
0x67768e4  mov [rbp+0x2C8],r14                           
0x67768eb  lea rax,[rbp+0x48]                            
0x67768ef  mov [rbp+0x2D0],rax                           
0x67768f6  lea rax,[rbp+0x108]                           
0x67768fd  mov [rbp+0x2D8],rax                           
0x6776904  movzx eax,byte ptr [rsi+0xB8]                 
0x677690b  cmp byte ptr [rbp+0x970],0                    
0x6776912  je short 0x6776970                            ; -> loc_6776970
0x6776914  test al,al                                    
0x6776916  je 0x67769C9                                  ; -> loc_67769c9
```

Interpretation: [rbp+0x2C0] = [rbp+0x980]. [rbp+0x2C8] = r14. [rbp+0x2D0] = &[rbp+0x48]. [rbp+0x2D8] = &[rbp+0x108]. al = byte [rsi+0xB8]. If [rbp+0x970] == 0, jump to loc_6776970. If al == 0, jump to loc_67769c9.

Callees: none.
Fields read: [rbp+0x980], [rbp+0x970], [rsi+0xB8]. Fields written: [rbp+0x2C0], [rbp+0x2C8], [rbp+0x2D0], [rbp+0x2D8].

---

## Phase 24 — al!=0 && [rbp+0x970]!=0: increment counter + shared_ptr refcount (0x677691c..0x677696d)

Increments a u16 counter at [rbp+0x988], checks [rbp+0x835]==3 and [rsi+0xD8]==3, then does shared_ptr refcount increment via lock inc.

```
0x677691c  mov rdx,[rbp+0x988]                           
0x6776923  movzx eax,word ptr [rdx]                      
0x6776926  lea ecx,[rax+1]                               
0x6776929  mov [rdx],cx                                  
0x677692c  cmp byte ptr [rbp+0x835],3                    
0x6776933  jne 0x6776D58                                 ; -> loc_6776d58
0x6776939  cmp byte ptr [rsi+0xD8],3                     
0x6776940  jne 0x677E033                                 ; -> sub_677e033
0x6776946  movaps [rbp+0x780],xmm6                       
0x677694d  mov rcx,[rbp+0x2F8]                           
0x6776954  test rcx,rcx                                  
0x6776957  je 0x67779BC                                  ; -> loc_67779bc
0x677695d  lock inc dword ptr [rcx+8]                    
0x6776961  mov rdx,[rbp+0x2F8]                           
0x6776968  jmp 0x67779BE                                 ; -> loc_67779be
0x677696d  nop [rax]                                     
```

Interpretation: rdx = [rbp+0x988]. eax = word [rdx], ecx = eax+1, store cx back to [rdx] (increment u16 counter). If [rbp+0x835] != 3, jump to loc_6776D58. If [rsi+0xD8] != 3, jump to 0x677E033. [rbp+0x780] = xmm6 (zero). rcx = [rbp+0x2F8]. If rcx == 0, jump to loc_67779BC. Otherwise lock inc dword [rcx+8] (shared_ptr refcount increment). rdx = [rbp+0x2F8], jump to loc_67779BE.

Callees: none.
Fields read: [rbp+0x988], [rdx], [rbp+0x835], [rsi+0xD8], [rbp+0x2F8], [rcx+8]. Fields written: [rdx] (counter), [rbp+0x780].

---

## Phase 25 — al!=0 && [rbp+0x970]!=0 && al!=0 path (0x6776970..0x67769c4)

Same pattern as Phase 24 but with different jump targets (0x6776F95 / 0x677E02D / loc_6777A3D / loc_6777A3F).

```
loc_6776970:  ; from 6776912
0x6776970  test al,al                                    
0x6776972  je 0x6776BE8                                  ; -> loc_6776be8
0x6776978  mov rdx,[rbp+0x988]                           
0x677697f  movzx eax,word ptr [rdx]                      
0x6776982  lea ecx,[rax+1]                               
0x6776985  mov [rdx],cx                                  
0x6776988  cmp byte ptr [rbp+0x835],3                    
0x677698f  jne 0x6776F95                                 ; -> loc_6776f95
0x6776995  cmp byte ptr [rsi+0xD8],3                     
0x677699c  jne 0x677E02D                                 ; -> sub_677e02d
0x67769a2  movaps [rbp+0x780],xmm6                       
0x67769a9  mov rcx,[rbp+0x2F8]                           
0x67769b0  test rcx,rcx                                  
0x67769b3  je 0x6777A3D                                  ; -> loc_6777a3d
0x67769b9  lock inc dword ptr [rcx+8]                    
0x67769bd  mov rdx,[rbp+0x2F8]                           
0x67769c4  jmp 0x6777A3F                                 ; -> loc_6777a3f
```

Interpretation: test al,al; if al==0 jump to loc_6776BE8. Otherwise: increment u16 counter at [rbp+0x988]. If [rbp+0x835] != 3, jump to loc_6776F95. If [rsi+0xD8] != 3, jump to 0x677E02D. [rbp+0x780] = xmm6. rcx = [rbp+0x2F8]. If rcx == 0 jump to loc_6777A3D. lock inc dword [rcx+8]. rdx = [rbp+0x2F8], jump to loc_6777A3F.

Callees: none.
Fields read: [rbp+0x988], [rdx], [rbp+0x835], [rsi+0xD8], [rbp+0x2F8], [rcx+8]. Fields written: [rdx] (counter), [rbp+0x780].

---

## Phase 26 — al==0 && [rsi+0xE0]==1: SIMD adjust + call 0x678CF10 + call 0x678E1D0 (0x67769c9..0x6776a2c)

When [rsi+0xB8]==0 and [rsi+0xE0]==1: addss xmm12,xmm13, addps xmm15,xmm14, store to [rbp+0x4A0/0x4A8], call 0x678CF10, then call 0x678E1D0.

```
loc_67769c9:  ; from 6776916
0x67769c9  cmp byte ptr [rsi+0xE0],1                     
0x67769d0  jne 0x6777119                                 ; -> loc_6777119
0x67769d6  addss xmm12,xmm13                             
0x67769db  addps xmm15,xmm14                             
0x67769df  movlps [rbp+0x4A0],xmm15                      
0x67769e7  movss [rbp+0x4A8],xmm12                       
0x67769f0  lea rcx,[rbp+0x2C0]                           
0x67769f7  mov rdx,r13                                   
0x67769fa  call 0x678CF10                                ; -> sub_678cf10
0x67769ff  nop                                           
0x6776a00  lea rax,[rbp+0x4A0]                           
0x6776a07  mov [rsp+0x20],rax                            
0x6776a0c  lea r14,[rbp+0x110]                           
0x6776a13  mov rcx,r14                                   
0x6776a16  lea rdx,[rbp+0x3E0]                           
0x6776a1d  lea r8,[rbp+0x388]                            
0x6776a24  mov r9,r13                                    
0x6776a27  call 0x678E1D0                                ; -> sub_678e1d0
0x6776a2c  nop                                           
```

Interpretation: If byte [rsi+0xE0] != 1, jump to loc_6777119. Otherwise: xmm12 += xmm13 (addss), xmm15 += xmm14 (addps). Store low 64 bits of xmm15 at [rbp+0x4A0], low 32 bits of xmm12 at [rbp+0x4A8]. rcx = &[rbp+0x2C0], rdx = r13 (&[rbp+0x300]). Call 0x678CF10. [rsp+0x20] = &[rbp+0x4A0]. r14 = &[rbp+0x110]. Call 0x678E1D0(rcx=r14, rdx=&[rbp+0x3E0], r8=&[rbp+0x388], r9=r13).

Callees: 0x678CF10 (sub_678cf10), 0x678E1D0 (sub_678e1d0).
Fields read: [rsi+0xE0], xmm13, xmm14, xmm12, xmm15, [rbp+0x2C0], r13, [rbp+0x110], [rbp+0x3E0], [rbp+0x388]. Fields written: [rbp+0x4A0], [rbp+0x4A8], [rsp+0x20].

---

## Phase 27 — Copy from 0x3E0 struct to [rbx+0x68..0xAF] (0x6776a2d..0x6776a8e)

Reads fields from [rbp+0x3E0] struct and copies to [rbx+0x68..0xAF] region. Also saves byte [rbp+0x44C] and u16 [rbp+0x490].

```
0x6776a2d  lea rcx,[rbp+0x3E0]                           
0x6776a34  mov eax,[rcx+0x68]                            
0x6776a37  mov [rbx+0x78],eax                            
0x6776a3a  movups xmm0,[rcx+0x58]                        
0x6776a3e  movups [rbx+0x68],xmm0                        
0x6776a42  movzx eax,byte ptr [rbp+0x44C]                
0x6776a49  mov [rbp+0x26C],al                            
0x6776a4f  movups xmm0,[rbp+0x450]                       
0x6776a56  movups [rbp+0x270],xmm0                       
0x6776a5d  movups xmm0,[rcx+0x80]                        
0x6776a64  movups xmm1,[rcx+0x90]                        
0x6776a6b  movups xmm2,[rcx+0x9F]                        
0x6776a72  movups [rbx+0xAF],xmm2                        
0x6776a79  movups [rbx+0xA0],xmm1                        
0x6776a80  movups [rbx+0x90],xmm0                        
0x6776a87  movzx eax,word ptr [rbp+0x490]                
0x6776a8e  mov [rbp+0x2B0],ax                            
```

Interpretation: rcx = &[rbp+0x3E0]. eax = [rcx+0x68], store at [rbx+0x78]. xmm0 = [rcx+0x58], store at [rbx+0x68]. al = byte [rbp+0x44C], store at [rbp+0x26C]. xmm0 = [rbp+0x450], store at [rbp+0x270]. xmm0 = [rcx+0x80], xmm1 = [rcx+0x90], xmm2 = [rcx+0x9F]. Store xmm2 at [rbx+0xAF], xmm1 at [rbx+0xA0], xmm0 at [rbx+0x90]. ax = word [rbp+0x490], store at [rbp+0x2B0].

Callees: none.
Fields read: [rcx+0x68], [rcx+0x58], [rbp+0x44C], [rbp+0x450], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x490]. Fields written: [rbx+0x78], [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0xAF], [rbx+0xA0], [rbx+0x90], [rbp+0x2B0].

---

## Phase 28 — Call 0x67E23F0 + call 0x678E420 (0x6776a95..0x6776ac0)

Calls 0x67E23F0 with rcx=r13, then calls 0x678E420 with multiple output pointers.

```
0x6776a95  mov rcx,r13                                   
0x6776a98  call 0x67E23F0                                ; -> sub_67e23f0
0x6776a9d  nop                                           
0x6776a9e  mov [rsp+0x20],r14                            
0x6776aa3  mov rcx,r12                                   
0x6776aa6  lea rdx,[rbp+0x200]                           
0x6776aad  lea r8,[rbp+0x1A8]                            
0x6776ab4  lea r9,[rbp+0x120]                            
0x6776abb  call 0x678E420                                ; -> sub_678e420
0x6776ac0  nop                                           
```

Interpretation: rcx = r13 (&[rbp+0x300]). Call 0x67E23F0. [rsp+0x20] = r14. rcx = r12 (&[rbp+0x570]). rdx = &[rbp+0x200]. r8 = &[rbp+0x1A8]. r9 = &[rbp+0x120]. Call 0x678E420.

Callees: 0x67E23F0 (sub_67e23f0), 0x678E420 (sub_678e420).
Fields read: none (registers only). Fields written: [rsp+0x20].

---

## Phase 29 — Copy [rbx+0x68..0xAF] to [rbp+0x6B8..0x710] (0x6776ac1..0x6776ace)

Copies data from [rbx+0x68..0xAF] to [rbp+0x6B8..0x710], also saves byte [rbp+0x26C] and u16 [rbp+0x2B0].

```
0x6776ac1  mov eax,[rbx+0x78]                            
0x6776ac4  lea rcx,[rbp+0x6B8]                           
0x6776acb  mov [rcx+0x10],eax                            
0x6776ace  movups xmm0,[rbx+0x68]                        
... (--max 100)
```

Interpretation: eax = [rbx+0x78], store at [rcx+0x10] where rcx = &[rbp+0x6B8], so [rbp+0x6C8] = [rbx+0x78]. xmm0 = [rbx+0x68], stored to [rcx] = [rbp+0x6B8] (continues in next chunk).

Callees: none.
Fields read: [rbx+0x78], [rbx+0x68]. Fields written: [rbp+0x6C8], [rbp+0x6B8].

---

## Phase 29 continued — Copy [rbx+0x68..0xAF] to [rbp+0x6B8..0x710] (0x6776ace..0x6776b1e)

Continues copying data from [rbx+0x68..0xAF] to [rbp+0x6B8..0x710], saves byte [rbp+0x26C] and u16 [rbp+0x2B0].

```
0x6776ace  movups xmm0,[rbx+0x68]                        
0x6776ad2  movups [rcx],xmm0                             ; W a0+0x0
0x6776ad5  movzx eax,byte ptr [rbp+0x26C]                
0x6776adc  mov [rbp+0x6CC],al                            
0x6776ae2  movups xmm0,[rbp+0x270]                       
0x6776ae9  movups [rbp+0x6D0],xmm0                       
0x6776af0  movups xmm0,[rbx+0x90]                        
0x6776af7  movups xmm1,[rbx+0xA0]                        
0x6776afe  movups xmm2,[rbx+0xAF]                        
0x6776b05  lea rax,[rbp+0x6E0]                           
0x6776b0c  movups [rax+0x1F],xmm2                        
0x6776b10  movups [rax+0x10],xmm1                        
0x6776b14  movups [rax],xmm0                             
0x6776b17  movzx eax,word ptr [rbp+0x2B0]                
0x6776b1e  mov [rbp+0x710],ax                            
```

Interpretation: xmm0 = [rbx+0x68], stored at [rcx] = [rbp+0x6B8]. al = byte [rbp+0x26C], stored at [rbp+0x6CC]. xmm0 = [rbp+0x270], stored at [rbp+0x6D0]. xmm0 = [rbx+0x90], xmm1 = [rbx+0xA0], xmm2 = [rbx+0xAF]. rax = &[rbp+0x6E0]. Store xmm2 at [rax+0x1F] = [rbp+0x6FF], xmm1 at [rax+0x10] = [rbp+0x6F0], xmm0 at [rax] = [rbp+0x6E0]. ax = word [rbp+0x2B0], stored at [rbp+0x710].

Callees: none.
Fields read: [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0x90], [rbx+0xA0], [rbx+0xAF], [rbp+0x2B0]. Fields written: [rbp+0x6B8], [rbp+0x6CC], [rbp+0x6D0], [rbp+0x6FF], [rbp+0x6F0], [rbp+0x6E0], [rbp+0x710].

---

## Phase 30 — Call 0x5ABA5C0 + zero xmm regs (0x6776b25..0x6776b95)

Calls 0x5ABA5C0 to get pass object, then zeros xmm registers [rbp+0x300..0x3C0].

```
0x6776b25  mov rax,[rbp+0x828]                           
0x6776b2c  mov rcx,[rax+0x10]                            
0x6776b30  mov eax,0x9D0                                 
0x6776b35  add rcx,rax                                   
0x6776b38  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x6776b3d  nop                                           
0x6776b3e  mov r14,rax                                   
0x6776b41  movaps [rbp+0x3B0],xmm6                       
0x6776b48  movaps [rbp+0x3A0],xmm6                       
0x6776b4f  movaps [rbp+0x390],xmm6                       
0x6776b56  movaps [rbp+0x380],xmm6                       
0x6776b5d  movaps [rbp+0x370],xmm6                       
0x6776b64  movaps [rbp+0x360],xmm6                       
0x6776b6b  movaps [rbp+0x350],xmm6                       
0x6776b72  movaps [rbp+0x340],xmm6                       
0x6776b79  movaps [rbp+0x330],xmm6                       
0x6776b80  movaps [rbp+0x320],xmm6                       
0x6776b87  movaps [rbp+0x310],xmm6                       
0x6776b8e  movaps [rbp+0x300],xmm6                       
0x6776b95  mov qword ptr [rbp+0x3C0],0                   
```

Interpretation: rax = [rbp+0x828] (BuilderSpan*). rcx = [rax+0x10]. rcx += 0x9D0. Call 0x5ABA5C0(rcx). Result (pass object) stored in r14. Then zero xmm6 into [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x300], and [rbp+0x3C0]=0.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x828], [rax+0x10], xmm6. Fields written: [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x300], [rbp+0x3C0].

---

## Phase 31 — TLS/cookie read + feature flag (0x6776ba0..0x6776bb7)

Reads TLS data, calls via [0xF99FFA0] with dl=0x4A, stores result at [rbp+0x838].

```
0x6776ba0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6776ba7  mov rax,[rcx]                                 
0x6776baa  mov rax,[rax+0x10]                            
0x6776bae  mov dl,0x4A                                   
0x6776bb0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6776bb6  nop                                           
0x6776bb7  mov [rbp+0x838],al                            
```

Interpretation: rcx = [0x1233E1B0] (TLS base). rax = [rcx], rax = [rax+0x10]. dl = 0x4A. Call via [0xF99FFA0] (sub_eea6040). Store al at [rbp+0x838] (feature flag).

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10]. Fields written: [rbp+0x838].

---

## Phase 32 — Pass object items buffer check + write u16 (0x6776bbd..0x6776be3)

Checks if pass object items buffer has room, writes u16 from [rbp+0x710] at [rdx], advances pointer by 2.

```
0x6776bbd  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6776bc4  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6776bcb  je 0x677829B                                  ; -> loc_677829b
0x6776bd1  movzx eax,word ptr [rbp+0x710]                
0x6776bd8  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x6776bdb  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6776be3  jmp 0x67782AF                                 ; -> loc_67782af
```

Interpretation: rdx = [r14+0x8A8] (items write cursor). Compare with [r14+0x8B0] (items end). If equal, jump to 0x677829B (grow/overflow). Otherwise: eax = word [rbp+0x710], store ax at [rdx] (write u16 to items buffer), [r14+0x8A8] += 2 (advance cursor). Jump to 0x67782AF.

Callees: none.
Fields read: [r14+0x8A8], [r14+0x8B0], [rbp+0x710]. Fields written: [rdx] (items buffer), [r14+0x8A8].

---

## Phase 33 — al!=0 && [rbp+0x970]==0 path: [rsi+0xE0]==1 check + calls (0x6776be8..0x6776c26)

When byte [rsi+0xB8]!=0 was false (al==0) and [rbp+0x970]==0: check [rsi+0xE0]==1, call 0x678CF10, then call 0x678F640.

```
loc_6776be8:  ; from 6776972
0x6776be8  cmp byte ptr [rsi+0xE0],1                     
0x6776bef  jne 0x6777339                                 ; -> loc_6777339
0x6776bf5  lea rcx,[rbp+0x2C0]                           
0x6776bfc  lea rdx,[rbp+0x110]                           
0x6776c03  call 0x678CF10                                ; -> sub_678cf10
0x6776c08  nop                                           
0x6776c09  mov rcx,r12                                   
0x6776c0c  lea rdx,[rbp+0x1F0]                           
0x6776c13  lea r8,[rbp+0x198]                           
0x6776c1a  lea r9,[rbp+0x110]                           
0x6776c21  call 0x678F640                                ; -> sub_678f640
0x6776c26  nop                                           
```

Interpretation: If byte [rsi+0xE0] != 1, jump to loc_6777339. Otherwise: rcx = &[rbp+0x2C0], rdx = &[rbp+0x110]. Call 0x678CF10. Then rcx = r12 (&[rbp+0x570]), rdx = &[rbp+0x1F0], r8 = &[rbp+0x198], r9 = &[rbp+0x110]. Call 0x678F640.

Callees: 0x678CF10 (sub_678cf10), 0x678F640 (sub_678f640).
Fields read: [rsi+0xE0], [rbp+0x2C0], [rbp+0x110], [rbp+0x1F0], [rbp+0x198]. Fields written: none.

---

## Phase 34 — Copy [rbx+0x68..0x9F] to [rbp+0x6B0..0x574] + call 0x5ABA5C0 (0x6776c27..0x6776cae)

Copies from [rbx+0x68..0x9F] to [rbp+0x6B0..0x574+0x183], saves byte [rbp+0x25C] and u16 [rbp+0x2A0], then calls 0x5ABA5C0 again.

```
0x6776c27  mov eax,[rbx+0x68]                            
0x6776c2a  lea rcx,[rbp+0x6B0]                           
0x6776c31  mov [rcx+0x10],eax                            
0x6776c34  movups xmm0,[rbx+0x58]                        
0x6776c38  movups [rcx],xmm0                             
0x6776c3b  movzx eax,byte ptr [rbp+0x25C]                
0x6776c42  mov [rbp+0x6C4],al                            
0x6776c48  movups xmm0,[rbp+0x260]                       
0x6776c4f  movups [rbp+0x6C8],xmm0                       
0x6776c56  movups xmm0,[rbx+0x80]                        
0x6776c5d  movups xmm1,[rbx+0x90]                        
0x6776c64  movups xmm2,[rbx+0x9F]                        
0x6776c6b  lea rax,[rbp+0x574]                           
0x6776c72  movups [rax+0x183],xmm2                       
0x6776c79  movups [rax+0x174],xmm1                       
0x6776c80  movups [rax+0x164],xmm0                       
0x6776c87  movzx eax,word ptr [rbp+0x2A0]                
0x6776c8e  mov [rbp+0x708],ax                            
0x6776c95  mov rax,[rbp+0x828]                           
0x6776c9c  mov rcx,[rax+0x10]                            
0x6776ca0  mov eax,0x9D0                                 
0x6776ca5  add rcx,rax                                   
0x6776ca8  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x6776cad  nop                                           
0x6776cae  mov r14,rax                                   
```

Interpretation: eax = [rbx+0x68], store at [rcx+0x10] where rcx=&[rbp+0x6B0] → [rbp+0x6C0]. xmm0 = [rbx+0x58], store at [rcx] = [rbp+0x6B0]. al = byte [rbp+0x25C], store at [rbp+0x6C4]. xmm0 = [rbp+0x260], store at [rbp+0x6C8]. xmm0 = [rbx+0x80], xmm1 = [rbx+0x90], xmm2 = [rbx+0x9F]. rax = &[rbp+0x574]. Store xmm2 at [rax+0x183] = [rbp+0x6F7], xmm1 at [rax+0x174] = [rbp+0x6E8], xmm0 at [rax+0x164] = [rbp+0x6D8]. ax = word [rbp+0x2A0], store at [rbp+0x708]. rax = [rbp+0x828], rcx = [rax+0x10], rcx += 0x9D0. Call 0x5ABA5C0(rcx). Result → r14.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbx+0x68], [rbx+0x58], [rbp+0x25C], [rbp+0x260], [rbx+0x80], [rbx+0x90], [rbx+0x9F], [rbp+0x2A0], [rbp+0x828], [rax+0x10]. Fields written: [rbp+0x6C0], [rbp+0x6B0], [rbp+0x6C4], [rbp+0x6C8], [rbp+0x6F7], [rbp+0x6E8], [rbp+0x6D8], [rbp+0x708].

---

## Phase 35 — Zero xmm regs [rbp+0x300..0x3C0] again (0x6776cb1..0x6776d05)

Same zeroing pattern as Phase 30.

```
0x6776cb1  movaps [rbp+0x3B0],xmm6                       
0x6776cb8  movaps [rbp+0x3A0],xmm6                       
0x6776cbf  movaps [rbp+0x390],xmm6                       
0x6776cc6  movaps [rbp+0x380],xmm6                       
0x6776ccd  movaps [rbp+0x370],xmm6                       
0x6776cd4  movaps [rbp+0x360],xmm6                       
0x6776cdb  movaps [rbp+0x350],xmm6                       
0x6776ce2  movaps [rbp+0x340],xmm6                       
0x6776ce9  movaps [rbp+0x330],xmm6                       
0x6776cf0  movaps [rbp+0x320],xmm6                       
0x6776cf7  movaps [rbp+0x310],xmm6                       
0x6776cfe  movaps [rbp+0x300],xmm6                       
0x6776d05  mov qword ptr [rbp+0x3C0],0                   
```

Interpretation: Zero xmm6 into [rbp+0x3B0] down to [rbp+0x300], and [rbp+0x3C0]=0. Same pattern as Phase 30.

Callees: none.
Fields read: xmm6. Fields written: [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x300], [rbp+0x3C0].

---

## Phase 36 — TLS/cookie read + feature flag (0x6776d10..~0x6776d20)

```
0x6776d10  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
... (--max 100)
```

Interpretation: Same TLS/cookie pattern as Phase 31 (continues in next chunk).

Callees: none (continues).
Fields read: [0x1233E1B0].

---

## Phase 36 continued — TLS/cookie read + feature flag + items buffer check (0x6776d10..0x6776d53)

Same TLS/cookie pattern as Phase 31, then writes u16 [rbp+0x708] to items buffer.

```
0x6776d10  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6776d17  mov rax,[rcx]                                 
0x6776d1a  mov rax,[rax+0x10]                            
0x6776d1e  mov dl,0x4A                                   
0x6776d20  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6776d26  nop                                           
0x6776d27  mov [rbp+0x838],al                            
0x6776d2d  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6776d34  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6776d3b  je 0x67780A5                                  ; -> loc_67780a5
0x6776d41  movzx eax,word ptr [rbp+0x708]                
0x6776d48  mov [rdx],ax                                  
0x6776d4b  add qword ptr [r14+0x8A8],2                   
0x6776d53  jmp 0x67780B9                                 ; -> loc_67780b9
```

Interpretation: rcx = [0x1233E1B0] (TLS base). rax = [rcx], rax = [rax+0x10]. dl = 0x4A. Call via [0xF99FFA0]. Store al at [rbp+0x838]. rdx = [r14+0x8A8] (items cursor), compare with [r14+0x8B0] (items end). If equal, jump to 0x67780A5. Otherwise: eax = word [rbp+0x708], store ax at [rdx], [r14+0x8A8] += 2. Jump to 0x67780B9.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x708]. Fields written: [rbp+0x838], [rdx] (items buffer), [r14+0x8A8].

---

## Phase 37 — [rbp+0x835]!=3 path: store [rbp+0x7BC] + SIMD adjust + calls (0x6776d58..0x6776e23)

When [rbp+0x835] != 3 (from Phase 24's jne target): store [rbp+0x7BC] at [rbp+0x4A0], ax at [rbp+0x4A4], SIMD adjust, call 0x678CF10 and 0x678E1D0.

```
0x6776d58  mov ecx,[rbp+0x7BC]                           
0x6776d5e  mov [rbp+0x4A0],ecx                           
0x6776d64  mov [rbp+0x4A4],ax                            
0x6776d6b  addss xmm12,xmm13                             
0x6776d70  addps xmm15,xmm14                             
0x6776d74  movlps [rbp+0x7C0],xmm15                      
0x6776d7c  movss [rbp+0x7C8],xmm12                       
0x6776d85  lea rcx,[rbp+0x2C0]                           
0x6776d8c  mov rdx,r13                                   
0x6776d8f  call 0x678CF10                                ; -> sub_678cf10
0x6776d94  nop                                           
0x6776d95  lea rax,[rbp+0x7C0]                           
0x6776d9c  mov [rsp+0x20],rax                            
0x6776da1  lea r14,[rbp+0x110]                           
0x6776da8  mov rcx,r14                                   
0x6776dab  lea rdx,[rbp+0x3E0]                           
0x6776db2  lea r8,[rbp+0x388]                            
0x6776db9  mov r9,r13                                    
0x6776dbc  call 0x678E1D0                                ; -> sub_678e1d0
0x6776dc1  nop                                           
0x6776dc2  lea rcx,[rbp+0x3E0]                           
0x6776dc9  mov eax,[rcx+0x68]                            
0x6776dcc  mov [rbx+0x78],eax                            
0x6776dcf  movups xmm0,[rcx+0x58]                        
0x6776dd3  movups [rbx+0x68],xmm0                        
0x6776dd7  movzx eax,byte ptr [rbp+0x44C]                
0x6776dde  mov [rbp+0x26C],al                            
0x6776de4  movups xmm0,[rbp+0x450]                       
0x6776deb  movups [rbp+0x270],xmm0                       
0x6776df2  movups xmm0,[rcx+0x80]                        
0x6776df9  movups xmm1,[rcx+0x90]                        
0x6776e00  movups xmm2,[rcx+0x9F]                        
0x6776e07  movups [rbx+0xAF],xmm2                        
0x6776e0e  movups [rbx+0xA0],xmm1                        
0x6776e15  movups [rbx+0x90],xmm0                        
0x6776e1c  movzx eax,word ptr [rbp+0x490]                
0x6776e23  mov [rbp+0x2B0],ax                            
```

Interpretation: ecx = [rbp+0x7BC], store at [rbp+0x4A0]. Store ax at [rbp+0x4A4]. xmm12 += xmm13, xmm15 += xmm14. Store low 64 bits of xmm15 at [rbp+0x7C0], low 32 bits of xmm12 at [rbp+0x7C8]. rcx = &[rbp+0x2C0], rdx = r13. Call 0x678CF10. [rsp+0x20] = &[rbp+0x7C0]. r14 = &[rbp+0x110]. Call 0x678E1D0(rcx=r14, rdx=&[rbp+0x3E0], r8=&[rbp+0x388], r9=r13). Then rcx = &[rbp+0x3E0]. eax = [rcx+0x68] → [rbx+0x78]. xmm0 = [rcx+0x58] → [rbx+0x68]. al = byte [rbp+0x44C] → [rbp+0x26C]. xmm0 = [rbp+0x450] → [rbp+0x270]. xmm0 = [rcx+0x80], xmm1 = [rcx+0x90], xmm2 = [rcx+0x9F]. Store xmm2 at [rbx+0xAF], xmm1 at [rbx+0xA0], xmm0 at [rbx+0x90]. ax = word [rbp+0x490] → [rbp+0x2B0].

Callees: 0x678CF10 (sub_678cf10), 0x678E1D0 (sub_678e1d0).
Fields read: [rbp+0x7BC], [rbp+0x4A4], xmm13, xmm12, xmm14, xmm15, [rbp+0x2C0], r13, [rbp+0x110], [rbp+0x3E0], [rbp+0x388], [rcx+0x68], [rcx+0x58], [rbp+0x44C], [rbp+0x450], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x490]. Fields written: [rbp+0x4A0], [rbp+0x4A4], [rbp+0x7C0], [rbp+0x7C8], [rsp+0x20], [rbx+0x78], [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0xAF], [rbx+0xA0], [rbx+0x90], [rbp+0x2B0].

---

## Phase 38 — Call 0x67E23F0 + call 0x6791880 (0x6776e2a..0x6776e6d)

Calls 0x67E23F0 with rcx=r13, then calls 0x6791880 with multiple output pointers.

```
0x6776e2a  mov rcx,r13                                   
0x6776e2d  call 0x67E23F0                                ; -> sub_67e23f0
0x6776e32  nop                                           
0x6776e33  lea rax,[rbp+0x4A0]                           
0x6776e3a  mov [rsp+0x30],rax                            
0x6776e3f  lea rax,[rbp+0x4A4]                           
0x6776e46  mov [rsp+0x28],rax                            
0x6776e4b  mov [rsp+0x20],r14                            
0x6776e50  mov rcx,r12                                   
0x6776e53  lea rdx,[rbp+0x200]                           
0x6776e5a  lea r8,[rbp+0x1A8]                            
0x6776e61  lea r9,[rbp+0x120]                            
0x6776e68  call 0x6791880                                ; -> sub_6791880
0x6776e6d  nop                                           
```

Interpretation: rcx = r13 (&[rbp+0x300]). Call 0x67E23F0. [rsp+0x30] = &[rbp+0x4A0]. [rsp+0x28] = &[rbp+0x4A4]. [rsp+0x20] = r14. rcx = r12 (&[rbp+0x570]). rdx = &[rbp+0x200]. r8 = &[rbp+0x1A8]. r9 = &[rbp+0x120]. Call 0x6791880.

Callees: 0x67E23F0 (sub_67e23f0), 0x6791880 (sub_6791880).
Fields read: none (registers only). Fields written: [rsp+0x30], [rsp+0x28], [rsp+0x20].

---

## Phase 39 — Copy [rbx+0x68..0xAF] to [rbp+0x6C8..0x720] + call 0x5ABA5C0 (0x6776e6e..0x6776eeb)

Copies from [rbx+0x68..0xAF] to [rbp+0x6C8..0x720], saves byte [rbp+0x26C] and u16 [rbp+0x2B0], then calls 0x5ABA5C0 again.

```
0x6776e6e  mov eax,[rbx+0x78]                            
0x6776e71  lea rcx,[rbp+0x6C8]                           
0x6776e78  mov [rcx+0x10],eax                            
0x6776e7b  movups xmm0,[rbx+0x68]                        
0x6776e7f  movups [rcx],xmm0                             
0x6776e82  movzx eax,byte ptr [rbp+0x26C]                
0x6776e89  mov [rbp+0x6DC],al                            
0x6776e8f  movups xmm0,[rbp+0x270]                       
0x6776e96  movups [rbp+0x6E0],xmm0                       
0x6776e9d  movups xmm0,[rbx+0x90]                        
0x6776ea4  movups xmm1,[rbx+0xA0]                        
0x6776eab  movups xmm2,[rbx+0xAF]                        
0x6776eb2  lea rax,[rbp+0x6F0]                           
0x6776eb9  movups [rax+0x1F],xmm2                        
0x6776ebd  movups [rax+0x10],xmm1                        
0x6776ec1  movups [rax],xmm0                             
0x6776ec4  movzx eax,word ptr [rbp+0x2B0]                
0x6776ecb  mov [rbp+0x720],ax                            
0x6776ed2  mov rax,[rbp+0x828]                           
0x6776ed9  mov rcx,[rax+0x10]                            
0x6776edd  mov eax,0x9D0                                 
0x6776ee2  add rcx,rax                                   
0x6776ee5  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x6776eea  nop                                           
0x6776eeb  mov r14,rax                                   
```

Interpretation: eax = [rbx+0x78], store at [rcx+0x10] where rcx=&[rbp+0x6C8] → [rbp+0x6D8]. xmm0 = [rbx+0x68], store at [rcx] = [rbp+0x6C8]. al = byte [rbp+0x26C], store at [rbp+0x6DC]. xmm0 = [rbp+0x270], store at [rbp+0x6E0]. xmm0 = [rbx+0x90], xmm1 = [rbx+0xA0], xmm2 = [rbx+0xAF]. rax = &[rbp+0x6F0]. Store xmm2 at [rax+0x1F] = [rbp+0x70F], xmm1 at [rax+0x10] = [rbp+0x700], xmm0 at [rax] = [rbp+0x6F0]. ax = word [rbp+0x2B0], store at [rbp+0x720]. rax = [rbp+0x828], rcx = [rax+0x10], rcx += 0x9D0. Call 0x5ABA5C0(rcx). Result → r14.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbx+0x78], [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0x90], [rbx+0xA0], [rbx+0xAF], [rbp+0x2B0], [rbp+0x828], [rax+0x10]. Fields written: [rbp+0x6D8], [rbp+0x6C8], [rbp+0x6DC], [rbp+0x6E0], [rbp+0x70F], [rbp+0x700], [rbp+0x6F0], [rbp+0x720].

---

## Phase 40 — Zero xmm regs [rbp+0x300..0x3C0] third time (0x6776eee..0x6776f2d)

Same zeroing pattern as Phases 30 and 35 (continues in next chunk).

```
0x6776eee  movaps [rbp+0x3B0],xmm6                       
0x6776ef5  movaps [rbp+0x3A0],xmm6                       
0x6776efc  movaps [rbp+0x390],xmm6                       
0x6776f03  movaps [rbp+0x380],xmm6                       
0x6776f0a  movaps [rbp+0x370],xmm6                       
0x6776f11  movaps [rbp+0x360],xmm6                       
0x6776f18  movaps [rbp+0x350],xmm6                       
0x6776f1f  movaps [rbp+0x340],xmm6                       
0x6776f26  movaps [rbp+0x330],xmm6                       
0x6776f2d  movaps [rbp+0x320],xmm6                       
... (--max 100)
```

Interpretation: Zero xmm6 into [rbp+0x3B0] down to [rbp+0x320] (continues in next chunk).

Callees: none.
Fields read: xmm6. Fields written: [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320] (continues).

---

## Phase 40 continued — Zero xmm regs + TLS/cookie + items buffer write (0x6776f2d..0x6776f90)

Continues zeroing xmm regs [rbp+0x320..0x3C0], then TLS/cookie read, then writes u16 [rbp+0x720] to items buffer.

```
0x6776f2d  movaps [rbp+0x320],xmm6                       
0x6776f34  movaps [rbp+0x310],xmm6                       
0x6776f3b  movaps [rbp+0x300],xmm6                       
0x6776f42  mov qword ptr [rbp+0x3C0],0                   
0x6776f4d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6776f54  mov rax,[rcx]                                 
0x6776f57  mov rax,[rax+0x10]                            
0x6776f5b  mov dl,0x4A                                   
0x6776f5d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6776f63  nop                                           
0x6776f64  mov [rbp+0x838],al                            
0x6776f6a  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6776f71  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6776f78  je 0x6778391                                  ; -> loc_6778391
0x6776f7e  movzx eax,word ptr [rbp+0x720]                
0x6776f85  mov [rdx],ax                                  
0x6776f88  add qword ptr [r14+0x8A8],2                   
0x6776f90  jmp 0x67783A5                                 ; -> loc_67783a5
```

Interpretation: Zero xmm6 into [rbp+0x320], [rbp+0x310], [rbp+0x300], [rbp+0x3C0]=0. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x838]. rdx=[r14+0x8A8], compare with [r14+0x8B0]. If equal jump to 0x6778391. Otherwise: eax=word [rbp+0x720], store ax at [rdx], [r14+0x8A8]+=2, jump to 0x67783A5.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x720]. Fields written: [rbp+0x320], [rbp+0x310], [rbp+0x300], [rbp+0x3C0], [rbp+0x838], [rdx] (items buffer), [r14+0x8A8].

---

## Phase 41 — [rbp+0x835]!=3 path (different variant): store [rbp+0x7BC] + calls 0x678CF10 + 0x6791F20 (0x6776f95..0x6776fec)

When [rbp+0x835] != 3 (from Phase 25's jne target): store [rbp+0x7BC], call 0x678CF10 then 0x6791F20.

```
0x6776f95  mov ecx,[rbp+0x7BC]                           
0x6776f9b  mov [rbp+0x4A0],ecx                           
0x6776fa1  mov [rbp+0x4A4],ax                            
0x6776fa8  lea rcx,[rbp+0x2C0]                           
0x6776faf  lea rdx,[rbp+0x110]                           
0x6776fb6  call 0x678CF10                                ; -> sub_678cf10
0x6776fbb  nop                                           
0x6776fbc  lea rax,[rbp+0x4A0]                           
0x6776fc3  mov [rsp+0x28],rax                            
0x6776fc8  lea rax,[rbp+0x4A4]                           
0x6776fcf  mov [rsp+0x20],rax                            
0x6776fd4  mov rcx,r12                                   
0x6776fd7  lea rdx,[rbp+0x1F0]                           
0x6776fde  lea r8,[rbp+0x198]                            
0x6776fe5  lea r9,[rbp+0x110]                            
0x6776fec  call 0x6791F20                                ; -> sub_6791f20
```

Interpretation: ecx = [rbp+0x7BC], store at [rbp+0x4A0]. Store ax at [rbp+0x4A4]. rcx = &[rbp+0x2C0], rdx = &[rbp+0x110]. Call 0x678CF10. [rsp+0x28] = &[rbp+0x4A0]. [rsp+0x20] = &[rbp+0x4A4]. rcx = r12 (&[rbp+0x570]), rdx = &[rbp+0x1F0], r8 = &[rbp+0x198], r9 = &[rbp+0x110]. Call 0x6791F20.

Callees: 0x678CF10 (sub_678cf10), 0x6791F20 (sub_6791f20).
Fields read: [rbp+0x7BC], [rbp+0x4A4], [rbp+0x2C0], [rbp+0x110], r12, [rbp+0x1F0], [rbp+0x198]. Fields written: [rbp+0x4A0], [rbp+0x4A4], [rsp+0x28], [rsp+0x20].

---

## Phase 42 — Copy [rbx+0x68..0x9F] to [rbp+0x6B8..0x710] + call 0x5ABA5C0 (0x6776ff2..0x677706f)

Copies from [rbx+0x68..0x9F] to [rbp+0x6B8..0x710], saves byte [rbp+0x25C] and u16 [rbp+0x2A0], then calls 0x5ABA5C0 again.

```
0x6776ff2  mov eax,[rbx+0x68]                            
0x6776ff5  lea rcx,[rbp+0x6B8]                           
0x6776ffc  mov [rcx+0x10],eax                            
0x6776fff  movups xmm0,[rbx+0x58]                        
0x6777003  movups [rcx],xmm0                             
0x6777006  movzx eax,byte ptr [rbp+0x25C]                
0x677700d  mov [rbp+0x6CC],al                            
0x6777013  movups xmm0,[rbp+0x260]                       
0x677701a  movups [rbp+0x6D0],xmm0                       
0x6777021  movups xmm0,[rbx+0x80]                        
0x6777028  movups xmm1,[rbx+0x90]                        
0x677702f  movups xmm2,[rbx+0x9F]                        
0x6777036  lea rax,[rbp+0x6E0]                           
0x677703d  movups [rax+0x1F],xmm2                        
0x6777041  movups [rax+0x10],xmm1                        
0x6777045  movups [rax],xmm0                             
0x6777048  movzx eax,word ptr [rbp+0x2A0]                
0x677704f  mov [rbp+0x710],ax                            
0x6777056  mov rax,[rbp+0x828]                           
0x677705d  mov rcx,[rax+0x10]                            
0x6777061  mov eax,0x9D0                                 
0x6777066  add rcx,rax                                   
0x6777069  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x677706e  nop                                           
0x677706f  mov r14,rax                                   
```

Interpretation: eax = [rbx+0x68], store at [rcx+0x10] where rcx=&[rbp+0x6B8] → [rbp+0x6C8]. xmm0 = [rbx+0x58], store at [rcx] = [rbp+0x6B8]. al = byte [rbp+0x25C], store at [rbp+0x6CC]. xmm0 = [rbp+0x260], store at [rbp+0x6D0]. xmm0 = [rbx+0x80], xmm1 = [rbx+0x90], xmm2 = [rbx+0x9F]. rax = &[rbp+0x6E0]. Store xmm2 at [rax+0x1F] = [rbp+0x6FF], xmm1 at [rax+0x10] = [rbp+0x6F0], xmm0 at [rax] = [rbp+0x6E0]. ax = word [rbp+0x2A0], store at [rbp+0x710]. rax = [rbp+0x828], rcx = [rax+0x10], rcx += 0x9D0. Call 0x5ABA5C0(rcx). Result → r14.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbx+0x68], [rbx+0x58], [rbp+0x25C], [rbp+0x260], [rbx+0x80], [rbx+0x90], [rbx+0x9F], [rbp+0x2A0], [rbp+0x828], [rax+0x10]. Fields written: [rbp+0x6C8], [rbp+0x6B8], [rbp+0x6CC], [rbp+0x6D0], [rbp+0x6FF], [rbp+0x6F0], [rbp+0x6E0], [rbp+0x710].

---

## Phase 43 — Zero xmm regs [rbp+0x300..0x3C0] fourth time + TLS/cookie + items write (0x6777072..0x6777114)

Zero xmm regs, TLS read, write u16 [rbp+0x710] to items buffer.

```
0x6777072  movaps [rbp+0x3B0],xmm6                       
0x6777079  movaps [rbp+0x3A0],xmm6                       
0x6777080  movaps [rbp+0x390],xmm6                       
0x6777087  movaps [rbp+0x380],xmm6                       
0x677708e  movaps [rbp+0x370],xmm6                       
0x6777095  movaps [rbp+0x360],xmm6                       
0x677709c  movaps [rbp+0x350],xmm6                       
0x67770a3  movaps [rbp+0x340],xmm6                       
0x67770aa  movaps [rbp+0x330],xmm6                       
0x67770b1  movaps [rbp+0x320],xmm6                       
0x67770b8  movaps [rbp+0x310],xmm6                       
0x67770bf  movaps [rbp+0x300],xmm6                       
0x67770c6  mov qword ptr [rbp+0x3C0],0                   
0x67770d1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67770d8  mov rax,[rcx]                                 
0x67770db  mov rax,[rax+0x10]                            
0x67770df  mov dl,0x4A                                   
0x67770e1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67770e7  nop                                           
0x67770e8  mov [rbp+0x838],al                            
0x67770ee  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x67770f5  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x67770fc  je 0x67781A5                                  ; -> loc_67781a5
0x6777102  movzx eax,word ptr [rbp+0x710]                
0x6777109  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x677710c  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6777114  jmp 0x67781B9                                 ; -> loc_67781b9
```

Interpretation: Zero xmm6 into [rbp+0x3B0]..[rbp+0x3C0]. TLS read pattern. rdx=[r14+0x8A8] vs [r14+0x8B0]. If equal jump to 0x67781A5. Otherwise: eax=word [rbp+0x710], store ax at [rdx], [r14+0x8A8]+=2, jump to 0x67781B9.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x710]. Fields written: [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x300], [rbp+0x3C0], [rbp+0x838], [rdx] (items buffer), [r14+0x8A8].

---

## Phase 44 — [rsi+0x48] qword compare + SIMD adjust + call 0x678CF10 (0x6777119..0x6777158)

Compare qword [rsi+0x48] with 0xB, addss/addps SIMD adjust, store to [rbp+0x4A0/0x4A8], call 0x678CF10.

```
0x6777119  mov rax,[rsi+0x48]                            
0x677711d  cmp qword ptr [rax],0xB                       
0x6777121  addss xmm12,xmm13                             
0x6777126  addps xmm15,xmm14                             
0x677712a  jne 0x677747D                                 ; -> loc_677747d
0x6777130  movlps [rbp+0x4A0],xmm15                      
0x6777138  movss [rbp+0x4A8],xmm12                       
0x6777141  lea rcx,[rbp+0x2C0]                           
0x6777148  mov rdx,r13                                   
0x677714b  call 0x678CF10                                ; -> sub_678cf10
0x6777150  nop                                           
0x6777151  lea rax,[rbp+0x4A0]                           
0x6777158  mov [rsp+0x20],rax                            
```

Interpretation: rax = [rsi+0x48], compare qword [rax] with 0xB. xmm12 += xmm13, xmm15 += xmm14. If not equal, jump to loc_677747D. Otherwise: store low 64 bits of xmm15 at [rbp+0x4A0], low 32 bits of xmm12 at [rbp+0x4A8]. rcx = &[rbp+0x2C0], rdx = r13. Call 0x678CF10. [rsp+0x20] = &[rbp+0x4A0].

Callees: 0x678CF10 (sub_678cf10).
Fields read: [rsi+0x48], [rax], xmm13, xmm12, xmm14, xmm15, [rbp+0x2C0], r13. Fields written: [rbp+0x4A0], [rbp+0x4A8], [rsp+0x20].

---

## Phase 45 — Call 0x678E1D0 + copy [rcx+0x68..0x9F] to [rbx+0x78..0x90] (0x6777158..0x67771e5)

Calls 0x678E1D0, then copies from [rbp+0x3E0] struct to [rbx+0x68..0xAF] region.

```
0x6777158  mov [rsp+0x20],rax                            
0x677715d  lea r14,[rbp+0x110]                           
0x6777164  mov rcx,r14                                   
0x6777167  lea rdx,[rbp+0x3E0]                           
0x677716e  lea r8,[rbp+0x388]                            
0x6777175  mov r9,r13                                    
0x6777178  call 0x678E1D0                                ; -> sub_678e1d0
0x677717d  nop                                           
0x677717e  lea rcx,[rbp+0x3E0]                           
0x6777185  mov eax,[rcx+0x68]                            
0x6777188  mov [rbx+0x78],eax                            
0x677718b  movups xmm0,[rcx+0x58]                        
0x677718f  movups [rbx+0x68],xmm0                        
0x6777193  movzx eax,byte ptr [rbp+0x44C]                
0x677719a  mov [rbp+0x26C],al                            
0x67771a0  movups xmm0,[rbp+0x450]                       
0x67771a7  movups [rbp+0x270],xmm0                       
0x67771ae  movups xmm0,[rcx+0x80]                        
0x67771b5  movups xmm1,[rcx+0x90]                        
0x67771bc  movups xmm2,[rcx+0x9F]                        
0x67771c3  movups [rbx+0xAF],xmm2                        
0x67771ca  movups [rbx+0xA0],xmm1                        
0x67771d1  movups [rbx+0x90],xmm0                        
0x67771d8  movzx eax,word ptr [rbp+0x490]                
0x67771df  mov [rbp+0x2B0],ax                            
```

Interpretation: [rsp+0x20]=rax. r14=&[rbp+0x110]. Call 0x678E1D0(rcx=r14, rdx=&[rbp+0x3E0], r8=&[rbp+0x388], r9=r13). Then rcx=&[rbp+0x3E0]. eax=[rcx+0x68]→[rbx+0x78]. xmm0=[rcx+0x58]→[rbx+0x68]. al=byte [rbp+0x44C]→[rbp+0x26C]. xmm0=[rbp+0x450]→[rbp+0x270]. xmm0=[rcx+0x80], xmm1=[rcx+0x90], xmm2=[rcx+0x9F]. Store xmm2 at [rbx+0xAF], xmm1 at [rbx+0xA0], xmm0 at [rbx+0x90]. ax=word [rbp+0x490]→[rbp+0x2B0].

Callees: 0x678E1D0 (sub_678e1d0).
Fields read: [rbp+0x3E0], [rcx+0x68], [rcx+0x58], [rbp+0x44C], [rbp+0x450], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x490], r13. Fields written: [rsp+0x20], [rbx+0x78], [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0xAF], [rbx+0xA0], [rbx+0x90], [rbp+0x2B0].

---

## Phase 46 — Call 0x67E23F0 + call 0x678E420 + copy to [rbp+0x6B8..0x710] (0x67771e6..0x677728f)

Calls 0x67E23F0 and 0x678E420, then copies from [rbx+0x78..0xAF] to [rbp+0x6B8..0x710].

```
0x67771e6  mov rcx,r13                                   
0x67771e9  call 0x67E23F0                                ; -> sub_67e23f0
0x67771ee  nop                                           
0x67771ef  mov [rsp+0x20],r14                            
0x67771f4  mov rcx,r12                                   
0x67771f7  lea rdx,[rbp+0x200]                           
0x67771fe  lea r8,[rbp+0x1A8]                            
0x6777205  lea r9,[rbp+0x120]                            
0x677720c  call 0x678E420                                ; -> sub_678e420
0x6777211  nop                                           
0x6777212  mov eax,[rbx+0x78]                            
0x6777215  lea rcx,[rbp+0x6B8]                           
0x677721c  mov [rcx+0x10],eax                            
0x677721f  movups xmm0,[rbx+0x68]                        
0x6777223  movups [rcx],xmm0                             
0x6777226  movzx eax,byte ptr [rbp+0x26C]                
0x677722d  mov [rbp+0x6CC],al                            
0x6777233  movups xmm0,[rbp+0x270]                       
0x677723a  movups [rbp+0x6D0],xmm0                       
0x6777241  movups xmm0,[rbx+0x90]                        
0x6777248  movups xmm1,[rbx+0xA0]                        
0x677724f  movups xmm2,[rbx+0xAF]                        
0x6777256  lea rax,[rbp+0x6E0]                           
0x677725d  movups [rax+0x1F],xmm2                        
0x6777261  movups [rax+0x10],xmm1                        
0x6777265  movups [rax],xmm0                             
0x6777268  movzx eax,word ptr [rbp+0x2B0]                
0x677726f  mov [rbp+0x710],ax                            
0x6777276  mov rax,[rbp+0x828]                           
0x677727d  mov rcx,[rax+0x10]                            
0x6777281  mov eax,0x9D0                                 
0x6777286  add rcx,rax                                   
0x6777289  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x677728e  nop                                           
0x677728f  mov r14,rax                                   
```

Interpretation: rcx=r13 (&[rbp+0x300]). Call 0x67E23F0. [rsp+0x20]=r14. rcx=r12 (&[rbp+0x570]). rdx=&[rbp+0x200]. r8=&[rbp+0x1A8]. r9=&[rbp+0x120]. Call 0x678E420. Then eax=[rbx+0x78]→[rcx+0x10]=[rbp+0x6C8]. xmm0=[rbx+0x68]→[rcx]=[rbp+0x6B8]. al=byte [rbp+0x26C]→[rbp+0x6CC]. xmm0=[rbp+0x270]→[rbp+0x6D0]. xmm0=[rbx+0x90], xmm1=[rbx+0xA0], xmm2=[rbx+0xAF]. rax=&[rbp+0x6E0]. Store xmm2 at [rax+0x1F]=[rbp+0x6FF], xmm1 at [rax+0x10]=[rbp+0x6F0], xmm0 at [rax]=[rbp+0x6E0]. ax=word [rbp+0x2B0]→[rbp+0x710]. rax=[rbp+0x828], rcx=[rax+0x10], rcx+=0x9D0. Call 0x5ABA5C0(rcx). Result→r14.

Callees: 0x67E23F0 (sub_67e23f0), 0x678E420 (sub_678e420), 0x5ABA5C0 (sub_5aba5c0).
Fields read: r13, r14, r12, [rbp+0x200], [rbp+0x1A8], [rbp+0x120], [rbx+0x78], [rbx+0x68], [rbp+0x26C], [rbp+0x270], [rbx+0x90], [rbx+0xA0], [rbx+0xAF], [rbp+0x2B0], [rbp+0x828], [rax+0x10]. Fields written: [rsp+0x20], [rbp+0x6C8], [rbp+0x6B8], [rbp+0x6CC], [rbp+0x6D0], [rbp+0x6FF], [rbp+0x6F0], [rbp+0x6E0], [rbp+0x710].

---

## Phase 47 — Zero xmm regs [rbp+0x300..0x3C0] fifth time + TLS/cookie + items write (0x6777292..0x6777334)

Zero xmm regs, TLS read, write u16 [rbp+0x710] to items buffer.

```
0x6777292  movaps [rbp+0x3B0],xmm6                       
0x6777299  movaps [rbp+0x3A0],xmm6                       
0x67772a0  movaps [rbp+0x390],xmm6                       
0x67772a7  movaps [rbp+0x380],xmm6                       
0x67772ae  movaps [rbp+0x370],xmm6                       
0x67772b5  movaps [rbp+0x360],xmm6                       
0x67772bc  movaps [rbp+0x350],xmm6                       
0x67772c3  movaps [rbp+0x340],xmm6                       
0x67772ca  movaps [rbp+0x330],xmm6                       
0x67772d1  movaps [rbp+0x320],xmm6                       
0x67772d8  movaps [rbp+0x310],xmm6                       
0x67772df  movaps [rbp+0x300],xmm6                       
0x67772e6  mov qword ptr [rbp+0x3C0],0                   
0x67772f1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67772f8  mov rax,[rcx]                                 
0x67772fb  mov rax,[rax+0x10]                            
0x67772ff  mov dl,0x4A                                   
0x6777301  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6777307  nop                                           
0x6777308  mov [rbp+0x838],al                            
0x677730e  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6777315  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x677731c  je 0x677ABCE                                  ; -> sub_677abce
0x6777322  movzx eax,word ptr [rbp+0x710]                
0x6777329  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x677732c  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6777334  jmp 0x677ABE2                                 ; -> sub_677abe2
```

Interpretation: Zero xmm6 into [rbp+0x3B0]..[rbp+0x3C0]. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x838]. rdx=[r14+0x8A8] vs [r14+0x8B0]. If equal jump to 0x677ABCE. Otherwise: eax=word [rbp+0x710], store ax at [rdx], [r14+0x8A8]+=2, jump to 0x677ABE2.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x710]. Fields written: [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x300], [rbp+0x3C0], [rbp+0x838], [rdx] (items buffer), [r14+0x8A8].

---

## Phase 48 — [rdi+0x50] align check + branch (0x6777339..0x677736d)

EAX=[rdi+0x50], ECX=EAX, NOT ECX, test CL,3. If not aligned, jump to loc_677761D. If [rbp+0x836]==0, jump to sub_677a714. Otherwise call 0x678CF10.

```
0x6777339  mov eax,[rdi+0x50]                            
0x677733c  mov ecx,eax                                   
0x677733e  not ecx                                       
0x6777340  test cl,3                                     
0x6777343  jne 0x677761D                                 ; -> loc_677761d
0x6777349  cmp byte ptr [rbp+0x836],0                    
0x6777350  je 0x677A714                                  ; -> sub_677a714
0x6777356  lea rcx,[rbp+0x2C0]                           
0x677735d  lea rdx,[rbp+0x110]                           
0x6777364  call 0x678CF10                                ; -> sub_678cf10
0x6777369  nop                                           
0x677736a  mov rcx,r12                                   
0x677736d  lea rdx,[rbp+0x1F0]                           
```

Interpretation: eax=[rdi+0x50], ecx=eax, ecx=~eax, test cl,3 (check alignment of ~eax low 2 bits). If not 0, jump to loc_677761D. If [rbp+0x836]==0, jump to sub_677a714. Otherwise: rcx=&[rbp+0x2C0], rdx=&[rbp+0x110]. Call 0x678CF10. Then rcx=r12 (&[rbp+0x570]), rdx=&[rbp+0x1F0] (continues in next chunk).

Callees: 0x678CF10 (sub_678cf10).
Fields read: [rdi+0x50], [rbp+0x836], [rbp+0x2C0], [rbp+0x110], r12, [rbp+0x1F0]. Fields written: none.

---

## Unit Complete — First 800 instructions transcribed

**File:** docs/progress/oc_U-E4-F1.md
**Range:** 0x67762e0 to 0x677736d (~800 instructions, 48 phases)
**Status:** DONE — first 800 instructions fully transcribed into phases of at most 40 instructions each.

**All callee RVAs encountered:** 0x5679DB0, 0xE86B370, 0x5AB9970, 0xE935700, 0xAA6580, 0x678C4C0, 0x678CF10, 0x678E1D0, 0x67E23F0, 0x678E420, 0x5ABA5C0, [0xF99FFA0]=sub_eea6040, 0x678F640, 0x6791880, 0x6791F20

**All [reg+disp] field reads/writes:** [rbp+0x8E0..0x850] xmm saves, [rbp+0x848] stack cookie, [rbp+0x828]/[rbp+0x768] arg saves, [rbp+0x837]/[rbp+0x838] TLS results, [rbp+0x2B8], [rbp+0x570], [rbp+0x110], [rbp+0x118], [rbp+0x81C]/[rbp+0x81E], [rbp-0x40], [rbp+0x40], [rbp+0x2F0], [rbp+0x774], [rbp+0x835], [rbp+0x820]/[rbp+0x824], [rbp+0x588]/[rbp+0x590]/[rbp+0x598]/[rbp+0x5A0], [rbp+0x100], [rbp+0x778], [rbp+0x7BC], [rbp+0x2E0]/[rbp+0x2E8], [rbp+0x570..0x5A8], [rbp+0xA0..0xD0], [rbp+0x108], [rbp+0x2C0]/[rbp+0x2C8]/[rbp+0x2D0]/[rbp+0x2D8], [rbp+0x780], [rbp+0x2F8], [rbp+0x4A0]/[rbp+0x4A8], [rbp+0x3E0], [rbp+0x200]/[rbp+0x1A8]/[rbp+0x120], [rbp+0x6B8]/[rbp+0x6C8]/[rbp+0x6E0]/[rbp+0x6F0], [rbp+0x6C0], [rbp+0x6CC]/[rbp+0x6D0]/[rbp+0x6FF]/[rbp+0x6F0]/[rbp+0x710]/[rbp+0x708], [rbp+0x300..0x3C0] (zeroed multiple times), [rdi+0x28]/[rdi+0x18]/[rdi+0x10]/[rdi+0x3C]/[rdi+0x44]/[rdi+0x48]/[rdi+0x4C]/[rdi+0x50], [rsi+0xD8]/[rsi+0xB8]/[rsi+0xC0]/[rsi+0xC4]/[rsi+0x48]/[rsi+0x40]/[rsi+0x38]/[rsi+0x78]/[rsi+0xE0], [rbx+0x78]/[rbx+0x68]/[rbx+0x90]/[rbx+0xA0]/[rbx+0xAF]/[rbx+0x58]/[rbx+0x80]/[rbx+0x9F], [rcx+0x68]/[rcx+0x58]/[rcx+0x80]/[rcx+0x90]/[rcx+0x9F], [r14+0x8A8]/[r14+0x8B0] (items buffer cursor/end), [0x1233E1B0] TLS base, [0x129FB1F8]/[0x128767C8] globals, [0x129FB1F0] search key, gs:[0x58] TEB, [rsp+0x20]/[rsp+0x28]/[rsp+0x30] spill slots.

**Next RVA to resume:** 0x677736d (`lea rdx,[rbp+0x1F0]`) — continuation of Phase 48's call sequence.



@25@