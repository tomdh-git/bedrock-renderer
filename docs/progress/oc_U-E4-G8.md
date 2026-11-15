# U-E4-G8 — Unit 8 of builder 0x670b6e0 (function ends 0x6713c64)

## NEXT block at TOP — resume at 0x6713c64 (function end reached)

Unit range covered: 0x6711bfe .. 0x6713c64 (phases 1-44)

Unit range covered: none yet
Resume address: none — function sub_670b6e0 is fully disassembled (0x670b6e0..0x6713c64). Last instruction 0x6713c5f `jmp 0x670B7AD` ends exactly at 0x6713c64; no further instructions remain. 0x6711bf0..0x6711bfe is data/padding — `mov bh,0x70`, `(bad)`, `add [rcx+0x3B],cl`, `mov bh,0x78`, `(bad)`, `add [rcx+rax*2+0x48],dh` — so code resumes at 0x6711bfe `mov rax,[rbp+0x128]`; U-E4-G7 phase 5 ended at 0x6711bfc `je short 0x6711C3F`).
Function end (given): 0x6713c64.

Method: linear `rdis dis` listing, 40-instruction steps per phase.
Tags: [V] = saw in disasm (cite RVA), [I] = inferred, [?] = unknown.
Direct jumps written as `jmp <addr>` (not `jmp qword ptr`).

---

### Phase 1 — instructions #1-#40 (0x6711bfe .. 0x6711cc5)

  6711bfe  mov rax,[rbp+0x128]                           ; [V] load saved value
  6711c05  mov [rsi],rax                                 ; W *(r15+0x768)+0x0  (store into new slot)
  6711c08  lea rcx,[rsi+8]                              ; [V]
  6711c0c  lea rdx,[rbp+0x130]                          ; [V]
  6711c13  call 0xE869FF0                                ; -> sub_e869ff0   [V]
  6711c18  nop
  6711c19  mov rax,[rbp+0x1A8]                          ; [V]
  6711c20  mov [rsi+0x80],rax                           ; W a1+0x80
  6711c27  mov qword ptr [rbp+0x1A8],0                  ; W clear saved value
  6711c32  add qword ptr [r15+0x770],0x88               ; W end_ptr += 0x88 (slot size)
  6711c3d  jmp short 0x6711C56                           ; -> loc_6711c56
  6711c3f  lea rcx,[r15+0x768]                          ; [V] else-branch: grow
  6711c46  mov rdx,rsi                                  ; [V]
  6711c49  lea r8,[rbp+0x128]                           ; [V]
  6711c50  call 0x6760710                                ; -> sub_6760710  [V] push_back into vector
  6711c55  nop

loc_6711c56:  ; from 6711c3d
  6711c56  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711c5d  mov rax,[rcx]
  6711c60  mov rax,[rax+0x10]
  6711c64  movzx edx,byte ptr [rbp+0x848]
  6711c6b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711c71  nop
  6711c72  mov eax,[r15+0x770]
  6711c79  sub eax,[r15+0x768]
  6711c80  shr eax,3
  6711c83  imul eax,0xFFFFF0F1
  6711c89  dec eax
  6711c8b  mov [rbp+0x5AA],ax
  6711c92  mov rcx,[0x1233E1B0]
  6711c99  mov rax,[rcx]
  6711c9c  mov rax,[rax+0x10]
  6711ca0  mov dl,0x4A
  6711ca2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711ca8  nop
  6711ca9  mov [rbp+0x848],al
  6711caf  mov rdx,[r15+0x2D8]
  6711cb6  cmp rdx,[r15+0x2E0]
  6711cbd  je short 0x6711CCB                            ; -> loc_6711ccb
  6711cbf  inc rdx
  6711cc2  mov [r15+0x2D8],rdx

Phase 1 summary: push a 0x88-byte slot into vector at r15+0x768/0x770 (either via in-place store when space remains, or via sub_6760710 push_back when full); then log count (size>>3 * 0xF0F1 - 1) into [rbp+0x5AA]; then advance vector at r15+0x2D0/0x2D8 by one element.

---

### Phase 2 — instructions #41-#80 (0x6711ccb .. 0x6711d7e)

  6711ccb  lea rcx,[r15+0x2D0]                          ; [V]
  6711cd2  call 0x6760E60                                ; -> sub_6760e60  [V] grow vector at r15+0x2D0
  6711cd7  nop

loc_6711cd8:  ; from 6711cc9
  6711cd8  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711cdf  mov rax,[rcx]
  6711ce2  mov rax,[rax+0x10]
  6711ce6  movzx edx,byte ptr [rbp+0x848]
  6711ced  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711cf3  nop
  6711cf4  mov rax,0x400000000A007009                    ; [V] packed tag 0x0A007009
  6711cfe  mov [rbp+0x580],rax                           ; W save tag
  6711d05  mov eax,[r15+0x2D0]
  6711d0c  not eax
  6711d0e  add eax,[r15+0x2D8]
  6711d15  mov [rbp+0x60C],ax                            ; W save count (not base + end)>>3
  6711d1c  mov rcx,[0x1233E1B0]
  6711d23  mov rax,[rcx]
  6711d26  mov rax,[rax+0x10]
  6711d2a  mov dl,0x4A
  6711d2c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711d32  nop
  6711d33  mov [rbp+0x848],al
  6711d39  mov rdx,[r15+0x6C8]
  6711d40  cmp rdx,[r15+0x6D0]
  6711d47  je short 0x6711D55                            ; -> loc_6711d55
  6711d49  inc rdx
  6711d4c  mov [r15+0x6C8],rdx                            ; W end_ptr += 1
  6711d53  jmp short 0x6711D62                           ; -> loc_6711d62

loc_6711d55:  ; from 6711d47
  6711d55  lea rcx,[r15+0x6C0]                          ; [V] else: grow
  6711d5c  call 0x6760E60                                ; -> sub_6760e60  [V]
  6711d61  nop

loc_6711d62:  ; from 6711d53
  6711d62  mov rcx,[0x1233E1B0]
  6711d69  mov rax,[rcx]
  6711d6c  mov rax,[rax+0x10]
  6711d70  movzx edx,byte ptr [rbp+0x848]
  6711d77  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711d7d  nop
  6711d7e  mov eax,[r15+0x6C0]

Phase 2 summary: grow vector r15+0x2D0 via sub_6760e60; save packed tag 0x0A007009 to [rbp+0x580] and element count to [rbp+0x60C]; advance vector at r15+0x6C0/0x6C8 by one element (grow via sub_6760e60 if full).

---

### Phase 3 — instructions #81-#120 (0x6711d7e .. 0x6711e39)

  6711d7e  mov eax,[r15+0x6C0]                           ; [V]
  6711d85  not eax
  6711d87  add eax,[r15+0x6C8]
  6711d8e  mov [rbp+0x5B8],ax                            ; W save count for vector r15+0x6C0
  6711d95  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711d9c  mov rax,[rcx]
  6711d9f  mov rax,[rax+0x10]
  6711da3  mov dl,0x4A
  6711da5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711dab  nop
  6711dac  mov [rbp+0x848],al
  6711db2  mov rdx,[r15+0x6B0]
  6711db9  cmp rdx,[r15+0x6B8]
  6711dc0  je short 0x6711DCE                            ; -> loc_6711dce
  6711dc2  inc rdx
  6711dc5  mov [r15+0x6B0],rdx                            ; W end_ptr += 1
  6711dcc  jmp short 0x6711DDE                           ; -> loc_6711dde

loc_6711dce:  ; from 6711dc0
  6711dce  mov rcx,r15
  6711dd1  add rcx,0x6A8                                 ; [V]
  6711dd8  call 0x6760E60                                ; -> sub_6760e60  [V] grow vector at r15+0x6A8
  6711ddd  nop

loc_6711dde:  ; from 6711dcc
  6711dde  mov rcx,[0x1233E1B0]
  6711de5  mov rax,[rcx]
  6711de8  mov rax,[rax+0x10]
  6711dec  movzx edx,byte ptr [rbp+0x848]
  6711df3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711df9  nop
  6711dfa  mov rax,0x400000000A307009                    ; [V] packed tag 0x0A307009
  6711e04  mov [rbp+0x580],rax                           ; W save tag
  6711e0b  mov eax,[r15+0x6A8]
  6711e12  not eax
  6711e14  add eax,[r15+0x6B0]
  6711e1b  mov [rbp+0x5BA],ax                            ; W save count for vector r15+0x6A8
  6711e22  mov rcx,[0x1233E1B0]
  6711e29  mov rax,[rcx]
  6711e2c  mov rax,[rax+0x10]
  6711e30  mov dl,0x4A
  6711e32  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711e38  nop
  6711e39  mov [rbp+0x848],al

Phase 3 summary: save count of vector r15+0x6C0 to [rbp+0x5B8]; advance vector r15+0x6A8/0x6B0 by one element (grow via sub_6760e60 if full); save packed tag 0x0A307009 to [rbp+0x580] and count to [rbp+0x5BA].

---

### Phase 4 — instructions #121-#160 (0x6711e39 .. 0x6711ee6)

  6711e39  mov [rbp+0x848],al
  6711e3f  mov rdx,[r15+8]                               ; [V]
  6711e43  cmp rdx,[r15+0x10]
  6711e47  je short 0x6711E64                            ; -> loc_6711e64
  6711e49  mov r8d,0xC8                                 ; [V] size 0xC8
  6711e4f  mov rcx,rdx
  6711e52  mov rdx,r13
  6711e55  call 0xEEC6EC0                                ; -> sub_eec6ec0  [V] emplace 0xC8-byte element
  6711e5a  add qword ptr [r15+8],0xC8                    ; W end_ptr += 0xC8
  6711e62  jmp short 0x6711E70                           ; -> loc_6711e70

loc_6711e64:  ; from 6711e47
  6711e64  mov rcx,r15                                  ; [V]
  6711e67  mov r8,r13
  6711e6a  call 0x5ABA6D0                                ; -> sub_5aba6d0  [V] grow + emplace
  6711e6f  nop

loc_6711e70:  ; from 6711e62
  6711e70  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711e77  mov rax,[rcx]
  6711e7a  mov rax,[rax+0x10]
  6711e7e  movzx edx,byte ptr [rbp+0x848]
  6711e85  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711e8b  nop
  6711e8c  lea rcx,[rbp+0x120]                          ; [V]
  6711e93  call 0x67E1840                                ; -> sub_67e1840  [V]
  6711e98  jmp 0x6713999                                 ; -> loc_6713999  [V] tail jump out

loc_6711e9d:  ; from 6711f98
  6711e9d  lea rcx,[r15+0x8A0]                          ; [V]
  6711ea4  lea r8,[rbp+0x748]                           ; [V]
  6711eab  call 0x1EF6F90                                ; -> sub_1ef6f90  [V]
  6711eb0  nop
  6711eb1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711eb8  mov rax,[rcx]
  6711ebb  mov rax,[rax+0x10]
  6711ebf  movzx edx,byte ptr [rbp+0x857]
  6711ec6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711ecc  nop
  6711ecd  mov eax,[r15+0x8A8]
  6711ed4  sub eax,[r15+0x8A0]
  6711edb  shr eax,1
  6711edd  dec eax
  6711edf  mov [rbp+0x320],ax                            ; W save count for vector r15+0x8A0
  6711ee6  mov rcx,[0x1233E1B0]

Phase 4 summary: push a 0xC8-byte element into vector at r15+8/0x10 (in-place via sub_eec6ec0 or grow via sub_5aba6d0); then sub_67e1840(rbp+0x120) and tail-jump to 0x6713999. The block at 0x6711e9d is a separate fall-through path reached from 0x6711f98; it saves count of vector r15+0x8A0 into [rbp+0x320].

---

### Phase 5 — instructions #161-#200 (0x6711fb1 .. 0x6712086)

  6711fb1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6711fb8  mov rax,[rcx]
  6711fbb  mov rax,[rax+0x10]
  6711fbf  movzx edx,byte ptr [rbp+0x857]
  6711fc6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711fcc  nop
  6711fcd  mov eax,[r15+0x8A8]
  6711fd4  sub eax,[r15+0x8A0]
  6711fdb  shr eax,1
  6711fdd  dec eax
  6711fdf  mov [rbp+0x320],ax                            ; W save count for vector r15+0x8A0
  6711fe6  mov rcx,[0x1233E1B0]
  6711fed  mov rax,[rcx]
  6711ff0  mov rax,[rax+0x10]
  6711ff4  mov dl,0x4A
  6711ff6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6711ffc  nop
  6711ffd  mov [rbp+0x857],al
  6712003  mov rdx,[r15+0x758]                           ; [V]
  671200a  cmp rdx,[r15+0x760]
  6712011  je 0x6712138                                  ; -> loc_6712138
  6712017  lea rcx,[rbp+0x6F8]                          ; [V]
  671201e  mov eax,[rcx+0x10]
  6712021  mov [rdx+0x10],eax                            ; W a1+0x10
  6712024  movups xmm0,[rcx]                            ; [V]
  6712027  movups [rdx],xmm0                            ; W a1+0x0..0x10
  671202a  movzx eax,byte ptr [rbp+0x70C]
  6712031  mov [rdx+0x14],al                            ; W a1+0x14
  6712034  movss xmm0,[rbp+0x710]
  671203c  movss [rdx+0x18],xmm0                        ; W a1+0x18
  6712041  movss xmm0,[rbp+0x714]
  6712049  movss [rdx+0x1C],xmm0                        ; W a1+0x1C
  671204e  movss xmm0,[rbp+0x718]
  6712056  movss [rdx+0x20],xmm0                        ; W a1+0x20
  671205b  movss xmm0,[rbp+0x71C]
  6712063  movss [rdx+0x24],xmm0                        ; W a1+0x24
  6712068  lea rax,[rbp+0x584]                          ; [V]
  671206f  movups xmm0,[rax+0x19C]
  6712076  movups xmm1,[rax+0x1AC]
  671207d  movups xmm2,[rax+0x1BB]
  6712084  movups [rdx+0x28],xmm0                       ; W a1+0x28
  6712088  movups [rdx+0x38],xmm1                       ; W a1+0x38
  671208c  movups [rdx+0x47],xmm2                       ; W a1+0x47
  6712090  add qword ptr [r15+0x758],0x58                ; W end_ptr += 0x58
  6712098  jmp 0x671214C                                 ; -> loc_671214c

Phase 5 summary: log count of vector r15+0x8A0 into [rbp+0x320]; copy a 0x58-byte struct from [rbp+0x6F8] into the next slot of vector r15+0x758/0x760 (in-place when space remains), then end_ptr += 0x58.

---

### Phase 6 — instructions #201-#240 (0x67120b1 .. 0x671214c)

  67120b1  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67120b8  mov rax,[rcx]
  67120bb  mov rax,[rax+0x10]
  67120bf  movzx edx,byte ptr [rbp+0x857]
  67120c6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67120cc  nop
  67120cd  mov qword ptr [rbp+0x310],0x4001              ; W save tag 0x0A004001
  67120d8  mov eax,[r15+0x758]
  67120df  sub eax,[r15+0x750]
  67120e6  shr eax,3
  67120e9  imul eax,0xFFFF8BA3
  67120ef  dec eax
  67120f1  mov [rbp+0x33C],ax                            ; W save count for vector r15+0x750
  67120f8  mov rcx,[0x1233E1B0]
  67120ff  mov rax,[rcx]
  6712102  mov rax,[rax+0x10]
  6712106  mov dl,0x4A
  6712108  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671210e  nop
  671210f  mov [rbp+0x857],al
  6712115  mov rdx,[r15+0x860]                           ; [V]
  671211c  cmp rdx,[r15+0x868]
  6712123  je 0x67121D3                                  ; -> loc_67121d3
  6712129  inc rdx
  671212c  mov [r15+0x860],rdx                            ; W end_ptr += 1
  6712133  jmp 0x67121E0                                 ; -> loc_67121e0

loc_6712138:  ; from 6712011
  6712138  lea rcx,[r15+0x750]                          ; [V] else-branch: grow
  671213f  lea r8,[rbp+0x6F8]                           ; [V]
  6712146  call 0x6760A80                                ; -> sub_6760a80  [V] push_back 0x58-byte struct
  671214b  nop

Phase 6 summary: save tag 0x0A004001 to [rbp+0x310] and count of vector r15+0x750 to [rbp+0x33C]; advance vector r15+0x858/0x860 by one element (in-place or grow via sub_6760e60); the else-branch at 0x6712138 pushes the 0x58-byte struct from [rbp+0x6F8] into vector r15+0x750 via sub_6760a80.

---

### Phase 7 — instructions #241-#280 (0x671214c .. 0x6712213)

  671214c  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6712153  mov rax,[rcx]
  6712156  mov rax,[rax+0x10]
  671215a  movzx edx,byte ptr [rbp+0x857]
  6712161  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712167  nop
  6712168  mov qword ptr [rbp+0x310],0x4001              ; W save tag 0x0A004001
  6712173  mov eax,[r15+0x758]
  671217a  sub eax,[r15+0x750]
  6712181  shr eax,3
  6712184  imul eax,0xFFFF8BA3
  671218a  dec eax
  671218c  mov [rbp+0x33C],ax                            ; W save count for vector r15+0x750
  6712193  mov rcx,[0x1233E1B0]
  671219a  mov rax,[rcx]
  671219d  mov rax,[rax+0x10]
  67121a1  mov dl,0x4A
  67121a3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67121a9  nop
  67121aa  mov [rbp+0x857],al
  67121b0  mov rdx,[r15+0x860]                           ; [V]
  67121b7  cmp rdx,[r15+0x868]
  67121be  je 0x6712253                                  ; -> loc_6712253
  67121c4  inc rdx
  67121c7  mov [r15+0x860],rdx                            ; W end_ptr += 1
  67121ce  jmp 0x6712260                                 ; -> loc_6712260

loc_67121d3:  ; from 6712123
  67121d3  lea rcx,[r15+0x858]                          ; [V] else: grow
  67121da  call 0x6760E60                                ; -> sub_6760e60  [V]
  67121df  nop

loc_67121e0:  ; from 6712133
  67121e0  mov rcx,[0x1233E1B0]
  67121e7  mov rax,[rcx]
  67121ea  mov rax,[rax+0x10]
  67121ee  movzx edx,byte ptr [rbp+0x857]
  67121f5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67121fb  nop
  67121fc  mov eax,[r15+0x858]
  6712203  not eax
  6712205  add eax,[r15+0x860]
  671220c  mov [rbp+0x326],ax                            ; W save count for vector r15+0x858
  6712213  mov rcx,[0x1233E1B0]

Phase 7 summary: save tag 0x0A004001 to [rbp+0x310] and count of vector r15+0x750 to [rbp+0x33C]; advance vector r15+0x858/0x860 by one element (in-place or grow via sub_6760e60); save count of vector r15+0x858 to [rbp+0x326].

---

### Phase 8 — instructions #281-#320 (0x6712230 .. 0x67122e0)

  6712230  mov rdx,[r15+0x620]                           ; [V]
  6712237  cmp rdx,[r15+0x628]
  671223e  je 0x67122D3                                  ; -> loc_67122d3
  6712244  inc rdx
  6712247  mov [r15+0x620],rdx                            ; W end_ptr += 1
  671224e  jmp 0x67122E0                                 ; -> loc_67122e0

loc_67122d3:  ; from 671223e
  67122d3  lea rcx,[r15+0x618]                          ; [V] else: grow
  67122da  call 0x6760E60                                ; -> sub_6760e60  [V]
  67122df  nop

loc_6712260:  ; from 67121ce
  6712260  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6712267  mov rax,[rcx]
  671226a  mov rax,[rax+0x10]
  671226e  movzx edx,byte ptr [rbp+0x857]
  6712275  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671227b  nop
  671227c  mov eax,[r15+0x858]
  6712283  not eax
  6712285  add eax,[r15+0x860]
  671228c  mov [rbp+0x326],ax                            ; W save count for vector r15+0x858
  6712293  mov rcx,[0x1233E1B0]
  671229a  mov rax,[rcx]
  671229d  mov rax,[rax+0x10]
  67122a1  mov dl,0x4A
  67122a3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67122a9  nop
  67122aa  mov [rbp+0x857],al
  67122b0  mov rdx,[r15+0x620]                           ; [V]
  67122b7  cmp rdx,[r15+0x628]
  67122be  je 0x6712432                                  ; -> loc_6712432
  67122c4  inc rdx
  67122c7  mov [r15+0x620],rdx                            ; W end_ptr += 1
  67122ce  jmp 0x671243F                                 ; -> loc_671243f

loc_67122e0:  ; from 671224e
  67122e0  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67122e7  mov rax,[rcx]
  67122ea  mov rax,[rax+0x10]
  67122ee  movzx edx,byte ptr [rbp+0x857]
  67122f5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67122fb  nop
  67122fc  mov qword ptr [rbp+0x310],0x8004009          ; W save tag 0x0A804009
  6712307  mov eax,[r15+0x618]
  671230e  not eax
  6712310  add eax,[r15+0x620]
  6712317  mov [rbp+0x356],ax                            ; W save count for vector r15+0x618
  671231e  mov rcx,[0x1233E1B0]
  6712325  mov rax,[rcx]
  6712328  mov rax,[rax+0x10]
  671232c  mov dl,0x4A
  671232e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712334  mov [rbp+0x857],al
  671233a  lea rcx,[r15+0x648]                           ; [V]
  6712341  lea rdx,[rbp+0x698]                           ; [V]
  6712348  call 0x675FB30                                ; -> sub_675fb30  [V]
  671234d  nop
  671234e  mov rcx,[0x1233E1B0]
  6712355  mov rax,[rcx]
  6712358  mov rax,[rax+0x10]
  671235c  movzx edx,byte ptr [rbp+0x857]
  6712363  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712369  nop
  671236a  mov eax,[r15+0x650]
  6712371  sub eax,[r15+0x648]
  6712378  shr eax,3
  671237b  imul eax,0xFFFF8E39
  6712381  dec eax
  6712383  mov [rbp+0x352],ax                            ; W save count for vector r15+0x648
  671238a  lea rcx,[r15+0x780]                           ; [V]
  6712391  lea rdx,[rbp+0x640]                           ; [V]
  6712398  call 0x675F3B0                                ; -> sub_675f3b0  [V]
  671239d  nop
  671239e  mov eax,[r15+0x788]

Phase 9 summary: save tag 0x0A804009 to [rbp+0x310] and count of vector r15+0x618 to [rbp+0x356]; call sub_675fb30(&r15+0x648, [rbp+0x698]); save count of vector r15+0x648 to [rbp+0x352]; call sub_675f3b0(&r15+0x780, [rbp+0x640]).

---

### Phase 10 — instructions #321-#360 (0x671239e .. 0x6712472)

  671239e  mov eax,[r15+0x788]                           ; [V]
  67123a5  sub eax,[r15+0x780]
  67123ac  shr eax,3
  67123af  imul eax,0xFFFF8BA3
  67123b5  dec eax
  67123b7  mov [rbp+0x338],ax                            ; W save count for vector r15+0x780
  67123be  mov rcx,[0x1233E1B0]
  67123c5  mov rax,[rcx]
  67123c8  mov rax,[rax+0x10]
  67123cc  mov dl,0x4A
  67123ce  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67123d4  mov [rbp+0x857],al
  67123da  mov rsi,[r15+0x770]                           ; [V]
  67123e1  cmp rsi,[r15+0x778]
  67123e8  je 0x6712591                                  ; -> loc_6712591
  67123ee  mov rax,[rbp+0x5B8]                           ; [V]
  67123f5  mov [rsi],rax                                 ; W a1+0x0
  67123f8  lea rcx,[rsi+8]                               ; [V]
  67123fc  lea rdx,[rbp+0x5C0]                           ; [V]
  6712403  call 0xE869FF0                                ; -> sub_e869ff0  [V]
  6712408  nop
  6712409  mov rax,[rbp+0x638]                           ; [V]
  6712410  mov [rsi+0x80],rax                            ; W a1+0x80
  6712417  mov qword ptr [rbp+0x638],0                   ; W clear saved value
  6712422  add qword ptr [r15+0x770],0x88                ; W end_ptr += 0x88
  671242d  jmp 0x67125A8                                 ; -> loc_67125a8

loc_6712432:  ; from 67122be
  6712432  lea rcx,[r15+0x618]                          ; [V] else: grow
  6712439  call 0x6760E60                                ; -> sub_6760e60  [V]
  671243e  nop

loc_671243f:  ; from 67122ce
  671243f  mov rcx,[0x1233E1B0]
  6712446  mov rax,[rcx]
  6712449  mov rax,[rax+0x10]
  671244d  movzx edx,byte ptr [rbp+0x857]
  6712454  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671245a  nop
  671245b  mov eax,[r15+0x618]
  6712462  not eax
  6712464  add eax,[r15+0x620]
  671246b  mov [rbp+0x356],ax                            ; W save count for vector r15+0x618

Phase 10 summary: save count of vector r15+0x780 to [rbp+0x338]; push a 0x88-byte slot into vector r15+0x768/0x770 (in-place store via sub_e869ff0 when space remains, else grow); save count of vector r15+0x618 to [rbp+0x356].

---

### Phase 11 — instructions #361-#400 (0x6712472 .. 0x6712539)

  6712472  mov rcx,[0x1233E1B0]
  6712479  mov rax,[rcx]
  671247c  mov rax,[rax+0x10]
  6712480  mov dl,0x4A
  6712482  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712488  mov [rbp+0x857],al
  671248e  lea rcx,[r15+0x648]                           ; [V]
  6712495  lea rdx,[rbp+0x6A0]                           ; [V]
  671249c  call 0x675FB30                                ; -> sub_675fb30  [V]
  67124a1  nop
  67124a2  mov rcx,[0x1233E1B0]
  67124a9  mov rax,[rcx]
  67124ac  mov rax,[rax+0x10]
  67124b0  movzx edx,byte ptr [rbp+0x857]
  67124b7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67124bd  nop
  67124be  mov eax,[r15+0x650]
  67124c5  sub eax,[r15+0x648]
  67124cc  shr eax,3
  67124cf  imul eax,0xFFFF8E39
  67124d5  dec eax
  67124d7  mov [rbp+0x352],ax                            ; W save count for vector r15+0x648
  67124de  lea rcx,[r15+0x780]                           ; [V]
  67124e5  lea rdx,[rbp+0x648]                           ; [V]
  67124ec  call 0x675F3B0                                ; -> sub_675f3b0  [V]
  67124f1  nop
  67124f2  mov qword ptr [rbp+0x310],0xA005009           ; W save tag 0x0A005009
  67124fd  mov eax,[r15+0x788]
  6712504  sub eax,[r15+0x780]
  671250b  shr eax,3
  671250e  imul eax,0xFFFF8BA3
  6712514  dec eax
  6712516  mov [rbp+0x338],ax                            ; W save count for vector r15+0x780
  671251d  mov rcx,[0x1233E1B0]
  6712524  mov rax,[rcx]
  6712527  mov rax,[rax+0x10]
  671252b  mov dl,0x4A
  671252d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712533  mov [rbp+0x857],al
  6712539  mov rsi,[r15+0x770]

Phase 11 summary: save tag 0x0A005009 to [rbp+0x310]; save count of vector r15+0x780 to [rbp+0x338]; call sub_675fb30(&r15+0x648, [rbp+0x6A0]); save count of vector r15+0x648 to [rbp+0x352]; call sub_675f3b0(&r15+0x780, [rbp+0x648]); save count of vector r15+0x780 again to [rbp+0x338].

---

### Phase 12 — instructions #401-#440 (0x6712539 .. 0x671260c)

  6712539  mov rsi,[r15+0x770]                           ; [V]
  6712540  cmp rsi,[r15+0x778]
  6712547  je 0x671262F                                  ; -> loc_671262f
  671254d  mov rax,[rbp+0x5C0]                           ; [V]
  6712554  mov [rsi],rax                                 ; W a1+0x0
  6712557  lea rcx,[rsi+8]                               ; [V]
  671255b  lea rdx,[rbp+0x5C8]                           ; [V]
  6712562  call 0xE869FF0                                ; -> sub_e869ff0  [V]
  6712567  nop
  6712568  mov rax,[rbp+0x640]                           ; [V]
  671256f  mov [rsi+0x80],rax                            ; W a1+0x80
  6712576  mov qword ptr [rbp+0x640],0                   ; W clear saved value
  6712581  add qword ptr [r15+0x770],0x88                ; W end_ptr += 0x88
  671258c  jmp 0x6712646                                 ; -> loc_6712646

loc_6712591:  ; from 67123e8
  6712591  lea rcx,[r15+0x768]                          ; [V] else-branch: grow
  6712598  mov rdx,rsi                                  ; [V]
  671259b  lea r8,[rbp+0x5B8]                           ; [V]
  67125a2  call 0x6760710                                ; -> sub_6760710  [V] push_back 0x88-byte struct
  67125a7  nop

Phase 12 summary: push a 0x88-byte slot into vector r15+0x768/0x770 (in-place via sub_e869ff0, else grow via sub_6760710).

---

### Phase 13 — instructions #441-#480 (0x671260c .. 0x67126c2)

  671260c  mov rdx,[r15+0x6B0]                           ; [V]
  6712613  cmp rdx,[r15+0x6B8]
  671261a  je 0x67126C2                                  ; -> loc_67126c2
  6712620  inc rdx
  6712623  mov [r15+0x6B0],rdx                            ; W end_ptr += 1
  671262a  jmp 0x67126CF                                 ; -> loc_67126cf

loc_671262f:  ; from 6712547
  671262f  lea rcx,[r15+0x768]                          ; [V] else-branch: grow r15+0x768
  6712636  mov rdx,rsi                                  ; [V]
  6712639  lea r8,[rbp+0x5C0]                           ; [V]
  6712640  call 0x6760710                                ; -> sub_6760710  [V] push_back 0x88-byte struct
  6712645  nop

loc_6712646:  ; from 6712645 (fall-through)
  6712646  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671264d  mov rax,[rcx]
  6712650  mov rax,[rax+0x10]
  6712654  movzx edx,byte ptr [rbp+0x857]
  671265b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712661  nop
  6712662  mov eax,[r15+0x770]
  6712669  sub eax,[r15+0x768]
  6712670  shr eax,3
  6712673  imul eax,0xFFFFF0F1
  6712679  dec eax
  671267b  mov [rbp+0x33A],ax                            ; W save count for vector r15+0x768 (imul 0xFFFFF0F1)
  6712682  mov rcx,[0x1233E1B0]
  6712689  mov rax,[rcx]
  671268c  mov rax,[rax+0x10]
  6712690  mov dl,0x4A
  6712692  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712698  nop
  6712699  mov [rbp+0x857],al
  671269f  mov rdx,[r15+0x2D8]
  67126a6  cmp rdx,[r15+0x2E0]
  67126ad  je 0x6712760                                  ; -> loc_6712760
  67126b3  inc rdx
  67126b6  mov [r15+0x2D8],rdx                            ; W end_ptr += 1
  67126bd  jmp 0x671276D                                 ; -> loc_671276d

loc_67126c2:  ; from 671261a
  67126c2  lea rcx,[r15+0x6A8]

Phase 13 summary: advance vector r15+0x6A8/0x6B0 by one element (in-place or grow); log count of vector r15+0x768 to [rbp+0x33A]; advance vector at r15+0x2D0/0x2D8 by one element.

---

### Phase 14 — instructions #481-#520 (0x67126cf .. 0x6712793)

  67126cf  mov rcx,[0x1233E1B0]
  67126d6  mov rax,[rcx]
  67126d9  mov rax,[rax+0x10]
  67126dd  movzx edx,byte ptr [rbp+0x857]
  67126e4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67126ea  nop
  67126eb  mov eax,[r15+0x6A8]
  67126f2  not eax
  67126f4  add eax,[r15+0x6B0]
  67126fb  mov [rbp+0x34A],ax                            ; W save count for vector r15+0x6A8
  6712702  mov rcx,[0x1233E1B0]
  6712709  mov rax,[rcx]
  671270c  mov rax,[rax+0x10]
  6712710  mov dl,0x4A
  6712712  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712718  nop
  6712719  mov [rbp+0x857],al
  671271f  mov rdx,[r15+0x590]
  6712726  cmp rdx,[r15+0x598]
  671272d  je 0x67127F1                                  ; -> loc_67127f1
  6712733  lea rax,[rdx+0x10]
  6712737  mov [rdx],rax
  671273a  mov rax,0x100000000
  6712744  mov [rdx+8],rax
  6712748  mov rcx,rdx
  671274b  mov rdx,r13
  671274e  call 0x6764990                                ; -> sub_6764990
  6712753  add qword ptr [r15+0x590],0x30
  671275b  jmp 0x6712804                                 ; -> loc_6712804

loc_6712760:  ; from 67126ad
  6712760  lea rcx,[r15+0x2D0]
  6712767  call 0x6760E60                                ; -> sub_6760e60
  671276c  nop

loc_671276d:  ; from 67126bd
  671276d  mov rcx,[0x1233E1B0]
  6712774  mov rax,[rcx]
  6712777  mov rax,[rax+0x10]
  671277b  movzx edx,byte ptr [rbp+0x857]
  6712782  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712788  nop
  6712789  mov rax,0x400000000A007009                    ; [V] packed tag 0x0A007009

Phase 14 summary: save count of vector r15+0x6A8 to [rbp+0x34A]; push a 0x30-byte element (chained pointer + 0x100000000) into vector r15+0x590/0x598 via sub_6764990 (grow via sub_6760e60 if full).

---

### Phase 15 — instructions #521-#560 (0x6712793 .. 0x671285b)

  6712793  mov [rbp+0x310],rax                            ; W save tag 0x0A007009
  671279a  mov eax,[r15+0x2D0]
  67127a1  not eax
  67127a3  add eax,[r15+0x2D8]
  67127aa  mov [rbp+0x39C],ax                             ; W save count for vector r15+0x2D0
  67127b1  mov rcx,[0x1233E1B0]
  67127b8  mov rax,[rcx]
  67127bb  mov rax,[rax+0x10]
  67127bf  mov dl,0x4A
  67127c1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67127c7  nop
  67127c8  mov [rbp+0x857],al
  67127ce  mov rdx,[r15+0x6B0]
  67127d5  cmp rdx,[r15+0x6B8]
  67127dc  je 0x671289E                                  ; -> loc_671289e
  67127e2  inc rdx
  67127e5  mov [r15+0x6B0],rdx                            ; W end_ptr += 1
  67127ec  jmp 0x67128AB                                  ; -> loc_67128ab

loc_67127f1:  ; from 67127dc
  67127f1  mov rcx,r15
  67127f4  add rcx,0x588                                  ; [V]
  67127fb  mov r8,r13                                     ; [V]
  67127fe  call 0x6765870                                ; -> sub_6765870  [V] grow vector r15+0x588
  6712803  nop

loc_6712804:  ; from 67127ec
  6712804  mov rcx,[0x1233E1B0]
  671280b  mov rax,[rcx]
  671280e  mov rax,[rax+0x10]
  6712812  movzx edx,byte ptr [rbp+0x857]
  6712819  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671281f  nop
  6712820  mov rax,0x20A207009                            ; [V] packed tag 0x0A072029
  671282a  mov [rbp+0x310],rax                            ; W save tag
  6712831  mov eax,[r15+0x590]
  6712838  sub eax,[r15+0x588]
  671283f  shr eax,4
  6712842  imul eax,0xFFFFAAAB
  6712848  dec eax
  671284a  mov [rbp+0x362],ax                             ; W save count for vector r15+0x588 (imul 0xFFFFAAAB)
  6712851  mov rcx,[0x1233E1B0]
  6712858  mov rax,[rcx]
  671285b  mov rax,[rax+0x10]

Phase 15 summary: save tag 0x0A007009 to [rbp+0x310]; save count of vector r15+0x2D0 to [rbp+0x39C]; advance vector r15+0x6A8/0x6B0 by one element (grow via sub_6765870 if full); save tag 0x0A072029 to [rbp+0x310]; save count of vector r15+0x588 (shr 4, imul 0xFFFFAAAB) to [rbp+0x362].

---

### Phase 16 — instructions #561-#600 (0x671285f .. 0x6712920)

  671285f  mov dl,0x4A                                   
  6712861  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712867  nop
  6712868  mov [rbp+0x857],al
  671286e  mov rdx,[r15+8]
  6712872  cmp rdx,[r15+0x10]
  6712876  je 0x671293C                                  ; -> loc_671293c
  671287c  mov r8d,0xC8
  6712882  mov rcx,rdx
  6712885  lea rdx,[rbp+0x310]
  671288c  call 0xEEC6EC0                                ; -> sub_eec6ec0  [V] emplace 0xC8-byte element
  6712891  add qword ptr [r15+8],0xC8                    ; W end_ptr += 0xC8
  6712899  jmp 0x671294C                                 ; -> loc_671294c

loc_671289e:  ; from 67127dc
  671289e  lea rcx,[r15+0x6A8]                          ; [V] else: grow vector r15+0x6A8
  67128a5  call 0x6760E60                                ; -> sub_6760e60
  67128aa  nop

loc_67128ab:  ; from 67127ec
  67128ab  mov rcx,[0x1233E1B0]
  67128b2  mov rax,[rcx]
  67128b5  mov rax,[rax+0x10]
  67128b9  movzx edx,byte ptr [rbp+0x857]
  67128c0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67128c6  nop
  67128c7  mov eax,[r15+0x6A8]
  67128ce  not eax
  67128d0  add eax,[r15+0x6B0]
  67128d7  mov [rbp+0x34A],ax                            ; W save count for vector r15+0x6A8
  67128de  mov rcx,[0x1233E1B0]
  67128e5  mov rax,[rcx]
  67128e8  mov rax,[rax+0x10]
  67128ec  mov dl,0x4A
  67128ee  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67128f4  nop
  67128f5  mov [rbp+0x857],al
  67128fb  mov rdx,[r15+0x590]
  6712902  cmp rdx,[r15+0x598]
  6712909  je 0x67130D4                                  ; -> loc_67130d4
  671290f  lea rax,[rdx+0x10]
  6712913  mov [rdx],rax
  6712916  mov rax,0x100000000
  6712920  mov [rdx+8],rax

Phase 16 summary: save tag dl=0x4A result to [rbp+0x857]; push a 0xC8-byte element into vector r15+8/0x10 (in-place via sub_eec6ec0, grow via sub_6760e60 if full); save count of vector r15+0x6A8 to [rbp+0x34A]; set up 0x30-byte element (chained pointer + 0x100000000) for vector r15+0x590 (call to sub_6764990 in phase 17).

---

### Phase 17 — instructions #561-#596 (0x6712924 .. 0x67129c3)

  6712924  mov rcx,rdx
  6712927  mov rdx,r13
  671292a  call 0x6764990                                ; -> sub_6764990
  671292f  add qword ptr [r15+0x590],0x30                ; W end_ptr += 0x30
  6712937  jmp 0x67130E7                                 ; -> loc_67130e7

loc_671293c:  ; from 6712876
  671293c  mov rcx,r15
  671293f  lea r8,[rbp+0x310]
  6712946  call 0x5ABA6D0                                ; -> sub_5aba6d0  [V] grow+emplace r15+8
  671294b  nop

loc_671294c:  ; from 671294b
  671294c  mov rcx,[0x1233E1B0]
  6712953  mov rax,[rcx]
  6712956  mov rax,[rax+0x10]
  671295a  movzx edx,byte ptr [rbp+0x857]
  6712961  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712967  nop
  6712968  cmp byte ptr [rbp+0x6D8],1
  671296f  jne short 0x67129C3                           ; -> loc_67129c3
  6712971  mov rcx,[rbp+0x698]
  6712978  test rcx,rcx
  671297b  je short 0x67129C3                            ; -> loc_67129c3
  671297d  mov rdx,[rbp+0x6A8]
  6712984  sub rdx,rcx
  6712987  cmp rdx,0x1000
  671298e  jb short 0x67129AC                            ; -> loc_67129ac
  6712990  mov rax,[rcx-8]
  6712994  add rcx,0xFFFFFFFFFFFFFFF8
  6712998 sub rcx,rax
  671299b cmp rcx,0x20
  671299f jae 0x6713B37                                 ; -> loc_6713b37 (near function end)
  67129a5 or rdx,0x27
  67129a9 mov rcx,rax

loc_67129ac:  ; from 671298e
  67129ac  call 0xE935700                                ; -> sub_e935700
  67129b1 lea rax,[rbp+0x698]
  67129b8 movups [rax],xmm6
  67129bb mov qword ptr [rax+0x10],0

loc_67129c3:  ; from 671296f, 671297b
  67129c3 mov rcx,r13

Phase 17 summary: finalize 0x30-byte element push into vector r15+0x590 (call sub_6764990, end_ptr += 0x30); else-branch: grow r15+8 via sub_5aba6d0 if full; then conditional block: if [rbp+0x6D8]==1 and [rbp+0x698]!=0 and ([rbp+0x6A8]-[rbp+0x698])>=0x1000, do heap-pointer arithmetic ([rcx-8], add -8, sub) and either jae 0x6713B37 or call sub_e935700; clear [rbp+0x698] struct; load r13 into rcx.

---

### Phase 18 — instructions #597-#636 (0x67129c3 .. 0x6712a61)

  67129c3  mov rcx,r13
  67129c6  call 0x6792C20                                ; -> sub_6792c20
  67129cb  mov r15,[rbp+0x790]
  67129d2  mov esi,[rbp+0x798]
  67129d8  test rsi,rsi
  67129db  je short 0x6712A26                            ; -> loc_6712a26
  67129dd  shl rsi,5
  67129e1  xor r12d,r12d
  67129e4  jmp short 0x67129F9                           ; -> loc_67129f9
  67129e6  nop [rax+rax]                                 ; R ret@6792c20+0x0+idx

loc_67129f0:  ; from 6712a01, 6712a07, 6712a16
  67129f0  add r12,0x20
  67129f4  cmp rsi,r12
  67129f7  je short 0x6712A18                            ; -> loc_6712a18

loc_67129f9:  ; from 67129e4
  67129f9  mov rcx,[r15+r12+8]
  67129fe  test rcx,rcx
  6712a01  je short 0x67129F0                            ; -> loc_67129f0
  6712a03  lock dec dword ptr [rcx+0xC]                  ; W refcount-1 at *(rcx+0xC)
  6712a07  jne short 0x67129F0
  6712a09  mov rax,[rcx]
  6712a0c mov rax,[rax+8]
  6712a10 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712a16 jmp short 0x67129F0

loc_6712a18:  ; from 67129f7
  6712a18 mov r15,[rbp+0x790]
  6712a1f lea r12,[rbp+0x3E0]

loc_6712a26:  ; from 67129db
  6712a26 lea rax,[rbp+0x7A0]
  6712a2d cmp rax,r15
  6712a30 je short 0x6712A4F                            ; -> loc_6712a4f
  6712a32 mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  6712a39 test r15,r15
  6712a3c je short 0x6712A4F                            ; -> loc_6712a4f
  6712a3e mov rax,[rcx]
  6712a41 mov rax,[rax+0x10]
  6712a45 mov rdx,r15
  6712a48 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712a4e nop

loc_6712a4f:  ; from 6712a30, 6712a3c
  6712a4f mov r15,[rbp+0x7D0]
  6712a56 mov esi,[rbp+0x7D8]
  6712a5c test rsi,rsi
  6712a5f je short 0x6712AA6                            ; -> loc_6712aa6
  6712a61 shl rsi,5

Phase 18 summary: call sub_6792c20; then three release-loops over refcounted objects: loop1 (base r15=[rbp+0x790], count esi=[rbp+0x798]) lock-dec [rcx+0xC] and call sub_eea6040 on each non-null object until count exhausted (r12 += 0x20 stride); loop2 at [rbp+0x7D0]/[rbp+0x7D8] with object table [rbp+0x7A0]; logging via sub_eea6040 between loops using data_1233e1a8.

---

### Phase 19 — instructions #637-#676 (0x6712a61 .. 0x6712af7)

  6712a61  shl rsi,5
  6712a65  xor r12d,r12d
  6712a68  jmp short 0x6712A79                           ; -> loc_6712a79
  6712a6a  nop [rax+rax]

loc_6712a70:  ; from 6712a81, 6712a87, 6712a96
  6712a70  add r12,0x20
  6712a74  cmp rsi,r12
  6712a77  je short 0x6712A98                            ; -> loc_6712a98

loc_6712a79:  ; from 6712a68
  6712a79  mov rcx,[r15+r12+8]
  6712a7e  test rcx,rcx
  6712a81  je short 0x6712A70                            ; -> loc_6712a70
  6712a83  lock dec dword ptr [rcx+0xC]                  ; W refcount-1 at *(rcx+0xC)
  6712a87  jne short 0x6712A70
  6712a89  mov rax,[rcx]
  6712a8c mov rax,[rax+8]
  6712a90 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712a96 jmp short 0x6712A70

loc_6712a98:  ; from 6712a77
  6712a98  mov r15,[rbp+0x7D0]
  6712a9f lea r12,[rbp+0x3E0]
  6712aa6 lea rax,[rbp+0x7E0]
  6712aad cmp rax,r15
  6712ab0 je short 0x6712ACF                            ; -> loc_6712acf
  6712ab2 mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  6712ab9 test r15,r15
  6712abc je short 0x6712ACF                            ; -> loc_6712acf
  6712abe mov rax,[rcx]
  6712ac1 mov rax,[rax+0x10]
  6712ac5 mov rdx,r15
  6712ac8 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712ace nop

loc_6712acf:  ; from 6712ab0, 6712abc
  6712acf mov r15,[rbp+0x810]
  6712ad6 test r15,r15
  6712ad9 je short 0x6712B55                            ; -> loc_6712b55
  6712adb mov rsi,[rbp+0x818]
  6712ae2 cmp r15,rsi
  6712ae5 jne short 0x6712AF9                           ; -> loc_6712af9
  6712ae7 jmp short 0x6712B1E                           ; -> loc_6712b1e
  6712ae9 nop [rax]

loc_6712af0:  ; from 6712b00, 6712b06, 6712b15
  6712af0 add r15,0x20
  6712af4 cmp r15,rsi
  6712af7 je short 0x6712B17                            ; -> loc_6712b17

Phase 19 summary: loop3 release over refcounted objects (base r15=[rbp+0x7D0], count esi=[rbp+0x7D8], stride 0x20): lock-dec [rcx+0xC], call sub_eea6040 when refcount hits zero; logging via sub_eea6040 using data_1233e1a8 between tables; then loop4 setup: r15=[rbp+0x810], end rsi=[rbp+0x818], if equal jump to end; else begin loop4 at 0x6712AF9.

---

### Phase 20 — instructions #677-#716 (0x6712af7 .. 0x6712ba8)

  6712af7  je short 0x6712B17                            ; -> loc_6712b17
  6712af9  mov rcx,[r15+8]
  6712afd  test rcx,rcx
  6712b00  je short 0x6712AF0                            ; -> sub_6712af0
  6712b02  lock dec dword ptr [rcx+0xC]                  ; W refcount-1 at *(rcx+0xC)
  6712b06  jne short 0x6712AF0
  6712b08  mov rax,[rcx]
  6712b0b mov rax,[rax+8]
  6712b0f call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712b15 jmp short 0x6712AF0

loc_6712b17:  ; from 6712af7
  6712b17  mov r15,[rbp+0x810]
  6712b1e  mov rdx,[rbp+0x820]
  6712b25  sub rdx,r15
  6712b28  cmp rdx,0x1000
  6712b2f  jb short 0x6712B4D                            ; -> loc_6712b4d
  6712b31  mov rax,[r15-8]
  6712b35  add r15,0xFFFFFFFFFFFFFFF8
  6712b39  sub r15,rax
  6712b3c cmp r15,0x20
  6712b40 jae 0x6713B37                                 ; -> loc_6713b37
  6712b46 add rdx,0x27
  6712b4a mov r15,rax

loc_6712b4d:  ; from 6712b2f
  6712b4d  mov rcx,r15
  6712b50 call 0xE935700                                ; -> sub_e935700
  6712b55 mov rax,[rbp+0x578]
  6712b5c cmp [rbp+0x848],rax
  6712b63 jne 0x67130C3                                 ; -> loc_67130c3
  6712b69 mov rax,[rbp+0x838]
  6712b70 mov rcx,[rax+0x10]
  6712b74 mov eax,0x9D0
  6712b79 add rcx,rax
  6712b7c call 0x5ABA5C0                                ; -> sub_5aba5c0
  6712b81 nop
  6712b82 mov r15,rax
  6712b85 movaps [rbp+0x630],xmm6                       ; W zero [rbp+0x630]
  6712b8c movaps [rbp+0x620],xmm6                       ; W zero [rbp+0x620]
  6712b93 movaps [rbp+0x610],xmm6                       ; W zero [rbp+0x610]
  6712b9a movaps [rbp+0x600],xmm6                       ; W zero [rbp+0x600]
  6712ba1 movaps [rbp+0x5F0],xmm6                       ; W zero [rbp+0x5F0]
  6712ba8 movaps [rbp+0x5E0],xmm6                       ; W zero [rbp+0x5E0]

Phase 20 summary: loop4 final release: lock-dec [rcx+0xC], call sub_eea6040; heap-pointer check (rdx = end-base, cmp 0x1000; [r15-8], add -8, sub; cmp 0x20; jae 0x6713B37 or call sub_e935700); then cmp [rbp+0x848] vs [rbp+0x578] (jne 0x67130C3); call sub_5aba5c0(&[rbp+0x838]+0x10, 0x9D0) -> r15; zero movaps blocks [rbp+0x630..0x5E0] via xmm6.

---

### Phase 21 — instructions #717-#756 (0x6712ba8 .. 0x6712c78)

  6712ba8  movaps [rbp+0x5E0],xmm6                       ; W zero [rbp+0x5E0]
  6712baf  movaps [rbp+0x5D0],xmm6                       ; W zero [rbp+0x5D0]
  6712bb6  movaps [rbp+0x5C0],xmm6                       ; W zero [rbp+0x5C0]
  6712bbd  movaps [rbp+0x5B0],xmm6                       ; W zero [rbp+0x5B0]
  6712bc4  movaps [rbp+0x5A0],xmm6                       ; W zero [rbp+0x5A0]
  6712bcb  movaps [rbp+0x590],xmm6                       ; W zero [rbp+0x590]
  6712bd2  movaps [rbp+0x580],xmm6                       ; W zero [rbp+0x580]
  6712bd9  mov qword ptr [rbp+0x640],0                   ; W clear [rbp+0x640]
  6712be4  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6712beb  mov rax,[rcx]
  6712bee  mov rax,[rax+0x10]
  6712bf2  mov dl,0x4A
  6712bf4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712bfa  nop
  6712bfb  mov [rbp+0x848],al
  6712c01  mov rdx,[r15+0x8A8]                           ; [V]
  6712c08  cmp rdx,[r15+0x8B0]
  6712c0f  je short 0x6712C25                            ; -> loc_6712c25
  6712c11  movzx eax,word ptr [rbp+0x2B8]
  6712c18  mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
  6712c1b add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8 += 2
  6712c23 jmp short 0x6712C39                           ; -> loc_6712c39

loc_6712c25:  ; from 6712c0f
  6712c25  lea rcx,[r15+0x8A0]                           ; [V]
  6712c2c  lea r8,[rbp+0x2B8]                            ; [V]
  6712c33  call 0x1EF6F90                                ; -> sub_1ef6f90  [V]
  6712c38  nop

loc_6712c39:  ; from 6712c23
  6712c39  mov rcx,[0x1233E1B0]
  6712c40  mov rax,[rcx]
  6712c43 mov rax,[rax+0x10]
  6712c47 movzx edx,byte ptr [rbp+0x848]
  6712c4e call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712c54 nop
  6712c55 mov eax,[r15+0x8A8]
  6712c5c sub eax,[r15+0x8A0]
  6712c63 shr eax,1
  6712c65 dec eax
  6712c67 mov [rbp+0x590],ax                            ; W save count (size>>1)-1
  6712c6e mov rcx,[0x1233E1B0]
  6712c75 mov rax,[rcx]
  6712c78 mov rax,[rax+0x10]

Phase 21 summary: zero remaining movaps blocks [rbp+0x5E0..0x580] and [rbp+0x640]; sub_eea6040(dl=0x4A); store word [rbp+0x2B8] into vector r15+0x8A0 slot (or grow via sub_1ef6f90); advance end by 2; compute count (size>>1)-1 into [rbp+0x590].

---

### Phase 22 — instructions #757-#796 (0x6712c78 .. 0x6712d43)

  6712c78  mov rax,[rax+0x10]
  6712c7c  mov dl,0x4A
  6712c7e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712c84  nop
  6712c85  mov [rbp+0x848],al
  6712c8b  mov rdx,[r15+0x758]                           ; [V]
  6712c92  cmp rdx,[r15+0x760]
  6712c99  je short 0x6712D1A                            ; -> loc_6712d1a
  6712c9b  lea rcx,[rbp+0x260]                           ; [V]
  6712ca2  mov eax,[rcx+0x10]
  6712ca5  mov [rdx+0x10],eax                            ; W a1+0x10
  6712ca8  movups xmm0,[rcx]                             ; [V]
  6712cab  movups [rdx],xmm0                             ; W a1+0x0..0x10
  6712cae  movzx eax,byte ptr [rbp+0x274]
  6712cb5  mov [rdx+0x14],al                             ; W a1+0x14
  6712cb8  movss xmm0,[rbp+0x278]
  6712cc0  movss [rdx+0x18],xmm0                         ; W a1+0x18
  6712cc5  movss xmm0,[rbp+0x27C]
  6712ccd  movss [rdx+0x1C],xmm0                         ; W a1+0x1C
  6712cd2  movss xmm0,[rbp+0x280]
  6712cda  movss [rdx+0x20],xmm0                         ; W a1+0x20
  6712cdf  movss xmm0,[rbp+0x284]
  6712ce7  movss [rdx+0x24],xmm0                         ; W a1+0x24
  6712cec  movups xmm0,[r14+0x88]                        ; [V]
  6712cf4  movups xmm1,[r14+0x98]                        ; [V]
  6712cfc  movups xmm2,[r14+0xA7]                        ; [V]
  6712d04  movups [rdx+0x28],xmm0                        ; W a1+0x28
  6712d08  movups [rdx+0x38],xmm1                        ; W a1+0x38
  6712d0c  movups [rdx+0x47],xmm2                        ; W a1+0x47
  6712d10  add qword ptr [r15+0x758],0x58                ; W end_ptr += 0x58
  6712d18  jmp short 0x6712D2E                           ; -> loc_6712d2e

loc_6712d1a:  ; from 6712c99
  6712d1a  lea rcx,[r15+0x750]                           ; [V] else-branch: grow
  6712d21  lea r8,[rbp+0x260]                            ; [V]
  6712d28  call 0x6760A80                                ; -> sub_6760a80  [V] push_back 0x58-byte struct
  6712d2d  nop

loc_6712d2e:  ; from 6712d18
  6712d2e  mov rcx,[0x1233E1B0]
  6712d35  mov rax,[rcx]
  6712d38 mov rax,[rax+0x10]
  6712d3c movzx edx,byte ptr [rbp+0x848]
  6712d43 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

Phase 22 summary: sub_eea6040(dl=0x4A); copy 0x58-byte struct from [rbp+0x260] into vector r15+0x758 slot (in-place, end_ptr += 0x58; else grow via sub_6760a80); sub_eea6040 again.

---

### Phase 23 — instructions #797-#836 (0x6712d43 .. 0x6712dfe)

  6712d43  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712d49  nop
  6712d4a  mov qword ptr [rbp+0x580],0x4001               ; W save tag 0x0A004001
  6712d55  mov eax,[r15+0x758]
  6712d5c  sub eax,[r15+0x750]
  6712d63  shr eax,3
  6712d66  imul eax,0xFFFF8BA3
  6712d6c  dec eax
  6712d6e  mov [rbp+0x5AC],ax                             ; W save count for vector r15+0x750 (imul 0xFFFF8BA3)
  6712d75  mov rcx,[0x1233E1B0]
  6712d7c  mov rax,[rcx]
  6712d7f mov rax,[rax+0x10]
  6712d83 mov dl,0x4A
  6712d85 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712d8b nop
  6712d8c mov [rbp+0x848],al
  6712d92 mov rdx,[r15+0x860]                            ; [V]
  6712d99 cmp rdx,[r15+0x868]
  6712da0 je short 0x6712DAE                            ; -> loc_6712dae
  6712da2 inc rdx
  6712da5 mov [r15+0x860],rdx                            ; W end_ptr += 1
  6712dac jmp short 0x6712DBB                           ; -> loc_6712dbb

loc_6712dae:  ; from 6712da0
  6712dae lea rcx,[r15+0x858]                           ; [V] else: grow
  6712db5 call 0x6760E60                                ; -> sub_6760e60  [V]
  6712dba nop

loc_6712dbb:  ; from 6712dac
  6712dbb mov rcx,[0x1233E1B0]
  6712dc2 mov rax,[rcx]
  6712dc5 mov rax,[rax+0x10]
  6712dc9 movzx edx,byte ptr [rbp+0x848]
  6712dd0 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712dd6 nop
  6712dd7 mov eax,[r15+0x858]
  6712dde not eax
  6712de0 add eax,[r15+0x860]
  6712de7 mov [rbp+0x596],ax                            ; W save count for vector r15+0x858
  6712dee mov rcx,[0x1233E1B0]
  6712df5 mov rax,[rcx]
  6712df8 mov rax,[rax+0x10]
  6712dfc mov dl,0x4A
  6712dfe call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

Phase 23 summary: save tag 0x0A004001 to [rbp+0x580]; save count of vector r15+0x750 to [rbp+0x5AC] (imul 0xFFFF8BA3); sub_eea6040; advance vector r15+0x858/0x860 by one element (grow via sub_6760e60 if full); save count of vector r15+0x858 to [rbp+0x596]; sub_eea6040 again.

---

### Phase 24 — instructions #837-#876 (0x6712e04 .. 0x6712ec1)

  6712e04  nop
  6712e05  mov [rbp+0x848],al
  6712e0b  mov rdx,[r15+0x620]                           ; [V]
  6712e12  cmp rdx,[r15+0x628]
  6712e19  je short 0x6712E27                            ; -> loc_6712e27
  6712e1b  inc rdx
  6712e1e  mov [r15+0x620],rdx                            ; W end_ptr += 1
  6712e25  jmp short 0x6712E34                           ; -> loc_6712e34

loc_6712e27:  ; from 6712e19
  6712e27  lea rcx,[r15+0x618]                           ; [V] else: grow
  6712e2e  call 0x6760E60                                ; -> sub_6760e60  [V]
  6712e33  nop

loc_6712e34:  ; from 6712e25
  6712e34  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6712e3b  mov rax,[rcx]
  6712e3e mov rax,[rax+0x10]
  6712e42 movzx edx,byte ptr [rbp+0x848]
  6712e49 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712e4f nop
  6712e50 mov eax,[r15+0x618]
  6712e57 not eax
  6712e59 add eax,[r15+0x620]
  6712e60 mov [rbp+0x5C6],ax                            ; W save count for vector r15+0x618
  6712e67 mov rcx,[0x1233E1B0]
  6712e6e mov rax,[rcx]
  6712e71 mov rax,[rax+0x10]
  6712e75 mov dl,0x4A
  6712e77 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712e7d mov [rbp+0x848],al
  6712e83 lea rcx,[r15+0x648]                           ; [V]
  6712e8a lea rdx,[rbp+0x208]                           ; [V]
  6712e91 call 0x675FB30                                ; -> sub_675fb30  [V]
  6712e96 nop
  6712e97 mov rcx,[0x1233E1B0]
  6712e9e mov rax,[rcx]
  6712ea1 mov rax,[rax+0x10]
  6712ea5 movzx edx,byte ptr [rbp+0x848]
  6712eac call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712eb2 nop
  6712eb3 mov eax,[r15+0x650]
  6712eba sub eax,[r15+0x648]
  6712ec1 shr eax,3

Phase 24 summary: advance vector r15+0x618/0x620 by one element (grow via sub_6760e60 if full); save count of vector r15+0x618 to [rbp+0x5C6]; sub_eea6040(dl=0x4A); call sub_675fb30(&r15+0x648, [rbp+0x208]); sub_eea6040 again; begin computing count of vector r15+0x648.

---

### Phase 25 — instructions #877-#916 (0x6712ec1 .. 0x6712f95)

  6712ec1  shr eax,3
  6712ec4  imul eax,0xFFFF8E39
  6712eca  dec eax
  6712ecc  mov [rbp+0x5C2],ax                            ; W save count for vector r15+0x648 (imul 0xFFFF8E39)
  6712ed3  lea rcx,[r15+0x780]                           ; [V]
  6712eda  lea rdx,[rbp+0x1B0]                           ; [V]
  6712ee1  call 0x675F3B0                                ; -> sub_675f3b0  [V]
  6712ee6  nop
  6712ee7  mov qword ptr [rbp+0x580],0xA005009           ; W save tag 0x0A005009
  6712ef2  mov eax,[r15+0x788]
  6712ef9  sub eax,[r15+0x780]
  6712f00  shr eax,3
  6712f03  imul eax,0xFFFF8BA3
  6712f09  dec eax
  6712f0b  mov [rbp+0x5A8],ax                            ; W save count for vector r15+0x780 (imul 0xFFFF8BA3)
  6712f12  mov rcx,[0x1233E1B0]
  6712f19 mov rax,[rcx]
  6712f1c mov rax,[rax+0x10]
  6712f20 mov dl,0x4A
  6712f22 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712f28 mov [rbp+0x848],al
  6712f2e mov rsi,[r15+0x770]                           ; [V]
  6712f35 cmp rsi,[r15+0x778]
  6712f3c je short 0x6712F7F                            ; -> loc_6712f7f
  6712f3e mov rax,[rbp+0x128]                           ; [V]
  6712f45 mov [rsi],rax                                 ; W a1+0x0
  6712f48 lea rcx,[rsi+8]                               ; [V]
  6712f4c lea rdx,[rbp+0x130]                           ; [V]
  6712f53 call 0xE869FF0                                ; -> sub_e869ff0  [V]
  6712f58 nop
  6712f59 mov rax,[rbp+0x1A8]                           ; [V]
  6712f60 mov [rsi+0x80],rax                            ; W a1+0x80
  6712f67 mov qword ptr [rbp+0x1A8],0                   ; W clear saved value
  6712f72 add qword ptr [r15+0x770],0x88                ; W end_ptr += 0x88
  6712f7d jmp short 0x6712F96                           ; -> loc_6712f96

loc_6712f7f:  ; from 6712f3c
  6712f7f  lea rcx,[r15+0x768]                           ; [V] else-branch: grow
  6712f86  mov rdx,rsi                                   ; [V]
  6712f89  lea r8,[rbp+0x128]                            ; [V]
  6712f90 call 0x6760710                                ; -> sub_6760710  [V] push_back 0x88-byte struct
  6712f95  nop

Phase 25 summary: finish count of vector r15+0x648 to [rbp+0x5C2]; call sub_675f3b0(&r15+0x780, [rbp+0x1B0]); save tag 0x0A005009 to [rbp+0x580]; save count of vector r15+0x780 to [rbp+0x5A8]; sub_eea6040(dl=0x4A); push 0x88-byte slot into vector r15+0x768/0x770 (in-place via sub_e869ff0, else grow via sub_6760710).

---

### Phase 26 — instructions #917-#956 (0x6712f96 .. 0x6713052)

  6712f96  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6712f9d  mov rax,[rcx]
  6712fa0  mov rax,[rax+0x10]
  6712fa4  movzx edx,byte ptr [rbp+0x848]
  6712fab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712fb1  nop
  6712fb2  mov eax,[r15+0x770]
  6712fb9  sub eax,[r15+0x768]
  6712fc0  shr eax,3
  6712fc3  imul eax,0xFFFFF0F1
  6712fc9  dec eax
  6712fcb  mov [rbp+0x5AA],ax                            ; W save count for vector r15+0x768 (imul 0xFFFFF0F1)
  6712fd2  mov rcx,[0x1233E1B0]
  6712fd9 mov rax,[rcx]
  6712fdc mov rax,[rax+0x10]
  6712fe0 mov dl,0x4A
  6712fe2 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6712fe8 nop
  6712fe9 mov [rbp+0x848],al
  6712fef mov rdx,[r15+0x6B0]                           ; [V]
  6712ff6 cmp rdx,[r15+0x6B8]
  6712ffd je short 0x671300B                            ; -> loc_671300b
  6712fff inc rdx
  6713002 mov [r15+0x6B0],rdx                            ; W end_ptr += 1
  6713009 jmp short 0x671301B                           ; -> loc_671301b

loc_671300b:  ; from 6712ffd
  671300b mov rcx,r15                                   ; [V]
  671300e add rcx,0x6A8                                 ; [V]
  6713015 call 0x6760E60                                ; -> sub_6760e60  [V] grow vector r15+0x6A8
  671301a nop

loc_671301b:  ; from 6713009
  671301b mov rcx,[0x1233E1B0]
  6713022 mov rax,[rcx]
  6713025 mov rax,[rax+0x10]
  6713029 movzx edx,byte ptr [rbp+0x848]
  6713030 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713036 nop
  6713037 mov qword ptr [rbp+0x580],0xA207009           ; W save tag 0x0A207009
  6713042 mov eax,[r15+0x6A8]
  6713049 not eax
  671304b add eax,[r15+0x6B0]
  6713052 mov [rbp+0x5BA],ax                            ; W save count for vector r15+0x6A8

Phase 26 summary: sub_eea6040(dl=0x4A); save count of vector r15+0x768 to [rbp+0x5AA] (imul 0xFFFFF0F1); sub_eea6040 again; advance vector r15+0x6A8/0x6B0 by one element (grow via sub_6760e60 if full); save tag 0x0A207009 to [rbp+0x580]; save count of vector r15+0x6A8 to [rbp+0x5BA].

---

### Phase 27 — instructions #957-#996 (0x6713052 .. 0x67130fc)

  6713052  mov [rbp+0x5BA],ax
  6713059  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6713060  mov rax,[rcx]
  6713063 mov rax,[rax+0x10]
  6713067 mov dl,0x4A
  6713069 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671306f nop
  6713070 mov [rbp+0x848],al
  6713076 mov rdx,[r15+8]                               ; [V]
  671307a cmp rdx,[r15+0x10]
  671307e je short 0x671309B                            ; -> loc_671309b
  6713080 mov r8d,0xC8                                  ; [V] size 0xC8
  6713086 mov rcx,rdx
  6713089 mov rdx,r13                                   ; [V]
  671308c call 0xEEC6EC0                                ; -> sub_eec6ec0  [V] emplace 0xC8-byte
  6713091 add qword ptr [r15+8],0xC8                    ; W end_ptr += 0xC8
  6713099 jmp short 0x67130A7                           ; -> loc_67130a7

loc_671309b:  ; from 671307e
  671309b mov rcx,r15                                   ; [V] else: grow+emplace
  671309e mov r8,r13
  67130a1 call 0x5ABA6D0                                ; -> sub_5aba6d0  [V]
  67130a6 nop

loc_67130a7:  ; from 6713099
  67130a7 mov rcx,[0x1233E1B0]
  67130ae mov rax,[rcx]
  67130b1 mov rax,[rax+0x10]
  67130b5 movzx edx,byte ptr [rbp+0x848]
  67130bc call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67130c2 nop
  67130c3 lea rcx,[rbp+0x120]                           ; [V]
  67130ca call 0x67E1840                                ; -> sub_67e1840  [V]
  67130cf jmp 0x6713999                                 ; -> loc_6713999  [V] tail jump

  ; forward-referenced blocks (targets of earlier jumps, not reached linearly here):
loc_67130d4:  ; from 6712909
  67130d4 mov rcx,r15
  67130d7 add rcx,0x588                                 ; [V]
  67130de mov r8,r13                                    ; [V]
  67130e1 call 0x6765870                                ; -> sub_6765870  [V]
  67130e6 nop

loc_67130e7:  ; from 671275b
  67130e7 mov rcx,[0x1233E1B0]
  67130ee mov rax,[rcx]
  67130f1 mov rax,[rax+0x10]
  67130f5 movzx edx,byte ptr [rbp+0x857]
  67130fc call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

Phase 27 summary: sub_eea6040(dl=0x4A); push 0xC8-byte element into vector r15+8/0x10 (in-place via sub_eec6ec0, else grow via sub_5aba6d0); sub_eea6040; sub_67e1840(rbp+0x120); tail-jmp 0x6713999. Also includes forward targets: loc_67130d4 (grow vector r15+0x588 via sub_6765870) and loc_67130e7 (sub_eea6040 with dl=[rbp+0x857]).

---

### Phase 28 — instructions #997-#1036 (0x67130fc .. 0x67131b6)

  67130fc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713102  nop
  6713103  mov rax,0x400000020A207009                    ; [V] packed tag 0x0A207002 0x40000002?
  671310d  mov [rbp+0x310],rax                           ; W save tag
  6713114  mov eax,[r15+0x590]
  671311b  sub eax,[r15+0x588]
  6713122  shr eax,4
  6713125  imul eax,0xFFFFAAAB
  671312b  dec eax
  671312d  mov [rbp+0x362],ax                            ; W save count for vector r15+0x588 (shr 4, imul 0xFFFFAAAB)
  6713134  mov rcx,[0x1233E1B0]
  671313b mov rax,[rcx]
  671313e mov rax,[rax+0x10]
  6713142 mov dl,0x4A
  6713144 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671314a nop
  671314b mov [rbp+0x857],al
  6713151 mov rdx,[r15+8]                               ; [V]
  6713155 cmp rdx,[r15+0x10]
  6713159 je short 0x671317A                            ; -> loc_671317a
  671315b mov r8d,0xC8                                  ; [V] size 0xC8
  6713161 mov rcx,rdx
  6713164 lea rdx,[rbp+0x310]                           ; [V]
  671316b call 0xEEC6EC0                                ; -> sub_eec6ec0  [V] emplace 0xC8-byte
  6713170 add qword ptr [r15+8],0xC8                    ; W end_ptr += 0xC8
  6713178 jmp short 0x671318A                           ; -> loc_671318a

loc_671317a:  ; from 6713159
  671317a mov rcx,r15                                   ; [V] else: grow+emplace
  671317d lea r8,[rbp+0x310]
  6713184 call 0x5ABA6D0                                ; -> sub_5aba6d0  [V]
  6713189 nop

loc_671318a:  ; from 6713178
  671318a mov rcx,[0x1233E1B0]
  6713191 mov rax,[rcx]
  6713194 mov rax,[rax+0x10]
  6713198 movzx edx,byte ptr [rbp+0x857]
  671319f call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67131a5 nop
  67131a6 cmp byte ptr [rbp+0x6E0],1
  67131ad jne short 0x6713201                           ; -> loc_6713201
  67131af mov rcx,[rbp+0x6A0]
  67131b6 test rcx,rcx

Phase 28 summary: sub_eea6040; save tag 0x400000020A207009 to [rbp+0x310]; save count of vector r15+0x588 to [rbp+0x362] (shr 4, imul 0xFFFFAAAB); sub_eea6040(dl=0x4A); push 0xC8-byte element into vector r15+8/0x10; sub_eea6040(dl=[rbp+0x857]); conditional: if [rbp+0x6E0]==1 and [rbp+0x6A0]!=0, do heap-pointer check ([rcx-8], add -8, sub; cmp 0x20; jae 0x6713B37 or call sub_e935700) and clear [rbp+0x6A0] struct; then call sub_6792400 and start release loop over [rbp+0x790]/[rbp+0x798].

---

### Phase 29 — instructions #1037-#1076 (0x67131b6 .. 0x6713258)

  67131b6  test rcx,rcx
  67131b9  je short 0x6713201                            ; -> loc_6713201
  67131bb  mov rdx,[rbp+0x6B0]                           ; [V]
  67131c2  sub rdx,rcx                                   ; [V]
  67131c5  cmp rdx,0x1000                                ; [V]
  67131cc  jb short 0x67131EA                            ; -> loc_67131ea
  67131ce  mov rax,[rcx-8]                               ; R a0-0x8
  67131d2  add rcx,0xFFFFFFFFFFFFFFF8                    ; [V]
  67131d6  sub rcx,rax                                   ; [V]
  67131d9  cmp rcx,0x20                                  ; [V]
  67131dd  jae 0x6713B37                                 ; -> loc_6713b37
  67131e3  or rdx,0x27                                   ; [V]
  67131e7  mov rcx,rax                                   ; [V]

loc_67131ea:  ; from 67131cc
  67131ea  call 0xE935700                                ; -> sub_e935700
  67131ef  lea rax,[rbp+0x6A0]                           ; [V]
  67131f6  movups [rax],xmm6                             ; W zero [rbp+0x6A0]
  67131f9  mov qword ptr [rax+0x10],0                    ; W zero [rbp+0x6A0+0x10]

loc_6713201:  ; from 67131b9
  6713201  mov rcx,r13                                   ; [V]
  6713204  call 0x6792400                                ; -> sub_6792400  [V]
  6713209  mov r15,[rbp+0x790]                           ; [V] base of object table
  6713210  mov esi,[rbp+0x798]                           ; [V] count
  6713216  test rsi,rsi
  6713219  je short 0x6713266                            ; -> loc_6713266
  671321b  shl rsi,5                                     ; count *= 0x20
  671321f xor r12d,r12d                                 ; index=0
  6713222 jmp short 0x6713239                           ; -> loc_6713239
  6713224 nop [rax+rax]

loc_6713230:  ; from 6713241, 6713247, 6713256
  6713230 add r12,0x20                                  ; index += 0x20
  6713234 cmp rsi,r12
  6713237 je short 0x6713258                            ; -> loc_6713258

loc_6713239:  ; from 6713222
  6713239 mov rcx,[r15+r12+8]                           ; R object ptr
  671323e test rcx,rcx
  6713241 je short 0x6713230                            ; -> loc_6713230
  6713243 lock dec dword ptr [rcx+0xC]                  ; W refcount-1
  6713247 jne short 0x6713230                           ; -> loc_6713230
  6713249 mov rax,[rcx]                                 ; R vtable
  671324c mov rax,[rax+8]                               ; R *(vtable+8)
  6713250 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713256 jmp short 0x6713230                           ; -> loc_6713230

loc_6713258:  ; from 6713237
  6713258 mov r15,[rbp+0x790]

Phase 29 summary: heap-pointer check for object at [rbp+0x6A0] (cmp 0x1000, [rcx-8], jae 0x6713B37 or call sub_e935700); clear [rbp+0x6A0] struct; call sub_6792400; release loop over refcounted objects at r15=[rbp+0x790], count [rbp+0x798], stride 0x20: lock-dec [rcx+0xC], call sub_eea6040 on zero refcount.

---

### Phase 30 — instructions #1077-#1116 (0x6713258 .. 0x67132f9)

  6713258  mov r15,[rbp+0x790]                           ; [V] re-load base
  671325f  lea r12,[rbp+0x3E0]                           ; [V]
  6713266  lea rax,[rbp+0x7A0]                           ; [V]
  671326d  cmp rax,r15
  6713270  je short 0x671328F                            ; -> loc_671328f
  6713272  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  6713279  test r15,r15
  671327c  je short 0x671328F                            ; -> loc_671328f
  671327e  mov rax,[rcx]
  6713281 mov rax,[rax+0x10]
  6713285 mov rdx,r15
  6713288 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671328e nop

loc_671328f:  ; from 6713270, 671327c
  671328f  mov r15,[rbp+0x7D0]                           ; [V] base of next table
  6713296  mov esi,[rbp+0x7D8]                           ; [V] count
  671329c test rsi,rsi
  671329f je short 0x67132E6                            ; -> loc_67132e6
  67132a1 shl rsi,5                                     ; count *= 0x20
  67132a5 xor r12d,r12d                                 ; index=0
  67132a8 jmp short 0x67132B9                           ; -> loc_67132b9
  67132aa nop [rax+rax]

loc_67132b0:  ; from 67132c1, 67132c7, 67132d6
  67132b0 add r12,0x20                                  ; index += 0x20
  67132b4 cmp rsi,r12
  67132b7 je short 0x67132D8                            ; -> loc_67132d8

loc_67132b9:  ; from 67132a8
  67132b9 mov rcx,[r15+r12+8]                           ; R object ptr
  67132be test rcx,rcx
  67132c1 je short 0x67132B0                            ; -> loc_67132b0
  67132c3 lock dec dword ptr [rcx+0xC]                  ; W refcount-1
  67132c7 jne short 0x67132B0                           ; -> loc_67132b0
  67132c9 mov rax,[rcx]                                 ; R vtable
  67132cc mov rax,[rax+8]                               ; R *(vtable+8)
  67132d0 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67132d6 jmp short 0x67132B0                           ; -> loc_67132b0

loc_67132d8:  ; from 67132b7
  67132d8 mov r15,[rbp+0x7D0]                           ; [V] re-load base
  67132df lea r12,[rbp+0x3E0]                           ; [V]

loc_67132e6:  ; from 671329f
  67132e6 lea rax,[rbp+0x7E0]                           ; [V]
  67132ed cmp rax,r15
  67132f0 je short 0x671330F                            ; -> loc_671330f
  67132f2 mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
  67132f9 test r15,r15

Phase 30 summary: logging sub_eea6040 via data_1233e1a8 after first table; release loop over refcounted objects at r15=[rbp+0x7D0], count [rbp+0x7D8], stride 0x20: lock-dec [rcx+0xC], call sub_eea6040 on zero refcount; then setup for next table at [rbp+0x7E0].

---

### Phase 31 — instructions #1117-#1156 (0x67132f9 .. 0x671338d)

  67132f9  test r15,r15
  67132fc  je short 0x671330F                            ; -> loc_671330f
  67132fe  mov rax,[rcx]                                 ; R a0+0x0
  6713301  mov rax,[rax+0x10]                            ; R *(a0+0x0)+0x10
  6713305  mov rdx,r15                                   ; [V]
  6713308  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671330e  nop

loc_671330f:  ; from 67132fc
  671330f  mov r15,[rbp+0x810]                           ; [V] base of next table
  6713316  test r15,r15
  6713319  je short 0x6713395                            ; -> loc_6713395
  671331b  mov rsi,[rbp+0x818]                           ; [V] end
  6713322  cmp r15,rsi
  6713325  jne short 0x6713339                           ; -> loc_6713339
  6713327  jmp short 0x671335E                           ; -> loc_671335e
  6713329 nop [rax]

loc_6713330:  ; from 6713340, 6713346, 6713355
  6713330 add r15,0x20                                  ; index += 0x20
  6713334 cmp r15,rsi
  6713337 je short 0x6713357                            ; -> loc_6713357

loc_6713339:  ; from 6713325
  6713339 mov rcx,[r15+8]                               ; R object ptr
  671333d test rcx,rcx
  6713340 je short 0x6713330                            ; -> loc_6713330
  6713342 lock dec dword ptr [rcx+0xC]                  ; W refcount-1
  6713346 jne short 0x6713330                           ; -> loc_6713330
  6713348 mov rax,[rcx]                                 ; R vtable
  671334b mov rax,[rax+8]                               ; R *(vtable+8)
  671334f call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713355 jmp short 0x6713330                           ; -> loc_6713330

loc_6713357:  ; from 6713337
  6713357 mov r15,[rbp+0x810]                           ; [V] re-load base

loc_671335e:  ; from 6713327
  671335e  mov rdx,[rbp+0x820]                           ; [V] end
  6713365  sub rdx,r15                                 ; [V]
  6713368  cmp rdx,0x1000                              ; [V]
  671336f  jb short 0x671338D                          ; -> loc_671338d
  6713371  mov rax,[r15-8]                             ; R a0-0x8
  6713375  add r15,0xFFFFFFFFFFFFFFF8                  ; [V]
  6713379  sub r15,rax                                 ; [V]
  671337c  cmp r15,0x20                                ; [V]
  6713380  jae 0x6713B37                               ; -> loc_6713b37
  6713386  add rdx,0x27                                ; [V]
  671338a  mov r15,rax                                 ; [V]

loc_671338d:  ; from 671336f
  671338d mov rcx,r15                                 ; [V]

Phase 31 summary: logging sub_eea6040 via data_1233e1a8; release loop over refcounted objects at r15=[rbp+0x810], end [rbp+0x820], stride 0x20: lock-dec [rcx+0xC], call sub_eea6040 on zero refcount; then heap-pointer check (rdx = end-base, cmp 0x1000; [r15-8], add -8, sub; cmp 0x20; jae 0x6713B37 or call sub_e935700).

---

### Phase 32 — instructions #1157-#1196 (0x671338d .. 0x6713465)

  671338d  mov rcx,r15
  6713390  call 0xE935700                                ; -> sub_e935700
  6713395  mov rax,[rbp+0x578]
  671339c  cmp [rbp+0x848],rax
  67133a3  jne 0x671398D                                 ; -> loc_671398d
  67133a9  mov rax,[rbp+0x838]
  67133b0  mov rcx,[rax+0x10]
  67133b4  mov eax,0x9D0
  67133b9  add rcx,rax
  67133bc  call 0x5ABA5C0                                ; -> sub_5aba5c0
  67133c1  nop
  67133c2  mov r15,rax
  67133c5  movaps [rbp+0x630],xmm6                       ; W zero [rbp+0x630]
  67133cc  movaps [rbp+0x620],xmm6                       ; W zero [rbp+0x620]
  67133d3  movaps [rbp+0x610],xmm6                       ; W zero [rbp+0x610]
  67133da  movaps [rbp+0x600],xmm6                       ; W zero [rbp+0x600]
  67133e1  movaps [rbp+0x5F0],xmm6                       ; W zero [rbp+0x5F0]
  67133e8  movaps [rbp+0x5E0],xmm6                       ; W zero [rbp+0x5E0]
  67133ef  movaps [rbp+0x5D0],xmm6                       ; W zero [rbp+0x5D0]
  67133f6  movaps [rbp+0x5C0],xmm6                       ; W zero [rbp+0x5C0]
  67133fd  movaps [rbp+0x5B0],xmm6                       ; W zero [rbp+0x5B0]
  6713404  movaps [rbp+0x5A0],xmm6                       ; W zero [rbp+0x5A0]
  671340b  movaps [rbp+0x590],xmm6                       ; W zero [rbp+0x590]
  6713412  movaps [rbp+0x580],xmm6                       ; W zero [rbp+0x580]
  6713419  mov qword ptr [rbp+0x640],0                   ; W clear [rbp+0x640]
  6713424  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671342b  mov rax,[rcx]
  671342e mov rax,[rax+0x10]
  6713432 mov dl,0x4A
  6713434 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671343a nop
  671343b mov [rbp+0x848],al
  6713441 mov rdx,[r15+0x8A8]                           ; R ret@5aba5c0+0x8A8
  6713448 cmp rdx,[r15+0x8B0]                           ; R ret@5aba5c0+0x8B0
  671344f je short 0x6713465                            ; -> loc_6713465
  6713451 movzx eax,word ptr [rbp+0x2B8]
  6713458 mov [rdx],ax                                  ; W *(ret@5aba5c0+0x8A8)+0x0
  671345b add qword ptr [r15+0x8A8],2                   ; W ret@5aba5c0+0x8A8
  6713463 jmp short 0x6713479                           ; -> loc_6713479

loc_6713465:  ; from 671344f
  6713465 lea rcx,[r15+0x8A0]                           ; [V] else-branch: grow

Phase 32 summary: epilogue: call sub_e935700; cmp [rbp+0x848] vs [rbp+0x578] (jne 0x671398D); call sub_5aba5c0(&[rbp+0x838]+0x10, 0x9D0) -> r15; zero movaps blocks [rbp+0x630..0x580] via xmm6; clear [rbp+0x640]; sub_eea6040(dl=0x4A); push word [rbp+0x2B8] into vector r15+0x8A0 (in-place or grow).

---

### Phase 33 — instructions #1197-#1236 (0x6713465 .. 0x6713527)

  6713465  lea rcx,[r15+0x8A0]                           ; [V]
  671346c  lea r8,[rbp+0x2B8]                            ; [V]
  6713473  call 0x1EF6F90                                ; -> sub_1ef6f90  [V] grow vector r15+0x8A0
  6713478  nop

loc_6713479:  ; from 6713463
  6713479  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6713480  mov rax,[rcx]
  6713483 mov rax,[rax+0x10]
  6713487 movzx edx,byte ptr [rbp+0x848]
  671348e call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713494 nop
  6713495 mov eax,[r15+0x8A8]
  671349c sub eax,[r15+0x8A0]
  67134a3 shr eax,1
  67134a5 dec eax
  67134a7 mov [rbp+0x590],ax                            ; W save count (size>>1)-1
  67134ae mov rcx,[0x1233E1B0]
  67134b5 mov rax,[rcx]
  67134b8 mov rax,[rax+0x10]
  67134bc mov dl,0x4A
  67134be call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67134c4 nop
  67134c5 mov [rbp+0x848],al
  67134cb mov rdx,[r15+0x758]                           ; [V]
  67134d2 cmp rdx,[r15+0x760]
  67134d9 je short 0x671355A                            ; -> loc_671355a
  67134db lea rcx,[rbp+0x260]                           ; [V]
  67134e2 mov eax,[rcx+0x10]
  67134e5 mov [rdx+0x10],eax                            ; W a1+0x10
  67134e8 movups xmm0,[rcx]                             ; [V]
  67134eb movups [rdx],xmm0                             ; W a1+0x0..0x10
  67134ee movzx eax,byte ptr [rbp+0x274]
  67134f5 mov [rdx+0x14],al                             ; W a1+0x14
  67134f8 movss xmm0,[rbp+0x278]
  6713500 movss [rdx+0x18],xmm0                         ; W a1+0x18
  6713505 movss xmm0,[rbp+0x27C]
  671350d movss [rdx+0x1C],xmm0                         ; W a1+0x1C
  6713512 movss xmm0,[rbp+0x280]
  671351a movss [rdx+0x20],xmm0                         ; W a1+0x20
  671351f movss xmm0,[rbp+0x284]
  6713527 movss [rdx+0x24],xmm0                         ; W a1+0x24

Phase 33 summary: grow vector r15+0x8A0 via sub_1ef6f90; compute count (size>>1)-1 into [rbp+0x590]; sub_eea6040(dl=0x4A); copy 0x58-byte struct from [rbp+0x260] into vector r15+0x758 slot (in-place; else-branch at 0x671355A).

---

### Phase 34 — instructions #1237-#1276 (0x6713527 .. 0x67135ee)

  6713527  movss [rdx+0x24],xmm0                        ; W a1+0x24
  671352c  movups xmm0,[r14+0x88]                       ; [V]
  6713534  movups xmm1,[r14+0x98]                       ; [V]
  671353c  movups xmm2,[r14+0xA7]                       ; [V]
  6713544  movups [rdx+0x28],xmm0                       ; W a1+0x28
  6713548  movups [rdx+0x38],xmm1                       ; W a1+0x38
  671354c  movups [rdx+0x47],xmm2                       ; W a1+0x47
  6713550  add qword ptr [r15+0x758],0x58               ; W end_ptr += 0x58
  6713558  jmp short 0x671356E                          ; -> loc_671356e

loc_671355a:  ; from 67134d9
  671355a  lea rcx,[r15+0x750]                          ; [V] else-branch: grow
  6713561  lea r8,[rbp+0x260]                           ; [V]
  6713568  call 0x6760A80                                ; -> sub_6760a80  [V] push_back 0x58-byte struct
  671356d  nop

loc_671356e:  ; from 6713558
  671356e  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6713575  mov rax,[rcx]
  6713578 mov rax,[rax+0x10]
  671357c movzx edx,byte ptr [rbp+0x848]
  6713583 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713589 nop
  671358a mov qword ptr [rbp+0x580],0x4001              ; W save tag 0x0A004001
  6713595 mov eax,[r15+0x758]
  671359c sub eax,[r15+0x750]
  67135a3 shr eax,3
  67135a6 imul eax,0xFFFF8BA3
  67135ac dec eax
  67135ae mov [rbp+0x5AC],ax                            ; W save count for vector r15+0x750 (imul 0xFFFF8BA3)
  67135b5 mov rcx,[0x1233E1B0]
  67135bc mov rax,[rcx]
  67135bf mov rax,[rax+0x10]
  67135c3 mov dl,0x4A
  67135c5 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67135cb nop
  67135cc mov [rbp+0x848],al
  67135d2 mov rdx,[r15+0x860]                           ; [V]
  67135d9 cmp rdx,[r15+0x868]
  67135e0 je short 0x67135EE                            ; -> loc_67135ee
  67135e2 inc rdx
  67135e5 mov [r15+0x860],rdx                           ; W end_ptr += 1
  67135ec jmp short 0x67135FB                           ; -> loc_67135fb

loc_67135ee:  ; from 67135e0
  67135ee lea rcx,[r15+0x858]                           ; [V] else: grow

Phase 34 summary: finish 0x58-byte struct copy into vector r15+0x758 (end_ptr += 0x58; else grow via sub_6760a80); sub_eea6040(dl=0x4A); save tag 0x0A004001 to [rbp+0x580]; save count of vector r15+0x750 to [rbp+0x5AC] (imul 0xFFFF8BA3); sub_eea6040(dl=0x4A); advance vector r15+0x858/0x860 by one element (grow via sub_6760e60 if full).

---

### Phase 35 — instructions #1277-#1316 (0x67135ee .. 0x67136ab)

  67135ee  lea rcx,[r15+0x858]                           ; [V] else-branch: grow
  67135f5  call 0x6760E60                                ; -> sub_6760e60  [V]
  67135fa  nop

loc_67135fb:  ; from 67135ec
  67135fb  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  6713602  mov rax,[rcx]
  6713605 mov rax,[rax+0x10]
  6713609 movzx edx,byte ptr [rbp+0x848]
  6713610 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713616 nop
  6713617 mov eax,[r15+0x858]
  671361e not eax
  6713620 add eax,[r15+0x860]
  6713627 mov [rbp+0x596],ax                            ; W save count for vector r15+0x858
  671362e mov rcx,[0x1233E1B0]
  6713635 mov rax,[rcx]
  6713638 mov rax,[rax+0x10]
  671363c mov dl,0x4A
  671363e call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713644 nop
  6713645 mov [rbp+0x848],al
  671364b mov rdx,[r15+0x620]                           ; [V]
  6713652 cmp rdx,[r15+0x628]
  6713659 je short 0x6713667                            ; -> loc_6713667
  671365b inc rdx
  671365e mov [r15+0x620],rdx                           ; W end_ptr += 1
  6713665 jmp short 0x6713674                           ; -> loc_6713674

loc_6713667:  ; from 6713659
  6713667 lea rcx,[r15+0x618]                           ; [V] else: grow
  671366e call 0x6760E60                                ; -> sub_6760e60  [V]
  6713673 nop

loc_6713674:  ; from 6713665
  6713674 mov rcx,[0x1233E1B0]
  671367b mov rax,[rcx]
  671367e mov rax,[rax+0x10]
  6713682 movzx edx,byte ptr [rbp+0x848]
  6713689 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671368f nop
  6713690 mov qword ptr [rbp+0x580],0x8004009           ; W save tag 0x0A804009
  671369b mov eax,[r15+0x618]
  67136a2 not eax
  67136a4 add eax,[r15+0x620]
  67136ab mov [rbp+0x5C6],ax                            ; W save count for vector r15+0x618

Phase 35 summary: grow vector r15+0x858 via sub_6760e60; sub_eea6040; save count of vector r15+0x858 to [rbp+0x596]; sub_eea6040(dl=0x4A); advance vector r15+0x618/0x620 by one element (grow via sub_6760e60 if full); sub_eea6040; save tag 0x0A804009 to [rbp+0x580]; save count of vector r15+0x618 to [rbp+0x5C6].

---

### Phase 36 — instructions #1317-#1356 (0x67136ab .. 0x671376e)

  67136ab  mov [rbp+0x5C6],ax                            ; W save count for vector r15+0x618
  67136b2  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67136b9  mov rax,[rcx]
  67136bc mov rax,[rax+0x10]
  67136c0 mov dl,0x4A
  67136c2 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67136c8 mov [rbp+0x848],al
  67136ce lea rcx,[r15+0x648]                           ; [V]
  67136d5 lea rdx,[rbp+0x208]                           ; [V]
  67136dc call 0x675FB30                                ; -> sub_675fb30  [V]
  67136e1 nop
  67136e2 mov rcx,[0x1233E1B0]
  67136e9 mov rax,[rcx]
  67136ec mov rax,[rax+0x10]
  67136f0 movzx edx,byte ptr [rbp+0x848]
  67136f7 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67136fd nop
  67136fe mov eax,[r15+0x650]
  6713705 sub eax,[r15+0x648]
  671370c shr eax,3
  671370f imul eax,0xFFFF8E39
  6713715 dec eax
  6713717 mov [rbp+0x5C2],ax                            ; W save count for vector r15+0x648 (imul 0xFFFF8E39)
  671371e lea rcx,[r15+0x780]                           ; [V]
  6713725 lea rdx,[rbp+0x1B0]                           ; [V]
  671372c call 0x675F3B0                                ; -> sub_675f3b0  [V]
  6713731 nop
  6713732 mov eax,[r15+0x788]
  6713739 sub eax,[r15+0x780]
  6713740 shr eax,3
  6713743 imul eax,0xFFFF8BA3
  6713749 dec eax
  671374b mov [rbp+0x5A8],ax                            ; W save count for vector r15+0x780 (imul 0xFFFF8BA3)
  6713752 mov rcx,[0x1233E1B0]
  6713759 mov rax,[rcx]
  671375c mov rax,[rax+0x10]
  6713760 mov dl,0x4A
  6713762 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713768 mov [rbp+0x848],al
  671376e mov rsi,[r15+0x770]                           ; [V]

Phase 36 summary: sub_eea6040(dl=0x4A); call sub_675fb30(&r15+0x648, [rbp+0x208]); sub_eea6040; save count of vector r15+0x648 to [rbp+0x5C2]; call sub_675f3b0(&r15+0x780, [rbp+0x1B0]); save count of vector r15+0x780 to [rbp+0x5A8]; sub_eea6040(dl=0x4A); load rsi=[r15+0x770] (vector slot ptr).

---

### Phase 37 — instructions #1357-#1396 (0x671376e .. 0x671383a)

  671376e  mov rsi,[r15+0x770]                           ; [V]
  6713775  cmp rsi,[r15+0x778]
  671377c  je short 0x67137BF                            ; -> loc_67137bf
  671377e  mov rax,[rbp+0x128]                           ; [V]
  6713785  mov [rsi],rax                                 ; W a1+0x0
  6713788  lea rcx,[rsi+8]                               ; [V]
  671378c  lea rdx,[rbp+0x130]                           ; [V]
  6713793  call 0xE869FF0                                ; -> sub_e869ff0  [V]
  6713798  nop
  6713799  mov rax,[rbp+0x1A8]                           ; [V]
  67137a0  mov [rsi+0x80],rax                            ; W a1+0x80
  67137a7  mov qword ptr [rbp+0x1A8],0                   ; W clear saved value
  67137b2  add qword ptr [r15+0x770],0x88                ; W end_ptr += 0x88
  67137bd  jmp short 0x67137D6                           ; -> loc_67137d6

loc_67137bf:  ; from 671377c
  67137bf  lea rcx,[r15+0x768]                           ; [V] else-branch: grow
  67137c6  mov rdx,rsi                                   ; [V]
  67137c9  lea r8,[rbp+0x128]                            ; [V]
  67137d0 call 0x6760710                                ; -> sub_6760710  [V] push_back 0x88-byte struct
  67137d5  nop

loc_67137d6:  ; from 67137bd
  67137d6  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  67137dd  mov rax,[rcx]
  67137e0 mov rax,[rax+0x10]
  67137e4 movzx edx,byte ptr [rbp+0x848]
  67137eb call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67137f1 nop
  67137f2 mov qword ptr [rbp+0x580],0xA007009           ; W save tag 0x0A007009
  67137fd mov eax,[r15+0x770]
  6713804 sub eax,[r15+0x768]
  671380b shr eax,3
  671380e imul eax,0xFFFFF0F1
  6713814 dec eax
  6713816 mov [rbp+0x5AA],ax                            ; W save count for vector r15+0x768 (imul 0xFFFFF0F1)
  671381d mov rcx,[0x1233E1B0]
  6713824 mov rax,[rcx]
  6713827 mov rax,[rax+0x10]
  671382b mov dl,0x4A
  671382d call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713833 nop
  6713834 mov [rbp+0x848],al
  671383a mov rdx,[r15+0x2D8]                           ; [V]

Phase 37 summary: push 0x88-byte slot into vector r15+0x768/0x770 (in-place via sub_e869ff0, else grow via sub_6760710); sub_eea6040(dl=0x4A); save tag 0x0A007009 to [rbp+0x580]; save count of vector r15+0x768 to [rbp+0x5AA] (imul 0xFFFFF0F1); sub_eea6040(dl=0x4A); advance vector r15+0x2D0/0x2D8 by one element.

---

### Phase 38 — instructions #1397-#1436 (0x671383a .. 0x67138ed)

  671383a  mov rdx,[r15+0x2D8]                           ; [V]
  6713841  cmp rdx,[r15+0x2E0]
  6713848  je short 0x6713856                            ; -> loc_6713856
  671384a  inc rdx
  671384d  mov [r15+0x2D8],rdx                            ; W end_ptr += 1
  6713854  jmp short 0x6713863                           ; -> loc_6713863

loc_6713856:  ; from 6713848
  6713856  lea rcx,[r15+0x2D0]                           ; [V] else: grow
  671385d  call 0x6760E60                                ; -> sub_6760e60  [V]
  6713862  nop

loc_6713863:  ; from 6713854
  6713863  mov rcx,[0x1233E1B0]                          ; [data_1233e1b0]
  671386a  mov rax,[rcx]
  671386d mov rax,[rax+0x10]
  6713871 movzx edx,byte ptr [rbp+0x848]
  6713878 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671387e nop
  671387f mov eax,[r15+0x2D0]
  6713886 not eax
  6713888 add eax,[r15+0x2D8]
  671388f mov [rbp+0x60C],ax                            ; W save count for vector r15+0x2D0
  6713896 mov rcx,[0x1233E1B0]
  671389d mov rax,[rcx]
  67138a0 mov rax,[rax+0x10]
  67138a4 mov dl,0x4A
  67138a6 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67138ac nop
  67138ad mov [rbp+0x848],al
  67138b3 mov rdx,[r15+0x6B0]                           ; [V]
  67138ba cmp rdx,[r15+0x6B8]
  67138c1 je short 0x67138CF                            ; -> loc_67138cf
  67138c3 inc rdx
  67138c6 mov [r15+0x6B0],rdx                           ; W end_ptr += 1
  67138cd jmp short 0x67138DF                           ; -> loc_67138df

loc_67138cf:  ; from 67138c1
  67138cf mov rcx,r15                                   ; [V] else: grow
  67138d2 add rcx,0x6A8                                 ; [V]
  67138d9 call 0x6760E60                                ; -> sub_6760e60  [V]
  67138de nop

loc_67138df:  ; from 67138cd
  67138df mov rcx,[0x1233E1B0]
  67138e6 mov rax,[rcx]
  67138e9 mov rax,[rax+0x10]
  67138ed movzx edx,byte ptr [rbp+0x848]

Phase 38 summary: advance vector r15+0x2D0/0x2D8 by one element (grow via sub_6760e60 if full); sub_eea6040(dl=0x4A); save count of vector r15+0x2D0 to [rbp+0x60C]; sub_eea6040(dl=0x4A); advance vector r15+0x6A8/0x6B0 by one element (grow via sub_6760e60 if full).

---

### Phase 39 — instructions #1437-#1476 (0x67138ed .. 0x67139a0)

  67138ed  movzx edx,byte ptr [rbp+0x848]
  67138f4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67138fa  nop
  67138fb  mov rax,0x400000000A207009                    ; [V] packed tag 0x0A207009
  6713905  mov [rbp+0x580],rax                           ; W save tag
  671390c  mov eax,[r15+0x6A8]
  6713913  not eax
  6713915  add eax,[r15+0x6B0]
  671391c  mov [rbp+0x5BA],ax                            ; W save count for vector r15+0x6A8
  6713923  mov rcx,[0x1233E1B0]
  671392a mov rax,[rcx]
  671392d mov rax,[rax+0x10]
  6713931 mov dl,0x4A
  6713933 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713939 nop
  671393a mov [rbp+0x848],al
  6713940 mov rdx,[r15+8]                               ; [V]
  6713944 cmp rdx,[r15+0x10]
  6713948 je short 0x6713965                            ; -> loc_6713965
  671394a mov r8d,0xC8                                  ; [V] size 0xC8
  6713950 mov rcx,rdx
  6713953 mov rdx,r13                                   ; [V]
  6713956 call 0xEEC6EC0                                ; -> sub_eec6ec0  [V] emplace 0xC8-byte
  671395b add qword ptr [r15+8],0xC8                    ; W end_ptr += 0xC8
  6713963 jmp short 0x6713971                           ; -> loc_6713971

loc_6713965:  ; from 6713948
  6713965 mov rcx,r15                                   ; [V] else: grow+emplace
  6713968 mov r8,r13
  671396b call 0x5ABA6D0                                ; -> sub_5aba6d0  [V]
  6713970 nop

loc_6713971:  ; from 6713963
  6713971 mov rcx,[0x1233E1B0]
  6713978 mov rax,[rcx]
  671397b mov rax,[rax+0x10]
  671397f movzx edx,byte ptr [rbp+0x848]
  6713986 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  671398c nop
  671398d lea rcx,[rbp+0x120]                           ; [V]
  6713994 call 0x67E1840                                ; -> sub_67e1840  [V]
  6713999 mov rcx,r12                                   ; [V]
  671399c nop [rax]                                     ; R ret@67e1840+0x0
  67139a0 call 0x67E23F0                                ; -> sub_67e23f0  [V] epilogue helper

Phase 39 summary: sub_eea6040(dl=0x4A); save tag 0x0A207009 to [rbp+0x580]; save count of vector r15+0x6A8 to [rbp+0x5BA]; sub_eea6040(dl=0x4A); push 0xC8-byte element into vector r15+8/0x10 (in-place via sub_eec6ec0, else grow via sub_5aba6d0); sub_eea6040(dl=0x4A); sub_67e1840(rbp+0x120); mov rcx,r12; call sub_67e23f0 (epilogue).

---

### Phase 40 — instructions #1477-#1516 (0x67139a0 .. 0x6713a42)

  67139a0  call 0x67E23F0                                ; -> sub_67e23f0  [V]
  67139a5  cmp byte ptr [rbp+0x80],3                     ; [V]
  67139ac  jne short 0x67139F0                           ; -> loc_67139f0
  67139ae  mov rsi,[rbp+0x78]                            ; [V]
  67139b2  test rsi,rsi
  67139b5  je short 0x67139F0                            ; -> loc_67139f0
  67139b7  lock dec dword ptr [rsi+8]                    ; W refcount-1
  67139bb  jne short 0x67139F0                           ; -> loc_67139f0
  67139bd  mov rax,[rsi]                                 ; R vtable
  67139c0  mov rax,[rax]                                 ; R *(vtable+0)
  67139c3  mov rcx,rsi                                   ; [V]
  67139c6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67139cc  lock dec dword ptr [rsi+0xC]                  ; W refcount2-1
  67139d0  jne short 0x67139F0                           ; -> loc_67139f0
  67139d2  mov rax,[rsi]                                 ; R vtable
  67139d5  mov rax,[rax+8]                               ; R *(vtable+8)
  67139d9  mov rcx,rsi                                   ; [V]
  67139dc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  67139e2 nop [rax+rax]

loc_67139f0:  ; from 67139ac, 67139b5, 67139bb, 67139d0
  67139f0  mov r15,[rbp+0x50]                            ; [V] loop base
  67139f4  test r15,r15
  67139f7  je 0x670BAD0                                  ; -> sub_670BAD0  [V] epilogue/restore
  67139fd  mov r12,[rbp+0x58]                            ; [V] loop end
  6713a01 jmp short 0x6713A14                           ; -> loc_6713a14
  6713a03 nop [rax+rax]

loc_6713a10:  ; from 6713a22, 6713a2b, 6713a31, 6713a46, 6713a58
  6713a10 add r15,0x28                                  ; [V] stride 0x28

loc_6713a14:  ; from 6713a01
  6713a14 cmp r15,r12
  6713a17 je 0x670BAD0                                  ; -> sub_670BAD0  [V]
  6713a1d cmp byte ptr [r15+0x18],2                     ; [V] type check
  6713a22 jne short 0x6713A10                           ; -> loc_6713a10
  6713a24 mov rsi,[r15+8]                               ; [V] object ptr
  6713a28 test rsi,rsi
  6713a2b je short 0x6713A10                            ; -> loc_6713a10
  6713a2d lock dec dword ptr [rsi+8]                    ; W refcount-1
  6713a31 jne short 0x6713A10                           ; -> loc_6713a10
  6713a33 mov rax,[rsi]                                 ; R vtable
  6713a36 mov rax,[rax]                                 ; R *(vtable+0)
  6713a39 mov rcx,rsi                                   ; [V]
  6713a3c call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713a42 lock dec dword ptr [rsi+0xC]                  ; W refcount2-1

Phase 40 summary: epilogue: call sub_67e23f0; conditional release of object at [rbp+0x78] (lock-dec refcount, call sub_eea6040 on vtable+0 and vtable+8, lock-dec refcount2); loop over [rbp+0x50]..[rbp+0x58] stride 0x28: if byte [r15+0x18]==2, release refcounted object at [r15+8] similarly; then jmp sub_670BAD0 (function epilogue/restore).

---

### Phase 41 — instructions #1517-#1556 (0x6713a42 .. 0x6713b02)

  6713a42  lock dec dword ptr [rsi+0xC]                  ; W refcount2-1
  6713a46  jne short 0x6713A10                           ; -> sub_6713a10
  6713a48  mov rax,[rsi]                                 ; R vtable
  6713a4b  mov rax,[rax+8]                               ; R *(vtable+8)
  6713a4f  mov rcx,rsi                                   ; [V]
  6713a52  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713a58  jmp short 0x6713A10                           ; -> sub_6713a10

  ; target at 0x6713a5a (loop body from phase 40's jmp targets continue here):
  6713a5a  mov rsi,[rbp+0x308]                           ; [V] object ptr
  6713a61  test rsi,rsi
  6713a64  je short 0x6713A91                            ; -> loc_6713a91
  6713a66  lock dec dword ptr [rsi+8]                    ; W refcount-1
  6713a6a  jne short 0x6713A91                           ; -> loc_6713a91
  6713a6c  mov rax,[rsi]                                 ; R vtable
  6713a6f  mov rax,[rax]                                 ; R *(vtable+0)
  6713a72  mov rcx,rsi                                   ; [V]
  6713a75  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713a7b  lock dec dword ptr [rsi+0xC]                  ; W refcount2-1
  6713a7f  jne short 0x6713A91                           ; -> loc_6713a91
  6713a81  mov rax,[rsi]                                 ; R vtable
  6713a84  mov rax,[rax+8]                               ; R *(vtable+8)
  6713a88  mov rcx,rsi                                   ; [V]
  6713a8b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_6713a91:  ; from 6713a64, 6713a6a, 6713a7f
  6713a91  mov rcx,[0x1233E1B0]                          ; [data_1233E1B0]
  6713a98  mov rax,[rcx]
  6713a9b mov rax,[rax+0x10]
  6713a9f movzx edx,byte ptr [rbp+0x847]
  6713aa6 call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  6713aac nop
  6713aad movaps xmm6,[rbp+0x860]                        ; R restore xmm6
  6713ab4 movaps xmm7,[rbp+0x870]                        ; R restore xmm7
  6713abb movaps xmm8,[rbp+0x880]                        ; R restore xmm8
  6713ac3 movaps xmm9,[rbp+0x890]                        ; R restore xmm9
  6713acb movaps xmm10,[rbp+0x8A0]                       ; R restore xmm10
  6713ad3 movaps xmm11,[rbp+0x8B0]                       ; R restore xmm11
  6713adb movaps xmm12,[rbp+0x8C0]                       ; R restore xmm12
  6713ae3 movaps xmm13,[rbp+0x8D0]                       ; R restore xmm13
  6713aeb movaps xmm14,[rbp+0x8E0]                       ; R restore xmm14
  6713af3 movaps xmm15,[rbp+0x8F0]                       ; R restore xmm15
  6713afb add rsp,0x988                                 ; W stack cleanup
  6713b02 pop rbx                                       ; R restore rbx

Phase 41 summary: finish release of object at [rbp+0x308] (lock-dec refcount, call sub_eea6040, lock-dec refcount2, call sub_eea6040); final sub_eea6040(dl=[rbp+0x847]); restore xmm6..xmm15 from [rbp+0x860..0x8F0]; add rsp,0x988; pop rbx.

---

### Phase 42 — instructions #1557-#1596 (0x6713b02 .. 0x6713b91)

  6713b02  pop rbx                                        ; R restore rbx
  6713b03  pop rdi                                        ; R restore rdi
  6713b04  pop rsi                                        ; R restore rsi
  6713b05  pop r12                                        ; R restore r12
  6713b07  pop r13                                        ; R restore r13
  6713b09  pop r14                                        ; R restore r14
  6713b0b  pop r15                                        ; R restore r15
  6713b0d  pop rbp                                        ; R restore rbp
  6713b0e  ret                                            ; [V] function return

  ; cold block after ret (linear continuation):
  6713b0f  call 0x78ED0                                   ; -> sub_78ed0
  6713b14  nop
  6713b15  mov ecx,0x30
  6713b1a  call 0x9BC830                                  ; -> sub_9bc830
  6713b1f  nop
  6713b20  jmp 0x670B922                                  ; -> sub_670b922
  6713b25  call 0xB432E0                                  ; -> sub_b432e0
  6713b2a  nop
  6713b2b  call 0x1166E0                                  ; -> sub_1166e0
  6713b30  nop
  6713b31  call 0x1166E0                                  ; -> sub_1166e0
  6713b36  nop

  ; heap-pointer-check failure path (target of jae 0x6713B37 from earlier phases):
loc_6713b37:  ; from 671299f, 67131dd, 6713380
  6713b37  mov qword ptr [rsp+0x20],0                     ; W [rsp+0x20]=0
  6713b40  xor ecx,ecx
  6713b42  xor edx,edx
  6713b44  xor r8d,r8d
  6713b47  xor r9d,r9d
  6713b4a  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
  6713b50  lea rcx,[0x129FB398]                          ; [data_129fb398]
  6713b57  call 0xE938CB0                                ; -> sub_e938cb0
  6713b5c  cmp dword ptr [0x129FB398],0xFFFFFFFF         ; [data_129fb398]
  6713b63  jne 0x670B7AD                                 ; -> sub_670b7ad
  6713b69  lea rdx,[0xF60E1A3]                           ; [data_f60e1a3] "RenderChunkFogAlpha"
  6713b70  lea rsi,[rbp+0x580]                           ; [V]
  6713b77  mov rcx,rsi                                   ; [V]
  6713b7a  call 0x79580                                  ; -> sub_79580
  6713b7f  nop
  6713b80  mov r8,[rbp+0x590]                            ; [V]
  6713b87  cmp qword ptr [rbp+0x598],0x10                ; [V]
  6713b8f  jb short 0x6713B98                            ; -> loc_6713b98
  6713b91  mov rsi,[rbp+0x580]                           ; [V]

Phase 42 summary: function epilogue: pop rbx,rdi,rsi,r12,r13,r14,r15,rbp; ret. Cold block: calls sub_78ed0/sub_9bc830/sub_b432e0/sub_1166e0, jmp sub_670b922. Heap-pointer-check failure path (0x6713b37): zero [rsp+0x20], call via [0xF9A8C78], sub_e938cb0, check data_129fb398, jne sub_670b7ad; load string "RenderChunkFogAlpha" at data_f60e1a3, sub_79580([rbp+0x580]); compare [rbp+0x598] vs 0x10.


---

### Phase 43 — instructions #1597-#1636 (0x6713b98 .. 0x6713c38)

  6713b98  test r8,r8
  6713b9b  je short 0x6713BC2                            ; -> loc_6713bc2
  6713b9d  mov eax,r8d
  6713ba0  and eax,3
  6713ba3  mov rcx,0x100000001B3
  6713bad  cmp r8,4
  6713bb1  jae short 0x6713BCE                           ; -> loc_6713bce
  6713bb3  mov rdx,0xCBF29CE484222325
  6713bbd  xor r9d,r9d
  6713bc0  jmp short 0x6713C20                           ; -> loc_6713c20

loc_6713bc2:  ; from 6713b9b
  6713bc2  mov rdx,0xCBF29CE484222325
  6713bcc  jmp short 0x6713C40                           ; -> loc_6713c40

loc_6713bce:  ; from 6713bb1
  6713bce  and r8,0xFFFFFFFFFFFFFFFC
  6713bd2  mov rdx,0xCBF29CE484222325
  6713bdc  xor r9d,r9d

loc_6713bdf:  ; from 6713c19
  6713bdf  movzx r10d,byte ptr [rsi+r9]
  6713be4  xor r10,rdx
  6713be7  imul r10,rcx
  6713beb  movzx edx,byte ptr [rsi+r9+1]
  6713bf1  xor rdx,r10
  6713bf4  imul rdx,rcx
  6713bf8  movzx r10d,byte ptr [rsi+r9+2]
  6713bfe  xor r10,rdx
  6713c01  imul r10,rcx
  6713c05  movzx edx,byte ptr [rsi+r9+3]
  6713c0b  xor rdx,r10
  6713c0e  imul rdx,rcx
  6713c12  add r9,4
  6713c16  cmp r8,r9
  6713c19  jne short 0x6713BDF                           ; -> loc_6713bdf
  6713c1b  test rax,rax
  6713c1e  je short 0x6713C40                            ; -> loc_6713c40

loc_6713c20:  ; from 6713bc0
  6713c20  add rsi,r9
  6713c23  xor r8d,r8d
  6713c26  mov r9,rdx

loc_6713c29:  ; from 6713c3e
  6713c29  movzx edx,byte ptr [rsi+r8]
  6713c2e  xor rdx,r9
  6713c31  imul rdx,rcx
  6713c35  inc r8
  6713c38  mov r9,rdx

Phase 43 summary: FNV-1a style hash preamble and 4-byte unrolled loop over a byte buffer (rsi = data pointer, r8 = length). Seed hash rdx = 0xCBF29CE484222325, prime rcx = 0x100000001B3, index r9 = 0. If r8 == 0 jump to loc_6713bc2 (seed only); if r8 >= 4 jump to loc_6713bce (align length down to multiple of 4) then enter the 4-byte loop at loc_6713bdf; otherwise fall to the tail path at loc_6713c20. The 4-byte loop (loc_6713bdf) XORs each byte into the hash and multiplies by the prime, processing 4 bytes per iteration (r9 += 4) until r9 >= r8; then test rax,rax / je short 0x6713C40 to the store. The tail path (loc_6713c20) advances rsi by r9, zeroes r8d, copies rdx to r9, then processes remaining bytes one at a time at loc_6713c29 (XOR + imul per byte, r8++).

---

### Phase 44 — instructions #1637-#1644 (0x6713c3b .. 0x6713c5f)

  6713c3b  cmp rax,r8
  6713c3e  jne short 0x6713C29                           ; -> loc_6713c29

loc_6713c40:  ; from 6713bcc, 6713c1e
  6713c40  mov [0x129FB390],rdx                          ; [data_129fb390]
  6713c47  lea rcx,[rbp+0x580]
  6713c4e  call 0x73150                                  ; -> sub_73150
  6713c53  lea rcx,[0x129FB398]                          ; [data_129fb398]
  6713c5a  call 0xE938D70                                ; -> sub_e938d70
  6713c5f  jmp 0x670B7AD                                 ; -> sub_670b7ad

Phase 44 summary: tail-loop exit test (cmp rax,r8; jne short 0x6713C29 back to loc_6713c29). At loc_6713c40: store final hash to data_129FB390 ([0x129FB390]); lea rcx,[rbp+0x580] and call sub_73150 ([0x6713c4e]); lea rcx,[0x129FB398] and call sub_e938d70 ([0x6713c5a]); tail-jmp 0x670B7AD ([0x6713c5f]) to the shared epilogue sub_670b7ad. The jmp at 0x6713c5f is 5 bytes and ends exactly at function boundary 0x6713c64 (0x6713c64 `nop [rax+rax]` is padding/start of next function, not part of this function).

---

### Epilogue — function end 0x6713c64

The function's terminal block computes an FNV-1a style hash (offset basis 0xCBF29CE484222325, prime 0x100000001B3) over a byte buffer (rsi = data pointer, r8 = length), processing 4 bytes per iteration in the unrolled loop at loc_6713bdf and remaining bytes one at a time at loc_6713c29. The final hash is stored to data_129FB390 ([0x129FB390]), then sub_73150 is called with rcx = &[rbp+0x580] (packed tag) and sub_e938d70 with rcx = &data_129FB398, followed by a tail-jump to sub_670b7ad (shared restore/epilogue). Last instruction 0x6713c5f `jmp 0x670B7AD` ends exactly at 0x6713c64; instruction range is complete with no gaps.

---

### Callee / struct field summary (this unit)

New callees:
- sub_73150 — direct call at 0x6713c4e, rcx = lea [rbp+0x580] (packed tag storage) [V]
- sub_e938d70 — direct call at 0x6713c5a, rcx = lea [0x129FB398] [V]
- sub_670b7ad — tail-jump target at 0x6713c5f (shared epilogue/restore; already logged in earlier phases)

Data / fields touched:
- [rbp+0x580] — packed tag, read via lea rcx,[rbp+0x580] at 0x6713c47 [V][R]
- data_129FB390 ([0x129FB390]) — final hash result, written via mov [0x129FB390],rdx at 0x6713c40 [V][W]
- data_129FB398 ([0x129FB398]) — read via lea rcx,[0x129FB398] at 0x6713c53 [V][R]

Hash registers: r8 = buffer length, rsi = data pointer, rdx = hash accumulator (seed 0xCBF29CE484222325), rcx = FNV prime 0x100000001B3, r9 = byte index, r10 = byte temp, rax = loop-limit compare.

---