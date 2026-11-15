# Progress: U-GF Gameface extractor 0x66ade80

## NEXT
Resume at 0x66afe7a (pass-entry push done). Remaining OPEN: Viewport write not found in 0x66af0c0..0x66af263 — only Data_VS (r15+0x50/0x58) and Data_PS (r15+0x60/0x68) are written via 0x5679db0 in this range. Need to check if Viewport is written via 0x5679db0 at a different RVA or via r15+0x70 elsewhere.

---

## Phase 1: Data_VS uniform write (0x66af0c0..0x66af192) [V disassembly]

### Instructions

```
0x66af0c0  cmp qword ptr [r15+0x58],0                      ; check Data_VS size != 0 (rec+0x58 = size)
0x66af0c5  je 0x66AF193                                     ; skip if zero -> Data_PS block
0x66af0cb  mov eax,[0x129F8F28]                            ; Data_VS static count (data_129f8f28)
0x66af0d1  mov ecx,[0x128767C8]                            ; TLS index (data_128767c8)
0x66af0d7  mov rdx,gs:[0x58]                                ; TLS base
0x66af0e0  mov rcx,[rdx+rcx*8]                              ; TLS slot array
0x66af0e4  cmp eax,[rcx+4]                                  ; compare vs static init counter
0x66af0ea  jg 0x66B0046                                     ; if not initialized -> static init handler
; --- fallthrough: table already initialized ---
loc_66af0f0:
0x66af0f0  mov rax,[r15+0x50]                              ; Data_VS ptr (rec+0x50)
0x66af0f4  mov qword ptr [rbp+0x320],0x80                   ; size = 0x80
0x66af0ff  mov [rbp+0x328],rax                              ; ptr = rec+0x50
0x66af106  test rax,rax                                     ; null check
0x66af109  je 0x66B0495                                     ; null -> error path
0x66af10f  mov rax,[rbp+0x90]                              ; table base (Data_VS slot table)
0x66af116  movzx r8d,word ptr [rbp+0x9A]                   ; index word
0x66af11e  mov edx,r8d
0x66af121  shl edx,4                                        ; index * 16 (entry stride)
0x66af124  mov rcx,rax
0x66af127  test r8d,r8d
0x66af12a  je short 0x66AF160                               ; index 0 -> skip search
0x66af12c  mov r8,[0x129F8F20]                             ; Data_VS static table ptr (data_129f8f20)
0x66af133  mov r9,rdx
0x66af136  mov rcx,rax
0x66af139  nop [rax]
loc_66af140:
0x66af140  mov r10,[rcx]                                    ; load table entry
0x66af143  cmp [r10+0x28],r8                                ; compare entry slot vs index
0x66af147  je short 0x66AF160                               ; match found
0x66af149  add rcx,0x10                                     ; next entry (stride 0x10)
0x66af14d  add r9,0xFFFFFFFFFFFFFFF0                        ; remaining count -= 16
0x66af151  jne short 0x66AF140                              ; loop
0x66af153  jmp short 0x66AF193                              ; not found -> skip
loc_66af160:
0x66af160  add rdx,rax                                      ; end = start + remaining
0x66af163  cmp rcx,rdx
0x66af166  jae short 0x66AF193                              ; past end -> not found
0x66af168  sub ecx,eax                                      ; offset from table start
0x66af16a  shr ecx,4                                        ; index = offset >> 4
0x66af16d  mov [rbp+0x208],cx                               ; store index word
0x66af174  mov byte ptr [rbp+0x20A],1                       ; flag byte = 1
0x66af17b  lea rcx,[rbp+0x60]                               ; uniform ctx object
0x66af17f  lea rdx,[rbp+0x208]                              ; {index, flag}
0x66af186  lea r8,[rbp+0x320]                               ; {size=0x80, ptr=rec+0x50}
0x66af18d  call 0x5679DB0                                   ; write uniform to slot
```

### C-like statement

```c
if (rec->Data_VS_size != 0) {                          // [r15+0x58]
    Data_VS_static_guard();                             // [0x129F8F28], [0x128767C8], gs:[0x58]
    u32 slot_idx = find_slot(Data_VS_table, word[rbp+0x9A] << 4); // [0x129F8F20], stride 0x10
    u8 uniform_ctx = rbp+0x60;
    u8 slot_word[2] = { slot_idx, 1 };
    uniform_write(uniform_ctx, slot_word, {0x80, rec->Data_VS_ptr}); // 0x5679db0, [r15+0x50]
}
```

### Struct fields touched
| Offset | Size | Direction | Meaning | Tag |
|--------|------|-----------|---------|-----|
| rec+0x50 | 8 | R | Data_VS pointer | [V] |
| rec+0x58 | 8 | R | Data_VS size (expect 0x80) | [V] |
| [rbp+0x90] | 8 | R | Data_VS slot table base | [V] |
| [rbp+0x9A] | 2 | R | Index word into table | [V] |
| [0x129F8F20] | 8 | R | Data_VS static table | [V] |
| [0x129F8F28] | 4 | R | Data_VS static count | [V] |
| [0x128767C8] | 4 | R | TLS index | [V] |
| gs:[0x58] | 8 | R | TLS base | [V] |
| rbp+0x320 | 8 | W | size = 0x80 | [V] |
| rbp+0x328 | 8 | W | ptr = rec+0x50 | [V] |
| rbp+0x208 | 2 | W | slot index word | [V] |
| rbp+0x20A | 1 | W | flag = 1 | [V] |

### Callees
- 0x5679DB0: uniform slot write (Data_VS) [V]

---

## Phase 2: Data_PS uniform write (0x66af193..0x66af262) [V disassembly]

### Instructions

```
loc_66af193:
0x66af193  cmp qword ptr [r15+0x68],0                      ; check Data_PS size != 0 (rec+0x68 = size)
0x66af198  je 0x66AF263                                     ; skip if zero -> mat4 block
0x66af19e  mov eax,[0x129F8F38]                            ; Data_PS static count (data_129f8f38)
0x66af1a4  mov ecx,[0x128767C8]                            ; TLS index (data_128767c8)
0x66af1aa  mov rdx,gs:[0x58]                                ; TLS base
0x66af1b3  mov rcx,[rdx+rcx*8]                              ; TLS slot array
0x66af1b7  cmp eax,[rcx+4]                                  ; compare vs static init counter
0x66af1bd  jg 0x66B00BD                                     ; if not initialized -> static init handler
; --- fallthrough: table already initialized ---
loc_66af1c3:
0x66af1c3  mov rax,[r15+0x60]                              ; Data_PS ptr (rec+0x60)
0x66af1c7  mov qword ptr [rbp+0x320],0x80                   ; size = 0x80
0x66af1d2  mov [rbp+0x328],rax                              ; ptr = rec+0x60
0x66af1d9  test rax,rax                                     ; null check
0x66af1dc  je 0x66B0495                                     ; null -> error path
0x66af1e2  mov rax,[rbp+0x90]                              ; table base (Data_PS slot table)
0x66af1e9  movzx r8d,word ptr [rbp+0x9A]                   ; index word (same as Data_VS)
0x66af1f1  mov edx,r8d
0x66af1f4  shl edx,4                                        ; index * 16
0x66af1f7  mov rcx,rax
0x66af1fa  test r8d,r8d
0x66af1fd  je short 0x66AF230                               ; index 0 -> skip search
0x66af1ff  mov r8,[0x129F8F30]                             ; Data_PS static table ptr (data_129f8f30)
0x66af206  mov r9,rdx
0x66af209  mov rcx,rax
0x66af20c  nop [rax]
loc_66af210:
0x66af210  mov r10,[rcx]                                    ; load table entry
0x66af213  cmp [r10+0x28],r8                                ; compare entry slot vs index
0x66af217  je short 0x66AF230                               ; match found
0x66af219  add rcx,0x10                                     ; next entry (stride 0x10)
0x66af21d  add r9,0xFFFFFFFFFFFFFFF0                        ; remaining count -= 16
0x66af221  jne short 0x66AF210                              ; loop
0x66af223  jmp short 0x66AF263                              ; not found -> skip
loc_66af230:
0x66af230  add rdx,rax                                      ; end = start + remaining
0x66af233  cmp rcx,rdx
0x66af236  jae short 0x66AF263                              ; past end -> not found
0x66af238  sub ecx,eax                                      ; offset from table start
0x66af23a  shr ecx,4                                        ; index = offset >> 4
0x66af23d  mov [rbp+0x208],cx                               ; store index word (overwrites Data_VS index)
0x66af244  mov byte ptr [rbp+0x20A],1                       ; flag byte = 1
0x66af24b  lea rcx,[rbp+0x60]                               ; uniform ctx object (same as Data_VS)
0x66af24f  lea rdx,[rbp+0x208]                              ; {index, flag}
0x66af256  lea r8,[rbp+0x320]                               ; {size=0x80, ptr=rec+0x60}
0x66af25d  call 0x5679DB0                                   ; write uniform to slot
```

### C-like statement

```c
if (rec->Data_PS_size != 0) {                              // [r15+0x68]
    Data_PS_static_guard();                                // [0x129F8F38], [0x128767C8], gs:[0x58]
    u32 slot_idx = find_slot(Data_PS_table, word[rbp+0x9A] << 4); // [0x129F8F30], stride 0x10
    u8 uniform_ctx = rbp+0x60;
    u8 slot_word[2] = { slot_idx, 1 };
    uniform_write(uniform_ctx, slot_word, {0x80, rec->Data_PS_ptr}); // 0x5679db0, [r15+0x60]
}
```

### Struct fields touched
| Offset | Size | Direction | Meaning | Tag |
|--------|------|-----------|---------|-----|
| rec+0x60 | 8 | R | Data_PS pointer | [V] |
| rec+0x68 | 8 | R | Data_PS size (expect 0x80) | [V] |
| [rbp+0x90] | 8 | R | Data_PS slot table base | [V] |
| [rbp+0x9A] | 2 | R | Index word into table (same as Data_VS) | [V] |
| [0x129F8F30] | 8 | R | Data_PS static table | [V] |
| [0x129F8F38] | 4 | R | Data_PS static count | [V] |
| [0x128767C8] | 4 | R | TLS index | [V] |
| gs:[0x58] | 8 | R | TLS base | [V] |
| rbp+0x320 | 8 | W | size = 0x80 | [V] |
| rbp+0x328 | 8 | W | ptr = rec+0x60 | [V] |
| rbp+0x208 | 2 | W | slot index word (overwrites Data_VS index) | [V] |
| rbp+0x20A | 1 | W | flag = 1 | [V] |

### Callees
- 0x5679DB0: uniform slot write (Data_PS) [V]

---

## Phase 3: Viewport write (0x66af0c0..0x66af263) [V disassembly — NOT FOUND in range]

### Observation

No Viewport write instruction exists within 0x66af0c0..0x66af263. The range contains exactly two calls to `0x5679DB0`:
1. At 0x66af18d: Data_VS (ptr from [r15+0x50], size from [r15+0x58])
2. At 0x66af25d: Data_PS (ptr from [r15+0x60], size from [r15+0x68])

There is no third block for Viewport (no check of [r15+0x70] or similar, no third call to 0x5679DB0). The block at 0x66af263 immediately transitions to mat4 buffer allocation (`mov rax,[r15+0x138]`).

**Conclusion**: Viewport is NOT written in the range 0x66af0c0..0x66af263. It may be written via `0x5679DB0` at a different RVA (the dossier mentions `0x5679db0 (Viewport uniform)` in the texture-slot section after 0x66af263) or via a different mechanism entirely. This is an OPEN question.

### Struct fields touched
None in this range for Viewport.

### Callees
None for Viewport in this range.

---

## Phase 4: Pass-entry words (0x66af72c..0x66afe7a) [V disassembly]

### Instructions

```
; --- Entry header: resolve pass manager P = frame+0x9D0 ---
0x66af72c  movups [rbp+0x4A8],xmm0                         ; float4 [rbp+0x300] -> entry+0xA8 (temp)
0x66af733  mov rax,[rbp+0x4E0]                              ; frame ctx
0x66af73a  mov rcx,[rax+0x10]                               ; [frame+0x10]
0x66af73e  mov eax,0x9D0                                    ; pass manager offset
0x66af743  add rcx,rax                                      ; rcx = frame + 0x9D0 = P
0x66af746  call 0x5ABA5C0                                   ; passLookup(P) -> rax
0x66af74c  mov r13,rax                                      ; r13 = P (pass manager object)

; --- Zero-init entry body at rbp+0x210 (skip rbp+0x208 head) ---
0x66af74f  lea rax,[rbp+0x210]                              ; entry buffer base (+0x10 from head)
0x66af756  movups [rax+0xB0],xmm8                           ; zero rbp+0x2C0
0x66af75e  movups [rax+0xA0],xmm8                           ; zero rbp+0x2B0
0x66af766  movups [rax+0x90],xmm8                           ; zero rbp+0x2A0
0x66af76e  movups [rax+0x80],xmm8                           ; zero rbp+0x290
0x66af776  movups [rax+0x70],xmm8                           ; zero rbp+0x280
0x66af77b  movups [rax+0x60],xmm8                           ; zero rbp+0x270
0x66af780  movups [rax+0x50],xmm8                           ; zero rbp+0x260
0x66af785  movups [rax+0x40],xmm8                           ; zero rbp+0x250
0x66af78a  movups [rax+0x30],xmm8                           ; zero rbp+0x240
0x66af794  movups [rax+0x20],xmm8                           ; zero rbp+0x230
0x66af799  movups [rax+0x10],xmm8                           ; zero rbp+0x220
                                     ; (rbp+0x210..rbp+0x2CF zeroed; rbp+0x208 head left for later)

; --- Push variantA to P+0x720 vector (stride 0x40) ---
0x66af79d  lea rcx,[r13+0x720]                              ; P+0x720 vector head
0x66af7a4  lea rdx,[rbp+0x478]                              ; src: variantA copy {ptr, ctrl} at rbp+0x478/0x480
0x66af7ab  call 0x67D7410                                   ; push 16 bytes to P+0x720
0x66af7b1  mov qword ptr [rbp+0x208],0x10000                ; entry head = 0x10000
0x66af7bc  mov eax,[r13+0x728]                              ; P+0x728 (end)
0x66af7c3  sub eax,[r13+0x720]                              ; P+0x720 (begin)
0x66af7ca  shr eax,6                                        ; >> 6 (divide by 0x40)
0x66af7cd  dec eax                                          ; -1
0x66af7cf  mov [rbp+0x238],ax                               ; entry+0x30 = P+0x720 index

; --- Mutex lock (vtable[+0x10] slot 2, dl=0x4A) ---
0x66af7d6  mov rcx,[0x1233E1B0]                             ; global mutex obj (data_1233e1b0)
0x66af7dd  mov rax,[rcx]
0x66af7e0  mov rax,[rax+0x10]                               ; vtable[+0x10]
0x66af7e4  mov dl,0x4A                                      ; mutex id
0x66af7e6  call qword ptr [0xF99FFA0]                       ; sub_eea6040
0x66af7ed  mov [rbp+0x537],al                               ; save mutex id byte

; --- Push per-draw state to P+0x750 vector (stride 0x58) ---
0x66af7f3  mov rdx,[r13+0x758]                              ; P+0x758 (end)
0x66af7fa  cmp rdx,[r13+0x760]                              ; P+0x760 (cap)
0x66af801  je 0x66AF890                                     ; full -> grow path (0x6760a80)
; inline push:
0x66af807  lea rcx,[rbp+0x420]                              ; src state block
0x66af80e  mov eax,[rcx+0x10]
0x66af811  mov [rdx+0x10],eax                               ; W P+0x758+0x10 = dword (blend enum)
0x66af814  movups xmm0,[rcx]
0x66af817  movups [rdx],xmm0                                ; W P+0x758+0x0 = 16 bytes (blend enum + 3 bytes + pad)
0x66af81a  movzx eax,byte ptr [rbp+0x434]
0x66af821  mov [rdx+0x14],al                                ; W P+0x758+0x14 = byte
0x66af824  movss xmm0,[rbp+0x438]
0x66af82c  movss [rdx+0x18],xmm0                            ; W P+0x758+0x18 = float
0x66af831  movss xmm0,[rbp+0x43C]
0x66af839  movss [rdx+0x1C],xmm0                            ; W P+0x758+0x1C = float
0x66af83e  movss xmm0,[rbp+0x440]
0x66af846  movss [rdx+0x20],xmm0                            ; W P+0x758+0x20 = float
0x66af84b  movss xmm0,[rbp+0x444]
0x66af853  movss [rdx+0x24],xmm0                            ; W P+0x758+0x24 = float
0x66af858  lea rax,[rbp+0x320]
0x66af85f  movups xmm0,[rax+0x128]                          ; load [rbp+0x448]..[rbp+0x457]
0x66af866  movups xmm1,[rax+0x138]                          ; load [rbp+0x458]..[rbp+0x467]
0x66af86d  movups xmm2,[rax+0x147]                          ; load [rbp+0x467]..[rbp+0x476] (16 bytes incl sub-windows)
0x66af874  movups [rdx+0x28],xmm0                           ; W P+0x758+0x28
0x66af878  movups [rdx+0x38],xmm1                           ; W P+0x758+0x38
0x66af87c  movups [rdx+0x47],xmm2                           ; W P+0x758+0x47 (7 bytes of 16)
0x66af880  add qword ptr [r13+0x758],0x58                   ; advance P+0x758 by stride 0x58
0x66af888  jmp short 0x66AF8A4
; grow path:
loc_66af890:
0x66af890  lea rcx,[r13+0x750]                              ; P+0x750 vector
0x66af897  lea r8,[rbp+0x420]                               ; src state block
0x66af89e  call 0x6760A80                                   ; grow P+0x750

loc_66af8a4:
; --- Mutex unlock ---
0x66af8a4  mov rcx,[0x1233E1B0]
0x66af8ab  mov rax,[rcx]
0x66af8ae  mov rax,[rax+0x10]
0x66af8b2  movzx edx,byte ptr [rbp+0x537]                   ; mutex id
0x66af8b9  call qword ptr [0xF99FFA0]                       ; sub_eea6040
; --- Index word for P+0x750 ---
0x66af8c0  mov eax,[r13+0x758]                              ; end after push
0x66af8c7  sub eax,[r13+0x750]                              ; begin
0x66af8ce  shr eax,3                                        ; >> 3 (divide by 8)
0x66af8d1  imul eax,0xFFFF8BA3                              ; magic: /0x28 (40)
0x66af8d7  dec eax                                          ; -1
0x66af8d9  mov [rbp+0x234],ax                               ; entry+0x2C = P+0x750 index

; --- Push scope to P+0x780 vector (stride 0x28) ---
0x66af8e0  lea rcx,[r13+0x780]                              ; P+0x780 vector
0x66af8e7  lea rdx,[rbp+0x3C8]                              ; src: draw record scope at rbp+0x3C8
0x66af8ee  call 0x675F3B0                                   ; push/clone scope
0x66af8f4  mov eax,[r13+0x788]                              ; P+0x788 (end)
0x66af8fb  sub eax,[r13+0x780]                              ; P+0x780 (begin)
0x66af902  shr eax,3                                        ; >> 3
0x66af905  imul eax,0xFFFF8BA3                              ; magic: /0x28
0x66af90b  dec eax                                          ; -1
0x66af90d  mov [rbp+0x230],ax                               ; entry+0x28 = P+0x780 index

; --- Mutex lock ---
0x66af914  mov rcx,[0x1233E1B0]
0x66af91b  mov rax,[rcx]
0x66af91e  mov rax,[rax+0x10]
0x66af922  mov dl,0x4A
0x66af924  call qword ptr [0xF99FFA0]
0x66af92b  mov [rbp+0x537],al

; --- Push scope clone to P+0x768 vector (stride 0x88) ---
0x66af931  mov rbx,[r13+0x770]                              ; P+0x770 (end)
0x66af938  cmp rbx,[r13+0x778]                              ; P+0x778 (cap)
0x66af93f  je short 0x66AF990                               ; full -> grow (0x6760710)
; inline push:
0x66af941  mov rax,[rbp+0x340]                              ; scope qword
0x66af948  mov [rbx],rax                                    ; W P+0x770+0x0 = scope qword
0x66af94b  lea rcx,[rbx+8]                                  ; dst = P+0x770+8
0x66af94f  lea rdx,[rbp+0x348]                              ; src = scope data rbp+0x348
0x66af956  call 0xE869FF0                                   ; clone scope
0x66af95c  mov rax,[rbp+0x3C0]                              ; scope owner
0x66af963  mov [rbx+0x80],rax                               ; W P+0x770+0x80 = scope owner
0x66af96a  mov qword ptr [rbp+0x3C0],0                      ; null scope owner
0x66af975  add qword ptr [r13+0x770],0x88                   ; advance P+0x770 by stride 0x88
0x66af980  jmp short 0x66AF9A7
loc_66af990:
0x66af990  lea rcx,[r13+0x768]                              ; P+0x768 vector
0x66af997  mov rdx,rbx
0x66af99a  lea r8,[rbp+0x340]
0x66af9a1  call 0x6760710                                   ; grow P+0x768
loc_66af9a7:
; --- Mutex unlock ---
0x66af9a7  mov rcx,[0x1233E1B0]
0x66af9ae  mov rax,[rcx]
0x66af9b1  mov rax,[rax+0x10]
0x66af9b5  movzx edx,byte ptr [rbp+0x537]
0x66af9bc  call qword ptr [0xF99FFA0]
0x66af9c3  mov qword ptr [rbp+0x208],0x17000                ; entry head = 0x17000
; --- Index word for P+0x768 ---
0x66af9ce  mov eax,[r13+0x770]                              ; end after push
0x66af9d5  sub eax,[r13+0x768]                              ; P+0x768 (begin)
0x66af9dc  shr eax,3                                        ; >> 3
0x66af9df  imul eax,0xFFFFF0F1                              ; magic: /0x88
0x66af9e5  dec eax                                          ; -1
0x66af9e7  mov [rbp+0x232],ax                               ; entry+0x2A = P+0x768 index

; --- Mutex lock ---
0x66af9ee  mov rcx,[0x1233E1B0]
0x66af9f5  mov rax,[rcx]
0x66af9f8  mov rax,[rax+0x10]
0x66af9fc  mov dl,0x4A
0x66af9fe  call qword ptr [0xF99FFA0]
0x66afa04  nop
0x66afa05  mov [rbp+0x537],al

; --- Push u16 to P+0x690 vector (stride 2) ---
0x66afa0b  mov rdx,[r13+0x698]                              ; P+0x698 (end)
0x66afa12  cmp rdx,[r13+0x6A0]                              ; P+0x6A0 (cap)
0x66afa19  je short 0x66AFA30                               ; full -> grow (0x1ef6f90)
; inline push:
0x66afa1b  movzx eax,word ptr [rbp+0x338]                   ; u16 data
0x66afa22  mov [rdx],ax                                     ; W P+0x698 = u16
0x66afa25  add qword ptr [r13+0x698],2                      ; advance by 2
0x66afa2d  jmp short 0x66AFA47
loc_66afa30:
0x66afa30  mov rcx,r13
0x66afa33  add rcx,0x690                                    ; P+0x690 vector
0x66afa3a  lea r8,[rbp+0x338]                               ; src u16
0x66afa41  call 0x1EF6F90                                   ; grow P+0x690
loc_66afa47:
; --- Mutex unlock ---
0x66afa47  mov rcx,[0x1233E1B0]
0x66afa4e  mov rax,[rcx]
0x66afa51  mov rax,[rax+0x10]
0x66afa55  movzx edx,byte ptr [rbp+0x537]
0x66afa5c  call qword ptr [0xF99FFA0]
0x66afa63  mov eax,[r13+0x698]                              ; end after push
0x66afa6a  sub eax,[r13+0x690]                              ; P+0x690 (begin)
0x66afa71  shr eax,1                                        ; >> 1 (divide by 2)
0x66afa73  dec eax                                          ; -1
0x66afa75  mov [rbp+0x244],ax                               ; entry+0x3C = P+0x690 index

; --- Mutex lock ---
0x66afa7c  mov rcx,[0x1233E1B0]
0x66afa83  mov rax,[rcx]
0x66afa86  mov rax,[rax+0x10]
0x66afa8a  mov dl,0x4A
0x66afa8c  call qword ptr [0xF99FFA0]
0x66afa92  nop
0x66afa93  mov edx,eax

; --- Push mat4 buffer to P+0x4B0 vector (stride 0x18) ---
0x66afa95  mov rsi,[r13+0x4B8]                              ; P+0x4B8 (end)
0x66afa9c  cmp rsi,[r13+0x4C0]                              ; P+0x4C0 (cap)
0x66afaa3  je short 0x66AFAE0                               ; full -> realloc path
; inline push:
0x66afaa5  mov rax,[rbp+0x330]                              ; mat4 buffer ptr (qword)
0x66afac6  movaps xmm0,[rbp+0x320]                          ; mat4 buffer begin (r12)
0x66afabe  movaps [rbp+0x320],xmm8                          ; null begin
0x66afac6  movups [rsi],xmm0                                ; W P+0x4B8+0x0 = mat4 begin
0x66afac9  mov [rsi+0x10],rax                               ; W P+0x4B8+0x10 = mat4 end
0x66afacd  add qword ptr [r13+0x4B8],0x18                   ; advance P+0x4B8 by stride 0x18
0x66afad5  jmp 0x66AFDD5
; realloc path:
loc_66afae0:
0x66afae0  mov [rbp+0x537],dl
0x66afae6  mov r14,rsi
0x66afae9  sub r14,[r13+0x4B0]                              ; current count bytes
0x66afaf0  mov rax,r14
0x66afaf3  sar rax,3                                        ; /8
0x66afaf7  mov rcx,0xAAAAAAAAAAAAAAAB                       ; magic for /3 (with adjustments)
; ... complex realloc: grow buffer, copy old entries (stride 0x18), free old ...
0x66afc30  mov rcx,[r12+0x10]                               ; copy loop: move {qword, qword} pairs
0x66afc35  mov qword ptr [r12+0x10],0
0x66afc3e  movups xmm0,[r12]
0x66afc43  movups [r12],xmm8
0x66afc48  movups [rax],xmm0
0x66afc4b  mov [rax+0x10],rcx
0x66afc4f  add rax,0x18
0x66afc53  add r12,0x18
0x66afc57  cmp r12,rsi
0x66afc5a  jne short 0x66AFC30
; ... realloc completes, sets [r13+0x4B0], [r13+0x4B8], [r13+0x4C0] ...
loc_66afdd5:
; --- Mutex unlock ---
0x66afdd5  mov rcx,[0x1233E1B0]
0x66afddc  mov rax,[rcx]
0x66afddf  mov rax,[rax+0x10]
0x66afde3  call qword ptr [0xF99FFA0]
; --- Final head ---
0x66afdea  mov rax,0x40000417000                            ; final head value
0x66afdf4  mov [rbp+0x208],rax                              ; entry+0x00 = head = 0x40000417000
; --- Index word for P+0x4B0 ---
0x66afdfb  mov eax,[r13+0x4B8]                              ; end after push
0x66afe02  sub eax,[r13+0x4B0]                              ; P+0x4B0 (begin)
0x66afe09  shr eax,3                                        ; >> 3
0x66afe0c  imul eax,0xFFFFAAAB                              ; magic: /0x30 (48)
0x66afe12  dec eax                                          ; -1
0x66afe14  mov [rbp+0x26C],ax                               ; entry+0x64 = P+0x4B0 index

; --- Mutex lock ---
0x66afe1b  mov rcx,[0x1233E1B0]
0x66afe22  mov rax,[rcx]
0x66afe25  mov rax,[rax+0x10]
0x66afe29  mov dl,0x4A
0x66afe2b  call qword ptr [0xF99FFA0]
0x66afe32  nop
0x66afe32  mov [rbp+0x537],al

; --- Push full entry (0xC8 bytes) to P+8 entry array ---
0x66afe38  mov rdx,[r13+8]                                  ; P+8 (end of entry array)
0x66afe3c  cmp rdx,[r13+0x10]                               ; P+0x10 (cap)
0x66afe40  je short 0x66AFE70                               ; full -> grow (0x5aba6d0)
; inline memcpy:
0x66afe42  mov r8d,0xC8                                     ; entry size = 0xC8
0x66afe48  mov rcx,rdx                                      ; dst = P+8 current end
0x66afe4b  lea rdx,[rbp+0x208]                              ; src = entry at rbp+0x208
0x66afe52  call 0xEEC6EC0                                   ; memcpy 0xC8 bytes
0x66afe57  add qword ptr [r13+8],0xC8                       ; advance P+8 by 0xC8
0x66afe5f  jmp short 0x66AFE80
loc_66afe70:
0x66afe70  mov rcx,r13
0x66afe73  lea r8,[rbp+0x208]                               ; src entry
0x66afe7a  call 0x5ABA6D0                                   ; grow entry array
```

### C-like statement

```c
Pass* P = passLookup(frame + 0x9D0);                       // 0x5ABA5C0
Entry entry;                                                // at rbp+0x208, 0xC8 bytes
memset(&entry + 0x10, 0, 0xC0);                            // zero body, leave head

// Push variantA {ptr, ctrl} to P+0x720 (stride 0x40)
push_vec(P+0x720, &entry.variantA, 16);                    // 0x67D7410
entry.head = 0x10000;
entry.idx_720 = (P+0x728 - P+0x720) / 0x40 - 1;            // shr 6, dec

mutex_lock(0x4A);                                           // vtable[+0x10] on global

// Push per-draw state to P+0x750 (stride 0x58)
if (full) grow_vec(P+0x750, &state, 0x58);                 // 0x6760a80
else memcpy(P+0x758, &state, 0x58); P+0x758 += 0x58;
mutex_unlock(0x4A);
entry.idx_750 = (P+0x758 - P+0x750) / 0x28 - 1;            // shr 3, imul 0xFFFF8BA3, dec

// Push scope to P+0x780 (stride 0x28)
entry.idx_780 = (P+0x788 - P+0x780) / 0x28 - 1;            // shr 3, imul 0xFFFF8BA3, dec
// (push via 0x675F3B0 before index calc)

// mutex_lock(0x4A)
// Push scope clone to P+0x768 (stride 0x88)
if (full) grow_vec(P+0x768, scope, 0x88);                  // 0x6760710
else { P+0x770[0] = scope_qword; clone_scope(P+0x770+8, rbp+0x348); P+0x770[0x80] = owner; }
P+0x770 += 0x88;
mutex_unlock(0x4A);
entry.head = 0x17000;
entry.idx_768 = (P+0x770 - P+0x768) / 0x88 - 1;            // shr 3, imul 0xFFFFF0F1, dec

// mutex_lock(0x4A)
// Push u16 to P+0x690 (stride 2)
if (full) grow_u16(P+0x690, val);                          // 0x1ef6f90
else { *(u16*)P+0x698 = val; P+0x698 += 2; }
mutex_unlock(0x4A);
entry.idx_690 = (P+0x698 - P+0x690) / 2 - 1;               // shr 1, dec

// mutex_lock(0x4A)
// Push mat4 buffer {begin, end} to P+0x4B0 (stride 0x18)
if (full) realloc_mat4(P+0x4B0);                           // 0xe935700, 0x9bc830
else { P+0x4B8[0] = mat4_begin; P+0x4B8[0x10] = mat4_end; P+0x4B8 += 0x18; }
mutex_unlock(0x4A);
entry.head = 0x40000417000;
entry.idx_4B0 = (P+0x4B8 - P+0x4B0) / 0x30 - 1;            // shr 3, imul 0xFFFFAAAB, dec

// mutex_lock(0x4A)
// Push full entry to P+8 (stride 0xC8)
if (full) grow_entries(P, &entry);                         // 0x5aba6d0
else { memcpy(P+8, &entry, 0xC8); P+8 += 0xC8; }
mutex_unlock(0x4A);
```

### Entry layout at rbp+0x208 (0xC8 bytes) [V]

| Entry offset | RVA set | Size | Meaning | Tag |
|-------------|---------|------|---------|-----|
| +0x00 | 0x66afb1/0x66af9c3/0x66afdf4 | 8 | head: 0x10000 → 0x17000 → 0x40000417000 | [V] |
| +0x28 | 0x66af90d | 2 | P+0x780 index (scope vector) | [V] |
| +0x2A | 0x66af9e7 | 2 | P+0x768 index (scope clone vector) | [V] |
| +0x2C | 0x66af8d9 | 2 | P+0x750 index (per-draw state vector) | [V] |
| +0x30 | 0x66af7cf | 2 | P+0x720 index (variantA vector, stride 0x40) | [V] |
| +0x3C | 0x66afa75 | 2 | P+0x690 index (u16 vector) | [V] |
| +0x64 | 0x66afe14 | 2 | P+0x4B0 index (mat4 buffer vector, stride 0x18) | [V] |

Note: All other entry bytes are zero-initialized or written by surrounding code (variant data at +0x478..+0x4FF, per-draw state at +0x420..+0x47F, etc.). Index words are computed as `(end - begin) / stride - 1` using magic-number division, giving the index of the last-pushed item (0-based, minus 1).

### Struct fields touched
| Offset | Size | Direction | Meaning | Tag |
|--------|------|-----------|---------|-----|
| frame+0x9D0 | 8 | R | pass manager P (via [frame+0x10] + 0x9D0) | [V] |
| P+0x720 | 8 | R/W | variantA vector begin | [V] |
| P+0x728 | 8 | R/W | variantA vector end | [V] |
| P+0x750 | 8 | R | per-draw state vector begin | [V] |
| P+0x758 | 8 | R/W | per-draw state vector end | [V] |
| P+0x760 | 8 | R | per-draw state vector cap | [V] |
| P+0x768 | 8 | R | scope clone vector begin | [V] |
| P+0x770 | 8 | R/W | scope clone vector end | [V] |
| P+0x778 | 8 | R | scope clone vector cap | [V] |
| P+0x780 | 8 | R | scope vector begin | [V] |
| P+0x788 | 8 | R/W | scope vector end | [V] |
| P+0x690 | 8 | R | u16 vector begin | [V] |
| P+0x698 | 8 | R/W | u16 vector end | [V] |
| P+0x6A0 | 8 | R | u16 vector cap | [V] |
| P+0x4B0 | 8 | R | mat4 buffer vector begin | [V] |
| P+0x4B8 | 8 | R/W | mat4 buffer vector end | [V] |
| P+0x4C0 | 8 | R | mat4 buffer vector cap | [V] |
| P+8 | 8 | R/W | entry array end | [V] |
| P+0x10 | 8 | R | entry array cap | [V] |
| rbp+0x208 | 8 | W | entry head | [V] |
| rbp+0x210..0x2CF | 16x | W | entry body zero-init | [V] |
| rbp+0x230 | 2 | W | entry+0x28 = P+0x780 index | [V] |
| rbp+0x232 | 2 | W | entry+0x2A = P+0x768 index | [V] |
| rbp+0x234 | 2 | W | entry+0x2C = P+0x750 index | [V] |
| rbp+0x238 | 2 | W | entry+0x30 = P+0x720 index | [V] |
| rbp+0x244 | 2 | W | entry+0x3C = P+0x690 index | [V] |
| rbp+0x26C | 2 | W | entry+0x64 = P+0x4B0 index | [V] |
| rbp+0x320 | 8 | R/W | mat4 begin (r12) | [V] |
| rbp+0x330 | 8 | R | mat4 end | [V] |
| rbp+0x338 | 2 | R | u16 data | [V] |
| rbp+0x340 | 8 | R | scope qword | [V] |
| rbp+0x348 | 16 | R | scope data | [V] |
| rbp+0x3C0 | 8 | R/W | scope owner | [V] |
| rbp+0x3C8 | 16 | R | draw record scope | [V] |
| rbp+0x420 | 16 | R | per-draw state block | [V] |
| rbp+0x478 | 16 | R | variantA copy {ptr, ctrl} | [V] |
| rbp+0x537 | 1 | W | mutex id byte | [V] |

### Callees
- 0x5ABA5C0: passLookup(frame+0x9D0) -> P [V]
- 0x67D7410: push variantA to P+0x720 [V]
- 0x6760A80: grow P+0x750 vector [V]
- 0x675F3B0: push scope to P+0x780 [V]
- 0x6760710: grow P+0x768 vector [V]
- 0x1EF6F90: grow P+0x690 u16 vector [V]
- 0xE935700: free mat4 buffer (realloc path) [V]
- 0x9BC830: alloc-fail / realloc helper [V]
- 0xEEC6EC0: memcpy 0xC8 bytes (entry push) [V]
- 0x5ABA6D0: grow entry array (P+8) [V]
- [0xF99FFA0] = sub_eea6040: vtable[+0x10] mutex lock/unlock (dl=0x4A) [V]

---

## Struct fields touched (summary across all phases)

| Offset | Size | Direction | Meaning | Phase | Tag |
|--------|------|-----------|---------|-------|-----|
| rec+0x50 | 8 | R | Data_VS pointer | 1 | [V] |
| rec+0x58 | 8 | R | Data_VS size | 1 | [V] |
| rec+0x60 | 8 | R | Data_PS pointer | 2 | [V] |
| rec+0x68 | 8 | R | Data_PS size | 2 | [V] |
| [rbp+0x90] | 8 | R | uniform slot table base | 1,2 | [V] |
| [rbp+0x9A] | 2 | R | index word | 1,2 | [V] |
| rbp+0x208 | 8 | W | entry head / slot index | 1,2,4 | [V] |
| rbp+0x20A | 1 | W | flag = 1 | 1,2 | [V] |
| rbp+0x320 | 8 | W | {size=0x80, then mat4 begin} | 1,2,4 | [V] |
| rbp+0x328 | 8 | W | {ptr=rec+0x50/0x60, then mat4 end} | 1,2 | [V] |

---

## Callees (summary)

| RVA | What it is | Call count | Tag |
|-----|-----------|------------|-----|
| 0x5679DB0 | uniform slot write (Data_VS/Data_PS/Viewport) | 2 in this range | [V] |
| 0x5ABA5C0 | passLookup(frame+0x9D0) | 1 | [V] |
| 0x67D7410 | push variantA to P+0x720 | 1 | [V] |
| 0x6760A80 | grow P+0x750 vector | 1 (grow path) | [V] |
| 0x675F3B0 | push scope to P+0x780 | 1 | [V] |
| 0x6760710 | grow P+0x768 vector | 1 (grow path) | [V] |
| 0x1EF6F90 | grow P+0x690 u16 vector | 1 (grow path) | [V] |
| 0xEEC6EC0 | memcpy 0xC8 bytes (entry push) | 1 | [V] |
| 0x5ABA6D0 | grow entry array P+8 | 1 (grow path) | [V] |
| [0xF99FFA0] = sub_eea6040 | vtable[+0x10] mutex lock/unlock (dl=0x4A) | ~8 | [V] |
| 0xE935700 | free buffer (realloc path) | 1 (realloc path) | [V] |
| 0x9BC830 | alloc-fail / realloc helper | 1 (realloc path) | [V] |

---

## OPEN questions

1. **Viewport write location**: No Viewport write exists in 0x66af0c0..0x66af263. Only Data_VS (rec+0x50/0x58) and Data_PS (rec+0x60/0x68) are written via 0x5679DB0. Viewport may be written via 0x5679DB0 at a different RVA (dossier mentions it in the texture-slot section after 0x66af263) or via rec+0x70 elsewhere. [V: confirmed absent from range]

2. **0x5679DB0 semantics**: The function takes (rcx=uniform_ctx at rbp+0x60, rdx={index,flag}, r8={size,ptr}). It is unclear whether the index word selects Data_VS vs Data_PS vs Viewport within the ctx object, or whether separate ctx objects are used. The same rbp+0x60 is used for both Data_VS and Data_PS calls. [I: need 0x5679DB0 disassembly]

3. **r15 base**: r15 is the element record pointer (stride 0x1a0, iterated in the element loop at 0x66aecc2). [V: from dossier]

4. **[rbp+0x60] object**: The uniform context object passed to 0x5679DB0. Its type and layout are unknown. [I]

5. **[rbp+0x90] table**: Set before 0x66af0c0 (outside this range). Contains slot entries of stride 0x10 with slot id at +0x28. [V: used but not set in this range]