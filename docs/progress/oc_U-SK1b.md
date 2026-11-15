# oc_U-SK1b — unit U-SK1b (join-3 sub_665b624 tail + cold range)

Target: Minecraft.Windows.exe 1.26.62.01
Task: fix corrupted tail of join-3 sub_665b624 range 0x665bd31..0x665c272 by re-disassembling with rdis (<=40 instructions/phase, exact rdis lines), then continue toward cold range 0x665cf64..0x665d7e5.
Static analysis only; no builds/commits; only create docs/progress/oc_<unit>.md; tag claims [V]/[I]/[?].

## NEXT
- [ ] Phase 7+ of main range: 0x665c272..end (exclusive 0x665c272) — complete residual tail after 0x665c251 block
- [ ] Cold range head 0x665cf64..0x665d19d — phase-by-phase exact rdis lines (<=40 instr/phase)
- [ ] Cold range tail 0x665d19e..0x665d7e4 (exclusive end 0x665d7e5) — phase-by-phase exact rdis lines (<=40 instr/phase)
- [ ] Verify all phase instruction counts <=40
- [ ] Tag each phase [V] verified / [I] inferred / [?] uncertain

---

## PHASES — main range 0x665bd31..0x665c272

### Phase 1 — 0x665bd31..0x665bd6e  [V]
; from rdis work/rdis/665bd31.txt lines 2-6
  665bd31  mov rax,[rbp+0x430]
  665bd38  mov [rbx+0x80],rax
  665bd3f  mov qword ptr [rbp+0x430],0
  665bd4a  add qword ptr [rsi+0x770],0x88
  665bd55  jmp short 0x665BD6E      ; -> loc_665bd6e

; block at loc_665bd57 (fall-through target, 5 instr)
  665bd57  lea r8,[rbp+0x3B0]
  665bd5e  lea rcx,[rsi+0x768]
  665bd65  mov rdx,rbx
  665bd68  call 0x6760710           ; -> sub_6760710
  665bd6d  nop

### Phase 2 — loc_665bd6e..0x665bdca  [V]
; from rdis work/rdis/665bd31.txt lines 13-33
  665bd6e  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665bd75  mov rax,[rcx]
  665bd78  mov rax,[rax+0x10]
  665bd7c  movzx edx,byte ptr [rbp+0x540]
  665bd83  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665bd89  nop
  665bd8a  mov qword ptr [rbp+0x1E0],0x2003001
  665bd95  mov eax,[rsi+0x770]
  665bd9b  sub eax,[rsi+0x768]
  665bda1  shr eax,3
  665bda4  imul eax,0xFFFFF0F1
  665bdaa  dec eax
  665bdac  mov [rbp+0x20A],ax
  665bdb3  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665bdba  mov rax,[rcx]
  665bdbd  mov rax,[rax+0x10]
  665bdc1  mov dl,0x4A
  665bdc3  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665bdc9  nop
  665bdca  mov [rbp+0x540],al

### Phase 3 — 0x665bdd0..0x665be0e  [V]
; from rdis work/rdis/665bd31.txt lines 34-44
  665bdd0  mov rdx,[rsi+0x680]
  665bdd7  cmp rdx,[rsi+0x688]
  665bdde  je short 0x665BE10       ; -> loc_665be10
  665bde0  movss xmm0,[rbp+0x3A0]
  665bde8  movss [rdx],xmm0
  665bdec  movss xmm0,[rbp+0x3A4]
  665bdf4  movss [rdx+4],xmm0
  665bdf9  movss xmm0,[rbp+0x3A8]
  665be01  movss [rdx+8],xmm0
  665be06  add qword ptr [rsi+0x680],0xC
  665be0e  jmp short 0x665BE24      ; -> loc_665be24

### Phase 4 — loc_665be10..0x665be23  [V]
; from rdis work/rdis/665bd31.txt lines 46-50
  665be10  lea r8,[rbp+0x3A0]
  665be17  lea rcx,[rsi+0x678]
  665be1e  call 0x1770A70           ; -> sub_1770a70
  665be23  nop

### Phase 5 — loc_665be24..0x665be57  [V]
; from rdis work/rdis/665bd31.txt lines 52-64
  665be24  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665be2b  mov rax,[rcx]
  665be2e  mov rax,[rax+0x10]
  665be32  movzx edx,byte ptr [rbp+0x540]
  665be39  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665be3f  nop
  665be40  mov eax,[rsi+0x680]
  665be46  sub eax,[rsi+0x678]
  665be4c  shr eax,2
  665be4f  imul eax,0xFFFFAAAB
  665be55  dec eax
  665be57  mov [rbp+0x21E],ax

### Phase 6 — 0x665be5e..0x665be75  [V]
; from rdis work/rdis/665bd31.txt lines 65-71
  665be5e  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665be65  mov rax,[rcx]
  665be68  mov rax,[rax+0x10]
  665be6c  mov dl,0x4A
  665be6e  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665be74  nop
  665be75  mov [rbp+0x540],al

### Phase 7 — 0x665be7b..0x665be95  [V]
; from rdis work/rdis/665bd31.txt lines 72-77
  665be7b  mov rdx,[rsi+0x830]
  665be82  cmp rdx,[rsi+0x838]
  665be89  je short 0x665BE97       ; -> loc_665be97
  665be8b  inc rdx
  665be8e  mov [rsi+0x830],rdx
  665be95  jmp short 0x665BEA4      ; -> loc_665bea4

### Phase 8 — loc_665be97..0x665bea3  [V]
; from rdis work/rdis/665bd31.txt lines 79-82
  665be97  lea rcx,[rsi+0x828]
  665be9e  call 0x6760E60           ; -> sub_6760e60
  665bea3  nop

### Phase 9 — loc_665bea4..0x665bee0  [V]
; from rdis work/rdis/665bd31.txt lines 84-96
  665bea4  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665beab  mov rax,[rcx]
  665beae  mov rax,[rax+0x10]
  665beb2  movzx edx,byte ptr [rbp+0x540]
  665beb9  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665bebf  nop
  665bec0  mov qword ptr [rbp+0x1E0],0x2803021
  665becb  mov eax,[rsi+0x828]
  665bed1  not eax
  665bed3  add eax,[rsi+0x830]
  665bed9  mov [rbp+0x1FA],ax
  665bee0  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]

### Phase 10 — 0x665bee7..0x665bef7  [V]
; from rdis work/rdis/665bd31.txt lines 97-102
  665bee7  mov rax,[rcx]
  665beea  mov rax,[rax+0x10]
  665beee  mov dl,0x4A
  665bef0  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665bef6  nop
  665bef7  mov [rbp+0x540],al

### Phase 11 — 0x665befd..0x665bf81  [V]
; from rdis work/rdis/665bd31.txt lines 103-127
  665befd  lea r8,[rbp+0x344]
  665bf04  mov rdx,[rsi+0x758]
  665bf0b  cmp rdx,[rsi+0x760]
  665bf12  je short 0x665BF8B       ; -> loc_665bf8b
  665bf14  mov eax,[r8+0x10]
  665bf18  mov [rdx+0x10],eax
  665bf1b  movups xmm0,[r8]
  665bf1f  movups [rdx],xmm0
  665bf22  movzx eax,byte ptr [rbp+0x358]
  665bf29  mov [rdx+0x14],al
  665bf2c  movss xmm0,[rbp+0x35C]
  665bf34  movss [rdx+0x18],xmm0
  665bf39  movss xmm0,[rbp+0x360]
  665bf41  movss [rdx+0x1C],xmm0
  665bf46  movss xmm0,[rbp+0x364]
  665bf4e  movss [rdx+0x20],xmm0
  665bf53  movss xmm0,[rbp+0x368]
  665bf5b  movss [rdx+0x24],xmm0
  665bf60  movups xmm0,[rbp+0x36C]
  665bf67  movups xmm1,[rbp+0x37C]
  665bf6e  movups xmm2,[rbp+0x38B]
  665bf75  movups [rdx+0x28],xmm0
  665bf79  movups [rdx+0x38],xmm1
  665bf7d  movups [rdx+0x47],xmm2
  665bf81  add qword ptr [rsi+0x758],0x58
  665bf89  jmp short 0x665BF98      ; -> loc_665bf98

### Phase 12 — loc_665bf8b..0x665bf97  [V]
; from rdis work/rdis/665bd31.txt lines 130-133
  665bf8b  lea rcx,[rsi+0x750]
  665bf92  call 0x6760A80           ; -> sub_6760a80
  665bf97  nop

### Phase 13 — loc_665bf98..0x665bfcb  [V]
; from rdis work/rdis/665bd31.txt lines 135-147
  665bf98  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665bf9f  mov rax,[rcx]
  665bfa2  mov rax,[rax+0x10]
  665bfa6  movzx edx,byte ptr [rbp+0x540]
  665bfad  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665bfb3  nop
  665bfb4  mov eax,[rsi+0x758]
  665bfba  sub eax,[rsi+0x750]
  665bfc0  shr eax,3
  665bfc3  imul eax,0xFFFF8BA3
  665bfc9  dec eax
  665bfcb  mov [rbp+0x20C],ax

### Phase 14 — 0x665bfd2..0x665bfe9  [V]
; from rdis work/rdis/665bd31.txt lines 148-154
  665bfd2  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665bfd9  mov rax,[rcx]
  665bfdc  mov rax,[rax+0x10]
  665bfe0  mov dl,0x4A
  665bfe2  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665bfe8  nop
  665bfe9  mov [rbp+0x540],al

### Phase 15 — 0x665bfef..0x665c009  [V]
; from rdis work/rdis/665bd31.txt lines 155-160
  665bfef  mov rdx,[rsi+0x458]
  665bff6  cmp rdx,[rsi+0x460]
  665bffd  je short 0x665C00B       ; -> loc_665c00b
  665bfff  inc rdx
  665c002  mov [rsi+0x458],rdx
  665c009  jmp short 0x665C01B      ; -> loc_665c01b

### Phase 16 — loc_665c00b..0x665c01a  [V]
; from rdis work/rdis/665bd31.txt lines 162-166
  665c00b  mov rcx,rsi
  665c00e  add rcx,0x450
  665c015  call 0x6760E60           ; -> sub_6760e60
  665c01a  nop

### Phase 17 — loc_665c01b..0x665c074  [V]
; from rdis work/rdis/665bd31.txt lines 168-187
  665c01b  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665c022  mov rax,[rcx]
  665c025  mov rax,[rax+0x10]
  665c029  movzx edx,byte ptr [rbp+0x540]
  665c030  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665c036  nop
  665c037  mov rax,0x400002807021
  665c041  mov [rbp+0x1E0],rax
  665c048  mov eax,[rsi+0x450]
  665c04e  not eax
  665c050  add eax,[rsi+0x458]
  665c056  mov [rbp+0x24C],ax
  665c05d  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665c064  mov rax,[rcx]
  665c067  mov rax,[rax+0x10]
  665c06b  mov dl,0x4A
  665c06d  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665c073  nop
  665c074  mov [rbp+0x540],al

### Phase 18 — 0x665c07a..0x665c0a1  [V]
; from rdis work/rdis/665bd31.txt lines 188-196
  665c07a  mov rax,[rsi+8]
  665c07e  cmp rax,[rsi+0x10]
  665c082  je short 0x665C0A3       ; -> loc_665c0a3
  665c084  lea rdx,[rbp+0x1E0]
  665c08b  mov r8d,0xC8
  665c091  mov rcx,rax
  665c094  call 0xEEC6EC0           ; -> sub_eec6ec0
  665c099  add qword ptr [rsi+8],0xC8
  665c0a1  jmp short 0x665C0B6      ; -> loc_665c0b6

### Phase 19 — loc_665c0a3..0x665c0b5  [V]
; from rdis work/rdis/665bd31.txt lines 198-203
  665c0a3  lea r8,[rbp+0x1E0]
  665c0aa  mov rcx,rsi
  665c0ad  mov rdx,rax
  665c0b0  call 0x5ABA6D0           ; -> sub_5aba6d0
  665c0b5  nop

### Phase 20 — loc_665c0b6..0x665c102  [V]
; from rdis work/rdis/665bd31.txt lines 205-220
  665c0b6  mov rcx,[0x1233E1B0]     ; [data_1233e1b0]
  665c0bd  mov rax,[rcx]
  665c0c0  mov rax,[rax+0x10]
  665c0c4  movzx edx,byte ptr [rbp+0x540]
  665c0cb  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665c0d1  nop
  665c0d2  lea rcx,[rbp+0x340]
  665c0d9  call 0x66A9C10           ; -> sub_66a9c10
  665c0de  cmp byte ptr [rbp+0x1B0],1
  665c0e5  jne 0x665D076            ; -> loc_665d076
  665c0eb  mov rcx,[rbp+0x170]
  665c0f2  test rcx,rcx
  665c0f5  je 0x665D076             ; -> loc_665d076
  665c0fb  mov rdx,[rbp+0x180]
  665c102  jmp 0x665D049            ; -> loc_665d049

### Phase 21 — 0x665c107..0x665c15a  [V]
; from rdis work/rdis/665bd31.txt lines 221-236
  665c107  xor edi,edi
  665c109  mov rbx,[rbp+0x78]
  665c10d  mov [rbp+0x4A8],rbx
  665c114  mov [rbp+0x4B0],rdi
  665c11b  mov [rbp+0x4B8],cl
  665c121  mov rcx,[rbp+0xA0]
  665c128  mov [rbp+0x4D0],rcx
  665c12f  movaps xmm0,[rbp+0x90]
  665c136  movups [rbp+0x4C0],xmm0
  665c13d  mov ecx,0x9D0
  665c142  add rcx,[rsi+0x10]
  665c146  mov [rsp+0x30],rax
  665c14b  mov [rsp+0x28],r10
  665c150  mov [rsp+0x20],r11
  665c155  call 0x67EA0D0           ; -> sub_67ea0d0
  665c15a  nop

### Phase 22 — 0x665c15b..0x665c1a1  [V]
; from rdis work/rdis/665bd31.txt lines 237-255
  665c15b  lea rcx,[rbp+0x340]
  665c162  call 0x673CB40           ; -> sub_673cb40
  665c167  cmp byte ptr [rbp+0x88],3
  665c16e  jne short 0x665C1A7      ; -> loc_665c1a7
  665c170  mov rsi,[rbp+0x80]
  665c177  test rsi,rsi
  665c17a  je short 0x665C1A7       ; -> loc_665c1a7
  665c17c  lock dec dword ptr [rsi+8]
  665c180  jne short 0x665C1A7      ; -> loc_665c1a7
  665c182  mov rax,[rsi]
  665c185  mov rax,[rax]
  665c188  mov rcx,rsi
  665c18b  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665c191  lock dec dword ptr [rsi+0xC]
  665c195  jne short 0x665C1A7      ; -> loc_665c1a7
  665c197  mov rax,[rsi]
  665c19a  mov rax,[rax+8]
  665c19e  mov rcx,rsi
  665c1a1  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040

### Phase 23 — loc_665c1a7..0x665c1b4  [V]
; from rdis work/rdis/665bd31.txt lines 257-262
  665c1a7  mov rdi,[rbp+0x58]
  665c1ab  test rdi,rdi
  665c1ae  je short 0x665C1FB       ; -> loc_665c1fb
  665c1b0  mov rbx,[rbp+0x60]
  665c1b4  jmp short 0x665C1BA      ; -> loc_665c1ba

### Phase 24 — loc_665c1b6..0x665c1bd  [V]
; from rdis work/rdis/665bd31.txt lines 264-269
  665c1b6  add rdi,0x28
  665c1ba  cmp rdi,rbx
  665c1bd  je short 0x665C1FB       ; -> loc_665c1fb

### Phase 25 — 0x665c1bf..0x665c1e3  [V]
; from rdis work/rdis/665bd31.txt lines 270-282
  665c1bf  cmp byte ptr [rdi+0x18],2
  665c1c3  jne short 0x665C1B6      ; -> loc_665c1b6
  665c1c5  mov rsi,[rdi+8]
  665c1c9  test rsi,rsi
  665c1cc  je short 0x665C1B6       ; -> loc_665c1b6
  665c1ce  lock dec dword ptr [rsi+8]
  665c1d2  jne short 0x665C1B6      ; -> loc_665c1b6
  665c1d4  mov rax,[rsi]
  665c1d7  mov rax,[rax]
  665c1da  mov rcx,rsi
  665c1dd  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665c1e3  lock dec dword ptr [rsi+0xC]

### Phase 26 — 0x665c1e7..0x665c1f9  [V]
; from rdis work/rdis/665bd31.txt lines 282-287
  665c1e7  jne short 0x665C1B6      ; -> loc_665c1b6
  665c1e9  mov rax,[rsi]
  665c1ec  mov rax,[rax+8]
  665c1f0  mov rcx,rsi
  665c1f3  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665c1f9  jmp short 0x665C1B6      ; -> loc_665c1b6

### Phase 27 — loc_665c1fb..0x665c244  [V]
; from rdis work/rdis/665bd31.txt lines 289-305
  665c1fb  cmp byte ptr [rbp+0x520],1
  665c202  jne 0x665CF64            ; -> loc_665cf64
  665c208  mov rcx,[rbp+0x4E0]
  665c20f  test rcx,rcx
  665c212  je 0x665CF64             ; -> loc_665cf64
  665c218  mov rdx,[rbp+0x4F0]
  665c21f  sub rdx,rcx
  665c222  cmp rdx,0x1000
  665c229  jb short 0x665C247       ; -> loc_665c247
  665c22b  mov rax,[rcx-8]
  665c22f  add rcx,0xFFFFFFFFFFFFFFF8
  665c233  sub rcx,rax
  665c236  cmp rcx,0x20
  665c23a  jae 0x665D43A            ; -> loc_665d43a
  665c240  or rdx,0x27
  665c244  mov rcx,rax

### Phase 28 — loc_665c247..0x665c26f  [V]  (main-range tail; end exclusive 0x665c272)
; from rdis work/rdis/665bd31.txt lines 307-316
  665c247  call 0xE935700           ; -> sub_e935700
  665c24c  jmp 0x665CF64            ; -> loc_665cf64
  665c251  xor r11d,r11d
  665c254  mov rdi,[rbp+0x208]
  665c25b  mov [rbp+0x4A0],rdi
  665c262  mov [rbp+0x4A8],r11
  665c269  mov [rbp+0x4B0],cl
  665c26f  mov rcx,[rbp+0x230]

-- END MAIN RANGE (exclusive end 0x665c272) --


## PHASES — cold range 0x665cf64..0x665d7e5  (exclusive end 0x665d7e5)

### Cold Phase 1 — 0x665cf64..0x665cfcc  [V]
; from rdis work/rdis/665cf64.txt lines 2-21
  665cf64  mov rsi,[rbp+0x28]
  665cf68  jmp 0x665D124        ; -> loc_665d124
  665cf6d  xor r11d,r11d
  665cf70  mov rdi,[rbp+0x508]
  665cf77  mov [rbp+0x4A0],rdi
  665cf7e  mov [rbp+0x4A8],r11
  665cf85  mov [rbp+0x4B0],cl
  665cf8b  mov rcx,[rbp+0x530]
  665cf92  mov [rbp+0x4C8],rcx
  665cf99  movaps xmm0,[rbp+0x520]
  665cfa0  movups [rbp+0x4B8],xmm0
  665cfa7  mov ecx,0x9D0
  665cfac  add rcx,[rsi+0x10]
  665cfb0  mov [rsp+0x28],rax
  665cfb5  mov [rsp+0x20],r10
  665cfba  call 0x67B40D0       ; -> sub_67b40d0
  665cfbf  nop
  665cfc0  lea rcx,[rbp+0x340]
  665cfc7  call 0x66A9AD0       ; -> sub_66a9ad0
  665cfcc  jmp short 0x665D02D  ; -> loc_665d02d

### Cold Phase 2 — 0x665cfce..0x665d028  [V]
; from rdis work/rdis/665cf64.txt lines 22-38
  665cfce  xor r11d,r11d
  665cfd1  mov rdi,[rbp+0x508]
  665cfd8  mov [rbp+0x4A0],rdi
  665cfdf  mov [rbp+0x4A8],r11
  665cfe6  mov [rbp+0x4B0],cl
  665cfec  mov rcx,[rbp+0x530]
  665cff3  mov [rbp+0x4C8],rcx
  665cffa  movaps xmm0,[rbp+0x520]
  665d001  movups [rbp+0x4B8],xmm0
  665d008  mov ecx,0x9D0
  665d00d  add rcx,[rsi+0x10]
  665d011  mov [rsp+0x28],rax
  665d016  mov [rsp+0x20],r10
  665d01b  call 0x67B47D0       ; -> sub_67b47d0
  665d020  nop
  665d021  lea rcx,[rbp+0x340]
  665d028  call 0x66A9AD0       ; -> sub_66a9ad0

### Cold Phase 3 — loc_665d02d..0x665d071  [V]
; from rdis work/rdis/665cf64.txt lines 40-59
  665d02d  cmp byte ptr [rbp+0x220],1
  665d034  jne short 0x665D076  ; -> loc_665d076
  665d036  mov rcx,[rbp+0x1E0]
  665d03d  test rcx,rcx
  665d040  je short 0x665D076   ; -> loc_665d076
  665d042  mov rdx,[rbp+0x1F0]
  665d049  sub rdx,rcx
  665d04c  cmp rdx,0x1000
  665d053  jb short 0x665D071   ; -> loc_665d071
  665d055  mov rax,[rcx-8]
  665d059  add rcx,0xFFFFFFFFFFFFFFF8
  665d05d  sub rcx,rax
  665d060  cmp rcx,0x20
  665d064  jae 0x665D43A        ; -> loc_665d43a
  665d06a  or rdx,0x27
  665d06e  mov rcx,rax
  665d071  call 0xE935700       ; -> sub_e935700

### Cold Phase 4 — loc_665d076..0x665d0bd  [V]
; from rdis work/rdis/665cf64.txt lines 61-80
  665d076  cmp byte ptr [rbp+0x538],1
  665d07d  jne 0x665D11D        ; -> loc_665d11d
  665d083  cmp byte ptr [rbp+0x518],3
  665d08a  jne short 0x665D0C3  ; -> loc_665d0c3
  665d08c  mov rsi,[rbp+0x510]
  665d093  test rsi,rsi
  665d096  je short 0x665D0C3   ; -> loc_665d0c3
  665d098  lock dec dword ptr [rsi+8]
  665d09c  jne short 0x665D0C3  ; -> loc_665d0c3
  665d09e  mov rax,[rsi]
  665d0a1  mov rax,[rax]
  665d0a4  mov rcx,rsi
  665d0a7  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665d0ad  lock dec dword ptr [rsi+0xC]
  665d0b1  jne short 0x665D0C3  ; -> loc_665d0c3
  665d0b3  mov rax,[rsi]
  665d0b6  mov rax,[rax+8]
  665d0ba  mov rcx,rsi
  665d0bd  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040

### Cold Phase 5 — loc_665d0c3..0x665d11b  [V]
; from rdis work/rdis/665cf64.txt lines 82-112
  665d0c3  mov rdi,[rbp+0x4E8]
  665d0ca  test rdi,rdi
  665d0cd  je short 0x665D11D   ; -> loc_665d11d
  665d0cf  mov rbx,[rbp+0x4F0]
  665d0d6  jmp short 0x665D0DC  ; -> loc_665d0dc
  665d0d8  add rdi,0x28
  665d0dc  cmp rdi,rbx
  665d0df  je short 0x665D11D   ; -> loc_665d11d
  665d0e1  cmp byte ptr [rdi+0x18],2
  665d0e5  jne short 0x665D0D8  ; -> loc_665d0d8
  665d0e7  mov rsi,[rdi+8]
  665d0eb  test rsi,rsi
  665d0ee  je short 0x665D0D8   ; -> loc_665d0d8
  665d0f0  lock dec dword ptr [rsi+8]
  665d0f4  jne short 0x665D0D8  ; -> loc_665d0d8
  665d0f6  mov rax,[rsi]
  665d0f9  mov rax,[rax]
  665d0fc  mov rcx,rsi
  665d0ff  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665d105  lock dec dword ptr [rsi+0xC]
  665d109  jne short 0x665D0D8  ; -> loc_665d0d8
  665d10b  mov rax,[rsi]
  665d10e  mov rax,[rax+8]
  665d112  mov rcx,rsi
  665d115  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665d11b  jmp short 0x665D0D8  ; -> loc_665d0d8

### Cold Phase 6 — loc_665d11d..0x665d14e  [V]
; from rdis work/rdis/665cf64.txt lines 114-131
  665d11d  mov rsi,[rbp+0x338]
  665d124  test rsi,rsi
  665d127  je short 0x665D154   ; -> loc_665d154
  665d129  lock dec dword ptr [rsi+8]
  665d12d  jne short 0x665D154  ; -> loc_665d154
  665d12f  mov rax,[rsi]
  665d132  mov rax,[rax]
  665d135  mov rcx,rsi
  665d138  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
  665d13e  lock dec dword ptr [rsi+0xC]
  665d142  jne short 0x665D154  ; -> loc_665d154
  665d144  mov rax,[rsi]
  665d147  mov rax,[rax+8]
  665d14b  mov rcx,rsi
  665d14e  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040

### Cold Phase 7 — loc_665d154..0x665d19d  [V]
; from rdis work/rdis/665cf64.txt lines 133-150
  665d154  movaps xmm6,[rbp+0x550]
  665d15b  movaps xmm7,[rbp+0x560]
  665d162  movaps xmm8,[rbp+0x570]
  665d16a  movaps xmm9,[rbp+0x580]
  665d172  movaps xmm10,[rbp+0x590]
  665d17a  movaps xmm11,[rbp+0x5A0]
  665d182  movaps xmm12,[rbp+0x5B0]
  665d18a  add rsp,0x648
  665d191  pop rbx
  665d192  pop rdi
  665d193  pop rsi
  665d194  pop r12
  665d196  pop r13
  665d198  pop r14
  665d19a  pop r15
  665d19c  pop rbp
  665d19d  ret

-- COLD RANGE TAIL 0x665d19e..0x665d7e4 (exclusive end 0x665d7e5) --

### Cold Tail Phase 1 — 0x665d19e..0x665d1d5  [V]
; from rdis work/rdis/665cf64.txt lines 151-165
  665d19e  mov ecx,0x20
  665d1a3  call 0x9BC830         ; -> sub_9bc830
  665d1a8  jmp 0x66564FF        ; -> sub_66564ff
  665d1ad  lea rcx,[rdi+0x27]
  665d1b1  call 0x9BC830         ; -> sub_9bc830
  665d1b6  nop
  665d1b7  jmp 0x6657223        ; -> sub_6657223
  665d1bc  lea rcx,[r13+0x27]
  665d1c0  call 0x9BC830         ; -> sub_9bc830
  665d1c5  nop
  665d1c6  jmp 0x66572E2        ; -> sub_66572e2
  665d1cb  mov rcx,[rbp+0x48]
  665d1cf  call 0x9BC830         ; -> sub_9bc830
  665d1d4  nop
  665d1d5  jmp 0x66573AF        ; -> sub_66573af

### Cold Tail Phase 2 — 0x665d1da..0x665d23d  [V]  (LegacyCubemap)
; from rdis work/rdis/665cf64.txt lines 166-182
  665d1da  lea rcx,[0x129F9C50]         ; [data_129f9c50]
  665d1e1  call 0xE938CB0               ; -> sub_e938cb0
  665d1e6  cmp dword ptr [0x129F9C50],0xFFFFFFFF   ; [data_129f9c50]
  665d1ed  jne 0x66561F1                ; -> sub_66561f1
  665d1f3  xorps xmm0,xmm0
  665d1f6  movaps [rbp+0x120],xmm0
  665d1fd  lea rax,[0xF57DBCE]          ; [data_f57dbce] "LegacyCubemap"
  665d204  mov [rbp+0x1D0],rax
  665d20b  mov qword ptr [rbp+0x1D8],0xD
  665d216  lea rcx,[0x129F9C40]         ; [data_129f9c40]
  665d21d  lea rdx,[rbp+0x1D0]
  665d224  lea r8,[rbp+0x120]
  665d22b  call 0x5668AC0               ; -> sub_5668ac0
  665d230  nop
  665d231  lea rcx,[0x129F9C50]         ; [data_129f9c50]
  665d238  call 0xE938D70               ; -> sub_e938d70
  665d23d  jmp 0x66561F1                ; -> sub_66561f1

### Cold Tail Phase 3 — 0x665d242..0x665d2a5  [V]  (LegacyCubemapForwardPBR)
; from rdis work/rdis/665cf64.txt lines 183-199
  665d242  lea rcx,[0x129F9C68]         ; [data_129f9c68]
  665d249  call 0xE938CB0               ; -> sub_e938cb0
  665d24e  cmp dword ptr [0x129F9C68],0xFFFFFFFF   ; [data_129f9c68]
  665d255  jne 0x6656216                ; -> sub_6656216
  665d25b  xorps xmm0,xmm0
  665d25e  movaps [rbp+0x310],xmm0
  665d265  lea rax,[0xF7CA1F7]          ; [data_f7ca1f7] "LegacyCubemapForwardPBR"
  665d26c  mov [rbp+0x320],rax
  665d273  mov qword ptr [rbp+0x328],0x17
  665d27e  lea rcx,[0x129F9C58]         ; [data_129f9c58]
  665d285  lea rdx,[rbp+0x320]
  665d28c  lea r8,[rbp+0x310]
  665d293  call 0x5668AC0               ; -> sub_5668ac0
  665d298  nop
  665d299  lea rcx,[0x129F9C68]         ; [data_129f9c68]
  665d2a0  call 0xE938D70               ; -> sub_e938d70
  665d2a5  jmp 0x6656216                ; -> sub_6656216

### Cold Tail Phase 4 — 0x665d2aa..0x665d2e9  [V]
; from rdis work/rdis/665cf64.txt lines 200-210
  665d2aa  lea rcx,[0x129F9D00]         ; [data_129f9d00]
  665d2b1  call 0xE938CB0               ; -> sub_e938cb0
  665d2b6  cmp dword ptr [0x129F9D00],0xFFFFFFFF   ; [data_129f9d00]
  665d2bd  jne 0x6656C32                ; -> sub_6656c32
  665d2c3  xorps xmm0,xmm0
  665d2c6  movaps [rbp+0x1D0],xmm0
  665d2cd  mov rax,[rbp+0x130]
  665d2d4  cmp qword ptr [rbp+0x138],0x10
  665d2dc  jb 0x665DAD4                 ; -> loc_665dad4
  665d2e2  mov rcx,[rbp+0x120]
  665d2e9  jmp 0x665DADB                ; -> loc_665dadb

### Cold Tail Phase 5 — 0x665d2ee..0x665d351  [V]
; from rdis work/rdis/665cf64.txt lines 211-227
  665d2ee  lea rcx,[0x129F9F28]         ; [data_129f9f28]
  665d2f5  call 0xE938CB0               ; -> sub_e938cb0
  665d2fa  cmp dword ptr [0x129F9F28],0xFFFFFFFF   ; [data_129f9f28]
  665d301  jne 0x6656713                ; -> sub_6656713
  665d307  xorps xmm0,xmm0
  665d30a  movaps [rbp+0x1D0],xmm0
  665d311  lea rax,[0xF51B964]          ; [data_f51b964]
  665d318  mov [rbp+0x310],rax
  665d31f  mov qword ptr [rbp+0x318],3
  665d32a  lea rcx,[0x129F9F18]         ; [data_129f9f18]
  665d331  lea rdx,[rbp+0x310]
  665d338  lea r8,[rbp+0x1D0]
  665d33f  call 0x5668AC0               ; -> sub_5668ac0
  665d344  nop
  665d345  lea rcx,[0x129F9F28]         ; [data_129f9f28]
  665d34c  call 0xE938D70               ; -> sub_e938d70
  665d351  jmp 0x6656713                ; -> sub_6656713

### Cold Tail Phase 6 — 0x665d356..0x665d3b9  [V]
; from rdis work/rdis/665cf64.txt lines 228-244
  665d356  lea rcx,[0x129F9F60]         ; [data_129f9f60]
  665d35d  call 0xE938CB0               ; -> sub_e938cb0
  665d362  cmp dword ptr [0x129F9F60],0xFFFFFFFF   ; [data_129f9f60]
  665d369  jne 0x6656837                ; -> sub_6656837
  665d36f  xorps xmm0,xmm0
  665d372  movaps [rbp+0x170],xmm0
  665d379  lea rax,[0xF54C3E1]          ; [data_f54c3e1] "Stars"
  665d380  mov [rbp+0x120],rax
  665d387  mov qword ptr [rbp+0x128],5
  665d392  lea rcx,[0x129F9F50]         ; [data_129f9f50]
  665d399  lea rdx,[rbp+0x120]
  665d3a0  lea r8,[rbp+0x170]
  665d3a7  call 0x5668AC0               ; -> sub_5668ac0
  665d3ac  nop
  665d3ad  lea rcx,[0x129F9F60]         ; [data_129f9f60]
  665d3b4  call 0xE938D70               ; -> sub_e938d70
  665d3b9  jmp 0x6656837                ; -> sub_6656837

### Cold Tail Phase 7 — 0x665d3be..0x665d435  [V]
; from rdis work/rdis/665cf64.txt lines 245-267
  665d3be  lea rcx,[0x129F9F78]         ; [data_129f9f78]
  665d3c5  call 0xE938CB0               ; -> sub_e938cb0
  665d3ca  cmp dword ptr [0x129F9F78],0xFFFFFFFF   ; [data_129f9f78]
  665d3d1  jne 0x665685C                ; -> sub_665685c
  665d3d7  xorps xmm0,xmm0
  665d3da  movaps [rbp+0x1D0],xmm0
  665d3e1  lea rax,[0xF7CA19E]          ; [data_f7ca19e] "StarsForwardPBR"
  665d3e8  mov [rbp+0x310],rax
  665d3ef  mov qword ptr [rbp+0x318],0xF
  665d3fa  lea rcx,[0x129F9F68]         ; [data_129f9f68]
  665d401  lea rdx,[rbp+0x310]
  665d408  lea r8,[rbp+0x1D0]
  665d40f  call 0x5668AC0               ; -> sub_5668ac0
  665d414  nop
  665d415  lea rcx,[0x129F9F78]         ; [data_129f9f78]
  665d41c  call 0xE938D70               ; -> sub_e938d70
  665d421  jmp 0x665685C                ; -> sub_665685c
  665d426  call 0x1166E0                ; -> sub_1166e0
  665d42b  nop
  665d42c  mov rcx,r15
  665d42f  call 0x9BC830                ; -> sub_9bc830
  665d434  nop
  665d435  jmp 0x665C83D                ; -> sub_665c83d

### Cold Tail Phase 8 — loc_665d43a..0x665d484  [V]
; from rdis work/rdis/665cf64.txt lines 269-284
  665d43a  mov qword ptr [rsp+0x20],0
  665d443  xor ecx,ecx
  665d445  xor edx,edx
  665d447  xor r8d,r8d
  665d44a  xor r9d,r9d
  665d44d  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]
  665d453  lea rcx,[0x129C13C0]         ; [data_129c13c0]
  665d45a  call 0xE938CB0               ; -> sub_e938cb0
  665d45f  cmp dword ptr [0x129C13C0],0xFFFFFFFF   ; [data_129c13c0]
  665d466  jne 0x6656306                ; -> sub_6656306
  665d46c  lea rcx,[0x4E05030]          ; [sub_4e05030]
  665d473  call 0xE935740               ; -> sub_e935740
  665d478  lea rcx,[0x129C13C0]         ; [data_129c13c0]
  665d47f  call 0xE938D70               ; -> sub_e938d70
  665d484  jmp 0x6656306                ; -> sub_6656306

### Cold Tail Phase 9 — 0x665d489..0x665d50a  [V]
; from rdis work/rdis/665cf64.txt lines 285-308
  665d489  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d490  call 0xE938CB0               ; -> sub_e938cb0
  665d495  cmp dword ptr [0x129CA5E0],0xFFFFFFFF   ; [data_129ca5e0]
  665d49c  jne 0x6656B6F                ; -> sub_6656b6f
  665d4a2  lea rcx,[0x129CA568]         ; [data_129ca568]
  665d4a9  call 0x567DB00               ; -> sub_567db00
  665d4ae  nop
  665d4af  lea rcx,[0x567DBA0]          ; [sub_567dba0]
  665d4b6  call 0xE935740               ; -> sub_e935740
  665d4bb  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d4c2  call 0xE938D70               ; -> sub_e938d70
  665d4c7  jmp 0x6656B6F                ; -> sub_6656b6f
  665d4cc  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d4d3  call 0xE938CB0               ; -> sub_e938cb0
  665d4d8  cmp dword ptr [0x129CA5E0],0xFFFFFFFF   ; [data_129ca5e0]
  665d4df  jne 0x66567A1                ; -> sub_66567a1
  665d4e5  lea rcx,[0x129CA568]         ; [data_129ca568]
  665d4ec  call 0x567DB00               ; -> sub_567db00
  665d4f1  nop
  665d4f2  lea rcx,[0x567DBA0]          ; [sub_567dba0]
  665d4f9  call 0xE935740               ; -> sub_e935740
  665d4fe  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d505  call 0xE938D70               ; -> sub_e938d70
  665d50a  jmp 0x66567A1                ; -> sub_66567a1

### Cold Tail Phase 10 — 0x665d50f..0x665d590  [V]
; from rdis work/rdis/665cf64.txt lines 309-332
  665d50f  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d516  call 0xE938CB0               ; -> sub_e938cb0
  665d51b  cmp dword ptr [0x129CA5E0],0xFFFFFFFF   ; [data_129ca5e0]
  665d522  jne 0x665690F                ; -> sub_665690f
  665d528  lea rcx,[0x129CA568]         ; [data_129ca568]
  665d52f  call 0x567DB00               ; -> sub_567db00
  665d534  nop
  665d535  lea rcx,[0x567DBA0]          ; [sub_567dba0]
  665d53c  call 0xE935740               ; -> sub_e935740
  665d541  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d548  call 0xE938D70               ; -> sub_e938d70
  665d54d  jmp 0x665690F                ; -> sub_665690f
  665d552  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d559  call 0xE938CB0               ; -> sub_e938cb0
  665d55e  cmp dword ptr [0x129CA5E0],0xFFFFFFFF   ; [data_129ca5e0]
  665d565  jne 0x6656CD7                ; -> sub_6656cd7
  665d56b  lea rcx,[0x129CA568]         ; [data_129ca568]
  665d572  call 0x567DB00               ; -> sub_567db00
  665d577  nop
  665d578  lea rcx,[0x567DBA0]          ; [sub_567dba0]
  665d57f  call 0xE935740               ; -> sub_e935740
  665d584  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d58b  call 0xE938D70               ; -> sub_e938d70
  665d590  jmp 0x6656CD7                ; -> sub_6656cd7

### Cold Tail Phase 11 — 0x665d595..0x665d5f8  [V]  (SunMoon)
; from rdis work/rdis/665cf64.txt lines 333-349
  665d595  lea rcx,[0x129F9FA0]         ; [data_129f9fa0]
  665d59c  call 0xE938CB0               ; -> sub_e938cb0
  665d5a1  cmp dword ptr [0x129F9FA0],0xFFFFFFFF   ; [data_129f9fa0]
  665d5a8  jne 0x6656554                ; -> sub_6656554
  665d5ae  xorps xmm0,xmm0
  665d5b1  movaps [rbp+0x1D0],xmm0
  665d5b8  lea rax,[0xF584D1D]          ; [data_f584d1d] "SunMoon"
  665d5bf  mov [rbp+0x310],rax
  665d5c6  mov qword ptr [rbp+0x318],7
  665d5d1  lea rcx,[0x129F9F90]         ; [data_129f9f90]
  665d5d8  lea rdx,[rbp+0x310]
  665d5df  lea r8,[rbp+0x1D0]
  665d5e6  call 0x5668AC0               ; -> sub_5668ac0
  665d5eb  nop
  665d5ec  lea rcx,[0x129F9FA0]         ; [data_129f9fa0]
  665d5f3  call 0xE938D70               ; -> sub_e938d70
  665d5f8  jmp 0x6656554                ; -> sub_6656554

### Cold Tail Phase 12 — 0x665d5fd..0x665d660  [V]  (SunMoonForwardPBR)
; from rdis work/rdis/665cf64.txt lines 350-366
  665d5fd  lea rcx,[0x129F9FB8]         ; [data_129f9fb8]
  665d604  call 0xE938CB0               ; -> sub_e938cb0
  665d609  cmp dword ptr [0x129F9FB8],0xFFFFFFFF   ; [data_129f9fb8]
  665d610  jne 0x6656579                ; -> sub_6656579
  665d616  xorps xmm0,xmm0
  665d619  movaps [rbp+0x320],xmm0
  665d620  lea rax,[0xF7CA226]          ; [data_f7ca226] "SunMoonForwardPBR"
  665d627  mov [rbp+0x330],rax
  665d62e  mov qword ptr [rbp+0x338],0x11
  665d639  lea rcx,[0x129F9FA8]         ; [data_129f9fa8]
  665d640  lea rdx,[rbp+0x330]
  665d647  lea r8,[rbp+0x320]
  665d64e  call 0x5668AC0               ; -> sub_5668ac0
  665d653  nop
  665d654  lea rcx,[0x129F9FB8]         ; [data_129f9fb8]
  665d65b  call 0xE938D70               ; -> sub_e938d70
  665d660  jmp 0x6656579                ; -> sub_6656579

### Cold Tail Phase 13 — 0x665d665..0x665d676  [V]
; from rdis work/rdis/665cf64.txt lines 367-372
  665d665  call 0x75740                 ; -> sub_75740
  665d66a  nop
  665d66b  call 0x75740                 ; -> sub_75740
  665d670  nop
  665d671  call 0x75740                 ; -> sub_75740
  665d676  nop

### Cold Tail Phase 14 — 0x665d677..0x665d6da  [V]  (Cubemap)
; from rdis work/rdis/665cf64.txt lines 373-389
  665d677  lea rcx,[0x129F9BC8]         ; [data_129f9bc8]
  665d67e  call 0xE938CB0               ; -> sub_e938cb0
  665d683  cmp dword ptr [0x129F9BC8],0xFFFFFFFF   ; [data_129f9bc8]
  665d68a  jne 0x665633E                ; -> sub_665633e
  665d690  xorps xmm0,xmm0
  665d693  movaps [rbp+0x120],xmm0
  665d69a  lea rax,[0xF2BE568]          ; [data_f2be568] "Cubemap"
  665d6a1  mov [rbp+0x1D0],rax
  665d6a8  mov qword ptr [rbp+0x1D8],7
  665d6b3  lea rcx,[0x129F9BB8]         ; [data_129f9bb8]
  665d6ba  lea rdx,[rbp+0x1D0]
  665d6c1  lea r8,[rbp+0x120]
  665d6c8  call 0x5668AC0               ; -> sub_5668ac0
  665d6cd  nop
  665d6ce  lea rcx,[0x129F9BC8]         ; [data_129f9bc8]
  665d6d5  call 0xE938D70               ; -> sub_e938d70
  665d6da  jmp 0x665633E                ; -> sub_665633e

### Cold Tail Phase 15 — 0x665d6df..0x665d742  [V]  (CubemapHDRi)
; from rdis work/rdis/665cf64.txt lines 390-406
  665d6df  lea rcx,[0x129F9BE0]         ; [data_129f9be0]
  665d6e6  call 0xE938CB0               ; -> sub_e938cb0
  665d6eb  cmp dword ptr [0x129F9BE0],0xFFFFFFFF   ; [data_129f9be0]
  665d6f2  jne 0x6656363                ; -> sub_6656363
  665d6f8  xorps xmm0,xmm0
  665d6fb  movaps [rbp+0x310],xmm0
  665d702  lea rax,[0xF2BE588]          ; [data_f2be588] "CubemapHDRi"
  665d709  mov [rbp+0x320],rax
  665d710  mov qword ptr [rbp+0x328],0xB
  665d71b  lea rcx,[0x129F9BD0]         ; [data_129f9bd0]
  665d722  lea rdx,[rbp+0x320]
  665d729  lea r8,[rbp+0x310]
  665d730  call 0x5668AC0               ; -> sub_5668ac0
  665d735  nop
  665d736  lea rcx,[0x129F9BE0]         ; [data_129f9be0]
  665d73d  call 0xE938D70               ; -> sub_e938d70
  665d742  jmp 0x6656363                ; -> sub_6656363

### Cold Tail Phase 16 — 0x665d747..0x665d79d  [V]
; from rdis work/rdis/665cf64.txt lines 407-421
  665d747  lea rcx,[0x129F9C28]         ; [data_129f9c28]
  665d74e  call 0xE938CB0               ; -> sub_e938cb0
  665d753  cmp dword ptr [0x129F9C28],0xFFFFFFFF   ; [data_129f9c28]
  665d75a  jne 0x6656388                ; -> sub_6656388
  665d760  mov dword ptr [rbp+0x340],0
  665d76a  lea rcx,[0x129F9BE8]         ; [data_129f9be8]
  665d771  lea rdx,[rbp+0x340]
  665d778  lea r8,[rbp+0x1E0]
  665d77f  call 0x9B020                 ; -> sub_9b020
  665d784  nop
  665d785  lea rcx,[0x673CFE0]          ; [sub_673cfe0]
  665d78c  call 0xE935740               ; -> sub_e935740
  665d791  lea rcx,[0x129F9C28]         ; [data_129f9c28]
  665d798  call 0xE938D70               ; -> sub_e938d70
  665d79d  jmp 0x6656388                ; -> sub_6656388

### Cold Tail Phase 17 — 0x665d7a2..0x665d7e0  [V]  (end exclusive 0x665d7e5)
; from rdis work/rdis/665cf64.txt lines 422-433
  665d7a2  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d7a9  call 0xE938CB0               ; -> sub_e938cb0
  665d7ae  cmp dword ptr [0x129CA5E0],0xFFFFFFFF   ; [data_129ca5e0]
  665d7b5  jne 0x6656626                ; -> sub_6656626
  665d7bb  lea rcx,[0x129CA568]         ; [data_129ca568]
  665d7c2  call 0x567DB00               ; -> sub_567db00
  665d7c7  nop
  665d7c8  lea rcx,[0x567DBA0]          ; [sub_567dba0]
  665d7cf  call 0xE935740               ; -> sub_e935740
  665d7d4  lea rcx,[0x129CA5E0]         ; [data_129ca5e0]
  665d7db  call 0xE938D70               ; -> sub_e938d70
  665d7e0  jmp 0x6656626                ; -> sub_6656626

-- END COLD RANGE (exclusive end 0x665d7e5) --




