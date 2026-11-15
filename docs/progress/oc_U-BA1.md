# Unit U-BA1 — bodyActor function 0x66d0a00 (1.26.62.01)

## Context [V]
- docs/BGFX_MAP.md line ~1438: `0x66d0a00 bodyActor pass (0x738b)` — a render-relevant big function, size about 0x738b bytes.
- docs/functions/66d9af0_builders.md: batch-actor extractor family at 0x66d9af0; bodyActor is a related pass in extractors-core.
- Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game is closed.

## NEXT
Resume at RVA 0x66d0a00. Run:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d0a00 40`
Then continue in 40-instruction phases: next phase starts at the RVA after the last instruction of this phase. On any `(bad)` line, restart the phase at the next address after the bad line. Append each phase right after this block in this file: exact `0xRVA  mnemonic operands` lines, then `// interpretation` tagged [V]/[I]/[?]. Every instruction in range 0x66d0a00..0x66d0a00+~0x738b belongs to a phase; instruction-complete (no "etc."). First 800 instructions are the unit scope.

## Phase 1 — 0x66d0a00, 40 instructions [V]
```
66d0a00  push rbp                                      
66d0a01  push r15                                      
66d0a03  push r14                                      
66d0a05  push r13                                      
66d0a07  push r12                                      
66d0a09  push rsi                                      
66d0a0a  push rdi                                      
66d0a0b  push rbx                                      
66d0a0c  sub rsp,0xE38                                 
66d0a13  lea rbp,[rsp+0x80]                            
66d0a1b  movaps [rbp+0xDA0],xmm6                       
66d0a22  mov qword ptr [rbp+0xD98],0xFFFFFFFFFFFFFFFE  
66d0a2d  mov [rbp+0xD78],r9                            
66d0a34  mov rdi,r8                                    
66d0a37  mov r15,rdx                                   
66d0a3a  mov [rbp+0xD70],rcx                           
66d0a41  mov rax,[r8]                                  ; R a2+0x0
66d0a44  movzx r14d,byte ptr [rax+0x151]               ; R *(a2+0x0)+0x151
66d0a4c  test r14b,r14b                                
66d0a4f  jne short 0x66D0A5A                           ; -> loc_66d0a5a
66d0a51  cmp byte ptr [rax+0x150],0                    ; R *(a2+0x0)+0x150
66d0a58  je short 0x66D0A5E                            ; -> loc_66d0a5e
loc_66d0a5a:  ; from 66d0a4f
66d0a5a  xor ebx,ebx                                   
66d0a5c  jmp short 0x66D0A65                           ; -> loc_66d0a65
loc_66d0a5e:  ; from 66d0a58
66d0a5e  movzx ebx,byte ptr [rax+0x1CE]                
loc_66d0a65:  ; from 66d0a5c
66d0a65  mov rax,[rax+0x140]                           
66d0a6c  test rax,rax                                  
66d0a6f  je short 0x66D0A86                            ; -> loc_66d0a86
66d0a71  mov rsi,[rax+0x40]                            
66d0a75  cmp byte ptr [rsi+0x25C],1                    
66d0a7c  jne short 0x66D0A91                           ; -> loc_66d0a91
loc_66d0a7e:  ; from 66d0a8f
66d0a7e  mov ecx,[rsi+0x258]                           
66d0a84  jmp short 0x66D0ABE                           ; -> loc_66d0abe
loc_66d0a86:  ; from 66d0a6f
66d0a86  xor esi,esi                                   
66d0a88  cmp byte ptr [rsi+0x25C],1                    
66d0a8f  je short 0x66D0A7E                            ; -> loc_66d0a7e
loc_66d0a91:  ; from 66d0a7c
66d0a91  lea rdx,[rsi+0x98]                            
66d0a98  lea rcx,[rbp+0xA50]                           
66d0a9f  call 0xBB68930                                ; -> sub_bb68930
66d0aa4  mov ecx,[rbp+0xA50]                           
```
`//` Prologue [V]: saves callee-saved regs (rbp,r15,r14,r13,r12,rsi,rdi,rbx), sub rsp,0xE38, frame pointer rbp=rsp+0x80, spills xmm6. Windows x64 arg map guess [I]: [rbp+0xD70]=rcx(arg1), rdi=r8(arg3), r15=rdx(arg2), [rbp+0xD78]=r9(arg4); [rbp+0xD98] = sentinel -2 (0xFFFFFFFFFFFFFFFE) [V]. `rax=[r8]` deref arg3 [V]; reads bytes [rax+0x151] (->r14b) and [rax+0x150] [V]; if r14b!=0 ebx=0 else if [rax+0x150]==0 ebx=[rax+0x1CE] [V][I: flag reads]. `rax=[rax+0x140]` [V]; if null esi=0 else rsi=[rax+0x40] [V]. Branch on byte [rsi+0x25C]==1: if equal ecx=[rsi+0x258] -> 0x66d0abe; else fall to 0x66d0a91 [V]. Note: null-rax path reads [rsi+0x25C] with rsi=0 (xor esi,esi) — target of that read unclear [?]. At 0x66d0a91: `call 0xBB68930(rcx=&stack rbp+0xA50, rdx=rsi+0x98)` [V call target+args]; then `ecx=[rbp+0xA50]` [V]. Call meaning unknown (stack struct init from rsi+0x98) [?].
## Phase 2 — 0x66d0aaa, 40 instructions [V]
```
66d0aaa  mov rax,0x100000000                           
66d0ab4  or rax,rcx                                    
66d0ab7  mov [rsi+0x258],rax                           
66d0abe  mov rdx,[rbp+0xE20]                           
66d0ac5  mov eax,r14d                                  
66d0ac8  xor al,1                                      
66d0aca  movzx esi,bl                                  
66d0acd  mov [rbp+0xD90],rcx                           
66d0ad4  or esi,ecx                                    
66d0ad6  mov [rbp+0x75C],esi                           
66d0adc  test esi,0x5001                               
66d0ae2  setne cl                                      
66d0ae5  or cl,al                                      
66d0ae7  mov [rbp+0xCD4],ebx                           
66d0aed  jne 0x66D0C92                                 ; -> loc_66d0c92
66d0af3  mov rax,[rdi]                                 
loc_66d0af6:  ; from 66d0cdb
66d0af6  mov rcx,[rbp+0xE20]                           
66d0afd  movzx r10d,byte ptr [rcx+0x118]               
66d0b05  xor r10b,1                                    
66d0b09  xor r11d,r11d                                 
66d0b0c  xor r12d,r12d                                 
66d0b0f  xor r8d,r8d                                   
loc_66d0b12:  ; from 66d0cdb, 66d0ce1, 66d0d1b, 66d0d5f, 66d0d78
66d0b12  mov [rbp+0xD80],r11d                          
66d0b19  mov [rbp+0xD8B],r14b                          
66d0b20  mov [rbp+0xD68],r10d                          
66d0b27  mov rax,[rax+0x140]                           
66d0b2e  mov rcx,[rax+0x40]                            
66d0b32  movzx r9d,byte ptr [r15+0x74]                 
66d0b37  lea rdx,[rbp+0x108]                           
66d0b3e  call 0x4DF8370                                ; -> sub_4df8370
66d0b43  mov rbx,[r15+0x68]                            
66d0b47  movups xmm0,[rbp+0x108]                       
66d0b4e  movaps [rbp+0x3D0],xmm0                       
66d0b55  mov r14,[r15+0x40]                            
66d0b59  lea rax,[rbp+0x28]                            
66d0b5d  mov [rbp+0x18],rax                            
66d0b61  mov rax,0x700000000                           
66d0b6b  mov [rbp+0x20],rax                            
66d0b6f  mov rax,[rbp+0x118]                           
66d0b76  mov edx,[rbp+0x120]                           
```
`//` [V] Writes: `[rsi+0x258] = rax (0x100000000 | rcx)` where rcx=[rbp+0xA50] from phase 1 [V]; stack locals [rbp+0xD90]=rcx, [rbp+0x75C]=esi=(bl|ecx), [rbp+0xCD4]=ebx, [rbp+0xD80]=r11d, [rbp+0xD8B]=r14b, [rbp+0xD68]=r10d, [rbp+0x18]=lea rbp+0x28, [rbp+0x20]=0x700000000, [rbp+0x3D0]=xmm0([rbp+0x108]) [V]. Reads [V]: [rbp+0xE20] (->rdx), [rdi] (->rax, =arg3 deref, repeated), [rcx+0x118] (->r10b), [rax+0x140] (->rax), [rax+0x40] (->rcx), [r15+0x74] (->r9d), [r15+0x68] (->rbx), [r15+0x40] (->r14), [rbp+0x108], [rbp+0x118] (->rax), [rbp+0x120] (->edx). Flags: al = (r14d^1)&0xFF [V]; esi = bl | ecx then tested vs 0x5001; setne cl; or cl,al; jne 0x66d0c92 if nonzero [V]. `xor r10b,1` flips byte [rcx+0x118] bit0 [V]. Zeroes r11d,r12d,r8d (loop counters) [V]. `call 0x4DF8370(rcx=[rax+0x40], rdx=&stack rbp+0x108, r9=[r15+0x74])` [V]; then movups xmm0 from [rbp+0x108] into [rbp+0x3D0] [V]. Loop header at 0x66d0b12 (targets from 0x66d0cdb/ce1/d1b/d5f/d78 — future phases) [V]. Stack item build begins: [rbp+0x28]..[rbp+0x20]=0x700000000 [I meaning unknown].
## Phase 3 — 0x66d0b7c, 40 instructions [V]
```
66d0b7c  mov [rbp+0xA50],rax                           
66d0b83  lea rcx,[rbp+0x18]                            
66d0b87  lea r8,[rbp+0xA50]                            
66d0b8e  mov r9,r8                                     
66d0b91  call 0x4E019A0                                ; -> sub_4e019a0
66d0b96  nop                                           
66d0b97  movups xmm0,[rbp+0x108]                       
66d0b9e  movaps [rbp+0x3E0],xmm0                       
66d0ba5  lea rcx,[rbp+0xA50]                           
66d0bac  lea rdx,[rbp+0x3E0]                           
66d0bb3  lea r8,[rbp+0x18]                             
66d0bb7  call 0x66D8F60                                ; -> sub_66d8f60
66d0bbc  nop                                           
66d0bbd  lea rax,[rbp+0x118]                           
66d0bc4  mov [rsp+0x28],rax                            
66d0bc9  lea rax,[rbp+0x3D0]                           
66d0bd0  mov [rsp+0x20],rax                            
66d0bd5  lea rdx,[rbp+0x460]                           
66d0bdc  lea r8,[rbp+0xA50]                            
66d0be3  mov rcx,rbx                                   
66d0be6  mov r9,r14                                    
66d0be9  call 0x67DA040                                ; -> sub_67da040
66d0bee  nop                                           
66d0bef  mov rbx,[rbp+0x460]                           
66d0bf6  mov r14,[rbx]                                 
66d0bf9  test r14,r14                                  
66d0bfc  je 0x66D6108                                  ; -> sub_66d6108
66d0c02  mov eax,[0x129CA5E0]                          ; [data_129ca5e0]
66d0c08  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d0c0e  mov rdx,gs:[0x58]                             
66d0c17  mov rcx,[rdx+rcx*8]                           
66d0c1b  cmp eax,[rcx+4]                               
66d0c21  jg 0x66D6197                                  ; -> sub_66d6197
66d0c27  cmp byte ptr [r14+0x10],1                     
66d0c2c  jne 0x66D6108                                 ; -> sub_66d6108
66d0c32  mov rax,[rbx+8]                               
66d0c36  test rax,rax                                  
66d0c39  je 0x66D0D7D                                  ; -> loc_66d0d7d
66d0c3f  lock inc dword ptr [rax+8]                    
66d0c43  mov rax,[rbx]                                 
66d0c46  mov rbx,[rbx+8]                               
```
`//` [V] Stack writes: [rbp+0xA50]=rax, [rbp+0x3E0]=xmm0([rbp+0x108]), [rsp+0x28]=lea rbp+0x118, [rsp+0x20]=lea rbp+0x3D0 [V]. Calls [V]: `call 0x4E019A0(rcx=&rbp+0x18, r8=&rbp+0xA50, r9=r8)`; `call 0x66D8F60(rcx=&rbp+0xA50, rdx=&rbp+0x3E0, r8=&rbp+0x18)`; `call 0x67DA040(rcx=rbx, rdx=&rbp+0x460, r8=&rbp+0xA50, r9=r14)` — callees' meanings unknown [?]. Reads [V]: [rbp+0x108], [rbp+0x118], [rbp+0x3D0], [rbp+0x460]->rbx, [rbx]->r14, [rbx+8]->rax (test+lock inc dword [rax+8] shared_ptr-style refcount [I]), [rbx]->rax again, [rbx+8]->rbx [V]. Data reads [V]: [0x129CA5E0]->eax, [0x128767C8]->ecx, gs:[0x58]->rdx then [rdx+rcx*8]->rcx, cmp eax,[rcx+4]. Branches [V]: test r14,r14 je 0x66d6108; cmp eax,[rcx+4] jg 0x66d6197; cmp byte [r14+0x10],1 jne 0x66d6108; test rax,rax je 0x66d0d7d. [I]: gs:[0x58] + data globals looks like a TLS/version tick check; lock inc [rax+8] is shared_ptr ctrl refcount. Both 0x66d6108 and 0x66d6197 are exit/fallback targets.
## Phase 4 — 0x66d0c46, 40 instructions [V]
```
66d0c46  mov rbx,[rbx+8]                               
66d0c4a  mov rax,[rax+0x18]                            
66d0c4e  mov r14,[rax]                                 
66d0c51  test rbx,rbx                                  
66d0c54  je 0x66D0D87                                  ; -> loc_66d0d87
66d0c5a  lock dec dword ptr [rbx+8]                    
66d0c5e  jne 0x66D0D87                                 ; -> loc_66d0d87
66d0c64  mov rax,[rbx]                                 
66d0c67  mov rax,[rax]                                 
66d0c6a  mov rcx,rbx                                   
66d0c6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d0c73  lock dec dword ptr [rbx+0xC]                  
66d0c77  jne 0x66D0D87                                 ; -> loc_66d0d87
66d0c7d  mov rax,[rbx]                                 
66d0c80  mov rax,[rax+8]                               
66d0c84  mov rcx,rbx                                   
66d0c87  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d0c8d  jmp 0x66D0D87                                 ; -> loc_66d0d87
66d0c92  mov rax,[rbp+0xD78]                           
66d0c99  cmp byte ptr [rax+0x130],1                    
66d0ca0  jne short 0x66D0CE6                           ; -> loc_66d0ce6
66d0ca2  mov rax,[rdi]                                 
66d0ca5  test byte ptr [rbp+0xD90],8                   
66d0cac  je short 0x66D0CFD                            ; -> loc_66d0cfd
loc_66d0cae:  ; from 66d0cfb
66d0cae  mov r12d,esi                                  
66d0cb1  and r12b,1                                    
66d0cb5  test r14b,r14b                                
66d0cb8  je short 0x66D0D23                            ; -> loc_66d0d23
66d0cba  mov rcx,[rax+0x140]                           
66d0cc1  mov rcx,[rcx+0x40]                            
66d0cc5  xor r11d,r11d                                 
66d0cc8  cmp byte ptr [rcx+0x185],1                    
66d0ccf  mov r10d,0                                    
66d0cd5  mov r8d,0                                     
66d0cdb  je 0x66D0AF6                                  ; -> sub_66d0af6
66d0ce1  jmp 0x66D0B12                                 ; -> sub_66d0b12
loc_66d0ce6:  ; from 66d0ca0
66d0ce6  mov rax,[rdi]                                 
66d0ce9  mov rcx,[rax+0x140]                           
66d0cf0  mov rcx,[rcx+0x40]                            
66d0cf4  cmp byte ptr [rcx+0x185],0                    
66d0cfb  je short 0x66D0CAE                            ; -> loc_66d0cae
```
`//` [V] shared_ptr release [I]: `rbx=[rbx+8]` (ctrl); if rbx!=0: `lock dec [rbx+8]`; if result!=0 goto 0x66d0d87; else `rax=[rbx]; rax=[rax]` (ptr); `rcx=rbx; call qword ptr [0xF99FFA0]` ([data_f99ffa0]=sub_eea6040) — ptr destroyer; `lock dec [rbx+0xC]` (weak count); if !=0 goto 0x66d0d87; else `rax=[rbx]; rax=[rax+8]`; `rcx=rbx; call qword ptr [0xF99FFA0]` (ctrl destroyer); jmp 0x66d0d87. All release paths converge at 0x66d0d87 [V]. Then [rbp+0xD78] (saved r9/arg4) ->rax; cmp byte [rax+0x130],1; jne 0x66d0ce6. mov rax,[rdi]; test byte [rbp+0xD90],8; je 0x66d0cfd. loc_66d0cae: r12d=esi; and r12b,1; test r14b,r14b; je 0x66d0d23; rcx=[rax+0x140]; rcx=[rcx+0x40]; xor r11d,r11d; cmp byte [rcx+0x185],1; r10d=0; r8d=0; if equal je 0x66d0af6 else jmp 0x66d0b12 (loop re-entry) [V]. 0x66d0ce6: rax=[rdi]; rcx=[rax+0x140]; rcx=[rcx+0x40]; cmp byte [rcx+0x185],0; je 0x66d0cae [V]. [I]: r14 is a shared_ptr payload from phase 3; loop re-entry at 0x66d0b12/0x66d0af6 driven by [rcx+0x185] byte (1->0x66d0af6, 0->0x66d0cae path).
## Phase 5 — 0x66d0cfb, 40 instructions [V]
```
66d0cfb  je short 0x66D0CAE                            ; -> sub_66d0cae
66d0cfd  movzx r10d,byte ptr [rdx+0x118]               ; R a1+0x118
66d0d05  xor r10b,1                                    
66d0d09  xor r12d,r12d                                 
66d0d0c  mov r11d,0                                    
66d0d12  mov r8d,0                                     
66d0d18  test r14b,r14b                                
66d0d1b  jne 0x66D0B12                                 ; -> sub_66d0b12
66d0d21  jmp short 0x66D0D26                           ; -> loc_66d0d26
66d0d23  xor r10d,r10d                                 
loc_66d0d26:  ; from 66d0d21
66d0d26  mov edx,[r15+0x70]                            
66d0d2a  cmp byte ptr [rax+0x150],0                    
66d0d31  je short 0x66D0D37                            ; -> loc_66d0d37
66d0d33  xor ecx,ecx                                   
66d0d35  jmp short 0x66D0D47                           ; -> loc_66d0d47
loc_66d0d37:  ; from 66d0d31
66d0d37  cmp edx,1                                     
66d0d3a  sete r8b                                      
66d0d3e  mov ecx,r10d                                  
66d0d41  xor cl,1                                      
66d0d44  and cl,r8b                                    
loc_66d0d47:  ; from 66d0d35
66d0d47  mov r9d,ecx                                   
66d0d4a  or r9b,r14b                                   
66d0d4d  cmp edx,1                                     
66d0d50  sete dl                                       
66d0d53  or dl,r9b                                     
66d0d56  xor r8d,r8d                                   
66d0d59  xor r11d,r11d                                 
66d0d5c  cmp dl,1                                      
66d0d5f  jne 0x66D0B12                                 ; -> sub_66d0b12
66d0d65  movzx ecx,cl                                  
66d0d68  test r9b,r9b                                  
66d0d6b  mov r8d,2                                     
66d0d71  cmovne r8d,ecx                                
66d0d75  mov r11b,1                                    
66d0d78  jmp 0x66D0B12                                 ; -> sub_66d0b12
66d0d7d  mov rax,[rbx]                                 
66d0d80  mov rax,[rax+0x18]                            
66d0d84  mov r14,[rax]                                 
66d0d87  test r14,r14                                  
66d0d8a  je 0x66D6108                                  ; -> sub_66d6108
66d0d90  mov r14,[r15]                                 
```
`//` [V] Loop-flag computation feeding 0x66d0b12: je 0x66d0cae; r10b = [rdx+0x118]^1 [V]; r12d=r11d=r8d=0; test r14b,r14b jne 0x66d0b12; jmp 0x66d0d26; else r10d=0. At 0x66d0d26: edx=[r15+0x70] [V]; cmp byte [rax+0x150],0: if 0 -> 0x66d0d37 (r8b=(edx==1); ecx=r10d^1 & r8b) else ecx=0 [V]; r9d=ecx|r14b; dl=(edx==1)|r9b; r8d=r11d=0; if dl!=1 jmp 0x66d0b12 else {movzx ecx,cl; test r9b,r9b; r8d = (r9b!=0)?ecx:2 via cmovne; r11b=1; jmp 0x66d0b12} [V]. Release target 0x66d0d7d: rax=[rbx]; rax=[rax+0x18]; r14=[rax]; test r14,r14 je 0x66d6108 [V]. Then 0x66d0d90: r14=[r15] [V] (start of next chunk). [I]: r15+0x70 and [rax+0x150] drive loop-exit/continue flags; cmovne picks r8d in {ecx,2}.
## Phase 6 — 0x66d0d90, 40 instructions [V]
```
66d0d90  mov r14,[r15]                                 
66d0d93  mov rax,[rbp+0x460]                           
66d0d9a  xorps xmm0,xmm0                               
66d0d9d  movaps [rbp+0xA50],xmm0                       
66d0da4  mov rcx,[rax+8]                               
66d0da8  test rcx,rcx                                  
66d0dab  je short 0x66D0DF4                            ; -> loc_66d0df4
66d0dad  lock inc dword ptr [rcx+8]                    
66d0db1  mov rbx,[rbp+0xA58]                           
66d0db8  movups xmm0,[rax]                             
66d0dbb  movaps [rbp+0xA50],xmm0                       
66d0dc2  test rbx,rbx                                  
66d0dc5  je short 0x66D0E09                            ; -> loc_66d0e09
66d0dc7  lock dec dword ptr [rbx+8]                    
66d0dcb  jne short 0x66D0E09                           ; -> loc_66d0e09
66d0dcd  mov rax,[rbx]                                 
66d0dd0  mov rax,[rax]                                 
66d0dd3  mov rcx,rbx                                   
66d0dd6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d0ddc  lock dec dword ptr [rbx+0xC]                  
66d0de0  jne short 0x66D0E09                           ; -> loc_66d0e09
66d0de2  mov rax,[rbx]                                 
66d0de5  mov rax,[rax+8]                               
66d0de9  mov rcx,rbx                                   
66d0dec  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d0df2  jmp short 0x66D0E09                           ; -> loc_66d0e09
loc_66d0df4:  ; from 66d0dab
66d0df4  mov rax,[rax]                                 
66d0df7  mov [rbp+0xA50],rax                           
66d0dfe  mov qword ptr [rbp+0xA58],0                   
loc_66d0e09:  ; from 66d0dc5, 66d0dcb, 66d0de0, 66d0df2
66d0e09  mov rax,[rbp+0xA50]                           
66d0e10  mov rax,[rax+0x18]                            
66d0e14  mov rax,[rax]                                 
66d0e17  mov [rbp+0xCE0],rax                           
66d0e1e  lea rcx,[rbp+0xCE8]                           
66d0e25  mov r8,[r14]                                  
66d0e28  mov rdx,[rax+0x170]                           
66d0e2f  call 0xE86B370                                ; -> sub_e86b370
66d0e34  nop                                           
66d0e35  mov [rbp+0xD60],r14                           
66d0e3c  mov rbx,[rbp+0xA58]                           
66d0e43  test rbx,rbx                                  
```
`//` [V] shared_ptr copy-assign into slot { [rbp+0xA50]=ptr, [rbp+0xA58]=ctrl }: rax=[rbp+0x460]; rcx=[rax+8] (ctrl); if rcx!=0 lock inc [rcx+8] [V] else loc_66d0df4: rax=[rax] (null), [rbp+0xA50]=rax, [rbp+0xA58]=0. Then xmm0=[rbp+0xA50] zeroed then =[rax] (movups xmm0,[rax]) [V]. Release old slot: rbx=[rbp+0xA58]; if rbx!=0 { lock dec [rbx+8]; if !=0 goto 0x66d0e09; else rax=[rbx]; rax=[rax]; rcx=rbx; call [0xF99FFA0] (ptr destroy); lock dec [rbx+0xC]; if !=0 goto 0x66d0e09; else rax=[rbx]; rax=[rax+8]; rcx=rbx; call [0xF99FFA0] (ctrl destroy); jmp 0x66d0e09 } [V] — classic shared_ptr release [I]. Converge 0x66d0e09: rax=[rbp+0xA50]; rax=[rax+0x18]; rax=[rax]; [rbp+0xCE0]=rax; rcx=&rbp+0xCE8; r8=[r14]; rdx=[rax+0x170]; call 0xE86B370 [V]; [rbp+0xD60]=r14; rbx=[rbp+0xA58]. [I]: call 0xE86B370(&rbp+0xCE8, [rax+0x170], [r14]) — registers a render-resource/callback [?]; [rbp+0xCE8..] is an out struct.
## Phase 7 — 0x66d0e43, 40 instructions [V]
```
66d0e43  test rbx,rbx                                  
66d0e46  je short 0x66D0E73                            ; -> loc_66d0e73
66d0e48  lock dec dword ptr [rbx+8]                    
66d0e4c  jne short 0x66D0E73                           ; -> loc_66d0e73
66d0e4e  mov rax,[rbx]                                 
66d0e51  mov rax,[rax]                                 
66d0e54  mov rcx,rbx                                   
66d0e57  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66d0e5d  lock dec dword ptr [rbx+0xC]                  
66d0e61  jne short 0x66D0E73                           ; -> loc_66d0e73
66d0e63  mov rax,[rbx]                                 
66d0e66  mov rax,[rax+8]                               
66d0e6a  mov rcx,rbx                                   
66d0e6d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_66d0e73:  ; from 66d0e46, 66d0e4c, 66d0e61
66d0e73  movups xmm0,[rdi+0x38]                        
66d0e77  movaps [rbp+0xA50],xmm0                       
66d0e7e  mov qword ptr [rbp+0x7E0],1                   
66d0e89  lea rax,[rbp+0xA50]                           
66d0e90  mov [rbp+0x7E8],rax                           
66d0e97  mov rax,[rbp+0xD18]                           
66d0e9e  movzx ecx,word ptr [rbp+0xD22]                
66d0ea5  mov edx,ecx                                   
66d0ea7  shl edx,4                                     
66d0eaa  mov r8,rax                                    
66d0ead  test ecx,ecx                                  
66d0eaf  mov [rbp+0xCD8],r15                           
66d0eb6  je short 0x66D0EE8                            ; -> loc_66d0ee8
66d0eb8  mov r9,[0x129F8320]                           ; [data_129f8320]
66d0ebf  xor r8d,r8d                                   
66d0ec2  nop [rax+rax]                                 
loc_66d0ed0:  ; from 66d0ee1
66d0ed0  mov r10,[rax+r8]                              
66d0ed4  cmp [r10+0x28],r9                             
66d0ed8  je short 0x66D0EE5                            ; -> loc_66d0ee5
66d0eda  add r8,0x10                                   
66d0ede  cmp rdx,r8                                    
66d0ee1  jne short 0x66d0ed0                           ; -> loc_66d0ed0
66d0ee3  jmp short 0x66D0F35                           ; -> loc_66d0f35
66d0ee5  add r8,rax                                    
loc_66d0ee8:  ; from 66d0eb6
66d0ee8  lea r9,[rax+rdx]                              
66d0eec  cmp r8,r9                                     
66d0eef  jae short 0x66D0F35                           ; -> loc_66d0f35
```
`//` [V] shared_ptr release tail of old [rbp+0xA58] slot (lock dec [rbx+8], [rbx+0xC], destroy ptr+ctrl via call [0xF99FFA0]=sub_eea6040, all paths to 0x66d0e73) [V][I]. Writes: [rbp+0xA50]=xmm0([rdi+0x38]) (16 bytes) [V]; [rbp+0x7E0]=1 [V]; [rbp+0x7E8]=&rbp+0xA50 [V]; [rbp+0xCD8]=r15 [V]. Reads: [rdi+0x38], [rbp+0xD18]->rax (table base), [rbp+0xD22] word ->ecx (count), [0x129F8320]->r9 (global), [rax+r8]->r10, [r10+0x28] (cmp) [V]. Loop 0x66d0ed0: linear scan over 0x10-stride table at rax, count=edx=ecx<<4, compare [r10+0x28]==r9; on match r8+=rax (entry ptr) ->0x66d0ee5; no match -> 0x66d0f35 [V]. End bound r9=rax+rdx; jae 0x66d0f35 [V]. [I]: rdi+0x38 stored as 16-byte value (vec4-ish) into [rbp+0xA50]; table lookup by key [r10+0x28] vs global [0x129F8320].
## Phase 8 — 0x66d0eef, 40 instructions [V]
```
66d0eef  jae short 0x66D0F35                           ; -> loc_66d0f35
66d0ef1  sub r8d,eax                                   
66d0ef4  shr r8d,4                                     
66d0ef8  mov [rbp+0x4D0],r8w                           
66d0f00  mov byte ptr [rbp+0x4D2],1                    
66d0f07  lea rdx,[rbp+0x4D0]                           
66d0f0e  lea r8,[rbp+0x7E0]                            
66d0f15  lea rcx,[rbp+0xCE8]                           
66d0f1c  call 0x5679DB0                                ; -> sub_5679db0
66d0f21  nop                                           
66d0f22  mov rax,[rbp+0xD18]                           
66d0f29  movzx ecx,word ptr [rbp+0xD22]                
66d0f30  mov edx,ecx                                   
66d0f32  shl edx,4                                     
loc_66d0f35:  ; from 66d0eef
66d0f35  movsd xmm0,[rdi+0x48]                         
66d0f3a  movups [rbp+0xA50],xmm0                       
66d0f41  mov qword ptr [rbp+0x7E0],1                   
66d0f4c  lea r8,[rbp+0xA50]                            
66d0f53  mov [rbp+0x7E8],r8                            
66d0f5a  mov r8,rax                                    
66d0f5d  test cx,cx                                    
66d0f60  je short 0x66D0F88                            ; -> loc_66d0f88
66d0f62  mov r9,[0x129F8328]                           ; [data_129f8328]
66d0f69  xor r8d,r8d                                   
66d0f6c  nop [rax]                                     
loc_66d0f70:  ; from 66d0f81
66d0f70  mov r10,[rax+r8]                              
66d0f74  cmp [r10+0x28],r9                             
66d0f78  je short 0x66D0F85                            ; -> loc_66d0f85
66d0f7a  add r8,0x10                                   
66d0f7e  cmp rdx,r8                                    
66d0f81  jne short 0x66d0f70                           ; -> loc_66d0f70
66d0f83  jmp short 0x66D0FD5                           ; -> loc_66d0fd5
66d0f85  add r8,rax                                    
loc_66d0f88:  ; from 66d0f60
66d0f88  lea r9,[rax+rdx]                              
66d0f8c  cmp r8,r9                                     
66d0f8f  jae short 0x66D0FD5                           ; -> loc_66d0fd5
66d0f91  sub r8d,eax                                   
66d0f94  shr r8d,4                                     
66d0f98  mov [rbp+0x4D0],r8w                           
66d0fa0  mov byte ptr [rbp+0x4D2],1                    
66d0fa7  lea rdx,[rbp+0x4D0]                           
```
`//` [V] Table-scan results: not-found (jae 0x66d0f35) skips first index store; found path (from phase 7 match): index=(r8-rax)>>4 -> [rbp+0x4D0] (r8w), byte [rbp+0x4D2]=1, then call 0x5679DB0(rdx=&rbp+0x4D0, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V]. Reload table base/count: rax=[rbp+0xD18], ecx=[rbp+0xD22] (word), edx=ecx<<4. Second scan: movsd xmm0=[rdi+0x48] -> [rbp+0xA50] (8 bytes) [V]; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]; r8=rax; if cx==0 ->0x66d0f88 else r9=[0x129F8328] (2nd global, differs from phase 7's [0x129F8320]) [V]; linear scan 0x10-stride [r10+0x28]==r9; match -> r8+=rax ->0x66d0f85; no match ->0x66d0fd5; end-bound jae 0x66d0fd5. Match/not-found both converge to index: sub r8d,eax; shr r8d,4; [rbp+0x4D0]=r8w; byte [rbp+0x4D2]=1; lea rdx,&rbp+0x4D0 [V]. [I]: two keyed table lookups (globals [0x129F8320] then [0x129F8328]) each yielding u16 index at [rbp+0x4D0] + flag byte [rbp+0x4D2]; call 0x5679db0 consumes index/value/out-struct [?].
## Phase 9 — 0x66d0fa7, 40 instructions [V]
```
66d0fa7  lea rdx,[rbp+0x4D0]                           
66d0fae  lea r8,[rbp+0x7E0]                            
66d0fb5  lea rcx,[rbp+0xCE8]                           
66d0fbc  call 0x5679DB0                                ; -> sub_5679db0
66d0fc1  nop                                           
66d0fc2  mov rax,[rbp+0xD18]                           
66d0fc9  movzx ecx,word ptr [rbp+0xD22]                
66d0fd0  mov edx,ecx                                   
66d0fd2  shl edx,4                                     
66d0fd5  movups xmm0,[rdi+0x50]                        
66d0fd9  movaps [rbp+0xA50],xmm0                       
66d0fe0  mov qword ptr [rbp+0x7E0],1                   
66d0feb  lea r8,[rbp+0xA50]                            
66d0ff2  mov [rbp+0x7E8],r8                            
66d0ff9  mov r8,rax                                    
66d0ffc  test cx,cx                                    
66d0fff  je short 0x66D1028                            ; -> loc_66d1028
66d1001  mov r9,[0x129F8330]                           ; [data_129f8330]
66d1008  xor r8d,r8d                                   
66d100b  nop [rax+rax]                                 
loc_66d1010:  ; from 66d1021
66d1010  mov r10,[rax+r8]                              
66d1014  cmp [r10+0x28],r9                             
66d1018  je short 0x66D1025                            ; -> loc_66d1025
66d101a  add r8,0x10                                   
66d101e  cmp rdx,r8                                    
66d1021  jne short 0x66D1010                           ; -> loc_66d1010
66d1023  jmp short 0x66D1075                           ; -> loc_66d1075
66d1025  add r8,rax                                    
loc_66d1028:  ; from 66d0fff
66d1028  lea r9,[rax+rdx]                              
66d102c  cmp r8,r9                                     
66d102f  jae short 0x66D1075                           ; -> loc_66d1075
66d1031  sub r8d,eax                                   
66d1034  shr r8d,4                                     
66d1038  mov [rbp+0x4D0],r8w                           
66d1040  mov byte ptr [rbp+0x4D2],1                    
66d1047  lea rdx,[rbp+0x4D0]                           
66d104e  lea r8,[rbp+0x7E0]                            
66d1055  lea rcx,[rbp+0xCE8]                           
66d105c  call 0x5679DB0                                ; -> sub_5679db0
66d1061  nop                                           
66d1062  mov rax,[rbp+0xD18]                           
```
`//` [V] call 0x5679DB0(rdx=&rbp+0x4D0, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) consuming 2nd lookup [V]; reload rax=[rbp+0xD18], ecx=[rbp+0xD22], edx=ecx<<4. 3rd table scan: movups xmm0=[rdi+0x50]->[rbp+0xA50] (16 bytes) [V]; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]; r8=rax; if cx==0 ->0x66d1028 else r9=[0x129F8330] (3rd global, distinct from ...8320/...8328) [V]; linear scan [r10+0x28]==r9 over 0x10-stride table, count edx; match ->r8+=rax ->0x66d1025; no match ->0x66d1075; end-bound jae 0x66d1075. Match/nf: [rbp+0x4D0]=r8w (index=(r8-rax)>>4); byte [rbp+0x4D2]=1; call 0x5679DB0(rdx=&rbp+0x4D0, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V] (4th call to this callee); nop; then 66d1062: rax=[rbp+0xD18] (phase 10). [I]: repeated pattern — keyed table lookups into table at [rbp+0xD18] (count u16 at [rbp+0xD22], stride 0x10, key field +0x28) against globals [0x129F8320]/[0x129F8328]/[0x129F8330]..., each lookup stores u16 index at [rbp+0x4D0]+flag byte [rbp+0x4D2]=1 and feeds call 0x5679DB0({index},{16-byte value at [rbp+0x7E8]}, &out [rbp+0xCE8]) [?].
## Phase 10 — 0x66d1062, 40 instructions [V]
```
66d1062  mov rax,[rbp+0xD18]                           
66d1069  movzx ecx,word ptr [rbp+0xD22]                
66d1070  mov edx,ecx                                   
66d1072  shl edx,4                                     
66d1075  movups xmm0,[rdi+0x28]                        
66d1079  movaps [rbp+0xA50],xmm0                       
66d1080  mov qword ptr [rbp+0x7E0],1                   
66d108b  lea r8,[rbp+0xA50]                            
66d1092  mov [rbp+0x7E8],r8                            
66d1099  mov r8,rax                                    
66d109c  test cx,cx                                    
66d109f  je short 0x66D10CD                            ; -> loc_66d10cd
66d10a1  mov r9,[0x129F8340]                           ; [data_129f8340]
66d10a8  xor r8d,r8d                                   
66d10ab  nop [rax+rax]                                 
loc_66d10b0:  ; from 66d10c1
66d10b0  mov r10,[rax+r8]                              
66d10b4  cmp [r10+0x28],r9                             
66d10b8  je short 0x66D10CA                            ; -> loc_66d10ca
66d10ba  add r8,0x10                                   
66d10be  cmp rdx,r8                                    
66d10c1  jne short 0x66D10B0                           ; -> loc_66d10b0
66d10c3  mov r9w,1                                     
66d10c8  jmp short 0x66D111D                           ; -> loc_66d111d
66d10ca  add r8,rax                                    
loc_66d10cd:  ; from 66d109f
66d10cd  lea r9,[rax+rdx]                              
66d10d1  cmp r8,r9                                     
66d10d4  jae short 0x66D111A                           ; -> loc_66d111a
66d10d6  sub r8d,eax                                   
66d10d9  shr r8d,4                                     
66d10dd  mov [rbp+0x4D0],r8w                           
66d10e5  mov byte ptr [rbp+0x4D2],1                    
66d10ec  lea rdx,[rbp+0x4D0]                           
66d10f3  lea r8,[rbp+0x7E0]                            
66d10fa  lea rcx,[rbp+0xCE8]                           
66d1101  call 0x5679DB0                                ; -> sub_5679db0
66d1106  nop                                           
66d1107  mov rax,[rbp+0xD18]                           
66d110e  movzx ecx,word ptr [rbp+0xD22]                
66d1115  mov edx,ecx                                   
66d1117  shl edx,4                                     
```
`//` [V] 4th table scan pattern: rax=[rbp+0xD18], ecx=[rbp+0xD22] (count), edx=ecx<<4; movups xmm0=[rdi+0x28]->[rbp+0xA50] (16 bytes) [V]; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]; if cx==0 ->0x66d10cd else r9=[0x129F8340] (4th global) [V]; scan [r10+0x28]==r9; match ->r8+=rax ->0x66d10ca; no match -> `mov r9w,1; jmp 0x66d111d` (default key=1, skips index calc) [V]; end-bound jae 0x66d111a. Match path: [rbp+0x4D0]=r8w (index=(r8-rax)>>4); byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0, &rbp+0x7E0, &rbp+0xCE8) [V] (5th call); nop; reload rax=[rbp+0xD18], ecx=[rbp+0xD22], edx=ecx<<4 [V]. [I]: each lookup = {key global, 16-byte value from rdi+0x28/0x38/0x48/0x50...} -> call 0x5679DB0(index, value, out&rbp+0xCE8) [?]. Not-found here defaults key r9w=1 rather than computing index — variation [V].
## Phase 11 — 0x66d111a, 40 instructions [V]
```
66d111a  mov r9d,ecx                                   
66d111d  movups xmm0,[rdi+0x70]                        
66d1121  movaps [rbp+0xA50],xmm0                       
66d1128  mov qword ptr [rbp+0x7E0],1                   
66d1133  lea r8,[rbp+0xA50]                            
66d113a  mov [rbp+0x7E8],r8                            
66d1141  mov r8,rax                                    
66d1144  test r9w,r9w                                  
66d1148  je short 0x66D1178                            ; -> loc_66d1178
66d114a  mov r9,[0x129F8348]                           ; [data_129f8348]
66d1151  xor r8d,r8d                                   
66d1154  mov r11,[rbp+0xD90]                           
66d115b  nop [rax+rax]                                 
loc_66d1160:  ; from 66d1171
66d1160  mov r10,[rax+r8]                              
66d1164  cmp [r10+0x28],r9                             
66d1168  je short 0x66D1175                            ; -> loc_66d1175
66d116a  add r8,0x10                                   
66d116e  cmp rdx,r8                                    
66d1171  jne short 0x66d1160                           ; -> loc_66d1160
66d1173  jmp short 0x66D11C6                           ; -> loc_66d11c6
66d1175  add r8,rax                                    
loc_66d1178:  ; from 66d1148
66d1178  add rdx,rax                                   
66d117b  cmp r8,rdx                                    
66d117e  jae short 0x66D11BF                           ; -> loc_66d11bf
66d1180  sub r8d,eax                                   
66d1183  shr r8d,4                                     
66d1187  mov [rbp+0x4D0],r8w                           
66d118f  mov byte ptr [rbp+0x4D2],1                    
66d1196  lea rdx,[rbp+0x4D0]                           
66d119d  lea r8,[rbp+0x7E0]                            
66d11a4  lea rcx,[rbp+0xCE8]                           
66d11ab  call 0x5679DB0                                ; -> sub_5679db0
66d11b0  nop                                           
66d11b1  mov rax,[rbp+0xD18]                           
66d11b8  movzx ecx,word ptr [rbp+0xD22]                
loc_66d11bf:  ; from 66d117e
66d11bf  mov r11,[rbp+0xD90]                           
loc_66d11c6:  ; from 66d1173
66d11c6  xorps xmm0,xmm0                               
66d11c9  test r11b,4                                   
66d11cd  je short 0x66D11D7                            ; -> loc_66d11d7
66d11cf  movss xmm0,[0xEEC8060]                        ; [data_eec8060]
loc_66d11d7:  ; from 66d11cd
66d11d7  mov [rbp+0xD6C],r12d                          
```
`//` [V] 5th table scan: r9d=ecx (count); movups xmm0=[rdi+0x70]->[rbp+0xA50] (16 bytes); [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50; r8=rax; if r9w==0 ->0x66d1178 (skip scan) else r9=[0x129F8348] (5th global), r11=[rbp+0xD90]; scan [r10+0x28]==r9; match ->r8+=rax->0x66d1175; no match ->0x66d11c6; end: rdx+=rax; cmp r8,rdx jae 0x66d11bf. Match: [rbp+0x4D0]=r8w; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (6th call); nop; rax=[rbp+0xD18]; ecx=[rbp+0xD22]. Converge: r11=[rbp+0xD90]; xorps xmm0; test r11b,4; if bit4 set -> movss xmm0=[0xEEC8060] (float constant) else xmm0=0 [V]; [rbp+0xD6C]=r12d [V]. [I]: r11b bit4 selects a float (0 or constant at 0xEEC8060) — likely a brightness/alpha; 6 call-0x5679db0 invocations so far each attach {u16 index, 16-byte value} to out struct [rbp+0xCE8] [?].
## Phase 12 — 0x66d11d7, 40 instructions [V]
```
66d11d7  mov [rbp+0xD6C],r12d                          
66d11de  shufps xmm0,xmm0,0                            
66d11e2  movaps [rbp+0xA50],xmm0                       
66d11e9  mov qword ptr [rbp+0x7E0],1                   
66d11f4  lea rdx,[rbp+0xA50]                           
66d11fb  mov [rbp+0x7E8],rdx                           
66d1202  movzx r8d,cx                                  
66d1206  mov edx,r8d                                   
66d1209  shl edx,4                                     
66d120c  mov rcx,rax                                   
66d120f  test r8w,r8w                                  
66d1213  je short 0x66D1245                            ; -> loc_66d1245
66d1215  mov r8,[0x129F8338]                           ; [data_129f8338]
66d121c  mov r9,rdx                                    
66d121f  mov rcx,rax                                   
66d1222  nop [rax+rax]                                 
loc_66d1230:  ; from 66d1241
66d1230  mov r10,[rcx]                                 
66d1233  cmp [r10+0x28],r8                             
66d1237  je short 0x66D1245                            ; -> loc_66d1245
66d1239  add rcx,0x10                                  
66d123d  add r9,0xFFFFFFFFFFFFFFF0                     
66d1241  jne short 0x66d1230                           ; -> loc_66d1230
66d1243  jmp short 0x66D127B                           ; -> loc_66d127b
loc_66d1245:  ; from 66d1213, 66d1237
66d1245  add rdx,rax                                   
66d1248  cmp rcx,rdx                                   
66d124b  jae short 0x66D127B                           ; -> loc_66d127b
66d124d  sub ecx,eax                                   
66d124f  shr ecx,4                                     
66d1252  mov [rbp+0x4D0],cx                            
66d1259  mov byte ptr [rbp+0x4D2],1                    
66d1260  lea rdx,[rbp+0x4D0]                           
66d1267  lea r8,[rbp+0x7E0]                            
66d126e  lea rcx,[rbp+0xCE8]                           
66d1275  call 0x5679DB0                                ; -> sub_5679db0
66d127a  nop                                           
loc_66d127b:  ; from 66d1243, 66d124b
66d127b  mov rbx,[rbp+0xD90]                           
66d1282  test ebx,0x81000                              
66d1288  je 0x66D1332                                  ; -> loc_66d1332
66d128e  movups xmm0,[rdi+0x18]                        
66d1292  movaps [rbp+0xA50],xmm0                       
66d1299  mov qword ptr [rbp+0x7E0],1                   
```
`//` [V] [rbp+0xD6C]=r12d; xmm0=shufps(xmm0,xmm0,0) (broadcast lo dword) -> [rbp+0xA50]; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]. 6th table scan variant: r8d=cx (zero-extended), r8=[0x129F8338] (6th global) as key, r9=edx (end counter), rcx=rax (walk ptr); if r8w==0 ->0x66d1245; else scan [r10+0x28]==r8 with rcx+=0x10, r9-=0x10 until r9==0 (jne) [V]; match ->rcx (=entry ptr) ->0x66d1245; no match ->0x66d127b. End: rdx+=rax; cmp rcx,rdx jae 0x66d127b; else index=(ecx-rax)>>4 -> [rbp+0x4D0] (cx); byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (7th call); nop. Converge 0x66d127b: rbx=[rbp+0xD90]; test ebx,0x81000; if zero je 0x66d1332 [V]. If nonzero: movups xmm0=[rdi+0x18]->[rbp+0xA50]; [rbp+0x7E0]=1 [V]. [I]: r11b bit4 (phase 11) and ebx bits 0x81000 are flag tests selecting value sources; 7 call-0x5679db0 invocations total so far.
## Phase 13 — 0x66d1299, 40 instructions [V]
```
66d1299  mov qword ptr [rbp+0x7E0],1                   
66d12a4  lea rax,[rbp+0xA50]                           
66d12ab  mov [rbp+0x7E8],rax                           
66d12b2  mov rax,[rbp+0xD18]                           
66d12b9  movzx r8d,word ptr [rbp+0xD22]                
66d12c1  mov edx,r8d                                   
66d12c4  shl edx,4                                     
66d12c7  mov rcx,rax                                   
66d12ca  test r8d,r8d                                  
66d12cd  je short 0x66D12F5                            ; -> loc_66d12f5
66d12cf  mov r8,[0x129F8360]                           ; [data_129f8360]
66d12d6  mov r9,rdx                                    
66d12d9  mov rcx,rax                                   
66d12dc  nop [rax]                                     
loc_66d12e0:  ; from 66d12f1
66d12e0  mov r10,[rcx]                                 
66d12e3  cmp [r10+0x28],r8                             
66d12e7  je short 0x66D12F5                            ; -> loc_66d12f5
66d12e9  add rcx,0x10                                  
66d12ed  add r9,0xFFFFFFFFFFFFFFF0                     
66d12f1  jne short 0x66d12e0                           ; -> loc_66d12e0
66d12f3  jmp short 0x66D132B                           ; -> loc_66d132b
loc_66d12f5:  ; from 66d12cd, 66d12e7
66d12f5  add rdx,rax                                   
66d12f8  cmp rcx,rdx                                   
66d12fb  jae short 0x66D132B                           ; -> loc_66d132b
66d12fd  sub ecx,eax                                   
66d12ff  shr ecx,4                                     
66d1302  mov [rbp+0x4D0],cx                            
66d1309  mov byte ptr [rbp+0x4D2],1                    
66d1310  lea rdx,[rbp+0x4D0]                           
66d1317  lea r8,[rbp+0x7E0]                            
66d131e  lea rcx,[rbp+0xCE8]                           
66d1325  call 0x5679DB0                                ; -> sub_5679db0
66d132a  nop                                           
loc_66d132b:  ; from 66d12f3, 66d12fb
66d132b  mov rbx,[rbp+0xD90]                           
66d1332  test ebx,0x200000                             
66d1338  je 0x66D13E2                                  ; -> loc_66d13e2
66d133e  movups xmm0,[rdi+0xA4]                        
66d1345  movaps [rbp+0xA50],xmm0                       
66d134c  mov qword ptr [rbp+0x7E0],1                   
66d1357  lea rax,[rbp+0xA50]                           
66d135e  mov [rbp+0x7E8],rax                           
```
`//` [V] [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]. 7th table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22] (count); edx=r8d<<4; rcx=rax; if r8d==0 ->0x66d12f5; else r8=[0x129F8360] (7th global); r9=rdx; scan [r10+0x28]==r8 (rcx+=0x10, r9-=0x10, jne until r9==0) [V]; match ->rcx->0x66d12f5; no match ->0x66d132b. End: rdx+=rax; cmp rcx,rdx jae 0x66d132b; else index=(ecx-rax)>>4 -> [rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (8th call); nop. Converge 0x66d132b: rbx=[rbp+0xD90]; test ebx,0x200000; je 0x66d13e2. If set: movups xmm0=[rdi+0xA4]->[rbp+0xA50]; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]. [I]: flag bits on ebx=[rbp+0xD90] select value source: bit4->float (0 or const 0xEEC8060), bit 0x81000->[rdi+0x18], bit 0x200000->[rdi+0xA4]. 8 call-0x5679db0 total.
## Phase 14 — 0x66d135e, 40 instructions [V]
```
66d135e  mov [rbp+0x7E8],rax                           
66d1365  mov rax,[rbp+0xD18]                           
66d136c  movzx r8d,word ptr [rbp+0xD22]                
66d1374  mov edx,r8d                                   
66d1377  shl edx,4                                     
66d137a  mov rcx,rax                                   
66d137d  test r8d,r8d                                  
66d1380  je short 0x66D13A5                            ; -> loc_66d13a5
66d1382  mov r8,[0x129F8368]                           ; [data_129f8368]
66d1389  mov r9,rdx                                    
66d138c  mov rcx,rax                                   
66d138f  nop                                           
loc_66d1390:  ; from 66d13a1
66d1390  mov r10,[rcx]                                 
66d1393  cmp [r10+0x28],r8                             
66d1397  je short 0x66D13A5                            ; -> loc_66d13a5
66d1399  add rcx,0x10                                  
66d139d  add r9,0xFFFFFFFFFFFFFFF0                     
66d13a1  jne short 0x66d1390                           ; -> loc_66d1390
66d13a3  jmp short 0x66D13DB                           ; -> loc_66d13db
loc_66d13a5:  ; from 66d1380, 66d1397
66d13a5  add rdx,rax                                   
66d13a8  cmp rcx,rdx                                   
66d13ab  jae short 0x66D13DB                           ; -> loc_66d13db
66d13ad  sub ecx,eax                                   
66d13af  shr ecx,4                                     
66d13b2  mov [rbp+0x4D0],cx                            
66d13b9  mov byte ptr [rbp+0x4D2],1                    
66d13c0  lea rdx,[rbp+0x4D0]                           
66d13c7  lea r8,[rbp+0x7E0]                            
66d13ce  lea rcx,[rbp+0xCE8]                           
66d13d5  call 0x5679DB0                                ; -> sub_5679db0
66d13da  nop                                           
loc_66d13db:  ; from 66d13a3, 66d13ab
66d13db  mov rbx,[rbp+0xD90]                           
66d13e2  test bl,bl                                    
66d13e4  jns 0x66D1635                                 ; -> loc_66d1635
66d13ea  movups xmm0,[rdi+0x8C]                        
66d13f1  movaps [rbp+0xA50],xmm0                       
66d13f8  mov qword ptr [rbp+0x7E0],1                   
66d1403  lea rax,[rbp+0xA50]                           
66d140a  mov [rbp+0x7E8],rax                           
66d1411  mov rax,[rbp+0xD18]                           
66d1418  movzx r8d,word ptr [rbp+0xD22]                
```
`//` [V] [rbp+0x7E8]=rax [V]. 8th table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22] (count); edx<<4; rcx=rax; if r8d==0 ->0x66d13a5; else r8=[0x129F8368] (8th global); r9=rdx; scan [r10+0x28]==r8 (rcx+=0x10, r9-=0x10) [V]; match->0x66d13a5; no match->0x66d13db. End: rdx+=rax; cmp rcx,rdx jae 0x66d13db; else index=(ecx-rax)>>4 -> [rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (9th call); nop. Converge 0x66d13db: rbx=[rbp+0xD90]; test bl,bl; jns 0x66d1635 (bl>=0 skips). If bl<0: movups xmm0=[rdi+0x8C]->[rbp+0xA50]; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50; then rax=[rbp+0xD18]; r8d=[rbp+0xD22] (phase 15) [V]. [I]: flag bl sign bit selects [rdi+0x8C] value. 9 call-0x5679db0 total.
## Phase 15 — 0x66d1418, 40 instructions [V]
```
66d1418  movzx r8d,word ptr [rbp+0xD22]                
66d1420  mov edx,r8d                                   
66d1423  shl edx,4                                     
66d1426  mov rcx,rax                                   
66d1429  test r8d,r8d                                  
66d142c  je short 0x66D1455                            ; -> loc_66d1455
66d142e  mov r8,[0x129F8368]                           ; [data_129f8368]
66d1435  mov r9,rdx                                    
66d1438  mov rcx,rax                                   
66d143b  nop [rax+rax]                                 
loc_66d1440:  ; from 66d1451
66d1440  mov r10,[rcx]                                 
66d1443  cmp [r10+0x28],r8                             
66d1447  je short 0x66D1455                            ; -> loc_66d1455
66d1449  add rcx,0x10                                  
66d144d  add r9,0xFFFFFFFFFFFFFFF0                     
66d1451  jne short 0x66d1440                           ; -> loc_66d1440
66d1453  jmp short 0x66D148B                           ; -> loc_66d148b
loc_66d1455:  ; from 66d142c, 66d1447
66d1455  add rdx,rax                                   
66d1458  cmp rcx,rdx                                   
66d145b  jae short 0x66D148B                           ; -> loc_66d148b
66d145d  sub ecx,eax                                   
66d145f  shr ecx,4                                     
66d1462  mov [rbp+0x4D0],cx                            
66d1469  mov byte ptr [rbp+0x4D2],1                    
66d1470  lea rdx,[rbp+0x4D0]                           
66d1477  lea r8,[rbp+0x7E0]                            
66d147e  lea rcx,[rbp+0xCE8]                           
66d1485  call 0x5679DB0                                ; -> sub_5679db0
66d148a  nop                                           
loc_66d148b:  ; from 66d1453, 66d145b
66d148b  mov eax,[0x129F8FA0]                          ; [data_129f8fa0]
66d1491  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1497  mov rdx,gs:[0x58]                             
66d14a0  mov rcx,[rdx+rcx*8]                           
66d14a4  cmp eax,[rcx+4]                               
66d14aa  jg 0x66D66BA                                  ; -> sub_66d66ba
66d14b0  mov eax,[0x129F8FB0]                          ; [data_129f8fb0]
66d14b6  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d14bc  mov rdx,gs:[0x58]                             
66d14c5  mov rcx,[rdx+rcx*8]                           
66d14c9  cmp eax,[rcx+4]                               
66d14cf  jg 0x66D672C                                  ; -> sub_66d672c
```
`//` [V] 10th table scan: rax=[rbp+0xD18] (carried from phase 14 end); r8d=[rbp+0xD22] (count); key r8=[0x129F8368] (same global as phase 14); scan [r10+0x28]==r8 (rcx+=0x10, r9-=0x10) [V]; index->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (10th call); nop. Then two TLS gated checks [V]: mov eax,[0x129F8FA0]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d66ba; repeat with eax=[0x129F8FB0], jg 0x66d672c. Same TLS/data pattern as phase 3 (0x129CA5E0/0x128767C8) [I: version/tick gate]. Data reads [0x129F8FA0], [0x128767C8], gs:[0x58] [V].
## Phase 16 — 0x66d14cf, 40 instructions [V]
```
66d14cf  jg 0x66D672C                                  ; -> sub_66d672c
66d14d5  movsd xmm0,[rdi+0x9C]                         
66d14dd  movups [rbp+0xA50],xmm0                       
66d14e4  mov qword ptr [rbp+0x7E0],1                   
66d14ef  lea rax,[rbp+0xA50]                           
66d14f6  mov [rbp+0x7E8],rax                           
66d14fd  mov rax,[rbp+0xD18]                           
66d1504  movzx edx,word ptr [rbp+0xD22]                
66d150b  mov ecx,edx                                   
66d150d  shl ecx,4                                     
66d1510  mov r8,rax                                    
66d1513  test edx,edx                                  
66d1515  je short 0x66D154C                            ; -> loc_66d154c
66d1517  mov r9,[0x129F8F98]                           ; [data_129f8f98]
66d151e  xor r8d,r8d                                   
66d1521  nop [rax+rax]                                 
loc_66d1530:  ; from 66d1541
66d1530  mov r10,[rax+r8]                              
66d1534  cmp [r10+0x28],r9                             
66d1538  je short 0x66D1549                            ; -> loc_66d1549
66d153a  add r8,0x10                                   
66d153e  cmp rcx,r8                                    
66d1541  jne short 0x66D1530                           ; -> loc_66d1530
66d1543  mov dx,1                                      
66d1547  jmp short 0x66D1599                           ; -> loc_66d1599
66d1549  add r8,rax                                    
loc_66d154c:  ; from 66d1515
66d154c  lea r9,[rax+rcx]                              
66d1550  cmp r8,r9                                     
66d1553  jae short 0x66D1599                           ; -> loc_66d1599
66d1555  sub r8d,eax                                   
66d1558  shr r8d,4                                     
66d155c  mov [rbp+0x4D0],r8w                           
66d1564  mov byte ptr [rbp+0x4D2],1                    
66d156b  lea rdx,[rbp+0x4D0]                           
66d1572  lea r8,[rbp+0x7E0]                            
66d1579  lea rcx,[rbp+0xCE8]                           
66d1580  call 0x5679DB0                                ; -> sub_5679db0
66d1585  nop                                           
66d1586  mov rax,[rbp+0xD18]                           
66d158d  movzx edx,word ptr [rbp+0xD22]                
66d1594  mov ecx,edx                                   
66d1596  shl ecx,4                                     
```
`//` [V] jg 0x66d672c (fall-through when phase-15 TLS check not taken). movsd xmm0=[rdi+0x9C]->[rbp+0xA50] (8 bytes); [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]. 11th table scan: rax=[rbp+0xD18]; edx=[rbp+0xD22] (count); ecx=edx<<4; r8=rax; if edx==0 ->0x66d154c; else r9=[0x129F8F98] (9th global); scan [r10+0x28]==r9 (r8+=0x10, cmp rcx,r8) [V]; match ->r8+=rax ->0x66d1549; not-found ->mov dx,1; jmp 0x66d1599 (default key 1). End-bound: lea r9,[rax+rcx]; cmp r8,r9 jae 0x66d1599; else index=(r8-rax)>>4 ->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (11th call); nop; rax=[rbp+0xD18]; edx=[rbp+0xD22]; ecx=edx; shl ecx,4 (phase 17). [I]: 11 call-0x5679db0 total; not-found default key=1 [V].
## Phase 17 — 0x66d1596, 40 instructions [V]
```
66d1596  shl ecx,4                                     
66d1599  movups xmm0,[rdi+8]                           
66d159d  movaps [rbp+0xA50],xmm0                       
66d15a4  mov qword ptr [rbp+0x7E0],1                   
66d15af  lea r8,[rbp+0xA50]                            
66d15b6  mov [rbp+0x7E8],r8                            
66d15bd  mov r8,rax                                    
66d15c0  test dx,dx                                    
66d15c3  je short 0x66D15F5                            ; -> loc_66d15f5
66d15c5  mov rdx,[0x129F8FA8]                          ; [data_129f8fa8]
66d15cc  mov r9,rcx                                    
66d15cf  mov r8,rax                                    
66d15d2  nop [rax+rax]                                 
loc_66d15e0:  ; from 66d15f1
66d15e0  mov r10,[r8]                                  
66d15e3  cmp [r10+0x28],rdx                            
66d15e7  je short 0x66D15F5                            ; -> loc_66d15f5
66d15e9  add r8,0x10                                   
66d15ed  add r9,0xFFFFFFFFFFFFFFF0                     
66d15f1  jne short 0x66d15e0                           ; -> loc_66d15e0
66d15f3  jmp short 0x66D162E                           ; -> loc_66d162e
66d15f5  add rcx,rax                                   
66d15f8  cmp r8,rcx                                    
66d15fb  jae short 0x66D162E                           ; -> loc_66d162e
66d15fd  sub r8d,eax                                   
66d1600  shr r8d,4                                     
66d1604  mov [rbp+0x4D0],r8w                           
66d160c  mov byte ptr [rbp+0x4D2],1                    
66d1613  lea rdx,[rbp+0x4D0]                           
66d161a  lea r8,[rbp+0x7E0]                            
66d1621  lea rcx,[rbp+0xCE8]                           
66d1628  call 0x5679DB0                                ; -> sub_5679db0
66d162d  nop                                           
loc_66d162e:  ; from 66d15f3, 66d15fb
66d162e  mov rbx,[rbp+0xD90]                           
66d1635  test ebx,0x600                                
66d163b  je 0x66D1712                                  ; -> loc_66d1712
66d1641  mov eax,[0x129F8FC0]                          ; [data_129f8fc0]
66d1647 mov ecx,[0x128767C8]                          ; [data_128767c8]
66d164d  mov rdx,gs:[0x58]                             
66d1656  mov rcx,[rdx+rcx*8]                           
66d165a  cmp eax,[rcx+4]                               
66d1660  jg 0x66D656A                                  ; -> sub_66d656a
```
`//` [V] shl ecx,4 (phase-16 scan count<<4). movups xmm0=[rdi+8]->[rbp+0xA50] (16 bytes); [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50; r8=rax; test dx,dx (dx=1 default key carried from phase-16 not-found path); je 0x66d15f5 (skip scan if dx==0) else rdx=[0x129F8FA8] (10th global); r9=rcx (end counter); r8=rax; scan [r10+0x28]==rdx (r8+=0x10, r9-=0x10) [V]; match->r8->0x66d15f5; no match->0x66d162e. End-bound: rcx+=rax; cmp r8,rcx jae 0x66d162e; else index=(r8-rax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (12th call); nop. Converge: rbx=[rbp+0xD90]; test ebx,0x600; je 0x66d1712; else mov eax,[0x129F8FC0]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d656a [V] (TLS gate, same pattern as phase 3/15). [I]: dx=1 chained key from phase 16's not-found default; 12 call-0x5679db0 total; flag bits on ebx=[rbp+0xD90]: 0x600 selects [0x129F8FC0] TLS check.
## Phase 18 — 0x66d1660, 40 instructions [V]
```
66d1660  jg 0x66D656A                                  ; -> sub_66d656a
66d1666  movups xmm0,[rdi+0x60]                        
66d166a  movaps [rbp+0xA50],xmm0                       
66d1671  mov qword ptr [rbp+0x7E0],1                   
66d167c  lea rax,[rbp+0xA50]                           
66d1683  mov [rbp+0x7E8],rax                           
66d168a  mov rax,[rbp+0xD18]                           
66d1691  movzx r8d,word ptr [rbp+0xD22]                
66d1699  mov edx,r8d                                   
66d169c  shl edx,4                                     
66d169f  mov rcx,rax                                   
66d16a2  test r8d,r8d                                  
66d16a5  je short 0x66D16D5                            ; -> loc_66d16d5
66d16a7  mov r8,[0x129F8FB8]                           ; [data_129f8fb8]
66d16ae  mov r9,rdx                                    
66d16b1  mov rcx,rax                                   
66d16b4  nop [rax+rax]                                 
loc_66d16c0:  ; from 66d16d1
66d16c0  mov r10,[rcx]                                 
66d16c3  cmp [r10+0x28],r8                             
66d16c7  je short 0x66D16D5                            ; -> loc_66d16d5
66d16c9  add rcx,0x10                                  
66d16cd  add r9,0xFFFFFFFFFFFFFFF0                     
66d16d1  jne short 0x66D16C0                           ; -> loc_66d16c0
66d16d3  jmp short 0x66D170B                           ; -> loc_66d170b
loc_66d16d5:  ; from 66d16a5, 66d16c7
66d16d5  add rdx,rax                                   
66d16d8  cmp rcx,rdx                                   
66d16db  jae short 0x66D170B                           ; -> loc_66d170b
66d16dd  sub ecx,eax                                   
66d16df  shr ecx,4                                     
66d16e2  mov [rbp+0x4D0],cx                            
66d16e9  mov byte ptr [rbp+0x4D2],1                    
66d16f0  lea rdx,[rbp+0x4D0]                           
66d16f7  lea r8,[rbp+0x7E0]                            
66d16fe  lea rcx,[rbp+0xCE8]                           
66d1705  call 0x5679DB0                                ; -> sub_5679db0
66d170a  nop                                           
loc_66d170b:  ; from 66d16d3, 66d16db
66d170b  mov rbx,[rbp+0xD90]                           
66d1712  test ebx,0x4000                               
66d1718  mov r14,[rbp+0xD78]                           
66d171f  je 0x66D17F9                                  ; -> loc_66d17f9
66d1725  mov eax,[0x129F8FD0]                          ; [data_129f8fd0]
```
`//` [V] jg 0x66d656a fall-through. movups xmm0=[rdi+0x60]->[rbp+0xA50]; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50 [V]. 13th table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22] (count); edx<<4; rcx=rax; if r8d==0 ->0x66d16d5; else r8=[0x129F8FB8] (11th global); r9=rdx; scan [r10+0x28]==r8 [V]; match->0x66d16d5; no match->0x66d170b. End-bound add rdx,rax; cmp rcx,rdx jae 0x66d170b; else index=(ecx-rax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (13th call); nop. Converge 0x66d170b: rbx=[rbp+0xD90]; test ebx,0x4000; r14=[rbp+0xD78]; je 0x66d17f9; if set mov eax,[0x129F8FD0] (phase 19). [I]: 13 call-0x5679db0 total; flag bit 0x4000 on ebx gates next TLS/data check.
## Phase 19 — 0x66d1725, 40 instructions [V]
```
66d1725  mov eax,[0x129F8FD0]                          ; [data_129f8fd0]
66d172b  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1731  mov rdx,gs:[0x58]                             
66d173a  mov rcx,[rdx+rcx*8]                           
66d173e  cmp eax,[rcx+4]                               
66d1744  jg 0x66D67A9                                  ; -> sub_66d67a9
66d174a  movaps xmm0,[0xEF40DE0]                       ; [data_ef40de0]
66d1751  movaps [rbp+0xA50],xmm0                       
66d1758  mov qword ptr [rbp+0x7E0],1                   
66d1763  lea rax,[rbp+0xA50]                           
66d176a  mov [rbp+0x7E8],rax                           
66d1771  mov rax,[rbp+0xD18]                           
66d1778  movzx r8d,word ptr [rbp+0xD22]                
66d1780  mov edx,r8d                                   
66d1783  shl edx,4                                     
66d1786  mov rcx,rax                                   
66d1789  test r8d,r8d                                  
66d178c  je short 0x66D17B5                            ; -> loc_66d17b5
66d178e  mov r8,[0x129F8FC8]                           ; [data_129f8fc8]
66d1795  mov r9,rdx                                    
66d1798  mov rcx,rax                                   
66d179b  nop [rax+rax]                                 
loc_66d17a0:  ; from 66d17b1
66d17a0  mov r10,[rcx]                                 
66d17a3  cmp [r10+0x28],r8                             
66d17a7  je short 0x66D17B5                            ; -> loc_66d17b5
66d17a9  add rcx,0x10                                  
66d17ad  add r9,0xFFFFFFFFFFFFFFF0                     
66d17b1  jne short 0x66D17A0                           ; -> loc_66d17a0
66d17b3  jmp short 0x66D17EB                           ; -> loc_66d17eb
loc_66d17b5:  ; from 66d178c, 66d17a7
66d17b5  add rdx,rax                                   
66d17b8  cmp rcx,rdx                                   
66d17bb  jae short 0x66D17EB                           ; -> loc_66d17eb
66d17bd  sub ecx,eax                                   
66d17bf  shr ecx,4                                     
66d17c2  mov [rbp+0x4D0],cx                            
66d17c9  mov byte ptr [rbp+0x4D2],1                    
66d17d0  lea rdx,[rbp+0x4D0]                           
66d17d7  lea r8,[rbp+0x7E0]                            
66d17de  lea rcx,[rbp+0xCE8]                           
66d17e5  call 0x5679DB0                                ; -> sub_5679db0
66d17ea  nop                                           
```
`//` [V] TLS gate: eax=[0x129F8FD0]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d67a9 (same pattern as phase 3/15/17). movaps xmm0=[0xEF40DE0] (16-byte .rodata constant, first non-[rdi+off] value) ->[rbp+0xA50] [V]; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50. 14th table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx<<4; rcx=rax; if r8d==0 ->0x66d17b5; else r8=[0x129F8FC8] (12th global); scan [r10+0x28]==r8 [V]; match->0x66d17b5; no match->0x66d17eb. End: index=(ecx-rax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (14th call); nop (phase 20). [I]: 14 call-0x5679db0 total; each attaches {u16 index@[rbp+0x4D0], flag byte [rbp+0x4D2]=1, 16-byte value@[rbp+0x7E8]} to out struct [rbp+0xCE8].
## Phase 20 — 0x66d17ea, 40 instructions [V]
```
66d17ea  nop                                           
66d17eb  mov rbx,[rbp+0xD90]                           
66d17f2  mov r14,[rbp+0xD78]                           
66d17f9  cmp byte ptr [r14+0x130],1                    
66d1801  mov r15,[rbp+0xE20]                           
66d1808  jne 0x66D189C                                 ; -> loc_66d189c
66d180e  mov eax,[0x129F8FE0]                          ; [data_129f8fe0]
66d1814  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d181a  mov rdx,gs:[0x58]                             
66d1823  mov rcx,[rdx+rcx*8]                           
66d1827  cmp eax,[rcx+4]                               
66d182d  jg 0x66D681B                                  ; -> sub_66d681b
66d1833  mov rax,[r14+0x70]                            
66d1837  mov [rbp+0xA50],rax                           
66d183e  cmp rax,0xFFFFFFFFFFFFFFFF                    
66d1842  je 0x66D5F14                                  ; -> sub_66d5f14
66d1848  mov [rbp+0xA58],r14                           
66d184f  mov rax,[rbp+0xD18]                           
66d1856  movzx r8d,word ptr [rbp+0xD22]                
66d185e  mov edx,r8d                                   
66d1861  shl edx,4                                     
66d1864  mov rcx,rax                                   
66d1867  test r8d,r8d                                  
66d186a  je 0x66D193C                                  ; -> loc_66d193c
66d1870  mov r8,[0x129F8FD8]                           ; [data_129f8fd8]
66d1877  mov r9,rdx                                    
66d187a  mov rcx,rax                                   
66d187d  nop [rax]                                     
loc_66d1880:  ; from 66d1895
66d1880  mov r10,[rcx]                                 
66d1883  cmp [r10+0x28],r8                             
66d1887  je 0x66D193C                                  ; -> loc_66d193c
66d188d  add rcx,0x10                                  
66d1891  add r9,0xFFFFFFFFFFFFFFF0                     
66d1895  jne short 0x66d1880                           ; -> loc_66d1880
66d1897  jmp 0x66D1972                                 ; -> loc_66d1972
loc_66d189c:  ; from 66d1808
66d189c  cmp byte ptr [r15+0x118],1                    
66d18a4  jne 0x66D1CE2                                 ; -> loc_66d1ce2
66d18aa  mov eax,[0x129F9010]                          ; [data_129f9010]
66d18b0  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d18b6  mov rdx,gs:[0x58]                             
66d18bf  mov rcx,[rdx+rcx*8]                           
```
`//` [V] nop; rbx=[rbp+0xD90]; r14=[rbp+0xD78]; cmp byte [r14+0x130],1; r15=[rbp+0xE20]; jne 0x66d189c. PathA ([r14+0x130]==1): TLS gate eax=[0x129F8FE0]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d681b [V]; mov rax,[r14+0x70]; [rbp+0xA50]=rax; cmp rax,-1 je 0x66d5f14; [rbp+0xA58]=r14 [V]. 15th table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx<<4; rcx=rax; if r8d==0 ->0x66d193c; else r8=[0x129F8FD8] (13th global); scan [r10+0x28]==r8; match->0x66d193c; no match->jmp 0x66d1972 [V]. PathB (0x66d189c, [r14+0x130]!=1): cmp byte [r15+0x118],1; jne 0x66d1ce2; if ==1: TLS gate eax=[0x129F9010]... (continues phase 21) [V]. [I]: major fork on byte [r14+0x130]; PathA stores [r14+0x70] as 8-byte value at [rbp+0xA50] with ctrl=[rbp+0xA58]=r14 (shared_ptr slot); 15 call-0x5679db0 pending for PathA scan.
## Phase 21 — 0x66d18bf, 40 instructions [V]
```
66d18bf  mov rcx,[rdx+rcx*8]                           ; R a1+0x0+idx
66d18c3  cmp eax,[rcx+4]                               ; R *(a1+0x0+idx)+0x4
66d18c9  jg 0x66D6B4F                                  ; -> sub_66d6b4f
66d18cf  mov rax,[r15+0x80]                            
66d18d6  mov [rbp+0xA50],rax                           
66d18dd  cmp rax,0xFFFFFFFFFFFFFFFF                    
66d18e1  je 0x66D5F14                                  ; -> sub_66d5f14
66d18e7  mov [rbp+0xA58],r15                           
66d18ee  mov rax,[rbp+0xD18]                           
66d18f5  movzx r8d,word ptr [rbp+0xD22]                
66d18fd  mov edx,r8d                                   
66d1900  shl edx,4                                     
66d1903  mov rcx,rax                                   
66d1906  test r8d,r8d                                  
66d1909  je 0x66D1B07                                  ; -> loc_66d1b07
66d190f  mov r8,[0x129F9008]                           ; [data_129f9008]
66d1916  mov r9,rdx                                    
66d1919  mov rcx,rax                                   
66d191c  nop [rax]                                     
loc_66d1920:  ; from 66d1935
66d1920  mov r10,[rcx]                                 
66d1923  cmp [r10+0x28],r8                             
66d1927  je 0x66D1B07                                  ; -> loc_66d1b07
66d192d  add rcx,0x10                                  
66d1931  add r9,0xFFFFFFFFFFFFFFF0                     
66d1935  jne short 0x66D1920                           ; -> loc_66d1920
66d1937  jmp 0x66D1B3D                                 ; -> loc_66d1b3d
66d193c  add rdx,rax                                   
66d193f  cmp rcx,rdx                                   
66d1942  jae short 0x66D1972                           ; -> loc_66d1972
66d1944  sub ecx,eax                                   
66d1946  shr ecx,4                                     
66d1949  mov [rbp+0x7E0],cx                            
66d1950  mov byte ptr [rbp+0x7E2],1                    
66d1957  lea rdx,[rbp+0x7E0]                           
66d195e  lea r8,[rbp+0xA50]                            
66d1965  lea rcx,[rbp+0xCE8]                           
66d196c  call 0x5679DB0                                ; -> sub_5679db0
66d1971  nop                                           
loc_66d1972:  ; from 66d1942
66d1972  mov eax,[0x129F8FF0]                          ; [data_129f8ff0]
66d1978  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d197e  mov rdx,gs:[0x58]                             
```
`//` [V] PathB TLS: mov rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d6b4f. mov rax=[r15+0x80]; [rbp+0xA50]=rax; cmp rax,-1 je 0x66d5f14; [rbp+0xA58]=r15 [V] (shared_ptr slot: ptr=[rbp+0xA50], ctrl=[rbp+0xA58]). 16th table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx<<4; rcx=rax; if r8d==0 ->0x66d1b07; else r8=[0x129F9008] (14th global); scan [r10+0x28]==r8; match->0x66d1b07; no match->jmp 0x66d1b3d [V]. Match end: index=(ecx-rax)>>4 -> [rbp+0x7E0] (cx) [NEW slot pair vs [rbp+0x4D0]]; byte [rbp+0x7E2]=1; call 0x5679DB0(rdx=&rbp+0x7E0, r8=&rbp+0xA50, rcx=&rbp+0xCE8) [V] (16th call); nop. Converge 0x66d1972: eax=[0x129F8FF0]; ecx=[0x128767C8]; rdx=gs:[0x58] (phase 22). [I]: second index slot pair [rbp+0x7E0]/[rbp+0x7E2]; value [r15+0x80] (8B), ctrl r15. 16 call-0x5679db0 total.
## Phase 22 — 0x66d197e, 40 instructions [V]
```
66d197e  mov rdx,gs:[0x58]                             
66d1987  mov rcx,[rdx+rcx*8]                           
66d198b  cmp eax,[rcx+4]                               
66d1991  jg 0x66D688D                                  ; -> sub_66d688d
66d1997  mov rcx,[rbp+0xD78]                           
66d199e  mov rax,[rcx+0xE8]                            
66d19a5  mov [rbp+0xA50],rax                           
66d19ac  cmp rax,0xFFFFFFFFFFFFFFFF                    
66d19b0  je 0x66D5F14                                  ; -> sub_66d5f14
66d19b6  lea rax,[rcx+0x78]                            
66d19ba  mov [rbp+0xA58],rax                           
66d19c1  mov rax,[rbp+0xD18]                           
66d19c8  movzx r8d,word ptr [rbp+0xD22]                
66d19d0  mov edx,r8d                                   
66d19d3  shl edx,4                                     
66d19d6  mov rcx,rax                                   
66d19d9  test r8d,r8d                                  
66d19dc  je short 0x66D1A05                            ; -> loc_66d1a05
66d19de  mov r8,[0x129F8FE8]                           ; [data_129f8fe8]
66d19e5  mov r9,rdx                                    
66d19e8  mov rcx,rax                                   
66d19eb  nop [rax+rax]                                 
loc_66d19f0:  ; from 66d1a01
66d19f0  mov r10,[rcx]                                 
66d19f3  cmp [r10+0x28],r8                             
66d19f7  je short 0x66D1A05                            ; -> loc_66d1a05
66d19f9  add rcx,0x10                                  
66d19fd  add r9,0xFFFFFFFFFFFFFFF0                     
66d1a01  jne short 0x66d19f0                           ; -> loc_66d19f0
66d1a03  jmp short 0x66D1A3B                           ; -> loc_66d1a3b
loc_66d1a05:  ; from 66d19dc, 66d19f7
66d1a05  add rdx,rax                                   
66d1a08  cmp rcx,rdx                                   
66d1a0b  jae short 0x66D1A3B                           ; -> loc_66d1a3b
66d1a0d  sub ecx,eax                                   
66d1a0f  shr ecx,4                                     
66d1a12  mov [rbp+0x7E0],cx                            
66d1a19  mov byte ptr [rbp+0x7E2],1                    
66d1a20  lea rdx,[rbp+0x7E0]                           
66d1a27  lea r8,[rbp+0xA50]                            
66d1a2e  lea rcx,[rbp+0xCE8]                           
66d1a35  call 0x5679DB0                                ; -> sub_5679db0
66d1a3a  nop                                           
```
`//` [V] PathB TLS cont.: rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d688d. rcx=[rbp+0xD78] (=r14); rax=[rcx+0xE8]; [rbp+0xA50]=rax; cmp rax,-1 je 0x66d5f14; lea rax,[rcx+0x78]; [rbp+0xA58]=rax (ctrl = r14+0x78, pointer into object — differs from earlier r14/r15 ctrl) [V]. 17th table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx<<4; rcx=rax; if r8d==0 ->0x66d1a05; else r8=[0x129F8FE8] (15th global); scan [r10+0x28]==r8; match->0x66d1a05; no match->jmp 0x66d1a3b [V]. Match end: index=(ecx-rax)>>4->[rbp+0x7E0]; byte [rbp+0x7E2]=1; call 0x5679DB0(&rbp+0x7E0,&rbp+0xA50,&rbp+0xCE8) [V] (17th call); nop (phase 23). [I]: value [r14+0xE8] (8B), ctrl [r14+0x78]; slot pair now [rbp+0x7E0]/[rbp+0x7E2]. 17 call-0x5679db0 total.
## Phase 23 — 0x66d1a3a, 40 instructions [V]
```
66d1a3a  nop                                           
66d1a3b  mov eax,[0x129F9000]                          ; [data_129f9000]
66d1a41  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1a47  mov rdx,gs:[0x58]                             
66d1a50  mov rcx,[rdx+rcx*8]                           
66d1a54  cmp eax,[rcx+4]                               
66d1a5a  jg 0x66D6971                                  ; -> sub_66d6971
66d1a60  mov rax,[rbp+0xD78]                           
66d1a67  add rax,0xF0                                  
66d1a6d  mov qword ptr [rbp+0xA50],4                   
66d1a78  mov [rbp+0xA58],rax                           
66d1a7f  mov rax,[rbp+0xD18]                           
66d1a86  movzx r8d,word ptr [rbp+0xD22]                
66d1a8e  mov edx,r8d                                   
66d1a91  shl edx,4                                     
66d1a94  mov rcx,rax                                   
66d1a97  test r8d,r8d                                  
66d1a9a  je short 0x66D1AC8                            ; -> loc_66d1ac8
66d1a9c  mov r8,[0x129F8FF8]                           ; [data_129f8ff8]
66d1aa3  mov r9,rdx                                    
66d1aa6  mov rcx,rax                                   
66d1aa9  nop [rax]                                     
loc_66d1ab0:  ; from 66d1ac1
66d1ab0  mov r10,[rcx]                                 
66d1ab3  cmp [r10+0x28],r8                             
66d1ab7  je short 0x66D1AC8                            ; -> loc_66d1ac8
66d1ab9  add rcx,0x10                                  
66d1abd  add r9,0xFFFFFFFFFFFFFFF0                     
66d1ac1  jne short 0x66d1ab0                           ; -> loc_66d1ab0
66d1ac3  jmp 0x66D1CDB                                 ; -> loc_66d1cdb
loc_66d1ac8:  ; from 66d1a9a, 66d1ab7
66d1ac8  add rdx,rax                                   
66d1acb  cmp rcx,rdx                                   
66d1ace  jae 0x66D1CDB                                 ; -> loc_66d1cdb
66d1ad4  sub ecx,eax                                   
66d1ad6  shr ecx,4                                     
66d1ad9  mov [rbp+0x7E0],cx                            
66d1ae0  mov byte ptr [rbp+0x7E2],1                    
66d1ae7  lea rdx,[rbp+0x7E0]                           
66d1aee  lea r8,[rbp+0xA50]                            
66d1af5  lea rcx,[rbp+0xCE8]                           
66d1afc  call 0x5679DB0                                ; -> sub_5679db0
66d1b01  nop                                           
```
`//` [V] PathB TLS cont.: eax=[0x129F9000]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d6971. rax=[rbp+0xD78] (=r14); rax+=0xF0; [rbp+0xA50]=4 (immediate u64 4, not a pointer — first immediate value) [V]; [rbp+0xA58]=rax (ctrl=r14+0xF0). 18th table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx<<4; rcx=rax; if r8d==0 ->0x66d1ac8; else r8=[0x129F8FF8] (16th global); scan [r10+0x28]==r8; match->0x66d1ac8; no match->jmp 0x66d1cdb [V]. Match end: index=(ecx-rax)>>4->[rbp+0x7E0]; byte [rbp+0x7E2]=1; call 0x5679DB0(&rbp+0x7E0,&rbp+0xA50,&rbp+0xCE8) [V] (18th call); nop (phase 24). [I]: [rbp+0xA50] holds immediate 4 here; ctrl=r14+0xF0; slot pair [rbp+0x7E0]/[rbp+0x7E2]. 18 call-0x5679db0 total.
## Phase 24 — 0x66d1b01, 40 instructions [V]
```
66d1b01  nop                                           
66d1b02  jmp 0x66D1CDB                                 ; -> loc_66d1cdb
66d1b07  add rdx,rax                                   
66d1b0a  cmp rcx,rdx                                   
66d1b0d  jae short 0x66D1B3D                           ; -> loc_66d1b3d
66d1b0f  sub ecx,eax                                   
66d1b11  shr ecx,4                                     
66d1b14  mov [rbp+0x7E0],cx                            
66d1b1b  mov byte ptr [rbp+0x7E2],1                    
66d1b22  lea rdx,[rbp+0x7E0]                           
66d1b29  lea r8,[rbp+0xA50]                            
66d1b30  lea rcx,[rbp+0xCE8]                           
66d1b37  call 0x5679DB0                                ; -> sub_5679db0
66d1b3c  nop                                           
loc_66d1b3d:  ; from 66d1b0d
66d1b3d  mov eax,[0x129F9020]                          ; [data_129f9020]
66d1b43  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1b49  mov rdx,gs:[0x58]                             
66d1b52  mov rcx,[rdx+rcx*8]                           
66d1b56  cmp eax,[rcx+4]                               
66d1b5c  jg 0x66D6BC1                                  ; -> sub_66d6bc1
66d1b62  mov rcx,[rbp+0xE20]                           
66d1b69  mov rax,[rcx+0x108]                           
66d1b70  mov [rbp+0xA50],rax                           
66d1b77  cmp rax,0xFFFFFFFFFFFFFFFF                    
66d1b7b  je 0x66D5F14                                  ; -> sub_66d5f14
66d1b81  lea rax,[rcx+0x88]                            
66d1b88  mov [rbp+0xA58],rax                           
66d1b8f  mov rax,[rbp+0xD18]                           
66d1b96  movzx r8d,word ptr [rbp+0xD22]                
66d1b9e  mov edx,r8d                                   
66d1ba1  shl edx,4                                     
66d1ba4  mov rcx,rax                                   
66d1ba7  test r8d,r8d                                  
66d1baa  je short 0x66D1BD5                            ; -> loc_66d1bd5
66d1bac  mov r8,[0x129F9018]                           ; [data_129f9018]
66d1bb3  mov r9,rdx                                    
66d1bb6  mov rcx,rax                                   
66d1bb9  nop [rax]                                     
loc_66d1bc0:  ; from 66d1bd1
66d1bc0  mov r10,[rcx]                                 
66d1bc3  cmp [r10+0x28],r8                             
66d1bc7  je short 0x66D1BD5                            ; -> loc_66d1bd5
```
`//` [V] nop; jmp 0x66d1cdb (skip phase-21 match-end). Block at 0x66d1b07 (phase-21 match-end target): add rdx,rax; cmp rcx,rdx; jae 0x66d1b3d; else index=(ecx-rax)>>4->[rbp+0x7E0]; byte [rbp+0x7E2]=1; call 0x5679DB0(&rbp+0x7E0,&rbp+0xA50,&rbp+0xCE8) [V] (19th call); nop. TLS at 0x66d1b3d: eax=[0x129F9020]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d6bc1. rcx=[rbp+0xE20] (=r15); rax=[rcx+0x108]; [rbp+0xA50]=rax; cmp rax,-1 je 0x66d5f14; lea rax,[rcx+0x88]; [rbp+0xA58]=rax (ctrl=r15+0x88) [V]. 20th table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx<<4; rcx=rax; if r8d==0 ->0x66d1bd5; else r8=[0x129F9018] (17th global); scan [r10+0x28]==r8 (continues phase 25) [V]. [I]: value [r15+0x108] (8B), ctrl [r15+0x88]; slot pair [rbp+0x7E0]/[rbp+0x7E2]. 19 call-0x5679db0 total.
## Phase 25 — 0x66d1bc7, 40 instructions [V]
```
66d1bc7  je short 0x66D1BD5                            ; -> loc_66d1bd5
66d1bc9  add rcx,0x10                                  
66d1bcd  add r9,0xFFFFFFFFFFFFFFF0                     
66d1bd1  jne short 0x66D1BC0                           ; -> sub_66d1bc0
66d1bd3  jmp short 0x66D1C0B                           ; -> loc_66d1c0b
loc_66d1bd5:  ; from 66d1bc7
66d1bd5  add rdx,rax                                   
66d1bd8  cmp rcx,rdx                                   
66d1bdb  jae short 0x66D1C0B                           ; -> loc_66d1c0b
66d1bdd  sub ecx,eax                                   
66d1bdf  shr ecx,4                                     
66d1be2  mov [rbp+0x7E0],cx                            
66d1be9  mov byte ptr [rbp+0x7E2],1                    
66d1bf0  lea rdx,[rbp+0x7E0]                           
66d1bf7  lea r8,[rbp+0xA50]                            
66d1bfe  lea rcx,[rbp+0xCE8]                           
66d1c05  call 0x5679DB0                                ; -> sub_5679db0
66d1c0a  nop                                           
loc_66d1c0b:  ; from 66d1bd3, 66d1bdb
66d1c0b  mov eax,[0x129F9030]                          ; [data_129f9030]
66d1c11  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1c17  mov rdx,gs:[0x58]                             
66d1c20  mov rcx,[rdx+rcx*8]                           
66d1c24  cmp eax,[rcx+4]                               
66d1c2a  jg 0x66D6C39                                  ; -> sub_66d6c39
66d1c30  mov rax,[rbp+0xE20]                           
66d1c37  movups xmm0,[rax+0x110]                       
66d1c3e  shufps xmm0,xmm0,0                            
66d1c42  movaps [rbp+0xA50],xmm0                       
66d1c49  mov qword ptr [rbp+0x7E0],1                   
66d1c54  lea rax,[rbp+0xA50]                           
66d1c5b  mov [rbp+0x7E8],rax                           
66d1c62  mov rax,[rbp+0xD18]                           
66d1c69  movzx r8d,word ptr [rbp+0xD22]                
66d1c71  mov edx,r8d                                   
66d1c74  shl edx,4                                     
66d1c77  mov rcx,rax                                   
66d1c7a  test r8d,r8d                                  
66d1c7d  je short 0x66D1CA5                            ; -> loc_66d1ca5
66d1c7f  mov r8,[0x129F9028]                           ; [data_129f9028]
66d1c86  mov r9,rdx                                    
66d1c89  mov rcx,rax                                   
66d1c8c  nop [rax]                                     
```
`//` [V] Phase-20 scan tail: je 0x66d1bd5; add rcx,0x10; add r9,-0x10; jne 0x66d1bc0; jmp 0x66d1c0b. Match-end 0x66d1bd5: add rdx,rax; cmp rcx,rdx; jae 0x66d1c0b; else index=(ecx-rax)>>4->[rbp+0x7E0]; byte [rbp+0x7E2]=1; call 0x5679DB0(&rbp+0x7E0,&rbp+0xA50,&rbp+0xCE8) [V] (20th call); nop. Converge 0x66d1c0b: TLS eax=[0x129F9030]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d6c39. rax=[rbp+0xE20] (=r15); movups xmm0=[rax+0x110]; shufps xmm0,xmm0,0 (broadcast lo dword); [rbp+0xA50]=xmm0 (16 bytes) [V]; mov qword ptr [rbp+0x7E0],1 (qword, clobbers index+flag slots); [rbp+0x7E8]=&rbp+0xA50 [V]. 21st table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx<<4; rcx=rax; if r8d==0 ->0x66d1ca5; else r8=[0x129F9028] (18th global); scan continues phase 26 [V]. [I]: value = broadcast [r15+0x110]; count written as qword 1 (variant calling pattern). 20 call-0x5679db0 total.
## Phase 26 — 0x66d1c8c, 40 instructions [V]
```
66d1c8c  nop [rax]                                     
loc_66d1c90:  ; from 66d1ca1
66d1c90  mov r10,[rcx]                                 ; R a0+0x0
66d1c93  cmp [r10+0x28],r8                             ; R *(a0+0x0)+0x28
66d1c97  je short 0x66D1CA5                            ; -> loc_66d1ca5
66d1c99  add rcx,0x10                                  
66d1c9d  add r9,0xFFFFFFFFFFFFFFF0                     
66d1ca1  jne short 0x66d1c90                           ; -> loc_66d1c90
66d1ca3  jmp short 0x66D1CDB                           ; -> loc_66d1cdb
loc_66d1ca5:  ; from 66d1c97
66d1ca5  add rdx,rax                                   
66d1ca8  cmp rcx,rdx                                   
66d1cab  jae short 0x66D1CDB                           ; -> loc_66d1cdb
66d1cad  sub ecx,eax                                   
66d1caf  shr ecx,4                                     
66d1cb2  mov [rbp+0x4D0],cx                            
66d1cb9  mov byte ptr [rbp+0x4D2],1                    
66d1cc0  lea rdx,[rbp+0x4D0]                           
66d1cc7  lea r8,[rbp+0x7E0]                            
66d1cce  lea rcx,[rbp+0xCE8]                           
66d1cd5  call 0x5679DB0                                ; -> sub_5679db0
66d1cda  nop                                           
loc_66d1cdb:  ; from 66d1ca3, 66d1cab
66d1cdb  mov rbx,[rbp+0xD90]                           
66d1ce2  mov eax,[0x129F9040]                          ; [data_129f9040]
66d1ce8  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1cee  mov rdx,gs:[0x58]                             
66d1cf7  mov rcx,[rdx+rcx*8]                           
66d1cfb  cmp eax,[rcx+4]                               
66d1d01  jg 0x66D61DA                                  ; -> sub_66d61da
66d1d07  test ebx,0x1000                               
66d1d0d  jne short 0x66D1D78                           ; -> loc_66d1d78
66d1d0f  xorps xmm0,xmm0                               
66d1d12  movaps [rbp+0xA50],xmm0                       
66d1d19  mov qword ptr [rbp+0x7E0],1                   
66d1d24  lea rax,[rbp+0xA50]                           
66d1d2b  mov [rbp+0x7E8],rax                           
66d1d32  mov rax,[rbp+0xD18]                           
66d1d39  movzx r8d,word ptr [rbp+0xD22]                
66d1d41  mov edx,r8d                                   
66d1d44  shl edx,4                                     
66d1d47  mov rcx,rax                                   
66d1d4a  test r8d,r8d                                  
66d1d4d  je 0x66D1DE5                                  ; -> loc_66d1de5
```
`//` [V] Phase-21 scan tail: nop; mov r10,[rcx]; cmp [r10+0x28],r8; je 0x66d1ca5; add rcx,0x10; add r9,-0x10; jne 0x66d1c90; jmp 0x66d1cdb. Match-end 0x66d1ca5: add rdx,rax; cmp rcx,rdx; jae 0x66d1cdb; else index=(ecx-rax)>>4->[rbp+0x4D0] (back to first slot pair); byte [rbp+0x4D2]=1; call 0x5679DB0(rdx=&rbp+0x4D0, r8=&rbp+0x7E0 (holds qword 1 from phase 25!), rcx=&rbp+0xCE8) [V] (21st call); nop — mixed slots. Converge 0x66d1cdb: rbx=[rbp+0xD90]; TLS eax=[0x129F9040]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d61da. test ebx,0x1000; jne 0x66d1d78; else xorps xmm0; [rbp+0xA50]=0 (16B zero); [rbp+0x7E0]=1 (qword); [rbp+0x7E8]=&rbp+0xA50 [V]. 22nd table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx<<4; rcx=rax; if r8d==0 ->0x66d1de5 (phase 27) [V]. [I]: slot pairs alternate; zero-xmm value path gated by ebx bit 0x1000. 21 call-0x5679db0 total.
## Phase 27 — 0x66d1d4d, 40 instructions [V]
```
66d1d4d  je 0x66D1DE5                                  ; -> loc_66d1de5
66d1d53  mov r8,[0x129F9038]                           ; [data_129f9038]
66d1d5a  mov r9,rdx                                    
66d1d5d  mov rcx,rax                                   
loc_66d1d60:  ; from 66d1d71
66d1d60  mov r10,[rcx]                                 
66d1d63  cmp [r10+0x28],r8                             
66d1d67  je short 0x66D1DE5                            ; -> loc_66d1de5
66d1d69  add rcx,0x10                                  
66d1d6d  add r9,0xFFFFFFFFFFFFFFF0                     
66d1d71  jne short 0x66d1d60                           ; -> loc_66d1d60
66d1d73  jmp 0x66D1E53                                 ; -> loc_66d1e53
66d1d78  movaps xmm0,[0xEF40DE0]                       ; [data_ef40de0]
66d1d7f  movaps [rbp+0xA50],xmm0                       
66d1d86  mov qword ptr [rbp+0x7E0],1                   
66d1d91  lea rax,[rbp+0xA50]                           
66d1d98  mov [rbp+0x7E8],rax                           
66d1d9f  mov rax,[rbp+0xD18]                           
66d1da6  movzx r8d,word ptr [rbp+0xD22]                
66d1dae  mov edx,r8d                                   
66d1db1  shl edx,4                                     
66d1db4  mov rcx,rax                                   
66d1db7  test r8d,r8d                                  
66d1dba  je short 0x66D1E1D                            ; -> loc_66d1e1d
66d1dbc  mov r8,[0x129F9038]                           ; [data_129f9038]
66d1dc3  mov r9,rdx                                    
66d1dc6  mov rcx,rax                                   
66d1dc9  nop [rax]                                     
loc_66d1dd0:  ; from 66d1de1
66d1dd0  mov r10,[rcx]                                 
66d1dd3  cmp [r10+0x28],r8                             
66d1dd7  je short 0x66D1E1D                            ; -> loc_66d1e1d
66d1dd9  add rcx,0x10                                  
66d1ddd  add r9,0xFFFFFFFFFFFFFFF0                     
66d1de1  jne short 0x66d1dd0                           ; -> loc_66d1dd0
66d1de3  jmp short 0x66D1E53                           ; -> loc_66d1e53
loc_66d1de5:  ; from 66d1d4d, 66d1d67
66d1de5  add rdx,rax                                   
66d1de8  cmp rcx,rdx                                   
66d1deb  jae short 0x66D1E53                           ; -> loc_66d1e53
66d1ded  sub ecx,eax                                   
66d1def  shr ecx,4                                     
66d1df2  mov [rbp+0x4D0],cx                            
66d1df9  mov byte ptr [rbp+0x4D2],1                    
```
`//` [V] Phase-22 scan tail: je 0x66d1de5; mov r8=[0x129F9038] (19th global); r9=rdx; rcx=rax; scan [r10+0x28]==r8; match->0x66d1de5; add rcx,0x10; add r9,-0x10; jne; jmp 0x66d1e53. Alternate path (ebx bit 0x1000 set, from phase 26): movaps xmm0=[0xEF40DE0] (same const as phase 19); [rbp+0xA50]=xmm0; [rbp+0x7E0]=1 (qword); [rbp+0x7E8]=&rbp+0xA50. 23rd table scan: rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx<<4; rcx=rax; if r8d==0 ->0x66d1e1d; else r8=[0x129F9038] (same 19th global); scan continues phase 28. Match-end 0x66d1de5: add rdx,rax; cmp rcx,rdx; jae 0x66d1e53; else index=(ecx-rax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1 (phase 28). [I]: constant 0xEF40DE0 reused as 16B value; qword-count pattern.
## Phase 28 — 0x66d1df9, 40 instructions [V]
```
66d1df9  mov byte ptr [rbp+0x4D2],1                    
66d1e00  lea rdx,[rbp+0x4D0]                           
66d1e07  lea r8,[rbp+0x7E0]                            
66d1e0e  lea rcx,[rbp+0xCE8]                           
66d1e15  call 0x5679DB0                                ; -> sub_5679db0
66d1e1a  nop                                           
66d1e1b  jmp short 0x66D1E53                           ; -> loc_66d1e53
66d1e1d  add rdx,rax                                   
66d1e20  cmp rcx,rdx                                   
66d1e23  jae short 0x66D1E53                           ; -> loc_66d1e53
66d1e25  sub ecx,eax                                   
66d1e27  shr ecx,4                                     
66d1e2a  mov [rbp+0x4D0],cx                            
66d1e31  mov byte ptr [rbp+0x4D2],1                    
66d1e38  lea rdx,[rbp+0x4D0]                           
66d1e3f  lea r8,[rbp+0x7E0]                            
66d1e46  lea rcx,[rbp+0xCE8]                           
66d1e4d  call 0x5679DB0                                ; -> sub_5679db0
66d1e52  nop                                           
loc_66d1e53:  ; from 66d1e1b, 66d1e23
66d1e53  mov eax,[0x129F9050]                          ; [data_129f9050]
66d1e59  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1e5f  mov rdx,gs:[0x58]                             
66d1e68  mov rcx,[rdx+rcx*8]                           
66d1e6c  cmp eax,[rcx+4]                               
66d1e72  jg 0x66D624C                                  ; -> sub_66d624c
66d1e78  mov eax,[0x129F9060]                          ; [data_129f9060]
66d1e7e  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1e84  mov rdx,gs:[0x58]                             
66d1e8d  mov rcx,[rdx+rcx*8]                           
66d1e91  cmp eax,[rcx+4]                               
66d1e97  jg 0x66D62BE                                  ; -> sub_66d62be
66d1e9d  mov eax,[0x129F9070]                          ; [data_129f9070]
66d1ea3  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1ea9  mov rdx,gs:[0x58]                             
66d1eb2  mov rcx,[rdx+rcx*8]                           
66d1eb6  cmp eax,[rcx+4]                               
66d1ebc  jg 0x66D6330                                  ; -> sub_66d6330
66d1ec2  mov eax,[0x129F9080]                          ; [data_129f9080]
66d1ec8  mov ecx,[0x128767C8]                          ; [data_128767c8]
66d1ece  mov rdx,gs:[0x58]                             
66d1ed7  mov rcx,[rdx+rcx*8]                           
```
`//` [V] Phase-27 match-end cont.: byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (22nd call); jmp 0x66d1e53. Alternate match-end (0x66d1e1d): add rdx,rax; cmp rcx,rdx; jae 0x66d1e53; else index->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0 [V] (23rd call); nop. Converge 0x66d1e53: BURST of TLS gates [V], each: mov eax,[data global]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg <target>: [0x129F9050]->0x66d624c; [0x129F9060]->0x66d62be; [0x129F9070]->0x66d6330; [0x129F9080]->(continues phase 29). [I]: 23 call-0x5679db0 total; TLS burst = consecutive version/tick checks against globals 0x129F9050..0x129F9080+.
## Phase 29 — 0x66d1ed7, 40 instructions [V]
```
66d1ed7  mov rcx,[rdx+rcx*8]                           ; R a1+0x0+idx
66d1edb  cmp eax,[rcx+4]                               ; R *(a1+0x0+idx)+0x4
66d1ee1  jg 0x66D63A2                                  ; -> sub_66d63a2
66d1ee7  mov rdx,[rdi]                                 
66d1eea  cmp byte ptr [rdx+0x174],1                    
66d1ef1  jne short 0x66D1F6C                           ; -> loc_66d1f6c
66d1ef3  movss xmm0,[rdx+0x164]                        
66d1efb  shufps xmm0,xmm0,0                            
66d1eff  movaps [rbp+0xA50],xmm0                       
66d1f06  mov qword ptr [rbp+0x7E0],1                   
66d1f11  lea rax,[rbp+0xA50]                           
66d1f18  mov [rbp+0x7E8],rax                           
66d1f1f  mov rax,[rbp+0xD18]                           
66d1f26  movzx r8d,word ptr [rbp+0xD22]                
66d1f2e  mov ecx,r8d                                   
66d1f31  shl ecx,4                                     
66d1f34  mov r9,rax                                    
66d1f37  test r8d,r8d                                  
66d1f3a  je 0x66D1FEF                                  ; -> loc_66d1fef
66d1f40  mov r10,[0x129F9048]                          ; [data_129f9048]
66d1f47  xor r9d,r9d                                   
66d1f4a  nop [rax+rax]                                 
loc_66d1f50:  ; from 66d1f65
66d1f50  mov r11,[rax+r9]                              
66d1f54  cmp [r11+0x28],r10                            
66d1f58  je 0x66D1FEC                                  ; -> loc_66d1fec
66d1f5e  add r9,0x10                                   
66d1f62  cmp rcx,r9                                    
66d1f65  jne short 0x66d1f50                           ; -> loc_66d1f50
66d1f67  jmp 0x66D2041                                 ; -> loc_66d2041
loc_66d1f6c:  ; from 66d1ef1
66d1f6c  mov rax,[rbp+0xD70]                           
66d1f73  movups xmm0,[rax+0x3E0]                       
66d1f7a  shufps xmm0,xmm0,0                            
66d1f7e  movaps [rbp+0xA50],xmm0                       
66d1f85  mov qword ptr [rbp+0x7E0],1                   
66d1f90  lea rax,[rbp+0xA50]                           
66d1f97  mov [rbp+0x7E8],rax                           
66d1f9e  mov rax,[rbp+0xD18]                           
66d1fa5  movzx edx,word ptr [rbp+0xD22]                
66d1fac  mov ecx,edx                                   
66d1fae  shl ecx,4                                     
66d1fb1  mov r8,rax                                    
```
`//` [V] TLS cont.: rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg 0x66d63a2. rdx=[rdi]; cmp byte [rdx+0x174],1; if ==1: movss xmm0=[rdx+0x164]; shufps (broadcast); [rbp+0xA50]=xmm0; [rbp+0x7E0]=1(qword); [rbp+0x7E8]=&rbp+0xA50; rax=[rbp+0xD18]; r8d=[rbp+0xD22]; ecx=r8d<<4; r9=rax; if r8d==0 ->0x66d1fef; else r10=[0x129F9048] (20th global); r9d=0; scan [r11+0x28]==r10 (KEY = the global itself, r9+=0x10, limit rcx) [V]; match->0x66d1fec; no match->jmp 0x66d2041. Else (byte!=1): rax=[rbp+0xD70] (arg1!); movups xmm0=[rax+0x3E0]; shufps; [rbp+0xA50]=xmm0; [rbp+0x7E0]=1; [rbp+0x7E8]=&rbp+0xA50; rax=[rbp+0xD18]; edx=[rbp+0xD22]; ecx=edx<<4; r8=rax (phase 30). [I]: two value sources: broadcast float from [rdi+0x164] or [arg1+0x3E0]; scan key is global value directly. 23 call-0x5679db0 so far (next calls pending).
## Phase 30 — 0x66d1fb1, 40 instructions [V]
```
66d1fb1  mov r8,rax                                    
66d1fb4  test edx,edx                                  
66d1fb6  je 0x66D20AF                                  ; -> loc_66d20af
66d1fbc  mov r9,[0x129F9048]                           ; [data_129f9048]
66d1fc3  xor r8d,r8d                                   
66d1fc6  nop [rax+rax]                                 
loc_66d1fd0:  ; from 66d1fe5
66d1fd0  mov r10,[rax+r8]                              
66d1fd4  cmp [r10+0x28],r9                             
66d1fd8  je 0x66D20AC                                  ; -> loc_66d20ac
66d1fde  add r8,0x10                                   
66d1fe2  cmp rcx,r8                                    
66d1fe5  jne short 0x66d1fd0                           ; -> loc_66d1fd0
66d1fe7  jmp 0x66D20FC                                 ; -> loc_66d20fc
66d1fec  add r9,rax                                    
66d1fef  lea r10,[rax+rcx]                             
66d1ff3  cmp r9,r10                                    
66d1ff6  jae short 0x66D2041                           ; -> loc_66d2041
66d1ff8  sub r9d,eax                                   
66d1ffb  shr r9d,4                                     
66d1fff  mov [rbp+0x4D0],r9w                           
66d2007  mov byte ptr [rbp+0x4D2],1                    
66d200e  lea rdx,[rbp+0x4D0]                           
66d2015  lea r8,[rbp+0x7E0]                            
66d201c  lea rcx,[rbp+0xCE8]                           
66d2023  call 0x5679DB0                                ; -> sub_5679db0
66d2028  nop                                           
66d2029  mov rdx,[rdi]                                 
66d202c mov rax,[rbp+0xD18]                           
66d2033 movzx r8d,word ptr [rbp+0xD22]                
66d203b mov ecx,r8d                                   
66d203e shl ecx,4                                     
loc_66d2041:  ; from 66d1ff6
66d2041  movss xmm0,[rdx+0x168]                        
66d2049  shufps xmm0,xmm0,0                            
66d204d  movaps [rbp+0xA50],xmm0                       
66d2054  mov qword ptr [rbp+0x7E0],1                   
66d205f  lea r9,[rbp+0xA50]                            
66d2066  mov [rbp+0x7E8],r9                            
66d206d  mov r9,rax                                    
66d2070  test r8w,r8w                                  
66d2074  je 0x66D216F                                  ; -> loc_66d216f
66d207a  mov r10,[0x129F9058]                          ; [data_129f9058]
```
`//` [V] 25th scan tail: test edx,edx; je 0x66d20af; else r9=[0x129F9048] (20th global, again); r8d=0; scan [r10+0x28]==r9 (r8+=0x10, cmp rcx,r8); match->0x66d20ac; no match->jmp 0x66d20fc. 24th scan ends (0x66d1fec/fef): add r9,rax; lea r10,[rax+rcx]; cmp r9,r10; jae 0x66d2041; else index=(r9d-eax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (24th call); nop; rdx=[rdi]; rax=[rbp+0xD18]; r8d=[rbp+0xD22]; ecx=r8d<<4 [V] (setup for next scan). 0x66d2041 (24th scan not-found): movss xmm0=[rdx+0x168]; shufps; [rbp+0xA50]=xmm0; [rbp+0x7E0]=1(qword); [rbp+0x7E8]=&rbp+0xA50; r9=rax; test r8w,r8w; je 0x66d216f; else r10=[0x129F9058] (21st global; phase 31). [I]: value = broadcast [rdi+0x168]. 24 call-0x5679db0 total.
## Phase 31 — 0x66d207a, 40 instructions [V]
```
66d207a  mov r10,[0x129F9058]                          ; [data_129f9058]
66d2081  xor r9d,r9d                                   
66d2084  nop [rax+rax]                                 
loc_66d2090:  ; from 66d20a5
66d2090  mov r11,[rax+r9]                              
66d2094  cmp [r11+0x28],r10                            
66d2098  je 0x66D216C                                  ; -> loc_66d216c
66d209e  add r9,0x10                                   
66d20a2  cmp rcx,r9                                    
66d20a5  jne short 0x66d2090                           ; -> loc_66d2090
66d20a7  jmp 0x66D21C1                                 ; -> loc_66d21c1
66d20ac  add r8,rax                                    
66d20af  lea r9,[rax+rcx]                              
66d20b3  cmp r8,r9                                     
66d20b6  jae short 0x66D20FC                           ; -> loc_66d20fc
66d20b8  sub r8d,eax                                   
66d20bb  shr r8d,4                                     
66d20bf  mov [rbp+0x4D0],r8w                           
66d20c7  mov byte ptr [rbp+0x4D2],1                    
66d20ce  lea rdx,[rbp+0x4D0]                           
66d20d5  lea r8,[rbp+0x7E0]                            
66d20dc  lea rcx,[rbp+0xCE8]                           
66d20e3  call 0x5679DB0                                ; -> sub_5679db0
66d20e8  nop                                           
66d20e9  mov rax,[rbp+0xD18]                           
66d20f0  movzx edx,word ptr [rbp+0xD22]                
66d20f7  mov ecx,edx                                   
66d20f9  shl ecx,4                                     
loc_66d20fc:  ; from 66d20b6
66d20fc  mov r8,[rbp+0xD70]                            
66d2103  movups xmm0,[r8+0x3E4]                        
66d210b  shufps xmm0,xmm0,0                            
66d210f  movaps [rbp+0xA50],xmm0                       
66d2116  mov qword ptr [rbp+0x7E0],1                   
66d2121  lea r8,[rbp+0xA50]                            
66d2128  mov [rbp+0x7E8],r8                            
66d212f  mov r8,rax                                    
66d2132  test dx,dx                                    
66d2135  je 0x66D2234                                  ; -> loc_66d2234
66d213b  mov r9,[0x129F9058]                           ; [data_129f9058]
66d2142  xor r8d,r8d                                   
66d2145  nop [rax+rax]                                 
loc_66d2150:  ; from 66d2165
66d2150  mov r10,[rax+r8]                              
```
`//` [V] 26th scan (key r10=[0x129F9058], 21st global): r9d=0; loop r11=[rax+r9]; cmp [r11+0x28],r10; je 0x66d216c; r9+=0x10; cmp rcx,r9 jne; no match->jmp 0x66d21c1. 25th scan match-end (0x66d20ac): add r8,rax; lea r9,[rax+rcx]; cmp r8,r9; jae 0x66d20fc; else index=(r8d-eax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (25th call); nop; rax=[rbp+0xD18]; edx=[rbp+0xD22]; ecx=edx<<4 [V]. 0x66d20fc: r8=[rbp+0xD70] (arg1); movups xmm0=[r8+0x3E4]; shufps; [rbp+0xA50]=xmm0; [rbp+0x7E0]=1(qword); [rbp+0x7E8]=&rbp+0xA50; r8=rax; test dx,dx; je 0x66d2234; else r9=[0x129F9058] (same 21st global); r8d=0; loop header 0x66d2150 (phase 32). [I]: value = broadcast [arg1+0x3E4]. 25 call-0x5679db0 total.
## Phase 32 — 0x66d2150, 40 instructions [V]
```
loc_66d2150:  ; from 66d2165
66d2150  mov r10,[rax+r8]                              
66d2154  cmp [r10+0x28],r9                             
66d2158  je 0x66D2231                                  ; -> loc_66d2231
66d215e  add r8,0x10                                   
66d2162  cmp rcx,r8                                    
66d2165  jne short 0x66d2150                           ; -> loc_66d2150
66d2167  jmp 0x66D2281                                 ; -> loc_66d2281
66d216c  add r9,rax                                    
66d216f  lea r10,[rax+rcx]                             
66d2173  cmp r9,r10                                    
66d2176  jae short 0x66d21c1                           ; -> loc_66d21c1
66d2178  sub r9d,eax                                   
66d217b  shr r9d,4                                     
66d217f  mov [rbp+0x4D0],r9w                           
66d2187  mov byte ptr [rbp+0x4D2],1                    
66d218e  lea rdx,[rbp+0x4D0]                           
66d2195  lea r8,[rbp+0x7E0]                            
66d219c  lea rcx,[rbp+0xCE8]                           
66d21a3  call 0x5679DB0                                ; -> sub_5679db0
66d21a8  nop                                           
66d21a9  mov rdx,[rdi]                                 
66d21ac  mov rax,[rbp+0xD18]                           
66d21b3  movzx r8d,word ptr [rbp+0xD22]                
66d21bb  mov ecx,r8d                                   
66d21be  shl ecx,4                                     
loc_66d21c1:  ; from 66d2176
66d21c1  movss xmm0,[rdx+0x16C]                        
66d21c9  shufps xmm0,xmm0,0                            
66d21cd  movaps [rbp+0xA50],xmm0                       
66d21d4  mov qword ptr [rbp+0x7E0],1                   
66d21df  lea r9,[rbp+0xA50]                            
66d21e6  mov [rbp+0x7E8],r9                            
66d21ed  mov r9,rax                                    
66d21f0  test r8w,r8w                                  
66d21f4  je 0x66D22F3                                  ; -> loc_66d22f3
66d21fa  mov r10,[0x129F9068]                          ; [data_129f9068]
66d2201  xor r9d,r9d                                   
66d2204  nop [rax+rax]                                 
loc_66d2210:  ; from 66d2225
66d2210  mov r11,[rax+r9]                              
66d2214  cmp [r11+0x28],r10                            
```
`//` [V] 27th scan loop: r10=[rax+r8]; cmp [r10+0x28],r9; je 0x66d2231; r8+=0x10; cmp rcx,r8 jne; no match->jmp 0x66d2281. 26th scan match-end (0x66d216c): add r9,rax; lea r10,[rax+rcx]; cmp r9,r10; jae 0x66d21c1; else index=(r9d-eax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (26th call); nop; rdx=[rdi]; rax=[rbp+0xD18]; r8d=[rbp+0xD22]; ecx=r8d<<4 [V] (setup). 0x66d21c1 (26th scan not-found): movss xmm0=[rdx+0x16C]; shufps; [rbp+0xA50]=xmm0; [rbp+0x7E0]=1(qword); [rbp+0x7E8]=&rbp+0xA50; r9=rax; test r8w,r8w; je 0x66d22f3; else r10=[0x129F9068] (22nd global); r9d=0; loop header 0x66d2210 (phase 33). [I]: value [rdx+0x16C] broadcast. 26 call-0x5679db0 total.
## Phase 33 — 0x66d2218, 40 instructions [V]
```
66d2218  je 0x66D22F0                                  ; -> loc_66d22f0
66d221e  add r9,0x10                                   
66d2222  cmp rcx,r9                                    
66d2225  jne short 0x66d2210                           ; -> sub_66d2210
66d2227  mov r8w,1                                     
66d222c  jmp 0x66D2345                                 ; -> loc_66d2345
66d2231  add r8,rax                                    
66d2234  lea r9,[rax+rcx]                              
66d2238  cmp r8,r9                                     
66d223b  jae short 0x66D2281                           ; -> loc_66d2281
66d223d  sub r8d,eax                                   
66d2240  shr r8d,4                                     
66d2244  mov [rbp+0x4D0],r8w                           
66d224c  mov byte ptr [rbp+0x4D2],1                    
66d2253  lea rdx,[rbp+0x4D0]                           
66d225a  lea r8,[rbp+0x7E0]                            
66d2261  lea rcx,[rbp+0xCE8]                           
66d2268  call 0x5679DB0                                ; -> sub_5679db0
66d226d  nop                                           
66d226e  mov rax,[rbp+0xD18]                           
66d2275  movzx edx,word ptr [rbp+0xD22]                
66d227c  mov ecx,edx                                   
66d227e  shl ecx,4                                     
loc_66d2281:  ; from 66d223b
66d2281  mov r8,[rbp+0xD70]                            
66d2288  movups xmm0,[r8+0x3E8]                        
66d2290  shufps xmm0,xmm0,0                            
66d2294  movaps [rbp+0xA50],xmm0                       
66d229b  mov qword ptr [rbp+0x7E0],1                   
66d22a6  lea r8,[rbp+0xA50]                            
66d22ad  mov [rbp+0x7E8],r8                            
66d22b4  mov r8,rax                                    
66d22b7  test dx,dx                                    
66d22ba  je 0x66D23EA                                  ; -> loc_66d23ea
66d22c0  mov r9,[0x129F9068]                           ; [data_129f9068]
66d22c7  xor r8d,r8d                                   
66d22ca  nop [rax+rax]                                 
loc_66d22d0:  ; from 66d22e5
66d22d0  mov r10,[rax+r8]                              
66d22d4  cmp [r10+0x28],r9                             
66d22d8  je 0x66D23E7                                  ; -> loc_66d23e7
66d22de  add r8,0x10                                   
66d22e2  cmp rcx,r8                                    
```
`//` [V] 28th scan loop tail: je 0x66d22f0; add r9,0x10; cmp rcx,r9 jne; no match->mov r8w,1; jmp 0x66d2345 (default index=1) [V]. 27th scan match-end (0x66d2231): add r8,rax; lea r9,[rax+rcx]; cmp r8,r9; jae 0x66d2281; else index=(r8d-eax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (27th call); nop; rax=[rbp+0xD18]; edx=[rbp+0xD22]; ecx=edx<<4 [V] (setup). 0x66d2281 (27th scan not-found): r8=[rbp+0xD70] (arg1); movups xmm0=[r8+0x3E8]; shufps; [rbp+0xA50]=xmm0; [rbp+0x7E0]=1(qword); [rbp+0x7E8]=&rbp+0xA50; r8=rax; test dx,dx; je 0x66d23ea; else r9=[0x129F9068] (22nd global, again); r8d=0; loop 0x66d22d0 (phase 34). [I]: value [arg1+0x3E8] broadcast; not-found default index=1 [V]. 27 call-0x5679db0 total.
## Phase 34 — 0x66d22e2, 40 instructions [V]
```
66d22e2  cmp rcx,r8                                    
66d22e5  jne short 0x66D22D0                           ; -> sub_66d22d0
66d22e7  mov dx,1                                      
66d22eb  jmp 0x66D2437                                 ; -> loc_66d2437
66d22f0  add r9,rax                                    
66d22f3  lea r10,[rax+rcx]                             
66d22f7  cmp r9,r10                                    
66d22fa  jae short 0x66d2345                           ; -> loc_66d2345
66d22fc  sub r9d,eax                                   
66d22ff  shr r9d,4                                     
66d2303  mov [rbp+0x4D0],r9w                           
66d230b  mov byte ptr [rbp+0x4D2],1                    
66d2312  lea rdx,[rbp+0x4D0]                           
66d2319  lea r8,[rbp+0x7E0]                            
66d2320  lea rcx,[rbp+0xCE8]                           
66d2327  call 0x5679DB0                                ; -> sub_5679db0
66d232c  nop                                           
66d232d  mov rdx,[rdi]                                 
66d2330  mov rax,[rbp+0xD18]                           
66d2337  movzx r8d,word ptr [rbp+0xD22]                
66d233f  mov ecx,r8d                                   
66d2342  shl ecx,4                                     
loc_66d2345:  ; from 66d22fa
66d2345  movss xmm0,[rdx+0x170]                        
66d234d  shufps xmm0,xmm0,0                            
66d2351  movaps [rbp+0xA50],xmm0                       
66d2358  mov qword ptr [rbp+0x7E0],1                   
66d2363  lea rdx,[rbp+0xA50]                           
66d236a  mov [rbp+0x7E8],rdx                           
66d2371  mov rdx,rax                                   
66d2374  test r8w,r8w                                  
66d2378  je short 0x66d23a8                            ; -> loc_66d23a8
66d237a  mov r8,[0x129F9078]                           ; [data_129f9078]
66d2381  mov r9,rcx                                    
66d2384  mov rdx,rax                                   
66d2387  nop [rax+rax]                                 
loc_66d2390:  ; from 66d23a1
66d2390  mov r10,[rdx]                                 
66d2393  cmp [r10+0x28],r8                             
66d2397  je short 0x66d23a8                            ; -> loc_66d23a8
66d2399  add rdx,0x10                                  
66d239d  add r9,0xFFFFFFFFFFFFFFF0                     
66d23a1  jne short 0x66d2390                           ; -> loc_66d2390
```
`//` [V] 29th scan loop tail: cmp rcx,r8 jne; no match->mov dx,1; jmp 0x66d2437 (default key=1) [V]. Match-end (0x66d22f0): add r9,rax; lea r10,[rax+rcx]; cmp r9,r10; jae 0x66d2345; else index=(r9d-eax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (28th call); nop; rdx=[rdi]; rax=[rbp+0xD18]; r8d=[rbp+0xD22]; ecx=r8d<<4 [V] (setup). 0x66d2345 (match/default): movss xmm0=[rdx+0x170]; shufps; [rbp+0xA50]=xmm0; [rbp+0x7E0]=1(qword); lea rdx,[rbp+0xA50]; [rbp+0x7E8]=rdx; rdx=rax; test r8w,r8w; je 0x66d23a8; else r8=[0x129F9078] (23rd global); r9=rcx; rdx=rax; scan loop 0x66d2390: r10=[rdx]; cmp [r10+0x28],r8; je 0x66d23a8; rdx+=0x10; r9-=0x10 jne [V]. [I]: value [rdi+0x170] broadcast; 28 call-0x5679db0 total.
## NEXT
Resume at RVA 0x66d239d (41st address of phase-34 call = `add r9,0xFFFFFFFFFFFFFFF0`). Run:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d239d 41`
Append first 40 as phase 35; next phase starts at the 41st-instruction address. On any `(bad)` line, restart at the next address after it. Target: first 800 instructions of 0x66d0a00 (size ~0x738b). Append each phase: exact `0xRVA  mnemonic operands` lines then `// interpretation` tagged [V]/[I]/[?]. Keep this NEXT block current.
