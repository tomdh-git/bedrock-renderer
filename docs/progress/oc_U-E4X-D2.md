# oc_U-E4X-D2 — Chunk extractor body D (listing lines 801..1598)

## NEXT
Scope complete: lines 801..1598 done (end of file). Source: docs/data/listings/e4_D.txt. Context: docs/functions/66ea3d0.md (body D = K==10 terrain_blend inline body, 0x66f4fcb..0x66f6e36). See ## End for where body D exits.

### lines 801..840
```
0x66f607c  shr eax,1
0x66f607e  dec eax
0x66f6080  mov [rbp+0x1140],ax
0x66f6087  mov rcx,[0x1233E1B0]
0x66f608e  mov rax,[rcx]
0x66f6091  mov rax,[rax+0x10]
0x66f6095  mov dl,0x4A
0x66f6097  call qword ptr [0xF99FFA0]
0x66f609d  nop
0x66f609e  mov [rbp+0x16B0],al
0x66f60a4  mov rdx,[r13+0x758]
0x66f60ab  cmp rdx,[r13+0x760]
0x66f60b2  je 0x66F613B
0x66f60b8  lea rcx,[rbp+0x15E8]
0x66f60bf  mov eax,[rcx+0x10]
0x66f60c2  mov [rdx+0x10],eax
0x66f60c5  movups xmm0,[rcx]
0x66f60c8  movups [rdx],xmm0
0x66f60cb  movzx eax,byte ptr [rbp+0x15FC]
0x66f60d2  mov [rdx+0x14],al
0x66f60d5  movss xmm0,[rbp+0x1600]
0x66f60dd  movss [rdx+0x18],xmm0
0x66f60e2  movss xmm0,[rbp+0x1604]
0x66f60ea  movss [rdx+0x1C],xmm0
0x66f60ef  movss xmm0,[rbp+0x1608]
0x66f60f7  movss [rdx+0x20],xmm0
0x66f60fc  movss xmm0,[rbp+0x160C]
0x66f6104  movss [rdx+0x24],xmm0
0x66f6109  lea rax,[rbp+0x1444]
0x66f6110  movups xmm0,[rax+0x1CC]
0x66f6117  movups xmm1,[rax+0x1DC]
0x66f611e  movups xmm2,[rax+0x1EB]
0x66f6125  movups [rdx+0x28],xmm0
0x66f6129  movups [rdx+0x38],xmm1
0x66f612d  movups [rdx+0x47],xmm2
0x66f6131  add qword ptr [r13+0x758],0x58
0x66f6139  jmp short 0x66F614F
0x66f613b  lea rcx,[r13+0x750]
0x66f6142  lea r8,[rbp+0x15E8]
0x66f6149  call 0x6760A80
```
Meaning: [rbp+0x1140] = (uint16)((eax >> 1) - 1) [V]. A global pointer [0x1233E1B0] is dereferenced to [rax+0x10], passed with dl=0x4A through indirect call [0xF99FFA0], and the result byte is stored at [rbp+0x16B0] [V]. Then one 0x58-byte terrain record is appended to a slot array: if [r13+0x758] == [r13+0x760] (array full), it calls 0x6760A80(&[r13+0x750], &[rbp+0x15E8]) — likely a flush/grow path [V][I]; otherwise it copies dword [rbp+0x15E8+0x10], byte [rbp+0x15FC], floats [rbp+0x1600..0x160C] into slot fields +0x10/+0x14/+0x18/+0x1C/+0x20/+0x24, then three 16-byte blocks from [rbp+0x1444+0x1CC/0x1DC/0x1EB] into +0x28/+0x38/+0x47, and advances [r13+0x758] by 0x58 [V].

### lines 841..880
```
0x66f614e  nop
0x66f614f  mov rcx,[0x1233E1B0]
0x66f6156  mov rax,[rcx]
0x66f6159  mov rax,[rax+0x10]
0x66f615d  movzx edx,byte ptr [rbp+0x16B0]
0x66f6164  call qword ptr [0xF99FFA0]
0x66f616a  nop
0x66f616b  mov eax,[r13+0x758]
0x66f6172  sub eax,[r13+0x750]
0x66f6179  shr eax,3
0x66f617c  imul eax,0xFFFF8BA3
0x66f6182  dec eax
0x66f6184  mov [rbp+0x115C],ax
0x66f618b  mov rcx,[0x1233E1B0]
0x66f6192  mov rax,[rcx]
0x66f6195  mov rax,[rax+0x10]
0x66f6199  mov dl,0x4A
0x66f619b  call qword ptr [0xF99FFA0]
0x66f61a1  nop
0x66f61a2  mov [rbp+0x16B0],al
0x66f61a8  mov rdx,[r13+0x830]
0x66f61af  cmp rdx,[r13+0x838]
0x66f61b6  je short 0x66F61C4
0x66f61b8  inc rdx
0x66f61bb  mov [r13+0x830],rdx
0x66f61c2  jmp short 0x66F61D1
0x66f61c4  lea rcx,[r13+0x828]
0x66f61cb  call 0x6760E60
0x66f61d0  nop
0x66f61d1  mov rcx,[0x1233E1B0]
0x66f61d8  mov rax,[rcx]
0x66f61db  mov rax,[rax+0x10]
0x66f61df  movzx edx,byte ptr [rbp+0x16B0]
0x66f61e6  call qword ptr [0xF99FFA0]
0x66f61ec  nop
0x66f61ed  mov qword ptr [rbp+0x1130],0x4021
0x66f61f8  mov eax,[r13+0x828]
0x66f61ff  not eax
0x66f6201  add eax,[r13+0x830]
0x66f6208  mov [rbp+0x114A],ax
```
Meaning: A second indirect call [0xF99FFA0] with dl = byte [rbp+0x16B0] on global [0x1233E1B0]->[rax+0x10] [V]. Computes [rbp+0x115C] = (uint16)(((([r13+0x758] - [r13+0x750]) >> 3) * 0xFFFF8BA3) - 1) — a magic-multiply count of 8-byte records between two array cursors [V][I]. Third call [0xF99FFA0] with dl = [rbp+0x16B0] [V]. Bounded cursor increment: if [r13+0x830] != [r13+0x838], inc [r13+0x830], else call 0x6760E60(&[r13+0x828]) — flush/grow on overflow [V][I]. Stores [rbp+0x1130] = 0x4021 [V] and [rbp+0x114A] = (uint16)(~[r13+0x828] + [r13+0x830]) [V].

### lines 881..920
```
0x66f620f  mov rcx,[0x1233E1B0]
0x66f6216  mov rax,[rcx]
0x66f6219  mov rax,[rax+0x10]
0x66f621d  mov dl,0x4A
0x66f621f  call qword ptr [0xF99FFA0]
0x66f6225  mov [rbp+0x16B0],al
0x66f622b  lea rcx,[r13+0x648]
0x66f6232  lea rdx,[rbp+0x1598]
0x66f6239  call 0x675FB30
0x66f623e  nop
0x66f623f  mov rcx,[0x1233E1B0]
0x66f6246  mov rax,[rcx]
0x66f6249  mov rax,[rax+0x10]
0x66f624d  movzx edx,byte ptr [rbp+0x16B0]
0x66f6254  call qword ptr [0xF99FFA0]
0x66f625a  nop
0x66f625b  mov eax,[r13+0x650]
0x66f6262  sub eax,[r13+0x648]
0x66f6269  shr eax,3
0x66f626c  imul eax,0xFFFF8E39
0x66f6272  dec eax
0x66f6274  mov [rbp+0x1172],ax
0x66f627b  lea rcx,[r13+0x780]
0x66f6282  lea rdx,[rbp+0x1540]
0x66f6289  call 0x675F3B0
0x66f628e  nop
0x66f628f  mov eax,[r13+0x788]
0x66f6296  sub eax,[r13+0x780]
0x66f629d  shr eax,3
0x66f62a0  imul eax,0xFFFF8BA3
0x66f62a6  dec eax
0x66f62a8  mov [rbp+0x1158],ax
0x66f62af  mov rcx,[0x1233E1B0]
0x66f62b6  mov rax,[rcx]
0x66f62b9  mov rax,[rax+0x10]
0x66f62bd  mov dl,0x4A
0x66f62bf  call qword ptr [0xF99FFA0]
0x66f62c5  mov [rbp+0x16B0],al
0x66f62cb  mov r14,[r13+0x770]
0x66f62d2  cmp r14,[r13+0x778]
```
Meaning: Indirect call [0xF99FFA0] with dl=0x4A on global [0x1233E1B0]->[rax+0x10], result -> [rbp+0x16B0] [V]. Calls 0x675FB30(&[r13+0x648], &[rbp+0x1598]) [V]; second indirect call [0xF99FFA0] with dl = [rbp+0x16B0] [V]. Computes [rbp+0x1172] = (uint16)(((([r13+0x650]-[r13+0x648])>>3)*0xFFFF8E39)-1) — record count for cursor pair 0x648/0x650 [V][I]. Calls 0x675F3B0(&[r13+0x780], &[rbp+0x1540]) [V]; computes [rbp+0x1158] = (uint16)(((([r13+0x788]-[r13+0x780])>>3)*0xFFFF8BA3)-1) [V][I]. Third indirect call [0xF99FFA0] with dl=0x4A [V]. r14 = [r13+0x770], compared against [r13+0x778] — bounded cursor check [V].

### lines 921..960
```
0x66f62d9  je short 0x66F631C
0x66f62db  mov rax,[rbp+0x14B8]
0x66f62e2  mov [r14],rax
0x66f62e5  lea rcx,[r14+8]
0x66f62e9  lea rdx,[rbp+0x14C0]
0x66f62f0  call 0xE869FF0
0x66f62f5  nop
0x66f62f6  mov rax,[rbp+0x1538]
0x66f62fd  mov [r14+0x80],rax
0x66f6304  mov qword ptr [rbp+0x1538],0
0x66f630f  add qword ptr [r13+0x770],0x88
0x66f631a  jmp short 0x66F6333
0x66f631c  lea rcx,[r13+0x768]
0x66f6323  mov rdx,r14
0x66f6326  lea r8,[rbp+0x14B8]
0x66f632d  call 0x6760710
0x66f6332  nop
0x66f6333  mov rcx,[0x1233E1B0]
0x66f633a  mov rax,[rcx]
0x66f633d  mov rax,[rax+0x10]
0x66f6341  movzx edx,byte ptr [rbp+0x16B0]
0x66f6348  call qword ptr [0xF99FFA0]
0x66f634e  nop
0x66f634f  mov qword ptr [rbp+0x1130],0x2007021
0x66f635a  mov eax,[r13+0x770]
0x66f6361  sub eax,[r13+0x768]
0x66f6368  shr eax,3
0x66f636b  imul eax,0xFFFFF0F1
0x66f6371  dec eax
0x66f6373  mov [rbp+0x115A],ax
0x66f637a  mov rcx,[0x1233E1B0]
0x66f6381  mov rax,[rcx]
0x66f6384  mov rax,[rax+0x10]
0x66f6388  mov dl,0x4A
0x66f638a  call qword ptr [0xF99FFA0]
0x66f6390  nop
0x66f6391  mov [rbp+0x16B0],al
0x66f6397  mov rdx,[r13+0x680]
0x66f639e  cmp rdx,[r13+0x688]
0x66f63a5  je short 0x66F63D7
```
Meaning: Cursor-full branch: slot at r14 = [rbp+0x14B8]; calls 0xE869FF0(&[r14+8], &[rbp+0x14C0]) [V]; [r14+0x80] = [rbp+0x1538], clears [rbp+0x1538], advances [r13+0x770] by 0x88 (0x88-byte record stride) [V]. Cursor-full path instead calls 0x6760710(&[r13+0x768], r14, &[rbp+0x14B8]) — flush/grow helper [V][I]. Indirect call [0xF99FFA0] with dl = [rbp+0x16B0] [V]. [rbp+0x1130] = 0x2007021 [V]. [rbp+0x115A] = (uint16)(((([r13+0x770]-[r13+0x768])>>3)*0xFFFFF0F1)-1) — record count for cursors 0x768/0x770 [V][I]. Fourth indirect call [0xF99FFA0] with dl=0x4A, result -> [rbp+0x16B0] [V]. rdx = [r13+0x680], compared against [r13+0x688] [V].

### lines 961..1000
```
0x66f63a7  movss xmm0,[rbp+0x14A8]
0x66f63af  movss [rdx],xmm0
0x66f63b3  movss xmm0,[rbp+0x14AC]
0x66f63bb  movss [rdx+4],xmm0
0x66f63c0  movss xmm0,[rbp+0x14B0]
0x66f63c8  movss [rdx+8],xmm0
0x66f63cd  add qword ptr [r13+0x680],0xC
0x66f63d5  jmp short 0x66F63EB
0x66f63d7  lea rcx,[r13+0x678]
0x66f63de  lea r8,[rbp+0x14A8]
0x66f63e5  call 0x1770A70
0x66f63ea  nop
0x66f63eb  mov rcx,[0x1233E1B0]
0x66f63f2  mov rax,[rcx]
0x66f63f5  mov rax,[rax+0x10]
0x66f63f9  movzx edx,byte ptr [rbp+0x16B0]
0x66f6400  call qword ptr [0xF99FFA0]
0x66f6406  nop
0x66f6407  mov eax,[r13+0x680]
0x66f640e  sub eax,[r13+0x678]
0x66f6415  shr eax,2
0x66f6418  imul eax,0xFFFFAAAB
0x66f641e  dec eax
0x66f6420  mov [rbp+0x116E],ax
0x66f6427  mov rcx,[0x1233E1B0]
0x66f642e  mov rax,[rcx]
0x66f6431  mov rax,[rax+0x10]
0x66f6435  mov dl,0x4A
0x66f6437  call qword ptr [0xF99FFA0]
0x66f643d  nop
0x66f643e  mov [rbp+0x16B0],al
0x66f6444  mov rdx,[r13+0x2D8]
0x66f644b  cmp rdx,[r13+0x2E0]
0x66f6452  je short 0x66F6460
0x66f6454  inc rdx
0x66f6457  mov [r13+0x2D8],rdx
0x66f645e  jmp short 0x66F646D
0x66f6460  lea rcx,[r13+0x2D0]
0x66f6467  call 0x6760E60
0x66f646c  nop
```
Meaning: Cursor-not-full path: writes vec3 ([rbp+0x14A8], +0x14AC, +0x14B0) to slot [rdx] and advances [r13+0x680] by 0xC (12-byte stride) [V]. Cursor-full path: calls 0x1770A70(&[r13+0x678], &[rbp+0x14A8]) — flush [V][I]. Indirect call [0xF99FFA0] with dl = [rbp+0x16B0] [V]. [rbp+0x116E] = (uint16)(((([r13+0x680]-[r13+0x678])>>2)*0xFFFFAAAB)-1) — count of 12-byte records [V][I]. Fifth indirect call [0xF99FFA0] with dl=0x4A, result -> [rbp+0x16B0] [V]. rdx = [r13+0x2D8]: if != [r13+0x2E0], inc and store [r13+0x2D8], else call 0x6760E60(&[r13+0x2D0]) — bounded increment/flush [V][I].

### lines 1001..1040
```
0x66f646d  mov rcx,[0x1233E1B0]
0x66f6474  mov rax,[rcx]
0x66f6477  mov rax,[rax+0x10]
0x66f647b  movzx edx,byte ptr [rbp+0x16B0]
0x66f6482  call qword ptr [0xF99FFA0]
0x66f6488  nop
0x66f6489  mov eax,[r13+0x2D0]
0x66f6490  not eax
0x66f6492  add eax,[r13+0x2D8]
0x66f6499  mov [rbp+0x11BC],ax
0x66f64a0  mov rcx,r13
0x66f64a3  add rcx,0x5D0
0x66f64aa  lea rdx,[rbp+0x1440]
0x66f64b1  call 0x678D690
0x66f64b6  nop
0x66f64b7  mov rax,0x4000000042807021
0x66f64c1  mov [rbp+0x1130],rax
0x66f64c8  mov eax,[r13+0x5D8]
0x66f64cf  sub eax,[r13+0x5D0]
0x66f64d6  shr eax,5
0x66f64d9  imul eax,0xFFFFAAAB
0x66f64df  dec eax
0x66f64e1  mov [rbp+0x117C],ax
0x66f64e8  mov rcx,[0x1233E1B0]
0x66f64ef  mov rax,[rcx]
0x66f64f2  mov rax,[rax+0x10]
0x66f64f6  mov dl,0x4A
0x66f64f8  call qword ptr [0xF99FFA0]
0x66f64fe  nop
0x66f64ff  mov [rbp+0x16B0],al
0x66f6505  mov rdx,[r13+8]
0x66f6509  cmp rdx,[r13+0x10]
0x66f650d  je short 0x66F652E
0x66f650f  mov r8d,0xC8
0x66f6515  mov rcx,rdx
0x66f6518  lea rdx,[rbp+0x1130]
0x66f651f  call 0xEEC6EC0
0x66f6524  add qword ptr [r13+8],0xC8
0x66f652c  jmp short 0x66F653E
0x66f652e  mov rcx,r13
```
Meaning: Indirect call [0xF99FFA0] with dl = [rbp+0x16B0] [V]. [rbp+0x11BC] = (uint16)(~[r13+0x2D0] + [r13+0x2D8]) [V]. Calls 0x678D690(r13+0x5D0, &[rbp+0x1440]) [V]. [rbp+0x1130] = 0x4000000042807021 — packed tag/flags constant [V]. [rbp+0x117C] = (uint16)(((([r13+0x5D8]-[r13+0x5D0])>>5)*0xFFFFAAAB)-1) — count of 0x20-byte records for cursors 0x5D0/0x5D8 [V][I]. Sixth indirect call [0xF99FFA0] with dl=0x4A, result -> [rbp+0x16B0] [V]. rdx = [r13+8]: if != [r13+0x10], calls 0xEEC6EC0([r13+8], &[rbp+0x1130]) with r8d=0xC8, then advances [r13+8] by 0xC8 (200-byte record stride) [V]; else falls to 0x66F652E with rcx=r13 (flush path, continues next phase) [V].

### lines 1041..1080
```
0x66f6531  lea r8,[rbp+0x1130]
0x66f6538  call 0x5ABA6D0
0x66f653d  nop
0x66f653e  mov rcx,[0x1233E1B0]
0x66f6545  mov rax,[rcx]
0x66f6548  mov rax,[rax+0x10]
0x66f654c  movzx edx,byte ptr [rbp+0x16B0]
0x66f6553  call qword ptr [0xF99FFA0]
0x66f6559  nop
0x66f655a  cmp byte ptr [rbp+0x15D8],1
0x66f6561  jne short 0x66F65B5
0x66f6563  mov rcx,[rbp+0x1598]
0x66f656a  test rcx,rcx
0x66f656d  je short 0x66F65B5
0x66f656f  mov rdx,[rbp+0x15A8]
0x66f6576  sub rdx,rcx
0x66f6579  cmp rdx,0x1000
0x66f6580  jb short 0x66F659E
0x66f6582  mov rax,[rcx-8]
0x66f6586  add rcx,0xFFFFFFFFFFFFFFF8
0x66f658a  sub rcx,rax
0x66f658d  cmp rcx,0x20
0x66f6591  jae 0x66F82BB
0x66f6597  or rdx,0x27
0x66f659b  mov rcx,rax
0x66f659e  call 0xE935700
0x66f65a3  lea rax,[rbp+0x1598]
0x66f65aa  movups [rax],xmm6
0x66f65ad  mov qword ptr [rax+0x10],0
0x66f65b5  lea rcx,[rbp+0x1440]
0x66f65bc  call 0x678E020
0x66f65c1  lea rcx,[rbp+0xF70]
0x66f65c8  call 0x67E1660
0x66f65cd  test rbx,rbx
0x66f65d0  je short 0x66F65FD
0x66f65d2  lock dec dword ptr [rbx+8]
0x66f65d6  jne short 0x66F65FD
0x66f65d8  mov rax,[rbx]
0x66f65db  mov rax,[rax]
0x66f65de  mov rcx,rbx
```
Meaning: Full-buffer flush path: call 0x5ABA6D0(r13, &[rbp+0x1130]) [V]. Indirect call [0xF99FFA0] with dl = [rbp+0x16B0] [V]. If byte [rbp+0x15D8] == 1 and [rbp+0x1598] != 0: computes free size = [rbp+0x15A8] - [rbp+0x1598]; if >= 0x1000, reads chunk header [rcx-8], computes remaining = (rcx-8) - [rax]; if remaining >= 0x20 jumps out to 0x66F82BB, else rdx |= 0x27 and rcx = rax [V]. Calls 0xE935700 — likely free/dealloc [V][I], resets [rbp+0x1598] via xmm6 store and clears [rax+0x10] [V]. Calls 0x678E020(&[rbp+0x1440]) and 0x67E1660(&[rbp+0xF70]) [V]. Refcount release on rbx: test rbx; lock dec dword [rbx+8]; if nonzero -> 0x66F65FD; if zero, rax = [rbx], rax = [rax], rcx = rbx — proceeds to destroy [V][I].

### lines 1081..1120
```
0x66f65e1  call qword ptr [0xF99FFA0]
0x66f65e7  lock dec dword ptr [rbx+0xC]
0x66f65eb  jne short 0x66F65FD
0x66f65ed  mov rax,[rbx]
0x66f65f0  mov rax,[rax+8]
0x66f65f4  mov rcx,rbx
0x66f65f7  call qword ptr [0xF99FFA0]
0x66f65fd  mov rbx,[rbp+0x13D0]
0x66f6604  test rbx,rbx
0x66f6607  je short 0x66F6634
0x66f6609  lock dec dword ptr [rbx+8]
0x66f660d  jne short 0x66F6634
0x66f660f  mov rax,[rbx]
0x66f6612  mov rax,[rax]
0x66f6615  mov rcx,rbx
0x66f6618  call qword ptr [0xF99FFA0]
0x66f661e  lock dec dword ptr [rbx+0xC]
0x66f6622  jne short 0x66F6634
0x66f6624  mov rax,[rbx]
0x66f6627  mov rax,[rax+8]
0x66f662b  mov rcx,rbx
0x66f662e  call qword ptr [0xF99FFA0]
0x66f6634  mov rbx,[rbp+0x13C0]
0x66f663b  test rbx,rbx
0x66f663e  je short 0x66F666B
0x66f6640  lock dec dword ptr [rbx+8]
0x66f6644  jne short 0x66F666B
0x66f6646  mov rax,[rbx]
0x66f6649  mov rax,[rax]
0x66f664c  mov rcx,rbx
0x66f664f  call qword ptr [0xF99FFA0]
0x66f6655  lock dec dword ptr [rbx+0xC]
0x66f6659  jne short 0x66F666B
0x66f665b  mov rax,[rbx]
0x66f665e  mov rax,[rax+8]
0x66f6662  mov rcx,rbx
0x66f6665  call qword ptr [0xF99FFA0]
0x66f666b  mov rbx,[rbp+0x1398]
0x66f6672  test rbx,rbx
0x66f6675  je short 0x66F66A2
```
Meaning: Continues the two-stage refcount release from the previous phase: call [0xF99FFA0], lock dec [rbx+0xC], if zero call [0xF99FFA0] with rax=[rax+8] (virtual destructor/dealloc pattern) [V][I]. Repeats identically for heap objects at [rbp+0x13D0] (release to 0x66F6634), [rbp+0x13C0] (release to 0x66F666B), then loads rbx = [rbp+0x1398] and begins a third release [V]. Each stage: test, lock dec [rbx+8], branch if nonzero, rax=[rbx]; rax=[rax] (vtable slot 0), call [0xF99FFA0], lock dec [rbx+0xC], branch if zero to rax=[rbx]; rax=[rax+8]; call [0xF99FFA0] [V]. Tagging of [0xF99FFA0] as destructor vs deallocator is [I].

### lines 1121..1160
```
0x66f6677  lock dec dword ptr [rbx+8]
0x66f667b  jne short 0x66F66A2
0x66f667d  mov rax,[rbx]
0x66f6680  mov rax,[rax]
0x66f6683  mov rcx,rbx
0x66f6686  call qword ptr [0xF99FFA0]
0x66f668c  lock dec dword ptr [rbx+0xC]
0x66f6690  jne short 0x66F66A2
0x66f6692  mov rax,[rbx]
0x66f6695  mov rax,[rax+8]
0x66f6699  mov rcx,rbx
0x66f669c  call qword ptr [0xF99FFA0]
0x66f66a2  mov rbx,[rbp+0x1330]
0x66f66a9  test rbx,rbx
0x66f66ac  je short 0x66F66D9
0x66f66ae  lock dec dword ptr [rbx+8]
0x66f66b2  jne short 0x66F66D9
0x66f66b4  mov rax,[rbx]
0x66f66b7  mov rax,[rax]
0x66f66ba  mov rcx,rbx
0x66f66bd  call qword ptr [0xF99FFA0]
0x66f66c3  lock dec dword ptr [rbx+0xC]
0x66f66c7  jne short 0x66F66D9
0x66f66c9  mov rax,[rbx]
0x66f66cc  mov rax,[rax+8]
0x66f66d0  mov rcx,rbx
0x66f66d3  call qword ptr [0xF99FFA0]
0x66f66d9  mov rbx,[rbp+0x1320]
0x66f66e0  test rbx,rbx
0x66f66e3  je short 0x66F6710
0x66f66e5  lock dec dword ptr [rbx+8]
0x66f66e9  jne short 0x66F6710
0x66f66eb  mov rax,[rbx]
0x66f66ee  mov rax,[rax]
0x66f66f1  mov rcx,rbx
0x66f66f4  call qword ptr [0xF99FFA0]
0x66f66fa  lock dec dword ptr [rbx+0xC]
0x66f66fe  jne short 0x66F6710
0x66f6700  mov rax,[rbx]
0x66f6703  mov rax,[rax+8]
```
Meaning: Completes the release for rbx=[rbp+0x1398] (jump target 0x66F66A2) [V]. Repeats the same two-stage refcount release (lock dec [rbx+8]; call [0xF99FFA0] on vtable slot 0; lock dec [rbx+0xC]; call [0xF99FFA0] on [rax+8]) for heap objects at [rbp+0x1330] (skip target 0x66F66D9) and [rbp+0x1320] (skip target 0x66F6710), ending mid-release at mov rax,[rax+8] [V]. Tagging of the two [0xF99FFA0] calls as destructor/deallocator is [I].

### lines 1161..1200
```
0x66f6707  mov rcx,rbx
0x66f670a  call qword ptr [0xF99FFA0]
0x66f6710  mov rbx,[rbp+0x1310]
0x66f6717  test rbx,rbx
0x66f671a  je short 0x66F6747
0x66f671c  lock dec dword ptr [rbx+8]
0x66f6720  jne short 0x66F6747
0x66f6722  mov rax,[rbx]
0x66f6725  mov rax,[rax]
0x66f6728  mov rcx,rbx
0x66f672b  call qword ptr [0xF99FFA0]
0x66f6731  lock dec dword ptr [rbx+0xC]
0x66f6735  jne short 0x66F6747
0x66f6737  mov rax,[rbx]
0x66f673a  mov rax,[rax+8]
0x66f673e  mov rcx,rbx
0x66f6741  call qword ptr [0xF99FFA0]
0x66f6747  mov rbx,[rbp+0x12E8]
0x66f674e  test rbx,rbx
0x66f6751  je short 0x66F677E
0x66f6753  lock dec dword ptr [rbx+8]
0x66f6757  jne short 0x66F677E
0x66f6759  mov rax,[rbx]
0x66f675c  mov rax,[rax]
0x66f675f  mov rcx,rbx
0x66f6762  call qword ptr [0xF99FFA0]
0x66f6768  lock dec dword ptr [rbx+0xC]
0x66f676c  jne short 0x66F677E
0x66f676e  mov rax,[rbx]
0x66f6771  mov rax,[rax+8]
0x66f6775  mov rcx,rbx
0x66f6778  call qword ptr [0xF99FFA0]
0x66f677e  mov rbx,[rbp+0x1668]
0x66f6785  test rbx,rbx
0x66f6788  je short 0x66F67B5
0x66f678a  lock dec dword ptr [rbx+8]
0x66f678e  jne short 0x66F67B5
0x66f6790  mov rax,[rbx]
0x66f6793  mov rax,[rax]
0x66f6796  mov rcx,rbx
```
Meaning: Finishes the [rbp+0x1320] release (call [0xF99FFA0] at 0x66F670A) [V]. Repeats the same two-stage refcount release for heap objects at [rbp+0x1310] (skip 0x66F6747), [rbp+0x12E8] (skip 0x66F677E), and starts the release for [rbp+0x1668] (skip 0x66F67B5), ending at mov rax,[rax] (vtable slot 0 load) [V]. Every stage follows: test rbx; lock dec [rbx+8]; jne skip; rax=[rbx]; rax=[rax] / [rax+8]; call [0xF99FFA0]; lock dec [rbx+0xC]; jne skip; second call variant [V]. Destructor/deallocator split of [0xF99FFA0] remains [I].

### lines 1201..1240
```
0x66f6799  call qword ptr [0xF99FFA0]
0x66f679f  lock dec dword ptr [rbx+0xC]
0x66f67a3  jne short 0x66F67B5
0x66f67a5  mov rax,[rbx]
0x66f67a8  mov rax,[rax+8]
0x66f67ac  mov rcx,rbx
0x66f67af  call qword ptr [0xF99FFA0]
0x66f67b5  mov rbx,[rbp+0x1378]
0x66f67bc  test rbx,rbx
0x66f67bf  jne 0x66F6C95
0x66f67c5  jmp 0x66F6CC0
0x66f67ca  xor eax,eax
0x66f67cc  mov rcx,[r14+0x20]
0x66f67d0  mov [rbp+0x1370],rcx
0x66f67d7  mov [rbp+0x1378],rax
0x66f67de  lea rax,[rbp+0x12E0]
0x66f67e5  mov [rsp+0x38],rax
0x66f67ea  lea rax,[rbp+0x1370]
0x66f67f1  mov [rsp+0x30],rax
0x66f67f6  mov eax,[rbp+0x16D0]
0x66f67fc  mov [rsp+0x28],ax
0x66f6801  mov [rsp+0x20],r14
0x66f6806  mov dword ptr [rsp+0x48],0xFFFFFF00
0x66f680e  mov dword ptr [rsp+0x40],0xFFFFFF00
0x66f6816  lea rcx,[rbp+0x1390]
0x66f681d  lea rdx,[rbp+0x1420]
0x66f6824  movzx r8d,byte ptr [rbp+0x16D4]
0x66f682c  mov r9,0xFFFFFFFFFFFFFFFF
0x66f6833  call 0x673CC80
0x66f6838  movaps [rbp+0x1130],xmm6
0x66f683f  mov rax,[rbp+0x1398]
0x66f6846  test rax,rax
0x66f6849  je short 0x66F6858
0x66f684b  lock inc dword ptr [rax+8]
0x66f684f  mov rax,[rbp+0x1398]
0x66f6856  jmp short 0x66F685A
0x66f6858  xor eax,eax
0x66f685a  mov rcx,[rbp+0x1390]
0x66f6861  mov [rbp+0x1130],rcx
0x66f6868  mov [rbp+0x1138],rax
```
Meaning: Finishes the [rbp+0x1668] release [V]. rbx = [rbp+0x1378]: if nonzero jumps out to 0x66F6C95, else jmp 0x66F6CC0 — both out-of-line exit/epilogue targets [V]. At fall-through 0x66F67CA: builds an arg block on the stack ([rsp+0x38]=&[rbp+0x12E0], [rsp+0x30]=&[rbp+0x1370], [rsp+0x28]=(u16)[rbp+0x16D0], [rsp+0x20]=r14, [rsp+0x48]=[rsp+0x40]=0xFFFFFF00), then calls 0x673CC80(rcx=&[rbp+0x1390], rdx=&[rbp+0x1420], r8d=(u8)[rbp+0x16D4] variant index classified in D1 [V], r9=-1) [V]. Zeroes [rbp+0x1130] via xmm6 [V]. Refcount: if [rbp+0x1398] != 0, lock inc [rax+8] [V]. Finally [rbp+0x1130] = [rbp+0x1390], [rbp+0x1138] = (result rax) [V].

### lines 1241..1280
```
0x66f686f  lea rcx,[rbp+0x13A0]
0x66f6876  movzx eax,word ptr [rcx+0x10]
0x66f687a  mov [r15+0x10],ax
0x66f687f  movups xmm0,[rcx]
0x66f6882  movups [r15],xmm0
0x66f6886  movups [r15+0x18],xmm6
0x66f688b  mov rax,[rbp+0x13C0]
0x66f6892  test rax,rax
0x66f6895  je short 0x66F68A4
0x66f6897  lock inc dword ptr [rax+8]
0x66f689b  mov rax,[rbp+0x13C0]
0x66f68a2  jmp short 0x66F68A6
0x66f68a4  xor eax,eax
0x66f68a6  mov rcx,[rbp+0x13B8]
0x66f68ad  mov [rbp+0x1158],rcx
0x66f68b4  mov [rbp+0x1160],rax
0x66f68bb  movups [r15+0x28],xmm6
0x66f68c0  mov rax,[rbp+0x13D0]
0x66f68c7  test rax,rax
0x66f68ca  je short 0x66F68D9
0x66f68cc  lock inc dword ptr [rax+8]
0x66f68d0  mov rax,[rbp+0x13D0]
0x66f68d7  jmp short 0x66F68DB
0x66f68d9  xor eax,eax
0x66f68db  mov rcx,[rbp+0x13C8]
0x66f68e2  mov [rbp+0x1168],rcx
0x66f68e9  mov [rbp+0x1170],rax
0x66f68f0  movups [r15+0x38],xmm6
0x66f68f5  mov rax,[rbp+0x13E0]
0x66f68fc  test rax,rax
0x66f68ff  je short 0x66F690E
0x66f6901  lock inc dword ptr [rax+8]
0x66f6905  mov rbx,[rbp+0x13E0]
0x66f690c  jmp short 0x66F6910
0x66f690e  xor ebx,ebx
0x66f6910  mov rax,[rbp+0x13D8]
0x66f6917  mov rcx,[rbp+0x13E8]
0x66f691e  mov [rbp+0x1178],rax
0x66f6925  mov [rbp+0x1180],rbx
0x66f692c  mov [rbp+0x1188],rcx
```
Meaning: Output record fill at r15: [r15+0x10] = (u16)[rbp+0x13A0+0x10]; [r15..+0x0F] = [rbp+0x13A0..0x13AF]; [r15+0x18] = 0 [V]. Refcount-inc pattern for object [rbp+0x13C0] (lock inc [rax+8] if nonzero) [V]. [rbp+0x1158] = [rbp+0x13B8]; [rbp+0x1160] = object-or-null; [r15+0x28] = 0 [V]. Same pattern for [rbp+0x13D0] into [rbp+0x1170] with [rbp+0x13C8] -> [rbp+0x1168]; [r15+0x38] = 0 [V]. Same pattern for [rbp+0x13E0] into rbx [V]. Finally [rbp+0x1178] = [rbp+0x13D8]; [rbp+0x1180] = rbx; [rbp+0x1188] = [rbp+0x13E8] [V] — ends mid-store at 0x66F692C.

### lines 1281..1320
```
0x66f6933  lea rcx,[rbp+0xEA8]
0x66f693a  lea r13,[rbp+0xF70]
0x66f6941  mov rdx,r13
0x66f6944  call 0x67A75D0
0x66f6949  nop
0x66f694a  lea rax,[rbp+0x1130]
0x66f6951  mov [rsp+0x20],rax
0x66f6956  lea r14,[rbp+0x1440]
0x66f695d  mov rcx,r14
0x66f6960  mov rdx,r12
0x66f6963  lea r8,[rbp+0xFF8]
0x66f696a  mov r9,r13
0x66f696d  call 0x678EF40
0x66f6972  nop
0x66f6973  mov eax,[r12+0x60]
0x66f6978  lea r8,[rbp+0x15D8]
0x66f697f  mov [r8+0x10],eax
0x66f6983  movups xmm0,[r12+0x50]
0x66f6989  movups [r8],xmm0
0x66f698d  movzx eax,byte ptr [rbp+0x10B4]
0x66f6994  mov [rbp+0x15EC],al
0x66f699a  movups xmm0,[rbp+0x10B8]
0x66f69a1  movups [rbp+0x15F0],xmm0
0x66f69a8  movups xmm0,[r12+0x78]
0x66f69ae  movups xmm1,[r12+0x88]
0x66f69b7  movups xmm2,[r12+0x97]
0x66f69c0  lea rax,[rbp+0x1444]
0x66f69c7  movups [rax+0x1DB],xmm2
0x66f69ce  movups [rax+0x1CC],xmm1
0x66f69d5  movups [rax+0x1BC],xmm0
0x66f69dc  movzx eax,word ptr [rbp+0x10F8]
0x66f69e3  mov [rbp+0x1630],ax
0x66f69ea  mov rax,[rbp+0x16A8]
0x66f69f1  mov rcx,[rax+0x10]
0x66f69f5  mov eax,0x9D0
0x66f69fa  add rcx,rax
0x66f69fd  mov [rsp+0x30],r14
0x66f6a02  lea rax,[rbp+0x14A8]
0x66f6a09  mov [rsp+0x28],rax
0x66f6a0e  lea rax,[rbp+0x1530]
```
Meaning: Calls 0x67A75D0(rcx=&[rbp+0xEA8], rdx=&[rbp+0xF70]) [V]. Call 0x678EF40(rcx=&[rbp+0x1440], rdx=r12, r8=&[rbp+0xFF8], r9=&[rbp+0xF70], stack arg &[rbp+0x1130]) [V]. Copies [r12+0x60] -> [rbp+0x15D8+0x10], [r12+0x50..] -> [rbp+0x15D8..] (movups) [V]. [rbp+0x15EC] = byte [rbp+0x10B4]; [rbp+0x15F0..] = [rbp+0x10B8..] (movups) [V]. Writes [r12+0x97]/+0x88/+0x78 into [rbp+0x1444+0x1DB/+0x1CC/+0x1BC] respectively — note inverted ordering vs the read path at lines 801-840 [V]. [rbp+0x1630] = (u16)[rbp+0x10F8] [V]. Builds arg block: rax=[rbp+0x16A8]; rcx=[rax+0x10]+0x9D0; [rsp+0x30]=&[rbp+0x1440]; [rsp+0x28]=&[rbp+0x14A8]; starts [rsp+0x20]=&[rbp+0x1530] (cut off at end of phase) [V].

### lines 1321..1360
```
0x66f6a15  mov [rsp+0x20],rax
0x66f6a1a  lea rdx,[rbp+0x1630]
0x66f6a21  lea r9,[rbp+0x1588]
0x66f6a28  call 0x67B2A60
0x66f6a2d  nop
0x66f6a2e  cmp byte ptr [rbp+0x15C8],1
0x66f6a35  jne short 0x66F6A89
0x66f6a37  mov rcx,[rbp+0x1588]
0x66f6a3e  test rcx,rcx
0x66f6a41  je short 0x66F6A89
0x66f6a43  mov rdx,[rbp+0x1598]
0x66f6a4a  sub rdx,rcx
0x66f6a4d  cmp rdx,0x1000
0x66f6a54  jb short 0x66F6A72
0x66f6a56  mov rax,[rcx-8]
0x66f6a5a  add rcx,0xFFFFFFFFFFFFFFF8
0x66f6a5e  sub rcx,rax
0x66f6a61  cmp rcx,0x20
0x66f6a65  jae 0x66F82BB
0x66f6a6b  or rdx,0x27
0x66f6a6f  mov rcx,rax
0x66f6a72  call 0xE935700
0x66f6a77  lea rax,[rbp+0x1588]
0x66f6a7e  movups [rax],xmm6
0x66f6a81  mov qword ptr [rax+0x10],0
0x66f6a89  lea rcx,[rbp+0x1440]
0x66f6a90  call 0x678F260
0x66f6a95  lea rcx,[rbp+0xF70]
0x66f6a9c  call 0x67E23F0
0x66f6aa1  test rbx,rbx
0x66f6aa4  je short 0x66F6AD1
0x66f6aa6  lock dec dword ptr [rbx+8]
0x66f6aaa  jne short 0x66F6AD1
0x66f6aac  mov rax,[rbx]
0x66f6aaf  mov rax,[rax]
0x66f6ab2  mov rcx,rbx
0x66f6ab5  call qword ptr [0xF99FFA0]
0x66f6abb  lock dec dword ptr [rbx+0xC]
0x66f6abf  jne short 0x66F6AD1
0x66f6ac1  mov rax,[rbx]
```
Meaning: Finishes arg block ([rsp+0x20]=rax from lea [rbp+0x1530]) and calls 0x67B2A60(rdx=&[rbp+0x1630], r9=&[rbp+0x1588]) [V]. If byte [rbp+0x15C8]==1 and [rbp+0x1588]!=0: free size = [rbp+0x1598]-[rbp+0x1588]; if >= 0x1000, reads chunk header [rcx-8], remaining=(rcx-8)-[rax]; if remaining>=0x20 jumps out to 0x66F82BB, else rdx|=0x27, rcx=rax [V]. Calls 0xE935700 — free/dealloc [V][I], then resets [rbp+0x1588] via xmm6 store and clears +0x10 [V]. Calls 0x678F260(&[rbp+0x1440]) and 0x67E23F0(&[rbp+0xF70]) [V]. Begins the same two-stage refcount release on rbx (test; lock dec [rbx+8]; call [0xF99FFA0] on vtable slot 0; lock dec [rbx+0xC]; ...), ending mid at mov rax,[rbx] [V].

### lines 1361..1400
```
0x66f6ac4  mov rax,[rax+8]
0x66f6ac8  mov rcx,rbx
0x66f6acb  call qword ptr [0xF99FFA0]
0x66f6ad1  mov rbx,[rbp+0x1170]
0x66f6ad8  test rbx,rbx
0x66f6adb  je short 0x66F6B08
0x66f6add  lock dec dword ptr [rbx+8]
0x66f6ae1  jne short 0x66F6B08
0x66f6ae3  mov rax,[rbx]
0x66f6ae6  mov rax,[rax]
0x66f6ae9  mov rcx,rbx
0x66f6aec  call qword ptr [0xF99FFA0]
0x66f6af2  lock dec dword ptr [rbx+0xC]
0x66f6af6  jne short 0x66F6B08
0x66f6af8  mov rax,[rbx]
0x66f6afb  mov rax,[rax+8]
0x66f6aff  mov rcx,rbx
0x66f6b02  call qword ptr [0xF99FFA0]
0x66f6b08  mov rbx,[rbp+0x1160]
0x66f6b0f  test rbx,rbx
0x66f6b12  je short 0x66F6B3F
0x66f6b14  lock dec dword ptr [rbx+8]
0x66f6b18  jne short 0x66F6B3F
0x66f6b1a  mov rax,[rbx]
0x66f6b1d  mov rax,[rax]
0x66f6b20  mov rcx,rbx
0x66f6b23  call qword ptr [0xF99FFA0]
0x66f6b29  lock dec dword ptr [rbx+0xC]
0x66f6b2d  jne short 0x66F6B3F
0x66f6b2f  mov rax,[rbx]
0x66f6b32  mov rax,[rax+8]
0x66f6b36  mov rcx,rbx
0x66f6b39  call qword ptr [0xF99FFA0]
0x66f6b3f  mov rbx,[rbp+0x1138]
0x66f6b46  test rbx,rbx
0x66f6b49  je short 0x66F6B76
0x66f6b4b  lock dec dword ptr [rbx+8]
0x66f6b4f  jne short 0x66F6B76
0x66f6b51  mov rax,[rbx]
0x66f6b54  mov rax,[rax]
```
Meaning: Finishes the rbx release started at lines 1321-1360 (call [0xF99FFA0] on [rax+8]) [V]. Repeats the same two-stage refcount release for heap objects [rbp+0x1170] (skip 0x66F6B08), [rbp+0x1160] (skip 0x66F6B3F), [rbp+0x1138] (skip 0x66F6B76), ending mid at mov rax,[rax] [V]. Each stage: test rbx; lock dec [rbx+8]; jne skip; rax=[rbx]; rax=[rax]; call [0xF99FFA0]; lock dec [rbx+0xC]; jne skip; rax=[rbx]; rax=[rax+8]; call [0xF99FFA0] [V]. Destructor/deallocator split of [0xF99FFA0] remains [I].

### lines 1401..1440
```
0x66f6b57  mov rcx,rbx
0x66f6b5a  call qword ptr [0xF99FFA0]
0x66f6b60  lock dec dword ptr [rbx+0xC]
0x66f6b64  jne short 0x66F6B76
0x66f6b66  mov rax,[rbx]
0x66f6b69  mov rax,[rax+8]
0x66f6b6d  mov rcx,rbx
0x66f6b70  call qword ptr [0xF99FFA0]
0x66f6b76  mov rbx,[rbp+0x13E0]
0x66f6b7d  test rbx,rbx
0x66f6b80  je short 0x66F6BAD
0x66f6b82  lock dec dword ptr [rbx+8]
0x66f6b86  jne short 0x66F6BAD
0x66f6b88  mov rax,[rbx]
0x66f6b8b  mov rax,[rax]
0x66f6b8e  mov rcx,rbx
0x66f6b91  call qword ptr [0xF99FFA0]
0x66f6b97  lock dec dword ptr [rbx+0xC]
0x66f6b9b  jne short 0x66F6BAD
0x66f6b9d  mov rax,[rbx]
0x66f6ba0  mov rax,[rax+8]
0x66f6ba4  mov rcx,rbx
0x66f6ba7  call qword ptr [0xF99FFA0]
0x66f6bad  mov rbx,[rbp+0x13D0]
0x66f6bb4  test rbx,rbx
0x66f6bb7  je short 0x66F6BE4
0x66f6bb9  lock dec dword ptr [rbx+8]
0x66f6bbd  jne short 0x66F6BE4
0x66f6bbf  mov rax,[rbx]
0x66f6bc2  mov rax,[rax]
0x66f6bc5  mov rcx,rbx
0x66f6bc8  call qword ptr [0xF99FFA0]
0x66f6bce  lock dec dword ptr [rbx+0xC]
0x66f6bd2  jne short 0x66F6BE4
0x66f6bd4  mov rax,[rbx]
0x66f6bd7  mov rax,[rax+8]
0x66f6bdb  mov rcx,rbx
0x66f6bde  call qword ptr [0xF99FFA0]
0x66f6be4  mov rbx,[rbp+0x13C0]
0x66f6beb  test rbx,rbx
```
Meaning: Finishes the [rbp+0x1138] release (second [0xF99FFA0] call at 0x66F6B70) [V]. Repeats the same two-stage refcount release for heap objects [rbp+0x13E0] (skip 0x66F6BAD), [rbp+0x13D0] (skip 0x66F6BE4), and starts [rbp+0x13C0] (test rbx,rbx at 0x66F6BEB) [V]. Same pattern each stage: test; lock dec [rbx+8]; jne skip; rax=[rbx]; rax=[rax] (vtable slot 0); call [0xF99FFA0]; lock dec [rbx+0xC]; jne skip; rax=[rbx]; rax=[rax+8]; call [0xF99FFA0] [V]. Destructor/deallocator split remains [I].

### lines 1441..1480
```
0x66f6bee  je short 0x66F6C1B
0x66f6bf0  lock dec dword ptr [rbx+8]
0x66f6bf4  jne short 0x66F6C1B
0x66f6bf6  mov rax,[rbx]
0x66f6bf9  mov rax,[rax]
0x66f6bfc  mov rcx,rbx
0x66f6bff  call qword ptr [0xF99FFA0]
0x66f6c05  lock dec dword ptr [rbx+0xC]
0x66f6c09  jne short 0x66F6C1B
0x66f6c0b  mov rax,[rbx]
0x66f6c0e  mov rax,[rax+8]
0x66f6c12  mov rcx,rbx
0x66f6c15  call qword ptr [0xF99FFA0]
0x66f6c1b  mov rbx,[rbp+0x1398]
0x66f6c22  test rbx,rbx
0x66f6c25  je short 0x66F6C52
0x66f6c27  lock dec dword ptr [rbx+8]
0x66f6c2b  jne short 0x66F6C52
0x66f6c2d  mov rax,[rbx]
0x66f6c30  mov rax,[rax]
0x66f6c33  mov rcx,rbx
0x66f6c36  call qword ptr [0xF99FFA0]
0x66f6c3c  lock dec dword ptr [rbx+0xC]
0x66f6c40  jne short 0x66F6C52
0x66f6c42  mov rax,[rbx]
0x66f6c45  mov rax,[rax+8]
0x66f6c49  mov rcx,rbx
0x66f6c4c  call qword ptr [0xF99FFA0]
0x66f6c52  mov rbx,[rbp+0x1378]
0x66f6c59  test rbx,rbx
0x66f6c5c  je short 0x66F6C89
0x66f6c5e  lock dec dword ptr [rbx+8]
0x66f6c62  jne short 0x66F6C89
0x66f6c64  mov rax,[rbx]
0x66f6c67  mov rax,[rax]
0x66f6c6a  mov rcx,rbx
0x66f6c6d  call qword ptr [0xF99FFA0]
0x66f6c73  lock dec dword ptr [rbx+0xC]
0x66f6c77  jne short 0x66F6C89
0x66f6c79  mov rax,[rbx]
```
Meaning: Finishes the [rbp+0x13C0] release (second call at 0x66F6C15) [V]. Repeats the same two-stage refcount release for heap objects [rbp+0x1398] (skip 0x66F6C52) and [rbp+0x1378] (skip 0x66F6C89), ending mid at mov rax,[rax] [V]. Same pattern each stage: test; lock dec [rbx+8]; jne skip; rax=[rbx]; rax=[rax] (vtable slot 0); call [0xF99FFA0]; lock dec [rbx+0xC]; jne skip; rax=[rbx]; rax=[rax+8]; call [0xF99FFA0] [V]. Destructor/deallocator split remains [I].

### lines 1481..1520
```
0x66f6c7c  mov rax,[rax+8]
0x66f6c80  mov rcx,rbx
0x66f6c83  call qword ptr [0xF99FFA0]
0x66f6c89  mov rbx,[rbp+0x12E8]
0x66f6c90  test rbx,rbx
0x66f6c93  je short 0x66F6CC0
0x66f6c95  lock dec dword ptr [rbx+8]
0x66f6c99  jne short 0x66F6CC0
0x66f6c9b  mov rax,[rbx]
0x66f6c9e  mov rax,[rax]
0x66f6ca1  mov rcx,rbx
0x66f6ca4  call qword ptr [0xF99FFA0]
0x66f6caa  lock dec dword ptr [rbx+0xC]
0x66f6cae  jne short 0x66F6CC0
0x66f6cb0  mov rax,[rbx]
0x66f6cb3  mov rax,[rax+8]
0x66f6cb7  mov rcx,rbx
0x66f6cba  call qword ptr [0xF99FFA0]
0x66f6cc0  mov rbx,[rbp+0x1428]
0x66f6cc7  test rbx,rbx
0x66f6cca  je short 0x66F6CF7
0x66f6ccc  lock dec dword ptr [rbx+8]
0x66f6cd0  jne short 0x66F6CF7
0x66f6cd2  mov rax,[rbx]
0x66f6cd5  mov rax,[rax]
0x66f6cd8  mov rcx,rbx
0x66f6cdb  call qword ptr [0xF99FFA0]
0x66f6ce1  lock dec dword ptr [rbx+0xC]
0x66f6ce5  jne short 0x66F6CF7
0x66f6ce7  mov rax,[rbx]
0x66f6cea  mov rax,[rax+8]
0x66f6cee  mov rcx,rbx
0x66f6cf1  call qword ptr [0xF99FFA0]
0x66f6cf7  cmp byte ptr [rbp+0xDF0],3
0x66f6cfe  jne short 0x66F6D37
0x66f6d00  mov rbx,[rbp+0xDE8]
0x66f6d07  test rbx,rbx
0x66f6d0a  je short 0x66F6D37
0x66f6d0c  lock dec dword ptr [rbx+8]
0x66f6d10  jne short 0x66F6D37
```
Meaning: Finishes the [rbp+0x1378] release (second call at 0x66F6C83) [V]. Release for [rbp+0x12E8] jumps to 0x66F6CC0 on zero/nonzero — the same 0x66F6CC0 epilogue target referenced at line 1228 [V]. Release for [rbp+0x1428] (skip 0x66F6CF7) [V]. Then: if byte [rbp+0xDF0] == 3 and [rbp+0xDE8] != 0, begins the same two-stage refcount release on [rbp+0xDE8] (lock dec [rbx+8] ...), ending mid-phase [V]. Same release pattern as before; destructor/deallocator split of [0xF99FFA0] remains [I].

### lines 1521..1560
```
0x66f6d12  mov rax,[rbx]
0x66f6d15  mov rax,[rax]
0x66f6d18  mov rcx,rbx
0x66f6d1b  call qword ptr [0xF99FFA0]
0x66f6d21  lock dec dword ptr [rbx+0xC]
0x66f6d25  jne short 0x66F6D37
0x66f6d27  mov rax,[rbx]
0x66f6d2a  mov rax,[rax+8]
0x66f6d2e  mov rcx,rbx
0x66f6d31  call qword ptr [0xF99FFA0]
0x66f6d37  mov r14,[rbp+0xDC0]
0x66f6d3e  test r14,r14
0x66f6d41  je 0x66F5358
0x66f6d47  mov r13,[rbp+0xDC8]
0x66f6d4e  jmp short 0x66F6D54
0x66f6d50  add r14,0x28
0x66f6d54  cmp r14,r13
0x66f6d57  je 0x66F5358
0x66f6d5d  cmp byte ptr [r14+0x18],2
0x66f6d62  jne short 0x66F6D50
0x66f6d64  mov rbx,[r14+8]
0x66f6d68  test rbx,rbx
0x66f6d6b  je short 0x66F6D50
0x66f6d6d  lock dec dword ptr [rbx+8]
0x66f6d71  jne short 0x66F6D50
0x66f6d73  mov rax,[rbx]
0x66f6d76  mov rax,[rax]
0x66f6d79  mov rcx,rbx
0x66f6d7c  call qword ptr [0xF99FFA0]
0x66f6d82  lock dec dword ptr [rbx+0xC]
0x66f6d86  jne short 0x66F6D50
0x66f6d88  mov rax,[rbx]
0x66f6d8b  mov rax,[rax+8]
0x66f6d8f  mov rcx,rbx
0x66f6d92  call qword ptr [0xF99FFA0]
0x66f6d98  jmp short 0x66F6D50
0x66f6d9a  mov rsi,[rbp+0x1670]
0x66f6da1  test rsi,rsi
0x66f6da4  je 0x66F6E3B
0x66f6daa  mov rbx,[rbp+0x1678]
```
Meaning: Finishes the [rbp+0xDE8] release [V]. Then r14=[rbp+0xDC0]; if zero, jumps to 0x66F5358 (inside body D range, 0x66f4fcb..0x66f6e36 [V]); r13=[rbp+0xDC8]; loop over entries stride 0x28 from [rbp+0xDC0] to [rbp+0xDC8]: if byte [r14+0x18]==2, two-stage refcount release on object [r14+8] (same destructor/deallocator pattern) [V][I]. Loop exits to 0x66F5358 when r14==r13 [V]. Finally rsi=[rbp+0x1670]; if zero jumps to 0x66F6E3B (just past body D end 0x66f6e36 [V]); rbx=[rbp+0x1678] — continues next phase [V].

### lines 1561..1598
```
0x66f6db1  cmp rsi,rbx
0x66f6db4  jne short 0x66F6DC1
0x66f6db6  jmp short 0x66F6E04
0x66f6db8  add rsi,0x18
0x66f6dbc  cmp rsi,rbx
0x66f6dbf  je short 0x66F6DFD
0x66f6dc1  cmp byte ptr [rsi+0x10],1
0x66f6dc5  jne short 0x66F6DB8
0x66f6dc7  mov rdi,[rsi+8]
0x66f6dcb  test rdi,rdi
0x66f6dce  je short 0x66F6DB8
0x66f6dd0  lock dec dword ptr [rdi+8]
0x66f6dd4  jne short 0x66F6DB8
0x66f6dd6  mov rax,[rdi]
0x66f6dd9  mov rax,[rax]
0x66f6ddc  mov rcx,rdi
0x66f6ddf  call qword ptr [0xF99FFA0]
0x66f6de5  lock dec dword ptr [rdi+0xC]
0x66f6de9  jne short 0x66F6DB8
0x66f6deb  mov rax,[rdi]
0x66f6dee  mov rax,[rax+8]
0x66f6df2  mov rcx,rdi
0x66f6df5  call qword ptr [0xF99FFA0]
0x66f6dfb  jmp short 0x66F6DB8
0x66f6dfd  mov rsi,[rbp+0x1670]
0x66f6e04  mov rdx,[rbp+0x1680]
0x66f6e0b  sub rdx,rsi
0x66f6e0e  cmp rdx,0x1000
0x66f6e15  jb short 0x66F6E33
0x66f6e17  mov rax,[rsi-8]
0x66f6e1b  add rsi,0xFFFFFFFFFFFFFFF8
0x66f6e1f  sub rsi,rax
0x66f6e22  cmp rsi,0x20
0x66f6e26  jae 0x66F82BB
0x66f6e2c  add rdx,0x27
0x66f6e30  mov rsi,rax
0x66f6e33  mov rcx,rsi
0x66f6e36  call 0xE935700
```
Meaning: Loop over stride-0x18 list [rbp+0x1670]..[rbp+0x1678] (rbx=[rbp+0x1678]): if byte [rsi+0x10]==1, two-stage refcount release on object [rsi+8] (same destructor/deallocator pattern) [V][I]. Loop exits at rsi==rbx -> 0x66F6E04 [V]. Final buffer free: rdx = [rbp+0x1680] - [rbp+0x1670]; if >= 0x1000, rax=[rsi-8], remaining=(rsi-8)-rax; if remaining >= 0x20 jump out to 0x66F82BB, else rdx+=0x27, rsi=rax; then rcx=rsi; call 0xE935700 — free/dealloc [V][I]. File ends at line 1598 with that call.

## End
Body D ends at line 1598 (0x66f6e36 `call 0xE935700`) — matching the D1-specified body D span 0x66f4fcb..0x66f6e36 [V]. Out-of-line exit/epilogue targets jumped to from body D: 0x66F82BB (oversized-free path, remaining >= 0x20) [V]; 0x66F5358 (cursor-range loop exit, [rbp+0xDC0]==0 or r14==[rbp+0xDC8]) [V]; 0x66F6E3B ([rbp+0x1670]==0) [V]; 0x66F6C95 / 0x66F6CC0 ([rbp+0x1378] nonzero / [rbp+0x12E8] release done) [V]. Scope complete: all listing lines 801..1598 covered verbatim.

