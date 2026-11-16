# Unit U-E4X-B4: chunk extractor body B — lines 2051..2680 of docs/data/listings/e4_B.txt
## NEXT
Next line to do: none — all phases 1-16 complete; body B listing ends at line 2680 (RVA 0x66f2817, `jmp short 0x66F27D0`, loop not exited in this range).
Base RVA: 0x66f1c35; end RVA at line 2680: 0x66f2817
Context: body B = K==13 light_source inline body of ChunkGeometry extractor at 0x66ea3d0 (docs/functions/66ea3d0.md)

### lines 2051..2090
```asm
0x66f1c35  mov rax,[rax]
0x66f1c38  mov rcx,rbx
0x66f1c3b  call qword ptr [0xF99FFA0]
0x66f1c41  lock dec dword ptr [rbx+0xC]
0x66f1c45  jne short 0x66F1C60
0x66f1c47  mov rax,[rbx]
0x66f1c4a  mov rax,[rax+8]
0x66f1c4e  mov rcx,rbx
0x66f1c51  call qword ptr [0xF99FFA0]
0x66f1c57  nop [rax+rax]
0x66f1c60  mov rbx,[rbp+0x1418]
0x66f1c67  test rbx,rbx
0x66f1c6a  je short 0x66F1CA0
0x66f1c6c  lock dec dword ptr [rbx+8]
0x66f1c70  jne short 0x66F1CA0
0x66f1c72  mov rax,[rbx]
0x66f1c75  mov rax,[rax]
0x66f1c78  mov rcx,rbx
0x66f1c7b  call qword ptr [0xF99FFA0]
0x66f1c81  lock dec dword ptr [rbx+0xC]
0x66f1c85  jne short 0x66F1CA0
0x66f1c87  mov rax,[rbx]
0x66f1c8a  mov rax,[rax+8]
0x66f1c8e  mov rcx,rbx
0x66f1c91  call qword ptr [0xF99FFA0]
0x66f1c97  nop [rax+rax]
0x66f1ca0  mov rbx,[rbp+0x1668]
0x66f1ca7  test rbx,rbx
0x66f1caa  je 0x66F26C0
0x66f1cb0  lock dec dword ptr [rbx+8]
0x66f1cb4  jne 0x66F26C0
0x66f1cba  mov rax,[rbx]
0x66f1cbd  mov rax,[rax]
0x66f1cc0  mov rcx,rbx
0x66f1cc3  call qword ptr [0xF99FFA0]
0x66f1cc9  lock dec dword ptr [rbx+0xC]
0x66f1ccd  jne 0x66F26C0
0x66f1cd3  mov rax,[rbx]
0x66f1cd6  mov rax,[rax+8]
0x66f1cda  mov rcx,rbx
```
Meaning: Three refcount-release sequences on heap objects [V] (each: `lock dec` refcount at +8 or +0xC; if it reaches zero, read the object's vtable and call dtor via [rax] then [rax+8] through indirect call [0xF99FFA0] [V]); applied to objects at [rbp+0x1418] and [rbp+0x1668], with null-check skip via je [V]; falls through to another [0xF99FFA0] call then `jmp 0x66F26C0` [V]. The `lock dec` + [0xF99FFA0] dtor pattern matches refcounted-object release seen in body B1 [I].

### lines 2091..2130
```asm
0x66f1cdd  call qword ptr [0xF99FFA0]
0x66f1ce3  jmp 0x66F26C0
0x66f1ce8  lea rcx,[r15+0x8A0]
0x66f1cef  lea r8,[rbp+0x15D8]
0x66f1cf6  call 0x1EF6F90
0x66f1cfb  nop
0x66f1cfc  mov rcx,[0x1233E1B0]
0x66f1d03  mov rax,[rcx]
0x66f1d06  mov rax,[rax+0x10]
0x66f1d0a  movzx edx,byte ptr [rbp+0x16D4]
0x66f1d11  call qword ptr [0xF99FFA0]
0x66f1d17  nop
0x66f1d18  mov eax,[r15+0x8A8]
0x66f1d1f  sub eax,[r15+0x8A0]
0x66f1d26  shr eax,1
0x66f1d28  dec eax
0x66f1d2a  mov [rbp+0x1140],ax
0x66f1d31  mov rcx,[0x1233E1B0]
0x66f1d38  mov rax,[rcx]
0x66f1d3b  mov rax,[rax+0x10]
0x66f1d3f  mov dl,0x4A
0x66f1d41  call qword ptr [0xF99FFA0]
0x66f1d47  nop
0x66f1d48  mov [rbp+0x16D4],al
0x66f1d4e  mov rdx,[r15+0x758]
0x66f1d55  cmp rdx,[r15+0x760]
0x66f1d5c  je 0x66F1EE8
0x66f1d62  lea rcx,[rbp+0x1580]
0x66f1d69  mov eax,[rcx+0x10]
0x66f1d6c  mov [rdx+0x10],eax
0x66f1d6f  movups xmm0,[rcx]
0x66f1d72  movups [rdx],xmm0
0x66f1d75  movzx eax,byte ptr [rbp+0x1594]
0x66f1d7c  mov [rdx+0x14],al
0x66f1d7f  movss xmm0,[rbp+0x1598]
0x66f1d87  movss [rdx+0x18],xmm0
0x66f1d8c  movss xmm0,[rbp+0x159C]
0x66f1d94  movss [rdx+0x1C],xmm0
0x66f1d99  movss xmm0,[rbp+0x15A0]
0x66f1da1  movss [rdx+0x20],xmm0
```
Meaning: Finish the release, then `jmp 0x66F26C0` [V]. A helper `0x1EF6F90` is called with rcx=[r15+0x8A0], r8=[rbp+0x15D8] [V], followed by the recurring telemetry sequence: global [0x1233E1B0] → vtable [rax+0x10] → dl=[rbp+0x16D4] → indirect call [0xF99FFA0] [V]. Then a count is computed: ([r15+0x8A8]-[r15+0x8A0]) >> 1 - 1, stored as word at [rbp+0x1140] [V]; telemetry repeats with dl=0x4A and [rbp+0x16D4]=al [V]. If [r15+0x758]==[r15+0x760] (buffer full) jump to 0x66F1EE8 [V]; otherwise a 0x58-byte record at [rdx]=[r15+0x758] is filled: dword at +0x10, byte at +0x14, floats at +0x18/0x1C/0x20/0x24 from [rbp+0x1594..0x15A4], and 16-byte chunks at +0x28/0x38/0x47 from [rbp+0x1444+0x164/0x174/0x183] [V].

### lines 2131..2170
```asm
0x66f1da6  movss xmm0,[rbp+0x15A4]
0x66f1dae  movss [rdx+0x24],xmm0
0x66f1db3  lea rax,[rbp+0x1444]
0x66f1dba  movups xmm0,[rax+0x164]
0x66f1dc1  movups xmm1,[rax+0x174]
0x66f1dc8  movups xmm2,[rax+0x183]
0x66f1dcf  movups [rdx+0x28],xmm0
0x66f1dd3  movups [rdx+0x38],xmm1
0x66f1dd7  movups [rdx+0x47],xmm2
0x66f1ddb  add qword ptr [r15+0x758],0x58
0x66f1de3  jmp 0x66F1EFC
0x66f1de8  lea rcx,[r15+0x8A0]
0x66f1def  lea r8,[rbp+0x15D8]
0x66f1df6  call 0x1EF6F90
0x66f1dfb  nop
0x66f1dfc  mov rcx,[0x1233E1B0]
0x66f1e03  mov rax,[rcx]
0x66f1e06  mov rax,[rax+0x10]
0x66f1e0a  movzx edx,byte ptr [rbp+0x16D4]
0x66f1e11  call qword ptr [0xF99FFA0]
0x66f1e17  nop
0x66f1e18  mov eax,[r15+0x8A8]
0x66f1e1f  sub eax,[r15+0x8A0]
0x66f1e26  shr eax,1
0x66f1e28  dec eax
0x66f1e2a  mov [rbp+0x1140],ax
0x66f1e31  mov rcx,[0x1233E1B0]
0x66f1e38  mov rax,[rcx]
0x66f1e3b  mov rax,[rax+0x10]
0x66f1e3f  mov dl,0x4A
0x66f1e41  call qword ptr [0xF99FFA0]
0x66f1e47  nop
0x66f1e48  mov [rbp+0x16D4],al
0x66f1e4e  mov rdx,[r15+0x758]
0x66f1e55  cmp rdx,[r15+0x760]
0x66f1e5c  je 0x66F1F83
0x66f1e62  lea rcx,[rbp+0x1580]
0x66f1e69  mov eax,[rcx+0x10]
0x66f1e6c  mov [rdx+0x10],eax
0x66f1e6f  movups xmm0,[rcx]
```
Meaning: Finish storing the last 16-byte chunk at [rdx+0x47] [V], advance [r15+0x758] by 0x58 (fixed record stride) [V], and `jmp 0x66F1EFC` [V]. Otherwise the second buffer slot repeats: helper 0x1EF6F90 [V], telemetry with dl from [rbp+0x16D4] then 0x4A [V], count ([r15+0x8A8]-[r15+0x8A0])>>1-1 → [rbp+0x1140] [V]. If [r15+0x758]==[r15+0x760] jump to 0x66F1F83 [V]; else start filling a second record at [rdx]=[r15+0x758] beginning with dword +0x10 and movups of [rbp+0x1580] [V].

### lines 2171..2210
```asm
0x66f1e72  movups [rdx],xmm0
0x66f1e75  movzx eax,byte ptr [rbp+0x1594]
0x66f1e7c  mov [rdx+0x14],al
0x66f1e7f  movss xmm0,[rbp+0x1598]
0x66f1e87  movss [rdx+0x18],xmm0
0x66f1e8c  movss xmm0,[rbp+0x159C]
0x66f1e94  movss [rdx+0x1C],xmm0
0x66f1e99  movss xmm0,[rbp+0x15A0]
0x66f1ea1  movss [rdx+0x20],xmm0
0x66f1ea6  movss xmm0,[rbp+0x15A4]
0x66f1eae  movss [rdx+0x24],xmm0
0x66f1eb3  lea rax,[rbp+0x1444]
0x66f1eba  movups xmm0,[rax+0x164]
0x66f1ec1  movups xmm1,[rax+0x174]
0x66f1ec8  movups xmm2,[rax+0x183]
0x66f1ecf  movups [rdx+0x28],xmm0
0x66f1ed3  movups [rdx+0x38],xmm1
0x66f1ed7  movups [rdx+0x47],xmm2
0x66f1edb  add qword ptr [r15+0x758],0x58
0x66f1ee3  jmp 0x66F1F97
0x66f1ee8  lea rcx,[r15+0x750]
0x66f1eef  lea r8,[rbp+0x1580]
0x66f1ef6  call 0x6760A80
0x66f1efb  nop
0x66f1efc  mov rcx,[0x1233E1B0]
0x66f1f03  mov rax,[rcx]
0x66f1f06  mov rax,[rax+0x10]
0x66f1f0a  movzx edx,byte ptr [rbp+0x16D4]
0x66f1f11  call qword ptr [0xF99FFA0]
0x66f1f17  nop
0x66f1f18  mov qword ptr [rbp+0x1130],0x4001
0x66f1f23  mov eax,[r15+0x758]
0x66f1f2a  sub eax,[r15+0x750]
0x66f1f31  shr eax,3
0x66f1f34  imul eax,0xFFFF8BA3
0x66f1f3a  dec eax
0x66f1f3c  mov [rbp+0x115C],ax
0x66f1f43  mov rcx,[0x1233E1B0]
0x66f1f4a  mov rax,[rcx]
0x66f1f4d  mov rax,[rax+0x10]
```
Meaning: Second record completed identically (floats at +0x18..0x24, three movups chunks at +0x28/0x38/0x47, +0x58 cursor advance) [V], `jmp 0x66F1F97` [V]. Buffer-full path at 0x66F1EE8: call 0x6760A80 with rcx=[r15+0x750], r8=[rbp+0x1580] [V]; telemetry [V]; store qword [rbp+0x1130]=0x4001 [V]; compute ([r15+0x758]-[r15+0x750])>>3, imul by magic 0xFFFF8BA3, dec, store word [rbp+0x115C] — compiler constant-magic division [I]; telemetry again [V].

### lines 2211..2250
```asm
0x66f1f51  mov dl,0x4A
0x66f1f53  call qword ptr [0xF99FFA0]
0x66f1f59  nop
0x66f1f5a  mov [rbp+0x16D4],al
0x66f1f60  mov rdx,[r15+0x890]
0x66f1f67  cmp rdx,[r15+0x898]
0x66f1f6e  je 0x66F201E
0x66f1f74  inc rdx
0x66f1f77  mov [r15+0x890],rdx
0x66f1f7e  jmp 0x66F202B
0x66f1f83  lea rcx,[r15+0x750]
0x66f1f8a  lea r8,[rbp+0x1580]
0x66f1f91  call 0x6760A80
0x66f1f96  nop
0x66f1f97  mov rcx,[0x1233E1B0]
0x66f1f9e  mov rax,[rcx]
0x66f1fa1  mov rax,[rax+0x10]
0x66f1fa5  movzx edx,byte ptr [rbp+0x16D4]
0x66f1fac  call qword ptr [0xF99FFA0]
0x66f1fb2  nop
0x66f1fb3  mov qword ptr [rbp+0x1130],0x4001
0x66f1fbe  mov eax,[r15+0x758]
0x66f1fc5  sub eax,[r15+0x750]
0x66f1fcc  shr eax,3
0x66f1fcf  imul eax,0xFFFF8BA3
0x66f1fd5  dec eax
0x66f1fd7  mov [rbp+0x115C],ax
0x66f1fde  mov rcx,[0x1233E1B0]
0x66f1fe5  mov rax,[rcx]
0x66f1fe8  mov rax,[rax+0x10]
0x66f1fec  mov dl,0x4A
0x66f1fee  call qword ptr [0xF99FFA0]
0x66f1ff4  nop
0x66f1ff5  mov [rbp+0x16D4],al
0x66f1ffb  mov rdx,[r15+0x890]
0x66f2002  cmp rdx,[r15+0x898]
0x66f2009  je 0x66F209E
0x66f200f  inc rdx
0x66f2012  mov [r15+0x890],rdx
0x66f2019  jmp 0x66F20AB
```
Meaning: Telemetry finishes with dl=0x4A and [rbp+0x16D4]=al [V]. Counter [r15+0x890] vs limit [r15+0x898]: if equal jump to 0x66F201E, else increment and store [V]. The 0x66F1F83 path repeats call 0x6760A80 [V], telemetry [V], [rbp+0x1130]=0x4001 [V], magic-division count ([r15+0x758]-[r15+0x750])>>3 → [rbp+0x115C] [V], telemetry [V]; then counter [r15+0x890] vs [r15+0x898]: equal → 0x66F209E, else inc/store and `jmp 0x66F20AB` [V].

### lines 2251..2290
```asm
0x66f201e  lea rcx,[r15+0x888]
0x66f2025  call 0x6760E60
0x66f202a  nop
0x66f202b  mov rcx,[0x1233E1B0]
0x66f2032  mov rax,[rcx]
0x66f2035  mov rax,[rax+0x10]
0x66f2039  movzx edx,byte ptr [rbp+0x16D4]
0x66f2040  call qword ptr [0xF99FFA0]
0x66f2046  nop
0x66f2047  mov eax,[r15+0x888]
0x66f204e  not eax
0x66f2050  add eax,[r15+0x890]
0x66f2057  mov [rbp+0x1142],ax
0x66f205e  mov rcx,[0x1233E1B0]
0x66f2065  mov rax,[rcx]
0x66f2068  mov rax,[rax+0x10]
0x66f206c  mov dl,0x4A
0x66f206e  call qword ptr [0xF99FFA0]
0x66f2074  nop
0x66f2075  mov [rbp+0x16D4],al
0x66f207b  mov rdx,[r15+0x7A0]
0x66f2082  cmp rdx,[r15+0x7A8]
0x66f2089  je 0x66F211E
0x66f208f  inc rdx
0x66f2092  mov [r15+0x7A0],rdx
0x66f2099  jmp 0x66F212B
0x66f209e  lea rcx,[r15+0x888]
0x66f20a5  call 0x6760E60
0x66f20aa  nop
0x66f20ab  mov rcx,[0x1233E1B0]
0x66f20b2  mov rax,[rcx]
0x66f20b5  mov rax,[rax+0x10]
0x66f20b9  movzx edx,byte ptr [rbp+0x16D4]
0x66f20c0  call qword ptr [0xF99FFA0]
0x66f20c6  nop
0x66f20c7  mov eax,[r15+0x888]
0x66f20ce  not eax
0x66f20d0  add eax,[r15+0x890]
0x66f20d7  mov [rbp+0x1142],ax
0x66f20de  mov rcx,[0x1233E1B0]
```
Meaning: Full-path helper call 0x6760E60(rcx=[r15+0x888]) [V], telemetry [V], then `[rbp+0x1142] = [r15+0x890] - [r15+0x888]` computed via `not eax; add eax,[r15+0x890]` [V], telemetry with dl=0x4A [V]. Counter [r15+0x7A0] vs [r15+0x7A8]: equal → 0x66F211E, else inc/store and `jmp 0x66F212B` [V]. Alternate at 0x66F209E repeats the same 0x6760E60 call and the not/add count → [rbp+0x1142] [V]. All values seen in disassembly [V]; meaning of the counters (remaining/used slots) inferred [I].

### lines 2291..2330
```asm
0x66f20e5  mov rax,[rcx]
0x66f20e8  mov rax,[rax+0x10]
0x66f20ec  mov dl,0x4A
0x66f20ee  call qword ptr [0xF99FFA0]
0x66f20f4  nop
0x66f20f5  mov [rbp+0x16D4],al
0x66f20fb  mov rdx,[r15+0x7A0]
0x66f2102  cmp rdx,[r15+0x7A8]
0x66f2109  je 0x66F227E
0x66f210f  inc rdx
0x66f2112  mov [r15+0x7A0],rdx
0x66f2119  jmp 0x66F228B
0x66f211e  lea rcx,[r15+0x798]
0x66f2125  call 0x6760E60
0x66f212a  nop
0x66f212b  mov rcx,[0x1233E1B0]
0x66f2132  mov rax,[rcx]
0x66f2135  mov rax,[rax+0x10]
0x66f2139  movzx edx,byte ptr [rbp+0x16D4]
0x66f2140  call qword ptr [0xF99FFA0]
0x66f2146  nop
0x66f2147  mov eax,[r15+0x798]
0x66f214e  not eax
0x66f2150  add eax,[r15+0x7A0]
0x66f2157  mov [rbp+0x1156],ax
0x66f215e  mov rcx,[0x1233E1B0]
0x66f2165  mov rax,[rcx]
0x66f2168  mov rax,[rax+0x10]
0x66f216c  mov dl,0x4A
0x66f216e  call qword ptr [0xF99FFA0]
0x66f2174  mov [rbp+0x16D4],al
0x66f217a  lea rcx,[r15+0x648]
0x66f2181  lea rdx,[rbp+0x1528]
0x66f2188  call 0x675FB30
0x66f218d  nop
0x66f218e  mov rcx,[0x1233E1B0]
0x66f2195  mov rax,[rcx]
0x66f2198  mov rax,[rax+0x10]
0x66f219c  movzx edx,byte ptr [rbp+0x16D4]
0x66f21a3  call qword ptr [0xF99FFA0]
```
Meaning: Finish alternate path's telemetry and counter-inc/jmp [V]. At 0x66F211E: call 0x6760E60(rcx=[r15+0x798]) [V], telemetry [V], count `[rbp+0x1156] = [r15+0x7A0] - [r15+0x798]` via not/add [V], telemetry with dl=0x4A [V]. Then helper 0x675FB30(rcx=[r15+0x648], rdx=[rbp+0x1528]) [V], followed by telemetry setup [V]. All instruction-level facts from listing [V]; semantic roles of counters/helpers inferred [I].

### lines 2331..2370
```asm
0x66f21a9  nop
0x66f21aa  mov eax,[r15+0x650]
0x66f21b1  sub eax,[r15+0x648]
0x66f21b8  shr eax,3
0x66f21bb  imul eax,0xFFFF8E39
0x66f21c1  dec eax
0x66f21c3  mov [rbp+0x1172],ax
0x66f21ca  lea rcx,[r15+0x780]
0x66f21d1  lea rdx,[rbp+0x14D0]
0x66f21d8  call 0x675F3B0
0x66f21dd  nop
0x66f21de  mov qword ptr [rbp+0x1130],0x2005803
0x66f21e9  mov eax,[r15+0x788]
0x66f21f0  sub eax,[r15+0x780]
0x66f21f7  shr eax,3
0x66f21fa  imul eax,0xFFFF8BA3
0x66f2200  dec eax
0x66f2202  mov [rbp+0x1158],ax
0x66f2209  mov rcx,[0x1233E1B0]
0x66f2210  mov rax,[rcx]
0x66f2213  mov rax,[rax+0x10]
0x66f2217  mov dl,0x4A
0x66f2219  call qword ptr [0xF99FFA0]
0x66f221f  nop
0x66f2220  mov [rbp+0x16D4],al
0x66f2226  mov rbx,[r15+0x770]
0x66f222d  cmp rbx,[r15+0x778]
0x66f2234  je 0x66F23DE
0x66f223a  mov rax,[rbp+0x1448]
0x66f2241  mov [rbx],rax
0x66f2244  lea rcx,[rbx+8]
0x66f2248  lea rdx,[rbp+0x1450]
0x66f224f  call 0xE869FF0
0x66f2254  nop
0x66f2255  mov rax,[rbp+0x14C8]
0x66f225c  mov [rbx+0x80],rax
0x66f2263  mov qword ptr [rbp+0x14C8],0
0x66f226e  add qword ptr [r15+0x770],0x88
0x66f2279  jmp 0x66F23F5
0x66f227e  lea rcx,[r15+0x798]
```
Meaning: Count `([r15+0x650]-[r15+0x648])>>3` via magic 0xFFFF8E39 → [rbp+0x1172] [V]; call 0x675F3B0(rcx=[r15+0x780], rdx=[rbp+0x14D0]) [V]; [rbp+0x1130]=0x2005803 [V]; count `([r15+0x788]-[r15+0x780])>>3` via magic 0xFFFF8BA3 → [rbp+0x1158] [V]; telemetry with dl=0x4A [V]. Entry [rbx]=[r15+0x770] vs limit [r15+0x778]: equal → 0x66F23DE; else write [rbp+0x1448] to [rbx], copy 16 bytes [rbp+0x1450]→[rbx+8] via call 0xE869FF0 [V], [rbx+0x80]=[rbp+0x14C8], clear [rbp+0x14C8], advance cursor [r15+0x770] by 0x88 [V], `jmp 0x66F23F5` [V].

### lines 2371..2410
```asm
0x66f2285  call 0x6760E60
0x66f228a  nop
0x66f228b  mov rcx,[0x1233E1B0]
0x66f2292  mov rax,[rcx]
0x66f2295  mov rax,[rax+0x10]
0x66f2299  movzx edx,byte ptr [rbp+0x16D4]
0x66f22a0  call qword ptr [0xF99FFA0]
0x66f22a6  nop
0x66f22a7  mov eax,[r15+0x798]
0x66f22ae  not eax
0x66f22b0  add eax,[r15+0x7A0]
0x66f22b7  mov [rbp+0x1156],ax
0x66f22be  mov rcx,[0x1233E1B0]
0x66f22c5  mov rax,[rcx]
0x66f22c8  mov rax,[rax+0x10]
0x66f22cc  mov dl,0x4A
0x66f22ce  call qword ptr [0xF99FFA0]
0x66f22d4  mov [rbp+0x16D4],al
0x66f22da  lea rcx,[r15+0x648]
0x66f22e1  lea rdx,[rbp+0x1528]
0x66f22e8  call 0x675FB30
0x66f22ed  nop
0x66f22ee  mov rcx,[0x1233E1B0]
0x66f22f5  mov rax,[rcx]
0x66f22f8  mov rax,[rax+0x10]
0x66f22fc  movzx edx,byte ptr [rbp+0x16D4]
0x66f2303  call qword ptr [0xF99FFA0]
0x66f2309  nop
0x66f230a  mov eax,[r15+0x650]
0x66f2311  sub eax,[r15+0x648]
0x66f2318  shr eax,3
0x66f231b  imul eax,0xFFFF8E39
0x66f2321  dec eax
0x66f2323  mov [rbp+0x1172],ax
0x66f232a  lea rcx,[r15+0x780]
0x66f2331  lea rdx,[rbp+0x14D0]
0x66f2338  call 0x675F3B0
0x66f233d  nop
0x66f233e  mov qword ptr [rbp+0x1130],0x2005803
0x66f2349  mov eax,[r15+0x788]
```
Meaning: Finish full-path tail: 0x6760E60 call [V], telemetry [V], count `[rbp+0x1156]=[r15+0x7A0]-[r15+0x798]` via not/add [V], telemetry with dl=0x4A [V], helper 0x675FB30 [V], telemetry setup [V], count `([r15+0x650]-[r15+0x648])>>3` magic 0xFFFF8E39 → [rbp+0x1172] [V], call 0x675F3B0 [V], [rbp+0x1130]=0x2005803 [V], count `([r15+0x788]-[r15+0x780])>>3` begins [V]. All counts are shr-by-3 followed by an imul magic constant (compiler division by a non-power-of-two constant) [I].

### lines 2411..2450
```asm
0x66f2350  sub eax,[r15+0x780]
0x66f2357  shr eax,3
0x66f235a  imul eax,0xFFFF8BA3
0x66f2360  dec eax
0x66f2362  mov [rbp+0x1158],ax
0x66f2369  mov rcx,[0x1233E1B0]
0x66f2370  mov rax,[rcx]
0x66f2373  mov rax,[rax+0x10]
0x66f2377  mov dl,0x4A
0x66f2379  call qword ptr [0xF99FFA0]
0x66f237f  nop
0x66f2380  mov [rbp+0x16D4],al
0x66f2386  mov rbx,[r15+0x770]
0x66f238d  cmp rbx,[r15+0x778]
0x66f2394  je 0x66F2471
0x66f239a  mov rax,[rbp+0x1448]
0x66f23a1  mov [rbx],rax
0x66f23a4  lea rcx,[rbx+8]
0x66f23a8  lea rdx,[rbp+0x1450]
0x66f23af  call 0xE869FF0
0x66f23b4  nop
0x66f23b5  mov rax,[rbp+0x14C8]
0x66f23bc  mov [rbx+0x80],rax
0x66f23c3  mov qword ptr [rbp+0x14C8],0
0x66f23ce  add qword ptr [r15+0x770],0x88
0x66f23d9  jmp 0x66F2488
0x66f23de  lea rcx,[r15+0x768]
0x66f23e5  mov rdx,rbx
0x66f23e8  lea r8,[rbp+0x1448]
0x66f23ef  call 0x6760710
0x66f23f4  nop
0x66f23f5  mov rcx,[0x1233E1B0]
0x66f23fc  mov rax,[rcx]
0x66f23ff  mov rax,[rax+0x10]
0x66f2403  movzx edx,byte ptr [rbp+0x16D4]
0x66f240a  call qword ptr [0xF99FFA0]
0x66f2410  nop
0x66f2411  mov eax,[r15+0x770]
0x66f2418  sub eax,[r15+0x768]
0x66f241f  shr eax,3
```
Meaning: Finish count → [rbp+0x1158] [V], telemetry dl=0x4A [V]. Entry path repeats: [rbx]=[r15+0x770] vs [r15+0x778], equal → 0x66F2471; else store [rbp+0x1448] at [rbx], copy via 0xE869FF0 [V], [rbx+0x80]=[rbp+0x14C8], clear [rbp+0x14C8], cursor [r15+0x770] += 0x88, `jmp 0x66F2488` [V]. Full path at 0x66F23DE: call 0x6760710(rcx=[r15+0x768], rdx=rbx, r8=[rbp+0x1448]) [V], telemetry [V], then eax=[r15+0x770]-[r15+0x768], shr 3 [V].

### lines 2451..2490
```asm
0x66f2422  imul eax,0xFFFFF0F1
0x66f2428  dec eax
0x66f242a  mov [rbp+0x115A],ax
0x66f2431  mov rcx,[0x1233E1B0]
0x66f2438  mov rax,[rcx]
0x66f243b  mov rax,[rax+0x10]
0x66f243f  mov dl,0x4A
0x66f2441  call qword ptr [0xF99FFA0]
0x66f2447  nop
0x66f2448  mov [rbp+0x16D4],al
0x66f244e  mov rdx,[r15+0x2D8]
0x66f2455  cmp rdx,[r15+0x2E0]
0x66f245c  je 0x66F2504
0x66f2462  inc rdx
0x66f2465  mov [r15+0x2D8],rdx
0x66f246c  jmp 0x66F2514
0x66f2471  lea rcx,[r15+0x768]
0x66f2478  mov rdx,rbx
0x66f247b  lea r8,[rbp+0x1448]
0x66f2482  call 0x6760710
0x66f2487  nop
0x66f2488  mov rcx,[0x1233E1B0]
0x66f248f  mov rax,[rcx]
0x66f2492  mov rax,[rax+0x10]
0x66f2496  movzx edx,byte ptr [rbp+0x16D4]
0x66f249d  call qword ptr [0xF99FFA0]
0x66f24a3  nop
0x66f24a4  mov eax,[r15+0x770]
0x66f24ab  sub eax,[r15+0x768]
0x66f24b2  shr eax,3
0x66f24b5  imul eax,0xFFFFF0F1
0x66f24bb  dec eax
0x66f24bd  mov [rbp+0x115A],ax
0x66f24c4  mov rcx,[0x1233E1B0]
0x66f24cb  mov rax,[rcx]
0x66f24ce  mov rax,[rax+0x10]
0x66f24d2  mov dl,0x4A
0x66f24d4  call qword ptr [0xF99FFA0]
0x66f24da  nop
0x66f24db  mov [rbp+0x16D4],al
```
Meaning: Count `([r15+0x770]-[r15+0x768])>>3` via magic 0xFFFFF0F1 → [rbp+0x115A] [V], telemetry dl=0x4A [V]. Counter [r15+0x2D8] vs [r15+0x2E0]: equal → 0x66F2504; else inc/store, `jmp 0x66F2514` [V]. Full path at 0x66F2471 repeats 0x6760710 [V], telemetry [V], same count → [rbp+0x115A] [V], telemetry dl=0x4A [V].

### lines 2491..2530
```asm
0x66f24e1  mov rdx,[r15+0x608]
0x66f24e8  cmp rdx,[r15+0x610]
0x66f24ef  je 0x66F25A1
0x66f24f5  inc rdx
0x66f24f8  mov [r15+0x608],rdx
0x66f24ff  jmp 0x66F25B1
0x66f2504  mov rcx,r15
0x66f2507  add rcx,0x2D0
0x66f250e  call 0x6760E60
0x66f2513  nop
0x66f2514  mov rcx,[0x1233E1B0]
0x66f251b  mov rax,[rcx]
0x66f251e  mov rax,[rax+0x10]
0x66f2522  movzx edx,byte ptr [rbp+0x16D4]
0x66f2529  call qword ptr [0xF99FFA0]
0x66f252f  nop
0x66f2530  mov rax,0x4000000002007803
0x66f253a  mov [rbp+0x1130],rax
0x66f2541  mov eax,[r15+0x2D0]
0x66f2548  not eax
0x66f254a  add eax,[r15+0x2D8]
0x66f2551  mov [rbp+0x11BC],ax
0x66f2558  mov rcx,[0x1233E1B0]
0x66f255f  mov rax,[rcx]
0x66f2562  mov rax,[rax+0x10]
0x66f2566  mov dl,0x4A
0x66f2568  call qword ptr [0xF99FFA0]
0x66f256e  nop
0x66f256f  mov [rbp+0x16D4],al
0x66f2575  mov rdx,[r15+8]
0x66f2579  cmp rdx,[r15+0x10]
0x66f257d  je 0x66F2631
0x66f2583  mov r8d,0xC8
0x66f2589  mov rcx,rdx
0x66f258c  mov rdx,r12
0x66f258f  call 0xEEC6EC0
0x66f2594  add qword ptr [r15+8],0xC8
0x66f259c  jmp 0x66F263D
0x66f25a1  mov rcx,r15
0x66f25a4  add rcx,0x600
```
Meaning: Counter [r15+0x608] vs [r15+0x610]: equal → 0x66F25A1; else inc/store, `jmp 0x66F25B1` [V]. Full path at 0x66F2504: call 0x6760E60(rcx=r15+0x2D0) [V], telemetry [V], [rbp+0x1130]=0x4000000002007803 [V] (large 64-bit tag), `[rbp+0x11BC]=[r15+0x2D8]-[r15+0x2D0]` via not/add [V], telemetry dl=0x4A [V]. Then [r15+8] vs [r15+0x10]: equal → 0x66F2631; else r8d=0xC8 (200 bytes), rcx=rdx, rdx=r12, call 0xEEC6EC0 — looks like a 0xC8-byte fill/copy [I]; advance [r15+8] by 0xC8 [V], `jmp 0x66F263D` [V]. Alternate at 0x66F25A1: rcx=r15+0x600, call 0x6760E60 [V].

### lines 2531..2570
```asm
0x66f25ab  call 0x6760E60
0x66f25b0  nop
0x66f25b1  mov rcx,[0x1233E1B0]
0x66f25b8  mov rax,[rcx]
0x66f25bb  mov rax,[rax+0x10]
0x66f25bf  movzx edx,byte ptr [rbp+0x16D4]
0x66f25c6  call qword ptr [0xF99FFA0]
0x66f25cc  nop
0x66f25cd  mov qword ptr [rbp+0x1130],0x12007803
0x66f25d8  mov eax,[r15+0x600]
0x66f25df  not eax
0x66f25e1  add eax,[r15+0x608]
0x66f25e8  mov [rbp+0x1178],ax
0x66f25ef  mov rcx,[0x1233E1B0]
0x66f25f6  mov rax,[rcx]
0x66f25f9  mov rax,[rax+0x10]
0x66f25fd  mov dl,0x4A
0x66f25ff  call qword ptr [0xF99FFA0]
0x66f2605  nop
0x66f2606  mov [rbp+0x16D4],al
0x66f260c  mov rdx,[r15+8]
0x66f2610  cmp rdx,[r15+0x10]
0x66f2614  je short 0x66F267B
0x66f2616  mov r8d,0xC8
0x66f261c  mov rcx,rdx
0x66f261f  mov rdx,r12
0x66f2622  call 0xEEC6EC0
0x66f2627  add qword ptr [r15+8],0xC8
0x66f262f  jmp short 0x66F2687
0x66f2631  mov rcx,r15
0x66f2634  mov r8,r12
0x66f2637  call 0x5ABA6D0
0x66f263c  nop
0x66f263d  mov rcx,[0x1233E1B0]
0x66f2644  mov rax,[rcx]
0x66f2647  mov rax,[rax+0x10]
0x66f264b  movzx edx,byte ptr [rbp+0x16D4]
0x66f2652  call qword ptr [0xF99FFA0]
0x66f2658  nop
0x66f2659  lea rcx,[rbp+0x1440]
```
Meaning: Finish alternate path: 0x6760E60 [V], telemetry [V], [rbp+0x1130]=0x12007803 [V], `[rbp+0x1178]=[r15+0x608]-[r15+0x600]` via not/add [V], telemetry dl=0x4A [V]. Counter [r15+8] vs [r15+0x10]: equal → short 0x66F267B; else r8d=0xC8, call 0xEEC6EC0(rcx, rdx=r12) [V], advance [r15+8]+=0xC8 [V], `jmp short 0x66F2687` [V]. If full at 0x66F2631: call 0x5ABA6D0(rcx=r15, r8=r12) [V]. Then telemetry [V] and lea rcx,[rbp+0x1440] [V].

### lines 2571..2610
```asm
0x66f2660  call 0x67E1840
0x66f2665  lea rcx,[rbp+0xF70]
0x66f266c  call 0x67E23F0
0x66f2671  test sil,sil
0x66f2674  jne short 0x66F26C0
0x66f2676  jmp 0x66F2700
0x66f267b  mov rcx,r15
0x66f267e  mov r8,r12
0x66f2681  call 0x5ABA6D0
0x66f2686  nop
0x66f2687  mov rcx,[0x1233E1B0]
0x66f268e  mov rax,[rcx]
0x66f2691  mov rax,[rax+0x10]
0x66f2695  movzx edx,byte ptr [rbp+0x16D4]
0x66f269c  call qword ptr [0xF99FFA0]
0x66f26a2  nop
0x66f26a3  lea rcx,[rbp+0x1440]
0x66f26aa  call 0x67E1840
0x66f26af  lea rcx,[rbp+0xF70]
0x66f26b6  call 0x67E23F0
0x66f26bb  nop [rax+rax]
0x66f26c0  mov rbx,[rbp+0x1428]
0x66f26c7  test rbx,rbx
0x66f26ca  je short 0x66F2700
0x66f26cc  lock dec dword ptr [rbx+8]
0x66f26d0  jne short 0x66F2700
0x66f26d2  mov rax,[rbx]
0x66f26d5  mov rax,[rax]
0x66f26d8  mov rcx,rbx
0x66f26db  call qword ptr [0xF99FFA0]
0x66f26e1  lock dec dword ptr [rbx+0xC]
0x66f26e5  jne short 0x66F2700
0x66f26e7  mov rax,[rbx]
0x66f26ea  mov rax,[rax+8]
0x66f26ee  mov rcx,rbx
0x66f26f1  call qword ptr [0xF99FFA0]
0x66f26f7  nop [rax+rax]
0x66f2700  cmp byte ptr [rbp+0xDF0],3
0x66f2707  jne short 0x66F2740
0x66f2709  mov rbx,[rbp+0xDE8]
```
Meaning: Calls 0x67E1840(rcx=[rbp+0x1440]) then 0x67E23F0(rcx=[rbp+0xF70]) [V]; if sil != 0 jump to 0x66F26C0 (release path), else `jmp 0x66F2700` [V]. Release path: refcount-release of object [rbp+0x1428] via [0xF99FFA0] dtor calls at [rax] and [rax+8] [V] (same pattern as phase 1). Then `cmp byte [rbp+0xDF0],3`; if not equal, `jmp short 0x66F2740`; else load rbx=[rbp+0xDE8] [V]. Telemetry calls surround each phase [V].

### lines 2611..2650
```asm
0x66f2710  test rbx,rbx
0x66f2713  je short 0x66F2740
0x66f2715  lock dec dword ptr [rbx+8]
0x66f2719  jne short 0x66F2740
0x66f271b  mov rax,[rbx]
0x66f271e  mov rax,[rax]
0x66f2721  mov rcx,rbx
0x66f2724  call qword ptr [0xF99FFA0]
0x66f272a  lock dec dword ptr [rbx+0xC]
0x66f272e  jne short 0x66F2740
0x66f2730  mov rax,[rbx]
0x66f2733  mov rax,[rax+8]
0x66f2737  mov rcx,rbx
0x66f273a  call qword ptr [0xF99FFA0]
0x66f2740  mov rsi,[rbp+0xDC0]
0x66f2747  test rsi,rsi
0x66f274a  je 0x66EF7F0
0x66f2750  mov rdi,[rbp+0xDC8]
0x66f2757  jmp short 0x66F2764
0x66f2759  nop [rax]
0x66f2760  add rsi,0x28
0x66f2764  cmp rsi,rdi
0x66f2767  je 0x66EF7F0
0x66f276d  cmp byte ptr [rsi+0x18],2
0x66f2771  jne short 0x66F2760
0x66f2773  mov rbx,[rsi+8]
0x66f2777  test rbx,rbx
0x66f277a  je short 0x66F2760
0x66f277c  lock dec dword ptr [rbx+8]
0x66f2780  jne short 0x66F2760
0x66f2782  mov rax,[rbx]
0x66f2785  mov rax,[rax]
0x66f2788  mov rcx,rbx
0x66f278b  call qword ptr [0xF99FFA0]
0x66f2791  lock dec dword ptr [rbx+0xC]
0x66f2795  jne short 0x66F2760
0x66f2797  mov rax,[rbx]
0x66f279a  mov rax,[rax+8]
0x66f279e  mov rcx,rbx
0x66f27a1  call qword ptr [0xF99FFA0]
```
Meaning: Finish refcount-release of [rbp+0xDE8] object [V]. Then a scan loop over array [rbp+0xDC0]..[rbp+0xDC8], step 0x28 [V]: skip entries where byte [rsi+0x18] != 2 [V]; for matching entries, refcount-release object [rsi+8] via [0xF99FFA0] dtor calls [V]; loop until rsi==rdi then jump 0x66EF7F0 [V] (exit of this body region). Empty-array check je 0x66EF7F0 [V]. Loop body continues into next phase.

### lines 2651..2680 (end)
```asm
0x66f27a7  jmp short 0x66F2760
0x66f27a9  mov rsi,[rbp+0x1670]
0x66f27b0  test rsi,rsi
0x66f27b3  je 0x66F6E3B
0x66f27b9  mov rbx,[rbp+0x1678]
0x66f27c0  cmp rsi,rbx
0x66f27c3  jne short 0x66F27DD
0x66f27c5  jmp 0x66F6E04
0x66f27ca  nop [rax+rax]
0x66f27d0  add rsi,0x18
0x66f27d4  cmp rsi,rbx
0x66f27d7  je 0x66F6DFD
0x66f27dd  cmp byte ptr [rsi+0x10],1
0x66f27e1  jne short 0x66F27D0
0x66f27e3  mov rdi,[rsi+8]
0x66f27e7  test rdi,rdi
0x66f27ea  je short 0x66F27D0
0x66f27ec  lock dec dword ptr [rdi+8]
0x66f27f0  jne short 0x66F27D0
0x66f27f2  mov rax,[rdi]
0x66f27f5  mov rax,[rax]
0x66f27f8  mov rcx,rdi
0x66f27fb  call qword ptr [0xF99FFA0]
0x66f2801  lock dec dword ptr [rdi+0xC]
0x66f2805  jne short 0x66F27D0
0x66f2807  mov rax,[rdi]
0x66f280a  mov rax,[rax+8]
0x66f280e  mov rcx,rdi
0x66f2811  call qword ptr [0xF99FFA0]
0x66f2817  jmp short 0x66F27D0
```
Meaning: Loop-continue `jmp short 0x66F2760` back into the 0x28-step scan loop [V]. Then a second scan loop over array [rbp+0x1670]..[rbp+0x1678], step 0x18 [V]: skip entries where byte [rsi+0x10] != 1 [V]; release refcounted object [rsi+8] via the same [0xF99FFA0] two-call dtor sequence [V]; empty array jumps 0x66F6E3B, exhausted loop jumps 0x66F6E04/0x66F6DFD [V] (targets outside this range). Body B ends here: the last listed instruction is line 2680 at RVA 0x66f2817 (`jmp short 0x66F27D0`), still inside the loop — the listing file ends without a function epilogue or ret, so body B continues beyond line 2680 [V]; no exit taken within this range [I].

## NEXT
Next line to do: none — all phases 1-16 complete; body B listing ends at line 2680 (RVA 0x66f2817, `jmp short 0x66F27D0`).