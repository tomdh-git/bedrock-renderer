## NEXT
DONE

# Unit U-Lr4: ClientInstance::loadResources slice 0x186f5b5..0x186fae0 (chunk 4 of 6)

Source: docs/progress/_part_Lr4.txt — orchestrator-computed listing of 250 instructions from ClientInstance::loadResources (0x186e6a0), Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only; nothing is executed.
Every verbatim `0xRVA  instr` line in the phases below is copied from _part_Lr4.txt and matches rdis disassembly (verified with tools/sigs/verify_oc.py). Meanings marked '-' are not shown by any instruction or constant in this slice.

## Phases (each <= 40 instructions; every listed instruction of the slice is covered; written and appended in pieces)

### Phase 1: 0x186f5b5..0x186f684 (40 instructions)
First resource load: instance pointer [rbp+0x628] -> rcx; call 0x1870DE0(rcx, &desc [rbp+0xE0] (built before this slice), &slot [rbp+0x4F0], index 0xB). On non-null rdi: call 0x2FE440(rdi), call 0xE935700(rdi, 0x138); zero slot [rbp+0x4F0] (16 B); allocate 0x10 bytes via global [0x1233E1A8] -> [rax+8] and call qword ptr [0xF99FFA0] (edx=0x10); on success store rdi to [rbp+0x4F0], [rbp+0x500]=rax+0x10, [rbp+0x4F8]=rax. Then descriptor 2 built: [rbp+0xF0]=&str 0xF55A7AB, [rbp+0xF8]=0x1B, [rsp+0x20]=rsi spill, &[rbp+0xF0] -> rdx for the next call.
0x186f5b5  lea rdx,[rbp+0xE0]
0x186f5bc  lea rsi,[rbp+0x4F0]
0x186f5c3  mov rcx,[rbp+0x628]
0x186f5ca  mov r8,rsi
0x186f5cd  mov r9d,0xB
0x186f5d3  call 0x1870DE0
0x186f5d8  nop
0x186f5d9  mov rdi,[rbp+0x4F0]
0x186f5e0  test rdi,rdi
0x186f5e3  je short 0x186F5FA
0x186f5e5  mov rcx,rdi
0x186f5e8  call 0x2FE440
0x186f5ed  mov edx,0x138
0x186f5f2  mov rcx,rdi
0x186f5f5  call 0xE935700
0x186f5fa  xorps xmm0,xmm0
0x186f5fd  movaps [rbp+0x4F0],xmm0
0x186f604  mov qword ptr [rbp+0x500],0
0x186f60f  mov rcx,[0x1233E1A8]
0x186f616  mov rax,[rcx]
0x186f619  mov rax,[rax+8]
0x186f61d  mov edx,0x10
0x186f622  call qword ptr [0xF99FFA0]
0x186f628  nop
0x186f629  mov rdi,rax
0x186f62c  test rax,rax
0x186f62f  je 0x1870231
0x186f635  mov [rbp+0x4F0],rdi
0x186f63c  mov rax,rdi
0x186f63f  add rax,0x10
0x186f643  mov [rbp+0x500],rax
0x186f64a  movaps xmm0,[0xF0FBCE0]
0x186f651  movups [rdi],xmm0
0x186f654  mov [rbp+0x4F8],rax
0x186f65b  mov qword ptr [rbp+0x510],0
0x186f666  lea rax,[0xF55A7AB]
0x186f66d  mov [rbp+0xF0],rax
0x186f674  mov qword ptr [rbp+0xF8],0x1B
0x186f67f  mov [rsp+0x20],rsi
0x186f684  lea rdx,[rbp+0xF0]

### Phase 2: 0x186f68b..0x186f76d (40 instructions)
Second resource load: call 0x1870DE0(instance [rbp+0x628] -> rcx, &desc [rbp+0xF0] -> rdx, &slot [rbp+0x510] -> rsi, index 0x17 -> r9d). On non-null rdi: call 0x2FE440(rdi), call 0xE935700(rdi, 0x138); zero slot [rbp+0x510] (16 B); allocate 4 bytes (edx=4) via global [0x1233E1A8] -> [rax+8] and call qword ptr [0xF99FFA0]; on success store rdi to [rbp+0x510], [rbp+0x520]=rax+4, [rbp+0x518]=rax, and mov dword ptr [rdi],1 at the new allocation. Then descriptor 3 built: [rbp+0x100]=&str 0xF55CDD3, [rbp+0x108]=0xC, [rsp+0x20]=rsi spill, &[rbp+0x100] -> rdx, &[rbp+0x530] -> rsi, index 6 -> r9d.
0x186f68b  lea rsi,[rbp+0x510]
0x186f692  mov rcx,[rbp+0x628]
0x186f699  mov r8,rsi
0x186f69c  mov r9d,0x17
0x186f6a2  call 0x1870DE0
0x186f6a7  nop
0x186f6a8  mov rdi,[rbp+0x510]
0x186f6af  test rdi,rdi
0x186f6b2  je short 0x186F6C9
0x186f6b4  mov rcx,rdi
0x186f6b7  call 0x2FE440
0x186f6bc  mov edx,0x138
0x186f6c1  mov rcx,rdi
0x186f6c4  call 0xE935700
0x186f6c9  xorps xmm0,xmm0
0x186f6cc  movaps [rbp+0x510],xmm0
0x186f6d3  mov qword ptr [rbp+0x520],0
0x186f6de  mov rcx,[0x1233E1A8]
0x186f6e5  mov rax,[rcx]
0x186f6e8  mov rax,[rax+8]
0x186f6ec  mov edx,4
0x186f6f1  call qword ptr [0xF99FFA0]
0x186f6f7  nop
0x186f6f8  mov rdi,rax
0x186f6fb  test rax,rax
0x186f6fe  je 0x1870241
0x186f704  mov [rbp+0x510],rdi
0x186f70b  mov rax,rdi
0x186f70e  add rax,4
0x186f712  mov [rbp+0x520],rax
0x186f719  mov dword ptr [rdi],1
0x186f71f  mov [rbp+0x518],rax
0x186f726  mov qword ptr [rbp+0x530],0
0x186f731  lea rax,[0xF55CDD3]
0x186f738  mov [rbp+0x100],rax
0x186f73f  mov qword ptr [rbp+0x108],0xC
0x186f74a  mov [rsp+0x20],rsi
0x186f74f  lea rdx,[rbp+0x100]
0x186f756  lea rsi,[rbp+0x530]
0x186f75d  mov rcx,[rbp+0x628]
0x186f764  mov r8,rsi
0x186f767  mov r9d,6
0x186f76d  call 0x1870DE0

### Phase 3: 0x186f772..0x186f838 (40 instructions)
Third resource load: index 6 -> r9d, slot [rbp+0x530]. On non-null rdi: call 0x2FE440(rdi), call 0xE935700(rdi, 0x138); zero slot [rbp+0x530] (16 B); allocate 4 bytes (edx=4) via global [0x1233E1A8] -> [rax+8] and call qword ptr [0xF99FFA0]; on success store rdi to [rbp+0x530], [rbp+0x540]=rax+4, [rbp+0x538]=rax, and mov dword ptr [rdi],1 at the new allocation. Then descriptor 4 built: [rbp+0x110]=&str 0xF55CDE0, [rbp+0x118]=9, [rsp+0x20]=rsi spill, &[rbp+0x110] -> rdx, &[rbp+0x550] -> rsi, index 7 -> r9d.
0x186f772  nop
0x186f773  mov rdi,[rbp+0x530]
0x186f77a  test rdi,rdi
0x186f77d  je short 0x186F794
0x186f77f  mov rcx,rdi
0x186f782  call 0x2FE440
0x186f787  mov edx,0x138
0x186f78c  mov rcx,rdi
0x186f78f  call 0xE935700
0x186f794  xorps xmm0,xmm0
0x186f797  movaps [rbp+0x530],xmm0
0x186f79e  mov qword ptr [rbp+0x540],0
0x186f7a9  mov rcx,[0x1233E1A8]
0x186f7b0  mov rax,[rcx]
0x186f7b3  mov rax,[rax+8]
0x186f7b7  mov edx,4
0x186f7bc  call qword ptr [0xF99FFA0]
0x186f7c2  nop
0x186f7c3  mov rdi,rax
0x186f7c6  test rax,rax
0x186f7c9  je 0x1870251
0x186f7cf  mov [rbp+0x530],rdi
0x186f7d6  mov rax,rdi
0x186f7d9  add rax,4
0x186f7dd  mov [rbp+0x540],rax
0x186f7e4  mov dword ptr [rdi],1
0x186f7ea  mov [rbp+0x538],rax
0x186f7f1  mov qword ptr [rbp+0x550],0
0x186f7fc  lea rax,[0xF55CDE0]
0x186f803  mov [rbp+0x110],rax
0x186f80a  mov qword ptr [rbp+0x118],9
0x186f815  mov [rsp+0x20],rsi
0x186f81a  lea rdx,[rbp+0x110]
0x186f821  lea rsi,[rbp+0x550]
0x186f828  mov rcx,[rbp+0x628]
0x186f82f  mov r8,rsi
0x186f832  mov r9d,7
0x186f838  call 0x1870DE0

### Phase 4: 0x186f83d..0x186f908 (40 instructions)
Fourth resource load (success path of call index 7, slot [rbp+0x550], issued at end of previous phase): on non-null rdi: call 0x2FE440(rdi), call 0xE935700(rdi, 0x138); zero slot [rbp+0x550] (16 B); allocate 4 bytes (edx=4) via global [0x1233E1A8] -> [rax+8] and call qword ptr [0xF99FFA0]; on success store rdi to [rbp+0x550], [rbp+0x560]=rax+4, [rbp+0x558]=rax, and mov dword ptr [rdi],1 at the new allocation. Then descriptor 5 built: [rbp+0x120]=&str 0xF55CE42, [rbp+0x128]=0xD, [rsp+0x20]=rsi spill, &[rbp+0x120] -> rdx, &[rbp+0x570] -> rsi, index 8 -> r9d; call 0x1870DE0 issued at the end of the phase.
0x186f83d  nop
0x186f83e  mov rdi,[rbp+0x550]
0x186f845  test rdi,rdi
0x186f848  je short 0x186F85F
0x186f84a  mov rcx,rdi
0x186f84d  call 0x2FE440
0x186f852  mov edx,0x138
0x186f857  mov rcx,rdi
0x186f85a  call 0xE935700
0x186f85f  xorps xmm0,xmm0
0x186f862  movaps [rbp+0x550],xmm0
0x186f869  mov qword ptr [rbp+0x560],0
0x186f874  mov rcx,[0x1233E1A8]
0x186f87b  mov rax,[rcx]
0x186f87e  mov rax,[rax+8]
0x186f882  mov edx,4
0x186f887  call qword ptr [0xF99FFA0]
0x186f88d  nop
0x186f88e  mov rdi,rax
0x186f891  test rax,rax
0x186f894  je 0x1870261
0x186f89a  mov [rbp+0x550],rdi
0x186f8a1  mov rax,rdi
0x186f8a4  add rax,4
0x186f8a8  mov [rbp+0x560],rax
0x186f8af  mov dword ptr [rdi],1
0x186f8b5  mov [rbp+0x558],rax
0x186f8bc  mov qword ptr [rbp+0x570],0
0x186f8c7  lea rax,[0xF55CE42]
0x186f8ce  mov [rbp+0x120],rax
0x186f8d5  mov qword ptr [rbp+0x128],0xD
0x186f8e0  mov [rsp+0x20],rsi
0x186f8e5  lea rdx,[rbp+0x120]
0x186f8ec  lea rsi,[rbp+0x570]
0x186f8f3  mov rcx,[rbp+0x628]
0x186f8fa  mov r8,rsi
0x186f8fd  mov r9d,8
0x186f903  call 0x1870DE0

### Phase 5: 0x186f909..0x186f9d7 (40 instructions)
Fifth resource load (success path of call index 8, slot [rbp+0x570]): on non-null rdi: call 0x2FE440(rdi), call 0xE935700(rdi, 0x138); zero slot [rbp+0x570] (16 B); allocate 0x10 bytes (edx=0x10) via global [0x1233E1A8] -> [rax+8] and call qword ptr [0xF99FFA0]; on success store rdi to [rbp+0x570], [rbp+0x580]=rax+0x10, movups [rdi] from constant [0xF0FBCF0] (16-byte store to the new allocation), [rbp+0x578]=rax. Then descriptor 6 built: [rbp+0x130]=&str 0xF55CDEA, [rbp+0x138]=0x13, [rsp+0x20]=rsi spill, &[rbp+0x130] -> rdx, &[rbp+0x590] -> rsi, index 0x26 -> r9d; call 0x1870DE0 issued at the end of the phase.
0x186f908  nop
0x186f909  mov rdi,[rbp+0x570]
0x186f910  test rdi,rdi
0x186f913  je short 0x186F92A
0x186f915  mov rcx,rdi
0x186f918  call 0x2FE440
0x186f91d  mov edx,0x138
0x186f922  mov rcx,rdi
0x186f925  call 0xE935700
0x186f92a  xorps xmm0,xmm0
0x186f92d  movaps [rbp+0x570],xmm0
0x186f934  mov qword ptr [rbp+0x580],0
0x186f93f  mov rcx,[0x1233E1A8]
0x186f946  mov rax,[rcx]
0x186f949  mov rax,[rax+8]
0x186f94d  mov edx,0x10
0x186f952  call qword ptr [0xF99FFA0]
0x186f958  nop
0x186f959  mov rdi,rax
0x186f95c  test rax,rax
0x186f95f  je 0x1870271
0x186f965  mov [rbp+0x570],rdi
0x186f96c  mov rax,rdi
0x186f96f  add rax,0x10
0x186f973  mov [rbp+0x580],rax
0x186f97a  movaps xmm0,[0xF0FBCF0]
0x186f981  movups [rdi],xmm0
0x186f984  mov [rbp+0x578],rax
0x186f98b  mov qword ptr [rbp+0x590],0
0x186f996  lea rax,[0xF55CDEA]
0x186f99d  mov [rbp+0x130],rax
0x186f9a4  mov qword ptr [rbp+0x138],0x13
0x186f9af  mov [rsp+0x20],rsi
0x186f9b4  lea rdx,[rbp+0x130]
0x186f9bb  lea rsi,[rbp+0x590]
0x186f9c2  mov rcx,[rbp+0x628]
0x186f9c9  mov r8,rsi
0x186f9cc  mov r9d,0x26
0x186f9d2  call 0x1870DE0

### Phase 6: 0x186f9d7..0x186fa9d (37 instructions)
Sixth resource load (success path of call index 0x26, slot [rbp+0x590]): on non-null rdi: call 0x2FE440(rdi), call 0xE935700(rdi, 0x138); zero slot [rbp+0x590] (16 B); allocate 4 bytes (edx=4) via global [0x1233E1A8] -> [rax+8] and call qword ptr [0xF99FFA0]; on success store rdi to [rbp+0x590], [rbp+0x5A0]=rax+4, [rbp+0x598]=rax, and mov dword ptr [rdi],6 at the new allocation (the only iteration storing an immediate value, 6). Then descriptor 7 prebuilt: [rbp+0x140]=&str 0xF55C92C, [rbp+0x148]=0xD, [rsp+0x20]=rsi spill, &[rbp+0x140] -> rdx, &[rbp+0x5B0] -> rsi, index 0xA -> r9d; call 0x1870DE0 issued at the end of the phase.
0x186f9d7  nop
0x186f9d8  mov rdi,[rbp+0x590]
0x186f9df  test rdi,rdi
0x186f9e2  je short 0x186F9F9
0x186f9e4  mov rcx,rdi
0x186f9e7  call 0x2FE440
0x186f9ec  mov edx,0x138
0x186f9f1  mov rcx,rdi
0x186f9f4  call 0xE935700
0x186f9f9  xorps xmm0,xmm0
0x186f9fc  movaps [rbp+0x590],xmm0
0x186fa03  mov qword ptr [rbp+0x5A0],0
0x186fa0e  mov rcx,[0x1233E1A8]
0x186fa15  mov rax,[rcx]
0x186fa18  mov rax,[rax+8]
0x186fa1c  mov edx,4
0x186fa21  call qword ptr [0xF99FFA0]
0x186fa27  nop
0x186fa28  mov rdi,rax
0x186fa2b  test rax,rax
0x186fa2e  je 0x1870281
0x186fa34  mov [rbp+0x590],rdi
0x186fa3b  mov rax,rdi
0x186fa3e  add rax,4
0x186fa42  mov [rbp+0x5A0],rax
0x186fa49  mov dword ptr [rdi],6
0x186fa4f  mov [rbp+0x598],rax
0x186fa56  mov qword ptr [rbp+0x5B0],0
0x186fa61  lea rax,[0xF55C92C]
0x186fa68  mov [rbp+0x140],rax
0x186fa6f  mov qword ptr [rbp+0x148],0xD
0x186fa7a  mov [rsp+0x20],rsi
0x186fa7f  lea rdx,[rbp+0x140]
0x186fa86  lea rsi,[rbp+0x5B0]
0x186fa8d  mov rcx,[rbp+0x628]
0x186fa94  mov r8,rsi
0x186fa97  mov r9d,0xA
0x186fa9d  call 0x1870DE0

### Phase 7: 0x186faa2..0x186fae0 (13 instructions)
Seventh resource load (slice ends at 0x186fae0, mid-sequence): success path of call index 0xA, slot [rbp+0x5B0]; on non-null rdi: call 0x2FE440(rdi), call 0xE935700(rdi, 0x138); zero slot [rbp+0x5B0] (16 B); zero [rbp+0x5C0]; allocation prologue begins: rcx=[0x1233E1A8], rax=[rcx] — slice stops before [rax+8], edx, and the indirect call.
0x186faa2  nop
0x186faa3  mov rdi,[rbp+0x5B0]
0x186faaa  test rdi,rdi
0x186faad  je short 0x186FAC4
0x186faaf  mov rcx,rdi
0x186fab2  call 0x2FE440
0x186fab7  mov edx,0x138
0x186fabc  mov rcx,rdi
0x186fabf  call 0xE935700
0x186fac4  xorps xmm0,xmm0
0x186fac7  movaps [rbp+0x5B0],xmm0
0x186face  mov qword ptr [rbp+0x5C0],0
0x186fad9  mov rcx,[0x1233E1A8]
0x186fae0  mov rax,[rcx]

## Field map: every [reg+off] field stored or loaded in the slice

| offset | size | direction | site | verbatim instruction line(s) | meaning |
|---|---|---|---|---|---|
| rbp+0xE0 | 8 | A | [rbp+0xE0] | `0x186f5b5  lea rdx,[rbp+0xE0]` | address computation only (lea rdx); no memory read |
| rbp+0x4F0 | 16 | R/W | [rbp+0x4F0] | `0x186f5bc  lea rsi,[rbp+0x4F0]` ; `0x186f5d9  mov rdi,[rbp+0x4F0]` ; `0x186f5fd  movaps [rbp+0x4F0],xmm0` ; `0x186f635  mov [rbp+0x4F0],rdi` | resource slot pointer: address taken (lea), loaded into rdi and non-null tested (je), 16-byte zeroed (movaps), re-stored |
| rbp+0x628 | 8 | R | [rbp+0x628] | `0x186f5c3  mov rcx,[rbp+0x628]` ; `0x186f692  mov rcx,[rbp+0x628]` ; `0x186f75d  mov rcx,[rbp+0x628]` ; `0x186f8f3  mov rcx,[rbp+0x628]` ; `0x186f9c2  mov rcx,[rbp+0x628]` ; `0x186fa8d  mov rcx,[rbp+0x628]` | instance pointer: loaded and passed as rcx (arg 1) to each call 0x1870DE0 |
| rbp+0x500 | 8 | W | [rbp+0x500] | `0x186f604  mov qword ptr [rbp+0x500],0` ; `0x186f643  mov [rbp+0x500],rax` | next-cursor field: zeroed, then set to rax+0x10 (end of the 0x10-byte allocation) |
| rbp+0x4F8 | 8 | W | [rbp+0x4F8] | `0x186f654  mov [rbp+0x4F8],rax` | - |
| rbp+0xF0 | 8 | A/W | [rbp+0xF0] | `0x186f66d  mov [rbp+0xF0],rax` ; `0x186f684  lea rdx,[rbp+0xF0]` | descriptor field 0: string pointer (&str 0xF55A7AB stored via lea rax,[0xF55A7AB]); its address passed as rdx to call 0x1870DE0 |
| rbp+0xF8 | 8 | W | [rbp+0xF8] | `0x186f674  mov qword ptr [rbp+0xF8],0x1B` | descriptor field 8: length 0x1B (immediate) |
| rsp+0x20 | 8 | W | [rsp+0x20] | `0x186f67f  mov [rsp+0x20],rsi` ; `0x186f74a  mov [rsp+0x20],rsi` ; `0x186f815  mov [rsp+0x20],rsi` ; `0x186f8e0  mov [rsp+0x20],rsi` ; `0x186f9af  mov [rsp+0x20],rsi` ; `0x186fa7a  mov [rsp+0x20],rsi` | spill slot: rsi (address of current output slot [rbp+0x5xx]) preserved across calls |
| rbp+0x510 | 16 | R/W | [rbp+0x510] | `0x186f65b  mov qword ptr [rbp+0x510],0` ; `0x186f68b  lea rsi,[rbp+0x510]` ; `0x186f6a8  mov rdi,[rbp+0x510]` ; `0x186f6cc  movaps [rbp+0x510],xmm0` | resource slot pointer: zeroed, address passed as rsi, loaded into rdi, 16-byte zeroed after use |
| rbp+0x520 | 8 | W | [rbp+0x520] | `0x186f6d3  mov qword ptr [rbp+0x520],0` ; `0x186f712  mov [rbp+0x520],rax` | next-cursor field: zeroed, then set to rax+4 (end of the 4-byte allocation) |
| rbp+0x518 | 8 | W | [rbp+0x518] | `0x186f71f  mov [rbp+0x518],rax` | - |
| rbp+0x530 | 16 | R/W | [rbp+0x530] | `0x186f726  mov qword ptr [rbp+0x530],0` ; `0x186f756  lea rsi,[rbp+0x530]` ; `0x186f773  mov rdi,[rbp+0x530]` ; `0x186f797  movaps [rbp+0x530],xmm0` | resource slot pointer |
| rbp+0x100 | 8 | A/W | [rbp+0x100] | `0x186f738  mov [rbp+0x100],rax` ; `0x186f74f  lea rdx,[rbp+0x100]` | descriptor field 0: string pointer (&str 0xF55CDD3); address passed as rdx |
| rbp+0x108 | 8 | W | [rbp+0x108] | `0x186f73f  mov qword ptr [rbp+0x108],0xC` | descriptor field 8: length 0xC |
| rbp+0x540 | 8 | W | [rbp+0x540] | `0x186f79e  mov qword ptr [rbp+0x540],0` ; `0x186f7dd  mov [rbp+0x540],rax` | next-cursor field: zeroed, then set to rax+4 |
| rbp+0x538 | 8 | W | [rbp+0x538] | `0x186f7ea  mov [rbp+0x538],rax` | - |
| rbp+0x550 | 16 | R/W | [rbp+0x550] | `0x186f7f1  mov qword ptr [rbp+0x550],0` ; `0x186f821  lea rsi,[rbp+0x550]` ; `0x186f83e  mov rdi,[rbp+0x550]` ; `0x186f862  movaps [rbp+0x550],xmm0` | resource slot pointer |
| rbp+0x110 | 8 | A/W | [rbp+0x110] | `0x186f803  mov [rbp+0x110],rax` ; `0x186f81a  lea rdx,[rbp+0x110]` | descriptor field 0: string pointer (&str 0xF55CDE0); address passed as rdx |
| rbp+0x118 | 8 | W | [rbp+0x118] | `0x186f80a  mov qword ptr [rbp+0x118],9` | descriptor field 8: length 9 |
| rbp+0x560 | 8 | W | [rbp+0x560] | `0x186f869  mov qword ptr [rbp+0x560],0` ; `0x186f8a8  mov [rbp+0x560],rax` | next-cursor field: zeroed, then set to rax+4 |
| rbp+0x558 | 8 | W | [rbp+0x558] | `0x186f8b5  mov [rbp+0x558],rax` | - |
| rbp+0x570 | 16 | R/W | [rbp+0x570] | `0x186f8bc  mov qword ptr [rbp+0x570],0` ; `0x186f8ec  lea rsi,[rbp+0x570]` ; `0x186f909  mov rdi,[rbp+0x570]` ; `0x186f92d  movaps [rbp+0x570],xmm0` | resource slot pointer |
| rbp+0x120 | 8 | A/W | [rbp+0x120] | `0x186f8ce  mov [rbp+0x120],rax` ; `0x186f8e5  lea rdx,[rbp+0x120]` | descriptor field 0: string pointer (&str 0xF55CE42); address passed as rdx |
| rbp+0x128 | 8 | W | [rbp+0x128] | `0x186f8d5  mov qword ptr [rbp+0x128],0xD` | descriptor field 8: length 0xD |
| rbp+0x580 | 8 | W | [rbp+0x580] | `0x186f934  mov qword ptr [rbp+0x580],0` ; `0x186f973  mov [rbp+0x580],rax` | next-cursor field: zeroed, then set to rax+0x10 (end of the 0x10-byte allocation) |
| rbp+0x578 | 8 | W | [rbp+0x578] | `0x186f984  mov [rbp+0x578],rax` | - |
| rbp+0x590 | 16 | R/W | [rbp+0x590] | `0x186f98b  mov qword ptr [rbp+0x590],0` ; `0x186f9bb  lea rsi,[rbp+0x590]` ; `0x186f9d8  mov rdi,[rbp+0x590]` ; `0x186f9fc  movaps [rbp+0x590],xmm0` | resource slot pointer |
| rbp+0x130 | 8 | A/W | [rbp+0x130] | `0x186f99d  mov [rbp+0x130],rax` ; `0x186f9b4  lea rdx,[rbp+0x130]` | descriptor field 0: string pointer (&str 0xF55CDEA); address passed as rdx |
| rbp+0x138 | 8 | W | [rbp+0x138] | `0x186f9a4  mov qword ptr [rbp+0x138],0x13` | descriptor field 8: length 0x13 |
| rbp+0x5A0 | 8 | W | [rbp+0x5A0] | `0x186fa03  mov qword ptr [rbp+0x5A0],0` ; `0x186fa42  mov [rbp+0x5A0],rax` | next-cursor field: zeroed, then set to rax+4 |
| rbp+0x598 | 8 | W | [rbp+0x598] | `0x186fa4f  mov [rbp+0x598],rax` | - |
| rbp+0x5B0 | 16 | R/W | [rbp+0x5B0] | `0x186fa56  mov qword ptr [rbp+0x5B0],0` ; `0x186fa86  lea rsi,[rbp+0x5B0]` ; `0x186faa3  mov rdi,[rbp+0x5B0]` ; `0x186fac7  movaps [rbp+0x5B0],xmm0` | resource slot pointer |
| rbp+0x140 | 8 | A/W | [rbp+0x140] | `0x186fa68  mov [rbp+0x140],rax` ; `0x186fa7f  lea rdx,[rbp+0x140]` | descriptor field 0: string pointer (&str 0xF55C92C); address passed as rdx |
| rbp+0x148 | 8 | W | [rbp+0x148] | `0x186fa6f  mov qword ptr [rbp+0x148],0xD` | descriptor field 8: length 0xD |
| rbp+0x5C0 | 8 | W | [rbp+0x5C0] | `0x186face  mov qword ptr [rbp+0x5C0],0` | next-cursor field: zeroed; slice ends before any store/use |
| rax+8 | 8 | R | [rax+8] | `0x186f619  mov rax,[rax+8]` ; `0x186f6e8  mov rax,[rax+8]` ; `0x186f7b3  mov rax,[rax+8]` ; `0x186f87e  mov rax,[rax+8]` ; `0x186f949  mov rax,[rax+8]` ; `0x186fa18  mov rax,[rax+8]` | pointer read via rcx=[0x1233E1A8], rax=[rcx], rax=[rax+8]; value is dead/overwritten by the indirect call result, meaning not shown |

## TOOL REQUESTS

cmp.py (throwaway, in %TEMP%\opencode, not in repo) | _part_Lr4.txt + rdis dis 0x186f5b5 250 -> mismatch report | verified all 250 quoted instruction lines against rdis disassembly instead of eyeballing them; no repo script was worth keeping.
