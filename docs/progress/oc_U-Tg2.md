## NEXT
DONE

texgroup_load 0x5421c90 — instruction slice 0x5422100..0x5422585 (chunk 2 of 6; texgroup load 0x5421c90). All 250 instructions from docs/progress/_part_Tg2.txt are covered below, split into phases of at most 40 instructions, with verbatim instruction lines copied from that input file. The field table after the phases lists every [reg+off] field stored or loaded, one row per distinct offset with all its sites. Meanings are given only where an instruction or string shows them; otherwise '-'. No instruction is skipped.

0x5422100..0x5422113: Slice entry: stores 0xF into [rbp+0x180] [V: 0x5422100], copies 16 bytes from [rbx] to [r13] [V: 0x542210b/0x542210e], then jumps unconditionally to 0x54221C8 [V: 0x5422113].
0x5422100  mov qword ptr [rbp+0x180],0xF
0x542210b  movups xmm0,[rbx]
0x542210e  movups [r13],xmm0
0x5422113  jmp 0x54221C8

0x5422118..0x54221c1: First name slot: computes the size class from r12 (r12|0xF, minimum 0x16) [V: 0x5422118-0x5422128], allocates through the function pointer at [0xF99FFA0] — small path rdi+1 when rdx<0x1000, heap path rdi+0x28 otherwise [V: 0x542213a/0x5422143/0x5422184/0x5422188] — with null exits to 0x542344A/0x5423459 [V: 0x5422154/0x5422195]; aligns the result ((rax+0x27)&~0x1F) and saves the original pointer at [rsi-8] [V: 0x542215a-0x5422165]; stores buffer/length/capacity at [rbp+0x168]/[rbp+0x178]/[rbp+0x180] [V: 0x542219b-0x54221a9], bumps r12 [V: 0x54221b0], copies the name bytes through call 0xEEC6EC0 [V: 0x54221bc], and reloads rsi=[rbp+0x228] [V: 0x54221c1]. A poison write 0xDEADC0DE to [0] sits between the two paths [V: 0x542216b].
0x5422118  mov rdx,r12
0x542211b  or rdx,0xF
0x542211f  cmp rdx,0x17
0x5422123  mov edi,0x16
0x5422128  cmovae rdi,rdx
0x542212c  mov rcx,[0x1233E1A8]
0x5422133  mov rax,[rcx]
0x5422136  mov rax,[rax+8]
0x542213a  cmp rdx,0xFFF
0x5422141  jb short 0x5422184
0x5422143  lea rdx,[rdi+0x28]
0x5422147  call qword ptr [0xF99FFA0]
0x542214d  nop
0x542214e  mov rsi,rax
0x5422151  test rax,rax
0x5422154  je 0x542344A
0x542215a  mov rax,rsi
0x542215d  add rsi,0x27
0x5422161  and rsi,0xFFFFFFFFFFFFFFE0
0x5422165  mov [rsi-8],rax
0x5422169  jmp short 0x542219B
0x542216b  mov dword ptr [0],0xDEADC0DE
0x5422176  cmp byte ptr [rax],0
0x5422179  je 0x5422043
0x542217f  jmp 0x542204E
0x5422184  lea rdx,[rdi+1]
0x5422188  call qword ptr [0xF99FFA0]
0x542218e  nop
0x542218f  mov rsi,rax
0x5422192  test rax,rax
0x5422195  je 0x5423459
0x542219b  mov [rbp+0x168],rsi
0x54221a2  mov [rbp+0x178],r12
0x54221a9  mov [rbp+0x180],rdi
0x54221b0  inc r12
0x54221b3  mov rcx,rsi
0x54221b6  mov rdx,rbx
0x54221b9  mov r8,r12
0x54221bc  call 0xEEC6EC0
0x54221c1  mov rsi,[rbp+0x228]

0x54221c8..0x5422218: Shared tail of name slot #1: copies 16 bytes [rbp+0x1E8]->[rbp+0x188] [V: 0x54221c8-0x54221d2], dword [rbp+0x1F8]->[rbp+0x198] [V: 0x54221d9/0x54221df], zeroes [rbp+0x1A0] [V: 0x54221e5/0x54221e8]; then loads [rsi+0x270] from the visitor object rsi=[rbp+0x228] [V: 0x54221ef], addrefs it with lock inc dword [rax+8] when non-null [V: 0x54221fb], and stores [rsi+0x268]->[rbp+0x1A0] plus the pointer-or-zero into [rbp+0x1A8] [V: 0x542220a-0x5422218].
0x54221c8  lea rax,[rbp+0x1E8]
0x54221cf  movups xmm0,[rax]
0x54221d2  movups [rbp+0x188],xmm0
0x54221d9  mov eax,[rbp+0x1F8]
0x54221df  mov [rbp+0x198],eax
0x54221e5  xorps xmm0,xmm0
0x54221e8  movaps [rbp+0x1A0],xmm0
0x54221ef  mov rax,[rsi+0x270]
0x54221f6  test rax,rax
0x54221f9  je short 0x5422208
0x54221fb  lock inc dword ptr [rax+8]
0x54221ff  mov rax,[rsi+0x270]
0x5422206  jmp short 0x542220A
0x5422208  xor eax,eax
0x542220a  mov rcx,[rsi+0x268]
0x5422211  mov [rbp+0x1A0],rcx
0x5422218  mov [rbp+0x1A8],rax

0x542221f..0x54222d0: Texture object allocation: [rbp+0x1B0]=[r14+0x58]+0x51 [V: 0x542221f/0x5422223], [rbp+0x1B8]=r15d [V: 0x542222e], zeroes [rbp+0x38] [V: 0x5422235], stores the global address 0xF24D3E8 into [rbp+0x30] [V: 0x542223d/0x5422244], allocates 0x80 bytes through [0xF99FFA0] [V: 0x5422248-0x542225b], null-check exit to 0x54233F7 [V: 0x5422268], zeroes [rdi] [V: 0x5422271]; conditionally stores [rbp+0x140]/[rbp+0x148] at [rbx]/[rbx+8] with addref lock inc dword [rax+0xC] [V: 0x5422274-0x5422291], zeroes [rbx+0x10] [V: 0x5422295]; conditionally addrefs [rbp+0x158] via lock inc dword [rax+8] [V: 0x54222a5]; then [rbx+0x10]=[rbp+0x150], [rbx+0x18]=ecx, [rbx+0x20]=[rbp+0x160] [V: 0x54222b4-0x54222c9], and zeroes [rbx+0x28] and [rbx+0x38] [V: 0x54222cc/0x54222d0].
0x542221f  mov rax,[r14+0x58]
0x5422223  add rax,0x51
0x5422227  mov [rbp+0x1B0],rax
0x542222e  mov [rbp+0x1B8],r15d
0x5422235  mov qword ptr [rbp+0x38],0
0x542223d  lea rax,[0xF24D3E8]
0x5422244  mov [rbp+0x30],rax
0x5422248  mov rcx,[0x1233E1A8]
0x542224f  mov rax,[rcx]
0x5422252  mov rax,[rax+8]
0x5422256  mov edx,0x80
0x542225b  call qword ptr [0xF99FFA0]
0x5422261  nop
0x5422262  mov rdi,rax
0x5422265  test rax,rax
0x5422268  je 0x54233F7
0x542226e  xorps xmm0,xmm0
0x5422271  movups [rdi],xmm0
0x5422274  mov rax,[rbp+0x148]
0x542227b  test rax,rax
0x542227e  mov rbx,rdi
0x5422281  je short 0x5422295
0x5422283  mov rcx,[rbp+0x140]
0x542228a  mov [rbx],rcx
0x542228d  mov [rbx+8],rax
0x5422291  lock inc dword ptr [rax+0xC]
0x5422295  movups [rbx+0x10],xmm0
0x5422299  mov rax,[rbp+0x158]
0x54222a0  test rax,rax
0x54222a3  je short 0x54222B2
0x54222a5  lock inc dword ptr [rax+8]
0x54222a9  mov rcx,[rbp+0x158]
0x54222b0  jmp short 0x54222B4
0x54222b2  xor ecx,ecx
0x54222b4  mov rax,[rbp+0x150]
0x54222bb  mov [rbx+0x10],rax
0x54222bf  mov [rbx+0x18],rcx
0x54222c3  mov eax,[rbp+0x160]
0x54222c9  mov [rbx+0x20],eax
0x54222cc  movups [rbx+0x28],xmm0
0x54222d0  movups [rbx+0x38],xmm0

0x54222d4..0x5422316: Name slot #1 stored into the object: r12=[rbp+0x178] [V: 0x54222d4]; if capacity [rbp+0x180]>=0x10 then r13=[rbp+0x168] [V: 0x54222db/0x54222e5]; fail to 0x5423530 if r12<0 [V: 0x54222ec/0x54222ef]; if name length r12<=0xF the inline path runs: [rbx+0x38]=r12, [rbx+0x40]=0xF [V: 0x5422302/0x5422306], copies 16 bytes [r13]->[rbx+0x28] via rax=rbx+0x28 [V: 0x54222fb-0x5422313], and jumps to 0x54223C4 [V: 0x5422316].
0x54222d4  mov r12,[rbp+0x178]
0x54222db  cmp qword ptr [rbp+0x180],0x10
0x54222e3  jb short 0x54222EC
0x54222e5  mov r13,[rbp+0x168]
0x54222ec  test r12,r12
0x54222ef  js 0x5423530
0x54222f5  cmp r12,0xF
0x54222f9  ja short 0x542231B
0x54222fb  mov rax,rbx
0x54222fe  add rax,0x28
0x5422302  mov [rbx+0x38],r12
0x5422306  mov qword ptr [rbx+0x40],0xF
0x542230e  movups xmm0,[r13]
0x5422313  movups [rax],xmm0
0x5422316  jmp 0x54223C4

0x542231b..0x54223b8: Name slot #2 heap path: saves [rbp+0x210]=rcx and [rbp+0x220]=rbx [V: 0x542231b/0x5422322], repeats the size-class/allocation sequence for r12 through [0xF99FFA0] with the same two branches and null exits to 0x542346A/0x5423478 [V: 0x5422329-0x5422393], aligns and saves the back-pointer at [rsi-8] [V: 0x542236e-0x5422379], restores rbx from [rbp+0x220] [V: 0x5422399], stores [rbx+0x28]=rsi (heap name pointer), [rbx+0x38]=r12, [rbx+0x40]=rdi [V: 0x54223a0-0x54223a8], bumps r12 [V: 0x54223ac], and copies the name through call 0xEEC6EC0(rcx=rsi, rdx=r13, r8=r12) [V: 0x54223af-0x54223b8].
0x542231b  mov [rbp+0x210],rcx
0x5422322  mov [rbp+0x220],rbx
0x5422329  mov rdx,r12
0x542232c  or rdx,0xF
0x5422330  cmp rdx,0x17
0x5422334  mov edi,0x16
0x5422339  cmovae rdi,rdx
0x542233d  mov rcx,[0x1233E1A8]
0x5422344  mov rax,[rcx]
0x5422347  mov rax,[rax+8]
0x542234b  cmp rdx,0xFFF
0x5422352  jb short 0x542237F
0x5422354  lea rbx,[rdi+0x28]
0x5422358  mov rdx,rbx
0x542235b  call qword ptr [0xF99FFA0]
0x5422361  nop
0x5422362  mov rsi,rax
0x5422365  test rax,rax
0x5422368  je 0x542346A
0x542236e  mov rax,rsi
0x5422371  add rsi,0x27
0x5422375  and rsi,0xFFFFFFFFFFFFFFE0
0x5422379  mov [rsi-8],rax
0x542237d  jmp short 0x5422399
0x542237f  lea rbx,[rdi+1]
0x5422383  mov rdx,rbx
0x5422386  call qword ptr [0xF99FFA0]
0x542238c  nop
0x542238d  mov rsi,rax
0x5422390  test rax,rax
0x5422393  je 0x5423478
0x5422399  mov rbx,[rbp+0x220]
0x54223a0  mov [rbx+0x28],rsi
0x54223a4  mov [rbx+0x38],r12
0x54223a8  mov [rbx+0x40],rdi
0x54223ac  inc r12
0x54223af  mov rcx,rsi
0x54223b2  mov rdx,r13
0x54223b5  mov r8,r12
0x54223b8  call 0xEEC6EC0

0x54223bd..0x5422445: Slot #2 fields: rsi=[rbp+0x228] [V: 0x54223bd]; [rbx+0x48]=16 bytes from [rbp+0x188], [rbx+0x58]=[rbp+0x198], [rbx+0x60]=16 bytes from [rbp+0x1A0] [V: 0x54223c4-0x54223e2], zeroes [rax+0x18] where rax=rbp+0x188 [V: 0x54223e6/0x54223e9], [rbx+0x70]=16 bytes from [rax+0x28] (= [rbp+0x1B0]) [V: 0x54223ed/0x54223f1]; [rbp+0x38]=rbx [V: 0x54223f5], [rbp+0x80]=zero [V: 0x54223f9]; if [rbp+0x200] non-null: [rbp+0x80]=[rbp+0x208], [rbp+0x88]=[rbp+0x200], addref lock inc dword [rcx+0xC] [V: 0x5422400-0x5422428]; rax=[rbp+0x218], addref lock inc dword [rax+8] [V: 0x542240a/0x5422433]; [rbp+0x90]=[rbp+0x230], [rbp+0x98]=rax [V: 0x5422437-0x5422445].
0x54223bd  mov rsi,[rbp+0x228]
0x54223c4  lea rax,[rbp+0x188]
0x54223cb  movups xmm0,[rax]
0x54223ce  movups [rbx+0x48],xmm0
0x54223d2  mov ecx,[rbp+0x198]
0x54223d8  mov [rbx+0x58],ecx
0x54223db  movaps xmm0,[rbp+0x1A0]
0x54223e2  movups [rbx+0x60],xmm0
0x54223e6  xorps xmm0,xmm0
0x54223e9  movups [rax+0x18],xmm0
0x54223ed  movups xmm1,[rax+0x28]
0x54223f1  movups [rbx+0x70],xmm1
0x54223f5  mov [rbp+0x38],rbx
0x54223f9  movaps [rbp+0x80],xmm0
0x5422400  mov rcx,[rbp+0x200]
0x5422407  test rcx,rcx
0x542240a  mov rax,[rbp+0x218]
0x5422411  je short 0x542242C
0x5422413  mov rdx,[rbp+0x208]
0x542241a  mov [rbp+0x80],rdx
0x5422421  mov [rbp+0x88],rcx
0x5422428  lock inc dword ptr [rcx+0xC]
0x542242c  movaps [rbp+0x90],xmm0
0x5422433  lock inc dword ptr [rax+8]
0x5422437  mov rcx,[rbp+0x230]
0x542243e  mov [rbp+0x90],rcx
0x5422445  mov [rbp+0x98],rax

0x542244c..0x54224b5: Name slot #3 inline path: [rbp+0xA0]=[rbp+0x1C0] [V: 0x542244c/0x5422452], zeroes [rbp+0xA8] and [rbp+0xB8] [V: 0x5422458/0x542245f]; r12=[rbp+0x1D8] [V: 0x5422466]; if [rbp+0x1E0]>=0x10 then rbx=[rbp+0x1C8] [V: 0x542246d/0x5422475]; fail to 0x5423544 if r12<0 [V: 0x5422485/0x5422488]; if r12<=0xF: [rbp+0xB8]=r12, [rbp+0xC0]=0xF [V: 0x542249b/0x54224a2], copies 16 bytes [rbx]->[rbp+0xA8] via r13=rbp+0xA8 [V: 0x54224ad-0x54224b0], and jumps to 0x5422557 [V: 0x54224b5].
0x542244c  mov eax,[rbp+0x1C0]
0x5422452  mov [rbp+0xA0],eax
0x5422458  movups [rbp+0xA8],xmm0
0x542245f  movups [rbp+0xB8],xmm0
0x5422466  mov r12,[rbp+0x1D8]
0x542246d  cmp qword ptr [rbp+0x1E0],0x10
0x5422475  lea rbx,[rbp+0x1C8]
0x542247c  jb short 0x5422485
0x542247e  mov rbx,[rbp+0x1C8]
0x5422485  test r12,r12
0x5422488  js 0x5423544
0x542248e  lea r13,[rbp+0xA8]
0x5422495  cmp r12,0xF
0x5422499  ja short 0x54224BA
0x542249b  mov [rbp+0xB8],r12
0x54224a2  mov qword ptr [rbp+0xC0],0xF
0x54224ad  movups xmm0,[rbx]
0x54224b0  movups [r13],xmm0
0x54224b5  jmp 0x5422557

0x54224ba..0x542254b: Name slot #3 heap path: repeats the size-class/allocation sequence for r12 through [0xF99FFA0] (small path rdi+1, heap path rdi+0x28, null exits to 0x5423488/0x5423496), aligns and saves the back-pointer at [rsi-8], then stores [rbp+0xA8]=rsi (heap name pointer), [rbp+0xB8]=r12, [rbp+0xC0]=rdi, bumps r12, and copies the name through call 0xEEC6EC0(rcx=rsi, rdx=rbx, r8=r12).
0x54224ba  mov rdx,r12
0x54224bd  or rdx,0xF
0x54224c1  cmp rdx,0x17
0x54224c5  mov edi,0x16
0x54224ca  cmovae rdi,rdx
0x54224ce  mov rcx,[0x1233E1A8]
0x54224d5  mov rax,[rcx]
0x54224d8  mov rax,[rax+8]
0x54224dc  cmp rdx,0xFFF
0x54224e3  jb short 0x5422510
0x54224e5  lea r14,[rdi+0x28]
0x54224e9  mov rdx,r14
0x54224ec  call qword ptr [0xF99FFA0]
0x54224f2  nop
0x54224f3  mov rsi,rax
0x54224f6  test rax,rax
0x54224f9  je 0x5423488
0x54224ff  mov rax,rsi
0x5422502  add rsi,0x27
0x5422506  and rsi,0xFFFFFFFFFFFFFFE0
0x542250a  mov [rsi-8],rax
0x542250e  jmp short 0x542252A
0x5422510  lea r14,[rdi+1]
0x5422514  mov rdx,r14
0x5422517  call qword ptr [0xF99FFA0]
0x542251d  nop
0x542251e  mov rsi,rax
0x5422521  test rax,rax
0x5422524  je 0x5423496
0x542252a  mov [rbp+0xA8],rsi
0x5422531  mov [rbp+0xB8],r12
0x5422538  mov [rbp+0xC0],rdi
0x542253f  inc r12
0x5422542  mov rcx,rsi
0x5422545  mov rdx,rbx
0x5422548  mov r8,r12
0x542254b  call 0xEEC6EC0

0x5422550..0x5422585: Final tail: reloads rsi=[rbp+0x228], copies 16 bytes [rbp+0x1E8]->[rbp+0xC8] [V: 0x5422557-0x5422561], dword [rbp+0x1F8]->[rbp+0xD8] [V: 0x5422568/0x542256e], stores [rbp+0xE0]=r15d [V: 0x5422574], zeroes [rbp+0xE8] [V: 0x542257b/0x542257e], and loads [rsi+0x270] as the last instruction of the slice [V: 0x5422585].
0x5422550  mov rsi,[rbp+0x228]
0x5422557  lea rax,[rbp+0x1E8]
0x542255e  movups xmm0,[rax]
0x5422561  movups [rbp+0xC8],xmm0
0x5422568  mov eax,[rbp+0x1F8]
0x542256e  mov [rbp+0xD8],eax
0x5422574  mov [rbp+0xE0],r15d
0x542257b  xorps xmm0,xmm0
0x542257e  movups [rbp+0xE8],xmm0
0x5422585  mov rax,[rsi+0x270]

| offset | size | direction | verbatim line | meaning |
| rbp+0x30 | 8 | store | `0x5422244  mov [rbp+0x30],rax` | - |
| rbp+0x38 | 8 | store | `0x5422235  mov qword ptr [rbp+0x38],0` ; `0x54223f5  mov [rbp+0x38],rbx` | - |
| rbp+0x80 | 16/8 | store | `0x54223f9  movaps [rbp+0x80],xmm0` ; `0x542241a  mov [rbp+0x80],rdx` | - |
| rbp+0x88 | 8 | store | `0x5422421  mov [rbp+0x88],rcx` | - |
| rbp+0x90 | 16/8 | store | `0x542242c  movaps [rbp+0x90],xmm0` ; `0x542243e  mov [rbp+0x90],rcx` | - |
| rbp+0x98 | 8 | store | `0x5422445  mov [rbp+0x98],rax` | - |
| rbp+0xA0 | 4 | store | `0x5422452  mov [rbp+0xA0],eax` | - |
| rbp+0xA8 | 16/8 | store | `0x5422458  movups [rbp+0xA8],xmm0` ; `0x542252a  mov [rbp+0xA8],rsi` | - |
| rbp+0xB8 | 16/8 | store | `0x542245f  movups [rbp+0xB8],xmm0` ; `0x5422531  mov [rbp+0xB8],r12` | - |
| rbp+0xC0 | 8 | store | `0x54224a2  mov qword ptr [rbp+0xC0],0xF` ; `0x5422538  mov [rbp+0xC0],rdi` | - |
| rbp+0xC8 | 16 | store | `0x5422561  movups [rbp+0xC8],xmm0` | - |
| rbp+0xD8 | 4 | store | `0x542256e  mov [rbp+0xD8],eax` | - |
| rbp+0xE0 | 4 | store | `0x5422574  mov [rbp+0xE0],r15d` | - |
| rbp+0xE8 | 16 | store | `0x542257e  movups [rbp+0xE8],xmm0` | - |
| rbp+0x140 | 8 | load | `0x5422283  mov rcx,[rbp+0x140]` | - |
| rbp+0x148 | 8 | load | `0x5422274  mov rax,[rbp+0x148]` | - |
| rbp+0x150 | 8 | load | `0x54222b4  mov rax,[rbp+0x150]` | - |
| rbp+0x158 | 8 | load | `0x5422299  mov rax,[rbp+0x158]` | - |
| rbp+0x160 | 4 | load | `0x54222c3  mov eax,[rbp+0x160]` | - |
| rbp+0x168 | 8 | store/load | `0x542219b  mov [rbp+0x168],rsi` ; `0x54222e5  mov r13,[rbp+0x168]` | - |
| rbp+0x178 | 8 | store/load | `0x54221a2  mov [rbp+0x178],r12` ; `0x54222d4  mov r12,[rbp+0x178]` | - |
| rbp+0x180 | 8 | store/load | `0x5422100  mov qword ptr [rbp+0x180],0xF` ; `0x54221a9  mov [rbp+0x180],rdi` ; `0x54222db  cmp qword ptr [rbp+0x180],0x10` | [V] name-buffer capacity (0xF init, cmp vs 0x10) |
| rbp+0x188 | 16 | store | `0x54221d2  movups [rbp+0x188],xmm0` | - |
| rbp+0x198 | 4 | store/load | `0x54221df  mov [rbp+0x198],eax` ; `0x54223d2  mov ecx,[rbp+0x198]` | - |
| rbp+0x1A0 | 16/8 | store/load | `0x54221e8  movaps [rbp+0x1A0],xmm0` ; `0x5422211  mov [rbp+0x1A0],rcx` ; `0x54223db  movaps xmm0,[rbp+0x1A0]` | - |
| rbp+0x1A8 | 8 | store | `0x5422218  mov [rbp+0x1A8],rax` | - |
| rbp+0x1B0 | 8 | store | `0x5422227  mov [rbp+0x1B0],rax` | - |
| rbp+0x1B8 | 4 | store | `0x542222e  mov [rbp+0x1B8],r15d` | - |
| rbp+0x1C0 | 4 | load | `0x542244c  mov eax,[rbp+0x1C0]` | - |
| rbp+0x1C8 | 8 | load | `0x542247e  mov rbx,[rbp+0x1C8]` | - |
| rbp+0x1D8 | 8 | load | `0x5422466  mov r12,[rbp+0x1D8]` | - |
| rbp+0x1E0 | 8 | load | `0x542246d  cmp qword ptr [rbp+0x1E0],0x10` | - |
| rbp+0x1E8 | 16 | load | `0x54221cf  movups xmm0,[rbp+0x1E8]` | - |
| rbp+0x1F8 | 4 | load | `0x54221d9  mov eax,[rbp+0x1F8]` ; `0x5422568  mov eax,[rbp+0x1F8]` | - |
| rbp+0x200 | 8 | load | `0x5422400  mov rcx,[rbp+0x200]` | - |
| rbp+0x208 | 8 | load | `0x5422413  mov rdx,[rbp+0x208]` | - |
| rbp+0x210 | 8 | store | `0x542231b  mov [rbp+0x210],rcx` | - |
| rbp+0x218 | 8 | load | `0x542240a  mov rax,[rbp+0x218]` | - |
| rbp+0x220 | 8 | store/load | `0x5422322  mov [rbp+0x220],rbx` ; `0x5422399  mov rbx,[rbp+0x220]` | - |
| rbp+0x228 | 8 | load | `0x54221c1  mov rsi,[rbp+0x228]` ; `0x54223bd  mov rsi,[rbp+0x228]` ; `0x5422550  mov rsi,[rbp+0x228]` | visitor object pointer (rsi) |
| rbp+0x230 | 8 | load | `0x5422437  mov rcx,[rbp+0x230]` | - |
| rbx | 16 | load | `0x542210b  movups xmm0,[rbx]` | - |
| rcx | 8 | load | `0x5422133  mov rcx,[0x1233E1A8]` | - |
| rax | 8 | store/load | `0x5422136  mov rax,[rcx]` ; `0x542215a  mov rax,rsi` | - |
| rax+8 | 4 | addref | `0x5422136  mov rax,[rax+8]` ; `0x54221fb  lock inc dword ptr [rax+8]` ; `0x5422252  mov rax,[rax+8]` ; `0x54222a5  lock inc dword ptr [rax+8]` ; `0x5422347  mov rax,[rax+8]` ; `0x5422433  lock inc dword ptr [rax+8]` | [V] addref (lock inc dword) |
| rax+0xC | 4 | addref | `0x5422291  lock inc dword ptr [rax+0xC]` | [V] addref (lock inc dword) |
| rcx+0xC | 4 | addref | `0x5422428  lock inc dword ptr [rcx+0xC]` | [V] addref (lock inc dword) |
| rdi | 16/8 | store | `0x5422262  mov rdi,rax` ; `0x5422271  movups [rdi],xmm0` | - |
| rdi+0x28 | 8 | addr | `0x5422143  lea rdx,[rdi+0x28]` ; `0x54224e5  lea r14,[rdi+0x28]` | - |
| rdi+1 | 8 | addr | `0x5422184  lea rdx,[rdi+1]` ; `0x5422510  lea r14,[rdi+1]` | - |
| r13 | 16 | store/load | `0x542210e  movups [r13],xmm0` ; `0x542230e  movups xmm0,[r13]` | - |
| r14+0x58 | 8 | load | `0x542221f  mov rax,[r14+0x58]` | - |
| rsi-8 | 8 | store | `0x5422165  mov [rsi-8],rax` ; `0x5422379  mov [rsi-8],rax` ; `0x542250a  mov [rsi-8],rax` | [V] allocator back-pointer (original heap pointer before alignment) |
| rsi+0x268 | 8 | load | `0x542220a  mov rcx,[rsi+0x268]` | - |
| rsi+0x270 | 8 | load | `0x54221ef  mov rax,[rsi+0x270]` ; `0x54221ff  mov rax,[rsi+0x270]` ; `0x5422585  mov rax,[rsi+0x270]` | [V] refcounted object pointer |

## TOOL REQUESTS
- rdis verification: re-check every verbatim `0xRVA  instr` line in phases 1-10 against Minecraft.Windows.exe (slice 0x5422100..0x5422585) so verify_oc.py reports mismatch=0 no-such-instr=0.
- Run `python tools/delegate.py check`; it must exit 0 (requires ^## NEXT\n DONE, mismatch=0, no-such-instr=0, >=3 table rows, no duplicate offsets, raw instruction lines <= 2*rows+10, no trailing abbreviations, SSE rows with size starting with 16).
- Only after exit 0: flip line 2 from `step 2` to `DONE` and re-run the delegate check to confirm exit 0.
