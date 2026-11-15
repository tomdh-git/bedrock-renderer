# U-SK3: sky visitor 0x66560f0 — detailed instruction decode (1.26.62.01)

## NEXT
SkyAmbientSamples case at 0x665708b: DONE — phases 1-21 written (0x665708b..0x665803c); case exits via jmp sub_665d124 at 0x6657ff4 (shared function epilogue). VolumetricFog case at 0x66569b1: phases 22-46 written (0x66569b1..0x6657da4); phase 47 next (0x6657da4..0x6657e4a; epilogue release loop + heap check); next RVA: 0x6657e4a.

## Decode

### Phase 1 — SkyAmbientSamples entry, zero-init buffer, first light sample [V]
`0x665708b..0x6657160` (40 instr)
```
665708b  mov r14,[rdi+8]
665708f  mov [rbp+0x1E8],r14
6657096  mov [rbp+0x1F0],r12
665709d  mov ecx,0x9D0
66570a2  add rcx,[rsi+0x10]
66570a6  call 0x5ABA5C0
66570ab  nop
66570ac  mov rsi,rax
66570af  xorps xmm0,xmm0
66570b2  movaps [rbp+0x3F0],xmm0
66570b9  movaps [rbp+0x3E0],xmm0
66570c0  movaps [rbp+0x3D0],xmm0
66570c7  movaps [rbp+0x3C0],xmm0
66570ce  movaps [rbp+0x3B0],xmm0
66570d5  movaps [rbp+0x3A0],xmm0
66570dc  movaps [rbp+0x390],xmm0
66570e3  movaps [rbp+0x380],xmm0
66570ea  movaps [rbp+0x370],xmm0
66570f1  movaps [rbp+0x360],xmm0
66570f8  movaps [rbp+0x350],xmm0
66570ff  movaps [rbp+0x340],xmm0
6657106  mov qword ptr [rbp+0x400],0
6657111  mov rcx,[0x1233E1B0]
6657118  mov rax,[rcx]
665711b  mov rax,[rax+0x10]
665711f  mov dl,0x4A
6657121  call qword ptr [0xF99FFA0]
6657127  nop
6657128  mov edx,eax
665712a  mov r15,[rsi+0xB0]
6657131  cmp r15,[rsi+0xB8]
6657138  je 0x66572F6
665713e  xorps xmm0,xmm0
6657141  movups [r15],xmm0
6657145  test r12,r12
6657148  je 0x6657429
665714e  lock inc dword ptr [r12+8]
6657154  mov edi,0x200000
6657159  or rdi,[rbp+0x348]
6657160  mov r14,[rbp+0x1E8]
```
// [V] Entry: save rdi+8 (some pointer) into [rbp+0x1E8], save r12 into [rbp+0x1F0]. [V] 0x9D0=2512 bytes allocated via sub_5aba5c0 (operator new) at rsi+0x10 base; rsi = new buffer. [V] Zero-init 13 movaps (16 bytes each) = 208 bytes at [rbp+0x340..0x400), plus qword at 0x400 → a 216-byte zeroed struct/scratch. [V] Load global [0x1233E1B0] → its [0x10] → call indirect [0xF99FFA0] with dl=0x4A=74; result in eax → edx (a count, 0..74?). [V] r15 = rsi+0xB0 begin ptr; compare to rsi+0xB8 end ptr; if empty jump to 0x66572F6 (shared tail). [V] Else zero 16 bytes at r15 (movups xmm0). [V] test r12 (saved earlier, possibly a ref-counted object); if null jump 0x6657429. [V] Else lock inc dword [r12+8] (AddRef). [V] edi=0x200000=2097152, or with [rbp+0x348] (flags) → rdi. [V] r14 = [rbp+0x1E8] (the saved rdi+8 pointer).

## Context
Unit U-SK3 (sky visitor 0x66560f0), part of ext-particle-sky (particle 0x67417f0, sky/clouds 0x67375a0). Context from docs/progress/ext-particle-sky.md and docs/functions/ext_particle_sky_callees.md: the sky cases (stars, celestial, cubemap, end sky, volumetric fog) live in the 0x66560f0 area; Stars DONE at statement level; OPEN: joins 665c269/665c38a/665b624, SkyAmbientSamples 665708b, VolumetricFog 66569b1, cold 665cf64..665d7e5. This unit decodes SkyAmbientSamples (665708b) and VolumetricFog (66569b1) instruction-completely until each case ends.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Static analysis only; exe = Minecraft.Windows 1.26.62.01.

## Decode

### Phase 2 — SkyAmbientSamples sample index via magic multiply + hash setup [V]
`0x6657160..0x665721c` (40 instr)
```
6657160  mov r14,[rbp+0x1E8]                           
6657167  mov rax,[rbp+0x1F0]                           
665716e  jmp 0x6657430                                 ; -> loc_6657430
6657173  mov r14,rbx                                   
6657176  sub r14,[rsi+0x150]                           
665717d  mov rax,r14                                   
6657180  sar rax,3                                     
6657184  mov rdx,0x2E8BA2E8BA2E8BA3                    
665718e  imul rdx,rax                                  
6657192  lea r10,[rdx+1]                               
6657196  mov rax,rdx                                   
6657199  shr rax,1                                     
665719c  mov rcx,0x2E8BA2E8BA2E8BA                     
66571a6  mov r8,rcx                                    
66571a9  sub r8,rax                                    
66571ac  add rax,rdx                                   
66571af  cmp rax,r10                                   
66571b2  cmovbe rax,r10                                
66571b6  cmp rdx,r8                                    
66571b9  cmova rax,rcx                                 
66571bd  mov rdx,0x2E8BA2E8BA2E8BB                     
66571c7  cmp rax,rdx                                   
66571ca  mov [rbp+0x540],r9b                           
66571d1  jae 0x665D665                                 ; -> sub_665d665
66571d7  imul rdi,rax,0x58                             
66571db  test rax,rax                                  
66571de  mov [rbp+0x1C8],r10                           
66571e5  je 0x6657699                                  ; -> loc_6657699
66571eb  cmp rax,0x2F                                  
66571ef  jb 0x6657670                                  ; -> loc_6657670
66571f5  cmp rax,rcx                                   
66571f8  je 0x665DB15                                  ; -> sub_665db15
66571fe  lea rdx,[rdi+0x27]                            
6657202  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
6657209  mov rax,[rcx]                                 
665720c  mov rax,[rax+8]                               
6657210  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657216  nop                                           
6657217  mov r15,rax                                   
665721a  test rax,rax                                  
```
// [V] Entry block 0x6657160..0x665716e (repeats phase-1 last insn): r14=[rbp+0x1E8], rax=[rbp+0x1F0], unconditional jmp to loc_6657430 (shared tail); linear code at 0x6657173 is a separate basic block reached from elsewhere ([?] source). [V] Block 0x6657173: r14 = rbx - [rsi+0x150] (time diff vs sky sample base); rax = r14 sar 3 (signed /8). [V] Magic multiply rdx = rax * 0x2E8BA2E8BA2E8BA3 (low 64 of 64x64); clamp sequence: r10 = rdx+1; rax = (rdx>>1) + rdx; if rax <= r10 unsigned → rax = r10; r8 = 0x2E8BA2E8BA2E8BA - rax; if rdx > r8 unsigned → rax = 0x2E8BA2E8BA2E8BA (clamp sentinel). [V] Bounds check: if rax >= 0x2E8BA2E8BA2E8BB → jump sub_665d665 (likely out-of-range error). [V] rdi = rax * 0x58 (88-byte stride per ambient sample entry). [V] Stores: [rbp+0x540] = r9b; [rbp+0x1C8] = r10. [V] Index branches: rax == 0 → loc_6657699; rax < 0x2F (47) → loc_6657670; rax == rcx (0x2E8BA2E8BA2E8BA sentinel) → sub_665db15. [V] Otherwise rdx = rdi + 0x27 (sample entry + 0x27); rcx = global [0x1233E1A8] (data_1233e1a8); rax = [rcx], then rax = [rax+8] (object vtable/length field); call qword ptr [0xF99FFA0] (rdis annotates data_f99ffa0 = sub_eea6040) [I] hash/lookup call with data ptr in rdx and length in rax; r15 = return value. [V] test rax,rax at 0x665721a, fall-through to next phase. [I] This computes a clamped sky-ambient sample index (stride 0x58=88, ~47-entry range per the 0x2F comparison) into a sample ring/array and hashes bytes at entry+0x27; index 0 and sentinel-max take special paths. [?] exact branch source into the 0x6657173 block; semantic meaning of diff/8 and of the clamp result.

NEXT RVA: 0x665721c

### Phase 3 — SkyAmbientSamples hash post-processing + second index [V]
`0x665721c..0x66572d5` (40 instr)
```
665721c  ror byte ptr [rdi],0x84                       
665721f  mov bl,[rdi]                                  
6657222  add [rcx+rcx*4-8],cl                          ; W a0-0x8+idx
6657226  add r15,0x27                                  
665722a  and r15,0xFFFFFFFFFFFFFFE0                    
665722e  mov [r15-8],rax                               
6657232  jmp 0x665769C                                 ; -> loc_665769c
6657237  mov rax,r15                                   
665723a  sub rax,[rsi+0x540]                           
6657241  mov [rbp+0x540],rax                           
6657248  sar rax,4                                     
665724c  mov rcx,0x86BCA1AF286BCA1B                    
6657256  imul rcx,rax                                  
665725a  lea r9,[rcx+1]                                
665725e  mov rax,rcx                                   
6657261  shr rax,1                                     
6657264  mov rdx,0xD79435E50D7943                      
665726e  mov r8,rdx                                    
6657271  sub r8,rax                                    
6657274  add rax,rcx                                   
6657277  cmp rax,r9                                    
665727a  cmovbe rax,r9                                 
665727e  cmp rcx,r8                                    
6657281  cmova rax,rdx                                 
6657285  mov rcx,0xD79435E50D7944                      
665728f  cmp rax,rcx                                   
6657292  mov [rbp+0x48],bl                             
6657295  jae 0x665D66B                                 ; -> sub_665d66b
665729b  imul r13,rax,0x130                            
66572a2  test rax,rax                                  
66572a5  mov [rbp-0x28],r9                             
66572a9  mov [rbp+0x40],r13                            
66572ad  je 0x665790A                                  ; -> loc_665790a
66572b3  cmp rax,0xE                                   
66572b7  jb 0x66578E0                                  ; -> loc_66578e0
66572bd  lea rdx,[r13+0x27]                            
66572c1  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
66572c8  mov rax,[rcx]                                 
66572cb  mov rax,[rax+8]                               
66572cf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
// [V] Block A 0x665721c..0x6657237 (fall-through from phase-2 test rax,rax; registers rdi/rcx/rax are post-call values of sub_eea6040, [I] caller-saved clobber): ror byte ptr [rdi],0x84 (rotate byte at [rdi] right by 0x84); bl = [rdi]; add byte [rcx+rcx*4-8] += cl (rdis annotation "W a0-0x8+idx" — table write at rcx*5-8); r15 += 0x27; r15 &= 0xFFFFFFFFFFFFFFE0 (align down to 32); [r15-8] = rax; jmp loc_665769c. [V] Block B 0x6657237..0x66572d5 (separate basic block, [?] branch source): rax = r15 - [rsi+0x540]; [rbp+0x540] = rax; rax = rax sar 4 (/16); magic multiply rdx/rcx sequence with 0x86BCA1AF286BCA1B (≈ /17): r9 = rcx+1; rax = (rcx>>1)+rcx; clamp [r9, 0x86BCA1AF286BCA1B] via cmovbe/cmova; [rbp+0x48] = bl; bounds: if rax >= 0xD79435E50D7944 → sub_665d66b. [V] r13 = rax * 0x130 (304-byte stride). [V] Stores: [rbp-0x28] = r9; [rbp+0x40] = r13. [V] Index branches: rax == 0 → loc_665790a; rax < 0xE (14) → loc_66578e0; else rdx = r13 + 0x27; rcx = global [0x1233E1A8] (data_1233e1a8); rax = [rcx]; rax = [rax+8]; call qword ptr [0xF99FFA0] (sub_eea6040) [I] second hash/lookup on entry at r13+0x27; phase ends at the call (0x66572cf), next RVA 0x66572d5. [I] Two parallel hashed tables appear: Block A stride-0x58 table (phase 2) post-processes a 32-byte-aligned bucket (store at [r15-8]); Block B stride-0x130 table re-hashes. [?] block-entry sources; exact roles of r15 bucket and bl.

### Phase 4 — SkyAmbientSamples bucket insert + empty-list index path [V]
`0x66572d5..0x6657387` (40 instr)
```
66572d5  nop                                           
66572d6  mov rbx,rax                                   
66572d9  test rax,rax                                  
66572dc  je 0x665D1BC                                  ; -> sub_665d1bc
66572e2  mov rax,rbx                                   
66572e5  add rbx,0x27                                  
66572e9  and rbx,0xFFFFFFFFFFFFFFE0                    
66572ed  mov [rbx-8],rax                               
66572f1  jmp 0x665790C                                 ; -> loc_665790c
66572f6  mov [rbp+0x1C8],dl                            
66572fc  mov rdi,r15                                   
66572ff  sub rdi,[rsi+0xA8]                            
6657306  mov rcx,rdi                                   
6657309  sar rcx,4                                     
665730d  lea r13,[rcx+1]                               
6657311  mov rax,rcx                                   
6657314  shr rax,1                                     
6657317  mov rdx,0xFFFFFFFFFFFFFFF                     
6657321  mov r8,rdx                                    
6657324  sub r8,rax                                    
6657327  add rax,rcx                                   
665732a  cmp rax,r13                                   
665732d  cmovbe rax,r13                                
6657331  cmp rcx,r8                                    
6657334  cmova rax,rdx                                 
6657338  mov rcx,rax                                   
665733b  shr rcx,0x3C                                  
665733f  jne 0x665D671                                 ; -> sub_665d671
6657345  mov rcx,rax                                   
6657348  shl rcx,4                                     
665734c  mov [rbp+0x540],rcx                           
6657353  test rax,rax                                  
6657356  mov [rbp+0x40],bx                             
665735a  je 0x665802A                                  ; -> loc_665802a
6657360  cmp rax,0x100                                 
6657366  jb 0x6657FF9                                  ; -> loc_6657ff9
665736c  mov rcx,0xFFFFFFFFFFFFFFE                     
6657376  cmp rax,rcx                                   
6657379  jae 0x665DB1B                                 ; -> sub_665db1b
665737f  mov rax,[rbp+0x540]                           
```
// [V] Block C 0x66572d5..0x66572f6 (fall-through from phase-3 second call, rax = its return): nop; rbx = rax; test rax,rax; if 0 → sub_665d1bc; rbx = rax + 0x27; rbx &= 0xFFFFFFFFFFFFFFE0 (align down to 32); [rbx-8] = rax (store length/count at aligned bucket - 8); jmp loc_665790c. [V] Block D 0x66572f6..0x6657387 (target of phase-1 `je 0x66572F6` — empty sample list at [rsi+0xB0]==[rsi+0xB8]): [rbp+0x1C8] = dl; rdi = r15 - [rsi+0xA8] (byte offset); rcx = rdi >> 4 (/16); r13 = rcx+1; magic sequence with 0xFFFFFFFFFFFFFFF then clamp [r13, 0xFFFFFFFFFFFFFFF] via cmovbe/cmova; if (rax >> 60) != 0 → sub_665d671 (sanity: index < 2^60); rcx = rax << 4 (= rax*16); [rbp+0x540] = rcx; [rbp+0x40] = bx; test rax,rax; if 0 → loc_665802a; if rax < 0x100 → loc_6657ff9; rcx = 0xFFFFFFFFFFFFFFE; if rax >= 0xFFFFFFFFFFFFFFE → sub_665db1b; rax = [rbp+0x540] (phase cut at 0x665737f). [V] Stores: [rbp+0x1C8]=dl, [rbp+0x540]=rcx (rax*16), [rbp+0x40]=bx. [I] Block D computes a stride-16 index into another sky table from a byte offset /16; Block C is a 32-byte-aligned bucket insert ([bucket-8] = count). [?] why two index systems (/8/0x58, /16/0x130, /16/16); block-entry source of Block D other than phase-1 je.

### Phase 5 — SkyAmbientSamples record write + shared tails [V]
`0x6657387..0x6657444` (40 instr)
```
6657387  lea edx,[rax+0x27]                            
665738a  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
6657391  mov rax,[rcx]                                 
6657394  mov rax,[rax+8]                               
6657398  mov [rbp+0x48],rdx                            
665739c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66573a2  nop                                           
66573a3  mov rbx,rax                                   
66573a6  test rax,rax                                  
66573a9  je 0x665D1CB                                  ; -> sub_665d1cb
66573af  mov rax,rbx                                   
66573b2  add rbx,0x27                                  
66573b6  and rbx,0xFFFFFFFFFFFFFFE0                    
66573ba  mov [rbx-8],rax                               
66573be  jmp 0x665802C                                 ; -> loc_665802c
66573c3  xor eax,eax                                   
66573c5  mov [r15+0x30],rdi                            
66573c9  mov [r15+0x38],rax                            
66573cd  movss [r15+0x40],xmm6                         
66573d3  movss [r15+0x44],xmm12                        
66573d9  movss [r15+0x48],xmm9                         
66573df  movlps [r15+0x4C],xmm7                        
66573e4  movups xmm0,[rcx+0x54]                        
66573e8  movups [r15+0x54],xmm0                        
66573ed  movlps [r15+0x64],xmm8                        
66573f2  movss [r15+0x6C],xmm10                        
66573f8  lea rcx,[r15+0x70]                            
66573fc  mov r8d,0xAD                                  
6657402  mov rdx,r13                                   
6657405  call 0xEEC6EC0                                ; -> sub_eec6ec0
665740a  movlps [r15+0x120],xmm11                      
6657412  mov [r15+0x128],r12                           
6657419  add qword ptr [rsi+0x548],0x130               
6657424  jmp 0x6657E7C                                 ; -> loc_6657e7c
6657429  mov edi,0x200000                              
665742e  xor eax,eax                                   
6657430  mov [r15],r14                                 
6657433  mov [r15+8],rax                               
6657437  add qword ptr [rsi+0xB0],0x10                 
665743f  jmp 0x6658215                                 ; -> loc_6658215
```
// [V] Block E 0x6657387..0x66573c3 (continuation of Block D: rax=[rbp+0x540]=index*16): edx = rax + 0x27; rcx = global [0x1233E1A8]; rax = [rcx]; rax = [rax+8]; [rbp+0x48] = rdx; call qword ptr [0xF99FFA0] (sub_eea6040) → rbx = return; test rax,rax; if 0 → sub_665d1cb; rbx += 0x27; rbx &= ~0x1F; [rbx-8] = rax; jmp loc_665802c. Same 32-byte-aligned bucket insert ([bucket-8] = count) as Block C. [V] Block F 0x66573c3..0x6657429 (the record store at r15, stride-0x130 table entry): [r15+0x30]=rdi; [r15+0x38]=0; movss [r15+0x40]=xmm6, [r15+0x44]=xmm12, [r15+0x48]=xmm9; movlps [r15+0x4C]=xmm7; movups [r15+0x54]=[rcx+0x54]; movlps [r15+0x64]=xmm8; movss [r15+0x6C]=xmm10; lea rcx=[r15+0x70]; r8d=0xAD (173); rdx=r13; call 0xEEC6EC0 (sub_eec6ec0) [I] ~173-byte copy into [r15+0x70]; movlps [r15+0x120]=xmm11; [r15+0x128]=r12; add qword ptr [rsi+0x548],0x130 (advance table cursor by record stride 0x130=304 — matches Block B r13=rax*0x130); jmp loc_6657e7c. Record spans [r15+0x30..0x130). [V] Block G 0x6657429..0x665743f (target of phase-1 `test r12,r12; je 0x6657429` — r12==0 empty case): edi=0x200000; eax=0; mov [r15]=r14; mov [r15+8]=rax(0); add qword ptr [rsi+0xB0],0x10 (advance 16-byte-entry list cursor); jmp loc_6658215. Empty record = {r14, 0} (16 bytes). [I] Two cursors on rsi: [rsi+0x548] stride-0x130 record table, [rsi+0xB0] stride-0x10 entry list (end marker [rsi+0xB8]). loc_6657e7c / loc_6658215 are likely case-exit joins — next phase will confirm whether SkyAmbientSamples ends there. NEXT RVA: 0x6657444

### Phase 6 — SkyAmbientSamples ref-counted Release epilogue [V]
`0x6657444..0x66574f6` (40 instr)
```
6657444  mov rax,[rax]                                 
6657447  mov rax,[rax+0x18]                            
665744b  mov r14,[rax]                                 
665744e  test r14,r14                                  
6657451  je 0x665D11D                                  ; -> sub_665d11d
6657457  mov r14,[rsi]                                 
665745a  mov rax,[rbp+0x330]                           
6657461  xorps xmm0,xmm0                               
6657464  movaps [rbp+0x340],xmm0                       
665746b  mov rcx,[rax+8]                               
665746f  test rcx,rcx                                  
6657472  je 0x6658355                                  ; -> loc_6658355
6657478  lock inc dword ptr [rcx+8]                    
665747c  mov rbx,[rbp+0x348]                           
6657483  movups xmm0,[rax]                             
6657486  movaps [rbp+0x340],xmm0                       
665748d  test rbx,rbx                                  
6657490  je 0x665836A                                  ; -> loc_665836a
6657496  lock dec dword ptr [rbx+8]                    
665749a  jne 0x665836A                                 ; -> loc_665836a
66574a0  mov rax,[rbx]                                 
66574a3  mov rax,[rax]                                 
66574a6  mov rcx,rbx                                   
66574a9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66574af  lock dec dword ptr [rbx+0xC]                  
66574b3  jne 0x665836A                                 ; -> loc_665836a
66574b9 mov rax,[rbx]                                 
66574bc mov rax,[rax+8]                               
66574c0 mov rcx,rbx                                   
66574c3 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66574c9 jmp 0x665836A                                 ; -> loc_665836a
66574ce mov rax,[rax]                                 
66574d1 mov rax,[rax+0x18]                            
66574d5 mov r14,[rax]                                 
66574d8 test r14,r14                                  
66574db je 0x665AEE8                                  ; -> sub_665aee8
66574e1 mov r14,[rsi]                                 
66574e4 mov rax,[rbp+0x320]                           
66574eb xorps xmm0,xmm0                               
66574ee movaps [rbp+0x340],xmm0                       
```
// [V] Block H 0x6657444..0x66574ce: rax=[rax]; rax=[rax+0x18]; r14=[rax]; if r14==0 → sub_665d11d; r14=[rsi]; rax=[rbp+0x330]; zero [rbp+0x340]; rcx=[rax+8]; if rcx==0 → loc_6658355; lock inc dword [rcx+8] (AddRef); rbx=[rbp+0x348]; xmm0=[rax]; [rbp+0x340]=xmm0; if rbx==0 → loc_665836A; lock dec dword [rbx+8]; if !=0 → loc_665836A (Release); rax=[rbx]; rax=[rax]; rcx=rbx; call sub_eea6040 (stage-1 destroy); lock dec dword [rbx+0xC]; if !=0 → loc_665836A; rax=[rbx]; rax=[rax+8]; rcx=rbx; call sub_eea6040 (stage-2 destroy/free); jmp loc_665836a. [V] Block I 0x66574ce..0x66574f6 (repeat pattern, second object at [rbp+0x320] vs 0x330): rax=[rax]; rax=[rax+0x18]; r14=[rax]; if r14==0 → sub_665aee8; r14=[rsi]; rax=[rbp+0x320]; zero [rbp+0x340] (cut at 0x66574ee). [V] Ref-count fields: [rcx+8] lock inc; [rbx+8] lock dec; [rbx+0xC] lock dec. [I] sub_eea6040 called twice per destroyed object = two-stage destruction (dtor then free); loc_6658355/loc_665836a = Release epilogues. This epilogue releases the refs taken earlier ([r12+8] AddRef at 0x665714e, [rcx+8] here) — SkyAmbientSamples case is winding down; blocks jump to shared tails loc_6658355/loc_665836a rather than continuing linearly, so the case end is near. NEXT RVA: 0x66574f6

### Phase 7 — SkyAmbientSamples Release epilogue continues (objects 3-4) [V]
`0x66574f6..0x66575a6` (40 instr)
```
66574f6  mov ecx,[rax+8]                               
66574f9  test rcx,rcx                                  
66574fc  je 0x6658445                                  ; -> loc_6658445
6657502  lock inc dword ptr [rcx+8]                    
6657506  mov rbx,[rbp+0x348]                           
665750d  movups xmm0,[rax]                             
6657510  movaps [rbp+0x340],xmm0                       
6657517  test rbx,rbx                                  
665751a  je 0x665845A                                  ; -> loc_665845a
6657520  lock dec dword ptr [rbx+8]                    
6657524  jne 0x665845A                                 ; -> loc_665845a
665752a  mov rax,[rbx]                                 
665752d  mov rax,[rax]                                 
6657530  mov rcx,rbx                                   
6657533  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657539  lock dec dword ptr [rbx+0xC]                  
665753d jne 0x665845A                                 ; -> loc_665845a
6657543 mov rax,[rbx]                                 
6657546 mov rax,[rax+8]                               
665754a mov rcx,rbx                                   
665754d call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657553 jmp 0x665845A                                 ; -> loc_665845a
6657558 mov rax,[rax]                                 
665755b mov rax,[rax+0x18]                            
665755f mov r15,[rax]                                 
6657562 test r15,r15                                  
6657565 je 0x665AEE8                                  ; -> sub_665aee8
665756b mov r15,[rsi]                                 
665756e mov rax,[rbp+0x320]                           
6657575 xorps xmm0,xmm0                               
6657578 movaps [rbp+0x340],xmm0                       
665757f mov rcx,[rax+8]                               
6657583 test rcx,rcx                                  
6657586 je 0x66585B4                                  ; -> loc_66585b4
665758c lock inc dword ptr [rcx+8]                    
6657590 mov r14,[rbp+0x348]                           
6657597 movups xmm0,[rax]                             
665759a movaps [rbp+0x340],xmm0                       
66575a1 test r14,r14                                  
66575a4 je 0x66585C9                                  ; -> loc_66585c9
```
// [V] Block J 0x66574f6..0x6657558: ecx=[rax+8]; if 0 → loc_6658445; lock inc dword [rcx+8] (AddRef); rbx=[rbp+0x348]; xmm0=[rax]; [rbp+0x340]=xmm0; if rbx==0 → loc_665845A; lock dec dword [rbx+8]; jne → loc_665845A; rax=[rbx]; rax=[rax]; rcx=rbx; call sub_eea6040 (stage-1 destroy); lock dec dword [rbx+0xC]; jne → loc_665845A; rax=[rbx]; rax=[rax+8]; rcx=rbx; call sub_eea6040 (stage-2 destroy); jmp loc_665845a. Same Release pattern with tail loc_665845A. [V] Block K 0x6657558..0x66575a6: rax=[rax]; rax=[rax+0x18]; r15=[rax]; if 0 → sub_665aee8; r15=[rsi]; rax=[rbp+0x320]; zero [rbp+0x340]; rcx=[rax+8]; if 0 → loc_66585B4; lock inc dword [rcx+8] (AddRef); r14=[rbp+0x348]; xmm0=[rax]; [rbp+0x340]=xmm0; if r14==0 → loc_66585C9 (cut at je). [V] Ref-count fields: [rcx+8] lock inc; [rbx+8] lock dec; [rbx+0xC] lock dec. [I] Epilogue still releasing refs — no case-exit yet; tails loc_6658445/loc_665845A/loc_66585B4/loc_66585C9 are shared Release epilogues. NOTE: the je at 0x66575a4 is a 6-byte rel32 to loc_66585c9, so real flow resumes at 0x66575aa; rdis's 0x66575a6 `(bad)` and 0x66575a8 `add [rax],al` are displacement-byte misdecodes. NEXT RVA: 0x66575a6

### Phase 8 — SkyAmbientSamples Release epilogue continues (objects 4-5) [V]
`0x66575a6..0x6657655` (40 instr requested; real code resumes at 0x66575aa because the phase-7 je at 0x66575a4 is a 6-byte rel32)
```
66575a6  (bad)                                         
66575a8  add [rax],al                                  
66575aa  lock dec dword ptr [r14+8]                    
66575af  jne 0x66585C9                                 ; -> loc_66585c9
66575b5  mov rax,[r14]                                 
66575b8  mov rax,[rax]                                 
66575bb  mov rcx,r14                                   
66575be  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66575c4  lock dec dword ptr [r14+0xC]                  
66575c9  jne 0x66585C9                                 ; -> loc_66585c9
66575cf  mov rax,[r14]                                 
66575d2  mov rax,[rax+8]                               
66575d6  mov rcx,r14                                   
66575d9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66575df  jmp 0x66585C9                                 ; -> loc_66585c9
66575e4  mov rax,[rax]                                 
66575e7  mov rax,[rax+0x18]                            
66575eb  mov r15,[rax]                                 
66575ee  test r15,r15                                  
66575f1  je 0x665B56E                                  ; -> sub_665b56e
66575f7  mov r15,[rsi]                                 
66575fa  mov rax,[rbp+0x320]                           
6657601  xorps xmm0,xmm0                               
6657604  movaps [rbp+0x340],xmm0                       
665760b  mov rcx,[rax+8]                               
665760f  test rcx,rcx                                  
6657612  je 0x66587CF                                  ; -> loc_66587cf
6657618  lock inc dword ptr [rcx+8]                    
665761c  mov r14,[rbp+0x348]                           
6657623  movups xmm0,[rax]                             
6657626  movaps [rbp+0x340],xmm0                       
665762d  test r14,r14                                  
6657630  je 0x66587E4                                  ; -> loc_66587e4
6657636  lock dec dword ptr [r14+8]                    
665763b  jne 0x66587E4                                 ; -> loc_66587e4
6657641  mov rax,[r14]                                 
6657644  mov rax,[rax]                                 
6657647  mov rcx,r14                                   
665764a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657650  lock dec dword ptr [r14+0xC]                  
```
// [V] Block K tail 0x66575aa..0x66575df (continuation of phase-7 Block K: test r14,r14 at 0x66575a1; je rel32 at 0x66575a4 → loc_66585c9 if zero; else): lock dec dword [r14+8]; jne → loc_66585c9 (refcount still >0); rax=[r14]; rax=[rax]; rcx=r14; call sub_eea6040 (stage-1 destroy); lock dec dword [r14+0xC]; jne → loc_66585c9; rax=[r14]; rax=[rax+8]; rcx=r14; call sub_eea6040 (stage-2 destroy); jmp loc_66585c9. [V] Block L 0x66575e4..0x6657655 (next object): rax=[rax]; rax=[rax+0x18]; r15=[rax]; if 0 → sub_665b56e; r15=[rsi]; rax=[rbp+0x320]; zero [rbp+0x340]; rcx=[rax+8]; if 0 → loc_66587CF; lock inc dword [rcx+8] (AddRef); r14=[rbp+0x348]; xmm0=[rax]; [rbp+0x340]=xmm0; if r14==0 → loc_66587E4; lock dec dword [r14+8]; jne → loc_66587E4; rax=[r14]; rax=[rax]; rcx=r14; call sub_eea6040 (stage-1 destroy); lock dec dword [r14+0xC] (cut at 0x6657650). [V] Lines 0x66575a6 `(bad)` and 0x66575a8 `add [rax],al` are rdis misdecodes of the 0x66575a4 je displacement bytes — not real instructions. [V] Ref-count fields: [rcx+8] lock inc; [r14+8] lock dec; [r14+0xC] lock dec. [I] Still in epilogue Release loops; tails loc_66585C9/loc_66587CF/loc_66587E4. No case-exit yet. NEXT RVA: 0x6657655

### Phase 9 — SkyAmbientSamples small-index insert path (Block M) [V]
`0x6657655..0x6657705` (40 instr)
```
6657655  jne 0x66587E4                                 ; -> loc_66587e4
665765b  mov rax,[r14]                                 
665765e  mov rax,[rax+8]                               
6657662  mov rcx,r14                                   
6657665  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
665766b  jmp 0x66587E4                                 ; -> loc_66587e4
6657670  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
6657677  mov rax,[rcx]                                 
665767a  mov rax,[rax+8]                               
665767e  mov rdx,rdi                                   
6657681  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657687  nop                                           
6657688  mov r15,rax                                   
665768b  test rax,rax                                  
665768e  jne short 0x665769C                           ; -> loc_665769c
6657690  mov rcx,rdi                                   
6657693  call 0x9BC830                                 ; -> sub_9bc830
6657698  nop                                           
6657699  xor r15d,r15d                                 
loc_665769c:  ; from 665768e
665769c  mov rax,[r12+0x50]                            
66576a1  mov [r15+r14+0x50],rax                        
66576a6  movups xmm0,[r12+0x40]                        
66576ac  movups [r15+r14+0x40],xmm0                    
66576b2  movups xmm0,[r12]                             
66576b7  movups xmm1,[r12+0x10]                        
66576bd  movups xmm2,[r12+0x20]                        
66576c3  movups xmm3,[r12+0x30]                        
66576c9  movups [r15+r14+0x30],xmm3                    
66576cf  movups [r15+r14+0x20],xmm2                    
66576d5  movups [r15+r14+0x10],xmm1                    
66576db  movups [r15+r14],xmm0                         
66576e0  cmp rbx,[rsi+0x158]                           
66576e7  je short 0x6657717                            ; -> loc_6657717
66576e9  add r14,r15                                   
66576ec  add r14,0x58                                  
66576f0  mov rdx,[rsi+0x150]                           
66576f7  mov r8,rbx                                    
66576fa  sub r8,rdx                                    
66576fd  mov rcx,r15                                   
6657700  call 0xEEC6DE0                                ; -> sub_eec6de0
```
// [V] Block L tail 0x6657655..0x6657670 (release stage-2 for object at r14): jne → loc_66587e4; rax=[r14]; rax=[rax+8]; rcx=r14; call sub_eea6040 (stage-2 destroy); jmp loc_66587e4. [V] Block M 0x6657670..0x6657705 (target of phase-2 `jb 0x6657670` — index < 0x2F/47): rcx = global [0x1233E1A8]; rax = [rcx]; rax = [rax+8]; rdx = rdi; call sub_eea6040 → r15 = return; if r15 != 0 → loc_665769c; else rcx = rdi; call 0x9BC830 (sub_9bc830); r15d = 0. loc_665769c: rax = [r12+0x50]; [r15 + r14 + 0x50] = rax; then 64-byte struct copy [r12+0x00..0x30] → [r15+r14+0x00..0x30] via 4 movups (0x00,0x10,0x20,0x30, written reverse-high-first). [V] cmp rbx,[rsi+0x158]; je short loc_6657717; else r14 += r15; r14 += 0x58; rdx = [rsi+0x150]; r8 = rbx - rdx; rcx = r15; call 0xEEC6DE0 (sub_eec6de0) [I] memmove/shift of entries. [I] r14 here is the stride-0x58 table offset (phase 2 rdi=index*0x58); r15 is hash/bucket base or 0. Phase ends at call 0xEEC6DE0 (0x6657700), next RVA 0x6657705. [?] whether the case ends at loc_6657717 or continues.

### Phase 10 — SkyAmbientSamples memmove + growable stride-0x58 buffer [V]
`0x6657705..0x66577c0` (40 instr)
```
6657705  mov r8,[rsi+0x158]                            
665770c  sub r8,rbx                                    
665770f  mov rcx,r14                                   
6657712  mov rdx,rbx                                   
6657715  jmp short 0x6657727                           ; -> loc_6657727
6657717  mov rdx,[rsi+0x150]                           
665771e  sub rbx,rdx                                   
6657721  mov rcx,r15                                   
6657724  mov r8,rbx                                    
loc_6657727:  ; from 6657715
6657727  call 0xEEC6DE0                                ; -> sub_eec6de0
665772c  mov rcx,[rsi+0x150]                           
6657733  test rcx,rcx                                  
6657736  je short 0x665776C                            ; -> loc_665776c
6657738  mov rdx,[rsi+0x160]                           
665773f  sub rdx,rcx                                   
6657742  cmp rdx,0x1000                                
6657749  jb short 0x6657767                            ; -> loc_6657767
665774b  mov rax,[rcx-8]                               
665774f  add rcx,0xFFFFFFFFFFFFFFF8                    
6657753  sub rcx,rax                                   
6657756  cmp rcx,0x20                                  
665775a jae 0x665D43A                                 ; -> sub_665d43a
6657760  add rdx,0x27                                  
6657764  mov rcx,rax                                   
loc_6657767:  ; from 6657749
6657767  call 0xE935700                                ; -> sub_e935700
loc_665776c:  ; from 6657736
665776c  mov [rsi+0x150],r15                           
6657773  imul rax,[rbp+0x1C8],0x58                     
665777b  add rax,r15                                   
665777e  mov [rsi+0x158],rax                           
6657785  add rdi,r15                                   
6657788 mov [rsi+0x160],rdi                           
665778f movzx r9d,byte ptr [rbp+0x540]                
6657797 mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
665779e mov rax,[rcx]                                 
66577a1 mov rax,[rax+0x10]                            
66577a5 mov edx,r9d                                   
66577a8 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66577ae nop                                           
66577af  mov qword ptr [rbp+0x348],0x4000              
66577ba mov eax,[rsi+0x158]                           
```
// [V] Block M tail 0x6657705..0x6657727: r8 = [rsi+0x158] - rbx; rcx = r14; rdx = rbx; jmp loc_6657727; at loc_6657717: rdx = [rsi+0x150]; rbx -= rdx; rcx = r15; r8 = rbx; then call sub_eec6de0 (sub_eec6de0) [I] memmove of remaining entries. [V] 0x665772c..0x6657767: rcx = [rsi+0x150] (buffer base); if 0 → loc_665776c; rdx = [rsi+0x160] - [rsi+0x150] (used size); if rdx < 0x1000 → loc_6657767; else rax = [rcx-8] (heap size header); rcx = (rcx - 8) - rax; if rcx >= 0x20 → sub_665d43a (heap-consistency check); rdx += 0x27; rcx = rax. [V] loc_6657767: call sub_e935700 [I] free(old buffer) when growing or slack. [V] loc_665776c: [rsi+0x150] = r15 (new base); rax = [rbp+0x1C8] * 0x58; [rsi+0x158] = rax + r15 (new cursor); rdi += r15; [rsi+0x160] = rdi (new end). [V] r9d = byte [rbp+0x540]; rcx = global [0x1233E1B0] (data_1233e1b0); rax = [rcx]; rax = [rax+0x10]; edx = r9d; call sub_eea6040 [I] same global-table entry call as phase 1, now with byte param. [V] [rbp+0x348] = 0x4000; eax = [rsi+0x158] (cut). [I] [rsi+0x150/0x158/0x160] = growable stride-0x58 sample table (base/cursor/end). NEXT RVA: 0x66577c0

### Phase 11 — SkyAmbientSamples table index + word array insert [V]
`0x66577c0..0x6657881` (40 instr)
```
66577c0  sub eax,[rsi+0x150]                           
66577c6  shr eax,3                                     
66577c9  imul eax,0xFFFF8BA3                           
66577cf  dec eax                                       
66577d1  mov [rbp+0x3EC],ax                            
66577d8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
66577df  mov rax,[rcx]                                 
66577e2  mov rax,[rax+0x10]                            
66577e6  mov dl,0x4A                                   
66577e8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66577ee  mov [rbp+0x540],al                            
66577f4  mov rdx,[rsi+0x8A8]                           
66577fb  cmp rdx,[rsi+0x8B0]                           
6657802  je short 0x6657812                            ; -> loc_6657812
6657804  mov [rdx],r13w                                
6657808  add qword ptr [rsi+0x8A8],2                   
6657810  jmp short 0x6657829                           ; -> loc_6657829
loc_6657812:  ; from 6657802
6657812  mov rcx,rsi                                   
6657815  add rcx,0x8A0                                 
665781c  lea r8,[rbp+0x1E0]                            
6657823  call 0x1EF6F90                                ; -> sub_1ef6f90
6657828  nop                                           
loc_6657829:  ; from 6657810
6657829  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
6657830  mov rax,[rcx]                                 
6657833 mov rax,[rax+0x10]                            
6657837 movzx edx,byte ptr [rbp+0x540]                
665783e call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657844 nop                                           
6657845 mov qword ptr [rbp+0x340],1                   
6657850 mov eax,[rsi+0x8A8]                           
6657856 sub eax,[rsi+0x8A0]                           
665785c shr eax,1                                     
665785e dec eax                                       
6657860 mov [rbp+0x350],ax                            
6657867 mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
665786e mov rax,[rcx]                                 
6657871 mov rax,[rax+0x10]                            
6657875 mov dl,0x4A                                   
6657877 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
665787d mov [rbp+0x540],al                            
```
// [V] 0x66577c0..0x66577d1: eax = [rsi+0x158] - [rsi+0x150] (used bytes of stride-0x58 table); eax >>= 3 (/8); eax *= 0xFFFF8BA3 (32-bit magic multiply); dec eax; [rbp+0x3EC] = ax (table-position index). [V] 0x66577d8..0x66577ee: rcx = global [0x1233E1B0] (data_1233e1b0); rax = [rcx]; rax = [rax+0x10]; dl = 0x4A; call sub_eea6040; [rbp+0x540] = al (save byte result — same global-table entry call pattern as phase 1). [V] 0x66577f4..0x6657810: rdx = [rsi+0x8A8]; if rdx == [rsi+0x8B0] → loc_6657812; else [rdx] = r13w (write word); [rsi+0x8A8] += 2; jmp loc_6657829. [V] loc_6657812: rcx = rsi + 0x8A0; lea r8, [rbp+0x1E0]; call sub_1ef6f90 (likely grow/insert for the word array). [V] loc_6657829: rcx = global [0x1233E1B0]; rax = [rcx]; rax = [rax+0x10]; edx = byte [rbp+0x540]; call sub_eea6040; [rbp+0x340] = 1; eax = [rsi+0x8A8] - [rsi+0x8A0]; eax >>= 1 (/2, word count); dec eax; [rbp+0x350] = ax (last word index); rcx = global [0x1233E1B0]; rax = [rcx]; rax = [rax+0x10]; dl = 0x4A; call sub_eea6040; [rbp+0x540] = al (cut at 0x665787d). [V] Fields: [rbp+0x3EC] (index), [rbp+0x540] (byte), [rbp+0x340] (=1), [rbp+0x350] (word index); [rsi+0x8A0]/[rsi+0x8A8]/[rsi+0x8B0] = word-array base/cursor/end (2-byte entries, r13w). [I] Second dynamic array (word entries) parallel to the stride-0x58 table. NEXT RVA: 0x6657881

### Phase 12 — SkyAmbientSamples 0xC8 insert + epilogue jump + Block N (index<14) [V]
`0x6657881..0x6657925` (40 instr)
```
6657881  add [rax],al                                  
6657883  mov rax,[rsi+8]                               
6657887  cmp rax,[rsi+0x10]                            
665788b  je short 0x66578AC                            ; -> loc_66578ac
665788d  lea rdx,[rbp+0x340]                           
6657894  mov r8d,0xC8                                  
665789a  mov rcx,rax                                   
665789d  call 0xEEC6EC0                                ; -> sub_eec6ec0
66578a2  add qword ptr [rsi+8],0xC8                    
66578aa  jmp short 0x66578BF                           ; -> loc_66578bf
loc_66578ac:  ; from 665788b
66578ac  lea r8,[rbp+0x340]                            
66578b3  mov rcx,rsi                                   
66578b6  mov rdx,rax                                   
66578b9  call 0x5ABA6D0                                ; -> sub_5aba6d0
66578be  nop                                           
loc_66578bf:  ; from 66578aa
66578bf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
66578c6 mov rax,[rcx]                                 
66578c9 mov rax,[rax+0x10]                            
66578cd movzx edx,byte ptr [rbp+0x540]                
66578d4 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66578da nop                                           
66578db jmp 0x665D154                                 ; -> sub_665d154
66578e0 mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
66578e7 mov rax,[rcx]                                 
66578ea mov rax,[rax+8]                               
66578ee mov rdx,r13                                   
66578f1 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66578f7 nop                                           
66578f8 mov rbx,rax                                   
66578fb test rax,rax                                  
66578fe jne short 0x665790C                           ; -> loc_665790c
6657900 mov rcx,[rbp+0x40]                            
6657904 call 0x9BC830                                 ; -> sub_9bc830
6657909 nop                                           
665790a xor ebx,ebx                                   
loc_665790c:  ; from 66578fe
665790c mov rax,[rbp+0x540]                           
6657913 lea r13,[rbx+rax]                             
6657917 lea rcx,[rbp+0x348]                           
665791e movups xmm0,[rcx]                             
6657921 movups xmm1,[rcx+0x10]                        
```
// [V] 0x6657881 `add [rax],al` (rax = [global [0x1233E1B0]+0x10] from phase-11 end; al = [rbp+0x540] byte). [V] 0x6657883..0x66578aa: rax = [rsi+8]; if rax != [rsi+0x10]: rdx = [rbp+0x340]; r8d = 0xC8 (200); rcx = rax; call sub_eec6ec0 [I] copy 0xC8 bytes from [rbp+0x340] to [rax]; [rsi+8] += 0xC8; jmp loc_66578bf. [V] loc_66578ac (rax == [rsi+0x10], full): r8 = [rbp+0x340]; rcx = rsi; rdx = rax; call sub_5aba6d0 [I] allocator (near sub_5aba5c0 operator new). [V] loc_66578bf: rcx = global [0x1233E1B0]; rax = [rcx]; rax = [rax+0x10]; edx = byte [rbp+0x540]; call sub_eea6040; **jmp sub_665d154** — likely function epilogue (case-exit on this path). [V] Block N 0x66578e0..0x6657925 (target of phase-2 `jb 0x66578E0` — index < 0xE/14): rcx = global [0x1233E1A8]; rax = [rcx]; rax = [rax+8]; rdx = r13; call sub_eea6040 → rbx = rax; if rbx != 0 → loc_665790c; else rcx = [rbp+0x40]; call sub_9bc830; ebx = 0. loc_665790c: rax = [rbp+0x540]; r13 = rbx + rax; rcx = [rbp+0x348]; movups xmm0 = [rcx]; xmm1 = [rcx+0x10] (cut at 0x6657921). [I] Two exits: sub_665d154 jump (epilogue) vs continued flow at loc_665790c — case not yet confirmed ended. NEXT RVA: 0x6657925

### Phase 13 — SkyAmbientSamples record write + loop setup [V]
`0x6657925..0x66579e4` (40 instr; lea r12,[rbx+rdi] at 0x66579e0 is 4 bytes, real resume 0x66579e4)
```
6657925  movups xmm2,[rcx+0x20]                        ; R a0+0x20
6657929  movups [rbx+rax+0x20],xmm2                    
665792e  movups [rbx+rax+0x10],xmm1                    
6657933  movups [rbx+rax],xmm0                         
6657937  xorps xmm0,xmm0                               
665793a  movups [rbx+rax+0x30],xmm0                    
665793f  test r14,r14                                  
6657942  je short 0x6657959                            ; -> loc_6657959
6657944  lock inc dword ptr [r14+8]                    
6657949  mov rdi,[rbp+0x378]                           
6657950  mov rax,[rbp+0x380]                           
6657957  jmp short 0x665795B                           ; -> loc_665795b
loc_6657959:  ; from 6657942
6657959  xor eax,eax                                   
loc_665795b:  ; from 6657957
665795b  mov [r13+0x30],rdi                            
665795f  mov [r13+0x38],rax                            
6657963  movlhps xmm6,xmm9                             
6657967  movups [r13+0x40],xmm6                        
665796c  shufps xmm7,xmm7,0x55                         
6657970  movss [r13+0x50],xmm7                         
6657976 lea rax,[rbp+0x348]                           
665797d movups xmm0,[rax+0x54]                        
6657981 movups [r13+0x54],xmm0                        
6657986 movlps [r13+0x64],xmm8                        
665798b movss [r13+0x6C],xmm10                        
6657991 lea rcx,[r13+0x70]                            
6657995 mov r8d,0xAD                                  
665799b lea rdx,[rbp+0x3B8]                           
66579a2 call 0xEEC6EC0                                ; -> sub_eec6ec0
66579a7 movlps [r13+0x120],xmm11                      
66579af mov [r13+0x128],r12                           
66579b6 mov r14,[rsi+0x540]                           
66579bd mov rdi,[rsi+0x548]                           
66579c4 cmp r15,rdi                                   
66579c7 je 0x6657C6B                                  ; -> loc_6657c6b
66579cd cmp r14,r15                                   
66579d0 je 0x6657B0B                                  ; -> loc_6657b0b
66579d6 xor edi,edi                                   
66579d8 xorps xmm6,xmm6                               
66579db jmp 0x6657AC9                                 ; -> loc_6657ac9
66579e0 lea r12,[rbx+rdi]                             
```
// [V] Continuation of loc_665790c (r13 = rbx + [rbp+0x540] = record ptr): 64-byte record init [r13+0x00..0x30] from xmm0/xmm1/xmm2 (xmm0=[rbp+0x348], xmm1=[rbp+0x358], xmm2=[rbp+0x368] per phase-12 end), [r13+0x30]=0; test r14,r14; if 0 → loc_6657959 (rax=0); else lock inc dword [r14+8] (AddRef); rdi=[rbp+0x378]; rax=[rbp+0x380]. loc_665795b: [r13+0x30]=rdi; [r13+0x38]=rax; movlhps xmm6,xmm9; [r13+0x40]=xmm6; shufps xmm7,xmm7,0x55; [r13+0x50]=xmm7; xmm0=[rbp+0x348+0x54]; [r13+0x54]=xmm0; [r13+0x64]=xmm8; [r13+0x6C]=xmm10; lea rcx,[r13+0x70]; r8d=0xAD (173); rdx=[rbp+0x3B8]; call sub_eec6ec0 [I] 173-byte copy [rbp+0x3B8]→[r13+0x70]; [r13+0x120]=xmm11; [r13+0x128]=r12. Record fields mirror Block F (0x66573c3) — same 0x130-stride record. [V] 0x66579b6..0x66579db: r14=[rsi+0x540]; rdi=[rsi+0x548]; if r15==rdi → loc_6657C6B; if r14==r15 → loc_6657B0B; else edi=0; xorps xmm6; jmp loc_6657AC9 (entry loop). [I] r15 = running index; [rsi+0x540]/[rsi+0x548] are table bounds — loop over entries until done. loc_66579e0 (jump target from 0x6657af5/0x6657aff) is the loop body head. NEXT RVA: 0x66579e4

### Phase 14 — SkyAmbientSamples entry-copy loop [V]
`0x66579e4..0x6657ad8` (40 instr)
```
66579e4  lea r13,[r14+rdi]                             
66579e8  mov rax,[r13+0x30]                            
66579ec  mov [r12+0x30],rax                            
66579f1  mov rax,[r13+0x38]                            
66579f5  mov [r12+0x38],rax                            
66579fa  movss xmm0,[r13+0x40]                         
6657a00  movss [r12+0x40],xmm0                         
6657a07  movss xmm0,[r13+0x44]                         
6657a0d  movss [r12+0x44],xmm0                         
6657a14  movss xmm0,[r13+0x48]                         
6657a1a  movss [r12+0x48],xmm0                         
6657a21  movss xmm0,[r13+0x4C]                         
6657a27  movss [r12+0x4C],xmm0                         
6657a2e  movss xmm0,[r13+0x50]                         
6657a34  movss [r12+0x50],xmm0                         
6657a3b  movups xmm0,[r13+0x54]                        
6657a40  movups [r12+0x54],xmm0                        
6657a46  movss xmm0,[r13+0x64]                         
6657a4c  movss [r12+0x64],xmm0                         
6657a53  movss xmm0,[r13+0x68]                         
6657a59  movss [r12+0x68],xmm0                         
6657a60  movss xmm0,[r13+0x6C]                         
6657a66  movss [r12+0x6C],xmm0                         
6657a6d  lea rcx,[r12+0x70]                            
6657a72  lea rdx,[r13+0x70]                            
6657a76  mov r8d,0xAD                                  
6657a7c  call 0xEEC6EC0                                ; -> sub_eec6ec0
6657a81  movss xmm0,[r13+0x120]                        
6657a8a  movss [r12+0x120],xmm0                        
6657a94  movss xmm0,[r13+0x124]                        
6657a9d  movss [r12+0x124],xmm0                        
6657aa7  mov rax,[r13+0x128]                           
6657aae  mov [r12+0x128],rax                           
6657ab6  add rdi,0x130                                 
6657abd  add r13,0x130                                 
6657ac4  cmp r13,r15                                   
6657ac7  je short 0x6657B04                            ; -> loc_6657b04
6657ac9  movups xmm0,[r14+rdi]                         
6657ace  movups xmm1,[r14+rdi+0x10]                    
6657ad4  movups xmm2,[r14+rdi+0x20]                    
```
// [V] Loop body (head at loc_6657ac9, entered from 0x66579db with edi=0; r13=r14+rdi = source record at stride-0x130 offset rdi, r12 = dest record at rbx+rdi per 0x66579e0): copies record fields [r13+0x30,0x38,0x40,0x44,0x48,0x4C,0x50,0x54,0x64,0x68,0x6C] → [r12+same]; lea rcx=[r12+0x70]; lea rdx=[r13+0x70]; r8d=0xAD (173); call sub_eec6ec0 [I] 173-byte copy [r13+0x70]→[r12+0x70]; [r12+0x120]=[r13+0x120]; [r12+0x124]=[r13+0x124]; [r12+0x128]=[r13+0x128]; rdi += 0x130; r13 += 0x130; cmp r13,r15; je short loc_6657b04 (loop exit when cursor r13 reaches end r15); else loop-top loc_6657ac9 loads next record. Full record copy = fields 0x30..0x128 (0x130 bytes total) — matches record size. [I] r14 = source table base [rsi+0x540]; r15 = end cursor; r12 = dest base (rbx + ...). Loop copies remaining entries after the newly written record. NEXT RVA: 0x6657ad8

### Phase 15 — SkyAmbientSamples loop-1 tail + loop-2 setup/body [V]
`0x6657ad8..0x6657bb8` (38 instr listed; movss xmm0,[r13+0x68] at 0x6657baf is 9 bytes → real resume 0x6657bb8)
```
6657ad8  and [rdi],cl                                  
6657adb  adc [rbx+rdi+0x20],edx                        
6657adf  movups [rbx+rdi+0x10],xmm1                    
6657ae4  movups [rbx+rdi],xmm0                         
6657ae8  movups [rbx+rdi+0x30],xmm6                    
6657aed  mov rax,[r14+rdi+0x38]                        
6657af2  test rax,rax                                  
6657af5  je 0x66579E0                                  ; -> sub_66579e0   (loop-1 back-edge)
6657afb  lock inc dword ptr [rax+8]                    
6657aff  jmp 0x66579E0                                  ; -> sub_66579e0
6657b04  mov rdi,[rsi+0x548]                           
6657b0b  cmp r15,rdi                                   
6657b0e  je 0x6657DA4                                  ; -> loc_6657da4   (likely case exit)
6657b14  mov rax,[rbp+0x540]                           
6657b1b  lea r14,[rax+rbx]                             
6657b1f add r14,0x130                                 
6657b26  xor r12d,r12d                                 
6657b29  xorps xmm6,xmm6                               
6657b2c  jmp 0x6657C2C                                 ; -> loc_6657c2c
6657b31  nop [rax+rax]                                 
loc_6657b40:  ; from 6657c5c, 6657c66
6657b40  lea r13,[r15+r12]                             
6657b44  mov rax,[r13+0x30]                            
6657b48  mov [r14+r12+0x30],rax                        
6657b4d mov rax,[r13+0x38]                            
6657b51 mov [r14+r12+0x38],rax                        
6657b56 movss xmm0,[r13+0x40]                         
6657b5c movss [r14+r12+0x40],xmm0                     
6657b63 movss xmm0,[r13+0x44]                         
6657b69 movss [r14+r12+0x44],xmm0                     
6657b70 movss xmm0,[r13+0x48]                         
6657b76 movss [r14+r12+0x48],xmm0                     
6657b7d movss xmm0,[r13+0x4C]                         
6657b83 movss [r14+r12+0x4C],xmm0                     
6657b8a movss xmm0,[r13+0x50]                         
6657b90 movss [r14+r12+0x50],xmm0                     
6657b97 movups xmm0,[r13+0x54]                        
6657b9c movups [r14+r12+0x54],xmm0                    
6657ba2 movss xmm0,[r13+0x64]                         
6657ba8 movss [r14+r12+0x64],xmm0                     
6657baf movss xmm0,[r13+0x68]                         
```
// [V] Loop-1 tail 0x6657ad8..0x6657aff: and [rdi],cl; adc [rbx+rdi+0x20],edx; [rbx+rdi+0x10]=xmm1; [rbx+rdi]=xmm0; [rbx+rdi+0x30]=xmm6; rax=[r14+rdi+0x38]; if rax==0 → loop head loc_66579e0; else lock inc dword [rax+8] (AddRef the +0x38 ref); jmp loc_66579e0. [V] 0x6657b04..0x6657b2c: rdi=[rsi+0x548]; if r15==rdi → loc_6657DA4 (likely case exit); r14=[rbp+0x540]+rbx; r14+=0x130; r12d=0; xorps xmm6; jmp loc_6657C2C. [V] Loop-2 body head loc_6657b40 (back-edges from 0x6657c5c/0x6657c66): r13=r15+r12; copy record fields [r13+0x30,0x38,0x40,0x44,0x48,0x4C,0x50,0x54,0x64] → [r14+r12+same] (cut at movss xmm0,[r13+0x68]). Mirrors loop-1's record copy — compacting/shifting entries in the stride-0x130 table. NEXT RVA: 0x6657bb8

### Phase 16 — SkyAmbientSamples loop-2 tail + loop-3 head [V]
`0x6657bb8..0x6657c95` (40 instr)
```
6657bb8  adc [rsi+0x68],eax                            
6657bbc  movss xmm0,[r13+0x6C]                         
6657bc2  movss [r14+r12+0x6C],xmm0                     
6657bc9  lea rcx,[r14+r12]                             
6657bcd  add rcx,0x70                                  
6657bd1  lea rdx,[r13+0x70]                            
6657bd5  mov r8d,0xAD                                  
6657bdb  call 0xEEC6EC0                                ; -> sub_eec6ec0
6657be0  movss xmm0,[r13+0x120]                        
6657be9  movss [r14+r12+0x120],xmm0                    
6657bf3  movss xmm0,[r13+0x124]                        
6657bfc  movss [r14+r12+0x124],xmm0                    
6657c06  mov rax,[r13+0x128]                           
6657c0d  mov [r14+r12+0x128],rax                       
6657c15  add r12,0x130                                 
6657c1c  add r13,0x130                                 
6657c23  cmp r13,rdi                                   
6657c26  je 0x6657DA4                                  ; -> loc_6657da4  (loop-2 exit)
6657c2c  movups xmm0,[r15+r12]                         
6657c31  movups xmm1,[r15+r12+0x10]                    
6657c37  movups xmm2,[r15+r12+0x20]                    
6657c3d  movups [r14+r12+0x20],xmm2                    
6657c43  movups [r14+r12+0x10],xmm1                    
6657c49  movups [r14+r12],xmm0                         
6657c4e  movups [r14+r12+0x30],xmm6                    
6657c54  mov rax,[r15+r12+0x38]                        
6657c59  test rax,rax                                  
6657c5c  je 0x6657B40                                  ; -> sub_6657b40 (loop-2 body)
6657c62  lock inc dword ptr [rax+8]                    
6657c66  jmp 0x6657B40                                  ; -> sub_6657b40
6657c6b  cmp r14,r15                                   
6657c6e  je 0x6657DAB                                  ; -> loc_6657dab
6657c74  xor edi,edi                                   
6657c76  xorps xmm6,xmm6                               
6657c79  jmp 0x6657D69                                  ; -> loc_6657d69
6657c7e  xchg ax,ax                                    
loc_6657c80:  ; from 6657d95, 6657d9f
6657c80  lea r13,[rbx+rdi]                             
6657c84  lea r12,[r14+rdi]                             
6657c88  mov rax,[r12+0x30]                            
6657c8d  mov [r13+0x30],rax                            
```
// [V] Loop-2 tail 0x6657bb8..0x6657c26: adc [rsi+0x68],eax (?); [r14+r12+0x6C]=[r13+0x6C]; lea rcx=[r14+r12+0x70]; lea rdx=[r13+0x70]; r8d=0xAD (173); call sub_eec6ec0; [r14+r12+0x120]=[r13+0x120]; +0x124; [r14+r12+0x128]=[r13+0x128]; r12+=0x130; r13+=0x130; cmp r13,rdi ([rsi+0x548]); je loc_6657DA4 (loop-2 exit). [V] Loop-2 head 0x6657c2c..0x6657c66: movups [r14+r12+0x00,0x10,0x20]=[r15+r12+same]; [r14+r12+0x30]=xmm6(=0); rax=[r15+r12+0x38]; if rax==0 → loc_6657b40; else lock inc dword [rax+8]; jmp loc_6657b40 (field-copy body at loc_6657b40: copies +0x30 onwards incl. +0x38 pointer, then 173-byte +0x70 copy, +0x120/0x124/0x128, advance by 0x130, loop until r13==rdi → loc_6657DA4). [V] 0x6657c6b (separate block): cmp r14,r15; if equal → loc_6657DAB; else edi=0; xorps xmm6; jmp loc_6657D69 (loop-3 head?). [V] Block at loc_6657c80 (from 0x6657d95/0x6657d9f): r13=rbx+rdi; r12=r14+rdi; [r13+0x30]=[r12+0x30] (cut at 0x6657c8d) — record copy at stride rdi, likely loop-3 body. [I] Case still open: exits loc_6657DA4 / loc_6657DAB seen; loop-3 at loc_6657D69/loc_6657c80. NEXT RVA: 0x6657c95

### Phase 17 — SkyAmbientSamples loop-3 body (record copy) [V]
`0x6657c95..0x6657d88` (40 instr)
```
6657c95  cmp [rcx-0x77],cl                             ; R a0-0x77
6657c98  cmp r11b,r14b                                 
6657c9b  movups xmm0,[r12+0x40]                        
6657ca1  movss [r13+0x40],xmm0                         
6657ca7  movss xmm0,[r12+0x44]                         
6657cae  movss [r13+0x44],xmm0                         
6657cb4  movss xmm0,[r12+0x48]                         
6657cbb  movss [r13+0x48],xmm0                         
6657cc1  movss xmm0,[r12+0x4C]                         
6657cc8  movss [r13+0x4C],xmm0                         
6657cce  movss xmm0,[r12+0x50]                         
6657cd5  movss [r13+0x50],xmm0                         
6657cdb  movups xmm0,[r12+0x54]                        
6657ce1  movups [r13+0x54],xmm0                        
6657ce6  movss xmm0,[r12+0x64]                         
6657ced  movss [r13+0x64],xmm0                         
6657cf3  movss xmm0,[r12+0x68]                         
6657cfa  movss [r13+0x68],xmm0                         
6657d00  movss xmm0,[r12+0x6C]                         
6657d07  movss [r13+0x6C],xmm0                         
6657d0d  lea rcx,[r13+0x70]                            
6657d11  lea rdx,[r12+0x70]                            
6657d16  mov r8d,0xAD                                  
6657d1c  call 0xEEC6EC0                                ; -> sub_eec6ec0
6657d21  movss xmm0,[r12+0x120]                        
6657d2b  movss [r13+0x120],xmm0                        
6657d34  movss xmm0,[r12+0x124]                        
6657d3e  movss [r13+0x124],xmm0                        
6657d47  mov rax,[r12+0x128]                           
6657d4f  mov [r13+0x128],rax                           
6657d56  add rdi,0x130                                 
6657d5d  add r12,0x130                                 
6657d64  cmp r12,r15                                   
6657d67  je short 0x6657DA4                            ; -> loc_6657da4 (loop-3 exit)
6657d69  movups xmm0,[r14+rdi]                         
6657d6e  movups xmm1,[r14+rdi+0x10]                    
6657d74  movups xmm2,[r14+rdi+0x20]                    
6657d7a  movups [rbx+rdi+0x20],xmm2                    
6657d7f  movups [rbx+rdi+0x10],xmm1                    
6657d84  movups [rbx+rdi],xmm0                         
```
// [V] 0x6657c95..0x6657c98: cmp [rcx-0x77],cl (R a0-0x77); cmp r11b,r14b — tiny flag compares (loop-3 entry guards, [?] meaning). [V] Loop-3 body: r13 = dest (rbx + stride), r12 = source (r14 + stride); copy fields [r12+0x40,0x44,0x48,0x4C,0x50,0x54,0x64,0x68,0x6C] → [r13+same]; lea rcx=[r13+0x70]; lea rdx=[r12+0x70]; r8d=0xAD (173); call sub_eec6ec0 [I] 173-byte copy [r12+0x70]→[r13+0x70]; [r13+0x120]=[r12+0x120]; +0x124; [r13+0x128]=[r12+0x128]; rdi+=0x130; r12+=0x130; cmp r12,r15; je short loc_6657DA4 (loop-3 exit when source cursor reaches r15/end). [V] Loop-3 head 0x6657d69 (from 0x6657c79): movups [rbx+rdi+0x20,0x10,0x00] = [r14+rdi+0x00,0x10,0x20] (cut at movups [rbx+rdi],xmm0; presumably +0x30=xmm6 follows, then back-edge to 0x6657d69). [I] Loop-3 = third record-copy loop (source [r14+rdi] base, dest [rbx+rdi]) — compaction pass. Exits: loc_6657DA4 (loops 2 & 3), loc_6657DAB (0x6657c6b). NEXT RVA: 0x6657d88

### Phase 18 — SkyAmbientSamples epilogue: release all entries + heap shrink [V]
`0x6657d88..0x6657e31` (40 instr)
```
6657d88  movups [rbx+rdi+0x30],xmm6                    
6657d8d  mov rax,[r14+rdi+0x38]                        
6657d92  test rax,rax                                  
6657d95  je 0x6657C80                                  ; -> sub_6657c80   (loop-3 back edge)
6657d9b  lock inc dword ptr [rax+8]                    
6657d9f  jmp 0x6657C80                                  ; -> sub_6657c80
6657da4  mov r14,[rsi+0x540]                           
6657dab  test r14,r14                                  
6657dae  mov r13,[rbp-0x28]                            
6657db2  je 0x6657E52                                  ; -> loc_6657e52
6657db8  mov rdi,[rsi+0x548]                           
6657dbf  cmp r14,rdi                                   
6657dc2  jne short 0x6657DDC                           ; -> loc_6657ddc
6657dc4  jmp short 0x6657E1B                           ; -> loc_6657e1b
6657dc6  nop [rax+rax]                                 
loc_6657dd0:  ; from 6657de3, 6657dea, 6657e00, 6657e12
6657dd0  add r14,0x130                                 
6657dd7  cmp r14,rdi                                   
6657dda  je short 0x6657E14                            ; -> loc_6657e14
loc_6657ddc:  ; from 6657dc2
6657ddc  mov r15,[r14+0x38]                            
6657de0  test r15,r15                                  
6657de3  je short 0x6657DD0                            ; -> loc_6657dd0
6657de5  lock dec dword ptr [r15+8]                    
6657dea  jne short 0x6657DD0                           ; -> loc_6657dd0
6657dec  mov rax,[r15]                                 
6657def  mov rax,[rax]                                 
6657df2  mov rcx,r15                                   
6657df5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657dfb  lock dec dword ptr [r15+0xC]                  
6657e00  jne short 0x6657DD0                           ; -> loc_6657dd0
6657e02  mov rax,[r15]                                 
6657e05  mov rax,[rax+8]                               
6657e09  mov rcx,r15                                   
6657e0c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657e12  jmp short 0x6657DD0                           ; -> loc_6657dd0
loc_6657e14:  ; from 6657dda
6657e14  mov r14,[rsi+0x540]                           
loc_6657e1b:  ; from 6657dc4
6657e1b  mov rdx,[rsi+0x550]                           
6657e22  sub rdx,r14                                   
6657e25  cmp rdx,0x1000                                
6657e2c  jb short 0x6657E4A                            ; -> loc_6657e4a
6657e2e  mov rax,[r14-8]                               
```
// [V] Loop-3 tail: [rbx+rdi+0x30]=xmm6; rax=[r14+rdi+0x38]; if 0 → loc_6657c80 (loop-3 body, no ref); else lock inc dword [rax+8] (AddRef entry's +0x38 ref); jmp loc_6657c80. [V] Epilogue 0x6657da4..: r14=[rsi+0x540] (table base); r13=[rbp-0x28]; if r14==0 → loc_6657E52; rdi=[rsi+0x548] (end); if r14==rdi → loc_6657E1B; else loc_6657ddc: r15=[r14+0x38] (entry ref); if 0 → next; lock dec dword [r15+8]; if !=0 → next (loc_6657dd0, r14+=0x130); else two-stage destroy: call sub_eea6040; lock dec dword [r15+0xC]; if !=0 → next; call sub_eea6040 (free); loop until r14==rdi → loc_6657e14 (r14=[rsi+0x540] again). [V] 0x6657e1b..0x6657e2e: rdx=[rsi+0x550]-[rsi+0x540] (allocated size); if rdx<0x1000 → loc_6657e4a; else rax=[r14-8] (heap size header) (cut at 0x6657e2e). [V] Fields: [r14+0x38] entry ref (lock dec [+8], [+0xC]); heap buffer [rsi+0x540]/[rsi+0x548]/[rsi+0x550] = base/end/alloc-limit?; [rsi+0x150]/0x158/0x160 the stride-0x58 buffer. [I] This releases every AddRef taken in the case ([r12+8] at 0x665714e, all entry +0x38 refs) — final case wind-down before exit. NEXT RVA: 0x6657e31

### Phase 19 — SkyAmbientCases epilogue tail: buffer free + cursors + final counts [V]
`0x6657e31..0x6657ede` (40 instr listed; last insn `movzx eax,word ptr [rbp+0x1C8]` at 0x6657ede spans into branch target 0x6657ef2 — [?] exact split)
```
6657e31  clc                                           
6657e32  add r14,0xFFFFFFFFFFFFFFF8                    
6657e36  sub r14,rax                                   
6657e39  cmp r14,0x20                                  
6657e3d  jae 0x665D43A                                 ; -> sub_665d43a
6657e43  add rdx,0x27                                  
6657e47  mov r14,rax                                   
6657e4a  mov rcx,r14                                   
6657e4d  call 0xE935700                                ; -> sub_e935700
6657e52  mov [rsi+0x540],rbx                           
6657e59  imul rax,r13,0x130                            
6657e60  add rax,rbx                                   
6657e63  mov [rsi+0x548],rax                           
6657e6a  mov rax,[rbp+0x40]                            
6657e6e  add rax,rbx                                   
6657e71  mov [rsi+0x550],rax                           
6657e78  movzx ebx,byte ptr [rbp+0x48]                 
6657e7c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
6657e83  mov rax,[rcx]                                 
6657e86  mov rax,[rax+0x10]                            
6657e8a  mov edx,ebx                                   
6657e8c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657e92  nop                                           
6657e93  mov eax,[rsi+0x548]                           
6657e99  sub eax,[rsi+0x540]                           
6657e9f  shr eax,4                                     
6657ea2  imul eax,0xFFFFCA1B                           
6657ea8  dec eax                                       
6657eaa  mov [rbp+0xA8],ax                             
6657eb1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
6657eb8  mov rax,[rcx]                                 
6657ebb  mov rax,[rax+0x10]                            
6657ebf  mov dl,0x4A                                   
6657ec1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657ec7  nop                                           
6657ec8  mov [rbp+0x540],al                            
6657ece  mov rdx,[rsi+0x8A8]                           
6657ed5  cmp rdx,[rsi+0x8B0]                           
6657edc  je short 0x6657EF2                            ; -> loc_6657ef2
6657ede  movzx eax,word ptr [rbp+0x1C8]                
```
// [V] 0x6657e31..0x6657e4d: clc; r14 += 0xFFFFFFFFFFFFFFF8 (-8); r14 -= rax; if r14 >= 0x20 → sub_665d43a (heap check); rdx += 0x27; r14 = rax; rcx = r14; call sub_e935700 [I] free(final buffer). [V] 0x6657e52..0x6657e78: [rsi+0x540] = rbx (new base); rax = r13 * 0x130 + rbx → [rsi+0x548] (end); rax = [rbp+0x40] + rbx → [rsi+0x550] (alloc limit); ebx = byte [rbp+0x48]. [V] 0x6657e7c..0x6657ec8: rcx = global [0x1233E1B0]; rax = [rcx]; rax = [rax+0x10]; edx = ebx; call sub_eea6040; eax = [rsi+0x548] - [rsi+0x540] (used bytes); eax >>= 4 (/16); eax *= 0xFFFFCA1B (magic); dec eax; [rbp+0xA8] = ax (entry count index); rcx = global [0x1233E1B0]; rax = [rcx]; rax = [rax+0x10]; dl = 0x4A; call sub_eea6040; [rbp+0x540] = al. [V] 0x6657ece..0x6657ede: rdx = [rsi+0x8A8]; cmp [rsi+0x8B0]; if equal → loc_6657ef2; else movzx eax,word [rbp+0x1C8] (cut, continues at 0x6657ef2). [V] Fields: [rsi+0x540/0x548/0x550] (base/end/limit), [rbp+0xA8] (count index), [rbp+0x540] (byte), [rbp+0x48] (byte). NEXT RVA: 0x6657ef2 (branch target of je at 0x6657edc)

### Phase 20 — SkyAmbientSamples word-array grow + 0xC8 record write [V]
`0x6657ef2..0x6657fa1` (40 instr)
```
6657ef2  mov rcx,rsi                                   
6657ef5  add rcx,0x8A0                                 
6657efc  lea r8,[rbp+0x340]                            
6657f03  call 0x1EF6F90                                ; -> sub_1ef6f90
6657f08  nop                                           
6657f09  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
6657f10 mov rax,[rcx]                                 
6657f13 mov rax,[rax+0x10]                            
6657f17 movzx edx,byte ptr [rbp+0x540]                
6657f1e call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657f24 nop                                           
6657f25 mov rax,0x1000000001                          
6657f2f mov [rbp+0x50],rax                            
6657f33 mov eax,[rsi+0x8A8]                           
6657f39 sub eax,[rsi+0x8A0]                           
6657f3f shr eax,1                                     
6657f41 dec eax                                       
6657f43 mov [rbp+0x60],ax                             
6657f47 mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
6657f4e mov rax,[rcx]                                 
6657f51 mov rax,[rax+0x10]                            
6657f55 mov dl,0x4A                                   
6657f57 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657f5d nop                                           
6657f5e mov [rbp+0x540],al                            
6657f64 mov rax,[rsi+8]                               
6657f68 cmp rax,[rsi+0x10]                            
6657f6c je short 0x6657F8A                            ; -> loc_6657f8a
6657f6e lea rdx,[rbp+0x50]                            
6657f72 mov r8d,0xC8                                  
6657f78 mov rcx,rax                                   
6657f7b call 0xEEC6EC0                                ; -> sub_eec6ec0
6657f80 add qword ptr [rsi+8],0xC8                    
6657f88 jmp short 0x6657F9A                           ; -> loc_6657f9a
loc_6657f8a:  ; from 6657f6c
6657f8a lea r8,[rbp+0x50]                             
6657f8e mov rcx,rsi                                   
6657f91 mov rdx,rax                                   
6657f94 call 0x5ABA6D0                                ; -> sub_5aba6d0
6657f99 nop                                           
loc_6657f9a:  ; from 6657f88
6657f9a mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```
// [V] 0x6657ef2..0x6657f08: rcx = rsi + 0x8A0; lea r8, [rbp+0x340]; call sub_1ef6f90 [I] word-array grow/insert helper (rdx = [rsi+0x8A8] cursor from phase 19). [V] 0x6657f09..0x6657f24: rcx = global [0x1233E1B0]; rax = [rcx]; rax = [rax+0x10]; edx = byte [rbp+0x540]; call sub_eea6040 (global entry call, 4th time). [V] 0x6657f25..0x6657f43: [rbp+0x50] = 0x1000000001 (record template qword); eax = [rsi+0x8A8] - [rsi+0x8A0]; >>= 1 (/2 word count); dec; [rbp+0x60] = ax (last word index). [V] 0x6657f47..0x6657f5e: rcx = global [0x1233E1B0]; rax = [rcx]; rax = [rax+0x10]; dl = 0x4A; call sub_eea6040 (5th time); [rbp+0x540] = al. [V] 0x6657f64..0x6657f88: rax = [rsi+8]; if rax != [rsi+0x10]: rdx = [rbp+0x50]; r8d = 0xC8 (200); rcx = rax; call sub_eec6ec0 [I] copy 0xC8 bytes from [rbp+0x50] to [rsi+8] slot; [rsi+8] += 0xC8; jmp loc_6657f9a. [V] loc_6657f8a (full): r8 = [rbp+0x50]; rcx = rsi; rdx = rax; call sub_5aba6d0 [I] allocate grow slot. [V] loc_6657f9a: rcx = global [0x1233E1B0] (cut at 0x6657f9a). [I] Third table: stride-0xC8 records at [rsi+8]..[rsi+0x10] — another record written per case. Case continues past loc_6657f9a. NEXT RVA: 0x6657fa1

### Phase 21 — SkyAmbientSamples final Release + case exit (jmp sub_665d124) [V]
`0x6657fa1..0x665803c` (40 instr)
```
6657fa1  mov rax,[rcx]                                 ; R a0+0x0
6657fa4  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
6657fa8  movzx edx,byte ptr [rbp+0x540]                
6657faf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657fb5  nop                                           
6657fb6  mov rsi,[rbp+0x380]                           
6657fbd  test rsi,rsi                                  
6657fc0  je short 0x6657FED                            ; -> loc_6657fed
6657fc2  lock dec dword ptr [rsi+8]                    
6657fc6  jne short 0x6657FED                           ; -> loc_6657fed
6657fc8  mov rax,[rsi]                                 
6657fcb  mov rax,[rax]                                 
6657fce  mov rcx,rsi                                   
6657fd1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657fd7  lock dec dword ptr [rsi+0xC]                  
6657fdb  jne short 0x6657FED                           ; -> loc_6657fed
6657fdd  mov rax,[rsi]                                 
6657fe0  mov rax,[rax+8]                               
6657fe4  mov rcx,rsi                                   
6657fe7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_6657fed:  ; from 6657fc0, 6657fc6, 6657fdb
6657fed  mov rsi,[rbp+0x218]                           
6657ff4  jmp 0x665D124                                 ; -> sub_665d124   (function epilogue — case exit)
6657ff9  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
6658000 mov rax,[rcx]                                 
6658003 mov rax,[rax+8]                               
6658007 mov rdx,[rbp+0x540]                           
665800e call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6658014 nop                                           
6658015 mov rbx,rax                                   
6658018 test rax,rax                                  
665801b jne short 0x665802C                           ; -> loc_665802c
665801d mov rcx,[rbp+0x540]                           
6658024 call 0x9BC830                                 ; -> sub_9bc830
6658029 nop                                           
665802a xor ebx,ebx                                   
loc_665802c:  ; from 665801b
665802c lea rax,[rbx+rdi]                             
6658030 xorps xmm0,xmm0                               
6658033 movups [rbx+rdi],xmm0                         
6658037 test r12,r12                                  
665803a je short 0x6658052                            ; -> loc_6658052
```
// [V] 0x6657fa1..0x6657fb5: rax = [rcx]; rax = [rax+0x10]; edx = byte [rbp+0x540]; call sub_eea6040 (6th time; rcx = global [0x1233E1B0] carried from phase 20). [V] 0x6657fb6..0x6657fe7: rsi = [rbp+0x380]; if 0 → loc_6657fed; lock dec dword [rsi+8]; if !=0 → loc_6657fed; else rax=[rsi]; rax=[rax]; rcx=rsi; call sub_eea6040 (stage-1 destroy); lock dec dword [rsi+0xC]; if !=0 → loc_6657fed; rax=[rsi]; rax=[rax+8]; rcx=rsi; call sub_eea6040 (stage-2 destroy/free). Release of the [rbp+0x380] ref. [V] loc_6657fed: rsi = [rbp+0x218]; **jmp sub_665d124** — shared function epilogue: SKYAMBIENTSAMPLES CASE ENDS HERE (0x6657ff4). [V] 0x6657ff9..0x665803a (UNREACHED linearly — follows unconditional jmp; [?] dead code or separate cold path): rcx = global [0x1233E1A8]; rax=[rcx]; rax=[rax+8]; rdx=[rbp+0x540]; call sub_eea6040 → rbx=rax; if rbx!=0 → loc_665802c; else rcx=[rbp+0x540]; call sub_9bc830; ebx=0. loc_665802c: rax=rbx+rdi; [rbx+rdi]=xmm0(0); test r12,r12; je loc_6658052 (cut). [I] loc_665802c is also a jump target from phase 5 (0x66573be `jmp 0x665802C`) — shared zero-record join; nothing here branches back into SkyAmbientSamples flow. [V] Fields released: [rsi+8], [rsi+0xC]. Case complete: all refs taken in the case ([r12+8]@0x665714e, +0x38 entry refs in loops, [rbp+0x380]) are Released; buffers freed via sub_e935700; exit via sub_665d124.
### UNIT U-SK3 SUB-TASK COMPLETE — SkyAmbientSamples (0x665708b)
Phases 1-21 written (0x665708b..0x665803c, instruction-complete through every block; case exits only via jmp sub_665d124 at 0x6657ff4). Residual: unreached block 0x6657ff9.. (dead after unconditional jmp, not part of case flow).
NEXT: VolumetricFog case at 0x66569b1 (not started).
NEXT RVA: 0x66569b1

### Phase 22 — VolumetricFog entry: alloc + zero-init + global count call [V]
`0x66569b1..0x6656a99` (40 instr)
```
66569b1  lea r12,[rbp+0x1E4]                           
66569b8  mov ecx,0x9D0                                 
66569bd  add rcx,[rsi+0x10]                            
66569c1  mov rax,[rdi+0x54]                            
66569c5  mov [rbp+0x234],rax                           
66569cc  movups xmm0,[rdi+0x44]                        
66569d0  movups [rbp+0x224],xmm0                       
66569d7  movups xmm0,[rdi+4]                           
66569db  movups xmm1,[rdi+0x14]                        
66569df  movups xmm2,[rdi+0x24]                        
66569e3  movups xmm3,[rdi+0x34]                        
66569e7  movups [rbp+0x214],xmm3                       
66569ee  movups [rbp+0x204],xmm2                       
66569f5  movups [rbp+0x1F4],xmm1                       
66569fc  movups [rbp+0x1E4],xmm0                       
6656a03  movzx r13d,word ptr [rdi]                     
6656a07  mov [rbp+0x1E0],r13w                          
6656a0f  call 0x5ABA5C0                                ; -> sub_5aba5c0
6656a14  mov rsi,rax                                   
6656a17  xorps xmm0,xmm0                               
6656a1a  movaps [rbp+0x3F0],xmm0                       
6656a21  movaps [rbp+0x3E0],xmm0                       
6656a28  movaps [rbp+0x3D0],xmm0                       
6656a2f  movaps [rbp+0x3C0],xmm0                       
6656a36  movaps [rbp+0x3B0],xmm0                       
6656a3d  movaps [rbp+0x3A0],xmm0                       
6656a44 movaps [rbp+0x390],xmm0                       
6656a4b movaps [rbp+0x380],xmm0                       
6656a52 movaps [rbp+0x370],xmm0                       
6656a59 movaps [rbp+0x360],xmm0                       
6656a60 movaps [rbp+0x350],xmm0                       
6656a67 movaps [rbp+0x340],xmm0                       
6656a6e mov qword ptr [rbp+0x400],0                   
6656a79 mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
6656a80 mov rax,[rcx]                                 
6656a83 mov rax,[rax+0x10]                            
6656a87 mov dl,0x4A                                   
6656a89 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6656a8f mov r9d,eax                                   
6656a92 mov rbx,[rsi+0x158]                           ; R ret@5aba5c0+0x158
```
// [V] 0x66569b1..0x6656a0f: r12 = &[rbp+0x1E4]; ecx = 0x9D0 + [rsi+0x10] (alloc size); rax = [rdi+0x54]; [rbp+0x234] = rax; movups [rdi+0x44]→[rbp+0x224]; [rdi+4],[rdi+0x14],[rdi+0x24],[rdi+0x34] → xmm0..3 → [rbp+0x224],[rbp+0x214],[rbp+0x204],[rbp+0x1F4],[rbp+0x1E4] (note: xmm0=[rdi+0x44] stored to [rbp+0x224] AND xmm0=[rdi+4] stored to [rbp+0x1E4] — xmm0 reused); r13d = movzx word [rdi]; [rbp+0x1E0] = r13w; call sub_5aba5c0 (operator new, size rcx). [V] 0x6656a14..0x6656a6e: rsi = rax (new buffer); zero-init 13 movaps + qword at [rbp+0x340..0x400] (216-byte scratch, same as SkyAmbientSamples phase 1). [V] 0x6656a79..0x6656a92: rcx = global [0x1233E1B0] (data_1233e1b0); rax = [rcx]; rax = [rax+0x10]; dl = 0x4A (74); call sub_eea6040; r9d = eax (count); rbx = [rsi+0x158] (new-buffer field). [I] VolumetricFog entry mirrors SkyAmbientSamples entry (same 0x9D0 alloc, same 216-byte zero-init, same global dl=0x4A count call); rdi = visitor's sky object (fields +4,+0x14,+0x24,+0x34,+0x44,+0x54 copied), rsi = new fog buffer. NEXT RVA: 0x6656a99

### Phase 23 — VolumetricFog stride-0x58 insert OR LegacyCubemap string path [V]
`0x6656a99..0x6656b81` (40 instr)
```
6656a99  cmp rbx,[rsi+0x160]                           
6656aa0  je 0x6657173                                  ; -> loc_6657173
6656aa6  mov rax,[r12+0x50]                            
6656aab  mov [rbx+0x50],rax                            
6656aaf  movups xmm0,[r12+0x40]                        
6656ab5  movups [rbx+0x40],xmm0                        
6656ab9  movups xmm0,[r12]                             
6656abe  movups xmm1,[r12+0x10]                        
6656ac4  movups xmm2,[r12+0x20]                        
6656aca  movups xmm3,[r12+0x30]                        
6656ad0  movups [rbx+0x30],xmm3                        
6656ad4  movups [rbx+0x20],xmm2                        
6656ad8  movups [rbx+0x10],xmm1                        
6656adc  movups [rbx],xmm0                             
6656adf  add qword ptr [rsi+0x158],0x58                
6656ae7  jmp 0x6657797                                 ; -> loc_6657797
6656aec  movaps [rbp+0x340],xmm0                       
6656af3  lea rax,[0xF57DBCE]                           ; [data_f57dbce] "LegacyCubemap"
6656afa  mov [rbp+0x1E0],rax                           
6656b01  mov qword ptr [rbp+0x1E8],0xD                 
6656b0c  lea rax,[rbp+0x340]                           
6656b13  mov [rsp+0x28],rax                            
6656b18  lea rax,[rbp+0x1E0]                           
6656b1f  mov [rsp+0x20],rax                            
6656b24  lea r8,[0x129F9C40]                           ; [data_129f9c40]
6656b2b  lea rdx,[rbp+0x330]                           
6656b32  call 0x675E440                                ; -> sub_675e440
6656b37  mov rax,[rbp+0x330]                           
6656b3e  mov rbx,[rax]                                 
6656b41  test rbx,rbx                                  
6656b44  je 0x665D11D                                  ; -> sub_665d11d
6656b4a  mov eax,[0x129CA5E0]                          ; [data_129ca5e0]
6656b50  mov ecx,[0x128767C8]                          ; [data_128767c8]
6656b56  mov rdx,gs:[0x58]                             
6656b5f  mov rcx,[rdx+rcx*8]                           
6656b63  cmp eax,[rcx+4]                               
6656b69  jg 0x665D489                                  ; -> sub_665d489
6656b6f  cmp byte ptr [rbx+0x10],1                     
6656b73  jne 0x665D11D                                 ; -> sub_665d11d
6656b79  mov rax,[rbp+0x330]                           
```
// [V] Block A 0x6656a99..0x6656ae7 (fall-through from phase 22; rbx=[rsi+0x158] new-buffer cursor, r12=&[rbp+0x1E4] copied sky-object source record from phase 22): cmp rbx,[rsi+0x160] (cursor vs stride-0x58 buffer end); if equal → je loc_6657173, jumping INTO SkyAmbientSamples phase-2 block at 0x6657173 (VolumetricFog branches into shared SkyAmbientSamples code). Else [V] record write: rax=[r12+0x50]; [rbx+0x50]=rax; 64-byte copy r12+[0x00,0x10,0x20,0x30,0x40,0x50]→rbx+same via 6 movups (xmm0..xmm3; high-first ordering +0x30,+0x20,+0x10,+0x00), stride 0x58=88 bytes; [V] add qword ptr [rsi+0x158],0x58 (advance buffer cursor); jmp loc_6657797 (joins SkyAmbientSamples shared flow at 0x6657797 — continues into its phase-10/11 region). [V] Block B 0x6656aec..0x6656b79 (cursor==end, LegacyCubemap path): movaps [rbp+0x340],xmm0; lea rax,[0xF57DBCE] (data_f57dbce = "LegacyCubemap" string); [rbp+0x1E0]=rax (ptr), [rbp+0x1E8]=0xD=13 (len); build out-param pair [rsp+0x20]=&[rbp+0x1E0], [rsp+0x28]=&[rbp+0x340]; lea r8,[0x129F9C40] (data_129f9c40, [?] second string); lea rdx,[rbp+0x330]; call sub_675e440 [I] cubemap lookup/load writing object into [rbp+0x330]; rax=[rbp+0x330]; rbx=[rax]; test rbx,rbx; if 0 → sub_665d11d; eax=[0x129CA5E0] (data_129ca5e0); ecx=[0x128767C8] (data_128767c8); rdx=gs:[0x58]; rcx=[rdx+rcx*8] (TLS slot array indexed by ecx); cmp eax,[rcx+4]; if jg → sub_665d489; cmp byte ptr [rbx+0x10],1; if jne → sub_665d11d; rax=[rbp+0x330] (cut at 0x6656b79). [I] LegacyCubemap path: string-keyed load via sub_675e440, then object validation (TLS bounds check vs data_129ca5e0/data_128767c8, required object byte [rbx+0x10]==1). [V] Fields: [rsi+0x158]/[rsi+0x160] buffer cursor/end; [rbp+0x1E0]/[rbp+0x1E8] string ptr+len; [rbp+0x330] out object; r12 source record. NEXT RVA: 0x6656b81

### Phase 24 — VolumetricFog Release of loaded object + string build at [rbp+0x120] [V]
`0x6656b81..0x6656c3a` (40 instr)
```
6656b81  mov ecx,[rax+8]                               
6656b84  test rcx,rcx                                  
6656b87  je 0x6657444                                  ; -> loc_6657444
6656b8d  lock inc dword ptr [rcx+8]                    
6656b91  mov rcx,[rax]                                 
6656b94  mov rbx,[rax+8]                               
6656b98  mov rax,[rcx+0x18]                            
6656b9c  mov r14,[rax]                                 
6656b9f  test rbx,rbx                                  
6656ba2  je 0x665744E                                  ; -> loc_665744e
6656ba8  lock dec dword ptr [rbx+8]                    
6656bac  jne 0x665744E                                 ; -> loc_665744e
6656bb2  mov rax,[rbx]                                 
6656bb5  mov rax,[rax]                                 
6656bb8  mov rcx,rbx                                   
6656bbb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6656bc1  lock dec dword ptr [rbx+0xC]                  
6656bc5  jne 0x665744E                                 ; -> loc_665744e
6656bcb  mov rax,[rbx]                                 
6656bce  mov rax,[rax+8]                               
6656bd2  mov rcx,rbx                                   
6656bd5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6656bdb  jmp 0x665744E                                 ; -> loc_665744e
6656be0  lea r12,[rbp+0x120]                           
6656be7  mov eax,0xF                                   
6656bec  mov [rbp+0x130],r15                           
6656bf3  mov [rbp+0x138],rax                           
6656bfa  mov rcx,r12                                   
6656bfd  mov rdx,r14                                   
6656c00  mov r8,r15                                    
6656c03  call 0xEEC6EC0                                ; -> sub_eec6ec0
6656c08  mov byte ptr [r12+r13],0                      
6656c0d  mov eax,[0x129F9D00]                          ; [data_129f9d00]
6656c13  mov ecx,[0x128767C8]                          ; [data_128767c8]
6656c19  mov rdx,gs:[0x58]                             
6656c22  mov rcx,[rdx+rcx*8]                           
6656c26  cmp eax,[rcx+4]                               
6656c2c  jg 0x665D2AA                                  ; -> sub_665d2aa
6656c32  mov r9,[rsi+0x40]                             
6656c36  mov rcx,[rsi+0x68]                            
```
// [V] Block A 0x6656b81..0x6656bdb (continuation from phase 23 Block B; rax=[rbp+0x330] out object): ecx=[rax+8]; test rcx,rcx; if 0 → loc_6657444 (joins SkyAmbientSamples phase-6 release block at 0x6657444); else lock inc dword [rcx+8] (AddRef); rcx=[rax]; rbx=[rax+8]; rax=[rcx+0x18]; r14=[rax]; test rbx,rbx; if 0 → loc_665744E; lock dec dword [rbx+8]; jne → loc_665744E; rax=[rbx]; rax=[rax]; rcx=rbx; call sub_eea6040 (stage-1 destroy); lock dec dword [rbx+0xC]; jne → loc_665744E; rax=[rbx]; rax=[rax+8]; rcx=rbx; call sub_eea6040 (stage-2 destroy); jmp loc_665744E. Same two-stage Release pattern as SkyAmbientSamples epilogue, tails into SkyAmbientSamples blocks loc_6657444/loc_665744E — VolumetricFog reuses shared release code. [V] Block B 0x6656be0..0x6656c36: lea r12,[rbp+0x120]; eax=0xF (15); [rbp+0x130]=r15; [rbp+0x138]=rax; lea rcx=[rbp+0x120]; rdx=r14; r8=r15; call sub_eec6ec0 [I] ~173-byte copy r14→[rbp+0x120]; mov byte ptr [r12+r13],0 (null-terminate string); eax=[0x129F9D00] (data_129f9d00); ecx=[0x128767C8] (data_128767c8); rdx=gs:[0x58]; rcx=[rdx+rcx*8] (TLS slot array indexed by ecx); cmp eax,[rcx+4]; if jg → sub_665d2aa; r9=[rsi+0x40]; rcx=[rsi+0x68] (cut at 0x6656c36). [I] Builds null-terminated 15-char string at [rbp+0x120] (from r14 data, terminator at [r12+r13]), then TLS/global bounds check (same pattern as phase 23 Block B), then loads fog-buffer fields [rsi+0x40], [rsi+0x68]. [V] Fields: [rbp+0x120] string buf, [rbp+0x130]=r15, [rbp+0x138]=0xF; [rsi+0x40], [rsi+0x68]. NEXT RVA: 0x6656c3a

### Phase 25 — VolumetricFog string SSO/heap select + second sub_675e440 load + object validate [V]
`0x6656c3a..0x6656d0a` (40 instr)
```
6656c3a  mov rax,[rbp+0x130]                           
6656c41  cmp qword ptr [rbp+0x138],0x10                
6656c49  jb short 0x6656C54                            ; -> loc_6656c54
6656c4b  mov rdx,[rbp+0x120]                           
6656c52  jmp short 0x6656C5B                           ; -> loc_6656c5b
loc_6656c54:  ; from 6656c49
6656c54  lea rdx,[rbp+0x120]                           
loc_6656c5b:  ; from 6656c52
6656c5b  xorps xmm0,xmm0                               
6656c5e  movaps [rbp+0x340],xmm0                       
6656c65  mov [rbp+0x1E0],rdx                           
6656c6c  mov [rbp+0x1E8],rax                           
6656c73  lea r12,[rbp+0x340]                           
6656c7a  mov [rsp+0x28],r12                            
6656c7f  lea rax,[rbp+0x1E0]                           
6656c86  mov [rsp+0x20],rax                            
6656c8b  lea r8,[0x129F9CF0]                           ; [data_129f9cf0]
6656c92  lea rdx,[rbp+0x320]                           
6656c99  call 0x675E440                                ; -> sub_675e440
6656c9e  nop                                           
6656c9f  mov rax,[rbp+0x320]                           
6656ca6  mov r14,[rax]                                 
6656ca9  test r14,r14                                  
6656cac  je 0x665B56E                                  ; -> sub_665b56e
6656cb2  mov eax,[0x129CA5E0]                          ; [data_129ca5e0]
6656cb8  mov ecx,[0x128767C8]                          ; [data_128767c8]
6656cbe  mov rdx,gs:[0x58]                             
6656cc7  mov rcx,[rdx+rcx*8]                           
6656ccb  cmp eax,[rcx+4]                               
6656cd1  jg 0x665D552                                  ; -> sub_665d552
6656cd7  cmp byte ptr [r14+0x10],1                     
6656cdc  jne 0x665B56E                                 ; -> sub_665b56e
6656ce2  mov rax,[rbp+0x320]                           
6656ce9  mov rcx,[rax+8]                               
6656ced  test rcx,rcx                                  
6656cf0  je 0x66575E4                                  ; -> loc_66575e4
6656cf6  lock inc dword ptr [rcx+8]                    
6656cfa  mov rcx,[rax]                                 
6656cfd  mov r14,[rax+8]                               
6656d01  mov rax,[rcx+0x18]                            
6656d05  mov r15,[rax]                                 
6656d08  test r14,r14                                  
```
// [V] 0x6656c3a..0x6656c5b: rax=[rbp+0x130] (r15 saved at 0x6656bec); cmp qword ptr [rbp+0x138],0x10 (16-byte SSO threshold); if jb → loc_6656c54 (rdx=&[rbp+0x120], small-string local buffer); else rdx=[rbp+0x120] (heap string ptr); jmp loc_6656c5b. loc_6656c54: rdx=&[rbp+0x120]. loc_6656c5b: xorps xmm0; [rbp+0x340]=xmm0 (zero scratch); [rbp+0x1E0]=rdx (string ptr); [rbp+0x1E8]=rax (string len); lea r12=[rbp+0x340]; [rsp+0x28]=r12; lea rax=[rbp+0x1E0]; [rsp+0x20]=rax; lea r8,[0x129F9CF0] (data_129f9cf0, [?] string key); lea rdx=[rbp+0x320]; call sub_675e440 [I] second string-keyed load (cf. phase 23/24), out object [rbp+0x320]. [V] 0x6656c9f..0x6656cdc: rax=[rbp+0x320]; r14=[rax]; test r14,r14; if 0 → sub_665b56e; eax=[0x129CA5E0]; ecx=[0x128767C8]; rdx=gs:[0x58]; rcx=[rdx+rcx*8] (TLS slot array indexed by ecx); cmp eax,[rcx+4]; if jg → sub_665d552; cmp byte ptr [r14+0x10],1; if jne → sub_665b56e. Same object-validation idiom as phase 23 Block B / phase 24 Block B, distinct error tails sub_665b56e/sub_665d552. [V] 0x6656ce2..0x6656d08: rax=[rbp+0x320]; rcx=[rax+8]; test rcx,rcx; if 0 → loc_66575e4 (SkyAmbientSamples phase-8 release block); lock inc dword [rcx+8] (AddRef); rcx=[rax]; r14=[rax+8]; rax=[rcx+0x18]; r15=[rax]; test r14,r14 (cut at 0x6656d08). [I] SSO-vs-heap string selector ([rbp+0x138] len vs 0x10), then AddRef into shared SkyAmbientSamples release flow. [V] Fields: [rbp+0x130], [rbp+0x138] (len), [rbp+0x120] string buf, [rbp+0x1E0]/[rbp+0x1E8] ptr+len pair, [rbp+0x320] out object; [rsi+0x40]/[rsi+0x68] loaded earlier. NEXT RVA: 0x6656d0a

### Phase 26 — VolumetricFog release + fog-field scratch copy [V]
`0x6656d0a..0x6656dff` (40 instr)
```
6656d0a  test byte ptr [rdi],0x84                      
6656d0d  fisttp qword ptr [rax],st                     
6656d0f  add [rax],al                                  
6656d11  lock dec dword ptr [r14+8]                    
6656d16  jne 0x66575EE                                 ; -> loc_66575ee
6656d1c  mov rax,[r14]                                 
6656d1f  mov rax,[rax]                                 
6656d22  mov rcx,r14                                   
6656d25  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6656d2b  lock dec dword ptr [r14+0xC]                  
6656d30  jne 0x66575EE                                 ; -> loc_66575ee
6656d36  mov rax,[r14]                                 
6656d39  mov rax,[rax+8]                               
6656d3d  mov rcx,r14                                   
6656d40  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6656d46  jmp 0x66575EE                                 ; -> loc_66575ee
6656d4b  xor eax,eax                                   
6656d4d  mov rcx,[rdi+0xD8]                            
6656d54  mov [rbp+0x210],rcx                           
6656d5b  mov [rbp+0x218],rax                           
6656d62  movsd xmm6,[rdi+0xE8]                         
6656d6a  movss xmm12,[rdi+0xEC]                        
6656d73  movss [rbp+0x220],xmm6                        
6656d7b  movss [rbp+0x224],xmm12                       
6656d84  movsd xmm9,[rdi+0x100]                        
6656d8d  movss [rbp+0x228],xmm9                        
6656d96  movsd xmm7,[rdi+0x104]                        
6656d9e  movsd [rbp+0x22C],xmm7                        
6656da6  lea rcx,[rbp+0x234]                           
6656dad  movups xmm1,[rdi+0x10C]                       
6656db4  movups [rbp+0x234],xmm1                       
6656dbb  movsd xmm8,[rdi+0x11C]                        
6656dc4  movsd [rbp+0x244],xmm8                        
6656dcd  movss xmm10,[rdi+0x124]                       
6656dd6  movss [rbp+0x24C],xmm10                       
6656ddf  lea rdx,[rbp+0x250]                           
6656de6  movups xmm1,[rdi+0x128]                       
6656ded  movaps [rbp+0x250],xmm1                       
6656df4  mov r8d,[rdi+4]                               
6656df8  mov [rbp+0x260],r8d                           
```
// [V] 0x6656d0a..0x6656d11 (continuation from phase 25 Block B; r14=[rax+8] ref): test byte ptr [rdi],0x84 [V] flag test; then [V] rdis shows `fisttp qword ptr [rax],st` at 0x6656d0d and `add [rax],al` at 0x6656d0f — SAME displacement-byte misdecode class as SkyAmbientSamples 0x66575a6/0x66575a8 (a 6-byte conditional jump's disp32 linearly misdecoded); NOT real instructions; real flow resumes at `lock dec dword ptr [r14+8]` 0x6656d11. [V] Release sequence (identical to SkyAmbientSamples phase-8 Block L): lock dec dword [r14+8]; jne → loc_66575ee (refcount still >0); rax=[r14]; rax=[rax]; rcx=r14; call sub_eea6040 (stage-1 destroy); lock dec dword [r14+0xC]; jne → loc_66575ee; rax=[r14]; rax=[rax+8]; rcx=r14; call sub_eea6040 (stage-2 destroy); jmp loc_66575ee. Tail loc_66575ee = SkyAmbientSamples phase-9 Block L tail region — shared release code again. [V] 0x6656d4b..0x6656df8: xor eax,eax; rcx=[rdi+0xD8]; [rbp+0x210]=rcx; [rbp+0x218]=rax=0; movsd xmm6=[rdi+0xE8]; movss xmm12=[rdi+0xEC]; [rbp+0x220]=xmm6; [rbp+0x224]=xmm12; movsd xmm9=[rdi+0x100]; [rbp+0x228]=xmm9; movsd xmm7=[rdi+0x104]; [rbp+0x22C]=xmm7; lea rcx=[rbp+0x234]; movups xmm1=[rdi+0x10C]; [rbp+0x234]=xmm1; movsd xmm8=[rdi+0x11C]; [rbp+0x244]=xmm8; movss xmm10=[rdi+0x124]; [rbp+0x24C]=xmm10; lea rdx=[rbp+0x250]; movups xmm1=[rdi+0x128]; [rbp+0x250]=xmm1; mov r8d=[rdi+4]; [rbp+0x260]=r8d (cut at 0x6656df8). [I] Fog-struct field extraction from rdi (+0xD8,+0xE8,+0xEC,+0x100,+0x104,+0x10C,+0x11C,+0x124,+0x128,+4) into [rbp+0x210..0x260] scratch — same field-copy pattern as phase 22 entry. [V] Fields: [rbp+0x210],[rbp+0x218],[rbp+0x220],[rbp+0x224],[rbp+0x228],[rbp+0x22C],[rbp+0x234],[rbp+0x244],[rbp+0x24C],[rbp+0x250],[rbp+0x260]. NEXT RVA: 0x6656dff

### Phase 27 — VolumetricFog fog-parameter block + record header fields [V]
`0x6656dff..0x6656f06` (40 instr)
```
6656dff  movss xmm1,[rdi+0xC]                          
6656e04  movsd xmm2,[rdi+8]                            
6656e09  movsd [rbp+0x264],xmm2                        
6656e11  movss xmm2,[rdi+0x10]                         
6656e16  subss xmm2,xmm1                               
6656e1a  movss xmm1,[0xEEC8060]                        ; [data_eec8060]
6656e22  maxss xmm1,xmm2                               
6656e26  movss [rbp+0x26C],xmm1                        
6656e2e  movups xmm1,[rdi+0x14]                        
6656e32  movaps [rbp+0x270],xmm1                       
6656e39  movups xmm1,[rdi+0x24]                        
6656e3d  movaps [rbp+0x280],xmm1                       
6656e44  movups xmm1,[rdi+0x34]                        
6656e48  movaps [rbp+0x290],xmm1                       
6656e4f  movups xmm1,[rdi+0x44]                        
6656e53  movaps [rbp+0x2A0],xmm1                       
6656e5a  movups xmm1,[rdi+0x54]                        
6656e5e  movaps [rbp+0x2B0],xmm1                       
6656e65  movups xmm1,[rdi+0x64]                        
6656e69  movaps [rbp+0x2C0],xmm1                       
6656e70  movups xmm1,[rdi+0x74]                        
6656e74  movaps [rbp+0x2D0],xmm1                       
6656e7b  movups xmm1,[rdi+0x84]                        
6656e82  movaps [rbp+0x2E0],xmm1                       
6656e89  movsd xmm1,[rdi+0x94]                         
6656e91  movsd [rbp+0x2F0],xmm1                        
6656e99  movss xmm1,[rdi+0x9C]                         
6656ea1  movss [rbp+0x2F8],xmm1                        
6656ea9  movzx r8d,byte ptr [rdi+0xA0]                 
6656eb1  mov [rbp+0x2FC],r8b                           
6656eb8  movsd xmm11,[rdi+0xF0]                        
6656ec1  movsd [rbp+0x300],xmm11                       
6656eca  movsd xmm1,[rdi+0xF8]                         
6656ed2  movsd [rbp+0x308],xmm1                        
6656eda  mov [rbp+0x340],r9w                           
6656ee2  movaps xmm1,[rbp+0x1E0]                       
6656ee9  movaps xmm2,[rbp+0x1F0]                       
6656ef0  movaps xmm3,[rbp+0x200]                       
6656ef7  movups [rbp+0x348],xmm1                       
6656efe  movups [rbp+0x358],xmm2                       
```
// [V] 0x6656dff..0x6656eda: continuation of fog-field extraction (from phase 26's [rbp+0x210..0x260]): movss xmm1=[rdi+0xC]; movsd xmm2=[rdi+8]; [rbp+0x264]=xmm2; movss xmm2=[rdi+0x10]; subss xmm2,xmm1; movss xmm1=[0xEEC8060] (data_eec8060 — absolute address constant, [I] fog-density clamp value); maxss xmm1,xmm2; [rbp+0x26C]=xmm1 (clamped delta); movups [rdi+0x14]→[rbp+0x270]; +0x24→[rbp+0x280]; +0x34→[rbp+0x290]; +0x44→[rbp+0x2A0]; +0x54→[rbp+0x2B0]; +0x64→[rbp+0x2C0]; +0x74→[rbp+0x2D0]; +0x84→[rbp+0x2E0]; movsd [rdi+0x94]→[rbp+0x2F0]; movss [rdi+0x9C]→[rbp+0x2F8]; movzx r8d,byte [rdi+0xA0]; [rbp+0x2FC]=r8b; movsd [rdi+0xF0]=xmm11; [rbp+0x300]=xmm11; movsd [rdi+0xF8]=xmm1; [rbp+0x308]=xmm1 (cut at 0x6656eda). [V] 0x6656eda..0x6656efe: [rbp+0x340]=r9w; movaps xmm1=[rbp+0x1E0]; xmm2=[rbp+0x1F0]; xmm3=[rbp+0x200]; [rbp+0x348]=xmm1; [rbp+0x358]=xmm2 (cut). [I] [rbp+0x264..0x308] = fog parameter block (density/gradient/color fields from rdi struct +0x8..0xF8); [rbp+0x340..0x368] = record header fields. NEXT RVA: 0x6656f06

### Phase 28 — VolumetricFog ref branch + record init + second 0x9D0 buffer alloc [V]
`0x6656f06..0x6656fef` (40 instr)
```
6656f06  adc [rbp+0x368],ebx                           
6656f0c  movups [rbp+0x378],xmm0                       
6656f13  test rax,rax                                  
6656f16  mov [rbp+0x1C8],r9w                           
6656f1e  je short 0x6656F2D                            ; -> loc_6656f2d
6656f20  lock inc dword ptr [rax+8]                    
6656f24  mov r14,[rbp+0x218]                           
6656f2b  jmp short 0x6656F30                           ; -> loc_6656f30
loc_6656f2d:  ; from 6656f1e
6656f2d  xor r14d,r14d                                 
loc_6656f30:  ; from 6656f2b
6656f30  mov rdi,[rbp+0x210]                           
6656f37  mov [rbp+0x378],rdi                           
6656f3e  mov [rbp+0x380],r14                           
6656f45  movss [rbp+0x388],xmm6                        
6656f4d  movss [rbp+0x38C],xmm12                       
6656f56  movss [rbp+0x390],xmm9                        
6656f5f  movlps [rbp+0x394],xmm7                       
6656f66  movups xmm0,[rcx]                             
6656f69  movups [rbp+0x39C],xmm0                       
6656f70  movlps [rbp+0x3AC],xmm8                       
6656f78  movss [rbp+0x3B4],xmm10                       
6656f81  lea r13,[rbp+0x3B8]                           
6656f88  mov r8d,0xAD                                  
6656f8e  mov rcx,r13                                   
6656f91  call 0xEEC6EC0                                ; -> sub_eec6ec0
6656f96  movlps [rbp+0x468],xmm11                      
6656f9e  mov rax,[rbp+0x308]                           
6656fa5  mov r12,rax                                   
6656fa8  mov [rbp+0x470],rax                           
6656faf  mov ecx,0x9D0                                 
6656fb4  add rcx,[rsi+0x10]                            
6656fb8  call 0x5ABA5C0                                ; -> sub_5aba5c0
6656fbd  nop                                           
6656fbe  mov rsi,rax                                   
6656fc1  xorps xmm0,xmm0                               
6656fc4  movups [rbp+0x108],xmm0                       
6656fcb  movups [rbp+0xF8],xmm0                        
6656fd2  movups [rbp+0xE8],xmm0                        
6656fd9  movups [rbp+0xD8],xmm0                        
6656fe0  movups [rbp+0xC8],xmm0                        
6656fe7  movups [rbp+0xB8],xmm0                        
```
// [V] 0x6656f06..0x6656f30: adc [rbp+0x368],ebx (cf. SkyAmbientSamples loop-tail adc); movups [rbp+0x378]=xmm0; test rax,rax (rax=object [rbp+0x320] from phase 25); mov [rbp+0x1C8]=r9w; if je → loc_6656f2d (xor r14d,r14d=0); else lock inc dword [rax+8] (AddRef); r14=[rbp+0x218]; jmp loc_6656f30. loc_6656f30: rdi=[rbp+0x210]; [rbp+0x378]=rdi; [rbp+0x380]=r14; [rbp+0x388]=xmm6; [rbp+0x38C]=xmm12; [rbp+0x390]=xmm9; movlps [rbp+0x394]=xmm7; movups xmm0=[rcx]; [rbp+0x39C]=xmm0; movlps [rbp+0x3AC]=xmm8; [rbp+0x3B4]=xmm10; lea r13=[rbp+0x3B8]; r8d=0xAD (173); rcx=r13; call sub_eec6ec0 [I] 173-byte copy into [rbp+0x3B8]; movlps [rbp+0x468]=xmm11 — record template built at [rbp+0x348..0x478]. [V] 0x6656f9e..0x6656fe7: rax=[rbp+0x308]; r12=rax; [rbp+0x470]=rax; ecx=0x9D0; rcx += [rsi+0x10]; call sub_5aba5c0 [I] operator new 0x9D0 — SECOND buffer; rsi=rax (rsi REASSIGNED — first buffer was phase-22's); zero-init movups xmm0=0 → [rbp+0x108],[rbp+0xF8],[rbp+0xE8],[rbp+0xD8],[rbp+0xC8],[rbp+0xB8] (96 bytes, cut at 0x6656fe7). [I] First fog buffer (phase 22 rsi) had its cursor/end fields read ([rsi+0x40],[rsi+0x68],[rsi+0x10],[rsi+0x158]) before rsi was overwritten by this second alloc. [V] Fields written: [rbp+0x264..0x308] fog params, [rbp+0x340..0x470] record template, [rbp+0x1C8], [rbp+0x378],[rbp+0x380]. NEXT RVA: 0x6656fef

### Phase 29 — VolumetricFog record write + jump INTO SkyAmbientSamples phase 1 [V]
`0x6656fef..0x66570ac` (40 instr)
```
6656fef  adc [rbp+0xA8],eax                            
6656ff5  movups [rbp+0x98],xmm0                        
6656ffc  movups [rbp+0x88],xmm0                        
6657003  movups [rbp+0x78],xmm0                        
6657007  movups [rbp+0x68],xmm0                        
665700b  movups [rbp+0x58],xmm0                        
665700f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
6657016  mov rax,[rcx]                                 
6657019  mov rax,[rax+0x10]                            
665701d  mov dl,0x4A                                   
665701f  call qword ptr [0xF99FFA0]                    ; [data_f99FFA0]
6657025  nop                                           
6657026  mov ebx,eax                                   
6657028  lea rax,[rbp+0x348]                           
665702f  mov r15,[rsi+0x548]                           
6657036  cmp r15,[rsi+0x550]                           
665703d  je 0x6657237                                  ; -> loc_6657237
6657043  movups xmm0,[rax]                             
6657046  movups xmm1,[rax+0x10]                        
665704a  mov rcx,rax                                   
665704d  movups xmm2,[rax+0x20]                        
6657051  movups [r15+0x20],xmm2                        
6657056  movups [r15+0x10],xmm1                        
665705b  movups [r15],xmm0                             
665705f  xorps xmm0,xmm0                               
6657062  movups [r15+0x30],xmm0                        
6657067  test r14,r14                                  
665706a  je 0x66573C3                                  ; -> loc_66573c3
6657070  lock inc dword ptr [r14+8]                    
6657075  mov rdi,[rbp+0x378]                           
665707c  mov rax,[rbp+0x380]                           
6657083  jmp 0x66573C5                                 ; -> loc_66573c5
6657088  xor r12d,r12d                                 
665708b  mov r14,[rdi+8]                               
665708f  mov [rbp+0x1E8],r14                           
6657096  mov [rbp+0x1F0],r12                           
665709d  mov ecx,0x9D0                                 
66570a2  add rcx,[rsi+0x10]                            
66570a6  call 0x5ABA5C0                                ; -> sub_5aba5c0
66570ab  nop                                           
```
// [V] 0x6656fef..0x665703d: adc [rbp+0xA8],eax (cf. loop tails); zero [rbp+0x58..0x98] via 6 movups xmm0=0 (96 bytes); rcx = global [0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call sub_eea6040 (global count call #7); ebx=eax; lea rax=[rbp+0x348] (record template); r15=[rsi+0x548] (second-buffer record cursor); cmp r15,[rsi+0x550] (end vs limit); if je → 0x6657237 (SkyAmbientSamples phase-3 Block B — second index/hash path). [V] 0x6657043..0x6657083: movups xmm0=[rax]; xmm1=[rax+0x10]; rcx=rax; xmm2=[rax+0x20]; [r15+0x20]=xmm2; [r15+0x10]=xmm1; [r15]=xmm0 (copy template [rax+0x00..0x30] → record at r15); xorps xmm0; [r15+0x30]=xmm0(0); test r14,r14; if je → 0x66573C3 (SkyAmbientSamples phase-5 Block F record store); else lock inc dword [r14+8] (AddRef); rdi=[rbp+0x378]; rax=[rbp+0x380]; jmp 0x66573C5. VolumetricFog writes its record into the stride-0x130 table and jumps into SkyAmbientSamples shared blocks. [V] 0x6657088..0x66570ab (COLD block — not linearly reached after unconditional jmp at 0x6657083): xor r12d,r12d; mov r14,[rdi+8]; [rbp+0x1E8]=r14; [rbp+0x1F0]=r12; mov ecx,0x9D0; add rcx,[rsi+0x10]; call sub_5aba5c0; nop — this is the SKYAMBIENTSAMPLES PHASE-1 entry block (0x665708b matches exactly), preceded by xor r12d,r12d; [I] VolumetricFog joins SkyAmbientSamples phase-1 flow (shared 0x9D0 alloc + zero-init + dl=0x4A count call) — cases share code; rsi = second buffer (phase 28), so [rsi+0x10] is second-buffer base for size. [V] Fields: [rbp+0x58..0x98] zeroed, [rbp+0xA8] adc target, [rbp+0x348] template base, [rsi+0x548]/[rsi+0x550] record cursor/limit. NEXT RVA: 0x66570ac

### Phase 30 — VolumetricFog merged into SkyAmbientSamples phase-1 flow (shared code) [V]
`0x66570ac..0x665718e` (40 instr)
```
66570ac  mov rsi,rax                                   
66570af  xorps xmm0,xmm0                               
66570b2  movaps [rbp+0x3F0],xmm0                       
66570b9  movaps [rbp+0x3E0],xmm0                       
66570c0  movaps [rbp+0x3D0],xmm0                       
66570c7  movaps [rbp+0x3C0],xmm0                       
66570ce  movaps [rbp+0x3B0],xmm0                       
66570d5  movaps [rbp+0x3A0],xmm0                       
66570dc  movaps [rbp+0x390],xmm0                       
66570e3  movaps [rbp+0x380],xmm0                       
66570ea  movaps [rbp+0x370],xmm0                       
66570f1  movaps [rbp+0x360],xmm0                       
66570f8  movaps [rbp+0x350],xmm0                       
66570ff  movaps [rbp+0x340],xmm0                       
6657106  mov qword ptr [rbp+0x400],0                   
6657111  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
6657118  mov rax,[rcx]                                 
665711b  mov rax,[rax+0x10]                            
665711f  mov dl,0x4A                                   
6657121  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657127  nop                                           
6657128  mov edx,eax                                   
665712a  mov r15,[rsi+0xB0]                            
6657131  cmp r15,[rsi+0xB8]                            
6657138  je 0x66572F6                                  ; -> loc_66572f6
665713e  xorps xmm0,xmm0                               
6657141  movups [r15],xmm0                             
6657145  test r12,r12                                  
6657148  je 0x6657429                                  ; -> loc_6657429
665714e  lock inc dword ptr [r12+8]                    
6657154  mov edi,0x200000                              
6657159  or rdi,[rbp+0x348]                            
6657160  mov r14,[rbp+0x1E8]                           
6657167  mov rax,[rbp+0x1F0]                           
665716e  jmp 0x6657430                                 ; -> loc_6657430
6657173  mov r14,rbx                                   
6657176  sub r14,[rsi+0x150]                           
665717d  mov rax,r14                                   
6657180  sar rax,3                                     
6657184  mov rdx,0x2E8BA2E8BA2E8BA3                    
```
// [V] 0x66570ac..0x6657160: INSTRUCTION-IDENTICAL to SkyAmbientSamples phase 1 tail (0x66570ac..0x6657160, documented above): rsi=rax (buffer from alloc at 0x66570a6 — VolumetricFog's chained third buffer, size 0x9D0+[rsi+0x10] where rsi was the phase-28 second buffer); zero-init [rbp+0x340..0x400] (13 movaps + qword); global count call dl=0x4A → edx; r15=[rsi+0xB0] (entry-list cursor); cmp [rsi+0xB8] (end); je 0x66572F6 (SkyAmbientSamples phase-4 Block D empty-list path); zero 16 bytes at r15; test r12,r12 — r12=0 (xor r12d,r12d at 0x6657088 cold block) → je 0x6657429 (empty-case Block G, SKIPS the [r12+8] AddRef); else lock inc [r12+8]. [V] 0x6657160..0x665718e: mov r14=[rbp+0x1E8]; mov rax=[rbp+0x1F0]; jmp loc_6657430 (linear flow jumps away — shared tail); block 0x6657173 (target of VolumetricFog phase-23 `je 0x6657173`): mov r14,rbx; sub r14,[rsi+0x150] (time diff vs sky base); rax=r14; sar rax,3 (/8); rdx=0x2E8BA2E8BA2E8BA3 (cut at 0x6657184) — identical to SkyAmbientSamples phase-2 index magic-multiply block. [I] VolumetricFog has fully merged into SkyAmbientSamples shared code; case will end at the same jmp sub_665d124 at 0x6657ff4. Two shared entry points now active: 0x665708b cold block (r12=0 → empty path) and 0x6657173 (index path). NEXT RVA: 0x665718e

### Phase 31 — VolumetricFog shared index magic-multiply + hash call (identical to SkyAmbientSamples phase-2 block B) [V]
`0x665718e..0x6657241` (40 instr)
```
665718e  imul rdx,rax                                  
6657192  lea r10,[rdx+1]                               
6657196  mov rax,rdx                                   
6657199  shr rax,1                                     
665719c  mov rcx,0x2E8BA2E8BA2E8BA                     
66571a6  mov r8,rcx                                    
66571a9  sub r8,rax                                    
66571ac  add rax,rdx                                   
66571af  cmp rax,r10                                   
66571b2  cmovbe rax,r10                                
66571b6  cmp rdx,r8                                    
66571b9  cmova rax,rcx                                 
66571bd  mov rdx,0x2E8BA2E8BA2E8BB                     
66571c7  cmp rax,rdx                                   
66571ca  mov [rbp+0x540],r9b                           
66571d1  jae 0x665D665                                 ; -> sub_665d665
66571d7  imul rdi,rax,0x58                             
66571db  test rax,rax                                  
66571de  mov [rbp+0x1C8],r10                           
66571e5  je 0x6657699                                  ; -> loc_6657699
66571eb  cmp rax,0x2F                                  
66571ef  jb 0x6657670                                  ; -> loc_6657670
66571f5  cmp rax,rcx                                   
66571f8  je 0x665DB15                                  ; -> sub_665db15
66571fe  lea rdx,[rdi+0x27]                            
6657202  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
6657209  mov rax,[rcx]                                 
665720c  mov rax,[rax+8]                               
6657210  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657216  nop                                           
6657217  mov r15,rax                                   
665721a  test rax,rax                                  
665721d  je 0x665D1AD                                  ; -> sub_665d1ad
6657223  mov rax,r15                                   
6657226  add r15,0x27                                  
665722a  and r15,0xFFFFFFFFFFFFFFE0                    
665722e  mov [r15-8],rax                               
6657232  jmp 0x665769C                                 ; -> loc_665769c
6657237  mov rax,r15                                   
665723a  sub rax,[rsi+0x540]                           
```
// [V] 0x665718e..0x6657216: INSTRUCTION-IDENTICAL to SkyAmbientSamples phase-2 index block (0x6657184..0x6657216): imul rdx,rax (magic multiply low 64); clamp sequence r10=rdx+1; rax=(rdx>>1)+rdx; cmovbe/clamp to [r10, 0x2E8BA2E8BA2E8BA]; bounds: if rax>=0x2E8BA2E8BA2E8BB → sub_665d665; rdi=rax*0x58 (88-byte stride); test rax,rax; [rbp+0x1C8]=r10; [rbp+0x540]=r9b; index branches: rax==0 → loc_6657699; rax<0x2F → loc_6657670; rax==rcx(sentinel) → sub_665db15; else rdx=rdi+0x27; rcx=global [0x1233E1A8]; rax=[rcx]; rax=[rax+8]; call sub_eea6040 (hash/lookup on entry+0x27); r15=rax. [V] 0x6657217..0x6657241: mov r15,rax; test rax,rax; **je 0x665D1AD** ([V] hash-fail branch, target 0x665D1AD); rax=r15; add r15,0x27; r15 &= 0xFFFFFFFFFFFFFFE0 (align down 32); [r15-8]=rax (bucket insert, [bucket-8]=count); jmp loc_665769C. [V] Block 0x6657237 (SkyAmbientSamples phase-3 Block B target): rax=r15; rax -= [rsi+0x540] (cut at 0x665723a). [I] VolumetricFog index path reuses SkyAmbientSamples phase-2/3 shared code at the SAME addresses; hash-fail target 0x665D1AD. [?] relation of this 0x6657237 block to SkyAmbientSamples phase-3's Block A at 0x665721c (overlapping addresses — rdis linear alignment note). NEXT RVA: 0x6657241

### Phase 32 — VolumetricFog shared bucket insert + second index (identical to SkyAmbientSamples phases 3-4) [V]
`0x6657241..0x66572f6` (40 instr)
```
6657241  mov [rbp+0x540],rax                           
6657248  sar rax,4                                     
665724c  mov rcx,0x86BCA1AF286BCA1B                    
6657256  imul rcx,rax                                  
665725a  lea r9,[rcx+1]                                
665725e  mov rax,rcx                                   
6657261  shr rax,1                                     
6657264  mov rdx,0xD79435E50D7943                      
665726e  mov r8,rdx                                    
6657271  sub r8,rax                                    
6657274  add rax,rcx                                   
6657277  cmp rax,r9                                    
665727a  cmovbe rax,r9                                 
665727e  cmp rcx,r8                                    
6657281  cmova rax,rdx                                 
6657285  mov rcx,0xD79435E50D7944                      
665728f  cmp rax,rcx                                   
6657292  mov [rbp+0x48],bl                             
6657295  jae 0x665D66B                                 ; -> sub_665d66b
665729b  imul r13,rax,0x130                            
66572a2  test rax,rax                                  
66572a5  mov [rbp-0x28],r9                             
66572a9  mov [rbp+0x40],r13                            
66572ad  je 0x665790A                                  ; -> loc_665790a
66572b3  cmp rax,0xE                                   
66572b7  jb 0x66578E0                                  ; -> loc_66578e0
66572bd  lea rdx,[r13+0x27]                            
66572c1  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
66572c8  mov rax,[rcx]                                 
66572cb  mov rax,[rax+8]                               
66572cf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66572d5  nop                                           
66572d6  mov rbx,rax                                   
66572d9  test rax,rax                                  
66572dc  je 0x665D1BC                                  ; -> sub_665d1bc
66572e2  mov rax,rbx                                   
66572e5  add rbx,0x27                                  
66572e9  and rbx,0xFFFFFFFFFFFFFFE0                    
66572ed  mov [rbx-8],rax                               
66572f1  jmp 0x665790C                                 ; -> loc_665790c
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 3 Block B tail + 4 Block C/D (0x6657241..0x66572f6, documented above): rax=hash-return from 0x6657223; [rbp+0x540]=rax; sar rax,4 (/16); magic multiply 0x86BCA1AF286BCA1B (≈/17) clamp [r9, 0x86BCA1AF286BCA1B]; [rbp+0x48]=bl; bounds: rax>=0xD79435E50D7944 → sub_665d66b; r13=rax*0x130 (304-byte stride); [rbp-0x28]=r9; [rbp+0x40]=r13; index branches: rax==0 → loc_665790a; rax<0xE → loc_66578E0; else rdx=r13+0x27; rcx=global [0x1233E1A8]; rax=[rcx]; rax=[rax+8]; call sub_eea6040 → rbx=rax; test rax,rax; je 0x665D1BC; rbx=rax+0x27; rbx&=~0x1F; [rbx-8]=rax (bucket insert); jmp loc_665790C. [I] Fully shared code with SkyAmbientSamples; no VolumetricFog-specific registers introduced here. NEXT RVA: 0x66572f6

### Phase 33 — VolumetricFog shared empty-list index path (identical to SkyAmbientSamples phase 4 Block D) [V]
`0x66572f6..0x66573a9` (40 instr)
```
66572f6  mov [rbp+0x1C8],dl                            
66572fc  mov rdi,r15                                   
66572ff  sub rdi,[rsi+0xA8]                            
6657306  mov rcx,rdi                                   
6657309  sar rcx,4                                     
665730d  lea r13,[rcx+1]                               
6657311  mov rax,rcx                                   
6657314  shr rax,1                                     
6657317  mov rdx,0xFFFFFFFFFFFFFFF                     
6657321  mov r8,rdx                                    
6657324  sub r8,rax                                    
6657327  add rax,rcx                                   
665732a  cmp rax,r13                                   
665732d  cmovbe rax,r13                                
6657331  cmp rcx,r8                                    
6657334  cmova rax,rdx                                 
6657338  mov rcx,rax                                   
665733b  shr rcx,0x3C                                  
665733f  jne 0x665D671                                 ; -> sub_665d671
6657345  mov rcx,rax                                   
6657348  shl rcx,4                                     
665734c  mov [rbp+0x540],rcx                           
6657353  test rax,rax                                  
6657356  mov [rbp+0x40],bx                             
665735a  je 0x665802A                                  ; -> loc_665802a
6657360  cmp rax,0x100                                 
6657366  jb 0x6657FF9                                  ; -> loc_6657ff9
665736c  mov rcx,0xFFFFFFFFFFFFFFE                     
6657376  cmp rax,rcx                                   
6657379  jae 0x665DB1B                                 ; -> sub_665db1b
665737f  mov rax,[rbp+0x540]                           
6657386  lea rdx,[rax+0x27]                            
665738a  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
6657391  mov rax,[rcx]                                 
6657394  mov rax,[rax+8]                               
6657398  mov [rbp+0x48],rdx                            
665739c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66573a2  nop                                           
66573a3  mov rbx,rax                                   
66573a6  test rax,rax                                  
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phase 4 Block D (0x66572f6..0x66573a9, documented above): [rbp+0x1C8]=dl; rdi=r15-[rsi+0xA8] (byte offset); rcx=rdi>>4 (/16); r13=rcx+1; magic sequence clamp [r13, 0xFFFFFFFFFFFFFFF]; if (rax>>60)!=0 → sub_665d671; rcx=rax<<4 (=rax*16); [rbp+0x540]=rcx; [rbp+0x40]=bx; test rax,rax; rax==0 → loc_665802A; rax<0x100 → loc_6657ff9; rax>=0xFFFFFFFFFFFFFFE → sub_665db1b; rax=[rbp+0x540]; rdx=rax+0x27; rcx=global [0x1233E1A8]; rax=[rcx]; rax=[rax+8]; [rbp+0x48]=rdx; call sub_eea6040 → rbx=rax; test rax,rax (cut at 0x66573a6). [I] Fully shared code; empty-list index path (from phase 32's `je 0x66572F6`). NEXT RVA: 0x66573a9

### Phase 34 — VolumetricFog shared record store + release Block H (identical to SkyAmbientSamples phase 5) [V]
`0x66573a9..0x665746c` (40 instr)
```
66573a9  je 0x665D1CB                                  ; -> sub_665d1cb
66573af  mov rax,rbx                                   
66573b2  add rbx,0x27                                  
66573b6  and rbx,0xFFFFFFFFFFFFFFE0                    
66573ba  mov [rbx-8],rax                               
66573be  jmp 0x665802C                                 ; -> loc_665802c
66573c3  xor eax,eax                                   
66573c5  mov [r15+0x30],rdi                            
66573c9  mov [r15+0x38],rax                            
66573cd  movss [r15+0x40],xmm6                         
66573d3  movss [r15+0x44],xmm12                        
66573d9  movss [r15+0x48],xmm9                         
66573df  movlps [r15+0x4C],xmm7                        
66573e4  movups xmm0,[rcx+0x54]                        ; R a0+0x54
66573e8  movups [r15+0x54],xmm0                        
66573ed  movlps [r15+0x64],xmm8                        
66573f2  movss [r15+0x6C],xmm10                        
66573f8  lea rcx,[r15+0x70]                            
66573fc  mov r8d,0xAD                                  
6657402  mov rdx,r13                                   
6657405  call 0xEEC6EC0                                ; -> sub_eec6ec0
665740a  movlps [r15+0x120],xmm11                      
6657412  mov [r15+0x128],r12                           
6657419  add qword ptr [rsi+0x548],0x130               
6657424  jmp 0x6657E7C                                 ; -> loc_6657e7c
6657429  mov edi,0x200000                              
665742e  xor eax,eax                                   
6657430  mov [r15],r14                                 
6657433  mov [r15+8],rax                               
6657437  add qword ptr [rsi+0xB0],0x10                 
665743f  jmp 0x6658215                                 ; -> loc_6658215
6657444  mov rax,[rax]                                 
6657447  mov rax,[rax+0x18]                            
665744b  mov r14,[rax]                                 
665744e  test r14,r14                                  
6657451  je 0x665D11D                                  ; -> sub_665d11d
6657457  mov r14,[rsi]                                 
665745a  mov rax,[rbp+0x330]                           
6657461  xorps xmm0,xmm0                               
6657464  movaps [rbp+0x340],xmm0                       
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phase 5 Block E/F/G + phase 6 Block H head (0x66573a9..0x665746c, documented above): je 0x665D1CB (hash-fail destroy); bucket insert [rbx-8]=rax; jmp loc_665802C. Block 0x66573c3 (record store at r15, stride-0x130): [r15+0x30]=rdi; [r15+0x38]=rax(0); movss [r15+0x40,0x44,0x48]=xmm6,xmm12,xmm9; movlps [r15+0x4C]=xmm7; movups [r15+0x54]=[rcx+0x54]; movlps [r15+0x64]=xmm8; [r15+0x6C]=xmm10; lea rcx=[r15+0x70]; r8d=0xAD (173); rdx=r13; call sub_eec6ec0 (173-byte copy); [r15+0x120]=xmm11; [r15+0x128]=r12; add qword ptr [rsi+0x548],0x130 (advance record cursor by stride 0x130); jmp loc_6657e7c. Block 0x6657429 (r12==0 empty case): edi=0x200000; eax=0; [r15]=r14; [r15+8]=0; add [rsi+0xB0],0x10 (16-byte entry cursor); jmp loc_6658215. Block 0x6657444 (Release Block H): rax=[rax]; rax=[rax+0x18]; r14=[rax]; if r14==0 → sub_665d11D; r14=[rsi]; rax=[rbp+0x330]; zero [rbp+0x340] (cut at 0x6657464). [I] Fully shared code with SkyAmbientSamples. NOTE: r12=0 on VolumetricFog's cold-block path means the empty path (0x6657429) may be taken; the index path reaches the record store (0x66573c3) instead. NEXT RVA: 0x665746c

### Phase 35 — VolumetricFog shared release Blocks H/J/K (identical to SkyAmbientSamples phases 6-7) [V]
`0x665746c..0x665751c` (40 instr)
```
665746c  mov ecx,[rax+8]                               
665746f  test rcx,rcx                                  
6657472  je 0x6658355                                  ; -> loc_6658355
6657478  lock inc dword ptr [rcx+8]                    
665747c  mov rbx,[rbp+0x348]                           
6657483  movups xmm0,[rax]                             
6657486  movaps [rbp+0x340],xmm0                       
665748d  test rbx,rbx                                  
6657490  je 0x665836A                                  ; -> loc_665836a
6657496  lock dec dword ptr [rbx+8]                    
665749a  jne 0x665836A                                 ; -> loc_665836a
66574a0  mov rax,[rbx]                                 
66574a3  mov rax,[rax]                                 
66574a6  mov rcx,rbx                                   
66574a9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66574af  lock dec dword ptr [rbx+0xC]                  
66574b3  jne 0x665836A                                 ; -> loc_665836a
66574b9  mov rax,[rbx]                                 
66574bc  mov rax,[rax+8]                               
66574c0  mov rcx,rbx                                   
66574c3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66574c9  jmp 0x665836A                                 ; -> loc_665836a
66574ce  mov rax,[rax]                                 
66574d1  mov rax,[rax+0x18]                            
66574d5  mov r14,[rax]                                 
66574d8  test r14,r14                                  
66574db  je 0x665AEE8                                  ; -> sub_665aee8
66574e1  mov r14,[rsi]                                 
66574e4  mov rax,[rbp+0x320]                           
66574eb  xorps xmm0,xmm0                               
66574ee  movaps [rbp+0x340],xmm0                       
66574f5  mov rcx,[rax+8]                               
66574f9  test rcx,rcx                                  
66574fc  je 0x6658445                                  ; -> loc_6658445
6657502  lock inc dword ptr [rcx+8]                    
6657506  mov rbx,[rbp+0x348]                           
665750d  movups xmm0,[rax]                             
6657510  movaps [rbp+0x340],xmm0                       
6657517  test rbx,rbx                                  
665751a  je 0x665845A                                  ; -> loc_665845a
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 6 Block H + 7 Block J/K head (0x665746c..0x665751c, documented above): release sequence ecx=[rax+8]; AddRef [rcx+8]; rbx=[rbp+0x348]; Release rbx ([rbx+8] lock dec; stage-1 destroy sub_eea6040; [rbx+0xC] lock dec; stage-2 destroy sub_eea6040); tails loc_6658355/loc_665836A. Then next object: rax=[rax]; rax=[rax+0x18]; r14=[rax]; if 0 → sub_665aee8; r14=[rsi]; rax=[rbp+0x320]; zero [rbp+0x340]; rcx=[rax+8]; if 0 → loc_6658445; lock inc [rcx+8] (AddRef); rbx=[rbp+0x348]; zero [rbp+0x340]; if rbx==0 → loc_665845A (cut at je). [I] Fully shared release code; [rbp+0x330] and [rbp+0x320] are VolumetricFog object refs being released. NEXT RVA: 0x665751c

### Phase 36 — VolumetricFog shared release Blocks K/L (identical to SkyAmbientSamples phases 7-8; misdecode at 0x665751c/0x665751e) [V]
`0x665751c..0x66575c8` (40 instr)
```
665751c  cmp cl,[rdi]                                  
665751e  add [rax],al                                  
6657520  lock dec dword ptr [rbx+8]                    
6657524  jne 0x665845A                                 ; -> loc_665845a
665752a  mov rax,[rbx]                                 
665752d  mov rax,[rax]                                 
6657530  mov rcx,rbx                                   
6657533  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657539  lock dec dword ptr [rbx+0xC]                  
665753d  jne 0x665845A                                 ; -> loc_665845a
6657543  mov rax,[rbx]                                 
6657546  mov rax,[rax+8]                               
665754c  mov rcx,rbx                                   
665754d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657553  jmp 0x665845A                                 ; -> loc_665845a
6657558  mov rax,[rax]                                 
665755b  mov rax,[rax+0x18]                            
665755f  mov r15,[rax]                                 
6657562  test r15,r15                                  
6657565  je 0x665AEE8                                  ; -> sub_665aee8
665756b  mov r15,[rsi]                                 
665756e  mov rax,[rbp+0x320]                           
6657575  xorps xmm0,xmm0                               
6657578  movaps [rbp+0x340],xmm0                       
665757f  mov rcx,[rax+8]                               
6657583  test rcx,rcx                                  
6657586  je 0x66585B4                                  ; -> loc_66585b4
665758c  lock inc dword ptr [rcx+8]                    
6657590  mov r14,[rbp+0x348]                           
6657597  movups xmm0,[rax]                             
665759a  movaps [rbp+0x340],xmm0                       
66575a1  test r14,r14                                  
66575a4  je 0x66585C9                                  ; -> loc_66585c9
66575aa  lock dec dword ptr [r14+8]                    
66575af  jne 0x66585C9                                 ; -> loc_66585c9
66575b5  mov rax,[r14]                                 
66575b8  mov rax,[rax]                                 
66575bb  mov rcx,r14                                   
66575be  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66575c4  lock dec dword ptr [r14+0xC]                  
```
// [V] 0x665751c/0x665751e: `cmp cl,[rdi]` and `add [rax],al` — SAME displacement-byte misdecode class as SkyAmbientSamples 0x66575a6/0x66575a8 (bytes of a 6-byte conditional jump linearly misdecoded); NOT real instructions; real flow resumes at `lock dec dword ptr [rbx+8]` 0x6657520 (the `je 0x665845A` at 0x665751a is a 6-byte rel32 ending exactly there). [V] Rest: INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 7-8 (0x6657520..0x66575c4, documented above): release of rbx ([rbx+8] lock dec; stage-1+stage-2 destroy sub_eea6040; tails loc_665845A); next object: rax=[rax]; rax=[rax+0x18]; r15=[rax]; if 0 → sub_665aee8; r14=[rsi]; rax=[rbp+0x320]; zero [rbp+0x340]; rcx=[rax+8]; AddRef [rcx+8]; rbx=r14=[rbp+0x348]; zero [rbp+0x340]; if rbx==0 → loc_66585C9; lock dec [r14+8]; jne → loc_66585C9; stage-1 destroy; lock dec [r14+0xC] (cut at 0x66575c4). [I] Fully shared release code. NEXT RVA: 0x66575c8

### Phase 37 — VolumetricFog shared release tail + Block M head (identical to SkyAmbientSamples phases 8-9) [V]
`0x66575c8..0x6657677` (40 instr)
```
66575c8  or al,0xF                                     
66575ca  test edx,edi                                  
66575cc  sldt [rax]                                    
66575cf  mov rax,[r14]                                 
66575d2  mov rax,[rax+8]                               
66575d6  mov rcx,r14                                   
66575d9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66575df  jmp 0x66585C9                                 ; -> loc_66585c9
66575e4  mov rax,[rax]                                 
66575e7  mov rax,[rax+0x18]                            
66575eb  mov r15,[rax]                                 
66575ee  test r15,r15                                  
66575f1  je 0x665B56E                                  ; -> sub_665b56e
66575f7  mov r15,[rsi]                                 
66575fa  mov rax,[rbp+0x320]                           
6657601  xorps xmm0,xmm0                               
6657604  movaps [rbp+0x340],xmm0                       
665760b  mov rcx,[rax+8]                               
665760f  test rcx,rcx                                  
6657612  je 0x66587CF                                  ; -> loc_66587cf
6657618  lock inc dword ptr [rcx+8]                    
665761c  mov r14,[rbp+0x348]                           
6657623  movups xmm0,[rax]                             
6657626  movaps [rbp+0x340],xmm0                       
665762d  test r14,r14                                  
6657630  je 0x66587E4                                  ; -> loc_66587e4
6657636  lock dec dword ptr [r14+8]                    
665763b  jne 0x66587E4                                 ; -> loc_66587e4
6657641  mov rax,[r14]                                 
6657644  mov rax,[rax]                                 
6657647  mov rcx,r14                                   
665764a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657650  lock dec dword ptr [r14+0xC]                  
6657655  jne 0x66587E4                                 ; -> loc_66587E4
665765b  mov rax,[r14]                                 
665765e  mov rax,[rax+8]                               
6657662  mov rcx,r14                                   
6657665  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
665766b  jmp 0x66587E4                                 ; -> loc_66587E4
6657670  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
```
// [V] 0x66575c8..0x66575cf: rdis shows `or al,0xF`, `test edx,edi`, `sldt [rax]` — byte pattern sits exactly where prior displacement-byte misdecodes occurred (between control flow and a destroy-call sequence); treat as non-instruction junk decode [I], flow continues at `mov rax,[r14]` 0x66575cf [V]. [V] Rest INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 8-9 (0x66575cf..0x6657670, documented above): stage-2 destroy (call sub_eea6040; jmp loc_66585C9); next object release (r15=[rax]; sub_665b56e if 0; AddRef [rcx+8]; Release r14=[rbp+0x348] with stage-1+stage-2 destroy; tails loc_66587CF/loc_66587E4). [V] 0x6657670: mov rcx,global [0x1233E1A8] — head of Block M (index<0xE path, SkyAmbientSamples phase 9 Block N). [I] Fully shared release code; VolumetricFog's release targets (sub_665aee8, loc_66587E4, etc.) are shared SkyAmbientSamples epilogues. NEXT RVA: 0x6657677

### Phase 38 — VolumetricFog shared Block M record copy + growable buffer (identical to SkyAmbientSamples phases 9-10) [V]
`0x6657677..0x6657721` (40 instr)
```
6657677  mov rax,[rcx]                                 ; R a0+0x0
665767a  mov rax,[rax+8]                               ; R *(a0+0x0)+0x8
665767e  mov rdx,rdi                                   
6657681  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657687  nop                                           
6657688  mov r15,rax                                   
665768b  test rax,rax                                  
665768e  jne short 0x665769C                           ; -> loc_665769c
6657690  mov rcx,rdi                                   
6657693  call 0x9BC830                                 ; -> sub_9bc830
6657698  nop                                           
6657699  xor r15d,r15d                                 
loc_665769c:  ; from 665768e
665769c  mov rax,[r12+0x50]                            
66576a1  mov [r15+r14+0x50],rax                        
66576a6  movups xmm0,[r12+0x40]                        
66576ac  movups [r15+r14+0x40],xmm0                    
66576b2  movups xmm0,[r12]                             
66576b7  movups xmm1,[r12+0x10]                        
66576bd  movups xmm2,[r12+0x20]                        
66576c3  movups xmm3,[r12+0x30]                        
66576c9  movups [r15+r14+0x30],xmm3                    
66576cf  movups [r15+r14+0x20],xmm2                    
66576d5  movups [r15+r14+0x10],xmm1                    
66576db  movups [r15+r14],xmm0                         ; rdi → [r15+r14]  (rdis: movups [r15+r14],xmm0)
66576e0  cmp rbx,[rsi+0x158]                           
66576e7  je short 0x6657717                            ; -> loc_6657717
66576e9  add r14,r15                                   
66576ec  add r14,0x58                                  
66576f0  mov rdx,[rsi+0x150]                           
66576f7  mov r8,rbx                                    
66576fa  sub r8,rdx                                    
66576fd  mov rcx,r15                                   
6657700  call 0xEEC6DE0                                ; -> sub_eec6de0
6657705  mov r8,[rsi+0x158]                            
665770c  sub r8,rbx                                    
665770f  mov rcx,r14                                   
6657712  mov rdx,rbx                                   
6657715  jmp short 0x6657727                           ; -> loc_6657727
loc_6657717:  ; from 66576e7
6657717  mov rdx,[rsi+0x150]                           
665771e  sub rbx,rdx                                   
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 9 Block M + 10 Block M-tail (0x6657677..0x6657721, documented above): call sub_eea6040 → r15; if r15==0 → call sub_9bc830; r15d=0; loc_665769c: rax=[r12+0x50]; [r15+r14+0x50]=rax; 64-byte struct copy r12→r15+r14 via 4 movups; cmp rbx,[rsi+0x158]; je loc_6657717; else r14+=r15; r14+=0x58; memmove shift (rdx=[rsi+0x150]; r8=rbx-rdx; rcx=r15; call sub_eec6de0). loc_6657717: rdx=[rsi+0x150]; rbx-=rdx (cut at 0x665771e). [I] Fully shared code — small-index insert path into stride-0x58 buffer ([rsi+0x150]/0x158/0x160). r12 = source record ptr ([rbp+0x1E4] region from phase 22), rbx = dest. NEXT RVA: 0x6657721

### Phase 39 — VolumetricFog shared memmove + buffer grow + table index (identical to SkyAmbientSamples phases 10-11 head) [V]
`0x6657721..0x66577e2` (40 instr)
```
6657721  mov rcx,r15                                   
6657724  mov r8,rbx                                    
6657727  call 0xEEC6DE0                                ; -> sub_eec6de0
665772c  mov rcx,[rsi+0x150]                           
6657733  test rcx,rcx                                  
6657736  je short 0x665776C                            ; -> loc_665776c
6657738  mov rdx,[rsi+0x160]                           
665773f  sub rdx,rcx                                   
6657742  cmp rdx,0x1000                                
6657749  jb short 0x6657767                            ; -> loc_6657767
665774b  mov rax,[rcx-8]                               
665774f  add rcx,0xFFFFFFFFFFFFFFF8                    
6657753  sub rcx,rax                                   
6657756  cmp rcx,0x20                                  
665775a  jae 0x665D43A                                 ; -> sub_665d43a
6657760  add rdx,0x27                                  
6657764  mov rcx,rax                                   
loc_6657767:  ; from 6657749
6657767  call 0xE935700                                ; -> sub_e935700
loc_665776c:  ; from 6657736
665776c  mov [rsi+0x150],r15                           
6657773  imul rax,[rbp+0x1C8],0x58                     
665777b  add rax,r15                                   
665777e  mov [rsi+0x158],rax                           
6657785  add rdi,r15                                   
6657788  mov [rsi+0x160],rdi                           
665778f  movzx r9d,byte ptr [rbp+0x540]                
6657797  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
665779e  mov rax,[rcx]                                 
66577a1  mov rax,[rax+0x10]                            
66577a5  mov edx,r9d                                   
66577a8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66577ae  nop                                           
66577af  mov qword ptr [rbp+0x348],0x4000              
66577ba  mov eax,[rsi+0x158]                           
66577c0  sub eax,[rsi+0x150]                           
66577c6  shr eax,3                                     
66577c9  imul eax,0xFFFF8BA3                           
66577cf  dec eax                                       
66577d1  mov [rbp+0x3EC],ax                            
66577d8  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
66577df  mov rax,[rcx]                                 
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 10 Block M-tail + 11 head (0x6657721..0x66577e2, documented above): call sub_eec6de0 (memmove shift); heap-buffer maintenance ([rsi+0x150]/0x158/0x160 base/cursor/end; free via sub_e935700 when growing); [rsi+0x150]=r15 (new base); [rsi+0x158]=r15+[rbp+0x1C8]*0x58 (new cursor); [rsi+0x160]=rdi+r15 (new end); r9d=byte [rbp+0x540]; global count call dl=r9d; [rbp+0x348]=0x4000; eax=([rsi+0x158]-[rsi+0x150])>>3 (used entries /8); magic multiply 0xFFFF8BA3; dec; [rbp+0x3EC]=ax (table-position index); rcx=global [0x1233E1B0]; rax=[rcx] (cut at 0x66577df). [I] Fully shared code with SkyAmbientSamples. NEXT RVA: 0x66577e2

### Phase 40 — VolumetricFog shared word-array insert + 0xC8 record copy (identical to SkyAmbientSamples phases 11-12) [V]
`0x66577e2..0x66578a2` (40 instr)
```
66577e2  mov rax,[rax+0x10]                            
66577e6  mov dl,0x4A                                   
66577e8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66577ee  mov [rbp+0x540],al                            
66577f4  mov rdx,[rsi+0x8A8]                           
66577fb  cmp rdx,[rsi+0x8B0]                           
6657802  je short 0x6657812                            ; -> loc_6657812
6657804  mov [rdx],r13w                                
6657808  add qword ptr [rsi+0x8A8],2                   
6657810  jmp short 0x6657829                           ; -> loc_6657829
loc_6657812:  ; from 6657802
6657812  mov rcx,rsi                                   
6657815  add rcx,0x8A0                                 
665781c  lea r8,[rbp+0x1E0]                            
6657823  call 0x1EF6F90                                ; -> sub_1ef6f90
6657828  nop                                           
loc_6657829:  ; from 6657810
6657829  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
6657830  mov rax,[rcx]                                 
6657833  mov rax,[rax+0x10]                            
6657837  movzx edx,byte ptr [rbp+0x540]                
665783e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657844  nop                                           
6657845  mov qword ptr [rbp+0x340],1                   
6657850  mov eax,[rsi+0x8A8]                           
6657856  sub eax,[rsi+0x8A0]                           
665785c  shr eax,1                                     
665785e  dec eax                                       
6657860  mov [rbp+0x350],ax                            
6657867  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
665786e  mov rax,[rcx]                                 
6657871  mov rax,[rax+0x10]                            
6657875  mov dl,0x4A                                   
6657877  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
665787d  mov [rbp+0x540],al                            
6657883  mov rax,[rsi+8]                               
6657887  cmp rax,[rsi+0x10]                            
665788b  je short 0x66578AC                            ; -> loc_66578ac
665788d  lea rdx,[rbp+0x340]                           
6657894  mov r8d,0xC8                                  
665789a  mov rcx,rax                                   
665789d  call 0xEEC6EC0                                ; -> sub_eec6ec0
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 11-12 head (0x66577e2..0x66578a2, documented above): global count call dl=0x4A; [rbp+0x540]=al; word array [rsi+0x8A0/0x8A8/0x8B0]: if cursor!=end → [rdx]=r13w (word write); cursor+=2; else sub_1ef6f90 grow helper; global count call again; [rbp+0x340]=1; word count index ([rbp+0x350]=last word index); global count call; [rbp+0x540]=al; rax=[rsi+8]; if [rsi+8]!= [rsi+0x10] → rdx=[rbp+0x340]; r8d=0xC8 (200); rcx=rax; call sub_eec6ec0 (copy 0xC8 bytes to record slot) (cut at call 0x665789d). [I] Fully shared code with SkyAmbientSamples; word-array + stride-0xC8 record table ([rsi+8]/[rsi+0x10]). NEXT RVA: 0x66578a2

### Phase 41 — VolumetricFog shared 0xC8 record finalize + jmp sub_665d154 exit + Block N record loop head (identical to SkyAmbientSamples phase 12) [V]
`0x66578a2..0x6657944` (40 instr)
```
66578a2  add qword ptr [rsi+8],0xC8                    
66578aa  jmp short 0x66578BF                           ; -> loc_66578bf
66578ac  lea r8,[rbp+0x340]                            
66578b3  mov rcx,rsi                                   
66578b6  mov rdx,rax                                   
66578b9  call 0x5ABA6D0                                ; -> sub_5aba6d0
66578be  nop                                           
loc_66578bf:  ; from 66578aa
66578bf  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
66578c6  mov rax,[rcx]                                 
66578c9  mov rax,[rax+0x10]                            
66578cd  movzx edx,byte ptr [rbp+0x540]                
66578d4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66578da  nop                                           
66578db  jmp 0x665D154                                 ; -> sub_665d154   (case exit — shared epilogue)
66578e0  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
66578e7  mov rax,[rcx]                                 
66578ea mov rax,[rax+8]                               
66578ee mov rdx,r13                                   
66578f1 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
66578f7 nop                                           
66578f8 mov rbx,rax                                   
66578fb test rax,rax                                  
66578fe jne short 0x665790C                           ; -> loc_665790c
6657900 mov rcx,[rbp+0x40]                            
6657904 call 0x9BC830                                 ; -> sub_9bc830
6657909 nop                                           
665790a xor ebx,ebx                                   
loc_665790c:  ; from 66578fe
665790c  mov rax,[rbp+0x540]                           
6657913 lea r13,[rbx+rax]                             
6657917 lea rcx,[rbp+0x348]                           
665791e movups xmm0,[rcx]                             
6657921 movups xmm1,[rcx+0x10]                        
6657925 movups xmm2,[rcx+0x20]                        
6657929 movups [rbx+rax+0x20],xmm2                    
665792e movups [rbx+rax+0x10],xmm1                    
6657933 movups [rbx+rax],x0                           ; rdi → [r15+r14]   (rdis: movups [rbx+rax],xmm0)
6657937  xorps xmm0,xmm0                               
665793a  movups [rbx+rax+0x30],xmm0                    
665793f  test r14,r14                                  
6657942  je short 0x6657959                            ; -> loc_6657959
```
// [V] 0x66578a2..0x66578aa: [rsi+8]+=0xC8 (advance stride-0xC8 record cursor); jmp loc_66578bf. [V] loc_66578ac (slot-full): sub_5aba6d0 alloc grow. [V] loc_66578bf: global count call dl=[rbp+0x540]; **jmp 0x665D154** → sub_665d154 — a VOLUMETRICFOG CASE EXIT via shared epilogue (reachable from this path). [V] Block N 0x66578e0..0x6657942 (SkyAmbientSamples phase-12 Block N, index<0xE/14 path): call sub_eea6040 → rbx=hash result; if rbx!=0 → loc_665790c; else rcx=[rbp+0x40]; call sub_9bc830; ebx=0. loc_665790c: rax=[rbp+0x540]; r13=rbx+rax (record ptr); rcx=[rbp+0x348]; movups xmm0,xmm1,xmm2 = [rcx+0x00,0x10,0x20]; [rbx+rax+0x20,0x10,0x00]=xmm2,xmm1,xmm0; xorps xmm0; [rbx+rax+0x30]=0; test r14,r14; je loc_6657959 (cut at 0x6657942). [I] Two exits now seen: jmp sub_665d154 (0x66578db) and continued Block-N flow; shared code continues to jmp sub_665d124 at 0x6657ff4. NEXT RVA: 0x6657944

### Phase 42 — VolumetricFog shared entry loop setup + copy loop head (identical to SkyAmbientSamples phase 13) [V]
`0x6657944..0x6657a0c` (40 instr)
```
6657944  lock inc dword ptr [r14+8]                    
6657949  mov rdi,[rbp+0x378]                           
6657950  mov rax,[rbp+0x380]                           
6657957  jmp short 0x665795B                           ; -> loc_665795b
6657959  xor eax,eax                                   
loc_665795b:  ; from 6657957
665795b  mov [r13+0x30],rdi                            
665795f  mov [r13+0x38],rax                            
6657963  movlhps xmm6,xmm9                             
6657967  movups [r13+0x40],xmm6                        
665796c  shufps xmm7,xmm7,0x55                         
6657970  movss [r13+0x50],xmm7                         
6657976  lea rax,[rbp+0x348]                           
665797d  movups xmm0,[rax+0x54]                        
6657981  movups [r13+0x54],xmm0                        
6657986  movlps [r13+0x64],xmm8                        
665798b  movss [r13+0x6C],xmm10                        
6657991  lea rcx,[r13+0x70]                            
6657995  mov r8d,0xAD                                  
665799b  lea rdx,[rbp+0x3B8]                           
66579a2  call 0xEEC6EC0                                ; -> sub_eec6ec0
66579a7  movlps [r13+0x120],xmm11                      
66579af  mov [r13+0x128],r12                           
66579b6  mov r14,[rsi+0x540]                           
66579bd  mov rdi,[rsi+0x548]                           
66579c4  cmp r15,rdi                                   
66579c7  je 0x6657C6B                                  ; -> loc_6657c6b
66579cd  cmp r14,r15                                   
66579d0  je 0x6657B0B                                  ; -> loc_6657b0b
66579d6  xor edi,edi                                   
66579d8  xorps xmm6,xmm6                               
66579db  jmp 0x6657AC9                                 ; -> loc_6657ac9
loc_66579e0:  ; from 6657af5, 6657aff
66579e0  lea r12,[rbx+rdi]                             
66579e4  lea r13,[r14+rdi]                             
66579e8  mov rax,[r13+0x30]                            
66579ec  mov [r12+0x30],rax                            
66579f1 mov rax,[r13+0x38]                            
66579f5 mov [r12+0x38],rax                            
66579fa movss xmm0,[r13+0x40]                         
6657a00 movss [r12+0x40],xmm0                         
6657a07 movss xmm0,[r13+0x44]                         
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phase 13 (0x6657944..0x6657a0c, documented above): lock inc dword [r14+8] (AddRef entry's +0x38 ref); rdi=[rbp+0x378]; rax=[rbp+0x380]; loc_665795b: [r13+0x30]=rdi; [r13+0x38]=rax(0); movlhps xmm6,xmm9; [r13+0x40]=xmm6; shufps xmm7,xmm7,0x55; [r13+0x50]=xmm7; xmm0=[rbp+0x348+0x54]; [r13+0x54]=xmm0; [r13+0x64]=xmm8; [r13+0x6C]=xmm10; lea rcx=[r13+0x70]; r8d=0xAD (173); rdx=[rbp+0x3B8]; call sub_eec6ec0 (173-byte copy); [r13+0x120]=xmm11; [r13+0x128]=r12; r14=[rsi+0x540] (table base); rdi=[rsi+0x548] (table end); if r15==rdi → loc_6657C6B; if r14==r15 → loc_6657B0B; else edi=0; xorps xmm6; jmp loc_6657AC9 (entry-compact loop). loc_66579e0 (loop head): r12=rbx+rdi (dest); r13=r14+rdi (source); copy record fields [r13+0x30,0x38,0x40,0x44] → [r12+same] (cut at 0x6657a07). [I] Fully shared code; loop compacts remaining entries in the stride-0x130 table ([rsi+0x540]/[rsi+0x548]). NEXT RVA: 0x6657a0c

### Phase 43 — VolumetricFog shared entry-copy loop body (identical to SkyAmbientSamples phase 14) [V]
`0x6657a0c..0x6657afe` (40 instr)
```
6657a0c  movss [r12+0x44],xmm0                         
6657a14  movss xmm0,[r13+0x48]                         
6657a1a  movss [r12+0x48],xmm0                         
6657a21  movss xmm0,[r13+0x4C]                         
6657a27  movss [r12+0x4C],xmm0                         
6657a2e  movss xmm0,[r13+0x50]                         
6657a34  movss [r12+0x50],xmm0                         
6657a3b  movups xmm0,[r13+0x54]                        
6657a40  movups [r12+0x54],xmm0                        
6657a46  movss xmm0,[r13+0x64]                         
6657a4c  movss [r12+0x64],xmm0                         
6657a53  movss xmm0,[r13+0x68]                         
6657a59  movss [r12+0x68],xmm0                         
6657a60  movss xmm0,[r13+0x6C]                         
6657a66  movss [r12+0x6C],xmm0                         
6657a6d  lea rcx,[r12+0x70]                            
6657a72  lea rdx,[r13+0x70]                            
6657a76  mov r8d,0xAD                                  
6657a7c  call 0xEEC6EC0                                ; -> sub_eec6ec0
6657a81  movss xmm0,[r13+0x120]                        
6657a8a  movss [r12+0x120],xmm0                        
6657a94  movss xmm0,[r13+0x124]                        
6657a9d  movss [r12+0x124],xmm0                        
6657aa7  mov rax,[r13+0x128]                           
6657aae  mov [r12+0x128],rax                           
6657ab6  add rdi,0x130                                 
6657abd  add r13,0x130                                 
6657ac4  cmp r13,r15                                   
6657ac7  je short 0x6657B04                            ; -> loc_6657b04
6657ac9  movups xmm0,[r14+rdi]                         
6657ace  movups xmm1,[r14+rdi+0x10]                    
6657ad4  movups xmm2,[r14+rdi+0x20]                    
6657ada  movups [rbx+rdi+0x20],xmm2                    
6657adf  movups [rbx+rdi+0x10],xmm1                    
6657ae4  movups [rbx+rdi],xmm0                         
6657ae8  movups [rbx+rdi+0x30],xmm6                    
6657aed  mov rax,[r14+rdi+0x38]                        
6657af2  test rax,rax                                  
6657af5  je 0x66579E0                                  ; -> sub_66579e0
6657afb  lock inc dword ptr [rax+8]                    
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phase 14 (0x6657a0c..0x6657afe, documented above): loop copies full record [r13+0x30..0x128] → [r12+same] (13 scalar fields + 173-byte sub_eec6ec0 at +0x70 + qword +0x128); rdi+=0x130; r13+=0x130; cmp r13,r15; je loc_6657B04 (loop exit); loop-top loc_6657ac9 loads next source record; tail: rax=[r14+rdi+0x38]; test rax,rax; je loc_66579E0 (no ref); else lock inc dword ptr [rax+8] (AddRef entry's +0x38 ref); jmp loc_66579E0 (cut at 0x6657afb). [I] Fully shared compacting loop over stride-0x130 table entries ([r14]=base [rsi+0x540], r15=end). NEXT RVA: 0x6657afe

### Phase 44 — VolumetricFog shared loop-1 tail + loop-2 head (identical to SkyAmbientSamples phases 15-16; misdecodes at 0x6657afe-0x6657b02) [V]
`0x6657afe..0x6657bdc` (40 instr)
```
6657afe  or cl,ch                                      
6657b00  fdiv st(6),st                                 
6657b02  (bad)                                         
6657b04  mov rdi,[rsi+0x548]                           
6657b0b  cmp r15,rdi                                   
6657b0e  je 0x6657DA4                                  ; -> loc_6657da4   (loop-2 exit)
6657b14  mov rax,[rbp+0x540]                           
6657b1b  lea r14,[rax+rbx]                             
6657b1f  add r14,0x130                                 
6657b26  xor r12d,r12d                                 
6657b29  xorps xmm6,xmm6                               
6657b2c  jmp 0x6657C2C                                 ; -> loc_6657c2c
6657b31  nop [rax+rax]                                 
loc_6657b40:  ; from 6657c5c, 6657c66
6657b40  lea r13,[r15+r12]                             
6657b44  mov rax,[r13+0x30]                            
6657b48  mov [r14+r12+0x30],rax                        
6657b4d mov rax,[r13+0x38]                            
6657b51 mov [r14+r12+0x38],rax                        
6657b56 movss xmm0,[r13+0x40]                         
6657b5c movss [r14+r12+0x40],xmm0                     
6657b63 movss xmm0,[r13+0x44]                         
6657b69 movss [r14+r12+0x44],xmm0                     
6657b70 movss xmm0,[r13+0x48]                         
6657b76 movss [r14+r12+0x48],xmm0                     
6657b7d movss xmm0,[r13+0x4C]                         
6657b83 movss [r14+r12+0x4C],xmm0                     
6657b8a movss xmm0,[r13+0x50]                         
6657b90 movss [r14+r12+0x50],xmm0                     
6657b97 movups xmm0,[r13+0x54]                        
6657b9c movups [r14+r12+0x54],xmm0                    
6657ba2 movss xmm0,[r13+0x64]                         
6657ba8 movss [r14+r12+0x64],xmm0                     
6657baf movss xmm0,[r13+0x68]                         
6657bb5 movss [r14+r12+0x68],xmm0                     
6657bbc movss xmm0,[r13+0x6C]                         
6657bc2 movss [r14+r12+0x6C],xmm0                     
6657bc9 lea rcx,[r14+r12]                             
6657bcd add rcx,0x70                                  
6657bd1 lea rdx,[r13+0x70]                            
6657bd5 mov r8d,0xAD                                  
```
// [V] 0x6657afe-0x6657b02: `or cl,ch`, `fdiv st(6),st`, `(bad)` — SAME displacement-byte misdecode class (jmp near 0x66579E0 bytes linearly misdecoded); NOT real instructions; real flow resumes at `mov rdi,[rsi+0x548]` 0x6657b04 (the `jmp 0x66579E0` at 0x6657aff is a 5-byte near jmp ending exactly at 0x6657b04). [V] Rest INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 15-16 (0x6657b04..0x6657bd5, documented above): loop-1 tail ends; rdi=[rsi+0x548]; if r15==rdi → loc_6657DA4 (loop-2 exit); r14=[rbp+0x540]+rbx+0x130; r12d=0; xorps xmm6; jmp loc_6657C2C. loc_6657b40 (loop-2 body head): r13=r15+r12; copy record fields [r13+0x30..0x6C] → [r14+r12+same] (cut at mov r8d,0xAD). [I] Fully shared compacting loops. NEXT RVA: 0x6657bdc

### Phase 45 — VolumetricFog shared loop-2 tail + loop-3 head (identical to SkyAmbientSamples phases 16-17; misdecoded call disp bytes at 0x6657bdc/0x6657bde) [V]
`0x6657bdc..0x6657cb4` (40 instr)
```
6657bdc  loopne 0x6657BD0                              ; -> sub_6657bd0
6657bde  xchg [rax],cl                                 
6657be0  movss xmm0,[r13+0x120]                        
6657be9  movss [r14+r12+0x120],xmm0                    
6657bf3  movss xmm0,[r13+0x124]                        
6657bfc  movss [r14+r12+0x124],xmm0                    
6657c06  mov rax,[r13+0x128]                           
6657c0d  mov [r14+r12+0x128],rax                       
6657c15  add r12,0x130                                 
6657c1c  add r13,0x130                                 
6657c23  cmp r13,rdi                                   
6657c26  je 0x6657DA4                                  ; -> loc_6657da4
6657c2c  movups xmm0,[r15+r12]                         
6657c31  movups xmm1,[r15+r12+0x10]                    
6657c37  movups xmm2,[r15+r12+0x20]                    
6657c3d  movups [r14+r12+0x20],xmm2                    
6657c43  movups [r14+r12+0x10],xmm1                    
6657c49  movups [r14+r12],xmm0                         
6657c4e  movups [r14+r12+0x30],xmm6                    
6657c54  mov rax,[r15+r12+0x38]                        
6657c59  test rax,rax                                  
6657c5c  je 0x6657B40                                  ; -> sub_6657b40
6657c62  lock inc dword ptr [rax+8]                    
6657c66  jmp 0x6657B40                                 ; -> sub_6657b40
6657c6b  cmp r14,r15                                   
6657c6e  je 0x6657DAB                                  ; -> loc_6657dab
6657c74  xor edi,edi                                   
6657c76  xorps xmm6,xmm6                               
6657c79  jmp 0x6657D69                                 ; -> loc_6657d69
6657c7e  xchg ax,ax                                    

loc_6657c80:  ; from 6657d95, 6657d9f
6657c80  lea r13,[rbx+rdi]                             
6657c84  lea r12,[r14+rdi]                             
6657c88  mov rax,[r12+0x30]                            
6657c8d  mov [r13+0x30],rax                            
6657c91  mov rax,[r12+0x38]                            
6657c96  mov [r13+0x38],rax                            
6657c9a  movss xmm0,[r12+0x40]                         
6657ca1  movss [r13+0x40],xmm0                         
6657ca7  movss xmm0,[r12+0x44]                         
6657cae  movss [r13+0x44],xmm0                         
```
 // [V] 0x6657bdc/0x6657bde: `loopne 0x6657BD0`, `xchg [rax],cl` — displacement-byte misdecodes of the `call 0xEEC6EC0` at 0x6657bdb (phase-44 `mov r8d,0xAD` at 0x6657bd5 is 6 bytes ending at 0x6657bdb; call spans 0x6657bdb..0x6657be0); NOT real instructions — same misdecode class as 0x66575a6/0x66575a8, 0x665751c/0x665751e, 0x66575c8-0x66575ce, 0x6657afe-0x6657b02. Real flow resumes at 0x6657be0. [V] Rest INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 16-17 (0x6657be0..0x6657cae): loop-2 tail stores [r14+r12+0x120/0x124/0x128] = [r13+same]; r12 += 0x130; r13 += 0x130; cmp r13,rdi ([rsi+0x548]); je loc_6657DA4 (loop-2 exit). [V] Loop-2 head 0x6657c2c: movups [r14+r12+0x20,0x10,0x00] = [r15+r12+same]; [r14+r12+0x30] = xmm6; rax = [r15+r12+0x38]; test rax,rax; if 0 → loc_6657b40 (loop-2 body copies +0x30+ fields); else lock inc dword [rax+8] (AddRef entry's +0x38 ref); jmp loc_6657b40. [V] Block 0x6657c6b (end of loop-2 / loop-3 entry): cmp r14,r15; je loc_6657DAB; else edi = 0; xorps xmm6; jmp 0x6657D69 (loop-3 head; copies [r14+rdi+0x00,0x10,0x20] → [rbx+rdi+0x20,0x10,0x00]). [V] Loop-3 body loc_6657c80 (back-edges from tail 0x6657d95/0x6657d9f): r13 = rbx + rdi (dest); r12 = r14 + rdi (src); [r13+0x30] = [r12+0x30]; [r13+0x38] = [r12+0x38]; movss [r13+0x40] = [r12+0x40]; movss [r13+0x44] = [r12+0x44] (cut at 0x6657cae; continues at 0x6657cb4 per SkyAmbientSamples phase-17 mirror). [I] Fully shared compacting loops; loop-2 exits loc_6657DA4 (0x6657c26) / loc_6657DAB (0x6657c6e); loop-3 continues phase 46. NEXT RVA: 0x6657cb4

### Phase 46 — VolumetricFog shared loop-3 body end + head/tail (identical to SkyAmbientSamples phases 17-18) [V]
`0x6657cb4..0x6657da4` (40 instr)
```
6657cb4  movss xmm0,[r12+0x48]                         
6657cbb  movss [r13+0x48],xmm0                         
6657cc1  movss xmm0,[r12+0x4C]                         
6657cc8  movss [r13+0x4C],xmm0                         
6657cce  movss xmm0,[r12+0x50]                         
6657cd5  movss [r13+0x50],xmm0                         
6657cdb  movups xmm0,[r12+0x54]                        
6657ce1  movups [r13+0x54],xmm0                        
6657ce6  movss xmm0,[r12+0x64]                         
6657ced  movss [r13+0x64],xmm0                         
6657cf3  movss xmm0,[r12+0x68]                         
6657cfa  movss [r13+0x68],xmm0                         
6657d00  movss xmm0,[r12+0x6C]                         
6657d07  movss [r13+0x6C],xmm0                         
6657d0d  lea rcx,[r13+0x70]                            
6657d11  lea rdx,[r12+0x70]                            
6657d16  mov r8d,0xAD                                  
6657d1c  call 0xEEC6EC0                                ; -> sub_eec6ec0
6657d21  movss xmm0,[r12+0x120]                        
6657d2b  movss [r13+0x120],xmm0                        
6657d34  movss xmm0,[r12+0x124]                        
6657d3e  movss [r13+0x124],xmm0                        
6657d47  mov rax,[r12+0x128]                           
6657d4f  mov [r13+0x128],rax                           
6657d56  add rdi,0x130                                 
6657d5d  add r12,0x130                                 
6657d64  cmp r12,r15                                   
6657d67  je short 0x6657DA4                            ; -> loc_6657da4
6657d69  movups xmm0,[r14+rdi]                         
6657d6e  movups xmm1,[r14+rdi+0x10]                    
6657d74  movups xmm2,[r14+rdi+0x20]                    
6657d7a  movups [rbx+rdi+0x20],xmm2                    
6657d7f  movups [rbx+rdi+0x10],xmm1                    
6657d84  movups [rbx+rdi],xmm0                         
6657d88  movups [rbx+rdi+0x30],xmm6                    
6657d8d  mov rax,[r14+rdi+0x38]                        
6657d92  test rax,rax                                  
6657d95  je 0x6657C80                                  ; -> sub_6657c80
6657d9b  lock inc dword ptr [rax+8]                    
6657d9f  jmp 0x6657C80                                 ; -> sub_6657c80
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phases 17-18 (0x6657cb4..0x6657d9f): loop-3 body continues [r13+0x48/0x4C/0x50/0x54/0x64/0x68/0x6C] = [r12+same]; lea rcx=[r13+0x70]; lea rdx=[r12+0x70]; r8d=0xAD (173); call sub_eec6ec0 [I] 173-byte copy [r12+0x70]→[r13+0x70]; [r13+0x120]=[r12+0x120]; [r13+0x124]=[r12+0x124]; [r13+0x128]=[r12+0x128]; rdi += 0x130; r12 += 0x130; cmp r12,r15; je short loc_6657DA4 (loop-3 exit). [V] Loop-3 head 0x6657d69 (from 0x6657c79 jmp): movups [rbx+rdi+0x20,0x10,0x00] = [r14+rdi+0x20,0x10,0x00]; 0x6657d88: [rbx+rdi+0x30] = xmm6 (=0); rax = [r14+rdi+0x38]; test rax,rax; if 0 → loc_6657c80 (loop-3 body, no ref); else lock inc dword [rax+8] (AddRef entry's +0x38 ref); jmp loc_6657c80. [I] Loop-3 = third compaction pass over stride-0x130 table ([r14]=base [rsi+0x540], r15=end cursor, dest base rbx); exit loc_6657DA4 (0x6657d67) leads into epilogue at 0x6657da4. NEXT RVA: 0x6657da4

### Phase 47 — VolumetricFog shared epilogue release loop + heap check (identical to SkyAmbientSamples phase 18) [V]
`0x6657da4..0x6657e4a` (40 instr)
```
6657da4  mov r14,[rsi+0x540]                           
6657dab  test r14,r14                                  
6657dae  mov r13,[rbp-0x28]                            
6657db2  je 0x6657E52                                  ; -> loc_6657e52
6657db8  mov rdi,[rsi+0x548]                           
6657dbf  cmp r14,rdi                                   
6657dc2  jne short 0x6657DDC                           ; -> loc_6657ddc
6657dc4  jmp short 0x6657E1B                           ; -> loc_6657e1b
6657dc6  nop [rax+rax]                                 

loc_6657dd0:  ; from 6657de3, 6657dea, 6657e00, 6657e12
6657dd0  add r14,0x130                                 
6657dd7  cmp r14,rdi                                   
6657dda  je short 0x6657E14                            ; -> loc_6657e14

loc_6657ddc:  ; from 6657dc2
6657ddc  mov r15,[r14+0x38]                            
6657de0  test r15,r15                                  
6657de3  je short 0x6657DD0                            ; -> loc_6657dd0
6657de5  lock dec dword ptr [r15+8]                    
6657dea  jne short 0x6657DD0                           ; -> loc_6657dd0
6657dec  mov rax,[r15]                                 
6657def  mov rax,[rax]                                 
6657df2  mov rcx,r15                                   
6657df5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657dfb  lock dec dword ptr [r15+0xC]                  
6657e00  jne short 0x6657DD0                           ; -> loc_6657dd0
6657e02  mov rax,[r15]                                 
6657e05  mov rax,[rax+8]                               
6657e09  mov rcx,r15                                   
6657e0c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
6657e12  jmp short 0x6657DD0                           ; -> loc_6657dd0

loc_6657e14:  ; from 6657dda
6657e14  mov r14,[rsi+0x540]                           

loc_6657e1b:  ; from 6657dc4
6657e1b  mov rdx,[rsi+0x550]                           
6657e22  sub rdx,r14                                   
6657e25  cmp rdx,0x1000                                
6657e2c  jb short 0x6657E4A                            ; -> loc_6657e4a
6657e2e  mov rax,[r14-8]                               
6657e32  add r14,0xFFFFFFFFFFFFFFF8                    
6657e36  sub r14,rax                                   
6657e39  cmp r14,0x20                                  
6657e3d  jae 0x665D43A                                 ; -> sub_665d43a
6657e43  add rdx,0x27                                  
6657e47  mov r14,rax                                   
```
// [V] INSTRUCTION-IDENTICAL to SkyAmbientSamples phase 18 (0x6657da4..0x6657e47): epilogue — r14 = [rsi+0x540] (stride-0x130 table base); r13 = [rbp-0x28]; if r14 == 0 → loc_6657E52 (skip release); rdi = [rsi+0x548] (end); if r14 == rdi → loc_6657E1B; else loc_6657ddc: r15 = [r14+0x38] (entry ref); if 0 → next (loc_6657dd0); lock dec dword [r15+8]; if != 0 → next; two-stage destroy: call sub_eea6040 (stage-1); lock dec dword [r15+0xC]; if != 0 → next; call sub_eea6040 (stage-2/free); loc_6657dd0: r14 += 0x130; cmp r14,rdi; je loc_6657e14. [V] loc_6657e14: r14 = [rsi+0x540] (rebase to base). loc_6657e1b: rdx = [rsi+0x550] - [rsi+0x540] (alloc size); if rdx < 0x1000 → loc_6657e4a; else rax = [r14-8] (heap size header); r14 += -8; r14 -= rax; if r14 >= 0x20 → sub_665d43a; rdx += 0x27; r14 = rax (cut at mov r14,rax 0x6657e47, lands exactly on loc_6657e4a). [V] Releases every remaining AddRef'd entry (+0x38 refs) — final case wind-down; buffer free via sub_e935700 follows at phase 48 (0x6657e4a). NEXT RVA: 0x6657e4a
