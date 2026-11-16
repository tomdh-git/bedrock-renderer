# Unit U-E4X-C3: chunk extractor body C, listing lines 1401..2012 (end)

Source: docs/data/listings/e4_C.txt (each line `0xRVA instruction`), Body C = 0x66f2820..0x66f4f5a per docs/functions/66ea3d0.md.
Context: continuation of U-E4X-C1 (lines 1..700); C3 covers the tail of Body C from listing line 1401 to end of file (line 2012, RVA 0x66f4f5a).
Tags: [V] = seen in this listing, [I] = inferred from structure, [?] = unknown.

### lines 1401..1440

```
0x66f4462  lea r8,[rbp+0x1130]
0x66f4469  call 0x5ABA6D0
0x66f446e  nop
0x66f446f  mov rcx,[0x1233E1B0]
0x66f4476  mov rax,[rcx]
0x66f4479  mov rax,[rax+0x10]
0x66f447d  movzx edx,byte ptr [rbp+0x16D4]
0x66f4484  call qword ptr [0xF99FFA0]
0x66f448a  nop
0x66f448b  lea rcx,[rbp+0x1440]
0x66f4492  call 0x67E1660
0x66f4497  lea rcx,[rbp+0xF70]
0x66f449e  call 0x67E1660
0x66f44a3  jmp 0x66F4E70
0x66f44a8  xor eax,eax
0x66f44aa  mov rcx,[rcx+0x20]
0x66f44ae  mov [rbp+0x1660],rcx
0x66f44b5  mov [rbp+0x1668],rax
0x66f44bc  lea rax,[rbp+0x1370]
0x66f44c3  mov [rsp+0x38],rax
0x66f44c8  lea rax,[rbp+0x1660]
0x66f44cf  mov [rsp+0x30],rax
0x66f44d4  mov eax,[rbp+0x1688]
0x66f44da  mov [rsp+0x28],ax
0x66f44df  mov rax,[rbp+0x16C0]
0x66f44e6  mov [rsp+0x20],rax
0x66f44eb  mov dword ptr [rsp+0x48],0xFFFFFF00
0x66f44f3  mov dword ptr [rsp+0x40],0xFFFFFF00
0x66f44fb  lea rcx,[rbp+0x12E0]
0x66f4502  lea rdx,[rbp+0x1420]
0x66f4509  movzx r8d,byte ptr [rbp+0x16D0]
0x66f4511  mov r9,0xFFFFFFFFFFFFFFFF
0x66f4518  call 0x673CC80
0x66f451d  movaps [rbp+0x1390],xmm6
0x66f4524  mov rax,[rbp+0x12E8]
0x66f452b  test rax,rax
0x66f452e  je short 0x66F453D
0x66f4530  lock inc dword ptr [rax+8]
0x66f4534  mov rax,[rbp+0x12E8]
0x66f453b  jmp short 0x66F453F
```

Meaning: Release branch at 0x66f448b destroys item [rbp+0x1440] via 0x67E1660 and geometry [rbp+0xF70] via 0x67E1660, then jumps to loop tail 0x66F4E70 [V]. Otherwise (0x66f44a8) stores shared_ptr pair {rax=null from xor, [rcx+0x20]} at [rbp+0x1660/0x1668] [V]. Prepares stack args {[rsp+0x38]=&[rbp+0x1370], [rsp+0x30]=&[rbp+0x1660], [rsp+0x28]=word [rbp+0x1688], [rsp+0x20]=[rbp+0x16C0] desc} and constants [rsp+0x48/0x40]=0xFFFFFF00 (-0x100) [V]. Calls 0x673CC80(&[rbp+0x12E0], &[rbp+0x1420], r8d=kind class [rbp+0x16D0], r9=-1) [V]. Retains shared_ptr [rbp+0x12E8]: ptr → [rbp+0x1390], lock-inc [rax+8] if non-null, ctrl → [rbp+0x1398] [V].

### lines 1441..1480

```
0x66f453d  xor eax,eax
0x66f453f  mov rcx,[rbp+0x12E0]
0x66f4546  mov [rbp+0x1390],rcx
0x66f454d  mov [rbp+0x1398],rax
0x66f4554  lea rdx,[rbp+0x12F0]
0x66f455b  movzx eax,word ptr [rdx+0x10]
0x66f455f  lea rcx,[rbp+0x13A0]
0x66f4566  mov [rcx+0x10],ax
0x66f456a  movups xmm0,[rdx]
0x66f456d  movups [rcx],xmm0
0x66f4570  movups [rcx+0x18],xmm6
0x66f4574  mov rax,[rbp+0x1310]
0x66f457b  test rax,rax
0x66f457e  je short 0x66F458D
0x66f4580  lock inc dword ptr [rax+8]
0x66f4584  mov rax,[rbp+0x1310]
0x66f458b  jmp short 0x66F458F
0x66f458d  xor eax,eax
0x66f458f  mov rcx,[rbp+0x1308]
0x66f4596  mov [rbp+0x13B8],rcx
0x66f459d  mov [rbp+0x13C0],rax
0x66f45a4  lea rax,[rbp+0x13A0]
0x66f45ab  movups [rax+0x28],xmm6
0x66f45af  mov rax,[rbp+0x1320]
0x66f45b6  test rax,rax
0x66f45b9  je short 0x66F45C8
0x66f45bb  lock inc dword ptr [rax+8]
0x66f45bf  mov rax,[rbp+0x1320]
0x66f45c6  jmp short 0x66F45CA
0x66f45c8  xor eax,eax
0x66f45ca  mov rcx,[rbp+0x1318]
0x66f45d1  mov [rbp+0x13C8],rcx
0x66f45d8  mov [rbp+0x13D0],rax
0x66f45df  lea rax,[rbp+0x13A0]
0x66f45e6  movups [rax+0x38],xmm6
0x66f45ea  mov rax,[rbp+0x1330]
0x66f45f1  test rax,rax
0x66f45f4  je short 0x66F4603
0x66f45f6  lock inc dword ptr [rax+8]
0x66f45fa  mov r14,[rbp+0x1330]
```

Meaning: Populates struct at [rbp+0x13A0]: [rbp+0x1390]=[rbp+0x12E0] ptr, [rbp+0x1398]=ctrl retained above [V]; word at [rbp+0x12F0+0x10] → [rcx+0x10], vec4 [rbp+0x12F0] → [rcx], zero [rcx+0x18] [V]. Then copies shared_ptr fields {[rbp+0x1310],[rbp+0x1308],[rbp+0x1318],[rbp+0x1320],[rbp+0x1328],[rbp+0x1330],[rbp+0x1338]} into ptr slots [rbp+0x13B8/0x13C8/0x13D8/0x13E8] and ctrl slots [rbp+0x13C0/0x13D0/0x13E0], lock-inc each if non-null else zero [V]. Zeroes struct slots [rax+0x28] and [rax+0x38] of [rbp+0x13A0] [V]. Retains [rbp+0x1330] into r14 [V].

### lines 1481..1520

```
0x66f4601  jmp short 0x66F4606
0x66f4603  xor r14d,r14d
0x66f4606  mov rax,[rbp+0x1328]
0x66f460d  mov rcx,[rbp+0x1338]
0x66f4614  mov [rbp+0x13D8],rax
0x66f461b  mov [rbp+0x13E0],r14
0x66f4622  mov [rbp+0x13E8],rcx
0x66f4629  lea rcx,[rbp+0xEA8]
0x66f4630  lea rbx,[rbp+0xF70]
0x66f4637  mov rdx,rbx
0x66f463a  call 0x67A75D0
0x66f463f  nop
0x66f4640  lea rax,[rbp+0x1390]
0x66f4647  mov [rsp+0x20],rax
0x66f464c  lea rcx,[rbp+0x1440]
0x66f4653  mov rdx,r12
0x66f4656  lea r8,[rbp+0xFF8]
0x66f465d  mov r9,rbx
0x66f4660  call 0x678EF40
0x66f4665  nop
0x66f4666  mov eax,[r12+0x60]
0x66f466b  lea rcx,[rbp+0x15D8]
0x66f4672  mov [rcx+0x10],eax
0x66f4675  movups xmm0,[r12+0x50]
0x66f467b  movups [rcx],xmm0
0x66f467e  movzx eax,byte ptr [rbp+0x10B4]
0x66f4685  mov [rbp+0x15EC],al
0x66f468b  movups xmm0,[rbp+0x10B8]
0x66f4692  movups [rbp+0x15F0],xmm0
0x66f4699  movups xmm0,[r12+0x78]
0x66f469f  movups xmm1,[r12+0x88]
0x66f46a8  movups xmm2,[r12+0x97]
0x66f46b1  movups [rdi+0x1DB],xmm2
0x66f46b8  movups [rdi+0x1CC],xmm1
0x66f46bf  movups [rdi+0x1BC],xmm0
0x66f46c6  movzx eax,word ptr [rbp+0x10F8]
0x66f46cd  mov [rbp+0x1630],ax
0x66f46d4  mov rax,[rbp+0x16A8]
0x66f46db  mov rcx,[rax+0x10]
0x66f46df  mov eax,0x9D0
```

Meaning: Completes shared_ptr fill: [rbp+0x13D8]=[rbp+0x1328], [rbp+0x13E0]=r14, [rbp+0x13E8]=[rbp+0x1338] [V]. Calls 0x67A75D0(&[rbp+0xEA8], rdx=&[rbp+0xF70]) builds descriptor [V]; then 0x678EF40(rcx=&[rbp+0x1440], rdx=r12, r8=&[rbp+0xFF8], r9=&[rbp+0xF70]) packs geometry/material [V]. Copies descriptor tail into staging [rbp+0x15D8..]: u32 [r12+0x60] → [rcx+0x10], vec4 [r12+0x50] → [rcx], byte [rbp+0x10B4] → [rbp+0x15EC], vec4 [rbp+0x10B8] → [rbp+0x15F0] [V]. Copies vec3s [r12+0x78/0x88/0x97] → [rdi+0x1BC/0x1CC/0x1DB], u16 [rbp+0x10F8] → [rbp+0x1630] [V]. Computes pass = *(u64*)(*[rbp+0x16A8]+0x10) + 0x9D0 via 0x5ABA5C0 [V].

### lines 1521..1560

```
0x66f46e4  add rcx,rax
0x66f46e7  call 0x5ABA5C0
0x66f46ec  nop
0x66f46ed  mov rbx,rax
0x66f46f0  movups [r13-0x28],xmm6
0x66f46f5  movups [r13-0x38],xmm6
0x66f46fa  movups [r13-0x48],xmm6
0x66f46ff  movups [r13-0x58],xmm6
0x66f4704  movups [r13-0x68],xmm6
0x66f4709  movups [r13-0x78],xmm6
0x66f470e  movups [r13-0x88],xmm6
0x66f4716  movups [r13-0x98],xmm6
0x66f471e  movups [r13-0xA8],xmm6
0x66f4726  movups [r13-0xB8],xmm6
0x66f472e  movups [r13-0xC8],xmm6
0x66f4736  movups [r13-0xD8],xmm6
0x66f473e  mov rcx,[0x1233E1B0]
0x66f4745  mov rax,[rcx]
0x66f4748  mov rax,[rax+0x10]
0x66f474c  mov dl,0x4A
0x66f474e  call qword ptr [0xF99FFA0]
0x66f4754  nop
0x66f4755  mov [rbp+0x16D4],al
0x66f475b  mov rdx,[rbx+0x8A8]
0x66f4762  cmp rdx,[rbx+0x8B0]
0x66f4769  je short 0x66F477F
0x66f476b  movzx eax,word ptr [rbp+0x1630]
0x66f4772  mov [rdx],ax
0x66f4775  add qword ptr [rbx+0x8A8],2
0x66f477d  jmp short 0x66F4793
0x66f477f  lea rcx,[rbx+0x8A0]
0x66f4786  lea r8,[rbp+0x1630]
0x66f478d  call 0x1EF6F90
0x66f4792  nop
0x66f4793  mov rcx,[0x1233E1B0]
0x66f479a  mov rax,[rcx]
0x66f479d  mov rax,[rax+0x10]
0x66f47a1  movzx edx,byte ptr [rbp+0x16D4]
0x66f47a8  call qword ptr [0xF99FFA0]
0x66f47ae  nop
```

Meaning: pass = result of 0x5ABA5C0 thread-local getter → rbx [V]; zeroes 12×16-byte slots at [r13-0x28..0xD8] with xmm6=0 [V]. Feature flag: vcall(*[0x1233E1B0])->+0x10)(dl=0x4A) → al stored at [rbp+0x16D4] [V]. u16 pool push: [rbx+0x8A8] vs [rbx+0x8B0]; if full → slow path 0x66F477F calling 0x1EF6F90(&[rbx+0x8A0], &[rbp+0x1630]) [V]; else writes u16 [rbp+0x1630] at [rdx], advances cursor [rbx+0x8A8] += 2 [V], jumps to 0x66F4793 [V]. Second feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V].

### lines 1561..1600

```
0x66f47af  mov qword ptr [rbp+0x1130],1
0x66f47ba  mov eax,[rbx+0x8A8]
0x66f47c0  sub eax,[rbx+0x8A0]
0x66f47c6  shr eax,1
0x66f47c8  dec eax
0x66f47ca  mov [rbp+0x1140],ax
0x66f47d1  mov rcx,[0x1233E1B0]
0x66f47d8  mov rax,[rcx]
0x66f47db  mov rax,[rax+0x10]
0x66f47df  mov dl,0x4A
0x66f47e1  call qword ptr [0xF99FFA0]
0x66f47e7  nop
0x66f47e8  mov [rbp+0x16D4],al
0x66f47ee  mov rdx,[rbx+0x758]
0x66f47f5  cmp rdx,[rbx+0x760]
0x66f47fc  je short 0x66F487A
0x66f47fe  lea rcx,[rbp+0x15D8]
0x66f4805  mov eax,[rcx+0x10]
0x66f4808  mov [rdx+0x10],eax
0x66f480b  movups xmm0,[rcx]
0x66f480e  movups [rdx],xmm0
0x66f4811  movzx eax,byte ptr [rbp+0x15EC]
0x66f4818  mov [rdx+0x14],al
0x66f481b  (bad)
0x66f481c  movups xmm0,[rbp+0x15F0]
0x66f4823  movss [rdx+0x18],xmm0
0x66f4828  movss xmm0,[rbp+0x15F4]
0x66f4830  movss [rdx+0x1C],xmm0
0x66f4835  movss xmm0,[rbp+0x15F8]
0x66f483d  movss [rdx+0x20],xmm0
0x66f4842  movss xmm0,[rbp+0x15FC]
0x66f484a  movss [rdx+0x24],xmm0
0x66f484f  movups xmm0,[rdi+0x1BC]
0x66f4856  movups xmm1,[rdi+0x1CC]
0x66f485d  movups xmm2,[rdi+0x1DB]
0x66f4864  movups [rdx+0x28],xmm0
0x66f4868  movups [rdx+0x38],xmm1
0x66f486c  movups [rdx+0x47],xmm2
0x66f4870  add qword ptr [rbx+0x758],0x58
0x66f4878  jmp short 0x66F488E
```

Meaning: [rbp+0x1130]=1 (u64) [V]. Pool index = (([rbx+0x8A8]-[rbx+0x8A0])>>1) - 1 → [rbp+0x1140] [V]. Third feature flag query vcall(*[0x1233E1B0])->+0x10)(dl=0x4A) → [rbp+0x16D4] [V]. Pool entry push: [rbx+0x758] vs [rbx+0x760]; if full → 0x66F487A [V]; else writes u32 [rcx+0x10] → [rdx+0x10], vec4 [rcx] → [rdx], byte [rbp+0x15EC] → [rdx+0x14], (bad) at 0x66f481b, movss [rdx+0x18/0x1C/0x20/0x24] from [rbp+0x15F0/0x15F4/0x15F8/0x15FC], vec3s [rdi+0x1BC/0x1CC/0x1DB] → [rdx+0x28/0x38/0x47], advances [rbx+0x758] += 0x58, jumps to 0x66F488E [V].

### lines 1601..1640

```
0x66f487a  lea rcx,[rbx+0x750]
0x66f4881  lea r8,[rbp+0x15D8]
0x66f4888  call 0x6760A80
0x66f488d  nop
0x66f488e  mov rcx,[0x1233E1B0]
0x66f4895  mov rax,[rcx]
0x66f4898  mov rax,[rax+0x10]
0x66f489c  movzx edx,byte ptr [rbp+0x16D4]
0x66f48a3  call qword ptr [0xF99FFA0]
0x66f48a9  nop
0x66f48aa  mov eax,[rbx+0x758]
0x66f48b0  sub eax,[rbx+0x750]
0x66f48b6  shr eax,3
0x66f48b9  imul eax,0xFFFF8BA3
0x66f48bf  dec eax
0x66f48c1  mov [rbp+0x115C],ax
0x66f48c8  mov rcx,[0x1233E1B0]
0x66f48cf  mov rax,[rcx]
0x66f48d2  mov rax,[rax+0x10]
0x66f48d6  mov dl,0x4A
0x66f48d8  call qword ptr [0xF99FFA0]
0x66f48de  nop
0x66f48df  mov [rbp+0x16D4],al
0x66f48e5  mov rdx,[rbx+0x890]
0x66f48ec  cmp rdx,[rbx+0x898]
0x66f48f3  je short 0x66F4901
0x66f48f5  inc rdx
0x66f48f8  mov [rbx+0x890],rdx
0x66f48ff  jmp short 0x66F490E
0x66f4901  lea rcx,[rbx+0x888]
0x66f4908  call 0x6760E60
0x66f490d  nop
0x66f490e  mov rcx,[0x1233E1B0]
0x66f4915  mov rax,[rcx]
0x66f4918  mov rax,[rax+0x10]
0x66f491c  movzx edx,byte ptr [rbp+0x16D4]
0x66f4923  call qword ptr [0xF99FFA0]
0x66f4929  nop
0x66f492a  mov eax,[rbx+0x888]
0x66f4930  not eax
```

Meaning: If pool full (0x66f487a): calls 0x6760A80(&[rbx+0x750], &[rbp+0x15D8]) [V]. Fourth feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]. Pool count = (([rbx+0x758]-[rbx+0x750])>>3)*0xFFFF8BA3 - 1 → [rbp+0x115C] [V] (index math). Fifth feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]. Counter: [rbx+0x890] vs [rbx+0x898]; if not full inc rdx and store [rbx+0x890] → jump 0x66F490E; if full call 0x6760E60(&[rbx+0x888]) [V]. Sixth feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]; eax=[rbx+0x888], not eax [V].

### lines 1641..1680

```
0x66f4932  add eax,[rbx+0x890]
0x66f4938  mov [rbp+0x1142],ax
0x66f493f  mov rcx,[0x1233E1B0]
0x66f4946  mov rax,[rcx]
0x66f4949  mov rax,[rax+0x10]
0x66f494d  mov dl,0x4A
0x66f494f  call qword ptr [0xF99FFA0]
0x66f4955  mov [rbp+0x16D4],al
0x66f495b  lea rcx,[rbx+0x648]
0x66f4962  lea rdx,[rbp+0x1588]
0x66f4969  call 0x675FB30
0x66f496e  nop
0x66f496f  mov rcx,[0x1233E1B0]
0x66f4976  mov rax,[rcx]
0x66f4979  mov rax,[rax+0x10]
0x66f497d  movzx edx,byte ptr [rbp+0x16D4]
0x66f4984  call qword ptr [0xF99FFA0]
0x66f498a  nop
0x66f498b  mov eax,[rbx+0x650]
0x66f4991  sub eax,[rbx+0x648]
0x66f4997  shr eax,3
0x66f499a  imul eax,0xFFFF8E39
0x66f49a0  dec eax
0x66f49a2  mov [rbp+0x1172],ax
0x66f49a9  lea rcx,[rbx+0x780]
0x66f49b0  lea rdx,[rbp+0x1530]
0x66f49b7  call 0x675F3B0
0x66f49bc  nop
0x66f49bd  mov qword ptr [rbp+0x1130],0x2005003
0x66f49c8  mov eax,[rbx+0x788]
0x66f49ce  sub eax,[rbx+0x780]
0x66f49d4  shr eax,3
0x66f49d7  imul eax,0xFFFF8BA3
0x66f49dd  dec eax
0x66f49df  mov [rbp+0x1158],ax
0x66f49e6  mov rcx,[0x1233E1B0]
0x66f49ed  mov rax,[rcx]
0x66f49f0  mov rax,[rax+0x10]
0x66f49f4  mov dl,0x4A
0x66f49f6  call qword ptr [0xF99FFA0]
```

Meaning: eax += [rbx+0x890] → [rbp+0x1142] [V]. Seventh feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]. Call 0x675FB30(rcx=&[rbx+0x648], rdx=&[rbp+0x1588]) [V]. Eighth feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]. Count = (([rbx+0x650]-[rbx+0x648])>>3)*0xFFFF8E39 - 1 → [rbp+0x1172] [V]. Call 0x675F3B0(rcx=&[rbx+0x780], rdx=&[rbp+0x1530]) [V]. [rbp+0x1130]=0x2005003 (u64) [V]. Count = (([rbx+0x788]-[rbx+0x780])>>3)*0xFFFF8BA3 - 1 → [rbp+0x1158] [V]. Ninth feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V].

### lines 1681..1720

```
0x66f49fc  mov [rbp+0x16D4],al
0x66f4a02  mov r15,[rbx+0x770]
0x66f4a09  cmp r15,[rbx+0x778]
0x66f4a10  je short 0x66F4A53
0x66f4a12  mov rax,[rbp+0x14A8]
0x66f4a19  mov [r15],rax
0x66f4a1c  lea rcx,[r15+8]
0x66f4a20  lea rdx,[rbp+0x14B0]
0x66f4a27  call 0xE869FF0
0x66f4a2c  nop
0x66f4a2d  mov rax,[rbp+0x1528]
0x66f4a34  mov [r15+0x80],rax
0x66f4a3b  mov qword ptr [rbp+0x1528],0
0x66f4a46  add qword ptr [rbx+0x770],0x88
0x66f4a51  jmp short 0x66F4A6A
0x66f4a53  lea rcx,[rbx+0x768]
0x66f4a5a  mov rdx,r15
0x66f4a5d  lea r8,[rbp+0x14A8]
0x66f4a64  call 0x6760710
0x66f4a69  nop
0x66f4a6a  mov rcx,[0x1233E1B0]
0x66f4a71  mov rax,[rcx]
0x66f4a74  mov rax,[rax+0x10]
0x66f4a78  movzx edx,byte ptr [rbp+0x16D4]
0x66f4a7f  call qword ptr [0xF99FFA0]
0x66f4a85  nop
0x66f4a86  mov eax,[rbx+0x770]
0x66f4a8c  sub eax,[rbx+0x768]
0x66f4a92  shr eax,3
0x66f4a95  imul eax,0xFFFFF0F1
0x66f4a9b  dec eax
0x66f4a9d  mov [rbp+0x115A],ax
0x66f4aa4  mov rcx,[0x1233E1B0]
0x66f4aab  mov rax,[rcx]
0x66f4aae  mov rax,[rax+0x10]
0x66f4ab2  mov dl,0x4A
0x66f4ab4  call qword ptr [0xF99FFA0]
0x66f4aba  nop
0x66f4abb  mov [rbp+0x16D4],al
0x66f4ac1  mov rdx,[rbx+0x2D8]
```

Meaning: [rbp+0x16D4]=al [V]. Slot push: r15=[rbx+0x770], cmp vs [rbx+0x778]; if not full: [r15]=[rbp+0x14A8], 0xE869FF0(&[r15+8], &[rbp+0x14B0]) [V], [r15+0x80]=[rbp+0x1528], [rbp+0x1528]=0, [rbx+0x770] += 0x88, jump 0x66F4A6A [V]; if full: 0x6760710(&[rbx+0x768], rdx=r15, r8=&[rbp+0x14A8]) [V]. Tenth feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]. Count = (([rbx+0x770]-[rbx+0x768])>>3)*0xFFFFF0F1 - 1 → [rbp+0x115A] [V]. Eleventh feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]; rdx=[rbx+0x2D8] [V].

### lines 1721..1760

```
0x66f4ac8  cmp rdx,[rbx+0x2E0]
0x66f4acf  je short 0x66F4ADD
0x66f4ad1  inc rdx
0x66f4ad4  mov [rbx+0x2D8],rdx
0x66f4adb  jmp short 0x66F4AEA
0x66f4add  lea rcx,[rbx+0x2D0]
0x66f4ae4  call 0x6760E60
0x66f4ae9  nop
0x66f4aea  mov rcx,[0x1233E1B0]
0x66f4af1  mov rax,[rcx]
0x66f4af4  mov rax,[rax+0x10]
0x66f4af8  movzx edx,byte ptr [rbp+0x16D4]
0x66f4aff  call qword ptr [0xF99FFA0]
0x66f4b05  nop
0x66f4b06  mov eax,[rbx+0x2D0]
0x66f4b0c  not eax
0x66f4b0e  add eax,[rbx+0x2D8]
0x66f4b14  mov [rbp+0x11BC],ax
0x66f4b1b  mov rcx,rbx
0x66f4b1e  add rcx,0x5D0
0x66f4b25  lea rdx,[rbp+0x1440]
0x66f4b2c  call 0x678D690
0x66f4b31  nop
0x66f4b32  mov rax,0x4000000042007003
0x66f4b3c  mov [rbp+0x1130],rax
0x66f4b43  mov eax,[rbx+0x5D8]
0x66f4b49  sub eax,[rbx+0x5D0]
0x66f4b4f  shr eax,5
0x66f4b52  imul eax,0xFFFFAAAB
0x66f4b58  dec eax
0x66f4b5a  mov [rbp+0x117C],ax
0x66f4b61  mov rcx,[0x1233E1B0]
0x66f4b68  mov rax,[rcx]
0x66f4b6b  mov rax,[rax+0x10]
0x66f4b6f  mov dl,0x4A
0x66f4b71  call qword ptr [0xF99FFA0]
0x66f4b77  nop
0x66f4b78  mov [rbp+0x16D4],al
0x66f4b7e  mov rdx,[rbx+8]
0x66f4b82  cmp rdx,[rbx+0x10]
```

Meaning: Counter: [rbx+0x2D8] vs [rbx+0x2E0]; if not equal inc rdx, store [rbx+0x2D8], jump 0x66F4AEA; if equal call 0x6760E60(&[rbx+0x2D0]) [V]. Twelfth feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]. Count = (~[rbx+0x2D0] + [rbx+0x2D8]) → [rbp+0x11BC] [V]. Calls 0x678D690(rcx=rbx+0x5D0, rdx=&[rbp+0x1440]) [V]. [rbp+0x1130]=0x4000000042007003 (u64) [V]. Count = (([rbx+0x5D8]-[rbx+0x5D0])>>5)*0xFFFFAAAB - 1 → [rbp+0x117C] [V]. Thirteenth feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]; rdx=[rbx+8] vs [rbx+0x10] [V].

### lines 1761..1800

```
0x66f4b86  je short 0x66F4BA7
0x66f4b88  mov r8d,0xC8
0x66f4b8e  mov rcx,rdx
0x66f4b91  lea rdx,[rbp+0x1130]
0x66f4b98  call 0xEEC6EC0
0x66f4b9d  add qword ptr [rbx+8],0xC8
0x66f4ba5  jmp short 0x66F4BB7
0x66f4ba7  mov rcx,rbx
0x66f4baa  lea r8,[rbp+0x1130]
0x66f4bb1  call 0x5ABA6D0
0x66f4bb6  nop
0x66f4bb7  mov rcx,[0x1233E1B0]
0x66f4bbe  mov rax,[rcx]
0x66f4bc1  mov rax,[rax+0x10]
0x66f4bc5  movzx edx,byte ptr [rbp+0x16D4]
0x66f4bcc  call qword ptr [0xF99FFA0]
0x66f4bd2  nop
0x66f4bd3  cmp byte ptr [rbp+0x15C8],1
0x66f4bda  jne short 0x66F4C2E
0x66f4bdc  mov rcx,[rbp+0x1588]
0x66f4be3  test rcx,rcx
0x66f4be6  je short 0x66F4C2E
0x66f4be8  mov rdx,[rbp+0x1598]
0x66f4bef  sub rdx,rcx
0x66f4bf2  cmp rdx,0x1000
0x66f4bf9  jb short 0x66F4C17
0x66f4bfb  mov rax,[rcx-8]
0x66f4bff  add rcx,0xFFFFFFFFFFFFFFF8
0x66f4c03  sub rcx,rax
0x66f4c06  cmp rcx,0x20
0x66f4c0a  jae 0x66F82BB
0x66f4c10  or rdx,0x27
0x66f4c14  mov rcx,rax
0x66f4c17  call 0xE935700
0x66f4c1c  lea rax,[rbp+0x1588]
0x66f4c23  movups [rax],xmm6
0x66f4c26  mov qword ptr [rax+0x10],0
0x66f4c2e  lea rcx,[rbp+0x1440]
0x66f4c35  call 0x678F260
0x66f4c3a  lea rcx,[rbp+0xF70]
```

Meaning: Buffer: [rbx+8] vs [rbx+0x10]; if not equal: r8d=0xC8, rcx=rdx, rdx=&[rbp+0x1130], call 0xEEC6EC0, [rbx+8] += 0xC8, jump 0x66F4BB7 [V]; if equal: 0x5ABA6D0(rcx=rbx, r8=&[rbp+0x1130]) [V]. Fourteenth feature flag query vcall(dl=0x4A) → [rbp+0x16D4] [V]. If byte [rbp+0x15C8]==1 and [rbp+0x1588] non-null: rdx=[rbp+0x1598]-[rbp+0x1588]; if >= 0x1000: rax=[rcx-8], rcx-=8, rcx-=rax, if >=0x20 → throw 0x66F82BB; else rdx|=0x27, rcx=rax [V]; call 0xE935700(rcx) [V]; zeroes [rbp+0x1588] (movups xmm6) and [rax+0x10]=0 [V]. Otherwise → 0x66F4C2E [V]. Calls 0x678F260(&[rbp+0x1440]) [V]; rcx=&[rbp+0xF70] [V].

### lines 1801..1840

```
0x66f4c41  call 0x67E23F0
0x66f4c46  test r14,r14
0x66f4c49  je short 0x66F4C78
0x66f4c4b  lock dec dword ptr [r14+8]
0x66f4c50  jne short 0x66F4C78
0x66f4c52  mov rax,[r14]
0x66f4c55  mov rax,[rax]
0x66f4c58  mov rcx,r14
0x66f4c5b  call qword ptr [0xF99FFA0]
0x66f4c61  lock dec dword ptr [r14+0xC]
0x66f4c66  jne short 0x66F4C78
0x66f4c68  mov rax,[r14]
0x66f4c6b  mov rax,[rax+8]
0x66f4c6f  mov rcx,r14
0x66f4c72  call qword ptr [0xF99FFA0]
0x66f4c78  mov rbx,[rbp+0x13D0]
0x66f4c7f  test rbx,rbx
0x66f4c82  je short 0x66F4CAF
0x66f4c84  lock dec dword ptr [rbx+8]
0x66f4c88  jne short 0x66F4CAF
0x66f4c8a  mov rax,[rbx]
0x66f4c8d  mov rax,[rax]
0x66f4c90  mov rcx,rbx
0x66f4c93  call qword ptr [0xF99FFA0]
0x66f4c99  lock dec dword ptr [rbx+0xC]
0x66f4c9d  jne short 0x66F4CAF
0x66f4c9f  mov rax,[rbx]
0x66f4ca2  mov rax,[rax+8]
0x66f4ca6  mov rcx,rbx
0x66f4ca9  call qword ptr [0xF99FFA0]
0x66f4caf  mov rbx,[rbp+0x13C0]
0x66f4cb6  test rbx,rbx
0x66f4cb9  je short 0x66F4CE6
0x66f4cbb  lock dec dword ptr [rbx+8]
0x66f4cbf  jne short 0x66F4CE6
0x66f4cc1  mov rax,[rbx]
0x66f4cc4  mov rax,[rax]
0x66f4cc7  mov rcx,rbx
0x66f4cca  call qword ptr [0xF99FFA0]
0x66f4cd0  lock dec dword ptr [rbx+0xC]
```

Meaning: Calls 0x67E23F0(&[rbp+0xF70]) releases geometry [V]. Shared_ptr release chain: for each of { [rbp+0x13D0], [rbp+0x13C0] }: test null → skip target (0x66F4C78/0x66F4CAF); lock-dec [rbx+8]; if !=0 skip; else mov rax=[rbx], rax=[rax] (vtable), call qword ptr [0xF99FFA0] (destroy object), lock-dec [rbx+0xC]; if !=0 skip; else mov rax=[rbx], rax=[rax+8], call [0xF99FFA0] (destroy ctrl block) [V].

### lines 1841..1880

```
0x66f4cd4  jne short 0x66F4CE6
0x66f4cd6  mov rax,[rbx]
0x66f4cd9  mov rax,[rax+8]
0x66f4cdd  mov rcx,rbx
0x66f4ce0  call qword ptr [0xF99FFA0]
0x66f4ce6  mov rbx,[rbp+0x1398]
0x66f4ced  test rbx,rbx
0x66f4cf0  je short 0x66F4D1D
0x66f4cf2  lock dec dword ptr [rbx+8]
0x66f4cf6  jne short 0x66F4D1D
0x66f4cf8  mov rax,[rbx]
0x66f4cfb  mov rax,[rax]
0x66f4cfe  mov rcx,rbx
0x66f4d01  call qword ptr [0xF99FFA0]
0x66f4d07  lock dec dword ptr [rbx+0xC]
0x66f4d0b  jne short 0x66F4D1D
0x66f4d0d  mov rax,[rbx]
0x66f4d10  mov rax,[rax+8]
0x66f4d14  mov rcx,rbx
0x66f4d17  call qword ptr [0xF99FFA0]
0x66f4d1d  mov rbx,[rbp+0x1330]
0x66f4d24  test rbx,rbx
0x66f4d27  je short 0x66F4D54
0x66f4d29  lock dec dword ptr [rbx+8]
0x66f4d2d  jne short 0x66F4D54
0x66f4d2f  mov rax,[rbx]
0x66f4d32  mov rax,[rax]
0x66f4d35  mov rcx,rbx
0x66f4d38  call qword ptr [0xF99FFA0]
0x66f4d3e  lock dec dword ptr [rbx+0xC]
0x66f4d42  jne short 0x66F4D54
0x66f4d44  mov rax,[rbx]
0x66f4d47  mov rax,[rax+8]
0x66f4d4b  mov rcx,rbx
0x66f4d4e  call qword ptr [0xF99FFA0]
0x66f4d54  mov rbx,[rbp+0x1320]
0x66f4d5b  test rbx,rbx
0x66f4d5e  je short 0x66F4D8B
0x66f4d60  lock dec dword ptr [rbx+8]
0x66f4d64  jne short 0x66F4D8B
```

Meaning: Continues shared_ptr release chain for { [rbp+0x13C0] ctrl destroy via [0xF99FFA0], [rbp+0x1398], [rbp+0x1330], [rbp+0x1320] } with same pattern (dec [rbx+8], destroy object via [0xF99FFA0], dec [rbx+0xC], destroy ctrl block via [0xF99FFA0]) [V]. Each release skips to next target (0x66F4CE6/0x66F4D1D/0x66F4D54/0x66F4D8B) on non-zero refcount [V]. Ends at [rbp+0x1320] release entry (lock-dec [rbx+8], jne 0x66F4D8B) [V].

### lines 1881..1920

```
0x66f4d66  mov rax,[rbx]
0x66f4d69  mov rax,[rax]
0x66f4d6c  mov rcx,rbx
0x66f4d6f  call qword ptr [0xF99FFA0]
0x66f4d75  lock dec dword ptr [rbx+0xC]
0x66f4d79  jne short 0x66F4D8B
0x66f4d7b  mov rax,[rbx]
0x66f4d7e  mov rax,[rax+8]
0x66f4d82  mov rcx,rbx
0x66f4d85  call qword ptr [0xF99FFA0]
0x66f4d8b  mov rbx,[rbp+0x1310]
0x66f4d92  test rbx,rbx
0x66f4d95  je short 0x66F4DC2
0x66f4d97  lock dec dword ptr [rbx+8]
0x66f4d9b  jne short 0x66F4DC2
0x66f4d9d  mov rax,[rbx]
0x66f4da0  mov rax,[rax]
0x66f4da3  mov rcx,rbx
0x66f4da6  call qword ptr [0xF99FFA0]
0x66f4dac  lock dec dword ptr [rbx+0xC]
0x66f4db0  jne short 0x66F4DC2
0x66f4db2  mov rax,[rbx]
0x66f4db5  mov rax,[rax+8]
0x66f4db9  mov rcx,rbx
0x66f4dbc  call qword ptr [0xF99FFA0]
0x66f4dc2  mov rbx,[rbp+0x12E8]
0x66f4dc9  test rbx,rbx
0x66f4dcc  je short 0x66F4DF9
0x66f4dce  lock dec dword ptr [rbx+8]
0x66f4dd2  jne short 0x66F4DF9
0x66f4dd4  mov rax,[rbx]
0x66f4dd7  mov rax,[rax]
0x66f4dda  mov rcx,rbx
0x66f4ddd  call qword ptr [0xF99FFA0]
0x66f4de3  lock dec dword ptr [rbx+0xC]
0x66f4de7  jne short 0x66F4DF9
0x66f4de9  mov rax,[rbx]
0x66f4dec  mov rax,[rax+8]
0x66f4df0  mov rcx,rbx
0x66f4df3  call qword ptr [0xF99FFA0]
```

Meaning: Finishes [rbp+0x1320] release: destroy object via [0xF99FFA0], lock-dec [rbx+0xC], if zero destroy ctrl via [0xF99FFA0] [V]. Continues release chain for { [rbp+0x1310], [rbp+0x12E8] }: same pattern (test null → skip to 0x66F4DC2/0x66F4DF9; lock-dec [rbx+8]; destroy object via [0xF99FFA0]; lock-dec [rbx+0xC]; destroy ctrl via [0xF99FFA0]) [V].

### lines 1921..1960

```
0x66f4df9  mov rbx,[rbp+0x1668]
0x66f4e00  test rbx,rbx
0x66f4e03  je short 0x66F4E30
0x66f4e05  lock dec dword ptr [rbx+8]
0x66f4e09  jne short 0x66F4E30
0x66f4e0b  mov rax,[rbx]
0x66f4e0e  mov rax,[rax]
0x66f4e11  mov rcx,rbx
0x66f4e14  call qword ptr [0xF99FFA0]
0x66f4e1a  lock dec dword ptr [rbx+0xC]
0x66f4e1e  jne short 0x66F4E30
0x66f4e20  mov rax,[rbx]
0x66f4e23  mov rax,[rax+8]
0x66f4e27  mov rcx,rbx
0x66f4e2a  call qword ptr [0xF99FFA0]
0x66f4e30  mov rbx,[rbp+0x1378]
0x66f4e37  test rbx,rbx
0x66f4e3a  je short 0x66F4E70
0x66f4e3c  lock dec dword ptr [rbx+8]
0x66f4e40  jne short 0x66F4E70
0x66f4e42  mov rax,[rbx]
0x66f4e45  mov rax,[rax]
0x66f4e48  mov rcx,rbx
0x66f4e4b  call qword ptr [0xF99FFA0]
0x66f4e51  lock dec dword ptr [rbx+0xC]
0x66f4e55  jne short 0x66F4E70
0x66f4e57  mov rax,[rbx]
0x66f4e5a  mov rax,[rax+8]
0x66f4e5e  mov rcx,rbx
0x66f4e61  call qword ptr [0xF99FFA0]
0x66f4e67  nop [rax+rax]
0x66f4e70  mov rbx,[rbp+0x1428]
0x66f4e77  test rbx,rbx
0x66f4e7a  je short 0x66F4EB0
0x66f4e7c  lock dec dword ptr [rbx+8]
0x66f4e80  jne short 0x66F4EB0
0x66f4e82  mov rax,[rbx]
0x66f4e85  mov rax,[rax]
0x66f4e88  mov rcx,rbx
0x66f4e8b  call qword ptr [0xF99FFA0]
```

Meaning: Finishes [rbp+0x1668] release then [rbp+0x1378] release (if zero refcount → jump loop tail 0x66F4E70) [V]. Loop tail 0x66f4e70: rbx=[rbp+0x1428] (cached shared_ptr ctrl retained earlier), test null → 0x66F4EB0; lock-dec [rbx+8]; destroy object via [0xF99FFA0] [V].

### lines 1961..2000

```
0x66f4e91  lock dec dword ptr [rbx+0xC]
0x66f4e95  jne short 0x66F4EB0
0x66f4e97  mov rax,[rbx]
0x66f4e9a  mov rax,[rax+8]
0x66f4e9e  mov rcx,rbx
0x66f4ea1  call qword ptr [0xF99FFA0]
0x66f4ea7  nop [rax+rax]
0x66f4eb0  cmp byte ptr [rbp+0xDF0],3
0x66f4eb7  jne short 0x66F4EF0
0x66f4eb9  mov rbx,[rbp+0xDE8]
0x66f4ec0  test rbx,rbx
0x66f4ec3  je short 0x66F4EF0
0x66f4ec5  lock dec dword ptr [rbx+8]
0x66f4ec9  jne short 0x66F4EF0
0x66f4ecb  mov rax,[rbx]
0x66f4ece  mov rax,[rax]
0x66f4ed1  mov rcx,rbx
0x66f4ed4  call qword ptr [0xF99FFA0]
0x66f4eda  lock dec dword ptr [rbx+0xC]
0x66f4ede  jne short 0x66F4EF0
0x66f4ee0  mov rax,[rbx]
0x66f4ee3  mov rax,[rax+8]
0x66f4ee7  mov rcx,rbx
0x66f4eea  call qword ptr [0xF99FFA0]
0x66f4ef0  mov r14,[rbp+0xDC0]
0x66f4ef7  test r14,r14
0x66f4efa  je 0x66F2D00
0x66f4f00  mov r15,[rbp+0xDC8]
0x66f4f07  jmp short 0x66F4F14
0x66f4f09  nop [rax]
0x66f4f10  add r14,0x28
0x66f4f14  cmp r14,r15
0x66f4f17  je 0x66F2D00
0x66f4f1d  cmp byte ptr [r14+0x18],2
0x66f4f22  jne short 0x66F4F10
0x66f4f24  mov rbx,[r14+8]
0x66f4f28  test rbx,rbx
0x66f4f2b  je short 0x66F4F10
0x66f4f2d  lock dec dword ptr [rbx+8]
0x66f4f31  jne short 0x66F4F10
```

Meaning: Finishes [rbp+0x1428] release: lock-dec [rbx+0xC]; if zero destroy ctrl via [0xF99FFA0] [V]. If byte [rbp+0xDF0]==3: rbx=[rbp+0xDE8], release shared_ptr (dec [rbx+8], destroy object [0xF99FFA0], dec [rbx+0xC], destroy ctrl [0xF99FFA0]) → else skip to 0x66F4EF0 [V]. Cleanup loop over entries [rbp+0xDC0..0xDC8] stride 0x28: r14=[rbp+0xDC0]; if null → 0x66F2D00 (re-enter pass-2 loop at entry step); r15=[rbp+0xDC8]; while r14 != r15: if byte [r14+0x18]!=2 skip; rbx=[r14+8]; release shared_ptr (dec [rbx+8], if zero destroy object then ctrl via [0xF99FFA0]) → loop 0x66F4F10 [V].

### lines 2001..2012

```
0x66f4f33  mov rax,[rbx]
0x66f4f36  mov rax,[rax]
0x66f4f39  mov rcx,rbx
0x66f4f3c  call qword ptr [0xF99FFA0]
0x66f4f42  lock dec dword ptr [rbx+0xC]
0x66f4f46  jne short 0x66F4F10
0x66f4f48  mov rax,[rbx]
0x66f4f4b  mov rax,[rax+8]
0x66f4f4f  mov rcx,rbx
0x66f4f52  call qword ptr [0xF99FFA0]
0x66f4f58  jmp short 0x66F4F10
0x66f4f5a  mov rsi,[rbp+0x1670]
```

Meaning: Finish shared_ptr release inside cleanup loop: destroy object via [0xF99FFA0], lock-dec [rbx+0xC], if zero destroy ctrl via [0xF99FFA0], jmp 0x66F4F10 [V]. Body C ends at line 2012 / RVA 0x66f4f5a: `mov rsi,[rbp+0x1670]` — the resolved-item vector head [V]; this is the last line of docs/data/listings/e4_C.txt, so Body C ends at RVA 0x66f4f5a [V].

## NEXT
All phases complete: lines 1401..2012 written (16 phases). Body C ends at line 2012 / RVA 0x66f4f5a (last line of docs/data/listings/e4_C.txt).








