# Unit U-E4X-C1: chunk extractor body C, listing lines 1..700

Source: docs/data/listings/e4_C.txt (each line `0xRVA instruction`), Body C = 0x66f2820..0x66f4f5a per docs/functions/66ea3d0.md.
Context: entered from Phase 5 dispatch of 0x66ea3d0 when f16cf && K != 0xC and f1658 set; Body C is the f1658 inline body.
Tags: [V] = seen in this listing, [I] = inferred from structure, [?] = unknown.

## NEXT
Next line to do: 1 (phase lines 1..40 not yet written).

### lines 1..40

```
0x66f2820  mov rax,[rbp+0xEE8]
0x66f2827  mov r8,[rbp+0xEF0]
0x66f282e  mov [rbp+0xC78],rax
0x66f2835  lea rcx,[rbp+0xC80]
0x66f283c  lea rdx,[rbp+0xEF0]
0x66f2843  call 0xE86B370
0x66f2848  nop
0x66f2849  mov qword ptr [rbp+0xCF8],0
0x66f2854  mov rax,[rbx+0x48]
0x66f2858  mov rdx,[rax]
0x66f285b  lea rax,[rdx-5]
0x66f285f  xor r13d,r13d
0x66f2862  test rax,0xFFFFFFFFFFFFFFFB
0x66f2868  sete r15b
0x66f286c  cmp rdx,0xA
0x66f2870  je 0x66F2924
0x66f2876  mov byte ptr [rbp+0x16D0],9
0x66f287d  cmp rdx,0xC
0x66f2881  je 0x66F292B
0x66f2887  lea rax,[rdx-7]
0x66f288b  cmp rax,3
0x66f288f  setb al
0x66f2892  lea rcx,[rdx-0xF]
0x66f2896  cmp rcx,2
0x66f289a  setb cl
0x66f289d  or cl,al
0x66f289f  mov [rbp+0x16D0],cl
0x66f28a5  jmp 0x66F292B
0x66f28aa  mov r8,[r13+0x3B8]
0x66f28b1  add r13,0x3B0
0x66f28b8  mov [rsp+0x28],r13
0x66f28bd  lea rax,[rbp+0x1410]
0x66f28c4  mov [rsp+0x20],rax
0x66f28c9  lea r9,[rbp+0xEE8]
0x66f28d0  mov rcx,[rbp+0x16A8]
0x66f28d7  mov rdx,rbx
0x66f28da  call 0x67AA700
0x66f28df  nop
0x66f28e0  jmp 0x66F6E3B
```

Meaning: Body C prologue [V]: clones the pass record via 0xE86B370(&rec_c80 at [rbp+0xC80], &passRecord at [rbp+0xEF0]) and zeroes [rbp+0xCF8] [V]. Reads K = *(u64*)desc[+0x48] via rbx (description kept in rbx per dossier) [V]; fogA r15b = ((K-5) & ~4) == 0, i.e. K in {5,9} [V]. Computes kind class v at [rbp+0x16D0]: v=9 if K==0xC; else if K==10 v=2 (jump target 0x66f2924); else v = ((K-7)<3) | ((K-0xF)<2), i.e. K in {7,8,9,0xF,0x10} [V]. Falls through to binder call 0x67AA700(builder+0x3B8, ..., &passRecord_ee8) then jumps to exit tail 0x66F6E3B [V]. Roles of 0x67AA700 and the jump target are [I].

### lines 41..80

```
0x66f28e5  add rdx,rax
0x66f28e8  cmp rcx,rdx
0x66f28eb  jae 0x66F4FC4
0x66f28f1  sub ecx,eax
0x66f28f3  shr ecx,4
0x66f28f6  mov [rbp+0x16BC],cx
0x66f28fd  mov byte ptr [rbp+0x16BE],1
0x66f2904  lea rdx,[rbp+0x16BC]
0x66f290b  lea r8,[rbp+0xF70]
0x66f2912  lea rcx,[rbp+0xEF0]
0x66f2919  call 0x5679DB0
0x66f291e  nop
0x66f291f  jmp 0x66F4FCB
0x66f2924  mov byte ptr [rbp+0x16D0],2
0x66f292b  mov [rbp+0x16B0],rdx
0x66f2932  xorps xmm0,xmm0
0x66f2935  movaps [rbp+0x1670],xmm0
0x66f293c  mov qword ptr [rbp+0x1680],0
0x66f2947  mov rax,[rbp+0x16C0]
0x66f294e  mov rax,[rax+0x38]
0x66f2952  mov [rbp+0x1440],rax
0x66f2959  test rax,rax
0x66f295c  je short 0x66F2985
0x66f295e  mov rcx,0xAAAAAAAAAAAAAAB
0x66f2968  cmp rax,rcx
0x66f296b  jae 0x66F9210
0x66f2971  lea rcx,[rbp+0x1670]
0x66f2978  lea rdx,[rbp+0x1440]
0x66f297f  call 0x678D170
0x66f2984  nop
0x66f2985  mov rsi,[rbp+0x16A0]
0x66f298c  lea rdi,[rsi+0x2E8]
0x66f2993  mov rcx,rdi
0x66f2996  call 0xEEC59F0
0x66f299b  test eax,eax
0x66f299d  jne 0x66F8FB0
0x66f29a3  mov [rbp+0x1690],rdi
0x66f29aa  cmp dword ptr [rsi+0x334],0x7FFFFFFF
0x66f29b4  je 0x66F8FBB
0x66f29ba  mov rax,[rbp+0x16C0]
```

Meaning: FogAlpha-found path (jump target 0x66f28e5) [V]: slot index = (pointer difference) >> 4 stored at [rbp+0x16BC] (u16), fogAlphaFound byte [rbp+0x16BE] = 1, then 0x5679DB0(&passRecord_ef0, {slot,1}, {1,&vec4}) writes a zero vec4 into the FogAlpha uniform slot; jumps to body tail 0x66F4FCB [V]. Otherwise (K==10 target at 0x66f2924) sets v=2 at [rbp+0x16D0], stores K at [rbp+0x16B0] [V]. Zeroes the resolved-item vector struct at [rbp+0x1670] and size [rbp+0x1680] = 0 [V]. Loads draw-list count n = desc[+0x38] into [rbp+0x1440] [V]; if n != 0, bounds-checks n < 0xAAAAAAAAAAAAAAB (else throws at 0x66F9210) and calls 0x678D170(&vec_1670, &n) to reserve capacity [V]. Then acquires builder mutex at builder[+0x2E8] via 0xEEC59F0 (_Mtx_lock) [V]; on lock failure jumps to throw 0x66F8FB0; saves mutex addr at [rbp+0x1690]; checks recursion limit builder[+0x334] != 0x7FFFFFFF (else throw 0x66F8FBB) [V].

### lines 81..120

```
0x66f29ba  mov rax,[rbp+0x16C0]
0x66f29c1  mov rax,[rax+0x38]
0x66f29c5  test rax,rax
0x66f29c8  je 0x66F2C29
0x66f29ce  mov rcx,[rbp+0x16C0]
0x66f29d5  mov rdi,[rcx+0x40]
0x66f29d9  imul rsi,rax,0x58
0x66f29dd  add rsi,rdi
0x66f29e0  lea rbx,[rbp+0x1440]
0x66f29e7  lea r14,[rbp+0xF70]
0x66f29ee  xorps xmm6,xmm6
0x66f29f1  jmp short 0x66F2A0D
0x66f29f3  add rdx,0x18
0x66f29f7  mov [rbp+0x1678],rdx
0x66f29fe  xchg ax,ax
0x66f2a00  add rdi,0x58
0x66f2a04  cmp rdi,rsi
0x66f2a07  je 0x66F2C29
0x66f2a0d  movzx eax,byte ptr [rdi+0x28]
0x66f2a11  test eax,eax
0x66f2a13  je short 0x66F2A24
0x66f2a15  cmp eax,1
0x66f2a18  jne 0x66F862C
0x66f2a1e  lea rax,[rdi+0x18]
0x66f2a22  jmp short 0x66F2A28
0x66f2a24  lea rax,[rdi+0x10]
0x66f2a28  mov rax,[rax]
0x66f2a2b  test rax,rax
0x66f2a2e  je short 0x66F2A00
0x66f2a30  mov rcx,[rbp+0x16A0]
0x66f2a37  mov rdx,[rcx+0x2D8]
0x66f2a3e  mov r8,[rdx+8]
0x66f2a42  cmp byte ptr [r8+0x19],0
0x66f2a47  mov rcx,rdx
0x66f2a4a  jne short 0x66F2A7E
0x66f2a4c  mov r9,[rax]
0x66f2a4f  mov rcx,rdx
0x66f2a52  nop [rax+rax]
0x66f2a60  xor r10d,r10d
0x66f2a63  cmp [r8+0x20],r9
```

Meaning: Pass-1 entry resolution loop [V]. If n==0 skips to 0x66F2C29 [V]. Computes end = drawListBase + n*0x58 (stride 0x58 per entry) [V]; rbx = &vec_1670 head, r14 = staging [rbp+0xF70], xmm6 = zero [V]. Loop entry jumps to 0x66f2a0d; each iteration advances rdi by 0x58 until rdi == end [V]. Reads entry tag byte at [rdi+0x28]: tag==0 → value pointer at [rdi+0x10]; tag==1 → value at [rdi+0x18]; other → throw 0x66F862C [V]. Null value pointer skips entry [V]. Looks up key in builder[+0x2D8] red-black tree: root at [mapHeader+8], node+0x19 = isNil flag, node+0x20 = key; on nil root takes a comparison branch (shl r10d,4 / mov r8,[r8+r10]) to walk children [V]. Dedupes: compares resolved value against cached pair [rbp+0xF70] (xor-or test at 0x66f2aef..0x66f2b1f) [V]. Reads desc flag50 = byte [desc+0x50] and kind pointer = [desc+0x48] [V].

## NEXT
Next line to do: 121 (phase lines 121..160 not yet written).

### lines 121..160

```
0x66f2a6b  setl r10b
0x66f2a6f  shl r10d,4
0x66f2a73  mov r8,[r8+r10]
0x66f2a77  cmp byte ptr [r8+0x19],0
0x66f2a7c  je short 0x66F2A60
0x66f2a7e  cmp byte ptr [rcx+0x19],0
0x66f2a82  jne 0x66F2A00
0x66f2a88  cmp rcx,rdx
0x66f2a8b  je 0x66F2A00
0x66f2a91  mov rdx,[rcx+0x20]
0x66f2a95  cmp [rax],rdx
0x66f2a98  jl 0x66F2A00
0x66f2a9e  mov r12,[rcx+0x28]
0x66f2aa2  test r12,r12
0x66f2aa5  je 0x66F2A00
0x66f2aab  mov rcx,[rbp+0x16C0]
0x66f2ab2  movzx eax,byte ptr [rcx+0x50]
0x66f2ab6  mov rcx,[rcx+0x48]
0x66f2aba  lea rdx,[r12+8]
0x66f2abf  mov rcx,[rcx]
0x66f2ac2  mov [rbp+0xF70],rcx
0x66f2ac9  mov [rbp+0xF78],al
0x66f2acf  mov rcx,rbx
0x66f2ad2  mov r8,r14
0x66f2ad5  call 0xBC090B0
0x66f2ada  mov rcx,[rbp+0x1440]
0x66f2ae1  mov rax,[rbp+0x1448]
0x66f2ae8  mov rdx,[rbp+0x1450]
0x66f2aef  xor rdx,rcx
0x66f2af2  mov r8,[rbp+0x1458]
0x66f2af9  xor r8,rax
0x66f2afc  or r8,rdx
0x66f2aff  mov rdx,[r12+0x28]
0x66f2b04  cmove rax,rdx
0x66f2b08  sete r8b
0x66f2b0c  cmp rcx,[r12+0x10]
0x66f2b11  sete cl
0x66f2b14  or cl,r8b
0x66f2b17  cmp rax,rdx
0x66f2b1a  sete dl
```

Meaning: Tree walk continues [V]: setl r10b = (node.key < search key), shl r10d,4, mov r8,[r8+r10] selects child by comparison result (0x10-byte node stride) [V]. Loops while child isNil == 0 [V]. When found node not nil and != root, compares search key [rax] vs node key [rcx+0x20] via cmp/jl [V]. Extracts node value r12 = [rcx+0x28], null-checks [V]. Calls 0xBC090B0(&out1440 at [rbp+0x1440], node.value+8, {kind=desc+0x48, flag50}) to resolve (kind, flag50) → shared_ptr pair [V]. Dedupes: compares new pair {rax,rcx} vs cached pair at [rbp+0x1448/0x1450] via xor-or; sete r8b / sete cl / or cl,r8b computes "same pair" flag; cmp rax,rdx / sete dl compares first elements [V]. Stores cached pair ptr [rbp+0xF70] = node value, [rbp+0xF78] = flag50 byte [V].

## NEXT
Next line to do: 161 (phase lines 161..200 not yet written).

### lines 161..200

```
0x66f2b1d  test cl,dl
0x66f2b1f  je short 0x66F2B26
0x66f2b21  xor r12d,r12d
0x66f2b24  jmp short 0x66F2B56
0x66f2b26  movaps [rbp+0x1440],xmm6
0x66f2b2d  mov rcx,[rax+8]
0x66f2b31  test rcx,rcx
0x66f2b34  je short 0x66F2B40
0x66f2b36  lock inc dword ptr [rcx+8]
0x66f2b3a  mov rcx,[rax+8]
0x66f2b3e  jmp short 0x66F2B42
0x66f2b40  xor ecx,ecx
0x66f2b42  mov rax,[rax]
0x66f2b45  mov [rbp+0x1440],rax
0x66f2b4c  mov [rbp+0x1448],rcx
0x66f2b53  mov r12b,1
0x66f2b56  mov [rbp+0x1450],r12b
0x66f2b5d  mov rdx,[rbp+0x1678]
0x66f2b64  cmp rdx,[rbp+0x1680]
0x66f2b6b  je short 0x66F2BA4
0x66f2b6d  mov byte ptr [rdx+0x10],0
0x66f2b71  test r12b,r12b
0x66f2b74  je 0x66F29F3
0x66f2b7a  movups [rdx],xmm6
0x66f2b7d  mov rcx,[rbp+0x1448]
0x66f2b84  test rcx,rcx
0x66f2b87  je short 0x66F2BBF
0x66f2b89  lock inc dword ptr [rcx+8]
0x66f2b8d  mov rax,[rbp+0x1440]
0x66f2b94  mov r8,[rbp+0x1448]
0x66f2b9b  mov rcx,[rbp+0x1678]
0x66f2ba2  jmp short 0x66F2BC5
0x66f2ba4  lea rcx,[rbp+0x1670]
0x66f2bab  mov r8,rbx
0x66f2bae  call 0x678D3F0
0x66f2bb3  nop
0x66f2bb4  test r12b,r12b
0x66f2bb7  je 0x66F2A00
0x66f2bbd  jmp short 0x66F2BDB
0x66f2bbf  mov rcx,rdx
```

Meaning: Dedup result branch [V]: if pairs differ (test cl,dl != 0 → valid entry, r12b stays 1) goes to 0x66f2b26; else valid=0 (xor r12d,r12d) → 0x66f2b56 [V]. For valid entries: zeroes out vec slot [rbp+0x1440] (movaps xmm6 zero) [V]; loads shared_ptr ctrl block [rax+8], lock-inc refcount if non-null [V]; stores pair {rax, rcx} at [rbp+0x1440/0x1448], valid byte r12b=1 at [rbp+0x1450] [V]. Vector growth: rdx = [rbp+0x1678] (insert cursor), cmp vs [rbp+0x1680] (end); if equal (full) calls 0x678D3F0(&vec_1670, &rbx head) grow path [V]; else marks existing slot valid=0 then writes pair [rax, rcx] at slot, valid=1 [V]. On dedup-hit (r12b==0) loops back to next entry 0x66F2A00 [V].

## NEXT
Next line to do: 201 (phase lines 201..240 not yet written).

### lines 201..240

```
0x66f2bc2  xor r8d,r8d
0x66f2bc5  mov [rdx],rax
0x66f2bc8  mov [rdx+8],r8
0x66f2bcc  mov byte ptr [rdx+0x10],1
0x66f2bd0  add rcx,0x18
0x66f2bd4  mov [rbp+0x1678],rcx
0x66f2bdb  mov r12,[rbp+0x1448]
0x66f2be2  test r12,r12
0x66f2be5  je 0x66F2A00
0x66f2beb  lock dec dword ptr [r12+8]
0x66f2bf1  jne 0x66F2A00
0x66f2bf7  mov rax,[r12]
0x66f2bfb  mov rax,[rax]
0x66f2bfe  mov rcx,r12
0x66f2c01  call qword ptr [0xF99FFA0]
0x66f2c07  lock dec dword ptr [r12+0xC]
0x66f2c0d  jne 0x66F2A00
0x66f2c13  mov rax,[r12]
0x66f2c17  mov rax,[rax+8]
0x66f2c1b  mov rcx,r12
0x66f2c1e  call qword ptr [0xF99FFA0]
0x66f2c24  jmp 0x66F2A00
0x66f2c29  mov rax,[rbp+0x16B0]
0x66f2c30  and rax,0xFFFFFFFFFFFFFFFE
0x66f2c34  mov [rbp+0x1658],rax
0x66f2c3b  mov rcx,[rbp+0x1690]
0x66f2c42  call 0xEEC5A10
0x66f2c47  mov rdx,[rbp+0x16C0]
0x66f2c4e  mov rsi,[rdx+0x40]
0x66f2c52  imul rax,[rdx+0x38],0x58
0x66f2c57  add rax,rsi
0x66f2c5a  mov [rbp+0x16A0],rax
0x66f2c61  lea rdi,[rbp+0x1444]
0x66f2c68  xor eax,eax
0x66f2c6a  movzx ecx,byte ptr [rbp+0x16D0]
0x66f2c71  cmp cl,2
0x66f2c74  sete al
0x66f2c77  shl eax,0xB
0x66f2c7a  cmp cl,9
0x66f2c7d  mov ecx,0x2800
```

Meaning: Vector slot commit [V]: writes resolved pair {rax, 0} into slot [rdx], valid byte = 1, advances insert cursor by 0x18 (shared_ptr pair size) [V]. Releases old cached pair: lock-dec ctrl+8; if reaches 0, calls destructor via [0xF99FFA0] vtable, then lock-dec ctrl+0xC and destroy again [V] (shared_ptr release). Pass-1 loop ends: jumps back to 0x66F2A00 for next entry [V]. After loop (target 0x66f2c29): K_and_mask = K & ~0xFFFFFFFFFFFFFFFE stored at [rbp+0x1658] (clears low bit of K) [V]. Releases builder mutex via 0xEEC5A10 (_Mtx_unlock) [V]. Computes pass-2 end = drawListBase + n*0x58 at [rbp+0x16A0] [V]. rdi = &[rbp+0x1444] (render-state staging). Computes render-state word base: (v==2 ? 0x800 : 0) << 0xB; if v==9 uses 0x2800 instead (cmovne) [V].

## NEXT
Next line to do: 241 (phase lines 241..280 not yet written).

### lines 241..280

```
0x66f2c85  lea rax,[rdx+0x78]
0x66f2c89  mov [rbp+0x1388],rax
0x66f2c90  mov r13b,r15b
0x66f2c93  lea eax,[rcx+r13*4+0x8101]
0x66f2c9b  mov [rbp+0x1688],eax
0x66f2ca1  lea r12,[rbp+0x1050]
0x66f2ca8  xorps xmm6,xmm6
0x66f2cab  movss xmm7,[0xEEC8060]
0x66f2cb3  movsd xmm8,[0xEFD32F0]
0x66f2cbc  movaps xmm9,[0xF0A4080]
0x66f2cc4  movss xmm10,[0xEEC8060]
0x66f2ccd  movsd xmm11,[0xEFD32F0]
0x66f2cd6  movss xmm13,[0xEFC13A4]
0x66f2cdf  movaps xmm14,[0xF0B8740]
0x66f2ce7  lea r13,[rbp+0x1210]
0x66f2cee  xor ebx,ebx
0x66f2cf0  jmp short 0x66F2D0E
0x66f2cf2  nop [rax+rax]
0x66f2d00  mov rbx,[rbp+0x1690]
0x66f2d07  inc rbx
0x66f2d0a  add rsi,0x58
0x66f2d0e  cmp rsi,[rbp+0x16A0]
0x66f2d15  je 0x66F4F5A
0x66f2d1b  movzx eax,byte ptr [rsi+0x28]
0x66f2d1f  test eax,eax
0x66f2d21  je short 0x66F2D38
0x66f2d23  cmp eax,1
0x66f2d26  jne 0x66F84B0
0x66f2d2c  lea rax,[rsi+0x18]
0x66f2d30  cmp qword ptr [rax],0
0x66f2d34  jne short 0x66F2D42
0x66f2d36  jmp short 0x66F2D0A
0x66f2d38  lea rax,[rsi+0x10]
0x66f2d3c  cmp qword ptr [rax],0
0x66f2d40  je short 0x66F2D0A
0x66f2d42  movsd xmm15,[rsi+0x3C]
0x66f2d48  mov dword ptr [rbp+0x1440],0x3F800000
0x66f2d52  movups [rdi],xmm6
0x66f2d55  mov dword ptr [rbp+0x1454],0x3F800000
0x66f2d5f  movups [rdi+0x14],xmm6
```

Meaning: Render-state word [rbp+0x1688] = 0x8101 + fogA*4 + (v==9 ? 0x2800 : (v==2 ? 0x800 : 0)) [V]; fogA=r15b from phase 1 [V]. Staging r12 = [rbp+0x1050] [V]. Constants loaded: xmm7=xmm10=1.0f (0xEEC8060), xmm8=xmm11 = double bits 0.0078125 (0xEFD32F0), xmm9 = {-0,-0,0,0} (0xF0A4080), xmm13 = 8.0f (0xEFC13A4), xmm14 = {8,8,0,0} (0xF0B8740) [V]. r13 = &[rbp+0x1210] (model matrix dst), ebx = entry index i = 0 [V]. Pass-2 loop: cmp rsi, end [rbp+0x16A0], je → body tail 0x66F4F5A [V]. Per entry: tag at [rsi+0x28] (0 → value +0x10, 1 → value +0x18, other → throw 0x66F84B0), null pointer skips entry [V]. Entry fields: xmm15 = *(float*)(entry+0x3C) [V]; staging [rbp+0x1440] = 0x3F800000 (1.0f), [rbp+0x1454] = 1.0f, [rdi] and [rdi+0x14] zeroed [V].

## NEXT
Next line to do: 281 (phase lines 281..320 not yet written).

### lines 281..320

```
0x66f2d63  movaps xmm0,xmm15
0x66f2d67  mulps xmm0,xmm6
0x66f2d6a  movaps xmm1,xmm0
0x66f2d6d  shufps xmm1,xmm0,0xE1
0x66f2d71  addps xmm1,xmm15
0x66f2d75  movss xmm12,[rsi+0x44]
0x66f2d7b  movaps xmm2,xmm12
0x66f2d7f  shufps xmm2,xmm12,0
0x66f2d84  mulps xmm2,xmm7
0x66f2d87  movaps xmm3,xmm0
0x66f2d8a  shufps xmm3,xmm0,0x55
0x66f2d8e  unpcklps xmm0,xmm0
0x66f2d91  addps xmm0,xmm3
0x66f2d94  addps xmm0,xmm2
0x66f2d97  addps xmm0,xmm8
0x66f2d9b  shufps xmm2,xmm2,0x55
0x66f2d9f  addps xmm2,xmm1
0x66f2da2  movaps xmm1,xmm9
0x66f2da6  movlhps xmm1,xmm2
0x66f2da9  addps xmm1,xmm7
0x66f2dac  movups [rbp+0x1468],xmm1
0x66f2db3  movlps [rbp+0x1478],xmm0
0x66f2dba  lea rcx,[rbp+0xE10]
0x66f2dc1  mov rdx,[rbp+0x1388]
0x66f2dc8  lea r8,[rbp+0x1440]
0x66f2dcf  call 0xAA6580
0x66f2dd4  nop
0x66f2dd5  movss xmm0,[rsi+0x48]
0x66f2dda  ucomiss xmm0,xmm10
0x66f2dde  jne short 0x66F2DE6
0x66f2de0  jnp 0x66F2E7A
0x66f2de6  movaps xmm1,xmm0
0x66f2de9  shufps xmm1,xmm0,0
0x66f2ded  mulps xmm1,xmm7
0x66f2df0  movss [rbp+0x1440],xmm0
0x66f2df8  movq xmm2,xmm1
0x66f2dfc  shufps xmm1,xmm1,0x55
0x66f2e00  movups [rbp+0x1444],xmm1
0x66f2e07  movss [rbp+0x1454],xmm0
0x66f2e0f  movups [rbp+0x1458],xmm1
```

Meaning: Translation matrix build [V]: xmm15 = (entry+0x3C) float2 (a,b); xmm0 = xmm15*0 (zero), xmm1 = shuffle(xmm0,0xE1) + xmm15 → builds row with {a,b,0,0} pattern; xmm12 = *(float*)(entry+0x44) = z, splatted, *1.0f; constructs translation T with k12=a, k13=b, k14=z into [rbp+0x1468]/[rbp+0x1478] (vec4 rows) [V]. Calls 0xAA6580(&model at [rbp+0xE10], descMat=[rbp+0x1388], &T=[rbp+0x1440]) → model = descMat * T [V]. Scale branch: xmm0 = *(float*)(entry+0x48), ucomiss vs 1.0f; if != 1.0f goes to scale path (0x66F2DE6): splat scale, mulps by 1.0f, builds scale matrix at [rbp+0x1440/0x1444/0x1454/0x1458] [V]; if == 1.0f falls through to 0x66F2E7A [I].

## NEXT
Next line to do: 321 (phase lines 321..360 not yet written).

### lines 321..360

```
0x66f2e16  movdqu [rbp+0x1468],xmm2
0x66f2e1e  movsd [rbp+0x1478],xmm11
0x66f2e27  lea rcx,[rbp+0xF70]
0x66f2e2e  lea rdx,[rbp+0xE10]
0x66f2e35  lea r8,[rbp+0x1440]
0x66f2e3c  call 0xAA6580
0x66f2e41  nop
0x66f2e42  movaps xmm0,[rbp+0xF70]
0x66f2e49  movaps xmm1,[rbp+0xF80]
0x66f2e50  movaps xmm2,[rbp+0xF90]
0x66f2e57  movaps xmm3,[rbp+0xFA0]
0x66f2e5e  movaps [rbp+0xE10],xmm0
0x66f2e65  movaps [rbp+0xE20],xmm1
0x66f2e6c  movaps [rbp+0xE30],xmm2
0x66f2e73  movaps [rbp+0xE40],xmm3
0x66f2e7a  mov rax,[rbp+0x16A8]
0x66f2e81  mov rdx,[rax]
0x66f2e84  mov [rsp+0x20],rsi
0x66f2e89  lea rcx,[rbp+0xDB8]
0x66f2e90  mov r8,[rbp+0x1698]
0x66f2e97  lea r9,[rbp+0xEE8]
0x66f2e9e  call 0x678C4C0
0x66f2ea3  nop
0x66f2ea4  lea rax,[rbp+0xC78]
0x66f2eab  mov [rbp+0x1650],rax
0x66f2eb2  cmp byte ptr [rbp+0x16BE],1
0x66f2eb9  jne short 0x66F2F15
0x66f2ebb  movss xmm0,[rsi+0x4C]
0x66f2ec0  xorps xmm1,xmm1
0x66f2ec3  ucomiss xmm0,xmm1
0x66f2ec6  jbe short 0x66F2F15
0x66f2ec8  shufps xmm0,xmm0,0
0x66f2ecc  movaps [rbp+0x1440],xmm0
0x66f2ed3  mov qword ptr [rbp+0xF70],1
0x66f2ede  lea rax,[rbp+0x1440]
0x66f2ee5  mov [rbp+0xF78],rax
0x66f2eec  lea rcx,[rbp+0xEF0]
0x66f2ef3  lea rdx,[rbp+0x16BC]
0x66f2efa  lea r8,[rbp+0xF70]
0x66f2f01  call 0x5679DB0
```

Meaning: If scale != 1.0f (fall-through from 0x66f2de0 jnp → 0x66f2e7a path), scale matrix already at [rbp+0x1440..0x1458] is multiplied: 0xAA6580(&f70=[rbp+0xF70], &model=[rbp+0xE10], &S=[rbp+0x1440]) → model = model * S [V]; result copied back [rbp+0xE10..0xE40] from [rbp+0xF70..0xFF0] (4x movaps) [V]. Draw-list build: 0x678C4C0(&drawlist=[rbp+0xDB8], ctx=[rbp+0x16A8], fogA=[rbp+0x1388], &passRecord_ee8=[rbp+0xEE8], entry=rsi) [V]. [rbp+0x1650] = &rec_c78 ([rbp+0xC78]) then = &passRecord_ee8 depending on FogAlpha path [V]. FogAlpha per entry: if fogAlphaFound byte [rbp+0x16BE]==1 and *(float*)(entry+0x4C) > 0: splat that float, [rbp+0xF70]=1 (u64), [rbp+0xF78]=&[rbp+0x1440], calls 0x5679DB0(&passRecord_ef0, {slot16bc,1}, {1,&vec4}) writes per-entry FogAlpha [V]; [rbp+0x1650] restored to &passRecord_ee8 [V].

## NEXT
Next line to do: 361 (phase lines 361..400 not yet written).

### lines 361..400

```
0x66f2f06  nop
0x66f2f07  lea rax,[rbp+0xEE8]
0x66f2f0e  mov [rbp+0x1650],rax
0x66f2f15  lea rax,[rbp+0x1410]
0x66f2f1c  mov [rbp+0xEA8],rax
0x66f2f23  lea rax,[rbp+0xE10]
0x66f2f2a  mov [rbp+0xEB0],rax
0x66f2f31  lea rax,[rbp+0xDB8]
0x66f2f38  mov [rbp+0xEB8],rax
0x66f2f3f  lea rax,[rbp+0x1650]
0x66f2f46  mov [rbp+0xEC0],rax
0x66f2f4d  mov rax,[rbp+0x1670]
0x66f2f54  mov [rbp+0x1690],rbx
0x66f2f5b  lea rcx,[rbx+rbx*2]
0x66f2f5f  mov byte ptr [rbp+0x1430],0
0x66f2f66  movzx ebx,byte ptr [rax+rcx*8+0x10]
0x66f2f6b  cmp bl,1
0x66f2f6e  jne short 0x66F2FA8
0x66f2f70  lea rax,[rax+rcx*8]
0x66f2f74  movaps [rbp+0x1420],xmm6
0x66f2f7b  mov rcx,[rax+8]
0x66f2f7f  test rcx,rcx
0x66f2f82  je short 0x66F2F8E
0x66f2f84  lock inc dword ptr [rcx+8]
0x66f2f88  mov rcx,[rax+8]
0x66f2f8c  jmp short 0x66F2F90
0x66f2f8e  xor ecx,ecx
0x66f2f90  mov rax,[rax]
0x66f2f93  mov [rbp+0x1420],rax
0x66f2f9a  mov [rbp+0x1428],rcx
0x66f2fa1  mov byte ptr [rbp+0x1430],1
0x66f2fa8  cmp qword ptr [rbp+0x1658],2
0x66f2fb0  sete cl
0x66f2fb3  mov eax,ebx
0x66f2fb5  xor al,1
0x66f2fb7  or al,cl
0x66f2fb9  movzx ecx,byte ptr [rbp+0x1368]
0x66f2fc0  test [rbp+0x16CF],cl
0x66f2fc6  je 0x66F320C
0x66f2fcc  test al,al
```

Meaning: Pack draw-item input block [rbp+0xea8..0xec0]: [rbp+0xEA8]=&[rbp+0x1410] (uv/offset), [rbp+0xEB0]=&[rbp+0xE10] (model), [rbp+0xEB8]=&[rbp+0xDB8] (drawlist), [rbp+0xEC0]=&[rbp+0x1650] (pass record) [V]. Takes vec1670[i]: rbx = entry index i, rcx = i*3 (3*8=24-byte stride? lea rcx,[rbx+rbx*2] = i*3), reads valid byte at [rax + rcx*8 + 0x10] where rax=&vec1670 → each ResolvedItem is 0x18 bytes (shared_ptr{ptr,ctrl} + u8 valid at +0x10) per dossier [V]. If valid==1: lock-inc shared_ptr ctrl, copy {ptr,ctrl} into [rbp+0x1420/0x1428], valid byte [rbp+0x1430]=1 [V]. Kind-class test: (K&~1)==2? sete cl → isKind2; al = valid ^ 1; al |= cl → proceed flag [V]. If [rbp+0x16CF] & isAB byte [rbp+0x1368] == 0 → jump 0x66F320C [V].

## NEXT
Next line to do: 401 (phase lines 401..440 not yet written).

### lines 401..440

```
0x66f2fce  je 0x66F332B
0x66f2fd4  addss xmm12,xmm13
0x66f2fd9  addps xmm15,xmm14
0x66f2fdd  cmp qword ptr [rbp+0x1658],2
0x66f2fe5  jne 0x66F33C0
0x66f2feb  test bl,bl
0x66f2fed  je 0x66F33C0
0x66f2ff3  movlps [rbp+0x1390],xmm15
0x66f2ffb  movss [rbp+0x1398],xmm12
0x66f3004  lea rcx,[rbp+0xEA8]
0x66f300b  lea rdx,[rbp+0x1130]
0x66f3012  call 0x67A75D0
0x66f3017  nop
0x66f3018  lea rbx,[rbp+0xF70]
0x66f301f  lea rax,[rbp+0x1390]
0x66f3026  mov [rsp+0x20],rax
0x66f302b  mov rcx,rbx
0x66f302e  lea rdx,[rbp+0x1210]
0x66f3035  lea r8,[rbp+0x11B8]
0x66f303c  lea r14,[rbp+0x1130]
0x66f3043  mov r9,r14
0x66f3046  call 0x678E1D0
0x66f304b  nop
0x66f304c  mov eax,[r13+0x60]
0x66f3050  mov [r12+0x70],eax
0x66f3055  movups xmm0,[r13+0x50]
0x66f305a  movups [r12+0x60],xmm0
0x66f3060  movzx eax,byte ptr [rbp+0x1274]
0x66f3067  mov [rbp+0x10C4],al
0x66f306d  movups xmm0,[rbp+0x1278]
0x66f3074  movups [rbp+0x10C8],xmm0
0x66f307b  movups xmm0,[r13+0x78]
0x66f3080  movups xmm1,[r13+0x88]
0x66f3088  movups xmm2,[r13+0x97]
0x66f3090  movups [r12+0xA7],xmm2
0x66f3099  movups [r12+0x98],xmm1
0x66f30a2  movups [r12+0x88],xmm0
0x66f30ab  movzx eax,word ptr [rbp+0x12B8]
0x66f30b2  mov [rbp+0x1108],ax
0x66f30b9  mov rcx,r14
```

Meaning: Kind==2 && valid path (0x66f2fd4..0x66f2ff3): xmm12 (z) += 8.0f (xmm13), xmm15 (vec2) += {8,8} (xmm14) — shift variant [V]; stores vec2/float at [rbp+0x1390/0x1398] [V]. If kind != 2 or not valid → 0x66F33C0 [V]. Descriptor prep: 0x67A75D0(&[rbp+0xEA8], &[rbp+0x1130]) builds ChunkDrawDescriptor [V]. Geometry/material call: 0x678E1D0(rcx=&[rbp+0xF70] staging, rdx=&[rbp+0x1210] model, r8=&[rbp+0x11B8], r9=&[rbp+0x1130] descriptor) [V]. Copies descriptor tail into staging [r12=rbp+0xF70]: [r12+0x70]=[r13+0x60], [r12+0x60]=[r13+0x50], byte [rbp+0x10C4]=[rbp+0x1274], [rbp+0x10C8]=[rbp+0x1278], descriptor bytes [r13+0x78/0x88/0x97] → [r12+0xA7/0x98/0x88], u16 [rbp+0x12B8] → [rbp+0x1108] [V].

## NEXT
Next line to do: 441 (phase lines 441..480 not yet written).

### lines 441..480

```
0x66f30bc  call 0x67E23F0
0x66f30c1  nop
0x66f30c2  mov [rsp+0x20],rbx
0x66f30c7  lea rcx,[rbp+0x1440]
0x66f30ce  lea rdx,[rbp+0x1060]
0x66f30d5  lea r8,[rbp+0x1008]
0x66f30dc  lea r9,[rbp+0xF80]
0x66f30e3  call 0x678E420
0x66f30e8  nop
0x66f30e9  mov eax,[r12+0x70]
0x66f30ee  lea rcx,[rbp+0x1580]
0x66f30f5  mov [rcx+0x10],eax
0x66f30f8  movups xmm0,[r12+0x60]
0x66f30fe  movups [rcx],xmm0
0x66f3101  movzx eax,byte ptr [rbp+0x10C4]
0x66f3108  mov [rbp+0x1594],al
0x66f310e  movups xmm0,[rbp+0x10C8]
0x66f3115  movups [rbp+0x1598],xmm0
0x66f311c  movups xmm0,[r12+0x88]
0x66f3125  movups xmm1,[r12+0x98]
0x66f312e  movups xmm2,[r12+0xA7]
0x66f3137  movups [rdi+0x183],xmm2
0x66f313e  movups [rdi+0x174],xmm1
0x66f3145  movups [rdi+0x164],xmm0
0x66f314c  movzx eax,word ptr [rbp+0x1108]
0x66f3153  mov [rbp+0x15D8],ax
0x66f315a  mov rax,[rbp+0x16A8]
0x66f3161  mov rcx,[rax+0x10]
0x66f3165  mov eax,0x9D0
0x66f316a  add rcx,rax
0x66f316d  call 0x5ABA5C0
0x66f3172  nop
0x66f3173  mov rbx,rax
0x66f3176  movups [r13-0x28],xmm6
0x66f317b  movups [r13-0x38],xmm6
0x66f3180  movups [r13-0x48],xmm6
0x66f3185  movups [r13-0x58],xmm6
0x66f318a  movups [r13-0x68],xmm6
0x66f318f  movups [r13-0x78],xmm6
0x66f3194  movups [r13-0x88],xmm6
```

Meaning: Geometry/material release: 0x67E23F0(&[rbp+0x1130]) releases descriptor ref [V]; 0x678E420(&[rbp+0x1440], &[rbp+0x1060], &[rbp+0x1008], &[rbp+0xF80]) assembles item state [V]. Copies descriptor fields into item staging [rbp+0x1580..]: u32 [r12+0x70] → [rcx+0x10], vec4 [r12+0x60] → [rcx], byte [rbp+0x10C4] → [rbp+0x1594], vec4 [rbp+0x10C8] → [rbp+0x1598], vec3s [r12+0x88/0x98/0xA7] → [rdi+0x164/0x174/0x183], u16 [rbp+0x1108] → [rbp+0x15D8] [V]. Pass allocation: pass = *(u64*)(*[rbp+0x16A8]+0x10) + 0x9D0 via 0x5ABA5C0 (thread-local getter) [V]; rbx = pass ptr [V]. Zeroes 12×16-byte DrawItem slots at [r13-0x28..-0xd8] with xmm6=0 [V].

## NEXT
Next line to do: 481 (phase lines 481..520 not yet written).

### lines 481..520

```
0x66f319c  movups [r13-0x98],xmm6
0x66f31a4  movups [r13-0xA8],xmm6
0x66f31ac  movups [r13-0xB8],xmm6
0x66f31b4  movups [r13-0xC8],xmm6
0x66f31bc  movups [r13-0xD8],xmm6
0x66f31c4  mov rcx,[0x1233E1B0]
0x66f31cb  mov rax,[rcx]
0x66f31ce  mov rax,[rax+0x10]
0x66f31d2  mov dl,0x4A
0x66f31d4  call qword ptr [0xF99FFA0]
0x66f31da  nop
0x66f31db  mov [rbp+0x16D4],al
0x66f31e1  mov rdx,[rbx+0x8A8]
0x66f31e8  cmp rdx,[rbx+0x8B0]
0x66f31ef  je 0x66F3FB8
0x66f31f5  movzx eax,word ptr [rbp+0x15D8]
0x66f31fc  mov [rdx],ax
0x66f31ff  add qword ptr [rbx+0x8A8],2
0x66f3207  jmp 0x66F3FCC
0x66f320c  test al,al
0x66f320e  je 0x66F3379
0x66f3214  cmp qword ptr [rbp+0x1658],2
0x66f321c  lea rdx,[rbp+0xF70]
0x66f3223  jne 0x66F3592
0x66f3229  test bl,bl
0x66f322b  je 0x66F3592
0x66f3231  lea rcx,[rbp+0xEA8]
0x66f3238  mov rbx,rdx
0x66f323b  call 0x67A75D0
0x66f3240  nop
0x66f3241  lea rcx,[rbp+0x1440]
0x66f3248  lea rdx,[rbp+0x1050]
0x66f324f  lea r8,[rbp+0xFF8]
0x66f3256  mov r9,rbx
0x66f3259  call 0x678F640
0x66f325e  nop
0x66f325f  mov eax,[r12+0x60]
0x66f3264  lea r8,[rbp+0x1578]
0x66f326b  mov [r8+0x10],eax
0x66f326f  movups xmm0,[r12+0x50]
```

Meaning: Feature flag query: vcall(*[0x1233E1B0])->+0x10)(dl=0x4A) → al = feature flag 0x4a, stored at [rbp+0x16D4] [V]. u16 pool push: [rbx+0x8A8] vs [rbx+0x8B0] bounds; if full → slow path 0x66F3FB8; else writes u16 [rbp+0x15D8] into pool at [rdx], advances pool write cursor by 2 [V]; jumps to 0x66F3FCC [V]. If proceed flag al==0 → 0x66F3379 [V]. If kind==2 && valid → descriptor pack path: 0x67A75D0(&[rbp+0xEA8], &[rbp+0x1050], r8=[rbp+0xFF8], r9=staging) then 0x678F640 (ChunkDrawDescriptor pack) [V]. Copies descriptor tail into staging [rbp+0x1578..]: u32 [r12+0x60] → [r8+0x10], vec4 [r12+0x50] → [r8] [V].

## NEXT
Next line to do: 521 (phase lines 521..560 not yet written).

### lines 521..560

```
0x66f3275  movups [r8],xmm0
0x66f3279  movzx eax,byte ptr [rbp+0x10B4]
0x66f3280  mov [rbp+0x158C],al
0x66f3286  movups xmm0,[rbp+0x10B8]
0x66f328d  movups [rbp+0x1590],xmm0
0x66f3294  movups xmm0,[r12+0x78]
0x66f329a  movups xmm1,[r12+0x88]
0x66f32a3  movups xmm2,[r12+0x97]
0x66f32ac  movups [rdi+0x17B],xmm2
0x66f32b3  movups [rdi+0x16C],xmm1
0x66f32ba  movups [rdi+0x15C],xmm0
0x66f32c1  movzx eax,word ptr [rbp+0x10F8]
0x66f32c8  mov [rbp+0x15D0],ax
0x66f32cf  mov rax,[rbp+0x16A8]
0x66f32d6  mov rcx,[rax+0x10]
0x66f32da  mov eax,0x9D0
0x66f32df  add rcx,rax
0x66f32e2  lea rax,[rbp+0x1448]
0x66f32e9  mov [rsp+0x28],rax
0x66f32ee  lea rax,[rbp+0x14D0]
0x66f32f5  mov [rsp+0x20],rax
0x66f32fa  lea rdx,[rbp+0x15D0]
0x66f3301  lea r9,[rbp+0x1528]
0x66f3308  call 0x67A8030
0x66f330d  nop
0x66f330e  lea rcx,[rbp+0x1440]
0x66f3315  call 0x67E1840
0x66f331a  lea rcx,[rbp+0xF70]
0x66f3321  call 0x67E23F0
0x66f3326  jmp 0x66F4E70
0x66f332b  movaps [rbp+0x1370],xmm6
0x66f3332  movaps [rbp+0x1660],xmm6
0x66f3339  cmp qword ptr [rbp+0x16B0],9
0x66f3341  lea r15,[rbp+0x1130]
0x66f3348  je short 0x66F3358
0x66f334a  cmp qword ptr [rbp+0x16B0],5
0x66f3352  jne 0x66F36A8
0x66f3358  mov rcx,[rbp+0x16C0]
0x66f335f  mov rax,[rcx+0x28]
0x66f3363  test rax,rax
```

Meaning: Staging item copy continues: byte [rbp+0x10B4] → [rbp+0x158C], vec4 [rbp+0x10B8] → [rbp+0x1590], vec3s [r12+0x78/0x88/0x97] → [rdi+0x15C/0x16C/0x17B], u16 [rbp+0x10F8] → [rbp+0x15D0] [V]. Second pass push: pass = *(u64*)(*[rbp+0x16A8]+0x10)+0x9D0; stack args {&[rbp+0x1448], &[rbp+0x14D0]}, rdx=&[rbp+0x15D0], r9=&[rbp+0x1528]; calls 0x67A8030 (binder) [V]; releases item 0x67E1840(&[rbp+0x1440]) and geometry 0x67E23F0(&[rbp+0xF70]) [V]; jumps to loop tail 0x66F4E70 [V]. Kind 9/5 seasons branch (0x66f332b): clears [rbp+0x1370] and [rbp+0x1660]; if K==9 or K==5 (else → 0x66F36A8 other path): takes shared_ptr at desc[+0x28] with lock-inc [V].

## NEXT
Next line to do: 561 (phase lines 561..600 not yet written).

### lines 561..600

```
0x66f3366  je 0x66F3694
0x66f336c  lock inc dword ptr [rax+8]
0x66f3370  mov rax,[rcx+0x28]
0x66f3374  jmp 0x66F3696
0x66f3379  movaps [rbp+0x1370],xmm6
0x66f3380  movaps [rbp+0x1660],xmm6
0x66f3387  cmp qword ptr [rbp+0x16B0],9
0x66f338f  je short 0x66F339F
0x66f3391  cmp qword ptr [rbp+0x16B0],5
0x66f3399  jne 0x66F44BC
0x66f339f  mov rcx,[rbp+0x16C0]
0x66f33a6  mov rax,[rcx+0x28]
0x66f33aa  test rax,rax
0x66f33ad  je 0x66F44A8
0x66f33b3  lock inc dword ptr [rax+8]
0x66f33b7  mov rax,[rcx+0x28]
0x66f33bb  jmp 0x66F44AA
0x66f33c0  movlps [rbp+0x1390],xmm15
0x66f33c8  movss [rbp+0x1398],xmm12
0x66f33d1  lea rcx,[rbp+0xEA8]
0x66f33d8  lea rdx,[rbp+0x1130]
0x66f33df  call 0x67A75D0
0x66f33e4  nop
0x66f33e5  lea r14,[rbp+0xF70]
0x66f33ec  lea rax,[rbp+0x1390]
0x66f33f3  mov [rsp+0x20],rax
0x66f33f8  mov rcx,r14
0x66f33fb  lea rdx,[rbp+0x1210]
0x66f3402  lea r8,[rbp+0x11B8]
0x66f3409  lea r15,[rbp+0x1130]
0x66f3410  mov r9,r15
0x66f3413  call 0x678E1D0
0x66f3418  nop
0x66f3419  mov eax,[r13+0x60]
0x66f341d  mov [r12+0x70],eax
0x66f3422  movups xmm0,[r13+0x50]
0x66f3427  movups [r12+0x60],xmm0
0x66f342d  movzx eax,byte ptr [rbp+0x1274]
0x66f3434  mov [rbp+0x10C4],al
0x66f343a  movups xmm0,[rbp+0x1278]
```

Meaning: Seasons shared_ptr: if null → 0x66F3694; else lock-inc [rax+8], rax=[rcx+0x28] → jump 0x66F3696 [V]. For K==9/5 path at 0x66f3379 (fall-through when kind!=9/5 in earlier branch): same clear + shared_ptr take [V]. Descriptor pack: 0x67A75D0(&[rbp+0xEA8], &[rbp+0x1130]) [V]; 0x678E1D0(rcx=&[rbp+0xF70], rdx=&[rbp+0x1210], r8=&[rbp+0x11B8], r9=&[rbp+0x1130]) geometry/material call [V]. Copies descriptor into staging [r12=rbp+0xF70]: [r12+0x70]=[r13+0x60], [r12+0x60]=[r13+0x50], byte [rbp+0x10C4]=[rbp+0x1274] [V].

## NEXT
Next line to do: 601 (phase lines 601..640 not yet written).

### lines 601..640

```
0x66f3441  movups [rbp+0x10C8],xmm0
0x66f3448  movups xmm0,[r13+0x78]
0x66f344d  movups xmm1,[r13+0x88]
0x66f3455  movups xmm2,[r13+0x97]
0x66f345d  movups [r12+0xA7],xmm2
0x66f3466  movups [r12+0x98],xmm1
0x66f346f  movups [r12+0x88],xmm0
0x66f3478  movzx eax,word ptr [rbp+0x12B8]
0x66f347f  mov [rbp+0x1108],ax
0x66f3486  mov rcx,r15
0x66f3489  call 0x67E23F0
0x66f348e  nop
0x66f348f  mov [rsp+0x20],r14
0x66f3494  lea rcx,[rbp+0x1440]
0x66f349b  lea rdx,[rbp+0x1060]
0x66f34a2  lea r8,[rbp+0x1008]
0x66f34a9  lea r9,[rbp+0xF80]
0x66f34b0  call 0x678E420
0x66f34b5  nop
0x66f34b6  mov eax,[r12+0x70]
0x66f34bb  lea r8,[rbp+0x1580]
0x66f34c2  mov [r8+0x10],eax
0x66f34c6  movups xmm0,[r12+0x60]
0x66f34cc  movups [r8],xmm0
0x66f34d0  movzx eax,byte ptr [rbp+0x10C4]
0x66f34d7  mov [rbp+0x1594],al
0x66f34dd  movups xmm0,[rbp+0x10C8]
0x66f34e4  movups [rbp+0x1598],xmm0
0x66f34eb  movups xmm0,[r12+0x88]
0x66f34f4  movups xmm1,[r12+0x98]
0x66f34fd  movups xmm2,[r12+0xA7]
0x66f3506  movups [rdi+0x183],xmm2
0x66f350d  movups [rdi+0x174],xmm1
0x66f3514  movups [rdi+0x164],xmm0
0x66f351b  movzx eax,word ptr [rbp+0x1108]
0x66f3522  mov [rbp+0x15D8],ax
0x66f3529  mov rax,[rbp+0x16A8]
0x66f3530  mov rcx,[rax+0x10]
0x66f3534  mov eax,0x9D0
0x66f3539  add rcx,rax
```

Meaning: Staging copy completes: vec4 [rbp+0x1278] → [rbp+0x10C8], descriptor bytes [r13+0x78/0x88/0x97] → [r12+0xA7/0x98/0x88], u16 [rbp+0x12B8] → [rbp+0x1108] [V]. Releases geometry 0x67E23F0(&[rbp+0x1130]=r15) [V]. Item assemble: 0x678E420(&[rbp+0x1440], &[rbp+0x1060], &[rbp+0x1008], &[rbp+0xF80]) [V]; copies descriptor tail into item staging [rbp+0x1580..]: u32, vec4, byte, vec4, vec3s, u16 [rbp+0x15D8] [V]. Pass allocation: pass = *(u64*)(*[rbp+0x16A8]+0x10)+0x9D0 via 0x5ABA5C0 [V].

## NEXT
Next line to do: 641 (phase lines 641..680 not yet written).

### lines 641..680

```
0x66f353c  mov [rsp+0x30],rdi
0x66f3541  lea rax,[rbp+0x1450]
0x66f3548  mov [rsp+0x28],rax
0x66f354d  lea rax,[rbp+0x14D8]
0x66f3554  mov [rsp+0x20],rax
0x66f3559  lea rdx,[rbp+0x15D8]
0x66f3560  lea r9,[rbp+0x1530]
0x66f3567  call 0x67A7830
0x66f356c  nop
0x66f356d  lea rcx,[rbp+0x1440]
0x66f3574  call 0x67E1660
0x66f3579  lea rcx,[rbp+0xF70]
0x66f3580  call 0x67E1660
0x66f3585  test bl,bl
0x66f3587  jne 0x66F4E70
0x66f358d  jmp 0x66F4EB0
0x66f3592  lea rcx,[rbp+0xEA8]
0x66f3599  mov r14,rdx
0x66f359c  call 0x67A75D0
0x66f35a1  nop
0x66f35a2  lea rcx,[rbp+0x1440]
0x66f35a9  lea rdx,[rbp+0x1050]
0x66f35b0  lea r8,[rbp+0xFF8]
0x66f35b7  mov r9,r14
0x66f35ba  call 0x678F640
0x66f35bf  nop
0x66f35c0  mov eax,[r12+0x60]
0x66f35c5  lea r8,[rbp+0x1578]
0x66f35cc  mov [r8+0x10],eax
0x66f35d0  movups xmm0,[r12+0x50]
0x66f35d6  movups [r8],xmm0
0x66f35da  movzx eax,byte ptr [rbp+0x10B4]
0x66f35e1  mov [rbp+0x158C],al
0x66f35e7  movups xmm0,[rbp+0x10B8]
0x66f35ee  movups [rbp+0x1590],xmm0
0x66f35f5  movups xmm0,[r12+0x78]
0x66f35fb  movups xmm1,[r12+0x88]
0x66f3604  movups xmm2,[r12+0x97]
0x66f360d  movups [rdi+0x17B],xmm2
0x66f3614  movups [rdi+0x16C],xmm1
```

Meaning: Kind!=9/5 path item emission: stack args {[rbp+0x1450], [rbp+0x14D8]}, rdx=&[rbp+0x15D8], r9=&[rbp+0x1530]; calls 0x67A7830 (binder) [V]; destroys item 0x67E1660(&[rbp+0x1440]) and geometry 0x67E1660(&[rbp+0xF70]) [V]; if valid bl → loop tail 0x66F4E70, else → 0x66F4EB0 [V]. Alternate descriptor pack path (0x66f3592): 0x67A75D0(&[rbp+0xEA8], &[rbp+0x1050], r8=[rbp+0xFF8], r9=staging) then 0x678F640 pack [V]; copies descriptor tail into [rbp+0x1578..]: u32 [r12+0x60], vec4 [r12+0x50], byte [rbp+0x10B4]→[rbp+0x158C], vec4 [rbp+0x10B8]→[rbp+0x1590], vec3s [r12+0x78/0x88/0x97]→[rdi+0x15C/0x16C/0x17B] [V].

## NEXT
Next line to do: 681 (phase lines 681..700 not yet written).

### lines 681..700

```
0x66f361b  movups [rdi+0x15C],xmm0
0x66f3622  movzx eax,word ptr [rbp+0x10F8]
0x66f3629  mov [rbp+0x15D0],ax
0x66f3630  mov rax,[rbp+0x16A8]
0x66f3637  mov rcx,[rax+0x10]
0x66f363b  mov eax,0x9D0
0x66f3640  add rcx,rax
0x66f3643  lea rax,[rbp+0x1448]
0x66f364a  mov [rsp+0x28],rax
0x66f364f  lea rax,[rbp+0x14D0]
0x66f3656  mov [rsp+0x20],rax
0x66f365b  lea rdx,[rbp+0x15D0]
0x66f3662  lea r9,[rbp+0x1528]
0x66f3669  call 0x67A8720
0x66f366e  nop
0x66f366f  lea rcx,[rbp+0x1440]
0x66f3676  call 0x67E1840
0x66f367b  lea rcx,[rbp+0xF70]
0x66f3682  call 0x67E23F0
0x66f3687  test bl,bl
```

Meaning: Staging item copy completes: vec4 [r12+0x78] → [rdi+0x15C], u16 [rbp+0x10F8] → [rbp+0x15D0] [V]. Second binder call: stack args {[rbp+0x1448], [rbp+0x14D0]}, rdx=&[rbp+0x15D0], r9=&[rbp+0x1528]; calls 0x67A8720 (binder) [V]; releases item 0x67E1840(&[rbp+0x1440]) and geometry 0x67E23F0(&[rbp+0xF70]) [V]; test bl,bl → continues to loop tail or exit [V]. Lines 681-700 complete the requested range 1..700.

## NEXT
Next line to do: 701 (all phases 1..18 complete for lines 1..700; unit done).
