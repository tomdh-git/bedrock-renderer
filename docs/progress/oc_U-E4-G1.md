Identical to F1 Phase 27? Yes in structure — F1 used rcx=[rbp+0x3E0], dest [rbx+0x68..0xAF], slots [rbp+0x44C]/[rbp+0x450]/[rbp+0x490], dest slots [rbp+0x26C]/[rbp+0x270]/[rbp+0x2B0]; here rcx=[rbp+0x4C0], dest [r14+0x68..0xAF], slots [rbp+0x52C]/[rbp+0x530]/[rbp+0x570], dest slots [rbp+0x27C]/[rbp+0x280]/[rbp+0x2C0]. Same pattern, different slots/base registers.

---

## Phase 28 — Call 0x67E23F0 + call 0x678E420 (0x670beaa..0x670bed5)

Calls 0x67E23F0 with rcx=r12, then calls 0x678E420 with multiple output pointers.

```
0x670beaa  mov rcx,r12                                   
0x670bead  call 0x67E23F0                                ; -> sub_67e23f0
0x670beb2  nop                                           
0x670beb3  mov [rsp+0x20],rsi                            
0x670beb8  mov rcx,r13                                   
0x670bebb  lea rdx,[rbp+0x210]                           
0x670bec2  lea r8,[rbp+0x1B8]                            
0x670bec9  lea r9,[rbp+0x130]                            
0x670bed0  call 0x678E420                                ; -> sub_678e420
0x670bed5  nop                                           
```

Interpretation: rcx = r12 (&[rbp+0x3E0]). Call 0x67E23F0. [rsp+0x20] = rsi. rcx = r13 (&[rbp+0x580]). rdx = &[rbp+0x210]. r8 = &[rbp+0x1B8]. r9 = &[rbp+0x130]. Call 0x678E420.

Callees: 0x67E23F0 (sub_67e23f0), 0x678E420 (sub_678e420).
Fields read: none (registers only). Fields written: [rsp+0x20].

Identical to F1 Phase 28? Yes in structure — F1 used rcx=r13/rdx=&[rbp+0x200]/r8=&[rbp+0x1A8]/r9=&[rbp+0x120]; here rcx=r12/rdx=&[rbp+0x210]/r8=&[rbp+0x1B8]/r9=&[rbp+0x130]. Same pattern, different slots.

---

## Phase 29 — Copy [r14+0x68..0xAF] to [rbp+0x6C8..0x720] (0x670bed6..0x670bf38)

Copies data from [r14+0x68..0xAF] to [rbp+0x6C8..0x720], also saves byte [rbp+0x27C] and u16 [rbp+0x2C0].

```
0x670bed6  mov eax,[r14+0x78]                            
0x670beda  lea rcx,[rbp+0x6C8]                           
0x670bee1  mov [rcx+0x10],eax                            
0x670bee4  movups xmm0,[r14+0x68]                        
0x670bee9  movups [rcx],xmm0                             
0x670beec  movzx eax,byte ptr [rbp+0x27C]                
0x670bef3  mov [rbp+0x6DC],al                            
0x670bef9  movups xmm0,[rbp+0x280]                       
0x670bf00  movups [rbp+0x6E0],xmm0                       
0x670bf07  movups xmm0,[r14+0x90]                        
0x670bf0f  movups xmm1,[r14+0xA0]                        
0x670bf17  movups xmm2,[r14+0xAF]                        
0x670bf1f  lea rax,[rbp+0x6F0]                           
0x670bf26  movups [rax+0x1F],xmm2                        
0x670bf2a  movups [rax+0x10],xmm1                        
0x670bf2e  movups [rax],xmm0                             
0x670bf31  movzx eax,word ptr [rbp+0x2C0]                
0x670bf38  mov [rbp+0x720],ax                            
```

Interpretation: eax = [r14+0x78], store at [rcx+0x10] where rcx = &[rbp+0x6C8], so [rbp+0x6D8] = [r14+0x78]. xmm0 = [r14+0x68], stored at [rcx] = [rbp+0x6C8]. al = byte [rbp+0x27C], stored at [rbp+0x6DC]. xmm0 = [rbp+0x280], stored at [rbp+0x6E0]. xmm0 = [r14+0x90], xmm1 = [r14+0xA0], xmm2 = [r14+0xAF]. rax = &[rbp+0x6F0]. Store xmm2 at [rax+0x1F] = [rbp+0x70F], xmm1 at [rax+0x10] = [rbp+0x700], xmm0 at [rax] = [rbp+0x6F0]. ax = word [rbp+0x2C0], stored at [rbp+0x720].

Callees: none.
Fields read: [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0x90], [r14+0xA0], [r14+0xAF], [rbp+0x2C0]. Fields written: [rbp+0x6D8], [rbp+0x6C8], [rbp+0x6DC], [rbp+0x6E0], [rbp+0x70F], [rbp+0x700], [rbp+0x6F0], [rbp+0x720].

Identical to F1 Phase 29/29-continued? Yes in structure — F1 used [rbx+0x78]/[rbx+0x68] and slots [rbp+0x6C8]/[rbp+0x6CC]/[rbp+0x6D0]/[rbp+0x6FF]/[rbp+0x6F0]/[rbp+0x6E0]/[rbp+0x710]; here [r14+0x78]/[r14+0x68] and slots [rbp+0x6D8]/[rbp+0x6DC]/[rbp+0x6E0]/[rbp+0x70F]/[rbp+0x700]/[rbp+0x6F0]/[rbp+0x720]. Same pattern, different base register/slots.

---

## Phase 30 — Call 0x5ABA5C0 + zero xmm regs [rbp+0x3E0..0x4A0] (0x670bf3f..0x670bfaf)

Calls 0x5ABA5C0 to get pass object, then zeros xmm registers [rbp+0x3E0..0x4A0].

```
0x670bf3f  mov rax,[rbp+0x838]                           
0x670bf46  mov rcx,[rax+0x10]                            
0x670bf4a  mov eax,0x9D0                                 
0x670bf4f  add rcx,rax                                   
0x670bf52  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x670bf57  nop                                           
0x670bf58  mov r15,rax                                   
0x670bf5b  movaps [rbp+0x490],xmm6                       
0x670bf62  movaps [rbp+0x480],xmm6                       
0x670bf69  movaps [rbp+0x470],xmm6                       
0x670bf70  movaps [rbp+0x460],xmm6                       
0x670bf77  movaps [rbp+0x450],xmm6                       
0x670bf7e  movaps [rbp+0x440],xmm6                       
0x670bf85  movaps [rbp+0x430],xmm6                       
0x670bf8c  movaps [rbp+0x420],xmm6                       
0x670bf93  movaps [rbp+0x410],xmm6                       
0x670bf9a  movaps [rbp+0x400],xmm6                       
0x670bfa1  movaps [rbp+0x3F0],xmm6                       
0x670bfa8  movaps [rbp+0x3E0],xmm6                       
0x670bfaf  mov qword ptr [rbp+0x4A0],0                   
```

Interpretation: rax = [rbp+0x838] (BuilderSpan*). rcx = [rax+0x10]. rcx += 0x9D0. Call 0x5ABA5C0(rcx). Result (pass object) stored in r15. Then zero xmm6 into [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], and [rbp+0x4A0]=0.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x838], [rax+0x10], xmm6. Fields written: [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], [rbp+0x4A0].

Identical to F1 Phase 30? Yes in structure — F1 used rax=[rbp+0x828]/rcx=[rax+0x10]+0x9D0, zeroed [rbp+0x3B0]..[rbp+0x3C0]; here rax=[rbp+0x838]/rcx=[rax+0x10]+0x9D0, zeroes [rbp+0x490]..[rbp+0x4A0]. Same pattern, different slots.

---

## Phase 31 — TLS/cookie read + feature flag + items buffer write (0x670bfba..0x670bffd)

Reads TLS data, calls via [0xF99FFA0] with dl=0x4A, stores result at [rbp+0x848]. Then writes u16 [rbp+0x720] to items buffer.

```
0x670bfba  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670bfc1  mov rax,[rcx]                                 
0x670bfc4  mov rax,[rax+0x10]                            
0x670bfc8  mov dl,0x4A                                   
0x670bfca  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670bfd0  nop                                           
0x670bfd1  mov [rbp+0x848],al                            
0x670bfd7  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x670bfde  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x670bfe5  je 0x670D763                                  ; -> sub_670d763
0x670bfeb  movzx eax,word ptr [rbp+0x720]                
0x670bff2  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x670bff5  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x670bffd  jmp 0x670D777                                 ; -> sub_670d777
```

Interpretation: rcx = [0x1233E1B0] (TLS base). rax = [rcx], rax = [rax+0x10]. dl = 0x4A. Call via [0xF99FFA0]. Store al at [rbp+0x848] (feature flag). rdx = [r15+0x8A8] (items write cursor). Compare with [r15+0x8B0] (items end). If equal, jump to 0x670D763 (grow/overflow). Otherwise: eax = word [rbp+0x720], store ax at [rdx] (write u16 to items buffer), [r15+0x8A8] += 2 (advance cursor). Jump to 0x670D777.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8B0], [rbp+0x720]. Fields written: [rbp+0x848], [rdx] (items buffer), [r15+0x8A8].

Identical to F1 Phase 32? Yes in structure — F1 used dl=0x4A, slots [rbp+0x838], r14+0x8A8/0x8B0, [rbp+0x710]; here dl=0x4A, slot [rbp+0x848], r15+0x8A8/0x8B0, [rbp+0x720]. Same pattern, different slots/registers.

---

## Phase 32 — al==0 && [rbp+0x837]==0 && [rdi+0xE0]==1 path (0x670c002..0x670c040)

When byte [rdi+0xB8]!=0 was false (al==0) and [rbp+0x837]==0: check [rdi+0xE0]==1, call 0x67E2190, then call 0x678F640.

```
loc_670c002:  ; from 670bd82
0x670c002  cmp byte ptr [rdi+0xE0],1                     
0x670c009  jne 0x670C771                                 ; -> loc_670c771
0x670c00f  lea rcx,[rbp+0x2D0]                           
0x670c016  lea rdx,[rbp+0x120]                           
0x670c01d  call 0x67E2190                                ; -> sub_67e2190
0x670c022  nop                                           
0x670c023  mov rcx,r13                                   
0x670c026  lea rdx,[rbp+0x200]                           
0x670c02d  lea r8,[rbp+0x1A8]                            
0x670c034  lea r9,[rbp+0x120]                            
0x670c03b  call 0x678F640                                ; -> sub_678f640
0x670c040  nop                                           
```

Interpretation: If byte [rdi+0xE0] != 1, jump to loc_670c771. Otherwise: rcx = &[rbp+0x2D0], rdx = &[rbp+0x120]. Call 0x67E2190. Then rcx = r13 (&[rbp+0x580]), rdx = &[rbp+0x200], r8 = &[rbp+0x1A8], r9 = &[rbp+0x120]. Call 0x678F640.

Callees: 0x67E2190 (sub_67e2190), 0x678F640 (sub_678f640).
Fields read: [rdi+0xE0], [rbp+0x2D0], [rbp+0x120], r13, [rbp+0x200], [rbp+0x1A8]. Fields written: none.

Identical to F1 Phase 33? Yes in structure — F1 used [rsi+0xE0], slots [rbp+0x2C0]/[rbp+0x110], calls 0x678CF10 then 0x678F640; here [rdi+0xE0], slots [rbp+0x2D0]/[rbp+0x120], calls 0x67E2190 then 0x678F640. Same pattern, different slots/callee.

---

## Phase 33 — Copy [r14+0x68..0x9F] to [rbp+0x6C0..0x584+0x183] + call 0x5ABA5C0 (0x670c041..0x670c0c7)

Copies from [r14+0x68..0x9F] to [rbp+0x6C0..0x584+0x183], saves byte [rbp+0x26C] and u16 [rbp+0x2B0], then calls 0x5ABA5C0 again.

```
0x670c041  mov eax,[r14+0x68]                            
0x670c045  lea rcx,[rbp+0x6C0]                           
0x670c04c  mov [rcx+0x10],eax                            
0x670c04f  movups xmm0,[r14+0x58]                        
0x670c054  movups [rcx],xmm0                             
0x670c057  movzx eax,byte ptr [rbp+0x26C]                
0x670c05e  mov [rbp+0x6D4],al                            
0x670c064  movups xmm0,[rbp+0x270]                       
0x670c06b  movups [rbp+0x6D8],xmm0                       
0x670c072  movups xmm0,[r14+0x80]                        
0x670c07a  movups xmm1,[r14+0x90]                        
0x670c082  movups xmm2,[r14+0x9F]                        
0x670c08a  lea rax,[rbp+0x584]                           
0x670c091  movups [rax+0x183],xmm2                       
0x670c098  movups [rax+0x174],xmm1                       
0x670c09f  movups [rax+0x164],xmm0                       
0x670c0a6  movzx eax,word ptr [rbp+0x2B0]                
0x670c0ad  mov [rbp+0x718],ax                            
0x670c0b4  mov rax,[rbp+0x838]                           
0x670c0bb  mov rcx,[rax+0x10]                            
0x670c0bf  mov eax,0x9D0                                 
0x670c0c4  add rcx,rax                                   
0x670c0c7  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x670c0cc  nop                                           
0x670c0cd  mov r15,rax                                   
```

Interpretation: eax = [r14+0x68], store at [rcx+0x10] where rcx=&[rbp+0x6C0] → [rbp+0x6D0]. xmm0 = [r14+0x58], store at [rcx] = [rbp+0x6C0]. al = byte [rbp+0x26C], store at [rbp+0x6D4]. xmm0 = [rbp+0x270], store at [rbp+0x6D8]. xmm0 = [r14+0x80], xmm1 = [r14+0x90], xmm2 = [r14+0x9F]. rax = &[rbp+0x584]. Store xmm2 at [rax+0x183] = [rbp+0x707], xmm1 at [rax+0x174] = [rbp+0x6F8], xmm0 at [rax+0x164] = [rbp+0x6E8]. ax = word [rbp+0x2B0], store at [rbp+0x718]. rax = [rbp+0x838], rcx = [rax+0x10], rcx += 0x9D0. Call 0x5ABA5C0(rcx). Result → r15.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [r14+0x68], [r14+0x58], [rbp+0x26C], [rbp+0x270], [r14+0x80], [r14+0x90], [r14+0x9F], [rbp+0x2B0], [rbp+0x838], [rax+0x10]. Fields written: [rbp+0x6D0], [rbp+0x6C0], [rbp+0x6D4], [rbp+0x6D8], [rbp+0x707], [rbp+0x6F8], [rbp+0x6E8], [rbp+0x718].

Identical to F1 Phase 34? Yes in structure — F1 used [rbx+0x68]/[rbx+0x58] and slots [rbp+0x6C0]/[rbp+0x6B0]/[rbp+0x6C4]/[rbp+0x6C8]/[rbp+0x6F7]/[rbp+0x6E8]/[rbp+0x6D8]/[rbp+0x708]; here [r14+0x68]/[r14+0x58] and slots [rbp+0x6D0]/[rbp+0x6C0]/[rbp+0x6D4]/[rbp+0x6D8]/[rbp+0x707]/[rbp+0x6F8]/[rbp+0x6E8]/[rbp+0x718]. Same pattern, different base register/slots.

---

## Phase 34 — Zero xmm regs [rbp+0x3E0..0x4A0] + TLS/cookie + items write (0x670c0d0..0x670c172)

Zero xmm regs, TLS read, write u16 [rbp+0x718] to items buffer.

```
0x670c0d0  movaps [rbp+0x490],xmm6                       
0x670c0d7  movaps [rbp+0x480],xmm6                       
0x670c0de  movaps [rbp+0x470],xmm6                       
0x670c0e5  movaps [rbp+0x460],xmm6                       
0x670c0ec  movaps [rbp+0x450],xmm6                       
0x670c0f3  movaps [rbp+0x440],xmm6                       
0x670c0fa  movaps [rbp+0x430],xmm6                       
0x670c101  movaps [rbp+0x420],xmm6                       
0x670c108  movaps [rbp+0x410],xmm6                       
0x670c10f  movaps [rbp+0x400],xmm6                       
0x670c116  movaps [rbp+0x3F0],xmm6                       
0x670c11d  movaps [rbp+0x3E0],xmm6                       
0x670c124  mov qword ptr [rbp+0x4A0],0                   
0x670c12f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670c136  mov rax,[rcx]                                 
0x670c139  mov rax,[rax+0x10]                            
0x670c13d  mov dl,0x4A                                   
0x670c13f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670c145  nop                                           
0x670c146  mov [rbp+0x848],al                            
0x670c14c  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x670c153  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x670c15a  je 0x670D56D                                  ; -> loc_670d56d
0x670c160  movzx eax,word ptr [rbp+0x718]                
0x670c167  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x670c16a  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x670c172  jmp 0x670D581                                 ; -> loc_670d581
```

Interpretation: Zero xmm6 into [rbp+0x490]..[rbp+0x4A0]. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x848]. rdx=[r15+0x8A8] vs [r15+0x8B0]. If equal jump to 0x670D56D. Otherwise: eax=word [rbp+0x718], store ax at [rdx], [r15+0x8A8]+=2, jump to 0x670D581.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8B0], [rbp+0x718]. Fields written: [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], [rbp+0x4A0], [rbp+0x848], [rdx] (items buffer), [r15+0x8A8].

Identical to F1 Phase 43? Yes in structure — F1 zeroed [rbp+0x3B0]..[rbp+0x3C0], wrote [rbp+0x710]; here zeroes [rbp+0x490]..[rbp+0x4A0], writes [rbp+0x718]. Same pattern, different slots.

---

## Phase 35 — [rbp+0x846]!=3 path: store [rbp+0x7CC] + SIMD adjust + calls (0x670c177..0x670c247)

When [rbp+0x846] != 3 (from Phase 23's jne target): store [rbp+0x7CC] at [rbp+0x310], ax at [rbp+0x314], SIMD adjust, call 0x67E2190 and 0x678E1D0.

```
0x670c177  mov ecx,[rbp+0x7CC]                           
0x670c17d  mov [rbp+0x310],ecx                           
0x670c183  mov [rbp+0x314],ax                            
0x670c18a  addss xmm12,xmm13                             
0x670c18f  addps xmm15,xmm14                             
0x670c193  movlps [rbp+0x7D0],xmm15                      
0x670c19b  movss [rbp+0x7D8],xmm12                       
0x670c1a4  lea rcx,[rbp+0x2D0]                           
0x670c1ab  mov rdx,r12                                   
0x670c1ae  call 0x67E2190                                ; -> sub_67e2190
0x670c1b3  nop                                           
0x670c1b4  lea rax,[rbp+0x7D0]                           
0x670c1bb  mov [rsp+0x20],rax                            
0x670c1c0  lea rsi,[rbp+0x120]                           
0x670c1c7  mov rcx,rsi                                   
0x670c1ca  lea rdx,[rbp+0x4C0]                           
0x670c1d1  lea r8,[rbp+0x468]                            
0x670c1d8  mov r9,r12                                    
0x670c1db  call 0x678E1D0                                ; -> sub_678e1d0
0x670c1e0  nop                                           
0x670c1e1  lea rcx,[rbp+0x4C0]                           
0x670c1e8  mov eax,[rcx+0x68]                            
0x670c1eb  mov [r14+0x78],eax                            
0x670c1ef  movups xmm0,[rcx+0x58]                        
0x670c1f3  movups [r14+0x68],xmm0                        
0x670c1f8  movzx eax,byte ptr [rbp+0x52C]                
0x670c1ff  mov [rbp+0x27C],al                            
0x670c205  movups xmm0,[rbp+0x530]                       
0x670c20c  movups [rbp+0x280],xmm0                       
0x670c213  movups xmm0,[rcx+0x80]                        
0x670c21a  movups xmm1,[rcx+0x90]                        
0x670c221  movups xmm2,[rcx+0x9F]                        
0x670c228  movups [r14+0xAF],xmm2                        
0x670c230  movups [r14+0xA0],xmm1                        
0x670c238  movups [r14+0x90],xmm0                        
0x670c240  movzx eax,word ptr [rbp+0x570]                
0x670c247  mov [rbp+0x2C0],ax                            
```

Interpretation: ecx = [rbp+0x7CC], store at [rbp+0x310]. Store ax at [rbp+0x314]. xmm12 += xmm13, xmm15 += xmm14. Store low 64 bits of xmm15 at [rbp+0x7D0], low 32 bits of xmm12 at [rbp+0x7D8]. rcx = &[rbp+0x2D0], rdx = r12. Call 0x67E2190. [rsp+0x20] = &[rbp+0x7D0]. rsi = &[rbp+0x120]. Call 0x678E1D0(rcx=rsi, rdx=&[rbp+0x4C0], r8=&[rbp+0x468], r9=r12). Then rcx = &[rbp+0x4C0]. eax = [rcx+0x68] → [r14+0x78]. xmm0 = [rcx+0x58] → [r14+0x68]. al = byte [rbp+0x52C] → [rbp+0x27C]. xmm0 = [rbp+0x530] → [rbp+0x280]. xmm0 = [rcx+0x80], xmm1 = [rcx+0x90], xmm2 = [rcx+0x9F]. Store xmm2 at [r14+0xAF], xmm1 at [r14+0xA0], xmm0 at [r14+0x90]. ax = word [rbp+0x570] → [rbp+0x2C0].

Callees: 0x67E2190 (sub_67e2190), 0x678E1D0 (sub_678e1d0).
Fields read: [rbp+0x7CC], [rbp+0x314], xmm13, xmm12, xmm14, xmm15, [rbp+0x2D0], r12, [rbp+0x120], [rbp+0x4C0], [rbp+0x468], [rcx+0x68], [rcx+0x58], [rbp+0x52C], [rbp+0x530], [rcx+0x80], [rcx+0x90], [rcx+0x9F], [rbp+0x570]. Fields written: [rbp+0x310], [rbp+0x314], [rbp+0x7D0], [rbp+0x7D8], [rsp+0x20], [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0xAF], [r14+0xA0], [r14+0x90], [rbp+0x2C0].

Identical to F1 Phase 37? Yes in structure — F1 used [rbp+0x7BC], slots [rbp+0x4A0]/[rbp+0x4A4], calls 0x678CF10 then 0x678E1D0; here [rbp+0x7CC], slots [rbp+0x310]/[rbp+0x314], calls 0x67E2190 then 0x678E1D0. Same pattern, different slots/callees.

---

## Phase 36 — Call 0x67E23F0 + call 0x6791880 + copy to [rbp+0x6D8..0x730] (0x670c24e..0x670c30e)

Calls 0x67E23F0 with rcx=r12, then 0x6791880 with output pointers, then copies from [r14+0x68..0xAF] to [rbp+0x6D8..0x730].

```
0x670c24e  mov rcx,r12                                   
0x670c251  call 0x67E23F0                                ; -> sub_67e23f0
0x670c256  nop                                           
0x670c257  lea rax,[rbp+0x310]                           
0x670c25e  mov [rsp+0x30],rax                            
0x670c263  lea rax,[rbp+0x314]                           
0x670c26a  mov [rsp+0x28],rax                            
0x670c26f  mov [rsp+0x20],rsi                            
0x670c274  mov rcx,r13                                   
0x670c277  lea rdx,[rbp+0x210]                           
0x670c27e  lea r8,[rbp+0x1B8]                            
0x670c285  lea r9,[rbp+0x130]                            
0x670c28c  call 0x6791880                                ; -> sub_6791880
0x670c291  nop                                           
0x670c292  mov eax,[r14+0x78]                            
0x670c296  lea rcx,[rbp+0x6D8]                           
0x670c29d  mov [rcx+0x10],eax                            
0x670c2a0  movups xmm0,[r14+0x68]                        
0x670c2a5  movups [rcx],xmm0                             
0x670c2a8  movzx eax,byte ptr [rbp+0x27C]                
0x670c2af  mov [rbp+0x6EC],al                            
0x670c2b5  movups xmm0,[rbp+0x280]                       
0x670c2bc  movups [rbp+0x6F0],xmm0                       
0x670c2c3  movups xmm0,[r14+0x90]                        
0x670c2cb  movups xmm1,[r14+0xA0]                        
0x670c2d3  movups xmm2,[r14+0xAF]                        
0x670c2db  lea rax,[rbp+0x700]                           
0x670c2e2  movups [rax+0x1F],xmm2                        
0x670c2e6  movups [rax+0x10],xmm1                        
0x670c2ea  movups [rax],xmm0                             
0x670c2ed  movzx eax,word ptr [rbp+0x2C0]                
0x670c2f4  mov [rbp+0x730],ax                            
0x670c2fb  mov rax,[rbp+0x838]                           
0x670c302  mov rcx,[rax+0x10]                            
0x670c306  mov eax,0x9D0                                 
0x670c30b  add rcx,rax                                   
0x670c30e  call 0x5ABA5C0                                ; -> sub_5aba5c0
```

Interpretation: rcx = r12 (&[rbp+0x3E0]). Call 0x67E23F0. [rsp+0x30] = &[rbp+0x310]. [rsp+0x28] = &[rbp+0x314]. [rsp+0x20] = rsi. rcx = r13 (&[rbp+0x580]). rdx = &[rbp+0x210]. r8 = &[rbp+0x1B8]. r9 = &[rbp+0x130]. Call 0x6791880. Then eax = [r14+0x78] → [rcx+0x10] = [rbp+0x6E8]. xmm0 = [r14+0x68] → [rcx] = [rbp+0x6D8]. al = byte [rbp+0x27C] → [rbp+0x6EC]. xmm0 = [rbp+0x280] → [rbp+0x6F0]. xmm0 = [r14+0x90], xmm1 = [r14+0xA0], xmm2 = [r14+0xAF]. rax = &[rbp+0x700]. Store xmm2 at [rax+0x1F] = [rbp+0x71F], xmm1 at [rax+0x10] = [rbp+0x710], xmm0 at [rax] = [rbp+0x700]. ax = word [rbp+0x2C0] → [rbp+0x730]. rax = [rbp+0x838], rcx = [rax+0x10], rcx += 0x9D0. Call 0x5ABA5C0(rcx). Result → r15.

Callees: 0x67E23F0 (sub_67e23f0), 0x6791880 (sub_6791880), 0x5ABA5C0 (sub_5aba5c0).
Fields read: r12, r13, rsi, [rbp+0x210], [rbp+0x1B8], [rbp+0x130], [r14+0x78], [r14+0x68], [rbp+0x27C], [rbp+0x280], [r14+0x90], [r14+0xA0], [r14+0xAF], [rbp+0x2C0], [rbp+0x838], [rax+0x10]. Fields written: [rsp+0x30], [rsp+0x28], [rsp+0x20], [rbp+0x6E8], [rbp+0x6D8], [rbp+0x6EC], [rbp+0x6F0], [rbp+0x71F], [rbp+0x710], [rbp+0x700], [rbp+0x730].

Identical to F1 Phase 46? Yes in structure — F1 called 0x67E23F0 + 0x678E420 then copied to [rbp+0x6B8..0x710]; here 0x67E23F0 + 0x6791880 then copies to [rbp+0x6D8..0x730]. Same pattern, different callees/slots.

---

## Phase 37 — Zero xmm regs + TLS/cookie + items write (0x670c313..0x670c3b9)

Zero xmm regs [rbp+0x490..0x4A0], TLS read, write u16 [rbp+0x730] to items buffer.

```
0x670c313  nop                                           
0x670c314  mov r15,rax                                   
0x670c317  movaps [rbp+0x490],xmm6                       
0x670c31e  movaps [rbp+0x480],xmm6                       
0x670c325  movaps [rbp+0x470],xmm6                       
0x670c32c  movaps [rbp+0x460],xmm6                       
0x670c333  movaps [rbp+0x450],xmm6                       
0x670c33a  movaps [rbp+0x440],xmm6                       
0x670c341  movaps [rbp+0x430],xmm6                       
0x670c348  movaps [rbp+0x420],xmm6                       
0x670c34f  movaps [rbp+0x410],xmm6                       
0x670c356  movaps [rbp+0x400],xmm6                       
0x670c35d  movaps [rbp+0x3F0],xmm6                       
0x670c364  movaps [rbp+0x3E0],xmm6                       
0x670c36b  mov qword ptr [rbp+0x4A0],0                   
0x670c376  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670c37d  mov rax,[rcx]                                 
0x670c380  mov rax,[rax+0x10]                            
0x670c384  mov dl,0x4A                                   
0x670c386  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670c38c  nop                                           
0x670c38d  mov [rbp+0x848],al                            
0x670c393  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x670c39a  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x670c3a1  je 0x670D859                                  ; -> sub_670d859
0x670c3a7  movzx eax,word ptr [rbp+0x730]                
0x670c3ae  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x670c3b1  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x670c3b9  jmp 0x670D86D                                 ; -> sub_670d86d
```

Interpretation: Zero xmm6 into [rbp+0x490]..[rbp+0x4A0]. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x848]. rdx=[r15+0x8A8] vs [r15+0x8B0]. If equal jump to 0x670D859. Otherwise: eax=word [rbp+0x730], store ax at [rdx], [r15+0x8A8]+=2, jump to 0x670D86D.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8B0], [rbp+0x730]. Fields written: [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], [rbp+0x4A0], [rbp+0x848], [rdx] (items buffer), [r15+0x8A8].

Identical to F1 Phase 47? Yes in structure — F1 zeroed [rbp+0x3B0]..[rbp+0x3C0], wrote [rbp+0x710]; here zeroes [rbp+0x490]..[rbp+0x4A0], writes [rbp+0x730]. Same pattern, different slots.

---

## Phase 38 — [rbp+0x846]!=3 path (different variant): store [rbp+0x7CC] + calls 0x67E2190 + 0x6791F20 (0x670c3be..0x670c415)

When [rbp+0x846] != 3 (from Phase 24's jne target): store [rbp+0x7CC], call 0x67E2190 then 0x6791F20.

```
loc_670c3be:  ; from 670bd9f
0x670c3be  mov ecx,[rbp+0x7CC]                           
0x670c3c4  mov [rbp+0x310],ecx                           
0x670c3ca  mov [rbp+0x314],ax                            
0x670c3d1  lea rcx,[rbp+0x2D0]                           
0x670c3d8  lea rdx,[rbp+0x120]                           
0x670c3df  call 0x67E2190                                ; -> sub_67e2190
0x670c3e4  nop                                           
0x670c3e5  lea rax,[rbp+0x310]                           
0x670c3ec  mov [rsp+0x28],rax                            
0x670c3f1  lea rax,[rbp+0x314]                           
0x670c3f8  mov [rsp+0x20],rax                            
0x670c3fd  mov rcx,r13                                   
0x670c400  lea rdx,[rbp+0x200]                           
0x670c407  lea r8,[rbp+0x1A8]                            
0x670c40e  lea r9,[rbp+0x120]                            
0x670c415  call 0x6791F20                                ; -> sub_6791f20
0x670c41a  nop                                           
```

Interpretation: ecx = [rbp+0x7CC], store at [rbp+0x310]. Store ax at [rbp+0x314]. rcx = &[rbp+0x2D0], rdx = &[rbp+0x120]. Call 0x67E2190. [rsp+0x28] = &[rbp+0x310]. [rsp+0x20] = &[rbp+0x314]. rcx = r13 (&[rbp+0x580]), rdx = &[rbp+0x200], r8 = &[rbp+0x1A8], r9 = &[rbp+0x120]. Call 0x6791F20.

Callees: 0x67E2190 (sub_67e2190), 0x6791F20 (sub_6791f20).
Fields read: [rbp+0x7CC], [rbp+0x314], [rbp+0x2D0], [rbp+0x120], r13, [rbp+0x200], [rbp+0x1A8]. Fields written: [rbp+0x310], [rbp+0x314], [rsp+0x28], [rsp+0x20].

Identical to F1 Phase 41? Yes in structure — F1 used [rbp+0x7BC], slots [rbp+0x4A0]/[rbp+0x4A4], calls 0x678CF10 then 0x6791F20; here [rbp+0x7CC], slots [rbp+0x310]/[rbp+0x314], calls 0x67E2190 then 0x6791F20. Same pattern, different slots/callee.

---

## Phase 39 — Copy [r14+0x68..0x9F] to [rbp+0x6C8..0x720] + call 0x5ABA5C0 (0x670c41b..0x670c497)

Copies from [r14+0x68..0x9F] to [rbp+0x6C8..0x720], saves byte [rbp+0x26C] and u16 [rbp+0x2B0], then calls 0x5ABA5C0 again.

```
0x670c41b  mov eax,[r14+0x68]                            
0x670c41f  lea rcx,[rbp+0x6C8]                           
0x670c426  mov [rcx+0x10],eax                            
0x670c429  movups xmm0,[r14+0x58]                        
0x670c42e  movups [rcx],xmm0                             
0x670c431  movzx eax,byte ptr [rbp+0x26C]                
0x670c438  mov [rbp+0x6DC],al                            
0x670c43e  movups xmm0,[rbp+0x270]                       
0x670c445  movups [rbp+0x6E0],xmm0                       
0x670c44c  movups xmm0,[r14+0x80]                        
0x670c454  movups xmm1,[r14+0x90]                        
0x670c45c  movups xmm2,[r14+0x9F]                        
0x670c464  lea rax,[rbp+0x6F0]                           
0x670c46b  movups [rax+0x1F],xmm2                        
0x670c46f  movups [rax+0x10],xmm1                        
0x670c473  movups [rax],xmm0                             
0x670c476  movzx eax,word ptr [rbp+0x2B0]                
0x670c47d  mov [rbp+0x720],ax                            
0x670c484  mov rax,[rbp+0x838]                           
0x670c48b  mov rcx,[rax+0x10]                            
0x670c48f  mov eax,0x9D0                                 
0x670c494  add rcx,rax                                   
0x670c497  call 0x5ABA5C0                                ; -> sub_5aba5c0
```

Interpretation: eax = [r14+0x68], store at [rcx+0x10] where rcx=&[rbp+0x6C8] → [rbp+0x6D8]. xmm0 = [r14+0x58], store at [rcx] = [rbp+0x6C8]. al = byte [rbp+0x26C], store at [rbp+0x6DC]. xmm0 = [rbp+0x270], store at [rbp+0x6E0]. xmm0 = [r14+0x80], xmm1 = [r14+0x90], xmm2 = [r14+0x9F]. rax = &[rbp+0x6F0]. Store xmm2 at [rax+0x1F] = [rbp+0x70F], xmm1 at [rax+0x10] = [rbp+0x700], xmm0 at [rax] = [rbp+0x6F0]. ax = word [rbp+0x2B0], store at [rbp+0x720]. rax = [rbp+0x838], rcx = [rax+0x10], rcx += 0x9D0. Call 0x5ABA5C0(rcx). Result → r15.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [r14+0x68], [r14+0x58], [rbp+0x26C], [rbp+0x270], [r14+0x80], [r14+0x90], [r14+0x9F], [rbp+0x2B0], [rbp+0x838], [rax+0x10]. Fields written: [rbp+0x6D8], [rbp+0x6C8], [rbp+0x6DC], [rbp+0x6E0], [rbp+0x70F], [rbp+0x700], [rbp+0x6F0], [rbp+0x720].

Identical to F1 Phase 42? Yes in structure — F1 used [rbx+0x68]/[rbx+0x58] and slots [rbp+0x6C8]/[rbp+0x6B8]/[rbp+0x6CC]/[rbp+0x6D0]/[rbp+0x6FF]/[rbp+0x6F0]/[rbp+0x6E0]/[rbp+0x710]; here [r14+0x68]/[r14+0x58] and slots [rbp+0x6D8]/[rbp+0x6C8]/[rbp+0x6DC]/[rbp+0x6E0]/[rbp+0x70F]/[rbp+0x700]/[rbp+0x6F0]/[rbp+0x720]. Same pattern, different base register/slots.

---

## Phase 40 — Zero xmm regs + TLS/cookie + items write (0x670c49c..0x670c542)

Zero xmm regs [rbp+0x490..0x4A0], TLS read, write u16 [rbp+0x720] to items buffer.

```
0x670c49c  nop                                           
0x670c49d  mov r15,rax                                   
0x670c4a0  movaps [rbp+0x490],xmm6                       
0x670c4a7  movaps [rbp+0x480],xmm6                       
0x670c4ae  movaps [rbp+0x470],xmm6                       
0x670c4b5  movaps [rbp+0x460],xmm6                       
0x670c4bc  movaps [rbp+0x450],xmm6                       
0x670c4c3  movaps [rbp+0x440],xmm6                       
0x670c4ca  movaps [rbp+0x430],xmm6                       
0x670c4d1  movaps [rbp+0x420],xmm6                       
0x670c4d8  movaps [rbp+0x410],xmm6                       
0x670c4df  movaps [rbp+0x400],xmm6                       
0x670c4e6  movaps [rbp+0x3F0],xmm6                       
0x670c4ed  movaps [rbp+0x3E0],xmm6                       
0x670c4f4  mov qword ptr [rbp+0x4A0],0                   
0x670c4ff  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670c506  mov rax,[rcx]                                 
0x670c509  mov rax,[rax+0x10]                            
0x670c50d  mov dl,0x4A                                   
0x670c50f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670c515  nop                                           
0x670c516  mov [rbp+0x848],al                            
0x670c51c  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x670c523  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x670c52a  je 0x670D66D                                  ; -> loc_670d66d
0x670c530  movzx eax,word ptr [rbp+0x720]                
0x670c537  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x670c53a  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x670c542  jmp 0x670D681                                 ; -> loc_670d681
```

Interpretation: Zero xmm6 into [rbp+0x490]..[rbp+0x4A0]. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], dl=0x4A, call via [0xF99FFA0], al→[rbp+0x848]. rdx=[r15+0x8A8] vs [r15+0x8B0]. If equal jump to 0x670D66D. Otherwise: eax=word [rbp+0x720], store ax at [rdx], [r15+0x8A8]+=2, jump to 0x670D681.

Callees: [0xF99FFA0] = sub_eea6040 (indirect call).
Fields read: xmm6, [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8B0], [rbp+0x720]. Fields written: [rbp+0x490], [rbp+0x480], [rbp+0x470], [rbp+0x460], [rbp+0x450], [rbp+0x440], [rbp+0x430], [rbp+0x420], [rbp+0x410], [rbp+0x400], [rbp+0x3F0], [rbp+0x3E0], [rbp+0x4A0], [rbp+0x848], [rdx] (items buffer), [r15+0x8A8].

Identical to F1 Phase 43? Yes in structure — F1 zeroed [rbp+0x3B0]..[rbp+0x3C0], wrote [rbp+0x710]; here zeroes [rbp+0x490]..[rbp+0x4A0], writes [rbp+0x720]. Same pattern, different slots.

---

## Phase 41 — [rdi+0x48] qword compare + SIMD adjust + call 0x67E2190 + call 0x678E1D0 (0x670c547..0x670c5ab)

Compare qword [rdi+0x48] with 0xB, addss/addps SIMD adjust, store to [rbp+0x310/0x318], call 0x67E2190, then call 0x678E1D0.

```
0x670c547  mov rax,[rdi+0x48]                            
0x670c54b  cmp qword ptr [rax],0xB                       
0x670c54f  addss xmm12,xmm13                             
0x670c554  addps xmm15,xmm14                             
0x670c558  jne 0x670C8BB                                 ; -> loc_670c8bb
0x670c55e  movlps [rbp+0x310],xmm15                      
0x670c566  movss [rbp+0x318],xmm12                       
0x670c56f  lea rcx,[rbp+0x2D0]                           
0x670c576  mov rdx,r12                                   
0x670c579  call 0x67E2190                                ; -> sub_67e2190
0x670c57e  nop                                           
0x670c57f  lea rax,[rbp+0x310]                           
0x670c586  mov [rsp+0x20],rax                            
0x670c58b  lea rsi,[rbp+0x120]                           
0x670c592  mov rcx,rsi                                   
0x670c595  lea rdx,[rbp+0x4C0]                           
0x670c59c  lea r8,[rbp+0x468]                            
0x670c5a3  mov r9,r12                                    
0x670c5a6  call 0x678E1D0                                ; -> sub_678E1D0
```

Interpretation: rax = [rdi+0x48], compare qword [rax] with 0xB. xmm12 += xmm13, xmm15 += xmm14. If not equal, jump to loc_670c8bb. Otherwise: store low 64 bits of xmm15 at [rbp+0x310], low 32 bits of xmm12 at [rbp+0x318]. rcx = &[rbp+0x2D0], rdx = r12. Call 0x67E2190. [rsp+0x20] = &[rbp+0x310]. rsi = &[rbp+0x120]. Call 0x678E1D0(rcx=rsi, rdx=&[rbp+0x4C0], r8=&[rbp+0x468], r9=r12).

Callees: 0x67E2190 (sub_67e2190), 0x678E1D0 (sub_678e1d0).
Fields read: [rdi+0x48], [rax], xmm13, xmm12, xmm14, xmm15, [rbp+0x2D0], r12, [rbp+0x120], [rbp+0x4C0], [rbp+0x468]. Fields written: [rbp+0x310], [rbp+0x318], [rsp+0x20].

Identical to F1 Phase 44? Yes in structure — F1 used [rsi+0x48], slots [rbp+0x4A0]/[rbp+0x4A8], call 0x678CF10; here [rdi+0x48], slots [rbp+0x310]/[rbp+0x318], call 0x67E2190 then 0x678E1D0. Same pattern, different slots/callees.

---

## Unit Complete — First 800 instructions transcribed

**File:** docs/progress/oc_U-E4-G1.md
**Range:** 0x670b6e0 to 0x670c5ab (~800 instructions, 41 phases)
**Status:** DONE — first 800 instructions fully transcribed into phases of at most 40 instructions each.

**All callee RVAs encountered:** 0x5679DB0, 0xE86B370, 0x5AB9970, 0xE935700, 0xAA6580, 0x678C4C0, 0x67E2190, 0x678E1D0, 0x67E23F0, 0x678E420, 0x5ABA5C0, [0xF99FFA0]=sub_eea6040, 0x678F640, 0x6791880, 0x6791F20

**All [reg+disp] field reads/writes:** [rbp+0x8F0..0x860] xmm saves, [rbp+0x858] stack cookie, [rbp+0x108]/[rbp+0x838]/[rbp+0x778] arg saves, [rbp+0x847] TLS result, [rbp+0x2C8], [rbp+0x580], [rbp+0x120], [rbp+0x128], [rbp+0x828]/[rbp+0x82A], [rbp-0x40], [rbp+0x40], [rbp+0x300], [rbp+0x784], [rbp+0x846], [rbp+0x82C]/[rbp+0x830], [rbp+0x588]/[rbp+0x5A0]/[rbp+0x5A8]/[rbp+0x5B0], [rbp+0x100], [rbp+0x837], [rbp+0x788], [rbp+0x7CC], [rbp+0x2F0]/[rbp+0x2F8], [rbp+0x580..0x5B8], [rbp+0xA0..0xD0], [rbp+0x110], [rbp+0x2D0]/[rbp+0x2D8]/[rbp+0x2E0]/[rbp+0x2E8], [rbp+0x790], [rbp+0x308], [rbp+0x310]/[rbp+0x318], [rbp+0x4C0]/[rbp+0x468], [rbp+0x200]/[rbp+0x1A8]/[rbp+0x130]/[rbp+0x120], [rbp+0x6C8]/[rbp+0x6D8]/[rbp+0x6F0]/[rbp+0x6D0]/[rbp+0x6DC]/[rbp+0x6E0]/[rbp+0x70F]/[rbp+0x700]/[rbp+0x720]/[rbp+0x718]/[rbp+0x6EC]/[rbp+0x730]/[rbp+0x6E8], [rbp+0x3E0..0x4A0] (zeroed multiple times), [rdi+0xD8]/[rdi+0xB8]/[rdi+0xC0]/[rdi+0xC4]/[rdi+0x48]/[rdi+0x40]/[rdi+0x38]/[rdi+0x78]/[rdi+0x4C]/[rdi+0x50]/[rdi+0x28]/[rdi+0x18]/[rdi+0x10]/[rdi+0x3C]/[rdi+0x44], [rsi+0x48] via [rbp+0x778]+0x470, [rbx+0x48]/[rbx+0x4C]/[rbx+0x3C]/[rbx+0x44], [r14+0x78]/[r14+0x68]/[r14+0x90]/[r14+0xA0]/[r14+0xAF]/[r14+0x58]/[r14+0x80]/[r14+0x9F], [rcx+0x68]/[rcx+0x58]/[rcx+0x80]/[rcx+0x90]/[rcx+0x9F], [r15+0x8A8]/[r15+0x8B0] (items buffer cursor/end), [0x1233E1B0] TLS base, [0x129FB398]/[0x128767C8] globals, [0x129FB390] search key, gs:[0x58] TEB, [rsp+0x20]/[rsp+0x28]/[rsp+0x30] spill slots.

**Next RVA to resume:** 0x670c5ab (`nop` after call 0x678E1D0) — continuation of Phase 41's call sequence.
