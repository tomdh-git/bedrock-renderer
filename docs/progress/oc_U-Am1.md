## NEXT
DONE — 0x4e1a0a0..0x4e1a527 fully covered: 12 phases (all 250 instructions verbatim), 59-row [reg+off] field store/load table, verify_oc clean.

## Unit U-Am1 — atlas_meta_parse 0x4e1a0a0..0x4e1a527 (chunk 1 of 7)

Source listing: docs/progress/_part_Am1.txt — 250 instructions from 0x4e1a0a0 to 0x4e1a527 (slice ends at `cmp r12,r13`; continuation is chunk 2). Static analysis only; RVAs are image-base RVAs of Minecraft.Windows.exe 1.26.62.01. Every phase and field claim is [V] (seen in the provided listing) unless tagged [I]/[?]. The listing is the ground truth for sizes, offsets and verbatim instruction text.

### Phase 1 — 0x4e1a0a0..0x4e1a0fe
0x4e1a0a0..0x4e1a0fe: Prologue pushes callee-saved rbp/r15/r14/r13/r12/rsi/rdi/rbx [V] and builds a 0x418-byte frame with rbp=rsp+0x80 [V], spilling XMM7 at [rbp+0x380] and XMM6 at [rbp+0x370] [V]. It stores incoming r9 at [rbp+0x338] and r8 at [rbp+0x350] [V], copies rdx->r15 and rcx->rsi [V], then reads global pointer [0x1233E1B0] [V], follows [rax+0x10] [V], and calls through IAT slot [0xF99FFA0] with dl=0x53 [V]; eax is saved into r14d [V].
0x4e1a0a0  push rbp
0x4e1a0a1  push r15
0x4e1a0a3  push r14
0x4e1a0a5  push r13
0x4e1a0a7  push r12
0x4e1a0a9  push rsi
0x4e1a0aa  push rdi
0x4e1a0ab  push rbx
0x4e1a0ac  sub rsp,0x418
0x4e1a0b3  lea rbp,[rsp+0x80]
0x4e1a0bb  movaps [rbp+0x380],xmm7
0x4e1a0c2  movaps [rbp+0x370],xmm6
0x4e1a0c9  mov qword ptr [rbp+0x368],0xFFFFFFFFFFFFFFFE
0x4e1a0d4  mov [rbp+0x338],r9
0x4e1a0db  mov [rbp+0x350],r8
0x4e1a0e2  mov r15,rdx
0x4e1a0e5  mov rsi,rcx
0x4e1a0e8  mov rcx,[0x1233E1B0]
0x4e1a0ef  mov rax,[rcx]
0x4e1a0f2  mov rax,[rax+0x10]
0x4e1a0f6  mov dl,0x53
0x4e1a0f8  call qword ptr [0xF99FFA0]
0x4e1a0fe  nop

### Phase 2 — 0x4e1a0ff..0x4e1a180
0x4e1a0ff..0x4e1a180: Captures eax into r14d [V], then zero-initializes four frame-local triplets at [rbp+0x130]..[rbp+0x1A8] — each is {16 bytes zeroed by movaps, qword=0, qword=0xF} (empty pointer/size/capacity shape) [V] — and saves rsi at [rbp+0x358] [V] before computing rbx=rsi+0x60 [V].
0x4e1a0ff  mov r14d,eax
0x4e1a102  xorps xmm6,xmm6
0x4e1a105  movaps [rbp+0x130],xmm6
0x4e1a10c  mov qword ptr [rbp+0x140],0
0x4e1a117  mov qword ptr [rbp+0x148],0xF
0x4e1a122  movaps [rbp+0x150],xmm6
0x4e1a129  mov qword ptr [rbp+0x160],0
0x4e1a134  mov qword ptr [rbp+0x168],0xF
0x4e1a13f  movaps [rbp+0x170],xmm6
0x4e1a146  mov qword ptr [rbp+0x180],0
0x4e1a151  mov qword ptr [rbp+0x188],0xF
0x4e1a15c  movaps [rbp+0x190],xmm6
0x4e1a163  mov qword ptr [rbp+0x1A0],0
0x4e1a16e  mov qword ptr [rbp+0x1A8],0xF
0x4e1a179  mov [rbp+0x358],rsi
0x4e1a180  lea rbx,[rsi+0x60]

### Phase 3 — 0x4e1a184..0x4e1a1c9
0x4e1a184..0x4e1a1c9: Clears [rbp+0x1B0] (16 bytes) and byte [rbp+0x1BF] [V], calls helper 0x282A8E0 with rsi=&[rbp+0x130] then 0x15B7F0 with rcx=rsi [V], loads the address of global 0x128C4FD0 into rdi [V], calls 0xE943178 [V], atomically increments global qword [0x128C5030] [V], and calls 0xE94319C [V].
0x4e1a184  movaps [rbp+0x1B0],xmm6
0x4e1a18b  mov dword ptr [rbp+0x1BF],0
0x4e1a195  lea rsi,[rbp+0x130]
0x4e1a19c  mov rcx,rbx
0x4e1a19f  mov rdx,rsi
0x4e1a1a2  call 0x282A8E0
0x4e1a1a7  mov rcx,rsi
0x4e1a1aa  call 0x15B7F0
0x4e1a1af  lea rdi,[0x128C4FD0]
0x4e1a1b6  mov rcx,rdi
0x4e1a1b9  call 0xE943178
0x4e1a1be  lock inc qword ptr [0x128C5030]
0x4e1a1c6  mov rcx,rdi
0x4e1a1c9  call 0xE94319C

### Phase 4 — 0x4e1a1ce..0x4e1a20f
0x4e1a1ce..0x4e1a20f: Loads global [0x128C5038] [V]; if it is non-zero and byte [rax]==1 it stores rbx at [rbp+0x2C8] [V] and, when rcx=[0x128C5040] is non-null, lock-increments the dword at [rcx+8] and jumps to 0x4E1A447 [V]; otherwise execution continues at 0x4E1A214 to initialize locals [V].
0x4e1a1ce  mov rax,[0x128C5038]
0x4e1a1d5  test rax,rax
0x4e1a1d8  je short 0x4E1A214
0x4e1a1da  cmp byte ptr [rax],1
0x4e1a1dd  jne short 0x4E1A214
0x4e1a1df  mov [rbp+0x2C8],rbx
0x4e1a1e6  mov rcx,[0x128C5040]
0x4e1a1ed  test rcx,rcx
0x4e1a1f0  mov rbx,[rbp+0x338]
0x4e1a1f7  je 0x4E1A445
0x4e1a1fd  lock inc dword ptr [rcx+8]
0x4e1a201  mov rax,[0x128C5038]
0x4e1a208  mov rsi,[0x128C5040]
0x4e1a20f  jmp 0x4E1A447

### Phase 5 — 0x4e1a214..0x4e1a27a
0x4e1a214..0x4e1a27a: Fallback path: clears [rbp+0x108], byte [rbp+0x110], [rbp+0x118] and [rbp+0x128] [V], calls 0x3B2020 with rcx=&global 0x128C4FD0 [V], reloads rbx=[rbp+0x338] [V], zeroes the 128-byte object at r15 ([r15]..[r15+0x70]) with eight movups stores [V], and clears [rbp+0x118] again [V].
0x4e1a214  mov qword ptr [rbp+0x108],0
0x4e1a21f  mov byte ptr [rbp+0x110],0
0x4e1a226  movups [rbp+0x118],xmm6
0x4e1a22d  mov qword ptr [rbp+0x128],0
0x4e1a238  lea rcx,[0x128C4FD0]
0x4e1a23f  call 0x3B2020
0x4e1a244  xor esi,esi
0x4e1a246  mov rbx,[rbp+0x338]
0x4e1a24d  xorps xmm0,xmm0
0x4e1a250  movups [r15+0x70],xmm0
0x4e1a255  movups [r15+0x60],xmm0
0x4e1a25a  movups [r15+0x50],xmm0
0x4e1a25f  movups [r15+0x40],xmm0
0x4e1a264  movups [r15+0x30],xmm0
0x4e1a269  movups [r15+0x20],xmm0
0x4e1a26e  movups [r15+0x10],xmm0
0x4e1a273  movups [r15],xmm0
0x4e1a277  xorps xmm0,xmm0
0x4e1a27a  movups [rbp+0x118],xmm0

### Phase 6 — 0x4e1a281..0x4e1a2f3
0x4e1a281..0x4e1a2f3: Release sequence: for object rsi it lock-decrements the dword at [rsi+8] and, only when it reaches zero, calls the [rax] and [rax+8] entry points through IAT slot [0xF99FFA0] and lock-decrements [rsi+0xC] [V]; the same sequence repeats for the object loaded from [rbp+0x120], finishing with `cmp byte ptr [rbp+0x110],1` [V].
0x4e1a281  test rsi,rsi
0x4e1a284  je short 0x4E1A2F3
0x4e1a286  lock dec dword ptr [rsi+8]
0x4e1a28a  jne short 0x4E1A2B1
0x4e1a28c  mov rax,[rsi]
0x4e1a28f  mov rax,[rax]
0x4e1a292  mov rcx,rsi
0x4e1a295  call qword ptr [0xF99FFA0]
0x4e1a29b  lock dec dword ptr [rsi+0xC]
0x4e1a29f  jne short 0x4E1A2B1
0x4e1a2a1  mov rax,[rsi]
0x4e1a2a4  mov rax,[rax+8]
0x4e1a2a8  mov rcx,rsi
0x4e1a2ab  call qword ptr [0xF99FFA0]
0x4e1a2b1  mov rsi,[rbp+0x120]
0x4e1a2b8  mov qword ptr [rbp+0x128],0
0x4e1a2c3  test rsi,rsi
0x4e1a2c6  je short 0x4E1A2F3
0x4e1a2c8  lock dec dword ptr [rsi+8]
0x4e1a2cc  jne short 0x4E1A2F3
0x4e1a2ce  mov rax,[rsi]
0x4e1a2d1  mov rax,[rax]
0x4e1a2d4  mov rcx,rsi
0x4e1a2d7  call qword ptr [0xF99FFA0]
0x4e1a2dd  lock dec dword ptr [rsi+0xC]
0x4e1a2e1  jne short 0x4E1A2F3
0x4e1a2e3  mov rax,[rsi]
0x4e1a2e6  mov rax,[rax+8]
0x4e1a2ea  mov rcx,rsi
0x4e1a2ed  call qword ptr [0xF99FFA0]
0x4e1a2f3  cmp byte ptr [rbp+0x110],1

### Phase 7 — 0x4e1a2fa..0x4e1a31f
0x4e1a2fa..0x4e1a31f: If byte [rbp+0x110]==1 it calls 0x3B2020 with rcx=[rbp+0x108] and falls through at 0x4E1A308 otherwise [V]; unconditionally it reloads the chain [0x1233E1B0]->[rax+0x10] [V], moves saved r14d into edx [V], and calls through IAT slot [0xF99FFA0] [V].
0x4e1a2fa  jne short 0x4E1A308
0x4e1a2fc  mov rcx,[rbp+0x108]
0x4e1a303  call 0x3B2020
0x4e1a308  mov rcx,[0x1233E1B0]
0x4e1a30f  mov rax,[rcx]
0x4e1a312  mov rax,[rax+0x10]
0x4e1a316  mov edx,r14d
0x4e1a319  call qword ptr [0xF99FFA0]
0x4e1a31f  nop

### Phase 8 — 0x4e1a320..0x4e1a367
0x4e1a320..0x4e1a367: Loads rsi=[rbp+0x400] [V] and unlinks an intrusive node: if [rbx+0x38] is non-null and not self-referential it loads [rcx] and [rax+0x20] then calls through IAT slot [0xF99FFA0], and stores 0 at [rbx+0x38] [V]; it repeats the same test-and-null sequence for [rsi+0x38] [V].
0x4e1a320  mov rsi,[rbp+0x400]
0x4e1a327  mov rcx,[rbx+0x38]
0x4e1a32b  test rcx,rcx
0x4e1a32e  je short 0x4E1A34B
0x4e1a330  cmp rcx,rbx
0x4e1a333  setne dl
0x4e1a336  mov rax,[rcx]
0x4e1a339  mov rax,[rax+0x20]
0x4e1a33d  call qword ptr [0xF99FFA0]
0x4e1a343  mov qword ptr [rbx+0x38],0
0x4e1a34b  mov rcx,[rsi+0x38]
0x4e1a34f  test rcx,rcx
0x4e1a352  je short 0x4E1A36F
0x4e1a354  cmp rcx,rsi
0x4e1a357  setne dl
0x4e1a35a  mov rax,[rcx]
0x4e1a35d  mov rax,[rax+0x20]
0x4e1a361  call qword ptr [0xF99FFA0]
0x4e1a367  mov qword ptr [rsi+0x38],0

### Phase 9 — 0x4e1a36f..0x4e1a3df
0x4e1a36f..0x4e1a3df: Runs the release sequence for the objects referenced at [rbp+0x408], [rbp+0x420] and [rbp+0x428]: load object pointer, move [rax+8] into rsi, skip when null, otherwise lock-decrement [rsi+8] and at zero call [rax] and [rax+8] through IAT slot [0xF99FFA0] then lock-decrement [rsi+0xC] [V].
0x4e1a36f  mov rax,[rbp+0x408]
0x4e1a376  mov rsi,[rax+8]
0x4e1a37a  test rsi,rsi
0x4e1a37d  je short 0x4E1A3AA
0x4e1a37f  lock dec dword ptr [rsi+8]
0x4e1a383  jne short 0x4E1A3AA
0x4e1a385  mov rax,[rsi]
0x4e1a388  mov rax,[rax]
0x4e1a38b  mov rcx,rsi
0x4e1a38e  call qword ptr [0xF99FFA0]
0x4e1a394  lock dec dword ptr [rsi+0xC]
0x4e1a398  jne short 0x4E1A3AA
0x4e1a39a  mov rax,[rsi]
0x4e1a39d  mov rax,[rax+8]
0x4e1a3a1  mov rcx,rsi
0x4e1a3a4  call qword ptr [0xF99FFA0]
0x4e1a3aa  mov rax,[rbp+0x420]
0x4e1a3b1  mov rsi,[rax+8]
0x4e1a3b5  test rsi,rsi
0x4e1a3b8  je short 0x4E1A3E5
0x4e1a3ba  lock dec dword ptr [rsi+8]
0x4e1a3be  jne short 0x4E1A3E5
0x4e1a3c0  mov rax,[rsi]
0x4e1a3c3  mov rax,[rax]
0x4e1a3c6  mov rcx,rsi
0x4e1a3c9  call qword ptr [0xF99FFA0]
0x4e1a3cf  lock dec dword ptr [rsi+0xC]
0x4e1a3d3  jne short 0x4E1A3E5
0x4e1a3d5  mov rax,[rsi]
0x4e1a3d8  mov rax,[rax+8]
0x4e1a3dc  mov rcx,rsi
0x4e1a3df  call qword ptr [0xF99FFA0]

### Phase 10 — 0x4e1a3e5..0x4e1a444
0x4e1a3e5..0x4e1a444: Runs the release sequence once more for the object at [rbp+0x428] [V], then sets rax=r15 [V], restores XMM6 from [rbp+0x370] and XMM7 from [rbp+0x380] [V], tears down the frame (add rsp,0x418), pops rbx/rdi/rsi/r12/r13/r14/r15/rbp and returns [V].
0x4e1a3e5  mov rax,[rbp+0x428]
0x4e1a3ec  mov rsi,[rax+8]
0x4e1a3f0  test rsi,rsi
0x4e1a3f3  je short 0x4E1A420
0x4e1a3f5  lock dec dword ptr [rsi+8]
0x4e1a3f9  jne short 0x4E1A420
0x4e1a3fb  mov rax,[rsi]
0x4e1a3fe  mov rax,[rax]
0x4e1a401  mov rcx,rsi
0x4e1a404  call qword ptr [0xF99FFA0]
0x4e1a40a  lock dec dword ptr [rsi+0xC]
0x4e1a40e  jne short 0x4E1A420
0x4e1a410  mov rax,[rsi]
0x4e1a413  mov rax,[rax+8]
0x4e1a417  mov rcx,rsi
0x4e1a41a  call qword ptr [0xF99FFA0]
0x4e1a420  mov rax,r15
0x4e1a423  movaps xmm6,[rbp+0x370]
0x4e1a42a  movaps xmm7,[rbp+0x380]
0x4e1a431  add rsp,0x418
0x4e1a438  pop rbx
0x4e1a439  pop rdi
0x4e1a43a  pop rsi
0x4e1a43b  pop r12
0x4e1a43d  pop r13
0x4e1a43f  pop r14
0x4e1a441  pop r15
0x4e1a443  pop rbp
0x4e1a444  ret

### Phase 11 — 0x4e1a445..0x4e1a4ab
0x4e1a445..0x4e1a4ab: Alternate target (from 0x4e1a1f7): zeroes esi, loads rcx=[0x128C5048] [V], and stores result locals [rbp+0x108]=rdi, byte [rbp+0x110]=1, [rbp+0x118]=rax, [rbp+0x120]=rsi(=0), [rbp+0x128]=rcx [V]; if rax is non-null with byte [rax]!=0 it stores [rbp+0x2C0]=r15 and [rbp+0x367]=r14b [V], reloads [rbp+0x358] and [rax+0x208] [V], and bails to 0x4E1A54F unless byte [rax]==1 [V].
0x4e1a445  xor esi,esi
0x4e1a447  mov rcx,[0x128C5048]
0x4e1a44e  mov [rbp+0x108],rdi
0x4e1a455  mov byte ptr [rbp+0x110],1
0x4e1a45c  mov [rbp+0x118],rax
0x4e1a463  mov [rbp+0x120],rsi
0x4e1a46a  mov [rbp+0x128],rcx
0x4e1a471  test rax,rax
0x4e1a474  je 0x4E1A24D
0x4e1a47a  cmp byte ptr [rax],0
0x4e1a47d  je 0x4E1A24D
0x4e1a483  mov [rbp+0x2C0],r15
0x4e1a48a  mov [rbp+0x367],r14b
0x4e1a491  mov rax,[rbp+0x358]
0x4e1a498  mov rax,[rax+0x208]
0x4e1a49f  test rax,rax
0x4e1a4a2  je 0x4E1A54F
0x4e1a4a8  cmp byte ptr [rax],1
0x4e1a4ab  jne 0x4E1A54F

### Phase 12 — 0x4e1a4b1..0x4e1a527
0x4e1a4b1..0x4e1a527: Reloads rax=[rbp+0x358] [V] and iterates entries from [rax+0x100] up to [rax+0x108] (stride 0x40), using [rax+0x218] as rsi [V]; for each entry it loads [rdi+0x28] into rbx and [rdi+0x30] into r15 [V], walks rbx from [rbx] toward [rbx+8] in steps of 0x18 [V], then advances r12 by 0x148 until r12==r13, where the slice ends at `cmp r12,r13` [V].
0x4e1a4b1  mov rax,[rbp+0x358]
0x4e1a4b8  mov rdi,[rax+0x100]
0x4e1a4bf  mov r14,[rax+0x108]
0x4e1a4c6  cmp rdi,r14
0x4e1a4c9  je 0x4E1A54F
0x4e1a4cf  mov rax,[rbp+0x358]
0x4e1a4d6  mov rsi,[rax+0x218]
0x4e1a4dd  jmp short 0x4E1A4E9
0x4e1a4df  nop
0x4e1a4e0  add rdi,0x40
0x4e1a4e4  cmp rdi,r14
0x4e1a4e7  je short 0x4E1A54F
0x4e1a4e9  mov rbx,[rdi+0x28]
0x4e1a4ed  mov r15,[rdi+0x30]
0x4e1a4f1  jmp short 0x4E1A504
0x4e1a4f3  nop [rax+rax]
0x4e1a500  add rbx,0x18
0x4e1a504  cmp rbx,r15
0x4e1a507  je short 0x4E1A4E0
0x4e1a509  mov r12,[rbx]
0x4e1a50c  mov r13,[rbx+8]
0x4e1a510  jmp short 0x4E1A527
0x4e1a512  nop [rax+rax]
0x4e1a520  add r12,0x148
0x4e1a527  cmp r12,r13

## Field table — every [reg+off] store/load in slice 0x4e1a0a0..0x4e1a527

| offset | size | read/store address | verbatim `0xRVA  instr` line(s) | meaning |
|---|---|---|---|---|
| rbp+0x380 | 16 | W [rbp+0x380] @ 0x4e1a0bb; R [rbp+0x380] @ 0x4e1a42a | `0x4e1a0bb  movaps [rbp+0x380],xmm7`<br>`0x4e1a42a  movaps xmm7,[rbp+0x380]` | - |
| rbp+0x370 | 16 | W [rbp+0x370] @ 0x4e1a0c2; R [rbp+0x370] @ 0x4e1a423 | `0x4e1a0c2  movaps [rbp+0x370],xmm6`<br>`0x4e1a423  movaps xmm6,[rbp+0x370]` | - |
| rbp+0x368 | 8 | W [rbp+0x368] @ 0x4e1a0c9 | `0x4e1a0c9  mov qword ptr [rbp+0x368],0xFFFFFFFFFFFFFFFE` | - |
| rbp+0x338 | 8 | W [rbp+0x338] @ 0x4e1a0d4; R [rbp+0x338] @ 0x4e1a1f2; R [rbp+0x338] @ 0x4e1a24f | `0x4e1a0d4  mov [rbp+0x338],r9`<br>`0x4e1a1f2  mov rbx,[rbp+0x338]`<br>`0x4e1a24f  mov rbx,[rbp+0x338]` | - |
| rbp+0x350 | 8 | W [rbp+0x350] @ 0x4e1a0db | `0x4e1a0db  mov [rbp+0x350],r8` | - |
| rbp+0x358 | 8 | W [rbp+0x358] @ 0x4e1a179; R [rbp+0x358] @ 0x4e1a48f; R [rbp+0x358] @ 0x4e1a4ab; R [rbp+0x358] @ 0x4e1a4ce | `0x4e1a179  mov [rbp+0x358],rsi`<br>`0x4e1a48f  mov rax,[rbp+0x358]`<br>`0x4e1a4ab  mov rax,[rbp+0x358]`<br>`0x4e1a4ce  mov rax,[rbp+0x358]` | - |
| rbp+0x130 | 16 | W [rbp+0x130] @ 0x4e1a105 | `0x4e1a105  movaps [rbp+0x130],xmm6` | - |
| rbp+0x140 | 8 | W [rbp+0x140] @ 0x4e1a10c | `0x4e1a10c  mov qword ptr [rbp+0x140],0` | - |
| rbp+0x148 | 8 | W [rbp+0x148] @ 0x4e1a117 | `0x4e1a117  mov qword ptr [rbp+0x148],0xF` | - |
| rbp+0x150 | 16 | W [rbp+0x150] @ 0x4e1a122 | `0x4e1a122  movaps [rbp+0x150],xmm6` | - |
| rbp+0x160 | 8 | W [rbp+0x160] @ 0x4e1a129 | `0x4e1a129  mov qword ptr [rbp+0x160],0` | - |
| rbp+0x168 | 8 | W [rbp+0x168] @ 0x4e1a134 | `0x4e1a134  mov qword ptr [rbp+0x168],0xF` | - |
| rbp+0x170 | 16 | W [rbp+0x170] @ 0x4e1a13f | `0x4e1a13f  movaps [rbp+0x170],xmm6` | - |
| rbp+0x180 | 8 | W [rbp+0x180] @ 0x4e1a146 | `0x4e1a146  mov qword ptr [rbp+0x180],0` | - |
| rbp+0x188 | 8 | W [rbp+0x188] @ 0x4e1a151 | `0x4e1a151  mov qword ptr [rbp+0x188],0xF` | - |
| rbp+0x190 | 16 | W [rbp+0x190] @ 0x4e1a15c | `0x4e1a15c  movaps [rbp+0x190],xmm6` | - |
| rbp+0x1A0 | 8 | W [rbp+0x1A0] @ 0x4e1a163 | `0x4e1a163  mov qword ptr [rbp+0x1A0],0` | - |
| rbp+0x1A8 | 8 | W [rbp+0x1A8] @ 0x4e1a16e | `0x4e1a16e  mov qword ptr [rbp+0x1A8],0xF` | - |
| rbp+0x1B0 | 16 | W [rbp+0x1B0] @ 0x4e1a184 | `0x4e1a184  movaps [rbp+0x1B0],xmm6` | - |
| rbp+0x1BF | 4 | W [rbp+0x1BF] @ 0x4e1a18b | `0x4e1a18b  mov dword ptr [rbp+0x1BF],0` | - |
| rcx+0x08 | 4 | R/W [rcx+0x8] @ 0x4e1a1fd (lock inc dword) | `0x4e1a1fd  lock inc dword ptr [rcx+8]` | - |
| rbp+0x2C8 | 8 | W [rbp+0x2C8] @ 0x4e1a1df | `0x4e1a1df  mov [rbp+0x2C8],rbx` | - |
| rbp+0x108 | 8 | W [rbp+0x108] @ 0x4e1a214; R [rbp+0x108] @ 0x4e1a2fc; W [rbp+0x108] @ 0x4e1a44e | `0x4e1a214  mov qword ptr [rbp+0x108],0`<br>`0x4e1a2fc  mov rcx,[rbp+0x108]`<br>`0x4e1a44e  mov [rbp+0x108],rdi` | - |
| rbp+0x110 | 1 | W [rbp+0x110] @ 0x4e1a21f; R [rbp+0x110] @ 0x4e1a2f3; W [rbp+0x110] @ 0x4e1a455 | `0x4e1a21f  mov byte ptr [rbp+0x110],0`<br>`0x4e1a2f3  cmp byte ptr [rbp+0x110],1`<br>`0x4e1a455  mov byte ptr [rbp+0x110],1` | - |
| rbp+0x118 | 16 | W [rbp+0x118] @ 0x4e1a226; W [rbp+0x118] @ 0x4e1a27a | `0x4e1a226  movups [rbp+0x118],xmm6`<br>`0x4e1a27a  movups [rbp+0x118],xmm0` | - |
| rbp+0x120 | 8 | R [rbp+0x120] @ 0x4e1a2b4; W [rbp+0x120] @ 0x4e1a463 | `0x4e1a2b4  mov rsi,[rbp+0x120]`<br>`0x4e1a463  mov [rbp+0x120],rsi` | - |
| rbp+0x128 | 8 | W [rbp+0x128] @ 0x4e1a22d; W [rbp+0x128] @ 0x4e1a2b8; W [rbp+0x128] @ 0x4e1a46a | `0x4e1a22d  mov qword ptr [rbp+0x128],0`<br>`0x4e1a2b8  mov qword ptr [rbp+0x128],0`<br>`0x4e1a46a  mov [rbp+0x128],rcx` | - |
| rbp+0x400 | 8 | R [rbp+0x400] @ 0x4e1a320 | `0x4e1a320  mov rsi,[rbp+0x400]` | - |
| rbp+0x408 | 8 | R [rbp+0x408] @ 0x4e1a36f | `0x4e1a36f  mov rax,[rbp+0x408]` | - |
| rbp+0x420 | 8 | R [rbp+0x420] @ 0x4e1a3b1 | `0x4e1a3b1  mov rax,[rbp+0x420]` | - |
| rbp+0x428 | 8 | R [rbp+0x428] @ 0x4e1a3ec | `0x4e1a3ec  mov rax,[rbp+0x428]` | - |
| rbp+0x2C0 | 8 | W [rbp+0x2C0] @ 0x4e1a483 | `0x4e1a483  mov [rbp+0x2C0],r15` | - |
| rbp+0x367 | 1 | W [rbp+0x367] @ 0x4e1a48a | `0x4e1a48a  mov [rbp+0x367],r14b` | - |
| r15+0x70 | 16 | W [r15+0x70] @ 0x4e1a250 | `0x4e1a250  movups [r15+0x70],xmm0` | - |
| r15+0x60 | 16 | W [r15+0x60] @ 0x4e1a255 | `0x4e1a255  movups [r15+0x60],xmm0` | - |
| r15+0x50 | 16 | W [r15+0x50] @ 0x4e1a25a | `0x4e1a25a  movups [r15+0x50],xmm0` | - |
| r15+0x40 | 16 | W [r15+0x40] @ 0x4e1a25f | `0x4e1a25f  movups [r15+0x40],xmm0` | - |
| r15+0x30 | 16 | W [r15+0x30] @ 0x4e1a264 | `0x4e1a264  movups [r15+0x30],xmm0` | - |
| r15+0x20 | 16 | W [r15+0x20] @ 0x4e1a269 | `0x4e1a269  movups [r15+0x20],xmm0` | - |
| r15+0x10 | 16 | W [r15+0x10] @ 0x4e1a26e | `0x4e1a26e  movups [r15+0x10],xmm0` | - |
| r15+0x00 | 16 | W [r15] @ 0x4e1a273 | `0x4e1a273  movups [r15],xmm0` | - |
| rsi+0x00 | 8 | R [rsi] @ 0x4e1a290; R [rsi] @ 0x4e1a2a2; R [rsi] @ 0x4e1a386; R [rsi] @ 0x4e1a3c4; R [rsi] @ 0x4e1a402 | `0x4e1a290  mov rax,[rsi]`<br>`0x4e1a2a2  mov rax,[rsi]`<br>`0x4e1a386  mov rax,[rsi]`<br>`0x4e1a3c4  mov rax,[rsi]`<br>`0x4e1a402  mov rax,[rsi]` | - |
| rsi+0x08 | 4 | R/W [rsi+8] @ 0x4e1a286; R/W [rsi+8] @ 0x4e1a2c8; R/W [rsi+8] @ 0x4e1a37a; R/W [rsi+8] @ 0x4e1a3ba; R/W [rsi+8] @ 0x4e1a3f5 (all lock dec dword) | `0x4e1a286  lock dec dword ptr [rsi+8]`<br>`0x4e1a2c8  lock dec dword ptr [rsi+8]`<br>`0x4e1a37a  lock dec dword ptr [rsi+8]`<br>`0x4e1a3ba  lock dec dword ptr [rsi+8]`<br>`0x4e1a3f5  lock dec dword ptr [rsi+8]` | - |
| rsi+0x0C | 4 | R/W [rsi+0xC] @ 0x4e1a289; R/W [rsi+0xC] @ 0x4e1a2d7; R/W [rsi+0xC] @ 0x4e1a38d; R/W [rsi+0xC] @ 0x4e1a3cd; R/W [rsi+0xC] @ 0x4e1a407 (all lock dec dword) | `0x4e1a289  lock dec dword ptr [rsi+0xC]`<br>`0x4e1a2d7  lock dec dword ptr [rsi+0xC]`<br>`0x4e1a38d  lock dec dword ptr [rsi+0xC]`<br>`0x4e1a3cd  lock dec dword ptr [rsi+0xC]`<br>`0x4e1a407  lock dec dword ptr [rsi+0xC]` | - |
| rsi+0x38 | 8 | R [rsi+0x38] @ 0x4e1a34b; W [rsi+0x38] @ 0x4e1a367 | `0x4e1a34b  mov rcx,[rsi+0x38]`<br>`0x4e1a367  mov qword ptr [rsi+0x38],0` | - |
| rax+0x00 | 8 / 1 (cmp byte) | R [rax] @ 0x4e1a293, 0x4e1a389, 0x4e1a3c7 (qword); R [rax] @ 0x4e1a47a and 0x4e1a4a8 (cmp byte ptr [rax]) | `0x4e1a293  mov rax,[rax]`<br>`0x4e1a389  mov rax,[rax]`<br>`0x4e1a3c7  mov rax,[rax]`<br>`0x4e1a47a  cmp byte ptr [rax],0`<br>`0x4e1a4a8  cmp byte ptr [rax],1` | - |
| rcx+0x00 | 8 | R [rcx] @ 0x4e1a0ef, 0x4e1a334, 0x4e1a358 | `0x4e1a0ef  mov rax,[rcx]`<br>`0x4e1a334  mov rax,[rcx]`<br>`0x4e1a358  mov rax,[rcx]` | - |
| rax+0x08 | 8 | R [rax+8] @ 0x4e1a2a5; R [rax+8] @ 0x4e1a2e6; R [rax+8] @ 0x4e1a376; R [rax+8] @ 0x4e1a3b7; R [rax+8] @ 0x4e1a3f2 | `0x4e1a2a5  mov rax,[rax+8]`<br>`0x4e1a2e6  mov rax,[rax+8]`<br>`0x4e1a376  mov rsi,[rax+8]`<br>`0x4e1a3b7  mov rsi,[rax+8]`<br>`0x4e1a3f2  mov rsi,[rax+8]` | - |
| rax+0x10 | 8 | R [rax+0x10] @ 0x4e1a0f2 | `0x4e1a0f2  mov rax,[rax+0x10]` | - |
| rax+0x20 | 8 | R [rax+0x20] @ 0x4e1a337; R [rax+0x20] @ 0x4e1a35b | `0x4e1a337  mov rax,[rax+0x20]`<br>`0x4e1a35b  mov rax,[rax+0x20]` | - |
| rbx+0x38 | 8 | R [rbx+0x38] @ 0x4e1a327; W [rbx+0x38] @ 0x4e1a343 | `0x4e1a327  mov rcx,[rbx+0x38]`<br>`0x4e1a343  mov qword ptr [rbx+0x38],0` | - |
| rbx+0x00 | 8 | R [rbx] @ 0x4e1a509 | `0x4e1a509  mov r12,[rbx]` | - |
| rbx+0x08 | 8 | R [rbx+8] @ 0x4e1a50c | `0x4e1a50c  mov r13,[rbx+8]` | - |
| rdi+0x28 | 8 | R [rdi+0x28] @ 0x4e1a4e9 | `0x4e1a4e9  mov rbx,[rdi+0x28]` | - |
| rdi+0x30 | 8 | R [rdi+0x30] @ 0x4e1a4f0 | `0x4e1a4f0  mov r15,[rdi+0x30]` | - |
| rax+0x100 | 8 | R [rax+0x100] @ 0x4e1a4b8 | `0x4e1a4b8  mov rdi,[rax+0x100]` | - |
| rax+0x108 | 8 | R [rax+0x108] @ 0x4e1a4bf | `0x4e1a4bf  mov r14,[rax+0x108]` | - |
| rax+0x208 | 8 | R [rax+0x208] @ 0x4e1a496 | `0x4e1a496  mov rax,[rax+0x208]` | - |
| rax+0x218 | 8 | R [rax+0x218] @ 0x4e1a4d3 | `0x4e1a4d3  mov rsi,[rax+0x218]` | - |

Notes on accesses not in the table (not [reg+off]): absolute-memory reads/writes [0x1233E1B0] (0x4e1a0e8), [0x128C5030] lock inc (0x4e1a1be), [0x128C5038] (0x4e1a1ce), [0x128C5040] (0x4e1a1e6, 0x4e1a208), [0x128C5048] (0x4e1a447); `lea rbx,[rsi+0x60]` (0x4e1a180) and `lea rcx,[0x128C4FD0]` (0x4e1a238) compute addresses without touching memory; indirect calls through IAT slot [0xF99FFA0]; push/pop stack accesses use implicit [rsp].

No field names or meanings appear in the slice (no strings, no symbolic info), so every meaning cell is '-'.

## TOOL REQUESTS

None.



