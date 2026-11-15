# U-E4-H5 (builder 0x6722cb0)

## NEXT
COMPLETE: all 20 phases / 800 instructions from 0x672604d done. Last instruction: 0x6726f00 `mov rax,[rbp+0x758]` (the 800th instruction); next instruction would start at 0x6726f07 (beyond target). Unit U-E4-H5 disassembly complete.

## Phase 2 (0x67260a2..0x672616c)
```
  67260a2  mov eax,[r14+0x810]
  67260a9  not eax
  67260ab  add eax,[r14+0x818]
  67260b2  mov [rbp+0x12C],ax
  67260b9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67260c0  mov rax,[rcx]
  67260c3  mov rax,[rax+0x10]
  67260c7  mov dl,0x4A
  67260c9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67260cf  nop
  67260d0  mov [rbp+0x818],al
  67260d6  mov rdx,[r14+0x368]
  67260dd  cmp rdx,[r14+0x370]
  67260e4  je 0x6726398                                  ; -> loc_6726398
  67260ea  inc rdx
  67260ed  mov [r14+0x368],rdx
  67260f4  jmp 0x67263A5                                 ; -> loc_67263a5
  67260f9  lea rcx,[r14+0x678]
  6726100  lea r8,[rbp+0x564]
  6726107  call 0x1770A70                                ; -> sub_1770a70
  672610c  nop
  672610d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726114  mov rax,[rcx]
  6726117  mov rax,[rax+0x10]
  672611b  movzx edx,byte ptr [rbp+0x818]
  6726122  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726128  nop
  6726129  mov qword ptr [rbp+0x110],0x2807009
  6726134  mov eax,[r14+0x680]
  672613b  sub eax,[r14+0x678]
  6726142  shr eax,2
  6726145  imul eax,0xFFFFAAAB
  672614b  dec eax
  672614d  mov [rbp+0x14E],ax
  6726154  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672615b  mov rax,[rcx]
  672615e  mov rax,[rax+0x10]
  6726162  mov dl,0x4A
  6726164  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672616a  nop
```
// Phase 2: computes ax = ~(r14+0x810) + (r14+0x818) (a 16-bit XOR-ish fold) into [rbp+0x12C], then calls sub_eea6040 with dl=0x4A ('J') and stores return al into [rbp+0x818]. Then a second cursor loop over r14+0x368 vs r14+0x370 (je loc_6726398 else inc and jmp loc_67263A5). Calls sub_1770a70 with rcx=r14+0x678, r8=rbp+0x564. Then sub_eea6040 again with edx=byte[rbp+0x818]. Stores constant 0x2807009 at [rbp+0x110]. Computes eax = ((r14+0x680)-(r14+0x678))>>2, multiplies by 0xFFFFAAAB (magic for division by 3), decrements, stores ax at [rbp+0x14E]. Then sub_eea6040 with dl=0x4A.

## Phase 3 (0x672616b..0x6726239)
```
  672616b  mov [rbp+0x818],al                            
  6726171  mov rdx,[r14+0x68]                            
  6726175  cmp rdx,[r14+0x70]                            
  6726179  je 0x6726431                                  ; -> loc_6726431
  672617f  inc rdx                                       
  6726182  mov [r14+0x68],rdx                            
  6726186  jmp 0x672643E                                 ; -> loc_672643e
  672618b  lea rcx,[r14+0x678]                           
  6726192  lea r8,[rbp+0x570]                            
  6726199  call 0x1770A70                                ; -> sub_1770a70
  672619e  nop                                           
  672619f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67261a6  mov rax,[rcx]                                 
  67261a9  mov rax,[rax+0x10]                            
  67261ad  movzx edx,byte ptr [rbp+0x818]                
  67261b4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67261ba  nop                                           
  67261bb  mov qword ptr [rbp+0x110],0x2807009           
  67261c6  mov eax,[r14+0x680]                           
  67261cd  sub eax,[r14+0x678]                           
  67261d4  shr eax,2                                     
  67261d7  imul eax,0xFFFFAAAB                           
  67261dd  dec eax                                       
  67261df  mov [rbp+0x14E],ax                            
  67261e6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67261ed  mov rax,[rcx]                                 
  67261f0  mov rax,[rax+0x10]                            
  67261f4  mov dl,0x4A                                   
  67261f6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67261fc  nop                                           
  67261fd  mov [rbp+0x818],al                            
  6726203  mov rdx,[r14+0x818]                           
  672620a  cmp rdx,[r14+0x820]                           
  6726211  je 0x67264BF                                  ; -> loc_67264bf
  6726217  inc rdx                                       
  672621a  mov [r14+0x818],rdx                           
  6726221  jmp 0x67264CC                                 ; -> loc_67264cc
  6726226  lea rcx,[r15+0x690]                           
  672622d  lea r8,[rbp+0x5A0]                            
  6726234  call 0x1EF6F90                                ; -> sub_1ef6f90
```
// Phase 3: `mov [rbp+0x818],al` stores the TLS sub_eea6040 return byte from phase 2. Cursor loop over [r14+0x68] vs [r14+0x70]: if equal `je 0x6726431` (-> loc_6726431) else `inc rdx`, `mov [r14+0x68],rdx`, `jmp 0x672643E` (-> loc_672643e). `lea rcx,[r14+0x678]`; `lea r8,[rbp+0x570]`; `call 0x1770A70` (sub_1770a70; `nop`). TLS singleton seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. `mov qword ptr [rbp+0x110],0x2807009`. Count calc: `eax=[r14+0x680]`; `sub eax,[r14+0x678]`; `shr eax,2`; `imul eax,0xFFFFAAAB` (magic for /3); `dec eax`; `mov [rbp+0x14E],ax`. Second TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `nop`; `mov [rbp+0x818],al`. Cursor loop [r14+0x818] vs [r14+0x820]: if equal `je 0x67264BF` (-> loc_67264bf) else `inc rdx`; `mov [r14+0x818],rdx`; `jmp 0x67264CC` (-> loc_67264cc). `lea rcx,[r15+0x690]`; `lea r8,[rbp+0x5A0]`; `call 0x1EF6F90` (sub_1ef6f90; continues next phase: 0x6726239 `nop`).

Callees: 0x1770A70 (sub_1770a70, direct), [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x1EF6F90 (sub_1ef6f90, direct).
Fields read: [rbp+0x818] [R], [r14+0x68] [R], [r14+0x70] [R], [r14+0x68] [W], [r14+0x678] [R], [rbp+0x570] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R], [rbp+0x110] [W], [r14+0x680] [R], [r14+0x678] [R], [rbp+0x14E] [W], [r14+0x818] [R/W], [r14+0x820] [R], [r14+0x818] [W], [r15+0x690] [R], [rbp+0x5A0] [R].
Fields written: [rbp+0x818], [r14+0x68], [rbp+0x110], [rbp+0x14E], [r14+0x818].

## Phase 4 (0x6726239..0x6726301)
```
  6726239  nop                                           
  672623a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726241  mov rax,[rcx]                                 
  6726244  mov rax,[rax+0x10]                            
  6726248  movzx edx,byte ptr [rbp+0x818]                
  672624f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726255  nop                                           
  6726256  mov eax,[r15+0x698]                           
  672625d  sub eax,[r15+0x690]                           
  6726264  shr eax,1                                     
  6726266  dec eax                                       
  6726268  mov [rbp+0x14C],ax                            
  672626f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726276  mov rax,[rcx]                                 
  6726279  mov rax,[rax+0x10]                            
  672627d  mov dl,0x4A                                   
  672627f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726285  nop                                           
  6726286  mov [rbp+0x818],al                            
  672628c  mov rdx,[r15+0x638]                           
  6726293  cmp rdx,[r15+0x640]                           
  672629a  je 0x672653F                                  ; -> loc_672653f
  67262a0  mov eax,[rbp+0x598]                           
  67262a6  mov [rdx],eax                                 
  67262a8  add qword ptr [r15+0x638],4                   
  67262b0  jmp 0x6726553                                 ; -> loc_6726553
  67262b5  lea rcx,[r15+0x678]                           
  67262bc  lea r8,[rbp+0x5A8]                            
  67262c3  call 0x1770A70                                ; -> sub_1770a70
  67262c8  nop                                           
  67262c9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67262d0  mov rax,[rcx]                                 
  67262d3  mov rax,[rax+0x10]                            
  67262d7  movzx edx,byte ptr [rbp+0x818]                
  67262de  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67262e4  nop                                           
  67262e5  mov qword ptr [rbp+0x110],0x2807009           
  67262f0  mov eax,[r15+0x680]                           
  67262f7  sub eax,[r15+0x678]                           
  67262fe  shr eax,2                                     
```
// Phase 4: `nop` tails the `call 0x1EF6F90` from phase 3. TLS seq tail: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. Count calc (shift 1): `eax=[r15+0x698]`; `sub eax,[r15+0x690]`; `shr eax,1`; `dec eax`; `mov [rbp+0x14C],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al`. Cursor loop [r15+0x638] vs [r15+0x640]: if equal `je 0x672653F` (-> loc_672653f) else `mov eax,[rbp+0x598]`; `mov [rdx],eax`; `add qword ptr [r15+0x638],4`; `jmp 0x6726553` (-> loc_6726553). `lea rcx,[r15+0x678]`; `lea r8,[rbp+0x5A8]`; `call 0x1770A70` (sub_1770a70); `nop`. TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop`. `mov qword ptr [rbp+0x110],0x2807009`. Count calc: `eax=[r15+0x680]`; `sub eax,[r15+0x678]`; `shr eax,2` (continues next phase: 0x6726301 `imul eax,0xFFFFAAAB`).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x1770A70 (sub_1770a70, direct).
Fields read: [rbp+0x818] [R], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [r15+0x698] [R], [r15+0x690] [R], [rbp+0x14C] [W], [r15+0x638] [R], [r15+0x640] [R], [rbp+0x598] [R], [rdx] [W], [r15+0x678] [R], [rbp+0x5A8] [R], [rbp+0x110] [W], [r15+0x680] [R], [r15+0x678] [R].
Fields written: [rbp+0x818], [rbp+0x14C], [r15+0x638], [rbp+0x110].

## Phase 7 (0x672648c..0x6726552)
```
  672648c  nop                                           
  672648d  mov [rbp+0x818],al                            
  6726493  mov rdx,[r14+8]                               
  6726497  cmp rdx,[r14+0x10]                            
  672649b  je 0x6726741                                  ; -> loc_6726741
  67264a1  mov r8d,0xC8                                  
  67264a7  mov rcx,rdx                                   
  67264aa  mov rdx,r15                                   
  67264ad  call 0xEEC6EC0                                ; -> sub_eec6ec0
  67264b2  add qword ptr [r14+8],0xC8                    
  67264ba  jmp 0x672674D                                 ; -> loc_672674d
  67264bf  lea rcx,[r14+0x810]                           
  67264c6  call 0x6760E60                                ; -> sub_6760e60
  67264cb  nop                                           
  67264cc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67264d3  mov rax,[rcx]                                 
  67264d6  mov rax,[rax+0x10]                            
  67264da  movzx edx,byte ptr [rbp+0x818]                
  67264e1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67264e7  nop                                           
  67264e8  mov eax,[r14+0x810]                           
  67264ef  not eax                                       
  67264f1  add eax,[r14+0x818]                           
  67264f8  mov [rbp+0x12C],ax                            
  67264ff  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726506  mov rax,[rcx]                                 
  6726509  mov rax,[rax+0x10]                            
  672650d  mov dl,0x4A                                   
  672650f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726515  nop                                           
  6726516  mov [rbp+0x818],al                            
  672651c  mov rdx,[r14+0x368]                           
  6726523  cmp rdx,[r14+0x370]                           
  672652a  je 0x672677A                                  ; -> loc_672677a
  6726530  inc rdx                                       
  6726533  mov [r14+0x368],rdx                           
  672653a  jmp 0x6726787                                 ; -> loc_6726787
  672653f  lea rcx,[r15+0x630]                           
  6726546  lea r8,[rbp+0x598]                            
  672654d  call 0x14DB710                                ; -> sub_14db710
```
// Phase 7: `nop`; `mov [rbp+0x818],al` stores the TLS result from phase 6's final call (0x6726486). Cursor loop [r14+8] vs [r14+0x10]: if equal `je 0x6726741` (-> loc_6726741) else `mov r8d,0xC8`; `mov rcx,rdx`; `mov rdx,r15`; `call 0xEEC6EC0` (sub_eec6ec0); `add qword ptr [r14+8],0xC8`; `jmp 0x672674D` (-> loc_672674d). Je-target block at 0x67264bf (from phase 3's `je 0x67264bf`): `lea rcx,[r14+0x810]`; `call 0x6760E60` (sub_6760e60); `nop`. TLS seq at 0x67264cc: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov eax,[r14+0x810]`; `not eax`; `add eax,[r14+0x818]`; `mov [rbp+0x12C],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al`. Cursor loop [r14+0x368] vs [r14+0x370]: if equal `je 0x672677A` (-> loc_672677a) else `inc rdx`; `mov [r14+0x368],rdx`; `jmp 0x6726787` (-> loc_6726787). Je-target block at 0x672653f (from phase 4's `je 0x672653f`): `lea rcx,[r15+0x630]`; `lea r8,[rbp+0x598]`; `call 0x14DB710` (sub_14db710; continues next phase: 0x6726552 `nop`).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xEEC6EC0 (sub_eec6ec0, direct), 0x6760E60 (sub_6760e60, direct), 0x14DB710 (sub_14db710, direct).
Fields read: [rbp+0x818] [R], [r14+8] [R], [r14+0x10] [R], [r14+8] [W], [r14+0x810] [R], [rbp+0x12C] [W], [r14+0x818] [R], [rbp+0x818] [W], [r14+0x368] [R/W], [r14+0x370] [R], [r15+0x630] [R], [rbp+0x598] [R].
Fields written: [rbp+0x818], [r14+8], [rbp+0x12C], [r14+0x368].

## Phase 8 (0x6726552..0x672661a)
```
  6726552  nop                                           
  6726553  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672655a  mov rax,[rcx]                                 
  672655d  mov rax,[rax+0x10]                            
  6726561  movzx edx,byte ptr [rbp+0x818]                
  6726568  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672656e  nop                                           
  672656f  mov qword ptr [rbp+0x110],0x6407009           
  672657a  mov eax,[r15+0x638]                           
  6726581  sub eax,[r15+0x630]                           
  6726588  shr eax,2                                     
  672658b  dec eax                                       
  672658d  mov [rbp+0x154],ax                            
  6726594  mov rcx,r15                                   
  6726597  add rcx,0x108                                 
  672659e  lea rdx,[rbp+0x560]                           
  67265a5  call 0x67693F0                                ; -> sub_67693f0
  67265aa  nop                                           
  67265ab  mov qword ptr [rbp+0x118],0x20000             
  67265b6  mov eax,[r15+0x110]                           
  67265bd  sub eax,[r15+0x108]                           
  67265c4  shr eax,3                                     
  67265c7  imul eax,0x6DB7                               
  67265cd  dec eax                                       
  67265cf  mov [rbp+0x1C2],ax                            
  67265d6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67265dd  mov rax,[rcx]                                 
  67265e0  mov rax,[rax+0x10]                            
  67265e4  mov dl,0x4A                                   
  67265e6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67265ec  nop                                           
  67265ed  mov [rbp+0x818],al                            
  67265f3  mov rdx,[r15+8]                               
  67265f7  cmp rdx,[r15+0x10]                            
  67265fb  je 0x6726813                                  ; -> loc_6726813
  6726601  mov r8d,0xC8                                  
  6726607  mov rcx,rdx                                   
  672660a  lea rdx,[rbp+0x110]                           
  6726611  call 0xEEC6EC0                                ; -> sub_eec6ec0
  6726616  add qword ptr [r15+8],0xC8                    
```
// Phase 8: `nop`; TLS seq tail continuing phase 7's `call 0x14DB710`: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. `mov qword ptr [rbp+0x110],0x6407009`. Count calc: `eax=[r15+0x638]`; `sub eax,[r15+0x630]`; `shr eax,2`; `dec eax`; `mov [rbp+0x154],ax`. `mov rcx,r15`; `add rcx,0x108`; `lea rdx,[rbp+0x560]`; `call 0x67693F0` (sub_67693f0); `nop`. `mov qword ptr [rbp+0x118],0x20000`. Count calc (new magic): `eax=[r15+0x110]`; `sub eax,[r15+0x108]`; `shr eax,3`; `imul eax,0x6DB7`; `dec eax`; `mov [rbp+0x1C2],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al`. Cursor loop [r15+8] vs [r15+0x10]: if equal `je 0x6726813` (-> loc_6726813) else `mov r8d,0xC8`; `mov rcx,rdx`; `lea rdx,[rbp+0x110]`; `call 0xEEC6EC0` (sub_eec6ec0); `add qword ptr [r15+8],0xC8` (continues next phase: 0x672661a `jmp` likely).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x67693F0 (sub_67693f0, direct), 0xEEC6EC0 (sub_eec6ec0, direct).
Fields read: [rbp+0x818] [R], [rbp+0x110] [W/R], [r15+0x638] [R], [r15+0x630] [R], [rbp+0x154] [W], [rbp+0x560] [R], [rbp+0x118] [W], [r15+0x110] [R], [r15+0x108] [R], [rbp+0x1C2] [W], [r15+8] [R/W].
Fields written: [rbp+0x818], [rbp+0x110], [rbp+0x154], [rbp+0x118], [rbp+0x1C2], [r15+8].

## Phase 9 (0x672661a..0x67266e1)
```
  672661a  enter 0,0                                     
  672661e  jmp 0x6726823                                 ; -> loc_6726823
  6726623  lea rcx,[r15+0x690]                           
  672662a  lea r8,[rbp+0x5A0]                            
  6726631  call 0x1EF6F90                                ; -> sub_1ef6f90
  6726636  nop                                           
  6726637  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672663e  mov rax,[rcx]                                 
  6726641  mov rax,[rax+0x10]                            
  6726645  movzx edx,byte ptr [rbp+0x818]                
  672664c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726652  nop                                           
  6726653  mov eax,[r15+0x698]                           
  672665a  sub eax,[r15+0x690]                           
  6726661  shr eax,1                                     
  6726663  dec eax                                       
  6726665  mov [rbp+0x14C],ax                            
  672666c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726673  mov rax,[rcx]                                 
  6726676  mov rax,[rax+0x10]                            
  672667a  mov dl,0x4A                                   
  672667c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726682  nop                                           
  6726683  mov [rbp+0x818],al                            
  6726689  mov rdx,[r15+0x638]                           
  6726690  cmp rdx,[r15+0x640]                           
  6726697  je 0x67268C0                                  ; -> loc_67268c0
  672669d  mov eax,[rbp+0x598]                           
  67266a3  mov [rdx],eax                                 
  67266a5  add qword ptr [r15+0x638],4                   
  67266ad  jmp 0x67268D4                                 ; -> loc_67268d4
  67266b2  lea rcx,[r14+0x690]                           
  67266b9  lea r8,[rbp+0x564]                            
  67266c0  call 0x1EF6F90                                ; -> sub_1ef6f90
  67266c5  nop                                           
  67266c6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67266cd  mov rax,[rcx]                                 
  67266d0  mov rax,[rax+0x10]                            
  67266d4  movzx edx,byte ptr [rbp+0x818]                
  67266db  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
// Phase 9: `enter 0,0`; `jmp 0x6726823` (-> loc_6726823). Je-target block at 0x6726623 (from phase 5's `je 0x6726623`): `lea rcx,[r15+0x690]`; `lea r8,[rbp+0x5A0]`; `call 0x1EF6F90` (sub_1ef6f90); `nop`. TLS seq at 0x6726637 (target of phase 5's `jmp 0x6726637`): `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov eax,[r15+0x698]`; `sub eax,[r15+0x690]`; `shr eax,1`; `dec eax`; `mov [rbp+0x14C],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al`. Cursor loop [r15+0x638] vs [r15+0x640]: if equal `je 0x67268C0` (-> loc_67268c0) else `mov eax,[rbp+0x598]`; `mov [rdx],eax`; `add qword ptr [r15+0x638],4`; `jmp 0x67268D4` (-> loc_67268d4). Je-target block at 0x67266b2 (from phase 6's `je 0x67266B2`): `lea rcx,[r14+0x690]`; `lea r8,[rbp+0x564]`; `call 0x1EF6F90` (sub_1ef6f90); `nop`; TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (continues next phase: 0x67266e1 `nop`).

Callees: jmp 0x6726823 (loc_6726823), 0x1EF6F90 (sub_1ef6f90, direct, twice), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rbp+0x818] [R/W], [r15+0x690] [R], [rbp+0x5A0] [R], [rbp+0x14C] [W], [r15+0x698] [R], [r15+0x638] [R/W], [r15+0x640] [R], [rbp+0x598] [R], [rdx] [W], [r14+0x690] [R], [rbp+0x564] [R].
Fields written: [rbp+0x818], [rbp+0x14C], [r15+0x638], [rdx].

## Phase 10 (0x67266e1..0x672679c)
```
  67266e1  nop                                           
  67266e2  mov eax,[r14+0x698]                           
  67266e9  sub eax,[r14+0x690]                           
  67266f0  shr eax,1                                     
  67266f2  dec eax                                       
  67266f4  mov [rbp+0x14C],ax                            
  67266fb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726702  mov rax,[rcx]                                 
  6726705  mov rax,[rax+0x10]                            
  6726709  mov dl,0x4A                                   
  672670b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726711  nop                                           
  6726712  mov [rbp+0x818],al                            
  6726718  mov rdx,[r14+0x638]                           
  672671f  cmp rdx,[r14+0x640]                           
  6726726  je 0x67269A4                                  ; -> loc_67269a4
  672672c  mov eax,[rbp+0x560]                           
  6726732  mov [rdx],eax                                 
  6726734  add qword ptr [r14+0x638],4                   
  672673c  jmp 0x67269BB                                 ; -> loc_67269bb
  6726741  mov rcx,r14                                   
  6726744  mov r8,r15                                    
  6726747  call 0x5ABA6D0                                ; -> sub_5aba6d0
  672674c  nop                                           
  672674d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726754  mov rax,[rcx]                                 
  6726757  mov rax,[rax+0x10]                            
  672675b  movzx edx,byte ptr [rbp+0x818]                
  6726762  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726768  nop                                           
  6726769  lea rcx,[rbp+0x560]                           
  6726770  call 0x67E1660                                ; -> sub_67e1660
  6726775  jmp 0x6727750                                 ; -> loc_6727750
  672677a  lea rcx,[r14+0x360]                           
  6726781  call 0x6760E60                                ; -> sub_6760e60
  6726786  nop                                           
  6726787  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672678e  mov rax,[rcx]                                 
  6726791  mov rax,[rax+0x10]                            
  6726795  movzx edx,byte ptr [rbp+0x818]                
```
// Phase 10: `nop`; TLS seq tail continuing phase 9's `call 0x1EF6F90`: `mov eax,[r14+0x698]`; `sub eax,[r14+0x690]`; `shr eax,1`; `dec eax`; `mov [rbp+0x14C],ax`. TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x818],al`. Cursor loop [r14+0x638] vs [r14+0x640]: if equal `je 0x67269A4` (-> loc_67269a4) else `mov eax,[rbp+0x560]`; `mov [rdx],eax`; `add qword ptr [r14+0x638],4`; `jmp 0x67269BB` (-> loc_67269bb). Je-target block at 0x6726741 (from phase 7's `je 0x6726741`): `mov rcx,r14`; `mov r8,r15`; `call 0x5ABA6D0` (sub_5aba6d0); `nop`. TLS seq at 0x672674d: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop`; `lea rcx,[rbp+0x560]`; `call 0x67E1660` (sub_67e1660); `jmp 0x6727750` (-> loc_6727750). Je-target block at 0x672677a (from phase 3's `je 0x672677A`): `lea rcx,[r14+0x360]`; `call 0x6760E60` (sub_6760e60); `nop`; TLS seq start: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]` (continues next phase: 0x672679c `call qword ptr [0xF99FFA0]`; `movzx edx,byte ptr [rbp+0x818]` at 0x6726795 is 7 bytes, so the call lands at 0x672679c).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x5ABA6D0 (sub_5aba6d0, direct), 0x67E1660 (sub_67e1660, direct), jmp 0x6727750 (loc_6727750), 0x6760E60 (sub_6760e60, direct).
Fields read: [rbp+0x14C] [W], [r14+0x698] [R], [r14+0x690] [R], [rbp+0x818] [R/W], [r14+0x638] [R/W], [r14+0x640] [R], [rbp+0x560] [R/W], [rdx] [W], [rbp+0x560] [R].
Fields written: [rbp+0x14C], [rbp+0x818], [r14+0x638], [rdx].

## Phase 11 (0x672679c..0x6726865)
```
  672679c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67267a2  nop                                           
  67267a3  mov rax,0x100000002807049                     
  67267ad  mov [rbp+0x110],rax                           
  67267b4  mov eax,[r14+0x360]                           
  67267bb  not eax                                       
  67267bd  add eax,[r14+0x368]                           
  67267c4  mov [rbp+0x190],ax                            
  67267cb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67267d2  mov rax,[rcx]                                 
  67267d5  mov rax,[rax+0x10]                            
  67267d9  mov dl,0x4A                                   
  67267db  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67267e1  nop                                           
  67267e2  mov [rbp+0x818],al                            
  67267e8  mov rdx,[r14+0x698]                           
  67267ef  cmp rdx,[r14+0x6A0]                           
  67267f6  je 0x6726A4B                                  ; -> loc_6726a4b
  67267fc  movzx eax,word ptr [rbp+0x564]                
  6726803  mov [rdx],ax                                  
  6726806  add qword ptr [r14+0x698],2                   
  672680e  jmp 0x6726A5F                                 ; -> loc_6726a5f
  6726813  mov rcx,r15                                   
  6726816  lea r8,[rbp+0x110]                            
  672681d  call 0x5ABA6D0                                ; -> sub_5aba6d0
  6726822  nop                                           
  6726823  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672682a  mov rax,[rcx]                                 
  672682d  mov rax,[rax+0x10]                            
  6726831  movzx edx,byte ptr [rbp+0x818]                
  6726838  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672683e  nop                                           
  672683f  cmp byte ptr [rbp+0x6C8],1                    
  6726846  jne short 0x672689A                           ; -> loc_672689a
  6726848  mov rcx,[rbp+0x688]                           
  672684f  test rcx,rcx                                  
  6726852  je short 0x672689A                            ; -> loc_672689a
  6726854  mov rdx,[rbp+0x698]                           
  672685b  sub rdx,rcx                                   
  672685e  cmp rdx,0x1000                                
```
// Phase 11: TLS seq tail continuing phase 10's `call 0x6760E60` path: `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`. `mov rax,0x100000002807049`; `mov [rbp+0x110],rax`. `mov eax,[r14+0x360]`; `not eax`; `add eax,[r14+0x368]`; `mov [rbp+0x190],ax`. TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x818],al`. Cursor loop [r14+0x698] vs [r14+0x6A0]: if equal `je 0x6726A4B` (-> loc_6726a4b) else `movzx eax,word ptr [rbp+0x564]`; `mov [rdx],ax`; `add qword ptr [r14+0x698],2`; `jmp 0x6726A5F` (-> loc_6726a5f). Je-target block at 0x6726813 (from phase 8's `je 0x6726813`): `mov rcx,r15`; `lea r8,[rbp+0x110]`; `call 0x5ABA6D0` (sub_5aba6d0); `nop`. TLS seq at 0x6726823: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop`. New branch: `cmp byte ptr [rbp+0x6C8],1`; if not equal `jne short 0x672689A` (-> loc_672689a); `mov rcx,[rbp+0x688]`; `test rcx,rcx`; if zero `je short 0x672689A`; `mov rdx,[rbp+0x698]`; `sub rdx,rcx`; `cmp rdx,0x1000` (continues next phase: 0x6726865).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x5ABA6D0 (sub_5aba6d0, direct).
Fields read: [rbp+0x818] [R/W], [rbp+0x110] [W], [r14+0x360] [R], [rbp+0x190] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [r14+0x698] [R/W], [r14+0x6A0] [R], [rbp+0x564] [R], [rdx] [W], [rbp+0x6C8] [R], [rbp+0x688] [R], [rbp+0x698] [R].
Fields written: [rbp+0x110], [rbp+0x190], [rbp+0x818], [r14+0x698], [rdx].

## Phase 12 (0x6726865..0x672692c)
```
  6726865  jb short 0x6726883                            ; -> loc_6726883
  6726867  mov rax,[rcx-8]                               ; R a0-0x8
  672686b  add rcx,0xFFFFFFFFFFFFFFF8                    
  672686f  sub rcx,rax                                   
  6726872  cmp rcx,0x20                                  
  6726876  jae 0x672A337                                 ; -> sub_672a337
  672687c  or rdx,0x27                                   
  6726880  mov rcx,rax                                   

loc_6726883:  ; from 6726865
  6726883  call 0xE935700                                ; -> sub_e935700
  6726888  lea rax,[rbp+0x688]                           
  672688f  movups [rax],xmm6                             
  6726892  mov qword ptr [rax+0x10],0                    
  672689a  lea rcx,[rbp+0x560]                           
  67268a1  call 0x6791DD0                                ; -> sub_6791dd0
  67268a6  lea rcx,[rbp+0x370]                           
  67268ad  call 0x67E23F0                                ; -> sub_67e23f0
  67268b2  test r14,r14                                  
  67268b5  jne 0x6726BBE                                 ; -> loc_6726bbe
  67268bb  jmp 0x6726BEB                                 ; -> loc_6726beb
  67268c0  lea rcx,[r15+0x630]                           
  67268c7  lea r8,[rbp+0x598]                            
  67268ce  call 0x14DB710                                ; -> sub_14db710
  67268d3  nop                                           
  67268d4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67268db  mov rax,[rcx]                                 
  67268de  mov rax,[rax+0x10]                            
  67268e2  movzx edx,byte ptr [rbp+0x818]                
  67268e9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67268ef  nop                                           
  67268f0  mov qword ptr [rbp+0x110],0x6C07009           
  67268fb  mov eax,[r15+0x638]                           
  6726902  sub eax,[r15+0x630]                           
  6726909  shr eax,2                                     
  672690c  dec eax                                       
  672690e  mov [rbp+0x154],ax                            
  6726915  mov rcx,r15                                   
  6726918  add rcx,0x108                                 
  672691f  lea rdx,[rbp+0x560]                           
  6726926  call 0x67693F0                                ; -> sub_67693f0
  672692b  nop                                           
```
// Phase 12: `jb short 0x6726883` from phase 11's `cmp rdx,0x1000`. Fall-through: `mov rax,[rcx-8]`; `add rcx,0xFFFFFFFFFFFFFFF8` (rcx -= 8); `sub rcx,rax`; `cmp rcx,0x20`; if above-or-equal `jae 0x672A337` (-> sub_672a337) else `or rdx,0x27`; `mov rcx,rax`. loc_6726883 (jb target): `call 0xE935700` (sub_e935700); `lea rax,[rbp+0x688]`; `movups [rax],xmm6`; `mov qword ptr [rax+0x10],0`. `lea rcx,[rbp+0x560]`; `call 0x6791DD0` (sub_6791dd0); `lea rcx,[rbp+0x370]`; `call 0x67E23F0` (sub_67e23f0); `test r14,r14`; if not equal `jne 0x6726BBE` (-> loc_6726bbe) else `jmp 0x6726BEB` (-> loc_6726beb). Je-target block at 0x67268c0 (from phase 9's `je 0x67268C0`): `lea rcx,[r15+0x630]`; `lea r8,[rbp+0x598]`; `call 0x14DB710` (sub_14db710); `nop`. TLS seq at 0x67268d4: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov qword ptr [rbp+0x110],0x6C07009`. Count calc: `eax=[r15+0x638]`; `sub eax,[r15+0x630]`; `shr eax,2`; `dec eax`; `mov [rbp+0x154],ax`. `mov rcx,r15`; `add rcx,0x108`; `lea rdx,[rbp+0x560]`; `call 0x67693F0` (sub_67693f0); `nop` (continues next phase: 0x672692c).

Callees: jb 0x6726883 (loc_6726883), 0xE935700 (sub_e935700, direct), jae 0x672A337 (sub_672a337), [0xF99FFA0] = sub_eea6040 (indirect), 0x6791DD0 (sub_6791dd0, direct), 0x67E23F0 (sub_67e23f0, direct), jne 0x6726BBE / jmp 0x6726BEB, 0x14DB710 (sub_14db710, direct), 0x67693F0 (sub_67693f0, direct).
Fields read: [rbp+0x818] [R], [rcx-8] [R], [rbp+0x688] [R/W], [rax] [W xmm6], [rax+0x10] [W], [rbp+0x560] [R], [rbp+0x370] [R], [r15+0x630] [R], [rbp+0x598] [R], [rbp+0x110] [W], [r15+0x638] [R], [r15+0x630] [R], [rbp+0x154] [W].
Fields written: [rbp+0x688], [rax], [rax+0x10], [rbp+0x110], [rbp+0x154].

## Phase 13 (0x672692c..0x67269fb)
```
  672692c  mov qword ptr [rbp+0x118],0x20000             
  6726937  mov eax,[r15+0x110]                           
  672693e  sub eax,[r15+0x108]                           
  6726945  shr eax,3                                     
  6726948  imul eax,0x6DB7                               
  672694e  dec eax                                       
  6726950  mov [rbp+0x1C2],ax                            
  6726957  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672695e  mov rax,[rcx]                                 
  6726961  mov rax,[rax+0x10]                            
  6726965  mov dl,0x4A                                   
  6726967  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672696d  nop                                           
  672696e  mov [rbp+0x818],al                            
  6726974  mov rdx,[r15+8]                               
  6726978  cmp rdx,[r15+0x10]                            
  672697c  je 0x6726B1A                                  ; -> loc_6726b1a
  6726982  mov r8d,0xC8                                  
  6726988  mov rcx,rdx                                   
  672698b  lea rdx,[rbp+0x110]                           
  6726992  call 0xEEC6EC0                                ; -> sub_eec6ec0
  6726997  add qword ptr [r15+8],0xC8                    
  672699f  jmp 0x6726B2A                                 ; -> loc_6726b2a
  67269a4  mov rcx,r14                                   
  67269a7  add rcx,0x630                                 
  67269ae  lea r8,[rbp+0x560]                            
  67269b5  call 0x14DB710                                ; -> sub_14db710
  67269ba  nop                                           
  67269bb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67269c2  mov rax,[rcx]                                 
  67269c5  mov rax,[rax+0x10]                            
  67269c9  movzx edx,byte ptr [rbp+0x818]                
  67269d0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67269d6  nop                                           
  67269d7  mov rax,0x100000006407049                     
  67269e1  mov [rbp+0x110],rax                           
  67269e8  mov eax,[r14+0x638]                           
  67269ef  sub eax,[r14+0x630]                           
  67269f6  shr eax,2                                     
  67269f9  dec eax                                       
```
// Phase 13: `mov qword ptr [rbp+0x118],0x20000` tails phase 12's `call 0x67693F0`. Count calc: `eax=[r15+0x110]`; `sub eax,[r15+0x108]`; `shr eax,3`; `imul eax,0x6DB7`; `dec eax`; `mov [rbp+0x1C2],ax`. TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x818],al`. Cursor loop [r15+8] vs [r15+0x10]: if equal `je 0x6726B1A` (-> loc_6726b1a) else `mov r8d,0xC8`; `mov rcx,rdx`; `lea rdx,[rbp+0x110]`; `call 0xEEC6EC0` (sub_eec6ec0); `add qword ptr [r15+8],0xC8`; `jmp 0x6726B2A` (-> loc_6726b2a). Je-target block at 0x67269a4 (from phase 10's `je 0x67269A4`): `mov rcx,r14`; `add rcx,0x630`; `lea r8,[rbp+0x560]`; `call 0x14DB710` (sub_14db710); `nop`. TLS seq at 0x67269bb: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop`; `mov rax,0x100000006407049`; `mov [rbp+0x110],rax`. Count calc: `eax=[r14+0x638]`; `sub eax,[r14+0x630]`; `shr eax,2`; `dec eax` (continues next phase: 0x67269fb — `dec eax` is 2 bytes, so the next instruction starts at 0x67269fb, expected `mov [rbp+0x154],ax` per the same count-calc pattern seen in phases 4/8).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xEEC6EC0 (sub_eec6ec0, direct), 0x14DB710 (sub_14db710, direct).
Fields read: [rbp+0x118] [W], [r15+0x110] [R], [r15+0x108] [R], [rbp+0x1C2] [W], [rbp+0x818] [R/W], [r15+8] [R/W], [r15+0x10] [R], [rbp+0x110] [R], [r14+0x630] [R], [rbp+0x560] [R], [rbp+0x818] [R], [rbp+0x110] [W], [r14+0x638] [R], [r14+0x630] [R], [rbp+0x154] [W].
Fields written: [rbp+0x118], [rbp+0x1C2], [rbp+0x818], [r15+8], [rbp+0x110], [rbp+0x154].

## Phase 14 (0x67269fb..0x6726ab5)
```
  67269fb  mov [rbp+0x154],ax                            
  6726a02  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726a09  mov rax,[rcx]                                 
  6726a0c  mov rax,[rax+0x10]                            
  6726a10  mov dl,0x4A                                   
  6726a12  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726a18  nop                                           
  6726a19  mov [rbp+0x818],al                            
  6726a1f  mov rdx,[r14+8]                               
  6726a23  cmp rdx,[r14+0x10]                            
  6726a27  je 0x6726ADA                                  ; -> loc_6726ada
  6726a2d  mov r8d,0xC8                                  
  6726a33  mov rcx,rdx                                   
  6726a36  mov rdx,r15                                   
  6726a39  call 0xEEC6EC0                                ; -> sub_eec6ec0
  6726a3e  add qword ptr [r14+8],0xC8                    
  6726a46  jmp 0x6726AE6                                 ; -> loc_6726ae6
  6726a4b  lea rcx,[r14+0x690]                           
  6726a52  lea r8,[rbp+0x564]                            
  6726a59  call 0x1EF6F90                                ; -> sub_1ef6f90
  6726a5e  nop                                           
  6726a5f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726a66  mov rax,[rcx]                                 
  6726a69  mov rax,[rax+0x10]                            
  6726a6d  movzx edx,byte ptr [rbp+0x818]                
  6726a74  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726a7a  nop                                           
  6726a7b  mov [rbp+0x818],al                            
  6726ab1  mov rdx,[r14+0x638]                           
```
// Phase 14: `mov [rbp+0x154],ax` tails phase 13's count calc. TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x818],al`. Cursor loop [r14+8] vs [r14+0x10]: if equal `je 0x6726ADA` (-> loc_6726ada) else `mov r8d,0xC8`; `mov rcx,rdx`; `mov rdx,r15`; `call 0xEEC6EC0` (sub_eec6ec0); `add qword ptr [r14+8],0xC8`; `jmp 0x6726AE6` (-> loc_6726ae6). Je-target block at 0x6726a4b (from phase 11's `je 0x6726A4B`): `lea rcx,[r14+0x690]`; `lea r8,[rbp+0x564]`; `call 0x1EF6F90` (sub_1ef6f90); `nop`. TLS seq at 0x6726a5f (target of phase 11's `jmp 0x6726A5F`): `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop`; `mov eax,[r14+0x698]`; `sub eax,[r14+0x690]`; `shr eax,1`; `dec eax`; `mov [rbp+0x14C],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al`; `mov rdx,[r14+0x638]` (continues next phase: 0x6726ab8 — `mov rdx,[r14+0x638]` at 0x6726ab1 is the 7-byte disp32 form, so the cursor loop's `cmp` is at 0x6726ab8).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xEEC6EC0 (sub_eec6ec0, direct), 0x1EF6F90 (sub_1ef6f90, direct).
Fields read: [rbp+0x154] [W], [rbp+0x818] [R/W], [r14+8] [R/W], [r14+0x10] [R], [r14+0x690] [R], [rbp+0x564] [R], [rbp+0x14C] [W], [r14+0x638] [R].
Fields written: [rbp+0x154], [rbp+0x818], [r14+8], [rdx].

## Phase 15 (0x6726ab8..0x6726b72)
```
  6726ab8  cmp rdx,[r14+0x640]                           
  6726abf  je 0x6726CE5                                  ; -> loc_6726ce5
  6726ac5  mov eax,[rbp+0x560]                           
  6726acb  mov [rdx],eax                                 ; W a1+0x0
  6726acd  add qword ptr [r14+0x638],4                   
  6726ad5  jmp 0x6726CFC                                 ; -> loc_6726cfc
  6726ada  mov rcx,r14                                   
  6726add  mov r8,r15                                    
  6726ae0  call 0x5ABA6D0                                ; -> sub_5aba6d0
  6726ae5  nop                                           
  6726ae6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726aed  mov rax,[rcx]                                 
  6726af0  mov rax,[rax+0x10]                            
  6726af4  movzx edx,byte ptr [rbp+0x818]                
  6726afb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726b01  nop                                           
  6726b02  lea rcx,[rbp+0x560]                           
  6726b09  call 0x67E1660                                ; -> sub_67e1660
  6726b0e  lea rcx,[rbp+0x370]                           
  6726b15  jmp 0x672A1A0                                 ; -> sub_672a1a0
  6726b1a  mov rcx,r15                                   
  6726b1d  lea r8,[rbp+0x110]                            
  6726b24  call 0x5ABA6D0                                ; -> sub_5aba6d0
  6726b29  nop                                           
  6726b2a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726b31  mov rax,[rcx]                                 
  6726b34  mov rax,[rax+0x10]                            
  6726b38  movzx edx,byte ptr [rbp+0x818]                
  6726b3f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726b45  nop                                           
  6726b46  cmp byte ptr [rbp+0x6D8],1                    
  6726b4d  jne short 0x6726BA1                           ; -> loc_6726ba1
  6726b4f  mov rcx,[rbp+0x698]                           
  6726b56  test rcx,rcx                                  
  6726b59  je short 0x6726BA1                            ; -> loc_6726ba1
  6726b5b  mov rdx,[rbp+0x6A8]                           
  6726b62  sub rdx,rcx                                   
  6726b65  cmp rdx,0x1000                                
  6726b6c  jb short 0x6726B8A                            ; -> loc_6726b8a
  6726b6e  mov rax,[rcx-8]                               ; R a0-0x8
```
// Phase 15: continuation of phase 14's cursor loop: `cmp rdx,[r14+0x640]`; if equal `je 0x6726CE5` (-> loc_6726ce5) else `mov eax,[rbp+0x560]`; `mov [rdx],eax`; `add qword ptr [r14+0x638],4`; `jmp 0x6726CFC` (-> loc_6726cfc). Je-target block at 0x6726ada (from phase 14's `je 0x6726ADA`): `mov rcx,r14`; `mov r8,r15`; `call 0x5ABA6D0` (sub_5aba6d0); `nop`. TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `lea rcx,[rbp+0x560]`; `call 0x67E1660` (sub_67e1660); `jmp 0x672A1A0` (-> sub_672a1a0; tail jump). Je-target block at 0x6726b1a (from phase 13's `je 0x6726B1A`): `mov rcx,r15`; `lea r8,[rbp+0x110]`; `call 0x5ABA6D0` (sub_5aba6d0); `nop`. TLS seq at 0x6726b2a: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop`. New branch: `cmp byte ptr [rbp+0x6D8],1`; if not equal `jne short 0x6726BA1` (-> loc_6726ba1); `mov rcx,[rbp+0x698]`; `test rcx,rcx`; if zero `je short 0x6726BA1`; `mov rdx,[rbp+0x6A8]`; `sub rdx,rcx`; `cmp rdx,0x1000`; if below `jb short 0x6726B8A` (-> loc_6726b8a); `mov rax,[rcx-8]`; `add rcx,0xFFFFFFFFFFFFFFF8` (rcx -= 8); `sub rcx,rax`; `cmp rcx,0x20` (continues next phase: 0x6726b72).

Callees: 0x5ABA6D0 (sub_5aba6d0, direct, twice), [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x67E1660 (sub_67e1660, direct), jmp 0x672A1A0 (sub_672a1a0, tail).
Fields read: [r14+0x640] [R], [rbp+0x560] [R], [rdx] [W], [r14+0x638] [R/W], [rbp+0x818] [R/W], [rbp+0x110] [R], [rbp+0x6D8] [R], [rbp+0x698] [R], [rbp+0x6A8] [R], [rcx-8] [R].
Fields written: [rdx], [r14+0x638], [rbp+0x818].

## Phase 16 (0x6726b72..0x6726c12)
```
  6726b72  add rcx,0xFFFFFFFFFFFFFFF8                    
  6726b76  sub rcx,rax                                   
  6726b79  cmp rcx,0x20                                  
  6726b7d  jae 0x672A337                                 ; -> sub_672a337
  6726b83  or rdx,0x27                                   
  6726b87  mov rcx,rax                                   
  6726b8a  call 0xE935700                                ; -> sub_e935700
  6726b8f  lea rax,[rbp+0x698]                           
  6726b96  movups [rax],xmm6                             
  6726b99  mov qword ptr [rax+0x10],0                    
  6726ba1  lea rcx,[rbp+0x560]                           
  6726ba8  call 0x6791730                                ; -> sub_6791730
  6726bad  lea rcx,[rbp+0x370]                           
  6726bb4  call 0x67E1660                                ; -> sub_67e1660
  6726bb9  test r14,r14                                  
  6726bbc  je short 0x6726BEB                            ; -> loc_6726beb
  6726bbe  lock dec dword ptr [r14+8]                    
  6726bc3  jne short 0x6726BEB                           ; -> loc_6726beb
  6726bc5  mov rax,[r14]                                 
  6726bc8  mov rax,[rax]                                 
  6726bcb  mov rcx,r14                                   
  6726bce  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726bd4  lock dec dword ptr [r14+0xC]                  
  6726bd9  jne short 0x6726BEB                           ; -> loc_6726beb
  6726bdb  mov rax,[r14]                                 
  6726bde  mov rax,[rax+8]                               
  6726be2  mov rcx,r14                                   
  6726be5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_6726beb:  ; from 6726bbc, 6726bc3, 6726bd9
  6726beb  mov rdi,[rbp+0x2A8]                           
  6726bf2  test rdi,rdi                                  
  6726bf5  je short 0x6726C22                            ; -> loc_6726c22
  6726bf7  lock dec dword ptr [rdi+8]                    
  6726bfb  jne short 0x6726C22                           ; -> loc_6726c22
  6726bfd  mov rax,[rdi]                                 
  6726c00  mov rax,[rax]                                 
  6726c03  mov rcx,rdi                                   
  6726c06  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726c0c  lock dec dword ptr [rdi+0xC]                  
  6726c10  jne short 0x6726C22                           ; -> loc_6726c22
  6726c12  mov rax,[rdi]                                 
```
// Phase 16: continuation of phase 15's not-below path: `add rcx,0xFFFFFFFFFFFFFFF8` (rcx -= 8); `sub rcx,rax`; `cmp rcx,0x20`; if above-or-equal `jae 0x672A337` (-> sub_672a337) else `or rdx,0x27`; `mov rcx,rax`. loc_6726b8a (phase 15's `jb short 0x6726B8A` target): `call 0xE935700` (sub_e935700); `lea rax,[rbp+0x698]`; `movups [rax],xmm6`; `mov qword ptr [rax+0x10],0`. loc_6726ba1 (phase 15's `jne`/`je short 0x6726BA1` targets): `lea rcx,[rbp+0x560]`; `call 0x6791730` (sub_6791730); `lea rcx,[rbp+0x370]`; `call 0x67E1660` (sub_67e1660); `test r14,r14`; if zero `je short 0x6726BEB` else `lock dec dword ptr [r14+8]`; if result nonzero `jne short 0x6726BEB`; `mov rax,[r14]`; `mov rax,[rax]`; `mov rcx,r14`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `lock dec dword ptr [r14+0xC]`; if nonzero `jne short 0x6726BEB`; `mov rax,[r14]`; `mov rax,[rax+8]`; `mov rcx,r14`; `call qword ptr [0xF99FFA0]` (sub_eea6040). loc_6726beb (branch targets from 0x6726bbc/0x6726bc3/0x6726bd9): `mov rdi,[rbp+0x2A8]`; `test rdi,rdi`; if zero `je short 0x6726C22` (-> loc_6726c22); `lock dec dword ptr [rdi+8]`; if nonzero `jne short 0x6726C22`; `mov rax,[rdi]`; `mov rax,[rax]`; `mov rcx,rdi`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `lock dec dword ptr [rdi+0xC]`; if nonzero `jne short 0x6726C22`; `mov rax,[rdi]` (continues next phase: 0x6726c12).

Callees: 0xE935700 (sub_e935700, direct), 0x6791730 (sub_6791730, direct), 0x67E1660 (sub_67e1660, direct), [0xF99FFA0] = sub_eea6040 (indirect, three times).
Fields read: [rbp+0x698] [R/W], [rbp+0x560] [R], [rbp+0x370] [R], [r14+8] [R/W], [r14] [R], [rax] [R], [r14+0xC] [R/W], [rax+8] [R], [rbp+0x2A8] [R], [rdi+8] [R/W], [rdi] [R], [rdi+0xC] [R/W].
Fields written: [rbp+0x698], [r14+8], [r14+0xC], [rbp+0x2A8] via rdi, [rdi+8], [rdi+0xC].

## Phase 17 (0x6726c12..0x6726ca0)
```
  6726c12  mov rax,[rdi]                                 
  6726c15  mov rax,[rax+8]                               
  6726c19  mov rcx,rdi                                   
  6726c1c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_6726c22:  ; from 6726c0c
  6726c22  mov rdi,[rbp+0x7B8]                           
  6726c29  test rdi,rdi                                  
  6726c2c  je short 0x6726C59                            ; -> loc_6726c59
  6726c2e  lock dec dword ptr [rdi+8]                    
  6726c32  jne short 0x6726C59                           ; -> loc_6726c59
  6726c34  mov rax,[rdi]                                 
  6726c37  mov rax,[rax]                                 
  6726c3a  mov rcx,rdi                                   
  6726c3d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726c43  lock dec dword ptr [rdi+0xC]                  
  6726c47  jne short 0x6726C59                           ; -> loc_6726c59
  6726c49  mov rax,[rdi]                                 
  6726c4c  mov rax,[rax+8]                               
  6726c50  mov rcx,rdi                                   
  6726c53  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_6726c59:  ; from 6726c2c, 6726c32, 6726c47
  6726c59  mov rdi,[rbp+0x7A8]                           
  6726c60  test rdi,rdi                                  
  6726c63  je short 0x6726C90                            ; -> loc_6726c90
  6726c65  lock dec dword ptr [rdi+8]                    
  6726c69  jne short 0x6726C90                           ; -> loc_6726c90
  6726c6b  mov rax,[rdi]                                 
  6726c6e  mov rax,[rax]                                 
  6726c71  mov rcx,rdi                                   
  6726c74  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726c7a  lock dec dword ptr [rdi+0xC]                  
  6726c7e  jne short 0x6726C90                           ; -> loc_6726c90
  6726c80  mov rax,[rdi]                                 
  6726c83  mov rax,[rax+8]                               
  6726c87  mov rcx,rdi                                   
  6726c8a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_6726c90:  ; from 6726c63, 6726c69, 6726c7e
  6726c90  mov rdi,[rbp+0x768]                           
  6726c97  test rdi,rdi                                  
  6726c9a  je 0x672775C                                  ; -> loc_672775c
```
// Phase 17: continuation of loc_6726beb path: `mov rax,[rdi]`; `mov rax,[rax+8]`; `mov rcx,rdi`; `call qword ptr [0xF99FFA0]` (sub_eea6040). loc_6726c22 (phase 16's `jne short 0x6726C22` target): `mov rdi,[rbp+0x7B8]`; `test rdi,rdi`; if zero `je short 0x6726C59`; `lock dec dword ptr [rdi+8]`; if nonzero `jne short 0x6726C59`; `mov rax,[rdi]`; `mov rax,[rax]`; `mov rcx,rdi`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `lock dec dword ptr [rdi+0xC]`; if nonzero `jne short 0x6726C59`; `mov rax,[rdi]`; `mov rax,[rax+8]`; `mov rcx,rdi`; `call qword ptr [0xF99FFA0]` (sub_eea6040). loc_6726c59: `mov rdi,[rbp+0x7A8]`; same release pattern: `test rdi,rdi`; `je short 0x6726C90`; `lock dec dword ptr [rdi+8]`; `jne short 0x6726C90`; `mov rax,[rdi]`; `mov rax,[rax]`; `mov rcx,rdi`; `call qword ptr [0xF99FFA0]`; `lock dec dword ptr [rdi+0xC]`; `jne short 0x6726C90`; `mov rax,[rdi]`; `mov rax,[rax+8]`; `mov rcx,rdi`; `call qword ptr [0xF99FFA0]`. loc_6726c90: `mov rdi,[rbp+0x768]`; `test rdi,rdi`; if zero `je 0x672775C` (-> loc_672775c); `lock dec dword ptr [rdi+8]`; if nonzero `jne 0x672775C`; `mov rax,[rdi]` (continues next phase: 0x6726ca0).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, four times).
Fields read: [rbp+0x7B8] [R], [rdi+8] [R/W] (lock), [rbp+0x7A8] [R], [rbp+0x768] [R], [rdi] [R], [rax] [R].
Fields written: [rdi+8] (lock), [rdi+0xC] (lock).

## Phase 18 (0x6726ca0..0x6726d5d)
```
  6726ca0  lock dec dword ptr [rdi+8]                    
  6726ca4  jne 0x672775C                                 ; -> loc_672775c
  6726caa  mov rax,[rdi]                                 
  6726cad  mov rax,[rax]                                 
  6726cb0  mov rcx,rdi                                   
  6726cb3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726cb9  lock dec dword ptr [rdi+0xC]                  
  6726cbd  jne 0x672775C                                 ; -> loc_672775c
  6726cc3  mov rax,[rdi]                                 
  6726cc6  mov rax,[rax+8]                               
  6726cca  mov rcx,rdi                                   
  6726ccd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726cd3  cmp byte ptr [rbp+0x80],3                     
  6726cda  je 0x672A1AE                                  ; -> sub_672a1ae
  6726ce0  jmp 0x672A1F0                                 ; -> sub_672a1f0
  6726ce5  mov rcx,r14                                   
  6726ce8  add rcx,0x630                                 
  6726cef  lea r8,[rbp+0x560]                            
  6726cf6  call 0x14DB710                                ; -> sub_14db710
  6726cfb  nop                                           
  6726cfc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726d03  mov rax,[rcx]                                 
  6726d06  mov rax,[rax+0x10]                            
  6726d0a  movzx edx,byte ptr [rbp+0x818]                
  6726d11  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726d17  nop                                           
  6726d18  mov rax,0x100000006C07049                     
  6726d22  mov [rbp+0x110],rax                           
  6726d29  mov eax,[r14+0x638]                           
  6726d30  sub eax,[r14+0x630]                           
  6726d37  shr eax,2                                     
  6726d3a  dec eax                                       
  6726d3c  mov [rbp+0x154],ax                            
  6726d43  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726d4a  mov rax,[rcx]                                 
  6726d4d  mov rax,[rax+0x10]                            
  6726d51  mov dl,0x4A                                   
  6726d53  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726d59  nop                                           
  6726d5a  mov [rbp+0x818],al                            
```
// Phase 18: continuation of loc_6726c90 path: `lock dec dword ptr [rdi+8]`; if nonzero `jne 0x672775C` (-> loc_672775c); `mov rax,[rdi]`; `mov rax,[rax]`; `mov rcx,rdi`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `lock dec dword ptr [rdi+0xC]`; if nonzero `jne 0x672775C`; `mov rax,[rdi]`; `mov rax,[rax+8]`; `mov rcx,rdi`; `call qword ptr [0xF99FFA0]` (sub_eea6040). `cmp byte ptr [rbp+0x80],3`; if equal `je 0x672A1AE` (-> sub_672a1ae) else `jmp 0x672A1F0` (-> sub_672a1f0; tail jumps). Je-target block at 0x6726ce5 (from phase 15's `je 0x6726CE5`): `mov rcx,r14`; `add rcx,0x630`; `lea r8,[rbp+0x560]`; `call 0x14DB710` (sub_14db710); `nop`. TLS seq at 0x6726cfc: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov rax,0x100000006C07049`; `mov [rbp+0x110],rax`. Count calc: `eax=[r14+0x638]`; `sub eax,[r14+0x630]`; `shr eax,2`; `dec eax`; `mov [rbp+0x154],ax`. TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]`; `nop`; `mov [rbp+0x818],al` (continues next phase: 0x6726d6b — `mov [rbp+0x818],al` at 0x6726d5a is the 6-byte disp32 form (same as phase 2's 0x67260d0, 6 bytes), ending at 0x6726d60; bytes 0x6726d60..0x6726d6b are padding that rdis mis-decodes as garbage instructions starting at 0x6726d5d (mid-instruction); real code resumes at 0x6726d6b `mov eax,0xC8`).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x14DB710 (sub_14db710, direct), je 0x672A1AE (sub_672a1ae), jmp 0x672A1F0 (sub_672a1f0).
Fields read: [rdi+8] [R/W lock], [rdi] [R], [rax] [R], [rdi+0xC] [R/W lock], [rax+8] [R], [rbp+0x80] [R], [rbp+0x110] [W], [r14+0x638] [R], [r14+0x630] [R], [rbp+0x154] [W], [rbp+0x818] [R/W].
Fields written: [rdi+8], [rdi+0xC], [rbp+0x110], [rbp+0x154], [rbp+0x818].

## Phase 19 (0x6726d6b..0x6726e2a)
```
  6726d6b  mov eax,0xC8                                  
  6726d70  mov rcx,rdx                                   
  6726d73  mov rdx,r15                                   
  6726d76  call 0xEEC6EC0                                ; -> sub_eec6ec0
  6726d7b  add qword ptr [r14+8],0xC8                    
  6726d83  jmp short 0x6726D91                           ; -> loc_6726d91
  6726d85  mov rcx,r14                                   
  6726d88  mov r8,r15                                    
  6726d8b  call 0x5ABA6D0                                ; -> sub_5aba6d0
  6726d90  nop                                           

loc_6726d91:  ; from 6726d83
  6726d91  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726d98  mov rax,[rcx]                                 
  6726d9b  mov rax,[rax+0x10]                            
  6726d9f  movzx edx,byte ptr [rbp+0x818]                
  6726da6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726dac  nop                                           
  6726dad  lea rcx,[rbp+0x560]                           
  6726db4  call 0x67E40A0                                ; -> sub_67e40a0
  6726db9  jmp 0x6727750                                 ; -> loc_6727750
  6726dbe  lea rcx,[rbp+0x510]                           
  6726dc5  mov rdx,r15                                   
  6726dc8  call 0x67A75D0                                ; -> sub_67a75d0
  6726dcd  nop                                           
  6726dce  lea rcx,[rbp+0x370]                           
  6726dd5  lea rdx,[rbp+0x1F0]                           
  6726ddc  lea r8,[rbp+0x198]                            
  6726de3  mov r9,r15                                    
  6726de6  call 0x678F640                                ; -> sub_678f640
  6726deb  nop                                           
  6726dec  mov eax,[r13+0x60]                            
  6726df0  lea rcx,[rbp+0x4A8]                           
  6726df7  mov [rcx+0x10],eax                            
  6726dfa  movups xmm0,[r13+0x50]                        
  6726dff  movups [rcx],xmm0                             
```
// Phase 19: cursor-loop body: `mov eax,0xC8`; `mov rcx,rdx`; `mov rdx,r15`; `call 0xEEC6EC0` (sub_eec6ec0); `add qword ptr [r14+8],0xC8`; `jmp short 0x6726D91` (-> loc_6726d91). Isolated block at 0x6726d85 (between the jmp and loc_6726d91; no in-range jump targets it seen so far [?]): `mov rcx,r14`; `mov r8,r15`; `call 0x5ABA6D0` (sub_5aba6d0); `nop`. loc_6726d91: TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `lea rcx,[rbp+0x560]`; `call 0x67E40A0` (sub_67e40a0); `jmp 0x6727750` (-> loc_6727750; tail jump). Block at 0x6726dbe (no in-range jump target seen [?]): `lea rcx,[rbp+0x510]`; `mov rdx,r15`; `call 0x67A75D0` (sub_67a75d0); `nop`; falls into `lea rcx,[rbp+0x370]`; `lea rdx,[rbp+0x1F0]`; `lea r8,[rbp+0x198]`; `mov r9,r15`; `call 0x678F640` (sub_678f640); `nop`; `mov eax,[r13+0x60]`; `lea rcx,[rbp+0x4A8]`; `mov [rcx+0x10],eax`; `movups xmm0,[r13+0x50]`; `movups [rcx],xmm0` (continues next phase: 0x6726e2a).

Callees: 0xEEC6EC0 (sub_eec6ec0, direct), 0x5ABA6D0 (sub_5aba6d0, direct), [0xF99FFA0] = sub_eea6040 (indirect), 0x67E40A0 (sub_67e40a0, direct), jmp 0x6727750 (loc_6727750), 0x67A75D0 (sub_67a75d0, direct), 0x678F640 (sub_678f640, direct).
Fields read: [r14+8] [R/W], [rbp+0x818] [R/W], [rbp+0x560] [R], [rbp+0x510] [R], [rbp+0x370] [R], [rbp+0x1F0] [R], [rbp+0x198] [R], [r13+0x60] [R], [r13+0x50] [R].
Fields written: [r14+8], [rdx], [rbp+0x4A8] via [rcx+0x10], [rcx].

## Phase 20 (0x6726e2a..0x6726f07)
```
  6726e2a  movups xmm2,[r13+0x97]                        
  6726e32  movups [rbx+0x9F],xmm2                        
  6726e39  movups [rbx+0x90],xmm1                        
  6726e40  movups [rbx+0x80],xmm0                        
  6726e47  movzx eax,word ptr [rbp+0x298]                
  6726e4e  mov [rbp+0x500],ax                            
  6726e55  mov rax,[rbp+0x748]                           
  6726e5c  mov r8,[rax+0x480]                            
  6726e63  mov rax,[rax+0x488]                           
  6726e6a  mov rdx,rax                                   
  6726e6d  sub rdx,r8                                    
  6726e70  cmp rdx,0xFFFFFFFFFFFFFFD0                    
  6726e74  je 0x672A30F                                  ; -> sub_672a30f
  6726e7a  test r8,r8                                    
  6726e7d  setne cl                                      
  6726e80  test rax,rax                                  
  6726e83  sete r9b                                      
  6726e87  or r9b,cl                                     
  6726e8a  je 0x672A30F                                  ; -> sub_672a30f
  6726e90  cmp rax,r8                                    
  6726e93  je 0x67282C9                                  ; -> loc_67282c9
  6726e99  mov rax,[rbp+0x758]                           
  6726ea0  cmp qword ptr [rax],0                         
  6726ea4  je 0x67282C9                                  ; -> loc_67282c9
  6726eaa  sar rdx,4                                     
  6726eae  mov rax,0xAAAAAAAAAAAAAAAB                    
  6726eb8  imul rdx,rax                                  
  6726ebc  mov dword ptr [rsp+0x20],0x41800000           
  6726ec4  lea rcx,[rbp+0x7E0]                           
  6726ecb  lea r9,[rbp+0x530]                            
  6726ed2  call 0x6769EE0                                ; -> sub_6769ee0
  6726ed7  nop                                           
  6726ed8  mov rax,[rbp+0x7E0]                           
  6726edf  mov rcx,[rbp+0x7E8]                           
  6726ee6  mov r14,rax                                   
  6726ee9  mov [rbp+0x818],rax                           
  6726ef0  mov [rbp+0x558],rcx                           
  6726ef7  cmp rax,rcx                                   
  6726efa  je 0x6728236                                  ; -> loc_6728236
  6726f00  mov rax,[rbp+0x758]                           
```
// Phase 20 (final phase; the 800th instruction is `mov rax,[rbp+0x758]` at 0x6726f00): continuation of phase 19's store sequence: `movups xmm2,[r13+0x97]`; `movups [rbx+0x9F],xmm2`; `movups [rbx+0x90],xmm1`; `movups [rbx+0x80],xmm0`; `movzx eax,word ptr [rbp+0x298]`; `mov [rbp+0x500],ax`. Tag check: `rax=[rbp+0x748]`; `r8=[rax+0x480]`; `rax=[rax+0x488]`; `rdx=rax`; `rdx-=r8`; `cmp rdx,0xFFFFFFFFFFFFFFD0`; if equal `je 0x672A30F` (-> sub_672a30f). `test r8,r8`; `setne cl`; `test rax,rax`; `sete r9b`; `or r9b,cl`; if zero `je 0x672A30F` (-> sub_672a30f). `cmp rax,r8`; if equal `je 0x67282C9` (-> loc_67282c9). `rax=[rbp+0x758]`; `cmp qword ptr [rax],0`; if zero `je 0x67282C9` (-> loc_67282c9). Division-by-17: `sar rdx,4`; `rax=0xAAAAAAAAAAAAAAAB`; `imul rdx,rax`; `mov dword ptr [rsp+0x20],0x41800000` (16.0f). `rcx=&[rbp+0x7E0]`; `r9=&[rbp+0x530]`; `call 0x6769EE0` (sub_6769ee0); `nop`. `rax=[rbp+0x7E0]`; `rcx=[rbp+0x7E8]`; `r14=rax`; `[rbp+0x818]=rax`; `[rbp+0x558]=rcx`; `cmp rax,rcx`; if equal `je 0x6728236` (-> loc_6728236). `rax=[rbp+0x758]` (continues beyond target: next instruction at 0x6726f07).

Callees: 0x6769EE0 (sub_6769ee0, direct).
Fields read: [r13+0x97] [R], [rbp+0x298] [R], [rbp+0x500] [W], [rbp+0x748] [R], [rax+0x480] [R], [rax+0x488] [R], [rbp+0x758] [R], [rax] [R], [rsp+0x20] [W], [rbp+0x7E0] [R/W], [rbp+0x7E8] [R], [rbp+0x818] [W], [rbp+0x558] [W].
Fields written: [rbx+0x9F], [rbx+0x90], [rbx+0x80], [rbp+0x500], [rsp+0x20], [rbp+0x818], [rbp+0x558], [r14].

---
## Redo of garbled RVAs from docs/progress/oc_U-E4-H4.md [V]
Re-disassembled with rdis (exact lines below). H4's notes at these RVAs were garbled; corrected here.

### Redo of 0x67258ec (clean — disassembles exactly as shown)
`rdis dis 0x67258ec 40`. Exact rdis lines for instructions starting at 0x67258ec:
```
  67258ec  mov eax,[rbp+0x580]                           
  67258f2  mov [rdi],rax                                 
  67258f5  lea rcx,[rdi+8]                               
  67258f9  lea rdx,[rbp+0x588]                           
  6725900  call 0xE869FF0                                ; -> sub_e869ff0
  6725905  nop                                           
  6725906  mov rax,[rbp+0x600]                           
  672590d  mov [rdi+0x80],rax                            
  6725914  mov qword ptr [rbp+0x600],0                   
  672591f  add qword ptr [r14+0x770],0x88                
  672592a  jmp 0x6725DEE                                 ; -> loc_6725dee
  672592f  lea rcx,[r15+0x858]                           
  6725936  call 0x6760E60                                ; -> sub_6760e60
  672593b  nop                                           
  672593c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725943  mov rax,[rcx]                                 
  6725946  mov rax,[rax+0x10]                            
  672594a  movzx edx,byte ptr [rbp+0x818]                
  6725951  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725957  nop                                           
  6725958  mov qword ptr [rbp+0x110],0x4009              
  6725963  mov eax,[r15+0x858]                           
  672596a  not eax                                       
  672596c  add eax,[r15+0x860]                           
  6725973  mov [rbp+0x126],ax                            
  672597a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725981  mov rax,[rcx]                                 
  6725984  mov rax,[rax+0x10]                            
  6725988  mov dl,0x4A                                   
  672598a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725990  mov [rbp+0x818],al                            
  6725996  lea rcx,[r15+0x648]                           
  672599d  lea rdx,[rbp+0x688]                           
  67259a4  call 0x675FB30                                ; -> sub_675fb30
  67259a9  nop                                           
  67259aa  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67259b1  mov rax,[rcx]                                 
  67259b4  mov rax,[rax+0x10]                            
  67259b8  movzx edx,byte ptr [rbp+0x818]                
  67259bf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```
Interpretation: release-block pattern (cf. H5 phases 7-10): `mov eax,[rbp+0x580]`; `mov [rdi],rax`; `lea rcx,[rdi+8]`; `lea rdx,[rbp+0x588]`; `call 0xE869FF0` (sub_e869ff0); `nop`; `mov rax,[rbp+0x600]`; `mov [rdi+0x80],rax`; `mov qword ptr [rbp+0x600],0`; `add qword ptr [r14+0x770],0x88`; `jmp 0x6725DEE` (-> loc_6725dee). Je-target block at 0x672592f: `lea rcx,[r15+0x858]`; `call 0x6760E60` (sub_6760e60); `nop`; TLS singleton seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov qword ptr [rbp+0x110],0x4009`; `eax=[r15+0x858]`; `not eax`; `add eax,[r15+0x860]`; `mov [rbp+0x126],ax`; TLS call: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `mov [rbp+0x818],al`; `lea rcx,[r15+0x648]`; `lea rdx,[rbp+0x688]`; `call 0x675FB30` (sub_675fb30); `nop`; TLS seq continues at 0x67259c5 (`mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`).
Callees: 0xE869FF0 (sub_e869ff0, direct), [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x6760E60 (sub_6760e60, direct), 0x675FB30 (sub_675fb30, direct).
Fields read: [rbp+0x580] [R], [rdi] [W], [rdi+8] [R], [rbp+0x588] [R], [rbp+0x600] [R/W], [r14+0x770] [R/W], [rbp+0x110] [W], [r15+0x858] [R], [r15+0x860] [R], [rbp+0x126] [W], [rbp+0x818] [R/W], [r15+0x648] [R], [rbp+0x688] [R], [rdi+0x80] [W].
Fields written: [rdi], [rdi+0x80], [rbp+0x600], [r14+0x770], [rbp+0x110], [rbp+0x126], [rbp+0x818].

### Redo of 0x67259cb (garbage at the RVA; real code at 0x67259cd)
`rdis dis 0x67259cb 40`. First line `67259cb add [rax],al` is garbage (2 padding bytes inside a previous instruction). Exact rdis lines for the real instructions starting at 0x67259cd:
```
  67259cd  sub eax,[r15+0x648]                           
  67259d4  shr eax,3                                     
  67259d7  imul eax,0xFFFF8E39                           
  67259dd  dec eax                                       
  67259df  mov [rbp+0x152],ax                            
  67259e6  lea rcx,[r15+0x780]                           
  67259ed  lea rdx,[rbp+0x630]                           
  67259f4  call 0x675F3B0                                ; -> sub_675f3b0
  67259f9  nop                                           
  67259fa  mov eax,[r15+0x788]                           
  6725a01  sub eax,[r15+0x780]                           
  6725a08  shr eax,3                                     
  6725a0b  imul eax,0xFFFF8BA3                           
  6725a11  dec eax                                       
  6725a13  mov [rbp+0x138],ax                            
  6725a1a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725a21  mov rax,[rcx]                                 
  6725a24  mov rax,[rax+0x10]                            
  6725a28  mov dl,0x4A                                   
  6725a2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725a30  mov [rbp+0x818],al                            
  6725a36  mov rdi,[r15+0x770]                           
  6725a3d  cmp rdi,[r15+0x778]                           
  6725a44  je 0x6725E8E                                  ; -> loc_6725e8e
  6725a4a  mov rax,[rbp+0x5A8]                           
  6725a51  mov [rdi],rax                                 
  6725a54  lea rcx,[rdi+8]                               
  6725a58  lea rdx,[rbp+0x5B0]                           
  6725a5f  call 0xE869FF0                                ; -> sub_e869ff0
  6725a64  nop                                           
  6725a65  mov rax,[rbp+0x628]                           
  6725a6c  mov [rdi+0x80],rax                            
  6725a73  mov qword ptr [rbp+0x628],0                   
  6725a7e  add qword ptr [r15+0x770],0x88                
  6725a89  jmp 0x6725EA5                                 ; -> loc_6725ea5
  6725a8e  lea rcx,[r15+0x858]                           
  6725a95  call 0x6760E60                                ; -> sub_6760e60
  6725a9a  nop                                           
  6725a9b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
```
Interpretation: count calc (eax carries prior value [?]): `sub eax,[r15+0x648]`; `shr eax,3`; `imul eax,0xFFFF8E39`; `dec eax`; `mov [rbp+0x152],ax`; `lea rcx,[r15+0x780]`; `lea rdx,[rbp+0x630]`; `call 0x675F3B0` (sub_675f3b0); `nop`. Count calc: `eax=[r15+0x788]`; `sub eax,[r15+0x780]`; `shr eax,3`; `imul eax,0xFFFF8BA3`; `dec eax`; `mov [rbp+0x138],ax`. TLS call dl=0x4A; `mov [rbp+0x818],al`. `rdi=[r15+0x770]`; `cmp rdi,[r15+0x778]`; if equal `je 0x6725E8E` (-> loc_6725e8e); else release block: `mov rax,[rbp+0x5A8]`; `mov [rdi],rax`; `lea rcx,[rdi+8]`; `lea rdx,[rbp+0x5B0]`; `call 0xE869FF0` (sub_e869ff0); `nop`; `mov rax,[rbp+0x628]`; `mov [rdi+0x80],rax`; `mov qword ptr [rbp+0x628],0`; `add qword ptr [r15+0x770],0x88`; `jmp 0x6725EA5` (-> loc_6725ea5). Je-target block at 0x6725a8e: `lea rcx,[r15+0x858]`; `call 0x6760E60` (sub_6760e60); `nop`; TLS seq continues (`mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]` ...).
Callees: 0x675F3B0 (sub_675f3b0, direct), [0xF99FFA0] = sub_eea6040 (indirect), 0xE869FF0 (sub_e869ff0, direct), 0x6760E60 (sub_6760e60, direct).
Fields read: [r15+0x648] [R], [rbp+0x152] [W], [r15+0x780] [R], [rbp+0x630] [R], [r15+0x788] [R], [rbp+0x138] [W], [rbp+0x818] [R/W], [r15+0x770] [R], [r15+0x778] [R], [rbp+0x5A8] [R], [rdi] [W], [rbp+0x628] [R], [rdi+0x80] [W], [r15+0x770] [R/W], [r15+0x858] [R].
Fields written: [rbp+0x152], [rbp+0x818], [rdi], [rdi+0x80], [rbp+0x628], [r15+0x770].

### Redo of 0x6725c58..0x6725c6b (padding; no real instruction starts in this range)
`rdis dis 0x6725c58 24`. The bytes at 0x6725c58..0x6725c6f decode as nonsensical instructions (huge absolute addresses) — padding, not real code:
```
  6725c58  adc [rdx+0x3F15FF4A],dh                       ; W a1+0x3F15FF4A
  6725c5e  mov [0x8188588900927],eax                     
  6725c67  add [rcx-0x75],cl                             ; W a0-0x75
  6725c6a  push rsi                                      
  6725c6b  push 0x70563B49                               
```
No real instruction starts in 0x6725c58..0x6725c6b (the range lies inside padding). Real code resumes at 0x6725c70:
```
  6725c70  je 0x6725FEB                                  ; -> loc_6725feb
  6725c76  inc rdx                                       
  6725c79  mov [r14+0x68],rdx                            
  6725c7d  jmp 0x6725FF8                                 ; -> loc_6725ff8
  6725c82  lea rcx,[r14+0x768]                           
  6725c89  mov rdx,rdi                                   
  6725c8c  lea r8,[rbp+0x570]                            
  6725c93  call 0x6760710                                ; -> sub_6760710
  6725c98  nop                                           
  6725c99  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6725ca0  mov rax,[rcx]                                 
  6725ca3  mov rax,[rax+0x10]                            
  6725ca7  movzx edx,byte ptr [rbp+0x818]                
  6725cae  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6725cb4  nop                                           
  6725cb5  mov qword ptr [rbp+0x110],0x2007009           
  6725cc0  mov eax,[r14+0x770]                           
  6725cc7  sub eax,[r14+0x768]                           
  6725cce  shr eax,3                                     
```
Interpretation: 0x6725c70 `je 0x6725FEB` (-> loc_6725feb); fall-through `inc rdx`; `mov [r14+0x68],rdx`; `jmp 0x6725FF8` (-> loc_6725ff8). Je-target block at 0x6725c82: `lea rcx,[r14+0x768]`; `mov rdx,rdi`; `lea r8,[rbp+0x570]`; `call 0x6760710` (sub_6760710); `nop`; TLS singleton seq: `mov rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov qword ptr [rbp+0x110],0x2007009`; `eax=[r14+0x770]`; `sub eax,[r14+0x768]`; `shr eax,3` (continues beyond this dump at 0x6725cce).
Callees: 0x6760710 (sub_6760710, direct), [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [r14+0x68] [R/W], [rbp+0x768] [R], [rbp+0x570] [R], [rbp+0x818] [R/W], [rbp+0x110] [W], [r14+0x770] [R], [r14+0x768] [R].
Fields written: [r14+0x68], [rbp+0x110].

## Phase 5 (0x6726301..0x67263c1)
```
  6726301  imul eax,0xFFFFAAAB                           
  6726307  dec eax                                       
  6726309  mov [rbp+0x14E],ax                            
  6726310  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6726317  mov rax,[rcx]                                 
  672631a  mov rax,[rax+0x10]                            
  672631e  mov dl,0x4A                                   
  6726320  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6726326  nop                                           
  6726327  mov [rbp+0x818],al                            
  672632d  mov rdx,[r15+0x698]                           
  6726334  cmp rdx,[r15+0x6A0]                           
  672633b  je 0x6726623                                  ; -> loc_6726623
  6726341  movzx eax,word ptr [rbp+0x5A0]                
  6726348  mov [rdx],ax                                  
  672634b  add qword ptr [r15+0x698],2                   
  6726353  jmp 0x6726637                                 ; -> loc_6726637
  6726358  mov rcx,r14                                   
  672635b  mov r8,r15                                    
  672635e  call 0x5ABA6D0                                ; -> sub_5aba6d0
  6726363  nop                                           
  6726364  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672636b  mov rax,[rcx]                                 
  672636e  mov rax,[rax+0x10]                            
  6726372  movzx edx,byte ptr [rbp+0x818]                
  6726379  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  672637f  nop                                           
  6726380  lea rcx,[rbp+0x560]                           
  6726387  call 0x67E1840                                ; -> sub_67e1840
  672638c  lea rcx,[rbp+0x370]                           
  6726393  jmp 0x672A1A0                                 ; -> sub_672a1a0
  6726398  lea rcx,[r14+0x360]                           
  672639f  call 0x6760E60                                ; -> sub_6760e60
  67263a4  nop                                           
  67263a5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67263ac  mov rax,[rcx]                                 
  67263af  mov rax,[rax+0x10]                            
  67263b3  movzx edx,byte ptr [rbp+0x818]                
  67263ba  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67263c0  nop                                           
```
// Phase 5: tail of phase 4's count calc: `imul eax,0xFFFFAAAB`; `dec eax`; `mov [rbp+0x14E],ax`. TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `mov dl,0x4A`; `call qword ptr [0xF99FFA0]` (sub_eea6040); `nop`; `mov [rbp+0x818],al`. Cursor loop [r15+0x698] vs [r15+0x6A0]: if equal `je 0x6726623` (-> loc_6726623) else `movzx eax,word ptr [rbp+0x5A0]`; `mov [rdx],ax`; `add qword ptr [r15+0x698],2`; `jmp 0x6726637` (-> loc_6726637). `mov rcx,r14`; `mov r8,r15`; `call 0x5ABA6D0` (sub_5aba6d0); `nop`. TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop`. `lea rcx,[rbp+0x560]`; `call 0x67E1840` (sub_67e1840). `lea rcx,[rbp+0x370]`; `jmp 0x672A1A0` (-> sub_672a1a0; tail jump). Je-target block at 0x6726398 (from phase 2's `je 0x6726398`): `lea rcx,[r14+0x360]`; `call 0x6760E60` (sub_6760e60); `nop`; TLS seq: `rcx=[0x1233E1B0]`; `rax=[rcx]`; `rax=[rax+0x10]`; `movzx edx,byte [rbp+0x818]`; `call qword ptr [0xF99FFA0]`; `nop` (continues next phase: 0x67263c1 `mov rax,0x100000002007049`; no `mov [rbp+0x818],al` store for that final TLS call appears on this path [?]).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x5ABA6D0 (sub_5aba6d0, direct), 0x67E1840 (sub_67e1840, direct), jmp 0x672A1A0 (sub_672a1a0, tail), 0x6760E60 (sub_6760e60, direct).
Fields read: [rbp+0x14E] [W], [0x1233E1B0] [R], [rcx] [R], [rax+0x10] [R], [rbp+0x818] [R/W], [r15+0x698] [R/W], [r15+0x6A0] [R], [rbp+0x5A0] [R], [rdx] [W], [rbp+0x560] [R], [rbp+0x370] [R], [r14+0x360] [R].
Fields written: [rbp+0x14E], [rbp+0x818], [r15+0x698], [rdx].

## Phase 1 (0x672604d..0x67260a1)
```
  672604d  mov rdx,[r14+8]
  6726051  cmp rdx,[r14+0x10]
  6726055  je 0x6726358                                  ; -> loc_6726358
  672605b  mov r8d,0xC8
  6726061  mov rcx,rdx
  6726064  mov rdx,r15
  6726067  call 0xEEC6EC0                                ; -> sub_eec6ec0
  672606c  add qword ptr [r14+8],0xC8
  6726074  jmp 0x6726364                                 ; -> loc_6726364
  6726079  lea rcx,[r14+0x810]
  6726080  call 0x6760E60                                ; -> sub_6760e60
  6726085  nop
  6726086  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  672608d  mov rax,[rcx]
  6726090  mov rax,[rax+0x10]
  6726094  movzx edx,byte ptr [rbp+0x818]
  672609b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67260a1  nop
```
// Phase 1: tail of a loop. Compares rdx (r14+8, a read cursor) against r14+0x10 (end pointer); if equal jumps to loc_6726358. Otherwise copies cursor into rcx, sets r8d=0xC8 (200), rdx=r15, and calls sub_eec6ec0 (likely a memcpy-like sink) then advances cursor by 0xC8. Falls through to loc_6726364. The block at 0x6726079 loads r14+0x810 into rcx and calls sub_6760e60, then reads a global singleton [0x1233E1B0]->[+0x10], reads byte [rbp+0x818], and calls sub_eea6040 (indirect via [0xF99FFA0]).