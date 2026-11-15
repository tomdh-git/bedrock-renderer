# U-E4-G0b: Chunk builder gap 0x670bb20..0x670beaa

Unit: U-E4-G0b
Function: sub_670b6e0 (chunk builder, called by chunk extractor) — gap between G0 Phase 15 and G1 Phase 28
RVAs: 0x670bb20 .. 0x670bea9 (ends just before G1 Phase 28 at 0x670beaa)
Source: `rdis dis 0x670bb20 300` on Minecraft.Windows.exe 1.26.62.01; 300 instructions reach 0x670c18a, past 0x670beaa, so no continuation disassembly was needed. Verified 170 instructions from 0x670bb20 up to (not including) 0x670beaa, strictly increasing RVAs.
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown
Template: docs/progress/oc_U-E4-G0.md

## NEXT
Resume at 0x670beaa (Phase 28 — Call 0x67E23F0 + call 0x678E420, continues from G1).

Register/offset mapping (same function as G0/F1):
- G0 rdi = F1 rsi (4th/2nd arg respectively); rdi is the loop/entry object
- [rbp+0x108] = saved r9; [rbp+0x838] = saved rdx (BuilderSpan*); [rbp+0x778] = saved rcx (FrameCtx*)
- [rbp+0x970] = search-table object; [rbp+0x2C8] = &search_table+8; [rbp+0x580] = vector base; [rbp+0x120] = u64 one/flag; [rbp+0x128] = &[rbp+0x580]
- [rbp+0x828] = found index; [rbp+0x82A] = found flag; [rbp+0x846] = al from [rdi+0xD8]; [rbp+0x837] = byte [rbp+0x978] & cl
- [rbp+0x980]/[rbp+0x990] = struct-copy objects; [rbp+0x998] = u16 counter object; [rbp+0x308] = refcounted object
- rsi = &[rbp+0xA0] (loop scratch), r12 = &[rbp+0x3E0], r13 = &[rbp+0x580], r14 = &[rbp+0x200], rbx = loop iterator (0x58 stride)
- Constants loaded in Phase 13 (reused here): xmm7=[0xEEC8060], xmm8=[0xEFD32F0], xmm9=[0xF0A4080], xmm10=[0xEEC8060], xmm11=[0xEFD32F0], xmm13=[0xEFC13A4], xmm14=[0xF0B8740]; xmm6 = zero

---

## Phase 16 — SIMD reduce of xmm15 + first call 0xAA6580 (0x670bb20..0x670bbbb)

Continues Phase 15's body (xmm15 = [rbx+0x3C]). [rbp+0x2F0] = xmm15. [rbp+0x580] = 0x3F800000 (1.0f), [rbp+0x584] zeroed, [rbp+0x594] = 0x3F800000. SIMD: xmm0 = xmm15*xmm6; xmm1 = shufps(xmm0,0xE1) + xmm15; xmm12 = [rbx+0x44] -> [rbp+0x2F8]; xmm2 = xmm12*xmm7; xmm0 = xmm0 + shufps(xmm0,0x55) + xmm2 + xmm8; xmm2 = shufps(xmm2,0x55) + xmm1; xmm1 = xmm9; movlhps(xmm1, xmm2); xmm1 += xmm7 -> [rbp+0x5A8]; movlps [rbp+0x5B8] = xmm0. Call 0xAA6580(rcx=rsi=&[rbp+0xA0], rdx=&[rdi+0x78], r8=r13). Branch: ucomiss xmm0=[rbx+0x48] vs xmm10; jne -> loc_670bbcc; jnp -> loc_670bc58 (unordered).

```
0x670bb20  movsd [rbp+0x2F0],xmm15                       
0x670bb29  mov dword ptr [rbp+0x580],0x3F800000          
0x670bb33  lea rax,[rbp+0x584]                           
0x670bb3a  movups [rax],xmm6                             
0x670bb3d  mov dword ptr [rbp+0x594],0x3F800000          
0x670bb47  movups [rax+0x14],xmm6                        
0x670bb4b  movaps xmm0,xmm15                             
0x670bb4f  mulps xmm0,xmm6                               
0x670bb52  movaps xmm1,xmm0                              
0x670bb55  shufps xmm1,xmm0,0xE1                         
0x670bb59  addps xmm1,xmm15                              
0x670bb5d  movss xmm12,[rbx+0x44]                        
0x670bb63  movss [rbp+0x2F8],xmm12                       
0x670bb6c  movaps xmm2,xmm12                             
0x670bb70  shufps xmm2,xmm12,0                           
0x670bb75  mulps xmm2,xmm7                               
0x670bb78  movaps xmm3,xmm0                              
0x670bb7b  shufps xmm3,xmm0,0x55                         
0x670bb7f  unpcklps xmm0,xmm0                            
0x670bb82  addps xmm0,xmm3                               
0x670bb85  addps xmm0,xmm2                               
0x670bb88  addps xmm0,xmm8                               
0x670bb8c  shufps xmm2,xmm2,0x55                         
0x670bb90  addps xmm2,xmm1                               
0x670bb93  movaps xmm1,xmm9                              
0x670bb97  movlhps xmm1,xmm2                             
0x670bb9a  addps xmm1,xmm7                               
0x670bb9d  movups [rbp+0x5A8],xmm1                       
0x670bba4  movlps [rbp+0x5B8],xmm0                       
0x670bbab  mov rcx,rsi                                   
0x670bbae  lea rdx,[rdi+0x78]                            
0x670bbb2  mov r8,r13                                    
0x670bbb5  call 0xAA6580                                 ; -> sub_aa6580
0x670bbba  nop                                           
0x670bbbb  movss xmm0,[rbx+0x48]                         
0x670bbc0  ucomiss xmm0,xmm10                            
0x670bbc4  jne short 0x670BBCC                           ; -> loc_670bbcc
0x670bbc6  jnp 0x670BC58                                 ; -> loc_670bc58
```

Interpretation: Phase 15's xmm15 ([rbx+0x3C]) is stored at [rbp+0x2F0]; constants 1.0f (0x3F800000) at [rbp+0x580]/[rbp+0x594], zero at [rbp+0x584]. A horizontal-ish SIMD reduce of xmm15 produces [rbp+0x5A8] and [rbp+0x5B8]; [rbx+0x44] is saved at [rbp+0x2F8]. Call 0xAA6580 with rcx=rsi (&[rbp+0xA0]), rdx=&[rdi+0x78], r8=r13. Then [rbx+0x48] is compared (ucomiss) against xmm10: not-equal jumps to loc_670bbcc, unordered jumps to loc_670bc58, equal+ordered falls through into loc_670bbcc (next instruction).

Callees: 0xAA6580 (sub_aa6580) at 0x670bbb5 [V].
Fields read: xmm15, [rbx+0x44], [rbx+0x48], rsi (&[rbp+0xA0]), [rdi+0x78], r13, xmm6-xmm15.
Fields written: [rbp+0x2F0], [rbp+0x580], [rbp+0x584], [rbp+0x594], [rbp+0x2F8], [rbp+0x5A8], [rbp+0x5B8].

---

## Phase 17 — loc_670bbcc + second call 0xAA6580 + 64-byte copy + call 0x678C4C0 (0x670bbcc..0x670bc91)

loc_670bbcc (equal-or-not-equal, i.e. not unordered): xmm1 = broadcast(xmm0 element 0) * xmm7; [rbp+0x580] = xmm0 low; [rbp+0x584]/[rbp+0x598] = xmm1; [rbp+0x594] = xmm0; [rbp+0x5A8] = xmm2 (movdqu); [rbp+0x5B8] = xmm11. Call 0xAA6580(rcx=&[rbp+0x120], rdx=rsi, r8=r13). Reload xmm0..xmm3 from [rbp+0x120..0x150], store at [rbp+0xA0..0xD0] (64-byte struct copy). loc_670bc58 (unordered path): rax = [rbp+0x838], rdx = [rax], [rsp+0x20] = rbx, rcx = &[rbp+0x48], r8 = [rbp+0x108], r9 = [rbp+0x970]; call 0x678C4C0. [rbp+0x110] = &[rbp-0x40]. cmp byte [rbp+0x82A],1 -> jne loc_670bce6.

```
loc_670bbcc:  ; from 670bbc4
0x670bbcc  movaps xmm1,xmm0                              
0x670bbcf  shufps xmm1,xmm0,0                            
0x670bbd3  mulps xmm1,xmm7                               
0x670bbd6  movss [rbp+0x580],xmm0                        
0x670bbde  movq xmm2,xmm1                                
0x670bbe2  shufps xmm1,xmm1,0x55                         
0x670bbe6  movups [rbp+0x584],xmm1                       
0x670bbed  movss [rbp+0x594],xmm0                        
0x670bbf5  movups [rbp+0x598],xmm1                       
0x670bbfc  movdqu [rbp+0x5A8],xmm2                       
0x670bc04  movsd [rbp+0x5B8],xmm11                       
0x670bc0d  lea rcx,[rbp+0x120]                           
0x670bc14  mov rdx,rsi                                   
0x670bc17  mov r8,r13                                    
0x670bc1a  call 0xAA6580                                 ; -> sub_aa6580
0x670bc1f  nop                                           
0x670bc20  movaps xmm0,[rbp+0x120]                       
0x670bc27  movaps xmm1,[rbp+0x130]                       
0x670bc2e  movaps xmm2,[rbp+0x140]                       
0x670bc35  movaps xmm3,[rbp+0x150]                       
0x670bc3c  movaps [rbp+0xA0],xmm0                        
0x670bc43  movaps [rbp+0xB0],xmm1                        
0x670bc4a  movaps [rbp+0xC0],xmm2                        
0x670bc51  movaps [rbp+0xD0],xmm3                        

loc_670bc58:  ; from 670bbc6
0x670bc58  mov rax,[rbp+0x838]                           
0x670bc5f  mov rdx,[rax]                                 
0x670bc62  mov [rsp+0x20],rbx                            
0x670bc67  lea rcx,[rbp+0x48]                            
0x670bc6b  mov r8,[rbp+0x108]                            
0x670bc72  mov r9,[rbp+0x970]                            
0x670bc79  call 0x678C4C0                                ; -> sub_678c4c0
0x670bc7e  nop                                           
0x670bc7f  lea rax,[rbp-0x40]                            
0x670bc83  mov [rbp+0x110],rax                           
0x670bc8a  cmp byte ptr [rbp+0x82A],1                    
0x670bc91  jne short 0x670BCE6                           ; -> loc_670bce6
```

Interpretation: Two result vectors are written ([rbp+0x580..0x5B8]) depending on the compare outcome. Second call 0xAA6580 with rcx=&[rbp+0x120], rdx=rsi, r8=r13. Then a 64-byte copy [rbp+0x120..0x150] -> [rbp+0xA0..0xD0]. On the unordered path, call 0x678C4C0(rcx=&[rbp+0x48], rdx=[rax] where rax=[rbp+0x838], r8=[rbp+0x108], r9=[rbp+0x970]); save &[rbp-0x40] at [rbp+0x110]; if the found-flag byte [rbp+0x82A] != 1, jump to loc_670bce6.

Callees: 0xAA6580 (sub_aa6580) at 0x670bc1a [V]; 0x678C4C0 (sub_678c4c0) at 0x670bc79 [V].
Fields read: [rbp+0x580], [rbp+0x594], [rbp+0x120], [rbp+0x130], [rbp+0x140], [rbp+0x150], [rbp+0x838], [rax] (rax=[rbp+0x838]), rbx, [rbp+0x108], [rbp+0x970], [rbp+0x82A].
Fields written: [rbp+0x580], [rbp+0x584], [rbp+0x594], [rbp+0x598], [rbp+0x5A8], [rbp+0x5B8], [rbp+0xA0], [rbp+0xB0], [rbp+0xC0], [rbp+0xD0], [rsp+0x20], [rbp+0x110].

---

## Phase 18 — found-flag path + loc_670bce6 setup + byte [rdi+0xB8] branch (0x670bc93..0x670bd22)

Fall-through from Phase 17 when [rbp+0x82A] == 1: xmm0 = [rbx+0x4C]; ucomiss vs 0.0 (xmm1); jbe -> loc_670bce6 (skip if <= 0). Else [rbp+0x580] = broadcast(xmm0), [rbp+0x120] = 1, [rbp+0x128] = r13; call 0x5679DB0(rcx=[rbp+0x2C8], rdx=&[rbp+0x828], r8=&[rbp+0x120]) — same found-path call as G0 Phase 7; [rbp+0x110] = [rbp+0x970]. loc_670bce6 (merge target): [rbp+0x2D0] = [rbp+0x990], [rbp+0x2D8] = rsi, [rbp+0x2E0] = &[rbp+0x48], [rbp+0x2E8] = &[rbp+0x110]. al = byte [rdi+0xB8]; cmp byte [rbp+0x837], 0 -> je loc_670bd80.

```
0x670bc93  movss xmm0,[rbx+0x4C]                         
0x670bc98  xorps xmm1,xmm1                               
0x670bc9b  ucomiss xmm0,xmm1                             
0x670bc9e  jbe short 0x670BCE6                           ; -> loc_670bce6
0x670bca0  shufps xmm0,xmm0,0                            
0x670bca4  movaps [rbp+0x580],xmm0                       
0x670bcab  mov qword ptr [rbp+0x120],1                   
0x670bcb6  mov [rbp+0x128],r13                           
0x670bcbd  mov rcx,[rbp+0x2C8]                           
0x670bcc4  lea rdx,[rbp+0x828]                           
0x670bccb  lea r8,[rbp+0x120]                            
0x670bcd2  call 0x5679DB0                                ; -> sub_5679db0
0x670bcd7  nop                                           
0x670bcd8  mov rax,[rbp+0x970]                           
0x670bcdf  mov [rbp+0x110],rax                           

loc_670bce6:  ; from 670bc91, 670bc9e
0x670bce6  mov rax,[rbp+0x990]                           
0x670bced  mov [rbp+0x2D0],rax                           
0x670bcf4  mov [rbp+0x2D8],rsi                           
0x670bcfb  lea rax,[rbp+0x48]                            
0x670bcff  mov [rbp+0x2E0],rax                           
0x670bd06  lea rax,[rbp+0x110]                           
0x670bd0d  mov [rbp+0x2E8],rax                           
0x670bd14  movzx eax,byte ptr [rdi+0xB8]                 
0x670bd1b  cmp byte ptr [rbp+0x837],0                    
0x670bd22  je short 0x670BD80                           ; -> loc_670bd80
```

Interpretation: When the search found a match ([rbp+0x82A]==1) and [rbx+0x4C] > 0.0, re-broadcast [rbx+0x4C] into [rbp+0x580], reset [rbp+0x120]=1/[rbp+0x128]=r13 and re-run the found-path call 0x5679DB0 with index storage [rbp+0x828]/[rbp+0x82A]. Both paths merge at loc_670bce6, which builds a 4-pointer descriptor block at [rbp+0x2D0..0x2E8] from [rbp+0x990], rsi, &[rbp+0x48], &[rbp+0x110]. Then al = byte [rdi+0xB8]; if [rbp+0x837] == 0 jump to loc_670bd80, otherwise fall through to Phase 19.

Callees: 0x5679DB0 (sub_5679db0) at 0x670bcd2 [V].
Fields read: [rbx+0x4C], [rbp+0x82A], [rbp+0x2C8], [rbp+0x828], [rbp+0x120], [rbp+0x970], [rbp+0x990], rsi, [rdi+0xB8], [rbp+0x837].
Fields written: [rbp+0x580], [rbp+0x120], [rbp+0x128], [rbp+0x110], [rbp+0x2D0], [rbp+0x2D8], [rbp+0x2E0], [rbp+0x2E8].

---

## Phase 19 — al!=0 u16 counter increment + refcount inc (0x670bd24..0x670bd7d)

test al,al (al = byte [rdi+0xB8]); je loc_670bdd9 if al == 0 (goes to Phase 21). Else: rdx = [rbp+0x998]; eax = word [rdx]; cx = eax+1; [rdx] = cx (u16 counter++). cmp byte [rbp+0x846], 3 -> jne loc_670c177 ([rbp+0x846] != 3 path). cmp byte [rdi+0xD8], 3 -> jne 0x6713B31 (error handler sub_6713b31). [rbp+0x790] = xmm6 (zero). rcx = [rbp+0x308]; je loc_670ce6f if null; lock inc dword [rcx+8] (refcount++); rdx = [rbp+0x308]; jmp loc_670ce71; nop [rax].

```
0x670bd24  test al,al                                    
0x670bd26  je 0x670BDD9                                  ; -> loc_670bdd9
0x670bd2c  mov rdx,[rbp+0x998]                           
0x670bd33  movzx eax,word ptr [rdx]                      
0x670bd36  lea ecx,[rax+1]                               
0x670bd39  mov [rdx],cx                                  
0x670bd3c  cmp byte ptr [rbp+0x846],3                    
0x670bd43  jne 0x670C177                                 ; -> loc_670c177
0x670bd49  cmp byte ptr [rdi+0xD8],3                     
0x670bd50  jne 0x6713B31                                 ; -> sub_6713b31
0x670bd56  movaps [rbp+0x790],xmm6                       
0x670bd5d  mov rcx,[rbp+0x308]                           
0x670bd64  test rcx,rcx                                  
0x670bd67  je 0x670CE6F                                  ; -> loc_670ce6f
0x670bd6d  lock inc dword ptr [rcx+8]                    
0x670bd71  mov rdx,[rbp+0x308]                           
0x670bd78  jmp 0x670CE71                                 ; -> loc_670ce71
0x670bd7d  nop [rax]                                     
```

Interpretation: When byte [rdi+0xB8] != 0, increment the u16 counter at *[rbp+0x998]. If byte [rbp+0x846] != 3, branch to loc_670c177 (outside gap). If byte [rdi+0xD8] != 3, jump to error handler 0x6713B31. Otherwise zero [rbp+0x790], increment the refcount at [rcx+8] where rcx = [rbp+0x308] (with null check to loc_670ce6f), and jump to loc_670ce71 (both outside gap).

Callees: none (0x6713B31, loc_670ce6f, loc_670ce71 are branch targets outside the gap).
Fields read: al, [rbp+0x998], [rbp+0x846], [rdi+0xD8], [rbp+0x308], [rcx+8].
Fields written: [rbp+0x998] (u16 counter), [rbp+0x790], [rcx+8] (refcount, lock inc).

---

## Phase 20 — loc_670bd80 path: counter increment + refcount inc variant (0x670bd80..0x670bdd4)

loc_670bd80 (taken from Phase 18 when [rbp+0x837] == 0): test al,al; je loc_670bdd9 if al == 0 (goes to Phase 21). Else: rdx = [rbp+0x998]; word [rdx]++ (same u16 counter increment). cmp byte [rbp+0x846], 3 -> jne loc_670c3be. cmp byte [rdi+0xD8], 3 -> jne 0x6713B2B (error handler sub_6713b2b). [rbp+0x790] = xmm6. rcx = [rbp+0x308]; je loc_670cef0 if null; lock inc dword [rcx+8]; rdx = [rbp+0x308]; jmp loc_670cef2.

```
loc_670bd80:  ; from 670bd22
0x670bd80  test al,al                                    
0x670bd82  je 0x670C002                                  ; -> loc_670c002
0x670bd88  mov rdx,[rbp+0x998]                           
0x670bd8f  movzx eax,word ptr [rdx]                      
0x670bd92  lea ecx,[rax+1]                               
0x670bd95  mov [rdx],cx                                  
0x670bd98  cmp byte ptr [rbp+0x846],3                    
0x670bd9f  jne 0x670C3BE                                 ; -> loc_670c3be
0x670bda5  cmp byte ptr [rdi+0xD8],3                     
0x670bdac  jne 0x6713B2B                                 ; -> sub_6713b2b
0x670bdb2  movaps [rbp+0x790],xmm6                       
0x670bdb9  mov rcx,[rbp+0x308]                           
0x670bdc0  test rcx,rcx                                  
0x670bdc3  je 0x670CEF0                                  ; -> loc_670cef0
0x670bdc9  lock inc dword ptr [rcx+8]                    
0x670bdcd  mov rdx,[rbp+0x308]                           
0x670bdd4  jmp 0x670CEF2                                 ; -> loc_670cef2
```

Interpretation: Mirror of Phase 19 under [rbp+0x837]==0: if byte [rdi+0xB8] != 0, increment u16 counter at *[rbp+0x998]; if byte [rbp+0x846] != 3 branch to loc_670c3be; if byte [rdi+0xD8] != 3 jump to error handler 0x6713B2B; otherwise refcount-inc [rcx+8] (rcx=[rbp+0x308], null check to loc_670cef0) and jump to loc_670cef2. If al == 0, fall into Phase 21 at loc_670bdd9.

Callees: none (0x6713B2B, loc_670cef0, loc_670cef2 are branch targets outside the gap).
Fields read: al, [rbp+0x998], [rbp+0x846], [rdi+0xD8], [rbp+0x308], [rcx+8].
Fields written: [rbp+0x998] (u16 counter), [rbp+0x790], [rcx+8] (refcount, lock inc).

---

## Phase 21 — loc_670bdd9: al==0 && [rbp+0x837]==0 path + calls 0x67E2190 + 0x678E1D0 + result copy (0x670bdd9..0x670bea3)

loc_670bdd9 (byte [rdi+0xB8]==0 && [rbp+0x837]==0): cmp byte [rdi+0xE0], 1 -> jne loc_670c547 if != 1. Else: addss xmm12, xmm13; addps xmm15, xmm14; movlps [rbp+0x310] = xmm15; movss [rbp+0x318] = xmm12. Call 0x67E2190(rcx=&[rbp+0x2D0], rdx=r12). [rsp+0x20] = &[rbp+0x310]. Call 0x678E1D0(rcx=&[rbp+0x120], rdx=&[rbp+0x4C0], r8=&[rbp+0x468], r9=r12). Then rcx = &[rbp+0x4C0]: [r14+0x78] = [rcx+0x68], [r14+0x68] = [rcx+0x58], [rbp+0x27C] = byte [rbp+0x52C], [rbp+0x280] = [rbp+0x530], [r14+0xAF] = [rcx+0x9F], [r14+0xA0] = [rcx+0x90], [r14+0x90] = [rcx+0x80], [rbp+0x2C0] = word [rbp+0x570]. The next instruction, 0x670beaa `mov rcx,r12`, is G1 Phase 28.

```
loc_670bdd9:  ; from 670bd26
0x670bdd9  cmp byte ptr [rdi+0xE0],1                     
0x670bde0  jne 0x670C547                                 ; -> loc_670c547
0x670bde6  addss xmm12,xmm13                             
0x670bdeb  addps xmm15,xmm14                             
0x670bdef  movlps [rbp+0x310],xmm15                      
0x670bdf7  movss [rbp+0x318],xmm12                       
0x670be00  lea rcx,[rbp+0x2D0]                           
0x670be07  mov rdx,r12                                   
0x670be0a  call 0x67E2190                                ; -> sub_67e2190
0x670be0f  nop                                           
0x670be10  lea rax,[rbp+0x310]                           
0x670be17  mov [rsp+0x20],rax                            
0x670be1c  lea rsi,[rbp+0x120]                           
0x670be23  mov rcx,rsi                                   
0x670be26  lea rdx,[rbp+0x4C0]                           
0x670be2d  lea r8,[rbp+0x468]                            
0x670be34  mov r9,r12                                    
0x670be37  call 0x678E1D0                                ; -> sub_678e1d0
0x670be3c  nop                                           
0x670be3d  lea rcx,[rbp+0x4C0]                           
0x670be44  mov eax,[rcx+0x68]                            
0x670be47  mov [r14+0x78],eax                            
0x670be4b  movups xmm0,[rcx+0x58]                        
0x670be4f  movups [r14+0x68],xmm0                        
0x670be54  movzx eax,byte ptr [rbp+0x52C]                
0x670be5b  mov [rbp+0x27C],al                            
0x670be61  movups xmm0,[rbp+0x530]                       
0x670be68  movups [rbp+0x280],xmm0                       
0x670be6f  movups xmm0,[rcx+0x80]                        
0x670be76  movups xmm1,[rcx+0x90]                        
0x670be7d  movups xmm2,[rcx+0x9F]                        
0x670be84  movups [r14+0xAF],xmm2                        
0x670be8c  movups [r14+0xA0],xmm1                        
0x670be94  movups [r14+0x90],xmm0                        
0x670be9c  movzx eax,word ptr [rbp+0x570]                
0x670bea3  mov [rbp+0x2C0],ax                            
```

Interpretation: When byte [rdi+0xB8] == 0 and [rbp+0x837] == 0: if byte [rdi+0xE0] != 1, branch to loc_670c547. Otherwise adjust SIMD accumulators (xmm12 += xmm13, xmm15 += xmm14) and store [rbp+0x310]/[rbp+0x318]. Call 0x67E2190(rcx=&[rbp+0x2D0], rdx=r12), spill &[rbp+0x310] to [rsp+0x20], then call 0x678E1D0(rcx=&[rbp+0x120], rdx=&[rbp+0x4C0], r8=&[rbp+0x468], r9=r12). Finally copy fields from [rcx+0x68..0x9F] (rcx=&[rbp+0x4C0]) into [r14+0x78]/[r14+0x68]/[r14+0x90..0xAF] plus bytes [rbp+0x27C]/[rbp+0x280] and word [rbp+0x2C0]. The last gap instruction is at 0x670bea3; 0x670beaa begins G1 Phase 28.

Callees: 0x67E2190 (sub_67e2190) at 0x670be0a [V]; 0x678E1D0 (sub_678e1d0) at 0x670be37 [V].
Fields read: [rdi+0xE0], xmm12, xmm13, xmm15, xmm14, [rbp+0x2D0], r12, [rbp+0x120], [rbp+0x4C0], [rbp+0x468], [rcx+0x68], [rcx+0x58], [rbp+0x52C], [rbp+0x530], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x570].
Fields written: [rbp+0x310], [rbp+0x318], [rsp+0x20], [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0xAF], [r14+0xA0], [r14+0x90], [rbp+0x2C0].

---

## Gap summary (0x670bb20..0x670beaa)

Callees ([V] = call target seen in disassembly):
- 0xAA6580 (sub_aa6580): called at 0x670bbb5 (rcx=rsi=&[rbp+0xA0], rdx=&[rdi+0x78], r8=r13) and 0x670bc1a (rcx=&[rbp+0x120], rdx=rsi, r8=r13). Semantics unknown [?].
- 0x678C4C0 (sub_678c4c0): called at 0x670bc79 (rcx=&[rbp+0x48], rdx=[rax] with rax=[rbp+0x838], r8=[rbp+0x108], r9=[rbp+0x970]). Semantics unknown [?].
- 0x5679DB0 (sub_5679db0): called at 0x670bcd2 (rcx=[rbp+0x2C8], rdx=&[rbp+0x828], r8=&[rbp+0x120]); same found-path call as G0 Phase 7 [V].
- 0x67E2190 (sub_67e2190): called at 0x670be0a (rcx=&[rbp+0x2D0], rdx=r12) [V].
- 0x678E1D0 (sub_678e1d0): called at 0x670be37 (rcx=&[rbp+0x120], rdx=&[rbp+0x4C0], r8=&[rbp+0x468], r9=r12) [V].

Local branch targets (not calls; destinations outside or inside gap): loc_670bbcc, loc_670bc58, loc_670bce6, loc_670bd80, loc_670bdd9; error handlers 0x6713B31 (sub_6713b31) and 0x6713B2B (sub_6713b2b); join targets 0x670CE6F/0x670CE71 and 0x670CEF0/0x670CEF2; misaligned paths 0x670C177/0x670C3BE; [rdi+0xE0]!=1 targets 0x670C547/0x670C002.

Fields touched in the gap (offset, size, direction, meaning, tag):
- [rbp+0x2F0] W xmm15 ([rbx+0x3C] from Phase 15) [V]
- [rbp+0x580] W 0x3F800000 (1.0f), then SIMD result, then broadcast [rbx+0x4C] [V]
- [rbp+0x584] W zero (xmm6), then xmm1 [V]
- [rbp+0x594] W 0x3F800000, then xmm0 [V]
- [rbp+0x598] W xmm1 [V]
- [rbp+0x5A8] W xmm1 (movups), then xmm2 (movdqu) [V]
- [rbp+0x5B8] W xmm0 (movlps), then xmm11 (movsd) [V]
- [rbp+0x2F8] W xmm12 = [rbx+0x44] [V]
- [rbp+0x120] W/R 1, then &[rbp+0x120] passed by ref [V]
- [rbp+0x128] W r13 [V]
- [rbp+0xA0..0xD0] W 64-byte copy of [rbp+0x120..0x150] [V]
- [rbp+0x110] W &[rbp-0x40], then [rbp+0x970] [V]
- [rsp+0x20] W rbx, then &[rbp+0x310] [V]
- [rbp+0x2D0] W [rbp+0x990]; [rbp+0x2D8] W rsi; [rbp+0x2E0] W &[rbp+0x48]; [rbp+0x2E8] W &[rbp+0x110] [V]
- [rbp+0x998] R/W u16 counter (read-modify-write) [V]
- [rbp+0x308] R refcounted object; [rcx+8] R/W lock inc dword [V]
- [rbp+0x790] W xmm6 (zero) [V]
- [rbp+0x310] W movlps xmm15; [rbp+0x318] W movss xmm12 [V]
- [rbp+0x4C0] R base for copy; [rbp+0x468] R [V]
- [rbp+0x52C] R byte; [rbp+0x530] R xmm; [rbp+0x570] R word [V]
- [r14+0x78] W, [r14+0x68] W, [r14+0x90] W, [r14+0xA0] W, [r14+0xAF] W [V]
- [rbp+0x27C] W byte, [rbp+0x280] W xmm, [rbp+0x2C0] W word [V]
- [rbx+0x44] R, [rbx+0x48] R (ucomiss), [rbx+0x4C] R [V]
- [rdi+0x78] R (lea), [rdi+0xB8] R byte, [rdi+0xD8] R byte, [rdi+0xE0] R byte [V]
- [rbp+0x82A] R found flag; [rbp+0x828] R index ptr; [rbp+0x837] R flag; [rbp+0x846] R byte [V]
- [rbp+0x970] R, [rbp+0x990] R, [rbp+0x838] R [V]

OPEN questions:
- Semantics of 0xAA6580 (sub_aa6580) and 0x678C4C0 (sub_678C4C0) not determined from this gap [?].
- Error handlers 0x6713B31 / 0x6713B2B and join targets 0x670CE6F/0x670CE71 / 0x670CEF0/0x670CEF2 lie outside the gap [?].
- Constant data addresses xmm7/xmm8/xmm9/xmm10/xmm11/xmm13/xmm14 ([0xEEC8060], [0xEFD32F0], [0xF0A4080], [0xEFC13A4], [0xF0B8740]) were annotated in G0 Phase 13 as data (some as sub_1000000, meaning unclear) [?].
- Resume point verified: 0x670beaa matches G1 Phase 28 head (`mov rcx,r12; call 0x67E23F0`) [V].
