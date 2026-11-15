# U-E4-F4: Chunk builder at 0x67762e0 — continuation of U-E4-F3

Unit: U-E4-F4
Function: sub_67762e0 (chunk builder, called by chunk extractor 0x66ea3d0) — continuation
RVAs: 0x677a4d4 .. (chunks of 40 instructions from 0x677a4d4)
Source: `rdis dis 0x677a4d4 40` etc. on Minecraft.Windows.exe 1.26.62.01
Tags: [V] = seen in disassembly, [I] = inferred, [?] = unknown

## Phase 115 — Heap metadata jae + shared_ptr clear + call 0x6791730 + call 0x67E1660 + double refcount-decrement/destructor (0x677a4d4..0x677a574)

cmp/jump on heap-size field, clear shared_ptr slot at [rbp+0x6A8], then two intrusive-refcount release sequences (r14, then r14=[rbp+0x4A8]) each doing lock-dec/[r14+8], destructor call via [0xF99FFA0] when count hits 0, then lock-dec/[r14+0xC].

```
0x677a4d4  cmp ecx,0x20                                  
0x677a4d7  jae 0x677E039                                 ; -> sub_677e039
0x677a4dd  or rdx,0x27                                   
0x677a4e1  mov rcx,rax                                   
0x677a4e4  call 0xE935700                                ; -> sub_e935700
0x677a4e9  lea rax,[rbp+0x6A8]                           
0x677a4f0  movups [rax],xmm6                             
0x677a4f3  mov qword ptr [rax+0x10],0                    
0x677a4fb  mov rcx,r12                                   
0x677a4fe  call 0x6791730                                ; -> sub_6791730
0x677a503  lea rcx,[rbp+0x110]                           
0x677a50a  call 0x67E1660                                ; -> sub_67e1660
0x677a50f  test r14,r14                                  
0x677a512  je short 0x677A541                            ; -> loc_677a541
0x677a514  lock dec dword ptr [r14+8]                    
0x677a519  jne short 0x677A541                           ; -> loc_677a541
0x677a51b  mov rax,[r14]                                 
0x677a51e  mov rax,[rax]                                 
0x677a521  mov rcx,r14                                   
0x677a524  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a52a  lock dec dword ptr [r14+0xC]                  
0x677a52f  jne short 0x677A541                           ; -> loc_677a541
0x677a531  mov rax,[r14]                                 
0x677a534  mov rax,[rax+8]                               
0x677a538  mov rcx,r14                                   
0x677a53b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a541  mov r14,[rbp+0x4A8]                           
0x677a548  test r14,r14                                  
0x677a54b  je short 0x677A57A                            ; -> loc_677a57a
0x677a54d  lock dec dword ptr [r14+8]                    
0x677a552  jne short 0x677A57A                           ; -> loc_677a57a
0x677a554  mov rax,[r14]                                 
0x677a557  mov rax,[rax]                                 
0x677a55a  mov rcx,r14                                   
0x677a55d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a563  lock dec dword ptr [r14+0xC]                  
0x677a568  jne short 0x677A57A                           ; -> loc_677a57a
0x677a56a  mov rax,[r14]                                 
0x677a56d  mov rax,[rax+8]                               
0x677a571  mov rcx,r14                                   
```

Interpretation: `cmp ecx,0x20`; if above/equal jump to 0x677E039 (the heap-metadata path also reached from 0x677a1e0). Otherwise `or rdx,0x27`, `mov rcx,rax`, call 0xE935700 (free). Then `lea rax,[rbp+0x6A8]`, `movups [rax],xmm6` (zero 16 bytes at [rbp+0x6A8]), `mov qword ptr [rax+0x10],0` ([rbp+0x6B8]=0 — clear shared_ptr slot). `mov rcx,r12`, call 0x6791730, `lea rcx,[rbp+0x110]`, call 0x67E1660, `test r14,r14`; if zero jump to loc_677a541. Release sequence for object r14: `lock dec dword ptr [r14+8]`; if result != 0 jump to loc_677a541 (next object), else run destructor: `mov rax,[r14]`, `mov rax,[rax]`, `mov rcx,r14`, call via [0xF99FFA0] (vtable+0), then `lock dec dword ptr [r14+0xC]`; if != 0 jump to loc_677a541, else second destructor call: `mov rax,[r14]`, `mov rax,[rax+8]`, `mov rcx,r14`, call via [0xF99FFA0] (vtable+8). loc_677a541: `r14=[rbp+0x4A8]`; `test r14,r14`; if zero jump to loc_677a57a; else repeat same release sequence for this second object (`lock dec [r14+8]` → jne loc_677a57A; else vtable+0 destructor; `lock dec [r14+0xC]` → jne loc_677a57A; else vtable+8 destructor). Range ends at `mov rcx,r14` (0x677a571); next instruction at 0x677a574.

Callees: 0xE935700 (sub_e935700), 0x6791730 (sub_6791730), 0x67E1660 (sub_67e1660), [0xF99FFA0] = sub_eea6040 (indirect, 3x: vtable+0 for r14, vtable+8 for r14, vtable+0 for r14=[rbp+0x4A8]).
Fields read: ecx, rdx, rax, [rbp+0x6A8] (lea), r12, [rbp+0x110], r14, [r14+8], [r14], [rax], [r14+0xC], [rax+8], [rbp+0x4A8] (second object pointer), then again [r14+8], [r14], [rax], [r14+0xC], [rax+8]. Fields written: [rbp+0x6A8] (movups 16-byte zero), [rbp+0x6B8] (qword 0 via [rax+0x10]), [r14+8] (lock dec), [r14+0xC] (lock dec), [r14+8] (second object), [r14+0xC] (second object).

## Phase 116 — Triple refcount-decrement/destructor sequences (r14=[rbp+0x7D8], [rbp+0x7C8], [rbp+0x788]) (0x677a574..0x677a616)

Three more shared_ptr release sequences: for r14 loaded from [rbp+0x7D8] (jumps to loc_677a5b3 on non-zero), then [rbp+0x7C8] (jumps to loc_677a5ec), then [rbp+0x788] (jumps to loc_677b13c). Each: lock-dec [r14+8]; if != 0 skip destructor; else vtable+0 call via [0xF99FFA0]; lock-dec [r14+0xC]; if != 0 skip; else vtable+8 call via [0xF99FFA0].

```
0x677a574  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a57a  mov r14,[rbp+0x7D8]                           
0x677a581  test r14,r14                                  
0x677a584  je short 0x677A5B3                            ; -> loc_677a5b3
0x677a586  lock dec dword ptr [r14+8]                    
0x677a58b  jne short 0x677A5B3                           ; -> loc_677a5b3
0x677a58d  mov rax,[r14]                                 
0x677a590  mov rax,[rax]                                 
0x677a593  mov rcx,r14                                   
0x677a596  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a59c  lock dec dword ptr [r14+0xC]                  
0x677a5a1  jne short 0x677A5B3                           ; -> loc_677a5b3
0x677a5a3  mov rax,[r14]                                 
0x677a5a6  mov rax,[rax+8]                               
0x677a5aa  mov rcx,r14                                   
0x677a5ad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a5b3  mov r14,[rbp+0x7C8]                           
0x677a5ba  test r14,r14                                  
0x677a5bd  je short 0x677A5EC                            ; -> loc_677a5ec
0x677a5bf  lock dec dword ptr [r14+8]                    
0x677a5c4  jne short 0x677A5EC                           ; -> loc_677a5ec
0x677a5c6  mov rax,[r14]                                 
0x677a5c9  mov rax,[rax]                                 
0x677a5cc  mov rcx,r14                                   
0x677a5cf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a5d5  lock dec dword ptr [r14+0xC]                  
0x677a5da  jne short 0x677A5EC                           ; -> loc_677a5ec
0x677a5dc  mov rax,[r14]                                 
0x677a5df  mov rax,[rax+8]                               
0x677a5e3  mov rcx,r14                                   
0x677a5e6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a5ec  mov r14,[rbp+0x788]                           
0x677a5f3  test r14,r14                                  
0x677a5f6  je 0x677B13C                                  ; -> loc_677b13c
0x677a5fc  lock dec dword ptr [r14+8]                    
0x677a601  jne 0x677B13C                                 ; -> loc_677b13c
0x677a607  mov rax,[r14]                                 
0x677a60a  mov rax,[rax]                                 
0x677a60d  mov rcx,r14                                   
0x677a610  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

Interpretation: `call qword ptr [0xF99FFA0]` — the vtable+8 destructor call for the previous object (r14=[rbp+0x4A8], from Phase 115). Then release sequence 2: `r14=[rbp+0x7D8]`; `test r14,r14`; if zero jump to loc_677a5b3; `lock dec dword ptr [r14+8]`; if != 0 jump to loc_677a5b3; else destructor: `mov rax,[r14]`, `mov rax,[rax]`, `mov rcx,r14`, call via [0xF99FFA0] (vtable+0); `lock dec dword ptr [r14+0xC]`; if != 0 jump to loc_677a5b3; else `mov rax,[r14]`, `mov rax,[rax+8]`, `mov rcx,r14`, call via [0xF99FFA0] (vtable+8). loc_677a5b3: `r14=[rbp+0x7C8]`; same sequence with jumps to loc_677a5ec. loc_677a5ec: `r14=[rbp+0x788]`; `test`; `je 0x677B13C`; `lock dec [r14+8]`; `jne 0x677B13C`; else destructor vtable+0 call at 0x677a610. Range ends at that call; next instruction at 0x677a616.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 4x in this phase: vtable+8 of prev object, then vtable+0/vtable+8 for [rbp+0x7D8], vtable+0/vtable+8 for [rbp+0x7C8], vtable+0 for [rbp+0x788]).
Fields read: [rbp+0x7D8], r14, [r14+8], [r14], [rax], [r14+0xC], [rax+8]; [rbp+0x7C8], [r14+8], [r14], [rax], [r14+0xC], [rax+8]; [rbp+0x788], [r14+8], [r14], [rax]. Fields written: [r14+8] (lock dec x3), [r14+0xC] (lock dec x2).

## Phase 117 — Destructor tail (vtable+8) + cmp byte [rbp+0x80],3 + grow stub 0x14DB710 + TLS + counter + shared_ptr push setup (0x677a616..0x677a6d0)

Tail of the [rbp+0x788] release sequence (lock-dec [r14+0xC], destructor vtable+8), then cmp byte [rbp+0x80],3 (je sub_677deae / jmp sub_677def0), grow-path stub `rcx=r14+0x630, r8=r12, call 0x14DB710`, TLS read, [rbp+0x300]=0x100000006C07843, shr2/dec counter at [rbp+0x344], TLS read, feature flag store, cursor [r14+8] vs [r14+0x10] (jne → shared_ptr push setup: r8d=0xC8, rcx=rdx, rdx=r13).

```
0x677a616  lock dec dword ptr [r14+0xC]                  
0x677a61b  jne 0x677B13C                                 ; -> loc_677b13c
0x677a621  mov rax,[r14]                                 
0x677a624  mov rax,[rax+8]                               
0x677a628  mov rcx,r14                                   
0x677a62b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a631  cmp byte ptr [rbp+0x80],3                     
0x677a638  je 0x677DEAE                                  ; -> sub_677deae
0x677a63e  jmp 0x677DEF0                                 ; -> sub_677def0
0x677a643  mov rcx,r14                                   
0x677a646  add rcx,0x630                                 
0x677a64d  mov r8,r12                                    
0x677a650  call 0x14DB710                                ; -> sub_14db710
0x677a655  nop                                           
0x677a656  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a65d  mov rax,[rcx]                                 
0x677a660  mov rax,[rax+0x10]                            
0x677a664  movzx edx,byte ptr [rbp+0x838]                
0x677a66b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a671  nop                                           
0x677a672  mov rax,0x100000006C07843                     
0x677a67c  mov [rbp+0x300],rax                           
0x677a683  mov eax,[r14+0x638]                           
0x677a68a  sub eax,[r14+0x630]                           
0x677a691  shr eax,2                                     
0x677a694  dec eax                                       
0x677a696  mov [rbp+0x344],ax                            
0x677a69d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a6a4  mov rax,[rcx]                                 
0x677a6a7  mov rax,[rax+0x10]                            
0x677a6ab  mov dl,0x4A                                   
0x677a6ad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a6b3  nop                                           
0x677a6b4  mov [rbp+0x838],al                            
0x677a6ba  mov rdx,[r14+8]                               
0x677a6be  cmp rdx,[r14+0x10]                            
0x677a6c2  je short 0x677A6DF                            ; -> loc_677a6df
0x677a6c4  mov r8d,0xC8                                  
0x677a6ca  mov rcx,rdx                                   
0x677a6cd  mov rdx,r13                                   
```

Interpretation: `lock dec dword ptr [r14+0xC]`; if != 0 jump to loc_677b13c; else destructor `mov rax,[r14]`, `mov rax,[rax+8]`, `mov rcx,r14`, call via [0xF99FFA0] (vtable+8). Then `cmp byte ptr [rbp+0x80],3`; `je 0x677DEAE` (sub_677deae); `jmp 0x677DEF0` (sub_677def0). Grow path: `mov rcx,r14`, `add rcx,0x630`, `mov r8,r12`, call 0x14DB710 (matches Phase 107's grow stub). TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. `mov rax,0x100000006C07843`, `[rbp+0x300]=rax` (u64). Counter: eax=[r14+0x638], sub [r14+0x630], shr 2, dec, [rbp+0x344]=ax. TLS read again, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+8], cmp [r14+0x10]; if equal jump to loc_677a6df (grow). Otherwise r8d=0xC8, rcx=rdx, rdx=r13 — fall into call 0xEEC6EC0 (next phase). Range ends at `mov rdx,r13`; next instruction at 0x677a6d0.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 2x), 0x14DB710 (sub_14db710), 0x677DEAE (sub_677deae, via je), 0x677DEF0 (sub_677def0, via jmp).
Fields read: [r14+0xC], [r14], [rax+8], [rbp+0x80], r14, [rbp+0x630]? no—[r14+0x638], [r14+0x630], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x638] (again via second TLS? no), [rbp+0x838] (again), [r14+8], [r14+0x10], r13. Fields written: [r14+0xC] (lock dec), [rbp+0x300], [rbp+0x344], [rbp+0x838].

## Phase 118 — shared_ptr push call + [r14+8]+=0xC8 + grow stub 0x5ABA6D0 + TLS + call 0x67E40A0 + jmp 0x677B130 + copy block (rbp+0x3E0 → rbp+0x250 / rbx+0xA7) (0x677a6d0..0x677a791)

Finish the shared_ptr push (call 0xEEC6EC0, [r14+8]+=0xC8, jmp loc_677a6eb); grow-path fallback `rcx=r14, r8=r13, call 0x5ABA6D0`; then TLS read, call 0x67E40A0 with rcx=r12, jmp 0x677B130. Fall-through at 0x677a714: call 0x678CF10 (rcx=&[rbp+0x2C0], rdx=r13), then call 0x678F640 with 4 args reading fields from [rbp+0x3E0] (+0x58,+0x68,+0x80,+0x90,+0x9F) and writing 16-byte chunks to [rbp+0x250] and [rbx+0xA7], plus byte [rbp+0x44C]→[rbp+0x264].

```
0x677a6d0  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x677a6d5  add qword ptr [r14+8],0xC8                    
0x677a6dd  jmp short 0x677A6EB                           ; -> loc_677a6eb
0x677a6df  mov rcx,r14                                   
0x677a6e2  mov r8,r13                                    
0x677a6e5  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x677a6ea  nop                                           
0x677a6eb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677a6f2  mov rax,[rcx]                                 
0x677a6f5  mov rax,[rax+0x10]                            
0x677a6f9  movzx edx,byte ptr [rbp+0x838]                
0x677a700  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a706  nop                                           
0x677a707  mov rcx,r12                                   
0x677a70a  call 0x67E40A0                                ; -> sub_67e40a0
0x677a70f  jmp 0x677B130                                 ; -> loc_677b130
0x677a714  lea rcx,[rbp+0x2C0]                           
0x677a71b  mov rdx,r13                                   
0x677a71e  call 0x678CF10                                ; -> sub_678cf10
0x677a723  nop                                           
0x677a724  lea rcx,[rbp+0x110]                           
0x677a72b  lea rdx,[rbp+0x3E0]                           
0x677a732  lea r8,[rbp+0x388]                            
0x677a739  mov r9,r13                                    
0x677a73c  call 0x678F640                                ; -> sub_678f640
0x677a741  nop                                           
0x677a742  lea rcx,[rbp+0x3E0]                           
0x677a749  mov eax,[rcx+0x68]                            
0x677a74c  lea rdx,[rbp+0x250]                           
0x677a753  mov [rdx+0x10],eax                            
0x677a756  movups xmm0,[rcx+0x58]                        
0x677a75a  movups [rdx],xmm0                             
0x677a75d  movzx eax,byte ptr [rbp+0x44C]                
0x677a764  mov [rbp+0x264],al                            
0x677a76a  movups xmm0,[rbp+0x450]                       
0x677a771  movups [rbp+0x268],xmm0                       
0x677a778  movups xmm0,[rcx+0x80]                        
0x677a77f  movups xmm1,[rcx+0x90]                        
0x677a786  movups xmm2,[rcx+0x9F]                        
0x677a78d  movups [rbx+0xA7],xmm2                        
```

Interpretation: `call 0xEEC6EC0` (shared_ptr push; rcx=cursor [r14+8], rdx=r13, r8d=0xC8 set in Phase 117), `add qword ptr [r14+8],0xC8`, `jmp short 0x677A6EB`. loc_677a6df (grow fail path, reached via je from 0x677a6c2): `mov rcx,r14`, `mov r8,r13`, call 0x5ABA6D0. loc_677a6eb: TLS read rcx=[0x1233E1B0]→[rax]→[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]; `mov rcx,r12`, call 0x67E40A0; `jmp 0x677B130`. Fall-through at 0x677a714 (landing pad from another branch): `lea rcx,[rbp+0x2C0]`, `mov rdx,r13`, call 0x678CF10; `lea rcx,[rbp+0x110]`, `lea rdx,[rbp+0x3E0]`, `lea r8,[rbp+0x388]`, `mov r9,r13`, call 0x678F640; `lea rcx,[rbp+0x3E0]`, `mov eax,[rcx+0x68]` ([rbp+0x3E0+0x68]), `lea rdx,[rbp+0x250]`, `mov [rdx+0x10],eax` ([rbp+0x250+0x10]=eax), `movups xmm0,[rcx+0x58]` ([rbp+0x3E0+0x58]), `movups [rdx],xmm0` ([rbp+0x250]=16 bytes), `movzx eax,byte [rbp+0x44C]`, `mov [rbp+0x264],al`, `movups xmm0,[rbp+0x450]`, `movups [rbp+0x268],xmm0`, `movups xmm0,[rcx+0x80]` ([rbp+0x3E0+0x80]), `movups xmm1,[rcx+0x90]`, `movups xmm2,[rcx+0x9F]`, `movups [rbx+0xA7],xmm2`. Range ends at `movups [rbx+0xA7],xmm2`; next instruction at 0x677a791.

Callees: 0xEEC6EC0 (sub_eec6ec0), 0x5ABA6D0 (sub_5aba6d0), [0xF99FFA0] = sub_eea6040 (indirect), 0x67E40A0 (sub_67e40a0), 0x678CF10 (sub_678cf10), 0x678F640 (sub_678f640).
Fields read: [r14+8], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], r12, [rbp+0x2C0] (addr only), r13, [rbp+0x110], [rbp+0x3E0], [[rbp+0x3E0]+0x68] (as [rcx+0x68]), [rbp+0x44C], [rbp+0x450], [[rbp+0x3E0]+0x58] (as [rcx+0x58]), [[rbp+0x3E0]+0x80], [[rbp+0x3E0]+0x90], [[rbp+0x3E0]+0x9F], rbx. Fields written: [r14+8], [rbp+0x838], [[rbp+0x250]+0x10] (as [rdx+0x10]), [rbp+0x250] (movups [rdx]), [rbp+0x264], [rbp+0x268], [rbx+0xA7].

## Phase 119 — Tail of copy block (add/adc/movups — likely embedded bytes) + movzx word [rbp+0x490] + size math vs 0x768 block + je sub_677e011 + cmp rax,r8 + je loc_677bd29 + magic multiply + call 0x6769EE0 + [rbp+0x800]/[rbp+0x808] setup (0x677a791..0x677a862)

Starts with four instructions (`add [rax],al`, `add [rdi],cl`, `adc [rbx+0x98],ecx`, `movups [rbx+0x88],xmm0`) that rdis prints right after the `movups [rbx+0xA7],xmm2` of Phase 118; their listed lengths don't sum cleanly (possible embedded bytes/padding), real code resumes cleanly at `movzx eax,word ptr [rbp+0x490]` (0x677a7a2) and stays consistent to the phase end. Then: load block ptr [rbp+0x768], r8=[rax+0x480], rax=[rax+0x488], rdx=rax-r8, cmp rdx,0xFFFFFFFFFFFFFFD0 → je sub_677e011; test r8,r8/setne cl; test rax,rax/sete r9b; or r9b,cl → je sub_677e011 if both zero; cmp rax,r8 → je loc_677bd29 if equal; mov rax,[rbp+0x778]; cmp qword [rax],0 → je loc_677bd29 if null; sar rdx,4; mov rax,0xAAAAAAAAAAAAAAAB; imul rdx,rax (magic divide); mov dword [rsp+0x20],0x41800000; lea rcx,[rbp+0x800]; lea r9,[rbp+0x2E0]; call 0x6769EE0; mov rax,[rbp+0x800]; mov rcx,[rbp+0x808]; mov r14,rax; [rbp+0x838]=rax; [rbp+0x568]=rcx; cmp rax,rcx → je loc_677bc96; then `mov rax,[rbp+0x778]` again (phase ends there).

```
0x677a791  add [rax],al                                  
0x677a793  add [rdi],cl                                  
0x677a795  adc [rbx+0x98],ecx                            
0x677a79b  movups [rbx+0x88],xmm0                        
0x677a7a2  movzx eax,word ptr [rbp+0x490]                
0x677a7a9  mov [rbp+0x2A8],ax                            
0x677a7b0  mov rax,[rbp+0x768]                           
0x677a7b7  mov r8,[rax+0x480]                            
0x677a7be  mov rax,[rax+0x488]                           
0x677a7c5  mov rdx,rax                                   
0x677a7c8  sub rdx,r8                                    
0x677a7cb  cmp rdx,0xFFFFFFFFFFFFFFD0                    
0x677a7cf  je 0x677E011                                  ; -> sub_677e011
0x677a7d5  test r8,r8                                    
0x677a7d8  setne cl                                      
0x677a7db  test rax,rax                                  
0x677a7de  sete r9b                                      
0x677a7e2  or r9b,cl                                     
0x677a7e5  je 0x677E011                                  ; -> sub_677e011
0x677a7eb  cmp rax,r8                                    
0x677a7ee  je 0x677BD29                                  ; -> loc_677bd29
0x677a7f4  mov rax,[rbp+0x778]                           
0x677a7fb  cmp qword ptr [rax],0                         
0x677a7ff  je 0x677BD29                                  ; -> loc_677bd29
0x677a805  sar rdx,4                                     
0x677a809  mov rax,0xAAAAAAAAAAAAAAAB                    
0x677a813  imul rdx,rax                                  
0x677a817  mov dword ptr [rsp+0x20],0x41800000           
0x677a81f  lea rcx,[rbp+0x800]                           
0x677a826  lea r9,[rbp+0x2E0]                            
0x677a82d  call 0x6769EE0                                ; -> sub_6769ee0
0x677a832  nop                                           
0x677a833  mov rax,[rbp+0x800]                           
0x677a83a  mov rcx,[rbp+0x808]                           
0x677a841  mov r14,rax                                   
0x677a844  mov [rbp+0x838],rax                           
0x677a84b  mov [rbp+0x568],rcx                           
0x677a852  cmp rax,rcx                                   
0x677a855  je 0x677BC96                                  ; -> loc_677bc96
0x677a85b  mov rax,[rbp+0x778]                           
```

Interpretation: `add [rax],al`; `add [rdi],cl`; `adc [rbx+0x98],ecx`; `movups [rbx+0x88],xmm0` — appear immediately after Phase 118's final movups; listed lengths don't sum cleanly to the next consistent stream ([I] possible embedded bytes/padding). From `movzx eax,word ptr [rbp+0x490]`: ax=[rbp+0x490], [rbp+0x2A8]=ax. rax=[rbp+0x768]; r8=[rax+0x480]; rax=[rax+0x488] (end ptr); rdx=rax; rdx-=r8 (size); cmp rdx,0xFFFFFFFFFFFFFFD0 (-48 as u64) → je sub_677e011 if equal. test r8,r8; setne cl (start!=0); test rax,rax; sete r9b (end!=0); or r9b,cl → je sub_677e011 if neither set. cmp rax,r8 → je loc_677bd29 if empty range. mov rax,[rbp+0x778]; cmp qword ptr [rax],0 → je loc_677bd29 if null. sar rdx,4; mov rax,magic 0xAAAAAAAAAAAAAAAB; imul rdx,rax (size/16 magic-mul). mov dword ptr [rsp+0x20],0x41800000 (float 1110.0?). lea rcx,[rbp+0x800]; lea r9,[rbp+0x2E0]; call 0x6769EE0 (with rdx=index, rcx=&[rbp+0x800], r9=&[rbp+0x2E0]). mov rax,[rbp+0x800]; mov rcx,[rbp+0x808]; mov r14,rax; [rbp+0x838]=rax; [rbp+0x568]=rcx (store range begin/end); cmp rax,rcx → je loc_677bc96 if equal. Range ends at `mov rax,[rbp+0x778]`; next instruction at 0x677a862.

Callees: 0x677E011 (sub_677e011, via je x2), 0x677BD29 (loc_677bd29, via je x2), 0x6769EE0 (sub_6769ee0).
Fields read: [rax] (add [rax],al), [rdi] (add [rdi],cl), [rbx+0x98] (adc), [rbx+0x88] (movups), [rbp+0x490], [rbp+0x768], [rax+0x480], [rax+0x488], [rbp+0x778], [rax] (cmp qword [rax],0), [rsp+0x20] (addr only), [rbp+0x800], [rbp+0x808]. Fields written: [rax] (add [rax],al), [rdi] (add [rdi],cl), [rbx+0x98] (adc), [rbx+0x88] (movups), [rbp+0x2A8], [rsp+0x20], [rbp+0x838], [rbp+0x568], r14.

## Phase 120 — Virtual call [rax+0x48] + range guards (je sub_677e011 x3) + [rbp+0x7C0/0x7C8] setup + 0x20-step loop call 0x676A670 + padding + loc_677a90c (0x677a862..0x677a913)

Virtual call on object [rbp+0x778] via vtable+0x48 with rdx=&[rbp+0x4A0]. Then r14=[rbp+0x800] (begin), r15=[rbp+0x808] (end); size=r15-r14; guards: size != 0xFFFFFFE0, both pointers non-null, r15>r14 — each failure je sub_677e011. Setup [rbp+0x7C0]=&[rbp+0x7D0], [rbp+0x7C8]=0x100000000. If begin==end jump to loc_677a90c; else loop loc_677a8f0: call 0x676A670(rcx=&[rbp+0x7C0], rdx=r12, r8=cur), cur+=0x20 until cur==end. Bytes 0x677a8ea-0x677a8ef (between nop [rax+rax] and loop label) decode as test [rax],al / add [rax],al / add [rax],al — alignment padding into loc_677a8f0 ([I]). Ends at loc_677a90c: lea rax,[rbp+0x790] (next instruction 0x677a913).

```
0x677a862  mov rcx,[rax]                                 
0x677a865  mov rax,[rcx]                                 
0x677a868  mov rax,[rax+0x48]                            
0x677a86c  lea rdx,[rbp+0x4A0]                           
0x677a873  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677a879  nop                                           
0x677a87a  mov r14,[rbp+0x800]                           
0x677a881  mov r15,[rbp+0x808]                           
0x677a888  mov rax,r15                                   
0x677a88b  sub rax,r14                                   
0x677a88e  cmp rax,0xFFFFFFFFFFFFFFE0                    
0x677a892  je 0x677E011                                  ; -> sub_677e011
0x677a898  test r14,r14                                  
0x677a89b  setne al                                      
0x677a89e  test r15,r15                                  
0x677a8a1  sete cl                                       
0x677a8a4  or cl,al                                      
0x677a8a6  je 0x677E011                                  ; -> sub_677e011
0x677a8ac  test r14,r14                                  
0x677a8af  setne al                                      
0x677a8b2  cmp r15,r14                                   
0x677a8b5  sete cl                                       
0x677a8b8  or cl,al                                      
0x677a8ba  je 0x677E011                                  ; -> sub_677e011
0x677a8c0  lea rax,[rbp+0x7D0]                           
0x677a8c7  mov [rbp+0x7C0],rax                           
0x677a8ce  mov rax,0x100000000                           
0x677a8d8  mov [rbp+0x7C8],rax                           
0x677a8df  cmp r15,r14                                   
0x677a8e2  je short 0x677A90C                            ; -> loc_677a90c
0x677a8e4  nop [rax+rax]                                 
0x677a8f0  lea rcx,[rbp+0x7C0]                           
0x677a8f7  mov rdx,r12                                   
0x677a8fa  mov r8,r14                                    
0x677a8fd  call 0x676A670                                ; -> sub_676a670
0x677a902  nop                                           
0x677a903  add r14,0x20                                  
0x677a907  cmp r14,r15                                   
0x677a90a  jne short 0x677A8F0                           ; -> loc_677a8f0
0x677a90c  lea rax,[rbp+0x790]                           
```

Interpretation: rax=[rbp+0x778] (from Phase 119); `mov rcx,[rax]`, `mov rax,[rcx]`, `mov rax,[rax+0x48]` (vtable+0x48), `lea rdx,[rbp+0x4A0]`, call via [0xF99FFA0] — virtual method call. Then `mov r14,[rbp+0x800]`, `mov r15,[rbp+0x808]` (range begin/end); `rax=r15-r14`; `cmp rax,0xFFFFFFFFFFFFFFE0` (-32) → `je sub_677e011`; `test r14,r14/setne al`, `test r15,r15/sete cl`, `or cl,al` → `je sub_677e011` if either pointer is null; `test r14,r14/setne al`, `cmp r15,r14/sete cl` (r15>r14 unsigned), `or cl,al` → `je sub_677e011` if not (end<=start). All three guards funnel to sub_677e011. `lea rax,[rbp+0x7D0]`; `[rbp+0x7C0]=rax` (pointer to local); `mov rax,0x100000000`; `[rbp+0x7C8]=rax` (u64 4294967296). `cmp r15,r14`; if equal `je loc_677a90c` (skip loop). `nop [rax+rax]`; padding bytes at 0x677a8ea-0x677a8ef decode as `test [rax],al`/`add [rax],al`/`add [rax],al` ([I] alignment fill). loc_677a8f0 loop: `lea rcx,[rbp+0x7C0]`, `mov rdx,r12`, `mov r8,r14`, call 0x676A670; `add r14,0x20`; `cmp r14,r15`; `jne loc_677a8f0`. loc_677a90c: `lea rax,[rbp+0x790]`; range ends there; next instruction 0x677a913.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), sub_677e011 (via je x3), loc_677a8f0 (loop back-edge via jne), loc_677a90c (via je), 0x676A670 (sub_676a670).
Fields read: [rbp+0x778], [rax] (= [[rbp+0x778]]), [rcx] (= [[rbp+0x778]]->vtable), [rax+0x48] (vtable+0x48), [rbp+0x4A0] (lea addr), [rbp+0x800], [rbp+0x808], r14, r15, [rbp+0x7D0] (lea addr). Fields written: [rbp+0x7C0], [rbp+0x7C8], r14 (loop induction).

## Phase 121 — [rbp+0x780/0x788] setup + call 0x6764990 + [rsp+0x20]=r14 + call 0x6792570 (4 args) + copy block [rbp+0x250]→[rbp+0x6F0], [rbx+0x88/0x98/0xA7]→[rbp+0x574+0x1C3/0x1B4/0x1A4] + word [rbp+0x2A8]→[rbp+0x748] + call 0x5ABA5C0 (0x677a913..0x677a9f2)

[rbp+0x780]=rax (=&[rbp+0x790] from Phase 120), [rbp+0x788]=0x100000000 (u64), r14=&[rbp+0x780]. `call 0x6764990`(rcx=&[rbp+0x780], rdx=&[rbp+0x7C0]); [rsp+0x20]=r14. `call 0x6792570`(rcx=r12, rdx=&[rbp+0x1F8], r8=&[rbp+0x1A0], r9=&[rbp+0x118]). Copy block: eax=[rbp+0x250+0x10]; [rbp+0x6F0+0x10]=eax; movups [rbp+0x6F0]=xmm0=[rbp+0x250] (16 bytes); movzx eax,byte [rbp+0x264]; [rbp+0x704]=al; movups [rbp+0x708]=xmm0=[rbp+0x268]; movups xmm0=[rbx+0x88], xmm1=[rbx+0x98], xmm2=[rbx+0xA7]; rax=&[rbp+0x574]; [rbp+0x574+0x1C3]=xmm2, [rbp+0x574+0x1B4]=xmm1, [rbp+0x574+0x1A4]=xmm0; movzx eax,word [rbp+0x2A8]; [rbp+0x748]=ax. Then rax=[rbp+0x828]; rcx=[rax+0x10]; eax=0x9D0; rcx+=rax; call 0x5ABA5C0. Ends with `nop` at 0x677a9f1; next instruction 0x677a9f2.

```
0x677a913  mov [rbp+0x780],rax                           
0x677a91a  mov rax,0x100000000                           
0x677a924  mov [rbp+0x788],rax                           
0x677a92b  lea r14,[rbp+0x780]                           
0x677a932  mov rcx,r14                                   
0x677a935  lea rdx,[rbp+0x7C0]                           
0x677a93c  call 0x6764990                                ; -> sub_6764990
0x677a941  nop                                           
0x677a942  mov [rsp+0x20],r14                            
0x677a947  mov rcx,r12                                   
0x677a94a  lea rdx,[rbp+0x1F8]                           
0x677a951  lea r8,[rbp+0x1A0]                            
0x677a958  lea r9,[rbp+0x118]                            
0x677a95f  call 0x6792570                                ; -> sub_6792570
0x677a964  nop                                           
0x677a965  lea rcx,[rbp+0x250]                           
0x677a96c  mov eax,[rcx+0x10]                            
0x677a96f  lea rdx,[rbp+0x6F0]                           
0x677a976  mov [rdx+0x10],eax                            
0x677a979  movups xmm0,[rcx]                             
0x677a97c  movups [rdx],xmm0                             
0x677a97f  movzx eax,byte ptr [rbp+0x264]                
0x677a986  mov [rbp+0x704],al                            
0x677a98c  movups xmm0,[rbp+0x268]                       
0x677a993  movups [rbp+0x708],xmm0                       
0x677a99a  movups xmm0,[rbx+0x88]                        
0x677a9a1  movups xmm1,[rbx+0x98]                        
0x677a9a8  movups xmm2,[rbx+0xA7]                        
0x677a9af  lea rax,[rbp+0x574]                           
0x677a9b6  movups [rax+0x1C3],xmm2                       
0x677a9bd  movups [rax+0x1B4],xmm1                       
0x677a9c4  movups [rax+0x1A4],xmm0                       
0x677a9cb  movzx eax,word ptr [rbp+0x2A8]                
0x677a9d2  mov [rbp+0x748],ax                            
0x677a9d9  mov rax,[rbp+0x828]                           
0x677a9e0  mov rcx,[rax+0x10]                            
0x677a9e4  mov eax,0x9D0                                 
0x677a9e9  add rcx,rax                                   
0x677a9ec  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x677a9f1  nop                                           
```

Interpretation: `mov [rbp+0x780],rax` (rax=&[rbp+0x790] from Phase 120's `lea rax,[rbp+0x790]`); `mov rax,0x100000000`; `[rbp+0x788]=rax` (u64 4294967296); `lea r14,[rbp+0x780]`; `mov rcx,r14`; `lea rdx,[rbp+0x7C0]`; call 0x6764990. `[rsp+0x20]=r14` (spill). `mov rcx,r12`; `lea rdx,[rbp+0x1F8]`; `lea r8,[rbp+0x1A0]`; `lea r9,[rbp+0x118]`; call 0x6792570 (4-arg). Copy sequence: `lea rcx,[rbp+0x250]`; `mov eax,[rcx+0x10]` ([rbp+0x250+0x10]); `lea rdx,[rbp+0x6F0]`; `[rdx+0x10]=eax` ([rbp+0x6F0+0x10]); `movups xmm0,[rcx]` ([rbp+0x250]); `movups [rdx],xmm0` ([rbp+0x6F0], 16 bytes); `movzx eax,byte [rbp+0x264]`; `[rbp+0x704]=al`; `movups xmm0,[rbp+0x268]`; `movups [rbp+0x708],xmm0`; `movups xmm0,[rbx+0x88]`; `movups xmm1,[rbx+0x98]`; `movups xmm2,[rbx+0xA7]`; `lea rax,[rbp+0x574]`; `[rax+0x1C3]=xmm2` ([rbp+0x574+0x1C3]); `[rax+0x1B4]=xmm1` ([rbp+0x574+0x1B4]); `[rax+0x1A4]=xmm0` ([rbp+0x574+0x1A4]); `movzx eax,word [rbp+0x2A8]`; `[rbp+0x748]=ax`. `mov rax,[rbp+0x828]`; `mov rcx,[rax+0x10]`; `mov eax,0x9D0`; `add rcx,rax`; call 0x5ABA5C0 with rcx=[rbp+0x828]+0x10+0x9D0. Ends `nop`; next instruction 0x677a9f2.

Callees: 0x6764990 (sub_6764990), 0x6792570 (sub_6792570), 0x5ABA5C0 (sub_5aba5c0).
Fields read: [rbp+0x780] (written here; read as source? no—written), [rbp+0x7C0] (addr), r12, [rbp+0x1F8], [rbp+0x1A0], [rbp+0x118] (addrs only), [rbp+0x250], [[rbp+0x250]+0x10], [rbp+0x264], [rbp+0x268], [rbx+0x88], [rbx+0x98], [rbx+0xA7], [rbp+0x574] (addr), [rbp+0x2A8], [rbp+0x828], [[rbp+0x828]+0x10]. Fields written: [rbp+0x780], [rbp+0x788], [rsp+0x20], [rbp+0x6F0], [[rbp+0x6F0]+0x10], [rbp+0x704], [rbp+0x708], [[rbp+0x574]+0x1C3], [[rbp+0x574]+0x1B4], [[rbp+0x574]+0x1A4], [rbp+0x748].

## Phase 122 — r14=rax + 12x movaps zero slots [rbp+0x550..0x4A0] + [rbp+0x560]=0 + TLS feature flag [rbp+0x847]=al + u16 cursor write [r14+0x8A8] (grow loc_677b4cc) + call 0x678CF10 + call 0x678F640 + mov eax,[rbx+0x68] (0x677a9f2..0x677aad4)

rax (0x5ABA5C0 result) → r14. Zero 12 16-byte slots [rbp+0x550] down to [rbp+0x4A0] with movaps xmm6, then [rbp+0x560]=0. TLS read + mov dl,0x4A + call via [0xF99FFA0] + [rbp+0x847]=al (feature flag). Cursor: rdx=[r14+0x8A8], cmp [r14+0x8B0] → je loc_677b4cc (grow); else movzx eax,word [rbp+0x748], [rdx]=ax (u16 write), [r14+0x8A8]+=2, jmp loc_677b4e0. Fall path loc_677aa9c (grow fail): lea rcx,[rbp+0x2C0], lea rdx,[rbp+0x110], call 0x678CF10. Then call 0x678F640(rcx=r12, rdx=rbx, r8=&[rbp+0x198], r9=&[rbp+0x110]). Then `mov eax,[rbx+0x68]`, `lea rcx,[rbp+0x6B0]` (continues next phase).

```
0x677a9f2  mov r14,rax                                   
0x677a9f5  movaps [rbp+0x550],xmm6                       
0x677a9fc  movaps [rbp+0x540],xmm6                       
0x677aa03  movaps [rbp+0x530],xmm6                       
0x677aa0a  movaps [rbp+0x520],xmm6                       
0x677aa11  movaps [rbp+0x510],xmm6                       
0x677aa18  movaps [rbp+0x500],xmm6                       
0x677aa1f  movaps [rbp+0x4F0],xmm6                       
0x677aa26  movaps [rbp+0x4E0],xmm6                       
0x677aa2d  movaps [rbp+0x4D0],xmm6                       
0x677aa34  movaps [rbp+0x4C0],xmm6                       
0x677aa3b  movaps [rbp+0x4B0],xmm6                       
0x677aa42  movaps [rbp+0x4A0],xmm6                       
0x677aa49  mov qword ptr [rbp+0x560],0                   
0x677aa54  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677aa5b  mov rax,[rcx]                                 
0x677aa5e  mov rax,[rax+0x10]                            
0x677aa62  mov dl,0x4A                                   
0x677aa64  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677aa6a  nop                                           
0x677aa6b  mov [rbp+0x847],al                            
0x677aa71  mov rdx,[r14+0x8A8]                           
0x677aa78  cmp rdx,[r14+0x8B0]                           
0x677aa7f  je 0x677B4CC                                  ; -> loc_677b4cc
0x677aa85  movzx eax,word ptr [rbp+0x748]                
0x677aa8c  mov [rdx],ax                                  
0x677aa8f  add qword ptr [r14+0x8A8],2                   
0x677aa97  jmp 0x677B4E0                                 ; -> loc_677b4e0
0x677aa9c  lea rcx,[rbp+0x2C0]                           
0x677aaa3  lea rdx,[rbp+0x110]                           
0x677aaaa  call 0x678CF10                                ; -> sub_678cf10
0x677aaaf  nop                                           
0x677aab0  mov rcx,r12                                   
0x677aab3  mov rdx,rbx                                   
0x677aab6  lea r8,[rbp+0x198]                            
0x677aabd  lea r9,[rbp+0x110]                            
0x677aac4  call 0x678F640                                ; -> sub_678f640
0x677aac9  nop                                           
0x677aaca  mov eax,[rbx+0x68]                            
0x677aacd  lea rcx,[rbp+0x6B0]                           
```

Interpretation: `mov r14,rax` (rax = call 0x5ABA5C0 result from Phase 121). Zero loop: `movaps [rbp+0x550],xmm6`, `movaps [rbp+0x540],xmm6`, `movaps [rbp+0x530],xmm6`, `movaps [rbp+0x520],xmm6`, `movaps [rbp+0x510],xmm6`, `movaps [rbp+0x500],xmm6`, `movaps [rbp+0x4F0],xmm6`, `movaps [rbp+0x4E0],xmm6`, `movaps [rbp+0x4D0],xmm6`, `movaps [rbp+0x4C0],xmm6`, `movaps [rbp+0x4B0],xmm6`, `movaps [rbp+0x4A0],xmm6` (12 slots, xmm6 presumed zero), then `mov qword ptr [rbp+0x560],0`. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], mov dl,0x4A, call via [0xF99FFA0]; `mov [rbp+0x847],al` (feature flag byte stored). Cursor bounds check: rdx=[r14+0x8A8], cmp [r14+0x8B0]; if equal jump to loc_677b4cc (grow path). Otherwise movzx eax,word [rbp+0x748], [rdx]=ax (u16 write at cursor), [r14+0x8A8]+=2, jmp loc_677b4e0. Grow-fail path loc_677aa9c (target of the je): `lea rcx,[rbp+0x2C0]`, `lea rdx,[rbp+0x110]`, call 0x678CF10. Then `mov rcx,r12`, `mov rdx,rbx`, `lea r8,[rbp+0x198]`, `lea r9,[rbp+0x110]`, call 0x678F640. Then `mov eax,[rbx+0x68]`, `lea rcx,[rbp+0x6B0]`; phase ends there; next instruction 0x677aad4.

Callees: [0xF99FFA0] = sub_eea6040 (indirect), loc_677b4cc (grow, via je), loc_677b4e0 (via jmp), 0x678CF10 (sub_678cf10), 0x678F640 (sub_678f640).
Fields read: xmm6 (zero source), [r14+0x8A8], [r14+0x8B0], [rbp+0x748], [0x1233E1B0], [rcx], [rax+0x10], r12, rbx, [rbx+0x68]. Fields written: [rbp+0x550], [rbp+0x540], [rbp+0x530], [rbp+0x520], [rbp+0x510], [rbp+0x500], [rbp+0x4F0], [rbp+0x4E0], [rbp+0x4D0], [rbp+0x4C0], [rbp+0x4B0], [rbp+0x4A0] (movaps x12), [rbp+0x560], [rbp+0x847], [r14+0x8A8] (u16 write via [rdx]), [r14+0x8A8] (add).

## Phase 123 — [rbp+0x6B0+0x10]=u16 [rbx+0x68] + copy block [rbx+0x58]→[rbp+0x6B0], [rbp+0x25C/0x260]→[rbp+0x6C4/0x6C8], [rbx+0x80/0x90/0x9F]→[rbp+0x574+0x164/0x174/0x183], word [rbp+0x2A0]→[rbp+0x708] + size/16 magic-mul + call 0x678F950 (0x677aad4..0x677abb9)

rcx=&[rbp+0x6B0] (from Phase 122); eax=movzx word [rbx+0x68] (Phase 122 end) stored to [rcx+0x10] = [rbp+0x6B0+0x10]. Copy block: movups [rbp+0x6B0]=xmm0=[rbx+0x58]; movzx eax,byte [rbp+0x25C]; [rbp+0x6C4]=al; movups [rbp+0x6C8]=xmm0=[rbp+0x260]; movups xmm0=[rbx+0x80], xmm1=[rbx+0x90], xmm2=[rbx+0x9F]; rax=&[rbp+0x574]; [rbp+0x574+0x164]=xmm0, [rbp+0x574+0x174]=xmm1, [rbp+0x574+0x183]=xmm2; movzx eax,word [rbp+0x2A0]; [rbp+0x708]=ax. Size math on object [rbp+0x768]: rax=[rcx+0x480] (begin), rdx=[rcx+0x488] (end), rcx=rdx-rax; cmp rcx,0xFFFFFFD0 (-48) → je sub_677e011; test rax,rax/setne r8b; test rdx,rdx/sete dl; or dl,r8b → je sub_677e011 if either pointer null; sar rcx,4; mov rdx,0xAAAAAAAAAAAAAAAB; imul rcx,rdx (magic-mul, size/16); [rbp+0xF0]=rcx (count), [rbp+0xF8]=rax (base), [rsp+0x20]=r12; rcx=[rbp+0x828], rdx=&[rbp+0xF0], r8=[rbp+0x778], r9=&[rbp+0x2E0]; call 0x678F950. Ends at call; next instruction 0x677abb9.

```
0x677aad4  mov [rcx+0x10],eax                            ; W a0+0x10
0x677aad7  movups xmm0,[rbx+0x58]                        
0x677aadb  movups [rcx],xmm0                             ; W a0+0x0
0x677aade  movzx eax,byte ptr [rbp+0x25C]                
0x677aae5  mov [rbp+0x6C4],al                            
0x677aaeb  movups xmm0,[rbp+0x260]                       
0x677aaf2  movups [rbp+0x6C8],xmm0                       
0x677aaf9  movups xmm0,[rbx+0x80]                        
0x677ab00  movups xmm1,[rbx+0x90]                        
0x677ab07  movups xmm2,[rbx+0x9F]                        
0x677ab0e  lea rax,[rbp+0x574]                           
0x677ab15  movups [rax+0x183],xmm2                       
0x677ab1c  movups [rax+0x174],xmm1                       
0x677ab23  movups [rax+0x164],xmm0                       
0x677ab2a  movzx eax,word ptr [rbp+0x2A0]                
0x677ab31  mov [rbp+0x708],ax                            
0x677ab38  mov rcx,[rbp+0x768]                           
0x677ab3f  mov rax,[rcx+0x480]                           
0x677ab46  mov rdx,[rcx+0x488]                           
0x677ab4d  mov rcx,rdx                                   
0x677ab50  sub rcx,rax                                   
0x677ab53  cmp rcx,0xFFFFFFFFFFFFFFD0                    
0x677ab57  je 0x677E011                                  ; -> sub_677e011
0x677ab5d  test rax,rax                                  
0x677ab60  setne r8b                                     
0x677ab64  test rdx,rdx                                  
0x677ab67  sete dl                                       
0x677ab6a  or dl,r8b                                     
0x677ab6d  je 0x677E011                                  ; -> sub_677e011
0x677ab73  sar rcx,4                                     
0x677ab77  mov rdx,0xAAAAAAAAAAAAAAAB                    
0x677ab81  imul rcx,rdx                                  
0x677ab85  mov [rbp+0xF0],rcx                            
0x677ab8c  mov [rbp+0xF8],rax                            
0x677ab93  mov [rsp+0x20],r12                            
0x677ab98  mov rcx,[rbp+0x828]                           
0x677ab9f  lea rdx,[rbp+0xF0]                            
0x677aba6  mov r8,[rbp+0x778]                            
0x677abad  lea r9,[rbp+0x2E0]                            
0x677abb4  call 0x678F950                                ; -> sub_678f950
```

Interpretation: `mov [rcx+0x10],eax` — rcx=&[rbp+0x6B0], eax = zero-extended u16 [rbx+0x68] from Phase 122's last mov. Then the copy sequence mirrors Phase 121's: [rbp+0x6B0]=16 bytes from [rbx+0x58]; byte [rbp+0x25C]→[rbp+0x6C4]; [rbp+0x260]→[rbp+0x6C8] (16 bytes); [rbx+0x80],[rbx+0x90],[rbx+0x9F]→[rbp+0x574+0x164],[rbp+0x574+0x174],[rbp+0x574+0x183]; word [rbp+0x2A0]→[rbp+0x708]. Then bounds math on block [rbp+0x768]: size = [rbp+0x768+0x488] - [rbp+0x768+0x480]; reject if size == -48 (0xFFFFFFD0) or either pointer null → sub_677e011; else count = size/16 via sar 4 + imul magic 0xAAAAAAAAAAAAAAAB; store [rbp+0xF0]=count, [rbp+0xF8]=base, [rsp+0x20]=r12; call 0x678F950(rcx=[rbp+0x828], rdx=&[rbp+0xF0], r8=[rbp+0x778], r9=&[rbp+0x2E0]).

Callees: sub_677e011 (via je x2), 0x678F950 (sub_678f950).
Fields read: [rcx+0x10] addr ([rbp+0x6B0+0x10]), [rbx+0x58], [rcx] addr ([rbp+0x6B0]), [rbp+0x25C], [rbp+0x260], [rbx+0x80], [rbx+0x90], [rbx+0x9F], [rbp+0x574] (addr), [rbp+0x2A0], [rbp+0x768], [[rbp+0x768]+0x480], [[rbp+0x768]+0x488], [rbp+0x828], [rbp+0x778]. Fields written: [[rbp+0x6B0]+0x10] (as [rcx+0x10]), [rbp+0x6B0] (movups), [rbp+0x6C4], [rbp+0x6C8], [[rbp+0x574]+0x164], [[rbp+0x574]+0x174], [[rbp+0x574]+0x183], [rbp+0x708], [rbp+0xF0], [rbp+0xF8], [rsp+0x20].

## Phase 124 — nop + call 0x67E1840 + jmp sub_677dea0 + grow call 0x1EF6F90 ([r14+0x8A0]) + TLS x2 + counter shr1/dec [rbp+0x310] + TLS + cursor [r14+0x758] vs [r14+0x760] (grow loc_677acbd) + copy [rbp+0x6B8]→[r14+0x758] (u32+byte+float) (0x677abb9..0x677ac76)

Two flows from the Phase-123 call site: `nop; mov rcx,r12; call 0x67E1840; lea rcx,[rbp+0x110]; jmp 0x677DEA0` (exit path). Fall-through block at 0x677abce: `lea rcx,[r14+0x8A0]`, `lea r8,[rbp+0x710]`, call 0x1EF6F90 (grow helper). TLS read + mov dl,0x4A + call via [0xF99FFA0]. Counter: eax=[r14+0x8A8], sub [r14+0x8A0], shr 1, dec, [rbp+0x310]=ax. TLS read again; [rbp+0x838]=al. Cursor: rdx=[r14+0x758], cmp [r14+0x760] → je loc_677acbd (grow); else lea rcx,[rbp+0x6B8]; eax=[rbp+0x6B8+0x10]; [r14+0x758+0x10]=eax; movups [r14+0x758]=xmm0=[rbp+0x6B8] (16 bytes); movzx eax,byte [rbp+0x6CC]; [r14+0x758+0x14]=al; movss xmm0=[rbp+0x6D0]; [r14+0x758+0x18]=xmm0; movss xmm0=[rbp+0x6D4] (phase ends; continues next phase).

```
0x677abb9  nop                                           
0x677abba  mov rcx,r12                                   
0x677abbd  call 0x67E1840                                ; -> sub_67e1840
0x677abc2  lea rcx,[rbp+0x110]                           
0x677abc9  jmp 0x677DEA0                                 ; -> sub_677dea0
0x677abce  lea rcx,[r14+0x8A0]                           
0x677abd5  lea r8,[rbp+0x710]                            
0x677abdc  call 0x1EF6F90                                ; -> sub_1ef6f90
0x677abe1  nop                                           
0x677abe2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677abe9  mov rax,[rcx]                                 
0x677abec  mov rax,[rax+0x10]                            
0x677abf0  movzx edx,byte ptr [rbp+0x838]                
0x677abf7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677abfd  nop                                           
0x677abfe  mov eax,[r14+0x8A8]                           
0x677ac05  sub eax,[r14+0x8A0]                           
0x677ac0c  shr eax,1                                     
0x677ac0e  dec eax                                       
0x677ac10  mov [rbp+0x310],ax                            
0x677ac17  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677ac1e  mov rax,[rcx]                                 
0x677ac21  mov rax,[rax+0x10]                            
0x677ac25  mov dl,0x4A                                   
0x677ac27  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677ac2d  nop                                           
0x677ac2e  mov [rbp+0x838],al                            
0x677ac34  mov rdx,[r14+0x758]                           
0x677ac3b  cmp rdx,[r14+0x760]                           
0x677ac42  je short 0x677ACBD                            ; -> loc_677acbd
0x677ac44  lea rcx,[rbp+0x6B8]                           
0x677ac4b  mov eax,[rcx+0x10]                            
0x677ac4e  mov [rdx+0x10],eax                            
0x677ac51  movups xmm0,[rcx]                             
0x677ac54  movups [rdx],xmm0                             
0x677ac57  movzx eax,byte ptr [rbp+0x6CC]                
0x677ac5e  mov [rdx+0x14],al                             
0x677ac61  movss xmm0,[rbp+0x6D0]                        
0x677ac69  movss [rdx+0x18],xmm0                         
0x677ac6e  movss xmm0,[rbp+0x6D4]                        
```

Interpretation: `nop`; `mov rcx,r12`; call 0x67E1840; `lea rcx,[rbp+0x110]`; `jmp 0x677DEA0` (exit to sub_677dea0). Unreachable-from-here but listed block at 0x677abce (jump target from elsewhere): `lea rcx,[r14+0x8A0]`, `lea r8,[rbp+0x710]`, call 0x1EF6F90 (grow helper for cursor [r14+0x8A0] with data [rbp+0x710]). TLS read: rcx=[0x1233E1B0]→[rax]→[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0]. Counter: eax=[r14+0x8A8], sub [r14+0x8A0], shr 1, dec, [rbp+0x310]=ax. Second TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. Cursor bounds check: rdx=[r14+0x758], cmp [r14+0x760]; if equal jump to loc_677acbd (grow). Otherwise `lea rcx,[rbp+0x6B8]`, `mov eax,[rcx+0x10]` ([rbp+0x6B8+0x10]), `[rdx+0x10]=eax` ([r14+0x758+0x10]), `movups xmm0,[rcx]` ([rbp+0x6B8]), `movups [rdx],xmm0` ([r14+0x758], 16 bytes), `movzx eax,byte [rbp+0x6CC]`, `[rdx+0x14]=al` ([r14+0x758+0x14]), `movss xmm0,[rbp+0x6D0]`, `movss [rdx+0x18],xmm0` ([r14+0x758+0x18]), `movss xmm0,[rbp+0x6D4]`; phase ends there; next instruction 0x677ac76.

Callees: 0x67E1840 (sub_67e1840), 0x677DEA0 (sub_677dea0, via jmp), 0x1EF6F90 (sub_1ef6f90), [0xF99FFA0] = sub_eea6040 (indirect, 2x), loc_677acbd (grow, via je).
Fields read: r12, [rbp+0x110] (lea addr), r14, [r14+0x8A0] (lea addr), [rbp+0x710] (lea addr), [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [r14+0x8A8], [r14+0x8A0], [rbp+0x838] (2nd store), [r14+0x758], [r14+0x760], [rbp+0x6B8] (lea addr), [[rbp+0x6B8]+0x10], [rbp+0x6CC], [rbp+0x6D0], [rbp+0x6D4]. Fields written: [rbp+0x838] (x2), [rbp+0x310], [r14+0x758+0x10] (as [rdx+0x10]), [r14+0x758] (movups [rdx]), [r14+0x758+0x14], [r14+0x758+0x18].

## Phase 125 — Finish cursor record ([rdx+0x1C/0x20/0x24/0x28/0x38/0x47] writes, [r14+0x758]+=0x58, jmp loc_677acd1) + grow path 0x6760A80 at loc_677acbd + TLS + [rbp+0x300]=0x4001 + counter shr3/imul 0xFFFF8BA3 [rbp+0x32C] + TLS + next cursor cmp [r14+0x890]/[r14+0x898] (0x677ac76..0x677ad43)

rdx=[r14+0x758] (cursor, from Phase 124). `movss [rdx+0x1C],xmm0` (xmm0=[rbp+0x6D4]); `movss xmm0,[rbp+0x6D8]`; [rdx+0x20]; `movss xmm0,[rbp+0x6DC]`; [rdx+0x24]; `lea rax,[rbp+0x6E0]`; movups xmm0=[rbp+0x6E0], xmm1=[rbp+0x6F0], xmm2=[rbp+0x6FF]; [rdx+0x28]=xmm0, [rdx+0x38]=xmm1, [rdx+0x47]=xmm2; `add qword ptr [r14+0x758],0x58` (advance cursor by 0x58); `jmp short 0x677ACD1`. Grow path loc_677acbd (je target from Phase 124): `lea rcx,[r14+0x750]`, `lea r8,[rbp+0x6B8]`, call 0x6760A80. loc_677acd1: TLS read; `[rbp+0x300]=0x4001` (u64); counter: eax=[r14+0x758], sub [r14+0x750], shr 3, imul 0xFFFF8BA3, dec, [rbp+0x32C]=ax; TLS read, mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al; next cursor check: rdx=[r14+0x890], cmp [r14+0x898] (phase ends there).

```
0x677ac76  movss [rdx+0x1C],xmm0                         ; W a1+0x1C
0x677ac7b  movss xmm0,[rbp+0x6D8]                        
0x677ac83  movss [rdx+0x20],xmm0                         ; W a1+0x20
0x677ac88  movss xmm0,[rbp+0x6DC]                        
0x677ac90  movss [rdx+0x24],xmm0                         ; W a1+0x24
0x677ac95  lea rax,[rbp+0x6E0]                           
0x677ac9c  movups xmm0,[rax]                             
0x677ac9f  movups xmm1,[rax+0x10]                        
0x677aca3  movups xmm2,[rax+0x1F]                        
0x677aca7  movups [rdx+0x28],xmm0                        ; W a1+0x28
0x677acab  movups [rdx+0x38],xmm1                        ; W a1+0x38
0x677acaf  movups [rdx+0x47],xmm2                        ; W a1+0x47
0x677acb3  add qword ptr [r14+0x758],0x58                
0x677acbb  jmp short 0x677ACD1                           ; -> loc_677acd1
0x677acbd  lea rcx,[r14+0x750]                           
0x677acc4  lea r8,[rbp+0x6B8]                            
0x677accb  call 0x6760A80                                ; -> sub_6760a80
0x677acd0  nop                                           
0x677acd1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677acd8  mov rax,[rcx]                                 
0x677acdb  mov rax,[rax+0x10]                            
0x677acdf  movzx edx,byte ptr [rbp+0x838]                
0x677ace6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677acec  nop                                           
0x677aced  mov qword ptr [rbp+0x300],0x4001              
0x677acf8  mov eax,[r14+0x758]                           
0x677acff  sub eax,[r14+0x750]                           
0x677ad06  shr eax,3                                     
0x677ad09  imul eax,0xFFFF8BA3                           
0x677ad0f  dec eax                                       
0x677ad11  mov [rbp+0x32C],ax                            
0x677ad18  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677ad1f  mov rax,[rcx]                                 
0x677ad22  mov rax,[rax+0x10]                            
0x677ad26  mov dl,0x4A                                   
0x677ad28  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677ad2e  nop                                           
0x677ad2f  mov [rbp+0x838],al                            
0x677ad35  mov rdx,[r14+0x890]                           
0x677ad3c  cmp rdx,[r14+0x898]                           
```

Interpretation: completes the per-element record at [r14+0x758] (floats at +0x1C,+0x20,+0x24, 16-byte chunks at +0x28/+0x38/+0x47 from [rbp+0x6E0]/[rbp+0x6F0]/[rbp+0x6FF]), then advances cursor [r14+0x758] by 0x58 and jumps to loc_677acd1. If the cursor was full (je from Phase 124), loc_677acbd grows via lea rcx,[r14+0x750], lea r8,[rbp+0x6B8], call 0x6760A80. loc_677acd1 re-reads the TLS feature flag, stores [rbp+0x300]=0x4001, computes count=([r14+0x758]-[r14+0x750])/8 via shr 3 + imul 0xFFFF8BA3 magic, stores [rbp+0x32C]=ax, re-reads TLS flag into [rbp+0x838], then checks the next cursor rdx=[r14+0x890] vs [r14+0x898]; phase ends at cmp.

Callees: 0x6760A80 (sub_6760a80), [0xF99FFA0] = sub_eea6040 (indirect, 2x), loc_677acd1 (via jmp).
Fields read: xmm0=[rbp+0x6D4] (carried), [rbp+0x6D8], [rbp+0x6DC], [rbp+0x6E0], [[rbp+0x6E0]+0x10], [[rbp+0x6E0]+0x1F], [r14+0x758], [r14+0x750], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838], [rbp+0x758] (again), [rbp+0x750], [rbp+0x838] (again), [r14+0x890], [r14+0x898]. Fields written: [r14+0x758+0x1C], [r14+0x758+0x20], [r14+0x758+0x24], [r14+0x758+0x28], [r14+0x758+0x38], [r14+0x758+0x47], [r14+0x758] (add 0x58), [rbp+0x300], [rbp+0x32C], [rbp+0x838].

## Phase 126 — Cursor [r14+0x890] inc/grow (0x6760E60) + TLS + not+add counter [rbp+0x312] + TLS + cursor [r14+0x7A0] inc/grow (0x6760E60) + TLS + [rbp+0x300]=0x4803 (0x677ad43..0x677adfd)

From Phase 125's cmp rdx,[r14+0x898]: if equal → loc_677ad51: `lea rcx,[r14+0x888]`, call 0x6760E60 (grow); else `inc rdx`, `[r14+0x890]=rdx`, jmp loc_677ad5e. loc_677ad5e: TLS read, call via [0xF99FFA0]; counter: eax=[r14+0x888], not eax, add eax,[r14+0x890], [rbp+0x312]=ax; TLS read; [rbp+0x838]=al. Cursor 2: rdx=[r14+0x7A0], cmp [r14+0x7A8] → je loc_677adca: `lea rcx,[r14+0x798]`, call 0x6760E60 (grow); else `inc rdx`, `[r14+0x7A0]=rdx`, jmp loc_677add7. loc_677add7: TLS read; `[rbp+0x300]=0x4803` (u64); phase ends there; next instruction 0x677adfd.

```
0x677ad43  je short 0x677AD51                            ; -> loc_677ad51
0x677ad45  inc rdx                                       
0x677ad48  mov [r14+0x890],rdx                           
0x677ad4f  jmp short 0x677AD5E                           ; -> loc_677ad5e
0x677ad51  lea rcx,[r14+0x888]                           
0x677ad58  call 0x6760E60                                ; -> sub_6760e60
0x677ad5d  nop                                           
0x677ad5e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677ad65  mov rax,[rcx]                                 
0x677ad68  mov rax,[rax+0x10]                            
0x677ad6c  movzx edx,byte ptr [rbp+0x838]                
0x677ad73  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677ad79  nop                                           
0x677ad7a  mov eax,[r14+0x888]                           
0x677ad81  not eax                                       
0x677ad83  add eax,[r14+0x890]                           
0x677ad8a  mov [rbp+0x312],ax                            
0x677ad91  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677ad98  mov rax,[rcx]                                 
0x677ad9b  mov rax,[rax+0x10]                            
0x677ad9f  mov dl,0x4A                                   
0x677ada1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677ada7  nop                                           
0x677ada8  mov [rbp+0x838],al                            
0x677adae  mov rdx,[r14+0x7A0]                           
0x677adb5  cmp rdx,[r14+0x7A8]                           
0x677adbc  je short 0x677ADCA                            ; -> loc_677adca
0x677adbe  inc rdx                                       
0x677adc1  mov [r14+0x7A0],rdx                           
0x677adc8  jmp short 0x677ADD7                           ; -> loc_677add7
0x677adca  lea rcx,[r14+0x798]                           
0x677add1  call 0x6760E60                                ; -> sub_6760e60
0x677add6  nop                                           
0x677add7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677adde  mov rax,[rcx]                                 
0x677ade1  mov rax,[rax+0x10]                            
0x677ade5  movzx edx,byte ptr [rbp+0x838]                
0x677adec  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677adf2  nop                                           
0x677adf3  mov qword ptr [rbp+0x300],0x4803              
```

Interpretation: cursor bounds checks with grow paths (0x6760E60) for two cursors ([r14+0x890]/[r14+0x898] and [r14+0x7A0]/[r14+0x7A8]), each with inc-store on success. Between them: not+add counter ([r14+0x888] not'd, + [r14+0x890]) → [rbp+0x312]. TLS feature-flag reads via [0xF99FFA0] with [rbp+0x838] stores surround each counter. Ends with [rbp+0x300]=0x4803, leading into the next counter/cursor block at 0x677adfd.

Callees: 0x6760E60 (sub_6760e60, 2x), [0xF99FFA0] = sub_eea6040 (indirect, 2x), loc_677ad51 (grow via je), loc_677ad5e (via jmp), loc_677adca (grow via je), loc_677add7 (via jmp).
Fields read: [r14+0x890], [r14+0x898], [r14+0x888], [r14+0x890] (2nd), [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838] (x2), [r14+0x7A0], [r14+0x7A8]. Fields written: [r14+0x890] (inc path), [rbp+0x312], [rbp+0x838] (x2), [r14+0x7A0] (inc path), [rbp+0x300].

## Phase 127 — Four odd add/xchg/rol/xchg instructions ([?]) + mov [rbp+0x326],eax + TLS + call 0x675FB30 + TLS + counter shr3/imul 0xFFFF8E39 [rbp+0x342] + call 0x675F3B0 + counter shr3/imul 0xFFFF8BA3 [rbp+0x328] + TLS (0x677adfd..0x677aec3)

Opens with four unusual instructions (`add [rcx-0x75],al`, `xchg [rax-0x8FFFFF9],bl`, `rol byte ptr [rcx+3],1`, `xchg [rax+0x66000007],ah`) — meaning unclear ([?], possibly data or real code). Then `mov [rbp+0x326],eax`. TLS read + mov dl,0x4A + call via [0xF99FFA0] + [rbp+0x838]=al. `lea rcx,[r14+0x648]`, `lea rdx,[rbp+0x660]`, call 0x675FB30. TLS read; movzx edx,byte [rbp+0x838]; call via [0xF99FFA0]; [rbp+0x838]=al. Counter 1: eax=[r14+0x650], sub [r14+0x648], shr 3, imul 0xFFFF8E39, dec, [rbp+0x342]=ax. `lea rcx,[r14+0x780]`, `lea rdx,[rbp+0x608]`, call 0x675F3B0. Counter 2: eax=[r14+0x788], sub [r14+0x780], shr 3, imul 0xFFFF8BA3, dec, [rbp+0x328]=ax. TLS read: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10]; phase ends there; next instruction 0x677aec3.

```
0x677adfd  add [rcx-0x75],al                             ; W a0-0x75
0x677ae00  xchg [rax-0x8FFFFF9],bl                       
0x677ae06  rol byte ptr [rcx+3],1                        ; W a0+0x3
0x677ae09  xchg [rax+0x66000007],ah                      
0x677ae0f  mov [rbp+0x326],eax                           
0x677ae15  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677ae1c  mov rax,[rcx]                                 
0x677ae1f  mov rax,[rax+0x10]                            
0x677ae23  mov dl,0x4A                                   
0x677ae25  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677ae2b  mov [rbp+0x838],al                            
0x677ae31  lea rcx,[r14+0x648]                           
0x677ae38  lea rdx,[rbp+0x660]                           
0x677ae3f  call 0x675FB30                                ; -> sub_675fb30
0x677ae44  nop                                           
0x677ae45  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
0x677ae4c  mov rax,[rcx]                                 
0x677ae4f  mov rax,[rax+0x10]                            
0x677ae53  movzx edx,byte ptr [rbp+0x838]                
0x677ae5a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677ae60  nop                                           
0x677ae61  mov eax,[r14+0x650]                           
0x677ae68  sub eax,[r14+0x648]                           
0x677ae6f  shr eax,3                                     
0x677ae72  imul eax,0xFFFF8E39                           
0x677ae78  dec eax                                       
0x677ae7a  mov [rbp+0x342],ax                            
0x677ae81  lea rcx,[r14+0x780]                           
0x677ae88  lea rdx,[rbp+0x608]                           
0x677ae8f  call 0x675F3B0                                ; -> sub_675f3b0
0x677ae94  nop                                           
0x677ae95  mov eax,[r14+0x788]                           
0x677ae9c  sub eax,[r14+0x780]                           
0x677aea3  shr eax,3                                     
0x677aea6  imul eax,0xFFFF8BA3                           
0x677aeac  dec eax                                       
0x677aeae  mov [rbp+0x328],ax                            
0x677aeb5  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677aebc  mov rax,[rcx]                                 
0x677aebf  mov rax,[rax+0x10]                            
```

Interpretation: `add [rcx-0x75],al`; `xchg [rax-0x8FFFFF9],bl`; `rol byte ptr [rcx+3],1`; `xchg [rax+0x66000007],ah` — unusual instructions at 0x677adfd..0x677ae0f ([?]). Then `mov [rbp+0x326],eax`. TLS: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10], mov dl,0x4A, call via [0xF99FFA0], [rbp+0x838]=al. `lea rcx,[r14+0x648]`, `lea rdx,[rbp+0x660]`, call 0x675FB30. TLS again: rcx=[0x1233E1B0]→[rax]→[rax+0x10], movzx edx,byte [rbp+0x838], call via [0xF99FFA0], [rbp+0x838]=al. Counter 1: eax=[r14+0x650], sub [r14+0x648], shr 3, imul 0xFFFF8E39, dec, [rbp+0x342]=ax. `lea rcx,[r14+0x780]`, `lea rdx,[rbp+0x608]`, call 0x675F3B0. Counter 2: eax=[r14+0x788], sub [r14+0x780], shr 3, imul 0xFFFF8BA3, dec, [rbp+0x328]=ax. TLS: rcx=[0x1233E1B0], rax=[rcx], rax=[rax+0x10]; ends; next instruction 0x677aec3.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 2x), 0x675FB30 (sub_675fb30), 0x675F3B0 (sub_675f3b0).
Fields read: [rcx-0x75], [rax-0x8FFFFF9], [rcx+3], [rax+0x66000007], eax, [rbp+0x838], r14+0x648 (lea addr), rbp+0x660 (lea addr), [rbp+0x838] (2nd read), [r14+0x650], [r14+0x648], [r14+0x788], [r14+0x780], [0x1233E1B0], [rcx], [rax+0x10]. Fields written: [rcx-0x75] (add), [rax-0x8FFFFF9] (xchg), [rcx+3] (rol), [rax+0x66000007] (xchg), [rbp+0x326], [rbp+0x838] (x2), [rbp+0x342], [rbp+0x328].

## Phase 128 — TLS tail (mov [rbp+0x838],al) + append element at [r14+0x770] (store [rbp+0x580], call 0xE869FF0, store [rbp+0x600], zero, +0x88) + grow path 0x6760710 + TLS + [rbp+0x300]=0x2007803 + counter shr3/imul 0xFFFFF0F1 [rbp+0x32A] + TLS (0x677aec3..0x677af96)

Tail of Phase-127 TLS: `mov dl,0x4A`, call via [0xF99FFA0], `[rbp+0x838]=al`. Append: r15=[r14+0x770]; cmp [r14+0x778]; if equal → loc_677af22 grow path (`lea rcx,[r14+0x768]`, `mov rdx,r15`, `lea r8,[rbp+0x580]`, call 0x6760710). Else `[r15]=[rbp+0x580]`, `rcx=r15+8`, `rdx=&[rbp+0x588]`, call 0xE869FF0, `[r15+0x80]=[rbp+0x600]`, `[rbp+0x600]=0`, `[r14+0x770]+=0x88`, jmp loc_677af39. loc_677af39: TLS read; `[rbp+0x300]=0x2007803` (u64); counter: eax=[r14+0x770], sub [r14+0x768], shr 3, imul 0xFFFFF0F1, dec, [rbp+0x32A]=ax; TLS read, mov dl,0x4A, call via [0xF99FFA0] (continues next phase).

```
0x677aec3  mov dl,0x4A                                   
0x677aec5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677aecb  mov [rbp+0x838],al                            
0x677aed1  mov r15,[r14+0x770]                           
0x677aed8  cmp r15,[r14+0x778]                           
0x677aedf  je short 0x677AF22                            ; -> loc_677af22
0x677aee1  mov rax,[rbp+0x580]                           
0x677aee8  mov [r15],rax                                 
0x677aeeb  lea rcx,[r15+8]                               
0x677aeef  lea rdx,[rbp+0x588]                           
0x677aef6  call 0xE869FF0                                ; -> sub_e869ff0
0x677aefb  nop                                           
0x677aefc  mov rax,[rbp+0x600]                           
0x677af03  mov [r15+0x80],rax                            
0x677af0a  mov qword ptr [rbp+0x600],0                   
0x677af15  add qword ptr [r14+0x770],0x88                
0x677af20  jmp short 0x677AF39                           ; -> loc_677af39
0x677af22  lea rcx,[r14+0x768]                           
0x677af29  mov rdx,r15                                   
0x677af2c  lea r8,[rbp+0x580]                            
0x677af33  call 0x6760710                                ; -> sub_6760710
0x677af38  nop                                           
0x677af39  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677af40  mov rax,[rcx]                                 
0x677af43  mov rax,[rax+0x10]                            
0x677af47  movzx edx,byte ptr [rbp+0x838]                
0x677af4e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677af54  nop                                           
0x677af55  mov qword ptr [rbp+0x300],0x2007803           
0x677af60  mov eax,[r14+0x770]                           
0x677af67  sub eax,[r14+0x768]                           
0x677af6e  shr eax,3                                     
0x677af71  imul eax,0xFFFFF0F1                           
0x677af77  dec eax                                       
0x677af79  mov [rbp+0x32A],ax                            
0x677af80  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677af87  mov rax,[rcx]                                 
0x677af8a  mov rax,[rax+0x10]                            
0x677af8e  mov dl,0x4A                                   
0x677af90  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

Interpretation: completes the TLS feature-flag read from Phase 127 (mov dl,0x4A; call via [0xF99FFA0]; [rbp+0x838]=al). Element append at cursor r15=[r14+0x770] vs end [r14+0x778]: full → grow (loc_677af22: lea rcx,[r14+0x768], mov rdx,r15, lea r8,[rbp+0x580], call 0x6760710); else store [rbp+0x580] at [r15], call 0xE869FF0(rcx=r15+8, rdx=&[rbp+0x588]), store [rbp+0x600] at [r15+0x80], zero [rbp+0x600], advance [r14+0x770] by 0x88, jump loc_677af39. loc_677af39: TLS read, [rbp+0x300]=0x2007803, counter eax=([r14+0x770]-[r14+0x768])>>1 magic-mul 0xFFFFF0F1, dec → [rbp+0x32A]=ax, then TLS read with mov dl,0x4A and call via [0xF99FFA0] at phase end; next instruction 0x677af96.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 2x), 0xE869FF0 (sub_e869ff0), 0x6760710 (sub_6760710), loc_677af22 (grow via je), loc_677af39 (via jmp).
Fields read: [rbp+0x838], [r14+0x770], [r14+0x778], [rbp+0x580], r15, [rbp+0x588] (addr), [rbp+0x600], [r14+0x770] (again), [rbp+0x768] (addr), r15 (mov rdx), [rbp+0x580] (addr), [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838] (2nd), [r14+0x770] (3rd), [r14+0x768]. Fields written: [rbp+0x838], [r15], [r15+0x80], [rbp+0x600], [r14+0x770], [rbp+0x300], [rbp+0x32A].

## Phase 129 — TLS tail ([rbp+0x838]=al) + cursor [r14+0x680] vs [r14+0x688] (movss x3 + +0xC, or grow 0x1770A70) + counter shr2/imul 0xFFFFAAAB [rbp+0x33E] + TLS + [rbp+0x838]=al + cursor [r14+0x518] vs [r14+0x520] (inc path starts) (0x677af96..0x677b05d)

Tail of Phase-128 TLS: `nop`, `mov [rbp+0x838],al`. Cursor: rdx=[r14+0x680], cmp [r14+0x688]; if equal → loc_677afdd: `lea rcx,[r14+0x678]`, `lea r8,[rbp+0x574]`, call 0x1770A70 (grow). Else `movss [rdx]=[rbp+0x574]`, `movss [rdx+4]=[rbp+0x578]`, `movss [rdx+8]=[rbp+0x57C]`, `[r14+0x680]+=0xC`, jmp loc_677aff1. loc_677aff1: TLS read; counter eax=[r14+0x680], sub [r14+0x678], shr 2, imul 0xFFFFAAAB, dec, [rbp+0x33E]=ax; TLS read; [rbp+0x838]=al. Next cursor: rdx=[r14+0x518], cmp [r14+0x520] → je loc_677b066; else `inc rdx` (phase ends; continues next phase).

```
0x677af96  nop                                           
0x677af97  mov [rbp+0x838],al                            
0x677af9d  mov rdx,[r14+0x680]                           
0x677afa4  cmp rdx,[r14+0x688]                           
0x677afab  je short 0x677AFDD                            ; -> loc_677afdd
0x677afad  movss xmm0,[rbp+0x574]                        
0x677afb5  movss [rdx],xmm0                              
0x677afb9  movss xmm0,[rbp+0x578]                        
0x677afc1  movss [rdx+4],xmm0                            
0x677afc6  movss xmm0,[rbp+0x57C]                        
0x677afce  movss [rdx+8],xmm0                            
0x677afd3  add qword ptr [r14+0x680],0xC                 
0x677afdb  jmp short 0x677AFF1                           ; -> loc_677aff1
0x677afdd  lea rcx,[r14+0x678]                           
0x677afe4  lea r8,[rbp+0x574]                            
0x677afeb  call 0x1770A70                                ; -> sub_1770a70
0x677aff0  nop                                           
0x677aff1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677aff8  mov rax,[rcx]                                 
0x677affb  mov rax,[rax+0x10]                            
0x677afff  movzx edx,byte ptr [rbp+0x838]                
0x677b006  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677b00c  nop                                           
0x677b00d  mov eax,[r14+0x680]                           
0x677b014  sub eax,[r14+0x678]                           
0x677b01b  shr eax,2                                     
0x677b01e  imul eax,0xFFFFAAAB                           
0x677b024  dec eax                                       
0x677b026  mov [rbp+0x33E],ax                            
0x677b02d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x677b034  mov rax,[rcx]                                 
0x677b037  mov rax,[rax+0x10]                            
0x677b03b  mov dl,0x4A                                   
0x677b03d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x677b043  nop                                           
0x677b044  mov [rbp+0x838],al                            
0x677b04a  mov rdx,[r14+0x518]                           
0x677b051  cmp rdx,[r14+0x520]                           
0x677b058  je short 0x677B066                            ; -> loc_677b066
0x677b05a  inc rdx                                       
```

Interpretation: completes Phase-128's TLS flag store. Cursor bounds check [r14+0x680] vs [r14+0x688]: full → grow via call 0x1770A70 (rcx=[r14+0x678], r8=[rbp+0x574]); else write 3 floats [rbp+0x574],[rbp+0x578],[rbp+0x57C] at [r14+0x680]..+8 and advance cursor by 0xC. Then counter: size=([r14+0x680]-[r14+0x678])>>1 via shr 2 + imul 0xFFFFAAAB magic, dec → [rbp+0x33E]=ax. TLS feature flag → [rbp+0x838]. Then next cursor check rdx=[r14+0x518] vs [r14+0x520]: equal → loc_677b066; else inc rdx; next instruction 0x677b05d.

Callees: [0xF99FFA0] = sub_eea6040 (indirect, 2x), 0x1770A70 (sub_1770a70), loc_677afdd (grow via je), loc_677aff1 (via jmp), loc_677b066 (via je).
Fields read: [rbp+0x838], [r14+0x680], [r14+0x688], [rbp+0x574], [rbp+0x578], [rbp+0x57C], [r14+0x680] (2nd), [r14+0x678], [0x1233E1B0], [rcx], [rax+0x10], [rbp+0x838] (2nd), [rbp+0x680], [rbp+0x678], [r14+0x518], [r14+0x520]. Fields written: [rbp+0x838], [r14+0x680] (movss x3), [r14+0x680] (add), [rbp+0x33E], [rbp+0x838] (2nd), rdx (inc).

## NEXT
Resume at 0x677b05d (Phase 130) — after `inc rdx` at 0x677b05a. Covered 0x677af96..0x677b05d (Phase 129, 40 instructions). Function span: [0x67762e0..0x677e166).

---
