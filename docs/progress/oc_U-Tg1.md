## NEXT
DONE

# UNIT U-Tg1 — texgroup_load 0x5421c90 slice, instructions 0x5421c90..0x54220f9

Source listing: docs/progress/_part_Tg1.txt (250 instructions, chunk 1 of 6 of texgroup_load_5421c90_54235a0). Every instruction in the slice is covered by exactly one phase below. The field table then lists every [reg+off] field the code stores or loads, one row per distinct offset, with all sites listed.

## Phase 1: 0x5421c90..0x5421cf0 — Prologue

Pushes eight callee-saved registers (rbp, r15, r14, r13, r12, rsi, rdi, rbx), sub rsp,0x2C8, sets frame base rbp=rsp+0x80, stores a -2 sentinel at [rbp+0x240], and spills incoming arguments (rcx->[rbp+0x228], rdx->r13, r8->r12, r9d->r15d, [r8]->[rbp+0x1C0]) while zeroing xmm0. [V 0x5421c90..0x5421cc9]
0x5421c90  push rbp
0x5421c91  push r15
0x5421c93  push r14
0x5421c95  push r13
0x5421c97  push r12
0x5421c99  push rsi
0x5421c9a  push rdi
0x5421c9b  push rbx
0x5421c9c  sub rsp,0x2C8
0x5421ca3  lea rbp,[rsp+0x80]
0x5421cab  mov qword ptr [rbp+0x240],0xFFFFFFFFFFFFFFFE
0x5421cb6  mov r15d,r9d
0x5421cb9  mov r12,r8
0x5421cbc  mov r13,rdx
0x5421cbf  mov [rbp+0x228],rcx
0x5421cc6  mov eax,[r8]
0x5421cc9  mov [rbp+0x1C0],eax
0x5421ccf  xorps xmm0,xmm0
0x5421cd2  movups [rbp+0x1C8],xmm0
0x5421cd9  movups [rbp+0x1D8],xmm0
0x5421ce0  mov rsi,[r8+0x18]
0x5421ce4  cmp qword ptr [r8+0x20],0x10
0x5421ce9  jb short 0x5421CF2
0x5421ceb  mov rbx,[r12+8]
0x5421cf0  jmp short 0x5421CF7

## Phase 2: 0x5421cf2..0x5421d2c — Small-string load and inline copy

rbx=[r12+8] is either the inline buffer [r12+8] (when [r8+0x20]<=0x10) or the heap pointer; a negative rsi branches to 0x5423524. For length<=0xF the code stacks the string descriptor ([rbp+0x120]=&rbp+0x1C8, [rbp+0x1D8]=rsi length, [rbp+0x1E0]=0xF capacity) and copies up to 16 bytes from [rbx] into [rbp+0x1C8] with movups, then jumps to 0x5421DBF. [V 0x5421cf2..0x5421d2c]
0x5421cf2  lea rbx,[r12+8]
0x5421cf7  test rsi,rsi
0x5421cfa  js 0x5423524
0x5421d00  lea rax,[rbp+0x1C8]
0x5421d07  cmp rsi,0xF
0x5421d0b  mov [rbp+0x120],rax
0x5421d12  ja short 0x5421D31
0x5421d14  mov [rbp+0x1D8],rsi
0x5421d1b  mov qword ptr [rbp+0x1E0],0xF
0x5421d26  movups xmm0,[rbx]
0x5421d29  movups [rax],xmm0
0x5421d2c  jmp 0x5421DBF

## Phase 3: 0x5421d31..0x5421d81 — Heap allocation size computation and allocator call

rdx=rsi|0xF, clamped to a minimum size of 0x16 in rdi; the allocator global is loaded from [0x1233E1A8] and the allocator is called through [0xF99FFA0]; sizes below 0xFFF allocate rdi+1 bytes, larger sizes align rdi+0x28 up to 0x20 and backstore the raw pointer at [rcx-8]; NULL returns branch to 0x5423437 (large) / 0x5423596 (small), success continues at 0x5421D9C. [V 0x5421d31..0x5421d81]
0x5421d31  mov rdx,rsi
0x5421d34  or rdx,0xF
0x5421d38  cmp rdx,0x17
0x5421d3c  mov edi,0x16
0x5421d41  cmovae rdi,rdx
0x5421d45  mov rcx,[0x1233E1A8]
0x5421d4c  mov rax,[rcx]
0x5421d4f  mov rax,[rax+8]
0x5421d53  cmp rdx,0xFFF
0x5421d5a  jb short 0x5421D83
0x5421d5c  lea r14,[rdi+0x28]
0x5421d60  mov rdx,r14
0x5421d63  call qword ptr [0xF99FFA0]
0x5421d69  test rax,rax
0x5421d6c  je 0x5423437
0x5421d72  mov rcx,rax
0x5421d75  add rcx,0x27
0x5421d79  and rcx,0xFFFFFFFFFFFFFFE0
0x5421d7d  mov [rcx-8],rax
0x5421d81  jmp short 0x5421D9C

## Phase 4: 0x5421d83..0x5421dba — Small allocation, descriptor store, and string copy

r14=rdi+1, call [0xF99FFA0], NULL branches to 0x5423596; on success the descriptor is stored ([rbp+0x1C8]=heap pointer rcx, [rbp+0x1D8]=rsi length, [rbp+0x1E0]=rdi capacity), rsi is incremented to include the NUL terminator, and call 0xEEC6EC0 copies the string (rcx=new buffer, rdx=old data [rbx], r8=new length). [V 0x5421d83..0x5421dba]
0x5421d83  lea r14,[rdi+1]
0x5421d87  mov rdx,r14
0x5421d8a  call qword ptr [0xF99FFA0]
0x5421d90  mov rcx,rax
0x5421d93  test rax,rax
0x5421d96  je 0x5423596
0x5421d9c  mov [rbp+0x1C8],rcx
0x5421da3  mov [rbp+0x1D8],rsi
0x5421daa  mov [rbp+0x1E0],rdi
0x5421db1  inc rsi
0x5421db4  mov rdx,rbx
0x5421db7  mov r8,rsi
0x5421dba  call 0xEEC6EC0

## Phase 5: 0x5421dbf..0x5421e1c — Descriptor reload and call to 0x5477A30

Loads [r12+0x28] into xmm0 and stores it at [rbp+0x1E8], stores r15d at [rbp+0x1F8], reloads rsi=[rbp+0x228] (the saved first argument), sets rcx=rsi+0x248 and rdx=&rbp+0x1C0, saves [rbp+0x78]=rcx, calls 0x5477A30, saves r13 at [rbp+0x138]; if rax==[rsi+0x248] it jumps to 0x5421E14 to zero [r13] and goto 0x5421EAA. [V 0x5421dbf..0x5421e1c]
0x5421dbf  movups xmm0,[r12+0x28]
0x5421dc5  movups [rbp+0x1E8],xmm0
0x5421dcc  mov [rbp+0x1F8],r15d
0x5421dd3  mov rsi,[rbp+0x228]
0x5421dda  lea rcx,[rsi+0x248]
0x5421de1  lea rdx,[rbp+0x1C0]
0x5421de8  mov [rbp+0x78],rcx
0x5421dec  call 0x5477A30
0x5421df1  cmp rax,[rsi+0x248]
0x5421df8  mov [rbp+0x138],r13
0x5421dff  je short 0x5421E14
0x5421e01  mov rcx,[rax+0x68]
0x5421e05  test rcx,rcx
0x5421e08  je short 0x5421E21
0x5421e0a  lock inc dword ptr [rcx+8]
0x5421e0e  mov rbx,[rax+0x68]
0x5421e12  jmp short 0x5421E23
0x5421e14  xorps xmm0,xmm0
0x5421e17  movups [r13],xmm0
0x5421e1c  jmp 0x5421EAA

## Phase 6: 0x5421e21..0x5421e53 — Existing-object handling and first virtual call

ebx=0, rsi=[rax+0x60], [r13]=rsi, [r13+8]=0; if rsi!=0 then rax=[rsi+0x18], rsi+=0x18, rax=[rax+8], rcx=rsi, call [0xF99FFA0]; test eax; r13 is restored from [rbp+0x138]; if zero branches to 0x5423171. [V 0x5421e21..0x5421e53]
0x5421e21  xor ebx,ebx
0x5421e23  mov rsi,[rax+0x60]
0x5421e27  mov [r13],rsi
0x5421e2b  mov [r13+8],rbx
0x5421e2f  test rsi,rsi
0x5421e32  je short 0x5421E7A
0x5421e34  mov rax,[rsi+0x18]
0x5421e38  add rsi,0x18
0x5421e3c  mov rax,[rax+8]
0x5421e40  mov rcx,rsi
0x5421e43  call qword ptr [0xF99FFA0]
0x5421e49  nop
0x5421e4a  test eax,eax
0x5421e4c  mov r13,[rbp+0x138]
0x5421e53  je 0x5423171

## Phase 7: 0x5421e59..0x5421ea4 — Second virtual call and reference-counted release

rax=[rsi], rax=[rax+8], call [0xF99FFA0]; cmp eax,1 branches to 0x5423171 when equal; otherwise the rbx object is released: test rbx skips when zero, lock dec [rbx+8] (exit if nonzero), rax=[rbx]; rax=[rax]; call [0xF99FFA0] (destroy), lock dec [rbx+0xC] (exit if nonzero), rax=[rbx]; rax=[rax+8]; call [0xF99FFA0] (free). [V 0x5421e59..0x5421ea4]
0x5421e59  mov rax,[rsi]
0x5421e5c  mov rax,[rax+8]
0x5421e60  mov rcx,rsi
0x5421e63  call qword ptr [0xF99FFA0]
0x5421e69  nop
0x5421e6a  cmp eax,1
0x5421e6d  mov r13,[rbp+0x138]
0x5421e74  je 0x5423171
0x5421e7a  test rbx,rbx
0x5421e7d  je short 0x5421EAA
0x5421e7f  lock dec dword ptr [rbx+8]
0x5421e83  jne short 0x5421EAA
0x5421e85  mov rax,[rbx]
0x5421e88  mov rax,[rax]
0x5421e8b  mov rcx,rbx
0x5421e8e  call qword ptr [0xF99FFA0]
0x5421e94  lock dec dword ptr [rbx+0xC]
0x5421e98  jne short 0x5421EAA
0x5421e9a  mov rax,[rbx]
0x5421e9d  mov rax,[rax+8]
0x5421ea1  mov rcx,rbx
0x5421ea4  call qword ptr [0xF99FFA0]

## Phase 8: 0x5421eaa..0x5421ef6 — Flag computation and call to 0x5475A30

rbx=[rbp+0x2B0]; ebx=(bit 32 of rbx set) ? 1 : 0 via bt cmovae; call 0x5475A30 with rcx=[rbp+0x228]+0x1A8, rdx=&rbp+0x140, r8=r12; ecx=(ebx==9) ? 1 : 0x40, then if bit 32 of [rbp+0x2B8] is set ecx=[rbp+0x2B8]; finally [rbp+0x128]=ecx. [V 0x5421eaa..0x5421ef6]
0x5421eaa  mov rbx,[rbp+0x2B0]
0x5421eb1  bt rbx,0x20
0x5421eb6  mov esi,1
0x5421ebb  cmovae ebx,esi
0x5421ebe  mov rax,[rbp+0x228]
0x5421ec5  lea rcx,[rax+0x1A8]
0x5421ecc  lea rdx,[rbp+0x140]
0x5421ed3  mov r8,r12
0x5421ed6  call 0x5475A30
0x5421edb  nop
0x5421edc  cmp ebx,9
0x5421edf  mov ecx,0x40
0x5421ee4  cmove ecx,esi
0x5421ee7  mov rax,[rbp+0x2B8]
0x5421eee  bt rax,0x20
0x5421ef3  cmovb ecx,eax
0x5421ef6  mov [rbp+0x128],ecx

## Phase 9: 0x5421efc..0x5421f75 — Flag byte store and 0x20-byte object allocation

r14=[rbp+0x140]; al=(r15d==1); ecx = (r15d!=0) ? al : 4; rax=[r14+0x58]; or [rax+0x51], cl stores the computed flag byte; the allocator global [0x1233E1A8] is dereferenced to [rax+8] and 0x20 bytes are allocated through [0xF99FFA0]; rdi=rax (NULL branches to 0x54233E7); [rbp+0x130]=rbx, [rdi+8]=0x100000001 (refcount 1), [rbp+0x108]=rdi+0xC, [rdi]=vtable 0xF09AA70, and [rdi+0x10] is zeroed with movups. [V 0x5421efc..0x5421f75]
0x5421efc  mov r14,[rbp+0x140]
0x5421f03  xor eax,eax
0x5421f05  cmp r15d,1
0x5421f09  sete al
0x5421f0c  test r15d,r15d
0x5421f0f  mov ecx,4
0x5421f14  cmovne ecx,eax
0x5421f17  mov rax,[r14+0x58]
0x5421f1b  or [rax+0x51],cl
0x5421f1e  mov rcx,[0x1233E1A8]
0x5421f25  mov rax,[rcx]
0x5421f28  mov rax,[rax+8]
0x5421f2c  mov edx,0x20
0x5421f31  call qword ptr [0xF99FFA0]
0x5421f37  nop
0x5421f38  mov rdi,rax
0x5421f3b  test rax,rax
0x5421f3e  je 0x54233E7
0x5421f44  mov [rbp+0x130],rbx
0x5421f4b  lea rbx,[rdi+8]
0x5421f4f  mov rax,0x100000001
0x5421f59  mov [rdi+8],rax
0x5421f5d  lea rax,[rdi+0xC]
0x5421f61  mov [rbp+0x108],rax
0x5421f68  lea rax,[0xF09AA70]
0x5421f6f  mov [rdi],rax
0x5421f72  xorps xmm0,xmm0
0x5421f75  movups [rdi+0x10],xmm0

## Phase 10: 0x5421f79..0x5421fd5 — Old-object refcount bump and saved pointer fixup

rsi=[rbp+0x228], rcx=[rsi+0x28] (zero branches to 0x542351E); [rbp+0x218]=rdi, [rbp+0x100]=rbx, [rbp+0x230]=rdi+0x10; the old object's refcount is bumped with eax=[rcx+8] then lock cmpxchg [rcx+8],eax+1 (retry loop until success); rax=[rsi+0x20], r12=[rsi+0x28]; [rbp+0x208] = (rax==0) ? 0 : rax-0x18 via lea/cmove. [V 0x5421f79..0x5421fd5]
0x5421f79  mov rsi,[rbp+0x228]
0x5421f80  mov rcx,[rsi+0x28]
0x5421f84  test rcx,rcx
0x5421f87  mov [rbp+0x218],rdi
0x5421f8e  mov [rbp+0x100],rbx
0x5421f95  je 0x542351E
0x5421f9b  mov rax,rdi
0x5421f9e  add rax,0x10
0x5421fa2  mov [rbp+0x230],rax
0x5421fa9  mov eax,[rcx+8]
0x5421fac  nop [rax]
0x5421fb0  test eax,eax
0x5421fb2  je 0x542351E
0x5421fb8  lea edx,[rax+1]
0x5421fbb  lock cmpxchg [rcx+8],edx
0x5421fc0  jne short 0x5421FB0
0x5421fc2  mov rax,[rsi+0x20]
0x5421fc6  mov r12,[rsi+0x28]
0x5421fca  lea rcx,[rax-0x18]
0x5421fce  test rax,rax
0x5421fd1  cmove rcx,rax
0x5421fd5  mov [rbp+0x208],rcx

## Phase 11: 0x5421fdc..0x542201a — Release of the previous object (r12)

If r12==0 skip to 0x542202E; otherwise lock inc [r12+0xC], lock dec [r12+8] and exit to 0x542202E if nonzero; rsi=r12+0xC; rax=[r12]; rax=[rax]; call [0xF99FFA0] (destroy); lock dec [rsi] (exit to 0x542201A if nonzero); rax=[r12]; rax=[rax+8]; call [0xF99FFA0] (free); at 0x542201a, rsi=[rbp+0x228] and control continues to 0x542202E. [V 0x5421fdc..0x542201a]
0x5421fdc  test r12,r12
0x5421fdf  je short 0x5422023
0x5421fe1  lock inc dword ptr [r12+0xC]
0x5421fe7  lock dec dword ptr [r12+8]
0x5421fed  jne short 0x542202E
0x5421fef  lea rsi,[r12+0xC]
0x5421ff4  mov rax,[r12]
0x5421ff8  mov rax,[rax]
0x5421ffb  mov rcx,r12
0x5421ffe  call qword ptr [0xF99FFA0]
0x5422004  lock dec dword ptr [rsi]
0x5422007  jne short 0x542201A
0x5422009  mov rax,[r12]
0x542200d  mov rax,[rax+8]
0x5422011  mov rcx,r12
0x5422014  call qword ptr [0xF99FFA0]
0x542201a  mov rsi,[rbp+0x228]
0x5422021  jmp short 0x542202E

## Phase 12: 0x5422023..0x5422083 — NULL check, poison write, and stack slot refresh

[rbp+0x208]=0; rax=[rsi+0x1B8], zero branches to 0x542216B; if *rax==0 jump to 0x542204E, otherwise mov dword ptr [0],0xDEADC0DE (a deliberate NULL-poison crash); rax=[rsi+0x1C8]; [rbp+0x70]=rax; xmm0 is zeroed and movaps [rbp+0x140]=0; if r12!=0 then [rbp+0x140]=[rbp+0x208], [rbp+0x148]=r12, lock inc [r12+0xC]; finally [rbp+0x200]=r12. [V 0x5422023..0x5422083]
0x5422023  mov qword ptr [rbp+0x208],0
0x542202e  mov rax,[rsi+0x1B8]
0x5422035  test rax,rax
0x5422038  je 0x542216B
0x542203e  cmp byte ptr [rax],0
0x5422041  jne short 0x542204E
0x5422043  mov dword ptr [0],0xDEADC0DE
0x542204e  mov rax,[rsi+0x1C8]
0x5422055  mov [rbp+0x70],rax
0x5422059  xorps xmm0,xmm0
0x542205c  movaps [rbp+0x140],xmm0
0x5422063  test r12,r12
0x5422066  je short 0x5422083
0x5422068  mov rax,[rbp+0x208]
0x542206f  mov [rbp+0x140],rax
0x5422076  mov [rbp+0x148],r12
0x542207d  lock inc dword ptr [r12+0xC]
0x5422083  mov [rbp+0x200],r12

## Phase 13: 0x542208a..0x54220f9 — Final store of the new object and length setup

movaps [rbp+0x150]=0; lock inc [rdi+8] bumps the new object refcount; [rbp+0x150]=[rbp+0x230], [rbp+0x158]=rdi; eax=[rbp+0x1C0]; [rbp+0x160]=eax; [rbp+0x168] and [rbp+0x178] are zeroed with movups; r12=[rbp+0x1D8] (old length); if length<=0x10 the inline buffer &rbp+0x1C8 is used else rbx=[rbp+0x1C8] (heap pointer); negative length branches to 0x542352A; [rbp+0x178]=r12 stores the length. [V 0x542208a..0x54220f9]
0x542208a  movaps [rbp+0x150],xmm0
0x5422091  lock inc dword ptr [rdi+8]
0x5422095  mov rax,[rbp+0x230]
0x542209c  mov [rbp+0x150],rax
0x54220a3  mov [rbp+0x158],rdi
0x54220aa  mov eax,[rbp+0x1C0]
0x54220b0  mov [rbp+0x160],eax
0x54220b6  movups [rbp+0x168],xmm0
0x54220bd  movups [rbp+0x178],xmm0
0x54220c4  mov r12,[rbp+0x1D8]
0x54220cb  cmp qword ptr [rbp+0x1E0],0x10
0x54220d3  lea rbx,[rbp+0x1C8]
0x54220da  jb short 0x54220E3
0x54220dc  mov rbx,[rbp+0x1C8]
0x54220e3  test r12,r12
0x54220e6  js 0x542352A
0x54220ec  lea r13,[rbp+0x168]
0x54220f3  cmp r12,0xF
0x54220f7  ja short 0x5422118
0x54220f9  mov [rbp+0x178],r12

## Field map: every [reg+off] field stored or loaded (one row per distinct offset)

| offset | size | read/store address | verbatim `0xRVA  instr` sites | meaning |
| rbp+0x240 | 8 | W [rbp+0x240] | `0x5421cab  mov qword ptr [rbp+0x240],0xFFFFFFFFFFFFFFFE` | - |
| rbp+0x228 | 8 | W [rbp+0x228] / R [rbp+0x228] | `0x5421cbf  mov [rbp+0x228],rcx`<br>`0x5421dd3  mov rsi,[rbp+0x228]`<br>`0x5421ebe  mov rax,[rbp+0x228]`<br>`0x5421f79  mov rsi,[rbp+0x228]`<br>`0x542201a  mov rsi,[rbp+0x228]` | - |
| r8+0 | 4 | R [r8+0] | `0x5421cc6  mov eax,[r8]` | - |
| r8+0x18 | 8 | R [r8+0x18] | `0x5421ce0  mov rsi,[r8+0x18]` | - |
| r8+0x20 | 8 | R [r8+0x20] | `0x5421ce4  cmp qword ptr [r8+0x20],0x10` | - |
| rbp+0x1C0 | 4 | W [rbp+0x1C0] / R [rbp+0x1C0] | `0x5421cc9  mov [rbp+0x1C0],eax`<br>`0x54220aa  mov eax,[rbp+0x1C0]` | - |
| rbp+0x1C8 | 16 (movups) / 8 (mov) | W [rbp+0x1C8] / R [rbp+0x1C8] | `0x5421cd2  movups [rbp+0x1C8],xmm0`<br>`0x5421d29  movups [rax],xmm0` (rax=&rbp+0x1C8)<br>`0x5421d9c  mov [rbp+0x1C8],rcx`<br>`0x54220dc  mov rbx,[rbp+0x1C8]` | - |
| rbp+0x1D8 | 16 (movups) / 8 (mov) | W [rbp+0x1D8] / R [rbp+0x1D8] | `0x5421cd9  movups [rbp+0x1D8],xmm0`<br>`0x5421d14  mov [rbp+0x1D8],rsi`<br>`0x5421da3  mov [rbp+0x1D8],rsi`<br>`0x54220c4  mov r12,[rbp+0x1D8]` | - |
| rbp+0x1E0 | 8 | W [rbp+0x1E0] / R [rbp+0x1E0] | `0x5421d1b  mov qword ptr [rbp+0x1E0],0xF`<br>`0x5421daa  mov [rbp+0x1E0],rdi`<br>`0x54220cb  cmp qword ptr [rbp+0x1E0],0x10` | - |
| rbp+0x120 | 8 | W [rbp+0x120] | `0x5421d0b  mov [rbp+0x120],rax` | - |
| rbx+0 | 16 (movups) / 8 | R [rbx+0] | `0x5421d26  movups xmm0,[rbx]`<br>`0x5421e85  mov rax,[rbx]`<br>`0x5421e9a  mov rax,[rbx]` | - |
| rcx+0 | 8 | R [rcx+0] | `0x5421d4c  mov rax,[rcx]`<br>`0x5421f25  mov rax,[rcx]` | - |
| rax+8 | 8 | R [rax+8] | `0x5421d4f  mov rax,[rax+8]`<br>`0x5421e3c  mov rax,[rax+8]`<br>`0x5421e5c  mov rax,[rax+8]`<br>`0x5421e9d  mov rax,[rax+8]`<br>`0x542200d  mov rax,[rax+8]` | - |
| abs 0x1233E1A8 | 8 | R [0x1233E1A8] | `0x5421d45  mov rcx,[0x1233E1A8]`<br>`0x5421f1e  mov rcx,[0x1233E1A8]` | - |
| abs 0xF99FFA0 | 8 | R [0xF99FFA0] (indirect-call target slot) | `0x5421d63  call qword ptr [0xF99FFA0]`<br>`0x5421d8a  call qword ptr [0xF99FFA0]`<br>`0x5421e43  call qword ptr [0xF99FFA0]`<br>`0x5421e63  call qword ptr [0xF99FFA0]`<br>`0x5421e8e  call qword ptr [0xF99FFA0]`<br>`0x5421ea4  call qword ptr [0xF99FFA0]`<br>`0x5421f31  call qword ptr [0xF99FFA0]`<br>`0x5421ffe  call qword ptr [0xF99FFA0]`<br>`0x5422014  call qword ptr [0xF99FFA0]` | - |
| rbp+0x1E8 | 16 | W [rbp+0x1E8] | `0x5421dc5  movups [rbp+0x1E8],xmm0` | - |
| rbp+0x1F8 | 4 | W [rbp+0x1F8] | `0x5421dcc  mov [rbp+0x1F8],r15d` | - |
| rbp+0x78 | 8 | W [rbp+0x78] | `0x5421de8  mov [rbp+0x78],rcx` | - |
| rsi+0x248 | 8 | R [rsi+0x248] | `0x5421df1  cmp rax,[rsi+0x248]` | - |
| rbp+0x138 | 8 | W [rbp+0x138] / R [rbp+0x138] | `0x5421df8  mov [rbp+0x138],r13`<br>`0x5421e4c  mov r13,[rbp+0x138]`<br>`0x5421e6d  mov r13,[rbp+0x138]` | - |
| rax+0x68 | 8 | R [rax+0x68] | `0x5421e01  mov rcx,[rax+0x68]`<br>`0x5421e0e  mov rbx,[rax+0x68]` | - |
| rcx+8 | 4 | R/W [rcx+8] | `0x5421e0a  lock inc dword ptr [rcx+8]`<br>`0x5421fa9  mov eax,[rcx+8]`<br>`0x5421fbb  lock cmpxchg [rcx+8],edx` | - |
| r13+0 | 16 (movups) / 8 | W [r13+0] | `0x5421e17  movups [r13],xmm0`<br>`0x5421e27  mov [r13],rsi` | - |
| rax+0x60 | 8 | R [rax+0x60] | `0x5421e23  mov rsi,[rax+0x60]` | - |
| r13+8 | 8 | W [r13+8] | `0x5421e2b  mov [r13+8],rbx` | - |
| rsi+0x18 | 8 | R [rsi+0x18] | `0x5421e34  mov rax,[rsi+0x18]` | - |
| rsi+0 | 8 | R [rsi+0] | `0x5421e59  mov rax,[rsi]` | - |
| rbx+8 | 4 | R/W [rbx+8] | `0x5421e7f  lock dec dword ptr [rbx+8]` | - |
| rax+0 | 8 / 1 | R [rax+0] | `0x5421e88  mov rax,[rax]`<br>`0x5421ff8  mov rax,[rax]`<br>`0x542203e  cmp byte ptr [rax],0` | - |
| rbx+0xC | 4 | R/W [rbx+0xC] | `0x5421e94  lock dec dword ptr [rbx+0xC]` | - |
| rbp+0x2B0 | 8 | R [rbp+0x2B0] | `0x5421eaa  mov rbx,[rbp+0x2B0]` | - |
| rbp+0x2B8 | 8 | R [rbp+0x2B8] | `0x5421ee7  mov rax,[rbp+0x2B8]` | - |
| rbp+0x128 | 4 | W [rbp+0x128] | `0x5421ef6  mov [rbp+0x128],ecx` | - |
| rbp+0x140 | 16 (movaps) / 8 | R [rbp+0x140] / W [rbp+0x140] | `0x5421efc  mov r14,[rbp+0x140]`<br>`0x542205c  movaps [rbp+0x140],xmm0`<br>`0x542206f  mov [rbp+0x140],rax` | - |
| r14+0x58 | 8 | R [r14+0x58] | `0x5421f17  mov rax,[r14+0x58]` | - |
| rax+0x51 | 1 | R/W [rax+0x51] | `0x5421f1b  or [rax+0x51],cl` | - |
| rdi+8 | 8 (mov) / 4 (lock inc) | W [rdi+8] / R/W [rdi+8] | `0x5421f59  mov [rdi+8],rax`<br>`0x5422091  lock inc dword ptr [rdi+8]` | - |
| rdi+0 | 8 | W [rdi+0] | `0x5421f6f  mov [rdi],rax` | - |
| rdi+0x10 | 16 | W [rdi+0x10] | `0x5421f75  movups [rdi+0x10],xmm0` | - |
| rbp+0x218 | 8 | W [rbp+0x218] | `0x5421f87  mov [rbp+0x218],rdi` | - |
| rbp+0x100 | 8 | W [rbp+0x100] | `0x5421f8e  mov [rbp+0x100],rbx` | - |
| rbp+0x230 | 8 | W [rbp+0x230] / R [rbp+0x230] | `0x5421fa2  mov [rbp+0x230],rax`<br>`0x5422095  mov rax,[rbp+0x230]` | - |
| rsi+0x20 | 8 | R [rsi+0x20] | `0x5421fc2  mov rax,[rsi+0x20]` | - |
| rsi+0x28 | 8 | R [rsi+0x28] | `0x5421f80  mov rcx,[rsi+0x28]`<br>`0x5421fc6  mov r12,[rsi+0x28]` | - |
| rbp+0x208 | 8 | W [rbp+0x208] / R [rbp+0x208] | `0x5421fd5  mov [rbp+0x208],rcx`<br>`0x5422023  mov qword ptr [rbp+0x208],0`<br>`0x5422068  mov rax,[rbp+0x208]` | - |
| r12+0xC | 4 | R/W [r12+0xC] | `0x5421fe1  lock inc dword ptr [r12+0xC]`<br>`0x542207d  lock inc dword ptr [r12+0xC]` | - |
| r12+8 | 8 (mov) / 4 (lock dec) | R [r12+8] / R/W [r12+8] | `0x5421ceb  mov rbx,[r12+8]`<br>`0x5421fe7  lock dec dword ptr [r12+8]` | - |
| r12+0 | 8 | R [r12+0] | `0x5421ff4  mov rax,[r12]`<br>`0x5422009  mov rax,[r12]` | - |
| rsi+0 (2nd use, =r12+0xC) | 4 | R/W [rsi+0] | `0x5422004  lock dec dword ptr [rsi]` | - |
| rsi+0x1B8 | 8 | R [rsi+0x1B8] | `0x542202e  mov rax,[rsi+0x1B8]` | - |
| abs 0x0 | 4 | W [0] | `0x5422043  mov dword ptr [0],0xDEADC0DE` | Deliberate NULL-poison crash writing 0xDEADC0DE to address 0, shown by the instruction itself [V 0x5422043] |
| rsi+0x1C8 | 8 | R [rsi+0x1C8] | `0x542204e  mov rax,[rsi+0x1C8]` | - |
| rbp+0x70 | 8 | W [rbp+0x70] | `0x5422055  mov [rbp+0x70],rax` | - |
| rbp+0x200 | 8 | W [rbp+0x200] | `0x5422083  mov [rbp+0x200],r12` | - |
| rbp+0x150 | 16 (movaps) / 8 | W [rbp+0x150] | `0x542208a  movaps [rbp+0x150],xmm0`<br>`0x542209c  mov [rbp+0x150],rax` | - |
| rbp+0x158 | 8 | W [rbp+0x158] | `0x54220a3  mov [rbp+0x158],rdi` | - |
| rbp+0x160 | 4 | W [rbp+0x160] | `0x54220b0  mov [rbp+0x160],eax` | - |
| rbp+0x168 | 16 | W [rbp+0x168] | `0x54220b6  movups [rbp+0x168],xmm0` | - |
| rbp+0x178 | 16 (movups) / 8 | W [rbp+0x178] | `0x54220bd  movups [rbp+0x178],xmm0`<br>`0x54220f9  mov [rbp+0x178],r12` | - |
