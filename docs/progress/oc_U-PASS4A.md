# Progress: U-PASS4A — decode sub_bbdad00 (RVA 0xbbdad00) completely

## NEXT
Transcribe phases from docs/progress/u-pass4a-fn-full.txt continuing at line 116 (loc_bbdaee6 / bbdaee6) through end of function (0xbbdcdc5); then report caller sub_67c9970 (args it builds, object type hints, before/after), sub_bbdad00 arguments (rcx/rdx/r8), pool +0x750 stride-0x88 usage + +0x78 compare, outputs (structures written, callees called), with [V]/[I]/[?] tags.

## SOURCE / METHOD (all static, exe not run)
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe 1.26.62.01. RVAs relative to image base.
- Bounds: `rdis fn 0xbbdad00 --max 10000` → sub_bbdad00 [0xbbdad00..0xbbdcdc5), size 0x20c5, 1 xref in. Raw: docs/progress/u-pass4a-fn-full.txt (2284 lines).
- Caller: `rdis dis 0x67c9970 150`. Raw: docs/progress/u-pass4a-caller-raw.txt (174 lines). Call at 0x67c99be.
- Tags: [V] = seen verbatim in disassembly (cite RVA); [I] = inferred from pattern; [?] = not determined from available data.
- Instruction quotes below are verbatim from rdis (`0xRVA` column as printed, without the `0x` prefix as rdis prints it). Each phase ≤ 40 instructions; interpretation in separate `;` comment lines. Every instruction in [0xbbdad00, 0xbbdcdc5) belongs to exactly one phase.

## PHASES — sub_bbdad00 full transcription

### Phase 1: 0xbbdad00..0xbbdad85 — prologue, fast-path flag check, sub_eec59f0 call, circular-list walk
```
  bbdad00  push rbp                                      
  bbdad01  push r15                                      
  bbdad03  push r14                                      
  bbdad05  push r13                                      
  bbdad07  push r12                                      
  bbdad09  push rsi                                      
  bbdad0a  push rdi                                      
  bbdad0b  push rbx                                      
  bbdad0c  sub rsp,0x368                                 
  bbdad13  lea rbp,[rsp+0x80]                            
  bbdad1b  movaps [rbp+0x2D0],xmm6                       
  bbdad22  mov qword ptr [rbp+0x2C8],0xFFFFFFFFFFFFFFFE  
  bbdad2d  mov r14,rdx                                   
  bbdad30  mov [rbp+0x238],rcx                           
  bbdad37  mov [rbp+0x220],r8                            
  bbdad3e  cmp byte ptr [r8+0x154],1                     ; R a2+0x154
  bbdad46  jne short 0xBBDADA9                           ; -> loc_bbdada9
  bbdad48  mov rdi,[rbp+0x220]                           
  bbdad4f  lea rsi,[rdi+0x158]                           
  bbdad56  mov rcx,rsi                                   
  bbdad59  call 0xEEC59F0                                ; -> sub_eec59f0
  bbdad5e  test eax,eax                                  
  bbdad60  jne 0xBBDCD9E                                 ; -> loc_bbdcd9e
  bbdad66  cmp dword ptr [rdi+0x1A4],0x7FFFFFFF          
  bbdad70  je 0xBBDCDA9                                  ; -> loc_bbdcda9
  bbdad76  mov rdi,[rdi+0x108]                           
  bbdad7d  mov rbx,[rdi]                                 
  bbdad80  cmp rbx,rdi                                   
  bbdad83  je short 0xBBDADA1                            ; -> loc_bbdada1
  bbdad85  nop [rax+rax]                                 ; R ret@eec59f0+0x0+idx
```
; Standard prologue: 0x368-byte frame, rbp = rsp+0x80 [V bbdad0c/13]. Args saved: r14 = rdx (a2) [V bbdad2d], [rbp+0x238] = rcx (a1) [V bbdad30], [rbp+0x220] = r8 (a3) [V bbdad37].
; Fast path [V]: if byte [a3+0x154] != 1 → jump to slow-path entry loc_bbdada9 (bbdad3e/46). Else rdi = a3; rsi = a3+0x158; call sub_eec59f0(rcx = rsi) — if eax != 0 → loc_bbdcd9e (bbdad48-60).
; If dword [rdi+0x1A4] == 0x7FFFFFFF → loc_bbdcda9 (bbdad66/70). Else rdi = [rdi+0x108] (list head), rbx = [rdi] (first node); circular walk: while rbx != rdi: call sub_bc39d70(rcx = rbx+0x20); rbx = [rbx] (next node) [V bbdad76-9f]. Empty list → loc_bbdada1: call sub_eec5a10(rcx = rsi = a3+0x158) [V bbdada1/a4].

### Phase 2: 0xbbdada9..0xbbdadde — slow-path entry, init loop state
```
loc_bbdada9:  ; from bbdad46
  bbdada9  xorps xmm6,xmm6                               
  bbdadac  movaps [rbp+0x1C0],xmm6                       
  bbdadb3  mov qword ptr [rbp+0x1D0],0                   
  bbdadbe  mov r13,[r14]                                 ; R a1+0x0
  bbdadc1  mov [rbp+0x158],r14                           
  bbdadc8  mov r15,[r14+8]                               ; R a1+0x8
  bbdadcc  lea rsi,[rbp-0x50]                            
  bbdadd0  lea rbx,[rbp+0x2A0]                           
  bbdadd7  lea r14,[rbp+0x248]                           
  bbdadde  jmp short 0xBBDADF3                           ; -> loc_bbdadf3
```
; Slow path ([a3+0x154] != 1) [V bbdad46]. xmm6 = 0; zero [rbp+0x1C0] (16 bytes) and [rbp+0x1D0] = 0 (a running counter/cursor end) [V bbdada9-b3]. r13 = [r14+0x0] where r14 = rdx = a2 → array base [V bbdadbe; R a1+0x0]; r15 = [r14+8] → array end [V bbdadc8; R a1+0x8]. r14 reloaded as &[rbp+0x248], rbx = &[rbp+0x2A0] (aligned buffer start slot), rsi = rbp-0x50 (scratch buffer slot) [V bbdadcc-d7]. Fall into loc_bbdadf3 (per-array-element loop).

### Phase 3: 0xbbdadf3..0xbbdae25 — per-element loop entry, element range [r13+0x358, r13+0x360)
```
loc_bbdadf3:  ; from bbdadde
  bbdadf3  cmp r13,r15                                   
  bbdadf6  je 0xBBDAFB8                                  ; -> loc_bbdafb8
  bbdadfc  movaps [rbp+0x2A0],xmm6                       
  bbdae03  mov qword ptr [rbp+0x2B0],0                   
  bbdae0e  mov r12,[r13+0x360]                           
  bbdae15  mov rcx,[r13+0x358]                           
  bbdae1c  mov rax,r12                                   
  bbdae1f  sub rax,rcx                                   
  bbdae22  sub r12,rcx                                   
  bbdae25  je 0xBBDAEE6                                  ; -> loc_bbdaee6
```
; Loop over array elements stepping 0x618 (r13 += 0x618 at loc_bbdadec/bbdadec) from [a2+0] to [a2+8] [V bbdadf3, bbdadec]. Exit r13 == r15 → loc_bbdafb8 [V bbdadf6]. Per element: clear [rbp+0x2A0] (16 bytes) and [rbp+0x2B0] = 0 [V bbdadfc/e03]. r12 = [r13+0x360] (element end), rcx = [r13+0x358] (element start); size = r12 - rcx in both rax and r12 [V bbdae0e-22]. If size == 0 → loc_bbdaee6 [V bbdae25].

### Phase 4: 0xbbdae2b..0xbbdae5f — size halving, allocator dispatch
```
  bbdae2b  sar rax,1                                     
  bbdae2e  js 0xBBDCD5C                                  ; -> loc_bbdcd5c
  bbdae34  cmp rax,0x800                                 
  bbdae3a  jb short 0xBBDAE80                            ; -> loc_bbdae80
  bbdae3c  lea rdi,[r12+0x27]                            
  bbdae41  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bbdae48  mov rax,[rcx]                                 
  bbdae4b  mov rax,[rax+8]                               
  bbdae4f  mov rdx,rdi                                   
  bbdae52  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdae58  nop                                           
  bbdae59  mov rsi,rax                                   
  bbdae5c  test rax,rax                                  
  bbdae5f  je 0xBBDAF9A                                  ; -> loc_bbdaf9a
```
; rax = size/2 (sar); negative → loc_bbdcd5c [V bbdae2e]. If (size/2) < 0x800 i.e. size < 0x1000 → small path loc_bbdae80 [V bbdae34/3a]. Else big allocation: rdi = size + 0x27; rcx = global [data_1233E1A8]; rax = [rcx] (vtable); rax = [rax+8] (method slot); rdx = rdi; indirect call qword ptr [0xF99FFA0] annotated `[data_f99ffa0] = sub_eea6040` → rax = result [V bbdae3c-52]. rsi = rax; if null → loc_bbdaf9a [V bbdae59-5f].

### Phase 5: 0xbbdaebc..0xbbdaee2 — copy element range into allocated buffer
```
  bbdaebc  mov rdx,[r13+0x358]                           
  bbdaec3  mov rdi,[r13+0x360]                           
  bbdaeca  sub rdi,rdx                                   
  bbdaecd  mov rcx,rsi                                   
  bbdaed0  mov r8,rdi                                    
  bbdaed3  call 0xEEC6DE0                                ; -> sub_eec6de0
  bbdaed8  add rdi,rsi                                   
  bbdaedb  mov [rbp+0x2A8],rdi                           
  bbdaee2  lea rsi,[rbp-0x50]                            
```
; Allocated buffer (rsi) copied from element range: rdx = [r13+0x358] (elem start), rdi = [r13+0x360] - rdx (size); call sub_eec6de0(rcx = rsi = dst, rdx = elem start, r8 = size) [V bbdaebc-d3]. rdi = rsi + size → [rbp+0x2A8] = end cursor; rsi = rbp-0x50 scratch reset [V bbdaed8-e2].

### Phase 6: 0xbbdaee6..0xbbdaf3a — empty-size path + 0x170-stride slot array
```
loc_bbdaee6:  ; from bbdae25
  bbdaee6  lea rdx,[r13+8]                               
  bbdaeea  mov byte ptr [rbp+0x280],0                    
  bbdaef1  mov rcx,rsi                                   
  bbdaef4  mov r8,rbx                                    
  bbdaef7  mov r9,r14                                    
  bbdaefa  call 0x566A450                                ; -> sub_566a450
  bbdaeff  nop                                           
  bbdaf00  mov rdx,[rbp+0x1C8]                           
  bbdaf07  cmp rdx,[rbp+0x1D0]                           
  bbdaf0e  je short 0xBBDAF30                            ; -> loc_bbdaf30
  bbdaf10  mov rcx,rdx                                   
  bbdaf13  mov rdx,rsi                                   
  bbdaf16  call 0x5667C80                                ; -> sub_5667c80
  bbdaf1b  nop                                           
  bbdaf1c  add qword ptr [rbp+0x1C8],0x170               
  bbdaf27  jmp short 0xBBDAF40                           ; -> loc_bbdaf40
  bbdaf29  nop [rax]                                     ; R ret@5667c80+0x0
loc_bbdaf30:  ; from bbdaf0e
  bbdaf30  lea rcx,[rbp+0x1C0]                           
  bbdaf37  mov r8,rsi                                    
  bbdaf3a  call 0x56B68C0                                ; -> sub_56b68c0
```
; size==0 path (bbdae25) [V bbdae25]: rdx = r13+8; byte [rbp+0x280] = 0; call sub_566a450(rcx = rsi (buffer or 0), rdx = r13+8, r8 = rbx=&[rbp+0x2A0], r9 = r14=&[rbp+0x248]) [V bbdaee6-fa]. Slot array at [rbp+0x1C0] with fixed 0x170 stride: cursor [rbp+0x1C8] vs end [rbp+0x1D0] [V bbdaf00/07]. If room: sub_5667c80(rcx = [rbp+0x1C8] slot, rdx = rsi); [rbp+0x1C8] += 0x170 [V bbdaf10-1c]. If full: sub_56b68c0(rcx = &[rbp+0x1C0] state, r8 = rsi) — likely grow-and-add [V bbdaf30-3a].

### Phase 7: 0xbbdaf40..0xbbdaf63 — release buffer, check null
```
loc_bbdaf40:  ; from bbdaf27
  bbdaf40  mov rcx,rsi                                   
  bbdaf43  call 0x5667E70                                ; -> sub_5667e70
  bbdaf48  cmp byte ptr [rbp+0x280],1                    
  bbdaf4f  jne short 0xBBDAF59                           ; -> loc_bbdaf59
  bbdaf51  mov rcx,r14                                   
  bbdaf54  call 0x655CEA0                                ; -> sub_655cea0
loc_bbdaf59:  ; from bbdaf4f
  bbdaf59  mov rcx,[rbp+0x2A0]                           
  bbdaf60  test rcx,rcx                                  
  bbdaf63  je 0xBBDADEC                                  ; -> loc_bbdadec
```
; sub_5667e70(rcx = rsi = buffer) — release/process temp buffer [V bbdaf40/43]. If byte [rbp+0x280] == 1: sub_655cea0(rcx = r14 = &[rbp+0x248]) [V bbdaf48-54]. rcx = [rbp+0x2A0] (buffer start); null → loc_bbdadec (element loop back-edge, r13 += 0x618) [V bbdaf59-63].

### Phase 8: 0xbbdaf69..0xbbdaf8f — buffer used/slack computation + helper blocks
```
  bbdaf69  mov rdx,[rbp+0x2B0]                           
  bbdaf70  sub rdx,rcx                                   
  bbdaf73  cmp rdx,0x1000                                
  bbdaf7a  jb 0xBBDADE7                                  ; -> loc_bbdade7
  bbdaf80  mov rax,[rcx-8]                               
  bbdaf84  add rcx,0xFFFFFFFFFFFFFFF8                    
  bbdaf88  sub rcx,rax                                   
  bbdaf8b  cmp rcx,0x20                                  
  bbdaf8f  jb 0xBBDADE0                                  ; -> loc_bbdade0
  bbdaf95  jmp 0xBBDCD42                                 ; -> loc_bbdcd42
```
; rdx = [rbp+0x2B0] - [rbp+0x2A0] = bytes used in buffer; if < 0x1000 → loc_bbdade7 [V bbdaf69-7a]. Else rax = [rcx-8] (original alloc pointer stored 8 bytes before aligned buffer [V bbdae70]); rcx = rcx - 8; rcx -= rax (slack = aligned-8 - original); if < 0x20 → loc_bbdade0 [V bbdaf80-8f]; else → loc_bbdcd42 [V bbdaf95]. Helper blocks referenced here: loc_bbdade0: `add rdx,0x27` / `mov rcx,rax` then `call 0xE935700` [V bbdade0-e7]; loc_bbdade7: `call 0xE935700` [V bbdade7]; loc_bbdadec: `add r13,0x618` (next array element) [V bbdadec].

### Phase 9: 0xbbdaf9a..0xbbdafa3 — big-alloc failure path
```
loc_bbdaf9a:  ; from bbdae5f
  bbdaf9a  mov rcx,rdi                                   
  bbdaf9d  call 0x9BC830                                 ; -> sub_9bc830
  bbdafa2  nop                                           
  bbdafa3  jmp 0xBBDAE65                                 ; -> loc_bbdae65
```
; Alloc returned null (bbdae5c): sub_9bc830(rcx = rdi = size+0x27) [V bbdaf9a-9d], then jmp back to loc_bbdae65 which re-runs the align/store sequence with rax = 0 (rsi = 0x20 after align) and joins bbdaea4 [V bbdafa3, bbdae65-74] — see Phase 12 for the bbdaea4 store semantics.

### Phase 10: 0xbbdafa8..0xbbdafb3 — small-alloc failure path
```
loc_bbdafa8:  ; from bbdae9e
  bbdafa8  mov rcx,r12                                   
  bbdafab  call 0x9BC830                                 ; -> sub_9bc830
  bbdafb0  nop                                           
  bbdafb1  xor esi,esi                                   
  bbdafb3  jmp 0xBBDAEA4                                 ; -> loc_bbdaea4
```
; Small-alloc null (bbdae9e): sub_9bc830(rcx = r12 = size) [V bbdafa8-ab]; rsi = 0 [V bbdafb1]; goto bbdaea4 → [rbp+0x2A0] = [rbp+0x2A8] = 0, [rbp+0x2B0] = r12 (size) [V bbdaea4/ab/eb2/eb5].

### Phase 11: 0xbbdafb8..0xbbdb00c — array done, sub_bbd9be0, counted division by 192
```
loc_bbdafb8:  ; from bbdadf6
  bbdafb8  lea rcx,[rbp+0x128]                           
  bbdafbf  lea rdx,[rbp+0x1C0]                           
  bbdafc6  call 0xBBD9BE0                                ; -> sub_bbd9be0
  bbdafcb  nop                                           
  bbdafcc  mov rbx,[rbp+0x130]                           
  bbdafd3  mov rcx,[rbp+0x128]                           
  bbdafda  mov rax,rbx                                   
  bbdafdd  sub rax,rcx                                   
  bbdafe0  mov rdx,0xCCCCCCCCCCCCCCD                    
  bbdafea  xorps xmm0,xmm0                               
  bbdafed  movaps [rbp+0x160],xmm0                       
  bbdaff4  mov qword ptr [rbp+0x170],0                   
  bbdafff  mov r8,0xCCCCCCCCCCCCCD                       
  bbdb009  sub rbx,rcx                                   
  bbdb00c  je short 0xBBDB061                            ; -> loc_bbdb061
  bbdb00e  sar rax,6                                     
  bbdb012  imul rax,rdx                                  
  bbdb016  cmp rax,r8                                    
  bbdb019  jae 0xBBDCD92                                 ; -> loc_bbdcd92
```
; Element loop finished (r13 == r15) [V bbdadf6]: sub_bbd9be0(rcx = &[rbp+0x128] start, rdx = &[rbp+0x1C0] slot-array state) [V bbdafb8-c6]. rbx = [rbp+0x130] (end), rcx = [rbp+0x128] (start); count_bytes = rbx - rcx [V bbdafcc-09]; zero [rbp+0x160] (16 bytes), [rbp+0x170] = 0, r8 = 0xCCCCCCCCCCCCCCCD [V bbdafea-ff]. Checked division: rax = count_bytes >> 6; rax *= 0xCCCCCCCCCCCCCCCD; if rax >= 0xCCCCCCCCCCCCCCCD (unsigned) → loc_bbdcd92 [V bbdb00e-19]; meaning of divisor [I] (checked /192-ish division of slot-array byte count).

### Phase 12: 0xbbdb066..0xbbdb0d3 — alloc-retry + sub_bc06200 call
```
  bbdb066  jmp short 0xBBDB0D7                           ; -> loc_bbdb0d7
loc_bbdb068:  ; from bbdb023
  bbdb068  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  bbdb06f  mov rax,[rcx]                                 
  bbdb072  mov rax,[rax+8]                               
  bbdb076  mov rdx,rbx                                   
  bbdb079  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb07f  nop                                           
  bbdb080  mov rsi,rax                                   
  bbdb083  test rax,rax                                  
  bbdb086  je 0xBBDCCF6                                  ; -> loc_bbdccf6
loc_bbdb08c:  ; from bbdb05f, bbdcd01
  bbdb08c  mov [rbp+0x160],rsi                           
  bbdb093  mov [rbp+0x168],rsi                           
  bbdb09a  add rbx,rsi                                   
  bbdb09d  mov [rbp+0x170],rbx                           
  bbdb0a4  mov rcx,[rbp+0x128]                           
  bbdb0ab  mov rdx,[rbp+0x130]                           
  bbdb0b2  lea r9,[rbp+0x160]                            
  bbdb0b9  mov r8,rsi                                    
  bbdb0bc  call 0xBC06200                                ; -> sub_bc06200
  bbdb0c1  nop                                           
  bbdb0c2  mov r12,rax                                   
  bbdb0c5  mov [rbp+0x168],rax                           
  bbdb0cc  mov rcx,[rbp+0x160]                           
  bbdb0d3  lea rsi,[rbp-0x50]                            
```
; loc_bbdb068 path (from bbdb023, short-count alloc retry): alloc with size rbx via rcx=[data_1233e1a8], indirect call [0xF99FFA0]=sub_eea6040; rsi=rax; null → loc_bbdccf6 [V bbdb068-86]. loc_bbdb08c: [rbp+0x160]=[rbp+0x168]=rsi (alloc result); rbx += rsi → [rbp+0x170] = end cursor [V bbdb08c-9d]; sub_bc06200(rcx=[rbp+0x128], rdx=[rbp+0x130], r8=rsi, r9=&[rbp+0x160]) → rax=r12, [rbp+0x168]=rax; rcx=[rbp+0x160]; rsi=rbp-0x50 [V bbdb0a4-d3].

### Phase 13: 0xbbdb0d7..0xbbdb107 — outer loop setup, array base [rbp+0x238]+0xA10
```
loc_bbdb0d7:  ; from bbdb066
  bbdb0d7  mov rax,[rbp+0x238]                           
  bbdb0de  mov rax,[rax]                                 
  bbdb0e1  mov [rbp+0x228],rax                           
  bbdb0e8  lea r13,[rax+0xA10]                           
  bbdb0ef  mov r15,0x8F5C28F5C28F5C29                    
  bbdb0f9  mov [rbp+0x230],r12                           
  bbdb100  mov [rbp+0x298],r13                           
  bbdb107  jmp short 0xBBDB13A                           ; -> loc_bbdb13a
  bbdb109  nop [rax]                                     
```
; rcx-arg object ([rbp+0x238] = rcx saved at entry): rax = [rax] (deref), [rbp+0x228] = rax; lea r13, [rax+0xA10] → array base at object+0xA10 [V bbdb0d7-e8]. r15 = magic 0x8F5C28F5C28F5C29 [V bbdb0ef]. [rbp+0x230] = r12; [rbp+0x298] = r13 [V bbdb0f9-100]. Fall into loc_bbdb13a.

### Phase 14: 0xbbdb110..0xbbdb176 — outer stride-0x140 loop + inner list walk
```
loc_bbdb110:  ; from bbdb329, bbdb553, bbdb65a
  bbdb110  mov r15,0x8F5C28F5C28F5C29                    
  bbdb11a  mov r12,[rbp+0x230]                           
  bbdb121  mov r13,[rbp+0x298]                           
loc_bbdb128:  ; from bbdb16d, bbdb728, bbdb745
  bbdb128  mov rcx,[rbp+0x2B8]                           
  bbdb12f  add rcx,0x140                                 
  bbdb136  lea rsi,[rbp-0x50]                            
loc_bbdb13a:  ; from bbdb107
  bbdb13a  cmp rcx,r12                                   
  bbdb13d  je 0xBBDB74A                                  ; -> loc_bbdb74a
  bbdb143  mov [rbp+0x2B8],rcx                           
  bbdb14a  lea rax,[rcx+0x128]                           
  bbdb151  lea rcx,[0xF440900]                           ; [data_f440900]
  bbdb158  mov [rbp-0x50],rcx                            
  bbdb15c  mov [rbp-0x48],rax                            
  bbdb160  mov [rbp-0x18],rsi                            
  bbdb164  mov rsi,[r13]                                 
  bbdb168  cmp rsi,r13                                   
  bbdb16b  jne short 0xBBDB17C                           ; -> loc_bbdb17c
  bbdb16d  jmp short 0xBBDB128                           ; -> loc_bbdb128
  bbdb16f  nop                                           
loc_bbdb170:  ; from bbdb187, bbdb19a
  bbdb170  mov rsi,[rsi]                                 
  bbdb173  cmp rsi,r13                                   
  bbdb176  je 0xBBDB721                                  ; -> loc_bbdb721
```
; loc_bbdb110 re-entry: r15 = magic; r12 = [rbp+0x230] (outer bound); r13 = [rbp+0x298] (array base) [V bbdb110-121]. loc_bbdb128: rcx = [rbp+0x2B8] + 0x140 → outer index advances by 0x140 [V bbdb128/12f]; rsi = rbp-0x50 [V bbdb136]. loc_bbdb13a: rcx == r12 → loc_bbdb74a (outer done) [V bbdb13a/13d]. Else [rbp+0x2B8] = rcx; rax = rcx+0x128; [rbp-0x50] = global ptr [data_f440900]; [rbp-0x48] = rcx+0x128; [rbp-0x18] = rsi [V bbdb143-60]. rsi = [r13] head node; circular list: rsi == r13 (empty) → loc_bbdb128 [V bbdb164-6d]; else loc_bbdb17c. loc_bbdb170: rsi = [rsi] next node; rsi == r13 → loc_bbdb721 [V bbdb170-76].

### Phase 15: 0xbbdb17c..0xbbdb1ec — inner 0xC8 record stride, per-record filters
```
loc_bbdb17c:  ; from bbdb16b
  bbdb17c  mov rdi,[rsi+0x10]                            
  bbdb180  mov rbx,[rsi+0x18]                            
  bbdb184  cmp rdi,rbx                                   
  bbdb187  je short 0xBBDB170                            ; -> loc_bbdb170
  bbdb189  lea r14,[rsi+0x28]                            
  bbdb18d  jmp short 0xBBDB19C                           ; -> loc_bbdb19c
  bbdb18f  nop                                           
loc_bbdb190:  ; from bbdb1a0, bbdb1d0
  bbdb190  add rdi,0xC8                                  
  bbdb197  cmp rdi,rbx                                   
  bbdb19a  je short 0xBBDB170                            ; -> loc_bbdb170
loc_bbdb19c:  ; from bbdb18d
  bbdb19c  test byte ptr [rdi+3],1                       
  bbdb1a0  je short 0xBBDB190                            ; -> loc_bbdb190
  bbdb1a2  mov rcx,[rbp-0x18]                            
  bbdb1a6  test rcx,rcx                                  
  bbdb1a9  je short 0xBBDB1F2                            ; -> loc_bbdb1f2
  bbdb1ab  mov [rbp+0x248],rdi                           
  bbdb1b2  mov [rbp+0x250],r14                           
  bbdb1b9  mov rax,[rcx]                                 
  bbdb1bc  mov rax,[rax+0x10]                            
  bbdb1c0  lea rdx,[rbp+0x248]                           
  bbdb1c7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb1cd  nop                                           
  bbdb1ce  test al,al                                    
  bbdb1d0  je short 0xBBDB190                            ; -> loc_bbdb190
  bbdb1d2  mov rcx,[rbp-0x18]                            
  bbdb1d6  test rcx,rcx                                  
  bbdb1d9  je short 0xBBDB1F2                            ; -> loc_bbdb1f2
  bbdb1db  lea rax,[rbp-0x50]                            
  bbdb1df  cmp rcx,rax                                   
  bbdb1e2  setne dl                                      
  bbdb1e5  mov rax,[rcx]                                 
  bbdb1e8  mov rax,[rax+0x20]                            
  bbdb1ec  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
; rdi = [rsi+0x10] (inner start), rbx = [rsi+0x18] (inner end); empty → loc_bbdb170 [V bbdb17c-87]. r14 = rsi+0x28 [V bbdb189]. loc_bbdb190: rdi += 0xC8 — **0xC8-byte record stride**; rdi == rbx → loc_bbdb170 [V bbdb190-9a]. Record filter: test byte [rdi+3], 1 → skip if clear [V bbdb19c/a0]. rcx = [rbp-0x18] (&data_f440900); null → loc_bbdb1f2 [V bbdb1a2-a9]. [rbp+0x248] = rdi (record), [rbp+0x250] = r14 [V bbdb1ab/b2]. rax = [rcx]; rax = [rax+0x10]; rdx = &[rbp+0x248]; call sub_eea6040 via [0xF99FFA0]; al == 0 → skip record [V bbdb1b9-d0]. rcx = [rbp-0x18]; null → loc_bbdb1f2 [V bbdb1d2-d9]. rax = &[rbp-0x50]; dl = (rcx != &[rbp-0x50]) [V bbdb1db-e2]; rax = [rcx]; rax = [rax+0x20]; call sub_eea6040 [V bbdb1e5-ec].

### Phase 16: 0xbbdb1f2..0xbbdb20a — per-record object fetch
```
loc_bbdb1f2:  ; from bbdb1a9, bbdb1d9
  bbdb1f2  mov rax,[rbp+0x228]                           
  bbdb1f9  mov rsi,[rax+0xA10]                           
  bbdb200  mov rax,[rax+0xA78]                           
  bbdb207  mov rax,[rax]                                 
  bbdb20a  cmp rsi,r13                                   
  bbdb20d  je 0xBBDB300                                  ; -> loc_bbdb300
```
; rax = [rbp+0x228] (= [a1]); rsi = [rax+0xA10]; rax = [rax+0xA78]; rax = [rax]; if rsi == r13 → loc_bbdb300 [V bbdb1f2-20a].

### Phase 17: 0xbbdb20d..0xbbdb239 — counted sum over sub-list (magic multiply)
```
  bbdb20d  je 0xBBDB300                                  ; -> loc_bbdb300
  bbdb213  mov rcx,rsi                                   
  bbdb216  xor edi,edi                                   
  bbdb218  mov r14,[rbp+0x2B8]                           
  bbdb21f  nop                                           
loc_bbdb220:  ; from bbdb239
  bbdb220  mov rdx,[rcx+0x18]                            
  bbdb224  sub rdx,[rcx+0x10]                            
  bbdb228  mov rcx,[rcx]                                 
  bbdb22b  sar rdx,3                                     
  bbdb22f  imul rdx,r15                                 
  bbdb233  add rdi,rdx                                   
  bbdb236  cmp rcx,r13                                   
  bbdb239  jne short 0xBBDB220                           ; -> loc_bbdb220
```
; rcx = rsi (list walker from [rax+0xA10] chain), edi = 0 accumulator, r14 = [rbp+0x2B8] (outer index) [V bbdb213-1f]. Loop loc_bbdb220: rdx = [rcx+0x18] - [rcx+0x10]; rcx = [rcx] (next node); rdx = rdx >> 3; rdx *= r15 (r15 = magic 0x8F5C28F5C28F5C29 set at bbdb0ef/bbdb110; meaning [I]); rdi += rdx; repeat until rcx == r13 [V bbdb220-39]. Sums per-node field-difference scaled by magic constant.

### Phase 18: 0xbbdb23b..0xbbdb28a — pool object + sub_a78940 alloc call
```
  bbdb23b  mov rax,[rax+0x40]                            
  bbdb23f  mov [rbp+0x2C0],rax                           
  bbdb246  test rdi,rdi                                  
  bbdb249  je 0xBBDB319                                  ; -> loc_bbdb319
  bbdb24f  mov rax,0xAAAAAAAAAAAAAAB                     
  bbdb259  cmp rdi,rax                                   
  bbdb25c  jae 0xBBDCD6E                                 ; -> loc_bbdcd6e
  bbdb262  lea rax,[rdi*8]                               
  bbdb26a  lea r8,[rax+rax*2]                            
  bbdb26e  mov rax,[rbp+0x2C0]                           
  bbdb275  mov rcx,[rax]                                 
  bbdb278  mov r9d,1                                     
  bbdb27e  lea rdx,[rbp+0x248]                           
  bbdb285  call 0xA78940                                 ; -> sub_a78940
  bbdb28a  nop                                           
```
; rax = [rax+0x40] → [rbp+0x2C0] (pool object pointer) [V bbdb23b/3f]. test rdi; zero → loc_bbdb319 [V bbdb246/49]. rax = 0xAAAAAAAAAAAAAAB (magic /3); rdi >= that → loc_bbdcd6e (overflow guard) [V bbdb24f-5c]. r8 = rdi*8 + rdi*16 = rdi*24 (byte size) [V bbdb262-6a]. rax = [rbp+0x2C0]; rcx = [rax]; r9d = 1; rdx = &[rbp+0x248]; call sub_a78940 — pool allocate of rdi*24 bytes [V bbdb26e-8a].

### Phase 19: 0xbbdb28b..0xbbdb2cd — two-stage refcount release
```
  bbdb28b  mov rbx,[rbp+0x258]                           
  bbdb292  mov rax,[rbp+0x248]                           
  bbdb299  mov rsi,[rbp+0x250]                           
  bbdb2a0  mov r15,[rax]                                 
  bbdb2a3  test rsi,rsi                                  
  bbdb2a6  je short 0xBBDB2E0                            ; -> loc_bbdb2e0
  bbdb2a8  lock dec dword ptr [rsi+8]                    
  bbdb2ac  jne short 0xBBDB2E0                           ; -> loc_bbdb2e0
  bbdb2ae  mov rax,[rsi]                                 
  bbdb2b1  mov rax,[rax]                                 
  bbdb2b4  mov rcx,rsi                                   
  bbdb2b7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb2bd  lock dec dword ptr [rsi+0xC]                  
  bbdb2c1  jne short 0xBBDB2E0                           ; -> loc_bbdb2e0
  bbdb2c3  mov rax,[rsi]                                 
  bbdb2c6  mov rax,[rax+8]                               
  bbdb2ca  mov rcx,rsi                                   
  bbdb2cd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
; rbx = [rbp+0x258]; rax = [rbp+0x248] (record); rsi = [rbp+0x250]; r15 = [rax] = [record] [V bbdb28b-a0]. Refcount release of object rsi ([rbp+0x250] = [r14] = node+0x28 object): lock dec [rsi+8]; if nonzero → loc_bbdb2e0; else vtable release call [rax] then lock dec [rsi+0xC]; if nonzero → loc_bbdb2e0; else vtable release call [rax+8] [V bbdb2a3-cd]. Two-stage (strong/weak) destroy.

### Phase 20: 0xbbdb2e0..0xbbdb32e — index update + outer-list advance
```
loc_bbdb2e0:  ; from bbdb2a6, bbdb2ac, bbdb2c1
  bbdb2e0  add r15,rbx                                   
  bbdb2e3  lea rax,[rdi+rdi*2]                           
  bbdb2e7  lea rdi,[r15+rax*8]                           
  bbdb2eb  mov rsi,[r13]                                 
  bbdb2ef  jmp short 0xBBDB31E                           ; -> loc_bbdb31e
  bbdb2f1  nop [rax+rax]                                 
loc_bbdb300:  ; from bbdb20d
  bbdb300  mov rax,[rax+0x40]                            
  bbdb304  mov [rbp+0x2C0],rax                           
  bbdb30b  xor edi,edi                                   
  bbdb30d  xor r15d,r15d                                 
  bbdb310  mov r14,[rbp+0x2B8]                           
  bbdb317  jmp short 0xBBDB31E                           ; -> loc_bbdb31e
loc_bbdb319:  ; from bbdb249
  bbdb319  xor edi,edi                                   
  bbdb31b  xor r15d,r15d                                 
loc_bbdb31e:  ; from bbdb2ef, bbdb317
  bbdb31e  mov rax,r13                                   
  bbdb321  mov r13,r15                                   
  bbdb324  cmp rsi,rax                                   
  bbdb327  jne short 0xBBDB340                           ; -> loc_bbdb340
  bbdb329  jmp 0xBBDB110                                 ; -> loc_bbdb110
  bbdb32e  xchg ax,ax                                    
```
; loc_bbdb2e0: r15 += rbx; rax = rdi*3; rdi = r15 + rax*8 = r15 + rdi*24 (running output offset, stride 24 = 0x18 entries); rsi = [r13]; jmp loc_bbdb31e [V bbdb2e0-eb]. loc_bbdb300 (rsi==r13 case): [rbp+0x2C0] = [rax+0x40]; edi = 0; r15d = 0; r14 = [rbp+0x2B8]; jmp loc_bbdb31e [V bbdb300-17]. loc_bbdb319: edi = 0; r15d = 0 [V bbdb319/1b]. loc_bbdb31e: rax = r13 (old list head); r13 = r15 (next head); cmp rsi, rax → different → loc_bbdb340; equal → jmp loc_bbdb110 (outer loop next iteration) [V bbdb31e-29].

### Phase 21: 0xbbdb330..0xbbdb361 — advance to next outer node
```
loc_bbdb330:  ; from bbdb34b, bbdb3aa
  bbdb330  mov rsi,[rsi]                                 
  bbdb333  cmp rsi,[rbp+0x298]                           
  bbdb33a  je 0xBBDB550                                  ; -> loc_bbdb550
loc_bbdb340:  ; from bbdb327
  bbdb340  mov rbx,[rsi+0x10]                            
  bbdb344  mov r12,[rsi+0x18]                            
  bbdb348  cmp rbx,r12                                   
  bbdb34b  je short 0xBBDB330                            ; -> loc_bbdb330
  bbdb34d  lea rax,[rsi+0x28]                            
  bbdb351  mov [rbp+0x288],rax                           
  bbdb358  mov [rbp+0x218],rsi                           
  bbdb35f  jmp short 0xBBDB3AC                           ; -> loc_bbdb3ac
  bbdb361  nop [rax+rax]                                 
```
; loc_bbdb330: rsi = [rsi] next node; rsi == [rbp+0x298] (array base) → loc_bbdb550 (all done) [V bbdb330-3a]. loc_bbdb340: rbx = [rsi+0x10] (inner start), r12 = [rsi+0x18] (inner end); empty → loc_bbdb330 [V bbdb340-4b]. rax = rsi+0x28 → [rbp+0x288]; [rbp+0x218] = rsi (current node); jmp loc_bbdb3ac [V bbdb34d-5f].

### Phase 22: 0xbbdb370..0xbbdb3b9 — output slot write + record valid-mask filter
```
loc_bbdb370:  ; from bbdb3ee, bbdb3f2, bbdb402, bbdb41e
  bbdb370  cmp r13,rdi                                   
  bbdb373  je 0xBBDB429                                  ; -> loc_bbdb429
  bbdb379  mov qword ptr [r13],0                         
  bbdb381  mov [r13+8],rbx                               
  bbdb385  mov rax,[rbp+0x288]                           
  bbdb38c  mov [r13+0x10],rax                            
  bbdb390  add r13,0x18                                  
loc_bbdb3a0:  ; from bbdb3b9, bbdb3ca, bbdb3db, bbdb424, bbdb549
  bbdb3a0  add rbx,0xC8                                  
  bbdb3a7  cmp rbx,r12                                   
  bbdb3aa  je short 0xBBDB330                            ; -> loc_bbdb330
loc_bbdb3ac:  ; from bbdb35f
  bbdb3ac  mov rax,[rbx]                                 
  bbdb3af  mov ecx,eax                                   
  bbdb3b1  not ecx                                       
  bbdb3b3  test ecx,0x3003000                            
  bbdb3b9  jne short 0xBBDB3A0                           ; -> loc_bbdb3a0
```
; loc_bbdb370: output slot r13 == end rdi → loc_bbdb429 (flush) [V bbdb370/73]. Else write 0x18-byte output entry: [r13] = 0; [r13+8] = rbx (record ptr); [r13+0x10] = [rbp+0x288] (node+0x28); r13 += 0x18 [V bbdb379-90]. loc_bbdb3a0: rbx += 0xC8 — **second 0xC8-byte record stride loop**; rbx == r12 → loc_bbdb330 [V bbdb3a0-3aa]. loc_bbdb3ac: rax = [rbx] = record mValidMask +0x00 (u64); ecx = eax; not ecx; test ecx, 0x3003000; nonzero → skip record (invalid mask bits) → loc_bbdb3a0 [V bbdb3ac-b9].

### Phase 23: 0xbbdb3bb..0xbbdb424 — record filter bits + pool-index u16 lookup at +0x10
```
  bbdb3bb  bt rax,0x31                                   
  bbdb3c0  jae short 0xBBDB3CC                           ; -> loc_bbdb3cc
  bbdb3c2  cmp qword ptr [rsi+0x418],0                   
  bbdb3ca  jne short 0xBBDB3A0                           ; -> loc_bbdb3a0
loc_bbdb3cc:  ; from bbdb3c0
  bbdb3cc  bt rax,0x38                                   
  bbdb3d1  jae short 0xBBDB3DD                           ; -> loc_bbdb3dd
  bbdb3d3  cmp qword ptr [rsi+0x370],0                   
  bbdb3db  jne short 0xBBDB3A0                           ; -> loc_bbdb3a0
loc_bbdb3dd:  ; from bbdb3d1
  bbdb3dd  mov rcx,[r14+0x128]                           
  bbdb3e4  mov rdx,[r14+0x130]                           
  bbdb3eb  cmp rcx,rdx                                   
  bbdb3ee  je short 0xBBDB370                            ; -> loc_bbdb370
  bbdb3f0  test al,1                                     
  bbdb3f2  je 0xBBDB370                                  ; -> loc_bbdb370
  bbdb3f8  mov rax,[rsi+0x8B0]                           
  bbdb3ff  test rax,rax                                  
  bbdb402  je 0xBBDB370                                  ; -> loc_bbdb370
  bbdb408  movzx r8d,word ptr [rbx+0x10]                 
  bbdb40d  movzx r8d,word ptr [rax+r8*2]                 
  bbdb412  call 0xE93B480                                ; -> sub_e93b480
  bbdb417  cmp rax,[r14+0x130]                           
  bbdb41e  jne 0xBBDB370                                 ; -> loc_bbdb370
  bbdb424  jmp 0xBBDB3A0                                 ; -> loc_bbdb3a0
```
; Continuing per-record filter (mask test passed at bbdb3b9): bt rax,0x31 (valid-mask bit 49); jae → loc_bbdb3cc; else [rsi+0x418] != 0 → skip [V bbdb3bb-ca]. bt rax,0x38 (bit 56); jae → loc_bbdb3dd; else [rsi+0x370] != 0 → skip [V bbdb3cc-db]. Output slots: rcx=[r14+0x128] vs rdx=[r14+0x130]; equal → loc_bbdb370 flush [V bbdb3dd-ee]. test al,1; clear → loc_bbdb370 [V bbdb3f0-32]. rax = [rsi+0x8B0]; null → loc_bbdb370 [V bbdb3f8-402]. **movzx r8d, word ptr [rbx+0x10]** — read u16 at record +0x10 (pool index); **movzx r8d, word ptr [rax + r8*2]** — index into pool table (rax = [rsi+0x8B0]) [V bbdb408/0d]. call sub_e93b480 [V bbdb412]. cmp rax,[r14+0x130]; jne → loc_bbdb370; else jmp loc_bbdb3a0 (next record) [V bbdb417-24].

### Phase 24: 0xbbdb429..0xbbdb49b — output-buffer flush + sub_a78940 alloc
```
  bbdb429  mov [rbp+0x240],r15                           
  bbdb430  sub r13,r15                                   
  bbdb433  mov rax,r13                                   
  bbdb436  sar rax,3                                     
  bbdb43a  mov rcx,0xAAAAAAAAAAAAAAAB                    
  bbdb444  imul rax,rcx                                  
  bbdb448  lea r14,[rax+1]                               
  bbdb44c  mov r15,rax                                   
  bbdb44f  shr r15,1                                     
  bbdb452  mov rdx,0xAAAAAAAAAAAAAAA                     
  bbdb45c  mov rcx,rdx                                   
  bbdb45f  sub rcx,r15                                   
  bbdb462  add r15,rax                                   
  bbdb465  cmp r15,r14                                   
  bbdb468  cmovbe r15,r14                                
  bbdb46c  cmp rax,rcx                                   
  bbdb46f  cmova r15,rdx                                 
  bbdb473  lea rax,[r15*8]                               
  bbdb47b  lea r8,[rax+rax*2]                            
  bbdb47f  mov rax,[rbp+0x2C0]                           
  bbdb486  mov rcx,[rax]                                 
  bbdb489  mov r9d,1                                     
  bbdb48f  lea rdx,[rbp+0x248]                           
  bbdb496  call 0xA78940                                 ; -> sub_a78940
  bbdb49b  nop                                           
```
; Flush full output buffer: [rbp+0x240] = r15 (saved count); rax = (r13 - r15) >> 3 (filled bytes /8); entry count via magic-multiply divide by 3 with round-up (rax *= 0xAAAAAAAAAAAAAAAB; r14 = rax+1; r15 = rax>>1; ... cmovbe r15, r14 / cmova r15, rdx where rdx = 0xAAAAAAAAAAAAAAA ≈ magic-1) → r15 = entry count [V bbdb429-6f; meaning of /24 division [I]]. r8 = r15*8 + r15*16 = r15*24 (alloc bytes for entries) [V bbdb473-7b]. sub_a78940(rcx = [[rbp+0x2C0]] pool obj, rdx = &[rbp+0x248], r8 = count*24, r9d = 1) → alloc new output batch [V bbdb47f-96].

### Phase 25: 0xbbdb49c..0xbbdb4ec — second two-stage refcount release
```
  bbdb49c  mov rcx,[rbp+0x258]                           
  bbdb4a3  mov rax,[rbp+0x248]                           
  bbdb4aa  mov rdi,[rbp+0x250]                           
  bbdb4b1  mov rsi,[rax]                                 
  bbdb4b4  test rdi,rdi                                  
  bbdb4b7  je short 0xBBDB4F9                            ; -> loc_bbdb4f9
  bbdb4b9  lock dec dword ptr [rdi+8]                    
  bbdb4bd  jne short 0xBBDB4F9                           ; -> loc_bbdb4f9
  bbdb4bf  mov rax,[rdi]                                 
  bbdb4c2  mov rax,[rax]                                 
  bbdb4c5  mov [rbp+0x290],rcx                           
  bbdb4cc  mov rcx,rdi                                   
  bbdb4cf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb4d5  mov rcx,[rbp+0x290]                           
  bbdb4dc  lock dec dword ptr [rdi+0xC]                  
  bbdb4e0  jne short 0xBBDB4F9                           ; -> loc_bbdb4f9
  bbdb4e2  mov rax,[rdi]                                 
  bbdb4e5  mov rax,[rax+8]                               
  bbdb4e9  mov rcx,rdi                                   
  bbdb4ec  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  bbdb4f2  mov rcx,[rbp+0x290]                           
```
; rcx = [rbp+0x258]; rax = [rbp+0x248] (record); rdi = [rbp+0x250]; rsi = [rax] = [record+0x0] [V bbdb49c-b1]. test rdi; zero → loc_bbdb4f9 [V bbdb4b4/4b7]. Two-stage release of rdi: lock dec [rdi+8] (nonzero → loc_bbdb4f9); else vtable release [rax]; rcx spilled to [rbp+0x290]; lock dec [rdi+0xC] (nonzero → loc_bbdb4f9); else vtable release [rax+8]; rcx restored [V bbdb4b9-ec]. Identical pattern to Phase 19.

### Phase 26: 0xbbdb4f9..0xbbdb549 — write output entry + sub_eec6de0 copy + advance cursors
```
  bbdb4f9  add rsi,rcx                                   
  bbdb4fc  mov qword ptr [r13+rsi],0                     
  bbdb505  mov [r13+rsi+8],rbx                           
  bbdb50a  mov rax,[rbp+0x288]                           
  bbdb511  mov [r13+rsi+0x10],rax                        
  bbdb516  mov rcx,rsi                                   
  bbdb519  mov rdx,[rbp+0x240]                           
  bbdb520  mov r8,r13                                    
  bbdb523  call 0xEEC6DE0                                ; -> sub_eec6de0
  bbdb528  lea rax,[r14+r14*2]                           
  bbdb52c  lea r13,[rsi+rax*8]                           
  bbdb530  lea rax,[r15+r15*2]                           
  bbdb534  lea rdi,[rsi+rax*8]                           
  bbdb538  mov r15,rsi                                   
  bbdb53b  mov r14,[rbp+0x2B8]                           
  bbdb542  mov rsi,[rbp+0x218]                           
  bbdb549  jmp 0xBBDB3A0                                 ; -> loc_bbdb3a0
  bbdb54e  xchg ax,ax                                    
```
; rsi += rcx; at output offset rsi in buffer r13: entry [r13+rsi+0] = 0; [r13+rsi+8] = rbx (record ptr); [r13+rsi+0x10] = [rbp+0x288] (node+0x28) — **0x18-byte output entries: {0, record, node+0x28}** [V bbdb4f9-11]. sub_eec6de0(rcx = rsi (dst offset), rdx = [rbp+0x240] (count), r8 = r13 (buffer)) — copies count entries into buffer [V bbdb516-23]. Advance: r13 = rsi + r14*24 (new end); rdi = rsi + r15*24 (new cursor); r15 = rsi (new start); r14 = [rbp+0x2B8]; rsi = [rbp+0x218] (node); jmp loc_bbdb3a0 [V bbdb528-49]. All multiplies are *24 = *3*8 (0x18 entry stride).

### Phase 27: 0xbbdb550..0xbbdb59a — final flush of remaining entries + sub_5689800
```
loc_bbdb550:  ; from bbdb33a
  bbdb550  cmp r15,r13                                   
  bbdb553  je 0xBBDB110                                  ; -> loc_bbdb110
  bbdb559  mov rsi,r13                                   
  bbdb55c  sub rsi,r15                                   
  bbdb55f  mov rdi,rsi                                   
  bbdb562  sar rdi,3                                     
  bbdb566  mov rax,0xAAAAAAAAAAAAAAAB                    
  bbdb570  imul rdi,rax                                  
  bbdb574  mov r12,r15                                   
  bbdb577  mov rcx,r15                                   
  bbdb57a  mov rdx,r13                                   
  bbdb57d  mov r8,rdi                                    
  bbdb580  call 0x5689800                                ; -> sub_5689800
  bbdb585  nop                                           
  bbdb586  lea r15,[rbp+0x2A0]                           
  bbdb58d  mov rax,0xAAAAAAAAAAAAAAB                     
  bbdb597  cmp rdi,rax                                   
  bbdb59a  jae 0xBBDCD74                                 ; -> loc_bbdcd74
```
; loc_bbdb550 (outer array exhausted): r15 == r13 → loc_bbdb110 (next outer iteration) [V bbdb550/53]. Else rsi = r13 - r15 (remaining filled bytes); rdi = rsi >> 3; rdi *= 0xAAAAAAAAAAAAAAAB (/3 magic) → remaining entry count [V bbdb559-70]. r12 = r15; rcx = r15; rdx = r13; r8 = count; call sub_5689800 — final flush of remaining entries [V bbdb574-85]. r15 = &[rbp+0x2A0] (temp-buffer start slot reset); rax = 0xAAAAAAAAAAAAAAB; rdi(count) >= that → loc_bbdcd74 [V bbdb586-9a].
