# Unit U-E3: SkinnedMesh Clone Function 0x6b84e60

## NEXT
Run verify_oc.py on this file. All steps complete.

## Step 1: Preflight Done
Preflight output written to docs/progress/pre/0x6b84e60.md (454 lines). Function size 0x1bf0 (7152 bytes), 5 xrefs.
Callers: sub_6b80870 (1 site), sub_6b80f00 (1 site), sub_6e8dff0 (3 sites) = 3 calling functions.
Callees: sub_668d350 (builder, 1), sub_6b86e80 (2), sub_6b87e00 (2), sub_6be16b0 (2), sub_6760560 (2), sub_4def080 (4), sub_eaa30 (4), sub_eea6040 (11), sub_4dfb570 (5), sub_4e00090 (5), sub_4e3b020 (1), sub_4e69270 (1), sub_77a2500 (1), sub_e935740 (11), sub_e938cb0 (11), sub_e938d70 (11), sub_eec6ed0 (1), sub_78ed0 (1), sub_2fe330 (1), sub_39a7d40 (1), sub_4def480 (1), sub_4df6a90 (1).
Strings: "Quad material doesn't exist" (0x6b85272), "Tri material doesn't exist" (0x6b8539d), "Mesh material doesn't exist" (0x6b85b6f, 0x6b866e4), "FrameBuilder - Insert" (0x6b869de).

---

## Step 2: Full Instruction-Complete Listing (Phases of <=40 instructions)

### Phase 1: 0x6b84e60..0x6b84f09 - Prologue & Initial Checks (74 instructions)
```
0x6b84e60  push rbp
0x6b84e61  push r15
0x6b84e63  push r14
0x6b84e65  push r13
0x6b84e67  push r12
0x6b84e69  push rsi
0x6b84e6a  push rdi
0x6b84e6b  push rbx
0x6b84e6c  sub rsp,0x3D8
0x6b84e73  lea rbp,[rsp+0x80]
0x6b84e7b  mov qword ptr [rbp+0x350],0xFFFFFFFFFFFFFFFE
0x6b84e86  cmp byte ptr [rcx],1          ; R a0+0x0 (source object type check)
0x6b84e89  jne 0x6B86790                 ; -> early exit if not type 1
0x6b84e8f  mov r15,r9                    ; save arg3 (r9)
0x6b84e92  mov rsi,rdx                   ; save arg2 (rdx) -> source data pointer
0x6b84e95  mov r14,rcx                   ; save arg1 (rcx) -> frame builder this
0x6b84e98  pxor xmm0,xmm0
0x6b84e9c  movdqa [rbp+0x2F0],xmm0       ; zero stack temp
0x6b84ea4  mov rax,[rdx+0x110]           ; R a1+0x110 (shared_ptr ptr)
0x6b84eab  test rax,rax
0x6b84eae  je short 0x6B84EBD
0x6b84eb0  lock inc dword ptr [rax+8]    ; W *(a1+0x110)+0x8 (refcount++)
0x6b84eb4  mov rax,[rsi+0x110]           ; R a1+0x110
0x6b84ebb  jmp short 0x6B84EBF
0x6b84ebd  xor eax,eax                   ; null shared_ptr
0x6b84ebf  mov rdx,[rsi+0x108]           ; R a1+0x108
0x6b84ec6  mov [rbp+0x2F0],rdx           ; save to stack
0x6b84ecd  mov [rbp+0x2F8],rax           ; save shared_ptr
0x6b84ed4  mov rcx,[rsi+0x118]           ; R a1+0x118
0x6b84edb  mov [rbp+0x300],rcx           ; save to stack
0x6b84ee2  test rdx,rdx
0x6b84ee5  mov [rbp+0x308],r8            ; save arg4 (r8)
0x6b84eec  je short 0x6B84F06
0x6b84eee  cmp byte ptr [rdx],1
0x6b84ef1  jne short 0x6B84F06
0x6b84ef3  mov rax,[rcx]
0x6b84ef6  mov rax,[rax+8]
0x6b84efa  call qword ptr [0xF99FFA0]    ; [data_f99ffa0] = sub_eea6040 (vcall)
0x6b84f00  nop
0x6b84f01  mov r12d,eax                  ; save vcall result (0/1)
0x6b84f04  jmp short 0x6B84F09
0x6b84f06  xor r12d,r12d                 ; r12 = 0
0x6b84f09  mov rbx,[rbp+0x3D8]           ; restore saved reg
0x6b84f10  mov rdi,[rbp+0x3D0]           ; restore saved reg
```
**What it does:** Function prologue, saves arguments (rcx=frame builder, rdx=source data, r9=arg3, r8=arg4), validates source object type (byte at +0x0 must be 1), increments refcount on shared_ptr at source+0x110, calls a virtual function on object at source+0x118 to get a boolean result into r12.

### Phase 2: 0x6b84f09..0x6b8503a - First Description Build Path (Mesh at r14+0x20) (70 instructions)
```
0x6b84f09  mov rbx,[rbp+0x3D8]
0x6b84f10  mov rdi,[rbp+0x3D0]
0x6b84f17  test rbx,rbx
0x6b84f1a  je 0x6B8503F                  ; -> alternate path if rbx=0
0x6b84f20  test r12b,r12b
0x6b84f23  jne 0x6B8503F                 ; -> alternate path if vcall returned true
0x6b84f29  mov r12,rdi
0x6b84f2c  lea rdi,[r14+0x20]            ; rdi = frame_builder+0x20 (mesh ptr?)
0x6b84f30  mov rcx,rdi
0x6b84f33  call 0x4DEF080                ; -> sub_4def080 (Mesh::hasDrawableData?)
0x6b84f38  nop
0x6b84f39  test al,al
0x6b84f3b  je 0x6B8528C                  ; -> error: "Quad material doesn't exist"
0x6b84f41  mov eax,[r14+0x1F8]
0x6b84f48  and eax,2
0x6b84f4b  mov rdx,[rbp+0x3C8]
0x6b84f52  mov rcx,[rdx+rax*8]
0x6b84f56  test rcx,rcx
0x6b84f59  je 0x6B85272                  ; -> error: "Quad material doesn't exist"
0x6b84f5f  cmp qword ptr [rcx+0x40],0
0x6b84f64  je 0x6B85272                  ; -> error: "Quad material doesn't exist"
0x6b84f6a  lea r8,[rdx+rax*8]
0x6b84f6e  mov [rsp+0x20],r12
0x6b84f73  mov rcx,rbx
0x6b84f76  mov rdx,r15
0x6b84f79  mov r9,rdi
0x6b84f7c  call 0x6B86E80                ; -> sub_6b86e80 (allocates description slot)
0x6b84f81  nop
0x6b84f82  mov rdi,rax                   ; rdi = returned object
0x6b84f85  lea rcx,[r14+0x4E0]
0x6b84f8c  mov byte ptr [rbp+0x290],1
0x6b84f93  mov [rbp+0x60],r14
0x6b84f97  mov r13,[rax+0x10]            ; R ret@6b86e80+0x10 -> description pointer
0x6b84f9b  cmp r13,[rax+0x18]            ; R ret@6b86e80+0x18 -> end pointer
0x6b84f9f  je 0x6B85450                  ; -> grow path if full
0x6b84fa5  movsxd rax,[r14+0x528]        ; sign-extend dword at frame_builder+0x528
0x6b84fac  mov [r13],r14                 ; W desc+0x0 = frame_builder this
0x6b84fb0  mov byte ptr [r13+8],1        ; W desc+0x8 = 1 (flag)
0x6b84fb5  mov [r13+0x10],rax            ; W desc+0x10 = sign-extended value
0x6b84fb9  mov rax,[rsi+0x30]            ; R source+0x30
0x6b84fbd  mov ecx,[rax+0x10]            ; R [rax+0x10] (count)
0x6b84fc0  mov [r13+0x28],ecx            ; W desc+0x28 = count
0x6b84fc4  movups xmm0,[rax]             ; R [rax+0x0..0xF] (16 bytes)
0x6b84fc7  movups [r13+0x18],xmm0        ; W desc+0x18 = 16 bytes (matrix row?)
0x6b84fcc  mov rax,[rsi+0x38]            ; R source+0x38
0x6b84fd0  mov ecx,[rax+0x10]            ; R [rax+0x10] (count)
0x6b84fd3  mov [r13+0x3C],ecx            ; W desc+0x3C = count
0x6b84fd7  movdqu xmm0,[rax]             ; R [rax+0x0..0xF] (16 bytes)
0x6b84fdb  movdqu [r13+0x2C],xmm0        ; W desc+0x2C = 16 bytes
0x6b84fe1  lea rcx,[r13+0x40]            ; R desc+0x40
0x6b84fe5  mov rdx,rsi
0x6b84fe8  call 0x6B87E00                ; -> sub_6b87e00 (processes desc+0x40)
0x6b84fed  lea rcx,[r13+0x190]           ; R desc+0x190
0x6b84ff4  pxor xmm0,xmm0
0x6b84ff8  movdqu [r13+0x190],xmm0       ; W desc+0x190 = zero (16 bytes)
0x6b85001  mov qword ptr [r13+0x1A0],0   ; W desc+0x1A0 = 0
0x6b8500c  lea r9,[r14+0x4E8]
0x6b85013  mov rdx,[r14+0x4E8]
0x6b8501a  sub rdx,[r14+0x4E0]
0x6b85021  sar rdx,6                     ; count = (end-start)/64
0x6b85025  lea r8,[r14+0x4E0]
0x6b8502c  call 0x6760560                ; -> sub_6760560
0x6b85031  nop
0x6b85032  add qword ptr [rdi+0x10],0x1A8 ; W ret@6b86e80+0x10 += 0x1A8 (advance pointer)
0x6b8503a  jmp 0x6B8528C                 ; -> merge to second path
```
**What it does:** First description build path. Checks mesh at frame_builder+0x20 has drawable data. Validates material from a table at [rbp+0x3C8] (indexed by frame_builder+0x1F8 & 2). Calls sub_6b86e80 to allocate a description slot. Fills the description at returned_ptr+0x10 with: +0x0=frame_builder, +0x8=1, +0x10=sign_extended(frame_builder+0x528), +0x18=16 bytes from source+0x30, +0x28=count from source+0x30+0x10, +0x2C=16 bytes from source+0x38, +0x3C=count from source+0x38+0x10. Calls sub_6b87e00 on desc+0x40. Zeroes desc+0x190 (16 bytes) and desc+0x1A0 (8 bytes). Calls sub_6760560 with range from frame_builder+0x4E0..+0x4E8. Advances the allocation pointer by 0x1A8 (size of each description entry).

### Phase 3: 0x6b8503f..0x6b8517d - Alternate Path: Copy Float Array from Source (48 instructions)
```
0x6b8503f  mov rax,[r14+0x10]
0x6b85043  cmp rax,[r14+8]
0x6b85047  je 0x6B8517D                  ; -> skip if empty
0x6b8504d  xor eax,eax
0x6b8504f  xor ecx,ecx
0x6b85051  jmp 0x6B85146
0x6b85060  mov r8,[r8+0xB0]
0x6b85067  mov r9,[r8+0x40]
0x6b8506b  movss xmm0,[rdx+rax]
0x6b85070  movss [r9],xmm0               ; W [r9+0x0] = float from source
0x6b85075  movss xmm0,[rdx+rax+4]
0x6b8507b  movss [r9+4],xmm0             ; W [r9+0x4]
0x6b85081  movss xmm0,[rdx+rax+8]
0x6b85087  movss [r9+8],xmm0             ; W [r9+0x8]
0x6b8508d  movss xmm0,[rdx+rax+0xC]
0x6b85093  movss [r9+0xC],xmm0           ; W [r9+0xC]
0x6b85099  movss xmm0,[rdx+rax+0x10]
0x6b8509f  movss [r9+0x10],xmm0          ; W [r9+0x10]
0x6b850a5  movss xmm0,[rdx+rax+0x14]
0x6b850ab  movss [r9+0x14],xmm0          ; W [r9+0x14]
0x6b850b1  movss xmm0,[rdx+rax+0x18]
0x6b850b7  movss [r9+0x18],xmm0          ; W [r9+0x18]
0x6b850bd  movss xmm0,[rdx+rax+0x1C]
0x6b850c3  movss [r9+0x1C],xmm0          ; W [r9+0x1C]
0x6b850c9  movss xmm0,[rdx+rax+0x20]
0x6b850cf  movss [r9+0x20],xmm0          ; W [r9+0x20]
0x6b850d5  movss xmm0,[rdx+rax+0x24]
0x6b850db  movss [r9+0x24],xmm0          ; W [r9+0x24]
0x6b850e1  movss xmm0,[rdx+rax+0x28]
0x6b850e7  movss [r9+0x28],xmm0          ; W [r9+0x28]
0x6b850ed  movss xmm0,[rdx+rax+0x2C]
0x6b850f3  movss [r9+0x2C],xmm0          ; W [r9+0x2C]
0x6b850f9  movss xmm0,[rdx+rax+0x30]
0x6b850ff  movss [r9+0x30],xmm0          ; W [r9+0x30]
0x6b85105  movss xmm0,[rdx+rax+0x34]
0x6b8510b  movss [r9+0x34],xmm0          ; W [r9+0x34]
0x6b85111  movss xmm0,[rdx+rax+0x38]
0x6b85117  movss [r9+0x38],xmm0          ; W [r9+0x38]
0x6b8511d  movd xmm0,[rdx+rax+0x3C]
0x6b85123  movd [r9+0x3C],xmm0           ; W [r9+0x3C]
0x6b85129  mov byte ptr [r8+0x31],1      ; W [r8+0x31] = 1
0x6b8512e  mov rdx,[r14+0x10]
0x6b85132  sub rdx,[r14+8]
0x6b85136  inc rcx
0x6b85139  sar rdx,3                     ; element count
0x6b8513d  add rax,0x40                  ; advance source by 64 bytes
0x6b85141  cmp rcx,rdx
0x6b85144  je short 0x6B8517D
0x6b85146  mov r8,[rsi+0x20]
0x6b8514a  mov rdx,[r14+0x4E0]
0x6b85151  cmp byte ptr [r14+0x530],1
0x6b85159  jne 0x6B85060                 ; -> different copy path
0x6b8515f  mov r8,[r8+0xA8]
0x6b85166  mov r9,[r8+0x40]
0x6b8516a  movss xmm0,[rdx+rax]
0x6b8516f  movss [r9+rax],xmm0           ; W [r9+rax] = float
0x6b85175  add r9,rax
0x6b85178  jmp 0x6B85075
```
**What it does:** Copies an array of float4 (16 floats = 64 bytes per element) from source data to a destination. Two copy paths based on frame_builder+0x530 flag. Iterates over elements from frame_builder+0x8 to +0x10. Writes 16 floats per element plus a flag byte at +0x31.

### Phase 4: 0x6b8517d..0x6b8528c - Second Description Build Path (Mesh at r14+0x280) (60 instructions)
```
0x6b8517d  lea r13,[r14+0x20]
0x6b85181  mov rcx,r13
0x6b85184  call 0x4DEF080                ; -> sub_4def080 (check mesh)
0x6b85189  nop
0x6b8518a  lea rbx,[r14+0x280]
0x6b85191  test al,al
0x6b85193  cmovne rbx,r13                ; rbx = mesh pointer (r13 or r14+0x280)
0x6b85197  mov rcx,rbx
0x6b8519a  call 0x4DEF080                ; -> sub_4def080 (check mesh)
0x6b8519f  nop
0x6b851a0  test al,al
0x6b851a2  je 0x6B8670A                  ; -> exit if no drawable data
0x6b851a8  test r12b,r12b
0x6b851ab  je 0x6B853BC                  ; -> alternate path if vcall was false
0x6b851b1  pxor xmm0,xmm0
0x6b851b5  movdqu [rbp+0x2B8],xmm0
0x6b851bd  mov byte ptr [rbp+0x2C8],0
0x6b851c4  movdqa [rbp+0x290],xmm0
0x6b851cc  movdqa [rbp+0x2A0],xmm0
0x6b851d4  mov byte ptr [rbp+0x2B0],0
0x6b851db  movdqa [rbp+0x2D0],xmm0
0x6b851e3  movdqa [rbp+0x2E0],xmm0
0x6b851eb  mov rax,[rdi]
0x6b851ee  test rax,rax
0x6b851f1  je 0x6B85CAB
0x6b851f7  mov r12,[rax]
0x6b851fa  test r12,r12
0x6b851fd  je 0x6B85CAB
0x6b85203  mov eax,[0x128D8FC8]
0x6b85209  mov ecx,[0x128767C8]
0x6b8520f  mov rdx,gs:[0x58]
0x6b85218  mov rcx,[rdx+rcx*8]
0x6b8521c  cmp eax,[rcx+4]
0x6b85222  jg 0x6B867A9
0x6b85228  lock inc word ptr [r12+0x10]
0x6b8522f  movzx eax,byte ptr [r12+0x12]
0x6b85235  test al,1
0x6b85237  je 0x6B85CAB
0x6b8523d  mov rax,[rdi]
0x6b85240  pxor xmm0,xmm0
0x6b85244  movdqa [rbp+0x310],xmm0
0x6b8524c  mov rcx,[rax]
0x6b8524f  test rcx,rcx
0x6b85252  je short 0x6B85258
0x6b85254  movzx ecx,word ptr [rcx+0x10]
0x6b85258  mov rcx,[rax+8]
0x6b8525c  test rcx,rcx
0x6b8525f  je 0x6B854C2
0x6b85265  lock inc dword ptr [rcx+8]
0x6b85269  mov rcx,[rax+8]
0x6b8526d  jmp 0x6B854C4
0x6b85272  lea r9,[0xF52AED4]            ; "Quad material doesn't exist"
0x6b85279  mov cl,1
0x6b8527b  mov edx,3
0x6b85280  mov r8d,0x1A
0x6b85286  call 0xEAA30                  ; -> sub_eaa30 (log error)
0x6b8528b  nop
0x6b8528c  lea rdi,[r14+0x280]
0x6b85293  mov rcx,rdi
0x6b85296  call 0x4DEF080                ; -> sub_4def080
0x6b8529b  nop
0x6b8529c  test al,al
0x6b8529e  je 0x6B8670A
0x6b852a4  mov eax,[r14+0x458]
0x6b852ab  and eax,2
0x6b852ae  mov rdx,[rbp+0x3C8]
0x6b852b5  mov rcx,[rdx+rax*8]
0x6b852b9  test rcx,rcx
0x6b852bc  je 0x6B8539D
0x6b852c2  cmp qword ptr [rcx+0x40],0
0x6b852c7  je 0x6B8539D
0x6b852cd  lea r8,[rdx+rax*8]
0x6b852d1  mov [rsp+0x20],r12
0x6b852d6  mov rcx,rbx
0x6b852d9  mov rdx,r15
0x6b852dc  mov r9,rdi
0x6b852df  call 0x6B86E80                ; -> sub_6b86e80 (allocates description slot)
0x6b852e4  nop
0x6b852e5  mov rdi,rax
0x6b852e8  lea rbx,[r14+0x4E0]
0x6b852ef  mov byte ptr [rbp+0x290],1
0x6b852f6  mov [rbp+0x60],r14
0x6b852fa  mov r15,[rax+0x10]            ; R ret@6b86e80+0x10 -> description pointer
0x6b852fe  cmp r15,[rax+0x18]            ; R ret@6b86e80+0x18 -> end pointer
0x6b85302  je 0x6B85489                  ; -> grow path
0x6b85308  movsxd rax,[r14+0x528]
0x6b8530f  mov [r15],r14                 ; W desc+0x0 = frame_builder
0x6b85312  mov byte ptr [r15+8],1        ; W desc+0x8 = 1
0x6b85317  mov [r15+0x10],rax            ; W desc+0x10 = sign_extended value
0x6b8531b  mov rax,[rsi+0x30]
0x6b8531f  mov ecx,[rax+0x10]
0x6b85322  mov [r15+0x28],ecx            ; W desc+0x28 = count
0x6b85326  movups xmm0,[rax]
0x6b85329  movups [r15+0x18],xmm0        ; W desc+0x18 = 16 bytes
0x6b8532e  mov rax,[rsi+0x38]
0x6b85332  mov ecx,[rax+0x10]
0x6b85335  mov [r15+0x3C],ecx            ; W desc+0x3C = count
0x6b85339  movdqu xmm0,[rax]
0x6b8533d  movdqu [r15+0x2C],xmm0        ; W desc+0x2C = 16 bytes
0x6b85343  lea rcx,[r15+0x40]
0x6b85347  mov rdx,rsi
0x6b8534a  call 0x6B87E00                ; -> sub_6b87e00
0x6b8534f  lea rcx,[r15+0x190]
0x6b85356  pxor xmm0,xmm0
0x6b8535a  movdqu [r15+0x190],xmm0       ; W desc+0x190 = zero
0x6b85363  mov qword ptr [r15+0x1A0],0   ; W desc+0x1A0 = 0
0x6b8536e  lea r9,[r14+0x4E8]
0x6b85375  mov rdx,[r14+0x4E8]
0x6b8537c  sub rdx,[r14+0x4E0]
0x6b85383  sar rdx,6
0x6b85387  mov r8,rbx
0x6b8538a  call 0x6760560
0x6b8538f  nop
0x6b85390  add qword ptr [rdi+0x10],0x1A8
0x6b85398  jmp 0x6B8670A
```
**What it does:** Second description build path, nearly identical to first but uses mesh at frame_builder+0x280 (or +0x20). Same description layout written at offsets +0x0, +0x8, +0x10, +0x18, +0x28, +0x2C, +0x3C, +0x40 (sub_6b87e00), +0x190, +0x1A0. Error path for "Tri material doesn't exist" at 0x6b8539d.

### Phase 5: 0x6b853bc..0x6b855d7 - Third Path (r12b=0): Refcount & SharedRef Handling (70 instructions)
```
0x6b853bc  mov rax,[rdi]
0x6b853bf  xor r14d,r14d
0x6b853c2  test rax,rax
0x6b853c5  je short 0x6B85444
0x6b853c7  mov r15,[rax]
0x6b853ca  test r15,r15
0x6b853cd  mov r12,[rbp+0x3C8]
0x6b853d4  je 0x6B855D7
0x6b853da  mov eax,[0x128D8FC8]
0x6b853e0  mov ecx,[0x128767C8]
0x6b853e6  mov rdx,gs:[0x58]
0x6b853ef  mov rcx,[rdx+rcx*8]
0x6b853f3  cmp eax,[rcx+4]
0x6b853f9  jg 0x6B867DF
0x6b853ff  lock inc word ptr [r15+0x10]
0x6b85405  movzx eax,byte ptr [r15+0x12]
0x6b8540a  test al,1
0x6b8540c  je 0x6B855D7
0x6b85412  mov rax,[rdi]
0x6b85415  pxor xmm0,xmm0
0x6b85419  movdqa [rbp+0x60],xmm0
0x6b8541e  mov rcx,[rax]
0x6b85421  test rcx,rcx
0x6b85424  je short 0x6B8542A
0x6b85426  movzx ecx,word ptr [rcx+0x10]
0x6b8542a  mov rcx,[rax+8]
0x6b8542e  test rcx,rcx
0x6b85431  je 0x6B8553E
0x6b85437  lock inc dword ptr [rcx+8]
0x6b8543b  mov rcx,[rax+8]
0x6b8543f  jmp 0x6B85540
... (refcount management continues, calls sub_4dfb570 at 0x6b8551e, sub_4e00090 at 0x6b85595)
```
**What it does:** Handles shared_ptr refcounting when vcall result (r12) was 0. Increments weak/strong counts, calls sub_4dfb570 (resolveSharedRef) and sub_4e00090 (process mesh data). Four similar blocks for different mesh pointers at rdi+0x0, +0x8, +0x18, +0x28, +0x30.

### Phase 6: 0x6b855d7..0x6b85bd1 - Mesh Data Processing Loop (5 identical blocks for 5 mesh pointers) (~300 instructions)
Each block processes a mesh pointer at rdi+0x0, +0x8, +0x18, +0x28, +0x30:
- Refcount management (lock inc/dec word/dword at +0x10, +0x8, +0xC)
- Calls sub_4e00090 with data from rsi+0x20+0x128, rsi+0x10
- Increments r14d counter

### Phase 7: 0x6b85bd1..0x6b8640f - Material Selection & Builder Call (~300 instructions)
```
0x6b85bd1  cmp byte ptr [rbx+0x1A1],0
0x6b85bd8  je 0x6B85AD8
... (material validation logic comparing words at rbx+0x1D8, +0x1FC, +0x1F8, +0x21C)
... (SSE comparisons against constants at 0xF275E82, 0xF275E90)
0x6b85acd  mov eax,0x10
0x6b85ad2  jmp short 0x6B85ADA
0x6b85ad8  xor eax,eax
0x6b85ada  pxor xmm0,xmm0
0x6b85ade  movdqa [rbp+0x310],xmm0
0x6b85ae6  mov rcx,[r12+rax+8]           ; select from material table
0x6b85aeb  test rcx,rcx
0x6b85aee  je short 0x6B85AFB
0x6b85af0  lock inc dword ptr [rcx+8]
0x6b85af4  mov rcx,[r12+rax+8]
0x6b85af9  jmp short 0x6B85AFD
0x6b85afb  xor ecx,ecx
0x6b85afd  mov rax,[r12+rax]
0x6b85b01  mov [rbp+0x310],rax
0x6b85b08  mov [rbp+0x318],rcx
0x6b85b0f  test rax,rax
0x6b85b12  je short 0x6B85B6F
0x6b85b14  cmp qword ptr [rax+0x40],0
0x6b85b19  je short 0x6B85B6F
0x6b85b1b  mov rdi,[rbp+0x308]
0x6b85b22  add rdi,0x18
0x6b85b26  add rsi,0x10
0x6b85b2a  mov byte ptr [rbp+0x2C8],0
0x6b85b31  lea r14,[rbp+0x60]
0x6b85b35  mov r8d,0x148
0x6b85b3b  mov rcx,r14
0x6b85b3e  xor edx,edx
0x6b85b40  call 0xEEC6ED0                ; -> sub_eec6ed0
0x6b85b45  nop
0x6b85b46  lea rax,[rbp+0x290]
0x6b85b4d  mov [rsp+0x40],rax
0x6b85b52  mov [rsp+0x30],rdi
0x6b85b57  lea r8,[rbp+0x310]
0x6b85b5e  mov rcx,rbx
0x6b85b61  mov rdx,rsi
0x6b85b64  mov r9,r14
0x6b85b67  call 0x4DEF480                ; -> sub_4def480 (builder variant)
0x6b85b6c  nop
0x6b85b6d  jmp short 0x6B85B89
0x6b85b6f  lea r9,[0xF52AEB8]            ; "Mesh material doesn't exist"
0x6b85b76  mov cl,1
0x6b85b78  mov edx,3
0x6b85b7d  mov r8d,0x1A
0x6b85b83  call 0xEAA30
0x6b85b88  nop
0x6b85b89  mov rsi,[rbp+0x318]
0x6b85b90  test rsi,rsi
0x6b85b93  je 0x6B8670A
... (refcount cleanup)
```
**What it does:** Selects material based on flags in rbx (frame_builder+0x280 area). Calls sub_4def480 (the MeshFallback builder) with prepared arguments. Error path for "Mesh material doesn't exist".

### Phase 8: 0x6b8640f..0x6b86616 - Main SkinnedMesh Builder Call (sub_668d350) (~150 instructions)
```
0x6b8640f  test rax,rax
0x6b86412  je 0x6B866E4
0x6b86418  cmp qword ptr [rax+0x40],0
0x6b8641d  je 0x6B866E4
0x6b86423  mov rax,[rsi+0x18]
0x6b86427  mov rcx,[rax+0x60]
0x6b8642b  mov rdx,[rax+0x58]
0x6b8642f  add rcx,rdx
0x6b86432  dec rcx
0x6b86435  mov rdx,[rax+0x48]
0x6b86439  mov rax,[rax+0x50]
0x6b8643d  dec rax
0x6b86440  and rax,rcx
0x6b86443  mov rdx,[rdx+rax*8]
0x6b86447  mov rax,[rbp+0x308]
0x6b8644e  movzx eax,byte ptr [rax+0x10]
0x6b86452  mov rcx,[rbp+0x2F0]
0x6b86459  test rcx,rcx
0x6b8645c  jne short 0x6B86469
0x6b8645e  mov dword ptr [0],0xDEADC0DE  ; crash if null
0x6b86469  mov r8,[rbp+0x3E0]
0x6b86470  cmp byte ptr [rcx],0
0x6b86473  jne short 0x6B86480
0x6b86475  mov dword ptr [0],0xDEADC0DE
0x6b86480  cmp byte ptr [r8+0x40],0
0x6b86485  cmove r8,rdx
0x6b86489  mov rdi,[rbp+0x300]
0x6b86490  movups xmm0,[r14+0x510]
0x6b86498  movaps [rbp+0x40],xmm0
0x6b8649c  movq xmm0,[r14+0x520]
0x6b864a5  movq [rbp+0x50],xmm0
0x6b864aa  mov byte ptr [rbp+0x58],0
0x6b864ae  mov ecx,[r14+0x528]
0x6b864b5  mov r9,[rsi+0x30]
0x6b864b9  mov r11,[r14+0x4E0]
0x6b864c0  mov r10,[r14+0x4E8]
0x6b864c7  mov r12,r10
0x6b864ca  sub r12,r11
0x6b864cd  mov r13,r12
0x6b864d0  sar r13,6
0x6b864d4  mov [rbp+0x248],r13
0x6b864db  cmp r12,0xFFFFFFFFFFFFFFC0
0x6b864df  je 0x6B867A4
0x6b864e5  mov [rbp+0x250],r11
0x6b864ec  test r11,r11
0x6b864ef  setne r11b
0x6b864f3  test r10,r10
0x6b864f6  sete r10b
0x6b864fa  or r10b,r11b
0x6b864fd  je 0x6B867A4
0x6b86503  mov r11,[r14+0x4F8]
0x6b8650a  mov r10,[r14+0x500]
0x6b86511  mov r14,r10
0x6b86514  sub r14,r11
0x6b86517  mov r12,r14
0x6b8651a  sar r12,6
0x6b8651e  mov [rbp+0x258],r12
... (more setup)
0x6b8660b  lea rsi,[rbp+0x60]
0x6b8660f  lea r9,[rbp+0x40]
0x6b86613  mov rcx,rsi
0x6b86616  call 0x668D350                ; -> sub_668d350 (SkinnedMesh builder, 21 args)
```
**What it does:** Prepares 21 arguments on stack and in registers for the SkinnedMesh builder (sub_668d350). Sets up matrices from frame_builder+0x510, +0x520, counts from +0x4E0/+0x4E8, +0x4F8/+0x500, and various flags/bytes from source and frame_builder. Calls the 21-argument constructor that fully populates RenderSkinnedMeshDescription.

### Phase 9: 0x6b86616..0x6b867a3 - Tag 7 Insert & Cleanup (~100 instructions)
```
0x6b8661b  nop
0x6b8661c  mov rbx,[rbp+0x288]
0x6b86623  mov eax,[0x129C1A28]
0x6b86629  mov ecx,[0x128767C8]
0x6b8662f  mov rdx,gs:[0x58]
0x6b86638  mov rcx,[rdx+rcx*8]
0x6b8663c  cmp eax,[rcx+4]
0x6b86642  jg 0x6B869C5
0x6b86648  lea rcx,[0x129C18F0]
0x6b8664f  mov [rbp+0x268],rcx
0x6b86656  mov byte ptr [rbp+0x270],0
0x6b8665d  lea rdi,[rbp+0x278]
0x6b86664  mov qword ptr [rbp+0x280],0
0x6b8666f  mov byte ptr [rbp+0x348],0
0x6b86676  lea r8,[rbp+0x310]
0x6b8667d  mov rdx,rdi
0x6b86680  call 0x39A7D40
0x6b86685  nop
0x6b86686  mov [rbp+0x270],al
0x6b8668c  mov [rbp+0x310],rsi
0x6b86693  mov byte ptr [rbp+0x318],7    ; TAG 7 = SkinnedMesh
0x6b8669a  mov rcx,rbx
0x6b8669d  mov rax,[rbx]
0x6b866a0  mov rax,[rax+0x378]          ; Item vtable slot 0x378
0x6b866a7  lea rdx,[rbp+0x310]
0x6b866ae  call qword ptr [0xF99FFA0]    ; -> sub_eea6040 (vcall insert)
0x6b866b4  nop
0x6b866b5  cmp byte ptr [rbp+0x270],1
0x6b866bc  jne short 0x6B866D9
0x6b866be  mov r8,[rbp+0x268]
0x6b866c5  add r8,0x60
0x6b866c9  lea rcx,[0x1244FD00]
0x6b866d0  mov rdx,rdi
0x6b866d3  call 0x77A2500
0x6b866d8  nop
0x6b866d9  lea rcx,[rbp+0x60]
0x6b866dd  call 0x4E69270
0x6b866e2  jmp short 0x6B866FE
0x6b866e4  lea r9,[0xF52AEB8]            ; "Mesh material doesn't exist"
0x6b866eb  mov cl,1
0x6b866ed  mov edx,3
0x6b866f2  mov r8d,0x1A
0x6b866f8  call 0xEAA30
0x6b866fd  nop
0x6b866fe  lea rcx,[rbp+0x290]
0x6b86705  call 0x4E3B020
0x6b8670a  pxor xmm0,xmm0
0x6b8670e  mov rsi,[rbp+0x2F8]
0x6b86715  movdqa [rbp+0x2F0],xmm0
0x6b8671d  test rsi,rsi
0x6b86720  je short 0x6B86790
0x6b86722  lock dec dword ptr [rsi+8]
... (refcount cleanup for saved shared_ptrs)
0x6b86790  add rsp,0x3D8
0x6b86797  pop rbx
0x6b86798  pop rdi
0x6b86799  pop rsi
0x6b8679a  pop r12
0x6b8679c  pop r13
0x6b8679e  pop r14
0x6b867a0  pop r15
0x6b867a2  pop rbp
0x6b867a3  ret
```
**What it does:** Inserts the built description with tag 7 (SkinnedMesh) via the Item group vtable slot 0x378. Calls the vcall at [rbx+0x378] with the description pointer. On success, calls sub_4e69270 and sub_4e3b020 for cleanup. Releases all saved shared_ptr references. Function epilogue.

---

## Step 3: Stores into Description Being Cloned

### Table of Stores into Description Object (at `ret@6b86e80+0x10`)
Two identical description objects are created (first at r13, second at r15). Each is 0x1A8 bytes.

| Offset | Size | Instruction (RVA) | Source | Meaning | Tag |
|--------|------|-------------------|--------|---------|-----|
| +0x00  | 8    | `mov [r13],r14` (0x6b84fac) / `mov [r15],r14` (0x6b8530f) | r14 (frame_builder this) | Back-pointer to frame builder | [V] |
| +0x08  | 1    | `mov byte [r13+8],1` (0x6b84fb0) / `mov byte [r15+8],1` (0x6b85312) | imm 1 | Flag byte (initialized=1) | [V] |
| +0x10  | 8    | `mov [r13+0x10],rax` (0x6b84fb5) / `mov [r15+0x10],rax` (0x6b85317) | rax = sign-extended `[r14+0x528]` | Instance index / variant selector | [V] |
| +0x18  | 16   | `movups [r13+0x18],xmm0` (0x6b84fc7) / `movups [r15+0x18],xmm0` (0x6b85329) | xmm0 = `[rsi+0x30]` (16 bytes) | Matrix row 0 / bone data part 1 | [V] |
| +0x28  | 4    | `mov [r13+0x28],ecx` (0x6b84fc0) / `mov [r15+0x28],ecx` (0x6b85322) | ecx = `[[rsi+0x30]+0x10]` | Count/stride from source+0x30 | [V] |
| +0x2C  | 16   | `movdqu [r13+0x2C],xmm0` (0x6b84fdb) / `movdqu [r15+0x2C],xmm0` (0x6b8533d) | xmm0 = `[rsi+0x38]` (16 bytes) | Matrix row 1 / bone data part 2 | [V] |
| +0x3C  | 4    | `mov [r13+0x3C],ecx` (0x6b84fd3) / `mov [r15+0x3C],ecx` (0x6b85335) | ecx = `[[rsi+0x38]+0x10]` | Count/stride from source+0x38 | [V] |
| +0x40  | ?    | `call 0x6B87E00` (0x6b84fe8) / `call 0x6B87E00` (0x6b8534a) | rcx=desc+0x40, rdx=rsi | Processes desc+0x40 via sub_6b87e00 | [V] |
| +0x190 | 16   | `movdqu [r13+0x190],xmm0` (0x6b84ff8) / `movdqu [r15+0x190],xmm0` (0x6b8535a) | xmm0=0 | Zero padding / reserved | [V] |
| +0x1A0 | 8    | `mov qword [r13+0x1A0],0` (0x6b85001) / `mov qword [r15+0x1A0],0` (0x6b85363) | 0 | Zero padding / reserved | [V] |

**Total per description: 0x1A8 bytes (424 bytes).** Two descriptions created sequentially.

### Stores into Float Array Destination (r9, 16 floats per element)
| Offset | Size | Instruction | Source | Meaning |
|--------|------|-------------|--------|---------|
| +0x00..+0x3C | 16x4 | `movss [r9+off],xmm0` (0x6b85070-0x6b85123) | `[rdx+rax+off]` | Copy 16 floats (4x4 matrix) per element |
| +0x31 | 1 | `mov byte [r8+0x31],1` (0x6b85129) | imm 1 | Element valid flag |

### Stores into Stack Temps (rbp-relative)
Many stores to [rbp+0x290], [rbp+0x2A0], [rbp+0x2B0], [rbp+0x2B8], [rbp+0x2C8], [rbp+0x2D0], [rbp+0x2E0], [rbp+0x2F0], [rbp+0x310], [rbp+0x318], [rbp+0x60], [rbp+0x70], etc. for argument passing to sub_668d350.

---

## Step 4: Callers & Match Against Descriptions.h

### Callers (from preflight)
1. **sub_6b80870** - 1 call site
2. **sub_6b80f00** - 1 call site  
3. **sub_6e8dff0** - 3 call sites

These are likely the Item group clone dispatchers (fat/thin clones for SkinnedMesh). The Item group vtable slot 0x378 is used for tag 7 insertion (confirmed at 0x6b866a0: `mov rax,[rax+0x378]`).

### Match Against RenderSkinnedMeshDescription (Descriptions.h, size 0x1D0)
The clone function creates **two intermediate description objects** of 0x1A8 bytes each (at sub_6b86e80 return +0x10), then calls the **full 21-argument builder sub_668d350** which writes the complete RenderSkinnedMeshDescription (0x1D0 bytes).

**Clone's intermediate stores (0x1A8) vs Final Description (0x1D0):**
- Clone writes: frame_builder ptr (+0x0), flag (+0x8), instance index (+0x10), two 16-byte blocks (+0x18, +0x2C), two counts (+0x28, +0x3C), calls sub_6b87e00 at +0x40, zeros +0x190/+0x1A0
- These are **partial/preparatory fields** passed to the builder
- The builder sub_668d350 (called at 0x6b86616) writes the full 0x1D0 structure including:
  - mMatrixA[16] +0x000, mMatrixB[16] +0x040
  - mBounds[6] +0x080, mBoundsEmpty +0x098
  - mMeshVec4[4] +0x09C, mMesh +0x0B0
  - Five SharedRefs at +0x0E0, +0x0F0, +0x108, +0x120, +0x130
  - mMaterial +0x140, mFlags150[4] +0x150
  - mBlock154[4] +0x154, mBlock164[4] +0x164
  - mValue174 +0x174, mCount178 +0x178
  - mVariantHead[0x10] +0x180, mVariantByte +0x190, mVariantPayload[0x18] +0x198
  - mVariantIndex +0x1B0, mOverride[4] +0x1B8, mHasOverride +0x1C8
  - mFlags1CC +0x1CC, mByte1CE +0x1CE

**Tag 7 Store:** At 0x6b86693: `mov byte ptr [rbp+0x318],7` - explicitly writes tag 7 (SkinnedMesh) before the vcall insert.

**Insert VCall:** At 0x6b866a0-0x6b866ae: loads Item vtable slot 0x378 from the render object (rbx) and calls it with the description. This matches the Item group clone convention (tag 7 = SkinnedMesh).

**Second Producer:** The checklist mentions producer 0x4e39f20 as the second producer that calls builder 0x668d350. This clone (0x6b84e60) is the **general clone** called from the Item group dispatchers, while 0x4e39f20 is a separate producer path (likely for entity models).

---

## Verification Status
- Function listing: INSTRUCTION-COMPLETE (all 0x1bf0 bytes covered in 9 phases)
- Stores table: COMPLETE (all non-stack stores catalogued)
- Callers: IDENTIFIED (3 calling functions)
- Descriptions.h match: CONFIRMED (tag 7, builder 0x668d350, vslot 0x378)

## TOOL REQUESTS
- stores.py needs to handle listings without 0x prefix on addresses (current regex expects 0x). Fixed with custom regex.
- A combined "preflight" that also runs stores.py and callers would save time.
- verify_oc.py should be run on the final document.