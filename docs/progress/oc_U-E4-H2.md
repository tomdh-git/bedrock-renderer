# U-E4-H2 — sub_6722cb0 continuation (builder 0x6722cb0)

H1 = docs/progress/oc_U-E4-H1.md covered phases 1-29, instructions 0x6722cb0..0x672396c.
H2 resumes at 0x6723971. Static analysis only. Tags: [V]=seen in disasm, [I]=inferred, [?]=unknown.

## NEXT
Resume at 0x6724a4d (the instruction after 0x6724a4a `mov rax,[rcx]`, which is the 800th instruction covered). Continue appending phases from there until 800 instructions consumed or rate limit.

---

## Phase 30 — al==3 copy+build block (0x6723971..0x6723a4b)

Same copy/build pattern as Phases 28-29 of H1, offsets shifted -0x10 vs the [rbp+0x450] variant: [rbp+0x79C] instead of [rbp+0x816], [rbp+0x510]/[rbp+0x370] instead of [rbp+0x560]/[rbp+0x460], [rbp+0x6A0] instead of [rbp+0x6B0], [rbx+0x50]/[rbx+0x78] instead of [rbx+0x60]/[rbx+0x88]. [V] per instruction quotes below.

```
0x6723971  mov ecx,[rbp+0x79C]                           
0x6723977  mov [rbp+0x2A0],ecx                           
0x672397d  mov [rbp+0x2A4],ax                            
0x6723984  lea rcx,[rbp+0x510]                           
0x672398b  lea rdx,[rbp+0x370]                           
0x6723992  call 0x67A75D0                                ; -> sub_67a75d0
0x6723997  nop                                           
0x6723998  lea rax,[rbp+0x2A0]                           
0x672399f  mov [rsp+0x28],rax                            
0x67239a4  lea rax,[rbp+0x2A4]                           
0x67239ab  mov [rsp+0x20],rax                            
0x67239b0  lea rcx,[rbp+0x560]                           
0x67239b7  lea rdx,[rbp+0x450]                           
0x67239be  lea r8,[rbp+0x3F8]                            
0x67239c5  lea r9,[rbp+0x370]                            
0x67239cc  call 0x6791F20                                ; -> sub_6791f20
0x67239d1  nop                                           
0x67239d2  mov eax,[rbx+0x60]                            
0x67239d5  lea rcx,[rbp+0x6A0]                           
0x67239dc  mov [rcx+0x10],eax                            
0x67239df  movups xmm0,[rbx+0x50]                        
0x67239e3  movups [rcx],xmm0                             
0x67239e6  movzx eax,byte ptr [rbp+0x4B4]                
0x67239ed  mov [rbp+0x6B4],al                            
0x67239f3  movups xmm0,[rbp+0x4B8]                       
0x67239fa  movups [rbp+0x6B8],xmm0                       
0x6723a01  movups xmm0,[rbx+0x78]                        
0x6723a05  movups xmm1,[rbx+0x88]                        
0x6723a0c  movups xmm2,[rbx+0x97]                        
0x6723a13  lea rax,[rbp+0x6C8]                           
0x6723a1a  movups [rax+0x1F],xmm2                        
0x6723a1e  movups [rax+0x10],xmm1                        
0x6723a22  movups [rax],xmm0                             
0x6723a25  movzx eax,word ptr [rbp+0x4F8]                
0x6723a2c  mov [rbp+0x6F8],ax                            
0x6723a33  mov rax,[rbp+0x808]                           
0x6723a3a  mov rcx,[rax+0x10]                            
0x6723a3e  mov eax,0x9D0                                 
0x6723a43  add rcx,rax                                   
0x6723a46  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x6723a4b  nop                                           
```

Interpretation: ecx = [rbp+0x79C], store at [rbp+0x2A0]; ax -> [rbp+0x2A4]. rcx = &[rbp+0x510], rdx = &[rbp+0x370], call 0x67A75D0(rcx,rdx). [rsp+0x28] = &[rbp+0x2A0], [rsp+0x20] = &[rbp+0x2A4]. rcx = &[rbp+0x560], rdx = &[rbp+0x450], r8 = &[rbp+0x3F8], r9 = &[rbp+0x370], call 0x6791F20. eax = [rbx+0x60]; rcx = &[rbp+0x6A0]; [rcx+0x10] = eax; xmm0 = [rbx+0x50] -> [rcx]. eax = byte [rbp+0x4B4] -> [rbp+0x6B4]. xmm0 = [rbp+0x4B8] -> [rbp+0x6B8]. xmm0 = [rbx+0x78], xmm1 = [rbx+0x88], xmm2 = [rbx+0x97] -> [rbp+0x6C8+0x1F]/[rbp+0x6C8+0x10]/[rbp+0x6C8]. eax = word [rbp+0x4F8] -> [rbp+0x6F8]. rax = [rbp+0x808], rcx = [rax+0x10], eax = 0x9D0, rcx += rax. Call 0x5ABA5C0.

Callees: 0x67A75D0 (sub_67a75d0), 0x6791F20 (sub_6791f20), 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x79C], [rbp+0x510], [rbp+0x370], [rbp+0x2A0], [rbp+0x2A4], [rbp+0x560], [rbp+0x450], [rbp+0x3F8], [rbx+0x60], [rbx+0x50], [rbp+0x4B4], [rbp+0x4B8], [rbx+0x78], [rbx+0x88], [rbx+0x97], [rbp+0x4F8], [rbp+0x808], [rax+0x10]. Fields written: [rbp+0x2A0], [rbp+0x2A4], [rsp+0x28], [rsp+0x20], [rbp+0x6A0+0x10], [rbp+0x6A0], [rbp+0x6B4], [rbp+0x6B8], [rbp+0x6C8+0x1F], [rbp+0x6C8+0x10], [rbp+0x6C8], [rbp+0x6F8].

---

## Phase 31 — result capture + zero + TLS call + word store + jump (0x6723a4c..0x6723ae0)

Mirrors H1 Phase 29 tail but r14 = result of 0x5ABA5C0 (not r15), and jumps to loc_6724b3a / loc_6724b4e (H1 jumped to 0x6724D3C/0x6724D50). [V] per instruction quotes below.

```
0x6723a4c  mov r14,rax                                   
0x6723a4f  movups [r13-0x28],xmm6                        
0x6723a54  movups [r13-0x38],xmm6                        
0x6723a59  movups [r13-0x48],xmm6                        
0x6723a5e  movups [r13-0x58],xmm6                        
0x6723a63  movups [r13-0x68],xmm6                        
0x6723a68  movups [r13-0x78],xmm6                        
0x6723a6d  movups [r13-0x88],xmm6                        
0x6723a75  movups [r13-0x98],xmm6                        
0x6723a7d  movups [r13-0xA8],xmm6                        
0x6723a85  movups [r13-0xB8],xmm6                        
0x6723a8d  movups [r13-0xC8],xmm6                        
0x6723a95  movups [r13-0xD8],xmm6                        
0x6723a9d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6723aa4  mov rax,[rcx]                                 
0x6723aa7  mov rax,[rax+0x10]                            
0x6723aab  mov dl,0x4A                                   
0x6723aad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6723ab3  nop                                           
0x6723ab4  mov [rbp+0x818],al                            
0x6723aba  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6723ac1  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6723ac8  je 0x6724B3A                                  ; -> loc_6724b3a
0x6723ace  movzx eax,word ptr [rbp+0x6F8]                
0x6723ad5  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x6723ad8  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6723ae0  jmp 0x6724B4E                                 ; -> loc_6724b4e
```

Interpretation: r14 = rax (result from 0x5ABA5C0). Zero xmm6 at [r13-0x28]..[r13-0xD8] (13 stores). rcx = [0x1233E1B0], rax = [rcx], rax = [rax+0x10], dl = 0x4A, call via [0xF99FFA0] (sub_eea6040), store al at [rbp+0x818]. rdx = [r14+0x8A8], cmp with [r14+0x8B0], if equal jump to 0x6724B3A. Otherwise: eax = word [rbp+0x6F8], store at [rdx], add qword [r14+0x8A8], 2, jmp 0x6724B4E.

Callees: [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [r13-0x28]..[r13-0xD8] (writes), [0x1233E1B0], [rcx], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x6F8]. Fields written: [rbp+0x818], [rdx] (word store), [r14+0x8A8].

---

## Phase 32 — [rsi+0x48] type check + xmm accumulate + call 0x67A75D0 (0x6723ae5..0x6723b1c)

Separate block reached by jump (fall-through target of the je at 0x6723af6 goes to loc_6723e41). If [rax]!=0xB jump to loc_6723e41; else store xmm15/xmm12 to [rbp+0x2A0]/[rbp+0x2A8] and call 0x67A75D0(&[rbp+0x510], r15). [V] per instruction quotes below.

```
0x6723ae5  mov rax,[rsi+0x48]                            
0x6723ae9  cmp qword ptr [rax],0xB                       
0x6723aed  addss xmm12,xmm13                             
0x6723af2  addps xmm15,xmm14                             
0x6723af6  jne 0x6723E41                                 ; -> loc_6723e41
0x6723afc  movlps [rbp+0x2A0],xmm15                      
0x6723b04  movss [rbp+0x2A8],xmm12                       
0x6723b0d  lea rcx,[rbp+0x510]                           
0x6723b14  mov rdx,r15                                   
0x6723b17  call 0x67A75D0                                ; -> sub_67a75d0
0x6723b1c  nop                                           
```

Interpretation: rax = [rsi+0x48]; if qword [rax] != 0xB jump to 0x6723E41. Otherwise addss xmm12,xmm13; addps xmm15,xmm14; movlps [rbp+0x2A0],xmm15; movss [rbp+0x2A8],xmm12. rcx = &[rbp+0x510], rdx = r15, call 0x67A75D0.

Callees: 0x67A75D0 (sub_67a75d0).
Fields read: [rsi+0x48], [rax], xmm12,xmm13,xmm15,xmm14, [rbp+0x510], r15. Fields written: [rbp+0x2A0], [rbp+0x2A8].

## Phase 33 — [rbp+0x2A0] arg setup + r13 field copy + call 0x67E23F0 (0x6723b1d..0x6723bb5)

Mirrors H1 Phase 28 tail but r13 is the source struct and rbx the destination (opposite direction vs H1's [rbx]->[rbp] copy). [V] per instruction quotes below.

```
0x6723b1d  lea rax,[rbp+0x2A0]                           
0x6723b24  mov [rsp+0x20],rax                            
0x6723b29  lea rdi,[rbp+0x370]                           
0x6723b30  mov rcx,rdi                                   
0x6723b33  lea rdx,[rbp+0x1F0]                           
0x6723b3a  lea r8,[rbp+0x198]                            
0x6723b41  mov r9,r15                                    
0x6723b44  call 0x678E1D0                                ; -> sub_678e1d0
0x6723b49  nop                                           
0x6723b4a  mov eax,[r13+0x60]                            
0x6723b4e  mov [rbx+0x70],eax                            
0x6723b51  movups xmm0,[r13+0x50]                        
0x6723b56  movups [rbx+0x60],xmm0                        
0x6723b5a  movzx eax,byte ptr [rbp+0x254]                
0x6723b61  mov [rbp+0x4C4],al                            
0x6723b67  movups xmm0,[rbp+0x258]                       
0x6723b6e  movups [rbp+0x4C8],xmm0                       
0x6723b75  movups xmm0,[r13+0x78]                        
0x6723b7a  movups xmm1,[r13+0x88]                        
0x6723b82  movups xmm2,[r13+0x97]                        
0x6723b8a  movups [rbx+0xA7],xmm2                        
0x6723b91  movups [rbx+0x98],xmm1                        
0x6723b98  movups [rbx+0x88],xmm0                        
0x6723b9f  movzx eax,word ptr [rbp+0x298]                
0x6723ba6  mov [rbp+0x508],ax                            
0x6723bad  mov rcx,r15                                   
0x6723bb0  call 0x67E23F0                                ; -> sub_67e23f0
0x6723bb5  nop                                           
```

Interpretation: [rsp+0x20] = &[rbp+0x2A0]. rdi = &[rbp+0x370]; rcx = rdi; rdx = &[rbp+0x1F0]; r8 = &[rbp+0x198]; r9 = r15; call 0x678E1D0. eax = [r13+0x60] -> [rbx+0x70]. xmm0 = [r13+0x50] -> [rbx+0x60]. eax = byte [rbp+0x254] -> [rbp+0x4C4]. xmm0 = [rbp+0x258] -> [rbp+0x4C8]. xmm0 = [r13+0x78], xmm1 = [r13+0x88], xmm2 = [r13+0x97] -> [rbx+0xA7]/[rbx+0x98]/[rbx+0x88]. eax = word [rbp+0x298] -> [rbp+0x508]. rcx = r15, call 0x67E23F0.

Callees: 0x678E1D0 (sub_678e1d0), 0x67E23F0 (sub_67e23f0).
Fields read: [rbp+0x2A0], [rbp+0x370], [rbp+0x1F0], [rbp+0x198], r15, [r13+0x60], [r13+0x50], [rbp+0x254], [rbp+0x258], [r13+0x78], [r13+0x88], [r13+0x97], [rbp+0x298]. Fields written: [rsp+0x20], [rbx+0x70], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0xA7], [rbx+0x98], [rbx+0x88], [rbp+0x508].

## Phase 34 — [rsp+0x20]=rdi + call 0x678E420 (0x6723bb6..0x6723bdc)

```
0x6723bb6  mov [rsp+0x20],rdi                            
0x6723bbb  lea rcx,[rbp+0x560]                           
0x6723bc2  lea rdx,[rbp+0x460]                           
0x6723bc9  lea r8,[rbp+0x408]                            
0x6723bd0  lea r9,[rbp+0x380]                            
0x6723bd7  call 0x678E420                                ; -> sub_678e420
0x6723bdc  nop                                           
```

Interpretation: [rsp+0x20] = rdi. rcx = &[rbp+0x560], rdx = &[rbp+0x460], r8 = &[rbp+0x408], r9 = &[rbp+0x380], call 0x678E420.

Callees: 0x678E420 (sub_678e420).
Fields read: rdi, [rbp+0x560], [rbp+0x460], [rbp+0x408], [rbp+0x380]. Fields written: [rsp+0x20].

---

## Phase 35 — rbx field copy + call 0x5ABA5C0 (0x6723bdd..0x6723c59)

Mirrors Phase 30's copy block but reads from rbx and writes to [rbp+0x6A0..], word stored at [rbp+0x6F8]. [V] per instruction quotes below.

```
0x6723bdd  mov eax,[rbx+0x70]                            
0x6723be0  lea rcx,[rbp+0x6A0]                           
0x6723be7  mov [rcx+0x10],eax                            
0x6723bea  movups xmm0,[rbx+0x60]                        
0x6723bee  movups [rcx],xmm0                             
0x6723bf1  movzx eax,byte ptr [rbp+0x4C4]                
0x6723bf8  mov [rbp+0x6B4],al                            
0x6723bfe  movups xmm0,[rbp+0x4C8]                       
0x6723c05  movups [rbp+0x6B8],xmm0                       
0x6723c0c  movups xmm0,[rbx+0x88]                        
0x6723c13  movups xmm1,[rbx+0x98]                        
0x6723c1a  movups xmm2,[rbx+0xA7]                        
0x6723c21  lea rax,[rbp+0x6C8]                           
0x6723c28  movups [rax+0x1F],xmm2                        
0x6723c2c  movups [rax+0x10],xmm1                        
0x6723c30  movups [rax],xmm0                             
0x6723c33  movzx eax,word ptr [rbp+0x508]                
0x6723c3a  mov [rbp+0x6F8],ax                            
0x6723c41  mov rax,[rbp+0x808]                           
0x6723c48  mov rcx,[rax+0x10]                            
0x6723c4c  mov eax,0x9D0                                 
0x6723c51  add rcx,rax                                   
0x6723c54  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x6723c59  nop                                           
```

Interpretation: eax = [rbx+0x70]; rcx = &[rbp+0x6A0]; [rcx+0x10] = eax; xmm0 = [rbx+0x60] -> [rcx]. eax = byte [rbp+0x4C4] -> [rbp+0x6B4]. xmm0 = [rbp+0x4C8] -> [rbp+0x6B8]. xmm0 = [rbx+0x88], xmm1 = [rbx+0x98], xmm2 = [rbx+0xA7] -> [rbp+0x6C8+0x1F]/[rbp+0x6C8+0x10]/[rbp+0x6C8]. eax = word [rbp+0x508] -> [rbp+0x6F8]. rax = [rbp+0x808], rcx = [rax+0x10], eax = 0x9D0, rcx += rax. Call 0x5ABA5C0.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbx+0x70], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0x88], [rbx+0x98], [rbx+0xA7], [rbp+0x508], [rbp+0x808], [rax+0x10]. Fields written: [rbp+0x6A0+0x10], [rbp+0x6A0], [rbp+0x6B4], [rbp+0x6B8], [rbp+0x6C8+0x1F], [rbp+0x6C8+0x10], [rbp+0x6C8], [rbp+0x6F8].

## Phase 36 — r14 capture + zero + TLS call + word store + jump (0x6723c5a..0x6723cee)

Mirrors Phase 31 but jumps to loc_6727262 / loc_6727276 (sub_6727262 / sub_6727276) instead of 0x6724B3A/0x6724B4E. [V] per instruction quotes below.

```
0x6723c5a  mov r14,rax                                   
0x6723c5d  movups [r13-0x28],xmm6                        
0x6723c62  movups [r13-0x38],xmm6                        
0x6723c67  movups [r13-0x48],xmm6                        
0x6723c6c  movups [r13-0x58],xmm6                        
0x6723c71  movups [r13-0x68],xmm6                        
0x6723c76  movups [r13-0x78],xmm6                        
0x6723c7b  movups [r13-0x88],xmm6                        
0x6723c83  movups [r13-0x98],xmm6                        
0x6723c8b  movups [r13-0xA8],xmm6                        
0x6723c93  movups [r13-0xB8],xmm6                        
0x6723c9b  movups [r13-0xC8],xmm6                        
0x6723ca3  movups [r13-0xD8],xmm6                        
0x6723cab  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6723cb2  mov rax,[rcx]                                 
0x6723cb5  mov rax,[rax+0x10]                            
0x6723cb9  mov dl,0x4A                                   
0x6723cbb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6723cc1  nop                                           
0x6723cc2  mov [rbp+0x818],al                            
0x6723cc8  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6723ccf  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6723cd6  je 0x6727262                                  ; -> sub_6727262
0x6723cdc  movzx eax,word ptr [rbp+0x6F8]                
0x6723ce3  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x6723ce6  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6723cee  jmp 0x6727276                                 ; -> sub_6727276
```

Interpretation: r14 = rax (result from 0x5ABA5C0). Zero xmm6 at [r13-0x28]..[r13-0xD8] (13 stores). rcx = [0x1233E1B0], rax = [rcx], rax = [rax+0x10], dl = 0x4A, call via [0xF99FFA0] (sub_eea6040), store al at [rbp+0x818]. rdx = [r14+0x8A8], cmp with [r14+0x8B0], if equal jump to 0x6727262. Otherwise: eax = word [rbp+0x6F8], store at [rdx], add qword [r14+0x8A8], 2, jmp 0x6727276.

Callees: [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [r13-0x28]..[r13-0xD8] (writes), [0x1233E1B0], [rcx], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x6F8]. Fields written: [rbp+0x818], [rdx] (word store), [r14+0x8A8].

---

## Phase 37 — [r12+0x50] low-bits check + sub_678F640 call (0x6723cf3..0x6723d47)

eax = [r12+0x50]; ecx = ~eax; if (cl & 3) != 0 jump loc_6723fe4. If byte [rbp+0x816]==0 jump sub_6726DBE. Else call 0x67A75D0(&[rbp+0x510],&[rbp+0x370]) then call 0x678F640(&[rbp+0x560],&[rbp+0x450],&[rbp+0x3F8],&[rbp+0x370]). [V] per instruction quotes below.

```
0x6723cf3  mov eax,[r12+0x50]                            
0x6723cf8  mov ecx,eax                                   
0x6723cfa  not ecx                                       
0x6723cfc  test cl,3                                     
0x6723cff  jne 0x6723FE4                                 ; -> loc_6723fe4
0x6723d05  cmp byte ptr [rbp+0x816],0                    
0x6723d0c  je 0x6726DBE                                  ; -> sub_6726dbe
0x6723d12  lea rcx,[rbp+0x510]                           
0x6723d19  lea rdx,[rbp+0x370]                           
0x6723d20  call 0x67A75D0                                ; -> sub_67a75d0
0x6723d25  nop                                           
0x6723d26  lea rcx,[rbp+0x560]                           
0x6723d2d  lea rdx,[rbp+0x450]                           
0x6723d34  lea r8,[rbp+0x3F8]                            
0x6723d3b  lea r9,[rbp+0x370]                            
0x6723d42  call 0x678F640                                ; -> sub_678f640
0x6723d47  nop                                           
```

Interpretation: eax = [r12+0x50]; ecx = ~eax; test cl,3; if nonzero jne 0x6723FE4. cmp byte [rbp+0x816],0; if equal je 0x6726DBE. rcx = &[rbp+0x510], rdx = &[rbp+0x370], call 0x67A75D0. rcx = &[rbp+0x560], rdx = &[rbp+0x450], r8 = &[rbp+0x3F8], r9 = &[rbp+0x370], call 0x678F640.

Callees: 0x67A75D0 (sub_67a75d0), 0x678F640 (sub_678f640).
Fields read: [r12+0x50], [rbp+0x816], [rbp+0x510], [rbp+0x370], [rbp+0x560], [rbp+0x450], [rbp+0x3F8]. Fields written: none (stack args only).

## Phase 38 — rbx field copy to [rbp+0x698..] + [rbp+0x748] range count (0x6723d48..0x6723e07)

eax=[rbx+0x60] -> [rbp+0x698+0x10]; xmm0=[rbx+0x50]->[rbp+0x698]; byte [rbp+0x4B4]->[rbp+0x6AC]; xmm0=[rbp+0x4B8]->[rbp+0x6B0]; xmm0-xmm2=[rbx+0x78/0x88/0x97]->[rbp+0x564+0x17B/0x16C/0x15C]; word [rbp+0x4F8]->[rbp+0x6F0]. Then rcx=[rbp+0x748]; rax=[rcx+0x480]; rdx=[rcx+0x488]; rcx = rdx - rax; if rcx == -0x30 (0xFFFFFFFFFFFFFFD0) jump sub_672a30f; if rax==0 or rdx==0 jump sub_672a30f; else rcx = rcx/16 (via *0xAAAA...AB magic) -> [rbp+0xE0], rax -> [rbp+0xE8]. [V] per instruction quotes below.

```
0x6723d48  mov eax,[rbx+0x60]                            
0x6723d4b  lea rcx,[rbp+0x698]                           
0x6723d52  mov [rcx+0x10],eax                            
0x6723d55  movups xmm0,[rbx+0x50]                        
0x6723d59  movups [rcx],xmm0                             
0x6723d5c  movzx eax,byte ptr [rbp+0x4B4]                
0x6723d63  mov [rbp+0x6AC],al                            
0x6723d69  movups xmm0,[rbp+0x4B8]                       
0x6723d70  movups [rbp+0x6B0],xmm0                       
0x6723d77  movups xmm0,[rbx+0x78]                        
0x6723d7b  movups xmm1,[rbx+0x88]                        
0x6723d82  movups xmm2,[rbx+0x97]                        
0x6723d89  lea rax,[rbp+0x564]                           
0x6723d90  movups [rax+0x17B],xmm2                       
0x6723d97  movups [rax+0x16C],xmm1                       
0x6723d9e  movups [rax+0x15C],xmm0                       
0x6723da5  movzx eax,word ptr [rbp+0x4F8]                
0x6723dac  mov [rbp+0x6F0],ax                            
0x6723db3  mov rcx,[rbp+0x748]                           
0x6723dba  mov rax,[rcx+0x480]                           
0x6723dc1  mov rdx,[rcx+0x488]                           
0x6723dc8  mov rcx,rdx                                   
0x6723dcb  sub rcx,rax                                   
0x6723dce  cmp rcx,0xFFFFFFFFFFFFFFD0                    
0x6723dd2  je 0x672A30F                                  ; -> sub_672a30f
0x6723dd8  test rax,rax                                  
0x6723ddb  setne r8b                                     
0x6723ddf  test rdx,rdx                                  
0x6723de2  sete dl                                       
0x6723de5  or dl,r8b                                     
0x6723de8  je 0x672A30F                                  ; -> sub_672a30f
0x6723dee  sar rcx,4                                     
0x6723df2  mov rdx,0xAAAAAAAAAAAAAAAB                    
0x6723dfc  imul rcx,rdx                                  
0x6723e00  mov [rbp+0xE0],rcx                            
0x6723e07  mov [rbp+0xE8],rax                            
```

Interpretation: eax = [rbx+0x60]; rcx = &[rbp+0x698]; [rcx+0x10] = eax; xmm0 = [rbx+0x50] -> [rcx]. eax = byte [rbp+0x4B4] -> [rbp+0x6AC]. xmm0 = [rbp+0x4B8] -> [rbp+0x6B0]. xmm0 = [rbx+0x78], xmm1 = [rbx+0x88], xmm2 = [rbx+0x97] -> [rbp+0x564+0x17B]/[rbp+0x564+0x16C]/[rbp+0x564+0x15C]. eax = word [rbp+0x4F8] -> [rbp+0x6F0]. rcx = [rbp+0x748]; rax = [rcx+0x480]; rdx = [rcx+0x488]; rcx = rdx - rax; if rcx == -0x30 jump 0x672A30F; test rax,rax / test rdx,rdx; if either zero jump 0x672A30F. rcx >>= 4 (sar rcx,4), then magic-multiply by 0xAAAAAAAAAAAAAAAB (unsigned divide by 16) -> [rbp+0xE0]; rax -> [rbp+0xE8].

Callees: none direct (jumps to sub_672a30f).
Fields read: [rbx+0x60], [rbx+0x50], [rbp+0x4B4], [rbp+0x4B8], [rbx+0x78], [rbx+0x88], [rbx+0x97], [rbp+0x4F8], [rbp+0x748], [rcx+0x480], [rcx+0x488]. Fields written: [rbp+0x698+0x10], [rbp+0x698], [rbp+0x6AC], [rbp+0x6B0], [rbp+0x564+0x17B], [rbp+0x564+0x16C], [rbp+0x564+0x15C], [rbp+0x6F0], [rbp+0xE0], [rbp+0xE8].

## Phase 39 — sub_67E4280 call + jump (0x6723e0e..0x6723e3c)

rdi = &[rbp+0x560]; [rsp+0x20] = rdi; rcx = [rbp+0x808]; rdx = &[rbp+0xE0]; r8 = [rbp+0x758]; r9 = &[rbp+0x530]; call 0x67E4280; jmp 0x672724E. [V] per instruction quotes below.

```
0x6723e0e  lea rdi,[rbp+0x560]                           
0x6723e15  mov [rsp+0x20],rdi                            
0x6723e1a  mov rcx,[rbp+0x808]                           
0x6723e21  lea rdx,[rbp+0xE0]                            
0x6723e28  mov r8,[rbp+0x758]                            
0x6723e2f  lea r9,[rbp+0x530]                            
0x6723e36  call 0x67E4280                                ; -> sub_67e4280
0x6723e3b  nop                                           
0x6723e3c  jmp 0x672724E                                 ; -> sub_672724e
```

Interpretation: rdi = &[rbp+0x560]; [rsp+0x20] = rdi. rcx = [rbp+0x808]; rdx = &[rbp+0xE0]; r8 = [rbp+0x758]; r9 = &[rbp+0x530]; call 0x67E4280(rcx,rdx,r8,r9). jmp 0x672724E.

Callees: 0x67E4280 (sub_67e4280).
Fields read: [rbp+0x560], [rbp+0x808], [rbp+0xE0], [rbp+0x758], [rbp+0x530]. Fields written: [rsp+0x20].

---

## Phase 40 — xmm15/xmm12 store + call 0x67A75D0 + call 0x678E1D0 (0x6723e41..0x6723e8e)

jne target from 0x6723af6 (when [rax]!=0xB). Stores xmm15/xmm12 to [rbp+0x2A0]/[rbp+0x2A8], then calls 0x67A75D0(&[rbp+0x510],r15) and 0x678E1D0(&[rbp+0x370], &[rbp+0x1F0], &[rbp+0x198], r15). [V] per instruction quotes below.

```
0x6723e41  movlps [rbp+0x2A0],xmm15                      
0x6723e49  movss [rbp+0x2A8],xmm12                       
0x6723e52  lea rcx,[rbp+0x510]                           
0x6723e59  mov rdx,r15                                   
0x6723e5c  call 0x67A75D0                                ; -> sub_67a75d0
0x6723e61  nop                                           
0x6723e62  lea rax,[rbp+0x2A0]                           
0x6723e69  mov [rsp+0x20],rax                            
0x6723e6e  lea rdi,[rbp+0x370]                           
0x6723e75  mov rcx,rdi                                   
0x6723e78  lea rdx,[rbp+0x1F0]                           
0x6723e7f  lea r8,[rbp+0x198]                            
0x6723e86  mov r9,r15                                    
0x6723e89  call 0x678E1D0                                ; -> sub_678e1d0
0x6723e8e  nop                                           
```

Interpretation: movlps [rbp+0x2A0],xmm15; movss [rbp+0x2A8],xmm12. rcx = &[rbp+0x510], rdx = r15, call 0x67A75D0. [rsp+0x20] = &[rbp+0x2A0]. rdi = &[rbp+0x370]; rcx = rdi; rdx = &[rbp+0x1F0]; r8 = &[rbp+0x198]; r9 = r15; call 0x678E1D0.

Callees: 0x67A75D0 (sub_67a75d0), 0x678E1D0 (sub_678e1d0).
Fields read: xmm15, xmm12, [rbp+0x510], r15, [rbp+0x2A0], [rbp+0x370], [rbp+0x1F0], [rbp+0x198]. Fields written: [rbp+0x2A0], [rbp+0x2A8], [rsp+0x20].

## Phase 41 — r13 field copy + call 0x67E23F0 + call 0x678E420 (0x6723e8f..0x6723f21)

Mirrors Phase 33/35 rbx/r13 copy pattern. eax=[r13+0x60]->[rbx+0x70]; xmm0=[r13+0x50]->[rbx+0x60]; byte [rbp+0x254]->[rbp+0x4C4]; xmm0=[rbp+0x258]->[rbp+0x4C8]; xmm0-xmm2=[r13+0x78/0x88/0x97]->[rbx+0xA7/0x98/0x88]; word [rbp+0x298]->[rbp+0x508]; rcx=r15 call 0x67E23F0; then [rsp+0x20]=rdi; call 0x678E420(&[rbp+0x560],&[rbp+0x460],&[rbp+0x408],&[rbp+0x380]). [V] per instruction quotes below.

```
0x6723e8f  mov eax,[r13+0x60]                            
0x6723e93  mov [rbx+0x70],eax                            
0x6723e96  movups xmm0,[r13+0x50]                        
0x6723e9b  movups [rbx+0x60],xmm0                        
0x6723e9f  movzx eax,byte ptr [rbp+0x254]                
0x6723ea6  mov [rbp+0x4C4],al                            
0x6723eac  movups xmm0,[rbp+0x258]                       
0x6723eb3  movups [rbp+0x4C8],xmm0                       
0x6723eba  movups xmm0,[r13+0x78]                        
0x6723ebf  movups xmm1,[r13+0x88]                        
0x6723ec7  movups xmm2,[r13+0x97]                        
0x6723ecf  movups [rbx+0xA7],xmm2                        
0x6723ed6  movups [rbx+0x98],xmm1                        
0x6723edd  movups [rbx+0x88],xmm0                        
0x6723ee4  movzx eax,word ptr [rbp+0x298]                
0x6723eeb  mov [rbp+0x508],ax                            
0x6723ef2  mov rcx,r15                                   
0x6723ef5  call 0x67E23F0                                ; -> sub_67e23f0
0x6723efa  nop                                           
0x6723efb  mov [rsp+0x20],rdi                            
0x6723f00  lea rcx,[rbp+0x560]                           
0x6723f07  lea rdx,[rbp+0x460]                           
0x6723f0e  lea r8,[rbp+0x408]                            
0x6723f15  lea r9,[rbp+0x380]                            
0x6723f1c  call 0x678E420                                ; -> sub_678e420
0x6723f21  nop                                           
```

Interpretation: eax = [r13+0x60] -> [rbx+0x70]. xmm0 = [r13+0x50] -> [rbx+0x60]. eax = byte [rbp+0x254] -> [rbp+0x4C4]. xmm0 = [rbp+0x258] -> [rbp+0x4C8]. xmm0 = [r13+0x78], xmm1 = [r13+0x88], xmm2 = [r13+0x97] -> [rbx+0xA7]/[rbx+0x98]/[rbx+0x88]. eax = word [rbp+0x298] -> [rbp+0x508]. rcx = r15, call 0x67E23F0. [rsp+0x20] = rdi. rcx = &[rbp+0x560], rdx = &[rbp+0x460], r8 = &[rbp+0x408], r9 = &[rbp+0x380], call 0x678E420.

Callees: 0x67E23F0 (sub_67e23f0), 0x678E420 (sub_678e420).
Fields read: [r13+0x60], [r13+0x50], [rbp+0x254], [rbp+0x258], [r13+0x78], [r13+0x88], [r13+0x97], [rbp+0x298], r15, rdi, [rbp+0x560], [rbp+0x460], [rbp+0x408], [rbp+0x380]. Fields written: [rbx+0x70], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0xA7], [rbx+0x98], [rbx+0x88], [rbp+0x508], [rsp+0x20].

---

## Phase 42 — rbx field copy + sub_67E1990 + sub_67E1660 + jump (0x6723f22..0x6723fdf)

eax=[rbx+0x70]->[rbp+0x6A0+0x10]; xmm0=[rbx+0x60]->[rbp+0x6A0]; byte [rbp+0x4C4]->[rbp+0x6B4]; xmm0=[rbp+0x4C8]->[rbp+0x6B8]; xmm0-xmm2=[rbx+0x88/0x98/0xA7]->[rbp+0x6C8+0x1F/0x10/0]; word [rbp+0x508]->[rbp+0x6F8]. rax=[rbp+0x808]; rcx=[rax+0x10]; rcx+=0x9D0. [rsp+0x30]=&[rbp+0x564]; [rsp+0x28]=&[rbp+0x570]; [rsp+0x20]=&[rbp+0x5F8]; rdx=&[rbp+0x6F8]; r9=&[rbp+0x650]; call 0x67E1990; lea rcx=&[rbp+0x560]; call 0x67E1660; jmp 0x6727750. [V] per instruction quotes below.

```
0x6723f22  mov eax,[rbx+0x70]                            
0x6723f25  lea r8,[rbp+0x6A0]                            
0x6723f2c  mov [r8+0x10],eax                             
0x6723f30  movups xmm0,[rbx+0x60]                        
0x6723f34  movups [r8],xmm0                              
0x6723f38  movzx eax,byte ptr [rbp+0x4C4]                
0x6723f3f  mov [rbp+0x6B4],al                            
0x6723f45  movups xmm0,[rbp+0x4C8]                       
0x6723f4c  movups [rbp+0x6B8],xmm0                       
0x6723f53  movups xmm0,[rbx+0x88]                        
0x6723f5a  movups xmm1,[rbx+0x98]                        
0x6723f61  movups xmm2,[rbx+0xA7]                        
0x6723f68  lea rax,[rbp+0x6C8]                           
0x6723f6f  movups [rax+0x1F],xmm2                        
0x6723f73  movups [rax+0x10],xmm1                        
0x6723f77  movups [rax],xmm0                             
0x6723f7a  movzx eax,word ptr [rbp+0x508]                
0x6723f81  mov [rbp+0x6F8],ax                            
0x6723f88  mov rax,[rbp+0x808]                           
0x6723f8f  mov rcx,[rax+0x10]                            
0x6723f93  mov eax,0x9D0                                 
0x6723f98  add rcx,rax                                   
0x6723f9b  lea rax,[rbp+0x564]                           
0x6723fa2  mov [rsp+0x30],rax                            
0x6723fa7  lea rax,[rbp+0x570]                           
0x6723fae  mov [rsp+0x28],rax                            
0x6723fb3  lea rax,[rbp+0x5F8]                           
0x6723fba  mov [rsp+0x20],rax                            
0x6723fbf  lea rdx,[rbp+0x6F8]                           
0x6723fc6  lea r9,[rbp+0x650]                            
0x6723fcd  call 0x67E1990                                ; -> sub_67e1990
0x6723fd2  nop                                           
0x6723fd3  lea rcx,[rbp+0x560]                           
0x6723fda  call 0x67E1660                                ; -> sub_67e1660
0x6723fdf  jmp 0x6727750                                 ; -> sub_6727750
```

Interpretation: eax = [rbx+0x70]; r8 = &[rbp+0x6A0]; [r8+0x10] = eax; xmm0 = [rbx+0x60] -> [r8]. eax = byte [rbp+0x4C4] -> [rbp+0x6B4]. xmm0 = [rbp+0x4C8] -> [rbp+0x6B8]. xmm0 = [rbx+0x88], xmm1 = [rbx+0x98], xmm2 = [rbx+0xA7] -> [rbp+0x6C8+0x1F]/[rbp+0x6C8+0x10]/[rbp+0x6C8]. eax = word [rbp+0x508] -> [rbp+0x6F8]. rax = [rbp+0x808], rcx = [rax+0x10], eax = 0x9D0, rcx += rax. [rsp+0x30] = &[rbp+0x564]; [rsp+0x28] = &[rbp+0x570]; [rsp+0x20] = &[rbp+0x5F8]. rdx = &[rbp+0x6F8], r9 = &[rbp+0x650], call 0x67E1990. lea rcx = &[rbp+0x560], call 0x67E1660. jmp 0x6727750.

Callees: 0x67E1990 (sub_67e1990), 0x67E1660 (sub_67e1660).
Fields read: [rbx+0x70], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0x88], [rbx+0x98], [rbx+0xA7], [rbp+0x508], [rbp+0x808], [rax+0x10], [rbp+0x564], [rbp+0x570], [rbp+0x5F8], [rbp+0x6F8], [rbp+0x650], [rbp+0x560]. Fields written: [rbp+0x6A0+0x10], [rbp+0x6A0], [rbp+0x6B4], [rbp+0x6B8], [rbp+0x6C8+0x1F], [rbp+0x6C8+0x10], [rbp+0x6C8], [rbp+0x6F8], [rsp+0x30], [rsp+0x28], [rsp+0x20].

---

## Phase 43 — al bit tests + sub_67A75D0 + sub_678F640 (0x6723fe4..0x672402e)

jne target from 0x6723cff (when (cl&3)!=0). test al,2 -> jne sub_6727128; test al,1 -> je sub_672775C; cmp byte [rbp+0x816],0 -> je sub_672776E; else call 0x67A75D0(&[rbp+0x510],r15) then call 0x678F640(&[rbp+0x370],&[rbp+0x1F0],&[rbp+0x198],r15). [V] per instruction quotes below.

```
0x6723fe4  test al,2                                     
0x6723fe6  jne 0x6727128                                 ; -> sub_6727128
0x6723fec  test al,1                                     
0x6723fee  je 0x672775C                                  ; -> sub_672775c
0x6723ff4  cmp byte ptr [rbp+0x816],0                    
0x6723ffb  je 0x672776E                                  ; -> sub_672776e
0x6724001  lea rcx,[rbp+0x510]                           
0x6724008  mov rdx,r15                                   
0x672400b  call 0x67A75D0                                ; -> sub_67a75d0
0x6724010  nop                                           
0x6724011  lea rcx,[rbp+0x370]                           
0x6724018  lea rdx,[rbp+0x1F0]                           
0x672401f  lea r8,[rbp+0x198]                            
0x6724026  mov r9,r15                                    
0x6724029  call 0x678F640                                ; -> sub_678f640
0x672402e  nop                                           
```

Interpretation: test al,2; if nonzero jne 0x6727128. test al,1; if zero je 0x672775C. cmp byte [rbp+0x816],0; if zero je 0x672776E. rcx = &[rbp+0x510], rdx = r15, call 0x67A75D0. rcx = &[rbp+0x370], rdx = &[rbp+0x1F0], r8 = &[rbp+0x198], r9 = r15, call 0x678F640.

Callees: 0x67A75D0 (sub_67a75d0), 0x678F640 (sub_678f640).
Fields read: al, [rbp+0x816], [rbp+0x510], r15, [rbp+0x370], [rbp+0x1F0], [rbp+0x198]. Fields written: none (stack args only).

## Phase 44 — [r13+0x60] copy to [rbp+0x4A8..] + range bounds check (0x672402f..0x67240e7)

eax=[r13+0x60]->[rbp+0x4A8+0x10]; xmm0=[r13+0x50]->[rbp+0x4A8]; byte [rbp+0x254]->[rbp+0x4BC]; xmm0=[rbp+0x258]->[rbp+0x4C0]; xmm0-xmm2=[r13+0x78/0x88/0x97]->[rbx+0x9F/0x90/0x80]; word [rbp+0x298]->[rbp+0x500]. Then rcx=[rbp+0x748]; r8=[rax+0x480]; rax=[rax+0x488]; rdx=rax; rdx-=r8; if rdx==-0x30 jump sub_672a30f; if r8==0 or rax==0 jump sub_672a30f; if rax==r8 jump sub_6729489; if qword [rbp+0x758]==0 jump sub_6729489. [V] per instruction quotes below.

```
0x672402f  mov eax,[r13+0x60]                            
0x6724033  lea rcx,[rbp+0x4A8]                           
0x672403a  mov [rcx+0x10],eax                            
0x672403d  movups xmm0,[r13+0x50]                        
0x6724042  movups [rcx],xmm0                             
0x6724045  movzx eax,byte ptr [rbp+0x254]                
0x672404c  mov [rbp+0x4BC],al                            
0x6724052  movups xmm0,[rbp+0x258]                       
0x6724059  movups [rbp+0x4C0],xmm0                       
0x6724060  movups xmm0,[r13+0x78]                        
0x6724065  movups xmm1,[r13+0x88]                        
0x672406d  movups xmm2,[r13+0x97]                        
0x6724075  movups [rbx+0x9F],xmm2                        
0x672407c  movups [rbx+0x90],xmm1                        
0x6724083  movups [rbx+0x80],xmm0                        
0x672408a  movzx eax,word ptr [rbp+0x298]                
0x6724091  mov [rbp+0x500],ax                            
0x6724098  mov rax,[rbp+0x748]                           
0x672409f  mov r8,[rax+0x480]                            
0x67240a6  mov rax,[rax+0x488]                           
0x67240ad  mov rdx,rax                                   
0x67240b0  sub rdx,r8                                    
0x67240b3  cmp rdx,0xFFFFFFFFFFFFFFD0                    
0x67240b7  je 0x672A30F                                  ; -> sub_672a30f
0x67240bd  test r8,r8                                    
0x67240c0  setne cl                                      
0x67240c3  test rax,rax                                  
0x67240c6  sete r9b                                      
0x67240ca  or r9b,cl                                     
0x67240cd  je 0x672A30F                                  ; -> sub_672a30f
0x67240d3  cmp rax,r8                                    
0x67240d6  je 0x6729489                                  ; -> sub_6729489
0x67240dc  mov rax,[rbp+0x758]                           
0x67240e3  cmp qword ptr [rax],0                         
0x67240e7  je 0x6729489                                  ; -> sub_6729489
```

Interpretation: eax = [r13+0x60]; rcx = &[rbp+0x4A8]; [rcx+0x10] = eax; xmm0 = [r13+0x50] -> [rcx]. eax = byte [rbp+0x254] -> [rbp+0x4BC]. xmm0 = [rbp+0x258] -> [rbp+0x4C0]. xmm0 = [r13+0x78], xmm1 = [r13+0x88], xmm2 = [r13+0x97] -> [rbx+0x9F]/[rbx+0x90]/[rbx+0x80]. eax = word [rbp+0x298] -> [rbp+0x500]. rax = [rbp+0x748]; r8 = [rax+0x480]; rax = [rax+0x488]; rdx = rax; rdx -= r8; if rdx == -0x30 jump 0x672A30F. test r8,r8 -> setne cl; test rax,rax -> sete r9b; or r9b,cl; if zero jump 0x672A30F. cmp rax,r8; if equal jump 0x6729489. rax = [rbp+0x758]; if qword [rax] == 0 jump 0x6729489.

Callees: none direct (jumps to sub_672a30f / sub_6729489).
Fields read: [r13+0x60], [r13+0x50], [rbp+0x254], [rbp+0x258], [r13+0x78], [r13+0x88], [r13+0x97], [rbp+0x298], [rbp+0x748], [rax+0x480], [rax+0x488], r8, rax, [rbp+0x758], [rax]. Fields written: [rbp+0x4A8+0x10], [rbp+0x4A8], [rbp+0x4BC], [rbp+0x4C0], [rbx+0x9F], [rbx+0x90], [rbx+0x80], [rbp+0x500].

---

## Phase 45 — rdx/16 magic divide + sub_6769EE0 call (0x67240ed..0x672411a)

sar rdx,4; rdx = rdx * 0xAAAAAAAAAAAAAAAB (high bits = rdx/16 unsigned); mov dword [rsp+0x20], 0x41800000 (float 3.5f); rcx=&[rbp+0x7E0]; r9=&[rbp+0x530]; call 0x6769EE0. [V] per instruction quotes below.

```
0x67240ed  sar rdx,4                                     
0x67240f1  mov rax,0xAAAAAAAAAAAAAAAB                    
0x67240fb  imul rdx,rax                                  
0x67240ff  mov dword ptr [rsp+0x20],0x41800000           
0x6724107  lea rcx,[rbp+0x7E0]                           
0x672410e  lea r9,[rbp+0x530]                            
0x6724115  call 0x6769EE0                                ; -> sub_6769ee0
0x672411a  nop                                           
```

Interpretation: sar rdx,4 (rdx >>= 4); mov rax,0xAAAAAAAAAAAAAAAB; imul rdx,rax (unsigned 64x64->128, rdx = high 64 = rdx_orig/16). mov dword [rsp+0x20], 0x41800000. lea rcx = &[rbp+0x7E0]; lea r9 = &[rbp+0x530]; call 0x6769EE0.

Callees: 0x6769EE0 (sub_6769ee0).
Fields read: rdx, [rsp+0x20], [rbp+0x7E0], [rbp+0x530]. Fields written: [rsp+0x20].

## Phase 46 — result unpack + virtual call + bounds checks + loop setup (0x672411b..0x67241ca)

rax=[rbp+0x7E0]; rcx=[rbp+0x7E8]; r14=rax; [rbp+0x818]=rax; [rbp+0x558]=rcx; if rax==rcx jump sub_67293F6. rax=[rbp+0x758]; rcx=[rax]; rax=[rcx]; rax=[rax+0x48]; rdx=&[rbp+0x2A0]; call via [0xF99FFA0] (sub_eea6040). r14=[rbp+0x7E0]; rdi=[rbp+0x7E8]; rax=rdi-r14; if rax==-0x20 jump sub_672a30f; bounds checks (r14/rdi nonzero, rdi>r14) else jump sub_672a30f. [rbp+0x7A0]=&[rbp+0x7B0]; [rbp+0x7A8]=0x100000000; if rdi==r14 jump loc_67241f0 else fall to loc_67241d0 loop. [V] per instruction quotes below.

```
0x672411b  mov rax,[rbp+0x7E0]                           
0x6724122  mov rcx,[rbp+0x7E8]                           
0x6724129  mov r14,rax                                   
0x672412c  mov [rbp+0x818],rax                           
0x6724133  mov [rbp+0x558],rcx                           
0x672413a  cmp rax,rcx                                   
0x672413d  je 0x67293F6                                  ; -> sub_67293f6
0x6724143  mov rax,[rbp+0x758]                           
0x672414a  mov rcx,[rax]                                 
0x672414d  mov rax,[rcx]                                 
0x6724150  mov rax,[rax+0x48]                            
0x6724154  lea rdx,[rbp+0x2A0]                           
0x672415b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6724161  nop                                           
0x6724162  mov r14,[rbp+0x7E0]                           
0x6724169  mov rdi,[rbp+0x7E8]                           
0x6724170  mov rax,rdi                                   
0x6724173  sub rax,r14                                   
0x6724176  cmp rax,0xFFFFFFFFFFFFFFE0                    
0x672417a  je 0x672A30F                                  ; -> sub_672a30f
0x6724180  test r14,r14                                  
0x6724183  setne al                                      
0x6724186  test rdi,rdi                                  
0x6724189  sete cl                                       
0x672418c  or cl,al                                      
0x672418e  je 0x672A30F                                  ; -> sub_672a30f
0x6724194  test r14,r14                                  
0x6724197  setne al                                      
0x672419a  cmp rdi,r14                                   
0x672419d  sete cl                                       
0x67241a0  or cl,al                                      
0x67241a2  je 0x672A30F                                  ; -> sub_672a30f
0x67241a8  lea rax,[rbp+0x7B0]                           
0x67241af  mov [rbp+0x7A0],rax                           
0x67241b6  mov rax,0x100000000                           
0x67241c0  mov [rbp+0x7A8],rax                           
0x67241c7  cmp rdi,r14                                   
0x67241ca  je short 0x67241F0                            ; -> loc_67241f0
0x67241cc  nop [rax]                                     
```

Interpretation: rax = [rbp+0x7E0]; rcx = [rbp+0x7E8]; r14 = rax; [rbp+0x818] = rax; [rbp+0x558] = rcx; if rax == rcx jump 0x67293F6. rax = [rbp+0x758]; rcx = [rax]; rax = [rcx]; rax = [rax+0x48]; rdx = &[rbp+0x2A0]; call via [0xF99FFA0] (sub_eea6040). r14 = [rbp+0x7E0]; rdi = [rbp+0x7E8]; rax = rdi - r14; if rax == -0x20 jump 0x672A30F. test r14,r14/setne al; test rdi,rdi/sete cl; or cl,al; if zero jump 0x672A30F. test r14,r14/setne al; cmp rdi,r14/sete cl; or cl,al; if zero jump 0x672A30F. lea rax = &[rbp+0x7B0]; [rbp+0x7A0] = rax; rax = 0x100000000; [rbp+0x7A8] = rax; if rdi == r14 je short 0x67241F0 else fall through to loc_67241d0.

Callees: [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [rbp+0x7E0], [rbp+0x7E8], [rbp+0x758], [rax], [rcx], [rax+0x48], [rbp+0x2A0], rdi, r14. Fields written: [rbp+0x818], [rbp+0x558], [rbp+0x7A0], [rbp+0x7A8].

---

## Phase 47 — loc_67241d0 loop: per-element sub_676A670 (0x67241d0..0x67241ee)

Loop from 0x67241ca when rdi!=r14. rcx=&[rbp+0x7A0]; rdx=&[rbp+0x560]; r8=r14; call 0x676A670; r14+=0x20; loop while r14!=rdi. [V] per instruction quotes below.

```
0x67241d0  lea rcx,[rbp+0x7A0]                           
0x67241d7  lea rdx,[rbp+0x560]                           
0x67241de  mov r8,r14                                    
0x67241e1  call 0x676A670                                ; -> sub_676a670
0x67241e6  nop                                           
0x67241e7  add r14,0x20                                  
0x67241eb  cmp r14,rdi                                   
0x67241ee  jne short 0x67241D0                           ; -> loc_67241d0
```

Interpretation: rcx = &[rbp+0x7A0]; rdx = &[rbp+0x560]; r8 = r14; call 0x676A670(rcx,rdx,r8). r14 += 0x20; if r14 != rdi loop back to 0x67241d0.

Callees: 0x676A670 (sub_676a670).
Fields read: [rbp+0x7A0], [rbp+0x560], r14, rdi. Fields written: r14.

## Phase 48 — loc_67241f0: second range setup + sub_6764990 + sub_6792980 (0x67241f0..0x672424c)

je target from 0x67241ca (when rdi==r14). rax=&[rbp+0x770]; [rbp+0x760]=rax; rax=0x100000000; [rbp+0x768]=rax. rdi=&[rbp+0x760]; rcx=rdi; rdx=&[rbp+0x7A0]; call 0x6764990. [rsp+0x20]=rdi. rcx=&[rbp+0x560]; rdx=&[rbp+0x458]; r8=&[rbp+0x400]; r9=&[rbp+0x378]; call 0x6792980. [V] per instruction quotes below.

```
0x67241f0  lea rax,[rbp+0x770]                           
0x67241f7  mov [rbp+0x760],rax                           
0x67241fe  mov rax,0x100000000                           
0x6724208  mov [rbp+0x768],rax                           
0x672420f  lea rdi,[rbp+0x760]                           
0x6724216  mov rcx,rdi                                   
0x6724219  lea rdx,[rbp+0x7A0]                           
0x6724220  call 0x6764990                                ; -> sub_6764990
0x6724225  nop                                           
0x6724226  mov [rsp+0x20],rdi                            
0x672422b  lea rcx,[rbp+0x560]                           
0x6724232  lea rdx,[rbp+0x458]                           
0x6724239  lea r8,[rbp+0x400]                            
0x6724240  lea r9,[rbp+0x378]                            
0x6724247  call 0x6792980                                ; -> sub_6792980
0x672424c  nop                                           
```

Interpretation: rax = &[rbp+0x770]; [rbp+0x760] = rax; rax = 0x100000000; [rbp+0x768] = rax. rdi = &[rbp+0x760]; rcx = rdi; rdx = &[rbp+0x7A0]; call 0x6764990. [rsp+0x20] = rdi. rcx = &[rbp+0x560], rdx = &[rbp+0x458], r8 = &[rbp+0x400], r9 = &[rbp+0x378], call 0x6792980.

Callees: 0x6764990 (sub_6764990), 0x6792980 (sub_6792980).
Fields read: [rbp+0x770], [rbp+0x760], rdi, [rbp+0x7A0], [rbp+0x560], [rbp+0x458], [rbp+0x400], [rbp+0x378]. Fields written: [rbp+0x760], [rbp+0x768], [rsp+0x20].

---

## Phase 49 — [rbp+0x4A8] copy to [rbp+0x6C8] + call 0x5ABA5C0 (0x672424d..0x67242d9)

eax=[rbp+0x4A8+0x10]->[rbp+0x6C8+0x10]; xmm0=[rbp+0x4A8]->[rbp+0x6C8]; byte [rbp+0x4BC]->[rbp+0x6DC]; xmm0=[rbp+0x4C0]->[rbp+0x6E0]; xmm0-xmm2=[rbx+0x80/0x90/0x9F]->[rbp+0x564+0x1AB/0x19C/0x18C]; word [rbp+0x500]->[rbp+0x720]. rax=[rbp+0x808]; rcx=[rax+0x10]; rcx+=0x9D0; call 0x5ABA5C0. [V] per instruction quotes below.

```
0x672424d  lea rcx,[rbp+0x4A8]                           
0x6724254  mov eax,[rcx+0x10]                            
0x6724257  lea rdx,[rbp+0x6C8]                           
0x672425e  mov [rdx+0x10],eax                            
0x6724261  movups xmm0,[rcx]                             
0x6724264  movups [rdx],xmm0                             
0x6724267  movzx eax,byte ptr [rbp+0x4BC]                
0x672426e  mov [rbp+0x6DC],al                            
0x6724274  movups xmm0,[rbp+0x4C0]                       
0x672427b  movups [rbp+0x6E0],xmm0                       
0x6724282  movups xmm0,[rbx+0x80]                        
0x6724289  movups xmm1,[rbx+0x90]                        
0x6724290  movups xmm2,[rbx+0x9F]                        
0x6724297  lea rax,[rbp+0x564]                           
0x672429e  movups [rax+0x1AB],xmm2                       
0x67242a5  movups [rax+0x19C],xmm1                       
0x67242ac  movups [rax+0x18C],xmm0                       
0x67242b3  movzx eax,word ptr [rbp+0x500]                
0x67242ba  mov [rbp+0x720],ax                            
0x67242c1  mov rax,[rbp+0x808]                           
0x67242c8  mov rcx,[rax+0x10]                            
0x67242cc  mov eax,0x9D0                                 
0x67242d1  add rcx,rax                                   
0x67242d4  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x67242d9  nop                                           
```

Interpretation: eax = [rbp+0x4A8+0x10]; rdx = &[rbp+0x6C8]; [rdx+0x10] = eax; xmm0 = [rbp+0x4A8] -> [rdx]. eax = byte [rbp+0x4BC] -> [rbp+0x6DC]. xmm0 = [rbp+0x4C0] -> [rbp+0x6E0]. xmm0 = [rbx+0x80], xmm1 = [rbx+0x90], xmm2 = [rbx+0x9F] -> [rbp+0x564+0x1AB]/[rbp+0x564+0x19C]/[rbp+0x564+0x18C]. eax = word [rbp+0x500] -> [rbp+0x720]. rax = [rbp+0x808], rcx = [rax+0x10], eax = 0x9D0, rcx += rax. Call 0x5ABA5C0.

Callees: 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x4A8+0x10], [rbp+0x4A8], [rbp+0x4BC], [rbp+0x4C0], [rbx+0x80], [rbx+0x90], [rbx+0x9F], [rbp+0x500], [rbp+0x808], [rax+0x10]. Fields written: [rbp+0x6C8+0x10], [rbp+0x6C8], [rbp+0x6DC], [rbp+0x6E0], [rbp+0x564+0x1AB], [rbp+0x564+0x19C], [rbp+0x564+0x18C], [rbp+0x720].

## Phase 50 — r14 capture + zero xmm6 at [rbp+0x2A4+0xB4..+4] (0x67242da..0x672431c)

r14 = rax (result of 0x5ABA5C0). Zero xmm6 at [rbp+0x2A4+0xB4], [0xA4], [0x94], [0x84], [0x74], [0x64], [0x54], [0x44], [0x34], [0x24], [0x14], [+4] — 13 stores descending by 0x10. [V] per instruction quotes below.

```
0x67242da  mov r14,rax                                   
0x67242dd  lea rax,[rbp+0x2A4]                           
0x67242e4  movups [rax+0xB4],xmm6                        
0x67242eb  movups [rax+0xA4],xmm6                        
0x67242f2  movups [rax+0x94],xmm6                        
0x67242f9  movups [rax+0x84],xmm6                        
0x6724300  movups [rax+0x74],xmm6                        
0x6724304  movups [rax+0x64],xmm6                        
0x6724308  movups [rax+0x54],xmm6                        
0x672430c  movups [rax+0x44],xmm6                        
0x6724310  movups [rax+0x34],xmm6                        
0x6724314  movups [rax+0x24],xmm6                        
0x6724318  movups [rax+0x14],xmm6                        
0x672431c  movups [rax+4],xmm6                           
```

Interpretation: r14 = rax. rax = &[rbp+0x2A4]. Zero xmm6 at [rbp+0x2A4+0xB4], [rbp+0x2A4+0xA4], [rbp+0x2A4+0x94], [rbp+0x2A4+0x84], [rbp+0x2A4+0x74], [rbp+0x2A4+0x64], [rbp+0x2A4+0x54], [rbp+0x2A4+0x44], [rbp+0x2A4+0x34], [rbp+0x2A4+0x24], [rbp+0x2A4+0x14], [rbp+0x2A4+0x04].

Callees: none.
Fields written: [rbp+0x2A4+0xB4], [rbp+0x2A4+0xA4], [rbp+0x2A4+0x94], [rbp+0x2A4+0x84], [rbp+0x2A4+0x74], [rbp+0x2A4+0x64], [rbp+0x2A4+0x54], [rbp+0x2A4+0x44], [rbp+0x2A4+0x34], [rbp+0x2A4+0x24], [rbp+0x2A4+0x14], [rbp+0x2A4+4].

## Phase 51 — TLS call + word store + jump (0x6724320..0x6724363)

rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0] (sub_eea6040); store al at [rbp+0x827]. rdx=[r14+0x8A8]; cmp with [r14+0x8B0]; if equal jump sub_67288ac; else eax=word[rbp+0x720], store at [rdx], add qword [r14+0x8A8],2, jmp sub_67288c0. [V] per instruction quotes below.

```
0x6724320  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6724327  mov rax,[rcx]                                 
0x672432a  mov rax,[rax+0x10]                            
0x672432e  mov dl,0x4A                                   
0x6724330  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6724336  nop                                           
0x6724337  mov [rbp+0x827],al                            
0x672433d  mov rdx,[r14+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6724344  cmp rdx,[r14+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x672434b  je 0x67288AC                                  ; -> sub_67288ac
0x6724351  movzx eax,word ptr [rbp+0x720]                
0x6724358  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x672435b  add qword ptr [r14+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6724363  jmp 0x67288C0                                 ; -> sub_67288c0
```

Interpretation: rcx = [0x1233E1B0]; rax = [rcx]; rax = [rax+0x10]; dl = 0x4A; call via [0xF99FFA0] (sub_eea6040); store al at [rbp+0x827]. rdx = [r14+0x8A8]; cmp with [r14+0x8B0]; if equal jump 0x67288AC. Otherwise: eax = word [rbp+0x720]; store at [rdx]; add qword [r14+0x8A8], 2; jmp 0x67288C0.

Callees: [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [r14+0x8A8], [r14+0x8B0], [rbp+0x720]. Fields written: [rbp+0x827], [rdx] (word store), [r14+0x8A8].

---

## Phase 52 — refcount object setup path A (0x6724368..0x67243e7)

edx=0; rcx=[rbp+0x540]; [rbp+0x760]=rcx; [rbp+0x768]=rdx(0). ecx=[rbp+0x800]->[rbp+0x770]; ecx=[rbp+0x7FC]->[rbp+0x774]; ecx=[rbp+0x754]->[rbp+0x778]. rcx=0x100000000->[rbp+0x77C]. dword [rbp+0x784]=1. movaps [rbp+0x7A0]=xmm6. rcx=[rsi+0xD0]; if rcx==0 je loc_6724466 else lock inc dword [rcx+8]; rcx=[rsi+0xD0]; rdx=[rbp+0x768]; jmp loc_6724468. [V] per instruction quotes below.

```
0x6724368  xor edx,edx                                   
0x672436a  mov rcx,[rbp+0x540]                           
0x6724371  mov [rbp+0x760],rcx                           
0x6724378  mov [rbp+0x768],rdx                           
0x672437f  mov ecx,[rbp+0x800]                           
0x6724385  mov [rbp+0x770],ecx                           
0x672438b  mov ecx,[rbp+0x7FC]                           
0x6724391  mov [rbp+0x774],ecx                           
0x6724397  mov ecx,[rbp+0x754]                           
0x672439d  mov [rbp+0x778],ecx                           
0x67243a3  mov rcx,0x100000000                           
0x67243ad  mov [rbp+0x77C],rcx                           
0x67243b4  mov dword ptr [rbp+0x784],1                   
0x67243be  movaps [rbp+0x7A0],xmm6                       
0x67243c5  mov rcx,[rsi+0xD0]                            
0x67243cc  test rcx,rcx                                  
0x67243cf  je 0x6724466                                  ; -> loc_6724466
0x67243d5  lock inc dword ptr [rcx+8]                    
0x67243d9  mov rcx,[rsi+0xD0]                            
0x67243e0  mov rdx,[rbp+0x768]                           
0x67243e7  jmp short 0x6724468                           ; -> loc_6724468
```

Interpretation: edx=0; rcx=[rbp+0x540]; [rbp+0x760]=rcx; [rbp+0x768]=0. ecx=[rbp+0x800]->[rbp+0x770]; ecx=[rbp+0x7FC]->[rbp+0x774]; ecx=[rbp+0x754]->[rbp+0x778]. rcx=0x100000000->[rbp+0x77C]; dword [rbp+0x784]=1; movaps [rbp+0x7A0]=xmm6. rcx=[rsi+0xD0]; test rcx,rcx; if zero jump 0x6724466; else lock inc dword [rcx+8]; rcx=[rsi+0xD0]; rdx=[rbp+0x768]; jmp 0x6724468.

Callees: none direct.
Fields read: [rbp+0x540], [rbp+0x800], [rbp+0x7FC], [rbp+0x754], rsi, [rsi+0xD0], [rbp+0x768], xmm6. Fields written: [rbp+0x760], [rbp+0x768], [rbp+0x770], [rbp+0x774], [rbp+0x778], [rbp+0x77C], [rbp+0x784], [rbp+0x7A0], [rcx+8] (lock inc).

## Phase 53 — refcount object setup path B (0x67243e9..0x6724464)

Identical setup to Phase 52 but jumps to loc_67244a1 / loc_67244a3 instead (shown linearly after path A's jmp by rdis; separate basic block). [V] per instruction quotes below.

```
0x67243e9  xor edx,edx                                   
0x67243eb  mov rcx,[rbp+0x540]                           
0x67243f2  mov [rbp+0x760],rcx                           
0x67243f9  mov [rbp+0x768],rdx                           
0x6724400  mov ecx,[rbp+0x800]                           
0x6724406  mov [rbp+0x770],ecx                           
0x672440c  mov ecx,[rbp+0x7FC]                           
0x6724412  mov [rbp+0x774],ecx                           
0x6724418  mov ecx,[rbp+0x754]                           
0x672441e  mov [rbp+0x778],ecx                           
0x6724424  mov rcx,0x100000000                           
0x672442e  mov [rbp+0x77C],rcx                           
0x6724435  mov dword ptr [rbp+0x784],1                   
0x672443f  movaps [rbp+0x7A0],xmm6                       
0x6724446  mov rcx,[rsi+0xD0]                            
0x672444d  test rcx,rcx                                  
0x6724450  je short 0x67244A1                            ; -> loc_67244a1
0x6724452  lock inc dword ptr [rcx+8]                    
0x6724456  mov rcx,[rsi+0xD0]                            
0x672445d  mov rdx,[rbp+0x768]                           
0x6724464  jmp short 0x67244A3                           ; -> loc_67244a3
```

Interpretation: edx=0; rcx=[rbp+0x540]; [rbp+0x760]=rcx; [rbp+0x768]=0. ecx=[rbp+0x800]->[rbp+0x770]; ecx=[rbp+0x7FC]->[rbp+0x774]; ecx=[rbp+0x754]->[rbp+0x778]. rcx=0x100000000->[rbp+0x77C]; dword [rbp+0x784]=1; movaps [rbp+0x7A0]=xmm6. rcx=[rsi+0xD0]; test rcx,rcx; if zero jump 0x67244A1; else lock inc dword [rcx+8]; rcx=[rsi+0xD0]; rdx=[rbp+0x768]; jmp 0x67244A3.

Callees: none direct.
Fields read: [rbp+0x540], [rbp+0x800], [rbp+0x7FC], [rbp+0x754], rsi, [rsi+0xD0], [rbp+0x768], xmm6. Fields written: [rbp+0x760], [rbp+0x768], [rbp+0x770], [rbp+0x774], [rbp+0x778], [rbp+0x77C], [rbp+0x784], [rbp+0x7A0], [rcx+8] (lock inc).

## Phase 54 — loc_6724466 / loc_6724468: r8=[rsi+0xC8] + zero + optional refcount inc (0x6724466..0x672449f)

loc_6724466 (xor ecx) falls into loc_6724468. r8=[rsi+0xC8]; [rbp+0x7A0]=r8; [rbp+0x7A8]=rcx; lea r8=&[rbp+0x7B0]; movups [r8]=xmm6 (zero). test rdx,rdx; if zero je loc_67244dc else lock inc dword [rdx+8]; rdx=[rbp+0x768]; rcx=[rbp+0x7A8]; jmp loc_67244de. [V] per instruction quotes below.

```
loc_6724466:  ; from 67243cf
  6724466  xor ecx,ecx                                   

loc_6724468:  ; from 67243e7
  6724468  mov r8,[rsi+0xC8]                             
  672446f  mov [rbp+0x7A0],r8                            
  6724476  mov [rbp+0x7A8],rcx                           
  672447d  lea r8,[rbp+0x7B0]                            
  6724484  movups [r8],xmm6                              
  6724488  test rdx,rdx                                  
  672448b  je short 0x67244DC                            ; -> loc_67244dc
  672448d  lock inc dword ptr [rdx+8]                    
  6724491  mov rdx,[rbp+0x768]                           
  6724498  mov rcx,[rbp+0x7A8]                           
  672449f  jmp short 0x67244DE                           ; -> loc_67244de
```

Interpretation: ecx=0. r8=[rsi+0xC8]; [rbp+0x7A0]=r8; [rbp+0x7A8]=rcx. r8=&[rbp+0x7B0]; movups [r8]=xmm6. test rdx,rdx; if zero jump 0x67244DC; else lock inc dword [rdx+8]; rdx=[rbp+0x768]; rcx=[rbp+0x7A8]; jmp 0x67244DE.

Callees: none direct.
Fields read: [rsi+0xC8], rcx, rdx, xmm6, [rbp+0x768], [rbp+0x7A8]. Fields written: [rbp+0x7A0], [rbp+0x7A8], [rbp+0x7B0], [rdx+8] (lock inc).

## Phase 55 — loc_67244a1 / loc_67244a3: same pattern, jumps to loc_6724532 / loc_6724534 (0x67244a1..0x67244da)

Same structure as Phase 54 but test rdx je loc_6724532 / lock inc -> jmp loc_6724534. [V] per instruction quotes below.

```
loc_67244a1:  ; from 6724450
  67244a1  xor ecx,ecx                                   

loc_67244a3:  ; from 6724464
  67244a3  mov r8,[rsi+0xC8]                             
  67244aa  mov [rbp+0x7A0],r8                            
  67244b1  mov [rbp+0x7A8],rcx                           
  67244b8  lea r8,[rbp+0x7B0]                            
  67244bf  movups [r8],xmm6                              
  67244c3  test rdx,rdx                                  
  67244c6  je short 0x6724532                            ; -> loc_6724532
  67244c8  lock inc dword ptr [rdx+8]                    
  67244cc  mov rdx,[rbp+0x768]                           
  67244d3  mov rcx,[rbp+0x7A8]                           
  67244da  jmp short 0x6724534                           ; -> loc_6724534
```

Interpretation: ecx=0. r8=[rsi+0xC8]; [rbp+0x7A0]=r8; [rbp+0x7A8]=rcx. r8=&[rbp+0x7B0]; movups [r8]=xmm6. test rdx,rdx; if zero jump 0x6724532; else lock inc dword [rdx+8]; rdx=[rbp+0x768]; rcx=[rbp+0x7A8]; jmp 0x6724534.

Callees: none direct.
Fields read: [rsi+0xC8], rcx, rdx, xmm6, [rbp+0x768], [rbp+0x7A8]. Fields written: [rbp+0x7A0], [rbp+0x7A8], [rbp+0x7B0], [rdx+8] (lock inc).

---

## Phase 56 — loc_67244dc / loc_67244de: rdx reset + r10/r8/r9 setup + refcount inc (0x67244dc..0x6724512)

loc_67244dc (xor edx) falls into loc_67244de. rdx=[rbp+0x768]; r8=[rbp+0x760]; [rbp+0x7B0]=r8; [rbp+0x7B8]=rdx; lea r10=&[rbp+0x770]; r8=[r10+0x10]; lea r8=&[rbp+0x7B0] (note: r8 reassigned); movups [r8]=xmm6. test rdx,rdx; if zero je loc_67244dc... wait — re-reading: lea r10=&[rbp+0x770]; r8=[r10+0x10]; lea r9=&[rbp+0x7B0]; [r9+0x20]=r8; movups xmm0=[r10]; movups [r9+0x10]=xmm0; movaps [rbp+0x2A0]=xmm6; test rcx,rcx; if zero je loc_6724588 else lock inc dword [rcx+8]; rcx=[rbp+0x7A8]; rdx=[rbp+0x7B8]; jmp loc_672458a. [V] per instruction quotes below.

```
loc_67244dc:  ; from 672448b
  67244dc  xor edx,edx                                   

loc_67244de:  ; from 672449f
  67244de  mov r8,[rbp+0x760]                            
  67244e5  mov [rbp+0x7B0],r8                            
  67244ec  mov [rbp+0x7B8],rdx                           
  67244f3  lea r10,[rbp+0x770]                           
  67244fa  mov r8,[r10+0x10]                             
  67244fe  lea r9,[rbp+0x7B0]                            
  6724505  mov [r9+0x20],r8                              
  6724509  movups xmm0,[r10]                             
  672450d  movups [r9+0x10],xmm0                         
  6724512  movaps [rbp+0x2A0],xmm6                       
  6724519  test rcx,rcx                                  
  672451c  je short 0x6724588                            ; -> loc_6724588
  672451e  lock inc dword ptr [rcx+8]                    
  6724522  mov rcx,[rbp+0x7A8]                           
  6724529  mov rdx,[rbp+0x7B8]                           
  6724530  jmp short 0x672458A                           ; -> loc_672458a
```

Interpretation: edx=0. r8=[rbp+0x760]; [rbp+0x7B0]=r8; [rbp+0x7B8]=rdx(0). r10=&[rbp+0x770]; r8=[r10+0x10]; r9=&[rbp+0x7B0]; [r9+0x20]=r8. movups xmm0=[r10]; movups [r9+0x10]=xmm0. movaps [rbp+0x2A0]=xmm6. test rcx,rcx; if zero jump 0x6724588; else lock inc dword [rcx+8]; rcx=[rbp+0x7A8]; rdx=[rbp+0x7B8]; jmp 0x672458A.

Callees: none direct.
Fields read: rdx, [rbp+0x760], rdx, [rbp+0x770], [r10+0x10], xmm0, xmm6, rcx, [rbp+0x7A8], [rbp+0x7B8]. Fields written: [rbp+0x7B0], [rbp+0x7B8], [r9+0x20], [r9+0x10], [rbp+0x2A0], [rcx+8] (lock inc).

## Phase 57 — loc_6724532 / loc_6724534: same pattern, jumps to loc_67245BC / loc_67245BE (0x6724532..0x6724586)

loc_6724532 (xor edx) falls into loc_6724534. Same structure as Phase 56 but je loc_67245BC / jmp loc_67245BE. [V] per instruction quotes below.

```
loc_6724532:  ; from 67244c6
  6724532  xor edx,edx                                   

loc_6724534:  ; from 67244da
  6724534  mov r8,[rbp+0x760]                            
  672453b  mov [rbp+0x7B0],r8                            
  6724542  mov [rbp+0x7B8],rdx                           
  6724549  lea r10,[rbp+0x770]                           
  6724550  mov r8,[r10+0x10]                             
  6724554  lea r9,[rbp+0x7B0]                            
  672455b  mov [r9+0x20],r8                              
  672455f  movups xmm0,[r10]                             
  6724563  movups [r9+0x10],xmm0                         
  6724568  movaps [rbp+0x2A0],xmm6                       
  672456f  test rcx,rcx                                  
  6724572  je short 0x67245BC                            ; -> loc_67245bc
  6724574  lock inc dword ptr [rcx+8]                    
  6724578  mov rcx,[rbp+0x7A8]                           
  672457f  mov rdx,[rbp+0x7B8]                           
  6724586  jmp short 0x67245BE                           ; -> loc_67245be
```

Interpretation: edx=0. r8=[rbp+0x760]; [rbp+0x7B0]=r8; [rbp+0x7B8]=rdx(0). r10=&[rbp+0x770]; r8=[r10+0x10]; r9=&[rbp+0x7B0]; [r9+0x20]=r8. movups xmm0=[r10]; movups [r9+0x10]=xmm0. movaps [rbp+0x2A0]=xmm6. test rcx,rcx; if zero jump 0x67245BC; else lock inc dword [rcx+8]; rcx=[rbp+0x7A8]; rdx=[rbp+0x7B8]; jmp 0x67245BE.

Callees: none direct.
Fields read: rdx, [rbp+0x760], rdx, [rbp+0x770], [r10+0x10], xmm0, xmm6, rcx, [rbp+0x7A8], [rbp+0x7B8]. Fields written: [rbp+0x7B0], [rbp+0x7B8], [r9+0x20], [r9+0x10], [rbp+0x2A0], [rcx+8] (lock inc).

## Phase 58 — loc_6724588 / loc_672458a (variant 1): r8=[rbp+0x7A0] + zero [rbp+0x2A4+0xC] + optional refcount + jmp loc_67245fa (0x6724588..0x67245e1)

loc_6724588 (xor ecx) falls into loc_672458a. r8=[rbp+0x7A0]; [rbp+0x2A0]=r8; [rbp+0x2A8]=rcx; lea rcx=&[rbp+0x2A4]; movups [rcx+0xC]=xmm6. test rdx,rdx; if zero je loc_67245f7 else lock inc dword [rdx+8]; r14=[rbp+0x7B8]; jmp loc_67245fa. [V] per instruction quotes below.

```
loc_6724588:  ; from 672451c
  6724588  xor ecx,ecx                                   

loc_672458a:  ; from 6724530
  672458a  mov r8,[rbp+0x7A0]                            
  6724591  mov [rbp+0x2A0],r8                            
  6724598  mov [rbp+0x2A8],rcx                           
  672459f  lea rcx,[rbp+0x2A4]                           
  67245a6  movups [rcx+0xC],xmm6                         
  67245aa  test rdx,rdx                                  
  67245ad  je short 0x67245F7                            ; -> loc_67245f7
  67245af  lock inc dword ptr [rdx+8]                    
  67245b3  mov r14,[rbp+0x7B8]                           
  67245ba  jmp short 0x67245FA                           ; -> loc_67245fa
```

Interpretation: ecx=0. r8=[rbp+0x7A0]; [rbp+0x2A0]=r8; [rbp+0x2A8]=rcx. rcx=&[rbp+0x2A4]; movups [rcx+0xC]=xmm6. test rdx,rdx; if zero jump 0x67245F7; else lock inc dword [rdx+8]; r14=[rbp+0x7B8]; jmp 0x67245FA.

Callees: none direct.
Fields read: [rbp+0x7A0], rcx, rdx, xmm6, [rbp+0x7B8]. Fields written: [rbp+0x2A0], [rbp+0x2A8], [rbp+0x2A4+0xC], [rdx+8] (lock inc), r14.

## Phase 59 — loc_67245bc / loc_67245be (variant 2): same, but je 0x672486f / jmp 0x6724872 (0x67245bc..0x67245f2)

loc_67245bc (xor ecx) falls into loc_67245be. Same structure as Phase 58 but test rdx je 0x672486F / lock inc -> jmp 0x6724872. [V] per instruction quotes below.

```
loc_67245bc:  ; from 6724572
  67245bc  xor ecx,ecx                                   

loc_67245be:  ; from 6724586
  67245be  mov r8,[rbp+0x7A0]                            
  67245c5  mov [rbp+0x2A0],r8                            
  67245cc  mov [rbp+0x2A8],rcx                           
  67245d3  lea rcx,[rbp+0x2A4]                           
  67245da  movups [rcx+0xC],xmm6                         
  67245de  test rdx,rdx                                  
  67245e1  je 0x672486F                                  ; -> loc_672486f
  67245e7  lock inc dword ptr [rdx+8]                    
  67245eb  mov r14,[rbp+0x7B8]                           
  67245f2  jmp 0x6724872                                 ; -> loc_6724872
```

Interpretation: ecx=0. r8=[rbp+0x7A0]; [rbp+0x2A0]=r8; [rbp+0x2A8]=rcx. rcx=&[rbp+0x2A4]; movups [rcx+0xC]=xmm6. test rdx,rdx; if zero jump 0x672486F; else lock inc dword [rdx+8]; r14=[rbp+0x7B8]; jmp 0x6724872.

Callees: none direct.
Fields read: [rbp+0x7A0], rcx, rdx, xmm6, [rbp+0x7B8]. Fields written: [rbp+0x2A0], [rbp+0x2A8], [rbp+0x2A4+0xC], [rdx+8] (lock inc), r14.

---

## Phase 60 — loc_67245f7 / loc_67245fa: r14 reset + [rbp+0x2B0/0x2B8] store + xmm12/xmm15 accumulate + call 0x67A75D0 (0x67245f7..0x67246fe)

loc_67245f7 (xor r14d) falls into loc_67245fa. rcx=[rbp+0x7B0]; [rbp+0x2B0]=rcx; [rbp+0x2B8]=r14. lea rdx=&[rbp+0x7B0]; rcx=[rdx+0x20]; lea r8=&[rbp+0x2A4]; [r8+0x2C]=rcx. movups xmm0=[rdx+0x10]; movups [r8+0x1C]=xmm0. ecx=[rbp+0x79C]; [rbp+0x2D8]=ecx; [rbp+0x2E0]=ax. addss xmm12,xmm13; addps xmm15,xmm14. movlps [rbp+0x7E0]=xmm15; movss [rbp+0x7E8]=xmm12. lea rcx=&[rbp+0x510]; rdx=r15; call 0x67A75D0. [V] per instruction quotes below.

```
loc_67245f7:  ; from 67245ad
  67245f7  xor r14d,r14d                                 

loc_67245fa:  ; from 67245ba
  67245fa  mov rcx,[rbp+0x7B0]                           
  6724601  mov [rbp+0x2B0],rcx                           
  6724608  mov [rbp+0x2B8],r14                           
  672460f  lea rdx,[rbp+0x7B0]                           
  6724616  mov rcx,[rdx+0x20]                            
  672461a  lea r8,[rbp+0x2A4]                            
  6724621  mov [r8+0x2C],rcx                             
  6724625  movups xmm0,[rdx+0x10]                        
  6724629  movups [r8+0x1C],xmm0                         
  672462e  mov ecx,[rbp+0x79C]                           
  6724634  mov [rbp+0x2D8],ecx                           
  672463a  mov [rbp+0x2E0],ax                            
  6724641  addss xmm12,xmm13                             
  6724646  addps xmm15,xmm14                             
  672464a  movlps [rbp+0x7E0],xmm15                      
  6724652  movss [rbp+0x7E8],xmm12                       
  672465b  lea rcx,[rbp+0x510]                           
  6724662  mov rdx,r15                                   
  6724665  call 0x67A75D0                                ; -> sub_67a75d0
  672466a  nop                                           
```

Interpretation: r14d=0 (xor r14d,r14d). rcx=[rbp+0x7B0]; [rbp+0x2B0]=rcx; [rbp+0x2B8]=r14. rdx=&[rbp+0x7B0]; rcx=[rdx+0x20]; r8=&[rbp+0x2A4]; [r8+0x2C]=rcx. movups xmm0=[rdx+0x10]; movups [r8+0x1C]=xmm0. ecx=[rbp+0x79C]; [rbp+0x2D8]=ecx; [rbp+0x2E0]=ax. addss xmm12,xmm13; addps xmm15,xmm14. movlps [rbp+0x7E0]=xmm15; movss [rbp+0x7E8]=xmm12. rcx=&[rbp+0x510]; rdx=r15; call 0x67A75D0(rcx,rdx).

Callees: 0x67A75D0 (sub_67a75d0).
Fields read: [rbp+0x7B0], r14, rdx, [rdx+0x20], [rbp+0x2A4], [rdx+0x10], [rbp+0x79C], xmm12,xmm13,xmm15,xmm14, [rbp+0x510], r15. Fields written: [rbp+0x2B0], [rbp+0x2B8], [rbp+0x2A4+0x2C], [rbp+0x2A4+0x1C], [rbp+0x2D8], [rbp+0x2E0], [rbp+0x7E0], [rbp+0x7E8].

## Phase 61 — call 0x678E1D0 + r13 field copy + call 0x67E23F0 + stack arg setup + call 0x6791420 (0x672466b..0x672474e)

lea rax=&[rbp+0x7E0]; [rsp+0x20]=rax. lea rdi=&[rbp+0x370]; rcx=rdi; rdx=&[rbp+0x1F0]; r8=&[rbp+0x198]; r9=r15; call 0x678E1D0. eax=[r13+0x60]->[rbx+0x70]; xmm0=[r13+0x50]->[rbx+0x60]; byte [rbp+0x254]->[rbp+0x4C4]; xmm0=[rbp+0x258]->[rbp+0x4C8]; xmm0-xmm2=[r13+0x78/0x88/0x97]->[rbx+0xA7/0x98/0x88]; word [rbp+0x298]->[rbp+0x508]; rcx=r15; call 0x67E23F0. [rsp+0x38]=&[rbp+0x2A0]; [rsp+0x30]=&[rbp+0x2D8]; [rsp+0x28]=&[rbp+0x2E0]; [rsp+0x20]=rdi. rcx=&[rbp+0x560]; rdx=&[rbp+0x460]; r8=&[rbp+0x408]; r9=&[rbp+0x380]; call 0x6791420. [V] per instruction quotes below.

```
0x672466b  lea rax,[rbp+0x7E0]                           
0x6724672  mov [rsp+0x20],rax                            
0x6724677  lea rdi,[rbp+0x370]                           
0x672467e  mov rcx,rdi                                   
0x6724681  lea rdx,[rbp+0x1F0]                           
0x6724688  lea r8,[rbp+0x198]                            
0x672468f  mov r9,r15                                    
0x6724692  call 0x678E1D0                                ; -> sub_678e1d0
0x6724697  nop                                           
0x6724698  mov eax,[r13+0x60]                            
0x672469c  mov [rbx+0x70],eax                            
0x672469f  movups xmm0,[r13+0x50]                        
0x67246a4  movups [rbx+0x60],xmm0                        
0x67246a8  movzx eax,byte ptr [rbp+0x254]                
0x67246af  mov [rbp+0x4C4],al                            
0x67246b5  movups xmm0,[rbp+0x258]                       
0x67246bc  movups [rbp+0x4C8],xmm0                       
0x67246c3  movups xmm0,[r13+0x78]                        
0x67246c8  movups xmm1,[r13+0x88]                        
0x67246d0  movups xmm2,[r13+0x97]                        
0x67246d8  movups [rbx+0xA7],xmm2                        
0x67246df  movups [rbx+0x98],xmm1                        
0x67246e6  movups [rbx+0x88],xmm0                        
0x67246ed  movzx eax,word ptr [rbp+0x298]                
0x67246f4  mov [rbp+0x508],ax                            
0x67246fb  mov rcx,r15                                   
0x67246fe  call 0x67E23F0                                ; -> sub_67e23f0
0x6724703  nop                                           
0x6724704  lea rax,[rbp+0x2A0]                           
0x672470b  mov [rsp+0x38],rax                            
0x6724710  lea rax,[rbp+0x2D8]                           
0x6724717  mov [rsp+0x30],rax                            
0x672471c  lea rax,[rbp+0x2E0]                           
0x6724723  mov [rsp+0x28],rax                            
0x6724728  mov [rsp+0x20],rdi                            
0x672472d  lea rcx,[rbp+0x560]                           
0x6724734  lea rdx,[rbp+0x460]                           
0x672473b  lea r8,[rbp+0x408]                            
0x6724742  lea r9,[rbp+0x380]                            
0x6724749  call 0x6791420                                ; -> sub_6791420
0x672474e  nop                                           
```

Interpretation: rax=&[rbp+0x7E0]; [rsp+0x20]=rax. rdi=&[rbp+0x370]; rcx=rdi; rdx=&[rbp+0x1F0]; r8=&[rbp+0x198]; r9=r15; call 0x678E1D0. eax=[r13+0x60]->[rbx+0x70]. xmm0=[r13+0x50]->[rbx+0x60]. eax=byte [rbp+0x254]->[rbp+0x4C4]. xmm0=[rbp+0x258]->[rbp+0x4C8]. xmm0=[r13+0x78],xmm1=[r13+0x88],xmm2=[r13+0x97]->[rbx+0xA7]/[rbx+0x98]/[rbx+0x88]. eax=word [rbp+0x298]->[rbp+0x508]. rcx=r15; call 0x67E23F0. [rsp+0x38]=&[rbp+0x2A0]; [rsp+0x30]=&[rbp+0x2D8]; [rsp+0x28]=&[rbp+0x2E0]; [rsp+0x20]=rdi. rcx=&[rbp+0x560]; rdx=&[rbp+0x460]; r8=&[rbp+0x408]; r9=&[rbp+0x380]; call 0x6791420.

Callees: 0x678E1D0 (sub_678e1d0), 0x67E23F0 (sub_67e23f0), 0x6791420 (sub_6791420).
Fields read: [rbp+0x7E0], [rbp+0x370], [rbp+0x1F0], [rbp+0x198], r15, [r13+0x60], [r13+0x50], [rbp+0x254], [rbp+0x258], [r13+0x78], [r13+0x88], [r13+0x97], [rbp+0x298], [rbp+0x2A0], [rbp+0x2D8], [rbp+0x2E0], rdi, [rbp+0x560], [rbp+0x460], [rbp+0x408], [rbp+0x380]. Fields written: [rsp+0x20], [rbx+0x70], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0xA7], [rbx+0x98], [rbx+0x88], [rbp+0x508], [rsp+0x38], [rsp+0x30], [rsp+0x28], [rsp+0x20].

## Phase 62 — rbx field copy + call 0x5ABA5C0 + zero + TLS + word store + jump (0x672474f..0x672486a)

eax=[rbx+0x70]->[rbp+0x6E8+0x10]; xmm0=[rbx+0x60]->[rbp+0x6E8]; byte [rbp+0x4C4]->[rbp+0x6FC]; xmm0=[rbp+0x4C8]->[rbp+0x700]; xmm0-xmm2=[rbx+0x88/0x98/0xA7]->[rbp+0x564+0x1CB/0x1BC/0x1AC]; word [rbp+0x508]->[rbp+0x740]. rax=[rbp+0x808]; rcx=[rax+0x10]; rcx+=0x9D0; call 0x5ABA5C0; r15=rax. zero xmm6 [r13-0x28..0xD8] (13 stores). rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0]; [rbp+0x818]=al. rdx=[r15+0x8A8]; cmp [r15+0x8B0]; if equal jmp loc_6724F48 else word [rbp+0x740]->[rdx]; add qword [r15+0x8A8],2; jmp loc_6724F5C. [V] per instruction quotes below.

```
0x672474f  mov eax,[rbx+0x70]                            
0x6724752  lea rcx,[rbp+0x6E8]                           
0x6724759  mov [rcx+0x10],eax                            
0x672475c  movups xmm0,[rbx+0x60]                        
0x6724760  movups [rcx],xmm0                             
0x6724763  movzx eax,byte ptr [rbp+0x4C4]                
0x672476a  mov [rbp+0x6FC],al                            
0x6724770  movups xmm0,[rbp+0x4C8]                       
0x6724777  movups [rbp+0x700],xmm0                       
0x672477e  movups xmm0,[rbx+0x88]                        
0x6724785  movups xmm1,[rbx+0x98]                        
0x672478c  movups xmm2,[rbx+0xA7]                        
0x6724793  lea rax,[rbp+0x564]                           
0x672479a  movups [rax+0x1CB],xmm2                       
0x67247a1  movups [rax+0x1BC],xmm1                       
0x67247a8  movups [rax+0x1AC],xmm0                       
0x67247af  movzx eax,word ptr [rbp+0x508]                
0x67247b6  mov [rbp+0x740],ax                            
0x67247bd  mov rax,[rbp+0x808]                           
0x67247c4  mov rcx,[rax+0x10]                            
0x67247c8  mov eax,0x9D0                                 
0x67247cd  add rcx,rax                                   
0x67247d0  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x67247d5  nop                                           
0x67247d6  mov r15,rax                                   
0x67247d9  movups [r13-0x28],xmm6                        
0x67247de  movups [r13-0x38],xmm6                        
0x67247e3  movups [r13-0x48],xmm6                        
0x67247e8  movups [r13-0x58],xmm6                        
0x67247ed  movups [r13-0x68],xmm6                        
0x67247f2  movups [r13-0x78],xmm6                        
0x67247f7  movups [r13-0x88],xmm6                        
0x67247ff  movups [r13-0x98],xmm6                        
0x6724807  movups [r13-0xA8],xmm6                        
0x672480f  movups [r13-0xB8],xmm6                        
0x6724817  movups [r13-0xC8],xmm6                        
0x672481f  movups [r13-0xD8],xmm6                        
0x6724827  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x672482e  mov rax,[rcx]                                 
0x6724831  mov rax,[rax+0x10]                            
0x6724835  mov dl,0x4A                                   
0x6724837  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x672483d  nop                                           
0x672483e  mov [rbp+0x818],al                            
0x6724844  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x672484b  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6724852  je 0x6724F48                                  ; -> loc_6724f48
0x6724858  movzx eax,word ptr [rbp+0x740]                
0x672485f  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x6724862  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x672486a  jmp 0x6724F5C                                 ; -> loc_6724f5c
```

Interpretation: eax=[rbx+0x70]; rcx=&[rbp+0x6E8]; [rcx+0x10]=eax; xmm0=[rbx+0x60]->[rcx]. eax=byte [rbp+0x4C4]->[rbp+0x6FC]. xmm0=[rbp+0x4C8]->[rbp+0x700]. xmm0=[rbx+0x88],xmm1=[rbx+0x98],xmm2=[rbx+0xA7]->[rbp+0x564+0x1CB]/[rbp+0x564+0x1BC]/[rbp+0x564+0x1AC]. eax=word [rbp+0x508]->[rbp+0x740]. rax=[rbp+0x808], rcx=[rax+0x10], eax=0x9D0, rcx+=rax. Call 0x5ABA5C0; r15=rax. zero xmm6 [r13-0x28]..[r13-0xD8] (13 stores). rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0] (sub_eea6040); store al at [rbp+0x818]. rdx=[r15+0x8A8]; cmp with [r15+0x8B0]; if equal jump 0x6724F48. Otherwise: eax=word [rbp+0x740]; store at [rdx]; add qword [r15+0x8A8],2; jmp 0x6724F5C.

Callees: 0x5ABA5C0 (sub_5aba5c0), [0xF99FFA0]=sub_eea6040 (indirect).
Fields read: [rbx+0x70], [rbx+0x60], [rbp+0x4C4], [rbp+0x4C8], [rbx+0x88], [rbx+0x98], [rbx+0xA7], [rbp+0x508], [rbp+0x808], [rax+0x10], [r13-0x28..0xD8] (writes), [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8B0], [rbp+0x740]. Fields written: [rbp+0x6E8+0x10], [rbp+0x6E8], [rbp+0x6FC], [rbp+0x700], [rbp+0x564+0x1CB], [rbp+0x564+0x1BC], [rbp+0x564+0x1AC], [rbp+0x740], [r15], [r13-0x28]..[r13-0xD8], [rbp+0x818], [rdx] (word store), [r15+0x8A8].

---

## Phase 63 — loc_672486f / loc_6724872: r14 reset + [rbp+0x2B0/0x2B8] + call 0x67A75D0 + stack setup (0x672486f..0x67248ef)

loc_672486f (xor r14d) falls into loc_6724872. rcx=[rbp+0x7B0]; [rbp+0x2B0]=rcx; [rbp+0x2B8]=r14. lea rdx=&[rbp+0x7B0]; rcx=[rdx+0x20]; lea r8=&[rbp+0x2A4]; [r8+0x2C]=rcx; movups xmm0=[rdx+0x10]; movups [r8+0x1C]=xmm0; ecx=[rbp+0x79C]; [rbp+0x2D8]=ecx; [rbp+0x2E0]=ax. lea rcx=&[rbp+0x510]; lea rdi=&[rbp+0x370]; rdx=rdi; call 0x67A75D0. [rsp+0x30]=&[rbp+0x2A0]; [rsp+0x28]=&[rbp+0x2D8]; [rsp+0x20]=&[rbp+0x2E0]. [V] per instruction quotes below.

```
loc_672486f:  ; from 67245e1
  672486f  xor r14d,r14d                                 

loc_6724872:  ; from 67245f2
  6724872  mov rcx,[rbp+0x7B0]                           
  6724879  mov [rbp+0x2B0],rcx                           
  6724880  mov [rbp+0x2B8],r14                           
  6724887  lea rdx,[rbp+0x7B0]                           
  672488e  mov rcx,[rdx+0x20]                            
  6724892  lea r8,[rbp+0x2A4]                            
  6724899  mov [r8+0x2C],rcx                             
  672489d  movups xmm0,[rdx+0x10]                        
  67248a1  movups [r8+0x1C],xmm0                         
  67248a6  mov ecx,[rbp+0x79C]                           
  67248ac  mov [rbp+0x2D8],ecx                           
  67248b2  mov [rbp+0x2E0],ax                            
  67248b9  lea rcx,[rbp+0x510]                           
  67248c0  lea rdi,[rbp+0x370]                           
  67248c7  mov rdx,rdi                                   
  67248ca  call 0x67A75D0                                ; -> sub_67a75d0
  67248cf  nop                                           
  67248d0  lea rax,[rbp+0x2A0]                           
  67248d7  mov [rsp+0x30],rax                            
  67248dc  lea rax,[rbp+0x2D8]                           
  67248e3  mov [rsp+0x28],rax                            
  67248e8  lea rax,[rbp+0x2E0]                           
  67248ef  mov [rsp+0x20],rax                            
```

Interpretation: r14d=0. rcx=[rbp+0x7B0]; [rbp+0x2B0]=rcx; [rbp+0x2B8]=r14. rdx=&[rbp+0x7B0]; rcx=[rdx+0x20]; r8=&[rbp+0x2A4]; [r8+0x2C]=rcx. movups xmm0=[rdx+0x10]; movups [r8+0x1C]=xmm0. ecx=[rbp+0x79C]; [rbp+0x2D8]=ecx; [rbp+0x2E0]=ax. rcx=&[rbp+0x510]; rdi=&[rbp+0x370]; rdx=rdi; call 0x67A75D0(rcx,rdx). [rsp+0x30]=&[rbp+0x2A0]; [rsp+0x28]=&[rbp+0x2D8]; [rsp+0x20]=&[rbp+0x2E0].

Callees: 0x67A75D0 (sub_67a75d0).
Fields read: [rbp+0x7B0], r14, rdx, [rdx+0x20], [rbp+0x2A4], [rdx+0x10], [rbp+0x79C], [rbp+0x510], rdi. Fields written: [rbp+0x2B0], [rbp+0x2B8], [rbp+0x2A4+0x2C], [rbp+0x2A4+0x1C], [rbp+0x2D8], [rbp+0x2E0], [rsp+0x30], [rsp+0x28], [rsp+0x20].

## Phase 64 — call 0x6791AF0 (&[rbp+0x560], &[rbp+0x450], &[rbp+0x3F8], rdi) (0x67248f4..0x6724911)

lea rcx=&[rbp+0x560]; lea rdx=&[rbp+0x450]; lea r8=&[rbp+0x3F8]; r9=rdi; call 0x6791AF0. [V] per instruction quotes below.

```
0x67248f4  lea rcx,[rbp+0x560]                           
0x67248fb  lea rdx,[rbp+0x450]                           
0x6724902  lea r8,[rbp+0x3F8]                            
0x6724909  mov r9,rdi                                    
0x672490c  call 0x6791AF0                                ; -> sub_6791af0
0x6724911  nop                                           
```

Interpretation: rcx=&[rbp+0x560]; rdx=&[rbp+0x450]; r8=&[rbp+0x3F8]; r9=rdi; call 0x6791AF0(rcx,rdx,r8,r9).

Callees: 0x6791AF0 (sub_6791af0).
Fields read: [rbp+0x560], [rbp+0x450], [rbp+0x3F8], rdi. Fields written: none (stack args only).

## Phase 65 — rbx field copy + call 0x5ABA5C0 + zero + TLS + word store + jump (0x6724912..0x6724a2a)

eax=[rbx+0x60]->[rbp+0x6D8+0x10]; xmm0=[rbx+0x50]->[rbp+0x6D8]; byte [rbp+0x4B4]->[rbp+0x6EC]; xmm0=[rbp+0x4B8]->[rbp+0x6F0]; xmm0-xmm2=[rbx+0x78/0x88/0x97]->[rbp+0x564+0x1BB/0x1AC/0x19C]; word [rbp+0x4F8]->[rbp+0x730]. rax=[rbp+0x808]; rcx=[rax+0x10]; rcx+=0x9D0; call 0x5ABA5C0; r15=rax. zero xmm6 [r13-0x28..0xD8] (13 stores). rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0]; [rbp+0x818]=al. rdx=[r15+0x8A8]; cmp [r15+0x8B0]; if equal jmp loc_6724E3D else word [rbp+0x730]->[rdx]; add qword [r15+0x8A8],2; jmp loc_6724E51. [V] per instruction quotes below.

```
0x6724912  mov eax,[rbx+0x60]                            
0x6724915  lea rcx,[rbp+0x6D8]                           
0x672491c  mov [rcx+0x10],eax                            
0x672491f  movups xmm0,[rbx+0x50]                        
0x6724923  movups [rcx],xmm0                             
0x6724926  movzx eax,byte ptr [rbp+0x4B4]                
0x672492d  mov [rbp+0x6EC],al                            
0x6724933  movups xmm0,[rbp+0x4B8]                       
0x672493a  movups [rbp+0x6F0],xmm0                       
0x6724941  movups xmm0,[rbx+0x78]                        
0x6724945  movups xmm1,[rbx+0x88]                        
0x672494c  movups xmm2,[rbx+0x97]                        
0x6724953  lea rax,[rbp+0x564]                           
0x672495a  movups [rax+0x1BB],xmm2                       
0x6724961  movups [rax+0x1AC],xmm1                       
0x6724968  movups [rax+0x19C],xmm0                       
0x672496f  movzx eax,word ptr [rbp+0x4F8]                
0x6724976  mov [rbp+0x730],ax                            
0x672497d  mov rax,[rbp+0x808]                           
0x6724984  mov rcx,[rax+0x10]                            
0x6724988  mov eax,0x9D0                                 
0x672498d  add rcx,rax                                   
0x6724990  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x6724995  nop                                           
0x6724996  mov r15,rax                                   
0x6724999  movups [r13-0x28],xmm6                        
0x672499e  movups [r13-0x38],xmm6                        
0x67249a3  movups [r13-0x48],xmm6                        
0x67249a8  movups [r13-0x58],xmm6                        
0x67249ad  movups [r13-0x68],xmm6                        
0x67249b2  movups [r13-0x78],xmm6                        
0x67249b7  movups [r13-0x88],xmm6                        
0x67249bf  movups [r13-0x98],xmm6                        
0x67249c7  movups [r13-0xA8],xmm6                        
0x67249cf  movups [r13-0xB8],xmm6                        
0x67249d7  movups [r13-0xC8],xmm6                        
0x67249df  movups [r13-0xD8],xmm6                        
0x67249e7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67249ee  mov rax,[rcx]                                 
0x67249f1  mov rax,[rax+0x10]                            
0x67249f5  mov dl,0x4A                                   
0x67249f7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67249fd  nop                                           
0x67249fe  mov [rbp+0x818],al                            
0x6724a04  mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x6724a0b  cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x6724a12  je 0x6724E3D                                  ; -> loc_6724e3d
0x6724a18  movzx eax,word ptr [rbp+0x730]                
0x6724a1f  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x6724a22  add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x6724a2a  jmp 0x6724E51                                 ; -> loc_6724e51
```

Interpretation: eax=[rbx+0x60]; rcx=&[rbp+0x6D8]; [rcx+0x10]=eax; xmm0=[rbx+0x50]->[rcx]. eax=byte [rbp+0x4B4]->[rbp+0x6EC]. xmm0=[rbp+0x4B8]->[rbp+0x6F0]. xmm0=[rbx+0x78],xmm1=[rbx+0x88],xmm2=[rbx+0x97]->[rbp+0x564+0x1BB]/[rbp+0x564+0x1AC]/[rbp+0x564+0x19C]. eax=word [rbp+0x4F8]->[rbp+0x730]. rax=[rbp+0x808], rcx=[rax+0x10], eax=0x9D0, rcx+=rax. Call 0x5ABA5C0; r15=rax. zero xmm6 [r13-0x28]..[r13-0xD8] (13 stores). rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call via [0xF99FFA0] (sub_eea6040); store al at [rbp+0x818]. rdx=[r15+0x8A8]; cmp with [r15+0x8B0]; if equal jump 0x6724E3D. Otherwise: eax=word [rbp+0x730]; store at [rdx]; add qword [r15+0x8A8],2; jmp 0x6724E51.

Callees: 0x5ABA5C0 (sub_5aba5c0), [0xF99FFA0]=sub_eea6040 (indirect).
Fields read: [rbx+0x60], [rbx+0x50], [rbp+0x4B4], [rbp+0x4B8], [rbx+0x78], [rbx+0x88], [rbx+0x97], [rbp+0x4F8], [rbp+0x808], [rax+0x10], [r13-0x28..0xD8] (writes), [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8B0], [rbp+0x730]. Fields written: [rbp+0x6D8+0x10], [rbp+0x6D8], [rbp+0x6EC], [rbp+0x6F0], [rbp+0x564+0x1BB], [rbp+0x564+0x1AC], [rbp+0x564+0x19C], [rbp+0x730], [r15], [r13-0x28]..[r13-0xD8], [rbp+0x818], [rdx] (word store), [r15+0x8A8].

## Phase 66 — call 0x1EF6F90 + TLS start (0x6724a2f..0x6724a4a, 800th instr)

lea rcx=[r14+0x8A0]; lea r8=&[rbp+0x6F0]; call 0x1EF6F90. lea rcx=[0x1233E1B0]; mov rax,[rcx] (800th instruction; next would be rax=[rax+0x10] at 0x6724a4d). [V] per instruction quotes below.

```
0x6724a2f  lea rcx,[r14+0x8A0]                           
0x6724a36  lea r8,[rbp+0x6F0]                            
0x6724a3d  call 0x1EF6F90                                ; -> sub_1ef6f90
0x6724a42  nop                                           
0x6724a43  lea rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6724a4a  mov rax,[rcx]                                 
```
(--max 800 reached after this instruction)

Interpretation: rcx=[r14+0x8A0]; r8=&[rbp+0x6F0]; call 0x1EF6F90(rcx,r8). rcx=[0x1233E1B0]; rax=[rcx] (800th instruction).

Callees: 0x1EF6F90 (sub_1ef6f90).
Fields read: [r14+0x8A0], [rbp+0x6F0], [0x1233E1B0], [rcx]. Fields written: none yet (rax loaded).

---

## Status
DONE - 800 instructions covered (0x6723971..0x6724a4a inclusive). Resume at 0x6724a4d (`mov rax,[rax+0x10]`).

File: docs/progress/oc_U-E4-H2.md (only file edited). Phases 30-66 appended.
