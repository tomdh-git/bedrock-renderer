# U-E4-F7: sub_67762e0 chunk builder — garbled-area redo + continuation from 0x677ca98

Unit: U-E4-F7
Function: sub_67762e0 (chunk builder, called by chunk extractor 0x66ea3d0) — continuation of U-E4-F6
RVAs: garbled-area redo (section below); continuation starts 0x677ca98 (Phase 1), function span [0x67762e0..0x677e166)
Source: `rdis dis` on Minecraft.Windows.exe 1.26.62.01 (version 1.26.62.01), RVAs relative to image base
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Resume continuation at RVA 0x677cdb6 (Phase 5). Garbled-area redo below records exact rdis lines for 0x677bde0..0x677be00, 0x677c100..0x677c115, 0x677c400..0x677c410, 0x677c4d0..0x677c4e5 (F6 doc had misaligned decodes at these spots).

## Redo — garbled areas (exact rdis lines; F6 doc mis-decoded these due to off-by-one/misaligned phase starts)

### Garbled area 0x677bde0..0x677be00 (end of F6 Phase 147 / start of F6 Phase 148)

Re-disassembled with `rdis dis 0x677bde0`. Exact rdis lines (range end 0x677be00 exclusive):

```
  677bde0  add [rax],al                                  
  677bde2  add ch,bl                                     
  677bde4  adc al,0x49                                   
  677bde6  lea ecx,[rsi+0x8A0]                           
  677bdec  lea r8,[rbp+0x2A8]                            
  677bdf3  call 0x1EF6F90                                ; -> sub_1ef6f90
  677bdf8  nop                                           
  677bdf9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```

// Interpretation: 0x677bde0..0x677bde4 `add [rax],al` / `add ch,bl` / `adc al,0x49` are embedded-data/padding ([?], same class as prior weird opens). Real grow-argument setup resumes at 0x677bde6 `lea ecx,[rsi+0x8A0]`, 0x677bdec `lea r8,[rbp+0x2A8]`, then **0x677bdf3 `call 0x1EF6F90`** (sub_1ef6f90 — the grow helper call F6's Phase 148 never saw; F6 instead decoded garbage `add al,[rax]`/`add al,ch`/`cwde`/`mov cl,0x77`/`sti`/`nop` starting at misaligned 0x677bdf0). 0x677bdf8 `nop`, then 0x677bdf9 `mov rcx,[0x1233E1B0]` begins the TLS flag read (continues at 0x677be00, excluded from this range). F6's Phase 148 opening was a misalignment artifact. // tag: [?] for the three opening adds and the lea ecx,[rsi+0x8A0] (register rsi unusual here, meaning undetermined); [V] for call 0x1EF6F90, TLS read start, exact RVAs/lines.

### Garbled area 0x677c100..0x677c115 (F6 Phase 152 start)

Re-disassembled with `rdis dis 0x677c100`. Exact rdis lines (range end 0x677c115 exclusive):

```
  677c100  add [rax],al                                  
  677c102  mov [r15],rax                                 
  677c105  lea rcx,[r15+8]                               
  677c109  lea rdx,[rbp+0x120]                           
  677c110  call 0xE869FF0                                ; -> sub_e869ff0
```

// Interpretation: F6 Phase 151 ended correctly at 0x677c105 `lea rcx,[r15+8]`, but F6 Phase 152 started 1 byte early at 0x677c108 (last byte of that lea) and decoded garbage `or [rax-0x73],cl`/`xchg ebp,eax`/`and [rcx],al`. Real stream: 0x677c100 `add [rax],al` (embedded data [?]); 0x677c102 `mov [r15],rax`; 0x677c105 `lea rcx,[r15+8]`; 0x677c109 `lea rdx,[rbp+0x120]`; 0x677c110 `call 0xE869FF0` (sub_e869ff0 — element append fast path, matches Phase 139/152); next instruction 0x677c115 `nop` (excluded). // tag: [?] for `add [rax],al` at 0x677c100; [V] for mov/lea/call lines and call target 0xE869FF0.

### Garbled area 0x677c400..0x677c410 (F6 Phase 156 start)

Re-disassembled with `rdis dis 0x677c400`. Exact rdis lines (range end 0x677c410 exclusive):

```
  677c400  mov rdx,[r14+0x758]                           
  677c407  cmp rdx,[r14+0x760]                           
  677c40e  je 0x677C59A                                  ; -> loc_677c59a
```

// Interpretation: F6 Phase 155 ended at 0x677c407 `cmp rdx,[r14+0x760]`, but F6 Phase 156 started at misaligned 0x677c40a (inside the 7-byte `cmp`) and emitted `(bad)` at 0x677c40a / `add [rax],al` at 0x677c40c. Real stream: 0x677c400 `mov rdx,[r14+0x758]`; 0x677c407 `cmp rdx,[r14+0x760]` (cursor bounds check); 0x677c40e `je loc_677c59a` (grow path); fall-through at 0x677c414 `lea rcx,[rbp+0x6E0]` continues next phase (excluded). // tag: [V] all lines; jump target loc_677c59a [V].

### Garbled area 0x677c4d0..0x677c4e5 (F6 Phase 157 start)

Re-disassembled with `rdis dis 0x677c4d0`. Exact rdis lines (range end 0x677c4e5 exclusive):

```
  677c4d0  add [rcx+0x2B],al                             ; W a0+0x2B
  677c4d3  xchg [rax-0x2EFFFFF8],ah                      
  677c4d9  call 0xFFFFFFFF8FDE8DDD                       ; -> data_8fde8ddd
  677c4de  test [rax+0x48000004],esi                     ; R ret@ffffffff8fde8ddd+0x48000004
  677c4e4  mov ecx,[0x1233E1B0]                          ; [data_1233e1b0]
```

// Interpretation: Likely embedded-data/misalignment zone ([?]): `add [rcx+0x2B],al`, `xchg [rax-0x2EFFFFF8],ah`, `call 0xFFFFFFFF8FDE8DDD` (target resolves to data_8fde8ddd, not code), `test [rax+0x48000004],esi`. F6 Phase 157 started at 0x677c4db with `enter 0x8966,0x85`/`mov al,4`/`add [rax],al` garbage — another misalignment artifact. Real code resumes at 0x677c4e4 `mov ecx,[0x1233E1B0]` (TLS flag read, continues at 0x677c4ea, excluded from this range). Never invent meaning for the call-to-data or test targets. // tag: [?] for all five lines (embedded data / undetermined); call target data_8fde8ddd [V] as rdis resolved it.

## Phase 1 — [0x677ca98..0x677cb5f) 40 instructions (`rdis dis 0x677ca98 41`)

Exact rdis lines:

```
  677ca98  lea r8,[rbp+0x5A8]                            
  677ca9f  call 0x6760710                                ; -> sub_6760710
  677caa4  nop                                           
  677caa5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677caac  mov rax,[rcx]                                 
  677caaf  mov rax,[rax+0x10]                            
  677cab3  movzx edx,byte ptr [rbp+0x847]                
  677caba  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cac0  nop                                           
  677cac1  mov qword ptr [rbp+0x4A0],0x2007803           
  677cacc  mov eax,[r14+0x770]                           
  677cad3  sub eax,[r14+0x768]                           
  677cada  shr eax,3                                     
  677cadd  imul eax,0xFFFFF0F1                           
  677cae3  dec eax                                       
  677cae5  mov [rbp+0x4CA],ax                            
  677caec  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677caf3  mov rax,[rcx]                                 
  677caf6  mov rax,[rax+0x10]                            
  677cafa  mov dl,0x4A                                   
  677cafc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cb02  nop                                           
  677cb03  mov [rbp+0x847],al                            
  677cb09  mov rdx,[r14+0x6B0]                           
  677cb10  cmp rdx,[r14+0x6B8]                           
  677cb17  je 0x677CBBF                                  ; -> loc_677cbbf
  677cb1d  inc rdx                                       
  677cb20  mov [r14+0x6B0],rdx                           
  677cb27  jmp 0x677CBCC                                 ; -> loc_677cbcc
  677cb2c  lea rcx,[r14+0x768]                           
  677cb33  mov rdx,r15                                   
  677cb36  lea r8,[rbp+0x5B0]                            
  677cb3d  call 0x6760710                                ; -> sub_6760710
  677cb42  nop                                           
  677cb43  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677cb4a  mov rax,[rcx]                                 
  677cb4d  mov rax,[rax+0x10]                            
  677cb51  movzx edx,byte ptr [rbp+0x847]                
  677cb58  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cb5e  nop                                           
```

// Interpretation: Completes F6 Phase 163's grow path loc_677ca8e (`lea rcx,[r14+0x768]` at 0x677ca8e, `mov rdx,r15` at 0x677ca95): `lea r8,[rbp+0x5A8]`; `call 0x6760710` (sub_6760710 — grow helper [V]); `nop`. TLS flag read `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x847]`→`call qword ptr [0xF99FFA0]` (= sub_eea6040 [V])→`nop`. State tag: `mov qword ptr [rbp+0x4A0],0x2007803`. Counter: `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1`; `dec eax`; `[rbp+0x4CA]=ax` (counter/÷8 pattern [I]). TLS flag again: `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`mov dl,0x4A`→`call [0xF99FFA0]`→`nop`; `[rbp+0x847]=al`. Append slot with cursor `rdx=[r14+0x6B0]`; `cmp [r14+0x6B8]`; `je loc_677cbbf` (grow); else `inc rdx`; `[r14+0x6B0]=rdx`; `jmp loc_677cbcc` (continues next phase). Grow path loc_677cb2c: `lea rcx,[r14+0x768]`; `mov rdx,r15`; `lea r8,[rbp+0x5B0]`; `call 0x6760710`; `nop`. loc_677cb43: TLS read `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x847]`→`call [0xF99FFA0]`→`nop` (call's `[rbp+0x847]=al` completes next phase). Counter `eax=[r14+0x770]` continues at 0x677cb5f (excluded from this phase). Range ends at `nop` 0x677cb5e (3 bytes → next instruction at 0x677cb5f).
// tag: [V] all lines; calls 0x6760710 [V], [0xF99FFA0]=sub_eea6040 [V] x3.

## Phase 2 — [0x677cb5f..0x677cc23) 40 instructions (`rdis dis 0x677cb5f 41`)

Exact rdis lines:

```
  677cb5f  mov eax,[r14+0x770]                           
  677cb66  sub eax,[r14+0x768]                           
  677cb6d  shr eax,3                                     
  677cb70  imul eax,0xFFFFF0F1                           
  677cb76  dec eax                                       
  677cb78  mov [rbp+0x4CA],ax                            
  677cb7f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677cb86  mov rax,[rcx]                                 
  677cb89  mov rax,[rax+0x10]                            
  677cb8d  mov dl,0x4A                                   
  677cb8f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cb95  nop                                           
  677cb96  mov [rbp+0x847],al                            
  677cb9c  mov rdx,[r14+0x2D8]                           
  677cba3  cmp rdx,[r14+0x2E0]                           
  677cbaa  je 0x677CC5D                                  ; -> loc_677cc5d
  677cbb0  inc rdx                                       
  677cbb3  mov [r14+0x2D8],rdx                           
  677cbba  jmp 0x677CC6A                                 ; -> loc_677cc6a
  677cbbf  lea rcx,[r14+0x6A8]                           
  677cbc6  call 0x6760E60                                ; -> sub_6760e60
  677cbcb  nop                                           
  677cbcc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677cbd3  mov rax,[rcx]                                 
  677cbd6  mov rax,[rax+0x10]                            
  677cbda  movzx edx,byte ptr [rbp+0x847]                
  677cbe1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cbe7  nop                                           
  677cbe8  mov eax,[r14+0x6A8]                           
  677cbef  not eax                                       
  677cbf1  add eax,[r14+0x6B0]                           
  677cbf8  mov [rbp+0x4DA],ax                            
  677cbff  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677cc06  mov rax,[rcx]                                 
  677cc09  mov rax,[rax+0x10]                            
  677cc0d  mov dl,0x4A                                   
  677cc0f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cc15  nop                                           
  677cc16  mov [rbp+0x847],al                            
  677cc1c  mov rdx,[r14+0x590]                           
  677cc23  cmp rdx,[r14+0x598]                           
```

// Interpretation: Completes Phase 1's counter: `mov eax,[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3`; `imul eax,0xFFFFF0F1`; `dec eax`; `mov [rbp+0x4CA],ax`. TLS flag read → `call [0xF99FFA0]` (= sub_eea6040 [V]) → `nop`; `[rbp+0x847]=al`. Append slot cursor `rdx=[r14+0x2D8]`; `cmp [r14+0x2E0]`; `je loc_677cc5d` (grow); else `inc rdx`; `[r14+0x2D8]=rdx`; `jmp loc_677cc6a` (continues next phase). Grow path loc_677cbbf: `lea rcx,[r14+0x6A8]`; `call 0x6760E60` (sub_6760e60 — grow helper #2 [V]); `nop`. loc_677cbcc: TLS read `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x847]`→`call [0xF99FFA0]`→`nop`; `[rbp+0x847]=al`. Counter/checksum: `eax=[r14+0x6A8]`; `not eax`; `add eax,[r14+0x6B0]`; `mov [rbp+0x4DA]=ax`. TLS flag again → `[rbp+0x847]=al`. Next append slot: `rdx=[r14+0x590]`; `cmp [r14+0x598]` continues at 0x677cc23 (excluded). Range ends at `mov rdx,[r14+0x590]` (4 bytes → next instruction at 0x677cc23).
// tag: [V] all lines; calls 0x6760E60 [V], [0xF99FFA0]=sub_eea6040 [V] x3.

## Phase 3 — [0x677cc23..0x677ccf1) 40 instructions (`rdis dis 0x677cc23 41`)

Exact rdis lines:

```
  677cc23  cmp rdx,[r14+0x598]                           
  677cc2a  je 0x677CCEE                                  ; -> loc_677ccee
  677cc30  lea rax,[rdx+0x10]                            ; R a1+0x10
  677cc34  mov [rdx],rax                                 ; W a1+0x0
  677cc37  mov rax,0x100000000                          
  677cc41  mov [rdx+8],rax                               ; W a1+0x8
  677cc45  mov rcx,rdx                                   
  677cc48  mov rdx,r12                                   
  677cc4b  call 0x6764990                                ; -> sub_6764990
  677cc50  add qword ptr [r14+0x590],0x30                
  677cc58  jmp 0x677CD01                                 ; -> loc_677cd01
  677cc5d  lea rcx,[r14+0x2D0]                           
  677cc64  call 0x6760E60                                ; -> sub_6760e60
  677cc69  nop                                           
  677cc6a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677cc71  mov rax,[rcx]                                 
  677cc74  mov rax,[rax+0x10]                            
  677cc78  movzx edx,byte ptr [rbp+0x847]                
  677cc7f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cc85  nop                                           
  677cc86  mov rax,0x4000000002007803                    
  677cc90  mov [rbp+0x4A0],rax                           
  677cc97  mov eax,[r14+0x2D0]                           
  677cc9e  not eax                                       
  677cca0  add eax,[r14+0x2D8]                           
  677cca7  mov [rbp+0x52C],ax                            
  677ccae  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677ccb5  mov rax,[rcx]                                 
  677ccb8  mov rax,[rax+0x10]                            
  677ccbc  mov dl,0x4A                                   
  677ccbe  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677ccc4  nop                                           
  677ccc5  mov [rbp+0x847],al                            
  677cccb  mov rdx,[r14+0x6B0]                           
  677ccd2  cmp rdx,[r14+0x6B8]                           
  677ccd9  je 0x677CD9B                                  ; -> loc_677cd9b
  677ccdf  inc rdx                                       
  677cce2  mov [r14+0x6B0],rdx                           
  677cce9  jmp 0x677CDA8                                 ; -> loc_677cda8
  677ccee  mov rcx,r14                                   
```

// Interpretation: Completes Phase 2's append slot: `cmp rdx,[r14+0x598]`; `je loc_677ccee` (grow); else fast path `lea rax,[rdx+0x10]`; `mov [rdx],rax`; `mov rax,0x100000000`; `mov [rdx+8],rax` (u64 0x100000000 at +8 [I]); `mov rcx,rdx`; `mov rdx,r12`; `call 0x6764990` (sub_6764990 — copy/finalize helper [I]); `add qword ptr [r14+0x590],0x30` (cursor += 0x30 [I]); `jmp loc_677cd01`. Grow path loc_677cc5d: `lea rcx,[r14+0x2D0]`; `call 0x6760E60` (sub_6760e60 — grow helper #2 [V]); `nop`. loc_677cc6a: TLS flag read → `call [0xF99FFA0]` (= sub_eea6040 [V]) → `nop`; `mov rax,0x4000000002007803`; `mov [rbp+0x4A0]=rax` (state tag [I]). Counter: `eax=[r14+0x2D0]`; `not eax`; `add eax,[r14+0x2D8]`; `mov [rbp+0x52C]=ax`. TLS flag again → `[rbp+0x847]=al`. Append slot cursor `rdx=[r14+0x6B0]`; `cmp [r14+0x6B8]`; `je loc_677cd9b` (grow); else `inc rdx`; `[r14+0x6B0]=rdx`; `jmp loc_677cda8` (continues next phase). Grow target loc_677ccee: `mov rcx,r14`; `add rcx,0x588` continues at 0x677ccf1 (excluded). Range ends at `mov rcx,r14` (0x677ccee, 3 bytes → next instruction at 0x677ccf1).
// tag: [V] all lines; calls 0x6764990 [V], 0x6760E60 [V], [0xF99FFA0]=sub_eea6040 [V] x3.

## Phase 4 — [0x677ccf1..0x677cdb6) 40 instructions (`rdis dis 0x677ccf1 41`)

Exact rdis lines:

```
  677ccf1  add rcx,0x588                                 
  677ccf8  mov r8,r12                                    
  677ccfb  call 0x6765870                                ; -> sub_6765870
  677cd00  nop                                           
  677cd01  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677cd08  mov rax,[rcx]                                 
  677cd0b  mov rax,[rax+0x10]                            
  677cd0f  movzx edx,byte ptr [rbp+0x847]                
  677cd16  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cd1c  nop                                           
  677cd1d  mov rax,0x202207803                           
  677cd27  mov [rbp+0x4A0],rax                           
  677cd2e  mov eax,[r14+0x590]                           
  677cd35  sub eax,[r14+0x588]                           
  677cd3c  shr eax,4                                     
  677cd3f  imul eax,0xFFFFAAAB                           
  677cd45  dec eax                                       
  677cd47  mov [rbp+0x4F2],ax                            
  677cd4e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677cd55  mov rax,[rcx]                                 
  677cd58  mov rax,[rax+0x10]                            
  677cd5c  mov dl,0x4A                                   
  677cd5e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  677cd64  nop                                           
  677cd65  mov [rbp+0x847],al                            
  677cd6b  mov rdx,[r14+8]                               
  677cd6f  cmp rdx,[r14+0x10]                            
  677cd73  je 0x677CE39                                  ; -> loc_677ce39
  677cd79  mov r8d,0xC8                                  
  677cd7f  mov rcx,rdx                                   
  677cd82  lea rdx,[rbp+0x4A0]                           
  677cd89  call 0xEEC6EC0                                ; -> sub_eec6ec0
  677cd8e  add qword ptr [r14+8],0xC8                    
  677cd96  jmp 0x677CE49                                 ; -> loc_677ce49
  677cd9b  lea rcx,[r14+0x6A8]                           
  677cda2  call 0x6760E60                                ; -> sub_6760e60
  677cda7  nop                                           
  677cda8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  677cdaf  mov rax,[rcx]                                 
  677cdb2  mov rax,[rax+0x10]                            
```

// Interpretation: Completes grow target loc_677ccee: `add rcx,0x588`; `mov r8,r12`; `call 0x6765870` (sub_6765870 — grow/copy helper [I]); `nop`. loc_677cd01 (Phase 3's jmp target): TLS flag read → `call [0xF99FFA0]` (= sub_eea6040 [V]) → `nop`; `mov rax,0x202207803`; `mov [rbp+0x4A0]=rax` (state tag [I]). Counter: `eax=[r14+0x590]`; `sub eax,[r14+0x588]`; `shr eax,4` (÷16 here vs ÷8 elsewhere [I]); `imul eax,0xFFFFAAAB`; `dec eax`; `mov [rbp+0x4F2]=ax`. TLS flag again → `[rbp+0x847]=al`. Append slot cursor `rdx=[r14+8]`; `cmp [r14+0x10]`; `je loc_677ce39` (grow); else `mov r8d,0xC8` (0xC8=200 [I]); `mov rcx,rdx`; `lea rdx,[rbp+0x4A0]`; `call 0xEEC6EC0` (sub_eec6ec0 — append/copy [I]); `add qword ptr [r14+8],0xC8` (cursor += 0xC8); `jmp loc_677ce49`. Grow path loc_677cd9b: `lea rcx,[r14+0x6A8]`; `call 0x6760E60` (sub_6760e60 — grow helper #2 [V]); `nop`. loc_677cda8: TLS read `mov rcx,[0x1233E1B0]`→`[rax]`→`[rax+0x10]`→`movzx edx,byte [rbp+0x847]` continues at 0x677cdb6 (excluded). Range ends at `mov rax,[rax+0x10]` (0x677cdb2, 4 bytes → next instruction at 0x677cdb6).
// tag: [V] all lines; calls 0x6765870 [V], 0xEEC6EC0 [V], 0x6760E60 [V], [0xF99FFA0]=sub_eea6040 [V] x3.
