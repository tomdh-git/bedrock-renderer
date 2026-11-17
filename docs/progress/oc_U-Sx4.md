## NEXT
DONE

## UNIT U-Sx4 — instruction slice 0x66aac49..0x66ab0d7

Slice: chunk 4 of 6 of effect_shadow_extractor_66a9d50_66ab74e (shadow extractor 0x66a9d50), Minecraft.Windows.exe 1.26.62.01. Source listing: docs/progress/_part_Sx4.txt (250 instructions, 0x66aac49..0x66ab0d7). Every verbatim line below is copied from that listing; every address, size and offset was cross-checked against rdis disassembly of the exe [V]. No instruction or string in this slice documents the meaning of any field, so the meaning column is '-' throughout.

Entry register map ([V] from slice instructions): rcx = interface pointer ([rcx] read at 0x66aac49); rbx = object/buffer base (fields [rbx+0x228], [rbx+0x230], [rbx+0x238]...); rdi = insertion cursor; r14 = saved rdi (0x66aac5b); rbp = frame pointer (locals [rbp+0xD0..0x437]); r15 = capacity/size scratch; r12 = allocator result; r13 = end-past-cursor scratch. Arguments/returns not materialized in the slice are not recorded.

Instruction coverage: phases P1-P13 below cover instructions 1-250 of the slice contiguously; no instruction is skipped.

### Phase P1 — 0x66aac49..0x66aac80 (15 instructions)
Interface call and cursor fast path: reads vtable pointer [rcx], calls interface method [rax+0x10] through IAT slot 0xF99FFA0 with dl=0x4A (result -> esi) [V 0x66aac49-0x66aac59]; if cursor [rbx+0x230] != end [rbx+0x238], increments [rbx+0x230], restores rdi=r14 and jumps to 0x66AB379 [V]; when full, falls through to store sil at [rbp+0x437] and proceed to grow [V].

0x66aac49  mov rax,[rcx]
0x66aac4c  mov rax,[rax+0x10]
0x66aac50  mov dl,0x4A
0x66aac52  call qword ptr [0xF99FFA0]
0x66aac58  nop
0x66aac59  mov esi,eax
0x66aac5b  mov r14,rdi
0x66aac5e  mov rdi,[rbx+0x230]
0x66aac65  cmp rdi,[rbx+0x238]
0x66aac6c  je short 0x66AAC80
0x66aac6e  inc rdi
0x66aac71  mov [rbx+0x230],rdi
0x66aac78  mov rdi,r14
0x66aac7b  jmp 0x66AB379
0x66aac80  mov [rbp+0x437],sil

### Phase P2 — 0x66aac87..0x66aad21 (38 instructions)
Grow path: need = rdi - [rbx+0x228] [V]; if need == 0x7FFFFFFFFFFFFFFF -> 0x66AB73A [V]; need+1 saved at [rbp+0x428]; candidate = need + (need>>1), clamped up to need+1 via cmovbe when it does not grow [V]; keeps the cap when need > ~(need>>1), otherwise r15 = candidate [V]; rejects r15 == 0 -> 0x66AB2D6, routes r15 < 0x1000 to exact-size allocation at 0x66AAD2F, rejects r15 >= 0xFFFFFFFFFFFFFFD9 -> 0x66AB746 [V]; r13 = r15 + 0x27; allocator call via global 0x1233E1A8 -> [rax+8], rdx = r13 [V].

0x66aac87  mov rsi,rdi
0x66aac8a  sub rsi,[rbx+0x228]
0x66aac91  mov r15,0x7FFFFFFFFFFFFFFF
0x66aac9b  cmp rsi,r15
0x66aac9e  je 0x66AB73A
0x66aaca4  lea rdx,[rsi+1]
0x66aaca8  mov rax,rsi
0x66aacab  shr rax,1
0x66aacae  mov rcx,rax
0x66aacb1  xor rcx,r15
0x66aacb4  add rax,rsi
0x66aacb7  cmp rax,rdx
0x66aacba  mov [rbp+0x428],rdx
0x66aacc1  cmovbe rax,rdx
0x66aacc5  cmp rsi,rcx
0x66aacc8  ja short 0x66AACCD
0x66aacca  mov r15,rax
0x66aaccd  test r15,r15
0x66aacd0  je 0x66AB2D6
0x66aacd6  cmp r15,0x1000
0x66aacdd  jb short 0x66AAD2F
0x66aacdf  cmp r15,0xFFFFFFFFFFFFFFD9
0x66aace3  jae 0x66AB746
0x66aace9  lea r13,[r15+0x27]
0x66aaced  mov rcx,[0x1233E1A8]
0x66aacf4  mov rax,[rcx]
0x66aacf7  mov rax,[rax+8]
0x66aacfb  mov rdx,r13
0x66aacfe  call qword ptr [0xF99FFA0]
0x66aad04  nop
0x66aad05  mov r12,rax
0x66aad08  test rax,rax
0x66aad0b  je 0x66AB653
0x66aad11  mov rax,r12
0x66aad14  add r12,0x27
0x66aad18  and r12,0xFFFFFFFFFFFFFFE0
0x66aad1c  mov [r12-8],rax
0x66aad21  cmp rdi,[rbx+0x230]

### Phase P3 — 0x66aad28..0x66aad40 (7 instructions)
Branch on cursor equality: if rdi != [rbx+0x230] -> 0x66AAD60 (copy path), else jmp 0x66AB2E6; small-allocation path entered from 0x66AAD2F: allocator call with rdx = r15, result r12; null -> 0x66AB2CD; rdi == [rbx+0x230] -> 0x66AB2E6 [V].

0x66aad28  jne short 0x66AAD60
0x66aad2a  jmp 0x66AB2E6
0x66aad2f  mov rcx,[0x1233E1A8]
0x66aad36  mov rax,[rcx]
0x66aad39  mov rax,[rax+8]
0x66aad3d  mov rdx,r15
0x66aad40  call qword ptr [0xF99FFA0]

### Phase P4 — 0x66aad46..0x66aad8c (18 instructions)
Allocator result in r12; null -> 0x66AB2CD; stores old rax at [r12-8] (allocation header) [V]; r13 = r12 + rsi + 1 (end+1); calls 0xEEC6DE0 with rcx=r12, rdx=[rbx+0x228], r8 = rdi-[rbx+0x228] (element copy) [V]; tail setup for 0x66AB2F6: r8 = [rbx+0x230]-rdi, rcx = r13, rdx = rdi, jmp 0x66AB2F6 [V].

0x66aad46  nop
0x66aad47  mov r12,rax
0x66aad4a  test rax,rax
0x66aad4d  je 0x66AB2CD
0x66aad53  cmp rdi,[rbx+0x230]
0x66aad5a  je 0x66AB2E6
0x66aad60  lea r13,[r12+rsi]
0x66aad64  inc r13
0x66aad67  mov rdx,[rbx+0x228]
0x66aad6e  mov r8,rdi
0x66aad71  sub r8,rdx
0x66aad74  mov rcx,r12
0x66aad77  call 0xEEC6DE0
0x66aad7c  mov r8,[rbx+0x230]
0x66aad83  sub r8,rdi
0x66aad86  mov rcx,r13
0x66aad89  mov rdx,rdi
0x66aad8c  jmp 0x66AB2F6

### Phase P5 — 0x66aad91..0x66aadde (16 instructions)
Frame record init: [rbp+0x310] = [rbp+0x3C8], [rbp+0x318] = rcx (= 0 after xor), [rbp+0x320] = al (= 0); [r14+0x184] = qword [rcx+0x48] with rcx = rbp+0x3A8 [V]; movups [r14+0x174] = [rcx+0x38], a 16B store [V]; rcx = [r15+0x10] + 0x9D0; call 0x5ABA5C0 -> rbx (new buffer object) [V].

0x66aad91  xor ecx,ecx
0x66aad93  mov rdx,[rbp+0x3C8]
0x66aad9a  mov [rbp+0x310],rdx
0x66aada1  mov [rbp+0x318],rcx
0x66aada8  mov [rbp+0x320],al
0x66aadae  lea rcx,[rbp+0x3A8]
0x66aadb5  mov rax,[rcx+0x48]
0x66aadb9  mov [r14+0x184],rax
0x66aadc0  movups xmm0,[rcx+0x38]
0x66aadc4  movups [r14+0x174],xmm0
0x66aadcc  mov rcx,[r15+0x10]
0x66aadd0  mov eax,0x9D0
0x66aadd5  add rcx,rax
0x66aadd8  call 0x5ABA5C0
0x66aaddd  nop
0x66aadde  mov rbx,rax

### Phase P6 — 0x66aade1..0x66aae59 (24 instructions)
rax = rbp+0xD8; stores zeroed xmm6 to [rax+0x00..0xB0] in twelve 16B stores ([rax], [rax+0x10] ... [rax+0xB0]), zeroing 0xC0 bytes of frame [V]; rcx = rbx+0x780, rdx = rbp+0x2E8, call 0x675F3B0 [V]; [rbp+0xD0] = 0x1000 qword [V]; eax = ((([rbx+0x788]-[rbx+0x780])>>1) * 0xFFFF8BA3) - 1 -> [rbp+0xF8] = ax [V].

0x66aade1  lea rax,[rbp+0xD8]
0x66aade8  movups [rax+0xB0],xmm6
0x66aadef  movups [rax+0xA0],xmm6
0x66aadf6  movups [rax+0x90],xmm6
0x66aadfd  movups [rax+0x80],xmm6
0x66aae04  movups [rax+0x70],xmm6
0x66aae08  movups [rax+0x60],xmm6
0x66aae0c  movups [rax+0x50],xmm6
0x66aae10  movups [rax+0x40],xmm6
0x66aae14  movups [rax+0x30],xmm6
0x66aae18  movups [rax+0x20],xmm6
0x66aae1c  movups [rax+0x10],xmm6
0x66aae20  movups [rax],xmm6
0x66aae23  lea rcx,[rbx+0x780]
0x66aae2a  lea rdx,[rbp+0x2E8]
0x66aae31  call 0x675F3B0
0x66aae36  nop
0x66aae37  mov qword ptr [rbp+0xD0],0x1000
0x66aae42  mov eax,[rbx+0x788]
0x66aae48  sub eax,[rbx+0x780]
0x66aae4e  shr eax,3
0x66aae51  imul eax,0xFFFF8BA3
0x66aae57  dec eax
0x66aae59  mov [rbp+0xF8],ax

### Phase P7 — 0x66aae60..0x66aaeb4 (18 instructions)
Interface call via global 0x1233E1B0 -> [rax+0x10] with dl=0x4A -> [rbp+0x437] = al [V]; if [rbx+0x8A8] != [rbx+0x8B0]: eax = word [rbp+0x2E0], [rdx] = ax, [rbx+0x8A8] += 2 [V]; else call 0x1EF6F90(rcx = [rbx+0x8A0], r8 = [rbp+0x2E0]) (commit/flush) [V].

0x66aae60  mov rcx,[0x1233E1B0]
0x66aae67  mov rax,[rcx]
0x66aae6a  mov rax,[rax+0x10]
0x66aae6e  mov dl,0x4A
0x66aae70  call qword ptr [0xF99FFA0]
0x66aae76  nop
0x66aae77  mov [rbp+0x437],al
0x66aae7d  mov rdx,[rbx+0x8A8]
0x66aae84  cmp rdx,[rbx+0x8B0]
0x66aae8b  je short 0x66AAEA1
0x66aae8d  movzx eax,word ptr [rbp+0x2E0]
0x66aae94  mov [rdx],ax
0x66aae97  add qword ptr [rbx+0x8A8],2
0x66aae9f  jmp short 0x66AAEB5
0x66aaea1  lea rcx,[rbx+0x8A0]
0x66aaea8  lea r8,[rbp+0x2E0]
0x66aaeaf  call 0x1EF6F90
0x66aaeb4  nop

### Phase P8 — 0x66aaeb5..0x66aaf33 (27 instructions)
Interface call via [0x1233E1B0] -> [rax+0x10] -> [rbp+0x437] = al [V]; eax = (([rbx+0x8A8]-[rbx+0x8A0])>>1) - 1 -> [rbp+0xE0] = ax [V]; interface call via [0x1233E1B0] -> [rbp+0x437] = al [V]; call 0x675FB30(rcx = [rbx+0x648], rdx = [rbp+0x298]) [V].

0x66aaeb5  mov rcx,[0x1233E1B0]
0x66aaebc  mov rax,[rcx]
0x66aaebf  mov rax,[rax+0x10]
0x66aaec3  movzx edx,byte ptr [rbp+0x437]
0x66aaeca  call qword ptr [0xF99FFA0]
0x66aaed0  nop
0x66aaed1  mov eax,[rbx+0x8A8]
0x66aaed7  sub eax,[rbx+0x8A0]
0x66aaedd  shr eax,1
0x66aaedf  dec eax
0x66aaee1  mov [rbp+0xE0],ax
0x66aaee8  mov rcx,[0x1233E1B0]
0x66aaeef  mov rax,[rcx]
0x66aaef2  mov rax,[rax+0x10]
0x66aaef6  mov dl,0x4A
0x66aaef8  call qword ptr [0xF99FFA0]
0x66aaefe  mov [rbp+0x437],al
0x66aaf04  lea rcx,[rbx+0x648]
0x66aaf0b  lea rdx,[rbp+0x298]
0x66aaf12  call 0x675FB30
0x66aaf17  nop
0x66aaf18  mov rcx,[0x1233E1B0]
0x66aaf1f  mov rax,[rcx]
0x66aaf22  mov rax,[rax+0x10]
0x66aaf26  movzx edx,byte ptr [rbp+0x437]
0x66aaf2d  call qword ptr [0xF99FFA0]
0x66aaf33  nop

### Phase P9 — 0x66aaf34..0x66aafbd (26 instructions)
eax = (([rbx+0x650]-[rbx+0x648])>>3) * 0xFFFF8E39 - 1 -> [rbp+0x112] = ax [V]; interface call via [0x1233E1B0] -> [rbp+0x437] = al [V]; rsi = [rbx+0x770]; if rsi != [rbx+0x778]: [rsi] = [rbp+0x210] (qword), call 0xE869FF0(rcx = rsi+8, rdx = [rbp+0x218]), [rsi+0x80] = [rbp+0x290], [rbp+0x290] = 0, [rbx+0x770] += 0x88, jmp 0x66AAFD6 [V]; else (full) falls to 0x66aafbf commit path.

0x66aaf34  mov eax,[rbx+0x650]
0x66aaf3a  sub eax,[rbx+0x648]
0x66aaf40  shr eax,3
0x66aaf43  imul eax,0xFFFF8E39
0x66aaf49  dec eax
0x66aaf4b  mov [rbp+0x112],ax
0x66aaf52  mov rcx,[0x1233E1B0]
0x66aaf59  mov rax,[rcx]
0x66aaf5c  mov rax,[rax+0x10]
0x66aaf60  mov dl,0x4A
0x66aaf62  call qword ptr [0xF99FFA0]
0x66aaf68  mov [rbp+0x437],al
0x66aaf6e  mov rsi,[rbx+0x770]
0x66aaf75  cmp rsi,[rbx+0x778]
0x66aaf7c  je short 0x66AAFBF
0x66aaf7e  mov rax,[rbp+0x210]
0x66aaf85  mov [rsi],rax
0x66aaf88  lea rcx,[rsi+8]
0x66aaf8c  lea rdx,[rbp+0x218]
0x66aaf93  call 0xE869FF0
0x66aaf98  nop
0x66aaf99  mov rax,[rbp+0x290]
0x66aafa0  mov [rsi+0x80],rax
0x66aafa7  mov qword ptr [rbp+0x290],0
0x66aafb2  add qword ptr [rbx+0x770],0x88
0x66aafbd  jmp short 0x66AAFD6

### Phase P10 — 0x66aafbf..0x66ab014 (18 instructions)
Full-path commit: call 0x6760710(rcx = [rbx+0x768], rdx = rsi, r8 = [rbp+0x210]) [V]; interface call via [0x1233E1B0] -> [rbp+0x437] = al [V]; [rbp+0xD0] = 0x2003001 qword [V]; eax = ((([rbx+0x770]-[rbx+0x768])>>3) * 0xFFFFF0F1) - 1 -> [rbp+0xFA] = ax [V].

0x66aafbf  lea rcx,[rbx+0x768]
0x66aafc6  mov rdx,rsi
0x66aafc9  lea r8,[rbp+0x210]
0x66aafd0  call 0x6760710
0x66aafd5  nop
0x66aafd6  mov rcx,[0x1233E1B0]
0x66aafdd  mov rax,[rcx]
0x66aafe0  mov rax,[rax+0x10]
0x66aafe4  movzx edx,byte ptr [rbp+0x437]
0x66aafeb  call qword ptr [0xF99FFA0]
0x66aaff1  nop
0x66aaff2  mov qword ptr [rbp+0xD0],0x2003001
0x66aaffd  mov eax,[rbx+0x770]
0x66ab003  sub eax,[rbx+0x768]
0x66ab009  shr eax,3
0x66ab00c  imul eax,0xFFFFF0F1
0x66ab012  dec eax
0x66ab014  mov [rbp+0xFA],ax

### Phase P11 — 0x66ab01b..0x66ab08b (26 instructions)
Interface call via [0x1233E1B0] -> [rbp+0x437] = al [V]; if [rbx+0x860] != [rbx+0x868]: [rbx+0x860]++ (inc rdx then store) and jmp 0x66AB061, else call 0x6760E60(rcx = [rbx+0x858]) [V]; interface call via [0x1233E1B0] -> [rbp+0x437] = al [V]; eax = (~[rbx+0x858]) + [rbx+0x860] -> [rbp+0xE6] = ax [V].

0x66ab01b  mov rcx,[0x1233E1B0]
0x66ab022  mov rax,[rcx]
0x66ab025  mov rax,[rax+0x10]
0x66ab029  mov dl,0x4A
0x66ab02b  call qword ptr [0xF99FFA0]
0x66ab031  nop
0x66ab032  mov [rbp+0x437],al
0x66ab038  mov rdx,[rbx+0x860]
0x66ab03f  cmp rdx,[rbx+0x868]
0x66ab046  je short 0x66AB054
0x66ab048  inc rdx
0x66ab04b  mov [rbx+0x860],rdx
0x66ab052  jmp short 0x66AB061
0x66ab054  lea rcx,[rbx+0x858]
0x66ab05b  call 0x6760E60
0x66ab060  nop
0x66ab061  mov rcx,[0x1233E1B0]
0x66ab068  mov rax,[rcx]
0x66ab06b  mov rax,[rax+0x10]
0x66ab06f  movzx edx,byte ptr [rbp+0x437]
0x66ab076  call qword ptr [0xF99FFA0]
0x66ab07c  nop
0x66ab07d  mov eax,[rbx+0x858]
0x66ab083  not eax
0x66ab085  add eax,[rbx+0x860]
0x66ab08b  mov [rbp+0xE6],ax

### Phase P12 — 0x66ab092..0x66ab0bd (10 instructions)
Interface call via [0x1233E1B0] -> [rbp+0x437] = al [V]; rdx = [rbx+0x758]; if rdx == [rbx+0x760] -> 0x66AB130 (outside this slice) [V]; otherwise falls through to P13.

0x66ab092  mov rcx,[0x1233E1B0]
0x66ab099  mov rax,[rcx]
0x66ab09c  mov rax,[rax+0x10]
0x66ab0a0  mov dl,0x4A
0x66ab0a2  call qword ptr [0xF99FFA0]
0x66ab0a8  nop
0x66ab0a9  mov [rbp+0x437],al
0x66ab0af  mov rdx,[rbx+0x758]
0x66ab0b6  cmp rdx,[rbx+0x760]
0x66ab0bd  je short 0x66AB130

### Phase P13 — 0x66ab0bf..0x66ab0d7 (7 instructions)
Element store at committed cursor: eax = [r14+0x10], [rdx+0x10] = eax (dword) [V]; movups [rdx] = [r14] (16B element copy) [V]; al = byte [rbp+0x1C8], [rdx+0x14] = al [V]; movss xmm0 = [rbp+0x1CC] (4B load, last instruction of the slice) [V].

0x66ab0bf  mov eax,[r14+0x10]
0x66ab0c3  mov [rdx+0x10],eax
0x66ab0c6  movups xmm0,[r14]
0x66ab0ca  movups [rdx],xmm0
0x66ab0cd  movzx eax,byte ptr [rbp+0x1C8]
0x66ab0d4  mov [rdx+0x14],al
0x66ab0d7  movss xmm0,[rbp+0x1CC]

## Fields touched ([reg+off] fields stored or loaded; one row per distinct offset, all sites listed)

| offset | size | direction | verbatim sites | meaning |
|---|---|---|---|---|
| rcx+0x0 | 8 | R | R: 0x66aac49  mov rax,[rcx] | - |
| rax+0x10 | 16/8 | R/W | R: 0x66aac4c  mov rax,[rax+0x10]; W: 0x66aae1c  movups [rax+0x10],xmm6 | - |
| rbx+0x230 | 8 | R/W | R: 0x66aac5e  mov rdi,[rbx+0x230]; W: 0x66aac71  mov [rbx+0x230],rdi; R: 0x66aad21  cmp rdi,[rbx+0x230]; R: 0x66aad53  cmp rdi,[rbx+0x230]; R: 0x66aad7c  mov r8,[rbx+0x230] | - |
| rbx+0x238 | 8 | R | R: 0x66aac65  cmp rdi,[rbx+0x238] | - |
| rbp+0x437 | 1 | R/W | W: 0x66aac80  mov [rbp+0x437],sil; R: 0x66aaec3  movzx edx,byte ptr [rbp+0x437]; W: 0x66aae77  mov [rbp+0x437],al; W: 0x66aaefe  mov [rbp+0x437],al; R: 0x66aaf26  movzx edx,byte ptr [rbp+0x437]; W: 0x66aaf68  mov [rbp+0x437],al; R: 0x66aafeb  movzx edx,byte ptr [rbp+0x437]; W: 0x66ab032  mov [rbp+0x437],al; R: 0x66ab06f  movzx edx,byte ptr [rbp+0x437]; W: 0x66ab0a9  mov [rbp+0x437],al | - |
| rbx+0x228 | 8 | R | R: 0x66aac8a  sub rsi,[rbx+0x228]; R: 0x66aad67  mov rdx,[rbx+0x228] | - |
| rbp+0x428 | 8 | W | W: 0x66aacba  mov [rbp+0x428],rdx | - |
| r12-8 | 8 | W | W: 0x66aad1c  mov [r12-8],rax | - |
| rbp+0x3C8 | 8 | R | R: 0x66aad93  mov rdx,[rbp+0x3C8] | - |
| rbp+0x310 | 8 | W | W: 0x66aad9a  mov [rbp+0x310],rdx | - |
| rbp+0x318 | 8 | W | W: 0x66aada1  mov [rbp+0x318],rcx | - |
| rbp+0x320 | 1 | W | W: 0x66aada8  mov [rbp+0x320],al | - |
| rcx+0x48 | 8 | R | R: 0x66aadb5  mov rax,[rcx+0x48] | - |
| r14+0x184 | 8 | W | W: 0x66aadb9  mov [r14+0x184],rax | - |
| rcx+0x38 | 16 | R | R: 0x66aadc0  movups xmm0,[rcx+0x38] | - |
| r14+0x174 | 16 | W | W: 0x66aadc4  movups [r14+0x174],xmm0 | - |
| r15+0x10 | 8 | R | R: 0x66aadcc  mov rcx,[r15+0x10] | - |
| rax+0xB0 | 16 | W | W: 0x66aade8  movups [rax+0xB0],xmm6 | - |
| rax+0xA0 | 16 | W | W: 0x66aadef  movups [rax+0xA0],xmm6 | - |
| rax+0x90 | 16 | W | W: 0x66aadf6  movups [rax+0x90],xmm6 | - |
| rax+0x80 | 16 | W | W: 0x66aadfd  movups [rax+0x80],xmm6 | - |
| rax+0x70 | 16 | W | W: 0x66aae04  movups [rax+0x70],xmm6 | - |
| rax+0x60 | 16 | W | W: 0x66aae08  movups [rax+0x60],xmm6 | - |
| rax+0x50 | 16 | W | W: 0x66aae0c  movups [rax+0x50],xmm6 | - |
| rax+0x40 | 16 | W | W: 0x66aae10  movups [rax+0x40],xmm6 | - |
| rax+0x30 | 16 | W | W: 0x66aae14  movups [rax+0x30],xmm6 | - |
| rax+0x20 | 16 | W | W: 0x66aae18  movups [rax+0x20],xmm6 | - |
| rax+0 | 16 | W | W: 0x66aae20  movups [rax],xmm6 | - |
| rbx+0x788 | 4 | R | R: 0x66aae42  mov eax,[rbx+0x788] | - |
| rbx+0x780 | 4 | R | R: 0x66aae48  sub eax,[rbx+0x780] | - |
| rbp+0xF8 | 2 | W | W: 0x66aae59  mov [rbp+0xF8],ax | - |
| rbx+0x8A8 | 8/8/4 | R/W/R | R: 0x66aae7d  mov rdx,[rbx+0x8A8]; W: 0x66aae97  add qword ptr [rbx+0x8A8],2; R: 0x66aaed1  mov eax,[rbx+0x8A8] | - |
| rbx+0x8B0 | 8 | R | R: 0x66aae84  cmp rdx,[rbx+0x8B0] | - |
| rbp+0x2E0 | 2 | R | R: 0x66aae8d  movzx eax,word ptr [rbp+0x2E0] | - |
| rbp+0xE0 | 2 | W | W: 0x66aaee1  mov [rbp+0xE0],ax | - |
| rbx+0x8A0 | 4 | R | R: 0x66aaed7  sub eax,[rbx+0x8A0] | - |
| rbx+0x650 | 4 | R | R: 0x66aaf34  mov eax,[rbx+0x650] | - |
| rbx+0x648 | 4 | R | R: 0x66aaf3a  sub eax,[rbx+0x648] | - |
| rbp+0x112 | 2 | W | W: 0x66aaf4b  mov [rbp+0x112],ax | - |
| rbx+0x770 | 8/8/4 | R/W/R | R: 0x66aaf6e  mov rsi,[rbx+0x770]; W: 0x66aafb2  add qword ptr [rbx+0x770],0x88; R: 0x66aaffd  mov eax,[rbx+0x770] | - |
| rbx+0x778 | 8 | R | R: 0x66aaf75  cmp rsi,[rbx+0x778] | - |
| rbp+0x210 | 8 | R | R: 0x66aaf7e  mov rax,[rbp+0x210] | - |
| rsi+0 | 8 | W | W: 0x66aaf85  mov [rsi],rax | - |
| rbp+0x290 | 8 | R/W | R: 0x66aaf99  mov rax,[rbp+0x290]; W: 0x66aafa7  mov qword ptr [rbp+0x290],0 | - |
| rsi+0x80 | 8 | W | W: 0x66aafa0  mov [rsi+0x80],rax | - |
| rbx+0x768 | 4 | R | R: 0x66ab003  sub eax,[rbx+0x768] | - |
| rbp+0xD0 | 8 | W | W: 0x66aae37  mov qword ptr [rbp+0xD0],0x1000; W: 0x66aaff2  mov qword ptr [rbp+0xD0],0x2003001 | - |
| rbp+0xFA | 2 | W | W: 0x66ab014  mov [rbp+0xFA],ax | - |
| rbx+0x860 | 8/8/4 | R/W/R | R: 0x66ab038  mov rdx,[rbx+0x860]; W: 0x66ab04b  mov [rbx+0x860],rdx; R: 0x66ab085  add eax,[rbx+0x860] | - |
| rbx+0x868 | 8 | R | R: 0x66ab03f  cmp rdx,[rbx+0x868] | - |
| rbx+0x858 | 4 | R | R: 0x66ab07d  mov eax,[rbx+0x858] | - |
| rbp+0xE6 | 2 | W | W: 0x66ab08b  mov [rbp+0xE6],ax | - |
| rbx+0x758 | 8 | R | R: 0x66ab0af  mov rdx,[rbx+0x758] | - |
| rbx+0x760 | 8 | R | R: 0x66ab0b6  cmp rdx,[rbx+0x760] | - |
| r14+0x10 | 4 | R | R: 0x66ab0bf  mov eax,[r14+0x10] | - |
| rdx+0x10 | 4 | W | W: 0x66ab0c3  mov [rdx+0x10],eax | - |
| r14+0 | 16 | R | R: 0x66ab0c6  movups xmm0,[r14] | - |
| rdx+0 | 16/2 | W | W: 0x66aae94  mov [rdx],ax; W: 0x66ab0ca  movups [rdx],xmm0 | - |
| rbp+0x1C8 | 1 | R | R: 0x66ab0cd  movzx eax,byte ptr [rbp+0x1C8] | - |
| rdx+0x14 | 1 | W | W: 0x66ab0d4  mov [rdx+0x14],al | - |
| rbp+0x1CC | 4 | R | R: 0x66ab0d7  movss xmm0,[rbp+0x1CC] | - |

## Calls and jumps out of the slice
Direct calls (callee identity not shown in the slice, [I]): 0xEEC6DE0 (P4), 0x5ABA5C0 (P5), 0x675F3B0 (P6), 0x1EF6F90 (P7), 0x675FB30 (P8), 0xE869FF0 (P9), 0x6760710 (P10), 0x6760E60 (P11).
Indirect calls: via IAT slot 0xF99FFA0 — rdis annotates [data_f99ffa0] = sub_eea6040 [V]; via interface vtable [rax+0x10] / [rcx+0x10] with object pointer from globals 0x1233E1A8 or 0x1233E1B0, dl = 0x4A [V].
Jump targets outside the slice ([I], continuations not listed here): 0x66AB379, 0x66AB73A, 0x66AB2D6, 0x66AB746, 0x66AB653, 0x66AB2CD, 0x66AB2E6, 0x66AB2F6, 0x66AB130.

## OPEN questions
- Semantics of byte field [rbp+0x437] (written with sil/al returned by the interface calls) — not shown by any instruction or string [?].
- Meaning of qword [rbp+0xD0] = 0x1000 vs 0x2003001 — not shown [?].
- Allocation header stored at [r12-8] — not shown [?].
- Identities of the eight direct callees (0xEEC6DE0, 0x5ABA5C0, 0x675F3B0, 0x1EF6F90, 0x675FB30, 0xE869FF0, 0x6760710, 0x6760E60) — not shown [?].

## TOOL REQUESTS
None.
