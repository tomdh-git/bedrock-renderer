# oc_U-L8 — Unit progress (texture path)

## NEXT
Start: run `python tools/sigs/xref.py callers <rva>` for RVAs 0x67ceb40, 0x67ceed0, 0x95ed00, 0x4e198d0, 0x4e1cbb0; then `rdis dis <rva> 40` x4 phases per function (~160 instructions); write each function's dossier into this file; append results after each step. Nothing written yet.

## Plan (from OPENCODE_BRIEF.md unit U-L8)
Functions to analyze:
- 0x67ceb40 — image object builder candidate (PNG/TGA decode / ClientTexture), find callers + disasm first ~160 instructions
- 0x67ceed0 — image object builder candidate (PNG/TGA decode / ClientTexture), find callers + disasm first ~160 instructions
- 0x95ed00 — atlas stitcher caller candidate, find callers + disasm first ~160 instructions
- 0x4e198d0 — atlas stitcher caller candidate, find callers + disasm first ~160 instructions
- 0x4e1cbb0 — atlas stitcher caller candidate, find callers + disasm first ~160 instructions

For each function record: RVA; callers (RVAs via xref.py callers); 40-instruction phases of first ~160 instructions with exact `0xRVA  mnemonic operands` lines, // interpretation tagged [V]/[I]/[?]; per brief format: signature guess, register/arg map, phase `RVA..RVA: <what it does>` + C-like statement, struct fields touched (offset/size/direction/meaning/tag), callees (rva/what/[V]/[I]), OPEN questions.

## Done
- Caller xref complete for all 5 RVAs:
  - 0x67ceb40 → 0 callers (no E8 call site)
  - 0x67ceed0 → 0 callers (no E8 call site)
  - 0x95ed00 → 0 callers (no E8 call site)
  - 0x4e198d0 → 5 callers (xrefs in); callers not yet resolved
  - 0x4e1cbb0 → 1 caller (xrefs in); caller not yet resolved
- Disassembly captured for first ~160 instructions of all 5 functions:
  - 0x67ceb40 (size 0x2000), 0x67ceed0 (size 0x2000), 0x95ed00 (size 0x2000), 0x4e198d0 (size 0x2000, 5 xrefs in), 0x4e1cbb0 (size 0x2000, 1 xref in)

## Blocked
- rdis `callers`/`callees` commands output not yet captured (only `dis` used)
- xref.py callers returned empty for the 3 builder/stitcher functions (need to confirm truly no callers or xref limitation)

## NEXT
Write function dossiers for 0x67ceb40, then 0x67ceed0, then 0x95ed00, then 0x4e198d0, then 0x4e1cbb0. Append after each.

### FUNCTION 0x67ceb40 (dossier)

**RVA:** 0x67ceb40
**Size:** 0x2000 (0x67ceb40..0x67d0b40)
**Callers:** none found via `xref.py callers 0x67ceb40` (no E8 rel32 targeting this RVA in .text). [V]
**Signature guess:** returns void/bool; takes rcx=this, rdx=out ptr. [I]
**Register/arg map:** rcx = this/arg0, rdx = output pointer (written to [rsi]=0 at end), rsi = out ptr, rdi = this copy. [V]

Phases (first ~160 instructions, 40 per phase):

Phase 1: 0x67ceb40..0x67cebb9
```
0x67ceb40  push rbp                                      
0x67ceb41  push rsi                                      
0x67ceb42  push rdi                                      
0x67ceb43  push rbx                                      
0x67ceb44  sub rsp,0xA8                                  
0x67ceb4b  lea rbp,[rsp+0x80]                            
0x67ceb53  mov qword ptr [rbp+0x20],0xFFFFFFFFFFFFFFFE   
0x67ceb5b  mov rsi,rdx                                   
0x67ceb5e  mov rdi,rcx                                   
0x67ceb61  mov rax,[rcx+0x18]                            ; R a0+0x18
0x67ceb65  test rax,rax                                  
0x67ceb68  je short 0x67CEB7C                            ; -> loc_67ceb7c
0x67ceb6a  lea rcx,[rdi+0x18]                            ; R a0+0x18
0x67ceb6e  lea rdx,[rdi+0x58]                            ; R a0+0x58
0x67ceb72  mov rax,[rax+0x10]                            ; R *(a0+0x18)+0x10
0x67ceb76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
// Phase 1: Saves rbp/rsi/rdi/rbx, allocates 0xA8 stack frame, sets [rbp+0x20] = -2 (exception-handling marker), copies rdx→rsi (out ptr), rcx→rdi (this). Loads *(this+0x18); if non-null loads *(*(this+0x18)+0x10) and calls sub_eea6040 with rcx=*(this+0x18) lea'd from rdi+0x18, rdx=rdi+0x58. [V] Interpretation: ref-count acquire/release helper on a sibling object at this+0x18, passing this+0x58 as second arg. [I]

Phase 2: 0x67ceb7c..0x67cec42
```
loc_67ceb7c:
0x67ceb7c  mov rdx,[rdi+0x10]                            ; R a0+0x10
0x67ceb80  test rdx,rdx                                  
0x67ceb83  je short 0x67CEBE6                            ; -> loc_67cebe6
0x67ceb85  mov eax,[rdx+8]                               ; R *(a0+0x10)+0x8
0x67ceb88  xor ecx,ecx                                   
0x67ceb8a  nop [rax+rax]                                 ; R *(*(a0+0x10)+0x8)+0x0+idx
loc_67ceb90:
0x67ceb90  test eax,eax                                  
0x67ceb92  je short 0x67CEBE8                            ; -> loc_67cebe8
0x67ceb94  lea r8d,[rax+1]                               ; R *(*(a0+0x10)+0x8)+0x1
0x67ceb98  lock cmpxchg [rdx+8],r8d                      ; R *(a0+0x10)+0x8
0x67ceb9e  jne short 0x67CEB90                           ; -> loc_67ceb90
0x67ceba0  mov rcx,[rdi+8]                               ; R a0+0x8
0x67ceba4  mov rbx,[rdi+0x10]                            ; R a0+0x10
0x67ceba8  test rbx,rbx                                  
0x67cebab  je short 0x67CEBE8                            ; -> loc_67cebe8
0x67cebad  lock inc dword ptr [rbx+8]                    ; W *(a0+0x10)+0x8
0x67cebb1  mov [rbp+0x10],rcx                            
0x67cebb5  mov [rbp+0x18],rbx                            
0x67cebb9  lock dec dword ptr [rbx+8]                    ; W *(a0+0x10)+0x8
```
// Phase 2: Atomic increment of refcount at *(this+0x10)+0x8 via lock cmpxchg loop (spin until success). Then loads this+0x8 into rcx, this+0x10 into rbx, increments dword [rbx+0x8] (strong ref), stores rcx→[rbp+0x10], rbx→[rbp+0x18], then decrements [rbx+0x8]. If refcount hits 0 after dec, calls sub_eea6040 on *rbx then **rbx, then decrements [rbx+0xC] (weak ref); if that hits 0 calls sub_eea6040 on *rbx and *(*rbx+0x8). [V] Interpretation: acquire strong ref on object at this+0x10, then release pattern; this+0x8/+0x10 are ref-counted pointer fields. [I]

Phase 3: 0x67cebbd..0x67cecfd
```
0x67cebbd  jne short 0x67CEBF4                           ; -> loc_67cebf4
0x67cebbf  mov rax,[rbx]                                 ; R *(a0+0x10)+0x0
0x67cebc2  mov rax,[rax]                                 ; R *(*(a0+0x10)+0x0)+0x0
0x67cebc5  mov rcx,rbx                                   
0x67cebc8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67cec42  cmp qword ptr [rbp+0x10],0                    
0x67cec47  je 0x67CECFD                                  ; -> loc_67cecfd
0x67cec4d  mov byte ptr [rbp+8],0                        
0x67cec51  mov r9,[rdi+0x78]                             
0x67cec55  add rdi,0x58                                  
0x67cec59  lea rdx,[rbp-0x50]                            
0x67cec5d  lea r8,[rbp+0x10]                             
0x67cec61  mov rcx,rdi                                   
0x67cec64  call 0x8B9F1C0                                ; -> sub_8b9f1c0
0x67cec69  nop                                           
0x67cec6a  lea rcx,[rbp-0x20]                            
0x67cec6e  lea rdx,[rbp-0x50]                            
0x67cec72  call 0x1B9A30                                 ; -> sub_1b9a30
0x67cec77  cmp byte ptr [rbp-0x28],1                     
0x67cec7b  jne short 0x67CECBC                           ; -> loc_67cecbc
0x67cec7d  mov rax,[rbp-0x30]                            
0x67cec81  cmp rax,0x10                                  
0x67cec85  jb short 0x67CECBC                            ; -> loc_67cecbc
0x67cec87  mov rcx,[rbp-0x48]                            
0x67cec8b  lea rdx,[rax+1]                               
0x67cec8f  cmp rdx,0x1000                                
0x67cec96  jb short 0x67CECB7                            ; -> loc_67cecb7
0x67cec98  mov r8,[rcx-8]                                
0x67cec9c  add rcx,0xFFFFFFFFFFFFFFF8                    
0x67ceca0  sub rcx,r8                                    
0x67ceca3  cmp rcx,0x20                                  
0x67ceca7  jae 0x67CED47                                 ; -> loc_67ced47
0x67cecad  add rax,0x28                                  
0x67cecb1  mov rdx,rax                                   
0x67cecb4  mov rcx,r8                                    
loc_67cecb7:
0x67cecb7  call 0xE935700                                ; -> sub_e935700
loc_67cecbc:
0x67cecbc  cmp byte ptr [rbp+8],1                        
0x67cecc0  jne short 0x67CECFD                           ; -> loc_67cecfd
0x67cecc2  mov rax,[rbp]                                 
0x67cecc6  cmp rax,0x10                                  
0x67cecca  jb short 0x67CECFD                            ; -> loc_67cecfd
0x67ceccc  mov rcx,[rbp-0x18]                            
0x67cecd0  lea rdx,[rax+1]                               
0x67cecd4  cmp rdx,0x1000                                
0x67cecdb  jb short 0x67CECF8                            ; -> loc_67cecf8
0x67cecdd  mov r8,[rcx-8]                                
0x67cece1  add rcx,0xFFFFFFFFFFFFFFF8                    
0x67cece5  sub rcx,r8                                    
0x67cece8  cmp rcx,0x20                                  
0x67cecec  jae short 0x67CED47                           ; -> loc_67ced47
0x67cecee  add rax,0x28                                  
0x67cecf2  mov rdx,rax                                   
0x67cecf5  mov rcx,r8                                    
loc_67cecf8:
0x67cecf8  call 0xE935700                                ; -> sub_e935700
loc_67cecfd:
0x67cecfd  mov qword ptr [rsi],0                        

Phase 4: 0x67ced04..0x67ced46
```
0x67ced04  mov rdi,[rbp+0x18]                            
0x67ced08  test rdi,rdi                                  
0x67ced0b  je short 0x67CED38                            ; -> loc_67ced38
0x67ced0d  lock dec dword ptr [rdi+8]                    
0x67ced11  jne short 0x67CED38                           ; -> loc_67ced38
0x67ced13  mov rax,[rdi]                                 
0x67ced16  mov rax,[rax]                                 
0x67ced19  mov rcx,rdi                                   
0x67ced1c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67ced22  lock dec dword ptr [rdi+0xC]                  
0x67ced26  jne short 0x67CED38                           ; -> loc_67ced38
0x67ced28  mov rax,[rdi]                                 
0x67ced2b  mov rax,[rax+8]                               
0x67ced2f  mov rcx,rdi                                   
0x67ced32  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_67ced38:
0x67ced38  mov rax,rsi                                   
0x67ced3b  add rsp,0xA8                                  
0x67ced42  pop rbx                                       
0x67ced43  pop rdi                                       
0x67ced44  pop rsi                                       
0x67ced45  pop rbp                                       
0x67ced46  ret                                           
```
// Phase 4: Releases the strong ref held in [rbp+0x18] (this+0x10 object): lock-dec [rdi+0x8]; if zero calls sub_eea6040 on *rdi then *rdi, then lock-dec [rdi+0xC]; if zero calls sub_eea6040 on *rdi then *(*rdi+0x8). Returns rax=rsi (out ptr). [V]

**Struct fields touched:**
- this+0x8: pointer (R) — loaded at 0x67ceba0, stored to [rbp+0x10]
- this+0x10: ref-counted object ptr (R/W) — loaded at 0x67ceb7c/0x67ceba4; [+0x8] strong refcount lock cmpxchg (0x67ceb98) and lock inc/dec (0x67cebad/0x67cebb9); [+0xC] weak refcount lock dec (0x67cebb9 path leads to 0x67cec2c)
- this+0x18: object ptr (R) — loaded at 0x67ceb61, tested, *[+0x10] passed to sub_eea6040
- this+0x58: ptr (R) — lea'd at 0x67ceb6e as arg to sub_eea6040
- this+0x78: qword (R) — loaded at 0x67cec51 into r9 for call to sub_8b9f1c0
- [rbp+0x10]: local (W) — holds this+0x8 value
- [rbp+0x18]: local (W) — holds this+0x10 value (strong ref)
- [rbp-0x50]/[rbp-0x20]: locals used by sub_8b9f1c0/sub_1b9a30 decode calls
- [rsi] (out): qword (W) — set to 0 at 0x67cecfd

**Callees:**
- sub_eea6040 (via [0xF99FFA0]) — refcount acquire/release helper, called multiple times [V]
- sub_8b9f1c0 at 0x8B9F1C0 — decode call with rcx=this+0x58, rdx=&[rbp-0x50], r8=&[rbp+0x10], r9=[rdi+0x78] [V]
- sub_1b9a30 at 0x1B9A30 — called after sub_8b9f1c0 [V]
- sub_e935700 at 0xE935700 — called on error/alloc path at 0x67cecb7 and 0x67cecf8 [V]
- [0xF9A8C78] at 0x67ced5a (beyond 160 instr, phase 5 boundary) — appears to be a failure/termination path [V]

**OPEN questions:**
- Exact ClientTexture struct layout not confirmed; field meanings (refcount at +0x8/+0xC, sibling at +0x10/+0x18, data ptr at +0x58) are [I]
- sub_8b9f1c0 / sub_1b9a30 identities unknown (PNG vs TGA decode?) [?]
- Whether 0x67ceb40 is the PNG or TGA builder specifically [?]

## Blocked
- rdis `callers`/`callees` commands output not yet captured (only `dis` used)
- xref.py callers returned empty for the 3 builder/stitcher functions (need to confirm truly no callers or xref limitation)

## NEXT
Write function dossiers for 0x67ceed0, then 0x95ed00, then 0x4e198d0, then 0x4e1cbb0. Append after each.

### FUNCTION 0x67ceed0 (dossier)

**RVA:** 0x67ceed0
**Size:** 0x2000 (0x67ceed0..0x67d0ed0)
**Callers:** none found via `xref.py callers 0x67ceed0` (no E8 rel32 targeting this RVA in .text). [V]
**Signature guess:** returns void/bool; takes rcx=this, rdx=out ptr. [I]
**Register/arg map:** rcx = this/arg0, rdx = output pointer (written to [rsi]=0 at end), rsi = out ptr, rdi = this copy. [V]

Phases (first ~160 instructions, 40 per phase):

Phase 1: 0x67ceed0..0x67cef4d
```
0x67ceed0  push rbp                                      
0x67ceed1  push rsi                                      
0x67ceed2  push rdi                                      
0x67ceed3  push rbx                                      
0x67ceed4  sub rsp,0xA8                                  
0x67ceedb  lea rbp,[rsp+0x80]                            
0x67ceeeb  mov qword ptr [rbp+0x20],0xFFFFFFFFFFFFFFFE   
0x67ceeeb  mov rsi,rdx                                   
0x67ceeeb  mov rdi,rcx                                   
0x67ceef1  mov rax,[rcx+0x18]                            ; R a0+0x18
0x67ceef5  test rax,rax                                  
0x67ceef8  je short 0x67CEF0C                            ; -> loc_67cef0c
0x67ceefa  lea rcx,[rdi+0x18]                            ; R a0+0x18
0x67ceefe  lea rdx,[rdi+0x58]                            ; R a0+0x58
0x67cef02  mov rax,[rax+0x10]                            ; R *(a0+0x18)+0x10
0x67cef06  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_67cef0c:
0x67cef0c  mov rdx,[rdi+0x10]                            ; R a0+0x10
0x67cef10  test rdx,rdx                                  
0x67cef13  je short 0x67CEF76                            ; -> loc_67cef76
0x67cef15  mov eax,[rdx+8]                               ; R *(a0+0x10)+0x8
0x67cef18  xor ecx,ecx                                   
0x67cef1a  nop [rax+rax]                                 ; R *(*(a0+0x10)+0x8)+0x0+idx
loc_67cef20:
0x67cef20  test eax,eax                                  
0x67cef22  je short 0x67CEF78                            ; -> loc_67cef78
0x67cef24  lea r8d,[rax+1]                               ; R *(*(a0+0x10)+0x8)+0x1
0x67cef28  lock cmpxchg [rdx+8],r8d                      ; R *(a0+0x10)+0x8
0x67cef2e  jne short 0x67CEF20                           ; -> loc_67cef20
0x67cef30  mov rcx,[rdi+8]                               ; R a0+0x8
0x67cef34  mov rbx,[rdi+0x10]                            ; R a0+0x10
0x67cef38  test rbx,rbx                                  
0x67cef3b  je short 0x67CEF78                            ; -> loc_67cef78
0x67cef3d  lock inc dword ptr [rbx+8]                    ; W *(a0+0x10)+0x8
0x67cef41  mov [rbp+0x10],rcx                            
0x67cef45  mov [rbp+0x18],rbx                            
0x67cef49  lock dec dword ptr [rbx+8]                    ; W *(a0+0x10)+0x8
```
// Phase 1: Saves rbp/rsi/rdi/rbx, allocates 0xA8 stack frame, [rbp+0x20]=-2 EH marker, rdx→rsi (out), rcx→rdi (this). Loads *(this+0x18); if non-null loads *(*(this+0x18)+0x10) and calls sub_eea6040(rcx=lea this+0x18, rdx=lea this+0x58). Then atomic strong-ref acquire on *(this+0x10)+0x8 via lock cmpxchg loop; loads this+0x8→rcx, this+0x10→rbx, lock-inc [rbx+0x8], stores rcx→[rbp+0x10], rbx→[rbp+0x18], lock-dec [rbx+0x8]. [V]

Phase 2: 0x67cef4d..0x67cefd2
```
0x67cef4d  jne short 0x67CEF84                           ; -> loc_67cef84
0x67cef4f  mov rax,[rbx]                                 ; R *(a0+0x10)+0x0
0x67cef52  mov rax,[rax]                                 ; R *(*(a0+0x10)+0x0)+0x0
0x67cef55  mov rcx,rbx                                   
0x67cef58  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67cef5e  lock dec dword ptr [rbx+0xC]                  ; W *(a0+0x10)+0xC
0x67cef62  jne short 0x67CEF84                           ; -> loc_67cef84
0x67cef64  mov rax,[rbx]                                 ; R *(a0+0x10)+0x0
0x67cef67  mov rax,[rax+8]                               ; R *(*(a0+0x10)+0x0)+0x8
0x67cef6b  mov rcx,rbx                                   
0x67cef6e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67cef74  jmp short 0x67CEF84                           ; -> loc_67cef84
loc_67cef76:
0x67cef76  xor ecx,ecx                                   
loc_67cef78:
0x67cef78  mov [rbp+0x10],rcx                            
0x67cef7c  mov qword ptr [rbp+0x18],0                    
loc_67cef84:
0x67cef84  mov rcx,[rdi+0x10]                            
0x67cef88  test rcx,rcx                                  
0x67cef8b  je short 0x67CEFD2                            ; -> loc_67cefd2
0x67cef8d  mov eax,[rcx+8]                               
loc_67cef90:
0x67cef90  test eax,eax                                  
0x67cef92  je short 0x67CEFD2                            ; -> loc_67cefd2
0x67cef94  lea edx,[rax+1]                               
0x67cef97  lock cmpxchg [rcx+8],edx                      
0x67cef9c  jne short 0x67CEF90                           ; -> loc_67cef90
0x67cef9e  mov rbx,[rdi+0x10]                            
0x67cefa2  test rbx,rbx                                  
0x67cefa5  je short 0x67CEFD2                            ; -> loc_67cefd2
0x67cefa7  lock dec dword ptr [rbx+8]                    
0x67cefab  jne short 0x67CEFD2                           ; -> loc_67cefd2
0x67cefad  mov rax,[rbx]                                 
0x67cefb0  mov rax,[rax]                                 
0x67cefb3  mov rcx,rbx                                   
0x67cefb6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67cefbc  lock dec dword ptr [rbx+0xC]                  
0x67cefc0  jne short 0x67CEFD2                           ; -> loc_67cefd2
0x67cefc2  mov rax,[rbx]                                 
0x67cefc5  mov rax,[rax+8]                               
0x67cefc9  mov rcx,rbx                                   
0x67cefcc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_67cefd2:
0x67cefd2  cmp qword ptr [rbp+0x10],0                    
```
// Phase 2: If strong-ref acquire failed (zero refcount), calls sub_eea6040 on *rbx then **rbx, lock-dec [rbx+0xC]; if zero calls sub_eea6040 on *rbx and *(*rbx+0x8). If [rdi+0x10] null, zeroes [rbp+0x10]/[rbp+0x18]. Otherwise repeats atomic acquire on *(this+0x10)+0x8, then lock-dec [rbx+0x8]; if zero calls sub_eea6040 chain again. Ends comparing [rbp+0x10] to 0. [V]

Phase 3: 0x67cefd2..0x67cf08d
```
0x67cefd7  je 0x67CF08D                                  ; -> loc_67cf08d
0x67cefdd  mov byte ptr [rbp+8],0                        
0x67cefe1  mov r9,[rdi+0x70]                             
0x67cefe5  add rdi,0x58                                  
0x67cefe9  lea rdx,[rbp-0x50]                            
0x67cefed  lea r8,[rbp+0x10]                             
0x67ceff1  mov rcx,rdi                                   
0x67ceff4  call 0x8B9F370                                ; -> sub_8b9f370
0x67ceff9  nop                                           
0x67ceffa  lea rcx,[rbp-0x20]                            
0x67ceffe  lea rdx,[rbp-0x50]                            
0x67cf002  call 0x1B9A30                                 ; -> sub_1b9a30
0x67cf007  cmp byte ptr [rbp-0x28],1                     
0x67cf00b  jne short 0x67CF04C                           ; -> loc_67cf04c
0x67cf00d  mov rax,[rbp-0x30]                            
0x67cf011  cmp rax,0x10                                  
0x67cf015  jb short 0x67CF04C                            ; -> loc_67cf04c
0x67cf017  mov rcx,[rbp-0x48]                            
0x67cf01b  lea rdx,[rax+1]                               
0x67cf01f  cmp rdx,0x1000                                
0x67cf026  jb short 0x67CF047                            ; -> loc_67cf047
0x67cf028  mov r8,[rcx-8]                                
0x67cf02c  add rcx,0xFFFFFFFFFFFFFFF8                    
0x67cf030  sub rcx,r8                                    
0x67cf033  cmp rcx,0x20                                  
0x67cf037  jae 0x67CF0D7                                 ; -> loc_67cf0d7
0x67cf03d  add rax,0x28                                  
0x67cf041  mov rdx,rax                                   
0x67cf044  mov rcx,r8                                    
loc_67cf047:
0x67cf047  call 0xE935700                                ; -> sub_e935700
loc_67cf04c:
0x67cf04c  cmp byte ptr [rbp+8],1                        
0x67cf050  jne short 0x67CF08D                           ; -> loc_67cf08d
0x67cf052  mov rax,[rbp]                                 
0x67cf056  cmp rax,0x10                                  
0x67cf05a  jb short 0x67CF08D                            ; -> loc_67cf08d
0x67cf05c  mov rcx,[rbp-0x18]                            
0x67cf060  lea rdx,[rax+1]                               
0x67cf064  cmp rdx,0x1000                                
0x67cf06b  jb short 0x67CF088                            ; -> loc_67cf088
0x67cf06d  mov r8,[rcx-8]                                
0x67cf071  add rcx,0xFFFFFFFFFFFFFFF8                    
0x67cf075  sub rcx,r8                                    
0x67cf078  cmp rcx,0x20                                  
0x67cf07c  jae short 0x67CF0D7                           ; -> loc_67cf0d7
0x67cf07e  add rax,0x28                                  
0x67cf082  mov rdx,rax                                   
0x67cf085  mov rcx,r8                                    
loc_67cf088:
0x67cf088  call 0xE935700                                ; -> sub_e935700
loc_67cf08d:
0x67cf08d  mov qword ptr [rsi],0                        
```
// Phase 3: If [rbp+0x10] non-zero, [rbp+8]=0 byte; r9=[rdi+0x70]; rdi+=0x58; calls sub_8b9f370(rcx=rdi+0x58, rdx=&[rbp-0x50], r8=&[rbp+0x10], r9=[this+0x70]); then sub_1b9a30(rcx=&[rbp-0x20], rdx=&[rbp-0x50]). Checks [rbp-0x28]==1 byte flag; if so validates string/buffer at [rbp-0x48] with length [rbp-0x30] vs 0x1000/0x20 bounds, else calls sub_e935700. Then checks [rbp+8]==1; validates [rbp-0x18] buffer [rbp] length similarly; calls sub_e935700 on failure. Ends [rsi]=0. [V]

Phase 4: 0x67cf08d..0x67cf0d6 (+ boundary)
```
0x67cf08d  mov qword ptr [rsi],0                         
0x67cf094  mov rdi,[rbp+0x18]                            
0x67cf098  test rdi,rdi                                  
0x67cf09b  je short 0x67CF0C8                            ; -> loc_67cf0c8
0x67cf09d  lock dec dword ptr [rdi+8]                    
0x67cf0a1  jne short 0x67CF0C8                           ; -> loc_67cf0c8
0x67cf0a3  mov rax,[rdi]                                 
0x67cf0a6  mov rax,[rax]                                 
0x67cf0a9  mov rcx,rdi                                   
0x67cf0ac  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67cf0b2  lock dec dword ptr [rdi+0xC]                  
0x67cf0b6  jne short 0x67CF0C8                           ; -> loc_67cf0c8
0x67cf0b8  mov rax,[rdi]                                 
0x67cf0bb  mov rax,[rax+8]                               
0x67cf0bf  mov rcx,rdi                                   
0x67cf0c2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_67cf0c8:
0x67cf0c8  mov rax,rsi                                   
0x67cf0cb  add rsp,0xA8                                  
0x67cf0d2  pop rbx                                       
0x67cf0d3  pop rdi                                       
0x67cf0d4  pop rsi                                       
0x67cf0d5  pop rbp                                       
0x67cf0d6  ret                                           
loc_67cf0d7:
0x67cf0d7  mov qword ptr [rsp+0x20],0                    
0x67cf0e0  xor ecx,ecx                                   
0x67cf0e2  xor edx,edx                                   
0x67cf0e4  xor r8d,r8d                                   
0x67cf0e7  xor r9d,r9d                                   
0x67cf0ea  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
```
// Phase 4: Releases strong ref [rbp+0x18]: lock-dec [rdi+0x8]; if zero calls sub_eea6040 on *rdi then *rdi, lock-dec [rdi+0xC]; if zero calls sub_eea6040 on *rdi and *(*rdi+0x8). Returns rax=rsi. Failure path at 0x67cf0d7 zeroes stack args and calls [0xF9A8C78] (termination/fail-fast). [V]

**Struct fields touched:**
- this+0x8: pointer (R) — 0x67cef30, stored to [rbp+0x10]
- this+0x10: ref-counted object ptr (R/W) — 0x67cef0c/0x67cef34; [+0x8] strong refcount lock cmpxchg/inc/dec (0x67cef28/0x67cef3d/0x67cef49/0x67cefa7); [+0xC] weak refcount lock dec (0x67cef5e/0x67cefbc)
- this+0x18: object ptr (R) — 0x67ceef1, *[+0x10] to sub_eea6040
- this+0x58: ptr (R) — lea'd 0x67ceefe as sub_eea6040 arg
- this+0x70: qword (R) — 0x67cefe1 into r9 for sub_8b9f370
- [rbp+0x10]/[rbp+0x18]: locals holding this+0x8 / this+0x10 (strong ref)
- [rsi] (out): qword (W) — set to 0 at 0x67cf08d

**Callees:**
- sub_eea6040 via [0xF99FFA0] — refcount helper, multiple calls [V]
- sub_8b9f370 at 0x8B9F370 — decode call (differs from 0x67ceb40 which calls sub_8b9f1c0; reads +0x70 vs +0x78) [V]
- sub_1b9a30 at 0x1B9A30 — post-decode call [V]
- sub_e935700 at 0xE935700 — error/alloc path [V]
- [0xF9A8C78] — fail-fast on alloc failure [V]

**OPEN questions:**
- 0x67ceb40 vs 0x67ceed0: likely PNG vs TGA decode variants (differ only in callee 0x8B9F1C0 vs 0x8B9F370 and field +0x78 vs +0x70) [I]
- ClientTexture struct layout not confirmed [I]
- sub_8b9f1c0/sub_8b9f370/sub_1b9a30 identities unknown [?]

## Blocked
- xref.py callers returned empty for all three builder/stitcher functions (no E8 call sites found). May be called via indirect calls or vtable slots not caught by xref.py's E8-only scan. [?]

## NEXT
Write function dossiers for 0x95ed00, then 0x4e198d0, then 0x4e1cbb0.

### FUNCTION 0x95ed00 (dossier)

**RVA:** 0x95ed00
**Size:** 0x2000 (0x95ed00..0x960d00)
**Callers:** none found via `xref.py callers 0x95ed00` (no E8 rel32 targeting this RVA in .text). [V]
**Signature guess:** takes rcx=some struct ptr; returns rax result; writes [rsi] and [rsi+8]. [I]
**Register/arg map:** rcx = arg0 (struct ptr), rsi = output ptr (set at 0x95edc6), rax = return value. [V]

Phases (first ~160 instructions, 40 per phase):

Phase 1: 0x95ed00..0x95ed88
```
0x95ed00  sub rsp,0x38                                  
0x95ed04  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
0x95ed0b  xor rax,rsp                                   
0x95ed0e  mov [rsp+0x30],rax                            
0x95ed13  mov r9,[rcx+0x20]                             ; R a0+0x20
0x95ed17  mov rdx,[r9+0x1490]                           ; R *(a0+0x20)+0x1490
0x95ed1e  test rdx,rdx                                  
0x95ed21  je short 0x95ED8D                             ; -> loc_95ed8d
0x95ed23  mov r8,[r9+0x1A8]                             ; R *(a0+0x20)+0x1A8
0x95ed2a  test r8,r8                                    
0x95ed2d  je short 0x95ED8D                             ; -> loc_95ed8d
0x95ed2f  mov rax,[r9+0x6C0]                            ; R *(a0+0x20)+0x6C0
0x95ed36  test rax,rax                                  
0x95ed39  je short 0x95ED8D                             ; -> loc_95ed8d
0x95ed3b  add rcx,8                                     
0x95ed3f  xorps xmm0,xmm0                               
0x95ed42  movaps [rsp+0x20],xmm0                        
0x95ed47  mov r10,[r9+0x6C8]                            ; R *(a0+0x20)+0x6C8
0x95ed4e  test r10,r10                                  
0x95ed51  je short 0x95ED76                             ; -> loc_95ed76
0x95ed53  lock inc dword ptr [r10+8]                    ; W *(*(a0+0x20)+0x6C8)+0x8
0x95ed58  mov rax,[r9+0x6C0]                            ; R *(a0+0x20)+0x6C0
0x95ed5f  mov r10,[r9+0x6C8]                            ; R *(a0+0x20)+0x6C8
0x95ed66  mov r8,[r9+0x1A8]                             ; R *(a0+0x20)+0x1A8
0x95ed6d  mov rdx,[r9+0x1490]                           ; R *(a0+0x20)+0x1490
0x95ed74  jmp short 0x95ED79                            ; -> loc_95ed79
loc_95ed76:
0x95ed76  xor r10d,r10d                                 
loc_95ed79:
0x95ed79  mov [rsp+0x20],rax                            
0x95ed7e  mov [rsp+0x28],r10                            
0x95ed83  lea r9,[rsp+0x20]                             
0x95ed88  call 0x6BFA6D0                                ; -> sub_6bfa6d0
```
// Phase 1: Stack cookie guard ([0x1230a0c0] xor rsp → [rsp+0x30]). Loads r9=[rcx+0x20]; null-tests *(r9+0x1490), *(r9+0x1A8), *(r9+0x6C0) — all must be non-null or jump to epilogue. rcx+=8. Zeroes [rsp+0x20]. r10=[r9+0x6C8]; if non-null lock-inc [r10+8] (strong ref acquire). Then rax=[r9+0x6C0], r10=[r9+0x6C8], r8=[r9+0x1A8], rdx=[r9+0x1490]; stores rax→[rsp+0x20], r10→[rsp+0x28], lea r9=&[rsp+0x20]; calls sub_6bfa6d0. [V] Interpretation: ref-count acquire on object at +0x6C8, then calls sub_6bfa6d0 with a 2-qword arg block (ptr at +0x6C0, ref obj at +0x6C8). [I]

Phase 2: 0x95ed8d..0x95edf2
```
loc_95ed8d:
0x95ed8d  mov rax,[rsp+0x30]                            
0x95ed92  xor rax,rsp                                   
0x95ed95  mov rcx,[0x1230A0C0]                          ; [data_1230a0c0]
0x95ed9c  cmp rcx,rax                                   
0x95ed9f  jne short 0x95EDA6                            ; -> loc_95eda6
0x95eda1  add rsp,0x38                                  
0x95eda5  ret                                           
loc_95eda6:
0x95eda6  mov rcx,[rsp+0x30]                            
0x95edab  xor rcx,rsp                                   
0x95edae  call 0xE951550                                ; -> sub_e951550 (stack-check fail)
0x95edb3  int3                                          
...
0x95edc0  push rsi                                      
0x95edc1  push rdi                                      
0x95edc2  sub rsp,0x28                                  
0x95edc6  mov rsi,rcx                                   
0x95edc9  mov rcx,[rdx+8]                               
0x95edcd  mov rax,[rcx+0x18]                            
0x95edd1  add rcx,0x18                                  
0x95edd5  mov rax,[rax+8]                               
0x95edd9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x95eddf  test eax,eax                                  
0x95ede1  je short 0x95EDF2                             ; -> loc_95edf2
0x95ede3  movups xmm0,[0x128D4558]                      ; [data_128d4558]
0x95edea  movups [rsi],xmm0                             
0x95eded  jmp 0x95EEC1                                  ; -> loc_95eec1
loc_95edf2:
0x95edf2  call 0xEEC5920                                ; -> sub_eec5920
0x95edf7  mov rdi,rax                                   
0x95edfa  call 0xEEC5930                                ; -> sub_eec5930
0x95edff  cmp rdi,0x16E3600                             
0x95ee06  je short 0x95EE1A                             ; -> loc_95ee1a
0x95ee08  cmp rdi,0x989680                              
0x95ee0f  jne short 0x95EE75                            ; -> loc_95ee75
```
// Phase 2: Stack-cookie verify; on mismatch calls sub_e951550 (fail). Otherwise rsi=rcx (out ptr). Loads rcx=[rdx+8], rax=[rcx+0x18], rcx+=0x18, rax=[rax+8], calls sub_eea6040 (refcount op). If eax==0: stores constant 16-byte xmm from [0x128d4558] to [rsi], jumps to epilogue. Else: calls sub_eec5920→rax, sub_eec5930; rdi=result; compares rdi to 0x16E3600 (14999984?) and 0x989680 (999999?); if ==0x16E3600 goes to 0x95ee1a; if ==0x989680 does imul rax,0x64; else falls to 0x95ee75. [V]

Phase 3: 0x95ee11..0x95eeb4
```
0x95ee11  imul rax,0x64                                 
0x95ee15  jmp 0x95EEB4                                  ; -> loc_95eeb4
loc_95ee1a:
0x95ee1a  mov r9,0xB2F4FC0794908CF3                     
0x95ee24  mov rcx,rax                                   
0x95ee27  imul r9                                       
0x95ee2a  mov r8,rdx                                    
0x95ee2d  add r8,rcx                                    
0x95ee30  mov rax,r8                                    
0x95ee33  shr rax,0x3F                                  
0x95ee37  sar r8,0x18                                   
0x95ee3b  add r8,rax                                    
0x95ee3e  imul rax,r8,0x16E3600                         
0x95ee45  sub rcx,rax                                   
0x95ee48  imul rcx,0x3B9ACA00                           
0x95ee4f  mov rax,rcx                                   
0x95ee52  imul r9                                       
0x95ee55  mov rax,rdx                                   
0x95ee58  imul rdx,r8,0x3B9ACA00                        
0x95ee5f  add rax,rcx                                   
0x95ee62  mov rcx,rax                                   
0x95ee65  shr rcx,0x3F                                  
0x95ee69  sar rax,0x18                                  
0x95ee6d  add rax,rcx                                   
0x95ee70  add rax,rdx                                   
0x95ee73  jmp short 0x95EEB4                            ; -> loc_95eeb4
loc_95ee75:
0x95ee75  mov rcx,rax                                   
0x95ee78  or rcx,rdi                                    
0x95ee7b  shr rcx,0x20                                  
0x95ee7f  je short 0x95EE88                             ; -> loc_95ee88
0x95ee81  cqo                                           
0x95ee83  idiv rdi                                      
0x95ee86  jmp short 0x95EE8C                            ; -> loc_95ee8c
loc_95ee88:
0x95ee88  xor edx,edx                                   
0x95ee8a  div edi                                       
loc_95ee8c:
0x95ee8c  imul rcx,rax,0x3B9ACA00                       
0x95ee93  imul rax,rdx,0x3B9ACA00                       
0x95ee9a  mov rdx,rax                                   
0x95ee9d  or rdx,rdi                                    
0x95eea0  shr rdx,0x20                                  
0x95eea4  je short 0x95EEAD                             ; -> loc_95eead
0x95eea6  cqo                                           
0x95eea8  idiv rdi                                      
0x95eeab  jmp short 0x95EEB1                            ; -> loc_95eeb1
loc_95eead:
0x95eead  xor edx,edx                                   
0x95eeaf  div edi                                       
loc_95eeb1:
0x95eeb1  add rax,rcx                                   
loc_95eeb4:
0x95eeb4  add rax,0xF4240                               
0x95eeba  mov byte ptr [rsi],0                          
0x95eebd  mov [rsi+8],rax                               
```
// Phase 3: Three division/modulo paths computing rax = rdi % constant (0x16E3600 via libmul __aullrem at 0x95ee1a-0x95ee73 using magic multiply 0xB2F4FC0794908CF3 and 0x3B9ACA00; or direct idiv/div at 0x95ee75-0x95eeb1). Then rax += 0xF4240 (1000000). Stores byte [rsi]=0 and qword [rsi+8]=rax. [V] Interpretation: computes an atlas/page index or texture coordinate via division by 14999984/999999, adds 1000000. Constants 0x16E3600, 0x989680, 0x3B9ACA00, 0xF4240 are [I] meanings unknown.

Phase 4: 0x95eec1..0x95eeca (+ next fn start)
```
loc_95eec1:
0x95eec1  mov rax,rsi                                   
0x95eec4  add rsp,0x28                                  
0x95eec8  pop rdi                                       
0x95eec9  pop rsi                                       
0x95eeca  ret                                           
0x95eecb  int3                                          
...
0x95eed0  push rsi                                      
0x95eed1  push rdi                                      
0x95eed2  sub rsp,0x28                                  
0x95eed6  mov rsi,rcx                                   
0x95eed9  mov rax,[rcx+0x78]                            
0x95eedd  cmp rax,0x10                                  
0x95eee1  jb short 0x95EF18                             ; -> loc_95ef18
0x95eee3  mov rcx,[rsi+0x60]                            
0x95eee7  lea rdx,[rax+1]                               
0x95eeeb  cmp rdx,0x1000                                
0x95eef2  jb short 0x95EF13                             ; -> loc_95ef13
0x95eef4  mov r8,[rcx-8]                                
0x95eef8  add rcx,0xFFFFFFFFFFFFFFF8                    
0x95eefc  sub rcx,r8                                    
0x95eeff  cmp rcx,0x20                                  
0x95ef03  jae 0x95EFCA                                  ; -> loc_95efca
0x95ef09  add rax,0x28                                  
0x95ef0d  mov rdx,rax                                   
0x95ef10  mov rcx,r8                                    
loc_95ef13:
0x95ef13  call 0xE935700                                ; -> sub_e935700
loc_95ef18:
0x95ef18  mov qword ptr [rsi+0x70],0                    
0x95ef20  mov qword ptr [rsi+0x78],0xF                  
0x95ef28  mov byte ptr [rsi+0x60],0                     
0x95ef2c  mov rcx,[rsi+0x38]                            
0x95ef30  test rcx,rcx                                  
0x95ef33  je short 0x95EF74                             ; -> loc_95ef74
```
// Phase 4: Returns rax=rsi. Next function begins at 0x95eed0 (refcount release pattern on [rcx+0x78], string bounds checks, calls sub_e935700; zeroes [rsi+0x70], sets [rsi+0x78]=0xF, byte [rsi+0x60]=0). [V]

**Struct fields touched:**
- arg0+0x20: struct ptr (R) — r9=[rcx+0x20]
- *(arg0+0x20)+0x1490: ptr (R) — null-tested 0x95ed17
- *(arg0+0x20)+0x1A8: ptr (R) — null-tested 0x95ed23, copied to r8 0x95ed66
- *(arg0+0x20)+0x6C0: ptr (R) — 0x95ed2f/0x95ed58, stored to [rsp+0x20]
- *(arg0+0x20)+0x6C8: ref-counted obj ptr (R/W) — 0x95ed47; [+0x8] lock-inc strong ref (0x95ed53)
- [rsp+0x20]/[rsp+0x28]: locals (W) — arg block for sub_6bfa6d0
- [rdx+8]: ptr (R) — 0x95edc9
- *(rdx+8)+0x18: ptr (R) — 0x95edcd
- *(*(rdx+8)+0x18)+8: refcount (R) — 0x95edd5 to sub_eea6040
- [rsi]: out qword (W) — [rsi]=0 at 0x95eeba, [rsi+8]=rax at 0x95eebd
- rsi+0x70/+0x78/+0x60/+0x38: fields in next fn (0x95eed0) [V]

**Callees:**
- sub_6bfa6d0 at 0x6BFA6D0 — atlas stitcher call target [V]
- sub_e951550 at 0xE951550 — stack-cookie fail [V]
- sub_eea6040 via [0xF99FFA0] — refcount helper [V]
- sub_eec5920 at 0xEEC5920; sub_eec5930 at 0xEEC5930 — division helper pair [V]
- sub_e935700 at 0xE935700 — bounds-check fail (in next fn) [V]

**OPEN questions:**
- Whether 0x95ed00 is the "atlas stitcher" itself or a caller — it calls sub_6bfa6d0 which may be the stitcher [I]
- Meaning of constants 0x16E3600, 0x989680, 0x3B9ACA00, 0xF4240 [?]
- arg0/struct layout (fields +0x20, +0x1490, +0x1A8, +0x6C0, +0x6C8) [I]

## Blocked
- xref.py callers returned empty for all three builder/stitcher functions (no E8 call sites found). May be called via indirect calls or vtable slots not caught by xref.py's E8-only scan. [?]

## NEXT
Write function dossiers for 0x4e198d0, then 0x4e1cbb0.

### FUNCTION 0x4e198d0 (dossier)

**RVA:** 0x4e198d0
**Size:** 0x2000 (0x4e198d0..0x4e1b8d0), 5 xrefs in
**Callers:** 5 callers per `xref.py callers 0x4e198d0` (xrefs in); caller RVAs not yet resolved via rdis `callers` command. [V]
**Signature guess:** takes rcx=a0, rdx=a1, r8=a2, r9=a3; builds/stitches something from a2+0x58 array. [I]
**Register/arg map:** rcx=a0 (rdi), rdx=a1 ([rbp+0x178]), r8=a2 (rbx), r9=a3 ([rbp+0x198]). [V]

Phases (first ~160 instructions, 40 per phase):

Phase 1: 0x4e198d0..0x4e199d6
```
0x4e198d0  push rbp                                      
0x4e198d1  push r15                                      
0x4e198d3  push r14                                      
0x4e198d5  push r13                                      
0x4e198d7  push r12                                      
0x4e198d9  push rsi                                      
0x4e198da  push rdi                                      
0x4e198db  push rbx                                      
0x4e198dc  sub rsp,0x228                                 
0x4e198e3  lea rbp,[rsp+0x80]                            
0x4e198eb  mov qword ptr [rbp+0x1A0],0xFFFFFFFFFFFFFFFE  
0x4e198f6  mov [rbp+0x198],r9                            
0x4e198fd  mov rbx,r8                                    
0x4e19900  mov [rbp+0x178],rdx                           
0x4e19907  mov rdi,rcx                                   
0x4e1990a  lea rcx,[rbp+0x130]                           
0x4e19911  xor edx,edx                                   
0x4e19913  call 0xE931470                                ; -> sub_e931470
0x4e19918  nop                                           
0x4e19919  lea rcx,[rbp-0x30]                            
0x4e1991d  call 0xE943820                                ; -> sub_e943820
0x4e19922  nop                                           
0x4e19923  lea rax,[0xF52F10]                            ; [sub_f52f10]
0x4e1992a  mov [rbp+0x120],rax                           
0x4e19931  lea rax,[0x84510]                             ; [sub_84510]
0x4e19938  mov [rbp+0x128],rax                           
0x4e1993f  mov rax,[rbx+0x58]                            ; R a2+0x58
0x4e19943  mov rcx,[rax+8]                               ; R *(a2+0x58)+0x8
0x4e19947  mov rax,[rax+0x10]                            ; R *(a2+0x58)+0x10
0x4e1994b  mov rdx,rax                                   
0x4e1994e  sub rdx,rcx                                   
0x4e19951  mov r8,rdx                                    
0x4e19954  sar r8,3                                      
0x4e19958  mov r9,0x14C1BACF914C1BAD                     
0x4e19962  imul r9,r8                                    
0x4e19966  mov [rbp+0x110],r9                            
0x4e1996d  cmp rdx,0xFFFFFFFFFFFFFED8                    
0x4e19974  je 0x4E19D79                                  ; -> loc_4e19d79
0x4e1997a  mov [rbp+0x118],rcx                           
0x4e19981  test rcx,rcx                                  
0x4e19984  setne cl                                      
0x4e19987  test rax,rax                                  
0x4e1998a  sete al                                       
0x4e1998d  or al,cl                                      
0x4e1998f  je 0x4E19D79                                  ; -> loc_4e19d79
0x4e19995  lea r8,[rdi+0x28]                             ; R a0+0x28
0x4e19999  lea rcx,[rbp+0x180]                           
0x4e199a0  lea rdx,[rbp+0x110]                           
0x4e199a7  lea r9,[rbp+0x120]                            
0x4e199ae  call 0x17C2840                                ; -> sub_17c2840
0x4e199b3  nop                                           
0x4e199b4  lea r14,[rbp+0x120]                           
0x4e199bb  mov rsi,0xFFFFFFFFFFFFFF28                    
0x4e199c2  lea r15,[rbp-0x30]                            
0x4e199c6  lea r12,[rbp+0x110]                           
0x4e199cd  lea r13,[rbp+0x130]                           
0x4e199d4  jmp short 0x4E19A02                           ; -> loc_4e19a02
0x4e199d6  nop [rax+rax]                                 ; R ret@17c2840+0x0+idx
```
// Phase 1: Saves callee regs, 0x228 stack frame, [rbp+0x1A0]=-2 EH marker. Stores r9→[rbp+0x198], r8→rbx (a2), rdx→[rbp+0x178] (a1), rcx→rdi (a0). Calls sub_e931470(lea [rbp+0x130], edx=0) and sub_e943820(lea [rbp-0x30]). Sets [rbp+0x120]=sub_f52f10, [rbp+0x128]=sub_84510 (likely comparator/function ptrs). Loads rax=[a2+0x58]; rcx=[rax+8] (begin), rax=[rax+0x10] (end); rdx=rax-rcx (byte length), r8=rdx>>3 (qword count), r9=magic 0x14C1BACF914C1BAD, imul r9,r8 → [rbp+0x110] (element count via magic mult). Compares rdx vs 0xFFFFFFFFFFFFFED8 (overflow check); if rcx or rax null jumps to loc_4e19d79 (fail). lea r8=[a0+0x28], rcx=&[rbp+0x180], rdx=&[rbp+0x110], r9=&[rbp+0x120]; calls sub_17c2840 (likely sort/binary search setup). r14=&[rbp+0x120], rsi=-0xD8 (0xFFFFFFFFFFFFFF28, negative stride), r15=&[rbp-0x30], r12=&[rbp+0x110], r13=&[rbp+0x130]; jumps to loc_4e19a02 (loop). [V]

Phase 2: 0x4e199e0..0x4e19a64
```
loc_4e199e0:
0x4e199e0  mov rcx,[rbp+0x188]                           
0x4e199e7  add rcx,rsi                                   
0x4e199ea  call 0x1158F0                                 ; -> sub_1158f0
0x4e199ef  add qword ptr [rbp+0x188],0xFFFFFFFFFFFFFF28  
0x4e199fa  mov rcx,r14                                   
0x4e199fd  call 0xE9319A0                                ; -> sub_e9319a0
loc_4e19a02:
0x4e19a02  mov rax,[rbp+0x180]                           
0x4e19a09  cmp rax,[rbp+0x188]                           
0x4e19a10  je short 0x4E19A64                            ; -> loc_4e19a64
0x4e19a12  mov rcx,r14                                   
0x4e19a15  xor edx,edx                                   
0x4e19a17  call 0xE931470                                ; -> sub_e931470
0x4e19a1c  nop                                           
0x4e19a1d  mov rdx,[rbp+0x188]                           
0x4e19a24  add rdx,rsi                                   
0x4e19a27  mov rcx,r15                                   
0x4e19a2a  mov r8,r14                                    
0x4e19a2d  xor r9d,r9d                                   
0x4e19a30  call 0xE943A00                                ; -> sub_e943a00
0x4e19a35  nop                                           
0x4e19a36  test al,al                                    
0x4e19a38  je short 0x4E199E0                            ; -> loc_4e199e0
0x4e19a3a  mov rcx,r12                                   
0x4e19a3d  mov rdx,r14                                   
0x4e19a40  mov r8,r13                                    
0x4e19a43  mov r9b,0x20                                  
0x4e19a46  call 0x3E1B50                                 ; -> sub_3e1b50
0x4e19a4b  nop                                           
0x4e19a4c  mov rcx,r13                                   
0x4e19a4f  mov rdx,r12                                   
0x4e19a52  call 0xE931B80                                ; -> sub_e931b80
0x4e19a57  mov rcx,r12                                   
0x4e19a5a  call 0xE9319A0                                ; -> sub_e9319a0
0x4e19a5f  jmp 0x4E199E0                                 ; -> loc_4e199e0
loc_4e19a64:
0x4e19a64  xorps xmm0,xmm0                               
0x4e19a67  movaps [rbp+0x140],xmm0                       
```
// Phase 2: Loop at loc_4e19a02: while [rbp+0x180] != [rbp+0x188]. Calls sub_1158f0(rcx=[rbp+0x188]+rsi), then adds -0xD8 to [rbp+0x188] (walk backward by 0xD8 stride). Calls sub_e9319A0(r14=&[rbp+0x120]). Calls sub_e931470(r14, edx=0). Calls sub_e943a00(rcx=r15=&[rbp-0x30], rdx=[rbp+0x188]+rsi, r8=r14, r9=0). If al==0 jumps back to loc_4e199e0. Else calls sub_3e1b50(rcx=r12=&[rbp+0x110], rdx=r14, r8=r13=&[rbp+0x130], r9b=0x20); then sub_e931b80(rcx=r13, rdx=r12); sub_e9319A0(rcx=r12); loops. [V] Interpretation: sorted-array binary-search/insertion loop walking backward by 0xD8 elements, comparing via sub_e943a00, shifting via sub_3e1b50 (memmove-like, r9b=0x20=32 byte stride). [I]

Phase 3: 0x4e19a6e..0x4e19b6f
```
0x4e19a6e  mov rcx,[rbp+0x230]                           
0x4e19a75  mov rax,[rcx+8]                               
0x4e19a79  test rax,rax                                  
0x4e19a7c  je short 0x4E19A88                            ; -> loc_4e19a88
0x4e19a7e  lock inc dword ptr [rax+8]                    
0x4e19a82  mov rax,[rcx+8]                               
0x4e19a86  jmp short 0x4E19A8A                           ; -> loc_4e19a8a
loc_4e19a88:
0x4e19a88  xor eax,eax                                   
loc_4e19a8a:
0x4e19a8a  mov rcx,[rcx]                                 
0x4e19a8d  mov [rbp+0x140],rcx                           
0x4e19a94  mov [rbp+0x148],rax                           
0x4e19a9b  movaps [rbp+0x150],xmm0                       
0x4e19aa2  mov rcx,[rbp+0x228]                           
0x4e19aa9  mov rax,[rcx+8]                               
0x4e19aad  test rax,rax                                  
0x4e19ab0  je short 0x4E19ABC                            ; -> loc_4e19abc
0x4e19ab2  lock inc dword ptr [rax+8]                    
0x4e19ab6  mov rax,[rcx+8]                               
0x4e19aba  jmp short 0x4E19ABE                           ; -> loc_4e19abe
loc_4e19abc:
0x4e19abc  xor eax,eax                                   
loc_4e19abe:
0x4e19abe  mov rcx,[rcx]                                 
0x4e19ac1  mov [rbp+0x150],rcx                           
0x4e19ac8  mov [rbp+0x158],rax                           
0x4e19acf  movaps [rbp+0x160],xmm0                       
0x4e19ad6  mov rcx,[rbp+0x218]                           
0x4e19add  mov rax,[rcx+8]                               
0x4e19ae1  test rax,rax                                  
0x4e19ae4  je short 0x4E19AF0                            ; -> loc_4e19af0
0x4e19ae6  lock inc dword ptr [rax+8]                    
0x4e19aea  mov rax,[rcx+8]                               
0x4e19aee  jmp short 0x4E19AF2                           ; -> loc_4e19af2
loc_4e19af0:
0x4e19af0  xor eax,eax                                   
loc_4e19af2:
0x4e19af2  mov rcx,[rcx]                                 
0x4e19af5  mov [rbp+0x160],rcx                           
0x4e19afc  mov [rbp+0x168],rax                           
0x4e19b03  mov qword ptr [rbp+0x108],0                   
0x4e19b0e  mov rax,[rbp+0x210]                           
0x4e19b15  mov rcx,[rax+0x38]                            
0x4e19b19  test rcx,rcx                                  
0x4e19b1c  je short 0x4E19B39                            ; -> loc_4e19b39
0x4e19b1e  mov rax,[rcx]                                 
0x4e19b21  mov rax,[rax]                                 
0x4e19b24  lea rdx,[rbp+0xD0]                            
0x4e19b2b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x4e19b31  nop                                           
0x4e19b32  mov [rbp+0x108],rax                           
loc_4e19b39:
0x4e19b39  mov qword ptr [rbp+0xC8],0                    
0x4e19b44  mov rax,[rbp+0x198]                           
0x4e19b4b  mov rcx,[rax+0x38]                            
0x4e19b4f  test rcx,rcx                                  
0x4e19b52  je short 0x4E19B6F                            ; -> loc_4e19b6f
0x4e19b54  mov rax,[rcx]                                 
0x4e19b57  mov rax,[rax]                                 
0x4e19b5a  lea rdx,[rbp+0x90]                            
0x4e19b61  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x4e19b67  nop                                           
0x4e19b68  mov [rbp+0xC8],rax                            
loc_4e19b6f:
0x4e19b6f  lea rax,[rbp+0x140]                           
0x4e19b76  mov [rsp+0x48],rax                            
0x4e19b7b  lea rax,[rbp+0x150]                           
0x4e19b82  mov [rsp+0x40],rax                            
0x4e19b87  mov [rsp+0x38],rbx                            
0x4e19b8c  movzx eax,byte ptr [rbp+0x220]                
0x4e19b93  mov [rsp+0x30],al                             
0x4e19b97  lea rax,[rbp+0x160]                           
0x4e19b9e  mov [rsp+0x28],rax                            
```
// Phase 3: Acquires strong refs on three objects: [rbp+0x230]→[rbp+0x140/0x148], [rbp+0x228]→[rbp+0x150/0x158], [rbp+0x218]→[rbp+0x160/0x168] (each: ptr at field+8, lock-inc [field+8], store ptr+count). Zeroes [rbp+0x108]; if [rbp+0x210]→[+0x38] non-null calls sub_eea6040(*[that], *that) → [rbp+0x108]. Zeroes [rbp+0xC8]; if [rbp+0x198]→[+0x38] non-null calls sub_eea6040 → [rbp+0xC8]. Builds arg block on stack: [rsp+0x48]=&[rbp+0x140], [rsp+0x40]=&[rbp+0x150], [rsp+0x38]=rbx(a2), [rsp+0x30]=byte [rbp+0x220], [rsp+0x28]=&[rbp+0x160]. [V]

Phase 4: 0x4e19b9e..(160-instr boundary)
```
0x4e19b9e  mov [rsp+0x28],rax                            
```
```
// Phase 4: (cut off at 160-instruction limit) Argument block setup continues; expected call to sub_4e1a0a0 (per sibling fn 0x4e1cbb0 pattern) but not yet captured. [?]
```

**Struct fields touched:**
- a2+0x58: array ptr (R) — rbx+0x58 at 0x4e1993f; [+8] begin, [+0x10] end; length/8 computed
- a0+0x28: ptr (R) — lea'd 0x4e19995 as arg to sub_17c2840
- [rbp+0x120]/[rbp+0x128]: function ptrs (W) — sub_f52f10 / sub_84510
- [rbp+0x180]/[rbp+0x188]: loop bounds (R/W) — sorted array cursor
- [rbp+0x110]: element count (W) — magic-mult result
- [rbp+0x140/0x148], [rbp+0x150/0x158], [rbp+0x160/0x168]: strong-ref pairs (W) from [rbp+0x230]/[0x228]/[0x218]
- [rbp+0x230]/[+0x228]/[+0x218]+8: refcount (R/W) — lock-inc strong ref
- [rbp+0x108], [rbp+0xC8]: acquired refs (W)
- [rbp+0x210]/[rbp+0x198]+0x38: ref-counted obj ptrs (R) — to sub_eea6040
- Stack arg block [rsp+0x48/0x40/0x38/0x30/0x28]: (W) — for sub_4e1a0a0 (inferred)

**Callees:**
- sub_e931470 at 0xE931470 — init helper (2 calls) [V]
- sub_e943820 at 0xE943820 — init helper [V]
- sub_17c2840 at 0x17C2840 — sort/bsearch setup [V]
- sub_1158F0 at 0x1158F0 — per-element helper [V]
- sub_e9319A0 at 0xE9319A0 — accessor (3 calls) [V]
- sub_e943A00 at 0xE943A00 — compare (returns al) [V]
- sub_3e1b50 at 0x3E1B50 — 32-byte shift/memmove [V]
- sub_e931B80 at 0xE931B80 — release/update [V]
- sub_eea6040 via [0xF99FFA0] — refcount helper (2 calls) [V]
- sub_4e1a0a0 — expected next call, not yet captured [I]

**OPEN questions:**
- Caller RVAs of 0x4e198d0 (5 xrefs) not yet resolved [?]
- Whether sub_4e1a0a0 is the atlas stitcher [I]
- Struct layout for a0/a1/a2/a3 args [I]

## Blocked
- rdis `callers` command not yet used to resolve the 5 callers of 0x4e198d0
- 0x4e198d0 disassembly cut off at 160 instructions before the sub_4e1a0a0 call

## NEXT
Write function dossier for 0x4e1cbb0 (last function).

### FUNCTION 0x4e1cbb0 (dossier)

**RVA:** 0x4e1cbb0
**Size:** 0x2000 (0x4e1cbb0..0x4e1ebb0), 1 xref in
**Callers:** 1 caller per `xref.py callers 0x4e1cbb0` (xref in); caller RVA not yet resolved via rdis `callers`. [V]
**Signature guess:** takes rcx=a0, rdx=a1, r8=a2, r9=a3; builds/stitches from 3 ref-counted objects, calls sub_4e1a0a0. [I]
**Register/arg map:** rcx=a0 (rbx), rdx=a1 (rsi), r8=a2 (rdi), r9=a3 (r14). [V]

Phases (first ~160 instructions, 40 per phase):

Phase 1: 0x4e1cbb0..0x4e1ccc1
```
0x4e1cbb0  push rbp                                      
0x4e1cbb1  push r14                                      
0x4e1cbb3  push rsi                                      
0x4e1cbb4  push rdi                                      
0x4e1cbb5  push rbx                                      
0x4e1cbb6  sub rsp,0x110                                 
0x4e1cbbd  lea rbp,[rsp+0x80]                            
0x4e1cbc5  mov qword ptr [rbp+0x88],0xFFFFFFFFFFFFFFFE   
0x4e1cbd0  mov r14,r9                                    
0x4e1cbd3  mov rdi,r8                                    
0x4e1cbd6  mov rsi,rdx                                   
0x4e1cbd9  mov rbx,rcx                                   
0x4e1cbdc  mov rcx,[rbp+0x108]                           
0x4e1cbe3  mov rdx,[rbp+0x100]                           
0x4e1cbea  xorps xmm0,xmm0                               
0x4e1cbed  movaps [rbp+0x50],xmm0                        
0x4e1cbf1  mov rax,[rcx+8]                               
0x4e1cbf5  test rax,rax                                  
0x4e1cbf8  je short 0x4E1CC04                            ; -> loc_4e1cc04
0x4e1cbfa  lock inc dword ptr [rax+8]                    
0x4e1cbfe  mov rax,[rcx+8]                               
0x4e1cc02  jmp short 0x4E1CC06                           ; -> loc_4e1cc06
loc_4e1cc04:
0x4e1cc04  xor eax,eax                                   
loc_4e1cc06:
0x4e1cc06  mov r8,[rbp+0xF0]                             
0x4e1cc0d  mov rcx,[rcx]                                 
0x4e1cc10  mov [rbp+0x50],rcx                            
0x4e1cc14  mov [rbp+0x58],rax                            
0x4e1cc18  movaps [rbp+0x60],xmm0                        
0x4e1cc1c  mov rax,[rdx+8]                               
0x4e1cc20  test rax,rax                                  
0x4e1cc23  je short 0x4E1CC2F                            ; -> loc_4e1cc2f
0x4e1cc25  lock inc dword ptr [rax+8]                    
0x4e1cc29  mov rax,[rdx+8]                               
0x4e1cc2d  jmp short 0x4E1CC31                           ; -> loc_4e1cc31
loc_4e1cc2f:
0x4e1cc2f  xor eax,eax                                   
loc_4e1cc31:
0x4e1cc31  mov r9,[rbp+0xE8]                             
0x4e1cc38  mov rcx,[rdx]                                 
0x4e1cc3b  mov [rbp+0x60],rcx                            
0x4e1cc3f  mov [rbp+0x68],rax                            
0x4e1cc43  movaps [rbp+0x70],xmm0                        
0x4e1cc47  mov rax,[r8+8]                                
0x4e1cc4b  test rax,rax                                  
0x4e1cc4e  je short 0x4E1CC5A                            ; -> loc_4e1cc5a
0x4e1cc50  lock inc dword ptr [rax+8]                    
0x4e1cc54  mov rax,[r8+8]                                
0x4e1cc58  jmp short 0x4E1CC5C                           ; -> loc_4e1cc5c
loc_4e1cc5a:
0x4e1cc5a  xor eax,eax                                   
loc_4e1cc5c:
0x4e1cc5c  mov rdx,[rbp+0xE0]                            
0x4e1cc63  mov rcx,[r8]                                  
0x4e1cc66  mov [rbp+0x70],rcx                            
0x4e1cc6a  mov [rbp+0x78],rax                            
0x4e1cc6e  mov qword ptr [rbp+0x48],0                    
0x4e1cc76  mov rcx,[r9+0x38]                             
0x4e1cc7a  test rcx,rcx                                  
0x4e1cc7d  je short 0x4E1CC9B                            ; -> loc_4e1cc9b
0x4e1cc7f  mov rax,[rcx]                                 
0x4e1cc82  mov rax,[rax]                                 
0x4e1cc85  lea rdx,[rbp+0x10]                            
0x4e1cc89  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x4e1cc8f  nop                                           
0x4e1cc90  mov [rbp+0x48],rax                            
0x4e1cc94  mov rdx,[rbp+0xE0]                            
loc_4e1cc9b:
0x4e1cc9b  mov qword ptr [rbp+8],0                       
0x4e1cca3  mov rcx,[rdx+0x38]                            
0x4e1cca7  test rcx,rcx                                  
0x4e1ccaa  je short 0x4E1CCC1                            ; -> loc_4e1ccc1
0x4e1ccac  mov rax,[rcx]                                 
0x4e1ccaf  mov rax,[rax]                                 
0x4e1ccb2  lea rdx,[rbp-0x30]                            
0x4e1ccb6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x4e1ccbc  nop                                           
0x4e1ccbd  mov [rbp+8],rax                               
loc_4e1ccc1:
0x4e1ccc1  movzx eax,byte ptr [rbp+0xF8]                 
```
// Phase 1: Saves callee regs, 0x110 stack frame, [rbp+0x88]=-2 EH marker. r14=r9(a3), rdi=r8(a2), rsi=rdx(a1), rbx=rcx(a0). Acquires strong refs on 3 objects from stack slots [rbp+0x108], [rbp+0x100], [rbp+0xF0]: each loads ptr at field+8, lock-inc [field+8], stores ptr to [rbp+0x50/0x60/0x70] and count to [rbp+0x58/0x68/0x78]. r9=[rbp+0xE8]. If [r9+0x38] non-null calls sub_eea6040(*[r9+0x38], *[that]) → [rbp+0x48]. Then if [rdx+0x38] non-null calls sub_eea6040 → [rbp+8]. [V]

Phase 2: 0x4e1ccc1..0x4e1cd33
```
0x4e1ccc1  movzx eax,byte ptr [rbp+0xF8]                 
0x4e1ccc8  lea rcx,[rbp+0x50]                            
0x4e1cccc  mov [rsp+0x48],rcx                            
0x4e1ccd1  lea rcx,[rbp+0x60]                            
0x4e1ccd5  mov [rsp+0x40],rcx                            
0x4e1ccda  mov [rsp+0x38],r14                            
0x4e1ccdf  mov [rsp+0x30],al                             
0x4e1cce3  lea rax,[rbp+0x70]                            
0x4e1cce7  mov [rsp+0x28],rax                            
0x4e1ccec  lea rax,[rbp+0x10]                            
0x4e1ccf0  mov [rsp+0x20],rax                            
0x4e1ccf5  lea r9,[rbp-0x30]                             
0x4e1ccf9  mov rcx,rbx                                   
0x4e1ccfc  mov rdx,rsi                                   
0x4e1ccff  mov r8,rdi                                    
0x4e1cd02  call 0x4E1A0A0                                ; -> sub_4e1a0a0
0x4e1cd07  nop                                           
0x4e1cd08  mov rdi,[rbp+0xE0]                            
0x4e1cd0f  mov rcx,[rdi+0x38]                            
0x4e1cd13  test rcx,rcx                                  
0x4e1cd16  je short 0x4E1CD33                            ; -> loc_4e1cd33
0x4e1cd18  cmp rcx,rdi                                   
0x4e1cd1b  setne dl                                      
0x4e1cd1e  mov rax,[rcx]                                 
0x4e1cd21  mov rax,[rax+0x20]                            
0x4e1cd25  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x4e1cd2b  mov qword ptr [rdi+0x38],0                    
loc_4e1cd33:
0x4e1cd33  mov r14,[rbp+0xE8]                            
0x4e1cd3a  mov rcx,[r14+0x38]                            
0x4e1cd3e  test rcx,rcx                                  
0x4e1cd41  mov rbx,[rbp+0x100]                           
0x4e1cd48  mov rdi,[rbp+0xF0]                            
0x4e1cd4f  je short 0x4E1CD6C                            ; -> loc_4e1cd6c
```
// Phase 2: byte [rbp+0xF8]→al. Builds stack arg block: [rsp+0x48]=&[rbp+0x50], [rsp+0x40]=&[rbp+0x60], [rsp+0x38]=r14(a3), [rsp+0x30]=al, [rsp+0x28]=&[rbp+0x70], [rsp+0x20]=&[rbp+0x10]. rcx=rbx(a0), rdx=rsi(a1), r8=rdi(a2), r9=&[rbp-0x30]; calls sub_4e1a0a0 (this appears to be the atlas stitcher core). Then releases refs: [rbp+0xE0]→[+0x38] (if self-relative, setne dl) calls sub_eea6040(rcx, *[+0x20]); zeroes [rdi+0x38]. [rbp+0xE8]→[+0x38] similarly → zeroes [r14+0x38]. [V]

Phase 3: 0x4e1cd51..0x4e1cda0
```
0x4e1cd51  cmp rcx,r14                                   
0x4e1cd54  setne dl                                      
0x4e1cd57  mov rax,[rcx]                                 
0x4e1cd5a  mov rax,[rax+0x20]                            
0x4e1cd5e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x4e1cd64  mov qword ptr [r14+0x38],0                    
loc_4e1cd6c:
0x4e1cd6c  mov rdi,[rdi+8]                               
0x4e1cd70  test rdi,rdi                                  
0x4e1cd73  je short 0x4E1CDA0                            ; -> loc_4e1cda0
0x4e1cd75  lock dec dword ptr [rdi+8]                    
0x4e1cd79  jne short 0x4E1CDA0                           ; -> loc_4e1cda0
0x4e1cd7b  mov rax,[rdi]                                 
0x4e1cd7e  mov rax,[rax]                                 
0x4e1cd81  mov rcx,rdi                                   
0x4e1cd84  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x4e1cd8a  lock dec dword ptr [rdi+0xC]                  
0x4e1cd8e  jne short 0x4E1CDA0                           ; -> loc_4e1cda0
0x4e1cd90  mov rax,[rdi]                                 
0x4e1cd93  mov rax,[rax+8]                               
0x4e1cd97  mov rcx,rdi                                   
0x4e1cd9a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_4e1cda0:
0x4e1cda0  mov rdi,[rbx+8]                               
0x4e1cda4  test rdi,rdi                                  
0x4e1cda7  je short 0x4E1CDD4                            ; -> loc_4e1cdd4
```
// Phase 3: Releases strong ref on [rbp+0xF0]→[+8] (rdi): lock-dec [rdi+8]; if zero calls sub_eea6040 on *rdi then *rdi, lock-dec [rdi+0xC]; if zero calls sub_eea6040 on *rdi and *(*rdi+0x8). Then moves to [rbx+8] ref (rbx=a0). [V]

Phase 4: 0x4e1cda9..0x4e1ce1e
```
0x4e1cda9  lock dec dword ptr [rdi+8]                    
0x4e1cdad  jne short 0x4E1CDD4                           ; -> loc_4e1cdd4
0x4e1cdaf  mov rax,[rdi]                                 
0x4e1cdb2  mov rax,[rax]                                 
0x4e1cdb5  mov rcx,rdi                                   
0x4e1cdb8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x4e1cdbe  lock dec dword ptr [rdi+0xC]                  
0x4e1cdc2  jne short 0x4E1CDD4                           ; -> loc_4e1cdd4
0x4e1cdc4  mov rax,[rdi]                                 
0x4e1cdc7  mov rax,[rax+8]                               
0x4e1cdcb  mov rcx,rdi                                   
0x4e1cdce  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_4e1cdd4:
0x4e1cdd4  mov rax,[rbp+0x108]                           
0x4e1cddb  mov rdi,[rax+8]                               
0x4e1cddf  test rdi,rdi                                  
0x4e1cde2  je short 0x4E1CE0F                            ; -> loc_4e1ce0f
0x4e1cde4  lock dec dword ptr [rdi+8]                    
0x4e1cde8  jne short 0x4E1CE0F                           ; -> loc_4e1ce0f
0x4e1cdea  mov rax,[rdi]                                 
0x4e1cded  mov rax,[rax]                                 
0x4e1cdf0  mov rcx,rdi                                   
0x4e1cdf3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x4e1cdf9  lock dec dword ptr [rdi+0xC]                  
0x4e1cdfd  jne short 0x4E1CE0F                           ; -> loc_4e1ce0f
0x4e1cdff  mov rax,[rdi]                                 
0x4e1ce02  mov rax,[rax+8]                               
0x4e1ce06  mov rcx,rdi                                   
0x4e1ce09  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_4e1ce0f:
0x4e1ce0f  mov rax,rsi                                   
0x4e1ce12  add rsp,0x110                                 
0x4e1ce19  pop rbx                                       
0x4e1ce1a  pop rdi                                       
0x4e1ce1b  pop rsi                                       
0x4e1ce1c  pop r14                                       
0x4e1ce1d  pop rbp                                       
0x4e1ce1e  ret                                           
```
// Phase 4: Releases refs on [rbx+8] and [rbp+0x108] using same strong+weak refcount-release pattern (lock-dec +0x8; sub_eea6040 chain; lock-dec +0xC; sub_eea6040 chain). Returns rax=rsi(a1). [V]

**Struct fields touched:**
- a0=rcx (rbx): ref-counted obj ptr (R/W) — [rbx+8] released at 0x4e1cda0
- a1=rdx (rsi): return value (W) — rax=rsi at 0x4e1ce0f; also [rbp+0x100] copy
- a2=r8 (rdi): ref-counted obj ptr (R/W) — [rbp+0xF0] copy; [+8]/[+0xC] refcounts released
- a3=r9 (r14): ref-counted obj ptr (R/W) — [rbp+0xE8] copy; [+0x38] zeroed
- [rbp+0x108], [rbp+0x100], [rbp+0xF0]: ref-counted obj ptr args (R) — copied from stack
- [rbp+0x50/0x58], [rbp+0x60/0x68], [rbp+0x70/0x78]: strong-ref pairs (W) from the 3 obj ptrs
- [rbp+0x48], [rbp+8]: acquired refs (W) from [r9+0x38] and [rdx+0x38] via sub_eea6040
- [rbp+0x10], [rbp-0x30]: out locals (W) — arg block for sub_4e1a0a0
- Stack arg block [rsp+0x48/0x40/0x38/0x30/0x28/0x20]: (W) — for sub_4e1a0a0

**Callees:**
- sub_eea6040 via [0xF99FFA0] — refcount acquire/release, ~9 calls [V]
- sub_4e1a0a0 at 0x4E1A0A0 — atlas stitcher core call (rcx=a0, rdx=a1, r8=a2, r9=&[rbp-0x30]) [V]

**OPEN questions:**
- Caller RVA of 0x4e1cbb0 (1 xref) not yet resolved [?]
- sub_4e1a0a0 identity: likely atlas stitcher proper [I]
- Struct layout for ref-counted objects (fields +8 strong, +0xC weak, +0x38 parent/backptr) [I]

## Blocked
- rdis `callers` command not yet used to resolve caller RVAs of 0x4e198d0 (5 callers) and 0x4e1cbb0 (1 caller)
- xref.py callers only scans E8 rel32 direct calls; indirect/vtable callers not detected [?]

## NEXT
All 5 function dossiers written. Unit U-L8 complete. Consider running `rdis callers`/`callees` for caller RVAs if needed.
```
