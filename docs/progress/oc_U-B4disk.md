# UNIT U-B4disk — dragon::utils::PipelineDiskCache::tick + PSO disk cache (BGFX_MAP 6x)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Raw artifacts: docs/progress/oc_U-B4disk_listing.txt (rdis dis 0xe8feb10 802), oc_U-B4disk_callers.txt (xref.py callers), oc_U-B4disk_callees.txt (rdis callees), oc_U-B4disk_descscan2.txt (descscan2 --reg rsi).

## NEXT
Resume at: run `python tools/sigs/verify_oc.py docs/progress/oc_U-B4disk.md` to validate every quoted `0xRVA  instr` line; then finalize unit.

## Summary
`dragon::utils::PipelineDiskCache::tick` = sub_e8feb10 [0xe8feb10..0xe8fedef) size 0x2df (BGFX_MAP.md L530; rdis fn [V]). Single caller: Frame renderer 0x67c9c20 ("Frame renderer - Frame") calls tick at 0x67ca1c1 [V BGFX_MAP.md L560]. The PSO cache file name is `rd_pipeline_cache.bin` (RVA 0xf593232), referenced only inside the save entry sub_e8fc760 at e8fc7e0 [V]. No load entry point identified in tick's neighbourhood.

## (1) tick 0xe8feb10 — register map, control flow in phases, per-frame behaviour

Register map (entry): rcx = arg1 = this (`dragon::utils::PipelineDiskCache*`) -> rsi [V e8feb31]. rdi = time delta/now value [V e8feb60]. Stack frame base rbp = rsp+0x80 [V e8feb1a]. Stack frame locals: [rbp-0x10] func-name ptr, [rbp-0x8] =0x39, [rbp] file-path ptr, [rbp+0x8] =0x53 source_location line [V e8fec84-e8fec9b]. Object fields touched via rsi(this): +0x000 vtable, +0x008 refcount-low, +0x00c refcount-high, +0x04c state/flag, +0x0d8 enabled byte, +0x0d9 work-in-progress byte, +0x0e0 next-due qword, +0x0e8 cache-object ptr [V descscan2].

What it does each frame: called once per frame from the Frame renderer. Takes a mutex, fast-path returns if disabled or not-due; when due it sets an in-progress flag, grabs the cache object ptr, calls vtable[0x40] on it, builds a source_location + a pair {ptr, refcount|0}, commits via sub_773320, then releases shared_ptr refcounts and returns. If the cache-object ptr is null it tail-jumps to the same-class SAVE entry sub_e8fee80 [I]. Lock failure or state==0x7FFFFFFF triggers a fail-fast poison path (log + write 0x7FFFFFFE + log + int3) [V].

Phase boundaries (each <=40 instructions, every instruction in [0xe8feb10,0xe8fedef) covered):

**Phase A — prologue, mutex lock, fast-path rejects** [e8feb10..e8feb8b]
```
e8feb10  push rbp                                      
e8feb11  push rsi                                      
e8feb12  push rdi                                      
e8feb13  sub rsp,0x110                                 
e8feb1a  lea rbp,[rsp+0x80]                            
e8feb22  movaps [rbp+0x80],xmm6                        
e8feb29  mov qword ptr [rbp+0x78],0xFFFFFFFFFFFFFFFE   
e8feb31  mov rsi,rcx                                    ; this -> rsi
e8feb34  call 0xEEC59F0                                ; mutex lock entry
e8feb39  test eax,eax                                  
e8feb3b  jne 0xE8FEDD3                                 ; lock failed -> lvl5 log path
e8feb41  cmp dword ptr [rsi+0x4C],0x7FFFFFFF           ; R a0+0x4C state/flag
e8feb48  je 0xE8FEDDD                                  ; ==0x7FFFFFFF -> poison path
e8feb4e  cmp byte ptr [rsi+0xD8],1                     ; R a0+0xD8 enabled flag
e8feb55  jne 0xE8FEC45                                 ; disabled -> return
e8feb5b  call 0xEEC5920                                ; now()
e8feb60  mov rdi,rax                                    ; rdi = now (time delta)
e8feb63  call 0xEEC5930                                ; timing query
e8feb68  cmp rdi,0x16E3600                             ; 24,000,000 us == 24 ms
e8feb6f  je short 0xE8FEB90                            ; ==24ms -> ms->us branch
e8feb71  cmp rdi,0x989680                              ; 10,000,000 us == 10 ms
e8feb78  jne short 0xE8FEBF4                           ; !=10ms -> 64-bit div branch
e8feb7a  imul rax,0x64                                 ; rax *= 100
e8feb7e  cmp rax,[rsi+0xE0]                            ; R a0+0xE0 next due time
e8feb85  jge 0xE8FEC3C                                 ; due -> do-work gate
e8feb8b  jmp 0xE8FEC45                                 ; not due -> return
```
C-like: `if (!mutex_trylock()) goto lvl5_log; if (this->state==0x7FFFFFFF) goto poison; if (!this->enabled) return; u64 now = time_now(); if (now==24ms) goto ms_branch; else if (now==10ms) goto div64; else { u64 t = now*100; if (t >= this->next_due) goto do_work; else return; }`

**Phase B1 — 24 ms branch: multiply/divide magic to convert ms->us, compare vs next_due** [e8feb90..e8febf2]
```
e8feb90  mov r9,0xB2F4FC0794908CF3                     
e8feb9a  mov rcx,rax                                   
e8feb9d  imul r9                                        ; rdx:rax = rax * magic
e8feba0  mov r8,rdx                                    
e8feba3  add r8,rcx                                    
e8feba6  mov rax,r8                                    
e8feba9  shr rax,0x3F                                  
e8febad  sar r8,0x18                                   
e8febb1  add r8,rax                                    
e8febb4  imul rax,r8,0x16E3600                          ; subtract quotient*24000000
e8febbb  sub rcx,rax                                    
e8febbe  imul rcx,0x3B9ACA00                            ; *1000000000 (us from ns rem)
e8febc5  mov rax,rcx                                   
e8febc8  imul r9                                        ; second magic divide
e8febcb  mov rax,rdx                                    
e8febce  imul rdx,r8,0x3B9ACA00                         
e8febd5  add rax,rcx                                    
e8febd8  mov rcx,rax                                    
e8febdb  shr rcx,0x3F                                   
e8febdf  sar rax,0x18                                  
e8febe3  add rax,rcx                                    
e8febe6  add rax,rdx                                    
e8febe9  cmp rax,[rsi+0xE0]                            ; R a0+0xE0 next due
e8febf0  jge short 0xE8FEC3C                           ; due -> do-work gate
e8febf2  jmp short 0xE8FEC45                           ; not due -> return
```
C-like: `u64 us = now_ms * 1000000 (via magic multiply); if (us >= this->next_due) goto do_work; else return;`

**Phase B2 — 10 ms / other branch: 64-bit signed/unsigned divide by time delta, compare vs next_due** [e8febf4..e8fec3a]
```
e8febf4  mov rcx,rax                                    
e8febf7  or rcx,rdi                                     
e8febfa  shr rcx,0x20                                   
e8febfe  je short 0xE8FEC07                            ; high dword==0 -> unsigned div
e8fec00  cqo                                            ; signed divide
e8fec02  idiv rdi                                       
e8fec05  jmp short 0xE8FEC0B                           
loc_e8fec07:                                            ; unsigned divide
e8fec07  xor edx,edx                                   
e8fec09  div edi                                        
loc_e8fec0b:
e8fec0b  imul rcx,rax,0x3B9ACA00                        
e8fec12  imul rax,rdx,0x3B9ACA00                        
e8fec19  mov rdx,rax                                    
e8fec1c  or rdx,rdi                                     
e8fec1f  shr rdx,0x20                                   
e8fec23  je short 0xE8FEC2C                           
e8fec25  cqo                                            
e8fec27  idiv rdi                                       
e8fec2a jmp short 0xE8FEC30                           
loc_e8fec2c:
e8fec2c xor edx,edx                                    
e8fec2e div edi                                        
loc_e8fec30:
e8fec30 add rax,rcx                                    
e8fec33 cmp rax,[rsi+0xE0]                            ; R a0+0xE0 next due
e8fec3a jl short 0xE8FEC45                            ; not due -> return
```
C-like: `u64 q = now / delta (signed or unsigned); u64 us = q*1000000000 + rem; if (us < this->next_due) return; else fall to do-work gate.`

**Phase C — due-check gate on +0xD9 work-in-progress; return or enter do-work** [e8fec3c..e8fec59]
```
e8fec3c  cmp byte ptr [rsi+0xD9],1                      ; R a0+0xD9 work-in-progress
e8fec43  jne short 0xE8FEC5E                           ; !=1 -> do-work
loc_e8fec45:                                            ; return path
e8fec45  mov rcx,rsi                                   
e8fec48  movaps xmm6,[rbp+0x80]                        
e8fec4f  add rsp,0x110                                 
e8fec56  pop rdi                                       
e8fec57  pop rsi                                       
e8fec58  pop rbp                                       
e8fec59  jmp 0xEEC5A10                                 ; mutex unlock tail-call
```
C-like: `if (this->work_in_progress != 1) goto do_work; else restore_frame(); return unlock();`

**Phase D — do-work: set in-progress, build source_location, call vtable[0x40], enqueue async save via sub_14a0c0** [e8fec5e..e8fed05]
```
e8fec5e  mov byte ptr [rsi+0xD9],1                      ; W a0+0xD9 = 1 (work in progress)
e8fec65  mov rcx,rsi                                   
e8fec68  call 0xEEC5A10                                ; unlock
e8fec6d  mov rdi,[rsi+0xE8]                            ; R a0+0xE8 cache-object ptr -> rdi
e8fec74  test rdi,rdi                                  
e8fec77  je 0xE8FED25                                  ; null -> tail to SAVE entry sub_e8fee80
e8fec7d  lea rax,[0xF828DF6]                           ; "void __cdecl dragon::utils::PipelineDiskCache::tick(void)"
e8fec84  mov [rbp-0x10],rax                            ; func-name ptr
e8fec88  mov qword ptr [rbp-8],0x39                     ; name length
e8fec90  lea rax,[0xF57AB7F]                           ; "...\Utility\PipelineDiskCache.cpp"
e8fec97  mov [rbp],rax                                 ; file-path ptr
e8fec9b  mov qword ptr [rbp+8],0x53                     ; source_location line 0x53
e8feca3  movaps xmm0,[0xF25D6B0]                       ; source_location storage
e8fecaa movups [rbp+0x10],xmm0                         
e8fecae mov byte ptr [rbp+0x20],0                     
e8fecb2 mov qword ptr [rbp+0x28],0                     
e8fecba xorps xmm6,xmm6                               
e8fecbd movaps [rbp+0x50],xmm6                         
e8fecc1 mov rax,[rdi]                                   ; R cache-object vtable
e8fecc4 mov rax,[rax+0x40]                              ; R vtable[0x40] method ptr
e8fecc8 mov rcx,rdi                                     ; this = cache object
e8feccb call qword ptr [0xF99FFA0]                      ; import thunk -> vcall vtable[0x40](cacheObj)
e8fecd1 nop                                            
e8fecd2 lea rcx,[0xF4F2070]                            ; ptr-table entry (NOT a string, see [UNVERIFIED])
e8fecd9 mov [rbp-0x50],rcx                             
e8fecdd mov [rbp-0x48],rsi                             
e8fece1 movaps [rbp+0x30],xmm6                         
e8fece5 movaps [rbp+0x50],xmm6                         
e8fece9 lea rcx,[rbp-0x50]                             
e8feced mov [rsp+0x28],rcx                             
e8fecf2 mov [rsp+0x20],al                              
e8fecf6 lea rcx,[rbp+0x68]                              ; &pair.first
e8fecfa lea r8,[rbp-0x10]                               ; &func_name
e8fecfe lea r9,[rbp+0x30]                               ; &source_location
e8fed02 mov rdx,rdi                                     ; cache object
e8fed05 call 0x14A0C0                                   ; sub_14a0c0(&pair, cacheObj, &srcloc, &{0}) -> enqueue async save
```
C-like: `this->work_in_progress = 1; unlock(); cacheObj* rdi = this->cache_obj; if (!rdi) goto save_entry; source_location sl = {tick_fn, PipelineDiskCache.cpp, 0x53}; vtable[0x40](rdi); sub_14a0c0(&pair, rdi, &sl, &zero);`

**Phase E — refcount, pair build, sub_773320 commit, shared_ptr releases** [e8fed0a..e8fedc1]
```
e8fed0b xorps xmm0,xmm0                               
e8fed0e movaps [rbp+0x40],xmm0                        
e8fed12 mov rax,[rbp+0x70]                             ; R pair.second (shared_ptr)
e8fed16 test rax,rax                                  
e8fed19 je short 0xE8FED3E                             ; null -> skip inc
e8fed1b lock inc dword ptr [rax+8]                     ; R/W refcount-low +8
e8fed1f mov rax,[rbp+0x70]                             
e8fed23 jmp short 0xE8FED40                           
e8fed25 mov rcx,rsi                                    ; null-cache path: restore & tail to save entry
e8fed28 movaps xmm6,[rbp+0x80]                        
e8fed2f add rsp,0x110                                 
e8fed36 pop rdi                                       
e8fed37 pop rsi                                       
e8fed38 pop rbp                                       
e8fed39 jmp 0xE8FEE80                                  ; tail -> sub_e8fee80 (SAVE entry)
e8fed3e xor eax,eax                                    
loc_e8fed40:
e8fed40 mov rcx,[rbp+0x68]                             ; R pair.first
e8fed44 mov [rbp+0x40],rcx                             
e8fed48 mov [rbp+0x48],rax                              ; pair.second = rax (refcounted ptr)
e8fed4c lea rdx,[rbp+0x40]                              ; &pair
e8fed50 mov rcx,rdi                                     ; cache object
e8fed53 call 0x773320                                   ; sub_773320(cacheObj, &pair) -> commit
e8fed58 nop                                            
e8fed59 mov rsi,[rbp+0x70]                             ; R pair.second -> rsi (release)
e8fed5d mov rdi,[rbp+0x58]                             ; R [rbp+0x58] -> rdi (release)
e8fed61 test rdi,rdi                                  
e8fed64 je short 0xE8FED91                             
e8fed66 lock dec dword ptr [rdi+8]                     ; R/W refcount-low -8
e8fed6a jne short 0xE8FED91                             
e8fed6c mov rax,[rdi]                                   ; vtable dtor
e8fed6f mov rax,[rax]                                  
e8fed72 mov rcx,rdi                                    
e8fed75 call qword ptr [0xF99FFA0]                      ; vtable[0] dtor
e8fed7b lock dec dword ptr [rdi+0xC]                   ; R/W refcount-high -0xC
e8fed7f jne short 0xE8FED91                             
e8fed81 mov rax,[rdi]                                  
e8fed84 mov rax,[rax+8]                                 ; vtable[8] delete
e8fed88 mov rcx,rdi                                    
e8fed8b call qword ptr [0xF99FFA0]                      ; delete
loc_e8fed91:
e8fed91 test rsi,rsi                                  
e8fed94 je short 0xE8FEDC1                             
e8fed96 lock dec dword ptr [rsi+8]                     ; R/W refcount-low -8
e8fed9a jne short 0xE8FEDC1                             
e8fed9c mov rax,[rsi]                                   ; vtable dtor
e8fed9f mov rax,[rax]                                  
e8feda2 mov rcx,rsi                                    
e8feda5 call qword ptr [0xF99FFA0]                      ; vtable[0] dtor
e8fedab lock dec dword ptr [rsi+0xC]                   ; R/W refcount-high -0xC
e8fedaf jne short 0xE8FEDC1                             
e8fedb1 mov rax,[rsi]                                  
e8fedb4 mov rax,[rax+8]                                 ; vtable[8] delete
e8fedb8 mov rcx,rsi                                    
e8fedbb call qword ptr [0xF99FFA0]                      ; delete
loc_e8fedc1:
e8fedc1 movaps xmm6,[rbp+0x80]                         
```
C-like: `pair = {pair.first, rax}; sub_773320(cacheObj, &pair); release_shared(pair.second); release_shared([rbp+0x58]);`

**Phase F — epilog / ret** [e8fedc8..e8fedd2]
```
e8fedc8 add rsp,0x110                                 
e8fedcf pop rdi                                       
e8fedd0 pop rsi                                       
e8fedd1 pop rbp                                       
e8fedd2 ret                                            
```

**Phase G — fail-fast poison paths (lock fail / state==0x7FFFFFFF)** [e8fedd3..e8fedef]
```
e8fedd3 mov ecx,5                                      ; log level 5
e8fedd8 call 0xEEC5A00                                 ; error logger lvl5
e8feddd mov dword ptr [rsi+0x4C],0x7FFFFFFE            ; W a0+0x4C = poison 0x7FFFFFFE
e8fede4 mov ecx,6                                      ; log level 6
e8fede9 call 0xEEC5A00                                 ; error logger lvl6
e8fedee int3                                           ; fail-fast breakpoint
e8fedef nop                                            
```
C-like: `log(5); this->state = 0x7FFFFFFE; log(6); int3;` — fail-fast poison on lock failure or poisoned state. [V]

---

## (2) Callees in order with identification, strings/paths referenced

Callees of tick (rdis callees [V]), in call order as they appear in the listing:

| # | Callee RVA | Identification | xrefs in tick | Strings/paths referenced | Tag |
|---|------------|----------------|---------------|--------------------------|-----|
| 1 | sub_eec59f0 | mutex lock entry (BGFX_MAP slot61 +0x3C563C0) | 1 (e8feb34) | none | [V] |
| 2 | sub_eec5920 | timing `now()` (BGFX_MAP 0xc267200 frame-render timing) | 1 (e8feb5b) | none | [V] |
| 3 | sub_eec5930 | timing query helper | 1 (e8feb63) | none | [V] |
| 4 | sub_eec5a10 | mutex unlock (tail-call) | 1 (e8fec59 tail + e8fec68) | none | [V] |
| 5 | sub_eec5a00 | error logger lvl5/lvl6 | 2 (e8fedd8, e8fede9) | none | [V BGFX_MAP slot61 +0x3C5640C==0x7fffffff] |
| 6 | sub_14a0c0 | async enqueue + refcounts, source_location carrier | 1 (e8fed05) | none | [I] |
| 7 | sub_773320 | cache commit helper | 1 (e8fed53) | none | [I] |

Strings referenced inside tick (rdis `strs 0xe8feb10` [V]):
- `0xf828df6` "void __cdecl dragon::utils::PipelineDiskCache::tick(void)" — loaded at e8fec7d into [rbp-0x10] (source_location func name) [V]
- `0xf57ab7f` "D:\a\_work\1\s\handheld\src-external\RenderDragon\src\Utility\PipelineDiskCache.cpp" — loaded at e8fec90 into [rbp] (source_location file path) [V]
- `0xf4f2070` — loaded at e8fecd2 into [rbp-0x50]; raw bytes are a **pointer table** (not a null-terminated string) [V raw]. Meaning unclear. [UNVERIFIED: 0xe8fecd2 what 0xF4F2070 pointer-table entry refers to]
- Cache file name/extension: `0xf593232` "rd_pipeline_cache.bin" — referenced at e8fc7e0 inside the SAVE entry sub_e8fc760 [V], NOT inside tick itself.

`xref.py str rd_pipeline_cache.bin` -> refs=[('0xe8fc7e0','0xe8fc760')] only [V].

---

## (3) PipelineDiskCache object — fields read/written by tick (descscan2.py --reg rsi)

| Offset | Size | Direction | Meaning (from context) | Evidence (RVA) | Tag |
|--------|------|-----------|------------------------|----------------|-----|
| +0x000 | qword | R | vtable pointer | `mov rax,[rsi]` @e8fed9c (x2) | [V] |
| +0x008 | dword | R | refcount low | `lock dec [rsi+8]` @e8fed96 | [V] |
| +0x00c | dword | R | refcount high | `lock dec [rsi+0xC]` @e8fedab | [V] |
| +0x04c | dword | R | state/flag (0x7FFFFFFF = poisoned) | `cmp [rsi+0x4C],0x7FFFFFFF` @e8feb41 x2 | [V] |
| +0x0d8 | byte | R | enabled flag (1 = enabled) | `cmp byte [rsi+0xD8],1` @e8feb4e | [V] |
| +0x0d9 | byte | R/W | work-in-progress flag | `cmp byte [rsi+0xD9],1` @e8fec3c x2; `mov byte [rsi+0xD9],1` @e8fec5e | [V] |
| +0x0e0 | qword | R | next due time (us) | `cmp rax,[rsi+0xE0]` @e8feb7e x3 | [V] |
| +0x0e8 | qword | R | cache-object pointer | `mov rdi,[rsi+0xE8]` @e8fec6d | [V] |

descscan2 read bytes: 0x0-0x10, 0x4c-0x50, 0xd8-0xda, 0xe0-0xf0. GAPS (unread): 0x10-0x4c, 0x50-0xd8, 0xda-0xe0 [V descscan2].

Stack frame locals (direction W):
- [rbp-0x10] qword W func-name ptr @e8fec84 [V]
- [rbp-0x8] qword W =0x39 @e8fec88 [V]
- [rbp] qword W file-path ptr @e8fec97 [V]
- [rbp+0x8] qword W =0x53 source_location line @e8fec9b [V]
- [rbp+0x78] qword W =0xFFFFFFFFFFFFFFFE @e8feb29, not read inside tick [UNVERIFIED: 0xe8feb29 why written, never read in-function]
- [rbp+0x58] / [rbp+0x70] shared_ptr refcount chains (lock dec +8, vtable[0] dtor, lock dec +0xC, vtable[8] delete) @e8fed66-e8fedbb [V]

---

## (4) Load and save entry points (neighbours / same class)

Only tick's direct caller is 0x67c9c20 (Frame renderer). Neighbouring same-class functions (same object offsets +0x4C/+0xD8/+0xE0, same timing guard constants 0x16E3600/0x989680/0x3B9ACA00):

| RVA | Size | Role | Tag |
|-----|------|------|-----|
| 0xe8fc760 | 0x17e8 | **SAVE entry** — writes cache file name "rd_pipeline_cache.bin" @e8fc7e0, builds path via sub_b1160, reads this->+0x4C/+0x50/+0x58/+0x70/+0x78/+0x7C/+0x80/+0x84/+0x88, vtable[0x38], loop [this+0xA0] writing entries, sub_eec6de0 memcpy, sub_a0850 alloc => writes RCDP-magic (0x43504452) cache file | [I] SAVE entry (called by 0x6639590) |
| 0xe8fee80 | 0xa6c | sibling same-class; identical guard (this=r14, +0x4C/+0xD8/+0xE0); writes str@0xF08C790 (pointer table), reads [r14+0x78/0x7C/0x80/0x84] via vtable[0x50]/[0x38] as "Unsigned Int"/"Unsigned Int 64", sub_eec6de0 memcpy, sub_a0850 alloc | [I] same-class sibling, exact role UNVERIFIED |

**Load entry point: NOT FOUND.** No neighbour references a load-related string; tick only tail-jumps to sub_e8fee80 when [rsi+0xE8]==null (null-cache path) [V]. [UNVERIFIED: 0xe8feb10 no load entry point identified among tick's neighbours; load may be a vtable method or a separate function not reached from tick]

Callers of tick: only 0x67c9c20 [V xref.py callers]. [UNVERIFIED: 0xe8feb10 whether there are indirect/vtable callers of tick not returned by xref.py]

---

## Callee dossiers (one-line roles)

- `sub_eec59f0` — mutex lock entry (returns eax!=0 on failure) [V]
- `sub_eec5920` — timing now() [V]
- `sub_eec5930` — timing query [V]
- `sub_eec5a10` — mutex unlock (tail-jump target) [V]
- `sub_eec5a00` — error logger, levels 5 and 6 [V]
- `sub_14a0c0` [0xe8feb10..] size 0x130 — async enqueue helper with source_location; refcounts rdx arg; calls sub_14a260, vtable[0x18], sub_14a430, sub_14abf0 [I]
- `sub_773320` [0x773320..0x7733e9) size 0xc9 — cache commit helper; switch [rcx+0xB0]: 1->release, 2->vtable[8]([rdx]), 3->[rax+0x30]=0, else->refcount+[rdx+8], vtable[0x20](rcx,&{[rdx],[rdx+8]inc}) [I]
- `sub_eea6040` — import thunk `jmp rax` via [0xF99FFA0] (used for vtable[0x40] vcall and shared_ptr dtor/delete) [V]

---

## Open questions / UNVERIFIED

- [UNVERIFIED: 0xe8fecd2] `lea rcx,[0xF4F2070]` loads a pointer-table entry, not a string; what it refers to is unknown.
- [UNVERIFIED: 0xe8feb29] `mov [rbp+0x78],0xFFFFFFFFFFFFFFFE` is written but never read inside tick; purpose unknown.
- [UNVERIFIED: 0xe8feb10] no load entry point identified among tick's neighbours (0xe8fc760 = save, 0xe8fee80 = same-class sibling). Load may be a vtable method or separate function.
- [UNVERIFIED: 0xe8feb10] whether xref.py's single caller (0x67c9c20) misses indirect/vtable call sites of tick.
- [I] sub_14a0c0 / sub_773320 roles inferred from call patterns, not independently dossier-verified.

## Verification artifacts
- docs/progress/oc_U-B4disk_listing.txt — rdis dis 0xe8feb10 802
- docs/progress/oc_U-B4disk_callers.txt — xref.py callers 0xe8feb10
- docs/progress/oc_U-B4disk_callees.txt — rdis callees 0xe8feb10
- docs/progress/oc_U-B4disk_descscan2.txt — descscan2 --start 0xe8feb10 --end 0xe8fedef --reg rsi

Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-B4disk.md`
