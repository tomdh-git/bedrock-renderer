## NEXT
DONE (orchestrator-written from listing ui_visitor_6664a00_6668510.txt; supersedes rejected oc_U-D8c.md)

# D8 UIMesh description field map (UI visitor case head 0x6664bd6, description pointer r9)

All lines below are verbatim from the listing. Call: `0x6664f4a  call 0x674A3A0` (extractor), rcx=r13-chain object (set before head), rdx=rdi (`0x6664f44  mov rdx,rdi`), r8d=0 (`0x6664f47  xor r8d,r8d`), 13+ stack args.

## Loads from description (r9) in the case head
    0x6664bd6  movzx ecx,byte ptr [r9+0x82]
    0x6664bde  movzx r12d,byte ptr [r9+0x83]
    0x6664be6  movzx edx,byte ptr [r9+0x84]
    0x6664bee  test cl,cl
    0x6664bf0  mov r8d,1
    0x6664bf6  cmove r8d,edx
    0x6664bfa  test r12b,r12b
    0x6664bfd  mov r10d,2
    0x6664c03  cmove r10d,r8d
    0x6664c07  lea rbx,[r9+0x88]
    0x6664c0e  mov byte ptr [rbp+0x224],0
    0x6664c15  movzx esi,byte ptr [r9+0x85]
    0x6664c1d  movzx r8d,byte ptr [r9+0x81]
    0x6664c25  movss xmm0,[r9+0x70]
    0x6664c2b  mov r11,[r9+0x60]
    0x6664c2f  mov rdx,[r9+0x68]
    0x6664c33  movzx edi,byte ptr [r9+0x80]
    0x6664c3b  lea rax,[r9+0x18]
    0x6664c3f  cmp qword ptr [r9+0x58],2
    0x6664c44  mov [rbp+0x520],cl
    0x6664c4a  mov [rbp+0x518],r12b
    0x6664c51  mov [rbp+0x510],dil
    0x6664c58  jb 0x6664E7C
    0x6664c5e  xorps xmm1,xmm1
    0x6664c61  movaps [rbp+0x400],xmm1
    0x6664c68  mov r15,[r9+0x30]

## Path taken when [r9+0x58] >= 2 and [r9+0x30] != 0 (16-byte {ptr, refcounted ctrl} copy at [rbp+0x400])
    0x6664c6c  test r15,r15
    0x6664c6f  je 0x6664E8E
    0x6664c68  mov r15,[r9+0x30]
    0x6664c6c  test r15,r15
    0x6664c6f  je 0x6664E8E
    0x6664c75  lock inc dword ptr [r15+8]
    0x6664c7a  mov r15,[r9+0x30]
    0x6664c7e  jmp 0x6664E91

## Stack-argument setup (0x6664e97..0x6664f4a)
    0x6664e82  xorps xmm1,xmm1
    0x6664e85  movaps [rbp+0x400],xmm1
    0x6664e8c  jmp short 0x6664EA9
    0x6664e8e  xor r15d,r15d
    0x6664e91  mov rcx,r13
    0x6664e94  mov rdi,r14
    0x6664e97  mov r12,[r9+0x28]
    0x6664e9b  mov [rbp+0x400],r12
    0x6664ea2  mov [rbp+0x408],r15
    0x6664ea9  mov r15,[r9+0x10]
    0x6664ead  mov r12,[r9+0x78]
    0x6664eb1  mov r13,[r9]
    0x6664eb4  mov r14,[r9+8]
    0x6664eb8  add r9,0x86
    0x6664ebf  mov [rsp+0xA0],rbx
    0x6664ec7  lea rbx,[rbp+0x1E0]
    0x6664ece  mov [rsp+0x98],rbx
    0x6664ed6  mov [rsp+0x90],r10d
    0x6664ede  mov [rsp+0x60],rdx
    0x6664ee3  mov [rsp+0x58],r11
    0x6664ee8  lea r10,[rbp+0x400]
    0x6664eef  mov [rsp+0x48],r10
    0x6664ef4  mov [rsp+0x40],rax
    0x6664ef9  mov [rsp+0x38],r13
    0x6664efe  mov [rsp+0x30],r15
    0x6664f03  mov [rsp+0x28],r12
    0x6664f08  mov [rsp+0x20],r14
    0x6664f0d  mov [rsp+0x88],sil
    0x6664f15  movzx eax,byte ptr [rbp+0x520]
    0x6664f1c  mov [rsp+0x80],al
    0x6664f23  movzx eax,byte ptr [rbp+0x518]
    0x6664f2a  mov [rsp+0x78],al
    0x6664f2e  mov [rsp+0x70],r8b
    0x6664f33  movzx eax,byte ptr [rbp+0x510]
    0x6664f3a  mov [rsp+0x50],al
    0x6664f3e  movss [rsp+0x68],xmm0
    0x6664f44  mov rdx,rdi
    0x6664f47  xor r8d,r8d
    0x6664f4a  call 0x674A3A0

## Table: extractor 0x674A3A0 argument -> description field
| arg slot | value | source (description offset) | evidence |
|---|---|---|---|
| [rsp+0x20] | r14 | qword [r9+0x08] | 0x6664eb4 mov r14,[r9+8]; 0x6664f08 mov [rsp+0x20],r14 |
| [rsp+0x28] | r12 | qword [r9+0x78] | 0x6664ead mov r12,[r9+0x78]; 0x6664f03 |
| [rsp+0x30] | r15 | qword [r9+0x10] | 0x6664ea9 mov r15,[r9+0x10]; 0x6664efe |
| [rsp+0x38] | r13 | qword [r9+0x00] | 0x6664eb1 mov r13,[r9]; 0x6664ef9 |
| [rsp+0x40] | rax | address r9+0x18 (embedded sub-object) | 0x6664c3b lea rax,[r9+0x18]; 0x6664ef4 |
| [rsp+0x48] | &[rbp+0x400] | 16B local {qword [r9+0x28], qword [r9+0x30] (refcounted ctrl, lock inc [ctrl+8] at 0x6664c75)}; zeroed when [r9+0x58]<2 (0x6664c58 jb) | 0x6664e97/0x6664e9b/0x6664ea2 |
| [rsp+0x50] | al | byte [r9+0x80] (via [rbp+0x510]) | 0x6664c33 movzx edi,byte ptr [r9+0x80]; 0x6664c51 mov [rbp+0x510],dil; 0x6664f33 |
| [rsp+0x58] | r11 | qword [r9+0x60] | 0x6664c2b; 0x6664ee3 |
| [rsp+0x60] | rdx | qword [r9+0x68] | 0x6664c2f; 0x6664ede |
| [rsp+0x68] | xmm0 | float [r9+0x70] | 0x6664c25 movss xmm0,[r9+0x70]; 0x6664f3e |
| [rsp+0x70] | r8b | byte [r9+0x81] | 0x6664c1d movzx r8d,byte ptr [r9+0x81]; 0x6664f2e |
| [rsp+0x78] | al | byte [r9+0x83] (via [rbp+0x518]) | 0x6664c4a mov [rbp+0x518],r12b with r12 from 0x6664bde; 0x6664f2a |
| [rsp+0x80] | al | byte [r9+0x82] (via [rbp+0x520]) | 0x6664c44 mov [rbp+0x520],cl with cl from 0x6664bd6; 0x6664f1c |
| [rsp+0x88] | sil | byte [r9+0x85] | 0x6664c15 movzx esi,byte ptr [r9+0x85]; 0x6664f0d |
| [rsp+0x90] | r10d | derived enum: 2 if byte[+0x83]!=0; else 1 if byte[+0x82]!=0; else byte[+0x84] | 0x6664bee..0x6664c03 (test/cmove chain) |
| [rsp+0x98] | &[rbp+0x1E0] | local 16B block (not from description in this path; the other case paths load it from 0xEF40DE0, e.g. 0x6664c90) | 0x6664ece lea rbx,[rbp+0x1E0] |
| [rsp+0xA0] | rbx | address r9+0x88 (embedded sub-object) | 0x6664c07 lea rbx,[r9+0x88] |

Description size lower bound: highest touched offset is the sub-object at +0x88 (pointer stored, size not visible); 0x6664eb8 add r9,0x86 hints a 0x86-byte stride (see [UNVERIFIED: 0x6664eb8 add r9,0x86 is whether the array element stride or a pointer bump]).
Field summary by offset: +0x00 q, +0x08 q, +0x10 q, +0x18 sub-object, +0x28 q, +0x30 q (refcounted ctrl), +0x40 sub-object (other path 0x6664c83), +0x58 count/size, +0x60 q, +0x68 q, +0x70 float, +0x78 q, +0x80..+0x85 bytes, +0x88 sub-object.
Names: none shown by instructions or strings; not guessing.

# HudIcon (case head 0x6664c83, description pointer r9, call 0x6664d46) — verbatim listing lines
    0x6664c83  lea rax,[r9+0x40]
    0x6664c87  mov rcx,[r9+0x30]
    0x6664c8b  movzx edx,byte ptr [r9+0x3A]
    0x6664c90  movaps xmm0,[0xEF40DE0]
    0x6664c97  movaps [rbp+0x1E0],xmm0
    0x6664c9e  mov r8,[r9+0x20]
    0x6664ca2  lea rdi,[r9+0x10]
    0x6664ca6  xorps xmm0,xmm0
    0x6664ca9  movaps [rbp+0x400],xmm0
    0x6664cb0  mov r10,[r9+0x28]
    0x6664cb4  mov r11,[r9]
    0x6664cb7  mov rsi,[r9+8]
    0x6664cbb  add r9,0x38
    0x6664cbf  mov [rsp+0xA0],rax
    0x6664cc7  mov [rsp+0x98],rcx
    0x6664ccf  mov [rsp+0x70],dl
    0x6664cd3  lea rax,[rbp+0x1E0]
    0x6664cda  mov [rsp+0x60],rax
    0x6664cdf  mov [rsp+0x58],r8
    0x6664ce4  lea rax,[rbp+0x400]
    0x6664ceb  mov [rsp+0x48],rax
    0x6664cf0  mov [rsp+0x40],rdi
    0x6664cf5  mov [rsp+0x38],r10
    0x6664cfa  mov [rsp+0x30],rsi
    0x6664cff  mov [rsp+0x20],r11
    0x6664d04  mov dword ptr [rsp+0x90],0
    0x6664d0f  mov byte ptr [rsp+0x88],0
    0x6664d17  mov byte ptr [rsp+0x80],0
    0x6664d1f  mov byte ptr [rsp+0x78],0
    0x6664d24  mov dword ptr [rsp+0x68],0x3F800000
    0x6664d2c  mov byte ptr [rsp+0x50],0
    0x6664d31  mov qword ptr [rsp+0x28],0
    0x6664d3a  mov rcx,r13
    0x6664d3d  mov rdx,r14
    0x6664d40  mov r8d,1
    0x6664d46  call 0x674A3A0

| arg | value | source | evidence |
|---|---|---|---|
| rcx / rdx / r8d | r13 / r14 / 1 | same context regs as UIMesh; r8d=1 (UIMesh passes 0) | 0x6664d3a mov rcx,r13; 0x6664d3d mov rdx,r14; 0x6664d40 mov r8d,1 |
| [rsp+0x20] | r11 | qword [r9+0x00] | 0x6664cb4 mov r11,[r9]; 0x6664cff |
| [rsp+0x28] | 0 | constant | 0x6664d31 mov qword ptr [rsp+0x28],0 |
| [rsp+0x30] | rsi | qword [r9+0x08] | 0x6664cb7 mov rsi,[r9+8]; 0x6664cfa |
| [rsp+0x38] | r10 | qword [r9+0x28] | 0x6664cb0 mov r10,[r9+0x28]; 0x6664cf5 |
| [rsp+0x40] | rdi | address r9+0x10 (sub-object) | 0x6664ca2 lea rdi,[r9+0x10]; 0x6664cf0 |
| [rsp+0x48] | &[rbp+0x400] | 16B local zeroed | 0x6664ca6 xorps xmm0,xmm0; 0x6664ca9 movaps [rbp+0x400],xmm0 |
| [rsp+0x50] | 0 | constant byte | 0x6664d2c |
| [rsp+0x58] | r8 | qword [r9+0x20] | 0x6664c9e mov r8,[r9+0x20]; 0x6664cdf |
| [rsp+0x60] | &[rbp+0x1E0] | 16B constant copied from [0xEF40DE0] | 0x6664c90 movaps xmm0,[0xEF40DE0]; 0x6664c97 movaps [rbp+0x1E0],xmm0 |
| [rsp+0x68] | 0x3F800000 (1.0f) | constant | 0x6664d24 |
| [rsp+0x70] | dl | byte [r9+0x3A] | 0x6664c8b movzx edx,byte ptr [r9+0x3A]; 0x6664ccf |
| [rsp+0x78],[rsp+0x80],[rsp+0x88] | 0 | constant bytes | 0x6664d1f, 0x6664d17, 0x6664d0f |
| [rsp+0x90] | 0 | constant dword | 0x6664d04 |
| [rsp+0x98] | rcx | qword [r9+0x30] | 0x6664c87 mov rcx,[r9+0x30]; 0x6664cc7 |
| [rsp+0xA0] | rax | address r9+0x40 (sub-object) | 0x6664c83 lea rax,[r9+0x40]; 0x6664cbf |

HudIcon description: read offsets +0x00,+0x08,+0x10(addr),+0x20,+0x28,+0x30,+0x3A(byte),+0x40(addr); stride bump `0x6664cbb  add r9,0x38` ([UNVERIFIED: 0x6664cbb whether 0x38 is the element stride]).
Constants vs UIMesh: scale float 1.0f, bytes/dword flags 0, mode r8d=1. Names: none shown; not guessing.

# Gameface (listing gameface_66ade80_66b0eb0.txt; description pointer r14, element pointer r15; walk from 0x66aecb7, tool output docs/progress/_d8_gameface_cw.txt)

Description (r14) reads, verbatim:
    0x66aebd4  movzx eax,byte ptr [r14+8]
    0x66aebd9  movzx ecx,byte ptr [r14+0xC]
    0x66aebec  cmp byte ptr [r14+0x17],1
    0x66aebf8  movzx ecx,byte ptr [r14+0xE]
    0x66aec1f  lea rdx,[r14+0x13]
    0x66aec6b  lea rdx,[r14+0xF]
    0x66aecb7  movzx eax,byte ptr [r14+0xD]
    0x66aecc2  mov rax,[r14+0x80]
    0x66aeef0  mov eax,[r14]

+0x80 is a pointer to a {begin,end} pair; elements iterated with stride 0x1A0:
    0x66aecc2  mov rax,[r14+0x80]
    0x66aecc9  mov r15,[rax]
    0x66aeccc  mov rax,[rax+8]
    0x66aece0  add r15,0x1A0
    0x66aece7  cmp r15,[rbp+0x1D0]

Element (r15, size 0x1A0 per `add r15,0x1A0`) reads, verbatim:
    0x66aed2a  movzx edi,byte ptr [r15+0x18C]
    0x66aed32  movups xmm9,[r15+0x190]
    0x66aed3a  mov eax,[r15+0x184]
    0x66aed41  mov ecx,[r15+0x188]
    0x66aed48  mov rdx,[r15]
    0x66aed57  mov rdx,[r15+0x48]
    0x66aed64  mov rdx,[r15+0x48]
    0x66aed72  mov r9,[r15+0x40]
    0x66aed84  mov rdx,[r15+0x28]
    0x66af0c0  cmp qword ptr [r15+0x58],0
    0x66af0f0  mov rax,[r15+0x50]
    0x66af193  cmp qword ptr [r15+0x68],0
    0x66af1c3  mov rax,[r15+0x60]
    0x66af263  mov rax,[r15+0x138]
    0x66af26a  mov rsi,[r15+0x140]

| element offset | size/kind | read site |
|---|---|---|
| +0x00 | qword ptr, then dword [ptr+4] loaded | 0x66aed48 / 0x66aed4b |
| +0x28 | qword | 0x66aed84 |
| +0x40 | qword | 0x66aed72 |
| +0x48 | qword refcounted ctrl (lock inc [ctrl+8]) | 0x66aed57..0x66aed64 |
| +0x50 / +0x58 | qword pair, +0x58 tested against 0 | 0x66af0f0 / 0x66af0c0 |
| +0x60 / +0x68 | qword pair, +0x68 tested against 0 | 0x66af1c3 / 0x66af193 |
| +0x138 / +0x140 | qword each | 0x66af263 / 0x66af26a |
| +0x184 / +0x188 | dword each | 0x66aed3a / 0x66aed41 |
| +0x18C | byte | 0x66aed2a |
| +0x190 | 16 bytes (movups) | 0x66aed32 |
Description: +0x00 dword (0x66aeef0), +0x08 byte, +0x0C, +0x0D, +0x0E bytes, +0x0F addr, +0x13 addr, +0x17 byte compared to 1, +0x80 ptr to {begin,end}.
Names: none shown. Not yet instruction-complete (the extractor-call arg slots for Gameface are not mapped): [UNVERIFIED: 0x66aed84.. which extractor call consumes these element fields].

# Gameface extractor call 0x66B2730 (call site 0x66aedf1): complete argument map (orchestrator, verbatim listing lines)
    0x66aed68  jmp short 0x66AED72
    0x66aed6a  nop [rax+rax]
    0x66aed70  xor edx,edx
    0x66aed72  mov r9,[r15+0x40]
    0x66aed76  mov [rbp+0x1E0],r9
    0x66aed7d  mov [rbp+0x1E8],rdx
    0x66aed84  mov rdx,[r15+0x28]
    0x66aed88  movaps [rbp+0x1F0],xmm8
    0x66aed90  mov r9,[rdx+8]
    0x66aed94  test r9,r9
    0x66aed97  je short 0x66AEDB0
    0x66aed99  lock inc dword ptr [r9+8]
    0x66aed9e  mov r9,[rdx+8]
    0x66aeda2  jmp short 0x66AEDB3
    0x66aeda4  nop [rax+rax]
    0x66aedb0  xor r9d,r9d
    0x66aedb3  mov rdx,[rdx]
    0x66aedb6  mov [rbp+0x1F0],rdx
    0x66aedbd  mov [rbp+0x1F8],r9
    0x66aedc4  mov rdx,[rbp+0x4E0]
    0x66aedcb  mov rdx,[rdx]
    0x66aedce  mov [rsp+0x30],eax
    0x66aedd2  mov [rsp+0x28],rcx
    0x66aedd7  mov [rsp+0x20],r8
    0x66aeddc  lea rcx,[rbp+0x170]
    0x66aede3  lea r8,[rbp+0x1F0]
    0x66aedea  lea r9,[rbp+0x1E0]

| arg | value | source | evidence |
|---|---|---|---|
| rcx | &[rbp+0x170] | local out/state block | 0x66aeddc lea rcx,[rbp+0x170] |
| rdx | [[rbp+0x4E0]] | pointer loaded from frame slot +0x4E0 (not from the description) | 0x66aedc4 mov rdx,[rbp+0x4E0]; 0x66aedcb mov rdx,[rdx] |
| r8 | &[rbp+0x1F0] | 16B {ptr [[r15+0x28]], refcounted ctrl [[r15+0x28]+8] (lock inc [ctrl+8])}; element +0x28 is a pointer to that pair | 0x66aed84 mov rdx,[r15+0x28]; 0x66aed90 mov r9,[rdx+8]; 0x66aed99 lock inc dword ptr [r9+8]; 0x66aedb3 mov rdx,[rdx]; 0x66aedb6 mov [rbp+0x1F0],rdx; 0x66aedbd mov [rbp+0x1F8],r9 |
| r9 | &[rbp+0x1E0] | 16B {qword element +0x40, element +0x48 refcounted ctrl (lock inc [ctrl+8])} | 0x66aed57 mov rdx,[r15+0x48]; 0x66aed60 lock inc dword ptr [rdx+8]; 0x66aed72 mov r9,[r15+0x40]; 0x66aed76 mov [rbp+0x1E0],r9; 0x66aed7d mov [rbp+0x1E8],rdx |
| [rsp+0x20] | r8 | dword [[element+0x00]+4] | 0x66aed48 mov rdx,[r15]; 0x66aed4b mov r8d,[rdx+4]; 0x66aedd7 mov [rsp+0x20],r8 |
| [rsp+0x28] | rcx | element dword +0x188 (zero-extended) | 0x66aed41 mov ecx,[r15+0x188]; 0x66aedd2 mov [rsp+0x28],rcx |
| [rsp+0x30] | eax | element dword +0x184 | 0x66aed3a mov eax,[r15+0x184]; 0x66aedce mov [rsp+0x30],eax |
