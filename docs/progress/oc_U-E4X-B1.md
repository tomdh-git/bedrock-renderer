# Unit U-E4X-B1: chunk extractor body B — lines 1..700 of docs/data/listings/e4_B.txt
## NEXT
Next line to do: 701 (all phases 1-18 complete)
Base RVA: 0x66ef308; end RVA at line 700: 0x66f014a
Context: body B = K==13 light_source inline body of ChunkGeometry extractor at 0x66ea3d0 (docs/functions/66ea3d0.md)

### lines 1..40
```asm
0x66ef308  mov rax,[rbp+0xEE8]
0x66ef30f  mov r8,[rbp+0xEF0]
0x66ef316  mov [rbp+0xC78],rax
0x66ef31d  lea rcx,[rbp+0xC80]
0x66ef324  lea rdx,[rbp+0xEF0]
0x66ef32b  call 0xE86B370
0x66ef330  nop
0x66ef331  mov qword ptr [rbp+0xCF8],0
0x66ef33c  mov rax,[rbx+0x48]
0x66ef340  mov rdx,[rax]
0x66ef343  lea rax,[rdx-5]
0x66ef347  xor esi,esi
0x66ef349  test rax,0xFFFFFFFFFFFFFFFB
0x66ef34f  sete dil
0x66ef353  cmp rdx,0xA
0x66ef357  je 0x66EF428
0x66ef35d  mov byte ptr [rbp+0x16D0],9
0x66ef364  cmp rdx,0xC
0x66ef368  je 0x66EF42F
0x66ef36e  lea rax,[rdx-7]
0x66ef372  cmp rax,3
0x66ef376  setb al
0x66ef379  lea rcx,[rdx-0xF]
0x66ef37d  cmp rcx,2
0x66ef381  setb cl
0x66ef384  or cl,al
0x66ef386  mov [rbp+0x16D0],cl
0x66ef38c  jmp 0x66EF42F
0x66ef391  lea rax,[r13+0x3B0]
0x66ef398  mov rcx,[r13+0x3B8]
0x66ef39f  cmp qword ptr [rbp+0x1690],0xA
0x66ef3a7  mov [rsp+0x40],rax
0x66ef3ac  sete [rsp+0x30]
0x66ef3b1  lea rax,[rbp+0x1410]
0x66ef3b8  mov [rsp+0x38],rax
0x66ef3bd  lea rax,[rbp+0xEE8]
0x66ef3c4  mov [rsp+0x28],rax
0x66ef3c9  mov [rsp+0x20],rcx
0x66ef3ce  mov rcx,r13
0x66ef3d1  mov rdx,[rbp+0x16A8]
```
Meaning: Clone pass record via 0xe86b370 into [rbp+0xC80] with &passRecord at [rbp+0xEF0] and destructor pointer at [rbp+0xEE8]; zero [rbp+0xCF8]. Load kind K from [rbx+0x48]; compute fogA = ((K-5)&~4)==0 (K in {5,9}) [V]. Branch: K==0xA jumps to 0x66EF428 fallback; K==0xC jumps to 0x66EF42F; else compute kind class ((K-7)<3)|((K-0xF)<2) for K in {8,9,0xD,0xF} into [rbp+0x16D0] [V]. Callee RVA: 0xe86b370 [V].

## NEXT
Next line to do: 41 (phase 1 of 18 complete)

### lines 41..80
```asm
0x66ef3d8  mov r8d,r15d
0x66ef3db  mov r9,rbx
0x66ef3de  call 0x6792D90
0x66ef3e3  nop
0x66ef3e4  jmp 0x66F6E3B
0x66ef3e9  add rdx,rax
0x66ef3ec  cmp rcx,rdx
0x66ef3ef  jae 0x66F2819
0x66ef3f5  sub ecx,eax
0x66ef3f7  shr ecx,4
0x66ef3fa  mov [rbp+0x16BC],cx
0x66ef401  mov byte ptr [rbp+0x16BE],1
0x66ef408  lea rdx,[rbp+0x16BC]
0x66ef40f  lea r8,[rbp+0xF70]
0x66ef416  lea rcx,[rbp+0xEF0]
0x66ef41d  call 0x5679DB0
0x66ef422  nop
0x66ef423  jmp 0x66F2820
0x66ef428  mov byte ptr [rbp+0x16D0],2
0x66ef42f  mov [rbp+0x16B0],rdx
0x66ef436  xorps xmm0,xmm0
0x66ef439  movaps [rbp+0x1670],xmm0
0x66ef440  mov qword ptr [rbp+0x1680],0
0x66ef44b  mov rax,[rbx+0x38]
0x66ef44f  mov [rbp+0x1440],rax
0x66ef456  test rax,rax
0x66ef459  je short 0x66EF482
0x66ef45b  mov rcx,0xAAAAAAAAAAAAAAB
0x66ef465  cmp rax,rcx
0x66ef468  jae 0x66F8F0B
0x66ef46e  lea rcx,[rbp+0x1670]
0x66ef475  lea rdx,[rbp+0x1440]
0x66ef47c  call 0x678D170
0x66ef481  nop
0x66ef482  lea rbx,[r13+0x2E8]
0x66ef489  mov rcx,rbx
0x66ef48c  call 0xEEC59F0
0x66ef491  test eax,eax
0x66ef493  jne 0x66F8B50
0x66ef499  mov [rbp+0x1690],rbx
```
Meaning: K==0xA fallback: call 0x6792D90(builder, ctx, mode, &passRecord, ...) then jmp exit 0x66F6E3B [V]. Success path (K!=0xA): compute slot index (rdx-rax)>>4 into [rbp+0x16BC], set fog-alpha written flag [rbp+0x16BE]=1, call 0x5679DB0(passRecord 0xEF0, {slot,1}, {1,&vec4}) to write zero FogAlpha [V], jmp 0x66F2820. K==0xC case: [rbp+0x16D0]=2, [rbp+0x16B0]=rdx, zero xmm0, init [rbp+0x1670]=0 and [rbp+0x1680]=0, load draw count from [rbx+0x38] into [rbp+0x1440]. Callee RVAs: 0x6792d90, 0x5679db0 [V].

## NEXT
Next line to do: 81 (phase 2 of 18 complete)

### lines 81..120
```asm
0x66ef4a0  cmp dword ptr [r13+0x334],0x7FFFFFFF
0x66ef4ab  mov rax,[rbp+0x16C0]
0x66ef4b2  je 0x66F8B5B
0x66ef4b8  mov rax,[rax+0x38]
0x66ef4bc  test rax,rax
0x66ef4bf  je 0x66EF729
0x66ef4c5  mov rcx,[rbp+0x16C0]
0x66ef4cc  mov r13,[rcx+0x40]
0x66ef4d0  imul r15,rax,0x58
0x66ef4d4  add r15,r13
0x66ef4d7  lea rbx,[rbp+0x1440]
0x66ef4de  lea r14,[rbp+0xF70]
0x66ef4e5  xorps xmm6,xmm6
0x66ef4e8  jmp short 0x66EF50D
0x66ef4ea  add rdx,0x18
0x66ef4ee  mov [rbp+0x1678],rdx
0x66ef4f5  nop [rax+rax]
0x66ef500  add r13,0x58
0x66ef504  cmp r13,r15
0x66ef507  je 0x66EF729
0x66ef50d  movzx eax,byte ptr [r13+0x28]
0x66ef512  test eax,eax
0x66ef514  je short 0x66EF530
0x66ef516  cmp eax,1
0x66ef519  jne 0x66F82B5
0x66ef51f  lea rax,[r13+0x18]
0x66ef523  jmp short 0x66EF534
0x66ef525  nop [rax+rax]
0x66ef530  lea rax,[r13+0x10]
0x66ef534  mov rax,[rax]
0x66ef537  test rax,rax
0x66ef53a  je short 0x66EF500
0x66ef53c  mov rcx,[rbp+0x16A0]
0x66ef543  mov rdx,[rcx+0x2D8]
0x66ef54a  mov r8,[rdx+8]
0x66ef54e  cmp byte ptr [r8+0x19],0
0x66ef553  mov rcx,rdx
0x66ef556  jne short 0x66EF57E
0x66ef558  mov r9,[rax]
0x66ef55b  mov rcx,rdx
```
Meaning: Vector reserve via 0x678D170(&vec_1670, &count) if count != 0 and count < 0xAAAAAAAAAAAAAAB else throw 0x66F8F0B [V]. Lock builder mutex 0xEEC59F0(builder+0x2E8), check recursion limit [r13+0x334]==0x7FFFFFFF -> throw 0x66F8B5B [V]. Load draw-list base [rbp+0x16C0]+0x40, compute end = base + count*0x58 into r15 [V]. Iterate entries: read tag byte [r13+0x28], tag 0 -> value ptr = r13+0x10, tag 1 -> value ptr = r13+0x18, else throw 0x66F82B5; skip if pointer null [V]. Callee RVAs: 0x678d170, 0xeec59f0 [V].

## NEXT
Next line to do: 121 (phase 3 of 18 complete)

### lines 121..160
```asm
0x66ef55e  xchg ax,ax
0x66ef560  xor r10d,r10d
0x66ef563  cmp [r8+0x20],r9
0x66ef567  setl r10b
0x66ef56b  cmovge rcx,r8
0x66ef56f  shl r10d,4
0x66ef573  mov r8,[r8+r10]
0x66ef577  cmp byte ptr [r8+0x19],0
0x66ef57c  je short 0x66EF560
0x66ef57e  cmp byte ptr [rcx+0x19],0
0x66ef582  jne 0x66EF500
0x66ef588  cmp rcx,rdx
0x66ef58b  je 0x66EF500
0x66ef591  mov rdx,[rcx+0x20]
0x66ef595  cmp [rax],rdx
0x66ef598  jl 0x66EF500
0x66ef59e  mov r12,[rcx+0x28]
0x66ef5a2  test r12,r12
0x66ef5a5  je 0x66EF500
0x66ef5ab  mov rcx,[rbp+0x16C0]
0x66ef5b2  movzx eax,byte ptr [rcx+0x50]
0x66ef5b6  mov rcx,[rcx+0x48]
0x66ef5ba  lea rdx,[r12+8]
0x66ef5bf  mov rcx,[rcx]
0x66ef5c2  mov [rbp+0xF70],rcx
0x66ef5c9  mov [rbp+0xF78],al
0x66ef5cf  mov rcx,rbx
0x66ef5d2  mov r8,r14
0x66ef5d5  call 0xBC090B0
0x66ef5da  mov rcx,[rbp+0x1440]
0x66ef5e1  mov rax,[rbp+0x1448]
0x66ef5e8  mov rdx,[rbp+0x1450]
0x66ef5ef  xor rdx,rcx
0x66ef5f2  mov r8,[rbp+0x1458]
0x66ef5f9  xor r8,rax
0x66ef5fc  or r8,rdx
0x66ef5ff  mov rdx,[r12+0x28]
0x66ef604  cmove rax,rdx
0x66ef608  sete r8b
0x66ef60c  cmp rcx,[r12+0x10]
```
Meaning: RB-tree lower_bound: start at [rdx+8] (root), walk while node+0x19 isnil, compare [r8+0x20] (key) vs r9 (*value), child offset shl r10d,4 (0x10 stride) to descend [V]. Found node rcx: check [rcx+0x19]!=0 -> continue; cmp rcx,rdx (==end) -> skip; load key [rcx+0x20], jl skip; load value r12 = [rcx+0x28], skip if null [V]. Read [rbp+0x16C0]: flag byte +0x50, ptr +0x48; load [r12+8] as lookup args, call 0xBC090B0(&out_1440, node.value+8, {kind_ptr, flag50}) [V]. Callee RVA: 0xbc090b0 [V].

## NEXT
Next line to do: 161 (phase 4 of 18 complete)

### lines 161..200
```asm
0x66ef611  sete cl
0x66ef614  or cl,r8b
0x66ef617  cmp rax,rdx
0x66ef61a  sete dl
0x66ef61d  test cl,dl
0x66ef61f  je short 0x66EF626
0x66ef621  xor r12d,r12d
0x66ef624  jmp short 0x66EF656
0x66ef626  movaps [rbp+0x1440],xmm6
0x66ef62d  mov rcx,[rax+8]
0x66ef631  test rcx,rcx
0x66ef634  je short 0x66EF640
0x66ef636  lock inc dword ptr [rcx+8]
0x66ef63a  mov rcx,[rax+8]
0x66ef63e  jmp short 0x66EF642
0x66ef640  xor ecx,ecx
0x66ef642  mov rax,[rax]
0x66ef645  mov [rbp+0x1440],rax
0x66ef64c  mov [rbp+0x1448],rcx
0x66ef653  mov r12b,1
0x66ef656  mov [rbp+0x1450],r12b
0x66ef65d  mov rdx,[rbp+0x1678]
0x66ef664  cmp rdx,[rbp+0x1680]
0x66ef66b  je short 0x66EF6A4
0x66ef66d  mov byte ptr [rdx+0x10],0
0x66ef671  test r12b,r12b
0x66ef674  je 0x66EF4EA
0x66ef67a  movups [rdx],xmm6
0x66ef67d  mov rcx,[rbp+0x1448]
0x66ef684  test rcx,rcx
0x66ef687  je short 0x66EF6BF
0x66ef689  lock inc dword ptr [rcx+8]
0x66ef68d  mov rax,[rbp+0x1440]
0x66ef694  mov r8,[rbp+0x1448]
0x66ef69b  mov rcx,[rbp+0x1678]
0x66ef6a2  jmp short 0x66EF6C5
0x66ef6a4  lea rcx,[rbp+0x1670]
0x66ef6ab  mov r8,rbx
0x66ef6ae  call 0x678D3F0
0x66ef6b3  nop
```
Meaning: Dedupe: compare out pair (rax,rcx) vs cached (rdx,[r12+0x28]); if equal skip (r12=0). Else shared_ptr copy: lock inc [rax+8], store ptr+ctrl at [rbp+0x1440/0x1448], r12b=1 (valid flag). Check [rbp+0x1678] != [rbp+0x1680] (vector not full): store [ptr,0,valid=1] at current end, advance end by 0x18. Else grow path: call 0x678D3F0(&vec_1670, rbx, ...) [V]. Release shared_ptr: lock dec [r12+8], if 0 call destructor via [0xF99FFA0] twice (ctrl+0xC then +8) [V]. Callee RVAs: 0x678d3f0, [0xF99FFA0] [V].

## NEXT
Next line to do: 201 (phase 5 of 18 complete)

### lines 201..240
```asm
0x66ef6b4  test r12b,r12b
0x66ef6b7  je 0x66EF500
0x66ef6bd  jmp short 0x66EF6DB
0x66ef6bf  mov rcx,rdx
0x66ef6c2  xor r8d,r8d
0x66ef6c5  mov [rdx],rax
0x66ef6c8  mov [rdx+8],r8
0x66ef6cc  mov byte ptr [rdx+0x10],1
0x66ef6d0  add rcx,0x18
0x66ef6d4  mov [rbp+0x1678],rcx
0x66ef6db  mov r12,[rbp+0x1448]
0x66ef6e2  test r12,r12
0x66ef6e5  je 0x66EF500
0x66ef6eb  lock dec dword ptr [r12+8]
0x66ef6f1  jne 0x66EF500
0x66ef6f7  mov rax,[r12]
0x66ef6fb  mov rax,[rax]
0x66ef6fe  mov rcx,r12
0x66ef701  call qword ptr [0xF99FFA0]
0x66ef707  lock dec dword ptr [r12+0xC]
0x66ef70d  jne 0x66EF500
0x66ef713  mov rax,[r12]
0x66ef717  mov rax,[rax+8]
0x66ef71b  mov rcx,r12
0x66ef71e  call qword ptr [0xF99FFA0]
0x66ef724  jmp 0x66EF500
0x66ef729  mov rax,[rbp+0x16B0]
0x66ef730  and rax,0xFFFFFFFFFFFFFFFE
0x66ef734  mov [rbp+0x1658],rax
0x66ef73b  mov rcx,[rbp+0x1690]
0x66ef742  call 0xEEC5A10
0x66ef747  mov rdx,[rbp+0x16C0]
0x66ef74e  mov r14,[rdx+0x40]
0x66ef752  imul rax,[rdx+0x38],0x58
0x66ef757  add rax,r14
0x66ef75a  mov [rbp+0x16A0],rax
0x66ef761  xor eax,eax
0x66ef763  movzx ecx,byte ptr [rbp+0x16D0]
0x66ef76a  cmp cl,2
0x66ef76d  sete al
```
Meaning: Unlock builder mutex 0xEEC5A10 [V]. Compute end = [rdx+0x40] + [rdx+0x38]*0x58 stored at [rbp+0x16A0] [V]. Render-state word: eax = (cl==2 ? 0x800 : 0)<<0xB; ecx = (cl==9) ? 0x2800 : eax; [rbp+0x1688] = ecx + dil*4 + 0x8101 where dil = fogA [V]. Set [rbp+0x1388] = rdx+0x78 (desc+0x78 terrain ptr). Load xmm constants: xmm7=xmm10=1.0f (0xEEC8060), xmm8=xmm11=0.0078125 (0xEFD32F0), xmm9={-0,-0,0,0} (0xF0A4080), xmm13=8.0f (0xEFC13A4), xmm14={8,8,0,0} (0xF0B8740) [V]. Loop entry: rsi=0, r12=&[rbp+0x1130], jump to loop test.

## NEXT
Next line to do: 241 (phase 6 of 18 complete)

### lines 241..280
```asm
0x66ef770  shl eax,0xB
0x66ef773  cmp cl,9
0x66ef776  mov ecx,0x2800
0x66ef77b  cmovne ecx,eax
0x66ef77e  lea rax,[rdx+0x78]
0x66ef782  mov [rbp+0x1388],rax
0x66ef789  mov sil,dil
0x66ef78c  lea eax,[rcx+rsi*4+0x8101]
0x66ef793  mov [rbp+0x1688],eax
0x66ef799  lea r13,[rbp+0x1050]
0x66ef7a0  xorps xmm6,xmm6
0x66ef7a3  movss xmm7,[0xEEC8060]
0x66ef7ab  movsd xmm8,[0xEFD32F0]
0x66ef7b4  movaps xmm9,[0xF0A4080]
0x66ef7bc  movss xmm10,[0xEEC8060]
0x66ef7c5  movsd xmm11,[0xEFD32F0]
0x66ef7ce  movss xmm13,[0xEFC13A4]
0x66ef7d7  movaps xmm14,[0xF0B8740]
0x66ef7df  xor esi,esi
0x66ef7e1  lea r12,[rbp+0x1130]
0x66ef7e8  jmp short 0x66EF7FE
0x66ef7ea  nop [rax+rax]
0x66ef7f0  mov rsi,[rbp+0x1690]
0x66ef7f7  inc rsi
0x66ef7fa  add r14,0x58
0x66ef7fe  cmp r14,[rbp+0x16A0]
0x66ef805  je 0x66F27A9
0x66ef80b  movzx eax,byte ptr [r14+0x28]
0x66ef810  test eax,eax
0x66ef812  je short 0x66EF830
0x66ef814  cmp eax,1
0x66ef817  jne 0x66F81DF
0x66ef81d  lea rax,[r14+0x18]
0x66ef821  cmp qword ptr [rax],0
0x66ef825  jne short 0x66EF83A
0x66ef827  jmp short 0x66EF7FA
0x66ef829  nop [rax]
0x66ef830  lea rax,[r14+0x10]
0x66ef834  cmp qword ptr [rax],0
0x66ef838  je short 0x66EF7FA
```
Meaning: Loop test: r14 < end [rbp+0x16A0] -> exit to 0x66F27A9 [V]. Entry variant resolution: tag [r14+0x28], tag 0 -> rax=r14+0x10, tag 1 -> rax=r14+0x18, else throw 0x66F81DF; skip if *rax==0 [V]. Load z = xmm15 = *(float*)[r14+0x3C] [V]. Init translation matrix: [rbp+0x1440]=0x3F800000 (1.0f), zero [rbp+0x1444..0x1478], [rbp+0x1454]=1.0f. Compute T = translate(a,b,z) via shuffles: xmm0 = xmm15 splatted, build translation matrix columns into [rbp+0x1468]/[rbp+0x1478] [V].

## NEXT
Next line to do: 281 (phase 7 of 18 complete)

### lines 281..320
```asm
0x66ef83a  movsd xmm15,[r14+0x3C]
0x66ef840  mov dword ptr [rbp+0x1440],0x3F800000
0x66ef84a  lea rax,[rbp+0x1444]
0x66ef851  movups [rax],xmm6
0x66ef854  mov dword ptr [rbp+0x1454],0x3F800000
0x66ef85e  movups [rax+0x14],xmm6
0x66ef862  movaps xmm0,xmm15
0x66ef866  mulps xmm0,xmm6
0x66ef869  movaps xmm1,xmm0
0x66ef86c  shufps xmm1,xmm0,0xE1
0x66ef870  addps xmm1,xmm15
0x66ef874  movss xmm12,[r14+0x44]
0x66ef87a  movaps xmm2,xmm12
0x66ef87e  shufps xmm2,xmm12,0
0x66ef883  mulps xmm2,xmm7
0x66ef886  movaps xmm3,xmm0
0x66ef889  shufps xmm3,xmm0,0x55
0x66ef88d  unpcklps xmm0,xmm0
0x66ef890  addps xmm0,xmm3
0x66ef893  addps xmm0,xmm2
0x66ef896  addps xmm0,xmm8
0x66ef89a  shufps xmm2,xmm2,0x55
0x66ef89e  addps xmm2,xmm1
0x66ef8a1  movaps xmm1,xmm9
0x66ef8a5  movlhps xmm1,xmm2
0x66ef8a8  addps xmm1,xmm7
0x66ef8ab  movups [rbp+0x1468],xmm1
0x66ef8b2  movlps [rbp+0x1478],xmm0
0x66ef8b9  lea rcx,[rbp+0xE10]
0x66ef8c0  mov rdx,[rbp+0x1388]
0x66ef8c7  lea r8,[rbp+0x1440]
0x66ef8ce  call 0xAA6580
0x66ef8d3  nop
0x66ef8d4  movss xmm0,[r14+0x48]
0x66ef8da  ucomiss xmm0,xmm10
0x66ef8de  jne short 0x66EF8E6
0x66ef8e0  jnp 0x66EF97A
0x66ef8e6  movaps xmm1,xmm0
0x66ef8e9  shufps xmm1,xmm0,0
0x66ef8ed  mulps xmm1,xmm7
```
Meaning: First mat4 multiply: call 0xAA6580(&model_e10 at [rbp+0xE10], desc_mat at [rbp+0x1388], &T at [rbp+0x1440]) -> model = descMat * T [V]. If *(float*)[r14+0x48] != 1.0f: scale matrix with s=splat(scale), call 0xAA6580(&f70 at [rbp+0xF70], &model_e10, &S) -> model = model * S [V]. Store final model at [rbp+0xE10..0xE40]. Callee RVAs: 0xaa6580 x2 [V].

## NEXT
Next line to do: 321 (phase 8 of 18 complete)

### lines 321..360
```asm
0x66ef8f0  movss [rbp+0x1440],xmm0
0x66ef8f8  movq xmm2,xmm1
0x66ef8fc  shufps xmm1,xmm1,0x55
0x66ef900  movups [rbp+0x1444],xmm1
0x66ef907  movss [rbp+0x1454],xmm0
0x66ef90f  movups [rbp+0x1458],xmm1
0x66ef916  movdqu [rbp+0x1468],xmm2
0x66ef91e  movsd [rbp+0x1478],xmm11
0x66ef927  lea rcx,[rbp+0xF70]
0x66ef92e  lea rdx,[rbp+0xE10]
0x66ef935  lea r8,[rbp+0x1440]
0x66ef93c  call 0xAA6580
0x66ef941  nop
0x66ef942  movaps xmm0,[rbp+0xF70]
0x66ef949  movaps xmm1,[rbp+0xF80]
0x66ef950  movaps xmm2,[rbp+0xF90]
0x66ef957  movaps xmm3,[rbp+0xFA0]
0x66ef95e  movaps [rbp+0xE10],xmm0
0x66ef965  movaps [rbp+0xE20],xmm1
0x66ef96c  movaps [rbp+0xE30],xmm2
0x66ef973  movaps [rbp+0xE40],xmm3
0x66ef97a  mov rax,[rbp+0x16A8]
0x66ef981  mov rdx,[rax]
0x66ef984  mov [rsp+0x20],r14
0x66ef989  lea rcx,[rbp+0xDB8]
0x66ef990  mov r8,[rbp+0x1698]
0x66ef997  lea r9,[rbp+0xEE8]
0x66ef99e  call 0x678C4C0
0x66ef9a3  nop
0x66ef9a4  lea rax,[rbp+0xC78]
0x66ef9ab  mov [rbp+0x1650],rax
0x66ef9b2  cmp byte ptr [rbp+0x16BE],1
0x66ef9b9  jne short 0x66EFA16
0x66ef9bb  movss xmm0,[r14+0x4C]
0x66ef9c1  xorps xmm1,xmm1
0x66ef9c4  ucomiss xmm0,xmm1
0x66ef9c7  jbe short 0x66EFA16
0x66ef9c9  shufps xmm0,xmm0,0
0x66ef9cd  movaps [rbp+0x1440],xmm0
0x66ef9d4  mov qword ptr [rbp+0xF70],1
```
Meaning: Call 0x678C4C0(&drawlist at [rbp+0xDB8], *ctx, [rbp+0x1388]=desc+0x78, &passRecord_ee8, &entry) — draw-list builder per entry [V]. Pack draw-item context: [rbp+0xEA8]=&[rbp+0x1370], [rbp+0xEB0]=&[rbp+0xE10], [rbp+0xEB8]=&[rbp+0xDB8], [rbp+0xEC0]=&[rbp+0x1650] (pass record ptr) [V]. Compute shared_ptr index rcx = rsi + rsi*2 (rsi*3), load valid byte [rax+rcx*8+0x10] from vec_1670 [V]. Callee RVA: 0x678c4c0 [V].

## NEXT
Next line to do: 361 (phase 9 of 18 complete)

### lines 361..400
```asm
0x66ef9df  lea rax,[rbp+0x1440]
0x66ef9e6  mov [rbp+0xF78],rax
0x66ef9ed  lea rcx,[rbp+0xEF0]
0x66ef9f4  lea rdx,[rbp+0x16BC]
0x66ef9fb  lea r8,[rbp+0xF70]
0x66efa02  call 0x5679DB0
0x66efa07  nop
0x66efa08  lea rax,[rbp+0xEE8]
0x66efa0f  mov [rbp+0x1650],rax
0x66efa16  lea rax,[rbp+0x1370]
0x66efa1d  mov [rbp+0xEA8],rax
0x66efa24  lea rax,[rbp+0xE10]
0x66efa2b  mov [rbp+0xEB0],rax
0x66efa32  lea rax,[rbp+0xDB8]
0x66efa39  mov [rbp+0xEB8],rax
0x66efa40  lea rax,[rbp+0x1650]
0x66efa47  mov [rbp+0xEC0],rax
0x66efa4e  mov rax,[rbp+0x1670]
0x66efa55  mov [rbp+0x1690],rsi
0x66efa5c  lea rcx,[rsi+rsi*2]
0x66efa60  mov byte ptr [rbp+0x1430],0
0x66efa67  movzx esi,byte ptr [rax+rcx*8+0x10]
0x66efa6c  cmp sil,1
0x66efa70  jne short 0x66EFAAA
0x66efa72  lea rax,[rax+rcx*8]
0x66efa76  movaps [rbp+0x1420],xmm6
0x66efa7d  mov rcx,[rax+8]
0x66efa81  test rcx,rcx
0x66efa84  je short 0x66EFA90
0x66efa86  lock inc dword ptr [rcx+8]
0x66efa8a  mov rcx,[rax+8]
0x66efa8e  jmp short 0x66EFA92
0x66efa90  xor ecx,ecx
0x66efa92  mov rax,[rax]
0x66efa95  mov [rbp+0x1420],rax
0x66efa9c  mov [rbp+0x1428],rcx
0x66efaa3  mov byte ptr [rbp+0x1430],1
0x66efaaa  cmp qword ptr [rbp+0x1658],2
0x66efab2  sete cl
0x66efab5  mov eax,esi
```
Meaning: FogAlpha per-entry: if [rbp+0x16BE]==1 and *(float*)[r14+0x4C] > 0: splat value into [rbp+0x1440], call 0x5679DB0(passRecord 0xEF0, {slot [rbp+0x16BC],1}, {1,&vec4}) to write FogAlpha [V]. Restore [rbp+0x1650]=&[rbp+0xEE8]. If valid byte==1: shared_ptr copy lock inc into [rbp+0x1420/0x1428], valid=1 [V]. Kind class test: cl = ([rbp+0x1658]==2), al = (valid^1)|cl, test [rbp+0x16CF] & [rbp+0x1368] (isAB flag) -> if zero goto 0x66EFD17 (kind!=2 path) [V]. Callee RVA: 0x5679db0 [V].

## NEXT
Next line to do: 401 (phase 10 of 18 complete)

### lines 401..440
```asm
0x66efab7  xor al,1
0x66efab9  or al,cl
0x66efabb  movzx ecx,byte ptr [rbp+0x1368]
0x66efac2  test [rbp+0x16CF],cl
0x66efac8  je 0x66EFD17
0x66eface  test al,al
0x66efad0  je 0x66EFEA1
0x66efad6  addss xmm12,xmm13
0x66efadb  addps xmm15,xmm14
0x66efadf  cmp qword ptr [rbp+0x1658],2
0x66efae7  jne 0x66EFF2F
0x66efaed  test sil,sil
0x66efaf0  je 0x66EFF2F
0x66efaf6  movlps [rbp+0x1390],xmm15
0x66efafe  movss [rbp+0x1398],xmm12
0x66efb07  lea rcx,[rbp+0xEA8]
0x66efb0e  mov rdx,r12
0x66efb11  call 0x678CF10
0x66efb16  nop
0x66efb17  lea rsi,[rbp+0xF70]
0x66efb1e  lea rax,[rbp+0x1390]
0x66efb25  mov [rsp+0x20],rax
0x66efb2a  mov rcx,rsi
0x66efb2d  lea rdx,[rbp+0x1210]
0x66efb34  lea r8,[rbp+0x11B8]
0x66efb3b  mov r9,r12
0x66efb3e  call 0x678E1D0
0x66efb43  nop
0x66efb44  lea rcx,[rbp+0x1210]
0x66efb4b  mov eax,[rcx+0x68]
0x66efb4e  mov [r13+0x78],eax
0x66efb52  movups xmm0,[rcx+0x58]
0x66efb56  movups [r13+0x68],xmm0
0x66efb5b  movzx eax,byte ptr [rbp+0x127C]
0x66efb62  mov [rbp+0x10CC],al
0x66efb68  movups xmm0,[rbp+0x1280]
0x66efb6f  movups [rbp+0x10D0],xmm0
0x66efb76  movups xmm0,[rcx+0x80]
0x66efb7d  movups xmm1,[rcx+0x90]
0x66efb84  movups xmm2,[rcx+0x9F]
```
Meaning: If al!=0 (kind class 2 && valid): addss xmm12,xmm13 (UV scroll += 8.0f), addps xmm15,xmm14 (UV offset += {8,8}) for shift variant [V]. Call 0x678CF10(&[rbp+0xEA8], r12) binder [V]. Call 0x678E1D0(&f70 [rbp+0xF70], &desc [rbp+0x1210], &item [rbp+0x11B8], &context [rbp+0xE10], r12) geometry/material [V]. Copy descriptor fields: [r13+0x78]=[rcx+0x68], [r13+0x68]=[rcx+0x58], byte [rbp+0x10CC]=[rbp+0x127C], [rbp+0x10D0]=[rbp+0x1280], xmm0=[rcx+0x80], xmm1=[rcx+0x90], xmm2=[rcx+0x9F] -> [r13+0xAF/0xA0/0x90], word [rbp+0x1110]=[rbp+0x12C0] [V]. Callee RVAs: 0x678cf10, 0x678e1d0 [V].

## NEXT
Next line to do: 441 (phase 11 of 18 complete)

### lines 441..480
```asm
0x66efb8b  movups [r13+0xAF],xmm2
0x66efb93  movups [r13+0xA0],xmm1
0x66efb9b  movups [r13+0x90],xmm0
0x66efba3  movzx eax,word ptr [rbp+0x12C0]
0x66efbaa  mov [rbp+0x1110],ax
0x66efbb1  mov rcx,r12
0x66efbb4  call 0x67E23F0
0x66efbb9  nop
0x66efbba  mov [rsp+0x20],rsi
0x66efbbf  lea rcx,[rbp+0x1440]
0x66efbc6  lea rdx,[rbp+0x1060]
0x66efbcd  lea r8,[rbp+0x1008]
0x66efbd4  lea r9,[rbp+0xF80]
0x66efbdb  call 0x678E420
0x66efbe0  nop
0x66efbe1  mov eax,[r13+0x78]
0x66efbe5  lea rcx,[rbp+0x1588]
0x66efbec  mov [rcx+0x10],eax
0x66efbef  movups xmm0,[r13+0x68]
0x66efbf4  movups [rcx],xmm0
0x66efbf7  movzx eax,byte ptr [rbp+0x10CC]
0x66efbfe  mov [rbp+0x159C],al
0x66efc04  movups xmm0,[rbp+0x10D0]
0x66efc0b  movups [rbp+0x15A0],xmm0
0x66efc12  movups xmm0,[r13+0x90]
0x66efc1a  movups xmm1,[r13+0xA0]
0x66efc22  movups xmm2,[r13+0xAF]
0x66efc2a  lea rax,[rbp+0x1444]
0x66efc31  movups [rax+0x18B],xmm2
0x66efc38  movups [rax+0x17C],xmm1
0x66efc3f  movups [rax+0x16C],xmm0
0x66efc46  movzx eax,word ptr [rbp+0x1110]
0x66efc4d  mov [rbp+0x15E0],ax
0x66efc54  mov rax,[rbp+0x16A8]
0x66efc5b  mov rcx,[rax+0x10]
0x66efc5f  mov eax,0x9D0
0x66efc64  add rcx,rax
0x66efc67  call 0x5ABA5C0
0x66efc6c  nop
0x66efc6d  mov r15,rax
```
Meaning: Call 0x67E23F0(r12) release shared_ptr [V]. Call 0x678E420(&model [rbp+0x1440], &out [rbp+0x1060], &tmp [rbp+0x1008], [rbp+0xF80]) item assemble [V]. Copy assembled item to staging [rbp+0x1588]: [rcx+0x10]=[r13+0x78], [rcx]=[r13+0x68], byte [rbp+0x159C]=[rbp+0x10CC], [rbp+0x15A0]=[rbp+0x10D0], xmm0/1/2=[r13+0x90/A0/AF] -> [rbp+0x1444+0x16C/17C/18B], word [rbp+0x15E0]=[rbp+0x1110] [V]. Push u16 to pass pool: pass = *(ctx+0x10)+0x9D0 via 0x5ABA5C0 [V], r15=pass ptr. Callee RVAs: 0x67e23f0, 0x678e420, 0x5aba5c0 [V].

## NEXT
Next line to do: 481 (phase 12 of 18 complete)

### lines 481..520
```asm
0x66efc70  movaps [rbp+0x11E0],xmm6
0x66efc77  movaps [rbp+0x11D0],xmm6
0x66efc7e  movaps [rbp+0x11C0],xmm6
0x66efc85  movaps [rbp+0x11B0],xmm6
0x66efc8c  movaps [rbp+0x11A0],xmm6
0x66efc93  movaps [rbp+0x1190],xmm6
0x66efc9a  movaps [rbp+0x1180],xmm6
0x66efca1  movaps [rbp+0x1170],xmm6
0x66efca8  movaps [rbp+0x1160],xmm6
0x66efcaf  movaps [rbp+0x1150],xmm6
0x66efcb6  movaps [rbp+0x1140],xmm6
0x66efcbd  movaps [rbp+0x1130],xmm6
0x66efcc4  mov qword ptr [rbp+0x11F0],0
0x66efccf  mov rcx,[0x1233E1B0]
0x66efcd6  mov rax,[rcx]
0x66efcd9  mov rax,[rax+0x10]
0x66efcdd  mov dl,0x4A
0x66efcdf  call qword ptr [0xF99FFA0]
0x66efce5  nop
0x66efce6  mov [rbp+0x16D4],al
0x66efcec  mov rdx,[r15+0x8A8]
0x66efcf3  cmp rdx,[r15+0x8B0]
0x66efcfa  je 0x66F0C67
0x66efd00  movzx eax,word ptr [rbp+0x15E0]
0x66efd07  mov [rdx],ax
0x66efd0a  add qword ptr [r15+0x8A8],2
0x66efd12  jmp 0x66F0C7B
0x66efd17  test al,al
0x66efd19  je 0x66EFEE8
0x66efd1f  cmp qword ptr [rbp+0x1658],2
0x66efd27  lea rdx,[rbp+0xF70]
0x66efd2e  jne 0x66F00F9
0x66efd34  test sil,sil
0x66efd37  je 0x66F00F9
0x66efd3d  lea rcx,[rbp+0xEA8]
0x66efd44  mov rsi,rdx
0x66efd47  call 0x678CF10
0x66efd4c  nop
0x66efd4d  lea rcx,[rbp+0x1440]
0x66efd54  lea rdx,[rbp+0x1050]
```
Meaning: Zero 16 xmm slots [rbp+0x1130..0x11F0] for item staging [V]. Query feature flag 0x4A: rcx=[0x1233E1B0], call qword [0xF99FFA0](rcx, 0x4A) -> [rbp+0x16D4] [V]. Push u16 [rbp+0x15E0] to pool [r15+0x8A8] (fast path) or slow path 0x66F0C67 via 0x1EF6F90; add qword [r15+0x8A8],2 [V]. Callee RVAs: [0xF99FFA0], 0x1ef6f90 [V/I].

## NEXT
Next line to do: 521 (phase 13 of 18 complete)

### lines 521..560
```asm
0x66efd5b  lea r8,[rbp+0xFF8]
0x66efd62  mov r9,rsi
0x66efd65  call 0x678F640
0x66efd6a  nop
0x66efd6b  mov eax,[r13+0x68]
0x66efd6f  lea rcx,[rbp+0x1580]
0x66efd76  mov [rcx+0x10],eax
0x66efd79  movups xmm0,[r13+0x58]
0x66efd7e  movups [rcx],xmm0
0x66efd81  movzx eax,byte ptr [rbp+0x10BC]
0x66efd88  mov [rbp+0x1594],al
0x66efd8e  movups xmm0,[rbp+0x10C0]
0x66efd95  movups [rbp+0x1598],xmm0
0x66efd9c  movups xmm0,[r13+0x80]
0x66efda4  movups xmm1,[r13+0x90]
0x66efdac  movups xmm2,[r13+0x9F]
0x66efdb4  lea rax,[rbp+0x1444]
0x66efdbb  movups [rax+0x183],xmm2
0x66efdc2  movups [rax+0x174],xmm1
0x66efdc9  movups [rax+0x164],xmm0
0x66efdd0  movzx eax,word ptr [rbp+0x1100]
0x66efdd7  mov [rbp+0x15D8],ax
0x66efdde  mov rax,[rbp+0x16A8]
0x66efde5  mov rcx,[rax+0x10]
0x66efde9  mov eax,0x9D0
0x66efdee  add rcx,rax
0x66efdf1  call 0x5ABA5C0
0x66efdf6  nop
0x66efdf7  mov r15,rax
0x66efdfa  movaps [rbp+0x11E0],xmm6
0x66efe01  movaps [rbp+0x11D0],xmm6
0x66efe08  movaps [rbp+0x11C0],xmm6
0x66efe0f  movaps [rbp+0x11B0],xmm6
0x66efe16  movaps [rbp+0x11A0],xmm6
0x66efe1d  movaps [rbp+0x1190],xmm6
0x66efe24  movaps [rbp+0x1180],xmm6
0x66efe2b  movaps [rbp+0x1170],xmm6
0x66efe32  movaps [rbp+0x1160],xmm6
0x66efe39  movaps [rbp+0x1150],xmm6
0x66efe40  movaps [rbp+0x1140],xmm6
```
Meaning: kind!=2 fallback path (jump from 0x66EFD17): call 0x678CF10(&[rbp+0xEA8], rdx=rsi) binder [V]; call 0x678F640(&model [rbp+0x1440], &out [rbp+0x1050], &tmp [rbp+0xFF8], rsi) variant descriptor pack [V]. Copy staging [rbp+0x1580]: [rcx+0x10]=[r13+0x68], [rcx]=[r13+0x58], byte [rbp+0x1594]=[rbp+0x10BC], [rbp+0x1598]=[rbp+0x10C0], xmm0/1/2=[r13+0x80/90/9F] -> [rbp+0x1444+0x164/174/183], word [rbp+0x15D8]=[rbp+0x1100] [V]. Push u16 [rbp+0x15D8] to pass pool via 0x5ABA5C0 [V]. Callee RVAs: 0x678cf10, 0x678f640, 0x5aba5c0 [V].

## NEXT
Next line to do: 561 (phase 14 of 18 complete)

### lines 561..600
```asm
0x66efe47  movaps [rbp+0x1130],xmm6
0x66efe4e  mov qword ptr [rbp+0x11F0],0
0x66efe59  mov rcx,[0x1233E1B0]
0x66efe60  mov rax,[rcx]
0x66efe63  mov rax,[rax+0x10]
0x66efe67  mov dl,0x4A
0x66efe69  call qword ptr [0xF99FFA0]
0x66efe6f  nop
0x66efe70  mov [rbp+0x16D4],al
0x66efe76  mov rdx,[r15+0x8A8]
0x66efe7d  cmp rdx,[r15+0x8B0]
0x66efe84  je 0x66F1DE8
0x66efe8a  movzx eax,word ptr [rbp+0x15D8]
0x66efe91  mov [rdx],ax
0x66efe94  add qword ptr [r15+0x8A8],2
0x66efe9c  jmp 0x66F1DFC
0x66efea1  movaps [rbp+0x1660],xmm6
0x66efea8  movaps [rbp+0x1410],xmm6
0x66efeaf  cmp qword ptr [rbp+0x16B0],9
0x66efeb7  je short 0x66EFEC7
0x66efeb9  cmp qword ptr [rbp+0x16B0],5
0x66efec1  jne 0x66F0271
0x66efec7  mov rcx,[rbp+0x16C0]
0x66efece  mov rax,[rcx+0x28]
0x66efed2  test rax,rax
0x66efed5  je 0x66F025D
0x66efedb  lock inc dword ptr [rax+8]
0x66efedf  mov rax,[rcx+0x28]
0x66efee3  jmp 0x66F025F
0x66efee8  movaps [rbp+0x1660],xmm6
0x66efeef  movaps [rbp+0x1410],xmm6
0x66efef6  cmp qword ptr [rbp+0x16B0],9
0x66efefe  je short 0x66EFF0E
0x66eff00  cmp qword ptr [rbp+0x16B0],5
0x66eff08  jne 0x66F11F7
0x66eff0e  mov rcx,[rbp+0x16C0]
0x66eff15  mov rax,[rcx+0x28]
0x66eff19  test rax,rax
0x66eff1c  je 0x66F11E3
0x66eff22  lock inc dword ptr [rax+8]
```
Meaning: Zero staging block, query flag 0x4A via vcall [0xF99FFA0] [V]. Push u16 [rbp+0x15D8] to pool [r15+0x8A8] (fast) or slow 0x66F1DE8 [V]. Seasons/alpha path: if kind [rbp+0x16B0] == 9 or 5: shared_ptr = [rbp+0x16C0]+0x28 with lock inc [V]; else jump to 0x66F0271 / 0x66F11F7. Store shared_ptr at [rbp+0x1410/0x1418] [V]. Callee RVAs: [0xF99FFA0] [V].

## NEXT
Next line to do: 601 (phase 15 of 18 complete)

### lines 601..640
```asm
0x66eff26  mov rax,[rcx+0x28]
0x66eff2a  jmp 0x66F11E5
0x66eff2f  movlps [rbp+0x1390],xmm15
0x66eff37  movss [rbp+0x1398],xmm12
0x66eff40  lea rcx,[rbp+0xEA8]
0x66eff47  mov rdx,r12
0x66eff4a  call 0x678CF10
0x66eff4f  nop
0x66eff50  lea rdi,[rbp+0xF70]
0x66eff57  lea rax,[rbp+0x1390]
0x66eff5e  mov [rsp+0x20],rax
0x66eff63  mov rcx,rdi
0x66eff66  lea rdx,[rbp+0x1210]
0x66eff6d  lea r8,[rbp+0x11B8]
0x66eff74  mov r9,r12
0x66eff77  call 0x678E1D0
0x66eff7c  nop
0x66eff7d  lea rcx,[rbp+0x1210]
0x66eff84  mov eax,[rcx+0x68]
0x66eff87  mov [r13+0x78],eax
0x66eff8b  movups xmm0,[rcx+0x58]
0x66eff8f  movups [r13+0x68],xmm0
0x66eff94  movzx eax,byte ptr [rbp+0x127C]
0x66eff9b  mov [rbp+0x10CC],al
0x66effa1  movups xmm0,[rbp+0x1280]
0x66effa8  movups [rbp+0x10D0],xmm0
0x66effaf  movups xmm0,[rcx+0x80]
0x66effb6  movups xmm1,[rcx+0x90]
0x66effbd  movups xmm2,[rcx+0x9F]
0x66effc4  movups [r13+0xAF],xmm2
0x66effcc  movups [r13+0xA0],xmm1
0x66effd4  movups [r13+0x90],xmm0
0x66effdc  movzx eax,word ptr [rbp+0x12C0]
0x66effe3  mov [rbp+0x1110],ax
0x66effea  mov rcx,r12
0x66effed  call 0x67E23F0
0x66efff2  nop
0x66efff3  mov [rsp+0x20],rdi
0x66efff8  lea rcx,[rbp+0x1440]
0x66effff  lea rdx,[rbp+0x1060]
```
Meaning: Duplicate seasons path (kind 9 or 5 from 0x66EFEF6): shared_ptr load from [rbp+0x16C0]+0x28 lock inc, store [rbp+0x1410/0x1418] [V]. Call 0x678CF10(&[rbp+0xEA8], r12) binder [V]; call 0x678E1D0(&f70 [rbp+0xF70], &desc [rbp+0x1210], &item [rbp+0x11B8], &ctx [rbp+0xE10], r12) [V]. Copy descriptor fields to [r13+0x78/0x68], byte [rbp+0x10CC]=[rbp+0x127C], [rbp+0x10D0]=[rbp+0x1280], xmm0/1/2=[rcx+0x80/90/9F]->[r13+0xAF/0xA0/0x90], word [rbp+0x1110]=[rbp+0x12C0] [V]. Call 0x67E23F0(r12) release [V]. Callee RVAs: 0x678cf10, 0x678e1d0, 0x67e23f0 [V].

## NEXT
Next line to do: 641 (phase 16 of 18 complete)

### lines 641..680
```asm
0x66f0006  lea r8,[rbp+0x1008]
0x66f000d  lea r9,[rbp+0xF80]
0x66f0014  call 0x678E420
0x66f0019  nop
0x66f001a  mov eax,[r13+0x78]
0x66f001e  lea r8,[rbp+0x1588]
0x66f0025  mov [r8+0x10],eax
0x66f0029  movups xmm0,[r13+0x68]
0x66f002e  movups [r8],xmm0
0x66f0032  movzx eax,byte ptr [rbp+0x10CC]
0x66f0039  mov [rbp+0x159C],al
0x66f003f  movups xmm0,[rbp+0x10D0]
0x66f0046  movups [rbp+0x15A0],xmm0
0x66f004d  movups xmm0,[r13+0x90]
0x66f0055  movups xmm1,[r13+0xA0]
0x66f005d  movups xmm2,[r13+0xAF]
0x66f0065  lea rdx,[rbp+0x1444]
0x66f006c  movups [rdx+0x18B],xmm2
0x66f0073  movups [rdx+0x17C],xmm1
0x66f007a  movups [rdx+0x16C],xmm0
0x66f0081  movzx eax,word ptr [rbp+0x1110]
0x66f0088  mov [rbp+0x15E0],ax
0x66f008f  mov rax,[rbp+0x16A8]
0x66f0096  mov rcx,[rax+0x10]
0x66f009a  mov eax,0x9D0
0x66f009f  add rcx,rax
0x66f00a2  mov [rsp+0x30],rdx
0x66f00a7  lea rax,[rbp+0x1450]
0x66f00ae  mov [rsp+0x28],rax
0x66f00b3  lea rax,[rbp+0x14D8]
0x66f00ba  mov [rsp+0x20],rax
0x66f00bf  lea rdx,[rbp+0x15E0]
0x66f00c6  lea r9,[rbp+0x1530]
0x66f00cd  call 0x678E670
0x66f00d2  nop
0x66f00d3  lea rcx,[rbp+0x1440]
0x66f00da  call 0x67E1660
0x66f00df  lea rcx,[rbp+0xF70]
0x66f00e6  call 0x67E1660
0x66f00eb  test sil,sil
```
Meaning: Call 0x678E420(&model [rbp+0x1440], &out [rbp+0x1060], &tmp [rbp+0x1008], [rbp+0xF80]) item assemble [V]. Copy to staging [rbp+0x1588]: [r8+0x10]=[r13+0x78], [r8]=[r13+0x68], byte [rbp+0x159C]=[rbp+0x10CC], [rbp+0x15A0]=[rbp+0x10D0], xmm0/1/2=[r13+0x90/A0/AF]->[rdx+0x16C/17C/18B], word [rbp+0x15E0]=[rbp+0x1110] [V]. Call 0x678E670(&model, &[rbp+0x1450], &[rbp+0x14D8], &[rbp+0x15E0], &[rbp+0x1530]) — different item writer [V]. Destroy geometry: 0x67E1660([rbp+0x1440]), 0x67E1660([rbp+0xF70]) [V]. If sil!=0 jump 0x66F26C0 else 0x66F2700. Callee RVAs: 0x678e420, 0x678e670, 0x67e1660 [V].

## NEXT
Next line to do: 681 (phase 17 of 18 complete)

### lines 681..700
```asm
0x66f00ee  jne 0x66F26C0
0x66f00f4  jmp 0x66F2700
0x66f00f9  lea rcx,[rbp+0xEA8]
0x66f0100  mov rdi,rdx
0x66f0103  call 0x678CF10
0x66f0108  nop
0x66f0109  lea rcx,[rbp+0x1440]
0x66f0110  lea rdx,[rbp+0x1050]
0x66f0117  lea r8,[rbp+0xFF8]
0x66f011e  mov r9,rdi
0x66f0121  call 0x678F640
0x66f0126  nop
0x66f0127  mov eax,[r13+0x68]
0x66f012b  lea rcx,[rbp+0x1580]
0x66f0132  mov [rcx+0x10],eax
0x66f0135  movups xmm0,[r13+0x58]
0x66f013a  movups [rcx],xmm0
0x66f013d  movzx eax,byte ptr [rbp+0x10BC]
0x66f0144  mov [rbp+0x1594],al
0x66f014a  movups xmm0,[rbp+0x10C0]
```
Meaning: Feature flag branch: if [rbp+0x16BE]!=0 (sil from dil at 0x66ef789): call 0x678CF10(&[rbp+0xEA8], rdi=rdx) binder [V]; call 0x678F640(&model [rbp+0x1440], &out [rbp+0x1050], &tmp [rbp+0xFF8], rdi) pack [V]. Copy staging [rbp+0x1580]: [rcx+0x10]=[r13+0x68], [rcx]=[r13+0x58], byte [rbp+0x1594]=[rbp+0x10BC], [rbp+0x1598]=[rbp+0x10C0], xmm0/1/2=[r13+0x80/90/9F]->[rbp+0x1444+0x164/174/183], word [rbp+0x15D8]=[rbp+0x1100] [V]. Push pool via 0x5ABA5C0 [V]. Callee RVAs: 0x678cf10, 0x678f640, 0x5aba5c0 [V].

## NEXT
Next line to do: 701 (phase 18 of 18 complete)
