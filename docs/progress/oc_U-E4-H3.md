# U-E4-H3 — sub_6722cb0 continuation (builder 0x6722cb0)

H1 = docs/progress/oc_U-E4-H1.md covered phases 1-29, instructions 0x6722cb0..0x672396c.
H2 = docs/progress/oc_U-E4-H2.md covered phases 30-66, instructions 0x6723971..0x6724a4a.
H3 resumes at 0x6724a4d (the instruction after 0x6724a4a `mov rax,[rcx]`). Static analysis only. Tags: [V]=seen in disasm, [I]=inferred, [?]=unknown.

## NEXT
Resume at 0x6725004 (the instruction after 0x6724fff `movss [rdx+0x1C],xmm0`, which is the 280th instruction covered). Continue appending phases from there until 800 instructions consumed or rate limit.

---

## Phase 7 — xmm2 store + add qword + jump + TLS seq + [r15+0x758]->[r15+0x760] copy #7 (0x6724f37..0x6725004)

xmm2 store at [rdx+0x47], add qword [r15+0x758],0x58, jmp loc_67252A7. Fall-through block at 0x6724f48: lea rcx=[r15+0x8A0]; lea r8=[rbp+0x740]; call 0x1EF6F90; TLS seq (mov rcx=[0x1233E1B0]; mov rax=[rcx]; mov rax=[rax+0x10]; movzx edx,byte [rbp+0x818]; call via [0xF99FFA0]; [rbp+0x818]=al). Count calc [r15+0x8A8]-[r15+0x8A0]>>1-1 -> [rbp+0x120]. TLS call dl=0x4A via [0xF99FFA0]. If [r15+0x758]==[r15+0x760] jump loc_6725323. Else copy [rbp+0x6E8] to [rdx] (dword+movups+byte+3 movss so far). [V] per instruction quotes below.

```
0x6724f37  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6724f3b  add qword ptr [r15+0x758],0x58                
  6724f43  jmp 0x67252A7                                 ; -> loc_67252a7
  6724f48  lea rcx,[r15+0x8A0]                           
  6724f4f  lea r8,[rbp+0x740]                            
  6724f56  call 0x1EF6F90                                ; -> sub_1ef6f90
  6724f5b  nop                                           
  6724f5c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724f63  mov rax,[rcx]                                 
  6724f66  mov rax,[rax+0x10]                            
  6724f6a  movzx edx,byte ptr [rbp+0x818]                
  6724f71  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724f77  nop                                           
  6724f78  mov qword ptr [rbp+0x110],1                   
  6724f83  mov eax,[r15+0x8A8]                           
  6724f8a  sub eax,[r15+0x8A0]                           
  6724f91  shr eax,1                                     
  6724f93  dec eax                                       
  6724f95  mov [rbp+0x120],ax                            
  6724f9c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724fa3  mov rax,[rcx]                                 
  6724fa6  mov rax,[rax+0x10]                            
  6724faa  mov dl,0x4A                                   
  6724fac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724fb2  nop                                           
  6724fb3  mov [rbp+0x818],al                            
  6724fb9  mov rdx,[r15+0x758]                           
  6724fc0  cmp rdx,[r15+0x760]                           
  6724fc7  je 0x6725323                                  ; -> loc_6725323
  6724fcd  lea rcx,[rbp+0x6E8]                           
  6724fd4  mov eax,[rcx+0x10]                            
  6724fd7  mov [rdx+0x10],eax                            
  6724fda  movups xmm0,[rcx]                             
  6724fdd  movups [rdx],xmm0                             
  6724fe0  movzx eax,byte ptr [rbp+0x6FC]                
  6724fe7  mov [rdx+0x14],al                             
  6724fea  movss xmm0,[rbp+0x700]                        
  6724ff2  movss [rdx+0x18],xmm0                         
  6724ff7  movss xmm0,[rbp+0x704]                        
  6724fff  movss [rdx+0x1C],xmm0                         
```

Interpretation: movups [rdx+0x47],xmm2. add qword [r15+0x758],0x58. jmp 0x67252A7. (Block at 0x6724f48) lea rcx,[r15+0x8A0]; lea r8,[rbp+0x740]; call 0x1EF6F90. mov rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; movzx edx,byte [rbp+0x818]; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. mov qword [rbp+0x110],1. eax=[r15+0x8A8]; sub eax,[r15+0x8A0]; shr eax,1; dec eax; mov [rbp+0x120],ax. rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; mov dl,0x4A; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. rdx=[r15+0x758]; cmp rdx,[r15+0x760]; if equal je 0x6725323. rcx=&[rbp+0x6E8]; eax=[rcx+0x10]; mov [rdx+0x10],eax. movups xmm0=[rcx]; movups [rdx],xmm0. movzx eax,byte [rbp+0x6FC]; mov [rdx+0x14],al. movss xmm0=[rbp+0x700]->[rdx+0x18]; movss xmm0=[rbp+0x704]->[rdx+0x1C].

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rdx+0x47], [r15+0x758], [r15+0x8A0], r8, [rbp+0x740], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x818], [r15+0x8A8], [r15+0x8A0], [r15+0x758], [r15+0x760], [rbp+0x6E8], [rcx+0x10], [rcx], [rbp+0x6FC], [rdx+0x14], [rbp+0x700], [rdx+0x18], [rbp+0x704], [rdx+0x1C]. Fields written: [rdx+0x47], [r15+0x758], [rbp+0x110], [rbp+0x120], [rbp+0x818], [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C].

---


## Phase 6 — TLS call end #2 + field count + [r15+0x758]->[r15+0x760] copy #6 + jump target (0x6724e5f..0x6724f37)

TLS call end #2: movzx edx,byte [rbp+0x818]; call via [0xF99FFA0]; [rbp+0x818]=al. mov qword [rbp+0x110],1. Count calc [r15+0x8A8]-[r15+0x8A0]>>1-1 -> [rbp+0x120]. TLS call dl=0x4A via [0xF99FFA0]. If [r15+0x758]==[r15+0x760] jump loc_6725293. Else copy [rbp+0x6D8] to [rdx] (dword+movups+byte+5 movss+movups xmm0-xmm2 from [rbp+0x564+0x19C/0x1AC/0x1BB] -> [rdx+0x28/0x38/0x47]). [V] per instruction quotes below.

```
0x6724e5f  movzx edx,byte ptr [rbp+0x818]                
  6724e66  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724e6c  nop                                           
  6724e6d  mov qword ptr [rbp+0x110],1                   
  6724e78  mov eax,[r15+0x8A8]                           
  6724e7f  sub eax,[r15+0x8A0]                           
  6724e86  shr eax,1                                     
  6724e88  dec eax                                       
  6724e8a  mov [rbp+0x120],ax                            
  6724e91  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724e98  mov rax,[rcx]                                 
  6724e9b  mov rax,[rax+0x10]                            
  6724e9f  mov dl,0x4A                                   
  6724ea1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724ea7  nop                                           
  6724ea8  mov [rbp+0x818],al                            
  6724eae  mov rdx,[r15+0x758]                           
  6724eb5  cmp rdx,[r15+0x760]                           
  6724ebc  je 0x6725293                                  ; -> loc_6725293
  6724ec2  lea rcx,[rbp+0x6D8]                           
  6724ec9  mov eax,[rcx+0x10]                            
  6724ecc  mov [rdx+0x10],eax                            
  6724ecf  movups xmm0,[rcx]                             
  6724ed2  movups [rdx],xmm0                             
  6724ed5  movzx eax,byte ptr [rbp+0x6EC]                
  6724edc  mov [rdx+0x14],al                             
  6724edf  movss xmm0,[rbp+0x6F0]                        
  6724ee7  movss [rdx+0x18],xmm0                         
  6724eec  movss xmm0,[rbp+0x6F4]                        
  6724ef4  movss [rdx+0x1C],xmm0                         
  6724ef9  movss xmm0,[rbp+0x6F8]                        
  6724f01  movss [rdx+0x20],xmm0                         
  6724f06  movss xmm0,[rbp+0x6FC]                        
  6724f0e  movss [rdx+0x24],xmm0                         
  6724f13  lea rax,[rbp+0x564]                           
  6724f1a  movups xmm0,[rax+0x19C]                       
  6724f21  movups xmm1,[rax+0x1AC]                       
  6724f28  movups xmm2,[rax+0x1BB]                       
  6724f2f  movups [rdx+0x28],xmm0                        
  6724f33  movups [rdx+0x38],xmm1                        
```

Interpretation: movzx edx,byte [rbp+0x818]; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. mov qword [rbp+0x110],1. eax=[r15+0x8A8]; sub eax,[r15+0x8A0]; shr eax,1; dec eax; mov [rbp+0x120],ax. rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; mov dl,0x4A; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. rdx=[r15+0x758]; cmp rdx,[r15+0x760]; if equal je 0x6725293. rcx=&[rbp+0x6D8]; eax=[rcx+0x10]; mov [rdx+0x10],eax. movups xmm0=[rcx]; movups [rdx],xmm0. movzx eax,byte [rbp+0x6EC]; mov [rdx+0x14],al. movss xmm0=[rbp+0x6F0]->[rdx+0x18]; movss xmm0=[rbp+0x6F4]->[rdx+0x1C]; movss xmm0=[rbp+0x6F8]->[rdx+0x20]; movss xmm0=[rbp+0x6FC]->[rdx+0x24]. lea rax=[rbp+0x564]; movups xmm0=[rax+0x19C], xmm1=[rax+0x1AC], xmm2=[rax+0x1BB]; movups [rdx+0x28]=xmm0, [rdx+0x38]=xmm1.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rbp+0x818], [r15+0x8A8], [r15+0x8A0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x818], [r15+0x758], [r15+0x760], [rbp+0x6D8], [rcx+0x10], [rcx], [rbp+0x6EC], [rdx+0x14], [rbp+0x6F0], [rdx+0x18], [rbp+0x6F4], [rdx+0x1C], [rbp+0x6F8], [rdx+0x20], [rbp+0x6FC], [rdx+0x24], [rbp+0x564+0x19C], [rbp+0x564+0x1AC], [rbp+0x564+0x1BB], [rdx+0x28], [rdx+0x38]. Fields written: [rbp+0x818], [rbp+0x110], [rbp+0x120], [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38].

---


## Phase 5 — TLS call end + field count + [r14+0x758]->[r14+0x760] copy #5 + jump target + TLS start #6 (0x6724d97..0x6724e5f)

TLS call end: mov rax,[rcx]; mov rax,[rax+0x10]; mov dl,0x4A; call via [0xF99FFA0]; [rbp+0x818]=al. If [r14+0x758]==[r14+0x760] jump loc_6725203. Else copy [rbp+0x6B0] to [rdx] (dword+movups+byte+5 movss+movups xmm0-xmm2 from [rbp+0x6D8] -> [rdx+0x28/0x38/0x47]). add qword [r14+0x758],0x58; jmp loc_6725217. Fall-through block at 0x6724e3d: lea rcx=[r15+0x8A0]; lea r8=[rbp+0x730]; call 0x1EF6F90; TLS seq starts (mov rcx=[0x1233E1B0]; mov rax,[rcx]; mov rax,[rax+0x10] continues next phase). [V] per instruction quotes below.

```
0x6724d97  mov rax,[rcx]                                 ; R a0+0x0
  6724d9a  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  6724d9e  mov dl,0x4A                                   
  6724da0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724da6  nop                                           
  6724da7  mov [rbp+0x818],al                            
  6724dad  mov rdx,[r14+0x758]                           
  6724db4  cmp rdx,[r14+0x760]                           
  6724dbb  je 0x6725203                                  ; -> loc_6725203
  6724dc1  lea rcx,[rbp+0x6B0]                           
  6724dc8  mov eax,[rcx+0x10]                            
  6724dcb  mov [rdx+0x10],eax                            
  6724dce  movups xmm0,[rcx]                             
  6724dd1  movups [rdx],xmm0                             
  6724dd4  movzx eax,byte ptr [rbp+0x6C4]                
  6724ddb  mov [rdx+0x14],al                             
  6724dde  movss xmm0,[rbp+0x6C8]                        
  6724de6  movss [rdx+0x18],xmm0                         
  6724deb  movss xmm0,[rbp+0x6CC]                        
  6724df3  movss [rdx+0x1C],xmm0                         
  6724df8  movss xmm0,[rbp+0x6D0]                        
  6724e00  movss [rdx+0x20],xmm0                         
  6724e05  movss xmm0,[rbp+0x6D4]                        
  6724e0d  movss [rdx+0x24],xmm0                         
  6724e12  lea rax,[rbp+0x6D8]                           
  6724e19  movups xmm0,[rax]                             
  6724e1c  movups xmm1,[rax+0x10]                        
  6724e20  movups xmm2,[rax+0x1F]                        
  6724e24  movups [rdx+0x28],xmm0                        
  6724e28  movups [rdx+0x38],xmm1                        
  6724e2c  movups [rdx+0x47],xmm2                        
  6724e30  add qword ptr [r14+0x758],0x58                
  6724e38  jmp 0x6725217                                 ; -> loc_6725217
  6724e3d  lea rcx,[r15+0x8A0]                           
  6724e44  lea r8,[rbp+0x730]                            
  6724e4b  call 0x1EF6F90                                ; -> sub_1ef6f90
  6724e50  nop                                           
  6724e51  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724e58  mov rax,[rcx]                                 
  6724e5b  mov rax,[rax+0x10]                            
```

Interpretation: mov rax=[rcx]; mov rax=[rax+0x10]; mov dl,0x4A; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. rdx=[r14+0x758]; cmp rdx,[r14+0x760]; if equal je 0x6725203. rcx=&[rbp+0x6B0]; eax=[rcx+0x10]; mov [rdx+0x10],eax. movups xmm0=[rcx]; movups [rdx],xmm0. movzx eax,byte [rbp+0x6C4]; mov [rdx+0x14],al. movss xmm0=[rbp+0x6C8]->[rdx+0x18]; movss xmm0=[rbp+0x6CC]->[rdx+0x1C]; movss xmm0=[rbp+0x6D0]->[rdx+0x20]; movss xmm0=[rbp+0x6D4]->[rdx+0x24]. lea rax=[rbp+0x6D8]; movups xmm0=[rax], xmm1=[rax+0x10], xmm2=[rax+0x1F]; movups [rdx+0x28]=xmm0, [rdx+0x38]=xmm1, [rdx+0x47]=xmm2. add qword [r14+0x758],0x58. jmp 0x6725217. (Block at 0x6724e3d) lea rcx,[r15+0x8A0]; lea r8,[rbp+0x730]; call 0x1EF6F90. mov rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10] (continues next phase).

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x1EF6F90 (sub_1ef6f90).
Fields read: [rcx], [rax+0x10], [rbp+0x818], [r14+0x758], [r14+0x760], [rbp+0x6B0], [rcx+0x10], [rcx], [rbp+0x6C4], [rdx+0x14], [rbp+0x6C8], [rdx+0x18], [rbp+0x6CC], [rdx+0x1C], [rbp+0x6D0], [rdx+0x20], [rbp+0x6D4], [rdx+0x24], [rbp+0x6D8], [rax], [rax+0x10], [rax+0x1F], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758], [r15+0x8A0], r8, [rbp+0x730], [0x1233E1B0], [rcx], [rax+0x10]. Fields written: [rbp+0x818], [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758].

---


## Phase 4 — [rbp+0x6A0] copy complete + add qword + jump + TLS seq + [r14+0x758]->[r14+0x760] copy #4 (0x6724cc7..0x6724d97)

Completes the [rbp+0x6A0] copy to [rdx] (dword+movups+byte+5 movss+movups xmm0-xmm2 from [rbp+0x6C8] -> [rdx+0x28/0x38/0x47]). add qword [r14+0x758],0x58; jmp loc_6725187. Fall-through block at 0x6724d3c: lea rcx=[r14+0x8A0]; lea r8=[rbp+0x708]; call 0x1EF6F90; TLS seq; count calc -> [rbp+0x120]; second TLS call starts (mov rcx=[0x1233E1B0] at 0x6724d90 continues next phase). [V] per instruction quotes below.

```
0x6724cc7  mov eax,[rcx+0x10]                            ; R a0+0x10
  6724cca  mov [rdx+0x10],eax                            ; W a1+0x10
  6724ccd  movups xmm0,[rcx]                             ; R a0+0x0
  6724cd0  movups [rdx],xmm0                             ; W a1+0x0
  6724cd3  movzx eax,byte ptr [rbp+0x6B4]                
  6724cda  mov [rdx+0x14],al                             ; W a1+0x14
  6724cdd  movss xmm0,[rbp+0x6B8]                        
  6724ce5  movss [rdx+0x18],xmm0                         ; W a1+0x18
  6724cea  movss xmm0,[rbp+0x6BC]                        
  6724cf2  movss [rdx+0x1C],xmm0                         ; W a1+0x1C
  6724cf7  movss xmm0,[rbp+0x6C0]                        
  6724cff  movss [rdx+0x20],xmm0                         ; W a1+0x20
  6724d04  movss xmm0,[rbp+0x6C4]                        
  6724d0c  movss [rdx+0x24],xmm0                         ; W a1+0x24
  6724d11  lea rax,[rbp+0x6C8]                           
  6724d18  movups xmm0,[rax]                             
  6724d1b  movups xmm1,[rax+0x10]                        
  6724d1f  movups xmm2,[rax+0x1F]                        
  6724d23  movups [rdx+0x28],xmm0                        ; W a1+0x28
  6724d27  movups [rdx+0x38],xmm1                        ; W a1+0x38
  6724d2b  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6724d2f  add qword ptr [r14+0x758],0x58                
  6724d37  jmp 0x6725187                                 ; -> loc_6725187
  6724d3c  lea rcx,[r14+0x8A0]                           
  6724d43  lea r8,[rbp+0x708]                            
  6724d4a  call 0x1EF6F90                                ; -> sub_1ef6f90
  6724d4f  nop                                           
  6724d50  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724d57  mov rax,[rcx]                                 
  6724d5a  mov rax,[rax+0x10]                            
  6724d5e  movzx edx,byte ptr [rbp+0x818]                
  6724d65  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724d6b  nop                                           
  6724d6c  mov qword ptr [rbp+0x110],1                   
  6724d77  mov eax,[r14+0x8A8]                           
  6724d7e  sub eax,[r14+0x8A0]                           
  6724d85  shr eax,1                                     
  6724d87  dec eax                                       
  6724d89  mov [rbp+0x120],ax                            
  6724d90  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```

Interpretation: mov eax,[rcx+0x10]; mov [rdx+0x10],eax. movups xmm0=[rcx]; movups [rdx],xmm0. movzx eax,byte [rbp+0x6B4]; mov [rdx+0x14],al. movss xmm0=[rbp+0x6B8]->[rdx+0x18]; movss xmm0=[rbp+0x6BC]->[rdx+0x1C]; movss xmm0=[rbp+0x6C0]->[rdx+0x20]; movss xmm0=[rbp+0x6C4]->[rdx+0x24]. lea rax=[rbp+0x6C8]; movups xmm0=[rax], xmm1=[rax+0x10], xmm2=[rax+0x1F]; movups [rdx+0x28]=xmm0, [rdx+0x38]=xmm1, [rdx+0x47]=xmm2. add qword [r14+0x758],0x58. jmp 0x6725187. (Block at 0x6724d3c) lea rcx,[r14+0x8A0]; lea r8,[rbp+0x708]; call 0x1EF6F90. mov rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; movzx edx,byte [rbp+0x818]; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. mov qword [rbp+0x110],1. eax=[r14+0x8A8]; sub eax,[r14+0x8A0]; shr eax,1; dec eax; mov [rbp+0x120],ax. mov rcx=[0x1233E1B0] (continues next phase).

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [rcx+0x10], [rdx+0x10], [rcx], [rdx], [rbp+0x6B4], [rdx+0x14], [rbp+0x6B8], [rdx+0x18], [rbp+0x6BC], [rdx+0x1C], [rbp+0x6C0], [rdx+0x20], [rbp+0x6C4], [rdx+0x24], [rbp+0x6C8], [rax], [rax+0x10], [rax+0x1F], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758], [r14+0x8A0], r8, [rbp+0x708], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x818], [r14+0x8A8], [r14+0x8A0], [r14+0x758], [r14+0x760]. Fields written: [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758], [rbp+0x110], [rbp+0x120], [rbp+0x818].

---


## Phase 1 — TLS call + field count + [r14+0x758]->[r14+0x760] struct copy + byte/float stores + xmm load (0x6724a4d..0x6724b29)

Continuation of the TLS sequence from H2 Phase 66: rax=[rax+0x10]; movzx edx,byte [rbp+0x818]; call via [0xF99FFA0] (sub_eea6040). Then field count calculation [r14+0x8A8]-[r14+0x8A0]>>1-1 -> [rbp+0x120]. Second TLS call dl=0x4A -> [rbp+0x818]. If [r14+0x758]==[r14+0x760] jump loc_6725053. Else copy [rbp+0x698] (dword+movups+byte+4 movss) to [rdx] where rdx=[r14+0x758]. Then load xmm0-xmm2 from [rbp+0x564+0x15C/0x16C/0x17B]. [V] per instruction quotes below.

```
0x6724a4d  mov rax,[rax+0x10]                            
  6724a51  movzx edx,byte ptr [rbp+0x818]                
  6724a58  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724a5e  nop                                           
  6724a5f  mov qword ptr [rbp+0x110],1                   
  6724a6a  mov eax,[r14+0x8A8]                           
  6724a71  sub eax,[r14+0x8A0]                           
  6724a78  shr eax,1                                     
  6724a7a  dec eax                                       
  6724a7c  mov [rbp+0x120],ax                            
  6724a83  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724a8a  mov rax,[rcx]                                 
  6724a8d  mov rax,[rax+0x10]                            
  6724a91  mov dl,0x4A                                   
  6724a93  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724a99  nop                                           
  6724a9a  mov [rbp+0x818],al                            
  6724aa0  mov rdx,[r14+0x758]                           
  6724aa7  cmp rdx,[r14+0x760]                           
  6724aae  je 0x6725053                                  ; -> loc_6725053
  6724ab4  lea rcx,[rbp+0x698]                           
  6724abb  mov eax,[rcx+0x10]                            
  6724abe  mov [rdx+0x10],eax                            
  6724ac1  movups xmm0,[rcx]                             
  6724ac4  movups [rdx],xmm0                             
  6724ac7  movzx eax,byte ptr [rbp+0x6AC]                
  6724ace  mov [rdx+0x14],al                             
  6724ad1  movss xmm0,[rbp+0x6B0]                        
  6724ad9  movss [rdx+0x18],xmm0                         
  6724ade  movss xmm0,[rbp+0x6B4]                        
  6724ae6  movss [rdx+0x1C],xmm0                         
  6724aeb  movss xmm0,[rbp+0x6B8]                        
  6724af3  movss [rdx+0x20],xmm0                         
  6724af8  movss xmm0,[rbp+0x6BC]                        
  6724b00  movss [rdx+0x24],xmm0                         
  6724b05  lea rax,[rbp+0x564]                           
  6724b0c  movups xmm0,[rax+0x15C]                       
  6724b13  movups xmm1,[rax+0x16C]                       
  6724b1a  movups xmm2,[rax+0x17B]                       
  6724b21  movups [rdx+0x28],xmm0                        
```

Interpretation: rax=[rax+0x10] (continuing from 0x6724a4a `mov rax,[rcx]`). movzx edx,byte [rbp+0x818]; call qword ptr [0xF99FFA0] (sub_eea6040). mov qword [rbp+0x110],1. eax=[r14+0x8A8]; sub eax,[r14+0x8A0]; shr eax,1; dec eax; mov [rbp+0x120],ax. rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. rdx=[r14+0x758]; cmp rdx,[r14+0x760]; if equal je 0x6725053. rcx=&[rbp+0x698]; eax=[rcx+0x10]; mov [rdx+0x10],eax. movups xmm0=[rcx]; movups [rdx],xmm0. movzx eax,byte [rbp+0x6AC]; mov [rdx+0x14],al. movss xmm0=[rbp+0x6B0]->[rdx+0x18]; movss xmm0=[rbp+0x6B4]->[rdx+0x1C]; movss xmm0=[rbp+0x6B8]->[rdx+0x20]; movss xmm0=[rbp+0x6BC]->[rdx+0x24]. rax=&[rbp+0x564]; xmm0=[rax+0x15C], xmm1=[rax+0x16C], xmm2=[rax+0x17B]; movups [rdx+0x28],xmm0.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rax+0x10], [rbp+0x818], [r14+0x8A8], [r14+0x8A0], [0x1233E1B0], [rcx], [rax+0x10], [r14+0x758], [r14+0x760], [rbp+0x698], [rcx+0x10], [rcx], [rbp+0x6AC], [rbp+0x6B0], [rbp+0x6B4], [rbp+0x6B8], [rbp+0x6BC], [rbp+0x564+0x15C], [rbp+0x564+0x16C], [rbp+0x564+0x17B]. Fields written: [rbp+0x110], [rbp+0x120], [rbp+0x818], [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28].

---

## Phase 2 — xmm2 store + add qword + jump + TLS seq + [r14+0x758]->[r14+0x760] copy #2 (0x6724b29..0x6724bf8)

Jump target from Phase 1's fallthrough (when je not taken at 0x6724aa7). Stores xmm2 at [rdx+0x47], adds 0x58 to [r14+0x758], jmp loc_6725067. Fall-through block at 0x6724b3a (je target): lea rcx=[r14+0x8A0]; lea r8=[rbp+0x6F8]; call 0x1EF6F90; TLS seq (rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; movzx edx,byte [rbp+0x818]; call via [0xF99FFA0]; [rbp+0x818]=al). Then count calc again -> [rbp+0x120]. Second TLS call dl=0x4A. If [r14+0x758]==[r14+0x760] jump loc_67250E3. Else copy [rbp+0x6A0] to [rdx] (dword+movups+byte+3 movss so far). [V] per instruction quotes below.

```
0x6724b29  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6724b2d  add qword ptr [r14+0x758],0x58                
  6724b35  jmp 0x6725067                                 ; -> loc_6725067
  6724b3a  lea rcx,[r14+0x8A0]                           
  6724b41  lea r8,[rbp+0x6F8]                            
  6724b48  call 0x1EF6F90                                ; -> sub_1ef6f90
  6724b4d  nop                                           
  6724b4e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724b55  mov rax,[rcx]                                 
  6724b58  mov rax,[rax+0x10]                            
  6724b5c  movzx edx,byte ptr [rbp+0x818]                
  6724b63  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724b69  nop                                           
  6724b6a  mov qword ptr [rbp+0x110],1                   
  6724b75  mov eax,[r14+0x8A8]                           
  6724b7c  sub eax,[r14+0x8A0]                           
  6724b83  shr eax,1                                     
  6724b85  dec eax                                       
  6724b87  mov [rbp+0x120],ax                            
  6724b8e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724b95  mov rax,[rcx]                                 
  6724b98  mov rax,[rax+0x10]                            
  6724b9c  mov dl,0x4A                                   
  6724b9e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724ba4  nop                                           
  6724ba5  mov [rbp+0x818],al                            
  6724bab  mov rdx,[r14+0x758]                           
  6724bb2  cmp rdx,[r14+0x760]                           
  6724bb9  je 0x67250E3                                  ; -> loc_67250e3
  6724bbf  lea rcx,[rbp+0x6A0]                           
  6724bc6  mov eax,[rcx+0x10]                            
  6724bc9  mov [rdx+0x10],eax                            
  6724bcc  movups xmm0,[rcx]                             
  6724bcf  movups [rdx],xmm0                             
  6724bd2  movzx eax,byte ptr [rbp+0x6B4]                
  6724bd9  mov [rdx+0x14],al                             
  6724bdc  movss xmm0,[rbp+0x6B8]                        
  6724be4  movss [rdx+0x18],xmm0                         
  6724be9  movss xmm0,[rbp+0x6BC]                        
  6724bf1  movss [rdx+0x1C],xmm0                         
```

Interpretation: movups [rdx+0x47],xmm2. add qword [r14+0x758],0x58. jmp 0x6725067. (Block at 0x6724b3a) lea rcx,[r14+0x8A0]; lea r8,[rbp+0x6F8]; call 0x1EF6F90. mov rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; movzx edx,byte [rbp+0x818]; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. mov qword [rbp+0x110],1. eax=[r14+0x8A8]; sub eax,[r14+0x8A0]; shr eax,1; dec eax; mov [rbp+0x120],ax. rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. rdx=[r14+0x758]; cmp rdx,[r14+0x760]; if equal je 0x67250E3. rcx=&[rbp+0x6A0]; eax=[rcx+0x10]; mov [rdx+0x10],eax. movups xmm0=[rcx]; movups [rdx],xmm0. movzx eax,byte [rbp+0x6B4]; mov [rdx+0x14],al. movss xmm0=[rbp+0x6B8]->[rdx+0x18]; movss xmm0=[rbp+0x6BC]->[rdx+0x1C].

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rdx+0x47], [r14+0x758], [r14+0x8A0], r8, [rbp+0x6F8], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x818], [r14+0x8A8], [r14+0x8A0], [r14+0x758], [r14+0x760], [rbp+0x6A0], [rcx+0x10], [rcx], [rbp+0x6B4], [rbp+0x6B8], [rbp+0x6BC]. Fields written: [rdx+0x47], [r14+0x758], [rbp+0x110], [rbp+0x120], [rbp+0x818], [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C].

---

## Phase 3 — adc byte + movss/xmm stores + add qword + jump + TLS seq + [r14+0x758]->[r14+0x760] copy #3 (0x6724bf8..0x6724cc7)

Fall-through from Phase 2's je-not-taken path (the `movss [rdx+0x20],xmm0` store at 0x6724bfe was preceded by `adc [rbp+0x6C0],al` at 0x6724bf8). Completes the [rbp+0x6A0] copy to [rdx] (movss [rdx+0x20], byte [rbp+0x6C4]->[rdx+0x24], movups xmm0-xmm2 from [rbp+0x6C8] -> [rdx+0x28/0x38/0x47]). add qword [r14+0x758],0x58; jmp loc_67250F7. Fall-through block at 0x6724c3b: lea rcx=[r14+0x8A0]; lea r8=[rbp+0x6F8]; call 0x1EF6F90; TLS seq; count calc -> [rbp+0x120]; second TLS call dl=0x4A. If [r14+0x758]==[r14+0x760] jump loc_6725173. Else lea rcx=[rbp+0x6A0] (copy continues next phase). [V] per instruction quotes below.

```
0x6724bf8  adc [rbp+0x6C0],al                            
  6724bfe  movss [rdx+0x20],xmm0                         ; W a1+0x20
  6724c03  movss xmm0,[rbp+0x6C4]                        
  6724c0b  movss [rdx+0x24],xmm0                         ; W a1+0x24
  6724c10  lea rax,[rbp+0x6C8]                           
  6724c17  movups xmm0,[rax]                             
  6724c1a  movups xmm1,[rax+0x10]                        
  6724c1e  movups xmm2,[rax+0x1F]                        
  6724c22  movups [rdx+0x28],xmm0                        ; W a1+0x28
  6724c26  movups [rdx+0x38],xmm1                        ; W a1+0x38
  6724c2a  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6724c2e  add qword ptr [r14+0x758],0x58                
  6724c36  jmp 0x67250F7                                 ; -> loc_67250f7
  6724c3b  lea rcx,[r14+0x8A0]                           
  6724c42  lea r8,[rbp+0x6F8]                            
  6724c49  call 0x1EF6F90                                ; -> sub_1ef6f90
  6724c4e  nop                                           
  6724c4f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724c56  mov rax,[rcx]                                 
  6724c59  mov rax,[rax+0x10]                            
  6724c5d  movzx edx,byte ptr [rbp+0x818]                
  6724c64  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724c6a  nop                                           
  6724c6b  mov qword ptr [rbp+0x110],1                   
  6724c76  mov eax,[r14+0x8A8]                           
  6724c7d  sub eax,[r14+0x8A0]                           
  6724c84  shr eax,1                                     
  6724c86  dec eax                                       
  6724c88  mov [rbp+0x120],ax                            
  6724c8f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6724c96  mov rax,[rcx]                                 
  6724c99  mov rax,[rax+0x10]                            
  6724c9d  mov dl,0x4A                                   
  6724c9f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6724ca5  nop                                           
  6724ca6  mov [rbp+0x818],al                            
  6724cac  mov rdx,[r14+0x758]                           
  6724cb3  cmp rdx,[r14+0x760]                           
  6724cba  je 0x6725173                                  ; -> loc_6725173
  6724cc0  lea rcx,[rbp+0x6A0]                           
```

Interpretation: adc [rbp+0x6C0],al. movss [rdx+0x20],xmm0. movss xmm0=[rbp+0x6C4]; movss [rdx+0x24],xmm0. lea rax=[rbp+0x6C8]; movups xmm0=[rax], xmm1=[rax+0x10], xmm2=[rax+0x1F]; movups [rdx+0x28]=xmm0, [rdx+0x38]=xmm1, [rdx+0x47]=xmm2. add qword [r14+0x758],0x58. jmp 0x67250F7. (Block at 0x6724c3b) lea rcx,[r14+0x8A0]; lea r8,[rbp+0x6F8]; call 0x1EF6F90. mov rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; movzx edx,byte [rbp+0x818]; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. mov qword [rbp+0x110],1. eax=[r14+0x8A8]; sub eax,[r14+0x8A0]; shr eax,1; dec eax; mov [rbp+0x120],ax. rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword ptr [0xF99FFA0]; mov [rbp+0x818],al. rdx=[r14+0x758]; cmp rdx,[r14+0x760]; if equal je 0x6725173. lea rcx=[rbp+0x6A0].

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rbp+0x6C0], al, [rdx+0x20], [rbp+0x6C4], [rdx+0x24], [rbp+0x6C8], [rax], [rax+0x10], [rax+0x1F], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758], [r14+0x8A0], r8, [rbp+0x6F8], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x818], [r14+0x8A8], [r14+0x8A0], [r14+0x758], [r14+0x760], [rbp+0x6A0]. Fields written: [rbp+0x6C0], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r14+0x758], [rbp+0x110], [rbp+0x120], [rbp+0x818].

---
