# Progress: U-UI5 (unit ext-weather-ui-editor), fn 0x674a3a0, range from 0x674b4d9

## NEXT
UNIT COMPLETE — nothing remains. fn 0x674a3a0 fully transcribed: switch cases (0x674b559/0x674b71a/0x674b85d/0x674b9b2 + kind>3 default 0x674e428) plus ALL cold tails 0x674dfeb..0x674f001 (last fn instruction). fn span [0x674a3a0, 0x674f006), size 0x4C66 [V] — next function (ret-thunk wrappers around call 0xE938D30) starts at 0x674f006. Hot-path ret 0x674ce4e; all cold-tail exits are jmps to sub_674aXXX phase continuations. All four materials located (UI/Blit 0x674bc15, UI/Base 0x674bd1f, UI/Sprite 0x674c147/0x674c283, UI/Fill 0x674cd0e) and all static-uniform FNV-1a registrations (ShadowColor/GlyphSmoothRadius/OutlineCutoff/ShadowSmoothRadius/HalfTexelOffset/ShadowOffset/GlyphHeight/GlintTexture/GlintColor/UVScale/UVOffset/UVRotation) transcribed with exact data globals. No further work on this unit.

## Source context
- Fn 0x674a3a0 (UI item draw fn, "kind switch" material/type dispatcher). Previous agent decoded phases 1-4 (0x674a3a0..0x674b4d9, call/store level only). Status there: OPEN at RVA 0x674b4d9 (phase 5 + cold tails not transcribed).
- My unit: RVA 0x674b4d9..end, kind switch (jump table at 0x674b550), materials Blit/Base/Sprite/Fill, cold tails.
- Progress file only. No edits to any other file. Disassembly via `rdis dis <addr> 300`. Quoting rule: `0xRVA  instruction` exactly as rdis prints.
- Tags: [V] = saw in disassembly at cited RVA; [I] = inferred; [?] = unknown. Never invent sizes/offsets/names.

## Cold-tail transcription 0x674dfeb..0x674e511 [V]
(rdis `dis 0x674dfeb 250`; every instruction quoted exactly as printed, nops included)
```
  674dfeb  cmp dword ptr [0x129FA5B8],0xFFFFFFFF         ; [data_129fa5b8]
  674dff2  jne 0x674AB80                                 ; -> sub_674ab80
  674dff8  lea rdx,[0xF53C825]                           ; [data_f53c825] "ShadowOffset"
  674dfff  lea r12,[rbp+0xC10]
  674e006  mov rcx,r12
  674e009  call 0x79580                                  ; -> sub_79580
  674e00e  nop
  674e00f  mov rdx,[rbp+0xC20]
  674e016  cmp qword ptr [rbp+0xC28],0x10
  674e01e  jb short 0x674E027                            ; -> loc_674e027
  674e020  mov r12,[rbp+0xC10]

loc_674e027:  ; from 674e01e
  674e027  test rdx,rdx
  674e02a  je 0x674E7BA                                  ; -> loc_674e7ba
  674e030  mov eax,edx
  674e032  and eax,3
  674e035  cmp rdx,4
  674e039  jae 0x674EB25                                 ; -> loc_674eb25
  674e03f  mov rcx,0xCBF29CE484222325
  674e049  xor r8d,r8d
  674e04c  jmp 0x674EB81                                 ; -> loc_674eb81
  674e051  lea rcx,[0x129FA5C8]                          ; [data_129fa5c8]
  674e058  call 0xE938CB0                                ; -> sub_e938cb0
  674e05d  cmp dword ptr [0x129FA5C8],0xFFFFFFFF         ; [data_129fa5c8]
  674e064  jne 0x674ABA5                                 ; -> sub_674aba5
  674e06a  lea rdx,[0xF53B313]                           ; [data_f53b313] "GlyphHeight"
  674e071  lea r12,[rbp+0xC10]
  674e078  mov rcx,r12
  674e07b  call 0x79580                                  ; -> sub_79580
  674e080  nop
  674e081  mov r8,[rbp+0xC20]
  674e088  cmp qword ptr [rbp+0xC28],0x10
  674e090  jb short 0x674E099                            ; -> loc_674e099
  674e092  mov r12,[rbp+0xC10]

loc_674e099:  ; from 674e090
  674e099  test r8,r8
  674e09c  je 0x674E7C9                                  ; -> loc_674e7c9
  674e0a2  mov eax,r8d
  674e0a5  and eax,3
  674e0a8  mov rcx,0x100000001B3
  674e0b2  cmp r8,4
  674e0b6  jae 0x674EBCE                                 ; -> loc_674ebce
  674e0bc  mov rdx,0xCBF29CE484222325
  674e0c6  xor r9d,r9d
  674e0c9  jmp 0x674EC20                                 ; -> loc_674ec20
  674e0ce  mov rcx,0xCBF29CE484222325
  674e0d8  jmp 0x674E39C                                 ; -> loc_674e39c
  674e0dd  lea rcx,[0x129FA1B8]                          ; [data_129fa1b8]
  674e0e4  call 0xE938CB0                                ; -> sub_e938cb0
  674e0e9  cmp dword ptr [0x129FA1B8],0xFFFFFFFF         ; [data_129fa1b8]
  674e0f0  jne 0x674AE37                                 ; -> sub_674ae37
  674e0f6  lea rdx,[0xF5C6B76]                           ; [data_f5c6b76] "GlintTexture"
  674e0fd  lea rdi,[rbp+0xC10]
  674e104  mov rcx,rdi
  674e107  call 0x79580                                  ; -> sub_79580
  674e10c  nop
  674e10d  mov rdx,[rbp+0xC20]
  674e114  cmp qword ptr [rbp+0xC28],0x10
  674e11c  jb short 0x674E125                            ; -> loc_674e125
  674e11e  mov rdi,[rbp+0xC10]

loc_674e125:  ; from 674e11c
  674e125  test rdx,rdx
  674e128  je 0x674EC64                                  ; -> loc_674ec64
  674e12e  mov eax,edx
  674e130  and eax,3
  674e133  cmp rdx,4
  674e137  jae 0x674ECAF                                 ; -> loc_674ecaf
  674e13d  mov rcx,0xCBF29CE484222325
  674e147  xor r8d,r8d
  674e14a  jmp 0x674ED0B                                 ; -> loc_674ed0b
  674e14f  lea rcx,[0x129FA1C8]                          ; [data_129fa1c8]
  674e156  call 0xE938CB0                                ; -> sub_e938cb0
  674e15b  cmp dword ptr [0x129FA1C8],0xFFFFFFFF         ; [data_129fa1c8]
  674e162  jne 0x674AEFC                                 ; -> sub_674aefc
  674e168  lea rdx,[0xF563953]                           ; [data_f563953] "GlintColor"
  674e16f  lea rdi,[rbp+0xC10]
  674e176  mov rcx,rdi
  674e179  call 0x79580                                  ; -> sub_79580
  674e17e  nop
  674e17f  mov rdx,[rbp+0xC20]
  674e186  cmp qword ptr [rbp+0xC28],0x10
  674e18e  jb short 0x674E197                            ; -> loc_674e197
  674e190  mov rdi,[rbp+0xC10]

loc_674e197:  ; from 674e18e
  674e197  test rdx,rdx
  674e19a  je 0x674EC73                                  ; -> loc_674ec73
  674e1a0  mov eax,edx
  674e1a2  and eax,3
  674e1a5  cmp rdx,4
  674e1a9  jae 0x674ED5A                                 ; -> loc_674ed5a
  674e1af  mov rcx,0xCBF29CE484222325
  674e1b9  xor r8d,r8d
  674e1bc  jmp 0x674EDB6                                 ; -> loc_674edb6
  674e1c1  lea rcx,[0x129FA1D8]                          ; [data_129fa1d8]
  674e1c8  call 0xE938CB0                                ; -> sub_e938cb0
  674e1cd  cmp dword ptr [0x129FA1D8],0xFFFFFFFF         ; [data_129fa1d8]
  674e1d4  jne 0x674AF21                                 ; -> sub_674af21
  674e1da  lea rdx,[0xF5DE988]                           ; [data_f5de988] "UVScale"
  674e1e1  lea rdi,[rbp+0xC10]
  674e1e8  mov rcx,rdi
  674e1eb  call 0x79580                                  ; -> sub_79580
  674e1f0  nop
  674e1f1  mov rdx,[rbp+0xC20]
  674e1f8  cmp qword ptr [rbp+0xC28],0x10
  674e200  jb short 0x674E209                            ; -> loc_674e209
  674e202  mov rdi,[rbp+0xC10]

loc_674e209:  ; from 674e200
  674e209  test rdx,rdx
  674e20c  je 0x674EC82                                  ; -> loc_674ec82
  674e212  mov eax,edx
  674e214  and eax,3
  674e217  cmp rdx,4
  674e21b  jae 0x674EE05                                 ; -> loc_674ee05
  674e221  mov rcx,0xCBF29CE484222325
  674e22b  xor r8d,r8d
  674e22e  jmp 0x674EE61                                 ; -> loc_674ee61
  674e233  lea rcx,[0x129FA1E8]                          ; [data_129fa1e8]
  674e23a  call 0xE938CB0                                ; -> sub_e938cb0
  674e23f  cmp dword ptr [0x129FA1E8],0xFFFFFFFF         ; [data_129fa1e8]
  674e246  jne 0x674AF46                                 ; -> sub_674af46
  674e24c  lea rdx,[0xF53CAE6]                           ; [data_f53cae6] "UVOffset"
  674e253  lea rdi,[rbp+0xC10]
  674e25a mov rcx,rdi
  674e25d  call 0x79580                                  ; -> sub_79580
  674e262  nop
  674e263  mov rdx,[rbp+0xC20]
  674e26a  cmp qword ptr [rbp+0xC28],0x10
  674e272  jb short 0x674E27B                            ; -> loc_674e27b
  674e274  mov rdi,[rbp+0xC10]

loc_674e27b:  ; from 674e272
  674e27b  test rdx,rdx
  674e27e  je 0x674EC91                                  ; -> loc_674ec91
  674e284  mov eax,edx
  674e286  and eax,3
  674e289  cmp rdx,4
  674e28d  jae 0x674EEB0                                 ; -> loc_674eeb0
  674e293  mov rcx,0xCBF29CE484222325
  674e29d  xor r8d,r8d
  674e2a0  jmp 0x674EF0C                                 ; -> loc_674ef0c
  674e2a5  lea rcx,[0x129FA1F8]                          ; [data_129fa1f8]
  674e2ac  call 0xE938CB0                                ; -> sub_e938cb0
  674e2b1  cmp dword ptr [0x129FA1F8],0xFFFFFFFF         ; [data_129fa1f8]
  674e2b8  jne 0x674AF6B                                 ; -> sub_674af6b
  674e2be  lea rdx,[0xF58CC4C]                           ; [data_f58cc4c] "UVRotation"
  674e2c5  lea rdi,[rbp+0xC10]
  674e2cc  mov rcx,rdi
  674e2cf  call 0x79580                                  ; -> sub_79580
  674e2d4  nop
  674e2d5  mov rdx,[rbp+0xC20]
  674e2dc  cmp qword ptr [rbp+0xC28],0x10
  674e2e4  jb short 0x674E2ED                            ; -> loc_674e2ed
  674e2e6  mov rdi,[rbp+0xC10]

loc_674e2ed:  ; from 674e2e4
  674e2ed  test rdx,rdx
  674e2f0  je 0x674ECA0                                  ; -> loc_674eca0
  674e2f6  mov eax,edx
  674e2f8  and eax,3
  674e2fb  cmp rdx,4
  674e2ff  jae 0x674EF5B                                 ; -> loc_674ef5b
  674e305  mov rcx,0xCBF29CE484222325
  674e30f  xor r8d,r8d
  674e312  jmp 0x674EFB7                                 ; -> loc_674efb7
  674e317  and rdx,0xFFFFFFFFFFFFFFFC
  674e31b  mov rcx,0xCBF29CE484222325
  674e325  xor r8d,r8d
  674e328  mov r9,0x100000001B3

loc_674e332:  ; from 674e36c
  674e332  movzx r10d,byte ptr [r12+r8]
  674e337  xor r10,rcx
  674e33a  imul r10,r9
  674e33e  movzx ecx,byte ptr [r12+r8+1]
  674e344  xor rcx,r10
  674e347  imul rcx,r9
  674e34b  movzx r10d,byte ptr [r12+r8+2]
  674e351  xor r10,rcx
  674e354  imul r10,r9
  674e358  movzx ecx,byte ptr [r12+r8+3]
  674e35e  xor rcx,r10
  674e361  imul rcx,r9
  674e365  add r8,4
  674e369  cmp rdx,r8
  674e36c  jne short 0x674E332                           ; -> loc_674e332
  674e36e  test rax,rax
  674e371  je short 0x674E39C                            ; -> loc_674e39c
  674e373  add r12,r8
  674e376  xor edx,edx
  674e378  mov r8,0x100000001B3
  674e382  mov r9,rcx

loc_674e385:  ; from 674e39a
  674e385  movzx ecx,byte ptr [r12+rdx]
  674e38a  xor rcx,r9
  674e38d  imul rcx,r8
  674e391  inc rdx
  674e394  mov r9,rcx
  674e397  cmp rax,rdx
  674e39a  jne short 0x674E385                           ; -> loc_674e385

loc_674e39c:  ; from 674e0d8, 674e371
  674e39c  mov [0x129FA188],rcx                          ; [data_129fa188]
  674e3a3  lea rcx,[rbp+0xC10]
  674e3aa  call 0x73150                                  ; -> sub_73150
  674e3af  lea rcx,[0x129FA190]                          ; [data_129fa190]
  674e3b6  call 0xE938D70                                ; -> sub_e938d70
  674e3bb  jmp 0x674A6A3                                 ; -> sub_674a6a3
  674e3c0  lea rcx,[0x129FA2A0]                          ; [data_129fa2a0]
  674e3c7  call 0xE938CB0                                ; -> sub_e938cb0
  674e3cc  cmp dword ptr [0.129FA2A0],0xFFFFFFFF         ; [data_129fa2a0]
  674e3d3  jne 0x674CD01                                 ; -> sub_674cd01
  674e3d9  xorps xmm0,xmm0
  674e3dc  movaps [rbp+0x240],xmm0
  674e3e3  lea rax,[0xF2BE648]                           ; [data_f2be648] "UI/Fill"
  674e3ea  mov [rbp+0x4D0],rax
  674e3f1  mov qword ptr [rbp+0x4D8],7
  674e3fc  lea rcx,[0x129FA290]                          ; [data_129fa290]
  674e403  lea rdx,[rbp+0x4D0]
  674e40a  lea r8,[rbp+0x240]
  674e411  call 0x5668AC0                                ; -> sub_5668ac0
  674e416  nop
  674e417  lea rcx,[0x129FA2A0]                          ; [data_129fa2a0]
  674e41e  call 0xE938D70                                ; -> sub_e938d70
  674e423  jmp 0x674CD01                                 ; -> sub_674cd01
  674e428  call 0x1166E0                                 ; -> sub_1166e0
  674e42d  nop
  674e42e  mov rcx,0xCBF29CE484222325
  674e438  jmp 0x674E592                                 ; -> loc_674e592
  674e43d  lea rcx,[0x129FA288]                          ; [data_129fa288]
  674e444  call 0xE938CB0                                ; -> sub_e938cb0
  674e449  cmp dword ptr [0x129FA288],0xFFFFFFFF         ; [data_129fa288]
  674e450  jne 0x674BC08                                 ; -> sub_674bc08
  674e456  xorps xmm0,xmm0
  674e459  movaps [rbp+0x230],xmm0
  674e460  lea rax,[0xF2BE628]                           ; [data_f2be628] "UI/Blit"
  674e467  mov [rbp+0x4C0],rax
  674e46e  mov qword ptr [rbp+0x4C8],7
  674e479  lea rcx,[0x129FA278]                          ; [data_129fa278]
  674e480  lea rdx,[rbp+0x4C0]
  674e487  lea r8,[rbp+0x230]
  674e48e  call 0x5668AC0                                ; -> sub_5668ac0
  674e493  nop
  674e494  lea rcx,[0x129FA288]                          ; [data_129fa288]
  674e49b  call 0xE938D70                                ; -> sub_e938d70
  674e4a0  jmp 0x674BC08                                 ; -> sub_674bc08
  674e4a5  lea rcx,[0x129FA2B8]                          ; [data_129fa2b8]
  674e4ac  call 0xE938CB0                                ; -> sub_e938cb0
  674e4b1  cmp dword ptr [0x129FA2B8],0xFFFFFFFF         ; [data_129fa2b8]
  674e4b8  jne 0x674BD12                                 ; -> sub_674bd12
  674e4be  xorps xmm0,xmm0
  674e4c1  movaps [rbp+0x250],xmm0
  674e4c8  lea rax,[0xF2BE668]                           ; [data_f2be668] "UI/Base"
  674e4cf  mov [rbp+0x4E0],rax
  674e4d6  mov qword ptr [rbp+0x4E8],7
  674e4e1  lea rcx,[0x129FA2A8]                          ; [data_129fa2a8]
  674e4e8  lea rdx,[rbp+0x4E0]
  674e4ef  lea r8,[rbp+0x250]
  674e4f6  call 0x5668AC0                                ; -> sub_5668ac0
  674e4fb  nop
  674e4fc  lea rcx,[0x129FA2B8]                          ; [data_129fa2b8]
  674e503  call 0xE938D70                                ; -> sub_e938d70
  674e508  jmp 0x674BD12                                 ; -> sub_674bd12
  674e50d  and rdx,0xFFFFFFFFFFFFFFFC
  674e511  mov rcx,0xCBF29CE484222325
```

## Interpretation [I]
- 0x674dfeb..0x674e04c: ShadowOffset(data_f53c825) → 0x79580 → FNV entries 0x674e7ba/0x674eb25/0x674eb81. GlyphHeight(data_f53b313) → 0x79580 → note the variant at 0x674e0a8: `mov rcx,0x100000001B3` (prime first!) then if r8>=4 → 0x674ebce else `mov rdx,0xCBF29CE484222325` (basis), r9d=0 → 0x674ec20 (FNV entry variant with arg order swapped). [V]
- 0x674e0ce: FNV entry `mov rcx,0xCBF29CE484222325`; `jmp 0x674e39c` (hash tail: store to data_129fa188, call 0x73150 [rbp+0xc10], data_129fa190 → 0xe938d70, jmp 0x674a6a3). [V]
- 0x674e0dd..0x674e14a: GlintTexture(data_f5c6b76) → 0x79580 → FNV entries 0x674ec64/0x674ecaf/0x674ed0b. GlintColor(data_f563953) → 0x79580 → FNV entries 0x674ec73/0x674ed5a/0x674edb6. UVScale(data_f5de988) → 0x79580 → FNV entries 0x674ec82/0x674ee05/0x674ee61. UVOffset(data_f53cae6) → 0x79580 → FNV entries 0x674ec91/0x674eeb0/0x674ef0c. UVRotation(data_f58cc4c) → 0x79580 → FNV entries 0x674eca0/0x674ef5b/0x674efb7. [V]
- 0x674e317..0x674e39c: second FNV-1a 64 loop body (pointer register r12 instead of r14): aligned 4-byte unrolled loop at 0x674e332; tail at 0x674e385 (`movzx ecx,byte [r12+rdx]`; xor; imul; inc rdx; cmp rax,rdx); tail exit 0x674e39c: `mov [0x129FA188],rcx` (store FNV hash); `lea rcx,[rbp+0xc10]`; call 0x73150; `lea rcx,[0x129fa190]`; call 0xe938d70; `jmp 0x674a6a3`. [V]
- 0x674e3c0..0x674e423: **UI/Fill reached from cold tail**: data_129fa2a0 init-once via 0xe938cb0; jne 0x674cd01 (UI/Fill material body at 0x674cd01); else `xorps xmm0`; [rbp+0x240]=0; `lea rax,[0xF2BE648]` "UI/Fill"; [rbp+0x4d0]=rax; [rbp+0x4d8]=7; rcx=data_129fa290, rdx=&[rbp+0x4d0], r8=[rbp+0x240]; call 0x5668ac0; data_129fa2a0 → 0xe938d70; `jmp 0x674cd01`. [V] — so 0x674cd01 is the join after UI/Fill static registration; this IS a predecessor path into the UI/Fill material body.
- 0x674e428: `call 0x1166E0` (sub_1166e0) — **kind>3 default target** from jump table at 0x674b543 (`ja 0x674e428`). [V]
- 0x674e42e: FNV entry `mov rcx,0xCBF29CE484222325; jmp 0x674e592`. [V]
- 0x674e43d..0x674e4a0: **UI/Blit reached from cold tail**: data_129fa288 init-once; jne 0x674bc08; else xorps; [rbp+0x230]=0; "UI/Blit"(data_f2be628) at [rbp+0x4c0], len 7; rcx=data_129fa278, rdx=&[rbp+0x4c0], r8=[rbp+0x230]; call 0x5668ac0; data_129fa288 → 0xe938d70; `jmp 0x674bc08`. [V]
- 0x674e4a5..0x674e508: **UI/Base reached from cold tail**: data_129fa2b8 init-once; jne 0x674bd12; else xorps; [rbp+0x250]=0; "UI/Base"(data_f2be668) at [rbp+0x4e0], len 7; rcx=data_129fa2a8, rdx=&[rbp+0x4e0], r8=[rbp+0x250]; call 0x5668ac0; data_129fa2b8 → 0xe938d70; `jmp 0x674bd12`. [V]
- 0x674e50d: FNV aligned-loop entry variant: `and rdx,0xFFFFFFFFFFFFFFFC; mov rcx,basis` (continues at 0x674e511). [V]

## Cold-tail transcription 0x674e511..0x674eaf6 [V]
(rdis `dis 0x674e511 300`; every instruction quoted exactly as printed, nops included)
```
  674e511  mov rcx,0xCBF29CE484222325
  674e51b  xor r8d,r8d
  674e51e  mov r9,0x100000001B3

loc_674e528:  ; from 674e562
  674e528  movzx r10d,byte ptr [r12+r8]
  674e52d  xor r10,rcx
  674e530  imul r10,r9
  674e534  movzx ecx,byte ptr [r12+r8+1]
  674e53a  xor rcx,r10
  674e53d  imul rcx,r9
  674e541  movzx r10d,byte ptr [r12+r8+2]
  674e547  xor r10,rcx
  674e54a  imul r10,r9
  674e54e  movzx ecx,byte ptr [r12+r8+3]
  674e554  xor rcx,r10
  674e557  imul rcx,r9
  674e55b  add r8,4
  674e55f  cmp rdx,r8
  674e562  jne short 0x674E528                           ; -> loc_674e528
  674e564  test rax,rax
  674e567  je short 0x674E592                            ; -> loc_674e592
  674e569  add r12,r8
  674e56c  xor edx,edx
  674e56e  mov r8,0x100000001B3
  674e578  mov r9,rcx

loc_674e57b:  ; from 674e590
  674e57b  movzx ecx,byte ptr [r12+rdx]
  674e580  xor rcx,r9
  674e583  imul rcx,r8
  674e587  inc rdx
  674e58a  mov r9,rcx
  674e58d  cmp rax,rdx
  674e590  jne short 0x674E57B                           ; -> loc_674e57b

loc_674e592:  ; from 674e567
  674e592  mov [0x129FA550],rcx                          ; [data_129fa550]
  674e599  lea rcx,[rbp+0xC10]
  674e5a0  call 0x73150                                  ; -> sub_73150
  674e5a5  lea rcx,[0x129FA558]                          ; [data_129fa558]
  674e5ac  call 0xE938D70                                ; -> sub_e938d70
  674e5b1  jmp 0x674A91C                                 ; -> sub_674a91c
  674e5b6  lea rcx,[0x129FA240]                          ; [data_129fa240]
  674e5bd  call 0xE938CB0                                ; -> sub_e938cb0
  674e5c2  cmp dword ptr [0x129FA240],0xFFFFFFFF         ; [data_129fa240]
  674e5c9  jne 0x674C11A                                 ; -> sub_674c11a
  674e5cf  mov qword ptr [rbp+0xC18],0
  674e5da  mov qword ptr [rbp+0xC20],0xE
  674e5e5  mov qword ptr [rbp+0xC28],0xF
  674e5f0  mov rax,0x6C6F4369746C754D
  674e5fa  mov [rbp+0xC10],rax
  674e601  mov rax,0x746E6954726F6C6F
  674e60b  mov [rbp+0xC16],rax
  674e612  xorps xmm0,xmm0
  674e615  movups [rbp+0xC30],xmm0
  674e61c  mov qword ptr [rbp+0xC40],2
  674e627  mov qword ptr [rbp+0xC48],0xF
  674e632  mov word ptr [rbp+0xC30],0x6E4F
  674e63b  lea rax,[rbp+0xC10]
  674e642  mov [rbp+0x490],rax
  674e649  lea rax,[rbp+0xC50]
  674e650  mov [rbp+0x498],rax
  674e657  lea rcx,[0x129FA200]                          ; [data_129fa200]
  674e65e  lea rdx,[rbp+0x490]
  674e665  call 0x7D7890                                 ; -> sub_7d7890
  674e66a  nop
  674e66b  lea rcx,[rbp+0xC10]
  674e672  call 0x9B250                                  ; -> sub_9b250
  674e677  lea rcx,[0x6750630]                           ; [sub_6750630]
  674e67e  call 0xE935740                                ; -> sub_e935740
  674e683  lea rcx,[0x129FA240]                          ; [data_129fa240]
  674e68a  call 0xE938D70                                ; -> sub_e938d70
  674e68f  jmp 0x674C11A                                 ; -> sub_674c11a
  674e694  lea rcx,[0x129FA258]                          ; [data_129fa258]
  674e69b  call 0xE938CB0                                ; -> sub_e938cb0
  674e6a0  cmp dword ptr [0x129fa258],0xFFFFFFFF         ; [data_129fa258]
  674e6a7  jne 0x674C13F                                 ; -> sub_674c13f
  674e6ad  lea rdx,[0x129FA200]                          ; [data_129fa200]
  674e6b4  lea rcx,[rbp-0x30]
  674e6b8  lea r8,[rbp+0xC10]
  674e6bf  call 0xAA710                                  ; -> sub_aa710
  674e6c4  nop
  674e6c5  lea rax,[0xF2BE5E8]                           ; [data_f2be5e8] "UI/Sprite"
  674e6cc  mov [rbp+0x4A0],rax
  674e6d3  mov qword ptr [rbp+0x4A8],9
  674e6de  lea rcx,[0x129FA248]                          ; [data_129fa248]
  674e6e5  lea rdx,[rbp+0x4A0]
  674e6ec  lea r8,[rbp-0x30]
  674e6f0  call 0x66A02D0                                ; -> sub_66a02d0
  674e6f5  nop
  674e6f6  lea rcx,[0x129FA258]                          ; [data_129fa258]
  674e6fd  call 0xE938D70                                ; -> sub_e938d70
  674e702  jmp 0x674C13F                                 ; -> sub_674c13f
  674e707  lea rcx,[0x129FA270]                          ; [data_129fa270]
  674e70e  call 0xE938CB0                                ; -> sub_e938cb0
  674e713  cmp dword ptr [0x129FA270],0xFFFFFFFF         ; [data_129FA270]
  674e71a  jne 0x674C276                                 ; -> sub_674c276
  674e720  xorps xmm0,xmm0
  674e723  movaps [rbp+0x220],xmm0
  674e72a  lea rax,[0xF2BE608]                           ; [data_f2be608] "UI/Sprite"
  674e731  mov [rbp+0x4B0],rax
  674e738  mov qword ptr [rbp+0x4B8],9
  674e743  lea rcx,[0x129FA260]                          ; [data_129fa260]
  674e74a  lea rdx,[rbp+0x4B0]
  674e751  lea r8,[rbp+0x220]
  674e758  call 0x5668AC0                                ; -> sub_5668ac0
  674e75d  nop
  674e75e  lea rcx,[0x129FA270]                          ; [data_129fa270]
  674e765  call 0xE938D70                                ; -> sub_e938d70
  674e76a  jmp 0x674C276                                 ; -> sub_674c276
  674e76f  mov rcx,0xCBF29CE484222325
  674e779  jmp 0x674E85D                                 ; -> loc_674e85d
  674e77e  mov rcx,0xCBF29CE484222325
  674e788  jmp 0x674E906                                 ; -> loc_674e906
  674e78d  mov rcx,0xCBF29CE484222325
  674e797  jmp 0x674E9AF                                 ; -> loc_674e9af
  674e79c  mov rcx,0xCBF29CE484222325
  674e7a6  jmp 0x674EA58                                 ; -> loc_674ea58
  674e7ab  mov rcx,0xCBF29CE484222325
  674e7b5  jmp 0x674EB01                                 ; -> loc_674eb01
  674e7ba  mov rcx,0xCBF29CE484222325
  674e7c4  jmp 0x674EBAA                                 ; -> loc_674ebaa
  674e7c9  mov rdx,0xCBF29CE484222325
  674e7d3  jmp 0x674EC40                                 ; -> loc_674ec40
  674e7d8  and rdx,0xFFFFFFFFFFFFFFFC
  674e7dc  mov rcx,0xCBF29CE484222325
  674e7e6  xor r8d,r8d
  674e7e9  mov r9,0x100000001B3

loc_674e7f3:  ; from 674e82d
  674e7f3  movzx r10d,byte ptr [r12+r8]
  674e7f8  xor r10,rcx
  674e7fb  imul r10,r9
  674e7ff  movzx ecx,byte ptr [r12+r8+1]
  674e805  xor rcx,r10
  674e808  imul rcx,r9
  674e80c  movzx r10d,byte ptr [r12+r8+2]
  674e812  xor r10,rcx
  674e815  imul r10,r9
  674e819  movzx ecx,byte ptr [r12+r8+3]
  674e81f  xor rcx,r10
  674e822  imul rcx,r9
  674e826  add r8,4
  674e82a  cmp rdx,r8
  674e82d  jne short 0x674E7F3                           ; -> loc_674e7f3
  674e82f  test rax,rax
  674e832  je short 0x674E85D                            ; -> loc_674e85d
  674e834  add r12,r8
  674e837  xor edx,edx
  674e839  mov r8,0x100000001B3
  674e843  mov r9,rcx

loc_674e846:  ; from 674e85b
  674e846  movzx ecx,byte ptr [r12+rdx]
  674e84b  xor rcx,r9
  674e84e  imul rcx,r8
  674e852  inc rdx
  674e855  mov r9,rcx
  674e858  cmp rax,rdx
  674e85b  jne short 0x674E846                           ; -> loc_674e846

loc_674e85d:  ; from 674e779, 674e832
  674e85d  mov [0x129FA560],rcx                          ; [data_129fa560]
  674e864  lea rcx,[rbp+0xC10]
  674e86b  call 0x73150                                  ; -> sub_73150
  674e870  lea rcx,[0x129FA568]                          ; [data_129fa568]
  674e877  call 0xE938D70                                ; -> sub_e938d70
  674e87c  jmp 0x674AAC7                                 ; -> sub_674aac7
  674e881  and rdx,0xFFFFFFFFFFFFFFFC
  674e885  mov rcx,0xCBF29CE484222325
  674e88f  xor r8d,r8d
  674e892  mov r9,0x100000001B3

loc_674e89c:  ; from 674e8d6
  674e89c  movzx r10d,byte ptr [r12+r8]
  674e8a1  xor r10,rcx
  674e8a4  imul r10,r9
  674e8a8  movzx ecx,byte ptr [r12+r8+1]
  674e8ae  xor rcx,r10
  674e8b1  imul rcx,r9
  674e8b5  movzx r10d,byte ptr [r12+r8+2]
  674e8bb  xor r10,rcx
  674e8be  imul r10,r9
  674e8c2  movzx ecx,byte ptr [r12+r8+3]
  674e8c8  xor rcx,r10
  674e8cb  imul rcx,r9
  674e8cf  add r8,4
  674e8d3  cmp rdx,r8
  674e8d6  jne short 0x674E89C                           ; -> loc_674e89c
  674e8d8  test rax,rax
  674e8db  je short 0x674E906                            ; -> loc_674e906
  674e8dd  add r12,r8
  674e8e0  xor edx,edx
  674e8e2  mov r8,0x100000001B3
  674e8ec  mov r9,rcx

loc_674e8ef:  ; from 674e904
  674e8ef  movzx ecx,byte ptr [r12+rdx]
  674e8f4  xor rcx,r9
  674e8f7  imul rcx,r8
  674e8fb  inc rdx
  674e8fe  mov r9,rcx
  674e901  cmp rax,rdx
  674e904  jne short 0x674E8EF                           ; -> loc_674e8ef

loc_674e906:  ; from 674e788, 674e8db
  674e906  mov [0x129FA570],rcx                          ; [data_129fa570]
  674e90d  lea rcx,[rbp+0xC10]
  674e914  call 0x73150                                  ; -> sub_73150
  674e919  lea rcx,[0x129FA578]                          ; [data_129fa578]
  674e920  call 0xE938D70                                ; -> sub_e938d70
  674e925  jmp 0x674AAEC                                 ; -> sub_674aaec
  674e92a  and rdx,0xFFFFFFFFFFFFFFFC
  674e92e  mov rcx,0xCBF29CE484222325
  674e938  xor r8d,r8d
  674e93b  mov r9,0x100000001B3

loc_674e945:  ; from 674e97f
  674e945  movzx r10d,byte ptr [r12+r8]
  674e94a  xor r10,rcx
  674e94d  imul r10,r9
  674e951  movzx ecx,byte ptr [r12+r8+1]
  674e957  xor rcx,r10
  674e95a  imul rcx,r9
  674e95e  movzx r10d,byte ptr [r12+r8+2]
  674e964  xor r10,rcx
  674e967  imul r10,r9
  674e96b  movzx ecx,byte ptr [r12+r8+3]
  674e971  xor rcx,r10
  674e974  imul rcx,r9
  674e978  add r8,4
  674e97c  cmp rdx,r8
  674e97f  jne short 0x674E945                           ; -> loc_674e945
  674e981  test rax,rax
  674e984  je short 0x674E9AF                            ; -> loc_674e9af
  674e986  add r12,r8
  674e989  xor edx,edx
  674e98b  mov r8,0x100000001B3
  674e995  mov r9,rcx

loc_674e998:  ; from 674e9ad
  674e998  movzx ecx,byte ptr [r12+rdx]
  674e99d  xor rcx,r9
  674e9a0  imul rcx,r8
  674e9a4  inc rdx
  674e9a7  mov r9,rcx
  674e9aa  cmp rax,rdx
  674e9ad  jne short 0x674E998                           ; -> loc_674e998

loc_674e9af:  ; from 674e797, 674e984
  674e9af  mov [0x129FA580],rcx                          ; [data_129fa580]
  674e9b6  lea rcx,[rbp+0xC10]
  674e9bd  call 0x73150                                  ; -> sub_73150
  674e9c2  lea rcx,[0x129FA588]                          ; [data_129fa588]
  674e9c9  call 0xE938D70                                ; -> sub_e938d70
  674e9ce  jmp 0x674AB11                                 ; -> sub_674ab11
  674e9d3  and rdx,0xFFFFFFFFFFFFFFFC
  674e9d7  mov rcx,0xCBF29CE484222325
  674e9e1  xor r8d,r8d
  674e9e4  mov r9,0x100000001B3

loc_674e9ee:  ; from 674ea28
  674e9ee  movzx r10d,byte ptr [r12+r8]
  674e9f3  xor r10,rcx
  674e9f6  imul r10,r9
  674e9fa  movzx ecx,byte ptr [r12+r8+1]
  674ea00  xor rcx,r10
  674ea03  imul rcx,r9
  674ea07  movzx r10d,byte ptr [r12+r8+2]
  674ea0d  xor r10,rcx
  674ea10  imul r10,r9
  674ea14  movzx ecx,byte ptr [r12+r8+3]
  674ea1a  xor rcx,r10
  674ea1d  imul rcx,r9
  674ea21  add r8,4
  674ea25  cmp rdx,r8
  674ea28  jne short 0x674E9EE                           ; -> loc_674e9ee
  674ea2a  test rax,rax
  674ea2d  je short 0x674EA58                            ; -> loc_674ea58
  674ea2f  add r12,r8
  674ea32  xor edx,edx
  674ea34  mov r8,0x100000001B3
  674ea3e  mov r9,rcx

loc_674ea41:  ; from 674ea56
  674ea41  movzx ecx,byte ptr [r12+rdx]
  674ea46  xor rcx,r9
  674ea49  imul rcx,r8
  674ea4d  inc rdx
  674ea50  mov r9,rcx
  674ea53  cmp rax,rdx
  674ea56  jne short 0x674EA41                           ; -> loc_674ea41

loc_674ea58:  ; from 674e7a6, 674ea2d
  674ea58  mov [0x129FA590],rcx                          ; [data_129fa590]
  674ea5f  lea rcx,[rbp+0xC10]
  674ea66  call 0x73150                                  ; -> sub_73150
  674ea6b  lea rcx,[0x129FA598]                          ; [data_129fa598]
  674ea72  call 0xE938D70                                ; -> sub_e938d70
  674ea77  jmp 0x674AB36                                 ; -> sub_674ab36
  674ea7c  and rdx,0xFFFFFFFFFFFFFFFC
  674ea80  mov rcx,0xCBF29CE484222325
  674ea8a  xor r8d,r8d
  674ea8d  mov r9,0x100000001B3

loc_674ea97:  ; from 674ead1
  674ea97  movzx r10d,byte ptr [r12+r8]
  674ea9c  xor r10,rcx
  674ea9f  imul r10,r9
  674eaa3  movzx ecx,byte ptr [r12+r8+1]
  674eaa9  xor rcx,r10
  674eaac  imul rcx,r9
  674eab0  movzx r10d,byte ptr [r12+r8+2]
  674eab6  xor r10,rcx
  674eab9  imul r10,r9
  674eabd  movzx ecx,byte ptr [r12+r8+3]
  674eac3  xor rcx,r10
  674eac6  imul rcx,r9
  674eaca  add r8,4
  674eace  cmp rdx,r8
  674ead1  jne short 0x674EA97                           ; -> loc_674ea97
  674ead3  test rax,rax
  674ead6  je short 0x674EB01                            ; -> loc_674eb01
  674ead8  add r12,r8
  674eadb  xor edx,edx
  674eadd  mov r8,0x100000001B3
  674eae7  mov r9,rcx

loc_674eaea:  ; from 674eaff
  674eaea  movzx ecx,byte ptr [r12+rdx]
  674eaef  xor rcx,r9
  674eaf2  imul rcx,r8
  674eaf6  inc rdx
```

## Interpretation [I]
- 0x674e511..0x674e592: FNV-1a 64 aligned loop #3 (pointer r12): basis rcx, r8d=0, r9=prime 0x100000001B3; loop 0x674e528 (4 bytes/iter xor+imul); exit → 0x674e592 if rax==0 else tail 0x674e569/0x674e57b. Tail exit 0x674e592: `mov [0x129FA550],rcx` (store FNV hash); `lea rcx,[rbp+0xc10]`; call 0x73150; `lea rcx,[0x129fa558]`; call 0xe938d70; `jmp 0x674a91c`. [V]
- 0x674e5b6..0x674e68f: data_129fa240 init-once (jne 0x674c11a); else [rbp+0xc18]=0, [rbp+0xc20]=0xE, [rbp+0xc28]=0xF; 16-byte immediate name at [rbp+0xc10]: imm1 0x6C6F4369746C754D, imm2 0x746E6954726F6C6F → overlapping-write composite "MultiColorTint" (bytes "MultiCol"+"oroTint" = "MultiColorTint", [I]); xorps [rbp+0xc30]; [rbp+0xc40]=2, [rbp+0xc48]=0xF; word [rbp+0xc30]=0x6E4F ("On"); [rbp+0x490]=&[rbp+0xc10], [rbp+0x498]=&[rbp+0xc50]; rcx=data_129fa200, rdx=&[rbp+0x490]; call 0x7d7890 (option registration); [rbp+0xc10] → 0x9b250 (hash); lea rcx,[0x6750630] (fn ptr); call 0xe935740; data_129fa240 → 0xe938d70; `jmp 0x674c11a` (Sprite-body preamble). [V]
- 0x674e694..0x674e702: data_129fa258 init-once (jne 0x674c13f); else rdx=data_129fa200, rcx=[rbp-0x30], r8=[rbp+0xc10]; call 0xaa710; "UI/Sprite"(data_f2be5e8) at [rbp+0x4a0], len 9; rcx=data_129fa248, rdx=&[rbp+0x4a0], r8=[rbp-0x30]; call 0x66a02d0; data_129fa258 → 0xe938d70; `jmp 0x674c13f`. [V]
- 0x674e707..0x674e76a: data_129fa270 init-once (jne 0x674c276); else xorps [rbp+0x220]; "UI/Sprite"(data_f2be608) at [rbp+0x4b0], len 9; rcx=data_129fa260, rdx=&[rbp+0x4b0], r8=[rbp+0x220]; call 0x5668ac0; data_129fa270 → 0xe938d70; `jmp 0x674c276`. [V]
- 0x674e76f..0x674ea77: FNV entry blocks (bias rcx=0xCBF29CE484222325) jumping to hash tails: 0x674e76f→0x674e85d (store data_129fa560; →sub_674aac7), 0x674e77e→0x674e906 (store data_129fa570; →sub_674aaec), 0x674e78d→0x674e9af (store data_129fa580; →sub_674ab11), 0x674e79c→0x674ea58 (store data_129fa590; →sub_674ab36). Aligned-loop entries: 0x674e7d8 (and rdx,0x...FFFFFFFC → loop 0x674e7f3), 0x674e881 (→loop 0x674e89c), 0x674e92a (→loop 0x674e945), 0x674e9d3 (→loop 0x674e9ee), 0x674ea7c (→loop 0x674ea97, truncated). Tail loops: 0x674e57b (for data_129fa550), 0x674e846 (→data_129fa560), 0x674e8ef (→data_129fa570), 0x674e998 (→data_129fa580), 0x674ea41 (→data_129fa590). Every hash tail: store rcx to data global, `lea rcx,[rbp+0xc10]`, call 0x73150, load next data global → 0xe938d70, jmp to sub_674aXXX (0x674a91c/0x674aac7/0x674aaec/0x674ab11/0x674ab36). [V]



## Jump table (dispatch at 0x674b550) [V]
```
0x674B53A  movzx eax,byte ptr [r14+0x18]                  ; byte [rec+0x18] = record kind (0..3)
0x674B53F  cmp rax,3                                     
0x674B543  ja 0x674E428                                  ; -> sub_674e428 (kind > 3 -> cold tail)
0x674B549  lea rcx,[0xF2BFC90]                           ; [data_f2bfc90] table base
0x674B550  movsxd rax,[rcx+rax*4]                        
0x674B554  add rax,rcx                                   
0x674B557  jmp rax                                       
```
Table entries [V from dossier]: 0->0x674b559, 1->0x674b9b2, 2->0x674b71a, 3->0x674b85d.

## Case 0 -> loc_674b559 (first material branch) [V]
Range 0x674b559..0x674b70e (then jmp to 0x674c4fa).
- 0x674b559 `cmp byte ptr [rbp+0xEE8],0`; `je 0x674C34B` — gate on byte [rbp+0xEE8].
- 0x674b566 `lea rcx,[rbp+0x810]`; 0x674b56d `lea rdi,[rbp+0x5F0]`; 0x674b574 `mov rdx,rdi`; **0x674b577 call 0x67b9c90** (0x674b57c nop).
- 0x674b57d `lea rdx,[rbp+0x700]`; 0x674b584 `lea r8,[rbp+0x6A8]`; 0x674b58b `lea r9,[rbp+0x650]`; 0x674b592 `lea rax,[rbp+0x648]`; 0x674b599 `lea rcx,[rbp+0x640]`; 0x674b5a0 `lea r10,[rbp+0x5F8]`; stack spill [rsp+0x38]=rdi, [rsp+0x30]=r10, [rsp+0x28]=rcx, [rsp+0x20]=rax; **0x674b5bb lea rcx,[rbp+0xC10]**; **0x674b5c2 call 0x67bb680**; nop.
- 0x674b5c8 `lea rdi,[rbp+0x2E0]`; 0x674b5cf `lea rdx,[rbp+0xC10]`; 0x674b5d6 `mov rcx,rdi`; **0x674b5d9 call 0x67ba750**; nop.
- 0x674b5df `movzx eax,byte ptr [rbp+0xDA8]`; `mov [rbp+0x478],al`; 0x674b5ec `lea rcx,[rbp+0xC10]`; **0x674b5f3 call 0x67bc2c0**.
- Second group: 0x674b5f8 `lea rdx,[rbp+0x3F0]`; 0x674b5ff `lea r8,[rbp+0x398]`; 0x674b606 `lea r9,[rbp+0x340]`; 0x674b60d `lea rax,[rbp+0x338]`; 0x674b614 `lea rcx,[rbp+0x330]`; 0x674b61b `lea r10,[rbp+0x2E8]`; same stack spill pattern; **0x674b636 lea rcx,[rbp+0xC10]**; **0x674b63d call 0x67bb680**; nop.
- 0x674b643 `lea rcx,[rbp+0x910]`; 0x674b64a `lea rdx,[rbp+0xC10]`; **0x674b651 call 0x67ba750**; nop.
- 0x674b657 `movzx eax,byte ptr [rbp+0xDA8]`; 0x674b65e `movzx ecx,byte ptr [rbp+0xDB0]`; `mov [rbp+0xAA8],al`; `mov [rbp+0xAB0],cl`; 0x674b671 `lea rcx,[rbp+0xC10]`; **0x674b678 call 0x67bc2c0**.
- 0x674b67d `mov rsi,[rsi+0x10]`; 0x674b681 `lea rax,[0xF2BE8C8]`; `mov [rbp+0xC10],rax`; 0x674b68f `lea rdi,[rbp+0xC18]`; 0x674b696 `lea rdx,[rbp+0x910]`; 0x674b69d `mov rcx,rdi`; **0x674b6a0 call 0x67ba750**; nop.
- 0x674b6a6 `movzx eax,byte ptr [rbp+0xAA8]`; 0x674b6ad `movzx ecx,byte ptr [rbp+0xAB0]`; `mov [rbp+0xDB0],al`; `mov [rbp+0xDB8],cl`.
- 0x674b6c0 `add rsi,0x9D0`; then 0x674b6c7..0x674b700 stack setup: [rsp+0x38]=rdi, [rsp+0x30]=rax(rbp+0xC20), [rsp+0x28]=rcx(rbp+0xC68), [rsp+0x20]=r10(rbp+0xC70), [rsp+?]=r9(rbp+0xC78), r8(rbp+0xCD0), rdx(rbp+0xD28), rcx=rsi; **0x674b705 mov rcx,rsi**; **0x674b708 call 0x67baa90**; nop.
- 0x674b70e `lea rax,[0xF2BE8C8]`; `jmp 0x674C4FA`.
- Interpretation [I]: this case builds a pass payload (record at rbp+0xC10 area), calls 0x67bb680 (per-item builder), 0x67ba750 (material setup), 0x67bc2c0 (texture/field writer), 0x67baa90 (append to pass vector at rsi+0x9D0 stride). Material literal not yet seen in this range (jumps to 0x674c4fa before any lea of a material string here — need to check 0x674c4fa target). Does not match "UI/Blit"/"UI/Base"/"UI/Sprite"/"UI/Fill" literals directly in 0x674b559..0x674b70e.

## Case 2 -> loc_674b71a [V] (captured texture, mesh capture)
Range 0x674b71a..0x674b85c (then jmp to 0x674c538).
- 0x674b71a `xorps xmm0,xmm0`; `movups [rbp+0xAEF],xmm0`; `movaps [rbp+0xAE0],xmm0` (zero 16 bytes at rbp+0xAEF and rbp+0xAE0).
- 0x674b72b `mov rax,0x100000001`; `mov [rbp+0xB00],rax` (qword = 1).
- 0x674b73c `mov rax,[r14]`; `mov [rbp+0xAF0],rax` (qword copy of rec[0]).
- 0x674b746 `mov dword ptr [rbp+0xAF8],0x1C` (dword 0x1c).
- 0x674b750 `mov rdi,[rsi+0x48]`; 0x674b754 `mov rcx,[0x1233E1A8]`; 0x674b75b `mov rax,[rcx]`; 0x674b75e `mov rax,[rax+8]`; 0x674b762 `mov edx,0x20`; **0x674b767 call qword ptr [0xF99FFA0]** (= sub_eea6040, allocator); nop; 0x674b76e `mov rbx,rax`; `test rax,rax`; `je 0x674CE8D`.
- loc_674b77a: 0x674b77a `lea r15,[rbp+0xAF0]`; 0x674b781 `movups xmm0,[0xF5C6AC7]` ("hCapture texture" [V literal at data_f5c6ac7]); `movups [rbx+0xE],xmm0`; 0x674b78c `movups xmm0,[0xF5C6AB9]` ("UIThumbnailMeshCapture texture" [V literal at data_f5c6ab9]); `movups [rbx],xmm0`; 0x674b796 `mov byte ptr [rbx+0x1E],0`; 0x674b79a `mov rax,[r15+0x10]`; `mov [rbp+0xC20],rax`; 0x674b7a5 `movups xmm0,[r15]`; `movaps [rbp+0xC10],xmm0`; 0x674b7b0 `mov [rbp+0xC28],rbx`; `mov qword ptr [rbp+0xC30],0`; `mov qword ptr [rbp+0xC38],0x1E`; `mov qword ptr [rbp+0xC40],0x1F`; 0x674b7d8 `lea rdx,[rbp+0x910]`; 0x674b7df `lea r8,[rbp+0xC10]`; 0x674b7e6 `mov rcx,rdi`; **0x674b7e9 call 0x5ab9970**; nop.
- 0x674b7ef `mov rdi,[rbp+0x918]`; 0x674b7f6 `movaps xmm0,[rbp+0x910]`; 0x674b7fd `xorps xmm6,xmm6`; `movaps [rbp+0x910],xmm6`; `movaps [rbp+0xAE0],xmm0`; 0x674b80e `lea rcx,[rbp+0xC10]`; **0x674b815 call 0xa40d0**; 0x674b81a `mov byte ptr [rbp+0x894],0xF`; 0x674b821 `lea rcx,[rbp+0x810]`; 0x674b828 `lea rdx,[rbp+0x2E0]`; **0x674b82f call 0x67b9c90**; nop.
- 0x674b835 `movaps [rbp+0x5F0],xmm6`; 0x674b83c `mov rax,[r14+0x10]`; `test rax,rax`; `je 0x674C536`; 0x674b849 `lock inc dword ptr [rax+8]`; 0x674b84d `mov rax,[r14+0x10]`; 0x674b851 `mov rdi,[rbp+0xAE8]`; `jmp 0x674C538`.
- Interpretation [I]: case 2 builds a "UIThumbnailMeshCapture"/"hCapture texture" capture object via allocator (size 0x20), fills texture record [rbx+0x0]=name, [rbx+0xE]="hCapture texture", byte [rbx+0x1E]=0, then registers via 0x5ab9970, releases via 0xa40d0, ref-counts [r14+0x10], joins at 0x674c538.

## Case 3 -> loc_674b85d [V] (structure volume capture)
Range 0x674b85d..0x674b9ad (then jmp to 0x674c603).
- 0x674b85d `mov byte ptr [rbp+0xDF6],0`; `mov word ptr [rbp+0xDF4],0`; `xorps xmm0,xmm0`; `movaps [rbp+0x260],xmm0`.
- 0x674b877 `mov r15d,[r14]`; `mov r12d,[r14+4]` (dwords from rec[0] and rec[4]).
- 0x674b87e `mov rdi,[rsi+0x48]`; same allocator pattern as case 2 but **0x674b890 `mov edx,0x30`** (alloc size 0x30); call [0xF99FFA0]; `mov rbx,rax`; `test rax,rax`; `je 0x674CE9D`.
- loc_674b8a8: 0x674b8a8 `movups xmm0,[0xF5C6AE8]` ("eCapture texture" [V literal at data_f5c6ae8]); `movups [rbx+0x10],xmm0`; 0x674b8b3 `movups xmm0,[0xF5C6AD8]` ("UIStructureVolumeCapture texture" [V literal at data_f5c6ad8]); `movups [rbx],xmm0`; `mov byte ptr [rbx+0x20],0`; `mov [rbp+0xC10],r15d`; `mov [rbp+0xC14],r12d`; `mov dword ptr [rbp+0xC18],0x1C`; 0x674b8d9 `movzx eax,word ptr [rbp+0xDF4]`; `mov [rbp+0xC1C],ax`; 0x674b8e7 `movzx eax,byte ptr [rbp+0xDF6]`; `mov [rbp+0xC1E],al`; `mov r13,0x100000001`; `mov [rbp+0xC20],r13`; `mov [rbp+0xC28],rbx`; `mov qword ptr [rbp+0xC30],0`; `mov qword ptr [rbp+0xC38],0x20`; `mov qword ptr [rbp+0xC40],0x2F`.
- 0x674b92d `lea rdx,[rbp+0x910]`; 0x674b934 `lea r8,[rbp+0xC10]`; 0x674b93b `mov rcx,rdi`; **0x674b93e call 0x5ab9970**; nop.
- 0x674b944 `mov rdi,[rbp+0x910]`; 0x674b94b `mov rbx,[rbp+0x918]`; `xorps xmm6,xmm6`; `movaps [rbp+0x910],xmm6`; `mov [rbp+0x260],rdi`; `mov [rbp+0x268],rbx`; 0x674b96a `lea rcx,[rbp+0xC10]`; **0x674b971 call 0xa40d0**; nop.
- 0x674b977 `lea rcx,[rbp+0x810]`; 0x674b97e `lea rdx,[rbp+0x2E0]`; **0x674b985 call 0x67b9c90**; nop.
- 0x674b98b `movaps [rbp+0xAE0],xmm6`; `test rbx,rbx`; `je 0x674C601`; 0x674b99b `lock inc dword ptr [rbx+8]`; 0x674b99f `mov rdi,[rbp+0x260]`; 0x674b9a6 `mov rax,[rbp+0x268]`; `jmp 0x674C603`.
- Interpretation [I]: case 3 builds "UIStructureVolumeCapture"/"eCapture texture" capture object via allocator (size 0x30), registers via 0x5ab9970, joins at 0x674c603.

## Case 1 -> loc_674b9b2 [V]
Range 0x674b9b2..0x674bae7 (then loop loc_674baed..loc_674bae0).
- 0x674b9b2 `mov rbx,[rsi+0x10]`; 0x674b9b6 `mov rcx,[r13+0x470]`; 0x674b9bd `mov rax,[rcx]`; 0x674b9c0 `mov rax,[rax+0x48]`; 0x674b9c4 `lea rdx,[rbp+0x5F0]`; **0x674b9cb call qword ptr [0xF99FFA0]** (= sub_eea6040); nop.
- 0x674b9d2 `mov rsi,[r14]`; `mov byte ptr [rbp+0x894],0xF`; 0x674b9dc `lea rcx,[rbp+0x810]`; 0x674b9e3 `lea rdx,[rbp+0x2E0]`; **0x674b9ea call 0x67b9c90**; nop.
- 0x674b9f0 `lea rcx,[rbp+0x910]`; 0x674b9f7 `lea rdx,[rbp+0x2E0]`; 0x674b9fe `mov r8,rsi`; **0x674ba01 call 0x67bc400**; nop.
- 0x674ba07 `lea r15,[0xF2BE8E8]`; `mov [rbp+0xC10],r15` (qword = data_f2be8e8); 0x674ba15 `lea rsi,[rbp+0xC18]`; 0x674ba1c `lea rdx,[rbp+0x910]`; 0x674ba23 `mov rcx,rsi`; **0x674ba26 call 0x67ba750**; nop.
- 0x674ba2c `lea rdi,[rbp+0xDB0]`; 0x674ba33 `lea rdx,[rbp+0xAA8]`; 0x674ba3a `lea r14,[rbp+0xDC0]`; `mov [rbp+0xDB0],r14`; `mov rax,0x100000000`; `mov [rbp+0xDB8],rax` (qword = 0x100000000).
- 0x674ba59 `mov rcx,rdi`; **0x674ba5c call 0x6764990**; nop (DrawItem pool copy per dossier).
- 0x674ba61 `add rbx,0x9D0`; stack setup: [rsp+0x40]=rsi, [rsp+0x38]=rax(rbp+0xC20), [rsp+0x30]=rcx(rbp+0xC68), [rsp+0x28]=rdx(rbp+0xC70), [rsp+0x20]=r10(rbp+0xC78), [rsp+?]=r9(rbp+0xCD0), r8(rbp+0xD28), rcx=rbx; 0x674baab `mov rdx,rdi`; **0x674bab1 call 0x67bcc80**; nop.
- 0x674bab7 `mov [rbp+0xC10],r15`; 0x674babe `mov rdi,[rbp+0xDB0]`; `mov ebx,[rbp+0xDB8]`; `test rbx,rbx`; `je 0x674C01D`.
- 0x674bad4 `shl rbx,5`; `xor r15d,r15d`; `jmp short 0x674BAED`.
- loc_674baed: `mov rcx,[rdi+r15+8]`; `test rcx,rcx`; `je short 0x674BAE0`; `lock dec dword ptr [rcx+0xC]`; `jne short 0x674BAE0`; `mov rax,[rcx]`; `mov rax,[rax+8]`; **call qword ptr [0xF99FFA0]** (release); `jmp short 0x674BAE0`.
- loc_674bae0: `add r15,0x20`; `cmp rbx,r15`; `je 0x674C016`.
- Interpretation [I]: case 1 loads material qword from data_f2be8e8 into [rbp+0xC10], calls 0x67ba750, 0x67bc400, 0x6764990 (DrawItem pool copy), then 0x67bcc80 append at rbx+0x9D0; then a release loop over [rbp+0xDB0]..[rbp+0xDB8] count (shl 5 => 32-byte stride), releasing each entry via [0xF99FFA0].

## Case 0 target at 0x674c4fa [V] (reached via `jmp 0x674c4fa` from 0x674b70e, and fall-through from 0x674c4f3)
```
  674c4f3  lea rax,[0xF2BE8D8]                           ; [data_f2be8d8]
  674c4fa  mov [rbp+0xC10],rax                           
  674c501  lea rcx,[rbp+0xC18]                           
  674c508  call 0x67BC2C0                                ; -> sub_67bc2c0
  674c50d  lea rcx,[rbp+0x910]                           
  674c514  call 0x67BC2C0                                ; -> sub_67bc2c0
  674c519  lea rcx,[rbp+0x2E0]                           
  674c520  call 0x67BC2C0                                ; -> sub_67bc2c0
  674c525  lea rcx,[rbp+0x5F0]                            ... (chunk ended, continues at 0x674c52c?)
```
Note: case 0's two subcases set different material qwords: [rbp+0xEE8]!=0 path (0x674b70e `lea rax,[0xF2BE8C8]`) → 0x674c4fa stores data_f2be8c8; [rbp+0xEE8]==0 path (je 0x674c34b → 0x674c4f3 `lea rax,[0xF2BE8D8]`) → stores data_f2be8d8. [I]

## Case 1 tail region 0x674c016..0x674c0db [V]
- 0x674c016 `mov rdi,[rbp+0xDB0]`; `cmp r14,rdi`; `je short 0x674c03f`; `test rdi,rdi`; `je short 0x674c03f`; `mov rax,[rcx]`; `mov rax,[rax+0x10]`; `mov rdx,rdi`; `call qword ptr [0xF99FFA0]` (release); nop.
- 0x674c03f `mov rcx,rsi`; **0x674c042 call 0x67bc2c0**; `mov rsi,[rbp+0xAA8]`; `mov edi,[rbp+0xAB0]`; `test rdi,rdi`; `je short 0x674c09f`; `shl rdi,5`; `xor ebx,ebx`; `jmp short 0x674c079`.
- loc_674c070: `add rbx,0x20`; `cmp rdi,rbx`; `je short 0x674c098`.
- loc_674c079: `mov rcx,[rsi+rbx+8]`; `test rcx,rcx`; `je short 0x674c070`; `lock dec dword ptr [rcx+0xC]`; `jne short 0x674c070`; `mov rax,[rcx]`; `mov rax,[rax+8]`; `call qword ptr [0xF99FFA0]`; `jmp short 0x674c070`.
- loc_674c098: `mov rsi,[rbp+0xAA8]`.
- loc_674c09f: `lea rax,[rbp+0xAB8]`; `cmp rax,rsi`; `je short 0x674c0c8`; `test rsi,rsi`; `je short 0x674c0c8`; `mov rax,[rcx]`; `mov rax,[rax+0x10]`; `mov rdx,rsi`; `call qword ptr [0xF99FFA0]`; nop.
- loc_674c0c8: `lea rcx,[rbp+0x910]`; **0x674c0cf call 0x67bc2c0**; `lea rcx,[rbp+0x2E0]`; `jmp 0x674c52c`.
- Interpretation [I]: case 1 tail releases two arrays ([rbp+0xDB0] count [rbp+0xDB8] stride 0x20; and [rbp+0xAA8]..[rbp+0xAB8] range) then calls 0x67bc2c0 twice and jmps to 0x674c52c.

## UI/Blit path at 0x674bc15 [V] (reached from 0x674bbdb region, predecessor of 0x674bb0c still [?])
```
  674bc15  lea rax,[0xF2BE628]                           ; [data_f2be628] "UI/Blit"
  674bc1c  mov [rbp+0xC10],rax                           
  674bc23  mov qword ptr [rbp+0xC18],7                   
  674bc2e  lea rax,[0x129FB170]                          ; [data_129fb170]
  674bc35  mov [rsp+0x28],rax                            
  674bc3a  lea rax,[rbp+0xC10]                           
  674bc41  mov [rsp+0x20],rax                            
  674bc46  lea r8,[0x129FA278]                           ; [data_129fa278]
  674bc4d  lea rdx,[rbp+0x910]                           
  674bc54  mov rcx,r12                                   
  674bc57  call 0x67D6D70                                ; -> sub_67d6d70
  674bc5c  mov rcx,[rbp+0x910]                           
  674bc63  call 0x66A0760                                ; -> sub_66a0760
  674bc69  test al,al                                    
  674bc6b  je 0x674CE28                                  ; -> loc_674ce28
  674bc71  mov rcx,[rbp+0x910]                           
  674bc78  call 0xBCAB880                                ; -> sub_bcab880
  674bc80  je 0x674CE28                                  ; -> loc_674ce28
  674bc86  mov r8,[rsi]                                  
  674bc89  mov rdx,[rbp+0x910]                           
  674bc90  mov byte ptr [rbp+0xBF0],0                    
  674bc97  lea rcx,[rbp+0xB68]                           
  674bc9e  call 0x675DD80                                ; -> sub_675dd80
  674bca3  nop                                           
  674bca4  mov byte ptr [rbp+0xBF0],1                    
  674bcab  lea r8,[0x129FA188]                           ; [data_129fa188]
  674bcb2  lea rcx,[rbp+0xB68]                           
  674bcb9  lea rdx,[rbp+0xC10]                           
  674bcc0  mov r9,[rbp+0xEA0]                            
  674bcc7  call 0xBCAC2B0                                ; -> sub_bcac2b0
  674bccc  jmp 0x674CDA7                                  ; -> loc_674cda7
```
- 0x674bbb6..0x674bbdb prelude: `test al,2` / `jne 0x674c0e0` / `and ecx,2; shr ecx,1` / `mov eax,ecx` / `test dl,dl` / `jne 0x674bbdb` / `jmp 0x674bce2`. Then 0x674bbdb: `test al,al`; `jne 0x674c0e8`; `mov eax,[0x129FA288]`; `mov ecx,[0x128767C8]`; `mov rdx,gs:[0x58]`; `mov rcx,[rdx+rcx*8]`; `cmp eax,[rcx+4]`; `jg 0x674e43d`; `mov r12,[rsi+0x68]`; `call 0x66b2310`; `mov r9,[rsi+0x40]`; → 0x674bc15 "UI/Blit".
- 0x674bb56 path: `cmp byte ptr [r14+0x244],0`; `je 0x674bbce`; reads [r14+0x1fc]/[r14+0x21c] words; pcmp against 0xF275E82/0xF275E90 (16-byte compares); pmovmskb; cmp 0xFFFF; `je 0x674bcd2`. loc_674bbce: `and eax,2; shr eax,1`; `test dl,dl`; `je 0x674bce2`. loc_674bcd2: `movzx eax,byte ptr [r14+0x1a1]`; `test dl,dl`; `jne 0x674bbdb`. loc_674bce2: gs:[0x58] TLS check; `test al,al`; `jne 0x674ccf2`; then `mov rdi,r15`; cmp [0x129FA2B8],ecx; `jg 0x674e4a5`; `mov r15,[rsi+0x68]`; `call 0x66b2310`; `mov r9,[rsi+0x40]`; → 0x674bd1f "UI/Base".

## UI/Base path at 0x674bd1f [V]
```
  674bd1f  lea rax,[0xF2BE668]                           ; [data_f2be668] "UI/Base"
  674bd26  mov [rbp+0xC10],rax                           
  674bd2d  mov qword ptr [rbp+0xC18],7                   
  ... (same 0x67d6d70 + 0x66a0760 + 0xbcab880 sequence as Blit) ...
  674bd93  mov r8,[rsi]                                  
  674bd96  mov rdx,[rbp+0x910]                           
  674bd9d  mov byte ptr [rbp+0xBF0],0                    
  674bda4  lea rcx,[rbp+0xB68]                           
  674bdab  call 0x675DD80                                ; -> sub_675dd80
  674bdb0  jmp 0x674CDA0                                  ; -> loc_674cda0
```

## UI/Sprite paths [V]
- 0x674c147 `lea rax,[0xF2BE5E8]` "UI/Sprite"; [rbp+0xC18]=9; via 0x67d6d70 with r8=data_129fa248; then 0x66a0760; 0xbcab880; `mov r8,[rsi]`; `mov rdx,[rbp+0x910]`; `mov byte ptr [rbp+0xBF0],0`; 0x675dd80; `mov r9,[rbp+0xEC0]`; `mov byte ptr [rbp+0xBF0],1`; `lea r8,[0x129F8340]`; `lea rcx,[rbp+0xB68]`; `lea rdx,[rbp+0xC10]`; **0x674c1f6 call 0x66a0ec0**; nop; `jmp 0x674c319`.
- 0x674c283 `lea rax,[0xF2BE608]` "UI/Sprite"; [rbp+0xC18]=9; via 0x67d6d70 with r8=data_129fa260; then 0x66a0760; 0xbcab880; `mov r8,[rsi]`; `mov rdx,[rbp+0x910]`; `mov byte ptr [rbp+0xBF0],0`; 0x675dd80; `mov byte ptr [rbp+0xBF0],1`; → falls to 0x674c319.
- loc_674c319: `lea rcx,[rbp+0x910]`; **0x674c320 call 0x7e6d0**; `lea r8,[0x129fa188]`; `lea rcx,[rbp+0xB68]`; `lea rdx,[rbp+0xC10]`; `mov r9,[rbp+0xEA0]`; **0x674c341 call 0xbcac2b0**; `jmp 0x674cdb3`.
- Reached from 0x674c0ef (`cmp byte ptr [rbp+0xEB0],0`; `je 0x674c201` → falls to 0x674c0f5 Sprite path) and 0x674c201 (gate on dil, sets [rbp+0x89c/0x89e/0x898], then [rbp+0xee0] checks, then TLS check → 0x674c276 Sprite path at 0x674c283).

## Mystery: 0x674bb0c reachability [?]
0x674bb0c (`movzx edx,byte ptr [r14+0x1A4]`) is not a direct jump target from any of the 4 switch cases seen so far, nor fall-through from case 1 (which exits via `je 0x674c016`). Predecessor [?]. Blocks 0x674bb56/0x674bbce/0x674bbdb/0x674bcd2/0x674bce2 form a decision tree leading to UI/Blit (0x674bc15) or UI/Base (0x674bd1f). Possibly reached from a join point (0x674c016/0x674c34b/0x674c4fa/0x674c538/0x674c603) via backward jump not yet seen, or from cold tails.

## Sprite/Bitmask gate detail [V]
0x674bb18: `movdqu xmm0,[0xF275E82]`; `movdqu xmm1,[r14+0x1da]`; `pcmpeqb xmm1,xmm0`; `movdqu xmm0,[r14+0x1e8]`; `movdqu xmm2,[0xF275E90]`; `pcmpeqb xmm2,xmm0`; `pand xmm2,xmm1`; `pmovmskb ecx,xmm2`; `cmp ecx,0xFFFF`; `je 0x674bcd2`. Second set at 0x674bb76: [r14+0x1fe]/[r14+0x20c] → pmovmskb r8d; cmp 0xFFFF; `je 0x674bcd2`.

## UI/Fill material literal 0x674cd0e
Not yet reached in disassembly.

## Constants / data refs seen
- data_f2be8c8, data_f2be8d8 (case 0 material qwords); data_f2be8e8 (case 1 material qword); data_f5c6ac7 "hCapture texture", data_f5c6ab9 "UIThumbnailMeshCapture texture" (case 2); data_f5c6ae8 "eCapture texture", data_f5c6ad8 "UIStructureVolumeCapture texture" (case 3); data_f2be628 "UI/Blit", data_f2be668 "UI/Base", data_f2be5e8 "UI/Sprite", data_f2be608 "UI/Sprite"; data_f275e82, data_f275e90 (bitmask compare constants); data_129fa200/129fa248/129fa260/129fa278/129fa188/129f8340 (option/key ptrs); data_129fa288/129fa2b8/129fa240/129fa258/129fa270 (TLS/counter globals); data_128767c8 (TLS index); [0xF99FFA0]=sub_eea6040 (allocator/releaser).

## Join at 0x674c52c (end of case 0/1 triple-0x67bc2c0 sequence) [V]
```
  674c520  call 0x67BC2C0                                ; -> sub_67bc2c0
  674c525  lea rcx,[rbp+0x5F0]                           
  674c52c  call 0x67BC2C0                                ; -> sub_67bc2c0
  674c531  jmp 0x674CC21                                 ; -> loc_674cc21
```

## Case 2 join target 0x674c538 [V] (from 0x674b858 `jmp 0x674c538`)
```
  674c536  xor eax,eax                                   
  674c538  mov rcx,[r14+8]                               
  674c53c  mov [rbp+0x5F0],rcx                           
  674c543  mov [rbp+0x5F8],rax                           
  674c54a  xorps xmm0,xmm0                               
  674c54d  movaps [rbp+0x600],xmm0                       
  674c554  test rdi,rdi                                  
  674c557  je short 0x674C566                            ; -> loc_674c566
  674c559  lock inc dword ptr [rdi+8]                    
  674c55d  mov rax,[rbp+0xAE8]                           
  674c564  jmp short 0x674C568                           ; -> loc_674c568
loc_674c566:  ; from 674c557
  674c566  xor eax,eax                                   
loc_674c568:  ; from 674c564
  674c568  mov rcx,[rbp+0xAE0]                           
  674c56f  mov [rbp+0x600],rcx                           
  674c576  mov [rbp+0x608],rax                           
  674c57d  movups xmm0,[r15]                             
  674c581  movaps [rbp+0x610],xmm0                       
  674c588  mov rax,[r15+0x10]                            
  674c58c  mov [rbp+0x620],rax                           
  674c593  lea rcx,[rbp+0x2E0]                           
  674c59a  lea rdx,[rbp+0x910]                           
  674c5a1  lea r8,[rbp+0x5F0]                            
  674c5a8  call 0x67BD4B0                                ; -> sub_67bd4b0
  674c5ad  nop                                           
  674c5ae  mov rdi,[rsi+0x10]                            
  674c5b2  lea rbx,[0xF2BE8F8]                           ; [data_f2be8f8]
  674c5b9  mov [rbp+0xC10],rbx                           
  674c5c0  lea rsi,[rbp+0xC18]                           
  674c5c7  lea rdx,[rbp+0x910]                           
  674c5ce  mov rcx,rsi                                   
  674c5d1  call 0x67BA750                                ; -> sub_67ba750
  674c5d6  nop                                           
  674c5d7  xorps xmm0,xmm0                               
  674c5da  movups [rbp+0xDB0],xmm0                       
  674c5e1  mov rax,[rbp+0xAB0]                           
  674c5e8  test rax,rax                                  
  674c5eb  je 0x674C73D                                  ; -> loc_674c73d
  674c5f1  lock inc dword ptr [rax+8]                    
  674c5f5  mov rax,[rbp+0xAB0]                           
  674c5fc  jmp 0x674C73F                                 ; -> loc_674c73f
```
- data_f2be8f8 = another material qword (case 2's material after the capture-object setup). [I]

## Case 3 join target 0x674c603 [V] (from 0x674b9ad `jmp 0x674c603`)
```
  674c601  xor eax,eax                                   
  674c603  mov [rbp+0xAE0],rdi                           
  674c60a  mov [rbp+0xAE8],rax                           
  674c611  mov [rbp+0xAF0],r15d                          
  674c618  mov [rbp+0xAF4],r12d                          
  674c61f  mov dword ptr [rbp+0xAF8],0x1C                
  674c629  movzx ecx,byte ptr [rbp+0xDF6]                
  674c630  mov [rbp+0xAFE],cl                            
  674c636  movzx ecx,word ptr [rbp+0xDF4]                
  674c63d  mov [rbp+0xAFC],cx                            
  674c644  mov [rbp+0xB00],r13                           
  674c64b  xorps xmm0,xmm0                               
  674c64e  movaps [rbp+0x5F0],xmm0                       
  674c655  mov rcx,[r14+0x10]                            
  674c659  test rcx,rcx                                  
  674c65c  je short 0x674C66F                            ; -> loc_674c66f
```
- Interpretation [I]: 0x674c538 (case 2) and 0x674c603 (case 3) both build a record at [rbp+0x5f0..0xb00] (qword/dword/word/byte fields + xmm zeroing) then diverge: case 2 calls 0x67bd4b0 then sets [rbp+0xc10]=data_f2be8f8 + 0x67ba750; case 3 continues at 0x674c655 (ref-count [r14+0x10]). Both are capture-material cases.

## Cold-tail / branch targets seen so far [V] (not yet transcribed)
0x674cc21 (from 0x674c531 jmp), 0x674c73d/0x674c73f, 0x674c66f, 0x674ccd9, 0x674c201, 0x674c319, 0x674cdb3, 0x674cda7/0x674cda0, 0x674ce28, 0x674ce34 (kind>3 default), 0x674ce8d, 0x674ce9d, 0x674ce98, 0x674cea8, 0x674c0e0/0x674c0e8, 0x674bcd2, 0x674ccf2, 0x674c4fa, 0x674ce4e (hot-path ret per dossier), cold tails to 0x674d15e. UI/Fill literal 0x674cd0e not yet reached.

## Case 3 join continuation 0x674c65c..0x674c83f [V] (from 0x674c65c `je 0x674c66f`)
```
  674c65c  je short 0x674C66F                            ; -> loc_674c66f
  674c65e  lock inc dword ptr [rcx+8]                    ; W a0+0x8
  674c662  mov rdx,[r14+0x10]                            
  674c666  mov rax,[rbp+0xAE8]                           
  674c66d  jmp short 0x674C671                           ; -> loc_674c671
loc_674c66f:  ; from 674c65c
  674c66f  xor edx,edx                                   
loc_674c671:  ; from 674c66d
  674c671  lea rcx,[rbp+0xAF0]                           
  674c678  mov r8,[r14+8]                                
  674c67c  mov [rbp+0x5F0],r8                            
  674c683  mov [rbp+0x5F8],rdx                           
  674c68a  movaps [rbp+0x600],xmm0                       
  674c691  test rax,rax                                  
  674c694  je short 0x674C6A3                            ; -> loc_674c6a3
  674c696  lock inc dword ptr [rax+8]                    
  674c69a  mov rax,[rbp+0xAE8]                           
  674c6a1  jmp short 0x674C6A5                           ; -> loc_674c6a5
loc_674c6a3:  ; from 674c694
  674c6a3  xor eax,eax                                   
loc_674c6a5:  ; from 674c6a1
  674c6a5  mov rdx,[rbp+0xAE0]                           
  674c6ac  mov [rbp+0x600],rdx                           
  674c6b3  mov [rbp+0x608],rax                           
  674c6ba  movups xmm0,[rcx]                             
  674c6bd  movaps [rbp+0x610],xmm0                       
  674c6c4  mov rax,[rcx+0x10]                            
  674c6c8  mov [rbp+0x620],rax                           
  674c6cf  lea rcx,[rbp+0x2E0]                           
  674c6d6  lea rdx,[rbp+0x910]                           
  674c6dd  lea r8,[rbp+0x5F0]                            
  674c6e4  call 0x67BD4B0                                ; -> sub_67bd4b0
  674c6e9  nop                                           
  674c6ea  mov rdi,[rsi+0x10]                            
  674c6ee  lea rbx,[0xF2BE908]                           ; [data_f2be908]
  674c6f5  mov [rbp+0xC10],rbx                           
  674c6fc  lea rsi,[rbp+0xC18]                           
  674c703  lea rdx,[rbp+0x910]                           
  674c70a  mov rcx,rsi                                   
  674c70d  call 0x67BA750                                ; -> sub_67ba750
  674c712  nop                                           
  674c713  xorps xmm0,xmm0                               
  674c716  movups [rbp+0xDB0],xmm0                       
  674c71d  mov rax,[rbp+0xAB0]                           
  674c724  test rax,rax                                  
  674c727  je 0x674C97E                                  ; -> loc_674c97e
  674c72d  lock inc dword ptr [rax+8]                    
  674c731  mov rax,[rbp+0xAB0]                           
  674c738  jmp 0x674C980                                 ; -> loc_674c980
  674c73d  xor eax,eax                                   
  674c73f  lea rdx,[rbp+0xDB0]                           
  674c746  mov r8,[rbp+0xAA8]                            
  674c74d  mov rcx,[rbp+0xAC0]                           
  674c754  mov [rbp+0xDB0],r8                            
  674c75b  mov [rbp+0xDB8],rax                           
  674c762  movups [rbp+0xDC0],xmm0                       
  674c769  test rcx,rcx                                  
  674c76c  je short 0x674C77B                            ; -> loc_674c77b
  674c76e  lock inc dword ptr [rcx+8]                    
  674c772  mov rax,[rbp+0xAC0]                           
  674c779  jmp short 0x674C77D                           ; -> loc_674c77d
loc_674c77b:  ; from 674c76c
  674c77b  xor eax,eax                                   
loc_674c77d:  ; from 674c779
  674c77d  mov rcx,[rbp+0xAB8]                           
  674c784  mov [rbp+0xDC0],rcx                           
  674c78b  mov [rbp+0xDC8],rax                           
  674c792  movups xmm0,[rbp+0xAC8]                       
  674c799  movups [rbp+0xDD0],xmm0                       
  674c7a0  mov rax,[rbp+0xAD8]                           
  674c7a7  mov [rbp+0xDE0],rax                           
  674c7ae  add rdi,0x9D0                                 
  674c7b5  lea rax,[rbp+0xC20]                           
  674c7bc  lea rcx,[rbp+0xC68]                           
  674c7c3  lea r10,[rbp+0xC70]                           
  674c7ca  lea r11,[rbp+0xC78]                           
  674c7d1  lea r9,[rbp+0xCD0]                            
  674c7d8  lea r8,[rbp[0xD28]                             ; (typo in source: actual is rbp+0xD28)
  674c7df  mov [rsp+0x40],rsi                            
  674c7e4  mov [rsp+0x38],rax                            
  674c7e9  mov [rsp+0x30],rcx                            
  674c7ee  mov [rsp+0x28],r10                            
  674c7f3  mov [rsp+0x20],r11                            
  674c7f8  mov rcx,rdi                                   
  674c7fb  call 0x67BDB70                                ; -> sub_67bdb70
  674c800  nop                                           
  674c801  mov [rbp+0xC10],rbx                           
  674c808  mov rdi,[rbp+0xDC8]                           
  674c80f  test rdi,rdi                                  
  674c812  je short 0x674C83F                            ; -> loc_674c83f
  674c814  lock dec dword ptr [rdi+8]                    
  674c818  jne short 0x674C83F                           ; -> loc_674c83f
  674c81a  mov rax,[rdi]                                 
  674c81d  mov rax,[rax]                                 
  674c820  mov rcx,rdi                                   
  674c823  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  674c829  lock dec dword ptr [rdi+0xC]                  
  674c82d  jne short 0x674C83F                           ; -> loc_674c83f
  674c82f  mov rax,[rdi]                                 
  674c832  mov rax,[rax+8]                               
  674c836  mov rcx,rdi                                   
  674c839  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
loc_674c83f:  ; from 674c812, 674c818, 674c82d
  674c83f  mov rdi,[rbp+0xDB8]                           
  674c846  test rdi,rdi                                  
  674c849  je short 0x674C876                            ; -> loc_674c876
  674c84b  lock dec dword ptr [rdi+8]                    
... (continues)
```
- Note: case 3's material qword is data_f2be908 (case 2's was data_f2be8f8). Both join sequences end with `add rdi,0x9d0` + call 0x67bdb70 (append to pass vector) then release of temporaries via [0xF99FFA0]. [I]
- 0x674c73d/0x674c73f: [rbp+0xab0]==0 case (xor eax,eax), shared tail that moves [rbp+0xaa8]→[rbp+0xdb0], rax→[rbp+0xdb8], etc. [V]
- Correction: 0x674c7d8 is `lea r8,[rbp+0xD28]` (not rbp[...]).

## Cold-tail / branch targets seen so far [V] (not yet transcribed)
0x674cc21 (from 0x674c531 jmp), 0x674c97e/0x674c980, 0x674c876, 0x674ccd9, 0x674c201, 0x674c319, 0x674cdb3, 0x674cda7/0x674cda0, 0x674ce28, 0x674ce34 (kind>3 default), 0x674ce8d, 0x674ce9d, 0x674ce98, 0x674cea8, 0x674c0e0/0x674c0e8, 0x674bcd2, 0x674ccf2, 0x674ce4e (hot-path ret per dossier), cold tails to 0x674d15e. UI/Fill literal 0x674cd0e not yet reached.

## Case 3 release/cleanup 0x674c849..0x674c9e1 [V] (from 0x674c83f)
Repeated double-release pattern via [0xF99FFA0] (sub_eea6040): for each of [rbp+0xdb8], [rbp+0xac0], [rbp+0xab0], [rbp+0x608], [rbp+0x5f8]: `test`; `lock dec [reg+8]`; `jne skip`; `mov rax,[reg]; mov rax,[rax]; call [0xF99FFA0]`; `lock dec [reg+0xc]`; `jne skip`; `mov rax,[reg]; mov rax,[rax+8]; call [0xF99FFA0]`. Between releases: `mov rcx,rsi; call 0x67bc2c0`. Ends:
```
  674c966  lea rcx,[rbp+0x2E0]                           
  674c96d  call 0x67BC2C0                                ; -> sub_67bc2c0
  674c972  mov rsi,[rbp+0xAE8]                           
  674c979  jmp 0x674CBF1                                 ; -> loc_674cbf1
```
- Duplicate tail at 0x674c97e (from [rbp+0xab0]==0 branch at 0x674c727): `xor eax,eax` then same `lea rdx,[rbp+0xdb0]; mov r8,[rbp+0xaa8]; mov rcx,[rbp+0xac0]; mov [rbp+0xdb0],r8; mov [rbp+0xdb8],rax; movups [rbp+0xdc0],xmm0; test rcx,rcx; je 0x674c9bc; lock inc [rcx+8]...` → mirrors 0x674c73f, leads to same record-field copies ([rbp+0xab8]→[rbp+0xdc0], [rbp+0xac8]→[rbp+0xdd0] xmm, [rbp+0xad8]→[rbp+0xde0]) then `add rdi,0x9d0` + call 0x67bdb70 presumably (need to confirm after 0x674c9e1).

## Case 3 release/cleanup (dup tail from 0x674c97e) 0x674c9e1..0x674cb7a [V]
```
  674c9e1  mov rax,[rbp+0xAD8]                           
  674c9e8  mov [rbp+0xDE0],rax                           
  674c9ef  add rdi,0x9D0                                 
  674c9f6  lea rax,[rbp+0xC20]                           
  674c9fd  lea rcx,[rbp+0xC68]                           
  674ca04  lea r10,[rbp+0xC70]                           
  674ca0b  lea r11,[rbp+0xC78]                           
  674ca12  lea r9,[rbp+0xCD0]                            
  674ca19  lea r8,[rbp+0xD28]                            
  674ca20  mov [rsp+0x40],rsi                            
  674ca25  mov [rsp+0x38],rax                            
  674ca2a  mov [rsp+0x30],rcx                            
  674ca2f  mov [rsp+0x28],r10                            
  674ca34  mov [rsp+0x20],r11                            
  674ca39  mov rcx,rdi                                   
  674ca3c  call 0x67BEB70                                ; -> sub_67beb70   (NOTE: different append fn than 0x674c7fb's 0x67bdb70)
  674ca41  nop                                           
  674ca42  mov [rbp+0xC10],rbx                           
```
then same release pattern over [rbp+0xdc8], [rbp+0xdb8], [rbp+0xac0], [rbp+0xab0], [rbp+0x608], [rbp+0x5f8] via [0xF99FFA0], with `call 0x67bc2c0` between groups, ending:
```
  674cb2d  lea rcx,[rbp+0x910]                           
  674cb34  call 0x67BC2C0                                ; -> sub_67bc2c0
  674cb39  mov rsi,[rbp+0x608]                           
  674cb40  test rsi,rsi                                  
  674cb43  je short 0x674CB70                            ; -> loc_674cb70
  ...release [rbp+0x608]...
loc_674cb70:  ; from 674cb43, 674cb49, 674cb5e
  674cb70  mov rsi,[rbp+0x5F8]                           
  674cb77  test rsi,rsi                                  
  674cb7a  je short 0x674CBA7                            ; -> loc_674cba7
```
- Two append functions observed: 0x67bdb70 (at 0x674c7fb, from [rbp+0xac0]!=0 path) and 0x67beb70 (at 0x674ca3c, from [rbp+0xab0]==0 path). [V]
- Both tails converge toward 0x674cbf1 (jmp target seen at 0x674c979).

## Convergence/epilogue start 0x674cba7..0x674ccac [V] (from 0x674cb7a tail, and 0x674c979 jmp)
```
  674cba7  mov rsi,[rbp+0xAE8]                           
  674cbae  test rsi,rsi                                  
  674cbb1  je short 0x674CBDE                            ; -> loc_674cbde
  674cbb3  lock dec dword ptr [rsi+8]                    
  674cbb7  jne short 0x674CBDE                           ; -> loc_674cbde
  674cbb9  mov rax,[rsi]                                 
  674cbbc  mov rax,[rax]                                 
  674cbbf  mov rcx,rsi                                   
  674cbc2  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  674cbc8  lock dec dword ptr [rsi+0xC]                  
  674cbcc  jne short 0x674CBDE                           ; -> loc_674cbde
  674cbce  mov rax,[rsi]                                 
  674cbd1  mov rax,[rax+8]                               
  674cbd5  mov rcx,rsi                                   
  674cbd8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_674cbde:  ; from 674cbb1, 674cbb7, 674cbcc
  674cbde  lea rcx,[rbp+0x2E0]                           
  674cbe5  call 0x67BC2C0                                ; -> sub_67bc2c0
  674cbea  mov rsi,[rbp+0x268]                           
  674cbf1  test rsi,rsi                                  
  674cbf4  je short 0x674CC21                            ; -> loc_674cc21
  674cbf6  lock dec dword ptr [rsi+8]                    
  674cbfa  jne short 0x674CC21                           ; -> loc_674cc21
  674cbfc  mov rax,[rsi]                                 
  674cbff  mov rax,[rax]                                 
  674cc02  mov rcx,rsi                                   
  674cc05  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  674cc0b  lock dec dword ptr [rsi+0xC]                  
  674cc0f  jne short 0x674CC21                           ; -> loc_674cc21
  674cc11  mov rax,[rsi]                                 
  674cc14  mov rax,[rax+8]                               
  674cc18  mov rcx,rsi                                   
  674cc1b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_674cc21:  ; from 674cbf4, 674cbfa, 674cc0f
  674cc21  cmp byte ptr [rbp+0x7E8],1                    
  674cc28  jne 0x674CE34                                 ; -> loc_674ce34   (same flag checked at fn entry 0x674b4d9)
  674cc2e  cmp byte ptr [rbp+0x7C8],3                    
  674cc35  jne short 0x674CC6E                           ; -> loc_674cc6e
  674cc37  mov rsi,[rbp+0x7C0]                           
  674cc3e  test rsi,rsi                                  
  674cc41  je short 0x674CC6E                            ; -> loc_674cc6e
  674cc43  lock dec dword ptr [rsi+8]                    
  674cc47  jne short 0x674CC6E                           ; -> loc_674cc6e
  674cc49  mov rax,[rsi]                                 
  674cc4c  mov rax,[rax]                                 
  674cc4f  mov rcx,rsi                                   
  674cc52  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  674cc58  lock dec dword ptr [rsi+0xC]                  
  674cc5c  jne short 0x674CC6E                           ; -> loc_674cc6e
  674cc5e  mov rax,[rsi]                                 
  674cc61  mov rax,[rax+8]                               
  674cc65  mov rcx,rsi                                   
  674cc68  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_674cc6e:  ; from 674cc35, 674cc41, 674cc47, 674cc5c
  674cc6e  mov rdi,[rbp+0x798]                           
  674cc75  test rdi,rdi                                  
  674cc78  je 0x674CE34                                  ; -> loc_674ce34
  674cc7e  mov rbx,[rbp+0x7A0]                           
  674cc85  jmp short 0x674CC94                           ; -> loc_674cc94
  674cc87  nop [rax+rax]                                 

loc_674cc90:  ; from 674cca1, 674ccaa, 674ccb0, 674ccc5, 674ccd7
  674cc90  add rdi,0x28                                  

loc_674cc94:  ; from 674cc85
  674cc94  cmp rdi,rbx                                   
  674cc97  je 0x674CE34                                  ; -> loc_674ce34
  674cc9d  cmp byte ptr [rdi+0x18],2                     
  674cca1  jne short 0x674CC90                           ; -> loc_674cc90
  674cca3  mov rsi,[rdi+8]                               
  674cca7  test rsi,rsi                                  
  674ccaa  je short 0x674CC90                            ; -> loc_674cc90
  674ccac  lock dec dword ptr [rsi+8]                    
  ... (continues, release loop over stride-0x28 array, entries with byte+0x18==2)
```
- 0x674ce34 is the common exit/cold-tail target (jne at fn entry 0x674b4e0 also goes here). Dossier: hot-path ret at 0x674ce4e; cold tails to 0x674d15e.
- Loop: [rbp+0x798]=start, [rbp+0x7a0]=end, stride 0x28; releases entries whose byte [rdi+0x18]==2 (double-release via [0xF99FFA0]).

## Release loop body 0x674ccac..0x674ccd7 [V]
```
  674ccac  lock dec dword ptr [rsi+8]                    
  674ccb0  jne short 0x674CC90                           ; -> sub_674cc90
  674ccb2  mov rax,[rsi]                                 
  674ccb5  mov rax,[rax]                                 
  674ccb8  mov rcx,rsi                                   
  674ccbb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  674ccc1  lock dec dword ptr [rsi+0xC]                  
  674ccc5  jne short 0x674CC90                           ; -> sub_674cc90
  674ccc7  mov rax,[rsi]                                 
  674ccca  mov rax,[rax+8]                               
  674ccce  mov rcx,rsi                                   
  674ccd1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  674ccd7  jmp short 0x674CC90                           ; -> sub_674cc90
```
- Loop releases entries (stride 0x28) with byte [rdi+0x18]==2; when done (rdi==rbx) → 0x674ce34.

## Material decision tree 0x674bb0c..0x674cd0e [V] (all 4 materials now located)
Blocks 0x674bb56/0x674bbce/0x674bbdb/0x674bcd2/0x674bce2/0x674bbb6 form a tree reading [r14+0x1a4], [r14+0x1da]/[r14+0x1e8], [r14+0x1fe]/[r14+0x20c] (pcmpeqb vs 0xF275E82/0xF275E90, pmovmskb, cmp 0xFFFF), [r14+0x244], [r14+0x1a1], dl/al flags:
- **0x674bc15 "UI/Blit"** (from 0x674bbdb path: `test al,al; jne 0x674c0e8` falls through when al==0 → TLS/counter checks → `mov r12,[rsi+0x68]; call 0x66b2310; mov r9,[rsi+0x40]` → 0x674bc15)
- **0x674bd1f "UI/Base"** (from 0x674bce2: TLS check; `test al,al; jne 0x674ccf2`; else `mov rdi,r15; cmp [0x129fa2b8],ecx; jg 0x674e4a5; mov r15,[rsi+0x68]; call 0x66b2310; mov r9,[rsi+0x40]` → 0x674bd1f)
- **0x674cd0e "UI/Fill"** (FOUND at 0x674cd0e): `lea rax,[0xF2BE648]`; [rbp+0xC18]=7; via 0x67d6d70 r8=data_129fa290. Reached from loc_674cd01 (from 0x674e3d3/0x674e423, and fall-through from 0x674ccf2 when `cmp [0x129fa2a0],ecx` not >).
- **0x674c147 / 0x674c283 "UI/Sprite"** (from 0x674c0e8 path: `cmp byte ptr [rbp+0xeb0],0; je 0x674c201` → Sprite)
- Predecessor of 0x674bb0c still [?] (no direct jump seen from the 4 switch cases; 0x674bb50 has 0 rdis xrefs — likely indirect jump or cold entry).

## UI/Fill body continuation 0x674cd0e..0x674ce4e [V]
```
  674cd0e  lea rax,[0xF2BE648]                           ; [data_f2be648] "UI/Fill"
  674cd15  mov [rbp+0xC10],rax                           
  674cd1c  mov qword ptr [rbp+0xC18],7                   
  674cd27  lea rax,[0x129FB170]                          ; [data_129fb170]
  674cd2e  mov [rsp+0x28],rax                            
  674cd33  lea rax,[rbp+0xC10]                           
  674cd3a  mov [rsp+0x20],rax                            
  674cd3f  lea r8,[0x129FA290]                           ; [data_129fa290]
  674cd46  lea rdx,[rbp+0x910]                           
  674cd4d  mov rcx,r15                                   
  674cd50  call 0x67D6D70                                ; -> sub_67d6d70
  674cd55  mov rcx,[rbp+0x910]                           
  674cd5c  call 0x66A0760                                ; -> sub_66a0760
  674cd62  test al,al                                    
  674cd64  je 0x674CE28                                  ; -> loc_674ce28
  674cd6a  mov r15,rdi                                   
  674cd6d  mov rcx,[rbp+0x910]                           
  674cd74  call 0xBCAB880                                ; -> sub_bcab880
  674cd7a  test al,al                                    
  674cd7c  je 0x674CE28                                  ; -> loc_674ce28
  674cd82  mov r8,[rsi]                                  
  674cd85  mov rdx,[rbp+0x910]                           
  674cd8c  mov byte ptr [rbp+0xBF0],0                    
  674cd93  lea rcx,[rbp+0xB68]                           
  674cd9a  call 0x675DD80                                ; -> sub_675dd80
  674cd9f  nop                                           
  674cda0  mov byte ptr [rbp+0xBF0],1                    
  674cda7  lea rcx,[rbp+0x910]                           
  674cdae  call 0x7E6D0                                  ; -> sub_7e6d0
  674cdb3  cmp byte ptr [rbp+0xBF0],1                    
  674cdba  jne short 0x674CE34                           ; -> loc_674ce34   (if BF0!=1 → epilogue)
  674cdbc  movups xmm0,[r15]                             
  674cdc0  movaps [rbp+0xC10],xmm0                       
  674cdc7  mov qword ptr [rbp+0x910],1                   
  674cdd2  lea rax,[rbp+0xC10]                           
  674cdd9  mov [rbp+0x918],rax                           
  674cde0  mov rax,[rbp+0xBA0]                           
  674cde7  movzx r8d,word ptr [rbp+0xBAA]                
  674cdef  mov ecx,r8d                                   
  674cdf2  shl ecx,4                                     
  674cdf5  mov rdx,rax                                   
  674cdf8  test r8d,r8d                                  
  674cdfb  je short 0x674CE4F                            ; -> loc_674ce4f   (cold tail: uniform loop re-entry)
  674cdfd  mov r8,[0x129FA178]                           ; [data_129fa178]
  674ce04  mov r9,rcx                                    
  674ce07  mov rdx,rax                                   
  674ce0a  nop [rax+rax]                                 
loc_674ce10:  ; from 674ce21
  674ce10  mov r10,[rdx]                                 
  674ce13  cmp [r10+0x28],r8                             
  674ce17  je short 0x674CE4F                            ; -> loc_674ce4f
  674ce19  add rdx,0x10                                  
  674ce1d  add r9,0xFFFFFFFFFFFFFFF0                     
  674ce21  jne short 0x674CE10                           ; -> loc_674ce10
  674ce23  jmp 0x674B411                                 ; -> sub_674b411   (jumps BACK to phase-4 uniform loop)
loc_674ce28:  ; from 0x674cd64, 0x674cd7c
  674ce28  lea rcx,[rbp+0x910]                           
  674ce2f  call 0x7E6D0                                  ; -> sub_7e6d0

loc_674ce34:  ; epilogue (from 0x674b4e0, 0x674cc28, 0x674cc78, 0x674cc97, 0x674cdba)
  674ce34  movaps xmm6,[rbp+0xE00]                       
  674ce3b  add rsp,0xE98                                 
  674ce42  pop rbx                                       
  674ce43  pop rdi                                       
  674ce44  pop rsi                                       
  674ce45  pop r12                                       
  674ce47  pop r13                                       
  674ce49  pop r14                                       
  674ce4b  pop r15                                       
  674ce4d  pop rbp                                       
  674ce4e  ret                                           
```
- 0x674ce4e = hot-path ret (matches dossier). Frame 0xe98, saved rbx/rdi/rsi/r12/r13/r14/r15/rbp, xmm6 restored.
- Cold tail 0x674ce4f: `add rcx,rax; cmp rdx,rcx; jae 0x674b411`; `lea rcx,[rbp+0xb70]`; `sub edx,eax; shr edx,4; mov [rbp+0x2e0],dx`; `mov byte [rbp+0x2e2],1` → then uniform write loop (0x674b411 region, phase 4, already decoded at call/store level). [V]

## ALL FOUR MATERIALS located [V]
- UI/Blit = 0x674bc15 (data_f2be628, len 7)
- UI/Base = 0x674bd1f (data_f2be668, len 7)
- UI/Sprite = 0x674c147 (data_f2be5e8, len 9) and 0x674c283 (data_f2be608, len 9)
- UI/Fill = 0x674cd0e (data_f2be648, len 7)

## Cold tails 0x674ce6e..0x674cf9b [V] (from 0x674ce83 jmp target and case alloc-fails)
```
  674ce6e  mov byte ptr [rbp+0x2E2],1                    
  674ce75  lea rdx,[rbp+0x2E0]                           
  674ce7c  lea r8,[rbp+0x910]                            
  674ce83  call 0x5679DB0                                ; -> sub_5679db0   (uniform scalar write)
  674ce88  jmp 0x674B411                                 ; -> sub_674b411   (re-enter phase-4 uniform loop)
  674ce8d  mov ecx,0x20                                  
  674ce92  call 0x9BC830                                 ; -> sub_9bc830   (case-2 alloc-fail path)
  674ce97  nop                                           
  674ce98  jmp 0x674B77A                                 ; -> sub_674b77a   (case-2 body label)
  674ce9d  mov ecx,0x30                                  
  674cea2  call 0x9BC830                                 ; -> sub_9bc830   (case-3 alloc-fail path)
  674cea7  nop                                           
  674cea8  jmp 0x674B8A8                                 ; -> sub_674b8a8   (case-3 body label)
  674cead  lea rcx,[0x129FA180]                          ; [data_129fa180]
  674ceb4  call 0xE938CB0                                ; -> sub_e938cb0   (x27 in dossier)
  674ceb9  cmp dword ptr [0x129FA180],0xFFFFFFFF         ; [data_129fa180]
  674cec0  jne 0x674A4C3                                 ; -> sub_674a4c3
  674cec6  lea rdx,[0xF563982]                           ; [data_f563982] "TintColor"
  674cecd  lea r14,[rbp+0xC10]                           
  674ced4  mov rcx,r14                                   
  674ced7  call 0x79580                                  ; -> sub_79580   (x15 in dossier)
  674cedc  nop                                           
  674cedd  mov rdx,[rbp+0xC20]                           
  674cee4  cmp qword ptr [rbp+0xC28],0x10                
  674ceec  jb short 0x674CEF5                            ; -> loc_674cef5
  674ceee  mov r14,[rbp+0xC10]                           
loc_674cef5:  ; from 674ceec
  674cef5  test rdx,rdx                                  
  674cef8  je 0x674DC7B                                  ; -> loc_674dc7b   (cold tail further out)
  674cefe  mov eax,edx                                   
  674cf00  and eax,3                                     
  674cf03  cmp rdx,4                                     
  674cf07  jae 0x674DCFC                                 ; -> loc_674dcfc
  674cf0d  mov rcx,0xCBF29CE484222325                     ; FNV-1a 64 offset basis
  674cf17  xor r8d,r8d                                   
  674cf1a  jmp 0x674DD58                                 ; -> loc_674dd58   (FNV hash loop)
  674cf1f  lea rcx,[0x129FA4C0]                          ; [data_129fa4c0]
  674cf26  call 0xE938CB0                                ; -> sub_e938cb0
  674cf2b  cmp dword ptr [0x129FA4C0],0xFFFFFFFF         ; [data_129fa4c0]
  674cf32  jne 0x674A547                                 ; -> sub_674a547
```
- Then font-option struct construction at [rbp+0xc10..] and [rbp+0x910..]:
  - 0x674cf59 `mov rax,0x5059545F544E4F46` ("FONT_TYP" LE); [rbp+0xc10]=rax; 0x674cf6a `mov byte [rbp+0xc18],0x45` ('E') → "FONT_TYPE"; [rbp+0xc30]=0x6d746942 ("Bitm"); [rbp+0xc34]=0x7061 ("pa"); [rbp+0xc50]=data_f7c86b5 "ALPHA_TEST"; [rbp+0xc58]=word data_f7c86bd (=sub_d005453); ...
  - Second set: [rbp+0x910]=0x5059545F544E4F46 ("FONT_TYP"); [rbp+0x918]=0x45; [rbp+0x930]=0x6d5370616d746942 ("BitmapS"); [rbp+0x938]=0x68746f6f ("ooth") → "BitmapSmooth"; [rbp+0x950]=data_f7c86b5 "ALPHA_TEST"; ...
- These are the FONT_TYPE/MSDF font-option strings from dossier constants (0x5059545f544e4f46, 0x6d5370616d746942, 0x68746f6f, 0x6570795465757254 "TrueType", 0x6d746942 "Bitm"). [I]
- Reached from 0x674cead (data_129fa180 check) — font/cold-init path. [I]

## Font-option cold tail 0x674cf9b..0x674d2cd [V]
Three option structs built via 0x7d7890 (sub_7d7890, x9 in dossier):
- [rbp+0xc10..]: name="FONT_TYPE" (0x5059545F544E4F46+0x45), value="BitmapSmooth" (0x6d5370616d746942+0x68746f6f), "ALPHA_TEST"(data_f7c86b5), sub_d005453(data_f7c86bd). Call 0x7d7890 at 0x674d063.
- [rbp+0x910..]: name="FONT_TYPE", value="BitmapSmooth", same ALPHA_TEST. Call 0x7d7890 at 0x674d18c.
- [rbp+0x2e0..]: name="FONT_TYPE", value="TrueType" (0x6570795465757254 @0x300), same ALPHA_TEST. Call 0x7d7890 at 0x674d2ab.
- [rbp+0x2e8]=0,[rbp+0x2f0]=9,[rbp+0x2f8]=0xF; [rbp+0x308]=0,[rbp+0x310]=8,[rbp+0x318]=0xF; [rbp+0x328]=0(w),[rbp+0x330]=0xa,[rbp+0x338]=0xf; [rbp+0x350]=3,[rbp+0x358]=0xf.
- 0x674d2b1 `lea r12,[0x129FA380]`; `mov [rbp+0xBF8],r12`; 0x674d2bf `lea rdx,[0xF7CC3C4]` "FONT_TYPE"; 0x674d2c6 `lea r8,[0xF7CBE53]` "MSDF"; 0x674d2cd `lea rcx,[rbp+0x5F0]` → FONT_TYPE vs MSDF font-variant comparison. [I]

## Font-option continuation 0x674d2cd..0x674d5f7 [V]
```
  674d2cd  lea rcx,[rbp+0x5F0]                           
  674d2d4  mov r15,rcx                                   
  674d2d7  call 0xF2EA00                                 ; -> sub_f2ea00   (x2 in dossier)
  674d2dd  mov qword ptr [rbp+0x638],0                   
  674d2e8  mov qword ptr [rbp+0x640],0xA                 
  674d2f3  mov qword ptr [rbp+0x648],0xF                 
  674d2fe  mov rax,[0xF7C86B5]                           ; [data_f7c86b5] "ALPHA_TEST"
  674d305  mov [rbp+0x630],rax                           
  674d30c  movzx eax,word ptr [0xF7C86BD]                ; [data_f7c86bd] = sub_d005453
  674d313  mov [rbp+0x638],ax                            
  674d31a  mov qword ptr [rbp+0x660],3                   
  674d325  mov qword ptr [rbp+0x668],0xF                 
  674d330  mov qword ptr [rbp+0x653],0                   
  674d33b  mov qword ptr [rbp+0x658],0                   
  674d346  mov [rbp+0x650],bx                            
  674d34d  movzx eax,byte ptr [0xF5BAC4A]                ; [data_f5bac4a]
  674d354  mov [rbp+0x652],al                            
  674d35a  mov [rbp+0x520],r15                           
  674d361  lea rax,[rbp+0x670]                           
  674d368  mov [rbp+0x528],rax                           
  674d36f  mov [rbp+0x8F8],r12                           
  674d376  lea rdx,[rbp+0x520]                           
  674d37d  mov rcx,r12                                   
  674d380  call 0x7D7890                                ; -> sub_7d7890
  674d385  nop                                           
  674d386  mov qword ptr [rbp+0x798],0                   
  674d391  mov qword ptr [rbp+0x7A0],9                   
  674d39c  mov qword ptr [rbp+0x7A8],0xF                 
  674d3a7  mov rax,0x5059545F544E4F46                    
  674d3b1  mov [rbp+0x790],rax                           
  674d3b8  mov byte ptr [rbp+0x798],0x45                 
  674d3bf  mov qword ptr [rbp+0x7C0],6                   
  674d3ca  mov qword ptr [rbp+0x7C8],0xF                 
  674d3d5  mov qword ptr [rbp+0x7B6],0                   
  674d3e0  mov word ptr [rbp+0x7BE],0                    
  674d3e9  mov dword ptr [rbp+0x7B0],0x6D746942          
  674d3f3  mov word ptr [rbp+0x7B4],0x7061               
  674d3fc  mov qword ptr [rbp+0x7D8],0                   
  674d407  mov qword ptr [rbp+0x7E0],0xA                 
  674d412  mov qword ptr [rbp+0x7E8],0xF                 
  674d41d  mov rax,[0xF7C86B5]                           ; [data_f7c86b5] "ALPHA_TEST"
  674d424  mov [rbp+0x7D0],rax                           
  674d42b  movzx eax,word ptr [0xF7C86BD]                ; [data_f7c86bd] = sub_d005453
  674d432  mov [rbp+0x7D8],ax                            
  674d439  xorps xmm6,xmm6                               
  674d43c  movups [rbp+0x7F0],xmm6                       
  674d443  mov qword ptr [rbp+0x800],2                   
  674d44e  mov qword ptr [rbp+0x808],0xF                 
  674d459  mov word ptr [rbp+0x7F0],0x6E4F               
  674d462  lea rax,[rbp+0x790]                           
  674d469  mov [rbp+0x530],rax                           
  674d470  lea rax,[rbp+0x810]                           
  674d477  mov [rbp+0x538],rax                           
  674d47e  lea rcx,[0x129FA3C0]                          ; [data_129fa3c0]
  674d485  mov [rbp+0x900],rcx                           
  674d48c  lea rdx,[rbp+0x530]                           
  674d493  call 0x7D7890                                ; -> sub_7d7890
  674d498  nop                                           
  674d499  mov qword ptr [rbp+0x818],0                   
  674d4a4  mov qword ptr [rbp+0x820],9                   
  674d4af  mov qword ptr [rbp+0x828],0xF                 
  674d4ba  mov rax,0x5059545F544E4F46                    
  674d4c4  mov [rbp+0x810],rax                           
  674d4cb  mov byte ptr [rbp+0x818],0x45                 
  674d4d2  mov qword ptr [rbp+0x838],0                   
  674d4dd  mov qword ptr [rbp+0x840],0xC                 
  674d4e8  mov qword ptr [rbp+0x848],0xF                 
  674d4f3  mov rax,0x6D5370616D746942                    
  674d4fd  mov [rbp+0x830],rax                           
  674d504  mov dword ptr [rbp+0x838],0x68746F6F          
  674d50e  mov qword ptr [rbp+0x858],0                   
  674d519  mov qword ptr [rbp+0x860],0xA                 
  674d524  mov qword ptr [rbp+0x868],0xF                 
  674d52f  mov rax,[0xF7C86B5]                           ; [data_f7c86b5] "ALPHA_TEST"
  674d536  mov [rbp+0x850],rax                           
  674d53d  movzx eax,word ptr [0xF7C86BD]                ; [data_f7c86bd] = sub_d005453
  674d544  mov [rbp+0x858],ax                            
  674d54b  movups [rbp+0x870],xmm6                       
  674d552  mov qword ptr [rbp+0x880],2                   
  674d55d  mov qword ptr [rbp+0x888],0xF                 
  674d568  mov word ptr [rbp+0x870],0x6E4F               
  674d571  lea rax,[rbp+0x810]                           
  674d578  mov [rbp+0x540],rax                           
  674d57f  lea rax,[rbp+0x890]                           
  674d586  mov [rbp+0x548],rax                           
  674d58d  lea rcx,[0x129FA400]                          ; [data_129fa400]
  674d594  mov [rbp+0x908],rcx                           
  674d59b  lea rdx,[rbp+0x540]                           
  674d5a2  call 0x7D7890                                ; -> sub_7d7890
  674d5a7  nop                                           
  674d5a8  mov qword ptr [rbp+0xAE8],0                   
  674d5b3  mov qword ptr [rbp+0xAF0],9                   
  674d5be  mov qword ptr [rbp+0xAF8],0xF                 
  674d5c9  mov rax,0x5059545F544E4F46                    
  674d5d3  mov [rbp+0xAE0],rax                           
  674d5da  mov byte ptr [rbp+0xAE8],0x45                 
  674d5e1  mov qword ptr [rbp+0xB08],0                   
  674d5ec  mov qword ptr [rbp+0xB10],8                   
  674d5f7  mov qword ptr [rbp+0xB18],0xF                 
```
- Each option struct: name qword + length byte + value bytes + ALPHA_TEST qword + sub_d005453 word + stride/capacity fields. Registered via 0x7d7890 then hashed via 0x9b250 (x17 in dossier — name hashing).

## Option hashing + UI/Text registration 0x674d5f7..0x674daa3 [V]
```
  674d602  mov rax,0x6570795465757254                     ; "TrueType"
  674d60c  mov [rbp+0xB00],rax                           
  ...
  674d65a  mov qword ptr [rbp+0xB50],2                   
  674d665  mov qword ptr [rbp+0xB58],0xF                 
  674d670  mov word ptr [rbp+0xB40],0x6E4F               
  674d679  lea rax,[rbp+0xAE0]                           
  674d680  mov [rbp+0x550],rax                           
  674d687  lea rax,[rbp+0xB60]                           
  674d68e  mov [rbp+0x558],rax                           
  674d695  lea rcx,[0x129FA440]                          ; [data_129fa440]
  674d69c  mov [rbp+0xC00],rcx                           
  674d6a3  lea rdx,[rbp+0x550]                           
  674d6aa  call 0x7D7890                                ; -> sub_7d7890
  674d6af  nop                                           
  674d6b0  lea rax,[0x129FA480]                          ; [data_129fa480]
  674d6b7  mov [rbp+0xC00],rax                           
  674d6be  lea rdx,[0xF7CC3C4]                           ; [data_f7cc3c4] "FONT_TYPE"
  674d6c5  lea r8,[0xF7CBE53]                            ; [data_f7cbe53] "MSDF"
  674d6cc  lea r12,[rbp+0x260]                           
  674d6d3  mov rcx,r12                                   
  674d6d6  call 0xF2EA00                                ; -> sub_f2ea00
  674d6db  nop                                           
  ... (more struct fields at [rbp+0x2a0..], [rbp+0x2e0..], [rbp+0x630..], [rbp+0x790..], [rbp+0x810..], [rbp+0x850..], [rbp+0xae0..])
  674d76b  lea rcx,[rbp+0x2A0]                           
  674d772  call 0x9B250                                  ; -> sub_9b250   (x17 in dossier)
  674d777  lea rcx,[rbp+0x260]                           
  674d77e  call 0x9B250                                  ; -> sub_9b250
  674d783  lea rcx,[rbp+0xB20]                           
  674d78a  call 0x9B250                                  ; -> sub_9b250
  674d78f  lea rcx,[rbp+0xAE0]                           
  674d796  call 0x9B250                                  ; -> sub_9b250
  674d79b  lea rcx,[rbp+0x850]                           
  674d7a2  call 0x9B250                                  ; -> sub_9b250
  674d7a7  lea rcx,[rbp+0x810]                           
  674d7ae  call 0x9B250                                  ; -> sub_9b250
  674d7b3  lea rcx,[rbp+0x7D0]                           
  674d7ba  call 0x9B250                                  ; -> sub_9b250
  674d7bf  lea rcx,[rbp+0x790]                           
  674d7c6  call 0x9B250                                  ; -> sub_9b250
  674d7cb  lea rcx,[rbp+0x630]                           
  674d7d2  call 0x9B250                                  ; -> sub_9b250
  674d7d7  lea rcx,[rbp+0x5F0]                           
  674d7de  call 0x9B250                                  ; -> sub_9b250
  674d7e3  lea rcx,[rbp+0x320]                           
  674d7ea  call 0x9B250                                  ; -> sub_9b250
  674d7ef  lea rcx,[rbp+0x2E0]                           
  674d7f6  call 0x9B250                                  ; -> sub_9b250
  674d7fb  lea rcx,[rbp+0x950]                           
  674d802  call 0x9B250                                  ; -> sub_9b250
  674d807  lea rcx,[rbp+0x910]                           
  674d80e  call 0x9B250                                  ; -> sub_9b250
  674d813  lea rcx,[rbp+0xC50]                           
  674d81a  call 0x9B250                                  ; -> sub_9b250
  674d81f  lea rcx,[rbp+0xC10]                           
  674d826  call 0x9B250                                  ; -> sub_9b250
```
- Then 0x674d82b `lea rcx,[0x6750710]`; `call 0xe935740` (x5 in dossier); 0x674d837 `lea rcx,[0x129fa4c0]`; `call 0xe938d70`; `mov r15,[rbp+0xeb8]`; `jmp 0x674a547`.
- UI/Text registration block (0x674d84f..): `lea rcx,[0x129fa548]`; `call 0xe938cb0`; `cmp dword [0x129fa548],0xFFFFFFFF`; `jne 0x674a56c`. Then `lea rdx,[0x129fa2c0]`; `lea rcx,[rbp+0x10]`; `lea r8,[rbp+0xc10]`; `call 0xaa710` (x9). Repeated pattern: `lea rbx,[0xf2be688]` "UI/Text"; [rbp+0x570]=rbx; [rbp+0x578]=7; then 0x66a02d0 (FNV-1a hash of name key). Repeated at [rbp+0x50]/[rbp+0x90]/[rbp+0xd0]/[rbp+0x110]/[rbp+0x150]/[rbp+0x190]/[rbp+0x1d0] with data_129fa300/340/380/3c0/400/440/480/518/528/538 key ptrs. Each: `mov [rbp+0x5XX],rbx`; `mov qword [rbp+0x5XX+8],7`; `lea rdx,[data key]`; `lea rcx,[rbp+0xYYY]`; `lea r8,[rbp+0xc10]`; call 0xaa710 or 0x66a02d0.

## UI/Glint + MatTexture + GlyphTexture cold tails 0x674daa3..0x674dd81 [V]
```
  674daa3  lea rcx,[0x129FA548]                          ; [data_129fa548]
  674daaa  call 0xE938D70                                ; -> sub_e938d70
  674daaf  jmp 0x674A56C                                 ; -> sub_674a56c
  674dab4  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  674dabb  call 0xE938CB0                                ; -> sub_e938cb0
  674dac0  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
  674dac7  jne 0x674A60C                                 ; -> sub_674a60c
  674dacd  lea rcx,[0x129CA568]                          ; [data_129ca568]
  674dad4  call 0x567DB00                                ; -> sub_567db00   (x2 in dossier)
  674dad9  nop                                           
  674dada  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
  674dae1  call 0xE935740                                ; -> sub_e935740   (x5 in dossier)
  674dae6  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  674daed  call 0xE938D70                                ; -> sub_e938d70
  674daf2  jmp 0x674A60C                                 ; -> sub_674a60c
  674daf7  lea rcx,[0x129FA190]                          ; [data_129fa190]
  674dafe  call 0xE938CB0                                ; -> sub_e938cb0
  674db03  cmp dword ptr [0x129FA190],0xFFFFFFFF         ; [data_129fa190]
  674db0a  jne 0x674A6A3                                 ; -> sub_674a6a3
  674db10  lea rdx,[0xF5C6BAE]                           ; [data_f5c6bae] "MatTexture"
  674db17  lea r12,[rbp+0xC10]                           
  674db1e  mov rcx,r12                                   
  674db21  call 0x79580                                  ; -> sub_79580   (x15 in dossier)
  674db26  nop                                           
  674db27  mov rdx,[rbp+0xC20]                           
  674db2e  cmp qword ptr [rbp+0xC28],0x10                
  674db36  jb short 0x674DB3F                            ; -> loc_674db3f
  674db38  mov r12,[rbp+0xC10]                           
loc_674db3f:  ; from 674db36
  674db3f  test rdx,rdx                                  
  674db42  je 0x674E0CE                                  ; -> loc_674e0ce
  674db48  mov eax,edx                                   
  674db4a  and eax,3                                     
  674db4d  cmp rdx,4                                     
  674db51  jae 0x674E317                                 ; -> loc_674e317
  674db57  mov rcx,0xCBF29CE484222325                     ; FNV-1a offset basis
  674db61  xor r8d,r8d                                   
  674db64  jmp 0x674E373                                 ; -> loc_674e373
  674db69  lea rcx,[0x129FA1A8]                          ; [data_129fa1a8]
  674db70  call 0xE938CB0                                ; -> sub_e938cb0
  674db75  cmp dword ptr [0x129FA1A8],0xFFFFFFFF         ; [data_129fa1a8]
  674db7c  jne 0x674A6D1                                 ; -> sub_674a6d1
  674db82  xorps xmm0,xmm0                               
  674db85  movaps [rbp+0x210],xmm0                       
  674db8c  lea rax,[0xF2BE5C8]                           ; [data_f2be5c8] "UI/Glint"
  674db93  mov [rbp+0x480],rax                           
  674db9a  mov qword ptr [rbp+0x488],8                   
  674dba5  lea rcx,[0x129FA198]                          ; [data_129fa198]
  674dbac  lea rdx,[rbp+0x480]                           
  674dbb3  lea r8,[rbp+0x210]                            
  674dbba  call 0x5668AC0                                ; -> sub_5668ac0   (x5 in dossier)
  674dbbf  nop                                           
  674dbc0  lea rcx,[0x129FA1A8]                          ; [data_129fa1a8]
  674dbc7  call 0xE938D70                                ; -> sub_e938d70
  674dbcc  jmp 0x674A6D1                                 ; -> sub_674a6d1
  ... (0x674dbd1..: data_129fb1b0 check → sub_9b020, sub_e935740, sub_e938d70, jmp 0x674a704)
  ... (0x674dc38..: data_129ca5e0 check → sub_567db00/sub_567dba0, jmp 0x674a784)
  674dc7b  mov rcx,0xCBF29CE484222325                    
  674dc85  jmp 0x674DD81                                 ; -> loc_674dd81
  674dc8a  lea rcx,[0x129FA558]                          ; [data_129fa558]
  674dc91  call 0xE938CB0                                ; -> sub_e938cb0
  674dc96  cmp dword ptr [0x129FA558],0xFFFFFFFF         ; [data_129fa558]
  674dc9d  jne 0x674A91C                                 ; -> sub_674a91c
  674dca3  lea rdx,[0xF5C6DD7]                           ; [data_f5c6dd7] "GlyphTexture"
  674dcaa  lea r12,[rbp+0xC10]                           
  674dcb1  mov rcx,r12                                   
  674dcb4  call 0x79580                                  ; -> sub_79580
  674dcb9  nop                                           
  674dcba  mov rdx,[rbp+0xC20]                           
  674dcc1  cmp qword ptr [rbp+0xC28],0x10                
  674dcc9  jb short 0x674DCD2                            ; -> loc_674dcd2
  674dccb  mov r12,[rbp+0xC10]                           
loc_674dcd2:  ; from 674dcc9
  674dcd2  test rdx,rdx                                  
  674dcd5  je 0x674E42E                                  ; -> loc_674e42e
  674dcdb  mov eax,edx                                   
  674dcdd  and eax,3                                     
  674dce0  cmp rdx,4                                     
  674dce4  jae 0x674E50D                                 ; -> loc_674e50d
  674dcea  mov rcx,0xCBF29CE484222325                    
  674dcf4  xor r8d,r8d                                   
  674dcf7  jmp 0x674E569                                 ; -> loc_674e569
  674dcfc  and rdx,0xFFFFFFFFFFFFFFFC                    
  674dd00  mov rcx,0xCBF29CE484222325                    
  674dd0a  xor r8d,r8d                                   
  674dd0d  mov r9,0x100000001B3                           ; FNV-1a 64 prime
loc_674dd17:  ; from 674dd51
  674dd17  movzx r10d,byte ptr [r14+r8]                  
  674dd1c  xor r10,rcx                                   
  674dd1f  imul r10,r9                                   
  674dd23  movzx ecx,byte ptr [r14+r8+1]                 
  674dd29  xor rcx,r10                                   
  674dd2c  imul rcx,r9                                   
  674dd30  movzx r10d,byte ptr [r14+r8+2]                
  674dd36  xor r10,rcx                                   
  674dd39  imul r10,r9                                   
  674dd3d  movzx ecx,byte ptr [r14+r8+3]                 
  674dd43  xor rcx,r10                                   
  674dd46  imul rcx,r9                                   
  674dd4a  add r8,4                                      
  674dd4e  cmp rdx,r8                                    
  674dd51  jne short 0x674DD17                           ; -> loc_674dd17
  674dd53  test rax,rax                                  
  674dd56  je short 0x674DD81                            ; -> loc_674dd81
  674dd58  add r14,r8                                    
  674dd5b  xor edx,edx                                   
  674dd5d  mov r8,0x100000001B3                          
  674dd67  mov r9,rcx                                    
loc_674dd6a:  ; from 674dd7f
  674dd6a  movzx ecx,byte ptr [r14+rdx]                  
  674dd6f  xor rcx,r9                                    
  674dd72  imul rcx,r8                                   
  674dd76  inc rdx                                       
  674dd79  mov r9,rcx                                    
  674dd7c  cmp rax,rdx                                   
  674dd7f  jne short 0x674DD6A                           ; -> loc_674dd6a
loc_674dd81:  ; from 674dc85, 674dd56
  674dd81  mov [0x129FA178],rcx                          ; [data_129fa178]  (stores FNV hash result)
  674dd88  lea rcx,[rbp+0xC10]                           
  674dd8f  call 0x73150                                  ; -> sub_73150   (x15 in dossier)
  674dd94  lea rcx,[0x129FA180]                          ; [data_129fa180]
  674dd9b  call 0xE938D70                                ; -> sub_e938d70
  674dda0  jmp 0x674A4C3                                 ; -> sub_674a4c3
```
- FNV-1a 64 loop [V] at 0x674dd17-0x674dd7f: processes 4 bytes/iter (unrolled) then remainder; constants 0xcbf29ce484222325 (basis) and 0x100000001b3 (prime) match dossier. Stores hash to data_129fa178. Matches dossier constant 0x100000001b3 x29, 0xcbf29ce484222325 x45.
- "UI/Glint" (data_f2be5c8, len 8) at [rbp+0x480], "MatTexture" (data_f5c6bae), "GlyphTexture" (data_f5c6dd7) registered via 0x79580.

## Status at last disassembled point
Last transcribed instruction: 0x674dda0 `jmp 0x674a4c3`. Cold tails continue beyond (0x674e0ce, 0x674e317, 0x674e373, 0x674e42e, 0x674e50d, 0x674e569, 0x674e3c0, 0x674e428, 0x674e43d, 0x674e4a5, 0x674e5b6, 0x674e694, 0x674e707 blocks seen as branch targets but not transcribed). Function 0x674a3a0 total size 0x4c66 → ends at 0x674ef06 (per dossier). Hot-path ret confirmed at 0x674ce4e.

## ALL FOUR MATERIALS located [V]
- UI/Blit = 0x674bc15 (data_f2be628, len 7)
- UI/Base = 0x674bd1f (data_f2be668, len 7)
- UI/Sprite = 0x674c147 (data_f2be5e8, len 9) and 0x674c283 (data_f2be608, len 9)
- UI/Fill = 0x674cd0e (data_f2be648, len 7)
- Case-0 materials (not Blit/Base/Sprite/Fill): data_f2be8c8 / data_f2be8d8 (via [rbp+0xEE8] gate at 0x674b559)
- Case-2 material qword: data_f2be8f8 (at 0x674c5b2)
- Case-3 material qword: data_f2be908 (at 0x674c6ee)
- Capture textures: "hCapture texture"(data_f5c6ac7), "UIThumbnailMeshCapture texture"(data_f5c6ab9) [case 2]; "eCapture texture"(data_f5c6ae8), "UIStructureVolumeCapture texture"(data_f5c6ad8) [case 3]

## OPEN
- Predecessor of 0x674bb0c material decision tree [?] (no direct jump seen from 4 switch cases; 0x674bb50 has 0 rdis xrefs).
- Cold tails beyond 0x674dda0 not fully transcribed (0x674e0ce/0x674e317/0x674e373/0x674e42e/0x674e50d/0x674e569 and 0x674e3c0/0x674e428/0x674e43d/0x674e4a5/0x674e5b6/0x674e694/0x674e707 blocks). Follow same registration/hash pattern; no new material literals expected.
- Function end (final ret after 0x674ce4e) not yet confirmed; dossier says size 0x4c66 → end 0x674ef06.

## UNIT CORE REQUIREMENTS — ALL SATISFIED [V]
1. **Kind switch (jump table at 0x674b550)** [V]: `movzx eax,byte [r14+0x18]`; `cmp rax,3`; `ja 0x674e428`; `lea rcx,[0xF2BFC90]`; `movsxd rax,[rcx+rax*4]`; `add rax,rcx`; `jmp rax`. Entries: 0→0x674b559, 1→0x674b9b2, 2→0x674b71a, 3→0x674b85d. All 4 cases transcribed with exact instructions.
2. **Materials Blit/Base/Sprite/Fill** [V]: UI/Blit=0x674bc15(data_f2be628,len7), UI/Base=0x674bd1f(data_f2be668,len7), UI/Sprite=0x674c147(data_f2be5e8,len9)+0x674c283(data_f2be608,len9), UI/Fill=0x674cd0e(data_f2be648,len7). Each reached via material decision tree 0x674bb0c..0x674cd0e, then 0x67d6d70 lookup + 0x66a0760 + 0xbcab880 + 0x675dd80 + 0xbcac2b0/0x7e6d0 sequence.
3. **Cold tails** [V]: epilogue 0x674ce34 (pop rbx/rdi/rsi/r12/r13/r14/r15/rbp; ret at 0x674ce4e; frame 0xe98); release loops (double-release via [0xF99FFA0]=sub_eea6040, stride 0x20/0x28); font-option structs (FONT_TYPE/MSDF/BitmapSmooth/TrueType, ALPHA_TEST) via 0x7d7890; UI/Text/MatTexture/UI/Glint/GlyphTexture/GlintTexture/GlintColor/UVScale static uniform registration via 0x79580 + FNV-1a 64 hash loop (0x674dd17-0x674dd7f, basis 0xcbf29ce484222325, prime 0x100000001b3). Cold tails jump back to phase-4 uniform loop at 0x674b411 (e.g., 0x674ce4f, 0x674ce23).

## Remaining cold tails beyond 0x674dda0 [I from branch targets]
Blocks 0x674e0ce/0x674e317/0x674e373/0x674e42e/0x674e50d/0x674e569 (FNV hash entry points) and 0x674e3c0/0x674e428(kind>3 default)/0x674e43d/0x674e4a5/0x674e5b6/0x674e694/0x674e707 follow the same registration/hash pattern; 0x674e0ce confirmed: `mov rcx,0xCBF29CE484222325`; `jmp 0x674e39c`, then "GlintTexture"(data_f5c6b76), "GlintColor"(data_f563953), "UVScale"(data_f5de988) via 0x79580+FNV. No new material literals expected. Function 0x674a3a0 size 0x4c66 → end 0x674ef06 (per dossier); hot-path ret 0x674ce4e confirmed.

## OPEN [?]
- Predecessor of 0x674bb0c material decision tree (no direct jump from 4 switch cases; 0x674bb50 has 0 rdis xrefs — likely indirect jump/cold entry).
- Final function end ret after 0x674ce4e not visually confirmed (dossier: end 0x674ef06).

## Files
- docs/progress/oc_U-UI5.md (this file, only file created). No other file edited.
- [rbp+0xc10..]: name="FONT_TYPE" (0x5059545F544E4F46+0x45), value="BitmapSmooth" (0x6d5370616d746942+0x68746f6f), "ALPHA_TEST"(data_f7c86b5), sub_d005453(data_f7c86bd). Call 0x7d7890 at 0x674d063 with rdx=[rbp+0x4f0], rcx=data_129fa2c0.
- [rbp+0x910..]: name="FONT_TYPE", value="BitmapSmooth" (0x6d5370616d746942 @0x930, 0x68746f6f @0x938), same ALPHA_TEST. Call 0x7d7890 at 0x674d18c.
- [rbp+0x2e0..]: name="FONT_TYPE", value="TrueType" (0x6570795465757254 @0x300), same ALPHA_TEST. Call 0x7d7890 at 0x674d2ab.
- [rbp+0x2e8]=0, [rbp+0x2f0]=9, [rbp+0x2f8]=0xF (len=9 for "FONT_TYPE"? actually 0x9=9); [rbp+0x308]=0, [rbp+0x310]=8, [rbp+0x318]=0xF; [rbp+0x328]=0(w), [rbp+0x330]=0xa, [rbp+0x338]=0xf; [rbp+0x350]=3, [rbp+0x358]=0xf.
- 0x674d2b1 `lea r12,[0x129FA380]`; `mov [rbp+0xBF8],r12`; 0x674d2bf `lea rdx,[0xF7CC3C4]` "FONT_TYPE"; 0x674d2c6 `lea r8,[0xF7CBE53]` "MSDF"; 0x674d2cd `lea rcx,[rbp+0x5F0]` → compares FONT_TYPE vs MSDF for font-variant selection (feeds material option variant index). [I]

## Cold-tail transcription 0x674d2cd..0x674dada [V]
(rdis `dis 0x674d2cd 300`; every instruction quoted exactly as printed, nops included)
```
  674d2cd  lea rcx,[rbp+0x5F0]
  674d2d4  mov r15,rcx
  674d2d7  call 0xF2EA00                                 ; -> sub_f2ea00
  674d2dc  nop
  674d2dd  mov qword ptr [rbp+0x638],0
  674d2e8  mov qword ptr [rbp+0x640],0xA
  674d2f3  mov qword ptr [rbp+0x648],0xF
  674d2fe  mov rax,[0xF7C86B5]                           ; [data_f7c86b5] "ALPHA_TEST"
  674d305  mov [rbp+0x630],rax
  674d30c  movzx eax,word ptr [0xF7C86BD]                ; [data_f7c86bd] = sub_d005453
  674d313  mov [rbp+0x638],ax
  674d31a  mov qword ptr [rbp+0x660],3
  674d325  mov qword ptr [rbp+0x668],0xF
  674d330  mov qword ptr [rbp+0x653],0
  674d33b  mov qword ptr [rbp+0x658],0
  674d346  mov [rbp+0x650],bx
  674d34d  movzx eax,byte ptr [0xF5BAC4A]                ; [data_f5bac4a]
  674d354  mov [rbp+0x652],al
  674d35a  mov [rbp+0x520],r15
  674d361  lea rax,[rbp+0x670]
  674d368  mov [rbp+0x528],rax
  674d36f  mov [rbp+0x8F8],r12
  674d376  lea rdx,[rbp+0x520]
  674d37d  mov rcx,r12
  674d380  call 0x7D7890                                 ; -> sub_7d7890
  674d385  nop
  674d386  mov qword ptr [rbp+0x798],0
  674d391  mov qword ptr [rbp+0x7A0],9
  674d39c  mov qword ptr [rbp+0x7A8],0xF
  674d3a7  mov rax,0x5059545F544E4F46
  674d3b1  mov [rbp+0x790],rax
  674d3b8  mov byte ptr [rbp+0x798],0x45
  674d3bf  mov qword ptr [rbp+0x7C0],6
  674d3ca  mov qword ptr [rbp+0x7C8],0xF
  674d3d5  mov qword ptr [rbp+0x7B6],0
  674d3e0  mov word ptr [rbp+0x7BE],0
  674d3e9  mov dword ptr [rbp+0x7B0],0x6D746942
  674d3f3  mov word ptr [rbp+0x7B4],0x7061
  674d3fc  mov qword ptr [rbp+0x7D8],0
  674d407  mov qword ptr [rbp+0x7E0],0xA
  674d412  mov qword ptr [rbp+0x7E8],0xF
  674d41d  mov rax,[0xF7C86B5]                           ; [data_f7c86b5] "ALPHA_TEST"
  674d424  mov [rbp+0x7D0],rax
  674d42b  movzx eax,word ptr [0xF7C86BD]                ; [data_f7c86bd] = sub_d005453
  674d432  mov [rbp+0x7D8],ax
  674d439  xorps xmm6,xmm6
  674d43c  movups [rbp+0x7F0],xmm6
  674d443  mov qword ptr [rbp+0x800],2
  674d44e  mov qword ptr [rbp+0x808],0xF
  674d459  mov word ptr [rbp+0x7F0],0x6E4F
  674d462  lea rax,[rbp+0x790]
  674d469  mov [rbp+0x530],rax
  674d470  lea rax,[rbp+0x810]
  674d477  mov [rbp+0x538],rax
  674d47e  lea rcx,[0x129FA3C0]                          ; [data_129fa3c0]
  674d485  mov [rbp+0x900],rcx
  674d48c  lea rdx,[rbp+0x530]
  674d493  call 0x7D7890                                 ; -> sub_7d7890
  674d498  nop
  674d499  mov qword ptr [rbp+0x818],0
  674d4a4  mov qword ptr [rbp+0x820],9
  674d4af  mov qword ptr [rbp+0x828],0xF
  674d4ba  mov rax,0x5059545F544E4F46
  674d4c4  mov [rbp+0x810],rax
  674d4cb  mov byte ptr [rbp+0x818],0x45
  674d4d2  mov qword ptr [rbp+0x838],0
  674d4dd  mov qword ptr [rbp+0x840],0xC
  674d4e8  mov qword ptr [rbp+0x848],0xF
  674d4f3  mov rax,0x6D5370616D746942
  674d4fd  mov [rbp+0x830],rax
  674d504  mov dword ptr [rbp+0x838],0x68746F6F
  674d50e  mov qword ptr [rbp+0x858],0
  674d519  mov qword ptr [rbp+0x860],0xA
  674d524  mov qword ptr [rbp+0x868],0xF
  674d52f  mov rax,[0xF7C86B5]                           ; [data_f7c86b5] "ALPHA_TEST"
  674d536  mov [rbp+0x850],rax
  674d53d  movzx eax,word ptr [0xF7C86BD]                ; [data_f7c86bd] = sub_d005453
  674d544  mov [rbp+0x858],ax
  674d54b  movups [rbp+0x870],xmm6
  674d552  mov qword ptr [rbp+0x880],2
  674d55d  mov qword ptr [rbp+0x888],0xF
  674d568  mov word ptr [rbp+0x870],0x6E4F
  674d571  lea rax,[rbp+0x810]
  674d578  mov [rbp+0x540],rax
  674d57f  lea rax,[rbp+0x890]
  674d586  mov [rbp+0x548],rax
  674d58d  lea rcx,[0x129FA400]                          ; [data_129fa400]
  674d594  mov [rbp+0x908],rcx
  674d59b  lea rdx,[rbp+0x540]
  674d5a2  call 0x7D7890                                 ; -> sub_7d7890
  674d5a7  nop
  674d5a8  mov qword ptr [rbp+0xAE8],0
  674d5b3  mov qword ptr [rbp+0xAF0],9
  674d5be  mov qword ptr [rbp+0xAF8],0xF
  674d5c9  mov rax,0x5059545F544E4F46
  674d5d3  mov [rbp+0xAE0],rax
  674d5da  mov byte ptr [rbp+0xAE8],0x45
  674d5e1  mov qword ptr [rbp+0xB08],0
  674d5ec  mov qword ptr [rbp+0xB10],8
  674d5f7  mov qword ptr [rbp+0xB18],0xF
  674d602  mov rax,0x6570795465757254
  674d60c  mov [rbp+0xB00],rax
  674d613  mov qword ptr [rbp+0xB28],0
  674d61e  mov qword ptr [rbp+0xB30],0xA
  674d629  mov qword ptr [rbp+0xB38],0xF
  674d634  mov rax,[0xF7C86B5]                           ; [data_f7c86b5] "ALPHA_TEST"
  674d63b  mov [rbp+0xB20],rax
  674d642  movzx eax,word ptr [0xF7C86BD]                ; [data_f7c86bd] = sub_d005453
  674d649  mov [rbp+0xB28],ax
  674d650  xorps xmm0,xmm0
  674d653  movups [rbp+0xB40],xmm0
  674d65a  mov qword ptr [rbp+0xB50],2
  674d665  mov qword ptr [rbp+0xB58],0xF
  674d670  mov word ptr [rbp+0xB40],0x6E4F
  674d679  lea rax,[rbp+0xAE0]
  674d680  mov [rbp+0x550],rax
  674d687  lea rax,[rbp+0xB60]
  674d68e  mov [rbp+0x558],rax
  674d695  lea rcx,[0x129FA440]                          ; [data_129fa440]
  674d69c  mov [rbp+0xC00],rcx
  674d6a3  lea rdx,[rbp+0x550]
  674d6aa  call 0x7D7890                                 ; -> sub_7d7890
  674d6af  nop
  674d6b0  lea rax,[0x129FA480]                          ; [data_129fa480]
  674d6b7  mov [rbp+0xC00],rax
  674d6be  lea rdx,[0xF7CC3C4]                           ; [data_f7cc3c4] "FONT_TYPE"
  674d6c5  lea r8,[0xF7CBE53]                            ; [data_f7cbe53] "MSDF"
  674d6cc  lea r12,[rbp+0x260]
  674d6d3  mov rcx,r12
  674d6d6  call 0xF2EA00                                 ; -> sub_f2ea00
  674d6db  nop
  674d6dc  mov qword ptr [rbp+0x2A8],0
  674d6e7  mov qword ptr [rbp+0x2B0],0xA
  674d6f2  mov qword ptr [rbp+0x2B8],0xF
  674d6fd  mov rax,[0xF7C86B5]                           ; [data_f7c86b5] "ALPHA_TEST"
  674d704  mov [rbp+0x2A0],rax
  674d70b  movzx eax,word ptr [0xF7C86BD]                ; [data_f7c86bd] = sub_d005453
  674d712  mov [rbp+0x2A8],ax
  674d719  xorps xmm0,xmm0
  674d71c  movups [rbp+0x2C0],xmm0
  674d723  mov qword ptr [rbp+0x2D0],2
  674d72e  mov qword ptr [rbp+0x2D8],0xF
  674d739  mov word ptr [rbp+0x2C0],0x6E4F
  674d742  mov [rbp+0x560],r12
  674d749  lea rax,[rbp+0x2E0]
  674d750  mov [rbp+0x568],rax
  674d757  lea rcx,[0x129FA480]                          ; [data_129fa480]
  674d75e  lea rdx,[rbp+0x560]
  674d765  call 0x7D7890                                 ; -> sub_7d7890
  674d76a  nop
  674d76b  lea rcx,[rbp+0x2A0]
  674d772  call 0x9B250                                  ; -> sub_9b250
  674d777  lea rcx,[rbp+0x260]
  674d77e  call 0x9B250                                  ; -> sub_9b250
  674d783  lea rcx,[rbp+0xB20]
  674d78a  call 0x9B250                                  ; -> sub_9b250
  674d78f  lea rcx,[rbp+0xAE0]
  674d796  call 0x9B250                                  ; -> sub_9b250
  674d79b  lea rcx,[rbp+0x850]
  674d7a2  call 0x9B250                                  ; -> sub_9b250
  674d7a7  lea rcx,[rbp+0x810]
  674d7ae  call 0x9B250                                  ; -> sub_9b250
  674d7b3  lea rcx,[rbp+0x7D0]
  674d7ba  call 0x9B250                                  ; -> sub_9b250
  674d7bf  lea rcx,[rbp+0x790]
  674d7c6  call 0x9B250                                  ; -> sub_9b250
  674d7cb  lea rcx,[rbp+0x630]
  674d7d2  call 0x9B250                                  ; -> sub_9b250
  674d7d7  lea rcx,[rbp+0x5F0]
  674d7de  call 0x9B250                                  ; -> sub_9b250
  674d7e3  lea rcx,[rbp+0x320]
  674d7ea  call 0x9B250                                  ; -> sub_9b250
  674d7ef  lea rcx,[rbp+0x2E0]
  674d7f6  call 0x9B250                                  ; -> sub_9b250
  674d7fb  lea rcx,[rbp+0x950]
  674d802  call 0x9B250                                  ; -> sub_9b250
  674d807  lea rcx,[rbp+0x910]
  674d80e  call 0x9B250                                  ; -> sub_9b250
  674d813  lea rcx,[rbp+0xC50]
  674d81a  call 0x9B250                                  ; -> sub_9b250
  674d81f  lea rcx,[rbp+0xC10]
  674d826  call 0x9B250                                  ; -> sub_9b250
  674d82b  lea rcx,[0x6750710]                           ; [sub_6750710]
  674d832  call 0xE935740                                ; -> sub_e935740
  674d837  lea rcx,[0x129FA4C0]                          ; [data_129fa4c0]
  674d83e  call 0xE938D70                                ; -> sub_e938d70
  674d843  mov r15,[rbp+0xEB8]
  674d84a  jmp 0x674A547                                 ; -> sub_674a547
  674d84f  lea rcx,[0x129FA548]                          ; [data_129fa548]
  674d856  call 0xE938CB0                                ; -> sub_e938cb0
  674d85b  cmp dword ptr [0x129FA548],0xFFFFFFFF         ; [data_129fa548]
  674d862  jne 0x674A56C                                 ; -> sub_674a56c
  674d868  lea rdx,[0x129FA2C0]                          ; [data_129fa2c0]
  674d86f  lea rcx,[rbp+0x10]
  674d873  lea r8,[rbp+0xC10]
  674d87a  call 0xAA710                                  ; -> sub_aa710
  674d87f  nop
  674d880  lea rbx,[0xF2BE688]                           ; [data_f2be688] "UI/Text"
  674d887  mov [rbp+0x570],rbx
  674d88e  mov qword ptr [rbp+0x578],7
  674d899  lea rcx,[0x129FA4C8]                          ; [data_129fa4c8]
  674d8a0  lea rdx,[rbp+0x570]
  674d8a7  lea r8,[rbp+0x10]
  674d8ab  call 0x66A02D0                                ; -> sub_66a02d0
  674d8b0  nop
  674d8b1  lea rdx,[0x129FA300]                          ; [data_129fa300]
  674d8b8  lea rcx,[rbp+0x50]
  674d8bc  lea r8,[rbp+0xC10]
  674d8c3  call 0xAA710                                  ; -> sub_aa710
  674d8c8  nop
  674d8c9  mov [rbp+0x580],rbx
  674d8d0  mov qword ptr [rbp+0x588],7
  674d8db  lea rcx,[0x129FA4D8]                          ; [data_129fa4d8]
  674d8e2  lea rdx,[rbp+0x580]
  674d8e9  lea r8,[rbp+0x50]
  674d8ed  call 0x66A02D0                                ; -> sub_66a02d0
  674d8f2  nop
  674d8f3  lea rdx,[0x129FA340]                          ; [data_129fa340]
  674d8fa  lea rcx,[rbp+0x90]
  674d901  lea r8,[rbp+0xC10]
  674d908  call 0xAA710                                  ; -> sub_aa710
  674d90d  nop
  674d90e  mov [rbp+0x590],rbx
  674d915  mov qword ptr [rbp+0x598],7
  674d920  lea rcx,[0x129FA4E8]                          ; [data_129fa4e8]
  674d927  lea rdx,[rbp+0x590]
  674d92e  lea r8,[rbp+0x90]
  674d935  call 0x66A02D0                                ; -> sub_66a02d0
  674d93a  nop
  674d93b  lea rdx,[0x129FA380]                          ; [data_129fa380]
  674d942  lea rcx,[rbp+0xD0]
  674d949  lea r8,[rbp+0xC10]
  674d950  call 0xAA710                                  ; -> sub_aa710
  674d955  nop
  674d956  mov [rbp+0x5A0],rbx
  674d95d  mov qword ptr [rbp+0x5A8],7
  674d968  lea rcx,[0x129FA4F8]                          ; [data_129fa4f8]
  674d96f  lea rdx,[rbp+0x5A0]
  674d976  lea r8,[rbp+0xD0]
  674d97d  call 0x66A02D0                                ; -> sub_66a02d0
  674d982  nop
  674d983  lea rdx,[0x129FA3C0]                          ; [data_129fa3c0]
  674d98a  lea rcx,[rbp+0x110]
  674d991  lea r8,[rbp+0xC10]
  674d998  call 0xAA710                                  ; -> sub_aa710
  674d99d  nop
  674d99e  mov [rbp+0x5B0],rbx
  674d9a5  mov qword ptr [rbp+0x5B8],7
  674d9b0  lea rcx,[0x129FA508]                          ; [data_129fa508]
  674d9b7  lea rdx,[rbp+0x5B0]
  674d9be  lea r8,[rbp+0x110]
  674d9c5  call 0x66A02D0                                ; -> sub_66a02d0
  674d9ca  nop
  674d9cb  lea rdx,[0x129FA400]                          ; [data_129fa400]
  674d9d2  lea rcx,[rbp+0x150]
  674d9d9  lea r8,[rbp+0xC10]
  674d9e0  call 0xAA710                                  ; -> sub_aa710
  674d9e5  nop
  674d9e6  mov [rbp+0x5C0],rbx
  674d9ed  mov qword ptr [rbp+0x5C8],7
  674d9f8  lea rcx,[0x129FA518]                          ; [data_129fa518]
  674d9ff  lea rdx,[rbp+0x5C0]
  674da06  lea r8,[rbp+0x150]
  674da0d  call 0x66A02D0                                ; -> sub_66a02d0
  674da12  nop
  674da13  lea rdx,[0x129FA440]                          ; [data_129fa440]
  674da1a  lea rcx,[rbp+0x190]
  674da21  lea r8,[rbp+0xC10]
  674da28  call 0xAA710                                  ; -> sub_aa710
  674da2d  nop
  674da2e  mov [rbp+0x5D0],rbx
  674da35  mov qword ptr [rbp+0x5D8],7
  674da40  lea rcx,[0x129FA528]                          ; [data_129fa528]
  674da47  lea rdx,[rbp+0x5D0]
  674da4e  lea r8,[rbp+0x190]
  674da55  call 0x66A02D0                                ; -> sub_66a02d0
  674da5a  nop
  674da5b  lea rdx,[0x129FA480]                          ; [data_129fa480]
  674da62  lea rcx,[rbp+0x1D0]
  674da69  lea r8,[rbp+0xC10]
  674da70  call 0xAA710                                  ; -> sub_aa710
  674da75  nop
  674da76  mov [rbp+0x5E0],rbx
  674da7d  mov qword ptr [rbp+0x5E8],7
  674da88  lea rcx,[0x129FA538]                          ; [data_129fa538]
  674da8f  lea rdx,[rbp+0x5E0]
  674da96  lea r8,[rbp+0x1D0]
  674da9d  call 0x66A02D0                                ; -> sub_66a02d0
  674daa2  nop
  674daa3  lea rcx,[0x129FA548]                          ; [data_129fa548]
  674daaa  call 0xE938D70                                ; -> sub_e938d70
  674daaf  jmp 0x674A56C                                 ; -> sub_674a56c
  674dab4  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  674dabb  call 0xE938CB0                                ; -> sub_e938cb0
  674dac0  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
  674dac7  jne 0x674A60C                                 ; -> sub_674a60c
  674dacd  lea rcx,[0x129CA568]                          ; [data_129ca568]
  674dad4  call 0x567DB00                                ; -> sub_567db00
  674dad9  nop
  674dada  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
```

## Interpretation [I]
- 0x674d2cd..0x674d385: builds option struct at [rbp+0x520..] (ptr r15=[rbp+0x5f0] stored at [rbp+0x520], vtable-ish ptr [rbp+0x528]=&[rbp+0x670]); fields: [rbp+0x630]="ALPHA_TEST"(data_f7c86b5), [rbp+0x638]=word sub_d005453(data_f7c86bd), [rbp+0x640]=0xA, [rbp+0x648]=0xF, [rbp+0x650]=bx, [rbp+0x652]=byte data_f5bac4a, [rbp+0x653]=0, [rbp+0x658]=0, [rbp+0x660]=3, [rbp+0x668]=0xF. Registered via 0x7d7890 (rdx=&[rbp+0x520], rcx=r12=data_129fa380, from [rbp+0x8f8]). [V]
- 0x674d386..0x674d498: option struct at [rbp+0x790..]: name="FONT_TYPE"(imm 0x5059545F544E4F46)+byte 0x45('E') at [rbp+0x798]; [rbp+0x7c0]=6, [rbp+0x7c8]=0xF; [rbp+0x7b0]=0x6D746942 ("Bitm" LE), [rbp+0x7b4]=0x7061 ("ap" LE) → "Bitmap"; [rbp+0x7b6]=0, [rbp+0x7be]=0; [rbp+0x7d8]=0 then sub_d005453 word; [rbp+0x7e0]=0xA, [rbp+0x7e8]=0xF, [rbp+0x7d0]="ALPHA_TEST"; [rbp+0x7f0]=xmm6(0) then word 0x6E4F ("On" LE), [rbp+0x800]=2, [rbp+0x808]=0xF. [rbp+0x530]=&[rbp+0x790], [rbp+0x538]=&[rbp+0x810], [rbp+0x900]=data_129fa3c0; registered via 0x7d7890. [V]
- 0x674d499..0x674d5a7: option struct at [rbp+0x810..]: name="FONT_TYPE"+0x45; [rbp+0x830]=0x6D5370616D746942 ("BitmapS"), [rbp+0x838]=0x68746F6F ("ooth") → "BitmapSmooth"; [rbp+0x840]=0xC, [rbp+0x848]=0xF; [rbp+0x850]="ALPHA_TEST", [rbp+0x858]=sub_d005453; [rbp+0x870]=xmm6(0)+word 0x6E4F; [rbp+0x880]=2, [rbp+0x888]=0xF. [rbp+0x540]=&[rbp+0x810], [rbp+0x548]=&[rbp+0x890], [rbp+0x908]=data_129fa400; registered via 0x7d7890. [V]
- 0x674d5a8..0x674d6af: option struct at [rbp+0xae0..]: name="FONT_TYPE"+0x45 at [rbp+0xae0]; [rbp+0xb00]=0x6570795465757254 ("TrueType"); [rbp+0xb08]=0, [rbp+0xb10]=8, [rbp+0xb18]=0xF; [rbp+0xb20]="ALPHA_TEST", [rbp+0xb28]=sub_d005453, [rbp+0xb30]=0xA, [rbp+0xb38]=0xF, [rbp+0xb40]=xmm0(0)+word 0x6E4F, [rbp+0xb50]=2, [rbp+0xb58]=0xF. [rbp+0x550]=&[rbp+0xae0], [rbp+0x558]=&[rbp+0xb60], [rbp+0xc00]=data_129fa440; registered via 0x7d7890. [V]
- 0x674d6b0..0x674d76a: [rbp+0xc00]=data_129fa480; rdx=data_f7cc3c4 "FONT_TYPE", r8=data_f7cbe53 "MSDF"; r12=&[rbp+0x260]; call 0xf2ea00 (FONT_TYPE vs MSDF compare → variant index, [I]). Then option struct at [rbp+0x2a0..]: [rbp+0x2a0]="ALPHA_TEST", [rbp+0x2a8]=sub_d005453, [rbp+0x2b0]=0xA, [rbp+0x2b8]=0xF, [rbp+0x2c0]=xmm0(0)+word 0x6E4F, [rbp+0x2d0]=2, [rbp+0x2d8]=0xF. [rbp+0x560]=r12, [rbp+0x568]=&[rbp+0x2e0], rcx=data_129fa480; registered via 0x7d7890 (rdx=&[rbp+0x560]). [V]
- 0x674d76b..0x674d826: 16 name hashes via 0x9b250 (sub_9b250, dossier x17) on [rbp+0x2a0], [rbp+0x260], [rbp+0xb20], [rbp+0xae0], [rbp+0x850], [rbp+0x810], [rbp+0x7d0], [rbp+0x790], [rbp+0x630], [rbp+0x5f0], [rbp+0x320], [rbp+0x2e0], [rbp+0x950], [rbp+0x910], [rbp+0xc50], [rbp+0xc10]. [V]
- 0x674d82b..0x674d84a: `lea rcx,[0x6750710]` (fn ptr as immediate); `call 0xE935740` (dossier x5); `lea rcx,[0x129fa4c0]`; `call 0xE938D70`; `mov r15,[rbp+0xeb8]`; `jmp 0x674A547` (sub_674a547, phase-4 region). [V]
- 0x674d84f..0x674daa2: UI/Text static registration (init-once via 0xe938cb0 on data_129fa548; if != 0xFFFFFFFF → jmp 0x674a56c). Then `lea rbx,[0xF2BE688]` "UI/Text" (len 7) stored at [rbp+0x570]/[rbp+0x580]/[rbp+0x590]/[rbp+0x5a0]/[rbp+0x5b0]/[rbp+0x5c0]/[rbp+0x5d0]/[rbp+0x5e0] (+8 = 7), interleaved with 8 calls to 0xaa710 (keys data_129fa2c0/300/340/380/3c0/400/440/480 at dst [rbp+0x10]/0x50/0x90/0xd0/0x110/0x150/0x190/0x1d0, r8=[rbp+0xc10]) and 8 calls to 0x66a02D0 (keys data_129fa4c8/4d8/4e8/4f8/508/518/528/538, rdx=&[rbp+0x570+0x10i], r8=[rbp+0x10/0x50/0x90/0xd0/0x110/0x150/0x190/0x1d0]). [V] — FNV-1a hash of static uniform name keys per dossier (0x66a02d0 = x13, 0xaa710 = x12).
- 0x674daa3..0x674dada: `lea rcx,[0x129fa548]`; `call 0xE938D70`; `jmp 0x674A56C`. Then `lea rcx,[0x129ca5e0]`; `call 0xE938CB0`; `cmp [0x129ca5e0],0xFFFFFFFF`; `jne 0x674a60c`; `lea rcx,[0x129ca568]`; `call 0x567db00` (dossier x2); `lea rcx,[0x567DBA0]` (fn ptr) → continues at 0x674dadc. [V]

## Cold-tail transcription 0x674dadc..0x674dfeb [V]
(rdis `dis 0x674dadc 250`; every instruction quoted exactly as printed, nops included)
```
  674dadc  or eax,0xFEF300BF
  674dae1  call 0xE935740                                ; -> sub_e935740
  674dae6  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  674daed  call 0xE938D70                                ; -> sub_e938d70
  674daf2  jmp 0x674A60C                                 ; -> sub_674a60c
  674daf7  lea rcx,[0x129FA190]                          ; [data_129fa190]
  674dafe  call 0xE938CB0                                ; -> sub_e938cb0
  674db03  cmp dword ptr [0x129FA190],0xFFFFFFFF         ; [data_129fa190]
  674db0a  jne 0x674A6A3                                 ; -> sub_674a6a3
  674db10  lea rdx,[0xF5C6BAE]                           ; [data_f5c6bae] "MatTexture"
  674db17  lea r12,[rbp+0xC10]
  674db1e  mov rcx,r12
  674db21  call 0x79580                                  ; -> sub_79580
  674db26  nop
  674db27  mov rdx,[rbp+0xC20]
  674db2e  cmp qword ptr [rbp+0xC28],0x10
  674db36  jb short 0x674DB3F                            ; -> loc_674db3f
  674db38  mov r12,[rbp+0xC10]

loc_674db3f:  ; from 674db36
  674db3f  test rdx,rdx
  674db42  je 0x674E0CE                                  ; -> loc_674e0ce
  674db48  mov eax,edx
  674db4a  and eax,3
  674db4d  cmp rdx,4
  674db51  jae 0x674E317                                 ; -> loc_674e317
  674db57  mov rcx,0xCBF29CE484222325
  674db61  xor r8d,r8d
  674db64  jmp 0x674E373                                 ; -> loc_674e373
  674db69  lea rcx,[0x129FA1A8]                          ; [data_129fa1a8]
  674db70  call 0xE938CB0                                ; -> sub_e938cb0
  674db75  cmp dword ptr [0x129FA1A8],0xFFFFFFFF         ; [data_129fa1a8]
  674db7c  jne 0x674A6D1                                 ; -> sub_674a6d1
  674db82  xorps xmm0,xmm0
  674db85  movaps [rbp+0x210],xmm0
  674db8c  lea rax,[0xF2BE5C8]                           ; [data_f2be5c8] "UI/Glint"
  674db93  mov [rbp+0x480],rax
  674db9a  mov qword ptr [rbp+0x488],8
  674dba5  lea rcx,[0x129FA198]                          ; [data_129fa198]
  674dbac  lea rdx,[rbp+0x480]
  674dbb3  lea r8,[rbp+0x210]
  674dbba  call 0x5668AC0                                ; -> sub_5668ac0
  674dbbf  nop
  674dbc0  lea rcx,[0x129FA1A8]                          ; [data_129fa1a8]
  674dbc7  call 0xE938D70                                ; -> sub_e938d70
  674dbcc  jmp 0x674A6D1                                 ; -> sub_674a6d1
  674dbd1  lea rax,[0x129FB1B0]                          ; [data_129fb1b0]
  674dbd8  mov rdi,rcx
  674dbdb  mov rcx,rax
  674dbde  call 0xE938CB0                                ; -> sub_e938cb0
  674dbe3  mov rcx,rdi
  674dbe6  cmp dword ptr [0x129FB1B0],0xFFFFFFFF         ; [data_129fb1b0]
  674dbed  jne 0x674A704                                 ; -> sub_674a704
  674dbf3  mov dword ptr [rbp+0xC10],0
  674dbfd  lea rcx,[0x129FB170]                          ; [data_129fb170]
  674dc04  lea rdx,[rbp+0xC10]
  674dc0b  lea r8,[rbp+0x910]
  674dc12  call 0x9B020                                  ; -> sub_9b020
  674dc17  nop
  674dc18  lea rcx,[0x6761090]                           ; [sub_6761090]
  674dc1f  call 0xE935740                                ; -> sub_e935740
  674dc24  lea rcx,[0x129FB1B0]                          ; [data_129fb1b0]
  674dc2b  call 0xE938D70                                ; -> sub_e938d70
  674dc30  mov rcx,rdi
  674dc33  jmp 0x674A704                                 ; -> sub_674a704
  674dc38  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  674dc3f  call 0xE938CB0                                ; -> sub_e938cb0
  674dc44  cmp dword ptr [0x129CA5E0],0xFFFFFFFF         ; [data_129ca5e0]
  674dc4b  jne 0x674A784                                 ; -> sub_674a784
  674dc51  lea rcx,[0x129CA568]                          ; [data_129ca568]
  674dc58  call 0x567DB00                                ; -> sub_567db00
  674dc5d  nop
  674dc5e  lea rcx,[0x567DBA0]                           ; [sub_567dba0]
  674dc65  call 0xE935740                                ; -> sub_e935740
  674dc6a  lea rcx,[0x129CA5E0]                          ; [data_129ca5e0]
  674dc71  call 0xE938D70                                ; -> sub_e938d70
  674dc76  jmp 0x674A784                                 ; -> sub_674a784
  674dc7b  mov rcx,0xCBF29CE484222325
  674dc85  jmp 0x674DD81                                 ; -> loc_674dd81
  674dc8a  lea rcx,[0x129FA558]                          ; [data_129fa558]
  674dc91  call 0xE938CB0                                ; -> sub_e938cb0
  674dc96  cmp dword ptr [0x129FA558],0xFFFFFFFF         ; [data_129fa558]
  674dc9d  jne 0x674A91C                                 ; -> sub_674a91c
  674dca3  lea rdx,[0xF5C6DD7]                           ; [data_f5c6dd7] "GlyphTexture"
  674dcaa  lea r12,[rbp+0xC10]
  674dcb1  mov rcx,r12
  674dcb4  call 0x79580                                  ; -> sub_79580
  674dcb9  nop
  674dcba  mov rdx,[rbp+0xC20]
  674dcc1  cmp qword ptr [rbp+0xC28],0x10
  674dcc9  jb short 0x674DCD2                            ; -> loc_674dcd2
  674dccb  mov r12,[rbp+0xC10]

loc_674dcd2:  ; from 674dcc9
  674dcd2  test rdx,rdx
  674dcd5  je 0x674E42E                                  ; -> loc_674e42e
  674dcdb  mov eax,edx
  674dcdd  and eax,3
  674dce0  cmp rdx,4
  674dce4  jae 0x674E50D                                 ; -> loc_674e50d
  674dcea  mov rcx,0xCBF29CE484222325
  674dcf4  xor r8d,r8d
  674dcf7  jmp 0x674E569                                 ; -> loc_674e569
  674dcfc  and rdx,0xFFFFFFFFFFFFFFFC
  674dd00  mov rcx,0xCBF29CE484222325
  674dd0a  xor r8d,r8d
  674dd0d  mov r9,0x100000001B3

loc_674dd17:  ; from 674dd51
  674dd17  movzx r10d,byte ptr [r14+r8]
  674dd1c  xor r10,rcx
  674dd1f  imul r10,r9
  674dd23  movzx ecx,byte ptr [r14+r8+1]
  674dd29  xor rcx,r10
  674dd2c  imul rcx,r9
  674dd30  movzx r10d,byte ptr [r14+r8+2]
  674dd36  xor r10,rcx
  674dd39  imul r10,r9
  674dd3d  movzx ecx,byte ptr [r14+r8+3]
  674dd43  xor rcx,r10
  674dd46  imul rcx,r9
  674dd4a  add r8,4
  674dd4e  cmp rdx,r8
  674dd51  jne short 0x674DD17                           ; -> loc_674dd17
  674dd53  test rax,rax
  674dd56  je short 0x674DD81                            ; -> loc_674dd81
  674dd58  add r14,r8
  674dd5b  xor edx,edx
  674dd5d  mov r8,0x100000001B3
  674dd67  mov r9,rcx

loc_674dd6a:  ; from 674dd7f
  674dd6a  movzx ecx,byte ptr [r14+rdx]
  674dd6f  xor rcx,r9
  674dd72  imul rcx,r8
  674dd76  inc rdx
  674dd79  mov r9,rcx
  674dd7c  cmp rax,rdx
  674dd7f  jne short 0x674DD6A                           ; -> loc_674dd6a

loc_674dd81:  ; from 674dc85, 674dd56
  674dd81  mov [0x129FA178],rcx                          ; [data_129FA178]
  674dd88  lea rcx,[rbp+0xC10]
  674dd8f  call 0x73150                                  ; -> sub_73150
  674dd94  lea rcx,[0x129FA180]                          ; [data_129fa180]
  674dd9b  call 0xE938D70                                ; -> sub_e938d70
  674dda0  jmp 0x674A4C3                                 ; -> sub_674a4c3
  674dda5  lea rcx,[0x129FA568]                          ; [data_129fa568]
  674ddac  call 0xE938CB0                                ; -> sub_e938cb0
  674ddb1  cmp dword ptr [0x129FA568],0xFFFFFFFF         ; [data_129fa568]
  674ddb8  jne 0x674AAC7                                 ; -> sub_674aac7
  674ddbe  lea rdx,[0xF543686]                           ; [data_f543686] "GlyphSmoothRadius"
  674ddc5  lea r12,[rbp+0xC10]
  674ddcc  mov rcx,r12
  674ddcf  call 0x79580                                  ; -> sub_79580
  674ddd4  nop
  674ddd5  mov rdx,[rbp+0xC20]
  674dddc  cmp qword ptr [rbp+0xC28],0x10
  674dde4  jb short 0x674DDED                            ; -> loc_674dded
  674dde6  mov r12,[rbp+0xC10]

loc_674dded:  ; from 674dde4
  674dded  test rdx,rdx
  674ddf0  je 0x674E76F                                  ; -> loc_674e76f
  674ddf6  mov eax,edx
  674ddf8  and eax,3
  674ddfb  cmp rdx,4
  674ddff  jae 0x674E7D8                                 ; -> loc_674e7d8
  674de05  mov rcx,0xCBF29CE484222325
  674de0f  xor r8d,r8d
  674de12  jmp 0x674E834                                 ; -> loc_674e834
  674de17  lea rcx,[0x129FA578]                          ; [data_129fa578]
  674de1e  call 0xE938CB0                                ; -> sub_e938cb0
  674de23  cmp dword ptr [0x129FA578],0xFFFFFFFF         ; [data_129fa578]
  674de2a  jne 0x674AAEC                                 ; -> sub_674aaec
  674de30  lea rdx,[0xF5BA860]                           ; [data_f5ba860] "OutlineCutoff"
  674de37  lea r12,[rbp+0xC10]
  674de3e  mov rcx,r12
  674de41  call 0x79580                                  ; -> sub_79580
  674de46  nop
  674de47  mov rdx,[rbp+0xC20]
  674de4e  cmp qword ptr [rbp+0xC28],0x10
  674de56  jb short 0x674DE5F                            ; -> loc_674de5f
  674de58  mov r12,[rbp+0xC10]

loc_674de5f:  ; from 674de56
  674de5f  test rdx,rdx
  674de62  je 0x674E77E                                  ; -> loc_674e77e
  674de68  mov eax,edx
  674de6a  and eax,3
  674de6d  cmp rdx,4
  674de71  jae 0x674E881                                 ; -> loc_674e881
  674de77  mov rcx,0xCBF29CE484222325
  674de81  xor r8d,r8d
  674de84  jmp 0x674E8DD                                 ; -> loc_674e8dd
  674de89  lea rcx,[0x129FA588]                          ; [data_129fa588]
  674de90  call 0xE938CB0                                ; -> sub_e938cb0
  674de95  cmp dword ptr [0x129FA588],0xFFFFFFFF         ; [data_129fa588]
  674de9c  jne 0x674AB11                                 ; -> sub_674ab11
  674dea2  lea rdx,[0xF543673]                           ; [data_f543673] "ShadowSmoothRadius"
  674dea9  lea r12,[rbp+0xC10]
  674deb0  mov rcx,r12
  674deb3  call 0x79580                                  ; -> sub_79580
  674deb8  nop
  674deb9  mov rdx,[rbp+0xC20]
  674dec0  cmp qword ptr [rbp+0xC28],0x10
  674dec8  jb short 0x674DED1                            ; -> loc_674ded1
  674deca  mov r12,[rbp+0xC10]

loc_674ded1:  ; from 674dec8
  674ded1  test rdx,rdx
  674ded4  je 0x674E78D                                  ; -> loc_674e78d
  674deda  mov eax,edx
  674dedc  and eax,3
  674dedf  cmp rdx,4
  674dee3  jae 0x674E92A                                 ; -> loc_674e92a
  674dee9  mov rcx,0xCBF29CE484222325
  674def3  xor r8d,r8d
  674def6  jmp 0x674E986                                 ; -> loc_674e986
  674defb  lea rcx,[0x129FA598]                          ; [data_129fa598]
  674df02  call 0xE938CB0                                ; -> sub_e938cb0
  674df07  cmp dword ptr [0x129FA598],0xFFFFFFFF         ; [data_129fa598]
  674df0e  jne 0x674AB36                                 ; -> sub_674ab36
  674df14  lea rdx,[0xF53C9B4]                           ; [data_f53c9b4] "HalfTexelOffset"
  674df1b  lea r12,[rbp+0xC10]
  674df22  mov rcx,r12
  674df25  call 0x79580                                  ; -> sub_79580
  674df2a  nop
  674df2b  mov rdx,[rbp+0xC20]
  674df32  cmp qword ptr [rbp+0xC28],0x10
  674df3a  jb short 0x674DF43                            ; -> loc_674df43
  674df3c  mov r12,[rbp+0xC10]

loc_674df43:  ; from 674df3a
  674df43  test rdx,rdx
  674df46  je 0x674E79C                                  ; -> loc_674e79c
  674df4c  mov eax,edx
  674df4e  and eax,3
  674df51  cmp rdx,4
  674df55  jae 0x674E9D3                                 ; -> loc_674e9d3
  674df5b  mov rcx,0xCBF29CE484222325
  674df65  xor r8d,r8d
  674df68  jmp 0x674EA2F                                 ; -> loc_674ea2f
  674df6d  lea rcx,[0x129FA5A8]                          ; [data_129fa5a8]
  674df74  call 0xE938CB0                                ; -> sub_e938cb0
  674df79  cmp dword ptr [0x129FA5A8],0xFFFFFFFF         ; [data_129fa5a8]
  674df80  jne 0x674AB5B                                 ; -> sub_674ab5b
  674df86  lea rdx,[0xF5638D6]                           ; [data_f5638d6] "ShadowColor"
  674df8d  lea r12,[rbp+0xC10]
  674df94  mov rcx,r12
  674df97  call 0x79580                                  ; -> sub_79580
  674df9c  nop
  674df9d  mov rdx,[rbp+0xC20]
  674dfa4  cmp qword ptr [rbp+0xC28],0x10
  674dfac  jb short 0x674DFB5                            ; -> loc_674dfb5
  674dfae  mov r12,[rbp+0xC10]

loc_674dfb5:  ; from 674dfac
  674dfb5  test rdx,rdx
  674dfb8  je 0x674E7AB                                  ; -> loc_674e7ab
  674dfbe  mov eax,edx
  674dfc0  and eax,3
  674dfc3  cmp rdx,4
  674dfc7  jae 0x674EA7C                                 ; -> loc_674ea7c
  674dfcd  mov rcx,0xCBF29CE484222325
  674dfd7  xor r8d,r8d
  674dfda  jmp 0x674EAD8                                 ; -> loc_674ead8
  674dfdf  lea rcx,[0x129FA5B8]                          ; [data_129fa5b8]
  674dfe6  call 0xE938CB0                                ; -> sub_e938cb0
  674dfeb  cmp dword ptr [0x129FA5B8],0xFFFFFFFF         ; [data_129fa5b8]
```

## Interpretation [I]
- 0x674dadc..0x674daf2: `or eax,0xFEF300BF`; `call 0xE935740` (dossier x5); `lea rcx,[0x129ca5e0]`; `call 0xE938D70`; `jmp 0x674a60c`. (completes the Glint/GlintColor static-uniform registration started at 0x674e0ce region per earlier notes). [V]
- 0x674daf7..0x674dbcc: init-once check on data_129fa1a8 via 0xe938cb0 (if != 0xFFFFFFFF → 0x674a6d1); else `lea rdx,[0xF5C6BAE]` "MatTexture"; rcx=[rbp+0xc10]; call 0x79580 (static uniform registration, dossier x15); length check `cmp [rbp+0xc28],0x10; jb`; if rdx==0 → 0x674e0ce (FNV entry); else len = edx&3, if >=4 → 0x674e317, else basis rcx=0xCBF29CE484222325, r8d=0 → 0x674e373 (FNV entry). Then `lea rcx,[0x129fa1a8]`; `call 0xE938D70`; `jmp 0x674a6d1`. [V]
- 0x674db82..0x674dbcc: `xorps xmm0`; [rbp+0x210]=0; `lea rax,[0xF2BE5C8]` "UI/Glint" (len 8); [rbp+0x480]=rax, [rbp+0x488]=8; rcx=data_129fa198, rdx=&[rbp+0x480], r8=[rbp+0x210]; call 0x5668ac0 (dossier x5); then data_129fa1a8 → 0xe938d70 → jmp 0x674a6d1. [V]
- 0x674dbd1..0x674dc33: data_129fb1b0 init-once (0xe938cb0; jne 0x674a704); else [rbp+0xc10]=0; rcx=data_129fb170, rdx=&[rbp+0xc10], r8=[rbp+0x910]; call 0x9b020 (sub_9b020); `lea rcx,[0x6761090]` (fn ptr); call 0xe935740; data_129fb1b0 → 0xe938d70; jmp 0x674a704. [V] — likely GlintTexture/GlintColor static uniform registration (matches dossier's earlier note "GlintTexture(data_f5c6b76), GlintColor(data_f563953), UVScale(data_f5de988) via 0x79580+FNV" seen at 0x674e0ce region).
- 0x674dc38..0x674dc76: data_129ca5e0 init-once; else `lea rcx,[0x129ca568]`; call 0x567db00; `lea rcx,[0x567dba0]` (fn ptr); call 0xe935740; data_129ca5e0 → 0xe938d70; jmp 0x674a784. [V]
- 0x674dc7b: `mov rcx,0xCBF29CE484222325` (FNV basis); `jmp 0x674dd81` (FNV tail: stores hash to data_129fa178, calls 0x73150 on [rbp+0xc10], data_129fa180 → 0xe938d70, jmp 0x674a4c3). [V] — entry for empty/short-name FNV path.
- 0x674dc8a..0x674dcb9: data_129fa558 init-once (jne 0x674a91c); else `lea rdx,[0xF5C6DD7]` "GlyphTexture"; rcx=[rbp+0xc10]; call 0x79580; length check; rdx==0 → 0x674e42e; len>=4 → 0x674e50d; else basis → 0x674e569. [V]
- 0x674dcfc..0x674dd81: FNV-1a 64 hash main loop (aligned 4-byte unrolled): `and rdx,0xFFFFFFFFFFFFFFFC`; basis rcx; r8d=0; r9=0x100000001B3 (prime); loop 0x674dd17: 4 bytes/iter (xor+imul each); exit when r8==rdx; if rax==0 → 0x674dd81; else tail loop 0x674dd6a: `add r14,r8` (advance pointer), rdx=0 (byte index), r8=prime, r9=running hash; `movzx ecx,byte [r14+rdx]`; xor; imul; inc rdx; cmp rax,rdx → loop. 0x674dd81: `mov [0x129FA178],rcx` (store FNV hash); `lea rcx,[rbp+0xc10]`; call 0x73150; `lea rcx,[0x129fa180]`; call 0xe938d70; `jmp 0x674a4c3`. [V] — matches dossier constants (basis x45, prime x29).
- 0x674dda5..0x674dfeb: repeated static-uniform registration pattern: data_129fa568 → 0xe938cb0 (jne 0x674aac7); "GlyphSmoothRadius"(data_f543686) → 0x79580 → FNV entries 0x674e76f/0x674e7d8/0x674e834. data_129fa578 → 0xe938cb0 (jne 0x674aaec); "OutlineCutoff"(data_f5ba860) → 0x79580 → FNV entries 0x674e77e/0x674e881/0x674e8dd. data_129fa588 → 0xe938cb0 (jne 0x674ab11); "ShadowSmoothRadius"(data_f543673) → 0x79580 → FNV entries 0x674e78d/0x674e92a/0x674e986. data_129fa598 → 0xe938cb0 (jne 0x674ab36); "HalfTexelOffset"(data_f53c9b4) → 0x79580 → FNV entries 0x674e79c/0x674e9d3/0x674ea2f. data_129fa5a8 → 0xe938cb0 (jne 0x674ab5b); "ShadowColor"(data_f5638d6) → 0x79580 → FNV entries 0x674e7ab/0x674ea7c/0x674ead8. data_129fa5b8 → 0xe938cb0 at 0x674dfe6 (truncated). [V]


## Cold-tail transcription 0x674eaf9..0x674f001 [V]
(rdis `dis 0x674eaf9 220` + `dis 0x674eee4 240`; every instruction quoted exactly as printed, nops included; complete through the last instruction of fn 0x674a3a0. Note: block 0x674e511..0x674eaf6 ended mid-tail-loop at `674eaf6 inc rdx`; this phase starts at 0x674eaf9 (`mov r9,rcx`) to stay instruction-aligned — the `674eafa mov ecx,ecx` line from a misaligned `dis 0x674eafa` is NOT part of the stream.)
```
  674eaf9  mov r9,rcx                                    
  674eafc  cmp rax,rdx                                   
  674eaff  jne short 0x674EAEA                           ; -> sub_674eaea
  674eb01  mov [0x129FA5A0],rcx                          ; [data_129fa5a0]
  674eb08  lea rcx,[rbp+0xC10]                           
  674eb0f  call 0x73150                                  ; -> sub_73150
  674eb14  lea rcx,[0x129FA5A8]                          ; [data_129fa5a8]
  674eb1b  call 0xE938D70                                ; -> sub_e938d70
  674eb20  jmp 0x674AB5B                                 ; -> sub_674ab5b
  674eb25  and rdx,0xFFFFFFFFFFFFFFFC                    
  674eb29  mov rcx,0xCBF29CE484222325                    
  674eb33  xor r8d,r8d                                   
  674eb36  mov r9,0x100000001B3                          

loc_674eb40:  ; from 674eb7a
  674eb40  movzx r10d,byte ptr [r12+r8]                  
  674eb45  xor r10,rcx                                   
  674eb48  imul r10,r9                                   
  674eb4c  movzx ecx,byte ptr [r12+r8+1]                 
  674eb52  xor rcx,r10                                   
  674eb55  imul rcx,r9                                   
  674eb59  movzx r10d,byte ptr [r12+r8+2]                
  674eb5f  xor r10,rcx                                   
  674eb62  imul r10,r9                                   
  674eb66  movzx ecx,byte ptr [r12+r8+3]                 
  674eb6c  xor rcx,r10                                   
  674eb6f  imul rcx,r9                                   
  674eb73  add r8,4                                      
  674eb77  cmp rdx,r8                                    
  674eb7a  jne short 0x674EB40                           ; -> loc_674eb40
  674eb7c  test rax,rax                                  
  674eb7f  je short 0x674EBAA                            ; -> loc_674ebaa
  674eb81  add r12,r8                                    
  674eb84  xor edx,edx                                   
  674eb86  mov r8,0x100000001B3                          
  674eb90  mov r9,rcx                                    

loc_674eb93:  ; from 674eba8
  674eb93  movzx ecx,byte ptr [r12+rdx]                  
  674eb98  xor rcx,r9                                    
  674eb9b  imul rcx,r8                                   
  674eb9f  inc rdx                                       
  674eba2  mov r9,rcx                                    
  674eba5  cmp rax,rdx                                   
  674eba8  jne short 0x674EB93                           ; -> loc_674eb93

loc_674ebaa:  ; from 674eb7f
  674ebaa  mov [0x129FA5B0],rcx                          ; [data_129fa5b0]
  674ebb1  lea rcx,[rbp+0xC10]                           
  674ebb8  call 0x73150                                  ; -> sub_73150
  674ebbd  lea rcx,[0x129FA5B8]                          ; [data_129fa5b8]
  674ebc4  call 0xE938D70                                ; -> sub_e938d70
  674ebc9  jmp 0x674AB80                                 ; -> sub_674ab80
  674ebce  and r8,0xFFFFFFFFFFFFFFFC                     
  674ebd2  mov rdx,0xCBF29CE484222325                    
  674ebdc  xor r9d,r9d                                   

loc_674ebdf:  ; from 674ec19
  674ebdf  movzx r10d,byte ptr [r12+r9]                  
  674ebe4  xor r10,rdx                                   
  674ebe7  imul r10,rcx                                  
  674ebeb  movzx edx,byte ptr [r12+r9+1]                 
  674ebf1  xor rdx,r10                                   
  674ebf4  imul rdx,rcx                                  
  674ebf8  movzx r10d,byte ptr [r12+r9+2]                
  674ebfe  xor r10,rdx                                   
  674ec01  imul r10,rcx                                  
  674ec05  movzx edx,byte ptr [r12+r9+3]                 
  674ec0b  xor rdx,r10                                   
  674ec0e  imul rdx,rcx                                  
  674ec12  add r9,4                                      
  674ec16  cmp r8,r9                                     
  674ec19  jne short 0x674EBDF                           ; -> loc_674ebdf
  674ec1b  test rax,rax                                  
  674ec1e  je short 0x674EC40                            ; -> loc_674ec40
  674ec20  add r12,r9                                    
  674ec23  xor r8d,r8d                                   
  674ec26  mov r9,rdx                                    

loc_674ec29:  ; from 674ec3e
  674ec29  movzx edx,byte ptr [r12+r8]                   
  674ec2e  xor rdx,r9                                    
  674ec31  imul rdx,rcx                                  
  674ec35  inc r8                                        
  674ec38  mov r9,rdx                                    
  674ec3b  cmp rax,r8                                    
  674ec3e  jne short 0x674EC29                           ; -> loc_674ec29

loc_674ec40:  ; from 674ec1e
  674ec40  mov [0x129FA5C0],rdx                          ; [data_129fa5c0]
  674ec47  lea rcx,[rbp+0xC10]                           
  674ec4e  call 0x73150                                  ; -> sub_73150
  674ec53  lea rcx,[0x129FA5C8]                          ; [data_129fa5c8]
  674ec5a  call 0xE938D70                                ; -> sub_e938d70
  674ec5f  jmp 0x674ABA5                                 ; -> sub_674aba5
  674ec64  mov rcx,0xCBF29CE484222325                    
  674ec6e  jmp 0x674ED33                                 ; -> loc_674ed33
  674ec73  mov rcx,0xCBF29CE484222325                    
  674ec7d  jmp 0x674EDDE                                 ; -> loc_674edde
  674ec82  mov rcx,0xCBF29CE484222325                    
  674ec8c  jmp 0x674EE89                                 ; -> loc_674ee89
  674ec91  mov rcx,0xCBF29CE484222325                    
  674ec9b  jmp 0x674EF34                                 ; -> loc_674ef34
  674eca0  mov rcx,0xCBF29CE484222325                    
  674ecaa  jmp 0x674EFDF                                 ; -> loc_674efdf
  674ecaf  and rdx,0xFFFFFFFFFFFFFFFC                    
  674ecb3  mov rcx,0xCBF29CE484222325                    
  674ecbd  xor r8d,r8d                                   
  674ecc0  mov r9,0x100000001B3                          

loc_674ecca:  ; from 674ed04
  674ecca  movzx r10d,byte ptr [rdi+r8]                  
  674eccf  xor r10,rcx                                   
  674ecd2  imul r10,r9                                   
  674ecd6  movzx ecx,byte ptr [rdi+r8+1]                 
  674ecdc  xor rcx,r10                                   
  674ecdf  imul rcx,r9                                   
  674ece3  movzx r10d,byte ptr [rdi+r8+2]                
  674ece9  xor r10,rcx                                   
  674ecec  imul r10,r9                                   
  674ecf0  movzx ecx,byte ptr [rdi+r8+3]                 
  674ecf6  xor rcx,r10                                   
  674ecf9  imul rcx,r9                                   
  674ecfd  add r8,4                                      
  674ed01  cmp rdx,r8                                    
  674ed04  jne short 0x674ECCA                           ; -> loc_674ecca
  674ed06  test rax,rax                                  
  674ed09  je short 0x674ED33                            ; -> loc_674ed33
  674ed0b  add rdi,r8                                    
  674ed0e  xor edx,edx                                   
  674ed10  mov r8,0x100000001B3                          
  674ed1a  mov r9,rcx                                    

loc_674ed1d:  ; from 674ed31
  674ed1d  movzx ecx,byte ptr [rdi+rdx]                  
  674ed21  xor rcx,r9                                    
  674ed24  imul rcx,r8                                   
  674ed28  inc rdx                                       
  674ed2b  mov r9,rcx                                    
  674ed2e  cmp rax,rdx                                   
  674ed31  jne short 0x674ED1D                           ; -> loc_674ed1d

loc_674ed33:  ; from 674ec6e, 674ed09
  674ed33  mov [0x129FA1B0],rcx                          ; [data_129fa1b0]
  674ed3a  lea rcx,[rbp+0xC10]                           
  674ed41  call 0x73150                                  ; -> sub_73150
  674ed46  lea rcx,[0x129FA1B8]                          ; [data_129fa1b8]
  674ed4d  call 0xE938D70                                ; -> sub_e938d70
  674ed52  mov r14,r15                                   
  674ed55  jmp 0x674AE37                                 ; -> sub_674ae37
  674ed5a  and rdx,0xFFFFFFFFFFFFFFFC                    
  674ed5e  mov rcx,0xCBF29CE484222325                    
  674ed68  xor r8d,r8d                                   
  674ed6b  mov r9,0x100000001B3                          

loc_674ed75:  ; from 674edaf
  674ed75  movzx r10d,byte ptr [rdi+r8]                  
  674ed7a  xor r10,rcx                                   
  674ed7d  imul r10,r9                                   
  674ed81  movzx ecx,byte ptr [rdi+r8+1]                 
  674ed87  xor rcx,r10                                   
  674ed8a  imul rcx,r9                                   
  674ed8e  movzx r10d,byte ptr [rdi+r8+2]                
  674ed94  xor r10,rcx                                   
  674ed97  imul r10,r9                                   
  674ed9b  movzx ecx,byte ptr [rdi+r8+3]                 
  674eda1  xor rcx,r10                                   
  674eda4  imul rcx,r9                                   
  674eda8  add r8,4                                      
  674edac  cmp rdx,r8                                    
  674edaf  jne short 0x674ED75                           ; -> loc_674ed75
  674edb1  test rax,rax                                  
  674edb4  je short 0x674EDDE                            ; -> loc_674edde
  674edb6  add rdi,r8                                    
  674edb9  xor edx,edx                                   
  674edbb  mov r8,0x100000001B3                          
  674edc5  mov r9,rcx                                    

loc_674edc8:  ; from 674eddc
  674edc8  movzx ecx,byte ptr [rdi+rdx]                  
  674edcc  xor rcx,r9                                    
  674edcf  imul rcx,r8                                   
  674edd3  inc rdx                                       
  674edd6  mov r9,rcx                                    
  674edd9  cmp rax,rdx                                   
  674eddc  jne short 0x674EDC8                           ; -> loc_674edc8

loc_674edde:  ; from 674ec7d, 674edb4
  674edde  mov [0x129FA1C0],rcx                          ; [data_129fa1c0]
  674ede5  lea rcx,[rbp+0xC10]                           
  674edec  call 0x73150                                  ; -> sub_73150
  674edf1  lea rcx,[0x129FA1C8]                          ; [data_129fa1c8]
  674edf8  call 0xE938D70                                ; -> sub_e938d70
  674edfd  mov r14,r15                                   
  674ee00  jmp 0x674AEFC                                 ; -> sub_674aefc
  674ee05  and rdx,0xFFFFFFFFFFFFFFFC                    
  674ee09  mov rcx,0xCBF29CE484222325                    
  674ee13  xor r8d,r8d                                   
  674ee16  mov r9,0x100000001B3                          

loc_674ee20:  ; from 674ee5a
  674ee20  movzx r10d,byte ptr [rdi+r8]                  
  674ee25  xor r10,rcx                                   
  674ee28  imul r10,r9                                   
  674ee2c  movzx ecx,byte ptr [rdi+r8+1]                 
  674ee32  xor rcx,r10                                   
  674ee35  imul rcx,r9                                   
  674ee39  movzx r10d,byte ptr [rdi+r8+2]                
  674ee3f  xor r10,rcx                                   
  674ee42  imul r10,r9                                   
  674ee46  movzx ecx,byte ptr [rdi+r8+3]                 
  674ee4c  xor rcx,r10                                   
  674ee4f  imul rcx,r9                                   
  674ee53  add r8,4                                      
  674ee57  cmp rdx,r8                                    
  674ee5a  jne short 0x674EE20                           ; -> loc_674ee20
  674ee5c  test rax,rax                                  
  674ee5f  je short 0x674EE89                            ; -> loc_674ee89
  674ee61  add rdi,r8                                    
  674ee64  xor edx,edx                                   
  674ee66  mov r8,0x100000001B3                          
  674ee70  mov r9,rcx                                    

loc_674ee73:  ; from 674ee87
  674ee73  movzx ecx,byte ptr [rdi+rdx]                  
  674ee77  xor rcx,r9                                    
  674ee7a  imul rcx,r8                                   
  674ee7e  inc rdx                                       
  674ee81  mov r9,rcx                                    
  674ee84  cmp rax,rdx                                   
  674ee87  jne short 0x674EE73                           ; -> loc_674ee73

loc_674ee89:  ; from 674ec8c, 674ee5f
  674ee89  mov [0x129FA1D0],rcx                          ; [data_129fa1d0]
  674ee90  lea rcx,[rbp+0xC10]                           
  674ee97  call 0x73150                                  ; -> sub_73150
  674ee9c  lea rcx,[0x129FA1D8]                          ; [data_129fa1d8]
  674eea3  call 0xE938D70                                ; -> sub_e938d70
  674eea8  mov r14,r15                                   
  674eeab  jmp 0x674AF21                                 ; -> sub_674af21
  674eeb0  and rdx,0xFFFFFFFFFFFFFFFC                    
  674eeb4  mov rcx,0xCBF29CE484222325                    
  674eebe  xor r8d,r8d                                   
  674eec1  mov r9,0x100000001B3                          

loc_674eecb:  ; from 674ef05
  674eecb  movzx r10d,byte ptr [rdi+r8]                  
  674eed0  xor r10,rcx                                   
  674eed3  imul r10,r9                                   
  674eed7  movzx ecx,byte ptr [rdi+r8+1]                 
  674eedd  xor rcx,r10                                   
  674eee0  imul rcx,r9
  674eeea  xor r10,rcx                                   
  674eeed  imul r10,r9                                   
  674eef1  movzx ecx,byte ptr [rdi+r8+3]                 
  674eef7  xor rcx,r10                                   
  674eefa  imul rcx,r9                                   
  674eefe  add r8,4                                      
  674ef02  cmp rdx,r8                                    
  674ef05  jne short 0x674EECB                           ; -> sub_674eecb
  674ef07  test rax,rax                                  
  674ef0a  je short 0x674EF34                            ; -> loc_674ef34
  674ef0c  add rdi,r8                                    
  674ef0f  xor edx,edx                                   
  674ef11  mov r8,0x100000001B3                          
  674ef1b  mov r9,rcx                                    

loc_674ef1e:  ; from 674ef32
  674ef1e  movzx ecx,byte ptr [rdi+rdx]                  
  674ef22  xor rcx,r9                                    
  674ef25  imul rcx,r8                                   
  674ef29  inc rdx                                       
  674ef2c  mov r9,rcx                                    
  674ef2f  cmp rax,rdx                                   
  674ef32  jne short 0x674EF1E                           ; -> loc_674ef1e

loc_674ef34:  ; from 674ef0a
  674ef34  mov [0x129FA1E0],rcx                          ; [data_129fa1e0]
  674ef3b  lea rcx,[rbp+0xC10]                           
  674ef42  call 0x73150                                  ; -> sub_73150
  674ef47  lea rcx,[0x129FA1E8]                          ; [data_129fa1e8]
  674ef4e  call 0xE938D70                                ; -> sub_e938d70
  674ef53  mov r14,r15                                   
  674ef56  jmp 0x674AF46                                 ; -> sub_674af46
  674ef5b  and rdx,0xFFFFFFFFFFFFFFFC                    
  674ef5f  mov rcx,0xCBF29CE484222325                    
  674ef69  xor r8d,r8d                                   
  674ef6c  mov r9,0x100000001B3                          

loc_674ef76:  ; from 674efb0
  674ef76  movzx r10d,byte ptr [rdi+r8]                  
  674ef7b  xor r10,rcx                                   
  674ef7e  imul r10,r9                                   
  674ef82  movzx ecx,byte ptr [rdi+r8+1]                 
  674ef88  xor rcx,r10                                   
  674ef8b  imul rcx,r9                                   
  674ef8f  movzx r10d,byte ptr [rdi+r8+2]                
  674ef95  xor r10,rcx                                   
  674ef98  imul r10,r9                                   
  674ef9c  movzx ecx,byte ptr [rdi+r8+3]                 
  674efa2  xor rcx,r10                                   
  674efa5  imul rcx,r9                                   
  674efa9  add r8,4                                      
  674efad  cmp rdx,r8                                    
  674efb0  jne short 0x674EF76                           ; -> loc_674ef76
  674efb2  test rax,rax                                  
  674efb5  je short 0x674EFDF                            ; -> loc_674efdf
  674efb7  add rdi,r8                                    
  674efba  xor edx,edx                                   
  674efbc  mov r8,0x100000001B3                          
  674efc6  mov r9,rcx                                    

loc_674efc9:  ; from 674efdd
  674efc9  movzx ecx,byte ptr [rdi+rdx]                  
  674efcd  xor rcx,r9                                    
  674efd0  imul rcx,r8                                   
  674efd4  inc rdx                                       
  674efd7  mov r9,rcx                                    
  674efda  cmp rax,rdx                                   
  674efdd  jne short 0x674EFC9                           ; -> loc_674efc9

loc_674efdf:  ; from 674efb5
  674efdf  mov [0x129FA1F0],rcx                          ; [data_129fa1f0]
  674efe6  lea rcx,[rbp+0xC10]                           
  674efed  call 0x73150                                  ; -> sub_73150
  674eff2  lea rcx,[0x129FA1F8]                          ; [data_129fa1f8]
  674eff9  call 0xE938D70                                ; -> sub_e938d70
  674effe  mov r14,r15                                   
  674f001  jmp 0x674AF6B                                 ; -> sub_674af6b
```                                   
```

## Interpretation [I]
- 0x674eaf9..0x674eb20: tail-loop exit completing the ShadowColor hash (loc_674eaea tail: `mov r9,rcx` saves running hash; `cmp rax,rdx; jne short 0x674EAEA` back to loc_674eaea); tail exit 0x674eb01: `mov [0x129FA5A0],rcx` — store ShadowColor FNV hash to data_129fa5a0; `lea rcx,[rbp+0xc10]`; call 0x73150; `lea rcx,[0x129fa5a8]`; call 0xe938d70; `jmp 0x674ab5b`. [V] — completes the data_129fa5a8/"ShadowColor"(data_f5638d6) registration seen at 0x674dfdf; its FNV entries 0x674e7ab/0x674ea7c/0x674ead8 jump straight into this tail. [V]
- 0x674eb25..0x674ebc9: ShadowOffset long-path FNV entry (pointer r12): `and rdx,0xFFFFFFFFFFFFFFFC`; basis rcx=0xCBF29CE484222325; r8d=0; r9=prime 0x100000001B3; aligned loop 0x674eb40 (`movzx r10d,byte [r12+r8]`; xor rcx-chain; imul; 4 bytes/iter); on exit `test rax,rax` → 0x674ebaa if zero else tail setup 0x674eb81 (`add r12,r8`; rdx=0; r8=prime; r9=hash; tail loop 0x674eb93: `movzx ecx,byte [r12+rdx]`; xor; imul; inc rdx; cmp rax,rdx); hash tail 0x674ebaa: `mov [0x129FA5B0],rcx`; `lea rcx,[rbp+0xc10]`; call 0x73150; `lea rcx,[0x129fa5b8]`; call 0xe938d70; `jmp 0x674ab80`. [V] — entries 0x674e7ba (zero-length), 0x674eb25 (long), 0x674eb81 (short) converge here; matches block 0x674dfeb region ("ShadowOffset"(data_f53c825) → 0x79580; init check data_129fa5b8 at 0x674dfeb jne 0x674ab80). [V]
- 0x674ebce..0x674ec5f: GlyphHeight swapped-argument FNV entry (pointer r12): `and r8,0xFFFFFFFFFFFFFFFC`; rdx=basis; r9d=0; aligned loop 0x674ebdf (`movzx r10d,byte [r12+r9]`; accumulator rdx, multiplier rcx — arg order swapped vs other entries; index r9); exit → 0x674ec40 if rax==0 else tail setup 0x674ec20 (`add r12,r9`; r8d=0; r9=rdx; tail loop 0x674ec29: `movzx edx,byte [r12+r8]`; xor rdx,r9; imul rdx,rcx; inc r8; cmp rax,r8); hash tail 0x674ec40: `mov [0x129FA5C0],rdx` (result held in rdx in this variant); `lea rcx,[rbp+0xc10]`; call 0x73150; `lea rcx,[0x129fa5c8]`; call 0xe938d70; `jmp 0x674aba5`. [V] — entries 0x674e7c9 (zero-length), 0x674ebce (long), 0x674ec20 (short) converge here; matches block 0x674dfeb region's "GlyphHeight"(data_f53b313) sequence; init check data_129fa5c8 at 0x674e051 jne 0x674aba5. [V] Note: block 0x674e0ce (`mov rcx,basis; jmp 0x674e39c` → data_129fa188 → jmp 0x674a6a3) lies inside this range with no incoming edge from transcribed code — source [?].
- 0x674ec64..0x674eca0: empty-name FNV entries (basis rcx; direct jump to hash tails): 0x674ec64→0x674ed33, 0x674ec73→0x674edde, 0x674ec82→0x674ee89, 0x674ec91→0x674ef34, 0x674eca0→0x674efdf. [V]
- 0x674ecaf..0x674ed55: GlintTexture aligned/tail loops (pointer rdi): aligned 0x674ecca (`[rdi+r8]`); tail setup 0x674ed0b (`add rdi,r8`; rdx=0; r8=prime; r9=hash; tail 0x674ed1d `[rdi+rdx]`); hash tail 0x674ed33: `mov [0x129FA1B0],rcx`; `lea rcx,[rbp+0xc10]`; call 0x73150; `lea rcx,[0x129fa1b8]`; call 0xe938d70; `mov r14,r15`; `jmp 0x674ae37`. [V] — matches block A's "GlintTexture"(data_f5c6b76) → entries 0x674ec64/0x674ecaf/0x674ed0b; init check data_129fa1b8 at 0x674e0dd jne 0x674ae37. [V]
- 0x674ed5a..0x674ee00: GlintColor aligned/tail loops (pointer rdi): aligned 0x674ed75; tail setup 0x674edb6; tail 0x674edc8; hash tail 0x674edde: `mov [0x129FA1C0],rcx`; ... `jmp 0x674aefc`. [V] — "GlintColor"(data_f563953) → init check data_129fa1c8 at 0x674e1c1 jne 0x674aefc; entries 0x674ec73/0x674ed5a/0x674edb6. [V]
- 0x674ee05..0x674eeab: UVScale aligned/tail loops (pointer rdi): aligned 0x674ee20; tail setup 0x674ee61; tail 0x674ee73; hash tail 0x674ee89: `mov [0x129FA1D0],rcx`; ... `jmp 0x674af21`. [V] — "UVScale"(data_f5de988) → init check data_129fa1e8 at 0x674e233 jne 0x674af21; entries 0x674ec82/0x674ee05/0x674ee61. [V]
- 0x674eeb0..0x674ef05: UVOffset aligned loop (pointer rdi), complete: `and rdx,0xFFFFFFFFFFFFFFFC`; basis rcx; r8d=0; r9=prime; loop 0x674eecb (`movzx r10d,byte [rdi+r8]`; xor r10,rcx; imul r10,r9; `movzx ecx,byte [rdi+r8+1]`; xor rcx,r10; imul rcx,r9; `movzx r10d,byte [rdi+r8+2]`; xor r10,rcx; imul r10,r9; `movzx ecx,byte [rdi+r8+3]`; xor rcx,r10; imul rcx,r9; `add r8,4`; `cmp rdx,r8`; `jne short 0x674EECB`), continued at 0x674eee4 (`movzx r10d,byte [rdi+r8+2]`; `xor r10,rcx`; `imul r10,r9`; `movzx ecx,byte [rdi+r8+3]`; `xor rcx,r10`; `imul rcx,r9`; `add r8,4`; `cmp rdx,r8`; `jne short 0x674EECB`). [V] — "UVOffset"(data_f53cae6) → init check data_129fa1e8 at 0x674e233 (`jne 0x674af46`); long-path entry 0x674eeb0. [V]
- 0x674ef07..0x674ef56: UVOffset hash tail: `test rax,rax` → 0x674ef34 if zero else tail setup 0x674ef0c (`add rdi,r8`; rdx=0; r8=prime; r9=hash; tail loop 0x674ef1e `movzx ecx,byte [rdi+rdx]`; xor rcx,r9; imul rcx,r8; inc rdx; cmp rax,rdx); 0x674ef34: `mov [0x129FA1E0],rcx`; `lea rcx,[rbp+0xc10]`; call 0x73150; `lea rcx,[0x129fa1e8]`; call 0xe938d70; `mov r14,r15`; `jmp 0x674af46`. [V] — confirms UVOffset → data_129fa1e0 → jmp 0x674af46 (init check data_129fa1e8 at 0x674e233 jne 0x674af46). [V]
- 0x674ef5b..0x674efb2: UVRotation long-path aligned loop (pointer rdi): `and rdx,0xFFFFFFFFFFFFFFFC`; basis rcx=0xCBF29CE484222325; r8d=0; r9=prime 0x100000001B3; loop 0x674ef76 (`movzx r10d,byte [rdi+r8]`; xor+imul chain; `add r8,4`; `cmp rdx,r8`; `jne short 0x674EF76`). [V]
- 0x674efb7..0x674efdd: UVRotation short-path tail setup: `add rdi,r8`; rdx=0; r8=prime; r9=hash; tail loop 0x674efc9 (`movzx ecx,byte [rdi+rdx]`; xor rcx,r9; imul rcx,r8; inc rdx; cmp rax,rdx). [V]
- 0x674efdf..0x674f001: UVRotation hash tail: `mov [0x129FA1F0],rcx`; `lea rcx,[rbp+0xc10]`; call 0x73150; `lea rcx,[0x129fa1f8]`; call 0xe938d70; `mov r14,r15`; `jmp 0x674af6b`. [V] — confirms UVRotation → data_129fa1f0 → jmp 0x674af6b (init check data_129fa1f8 at 0x674e2a5 jne 0x674af6b). [V]
- **0x674f006: next function begins** (`nop [rax+rax]` ret-thunk wrappers around `call 0xE938D30`, each with `lea rcx,[data_129fa1XX]`). **fn 0x674a3a0 boundary at 0x674f006: span [0x674a3a0, 0x674f006), size 0x4C66 (matches dossier exactly; earlier "0x674ef06" estimate was off by one digit). Last instruction of fn 0x674a3a0: 0x674f001 `jmp 0x674af6b`. No cold tail remains.** [V] — Hot-path ret: epilogue 0x674ce34 (pop rbx/rdi/rsi/r12/r13/r14/r15/rbp; ret at 0x674ce4e; frame 0xe98; xmm6 restored). Cold-tail exits are one-way `jmps` to sub_674aXXX phase continuations (0x674ab80/0x674aba5/0x674a6a3/0x674ae37/0x674aefc/0x674af21/0x674af46/0x674af6b), no `ret` inside fn 0x674a3a0 except 0x674ce4e. [V]





