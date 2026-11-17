## NEXT
DONE

# U-Edh — EditorHighlightConfiguration clone (0x4C8A5B0) + producer (0x4C88900)

Sources (read fully, all lines below verbatim from them): docs/data/listings/lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt (70 ins), docs/data/listings/lightgame_edhighlight_producer_4c88900_4c89881.txt (823 ins). `call qword ptr [0xF99FFA0]` = CFG-guarded indirect/virtual call with target in rax [I]. Phase lines are exact copies of the listing lines.

## Function 1: EditorHighlightConfiguration clone, 0x4C8A5B0..0x4C8A6E4

#### 0x4c8a5b0..0x4c8a658: Prologue saves rbx/rdi/rsi, reserves 0xC8 bytes with frame rbp=rsp+0x80 and EH guard slot [rbp+0x40]=-2; source object rcx kept in rsi, destination rdx kept in rdi. Thread-safe static-init check: global epoch [0x129C0BA0] vs TLS slot at [[gs:[0x58]+[0x128767C8]*8]+4]; if the global is behind, jump to the init path at 0x4C8A66A. Fast path: call 0x39A7D40 (rcx=static object 0x129C0A68, rdx=rbp+0x30 out, r8=rbp-0x50) returning a bool into [rbp+0x28]; wraps the destination pointer rdi in an engaged optional-like ([rbp+0x10]=rdi, [rbp+0x18]=8) and virtual-calls source vtable slot +0x360 with it.
```
0x4c8a5b0  push rbp
0x4c8a5b1  push rsi
0x4c8a5b2  push rdi
0x4c8a5b3  push rbx
0x4c8a5b4  sub rsp,0xC8
0x4c8a5bb  lea rbp,[rsp+0x80]
0x4c8a5c3  mov qword ptr [rbp+0x40],0xFFFFFFFFFFFFFFFE
0x4c8a5cb  mov rdi,rdx
0x4c8a5ce  mov rsi,rcx
0x4c8a5d1  mov eax,[0x129C0BA0]
0x4c8a5d7  mov ecx,[0x128767C8]
0x4c8a5dd  mov rdx,gs:[0x58]
0x4c8a5e6  mov rcx,[rdx+rcx*8]
0x4c8a5ea  cmp eax,[rcx+4]
0x4c8a5f0  jg short 0x4C8A66A
0x4c8a5f2  lea rcx,[0x129C0A68]
0x4c8a5f9  mov [rbp+0x20],rcx
0x4c8a5fd  mov byte ptr [rbp+0x28],0
0x4c8a601  lea rbx,[rbp+0x30]
0x4c8a605  mov qword ptr [rbp+0x38],0
0x4c8a60d  mov byte ptr [rbp-0x18],0
0x4c8a611  lea r8,[rbp-0x50]
0x4c8a615  mov rdx,rbx
0x4c8a618  call 0x39A7D40
0x4c8a61d  mov [rbp+0x28],al
0x4c8a620  mov [rbp+0x10],rdi
0x4c8a624  mov byte ptr [rbp+0x18],8
0x4c8a628  mov rax,[rsi]
0x4c8a62b  mov rax,[rax+0x360]
0x4c8a632  lea rdx,[rbp+0x10]
0x4c8a636  mov rcx,rsi
0x4c8a639  call qword ptr [0xF99FFA0]
0x4c8a63f  nop
0x4c8a640  cmp byte ptr [rbp+0x28],1
0x4c8a644  jne short 0x4C8A65E
0x4c8a646  mov r8,[rbp+0x20]
0x4c8a64a  add r8,0x60
0x4c8a64e  lea rcx,[0x1244FD00]
0x4c8a655  mov rdx,rbx
0x4c8a658  call 0x77A2500
```

#### 0x4c8a65d..0x4c8a6e4: If the bool [rbp+0x28]==1, call 0x77A2500 (rcx=0x1244FD00 blob, rdx=rbp+0x30 result, r8=0x129C0A68+0x60) — registers/applies the produced value into the static registry's +0x60 member [I] — then epilogue. Slow path 0x4C8A66A: refresh the TLS epoch via 0xE938CB0; if guard [0x129C0BA0] is still -1, build a 21-byte (0x15) message string from constants 0xF52E07A/0xF0BCBF8 and call 0x2FE330 with type blob 0xF20B440 and r8b=1 (throw/report helper [I]), then register cleanup 0x4CA4170 via 0xE935740, bump the guard via 0xE938D70, and jump back to the fast path.
```
0x4c8a65d  nop
0x4c8a65e  add rsp,0xC8
0x4c8a665  pop rbx
0x4c8a666  pop rdi
0x4c8a667  pop rsi
0x4c8a668  pop rbp
0x4c8a669  ret
0x4c8a66a  lea rcx,[0x129C0BA0]
0x4c8a671  call 0xE938CB0
0x4c8a676  cmp dword ptr [0x129C0BA0],0xFFFFFFFF
0x4c8a67d  jne 0x4C8A5F2
0x4c8a683  lea rax,[0xF52E07A]
0x4c8a68a  mov [rbp],rax
0x4c8a68e  mov qword ptr [rbp+8],0x15
0x4c8a696  movups xmm0,[0xF0BCBF8]
0x4c8a69d  movaps [rbp-0x10],xmm0
0x4c8a6a1  lea rax,[0xF20B440]
0x4c8a6a8  mov [rsp+0x28],rax
0x4c8a6ad  mov dword ptr [rsp+0x20],0
0x4c8a6b5  lea rcx,[0x129C0A68]
0x4c8a6bc  lea rdx,[rbp-0x10]
0x4c8a6c0  mov r9,rbp
0x4c8a6c3  mov r8b,1
0x4c8a6c6  call 0x2FE330
0x4c8a6cb  nop
0x4c8a6cc  lea rcx,[0x4CA4170]
0x4c8a6d3  call 0xE935740
0x4c8a6d8  lea rcx,[0x129C0BA0]
0x4c8a6df  call 0xE938D70
0x4c8a6e4  jmp 0x4C8A5F2
```

## Function 2: EditorHighlightConfiguration producer, 0x4C88900..0x4C89880

#### 0x4c88900..0x4c88a1a: Prologue: 8 GPR pushes + 0x838 frame, rbp=rsp+0x80, saves xmm6-xmm14 and EH guard [rbp+0x718]=-2; args rcx→rbx (this), rdx→rdi, r8→rsi. Lazy init: if byte [rbx+0x38]==0 call 0x331DF0 on rcx=rbx+0x18 with float constant 0xEEC8060 in xmm1, then set [rbx+0x38]=1; if [rbx+0x60] already non-null jump 0x4C88BED; else virtual-call slot +0x338 of [rsi] into [rbp+0x568], zero 0x3D8 bytes at [rbp+0x18] (0xEEC6ED0), and build a string from constant 0x79616C7265764F2D ('-Overlay' [I]) plus the 32 bytes at 0xF51E461/0xF51E471, with [rbp+0x3F0]=0x28 and the data/len pair in [rbp+0x5D8]/[rbp+0x5E0].
```
0x4c88900  push rbp
0x4c88901  push r15
0x4c88903  push r14
0x4c88905  push r13
0x4c88907  push r12
0x4c88909  push rsi
0x4c8890a  push rdi
0x4c8890b  push rbx
0x4c8890c  sub rsp,0x838
0x4c88913  lea rbp,[rsp+0x80]
0x4c8891b  movaps [rbp+0x7A0],xmm14
0x4c88923  movaps [rbp+0x790],xmm13
0x4c8892b  movaps [rbp+0x780],xmm12
0x4c88933  movdqa [rbp+0x770],xmm11
0x4c8893c  movdqa [rbp+0x760],xmm10
0x4c88945  movaps [rbp+0x750],xmm9
0x4c8894d  movaps [rbp+0x740],xmm8
0x4c88955  movaps [rbp+0x730],xmm7
0x4c8895c  movaps [rbp+0x720],xmm6
0x4c88963  mov qword ptr [rbp+0x718],0xFFFFFFFFFFFFFFFE
0x4c8896e  mov rsi,r8
0x4c88971  mov rdi,rdx
0x4c88974  mov rbx,rcx
0x4c88977  cmp byte ptr [rcx+0x38],0
0x4c8897b  jne short 0x4C88992
0x4c8897d  lea rcx,[rbx+0x18]
0x4c88981  movss xmm1,[0xEEC8060]
0x4c88989  call 0x331DF0
0x4c8898e  mov byte ptr [rbx+0x38],1
0x4c88992  lea r13,[rbx+0x60]
0x4c88996  mov rax,[rbx+0x60]
0x4c8899a  test rax,rax
0x4c8899d  jne 0x4C88BED
0x4c889a3  mov rax,[rsi]
0x4c889a6  mov rax,[rax+0x338]
0x4c889ad  lea rdx,[rbp+0x568]
0x4c889b4  mov rcx,rsi
0x4c889b7  call qword ptr [0xF99FFA0]
0x4c889bd  mov r14,[rbp+0x568]
0x4c889c4  lea rcx,[rbp+0x18]
0x4c889c8  mov r8d,0x3D8
0x4c889ce  xor edx,edx
0x4c889d0  call 0xEEC6ED0
0x4c889d5  mov rax,0x79616C7265764F2D
0x4c889df  mov [rbp+0x10],rax
0x4c889e3  movups xmm0,[0xF51E461]
0x4c889ea  movaps [rbp-0x10],xmm0
0x4c889ee  movups xmm0,[0xF51E471]
0x4c889f5  movaps [rbp],xmm0
0x4c889f9  mov qword ptr [rbp+0x3F0],0x28
0x4c88a04  lea rax,[rbp-0x10]
0x4c88a08  mov [rbp+0x5D8],rax
0x4c88a0f  mov qword ptr [rbp+0x5E0],0x28
0x4c88a1a  lea rcx,[rbp+0x480]
```

#### 0x4c88a21..0x4c88a8e: Copy/construct the string into [rbp+0x480] via 0x3946B0, then r14=[rbp+0x568]+0x18 and a copy through 0x541F8F0 (rcx=r14, rdx=r15=rbp+0x400, r8=[rbp+0x480], r9d=0). If r13 (rbx+0x60) == r15 skip the swap; else move the built 16-byte value [rbp+0x400] into [rbx+0x60] (zeroing the local with xmm6) and save the old control block [rbx+0x68] into r14 for release (lock dec [r14+8]).
```
0x4c88a21  lea rdx,[rbp+0x5D8]
0x4c88a28  call 0x3946B0
0x4c88a2d  nop
0x4c88a2e  add r14,0x18
0x4c88a32  mov byte ptr [rsp+0x28],0
0x4c88a37  mov qword ptr [rsp+0x20],0
0x4c88a40  lea r15,[rbp+0x400]
0x4c88a47  lea r8,[rbp+0x480]
0x4c88a4e  mov rcx,r14
0x4c88a51  mov rdx,r15
0x4c88a54  xor r9d,r9d
0x4c88a57  call 0x541F8F0
0x4c88a5c  nop
0x4c88a5d  cmp r13,r15
0x4c88a60  je 0x4C88AF9
0x4c88a66  movaps xmm0,[rbp+0x400]
0x4c88a6d  xorps xmm6,xmm6
0x4c88a70  movaps [rbp+0x400],xmm6
0x4c88a77  mov r14,[rbx+0x68]
0x4c88a7b  movups [rbx+0x60],xmm0
0x4c88a7f  test r14,r14
0x4c88a82  je short 0x4C88AB1
0x4c88a84  lock dec dword ptr [r14+8]
0x4c88a89  jne short 0x4C88AB1
0x4c88a8b  mov rax,[r14]
0x4c88a8e  mov rax,[rax]
```

#### 0x4c88a91..0x4c88b29: Finish releasing the old [rbx+0x60] pair: on refcount zero destroy the object via vtable slot 0 (CFG call), then lock dec [r14+0xC] and, on zero, free via vtable slot +8. Same swap-and-release for the second member: [rbp+0x410] → [rbx+0x70], old [rbx+0x78] released.
```
0x4c88a91  mov rcx,r14
0x4c88a94  call qword ptr [0xF99FFA0]
0x4c88a9a  lock dec dword ptr [r14+0xC]
0x4c88a9f  jne short 0x4C88AB1
0x4c88aa1  mov rax,[r14]
0x4c88aa4  mov rax,[rax+8]
0x4c88aa8  mov rcx,r14
0x4c88aab  call qword ptr [0xF99FFA0]
0x4c88ab1  movaps xmm0,[rbp+0x410]
0x4c88ab8  movaps [rbp+0x410],xmm6
0x4c88abf  mov r14,[rbx+0x78]
0x4c88ac3  movups [rbx+0x70],xmm0
0x4c88ac7  test r14,r14
0x4c88aca  je short 0x4C88AF9
0x4c88acc  lock dec dword ptr [r14+8]
0x4c88ad1  jne short 0x4C88AF9
0x4c88ad3  mov rax,[r14]
0x4c88ad6  mov rax,[rax]
0x4c88ad9  mov rcx,r14
0x4c88adc  call qword ptr [0xF99FFA0]
0x4c88ae2  lock dec dword ptr [r14+0xC]
0x4c88ae7  jne short 0x4C88AF9
0x4c88ae9  mov rax,[r14]
0x4c88aec  mov rax,[rax+8]
0x4c88af0  mov rcx,r14
0x4c88af3  call qword ptr [0xF99FFA0]
0x4c88af9  mov r14,[rbp+0x418]
0x4c88b00  test r14,r14
0x4c88b03  je short 0x4C88B32
0x4c88b05  lock dec dword ptr [r14+8]
0x4c88b0a  jne short 0x4C88B32
0x4c88b0c  mov rax,[r14]
0x4c88b0f  mov rax,[rax]
0x4c88b12  mov rcx,r14
0x4c88b15  call qword ptr [0xF99FFA0]
0x4c88b1b  lock dec dword ptr [r14+0xC]
0x4c88b20  jne short 0x4C88B32
0x4c88b22  mov rax,[r14]
0x4c88b25  mov rax,[rax+8]
0x4c88b29  mov rcx,r14
```

#### 0x4c88b2c..0x4c88bc1: Release the second saved local [rbp+0x408] with the same destroy/free pattern, then the capacity check of the temporary string in [rbp+0x480] ([rbp+0x4A0] vs the 0x10 SSO threshold): if heap-allocated, read the allocation header ([rcx-8]) and deallocate via 0xE935700. Then start releasing [rbp+0x570] (lock dec [r14+8]).
```
0x4c88b2c  call qword ptr [0xF99FFA0]
0x4c88b32  mov r14,[rbp+0x408]
0x4c88b39  test r14,r14
0x4c88b3c  je short 0x4C88B6B
0x4c88b3e  lock dec dword ptr [r14+8]
0x4c88b43  jne short 0x4C88B6B
0x4c88b45  mov rax,[r14]
0x4c88b48  mov rax,[rax]
0x4c88b4b  mov rcx,r14
0x4c88b4e  call qword ptr [0xF99FFA0]
0x4c88b54  lock dec dword ptr [r14+0xC]
0x4c88b59  jne short 0x4C88B6B
0x4c88b5b  mov rax,[r14]
0x4c88b5e  mov rax,[rax+8]
0x4c88b62  mov rcx,r14
0x4c88b65  call qword ptr [0xF99FFA0]
0x4c88b6b  mov rax,[rbp+0x4A0]
0x4c88b72  cmp rax,0x10
0x4c88b76  jb short 0x4C88BB0
0x4c88b78  mov rcx,[rbp+0x488]
0x4c88b7f  lea rdx,[rax+1]
0x4c88b83  cmp rdx,0x1000
0x4c88b8a  jb short 0x4C88BAB
0x4c88b8c  mov r8,[rcx-8]
0x4c88b90  add rcx,0xFFFFFFFFFFFFFFF8
0x4c88b94  sub rcx,r8
0x4c88b97  cmp rcx,0x20
0x4c88b9b  jae 0x4C89867
0x4c88ba1  add rax,0x28
0x4c88ba5  mov rdx,rax
0x4c88ba8  mov rcx,r8
0x4c88bab  call 0xE935700
0x4c88bb0  mov r14,[rbp+0x570]
0x4c88bb7  test r14,r14
0x4c88bba  je short 0x4C88BE9
0x4c88bbc  lock dec dword ptr [r14+8]
0x4c88bc1  jne short 0x4C88BE9
```

#### 0x4c88bc3..0x4c88c87: Finish the [rbp+0x570] release; merge point 0x4C88BED: rax=[r13] (the rbx+0x60 pair) or fallback singleton 0x129C1210 when null; if [rax]==0 exit via 0x4C88FB8. Virtual-call slot +0x100 of [rsi] into [rbp+0x670], require non-null and byte==1 else exit via 0x4C88F35; virtual-call slots +0xF0 (→r15) and +0x5C8 (→[rbp+0x708]) with null checks guarded by 0xDEADC0DE traps.
```
0x4c88bc3  mov rax,[r14]
0x4c88bc6  mov rax,[rax]
0x4c88bc9  mov rcx,r14
0x4c88bcc  call qword ptr [0xF99FFA0]
0x4c88bd2  lock dec dword ptr [r14+0xC]
0x4c88bd7  jne short 0x4C88BE9
0x4c88bd9  mov rax,[r14]
0x4c88bdc  mov rax,[rax+8]
0x4c88be0  mov rcx,r14
0x4c88be3  call qword ptr [0xF99FFA0]
0x4c88be9  mov rax,[r13]
0x4c88bed  test rax,rax
0x4c88bf0  lea r14,[0x129C1210]
0x4c88bf7  cmove rax,r14
0x4c88bfb  cmp qword ptr [rax],0
0x4c88bff  je 0x4C88FB8
0x4c88c05  mov rax,[rsi]
0x4c88c08  mov rax,[rax+0x100]
0x4c88c0f  lea rdx,[rbp+0x670]
0x4c88c16  mov rcx,rsi
0x4c88c19  call qword ptr [0xF99FFA0]
0x4c88c1f  mov rax,[rbp+0x670]
0x4c88c26  test rax,rax
0x4c88c29  je 0x4C88F35
0x4c88c2f  cmp byte ptr [rax],1
0x4c88c32  jne 0x4C88F35
0x4c88c38  mov rax,[rsi]
0x4c88c3b  mov rax,[rax+0xF0]
0x4c88c42  mov rcx,rsi
0x4c88c45  call qword ptr [0xF99FFA0]
0x4c88c4b  nop
0x4c88c4c  mov r15,rax
0x4c88c4f  test rax,rax
0x4c88c52  je 0x4C88F35
0x4c88c58  mov rax,[rsi]
0x4c88c5b  mov rax,[rax+0x5C8]
0x4c88c62  mov rcx,rsi
0x4c88c65  call qword ptr [0xF99FFA0]
0x4c88c6b  mov [rbp+0x708],rax
0x4c88c72  cmp qword ptr [rbp+0x708],0
0x4c88c7a  je 0x4C88F35
0x4c88c80  mov rax,[rbp+0x670]
0x4c88c87  test rax,rax
```

#### 0x4c88c8a..0x4c88d2d: Assert byte [[rbp+0x670]]!=0 (else trap 0xDEADC0DE); virtual-call [rbp+0x680] vptr slot +0x28, then 0x4C8A340 → r12, require non-null, require [r12] slot +0x30 to return false (al==0), and slot +0x18 fills [rbp+0x618] (list out). Store r15 to [rbp+0x5E8], increment [rbx+0x48]; load [rdi+0x10], read its +0x74 byte clamped <4 to index the float array at +0x120 (xmm0), and bulk-load r8d=[rax], r15d=[rax+4], r10=[rax+0x100], r11=[rax+0xF8], r9=[rax+0xB0], rcx=[rax+0xA8].
```
0x4c88c8a  jne short 0x4C88C97
0x4c88c8c  mov dword ptr [0],0xDEADC0DE
0x4c88c97  cmp byte ptr [rax],0
0x4c88c9a  jne short 0x4C88CA7
0x4c88c9c  mov dword ptr [0],0xDEADC0DE
0x4c88ca7  mov rcx,[rbp+0x680]
0x4c88cae  mov rax,[rcx]
0x4c88cb1  mov rax,[rax+0x28]
0x4c88cb5  call qword ptr [0xF99FFA0]
0x4c88cbb  nop
0x4c88cbc  mov rcx,rax
0x4c88cbf  call 0x4C8A340
0x4c88cc4  nop
0x4c88cc5  mov r12,rax
0x4c88cc8  test rax,rax
0x4c88ccb  je 0x4C88F35
0x4c88cd1  mov rax,[r12]
0x4c88cd5  mov rax,[rax+0x30]
0x4c88cd9  mov rcx,r12
0x4c88cdc  call qword ptr [0xF99FFA0]
0x4c88ce2  nop
0x4c88ce3  test al,al
0x4c88ce5  jne 0x4C88F35
0x4c88ceb  mov rax,[r12]
0x4c88cef  mov rax,[rax+0x18]
0x4c88cf3  lea rdx,[rbp+0x618]
0x4c88cfa  mov rcx,r12
0x4c88cfd  call qword ptr [0xF99FFA0]
0x4c88d03  nop
0x4c88d04  mov [rbp+0x5E8],r15
0x4c88d0b  inc qword ptr [rbx+0x48]
0x4c88d0f  mov rax,[rdi+0x10]
0x4c88d13  mov ecx,[rax+0x74]
0x4c88d16  xor edx,edx
0x4c88d18  cmp cl,4
0x4c88d1b  cmovae ecx,edx
0x4c88d1e  movzx ecx,cl
0x4c88d21  movss xmm0,[rax+rcx*4+0x120]
0x4c88d2a  mov r8d,[rax]
0x4c88d2d  mov r15d,[rax+4]
```

#### 0x4c88d31..0x4c88e0d: Zero [rbp+0x480]; build a refcounted triple from [rax+0x90]/[rax+0x98] (addref via lock inc [ctl+8])/[rax+0xA0]; fatal 0x4C89862 if the +0x90 pointer is null or its byte is 0. Spill the stack args (rax+0xB8, rax+0xD0, [rax+0x88], rax+0x10, xmm0, r15d, r8d) and call 0x56FFD0 (rcx=[rbp-0x10] string, r8=[rbp+0x480], r9=[rbp+0x6D0]); then [rbp+0x65]=0, [rbp+0x6A]=1, and copy byte [rax+0x74] → [rbp+0x64].
```
0x4c88d31  mov r10,[rax+0x100]
0x4c88d38  mov r11,[rax+0xF8]
0x4c88d3f  mov r9,[rax+0xB0]
0x4c88d46  mov rcx,[rax+0xA8]
0x4c88d4d  mov [rbp+0x6D0],rcx
0x4c88d54  xorps xmm1,xmm1
0x4c88d57  movaps [rbp+0x480],xmm1
0x4c88d5e  mov r12,[rax+0x98]
0x4c88d65  test r12,r12
0x4c88d68  je short 0x4C88D77
0x4c88d6a  lock inc dword ptr [r12+8]
0x4c88d70  mov rdx,[rax+0x98]
0x4c88d77  mov r12,[rax+0x90]
0x4c88d7e  mov [rbp+0x480],r12
0x4c88d85  mov [rbp+0x488],rdx
0x4c88d8c  mov rdx,[rax+0xA0]
0x4c88d93  mov [rbp+0x490],rdx
0x4c88d9a  test r12,r12
0x4c88d9d  je 0x4C89862
0x4c88da3  cmp byte ptr [r12],0
0x4c88da8  je 0x4C89862
0x4c88dae  lea r12,[rax+0xB8]
0x4c88db5  lea rcx,[rax+0xD0]
0x4c88dbc  mov rdx,[rax+0x88]
0x4c88dc3  add rax,0x10
0x4c88dc7  movss [rsp+0x60],xmm0
0x4c88dcd  mov [rsp+0x58],r15d
0x4c88dd2  mov [rsp+0x50],r8d
0x4c88dd7  mov [rsp+0x48],rax
0x4c88ddc  mov [rsp+0x40],r10
0x4c88de1  mov [rsp+0x38],r11
0x4c88de6  mov [rsp+0x30],rcx
0x4c88deb  mov [rsp+0x28],r12
0x4c88df0  mov [rsp+0x20],r9
0x4c88df5  lea rcx,[rbp-0x10]
0x4c88df9  lea r8,[rbp+0x480]
0x4c88e00  mov r9,[rbp+0x6D0]
0x4c88e07  call 0x56FFD0
0x4c88e0c  nop
0x4c88e0d  mov byte ptr [rbp+0x65],0
```

#### 0x4c88e11..0x4c88ecd: Take the global lock object 0x128C4FD0 (enter 0xE943178, lock inc [0x128C5030], leave 0xE94319C) and read the cached pair [0x128C5038]/[0x128C5040]: if valid (byte==1, non-null) addref [rcx+8] and jump 0x4C89015, else create the pair via two 0x3B2020 calls. Release the string at [rbp-0x10] via 0x570360; then walk the vector [rbp+0x618]..[rbp+0x620] releasing each element's pointer ([rsi+8]: lock dec [ctl+0xC], destroy via [vptr+8]).
```
0x4c88e11  mov byte ptr [rbp+0x6A],1
0x4c88e15  mov rax,[rdi+0x10]
0x4c88e19  movzx eax,byte ptr [rax+0x74]
0x4c88e1d  mov [rbp+0x64],al
0x4c88e20  lea r15,[0x128C4FD0]
0x4c88e27  mov rcx,r15
0x4c88e2a  call 0xE943178
0x4c88e2f  lock inc qword ptr [0x128C5030]
0x4c88e37  mov rcx,r15
0x4c88e3a  call 0xE94319C
0x4c88e3f  mov rax,[0x128C5038]
0x4c88e46  test rax,rax
0x4c88e49  je short 0x4C88E77
0x4c88e4b  cmp byte ptr [rax],1
0x4c88e4e  jne short 0x4C88E77
0x4c88e50  mov rcx,[0x128C5040]
0x4c88e57  test rcx,rcx
0x4c88e5a  je 0x4C89012
0x4c88e60  lock inc dword ptr [rcx+8]
0x4c88e64  mov rax,[0x128C5038]
0x4c88e6b  mov r12,[0x128C5040]
0x4c88e72  jmp 0x4C89015
0x4c88e77  mov qword ptr [rbp+0x6A0],0
0x4c88e82  mov byte ptr [rbp+0x6A8],0
0x4c88e89  lea rcx,[0x128C4FD0]
0x4c88e90  call 0x3B2020
0x4c88e95  cmp byte ptr [rbp+0x6A8],1
0x4c88e9c  jne short 0x4C88EAA
0x4c88e9e  mov rcx,[rbp+0x6A0]
0x4c88ea5  call 0x3B2020
0x4c88eaa  lea rcx,[rbp-0x10]
0x4c88eae  call 0x570360
0x4c88eb3  mov rsi,[rbp+0x618]
0x4c88eba  test rsi,rsi
0x4c88ebd  je short 0x4C88F35
0x4c88ebf  mov rdi,[rbp+0x620]
0x4c88ec6  cmp rsi,rdi
0x4c88ec9  jne short 0x4C88ED9
0x4c88ecb  jmp short 0x4C88EFE
0x4c88ecd  nop [rax]
```

#### 0x4c88ed0..0x4c88f64: Vector element walk continues: each element rcx=[rsi+8] is released via lock dec [rcx+0xC] (on zero destroy via vptr then free via [vptr+8]); at walk end deallocate the vector buffer (size guards 0x1000/0x20, allocation header [rsi-8]) via 0xE935700. Exit path 0x4C88F35: zero the [rbp+0x670] pair with movups and release [rbp+0x678] (destroy via [vptr], free via [vptr+8]).
```
0x4c88ed0  add rsi,0x10
0x4c88ed4  cmp rsi,rdi
0x4c88ed7  je short 0x4C88EF7
0x4c88ed9  mov rcx,[rsi+8]
0x4c88edd  test rcx,rcx
0x4c88ee0  je short 0x4C88ED0
0x4c88ee2  lock dec dword ptr [rcx+0xC]
0x4c88ee6  jne short 0x4C88ED0
0x4c88ee8  mov rax,[rcx]
0x4c88eeb  mov rax,[rax+8]
0x4c88eef  call qword ptr [0xF99FFA0]
0x4c88ef5  jmp short 0x4C88ED0
0x4c88ef7  mov rsi,[rbp+0x618]
0x4c88efe  mov rdx,[rbp+0x628]
0x4c88f05  sub rdx,rsi
0x4c88f08  cmp rdx,0x1000
0x4c88f0f  jb short 0x4C88F2D
0x4c88f11  mov rax,[rsi-8]
0x4c88f15  add rsi,0xFFFFFFFFFFFFFFF8
0x4c88f19  sub rsi,rax
0x4c88f1c  cmp rsi,0x20
0x4c88f20  jae 0x4C89867
0x4c88f26  add rdx,0x27
0x4c88f2a  mov rsi,rax
0x4c88f2d  mov rcx,rsi
0x4c88f30  call 0xE935700
0x4c88f35  xorps xmm0,xmm0
0x4c88f38  mov rsi,[rbp+0x678]
0x4c88f3f  movups [rbp+0x670],xmm0
0x4c88f46  test rsi,rsi
0x4c88f49  je short 0x4C88FB8
0x4c88f4b  lock dec dword ptr [rsi+8]
0x4c88f4f  jne short 0x4C88F76
0x4c88f51  mov rax,[rsi]
0x4c88f54  mov rax,[rax]
0x4c88f57  mov rcx,rsi
0x4c88f5a  call qword ptr [0xF99FFA0]
0x4c88f60  lock dec dword ptr [rsi+0xC]
0x4c88f64  jne short 0x4C88F76
```

#### 0x4c88f66..0x4c89015: Finish releasing the [rbp+0x680] pair member, then early-out epilogue at 0x4C88FB8 (restore xmm6-xmm14, add rsp 0x838, pop the 8 GPRs, ret). 0x4C89012 xor r12d,r12d (null cached control block); 0x4C89015 cache-fill start: rcx=[0x128C5048] (holder pointer [I]); the cached-pair stores continue at 0x4c8901c in the next phase.
```
0x4c88f66  mov rax,[rsi]
0x4c88f69  mov rax,[rax+8]
0x4c88f6d  mov rcx,rsi
0x4c88f70  call qword ptr [0xF99FFA0]
0x4c88f76  mov rsi,[rbp+0x678]
0x4c88f7d  mov qword ptr [rbp+0x680],0
0x4c88f88  test rsi,rsi
0x4c88f8b  je short 0x4C88FB8
0x4c88f8d  lock dec dword ptr [rsi+8]
0x4c88f91  jne short 0x4C88FB8
0x4c88f93  mov rax,[rsi]
0x4c88f96  mov rax,[rax]
0x4c88f99  mov rcx,rsi
0x4c88f9c  call qword ptr [0xF99FFA0]
0x4c88fa2  lock dec dword ptr [rsi+0xC]
0x4c88fa6  jne short 0x4C88FB8
0x4c88fa8  mov rax,[rsi]
0x4c88fab  mov rax,[rax+8]
0x4c88faf  mov rcx,rsi
0x4c88fb2  call qword ptr [0xF99FFA0]
0x4c88fb8  movaps xmm6,[rbp+0x720]
0x4c88fbf  movaps xmm7,[rbp+0x730]
0x4c88fc6  movaps xmm8,[rbp+0x740]
0x4c88fce  movaps xmm9,[rbp+0x750]
0x4c88fd6  movaps xmm10,[rbp+0x760]
0x4c88fde  movaps xmm11,[rbp+0x770]
0x4c88fe6  movaps xmm12,[rbp+0x780]
0x4c88fee  movaps xmm13,[rbp+0x790]
0x4c88ff6  movaps xmm14,[rbp+0x7A0]
0x4c88ffe  add rsp,0x838
0x4c89005  pop rbx
0x4c89006  pop rdi
0x4c89007  pop rsi
0x4c89008  pop r12
0x4c8900a  pop r13
0x4c8900c  pop r14
0x4c8900e  pop r15
0x4c89010  pop rbp
0x4c89011  ret
0x4c89012  xor r12d,r12d
0x4c89015  mov rcx,[0x128C5048]
```

#### 0x4c8901c..0x4c890ef: Fill the static cache pair: [rbp+0x6A0]=r15, byte [rbp+0x6A8]=1, [rbp+0x6B0]=rax, [rbp+0x6B8]=r12, [rbp+0x6C0]=rcx; validate rax (non-null, byte==1, else exit via 0x4C897C8) and virtual-call its vptr slot +8 → test al. Via [rbp+0x708]: rcx=[rax+0x418], virtual-call vptr slot +0x270 → rax, rcx=[rax], r8=[rcx+0x230], rdx=[rbp+0x548], CFG call; copy al=byte [[rbp+0x708]+0x4B4] → [rbp+0x560]; loop prep: r15=[rbp+0x618], [rbp+0x6D0]=[rbp+0x620], SIMD consts xmm9=0, xmm10=all-ones (pcmpeqd), xmm11=[0xEF3F050], xmm12=[0xF20A380], xmm13=[0xF0922E0]; jmp short 0x4C890F5.
```
0x4c8901c  mov [rbp+0x6A0],r15
0x4c89023  mov byte ptr [rbp+0x6A8],1
0x4c8902a  mov [rbp+0x6B0],rax
0x4c89031  mov [rbp+0x6B8],r12
0x4c89038  mov [rbp+0x6C0],rcx
0x4c8903f  test rax,rax
0x4c89042  je 0x4C897C8
0x4c89048  cmp byte ptr [rax],1
0x4c8904b  jne 0x4C897C8
0x4c89051  mov rax,[rcx]
0x4c89054  mov rax,[rax+8]
0x4c89058  call qword ptr [0xF99FFA0]
0x4c8905e  nop
0x4c8905f  test al,al
0x4c89061  je 0x4C897C8
0x4c89067  mov rax,[rbp+0x708]
0x4c8906e  mov rcx,[rax+0x418]
0x4c89075  mov rax,[rcx]
0x4c89078  mov rax,[rax+0x270]
0x4c8907f  call qword ptr [0xF99FFA0]
0x4c89085  nop
0x4c89086  mov rcx,[rax]
0x4c89089  mov r8,[rcx+0x230]
0x4c89090  lea rdx,[rbp+0x548]
0x4c89097  mov rcx,rax
0x4c8909a  mov rax,r8
0x4c8909d  call qword ptr [0xF99FFA0]
0x4c890a3  nop
0x4c890a4  mov rax,[rbp+0x708]
0x4c890ab  movzx eax,byte ptr [rax+0x4B4]
0x4c890b2  mov [rbp+0x560],al
0x4c890b8  mov r15,[rbp+0x618]
0x4c890bf  mov rax,[rbp+0x620]
0x4c890c6  mov [rbp+0x6D0],rax
0x4c890cd  xorps xmm9,xmm9
0x4c890d1  pcmpeqd xmm10,xmm10
0x4c890d6  movdqa xmm11,[0xEF3F050]
0x4c890df  movaps xmm12,[0xF20A380]
0x4c890e7  movaps xmm13,[0xF0922E0]
0x4c890ef  jmp short 0x4C890F5
```

#### 0x4c890f1..0x4c89199: Loop head 0x4C890F1 (add r15,0x10); body: exit loop when r15==[rbp+0x6D0] → 0x4C897B5; zero [rbp+0x600] with xmm9; addref r15's control block (rcx=[r15+8]; test/addref loop: eax=[rcx+8], lea edx,[rax+1], lock cmpxchg [rcx+8],edx) and copy the pair: movups [r15]→xmm0, r12=[r15], movaps [rbp+0x600],xmm0; null element → 0x4C89767. Chain walk [r12+8]→[rax+8] vptr call stores the fetched value to [rbx+0x40]; r12=[r12+0x60]; require 0x6C96D40(r12) returns al!=0 and byte [r12+0x20]==1 (else 0x4C89767); vptr slot +0x10 → rcx=r12 for the next CFG call.
```
0x4c890f1  add r15,0x10
0x4c890f5  cmp r15,[rbp+0x6D0]
0x4c890fc  je 0x4C897B5
0x4c89102  movaps [rbp+0x600],xmm9
0x4c8910a  mov rcx,[r15+8]
0x4c8910e  test rcx,rcx
0x4c89111  je short 0x4C890F1
0x4c89113  mov eax,[rcx+8]
0x4c89116  nop [rax+rax]
0x4c89120  test eax,eax
0x4c89122  je short 0x4C8913E
0x4c89124  lea edx,[rax+1]
0x4c89127  lock cmpxchg [rcx+8],edx
0x4c8912c  jne short 0x4C89120
0x4c8912e  movups xmm0,[r15]
0x4c89132  mov r12,[r15]
0x4c89135  movaps [rbp+0x600],xmm0
0x4c8913c  jmp short 0x4C89145
0x4c8913e  mov r12,[rbp+0x600]
0x4c89145  test r12,r12
0x4c89148  je 0x4C89767
0x4c8914e  lea rcx,[r12+8]
0x4c89153  mov rax,[r12+8]
0x4c89158  mov rax,[rax+8]
0x4c8915c  call qword ptr [0xF99FFA0]
0x4c89162  nop
0x4c89163  mov [rbx+0x40],rax
0x4c89167  mov r12,[r12+0x60]
0x4c8916c  test r12,r12
0x4c8916f  je 0x4C89767
0x4c89175  mov rcx,r12
0x4c89178  call 0x6C96D40
0x4c8917d  test al,al
0x4c8917f  je 0x4C89767
0x4c89185  cmp byte ptr [r12+0x20],1
0x4c8918b  jne 0x4C89767
0x4c89191  mov rax,[r12]
0x4c89195  mov rax,[rax+0x10]
0x4c89199  mov rcx,r12
```

#### 0x4c8919c..0x4c8925e: Store the slot +0x10 result: [rbp+0x710]=rax; vptr slot +0x58 call with rdx=[rbp+0x480]; then rcx=[r12+8], rax=[rcx+8], rcx+=8, vptr slot +0x18 CFG call with rdx=[rbp+0x400], r8=[rbp+0x480]; recheck byte [r12+0x20]==1 (else 0x4C8975B); rax=[r12+0x60]→[rbp+0x6F0], require non-null and [r12+0x68]!=0 (else 0x4C8975B). Load floats of [rbp+0x710]: xmm8=[rax+8], xmm6=[rax], xmm7=[rax+4]; call 0x7789400 (rcx=[rbp+0x400], rdx=[rbp+0x688]); floor each via 0xEEC75A0 + cvttss2si (xmm8→[rbp+0x710]; xmm7 and xmm6 follow).
```
0x4c8919c  call qword ptr [0xF99FFA0]
0x4c891a2  mov [rbp+0x710],rax
0x4c891a9  mov rax,[r12]
0x4c891ad  mov rax,[rax+0x58]
0x4c891b1  mov rcx,r12
0x4c891b4  lea rdx,[rbp+0x480]
0x4c891bb  call qword ptr [0xF99FFA0]
0x4c891c1  nop
0x4c891c2  mov rcx,[r12+8]
0x4c891c7  mov rax,[rcx+8]
0x4c891cb  add rcx,8
0x4c891cf  mov rax,[rax+0x18]
0x4c891d3  lea rdx,[rbp+0x400]
0x4c891da  lea r8,[rbp+0x480]
0x4c891e1  call qword ptr [0xF99FFA0]
0x4c891e7  nop
0x4c891e8  cmp byte ptr [r12+0x20],1
0x4c891ee  jne 0x4C8975B
0x4c891f4  mov rax,[r12+0x60]
0x4c891f9  mov [rbp+0x6F0],rax
0x4c89200  test rax,rax
0x4c89203  je 0x4C8975B
0x4c89209  cmp qword ptr [r12+0x68],0
0x4c8920f  je 0x4C8975B
0x4c89215  mov rax,[rbp+0x710]
0x4c8921c  movss xmm8,[rax+8]
0x4c89222  movss xmm6,[rax]
0x4c89226  movss xmm7,[rax+4]
0x4c8922b  lea rcx,[rbp+0x400]
0x4c89232  lea rdx,[rbp+0x688]
0x4c89239  call 0x7789400
0x4c8923e  nop
0x4c8923f  movaps xmm0,xmm8
0x4c89243  call 0xEEC75A0
0x4c89248  cvttss2si eax,xmm0
0x4c8924c  mov [rbp+0x710],rax
0x4c89253  movaps xmm0,xmm7
0x4c89256  call 0xEEC75A0
0x4c8925b  movaps xmm7,xmm0
0x4c8925e  movaps xmm0,xmm6
```

#### 0x4c89261..0x4c8932f: Finish the xmm6 floor; accumulate: eax=[rbp+0x690], ecx=[rbp+0x69C], r8=[rbp+0x710]; edx=eax+r8d → [rbp+0x6D8]+[rbp+0x690]; r8d+=ecx → [rbp+0x69C]; rdx=[[rbp+0x708]+0x480]; xmm6=[rdx+0x654]. Pack the floored ints: unpcklps xmm0,xmm7, cvttps2dq, movq loads of [rbp+0x688]/[rbp+0x694] with paddd stored back; xmm7=two floats [rdx+0x64C] (movsd); build the delta vector (movd/punpcklqdq/shufps 0x84 chains, psubd, psubd xmm0,xmm10, cvtdq2ps, pxor xmm2,xmm11 sign mask, pcmpeqd/pcmpgtd, shufps 0x23/0x24, andnps) → [rbp+0x650].
```
0x4c89261  call 0xEEC75A0
0x4c89266  mov eax,[rbp+0x690]
0x4c8926c  mov ecx,[rbp+0x69C]
0x4c89272  mov r8,[rbp+0x710]
0x4c89279  lea edx,[rax+r8]
0x4c8927d  mov [rbp+0x6D8],edx
0x4c89283  mov [rbp+0x690],edx
0x4c89289  add r8d,ecx
0x4c8928c  mov [rbp+0x69C],r8d
0x4c89293  mov rdx,[rbp+0x708]
0x4c8929a  mov rdx,[rdx+0x480]
0x4c892a1  movss xmm6,[rdx+0x654]
0x4c892a9  unpcklps xmm0,xmm7
0x4c892ac  cvttps2dq xmm0,xmm0
0x4c892b0  movq xmm1,[rbp+0x688]
0x4c892b8  movdqa xmm8,xmm1
0x4c892bd  paddd xmm8,xmm0
0x4c892c2  movq [rbp+0x688],xmm8
0x4c892cb  movq xmm2,[rbp+0x694]
0x4c892d3  paddd xmm0,xmm2
0x4c892d7  movq [rbp+0x694],xmm0
0x4c892df  movsd xmm7,[rdx+0x64C]
0x4c892e7  movd xmm0,ecx
0x4c892eb  punpcklqdq xmm0,xmm2
0x4c892ef  shufps xmm2,xmm0,0x84
0x4c892f3  movd xmm0,eax
0x4c892f7  punpcklqdq xmm0,xmm1
0x4c892fb  shufps xmm1,xmm0,0x84
0x4c892ff  psubd xmm2,xmm1
0x4c89303  movdqa xmm0,xmm2
0x4c89307  psubd xmm0,xmm10
0x4c8930c  cvtdq2ps xmm1,xmm0
0x4c8930f  pxor xmm2,xmm11
0x4c89314  pcmpeqd xmm3,xmm3
0x4c89318  pcmpgtd xmm3,xmm2
0x4c8931c  pxor xmm2,xmm2
0x4c89320  pcmpgtd xmm2,xmm0
0x4c89324  shufps xmm2,xmm3,0x23
0x4c89328  shufps xmm3,xmm2,0x24
0x4c8932c  andnps xmm3,xmm1
0x4c8932f  movaps [rbp+0x650],xmm3
```

#### 0x4c89336..0x4c89415: Clamp and copy: shufps xmm1,xmm1,0xE9, xorps xmm0, maxps → movlps [rbp+0x660]; [rbp+0x660]→[rbp+0x5D0], [rbp+0x650]→[rbp+0x5C0]; movups [r12+0x74]→[rbp+0x470] (movaps store); [r12+0x8C]→[rbp+0x648], rax=[r12+0x84]→[rbp+0x640], xmm14=[r12+0x90]; repeat into [rbp+0x638]/[rbp+0x630]; rdx=[r13] with cmove fallback r14; r12=lea [rbp+0x480]; call 0x4C74180 (rcx=r12) and 0x4DFB570 (rcx=[rbp+0x568], rdx=r12); dword [rbp+0x578]=1; build the 0x28-byte record at [rbp+0x57C]: eax=[rbp+0x638]→[rcx+8], rax=[rbp+0x630]→[rcx], movss [rbp+0x588]=xmm14, eax=[rbp+0x648]→[rcx+0x18], rax=[rbp+0x640]→[rcx+0x10].
```
0x4c89336  shufps xmm1,xmm1,0xE9
0x4c8933a  xorps xmm0,xmm0
0x4c8933d  maxps xmm0,xmm1
0x4c89340  movlps [rbp+0x660],xmm0
0x4c89347  mov rax,[rbp+0x660]
0x4c8934e  mov [rbp+0x5D0],rax
0x4c89355  movaps xmm0,[rbp+0x650]
0x4c8935c  movaps [rbp+0x5C0],xmm0
0x4c89363  movups xmm0,[r12+0x74]
0x4c89369  movaps [rbp+0x470],xmm0
0x4c89370  mov eax,[r12+0x8C]
0x4c89378  mov [rbp+0x648],eax
0x4c8937e  mov rax,[r12+0x84]
0x4c89386  mov [rbp+0x640],rax
0x4c8938d  movss xmm14,[r12+0x90]
0x4c89397  mov eax,[r12+0x8C]
0x4c8939f  mov [rbp+0x638],eax
0x4c893a5  mov rax,[r12+0x84]
0x4c893ad  mov [rbp+0x630],rax
0x4c893b4  mov rdx,[r13]
0x4c893b8  test rdx,rdx
0x4c893bb  cmove rdx,r14
0x4c893bf  lea r12,[rbp+0x480]
0x4c893c6  mov rcx,r12
0x4c893c9  call 0x4C74180
0x4c893ce  nop
0x4c893cf  lea rcx,[rbp+0x568]
0x4c893d6  mov rdx,r12
0x4c893d9  call 0x4DFB570
0x4c893de  nop
0x4c893df  mov dword ptr [rbp+0x578],1
0x4c893e9  mov eax,[rbp+0x638]
0x4c893ef  lea rcx,[rbp+0x57C]
0x4c893f6  mov [rcx+8],eax
0x4c893f9  mov rax,[rbp+0x630]
0x4c89400  mov [rcx],rax
0x4c89403  movss [rbp+0x588],xmm14
0x4c8940c  mov eax,[rbp+0x648]
0x4c89412  mov [rcx+0x18],eax
0x4c89415  mov rax,[rbp+0x640]
```

#### 0x4c8941c..0x4c894d0: Finish the record: mov [rcx+0x10],rax; movss [rbp+0x598],xmm14; movaps [rbp+0x470]→xmm0, movups [rcx+0x20],xmm0; movups [rbp+0x5AC],xmm12; dword [rbp+0x5BC]=0x3F800000 (1.0f); release [rbp+0x480] via 0x7E6D0 (rcx=r12). Assert byte [[rbp+0x6B0]]==0 (test + cmp byte, trap 0xDEADC0DE if zero); then CALL THE CLONE 0x4C8A5B0 (rcx=[rbp+0x6C0], rdx=[rbp+0x568]); walk [rdi+0x10]→+0x20→+0x10→rcx=[rax+0x40]; movups [rcx],xmm13; byte [rax+0x31]=1; vptr slot +0x270 of [rsi] (rcx=rsi) → rax; call 0x57E2560 (rcx=[rbp+0x480], rdx=[rbp-0x10], r8=rsi, r9=rax); convert back: cvtsi2ss xmm0,[rbp+0x6D8], subss xmm6,xmm0; cvtdq2ps xmm0,xmm8, subps xmm7,xmm0 (position deltas [I]).
```
0x4c8941c  mov [rcx+0x10],rax
0x4c89420  movss [rbp+0x598],xmm14
0x4c89429  movaps xmm0,[rbp+0x470]
0x4c89430  movups [rcx+0x20],xmm0
0x4c89434  movups [rbp+0x5AC],xmm12
0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000
0x4c89446  mov rcx,r12
0x4c89449  call 0x7E6D0
0x4c8944e  mov rax,[rbp+0x6B0]
0x4c89455  test rax,rax
0x4c89458  je short 0x4C8946A
0x4c8945a  cmp byte ptr [rax],0
0x4c8945d  jne short 0x4C8946A
0x4c8945f  mov dword ptr [0],0xDEADC0DE
0x4c8946a  mov rcx,[rbp+0x6C0]
0x4c89471  lea rdx,[rbp+0x568]
0x4c89478  call 0x4C8A5B0
0x4c8947d  nop
0x4c8947e  mov rax,[rdi+0x10]
0x4c89482  mov rax,[rax+0x20]
0x4c89486  mov rax,[rax+0x10]
0x4c8948a  mov rcx,[rax+0x40]
0x4c8948e  movups [rcx],xmm13
0x4c89492  mov byte ptr [rax+0x31],1
0x4c89496  mov rax,[rsi]
0x4c89499  mov rax,[rax+0x270]
0x4c894a0  mov rcx,rsi
0x4c894a3  call qword ptr [0xF99FFA0]
0x4c894a9  nop
0x4c894aa  lea rcx,[rbp+0x480]
0x4c894b1  lea rdx,[rbp-0x10]
0x4c894b5  mov r8,rsi
0x4c894b8  mov r9,rax
0x4c894bb  call 0x57E2560
0x4c894c0  nop
0x4c894c1  xorps xmm0,xmm0
0x4c894c4  cvtsi2ss xmm0,dword ptr [rbp+0x6D8]
0x4c894cc  subss xmm6,xmm0
0x4c894d0  cvtdq2ps xmm0,xmm8
```

#### 0x4c894d4..0x4c895a9: subps xmm7,xmm0; byte [rbp+0x53B]=1; store results via [rbp+0x528]: movlps [rax+0x20]=xmm7, movss [rax+0x28]=xmm6; rax=[rbp+0x528]: rcx=[rbp+0x5D0]→[rax+0x48], movaps [rbp+0x5C0]→movups [rax+0x38]; rcx=[rbp+0x5E8] call 0xBA16F0; virtual-call r8=[[rax]+0x18] with rdx=[rbp+0x6CC] (rcx=rax, rax=r8); r8d=[rbp+0x6CC]; call 0x533C450 (rcx=[rbp+0x708], rdx=[rbp+0x6E0]); r12=[rbp+0x6E8]→[rbp+0x710]; if non-null: rcx=[rbp+0x6E0]→[rbp+0x6D8], lock inc [r12+0xC], release temp via 0x7E6D0, store [rbp+0x5F0]=[rbp+0x6D8], [rbp+0x5F8]=r12, lock inc [r12+0xC], jmp 0x4C895B1; else release (0x7E6D0) and movaps [rbp+0x5F0],xmm9 (zero).
```
0x4c894d4  subps xmm7,xmm0
0x4c894d7  mov byte ptr [rbp+0x53B],1
0x4c894de  mov rax,[rbp+0x528]
0x4c894e5  movlps [rax+0x20],xmm7
0x4c894e9  movss [rax+0x28],xmm6
0x4c894ee  mov rax,[rbp+0x528]
0x4c894f5  mov rcx,[rbp+0x5D0]
0x4c894fc  mov [rax+0x48],rcx
0x4c89500  movaps xmm0,[rbp+0x5C0]
0x4c89507  movups [rax+0x38],xmm0
0x4c8950b  mov rcx,[rbp+0x5E8]
0x4c89512  call 0xBA16F0
0x4c89517  mov rcx,[rax]
0x4c8951a  mov r8,[rcx+0x18]
0x4c8951e  mov rcx,rax
0x4c89521  lea rdx,[rbp+0x6CC]
0x4c89528  mov rax,r8
0x4c8952b  call qword ptr [0xF99FFA0]
0x4c89531  nop
0x4c89532  mov r8d,[rbp+0x6CC]
0x4c89539  mov rcx,[rbp+0x708]
0x4c89540  lea rdx,[rbp+0x6E0]
0x4c89547  call 0x533C450
0x4c8954c  nop
0x4c8954d  mov r12,[rbp+0x6E8]
0x4c89554  test r12,r12
0x4c89557  mov [rbp+0x710],r12
0x4c8955e  je short 0x4C8959D
0x4c89560  mov rcx,[rbp+0x6E0]
0x4c89567  mov [rbp+0x6D8],rcx
0x4c8956e  lock inc dword ptr [r12+0xC]
0x4c89574  lea rcx,[rbp+0x6E0]
0x4c8957b  call 0x7E6D0
0x4c89580  mov rax,[rbp+0x6D8]
0x4c89587  mov [rbp+0x5F0],rax
0x4c8958e  mov [rbp+0x5F8],r12
0x4c89595  lock inc dword ptr [r12+0xC]
0x4c8959b  jmp short 0x4C895B1
0x4c8959d  lea rcx,[rbp+0x6E0]
0x4c895a4  call 0x7E6D0
0x4c895a9  movaps [rbp+0x5F0],xmm9
```

#### 0x4c895b1..0x4c89670: Call 0x4C8A770 (rcx=rbx, rdx=[rbp+0x548], r8=[rbp+0x6F0], r9=[[rbp+0x4A8]+0xB0], [rsp+0x20]=[rbp+0x5F0], [rsp+0x28]=[rbp+0x650]); call 0x5AC20A0 (rcx=[rbp+8]+0x40, rdx=[rbp+0x6E0], r8d=0) and set byte [[rbp+0x6E0]+0x38]=1; zero the pair [rbp+0x6F8]/[rbp+0x700] via xorps xmm6/xmm7 against xmm11 (movlps/movss stores); r12=lea [rbp+0x6F8]; call 0x4C8A9F0 (rcx=[rbp+0x6E8], rdx=r12); clamp al=[rbp+0x64] to <4 (cmp/mov ecx,0/cmovae); rcx=[[rbp+0x708]+0x480]; movss xmm2,[rbp+rax*4+0x110] (indexed float table); rdx=[rbp+8]; call 0x53B3600; zero [rbp+0x6F8] again.
```
0x4c895b1  mov rax,[rbp+0x4A8]
0x4c895b8  mov r9,[rax+0xB0]
0x4c895bf  lea rax,[rbp+0x650]
0x4c895c6  mov [rsp+0x28],rax
0x4c895cb  lea rax,[rbp+0x5F0]
0x4c895d2  mov [rsp+0x20],rax
0x4c895d7  mov rcx,rbx
0x4c895da  lea rdx,[rbp+0x548]
0x4c895e1  mov r8,[rbp+0x6F0]
0x4c895e8  call 0x4C8A770
0x4c895ed  nop
0x4c895ee  mov rcx,[rbp+8]
0x4c895f2  add rcx,0x40
0x4c895f6  lea rdx,[rbp+0x6E0]
0x4c895fd  xor r8d,r8d
0x4c89600  call 0x5AC20A0
0x4c89605  nop
0x4c89606  mov rax,[rbp+0x6E0]
0x4c8960d  mov byte ptr [rax+0x38],1
0x4c89611  mov rcx,[rbp+0x6E8]
0x4c89618  xorps xmm6,xmm11
0x4c8961c  xorps xmm7,xmm11
0x4c89620  movlps [rbp+0x6F8],xmm7
0x4c89627  movss [rbp+0x700],xmm6
0x4c8962f  lea r12,[rbp+0x6F8]
0x4c89636  mov rdx,r12
0x4c89639  call 0x4C8A9F0
0x4c8963e  nop
0x4c8963f  mov eax,[rbp+0x64]
0x4c89642  cmp al,4
0x4c89644  mov ecx,0
0x4c89649  cmovae eax,ecx
0x4c8964c  mov rcx,[rbp+0x708]
0x4c89653  mov rcx,[rcx+0x480]
0x4c8965a  movzx eax,al
0x4c8965d  movss xmm2,[rbp+rax*4+0x110]
0x4c89666  mov rdx,[rbp+8]
0x4c8966a  call 0x53B3600
0x4c8966f  nop
0x4c89670  mov qword ptr [rbp+0x6F8],0
```

#### 0x4c8967b..0x4c8974f: Zero [rbp+0x700]; call 0x4C8AA30 (rcx=rbx, rdx=[rbp+0x480], r8=[rbp+0x6F0], r9=[rbp+0x650], [rsp+0x20]=r12); zero the pair again; call 0x4C8CE50 (rcx=[rbp+0x480], rdx=[rbp+0x6F0], r8=[rbp+0x650], r9=r12) with byte [rsp+0x20]=0; zero again; call 0x4C8CE50 again with byte [rsp+0x20]=1; call 0x5AC23D0 ([rbp+0x6E0]); release [rbp+0x710] (lock dec [rcx+0xC], on zero destroy via [vptr+8]); call 0x57E29E0 ([rbp+0x480]); call 0x7E6D0 ([rbp+0x568]).
```
0x4c8967b  mov dword ptr [rbp+0x700],0
0x4c89685  mov [rsp+0x20],r12
0x4c8968a  mov rcx,rbx
0x4c8968d  lea rdx,[rbp+0x480]
0x4c89694  mov r8,[rbp+0x6F0]
0x4c8969b  lea r9,[rbp+0x650]
0x4c896a2  call 0x4C8AA30
0x4c896a7  nop
0x4c896a8  mov qword ptr [rbp+0x6F8],0
0x4c896b3  mov dword ptr [rbp+0x700],0
0x4c896bd  mov byte ptr [rsp+0x20],0
0x4c896c2  lea rcx,[rbp+0x480]
0x4c896c9  mov rdx,[rbp+0x6F0]
0x4c896d0  lea r8,[rbp+0x650]
0x4c896d7  mov r9,r12
0x4c896da  call 0x4C8CE50
0x4c896df  nop
0x4c896e0  mov qword ptr [rbp+0x6F8],0
0x4c896eb  mov dword ptr [rbp+0x700],0
0x4c896f5  mov byte ptr [rsp+0x20],1
0x4c896fa  lea rcx,[rbp+0x480]
0x4c89701  mov rdx,[rbp+0x6F0]
0x4c89708  lea r8,[rbp+0x650]
0x4c8970f  mov r9,r12
0x4c89712  call 0x4C8CE50
0x4c89717  nop
0x4c89718  lea rcx,[rbp+0x6E0]
0x4c8971f  call 0x5AC23D0
0x4c89724  mov rcx,[rbp+0x710]
0x4c8972b  test rcx,rcx
0x4c8972e  je short 0x4C89743
0x4c89730  lock dec dword ptr [rcx+0xC]
0x4c89734  jne short 0x4C89743
0x4c89736  mov rax,[rcx]
0x4c89739  mov rax,[rax+8]
0x4c8973d  call qword ptr [0xF99FFA0]
0x4c89743  lea rcx,[rbp+0x480]
0x4c8974a  call 0x57E29E0
0x4c8974f  lea rcx,[rbp+0x568]
0x4c89756  call 0x7E6D0
```

#### 0x4c8975b..0x4c89816: Loop tail: call 0x73150 ([rbp+0x400]); r12=[rbp+0x608]: release the element (lock dec [r12+8] → on zero destroy via vptr; lock dec [r12+0xC] → on zero free via [vptr+8]) and jmp 0x4C890F1. Path 0x4C897B5: call 0x78CE0 ([rbp+0x548]); r12=[rbp+0x6B8]. Path 0x4C897C8: zero the [rbp+0x6B0] pair with movups; release the [rbp+0x6B8] pair (destroy/free lock dec patterns); rsi=[rbp+0x6B8]; [rbp+0x6C0]=0.
```
0x4c8975b  lea rcx,[rbp+0x400]
0x4c89762  call 0x73150
0x4c89767  mov r12,[rbp+0x608]
0x4c8976e  test r12,r12
0x4c89771  je 0x4C890F1
0x4c89777  lock dec dword ptr [r12+8]
0x4c8977d  jne 0x4C890F1
0x4c89783  mov rax,[r12]
0x4c89787  mov rax,[rax]
0x4c8978a  mov rcx,r12
0x4c8978d  call qword ptr [0xF99FFA0]
0x4c89793  lock dec dword ptr [r12+0xC]
0x4c89799  jne 0x4C890F1
0x4c8979f  mov rax,[r12]
0x4c897a3  mov rax,[rax+8]
0x4c897a7  mov rcx,r12
0x4c897aa  call qword ptr [0xF99FFA0]
0x4c897b0  jmp 0x4C890F1
0x4c897b5  lea rcx,[rbp+0x548]
0x4c897bc  call 0x78CE0
0x4c897c1  mov r12,[rbp+0x6B8]
0x4c897c8  lea rax,[rbp+0x6B0]
0x4c897cf  xorps xmm0,xmm0
0x4c897d2  movups [rax],xmm0
0x4c897d5  test r12,r12
0x4c897d8  je 0x4C88E95
0x4c897de  lock dec dword ptr [r12+8]
0x4c897e4  jne short 0x4C8980F
0x4c897e6  mov rax,[r12]
0x4c897ea  mov rax,[rax]
0x4c897ed  mov rcx,r12
0x4c897f0  call qword ptr [0xF99FFA0]
0x4c897f6  lock dec dword ptr [r12+0xC]
0x4c897fc  jne short 0x4C8980F
0x4c897fe  mov rax,[r12]
0x4c89802  mov rax,[rax+8]
0x4c89806  mov rcx,r12
0x4c89809  call qword ptr [0xF99FFA0]
0x4c8980f  mov rsi,[rbp+0x6B8]
0x4c89816  mov qword ptr [rbp+0x6C0],0
```

#### 0x4c89821..0x4c89880: Finish releasing the cached [rbp+0x6C0] pair via rsi (lock dec [rsi+8]/[rsi+0xC] destroy/free patterns) then jmp 0x4C88E95 (lock re-acquire path). Fatal tails: 0x4C89862 call 0x78ED0 (abort/fastfail [I]); 0x4C89867 report stub: qword [rsp+0x20]=0, xor ecx/edx/r8d/r9d, call [0xF9A8C78]; int3.
```
0x4c89821  test rsi,rsi
0x4c89824  je 0x4C88E95
0x4c8982a  lock dec dword ptr [rsi+8]
0x4c8982e  jne 0x4C88E95
0x4c89834  mov rax,[rsi]
0x4c89837  mov rax,[rax]
0x4c8983a  mov rcx,rsi
0x4c8983d  call qword ptr [0xF99FFA0]
0x4c89843  lock dec dword ptr [rsi+0xC]
0x4c89847  jne 0x4C88E95
0x4c8984d  mov rax,[rsi]
0x4c89850  mov rax,[rax+8]
0x4c89854  mov rcx,rsi
0x4c89857  call qword ptr [0xF99FFA0]
0x4c8985d  jmp 0x4C88E95
0x4c89862  call 0x78ED0
0x4c89867  mov qword ptr [rsp+0x20],0
0x4c89870  xor ecx,ecx
0x4c89872  xor edx,edx
0x4c89874  xor r8d,r8d
0x4c89877  xor r9d,r9d
0x4c8987a  call qword ptr [0xF9A8C78]
0x4c89880  int3
```

## Field table ([reg+off] accesses)

Excluded: rbp/rsp-relative stack slots, no-displacement [reg] forms (vptr loads like `mov rax,[rax]`), absolutes [0x...], LEAs, and the indexed [rbp+rax*4+0x110] stack table. Direction = read or store in this code.

| offset | size | dir | read/store address | verbatim sites | meaning |
|--|--|--|--|--|--|
| -0x8 | 8 | read | [rcx-8] 0x4c88b8c; [rsi-8] 0x4c88f11 | `0x4c88b8c  mov r8,[rcx-8]`<br>`0x4c88f11  mov rax,[rsi-8]` | allocation header read before deallocate (0xE935700) |
| gs:0x58 | 8 | read | gs:[0x58] 0x4c8a5dd | `0x4c8a5dd  mov rdx,gs:[0x58]` | TLS array base (clone) |
| 0x4 | 4 | read | [rcx+4] 0x4c8a5ea; [rax+4] 0x4c88d2d, 0x4c89226 | `0x4c8a5ea  cmp eax,[rcx+4]`<br>`0x4c88d2d  mov r15d,[rax+4]`<br>`0x4c89226  movss xmm7,[rax+4]` | TLS init-epoch slot vs guard 0x129C0BA0 (clone) / - / - |
| 0x8 | 4 / 8 | rw | see sites | `0x4c88a84  lock dec dword ptr [r14+8]`<br>`0x4c88acc  lock dec dword ptr [r14+8]`<br>`0x4c88b05  lock dec dword ptr [r14+8]`<br>`0x4c88b3e  lock dec dword ptr [r14+8]`<br>`0x4c88bbc  lock dec dword ptr [r14+8]`<br>`0x4c88d6a  lock inc dword ptr [r12+8]`<br>`0x4c88e60  lock inc dword ptr [rcx+8]`<br>`0x4c88ed9  mov rcx,[rsi+8]`<br>`0x4c88eeb  mov rax,[rax+8]`<br>`0x4c88f4b  lock dec dword ptr [rsi+8]`<br>`0x4c88f8d  lock dec dword ptr [rsi+8]`<br>`0x4c88fab  mov rax,[rax+8]`<br>`0x4c89054  mov rax,[rax+8]`<br>`0x4c8910a  mov rcx,[r15+8]`<br>`0x4c89113  mov eax,[rcx+8]`<br>`0x4c89127  lock cmpxchg [rcx+8],edx`<br>`0x4c89153  mov rax,[r12+8]`<br>`0x4c89158  mov rax,[rax+8]`<br>`0x4c891c2  mov rcx,[r12+8]`<br>`0x4c891c7  mov rax,[rcx+8]`<br>`0x4c8921c  movss xmm8,[rax+8]`<br>`0x4c893f6  mov [rcx+8],eax`<br>`0x4c89777  lock dec dword ptr [r12+8]`<br>`0x4c897a3  mov rax,[rax+8]`<br>`0x4c897de  lock dec dword ptr [r12+8]`<br>`0x4c89802  mov rax,[rax+8]`<br>`0x4c8982a  lock dec dword ptr [rsi+8]`<br>`0x4c89850  mov rax,[rax+8]` | refcount: dec → destroy object via [vptr]; inc/cmpxchg on addref; qword reads = ptr/deleter slot; movss = float component |
| 0xC | 4 | rw | see sites | `0x4c88a9a  lock dec dword ptr [r14+0xC]`<br>`0x4c88ae2  lock dec dword ptr [r14+0xC]`<br>`0x4c88b1b  lock dec dword ptr [r14+0xC]`<br>`0x4c88b54  lock dec dword ptr [r14+0xC]`<br>`0x4c88bd2  lock dec dword ptr [r14+0xC]`<br>`0x4c88ee2  lock dec dword ptr [rcx+0xC]`<br>`0x4c88f60  lock dec dword ptr [rsi+0xC]`<br>`0x4c88fa2  lock dec dword ptr [rsi+0xC]`<br>`0x4c8956e  lock inc dword ptr [r12+0xC]`<br>`0x4c89595  lock inc dword ptr [r12+0xC]`<br>`0x4c89730  lock dec dword ptr [rcx+0xC]`<br>`0x4c89793  lock dec dword ptr [r12+0xC]`<br>`0x4c897f6  lock dec dword ptr [r12+0xC]`<br>`0x4c89843  lock dec dword ptr [rsi+0xC]` | second refcount: on zero free via [vptr+8]; lock inc on store (addref) |
| 0x10 | 8 | rw | see sites | `0x4c88d0f  mov rax,[rdi+0x10]`<br>`0x4c88e15  mov rax,[rdi+0x10]`<br>`0x4c89195  mov rax,[rax+0x10]`<br>`0x4c8941c  mov [rcx+0x10],rax`<br>`0x4c8947e  mov rax,[rdi+0x10]`<br>`0x4c89486  mov rax,[rax+0x10]` | config pointer [rdi+0x10] / vtable slots / record store |
| 0x18 | 8 / 4 | rw | see sites | `0x4c88cef  mov rax,[rax+0x18]`<br>`0x4c891cf  mov rax,[rax+0x18]`<br>`0x4c89412  mov [rcx+0x18],eax`<br>`0x4c8951a  mov r8,[rcx+0x18]` | vtable slots (CFG call) / record dword store |
| 0x20 | 16 / 8 / 1 | rw | see sites | `0x4c89185  cmp byte ptr [r12+0x20],1`<br>`0x4c891e8  cmp byte ptr [r12+0x20],1`<br>`0x4c89430  movups [rcx+0x20],xmm0`<br>`0x4c89482  mov rax,[rax+0x20]`<br>`0x4c894e5  movlps [rax+0x20],xmm7` | flag byte tested ==1 / 16-byte record store / qword stores |
| 0x28 | 4 / 8 | rw | see sites | `0x4c88cb1  mov rax,[rax+0x28]`<br>`0x4c894e9  movss [rax+0x28],xmm6` | vtable slot / float store |
| 0x31 | 1 | store | [rax+0x31] 0x4c89492 | `0x4c89492  mov byte ptr [rax+0x31],1` | - |
| 0x38 | 16 / 1 | rw | see sites | `0x4c88977  cmp byte ptr [rcx+0x38],0`<br>`0x4c8898e  mov byte ptr [rbx+0x38],1`<br>`0x4c89507  movups [rax+0x38],xmm0`<br>`0x4c8960d  mov byte ptr [rax+0x38],1` | lazy-init done flag (0→call 0x331DF0→1) / 16-byte result store |
| 0x40 | 8 | rw | see sites | `0x4c89167  mov [rbx+0x40],rax`<br>`0x4c8948a  mov rcx,[rax+0x40]` | - |
| 0x48 | 8 | rw | see sites | `0x4c88d0b  inc qword ptr [rbx+0x48]`<br>`0x4c894fc  mov [rax+0x48],rcx` | counter (inc) |
| 0x58 | 8 | read | [rax+0x58] 0x4c891ad | `0x4c891ad  mov rax,[rax+0x58]` | vtable slot (CFG call) |
| 0x60 | 16 / 8 | rw | see sites | `0x4c88996  mov rax,[rbx+0x60]`<br>`0x4c88a7b  movups [rbx+0x60],xmm0`<br>`0x4c89168  mov r12,[r12+0x60]`<br>`0x4c891f4  mov rax,[r12+0x60]` | 16-byte shared-ptr-style pair member swapped in; +0x68 control block released; +0x60 member walk |
| 0x68 | 8 | read | see sites | `0x4c88a77  mov r14,[rbx+0x68]`<br>`0x4c89209  cmp qword ptr [r12+0x68],0` | control block of [rbx+0x60] pair (lock-dec release) |
| 0x70 | 16 | store | [rbx+0x70] 0x4c88ac3 | `0x4c88ac3  movups [rbx+0x70],xmm0` | second 16-byte member swapped in (old control block [rbx+0x78] released) |
| 0x74 | 16 / 4 / 1 | read | see sites | `0x4c88d13  mov ecx,[rax+0x74]`<br>`0x4c88e19  movzx eax,byte ptr [rax+0x74]`<br>`0x4c89363  movups xmm0,[r12+0x74]` | index byte (<4, clamped) into float array +0x120; 16-byte read copied to [rbp+0x470] |
| 0x78 | 8 | read | [rbx+0x78] 0x4c88abf | `0x4c88abf  mov r14,[rbx+0x78]` | control block of [rbx+0x70] pair |
| 0x84 | 8 | read | [r12+0x84] 0x4c8937e, 0x4c893a5 | `0x4c8937e  mov rax,[r12+0x84]`<br>`0x4c893a5  mov rax,[r12+0x84]` | - |
| 0x88 | 8 | read | [rax+0x88] 0x4c88dbc | `0x4c88dbc  mov rdx,[rax+0x88]` | - |
| 0x8C | 4 | read | [r12+0x8C] 0x4c89370, 0x4c89397 | `0x4c89370  mov eax,[r12+0x8C]`<br>`0x4c89397  mov eax,[r12+0x8C]` | - |
| 0x90 | 4 / 8 | read | see sites | `0x4c88d77  mov r12,[rax+0x90]`<br>`0x4c8938d  movss xmm14,[r12+0x90]` | pointer of refcounted triple / float read |

| 0x98 | 8 | read | [rax+0x98] 0x4c88d5e, 0x4c88d70 | `0x4c88d5e  mov r12,[rax+0x98]`<br>`0x4c88d70  mov rdx,[rax+0x98]` | control block; addref via lock inc [ctl+8] |
| 0xA0 | 8 | read | [rax+0xA0] 0x4c88d8c | `0x4c88d8c  mov rdx,[rax+0xA0]` | - |
| 0xA8 | 8 | read | [rax+0xA8] 0x4c88d46 | `0x4c88d46  mov rcx,[rax+0xA8]` | - |
| 0xB0 | 8 | read | [rax+0xB0] 0x4c88d3f, 0x4c895b8 | `0x4c88d3f  mov r9,[rax+0xB0]`<br>`0x4c895b8  mov r9,[rax+0xB0]` | - |
| 0xF0 | 8 | read | [rax+0xF0] 0x4c88c3b | `0x4c88c3b  mov rax,[rax+0xF0]` | vtable slot (CFG call) |
| 0xF8 | 8 | read | [rax+0xF8] 0x4c88d38 | `0x4c88d38  mov r11,[rax+0xF8]` | - |
| 0x100 | 8 | read | [rax+0x100] 0x4c88c08; [rax+0x100] 0x4c88d31 | `0x4c88c08  mov rax,[rax+0x100]`<br>`0x4c88d31  mov r10,[rax+0x100]` | vtable slot (CFG call) / - |
| 0x120 | 4 | read | [rax+rcx*4+0x120] 0x4c88d21 | `0x4c88d21  movss xmm0,[rax+rcx*4+0x120]` | float array indexed by clamped +0x74 byte |
| 0x230 | 8 | read | [rcx+0x230] 0x4c89089 | `0x4c89089  mov r8,[rcx+0x230]` | vtable slot (CFG call) |
| 0x270 | 8 | read | [rax+0x270] 0x4c89078; [rax+0x270] 0x4c89499 | `0x4c89078  mov rax,[rax+0x270]`<br>`0x4c89499  mov rax,[rax+0x270]` | vtable slot (CFG call) |
| 0x338 | 8 | read | [rax+0x338] 0x4c889a6 | `0x4c889a6  mov rax,[rax+0x338]` | vtable slot (CFG call) |
| 0x360 | 8 | read | [rax+0x360] 0x4c8a62b (clone) | `0x4c8a62b  mov rax,[rax+0x360]` | vtable slot (CFG call) |
| 0x418 | 8 | read | [rax+0x418] 0x4c8906e | `0x4c8906e  mov rcx,[rax+0x418]` | - |
| 0x480 | 8 | read | [rdx+0x480] 0x4c8929a; [rcx+0x480] 0x4c89653 | `0x4c8929a  mov rdx,[rdx+0x480]`<br>`0x4c89653  mov rcx,[rcx+0x480]` | - |
| 0x4B4 | 1 | read | [rax+0x4B4] 0x4c890ab | `0x4c890ab  movzx eax,byte ptr [rax+0x4B4]` | - |
| 0x5C8 | 8 | read | [rax+0x5C8] 0x4c88c5b | `0x4c88c5b  mov rax,[rax+0x5C8]` | vtable slot (CFG call) |
| 0x64C | 8 | read | [rdx+0x64C] 0x4c892df | `0x4c892df  movsd xmm7,[rdx+0x64C]` | - |
| 0x654 | 4 | read | [rdx+0x654] 0x4c892a1 | `0x4c892a1  movss xmm6,[rdx+0x654]` | - |

## OPEN

- [UNVERIFIED: 0x4c8a683 message string text at 0xF52E07A not readable from listing]
- [UNVERIFIED: 0x4c892a1 gameplay meaning of floats [rdx+0x64C]/[rdx+0x654]]

## TOOL REQUESTS

None.
