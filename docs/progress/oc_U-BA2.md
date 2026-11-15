# Unit U-BA2 — bodyActor function 0x66d0a00 (1.26.62.01), continued from 0x66d23a3

## Context [V]
- Continuation of U-BA1 (docs/progress/oc_U-BA1.md), which covered 0x66d0a00..0x66d23a1 (phases 1–34, ~1360 instructions).
- U-BA1 NEXT block (stale) pointed at 0x66d239d; this unit resumes at 0x66d23a3 per orchestrator.
- Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; game is closed.

## Phase 1 — 0x66d23a3, 40 instructions [V]
```
66d23a3  jmp 0x66D24CE                                 ; -> loc_66d24ce
66d23a8  add rcx,rax                                   
66d23ab  cmp rdx,rcx                                   
66d23ae  jae 0x66D24CE                                 ; -> loc_66d24ce
66d23b4  sub edx,eax                                   
66d23b6  shr edx,4                                     
66d23b9  mov [rbp+0x4D0],dx                            
66d23c0  mov byte ptr [rbp+0x4D2],1                    
66d23c7  lea rdx,[rbp+0x4D0]                           
66d23ce  lea r8,[rbp+0x7E0]                            
66d23d5  lea rcx,[rbp+0xCE8]                           
66d23dc  call 0x5679DB0                                ; -> sub_5679db0
66d23e1  nop                                           
66d23e2  jmp 0x66D24CE                                 ; -> loc_66d24ce
66d23e7  add r8,rax                                    
66d23ea  lea r9,[rax+rcx]                              ; R ret@5679db0+0x0+idx
66d23ee  cmp r8,r9                                     
66d23f1  jae short 0x66D2437                           ; -> loc_66d2437
66d23f3  sub r8d,eax                                   
66d23f6  shr r8d,4                                     
66d23fa  mov [rbp+0x4D0],r8w                           
66d2402  mov byte ptr [rbp+0x4D2],1                    
66d2409  lea rdx,[rbp+0x4D0]                           
66d2410  lea r8,[rbp+0x7E0]                            
66d2417  lea rcx,[rbp+0xCE8]                           
66d241e  call 0x5679DB0                                ; -> sub_5679db0
66d2423  nop                                           
66d2424  mov rax,[rbp+0xD18]                           
66d242b  movzx edx,word ptr [rbp+0xD22]                
66d2432  mov ecx,edx                                   
66d2434  shl ecx,4                                     
66d2437  mov r8,[rbp+0xD70]                            
66d243e  movups xmm0,[r8+0x3EC]                        
66d2446  shufps xmm0,xmm0,0                            
66d244a  movaps [rbp+0xA50],xmm0                       
66d2451  mov qword ptr [rbp+0x7E0],1                   
66d245c  lea r8,[rbp+0xA50]                            
66d2463  mov [rbp+0x7E8],r8                            
66d246a  mov r8,rax                                    
66d246d  test dx,dx                                    
```
`//` [V] Entry at 0x66d23a3 is the 29th table-scan's not-found path (jmp 0x66d24ce) [V, matching U-BA1 phase-34 tail]. Match-end block at 0x66d23a8: add rcx,rax; cmp rdx,rcx; jae 0x66d24ce; else index=(edx-eax)>>4 -> [rbp+0x4D0] (dx); byte [rbp+0x4D2]=1; call 0x5679DB0(rdx=&rbp+0x4D0, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V] (29th call); nop; jmp 0x66d24ce. 30th scan match-end at 0x66d23e7: add r8,rax; lea r9,[rax+rcx]; cmp r8,r9; jae 0x66d2437; else index=(r8d-eax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (30th call); nop; reload rax=[rbp+0xD18], edx=[rbp+0xD22], ecx=edx<<4 [V]. 0x66d2437 (30th scan not-found): r8=[rbp+0xD70] (=arg1); movups xmm0=[r8+0x3EC]; shufps (broadcast lo dword); [rbp+0xA50]=xmm0; [rbp+0x7E0]=1 (qword); [rbp+0x7E8]=&rbp+0xA50; r8=rax; test dx,dx (phase 2) [V]. [I]: value = broadcast [arg1+0x3EC]; 30 call-0x5679db0 total so far.

## Phase 2 — 0x66d2470, 40 instructions [V]
```
66d2470  je short 0x66D2495                            ; -> loc_66d2495
66d2472  mov rdx,[0x129F9078]                          ; [data_129f9078]
66d2479  mov r9,rcx                                    
66d247c  mov r8,rax                                    
66d247f  nop                                           
66d2480  mov r10,[r8]                                  
66d2483  cmp [r10+0x28],rdx                            
66d2487  je short 0x66D2495                            ; -> loc_66d2495
66d2489  add r8,0x10                                   
66d248d  add r9,0xFFFFFFFFFFFFFFF0                     
66d2491  jne short 0x66D2480                           ; -> loc_66d2480
66d2493  jmp short 0x66D24CE                           ; -> loc_66d24ce
66d2495  add rcx,rax                                   
66d2498  cmp r8,rcx                                    
66d249b  jae short 0x66D24CE                           ; -> loc_66d24ce
66d249d  sub r8d,eax                                   
66d24a0  shr r8d,4                                     
66d24a4  mov [rbp+0x4D0],r8w                           
66d24ac  mov byte ptr [rbp+0x4D2],1                    
66d24b3  lea rdx,[rbp+0x4D0]                           
66d24ba  lea r8,[rbp+0x7E0]                            
66d24c1  lea rcx,[rbp+0xCE8]                           
66d24c8  call 0x5679DB0                                ; -> sub_5679db0
66d24cd  nop                                           
66d24ce  mov r8,[rdi]                                  
66d24d1  mov rax,[r8+0x140]                            
66d24d8  mov rax,[rax+0x40]                            
66d24dc  xor ecx,ecx                                   
66d24de  cmp byte ptr [rax+0x1AD],0                    
66d24e5  sete cl                                       
66d24e8  cmp byte ptr [rax+0x1AE],0                    
66d24ef  lea edx,[rcx+4]                               
66d24f2  movzx edx,dl                                  
66d24f5  cmovne edx,ecx                                
66d24f8  lea ecx,[rdx+0x10]                            
66d24fb  cmp byte ptr [rax+0x1AF],0                    
66d2502  movzx r14d,cl                                 
66d2506  cmovne r14d,edx                               
66d250a  movzx eax,byte ptr [rax+0x1AC]                
66d2511  test al,0xFB                                  
```
`//` [V] 31st scan (key rdx=[0x129F9078], 23rd global, same as phase-1 tail): if dx==0 ->0x66d2495; else r9=rcx (end counter), r8=rax; scan loop 0x66d2480: r10=[r8]; cmp [r10+0x28],rdx; je 0x66d2495; r8+=0x10; r9-=0x10 jne; no match ->jmp 0x66d24ce [V]. Match-end 0x66d2495: add rcx,rax; cmp r8,rcx; jae 0x66d24ce; else index=(r8d-eax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(&rbp+0x4D0,&rbp+0x7E0,&rbp+0xCE8) [V] (31st call); nop. Converge 0x66d24ce (table-scan loop done): r8=[rdi]; rax=[r8+0x140]; rax=[rax+0x40] [V] (chain: arg3 -> +0x140 -> +0x40, same as phase 1/2 of U-BA1). Then byte-flag accumulation on r14d: cl=(byte [rax+0x1AD]==0)?1:0 [V]; if [rax+0x1AE]!=0 edx=cl else edx=cl+4 [V]; cl=(byte [rax+0x1AF]!=0)?edx:cl+0x10 [V]; eax=byte [rax+0x1AC]; test al,0xFB (phase 3) [V]. [I]: r14d accumulates a bitfield from bytes [rax+0x1AC..0x1AF] at offset +0x1AD..+0x1AF; the 0x5679db0 table-scan loop series ends here (31 calls total). Table-scan loop series done [V].

## Phase 3 — 0x66d2514, 40 instructions [V] (contains a `(bad)` line; phase restarts after it)
```
66d2514  or eax,[rcx-0x80]                             ; R a0-0x80
66d2517  (bad)                                         
66d2519  mov r13w,0x500                                
66d251e  jmp short 0x66D2523                           ; -> loc_66d2523
66d2520  xor r13d,r13d                                 
66d2523  mov rax,[rbp+0xD28]                           
66d252a  movzx r9d,word ptr [rbp+0xD32]                
66d2532  mov ecx,r9d                                   
66d2535  shl ecx,4                                     
66d2538  lea rdx,[rcx+rcx*2]                            
66d253c  mov rcx,rax                                   
66d253f  test r9,r9                                    
66d2542  je short 0x66D2575                            ; -> loc_66d2575
66d2544  mov r9,[0x129F8318]                           ; [data_129f8318]
66d254b  mov r10,rdx                                   
66d254e  mov rcx,rax                                   
66d2551  nop [rax+rax]                                 
66d2560  mov r11,[rcx]                                 
66d2563  cmp [r11+0x28],r9                             
66d2567  je short 0x66D2575                            ; -> loc_66d2575
66d2569  add rcx,0x30                                  
66d256d  add r10,0xFFFFFFFFFFFFFFD0                    
66d2571  jne short 0x66D2560                           ; -> loc_66d2560
66d2573  jmp short 0x66D25EC                           ; -> loc_66d25ec
66d2575  add rdx,rax                                   
66d2578  cmp rcx,rdx                                   
66d257b  jae short 0x66D25EC                           ; -> loc_66d25ec
66d257d  add r8,0xE0                                   
66d2584  sub ecx,eax                                   
66d2586  shr ecx,4                                     
66d2589  imul eax,ecx,0xFFFFAAAB                       
66d258f  mov [rbp+0x7E0],ax                            
66d2596  mov byte ptr [rbp+0x7E2],1                    
66d259d  movzx eax,r14b                                
66d25a1  movzx ecx,r13w                                
66d25a5  or ecx,eax                                    
66d25a7  mov [rbp+0xA50],cx                            
66d25ae  mov dword ptr [rbp+0xA54],0                   
66d25b8  mov byte ptr [rbp+0xA58],0                    
66d25bf  mov byte ptr [rbp+0xA5C],1                    
```
`//` [V] rdis emitted `(bad)` at 0x66d2517 (3 bytes after the 0x66d2514 `or eax,[rcx-0x80]`); per brief the phase restarts at 0x66d2519. The 0x66d2514 instruction is recorded as rdis printed it [V]; its length/validity is uncertain [?]. From 0x66d2519: r13w=0x500 (jmp over the 0x66d2520 `xor r13d,r13d` alternate) [V]. NEW table-scan series (stride 0x30, not 0x10): base rax=[rbp+0xD28], count r9d=[rbp+0xD32] (word), edx=r9d*3*4 (lea rdx,[rcx+rcx*2] then shl ecx,4 → edx=rcx*3, i.e. byte size = count*0x30) [V]; if count==0 ->0x66d2575; else key r9=[0x129F8318] (24th global); scan loop 0x66d2560: r11=[rcx]; cmp [r11+0x28],r9; je 0x66d2575; rcx+=0x30; r10-=0x30 jne; no match ->jmp 0x66d25ec [V]. Match-end 0x66d2575: add rdx,rax; cmp rcx,rdx; jae 0x66d25ec; else add r8,0xE0; ecx=(rcx-rax)>>4; eax=ecx*0xFFFFAAAB (imul, low 32) [V]; [rbp+0x7E0]=ax (u16); byte [rbp+0x7E2]=1 [V]. Value struct: eax=r14b; ecx=r13w; or ecx,eax; [rbp+0xA50]=cx (2 bytes); [rbp+0xA54]=0 (dword); [rbp+0xA58]=0 (byte); [rbp+0xA5C]=1 (byte) [V]. [I]: index slot now [rbp+0x7E0]/[rbp+0x7E2] (reused from phase-21/22 pair); the imul 0xFFFFAAAB is a div-by-12-style magic but its exact result meaning is unclear [?]; value is a 2-byte OR of r14b (bytefield from phase 2) and r13w (0x500) into a small 0xA50..0xA5C struct.

## Phase 4 — 0x66d2519, 40 instructions [V]
```
66d2519  mov r13w,0x500                                
66d251e  jmp short 0x66D2523                           ; -> loc_66d2523
66d2520  xor r13d,r13d                                 
66d2523  mov rax,[rbp+0xD28]                           
66d252a  movzx r9d,word ptr [rbp+0xD32]                
66d2532  mov ecx,r9d                                   
66d2535  shl ecx,4                                     
66d2538  lea rdx,[rcx+rcx*2]                            
66d253c  mov rcx,rax                                   
66d253f  test r9,r9                                    
66d2542  je short 0x66D2575                            ; -> loc_66d2575
66d2544  mov r9,[0x129F8318]                           ; [data_129f8318]
66d254b  mov r10,rdx                                   
66d254e  mov rcx,rax                                   
66d2551  nop [rax+rax]                                 
66d2560  mov r11,[rcx]                                 
66d2563  cmp [r11+0x28],r9                             
66d2567  je short 0x66D2575                            ; -> loc_66d2575
66d2569  add rcx,0x30                                  
66d256d  add r10,0xFFFFFFFFFFFFFFD0                    
66d2571  jne short 0x66D2560                           ; -> loc_66d2560
66d2573  jmp short 0x66D25EC                           ; -> loc_66d25ec
66d2575  add rdx,rax                                   
66d2578  cmp rcx,rdx                                   
66d257b  jae short 0x66D25EC                           ; -> loc_66d25ec
66d257d  add r8,0xE0                                   
66d2584  sub ecx,eax                                   
66d2586  shr ecx,4                                     
66d2589  imul eax,ecx,0xFFFFAAAB                       
66d258f  mov [rbp+0x7E0],ax                            
66d2596  mov byte ptr [rbp+0x7E2],1                    
66d259d  movzx eax,r14b                                
66d25a1  movzx ecx,r13w                                
66d25a5  or ecx,eax                                    
66d25a7  mov [rbp+0xA50],cx                            
66d25ae  mov dword ptr [rbp+0xA54],0                   
66d25b8  mov byte ptr [rbp+0xA58],0                    
66d25bf  mov byte ptr [rbp+0xA5C],1                    
66d25c6  mov dword ptr [rsp+0x20],0                    
66d25ce  lea rcx,[rbp+0xCE0]                           
```
`//` [V] Same 0x30-stride table scan as phase 3 (base [rbp+0xD28], count u16 [rbp+0xD32], key [0x129F8318], match-end stores index at [rbp+0x7E0]/flag [rbp+0x7E2]) [V]. Value struct build: [rbp+0xA50]=cx=(r13w|r14b) (2 bytes), [rbp+0xA54]=0 (dword), [rbp+0xA58]=0 (byte), [rbp+0xA5C]=1 (byte) [V]. New: [rsp+0x20]=0 (dword, stack arg slot for the pending call) [V]; rcx=&rbp+0xCE0 (call setup, phase 5) [V]. [I]: r13w=0x500 default ORed with r14b bytefield; the 0xA50..0xA5C struct is an 8-byte value struct (2+4+1+1) with trailing flag=1.

## Phase 5 — 0x66d25d5, 40 instructions [V]
```
66d25d5  lea rdx,[rbp+0x7E0]                           
66d25dc  lea r9,[rbp+0xA50]                            
66d25e3  call 0xBCABA00                                ; -> sub_bcaba00
66d25e8  nop                                           
66d25e9  mov r8,[rdi]                                  
66d25ec  movzx r12d,word ptr [0x128C1A5E]              ; [data_128c1a5e]
66d25f4  mov r15,[r8+0xF0]                             
66d25fb  xor ebx,ebx                                   
66d25fd  mov eax,[0x128767C8]                          ; [data_128767c8]
66d2603  mov rcx,gs:[0x58]                             
66d260c  mov rax,[rcx+rax*8]                           
66d2610  mov eax,[rax+4]                               
66d2616  test r15,r15                                  
66d2619  je 0x66D275F                                  ; -> loc_66d275f
66d261f  cmp [0x129C13C0],eax                          ; [data_129c13c0]
66d2625  jg 0x66D65DC                                  ; -> sub_66d65dc
66d262b  lock inc word ptr [r15+0x10]                  
66d2631  movzx ecx,byte ptr [r15+0x12]                 
66d2636  and cl,[rbp+0xD80]                            
66d263c  mov r8,[rdi]                                  
66d263f  mov eax,[0x128767C8]                          ; [data_128767c8]
66d2645  mov rdx,gs:[0x58]                             
66d264e  mov rax,[rdx+rax*8]                           
66d2652  mov eax,[rax+4]                               
66d2658  cmp cl,1                                      
66d265b  jne 0x66D275F                                 ; -> loc_66d275f
66d2661  xor ebx,ebx                                   
66d2663  cmp byte ptr [r8+0x100],1                     
66d266b  sete r15b                                     
66d266f  cmp [0x129F9090],eax                          ; [data_129f9090]
66d2675  jg 0x66D69E3                                  ; -> sub_66d69e3
66d267b  mov r8,[rdi]                                  
66d267e  mov rax,[rbp+0xD28]                           
66d2685  movzx r9d,word ptr [rbp+0xD32]                
66d268d  mov ecx,r9d                                   
66d2690  shl ecx,4                                     
66d2693  lea rdx,[rcx+rcx*2]                            
66d2697  mov rcx,rax                                   
66d269a  test r9,r9                                    
66d269d  je short 0x66D26C5                            ; -> loc_66d26c5
```
`//` [V] Call 0xBCABA00(rdx=&rbp+0x7E0 [index+flag], r9=&rbp+0xA50 [value struct], rcx=&rbp+0xCE0 [out]) [V] — 32nd call to this callee family; consumes the phase-4 value struct. Then r8=[rdi]; r12d=[0x128C1A5E] (word global) [V]; r15=[r8+0xF0] [V]; ebx=0; TLS: eax=[0x128767C8]; rcx=gs:[0x58]; rax=[rcx+rax*8]; eax=[rax+4] [V]; test r15,r15 je 0x66d275f; cmp [0x129C13C0],eax jg 0x66d65dc [V] (TLS/version gate, same gs:[0x58] pattern). lock inc word [r15+0x10] (16-bit refcount) [V]; ecx=byte [r15+0x12]; and cl,[rbp+0xD80] [V]; r8=[rdi]; TLS eax=[rax+4] again; cmp cl,1 jne 0x66d275f [V]; xor ebx,ebx; cmp byte [r8+0x100],1; sete r15b [V]; cmp [0x129F9090],eax jg 0x66d69e3 [V]; r8=[rdi]; rax=[rbp+0xD28]; r9d=[rbp+0xD32] (word); ecx=r9d; shl ecx,4; lea rdx,[rcx+rcx*2] (byte size = count*0x30); rcx=rax; test r9,r9; je 0x66d26c5 (phase 6) [V]. [I]: r15=[rdi+0xF0] is a shared_ptr-like payload (word refcount at +0x10); [rbp+0xD80] is a byte mask from phase 2; second 0x30-stride table scan starting (base [rbp+0xD28], count [rbp+0xD32]).

## Phase 6 — 0x66d269f, 40 instructions [V]
```
66d269f  mov r9,[0x129F9088]                           ; [data_129f9088]
66d26a6  mov r10,rdx                                   
66d26a9  mov rcx,rax                                   
66d26ac  nop [rax]                                     
66d26b0  mov r11,[rcx]                                 
66d26b3  cmp [r11+0x28],r9                             
66d26b7  je short 0x66D26C5                            ; -> loc_66d26c5
66d26b9  add rcx,0x30                                  
66d26bd  add r10,0xFFFFFFFFFFFFFFD0                    
66d26c1  jne short 0x66D26B0                           ; -> loc_66d26b0
66d26c3  jmp short 0x66D273C                           ; -> loc_66d273c
66d26c5  add rdx,rax                                   
66d26c8  cmp rcx,rdx                                   
66d26cb  jae short 0x66D273C                           ; -> loc_66d273c
66d26cd  add r8,0xF0                                   
66d26d4  sub ecx,eax                                   
66d26d6  shr ecx,4                                     
66d26d9  imul eax,ecx,0xFFFFAAAB                       
66d26df  mov [rbp+0x7E0],ax                            
66d26e6  mov byte ptr [rbp+0x7E2],1                    
66d26ed  movzx eax,r14b                                
66d26f1  movzx ecx,r13w                                
66d26f5  or ecx,eax                                    
66d26f7  mov [rbp+0xA50],cx                            
66d26fe  mov dword ptr [rbp+0xA54],0                   
66d2708  mov byte ptr [rbp+0xA58],0                    
66d270f  mov byte ptr [rbp+0xA5C],1                    
66d2716  mov dword ptr [rsp+0x20],0                    
66d271e  lea rcx,[rbp+0xCE0]                           
66d2725  lea rdx,[rbp+0x7E0]                           
66d272c  lea r9,[rbp+0xA50]                            
66d2733  call 0xBCABA00                                ; -> sub_bcaba00
66d2738  nop                                           
66d2739  mov r8,[rdi]                                  

loc_66d273c:  ; from 66d26c3, 66d26cb
66d273c  mov bl,r15b                                   
66d273f  lea ebx,[rbx*2+1]                             
66d2746  mov eax,[0x128767C8]                          ; [data_128767c8]
66d274c  mov rcx,gs:[0x58]                             
66d2755  mov rax,[rcx+rax*8]                           
66d2759  mov eax,[rax+4]                               
```
`//` [V] Second 0x30-stride scan (key r9=[0x129F9088], 25th global): loop 0x66d26b0: r11=[rcx]; cmp [r11+0x28],r9; je 0x66d26c5; rcx+=0x30; r10-=0x30 jne; no match ->jmp 0x66d273c [V]. Match-end 0x66d26c5: add rdx,rax; cmp rcx,rdx; jae 0x66d273c; else add r8,0xF0; ecx=(rcx-rax)>>4; eax=ecx*0xFFFFAAAB; [rbp+0x7E0]=ax; byte [rbp+0x7E2]=1 [V]; value struct identical to phase 4 (cx=r13w|r14b, [rbp+0xA54]=0, [rbp+0xA58]=0, [rbp+0xA5C]=1) [V]; [rsp+0x20]=0; call 0xBCABA00(rdx=&rbp+0x7E0, r9=&rbp+0xA50, rcx=&rbp+0xCE0) [V] (33rd call); nop; r8=[rdi] [V]. Converge 0x66d273c: bl=r15b; ebx=ebx*2+1 (fold flag into ebx) [V]; TLS eax=[rax+4] again (phase 7) [V]. [I]: second value struct attached via 0xBCABA00; r8 offset now +0xF0 vs +0xE0 in phase 4; ebx accumulates 2*r15b+1.

## Phase 7 — 0x66d275e, 40 instructions [V]
```
66d275e  add [rbp-0x75],cl                             
66d2761  mov eax,0x108                                 
66d2766  test r15,r15                                  
66d2769  je 0x66D28BE                                  ; -> loc_66d28be
66d276f  cmp [0x129C13C0],eax                          ; [data_129c13c0]
66d2775  jg 0x66D6612                                  ; -> sub_66d6612
66d277b  lock inc word ptr [r15+0x10]                  
66d2781  movzx eax,byte ptr [r15+0x12]                 
66d2786  mov edx,[rbp+0xD80]                           
66d278c  and dl,al                                      
66d278e  mov eax,[0x128767C8]                          ; [data_128767c8]
66d2794  mov rcx,gs:[0x58]                             
66d279d  mov rax,[rcx+rax*8]                           
66d27a1  mov eax,[rax+4]                               
66d27a7  cmp dl,1                                      
66d27aa  jne 0x66D28BE                                 ; -> loc_66d28be
66d27b0  mov rcx,[rdi]                                 
66d27b3  movzx ecx,byte ptr [rcx+0x118]                
66d27ba  xor edx,edx                                   
66d27bc  cmp cl,2                                      
66d27bf  sete dl                                       
66d27c2  lea edx,[rdx*8+8]                             
66d27c9  test cl,cl                                    
66d27cb  mov r15d,4                                    
66d27d1  cmovne r15d,edx                               
66d27d5  cmp [0x129F90A0],eax                          ; [data_129f90a0]
66d27db  jg 0x66D6A60                                  ; -> sub_66d6a60
66d27e1  mov r8d,0x108                                 
66d27e7  add r8,[rdi]                                  
66d27ea  mov rax,[rbp+0xD28]                           
66d27f1  movzx r9d,word ptr [rbp+0xD32]                
66d27f9  mov ecx,r9d                                   
66d27fc  shl ecx,4                                     
66d27ff  lea rdx,[rcx+rcx*2]                            
66d2803  mov rcx,rax                                   
66d2806  test r9,r9                                    
66d2809  je short 0x66D2835                            ; -> loc_66d2835
66d280b  mov r9,[0x129F9098]                           ; [data_129f9098]
66d2812  mov r10,rdx                                   
66d2815  mov rcx,rax                                   
```
`//` [V] Odd first line: `add [rbp-0x75],cl` (3 bytes) writes cl into [rsp+0xB] scratch [V]; possibly a data/misaligned byte — flagged [?]. Then block mirrors phase 5: eax=0x108; test r15,r15 je 0x66d28be; cmp [0x129C13C0],eax jg 0x66d6612 [V]; lock inc word [r15+0x10] (16-bit refcount on [rdi+0xF0] payload) [V]; eax=byte [r15+0x12]; edx=[rbp+0xD80]; and dl,al [V]; TLS eax=[rax+4]; cmp dl,1 jne 0x66d28be [V]; rcx=[rdi]; ecx=byte [rcx+0x118]; edx=(cl==2)?8:0 via sete+lea [rdx*8+8]; r15d=4; cmovne r15d,edx (r15d = cl!=0 ? (cl==2?8:0) : 4) [V]; cmp [0x129F90A0],eax jg 0x66d6a60 [V]; r8d=0x108; r8+=rdi (r8=rdi+0x108) [V]; third 0x30-stride scan setup: rax=[rbp+0xD28], r9d=[rbp+0xD32], ecx=r9d<<4, rdx=rcx*3, rcx=rax; test r9,r9 je 0x66d2835; else key r9=[0x129F9098] (26th global); r10=rdx; rcx=rax (phase 8) [V]. [I]: r15 reused as a selector (4 or 0/8) from byte [rdi+0x118]; r8=rdi+0x108 is a new pointer base for the value struct in the next scan.

## Phase 8 — 0x66d2818, 40 instructions [V]
```
66d2818  nop [rax+rax]                                 
66d2820  mov r11,[rcx]                                 
66d2823  cmp [r11+0x28],r9                             
66d2827  je short 0x66D2835                            ; -> loc_66d2835
66d2829  add rcx,0x30                                  
66d282d  add r10,0xFFFFFFFFFFFFFFD0                    
66d2831  jne short 0x66D2820                           ; -> loc_66d2820
66d2833  jmp short 0x66D28A2                           ; -> loc_66d28a2
66d2835  add rdx,rax                                   
66d2838  cmp rcx,rdx                                   
66d283b  jae short 0x66D28A2                           ; -> loc_66d28a2
66d283d  sub ecx,eax                                   
66d283f  shr ecx,4                                     
66d2842  imul eax,ecx,0xFFFFAAAB                       
66d2848  mov [rbp+0x7E0],ax                            
66d284f  mov byte ptr [rbp+0x7E2],1                    
66d2856  movzx eax,r14b                                
66d285a  movzx ecx,r13w                                
66d285e  or ecx,eax                                    
66d2860  mov [rbp+0xA50],cx                            
66d2867  mov dword ptr [rbp+0xA54],0                   
66d2871  mov byte ptr [rbp+0xA58],0                    
66d2878  mov byte ptr [rbp+0xA5C],1                    
66d287f  mov dword ptr [rsp+0x20],0                    
66d2887  lea rcx,[rbp+0xCE0]                           
66d288e  lea rdx,[rbp+0x7E0]                           
66d2895  lea r9,[rbp+0xA50]                            
66d289c  call 0xBCABA00                                ; -> sub_bcaba00
66d28a1  nop                                           
66d28a2  or ebx,r15d                                   
66d28a5  mov eax,[0x128767C8]                          ; [data_128767c8]
66d28ab  mov rcx,gs:[0x58]                             
66d28b4  mov rax,[rcx+rax*8]                           
66d28b8  mov eax,[rax+4]                               
66d28be  cmp [0x129F90B0],eax                          ; [data_129f90b0]
66d28c4  jg 0x66D6414                                  ; -> sub_66d6414
66d28ca  xorps xmm0,xmm0                               
66d28cd  cvtsi2ss xmm0,ebx                             
66d28d1  shufps xmm0,xmm0,0                            
66d28d5  movaps [rbp+0xA50],xmm0                       
```
`//` [V] Third 0x30-stride scan (key r9=[0x129F9098], 26th global): loop 0x66d2820: r11=[rcx]; cmp [r11+0x28],r9; je 0x66d2835; rcx+=0x30; r10-=0x30 jne; no match ->jmp 0x66d28a2 [V]. Match-end 0x66d2835: add rdx,rax; cmp rcx,rdx; jae 0x66d28a2; else ecx=(rcx-rax)>>4; eax=ecx*0xFFFFAAAB; [rbp+0x7E0]=ax; byte [rbp+0x7E2]=1 [V]; value struct again (cx=r13w|r14b, [rbp+0xA54]=0, [rbp+0xA58]=0, [rbp+0xA5C]=1) [V]; [rsp+0x20]=0; call 0xBCABA00(rdx=&rbp+0x7E0, r9=&rbp+0xA50, rcx=&rbp+0xCE0) [V] (34th call); nop. Converge 0x66d28a2: or ebx,r15d (fold r15d selector into ebx) [V]; TLS eax=[rax+4]; cmp [0x129F90B0],eax jg 0x66d6414 [V]; xorps xmm0; cvtsi2ss xmm0,ebx (float from ebx) [V]; shufps (broadcast); [rbp+0xA50]=xmm0 (16 bytes) [V]. [I]: ebx accumulates r15d selectors (2*r15b+1, then or r15d); first float value built by cvtsi2ss(ebx) — likely a count/index cast to float.

## Phase 9 — 0x66d28da, 40 instructions [V]
```
66d28da  add [rax],al                                  
66d28dc  mov qword ptr [rbp+0x7E0],1                   
66d28e7  lea rax,[rbp+0xA50]                           
66d28ee  mov [rbp+0x7E8],rax                           
66d28f5  mov rax,[rbp+0xD18]                           
66d28fc  movzx r8d,word ptr [rbp+0xD22]                
66d2904  mov edx,r8d                                   
66d2907  shl edx,4                                     
66d290a  mov rcx,rax                                   
66d290d  test r8d,r8d                                  
66d2910  je short 0x66D2935                            ; -> loc_66d2935
66d2912  mov r8,[0x129F90A8]                           ; [data_129f90a8]
66d2919  mov r9,rdx                                    
66d291c  mov rcx,rax                                   
66d291f  nop                                           
66d2920  mov r10,[rcx]                                 
66d2923  cmp [r10+0x28],r8                             
66d2927  je short 0x66D2935                            ; -> loc_66d2935
66d2929  add rcx,0x10                                  
66d292d  add r9,0xFFFFFFFFFFFFFFF0                     
66d2931  jne short 0x66D2920                           ; -> loc_66d2920
66d2933  jmp short 0x66D296B                           ; -> loc_66d296b
66d2935  add rdx,rax                                   
66d2938  cmp rcx,rdx                                   
66d293b  jae short 0x66D296B                           ; -> loc_66d296b
66d293d  sub ecx,eax                                   
66d293f  shr ecx,4                                     
66d2942  mov [rbp+0x4D0],cx                            
66d2949  mov byte ptr [rbp+0x4D2],1                    
66d2950  lea rdx,[rbp+0x4D0]                           
66d2957  lea r8,[rbp+0x7E0]                            
66d295e  lea rcx,[rbp+0xCE8]                           
66d2965  call 0x5679DB0                                ; -> sub_5679db0
66d296a  nop                                           
66d296b  mov eax,[0x128767C8]                          ; [data_128767c8]
66d2971  mov rcx,gs:[0x58]                             
66d297a  mov rax,[rcx+rax*8]                           
66d297e  mov eax,[rax+4]                               
66d2984  mov rbx,[rbp+0xD90]                           
66d298b  test ebx,0x30480                              
```
`//` [V] Odd first line `add [rax],al` (3 bytes) at 0x66d28da — a data/misaligned byte, flagged [?] (rdis resumed disassembly 3 bytes into a previous instruction). Then back to the 0x10-stride table-scan pattern: mov qword ptr [rbp+0x7E0]=1 (clobbers index+flag pair) [V]; [rbp+0x7E8]=&rbp+0xA50 [V]; rax=[rbp+0xD18]; r8d=[rbp+0xD22] (count); edx=r8d<<4; rcx=rax; if r8d==0 ->0x66d2935; else r8=[0x129F90A8] (27th global); scan loop 0x66d2920: r10=[rcx]; cmp [r10+0x28],r8; je 0x66d2935; rcx+=0x10; r9-=0x10 jne; no match ->jmp 0x66d296b [V]. Match-end 0x66d2935: add rdx,rax; cmp rcx,rdx; jae 0x66d296b; else index=(ecx-rax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(rdx=&rbp+0x4D0, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V] (35th call); nop. Converge 0x66d296b: TLS eax=[rax+4]; rbx=[rbp+0xD90]; test ebx,0x30480 (phase 10) [V]. [I]: value is the float broadcast at [rbp+0xA50] from phase 8 (cvtsi2ss(ebx)); 35 call-0x5679db0 total; flag mask 0x30480 on ebx=[rbp+0xD90].

## Phase 10 — 0x66d2991, 40 instructions [V]
```
66d2991  je 0x66D2A9A                                  ; -> loc_66d2a9a
66d2997  cmp [0x129F90C0],eax                          ; [data_129f90c0]
66d299d  jg 0x66D6648                                  ; -> sub_66d6648
66d29a3  mov r8d,0x120                                 
66d29a9  add r8,[rdi]                                  
66d29ac  mov rax,[rbp+0xD28]                           
66d29b3  movzx r9d,word ptr [rbp+0xD32]                
66d29bb  mov ecx,r9d                                   
66d29be  shl ecx,4                                     
66d29c1  lea rdx,[rcx+rcx*2]                            
66d29c5  mov rcx,rax                                   
66d29c8  test r9,r9                                    
66d29cb  mov r14,[rbp+0xE20]                           
66d29d2  je short 0x66D2A05                            ; -> loc_66d2a05
66d29d4  mov r9,[0x129F90B8]                           ; [data_129f90b8]
66d29db  mov r10,rdx                                   
66d29de  mov rcx,rax                                   
66d29e1  nop [rax+rax]                                 
66d29f0  mov r11,[rcx]                                 
66d29f3  cmp [r11+0x28],r9                             
66d29f7  je short 0x66D2A05                            ; -> loc_66d2a05
66d29f9  add rcx,0x30                                  
66d29fd  add r10,0xFFFFFFFFFFFFFFD0                    
66d2a01  jne short 0x66D29F0                           ; -> loc_66d29f0
66d2a03  jmp short 0x66D2A77                           ; -> loc_66d2a77
66d2a05  add rdx,rax                                   
66d2a08  cmp rcx,rdx                                   
66d2a0b  jae short 0x66D2A77                           ; -> loc_66d2a77
66d2a0d  sub ecx,eax                                   
66d2a0f  shr ecx,4                                     
66d2a12  imul eax,ecx,0xFFFFAAAB                       
66d2a18  mov [rbp+0x7E0],ax                            
66d2a1f  mov byte ptr [rbp+0x7E2],1                    
66d2a26  mov [rbp+0xA50],r12w                          
66d2a2e  mov dword ptr [rbp+0xA54],0                   
66d2a38  mov byte ptr [rbp+0xA58],1                    
66d2a3f  mov byte ptr [rbp+0xA5C],1                    
66d2a46  mov dword ptr [rsp+0x20],0                    
66d2a4e  lea rcx,[rbp+0xCE0]                           
```
`//` [V] Flag test result (phase 9): je 0x66d2a9a if zero (skip); cmp [0x129F90C0],eax jg 0x66d6648 [V]; r8d=0x120; r8+=rdi (r8=rdi+0x120) [V]; fourth 0x30-stride scan setup: rax=[rbp+0xD28], r9d=[rbp+0xD32], ecx=r9d<<4, rdx=rcx*3, rcx=rax; r14=[rbp+0xE20] (r15) [V]; if r9==0 ->0x66d2a05; else key r9=[0x129F90B8] (28th global); scan loop 0x66d29f0: r11=[rcx]; cmp [r11+0x28],r9; je 0x66d2a05; rcx+=0x30; r10-=0x30 jne; no match ->jmp 0x66d2a77 [V]. Match-end 0x66d2a05: add rdx,rax; cmp rcx,rdx; jae 0x66d2a77; else ecx=(rcx-rax)>>4; eax=ecx*0xFFFFAAAB; [rbp+0x7E0]=ax; byte [rbp+0x7E2]=1 [V]; NEW value struct: [rbp+0xA50]=r12w (2 bytes, u16 from phase 2's r12d) [V]; [rbp+0xA54]=0 (dword); [rbp+0xA58]=1 (byte); [rbp+0xA5C]=1 (byte) [V]; [rsp+0x20]=0; rcx=&rbp+0xCE0 (phase 11) [V]. [I]: value is now r12w (a u16 index) with flags 0/1/1; r8=rdi+0x120 is another pointer base. Note: rdis printed `add eax,[rax]` at 0x66d298f (3 bytes) which is a misaligned re-disassembly of the `test ebx,0x30480` tail; the real next instruction is 0x66d2991 `je 0x66D2A9A` [V].

## Phase 11 — 0x66d2a55, 39 instructions [V]
```
66d2a55  lea rdx,[rbp+0x7E0]                           
66d2a5c  lea r9,[rbp+0xA50]                            
66d2a63  call 0xBCABA00                                ; -> sub_bcaba00
66d2a68  nop                                           
66d2a69  mov rbx,[rbp+0xD90]                           
66d2a70  mov r14,[rbp+0xE20]                           
66d2a77  mov eax,[0x128767C8]                          ; [data_128767c8]
66d2a7d  mov rcx,gs:[0x58]                             
66d2a86  mov rax,[rcx+rax*8]                           
66d2a8a  mov eax,[rax+4]                               
66d2a90  test ebx,0x10000                              
66d2a96  je short 0x66D2AA9                            ; -> loc_66d2aa9
66d2a98  jmp short 0x66D2AB7                           ; -> loc_66d2ab7
66d2a9a  mov r14,[rbp+0xE20]                           
66d2aa1  test ebx,0x10000                              
66d2aa7  jne short 0x66D2AB7                           ; -> loc_66d2ab7
66d2aa9  cmp byte ptr [r14+0x118],0                    
66d2ab1  je 0x66D2B92                                  ; -> loc_66d2b92
66d2ab7  cmp [0x129F90D0],eax                          ; [data_129f90d0]
66d2abd  jg 0x66D68FF                                  ; -> sub_66d68ff
66d2ac3  mov r8d,0x130                                 
66d2ac9  add r8,[rdi]                                  
66d2acc  mov rax,[rbp+0xD28]                           
66d2ad3  movzx r9d,word ptr [rbp+0xD32]                
66d2adb  mov ecx,r9d                                   
66d2ade  shl ecx,4                                     
66d2ae1  lea rdx,[rcx+rcx*2]                            
66d2ae5  mov rcx,rax                                   
66d2ae8  test r9,r9                                    
66d2aeb  je short 0x66D2B15                            ; -> loc_66d2b15
66d2aed  mov r9,[0x129F90C8]                           ; [data_129f90c8]
66d2af4  mov r10,rdx                                   
66d2af7  mov rcx,rax                                   
66d2afa  nop [rax+rax]                                 
66d2b00  mov r11,[rcx]                                 
66d2b03  cmp [r11+0x28],r9                             
66d2b07  je short 0x66D2B15                            ; -> loc_66d2b15
66d2b09  add rcx,0x30                                  
66d2b0d  add r10,0xFFFFFFFFFFFFFFD0                    
66d2b11  jne short 0x66D2B00                           ; -> loc_66d2b00
```
`//` [V] Call 0xBCABA00(rdx=&rbp+0x7E0, r9=&rbp+0xA50, rcx=&rbp+0xCE0) consuming the phase-10 value struct (r12w + flags 0/1/1) [V] (36th call). rbx=[rbp+0xD90]; r14=[rbp+0xE20] (r15) [V]; TLS eax=[rax+4]; test ebx,0x10000: if set ->jmp 0x66d2ab7; else ->0x66d2aa9: r14=[rbp+0xE20]; test ebx,0x10000 again; jne 0x66d2ab7; else cmp byte [r14+0x118],0 je 0x66d2b92 [V] (branch on r15+0x118 byte). Converge 0x66d2ab7: cmp [0x129F90D0],eax jg 0x66d68ff [V]; r8d=0x130; r8+=rdi (r8=rdi+0x130) [V]; fifth 0x30-stride scan setup: rax=[rbp+0xD28], r9d=[rbp+0xD32], ecx=r9d<<4, rdx=rcx*3, rcx=rax; if r9==0 ->0x66d2b15; else key r9=[0x129F90C8] (29th global); scan loop 0x66d2b00: r11=[rcx]; cmp [r11+0x28],r9; je 0x66d2b15; rcx+=0x30; r10-=0x30 jne (phase 12) [V]. [I]: flag bit 0x10000 on ebx=[rbp+0xD90] gates a branch on byte [r15+0x118]; r8=rdi+0x130 next pointer base.

## Phase 12 — 0x66d2b13, 40 instructions [V]
```
66d2b13  jmp short 0x66D2B79                           ; -> loc_66d2b79
66d2b15  add rdx,rax                                   
66d2b18  cmp rcx,rdx                                   
66d2b1b  jae short 0x66D2B79                           ; -> loc_66d2b79
66d2b1d  sub ecx,eax                                   
66d2b1f  shr ecx,4                                     
66d2b22  imul eax,ecx,0xFFFFAAAB                       
66d2b28  mov [rbp+0x7E0],ax                            
66d2b2f  mov byte ptr [rbp+0x7E2],1                    
66d2b36  mov [rbp+0xA50],r12w                          
66d2b3e  mov dword ptr [rbp+0xA54],0                   
66d2b48  mov byte ptr [rbp+0xA58],1                    
66d2b4f  mov byte ptr [rbp+0xA5C],1                    
66d2b56  mov dword ptr [rsp+0x20],0                    
66d2b5e  lea rcx,[rbp+0xCE0]                           
66d2b65  lea rdx,[rbp+0x7E0]                           
66d2b6c  lea r9,[rbp+0xA50]                            
66d2b73  call 0xBCABA00                                ; -> sub_bcaba00
66d2b78  nop                                           
66d2b79  mov eax,[0x128767C8]                          ; [data_128767c8]
66d2b7f  mov rcx,gs:[0x58]                             
66d2b88  mov rax,[rcx+rax*8]                           
66d2b8c  mov eax,[rax+4]                               
66d2b92  cmp [0x129F90E0],eax                          ; [data_129f90e0]
66d2b98  jg 0x66D6486                                  ; -> sub_66d6486
66d2b9e  movups xmm0,[0x12ADFC94]                      ; [data_12adfc94]
66d2ba5  shufps xmm0,xmm0,0                            
66d2ba9  movaps [rbp+0xA50],xmm0                       
66d2bb0  mov qword ptr [rbp+0x7E0],1                   
66d2bbb  lea rax,[rbp+0xA50]                           
66d2bc2  mov [rbp+0x7E8],rax                           
66d2bc9  mov rax,[rbp+0xD18]                           
66d2bd0  movzx r8d,word ptr [rbp+0xD22]                
66d2bd8  mov edx,r8d                                   
66d2bdb  shl edx,4                                     
66d2bde  mov rcx,rax                                   
66d2be1  test r8d,r8d                                  
66d2be4  je short 0x66D2C15                            ; -> loc_66d2c15
66d2be6  mov r8,[0x129F90D8]                           ; [data_129f90d8]
66d2bed  mov r9,rdx                                    
```
`//` [V] Fifth 0x30-stride scan match-end (0x66d2b15): add rdx,rax; cmp rcx,rdx; jae 0x66d2b79; else ecx=(rcx-rax)>>4; eax=ecx*0xFFFFAAAB; [rbp+0x7E0]=ax; byte [rbp+0x7E2]=1 [V]; value struct [rbp+0xA50]=r12w, [rbp+0xA54]=0, [rbp+0xA58]=1, [rbp+0xA5C]=1 [V]; [rsp+0x20]=0; call 0xBCABA00(rdx=&rbp+0x7E0, r9=&rbp+0xA50, rcx=&rbp+0xCE0) [V] (37th call); nop. Converge 0x66d2b79: TLS eax=[rax+4]; cmp [0x129F90E0],eax jg 0x66d6486 [V]; movups xmm0=[0x12ADFC94] (16-byte .rodata const) [V]; shufps (broadcast lo dword); [rbp+0xA50]=xmm0; [rbp+0x7E0]=1 (qword); [rbp+0x7E8]=&rbp+0xA50 [V]; rax=[rbp+0xD18]; r8d=[rbp+0xD22]; edx=r8d<<4; rcx=rax; if r8d==0 ->0x66d2c15; else r8=[0x129F90D8] (30th global); r9=rdx (phase 13) [V]. [I]: value is a .rodata constant broadcast; 37 call-0xBCABA00 total.

## Phase 13 — 0x66d2bf0, 40 instructions [V]
```
66d2bf0  mov rcx,rax                                   
66d2bf3  nop [rax+rax]                                 
66d2c00  mov r10,[rcx]                                 
66d2c03  cmp [r10+0x28],r8                             
66d2c07  je short 0x66D2C15                            ; -> loc_66d2c15
66d2c09  add rcx,0x10                                  
66d2c0d  add r9,0xFFFFFFFFFFFFFFF0                     
66d2c11  jne short 0x66D2C00                           ; -> loc_66d2c00
66d2c13  jmp short 0x66D2C4B                           ; -> loc_66d2c4b
66d2c15  add rdx,rax                                   
66d2c18  cmp rcx,rdx                                   
66d2c1b  jae short 0x66D2C4B                           ; -> loc_66d2c4b
66d2c1d  sub ecx,eax                                   
66d2c1f  shr ecx,4                                     
66d2c22  mov [rbp+0x4D0],cx                            
66d2c29  mov byte ptr [rbp+0x4D2],1                    
66d2c30  lea rdx,[rbp+0x4D0]                           
66d2c37  lea r8,[rbp+0x7E0]                            
66d2c3e  lea rcx,[rbp+0xCE8]                           
66d2c45  call 0x5679DB0                                ; -> sub_5679DB0
66d2c4a  nop                                           
66d2c4b  cmp byte ptr [rdi+0x100],1                    
66d2c52  jne 0x66D2DD2                                 ; -> loc_66d2dd2
66d2c58  lea rdx,[rdi+0xB8]                            
66d2c5f  movzx eax,byte ptr [rdi+0xF8]                 
66d2c66  test eax,eax                                  
66d2c68  je short 0x66D2C85                            ; -> loc_66d2c85
66d2c6a  cmp eax,1                                     
66d2c6d  jne 0x66D6C33                                 ; -> sub_66d6c33
66d2c73  mov rdx,[rdx]                                 
66d2c76  lea rcx,[rbp+0xA50]                           
66d2c7d  call 0x67747B0                                ; -> sub_67747b0
66d2c82  nop                                           
66d2c83  jmp short 0x66D2C92                           ; -> loc_66d2c92
66d2c85  lea rcx,[rbp+0xA50]                           
66d2c8c  call 0x67747B0                                ; -> sub_67747b0
66d2c91  nop                                           
66d2c92  mov r13,[rbp+0xA58]                           
66d2c99  mov r12,[r13]                                 
66d2c9d  cmp r12,r13                                   
```
`//` [V] Sixth (last of this series) 0x30-stride scan (key r8=[0x129F90D8], 30th global, stride 0x30 → actually rdis shows add rcx,0x10 here; loop uses stride 0x10 at 0x66d2c09; hmm phase-12 key block said 0x30 but this loop adds rcx,0x10 — recorded as printed [V]) : loop 0x66d2c00: r10=[rcx]; cmp [r10+0x28],r8; je 0x66d2c15; rcx+=0x10; r9-=0x10 jne; no match ->jmp 0x66d2c4b [V]. Match-end 0x66d2c15: add rdx,rax; cmp rcx,rdx; jae 0x66d2c4b; else index=(ecx-rax)>>4->[rbp+0x4D0]; byte [rbp+0x4D2]=1; call 0x5679DB0(rdx=&rbp+0x4D0, r8=&rbp+0x7E0, rcx=&rbp+0xCE8) [V] (38th call); nop. Converge 0x66d2c4b: cmp byte [rdi+0x100],1; jne 0x66d2dd2 (new target) [V]; if ==1: rdx=rdi+0xB8; eax=byte [rdi+0xF8]; if eax==0 ->0x66d2c85; else if eax!=1 ->0x66d6c33; else rdx=[rdx] (deref [rdi+0xB8]); lea rcx,&rbp+0xA50; call 0x67747B0(rcx=&rbp+0xA50, rdx=[rdi+0xB8]) [V]; jmp 0x66d2c92. Else path 0x66d2c85: call 0x67747B0(rcx=&rbp+0xA50, rdx=? from prior) [V]. Converge 0x66d2c92: r13=[rbp+0xA58]; r12=[r13]; cmp r12,r13 (phase 14) [V]. [I]: rdi+0x100 is a flag byte; rdi+0xF8 is a switch byte (0/1/>1); call 0x67747B0 consumes the [rbp+0xA50] value (float const or the broadcast float from phase 12/13). 38 call-0x5679db0 + call-0xBCABA00s done.

## COMPRESSED: phases 1–13 of U-BA2 are recorded in this file (0x66d23a3..0x66d2c9d); key state recap:
- 38 call-0x5679DB0 invocations total (10-stride scan series finished at phase 9; match-ends store index at [rbp+0x4D0]/flag [rbp+0x4D2]).
- 37 call-0xBCABA00 invocations total (0x30-stride scan series; match-ends store index at [rbp+0x7E0]/flag [rbp+0x7E2], value struct [rbp+0xA50]=2 bytes + [rbp+0xA54]=0 + [rbp+0xA58]/[rbp+0xA5C]=1, [rsp+0x20]=0 stack slot, rcx=&rbp+0xCE0 out).
- Byte-flag accumulation r14d from bytes [rax+0x1AC..0x1AF] (phase 2). r13w=0x500 ORed with r14b into value low word (phases 3-13).
- TLS gates (eax=[data global]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8]; cmp eax,[rcx+4]; jg <fallback>) at phases 5,6,7,8,10,11,12 with globals [0x128C1A5E],[0x129C13C0],[0x129F9090],[0x129F90A0],[0x129F90B0],[0x129F90C0],[0x129F90D0],[0x129F90E0] and fallbacks 0x66d65dc/0x66d6612/0x66d69e3/0x66d6a60/0x66d6414/0x66d6648/0x66d68ff/0x66d6486.
- Extra: call 0x67747B0(rcx=&rbp+0xA50, rdx=[rdi+0xB8] or [rdi]) at phase 13 after cmp byte [rdi+0x100],1 and byte [rdi+0xF8] switch (0/1/>1); fallback 0x66d6c33, jne target 0x66d2dd2.

## Phase 14 — 0x66d2ca2, 40 instructions [V]
```
66d2ca2  mov bl,0                                      
66d2ca4  add [rax],al                                   
66d2ca6  lea r15,[rbp+0xCE0]                           
66d2cad  lea r14,[rbp+0x400]                           
66d2cb4  lea rbx,[rbp+0x7E0]                           
66d2cbb  xorps xmm6,xmm6                               
66d2cbe  jmp short 0x66D2CE7                           ; -> loc_66d2ce7

loc_66d2cc0:  ; from 66d2d3e
  66d2cc0  add rdx,0x27                                  
  66d2cc4  mov rcx,rax                                   

loc_66d2cc7:  ; from 66d2d2d
  66d2cc7  call 0xE935700                                ; -> sub_e935700
  66d2ccc  movaps [rbp+0x400],xmm6                       
  66d2cd3  mov qword ptr [rbp+0x410],0                   

loc_66d2cde:  ; from 66d2d0e, 66d2d1a
  66d2cde  mov r12,[r12]                                 
  66d2ce2  cmp r12,r13                                   
  66d2ce5  je short 0x66D2D59                            ; -> loc_66d2d59

loc_66d2ce7:  ; from 66d2cbe
  66d2ce7  lea r9,[r12+0x18]                             
  66d2cec  mov rax,[r12+0x10]                            
  66d2cf1  mov [rbp+0x7E0],rax                           
  66d2cf8  mov rcx,r15                                   
  66d2cfb  mov rdx,r14                                   
  66d2cfe  mov r8,rbx                                    
  66d2d01  call 0x66D93C0                                ; -> sub_66d93c0
  66d2d06  nop                                           
  66d2d07  cmp byte ptr [rbp+0x418],1                    
  66d2d0e  jne short 0x66D2CDE                           ; -> loc_66d2cde
  66d2d10  mov rcx,[rbp+0x400]                           
  66d2d17  test rcx,rcx                                  
  66d2d1a  je short 0x66D2CDE                            ; -> loc_66d2cde
  66d2d1c  mov rdx,[rbp+0x410]                           
  66d2d23  sub rdx,rcx                                   
  66d2d26  cmp rdx,0x1000                                
  66d2d2d  jb short 0x66D2CC7                            ; -> loc_66d2cc7
  66d2d2f  mov rax,[rcx-8]                               
  66d2d33  add rcx,0xFFFFFFFFFFFFFFF8                    
  66d2d37  sub rcx,rax                                   
  66d2d3a  jb short 0x66D2CC0                            ; -> loc_66d2cc0

loc_66d2d40:  ; from 66d2d87, 66d3d39
  66d2d40  mov qword ptr [rsp+0x20],0                    
  66d2d49  xor ecx,ecx                                   
  66d2d4b  xor edx,edx                                   
  66d2d4d  xor r8d,r8d                                   
```
`//` [V] `add [rax],al` at 0x66d2ca4 is the usual 2-byte phase-start pad; real code starts 0x66d2ca6 [?]. bl=0; r15=&rbp+0xCE0 (out ctx, same rcx slot as BCABA00 calls), r14=&rbp+0x400 (work buffer), rbx=&rbp+0x7E0 (index/flag slot), xmm6=0.0 [V]. r13=[rbp+0xA58] is the list sentinel (phase 13: r13=[rbp+0xA58], r12=[r13]) [V]. Loop head ce7: walk r12 via [r12] until r12==r13 (je 0x66d2d59 exits loop) [V]; per node: rax=[r12+0x10] (data ptr) -> [rbp+0x7E0] index slot; r9=r12+0x18 (4th arg); call sub_66d93c0(rcx=&rbp+0xCE0, rdx=&rbp+0x400 buffer, r8=&rbp+0x7E0, r9=r12+0x18) — first call to this callee [V]. Flag byte [rbp+0x418]==1? if not, advance node [V]. If yes: rcx=[rbp+0x400]; if null ->advance; else size=[rbp+0x410]-[rbp+0x400]; if size<0x1000 -> cc7: call 0xE935700(rcx=[rbp+0x400]) then zero [rbp+0x400]/[rbp+0x410] [V]; else rax=[rcx-8] (heap chunk header), rcx-=8, rcx-=rax; if below unsigned -> cc0: rdx+=0x27, rcx=rax, call 0xE935700, zero buffer; else fall to d40 block [V]. d40 block (also entered from 66d2d87/66d3d39): [rsp+0x20]=0; ecx=edx=r8d=r9d=0; call qword ptr [0xF9A8C78] (indirect via IAT/global); then d59: rcx=[rbp+0xA68] [V]. [I]: free-list/node walk over nodes linked at [r12] with data at [r12+0x10]; sub_66d93c0 serializes node data into [rbp+0x400..0x410]; small results go to sub_e935700; oversized free chunks do header arithmetic before sub_e935700 or exit via indirect call [0xF9A8C78].

## NEXT
Resume at RVA 0x66d2d50. Run:
`tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x66d2d50 40`
Then continue in 40-instruction phases: next phase starts at the RVA after the last instruction of this phase. On any `(bad)` line, restart the phase at the next address after the bad line. Append each phase right after this block in this file: exact `0xRVA  mnemonic operands` lines, then `// interpretation` tagged [V]/[I]/[?]. Keep this NEXT block current at top of file. Scope: 1200 instructions from 0x66d23a3 (~480 of 1200 done).