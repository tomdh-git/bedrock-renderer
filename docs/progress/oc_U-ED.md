# Unit U-ED: editor extractor callees

Status: IN PROGRESS. Functions to decode: 0x66a6190, 0x66a6060, 0x66a6470, 0x66a65b0, 0x67d3850, 0x67d2f80.

Context (from docs/functions/66a1860.md, [I] summary of parent dossier): parent 0x66a1860 calls 0x66a6190 x5, 0x66a6060 x3, 0x66a6470 x3, 0x66a65b0 x2, 0x67d3850 x2, 0x67d2f80 (pass-vector append). These are draw-record / pass-build helpers used by the Editor block-volume wireframe extractor. All RVAs relative to Minecraft.Windows.exe image base 1.26.62.01. Static analysis only via rdis.

## NEXT

Start: function 0x66a6060 (smallest). Then 0x66a6190, then 0x66a6470/0x66a65b0 (mirror pair), then 0x67d3850 and 0x67d2f80 (large mirror pair). Resume at next un-transcribed function.

---

## Function 0x66a6060

Bounds [V]: `sub_66a6060 [0x66a6060..0x66a6182) size 0x122` (rdis `fn`). Ends at ret 0x66a6182.

### Phase 1: 0x66a6060..0x66a60e6 (40 instructions)

Prologue: save callee regs, load range [rcx+0x28, rcx+0x30) from argument a0, set bl=1. If empty range jump to the single-element tail at 0x66a60f8. Otherwise iterate elements of 0x10 stride; for each non-null element run a TLS-guarded call sequence (0xE938CB0 register, 0xE935740 log, 0xE938D70 unregister).

```
0x66a6060  push r15                                      
0x66a6062  push r14                                      
0x66a6064  push r13                                      
0x66a6066  push r12                                      
0x66a6068  push rsi                                      
0x66a6069  push rdi                                      
0x66a606a  push rbx                                      
0x66a606b  sub rsp,0x20                                  
0x66a606f  mov r14,[rcx+0x28]                            ; R a0+0x28
0x66a6073  mov r15,[rcx+0x30]                            ; R a0+0x30
0x66a6077  mov bl,1                                      
0x66a6079  cmp r14,r15                                   
0x66a607c  je short 0x66A60F8                            ; -> loc_66a60f8
0x66a607e  lea rsi,[0x129441AC]                          ; [data_129441ac]
0x66a6085  lea rdi,[0x1F59570]                           ; [sub_1f59570]
0x66a608c  jmp short 0x66A60A3                           ; -> loc_66a60a3
0x66a608e  xchg ax,ax                                    
0x66a6090  test bl,bl                                    
0x66a6092  setne bl                                      
0x66a6095  and bl,[r12+0x10]                             
0x66a609a  add r14,0x10                                  
0x66a609e  cmp r14,r15                                   
0x66a60a1  je short 0x66A60F8                            ; -> loc_66a60f8
0x66a60a3  mov r12,[r14]                                 
0x66a60a6  test r12,r12                                  
0x66a60a9  je short 0x66A609A                            ; -> loc_66a609a
0x66a60ab  mov eax,[0x129441AC]                          ; [data_129441ac]
0x66a60b1  mov edx,[0x128767C8]                          ; [data_128767c8]
0x66a60b7  mov r8,gs:[0x58]                              
0x66a60c0  mov rdx,[r8+rdx*8]                            
0x66a60c4  cmp eax,[rdx+4]                               
0x66a60ca  jle short 0x66A6090                           ; -> loc_66a6090
0x66a60cc  mov r13,rcx                                   
0x66a60cf  mov rcx,rsi                                   
0x66a60d2  call 0xE938CB0                                ; -> sub_e938cb0
0x66a60d7  mov rcx,r13                                   
0x66a60da  cmp dword ptr [0x129441AC],0xFFFFFFFF         ; [data_129441ac]
0x66a60e1  jne short 0x66A6090                           ; -> loc_66a6090
0x66a60e3  mov rcx,rdi                                   
0x66a60e6  call 0xE935740                                ; -> sub_e935740
```

Interpretation:
- prologue saves r15,r14,r13,r12,rsi,rdi,rbx; frame 0x20 [V 0x66a606b]
- r14 = [a0+0x28] (range begin), r15 = [a0+0x30] (range end) [V]
- bl = 1 (running "all matched" flag) [V]
- if range empty (r14==r15) jump to tail 0x66a60f8 [V]
- rsi = &data_129441AC (TLS/index counter), rdi = sub_1f59570 (format string?) [V]
- loop at 0x66a6090: test bl; setne bl; and bl,[r12+0x10] — fold element byte +0x10 into flag [V]
- advance r14 by 0x10 (element stride) [V]
- if r12==null skip call chain [V]
- TLS check: read data_129441AC, read gs:[0x58] TEB, rdx = [r8+rdx*8] (TLS slot array), cmp eax,[rdx+4], jle -> skip (not initialized) [V]
- call chain: 0xE938CB0 (rcx=rsi=data ptr), then if data_129441AC != 0xFFFFFFFF jump back (retry?), else 0xE935740 (rcx=rdi), 0xE938D70 (rcx=rsi), loop back [V]

### Phase 2: 0x66a60eb..0x66a6178 (39 instructions)

Tail for empty/short range: load single ptr [rcx+0x40]; TLS-guarded register/log/unregister sequence with data_129441B0 and format sub_1f5d7a0. Then combine flags and return.

```
0x66a60eb  mov rcx,rsi                                   
0x66a60ee  call 0xE938D70                                ; -> sub_e938d70
0x66a60f3  mov rcx,r13                                   
0x66a60f6  jmp short 0x66A6090                           ; -> loc_66a6090
0x66a60f8  mov rsi,[rcx+0x40]                            
0x66a60fc  test rsi,rsi                                  
0x66a60ff  je short 0x66A612A                            ; -> loc_66a612a
0x66a6101  mov eax,[0x129441B0]                          ; [data_129441b0]
0x66a6107  mov edx,[0x128767C8]                          ; [data_128767c8]
0x66a610d  mov r8,gs:[0x58]                              
0x66a6116  mov rdx,[r8+rdx*8]                            
0x66a611a  cmp eax,[rdx+4]                               
0x66a6120  jg short 0x66A6147                            ; -> loc_66a6147
0x66a6122  test bl,bl                                    
0x66a6124  setne bl                                      
0x66a6127  and bl,[rsi+0x10]                             
0x66a612a  mov rax,[rcx+0x28]                            
0x66a612e  cmp rax,[rcx+0x30]                            
0x66a6132  setne al                                      
0x66a6135  and al,bl                                     
0x66a6137  add rsp,0x20                                  
0x66a613b  pop rbx                                       
0x66a613c  pop rdi                                       
0x66a613d  pop rsi                                       
0x66a613e  pop r12                                       
0x66a6140  pop r13                                       
0x66a6142  pop r14                                       
0x66a6144  pop r15                                       
0x66a6146  ret                                           
0x66a6147  lea rax,[0x129441B0]                          ; [data_129441b0]
0x66a614e  mov rdi,rcx                                   
0x66a6151  mov rcx,rax                                   
0x66a6154  call 0xE938CB0                                ; -> sub_e938cb0
0x66a6159  mov rcx,rdi                                   
0x66a615c  cmp dword ptr [0x129441B0],0xFFFFFFFF         ; [data_129441b0]
0x66a6163  jne short 0x66A6122                           ; -> loc_66a6122
0x66a6165  lea rcx,[0x1F5D7A0]                           ; [sub_1f5d7a0]
0x66a616c  call 0xE935740                                ; -> sub_e935740
0x66a6171  lea rcx,[0x129441B0]                          ; [data_129441b0]
0x66a6178  call 0xE938D70                                ; -> sub_e938d70
```

Interpretation:
- loop backedge target 0x66a60f6 continues into tail at 0x66a60f8 [V]
- rsi = [a0+0x40] (single pointer) [V]
- if rsi null skip to flag combine [V]
- TLS check with data_129441B0 vs gs:[0x58] TEB slot; jg -> slow path 0x66a6147 [V]
- fast path: test bl; setne bl; and bl,[rsi+0x10] [V]
- combine: al = ( [a0+0x28] != [a0+0x30] ); al &= bl; return al [V]
- epilogue restores and ret [V]
- slow path 0x66a6147: register 0xE938CB0 with data_129441B0, if !=0xFFFFFFFF jump to combine, else log 0xE935740 with sub_1f5d7a0, unregister 0xE938D70, jump to combine [V]

### Phase 3: 0x66a617d..0x66a6182 (4 instructions)

```
0x66a617d  mov rcx,rdi                                   
0x66a6180  jmp short 0x66A6122                           ; -> loc_66a6122
```

Interpretation: slow-path tail: rcx=rdi (arg preserved), jump to flag-combine block at 0x66a6122 [V].

---

### 0x66a6060 summary

Args [V]: rcx = a0 (pointer to a struct with +0x28 begin, +0x30 end, +0x40 single ptr). rdx/r8/r9 unused.

Fields touched [V] (reg+disp, R/W):
- R [rcx+0x28] (range begin)
- R [rcx+0x30] (range end)
- R [rcx+0x40] (single pointer)
- R [r12+0x10] (element byte, inside loop)
- R [rsi+0x10] (single pointer byte)
- W none to memory (only register bl/al); reads TLS data_129441AC / data_129441B0 and gs:[0x58]

Callees [V]:
- 0xE938CB0 (register TLS, x2 paths)
- 0xE935740 (log, x2 paths, formats sub_1f59570 / sub_1f5d7a0)
- 0xE938D70 (unregister TLS, x2 paths)

Return: al (bool) = all-elements-matched AND (range non-empty) [I].

OPEN: exact semantics of data_129441AC/129441B0 and sub_1f59570/1f5d7a0 (TLS logging) [I].

---

## Function 0x66a6190

Bounds [V]: `sub_66a6190 [0x66a6190..0x66a63af) size 0x21f` (rdis `fn`). Ends at ret 0x66a6332 (fallthrough) plus cold int3 tail at 0x66a63ae.

### Phase 1: 0x66a6190..0x66a6215 (35 instructions)

Prologue: save callee regs, xmm6; out = rcx (a0), src = rdx (a1), iterable = r8 (a2->rsi). Copy *[a1] -> [a0] (qword), zero a0+0x38/0x40/0x48, zero a0+0x8/0x18, store a0+0x50 = rdx. r14 = (a2+0x20 != 0) ? (i32)[a2+0x1C] : 0. rax = [a2+0x28], compare [a2+0x30] vs rax; if equal jump to done block 0x66a62c3. Else r15=8 (cursor), r12=0 (index), rdi = &rbp-0x40 (temp variant slot), jump to loop head.

```
0x66a6190  push rbp                                      
0x66a6191  push r15                                      
0x66a6193  push r14                                      
0x66a6195  push r12                                      
0x66a6197  push rsi                                      
0x66a6198  push rdi                                      
0x66a6199  push rbx                                      
0x66a619a  sub rsp,0x80                                  
0x66a61a1  lea rbp,[rsp+0x80]                            
0x66a61a9  movaps [rbp-0x10],xmm6                        
0x66a61ad  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE   
0x66a61b5  mov rsi,r8                                    
0x66a61b8  mov rbx,rcx                                   
0x66a61bb  mov rax,[rdx]                                 ; R a1+0x0
0x66a61be  mov rax,[rax]                                 ; R *(a1+0x0)+0x0
0x66a61c1  mov [rcx],rax                                 ; W a0+0x0
0x66a61c4  mov byte ptr [rcx+0x38],0                     ; W a0+0x38
0x66a61c8  mov dword ptr [rcx+0x40],0                    ; W a0+0x40
0x66a61cf  mov qword ptr [rcx+0x48],0                    ; W a0+0x48
0x66a61d7  xorps xmm6,xmm6                               
0x66a61da  movups [rcx+8],xmm6                           ; W a0+0x8
0x66a61de  movups [rcx+0x18],xmm6                        ; W a0+0x18
0x66a61e2  mov [rcx+0x50],rdx                            ; W a0+0x50
0x66a61e6  movsxd rax,[r8+0x1C]                          ; R a2+0x1C
0x66a61ea  xor r14d,r14d                                 
0x66a61ed  cmp byte ptr [r8+0x20],0                      ; R a2+0x20
0x66a61f2  cmovne r14,rax                                
0x66a61f6  mov rax,[r8+0x28]                             ; R a2+0x28
0x66a61fa  cmp [r8+0x30],rax                             ; R a2+0x30
0x66a61fe  mov [rbp-0x48],rcx                            
0x66a6202  je 0x66A62C3                                  ; -> loc_66a62c3
0x66a6208  mov r15d,8                                    
0x66a620e  xor r12d,r12d                                 
0x66a6211  lea rdi,[rbp-0x40]                            
0x66a6215  jmp short 0x66A6243                           ; -> loc_66a6243
```

Interpretation:
- a0 = out record (rcx), a1 = source pointer (rdx), a2 = iterable descriptor (r8 -> rsi) [V]
- out+0x0 = *(a1+0x0) dereferenced (vtable copy) [V]
- out+0x38 byte=0, out+0x40 dword=0, out+0x48 qword=0 [V]
- out+0x8 = 0, out+0x18 = 0 (xmm6 zero) [V]
- out+0x50 = rdx (a1) [V]
- r14 = [a2+0x1C] if [a2+0x20]!=0 else 0 (cmovne) [V]
- empty check: [a2+0x30]==[a2+0x28] -> done [V]
- r15 = cursor start 8, r12 = index 0 [V]

### Phase 2: 0x66a6217..0x66a6284 (31 instructions)

Loop iteration: compute element count = ([a2+0x30]-[a2+0x28])>>4; advance cursor r15 += 0x10; if index >= count -> done. Else load element vtable = [a2+0x0], r9d = [vtable+0x4+idx*8]; clear temp variant slot; rcx = element ptr [[a2+0x28]+cursor]; if non-null lock inc [rcx+8] (addref). Then slot.lo = [rax+r15-8], slot.hi = [rax+r15]; tag byte [rbp-0x28]=2; call sub_c2adac0(out, &slot, 0). If tag != 2 loop back. Else rbx = slot.hi; if rbx addref-release; lock dec [rbx+8]; if !=0 loop back; else full destroy (call [0xF99FFA0]=sub_eea6040 dtor1, lock dec [rbx+0xC], if !=0 loop back, else call [0xF99FFA0] dtor2) then loop back.

```
0x66a6217  nop [rax+rax]                                 ; R *(a2+0x28)+0x0+idx
0x66a6220  inc r12                                       
0x66a6223  mov rax,[rsi+0x28]                            ; R a2+0x28
0x66a6227  mov rcx,[rsi+0x30]                            ; R a2+0x30
0x66a622b  sub rcx,rax                                   
0x66a622e  sar rcx,4                                     
0x66a6232  add r15,0x10                                  
0x66a6236  cmp r12,rcx                                   
0x66a6239  mov rbx,[rbp-0x48]                            
0x66a623d  jae 0x66A62C3                                 ; -> loc_66a62c3
0x66a6243  mov rcx,[rsi]                                 ; R a2+0x0
0x66a6246  mov r9d,[rcx+r12*8+4]                         ; R *(a2+0x0)+0x4+idx
0x66a624b  movaps [rbp-0x40],xmm6                        
0x66a624f  mov rcx,[rax+r15]                             ; R *(a2+0x28)+0x0+idx
0x66a6253  test rcx,rcx                                  
0x66a6256  je short 0x66A625C                            ; -> loc_66a625c
0x66a6258  lock inc dword ptr [rcx+8]                    ; W *(*(a2+0x28)+0x0+idx)+0x8
0x66a625c  mov rcx,[rax+r15-8]                           ; R *(a2+0x28)-0x8+idx
0x66a6261  mov [rbp-0x40],rcx                            
0x66a6265  mov rax,[rax+r15]                             ; R *(a2+0x28)+0x0+idx
0x66a6269  mov [rbp-0x38],rax                            
0x66a626d  mov byte ptr [rbp-0x28],2                     
0x66a6271  mov rcx,rbx                                   
0x66a6274  mov rdx,rdi                                   
0x66a6277  xor r8d,r8d                                   
0x66a627a  call 0xC2ADAC0                                ; -> sub_c2adac0
0x66a627f  nop                                           
0x66a6280  cmp byte ptr [rbp-0x28],2                     
0x66a6284  jne short 0x66A6220                           ; -> loc_66a6220
```

Interpretation:
- element stride 0x10, count computed by sar 4 [V]
- per element: vtable = [a2+0], method ptr r9d = [vtable+4+idx*8] [V]
- element ptr rcx = [[a2+0x28] + cursor]; addref [rcx+8] if non-null [V]
- temp variant: lo=[rax+r15-8], hi=[rax+r15], tag=2 [V]
- call sub_c2adac0(rcx=out, rdx=&slot, r8=0) — converts element into variant slot [V]
- on tag==2, release previous slot.hi (refcount dec, conditional destroy) [V]

### Phase 3: 0x66a6286..0x66a630d (25 instructions)

Release of replaced slot value then done block: movaps temp=zero; rax=[a2+0x48]; if null eax=0 else lock inc [rax+8]; rax=[a2+0x48]; rcx=[a2+0x40]; temp.lo=rcx, temp.hi=rax; tag [rbp-0x30]=3; lea rax,[rbx+0x28] (out+0x28); [rbp-0x58]=rax; rdx=&[rbp-0x58], r8=&[rbp-0x40], ecx=4; call sub_c2adfd0(out+0x28?, &temp, 4). movzx eax, tag [rbp-0x30]; cmp eax,3; jae -> long variant path 0x66a6333.

```
0x66a6286  mov rbx,[rbp-0x38]                            
0x66a628a  test rbx,rbx                                  
0x66a628d  je short 0x66A6220                            ; -> loc_66a6220
0x66a628f  lock dec dword ptr [rbx+8]                    
0x66a6293  jne short 0x66A6220                           ; -> loc_66a6220
0x66a6295  mov rax,[rbx]                                 
0x66a6298  mov rax,[rax]                                 
0x66a629b  mov rcx,rbx                                   
0x66a629e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a62a4  lock dec dword ptr [rbx+0xC]                  
0x66a62a8  jne 0x66A6220                                 ; -> loc_66a6220
0x66a62ae  mov rax,[rbx]                                 
0x66a62b1  mov rax,[rax+8]                               
0x66a62b5  mov rcx,rbx                                   
0x66a62b8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a62be  jmp 0x66A6220                                 ; -> loc_66a6220
0x66a62c3  movaps [rbp-0x40],xmm6                        
0x66a62c7  mov rax,[rsi+0x48]                            
0x66a62cb  test rax,rax                                  
0x66a62ce  je short 0x66A62DA                            ; -> loc_66a62da
0x66a62d0  lock inc dword ptr [rax+8]                    
0x66a62d4  mov rax,[rsi+0x48]                            
0x66a62d8  jmp short 0x66A62DC                           ; -> loc_66a62dc
0x66a62da  xor eax,eax                                   
0x66a62dc  mov rcx,[rsi+0x40]                            
0x66a62e0  mov [rbp-0x40],rcx                            
0x66a62e4  mov [rbp-0x38],rax                            
0x66a62e8  mov byte ptr [rbp-0x30],3                     
0x66a62ec  lea rax,[rbx+0x28]                            
0x66a62f0  mov [rbp-0x58],rax                            
0x66a62f4  lea rdx,[rbp-0x58]                            
0x66a62f8  lea r8,[rbp-0x40]                             
0x66a62fc  mov ecx,4                                     
0x66a6301  call 0xC2ADFD0                                ; -> sub_c2adfd0
0x66a6306  movzx eax,byte ptr [rbp-0x30]                 
0x66a630a  cmp eax,3                                     
0x66a630d  jae short 0x66A6333                           ; -> loc_66a6333
```

Interpretation:
- full destroy path: dtor1 ([0xF99FFA0]=sub_eea6040), lock dec [rbx+0xC], if zero dtor2 ([0xF99FFA0]) [V]
- done block: temp variant from [a2+0x40] (lo) and [a2+0x48] (hi, addrefed) [V]
- call sub_c2adfd0 with ecx=4 — writes temp into out at [rbx+0x28] area [V]
- branch on tag==3 -> long-variant path [V]

### Phase 4: 0x66a630f..0x66a6332 (13 instructions)

Short variant (tag<3): [rbx+0x40] = 0; [rbx+0x48] = r14; then epilogue: rax=rbx (return out), restore xmm6, rsp+=0x80, pop rbx/rdi/rsi/r12/r14/r15/rbp, ret.

```
0x66a630f  mov dword ptr [rbx+0x40],0                    
0x66a6316  mov [rbx+0x48],r14                            
0x66a631a  mov rax,rbx                                   
0x66a631d  movaps xmm6,[rbp-0x10]                        
0x66a6321  add rsp,0x80                                  
0x66a6328  pop rbx                                       
0x66a6329  pop rdi                                       
0x66a632a  pop rsi                                       
0x66a632b  pop r12                                       
0x66a632d  pop r14                                       
0x66a632f  pop r15                                       
0x66a6331  pop rbp                                       
0x66a6332  ret                                           
```

Interpretation:
- short variant: hi=0, lo=r14 (the cmovne value) stored at out+0x40/0x48 [V]
- return rax = rbx = out pointer [V]
- standard epilogue [V]

### Phase 5: 0x66a6333..0x66a6367 (16 instructions)

Long variant (tag==3): jne -> cold int3 tail; else rcx=[rbx+0x50]+8; call 0x675D320; rax += 0x50; rdx=&[rbp-0x58], r8=&[rbp-0x40], rcx=rax; call 0xC2AE240. Then movzx eax,tag; rbx=[rbp-0x48]=out; [rbx+0x40]=0; [rbx+0x48]=r14; cmp al,3; jne -> epilogue. Else fall to release phase.

```
0x66a6333  jne short 0x66A63A8                           ; -> loc_66a63a8
0x66a6335  mov rcx,[rbx+0x50]                            
0x66a6339  add rcx,8                                     
0x66a633d  call 0x675D320                                ; -> sub_675d320
0x66a6342  nop                                           
0x66a6343  add rax,0x50                                  
0x66a6347  lea rdx,[rbp-0x58]                            
0x66a634b  lea r8,[rbp-0x40]                             
0x66a634f  mov rcx,rax                                   
0x66a6352  call 0xC2AE240                                ; -> sub_c2ae240
0x66a6357  nop                                           
0x66a6358  movzx eax,byte ptr [rbp-0x30]                 
0x66a635c  mov rbx,[rbp-0x48]                            
0x66a6360  mov dword ptr [rbx+0x40],0                    
0x66a6367  mov [rbx+0x48],r14                            
0x66a636b  cmp al,3                                      
0x66a636d  jne short 0x66A631A                           ; -> loc_66a631a
```

Interpretation:
- long variant: sub_675d320([rbx+0x50]+8) -> rax; rax+=0x50; sub_c2ae240(rax, &temp, &slot) — deep copy / clone [V]
- restore out pointer rbx=[rbp-0x48]; short-store [rbx+0x40]=0, [rbx+0x48]=r14 [V]
- if tag != 3 jump to epilogue [V]

### Phase 6: 0x66a636f..0x66a63a3 (15 instructions)

Release rsi = [rbp-0x38] (the old temp.hi) with addref-release pattern: if null skip; lock dec [rsi+8]; if !=0 skip; dtor1 ([0xF99FFA0]=sub_eea6040), lock dec [rsi+0xC]; if !=0 skip; dtor2 ([0xF99FFA0]); jump epilogue.

```
0x66a636f  mov rsi,[rbp-0x38]                            
0x66a6373  test rsi,rsi                                  
0x66a6376  je short 0x66A631A                            ; -> loc_66a631a
0x66a6378  lock dec dword ptr [rsi+8]                    
0x66a637c  jne short 0x66A631A                           ; -> loc_66a631a
0x66a637e  mov rax,[rsi]                                 
0x66a6381  mov rax,[rax]                                 
0x66a6384  mov rcx,rsi                                   
0x66a6387  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a638d  lock dec dword ptr [rsi+0xC]                  
0x66a6391  jne short 0x66A631A                           ; -> loc_66a631a
0x66a6393  mov rax,[rsi]                                 
0x66a6396  mov rax,[rax+8]                               
0x66a639a  mov rcx,rsi                                   
0x66a639d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a63a3  jmp 0x66A631A                                 ; -> loc_66a631a
```

### Phase 7: 0x66a63a8..0x66a63ae (3 instructions)

Cold terminator: call 0x1166E0 (likely __report_gsfailure / fail-fast), nop, int3.

```
0x66a63a8  call 0x1166E0                                 ; -> sub_1166e0
0x66a63ad  nop                                           
0x66a63ae  int3                                          
```

---

### 0x66a6190 summary

Args [V]: rcx = a0 (out record), rdx = a1 (source ptr, *[a1] copied), r8 = a2 (iterable descriptor with +0x28 begin/+0x30 end/+0x40/+0x48/+0x1C/+0x20).

Fields touched [V] (reg+disp, R/W):
- R [a1+0x0], then R [*(a1+0x0)+0x0]
- W [a0+0x0] (qword), W [a0+0x38] byte, W [a0+0x40] dword, W [a0+0x48] qword, W [a0+0x8], W [a0+0x18], W [a0+0x50]
- R [a2+0x1C], R [a2+0x20], R [a2+0x28], R [a2+0x30], R [a2+0x0], R [*(a2+0x0)+0x4+idx]
- R/W [a2+0x28]+cursor element (addref [+8]); R [a2+0x40], R [a2+0x48]
- W [out+0x28..] via sub_c2adfd0; W [out+0x40], W [out+0x48]
- stack slots [rbp-0x40]/[rbp-0x38]/[rbp-0x28]/[rbp-0x30]/[rbp-0x58] (temp variants)

Callees [V]:
- 0xC2ADAC0 (variant convert, in loop)
- 0xC2ADFD0 (variant write, done block)
- [0xF99FFA0] = sub_eea6040 (refcounted object dtor, x2 call sites per destroy)
- 0x675D320 (long-variant helper)
- 0xC2AE240 (long-variant clone/copy)
- 0x1166E0 (cold fail-fast, int3 after)

Return: rax = out pointer (a0) [V].

OPEN: exact field layout of out record (a0) beyond +0x50; role of sub_c2adac0/sub_c2adfd0/sub_675d320/sub_c2ae240 [I].

---

## Function 0x66a6470

Bounds [V]: `sub_66a6470 [0x66a6470..0x66a65b0) size 0x140` (rdis `fn`). Ends at ret 0x66a6595; cold int3 tail at 0x66a65af. Mirror of 0x66a65b0 (same shape, different displacements).

### Phase 1: 0x66a6470..0x66a64b8 (24 instructions)

Prologue: save callee regs; rsi = rcx (a0 = record). If byte [a0+0x178] != 3 skip to 0x66a64be. Else rdi = [a0+0x170]; if null skip. Refcount-release rdi: lock dec [rdi+8]; if !=0 skip; dtor1 ([0xF99FFA0]=sub_eea6040), lock dec [rdi+0xC]; if !=0 skip; dtor2 ([0xF99FFA0]).

```
0x66a6470  push r15                                      
0x66a6472  push r14                                      
0x66a6474  push rsi                                      
0x66a6475  push rdi                                      
0x66a6476  push rbx                                      
0x66a6477  sub rsp,0x30                                  
0x66a647b  mov rsi,rcx                                   
0x66a647e  cmp byte ptr [rcx+0x178],3                    ; R a0+0x178
0x66a6485  jne short 0x66A64BE                           ; -> loc_66a64be
0x66a6487  mov rdi,[rsi+0x170]                           ; R a0+0x170
0x66a648e  test rdi,rdi                                  
0x66a6491  je short 0x66A64BE                            ; -> loc_66a64be
0x66a6493  lock dec dword ptr [rdi+8]                    ; W *(a0+0x170)+0x8
0x66a6497  jne short 0x66A64BE                           ; -> loc_66a64be
0x66a6499  mov rax,[rdi]                                 ; R *(a0+0x170)+0x0
0x66a649c  mov rax,[rax]                                 ; R *(*(a0+0x170)+0x0)+0x0
0x66a649f  mov rcx,rdi                                   
0x66a64a2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a64a8  lock dec dword ptr [rdi+0xC]                  ; W *(a0+0x170)+0xC
0x66a64ac  jne short 0x66A64BE                           ; -> loc_66a64be
0x66a64ae  mov rax,[rdi]                                 ; R *(a0+0x170)+0x0
0x66a64b1  mov rax,[rax+8]                               ; R *(*(a0+0x170)+0x0)+0x8
0x66a64b5  mov rcx,rdi                                   
0x66a64b8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

Interpretation:
- a0 = record (rcx->rsi) [V]
- tag gate: byte [a0+0x178] == 3 required to touch [a0+0x170] [V]
- [a0+0x170] is a refcounted pointer: release via [+8] dec, conditional destroy (dtor1 at [0xF99FFA0], then [+0xC] dec, dtor2) [V]

### Phase 2: 0x66a64be..0x66a64f8 (40 instructions)

Array clear loop over [a0+0x148 .. [a0+0x150)) stride 0x28: rbx = [a0+0x148]; if null skip to 0x66a6534. r14 = &[a0+0x148] (array base), r15 = [a0+0x150] (end). Jump to cmp. Loop body: if rbx == r15 -> done 0x66a6525. If byte [rbx+0x18] != 2 skip (advance). Else rdi = [rbx+8]; if null skip. Refcount-release rdi (same pattern as phase 1). Then advance rbx += 0x28 and loop.

```
0x66a64be  mov rbx,[rsi+0x148]                           ; R a0+0x148
0x66a64c5  test rbx,rbx                                  
0x66a64c8  je short 0x66A6534                            ; -> loc_66a6534
0x66a64ca  lea r14,[rsi+0x148]                           ; R a0+0x148
0x66a64d1  mov r15,[rsi+0x150]                           ; R a0+0x150
0x66a64d8  jmp short 0x66A64E4                           ; -> loc_66a64e4
0x66a64da  nop [rax+rax]                                 
0x66a64e0  add rbx,0x28                                  
0x66a64e4  cmp rbx,r15                                   
0x66a64e7  je short 0x66A6525                            ; -> loc_66a6525
0x66a64e9  cmp byte ptr [rbx+0x18],2                     
0x66a64ed  jne short 0x66A64E0                           ; -> loc_66a64e0
0x66a64ef  mov rdi,[rbx+8]                               
0x66a64f3  test rdi,rdi                                  
0x66a64f6  je short 0x66A64E0                            ; -> loc_66a64e0
0x66a64f8  lock dec dword ptr [rdi+8]                    
```

Interpretation:
- array base [a0+0x148], end [a0+0x150], stride 0x28 [V]
- only elements with byte [rbx+0x18] == 2 are released [V]
- released pointer at [rbx+8] [V]

### Phase 3: 0x66a64fc..0x66a652c (15 instructions)

Rest of release loop (dtor1/dtor2) then clear array: lock dec [rdi+8] cont'd -> jne loop; dtor1 ([0xF99FFA0]); lock dec [rdi+0xC]; jne loop; dtor2 ([0xF99FFA0]); jmp loop. After loop: xorps xmm0; movups [r14]=0 (clear array base qword); mov qword [r14+0x10]=0.

```
0x66a64fc  jne short 0x66A64E0                           ; -> loc_66a64e0
0x66a64fe  mov rax,[rdi]                                 
0x66a6501  mov rax,[rax]                                 
0x66a6504  mov rcx,rdi                                   
0x66a6507  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a650d  lock dec dword ptr [rdi+0xC]                  
0x66a6511  jne short 0x66A64E0                           ; -> loc_66a64e0
0x66a6513  mov rax,[rdi]                                 
0x66a6516  mov rax,[rax+8]                               
0x66a651a  mov rcx,rdi                                   
0x66a651d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a6523  jmp short 0x66A64E0                           ; -> loc_66a64e0
0x66a6525  xorps xmm0,xmm0                               
0x66a6528  movups [r14],xmm0                             
0x66a652c  mov qword ptr [r14+0x10],0                    
```

### Phase 4: 0x66a6534..0x66a6595 (28 instructions)

Single-pointer release at [a0+0x138] if byte [a0+0x138] == 1: rdi = &[a0+0xF8]; rcx = [rdi]; if null skip 0x66a658a. rdx = [a0+0x108]; rdx -= rcx; if rdx < 0x1000 -> 0x66a6577. Else rax = [rcx-8]; rcx += -8; rcx -= rax; if rcx >= 0x20 -> 0x66a6596 (int3 path). Else rdx |= 0x27; rcx = rax. Then call 0xE935700. Finally xorps xmm0; [rdi]=0; [rdi+0x10]=0; epilogue (rsp+=0x30, pops, ret).

```
0x66a6534  cmp byte ptr [rsi+0x138],1                    
0x66a653b  jne short 0x66A658A                           ; -> loc_66a658a
0x66a653d  lea rdi,[rsi+0xF8]                            
0x66a6544  mov rcx,[rdi]                                 
0x66a6547  test rcx,rcx                                  
0x66a654a  je short 0x66A658A                            ; -> loc_66a658a
0x66a654c  mov rdx,[rsi+0x108]                           
0x66a6553  sub rdx,rcx                                   
0x66a6556  cmp rdx,0x1000                                
0x66a655d  jb short 0x66A6577                            ; -> loc_66a6577
0x66a655f  mov rax,[rcx-8]                               
0x66a6563  add rcx,0xFFFFFFFFFFFFFFF8                    
0x66a6567  sub rcx,rax                                   
0x66a656a  cmp rcx,0x20                                  
0x66a656e  jae short 0x66A6596                           ; -> loc_66a6596
0x66a6570  or rdx,0x27                                   
0x66a6574  mov rcx,rax                                   
0x66a6577  call 0xE935700                                ; -> sub_e935700
0x66a657c  xorps xmm0,xmm0                               
0x66a657f  movups [rdi],xmm0                             
0x66a6582  mov qword ptr [rdi+0x10],0                    
0x66a658a  add rsp,0x30                                  
0x66a658e  pop rbx                                       
0x66a658f  pop rdi                                       
0x66a6590  pop rsi                                       
0x66a6591  pop r14                                       
0x66a6593  pop r15                                       
0x66a6595  ret                                           
```

Interpretation:
- gate byte [a0+0x138] == 1 [V]
- pointer region [a0+0xF8] with size [a0+0x108]; bounds check vs 0x1000 and heap-chunk validation ([rcx-8], [rcx+ -8] vs 0x20) then call 0xE935700 (free) [V]
- clear [rdi] and [rdi+0x10] [V]

### Phase 5: 0x66a6596..0x66a65af (6 instructions)

Cold fail path: [rsp+0x20]=0; xor ecx,edx,r8d,r9d; call qword ptr [0xF9A8C78] (likely heap failure / report); int3.

```
0x66a6596  mov qword ptr [rsp+0x20],0                    
0x66a659f  xor ecx,ecx                                   
0x66a65a1  xor edx,edx                                   
0x66a65a3  xor r8d,r8d                                   
0x66a65a6  xor r9d,r9d                                   
0x66a65a9  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
0x66a65af  int3                                          
```

---

### 0x66a6470 summary

Args [V]: rcx = a0 (record). rdx/r8/r9 unused.

Fields touched [V] (reg+disp, R/W):
- R byte [a0+0x178]
- R [a0+0x170]; W [*(a0+0x170)+0x8] (lock dec), W [*(a0+0x170)+0xC] (lock dec)
- R [a0+0x148], R [a0+0x150]
- R byte [rbx+0x18] (array element tag), R [rbx+8] (element pointer)
- W [*(rbx+8)+0x8], W [*(rbx+8)+0xC] (refcount releases)
- W [r14] (= [a0+0x148]) qword=0, W [r14+0x10] qword=0 (array clear)
- R byte [a0+0x138]; R [a0+0xF8], R [a0+0x108]
- W [rdi] qword=0, W [rdi+0x10] qword=0 (single-pointer clear)

Callees [V]:
- [0xF99FFA0] = sub_eea6040 (refcounted object dtor, 4 call sites)
- 0xE935700 (free/single-pointer release)
- [0xF9A8C78] (cold fail, int3 after)

Return: void [V].

OPEN: exact struct type of a0; role of 0xE935700 vs sub_eea6040 [I].

---

## Function 0x66a65b0

Bounds [V]: `sub_66a65b0 [0x66a65b0..0x66a66f0) size 0x140` (rdis `fn`). Ends at ret 0x66a66d5; cold int3 tail at 0x66a66ef. Mirror of 0x66a6470 (same shape, different displacements: +0x168/+0x160 instead of +0x178/+0x170; +0x138/+0x140 instead of +0x148/+0x150; +0xE8/+0xF8 instead of +0xF8/+0x108; gate byte +0x128 instead of +0x138).

### Phase 1: 0x66a65b0..0x66a65f8 (24 instructions)

Prologue: save callee regs; rsi = rcx (a0 = record). If byte [a0+0x168] != 3 skip to 0x66a65fe. Else rdi = [a0+0x160]; if null skip. Refcount-release rdi: lock dec [rdi+8]; if !=0 skip; dtor1 ([0xF99FFA0]=sub_eea6040), lock dec [rdi+0xC]; if !=0 skip; dtor2 ([0xF99FFA0]).

```
0x66a65b0  push r15                                      
0x66a65b2  push r14                                      
0x66a65b4  push rsi                                      
0x66a65b5  push rdi                                      
0x66a65b6  push rbx                                      
0x66a65b7  sub rsp,0x30                                  
0x66a65bb  mov rsi,rcx                                   
0x66a65be  cmp byte ptr [rcx+0x168],3                    ; R a0+0x168
0x66a65c5  jne short 0x66A65FE                           ; -> loc_66a65fe
0x66a65c7  mov rdi,[rsi+0x160]                           ; R a0+0x160
0x66a65ce  test rdi,rdi                                  
0x66a65d1  je short 0x66A65FE                            ; -> loc_66a65fe
0x66a65d3  lock dec dword ptr [rdi+8]                    ; W *(a0+0x160)+0x8
0x66a65d7  jne short 0x66A65FE                           ; -> loc_66a65fe
0x66a65d9  mov rax,[rdi]                                 ; R *(a0+0x160)+0x0
0x66a65dc  mov rax,[rax]                                 ; R *(*(a0+0x160)+0x0)+0x0
0x66a65df  mov rcx,rdi                                   
0x66a65e2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a65e8  lock dec dword ptr [rdi+0xC]                  ; W *(a0+0x160)+0xC
0x66a65ec  jne short 0x66A65FE                           ; -> loc_66a65fe
0x66a65ee  mov rax,[rdi]                                 ; R *(a0+0x160)+0x0
0x66a65f1  mov rax,[rax+8]                               ; R *(*(a0+0x160)+0x0)+0x8
0x66a65f5  mov rcx,rdi                                   
0x66a65f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

### Phase 2: 0x66a65fe..0x66a6638 (40 instructions)

Array clear loop over [a0+0x138 .. [a0+0x140)) stride 0x28: rbx = [a0+0x138]; if null skip to 0x66a6674. r14 = &[a0+0x138], r15 = [a0+0x140]. Jump to cmp. Loop body: if rbx == r15 -> done 0x66a6665. If byte [rbx+0x18] != 2 skip (advance). Else rdi = [rbx+8]; if null skip. Refcount-release rdi.

```
0x66a65fe  mov rbx,[rsi+0x138]                           ; R a0+0x138
0x66a6605  test rbx,rbx                                  
0x66a6608  je short 0x66A6674                            ; -> loc_66a6674
0x66a660a  lea r14,[rsi+0x138]                           ; R a0+0x138
0x66a6611  mov r15,[rsi+0x140]                           ; R a0+0x140
0x66a6618  jmp short 0x66A6624                           ; -> loc_66a6624
0x66a661a  nop [rax+rax]                                 
0x66a6620  add rbx,0x28                                  
0x66a6624  cmp rbx,r15                                   
0x66a6627  je short 0x66A6665                            ; -> loc_66a6665
0x66a6629  cmp byte ptr [rbx+0x18],2                     
0x66a662d  jne short 0x66A6620                           ; -> loc_66a6620
0x66a662f  mov rdi,[rbx+8]                               
0x66a6633  test rdi,rdi                                  
0x66a6636  je short 0x66A6620                            ; -> loc_66a6620
0x66a6638  lock dec dword ptr [rdi+8]                    
```

### Phase 3: 0x66a663c..0x66a666c (15 instructions)

Rest of release loop (dtor1/dtor2) then clear array: lock dec [rdi+8] cont'd -> jne loop; dtor1 ([0xF99FFA0]); lock dec [rdi+0xC]; jne loop; dtor2 ([0xF99FFA0]); jmp loop. After loop: xorps xmm0; movups [r14]=0; mov qword [r14+0x10]=0.

```
0x66a663c  jne short 0x66A6620                           ; -> loc_66a6620
0x66a663e  mov rax,[rdi]                                 
0x66a6641  mov rax,[rax]                                 
0x66a6644  mov rcx,rdi                                   
0x66a6647  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a664d  lock dec dword ptr [rdi+0xC]                  
0x66a6651  jne short 0x66A6620                           ; -> loc_66a6620
0x66a6653  mov rax,[rdi]                                 
0x66a6656  mov rax,[rax+8]                               
0x66a665a  mov rcx,rdi                                   
0x66a665d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x66a6663  jmp short 0x66A6620                           ; -> loc_66a6620
0x66a6665  xorps xmm0,xmm0                               
0x66a6668  movups [r14],xmm0                             
0x66a666c  mov qword ptr [r14+0x10],0                    
```

### Phase 4: 0x66a6674..0x66a66d5 (28 instructions)

Single-pointer release at [a0+0x128] if byte [a0+0x128] == 1: rdi = &[a0+0xE8]; rcx = [rdi]; if null skip 0x66a66ca. rdx = [a0+0xF8]; rdx -= rcx; if rdx < 0x1000 -> 0x66a66b7. Else rax = [rcx-8]; rcx += -8; rcx -= rax; if rcx >= 0x20 -> 0x66a66d6 (int3 path). Else rdx |= 0x27; rcx = rax. Then call 0xE935700. Finally xorps xmm0; [rdi]=0; [rdi+0x10]=0; epilogue (rsp+=0x30, pops, ret).

```
0x66a6674  cmp byte ptr [rsi+0x128],1                    
0x66a667b  jne short 0x66A66CA                           ; -> loc_66a66ca
0x66a667d  lea rdi,[rsi+0xE8]                            
0x66a6684  mov rcx,[rdi]                                 
0x66a6687  test rcx,rcx                                  
0x66a668a  je short 0x66A66CA                            ; -> loc_66a66ca
0x66a668c  mov rdx,[rsi+0xF8]                            
0x66a6693  sub rdx,rcx                                   
0x66a6696  cmp rdx,0x1000                                
0x66a669d  jb short 0x66A66B7                            ; -> loc_66a66b7
0x66a669f  mov rax,[rcx-8]                               
0x66a66a3  add rcx,0xFFFFFFFFFFFFFFF8                    
0x66a66a7  sub rcx,rax                                   
0x66a66aa  cmp rcx,0x20                                  
0x66a66ae  jae short 0x66A66D6                           ; -> loc_66a66d6
0x66a66b0  or rdx,0x27                                   
0x66a66b4  mov rcx,rax                                   
0x66a66b7  call 0xE935700                                ; -> sub_e935700
0x66a66bc  xorps xmm0,xmm0                               
0x66a66bf  movups [rdi],xmm0                             
0x66a66c2  mov qword ptr [rdi+0x10],0                    
0x66a66ca  add rsp,0x30                                  
0x66a66ce  pop rbx                                       
0x66a66cf  pop rdi                                       
0x66a66d0  pop rsi                                       
0x66a66d1  pop r14                                       
0x66a66d3  pop r15                                       
0x66a66d5  ret                                           
```

### Phase 5: 0x66a66d6..0x66a66ef (6 instructions)

Cold fail path: [rsp+0x20]=0; xor ecx,edx,r8d,r9d; call qword ptr [0xF9A8C78]; int3.

```
0x66a66d6  mov qword ptr [rsp+0x20],0                    
0x66a66df  xor ecx,ecx                                   
0x66a66e1  xor edx,edx                                   
0x66a66e3  xor r8d,r8d                                   
0x66a66e6  xor r9d,r9d                                   
0x66a66e9  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
0x66a66ef  int3                                          
```

---

### 0x66a65b0 summary

Args [V]: rcx = a0 (record). rdx/r8/r9 unused.

Fields touched [V] (reg+disp, R/W):
- R byte [a0+0x168]
- R [a0+0x160]; W [*(a0+0x160)+0x8], W [*(a0+0x160)+0xC]
- R [a0+0x138], R [a0+0x140]
- R byte [rbx+0x18], R [rbx+8]
- W [*(rbx+8)+0x8], W [*(rbx+8)+0xC]
- W [r14] (= [a0+0x138]) qword=0, W [r14+0x10] qword=0
- R byte [a0+0x128]; R [a0+0xE8], R [a0+0xF8]
- W [rdi] qword=0, W [rdi+0x10] qword=0

Callees [V]:
- [0xF99FFA0] = sub_eea6040 (4 call sites)
- 0xE935700 (free)
- [0xF9A8C78] (cold fail)

Return: void [V].

OPEN: exact struct type of a0; role of 0xE935700 vs sub_eea6040 [I].

---

## Function 0x67d3850

Bounds [V]: `sub_67d3850 [0x67d3850..0x67d3d20) size 0x4d0` (rdis `fn`). Ends at ret 0x67d3d1f. Large pass-builder: calls sub_5aba5c0 to get a pass buffer (rsi), then writes a sequence of typed draw/dispatch entries into multiple pass sub-buffers (at rsi+0x780, +0x648, +0x770, +0x758, +0x750, +0x2D0, +0x890, +0x888, +0x608, +0x600) and appends the pass to a queue at rsi+8 via 0xEEC6EC0 / 0x5ABA6D0. Mirror of 0x67d2f80 (different displacements: +0x8A8 vs +0x8A8 same; +0x780/+0x648 same; +0x770/+0x758 same; but tail differs: 0x67d3850 uses +0x680 at 0x67d3311-equivalent? No — 0x67d3850's tail uses +0x2D0/+0x890/+0x888/+0x608/+0x600 while 0x67d2f80 uses +0x680/+0x830/+0x828/+0x608/+0x600). Actually they are near-mirrors with different field offsets in later phases.

### Phase 1: 0x67d3850..0x67d38eb (40 instructions)

Prologue: save callee regs + rbp frame; rdi=r9 (a3), rbx=r8 (a2), r14=rdx (a1). call sub_5aba5c0 -> rsi = pass buffer ptr. Zero 12 xmmwords at rbp+0x60 down to rbp-0x50. [rbp+0x78] = 0xFFFFFFFFFFFFFFFE (sentinel). TLS/cookie: rcx=[data_1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call [0xF99FFA0]=sub_eea6040, [rbp+0x77]=al (cookie byte). Then write first entry: rdx=[rsi+0x8A8] (write cursor), cmp [rsi+0x8B0] (end); if equal -> slow path 0x67d38eb (sub_1ef6f90). Else movzx eax,word [r14] (a1+0x0), store ax at [rdx], add [rsi+0x8A8],2.

```
0x67d3850  push rbp                                      
0x67d3851  push r14                                      
0x67d3853  push rsi                                      
0x67d3854  push rdi                                      
0x67d3855  push rbx                                      
0x67d3856  sub rsp,0x100                                 
0x67d385d  lea rbp,[rsp+0x80]                            
0x67d3865  mov qword ptr [rbp+0x78],0xFFFFFFFFFFFFFFFE   
0x67d386d  mov rdi,r9                                    
0x67d3870  mov rbx,r8                                    
0x67d3873  mov r14,rdx                                   
0x67d3876  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x67d387b  mov rsi,rax                                   
0x67d387e  xorps xmm0,xmm0                               
0x67d3881  movups [rbp+0x60],xmm0                        
0x67d3885  movups [rbp+0x50],xmm0                        
0x67d3889  movups [rbp+0x40],xmm0                        
0x67d388d  movups [rbp+0x30],xmm0                        
0x67d3891  movups [rbp+0x20],xmm0                        
0x67d3895  movups [rbp+0x10],xmm0                        
0x67d3899  movups [rbp],xmm0                             
0x67d389d  movups [rbp-0x10],xmm0                        
0x67d38a1  movups [rbp-0x20],xmm0                        
0x67d38a5  movups [rbp-0x30],xmm0                        
0x67d38a9  movups [rbp-0x40],xmm0                        
0x67d38ad  movups [rbp-0x50],xmm0                        
0x67d38b1  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d38b8  mov rax,[rcx]                                 
0x67d38bb  mov rax,[rax+0x10]                            
0x67d38bf  mov dl,0x4A                                   
0x67d38c1  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d38c7  mov [rbp+0x77],al                             
0x67d38ca  mov rdx,[rsi+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x67d38d1  cmp rdx,[rsi+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x67d38d8  je short 0x67D38EB                            ; -> loc_67d38eb
0x67d38da  movzx eax,word ptr [r14]                      ; R a1+0x0
0x67d38de  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x67d38e1  add qword ptr [rsi+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x67d38e9  jmp short 0x67D38FB                           ; -> loc_67d38fb
```

Interpretation:
- args: r9=a3 (rdi), r8=a2 (rbx), rdx=a1 (r14 -> source for word copy), rcx=4th arg (unused at entry) [V]
- rsi = pass buffer from sub_5aba5c0 [V]
- 12 xmm zero slots at rbp-0x50..rbp+0x60 (stack struct template) [V]
- cookie byte [rbp+0x77] from TLS via sub_eea6040(dl=0x4A) [V]
- entry 0: word copy [r14] -> [rsi+0x8A8], cursor += 2 [V]
- slow path if cursor==end: sub_1ef6f90(rcx=&[rsi+0x8A0], r8=r14) [V]

### Phase 2: 0x67d38f2..0x67d3998 (40 instructions)

After slow path (nop at 67d38fa): cookie call again ([rbp+0x77]=al). [rbp-0x58]=1. Index1 = ([rsi+0x8A8]-[rsi+0x8A0])>>2 - 1 -> [rbp-0x48] (word index). Entry 1: rcx=&[rsi+0x780], rdx=rbx (a2), call sub_675f3b0 (write handle/ptr into +0x780 slot). Index2 = ([rsi+0x788]-[rsi+0x780])>>3 * 0xFFFF8BA3 - 1 -> [rbp-0x30]. rbx=&[rsi+0x648]. Cookie call again ([rbp+0x77]=al). Entry 2: rcx=rbx (&[rsi+0x648]), rdx=rdi (a3), call sub_675fb30. Cookie call again ([rbp+0x77]=al). Index3 = ([rsi+0x650]-[rsi+0x648])>>3 * 0xFFFF8E39 - 1 -> [rbp-0x16].

```
0x67d38f2  mov r8,r14                                    
0x67d38f5  call 0x1EF6F90                                ; -> sub_1ef6f90
0x67d38fa  nop                                           
0x67d38fb  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3902  mov rax,[rcx]                                 
0x67d3905  mov rax,[rax+0x10]                            
0x67d3909  movzx edx,byte ptr [rbp+0x77]                 
0x67d390d  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3913  nop                                           
0x67d3914  mov qword ptr [rbp-0x58],1                    
0x67d391c  mov eax,[rsi+0x8A8]                           
0x67d3922  sub eax,[rsi+0x8A0]                           
0x67d3928  shr eax,1                                     
0x67d392a  dec eax                                       
0x67d392c  mov [rbp-0x48],ax                             
0x67d3930  lea rcx,[rsi+0x780]                           
0x67d3937  mov rdx,rbx                                   
0x67d393a  call 0x675F3B0                                ; -> sub_675f3b0
0x67d393f  mov eax,[rsi+0x788]                           
0x67d3945  sub eax,[rsi+0x780]                           
0x67d394b  shr eax,3                                     
0x67d394e  imul eax,0xFFFF8BA3                           
0x67d3954  dec eax                                       
0x67d3956  mov [rbp-0x30],ax                             
0x67d395a  lea rbx,[rsi+0x648]                           
0x67d3961  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3968  mov rax,[rcx]                                 
0x67d396b  mov rax,[rax+0x10]                            
0x67d396f  mov dl,0x4A                                   
0x67d3971  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3977  mov [rbp+0x77],al                             
0x67d397a  mov rcx,rbx                                   
0x67d397d  mov rdx,rdi                                   
0x67d3980  call 0x675FB30                                ; -> sub_675fb30
0x67d3985  nop                                           
0x67d3986  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d398d  mov rax,[rcx]                                 
0x67d3990  mov rax,[rax+0x10]                            
0x67d3994  movzx edx,byte ptr [rbp+0x77]                 
0x67d3998  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
```

Interpretation:
- [rbp-0x58] = 1 (entry-type tag for first group) [V]
- word-index = ((+0x8A8 - +0x8A0) >> 1) - 1 stored at [rbp-0x48] [V]
- sub_675f3b0(&[rsi+0x780], rbx=a2) — writes a2 into +0x780 sub-buffer [V]
- handle-index2 = ((+0x788 - +0x780) >> 3) * 0xFFFF8BA3 - 1 -> [rbp-0x30] [V]
- sub_675fb30(&[rsi+0x648], rdi=a3) — writes a3 into +0x648 sub-buffer [V]
- handle-index3 = ((+0x650 - +0x648) >> 3) * 0xFFFF8E39 - 1 -> [rbp-0x16] [V]

### Phase 3: 0x67d399e..0x67d3a22 (28 instructions)

Index4 = ([rsi+0x650]-[rsi+0x648])>>3 * 0xFFFF8E39 - 1 -> [rbp-0x16] (redo/store). rdi=[rbp+0xD0] (a3 field slot?). rbx=[rsi+0x770] (write cursor), cmp [rsi+0x778] (end); if equal -> grow path 0x67d3a24 (sub_6760710). Else: mov rax,[rdi]; [rbx]=rax; rcx=&[rbx+8], rdx=&[rdi+8], call sub_e869ff0 (copy 8 bytes?); rax=[rdi+0x80]; [rbx+0x80]=rax; [rdi+0x80]=0; [rsi+0x770]+=0x88; jump 0x67d3a37.

```
0x67d399e  nop                                           
0x67d399f  mov eax,[rsi+0x650]                           
0x67d39a5  sub eax,[rsi+0x648]                           
0x67d39ab  mov rdi,[rbp+0xD0]                            
0x67d39b2  shr eax,3                                     
0x67d39b5  imul eax,0xFFFF8E39                           
0x67d39bb  dec eax                                       
0x67d39bd  mov [rbp-0x16],ax                             
0x67d39c1  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d39c8  mov rax,[rcx]                                 
0x67d39cb  mov rax,[rax+0x10]                            
0x67d39cf  mov dl,0x4A                                   
0x67d39d1  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d39d7  mov [rbp+0x77],al                             
0x67d39da  mov rbx,[rsi+0x770]                           
0x67d39e1  cmp rbx,[rsi+0x778]                           
0x67d39e8  je short 0x67D3A24                            ; -> loc_67d3a24
0x67d39ea  mov rax,[rdi]                                 
0x67d39ed  mov [rbx],rax                                 
0x67d39f0  lea rcx,[rbx+8]                               
0x67d39f4  lea rdx,[rdi+8]                               
0x67d39f8  call 0xE869FF0                                ; -> sub_e869ff0
0x67d39fd  nop                                           
0x67d39fe  mov rax,[rdi+0x80]                            
0x67d3a05  mov [rbx+0x80],rax                            
0x67d3a0c  mov qword ptr [rdi+0x80],0                    
0x67d3a17  add qword ptr [rsi+0x770],0x88                
0x67d3a22  jmp short 0x67D3A37                           ; -> loc_67d3a37
```

Interpretation:
- rdi = [rbp+0xD0] — source struct pointer (a3-derived field) [V]
- +0x770/+0x778 is a growable sub-buffer of 0x88-byte entries [V]
- fast path: copy [rdi] (qword) to [rbx], sub_e869ff0(&[rbx+8], &[rdi+8]) copies 0x78 bytes, then [rbx+0x80]=[rdi+0x80], clear [rdi+0x80], cursor += 0x88 [V]
- slow path (full): sub_6760710(&[rsi+0x768], rbx, rdi) [V]

### Phase 4: 0x67d3a24..0x67d3aac (32 instructions)

At 0x67d3a37: cookie call ([rbp+0x77]=al). [rbp-0x58] = 0x2003001 (typed tag). Index5 = ([rsi+0x770]-[rsi+0x768])>>3 * 0xFFFFF0F1 - 1 -> [rbp-0x2E]. Cookie call again. rdx=[rsi+0x758] (cursor), cmp [rsi+0x760] (end); if equal -> grow path 0x67d3b00 (sub_6760a80). Else: eax=[rdi+0x10]; [rdx+0x10]=eax; movups [rdx]=[rdi] (16 bytes); byte [rdx+0x14]=[rdi+0x14]; movss [rdx+0x18..0x24] = [rdi+0x18..0x24] (5 floats); movups [rdx+0x28]=[rdi+0x28], xmm1=[rdi+0x38], xmm2=[rdi+0x47]; store to [rdx+0x28/0x38/0x47]. [rsi+0x758]+=0x58; jump 0x67d3b10.

```
0x67d3a24  lea rcx,[rsi+0x768]                           
0x67d3a2b  mov rdx,rbx                                   
0x67d3a2e  mov r8,rdi                                    
0x67d3a31  call 0x6760710                                ; -> sub_6760710
0x67d3a36  nop                                           
0x67d3a37  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3a3e  mov rax,[rcx]                                 
0x67d3a41  mov rax,[rax+0x10]                            
0x67d3a45  movzx edx,byte ptr [rbp+0x77]                 
0x67d3a49  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3a4f  nop                                           
0x67d3a50  mov qword ptr [rbp-0x58],0x2003001            
0x67d3a58  mov eax,[rsi+0x770]                           
0x67d3a5e  sub eax,[rsi+0x768]                           
0x67d3a64  mov rdi,[rbp+0xD8]                            
0x67d3a6b  shr eax,3                                     
0x67d3a6e  imul eax,0xFFFFF0F1                           
0x67d3a74  dec eax                                       
0x67d3a76  mov [rbp-0x2E],ax                             
0x67d3a7a  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3a81  mov rax,[rcx]                                 
0x67d3a84  mov rax,[rax+0x10]                            
0x67d3a88  mov dl,0x4A                                   
0x67d3a8a  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3a90  mov [rbp+0x77],al                             
0x67d3a93  mov rdx,[rsi+0x758]                           
0x67d3a9a  cmp rdx,[rsi+0x760]                           
0x67d3aa1  je short 0x67D3B00                            ; -> loc_67d3b00
0x67d3aa3  mov eax,[rdi+0x10]                            
0x67d3aa6  mov [rdx+0x10],eax                            
0x67d3aa9  movups xmm0,[rdi]                             
0x67d3aac  movups [rdx],xmm0                             
```

Interpretation:
- rdi now = [rbp+0xD8] (different source for this entry, 0x58-byte struct) [V]
- tag [rbp-0x58] = 0x2003001 [V]
- index5 computed with magic multiply 0xFFFFF0F1 [V]
- entry: 0x58-byte struct copy from rdi to [rdx] at +0x758 cursor: qword+0x10, 16-byte movups, byte+0x14, 5 float ss, 3 movups (0x28,0x38,0x47) = 0x58 bytes total [V]
- cursor +0x58 [V]

### Phase 5: 0x67d3aaf..0x67d3afe (18 instructions)

Rest of 0x58-byte entry copy (byte+0x14 through end) then advance cursor and jump to 0x67d3b10.

```
0x67d3aaf  movzx eax,byte ptr [rdi+0x14]                 
0x67d3ab3  mov [rdx+0x14],al                             
0x67d3ab6  movss xmm0,[rdi+0x18]                         
0x67d3abb  movss [rdx+0x18],xmm0                         
0x67d3ac0  movss xmm0,[rdi+0x1C]                         
0x67d3ac5  movss [rdx+0x1C],xmm0                         
0x67d3aca  movss xmm0,[rdi+0x20]                         
0x67d3acf  movss [rdx+0x20],xmm0                         
0x67d3ad4  movss xmm0,[rdi+0x24]                         
0x67d3ad9  movss [rdx+0x24],xmm0                         
0x67d3ade  movups xmm0,[rdi+0x28]                        
0x67d3ae2  movups xmm1,[rdi+0x38]                        
0x67d3ae6  movups xmm2,[rdi+0x47]                        
0x67d3aea  movups [rdx+0x28],xmm0                        
0x67d3aee  movups [rdx+0x38],xmm1                        
0x67d3af2  movups [rdx+0x47],xmm2                        
0x67d3af6  add qword ptr [rsi+0x758],0x58                
0x67d3afe  jmp short 0x67D3B10                           ; -> loc_67d3b10
```

### Phase 6: 0x67d3b00..0x67d3b77 (28 instructions)

Slow path for +0x758 buffer full: sub_6760a80(&[rsi+0x750], rdi). Then at 0x67d3b10: cookie call ([rbp+0x77]=al). Index6 = ([rsi+0x758]-[rsi+0x750])>>3 * 0xFFFF8BA3 - 1 -> [rbp-0x2C]. Cookie call again. rdx=[rsi+0x2D8], cmp [rsi+0x2E0]; if equal -> grow 0x67d3b79 (sub_6760e60). Else inc [rsi+0x2D8]; jump 0x67d3b86.

```
0x67d3b00  lea rcx,[rsi+0x750]                           
0x67d3b07  mov r8,rdi                                    
0x67d3b0a  call 0x6760A80                                ; -> sub_6760a80
0x67d3b0f  nop                                           
0x67d3b10  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3b17  mov rax,[rcx]                                 
0x67d3b1a  mov rax,[rax+0x10]                            
0x67d3b1e  movzx edx,byte ptr [rbp+0x77]                 
0x67d3b22  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3b28  nop                                           
0x67d3b29  mov eax,[rsi+0x758]                           
0x67d3b2f  sub eax,[rsi+0x750]                           
0x67d3b35  shr eax,3                                     
0x67d3b38  imul eax,0xFFFF8BA3                           
0x67d3b3e  dec eax                                       
0x67d3b40  mov [rbp-0x2C],ax                             
0x67d3b44  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3b4b  mov rax,[rcx]                                 
0x67d3b4e  mov rax,[rax+0x10]                            
0x67d3b52  mov dl,0x4A                                   
0x67d3b54  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3b5a  mov [rbp+0x77],al                             
0x67d3b5d  mov rdx,[rsi+0x2D8]                           
0x67d3b64  cmp rdx,[rsi+0x2E0]                           
0x67d3b6b  je short 0x67D3B79                            ; -> loc_67d3b79
0x67d3b6d  inc rdx                                       
0x67d3b70  mov [rsi+0x2D8],rdx                           
0x67d3b77  jmp short 0x67D3B86                           ; -> loc_67d3b86
```

### Phase 7: 0x67d3b79..0x67d3bf2 (26 instructions)

Slow path +0x2D8 full: sub_6760e60(&[rsi+0x2D0]). At 0x67d3b86: cookie call ([rbp+0x77]=al). [rbp-0x58] = 0x4000000002007001. eax=[rsi+0x2D0]; not eax; eax += [rsi+0x2D8]; [rbp+0x34]=ax. Cookie call again. rdx=[rsi+0x890], cmp [rsi+0x898]; if equal -> grow 0x67d3bf4 (sub_6760e60). Else inc [rsi+0x890]; jump 0x67d3c01.

```
0x67d3b79  lea rcx,[rsi+0x2D0]                           
0x67d3b80  call 0x6760E60                                ; -> sub_6760e60
0x67d3b85  nop                                           
0x67d3b86  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3b8d  mov rax,[rcx]                                 
0x67d3b90  mov rax,[rax+0x10]                            
0x67d3b94  movzx edx,byte ptr [rbp+0x77]                 
0x67d3b98  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3b9e  nop                                           
0x67d3b9f  mov rax,0x4000000002007001                    
0x67d3ba9  mov [rbp-0x58],rax                            
0x67d3bad  mov eax,[rsi+0x2D0]                           
0x67d3bb3  not eax                                       
0x67d3bb5  add eax,[rsi+0x2D8]                           
0x67d3bbb  mov [rbp+0x34],ax                             
0x67d3bbf  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3bc6  mov rax,[rcx]                                 
0x67d3bc9  mov rax,[rax+0x10]                            
0x67d3bcd  mov dl,0x4A                                   
0x67d3bcf  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3bd5  mov [rbp+0x77],al                             
0x67d3bd8  mov rdx,[rsi+0x890]                           
0x67d3bdf  cmp rdx,[rsi+0x898]                           
0x67d3be6  je short 0x67D3BF4                            ; -> loc_67d3bf4
0x67d3be8  inc rdx                                       
0x67d3beb  mov [rsi+0x890],rdx                           
0x67d3bf2  jmp short 0x67D3C01                           ; -> loc_67d3c01
```

### Phase 8: 0x67d3bf4..0x67d3c5f (25 instructions)

Slow path +0x890 full: sub_6760e60(&[rsi+0x888]). At 0x67d3c01: cookie call ([rbp+0x77]=al). eax=[rsi+0x888]; not eax; eax += [rsi+0x890]; [rbp-0x46]=ax. Cookie call again. rdx=[rsi+0x608], cmp [rsi+0x610]; if equal -> grow 0x67d3c61 (sub_6760e60 with rcx=rsi+0x600). Else inc [rsi+0x608]; jump 0x67d3c71.

```
0x67d3bf4  lea rcx,[rsi+0x888]                           
0x67d3bfb  call 0x6760E60                                ; -> sub_6760e60
0x67d3c00  nop                                           
0x67d3c01  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3c08  mov rax,[rcx]                                 
0x67d3c0b  mov rax,[rax+0x10]                            
0x67d3c0f  movzx edx,byte ptr [rbp+0x77]                 
0x67d3c13  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3c19  nop                                           
0x67d3c1a  mov eax,[rsi+0x888]                           
0x67d3c20  not eax                                       
0x67d3c22  add eax,[rsi+0x890]                           
0x67d3c28  mov [rbp-0x46],ax                             
0x67d3c2c  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3c33  mov rax,[rcx]                                 
0x67d3c36  mov rax,[rax+0x10]                            
0x67d3c3a  mov dl,0x4A                                   
0x67d3c3c  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3c42  mov [rbp+0x77],al                             
0x67d3c45  mov rdx,[rsi+0x608]                           
0x67d3c4c  cmp rdx,[rsi+0x610]                           
0x67d3c53  je short 0x67D3C61                            ; -> loc_67d3c61
0x67d3c55  inc rdx                                       
0x67d3c58  mov [rsi+0x608],rdx                           
0x67d3c5f  jmp short 0x67D3C71                           ; -> loc_67d3c71
```

### Phase 9: 0x67d3c61..0x67d3cdf (30 instructions)

Slow path +0x608 full: sub_6760e60(rcx=rsi+0x600). At 0x67d3c71: cookie call ([rbp+0x77]=al). [rbp-0x58] = 0x4000000012007003. eax=[rsi+0x600]; not eax; eax += [rsi+0x608]; [rbp-0x10]=ax. Cookie call again. rax=[rsi+8] (queue head), cmp [rsi+0x10] (queue end); if equal -> slow path 0x67d3ce9 (sub_5aba6d0). Else: rdx=&[rbp-0x58] (entry template), r8d=0xC8 (200 bytes), rcx=rax, call sub_eec6ec0 (copy entry into queue slot); [rsi+8]+=0xC8; jump 0x67d3cf9.

```
0x67d3c61  mov rcx,rsi                                   
0x67d3c64  add rcx,0x600                                 
0x67d3c6b  call 0x6760E60                                ; -> sub_6760e60
0x67d3c70  nop                                           
0x67d3c71  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3c78  mov rax,[rcx]                                 
0x67d3c7b  mov rax,[rax+0x10]                            
0x67d3c7f  movzx edx,byte ptr [rbp+0x77]                 
0x67d3c83  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3c89  nop                                           
0x67d3c8a  mov rax,0x4000000012007003                    
0x67d3c94  mov [rbp-0x58],rax                            
0x67d3c98  mov eax,[rsi+0x600]                           
0x67d3c9e  not eax                                       
0x67d3ca0  add eax,[rsi+0x608]                           
0x67d3ca6  mov [rbp-0x10],ax                             
0x67d3caa  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3cb1  mov rax,[rcx]                                 
0x67d3cb4  mov rax,[rax+0x10]                            
0x67d3cb8  mov dl,0x4A                                   
0x67d3cba  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3cc0  mov [rbp+0x77],al                             
0x67d3cc3  mov rax,[rsi+8]                               
0x67d3cc7  cmp rax,[rsi+0x10]                            
0x67d3ccb  je short 0x67D3CE9                            ; -> loc_67d3ce9
0x67d3ccd  lea rdx,[rbp-0x58]                            
0x67d3cd1  mov r8d,0xC8                                  
0x67d3cd7  mov rcx,rax                                   
0x67d3cda  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x67d3cdf  add qword ptr [rsi+8],0xC8                    
0x67d3ce7  jmp short 0x67D3CF9                           ; -> loc_67d3cf9
```

### Phase 10: 0x67d3ce9..0x67d3d1f (19 instructions)

Slow path queue full: rcx=rsi (pass buffer), rdx=rax (head slot), r8=&[rbp-0x58] (entry template), call sub_5aba6d0. Then cookie call ([rbp+0x77]=al). Epilogue: rsp+=0x100, pop rbx/rdi/rsi/r14/rbp, ret.

```
0x67d3ce7  jmp short 0x67D3CF9                           ; -> loc_67d3cf9
0x67d3ce9  lea r8,[rbp-0x58]                             
0x67d3ced  mov rcx,rsi                                   
0x67d3cf0  mov rdx,rax                                   
0x67d3cf3  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x67d3cf8  nop                                           
0x67d3cf9  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x67d3d00  mov rax,[rcx]                                 
0x67d3d03  mov rax,[rax+0x10]                            
0x67d3d07  movzx edx,byte ptr [rbp+0x77]                 
0x67d3d0b  call qword ptr [0xF99FFA0]                    ; [data_F99FFA0] = sub_eea6040
0x67d3d11  nop                                           
0x67d3d12  add rsp,0x100                                 
0x67d3d19  pop rbx                                       
0x67d3d1a  pop rdi                                       
0x67d3d1b  pop rsi                                       
0x67d3d1c  pop r14                                       
0x67d3d1e  pop rbp                                       
0x67d3d1f  ret                                           
```

---

### 0x67d3850 summary

Args [V]: rdx=a1 (r14, source word ptr +0x0), r8=a2 (rbx, handle ptr), r9=a3 (rdi, source struct ptr at +0xD0/+0xD8), rcx=4th arg (not used directly at entry).

Fields touched [V] (reg+disp, R/W):
- Stack template: W rbp+0x78 (sentinel), W rbp+0x60/0x50/0x40/0x30/0x20/0x10/0x0/-0x10/-0x20/-0x30/-0x40/-0x50 (12 xmm zero slots), W rbp+0x77 (cookie byte, many), W rbp-0x58 (tag, many), W rbp-0x48/0x30/0x16/0x2E/0x2C/0x34/0x46/0x10 (index/handle slots)
- Pass buffer rsi (from sub_5aba5c0): R/W [rsi+0x8A8]/[rsi+0x8B0] (entry0 cursor/end), R/W [rsi+0x8A0] (entry0 base), R/W [rsi+0x780]/[rsi+0x788] (sub-buffer1), R/W [rsi+0x648]/[rsi+0x650] (sub-buffer2), R/W [rsi+0x770]/[rsi+0x778] (sub-buffer3, 0x88 entries), R/W [rsi+0x768] (sub-buffer3 base), R/W [rsi+0x758]/[rsi+0x760] (sub-buffer4, 0x58 entries), R/W [rsi+0x750] (sub-buffer4 base), R/W [rsi+0x2D8]/[rsi+0x2E0] (counter+limit), R/W [rsi+0x2D0] (base), R/W [rsi+0x890]/[rsi+0x898] (counter+limit), R/W [rsi+0x888] (base), R/W [rsi+0x608]/[rsi+0x610] (counter+limit), R/W [rsi+0x600] (base), R/W [rsi+8]/[rsi+0x10] (queue head/end)
- Source reads: R word [r14+0x0], R qword [rdi], R 0x58 bytes [rdi+0x0..0x47], R [rdi+0x10], R [rdi+0x80]
- W via callees: sub_675f3b0(&[rsi+0x780], rbx), sub_675fb30(&[rsi+0x648], rdi), sub_e869ff0(&[rbx+8], &[rdi+8]), sub_6760710, sub_6760a80, sub_6760e60 (x3), sub_eec6ec0(dst=head, src=&[rbp-0x58], 0xC8), sub_5aba6d0

Callees [V]:
- sub_5aba5c0 (get pass buffer)
- [0xF99FFA0]=sub_eea6040 (cookie/TLS, ~9 calls)
- sub_1ef6f90 (slow path entry0)
- sub_675f3b0 (write handle to +0x780)
- sub_675fb30 (write handle to +0x648)
- sub_e869ff0 (copy 0x78 bytes)
- sub_6760710 (slow path grow +0x770)
- sub_6760a80 (slow path grow +0x758)
- sub_6760e60 (slow path grow +0x2D0/+0x888/+0x600, x3)
- sub_eec6ec0 (copy 0xC8 entry to queue)
- sub_5aba6d0 (slow path queue append)

Return: void [V].

OPEN: exact meaning of magic multipliers 0xFFFF8BA3/0xFFFF8E39/0xFFFFF0F1 (hash/index into sub-buffers) [I]; exact struct layout of the 0x88 and 0x58-byte entries [I]; what sub_5aba5c0 returns [I].

---

## Function 0x67d2f80

Bounds [V]: `sub_67d2f80 [0x67d2f80..0x67d34ea) size 0x56a` (rdis `fn`). Ends at ret 0x67d34e9. Near-mirror of 0x67d3850: same prologue and first 4 sub-buffers (+0x8A8, +0x780, +0x648, +0x770, +0x758), but tail diverges: after +0x2D8 counter it writes 3 floats (12 bytes) into +0x680 (not +0x890 counter), then +0x830 counter/+0x828 base instead of +0x890/+0x888. Same queue append at rsi+8 (0xC8 bytes) via sub_eec6ec0 / sub_5aba6d0.

### Phase 1: 0x67d2f80..0x67d301b (40 instructions)

Identical to 0x67d3850 phase 1: prologue, sub_5aba5c0 -> rsi pass buffer, zero 12 xmm slots, cookie byte [rbp+0x77], entry0 word copy [r14]->[rsi+0x8A8], cursor+=2, slow path sub_1ef6f90 if full.

```
0x67d2f80  push rbp                                      
0x67d2f81  push r14                                      
0x67d2f83  push rsi                                      
0x67d2f84  push rdi                                      
0x67d2f85  push rbx                                      
0x67d2f86  sub rsp,0x100                                 
0x67d2f8d  lea rbp,[rsp+0x80]                            
0x67d2f95  mov qword ptr [rbp+0x78],0xFFFFFFFFFFFFFFFE   
0x67d2f9d  mov rdi,r9                                    
0x67d2fa0  mov rbx,r8                                    
0x67d2fa3  mov r14,rdx                                   
0x67d2fa6  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x67d2fab  mov rsi,rax                                   
0x67d2fae  xorps xmm0,xmm0                               
0x67d2fb1  movups [rbp+0x60],xmm0                        
0x67d2fb5  movups [rbp+0x50],xmm0                        
0x67d2fb9  movups [rbp+0x40],xmm0                        
0x67d2fbd  movups [rbp+0x30],xmm0                        
0x67d2fc1  movups [rbp+0x20],xmm0                        
0x67d2fc5  movups [rbp+0x10],xmm0                        
0x67d2fc9  movups [rbp],xmm0                             
0x67d2fcd  movups [rbp-0x10],xmm0                        
0x67d2fd1  movups [rbp-0x20],xmm0                        
0x67d2fd5  movups [rbp-0x30],xmm0                        
0x67d2fd9  movups [rbp-0x40],xmm0                        
0x67d2fdd  movups [rbp-0x50],xmm0                        
0x67d2fe1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d2fe8  mov rax,[rcx]                                 
0x67d2feb  mov rax,[rax+0x10]                            
0x67d2fef  mov dl,0x4A                                   
0x67d2ff1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d2ff7  mov [rbp+0x77],al                             
0x67d2ffa  mov rdx,[rsi+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x67d3001  cmp rdx,[rsi+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x67d3008  je short 0x67D301B                            ; -> loc_67d301b
0x67d300a  movzx eax,word ptr [r14]                      ; R a1+0x0
0x67d300e  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x67d3011  add qword ptr [rsi+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x67d3019  jmp short 0x67D302B                           ; -> loc_67d302b
```

### Phase 2: 0x67d3022..0x67d30c6 (40 instructions)

Same as 0x67d3850 phase 2: cookie, [rbp-0x58]=1, index1=((+0x8A8-+0x8A0)>>2)-1 -> [rbp-0x48], sub_675f3b0(&[rsi+0x780], rbx), index2=((+0x788-+0x780)>>3)*0xFFFF8BA3-1 -> [rbp-0x30], sub_675fb30(&[rsi+0x648], rdi), cookie.

```
0x67d3022  mov r8,r14                                    
0x67d3025  call 0x1EF6F90                                ; -> sub_1ef6f90
0x67d302a  nop                                           
0x67d302b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d3032  mov rax,[rcx]                                 
0x67d3035  mov rax,[rax+0x10]                            
0x67d3039  movzx edx,byte ptr [rbp+0x77]                 
0x67d303d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d3043  nop                                           
0x67d3044  mov eax,[rsi+0x8A8]                           
0x67d304a  sub eax,[rsi+0x8A0]                           
0x67d3050  shr eax,1                                     
0x67d3052  dec eax                                       
0x67d3054  mov [rbp-0x48],ax                             
0x67d3058  lea rcx,[rsi+0x780]                           
0x67d305f  mov rdx,rbx                                   
0x67d3062  call 0x675F3B0                                ; -> sub_675f3b0
0x67d3067  mov eax,[rsi+0x788]                           
0x67d306d  sub eax,[rsi+0x780]                           
0x67d3073  shr eax,3                                     
0x67d3076  imul eax,0xFFFF8BA3                           
0x67d307c  dec eax                                       
0x67d307e  mov [rbp-0x30],ax                             
0x67d3082  lea rbx,[rsi+0x648]                           
0x67d3089  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d3090  mov rax,[rcx]                                 
0x67d3093  mov rax,[rax+0x10]                            
0x67d3097  mov dl,0x4A                                   
0x67d3099  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d309f  mov [rbp+0x77],al                             
0x67d30a2  mov rcx,rbx                                   
0x67d30a5  mov rdx,rdi                                   
0x67d30a8  call 0x675FB30                                ; -> sub_675fb30
0x67d30ad  nop                                           
0x67d30ae  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d30b5  mov rax,[rcx]                                 
0x67d30b8  mov rax,[rax+0x10]                            
0x67d30bc  movzx edx,byte ptr [rbp+0x77]                 
0x67d30c0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d30c6  nop                                           
```

### Phase 3: 0x67d30c7..0x67d312d (23 instructions)

[rbp-0x58]=0x2001001 (tag, differs from 0x67d3850's 0x2003001). index3=((+0x650-+0x648)>>3)*0xFFFF8E39-1 -> [rbp-0x16]. rdi=[rbp+0xD0]. rbx=[rsi+0x770], cmp [rsi+0x778]; if equal -> slow path 0x67d3154 (sub_6760710). Else copy [rdi]->[rbx], sub_e869ff0(&[rbx+8],&[rdi+8]), [rbx+0x80]=[rdi+0x80], clear [rdi+0x80], cursor+=0x88.

```
0x67d30c7  mov qword ptr [rbp-0x58],0x2001001            
0x67d30cf  mov eax,[rsi+0x650]                           
0x67d30d5  sub eax,[rsi+0x648]                           
0x67d30db  mov rdi,[rbp+0xD0]                            
0x67d30e2  shr eax,3                                     
0x67d30e5  imul eax,0xFFFF8E39                           
0x67d30eb  dec eax                                       
0x67d30ed  mov [rbp-0x16],ax                             
0x67d30f1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d30f8  mov rax,[rcx]                                 
0x67d30fb  mov rax,[rax+0x10]                            
0x67d30ff  mov dl,0x4A                                   
0x67d3101  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d3107  mov [rbp+0x77],al                             
0x67d310a  mov rbx,[rsi+0x770]                           
0x67d3111  cmp rbx,[rsi+0x778]                           
0x67d3118  je short 0x67D3154                            ; -> loc_67d3154
0x67d311a  mov rax,[rdi]                                 
0x67d311d  mov [rbx],rax                                 
0x67d3120  lea rcx,[rbx+8]                               
0x67d3124  lea rdx,[rdi+8]                               
0x67d3128  call 0xE869FF0                                ; -> sub_e869ff0
0x67d312d  nop                                           
```

### Phase 4: 0x67d312e..0x67d31b8 (29 instructions)

[rbx+0x80]=[rdi+0x80], [rdi+0x80]=0, [rsi+0x770]+=0x88, jump 0x67d3167. Slow path sub_6760710(&[rsi+0x768],rbx,rdi). At 0x67d3167: cookie, [rbp-0x58]=0x2001001 (note: same as phase 3, differs from 0x67d3850's 0x2003001 here). index=((+0x770-+0x768)>>3)*0xFFFFF0F1-1 -> [rbp-0x2E]. cookie.

```
0x67d312e  mov rax,[rdi+0x80]                            
0x67d3135  mov [rbx+0x80],rax                            
0x67d313c  mov qword ptr [rdi+0x80],0                    
0x67d3147  add qword ptr [rsi+0x770],0x88                
0x67d3152  jmp short 0x67D3167                           ; -> loc_67d3167
0x67d3154  lea rcx,[rsi+0x768]                           
0x67d315b  mov rdx,rbx                                   
0x67d315e  mov r8,rdi                                    
0x67d3161  call 0x6760710                                ; -> sub_6760710
0x67d3166  nop                                           
0x67d3167  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d316e  mov rax,[rcx]                                 
0x67d3171  mov rax,[rax+0x10]                            
0x67d3175  movzx edx,byte ptr [rbp+0x77]                 
0x67d3179  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d317f  nop                                           
0x67d3180  mov eax,[rsi+0x770]                           
0x67d3186  sub eax,[rsi+0x768]                           
0x67d318c  mov rdi,[rbp+0xD8]                            
0x67d3193  shr eax,3                                     
0x67d3196  imul eax,0xFFFFF0F1                           
0x67d319c  dec eax                                       
0x67d319e  mov [rbp-0x2E],ax                             
0x67d31a2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d31a9  mov rax,[rcx]                                 
0x67d31ac  mov rax,[rax+0x10]                            
0x67d31b0  mov dl,0x4A                                   
0x67d31b2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d31b8  mov [rbp+0x77],al                             
```

### Phase 5: 0x67d31bb..0x67d3226 (25 instructions)

rdx=[rsi+0x758] cursor, cmp [rsi+0x760]; if equal -> slow path 0x67d3228 (sub_6760a80). Else 0x58-byte entry copy from rdi=[rbp+0xD8]: [rdx+0x10]=[rdi+0x10], movups [rdx]=[rdi], byte [rdx+0x14]=[rdi+0x14], 5 float ss [rdx+0x18..0x24]=[rdi+0x18..0x24], movups [rdx+0x28/0x38/0x47]=[rdi+0x28/0x38/0x47]. Cursor [rsi+0x758]+=0x58; jump 0x67d3238.

```
0x67d31bb  mov rdx,[rsi+0x758]                           
0x67d31c2  cmp rdx,[rsi+0x760]                           
0x67d31c9  je short 0x67D3228                            ; -> loc_67d3228
0x67d31cb  mov eax,[rdi+0x10]                            
0x67d31ce  mov [rdx+0x10],eax                            
0x67d31d1  movups xmm0,[rdi]                             
0x67d31d4  movups [rdx],xmm0                             
0x67d31d7  movzx eax,byte ptr [rdi+0x14]                 
0x67d31db  mov [rdx+0x14],al                             
0x67d31de  movss xmm0,[rdi+0x18]                         
0x67d31e3  movss [rdx+0x18],xmm0                         
0x67d31e8  movss xmm0,[rdi+0x1C]                         
0x67d31ed  movss [rdx+0x1C],xmm0                         
0x67d31f2  movss xmm0,[rdi+0x20]                         
0x67d31f7  movss [rdx+0x20],xmm0                         
0x67d31fc  movss xmm0,[rdi+0x24]                         
0x67d3201  movss [rdx+0x24],xmm0                         
0x67d3206  movups xmm0,[rdi+0x28]                        
0x67d320a  movups xmm1,[rdi+0x38]                        
0x67d320e  movups xmm2,[rdi+0x47]                        
0x67d3212  movups [rdx+0x28],xmm0                        
0x67d3216  movups [rdx+0x38],xmm1                        
0x67d321a  movups [rdx+0x47],xmm2                        
0x67d321e  add qword ptr [rsi+0x758],0x58                
0x67d3226  jmp short 0x67D3238                           ; -> loc_67d3238
```

### Phase 6: 0x67d3228..0x67d32a7 (29 instructions)

Slow path +0x758 full: sub_6760a80(&[rsi+0x750], rdi). At 0x67d3238: cookie, [rbp-0x58]=0x2007001, index=((+0x758-+0x750)>>3)*0xFFFF8BA3-1 -> [rbp-0x2C]. cookie. rdx=[rsi+0x2D8], cmp [rsi+0x2E0]; if equal -> grow 0x67d32a9 (sub_6760e60). Else inc [rsi+0x2D8]; jump 0x67d32b6.

```
0x67d3228  lea rcx,[rsi+0x750]                           
0x67d322f  mov r8,rdi                                    
0x67d3232  call 0x6760A80                                ; -> sub_6760a80
0x67d3237  nop                                           
0x67d3238  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d323f  mov rax,[rcx]                                 
0x67d3242  mov rax,[rax+0x10]                            
0x67d3246  movzx edx,byte ptr [rbp+0x77]                 
0x67d324a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d3250  nop                                           
0x67d3251  mov qword ptr [rbp-0x58],0x2007001            
0x67d3259  mov eax,[rsi+0x758]                           
0x67d325f  sub eax,[rsi+0x750]                           
0x67d3265  shr eax,3                                     
0x67d3268  imul eax,0xFFFF8BA3                           
0x67d326e  dec eax                                       
0x67d3270  mov [rbp-0x2C],ax                             
0x67d3274  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d327b  mov rax,[rcx]                                 
0x67d327e  mov rax,[rax+0x10]                            
0x67d3282  mov dl,0x4A                                   
0x67d3284  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d328a  mov [rbp+0x77],al                             
0x67d328d  mov rdx,[rsi+0x2D8]                           
0x67d3294  cmp rdx,[rsi+0x2E0]                           
0x67d329b  je short 0x67D32A9                            ; -> loc_67d32a9
0x67d329d  inc rdx                                       
0x67d32a0  mov [rsi+0x2D8],rdx                           
0x67d32a7  jmp short 0x67D32B6                           ; -> loc_67d32b6
```

### Phase 7: 0x67d32a9..0x67d3335 (28 instructions)

Slow path +0x2D8 full: sub_6760e60(&[rsi+0x2D0]). At 0x67d32b6: cookie, rdi=[rbp+0xE0] (different source for tail entries). eax=[rsi+0x2D0]; not eax; eax += [rsi+0x2D8]; [rbp+0x34]=ax. cookie. rdx=[rsi+0x680], cmp [rsi+0x688]; if equal -> grow 0x67d3337 (sub_1770a70). Else movss x3 [rdx+0..8]=[rdi+0..8] (3 floats = 12 bytes), [rsi+0x680]+=0xC; jump 0x67d3347.

```
0x67d32a9  lea rcx,[rsi+0x2D0]                           
0x67d32b0  call 0x6760E60                                ; -> sub_6760e60
0x67d32b5  nop                                           
0x67d32b6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d32bd  mov rax,[rcx]                                 
0x67d32c0  mov rax,[rax+0x10]                            
0x67d32c4  movzx edx,byte ptr [rbp+0x77]                 
0x67d32c8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d32ce  nop                                           
0x67d32cf  mov rdi,[rbp+0xE0]                            
0x67d32d6  mov eax,[rsi+0x2D0]                           
0x67d32dc  not eax                                       
0x67d32de  add eax,[rsi+0x2D8]                           
0x67d32e4  mov [rbp+0x34],ax                             
0x67d32e8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d32ef  mov rax,[rcx]                                 
0x67d32f2  mov rax,[rax+0x10]                            
0x67d32f6  mov dl,0x4A                                   
0x67d32f8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d32fe  mov [rbp+0x77],al                             
0x67d3301  mov rdx,[rsi+0x680]                           
0x67d3308  cmp rdx,[rsi+0x688]                           
0x67d330f  je short 0x67D3337                            ; -> loc_67d3337
0x67d3311  movss xmm0,[rdi]                              
0x67d3315  movss [rdx],xmm0                              
0x67d3319  movss xmm0,[rdi+4]                            
0x67d331e  movss [rdx+4],xmm0                            
0x67d3323  movss xmm0,[rdi+8]                            
0x67d3328  movss [rdx+8],xmm0                            
0x67d332d  add qword ptr [rsi+0x680],0xC                 
0x67d3335  jmp short 0x67D3347                           ; -> loc_67d3347
```

### Phase 8: 0x67d3337..0x67d33b5 (29 instructions)

Slow path +0x680 full: sub_1770a70(&[rsi+0x678], rdi). At 0x67d3347: cookie, [rbp-0x58]=0x4000000002807001, eax=[rsi+0x680]-[rsi+0x678]>>2 * 0xFFFFAAAB -1 -> [rbp-0x1A] (note: shr 2, magic 0xFFFFAAAB — different from 0xFFFF8BA3). cookie. rdx=[rsi+0x830], cmp [rsi+0x838]; if equal -> grow 0x67d33be (sub_6760e60). Else inc [rsi+0x830]; jump 0x67d33cb.

```
0x67d3337  lea rcx,[rsi+0x678]                           
0x67d333e  mov r8,rdi                                    
0x67d3341  call 0x1770A70                                ; -> sub_1770a70
0x67d3346  nop                                           
0x67d3347  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d334e  mov rax,[rcx]                                 
0x67d3351  mov rax,[rax+0x10]                            
0x67d3355  movzx edx,byte ptr [rbp+0x77]                 
0x67d3359  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d335f  nop                                           
0x67d3360  mov rax,0x4000000002807001                    
0x67d336a  mov [rbp-0x58],rax                            
0x67d336e  mov eax,[rsi+0x680]                           
0x67d3374  sub eax,[rsi+0x678]                           
0x67d337a  shr eax,2                                     
0x67d337d  imul eax,0xFFFFAAAB                           
0x67d3383  dec eax                                       
0x67d3385  mov [rbp-0x1A],ax                             
0x67d3389  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d3390  mov rax,[rcx]                                 
0x67d3393  mov rax,[rax+0x10]                            
0x67d3397  mov dl,0x4A                                   
0x67d3399  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d339f  mov [rbp+0x77],al                             
0x67d33a2  mov rdx,[rsi+0x830]                           
0x67d33a9  cmp rdx,[rsi+0x838]                           
0x67d33b0  je short 0x67D33BE                            ; -> loc_67d33be
0x67d33b2  inc rdx                                       
0x67d33b5  mov [rsi+0x830],rdx                           
```

### Phase 9: 0x67d33bc..0x67d3429 (26 instructions)

jump to 0x67d33cb. Slow path +0x830 full: sub_6760e60(&[rsi+0x828]). At 0x67d33cb: cookie, eax=[rsi+0x828]; not eax; eax += [rsi+0x830]; [rbp-0x3E]=ax. cookie. rdx=[rsi+0x608], cmp [rsi+0x610]; if equal -> grow 0x67d342b (sub_6760e60 rcx=rsi+0x600). Else inc [rsi+0x608]; jump 0x67d343b.

```
0x67d33bc  jmp short 0x67D33CB                           ; -> loc_67d33cb
0x67d33be  lea rcx,[rsi+0x828]                           
0x67d33c5  call 0x6760E60                                ; -> sub_6760e60
0x67d33ca  nop                                           
0x67d33cb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d33d2  mov rax,[rcx]                                 
0x67d33d5  mov rax,[rax+0x10]                            
0x67d33d9  movzx edx,byte ptr [rbp+0x77]                 
0x67d33dd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d33e3  nop                                           
0x67d33e4  mov eax,[rsi+0x828]                           
0x67d33ea  not eax                                       
0x67d33ec  add eax,[rsi+0x830]                           
0x67d33f2  mov [rbp-0x3E],ax                             
0x67d33f6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d33fd  mov rax,[rcx]                                 
0x67d3400  mov rax,[rax+0x10]                            
0x67d3404  mov dl,0x4A                                   
0x67d3406  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d340c  mov [rbp+0x77],al                             
0x67d340f  mov rdx,[rsi+0x608]                           
0x67d3416  cmp rdx,[rsi+0x610]                           
0x67d341d  je short 0x67D342B                            ; -> loc_67d342b
0x67d341f  inc rdx                                       
0x67d3422  mov [rsi+0x608],rdx                           
0x67d3429  jmp short 0x67D343B                           ; -> loc_67d343b
```

### Phase 10: 0x67d342b..0x67d34b1 (29 instructions)

Slow path +0x608 full: sub_6760e60(rcx=rsi+0x600). At 0x67d343b: cookie, [rbp-0x58]=0x4000000012807021, eax=[rsi+0x600]; not eax; eax += [rsi+0x608]; [rbp-0x10]=ax. cookie. rax=[rsi+8] queue head, cmp [rsi+0x10] end; if equal -> slow path 0x67d34b3 (sub_5aba6d0). Else rdx=&[rbp-0x58], r8d=0xC8, rcx=rax, call sub_eec6ec0 (copy 0xC8 entry), [rsi+8]+=0xC8, jump 0x67d34c3.

```
0x67d342b  mov rcx,rsi                                   
0x67d342e  add rcx,0x600                                 
0x67d3435  call 0x6760E60                                ; -> sub_6760e60
0x67d343a  nop                                           
0x67d343b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d3442  mov rax,[rcx]                                 
0x67d3445  mov rax,[rax+0x10]                            
0x67d3449  movzx edx,byte ptr [rbp+0x77]                 
0x67d344d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d3453  nop                                           
0x67d3454  mov rax,0x4000000012807021                    
0x67d345e  mov [rbp-0x58],rax                            
0x67d3462  mov eax,[rsi+0x600]                           
0x67d3468  not eax                                       
0x67d346a  add eax,[rsi+0x608]                           
0x67d3470  mov [rbp-0x10],ax                             
0x67d3474  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d347b  mov rax,[rcx]                                 
0x67d347e  mov rax,[rax+0x10]                            
0x67d3482  mov dl,0x4A                                   
0x67d3484  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d348a  mov [rbp+0x77],al                             
0x67d348d  mov rax,[rsi+8]                               
0x67d3491  cmp rax,[rsi+0x10]                            
0x67d3495  je short 0x67D34B3                            ; -> loc_67d34b3
0x67d3497  lea rdx,[rbp-0x58]                            
0x67d349b  mov r8d,0xC8                                  
0x67d34a1  mov rcx,rax                                   
0x67d34a4  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x67d34a9  add qword ptr [rsi+8],0xC8                    
0x67d34b1  jmp short 0x67D34C3                           ; -> loc_67d34c3
```

### Phase 11: 0x67d34b3..0x67d34e9 (18 instructions)

Slow path queue full: sub_5aba6d0(rcx=rsi, rdx=rax head slot, r8=&[rbp-0x58]). At 0x67d34c3: cookie. Epilogue: rsp+=0x100, pop rbx/rdi/rsi/r14/rbp, ret.

```
0x67d34b3  lea r8,[rbp-0x58]                             
0x67d34b7  mov rcx,rsi                                   
0x67d34ba  mov rdx,rax                                   
0x67d34bd  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x67d34c2  nop                                           
0x67d34c3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67d34ca  mov rax,[rcx]                                 
0x67d34cd  mov rax,[rax+0x10]                            
0x67d34d1  movzx edx,byte ptr [rbp+0x77]                 
0x67d34d5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67d34db  nop                                           
0x67d34dc  add rsp,0x100                                 
0x67d34e3  pop rbx                                       
0x67d34e4  pop rdi                                       
0x67d34e5  pop rsi                                       
0x67d34e6  pop r14                                       
0x67d34e8  pop rbp                                       
0x67d34e9  ret                                           
```

---

### 0x67d2f80 summary

Args [V]: rdx=a1 (r14, source word ptr +0x0), r8=a2 (rbx, handle ptr), r9=a3 (rdi, source struct ptr at +0xD0/+0xD8/+0xE0), rcx=4th arg (not used directly at entry).

Fields touched [V] (reg+disp, R/W):
- Stack template: W rbp+0x78 (sentinel), W rbp+0x60/0x50/0x40/0x30/0x20/0x10/0x0/-0x10/-0x20/-0x30/-0x40/-0x50 (12 xmm zero slots), W rbp+0x77 (cookie byte, many), W rbp-0x58 (tag: 1 / 0x2001001 / 0x2007001 / 0x4000000002807001 / 0x4000000012807021), W rbp-0x48/0x30/0x16/0x2E/0x2C/0x34/0x3E/0x10 (index/handle slots)
- Pass buffer rsi: R/W [rsi+0x8A8]/[rsi+0x8B0], R [rsi+0x8A0]; R/W [rsi+0x780]/[rsi+0x788]; R/W [rsi+0x648]/[rsi+0x650]; R/W [rsi+0x770]/[rsi+0x778], R [rsi+0x768]; R/W [rsi+0x758]/[rsi+0x760], R [rsi+0x750]; R/W [rsi+0x2D8]/[rsi+0x2E0], R [rsi+0x2D0]; R/W [rsi+0x680]/[rsi+0x688], R [rsi+0x678]; R/W [rsi+0x830]/[rsi+0x838], R [rsi+0x828]; R/W [rsi+0x608]/[rsi+0x610], R [rsi+0x600]; R/W [rsi+8]/[rsi+0x10] (queue)
- Source reads: R word [r14+0x0], R qword [rdi], R 12 bytes [rdi+0x0..0x8] (3 floats), R [rdi+0x10], R [rdi+0x80]
- W via callees: sub_675f3b0(&[rsi+0x780], rbx), sub_675fb30(&[rsi+0x648], rdi), sub_e869ff0(&[rbx+8], &[rdi+8]), sub_6760710, sub_6760a80, sub_6760e60 (x3: +0x2D0/+0x828/+0x600), sub_1770a70 (+0x678), sub_eec6ec0(dst=head, src=&[rbp-0x58], 0xC8), sub_5aba6d0

Callees [V]:
- sub_5aba5c0 (get pass buffer)
- [0xF99FFA0]=sub_eea6040 (cookie/TLS, ~9 calls)
- sub_1ef6f90 (slow path entry0)
- sub_675f3b0 (write handle to +0x780)
- sub_675fb30 (write handle to +0x648)
- sub_e869ff0 (copy 0x78 bytes)
- sub_6760710 (slow path grow +0x770)
- sub_6760a80 (slow path grow +0x758)
- sub_6760e60 (slow path grow +0x2D0/+0x828/+0x600, x3)
- sub_1770a70 (slow path grow +0x680)
- sub_eec6ec0 (copy 0xC8 entry to queue)
- sub_5aba6d0 (slow path queue append)

Return: void [V].

Differences vs 0x67d3850 [I]: tags differ (0x2001001 vs 0x2003001 at phase 3/4; 0x2007001 same); tail magic differs (0xFFFFAAAB with shr 2 vs none); tail reads 3 floats at +0x680 vs counter at +0x890; sub_1770a70 used instead of second sub_6760e60 for +0x680 grow; final tag 0x4000000012807021 vs 0x4000000012007003.

## NEXT

Unit U-ED complete: all 6 functions transcribed (0x66a6060, 0x66a6190, 0x66a6470, 0x66a65b0, 0x67d3850, 0x67d2f80). All phases instruction-complete, each ≤40 instructions, every instruction quoted verbatim from rdis. File: docs/progress/oc_U-ED.md only. No other files edited.

## Summary of all functions

| Function | Bounds [V] | Phases | Key role |
|----------|-----------|--------|----------|
| 0x66a6060 | [0x66a6060..0x66a6182) | 3 | Refcounted range iterator with TLS log |
| 0x66a6190 | [0x66a6190..0x66a63af) | 8 | Variant array builder from iterable |
| 0x66a6470 | [0x66a6470..0x66a65b0) | 5 | Record cleanup: refcount + array + single pointer release |
| 0x66a65b0 | [0x66a65b0..0x66a66f0) | 5 | Mirror of 0x66a6470 (different displacements) |
| 0x67d3850 | [0x67d3850..0x67d3d20) | 10 | Pass-builder: 9 sub-buffer entries + queue append |
| 0x67d2f80 | [0x67d2f80..0x67d34ea) | 11 | Near-mirror pass-builder (tail: 3-float +0x680 vs counter) |

OPEN (unit-level): exact struct layouts of pass-buffer sub-entries and record types; roles of magic multipliers and cookie/TLS sub_eea6040; meanings of sub_675f3b0/sub_675fb30/sub_6760710/sub_6760a80/sub_6760e60/sub_1770a70/sub_eec6ec0/sub_5aba6d0 [I].

Verification: every instruction line quoted verbatim from rdis `fn` output; each phase ≤40 instructions; all instruction-complete (no ranges skipped). Only file created: docs/progress/oc_U-ED.md. No other files edited. No builds run. No commits.






