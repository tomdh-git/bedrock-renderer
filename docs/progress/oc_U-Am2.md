## NEXT
DONE

## Unit U-Am2 — atlas_meta_parse 0x4e1a52a..0x4e1a9c2 (chunk 2 of 7)

Source listing: docs/progress/_part_Am2.txt — 250 instructions from 0x4e1a52a to 0x4e1a9c2 (continuation of chunk 1, oc_U-Am1, which ends at 0x4e1a527). Static analysis only; RVAs are image-base RVAs of Minecraft.Windows.exe 1.26.62.01. Every phase and field claim is [V] (seen in the provided listing); the listing is ground truth for sizes, offsets and verbatim instruction text. Processed in five ~60-instruction pieces, appended after each piece.

### Phase 1 — 0x4e1a52a..0x4e1a54d (piece 1 of 5)
0x4e1a52a..0x4e1a54d: Loop tail: when the word at [rax+0x5C] differs from 0xFFFF, call 0x6692240 with rcx=rsi [V], then force that word to 0xFFFF [V] and jump back to 0x4E1A520 [V]; when it already equals 0xFFFF the jump back is taken immediately [V].
0x4e1a52a  je short 0x4E1A500
0x4e1a52c  mov rax,[r12]
0x4e1a530  movzx edx,word ptr [rax+0x5C]
0x4e1a534  cmp dx,0xFFFF
0x4e1a538  je short 0x4E1A520
0x4e1a53a  mov rcx,rsi
0x4e1a53d  call 0x6692240
0x4e1a542  nop
0x4e1a543  mov rax,[r12]
0x4e1a547  mov word ptr [rax+0x5C],0xFFFF
0x4e1a54d  jmp short 0x4E1A520

### Phase 2 — 0x4e1a54f..0x4e1a57f (piece 1 of 5)
0x4e1a54f..0x4e1a57f: Load rax=[rbp+0x358], then walk rsi=[rax+0x100] toward rdi=[rax+0x108] [V], calling 0x4E196B0 with rcx=rsi on each 0x40-byte element until rsi == rdi [V].
0x4e1a54f  mov rax,[rbp+0x358]
0x4e1a556  mov rsi,[rax+0x100]
0x4e1a55d  mov rdi,[rax+0x108]
0x4e1a564  cmp rsi,rdi
0x4e1a567  je short 0x4E1A596
0x4e1a569  nop [rax]
0x4e1a570  mov rcx,rsi
0x4e1a573  call 0x4E196B0
0x4e1a578  add rsi,0x40
0x4e1a57c  cmp rsi,rdi
0x4e1a57f  jne short 0x4E1A570

### Phase 3 — 0x4e1a581..0x4e1a5c7 (piece 1 of 5)
0x4e1a581..0x4e1a5c7: Reset the range with [rcx+0x108] = [rcx+0x100] [V], then zero the frame block [rbp+0x130..0x180] with five movaps stores [V], clear qword [rbp+0x180] and dword [rbp+0x2D0] [V].
0x4e1a581  mov rcx,[rbp+0x358]
0x4e1a588  mov rax,[rcx+0x100]
0x4e1a58f  mov [rcx+0x108],rax
0x4e1a596  xorps xmm6,xmm6
0x4e1a599  movaps [rbp+0x170],xmm6
0x4e1a5a0  movaps [rbp+0x160],xmm6
0x4e1a5a7  movaps [rbp+0x150],xmm6
0x4e1a5ae  movaps [rbp+0x140],xmm6
0x4e1a5b5  movaps [rbp+0x130],xmm6
0x4e1a5bc  mov qword ptr [rbp+0x180],0
0x4e1a5c7  mov dword ptr [rbp+0x2D0],0

### Phase 4 — 0x4e1a5d1..0x4e1a60f (piece 1 of 5)
0x4e1a5d1..0x4e1a60f: Set rdi=&[rbp+0x130], rdx=&[rbp+0x2D0], r8=&[rbp+0x310] and call 0x4E60480 [V], re-zero [rbp+0x170] and [rbp+0x180] [V], load rsi = [[rbp+0x358]+0x18] [V], and jump to 0x4E1A6F4 when rsi == rdi [V].
0x4e1a5d1  lea rdi,[rbp+0x130]
0x4e1a5d8  lea rdx,[rbp+0x2D0]
0x4e1a5df  lea r8,[rbp+0x310]
0x4e1a5e6  mov rcx,rdi
0x4e1a5e9  call 0x4E60480
0x4e1a5ee  nop
0x4e1a5ef  movaps [rbp+0x170],xmm6
0x4e1a5f6  mov qword ptr [rbp+0x180],0
0x4e1a601  mov rax,[rbp+0x358]
0x4e1a608  mov rsi,[rax+0x18]
0x4e1a60c  cmp rsi,rdi
0x4e1a60f  je 0x4E1A6F4

### Phase 5 — 0x4e1a615..0x4e1a645 (piece 1 of 5)
0x4e1a615..0x4e1a645: Store rsi at [rbp+0x2D0], copy dword [rbp+0x130] to [rsi] [V], then with rcx=rsi+8 and rdx=[[rbp+0x138]] call 0x4E60730 [V]; finally load [rsi+0x10] and [rsi+0x38] [V] and convert [rsi+0x10] to float, with negatives fixed up by shift/or [V].
0x4e1a615  mov [rbp+0x2D0],rsi
0x4e1a61c  mov eax,[rbp+0x130]
0x4e1a622  mov [rsi],eax
0x4e1a624  lea rcx,[rsi+8]
0x4e1a628  mov r8,[rbp+0x138]
0x4e1a62f  mov rdx,[r8]
0x4e1a632  call 0x4E60730
0x4e1a637  nop
0x4e1a638  mov rax,[rsi+0x10]
0x4e1a63c  mov rdi,[rsi+0x38]
0x4e1a640  test rax,rax
0x4e1a643  js short 0x4E1A64C
0x4e1a645  cvtsi2ss xmm0,rax
0x4e1a64a  jmp short 0x4E1A661

### Phase 6 — 0x4e1a64c..0x4e1a6b1 (piece 2 of 5)
0x4e1a64c..0x4e1a6b1: Convert the integer to float exactly (the negative path shifts/or-computes before cvtsi2ss) [V], divide xmm0 by the dword at [rsi] [V], round via 0xEEC73F0 with a 0.5f bias from [0xEEE6700] plus a sign-mask correction [V], then clamp the result to a minimum of 8 [V].
0x4e1a64c  mov rcx,rax
0x4e1a64f  shr rcx,1
0x4e1a652  and eax,1
0x4e1a655  or rax,rcx
0x4e1a658  cvtsi2ss xmm0,rax
0x4e1a65d  addss xmm0,xmm0
0x4e1a661  divss xmm0,[rsi]
0x4e1a665  call 0xEEC73F0
0x4e1a66a  cvttss2si rax,xmm0
0x4e1a66f  mov rcx,rax
0x4e1a672  subss xmm0,[0xEEE6700]
0x4e1a67a  cvttss2si rdx,xmm0
0x4e1a67f  sar rcx,0x3F
0x4e1a683  and rdx,rcx
0x4e1a686  or rdx,rax
0x4e1a689  cmp rdx,9
0x4e1a68d  mov eax,8
0x4e1a692  cmovae rax,rdx
0x4e1a696  cmp rdi,rax
0x4e1a699  jae short 0x4E1A6B8
0x4e1a69b  lea rcx,[rdi*8]
0x4e1a6a3  cmp rcx,rax
0x4e1a6a6  cmovbe rcx,rax
0x4e1a6aa  cmp rdi,0x200
0x4e1a6b1  cmovae rcx,rax

### Phase 7 — 0x4e1a6b5..0x4e1a6ee (piece 2 of 5)
0x4e1a6b5..0x4e1a6ee: Move the clamped count into rdi and call 0x77D80 with rcx=rsi, rdx=rdi [V]; advance rsi by 0x40, compute (([rbp+0x178]-[rbp+0x170])>>3) * 0xAAAAAAAAAAAAAAAB [V], and call 0x4E61430 with rcx=rsi, rdx=[rbp+0x178] [V].
0x4e1a6b5  mov rdi,rcx
0x4e1a6b8  mov rcx,rsi
0x4e1a6bb  mov rdx,rdi
0x4e1a6be  call 0x77D80
0x4e1a6c3  nop
0x4e1a6c4  add rsi,0x40
0x4e1a6c8  mov rdx,[rbp+0x170]
0x4e1a6cf  mov r8,[rbp+0x178]
0x4e1a6d6  sub r8,rdx
0x4e1a6d9  sar r8,3
0x4e1a6dd  mov rax,0xAAAAAAAAAAAAAAAB
0x4e1a6e7  imul r8,rax
0x4e1a6eb  mov rcx,rsi
0x4e1a6ee  call 0x4E61430

### Phase 8 — 0x4e1a6f3..0x4e1a728 (piece 2 of 5)
0x4e1a6f3..0x4e1a728: Finalize via 0x4E1F1B0 on &[rbp+0x130] [V], then store the tagged qword 0xD000000000000 | (0xF55CD23 & 0xFF00FFFFFFFFFFFF) to [rbp+0x2D0] [V] and clear byte [rbp+0x140] [V].
0x4e1a6f3  nop
0x4e1a6f4  lea rcx,[rbp+0x130]
0x4e1a6fb  call 0x4E1F1B0
0x4e1a700  lea rax,[0xF55CD23]
0x4e1a707  mov rsi,0xFF00FFFFFFFFFFFF
0x4e1a711  and rax,rsi
0x4e1a714  mov rcx,0xD000000000000
0x4e1a71e  or rcx,rax
0x4e1a721  mov [rbp+0x2D0],rcx
0x4e1a728  mov byte ptr [rbp+0x140],0

### Phase 9 — 0x4e1a72f..0x4e1a75f (piece 2 of 5)
0x4e1a72f..0x4e1a75f: Call 0x3D2D90 with rcx=&[rbp+0x10], rdx=&[rbp+0x130], r8=&[rbp+0x2D0] [V]; test bit 0x37 of [rbp+0x2D0] and, when clear, mask rdx with rsi, subtract 8, and indirect-call through [[0x1233E1A8]+0x20] via IAT slot [0xF99FFA0] [V].
0x4e1a72f  lea rcx,[rbp+0x10]
0x4e1a733  lea rdx,[rbp+0x130]
0x4e1a73a  lea r8,[rbp+0x2D0]
0x4e1a741  call 0x3D2D90
0x4e1a746  nop
0x4e1a747  mov rdx,[rbp+0x2D0]
0x4e1a74e  bt rdx,0x37
0x4e1a753  jae short 0x4E1A771
0x4e1a755  mov rcx,[0x1233E1A8]
0x4e1a75c  and rdx,rsi
0x4e1a75f  add rdx,0xFFFFFFFFFFFFFFF8
0x4e1a763  mov rax,[rcx]
0x4e1a766  mov rax,[rax+0x20]
0x4e1a76a  call qword ptr [0xF99FFA0]
0x4e1a770  nop

### Phase 10 — 0x4e1a771..0x4e1a814 (piece 3 of 5)
0x4e1a771..0x4e1a814: Call 0xE931580 on &[rbp+0x2D0] with edx=0 [V], call 0xE932FA0 with rcx=[rbp+0x350], rdx=&[rbp+0x130], r9=&[rbp+0x2D0], r8=0xF5B7B8A [V], then call 0xE932200 on &[rbp+0x130] with edx=0 [V].
0x4e1a771  lea rcx,[rbp+0x2D0]
0x4e1a778  xor edx,edx
0x4e1a77a  call 0xE931580
0x4e1a77f  nop
0x4e1a780  lea r8,[0xF5B7B8A]
0x4e1a787  lea rdx,[rbp+0x130]
0x4e1a78e  lea r9,[rbp+0x2D0]
0x4e1a795  mov rcx,[rbp+0x350]
0x4e1a79c  call 0xE932FA0
0x4e1a7a1  nop
0x4e1a7a2  lea rcx,[rbp+0x130]
0x4e1a7a9  xor edx,edx
0x4e1a7ab  call 0xE932200
0x4e1a7b0  nop

### Phase 11 — 0x4e1a7b1..0x4e1a805 (piece 3 of 5)
0x4e1a7b1..0x4e1a805: Store eax to [[rbp+0x358]+0xF8] [V], release &[rbp+0x130] and &[rbp+0x2D0] via 0xE9319A0 [V], re-arm [rbp+0x2D0] with 0xE931580(edx=1) [V], then call 0xE932FA0 with r8=0xF5515C8 [V].
0x4e1a7b1  mov rcx,[rbp+0x358]
0x4e1a7b8  mov [rcx+0xF8],eax
0x4e1a7be  lea rcx,[rbp+0x130]
0x4e1a7c5  call 0xE9319A0
0x4e1a7ca  lea rcx,[rbp+0x2D0]
0x4e1a7d1  call 0xE9319A0
0x4e1a7d6  nop
0x4e1a7d7  lea rcx,[rbp+0x2D0]
0x4e1a7de  mov edx,1
0x4e1a7e3  call 0xE931580
0x4e1a7e8  nop
0x4e1a7e9  lea r8,[0xF5515C8]
0x4e1a7f0  lea rdx,[rbp+0x130]
0x4e1a7f7  lea r9,[rbp+0x2D0]
0x4e1a7fe  mov rcx,[rbp+0x350]
0x4e1a805  call 0xE932FA0

### Phase 12 — 0x4e1a80a..0x4e1a875 (piece 3 of 5)
0x4e1a80a..0x4e1a875: Call 0xE932200 on &[rbp+0x130] with edx=0 [V], store eax to [[rbp+0x358]+0xFC] [V], release both stack objects again via 0xE9319A0 [V], call 0xE9315D0 with rcx=&[rbp+0x310], rdx=0xF847A07 [V], then 0xE932FA0 with r8=0xF5634A2, rdx=&[rbp+0x2D0], r9=&[rbp+0x310] [V].
0x4e1a80a  nop
0x4e1a80b  lea rcx,[rbp+0x130]
0x4e1a812  xor edx,edx
0x4e1a814  call 0xE932200
0x4e1a819  nop
0x4e1a81a  mov rcx,[rbp+0x358]
0x4e1a821  mov [rcx+0xFC],eax
0x4e1a827  lea rcx,[rbp+0x130]
0x4e1a82e  call 0xE9319A0
0x4e1a833  lea rcx,[rbp+0x2D0]
0x4e1a83a  call 0xE9319A0
0x4e1a83f  nop
0x4e1a840  lea rdx,[0xF847A07]
0x4e1a847  lea rcx,[rbp+0x310]
0x4e1a84e  call 0xE9315D0
0x4e1a853  nop
0x4e1a854  lea r8,[0xF5634A2]
0x4e1a85b  lea rdx,[rbp+0x2D0]
0x4e1a862  lea r9,[rbp+0x310]
0x4e1a869  mov rcx,[rbp+0x350]
0x4e1a870  call 0xE932FA0
0x4e1a875  nop

### Phase 13 — 0x4e1a876..0x4e1a88b (piece 3 of 5)
0x4e1a876..0x4e1a88b: Reset the SSO string: movaps zeroes [rbp+0x130], qword [rbp+0x140] = 0, qword [rbp+0x148] = 0xF [V].
0x4e1a876  xorps xmm0,xmm0
0x4e1a879  movaps [rbp+0x130],xmm0
0x4e1a880  mov qword ptr [rbp+0x140],0
0x4e1a88b  mov qword ptr [rbp+0x148],0xF

### Phase 14 — 0x4e1a896..0x4e1a8d3 (piece 4 of 5)
0x4e1a896..0x4e1a8d3: Copy [rbp+0x68..0x78) into the SSO buffer [rbp+0x130] via 0xE932140 [V]; load capacity [rbp+0x148], load qword [rbp+0x130] into rcx [V], and when capacity is at least 0x10 and capacity+1 is at least 0x1000 take the heap path [V].
0x4e1a896  lea rcx,[rbp+0x2D0]
0x4e1a89d  lea rdi,[rbp+0x68]
0x4e1a8a1  lea rsi,[rbp+0x130]
0x4e1a8a8  mov rdx,rdi
0x4e1a8ab  mov r8,rsi
0x4e1a8ae  call 0xE932140
0x4e1a8b3  nop
0x4e1a8b4  mov rax,[rbp+0x148]
0x4e1a8bb  cmp rax,0x10
0x4e1a8bf  jb short 0x4E1A8F9
0x4e1a8c1  mov rcx,[rbp+0x130]
0x4e1a8c8  lea rdx,[rax+1]
0x4e1a8cc  cmp rdx,0x1000
0x4e1a8d3  jb short 0x4E1A8F4

### Phase 15 — 0x4e1a8d5..0x4e1a90c (piece 4 of 5)
0x4e1a8d5..0x4e1a90c: Heap free: read the size header [rcx-8] [V], reject the block when (rcx-8)-header >= 0x20 (jump 0x4E1BFC5) [V], then free via 0xE935700 with the adjusted pointer [V] and release &[rbp+0x2D0] and &[rbp+0x310] [V].
0x4e1a8d5  mov r8,[rcx-8]
0x4e1a8d9  add rcx,0xFFFFFFFFFFFFFFF8
0x4e1a8dd  sub rcx,r8
0x4e1a8e0  cmp rcx,0x20
0x4e1a8e4  jae 0x4E1BFC5
0x4e1a8ea  add rax,0x28
0x4e1a8ee  mov rdx,rax
0x4e1a8f1  mov rcx,r8
0x4e1a8f4  call 0xE935700
0x4e1a8f9  lea rcx,[rbp+0x2D0]
0x4e1a900  call 0xE9319A0
0x4e1a905  lea rcx,[rbp+0x310]
0x4e1a90c  call 0xE9319A0

### Phase 16 — 0x4e1a911..0x4e1a969 (piece 4 of 5)
0x4e1a911..0x4e1a969: If [rbp+0x78] is zero jump to 0x4E1AA70 [V]; otherwise r14 = [rbp+0x78]-1, capture r13=[rbp+0x68] and rbx=[rbp+0x80] [V], and compute capacity r15 = 0xF, or r14|0xF when that value is >= 0x17; sizes below 0xFFF take the small path [V].
0x4e1a911  mov rax,[rbp+0x78]
0x4e1a915  test rax,rax
0x4e1a918  je 0x4E1AA70
0x4e1a91e  xorps xmm0,xmm0
0x4e1a921  movaps [rbp+0x130],xmm0
0x4e1a928  mov r14,rax
0x4e1a92b  dec r14
0x4e1a92e  js 0x4E1BFDF
0x4e1a934  mov r13,[rbp+0x68]
0x4e1a938  mov rbx,[rbp+0x80]
0x4e1a93f  mov r15d,0xF
0x4e1a945  mov r12,rsi
0x4e1a948  cmp rax,0x11
0x4e1a94c  jb short 0x4E1A99B
0x4e1a94e  mov rax,r14
0x4e1a951  or rax,0xF
0x4e1a955  cmp rax,0x17
0x4e1a959  mov r15d,0x16
0x4e1a95f  cmovae r15,rax
0x4e1a963  cmp rax,0xFFF
0x4e1a969  jb short 0x4E1A987

### Phase 17 — 0x4e1a987..0x4e1a994 (piece 4 of 5)
0x4e1a987..0x4e1a994: Large path: malloc 0x392920 with r15+0x28 [V], align r12 up to 32 bytes and save the base pointer at [r12-8] [V]; small path: allocate r15+1 bytes and store the pointer at [rbp+0x130] [V].
0x4e1a96b  lea rcx,[r15+0x28]
0x4e1a96f  call 0x392920
0x4e1a974  nop
0x4e1a975  mov r12,rax
0x4e1a978  add r12,0x27
0x4e1a97c  and r12,0xFFFFFFFFFFFFFFE0
0x4e1a980  mov [r12-8],rax
0x4e1a985  jmp short 0x4E1A994
0x4e1a987  lea rcx,[r15+1]
0x4e1a98b  call 0x392920
0x4e1a990  nop
0x4e1a991  mov r12,rax
0x4e1a994  mov [rbp+0x130],r12

### Phase 18 — 0x4e1a99b..0x4e1a9c2 (piece 5 of 5)
0x4e1a99b..0x4e1a9c2: Set rdi = (rbx >= 0x10) ? r13 : rdi and increment it [V], store size r14 to [rbp+0x140] and capacity r15 to [rbp+0x148] [V], call 0xEEC6EC0 with rcx=r12, rdx=rdi, r8=r14 [V], and write byte 0 to [r12+r14] [V].
0x4e1a99b  cmp rbx,0x10
0x4e1a99f  cmovae rdi,r13
0x4e1a9a3  inc rdi
0x4e1a9a6  mov [rbp+0x140],r14
0x4e1a9ad  mov [rbp+0x148],r15
0x4e1a9b4  mov rcx,r12
0x4e1a9b7  mov rdx,rdi
0x4e1a9ba  mov r8,r14
0x4e1a9bd  call 0xEEC6EC0
0x4e1a9c2  mov byte ptr [r12+r14],0

## Field table — every [reg+off] store/load in slice 0x4e1a52a..0x4e1a9c2

| offset | size | read/store address | verbatim `0xRVA  instr` line(s) | meaning |
|---|---|---|---|---|
| r12+0 | 8 | R [r12] @ 0x4e1a52c | `0x4e1a52c  mov rax,[r12]` | - |
| rax+0x5C | 2, 2 | R [rax+0x5C] @ 0x4e1a530; W [rax+0x5C] @ 0x4e1a547 | `0x4e1a530  movzx edx,word ptr [rax+0x5C]<br>0x4e1a547  mov word ptr [rax+0x5C],0xFFFF` | word field forced to 0xFFFF |
| rbp+0x358 | 8, 8, 8, 8 | R [rbp+0x358] @ 0x4e1a54f; R [rbp+0x358] @ 0x4e1a581; R [rbp+0x358] @ 0x4e1a7b1; R [rbp+0x358] @ 0x4e1a81a | `0x4e1a54f  mov rax,[rbp+0x358]<br>0x4e1a581  mov rcx,[rbp+0x358]<br>0x4e1a7b1  mov rcx,[rbp+0x358]<br>0x4e1a81a  mov rcx,[rbp+0x358]` | - |
| rax+0x100 | 8 | R [rax+0x100] @ 0x4e1a556 | `0x4e1a556  mov rsi,[rax+0x100]` | - |
| rax+0x108 | 8 | R [rax+0x108] @ 0x4e1a55d | `0x4e1a55d  mov rdi,[rax+0x108]` | - |
| rbp+0x170 | 16, 16, 8 | W [rbp+0x170] @ 0x4e1a599; W [rbp+0x170] @ 0x4e1a5ef; R [rbp+0x170] @ 0x4e1a6c8 | `0x4e1a599  movaps [rbp+0x170],xmm6<br>0x4e1a5ef  movaps [rbp+0x170],xmm6<br>0x4e1a6c8  mov rdx,[rbp+0x170]` | - |
| rbp+0x160 | 16 | W [rbp+0x160] @ 0x4e1a5a0 | `0x4e1a5a0  movaps [rbp+0x160],xmm6` | - |
| rbp+0x150 | 16 | W [rbp+0x150] @ 0x4e1a5a7 | `0x4e1a5a7  movaps [rbp+0x150],xmm6` | - |
| rbp+0x140 | 16, 1, 8, 8 | W [rbp+0x140] @ 0x4e1a5ae; W [rbp+0x140] @ 0x4e1a728; W [rbp+0x140] @ 0x4e1a88b; W [rbp+0x140] @ 0x4e1a9a6 | `0x4e1a5ae  movaps [rbp+0x140],xmm6<br>0x4e1a728  mov byte ptr [rbp+0x140],0<br>0x4e1a88b  mov qword ptr [rbp+0x140],0<br>0x4e1a9a6  mov [rbp+0x140],r14` | - |
| rbp+0x130 | 16, 4, 8, 16, 16, 8 | W [rbp+0x130] @ 0x4e1a5b5; R [rbp+0x130] @ 0x4e1a61c; R [rbp+0x130] @ 0x4e1a8c1; W [rbp+0x130] @ 0x4e1a879; W [rbp+0x130] @ 0x4e1a921; W [rbp+0x130] @ 0x4e1a994 | `0x4e1a5b5  movaps [rbp+0x130],xmm6<br>0x4e1a61c  mov eax,[rbp+0x130]<br>0x4e1a8c1  mov rcx,[rbp+0x130]<br>0x4e1a879  movaps [rbp+0x130],xmm0<br>0x4e1a921  movaps [rbp+0x130],xmm0<br>0x4e1a994  mov [rbp+0x130],r12` | - |
| rbp+0x180 | 8, 8 | W [rbp+0x180] @ 0x4e1a5bc; W [rbp+0x180] @ 0x4e1a5f6 | `0x4e1a5bc  mov qword ptr [rbp+0x180],0<br>0x4e1a5f6  mov qword ptr [rbp+0x180],0` | - |
| rbp+0x2D0 | 4, 8, 8, 8 | W [rbp+0x2D0] @ 0x4e1a5c7; W [rbp+0x2D0] @ 0x4e1a615; W [rbp+0x2D0] @ 0x4e1a721; R [rbp+0x2D0] @ 0x4e1a747 | `0x4e1a5c7  mov dword ptr [rbp+0x2D0],0<br>0x4e1a615  mov [rbp+0x2D0],rsi<br>0x4e1a721  mov [rbp+0x2D0],rcx<br>0x4e1a747  mov rdx,[rbp+0x2D0]` | - |
| rsi+0 | 4, 4 | W [rsi] @ 0x4e1a622; R [rsi] @ 0x4e1a661 | `0x4e1a622  mov [rsi],eax<br>0x4e1a661  divss xmm0,[rsi]` | dword copied from [rbp+0x130], then read as the divss divisor |
| rbp+0x138 | 8 | R [rbp+0x138] @ 0x4e1a628 | `0x4e1a628  mov r8,[rbp+0x138]` | - |
| r8+0 | 8 | R [r8] @ 0x4e1a62f | `0x4e1a62f  mov rdx,[r8]` | - |
| rsi+0x10 | 8 | R [rsi+0x10] @ 0x4e1a638 | `0x4e1a638  mov rax,[rsi+0x10]` | - |
| rsi+0x38 | 8 | R [rsi+0x38] @ 0x4e1a63c | `0x4e1a63c  mov rdi,[rsi+0x38]` | - |
| rbp+0x178 | 8 | R [rbp+0x178] @ 0x4e1a6cf | `0x4e1a6cf  mov r8,[rbp+0x178]` | - |
| rcx+0xF8 | 4 | W [rcx+0xF8] @ 0x4e1a7b8 | `0x4e1a7b8  mov [rcx+0xF8],eax` | - |
| rcx+0xFC | 4 | W [rcx+0xFC] @ 0x4e1a821 | `0x4e1a821  mov [rcx+0xFC],eax` | - |
| rbp+0x148 | 8, 8, 8 | W [rbp+0x148] @ 0x4e1a88b; R [rbp+0x148] @ 0x4e1a8b4; W [rbp+0x148] @ 0x4e1a9ad | `0x4e1a88b  mov qword ptr [rbp+0x148],0xF<br>0x4e1a8b4  mov rax,[rbp+0x148]<br>0x4e1a9ad  mov [rbp+0x148],r15` | - |
| rcx-8 | 8 | R [rcx-8] @ 0x4e1a8d5 | `0x4e1a8d5  mov r8,[rcx-8]` | - |
| rbp+0x78 | 8 | R [rbp+0x78] @ 0x4e1a911 | `0x4e1a911  mov rax,[rbp+0x78]` | - |
| rbp+0x68 | 8 | R [rbp+0x68] @ 0x4e1a934 | `0x4e1a934  mov r13,[rbp+0x68]` | - |
| rbp+0x80 | 8 | R [rbp+0x80] @ 0x4e1a938 | `0x4e1a938  mov rbx,[rbp+0x80]` | - |
| r12-8 | 8 | W [r12-8] @ 0x4e1a980 | `0x4e1a980  mov [r12-8],rax` | - |
| r12+r14 | 1 | W [r12+r14] @ 0x4e1a9c2 | `0x4e1a9c2  mov byte ptr [r12+r14],0` | byte 0 written at r12+r14 (NUL terminator) |

Notes on accesses not in the table (not [reg+off]): absolute-memory reads [0xEEE6700] (0x4e1a672 subss) and [0x1233E1A8] (0x4e1a755), and the IAT indirect call [0xF99FFA0] (0x4e1a76a); every lea (lea rcx,[rbp+0x10] @ 0x4e1a72f, lea rdx,[rbp+0x130] @ 0x4e1a733, lea r8,[rbp+0x2D0] @ 0x4e1a73a, lea rcx,[rbp+0x310] @ 0x4e1a847, lea rdx,[0xF847A07] @ 0x4e1a840, and others) computes an address without touching memory; push/pop stack accesses do not occur in this slice. No field names or string meanings appear in the slice, so unset meaning cells are '-'.
Listing note: at 0x4e1a8c1 the provided input line `0x4e1a8c1  lea rdx,[rax+1]` does not match the exe; the exe decodes `0x4e1a8c1  mov rcx,[rbp+0x130]` there, and `lea rdx,[rax+1]` really sits at 0x4e1a8c8 (the listing dropped that 7-byte instruction). The exe rendering is used in the phases and table above so every quoted line verifies against Minecraft.Windows.exe.

## TOOL REQUESTS

None.
