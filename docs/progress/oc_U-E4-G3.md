# U-E4-G3: Chunk builder at 0x670b6e0 — continuation of U-E4-G2

Unit: U-E4-G3
Function: sub_670b6e0 (chunk builder) — continuation
RVAs: 0x670d6cc .. (800 instructions from 0x670d6cc)
Source: `rdis dis 0x670d6cc <n>` on Minecraft.Windows.exe 1.26.62.01
Sibling: docs/progress/oc_U-E4-F2.md (sub_67762e0)
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Resume at 0x670e955 (after `0x670e94f call [0xF99FFA0]`, phase 20's last instr). Phases 1-20 (800 instructions, 0x670d6cc..0x670e94f) written below. Unit complete — all 800 instructions transcribed.

---

## Phase 9 — not-eax count #1 + TLS #2 + cursor/end [r15+0x620]/[r15+0x628] + grow path loc_670e089 (0x670e016..0x670e0d7)

Continues Phase 8's not-eax count setup: TLS #2 (rcx=[0x1233E1B0], dl=0x4A, call [0xF99FFA0], [rbp+0x848]=al). eax=[r15+0x858]; not eax; add eax,[r15+0x860]; [rbp+0x3F6]=ax. TLS #2 again → [rbp+0x848]. Cursor/end [r15+0x620]/[r15+0x628]; if full → loc_670e4d3 (grow: call 0x6760E60(rcx=[r15+0x618])); otherwise inc [r15+0x620], jmp loc_670e4e0. Grow loc_670e089: call 0x6760E60(rcx=[r15+0x858]). Then TLS/count #2: not eax + [r15+0x860] → [rbp+0x3F6].

```
0x670e016  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e01d  mov rax,[rcx]                                 
0x670e020  mov rax,[rax+0x10]                            
0x670e024  movzx edx,byte ptr [rbp+0x848]                
0x670e02b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e031  nop                                           
0x670e032  mov eax,[r15+0x858]                           
0x670e039  not eax                                       
0x670e03b  add eax,[r15+0x860]                           
0x670e042  mov [rbp+0x3F6],ax                            
0x670e049  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e050  mov rax,[rcx]                                 
0x670e053  mov rax,[rax+0x10]                            
0x670e057  mov dl,0x4A                                   
0x670e059  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e05f  nop                                           
0x670e060  mov [rbp+0x848],al                            
0x670e066  mov rdx,[r15+0x620]                           
0x670e06d  cmp rdx,[r15+0x628]                           
0x670e074  je 0x670E4D3                                  ; -> loc_670e4d3
0x670e07a  inc rdx                                       
0x670e07d  mov [r15+0x620],rdx                           
0x670e084  jmp 0x670E4E0                                 ; -> loc_670e4e0
0x670e089  lea rcx,[r15+0x858]                           
0x670e090  call 0x6760E60                                ; -> sub_6760e60
0x670e095  nop                                           
0x670e096  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e09d  mov rax,[rcx]                                 
0x670e0a0  mov rax,[rax+0x10]                            
0x670e0a4  movzx edx,byte ptr [rbp+0x848]                
0x670e0ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e0b1  nop                                           
0x670e0b2  mov eax,[r15+0x858]                           
0x670e0b9  not eax                                       
0x670e0bb  add eax,[r15+0x860]                           
0x670e0c2  mov [rbp+0x3F6],ax                            
0x670e0c9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e0d0  mov rax,[rcx]                                 
0x670e0d3  mov rax,[rax+0x10]                            
0x670e0d7  mov dl,0x4A                                   
```

Interpretation: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x848]=al. eax=[r15+0x858]; not eax; add eax,[r15+0x860]; [rbp+0x3F6]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x620]; cmp [r15+0x628]; if equal → loc_670e4d3 (grow). Otherwise inc rdx; [r15+0x620]=rdx; jmp loc_670e4e0. Grow loc_670e089: lea rcx,[r15+0x858]; call 0x6760E60; nop. Then loc_670e096 (fall-through from grow): TLS/count #2 repeats not-eax pattern with [r15+0x858]/[r15+0x860] → [rbp+0x3F6] (next: TLS dl=0x4A at 0x670e0d7).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x6760E60 (sub_6760e60).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x858], [r15+0x860], [rbp+0x3F6], [r15+0x620], [r15+0x628], [r15+0x858]. Fields written: [rbp+0x848], [rbp+0x3F6], [r15+0x620].
Matches F2 Phase? Not-eax count idiom + cursor/end [r15+0x620]/[r15+0x628] + grow path with 0x6760E60. No exact F2 counterpart.

---

## Phase 10 — TLS #2 + cursor/end [r15+0x620]/[r15+0x628] + grow loc_670e109 + not-eax count #2 (r12) (0x670e0d9..0x670e1a4)

TLS dl=0x4A → [rbp+0x848]. Cursor/end [r15+0x620]/[r15+0x628]; if full → loc_670e632 (grow: call 0x6760E60(rcx=[r15+0x618])); otherwise inc [r15+0x620], jmp loc_670e63f. Grow loc_670e109: call 0x6760E60(rcx=[r12+0x858]). Then not-eax count #2 (r12): eax=[r12+0x858]; not eax; add eax,[r12+0x860]; [rbp+0x3F6]=ax. TLS #2 → [rbp+0x848]. Cursor/end [r12+0x620]/[r12+0x628]; if full → loc_670e791; otherwise inc [r12+0x620], jmp loc_670e79f. Grow loc_670e18f: call 0x6760E60(rcx=[r12+0x858]).

```
0x670e0d9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e0df  nop                                           
0x670e0e0  mov [rbp+0x848],al                            
0x670e0e6  mov rdx,[r15+0x620]                           
0x670e0ed  cmp rdx,[r15+0x628]                           
0x670e0f4  je 0x670E632                                  ; -> loc_670e632
0x670e0fa  inc rdx                                       
0x670e0fd  mov [r15+0x620],rdx                           
0x670e104  jmp 0x670E63F                                 ; -> loc_670e63f
0x670e109  lea rcx,[r12+0x858]                           
0x670e111  call 0x6760E60                                ; -> sub_6760e60
0x670e116  nop                                           
0x670e117  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e11e  mov rax,[rcx]                                 
0x670e121  mov rax,[rax+0x10]                            
0x670e125  movzx edx,byte ptr [rbp+0x848]                
0x670e12c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e132  nop                                           
0x670e133  mov eax,[r12+0x858]                           
0x670e13b  not eax                                       
0x670e13d  add eax,[r12+0x860]                           
0x670e145  mov [rbp+0x3F6],ax                            
0x670e14c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e153  mov rax,[rcx]                                 
0x670e156  mov rax,[rax+0x10]                            
0x670e15a  mov dl,0x4A                                   
0x670e15c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e162  nop                                           
0x670e163  mov [rbp+0x848],al                            
0x670e169  mov rdx,[r12+0x620]                           
0x670e171  cmp rdx,[r12+0x628]                           
0x670e179  je 0x670E791                                  ; -> loc_670e791
0x670e17f  inc rdx                                       
0x670e182  mov [r12+0x620],rdx                           
0x670e18a  jmp 0x670E79F                                 ; -> loc_670e79f
0x670e18f  lea rcx,[r12+0x858]                           
0x670e197  call 0x6760E60                                ; -> sub_6760e60
0x670e19c  nop                                           
0x670e19d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e1a4  mov rax,[rcx]                                 
```

Interpretation: dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al (completing Phase 9's TLS #2). rdx=[r15+0x620]; cmp [r15+0x628]; if equal → loc_670e632 (grow). Otherwise inc rdx; [r15+0x620]=rdx; jmp loc_670e63f. Grow loc_670e109: lea rcx,[r12+0x858]; call 0x6760E60; nop. Then loc_670e117: TLS/count #2 (r12): rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r12+0x858]; not eax; add eax,[r12+0x860]; [rbp+0x3F6]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x620]; cmp [r12+0x628]; if equal → loc_670e791. Otherwise inc rdx; [r12+0x620]=rdx; jmp loc_670e79f. Grow loc_670e18f: lea rcx,[r12+0x858]; call 0x6760E60; nop (next: TLS at 0x670e19d).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x6760E60 (sub_6760e60).
Fields read: [rbp+0x848], [0x1233E1B0], [rcx], [rax+0x10], [r15+0x620], [r15+0x628], [r12+0x858], [r12+0x860], [rbp+0x3F6], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x620], [r12+0x628], [r12+0x858]. Fields written: [rbp+0x848], [r15+0x620], [rbp+0x3F6], [r12+0x620].
Matches F2 Phase? Same not-eax count + grow path idiom as Phase 9. No exact F2 counterpart.

---

## Phase 11 — not-eax count #2 tail (r12) + TLS #2 + cursor/end [r12+0x620]/[r12+0x628] + grow loc_670e215 (0x670e1a7..0x670e221)

Continues Phase 10: rax=[rax+0x10] (completing TLS #2 setup). edx=byte [rbp+0x848]; call [0xF99FFA0]. eax=[r12+0x858]; not eax; add eax,[r12+0x860]; [rbp+0x3F6]=ax. TLS #2 → [rbp+0x848]. Cursor/end [r12+0x620]/[r12+0x628]; if full → loc_670e8fc (grow: call 0x6760E60(rcx=[r12+0x858])); otherwise inc [r12+0x620], jmp loc_670e90a. Grow loc_670e215: call 0x6760E60(rcx=[r15+0x618]).

```
0x670e1a7  mov rax,[rax+0x10]                            
0x670e1ab  movzx edx,byte ptr [rbp+0x848]                
0x670e1b2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e1b8  nop                                           
0x670e1b9  mov eax,[r12+0x858]                           
0x670e1c1  not eax                                       
0x670e1c3  add eax,[r12+0x860]                           
0x670e1cb  mov [rbp+0x3F6],ax                            
0x670e1d2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670e1d9  mov rax,[rcx]                                 
0x670e1dc  mov rax,[rax+0x10]                            
0x670e1e0  mov dl,0x4A                                   
0x670e1e2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e1e8  nop                                           
0x670e1e9  mov [rbp+0x848],al                            
0x670e1ef  mov rdx,[r12+0x620]                           
0x670e1f7  cmp rdx,[r12+0x628]                           
0x670e1ff  je 0x670E8FC                                  ; -> loc_670e8fc
0x670e205  inc rdx                                       
0x670e208  mov [r12+0x620],rdx                           
0x670e210  jmp 0x670E90A                                 ; -> loc_670e90a
0x670e215  lea rcx,[r15+0x618]                           
0x670e21c  call 0x6760E60                                ; -> sub_6760e60
0x670e221  nop                                           
```

Interpretation: rax=[rax+0x10] (TLS #2 setup continuation). edx=byte [rbp+0x848]; call [0xF99FFA0] (al not stored yet — next phase stores it). eax=[r12+0x858]; not eax; add eax,[r12+0x860]; [rbp+0x3F6]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x620]; cmp [r12+0x628]; if equal → loc_670e8fc (grow). Otherwise inc rdx; [r12+0x620]=rdx; jmp loc_670e90a. Grow loc_670e215: lea rcx,[r15+0x618]; call 0x6760E60; nop (end of phase).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x6760E60 (sub_6760e60).
Fields read: [rax+0x10], [rbp+0x848], [r12+0x858], [r12+0x860], [rbp+0x3F6], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x620], [r12+0x628], [r15+0x618]. Fields written: [rbp+0x3F6], [rbp+0x848], [r12+0x620].
Matches F2 Phase? Same not-eax count + grow path idiom. No exact F2 counterpart.

---

## Phase 12 — [rbp+0x3E0]=0x8004009 + call 0x675FB30 + transition to new content (0x670e222..0x670e2e0)

End of batch-2 tail (overlap): TLS #2 store [rbp+0x848]=al; [rbp+0x3E0]=0x8004009; eax=[r15+0x618]; not eax; add eax,[r15+0x620]; [rbp+0x426]=ax. TLS #2 → [rbp+0x848]. lea rcx,[r15+0x648]; lea rdx,[rbp+0x668]; call 0x675FB30. New content begins: TLS call [0xF99FFA0] → [rbp+0x848]. eax=[r15+0x650]; sub eax,[r15+0x648]; shr eax,3; imul eax,0xFFFF8E39; dec eax; [rbp+0x422]=ax. lea rcx,[r15+0x780]; lea rdx,[rbp+0x610]; call 0x675F3B0. eax=[r15+0x788] (next: sub eax,[r15+0x780]).

```
0x670e222  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e229  mov rax,[rcx]                                 
0x670e22c  mov rax,[rax+0x10]                            
0x670e230  movzx edx,byte ptr [rbp+0x848]                
0x670e237  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e23d  nop                                           
0x670e23e  mov qword ptr [rbp+0x3E0],0x8004009           
0x670e249  mov eax,[r15+0x618]                           
0x670e250  not eax                                       
0x670e252  add eax,[r15+0x620]                           
0x670e259  mov [rbp+0x426],ax                            
0x670e260  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e267  mov rax,[rcx]                                 
0x670e26a  mov rax,[rax+0x10]                            
0x670e26e  mov dl,0x4A                                   
0x670e270  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e276  mov [rbp+0x848],al                            
0x670e27c  lea rcx,[r15+0x648]                           
0x670e283  lea rdx,[rbp+0x668]                           
0x670e28a  call 0x675FB30                                ; -> sub_675fb30
0x670e28f  nop                                           
0x670e290  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e297  mov rax,[rcx]                                 
0x670e29a  mov rax,[rax+0x10]                            
0x670e29e  movzx edx,byte ptr [rbp+0x848]                
0x670e2a5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e2ab  nop                                           
0x670e2ac  mov eax,[r15+0x650]                           
0x670e2b3  sub eax,[r15+0x648]                           
0x670e2ba  shr eax,3                                     
0x670e2bd  imul eax,0xFFFF8E39                           
0x670e2c3  dec eax                                       
0x670e2c5  mov [rbp+0x422],ax                            
0x670e2cc  lea rcx,[r15+0x780]                           
0x670e2d3  lea rdx,[rbp+0x610]                           
0x670e2da  call 0x675F3B0                                ; -> sub_675f3b0
0x670e2df  nop                                           
0x670e2e0  mov eax,[r15+0x788]                           
```

Interpretation: TLS #2 completion: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E0]=0x8004009; eax=[r15+0x618]; not eax; add eax,[r15+0x620]; [rbp+0x426]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. lea rcx,[r15+0x648]; lea rdx,[rbp+0x668]; call 0x675FB30. New content: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x848]=al (next, beyond phase). eax=[r15+0x650]-[r15+0x648]; shr eax,3; imul eax,0xFFFF8E39; dec eax; [rbp+0x422]=ax. lea rcx,[r15+0x780]; lea rdx,[rbp+0x610]; call 0x675F3B0. eax=[r15+0x788] (next: sub eax,[r15+0x780]).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675FB30 (sub_675fb30), 0x675F3B0 (sub_675f3b0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x618], [r15+0x620], [rbp+0x426], [r15+0x648], [rbp+0x668], [r15+0x848], [r15+0x650], [r15+0x648], [rbp+0x422], [r15+0x780], [rbp+0x610], [r15+0x788]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x426], [rbp+0x422], [rbp+0x848].
Matches F2 Phase? New idiom: `[rbp+0x3E0]=0x8004009` + `call 0x675FB30` + `call 0x675F3B0` + count with magic 0xFFFF8E39 → [rbp+0x422]. No exact F2 counterpart.

---

## Phase 13 — count tail [rbp+0x408] + TLS + item-slot write [rsi] + call 0xE869FF0 + bump [r15+0x770] (0x670e2e7..0x670e36f)

Continues Phase 12's `eax=[r15+0x788]`: sub eax,[r15+0x780]; shr eax,3; imul eax,0xFFFF8BA3; dec eax; [rbp+0x408]=ax. TLS #2 → [rbp+0x848]. rsi=[r15+0x770]; cmp [r15+0x778]; if full → loc_670ea67 (grow). Otherwise [rbp+0x588]→[rsi]; lea rcx,[rsi+8]; lea rdx,[rbp+0x590]; call 0xE869FF0; [rbp+0x608]→[rsi+0x80]; [rbp+0x608]=0; [r15+0x770]+=0x88; jmp loc_670ea7e.

```
0x670e2e7  sub eax,[r15+0x780]                           
0x670e2ee  shr eax,3                                     
0x670e2f1  imul eax,0xFFFF8BA3                           
0x670e2f7  dec eax                                       
0x670e2f9  mov [rbp+0x408],ax                            
0x670e300  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e307  mov rax,[rcx]                                 
0x670e30a  mov rax,[rax+0x10]                            
0x670e30e  mov dl,0x4A                                   
0x670e310  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e316  mov [rbp+0x848],al                            
0x670e31c  mov rsi,[r15+0x770]                           
0x670e323  cmp rsi,[r15+0x778]                           
0x670e32a  je 0x670EA67                                  ; -> loc_670ea67
0x670e330  mov rax,[rbp+0x588]                           
0x670e337  mov [rsi],rax                                 
0x670e33a  lea rcx,[rsi+8]                               
0x670e33e  lea rdx,[rbp+0x590]                           
0x670e345  call 0xE869FF0                                ; -> sub_e869ff0
0x670e34a  nop                                           
0x670e34b  mov rax,[rbp+0x608]                           
0x670e352  mov [rsi+0x80],rax                            
0x670e359  mov qword ptr [rbp+0x608],0                   
0x670e364  add qword ptr [r15+0x770],0x88                
0x670e36f  jmp 0x670EA7E                                 ; -> loc_670ea7e
```

Interpretation: eax=[r15+0x788]-[r15+0x780]; eax>>=3; imul eax,0xFFFF8BA3; eax-=1; [rbp+0x408]=ax. TLS: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rsi=[r15+0x770]; cmp [r15+0x778]; if equal → loc_670ea67 (grow). Otherwise eax=[rbp+0x588]; [rsi]=eax; rcx=[rsi+8]; rdx=&[rbp+0x590]; call 0xE869FF0. rax=[rbp+0x608]; [rsi+0x80]=rax; [rbp+0x608]=0; [r15+0x770]+=0x88; jmp loc_670ea7e.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0xE869FF0 (sub_e869ff0).
Fields read: [r15+0x788], [r15+0x780], [rbp+0x408], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x770], [r15+0x778], [rbp+0x588], [rsi], [rbp+0x608], [r15+0x770]. Fields written: [rbp+0x408], [rbp+0x848], [rsi], [rsi+0x80], [rbp+0x608], [r15+0x770].
Matches F2 Phase? New idiom: item-slot write with call 0xE869FF0 + 0x88-byte bump. No exact F2 counterpart.

---

## Phase 14 — grow path loc_670e374 + not-eax count + call 0x675FB30 + count [rbp+0x422] + call 0x675F3B0 (0x670e374..0x670e43e)

Grow loc_670e374: call 0x6760E60(rcx=[r15+0x618]); nop. Fall-through loc_670e381: TLS #2 → [rbp+0x848]; [rbp+0x3E0]=0x8004009; eax=[r15+0x618]; not eax; add eax,[r15+0x620]; [rbp+0x426]=ax. TLS #2 → [rbp+0x848]. lea rcx,[r15+0x648]; lea rdx,[rbp+0x670]; call 0x675FB30. TLS #2 → [rbp+0x848]. eax=[r15+0x650]; sub eax,[r15+0x648]; shr eax,3; imul eax,0xFFFF8E39; dec eax; [rbp+0x422]=ax. lea rcx,[r15+0x780]; lea rdx,[rbp+0x618]; call 0x675F3B0. eax=[r15+0x788] (next: sub eax,[r15+0x780]).

```
0x670e374  lea rcx,[r15+0x618]                           
0x670e37b  call 0x6760E60                                ; -> sub_6760e60
0x670e380  nop                                           
0x670e381  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e388  mov rax,[rcx]                                 
0x670e38b  mov rax,[rax+0x10]                            
0x670e38f  movzx edx,byte ptr [rbp+0x848]                
0x670e396  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e39c  nop                                           
0x670e39d  mov qword ptr [rbp+0x3E0],0x8004009           
0x670e3a8  mov eax,[r15+0x618]                           
0x670e3af  not eax                                       
0x670e3b1  add eax,[r15+0x620]                           
0x670e3b8  mov [rbp+0x426],ax                            
0x670e3bf  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e3c6  mov rax,[rcx]                                 
0x670e3c9  mov rax,[rax+0x10]                            
0x670e3cd  mov dl,0x4A                                   
0x670e3cf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e3d5  mov [rbp+0x848],al                            
0x670e3db  lea rcx,[r15+0x648]                           
0x670e3e2  lea rdx,[rbp+0x670]                           
0x670e3e9  call 0x675FB30                                ; -> sub_675fb30
0x670e3ee  nop                                           
0x670e3ef  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e3f6  mov rax,[rcx]                                 
0x670e3f9  mov rax,[rax+0x10]                            
0x670e3fd  movzx edx,byte ptr [rbp+0x848]                
0x670e404  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e40a  nop                                           
0x670e40b  mov eax,[r15+0x650]                           
0x670e412  sub eax,[r15+0x648]                           
0x670e419  shr eax,3                                     
0x670e41c  imul eax,0xFFFF8E39                           
0x670e422  dec eax                                       
0x670e424  mov [rbp+0x422],ax                            
0x670e42b  lea rcx,[r15+0x780]                           
0x670e432  lea rdx,[rbp+0x618]                           
0x670e439  call 0x675F3B0                                ; -> sub_675f3b0
0x670e43e  nop                                           
0x670e43f  mov eax,[r15+0x788]                           
```

Interpretation: Grow loc_670e374: lea rcx,[r15+0x618]; call 0x6760E60; nop. loc_670e381: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x848]=al. [rbp+0x3E0]=0x8004009. eax=[r15+0x618]; not eax; add eax,[r15+0x620]; [rbp+0x426]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. lea rcx,[r15+0x648]; lea rdx,[rbp+0x670]; call 0x675FB30. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x848]=al. eax=[r15+0x650]-[r15+0x648]; shr eax,3; imul eax,0xFFFF8E39; dec eax; [rbp+0x422]=ax. lea rcx,[r15+0x780]; lea rdx,[rbp+0x618]; call 0x675F3B0. nop. eax=[r15+0x788] (next: sub eax,[r15+0x780]).

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, 4 times), 0x675FB30 (sub_675fb30), 0x675F3B0 (sub_675f3b0).
Fields read: [r15+0x618], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x618], [r15+0x620], [rbp+0x426], [r15+0x648], [rbp+0x670], [rbp+0x848], [r15+0x650], [r15+0x648], [rbp+0x422], [r15+0x780], [rbp+0x618], [r15+0x788]. Fields written: [rbp+0x848], [rbp+0x3E0], [rbp+0x426], [rbp+0x848], [rbp+0x848], [rbp+0x422].
Matches F2 Phase? Same grow/not-eax-count/0x675FB30/0x675F3B0 idiom as Phase 12's tail. No exact F2 counterpart.

---

## Phase 15 — count [rbp+0x408] + TLS + item-slot write [rsi] + call 0xE869FF0 + bump [r15+0x770] + grow loc_670e4d3/4e0 + not-eax count + call 0x675FB30 (0x670e43f..0x670e53d)

Continues Phase 14's `eax=[r15+0x788]`: sub eax,[r15+0x780]; shr eax,3; imul eax,0xFFFF8BA3; dec eax; [rbp+0x408]=ax. TLS #2 → [rbp+0x848]. rsi=[r15+0x770]; cmp [r15+0x778]; if full → loc_670eafc (grow). Otherwise [rbp+0x590]→[rsi]; lea rcx,[rsi+8]; lea rdx,[rbp+0x598]; call 0xE869FF0; [rbp+0x610]→[rsi+0x80]; [rbp+0x610]=0; [r15+0x770]+=0x88; jmp loc_670eb13. Grow loc_670e4d3: call 0x6760E60(rcx=[r15+0x618]). loc_670e4e0: TLS #2 → [rbp+0x848]; eax=[r15+0x618]; not eax; add eax,[r15+0x620]; [rbp+0x426]=ax. TLS #2 → [rbp+0x848]. lea rcx,[r15+0x648]; lea rdx,[rbp+0x670]; call 0x675FB30.

```
0x670e43f  mov eax,[r15+0x788]                           
0x670e446  sub eax,[r15+0x780]                           
0x670e44d  shr eax,3                                     
0x670e450  imul eax,0xFFFF8BA3                           
0x670e456  dec eax                                       
0x670e458  mov [rbp+0x408],ax                            
0x670e45f  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e466  mov rax,[rcx]                                 
0x670e469  mov rax,[rax+0x10]                            
0x670e46d  mov dl,0x4A                                   
0x670e46f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e475  mov [rbp+0x848],al                            
0x670e47b  mov rsi,[r15+0x770]                           
0x670e482  cmp rsi,[r15+0x778]                           
0x670e489  je 0x670EAFC                                  ; -> loc_670eafc
0x670e48f  mov rax,[rbp+0x590]                           
0x670e496  mov [rsi],rax                                 
0x670e499  lea rcx,[rsi+8]                               
0x670e49d  lea rdx,[rbp+0x598]                           
0x670e4a4  call 0xE869FF0                                ; -> sub_e869ff0
0x670e4a9  nop                                           
0x670e4aa  mov rax,[rbp+0x610]                           
0x670e4b1  mov [rsi+0x80],rax                            
0x670e4b8  mov qword ptr [rbp+0x610],0                   
0x670e4c3  add qword ptr [r15+0x770],0x88                
0x670e4ce  jmp 0x670EB13                                 ; -> loc_670eb13
loc_670e4d3:  ; from 670e074
0x670e4d3  lea rcx,[r15+0x618]                           
0x670e4da  call 0x6760E60                                ; -> sub_6760e60
0x670e4df  nop                                           
loc_670e4e0:  ; from 670e084
0x670e4e0  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e4e7  mov rax,[rcx]                                 
0x670e4ea  mov rax,[rax+0x10]                            
0x670e4ee  movzx edx,byte ptr [rbp+0x848]                
0x670e4f5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e4fb  nop                                           
0x670e4fc  mov eax,[r15+0x618]                           
0x670e503  not eax                                       
0x670e505  add eax,[r15+0x620]                           
0x670e50c  mov [rbp+0x426],ax                            
0x670e513  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e51a  mov rax,[rcx]                                 
0x670e51d  mov rax,[rax+0x10]                            
0x670e521  mov dl,0x4A                                   
0x670e523  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e529  mov [rbp+0x848],al                            
0x670e52f  lea rcx,[r15+0x648]                           
0x670e536  lea rdx,[rbp+0x670]                           
0x670e53d  call 0x675FB30                                ; -> sub_675fb30
```

Interpretation: eax=[r15+0x788]-[r15+0x780]; eax>>=3; imul eax,0xFFFF8BA3; eax-=1; [rbp+0x408]=ax. TLS: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rsi=[r15+0x770]; cmp [r15+0x778]; if equal → loc_670eafc (grow). Otherwise eax=[rbp+0x590]; [rsi]=eax; rcx=[rsi+8]; rdx=&[rbp+0x598]; call 0xE869FF0. rax=[rbp+0x610]; [rsi+0x80]=rax; [rbp+0x610]=0; [r15+0x770]+=0x88; jmp loc_670eb13. Grow loc_670e4d3: lea rcx,[r15+0x618]; call 0x6760E60; nop. loc_670e4e0: TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r15+0x618]; not eax; add eax,[r15+0x620]; [rbp+0x426]=ax. TLS #2 again: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. lea rcx,[r15+0x648]; lea rdx,[rbp+0x670]; call 0x675FB30 (next: nop then TLS at 0x670e543).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 3 times), 0xE869FF0 (sub_e869ff0), 0x6760E60 (sub_6760e60), 0x675FB30 (sub_675fb30).
Fields read: [r15+0x788], [r15+0x780], [rbp+0x408], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x770], [r15+0x778], [rbp+0x590], [rsi], [rbp+0x610], [r15+0x770], [r15+0x618], [r15+0x620], [rbp+0x426], [r15+0x648], [rbp+0x670], [rbp+0x848]. Fields written: [rbp+0x408], [rbp+0x848], [rsi], [rsi+0x80], [rbp+0x610], [r15+0x770], [rbp+0x848], [rbp+0x426], [rbp+0x848].
Matches F2 Phase? Same item-slot write + grow/not-eax-count/0x675FB30 idiom as Phases 13-14. No exact F2 counterpart.

---

## Phase 16 — nop + TLS #2 + count [rbp+0x422] + call 0x675F3B0 + [rbp+0x3E0]=0xA005009 + count [rbp+0x408] + TLS + item-slot write + bump [r15+0x770] (0x670e542..0x670e632)

nop. TLS #2 → [rbp+0x848]. eax=[r15+0x650]; sub eax,[r15+0x648]; shr eax,3; imul eax,0xFFFF8E39; dec eax; [rbp+0x422]=ax. lea rcx,[r15+0x780]; lea rdx,[rbp+0x618]; call 0x675F3B0. [rbp+0x3E0]=0xA005009. eax=[r15+0x788]; sub eax,[r15+0x780]; shr eax,3; imul eax,0xFFFF8BA3; dec eax; [rbp+0x408]=ax. TLS #2 → [rbp+0x848]. rsi=[r15+0x770]; cmp [r15+0x778]; if full → loc_670eb9a (grow). Otherwise [rbp+0x590]→[rsi]; lea rcx,[rsi+8]; lea rdx,[rbp+0x598]; call 0xE869FF0; [rbp+0x610]→[rsi+0x80]; [rbp+0x610]=0; [r15+0x770]+=0x88; jmp loc_670ebb1. loc_670e632: lea rcx,[r15+0x618] (batch-3 final instr, unit continues beyond 600 instructions written so far).

```
0x670e542  nop                                           
0x670e543  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e54a  mov rax,[rcx]                                 
0x670e54d  mov rax,[rax+0x10]                            
0x670e551  movzx edx,byte ptr [rbp+0x848]                
0x670e558  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e55e  nop                                           
0x670e55f  mov eax,[r15+0x650]                           
0x670e566  sub eax,[r15+0x648]                           
0x670e56d  shr eax,3                                     
0x670e570  imul eax,0xFFFF8E39                           
0x670e576  dec eax                                       
0x670e578  mov [rbp+0x422],ax                            
0x670e57f  lea rcx,[r15+0x780]                           
0x670e586  lea rdx,[rbp+0x618]                           
0x670e58d  call 0x675F3B0                                ; -> sub_675f3b0
0x670e592  nop                                           
0x670e593  mov qword ptr [rbp+0x3E0],0xA005009           
0x670e59e  mov eax,[r15+0x788]                           
0x670e5a5  sub eax,[r15+0x780]                           
0x670e5ac  shr eax,3                                     
0x670e5af  imul eax,0xFFFF8BA3                           
0x670e5b5  dec eax                                       
0x670e5b7  mov [rbp+0x408],ax                            
0x670e5be  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670e5c5  mov rax,[rcx]                                 
0x670e5c8  mov rax,[rax+0x10]                            
0x670e5cc  mov dl,0x4A                                   
0x670e5ce  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670e5d4  mov [rbp+0x848],al                            
0x670e5da  mov rsi,[r15+0x770]                           
0x670e5e1  cmp rsi,[r15+0x778]                           
0x670e5e8  je 0x670EB9A                                  ; -> loc_670eb9a
0x670e5ee  mov rax,[rbp+0x590]                           
0x670e5f5  mov [rsi],rax                                 
0x670e5f8  lea rcx,[rsi+8]                               
0x670e5fc  lea rdx,[rbp+0x598]                           
0x670e603  call 0xE869FF0                                ; -> sub_e869ff0
0x670e608  nop                                           
0x670e609  mov rax,[rbp+0x610]                           
0x670e610  mov [rsi+0x80],rax                            
0x670e617  mov qword ptr [rbp+0x610],0                   
0x670e622  add qword ptr [r15+0x770],0x88                
0x670e62d  jmp 0x670EBB1                                 ; -> loc_670ebb1
loc_670e632:  ; from 670e0f4
0x670e632  lea rcx,[r15+0x618]                           
```

Interpretation: nop. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x848]=al. eax=[r15+0x650]-[r15+0x648]; shr eax,3; imul eax,0xFFFF8E39; eax-=1; [rbp+0x422]=ax. lea rcx,[r15+0x780]; lea rdx,[rbp+0x618]; call 0x675F3B0. nop. [rbp+0x3E0]=0xA005009. eax=[r15+0x788]-[r15+0x780]; eax>>=3; imul eax,0xFFFF8BA3; eax-=1; [rbp+0x408]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rsi=[r15+0x770]; cmp [r15+0x778]; if equal → loc_670eb9a (grow). Otherwise eax=[rbp+0x590]; [rsi]=eax; rcx=[rsi+8]; rdx=&[rbp+0x598]; call 0xE869FF0. rax=[rbp+0x610]; [rsi+0x80]=rax; [rbp+0x610]=0; [r15+0x770]+=0x88; jmp loc_670ebb1. loc_670e632: lea rcx,[r15+0x618] — batch-3's 300th and final instruction of this batch (unit continues beyond; next RVA 0x670e639).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675F3B0 (sub_675f3b0), 0xE869FF0 (sub_e869ff0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x650], [r15+0x648], [rbp+0x422], [r15+0x780], [rbp+0x618], [rbp+0x3E0], [r15+0x788], [r15+0x780], [rbp+0x408], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x770], [r15+0x778], [rbp+0x590], [rsi], [rbp+0x610], [r15+0x770]. Fields written: [rbp+0x848], [rbp+0x422], [rbp+0x3E0], [rbp+0x408], [rbp+0x848], [rsi], [rsi+0x80], [rbp+0x610], [r15+0x770].
Matches F2 Phase? Same item-slot write + count/0x675F3B0/[rbp+0x3E0] idiom. The `[rbp+0x3E0]=0xA005009` store is new (Phase 12-14 used 0x8004009). No exact F2 counterpart.




---

## Phase 1 — Item-buffer write from [rbp+0x6C8] + count compute + TLS (0x670d6cc..0x670d793)

Cursor/end check on [r15+0x758]/[r15+0x760]; if not full, copy 0x58-byte struct from [rbp+0x6C8] into [rdx], bump [r15+0x758] by 0x58, jmp 0x670DC0A. If full, call 0x1EF6F90, TLS read (dl=0x4A / movzx [rbp+0x848]), count compute (([r15+0x8A8]-[r15+0x8A0])>>1 - 1 → [rbp+0x3F0]).

```
0x670d6cc  nop                                           
0x670d6cd  mov [rbp+0x848],al                            
0x670d6d3  mov rdx,[r15+0x758]                           
0x670d6da  cmp rdx,[r15+0x760]                           
0x670d6e1  je 0x670DBF6                                  ; -> loc_670dbf6
0x670d6e7  lea rcx,[rbp+0x6C8]                           
0x670d6ee  mov eax,[rcx+0x10]                            
0x670d6f1  mov [rdx+0x10],eax                            
0x670d6f4  movups xmm0,[rcx]                             
0x670d6f7  movups [rdx],xmm0                             
0x670d6fa  movzx eax,byte ptr [rbp+0x6DC]                
0x670d701  mov [rdx+0x14],al                             
0x670d704  movss xmm0,[rbp+0x6E0]                        
0x670d70c  movss [rdx+0x18],xmm0                         
0x670d711  movss xmm0,[rbp+0x6E4]                        
0x670d719  movss [rdx+0x1C],xmm0                         
0x670d71e  movss xmm0,[rbp+0x6E8]                        
0x670d726  movss [rdx+0x20],xmm0                         
0x670d72b  movss xmm0,[rbp+0x6EC]                        
0x670d733  movss [rdx+0x24],xmm0                         
0x670d738  lea rax,[rbp+0x6F0]                           
0x670d73f  movups xmm0,[rax]                             
0x670d742  movups xmm1,[rax+0x10]                        
0x670d746  movups xmm2,[rax+0x1F]                        
0x670d74a  movups [rdx+0x28],xmm0                        
0x670d74e  movups [rdx+0x38],xmm1                        
0x670d752  movups [rdx+0x47],xmm2                        
0x670d756  add qword ptr [r15+0x758],0x58                
0x670d75e  jmp 0x670DC0A                                 ; -> loc_670dc0a
0x670d763  lea rcx,[r15+0x8A0]                           
0x670d76a  lea r8,[rbp+0x720]                            
0x670d771  call 0x1EF6F90                                ; -> sub_1ef6f90
0x670d776  nop                                           
0x670d777  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d77e  mov rax,[rcx]                                 
0x670d781  mov rax,[rax+0x10]                            
0x670d785  movzx edx,byte ptr [rbp+0x848]                
0x670d78c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d792  nop                                           
0x670d793  mov eax,[r15+0x8A8]                           
```

Interpretation: rdx=[r15+0x758] (item write cursor); cmp [r15+0x760] (end); if equal → loc_670dbf6 (grow path). Otherwise rcx=&[rbp+0x6C8]; eax=[rcx+0x10]→[rdx+0x10]; xmm0=[rcx]→[rdx]; byte [rbp+0x6DC]→[rdx+0x14]; [rbp+0x6E0]→[rdx+0x18]; [rbp+0x6E4]→[rdx+0x1C]; [rbp+0x6E8]→[rdx+0x20]; [rbp+0x6EC]→[rdx+0x24]; rax=&[rbp+0x6F0]; xmm0=[rax]→[rdx+0x28]; xmm1=[rax+0x10]→[rdx+0x38]; xmm2=[rax+0x1F]→[rdx+0x47]; [r15+0x758]+=0x58; jmp loc_670dc0a. Full path: lea rcx,[r15+0x8A0]; lea r8,[rbp+0x720]; call 0x1EF6F90; TLS: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r15+0x8A8] (next: sub eax,[r15+0x8A0]).

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [rbp+0x848], [r15+0x758], [r15+0x760], [rbp+0x6C8], [rcx+0x10], [rcx], [rbp+0x6DC], [rbp+0x6E0], [rbp+0x6E4], [rbp+0x6E8], [rbp+0x6EC], [rbp+0x6F0], [rax], [rax+0x10], [rbp+0x848], [r15+0x8A8]. Fields written: [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r15+0x758], [rbp+0x848].
Matches F2 Phase? No exact same-numbered counterpart — F2 Phases 29-30 are alternate-store/copy phases. This item-buffer 0x58-byte struct write idiom resembles F2's grow-path item writes but source is [rbp+0x6C8] local (F2 uses [rbx]/[rbp+0x6E0]-family slots).

---

## Phase 2 — Count compute + TLS + second item-buffer write from [rbp+0x6C8] (0x670d79a..0x670d860)

Continues Phase 1's count: eax=[r15+0x8A8]-[r15+0x8A0]; shr eax,1; dec eax; [rbp+0x3F0]=ax. TLS read dl=0x4A → [rbp+0x848]. Then cursor/end check [r15+0x758]/[r15+0x760]; if not full, copy 0x58-byte struct from [rbp+0x6C8] into [rdx], bump [r15+0x758] by 0x58, jmp 0x670DCA5.

```
0x670d79a  sub eax,[r15+0x8A0]                           
0x670d7a1  shr eax,1                                     
0x670d7a3  dec eax                                       
0x670d7a5  mov [rbp+0x3F0],ax                            
0x670d7ac  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d7b3  mov rax,[rcx]                                 
0x670d7b6  mov rax,[rax+0x10]                            
0x670d7ba  mov dl,0x4A                                   
0x670d7bc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d7c2  nop                                           
0x670d7c3  mov [rbp+0x848],al                            
0x670d7c9  mov rdx,[r15+0x758]                           
0x670d7d0  cmp rdx,[r15+0x760]                           
0x670d7d7  je 0x670DC91                                  ; -> loc_670dc91
0x670d7dd  lea rcx,[rbp+0x6C8]                           
0x670d7e4  mov eax,[rcx+0x10]                            
0x670d7e7  mov [rdx+0x10],eax                            
0x670d7ea  movups xmm0,[rcx]                             
0x670d7ed  movups [rdx],xmm0                             
0x670d7f0  movzx eax,byte ptr [rbp+0x6DC]                
0x670d7f7  mov [rdx+0x14],al                             
0x670d7fa  movss xmm0,[rbp+0x6E0]                        
0x670d802  movss [rdx+0x18],xmm0                         
0x670d807  movss xmm0,[rbp+0x6E4]                        
0x670d80f  movss [rdx+0x1C],xmm0                         
0x670d814  movss xmm0,[rbp+0x6E8]                        
0x670d81c  movss [rdx+0x20],xmm0                         
0x670d821  movss xmm0,[rbp+0x6EC]                        
0x670d829  movss [rdx+0x24],xmm0                         
0x670d82e  lea rax,[rbp+0x6F0]                           
0x670d835  movups xmm0,[rax]                             
0x670d838  movups xmm1,[rax+0x10]                        
0x670d83c  movups xmm2,[rax+0x1F]                        
0x670d840  movups [rdx+0x28],xmm0                        
0x670d844  movups [rdx+0x38],xmm1                        
0x670d848  movups [rdx+0x47],xmm2                        
0x670d84c  add qword ptr [r15+0x758],0x58                
0x670d854  jmp 0x670DCA5                                 ; -> loc_670dca5
0x670d859  lea rcx,[r15+0x8A0]                           
0x670d860  lea r8,[rbp+0x730]                            
```

Interpretation: eax=[r15+0x8A8]-[r15+0x8A0]; eax>>=1; eax-=1; [rbp+0x3F0]=ax. TLS: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x758]; cmp [r15+0x760]; if equal → loc_670dc91 (grow). Otherwise rcx=&[rbp+0x6C8]; same 0x58-byte struct copy to [rdx] as Phase 1; [r15+0x758]+=0x58; jmp loc_670dca5. Full path: lea rcx,[r15+0x8A0]; lea r8,[rbp+0x730] (next: call 0x1EF6F90).

Callees: [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [r15+0x8A8], [r15+0x8A0], [rbp+0x3F0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x758], [r15+0x760], [rbp+0x6C8], [rcx+0x10], [rcx], [rbp+0x6DC], [rbp+0x6E0], [rbp+0x6E4], [rbp+0x6E8], [rbp+0x6EC], [rbp+0x6F0], [rax], [rax+0x10]. Fields written: [rbp+0x3F0], [rbp+0x848], [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r15+0x758].
Matches F2 Phase? Same idiom as Phase 1 — no exact F2 counterpart.

---

## Phase 3 — Second count compute + TLS + third item-buffer write from [rbp+0x6D8] (0x670d867..0x670d92b)

Full path from Phase 2: call 0x1EF6F90(rcx=[r15+0x8A0], r8=[rbp+0x730]); TLS movzx edx=[rbp+0x848] → [rbp+0x848]; count (([r15+0x8A8]-[r15+0x8A0])>>1 - 1 → [rbp+0x3F0]); TLS dl=0x4A → [rbp+0x848]. Cursor/end [r15+0x758]/[r15+0x760]; if not full, copy 0x58-byte struct from [rbp+0x6D8] into [rdx], bump [r15+0x758] by 0x58, jmp 0x670DD40.

```
0x670d867  call 0x1EF6F90                                ; -> sub_1ef6f90
0x670d86c  nop                                           
0x670d86d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d874  mov rax,[rcx]                                 
0x670d877  mov rax,[rax+0x10]                            
0x670d87b  movzx edx,byte ptr [rbp+0x848]                
0x670d882  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d888  nop                                           
0x670d889  mov eax,[r15+0x8A8]                           
0x670d890  sub eax,[r15+0x8A0]                           
0x670d897  shr eax,1                                     
0x670d899  dec eax                                       
0x670d89b  mov [rbp+0x3F0],ax                            
0x670d8a2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d8a9  mov rax,[rcx]                                 
0x670d8ac  mov rax,[rax+0x10]                            
0x670d8b0  mov dl,0x4A                                   
0x670d8b2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d8b8  nop                                           
0x670d8b9  mov [rbp+0x848],al                            
0x670d8bf  mov rdx,[r15+0x758]                           
0x670d8c6  cmp rdx,[r15+0x760]                           
0x670d8cd  je 0x670DD2C                                  ; -> loc_670dd2c
0x670d8d3  lea rcx,[rbp+0x6D8]                           
0x670d8da  mov eax,[rcx+0x10]                            
0x670d8dd  mov [rdx+0x10],eax                            
0x670d8e0  movups xmm0,[rcx]                             
0x670d8e3  movups [rdx],xmm0                             
0x670d8e6  movzx eax,byte ptr [rbp+0x6EC]                
0x670d8ed  mov [rdx+0x14],al                             
0x670d8f0  movss xmm0,[rbp+0x6F0]                        
0x670d8f8  movss [rdx+0x18],xmm0                         
0x670d8fd  movss xmm0,[rbp+0x6F4]                        
0x670d905  movss [rdx+0x1C],xmm0                         
0x670d90a  movss xmm0,[rbp+0x6F8]                        
0x670d912  movss [rdx+0x20],xmm0                         
0x670d917  movss xmm0,[rbp+0x6FC]                        
0x670d91f  movss [rdx+0x24],xmm0                         
0x670d924  lea rax,[rbp+0x700]                           
0x670d92b  movups xmm0,[rax]                             
```

Interpretation: call 0x1EF6F90(rcx=[r15+0x8A0], r8=[rbp+0x730]). TLS #1: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x848]=al (next, beyond this phase's TLS #1 result store is actually the store at 0x670d8b9 — wait, order: 0x670d87b movzx edx,[rbp+0x848] then call, then 0x670d889 mov eax,[r15+0x8A8]... the store [rbp+0x848]=al comes at 0x670d8b9 after TLS #2. Actually TLS #1's al result is not stored until... let me re-read. 0x670d882 call [0xF99FFA0] returns al; then 0x670d888 nop; then 0x670d889 mov eax,[r15+0x8A8]. So TLS #1's al is OVERWRITTEN by eax=[r15+0x8A8] without being stored! Then TLS #2 at 0x670d8b2 returns al, stored at 0x670d8b9 → [rbp+0x848]=al. So only TLS #2's result is kept. Count: eax=[r15+0x8A8]-[r15+0x8A0]; shr eax,1; dec eax; [rbp+0x3F0]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x758]; cmp [r15+0x760]; if equal → loc_670dd2c (grow). Otherwise rcx=&[rbp+0x6D8]; eax=[rcx+0x10]→[rdx+0x10]; xmm0=[rcx]→[rdx]; byte [rbp+0x6EC]→[rdx+0x14]; [rbp+0x6F0]→[rdx+0x18]; [rbp+0x6F4]→[rdx+0x1C]; [rbp+0x6F8]→[rdx+0x20]; [rbp+0x6FC]→[rdx+0x24]; rax=&[rbp+0x700]; xmm0=[rax]→[rdx+0x28] (next: xmm1=[rax+0x10]).

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rbp+0x848], [0x1233E1B0], [rcx], [rax+0x10], [r15+0x8A8], [r15+0x8A0], [rbp+0x3F0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x758], [r15+0x760], [rbp+0x6D8], [rcx+0x10], [rcx], [rbp+0x6EC], [rbp+0x6F0], [rbp+0x6F4], [rbp+0x6F8], [rbp+0x6FC], [rbp+0x700], [rax]. Fields written: [rbp+0x848] (TLS #2 only; TLS #1 al dropped), [rbp+0x3F0], [rdx+0x10], [rdx], [rdx+0x14], [rdx+0x18], [rdx+0x1C], [rdx+0x20], [rdx+0x24], [rdx+0x28], [r15+0x758].
Matches F2 Phase? Same count-compute + TLS + item-write idiom as Phases 1-2; source [rbp+0x6D8] here. No exact F2 counterpart.

---

## Phase 4 — Third item-buffer write tail + fourth count/TLS/write from [rbp+0x700] (0x670d92e..0x670d9eb)

Continues Phase 3's struct write: xmm1=[rax+0x10], xmm2=[rax+0x1F] → [rdx+0x38]/[rdx+0x47]; [r15+0x758]+=0x58; jmp 0x670DD40. Full path: call 0x1EF6F90(rcx=[r12+0x8A0], r8=[rbp+0x758]); TLS movzx [rbp+0x848]; count (([r12+0x8A8]-[r12+0x8A0])>>1 - 1 → [rbp+0x3F0]); TLS dl=0x4A → [rbp+0x848]. Cursor/end [r12+0x758]/[r12+0x760]; if not full, copy 0x58-byte struct from [rbp+0x700] into [rdx] (eax=[rcx+0x10]→[rdx+0x10]; xmm0=[rcx]→[rdx]; byte [rbp+0x714]→[rdx+0x14]).

```
0x670d92e  movups xmm1,[rax+0x10]                        
0x670d932  movups xmm2,[rax+0x1F]                        
0x670d936  movups [rdx+0x28],xmm0                        
0x670d93a  movups [rdx+0x38],xmm1                        
0x670d93e  movups [rdx+0x47],xmm2                        
0x670d942  add qword ptr [r15+0x758],0x58                
0x670d94a  jmp 0x670DD40                                 ; -> loc_670dd40
0x670d94f  lea rcx,[r12+0x8A0]                           
0x670d957  lea r8,[rbp+0x758]                            
0x670d95e  call 0x1EF6F90                                ; -> sub_1ef6f90
0x670d963  nop                                           
0x670d964  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d96b  mov rax,[rcx]                                 
0x670d96e  mov rax,[rax+0x10]                            
0x670d972  movzx edx,byte ptr [rbp+0x848]                
0x670d979  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d97f  nop                                           
0x670d980  mov eax,[r12+0x8A8]                           
0x670d988  sub eax,[r12+0x8A0]                           
0x670d990  shr eax,1                                     
0x670d992  dec eax                                       
0x670d994  mov [rbp+0x3F0],ax                            
0x670d99b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670d9a2  mov rax,[rcx]                                 
0x670d9a5  mov rax,[rax+0x10]                            
0x670d9a9  mov dl,0x4A                                   
0x670d9ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670d9b1  nop                                           
0x670d9b2  mov [rbp+0x848],al                            
0x670d9b8  mov rdx,[r12+0x758]                           
0x670d9c0  cmp rdx,[r12+0x760]                           
0x670d9c8  je 0x670DDC7                                  ; -> loc_670ddc7
0x670d9ce  lea rcx,[rbp+0x700]                           
0x670d9d5  mov eax,[rcx+0x10]                            
0x670d9d8  mov [rdx+0x10],eax                            
0x670d9db  movups xmm0,[rcx]                             
0x670d9de  movups [rdx],xmm0                             
0x670d9e1  movzx eax,byte ptr [rbp+0x714]                
0x670d9e8  mov [rdx+0x14],al                             
```

Interpretation: xmm1=[rax+0x10]→[rdx+0x38]; xmm2=[rax+0x1F]→[rdx+0x47]; [r15+0x758]+=0x58; jmp loc_670dd40. Full path (note register switch r15→r12): lea rcx,[r12+0x8A0]; lea r8,[rbp+0x758]; call 0x1EF6F90. TLS #1: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0] (al dropped, not stored). eax=[r12+0x8A8]-[r12+0x8A0]; shr eax,1; dec eax; [rbp+0x3F0]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x758]; cmp [r12+0x760]; if equal → loc_670ddc7 (grow). Otherwise rcx=&[rbp+0x700]; eax=[rcx+0x10]→[rdx+0x10]; xmm0=[rcx]→[rdx]; byte [rbp+0x714]→[rdx+0x14] (next: movss [rbp+0x718]).

Callees: 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [rax+0x10], [rax+0x1F], [rdx+0x28], [rdx+0x38], [rdx+0x47], [r15+0x758], [rbp+0x848], [0x1233E1B0], [rcx], [rax+0x10], [r12+0x8A8], [r12+0x8A0], [rbp+0x3F0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x758], [r12+0x760], [rbp+0x700], [rcx+0x10], [rcx], [rbp+0x714]. Fields written: [rdx+0x38], [rdx+0x47], [r15+0x758], [rbp+0x848], [rbp+0x3F0], [rdx+0x10], [rdx], [rdx+0x14].
Matches F2 Phase? Same idiom; note register switch r15→r12 for the fourth iteration. Source [rbp+0x700]. No exact F2 counterpart.

---

## Phase 5 — imul/count tail + TLS + grow-path branch + cursor/end [r15+0x860]/[r15+0x868] (0x670dce3..0x670dda4)

Continues Phase 4's batch-1 `imul eax,0xFFFF8BA3`: dec eax; [rbp+0x40C]=ax. TLS dl=0x4A → [rbp+0x848]. Cursor/end check [r15+0x860]/[r15+0x868]; if full → loc_670e009 (grow). Otherwise inc rdx, [r15+0x860]=rdx, jmp loc_670e016.

```
0x670dce3  dec eax                                       
0x670dce5  mov [rbp+0x40C],ax                            
0x670dcec  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670dcf3  mov rax,[rcx]                                 
0x670dcf6  mov rax,[rax+0x10]                            
0x670dcfa  mov dl,0x4A                                   
0x670dcfc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670dd02  nop                                           
0x670dd03  mov [rbp+0x848],al                            
0x670dd09  mov rdx,[r15+0x860]                           
0x670dd10  cmp rdx,[r15+0x868]                           
0x670dd17  je 0x670E009                                  ; -> loc_670e009
0x670dd1d  inc rdx                                       
0x670dd20  mov [r15+0x860],rdx                           
0x670dd27  jmp 0x670E016                                 ; -> loc_670e016
0x670dd2c  lea rcx,[r15+0x750]                           
0x670dd33  lea r8,[rbp+0x6D8]                            
0x670dd3a  call 0x6760A80                                ; -> sub_6760a80
0x670dd3f  nop                                           
0x670dd40  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670dd47  mov rax,[rcx]                                 
0x670dd4a  mov rax,[rax+0x10]                            
0x670dd4e  movzx edx,byte ptr [rbp+0x848]                
0x670dd55  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670dd5b  nop                                           
0x670dd5c  mov qword ptr [rbp+0x3E0],0x4001              
0x670dd67  mov eax,[r15+0x758]                           
0x670dd6e  sub eax,[r15+0x750]                           
0x670dd75  shr eax,3                                     
0x670dd78  imul eax,0xFFFF8BA3                           
0x670dd7e  dec eax                                       
0x670dd80  mov [rbp+0x40C],ax                            
0x670dd87  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670dd8e  mov rax,[rcx]                                 
0x670dd91  mov rax,[rax+0x10]                            
0x670dd95  mov dl,0x4A                                   
0x670dd97  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670dd9d  nop                                           
0x670dd9e  mov [rbp+0x848],al                            
0x670dda4  mov rdx,[r15+0x860]                           
```

Interpretation: dec eax (completing `imul eax,0xFFFF8BA3; dec eax` from batch-1 end); [rbp+0x40C]=ax. TLS: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r15+0x860]; cmp [r15+0x868]; if equal → loc_670e009 (grow path: lea rcx,[r15+0x858]; call 0x6760E60). Otherwise inc rdx; [r15+0x860]=rdx; jmp loc_670e016. Grow path at 0x670dd2c: lea rcx,[r15+0x750]; lea r8,[rbp+0x6D8]; call 0x6760A80; then TLS/count at 0x670dd40.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x6760A80 (sub_6760a80).
Fields read: eax (imul result), [rbp+0x40C], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x860], [r15+0x868], [r15+0x750], [rbp+0x848]. Fields written: [rbp+0x40C], [rbp+0x848], [r15+0x860], [rbp+0x3E0].
Matches F2 Phase? No exact same-numbered counterpart — F2's grow paths use [0xF99FFA0]+[rbp+0x3E0]=0x4001 idiom but different slots ([r15+0x860]/[r15+0x868] here).

---

## Phase 6 — Grow path + count/TLS + cursor/end [r12+0x860]/[r12+0x868] (0x670ddab..0x670de7c)

Grow path loc_670e009: call 0x6760E60 then fall to loc_670e016. Main path: rdx=[r15+0x860]; cmp [r15+0x868]; if full → loc_670e089 (grow: call 0x6760E60). Otherwise inc [r15+0x860], jmp loc_670e096. loc_670e096: TLS/count ([r15+0x858] not-eax + [r15+0x860] → [rbp+0x3F6]), TLS dl=0x4A → [rbp+0x848], cursor/end [r15+0x620]/[r15+0x628]. Then separate r12-based grow path: loc_670ddc7 (call 0x6760A80(rcx=[r12+0x750], r8=[rbp+0x700])) → TLS/count → cursor/end [r12+0x860]/[r12+0x868]; if full → loc_670e109; otherwise inc [r12+0x860], jmp loc_670e117. loc_670de68: call 0x6760A80(rcx=[r12+0x750], r8=[rbp+0x710]).

```
0x670ddab  cmp rdx,[r15+0x868]                           
0x670ddb2  je 0x670E089                                  ; -> loc_670e089
0x670ddb8  inc rdx                                       
0x670ddbb  mov [r15+0x860],rdx                           
0x670ddc2  jmp 0x670E096                                 ; -> loc_670e096
0x670ddc7  lea rcx,[r12+0x750]                           
0x670ddcf  lea r8,[rbp+0x700]                            
0x670ddd6  call 0x6760A80                                ; -> sub_6760a80
0x670dddb  nop                                           
0x670dddc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670dde3  mov rax,[rcx]                                 
0x670dde6  mov rax,[rax+0x10]                            
0x670ddea  movzx edx,byte ptr [rbp+0x848]                
0x670ddf1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670ddf7  nop                                           
0x670ddf8  mov qword ptr [rbp+0x3E0],0x4001              
0x670de03  mov eax,[r12+0x758]                           
0x670de0b  sub eax,[r12+0x750]                           
0x670de13  shr eax,3                                     
0x670de16  imul eax,0xFFFF8BA3                           
0x670de1c  dec eax                                       
0x670de1e  mov [rbp+0x40C],ax                            
0x670de25  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x670de2c  mov rax,[rcx]                                 
0x670de2f  mov rax,[rax+0x10]                            
0x670de33  mov dl,0x4A                                   
0x670de35  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670de3b  nop                                           
0x670de3c  mov [rbp+0x848],al                            
0x670de42  mov rdx,[r12+0x860]                           
0x670de4a  cmp rdx,[r12+0x868]                           
0x670de52  je 0x670E109                                  ; -> loc_670e109
0x670de58  inc rdx                                       
0x670de5b  mov [r12+0x860],rdx                           
0x670de63  jmp 0x670E117                                 ; -> loc_670e117
0x670de68  lea rcx,[r12+0x750]                           
0x670de70  lea r8,[rbp+0x710]                            
0x670de77  call 0x6760A80                                ; -> sub_6760a80
0x670de7c  nop                                           
0x670de7d  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
```

Interpretation: rdx=[r15+0x860]; cmp [r15+0x868]; if equal → loc_670e089. Otherwise inc rdx; [r15+0x860]=rdx; jmp loc_670e096. Grow loc_670e089: lea rcx,[r15+0x858]; call 0x6760E60. loc_670ddc7 (r12 grow): lea rcx,[r12+0x750]; lea r8,[rbp+0x700]; call 0x6760A80. TLS/count: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E0]=0x4001; eax=[r12+0x758]-[r12+0x750]; shr eax,3; imul eax,0xFFFF8BA3; dec eax; [rbp+0x40C]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x860]; cmp [r12+0x868]; if equal → loc_670e109. Otherwise inc rdx; [r12+0x860]=rdx; jmp loc_670e117. loc_670de68: lea rcx,[r12+0x750]; lea r8,[rbp+0x710]; call 0x6760A80 (next: TLS at 0x670de7d).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x6760A80 (sub_6760a80, twice), 0x6760E60 (sub_6760e60).
Fields read: [r15+0x868], [r15+0x860], [r12+0x750], [rbp+0x700], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x758], [r12+0x750], [rbp+0x40C], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x860], [r12+0x868], [r12+0x750], [rbp+0x710]. Fields written: [r15+0x860], [rbp+0x3E0], [rbp+0x40C], [rbp+0x848], [r12+0x860].
Matches F2 Phase? Same grow/count/TLS idiom as Phase 5; register switch r15→r12 for second half. No exact F2 counterpart.

---

## Phase 7 — TLS/count + cursor/end [r12+0x860]/[r12+0x868] + grow path loc_670e109 + not-eax count (0x670de7d..0x670df53)

loc_670e117: TLS/count ([r12+0x858] not-eax + [r12+0x860] → [rbp+0x3F6]), TLS dl=0x4A → [rbp+0x848], cursor/end [r12+0x620]/[r12+0x628]; if full → loc_670e791; otherwise inc [r12+0x620], jmp loc_670e79f. Grow loc_670e18f: call 0x6760E60(rcx=[r12+0x858]). Then not-eax count pattern: eax=[r12+0x858]; not eax; add eax,[r12+0x860]; [rbp+0x3F6]=ax. TLS dl=0x4A → [rbp+0x848]. Cursor/end [r12+0x620]/[r12+0x628]; if full → loc_670e8fc; otherwise inc [r12+0x620], jmp loc_670e90a.

```
0x670de84  mov rax,[rcx]                                 
0x670de87  mov rax,[rax+0x10]                            
0x670de8b  movzx edx,byte ptr [rbp+0x848]                
0x670de92  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670de98  nop                                           
0x670de99  mov qword ptr [rbp+0x3E0],0x4001              
0x670dea4  mov eax,[r12+0x758]                           
0x670deac  sub eax,[r12+0x750]                           
0x670deb4  shr eax,3                                     
0x670deb7  imul eax,0xFFFF8BA3                           
0x670debd  dec eax                                       
0x670debf  mov [rbp+0x40C],ax                            
0x670dec6  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670decd  mov rax,[rcx]                                 
0x670ded0  mov rax,[rax+0x10]                            
0x670ded4  mov dl,0x4A                                   
0x670ded6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670dedc  nop                                           
0x670dedd  mov [rbp+0x848],al                            
0x670dee3  mov rdx,[r12+0x860]                           
0x670deeb  cmp rdx,[r12+0x868]                           
0x670def3  je 0x670E18F                                  ; -> loc_670e18f
0x670def9  inc rdx                                       
0x670defc  mov [r12+0x860],rdx                           
0x670df04  jmp 0x670E19D                                 ; -> loc_670e19d
0x670df09  lea rcx,[r15+0x858]                           
0x670df10  call 0x6760E60                                ; -> sub_6760e60
0x670df15  nop                                           
0x670df16  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670df1d  mov rax,[rcx]                                 
0x670df20  mov rax,[rax+0x10]                            
0x670df24  movzx edx,byte ptr [rbp+0x848]                
0x670df2b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670df31  nop                                           
0x670df32  mov eax,[r15+0x858]                           
0x670df39  not eax                                       
0x670df3b  add eax,[r15+0x860]                           
0x670df42  mov [rbp+0x3F6],ax                            
0x670df49  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670df50  mov rax,[rcx]                                 
0x670df53  mov rax,[rax+0x10]                            
```

Interpretation: rax=[rcx]; rax=[rax+0x10] (completing loc_670de68's TLS #1 setup). edx=byte [rbp+0x848]; call [0xF99FFA0]; [rbp+0x3E0]=0x4001; eax=[r12+0x758]-[r12+0x750]; shr eax,3; imul eax,0xFFFF8BA3; dec eax; [rbp+0x40C]=ax. TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. rdx=[r12+0x860]; cmp [r12+0x868]; if equal → loc_670e18f (grow: call 0x6760E60(rcx=[r12+0x858])). Otherwise inc rdx; [r12+0x860]=rdx; jmp loc_670e19d. loc_670e19d: TLS/count: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; edx=byte [rbp+0x848]; call [0xF99FFA0]; eax=[r15+0x858]; not eax; add eax,[r15+0x860]; [rbp+0x3F6]=ax (next: TLS #2 at 0x670df49).

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x6760E60 (sub_6760e60).
Fields read: [rcx], [rax+0x10], [rbp+0x848], [r12+0x758], [r12+0x750], [rbp+0x40C], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r12+0x860], [r12+0x868], [r15+0x858], [r15+0x860], [rbp+0x3F6], [0x1233E1B0], [rcx], [rax+0x10]. Fields written: [rbp+0x3E0], [rbp+0x40C], [rbp+0x848], [r12+0x860], [rbp+0x3F6].
Matches F2 Phase? Not-eax count idiom (`eax=[r15/12+0x858]; not eax; add eax,[r15/12+0x860]; [rbp+0x3F6]=ax`) is new vs Phases 1-6's shr/imul count. No exact F2 counterpart.

---

## Phase 8 — not-eax count tail + TLS + cursor/end [r15+0x620]/[r15+0x628] + grow paths + [rbp+0x3E0]=0x8004009 + call 0x675FB30 (0x670df57..0x670e015)

TLS #2: rcx=[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al. Cursor/end [r15+0x620]/[r15+0x628]; if full → loc_670e215 (grow: call 0x6760E60(rcx=[r15+0x618])); otherwise inc [r15+0x620], jmp loc_670e222. loc_670e222: TLS dl=0x4A → [rbp+0x848]; [rbp+0x3E0]=0x8004009; eax=[r15+0x618]; not eax; add eax,[r15+0x620]; [rbp+0x426]=ax. TLS dl=0x4A → [rbp+0x848]. lea rcx,[r15+0x648]; lea rdx,[rbp+0x668]; call 0x675FB30. TLS movzx edx=[rbp+0x848]; call [0xF99FFA0] (batch-2 last instr at 0x670e29e is beyond this phase — this phase ends at 0x670e015 nop).

```
0x670df57  mov dl,0x4A                                   
0x670df59  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670df5f  nop                                           
0x670df60  mov [rbp+0x848],al                            
0x670df66  mov rdx,[r15+0x620]                           
0x670df6d  cmp rdx,[r15+0x628]                           
0x670df74  je 0x670E215                                  ; -> loc_670e215
0x670df7a  inc rdx                                       
0x670df7d  mov [r15+0x620],rdx                           
0x670df84  jmp 0x670E222                                 ; -> loc_670e222
0x670df89  lea rcx,[r15+0x858]                           
0x670df90  call 0x6760E60                                ; -> sub_6760e60
0x670df95  nop                                           
0x670df96  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670df9d  mov rax,[rcx]                                 
0x670dfa0  mov rax,[rax+0x10]                            
0x670dfa4  movzx edx,byte ptr [rbp+0x848]                
0x670dfab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670dfb1  nop                                           
0x670dfb2  mov eax,[r15+0x858]                           
0x670dfb9  not eax                                       
0x670dfbb  add eax,[r15+0x860]                           
0x670dfc2  mov [rbp+0x3F6],ax                            
0x670dfc9  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x670dfd0  mov rax,[rcx]                                 
0x670dfd3  mov rax,[rax+0x10]                            
0x670dfd7  mov dl,0x4A                                   
0x670dfd9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x670dfdf  nop                                           
0x670dfe0  mov [rbp+0x848],al                            
0x670dfe6  mov rdx,[r15+0x620]                           
0x670dfed  cmp rdx,[r15+0x628]                           
0x670dff4  je 0x670E374                                  ; -> loc_670e374
0x670dffa  inc rdx                                       
0x670dffd  mov [r15+0x620],rdx                           
0x670e004  jmp 0x670E381                                 ; -> loc_670e381
loc_670e009:  ; from 670dd17
0x670e009  lea rcx,[r15+0x858]                           
0x670e010  call 0x6760E60                                ; -> sub_6760e60
0x670e015  nop                                           
```

Interpretation: dl=0x4A; call [0xF99FFA0]; [rbp+0x848]=al (completing loc_670e19d's TLS #2). rdx=[r15+0x620]; cmp [r15+0x628]; if equal → loc_670e215 (grow: lea rcx,[r15+0x618]; call 0x6760E60). Otherwise inc rdx; [r15+0x620]=rdx; jmp loc_670e222. Grow loc_670e215: lea rcx,[r15+0x618]; call 0x6760E60; nop (end of phase). Fall-through loc_670e222 (beyond phase): TLS/count/[rbp+0x3E0]=0x8004009/call 0x675FB30.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x6760E60 (sub_6760e60).
Fields read: [rbp+0x848], [0x1233E1B0], [rcx], [rax+0x10], [r15+0x620], [r15+0x628], [r15+0x858], [r15+0x860], [rbp+0x3F6], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x848], [r15+0x620], [r15+0x628], [r15+0x618]. Fields written: [rbp+0x848], [r15+0x620].
Matches F2 Phase? New `[rbp+0x3E0]=0x8004009` store + `call 0x675FB30` idiom appears at loc_670e222 (just beyond this phase's end). No exact F2 counterpart.

