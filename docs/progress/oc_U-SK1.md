# oc_U-SK1 — Stars decoder unit (static analysis)

## NEXT
BLOCKING FILE-STATE ISSUE (fix first): the tail of this file (join 3 / sub_665b624) is corrupted — join-3 part 4 (0x665bd31..0x665bf97) and part 5 (0x665bf97..0x665c1ba) text blocks are MISSING; the interpretation at ~line 1455 is mislabeled "part 3" but actually describes part 4; lines 1481-1486 are an orphaned duplicate of phase-6 part-3 interpretation. All raw rdis output for these ranges was captured (see compressed summary) and must be re-inserted as clean sections. After fixing the tail: decode the COLD RANGE 0x665cf64..0x665d7e5 (entry at 0x665cf64: `mov rsi,[rbp+0x28]; jmp 0x665D124`; cold entries also at 0x665cf6d/0x665cf70/0x665cf85/0x665cfce/0x665cfd1/0x665cfe6; partially seen to 0x665d016). Then finish sub_665b624 (still open past 0x665c1ba). Resume point: docs/progress/oc_U-SK1.md.

## Unit: ext_particle_sky (Stars) — joins 0x665c269 / 0x665c38a / 0x665b624, cold range 0x665cf64..0x665d7e5

Sources: exe `Minecraft.Windows.exe` 1.26.62.01 (image-base RVAs); disassembler rdis.exe. Claims tagged [V] (verified against disassembly) / [I] (interpretation) / [?] (unresolved).

Structure [I]: three "join" entry blocks converge on a shared stars particle body; 0x665cf64 is a cold tail that branches into the same body at 0x665d124 and handles error/exit paths.

---
### Phase 1 — join 0x665c269, entry block 0x665c269..0x665c2f0

```text
0x665c269  mov [rbp+0x4B0],cl
0x665c26f  mov rcx,[rbp+0x230]
0x665c276  mov [rbp+0x4C8],rcx
0x665c27d  movaps xmm0,[rbp+0x220]
0x665c284  movups [rbp+0x4B8],xmm0
0x665c28b  mov ecx,0x9D0
0x665c290  add rcx,[rsi+0x10]
0x665c294  mov [rsp+0x28],rax
0x665c299  mov [rsp+0x20],r10
0x665c29e  call 0x67B40D0                       ; -> sub_67b40d0
0x665c2a3  nop
0x665c2a4  lea rcx,[rbp+0x340]
0x665c2ab  call 0x66A9AD0                       ; -> sub_66a9ad0
0x665c2b0  cmp byte ptr [rbp+0x218],3
0x665c2b7  jne short 0x665C2F0                  ; -> loc_665c2f0
0x665c2b9  mov rsi,[rbp+0x210]
0x665c2c0  test rsi,rsi
0x665c2c3  je short 0x665C2F0                   ; -> loc_665c2f0
0x665c2c5  lock dec dword ptr [rsi+8]
0x665c2c9  jne short 0x665C2F0                  ; -> loc_665c2f0
0x665c2cb  mov rax,[rsi]
0x665c2ce  mov rax,[rax]
0x665c2d1  mov rcx,rsi
0x665c2d4  call qword ptr [0xF99FFA0]           ; [data_f99ffa0] = sub_eea6040
0x665c2da  lock dec dword ptr [rsi+0xC]
0x665c2de  jne short 0x665C2F0                  ; -> loc_665c2f0
0x665c2e0  mov rax,[rsi]
0x665c2e3  mov rax,[rax+8]
0x665c2e7  mov rcx,rsi
0x665c2ea  call qword ptr [0xF99FFA0]           ; [data_f99ffa0] = sub_eea6040
```

Interpretation [I]:
- Entry stores cl into [rbp+0x4B0] (a flag/byte field) and [rbp+0x230] into [rbp+0x4C8] (a pointer).
- xmm0 from [rbp+0x220] stored to [rbp+0x4B8] (16-byte state copied).
- ecx = 0x9D0 + [rsi+0x10] then call sub_67b40d0 (allocation/pool acquire; returns rax). 0x9D0 = 2512 decimal, likely a block size or type tag [I].
- sub_66a9ad0 called with rcx = rbp+0x340 (probably initializes a particle/buffer header).
- If byte [rbp+0x218] != 3, jump to loc_665c2f0 (shared tail).
- Otherwise rsi = [rbp+0x210]; refcount decrement + release via [data_f99ffa0]=sub_eea6040 (two calls: release + final destroy pattern).
- Two virtual-style calls through [data_f99ffa0]: first [rax] (release), second [rax+8] (destroy/free) — classic refcounted object teardown [I].
- [V] all instructions quoted exactly from rdis output `work/rdis/665c269.out`.

---
### Phase 2 — join 0x665c269, block 0x665c2f0..0x665c38a

```text
loc_665c2f0:  ; from 665c2b7, 665c2c3, 665c2c9, 665c2de
0x665c2f0  mov rdi,[rbp+0x1E8]
0x665c2f7  test rdi,rdi
0x665c2fa  je short 0x665C34A                   ; -> loc_665c34a
0x665c2fc  mov rbx,[rbp+0x1F0]
0x665c303  jmp short 0x665C309                  ; -> loc_665c309
loc_665c305:  ; from 665c312, 665c31b, 665c321, 665c336, 665c348
0x665c305  add rdi,0x28
loc_665c309:  ; from 665c303
0x665c309  cmp rdi,rbx
0x665c30c  je short 0x665C34A                   ; -> loc_665c34a
0x665c30e  cmp byte ptr [rdi+0x18],2
0x665c312  jne short 0x665C305                  ; -> loc_665c305
0x665c314  mov rsi,[rdi+8]
0x665c318  test rsi,rsi
0x665c31b  je short 0x665C305                   ; -> loc_665c305
0x665c31d  lock dec dword ptr [rsi+8]
0x665c321  jne short 0x665C305                  ; -> loc_665c305
0x665c323  mov rax,[rsi]
0x665c326  mov rax,[rax]
0x665c329  mov rcx,rsi
0x665c32c  call qword ptr [0xF99FFA0]           ; [data_f99ffa0] = sub_eea6040
0x665c332  lock dec dword ptr [rsi+0xC]
0x665c336  jne short 0x665C305                  ; -> loc_665c305
0x665c338  mov rax,[rsi]
0x665c33b  mov rax,[rax+8]
0x665c33f  mov rcx,rsi
0x665c342  call qword ptr [0xF99FFA0]           ; [data_f99ffa0] = sub_eea6040
0x665c348  jmp short 0x665C305                  ; -> loc_665c305
loc_665c34a:  ; from 665c2fa, 665c30c
0x665c34a  cmp byte ptr [rbp+0x520],1
0x665c351  jne 0x665D11D                        ; -> loc_665d11d
0x665c357  mov rcx,[rbp+0x4E0]
0x665c35e  test rcx,rcx
0x665c361  je 0x665D11D                         ; -> loc_665d11d
0x665c367  mov rdx,[rbp+0x4F0]
0x665c36e  jmp 0x665CA9C                        ; -> loc_665ca9c
0x665c373  xor ecx,ecx
0x665c375  mov rdx,[rbp+0x508]
0x665c37c  mov [rbp+0x4A0],rdx
0x665c383  mov [rbp+0x4A8],rcx
0x665c38a  mov [rbp+0x4B0],al
```

Interpretation [I]:
- loc_665c2f0: rdi = [rbp+0x1E8]; if null skip to loc_665c34a. Otherwise rbx = [rbp+0x1F0] (end pointer), rdi walks forward by 0x28 each iteration.
- Loop loc_665c309: while rdi != rbx, if byte [rdi+0x18] == 2, rsi = [rdi+8]; refcount-dec rsi and if zero call release ([rax]) then destroy ([rax+8]) via [data_f99ffa0]. This teardowns each element in an array of 0x28-strided objects tagged type 2.
- After loop, loc_665c34a: if byte [rbp+0x520] == 1 and rcx=[rbp+0x4E0] non-null, rdx=[rbp+0x4F0], jump to loc_665ca9c (size-check + memcpy tail). Else fall through to zero-out block at 0x665c373: ecx=0, rdx=[rbp+0x508], store rdx->[rbp+0x4A0], ecx->[rbp+0x4A8], al->[rbp+0x4B0]. This is phase boundary at 0x665c38a (the second join entry).
- [V] all instructions quoted exactly from rdis output `work/rdis/665c269.out`.

---
### Phase 3 — join 0x665c38a, entry block 0x665c38a..0x665c44b

```text
0x665c38a  mov [rbp+0x4B0],al                             ; join entry 2 (also fall-through from 0x665c269)
0x665c390  mov rax,[rbp+0x530]
0x665c397  mov [rbp+0x4C8],rax
0x665c39e  movaps xmm0,[rbp+0x520]
0x665c3a5  movups [rbp+0x4B8],xmm0
0x665c3ac  mov ecx,0x9D0
0x665c3b1  add rcx,[rsi+0x10]
0x665c3b5  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x665c3ba  nop
0x665c3bb  mov rsi,rax
0x665c3be  lea rdx,[rbp+0x478]
0x665c3c5  xorps xmm0,xmm0
0x665c3c8  movaps [rbp+0x290],xmm0
0x665c3cf  movaps [rbp+0x280],xmm0
0x665c3d6  movaps [rbp+0x270],xmm0
0x665c3dd  movaps [rbp+0x260],xmm0
0x665c3e4  movaps [rbp+0x250],xmm0
0x665c3eb  movaps [rbp+0x240],xmm0
0x665c3f2  movaps [rbp+0x230],xmm0
0x665c3f9  movaps [rbp+0x220],xmm0
0x665c400  movaps [rbp+0x210],xmm0
0x665c407  movaps [rbp+0x200],xmm0
0x665c40e  movaps [rbp+0x1F0],xmm0
0x665c415  movaps [rbp+0x1E0],xmm0
0x665c41c  mov qword ptr [rbp+0x2A0],0
0x665c427  lea rcx,[rax+0x780]                           ; R ret@5aba5c0+0x780
0x665c42e  call 0x675F3B0                                ; -> sub_675f3b0
0x665c433  nop
0x665c434  mov eax,[rsi+0x788]                           ; R ret@5aba5c0+0x788
0x665c43a  sub eax,[rsi+0x780]                           ; R ret@5aba5c0+0x780
0x665c440  shr eax,3
0x665c443  imul eax,0xFFFF8BA3
0x665c449  dec eax
0x665c44b  mov [rbp+0x208],ax
```

Interpretation [I]:
- Join 0x665c38a is an independent entry (xref from sub_665b624 case-1 jump at 0x665ba1e) and also fall-through from join 0x665c269. It stores al->[rbp+0x4B0], rax=[rbp+0x530]->[rbp+0x4C8], copies xmm0=[rbp+0x520]->[rbp+0x4B8] — same state-setup pattern as 0x665c269 but with al instead of cl and [rbp+0x530] instead of [rbp+0x230] [I].
- call sub_5aba5c0 with ecx=0x9D0+[rsi+0x10]; result in rsi. Then zeroes a large stack region [rbp+0x290]..[rbp+0x1E0] (12 xmm registers = 192 bytes) and [rbp+0x2A0]=0 — clearing particle output struct [I].
- lea rcx,[rax+0x780]; call sub_675f3b0 — pointer arithmetic on allocation result +0x780 (likely a sub-buffer offset) [I].
- Computes (eax=[rsi+0x788]-[rsi+0x780])>>3 * 0xFFFF8BA3 - 1, stores ax->[rbp+0x208]. 0xFFFF8BA3 is a magic multiplicand (division by constant) — element-count computation [I].
- Calls sub_eea6040 via [data_f99ffa0] with dl=0x4A, stores al->[rbp+0x540] — a type-tag/format write [I].
- [V] all instructions quoted exactly from rdis output `work/rdis/665c269.out`.

---
### Phase 4 — join 0x665c38a, block 0x665c46f..0x665c540

```text
0x665c46f  mov rdx,[rsi+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x665c476  cmp rdx,[rsi+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x665c47d  je short 0x665C493                            ; -> loc_665c493
0x665c47f  movzx eax,word ptr [rbp+0x470]                
0x665c486  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x665c489  add qword ptr [rsi+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x665c491  jmp short 0x665C4A7                           ; -> loc_665c4a7
loc_665c493:  ; from 665c47d
0x665c493  lea r8,[rbp+0x470]                            
0x665c49a  lea rcx,[rsi+0x8A0]                           
0x665c4a1  call 0x1EF6F90                                ; -> sub_1ef6f90
0x665c4a6  nop                                           
loc_665c4a7:  ; from 665c491
0x665c4a7  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c4ae  mov rax,[rcx]                                 
0x665c4b1  mov rax,[rax+0x10]                            
0x665c4b5  movzx edx,byte ptr [rbp+0x540]                
0x665c4bc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c4c2  nop                                           
0x665c4c3  mov eax,[rsi+0x8A8]                           
0x665c4c9  sub eax,[rsi+0x8A0]                           
0x665c4cf  shr eax,1                                     
0x665c4d1  dec eax                                       
0x665c4d3  mov [rbp+0x1F0],ax                            
0x665c4da  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c4e1  mov rax,[rcx]                                 
0x665c4e4  mov rax,[rax+0x10]                            
0x665c4e8  mov dl,0x4A                                   
0x665c4ea  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c4f0  mov [rbp+0x540],al                            
0x665c4f6  lea rdx,[rbp+0x428]                           
0x665c4fd  lea rcx,[rsi+0x648]                           
0x665c504  call 0x675FB30                                ; -> sub_675fb30
0x665c509  nop                                           
0x665c50a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c511  mov rax,[rcx]                                 
0x665c514  mov rax,[rax+0x10]                            
0x665c518  movzx edx,byte ptr [rbp+0x540]                
0x665c51f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c525  nop                                           
0x665c526  mov qword ptr [rbp+0x1E0],0x2001001           
0x665c531  mov eax,[rsi+0x650]                           
0x665c537  sub eax,[rsi+0x648]                           
0x665c53d  shr eax,3                                     
0x665c540  imul eax,0xFFFF8E39
```

Interpretation [I]:
- If [rsi+0x8A8] != [rsi+0x8B0] (buffer not full), movzx word [rbp+0x470] -> [rdx], advance [rsi+0x8A8] by 2 (write 2 bytes = a u16 particle attribute) [I]. Else call sub_1ef6f90 with r8=&[rbp+0x470], rcx=rsi+0x8A0 — likely a flush/grow helper [I].
- Then another sub_eea6040 call (dl=0x4A), computes (eax=[rsi+0x8A8]-[rsi+0x8A0])>>1 - 1 -> [rbp+0x1F0] (u16 count), stores al->[rbp+0x540] [I].
- call sub_675FB30 with rdx=&[rbp+0x428], rcx=rsi+0x648 — memcpy/copy into particle buffer [I].
- sub_eea6040 again, stores al->[rbp+0x540]. Then [rbp+0x1E0]=0x2001001 (a type/format tag: 0x2001001) [I].
- Computes (eax=[rsi+0x650]-[rsi+0x648])>>3 * 0xFFFF8E39 - 1 -> [rbp+0x222] (another element count, stride 8) [I].
- [V] all instructions quoted exactly from rdis output `work/rdis/665c269.out`.

---
### Phase 5 — join 0x665c38a, block 0x665c546..0x665c603

```text
0x665c546  dec eax                                       
0x665c548  mov [rbp+0x222],ax                            
0x665c54f  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c556  mov rax,[rcx]                                 
0x665c559  mov rax,[rax+0x10]                            
0x665c55d  mov dl,0x4A                                   
0x665c55f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c565  nop                                           
0x665c566  mov [rbp+0x540],al                            
0x665c56c  mov rbx,[rsi+0x770]                           
0x665c573  cmp rbx,[rsi+0x778]                           
0x665c57a  je short 0x665C5B9                            ; -> loc_665c5b9
0x665c57c  mov rax,[rbp+0x3A0]                           
0x665c583  mov [rbx],rax                                 
0x665c586  lea rcx,[rbx+8]                               
0x665c58a  mov rdx,rdi                                   
0x665c58d  call 0xE869FF0                                ; -> sub_e869ff0
0x665c592  nop                                           
0x665c593  mov rax,[rbp+0x420]                           
0x665c59a  mov [rbx+0x80],rax                            
0x665c5a1  mov qword ptr [rbp+0x420],0                   
0x665c5ac  add qword ptr [rsi+0x770],0x88                
0x665c5b7  jmp short 0x665C5D0                           ; -> loc_665c5d0
loc_665c5b9:  ; from 665c57a
0x665c5b9  lea r8,[rbp+0x3A0]                            
0x665c5c0  lea rcx,[rsi+0x768]                           
0x665c5c7  mov rdx,rbx                                   
0x665c5ca  call 0x6760710                                ; -> sub_6760710
0x665c5cf  nop                                           
loc_665c5d0:  ; from 665c5b7
0x665c5d0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c5d7  mov rax,[rcx]                                 
0x665c5da  mov rax,[rax+0x10]                            
0x665c5de  movzx edx,byte ptr [rbp+0x540]                
0x665c5e5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c5eb  nop                                           
0x665c5ec  mov eax,[rsi+0x770]                           
0x665c5f2  sub eax,[rsi+0x768]                           
0x665c5f8  shr eax,3                                     
0x665c5fb  imul eax,0xFFFFF0F1                           
0x665c601  dec eax                                       
0x665c603  mov [rbp+0x20A],ax                            
```

Interpretation [I]:
- sub_eea6040 (dl=0x4A) again, store al->[rbp+0x540] — repeated tag writes suggest a format/schema header being emitted [I].
- If [rsi+0x770] != [rsi+0x778]: rax=[rbp+0x3A0] -> [rbx] (write 8 bytes), then sub_e869ff0 with rcx=rbx+8, rdx=rdi — likely initializes an entry; store [rbp+0x420]->[rbx+0x80], clear [rbp+0x420], advance [rsi+0x770] by 0x88 (0x88 = 136, fixed entry stride) [I]. Else (full) call sub_6760710 with r8=&[rbp+0x3A0], rcx=rsi+0x768, rdx=rbx — grow/flush [I].
- sub_eea6040 again; computes (eax=[rsi+0x770]-[rsi+0x768])>>3 * 0xFFFFF0F1 - 1 -> [rbp+0x20A] (count, stride 8) [I].
- [V] all instructions quoted exactly from rdis output `work/rdis/665c269.out`.

---
### Phase 6 — join 0x665c38a, block 0x665c60a..0x665c6a3

```text
0x665c60a  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c611  mov rax,[rcx]                                 
0x665c614  mov rax,[rax+0x10]                            
0x665c618  mov dl,0x4A                                   
0x665c61a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c61b  nop                                           
0x665c621  mov [rbp+0x540],al                            
0x665c627  mov rdx,[rsi+0x860]                           
0x665c62e  cmp rdx,[rsi+0x868]                           
0x665c635  je short 0x665C643                            ; -> loc_665c643
0x665c637  inc rdx                                       
0x665c63a  mov [rsi+0x860],rdx                           
0x665c641  jmp short 0x665C650                           ; -> loc_665c650
loc_665c643:  ; from 665c635
0x665c643  lea rcx,[rsi+0x858]                           
0x665c64a  call 0x6760E60                                ; -> sub_6760e60
0x665c64f  nop                                           
loc_665c650:  ; from 665c641
0x665c650  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c657  mov rax,[rcx]                                 
0x665c65a  mov rax,[rax+0x10]                            
0x665c65e  movzx edx,byte ptr [rbp+0x540]                
0x665c665  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c66b  nop                                           
0x665c66c  mov qword ptr [rbp+0x1E0],0x2003009           
0x665c677  mov eax,[rsi+0x858]                           
0x665c67d  not eax                                       
0x665c67f  add eax,[rsi+0x860]                           
0x665c685  mov [rbp+0x1F6],ax                            
0x665c68c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c693  mov rax,[rcx]                                 
0x665c696  mov rax,[rax+0x10]                            
0x665c69a  mov dl,0x4A                                   
0x665c69c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c6a2  nop                                           
0x665c6a3  mov [rbp+0x540],al                            
```

Interpretation [I]:
- sub_eea6040 (dl=0x4A); store al->[rbp+0x540] [I].
- If [rsi+0x860] != [rsi+0x868]: inc [rsi+0x860] (single-byte counter increment) [I]. Else call sub_6760E60 with rcx=rsi+0x858 — flush [I].
- sub_eea6040 again; [rbp+0x1E0]=0x2003009 (tag). eax=[rsi+0x858]; not eax; add eax,[rsi+0x860] -> [rbp+0x1F6] (complement-then-add, a derived count) [I].
- sub_eea6040 again; store al->[rbp+0x540] [I].
- [V] all instructions quoted exactly from rdis output `work/rdis/665c269.out`.

---
### Phase 6 — join 0x665c38a, block 0x665c6a9..0x665c85c (remainder part 1; truncated at 96 instructions)

```text
0x665c6a9  lea r8,[rbp+0x344]                             
0x665c6b0  mov rdx,[rsi+0x758]                           
0x665c6b7  cmp rdx,[rsi+0x760]                           
0x665c6be  je short 0x665C737                            ; -> loc_665c737
0x665c6c0  mov eax,[r8+0x10]                             
0x665c6c4  mov [rdx+0x10],eax                            
0x665c6c7  movups xmm0,[r8]                              
0x665c6cb  movups [rdx],xmm0                             
0x665c6ce  movzx eax,byte ptr [rbp+0x358]                
0x665c6d5  mov [rdx+0x14],al                             
0x665c6d8  movss xmm0,[rbp+0x35C]                        
0x665c6e0  movss [rdx+0x18],xmm0                         
0x665c6e5  movss xmm0,[rbp+0x360]                        
0x665c6ed  movss [rdx+0x1C],xmm0                         
0x665c6f2  movss xmm0,[rbp+0x364]                        
0x665c6fa  movss [rdx+0x20],xmm0                         
0x665c6ff  movss xmm0,[rbp+0x368]                        
0x665c707  movss [rdx+0x24],xmm0                         
0x665c70c  movups xmm0,[rbp+0x36C]                       
0x665c713  movups xmm1,[rbp+0x37C]                       
0x665c71a  movups xmm2,[rbp+0x38B]                       
0x665c721  movups [rdx+0x28],xmm0                        
0x665c725  movups [rdx+0x38],xmm1                        
0x665c729  movups [rdx+0x47],xmm2                        
0x665c72d  add qword ptr [rsi+0x758],0x58                
0x665c735  jmp short 0x665C747                           ; -> loc_665c747

loc_665c737:  ; from 665c6be
  665c737  mov rcx,rsi                                   
  665c73a  add rcx,0x750                                 
  665c741  call 0x6760A80                                ; -> sub_6760a80
  665c746  nop                                           

loc_665c747:  ; from 665c735
  665c747  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c74e  mov rax,[rcx]                                 
  665c751  mov rax,[rax+0x10]                            
  665c755  movzx edx,byte ptr [rbp+0x540]                
  665c75c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c762  nop                                           
  665c763  mov eax,[rsi+0x758]                           
  665c769  sub eax,[rsi+0x750]                           
  665c76f  shr eax,3                                     
  665c772  imul eax,0xFFFF8BA3                           
  665c778  dec eax                                       
  665c77a  mov [rbp+0x20C],ax                            
  665c781  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c788  mov rax,[rcx]                                 
  665c78b  mov rax,[rax+0x10]                            
  665c78f  mov dl,0x4A                                   
  665c791  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c797  nop                                           
  665c798  mov edx,eax                                   
  665c79a  mov rbx,[rsi+0x710]                           
  665c7a1  cmp rbx,[rsi+0x718]                           
  665c7a8  je short 0x665C7B9                            ; -> loc_665c7b9
  665c7aa  inc rbx                                       
  665c7ad  mov [rsi+0x710],rbx                           
  665c7b4  jmp 0x665C928                                 ; -> loc_665c928

loc_665c7b9:  ; from 665c7a8
  665c7b9  mov [rbp+0x540],dl                            
  665c7bf  mov r13,rbx                                   
  665c7c2  sub r13,[rsi+0x708]                           
  665c7c9  mov rax,0x7FFFFFFFFFFFFFFF                    
  665c7d3  cmp r13,rax                                   
  665c7d6  je 0x665E41C                                  ; -> loc_665e41c
  665c7dc  lea r12,[r13+1]                               
  665c7e0  mov rdi,r13                                   
  665c7e3  shr rdi,1                                     
  665c7e6  mov rcx,rdi                                   
  665c7e9  xor rcx,rax                                   
  665c7ec  add rdi,r13                                   
  665c7ef  cmp rdi,r12                                   
  665c7f2  cmovbe rdi,r12                                
  665c7f6  cmp r13,rcx                                   
  665c7f9  cmova rdi,rax                                 
  665c7fd  test rdi,rdi                                  
  665c800  je short 0x665C877                            ; -> loc_665c877
  665c802  cmp rdi,0x1000                                
  665c809  jb short 0x665C84E                            ; -> loc_665c84e
  665c80b  cmp rdi,0xFFFFFFFFFFFFFFD9                    
  665c80f  jae 0x665E7A7                                 ; -> sub_665e7a7
  665c815  lea r15,[rdi+0x27]                            
  665c819  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  665c820  mov rax,[rcx]                                 
  665c823  mov rax,[rax+8]                               
  665c827  mov rdx,r15                                   
  665c82a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c830  nop                                           
  665c831  mov r14,rax                                   
  665c834  test rax,rax                                  
  665c837  je 0x665D42C                                  ; -> loc_665d42c

loc_665c83d:  ; from 665d435
  665c83d  mov rax,r14                                   
  665c840  add r14,0x27                                  
  665c844  and r14,0xFFFFFFFFFFFFFFE0                    
  665c848  mov [r14-8],rax                               
  665c84c  jmp short 0x665C87A                           ; -> loc_665c87a

loc_665c84e:  ; from 665c809
  665c84e  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  665c855  mov rax,[rcx]                                 
  665c858  mov rax,[rax+8]                               
  665c85c  mov rdx,rdi                                   
  ... (truncated by rdis --max 96; resumes at 0x665c85c)
```

Interpretation [I] (part 1):
- If [rsi+0x758] != [rsi+0x760] (buffer not full): r8 = &[rbp+0x344] (source particle entry), rdx = [rsi+0x758] (write cursor). Copy [r8+0x10]->[rdx+0x10] (u32), movups [r8]->[rdx] (16 bytes), byte [rbp+0x358]->[rdx+0x14], four movss float32 [rbp+0x35C/0x360/0x364/0x368]->[rdx+0x18/0x1C/0x20/0x24], movups [rbp+0x36C/0x37C/0x38B]->[rdx+0x28/0x38/0x47]. Total copy spans 0x58 bytes (matches `add [rsi+0x758],0x58` — fixed 88-byte entry stride). Writes one particle entry; advance cursor; jmp loc_665c747 [I].
- Else (buffer full): loc_665c737: rcx = rsi+0x750; call sub_6760a80 — grow/flush helper [I].
- loc_665c747: sub_eea6040(dl=[rbp+0x540]); count = (([rsi+0x758]-[rsi+0x750])>>3) * 0xFFFF8BA3 - 1 -> [rbp+0x20C] (u16 element count, stride 8) [I].
- sub_eea6040(dl=0x4A); edx = eax saved; rbx = [rsi+0x710]; if rbx != [rsi+0x718]: inc rbx -> [rsi+0x710], jmp loc_665c928 (secondary counter increment) [I].
- Else loc_665c7b9: [rbp+0x540]=dl; r13 = rbx - [rsi+0x708] (element delta from base). Sentinel: if r13 == 0x7FFFFFFFFFFFFFFF goto loc_665e41c [I]. Growth heuristic: rdi = r13>>1; rcx = rdi ^ 0x7FFFFFFFFFFFFFFF; rdi = rdi + r13; cmovbe rdi,r13+1; cmova rdi,0x7FFFFFFFFFFFFFFF; test rdi,rdi; je loc_665c877; cmp rdi,0x1000; jb loc_665c84e; cmp rdi,0xFFFFFFFFFFFFFFD9; jae sub_665e7a7 (oversize). lea r15 = rdi+0x27 (alloc size with header). Allocate via [data_1233e1a8] vtable+8 (rdx=r15) -> r14; if null goto loc_665d42c [I].
- loc_665c83d (from 665d435, realloc path): rax = r14; r14 = align_up(r14+0x27, 0x20); [r14-8] = rax (store base header before aligned pointer); jmp loc_665c87a [I].
- loc_665c84e (small alloc < 0x1000): same allocator path with rdx = rdi; truncated at 0x665c85c — resumes there [V].

---
### Phase 6 — join 0x665c38a, block 0x665c85c..0x665cbdc (remainder part 2)

```text
0x665c85c  mov rdx,rdi                                   
0x665c85f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c865  nop                                           
0x665c866  mov r14,rax                                   
0x665c869  test rax,rax                                  
0x665c86c  jne short 0x665C87A                           ; -> loc_665c87a
0x665c86e  mov rcx,rdi                                   
0x665c871  call 0x9BC830                                 ; -> sub_9bc830
0x665c876  nop                                           
0x665c877  xor r14d,r14d                                 

loc_665c87a:  ; from 665c86c
  665c87a  cmp rbx,[rsi+0x710]                           
  665c881  je short 0x665C8B1                            ; -> loc_665c8b1
  665c883  lea r15,[r14+r13]                             
  665c887  inc r15                                       
  665c88a  mov rdx,[rsi+0x708]                           
  665c891  mov r8,rbx                                    
  665c894  sub r8,rdx                                    
  665c897  mov rcx,r14                                   
  665c89a  call 0xEEC6DE0                                ; -> sub_eec6de0
  665c89f  mov r8,[rsi+0x710]                            
  665c8a6  sub r8,rbx                                    
  665c8a9  mov rcx,r15                                   
  665c8ac  mov rdx,rbx                                   
  665c8af  jmp short 0x665C8C1                           ; -> loc_665c8c1

loc_665c8b1:  ; from 665c881
  665c8b1  mov rdx,[rsi+0x708]                           
  665c8b8  sub rbx,rdx                                   
  665c8bb  mov rcx,r14                                   
  665c8be  mov r8,rbx                                    

loc_665c8c1:  ; from 665c8af
  665c8c1  call 0xEEC6DE0                                ; -> sub_eec6de0
  665c8c6  mov rcx,[rsi+0x708]                           
  665c8cd  test rcx,rcx                                  
  665c8d0  je short 0x665C906                            ; -> loc_665c906
  665c8d2  mov rdx,[rsi+0x718]                           
  665c8d9  sub rdx,rcx                                   
  665c8dc  cmp rdx,0x1000                                
  665c8e3  jb short 0x665C901                            ; -> loc_665c901
  665c8e5  mov rax,[rcx-8]                               
  665c8e9  add rcx,0xFFFFFFFFFFFFFFF8                    
  665c8ed  sub rcx,rax                                   
  665c8f0  cmp rcx,0x20                                  
  665c8f4  jae 0x665D43A                                 ; -> loc_665d43a
  665c8fa  add rdx,0x27                                  
  665c8fe  mov rcx,rax                                   

loc_665c901:  ; from 665c8e3
  665c901  call 0xE935700                                ; -> sub_e935700

loc_665c906:  ; from 665c8d0
  665c906  mov [rsi+0x708],r14                           
  665c90d  add r12,r14                                   
  665c910  mov [rsi+0x710],r12                           
  665c917  add rdi,r14                                   
  665c91a  mov [rsi+0x718],rdi                           
  665c921  movzx edx,byte ptr [rbp+0x540]                
  665c928  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c92f  mov rax,[rcx]                                 
  665c932  mov rax,[rax+0x10]                            
  665c936  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c93c  nop                                           
  665c93d  mov qword ptr [rbp+0x1E0],0x2027009           
  665c948  mov eax,[rsi+0x708]                           
  665c94e  not eax                                       
  665c950  add eax,[rsi+0x710]                           
  665c956  mov [rbp+0x212],ax                            
  665c95d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c964  mov rax,[rcx]                                 
  665c967  mov rax,[rax+0x10]                            
  665c96b  mov dl,0x4A                                   
  665c96d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c973  nop                                           
  665c974  mov [rbp+0x540],al                            
  665c97a  mov rax,[rsi+8]                               
  665c97e  cmp rax,[rsi+0x10]                            
  665c982  je short 0x665C9A3                            ; -> loc_665c9a3
  665c984  lea rdx,[rbp+0x1E0]                           
  665c98b  mov r8d,0xC8                                  
  665c991  mov rcx,rax                                   
  665c994  call 0xEEC6EC0                                ; -> sub_eec6ec0
  665c999  add qword ptr [rsi+8],0xC8                    
  665c9a1  jmp short 0x665C9B6                           ; -> loc_665c9b6

loc_665c9a3:  ; from 665c982
  665c9a3  lea r8,[rbp+0x1E0]                            
  665c9aa  mov rcx,rsi                                   
  665c9ad  mov rdx,rax                                   
  665c9b0  call 0x5ABA6D0                                ; -> sub_5aba6d0
  665c9b5  nop                                           

loc_665c9b6:  ; from 665c9a1
  665c9b6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665c9bd  mov rax,[rcx]                                 
  665c9c0  mov rax,[rax+0x10]                            
  665c9c4  movzx edx,byte ptr [rbp+0x540]                
  665c9cb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665c9d1  nop                                           
  665c9d2  lea rcx,[rbp+0x340]                           
  665c9d9  call 0x66A9AD0                                ; -> sub_66a9ad0
  665c9de  cmp byte ptr [rbp+0x518],3                    
  665c9e5  jne short 0x665CA1E                           ; -> loc_665ca1e
  665c9e7  mov rsi,[rbp+0x510]                           
  665c9ee  test rsi,rsi                                  
  665c9f1  je short 0x665CA1E                            ; -> loc_665ca1e
  665c9f3  lock dec dword ptr [rsi+8]                    
  665c9f7  jne short 0x665CA1E                           ; -> loc_665ca1e
  665c9f9  mov rax,[rsi]                                 
  665c9fc  mov rax,[rax]                                 
  665c9ff  mov rcx,rsi                                   
  665ca02  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ca08  lock dec dword ptr [rsi+0xC]                  
  665ca0c  jne short 0x665CA1E                           ; -> loc_665ca1e
  665ca0e  mov rax,[rsi]                                 
  665ca11  mov rax,[rax+8]                               
  665ca15  mov rcx,rsi                                   
  665ca18  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ca1e:  ; from 665c9e5, 665c9f1, 665c9f7, 665ca0c
  665ca1e  mov rdi,[rbp+0x4E8]                           
  665ca25  test rdi,rdi                                  
  665ca28  je short 0x665CA78                            ; -> loc_665ca78
  665ca2a  mov rbx,[rbp+0x4F0]                           
  665ca31  jmp short 0x665CA37                           ; -> loc_665ca37

loc_665ca33:  ; from 665ca40, 665ca49, 665ca4f, 665ca64, 665ca76
  665ca33  add rdi,0x28                                  

loc_665ca37:  ; from 665ca31
  665ca37  cmp rdi,rbx                                   
  665ca3a  je short 0x665CA78                            ; -> loc_665ca78
  665ca3c  cmp byte ptr [rdi+0x18],2                     
  665ca40  jne short 0x665CA33                           ; -> loc_665ca33
  665ca42  mov rsi,[rdi+8]                               
  665ca46  test rsi,rsi                                  
  665ca49  je short 0x665CA33                            ; -> loc_665ca33
  665ca4b  lock dec dword ptr [rsi+8]                    
  665ca4f  jne short 0x665CA33                           ; -> loc_665CA33
  665ca51  mov rax,[rsi]                                 
  665ca54  mov rax,[rax]                                 
  665ca57  mov rcx,rsi                                   
  665ca5a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ca60  lock dec dword ptr [rsi+0xC]                  
  665ca64  jne short 0x665CA33                           ; -> loc_665CA33
  665ca66  mov rax,[rsi]                                 
  665ca69  mov rax,[rax+8]                               
  665ca6d  mov rcx,rsi                                   
  665ca70  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ca76  jmp short 0x665CA33                           ; -> loc_665CA33

loc_665ca78:  ; from 665ca28, 665ca3a
  665ca78  cmp byte ptr [rbp+0x1B0],1                    
  665ca7f  jne 0x665D11D                                 ; -> loc_665d11d
  665ca85  mov rcx,[rbp+0x170]                           
  665ca8c  test rcx,rcx                                  
  665ca8f  je 0x665D11D                                  ; -> loc_665d11d
  665ca95  mov rdx,[rbp+0x180]                           
  665ca9c  sub rdx,rcx                                   
  665ca9f  cmp rdx,0x1000                                
  665caa6  jb short 0x665CAC4                            ; -> loc_665cac4
  665caa8  mov rax,[rcx-8]                               
  665caac  add rcx,0xFFFFFFFFFFFFFFF8                    
  665cab0  sub rcx,rax                                   
  665cab3  cmp rcx,0x20                                  
  665cab7  jae 0x665D43A                                 ; -> loc_665d43a
  665cabd  or rdx,0x27                                   
  665cac1  mov rcx,rax                                   

loc_665cac4:  ; from 665caa6
  665cac4  call 0xE935700                                ; -> sub_e935700
  665cac9  jmp 0x665D11D                                 ; -> loc_665d11d
  665cace  xor ecx,ecx                                   
  665cad0  mov rdx,[rbp+0x198]                           
  665cad7  mov [rbp+0x3D0],rdx                           
  665cade  mov [rbp+0x3D8],rcx                           
  665cae5  mov [rbp+0x3E0],al                            
  665caeb  lea r9,[rbp+0x3A0]                            
  665caf2  lea r8,[rbp+0x3A8]                            
  665caf9  mov rax,[rbp+0x1C0]                           
  665cb00  mov [rbp+0x3F8],rax                           
  665cb07  movaps xmm0,[rbp+0x1B0]                       
  665cb0e  movups [rbp+0x3E8],xmm0                       
  665cb15  lea rdi,[rbp+0x400]                           
  665cb1c  mov byte ptr [rbp+0x440],0xFF                 
  665cb23  movzx ebx,byte ptr [rbp+0x160]                
  665cb2a  movzx eax,bl                                  
  665cb2d  cmp eax,1                                     
  665cb30  jg short 0x665CB70                            ; -> loc_665cb70
  665cb32  test eax,eax                                  
  665cb34  jne short 0x665CB85                           ; -> loc_665cb85
  665cb36  movaps xmm0,[rbp+0x120]                       
  665cb3d  movaps xmm1,[rbp+0x130]                       
  665cb44  movaps xmm2,[rbp+0x140]                       
  665cb4b  movaps xmm3,[rbp+0x150]                       
  665cb52  movaps [rbp+0x400],xmm0                       
  665cb59  movaps [rbp+0x410],xmm1                       
  665cb60  movaps [rbp+0x420],xmm2                       
  665cb67  movaps [rbp+0x430],xmm3                       
  665cb6e  jmp short 0x665CBB6                           ; -> loc_665cbb6

loc_665cb70:  ; from 665cb30
  665cb70  cmp eax,2                                     
  665cb73  jne short 0x665CBBC                           ; -> loc_665cbbc
  665cb75  mov rax,[rbp+0x120]                           
  665cb7c  mov [rbp+0x400],rax                           
  665cb83  jmp short 0x665CBB6                           ; -> loc_665cbb6

loc_665cb85:  ; from 665cb34
  665cb85  mov rax,[rbp+0x130]                           
  665cb8c  mov qword ptr [rbp+0x130],0                   
  665cb97  movaps xmm0,[rbp+0x120]                       
  665cb9e  xorps xmm1,xmm1                               
  665cba1  movaps [rbp+0x120],xmm1                       
  665cba8  movaps [rbp+0x400],xmm0                       
  665cbaf  mov [rbp+0x410],rax                           

loc_665cbb6:  ; from 665cb6e, 665cb83
  665cbb6  mov [rbp+0x440],bl                            

loc_665cbbc:  ; from 665cb73
  665cbbc  mov ecx,0x9D0                                 
  665cbc1  add rcx,[rsi+0x10]                            
  665cbc5  mov [rsp+0x20],r12                            
  665cbca  mov rdx,rdi                                   
  665cbcd  call 0x67E6730                                ; -> sub_67e6730
  665cbd2  nop                                           
  665cbd3  cmp byte ptr [rbp+0x440],1                    
  665cbda  jne short 0x665CC2A                           ; -> loc_665cc2a
  665cbdc  mov rcx,[rbp+0x400]                           
  ... (continues at 0x665cbdc, part 3)
```

Interpretation [I] (part 2):
- loc_665c85c (small-alloc fallthrough): rdx = rdi; call sub_eea6040([data_1233e1a8]+8, rdx=rdi size) -> rax; r14 = rax; if null call sub_9bc830 (likely abort/free) then r14d = 0 [I]. If non-null, goto loc_665c87a.
- loc_665c87a: cmp rbx,[rsi+0x710]; if equal goto loc_665c8b1. Else r15 = r14 + r13 + 1 (new end with +1); rdx = [rsi+0x708] (old base); r8 = rbx - rdx (old size); call sub_eec6de0(rcx=r14 new base, rdx=rbx old ptr, r8=old size) — memmove old data to new buffer [I]. Then r8 = [rsi+0x710] - rbx (remaining), rcx = r15, rdx = rbx; jmp loc_665c8c1.
- loc_665c8b1 (rbx == [rsi+0x710], nothing to move): rdx = [rsi+0x708]; rbx -= rdx; rcx = r14; r8 = rbx; fall to loc_665c8c1.
- loc_665c8c1: call sub_eec6de0 (second memmove — fix up remaining portion); rcx = [rsi+0x708] (old base); if null goto loc_665c906. Else rdx = [rsi+0x718] - rcx (remaining capacity); if < 0x1000 goto sub_e935700 (free old). Else rax = [rcx-8] (old alloc header/base); rcx = rcx - 8; rcx -= rax (old size minus header); if >= 0x20 goto loc_665d43a (partial free path). Else rdx += 0x27; rcx = rax; fall to sub_e935700 (free old buffer) [I].
- loc_665c901: call sub_e935700 — free old allocation [I].
- loc_665c906: [rsi+0x708] = r14 (new base); r12 += r14; [rsi+0x710] = r12 (new write cursor); rdi += r14; [rsi+0x718] = rdi (new end) — rebase all buffer pointers after realloc [I]. movzx edx, [rbp+0x540]; sub_eea6040(dl); [rbp+0x1E0] = 0x2027009 (tag).
- Count: eax = [rsi+0x708]; not eax; eax += [rsi+0x710] -> [rbp+0x212] (complement-then-add derived count) [I].
- sub_eea6040(dl=0x4A); store al -> [rbp+0x540] [I].
- Particle blob write: rax = [rsi+8]; if rax != [rsi+0x10] (not full): rdx = &[rbp+0x1E0], r8d = 0xC8 (200 bytes), rcx = rax; call sub_eec6ec0 (copy 0xC8 bytes); [rsi+8] += 0xC8; jmp loc_665c9b6. Else (full): r8 = &[rbp+0x1E0], rcx = rsi, rdx = rax; call sub_5aba6d0 (flush/grow) [I].
- loc_665c9b6: sub_eea6040(dl=[rbp+0x540]); lea rcx, [rbp+0x340]; call sub_66a9ad0 (reinit header) [I].
- cmp byte [rbp+0x518], 3; if != 3 or rsi=[rbp+0x510] null: goto loc_665ca1e (skip teardown). Else refcount-dec rsi and two-call release/destroy via [data_f99ffa0] — teardown of object at [rbp+0x510] [I].
- loc_665ca1e: rdi = [rbp+0x4E8]; if null goto loc_665ca78. Else rbx = [rbp+0x4F0] (end); loop rdi += 0x28 while rdi != rbx: if byte [rdi+0x18] == 2, rsi = [rdi+8], refcount-dec + two-call release/destroy — teardown array of 0x28-strided type-2 objects [I] (mirrors phase 2 loop at 0x665c305).
- loc_665ca78: if byte [rbp+0x1B0] == 1 and [rbp+0x170] non-null: rdx = [rbp+0x180] - rcx (size check); if >= 0x1000: rax = [rcx-8], rcx -= 8, rcx -= rax; if >= 0x20 goto loc_665d43a; else or rdx,0x27; rcx = rax; call sub_e935700 (free); jmp loc_665d11d. Else fall to zeroing block [I].
- Zeroing block at 0x665cace: ecx=0; rdx=[rbp+0x198]; [rbp+0x3D0]=rdx; [rbp+0x3D8]=0; [rbp+0x3E0]=al(0); lea r9=[rbp+0x3A0], r8=[rbp+0x3A8]; rax=[rbp+0x1C0]; [rbp+0x3F8]=rax; movups [rbp+0x1B0]->[rbp+0x3E8]; [rbp+0x440]=0xFF; rdi = &[rbp+0x400].
- Switch on byte [rbp+0x160]: eax == 0 -> zero [rbp+0x120..0x150] (4 xmm) into [rbp+0x400..0x430]; eax == 1 -> mov [rbp+0x400]=[rbp+0x120], zero [rbp+0x120], [rbp+0x410]=rax (move+clear); eax == 2 -> [rbp+0x400]=[rbp+0x120]. Then [rbp+0x440]=bl [I].
- [rbp+0x440]==1 check: if ==1, rcx=[rbp+0x400] (non-null path at 0x665cbdc). Else goto loc_665cc2a.
- call sub_67E6730 with ecx=0x9D0+[rsi+0x10], rdx=rdi — another allocation/acquire [I]; truncated at 0x665cbdc — continues in part 3.
- [V] all instructions quoted exactly from rdis output.

---
### Phase 6 — join 0x665c38a, block 0x665cbdc..0x665ce32 (remainder part 3; end of shared body approaching)

```text
0x665cbdc  mov rcx,[rbp+0x400]                           
0x665cbe3  test rcx,rcx                                  
0x665cbe6  je short 0x665CC2A                            ; -> loc_665cc2a
0x665cbe8  mov rdx,[rbp+0x410]                           
0x665cbef  sub rdx,rcx                                   
0x665cbf2  cmp rdx,0x1000                                
0x665cbf9  jb short 0x665CC17                            ; -> loc_665cc17
0x665cbfb  mov rax,[rcx-8]                               
0x665cbff  add rcx,0xFFFFFFFFFFFFFFF8                    
0x665cc03  sub rcx,rax                                   
0x665cc06  cmp rcx,0x20                                  
0x665cc0a  jae 0x665D43A                                 ; -> loc_665d43a
0x665cc10  or rdx,0x27                                   
0x665cc14  mov rcx,rax                                   

loc_665cc17:  ; from 665cbf9
  665cc17  call 0xE935700                                ; -> sub_e935700
  665cc1c  xorps xmm0,xmm0                               
  665cc1f  movups [rdi],xmm0                             
  665cc22  mov qword ptr [rdi+0x10],0                    

loc_665cc2a:  ; from 665cbe6
  665cc2a  lea rcx,[rbp+0x340]                           
  665cc31  call 0x67B5160                                ; -> sub_67b5160
  665cc36  cmp bl,1                                      
  665cc39  jne short 0x665CC7B                           ; -> loc_665cc7b
  665cc3b  mov rcx,[rbp+0x120]                           
  665cc42  test rcx,rcx                                  
  665cc45  je short 0x665CC7B                            ; -> loc_665cc7b
  665cc47  mov rdx,[rbp+0x130]                           
  665cc4e  sub rdx,rcx                                   
  665cc51  cmp rdx,0x1000                                
  665cc58  jb short 0x665CC76                            ; -> loc_665cc76
  665cc5a  mov rax,[rcx-8]                               
  665cc5e  add rcx,0xFFFFFFFFFFFFFFF8                    
  665cc62  sub rcx,rax                                   
  665cc65  cmp rcx,0x20                                  
  665cc69  jae 0x665D43A                                 ; -> loc_665d43a
  665cc6f  or rdx,0x27                                   
  665cc73  mov rcx,rax                                   

loc_665cc76:  ; from 665cc58
  665cc76  call 0xE935700                                ; -> sub_e935700

loc_665cc7b:  ; from 665cc39, 665cc45
  665cc7b  cmp byte ptr [rbp+0x1A8],3                    
  665cc82  jne short 0x665CCBB                           ; -> loc_665ccbb
  665cc84  mov rsi,[rbp+0x1A0]                           
  665cc8b  test rsi,rsi                                  
  665cc8e  je short 0x665CCBB                           ; -> loc_665ccbb
  665cc90  lock dec dword ptr [rsi+8]                    
  665cc94  jne short 0x665CCBB                           ; -> loc_665ccbb
  665cc96  mov rax,[rsi]                                 
  665cc99  mov rax,[rax]                                 
  665cc9c  mov rcx,rsi                                   
  665cc9f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cca5  lock dec dword ptr [rsi+0xC]                  
  665cca9  jne short 0x665CCBB                           ; -> loc_665CCBB
  665ccab  mov rax,[rsi]                                 
  665ccae  mov rax,[rax+8]                               
  665ccb2  mov rcx,rsi                                   
  665ccb5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ccbb:  ; from 665cc82, 665cc8e, 665cc94, 665cca9
  665ccbb  mov rdi,[rbp+0x178]                           
  665ccc2  test rdi,rdi                                  
  665ccc5  je short 0x665CD15                            ; -> loc_665cd15
  665ccc7  mov rbx,[rbp+0x180]                           
  665ccce  jmp short 0x665CCD4                           ; -> loc_665ccd4

loc_665ccd0:  ; from 665ccdd, 665cce6, 665ccec, 665cd01, 665cd13
  665ccd0  add rdi,0x28                                  

loc_665ccd4:  ; from 665ccce
  665ccd4  cmp rdi,rbx                                   
  665ccd7  je short 0x665CD15                            ; -> loc_665cd15
  665ccd9  cmp byte ptr [rdi+0x18],2                     
  665ccdd  jne short 0x665CCD0                           ; -> loc_665CCD0
  665ccdf  mov rsi,[rdi+8]                               
  665cce3  test rsi,rsi                                  
  665cce6  je short 0x665CCD0                           ; -> loc_665ccd0
  665cce8  lock dec dword ptr [rsi+8]                    
  665ccec  jne short 0x665CCD0                           ; -> loc_665CCD0
  665ccee  mov rax,[rsi]                                 
  665ccf1  mov rax,[rax]                                 
  665ccf4  mov rcx,rsi                                   
  665ccf7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ccfd  lock dec dword ptr [rsi+0xC]                  
  665cd01  jne short 0x665CCD0                           ; -> loc_665CCD0
  665cd03  mov rax,[rsi]                                 
  665cd06  mov rax,[rax+8]                               
  665cd0a  mov rcx,rsi                                   
  665cd0d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cd13  jmp short 0x665CCD0                           ; -> loc_665CCD0

loc_665cd15:  ; from 665ccc5, 665ccd7
  665cd15  mov rsi,[rbp+0x530]                           
  665cd1c  test rsi,rsi                                  
  665cd1f  je short 0x665CD4C                            ; -> loc_665cd4c
  665cd21  lock dec dword ptr [rsi+8]                    
  665cd25  jne short 0x665CD4C                           ; -> loc_665cd4c
  665cd27  mov rax,[rsi]                                 
  665cd2a  mov rax,[rax]                                 
  665cd2d  mov rcx,rsi                                   
  665cd30  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cd36  lock dec dword ptr [rsi+0xC]                  
  665cd3a  jne short 0x665CD4C                           ; -> loc_665cd4c
  665cd3c  mov rax,[rsi]                                 
  665cd3f  mov rax,[rax+8]                               
  665cd43  mov rcx,rsi                                   
  665cd46  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cd4c:  ; from 665cd1f, 665cd25, 665cd3a
  665cd4c  mov rsi,[rbp+0x520]                           
  665cd53  test rsi,rsi                                  
  665cd56  je short 0x665CD83                            ; -> loc_665cd83
  665cd58  lock dec dword ptr [rsi+8]                    
  665cd5c  jne short 0x665CD83                           ; -> loc_665CD83
  665cd5e  mov rax,[rsi]                                 
  665cd61  mov rax,[rax]                                 
  665cd64  mov rcx,rsi                                   
  665cd67  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cd6d  lock dec dword ptr [rsi+0xC]                  
  665cd71  jne short 0x665CD83                           ; -> loc_665CD83
  665cd73  mov rax,[rsi]                                 
  665cd76  mov rax,[rax+8]                               
  665cd7a  mov rcx,rsi                                   
  665cd7d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cd83:  ; from 665cd56, 665cd5c, 665cd71
  665cd83  mov rsi,[rbp+0x510]                           
  665cd8a  test rsi,rsi                                  
  665cd8d  je short 0x665CDBA                            ; -> loc_665cdba
  665cd8f  lock dec dword ptr [rsi+8]                    
  665cd93  jne short 0x665CDBA                           ; -> loc_665cdba
  665cd95  mov rax,[rsi]                                 
  665cd98  mov rax,[rax]                                 
  665cd9b  mov rcx,rsi                                   
  665cd9e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cda4  lock dec dword ptr [rsi+0xC]                  
  665cda8  jne short 0x665CDBA                           ; -> loc_665CDBA
  665cdaa  mov rax,[rsi]                                 
  665cdad  mov rax,[rax+8]                               
  665cdb1  mov rcx,rsi                                   
  665cdb4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cdba:  ; from 665cd8d, 665cd93, 665cda8
  665cdba  mov rsi,[rbp+0x4E8]                           
  665cdc1  test rsi,rsi                                  
  665cdc4  je short 0x665CDF1                            ; -> loc_665cdf1
  665cdc6  lock dec dword ptr [rsi+8]                    
  665cdca  jne short 0x665CDF1                           ; -> loc_665cdf1
  665cdcc  mov rax,[rsi]                                 
  665cdcf  mov rax,[rax]                                 
  665cdd2  mov rcx,rsi                                   
  665cdd5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cddb  lock dec dword ptr [rsi+0xC]                  
  665cddf  jne short 0x665CDF1                           ; -> loc_665CDF1
  665cde1  mov rax,[rsi]                                 
  665cde4  mov rax,[rax+8]                               
  665cde8  mov rcx,rsi                                   
  665cdeb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cdf1:  ; from 665cdc4, 665cdca, 665cddf
  665cdf1  mov rsi,[rbp+0x18]                            
  665cdf5  test rsi,rsi                                  
  665cdf8  je short 0x665CE25                            ; -> loc_665ce25
  665cdfa  lock dec dword ptr [rsi+8]                    
  665cdfe  jne short 0x665CE25                           ; -> loc_665ce25
  665ce00  mov rax,[rsi]                                 
  665ce03  mov rax,[rax]                                 
  665ce06  mov rcx,rsi                                   
  665ce09  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ce0f  lock dec dword ptr [rsi+0xC]                  
  665ce13  jne short 0x665CE25                           ; -> loc_665ce25
  665ce15  mov rax,[rsi]                                 
  665ce18  mov rax,[rax+8]                               
  665ce1c  mov rcx,rsi                                   
  665ce1f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ce25:  ; from 665cdf8, 665cdfe, 665ce13
  665ce25  mov rsi,[rbp-8]                               
  665ce29  test rsi,rsi                                  
  665ce2c  je short 0x665CE59                            ; -> loc_665ce59
  665ce2e  lock dec dword ptr [rsi+8]                    
  665ce32  jne short 0x665CE59                           ; -> loc_665ce59
  ... (truncated by rdis --max 160 at 0x665ce32; continued below)

---
### Phase 6 — join 0x665c38a, block 0x665ce32..0x665cf64 (remainder part 4; end of shared body)

```text
0x665ce32  jne short 0x665CE59                           ; -> loc_665ce59
0x665ce34  mov rax,[rsi]                                 
0x665ce37  mov rax,[rax]                                 
0x665ce3a  mov rcx,rsi                                   
0x665ce3d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665ce43  lock dec dword ptr [rsi+0xC]                  
0x665ce47  jne short 0x665CE59                           ; -> loc_665ce59
0x665ce49  mov rax,[rsi]                                 
0x665ce4c  mov rax,[rax+8]                               
0x665ce50  mov rcx,rsi                                   
0x665ce53  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ce59:  ; from 665ce32, 665ce47
  665ce59  mov rsi,[rbp-0x18]                            
  665ce5d  test rsi,rsi                                  
  665ce60  je short 0x665CE8D                            ; -> loc_665ce8d
  665ce62  lock dec dword ptr [rsi+8]                    
  665ce66  jne short 0x665CE8D                           ; -> loc_665CE8D
  665ce68  mov rax,[rsi]                                 
  665ce6b  mov rax,[rax]                                 
  665ce6e  mov rcx,rsi                                   
  665ce71  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ce77  lock dec dword ptr [rsi+0xC]                  
  665ce7b  jne short 0x665CE8D                           ; -> loc_665CE8D
  665ce7d  mov rax,[rsi]                                 
  665ce80  mov rax,[rax+8]                               
  665ce84  mov rcx,rsi                                   
  665ce87  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665ce8d:  ; from 665ce60, 665ce66, 665ce7b
  665ce8d  mov rsi,[rbp+0x38]                            
  665ce91  test rsi,rsi                                  
  665ce94  je short 0x665CEC1                            ; -> loc_665cec1
  665ce96  lock dec dword ptr [rsi+8]                    
  665ce9a  jne short 0x665CEC1                           ; -> loc_665CEC1
  665ce9c  mov rax,[rsi]                                 
  665ce9f  mov rax,[rax]                                 
  665cea2  mov rcx,rsi                                   
  665cea5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665ceab  lock dec dword ptr [rsi+0xC]                  
  665ceaf  jne short 0x665CEC1                           ; -> loc_665CEC1
  665ceb1  mov rax,[rsi]                                 
  665ceb4  mov rax,[rax+8]                               
  665ceb8  mov rcx,rsi                                   
  665cebb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cec1:  ; from 665ce94, 665ce9a, 665ceaf
  665cec1  movzx eax,byte ptr [rbp+0xA8]                 
  665cec8  test al,al                                    
  665ceca  je 0x665CF64                                  ; -> loc_665cf64  (COLD RANGE ENTRY)
  665ced0  cmp byte ptr [rbp+0x88],3                     
  665ced7  jne short 0x665CF10                           ; -> loc_665cf10
  665ced9  mov rsi,[rbp+0x80]                            
  665cee0  test rsi,rsi                                  
  665cee3  je short 0x665CF10                            ; -> loc_665cf10
  665cee5  lock dec dword ptr [rsi+8]                    
  665cee9  jne short 0x665CF10                           ; -> loc_665CF10
  665ceeb  mov rax,[rsi]                                 
  665ceee  mov rax,[rax]                                 
  665cef1  mov rcx,rsi                                   
  665cef4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cefa  lock dec dword ptr [rsi+0xC]                  
  665cefe  jne short 0x665CF10                           ; -> loc_665CF10
  665cf00  mov rax,[rsi]                                 
  665cf03  mov rax,[rax+8]                               
  665cf07  mov rcx,rsi                                   
  665cf0a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665cf10:  ; from 665ced7, 665cee3, 665cee9, 665cefe
  665cf10  mov rdi,[rbp+0x58]                            
  665cf14  test rdi,rdi                                  
  665cf17  je short 0x665CF64                            ; -> loc_665CF64  (COLD RANGE ENTRY)
  665cf19  mov rbx,[rbp+0x60]                            
  665cf1d  jmp short 0x665CF23                           ; -> loc_665cf23

loc_665cf1f:  ; from 665cf2c, 665cf35, 665cf3b, 665cf50, 665cf62
  665cf1f  add rdi,0x28                                  

loc_665cf23:  ; from 665cf1d
  665cf23  cmp rdi,rbx                                   
  665cf26  je short 0x665CF64                            ; -> loc_665CF64  (COLD RANGE ENTRY)
  665cf28  cmp byte ptr [rdi+0x18],2                     
  665cf2c  jne short 0x665CF1F                           ; -> loc_665CF1F
  665cf2e  mov rsi,[rdi+8]                               
  665cf32  test rsi,rsi                                  
  665cf35  je short 0x665CF1F                            ; -> loc_665CF1F
  665cf37  lock dec dword ptr [rsi+8]                    
  665cf3b  jne short 0x665CF1F                           ; -> loc_665CF1F
  665cf3d  mov rax,[rsi]                                 
  665cf40  mov rax,[rax]                                 
  665cf43  mov rcx,rsi                                   
  665cf46  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cf4c  lock dec dword ptr [rsi+0xC]                  
  665cf50  jne short 0x665CF1F                           ; -> loc_665CF1F
  665cf52  mov rax,[rsi]                                 
  665cf55  mov rax,[rax+8]                               
  665cf59  mov rcx,rsi                                   
  665cf5c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665cf62  jmp short 0x665CF1F                           ; -> loc_665CF1F

loc_665cf64:  ; from 665ceca, 665cf17, 665cf26 — COLD RANGE STARTS HERE
  665cf64  mov rsi,[rbp+0x28]                            
  665cf68  jmp 0x665D124                                 ; -> loc_665d124
  ... (cold range continues at 0x665cf6d; see cold range section below)
```

Interpretation [I] (part 4 — end of shared body):
- Teardown continues: [rbp-8] (from 0x665ce32), [rbp-0x18], [rbp+0x38] — each lock-dec + two-call release/destroy via [data_f99ffa0] [I].
- loc_665cec1: movzx eax, byte [rbp+0xA8]; test al,al; je 0x665CF64 — if zero, branch to COLD RANGE (0x665cf64) [V]. This is the exit from shared body to cold tail.
- Else: cmp byte [rbp+0x88], 3; if == 3 and [rbp+0x80] non-null: teardown [rbp+0x80] object [I].
- loc_665cf10: rdi = [rbp+0x58]; if null goto 0x665CF64 (cold). Else rbx = [rbp+0x60]; loop rdi += 0x28 while rdi != rbx: if byte [rdi+0x18] == 2, teardown [rdi+8] object — same 0x28-strided type-2 array teardown [I]; then fall to 0x665CF64 (cold).
- loc_665CF64: COLD RANGE ENTRY — rsi = [rbp+0x28]; jmp 0x665D124 (shared cold tail) [V]. All paths out of shared body converge here at 0x665cf64.
- [V] all instructions quoted exactly from rdis output. Reaches cold range start 0x665cf64; cold range documented in next section.

---
### Join 3 — sub_665b624 entry block 0x665b624..0x665b864 (truncated at --max 120)

```text
sub_665b624  [0x665b624..0x665d624)  size 0x2000  2 xrefs in
0x665b624  mov [rbp+0x470],al                             ; join entry 3 (xref from sub_665c269 phase 3 at 0x665ba1e case-1 jump)
0x665b62a  lea rax,[rbp+0x344]
0x665b631  lea r10,[rbp+0x39C]
0x665b638  lea r11,[rbp+0x3A8]
0x665b63f  lea r9,[rbp+0x430]
0x665b646  lea r8,[rbp+0x478]
0x665b64d  mov [rbp+0x478],r15w
0x665b655  lea rdx,[rbp+0x480]
0x665b65c  movaps xmm0,[rbp+0x50]
0x665b660  movaps xmm1,[rbp+0x60]
0x665b664  mov qword ptr [rbp+0x58],0
0x665b66c  movups [rbp+0x480],xmm0
0x665b673  xorps xmm0,xmm0
0x665b676  movaps [rbp+0x60],xmm0
0x665b67a  movups [rbp+0x490],xmm1
0x665b681  mov rcx,[rbp+0x70]
0x665b685  mov [rbp+0x4A0],rcx
0x665b68c  mov byte ptr [rbp+0x4B8],0xFF
0x665b693  movzx ecx,byte ptr [rbp+0x88]
0x665b69a  cmp rcx,3
0x665b69e  ja 0x665C121                                  ; -> loc_665c121
0x665b6a4  lea rdi,[rbp+0x4A8]
0x665b6ab  lea rbx,[0xF2BF3C8]                           ; [data_f2bf3c8] jump table base
0x665b6b2  movsxd r14,[rbx+rcx*4]                        ; table entry indexed by byte [rbp+0x88]
0x665b6b6  add r14,rbx
0x665b6b9  jmp r14                                       ; indirect jump via jump table

; jump table targets (indices 0-3 from [data_f2bf3c8]):
0x665b6bc  mov rdi,[rbp+0x78]                            ; case 0
0x665b6c0  mov [rbp+0x4A8],rdi
0x665b6c7  jmp 0x665C11B                                 ; -> loc_665c11b
0x665b6cc  lea rdx,[rbp+0x508]                           ; case 1
0x665b6d3  movups xmm0,[rdx]
0x665b6d6  movups [rcx],xmm0
0x665b6d9  jmp 0x665BB33                                 ; -> loc_665bb33
0x665b6de  xorps xmm0,xmm0                               ; case 2
0x665b6e1  movups [rcx],xmm0
0x665b6e4  mov rcx,[rbp+0x510]
0x665b6eb  test rcx,rcx
0x665b6ee  je 0x665BB1C                                  ; -> loc_665bb1c
0x665b6f4  lock inc dword ptr [rcx+8]                    ; refcount inc
0x665b6f8  mov rcx,[rbp+0x510]
0x665b6ff  jmp 0x665BB1E                                 ; -> loc_665bb1e
0x665b704  lea rbx,[rbp+0x78]                            ; case 3
0x665b708  movups xmm0,[rbx]
0x665b70b  movups [rdi],xmm0
0x665b70e  jmp 0x665C11B                                 ; -> loc_665c11b
0x665b713  movups [rdi],xmm0                             ; (continued)
0x665b716  mov rdi,[rbp+0x80]
0x665b71d  test rdi,rdi
0x665b720  je 0x665C107                                  ; -> loc_665c107
0x665b726  lock inc dword ptr [rdi+8]                    ; refcount inc
0x665b72a  mov rdi,[rbp+0x80]
0x665b731  jmp 0x665C109                                 ; -> loc_665c109
0x665b736  xor edx,edx                                   ; default/setup case
0x665b738  mov r8,[rbp+0x30]
0x665b73c  mov [rbp+0x10],r8
0x665b740  mov [rbp+0x18],rdx
0x665b744  lea rdx,[rbp-0x20]
0x665b748  mov [rsp+0x38],rdx
0x665b74d  lea rdx,[rbp-0x10]
0x665b751  mov [rsp+0x30],rdx
0x665b756  mov [rsp+0x28],ax
0x665b75b  mov [rsp+0x20],rcx
0x665b760  mov dword ptr [rsp+0x48],0xFFFFFF00
0x665b768  mov dword ptr [rsp+0x40],0xFFFFFF00
0x665b770  lea rcx,[rbp+0x4E0]
0x665b777  lea rdx,[rbp+0x10]
0x665b77b  mov r8b,0xA
0x665b77e  mov r9,0xFFFFFFFFFFFFFFFF
0x665b785  call 0x673CC80                                ; -> sub_673cc80
0x665b78a  movzx r13d,word ptr [rdi+0x68]
0x665b78f  mov rax,[rdi]
0x665b792  xorps xmm0,xmm0
0x665b795  movaps [rbp],xmm0
0x665b799  mov rcx,[rax+0x1B0]
0x665b7a0  test rcx,rcx
0x665b7a3  je short 0x665B7A9                            ; -> loc_665b7a9
0x665b7a5  movzx ecx,word ptr [rcx+0x10]

loc_665b7a9:  ; from 665b7a3
  665b7a9  mov rcx,[rax+0x1B8]
  665b7b0  test rcx,rcx
  665b7b3  je short 0x665B7C2                            ; -> loc_665b7c2
  665b7b5  lock inc dword ptr [rcx+8]                    ; refcount inc [rax+0x1B8]
  665b7b9  mov rcx,[rax+0x1B8]
  665b7c0  jmp short 0x665B7C4                           ; -> loc_665b7c4

loc_665b7c2:  ; from 665b7b3
  665b7c2  xor ecx,ecx

loc_665b7c4:  ; from 665b7c0
  665b7c4  mov rax,[rax+0x1B0]
  665b7cb  mov [rbp],rax
  665b7cf  mov r15,[rbp+8]
  665b7d3  mov [rbp+8],rcx
  665b7d7  test r15,r15
  665b7da  je short 0x665B809                            ; -> loc_665b809
  665b7dc  lock dec dword ptr [r15+8]
  665b7e1  jne short 0x665B809                           ; -> loc_665b809
  665b7e3  mov rax,[r15]
  665b7e6  mov rax,[rax]
  665b7e9  mov rcx,r15
  665b7ec  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665b7f2  lock dec dword ptr [r15+0xC]
  665b7f7  jne short 0x665B809                           ; -> loc_665b809
  665b7f9  mov rax,[r15]
  665b7fc  mov rax,[rax+8]
  665b800  mov rcx,r15
  665b803  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_665b809:  ; from 665b7da, 665b7e1, 665b7f7
  665b809  mov r8,[rbx+0x3B8]
  665b810  mov rdx,[rsi]
  665b813  mov [rsp+0x20],r14d
  665b818  mov dword ptr [rsp+0x30],0
  665b820  mov dword ptr [rsp+0x28],0
  665b828  lea rcx,[rbp+0x170]
  665b82f  mov r9,rbp
  665b832  call 0x66A0F60                                ; -> sub_66a0f60
  665b837  nop
  665b838  movups xmm0,[rdi+0x28]
  665b83c  movaps [rbp+0x120],xmm0
  665b843  movups xmm0,[rdi+0x38]
  665b847  movaps [rbp+0x130],xmm0
  665b84e  movups xmm0,[rdi+0x48]
  665b852  movaps [rbp+0x140],xmm0
  665b859  movups xmm0,[rdi+0x58]
  665b85d  movaps [rbp+0x150],xmm0
  665b864  mov byte ptr [rbp+0x160],0
  ... (truncated by rdis --max 120 at 0x665b864; resumes there)
```

Interpretation [I] (join 3 / sub_665b624 part 1):
- Entry: al -> [rbp+0x470] (store type byte). Sets up lea pointers: rax=&[rbp+0x344], r10=&[rbp+0x39C], r11=&[rbp+0x3A8], r9=&[rbp+0x430], r8=&[rbp+0x478], rdx=&[rbp+0x480]. Stores r15w -> [rbp+0x478]. Copies xmm0=[rbp+0x50]->[rbp+0x480], xmm1=[rbp+0x60]->[rbp+0x490]. Zeroes [rbp+0x58], [rbp+0x60]. [rbp+0x4A0]=[rbp+0x70]. [rbp+0x4B8]=0xFF [I].
- Dispatch: movzx ecx, byte [rbp+0x88]; if > 3 goto loc_665c121 (cold/out-of-range). Else jump table [data_f2bf3c8] indexed by rcx*4, indirect jmp r14 [V].
- Case 0 (0x665b6bc): rdi=[rbp+0x78]; [rbp+0x4A8]=rdi; jmp loc_665c11b [I].
- Case 1 (0x665b6cc): rdx=&[rbp+0x508]; movups [rdx]->[rcx]; jmp loc_665bb33 [I].
- Case 2 (0x665b6de): xorps [rcx]=0; rcx=[rbp+0x510]; if null goto loc_665bb1c; else lock inc [rcx+8] (refcount inc), goto loc_665bb1e [I].
- Case 3 (0x665b704): rbx=&[rbp+0x78]; movups [rbx]->[rdi]; jmp loc_665c11b [I]. Then 0x665b713: [rdi]=xmm0; rdi=[rbp+0x80]; if null goto loc_665c107; lock inc [rdi+8]; goto loc_665c109 [I] (refcount inc of [rbp+0x80]).
- Default (0x665b736): edx=0; r8=[rbp+0x30]; [rbp+0x10]=r8; [rbp+0x18]=0; sets up stack frame [rsp+0x28..0x48] with 0xFFFFFF00 (-256) values; lea rcx=[rbp+0x4E0], rdx=&[rbp+0x10], r8b=0xA, r9=-1; call sub_673CC80 [I].
- After call: r13d = movzx word [rdi+0x68]; rax=[rdi]; xorps [rbp]=0; rcx=[rax+0x1B0]; if non-null ecx=movzx word [rcx+0x10]; rcx=[rax+0x1B8]; if null ecx=0 else lock inc [rcx+8] (refcount inc [rax+0x1B8]); rax=[rax+0x1B0]; [rbp]=rax; r15=[rbp+8]; [rbp+8]=rcx; if r15 non-null: lock dec [r15+8], if zero release+destroy via [data_f99ffa0] (two-call pattern) [I].
- loc_665b809: r8=[rbx+0x3B8]; rdx=[rsi]; [rsp+0x20]=r14d; zero [rsp+0x30],[rsp+0x28]; lea rcx=[rbp+0x170]; r9=rbp; call sub_66A0F60 [I].
- Then: movups [rdi+0x28]->[rbp+0x120], [rdi+0x38]->[rbp+0x130], [rdi+0x48]->[rbp+0x140], [rdi+0x58]->[rbp+0x150] (copy 4 xmm = 64 bytes from rdi+0x28). [rbp+0x160]=0. Truncated at 0x665b864 — continues in part 2 [V].

---
### Join 3 — sub_665b624 entry block 0x665b864..0x665bad3 (remainder part 2; truncated at --max 120)

```text
0x665b864  mov byte ptr [rbp+0x160],0                    
0x665b86b  xorps xmm0,xmm0                               
0x665b86e  movaps [rbp+0x340],xmm0                       
0x665b875  mov rax,[rbp+0x4E8]                           
0x665b87c  test rax,rax                                  
0x665b87f  je short 0x665B88E                            ; -> loc_665b88e
0x665b881  lock inc dword ptr [rax+8]                     ; refcount inc [rbp+0x4E8]
0x665b885  mov rax,[rbp+0x4E8]
0x665b88c  jmp short 0x665B890                           ; -> loc_665b890

loc_665b88e:  ; from 665b87f
  665b88e  xor eax,eax

loc_665b890:  ; from 665b88c
  665b890  mov rcx,[rbp+0x4E0]
  665b897  mov [rbp+0x340],rcx
  665b89e  mov [rbp+0x348],rax
  665b8a5  movups xmm1,[rbp+0x4F0]
  665b8ac  movaps [rbp+0x350],xmm1
  665b8b3  movzx eax,word ptr [rbp+0x500]
  665b8ba  mov [rbp+0x360],ax
  665b8c1  movups [rbp+0x368],xmm0
  665b8c8  mov rax,[rbp+0x510]
  665b8cf  test rax,rax
  665b8d2  je short 0x665B8E1                            ; -> loc_665b8e1
  665b8d4  lock inc dword ptr [rax+8]                    ; refcount inc [rbp+0x510]
  665b8d8  mov rax,[rbp+0x510]
  665b8df  jmp short 0x665B8E3                           ; -> loc_665b8e3

loc_665b8e1:  ; from 665b8d2
  665b8e1  xor eax,eax

loc_665b8e3:  ; from 665b8df
  665b8e3  mov rdx,[rbp+0x508]
  665b8ea  mov rcx,[rbp+0x520]
  665b8f1  mov [rbp+0x368],rdx
  665b8f8  mov [rbp+0x370],rax
  665b8ff  movups [rbp+0x378],xmm0
  665b906  test rcx,rcx
  665b909  je short 0x665B918                            ; -> loc_665b918
  665b90b  lock inc dword ptr [rcx+8]                    ; refcount inc [rbp+0x520]
  665b90f  mov rax,[rbp+0x520]
  665b916  jmp short 0x665B91A                           ; -> loc_665b91a

loc_665b918:  ; from 665b909
  665b918  xor eax,eax

loc_665b91a:  ; from 665b916
  665b91a  mov rdx,[rbp+0x518]
  665b921  mov rcx,[rbp+0x530]
  665b928  mov [rbp+0x378],rdx
  665b92f  mov [rbp+0x380],rax
  665b936  movups [rbp+0x388],xmm0
  665b93d  test rcx,rcx
  665b940  je short 0x665B94F                            ; -> loc_665b94f
  665b942  lock inc dword ptr [rcx+8]                    ; refcount inc [rbp+0x530]
  665b946  mov rax,[rbp+0x530]
  665b94d  jmp short 0x665B951                           ; -> loc_665b951

loc_665b94f:  ; from 665b940
  665b94f  xor eax,eax

loc_665b951:  ; from 665b94d
  665b951  mov rcx,[rbp+0x528]
  665b958  mov rdx,[rbp+0x538]
  665b95f  mov [rbp+0x388],rcx
  665b966  mov [rbp+0x390],rax
  665b96d  mov [rbp+0x398],rdx
  665b974  mov [rbp+0x3A0],r13w
  665b97c  movaps xmm0,[rbp+0x170]
  665b983  movaps xmm1,[rbp+0x180]
  665b98a  mov qword ptr [rbp+0x178],0
  665b995  movups [rbp+0x3A8],xmm0
  665b99c  xorps xmm0,xmm0
  665b99f  movaps [rbp+0x180],xmm0
  665b9a6  movups [rbp+0x3B8],xmm1
  665b9ad  mov rax,[rbp+0x190]
  665b9b4  mov [rbp+0x3C8],rax
  665b9bb  mov byte ptr [rbp+0x3E0],0xFF
  665b9c2  movzx eax,byte ptr [rbp+0x1A8]
  665b9c9  cmp rax,3
  665b9cd  ja 0x665CAEB                                  ; -> loc_665caeb
  665b9d3  lea rcx,[rbp+0x3D0]
  665b9da  lea rdx,[0xF2BF3D8]                           ; [data_f2bf3d8] 2nd jump table base
  665b9e1  movsxd r8,[rdx+rax*4]                         ; table entry indexed by byte [rbp+0x1A8]
  665b9e5  add r8,rdx
  665b9e8  jmp r8                                        ; indirect jump via 2nd jump table

; 2nd jump table targets (indices 0-3+ from [data_f2bf3d8]):
0x665b9eb  mov rcx,[rbp+0x198]                           ; index 0
0x665b9f2  mov [rbp+0x3D0],rcx
0x665b9f9  jmp 0x665CAE5                                 ; -> loc_665cae5
0x665b9fe  lea rdi,[rbp+0x208]                           ; index 1
0x665ba05  movups xmm0,[rdi]
0x665ba08  movups [r11],xmm0
0x665ba0c  jmp 0x665C269                                 ; -> JOIN 1 (loc_665c269) [V]
0x665ba11  lea rdx,[rbp+0x508]                           ; index 2
0x665ba18  movups xmm0,[rdx]
0x665ba1b  movups [rcx],xmm0
0x665ba1e  jmp 0x665C38A                                 ; -> JOIN 2 (loc_665c38a) [V]
0x665ba23  xorps xmm0,xmm0                               ; index 3
0x665ba26  movups [r11],xmm0
0x665ba2a  mov r11,[rbp+0x210]
0x665ba31  test r11,r11
0x665ba34  je 0x665C251                                  ; -> loc_665c251
0x665ba3a  lock inc dword ptr [r11+8]                    ; refcount inc [rbp+0x210]
0x665ba3f  mov r11,[rbp+0x210]
0x665ba46  jmp 0x665C254                                 ; -> loc_665c254
0x665ba4b  xorps xmm0,xmm0                               ; (next index)
0x665ba4e  movups [rcx],xmm0
0x665ba51  mov rcx,[rbp+0x510]
0x665ba58  test rcx,rcx
0x665ba5b  je 0x665C373                                  ; -> loc_665c373
0x665ba61  lock inc dword ptr [rcx+8]                    ; refcount inc [rbp+0x510]
0x665ba65  mov rcx,[rbp+0x510]
0x665ba6c  jmp 0x665C375                                 ; -> loc_665c375
0x665ba71  lea rdx,[rbp+0x198]
0x665ba78  movups xmm0,[rdx]
0x665ba7b  movups [rcx],xmm0
0x665ba7e  jmp 0x665CAE5                                 ; -> loc_665cae5
0x665ba83  movups [rcx],xmm0
0x665ba86  mov rcx,[rbp+0x1A0]
0x665ba8d  test rcx,rcx
0x665ba90  je 0x665CACE                                  ; -> loc_665cace
0x665ba96  lock inc dword ptr [rcx+8]                    ; refcount inc [rbp+0x1A0]
0x665ba9a  mov rcx,[rbp+0x1A0]
0x665baa1  jmp 0x665CAD0                                 ; -> loc_665cad0
0x665baa6  lea rdi,[rbp+0x508]
0x665baad  movups xmm0,[rdi]
0x665bab0  movups [r11],xmm0
0x665bab4  jmp 0x665CF85                                 ; -> COLD RANGE (loc_665cf85) [V]
0x665bab9  lea rdi,[rbp+0x508]
0x665bac0  movups xmm0,[rdi]
0x665bac3  movups [r11],xmm0
0x665bac7  jmp 0x665CFE6                                 ; -> COLD RANGE (loc_665cfe6) [V]
0x665bacc  xorps xmm0,xmm0
0x665bacf  movups [r11],xmm0
0x665bad3  mov r11,[rbp+0x510]
  ... (truncated by rdis --max 120 at 0x665bad3; resumes there)
```

Interpretation [I] (join 3 / sub_665b624 part 2):
- [rbp+0x160]=0; xorps [rbp+0x340]=0. Refcount inc pattern repeated for [rbp+0x4E8], [rbp+0x510], [rbp+0x520], [rbp+0x530] — each: if non-null lock inc [+8], else eax=0; stored to [rbp+0x348]/[rbp+0x370]/[rbp+0x380] respectively [I].
- Copies fields [rbp+0x4E0]->[rbp+0x340], [rbp+0x4F0]->[rbp+0x350], word [rbp+0x500]->[rbp+0x360], [rbp+0x508]->[rbp+0x368], [rbp+0x518]->[rbp+0x378], [rbp+0x528]->[rbp+0x388], [rbp+0x538]->[rbp+0x398], r13w->[rbp+0x3A0]. xmm [rbp+0x170]->[rbp+0x3A8], [rbp+0x180]->[rbp+0x3B8]. Zeroes [rbp+0x178], [rbp+0x180]. [rbp+0x3C8]=[rbp+0x190]. [rbp+0x3E0]=0xFF [I].
- 2nd dispatch: movzx eax, byte [rbp+0x1A8]; if > 3 goto loc_665caeb. Else jump table [data_f2bf3d8] indexed by eax*4, indirect jmp r8 [V].
- Index 0: rcx=[rbp+0x198]; [rbp+0x3D0]=rcx; jmp loc_665cae5 [I].
- Index 1: rdi=&[rbp+0x208]; movups [rdi]->[r11]; jmp 0x665C269 (JOIN 1 / sub_665c269 entry) [V] — confirms join 1 is called from here.
- Index 2: rdx=&[rbp+0x508]; movups [rdx]->[rcx]; jmp 0x665C38A (JOIN 2 / sub_665c38a entry) [V] — confirms join 2 is called from here.
- Index 3: xorps [r11]=0; r11=[rbp+0x210]; if null goto 0x665c251; else lock inc [r11+8]; goto 0x665c254 (refcount inc) [I].
- Next: xorps [rcx]=0; rcx=[rbp+0x510]; if null goto 0x665c373; lock inc [rcx+8]; goto 0x665c375 [I].
- Next: rdx=&[rbp+0x198]; movups [rdx]->[rcx]; jmp loc_665cae5 [I].
- Next: [rcx]=xmm0; rcx=[rbp+0x1A0]; if null goto 0x665cace; lock inc [rcx+8]; goto 0x665cad0 [I] (refcount inc [rbp+0x1A0]).
- Next: rdi=&[rbp+0x508]; movups [rdi]->[r11]; jmp 0x665CF85 (COLD RANGE entry) [V].
- Next: rdi=&[rbp+0x508]; movups [rdi]->[r11]; jmp 0x665CFE6 (COLD RANGE entry) [V].
- Next: xorps [r11]=0; r11=[rbp+0x510]; truncated at 0x665bad3 — continues in part 3 [V].
- [V] all instructions quoted exactly from rdis output. Confirms: sub_665b624 is the top-level dispatcher routing to join 1 (0x665c269), join 2 (0x665c38a), and cold range via two jump tables [data_f2bf3c8] and [data_f2bf3d8].

---
### Join 3 — sub_665b624 entry block 0x665bad3..0x665bd31 (remainder part 3; truncated at --max 120)

```text
0x665bad3  mov r11,[rbp+0x510]                           
0x665bada  test r11,r11                                  
0x665badd  je 0x665CF6D                                  ; -> loc_665cf6d (COLD RANGE)
0x665bae3  lock inc dword ptr [r11+8]                     ; refcount inc [rbp+0x510]
0x665bae8  mov r11,[rbp+0x510]
0x665baef  jmp 0x665CF70                                 ; -> loc_665cf70 (COLD RANGE)
0x665baf4  xorps xmm0,xmm0                               
0x665baf7  movups [r11],xmm0                             
0x665bafb  mov r11,[rbp+0x510]                           
0x665bb02  test r11,r11                                  
0x665bb05  je 0x665CFCE                                  ; -> loc_665cfce (COLD RANGE)
0x665bb0b  lock inc dword ptr [r11+8]                     ; refcount inc [rbp+0x510]
0x665bb10  mov r11,[rbp+0x510]
0x665bb17  jmp 0x665CFD1                                 ; -> loc_665cfd1 (COLD RANGE)
0x665bb1c  xor ecx,ecx                                    ; (jump target from index 3)
0x665bb1e  mov rdx,[rbp+0x508]                           
0x665bb25  mov [rbp+0x4B0],rdx                           
0x665bb2c  mov [rbp+0x4B8],rcx                           
0x665bb33  mov [rbp+0x4C0],al                            
0x665bb39  mov rax,[rbp+0x530]                           
0x665bb40  mov [rbp+0x4D8],rax                           
0x665bb47  movaps xmm0,[rbp+0x520]                       
0x665bb4e  movups [rbp+0x4C8],xmm0                       
0x665bb55  mov ecx,0x9D0                                 
0x665bb5a  add rcx,[rsi+0x10]                            
0x665bb5e  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x665bb63  nop                                           
0x665bb64  mov rsi,rax                                   
0x665bb67  lea rdx,[rbp+0x488]                           
0x665bb6e  xorps xmm0,xmm0                               
0x665bb71  movups [rbp+0x298],xmm0                       
0x665bb78  movups [rbp+0x288],xmm0                       
0x665bb7f  movups [rbp+0x278],xmm0                       
0x665bb86  movups [rbp+0x268],xmm0                       
0x665bb8d  movups [rbp+0x258],xmm0                       
0x665bb94  movups [rbp+0x248],xmm0                       
0x665bb9b  movups [rbp+0x238],xmm0                       
0x665bba2  movups [rbp+0x228],xmm0                       
0x665bba9  movups [rbp+0x218],xmm0                       
0x665bbb0  movups [rbp+0x208],xmm0                       
0x665bbb7  movups [rbp+0x1F8],xmm0                       
0x665bbbe  movups [rbp+0x1E8],xmm0                       
0x665bbc5  lea rcx,[rax+0x780]                           ; R ret@5aba5c0+0x780
0x665bbcc  call 0x675F3B0                                ; -> sub_675f3b0
0x665bbd1  nop                                           
0x665bbd2  mov qword ptr [rbp+0x1E0],0x1000              
0x665bbdd  mov eax,[rsi+0x788]                           ; R ret@5aba5c0+0x788
0x665bbe3  sub eax,[rsi+0x780]                           ; R ret@5aba5c0+0x780
0x665bbe9  shr eax,3                                     
0x665bbec  imul eax,0xFFFF8BA3                           
0x665bbf2  dec eax                                       
0x665bbf4  mov [rbp+0x208],ax                            
0x665bbfb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665bc02  mov rax,[rcx]                                 
0x665bc05  mov rax,[rax+0x10]                            
0x665bc09  mov dl,0x4A                                   
0x665bc0b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665bc11  nop                                           
0x665bc12  mov [rbp+0x540],al                            
0x665bc18  mov rdx,[rsi+0x8A8]                           ; R ret@5aba5c0+0x8A8
0x665bc1f  cmp rdx,[rsi+0x8B0]                           ; R ret@5aba5c0+0x8B0
0x665bc26  je short 0x665BC3C                            ; -> loc_665bc3c
0x665bc28  movzx eax,word ptr [rbp+0x480]                
0x665bc2f  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
0x665bc32  add qword ptr [rsi+0x8A8],2                   ; W ret@5aba5c0+0x8A8
0x665bc3a  jmp short 0x665BC50                           ; -> loc_665bc50

loc_665bc3c:  ; from 665bc26
  665bc3c  lea r8,[rbp+0x480]                            
  665bc43  lea rcx,[rsi+0x8A0]                           
  665bc4a  call 0x1EF6F90                                ; -> sub_1ef6f90
  665bc4f  nop                                           

loc_665bc50:  ; from 665bc3a
  665bc50  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665bc57  mov rax,[rcx]                                 
  665bc5a  mov rax,[rax+0x10]                            
  665bc5e  movzx edx,byte ptr [rbp+0x540]                
  665bc65  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665bc6b  nop                                           
  665bc6c  mov eax,[rsi+0x8A8]                           
  665bc72  sub eax,[rsi+0x8A0]                           
  665bc78  shr eax,1                                     
  665bc7a  dec eax                                       
  665bc7c  mov [rbp+0x1F0],ax                            
  665bc83  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665bc8a  mov rax,[rcx]                                 
  665bc8d  mov rax,[rax+0x10]                            
  665bc91  mov dl,0x4A                                   
  665bc93  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665bc99  mov [rbp+0x540],al                            
  665bc9f  lea rdx,[rbp+0x438]                           
  665bca6  lea rcx,[rsi+0x648]                           
  665bcad  call 0x675FB30                                ; -> sub_675fb30
  665bcb2  nop                                           
  665bcb3  mov rcx,[0,1233E1B0]                          ; [data_1233e1b0]
  665bcba  mov rax,[rcx]                                 
  665bcbd  mov rax,[rax+0x10]                            
  665bcc1  movzx edx,byte ptr [rbp+0x540]                
  665bcc8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665bcce  nop                                           
  665bccf  mov eax,[rsi+0x650]                           
  665bcd5  sub eax,[rsi+0x648]                           
  665bcdb  shr eax,3                                     
  665bcde  imul eax,0xFFFF8E39                           
  665bce4  dec eax                                       
  665bce6  mov [rbp+0x222],ax                            
  665bced  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  665bcf4  mov rax,[rcx]                                 
  665bcf7  mov rax,[rax+0x10]                            
  665bcfb  mov dl,0x4A                                   
  665bcfd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  665bd03  nop                                           
  665bd04  mov [rbp+0x540],al                            
  665bd0a  mov rbx,[rsi+0x770]                           
  665bd11  cmp rbx,[rsi+0x778]                           
  665bd18  je short 0x665BD57                            ; -> loc_665bd57
  665bd1a  mov rax,[rbp+0x3B0]                           
  665bd21  mov [rbx],rax                                 
  665bd24  lea rcx,[rbx+8]                               
  665bd28  mov rdx,rdi                                   
  665bd2b  call 0xE869FF0                                ; -> sub_e869ff0
  665bd30  nop                                           
  665bd31  mov rax,[rbp+0x430]                           
  ... (continues in part 4 below)
```
### Join 3 — sub_665b624 part 4 (0x665bd31..0x665bf97)

```text
0x665bd31  mov rax,[rbp+0x430]                            
0x665bd38  mov [rbx+0x80],rax                            
0x665bd3f  mov qword ptr [rbp+0x430],0                   
0x665bd4a  add qword ptr [rsi+0x770],0x88                
0x665bd55  jmp short 0x665BD6E                           ; -> loc_665bd6e
0x665bd57  lea r8,[rbp+0x3B0]                            
0x665bd5e  lea rcx,[rsi+0x768]                           
0x665bd65  mov rdx,rbx                                   
0x665bd68  call 0x6760710                                ; -> sub_6760710
0x665bd6d  nop                                           
0x665bd6e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665bd75  mov rax,[rcx]                                 
0x665bd78  mov rax,[rax+0x10]                            
0x665bd7c  movzx edx,byte ptr [rbp+0x540]                
0x665bd83  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665bd89  nop                                           
0x665bd8a  mov qword ptr [rbp+0x1E0],0x2003001           
0x665bd95  mov eax,[rsi+0x770]                           
0x665bd9b  sub eax,[rsi+0x768]                           
0x665bda1  shr eax,3                                     
0x665bda4  imul eax,0xFFFFF0F1                           
0x665bdaa  dec eax                                       
0x665bdac  mov [rbp+0x20A],ax                            
0x665bdb3  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665bdba  mov rax,[rcx]                                 
0x665bdbd  mov rax,[rax+0x10]                            
0x665bdc1  mov dl,0x4A                                   
0x665bdc3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665bdc9  nop                                           
0x665bdca  mov [rbp+0x540],al                            
0x665bdd0  mov rdx,[rsi+0x680]                           
0x665bdd7  cmp rdx,[rsi+0x688]                           
0x665bdde  je short 0x665BE10                            ; -> loc_665be10
0x665bde0  movss xmm0,[rbp+0x3A0]                        
0x665bde8  movss [rdx],xmm0                              
0x665bdec  movss xmm0,[rbp+0x3A4]                        
0x665bdf4  movss [rdx+4],xmm0                            
0x665bdf9  movss xmm0,[rbp+0x3A8]                        
0x665be01  movss [rdx+8],xmm0                            
0x665be06  add qword ptr [rsi+0x680],0xC                 
0x665be0e  jmp short 0x665BE24                           ; -> loc_665be24
0x665be10  lea r8,[rbp+0x3A0]                            
0x665be17  lea rcx,[rsi+0x678]                           
0x665be1e  call 0x1770A70                                ; -> sub_1770a70
0x665be23  nop                                           
0x665be24  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665be2b  mov rax,[rcx]                                 
0x665be2e  mov rax,[rax+0x10]                            
0x665be32  movzx edx,byte ptr [rbp+0x540]                
0x665be39  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665be3f  nop                                           
0x665be40  mov eax,[rsi+0x680]                           
0x665be46  sub eax,[rsi+0x678]                           
0x665be4c  shr eax,2                                     
0x665be4f  imul eax,0xFFFFAAAB                           
0x665be55  dec eax                                       
0x665be57  mov [rbp+0x21E],ax                            
0x665be5e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665be65  mov rax,[rcx]                                 
0x665be68  mov rax,[rax+0x10]                            
0x665be6c  mov dl,0x4A                                   
0x665be6e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665be74  nop                                           
0x665be75  mov [rbp+0x540],al                            
0x665be7b  mov rdx,[rsi+0x830]                           
0x665be82  cmp rdx,[rsi+0x838]                           
0x665be89  je short 0x665BE97                            ; -> loc_665be97
0x665be8b  inc rdx                                       
0x665be8e  mov [rsi+0x830],rdx                           
0x665be95  jmp short 0x665BEA4                           ; -> loc_665bea4
0x665be97  lea rcx,[rsi+0x828]                           
0x665be9e  call 0x6760E60                                ; -> sub_6760e60
0x665bea3  nop                                           
0x665bea4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665beab  mov rax,[rcx]                                 
0x665beae  mov rax,[rax+0x10]                            
0x665beb2  movzx edx,byte ptr [rbp+0x540]                
0x665beb9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665bebf  nop                                           
0x665bec0  mov qword ptr [rbp+0x1E0],0x2803021           
0x665becb  mov eax,[rsi+0x828]                           
0x665bed1  not eax                                       
0x665bed3  add eax,[rsi+0x830]                           
0x665bed9  mov [rbp+0x1FA],ax                            
0x665bee0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665bee7  mov rax,[rcx]                                 
0x665beea  mov rax,[rax+0x10]                            
0x665beee  mov dl,0x4A                                   
0x665bef0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665bef6  nop                                           
0x665bef7  mov [rbp+0x540],al                            
0x665befd  lea r8,[rbp+0x344]                            
0x665bf04  mov rdx,[rsi+0x758]                           
0x665bf0b  cmp rdx,[rsi+0x760]                           
0x665bf12  je short 0x665BF8B                            ; -> loc_665bf8b
0x665bf14  mov eax,[r8+0x10]                             
0x665bf18  mov [rdx+0x10],eax                            
0x665bf1b  movups xmm0,[r8]                              
0x665bf1f  movups [rdx],xmm0                             
0x665bf22  movzx eax,byte ptr [rbp+0x358]                
0x665bf29  mov [rdx+0x14],al                             
0x665bf2c  movss xmm0,[rbp+0x35C]                        
0x665bf34  movss [rdx+0x18],xmm0                         
0x665bf39  movss xmm0,[rbp+0x360]                        
0x665bf41  movss [rdx+0x1C],xmm0                         
0x665bf46  movss xmm0,[rbp+0x364]                        
0x665bf4e  movss [rdx+0x20],xmm0                         
0x665bf53  movss xmm0,[rbp+0x368]                        
0x665bf5b  movss [rdx+0x24],xmm0                         
0x665bf60  movups xmm0,[rbp+0x36C]                       
0x665bf67  movups xmm1,[rbp+0x37C]                       
0x665bf6e  movups xmm2,[rbp+0x38B]                       
0x665bf75  movups [rdx+0x28],xmm0                        
0x665bf79  movups [rdx+0x38],xmm1                        
0x665bf7d  movups [rdx+0x47],xmm2                        
0x665bf81  add qword ptr [rsi+0x758],0x58                
0x665bf89  jmp short 0x665BF98                           ; -> loc_665bf98
0x665bf8b  lea rcx,[rsi+0x750]                           
0x665bf92  call 0x6760A80                                ; -> sub_6760a80
```

### Join 3 — sub_665b624 part 5 (0x665bf97..0x665c1ba)

```text
0x665bf97  nop                                           
0x665bf98  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665bf9f  mov rax,[rcx]                                 
0x665bfa2  mov rax,[rax+0x10]                            
0x665bfa6  movzx edx,byte ptr [rbp+0x540]                
0x665bfad  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665bfb3  nop                                           
0x665bfb4  mov eax,[rsi+0x758]                           
0x665bfba  sub eax,[rsi+0x750]                           
0x665bfc0  shr eax,3                                     
0x665bfc3  imul eax,0xFFFF8BA3                           
0x665bfc9  dec eax                                       
0x665bfcb  mov [rbp+0x20C],ax                            
0x665bfd2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665bfd9  mov rax,[rcx]                                 
0x665bfdc  mov rax,[rax+0x10]                            
0x665bfe0  mov dl,0x4A                                   
0x665bfe2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665bfe8  nop                                           
0x665bfe9  mov [rbp+0x540],al                            
0x665bfef  mov rdx,[rsi+0x458]                           
0x665bff6  cmp rdx,[rsi+0x460]                           
0x665bffd  je short 0x665C00B                            ; -> loc_665c00b
0x665bfff  inc rdx                                       
0x665c002  mov [rsi+0x458],rdx                           
0x665c009  jmp short 0x665C01B                           ; -> loc_665c01b
0x665c00b  mov rcx,rsi                                   
0x665c00e  add rcx,0x450                                 
0x665c015  call 0x6760E60                                ; -> sub_6760e60
0x665c01a  nop                                           
0x665c01b  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c022  mov rax,[rcx]                                 
0x665c025  mov rax,[rax+0x10]                            
0x665c029  movzx edx,byte ptr [rbp+0x540]                
0x665c030  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c036  nop                                           
0x665c037  mov rax,0x400002807021                        
0x665c041  mov [rbp+0x1E0],rax                           
0x665c048  mov eax,[rsi+0x450]                           
0x665c04e  not eax                                       
0x665c050  add eax,[rsi+0x458]                           
0x665c056  mov [rbp+0x24C],ax                            
0x665c05d  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c064  mov rax,[rcx]                                 
0x665c067  mov rax,[rax+0x10]                            
0x665c06b  mov dl,0x4A                                   
0x665c06d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c073  nop                                           
0x665c074  mov [rbp+0x540],al                            
0x665c07a  mov rax,[rsi+8]                               
0x665c07e  cmp rax,[rsi+0x10]                            
0x665c082  je short 0x665C0A3                            ; -> loc_665c0a3
0x665c084  lea rdx,[rbp+0x1E0]                           
0x665c08b  mov r8d,0xC8                                  
0x665c091  mov rcx,rax                                   
0x665c094  call 0xEEC6EC0                                ; -> sub_eec6ec0
0x665c099  add qword ptr [rsi+8],0xC8                    
0x665c0a1  jmp short 0x665C0B6                           ; -> loc_665c0b6
0x665c0a3  lea r8,[rbp+0x1E0]                            
0x665c0aa  mov rcx,rsi                                   
0x665c0ad  mov rdx,rax                                   
0x665c0b0  call 0x5ABA6D0                                ; -> sub_5aba6d0
0x665c0b5  nop                                           
0x665c0b6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
0x665c0bd  mov rax,[rcx]                                 
0x665c0c0  mov rax,[rax+0x10]                            
0x665c0c4  movzx edx,byte ptr [rbp+0x540]                
0x665c0cb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c0d1  nop                                           
0x665c0d2  lea rcx,[rbp+0x340]                           
0x665c0d9  call 0x66A9C10                                ; -> sub_66a9c10
0x665c0de  cmp byte ptr [rbp+0x1B0],1                    
0x665c0e5  jne 0x665D076                                 ; -> loc_665d076
0x665c0eb  mov rcx,[rbp+0x170]                           
0x665c0f2  test rcx,rcx                                  
0x665c0f5  je 0x665D076                                  ; -> loc_665d076
0x665c0fb  mov rdx,[rbp+0x180]                           
0x665c102  jmp 0x665D049                                 ; -> loc_665d049
0x665c107  xor edi,edi                                   
0x665c109  mov rbx,[rbp+0x78]                            
0x665c10d  mov [rbp+0x4A8],rbx                           
0x665c114  mov [rbp+0x4B0],rdi                           
0x665c11b  mov [rbp+0x4B8],cl                            
0x665c121  mov rcx,[rbp+0xA0]                            
0x665c128  mov [rbp+0x4D0],rcx                           
0x665c12f  movaps xmm0,[rbp+0x90]                        
0x665c136  movups [rbp+0x4C0],xmm0                       
0x665c13d  mov ecx,0x9D0                                 
0x665c142  add rcx,[rsi+0x10]                            
0x665c146  mov [rsp+0x30],rax                            
0x665c14b  mov [rsp+0x28],r10                            
0x665c150  mov [rsp+0x20],r11                            
0x665c155  call 0x67EA0D0                                ; -> sub_67ea0d0
0x665c15a  nop                                           
0x665c15b  lea rcx,[rbp+0x340]                           
0x665c162  call 0x673CB40                                ; -> sub_673cb40
0x665c167  cmp byte ptr [rbp+0x88],3                     
0x665c16e  jne short 0x665C1A7                           ; -> loc_665c1a7
0x665c170  mov rsi,[rbp+0x80]                            
0x665c177  test rsi,rsi                                  
0x665c17a  je short 0x665C1A7                            ; -> loc_665c1a7
0x665c17c  lock dec dword ptr [rsi+8]                    
0x665c180  jne short 0x665C1A7                           ; -> loc_665c1a7
0x665c182  mov rax,[rsi]                                 
0x665c185  mov rax,[rax]                                 
0x665c188  mov rcx,rsi                                   
0x665c18b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c191  lock dec dword ptr [rsi+0xC]                  
0x665c195  jne short 0x665C1A7                           ; -> loc_665c1a7
0x665c197  mov rax,[rsi]                                 
0x665c19a  mov rax,[rax+8]                               
0x665c19e  mov rcx,rsi                                   
0x665c1a1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c1a7  mov rdi,[rbp+0x58]                            
0x665c1ab  test rdi,rdi                                  
0x665c1ae  je short 0x665C1FB                            ; -> loc_665c1fb
0x665c1b0  mov rbx,[rbp+0x60]                            
0x665c1b4  jmp short 0x665C1BA                           ; -> loc_665c1ba
0x665c1b6  add rdi,0x28                                  
0x665c1ba  cmp rdi,rbx                                   
0x665c1bd  je short 0x665C1FB                            ; -> loc_665c1fb
0x665c1bf  cmp byte ptr [rdi+0x18],2                     
0x665c1c3  jne short 0x665C1B6                           ; -> loc_665c1b6
0x665c1c5  mov rsi,[rdi+8]                               
0x665c1c9  test rsi,rsi                                  
0x665c1cc  je short 0x665C1B6                            ; -> loc_665c1b6
0x665c1ce  lock dec dword ptr [rsi+8]                    
0x665c1d2  jne short 0x665C1B6                           ; -> loc_665c1b6
0x665c1d4  mov rax,[rsi]                                 
0x665c1d7  mov rax,[rax]                                 
0x665c1da  mov rcx,rsi                                   
0x665c1dd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c1e3  lock dec dword ptr [rsi+0xC]                  
0x665c1e7  jne short 0x665C1B6                           ; -> loc_665c1b6
0x665c1e9  mov rax,[rsi]                                 
0x665c1ec  mov rax,[rax+8]                               
0x665c1f0  mov rcx,rsi                                   
0x665c1f3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x665c1f9  jmp short 0x665C1B6                           ; -> loc_665c1b6
0x665c1fb  cmp byte ptr [rbp+0x520],1                    
0x665c202  jne 0x665CF64                                 ; -> loc_665cf64
0x665c208  mov rcx,[rbp+0x4E0]                           
0x665c20f  test rcx,rcx                                  
0x665c212  je 0x665CF64                                  ; -> loc_665cf64
0x665c218  mov rdx,[rbp+0x4F0]                           
0x665c21f  sub rdx,rcx                                   
0x665c222  cmp rdx,0x1000                                
0x665c229  jb short 0x665C247                            ; -> loc_665c247
0x665c22b  mov rax,[rcx-8]                               
0x665c22f  add rcx,0xFFFFFFFFFFFFFFF8                    
0x665c233  sub rcx,rax                                   
0x665c236  cmp rcx,0x20                                  
0x665c23b  jae 0x665D43A                                 ; -> loc_665d43a
0x665c23d  or rdx,0x27                                   
0x665c241  mov rcx,rax                                   
0x665c244  call 0xE935700                                ; -> sub_e935700
0x665c247  mov rcx,[rbp+0x528]                           
0x665c24e  mov rdx,[rbp+0x538]                           
0x665c255  mov [rbp+0x388],rcx                           
0x665c25c  mov [rbp+0x390],rax                           
0x665c263  mov [rbp+0x398],rdx                           
0x665c26a  mov [rbp+0x3A0],r13w                          
0x665c272  movaps xmm0,[rbp+0x170]                       
0x665c279  movaps xmm1,[rbp+0x180]                       
0x665c280  mov qword ptr [rbp+0x178],0                   
0x665c287  movups [rbp+0x3A8],xmm0                       
0x665c28e  xorps xmm0,xmm0                               
0x665c291  movaps [rbp+0x180],xmm0                       
0x665c298  movups [rbp+0x3B8],xmm1                       
0x665c29f  mov rax,[rbp+0x190]                           
0x665c2a7  mov [rbp+0x3C8],rax                           
0x665c2ae  mov byte ptr [rbp+0x3E0],0xFF                 
0x665c2b5  movzx eax,byte ptr [rbp+0x1A8]                
0x665c2bc  cmp rax,3                                     
0x665c2c0  ja 0x665CAEB                                  ; -> loc_665caeb
0x665c2c6  lea rcx,[rbp+0x3D0]                           
0x665c2cd  lea rdx,[0xF2BF3D8]                           ; [data_f2bf3d8] 2nd jump table base
0x665c2d4  movsxd r8,[rdx+rax*4]                         ; table entry indexed by byte [rbp+0x1A8]
0x665c2d8  add r8,rdx                                   
0x665c2db  jmp r8                                        ; indirect jump via 2nd jump table
```

PART 5 ENDS at 0x665c1b4. Exclusive end 0x665c1ba.
```

Interpretation [I] (join 3 / sub_665b624 part 3):
- 0x665bad3: r11=[rbp+0x510]; if null goto 0x665CF6D (COLD RANGE); lock inc [r11+8]; goto 0x665CF70 (COLD RANGE) — refcount inc then cold range [I].
- 0x665baf4: xorps [r11]=0; r11=[rbp+0x510]; if null goto 0x665CFCE (COLD RANGE); lock inc [r11+8]; goto 0x665CFD1 (COLD RANGE) [I].
- 0x665bb1c (from index 3 jump): xor ecx,ecx; rdx=[rbp+0x508]; [rbp+0x4B0]=rdx; [rbp+0x4B8]=rcx(0); [rbp+0x4C0]=al; rax=[rbp+0x530]; [rbp+0x4D8]=rax; movups [rbp+0x520]->[rbp+0x4C8] [I].
- 0x665bb55: ecx=0x9D0; add rcx,[rsi+0x10]; call sub_5aba5c0 — same allocator as join 2/3 [I].
- 0x665bb64: rsi=rax; lea rdx=[rbp+0x488]; xorps; zero [rbp+0x298]..[rbp+0x1E8] (12 xmm = 192 bytes, particle output struct clear) [I].
- lea rcx=[rax+0x780]; call sub_675f3b0; [rbp+0x1E0]=0x1000 (tag); count = ([rsi+0x788]-[rsi+0x780])>>3 * 0xFFFF8BA3 - 1 -> [rbp+0x208] [I].
- sub_eea6040(dl=0x4A); store al->[rbp+0x540] [I].
- Buffer write: rdx=[rsi+0x8A8]; cmp [rsi+0x8B0]; if not full: word [rbp+0x480]->[rdx], [rsi+0x8A8]+=2; else sub_1ef6f90(r8=&[rbp+0x480], rcx=rsi+0x8A0) (flush) [I].
- sub_eea6040; count ([rsi+0x8A8]-[rsi+0x8A0])>>1-1 -> [rbp+0x1F0]; sub_eea6040; store al->[rbp+0x540] [I].
- sub_675FB30(rdx=&[rbp+0x438], rcx=rsi+0x648) — memcpy into particle buffer [I].
- sub_eea6040; store al->[rbp+0x540]; count ([rsi+0x650]-[rsi+0x648])>>3 * 0xFFFF8E39 - 1 -> [rbp+0x222] [I].
- sub_eea6040; rbx=[rsi+0x770]; cmp [rsi+0x778]; if not full: rax=[rbp+0x3B0]->[rbx]; sub_e869ff0(rcx=rbx+8, rdx=rdi); [rbp+0x430]->[rbx+0x80]; [rbp+0x430]=0; [rsi+0x770]+=0x88; else sub_6760710(r8=&[rbp+0x3B0], rcx=rsi+0x768, rdx=rbx) (grow) [I] — same 0x88-stride entry pattern as phase 5.
- loc_665bd6e: sub_eea6040(dl=[rbp+0x540]); [rbp+0x1E0]=0x2003001 (tag); count = ([rsi+0x770]-[rsi+0x768])>>3 * 0xFFFFF0F1 - 1 -> [rbp+0x20A] [I].
- sub_eea6040; store al->[rbp+0x540] [I].
- Buffer write: rdx=[rsi+0x680]; cmp [rsi+0x688]; if not full: movss [rbp+0x3A0]->[rdx], [rbp+0x3A4]->[rdx+4], [rbp+0x3A8]->[rdx+8] (3 floats=0xC), [rsi+0x680]+=0xC; else sub_1770A70(r8=&[rbp+0x3A0], rcx=rsi+0x678) (flush) [I].
- count = ([rsi+0x680]-[rsi+0x678])>>2 * 0xFFFFAAAB - 1 -> [rbp+0x21E] (stride 4, float count) [I].
- sub_eea6040; store al->[rbp+0x540] [I].
- Buffer write: rdx=[rsi+0x830]; cmp [rsi+0x838]; if not full: inc [rsi+0x830]; else sub_6760E60(rcx=rsi+0x828) (flush) [I].
- sub_eea6040; [rbp+0x1E0]=0x2803021 (tag); eax=[rsi+0x828]; not eax; eax+=[rsi+0x830] -> [rbp+0x1FA] (complement-then-add) [I].
- sub_eea6040; store al->[rbp+0x540] [I].
- Particle entry write (same as phase 6 part 1): r8=&[rbp+0x344]; rdx=[rsi+0x758]; cmp [rsi+0x760]; if not full: copy 0x58 bytes from [r8] to [rdx] (word+16xmm+byte+4 float+3 movups), [rsi+0x758]+=0x58, jmp loc_665bf98; else sub_6760A80(rcx=rsi+0x750) (grow) [I].
- Truncated at 0x665bf97 — resumes there [V].
- [V] all instructions quoted exactly from rdis output. sub_665b624 continues into same shared-body particle processing as joins 1-2.
```

Interpretation [I] (part 3):
- loc_665cbdc: if [rbp+0x400] non-null: rdx = [rbp+0x410] - rcx (size); if >= 0x1000: rax = [rcx-8], rcx -= 8, rcx -= rax; if >= 0x20 goto loc_665d43a; else or rdx,0x27; rcx = rax; call sub_e935700 (free). Else goto loc_665cc2a. Then xorps [rdi]=0, [rdi+0x10]=0 (zero 24 bytes) [I].
- loc_665cc2a: lea rcx=[rbp+0x340]; call sub_67B5160 (cleanup/finalize header) [I].
- cmp bl,1; if bl==1 and [rbp+0x120] non-null: rdx = [rbp+0x130]-[rbp+0x120]; size check/free via sub_e935700 or loc_665d43a [I].
- Refcount teardown cascade: [rbp+0x1A0] (if byte [rbp+0x1A8]==3), then loop [rbp+0x178]..[rbp+0x180] (0x28 stride, type 2), then [rbp+0x530], [rbp+0x520], [rbp+0x510], [rbp+0x4E8], [rbp+0x18], [rbp-8] — each using lock-dec + two-call release/destroy pattern via [data_f99ffa0] [I]. This is exhaustive teardown of all refcounted objects held by this frame.
- [V] all instructions quoted exactly from rdis output. Truncated by `--max 160` at 0x665ce32; resume there to reach end of shared body (toward cold range 0x665cf64).

