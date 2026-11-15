# U-E4-F3: Chunk builder at 0x67762e0 — continuation of U-E4-F2

Unit: U-E4-F3
Function: sub_67762e0 (chunk builder, called by chunk extractor 0x66ea3d0) — continuation
RVAs: 0x6778c1a .. (800 instructions from 0x6778c1a)
Source: `rdis dis 0x6778c1a 800` on Minecraft.Windows.exe 1.26.62.01
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## NEXT
Resume at 0x677a4d4 (Phase 115) — after `sub rcx,rax` at 0x677a4d0, before `cmp ecx,0x20` at 0x677a4d4. Covered 0x6779563..0x677a4d0 (Phases 62-114, 800 instructions).

---

## Phase 41 — inc rdx/store + grow path 0x6760E60 + not+add counter + TLS feature flag + shared_ptr cursor inc (0x6778c1a..0x6778ca4)

Continues the shared_ptr [r14+0x7A0] increment, then a grow path, a not+add counter pattern, a TLS feature-flag read, and a shared_ptr [r13+0x7A0] cursor increment with bounds check.

```
0x6778c1a  inc rdx                                       
0x6778c1d  mov [r14+0x7A0],rdx                           
0x6778c24  jmp 0x6779153                                 ; -> loc_6779153
0x6778c29  lea rcx,[r13+0x888]                           
0x6778c30  call 0x6760E60                                ; -> sub_6760e60
0x6778c35  nop                                           
0x6778c36  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778c3d  mov rax,[rcx]                                 
0x6778c40  mov rax,[rax+0x10]                            
0x6778c44  movzx edx,byte ptr [rbp+0x838]                
0x6778c4b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778c51  nop                                           
0x6778c52  mov eax,[r13+0x888]                           
0x6778c59  not eax                                       
0x6778c5b  add eax,[r13+0x890]                           
0x6778c62  mov [rbp+0x312],ax                            
0x6778c69  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778c70  mov rax,[rcx]                                 
0x6778c73  mov rax,[rax+0x10]                            
0x6778c77  mov dl,0x4A                                   
0x6778c79  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778c7f  nop                                           
0x6778c80  mov [rbp+0x838],al                            
0x6778c86  mov rdx,[r13+0x7A0]                           
0x6778c8d  cmp rdx,[r13+0x7A8]                           
0x6778c94  je 0x67792A5                                  ; -> loc_67792a5
0x6778c9a  inc rdx                                       
0x6778c9d  mov [r13+0x7A0],rdx                           
0x6778ca4  jmp 0x67792B2                                 ; -> loc_67792b2
```

Interpretation: `inc rdx`; store incremented cursor at [r14+0x7A0]; jump to loc_6779153. Grow path: `lea rcx,[r13+0x888]`, call 0x6760E60. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r13+0x888], not eax, add eax,[r13+0x890], [rbp+0x312]=ax. Second TLS read: rcx=[0x1233E1B0]..., mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al (feature flag). Cursor bounds check: rdx=[r13+0x7A0], cmp with [r13+0x7A8]; if equal jump to loc_67792a5 (grow). Otherwise inc rdx, [r13+0x7A0]=rdx, jump to loc_67792b2.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r14+0x7A0] (implicit via inc/store), [r13+0x888], [r13+0x890], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x7A0], [r13+0x7A8]. Fields written: [r14+0x7A0], [rbp+0x312], [rbp+0x838], [r13+0x7A0].

---

## Phase 42 — Grow path 0x6760E60 + not+add counter + TLS feature flag + shared_ptr cursor inc (0x6778ca9..0x6778d24)

Grow path call, counter pattern, feature flag store, and shared_ptr [r13+0x7A0] cursor increment with bounds check.

```
0x6778ca9  lea rcx,[r13+0x888]                           
0x6778cb0  call 0x6760E60                                ; -> sub_6760e60
0x6778cb5  nop                                           
0x6778cb6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778cbd  mov rax,[rcx]                                 
0x6778cc0  mov rax,[rax+0x10]                            
0x6778cc4  movzx edx,byte ptr [rbp+0x838]                
0x6778ccb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778cd1  nop                                           
0x6778cd2  mov eax,[r13+0x888]                           
0x6778cd9  not eax                                       
0x6778cdb  add eax,[r13+0x890]                           
0x6778ce2  mov [rbp+0x312],ax                            
0x6778ce9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778cf0  mov rax,[rcx]                                 
0x6778cf3  mov rax,[rax+0x10]                            
0x6778cf7  mov dl,0x4A                                   
0x6778cf9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778cff  nop                                           
0x6778d00  mov [rbp+0x838],al                            
0x6778d06  mov rdx,[r13+0x7A0]                           
0x6778d0d  cmp rdx,[r13+0x7A8]                           
0x6778d14  je 0x6779404                                  ; -> loc_6779404
0x6778d1a  inc rdx                                       
0x6778d1d  mov [r13+0x7A0],rdx                           
0x6778d24  jmp 0x6779411                                 ; -> loc_6779411
```

Interpretation: `lea rcx,[r13+0x888]`, call 0x6760E60 (grow). TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r13+0x888], not eax, add eax,[r13+0x890], [rbp+0x312]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r13+0x7A0], cmp [r13+0x7A8]; if equal jump to loc_6779404 (grow). Otherwise inc rdx, [r13+0x7A0]=rdx, jump to loc_6779411.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r13+0x888], [r13+0x890], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x7A0], [r13+0x7A8]. Fields written: [rbp+0x312], [rbp+0x838], [r13+0x7A0].

---

## Phase 43 — Grow path 0x6760E60 + TLS feature flag + mov qword [rbp+0x300] + not+add counter + TLS feature flag + call 0x675FB30 (0x6778d29..0x6778da3)

Grow path for [r14+0x798], TLS reads, feature flag store, [rbp+0x300]=0x4803, not+add counter stored at [rbp+0x326], second feature flag store, then call 0x675FB30 with [r14+0x648] and [rbp+0x658].

```
0x6778d29  lea rcx,[r14+0x798]                           
0x6778d30  call 0x6760E60                                ; -> sub_6760e60
0x6778d35  nop                                           
0x6778d36  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778d3d  mov rax,[rcx]                                 
0x6778d40  mov rax,[rax+0x10]                            
0x6778d44  movzx edx,byte ptr [rbp+0x838]                
0x6778d4b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778d51  nop                                           
0x6778d52  mov qword ptr [rbp+0x300],0x4803              
0x6778d5d  mov eax,[r14+0x798]                           
0x6778d64  not eax                                       
0x6778d66  add eax,[r14+0x7A0]                           
0x6778d6d  mov [rbp+0x326],ax                            
0x6778d74  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778d7b  mov rax,[rcx]                                 
0x6778d7e  mov rax,[rax+0x10]                            
0x6778d82  mov dl,0x4A                                   
0x6778d84  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778d8a  mov [rbp+0x838],al                            
0x6778d90  lea rcx,[r14+0x648]                           
0x6778d97  lea rdx,[rbp+0x658]                           
0x6778d9e  call 0x675FB30                                ; -> sub_675fb30
0x6778da3  nop                                           
```

Interpretation: `lea rcx,[r14+0x798]`, call 0x6760E60 (grow). TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x4803 (u64). Counter: eax=[r14+0x798], not eax, add eax,[r14+0x7A0], [rbp+0x326]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. `lea rcx,[r14+0x648]`, `lea rdx,[rbp+0x658]`, call 0x675FB30.

Callees: 0x6760E60 (sub_6760e60), [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675FB30 (sub_675fb30).
Fields read: [r14+0x798], [r14+0x7A0], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x648]. Fields written: [rbp+0x300], [rbp+0x326], [rbp+0x838].

---

## Phase 44 — TLS feature flag + sub/shr/imul/dec counter + call 0x675F3B0 + sub/shr/imul/dec counter + TLS feature flag (0x6778da4..0x6778e2a)

TLS reads, feature flag store, two sub/shrink/imul/dec counter computations stored at [rbp+0x342] and [rbp+0x328], interleaved with call 0x675F3B0 and feature flag stores.

```
0x6778da4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778dab  mov rax,[rcx]                                 
0x6778dae  mov rax,[rax+0x10]                            
0x6778db2  movzx edx,byte ptr [rbp+0x838]                
0x6778db9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778dbf  nop                                           
0x6778dc0  mov eax,[r14+0x650]                           
0x6778dc7  sub eax,[r14+0x648]                           
0x6778dce  shr eax,3                                     
0x6778dd1  imul eax,0xFFFF8E39                           
0x6778dd7  dec eax                                       
0x6778dd9  mov [rbp+0x342],ax                            
0x6778de0  lea rcx,[r14+0x780]                           
0x6778de7  lea rdx,[rbp+0x600]                           
0x6778dee  call 0x675F3B0                                ; -> sub_675f3b0
0x6778df3  nop                                           
0x6778df4  mov eax,[r14+0x788]                           
0x6778dfb  sub eax,[r14+0x780]                           
0x6778e02  shr eax,3                                     
0x6778e05  imul eax,0xFFFF8BA3                           
0x6778e0b  dec eax                                       
0x6778e0d  mov [rbp+0x328],ax                            
0x6778e14  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778e1b  mov rax,[rcx]                                 
0x6778e1e  mov rax,[rax+0x10]                            
0x6778e22  mov dl,0x4A                                   
0x6778e24  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778e2a  mov [rbp+0x838],al                            
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter 1: eax=[r14+0x650], sub [r14+0x648], shr 3, imul 0xFFFF8E39, dec, [rbp+0x342]=ax. `lea rcx,[r14+0x780]`, `lea rdx,[rbp+0x600]`, call 0x675F3B0. Counter 2: eax=[r14+0x788], sub [r14+0x780], shr 3, imul 0xFFFF8BA3, dec, [rbp+0x328]=ax. TLS read again, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675F3B0 (sub_675f3b0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x650], [r14+0x648], [r14+0x788], [r14+0x780]. Fields written: [rbp+0x342], [rbp+0x328], [rbp+0x838].

---

## Phase 45 — mov r15 cmp je + store + call 0xE869FF0 + store + zero + add + jmp + grow path 0x6760E60 (0x6778e30..0x6778e94)

Loads r15=[r14+0x770], bounds-checks against [r14+0x778], on success stores [rbp+0x578] at [r15], calls 0xE869FF0, stores [rbp+0x5F8] at [r15+0x80], zeros [rbp+0x5F8], advances [r14+0x770] by 0x88, jumps; otherwise grow path call 0x6760E60.

```
0x6778e30  mov r15,[r14+0x770]                           
0x6778e37  cmp r15,[r14+0x778]                           
0x6778e3e  je 0x6779563                                  ; -> loc_6779563
0x6778e44  mov rax,[rbp+0x578]                           
0x6778e4b  mov [r15],rax                                 
0x6778e4e  lea rcx,[r15+8]                               
0x6778e52  lea rdx,[rbp+0x580]                           
0x6778e59  call 0xE869FF0                                ; -> sub_e869ff0
0x6778e5e  nop                                           
0x6778e5f  mov rax,[rbp+0x5F8]                           
0x6778e66  mov [r15+0x80],rax                            
0x6778e6d  mov qword ptr [rbp+0x5F8],0                   
0x6778e78  add qword ptr [r14+0x770],0x88                
0x6778e83  jmp 0x677957A                                 ; -> loc_677957a
0x6778e88  lea rcx,[r14+0x798]                           
0x6778e8f  call 0x6760E60                                ; -> sub_6760e60
0x6778e94  nop                                           
```

Interpretation: r15=[r14+0x770]; cmp r15,[r14+0x778]; if equal jump to loc_6779563 (grow). Otherwise rax=[rbp+0x578], [r15]=rax; rcx=r15+8, rdx=&[rbp+0x580], call 0xE869FF0; rax=[rbp+0x5F8], [r15+0x80]=rax; [rbp+0x5F8]=0; [r14+0x770]+=0x88; jump to loc_677957a. If bounds check failed (je taken): lea rcx,[r14+0x798], call 0x6760E60 (grow).

Callees: 0xE869FF0 (sub_e869ff0), 0x6760E60 (sub_6760e60).
Fields read: [r14+0x770], [r14+0x778], [rbp+0x578], [rbp+0x5F8], [r14+0x798]. Fields written: [r15], [r15+0x80], [rbp+0x5F8], [r14+0x770].

---

## Phase 46 — TLS feature flag + mov qword [rbp+0x300] + not+add counter + TLS feature flag + call 0x675FB30 (0x6778e95..0x6778f02)

TLS reads, feature flag store, [rbp+0x300]=0x4803, not+add counter at [rbp+0x326], second feature flag store, then call 0x675FB30 with [r14+0x648] and [rbp+0x660].

```
0x6778e95  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778e9c  mov rax,[rcx]                                 
0x6778e9f  mov rax,[rax+0x10]                            
0x6778ea3  movzx edx,byte ptr [rbp+0x838]                
0x6778eaa  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778eb0  nop                                           
0x6778eb1  mov qword ptr [rbp+0x300],0x4803              
0x6778ebc  mov eax,[r14+0x798]                           
0x6778ec3  not eax                                       
0x6778ec5  add eax,[r14+0x7A0]                           
0x6778ecc  mov [rbp+0x326],ax                            
0x6778ed3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778eda  mov rax,[rcx]                                 
0x6778edd  mov rax,[rax+0x10]                            
0x6778ee1  mov dl,0x4A                                   
0x6778ee3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778ee9  mov [rbp+0x838],al                            
0x6778eef  lea rcx,[r14+0x648]                           
0x6778ef6  lea rdx,[rbp+0x660]                           
0x6778efd  call 0x675FB30                                ; -> sub_675fb30
0x6778f02  nop                                           
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x4803 (u64). Counter: eax=[r14+0x798], not eax, add eax,[r14+0x7A0], [rbp+0x326]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. `lea rcx,[r14+0x648]`, `lea rdx,[rbp+0x660]`, call 0x675FB30.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675FB30 (sub_675fb30).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x798], [r14+0x7A0], [r14+0x648]. Fields written: [rbp+0x300], [rbp+0x326], [rbp+0x838].

---

## Phase 47 — TLS feature flag + sub/shr/imul/dec counter + call 0x675F3B0 + sub/shr/imul/dec counter + TLS feature flag (0x6778f03..0x6778f89)

TLS reads, feature flag store, two sub/shrink/imul/dec counter computations stored at [rbp+0x342] and [rbp+0x328], interleaved with call 0x675F3B0 and feature flag stores.

```
0x6778f03  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778f0a  mov rax,[rcx]                                 
0x6778f0d  mov rax,[rax+0x10]                            
0x6778f11  movzx edx,byte ptr [rbp+0x838]                
0x6778f18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778f1e  nop                                           
0x6778f1f  mov eax,[r14+0x650]                           
0x6778f26  sub eax,[r14+0x648]                           
0x6778f2d  shr eax,3                                     
0x6778f30  imul eax,0xFFFF8E39                           
0x6778f36  dec eax                                       
0x6778f38  mov [rbp+0x342],ax                            
0x6778f3f  lea rcx,[r14+0x780]                           
0x6778f46  lea rdx,[rbp+0x608]                           
0x6778f4d  call 0x675F3B0                                ; -> sub_675f3b0
0x6778f52  nop                                           
0x6778f53  mov eax,[r14+0x788]                           
0x6778f5a  sub eax,[r14+0x780]                           
0x6778f61  shr eax,3                                     
0x6778f64  imul eax,0xFFFF8BA3                           
0x6778f6a  dec eax                                       
0x6778f6c  mov [rbp+0x328],ax                            
0x6778f73  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778f7a  mov rax,[rcx]                                 
0x6778f7d  mov rax,[rax+0x10]                            
0x6778f81  mov dl,0x4A                                   
0x6778f83  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6778f89  mov [rbp+0x838],al                            
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter 1: eax=[r14+0x650], sub [r14+0x648], shr 3, imul 0xFFFF8E39, dec, [rbp+0x342]=ax. `lea rcx,[r14+0x780]`, `lea rdx,[rbp+0x608]`, call 0x675F3B0. Counter 2: eax=[r14+0x788], sub [r14+0x780], shr 3, imul 0xFFFF8BA3, dec, [rbp+0x328]=ax. TLS read again, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675F3B0 (sub_675f3b0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x650], [r14+0x648], [r14+0x788], [r14+0x780]. Fields written: [rbp+0x342], [rbp+0x328], [rbp+0x838].

---

## Phase 48 — mov r15 cmp je + store + call 0xE869FF0 + store + zero + add + jmp + grow path 0x6760E60 (0x6778f8f..0x6778ff3)

Loads r15=[r14+0x770], bounds-checks against [r14+0x778], on success stores [rbp+0x580] at [r15], calls 0xE869FF0, stores [rbp+0x600] at [r15+0x80], zeros [rbp+0x600], advances [r14+0x770] by 0x88, jumps; otherwise grow path call 0x6760E60.

```
0x6778f8f  mov r15,[r14+0x770]                           
0x6778f96  cmp r15,[r14+0x778]                           
0x6778f9d  je 0x67795F8                                  ; -> loc_67795f8
0x6778fa3  mov rax,[rbp+0x580]                           
0x6778faa  mov [r15],rax                                 
0x6778fad  lea rcx,[r15+8]                               
0x6778fb1  lea rdx,[rbp+0x588]                           
0x6778fb8  call 0xE869FF0                                ; -> sub_e869ff0
0x6778fbd  nop                                           
0x6778fbe  mov rax,[rbp+0x600]                           
0x6778fc5  mov [r15+0x80],rax                            
0x6778fcc  mov qword ptr [rbp+0x600],0                   
0x6778fd7  add qword ptr [r14+0x770],0x88                
0x6778fe2  jmp 0x677960F                                 ; -> loc_677960f
0x6778fe7  lea rcx,[r14+0x798]                           
0x6778fee  call 0x6760E60                                ; -> sub_6760e60
0x6778ff3  nop                                           
```

Interpretation: r15=[r14+0x770]; cmp r15,[r14+0x778]; if equal jump to loc_67795f8 (grow). Otherwise rax=[rbp+0x580], [r15]=rax; rcx=r15+8, rdx=&[rbp+0x588], call 0xE869FF0; rax=[rbp+0x600], [r15+0x80]=rax; [rbp+0x600]=0; [r14+0x770]+=0x88; jump to loc_677960f. If bounds check failed (je taken): lea rcx,[r14+0x798], call 0x6760E60 (grow).

Callees: 0xE869FF0 (sub_e869ff0), 0x6760E60 (sub_6760e60).
Fields read: [r14+0x770], [r14+0x778], [rbp+0x580], [rbp+0x600], [r14+0x798]. Fields written: [r15], [r15+0x80], [rbp+0x600], [r14+0x770].

---

## Phase 49 — TLS feature flag + not+add counter + TLS feature flag + call 0x675FB30 (0x6778ff4..0x6779056)

TLS reads, feature flag store, not+add counter stored at [rbp+0x326], second feature flag store, then call 0x675FB30 with [r14+0x648] and [rbp+0x660].

```
0x6778ff4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6778ffb  mov rax,[rcx]                                 
0x6778ffe  mov rax,[rax+0x10]                            
0x6779002  movzx edx,byte ptr [rbp+0x838]                
0x6779009  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677900f  nop                                           
0x6779010  mov eax,[r14+0x798]                           
0x6779017  not eax                                       
0x6779019  add eax,[r14+0x7A0]                           
0x6779020  mov [rbp+0x326],ax                            
0x6779027  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677902e  mov rax,[rcx]                                 
0x6779031  mov rax,[rax+0x10]                            
0x6779035  mov dl,0x4A                                   
0x6779037  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677903d  mov [rbp+0x838],al                            
0x6779043  lea rcx,[r14+0x648]                           
0x677904a  lea rdx,[rbp+0x660]                           
0x6779051  call 0x675FB30                                ; -> sub_675fb30
0x6779056  nop                                           
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r14+0x798], not eax, add eax,[r14+0x7A0], [rbp+0x326]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. `lea rcx,[r14+0x648]`, `lea rdx,[rbp+0x660]`, call 0x675FB30.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675FB30 (sub_675fb30).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x798], [r14+0x7A0], [r14+0x648]. Fields written: [rbp+0x326], [rbp+0x838].

---

## Phase 50 — TLS feature flag + sub/shr/imul/dec counter + call 0x675F3B0 + mov qword [rbp+0x300] + sub/shr/imul/dec counter (0x6779057..0x67790cb)

TLS reads, feature flag store, two sub/shrink/imul/dec counter computations stored at [rbp+0x342] and [rbp+0x328], interleaved with call 0x675F3B0 and [rbp+0x300]=0x2005803.

```
0x6779057  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677905e  mov rax,[rcx]                                 
0x6779061  mov rax,[rax+0x10]                            
0x6779065  movzx edx,byte ptr [rbp+0x838]                
0x677906c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779072  nop                                           
0x6779073  mov eax,[r14+0x650]                           
0x677907a  sub eax,[r14+0x648]                           
0x6779081  shr eax,3                                     
0x6779084  imul eax,0xFFFF8E39                           
0x677908a  dec eax                                       
0x677908c  mov [rbp+0x342],ax                            
0x6779093  lea rcx,[r14+0x780]                           
0x677909a  lea rdx,[rbp+0x608]                           
0x67790a1  call 0x675F3B0                                ; -> sub_675f3b0
0x67790a6  nop                                           
0x67790a7  mov qword ptr [rbp+0x300],0x2005803           
0x67790b2  mov eax,[r14+0x788]                           
0x67790b9  sub eax,[r14+0x780]                           
0x67790c0  shr eax,3                                     
0x67790c3  imul eax,0xFFFF8BA3                           
0x67790c9  dec eax                                       
0x67790cb  mov [rbp+0x328],ax                            
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter 1: eax=[r14+0x650], sub [r14+0x648], shr 3, imul 0xFFFF8E39, dec, [rbp+0x342]=ax. `lea rcx,[r14+0x780]`, `lea rdx,[rbp+0x608]`, call 0x675F3B0. [rbp+0x300]=0x2005803 (u64). Counter 2: eax=[r14+0x788], sub [r14+0x780], shr 3, imul 0xFFFF8BA3, dec, [rbp+0x328]=ax.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x675F3B0 (sub_675f3b0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x650], [r14+0x648], [r14+0x788], [r14+0x780]. Fields written: [rbp+0x342], [rbp+0x300], [rbp+0x328].

---

## Phase 51 — TLS feature flag + mov r15 cmp je + store + call 0xE869FF0 + store + zero + add + jmp + grow path 0x6760E60 (0x67790d2..0x6779141)

TLS read, feature flag store, r15=[r14+0x770] bounds-check against [r14+0x778], on success store [rbp+0x580] at [r15], call 0xE869FF0, store [rbp+0x600] at [r15+0x80], zero [rbp+0x600], advance [r14+0x770] by 0x88, jump; otherwise grow path.

```
0x67790d2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67790d9  mov rax,[rcx]                                 
0x67790dc  mov rax,[rax+0x10]                            
0x67790e0  mov dl,0x4A                                   
0x67790e2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67790e8  mov [rbp+0x838],al                            
0x67790ee  mov r15,[r14+0x770]                           
0x67790f5  cmp r15,[r14+0x778]                           
0x67790fc  je 0x6779696                                  ; -> loc_6779696
0x6779102  mov rax,[rbp+0x580]                           
0x6779109  mov [r15],rax                                 
0x677910c  lea rcx,[r15+8]                               
0x6779110  lea rdx,[rbp+0x588]                           
0x6779117  call 0xE869FF0                                ; -> sub_e869ff0
0x677911c  nop                                           
0x677911d  mov rax,[rbp+0x600]                           
0x6779124  mov [r15+0x80],rax                            
0x677912b  mov qword ptr [rbp+0x600],0                   
0x6779136  add qword ptr [r14+0x770],0x88                
0x6779141  jmp 0x67796AD                                 ; -> loc_67796ad
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. r15=[r14+0x770]; cmp r15,[r14+0x778]; if equal jump to loc_6779696 (grow). Otherwise rax=[rbp+0x580], [r15]=rax; rcx=r15+8, rdx=&[rbp+0x588], call 0xE869FF0; rax=[rbp+0x600], [r15+0x80]=rax; [rbp+0x600]=0; [r14+0x770]+=0x88; jump to loc_67796ad.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0xE869FF0 (sub_e869ff0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x770], [r14+0x778], [rbp+0x580], [rbp+0x600]. Fields written: [rbp+0x838], [r15], [r15+0x80], [rbp+0x600], [r14+0x770].

---

## Phase 52 — Grow path call 0x6760E60 (0x6779146..0x6779152)

Small grow-path stub reached from the failed bounds check in Phase 51.

```
0x6779146  lea rcx,[r14+0x798]                           
0x677914d  call 0x6760E60                                ; -> sub_6760e60
0x6779152  nop                                           
```

Interpretation: `lea rcx,[r14+0x798]`, call 0x6760E60 (grow).

Callees: 0x6760E60 (sub_6760e60).
Fields read: [r14+0x798]. Fields written: none.

---

## Phase 53 — loc_6779153: TLS feature flag + not+add counter + TLS feature flag + call 0x675FB30 (0x6779153..0x67791b5)

TLS reads, feature flag store, not+add counter stored at [rbp+0x326], second feature flag store, then call 0x675FB30 with [r14+0x648] and [rbp+0x670].

```
0x6779153  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677915a  mov rax,[rcx]                                 
0x677915d  mov rax,[rax+0x10]                            
0x6779161  movzx edx,byte ptr [rbp+0x838]                
0x6779168  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677916e  nop                                           
0x677916f  mov eax,[r14+0x798]                           
0x6779176  not eax                                       
0x6779178  add eax,[r14+0x7A0]                           
0x677917f  mov [rbp+0x326],ax                            
0x6779186  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677918d  mov rax,[rcx]                                 
0x6779190  mov rax,[rax+0x10]                            
0x6779194  mov dl,0x4A                                   
0x6779196  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677919c  mov [rbp+0x838],al                            
0x67791a2  lea rcx,[r14+0x648]                           
0x67791a9  lea rdx,[rbp+0x670]                           
0x67791b0  call 0x675FB30                                ; -> sub_675fb30
0x67791b5  nop                                           
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r14+0x798], not eax, add eax,[r14+0x7A0], [rbp+0x326]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. `lea rcx,[r14+0x648]`, `lea rdx,[rbp+0x670]`, call 0x675FB30.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x675FB30 (sub_675fb30).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x798], [r14+0x7A0], [r14+0x648]. Fields written: [rbp+0x326], [rbp+0x838].

---

## Phase 54 — TLS feature flag + sub/shr/imul/dec counter + call 0x675F3B0 + mov qword [rbp+0x300] + sub/shr/imul/dec counter (0x67791b6..0x677922a)

TLS reads, feature flag store, two sub/shrink/imul/dec counter computations stored at [rbp+0x342] and [rbp+0x328], interleaved with call 0x675F3B0 and [rbp+0x300]=0x2005803.

```
0x67791b6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67791bd  mov rax,[rcx]                                 
0x67791c0  mov rax,[rax+0x10]                            
0x67791c4  movzx edx,byte ptr [rbp+0x838]                
0x67791cb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67791d1  nop                                           
0x67791d2  mov eax,[r14+0x650]                           
0x67791d9  sub eax,[r14+0x648]                           
0x67791e0  shr eax,3                                     
0x67791e3  imul eax,0xFFFF8E39                           
0x67791e9  dec eax                                       
0x67791eb  mov [rbp+0x342],ax                            
0x67791f2  lea rcx,[r14+0x780]                           
0x67791f9  lea rdx,[rbp+0x618]                           
0x6779200  call 0x675F3B0                                ; -> sub_675f3b0
0x6779205  nop                                           
0x6779206  mov qword ptr [rbp+0x300],0x2005803           
0x6779211  mov eax,[r14+0x788]                           
0x6779218  sub eax,[r14+0x780]                           
0x677921f  shr eax,3                                     
0x6779222  imul eax,0xFFFF8BA3                           
0x6779228  dec eax                                       
0x677922a  mov [rbp+0x328],ax                            
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter 1: eax=[r14+0x650], sub [r14+0x648], shr 3, imul 0xFFFF8E39, dec, [rbp+0x342]=ax. `lea rcx,[r14+0x780]`, `lea rdx,[rbp+0x618]`, call 0x675F3B0. [rbp+0x300]=0x2005803 (u64). Counter 2: eax=[r14+0x788], sub [r14+0x780], shr 3, imul 0xFFFF8BA3, dec, [rbp+0x328]=ax.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x675F3B0 (sub_675f3b0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x650], [r14+0x648], [r14+0x788], [r14+0x780]. Fields written: [rbp+0x342], [rbp+0x300], [rbp+0x328].

---

## Phase 55 — TLS feature flag + mov r15 cmp je + store + call 0xE869FF0 + store + zero + add + jmp + grow path 0x677974D (0x6779231..0x67792a0)

TLS read, feature flag store, r15=[r14+0x770] bounds-check against [r14+0x778], on success store [rbp+0x590] at [r15], call 0xE869FF0, store [rbp+0x610] at [r15+0x80], zero [rbp+0x610], advance [r14+0x770] by 0x88, jump; otherwise grow path loc_677974D.

```
0x6779231  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779238  mov rax,[rcx]                                 
0x677923b  mov rax,[rax+0x10]                            
0x677923f  mov dl,0x4A                                   
0x6779241  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779247  mov [rbp+0x838],al                            
0x677924d  mov r15,[r14+0x770]                           
0x6779254  cmp r15,[r14+0x778]                           
0x677925b  je 0x677974D                                  ; -> loc_677974d
0x6779261  mov rax,[rbp+0x590]                           
0x6779268  mov [r15],rax                                 
0x677926b  lea rcx,[r15+8]                               
0x677926f  lea rdx,[rbp+0x598]                           
0x6779276  call 0xE869FF0                                ; -> sub_e869ff0
0x677927b  nop                                           
0x677927c  mov rax,[rbp+0x610]                           
0x6779283  mov [r15+0x80],rax                            
0x677928a  mov qword ptr [rbp+0x610],0                   
0x6779295  add qword ptr [r14+0x770],0x88                
0x67792a0  jmp 0x6779764                                 ; -> loc_6779764
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. r15=[r14+0x770]; cmp r15,[r14+0x778]; if equal jump to loc_677974d (grow). Otherwise rax=[rbp+0x590], [r15]=rax; rcx=r15+8, rdx=&[rbp+0x598], call 0xE869FF0; rax=[rbp+0x610], [r15+0x80]=rax; [rbp+0x610]=0; [r14+0x770]+=0x88; jump to loc_6779764.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0xE869FF0 (sub_e869ff0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x770], [r14+0x778], [rbp+0x590], [rbp+0x610]. Fields written: [rbp+0x838], [r15], [r15+0x80], [rbp+0x610], [r14+0x770].

---

## Phase 56 — Grow path call 0x6760E60 at loc_67792a5 (0x67792a5..0x67792b1)

Small grow-path stub reached from the failed bounds check in Phase 55 (je to loc_677974d ultimately flows through loc_67792a5? Actually reached from 0x6778c94 je).

```
0x67792a5  lea rcx,[r13+0x798]                           
0x67792ac  call 0x6760E60                                ; -> sub_6760e60
0x67792b1  nop                                           
```

Interpretation: `lea rcx,[r13+0x798]`, call 0x6760E60 (grow).

Callees: 0x6760E60 (sub_6760e60).
Fields read: [r13+0x798]. Fields written: none.

---

## Phase 57 — loc_67792b2: TLS feature flag + mov qword [rbp+0x300] + not+add counter + TLS feature flag + call 0x675FB30 + TLS feature flag + sub/shr/imul/dec counter (0x67792b2..0x6779355)

TLS reads, feature flag store, [rbp+0x300]=0x4803, not+add counter at [rbp+0x326], second feature flag store, call 0x675FB30 with [r13+0x648] and [rbp+0x698], third TLS feature flag store, sub/shrink/imul/dec counter stored at [rbp+0x342].

```
0x67792b2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67792b9  mov rax,[rcx]                                 
0x67792bc  mov rax,[rax+0x10]                            
0x67792c0  movzx edx,byte ptr [rbp+0x838]                
0x67792c7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67792cd  nop                                           
0x67792ce  mov qword ptr [rbp+0x300],0x4803              
0x67792d9  mov eax,[r13+0x798]                           
0x67792e0  not eax                                       
0x67792e2  add eax,[r13+0x7A0]                           
0x67792e9  mov [rbp+0x326],ax                            
0x67792f0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67792f7  mov rax,[rcx]                                 
0x67792fa  mov rax,[rax+0x10]                            
0x67792fe  mov dl,0x4A                                   
0x6779300  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779306  mov [rbp+0x838],al                            
0x677930c  lea rcx,[r13+0x648]                           
0x6779313  lea rdx,[rbp+0x698]                           
0x677931a  call 0x675FB30                                ; -> sub_675fb30
0x677931f  nop                                           
0x6779320  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779327  mov rax,[rcx]                                 
0x677932a  mov rax,[rax+0x10]                            
0x677932e  movzx edx,byte ptr [rbp+0x838]                
0x6779335  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677933b  nop                                           
0x677933c  mov eax,[r13+0x650]                           
0x6779343  sub eax,[r13+0x648]                           
0x677934a  shr eax,3                                     
0x677934d  imul eax,0xFFFF8E39                           
0x6779353  dec eax                                       
0x6779355  mov [rbp+0x342],ax                            
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x4803 (u64). Counter: eax=[r13+0x798], not eax, add eax,[r13+0x7A0], [rbp+0x326]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. `lea rcx,[r13+0x648]`, `lea rdx,[rbp+0x698]`, call 0x675FB30. Third TLS read, mov dl,0x4A, call via [0xF99FFA0]. Counter: eax=[r13+0x650], sub [r13+0x648], shr 3, imul 0xFFFF8E39, dec, [rbp+0x342]=ax.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x675FB30 (sub_675fb30).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x798], [r13+0x7A0], [r13+0x648], [r13+0x650]. Fields written: [rbp+0x300], [rbp+0x326], [rbp+0x838], [rbp+0x342].

---

## Phase 58 — call 0x675F3B0 + sub/shr/imul/dec counter + TLS feature flag + mov r15 cmp je + store + call 0xE869FF0 + store + zero + add + jmp (0x677935c..0x67793ff)

`lea rcx,[r13+0x780]`, `lea rdx,[rbp+0x640]`, call 0x675F3B0, counter 2 at [rbp+0x328], TLS feature flag store, r15=[r13+0x770] bounds-check against [r13+0x778], on success store [rbp+0x5B8] at [r15], call 0xE869FF0, store [rbp+0x638] at [r15+0x80], zero [rbp+0x638], advance [r13+0x770] by 0x88, jump; otherwise grow path loc_6779804.

```
0x677935c  lea rcx,[r13+0x780]                           
0x6779363  lea rdx,[rbp+0x640]                           
0x677936a  call 0x675F3B0                                ; -> sub_675f3b0
0x677936f  nop                                           
0x6779370  mov eax,[r13+0x788]                           
0x6779377  sub eax,[r13+0x780]                           
0x677937e  shr eax,3                                     
0x6779381  imul eax,0xFFFF8BA3                           
0x6779387  dec eax                                       
0x6779389  mov [rbp+0x328],ax                            
0x6779390  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779397  mov rax,[rcx]                                 
0x677939a  mov rax,[rax+0x10]                            
0x677939e  mov dl,0x4A                                   
0x67793a0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67793a6  mov [rbp+0x838],al                            
0x67793ac  mov r15,[r13+0x770]                           
0x67793b3  cmp r15,[r13+0x778]                           
0x67793ba  je 0x6779804                                  ; -> loc_677980d
0x67793c0  mov rax,[rbp+0x5B8]                           
0x67793c7  mov [r15],rax                                 
0x67793ca  lea rcx,[r15+8]                               
0x67793ce  lea rdx,[rbp+0x5C0]                           
0x67793d5  call 0xE869FF0                                ; -> sub_e869ff0
0x67793da  nop                                           
0x67793db  mov rax,[rbp+0x638]                           
0x67793e2  mov [r15+0x80],rax                            
0x67793e9  mov qword ptr [rbp+0x638],0                   
0x67793f4  add qword ptr [r13+0x770],0x88                
0x67793ff  jmp 0x677981B                                 ; -> loc_677981b
```

Interpretation: `lea rcx,[r13+0x780]`, `lea rdx,[rbp+0x640]`, call 0x675F3B0. Counter 2: eax=[r13+0x788], sub [r13+0x780], shr 3, imul 0xFFFF8BA3, dec, [rbp+0x328]=ax. TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. r15=[r13+0x770]; cmp r15,[r13+0x778]; if equal jump to loc_6779804 (grow). Otherwise rax=[rbp+0x5B8], [r15]=rax; rcx=r15+8, rdx=&[rbp+0x5C0], call 0xE869FF0; rax=[rbp+0x638], [r15+0x80]=rax; [rbp+0x638]=0; [r13+0x770]+=0x88; jump to loc_677981b.

Callees: 0x675F3B0 (sub_675f3b0), [0xF99FFA0] = sub_eea6040 (indirect), 0xE869FF0 (sub_e869ff0).
Fields read: [r13+0x780], [rbp+0x640], [r13+0x788], [r13+0x780], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x770], [r13+0x778], [rbp+0x5B8], [rbp+0x638]. Fields written: [rbp+0x328], [rbp+0x838], [r15], [r15+0x80], [rbp+0x638], [r13+0x770].

---

## Phase 60 — loc_6779411: TLS feature flag + mov qword [rbp+0x300] + not+add counter + TLS feature flag + call 0x675FB30 + TLS feature flag + sub/shr/imul/dec counter (0x6779411..0x67794a9)

TLS reads, feature flag store, [rbp+0x300]=0x4803, not+add counter at [rbp+0x326], second feature flag store, call 0x675FB30 with [r13+0x648] and [rbp+0x6A8], third TLS feature flag store, sub/shrink/imul/dec counter stored at [rbp+0x342].

```
0x6779411  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779418  mov rax,[rcx]                                 
0x677941b  mov rax,[rax+0x10]                            
0x677941f  movzx edx,byte ptr [rbp+0x838]                
0x6779426  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677942c  nop                                           
0x677942d  mov eax,[r13+0x798]                           
0x6779434  not eax                                       
0x6779436  add eax,[r13+0x7A0]                           
0x677943d  mov [rbp+0x326],ax                            
0x6779444  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677944b  mov rax,[rcx]                                 
0x677944e  mov rax,[rax+0x10]                            
0x6779452  mov dl,0x4A                                   
0x6779454  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677945a  mov [rbp+0x838],al                            
0x6779460  lea rcx,[r13+0x648]                           
0x6779467  lea rdx,[rbp+0x6A8]                           
0x677946e  call 0x675FB30                                ; -> sub_675fb30
0x6779473  nop                                           
0x6779474  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677947b  mov rax,[rcx]                                 
0x677947e  mov rax,[rax+0x10]                            
0x6779482  movzx edx,byte ptr [rbp+0x838]                
0x6779489  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677948f  nop                                           
0x6779490  mov eax,[r13+0x650]                           
0x6779497  sub eax,[r13+0x648]                           
0x677949e  shr eax,3                                     
0x67794a1  imul eax,0xFFFF8E39                           
0x67794a7  dec eax                                       
0x67794a9  mov [rbp+0x342],ax                            
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x4803 (u64) — wait, no: actually [rbp+0x300] is NOT set in this phase. Let me re-check. Lines 399-431: there's no `mov qword ptr [rbp+0x300]` here. The [rbp+0x300]=0x4803 appears at phase 57 (0x67792ce) and phase 49/50/54. In phase 60 (0x6779411), the sequence is: TLS read, then directly `mov eax,[r13+0x798]` / not / add / [rbp+0x326]=ax. So no [rbp+0x300] store here.

Corrected interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r13+0x798], not eax, add eax,[r13+0x7A0], [rbp+0x326]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. `lea rcx,[r13+0x648]`, `lea rdx,[rbp+0x6A8]`, call 0x675FB30. Third TLS read, mov dl,0x4A, call via [0xF99FFA0]. Counter: eax=[r13+0x650], sub [r13+0x648], shr 3, imul 0xFFFF8E39, dec, [rbp+0x342]=ax.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, three times), 0x675FB30 (sub_675fb30).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x798], [r13+0x7A0], [r13+0x648], [r13+0x650]. Fields written: [rbp+0x326], [rbp+0x838], [rbp+0x342].

---

## Phase 61 — call 0x675F3B0 + mov qword [rbp+0x300] + sub/shr/imul/dec counter + TLS feature flag + mov r15 cmp je + store + call 0xE869FF0 + store + zero + add + jmp (0x67794b0..0x677955e)

`lea rcx,[r13+0x780]`, `lea rdx,[rbp+0x650]`, call 0x675F3B0, [rbp+0x300]=0x2005803, counter 2 at [rbp+0x328], TLS feature flag store, r15=[r13+0x770] bounds-check against [r13+0x778], on success store [rbp+0x5C8] at [r15], call 0xE869FF0, store [rbp+0x648] at [r15+0x80], zero [rbp+0x648], advance [r13+0x770] by 0x88, jump; otherwise grow path loc_67798aa.

```
0x67794b0  lea rcx,[r13+0x780]                           
0x67794b7  lea rdx,[rbp+0x650]                           
0x67794be  call 0x675F3B0                                ; -> sub_675f3b0
0x67794c3  nop                                           
0x67794c4  mov qword ptr [rbp+0x300],0x2005803           
0x67794cf  mov eax,[r13+0x788]                           
0x67794d6  sub eax,[r13+0x780]                           
0x67794dd  shr eax,3                                     
0x67794e0  imul eax,0xFFFF8BA3                           
0x67794e6  dec eax                                       
0x67794e8  mov [rbp+0x328],ax                            
0x67794ef  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67794f6  mov rax,[rcx]                                 
0x67794f9  mov rax,[rax+0x10]                            
0x67794fd  mov dl,0x4A                                   
0x67794ff  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779505  mov [rbp+0x838],al                            
0x677950b  mov r15,[r13+0x770]                           
0x6779512  cmp r15,[r13+0x778]                           
0x6779519  je 0x67798AA                                  ; -> loc_67798aa
0x677951f  mov rax,[rbp+0x5C8]                           
0x6779526  mov [r15],rax                                 
0x6779529  lea rcx,[r15+8]                               
0x677952d  lea rdx,[rbp+0x5D0]                           
0x6779534  call 0xE869FF0                                ; -> sub_e869ff0
0x6779539  nop                                           
0x677953a  mov rax,[rbp+0x648]                           
0x6779541  mov [r15+0x80],rax                            
0x6779548  mov qword ptr [rbp+0x648],0                   
0x6779553  add qword ptr [r13+0x770],0x88                
0x677955e  jmp 0x67798C1                                 ; -> loc_67798c1
```

Interpretation: `lea rcx,[r13+0x780]`, `lea rdx,[rbp+0x650]`, call 0x675F3B0. [rbp+0x300]=0x2005803 (u64). Counter 2: eax=[r13+0x788], sub [r13+0x780], shr 3, imul 0xFFFF8BA3, dec, [rbp+0x328]=ax. TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. r15=[r13+0x770]; cmp r15,[r13+0x778]; if equal jump to loc_67798aa (grow). Otherwise rax=[rbp+0x5C8], [r15]=rax; rcx=r15+8, rdx=&[rbp+0x5D0], call 0xE869FF0; rax=[rbp+0x648], [r15+0x80]=rax; [rbp+0x648]=0; [r13+0x770]+=0x88; jump to loc_67798c1.

Callees: 0x675F3B0 (sub_675f3b0), [0xF99FFA0] = sub_eea6040 (indirect), 0xE869FF0 (sub_e869ff0).
Fields read: [r13+0x780], [rbp+0x650], [r13+0x788], [r13+0x780], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x770], [r13+0x778], [rbp+0x5C8], [rbp+0x648]. Fields written: [rbp+0x300], [rbp+0x328], [rbp+0x838], [r15], [r15+0x80], [rbp+0x648], [r13+0x770].

## Phase 62 — Grow helper 0x6760710 + TLS read + counter + cursor check r14+0x68/0x70 (0x6779563..0x67795f3)

Grow helper call for [r14+0x768], TLS read, [rbp+0x300]=0x2007803, shr/imul/dec counter at [rbp+0x32A], second TLS read, feature flag store, then cursor [r14+0x68] vs [r14+0x70] with inc/jmp or grow path.

```
0x6779563  lea rcx,[r14+0x768]                           
0x677956a  mov rdx,r15                                   
0x677956d  lea r8,[rbp+0x578]                            
0x6779574  call 0x6760710                                ; -> sub_6760710
0x6779579  nop                                           
0x677957a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779581  mov rax,[rcx]                                 
0x6779584  mov rax,[rax+0x10]                            
0x6779588  movzx edx,byte ptr [rbp+0x838]                
0x677958f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779595  nop                                           
0x6779596  mov qword ptr [rbp+0x300],0x2007803           
0x67795a1  mov eax,[r14+0x770]                           
0x67795a8  sub eax,[r14+0x768]                           
0x67795af  shr eax,3                                     
0x67795b2  imul eax,0xFFFFF0F1                           
0x67795b8  dec eax                                       
0x67795ba  mov [rbp+0x32A],ax                            
0x67795c1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67795c8  mov rax,[rcx]                                 
0x67795cb  mov rax,[rax+0x10]                            
0x67795cf  mov dl,0x4A                                   
0x67795d1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67795d7  nop                                           
0x67795d8  mov [rbp+0x838],al                            
0x67795de  mov rdx,[r14+0x68]                            
0x67795e2  cmp rdx,[r14+0x70]                            
0x67795e6  je 0x6779961                                  ; -> loc_6779961
0x67795ec  inc rdx                                       
0x67795ef  mov [r14+0x68],rdx                            
0x67795f3  jmp 0x677996E                                 ; -> loc_677996e
```

Interpretation: `lea rcx,[r14+0x768]`, `mov rdx,r15`, `lea r8,[rbp+0x578]`, call 0x6760710 (grow helper). TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x2007803 (u64). Counter: eax=[r14+0x770], sub [r14+0x768], shr 3, imul 0xFFFFF0F1, dec, [rbp+0x32A]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x68], cmp [r14+0x70]; if equal jump to loc_6779961 (grow). Otherwise inc rdx, [r14+0x68]=rdx, jump to loc_677996e.

Callees: 0x6760710 (sub_6760710), [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [r14+0x768], r15, [rbp+0x578], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x770], [r14+0x768], [r14+0x68], [r14+0x70]. Fields written: [rbp+0x300], [rbp+0x32A], [rbp+0x838], [r14+0x68].

---

## Phase 63 — Grow path stub 0x6760710 at loc_67795f8 (0x67795f8..0x677960e)

Small grow-path stub reached from the failed bounds check in Phase 62 (je to loc_6779961).

```
0x67795f8  lea rcx,[r14+0x768]                           
0x67795ff  mov rdx,r15                                   
0x6779602  lea r8,[rbp+0x580]                            
0x6779609  call 0x6760710                                ; -> sub_6760710
0x677960e  nop                                           
```

Interpretation: `lea rcx,[r14+0x768]`, `mov rdx,r15`, `lea r8,[rbp+0x580]`, call 0x6760710 (grow helper).

Callees: 0x6760710 (sub_6760710).
Fields read: [r14+0x768], r15, [rbp+0x580]. Fields written: none.

---

## Phase 64 — TLS read + counter + cursor check r14+0x818/0x820 (0x677960f..0x6779691)

TLS reads, [rbp+0x300]=0x2007803, shr/imul/dec counter at [rbp+0x32A], second TLS read, feature flag store, then cursor [r14+0x818] vs [r14+0x820] with inc/jmp or grow path.

```
0x677960f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779616  mov rax,[rcx]                                 
0x6779619  mov rax,[rax+0x10]                            
0x677961d  movzx edx,byte ptr [rbp+0x838]                
0x6779624  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677962a  nop                                           
0x677962b  mov qword ptr [rbp+0x300],0x2007803           
0x6779636  mov eax,[r14+0x770]                           
0x677963d  sub eax,[r14+0x768]                           
0x6779644  shr eax,3                                     
0x6779647  imul eax,0xFFFFF0F1                           
0x677964d  dec eax                                       
0x677964f  mov [rbp+0x32A],ax                            
0x6779656  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677965d  mov rax,[rcx]                                 
0x6779660  mov rax,[rax+0x10]                            
0x6779664  mov dl,0x4A                                   
0x6779666  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677966c  nop                                           
0x677966d  mov [rbp+0x838],al                            
0x6779673  mov rdx,[r14+0x818]                           
0x677967a  cmp rdx,[r14+0x820]                           
0x6779681  je 0x67799EF                                  ; -> loc_67799ef
0x6779687  inc rdx                                       
0x677968a  mov [r14+0x818],rdx                           
0x6779691  jmp 0x67799FC                                 ; -> loc_67799fc
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x2007803 (u64). Counter: eax=[r14+0x770], sub [r14+0x768], shr 3, imul 0xFFFFF0F1, dec, [rbp+0x32A]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x818], cmp [r14+0x820]; if equal jump to loc_67799ef (grow). Otherwise inc rdx, [r14+0x818]=rdx, jump to loc_67799fc.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x770], [r14+0x768], [r14+0x818], [r14+0x820]. Fields written: [rbp+0x300], [rbp+0x32A], [rbp+0x838], [r14+0x818].

---

## Phase 65 — Grow path stub 0x6760710 at loc_6779696 (0x6779696..0x67796ac)

Small grow-path stub reached from the failed bounds check in Phase 64 (je to loc_67799ef).

```
0x6779696  lea rcx,[r14+0x768]                           
0x677969d  mov rdx,r15                                   
0x67796a0  lea r8,[rbp+0x580]                            
0x67796a7  call 0x6760710                                ; -> sub_6760710
0x67796ac  nop                                           
```

Interpretation: `lea rcx,[r14+0x768]`, `mov rdx,r15`, `lea r8,[rbp+0x580]`, call 0x6760710 (grow helper).

Callees: 0x6760710 (sub_6760710).
Fields read: [r14+0x768], r15, [rbp+0x580]. Fields written: none.

---

## Phase 66 — TLS read + counter + movss writes + cursor check r14+0x680/0x688 (0x67796ad..0x6779748)

TLS reads, [rbp+0x300]=0x2007803, shr/imul/dec counter at [rbp+0x32A], second TLS read, feature flag store, then cursor [r14+0x680] vs [r14+0x688] with movss writes (3x4 bytes) and add 0xC, or grow path.

```
0x67796ad  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67796b4  mov rax,[rcx]                                 
0x67796b7  mov rax,[rax+0x10]                            
0x67796bb  movzx edx,byte ptr [rbp+0x838]                
0x67796c2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67796c8  nop                                           
0x67796c9  mov eax,[r14+0x770]                           
0x67796d0  sub eax,[r14+0x768]                           
0x67796d7  shr eax,3                                     
0x67796da  imul eax,0xFFFFF0F1                           
0x67796e0  dec eax                                       
0x67796e2  mov [rbp+0x32A],ax                            
0x67796e9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67796f0  mov rax,[rcx]                                 
0x67796f3  mov rax,[rax+0x10]                            
0x67796f7  mov dl,0x4A                                   
0x67796f9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67796ff  nop                                           
0x6779700  mov [rbp+0x838],al                            
0x6779706  mov rdx,[r14+0x680]                           
0x677970d  cmp rdx,[r14+0x688]                           
0x6779714  je 0x6779A6F                                  ; -> loc_6779a6f
0x677971a  movss xmm0,[rbp+0x574]                        
0x6779722  movss [rdx],xmm0                              
0x6779726  movss xmm0,[rbp+0x578]                        
0x677972e  movss [rdx+4],xmm0                            
0x6779733  movss xmm0,[rbp+0x57C]                        
0x677973b  movss [rdx+8],xmm0                            
0x6779740  add qword ptr [r14+0x680],0xC                 
0x6779748  jmp 0x6779A83                                 ; -> loc_6779a83
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x2007803 (u64). Counter: eax=[r14+0x770], sub [r14+0x768], shr 3, imul 0xFFFFF0F1, dec, [rbp+0x32A]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x680], cmp [r14+0x688]; if equal jump to loc_6779a6f (grow). Otherwise movss [rdx]=xmm0[rbp+0x574], movss [rdx+4]=xmm0[rbp+0x578], movss [rdx+8]=xmm0[rbp+0x57C], [r14+0x680]+=0xC, jump to loc_6779a83.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x770], [r14+0x768], [rbp+0x574], [rbp+0x578], [rbp+0x57C], [r14+0x680], [r14+0x688]. Fields written: [rbp+0x300], [rbp+0x32A], [rbp+0x838], [rdx] (via movss x3), [r14+0x680].

---

## Phase 67 — Grow path stub 0x6760710 at loc_677974d (0x677974d..0x6779763)

Small grow-path stub reached from the failed bounds check in Phase 66 (je to loc_6779a6f).

```
0x677974d  lea rcx,[r14+0x768]                           
0x6779754  mov rdx,r15                                   
0x6779757  lea r8,[rbp+0x590]                            
0x677975e  call 0x6760710                                ; -> sub_6760710
0x6779763  nop                                           
```

Interpretation: `lea rcx,[r14+0x768]`, `mov rdx,r15`, `lea r8,[rbp+0x590]`, call 0x6760710 (grow helper).

Callees: 0x6760710 (sub_6760710).
Fields read: [r14+0x768], r15, [rbp+0x590]. Fields written: none.

---

## Phase 68 — TLS read + counter + movss writes + cursor check r14+0x680/0x688 (0x6779764..0x67797ff)

TLS reads, [rbp+0x300]=0x2007803, shr/imul/dec counter at [rbp+0x32A], second TLS read, feature flag store, then cursor [r14+0x680] vs [r14+0x688] with movss writes (3x4 bytes) and add 0xC, or grow path.

```
0x6779764  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677976b  mov rax,[rcx]                                 
0x677976e  mov rax,[rax+0x10]                            
0x6779772  movzx edx,byte ptr [rbp+0x838]                
0x6779779  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677977f  nop                                           
0x6779780  mov eax,[r14+0x770]                           
0x6779787  sub eax,[r14+0x768]                           
0x677978e  shr eax,3                                     
0x6779791  imul eax,0xFFFFF0F1                           
0x6779797  dec eax                                       
0x6779799  mov [rbp+0x32A],ax                            
0x67797a0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67797a7  mov rax,[rcx]                                 
0x67797aa  mov rax,[rax+0x10]                            
0x67797ae  mov dl,0x4A                                   
0x67797b0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67797b6  nop                                           
0x67797b7  mov [rbp+0x838],al                            
0x67797bd  mov rdx,[r14+0x680]                           
0x67797c4  cmp rdx,[r14+0x688]                           
0x67797cb  je 0x6779B01                                  ; -> loc_6779b01
0x67797d1  movss xmm0,[rbp+0x580]                        
0x67797d9  movss [rdx],xmm0                              
0x67797dd  movss xmm0,[rbp+0x584]                        
0x67797e5  movss [rdx+4],xmm0                            
0x67797ea  movss xmm0,[rbp+0x588]                        
0x67797f2  movss [rdx+8],xmm0                            
0x67797f7  add qword ptr [r14+0x680],0xC                 
0x67797ff  jmp 0x6779B15                                 ; -> loc_6779b15
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x2007803 (u64). Counter: eax=[r14+0x770], sub [r14+0x768], shr 3, imul 0xFFFFF0F1, dec, [rbp+0x32A]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x680], cmp [r14+0x688]; if equal jump to loc_6779b01 (grow). Otherwise movss [rdx]=xmm0[rbp+0x580], movss [rdx+4]=xmm0[rbp+0x584], movss [rdx+8]=xmm0[rbp+0x588], [r14+0x680]+=0xC, jump to loc_6779b15.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x770], [r14+0x768], [rbp+0x580], [rbp+0x584], [rbp+0x588], [r14+0x680], [r14+0x688]. Fields written: [rbp+0x300], [rbp+0x32A], [rbp+0x838], [rdx] (via movss x3), [r14+0x680].

---

## Phase 69 — Grow path stub 0x6760710 at loc_6779804 (0x6779804..0x677981a)

Small grow-path stub reached from the failed bounds check in Phase 68 (je to loc_6779b01).

```
0x6779804  lea rcx,[r13+0x768]                           
0x677980b  mov rdx,r15                                   
0x677980e  lea r8,[rbp+0x5B8]                            
0x6779815  call 0x6760710                                ; -> sub_6760710
0x677981a  nop                                           
```

Interpretation: `lea rcx,[r13+0x768]`, `mov rdx,r15`, `lea r8,[rbp+0x5B8]`, call 0x6760710 (grow helper).

Callees: 0x6760710 (sub_6760710).
Fields read: [r13+0x768], r15, [rbp+0x5B8]. Fields written: none.

---

## Phase 70 — TLS read + counter + cursor check r13+0x698/0x6A0 (0x677981b..0x67798a5)

TLS reads, [rbp+0x300]=0x2007803, shr/imul/dec counter at [rbp+0x32A], second TLS read, feature flag store, then cursor [r13+0x698] vs [r13+0x6A0] with u16 write and add 2, or grow path.

```
0x677981b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779822  mov rax,[rcx]                                 
0x6779825  mov rax,[rax+0x10]                            
0x6779829  movzx edx,byte ptr [rbp+0x838]                
0x6779830  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779836  nop                                           
0x6779837  mov qword ptr [rbp+0x300],0x2007803           
0x6779842  mov eax,[r13+0x770]                           
0x6779849  sub eax,[r13+0x768]                           
0x6779850  shr eax,3                                     
0x6779853  imul eax,0xFFFFF0F1                           
0x6779859  dec eax                                       
0x677985b  mov [rbp+0x32A],ax                            
0x6779862  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779869  mov rax,[rcx]                                 
0x677986c  mov rax,[rax+0x10]                            
0x6779870  mov dl,0x4A                                   
0x6779872  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779878  nop                                           
0x6779879  mov [rbp+0x838],al                            
0x677987f  mov rdx,[r13+0x698]                           
0x6779886  cmp rdx,[r13+0x6A0]                           
0x677988d  je 0x6779B9C                                  ; -> loc_6779b9c
0x6779893  movzx eax,word ptr [rbp+0x5B0]                
0x677989a  mov [rdx],ax                                  
0x677989d  add qword ptr [r13+0x698],2                   
0x67798a5  jmp 0x6779BB0                                 ; -> loc_6779bb0
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x2007803 (u64). Counter: eax=[r13+0x770], sub [r13+0x768], shr 3, imul 0xFFFFF0F1, dec, [rbp+0x32A]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r13+0x698], cmp [r13+0x6A0]; if equal jump to loc_6779b9c (grow). Otherwise movzx eax,word [rbp+0x5B0], [rdx]=ax (write u16), [r13+0x698]+=2, jump to loc_6779bb0.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x770], [r13+0x768], [rbp+0x5B0], [r13+0x698], [r13+0x6A0]. Fields written: [rbp+0x300], [rbp+0x32A], [rbp+0x838], [rdx] (u16 write), [r13+0x698].

---

## Phase 71 — Grow path stub 0x6760710 at loc_67798aa (0x67798aa..0x67798c0)

Small grow-path stub reached from the failed bounds check in Phase 70 (je to loc_6779b9c).

```
0x67798aa  lea rcx,[r13+0x768]                           
0x67798b1  mov rdx,r15                                   
0x67798b4  lea r8,[rbp+0x5C8]                            
0x67798bb  call 0x6760710                                ; -> sub_6760710
0x67798c0  nop                                           
```

Interpretation: `lea rcx,[r13+0x768]`, `mov rdx,r15`, `lea r8,[rbp+0x5C8]`, call 0x6760710 (grow helper).

Callees: 0x6760710 (sub_6760710).
Fields read: [r13+0x768], r15, [rbp+0x5C8]. Fields written: none.

---

## Phase 72 — TLS read + counter + movss writes + cursor check r13+0x680/0x688 (0x67798c1..0x677995c)

TLS reads, [rbp+0x300]=0x2007803, shr/imul/dec counter at [rbp+0x32A], second TLS read, feature flag store, then cursor [r13+0x680] vs [r13+0x688] with movss writes (3x4 bytes) and add 0xC, or grow path.

```
0x67798c1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67798c8  mov rax,[rcx]                                 
0x67798cb  mov rax,[rax+0x10]                            
0x67798cf  movzx edx,byte ptr [rbp+0x838]                
0x67798d6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67798dc  nop                                           
0x67798dd  mov eax,[r13+0x770]                           
0x67798e4  sub eax,[r13+0x768]                           
0x67798eb  shr eax,3                                     
0x67798ee  imul eax,0xFFFFF0F1                           
0x67798f4  dec eax                                       
0x67798f6  mov [rbp+0x32A],ax                            
0x67798fd  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779904  mov rax,[rcx]                                 
0x6779907  mov rax,[rax+0x10]                            
0x677990b  mov dl,0x4A                                   
0x677990d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779913  nop                                           
0x6779914  mov [rbp+0x838],al                            
0x677991a  mov rdx,[r13+0x680]                           
0x6779921  cmp rdx,[r13+0x688]                           
0x6779928  je 0x6779C2B                                  ; -> loc_6779c2b
0x677992e  movss xmm0,[rbp+0x5B8]                        
0x6779936  movss [rdx],xmm0                              
0x677993a  movss xmm0,[rbp+0x5BC]                        
0x6779942  movss [rdx+4],xmm0                            
0x6779947  movss xmm0,[rbp+0x5C0]                        
0x677994f  movss [rdx+8],xmm0                            
0x6779954  add qword ptr [r13+0x680],0xC                 
0x677995c  jmp 0x6779C3F                                 ; -> loc_6779c3f
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x2007803 (u64). Counter: eax=[r13+0x770], sub [r13+0x768], shr 3, imul 0xFFFFF0F1, dec, [rbp+0x32A]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r13+0x680], cmp [r13+0x688]; if equal jump to loc_6779c2b (grow). Otherwise movss [rdx]=xmm0[rbp+0x5B8], movss [rdx+4]=xmm0[rbp+0x5BC], movss [rdx+8]=xmm0[rbp+0x5C0], [r13+0x680]+=0xC, jump to loc_6779c3f.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x770], [r13+0x768], [rbp+0x5B8], [rbp+0x5BC], [rbp+0x5C0], [r13+0x680], [r13+0x688]. Fields written: [rbp+0x300], [rbp+0x32A], [rbp+0x838], [rdx] (via movss x3), [r13+0x680].

---

## Phase 73 — Grow path stub 0x6760E60 at loc_6779961 (0x6779961..0x677996d)

Small grow-path stub reached from the failed bounds check in Phase 62 (je to loc_6779961). Uses r14+0x60 grow target.

```
0x6779961  mov rcx,r14                                   
0x6779964  add rcx,0x60                                  
0x6779968  call 0x6760E60                                ; -> sub_6760e60
0x677996d  nop                                           
```

Interpretation: `mov rcx,r14`, `add rcx,0x60`, call 0x6760E60 (grow helper).

Callees: 0x6760E60 (sub_6760e60).
Fields read: r14. Fields written: none.

---

## Phase 74 — TLS read + feature flag + counter + shared_ptr push + cursor check (0x677996e..0x67799ea)

TLS reads, [rbp+0x308]=0x1000000, not/add counter at [rbp+0x3C0], second TLS read, feature flag store, then cursor [r14+8] vs [r14+0x10] with shared_ptr push call 0xEEC6EC0 and add 0xC8, or grow path.

```
0x677996e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779975  mov rax,[rcx]                                 
0x6779978  mov rax,[rax+0x10]                            
0x677997c  movzx edx,byte ptr [rbp+0x838]                
0x6779983  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779989  nop                                           
0x677998a  mov qword ptr [rbp+0x308],0x1000000           
0x6779995  mov eax,[r14+0x60]                            
0x6779999  not eax                                       
0x677999b  add eax,[r14+0x68]                            
0x677999f  mov [rbp+0x3C0],ax                            
0x67799a6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x67799ad  mov rax,[rcx]                                 
0x67799b0  mov rax,[rax+0x10]                            
0x67799b4  mov dl,0x4A                                   
0x67799b6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x67799bc  nop                                           
0x67799bd  mov [rbp+0x838],al                            
0x67799c3  mov rdx,[r14+8]                               
0x67799c7  cmp rdx,[r14+0x10]                            
0x67799cb  je 0x6779CCE                                  ; -> loc_6779cce
0x67799d1  mov r8d,0xC8                                  
0x67799d7  mov rcx,rdx                                   
0x67799da  mov rdx,r13                                   
0x67799dd  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x67799e2  add qword ptr [r14+8],0xC8                    
0x67799ea  jmp 0x6779CDA                                 ; -> loc_6779cda
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x308]=0x1000000 (u64). Counter: eax=[r14+0x60], not eax, add eax,[r14+0x68], [rbp+0x3C0]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+8], cmp [r14+0x10]; if equal jump to loc_6779cce (grow). Otherwise r8d=0xC8, rcx=rdx, rdx=r13, call 0xEEC6EC0, [r14+8]+=0xC8, jump to loc_6779cda.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x60], [r14+0x68], [r14+8], [r14+0x10], r13. Fields written: [rbp+0x308], [rbp+0x3C0], [rbp+0x838], [r14+8].

---

## Phase 75 — Grow path stub 0x6760E60 at loc_67799ef (0x67799ef..0x67799fb)

Small grow-path stub reached from the failed bounds check in Phase 64 (je to loc_67799ef).

```
0x67799ef  lea rcx,[r14+0x810]                           
0x67799f6  call 0x6760E60                                ; -> sub_6760e60
0x67799fb  nop                                           
```

Interpretation: `lea rcx,[r14+0x810]`, call 0x6760E60 (grow helper).

Callees: 0x6760E60 (sub_6760e60).
Fields read: [r14+0x810]. Fields written: none.

---

## Phase 76 — TLS read + feature flag + counter + cursor check r14+0x368/0x370 (0x67799fc..0x6779a6a)

TLS reads, not/add counter at [rbp+0x31C], second TLS read, feature flag store, then cursor [r14+0x368] vs [r14+0x370] with inc/jmp or grow path.

```
0x67799fc  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779a03  mov rax,[rcx]                                 
0x6779a06  mov rax,[rax+0x10]                            
0x6779a0a  movzx edx,byte ptr [rbp+0x838]                
0x6779a11  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779a17  nop                                           
0x6779a18  mov eax,[r14+0x810]                           
0x6779a1f  not eax                                       
0x6779a21  add eax,[r14+0x818]                           
0x6779a28  mov [rbp+0x31C],ax                            
0x6779a2f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779a36  mov rax,[rcx]                                 
0x6779a39  mov rax,[rax+0x10]                            
0x6779a3d  mov dl,0x4A                                   
0x6779a3f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779a45  nop                                           
0x6779a46  mov [rbp+0x838],al                            
0x6779a4c  mov rdx,[r14+0x368]                           
0x6779a53  cmp rdx,[r14+0x370]                           
0x6779a5a  je 0x6779D0A                                  ; -> loc_6779d0a
0x6779a60  inc rdx                                       
0x6779a63  mov [r14+0x368],rdx                           
0x6779a6a  jmp 0x6779D17                                 ; -> loc_6779d17
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r14+0x810], not eax, add eax,[r14+0x818], [rbp+0x31C]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x368], cmp [r14+0x370]; if equal jump to loc_6779d0a (grow). Otherwise inc rdx, [r14+0x368]=rdx, jump to loc_6779d17.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x810], [r14+0x818], [r14+0x368], [r14+0x370]. Fields written: [rbp+0x31C], [rbp+0x838], [r14+0x368].

---

## Phase 77 — Grow path stub call 0x1770A70 at loc_6779a6f (0x6779a6f..0x6779a82)

Small grow-path stub reached from the failed bounds check in Phase 66 (je to loc_6779a6f).

```
0x6779a6f  lea rcx,[r14+0x678]                           
0x6779a76  lea r8,[rbp+0x574]                            
0x6779a7d  call 0x1770A70                                ; -> sub_1770a70
0x6779a82  nop                                           
```

Interpretation: `lea rcx,[r14+0x678]`, `lea r8,[rbp+0x574]`, call 0x1770A70 (sub_1770a70).

Callees: 0x1770A70 (sub_1770a70).
Fields read: [r14+0x678], [rbp+0x574]. Fields written: none.

---

## Phase 78 — TLS read + counter + cursor check r14+0x68/0x70 (0x6779a83..0x6779afc)

TLS reads, [rbp+0x300]=0x2807803, shr2/imul/dec counter at [rbp+0x33E], second TLS read, feature flag store, then cursor [r14+0x68] vs [r14+0x70] with inc/jmp or grow path.

```
0x6779a83  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779a8a  mov rax,[rcx]                                 
0x6779a8d  mov rax,[rax+0x10]                            
0x6779a91  movzx edx,byte ptr [rbp+0x838]                
0x6779a98  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779a9e  nop                                           
0x6779a9f  mov qword ptr [rbp+0x300],0x2807803           
0x6779aaa  mov eax,[r14+0x680]                           
0x6779ab1  sub eax,[r14+0x678]                           
0x6779ab8  shr eax,2                                     
0x6779abb  imul eax,0xFFFFAAAB                           
0x6779ac1  dec eax                                       
0x6779ac3  mov [rbp+0x33E],ax                            
0x6779aca  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779ad1  mov rax,[rcx]                                 
0x6779ad4  mov rax,[rax+0x10]                            
0x6779ad8  mov dl,0x4A                                   
0x6779ada  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779ae0  nop                                           
0x6779ae1  mov [rbp+0x838],al                            
0x6779ae7  mov rdx,[r14+0x68]                            
0x6779aeb  cmp rdx,[r14+0x70]                            
0x6779aef  je 0x6779DA3                                  ; -> loc_6779da3
0x6779af5  inc rdx                                       
0x6779af8  mov [r14+0x68],rdx                            
0x6779afc  jmp 0x6779DB0                                 ; -> loc_6779db0
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x2807803 (u64). Counter: eax=[r14+0x680], sub [r14+0x678], shr 2, imul 0xFFFFAAAB, dec, [rbp+0x33E]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x68], cmp [r14+0x70]; if equal jump to loc_6779da3 (grow). Otherwise inc rdx, [r14+0x68]=rdx, jump to loc_6779db0.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x680], [r14+0x678], [r14+0x68], [r14+0x70]. Fields written: [rbp+0x300], [rbp+0x33E], [rbp+0x838], [r14+0x68].

---

## Phase 79 — Grow path stub call 0x1770A70 at loc_6779b01 (0x6779b01..0x6779b14)

Small grow-path stub reached from the failed bounds check in Phase 68 (je to loc_6779b01).

```
0x6779b01  lea rcx,[r14+0x678]                           
0x6779b08  lea r8,[rbp+0x580]                            
0x6779b0f  call 0x1770A70                                ; -> sub_1770a70
0x6779b14  nop                                           
```

Interpretation: `lea rcx,[r14+0x678]`, `lea r8,[rbp+0x580]`, call 0x1770A70 (sub_1770a70).

Callees: 0x1770A70 (sub_1770a70).
Fields read: [r14+0x678], [rbp+0x580]. Fields written: none.

---

## Phase 80 — TLS read + counter + cursor check r14+0x818/0x820 (0x6779b15..0x6779b97)

TLS reads, [rbp+0x300]=0x2807803, shr2/imul/dec counter at [rbp+0x33E], second TLS read, feature flag store, then cursor [r14+0x818] vs [r14+0x820] with inc/jmp or grow path.

```
0x6779b15  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779b1c  mov rax,[rcx]                                 
0x6779b1f  mov rax,[rax+0x10]                            
0x6779b23  movzx edx,byte ptr [rbp+0x838]                
0x6779b2a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779b30  nop                                           
0x6779b31  mov qword ptr [rbp+0x300],0x2807803           
0x6779b3c  mov eax,[r14+0x680]                           
0x6779b43  sub eax,[r14+0x678]                           
0x6779b4a  shr eax,2                                     
0x6779b4d  imul eax,0xFFFFAAAB                           
0x6779b53  dec eax                                       
0x6779b55  mov [rbp+0x33E],ax                            
0x6779b5c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779b63  mov rax,[rcx]                                 
0x6779b66  mov rax,[rax+0x10]                            
0x6779b6a  mov dl,0x4A                                   
0x6779b6c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779b72  nop                                           
0x6779b73  mov [rbp+0x838],al                            
0x6779b79  mov rdx,[r14+0x818]                           
0x6779b80  cmp rdx,[r14+0x820]                           
0x6779b87  je 0x6779E31                                  ; -> loc_6779e31
0x6779b8d  inc rdx                                       
0x6779b90  mov [r14+0x818],rdx                           
0x6779b97  jmp 0x6779E3E                                 ; -> loc_6779e3e
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x2807803 (u64). Counter: eax=[r14+0x680], sub [r14+0x678], shr 2, imul 0xFFFFAAAB, dec, [rbp+0x33E]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x818], cmp [r14+0x820]; if equal jump to loc_6779e31 (grow). Otherwise inc rdx, [r14+0x818]=rdx, jump to loc_6779e3e.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x680], [r14+0x678], [r14+0x818], [r14+0x820]. Fields written: [rbp+0x300], [rbp+0x33E], [rbp+0x838], [r14+0x818].

---

## Phase 81 — Grow path stub call 0x1EF6F90 at loc_6779b9c (0x6779b9c..0x6779baf)

Small grow-path stub reached from the failed bounds check in Phase 70 (je to loc_6779b9c).

```
0x6779b9c  lea rcx,[r13+0x690]                           
0x6779ba3  lea r8,[rbp+0x5B0]                            
0x6779baa  call 0x1EF6F90                                ; -> sub_1ef6f90
0x6779baf  nop                                           
```

Interpretation: `lea rcx,[r13+0x690]`, `lea r8,[rbp+0x5B0]`, call 0x1EF6F90 (sub_1ef6f90).

Callees: 0x1EF6F90 (sub_1ef6f90).
Fields read: [r13+0x690], [rbp+0x5B0]. Fields written: none.

---

## Phase 82 — TLS read + feature flag + counter + cursor check r13+0x638/0x640 (0x6779bb0..0x6779c26)

TLS reads, shr1/dec counter at [rbp+0x33C], second TLS read, feature flag store, then cursor [r13+0x638] vs [r13+0x640] with u32 write and add 4, or grow path.

```
0x6779bb0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779bb7  mov rax,[rcx]                                 
0x6779bba  mov rax,[rax+0x10]                            
0x6779bbe  movzx edx,byte ptr [rbp+0x838]                
0x6779bc5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779bcb  nop                                           
0x6779bcc  mov eax,[r13+0x698]                           
0x6779bd3  sub eax,[r13+0x690]                           
0x6779bda  shr eax,1                                     
0x6779bdc  dec eax                                       
0x6779bde  mov [rbp+0x33C],ax                            
0x6779be5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779bec  mov rax,[rcx]                                 
0x6779bef  mov rax,[rax+0x10]                            
0x6779bf3  mov dl,0x4A                                   
0x6779bf5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779bfb  nop                                           
0x6779bfc  mov [rbp+0x838],al                            
0x6779c02  mov rdx,[r13+0x638]                           
0x6779c09  cmp rdx,[r13+0x640]                           
0x6779c10  je 0x6779EB1                                  ; -> loc_6779eb1
0x6779c16  mov eax,[rbp+0x5A8]                           
0x6779c1c  mov [rdx],eax                                 
0x6779c1e  add qword ptr [r13+0x638],4                   
0x6779c26  jmp 0x6779EC5                                 ; -> loc_6779ec5
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r13+0x698], sub [r13+0x690], shr 1, dec, [rbp+0x33C]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r13+0x638], cmp [r13+0x640]; if equal jump to loc_6779eb1 (grow). Otherwise eax=[rbp+0x5A8], [rdx]=eax (write u32), [r13+0x638]+=4, jump to loc_6779ec5.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x698], [r13+0x690], [rbp+0x5A8], [r13+0x638], [r13+0x640]. Fields written: [rbp+0x33C], [rbp+0x838], [rdx] (u32 write), [r13+0x638].

---

## Phase 83 — Grow path stub call 0x1770A70 at loc_6779c2b (0x6779c2b..0x6779c3e)

Small grow-path stub reached from the failed bounds check in Phase 72 (je to loc_6779c2b).

```
0x6779c2b  lea rcx,[r13+0x678]                           
0x6779c32  lea r8,[rbp+0x5B8]                            
0x6779c39  call 0x1770A70                                ; -> sub_1770a70
0x6779c3e  nop                                           
```

Interpretation: `lea rcx,[r13+0x678]`, `lea r8,[rbp+0x5B8]`, call 0x1770A70 (sub_1770a70).

Callees: 0x1770A70 (sub_1770a70).
Fields read: [r13+0x678], [rbp+0x5B8]. Fields written: none.

---

## Phase 84 — TLS read + counter + cursor check r13+0x698/0x6A0 (0x6779c3f..0x6779cc9)

TLS reads, [rbp+0x300]=0x2807803, shr2/imul/dec counter at [rbp+0x33E], second TLS read, feature flag store, then cursor [r13+0x698] vs [r13+0x6A0] with u16 write and add 2, or grow path.

```
0x6779c3f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779c46  mov rax,[rcx]                                 
0x6779c49  mov rax,[rax+0x10]                            
0x6779c4d  movzx edx,byte ptr [rbp+0x838]                
0x6779c54  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779c5a  nop                                           
0x6779c5b  mov qword ptr [rbp+0x300],0x2807803           
0x6779c66  mov eax,[r13+0x680]                           
0x6779c6d  sub eax,[r13+0x678]                           
0x6779c74  shr eax,2                                     
0x6779c77  imul eax,0xFFFFAAAB                           
0x6779c7d  dec eax                                       
0x6779c7f  mov [rbp+0x33E],ax                            
0x6779c86  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779c8d  mov rax,[rcx]                                 
0x6779c90  mov rax,[rax+0x10]                            
0x6779c94  mov dl,0x4A                                   
0x6779c96  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779c9c  nop                                           
0x6779c9d  mov [rbp+0x838],al                            
0x6779ca3  mov rdx,[r13+0x698]                           
0x6779caa  cmp rdx,[r13+0x6A0]                           
0x6779cb1  je 0x6779F91                                  ; -> loc_6779f91
0x6779cb7  movzx eax,word ptr [rbp+0x5B0]                
0x6779cbe  mov [rdx],ax                                  
0x6779cc1  add qword ptr [r13+0x698],2                   
0x6779cc9  jmp 0x6779FA5                                 ; -> loc_6779fa5
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x2807803 (u64). Counter: eax=[r13+0x680], sub [r13+0x678], shr 2, imul 0xFFFFAAAB, dec, [rbp+0x33E]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r13+0x698], cmp [r13+0x6A0]; if equal jump to loc_6779f91 (grow). Otherwise movzx eax,word [rbp+0x5B0], [rdx]=ax (write u16), [r13+0x698]+=2, jump to loc_6779fa5.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x680], [r13+0x678], [rbp+0x5B0], [r13+0x698], [r13+0x6A0]. Fields written: [rbp+0x300], [rbp+0x33E], [rbp+0x838], [rdx] (u16 write), [r13+0x698].

---

## Phase 85 — Grow path stub call 0x5ABA6D0 at loc_6779cce (0x6779cce..0x6779cd9)

Small grow-path stub reached from the failed bounds check in Phase 74 (je to loc_6779cce).

```
0x6779cce  mov rcx,r14                                   
0x6779cd1  mov r8,r13                                    
0x6779cd4  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x6779cd9  nop                                           
```

Interpretation: `mov rcx,r14`, `mov r8,r13`, call 0x5ABA6D0 (sub_5aba6d0).

Callees: 0x5ABA6D0 (sub_5aba6d0).
Fields read: r14, r13. Fields written: none.

---

## Phase 86 — TLS read + call 0x67E1840 + jmp 0x677DEA0 at loc_6779cda (0x6779cda..0x6779d05)

TLS read, feature flag store, then call 0x67E1840 with rcx=r12, lea rcx,[rbp+0x110], jmp to 0x677DEA0.

```
0x6779cda  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779ce1  mov rax,[rcx]                                 
0x6779ce4  mov rax,[rax+0x10]                            
0x6779ce8  movzx edx,byte ptr [rbp+0x838]                
0x6779cef  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779cf5  nop                                           
0x6779cf6  mov rcx,r12                                   
0x6779cf9  call 0x67E1840                                ; -> sub_67e1840
0x6779cfe  lea rcx,[rbp+0x110]                           
0x6779d05  jmp 0x677DEA0                                 ; -> sub_677dea0
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Then mov rcx,r12, call 0x67E1840, lea rcx,[rbp+0x110], jmp 0x677DEA0.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x67E1840 (sub_67e1840), 0x677DEA0 (sub_677dea0, via jmp).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], r12, [rbp+0x110]. Fields written: [rbp+0x838].

---

## Phase 87 — Grow path stub 0x6760E60 at loc_6779d0a (0x6779d0a..0x6779d16)

Small grow-path stub reached from the failed bounds check in Phase 76 (je to loc_6779d0a).

```
0x6779d0a  lea rcx,[r14+0x360]                           
0x6779d11  call 0x6760E60                                ; -> sub_6760e60
0x6779d16  nop                                           
```

Interpretation: `lea rcx,[r14+0x360]`, call 0x6760E60 (grow helper).

Callees: 0x6760E60 (sub_6760e60).
Fields read: [r14+0x360]. Fields written: none.

---

## Phase 88 — TLS read + feature flag + counter + cursor check r14+0x698/0x6A0 (0x6779d17..0x6779d9e)

TLS reads, rax=0x100000002007843 stored at [rbp+0x300], not/add counter at [rbp+0x380], second TLS read, feature flag store, then cursor [r14+0x698] vs [r14+0x6A0] with u16 write and add 2, or grow path.

```
0x6779d17  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779d1e  mov rax,[rcx]                                 
0x6779d21  mov rax,[rax+0x10]                            
0x6779d25  movzx edx,byte ptr [rbp+0x838]                
0x6779d2c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779d32  nop                                           
0x6779d33  mov rax,0x100000002007843                     
0x6779d3d  mov [rbp+0x300],rax                           
0x6779d44  mov eax,[r14+0x360]                           
0x6779d4b  not eax                                       
0x6779d4d  add eax,[r14+0x368]                           
0x6779d54  mov [rbp+0x380],ax                            
0x6779d5b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779d62  mov rax,[rcx]                                 
0x6779d65  mov rax,[rax+0x10]                            
0x6779d69  mov dl,0x4A                                   
0x6779d6b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779d71  nop                                           
0x6779d72  mov [rbp+0x838],al                            
0x6779d78  mov rdx,[r14+0x698]                           
0x6779d7f  cmp rdx,[r14+0x6A0]                           
0x6779d86  je 0x677A020                                  ; -> loc_677a020
0x6779d8c  movzx eax,word ptr [rbp+0x574]                
0x6779d93  mov [rdx],ax                                  
0x6779d96  add qword ptr [r14+0x698],2                   
0x6779d9e  jmp 0x677A034                                 ; -> loc_677a034
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. rax=0x100000002007843, [rbp+0x300]=rax (u64). Counter: eax=[r14+0x360], not eax, add eax,[r14+0x368], [rbp+0x380]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x698], cmp [r14+0x6A0]; if equal jump to loc_677a020 (grow). Otherwise movzx eax,word [rbp+0x574], [rdx]=ax (write u16), [r14+0x698]+=2, jump to loc_677a034.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x360], [r14+0x368], [rbp+0x574], [r14+0x698], [r14+0x6A0]. Fields written: [rbp+0x300], [rbp+0x380], [rbp+0x838], [rdx] (u16 write), [r14+0x698].

---

## Phase 89 — Grow path stub 0x6760E60 at loc_6779da3 (0x6779da3..0x6779daf)

Small grow-path stub reached from the failed bounds check in Phase 78 (je to loc_6779da3).

```
0x6779da3  mov rcx,r14                                   
0x6779da6  add rcx,0x60                                  
0x6779daa  call 0x6760E60                                ; -> sub_6760e60
0x6779daf  nop                                           
```

Interpretation: `mov rcx,r14`, `add rcx,0x60`, call 0x6760E60 (grow helper).

Callees: 0x6760E60 (sub_6760e60).
Fields read: r14. Fields written: none.

---

## Phase 90 — TLS read + feature flag + counter + shared_ptr push + cursor check (0x6779db0..0x6779e2c)

TLS reads, [rbp+0x308]=0x1000000, not/add counter at [rbp+0x3C0], second TLS read, feature flag store, then cursor [r14+8] vs [r14+0x10] with shared_ptr push call 0xEEC6EC0 and add 0xC8, or grow path.

```
0x6779db0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779db7  mov rax,[rcx]                                 
0x6779dba  mov rax,[rax+0x10]                            
0x6779dbe  movzx edx,byte ptr [rbp+0x838]                
0x6779dc5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779dcb  nop                                           
0x6779dcc  mov qword ptr [rbp+0x308],0x1000000           
0x6779dd7  mov eax,[r14+0x60]                            
0x6779ddb  not eax                                       
0x6779ddd  add eax,[r14+0x68]                            
0x6779de1  mov [rbp+0x3C0],ax                            
0x6779de8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779def  mov rax,[rcx]                                 
0x6779df2  mov rax,[rax+0x10]                            
0x6779df6  mov dl,0x4A                                   
0x6779df8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779dfe  nop                                           
0x6779dff  mov [rbp+0x838],al                            
0x6779e05  mov rdx,[r14+8]                               
0x6779e09  cmp rdx,[r14+0x10]                            
0x6779e0d  je 0x677A0AF                                  ; -> loc_677a0af
0x6779e13  mov r8d,0xC8                                  
0x6779e19  mov rcx,rdx                                   
0x6779e1c  mov rdx,r13                                   
0x6779e1f  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x6779e24  add qword ptr [r14+8],0xC8                    
0x6779e2c  jmp 0x677A0BB                                 ; -> loc_677a0bb
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x308]=0x1000000 (u64). Counter: eax=[r14+0x60], not eax, add eax,[r14+0x68], [rbp+0x3C0]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+8], cmp [r14+0x10]; if equal jump to loc_677a0af (grow). Otherwise r8d=0xC8, rcx=rdx, rdx=r13, call 0xEEC6EC0, [r14+8]+=0xC8, jump to loc_677a0bb.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x60], [r14+0x68], [r14+8], [r14+0x10], r13. Fields written: [rbp+0x308], [rbp+0x3C0], [rbp+0x838], [r14+8].

---

## Phase 91 — Grow path stub 0x6760E60 at loc_6779e31 (0x6779e31..0x6779e3d)

Small grow-path stub reached from the failed bounds check in Phase 80 (je to loc_6779e31).

```
0x6779e31  lea rcx,[r14+0x810]                           
0x6779e38  call 0x6760E60                                ; -> sub_6760e60
0x6779e3d  nop                                           
```

Interpretation: `lea rcx,[r14+0x810]`, call 0x6760E60 (grow helper).

Callees: 0x6760E60 (sub_6760e60).
Fields read: [r14+0x810]. Fields written: none.

---

## Phase 92 — TLS read + feature flag + counter + cursor check r14+0x368/0x370 (0x6779e3e..0x6779eac)

TLS reads, not/add counter at [rbp+0x31C], second TLS read, feature flag store, then cursor [r14+0x368] vs [r14+0x370] with inc/jmp or grow path.

```
0x6779e3e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779e45  mov rax,[rcx]                                 
0x6779e48  mov rax,[rax+0x10]                            
0x6779e4c  movzx edx,byte ptr [rbp+0x838]                
0x6779e53  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779e59  nop                                           
0x6779e5a  mov eax,[r14+0x810]                           
0x6779e61  not eax                                       
0x6779e63  add eax,[r14+0x818]                           
0x6779e6a  mov [rbp+0x31C],ax                            
0x6779e71  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779e78  mov rax,[rcx]                                 
0x6779e7b  mov rax,[rax+0x10]                            
0x6779e7f  mov dl,0x4A                                   
0x6779e81  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779e87  nop                                           
0x6779e88  mov [rbp+0x838],al                            
0x6779e8e  mov rdx,[r14+0x368]                           
0x6779e95  cmp rdx,[r14+0x370]                           
0x6779e9c  je 0x677A0E4                                  ; -> loc_677a0e4
0x6779ea2  inc rdx                                       
0x6779ea5  mov [r14+0x368],rdx                           
0x6779eac  jmp 0x677A0F1                                 ; -> loc_677a0f1
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r14+0x810], not eax, add eax,[r14+0x818], [rbp+0x31C]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x368], cmp [r14+0x370]; if equal jump to loc_677a0e4 (grow). Otherwise inc rdx, [r14+0x368]=rdx, jump to loc_677a0f1.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x810], [r14+0x818], [r14+0x368], [r14+0x370]. Fields written: [rbp+0x31C], [rbp+0x838], [r14+0x368].

---

## Phase 93 — Grow path stub 0x6760E60 at loc_6779eb1 (0x6779eb1..0x6779ec4)

Small grow-path stub reached from the failed bounds check in Phase 82 (je to loc_6779eb1).

```
0x6779eb1  lea rcx,[r13+0x630]                           
0x6779eb8  lea r8,[rbp+0x5A8]                            
0x6779ebf  call 0x14DB710                                ; -> sub_14db710
0x6779ec4  nop                                           
```

Interpretation: `lea rcx,[r13+0x630]`, `lea r8,[rbp+0x5A8]`, call 0x14DB710 (sub_14db710).

Callees: 0x14DB710 (sub_14db710).
Fields read: [r13+0x630], [rbp+0x5A8]. Fields written: none.

---

## Phase 94 — TLS read + feature flag + counter + call + cursor check r13+8/0x10 (0x6779ec5..0x6779f8c)

TLS reads, [rbp+0x300]=0x6407803, shr2/dec counter at [rbp+0x344], call 0x67693F0, [rbp+0x308]=0x20000, shr3/imul/dec counter at [rbp+0x3B2], second TLS read, feature flag store, then cursor [r13+8] vs [r13+0x10] with shared_ptr push call 0xEEC6EC0 and add 0xC8, or grow path.

```
0x6779ec5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779ecc  mov rax,[rcx]                                 
0x6779ecf  mov rax,[rax+0x10]                            
0x6779ed3  movzx edx,byte ptr [rbp+0x838]                
0x6779eda  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779ee0  nop                                           
0x6779ee1  mov qword ptr [rbp+0x300],0x6407803           
0x6779eec  mov eax,[r13+0x638]                           
0x6779ef3  sub eax,[r13+0x630]                           
0x6779efa  shr eax,2                                     
0x6779efd  dec eax                                       
0x6779eff  mov [rbp+0x344],ax                            
0x6779f06  mov rcx,r13                                   
0x6779f09  add rcx,0x108                                 
0x6779f10  mov rdx,r12                                   
0x6779f13  call 0x67693F0                                ; -> sub_67693f0
0x6779f18  nop                                           
0x6779f19  mov qword ptr [rbp+0x308],0x20000             
0x6779f24  mov eax,[r13+0x110]                           
0x6779f2b  sub eax,[r13+0x108]                           
0x6779f32  shr eax,3                                     
0x6779f35  imul eax,0x6DB7                               
0x6779f3b  dec eax                                       
0x6779f3d  mov [rbp+0x3B2],ax                            
0x6779f44  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779f4b  mov rax,[rcx]                                 
0x6779f4e  mov rax,[rax+0x10]                            
0x6779f52  mov dl,0x4A                                   
0x6779f54  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779f5a  nop                                           
0x6779f5b  mov [rbp+0x838],al                            
0x6779f61  mov rdx,[r13+8]                               
0x6779f65  cmp rdx,[r13+0x10]                            
0x6779f69  je 0x677A17D                                  ; -> loc_677a17d
0x6779f6f  mov r8d,0xC8                                  
0x6779f75  mov rcx,rdx                                   
0x6779f78  lea rdx,[rbp+0x300]                           
0x6779f7f  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x6779f84  add qword ptr [r13+8],0xC8                    
0x6779f8c  jmp 0x677A18D                                 ; -> loc_677a18d
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x6407803 (u64). Counter: eax=[r13+0x638], sub [r13+0x630], shr 2, dec, [rbp+0x344]=ax. rcx=r13+0x108, rdx=r12, call 0x67693F0. [rbp+0x308]=0x20000 (u64). Counter: eax=[r13+0x110], sub [r13+0x108], shr 3, imul 0x6DB7, dec, [rbp+0x3B2]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r13+8], cmp [r13+0x10]; if equal jump to loc_677a17d (grow). Otherwise r8d=0xC8, rcx=rdx, rdx=&[rbp+0x300], call 0xEEC6EC0, [r13+8]+=0xC8, jump to loc_677a18d.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x67693F0 (sub_67693f0), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x638], [r13+0x630], r13, r12, [r13+0x108], [r13+0x110], [r13+8], [r13+0x10]. Fields written: [rbp+0x300], [rbp+0x344], [rbp+0x308], [rbp+0x3B2], [rbp+0x838], [r13+8].

---

## Phase 95 — Grow path stub call 0x1EF6F90 at loc_6779f91 (0x6779f91..0x6779fa4)

Small grow-path stub reached from the failed bounds check in Phase 84 (je to loc_6779f91).

```
0x6779f91  lea rcx,[r13+0x690]                           
0x6779f98  lea r8,[rbp+0x5B0]                            
0x6779f9f  call 0x1EF6F90                                ; -> sub_1ef6f90
0x6779fa4  nop                                           
```

Interpretation: `lea rcx,[r13+0x690]`, `lea r8,[rbp+0x5B0]`, call 0x1EF6F90 (sub_1ef6f90).

Callees: 0x1EF6F90 (sub_1ef6f90).
Fields read: [r13+0x690], [rbp+0x5B0]. Fields written: none.

---

## Phase 96 — TLS read + feature flag + counter + cursor check r13+0x638/0x640 (0x6779fa5..0x677a01b)

TLS reads, shr1/dec counter at [rbp+0x33C], second TLS read, feature flag store, then cursor [r13+0x638] vs [r13+0x640] with u32 write and add 4, or grow path.

```
0x6779fa5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779fac  mov rax,[rcx]                                 
0x6779faf  mov rax,[rax+0x10]                            
0x6779fb3  movzx edx,byte ptr [rbp+0x838]                
0x6779fba  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779fc0  nop                                           
0x6779fc1  mov eax,[r13+0x698]                           
0x6779fc8  sub eax,[r13+0x690]                           
0x6779fcf  shr eax,1                                     
0x6779fd1  dec eax                                       
0x6779fd3  mov [rbp+0x33C],ax                            
0x6779fda  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x6779fe1  mov rax,[rcx]                                 
0x6779fe4  mov rax,[rax+0x10]                            
0x6779fe8  mov dl,0x4A                                   
0x6779fea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x6779ff0  nop                                           
0x6779ff1  mov [rbp+0x838],al                            
0x6779ff7  mov rdx,[r13+0x638]                           
0x6779ffe  cmp rdx,[r13+0x640]                           
0x677a005  je 0x677A226                                  ; -> loc_677a226
0x677a00b  mov eax,[rbp+0x5A8]                           
0x677a011  mov [rdx],eax                                 
0x677a013  add qword ptr [r13+0x638],4                   
0x677a01b  jmp 0x677A23A                                 ; -> loc_677a23a
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r13+0x698], sub [r13+0x690], shr 1, dec, [rbp+0x33C]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r13+0x638], cmp [r13+0x640]; if equal jump to loc_677a226 (grow). Otherwise eax=[rbp+0x5A8], [rdx]=eax (write u32), [r13+0x638]+=4, jump to loc_677a23a.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x698], [r13+0x690], [rbp+0x5A8], [r13+0x638], [r13+0x640]. Fields written: [rbp+0x33C], [rbp+0x838], [rdx] (u32 write), [r13+0x638].

---

## Phase 97 — Grow path stub call 0x1EF6F90 at loc_677a020 (0x677a020..0x677a033)

Small grow-path stub reached from the failed bounds check in Phase 88 (je to loc_677a020).

```
0x677a020  lea rcx,[r14+0x690]                           
0x677a027  lea r8,[rbp+0x574]                            
0x677a02e  call 0x1EF6F90                                ; -> sub_1ef6f90
0x677a033  nop                                           
```

Interpretation: `lea rcx,[r14+0x690]`, `lea r8,[rbp+0x574]`, call 0x1EF6F90 (sub_1ef6f90).

Callees: 0x1EF6F90 (sub_1ef6f90).
Fields read: [r14+0x690], [rbp+0x574]. Fields written: none.

---

## Phase 98 — TLS read + feature flag + counter + cursor check r14+0x638/0x640 (0x677a034..0x677a0aa)

TLS reads, shr1/dec counter at [rbp+0x33C], second TLS read, feature flag store, then cursor [r14+0x638] vs [r14+0x640] with u32 write and add 4, or grow path.

```
0x677a034  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a03b  mov rax,[rcx]                                 
0x677a03e  mov rax,[rax+0x10]                            
0x677a042  movzx edx,byte ptr [rbp+0x838]                
0x677a049  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a04f  nop                                           
0x677a050  mov eax,[r14+0x698]                           
0x677a057  sub eax,[r14+0x690]                           
0x677a05e  shr eax,1                                     
0x677a060  dec eax                                       
0x677a062  mov [rbp+0x33C],ax                            
0x677a069  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a070  mov rax,[rcx]                                 
0x677a073  mov rax,[rax+0x10]                            
0x677a077  mov dl,0x4A                                   
0x677a079  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a07f  nop                                           
0x677a080  mov [rbp+0x838],al                            
0x677a086  mov rdx,[r14+0x638]                           
0x677a08d  cmp rdx,[r14+0x640]                           
0x677a094  je 0x677A306                                  ; -> loc_677a306
0x677a09a  mov eax,[rbp+0x570]                           
0x677a0a0  mov [rdx],eax                                 
0x677a0a2  add qword ptr [r14+0x638],4                   
0x677a0aa  jmp 0x677A319                                 ; -> loc_677a319
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r14+0x698], sub [r14+0x690], shr 1, dec, [rbp+0x33C]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x638], cmp [r14+0x640]; if equal jump to loc_677a306 (grow). Otherwise eax=[rbp+0x570], [rdx]=eax (write u32), [r14+0x638]+=4, jump to loc_677a319.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x698], [r14+0x690], [rbp+0x570], [r14+0x638], [r14+0x640]. Fields written: [rbp+0x33C], [rbp+0x838], [rdx] (u32 write), [r14+0x638].

---

## Phase 99 — Grow path stub call 0x5ABA6D0 at loc_677a0af (0x677a0af..0x677a0ba)

Small grow-path stub reached from the failed bounds check in Phase 90 (je to loc_677a0af).

```
0x677a0af  mov rcx,r14                                   
0x677a0b2  mov r8,r13                                    
0x677a0b5  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x677a0ba  nop                                           
```

Interpretation: `mov rcx,r14`, `mov r8,r13`, call 0x5ABA6D0 (sub_5aba6d0).

Callees: 0x5ABA6D0 (sub_5aba6d0).
Fields read: r14, r13. Fields written: none.

---

## Phase 100 — TLS read + call 0x67E1660 + jmp 0x677B130 at loc_677a0bb (0x677a0bb..0x677a0df)

TLS read, feature flag store, then call 0x67E1660 with rcx=r12, jmp to 0x677B130.

```
0x677a0bb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a0c2  mov rax,[rcx]                                 
0x677a0c5  mov rax,[rax+0x10]                            
0x677a0c9  movzx edx,byte ptr [rbp+0x838]                
0x677a0d0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a0d6  nop                                           
0x677a0d7  mov rcx,r12                                   
0x677a0da  call 0x67E1660                                ; -> sub_67e1660
0x677a0df  jmp 0x677B130                                 ; -> loc_677b130
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Then mov rcx,r12, call 0x67E1660, jmp 0x677B130.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x67E1660 (sub_67e1660), 0x677B130 (loc_677b130, via jmp).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], r12. Fields written: [rbp+0x838].

---

## Phase 101 — Grow path stub 0x6760E60 at loc_677a0e4 (0x677a0e4..0x677a0f0)

Small grow-path stub reached from the failed bounds check in Phase 92 (je to loc_677a0e4).

```
0x677a0e4  lea rcx,[r14+0x360]                           
0x677a0eb  call 0x6760E60                                ; -> sub_6760e60
0x677a0f0  nop                                           
```

Interpretation: `lea rcx,[r14+0x360]`, call 0x6760E60 (grow helper).

Callees: 0x6760E60 (sub_6760e60).
Fields read: [r14+0x360]. Fields written: none.

---

## Phase 102 — TLS read + feature flag + counter + cursor check r14+0x698/0x6A0 (0x677a0f1..0x677a178)

TLS reads, rax=0x100000002807843 stored at [rbp+0x300], not/add counter at [rbp+0x380], second TLS read, feature flag store, then cursor [r14+0x698] vs [r14+0x6A0] with u16 write and add 2, or grow path.

```
0x677a0f1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a0f8  mov rax,[rcx]                                 
0x677a0fb  mov rax,[rax+0x10]                            
0x677a0ff  movzx edx,byte ptr [rbp+0x838]                
0x677a106  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a10c  nop                                           
0x677a10d  mov rax,0x100000002807843                     
0x677a117  mov [rbp+0x300],rax                           
0x677a11e  mov eax,[r14+0x360]                           
0x677a125  not eax                                       
0x677a127  add eax,[r14+0x368]                           
0x677a12e  mov [rbp+0x380],ax                            
0x677a135  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a13c  mov rax,[rcx]                                 
0x677a13f  mov rax,[rax+0x10]                            
0x677a143  mov dl,0x4A                                   
0x677a145  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a14b  nop                                           
0x677a14c  mov [rbp+0x838],al                            
0x677a152  mov rdx,[r14+0x698]                           
0x677a159  cmp rdx,[r14+0x6A0]                           
0x677a160  je 0x677A3A9                                  ; -> loc_677a3a9
0x677a166  movzx eax,word ptr [rbp+0x574]                
0x677a16d  mov [rdx],ax                                  
0x677a170  add qword ptr [r14+0x698],2                   
0x677a178  jmp 0x677A3BD                                 ; -> loc_677a3bd
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. rax=0x100000002807843, [rbp+0x300]=rax (u64). Counter: eax=[r14+0x360], not eax, add eax,[r14+0x368], [rbp+0x380]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x698], cmp [r14+0x6A0]; if equal jump to loc_677a3a9 (grow). Otherwise movzx eax,word [rbp+0x574], [rdx]=ax (write u16), [r14+0x698]+=2, jump to loc_677a3bd.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x360], [r14+0x368], [rbp+0x574], [r14+0x698], [r14+0x6A0]. Fields written: [rbp+0x300], [rbp+0x380], [rbp+0x838], [rdx] (u16 write), [r14+0x698].

---

## Phase 103 — Grow path stub call 0x5ABA6D0 at loc_677a17d (0x677a17d..0x677a18c)

Small grow-path stub reached from the failed bounds check in Phase 94 (je to loc_677a17d).

```
0x677a17d  mov rcx,r13                                   
0x677a180  lea r8,[rbp+0x300]                            
0x677a187  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x677a18c  nop                                           
```

Interpretation: `mov rcx,r13`, `lea r8,[rbp+0x300]`, call 0x5ABA6D0 (sub_5aba6d0).

Callees: 0x5ABA6D0 (sub_5aba6d0).
Fields read: r13, [rbp+0x300]. Fields written: none.

---

## Phase 104 — TLS read + heap metadata check + calls + test/jmp (0x677a18d..0x677a221)

TLS read, feature flag store, then cmp byte [rbp+0x6D8],1 (jne to loc_677a204), rcx=[rbp+0x698] (test rcx,rcx; je to loc_677a204), rdx=[rbp+0x6A8], sub rdx,rcx, cmp rdx,0x1000 (jb to loc_677a1ed), mov rax,[rcx-8], add rcx,0xFFFFFFFFFFFFFFF8, sub rcx,rax, cmp rcx,0x20 (jae to 0x677E039), or rdx,0x27, mov rcx,rax. loc_677a1ed: call 0xE935700, lea rax,[rbp+0x698], movups [rax],xmm6, mov qword [rax+0x10],0. loc_677a204: mov rcx,r12, call 0x6791DD0, lea rcx,[rbp+0x110], call 0x67E23F0, test r14,r14, jne 0x677A514, jmp 0x677A541.

```
0x677a18d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a194  mov rax,[rcx]                                 
0x677a197  mov rax,[rax+0x10]                            
0x677a19b  movzx edx,byte ptr [rbp+0x838]                
0x677a1a2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a1a8  nop                                           
0x677a1a9  cmp byte ptr [rbp+0x6D8],1                    
0x677a1b0  jne short 0x677A204                           ; -> loc_677a204
0x677a1b2  mov rcx,[rbp+0x698]                           
0x677a1b9  test rcx,rcx                                  
0x677a1bc  je short 0x677A204                            ; -> loc_677a204
0x677a1be  mov rdx,[rbp+0x6A8]                           
0x677a1c5  sub rdx,rcx                                   
0x677a1c8  cmp rdx,0x1000                                
0x677a1cf  jb short 0x677A1ED                            ; -> loc_677a1ed
0x677a1d1  mov rax,[rcx-8]                               
0x677a1d5  add rcx,0xFFFFFFFFFFFFFFF8                    
0x677a1d9  sub rcx,rax                                   
0x677a1dc  cmp rcx,0x20                                  
0x677a1e0  jae 0x677E039                                 ; -> sub_677e039
0x677a1e6  or rdx,0x27                                   
0x677a1ea  mov rcx,rax                                   
0x677a1ed  call 0xE935700                                ; -> sub_e935700
0x677a1f2  lea rax,[rbp+0x698]                           
0x677a1f9  movups [rax],xmm6                             
0x677a1fc  mov qword ptr [rax+0x10],0                    
0x677a204  mov rcx,r12                                   
0x677a207  call 0x6791DD0                                ; -> sub_6791dd0
0x677a20c  lea rcx,[rbp+0x110]                           
0x677a213  call 0x67E23F0                                ; -> sub_67e23f0
0x677a218  test r14,r14                                  
0x677a21b  jne 0x677A514                                 ; -> loc_677a514
0x677a221  jmp 0x677A541                                 ; -> loc_677a541
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Then cmp byte [rbp+0x6D8],1; if not equal jump to loc_677a204. rcx=[rbp+0x698]; test rcx,rcx; if zero jump to loc_677a204. rdx=[rbp+0x6A8], rdx-=rcx, cmp rdx,0x1000; if below jump to loc_677a1ed. mov rax,[rcx-8], add rcx,0xFFFFFFFFFFFFFFF8, sub rcx,rax, cmp rcx,0x20; if above or equal jump to 0x677E039. Otherwise or rdx,0x27, mov rcx,rax. loc_677a1ed: call 0xE935700, lea rax,[rbp+0x698], movups [rax],xmm6 (zero 16 bytes), mov qword [rax+0x10],0. loc_677a204: mov rcx,r12, call 0x6791DD0, lea rcx,[rbp+0x110], call 0x67E23F0, test r14,r14; if not equal jump to loc_677a514, otherwise jmp 0x677A541.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0xE935700 (sub_e935700), 0x6791DD0 (sub_6791dd0), 0x67E23F0 (sub_67e23f0), 0x677E039 (sub_677e039, via jae), 0x677A514 (loc_677a514, via jne), 0x677A541 (loc_677a541, via jmp).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [rbp+0x6D8], [rbp+0x698], [rbp+0x6A8], [rcx-8], r12, r14. Fields written: [rbp+0x838], [rax] (movups xmm6), [rax+0x10].

---

## Phase 105 — Grow path stub call 0x14DB710 at loc_677a226 (0x677a226..0x677a239)

Small grow-path stub reached from the failed bounds check in Phase 96 (je to loc_677a226).

```
0x677a226  lea rcx,[r13+0x630]                           
0x677a22d  lea r8,[rbp+0x5A8]                            
0x677a234  call 0x14DB710                                ; -> sub_14db710
0x677a239  nop                                           
```

Interpretation: `lea rcx,[r13+0x630]`, `lea r8,[rbp+0x5A8]`, call 0x14DB710 (sub_14db710).

Callees: 0x14DB710 (sub_14db710).
Fields read: [r13+0x630], [rbp+0x5A8]. Fields written: none.

---

## Phase 106 — TLS read + feature flag + counter + call + cursor check r13+8/0x10 (0x677a23a..0x677a301)

TLS reads, [rbp+0x300]=0x6C07803, shr2/dec counter at [rbp+0x344], call 0x67693F0, [rbp+0x308]=0x20000, shr3/imul/dec counter at [rbp+0x3B2], second TLS read, feature flag store, then cursor [r13+8] vs [r13+0x10] with shared_ptr push call 0xEEC6EC0 and add 0xC8, or grow path.

```
0x677a23a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a241  mov rax,[rcx]                                 
0x677a244  mov rax,[rax+0x10]                            
0x677a248  movzx edx,byte ptr [rbp+0x838]                
0x677a24f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a255  nop                                           
0x677a256  mov qword ptr [rbp+0x300],0x6C07803           
0x677a261  mov eax,[r13+0x638]                           
0x677a268  sub eax,[r13+0x630]                           
0x677a26f  shr eax,2                                     
0x677a272  dec eax                                       
0x677a274  mov [rbp+0x344],ax                            
0x677a27b  mov rcx,r13                                   
0x677a27e  add rcx,0x108                                 
0x677a285  mov rdx,r12                                   
0x677a288  call 0x67693F0                                ; -> sub_67693f0
0x677a28d  nop                                           
0x677a28e  mov qword ptr [rbp+0x308],0x20000             
0x677a299  mov eax,[r13+0x110]                           
0x677a2a0  sub eax,[r13+0x108]                           
0x677a2a7  shr eax,3                                     
0x677a2aa  imul eax,0x6DB7                               
0x677a2b0  dec eax                                       
0x677a2b2  mov [rbp+0x3B2],ax                            
0x677a2b9  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a2c0  mov rax,[rcx]                                 
0x677a2c3  mov rax,[rax+0x10]                            
0x677a2c7  mov dl,0x4A                                   
0x677a2c9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a2cf  nop                                           
0x677a2d0  mov [rbp+0x838],al                            
0x677a2d6  mov rdx,[r13+8]                               
0x677a2da  cmp rdx,[r13+0x10]                            
0x677a2de  je 0x677A474                                  ; -> loc_677a474
0x677a2e4  mov r8d,0xC8                                  
0x677a2ea  mov rcx,rdx                                   
0x677a2ed  lea rdx,[rbp+0x300]                           
0x677a2f4  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x677a2f9  add qword ptr [r13+8],0xC8                    
0x677a301  jmp 0x677A484                                 ; -> loc_677a484
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. [rbp+0x300]=0x6C07803 (u64). Counter: eax=[r13+0x638], sub [r13+0x630], shr 2, dec, [rbp+0x344]=ax. rcx=r13+0x108, rdx=r12, call 0x67693F0. [rbp+0x308]=0x20000 (u64). Counter: eax=[r13+0x110], sub [r13+0x108], shr 3, imul 0x6DB7, dec, [rbp+0x3B2]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r13+8], cmp [r13+0x10]; if equal jump to loc_677a474 (grow). Otherwise r8d=0xC8, rcx=rdx, rdx=&[rbp+0x300], call 0xEEC6EC0, [r13+8]+=0xC8, jump to loc_677a484.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0x67693F0 (sub_67693f0), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r13+0x638], [r13+0x630], r13, r12, [r13+0x108], [r13+0x110], [r13+8], [r13+0x10]. Fields written: [rbp+0x300], [rbp+0x344], [rbp+0x308], [rbp+0x3B2], [rbp+0x838], [r13+8].

---

## Phase 107 — Grow path stub call 0x14DB710 at loc_677a306 (0x677a306..0x677a318)

Small grow-path stub reached from the failed bounds check in Phase 98 (je to loc_677a306).

```
0x677a306  mov rcx,r14                                   
0x677a309  add rcx,0x630                                 
0x677a310  mov r8,r12                                    
0x677a313  call 0x14DB710                                ; -> sub_14db710
0x677a318  nop                                           
```

Interpretation: `mov rcx,r14`, `add rcx,0x630`, `mov r8,r12`, call 0x14DB710 (sub_14db710).

Callees: 0x14DB710 (sub_14db710).
Fields read: r14, r12. Fields written: none.

---

## Phase 108 — TLS read + feature flag + counter + cursor check r14+8/0x10 (0x677a319..0x677a3a4)

TLS reads, rax=0x100000006407843 stored at [rbp+0x300], shr2/dec counter at [rbp+0x344], second TLS read, feature flag store, then cursor [r14+8] vs [r14+0x10] with shared_ptr push call 0xEEC6EC0 and add 0xC8, or grow path.

```
0x677a319  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a320  mov rax,[rcx]                                 
0x677a323  mov rax,[rax+0x10]                            
0x677a327  movzx edx,byte ptr [rbp+0x838]                
0x677a32e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a334  nop                                           
0x677a335  mov rax,0x100000006407843                     
0x677a33f  mov [rbp+0x300],rax                           
0x677a346  mov eax,[r14+0x638]                           
0x677a34d  sub eax,[r14+0x630]                           
0x677a354  shr eax,2                                     
0x677a357  dec eax                                       
0x677a359  mov [rbp+0x344],ax                            
0x677a360  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a367  mov rax,[rcx]                                 
0x677a36a  mov rax,[rax+0x10]                            
0x677a36e  mov dl,0x4A                                   
0x677a370  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a376  nop                                           
0x677a377  mov [rbp+0x838],al                            
0x677a37d  mov rdx,[r14+8]                               
0x677a381  cmp rdx,[r14+0x10]                            
0x677a385  je 0x677A438                                  ; -> loc_677a438
0x677a38b  mov r8d,0xC8                                  
0x677a391  mov rcx,rdx                                   
0x677a394  mov rdx,r13                                   
0x677a397  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x677a39c  add qword ptr [r14+8],0xC8                    
0x677a3a4  jmp 0x677A444                                 ; -> loc_677a444
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. rax=0x100000006407843, [rbp+0x300]=rax (u64). Counter: eax=[r14+0x638], sub [r14+0x630], shr 2, dec, [rbp+0x344]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+8], cmp [r14+0x10]; if equal jump to loc_677a438 (grow). Otherwise r8d=0xC8, rcx=rdx, rdx=r13, call 0xEEC6EC0, [r14+8]+=0xC8, jump to loc_677a444.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice), 0xEEC6EC0 (sub_eec6ec0).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x638], [r14+0x630], [r14+8], [r14+0x10], r13. Fields written: [rbp+0x300], [rbp+0x344], [rbp+0x838], [r14+8].

---

## Phase 109 — Grow path stub call 0x1EF6F90 at loc_677a3a9 (0x677a3a9..0x677a3bc)

Small grow-path stub reached from the failed bounds check in Phase 102 (je to loc_677a3a9).

```
0x677a3a9  lea rcx,[r14+0x690]                           
0x677a3b0  lea r8,[rbp+0x574]                            
0x677a3b7  call 0x1EF6F90                                ; -> sub_1ef6f90
0x677a3bc  nop                                           
```

Interpretation: `lea rcx,[r14+0x690]`, `lea r8,[rbp+0x574]`, call 0x1EF6F90 (sub_1ef6f90).

Callees: 0x1EF6F90 (sub_1ef6f90).
Fields read: [r14+0x690], [rbp+0x574]. Fields written: none.

---

## Phase 110 — TLS read + feature flag + counter + cursor check r14+0x638/0x640 (0x677a3bd..0x677a433)

TLS reads, shr1/dec counter at [rbp+0x33C], second TLS read, feature flag store, then cursor [r14+0x638] vs [r14+0x640] with u32 write and add 4, or grow path.

```
0x677a3bd  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a3c4  mov rax,[rcx]                                 
0x677a3c7  mov rax,[rax+0x10]                            
0x677a3cb  movzx edx,byte ptr [rbp+0x838]                
0x677a3d2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a3d8  nop                                           
0x677a3d9  mov eax,[r14+0x698]                           
0x677a3e0  sub eax,[r14+0x690]                           
0x677a3e7  shr eax,1                                     
0x677a3e9  dec eax                                       
0x677a3eb  mov [rbp+0x33C],ax                            
0x677a3f2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a3f9  mov rax,[rcx]                                 
0x677a3fc  mov rax,[rax+0x10]                            
0x677a400  mov dl,0x4A                                   
0x677a402  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a408  nop                                           
0x677a409  mov [rbp+0x838],al                            
0x677a40f  mov rdx,[r14+0x638]                           
0x677a416  cmp rdx,[r14+0x640]                           
0x677a41d  je 0x677A643                                  ; -> loc_677a643
0x677a423  mov eax,[rbp+0x570]                           
0x677a429  mov [rdx],eax                                 
0x677a42b  add qword ptr [r14+0x638],4                   
0x677a433  jmp 0x677A656                                 ; -> loc_677a656
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r14+0x698], sub [r14+0x690], shr 1, dec, [rbp+0x33C]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x638], cmp [r14+0x640]; if equal jump to loc_677a643 (grow). Otherwise eax=[rbp+0x570], [rdx]=eax (write u32), [r14+0x638]+=4, jump to loc_677a656.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, twice).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x698], [r14+0x690], [rbp+0x570], [r14+0x638], [r14+0x640]. Fields written: [rbp+0x33C], [rbp+0x838], [rdx] (u32 write), [r14+0x638].

---

## Phase 111 — Grow path stub call 0x5ABA6D0 at loc_677a438 (0x677a438..0x677a443)

Small grow-path stub reached from the failed bounds check in Phase 108 (je to loc_677a438).

```
0x677a438  mov rcx,r14                                   
0x677a43b  mov r8,r13                                    
0x677a43e  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x677a443  nop                                           
```

Interpretation: `mov rcx,r14`, `mov r8,r13`, call 0x5ABA6D0 (sub_5aba6d0).

Callees: 0x5ABA6D0 (sub_5aba6d0).
Fields read: r14, r13. Fields written: none.

---

## Phase 112 — TLS read + call 0x67E1660 + jmp 0x677DEA0 at loc_677a444 (0x677a444..0x677a46f)

TLS read, feature flag store, then call 0x67E1660 with rcx=r12, lea rcx,[rbp+0x110], jmp to 0x677DEA0.

```
0x677a444  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a44b  mov rax,[rcx]                                 
0x677a44e  mov rax,[rax+0x10]                            
0x677a452  movzx edx,byte ptr [rbp+0x838]                
0x677a459  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a45f  nop                                           
0x677a460  mov rcx,r12                                   
0x677a463  call 0x67E1660                                ; -> sub_67e1660
0x677a468  lea rcx,[rbp+0x110]                           
0x677a46f  jmp 0x677DEA0                                 ; -> sub_677dea0
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Then mov rcx,r12, call 0x67E1660, lea rcx,[rbp+0x110], jmp 0x677DEA0.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), 0x67E1660 (sub_67e1660), 0x677DEA0 (sub_677dea0, via jmp).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], r12, [rbp+0x110]. Fields written: [rbp+0x838].

---

## Phase 113 — Grow path stub call 0x5ABA6D0 at loc_677a474 (0x677a474..0x677a483)

Small grow-path stub reached from the failed bounds check in Phase 106 (je to loc_677a474).

```
0x677a474  mov rcx,r13                                   
0x677a477  lea r8,[rbp+0x300]                            
0x677a47e  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x677a483  nop                                           
```

Interpretation: `mov rcx,r13`, `lea r8,[rbp+0x300]`, call 0x5ABA6D0 (sub_5aba6d0).

Callees: 0x5ABA6D0 (sub_5aba6d0).
Fields read: r13, [rbp+0x300]. Fields written: none.

---

## Phase 114 — TLS read + heap metadata check (partial) (0x677a484..0x677a4d0)

TLS read, feature flag store, then cmp byte [rbp+0x6E8],1 (jne to loc_677a4fb), rcx=[rbp+0x6A8] (test rcx,rcx; je to loc_677a4fb), rdx=[rbp+0x6B8], sub rdx,rcx, cmp rdx,0x1000 (jb to loc_677a4e4), mov rax,[rcx-8], add rcx,0xFFFFFFFFFFFFFFF8, sub rcx,rax. (Range ends at 0x677a4d0; next instruction at 0x677a4d4.)

```
0x677a484  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a48b  mov rax,[rcx]                                 
0x677a48e  mov rax,[rax+0x10]                            
0x677a492  movzx edx,byte ptr [rbp+0x838]                
0x677a499  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a49f  nop                                           
0x677a4a0  cmp byte ptr [rbp+0x6E8],1                    
0x677a4a7  jne short 0x677A4FB                           ; -> loc_677a4fb
0x677a4a9  mov rcx,[rbp+0x6A8]                           
0x677a4b0  test rcx,rcx                                  
0x677a4b3  je short 0x677A4FB                            ; -> loc_677a4fb
0x677a4b5  mov rdx,[rbp+0x6B8]                           
0x677a4bc  sub rdx,rcx                                   
0x677a4bf  cmp rdx,0x1000                                
0x677a4c6  jb short 0x677A4E4                            ; -> loc_677a4e4
0x677a4c8  mov rax,[rcx-8]                               
0x677a4cc  add rcx,0xFFFFFFFFFFFFFFF8                    
0x677a4d0  sub rcx,rax                                   
```

Interpretation: TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Then cmp byte [rbp+0x6E8],1; if not equal jump to loc_677a4fb. rcx=[rbp+0x6A8]; test rcx,rcx; if zero jump to loc_677a4fb. rdx=[rbp+0x6B8], rdx-=rcx, cmp rdx,0x1000; if below jump to loc_677a4e4. mov rax,[rcx-8], add rcx,0xFFFFFFFFFFFFFFF8, sub rcx,rax. Range ends at 0x677a4d0 (instruction #800); next instruction is at 0x677a4d4.

Callees: [0xF99FFA0] = sub_eea6040 (indirect).
Fields read: [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [rbp+0x6E8], [rbp+0x6A8], [rbp+0x6B8], [rcx-8]. Fields written: [rbp+0x838].

---

## NEXT
Resume at 0x677a4d4 (Phase 115) — after `sub rcx,rax` at 0x677a4d0, before `cmp ecx,0x20` at 0x677a4d4. Covered 0x6779563..0x677a4d0 (Phases 62-114, 800 instructions).

---




