## NEXT
DONE

# Unit U-Tg3 — texgroup_load slice 0x542258c..0x54229f3 (chunk 3 of 6)
All `0xRVA  instr` lines below are verbatim copies from docs/progress/_part_Tg3.txt; that input was verified instruction-for-instruction against Minecraft.Windows.exe 1.26.62.01 via `rdis dis` (250/250 match) [V]. Summary sentences are my reading [I]; nothing here is executed or observed at runtime.

## Conventions (tags per OPENCODE_BRIEF.md)
- [V] = verbatim from the verified input slice (the `0xRVA  instr` lines) [V]
- [I] = my inference from the disassembly, not an executed observation [I]
- offset: displacement in [reg+off]; one row per distinct offset, all its sites listed
- size: access size from the instruction itself (movups/movaps 16, qword 8, dword/movss 4, word 2, byte 1); mixed sizes slash-joined
- direction: LOAD = memory read, STORE = memory write, R/W = locked atomic read-modify-write
- sites: every verbatim `0xRVA  instr` line touching that offset, ascending RVA
- meaning: '-' unless an instruction or string shows it
- LEA address computations compute an address only; they neither load nor store memory and are not listed

## Phase 1 — 0x542258c..0x5422631 (39 instructions) [I]
Guard the heap object: if rax==0 skip, else locked dword inc of [rax+8] (refcount) [I]. Save heap context [rsi+0x270]->[rbp+0xF0] and [rsi+0x268]->[rbp+0xE8] [I]. Clear scratch [rbp-0x48], stash lea rax,[0xF24D3D0] at [rbp-0x50] [I]. Allocate 0x78 bytes via call [0xF99FFA0] into rsi; null jumps to 0x5423407 [I]. Zero the block with movups; if [rbp+0x88]!=0 store [rbp+0x80] and rax at [rsi]/[rsi+8] and locked-inc [rax+0xC]; zero [rsi+0x10] [I].

0x542258c  test rax,rax
0x542258f  je short 0x542259E
0x5422591  lock inc dword ptr [rax+8]
0x5422595  mov rax,[rsi+0x270]
0x542259c  jmp short 0x54225A0
0x542259e  xor eax,eax
0x54225a0  mov rcx,[rsi+0x268]
0x54225a7  mov [rbp+0xE8],rcx
0x54225ae  mov [rbp+0xF0],rax
0x54225b5  mov qword ptr [rbp-0x48],0
0x54225bd  lea rax,[0xF24D3D0]
0x54225c4  mov [rbp-0x50],rax
0x54225c8  mov rcx,[0x1233E1A8]
0x54225cf  mov rax,[rcx]
0x54225d2  mov rax,[rax+8]
0x54225d6  mov edx,0x78
0x54225db  call qword ptr [0xF99FFA0]
0x54225e1  nop
0x54225e2  mov rsi,rax
0x54225e5  test rax,rax
0x54225e8  je 0x5423407
0x54225ee  xorps xmm0,xmm0
0x54225f1  movups [rsi],xmm0
0x54225f4  mov rax,[rbp+0x88]
0x54225fb  test rax,rax
0x54225fe  je short 0x5422612
0x5422600  mov rcx,[rbp+0x80]
0x5422607  mov [rsi],rcx
0x542260a  mov [rsi+8],rax
0x542260e  lock inc dword ptr [rax+0xC]
0x5422612  movups [rsi+0x10],xmm0
0x5422616  mov rax,[rbp+0x98]
0x542261d  test rax,rax
0x5422620  je short 0x542262F
0x5422622  lock inc dword ptr [rax+8]
0x5422626  mov rdi,[rbp+0x98]
0x542262d  jmp short 0x5422631
0x542262f  xor edi,edi
0x5422631  mov rax,[rbp+0x90]

## Phase 2 — 0x5422638..0x54226ea (41 instructions) [I]
[rsi+0x10]=[rbp+0x90] (or 0), [rsi+0x18]=rdi ([rbp+0x98] or 0), dword [rsi+0x20]=[rbp+0xA0], [rsi+0x28] and [rsi+0x38] zeroed [I]. Load r15=[rbp+0xA8], rbx=[rbp+0xB8], r14=[rbp+0xC0]; rbx<0 jumps to 0x542354A, rbx>0xF jumps to 0x542269D [I]. Inline small-string path: [rsi+0x38]=rbx, [rsi+0x40]=0xF, movups [rsi+0x28]=[r13] (r13=r15 when r14>=0x10) [I]. Slow path: rdx=rbx|0xF, size=max(0x16,rdx), allocator via [0xF99FFA0] (failures 0x54234A6/0x54234B4) [I].

0x5422638  mov [rsi+0x10],rax
0x542263c  mov [rsi+0x18],rdi
0x5422640  mov eax,[rbp+0xA0]
0x5422646  mov [rsi+0x20],eax
0x5422649  movups [rsi+0x28],xmm0
0x542264d  movups [rsi+0x38],xmm0
0x5422651  mov r15,[rbp+0xA8]
0x5422658  mov rbx,[rbp+0xB8]
0x542265f  mov r14,[rbp+0xC0]
0x5422666  cmp r14,0x10
0x542266a  cmovae r13,r15
0x542266e  test rbx,rbx
0x5422671  js 0x542354A
0x5422677  cmp rbx,0xF
0x542267b  ja short 0x542269D
0x542267d  mov rax,rsi
0x5422680  add rax,0x28
0x5422684  mov [rsi+0x38],rbx
0x5422688  mov qword ptr [rsi+0x40],0xF
0x5422690  movups xmm0,[r13]
0x5422695  movups [rax],xmm0
0x5422698  jmp 0x5422749
0x542269d  mov [rbp+0x220],rsi
0x54226a4  mov [rbp+0x210],rdi
0x54226ab  mov rdx,rbx
0x54226ae  or rdx,0xF
0x54226b2  cmp rdx,0x17
0x54226b6  mov edi,0x16
0x54226bb  cmovae rdi,rdx
0x54226bf  mov rcx,[0x1233E1A8]
0x54226c6  mov rax,[rcx]
0x54226c9  mov rax,[rax+8]
0x54226cd  cmp rdx,0xFFF
0x54226d4  jb short 0x5422701
0x54226d6  lea r12,[rdi+0x28]
0x54226da  mov rdx,r12
0x54226dd  call qword ptr [0xF99FFA0]
0x54226e3  nop
0x54226e4  mov rsi,rax
0x54226e7  test rax,rax
0x54226ea  je 0x54234A6

## Phase 3 — 0x54226f0..0x54227b5 (46 instructions) [I]
Allocation success path [I]. rax=[rbp+0x220] (saved context rsi); new buffer goes at [rax+0x28], rbx (len) at [rax+0x38], rdi (cap) at [rax+0x40]; inc rbx; call 0xEEC6EC0 with rcx=new buffer, rdx=r13 (source), r8=rbx (len) — a copy of the string data [I]. rdi restored from [rbp+0x210]. Then the big struct at rsi is filled: lea rax,[rbp+0xC8]; movups [rsi+0x48] = [rbp+0xC8] (16 bytes); [rbp+0xD8]->[rsi+0x58]; [rbp+0xE0]->[rsi+0x60]; movups [rsi+0x68] = [rbp+0xE8] (16 bytes); zero [rbp+0xE8] via [rax+0x20]; [rbp-0x48]=rsi; byte [rbp+0x23F]=0 [I]. Finally eax=[rbp+0x128] -> [rsp+0x28], lea rax,[rbp+0x30] -> [rsp+0x20], lea rdx,[rbp+0x110], lea r9,[rbp-0x50], rcx=[rbp+0x70], r8=[rbp+0x130], call 0x18718D0 (texgroup registration/init with these args) [I].

0x54226f0  mov rax,rsi
0x54226f3  add rsi,0x27
0x54226f7  and rsi,0xFFFFFFFFFFFFFFE0
0x54226fb  mov [rsi-8],rax
0x54226ff  jmp short 0x542271B
0x5422701  lea r12,[rdi+1]
0x5422705  mov rdx,r12
0x5422708  call qword ptr [0xF99FFA0]
0x542270e  nop
0x542270f  mov rsi,rax
0x5422712  test rax,rax
0x5422715  je 0x54234B4
0x542271b  mov rax,[rbp+0x220]
0x5422722  mov [rax+0x28],rsi
0x5422726  mov [rax+0x38],rbx
0x542272a  mov [rax+0x40],rdi
0x542272e  inc rbx
0x5422731  mov rcx,rsi
0x5422734  mov rsi,rax
0x5422737  mov rdx,r13
0x542273a  mov r8,rbx
0x542273d  call 0xEEC6EC0
0x5422742  mov rdi,[rbp+0x210]
0x5422749  lea rax,[rbp+0xC8]
0x5422750  movups xmm0,[rax]
0x5422753  movups [rsi+0x48],xmm0
0x5422757  mov ecx,[rbp+0xD8]
0x542275d  mov [rsi+0x58],ecx
0x5422760  mov ecx,[rbp+0xE0]
0x5422766  mov [rsi+0x60],ecx
0x5422769  movups xmm0,[rbp+0xE8]
0x5422770  movups [rsi+0x68],xmm0
0x5422774  xorps xmm0,xmm0
0x5422777  movups [rax+0x20],xmm0
0x542277b  mov [rbp-0x48],rsi
0x542277f  mov byte ptr [rbp+0x23F],0
0x5422786  mov eax,[rbp+0x128]
0x542278c  mov [rsp+0x28],eax
0x5422790  lea rax,[rbp+0x30]
0x5422794  mov [rsp+0x20],rax
0x5422799  lea rdx,[rbp+0x110]
0x54227a0  lea r9,[rbp-0x50]
0x54227a4  mov rcx,[rbp+0x70]
0x54227a8  mov r8,[rbp+0x130]
0x54227af  call 0x18718D0
0x54227b4  nop

## Phase 4 — 0x54227b5..0x5422843 (35 instructions) [I]
cmp r14,0x10 then release the old buffer r14=[rbp+0x200]: size>=0x10 path adjusts [r15-8], small path calls 0xE935700 to free; on failure jump 0x542357D [I]. Reset [rbp+0xB8]=0, [rbp+0xC0]=0xF, byte [rbp+0xA8]=0 [I]. If rdi!=0: locked dec [rdi+8]; if it hit zero, rax=[rdi], rax=[rax], call [0xF99FFA0]; then locked dec [rdi+0xC]; if zero, rax=[rdi], rax=[rax+8], call [0xF99FFA0] (two-stage object+vtable free) [I]. Finally reload [rbp+0x88] into rcx [I].

0x54227b5  cmp r14,0x10
0x54227b9  mov rsi,[rbp+0x200]
0x54227c0  jb short 0x54227F6
0x54227c2  lea rdx,[r14+1]
0x54227c6  cmp rdx,0x1000
0x54227cd  jb short 0x54227EE
0x54227cf  mov rax,[r15-8]
0x54227d3  add r15,0xFFFFFFFFFFFFFFF8
0x54227d7  sub r15,rax
0x54227da  cmp r15,0x20
0x54227de  jae 0x542357D
0x54227e4  add r14,0x28
0x54227e8  mov rdx,r14
0x54227eb  mov r15,rax
0x54227ee  mov rcx,r15
0x54227f1  call 0xE935700
0x54227f6  mov qword ptr [rbp+0xB8],0
0x5422801  mov qword ptr [rbp+0xC0],0xF
0x542280c  mov byte ptr [rbp+0xA8],0
0x5422813  test rdi,rdi
0x5422816  je short 0x5422843
0x5422818  lock dec dword ptr [rdi+8]
0x542281c  jne short 0x5422843
0x542281e  mov rax,[rdi]
0x5422821  mov rax,[rax]
0x5422824  mov rcx,rdi
0x5422827  call qword ptr [0xF99FFA0]
0x542282d  lock dec dword ptr [rdi+0xC]
0x5422831  jne short 0x5422843
0x5422833  mov rax,[rdi]
0x5422836  mov rax,[rax+8]
0x542283a  mov rcx,rdi
0x542283d  call qword ptr [0xF99FFA0]
0x5422843  mov rcx,[rbp+0x88]

## Phase 5 — 0x542284a..0x5422921 (43 instructions) [I]
Release [rbp+0x88] the same way (locked dec [rcx+0xC], free on zero via call [0xF99FFA0]) [I]. Init stack object: lea rcx,[rbp+0x140], call 0x5424000 [I]. Zero [rbp+0x140] (movaps); if rsi: [rbp+0x140]=[rbp+0x208], [rbp+0x148]=rsi, locked inc [rsi+0xC] [I]. eax=[rbp+0x1C0]->[rbp+0x150]; zero [rbp+0x158] and [rbp+0x168]; r12=[rbp+0x1D8]; cmp qword [rbp+0x1E0],0x10; rbx=[rbp+0x1C8] if >=0x10 else &[rbp+0x1C8] (lea) [I]; r12<0 jumps to 0x542355E [I]. rsi=[rbp+0x228]; if r12<=0xF: [rbp+0x168]=r12, [rbp+0x170]=0xF, movups [rbp+0x158]=[rbx], jump 0x54229AE; else slow path: rdx=r12|0xF, size=max(0x16,rdx) [I].

0x542284a  test rcx,rcx
0x542284d  je short 0x5422862
0x542284f  lock dec dword ptr [rcx+0xC]
0x5422853  jne short 0x5422862
0x5422855  mov rax,[rcx]
0x5422858  mov rax,[rax+8]
0x542285c  call qword ptr [0xF99FFA0]
0x5422862  lea rcx,[rbp+0x140]
0x5422869  call 0x5424000
0x542286e  mov r14,[rbp+0x110]
0x5422875  xorps xmm0,xmm0
0x5422878  movaps [rbp+0x140],xmm0
0x542287f  test rsi,rsi
0x5422882  je short 0x542289D
0x5422884  mov rax,[rbp+0x208]
0x542288b  mov [rbp+0x140],rax
0x5422892  mov [rbp+0x148],rsi
0x5422899  lock inc dword ptr [rsi+0xC]
0x542289d  mov eax,[rbp+0x1C0]
0x54228a3  mov [rbp+0x150],eax
0x54228a9  movups [rbp+0x158],xmm0
0x54228b0  movups [rbp+0x168],xmm0
0x54228b7  mov r12,[rbp+0x1D8]
0x54228be  cmp qword ptr [rbp+0x1E0],0x10
0x54228c6  lea rbx,[rbp+0x1C8]
0x54228cd  jb short 0x54228D6
0x54228cf  mov rbx,[rbp+0x1C8]
0x54228d6  test r12,r12
0x54228d9  mov rsi,[rbp+0x228]
0x54228e0  js 0x542355E
0x54228e6  lea r15,[rbp+0x158]
0x54228ed  cmp r12,0xF
0x54228f1  ja short 0x5422911
0x54228f3  mov [rbp+0x168],r12
0x54228fa  mov qword ptr [rbp+0x170],0xF
0x5422905  movups xmm0,[rbx]
0x5422908  movups [r15],xmm0
0x542290c  jmp 0x54229AE
0x5422911  mov rdx,r12
0x5422914  or rdx,0xF
0x5422918  cmp rdx,0x17
0x542291c  mov edi,0x16

## Phase 6 — 0x5422921..0x54229e8 (45 instructions) [I]
cmovae rdi,rdx (final size) [I]. Allocation: rdx<0xFFF -> alloc rdi+0x28 else rdi+1 via call [0xF99FFA0], failures 0x54234C4/0x54234D2 [I]. Success: [rbp+0x158]=rsi (buffer), [rbp+0x168]=r12 (len), [rbp+0x170]=rdi (cap), inc r12; call 0xEEC6EC0 (rcx=rsi, rdx=rbx=source, r8=r12=len) — string copy [I]. rsi=[rbp+0x228]; movups [rbp+0x178] = [rbp+0x1E8] (16 bytes); eax=[rbp+0x1F8]->[rbp+0x188]; zero [rbp+0x190]; rax=[rsi+0x1C0]; if nonzero locked inc [rax+8]; rax=[rsi+0x1C0] again; jmp short 0x54229F7 — slice exit [I].

0x5422921  cmovae rdi,rdx
0x5422925  mov rcx,[0x1233E1A8]
0x542292c  mov rax,[rcx]
0x542292f  mov rax,[rax+8]
0x5422933  cmp rdx,0xFFF
0x542293a  jb short 0x5422967
0x542293c  lea r13,[rdi+0x28]
0x5422940  mov rdx,r13
0x5422943  call qword ptr [0xF99FFA0]
0x5422949  nop
0x542294a  mov rsi,rax
0x542294d  test rax,rax
0x5422950  je 0x54234C4
0x5422956  mov rax,rsi
0x5422959  add rsi,0x27
0x542295d  and rsi,0xFFFFFFFFFFFFFFE0
0x5422961  mov [rsi-8],rax
0x5422965  jmp short 0x5422981
0x5422967  lea r13,[rdi+1]
0x542296b  mov rdx,r13
0x542296e  call qword ptr [0xF99FFA0]
0x5422974  nop
0x5422975  mov rsi,rax
0x5422978  test rax,rax
0x542297b  je 0x54234D2
0x5422981  mov [rbp+0x158],rsi
0x5422988  mov [rbp+0x168],r12
0x542298f  mov [rbp+0x170],rdi
0x5422996  inc r12
0x5422999  mov rcx,rsi
0x542299c  mov rdx,rbx
0x542299f  mov r8,r12
0x54229a2  call 0xEEC6EC0
0x54229a7  mov rsi,[rbp+0x228]
0x54229ae  lea rax,[rbp+0x1E8]
0x54229b5  movups xmm0,[rax]
0x54229b8  movups [rbp+0x178],xmm0
0x54229bf  mov eax,[rbp+0x1F8]
0x54229c5  mov [rbp+0x188],eax
0x54229cb  xorps xmm0,xmm0
0x54229ce  movaps [rbp+0x190],xmm0
0x54229d5  mov rax,[rsi+0x1C0]
0x54229dc  test rax,rax
0x54229df  mov rdx,[rbp+0x218]
0x54229e6  je short 0x54229F5
0x54229e8  lock inc dword ptr [rax+8]

## Phase 7 — 0x54229ec..0x54229f3 (2 instructions) [I]
rax=[rsi+0x1C0] again, then jmp short 0x54229F7 leaves the slice [I].

0x54229ec  mov rax,[rsi+0x1C0]
0x54229f3  jmp short 0x54229F7

## Field map — every [reg+off] field stored or loaded in the slice
One row per distinct offset; direction LOAD = memory read, STORE = memory write, R/W = locked atomic read-modify-write; size from the instruction; '-' means no meaning is shown by the code. LEA computations are not loads/stores and are not listed [I].

| offset | size | direction | sites (verbatim `0xRVA  instr` lines) | meaning |
|--------|------|-----------|---------------------------------------|---------|
| -0x50 | 8 | STORE | `0x54225c4  mov [rbp-0x50],rax` | - |
| -0x48 | 8 | STORE | `0x54225b5  mov qword ptr [rbp-0x48],0`<br>`0x542277b  mov [rbp-0x48],rsi` | - |
| -0x8 | 8 | LOAD, STORE | `0x54226fb  mov [rsi-8],rax`<br>`0x54227cf  mov rax,[r15-8]`<br>`0x5422961  mov [rsi-8],rax` | - |
| +0x0 | 16/8 | LOAD, STORE | `0x54225cf  mov rax,[rcx]`<br>`0x54225f1  movups [rsi],xmm0`<br>`0x5422607  mov [rsi],rcx`<br>`0x5422690  movups xmm0,[r13]`<br>`0x5422695  movups [rax],xmm0`<br>`0x54226c6  mov rax,[rcx]`<br>`0x5422750  movups xmm0,[rax]`<br>`0x542281e  mov rax,[rdi]`<br>`0x5422821  mov rax,[rax]`<br>`0x5422833  mov rax,[rdi]`<br>`0x5422905  movups xmm0,[rbx]`<br>`0x5422908  movups [r15],xmm0`<br>`0x542292c  mov rax,[rcx]`<br>`0x542292f  mov rax,[rax]`<br>`0x54229b5  movups xmm0,[rax]` | - |
| +0x8 | 8/4 | LOAD, R/W, STORE | `0x5422591  lock inc dword ptr [rax+8]`<br>`0x54225d2  mov rax,[rax+8]`<br>`0x542260a  mov [rsi+8],rax`<br>`0x5422622  lock inc dword ptr [rax+8]`<br>`0x54226c9  mov rax,[rax+8]`<br>`0x5422818  lock dec dword ptr [rdi+8]`<br>`0x5422836  mov rax,[rax+8]`<br>`0x5422858  mov rax,[rax+8]`<br>`0x54229e8  lock inc dword ptr [rax+8]` | - |
| +0xc | 4 | R/W | `0x542260e  lock inc dword ptr [rax+0xC]`<br>`0x542282d  lock dec dword ptr [rdi+0xC]`<br>`0x542284f  lock dec dword ptr [rcx+0xC]`<br>`0x5422899  lock inc dword ptr [rsi+0xC]` | - |
| +0x10 | 16/8 | STORE | `0x5422612  movups [rsi+0x10],xmm0`<br>`0x5422638  mov [rsi+0x10],rax` | - |
| +0x18 | 8 | STORE | `0x542263c  mov [rsi+0x18],rdi` | - |
| +0x20 | 16/8/4 | STORE | `0x5422646  mov [rsi+0x20],eax`<br>`0x5422777  movups [rax+0x20],xmm0`<br>`0x5422794  mov [rsp+0x20],rax` | - |
| +0x28 | 16/8/4 | STORE | `0x5422649  movups [rsi+0x28],xmm0`<br>`0x5422722  mov [rax+0x28],rsi`<br>`0x542278c  mov [rsp+0x28],eax` | - |
| +0x38 | 16/8 | STORE | `0x542264d  movups [rsi+0x38],xmm0`<br>`0x5422684  mov [rsi+0x38],rbx`<br>`0x5422726  mov [rax+0x38],rbx` | - |
| +0x40 | 8 | STORE | `0x5422688  mov qword ptr [rsi+0x40],0xF`<br>`0x542272a  mov [rax+0x40],rdi` | - |
| +0x48 | 16 | STORE | `0x5422753  movups [rsi+0x48],xmm0` | - |
| +0x58 | 4 | STORE | `0x542275d  mov [rsi+0x58],ecx` | - |
| +0x60 | 4 | STORE | `0x5422766  mov [rsi+0x60],ecx` | - |
| +0x68 | 16 | STORE | `0x5422770  movups [rsi+0x68],xmm0` | - |
| +0x70 | 8 | LOAD | `0x54227a4  mov rcx,[rbp+0x70]` | - |
| +0x80 | 8 | LOAD | `0x5422600  mov rcx,[rbp+0x80]` | - |
| +0x88 | 8 | LOAD | `0x54225f4  mov rax,[rbp+0x88]`<br>`0x5422843  mov rcx,[rbp+0x88]` | - |
| +0x90 | 8 | LOAD | `0x5422631  mov rax,[rbp+0x90]` | - |
| +0x98 | 8 | LOAD | `0x5422616  mov rax,[rbp+0x98]`<br>`0x5422626  mov rdi,[rbp+0x98]` | - |
| +0xa0 | 4 | LOAD | `0x5422640  mov eax,[rbp+0xA0]` | - |
| +0xa8 | 8/1 | LOAD, STORE | `0x5422651  mov r15,[rbp+0xA8]`<br>`0x542280c  mov byte ptr [rbp+0xA8],0` | - |
| +0xb8 | 8 | LOAD, STORE | `0x5422658  mov rbx,[rbp+0xB8]`<br>`0x54227f6  mov qword ptr [rbp+0xB8],0` | - |
| +0xc0 | 8 | LOAD, STORE | `0x542265f  mov r14,[rbp+0xC0]`<br>`0x5422801  mov qword ptr [rbp+0xC0],0xF` | - |
| +0xd8 | 4 | LOAD | `0x5422757  mov ecx,[rbp+0xD8]` | - |
| +0xe0 | 4 | LOAD | `0x5422760  mov ecx,[rbp+0xE0]` | - |
| +0xe8 | 16/8 | LOAD, STORE | `0x54225a7  mov [rbp+0xE8],rcx`<br>`0x5422769  movups xmm0,[rbp+0xE8]` | - |
| +0xf0 | 8 | STORE | `0x54225ae  mov [rbp+0xF0],rax` | - |
| +0x110 | 8 | LOAD | `0x542286e  mov r14,[rbp+0x110]` | - |
| +0x128 | 4 | LOAD | `0x5422786  mov eax,[rbp+0x128]` | - |
| +0x130 | 8 | LOAD | `0x54227a8  mov r8,[rbp+0x130]` | - |
| +0x140 | 16/8 | STORE | `0x5422878  movaps [rbp+0x140],xmm0`<br>`0x542288b  mov [rbp+0x140],rax` | - |
| +0x148 | 8 | STORE | `0x5422892  mov [rbp+0x148],rsi` | - |
| +0x150 | 4 | STORE | `0x54228a3  mov [rbp+0x150],eax` | - |
| +0x158 | 16/8 | STORE | `0x54228a9  movups [rbp+0x158],xmm0`<br>`0x5422981  mov [rbp+0x158],rsi` | - |
| +0x168 | 16/8 | STORE | `0x54228b0  movups [rbp+0x168],xmm0`<br>`0x54228f3  mov [rbp+0x168],r12`<br>`0x5422988  mov [rbp+0x168],r12` | - |
| +0x170 | 8 | STORE | `0x54228fa  mov qword ptr [rbp+0x170],0xF`<br>`0x542298f  mov [rbp+0x170],rdi` | - |
| +0x178 | 16 | STORE | `0x54229b8  movups [rbp+0x178],xmm0` | - |
| +0x188 | 4 | STORE | `0x54229c5  mov [rbp+0x188],eax` | - |
| +0x190 | 16 | STORE | `0x54229ce  movaps [rbp+0x190],xmm0` | - |
| +0x1c0 | 8/4 | LOAD | `0x542289d  mov eax,[rbp+0x1C0]`<br>`0x54229d5  mov rax,[rsi+0x1C0]`<br>`0x54229ec  mov rax,[rsi+0x1C0]` | - |
| +0x1c8 | 8 | LOAD | `0x54228cf  mov rbx,[rbp+0x1C8]` | - |
| +0x1d8 | 8 | LOAD | `0x54228b7  mov r12,[rbp+0x1D8]` | - |
| +0x1e0 | 8 | LOAD | `0x54228be  cmp qword ptr [rbp+0x1E0],0x10` | - |
| +0x1f8 | 4 | LOAD | `0x54229bf  mov eax,[rbp+0x1F8]` | - |
| +0x200 | 8 | LOAD | `0x54227b9  mov rsi,[rbp+0x200]` | - |
| +0x208 | 8 | LOAD | `0x5422884  mov rax,[rbp+0x208]` | - |
| +0x210 | 8 | LOAD, STORE | `0x54226a4  mov [rbp+0x210],rdi`<br>`0x5422742  mov rdi,[rbp+0x210]` | - |
| +0x218 | 8 | LOAD | `0x54229df  mov rdx,[rbp+0x218]` | - |
| +0x220 | 8 | LOAD, STORE | `0x542269d  mov [rbp+0x220],rsi`<br>`0x542271b  mov rax,[rbp+0x220]` | - |
| +0x228 | 8 | LOAD | `0x54228d9  mov rsi,[rbp+0x228]`<br>`0x54229a7  mov rsi,[rbp+0x228]` | - |
| +0x23f | 1 | STORE | `0x542277f  mov byte ptr [rbp+0x23F],0` | - |
| +0x268 | 8 | LOAD | `0x54225a0  mov rcx,[rsi+0x268]` | - |
| +0x270 | 8 | LOAD | `0x5422598  mov rax,[rsi+0x270]` | - |
