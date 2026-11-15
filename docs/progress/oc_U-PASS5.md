# Progress: U-PASS5 (reverse-engineer sub_55f1450 fully)

## NEXT
- Task 1: Need more rdis dis output for entry region beyond 0x55f1450+80 instr (currently have exact lines through 0x55f15dd + truncated at --max 80). Continue phases 2+ for argument spill/locals/loop B through ~400 instr, each phase ≤40 instr, exact `0xRVA  instruction` quotes with [V]/[I]/[?] tags.
- Task 2: String refs table below is COMPLETE (first 15 distinct strings with offsets, verified via rdis str output in prior session). No further action needed.
- Task 3: Xref results below are COMPLETE (0 direct callers, 0 ripscans — invoked only indirectly via vtable/lambda/jump table). No further action needed unless ripscan.py 0x55f1450 needs re-running to check vtable slots/lambda objects.
- Task 4: Stride loop exact disassembly below is COMPLETE (0x55f164a..0x55f1810, 150 instr). Need to explain what 0x18-byte entries {0, DrawItem*, r13} are used for next (who reads them: entry vector begin/end stored where?).
- Only edit docs/progress/oc_U-PASS5.md. Keep NEXT block at top. Tag every claim.

## EXE / SOURCE [V]
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
- rdis binary: tools/rdis/target/release/rdis.exe
- Static analysis only. Never commit. Never edit src/ except named header.

## BOUNDS [V]
- `sub_55f1450 [0x55f1450..0x563f594), size 0x4e144, 0 direct callers` (rdis xr 0x55f1450 -> 0 xrefs; ripscan 0x55f1450 -> none).
- PASS4B identified sub_562bb00 as INTERIOR region of sub_55f1450 (not a separate function).
- Entry garbage note: 0x55f1640 starts with garbage bytes; real stride-loop code starts at 0x55f164a.

## TASK 1 — ENTRY TRANSCRIPTION (~400 instr, phases ≤40 instr) [V/I]

### Phase 1: Prologue 0x55f1450..0x55f14c2 — save regs + stack probe + xmm saves
```
55f1450  push rbp                                      
55f1451  push r15                                      
55f1453  push r14                                      
55f1455  push r13                                      
55f1457  push r12                                      
55f1459  push rsi                                      
55f145a  push rdi                                      
55f145b  push rbx                                      
55f145c  mov eax,0x3398                                
55f1461  call 0xE9E7970                                ; -> sub_e9e7970
55f1466  sub rsp,rax                                   
55f1469  lea rbp,[rsp+0x80]                            
55f1471  movdqa [rbp+0x3300],xmm15                     
55f147a  movaps [rbp+0x32F0],xmm14                     
55f1482  movaps [rbp+0x32E0],xmm13                     
55f148a  movaps [rbp+0x32D0],xmm12                     
55f1492  movdqa [rbp+0x32C0],xmm11                     
55f149b  movdqa [rbp+0x32B0],xmm10                     
55f14a4  movaps [rbp+0x32A0],xmm9                      
55f14ac  movaps [rbp+0x3290],xmm8                      
55f14b4  movaps [rbp+0x3280],xmm7                      
55f14bb  movaps [rbp+0x3270],xmm6                      
```
Interpretation: Standard prologue: push 8 GPRs (rbp,r15,r14,r13,r12,rsi,rdi,rbx), allocate 0x3398 bytes of stack via stack probe sub_e9e7970, set frame pointer rbp=rsp+0x80, save xmm15..xmm7 at [rbp+0x3300] down to [rbp+0x3270] (10 slots stride 0x10; xmm15..xmm8 at +0x3300..+0x3280 per prior finding). [V]

### Phase 2: Prologue tail + argument spill 0x55f14c2..0x55f1504 — sentinel + arg spills + container fields
```
55f14c2  mov qword ptr [rbp+0x3268],0xFFFFFFFFFFFFFFFE 
55f14cd  mov [rbp+0x3260],rdx                          
55f14d4  mov [rbp+0x3140],rcx                          
55f14db  mov rdx,[r8+0xA10]                            
55f14e2  mov rax,[r8+0xA78]                            
55f14e9  mov rax,[rax]                                 
55f14ec  mov [rbp+0x3238],r8                           
55f14f3  lea rcx,[r8+0xA10]                            
55f14fa  mov [rbp+0x2EB0],rcx                          
55f1501  cmp rdx,rcx                                   
55f1504  mov [rbp+0x22F0],r9                           
```
Interpretation: Store sentinel -2 at [rbp+0x3268]; spill arg2=rdx to [rbp+0x3260]; spill arg1=rcx to [rbp+0x3140]; load container field [r8+0xA10] into rdx (list head); load [r8+0xA78] then dereference [rax] (vtable/obj ptr) into rax; spill arg3=r8=container to [rbp+0x3238]; compute list head = r8+0xA10, store to [rbp+0x2EB0]; compare rdx (list head) with rcx (also list head); spill arg4=r9 to [rbp+0x22F0]. [V]

### Phase 3: Arguments [V]
| Register | Meaning | Spill location | Tag |
|----------|---------|----------------|-----|
| rcx | arg1 | [rbp+0x3140] | V |
| rdx | arg2 | [rbp+0x3260] | V |
| r8 | arg3 = container ptr | [rbp+0x3238] | V |
| r9 | arg4 | [rbp+0x22F0] | V |

Container field reads: [r8+0xA10] = list head; [r8+0xA78] -> mov rax,[rax] -> [rbp+0x3210] (vtable/obj ptr). [rbp+0x3260] passed to sub_56ba620 calls later. [V]

### Phase 4: Loop B item count 0x55f1511..0x55f1549 — magic-multiply divide by 5
```
55f1511  xor r14d,r14d                                 
55f1514  mov rcx,0x8F5C28F5C28F5C29                    
55f151e  mov r10,rdx                                   
55f1521  mov r9,[rbp+0x2EB0]                           
55f1528  nop [rax+rax]                                 
55f1530  mov r8,[rdx+0x18]                             
55f1534  sub r8,[rdx+0x10]                             
55f1538  mov rdx,[rdx]                                 
55f153b  sar r8,3                                      
55f153f  imul r8,rcx                                   
55f1543  add r14,r8                                    
55f1546  cmp rdx,r9                                    
55f1549  jne short 0x55F1530                           ; -> loc_55f1530
```
Interpretation: r14=item count accumulator; rcx=magic 0x8F5C28F5C28F5C29 (divide by 5 via multiply-high); r10=rdx (current node); r9=list head end sentinel. Loop: for each node, r8=[rdx+0x18]-[rdx+0x10] (span/8), sar 3 (divide by 8), imul rcx (magic), add to r14; rdx=[rdx] (next node); continue until rdx==r9 (back at head). Counts items across a circular doubly-linked list of blocks. [V]

### Phase 5: Loop B exit + vector alloc 0x55f154b..0x55f15b0
```
55f154b  mov rax,[rax+0x40]                            
55f154f  mov [rbp+0x3210],rax                          
55f1556  test r14,r14                                  
55f1559  je 0x55F162C                                  ; -> loc_55f162c
55f155f  mov rax,0xAAAAAAAAAAAAAAB                     
55f1569  cmp r14,rax                                   
55f156c  jae 0x563EAF6                                 ; -> sub_563eaf6
55f1572  lea rax,[r14*8]                               
55f157a  lea r8,[rax+rax*2]                            
55f157e  mov rax,[rbp+0x3210]                          
55f1585  mov rcx,[rax]                                 
55f1588  lea rdx,[rbp+0x27A0]                          
55f158f  mov r9d,1                                     
55f1595  call 0xA78940                                 ; -> sub_a78940
55f159a  nop                                           
55f159b  mov rsi,[rbp+0x27B0]                          
55f15a2  mov rax,[rbp+0x27A0]                          
55f15a9  mov rbx,[rbp+0x27A8]                          
55f15b0  mov rdi,[rax]                                 
```
Interpretation: rax=[rax+0x40] -> [rbp+0x3210] (object ptr). If count==0, jump to loc_55f162c. If count >= 0xAAAAAAAAAAAAAAB, error path sub_563eaf6. Compute size=count*3 (lea rax,[r14*8]; lea r8,[rax+rax*2] = count*24). rax=[rbp+0x3210]; rcx=[rax]; rdx=&[rbp+0x27A0] (out ptr); r9d=1; call sub_a78940 (vector alloc/grow). After call: rsi=[rbp+0x27B0] (old base?), rax=[rbp+0x27A0] (new base), rbx=[rbp+0x27A8] (old ptr for refcount release), rdi=[rax] (new vector base). [V]

### Phase 6: Refcount release + jump to stride loop 0x55f15b3..0x55f15dd (truncated at --max 80)
```
55f15b3  test rbx,rbx                                  
55f15b6  je short 0x55F15E3                            ; -> loc_55f15e3
55f15b8  lock dec dword ptr [rbx+8]                    
55f15bc  jne short 0x55F15E3                           ; -> loc_55f15e3
55f15be  mov rax,[rbx]                                 
55f15c1  mov rax,[rax]                                 
55f15c4  mov rcx,rbx                                   
55f15c7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
55f15cd  lock dec dword ptr [rbx+0xC]                  
55f15d1  jne short 0x55F15E3                           ; -> loc_55f15e3
55f15d3  mov rax,[rbx]                                 
55f15d6  mov rax,[rax+8]                               
55f15da  mov rcx,rbx                                   
55f15dd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
Interpretation: Refcount decrement on old vector buffer rbx (lock dec [rbx+8]; if zero, call sub_eea6040 via [0xF99FFA0]; lock dec [rbx+0xC]; if zero, call sub_eea6040 again with [rbx]). Then fall through to stride loop (rdi=new vector base, r14=count). [V]

### Locals seen so far [V/I]
| Local | Meaning | Tag |
|-------|---------|-----|
| [rbp+0x3268] | sentinel -2 | V |
| [rbp+0x3260] | arg2 spill | V |
| [rbp+0x3140] | arg1 spill | V |
| [rbp+0x3238] | arg3=container spill | V |
| [rbp+0x2EB0] | container+0xA10 list head | V |
| [rbp+0x22F0] | arg4 spill | V |
| [rbp+0x3210] | vtable/obj ptr from [r8+0xA78]->[rax] | V |
| [rbp+0x27A0] | vector alloc out-param (base ptr) | V |
| [rbp+0x27B0] | vector old base (for refcount release) | V |
| [rbp+0x27A8] | vector old ptr (for refcount release) | V |
| [rbp+0x31F0] | block iter ptr (used in stride loop) | V |
| [rbp+0x3240] | block end (used in stride loop) | V |

Remaining entry region (~0x55f15e3 onward through ~0x55f1810) to be transcribed in NEXT phases. [I]

## TASK 2 — STRING REFS INSIDE sub_55f1450 [V]
First 15 distinct strings (addr : string : sub_55f1450+offset xrefs):

| # | String addr | String | sub_55f1450 xref offsets |
|---|-------------|--------|--------------------------|
| 1 | f539a84 | "Core/Screen/Blit" | +0x1a308, +0x1a922, +0x20662, +0x417b2, +0x42e0f, +0x4ac23 |
| 2 | f51a87c | "DebugWaterDepthBufferCopy" | +0x20757 |
| 3 | f51a896 | "DebugDepthBufferCopy" | +0x1a3f2 |
| 4 | f52cf20 | "DepthOnlyAlphaTest" | +0x18044 |
| 5 | f539a1c | "SSRColorBufferBlit" | +0x32164, +0x321ae |
| 6 | f539a2f | "WaterDepthBufferBlit" | +0x19f2a, +0x19f73 |
| 7 | f5427d1 | "VolumetricsShadows" | +0xad79 |
| 8 | f5427e4 | "SampleCascadedShadows" | +0xb038, +0xb088 |
| 9 | f55a70a | "Shadow Cascades" | +0x23ed |
| 10 | f55b3ec | "ClusterDepthBounds" | +0x45e8b |
| 11 | f56ea45 | "BlitFSRToBackBuffer" | +0x418bc |
| 12 | f5975f6 | "BlitColorCorrectedUIToScreen" | +0x42f34 |
| 13 | f5a62bd | "ScreenSpaceWaterFrontFaceDepthAndNormal" | +0x46bcf |
| 14 | f5a62e5 | "ScreenSpaceWaterBackFaceDepthAndNormal" | +0x46c46 |
| 15 | f5f440c | "BlitUncompressed" | +0x1aa4f |

Additional strings inside sub_55f1450: f5256d5 CascadedShadowBufferOut +0x466b7; f56ec0e PreviousCascadedShadowBuffer +0x467a5; f5850f7 PointLightShadowAtlasResolution +0x45d9d; f58a612 DirectionalLightSourceShadowDirection +0x45187; f5acc9a CascadesShadowProj +0x46552; f5accad PlayerShadowProj +0x4571b; f5accbe CloudShadowProj +0x4562d; f5acd10 CascadesShadowInvProj +0x465c9; f5ae68c ShadowFilterOffset... +0x45880; f5daa1b DirectionalShadowMode... +0x44c6a; f5dcac9 CloudShadowsVisible +0x456a4; f7dde72 PointLightShadowParams1 +0x45e14; f63ee26 [ClearDepth][ItemInHandObject] +0x341ee; f640f15 [ClearGBuffer][ScenePrepass] +0xe20b; f669768 [ClearColor][ForceRasterization] +0x3d2b6; f66c679 [ClearStencil][WaterSurfaceStencil] +0x19bfa; f6950bb [ClearStencil][ForwardPBR] +0x20a78; f6950bb [ClearDepth][EntitiesInUI] +0x4cac6; f6950d6 [ClearColorDepth][ColorCorrectedUI] +0x41d73. [V]

=> sub_55f1450 is a RENDER-GRAPH/FRAMEGRAPH PASS EXECUTOR: pass-name keyed, clear/blit/copy/depth/shadow ops. [V]

## TASK 3 — WHO REFERENCES sub_55f1450 [V]
- `rdis xr 0x55f1450` -> 0 xrefs (NO direct callers). [V]
- ripscan 0x55f1450 -> none. [V]
- => invoked ONLY indirectly (vtable slot / lambda object / jump table / indirect call). [V]
- CALLEES seen inside sub_55f1450: sub_a78940 (vector alloc/grow), sub_eea6040 (refcount dec via [0xF99FFA0]), sub_eec6de0 (memcpy), sub_5689800 (sort/finalize vector), sub_56ba620, sub_bb418d0, sub_bb45050, sub_e9e7970 (stack probe). [V]

## TASK 4 — STRIDE LOOP 0x55f1640..0x55f1810 [V]
Exact disassembly (rdis dis 0x55f164a 150; real code starts at 0x55f164a — 0x55f1640 is garbage):

```
55f164a  mov r8,rdx                                    
55f164d  mov rcx,[rbp+0x3238]                          
55f1654  add rcx,0x9D0                                 
55f165b  mov [rbp+0x1F78],rcx                          
55f1662  mov rbx,rdi                                   
55f1665  jmp short 0x55F1687                           ; -> loc_55f1687
55f1667  nop [rax+rax]                                 
loc_55f1670:  ; from 55f1699, 55f16cd
55f1670  mov r8,[rbp+0x31F0]                           
55f1677  mov r8,[r8]                                   
55f167a  cmp r8,[rbp+0x2EB0]                           
55f1681  je 0x55F17F7                                  ; -> loc_55f17f7
loc_55f1687:  ; from 55f1665
55f1687  mov r14,[r8+0x10]                             
55f168b  mov rcx,[r8+0x18]                             
55f168f  cmp r14,rcx                                   
55f1692  mov [rbp+0x31F0],r8                           
55f1699  je short 0x55F1670                            ; -> loc_55f1670
55f169b  lea r13,[r8+0x28]                             
55f169f  mov [rbp+0x3240],rcx                          
55f16a6  jmp short 0x55F16CF                           ; -> loc_55f16cf
55f16a8  nop [rax+rax]                                 
loc_55f16b0:  ; from 55f16d9
55f16b0  mov qword ptr [rbx],0                         
55f16b7  mov [rbx+8],r14                               
55f16bb  mov [rbx+0x10],r13                            
55f16bf  add rbx,0x18                                  
loc_55f16c3:  ; from 55f16d4, 55f17f2
55f16c3  add r14,0xC8                                  
55f16ca  cmp r14,rcx                                   
55f16cd  je short 0x55F1670                            ; -> loc_55f1670
loc_55f16cf:  ; from 55f16a6
55f16cf  test byte ptr [r14+0xB],4                     
55f16d4  je short 0x55F16C3                            ; -> loc_55f16c3
55f16d6  cmp rbx,rax                                   
55f16d9  jne short 0x55F16B0                           ; -> loc_55f16b0
55f16db  mov [rbp+0x3220],rdi                          
55f16e2  sub rbx,rdi                                   
55f16e5  mov rax,rbx                                   
55f16e8  sar rax,3                                     
55f16ec  mov rcx,0xAAAAAAAAAAAAAAAB                    
55f16f6  imul rax,rcx                                  
55f16fa  lea rsi,[rax+1]                               
55f16fe  mov rdi,rax                                   
55f1701  shr rdi,1                                     
55f1704  mov rdx,0xAAAAAAAAAAAAAAA                     
55f170e  mov rcx,rdx                                   
55f1711  sub rcx,rdi                                   
55f1714  add rdi,rax                                   
55f1717  cmp rdi,rsi                                   
55f171a  cmovbe rdi,rsi                                
55f171e  cmp rax,rcx                                   
55f1721  cmova rdi,rdx                                 
55f1725  lea rax,[rdi*8]                               
55f172d  lea r8,[rax+rax*2]                            
55f1731  mov rax,[rbp+0x3210]                          
55f1738  mov rcx,[rax]                                 
55f173b  mov r9d,1                                     
55f1741  lea rdx,[rbp+0x27A0]                          
55f1748  call 0xA78940                                 ; -> sub_a78940
55f174d  nop                                           
55f174e  mov rcx,[rbp+0x27B0]                          
55f1755  mov rax,[rbp+0x27A0]                          
55f175c  mov r12,[rbp+0x27A8]                          
55f1763  mov r15,[rax]                                 
55f1766  test r12,r12                                  
55f1769  je short 0x55F17B1                            ; -> loc_55f17b1
55f176b  lock dec dword ptr [r12+8]                    
55f1771  jne short 0x55F17B1                           ; -> loc_55f17b1
55f1773  mov rax,[r12]                                 
55f1777  mov rax,[rax]                                 
55f177a  mov [rbp+0x3200],rcx                          
55f1781  mov rcx,r12                                   
55f1784  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
55f178a  mov rcx,[rbp+0x3200]                          
55f1791  lock dec dword ptr [r12+0xC]                  
55f1797  jne short 0x55F17B1                           ; -> loc_55f17b1
55f1799  mov rax,[r12]                                 
55f179d  mov rax,[rax+8]                               
55f17a1  mov rcx,r12                                   
55f17a4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
55f17aa  mov rcx,[rbp+0x3200]                          
loc_55f17b1:  ; from 55f1769, 55f1771, 55f1797
55f17b1  add r15,rcx                                   
55f17b4  mov qword ptr [rbx+r15],0                     
55f17bc  mov [rbx+r15+8],r14                           
55f17c1  mov [rbx+r15+0x10],r13                        
55f17c6  mov rcx,r15                                   
55f17c9  mov rdx,[rbp+0x3220]                          
55f17d0  mov r8,rbx                                    
55f17d3  call 0xEEC6DE0                                ; -> sub_eec6de0
55f17d8  lea rax,[rsi+rsi*2]                           
55f17dc  lea rbx,[r15+rax*8]                           
55f17e0  lea rax,[rdi+rdi*2]                           
55f17e4  lea rax,[r15+rax*8]                           
55f17e8  mov rdi,r15                                   
55f17eb  mov rcx,[rbp+0x3240]                          
55f17f2  jmp 0x55F16C3                                 ; -> loc_55f16c3
loc_55f17f7:  ; from 55f1681
55f17f7  cmp rdi,rbx                                   
55f17fa  mov r14,[rbp+0x22F0]                          
55f1801  je 0x563E89B                                  ; -> sub_563e89b
55f1807  mov r15,rbx                                   
55f180a  sub r15,rdi                                   
55f180d  mov r14,r15                                   
55f1810  sar r14,3                                     
```

### Phase interpretation of stride loop [V/I]

**Setup (0x55f164a..0x55f1665):** r8=rdx (block ptr from outer loop); rcx=[rbp+0x3238]+0x9D0 (=container+0x9D0, block list end) -> [rbp+0x1F78]; rbx=rdi (entry vector base); jump to loc_55f1687. [V]

**Block advance (loc_55f1670):** r8=[rbp+0x31F0] (saved block ptr); r8=[r8] (next block via link); if r8==[rbp+0x2EB0] (list head) -> done (loc_55f17f7). [V]

**Record iteration (loc_55f1687):** r14=[r8+0x10] = record cur ptr; rcx=[r8+0x18] = record end ptr; if cur==end, next block; else r13=lea[r8+0x28] (record data start); save end to [rbp+0x3240]; jump to filter. [V]

**Record filter (loc_55f16cf):** test byte ptr [r14+0xB],4; if not set -> skip (advance r14 by 0xC8). If set -> check room (cmp rbx,rax; jne write). [V]

**Write entry (loc_55f16b0):** `mov qword ptr [rbx],0; mov [rbx+8],r14; mov [rbx+0x10],r13; add rbx,0x18` — writes 0x18-byte entry {0, record_cur_ptr=r14, record_data_start=r13}. [V]

**Stride (loc_55f16c3):** add r14,0xC8 (200 bytes per record stride); if r14==rcx (end) -> next block; else loop back to filter. [V]

**Vector grow (exit when full):** [rbp+0x3220]=rdi; sub rbx,rdi (count bytes); rax=rbx; sar rax,3 (count/8 entries); magic-mul round up -> rsi=entry count; grow vector via sub_a78940; refcount release old buffer r12; then at loc_55f17b1 write entry at [rbx+r15] (r15=old offset), memcpy via sub_eec6de0, update rbx=r15+count*24, rdi=r15, rcx=[rbp+0x3240], loop back to stride. [V]

**Loop exit (loc_55f17f7):** cmp rdi,rbx; if empty -> sub_563e89b. Else r15=rbx-rdi (total bytes); r14=r15; sar r14,3 (entry count); call sub_5689800 (sort/finalize vector) with rcx=rdi (begin), rdx=rbx (end), r8=count. Then grow vector again via sub_a78940, refcount release, memcpy at loc_55f18b9. [V]

### What 0x18-byte entries {0, DrawItem*, r13} are used for next [I]
Each entry is {qword 0, qword record_cur_ptr (r14), qword record_data_start (r13)}. The entry vector base is rbx (initialized from rdi at 0x55f1662, where rdi=[rax]=[rbp+0x3210] = container+0xA78->[rax] vtable/obj ptr). The end pointer is rax (computed during allocation/grow). After the stride loop completes, the vector range [rdi, rbx) is passed to sub_5689800 (sort/finalize) at rcx=rdi (begin), rdx=rbx (end), r8=entry count. Entry 0 field appears to be a reserved/tag slot (always written 0). Field +8 = record cursor (which record within block), field +0x10 = record data start (r8+0x28). The sorted/finalized vector is then consumed downstream (likely by the render-graph pass executor to issue draw commands per record). [I]

## FILES
- docs/progress/oc_U-PASS5.md (this file; only file edited for this unit)
- oc_U-PASS4B.md identified sub_562bb00 as interior region of sub_55f1450