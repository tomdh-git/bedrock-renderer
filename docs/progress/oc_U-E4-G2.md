# U-E4-G2: Chunk builder at 0x670b6e0 — continuation of U-E4-G1

Unit: U-E4-G2
Function: sub_670b6e0 (chunk builder) — continuation
RVAs: 0x670c5a6 .. 0x670d6c6 (800 instructions from 0x670c5a6)
Source: `rdis dis 0x670c5a6 <n>` on Minecraft.Windows.exe 1.26.62.01
Sibling: docs/progress/oc_U-E4-F2.md (sub_67762e0, started 0x677736e)
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Unit complete — all 800 instructions transcribed (0x670c5a6..0x670d6c6, Phases 1-30). No further work on U-E4-G2. Beyond-unit resume point: 0x670d6cc (nop after final call [0xF99FFA0] at 0x670d6c6) — available for a follow-up unit.

---

## Phase 1 — Call 0x678E1D0 + copy [rbp+0x4C0]→[r14+0x78..0xAF] + call 0x67E23F0 + call 0x678E420 (0x670c5a6..0x670c644)

Resumes the call sequence from G1 Phase 41: `call 0x678E1D0`, then copies [rbp+0x4C0]+{0x68,0x58,0x80,0x90,0x9F} plus byte/u16 locals into [r14+0x78..0xAF] and [rbp+0x27C/0x280/0x2C0], then calls 0x67E23F0 and 0x678E420.

```
0x670c5a6  call 0x678E1D0                                ; -> sub_678e1d0
0x670c5ab  nop                                           
0x670c5ac  lea rcx,[rbp+0x4C0]                           
0x670c5b3  mov eax,[rcx+0x68]                            
0x670c5b6  mov [r14+0x78],eax                            
0x670c5ba  movups xmm0,[rcx+0x58]                        
0x670c5be  movups [r14+0x68],xmm0                        
0x670c5c3  movzx eax,byte ptr [rbp+0x52C]                
0x670c5ca  mov [rbp+0x27C],al                            
0x670c5d0  movups xmm0,[rbp+0x530]                       
0x670c5d7  movups [rbp+0x280],xmm0                       
0x670c5de  movups xmm0,[rcx+0x80]                        
0x670c5e5  movups xmm1,[rcx+0x90]                        
0x670c5ec  movups xmm2,[rcx+0x9F]                        
0x670c5f3  movups [r14+0xAF],xmm2                        
0x670c5fb  movups [r14+0xA0],xmm1                        
0x670c603  movups [r14+0x90],xmm0                        
0x670c60b  movzx eax,word ptr [rbp+0x570]                
0x670c612  mov [rbp+0x2C0],ax                            
0x670c619  mov rcx,r12                                   
0x670c61c  call 0x67E23F0                                ; -> sub_67e23f0
0x670c621  nop                                           
0x670c622  mov [rsp+0x20],rsi                            
0x670c627  mov rcx,r13                                   
0x670c62a  lea rdx,[rbp+0x210]                           
0x670c631  lea r8,[rbp+0x1B8]                            
0x670c638  lea r9,[rbp+0x130]                            
0x670c63f  call 0x678E420                                ; -> sub_678e420
0x670c644  nop                                           
```

Interpretation: `call 0x678E1D0` (continuation of G1 Phase 41's equal-path call sequence). rcx = &[rbp+0x4C0]. eax = [rcx+0x68] → [r14+0x78]. xmm0 = [rcx+0x58] → [r14+0x68]. al = byte [rbp+0x52C] → [rbp+0x27C]. xmm0 = [rbp+0x530] → [rbp+0x280]. xmm0 = [rcx+0x80], xmm1 = [rcx+0x90], xmm2 = [rcx+0x9F] → [r14+0xAF], [r14+0xA0], [r14+0x90]. ax = word [rbp+0x570] → [rbp+0x2C0]. rcx = r12. Call 0x67E23F0. [rsp+0x20] = rsi. rcx = r13. rdx = &[rbp+0x210], r8 = &[rbp+0x1B8], r9 = &[rbp+0x130]. Call 0x678E420.

Callees: 0x678E1D0 (sub_678e1d0), 0x67E23F0 (sub_67e23f0), 0x678E420 (sub_678e420).
Fields read: [rcx+0x68], [rcx+0x58], [rbp+0x52C], [rbp+0x530], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x570], r12, r13, rsi, [rbp+0x210], [rbp+0x1B8], [rbp+0x130]. Fields written: [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0xAF], [r14+0xA0], [r14+0x90], [rbp+0x2C0], [rsp+0x20].
Matches F2 Phase? No exact match to one F2 phase — combines an F2 Phase 5-like copy ([rcx+0x68..0x9F] → dest, different base/slots) with an F2 Phase 6-like call pair (0x67E23F0 + 0x678E420), but F2 Phase 6 used rcx=r13 for the first call and rdx=&[rbp+0x200]/r8=&[rbp+0x1A8]/r9=&[rbp+0x120]; here rcx=r12 and rdx=&[rbp+0x210]/r8=&[rbp+0x1B8]/r9=&[rbp+0x130].

---

## Phase 2 — Copy [r14+0x78..0xAF]→[rbp+0x6C8..0x720] + call 0x5ABA5C0 (0x670c645..0x670c6c6)

Copies [r14+0x78..0xAF] plus byte/u16 locals into [rbp+0x6C8..0x720], then builds a BuilderSpan+0x9D0 argument and calls 0x5ABA5C0.

```
0x670c645  mov eax,[r14+0x78]                            
0x670c649  lea rcx,[rbp+0x6C8]                           
0x670c650  mov [rcx+0x10],eax                            
0x670c653  movups xmm0,[r14+0x68]                        
0x670c658  movups [rcx],xmm0                             
0x670c65b  movzx eax,byte ptr [rbp+0x27C]                
0x670c662  mov [rbp+0x6DC],al                            
0x670c668  movups xmm0,[rbp+0x280]                       
0x670c66f  movups [rbp+0x6E0],xmm0                       
0x670c676  movups xmm0,[r14+0x90]                        
0x670c67e  movups xmm1,[r14+0xA0]                        
0x670c686  movups xmm2,[r14+0xAF]                        
0x670c68e  lea rax,[rbp+0x6F0]                           
0x670c695  movups [rax+0x1F],xmm2                        
0x670c699  movups [rax+0x10],xmm1                        
0x670c69d  movups [rax],xmm0                             
0x670c6a0  movzx eax,word ptr [rbp+0x2C0]                
0x670c6a7  mov [rbp+0x720],ax                            
0x670c6ae  mov rax,[rbp+0x838]                           
0x670c6b5  mov rcx,[rax+0x10]                            
0x670c6b9  mov eax,0x9D0                                 
0x670c6be  add rcx,rax                                   
0x670c6c1  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x670c6c6  nop                                           
```

Interpretation: eax = [r14+0x78] → [rcx+0x10] = [rbp+0x6D8]. xmm0 = [r14+0x68] → [rcx] = [rbp+0x6C8]. al = byte [rbp+0x27C] → [rbp+0x6DC]. xmm0 = [rbp+0x280] → [rbp+0x6E0]. xmm0 = [r14+0x90], xmm1 = [r14+0xA0], xmm2 = [r14+0xAF]. rax = &[rbp+0x6F0]. xmm2 → [rax+0x1F] = [rbp+0x70F], xmm1 → [rax+0x10] = [rbp+0x710], xmm0 → [rax] = [rbp+0x700]. ax = word [rbp+0x2C0] → [rbp+0x720]. rax = [rbp+0x838], rcx = [rax+0x10], rcx += 0x9D0. Call 0x5ABA5C0(rcx). Result → rax (consumed in next phase).

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0x90], [r14+0xA0], [r14+0xAF], [rbp+0x2C0], [rbp+0x838], [rax+0x10]. Fields written: [rbp+0x6D8], [rbp+0x6C8], [rbp+0x6DC], [rbp+0x6E0], [rbp+0x70F], [rbp+0x710], [rbp+0x700], [rbp+0x720].
Matches F2 Phase? Partial match — F2 Phase 7 is the same copy pattern ([rbx+0x78..0xAF] → [rbp+0x6B8..0x710], different dest base/slots) but F2 does not follow it with 0x5ABA5C0 in the same phase (F2 calls 0x5ABA5C0 in Phase 8/16/27).

---

## Phase 3 — Zero xmm regs [rbp+0x490..0x4A0] + TLS/cookie + items write + jmp 0x671011A (0x670c6c7..0x670c76c)

Zeroes xmm6 into [rbp+0x490..0x4A0], reads TLS/feature flag via [0xF99FFA0] with dl=0x4A, writes u16 [rbp+0x720] to the pass items buffer, jumps to 0x671011A on the grow path.

```
0x670c6c7  mov r15,rax                                   
0x670c6ca  movaps [rbp+0x490],xmm6                       
0x670c6d1  movaps [rbp+0x480],xmm6                       
0x670c6d8  movaps [rbp+0x470],xmm6                       
0x670c6df  movaps [rbp+0x460],xmm6                       
0x670c6e6  movaps [rbp+0x450],xmm6                       
0x670c6ed  movaps [rbp+0x440],xmm6                       
0x670c6f4  movaps [rbp+0x430],xmm6                       
0x670c6fb  movaps [rbp+0x420],xmm6                       
0x670c702  movaps [rbp+0x410],xmm6                       
0x670c709  movaps [rbp+0x400],xmm6                       
0x670c710  movaps [rbp+0x3F0],xmm6                       
0x670c717  movaps [rbp+0x3E0],xmm6                       
0x670c71e  mov qword ptr [rbp+0x4A0],0                   
0x670c729  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670c730  mov rax,[rcx]                                 
0x670c733  mov rax,[rax+0x10]                            
0x670c737  mov dl,0x4A                                   
0x670c739  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670c73f  nop                                           
0x670c740  mov [rbp+0x848],al                            
0x670c746  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x670c74d  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x670c754  je 0x6710106                                  ; -> sub_6710106
0x670c75a  movzx eax,word ptr [rbp+0x720]                
0x670c761  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x670c764  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x670c76c  jmp 0x671011A                                 ; -> sub_671011a
```

Interpretation: r15 = rax (pass object from 0x5ABA5C0). Zero xmm6 into [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], [rbp+0x4A0]=0. TLS read: rcx = [0x1233E1B0], rax = [rcx], rax = [rax+0x10], dl = 0x4A, call via [0xF99FFA0], al → [rbp+0x848] (feature flag). rdx = [r15+0x8A8] (items write cursor), cmp [r15+0x8B0] (items end). If equal → jump to 0x6710106 (grow). Otherwise eax = word [rbp+0x720], store ax at [rdx] (write u16 to items buffer), [r15+0x8A8] += 2, jump to 0x671011A.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: rax (pass obj), xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8B0], [rbp+0x720]. Fields written: [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], [rbp+0x4A0], [rbp+0x848], [rdx] (items buffer), [r15+0x8A8].
Matches F2 Phase? No exact match — matches G1 Phase 37's pattern (zero xmm block + TLS + items write). F2 Phase 17 has the TLS + items write but without the leading zero-xmm block, and writes [rbp+0x738] vs here [rbp+0x720], jump targets differ (0x671011A vs 0x677C3AE).

---

## Phase 4 — [rbx+0x50] ~0x3 check + calls 0x67E2190 + 0x678F640 (0x670c771..0x670c7c0)

Loads [rbx+0x50], bitwise-nots it, tests low byte against 3; if nonzero jumps to loc_670cace. Otherwise checks [rbp+0x118]==1, calls 0x67E2190 then 0x678F640.

```
0x670c771  mov eax,[rbx+0x50]                            
0x670c774  mov ecx,eax                                   
0x670c776  not ecx                                       
0x670c778  test cl,3                                     
0x670c77b  jne 0x670CACE                                 ; -> loc_670cace
0x670c781  cmp qword ptr [rbp+0x118],1                   
0x670c789  jne 0x670FC3E                                 ; -> sub_670fc3e
0x670c78f  lea rcx,[rbp+0x2D0]                           
0x670c796  lea rdx,[rbp+0x120]                           
0x670c79d  call 0x67E2190                                ; -> sub_67e2190
0x670c7a2  nop                                           
0x670c7a3  mov rcx,r13                                   
0x670c7a6  lea rdx,[rbp+0x200]                           
0x670c7ad  lea r8,[rbp+0x1A8]                            
0x670c7b4  lea r9,[rbp+0x120]                            
0x670c7bb  call 0x678F640                                ; -> sub_678f640
0x670c7c0  nop                                           
```

Interpretation: eax = [rbx+0x50], ecx = eax, ecx = ~ecx, test cl,3. If cl&3 != 0 → jump to loc_670cace (Phase 11). Fall-through: cmp qword [rbp+0x118], 1; if not equal → jump to 0x670FC3E. Otherwise rcx = &[rbp+0x2D0], rdx = &[rbp+0x120]. Call 0x67E2190. Then rcx = r13 (&[rbp+0x580]), rdx = &[rbp+0x200], r8 = &[rbp+0x1A8], r9 = &[rbp+0x120]. Call 0x678F640.

Callees: 0x67E2190 (sub_67e2190), 0x678F640 (sub_678f640).
Fields read: [rbx+0x50], [rbp+0x118], [rbp+0x2D0], [rbp+0x120], r13, [rbp+0x200], [rbp+0x1A8]. Fields written: none.
Matches F2 Phase? No exact match — F2 Phase 9 has a similar conditional-call structure (test al,2/1 + cmp [rbp+0x836] + calls 0x678CF10/0x678F640) but different tests, condition ([rbx+0x50]~0 & 3 here), and first callee (0x67E2190 vs 0x678CF10).

---

## Phase 5 — Copy [r14+0x68..0x9F]→[rbp+0x6C0..0x718] (0x670c7c1..0x670c82d)

Copies [r14+0x68..0x9F] plus byte/u16 locals into [rbp+0x6C0..0x718]. (The next instruction `0x670c834 mov rcx,[rbp+0x778]` belongs to Phase 6.)

```
0x670c7c1  mov eax,[r14+0x68]                            
0x670c7c5  lea rcx,[rbp+0x6C0]                           
0x670c7cc  mov [rcx+0x10],eax                            
0x670c7cf  movups xmm0,[r14+0x58]                        
0x670c7d4  movups [rcx],xmm0                             
0x670c7d7  movzx eax,byte ptr [rbp+0x26C]                
0x670c7de  mov [rbp+0x6D4],al                            
0x670c7e4  movups xmm0,[rbp+0x270]                       
0x670c7eb  movups [rbp+0x6D8],xmm0                       
0x670c7f2  movups xmm0,[r14+0x80]                        
0x670c7fa  movups xmm1,[r14+0x90]                        
0x670c802  movups xmm2,[r14+0x9F]                        
0x670c80a  lea rax,[rbp+0x584]                           
0x670c811  movups [rax+0x183],xmm2                       
0x670c818  movups [rax+0x174],xmm1                       
0x670c81f  movups [rax+0x164],xmm0                       
0x670c826  movzx eax,word ptr [rbp+0x2B0]                
0x670c82d  mov [rbp+0x718],ax                            
```

Interpretation: eax = [r14+0x68] → [rcx+0x10] where rcx=&[rbp+0x6C0] → [rbp+0x6D0]. xmm0 = [r14+0x58] → [rcx] = [rbp+0x6C0]. al = byte [rbp+0x26C] → [rbp+0x6D4]. xmm0 = [rbp+0x270] → [rbp+0x6D8]. xmm0 = [r14+0x80], xmm1 = [r14+0x90], xmm2 = [r14+0x9F]. rax = &[rbp+0x584]. xmm2 → [rax+0x183] = [rbp+0x707], xmm1 → [rax+0x174] = [rbp+0x6F8], xmm0 → [rax+0x164] = [rbp+0x6E8]. ax = word [rbp+0x2B0] → [rbp+0x718]. (Next instruction `0x670c834 mov rcx,[rbp+0x778]` starts Phase 6.)

Callees: none.
Fields read: [r14+0x68], [r14+0x58], [rbp+0x26C], [rbp+0x270], [r14+0x80], [r14+0x90], [r14+0x9F], [rbp+0x2B0]. Fields written: [rbp+0x6D0], [rbp+0x6C0], [rbp+0x6D4], [rbp+0x6D8], [rbp+0x707], [rbp+0x6F8], [rbp+0x6E8], [rbp+0x718].
Matches F2 Phase? Partial match — F2 Phase 1 is the same copy pattern ([rbx+0x68..0x9F] → [rbp+0x6B0..], different dest base/slots) and F2 Phase 15 copies [rcx+0x10..0x9F]; here [r14] is the source.

---

## Phase 6 — Range check [rbp+0x778]+0x480/0x488 + call 0x67E2540 + jmp 0x67100F2 (0x670c834..0x670c8b6)

Computes [rbp+0x778]+0x488 minus +0x480, range-checks against 0xFFFFFFD0, divides by 15 via magic multiply, stores results, calls 0x67E2540, jumps to 0x67100F2.

```
0x670c834  mov rcx,[rbp+0x778]                           
0x670c83b  mov rax,[rcx+0x480]                           
0x670c842  mov rdx,[rcx+0x488]                           
0x670c849  mov rcx,rdx                                   
0x670c84c  sub rcx,rax                                   
0x670c84f  cmp rcx,0xFFFFFFFFFFFFFFD0                    
0x670c853  je 0x6713B0F                                  ; -> sub_6713b0f
0x670c859  test rax,rax                                  
0x670c85c  setne r8b                                     
0x670c860  test rdx,rdx                                  
0x670c863  sete dl                                       
0x670c866  or dl,r8b                                     
0x670c869  je 0x6713B0F                                  ; -> sub_6713b0f
0x670c86f  sar rcx,4                                     
0x670c873  mov rdx,0xAAAAAAAAAAAAAAAB                    
0x670c87d  imul rcx,rdx                                  
0x670c881  mov [rbp+0xE0],rcx                            
0x670c888  mov [rbp+0xE8],rax                            
0x670c88f  mov [rsp+0x20],r13                            
0x670c894  mov rcx,[rbp+0x838]                           
0x670c89b  lea rdx,[rbp+0xE0]                            
0x670c8a2  mov r8,[rbp+0x788]                            
0x670c8a9  lea r9,[rbp+0x2F0]                            
0x670c8b0  call 0x67E2540                                ; -> sub_67e2540
0x670c8b5  nop                                           
0x670c8b6  jmp 0x67100F2                                 ; -> sub_67100f2
```

Interpretation: rcx = [rbp+0x778]. rax = [rcx+0x480], rdx = [rcx+0x488]. rcx = rdx, rcx -= rax (difference). If difference == 0xFFFFFFD0 (-48) → jump to 0x6713B0F. test rax,rax → setne r8b (rax!=0). test rdx,rdx → sete dl (rdx==0). or dl,r8b. If 0 → jump to 0x6713B0F. sar rcx,4 (divide by 16). imul rcx, 0xAAAAAAAAAAAAAAAB (magic multiply for divide by 15). [rbp+0xE0] = rcx. [rbp+0xE8] = rax. [rsp+0x20] = r13. rcx = [rbp+0x838]. rdx = &[rbp+0xE0]. r8 = [rbp+0x788]. r9 = &[rbp+0x2F0]. Call 0x67E2540. Jump to 0x67100F2.

Callees: 0x67E2540 (sub_67e2540).
Fields read: [rbp+0x778], [rcx+0x480], [rcx+0x488], [rbp+0x838], [rbp+0x788], [rbp+0xE0], [rbp+0x2F0]. Fields written: [rbp+0xE0], [rbp+0xE8], [rsp+0x20].
Matches F2 Phase? Partial match — F2 Phase 11 has the same range-check + magic-divide structure and calls 0x6769EE0; here the callee is 0x67E2540 and F2's extra `cmp rax,r8` / `cmp [rax],0` checks are absent. F2 passes rcx=&[rbp+0x800]/r9=&[rbp+0x2E0]; here rcx=[rbp+0x838]/r9=&[rbp+0x2F0].

---

## Phase 7 — movlps/movss store + calls 0x67E2190 + 0x678E1D0 (0x670c8bb..0x670c908)

Target of the `jne 0x670C8BB` from G1 Phase 41: stores xmm15/xmm12 to [rbp+0x310/0x318], calls 0x67E2190 then 0x678E1D0.

```
0x670c8bb  movlps [rbp+0x310],xmm15                      
0x670c8c3  movss [rbp+0x318],xmm12                       
0x670c8cc  lea rcx,[rbp+0x2D0]                           
0x670c8d3  mov rdx,r12                                   
0x670c8d6  call 0x67E2190                                ; -> sub_67e2190
0x670c8db  nop                                           
0x670c8dc  lea rax,[rbp+0x310]                           
0x670c8e3  mov [rsp+0x20],rax                            
0x670c8e8  lea rsi,[rbp+0x120]                           
0x670c8ef  mov rcx,rsi                                   
0x670c8f2  lea rdx,[rbp+0x4C0]                           
0x670c8f9  lea r8,[rbp+0x468]                            
0x670c900  mov r9,r12                                    
0x670c903  call 0x678E1D0                                ; -> sub_678e1d0
0x670c908  nop                                           
```

Interpretation: [rbp+0x310] = low64(xmm15) (movlps), [rbp+0x318] = low32(xmm12) (movss). rcx = &[rbp+0x2D0], rdx = r12. Call 0x67E2190. [rsp+0x20] = &[rbp+0x310]. rsi = &[rbp+0x120]. Call 0x678E1D0(rcx=rsi, rdx=&[rbp+0x4C0], r8=&[rbp+0x468], r9=r12).

Callees: 0x67E2190 (sub_67e2190), 0x678E1D0 (sub_678e1d0).
Fields read: xmm15, xmm12, [rbp+0x2D0], r12, [rbp+0x120], [rbp+0x4C0], [rbp+0x468]. Fields written: [rbp+0x310], [rbp+0x318], [rsp+0x20].
Matches F2 Phase? Partial match — F2 Phase 4 is the same shape (movlps/movss store + two calls) but F2's callees are 0x678CF10 then 0x678E1D0 with rcx=&[rbp+0x2C0]/rdx=r13; here 0x67E2190 then 0x678E1D0 with rcx=&[rbp+0x2D0]/rdx=r12.

---

## Phase 8 — Copy [rbp+0x4C0]→[r14+0x78..0xAF] + call 0x67E23F0 + call 0x678E420 (0x670c909..0x670c9a1)

Copies [rbp+0x4C0]+{0x68,0x58,0x80,0x90,0x9F} plus byte/u16 locals into [r14+0x78..0xAF] and [rbp+0x27C/0x280/0x2C0], then calls 0x67E23F0 and 0x678E420 (same shape as Phase 1 but source is [rbp+0x4C0] via rcx directly).

```
0x670c909  lea rcx,[rbp+0x4C0]                           
0x670c910  mov eax,[rcx+0x68]                            
0x670c913  mov [r14+0x78],eax                            
0x670c917  movups xmm0,[rcx+0x58]                        
0x670c91b  movups [r14+0x68],xmm0                        
0x670c920  movzx eax,byte ptr [rbp+0x52C]                
0x670c927  mov [rbp+0x27C],al                            
0x670c92d  movups xmm0,[rbp+0x530]                       
0x670c934  movups [rbp+0x280],xmm0                       
0x670c93b  movups xmm0,[rcx+0x80]                        
0x670c942  movups xmm1,[rcx+0x90]                        
0x670c949  movups xmm2,[rcx+0x9F]                        
0x670c950  movups [r14+0xAF],xmm2                        
0x670c958  movups [r14+0xA0],xmm1                        
0x670c960  movups [r14+0x90],xmm0                        
0x670c968  movzx eax,word ptr [rbp+0x570]                
0x670c96f  mov [rbp+0x2C0],ax                            
0x670c976  mov rcx,r12                                   
0x670c979  call 0x67E23F0                                ; -> sub_67e23f0
0x670c97e  nop                                           
0x670c97f  mov [rsp+0x20],rsi                            
0x670c984  mov rcx,r13                                   
0x670c987  lea rdx,[rbp+0x210]                           
0x670c98e  lea r8,[rbp+0x1B8]                            
0x670c995  lea r9,[rbp+0x130]                            
0x670c99c  call 0x678E420                                ; -> sub_678e420
0x670c9a1  nop                                           
```

Interpretation: rcx = &[rbp+0x4C0]. eax = [rcx+0x68] → [r14+0x78]. xmm0 = [rcx+0x58] → [r14+0x68]. al = byte [rbp+0x52C] → [rbp+0x27C]. xmm0 = [rbp+0x530] → [rbp+0x280]. xmm0 = [rcx+0x80], xmm1 = [rcx+0x90], xmm2 = [rcx+0x9F] → [r14+0xAF], [r14+0xA0], [r14+0x90]. ax = word [rbp+0x570] → [rbp+0x2C0]. rcx = r12. Call 0x67E23F0. [rsp+0x20] = rsi. rcx = r13. rdx = &[rbp+0x210], r8 = &[rbp+0x1B8], r9 = &[rbp+0x130]. Call 0x678E420.

Callees: 0x67E23F0 (sub_67e23f0), 0x678E420 (sub_678e420).
Fields read: [rcx+0x68], [rcx+0x58], [rbp+0x52C], [rbp+0x530], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x570], r12, r13, rsi, [rbp+0x210], [rbp+0x1B8], [rbp+0x130]. Fields written: [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0xAF], [r14+0xA0], [r14+0x90], [rbp+0x2C0], [rsp+0x20].
Matches F2 Phase? Same combined pattern as Phase 1 (F2 Phase 5-like copy + F2 Phase 6-like calls) — no exact single-F2-phase match; argument slots identical to Phase 1 here (rcx=r12, rdx=&[rbp+0x210]...).

---

## Phase 9 — Copy [r14+0x78..0xAF]→[rbp+0x6C8..0x720] + call 0x5ABA5C0 (0x670c9a2..0x670ca23)

Same shape as Phase 2: copies [r14+0x78..0xAF] plus byte/u16 locals into [rbp+0x6C8..0x720], then calls 0x5ABA5C0.

```
0x670c9a2  mov eax,[r14+0x78]                            
0x670c9a6  lea rcx,[rbp+0x6C8]                           
0x670c9ad  mov [rcx+0x10],eax                            
0x670c9b0  movups xmm0,[r14+0x68]                        
0x670c9b5  movups [rcx],xmm0                             
0x670c9b8  movzx eax,byte ptr [rbp+0x27C]                
0x670c9bf  mov [rbp+0x6DC],al                            
0x670c9c5  movups xmm0,[rbp+0x280]                       
0x670c9cc  movups [rbp+0x6E0],xmm0                       
0x670c9d3  movups xmm0,[r14+0x90]                        
0x670c9db  movups xmm1,[r14+0xA0]                        
0x670c9e3  movups xmm2,[r14+0xAF]                        
0x670c9eb  lea rax,[rbp+0x6F0]                           
0x670c9f2  movups [rax+0x1F],xmm2                        
0x670c9f6  movups [rax+0x10],xmm1                        
0x670c9fa  movups [rax],xmm0                             
0x670c9fd  movzx eax,word ptr [rbp+0x2C0]                
0x670ca04  mov [rbp+0x720],ax                            
0x670ca0b  mov rax,[rbp+0x838]                           
0x670ca12  mov rcx,[rax+0x10]                            
0x670ca16  mov eax,0x9D0                                 
0x670ca1b  add rcx,rax                                   
0x670ca1e  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x670ca23  nop                                           
```

Interpretation: Identical structure to Phase 2: eax=[r14+0x78]→[rbp+0x6D8], xmm0=[r14+0x68]→[rbp+0x6C8], al=byte[rbp+0x27C]→[rbp+0x6DC], xmm0=[rbp+0x280]→[rbp+0x6E0], xmm0/1/2=[r14+0x90/0xA0/0xAF]→[rbp+0x700/0x710/0x70F], ax=word[rbp+0x2C0]→[rbp+0x720], rax=[rbp+0x838], rcx=[rax+0x10]+0x9D0, call 0x5ABA5C0. Result → rax (consumed in next phase).

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0x90], [r14+0xA0], [r14+0xAF], [rbp+0x2C0], [rbp+0x838], [rax+0x10]. Fields written: [rbp+0x6D8], [rbp+0x6C8], [rbp+0x6DC], [rbp+0x6E0], [rbp+0x70F], [rbp+0x710], [rbp+0x700], [rbp+0x720].
Matches F2 Phase? Same as Phase 2 — partial match to F2 Phase 7's copy pattern, F2 does not pair it with 0x5ABA5C0 in one phase.

---

## Phase 10 — mov r15,rax + zero xmm regs [rbp+0x490..0x4A0] + TLS/cookie + items write + jmp 0x6710210 (0x670ca24..0x670cac9)

Same shape as Phase 3 but jump target 0x6710210 / grow target 0x67101FC.

```
0x670ca24  mov r15,rax                                   
0x670ca27  movaps [rbp+0x490],xmm6                       
0x670ca2e  movaps [rbp+0x480],xmm6                       
0x670ca35  movaps [rbp+0x470],xmm6                       
0x670ca3c  movaps [rbp+0x460],xmm6                       
0x670ca43  movaps [rbp+0x450],xmm6                       
0x670ca4a  movaps [rbp+0x440],xmm6                       
0x670ca51  movaps [rbp+0x420],xmm6                       
0x670ca5f  movaps [rbp+0x410],xmm6                       
0x670ca66  movaps [rbp+0x400],xmm6                       
0x670ca6d  movaps [rbp+0x3F0],xmm6                       
0x670ca74  movaps [rbp+0x3E0],xmm6                       
0x670ca7b  mov qword ptr [rbp+0x4A0],0                   
0x670ca86  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ca8d  mov rax,[rcx]                                 
0x670ca90  mov rax,[rax+0x10]                            
0x670ca94  mov dl,0x4A                                   
0x670ca96  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ca9c  nop                                           
0x670ca9d  mov [rbp+0x848],al                            
0x670caa3  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x670caaa  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x670cab1  je 0x67101FC                                  ; -> sub_67101fc
0x670cab7  movzx eax,word ptr [rbp+0x720]                
0x670cabe  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x670cac1  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x670cac9  jmp 0x6710210                                 ; -> sub_6710210
```

Interpretation: r15 = rax (pass object). Zero xmm6 into [rbp+0x490..0x4A0] (same slots as Phase 3). TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x848]. rdx=[r15+0x8A8] vs [r15+0x8B0]. If equal → jump to 0x67101FC (grow). Otherwise eax=word [rbp+0x720], store ax at [rdx], [r15+0x8A8]+=2, jump to 0x6710210.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: rax, xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8B0], [rbp+0x720]. Fields written: [rbp+0x490..0x4A0] (zero block), [rbp+0x848], [rdx] (items buffer), [r15+0x8A8].
Matches F2 Phase? Same as Phase 3 — matches G1 Phase 37 pattern; F2 Phase 17 has TLS+items write without leading zero block, different slots/jump targets.

---

## Phase 11 — test al,2/1 + cmp [rbp+0x118],1 + calls 0x67E2190 + 0x678F640 (0x670cace..0x670cb19)

Target of `jne 0x670CACE` from Phase 4: tests al bits 2 and 1, checks [rbp+0x118]==1, calls 0x67E2190 then 0x678F640.

```
0x670cace  test al,2                                     
0x670cad0  jne 0x670FFCF                                 ; -> sub_670ffcf
0x670cad6  test al,1                                     
0x670cad8  je 0x6710C2C                                  ; -> sub_6710c2c
0x670cade  cmp qword ptr [rbp+0x118],1                   
0x670cae6  jne 0x6710C3E                                 ; -> sub_6710c3e
0x670caec  lea rcx,[rbp+0x2D0]                           
0x670caf3  mov rdx,r12                                   
0x670caf6  call 0x67E2190                                ; -> sub_67e2190
0x670cafb  nop                                           
0x670cafc  lea rcx,[rbp+0x120]                           
0x670cb03  lea rdx,[rbp+0x4C0]                           
0x670cb0a  lea r8,[rbp+0x468]                            
0x670cb11  mov r9,r12                                    
0x670cb14  call 0x678F640                                ; -> sub_678f640
0x670cb19  nop                                           
```

Interpretation: test al,2; if nonzero → jump to 0x670FFCF. test al,1; if zero → jump to 0x6710C2C. cmp qword [rbp+0x118], 1; if not equal → jump to 0x6710C3E. Otherwise: rcx = &[rbp+0x2D0], rdx = r12. Call 0x67E2190. Then rcx = &[rbp+0x120], rdx = &[rbp+0x4C0], r8 = &[rbp+0x468], r9 = r12. Call 0x678F640.

Callees: 0x67E2190 (sub_67e2190), 0x678F640 (sub_678f640).
Fields read: al, [rbp+0x118], [rbp+0x2D0], r12, [rbp+0x120], [rbp+0x4C0], [rbp+0x468]. Fields written: none.
Matches F2 Phase? No exact match — F2 Phase 9 is the closest (test al,2/1 + conditional calls 0x678CF10/0x678F640) but different conditions/callee order/slots here (0x67E2190 first, rdx=r12 vs r13).

---

## Phase 12 — Copy [rbp+0x4C0]→[rbp+0x260..] + save byte/u16 locals (0x670cb1a..0x670cb84)

Copies [rbp+0x4C0]+{0x68,0x58,0x80,0x90,0x9F} plus byte/u16 locals into [rbp+0x260..] and [r14+0x88/0x98/0xA7] and [rbp+0x274/0x278/0x2B8].

```
0x670cb1a  lea rcx,[rbp+0x4C0]                           
0x670cb21  mov eax,[rcx+0x68]                            
0x670cb24  lea rdx,[rbp+0x260]                           
0x670cb2b  mov [rdx+0x10],eax                            
0x670cb2e  movups xmm0,[rcx+0x58]                        
0x670cb32  movups [rdx],xmm0                             
0x670cb35  movzx eax,byte ptr [rbp+0x52C]                
0x670cb3c  mov [rbp+0x274],al                            
0x670cb42  movups xmm0,[rbp+0x530]                       
0x670cb49  movups [rbp+0x278],xmm0                       
0x670cb50  movups xmm0,[rcx+0x80]                        
0x670cb57  movups xmm1,[rcx+0x90]                        
0x670cb5e  movups xmm2,[rcx+0x9F]                        
0x670cb65  movups [r14+0xA7],xmm2                        
0x670cb6d  movups [r14+0x98],xmm1                        
0x670cb75  movups [r14+0x88],xmm0                        
0x670cb7d  movzx eax,word ptr [rbp+0x570]                
0x670cb84  mov [rbp+0x2B8],ax                            
```

Interpretation: rcx = &[rbp+0x4C0]. eax = [rcx+0x68] → [rdx+0x10] where rdx=&[rbp+0x260] → [rbp+0x270]. xmm0 = [rcx+0x58] → [rdx] = [rbp+0x260]. al = byte [rbp+0x52C] → [rbp+0x274]. xmm0 = [rbp+0x530] → [rbp+0x278]. xmm0 = [rcx+0x80], xmm1 = [rcx+0x90], xmm2 = [rcx+0x9F] → [r14+0xA7], [r14+0x98], [r14+0x88]. ax = word [rbp+0x570] → [rbp+0x2B8].

Callees: none.
Fields read: [rcx+0x68], [rcx+0x58], [rbp+0x52C], [rbp+0x530], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x570]. Fields written: [rbp+0x270], [rbp+0x260], [rbp+0x274], [rbp+0x278], [r14+0xA7], [r14+0x98], [r14+0x88], [rbp+0x2B8].
Matches F2 Phase? Partial match — F2 Phase 10 is the same copy pattern ([rcx+0x68..0x9F] → [rbp+0x250..], different dest slots) and F2 Phase 15 copies to [rbp+0x6E0..]; here destination is [rbp+0x260..] plus [r14+0x88/0x98/0xA7].

---

## Phase 13 — Range check [rbp+0x778]+0x480/0x488 + call 0x6769EE0 + store [rbp+0x810/0x818] (0x670cb8b..0x670cc1f)

Computes [rbp+0x778]+0x488 minus +0x480, range-checks against 0xFFFFFFD0 with extra `cmp rax,r8` / `[rax]==0` checks, divides by 15 via magic multiply, stores float 0x41800000 at [rsp+0x20], calls 0x6769EE0, then loads [rbp+0x810/0x818] into r15 and [rbp+0x848].

```
0x670cb8b  mov rax,[rbp+0x778]                           
0x670cb92  mov r8,[rax+0x480]                            
0x670cb99  mov rax,[rax+0x488]                           
0x670cba0  mov rdx,rax                                   
0x670cba3  sub rdx,r8                                    
0x670cba6  cmp rdx,0xFFFFFFFFFFFFFFD0                    
0x670cbaa  je 0x6713B0F                                  ; -> sub_6713b0f
0x670cbb0  test r8,r8                                    
0x670cbb3  setne cl                                      
0x670cbb6  test rax,rax                                  
0x670cbb9  sete r9b                                      
0x670cbbd  or r9b,cl                                     
0x670cbc0  je 0x6713B0F                                  ; -> sub_6713b0f
0x670cbc6  cmp rax,r8                                    
0x670cbc9  je 0x6712B69                                  ; -> sub_6712b69
0x670cbcf  mov rax,[rbp+0x788]                           
0x670cbd6  cmp qword ptr [rax],0                         
0x670cbda  je 0x6712B69                                  ; -> sub_6712b69
0x670cbe0  sar rdx,4                                     
0x670cbe4  mov rax,0xAAAAAAAAAAAAAAAB                    
0x670cbee  imul rdx,rax                                  
0x670cbf2  mov dword ptr [rsp+0x20],0x41800000           
0x670cbfa  lea rcx,[rbp+0x810]                           
0x670cc01  lea r9,[rbp+0x2F0]                            
0x670cc08  call 0x6769EE0                                ; -> sub_6769ee0
0x670cc0d  nop                                           
0x670cc0e  mov rax,[rbp+0x810]                           
0x670cc15  mov rcx,[rbp+0x818]                           
0x670cc1c  mov r15,rax                                   
0x670cc1f  mov [rbp+0x848],rax                           
```

Interpretation: rax = [rbp+0x778]. r8 = [rax+0x480], rax = [rax+0x488]. rdx = rax, rdx -= r8 (difference). If difference == 0xFFFFFFD0 → jump to 0x6713B0F. test r8,r8 → setne cl. test rax,rax → sete r9b. or r9b,cl. If 0 → jump to 0x6713B0F. cmp rax,r8; if equal → jump to 0x6712B69. rax = [rbp+0x788]; if [rax] == 0 → jump to 0x6712B69. sar rdx,4 (divide by 16). imul rdx, 0xAAAAAAAAAAAAAAAB (magic multiply for divide by 15). [rsp+0x20] = 0x41800000 (float 31.0). rcx = &[rbp+0x810], r9 = &[rbp+0x2F0]. Call 0x6769EE0. Then rax = [rbp+0x810], rcx = [rbp+0x818], r15 = rax, [rbp+0x848] = rax. (Continues at 0x670cc26: `mov [rbp+0x578],rcx`.)

Callees: 0x6769EE0 (sub_6769ee0).
Fields read: [rbp+0x778], [rax+0x480], [rax+0x488], [rbp+0x788], [rax], [rbp+0x810], [rbp+0x818]. Fields written: [rsp+0x20], r15, [rbp+0x848].
Matches F2 Phase? Partial match — F2 Phase 11 has the same range-check structure and the same callee 0x6769EE0, but F2's version lacks the `cmp rax,r8` / `cmp [rax],0` checks (those appear in F2 Phase 11 actually — re-reading F2 Phase 11: it HAS `cmp rax,r8 je 0x677D069` and `mov rax,[rbp+0x778]; cmp qword ptr [rax],0 je 0x677D069`). So F2 Phase 11 is the closer structural match here: same checks, same callee 0x6769EE0, but F2 passes rcx=&[rbp+0x800]/r9=&[rbp+0x2E0] and stores [rsp+0x20]=0x41800000 before the call; here rcx=&[rbp+0x810]/r9=&[rbp+0x2F0] with extra trailing stores to r15/[rbp+0x848].

---

---

## Phase 14 — mov [rbp+0x578],rcx + range check + shared_ptr setup for call [0xF99FFA0] (0x670cc26..0x670ccbf)

Stores rcx at [rbp+0x578], compares rax vs rcx (je 0x6712AD6 on equal), loads [rbp+0x788]→rax, dereferences twice + [rax+0x48], sets rdx=&[rbp+0x310], calls via [0xF99FFA0] with dl (feature-flag arg) later. Then r15=[rbp+0x810], rsi=[rbp+0x818], computes rax=rsi-r15, range-checks against 0xFFFFFFE0 (-32) with the three-way test/setne/sete/or pattern (je 0x6713B0F on failure), sets up [rbp+0x7D0]=[rbp+0x7E0], [rbp+0x7D8]=0x100000000, and branches to loc_670ccdc if rsi==r15.

```
0x670cc26  mov [rbp+0x578],rcx                           
0x670cc2d  cmp rax,rcx                                   
0x670cc30  je 0x6712AD6                                  ; -> sub_6712ad6
0x670cc36  mov rax,[rbp+0x788]                           
0x670cc3d  mov rcx,[rax]                                 
0x670cc40  mov rax,[rcx]                                 
0x670cc43  mov rax,[rax+0x48]                            
0x670cc47  lea rdx,[rbp+0x310]                           
0x670cc4e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670cc54  nop                                           
0x670cc55  mov r15,[rbp+0x810]                           
0x670cc5c  mov rsi,[rbp+0x818]                           
0x670cc63  mov rax,rsi                                   
0x670cc66  sub rax,r15                                   
0x670cc69  cmp rax,0xFFFFFFFFFFFFFFE0                    
0x670cc6d  je 0x6713B0F                                  ; -> sub_6713b0f
0x670cc73  test r15,r15                                  
0x670cc76  setne al                                      
0x670cc79  test rsi,rsi                                  
0x670cc7c  sete cl                                       
0x670cc7f  or cl,al                                      
0x670cc81  je 0x6713B0F                                  ; -> sub_6713b0f
0x670cc87  test r15,r15                                  
0x670cc8a  setne al                                      
0x670cc8d  cmp rsi,r15                                   
0x670cc90  sete cl                                       
0x670cc93  or cl,al                                      
0x670cc95  je 0x6713B0F                                  ; -> sub_6713b0f
0x670cc9b  lea rax,[rbp+0x7E0]                           
0x670cca2  mov [rbp+0x7D0],rax                           
0x670cca9  mov rax,0x100000000                           
0x670ccb3  mov [rbp+0x7D8],rax                           
0x670ccba  cmp rsi,r15                                   
0x670ccbd  je short 0x670CCDC                            ; -> loc_670ccdc
0x670ccbf  nop                                           
```

Interpretation: [rbp+0x578]=rcx. if (rax==rcx) goto 0x6712AD6. rax=[rbp+0x788]; rcx=[rax]; rax=[rcx]; rax=[rax+0x48]; rdx=&[rbp+0x310]; call via [0xF99FFA0] (sub_eea6040). r15=[rbp+0x810]; rsi=[rbp+0x818]; rax=rsi-r15; if (rax==-32) goto 0x6713B0F; al=(r15!=0); cl=(rsi==0); cl|=al; if (!cl) goto 0x6713B0F; al=(r15!=0); cl=(rsi==r15); cl|=al; if (!cl) goto 0x6713B0F. [rbp+0x7D0]=[rbp+0x7E0]; [rbp+0x7D8]=0x100000000; if (rsi==r15) goto loc_670ccdc.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [rbp+0x578], rax, [rbp+0x788], [rax], [rcx], [rax+0x48], rdx, [rbp+0x810], [rbp+0x818], rsi, r15, [rbp+0x7E0]. Fields written: [rbp+0x578], [rbp+0x7D0], [rbp+0x7D8].
Matches F2 Phase? No same-numbered counterpart (F2 Phase 14 is the loop-region setup below). This phase's shared_ptr/feature-flag setup is conceptually similar to F2's refcount setup but the instruction sequence differs.

---

## Phase 15 — loc_670ccc0 refcount loop + loc_670ccdc setup: call 0x676A670, call 0x6764990, call 0x6792980 (0x670ccc0..0x670cd34)

Loop: while (r15 != rsi) { call 0x676A670(rcx=&[rbp+0x7D0], rdx=r13, r8=r15); r15 += 0x20; }. Fall-through loc_670ccdc: [rbp+0x790]=[rbp+0x7E0], [rbp+0x798]=0x100000000, rsi=&[rbp+0x790], call 0x6764990(rcx=rsi, rdx=&[rbp+0x7D0]), [rsp+0x20]=rsi, then call 0x6792980(rcx=r13, rdx=&[rbp+0x208], r8=&[rbp+0x1B0], r9=&[rbp+0x128]).

```
loc_670ccc0:  ; from 670ccda
0x670ccc0  lea rcx,[rbp+0x7D0]                           
0x670ccc7  mov rdx,r13                                   
0x670ccca  mov r8,r15                                    
0x670cccd  call 0x676A670                                ; -> sub_676a670
0x670ccd2  nop                                           
0x670ccd3  add r15,0x20                                  
0x670ccd7  cmp r15,rsi                                   
0x670ccda  jne short 0x670CCC0                           ; -> loc_670ccc0
loc_670ccdc:  ; from 670ccbd
0x670ccdc  lea rax,[rbp+0x7A0]                           
0x670cce3  mov [rbp+0x790],rax                           
0x670ccea  mov rax,0x100000000                           
0x670ccf4  mov [rbp+0x798],rax                           
0x670ccfb  lea rsi,[rbp+0x790]                           
0x670cd02  mov rcx,rsi                                   
0x670cd05  lea rdx,[rbp+0x7D0]                           
0x670cd0c  call 0x6764990                                ; -> sub_6764990
0x670cd11  nop                                           
0x670cd12  mov [rsp+0x20],rsi                            
0x670cd17  mov rcx,r13                                   
0x670cd1a  lea rdx,[rbp+0x208]                           
0x670cd21  lea r8,[rbp+0x1B0]                            
0x670cd28  lea r9,[rbp+0x128]                            
0x670cd2f  call 0x6792980                                ; -> sub_6792980
0x670cd34  nop                                           
```

Interpretation: do { call 0x676A670(&[rbp+0x7D0], r13, r15); r15 += 0x20; } while (r15 != rsi). [rbp+0x790]=[rbp+0x7E0]; [rbp+0x798]=0x100000000; call 0x6764990(&[rbp+0x790], &[rbp+0x7D0]); [rsp+0x20]=rsi; call 0x6792980(r13, &[rbp+0x208], &[rbp+0x1B0], &[rbp+0x128]).

Callees: 0x676A670 (sub_676a670), 0x6764990 (sub_6764990), 0x6792980 (sub_6792980).
Fields read: [rbp+0x7D0], r13, r15, rsi, [rbp+0x7A0], [rbp+0x7D0], [rbp+0x208], [rbp+0x1B0], [rbp+0x128]. Fields written: [rbp+0x790], [rbp+0x798], [rsp+0x20].
Matches F2 Phase 14? Yes in structure — both set up a loop/copy region then call 0x6764990 followed by 0x6792980 with a saved [rsp+0x20] argument. F2 Phase 14 uses rcx=r14=&[rbp+0x780]/rdx=&[rbp+0x7C0] for 0x6764990 and rcx=r12/rdx=&[rbp+0x1F8]/r8=&[rbp+0x1A0]/r9=&[rbp+0x118] for 0x6792980; here rcx=rsi=&[rbp+0x790]/rdx=&[rbp+0x7D0] and rcx=r13/rdx=&[rbp+0x208]/r8=&[rbp+0x1B0]/r9=&[rbp+0x128]. Same pattern, different slots/registers.

---

## Phase 16 — Copy [rbp+0x260]→[rbp+0x6F0] + byte/u16 locals + call 0x5ABA5C0 (0x670cd35..0x670cdc6)

Copies [rcx=&[rbp+0x260]]+{0x10,0x0} to [rdx=&[rbp+0x6F0]]+{0x10,0x0}, saves byte [rbp+0x274] at [rbp+0x704] and xmm [rbp+0x278] at [rbp+0x708], then copies [r14+0x88/0x98/0xA7] into [rbp+0x584+0x194/0x1A4/0x1B3] and u16 [rbp+0x2B8] at [rbp+0x748]. Finally builds BuilderSpan+0x9D0 arg and calls 0x5ABA5C0.

```
0x670cd35  lea rcx,[rbp+0x260]                           
0x670cd3c  mov eax,[rcx+0x10]                            
0x670cd3f  lea rdx,[rbp+0x6F0]                           
0x670cd46  mov [rdx+0x10],eax                            
0x670cd49  movups xmm0,[rcx]                             
0x670cd4c  movups [rdx],xmm0                             
0x670cd4f  movzx eax,byte ptr [rbp+0x274]                
0x670cd56  mov [rbp+0x704],al                            
0x670cd5c  movups xmm0,[rbp+0x278]                       
0x670cd63  movups [rbp+0x708],xmm0                       
0x670cd6a  movups xmm0,[r14+0x88]                        
0x670cd72  movups xmm1,[r14+0x98]                        
0x670cd7a  movups xmm2,[r14+0xA7]                        
0x670cd82  lea rax,[rbp+0x584]                           
0x670cd89  movups [rax+0x1B3],xmm2                       
0x670cd90  movups [rax+0x1A4],xmm1                       
0x670cd97  movups [rax+0x194],xmm0                       
0x670cd9e  movzx eax,word ptr [rbp+0x2B8]                
0x670cda5  mov [rbp+0x748],ax                            
0x670cdac  mov rax,[rbp+0x838]                           
0x670cdb3  mov rcx,[rax+0x10]                            
0x670cdb7  mov eax,0x9D0                                 
0x670cdbc  add rcx,rax                                   
0x670cdbf  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x670cdc4  nop                                           
0x670cdc5  mov r15,rax                                   
```

Interpretation: [rbp+0x700]=[rbp+0x270] (via [rcx+0x10] where rcx=&[rbp+0x260]); [rbp+0x6F0]=[rbp+0x260]; [rbp+0x704]=byte [rbp+0x274]; [rbp+0x708]=[rbp+0x278]; [rbp+0x707? no] — xmm2=[r14+0xA7]→[rbp+0x737] ([rax+0x1B3] where rax=&[rbp+0x584]), xmm1=[r14+0x98]→[rbp+0x728] ([rax+0x1A4]), xmm0=[r14+0x88]→[rbp+0x718] ([rax+0x194]); [rbp+0x748]=word [rbp+0x2B8]. rax=[rbp+0x838]; rcx=[rax+0x10]+0x9D0; call 0x5ABA5C0(rcx); result→r15.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x270], [rbp+0x260], [rbp+0x274], [rbp+0x278], [r14+0x88], [r14+0x98], [r14+0xA7], [rbp+0x2B8], [rbp+0x838], [rax+0x10]. Fields written: [rbp+0x700], [rbp+0x6F0], [rbp+0x704], [rbp+0x708], [rbp+0x737], [rbp+0x728], [rbp+0x718], [rbp+0x748], r15.
Matches F2 Phase 15? Partial match — F2 Phase 15 copies [rcx=&[rbp+0x250]]+{0x10,0} to [rbp+0x6F0/0x6E0], saves byte [rbp+0x264] at [rbp+0x6F4] and xmm [rbp+0x268] at [rbp+0x6F8], plus [rbx+0x88/0x98/0xA7] via [rbp+0x574] and u16 [rbp+0x2A8] at [rbp+0x738]. Same copy pattern, different source base ([rbp+0x260] vs [rbp+0x250]), dest slots ([rbp+0x6F0/0x704/0x708/0x748] vs [rbp+0x6F0/0x6F4/0x6F8/0x738]), and G2 does not follow with 0x5ABA5C0 in the same phase (F2 does in Phase 16).

---

## Phase 17 — mov r15,rax + zero xmm [rbp+0x310..0x3D0] + TLS/cookie + items write + jmp 0x6711EB1 (0x670cdc5..0x670ce6a)

r15 = pass object from 0x5ABA5C0. Zeroes xmm6 into [rbp+0x3C0]..[rbp+0x310] and [rbp+0x3D0]=0. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x857]. Then rdx=[r15+0x8A8] vs [r15+0x8B0]; if equal jump to 0x6711E9D (grow). Otherwise eax=word [rbp+0x748], store ax at [rdx] (write u16 to items buffer), [r15+0x8A8]+=2, jump to 0x6711EB1.

```
0x670cdc5  mov r15,rax                                   
0x670cdc8  movaps [rbp+0x3C0],xmm6                       
0x670cdcf  movaps [rbp+0x3B0],xmm6                       
0x670cdd6  movaps [rbp+0x3A0],xmm6                       
0x670cddd  movaps [rbp+0x390],xmm6                       
0x670cde4  movaps [rbp+0x380],xmm6                       
0x670cdeb  movaps [rbp+0x370],xmm6                       
0x670cdf2  movaps [rbp+0x360],xmm6                       
0x670cdf9  movaps [rbp+0x350],xmm6                       
0x670ce00  movaps [rbp+0x340],xmm6                       
0x670ce07  movaps [rbp+0x330],xmm6                       
0x670ce0e  movaps [rbp+0x320],xmm6                       
0x670ce15  movaps [rbp+0x310],xmm6                       
0x670ce1c  mov qword ptr [rbp+0x3D0],0                   
0x670ce27  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670ce2e  mov rax,[rcx]                                 
0x670ce31  mov rax,[rax+0x10]                            
0x670ce35  mov dl,0x4A                                   
0x670ce37  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ce3d  nop                                           
0x670ce3e  mov [rbp+0x857],al                            
0x670ce44  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x670ce4b  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x670ce52  je 0x6711E9D                                  ; -> sub_6711e9d
0x670ce58  movzx eax,word ptr [rbp+0x748]                
0x670ce5f  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x670ce62  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x670ce6a  jmp 0x6711EB1                                 ; -> sub_6711eb1
```

Interpretation: r15=rax. Zero xmm6 into [rbp+0x3C0], [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310]; [rbp+0x3D0]=0. TLS: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0]; [rbp+0x857]=al. rdx=[r15+0x8A8]; cmp [r15+0x8B0]; if equal goto 0x6711E9D. [rbp+0x748]→eax; [rdx]=ax; [r15+0x8A8]+=2; goto 0x6711EB1.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: rax, xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8B0], [rbp+0x748]. Fields written: [rbp+0x3C0], [rbp+0x3B0], [rbp+0x3A0], [rbp+0x390], [rbp+0x380], [rbp+0x370], [rbp+0x360], [rbp+0x350], [rbp+0x340], [rbp+0x330], [rbp+0x320], [rbp+0x310], [rbp+0x3D0], [rbp+0x857], [rdx] (items buffer), [r15+0x8A8].
Matches F2 Phase? Combines F2 Phase 16's zero-xmm block (here [rbp+0x310..0x3D0], F2 [rbp+0x4A0..0x560]) with F2 Phase 17's TLS+items write (here flag [rbp+0x857]/u16 [rbp+0x748]/jmp 0x6711EB1; F2 flag [rbp+0x847]/u16 [rbp+0x738]/jmp 0x677C3AE). No exact same-numbered counterpart; structure matches G1 Phase 3/10 pattern.

---

## Phase 18 — Slot fill [rbp+0x790..0x7B4] + shared_ptr refcount [rdi+0xD0] (part 1) (0x670ce6f..0x670cf59)

Fills [rbp+0x790]=[rbp+0x300], [rbp+0x798]=0, [rbp+0x7A0]=[rbp+0x830], [rbp+0x7A4]=[rbp+0x82C], [rbp+0x7A8]=[rbp+0x784], [rbp+0x7AC]=0x100000000, [rbp+0x7B4]=1, [rbp+0x7D0]=0. Then refcounts [rdi+0xD0]: if non-null lock inc [rcx+8], reload rcx=[rdi+0xD0], rdx=[rbp+0x798], jump to loc_670cf6f. Null path (xor edx,edx) repeats the slot fill with rdx=0 and jumps to loc_670cfa8. Second copy refcounts [rdi+0xD0] again and locks [rcx+8] at 0x670cf59.

```
0x670ce6f  xor edx,edx                                   
0x670ce71  mov rcx,[rbp+0x300]                           
0x670ce78  mov [rbp+0x790],rcx                           
0x670ce7f  mov [rbp+0x798],rdx                           
0x670ce86  mov ecx,[rbp+0x830]                           
0x670ce8c  mov [rbp+0x7A0],ecx                           
0x670ce92  mov ecx,[rbp+0x82C]                           
0x670ce98  mov [rbp+0x7A4],ecx                           
0x670ce9e  mov ecx,[rbp+0x784]                           
0x670cea4  mov [rbp+0x7A8],ecx                           
0x670ceaa  mov rcx,0x100000000                           
0x670ceb4  mov [rbp+0x7AC],rcx                           
0x670cebb  mov dword ptr [rbp+0x7B4],1                   
0x670cec5  movaps [rbp+0x7D0],xmm6                       
0x670cecc  mov rcx,[rdi+0xD0]                            
0x670ced3  test rcx,rcx                                  
0x670ced6  je 0x670CF6D                                  ; -> loc_670cf6d
0x670cedc  lock inc dword ptr [rcx+8]                    
0x670cee0  mov rcx,[rdi+0xD0]                            
0x670cee7  mov rdx,[rbp+0x798]                           
0x670ceee  jmp short 0x670CF6F                           ; -> loc_670cf6f
0x670cef0  xor edx,edx                                   
0x670cef2  mov rcx,[rbp+0x300]                           
0x670cef9  mov [rbp+0x790],rcx                           
0x670cf00  mov [rbp+0x798],rdx                           
0x670cf07  mov ecx,[rbp+0x830]                           
0x670cf0d  mov [rbp+0x7A0],ecx                           
0x670cf13  mov ecx,[rbp+0x82C]                           
0x670cf19  mov [rbp+0x7A4],ecx                           
0x670cf1f  mov ecx,[rbp+0x784]                           
0x670cf25  mov [rbp+0x7A8],ecx                           
0x670cf2b  mov rcx,0x100000000                           
0x670cf35  mov [rbp+0x7AC],rcx                           
0x670cf3c  mov dword ptr [rbp+0x7B4],1                   
0x670cf46  movaps [rbp+0x7D0],xmm6                       
0x670cf4d  mov rcx,[rdi+0xD0]                            
0x670cf54  test rcx,rcx                                  
0x670cf57  je short 0x670CFA8                            ; -> loc_670cfa8
0x670cf59  lock inc dword ptr [rcx+8]                    
```

Interpretation: edx=0; [rbp+0x790]=[rbp+0x300]; [rbp+0x798]=edx(0); [rbp+0x7A0]=[rbp+0x830]; [rbp+0x7A4]=[rbp+0x82C]; [rbp+0x7A8]=[rbp+0x784]; [rbp+0x7AC]=0x100000000; [rbp+0x7B4]=1; [rbp+0x7D0]=0. rcx=[rdi+0xD0]; if rcx==0 goto loc_670cf6d; else lock inc dword [rcx+8] (shared_ptr refcount). rcx=[rdi+0xD0]; rdx=[rbp+0x798]; goto loc_670cf6f. Null path: edx=0; repeat slot fill ([rbp+0x790..0x7A8], [rbp+0x7AC], [rbp+0x7B4], [rbp+0x7D0]=0). rcx=[rdi+0xD0]; if rcx==0 goto loc_670cfa8; else lock inc dword [rcx+8].

Callees: none.
Fields read: edx, [rbp+0x300], [rbp+0x830], [rbp+0x82C], [rbp+0x784], [rdi+0xD0], [rcx+8], [rbp+0x798]. Fields written: [rbp+0x790], [rbp+0x798], [rbp+0x7A0], [rbp+0x7A4], [rbp+0x7A8], [rbp+0x7AC], [rbp+0x7B4], [rbp+0x7D0], [rcx+8].
Matches F2 Phase 18? Yes in structure — both fill a slot region ([rbp+0x790..0x7A4] here vs [rbp+0x780..0x7A4] in F2), zero a 16-byte slot ([rbp+0x7C0] in F2, [rbp+0x7D0] here), set a 0x100000000 and dword=1 marker, and refcount a shared_ptr ([rdi+0xD0] here vs [rsi+0xD0] in F2) with lock inc [rcx+8]. F2 Phase 18 lacks the duplicated second refcount block seen here at 0x670cf2b..0x670cf59.

---

## Phase 19 — loc_670cf6f..loc_670d08f: shared_ptr slot construction + refcount rcx/rdx (0x670cf5d..0x670d08f)

Builds a 16-byte shared_ptr-like slot at [rbp+0x7D0..0x7DF]: [rbp+0x7D0]=[rdi+0xC8], [rbp+0x7D8]=rcx (0 or [rdi+0xD0]), zeroes [rbp+0x7E0], refcounts rdx if non-null. Then [rbp+0x7E0]=[rbp+0x790], [rbp+0x7E8]=rdx, builds second struct at [rbp+0x7A0]: r8=[rbp+0x7A0+0x10]→[r9+0x20], xmm0=[rbp+0x7A0]→[r9+0x10], [rbp+0x310]=0, refcounts rcx if non-null, resolves [rbp+0x310..0x318] from [rbp+0x7D0]/rcx, zeroes [rbp+0x314+0xC]. Multiple null/non-null branches (loc_670cf6d/6f, loc_670cfa8/aa, loc_670cfe3/e5, loc_670d039/3b, loc_670d08f/91).

```
0x670cf5d  mov rcx,[rdi+0xD0]                            
0x670cf64  mov rdx,[rbp+0x798]                           
0x670cf6b  jmp short 0x670CFAA                           ; -> loc_670cfaa
loc_670cf6d:  ; from 670ced6
0x670cf6d  xor ecx,ecx                                   
loc_670cf6f:  ; from 670ceee
0x670cf6f  mov r8,[rdi+0xC8]                             
0x670cf76  mov [rbp+0x7D0],r8                            
0x670cf7d  mov [rbp+0x7D8],rcx                           
0x670cf84  lea r8,[rbp+0x7E0]                            
0x670cf8b  movups [r8],xmm6                              
0x670cf8f  test rdx,rdx                                  
0x670cf92  je short 0x670CFE3                            ; -> loc_670cfe3
0x670cf94  lock inc dword ptr [rdx+8]                    
0x670cf98  mov rdx,[rbp+0x798]                           
0x670cf9f  mov rcx,[rbp+0x7D8]                           
0x670cfa6  jmp short 0x670CFE5                           ; -> loc_670cfe5
loc_670cfa8:  ; from 670cf57
0x670cfa8  xor ecx,ecx                                   
loc_670cfaa:  ; from 670cf6b
0x670cfaa  mov r8,[rdi+0xC8]                             
0x670cfb1  mov [rbp+0x7D0],r8                            
0x670cfb8  mov [rbp+0x7D8],rcx                           
0x670cfbf  lea r8,[rbp+0x7E0]                            
0x670cfc6  movups [r8],xmm6                              
0x670cfca  test rdx,rdx                                  
0x670cfcd  je short 0x670D039                            ; -> loc_670d039
0x670cfcf  lock inc dword ptr [rdx+8]                    
0x670cfd3  mov rdx,[rbp+0x798]                           
0x670cfda  mov rcx,[rbp+0x7D8]                           
0x670cfe1  jmp short 0x670D03B                           ; -> loc_670d03b
loc_670cfe3:  ; from 670cf92
0x670cfe3  xor edx,edx                                   
loc_670cfe5:  ; from 670cfa6
0x670cfe5  mov r8,[rbp+0x790]                            
0x670cfec  mov [rbp+0x7E0],r8                            
0x670cff3  mov [rbp+0x7E8],rdx                           
0x670cffa  lea r10,[rbp+0x7A0]                           
0x670d001  mov r8,[r10+0x10]                             
0x670d005  lea r9,[rbp+0x7E0]                            
0x670d00c  mov [r9+0x20],r8                              
0x670d010  movups xmm0,[r10]                             
0x670d014  movups [r9+0x10],xmm0                         
0x670d019  movaps [rbp+0x310],xmm6                       
0x670d020  test rcx,rcx                                  
0x670d023  je short 0x670D08F                            ; -> loc_670d08f
0x670d025  lock inc dword ptr [rcx+8]                    
0x670d029  mov rcx,[rbp+0x7D8]                           
0x670d030  mov rdx,[rbp+0x7E8]                           
0x670d037  jmp short 0x670D091                           ; -> loc_670d091
loc_670d039:  ; from 670cfcd
0x670d039  xor edx,edx                                   
loc_670d03b:  ; from 670cfe1
0x670d03b  mov r8,[rbp+0x790]                            
0x670d042  mov [rbp+0x7E0],r8                            
0x670d049  mov [rbp+0x7E8],rdx                           
0x670d050  lea r10,[rbp+0x7A0]                           
0x670d057  mov r8,[r10+0x10]                             
0x670d05b  lea r9,[rbp+0x7E0]                            
0x670d062  mov [r9+0x20],r8                              
0x670d066  movups xmm0,[r10]                             
0x670d06a  movups [r9+0x10],xmm0                         
0x670d06f  movaps [rbp+0x310],xmm6                       
0x670d076  test rcx,rcx                                  
0x670d079  je short 0x670D0C3                            ; -> loc_670d0c3
0x670d07b  lock inc dword ptr [rcx+8]                    
0x670d07f  mov rcx,[rbp+0x7D8]                           
0x670d086  mov rdx,[rbp+0x7E8]                           
0x670d08d  jmp short 0x670D0C5                           ; -> loc_670d0c5
loc_670d08f:  ; from 670d023
0x670d08f  xor ecx,ecx                                   
```

Interpretation: rcx=[rdi+0xD0]; rdx=[rbp+0x798]; goto loc_670cfaa. loc_670cf6d: ecx=0. loc_670cf6f: r8=[rdi+0xC8]; [rbp+0x7D0]=r8; [rbp+0x7D8]=rcx; zero [rbp+0x7E0]; if rdx==0 goto loc_670cfe3; else lock inc [rdx+8]; rdx=[rbp+0x798]; rcx=[rbp+0x7D8]; goto loc_670cfe5. loc_670cfa8: ecx=0. loc_670cfaa: same store pattern ([rbp+0x7D0]=[rdi+0xC8], [rbp+0x7D8]=rcx, zero [rbp+0x7E0]); if rdx==0 goto loc_670d039; else lock inc [rdx+8]; rdx=[rbp+0x798]; rcx=[rbp+0x7D8]; goto loc_670d03b. loc_670cfe3: edx=0. loc_670cfe5: [rbp+0x7E0]=[rbp+0x790]; [rbp+0x7E8]=rdx; r10=&[rbp+0x7A0]; r8=[r10+0x10]; r9=&[rbp+0x7E0]; [r9+0x20]=r8; xmm0=[r10]; [r9+0x10]=xmm0; [rbp+0x310]=0; if rcx==0 goto loc_670d08f; else lock inc [rcx+8]; rcx=[rbp+0x7D8]; rdx=[rbp+0x7E8]; goto loc_670d091. loc_670d039: edx=0. loc_670d03b: same as fe5 but if rcx==0 goto loc_670d0c3. loc_670d08f: ecx=0.

Callees: none.
Fields read: [rdi+0xD0], [rbp+0x798], [rdi+0xC8], [rcx+8], [rdx+8], [rbp+0x790], [rbp+0x7A0], [rbp+0x7A0+0x10], [rbp+0x7D8], [rbp+0x7E8]. Fields written: [rbp+0x7D0], [rbp+0x7D8], [rbp+0x7E0], [rcx+8], [rdx+8], [rbp+0x7E8], [rbp+0x310], [rbp+0x314+0xC].
Matches F2 Phase 19? Partial match — F2 Phase 19 stores [rsi+0xC8] at [rbp+0x7C0], [rbp+0x7C8]=rcx, zeroes [rbp+0x7D0], refcounts rdx. Here the analogous store is [rbp+0x7D0]=[rdi+0xC8]/[rbp+0x7D8]=rcx with refcount of rdx, plus the additional [rbp+0x7A0]-based 16-byte struct construction that appears in F2 Phase 20. Same shared_ptr slot-construction idiom, different slots/registers.

---

## Phase 20 — loc_670d091..0x670d0e1: resolve [rbp+0x310/0x318] + zero [rbp+0x314+0xC] (0x670d091..0x670d0e1)

loc_670d091: [rbp+0x310]=r8 ([rbp+0x7D0]), [rbp+0x318]=rcx, rcx=&[rbp+0x314], [rcx+0xC]=[rbp+0x320]=0 (xmm6). If rdx==0 goto loc_670d0fe else lock inc [rdx+8], r15=[rbp+0x7E8], goto loc_670d101. loc_670d0c3: ecx=0. loc_670d0c5: [rbp+0x310]=r8, [rbp+0x318]=rcx, [rcx+0xC]=[rbp+0x320]=0.

```
loc_670d091:  ; from 670d037
0x670d091  mov r8,[rbp+0x7D0]                            
0x670d098  mov [rbp+0x310],r8                            
0x670d09f  mov [rbp+0x318],rcx                           
0x670d0a6  lea rcx,[rbp+0x314]                           
0x670d0ad  movups [rcx+0xC],xmm6                         
0x670d0b1  test rdx,rdx                                  
0x670d0b4  je short 0x670D0FE                            ; -> loc_670d0fe
0x670d0b6  lock inc dword ptr [rdx+8]                    
0x670d0ba  mov r15,[rbp+0x7E8]                           
0x670d0c1  jmp short 0x670D101                           ; -> loc_670d101
loc_670d0c3:  ; from 670d079
0x670d0c3  xor ecx,ecx                                   
loc_670d0c5:  ; from 670d08d
0x670d0c5  mov r8,[rbp+0x7D0]                            
0x670d0cc  mov [rbp+0x310],r8                            
0x670d0d3  mov [rbp+0x318],rcx                           
0x670d0da  lea rcx,[rbp+0x314]                           
0x670d0e1  movups [rcx+0xC],xmm6                         
```

Interpretation: [rbp+0x310]=[rbp+0x7D0]; [rbp+0x318]=rcx; [rbp+0x320]=0; if (rdx!=0) { lock inc [rdx+8]; r15=[rbp+0x7E8]; } goto loc_670d101. Null alt: ecx=0; [rbp+0x310]=[rbp+0x7D0]; [rbp+0x318]=rcx; [rbp+0x320]=0.

Callees: none.
Fields read: [rbp+0x7D0], rcx, rdx, [rdx+8], [rbp+0x7E8]. Fields written: [rbp+0x310], [rbp+0x318], [rbp+0x320], [rdx+8], r15.
Matches F2 Phase 20? Partial match — F2 Phase 20 stores [rbp+0x780] at [rbp+0x7D0], [rbp+0x7D8]=rdx, builds the 16-byte struct ([r9+0x20]=[r10+0x10], movups [r10]→[r9+0x10]), zeroes [rbp+0x4A0], refcounts rcx. Here the analogous struct resolution is at [rbp+0x310/0x318/0x320] with [rcx+0xC]=0 and refcount of rdx. Same idiom, different slots; the [rbp+0x7A0] struct copy belongs to the previous phase here.

---

## Phase 21 — loc_670d0fe/loc_670d101 resolution + [rbp+0x320/0x328/0x348/0x350] + addss/addps + calls 0x67E2190 + 0x678E1D0 (0x670d0e5..0x670d19e)

loc_670d0fe: r15d=0. loc_670d101: [rbp+0x320]=[rbp+0x7E0], [rbp+0x328]=r15, rdx=&[rbp+0x7E0], rcx=[rdx+0x20]=[rbp+0x7F0], r8=&[rbp+0x314], [r8+0x2C]=[rbp+0x340]=rcx, xmm0=[rdx+0x10]=[rbp+0x7E0]→[r8+0x1C]=[rbp+0x330]. ecx=[rbp+0x7CC]→[rbp+0x348], ax→[rbp+0x350]. addss xmm12,xmm13; addps xmm15,xmm14; movlps [rbp+0x810]=xmm15; movss [rbp+0x818]=xmm12. Call 0x67E2190(rcx=&[rbp+0x2D0], rdx=r12). [rsp+0x20]=&[rbp+0x810]. Call 0x678E1D0(rcx=&[rbp+0x120], rdx=&[rbp+0x4C0], r8=&[rbp+0x468], r9=r12).

```
0x670d0e5  test rdx,rdx                                  
0x670d0e8  je 0x670D395                                  ; -> loc_670d395
0x670d0ee  lock inc dword ptr [rdx+8]                    
0x670d0f2  mov r15,[rbp+0x7E8]                           
0x670d0f9  jmp 0x670D398                                 ; -> loc_670d398
loc_670d0fe:  ; from 670d0b4
0x670d0fe  xor r15d,r15d                                 
loc_670d101:  ; from 670d0c1
0x670d101  mov rcx,[rbp+0x7E0]                           
0x670d108  mov [rbp+0x320],rcx                           
0x670d10f  mov [rbp+0x328],r15                           
0x670d116  lea rdx,[rbp+0x7E0]                           
0x670d11d  mov rcx,[rdx+0x20]                            
0x670d121  lea r8,[rbp+0x314]                            
0x670d128  mov [r8+0x2C],rcx                             
0x670d12c  movups xmm0,[rdx+0x10]                        
0x670d130  movups [r8+0x1C],xmm0                         
0x670d135  mov ecx,[rbp+0x7CC]                           
0x670d13b  mov [rbp+0x348],ecx                           
0x670d141  mov [rbp+0x350],ax                            
0x670d148  addss xmm12,xmm13                             
0x670d14d  addps xmm15,xmm14                             
0x670d151  movlps [rbp+0x810],xmm15                      
0x670d159  movss [rbp+0x818],xmm12                       
0x670d162  lea rcx,[rbp+0x2D0]                           
0x670d169  mov rdx,r12                                   
0x670d16c  call 0x67E2190                                ; -> sub_67e2190
0x670d171  nop                                           
0x670d172  lea rax,[rbp+0x810]                           
0x670d179  mov [rsp+0x20],rax                            
0x670d17e  lea rsi,[rbp+0x120]                           
0x670d185  mov rcx,rsi                                   
0x670d188  lea rdx,[rbp+0x4C0]                           
0x670d18f  lea r8,[rbp+0x468]                            
0x670d196  mov r9,r12                                    
0x670d199  call 0x678E1D0                                ; -> sub_678e1d0
0x670d19e  nop                                           
```

Interpretation: if (rdx!=0) { lock inc [rdx+8]; r15=[rbp+0x7E8]; } goto loc_670d398. loc_670d0fe: r15=0. loc_670d101: [rbp+0x320]=[rbp+0x7E0]; [rbp+0x328]=r15; rdx=&[rbp+0x7E0]; rcx=[rdx+0x20]; r8=&[rbp+0x314]; [r8+0x2C]=rcx; xmm0=[rdx+0x10]; [r8+0x1C]=xmm0. ecx=[rbp+0x7CC]; [rbp+0x348]=ecx; [rbp+0x350]=ax. xmm12+=xmm13; xmm15+=xmm14; [rbp+0x810]=low64(xmm15); [rbp+0x818]=low32(xmm12). rcx=&[rbp+0x2D0]; rdx=r12; call 0x67E2190. [rsp+0x20]=&[rbp+0x810]. rsi=&[rbp+0x120]; call 0x678E1D0(rcx=rsi, rdx=&[rbp+0x4C0], r8=&[rbp+0x468], r9=r12).

Callees: 0x67E2190 (sub_67e2190), 0x678E1D0 (sub_678e1d0).
Fields read: rdx, [rdx+8], [rbp+0x7E8], [rbp+0x7E0], [rdx+0x20], [rdx+0x10], [rbp+0x7CC], xmm12, xmm13, xmm15, xmm14, [rbp+0x2D0], r12, [rbp+0x120], [rbp+0x4C0], [rbp+0x468]. Fields written: [rbp+0x320], [rbp+0x328], [rbp+0x340], [rbp+0x330], [rbp+0x348], [rbp+0x350], [rbp+0x810], [rbp+0x818], [rsp+0x20], r15.
Matches F2 Phase 21? Partial match — F2 Phase 21 stores [rbp+0x7C0]→[rbp+0x4A0], rcx→[rbp+0x4A8], zeroes [rbp+0x4A4+0xC], refcounts rdx, r14=[rbp+0x7D8], [rbp+0x7D0]→[rbp+0x4B0], [rbp+0x4B8]=r14. Here [rbp+0x7E0]→[rbp+0x320], r15→[rbp+0x328], [rdx+0x20]→[rbp+0x340], [rdx+0x10]→[rbp+0x330], [rbp+0x7CC]→[rbp+0x348], ax→[rbp+0x350]. Same tail idiom, then both phases end with addss/addps + two calls (here 0x67E2190 then 0x678E1D0; F2 0x678CF10 then 0x678E1D0) and [rsp+0x20] spill.

---

## Phase 22 — Copy [rbp+0x4C0]→[r14+0x78..0xAF] + save byte/u16 locals + call 0x67E23F0 + call 0x6791420 + start copy to [rbp+0x710] (0x670d19f..0x670d2ba)

rcx=&[rbp+0x4C0]. eax=[rcx+0x68]→[r14+0x78]. xmm0=[rcx+0x58]→[r14+0x68]. al=byte [rbp+0x52C]→[rbp+0x27C]. xmm0=[rbp+0x530]→[rbp+0x280]. xmm0=[rcx+0x80], xmm1=[rcx+0x90], xmm2=[rcx+0x9F]→[r14+0xAF], [r14+0xA0], [r14+0x90]. ax=word [rbp+0x570]→[rbp+0x2C0]. rcx=r12; call 0x67E23F0. [rsp+0x38]=&[rbp+0x310], [rsp+0x30]=&[rbp+0x348], [rsp+0x28]=&[rbp+0x350], [rsp+0x20]=rsi. rcx=r13; rdx=&[rbp+0x210]; r8=&[rbp+0x1B8]; r9=&[rbp+0x130]; call 0x6791420. Then eax=[r14+0x78]→[rcx+0x10]=[rbp+0x720], xmm0=[r14+0x68]→[rcx]=[rbp+0x710], byte [rbp+0x27C]→[rbp+0x724], xmm0=[rbp+0x280]→[rbp+0x728], xmm0/1/2=[r14+0x90/0xA0/0xAF]→[rbp+0x584+0x1C3/0x1B4/0x1D3].

```
0x670d19f  lea rcx,[rbp+0x4C0]                           
0x670d1a6  mov eax,[rcx+0x68]                            
0x670d1a9  mov [r14+0x78],eax                            
0x670d1ad  movups xmm0,[rcx+0x58]                        
0x670d1b1  movups [r14+0x68],xmm0                        
0x670d1b6  movzx eax,byte ptr [rbp+0x52C]                
0x670d1bd  mov [rbp+0x27C],al                            
0x670d1c3  movups xmm0,[rbp+0x530]                       
0x670d1ca  movups [rbp+0x280],xmm0                       
0x670d1d1  movups xmm0,[rcx+0x80]                        
0x670d1d8  movups xmm1,[rcx+0x90]                        
0x670d1df  movups xmm2,[rcx+0x9F]                        
0x670d1e6  movups [r14+0xAF],xmm2                        
0x670d1ee  movups [r14+0xA0],xmm1                        
0x670d1f6  movups [r14+0x90],xmm0                        
0x670d1fe  movzx eax,word ptr [rbp+0x570]                
0x670d205  mov [rbp+0x2C0],ax                            
0x670d20c  mov rcx,r12                                   
0x670d20f  call 0x67E23F0                                ; -> sub_67e23f0
0x670d214  nop                                           
0x670d215  lea rax,[rbp+0x310]                           
0x670d21c  mov [rsp+0x38],rax                            
0x670d221  lea rax,[rbp+0x348]                           
0x670d228  mov [rsp+0x30],rax                            
0x670d22d  lea rax,[rbp+0x350]                           
0x670d234  mov [rsp+0x28],rax                            
0x670d239  mov [rsp+0x20],rsi                            
0x670d23e  mov rcx,r13                                   
0x670d241  lea rdx,[rbp+0x210]                           
0x670d248  lea r8,[rbp+0x1B8]                            
0x670d24f  lea r9,[rbp+0x130]                            
0x670d256  call 0x6791420                                ; -> sub_6791420
0x670d25b  nop                                           
0x670d25c  mov eax,[r14+0x78]                            
0x670d260  lea rcx,[rbp+0x710]                           
0x670d267  mov [rcx+0x10],eax                            
0x670d26a  movups xmm0,[r14+0x68]                        
0x670d26f  movups [rcx],xmm0                             
0x670d272  movzx eax,byte ptr [rbp+0x27C]                
0x670d279  mov [rbp+0x724],al                            
0x670d27f  movups xmm0,[rbp+0x280]                       
0x670d286  movups [rbp+0x728],xmm0                       
0x670d28d  movups xmm0,[r14+0x90]                        
0x670d295  movups xmm1,[r14+0xA0]                        
0x670d29d  movups xmm2,[r14+0xAF]                        
0x670d2a5  lea rax,[rbp+0x584]                           
0x670d2ac  movups [rax+0x1D3],xmm2                       
0x670d2b3  movups [rax+0x1C4],xmm1                       
0x670d2ba  movups [rax+0x1B4],xmm0                       
```

Interpretation: [r14+0x78]=[rbp+0x548] (=[rcx+0x68]); [r14+0x68]=[rbp+0x518] (=[rcx+0x58]); [rbp+0x27C]=byte [rbp+0x52C]; [rbp+0x280]=[rbp+0x530]; [r14+0xAF]=[rbp+0x540] (=[rcx+0x9F]); [r14+0xA0]=[rbp+0x538] (=[rcx+0x90]); [r14+0x90]=[rbp+0x528] (=[rcx+0x80]); [rbp+0x2C0]=word [rbp+0x570]. call 0x67E23F0(rcx=r12). Spill [rsp+0x38/0x30/0x28/0x20]. call 0x6791420(rcx=r13, rdx=&[rbp+0x210], r8=&[rbp+0x1B8], r9=&[rbp+0x130]). [rbp+0x720]=[r14+0x78]; [rbp+0x710]=[r14+0x68]; [rbp+0x724]=byte [rbp+0x27C]; [rbp+0x728]=[rbp+0x280]; [rbp+0x743?] — xmm2=[r14+0xAF]→[rbp+0x757] ([rax+0x1D3]), xmm1=[r14+0xA0]→[rbp+0x748] ([rax+0x1C4]), xmm0=[r14+0x90]→[rbp+0x738] ([rax+0x1B4]).

Callees: 0x67E23F0 (sub_67e23f0), 0x6791420 (sub_6791420).
Fields read: [rcx+0x68], [rcx+0x58], [rbp+0x52C], [rbp+0x530], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x570], r12, r13, rsi, [rbp+0x210], [rbp+0x1B8], [rbp+0x130], [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0x90], [r14+0xA0], [r14+0xAF]. Fields written: [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0xAF], [r14+0xA0], [r14+0x90], [rbp+0x2C0], [rsp+0x38], [rsp+0x30], [rsp+0x28], [rsp+0x20], [rbp+0x720], [rbp+0x710], [rbp+0x724], [rbp+0x728], [rbp+0x757], [rbp+0x748], [rbp+0x738].
Matches F2 Phase 25? Yes in structure — both call 0x67E23F0 then set up 4 stack spill args ([rsp+0x38/0x30/0x28/0x20]) and call 0x6791420. F2 uses rcx=r13 for 0x67E23F0 and spills &[rbp+0x4A0]/&[rbp+0x4D8]/&[rbp+0x4E0] with [rsp+0x20]=r15, then 0x6791420(rcx=r12, rdx=&[rbp+0x200], r8=&[rbp+0x1A8], r9=&[rbp+0x120]). Here rcx=r12, spills &[rbp+0x310]/&[rbp+0x348]/&[rbp+0x350] with [rsp+0x20]=rsi, then 0x6791420(rcx=r13, rdx=&[rbp+0x210], r8=&[rbp+0x1B8], r9=&[rbp+0x130]). Same pattern, different registers/slots. The following copy ([rbp+0x4C0]→[r14] and [r14]→[rbp+0x710]) matches F2 Phase 24/26's copy idiom.

---

## Phase 23 — Finish copy to [rbp+0x710..0x768] + call 0x5ABA5C0 + zero xmm [rbp+0x490..0x4A0] (0x670d2c1..0x670d33f)

ax=word [rbp+0x2C0]→[rbp+0x768]. rax=[rbp+0x838]; rcx=[rax+0x10]+0x9D0; call 0x5ABA5C0(rcx); result→r12. Zero xmm6 into [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0]; [rbp+0x4A0]=0.

```
0x670d2c1  movzx eax,word ptr [rbp+0x2C0]                
0x670d2c8  mov [rbp+0x768],ax                            
0x670d2cf  mov rax,[rbp+0x838]                           
0x670d2d6  mov rcx,[rax+0x10]                            
0x670d2da  mov eax,0x9D0                                 
0x670d2df  add rcx,rax                                   
0x670d2e2  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x670d2e7  nop                                           
0x670d2e8  mov r12,rax                                   
0x670d2eb  movaps [rbp+0x490],xmm6                       
0x670d2f2  movaps [rbp+0x480],xmm6                       
0x670d2f9  movaps [rbp+0x470],xmm6                       
0x670d300  movaps [rbp+0x460],xmm6                       
0x670d307  movaps [rbp+0x450],xmm6                       
0x670d30e  movaps [rbp+0x440],xmm6                       
0x670d315  movaps [rbp+0x430],xmm6                       
0x670d31c  movaps [rbp+0x420],xmm6                       
0x670d323  movaps [rbp+0x410],xmm6                       
0x670d32a  movaps [rbp+0x400],xmm6                       
0x670d331  movaps [rbp+0x3F0],xmm6                       
0x670d338  movaps [rbp+0x3E0],xmm6                       
0x670d33f  mov qword ptr [rbp+0x4A0],0                   
```

Interpretation: [rbp+0x768]=word [rbp+0x2C0]. rax=[rbp+0x838]; rcx=[rax+0x10]+0x9D0; call 0x5ABA5C0(rcx); r12=rax. Zero xmm6 into [rbp+0x490..0x3E0] and [rbp+0x4A0]=0.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x2C0], [rbp+0x838], [rax+0x10], xmm6. Fields written: [rbp+0x768], r12, [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], [rbp+0x4A0].
Matches F2 Phase 27? Partial match — F2 Phase 27 calls 0x5ABA5C0 (rcx=[rbp+0x828]+0x10+0x9D0), result→r13, zeroes [rbp+0x300..0x3C0] and [rbp+0x3C0]=0. Here result→r12, zeroes [rbp+0x490..0x4A0] and [rbp+0x4A0]=0. Same call+zero-xmm idiom, different result register and slot range.

---

## Phase 24 — TLS/cookie + feature flag [rbp+0x848] + items write u16 [rbp+0x768] + jmp 0x670DA6A (0x670d34a..0x670d390)

TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x848]. rdx=[r12+0x8A8] vs [r12+0x8B0]; if equal jump to 0x670DA55 (grow). Otherwise eax=word [rbp+0x768], store ax at [rdx], [r12+0x8A8]+=2, jump to 0x670DA6A.

```
0x670d34a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d351  mov rax,[rcx]                                 
0x670d354  mov rax,[rax+0x10]                            
0x670d358  mov dl,0x4A                                   
0x670d35a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d360  nop                                           
0x670d361  mov [rbp+0x848],al                            
0x670d367  mov rdx,[r12+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x670d36f  cmp rdx,[r12+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x670d377  je 0x670DA55                                  ; -> loc_670da55
0x670d37d  movzx eax,word ptr [rbp+0x768]                
0x670d384  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x670d387  add qword ptr [r12+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x670d390  jmp 0x670DA6A                                 ; -> loc_670da6a
```

Interpretation: rcx=[0x1233E1B0] (TLS base); rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0]; [rbp+0x848]=al (feature flag). rdx=[r12+0x8A8] (items write cursor); cmp [r12+0x8B0] (items end); if equal goto 0x670DA55. eax=word [rbp+0x768]; [rdx]=ax (write u16 to items buffer); [r12+0x8A8]+=2; goto 0x670DA6A.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [r12+0x8A8], [r12+0x8B0], [rbp+0x768]. Fields written: [rbp+0x848], [rdx] (items buffer), [r12+0x8A8].
Matches F2 Phase 28? Yes in structure — F2 Phase 28 does TLS read dl=0x4A, flag [rbp+0x838], items write u16 [rbp+0x758], jmp 0x677859B. Here flag [rbp+0x848], u16 [rbp+0x768], jmp 0x670DA6A. Same pattern, different slots/jump targets.

---

## Phase 25 — loc_670d395/loc_670d398 alternate: store [rbp+0x7E0..0x7E8] + struct copy + call 0x67E2190 + call 0x6791AF0 (0x670d395..0x670d433)

loc_670d395: r15d=0. loc_670d398: [rbp+0x320]=[rbp+0x7E0], [rbp+0x328]=r15, rdx=&[rbp+0x7E0], rcx=[rdx+0x20], r8=&[rbp+0x314], [r8+0x2C]=rcx, xmm0=[rdx+0x10]→[r8+0x1C]. ecx=[rbp+0x7CC]→[rbp+0x348], ax→[rbp+0x350]. rcx=&[rbp+0x2D0], rdx=rsi=&[rbp+0x120]; call 0x67E2190. Spill [rsp+0x30/0x28/0x20]=&[rbp+0x310/0x348/0x350]. rcx=r13; rdx=&[rbp+0x200]; r8=&[rbp+0x1A8]; r9=rsi; call 0x6791AF0.

```
loc_670d395:  ; from 670d0e8
0x670d395  xor r15d,r15d                                 
loc_670d398:  ; from 670d0f9
0x670d398  mov rcx,[rbp+0x7E0]                           
0x670d39f  mov [rbp+0x320],rcx                           
0x670d3a6  mov [rbp+0x328],r15                           
0x670d3ad  lea rdx,[rbp+0x7E0]                           
0x670d3b4  mov rcx,[rdx+0x20]                            
0x670d3b8  lea r8,[rbp+0x314]                            
0x670d3bf  mov [r8+0x2C],rcx                             
0x670d3c3  movups xmm0,[rdx+0x10]                        
0x670d3c7  movups [r8+0x1C],xmm0                         
0x670d3cc  mov ecx,[rbp+0x7CC]                           
0x670d3d2  mov [rbp+0x348],ecx                           
0x670d3d8  mov [rbp+0x350],ax                            
0x670d3df  lea rcx,[rbp+0x2D0]                           
0x670d3e6  lea rsi,[rbp+0x120]                           
0x670d3ed  mov rdx,rsi                                   
0x670d3f0  call 0x67E2190                                ; -> sub_67e2190
0x670d3f5  nop                                           
0x670d3f6  lea rax,[rbp+0x310]                           
0x670d3fd  mov [rsp+0x30],rax                            
0x670d402  lea rax,[rbp+0x348]                           
0x670d409  mov [rsp+0x28],rax                            
0x670d40e  lea rax,[rbp+0x350]                           
0x670d415  mov [rsp+0x20],rax                            
0x670d41a  mov rcx,r13                                   
0x670d41d  lea rdx,[rbp+0x200]                           
0x670d424  lea r8,[rbp+0x1A8]                            
0x670d42b  mov r9,rsi                                    
0x670d42e  call 0x6791AF0                                ; -> sub_6791af0
0x670d433  nop                                           
```

Interpretation: r15=0. [rbp+0x320]=[rbp+0x7E0]; [rbp+0x328]=r15; rdx=&[rbp+0x7E0]; rcx=[rdx+0x20]; r8=&[rbp+0x314]; [r8+0x2C]=rcx; xmm0=[rdx+0x10]; [r8+0x1C]=xmm0. ecx=[rbp+0x7CC]; [rbp+0x348]=ecx; [rbp+0x350]=ax. rcx=&[rbp+0x2D0]; rdx=rsi; call 0x67E2190. [rsp+0x30]=&[rbp+0x310]; [rsp+0x28]=&[rbp+0x348]; [rsp+0x20]=&[rbp+0x350]. rcx=r13; rdx=&[rbp+0x200]; r8=&[rbp+0x1A8]; r9=rsi. call 0x6791AF0.

Callees: 0x67E2190 (sub_67e2190), 0x6791AF0 (sub_6791af0).
Fields read: [rbp+0x7E0], r15, [rdx+0x20], [rdx+0x10], [rbp+0x7CC], [rbp+0x2D0], rsi, [rbp+0x200], [rbp+0x1A8]. Fields written: [rbp+0x320], [rbp+0x328], [rbp+0x340], [rbp+0x330], [rbp+0x348], [rbp+0x350], [rsp+0x30], [rsp+0x28], [rsp+0x20].
Matches F2 Phase 29? Yes in structure — F2 Phase 29: r14d=0, [rbp+0x7D0]→[rbp+0x4B0], [rbp+0x4B8]=r14, copy [rdx+0x20]→[r8+0x2C], movups [rdx+0x10]→[r8+0x1C], [rbp+0x7BC]→[rbp+0x4D8], [rbp+0x4E0]=ax, call 0x678CF10, spill [rsp+0x30/0x28/0x20], call 0x6791AF0(rcx=r12, rdx=&[rbp+0x1F0], r8=&[rbp+0x198], r9=r15). Here [rbp+0x7E0]→[rbp+0x320], [rbp+0x328]=r15, [rbp+0x7CC]→[rbp+0x348], [rbp+0x350]=ax, call 0x67E2190 (different first callee), spill same slots, 0x6791AF0(rcx=r13, rdx=&[rbp+0x200], r8=&[rbp+0x1A8], r9=rsi). Same pattern, different slots/callees.

---

## Phase 26 — Copy [r14+0x68..0x9F]→[rbp+0x700..0x758] + save byte/u16 locals + call 0x5ABA5C0 (0x670d434..0x670d4ba)

eax=[r14+0x68]→[rcx+0x10]=[rbp+0x710]. xmm0=[r14+0x58]→[rcx]=[rbp+0x700]. al=byte [rbp+0x26C]→[rbp+0x714]. xmm0=[rbp+0x270]→[rbp+0x718]. xmm0=[r14+0x80], xmm1=[r14+0x90], xmm2=[r14+0x9F]; rax=&[rbp+0x584]; xmm2→[rax+0x1C3]=[rbp+0x747], xmm1→[rax+0x1B4]=[rbp+0x738], xmm0→[rax+0x1A4]=[rbp+0x728]. ax=word [rbp+0x2B0]→[rbp+0x758]. rax=[rbp+0x838]; rcx=[rax+0x10]+0x9D0; call 0x5ABA5C0(rcx).

```
0x670d434  mov eax,[r14+0x68]                            
0x670d438  lea rcx,[rbp+0x700]                           
0x670d43f  mov [rcx+0x10],eax                            
0x670d442  movups xmm0,[r14+0x58]                        
0x670d447  movups [rcx],xmm0                             
0x670d44a  movzx eax,byte ptr [rbp+0x26C]                
0x670d451  mov [rbp+0x714],al                            
0x670d457  movups xmm0,[rbp+0x270]                       
0x670d45e  movups [rbp+0x718],xmm0                       
0x670d465  movups xmm0,[r14+0x80]                        
0x670d46d  movups xmm1,[r14+0x90]                        
0x670d475  movups xmm2,[r14+0x9F]                        
0x670d47d  lea rax,[rbp+0x584]                           
0x670d484  movups [rax+0x1C3],xmm2                       
0x670d48b  movups [rax+0x1B4],xmm1                       
0x670d492  movups [rax+0x1A4],xmm0                       
0x670d499  movzx eax,word ptr [rbp+0x2B0]                
0x670d4a0  mov [rbp+0x758],ax                            
0x670d4a7  mov rax,[rbp+0x838]                           
0x670d4ae  mov rcx,[rax+0x10]                            
0x670d4b2  mov eax,0x9D0                                 
0x670d4b7  add rcx,rax                                   
0x670d4ba  call 0x5ABA5C0                                ; -> sub_5aba5c0
```

Interpretation: [rbp+0x710]=[r14+0x68]; [rbp+0x700]=[r14+0x58]; [rbp+0x714]=byte [rbp+0x26C]; [rbp+0x718]=[rbp+0x270]; [rbp+0x747]=[r14+0x9F]; [rbp+0x738]=[r14+0x90]; [rbp+0x728]=[r14+0x80]; [rbp+0x758]=word [rbp+0x2B0]. rax=[rbp+0x838]; rcx=[rax+0x10]+0x9D0; call 0x5ABA5C0(rcx); result→rax (→r12 in next phase).

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [r14+0x68], [r14+0x58], [rbp+0x26C], [rbp+0x270], [r14+0x80], [r14+0x90], [r14+0x9F], [rbp+0x2B0], [rbp+0x838], [rax+0x10]. Fields written: [rbp+0x710], [rbp+0x700], [rbp+0x714], [rbp+0x718], [rbp+0x747], [rbp+0x738], [rbp+0x728], [rbp+0x758].
Matches F2 Phase 30? Partial match — F2 Phase 30 copies [rbx+0x68..0x9F] to [rbp+0x6F0..], saves byte [rbp+0x25C] at [rbp+0x704] and u16 [rbp+0x2A0] at [rbp+0x748], calls 0x5ABA5C0, then zeroes [rbp+0x370..0x3C0]. Here source is [r14], dest [rbp+0x700..], byte [rbp+0x26C] at [rbp+0x714], u16 [rbp+0x2B0] at [rbp+0x758], call 0x5ABA5C0 (no zero-xmm in this phase). Same copy idiom, different base register and slots.

---

## Phase 27 — mov r12,rax + zero xmm [rbp+0x490..0x4A0] + TLS + items write u16 [rbp+0x758] + jmp 0x670D964 (0x670d4bf..0x670d568)

nop; r12=rax (pass object from 0x5ABA5C0). Zero xmm6 into [rbp+0x490]..[rbp+0x4A0]. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x848]. rdx=[r12+0x8A8] vs [r12+0x8B0]; if equal jump to 0x670D94F (grow). Otherwise eax=word [rbp+0x758], store ax at [rdx], [r12+0x8A8]+=2, jump to 0x670D964.

```
0x670d4bf  nop                                           
0x670d4c0  mov r12,rax                                   
0x670d4c3  movaps [rbp+0x490],xmm6                       
0x670d4ca  movaps [rbp+0x480],xmm6                       
0x670d4d1  movaps [rbp+0x470],xmm6                       
0x670d4d8  movaps [rbp+0x460],xmm6                       
0x670d4df  movaps [rbp+0x450],xmm6                       
0x670d4e6  movaps [rbp+0x440],xmm6                       
0x670d4ed  movaps [rbp+0x430],xmm6                       
0x670d4f4  movaps [rbp+0x420],xmm6                       
0x670d4fb  movaps [rbp+0x410],xmm6                       
0x670d502  movaps [rbp+0x400],xmm6                       
0x670d509  movaps [rbp+0x3F0],xmm6                       
0x670d510  movaps [rbp+0x3E0],xmm6                       
0x670d517  mov qword ptr [rbp+0x4A0],0                   
0x670d522  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d529  mov rax,[rcx]                                 
0x670d52c  mov rax,[rax+0x10]                            
0x670d530  mov dl,0x4A                                   
0x670d532  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d538  nop                                           
0x670d539  mov [rbp+0x848],al                            
0x670d53f  mov rdx,[r12+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x670d547  cmp rdx,[r12+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x670d54f  je 0x670D94F                                  ; -> loc_670d94f
0x670d555  movzx eax,word ptr [rbp+0x758]                
0x670d55c  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x670d55f  add qword ptr [r12+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x670d568  jmp 0x670D964                                 ; -> loc_670d964
```

Interpretation: r12=rax. Zero xmm6 into [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], [rbp+0x4A0]=0. TLS: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x8A8]; cmp [r12+0x8B0]; if equal goto 0x670D94F. eax=word [rbp+0x758]; [rdx]=ax; [r12+0x8A8]+=2; goto 0x670D964.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: rax, xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r12+0x8A8], [r12+0x8B0], [rbp+0x758]. Fields written: [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], [rbp+0x4A0], [rbp+0x848], [rdx] (items buffer), [r12+0x8A8].
Matches F2 Phase? Combines F2 Phase 27's zero-xmm block (here [rbp+0x490..0x4A0], F2 [rbp+0x300..0x3C0]) with F2 Phase 28's TLS+items write (here flag [rbp+0x848]/u16 [rbp+0x758], F2 flag [rbp+0x838]/u16 [rbp+0x758]). Note u16 source slot [rbp+0x758] matches F2 exactly. No exact same-numbered counterpart.

---

## Phase 28 — call 0x1EF6F90 + TLS + count compute (sub/shr/dec → [rbp+0x3F0]) + TLS again (0x670d56d..0x670d5cd)

lea rcx,[r15+0x8A0]; lea r8,[rbp+0x718]; call 0x1EF6F90. TLS read #1: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx=byte [rbp+0x848], call via [0xF99FFA0], al→[rbp+0x848]. Then eax=[r15+0x8A8]; eax-=[r15+0x8A0]; shr eax,1; dec eax; [rbp+0x3F0]=ax. TLS read #2: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x848].

```
0x670d56d  lea rcx,[r15+0x8A0]                           
0x670d574  lea r8,[rbp+0718]                            
0x670d57b  call 0x1EF6F90                                ; -> sub_1ef6f90
0x670d580  nop                                           
0x670d581  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d588  mov rax,[rcx]                                 
0x670d58b  mov rax,[rax+0x10]                            
0x670d58f  movzx edx,byte ptr [rbp+0x848]                
0x670d596  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d59c  nop                                           
0x670d59d  mov eax,[r15+0x8A8]                           
0x670d5a4  sub eax,[r15+0x8A0]                           
0x670d5ab  shr eax,1                                     
0x670d5ad  dec eax                                       
0x670d5af  mov [rbp+0x3F0],ax                            
0x670d5b6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d5bd  mov rax,[rcx]                                 
0x670d5c0  mov rax,[rax+0x10]                            
0x670d5c4  mov dl,0x4A                                   
0x670d5c6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d5cc  nop                                           
0x670d5cd  mov [rbp+0x848],al                            
```

Interpretation: call 0x1EF6F90(rcx=[r15+0x8A0], r8=[rbp+0x718]). TLS #1: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call via [0xF99FFA0]; [rbp+0x848]=al. eax=[r15+0x8A8]-[r15+0x8A0]; eax>>=1; eax-=1; [rbp+0x3F0]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0]; [rbp+0x848]=al.

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect call, twice).
Fields read: [r15+0x8A0], [rbp+0x718], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x8A8], [r15+0x8A0]. Fields written: [rbp+0x848], [rbp+0x3F0].
Matches F2 Phase? No same-numbered counterpart — F2 Phases 29-30 are the alternate refcount/store and copy+call phases. The count-compute ((end-start)/2-1 → [rbp+0x3F0]) and double TLS-read pattern appears in F2's grow paths (Phases 32-33) rather than same-numbered phases.

---

## Phase 29 — items buffer write from [rbp+0x6C0] struct + add [r15+0x758],0x58 + jmp 0x670DB6F (0x670d5d3..0x670d668)

rdx=[r15+0x758] vs [r15+0x760]; if equal jump to 0x670DB5B (grow). Otherwise rcx=&[rbp+0x6C0]; eax=[rcx+0x10]→[rdx+0x10]; xmm0=[rcx]→[rdx]; al=byte [rbp+0x6D4]→[rdx+0x14]; xmm0=[rbp+0x6D8]→[rdx+0x18]; xmm0=[rbp+0x6DC]→[rdx+0x1C]; xmm0=[rbp+0x6E0]→[rdx+0x20]; xmm0=[rbp+0x6E4]→[rdx+0x24]. rax=&[rbp+0x584]; xmm0=[rax+0x164], xmm1=[rax+0x174], xmm2=[rax+0x183]; [rdx+0x28]=xmm0, [rdx+0x38]=xmm1, [rdx+0x47]=xmm2. [r15+0x758]+=0x58; jump to 0x670DB6F.

```
0x670d5d3  mov rdx,[r15+0x758]                           
0x670d5da  cmp rdx,[r15+0x760]                           
0x670d5e1  je 0x670DB5B                                  ; -> loc_670db5b
0x670d5e7  lea rcx,[rbp+0x6C0]                           
0x670d5ee  mov eax,[rcx+0x10]                            
0x670d5f1  mov [rdx+0x10],eax                            
0x670d5f4  movups xmm0,[rcx]                             
0x670d5f7  movups [rdx],xmm0                             
0x670d5fa  movzx eax,byte ptr [rbp+0x6D4]                
0x670d601  mov [rdx+0x14],al                             
0x670d604  movss xmm0,[rbp+0x6D8]                        
0x670d60c  movss [rdx+0x18],xmm0                         
0x670d611  movss xmm0,[rbp+0x6DC]                        
0x670d619  movss [rdx+0x1C],xmm0                         
0x670d61e  movss xmm0,[rbp+0x6E0]                        
0x670d626  movss [rdx+0x20],xmm0                         
0x670d62b  movss xmm0,[rbp+0x6E4]                        
0x670d633  movss [rdx+0x24],xmm0                         
0x670d638  lea rax,[rbp+0x584]                           
0x670d63f  movups xmm0,[rax+0x164]                       
0x670d646  movups xmm1,[rax+0x174]                       
0x670d64d  movups xmm2,[rax+0x183]                       
0x670d654  movups [rdx+0x28],xmm0                        
0x670d658  movups [rdx+0x38],xmm1                        
0x670d65c  movups [rdx+0x47],xmm2                        
0x670d660  add qword ptr [r15+0x758],0x58                
0x670d668  jmp 0x670DB6F                                 ; -> loc_670db6f
```

Interpretation: rdx=[r15+0x758] (items write cursor); cmp [r15+0x760] (items end); if equal goto 0x670DB5B. [rbp+0x6D0] (=[rcx+0x10])→[rdx+0x10]; [rbp+0x6C0]→[rdx]; byte [rbp+0x6D4]→[rdx+0x14]; [rbp+0x6D8]→[rdx+0x18]; [rbp+0x6DC]→[rdx+0x1C]; [rbp+0x6E0]→[rdx+0x20]; [rbp+0x6E4]→[rdx+0x24]. [rbp+0x6E8? no] — xmm0=[rbp+0x6E4?] — from [rbp+0x584+0x164]=[rbp+0x6E8]→[rdx+0x28]; [rbp+0x584+0x174]=[rbp+0x6F8]→[rdx+0x38]; [rbp+0x584+0x183]=[rbp+0x707]→[rdx+0x47]. [r15+0x758]+=0x58; goto 0x670DB6F.

Callees: none.
Fields read: [r15+0x758], [r15+0x760], [rcx+0x10], [rcx], [rbp+0x6D4], [rbp+0x6D8], [rbp+0x6DC], [rbp+0x6E0], [rbp+0x6E4], [rbp+0x584+0x164], [rbp+0x584+0x174], [rbp+0x584+0x183], [r15+0x758]. Fields written: [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r15+0x758].
Matches F2 Phase? No same-numbered counterpart — F2 Phases 29-30 are alternate-store/copy phases. This phase's item-buffer struct write (u16+byte+4 float32+3 xmm from [rbp+0x584]) resembles F2 Phase 32-33's grow-path item write idiom but with different source ([rbp+0x6C0] local vs [rbx]).

---

## Phase 30 — alternate path: call 0x1EF6F90 + TLS + count compute → [rbp+0x3F0] + TLS + call [0xF99FFA0] (unit end at 0x670d6c6) (0x670d66d..0x670d6c6)

lea rcx,[r15+0x8A0]; lea r8,[rbp+0x720]; call 0x1EF6F90. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx=byte [rbp+0x848], call via [0xF99FFA0], al→[rbp+0x848]. eax=[r15+0x8A8]; eax-=[r15+0x8A0]; shr eax,1; dec eax; [rbp+0x3F0]=ax. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0] (this is the 800th and final instruction of the unit).

```
0x670d66d  lea rcx,[r15+0x8A0]                           
0x670d674  lea r8,[rbp+0x720]                            
0x670d67b  call 0x1EF6F90                                ; -> sub_1ef6f90
0x670d680  nop                                           
0x670d681  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d688  mov rax,[rcx]                                 
0x670d68b  mov rax,[rax+0x10]                            
0x670d68f  movzx edx,byte ptr [rbp+0x848]                
0x670d696  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d69c  nop                                           
0x670d69d  mov eax,[r15+0x8A8]                           
0x670d6a4  sub eax,[r15+0x8A0]                           
0x670d6ab  shr eax,1                                     
0x670d6ad  dec eax                                       
0x670d6af  mov [rbp+0x3F0],ax                            
0x670d6b6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d6bd  mov rax,[rcx]                                 
0x670d6c0  mov rax,[rax+0x10]                            
0x670d6c4  mov dl,0x4A                                   
0x670d6c6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

Interpretation: call 0x1EF6F90(rcx=[r15+0x8A0], r8=[rbp+0x720]). TLS: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call via [0xF99FFA0]; [rbp+0x848]=al (next instruction, beyond unit). eax=[r15+0x8A8]-[r15+0x8A0]; eax>>=1; eax-=1; [rbp+0x3F0]=ax. TLS: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0] — final instruction of unit at 0x670d6c6.

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [r15+0x8A0], [rbp+0x720], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x8A8], [r15+0x8A0]. Fields written: [rbp+0x848], [rbp+0x3F0].
Matches F2 Phase? No same-numbered counterpart — F2 Phases 29-30 are alternate-store/copy phases. Same count-compute and TLS idiom as Phase 28 here, mirrored in F2's grow paths (Phases 32-33) rather than same-numbered phases.

---

## Unit Complete — 800 instructions transcribed

**File:** docs/progress/oc_U-E4-G2.md
**Range:** 0x670c5a6 to 0x670d6c6 (800 instructions from 0x670c5a6; Phases 1-13 pre-existed, Phases 14-30 added here)
**Status:** DONE — all 800 instructions fully transcribed into phases of at most 40 instructions each.

**All callee RVAs encountered (this continuation):** 0x676A670, 0x6764990, 0x6792980, 0x5ABA5C0, [0xF99FFA0]=sub_eea6040, 0x67E2190, 0x678E1D0, 0x67E23F0, 0x6791420, 0x1EF6F90, 0x6791AF0
(Combined with G1: 0x5679DB0, 0xE86B370, 0x5AB9970, 0xE935700, 0xAA6580, 0x678C4C0, 0x678E420, 0x678F640, 0x67E2540, 0x6769EE0 also appear across the full unit.)

**All [reg+disp] field reads/writes (this continuation):** [rbp+0x578], [rbp+0x788], [rax], [rcx], [rax+0x48], [rbp+0x310], [rbp+0x810], [rbp+0x818], [rbp+0x7E0], [rbp+0x7D0], [rbp+0x7D8], [rbp+0x7A0], [rbp+0x790], [rbp+0x798], [rbp+0x260], [rbp+0x6F0], [rbp+0x274], [rbp+0x278], [r14+0x88], [r14+0x98], [r14+0xA7], [rbp+0x584+0x194/0x1A4/0x1B3], [rbp+0x2B8], [rbp+0x748], [rbp+0x838], [rbp+0x3C0..0x310], [rbp+0x3D0], [0x1233E1B0], [rbp+0x857], [r15+0x8A8/0x8B0], [rbp+0x748], [rbp+0x300], [rbp+0x830], [rbp+0x82C], [rbp+0x784], [rbp+0x790..0x7B4], [rdi+0xD0], [rcx+8], [rdi+0xC8], [rbp+0x7C0], [rbp+0x7E0], [rbp+0x7E8], [rbp+0x7A0], [rbp+0x7A0+0x10], [rbp+0x320], [rbp+0x328], [rbp+0x340], [rbp+0x330], [rbp+0x7CC], [rbp+0x348], [rbp+0x350], [rbp+0x810], [rbp+0x818], [rbp+0x2D0], [rbp+0x4C0], [rbp+0x468], [rsp+0x38/0x30/0x28/0x20], [rbp+0x210], [rbp+0x1B8], [rbp+0x130], [rbp+0x710], [rbp+0x720], [rbp+0x724], [rbp+0x728], [rbp+0x738], [rbp+0x748], [rbp+0x757], [rbp+0x758], [rbp+0x768], [rbp+0x490..0x4A0], [0x1233E1B0], [rbp+0x848], [r12+0x8A8/0x8B0], [r15+0x758/0x760], [rbp+0x6C0..0x6E4], [rbp+0x584+0x164/0x174/0x183], [r15+0x8A0], [rbp+0x720], [rbp+0x3F0].

**Next RVA to resume:** 0x670d6cc (nop after the final call [0xF99FFA0] at 0x670d6c6) — beyond the 800-instruction unit; available for a follow-up unit.
