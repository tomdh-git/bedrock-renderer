## NEXT
DONE

# U-Img dossier — imageutils loadImageFromFile (F1 0x19944B0) + loadImageFromMemory (F2 0x1994F90)

Static analysis of `Minecraft.Windows.exe` listings in docs/data/listings/. Every instruction of both listings is reproduced verbatim below, split into phases of at most 40 instructions. [V] = read directly from the listing/strings, [I] = inference from call targets and data flow.

## F1 imageutils_loadImageFromFile 0x19944B0..0x1994DB6 (plus 7 small stubs to 0x1994F8F)

Out-object builder [I]: rcx = result image object (rsi), rdx = 16-byte argument copied by value (rbx). Builds a stream context, runs format sniffing and two registry lookups (0x3AFBE0), drives decoders 0x764950/0x7647C0, computes the byte size and allocates via 0x1993EB0; error path 0x1994BBF logs through 0x3CF160.

#### Phase 1 0x19944b0..0x199457f: Prologue: spill xmm6 to [rbp+0x200], stack cookie -2 at [rbp+0x1F8], stage the 16-byte second argument by value (movups from [rdx] into [rbp+0x10], saved base at [rbp+0x98]) and zero decoder outputs [rbp+0x1EC/0x1F0/0x1F4] [V]. Reads the static-init guard global (cmp eax,[rcx+4]) and TLS gs:[0x58] before entering the guarded body [I].
```
0x19944b0  push rbp
0x19944b1  push r15
0x19944b3  push r14
0x19944b5  push r13
0x19944b7  push r12
0x19944b9  push rsi
0x19944ba  push rdi
0x19944bb  push rbx
0x19944bc  sub rsp,0x298
0x19944c3  lea rbp,[rsp+0x80]
0x19944cb  movaps [rbp+0x200],xmm6
0x19944d2  mov qword ptr [rbp+0x1F8],0xFFFFFFFFFFFFFFFE
0x19944dd  mov rbx,rdx
0x19944e0  mov rsi,rcx
0x19944e3  mov dword ptr [rbp+0x1F4],0
0x19944ed  mov dword ptr [rbp+0x1EC],0
0x19944f7  mov dword ptr [rbp+0x1F0],0
0x1994501  xorps xmm0,xmm0
0x1994504  movaps [rbp+0x1A0],xmm0
0x199450b  movups xmm0,[rdx]
0x199450e  movaps [rbp+0x10],xmm0
0x1994512  mov eax,[0x128D09C0]
0x1994518  mov ecx,[0x128767C8]
0x199451e  mov rdx,gs:[0x58]
0x1994527  mov rcx,[rdx+rcx*8]
0x199452b  cmp eax,[rcx+4]
0x1994531  jg 0x1994D73
0x1994537  movaps xmm0,[rbp+0x10]
0x199453b  movaps [rbp+0xA0],xmm0
0x1994542  lea rcx,[0x128D09A0]
0x1994549  mov rax,[0x128D09A0]
0x1994550  mov rax,[rax+8]
0x1994554  mov r10,[0xF99FFA0]
0x199455b  mov dword ptr [rsp+0x28],0
0x1994563  mov word ptr [rsp+0x20],0x121
0x199456a  lea rdx,[rbp-0x38]
0x199456e  lea r8,[rbp+0xA0]
0x1994575  lea r9,[rbp+0x1A0]
0x199457c  call r10
0x199457f  nop
```

#### Phase 2 0x1994580..0x199467f: Builds the first find-descriptor at [rbp+0x20..0x68] (tag 0xBB with r14/r13 keys, saved arg base at [rbp+0x98]) and calls registry lookup 0x3AFBE0(edx=2, r8d=0x2D), testing the result flag at [rax+0x40] [V]. Initializes the stream-context block [rbp+0xB0..0xD8] and zeroes the position accumulator [rbp+0x158] [I].
```
0x1994580  mov rdi,0x29AAF7A7645E47FD
0x199458a  mov [rbp+0x20],rdi
0x199458e  lea r12,[0xF81EDF7]
0x1994595  mov [rbp+0x28],r12
0x1994599  mov qword ptr [rbp+0x30],1
0x19945a1  mov dword ptr [rbp+0x38],0xBB
0x19945a8  lea r14,[0xAA6D0]
0x19945af  mov [rbp+0x40],r14
0x19945b3  lea r13,[0x3AFCB0]
0x19945ba  mov [rbp+0x48],r13
0x19945be  lea rax,[rbp+0x20]
0x19945c2  mov [rsp+0x20],rax
0x19945c7  lea rcx,[rbp-0x38]
0x19945cb  lea r9,[rbp+0x40]
0x19945cf  mov edx,2
0x19945d4  mov r8d,0x2D
0x19945da  call 0x3AFBE0
0x19945df  cmp byte ptr [rax+0x40],1
0x19945e3  jne 0x199472A
0x19945e9  mov [rbp+0x98],rbx
0x19945f0  movaps xmm0,[rbp+0x1A0]
0x19945f7  mov rcx,[rbp+0x1A0]
0x19945fe  mov qword ptr [rbp+0x1A0],0
0x1994609  movaps [rbp+0x1D0],xmm0
0x1994610  mov qword ptr [rbp+0x1A8],0
0x199461b  mov rax,[0xF0FF760]
0x1994622  mov [rbp+0xC0],rax
0x1994629  movups xmm6,[0xF0FF750]
0x1994630  movups [rbp+0xB0],xmm6
0x1994637  lea rax,[rbp+0x1D0]
0x199463e  mov [rbp+0xC8],rax
0x1994645  mov rax,0x8000000001
0x199464f  mov [rbp+0xD0],rax
0x1994656  mov dword ptr [rbp+0x158],0
0x1994660  mov r15,r14
0x1994663  lea r14,[rbp+0xD8]
0x199466a  mov [rbp+0x170],r14
0x1994671  mov [rbp+0x160],r14
0x1994678  lea rax,[rbp+0x1B8]
0x199467f  mov [rsp+0x20],rax
```

#### Phase 3 0x1994684..0x1994757: Fills the second descriptor (tag 0x26) and its [rbp+0x1C0/0x1C8] payload, then applies the first stream-position update [rbp+0x158] += eax - [rbp+0x170] and re-arms the cursor held at [rbp+0x1D0] [I].
```
0x1994684  lea rbx,[rbp+0x50]
0x1994688  mov r9d,0x80
0x199468e  mov rdx,rbx
0x1994691  mov r8,r14
0x1994694  call 0x45E6F0
0x1994699  mov [rbp+0x180],rdi
0x19946a0  mov [rbp+0x188],r12
0x19946a7  mov qword ptr [rbp+0x190],1
0x19946b2  mov dword ptr [rbp+0x198],0x26
0x19946bc  mov [rbp+0x1C0],r15
0x19946c3  mov [rbp+0x1C8],r13
0x19946ca  lea rax,[rbp+0x180]
0x19946d1  mov [rsp+0x20],rax
0x19946d6  lea r9,[rbp+0x1C0]
0x19946dd  mov rcx,rbx
0x19946e0  mov edx,2
0x19946e5  mov r8d,0x2D
0x19946eb  call 0x3AFBE0
0x19946f0  cmp byte ptr [rax+0x40],0
0x19946f4  mov r15d,0xFFFFFFFF
0x19946fa  je short 0x1994703
0x19946fc  mov r15d,[rbp+0x1B8]
0x1994703  mov rcx,rbx
0x1994706  call 0x87440
0x199470b  mov eax,[rbp+0x160]
0x1994711  sub eax,[rbp+0x170]
0x1994717  add [rbp+0x158],eax
0x199471d  test r15d,r15d
0x1994720  je short 0x1994731
0x1994722  movsxd rax,r15d
0x1994725  add rax,r14
0x1994728  jmp short 0x1994749
0x199472a  xor edi,edi
0x199472c  jmp 0x1994CE9
0x1994731  mov dword ptr [rbp+0xD0],0
0x199473b  lea rax,[rbp+0xD9]
0x1994742  mov byte ptr [rbp+0xD8],0
0x1994749  mov [rbp+0x160],r14
0x1994750  mov [rbp+0x168],rax
0x1994757  mov [rbp+0x178],rax
```

#### Phase 4 0x199475e..0x199481e: Calls the format sniffer 0x764E50 and stores its verdict in [rbp+0x1B4] (later the byte-size shift count) [V]. Replaces a previously held object at [rbp+0x50]/[rbp+0x58] via the destroy-when-flag pattern (cmp byte ptr [rbp+0x58],1) and seeds a fresh holder with constants 1 and 0x40 [I].
```
0x199475e  lea rcx,[rbp+0xA0]
0x1994765  call 0x764E50
0x199476a  mov [rbp+0x1B4],eax
0x1994770  mov r15,[rbp+0x1D0]
0x1994777  lea rdx,[rbp+0x50]
0x199477b  mov rcx,r15
0x199477e  mov r8b,1
0x1994781  call 0x45E5C0
0x1994786  nop
0x1994787  lea rdx,[rbp+0xA0]
0x199478e  mov rcx,r15
0x1994791  xor r8d,r8d
0x1994794  call 0x45EB90
0x1994799  nop
0x199479a  cmp byte ptr [rbp+0x58],1
0x199479e  jne short 0x19947A9
0x19947a0  mov rcx,[rbp+0x50]
0x19947a4  call 0xEEC5A10
0x19947a9  mov [rbp+0x50],rdi
0x19947ad  mov [rbp+0x58],r12
0x19947b1  mov qword ptr [rbp+0x60],1
0x19947b9  mov dword ptr [rbp+0x68],0x40
0x19947c0  lea rbx,[0xAA6D0]
0x19947c7  mov [rbp+0x180],rbx
0x19947ce  mov [rbp+0x188],r13
0x19947d5  lea rax,[rbp+0x50]
0x19947d9  mov [rsp+0x20],rax
0x19947de  lea r15,[rbp+0xA0]
0x19947e5  lea r13,[rbp+0x180]
0x19947ec  mov rcx,r15
0x19947ef  mov edx,2
0x19947f4  mov r8d,0x2D
0x19947fa  mov r9,r13
0x19947fd  call 0x3AFBE0
0x1994802  mov rcx,r15
0x1994805  call 0x87440
0x199480a  cmp dword ptr [rbp+0x1B4],0
0x1994811  je 0x1994920
0x1994817  mov rax,[0xF0FF760]
0x199481e  mov [rbp+0xC0],rax
```

#### Phase 5 0x1994825..0x199490f: Rebuilds the stream context for a second read attempt (movups [rbp+0xB0],xmm6 and friends) and repeats the position update [V]. Runs the second registry lookup (tag 0x26) and takes the result id from [rbp+0x1B8] when the flag byte at [rax+0x40] clears [I].
```
0x1994825  movups [rbp+0xB0],xmm6
0x199482c  lea rax,[rbp+0x1D0]
0x1994833  mov [rbp+0xC8],rax
0x199483a  mov rax,0x8000000001
0x1994844  mov [rbp+0xD0],rax
0x199484b  mov dword ptr [rbp+0x158],0
0x1994855  mov [rbp+0x170],r14
0x199485c  mov [rbp+0x160],r14
0x1994863  mov rcx,[rbp+0x1D0]
0x199486a  lea rax,[rbp+0x1B8]
0x1994871  mov [rsp+0x20],rax
0x1994876  lea r15,[rbp+0x50]
0x199487a  mov r9d,0x80
0x1994880  mov rdx,r15
0x1994883  mov r8,r14
0x1994886  call 0x45E6F0
0x199488b  mov [rbp+0x180],rdi
0x1994892  mov [rbp+0x188],r12
0x1994899  mov qword ptr [rbp+0x190],1
0x19948a4  mov dword ptr [rbp+0x198],0x26
0x19948ae  mov [rbp+0x1C0],rbx
0x19948b5  lea rax,[0x3AFCB0]
0x19948bc  mov [rbp+0x1C8],rax
0x19948c3  mov [rsp+0x20],r13
0x19948c8  lea r9,[rbp+0x1C0]
0x19948cf  mov rcx,r15
0x19948d2  mov edx,2
0x19948d7  mov r8d,0x2D
0x19948dd  call 0x3AFBE0
0x19948e2  cmp byte ptr [rax+0x40],0
0x19948e6  mov edi,0xFFFFFFFF
0x19948eb  je short 0x19948F3
0x19948ed  mov edi,[rbp+0x1B8]
0x19948f3  mov rcx,r15
0x19948f6  call 0x87440
0x19948fb  mov eax,[rbp+0x160]
0x1994901  sub eax,[rbp+0x170]
0x1994907  add [rbp+0x158],eax
0x199490d  test edi,edi
0x199490f  je 0x1994A25
```

#### Phase 6 0x1994915..0x19949ff: Third stream-context build for the fallback lookup path: re-fills the 0x26 descriptor at [rbp+0x180..0x198], re-reads through the cursor [rbp+0x1D0], and again harvests the lookup id from [rbp+0x1B8] gated by [rax+0x40] [I].
```
0x1994915  movsxd rax,edi
0x1994918  add rax,r14
0x199491b  jmp 0x1994A3D
0x1994920  mov rax,[0xF0FF760]
0x1994927  mov [rbp+0xC0],rax
0x199492e  movups [rbp+0xB0],xmm6
0x1994935  lea rax,[rbp+0x1D0]
0x199493c  mov [rbp+0xC8],rax
0x1994943  mov rax,0x8000000001
0x199494d  mov [rbp+0xD0],rax
0x1994954  mov dword ptr [rbp+0x158],0
0x199495e  mov [rbp+0x170],r14
0x1994965  mov [rbp+0x160],r14
0x199496c  mov rcx,[rbp+0x1D0]
0x1994973  lea rax,[rbp+0x1B8]
0x199497a  mov [rsp+0x20],rax
0x199497f  lea r15,[rbp+0x50]
0x1994983  mov r9d,0x80
0x1994989  mov rdx,r15
0x199498c  mov r8,r14
0x199498f  call 0x45E6F0
0x1994994  mov [rbp+0x180],rdi
0x199499b  mov [rbp+0x188],r12
0x19949a2  mov qword ptr [rbp+0x190],1
0x19949ad  mov dword ptr [rbp+0x198],0x26
0x19949b7  mov [rbp+0x1C0],rbx
0x19949be  lea rax,[0x3AFCB0]
0x19949c5  mov [rbp+0x1C8],rax
0x19949cc  mov [rsp+0x20],r13
0x19949d1  lea r9,[rbp+0x1C0]
0x19949d8  mov rcx,r15
0x19949db  mov edx,2
0x19949e0  mov r8d,0x2D
0x19949e6  call 0x3AFBE0
0x19949eb  cmp byte ptr [rax+0x40],0
0x19949ef  mov edi,0xFFFFFFFF
0x19949f4  je short 0x19949FC
0x19949f6  mov edi,[rbp+0x1B8]
0x19949fc  mov rcx,r15
0x19949ff  call 0x87440
```

#### Phase 7 0x1994a04..0x1994af5: Completes the last position update and decoder-handoff bookkeeping (payload [rbp+0x1C0/0x1C8], dword resets inside the stream block) [V]. Loads the decoder format id eax=[rbp+0x1F4] to start the format mapping step [I].
```
0x1994a04  mov eax,[rbp+0x160]
0x1994a0a  sub eax,[rbp+0x170]
0x1994a10  add [rbp+0x158],eax
0x1994a16  test edi,edi
0x1994a18  je short 0x1994A98
0x1994a1a  movsxd rax,edi
0x1994a1d  add rax,r14
0x1994a20  jmp 0x1994AB0
0x1994a25  mov dword ptr [rbp+0xD0],0
0x1994a2f  lea rax,[rbp+0xD9]
0x1994a36  mov byte ptr [rbp+0xD8],0
0x1994a3d  mov [rbp+0x160],r14
0x1994a44  mov [rbp+0x168],rax
0x1994a4b  mov [rbp+0x178],rax
0x1994a52  mov dword ptr [rsp+0x20],0
0x1994a5a  lea rcx,[rbp+0xA0]
0x1994a61  lea rdx,[rbp+0x1EC]
0x1994a68  lea r8,[rbp+0x1F0]
0x1994a6f  lea r9,[rbp+0x1F4]
0x1994a76  call 0x764950
0x1994a7b  mov [rbp+0x1C0],rax
0x1994a82  test rax,rax
0x1994a85  je 0x1994BBF
0x1994a8b  mov r12d,5
0x1994a91  mov al,2
0x1994a93  jmp 0x1994B1B
0x1994a98  mov dword ptr [rbp+0xD0],0
0x1994aa2  lea rax,[rbp+0xD9]
0x1994aa9  mov byte ptr [rbp+0xD8],0
0x1994ab0  mov [rbp+0x160],r14
0x1994ab7  mov [rbp+0x168],rax
0x1994abe  mov [rbp+0x178],rax
0x1994ac5  mov dword ptr [rsp+0x20],0
0x1994acd  lea rcx,[rbp+0xA0]
0x1994ad4  lea rdx,[rbp+0x1EC]
0x1994adb  lea r8,[rbp+0x1F0]
0x1994ae2  lea r9,[rbp+0x1F4]
0x1994ae9  call 0x7647C0
0x1994aee  mov [rbp+0x1C0],rax
0x1994af5  test rax,rax
```

#### Phase 8 0x1994af8..0x1994ba3: Writes the result image object at [rsi]: format r12d, width [rbp+0x1EC], height [rbp+0x1F0], zero fields, the 0x3C7B10 vtable pointer at +0x18, releasing any old +0x20 buffer through import [0xF99FFA0] [V]. Computes the byte size w*h*[rbp+0x1F4] shifted by the sniffer value in [rbp+0x1B4] (imul/shl), then tests the held stream object [rbp+0x1D0] for null [I].
```
0x1994af8  je 0x1994BBF
0x1994afe  mov eax,[rbp+0x1F4]
0x1994b04  xor r12d,r12d
0x1994b07  cmp eax,3
0x1994b0a  setne r12b
0x1994b0e  add r12d,3
0x1994b12  cmp eax,1
0x1994b15  cmove r12d,eax
0x1994b19  mov al,1
0x1994b1b  mov r14d,[rbp+0x1F0]
0x1994b22  mov r15d,[rbp+0x1EC]
0x1994b29  mov [rsi],r12d
0x1994b2c  mov [rsi+4],r15d
0x1994b30  mov [rsi+8],r14d
0x1994b34  mov dword ptr [rsi+0xC],0
0x1994b3b  mov [rsi+0x10],al
0x1994b3e  mov byte ptr [rsi+0x11],0
0x1994b42  mov rcx,[rsi+0x20]
0x1994b46  mov qword ptr [rsi+0x20],0
0x1994b4e  test rcx,rcx
0x1994b51  je short 0x1994B5E
0x1994b53  mov rax,[rsi+0x18]
0x1994b57  call qword ptr [0xF99FFA0]
0x1994b5d  nop
0x1994b5e  lea rax,[0x3C7B10]
0x1994b65  mov [rsi+0x18],rax
0x1994b69  mov qword ptr [rsi+0x28],0
0x1994b71  mov eax,r15d
0x1994b74  imul eax,r14d
0x1994b78  imul eax,[rbp+0x1F4]
0x1994b7f  mov ecx,[rbp+0x1B4]
0x1994b85  shl eax,cl
0x1994b87  cdqe
0x1994b89  mov dil,1
0x1994b8c  mov [rsp+0x28],r12d
0x1994b91  mov [rsp+0x20],rax
0x1994b96  lea rdx,[rbp+0x1C0]
0x1994b9d  mov rcx,rsi
0x1994ba0  mov r8d,r15d
0x1994ba3  mov r9d,r14d
```

#### Phase 9 0x1994ba6..0x1994c8d: Error path 0x1994BBF: loads EH/TLS state (gs:[0x58] then [rax+0xC98]), takes the message from the caller's arg2 or the default string 0xF824F15, and logs through 0x3CF160 with level 8 using strings 0xF50D4A5 (len 0x25), 0xF5DA1C7 (len 0xE4) and 0xF000628 [V].
```
0x1994ba6  call 0x1993EB0
0x1994bab  nop
0x1994bac  cmp qword ptr [rbp+0x1D0],0
0x1994bb4  jne 0x1994C8F
0x1994bba  jmp 0x1994CAF
0x1994bbf  mov eax,[0x128767C8]
0x1994bc5  mov rcx,gs:[0x58]
0x1994bce  mov rax,[rcx+rax*8]
0x1994bd2  mov rax,[rax+0xC98]
0x1994bd9  mov rcx,[rbp+0x98]
0x1994be0  mov rcx,[rcx]
0x1994be3  test rcx,rcx
0x1994be6  lea rdx,[0xF824F15]
0x1994bed  cmovne rdx,rcx
0x1994bf1  mov [rbp+0xA0],rdx
0x1994bf8  mov [rbp+0xB0],rax
0x1994bff  lea rax,[0xF000628]
0x1994c06  mov [rbp+0xC0],rax
0x1994c0d  mov qword ptr [rbp+0xC8],1
0x1994c18  mov qword ptr [rbp+0x50],0xDCC
0x1994c20  lea rax,[rbp+0xA0]
0x1994c27  mov [rbp+0x58],rax
0x1994c2b  lea rax,[0xF50D4A5]
0x1994c32  mov [rbp+0x180],rax
0x1994c39  mov qword ptr [rbp+0x188],0x25
0x1994c44  lea rax,[rbp+0x50]
0x1994c48  mov [rsp+0x40],rax
0x1994c4d  mov [rsp+0x38],r13
0x1994c52  lea rax,[0xF5DA1C7]
0x1994c59  mov [rsp+0x28],rax
0x1994c5e  mov dword ptr [rsp+0x30],0xE4
0x1994c66  mov dword ptr [rsp+0x20],8
0x1994c6e  xor edi,edi
0x1994c70  xor ecx,ecx
0x1994c72  mov edx,1
0x1994c77  xor r8d,r8d
0x1994c7a  mov r9d,0xF
0x1994c80  call 0x3CF160
0x1994c85  cmp qword ptr [rbp+0x1D0],0
0x1994c8d  je short 0x1994CAF
```

#### Phase 10 0x1994c8f..0x1994d43: Post-error cleanup: walks the held objects ([rbp+0x1D8], [rbp+0x1A8], [rbp+0x1A0]) through double indirections ([rcx] then [rax]) to reach and invoke their destructors only when non-null [I].
```
0x1994c8f  lea rcx,[rbp+0x1D0]
0x1994c96  lea rdx,[rbp+0xA0]
0x1994c9d  call 0x43C5D0
0x1994ca2  nop
0x1994ca3  lea rcx,[rbp+0xA0]
0x1994caa  call 0x87440
0x1994caf  mov rcx,[rbp+0x1D8]
0x1994cb6  test rcx,rcx
0x1994cb9  je short 0x1994CCC
0x1994cbb  mov rax,[rcx]
0x1994cbe  mov rax,[rax]
0x1994cc1  mov edx,1
0x1994cc6  call qword ptr [0xF99FFA0]
0x1994ccc  mov rcx,[rbp+0x1D0]
0x1994cd3  test rcx,rcx
0x1994cd6  je short 0x1994CE9
0x1994cd8  mov rax,[rcx]
0x1994cdb  mov rax,[rax]
0x1994cde  mov edx,1
0x1994ce3  call qword ptr [0xF99FFA0]
0x1994ce9  lea rcx,[rbp-0x38]
0x1994ced  call 0x87440
0x1994cf2  cmp qword ptr [rbp+0x1A0],0
0x1994cfa  je short 0x1994D1C
0x1994cfc  lea rcx,[rbp+0x1A0]
0x1994d03  lea rdx,[rbp+0xA0]
0x1994d0a  call 0x43C5D0
0x1994d0f  nop
0x1994d10  lea rcx,[rbp+0xA0]
0x1994d17  call 0x87440
0x1994d1c  mov rcx,[rbp+0x1A8]
0x1994d23  test rcx,rcx
0x1994d26  je short 0x1994D39
0x1994d28  mov rax,[rcx]
0x1994d2b  mov rax,[rax]
0x1994d2e  mov edx,1
0x1994d33  call qword ptr [0xF99FFA0]
0x1994d39  mov rcx,[rbp+0x1A0]
0x1994d40  test rcx,rcx
0x1994d43  je short 0x1994D56
```

#### Phase 11 0x1994d45..0x1994db6: Epilogue restoring xmm6 from [rbp+0x200], followed by the in-place static-init slow path 0x1994D73: guards global 0x128D09C0, runs initializers 0xE938CB0 / 0x446CB0 / 0xE935740 / 0xE938D70 and jumps back to 0x1994537 [V].
```
0x1994d45  mov rax,[rcx]
0x1994d48  mov rax,[rax]
0x1994d4b  mov edx,1
0x1994d50  call qword ptr [0xF99FFA0]
0x1994d56  mov eax,edi
0x1994d58  movaps xmm6,[rbp+0x200]
0x1994d5f  add rsp,0x298
0x1994d66  pop rbx
0x1994d67  pop rdi
0x1994d68  pop rsi
0x1994d69  pop r12
0x1994d6b  pop r13
0x1994d6d  pop r14
0x1994d6f  pop r15
0x1994d71  pop rbp
0x1994d72  ret
0x1994d73  lea rcx,[0x128D09C0]
0x1994d7a  call 0xE938CB0
0x1994d7f  cmp dword ptr [0x128D09C0],0xFFFFFFFF
0x1994d86  jne 0x1994537
0x1994d8c  lea rcx,[0x128D09A0]
0x1994d93  call 0x446CB0
0x1994d98  nop
0x1994d99  lea rcx,[0x446ED0]
0x1994da0  call 0xE935740
0x1994da5  lea rcx,[0x128D09C0]
0x1994dac  call 0xE938D70
0x1994db1  jmp 0x1994537
0x1994db6  nop [rax+rax]
```

#### Phase 12 stub S1 0x1994dc0..0x1994e06: Deleter stub sharing F1's frame layout (rbp = rdx+0x80): homes rdx at [rsp+0x10], spills xmm6 to [rsp+0x40]; when the held-object flag byte [rbp+0x58] equals 1 it calls 0xEEC5A10([rbp+0x50]) to destroy the buffered image [I].
```
0x1994dc0  mov [rsp+0x10],rdx
0x1994dc5  push rbp
0x1994dc6  push r15
0x1994dc8  push r14
0x1994dca  push r13
0x1994dcc  push r12
0x1994dce  push rsi
0x1994dcf  push rdi
0x1994dd0  push rbx
0x1994dd1  sub rsp,0x58
0x1994dd5  lea rbp,[rdx+0x80]
0x1994ddc  movaps [rsp+0x40],xmm6
0x1994de1  cmp byte ptr [rbp+0x58],1
0x1994de5  jne short 0x1994DF0
0x1994de7  mov rcx,[rbp+0x50]
0x1994deb  call 0xEEC5A10
0x1994df0  movaps xmm6,[rsp+0x40]
0x1994df5  add rsp,0x58
0x1994df9  pop rbx
0x1994dfa  pop rdi
0x1994dfb  pop rsi
0x1994dfc  pop r12
0x1994dfe  pop r13
0x1994e00  pop r14
0x1994e02  pop r15
0x1994e04  pop rbp
0x1994e05  ret
0x1994e06  nop [rax+rax]
```

#### Phase 13 stub S2 0x1994e10..0x1994e53: Companion stub: homes rdx, spills xmm6, then calls 0x1134D0 on the object held at [rbp+0x1A0], the stream companion of F1's decoder holder [I].
```
0x1994e10  mov [rsp+0x10],rdx
0x1994e15  push rbp
0x1994e16  push r15
0x1994e18  push r14
0x1994e1a  push r13
0x1994e1c  push r12
0x1994e1e  push rsi
0x1994e1f  push rdi
0x1994e20  push rbx
0x1994e21  sub rsp,0x58
0x1994e25  lea rbp,[rdx+0x80]
0x1994e2c  movaps [rsp+0x40],xmm6
0x1994e31  lea rcx,[rbp+0x1A0]
0x1994e38  call 0x1134D0
0x1994e3d  movaps xmm6,[rsp+0x40]
0x1994e42  add rsp,0x58
0x1994e46  pop rbx
0x1994e47  pop rdi
0x1994e48  pop rsi
0x1994e49  pop r12
0x1994e4b  pop r13
0x1994e4d  pop r14
0x1994e4f  pop r15
0x1994e51  pop rbp
0x1994e52  ret
0x1994e53  nop [rax+rax]
```

#### Phase 14 stub S3 0x1994e60..0x1994ea3: Init-guard release stub: homes rdx, spills xmm6, then calls 0xE938D30 on global 0x128D09C0, releasing the loader static-init lock taken by F1's slow path [I].
```
0x1994e60  mov [rsp+0x10],rdx
0x1994e65  push rbp
0x1994e66  push r15
0x1994e68  push r14
0x1994e6a  push r13
0x1994e6c  push r12
0x1994e6e  push rsi
0x1994e6f  push rdi
0x1994e70  push rbx
0x1994e71  sub rsp,0x58
0x1994e75  lea rbp,[rdx+0x80]
0x1994e7c  movaps [rsp+0x40],xmm6
0x1994e81  lea rcx,[0x128D09C0]
0x1994e88  call 0xE938D30
0x1994e8d  movaps xmm6,[rsp+0x40]
0x1994e92  add rsp,0x58
0x1994e96  pop rbx
0x1994e97  pop rdi
0x1994e98  pop rsi
0x1994e99  pop r12
0x1994e9b  pop r13
0x1994e9d  pop r14
0x1994e9f  pop r15
0x1994ea1  pop rbp
0x1994ea2  ret
0x1994ea3  nop [rax+rax]
```

#### Phase 15 stubs S4+S5 0x1994eb0..0x1994f07: Two noreturn traps: each homes rdx, spills xmm6, calls 0xEEC6E40 and ends in int3 — unreachable-by-design error stubs [V].
```
0x1994eb0  mov [rsp+0x10],rdx
0x1994eb5  push rbp
0x1994eb6  push r15
0x1994eb8  push r14
0x1994eba  push r13
0x1994ebc  push r12
0x1994ebe  push rsi
0x1994ebf  push rdi
0x1994ec0  push rbx
0x1994ec1  sub rsp,0x58
0x1994ec5  lea rbp,[rdx+0x80]
0x1994ecc  movaps [rsp+0x40],xmm6
0x1994ed1  call 0xEEC6E40
0x1994ed6  int3
0x1994ed7  nop [rax+rax]
0x1994ee0  mov [rsp+0x10],rdx
0x1994ee5  push rbp
0x1994ee6  push r15
0x1994ee8  push r14
0x1994eea  push r13
0x1994eec  push r12
0x1994eee  push rsi
0x1994eef  push rdi
0x1994ef0  push rbx
0x1994ef1  sub rsp,0x58
0x1994ef5  lea rbp,[rdx+0x80]
0x1994efc  movaps [rsp+0x40],xmm6
0x1994f01  call 0xEEC6E40
0x1994f06  int3
0x1994f07  nop [rax+rax]
```

#### Phase 16 stub S6 0x1994f10..0x1994f5c: Destructor stub: homes rdx, spills xmm6, calls 0x1134D0 on the stream context [rbp+0x1D0] and 0x87440 on the contained string at [rbp-0x38], then nop-pads out [I].
```
0x1994f10  mov [rsp+0x10],rdx
0x1994f15  push rbp
0x1994f16  push r15
0x1994f18  push r14
0x1994f1a  push r13
0x1994f1c  push r12
0x1994f1e  push rsi
0x1994f1f  push rdi
0x1994f20  push rbx
0x1994f21  sub rsp,0x58
0x1994f25  lea rbp,[rdx+0x80]
0x1994f2c  movaps [rsp+0x40],xmm6
0x1994f31  lea rcx,[rbp+0x1D0]
0x1994f38  call 0x1134D0
0x1994f3d  lea rcx,[rbp-0x38]
0x1994f41  call 0x87440
0x1994f46  movaps xmm6,[rsp+0x40]
0x1994f4b  add rsp,0x58
0x1994f4f  pop rbx
0x1994f50  pop rdi
0x1994f51  pop rsi
0x1994f52  pop r12
0x1994f54  pop r13
0x1994f56  pop r14
0x1994f58  pop r15
0x1994f5a  pop rbp
0x1994f5b  ret
0x1994f5c  nop [rax]
```

#### Phase 17 stub S7 0x1994f60..0x1994f8f: Noreturn trap like S4/S5: homes rdx, spills xmm6, calls 0xEEC6E40 and int3 with padding to 0x1994f8f [V].
```
0x1994f60  mov [rsp+0x10],rdx
0x1994f65  push rbp
0x1994f66  push r15
0x1994f68  push r14
0x1994f6a  push r13
0x1994f6c  push r12
0x1994f6e  push rsi
0x1994f6f  push rdi
0x1994f70  push rbx
0x1994f71  sub rsp,0x58
0x1994f75  lea rbp,[rdx+0x80]
0x1994f7c  movaps [rsp+0x40],xmm6
0x1994f81  call 0xEEC6E40
0x1994f86  int3
0x1994f87  int3
0x1994f88  int3
0x1994f89  int3
0x1994f8a  int3
0x1994f8b  int3
0x1994f8c  int3
0x1994f8d  int3
0x1994f8e  int3
0x1994f8f  int3
```

## Field tables

| offset | size | direction | verbatim line | meaning |
|---|---|---|---|---|
| F1 rsi+0x0 | 4 | W | 0x1994b29  mov [rsi],r12d | out image: format id [I] |
| F1 rsi+0x4 | 4 | W | 0x1994b2c  mov [rsi+4],r15d | out image: width from [rbp+0x1EC] [I] |
| F1 rsi+0x8 | 4 | W | 0x1994b30  mov [rsi+8],r14d | out image: height from [rbp+0x1F0] [I] |
| F1 rsi+0xc | 4 | W | 0x1994b34  mov dword ptr [rsi+0xC],0 | out image field zeroed |
| F1 rsi+0x10 | 1 | W | 0x1994b3b  mov [rsi+0x10],al | out image: flag byte from decoder [I] |
| F1 rsi+0x11 | 1 | W | 0x1994b3e  mov byte ptr [rsi+0x11],0 | out image field zeroed |
| F1 rsi+0x18 | 8 | R+W | 0x1994b53  mov rax,[rsi+0x18] ; 0x1994b65  mov [rsi+0x18],rax | vtable slot, rewritten to 0x3C7B10 [I] |
| F1 rsi+0x20 | 8 | R+W | 0x1994b42  mov rcx,[rsi+0x20] ; 0x1994b46  mov qword ptr [rsi+0x20],0 | old buffer ptr, freed via import [0xF99FFA0] [I] |
| F1 rsi+0x28 | 8 | W | 0x1994b69  mov qword ptr [rsi+0x28],0 | out image tail field zeroed |
| F1 rbp+0x10 | 16 | W+R | 0x199450e  movaps [rbp+0x10],xmm0 ; 0x1994537  movaps xmm0,[rbp+0x10] | staging of the 16-byte arg2 copy [I] |
| F1 rbp+0x20 | 8 | W | 0x199458a  mov [rbp+0x20],rdi | find-descriptor key 1 [I] |
| F1 rbp+0x28 | 8 | W | 0x1994595  mov [rbp+0x28],r12 | find-descriptor key 2 [I] |
| F1 rbp+0x30 | 8 | W | 0x1994599  mov qword ptr [rbp+0x30],1 | descriptor kind = 1 [I] |
| F1 rbp+0x38 | 4 | W | 0x19945a1  mov dword ptr [rbp+0x38],0xBB | descriptor tag 0xBB |
| F1 rbp+0x40 | 8 | W | 0x19945af  mov [rbp+0x40],r14 | descriptor payload [I] |
| F1 rbp+0x48 | 8 | W | 0x19945ba  mov [rbp+0x48],r13 | descriptor payload [I] |
| F1 rbp+0x50 | 8 | R+W | 0x19947a0  mov rcx,[rbp+0x50] ; 0x19947a9  mov [rbp+0x50],rdi ; 0x1994c18  mov qword ptr [rbp+0x50],0xDCC | held-object slot; 0xDCC is the error-fill string ptr [I] |
| F1 rbp+0x58 | 8 (also 1) | R+W | 0x199479a  cmp byte ptr [rbp+0x58],1 ; 0x19947ad  mov [rbp+0x58],r12 ; 0x1994c27  mov [rbp+0x58],rax | held-object flag (byte tested, word stored) |
| F1 rbp+0x60 | 8 | W | 0x19947b1  mov qword ptr [rbp+0x60],1 | holder init constant [I] |
| F1 rbp+0x68 | 4 | W | 0x19947b9  mov dword ptr [rbp+0x68],0x40 | holder tag 0x40 [I] |
| F1 rbp+0x98 | 8 | W+R | 0x19945e9  mov [rbp+0x98],rbx ; 0x1994bd9  mov rcx,[rbp+0x98] | saved arg2 base (message source in error path) [I] |
| F1 rbp+0xa0 | 16 (also 8) | W | 0x199453b  movaps [rbp+0xA0],xmm0 ; 0x1994bf1  mov [rbp+0xA0],rdx | decoder argument block start [I] |
| F1 rbp+0xb0 | 16 (also 8) | W | 0x1994630  movups [rbp+0xB0],xmm6 ; 0x1994825  movups [rbp+0xB0],xmm6 ; 0x199492e  movups [rbp+0xB0],xmm6 ; 0x1994bf8  mov [rbp+0xB0],rax | stream-context init (data from 0xF0FF760 region) [I] |
| F1 rbp+0xc0 | 8 | W | 0x1994622  mov [rbp+0xC0],rax ; 0x199481e  mov [rbp+0xC0],rax ; 0x1994927  mov [rbp+0xC0],rax ; 0x1994c06  mov [rbp+0xC0],rax | stream-context field [I] |
| F1 rbp+0xc8 | 8 | W | 0x199463e  mov [rbp+0xC8],rax ; 0x1994833  mov [rbp+0xC8],rax ; 0x199493c  mov [rbp+0xC8],rax ; 0x1994c0d  mov qword ptr [rbp+0xC8],1 | stream-context field (1 = active) [I] |
| F1 rbp+0xd0 | 8 (also 4) | W | 0x199464f  mov [rbp+0xD0],rax ; 0x1994731  mov dword ptr [rbp+0xD0],0 ; 0x1994844  mov [rbp+0xD0],rax ; 0x199494d  mov [rbp+0xD0],rax ; 0x1994a25  mov dword ptr [rbp+0xD0],0 ; 0x1994a98  mov dword ptr [rbp+0xD0],0 | stream-context cursor/state [I] |
| F1 rbp+0xd8 | 1 | W | 0x1994742  mov byte ptr [rbp+0xD8],0 ; 0x1994a36  mov byte ptr [rbp+0xD8],0 ; 0x1994aa9  mov byte ptr [rbp+0xD8],0 | stream-context flag byte [I] |
| F1 rbp+0x158 | 4 | W+RW | 0x1994656  mov dword ptr [rbp+0x158],0 ; 0x1994717  add [rbp+0x158],eax ; 0x199484b  mov dword ptr [rbp+0x158],0 ; 0x1994907  add [rbp+0x158],eax ; 0x1994954  mov dword ptr [rbp+0x158],0 ; 0x1994a10  add [rbp+0x158],eax | stream position accumulator [I] |
| F1 rbp+0x160 | 8 (also 4) | W+R | 0x1994671  mov [rbp+0x160],r14 ; 0x199470b  mov eax,[rbp+0x160] ; 0x1994749  mov [rbp+0x160],r14 ; 0x199485c  mov [rbp+0x160],r14 ; 0x19948fb  mov eax,[rbp+0x160] ; 0x1994965  mov [rbp+0x160],r14 ; 0x1994a04  mov eax,[rbp+0x160] ; 0x1994a3d  mov [rbp+0x160],r14 ; 0x1994ab0  mov [rbp+0x160],r14 | read-cursor mark for position delta [I] |
| F1 rbp+0x168 | 8 | W | 0x1994750  mov [rbp+0x168],rax ; 0x1994a44  mov [rbp+0x168],rax ; 0x1994abe  mov [rbp+0x168],rax | stream-context field [I] |
| F1 rbp+0x170 | 8 (also 4) | W+R | 0x199466a  mov [rbp+0x170],r14 ; 0x1994711  sub eax,[rbp+0x170] ; 0x1994855  mov [rbp+0x170],r14 ; 0x1994901  sub eax,[rbp+0x170] ; 0x199495e  mov [rbp+0x170],r14 ; 0x1994a0a  sub eax,[rbp+0x170] | read-start mark for position delta [I] |
| F1 rbp+0x178 | 8 | W | 0x1994757  mov [rbp+0x178],rax ; 0x1994a4b  mov [rbp+0x178],rax ; 0x1994abe  mov [rbp+0x178],rax | stream-context field [I] |
| F1 rbp+0x180 | 8 | W | 0x1994699  mov [rbp+0x180],rdi ; 0x19947c7  mov [rbp+0x180],rbx ; 0x199488b  mov [rbp+0x180],rdi ; 0x1994994  mov [rbp+0x180],rdi ; 0x1994c32  mov [rbp+0x180],rax | descriptor key 1 (error fill reuses as string ptr) [I] |
| F1 rbp+0x188 | 8 | W | 0x19946a0  mov [rbp+0x188],r12 ; 0x19947ce  mov [rbp+0x188],r13 ; 0x1994892  mov [rbp+0x188],r12 ; 0x199499b  mov [rbp+0x188],r12 ; 0x1994c39  mov qword ptr [rbp+0x188],0x25 | descriptor key 2 (0x25 = msg length in error fill) [I] |
| F1 rbp+0x190 | 8 | W | 0x19946a7  mov qword ptr [rbp+0x190],1 ; 0x1994899  mov qword ptr [rbp+0x190],1 ; 0x19949a2  mov qword ptr [rbp+0x190],1 | descriptor kind = 1 [I] |
| F1 rbp+0x198 | 4 | W | 0x19946b2  mov dword ptr [rbp+0x198],0x26 ; 0x19948a4  mov dword ptr [rbp+0x198],0x26 ; 0x19949ad  mov dword ptr [rbp+0x198],0x26 | descriptor tag 0x26 |
| F1 rbp+0x1a0 | 16 (also 8) | W+R | 0x1994504  movaps [rbp+0x1A0],xmm0 ; 0x19945f0  movaps xmm0,[rbp+0x1A0] ; 0x19945f7  mov rcx,[rbp+0x1A0] ; 0x19945fe  mov qword ptr [rbp+0x1A0],0 ; 0x1994cf2  cmp qword ptr [rbp+0x1A0],0 ; 0x1994d39  mov rcx,[rbp+0x1A0] | decoder/stream object slot [I] |
| F1 rbp+0x1a8 | 8 | W+R | 0x1994610  mov qword ptr [rbp+0x1A8],0 ; 0x1994d1c  mov rcx,[rbp+0x1A8] | companion object slot [I] |
| F1 rbp+0x1b4 | 4 | W+R | 0x199476a  mov [rbp+0x1B4],eax ; 0x199480a  cmp dword ptr [rbp+0x1B4],0 ; 0x1994b7f  mov ecx,[rbp+0x1B4] | sniffer 0x764E50 verdict; byte-size shift count [I] |
| F1 rbp+0x1b8 | 4 | R | 0x19946fc  mov r15d,[rbp+0x1B8] ; 0x19948ed  mov edi,[rbp+0x1B8] ; 0x19949f6  mov edi,[rbp+0x1B8] | find-lookup result id (0xFFFFFFFF when failed) [I] |
| F1 rbp+0x1c0 | 8 | W | 0x19946bc  mov [rbp+0x1C0],r15 ; 0x19948ae  mov [rbp+0x1C0],rbx ; 0x19949b7  mov [rbp+0x1C0],rbx ; 0x1994a7b  mov [rbp+0x1C0],rax ; 0x1994aee  mov [rbp+0x1C0],rax | descriptor payload [I] |
| F1 rbp+0x1c8 | 8 | W | 0x19946c3  mov [rbp+0x1C8],r13 ; 0x19948bc  mov [rbp+0x1C8],rax ; 0x19949c5  mov [rbp+0x1C8],rax | descriptor payload [I] |
| F1 rbp+0x1d0 | 16 (also 8) | W+R | 0x1994609  movaps [rbp+0x1D0],xmm0 ; 0x1994770  mov r15,[rbp+0x1D0] ; 0x1994863  mov rcx,[rbp+0x1D0] ; 0x199496c  mov rcx,[rbp+0x1D0] ; 0x1994bac  cmp qword ptr [rbp+0x1D0],0 ; 0x1994c85  cmp qword ptr [rbp+0x1D0],0 ; 0x1994ccc  mov rcx,[rbp+0x1D0] | active stream cursor object [I] |
| F1 rbp+0x1d8 | 8 | R | 0x1994caf  mov rcx,[rbp+0x1D8] | held object for cleanup deref [I] |
| F1 rbp+0x1ec | 4 | W+R | 0x19944ed  mov dword ptr [rbp+0x1EC],0 ; 0x1994b22  mov r15d,[rbp+0x1EC] | decoded width (out to [rsi+4]) [I] |
| F1 rbp+0x1f0 | 4 | W+R | 0x19944f7  mov dword ptr [rbp+0x1F0],0 ; 0x1994b1b  mov r14d,[rbp+0x1F0] | decoded height (out to [rsi+8]) [I] |
| F1 rbp+0x1f4 | 4 | W+R | 0x19944e3  mov dword ptr [rbp+0x1F4],0 ; 0x1994afe  mov eax,[rbp+0x1F4] ; 0x1994b78  imul eax,[rbp+0x1F4] | decoded format id (bytes-per-pixel factor) [I] |
| F1 rbp+0x1f8 | 8 | W | 0x19944d2  mov qword ptr [rbp+0x1F8],0xFFFFFFFFFFFFFFFE | stack cookie init [I] |
| F1 rbp+0x200 | 16 | W+R | 0x19944cb  movaps [rbp+0x200],xmm6 ; 0x1994d58  movaps xmm6,[rbp+0x200] | xmm6 spill slot |
| F1 rsp+0x20 | 8 (also 4, 2) | W | 0x1994563  mov word ptr [rsp+0x20],0x121 ; 0x19945c2  mov [rsp+0x20],rax ; 0x199467f  mov [rsp+0x20],rax ; 0x19946d1  mov [rsp+0x20],rax ; 0x19947d9  mov [rsp+0x20],rax ; 0x1994871  mov [rsp+0x20],rax ; 0x19948c3  mov [rsp+0x20],r13 ; 0x199497a  mov [rsp+0x20],rax ; 0x19949cc  mov [rsp+0x20],r13 ; 0x1994a52  mov dword ptr [rsp+0x20],0 ; 0x1994ac5  mov dword ptr [rsp+0x20],0 ; 0x1994b91  mov [rsp+0x20],rax ; 0x1994c66  mov dword ptr [rsp+0x20],8 | stack argument slot (word 0x121 init, call args, log level 8) [I] |
| F1 rsp+0x28 | 8 (also 4) | W | 0x199455b  mov dword ptr [rsp+0x28],0 ; 0x1994b8c  mov [rsp+0x28],r12d ; 0x1994c59  mov [rsp+0x28],rax | stack argument slot [I] |
| F1 rsp+0x30 | 4 | W | 0x1994c5e  mov dword ptr [rsp+0x30],0xE4 | log string length for 0xF5DA1C7 [I] |
| F1 rsp+0x38 | 8 | W | 0x1994c4d  mov [rsp+0x38],r13 | stack argument (log string) [I] |
| F1 rsp+0x40 | 8 | W | 0x1994c48  mov [rsp+0x40],rax | stack argument (log string) [I] |
| F1 gs+0x58 | 8 | R | 0x199451e  mov rdx,gs:[0x58] ; 0x1994bc5  mov rcx,gs:[0x58] | TLS linear-array pointer (EH/security init) [I] |
| F1 rax+0x0 | 8 | R | 0x1994cbe  mov rax,[rax] ; 0x1994cdb  mov rax,[rax] ; 0x1994d2b  mov rax,[rax] ; 0x1994d48  mov rax,[rax] | deref in destructor chain [I] |
| F1 rax+0x8 | 8 | R | 0x1994550  mov rax,[rax+8] | init-guard global field [I] |
| F1 rax+0x40 | 1 | R | 0x19945df  cmp byte ptr [rax+0x40],1 ; 0x19946f0  cmp byte ptr [rax+0x40],0 ; 0x19948e2  cmp byte ptr [rax+0x40],0 ; 0x19949eb  cmp byte ptr [rax+0x40],0 | find-table entry match flag [I] |
| F1 rax+0xc98 | 8 | R | 0x1994bd2  mov rax,[rax+0xC98] | TLS/EH state field [I] |
| F1 rcx+0x0 | 8 | R | 0x1994be0  mov rcx,[rcx] ; 0x1994cbb  mov rax,[rcx] ; 0x1994cd8  mov rax,[rcx] ; 0x1994d28  mov rax,[rcx] ; 0x1994d45  mov rax,[rcx] | deref of guard global / held objects [I] |
| F1 rcx+0x4 | 4 | R | 0x199452b  cmp eax,[rcx+4] | init-guard global field [I] |
| F1 rdx+0x0 | 16 | R | 0x199450b  movups xmm0,[rdx] | arg2 16-byte by-value copy source |
| S1-S7 rsp+0x10 | 8 | W | 0x1994dc0  mov [rsp+0x10],rdx ; 0x1994e10  mov [rsp+0x10],rdx ; 0x1994e60  mov [rsp+0x10],rdx ; 0x1994eb0  mov [rsp+0x10],rdx ; 0x1994ee0  mov [rsp+0x10],rdx ; 0x1994f10  mov [rsp+0x10],rdx ; 0x1994f60  mov [rsp+0x10],rdx | home slot for incoming rdx (frame shared with F1) [I] |
| S1-S7 rsp+0x40 | 16 | W+R | 0x1994ddc  movaps [rsp+0x40],xmm6 ; 0x1994df0  movaps xmm6,[rsp+0x40] ; 0x1994e2c  movaps [rsp+0x40],xmm6 ; 0x1994e3d  movaps xmm6,[rsp+0x40] ; 0x1994e7c  movaps [rsp+0x40],xmm6 ; 0x1994e8d  movaps xmm6,[rsp+0x40] ; 0x1994ecc  movaps [rsp+0x40],xmm6 ; 0x1994efc  movaps [rsp+0x40],xmm6 ; 0x1994f2c  movaps [rsp+0x40],xmm6 ; 0x1994f46  movaps xmm6,[rsp+0x40] ; 0x1994f7c  movaps [rsp+0x40],xmm6 | xmm6 spill/restore (S4/S5/S7 store only) |
| S1 rbp+0x50 | 8 | R | 0x1994de7  mov rcx,[rbp+0x50] | held buffer passed to 0xEEC5A10 [I] |
| S1 rbp+0x58 | 1 | R | 0x1994de1  cmp byte ptr [rbp+0x58],1 | held-object flag [I] |
| F2 rdi+0x0 | 4 (also 8) | W+R | 0x1995480  mov [rdi],ebx ; 0x199565b  mov rdx,[rdi] ; 0x1995817  mov [rdi],eax | out image: format id (read back in tail) [I] |
| F2 rdi+0x4 | 8 (also 4) | W | 0x1995482  mov [rdi+4],r12d ; 0x1995819  mov [rdi+4],rdx | out image: width (qword store in container path) [I] |
| F2 rdi+0x8 | 4 | W | 0x1995486  mov [rdi+8],r14d | out image: height [I] |
| F2 rdi+0xc | 4 | W | 0x199548a  mov [rdi+0xC],r13d ; 0x199581d  mov dword ptr [rdi+0xC],0 | out image: field / zeroed in container path [I] |
| F2 rdi+0x10 | 2 (also 1) | W | 0x199548e  mov word ptr [rdi+0x10],1 ; 0x1995824  mov [rdi+0x10],cl | out image: flags word / byte cl=[rbp+0x110]+1 [I] |
| F2 rdi+0x11 | 1 | W | 0x1995827  mov byte ptr [rdi+0x11],0 | out image field zeroed |
| F2 rdi+0x18 | 8 | R+W | 0x19954a5  mov rax,[rdi+0x18] ; 0x19954b7  mov [rdi+0x18],rax ; 0x1995840  mov rax,[rdi+0x18] ; 0x1995856  mov [rdi+0x18],rax ; 0x1995999  mov [rdi+0x18],rax ; 0x19959b4  mov [rdi+0x18],rax | vtable slot, rewritten to 0x3C7B10 [I] |
| F2 rdi+0x20 | 8 | R+W | 0x1995494  mov rcx,[rdi+0x20] ; 0x1995498  mov qword ptr [rdi+0x20],0 ; 0x199582b  mov rcx,[rdi+0x20] ; 0x199582f  mov qword ptr [rdi+0x20],0 ; 0x199584b  mov rcx,[rdi+0x20] ; 0x1995869  mov [rdi+0x20],rax ; 0x19959ac  mov [rdi+0x20],rax | buffer ptr (old freed via import [0xF99FFA0], new = decoder obj) [I] |
| F2 rdi+0x28 | 8 | W | 0x19954bb  mov qword ptr [rdi+0x28],0 ; 0x199585a  mov qword ptr [rdi+0x28],0 ; 0x199599d  mov qword ptr [rdi+0x28],0 ; 0x19959bc  mov [rdi+0x28],rax | out image tail field [I] |
| F2 rbp-0x30 | 8 | W | 0x19952fa  mov [rbp-0x30],rax | decoder object ptr saved [I] |
| F2 rbp-0x20 | 8 | W+R | 0x1995358  mov qword ptr [rbp-0x20],0 ; 0x19953c8  mov [rbp-0x20],rax ; 0x199553a  mov qword ptr [rbp-0x20],0 ; 0x19955b9  mov qword ptr [rbp-0x20],0 ; 0x1995905  mov rax,[rbp-0x20] ; 0x1995912  mov qword ptr [rbp-0x20],0 ; 0x19959b0  mov rax,[rbp-0x20] ; 0x1995a3f  mov [rbp-0x20],rax | container reader state (0xE335C80 out) [I] |
| F2 rbp-0x18 | 16 (also 8) | W+R | 0x1995367  mov [rbp-0x18],rax ; 0x1995549  mov [rbp-0x18],rax ; 0x19955c8  mov [rbp-0x18],rax ; 0x19957b8  mov rcx,[rbp-0x18] ; 0x1995921  mov [rbp-0x18],rax ; 0x1995a34  movups [rbp-0x18],xmm0 | decoder object ptr; zeroed by movups in throw path [I] |
| F2 rbp-0x14 | 4 | R | 0x1995158  mov eax,[rbp-0x14] | header endianness magic 0x4030201/0x1020304 [I] |
| F2 rbp-0x10 | 8 | W+R | 0x1995088  mov qword ptr [rbp-0x10],0 ; 0x19950e9  mov qword ptr [rbp-0x10],0 ; 0x1995239  mov qword ptr [rbp-0x10],0 ; 0x19952a0  mov qword ptr [rbp-0x10],0 ; 0x19953d3  mov [rbp-0x10],rax ; 0x19959b8  mov rax,[rbp-0x10] | stream object slot [I] |
| F2 rbp-0x8 | 8 | W | 0x19953d7  mov qword ptr [rbp-8],1 | local flag [I] |
| F2 rbp+0x8 | 4 | R | 0x199516d  cmp dword ptr [rbp+8],0 | header field must be nonzero [I] |
| F2 rbp+0xc | 4 | R | 0x1995177  cmp dword ptr [rbp+0xC],0 | header field must be zero [I] |
| F2 rbp+0x10 | 4 | W+R | 0x1995090  mov dword ptr [rbp+0x10],0 ; 0x19950f1  mov dword ptr [rbp+0x10],0 ; 0x199518b  cmp dword ptr [rbp+0x10],0 ; 0x1995241  mov dword ptr [rbp+0x10],0 ; 0x19952a8  mov dword ptr [rbp+0x10],0 | header field / decoder out reset [I] |
| F2 rbp+0x14 | 4 | R | 0x1995181  cmp dword ptr [rbp+0x14],1 | header version must be 1 [I] |
| F2 rbp+0x98 | 4 | W | 0x1995097  mov dword ptr [rbp+0x98],0 ; 0x19950f8  mov dword ptr [rbp+0x98],0 ; 0x1995248  mov dword ptr [rbp+0x98],0 ; 0x19952af  mov dword ptr [rbp+0x98],0 | decoder out reset [I] |
| F2 rbp+0xa0 | 8 | W | 0x19950a8  mov [rbp+0xA0],r12 ; 0x1995109  mov [rbp+0xA0],r12 ; 0x1995259  mov [rbp+0xA0],r12 ; 0x19952c0  mov [rbp+0xA0],r12 | stream cursor (data ptr) [I] |
| F2 rbp+0xa8 | 8 | W | 0x19950b9  mov [rbp+0xA8],r15 ; 0x1995117  mov [rbp+0xA8],r15 ; 0x1995267  mov [rbp+0xA8],r15 ; 0x19952ce  mov [rbp+0xA8],r15 | stream end (data ptr + size) [I] |
| F2 rbp+0xb0 | 8 | W | 0x19950a1  mov [rbp+0xB0],r12 ; 0x1995102  mov [rbp+0xB0],r12 ; 0x1995252  mov [rbp+0xB0],r12 ; 0x19952b9  mov [rbp+0xB0],r12 | stream cursor copy [I] |
| F2 rbp+0xb8 | 8 | W | 0x19950b2  mov [rbp+0xB8],r15 ; 0x1995110  mov [rbp+0xB8],r15 ; 0x1995260  mov [rbp+0xB8],r15 ; 0x19952c7  mov [rbp+0xB8],r15 | stream end copy [I] |
| F2 rbp+0xc0 | 8 | W | 0x1994fe9  mov qword ptr [rbp+0xC0],0 | decoded-image out slot init [I] |
| F2 rbp+0xc5 | 8 | W | 0x1994ff4  mov qword ptr [rbp+0xC5],0 | unaligned zero fill of decoded-image slot [I] |
| F2 rbp+0xc8 | 4 | R | 0x19951d2  mov ebx,[rbp+0xC8] | decoded format id [I] |
| F2 rbp+0xd0 | 8 (also 4) | W+R | 0x1994fd4  mov qword ptr [rbp+0xD0],0 ; 0x19951d8  mov eax,[rbp+0xD0] ; 0x1995704  mov eax,[rbp+0xD0] ; 0x199574a  mov eax,[rbp+0xD0] ; 0x1995789  mov eax,[rbp+0xD0] | decoded width [I] |
| F2 rbp+0xd4 | 4 | R | 0x19951fa  mov edx,[rbp+0xD4] ; 0x1995710  mov edx,[rbp+0xD4] ; 0x1995756  mov edx,[rbp+0xD4] ; 0x1995795  mov edx,[rbp+0xD4] | decoded height [I] |
| F2 rbp+0xd8 | 4 | W | 0x1994fdf  mov dword ptr [rbp+0xD8],0 | decoded-image slot init [I] |
| F2 rbp+0xe0 | 8 | W+R | 0x1994fc9  mov qword ptr [rbp+0xE0],0 ; 0x199564f  mov rdi,[rbp+0xE0] | decoded image object (freed in tail 0x199564F) [I] |
| F2 rbp+0xe8 | 8 | W | 0x19953f8  mov [rbp+0xE8],rax ; 0x199589e  mov [rbp+0xE8],rax ; 0x19959e7  mov [rbp+0xE8],rax | log string ptr [I] |
| F2 rbp+0xf0 | 8 | W | 0x19953ff  mov qword ptr [rbp+0xF0],0x2E ; 0x19958a5  mov qword ptr [rbp+0xF0],0x1B ; 0x19959ee  mov qword ptr [rbp+0xF0],0x19 | log string length [I] |
| F2 rbp+0xf8 | 8 | W | 0x1995372  mov [rbp+0xF8],rax ; 0x19953df  mov qword ptr [rbp+0xF8],0xDC ; 0x1995554  mov [rbp+0xF8],rax ; 0x19955d3  mov [rbp+0xF8],rax ; 0x1995881  mov qword ptr [rbp+0xF8],0 ; 0x199592c  mov [rbp+0xF8],rax ; 0x19959ca  mov qword ptr [rbp+0xF8],0 | log site id / string ptr [I] |
| F2 rbp+0x100 | 8 | W | 0x1995379  mov qword ptr [rbp+0x100],0x38 ; 0x19953ea  mov [rbp+0x100],r14 ; 0x199555b  mov qword ptr [rbp+0x100],0x2C ; 0x19955da  mov qword ptr [rbp+0x100],0x47 ; 0x1995890  mov [rbp+0x100],rax ; 0x1995933  mov qword ptr [rbp+0x100],0x19 ; 0x19959d9  mov [rbp+0x100],rax | log string length [I] |
| F2 rbp+0x10c | 4 | W+R | 0x1995050  mov dword ptr [rbp+0x10C],0 ; 0x19951de  mov dword ptr [rbp+0x10C],0 ; 0x199528c  cmp dword ptr [rbp+0x10C],3 ; 0x199530c  mov [rbp+0x10C],r13d ; 0x19954cf  imul r13d,[rbp+0x10C] ; 0x1995507  mov ebx,[rbp+0x10C] ; 0x19956e8  mov dword ptr [rbp+0x10C],0 ; 0x199572e  mov dword ptr [rbp+0x10C],0 ; 0x199576d  mov dword ptr [rbp+0x10C],0 ; 0x19957ea  mov eax,[rbp+0x10C] | decoded format id (drives jt 0xF0FFB98 and byte size) [I] |
| F2 rbp+0x110 | 1 | W+R | 0x19951e8  mov byte ptr [rbp+0x110],0 ; 0x19956f2  mov byte ptr [rbp+0x110],0 ; 0x1995738  mov byte ptr [rbp+0x110],0 ; 0x1995777  mov byte ptr [rbp+0x110],0 ; 0x1995807  movzx ecx,byte ptr [rbp+0x110] | decoder channel/flag byte ([rdi+0x10] = cl+1) [I] |
| F2 rbp+0x114 | 8 | W+R | 0x19951ef  mov qword ptr [rbp+0x114],0 ; 0x19956f9  mov qword ptr [rbp+0x114],0 ; 0x199573f  mov qword ptr [rbp+0x114],0 ; 0x199577e  mov qword ptr [rbp+0x114],0 ; 0x1995810  mov rdx,[rbp+0x114] | decoded buffer ptr (stored to [rdi+4]) [I] |
| F2 rbp+0x11c | 4 | W+R | 0x199505a  mov dword ptr [rbp+0x11C],0 ; 0x1995336  mov r12d,[rbp+0x11C] ; 0x1995479  mov r12d,[rbp+0x11C] | decoded width (out to [rdi+4]) [I] |
| F2 rbp+0x120 | 8 | W+R | 0x199502f  mov [rbp+0x120],r13 ; 0x1995327  mov r13,[rbp+0x120] ; 0x1995453  mov r13,[rbp+0x120] ; 0x19954f6  mov r13,[rbp+0x120] ; 0x1995515  mov r13,[rbp+0x120] ; 0x1995627  mov r13,[rbp+0x120] ; 0x19957d2  mov [rbp+0x120],rcx ; 0x1995862  mov rax,[rbp+0x120] ; 0x19958f9  mov rcx,[rbp+0x120] ; 0x19959a5  mov rax,[rbp+0x120] | status-object ptr (saved rcx arg) / decoder obj in container path [I] |
| F2 rbp+0x12c | 4 | W+R | 0x1995064  mov dword ptr [rbp+0x12C],0 ; 0x1995349  mov eax,[rbp+0x12C] ; 0x199546c  mov r14d,[rbp+0x12C] ; 0x19956d9  mov [rbp+0x12C],r12d | decoded height (h=w in square path) [I] |
| F2 rbp+0x130 | 8 | W | 0x1994fab  mov qword ptr [rbp+0x130],0xFFFFFFFFFFFFFFFE | stack cookie init [I] |
| F2 rbp+0x1a0 | 8 | R | 0x1994fc2  mov r15,[rbp+0x1A0] | home slot of 6th argument = byte size [I] |
| F2 rbp+0x1a8 | 1 | R | 0x1995313  movzx ecx,byte ptr [rbp+0x1A8] | direct-vs-decode flag byte [I] |
| F2 rsp+0x20 | 8 (also 4) | W | 0x199511e  mov [rsp+0x20],r13d ; 0x19952d5  mov [rsp+0x20],r13d ; 0x1995436  mov dword ptr [rsp+0x20],8 ; 0x19954de  mov [rsp+0x20],rax ; 0x199558b  mov dword ptr [rsp+0x20],8 ; 0x199560a  mov dword ptr [rsp+0x20],8 ; 0x19957bc  mov dword ptr [rsp+0x20],0 ; 0x19958dc  mov dword ptr [rsp+0x20],8 ; 0x1995963  mov dword ptr [rsp+0x20],8 | stack args (decoder dword arg, log level 8, null) [I] |
| F2 rsp+0x28 | 8 (also 4) | W | 0x199539c  mov [rsp+0x28],rax ; 0x1995429  mov [rsp+0x28],rax ; 0x19954da  mov [rsp+0x28],ebx ; 0x199557e  mov [rsp+0x28],rax ; 0x19955fd  mov [rsp+0x28],rax ; 0x19958cf  mov [rsp+0x28],rax ; 0x1995956  mov [rsp+0x28],rax ; 0x1995a18  mov [rsp+0x28],rax | stack args (log string ptr, ebx format) [I] |
| F2 rsp+0x30 | 4 | W | 0x19953a1  mov dword ptr [rsp+0x30],0x1A4 ; 0x199542e  mov dword ptr [rsp+0x30],0x1C4 ; 0x1995583  mov dword ptr [rsp+0x30],0x1A0 ; 0x1995602  mov dword ptr [rsp+0x30],0x1AB ; 0x19958d4  mov dword ptr [rsp+0x30],0x10C ; 0x199595b  mov dword ptr [rsp+0x30],0x104 ; 0x1995a1d  mov dword ptr [rsp+0x30],0x11D | log line numbers [I] |
| F2 rsp+0x38 | 8 | W | 0x1995390  mov [rsp+0x38],rax ; 0x199541d  mov [rsp+0x38],rax ; 0x1995572  mov [rsp+0x38],rax ; 0x19955f1  mov [rsp+0x38],rax ; 0x19958c3  mov [rsp+0x38],rax ; 0x199594a  mov [rsp+0x38],rax ; 0x1995a0c  mov [rsp+0x38],rax | log string ptr [I] |
| F2 rsp+0x40 | 8 | W | 0x1995384  mov [rsp+0x40],r14 ; 0x1995411  mov [rsp+0x40],rax ; 0x1995566  mov [rsp+0x40],r14 ; 0x19955e5  mov [rsp+0x40],r14 ; 0x19958b7  mov [rsp+0x40],rax ; 0x199593e  mov [rsp+0x40],r14 ; 0x1995a00  mov [rsp+0x40],rax | log string ptr [I] |
| F2 r12+0x0 | 8 | R | 0x1995010  mov rax,[r12] | container magic dword 1 (xored with data at 0xF4DE65C) |
| F2 r12+0x8 | 4 | R | 0x199501b  mov ecx,[r12+8] | container magic dword 2 (xored with data at 0xF4DE664) |
| F2 rax+0x10 | 8 | R | 0x199566d  mov rax,[rax+0x10] | interface fn ptr for decoded-image free [I] |
| F2 rax+0xc98 | 8 | R | 0x19953c1  mov rax,[rax+0xC98] | TLS/EH state field [I] |
| F2 rcx+0x0 | 8 | R | 0x199566a  mov rax,[rcx] | decoded-image object deref before interface free [I] |
| F2 gs+0x58 | 8 | R | 0x19953b4  mov rcx,gs:[0x58] | TLS linear-array pointer (EH frame registration) [I] |

## OPEN QUESTIONS

- [UNVERIFIED: 0x19944d2 question] whether [rbp+0x1F8] = -2 is the /GS stack cookie or a scoped EH state var; both patterns store -2 in this codebase [I].

## TOOL REQUESTS

- Temp\opencode\ocimg_fill.py | modes bounds/fill/sites: prints chunk RVAs, splices @@BLOCK markers with verbatim listing lines, extracts [reg+off] sites with sizes | avoided hand-transcription of 1126 listing lines.



## F2 imageutils_loadImageFromMemory 0x1994F90..0x1995A53

Decoder front-end [I]: r13 = status out (rcx), rdi = image out (rdx), ebx = format id (r8d), r12 = data pointer (r9), r15 = byte size loaded from the home slot [rbp+0x1A0]. Checks a 12-byte container magic, otherwise falls back to sniffing/decoding through 0x7647C0/0x764950; the container path uses reader 0xE335C80 and decoder 0xE336840/0x9144720, with logging through 0x3CF160 on every failure.

#### Phase 1 0x1994f90..0x1995046: Prologue: frame rbp=rsp+0x80, cookie -2 at [rbp+0x130], register args r12=r9, ebx=r8d, rdi=rdx, r13=rcx, size r15=[rbp+0x1A0], and zeroes the pending-output locals [rbp+0xE0/0xD0/0xD8/0xC0/0xC5] [V]. Rejects tiny/null inputs (r9==0 or r15<0x40) unless the 12-byte container magic matches: [r12] xored against absolute data 0xF4DE65C and [r12+8] against 0xF4DE664 [V].
```
0x1994f90  push rbp
0x1994f91  push r15
0x1994f93  push r14
0x1994f95  push r13
0x1994f97  push r12
0x1994f99  push rsi
0x1994f9a  push rdi
0x1994f9b  push rbx
0x1994f9c  sub rsp,0x1B8
0x1994fa3  lea rbp,[rsp+0x80]
0x1994fab  mov qword ptr [rbp+0x130],0xFFFFFFFFFFFFFFFE
0x1994fb6  mov r12,r9
0x1994fb9  mov ebx,r8d
0x1994fbc  mov rdi,rdx
0x1994fbf  mov r13,rcx
0x1994fc2  mov r15,[rbp+0x1A0]
0x1994fc9  mov qword ptr [rbp+0xE0],0
0x1994fd4  mov qword ptr [rbp+0xD0],0
0x1994fdf  mov dword ptr [rbp+0xD8],0
0x1994fe9  mov qword ptr [rbp+0xC0],0
0x1994ff4  mov qword ptr [rbp+0xC5],0
0x1994fff  test r9,r9
0x1995002  sete al
0x1995005  cmp r15,0x40
0x1995009  setb cl
0x199500c  or cl,al
0x199500e  jne short 0x199502F
0x1995010  mov rax,[r12]
0x1995014  xor rax,[0xF4DE65C]
0x199501b  mov ecx,[r12+8]
0x1995020  xor ecx,[0xF4DE664]
0x1995026  or rcx,rax
0x1995029  je 0x1995148
0x199502f  mov [rbp+0x120],r13
0x1995036  xor r13d,r13d
0x1995039  mov sil,1
0x199503c  cmp ebx,4
0x199503f  ja short 0x1995050
0x1995041  mov eax,0x1A
0x1995046  bt eax,ebx
```

#### Phase 2 0x1995049..0x1995123: Generic path: zeroes decoder outs [rbp+0x10C/0x11C/0x12C], filters the requested format with bt eax(0x1A),ebx (only ids 1,3,4 pass) [V]. Initializes the stream state (cursor/end [rbp+0xB0]=r12, [rbp+0xB8]=r15 and [rbp+0xA0]=r12, [rbp+0xA8]=r15) and calls decoder 0x7647C0 with the format id on the stack [I].
```
0x1995049  jae short 0x1995050
0x199504b  xor esi,esi
0x199504d  mov r13d,ebx
0x1995050  mov dword ptr [rbp+0x10C],0
0x199505a  mov dword ptr [rbp+0x11C],0
0x1995064  mov dword ptr [rbp+0x12C],0
0x199506e  movsxd rax,r15d
0x1995071  cmp rax,r15
0x1995074  jne 0x1995A31
0x199507a  mov eax,r15d
0x199507d  and eax,0x80000000
0x1995082  jne 0x1995A31
0x1995088  mov qword ptr [rbp-0x10],0
0x1995090  mov dword ptr [rbp+0x10],0
0x1995097  mov dword ptr [rbp+0x98],0
0x19950a1  mov [rbp+0xB0],r12
0x19950a8  mov [rbp+0xA0],r12
0x19950af  add r15,r12
0x19950b2  mov [rbp+0xB8],r15
0x19950b9  mov [rbp+0xA8],r15
0x19950c0  lea r14,[rbp-0x20]
0x19950c4  mov rcx,r14
0x19950c7  call 0x764E50
0x19950cc  test sil,sil
0x19950cf  je short 0x19950E1
0x19950d1  test eax,eax
0x19950d3  je 0x1995239
0x19950d9  mov r13d,3
0x19950df  jmp short 0x19950E9
0x19950e1  test eax,eax
0x19950e3  je 0x19952A0
0x19950e9  mov qword ptr [rbp-0x10],0
0x19950f1  mov dword ptr [rbp+0x10],0
0x19950f8  mov dword ptr [rbp+0x98],0
0x1995102  mov [rbp+0xB0],r12
0x1995109  mov [rbp+0xA0],r12
0x1995110  mov [rbp+0xB8],r15
0x1995117  mov [rbp+0xA8],r15
0x199511e  mov [rsp+0x20],r13d
0x1995123  lea rcx,[rbp-0x20]
```

#### Phase 3 0x1995127..0x19951d2: Second generic variant through decoder 0x764950 (dword stack argument), then the container path: reader 0xE335C80 parses the header into [rbp-0x20..], checking endianness magic [rbp-0x14] against 0x4030201/0x1020304 and requiring [rbp+8] nonzero, [rbp+0xC]==0, [rbp+0x14]==1, [rbp+0x10]==0 [V/I].
```
0x1995127  lea rdx,[rbp+0x11C]
0x199512e  lea r8,[rbp+0x12C]
0x1995135  lea r9,[rbp+0x10C]
0x199513c  call 0x764950
0x1995141  xor edx,edx
0x1995143  jmp 0x19952FA
0x1995148  lea r14,[rbp-0x20]
0x199514c  mov rcx,r14
0x199514f  mov rdx,r12
0x1995152  call 0xE335C80
0x1995157  nop
0x1995158  mov eax,[rbp-0x14]
0x199515b  cmp eax,0x4030201
0x1995160  je short 0x199516D
0x1995162  cmp eax,0x1020304
0x1995167  jne 0x199502F
0x199516d  cmp dword ptr [rbp+8],0
0x1995171  je 0x199502F
0x1995177  cmp dword ptr [rbp+0xC],0
0x199517b  jne 0x199502F
0x1995181  cmp dword ptr [rbp+0x14],1
0x1995185  jne 0x199502F
0x199518b  cmp dword ptr [rbp+0x10],0
0x199518f  jne 0x199502F
0x1995195  lea rcx,[rbp+0xE0]
0x199519c  lea rdx,[rbp+0xC0]
0x19951a3  mov r8,r12
0x19951a6  mov r9,r15
0x19951a9  call 0xE336840
0x19951ae  nop
0x19951af  test al,al
0x19951b1  je 0x199502F
0x19951b7  cmp ebx,4
0x19951ba  ja 0x1995912
0x19951c0  mov eax,ebx
0x19951c2  lea rcx,[0xF0FFB74]
0x19951c9  movsxd rax,[rcx+rax*4]
0x19951cd  add rax,rcx
0x19951d0  jmp rax
0x19951d2  mov ebx,[rbp+0xC8]
```

#### Phase 4 0x19951d8..0x19952af: Reads decoded dimensions ([rbp+0xC8] format, [rbp+0xD0] width, [rbp+0xD4] height) with a cmp 1/adc-0 clamp, resets [rbp+0x10C/0x110/0x114] and dispatches bytes-per-pixel via jump table 0xF0FFB88 on ebx-1 (x1/x2/x3/x4 multipliers) [V]. Runs format probe 0x766600 (r13d = 4 when [rbp+0x10C]==3 and al set, else (cl&al)<<2) and decoder 0x7647C0 [I].
```
0x19951d8  mov eax,[rbp+0xD0]
0x19951de  mov dword ptr [rbp+0x10C],0
0x19951e8  mov byte ptr [rbp+0x110],0
0x19951ef  mov qword ptr [rbp+0x114],0
0x19951fa  mov edx,[rbp+0xD4]
0x1995200  cmp eax,1
0x1995203  adc eax,0
0x1995206  cmp edx,1
0x1995209  adc edx,0
0x199520c  lea ecx,[rbx-1]
0x199520f  cmp ecx,3
0x1995212  ja 0x1995A2A
0x1995218  lea r8,[0xF0FFB88]
0x199521f  movsxd rcx,[r8+rcx*4]
0x1995223  add rcx,r8
0x1995226  jmp rcx
0x1995228  imul rdx,rax
0x199522c  add rdx,rdx
0x199522f  mov ebx,2
0x1995234  jmp 0x19957AE
0x1995239  mov qword ptr [rbp-0x10],0
0x1995241  mov dword ptr [rbp+0x10],0
0x1995248  mov dword ptr [rbp+0x98],0
0x1995252  mov [rbp+0xB0],r12
0x1995259  mov [rbp+0xA0],r12
0x1995260  mov [rbp+0xB8],r15
0x1995267  mov [rbp+0xA8],r15
0x199526e  lea rcx,[rbp-0x20]
0x1995272  lea rdx,[rbp+0x11C]
0x1995279  lea r8,[rbp+0x12C]
0x1995280  lea r9,[rbp+0x10C]
0x1995287  call 0x766600
0x199528c  cmp dword ptr [rbp+0x10C],3
0x1995293  sete cl
0x1995296  and cl,al
0x1995298  movzx r13d,cl
0x199529c  shl r13d,2
0x19952a0  mov qword ptr [rbp-0x10],0
0x19952a8  mov dword ptr [rbp+0x10],0
0x19952af  mov dword ptr [rbp+0x98],0
```

#### Phase 5 0x19952b9..0x1995390: Rebuilds the stream state for the decode attempt (cursor/end pairs at [rbp+0xB0/0xB8] and [rbp+0xA0/0xA8]) and calls decoder 0x764950 with r13d on the stack [V]. Saves the decoder object at [rbp-0x30]/[rbp-0x18] and prepares a null-decoder log through 0x3CF160 (string length 0x38 at [rbp+0x100], line 0xDC) [I].
```
0x19952b9  mov [rbp+0xB0],r12
0x19952c0  mov [rbp+0xA0],r12
0x19952c7  mov [rbp+0xB8],r15
0x19952ce  mov [rbp+0xA8],r15
0x19952d5  mov [rsp+0x20],r13d
0x19952da  lea rcx,[rbp-0x20]
0x19952de  lea rdx,[rbp+0x11C]
0x19952e5  lea r8,[rbp+0x12C]
0x19952ec  lea r9,[rbp+0x10C]
0x19952f3  call 0x7647C0
0x19952f8  mov dl,1
0x19952fa  mov [rbp-0x30],rax
0x19952fe  test rax,rax
0x1995301  je 0x19953AE
0x1995307  test r13d,r13d
0x199530a  je short 0x1995313
0x199530c  mov [rbp+0x10C],r13d
0x1995313  movzx ecx,byte ptr [rbp+0x1A8]
0x199531a  mov esi,1
0x199531f  test ebx,ebx
0x1995321  je 0x1995507
0x1995327  mov r13,[rbp+0x120]
0x199532e  test cl,cl
0x1995330  je 0x199546C
0x1995336  mov r12d,[rbp+0x11C]
0x199533d  mov r15,rax
0x1995340  test r12d,r12d
0x1995343  je 0x199553A
0x1995349  mov eax,[rbp+0x12C]
0x199534f  cmp eax,r12d
0x1995352  jge 0x19955AD
0x1995358  mov qword ptr [rbp-0x20],0
0x1995360  lea rax,[rbp+0xE8]
0x1995367  mov [rbp-0x18],rax
0x199536b  lea rax,[0xF5AEC4C]
0x1995372  mov [rbp+0xF8],rax
0x1995379  mov qword ptr [rbp+0x100],0x38
0x1995384  mov [rsp+0x40],r14
0x1995389  lea rax,[rbp+0xF8]
0x1995390  mov [rsp+0x38],rax
```

#### Phase 6 0x1995395..0x1995486: Null-decoder branch: logs with level 8 (strings at [rbp+0xF8]=0xDC, [rbp+0xF0]=0x2E, line 0x1A4, TLS via gs:[0x58] and [rax+0xC98]) and sets status 2 [V]. Then the direct path 0x199546C: loads width r12d=[rbp+0x11C], height r14d=[rbp+0x12C] and starts writing the image out object ([rdi]=format, [rdi+4], [rdi+8]) [I].
```
0x1995395  lea rax,[0xF518FA5]
0x199539c  mov [rsp+0x28],rax
0x19953a1  mov dword ptr [rsp+0x30],0x1A4
0x19953a9  jmp 0x199558B
0x19953ae  mov eax,[0x128767C8]
0x19953b4  mov rcx,gs:[0x58]
0x19953bd  mov rax,[rcx+rax*8]
0x19953c1  mov rax,[rax+0xC98]
0x19953c8  mov [rbp-0x20],rax
0x19953cc  lea rax,[0xF000628]
0x19953d3  mov [rbp-0x10],rax
0x19953d7  mov qword ptr [rbp-8],1
0x19953df  mov qword ptr [rbp+0xF8],0xDC
0x19953ea  mov [rbp+0x100],r14
0x19953f1  lea rax,[0xF50D4CB]
0x19953f8  mov [rbp+0xE8],rax
0x19953ff  mov qword ptr [rbp+0xF0],0x2E
0x199540a  lea rax,[rbp+0xF8]
0x1995411  mov [rsp+0x40],rax
0x1995416  lea rax,[rbp+0xE8]
0x199541d  mov [rsp+0x38],rax
0x1995422  lea rax,[0xF518FA5]
0x1995429  mov [rsp+0x28],rax
0x199542e  mov dword ptr [rsp+0x30],0x1C4
0x1995436  mov dword ptr [rsp+0x20],8
0x199543e  xor ecx,ecx
0x1995440  mov edx,1
0x1995445  xor r8d,r8d
0x1995448  mov r9d,0xF
0x199544e  call 0x3CF160
0x1995453  mov r13,[rbp+0x120]
0x199545a  mov byte ptr [r13+0x10],0
0x199545f  mov dword ptr [r13],2
0x1995467  jmp 0x1995644
0x199546c  mov r14d,[rbp+0x12C]
0x1995473  mov r13d,1
0x1995479  mov r12d,[rbp+0x11C]
0x1995480  mov [rdi],ebx
0x1995482  mov [rdi+4],r12d
0x1995486  mov [rdi+8],r14d
```

#### Phase 7 0x199548a..0x199553a: Finishes the out-object fields ([rdi+0xC]=r13d, word [rdi+0x10]=1), frees the old +0x20 buffer through import [0xF99FFA0] and sets the 0x3C7B10 vtable at [rdi+0x18] [V]. Computes size 1*w*h*[rbp+0x10C], allocates via 0x1993EB0, sets status [r13+0x10]=1; height==0 diverts to the log at 0x199553A [I].
```
0x199548a  mov [rdi+0xC],r13d
0x199548e  mov word ptr [rdi+0x10],1
0x1995494  mov rcx,[rdi+0x20]
0x1995498  mov qword ptr [rdi+0x20],0
0x19954a0  test rcx,rcx
0x19954a3  je short 0x19954B0
0x19954a5  mov rax,[rdi+0x18]
0x19954a9  call qword ptr [0xF99FFA0]
0x19954af  nop
0x19954b0  lea rax,[0x3C7B10]
0x19954b7  mov [rdi+0x18],rax
0x19954bb  mov qword ptr [rdi+0x28],0
0x19954c3  imul r13d,esi
0x19954c7  imul r13d,r12d
0x19954cb  imul r13d,r14d
0x19954cf  imul r13d,[rbp+0x10C]
0x19954d7  movsxd rax,r13d
0x19954da  mov [rsp+0x28],ebx
0x19954de  mov [rsp+0x20],rax
0x19954e3  lea rdx,[rbp-0x30]
0x19954e7  mov rcx,rdi
0x19954ea  mov r8d,r12d
0x19954ed  mov r9d,r14d
0x19954f0  call 0x1993EB0
0x19954f5  nop
0x19954f6  mov r13,[rbp+0x120]
0x19954fd  mov byte ptr [r13+0x10],1
0x1995502  jmp 0x199564F
0x1995507  mov ebx,[rbp+0x10C]
0x199550d  lea r8d,[rbx-1]
0x1995511  cmp r8d,3
0x1995515  mov r13,[rbp+0x120]
0x199551c  ja 0x19956CC
0x1995522  lea r9,[0xF0FFB98]
0x1995529  movsxd r8,[r9+r8*4]
0x199552d  add r8,r9
0x1995530  jmp r8
0x1995533  mov esi,ebx
0x1995535  jmp 0x199532E
0x199553a  mov qword ptr [rbp-0x20],0
```

#### Phase 8 0x1995542..0x1995622: Height sanity logging: h==0 logs string 0xF57E729 (len 0x2C, line 0x1A0); the h>=w divisibility check idiv at 0x19955AD logs string 0xF5AEC04 (len 0x47, line 0x1AB) on nonzero remainder, then frees the decoder through import [0xF9A6F98] and returns status 1 [V/I].
```
0x1995542  lea rax,[rbp+0xE8]
0x1995549  mov [rbp-0x18],rax
0x199554d  lea rax,[0xF57E729]
0x1995554  mov [rbp+0xF8],rax
0x199555b  mov qword ptr [rbp+0x100],0x2C
0x1995566  mov [rsp+0x40],r14
0x199556b  lea rax,[rbp+0xF8]
0x1995572  mov [rsp+0x38],rax
0x1995577  lea rax,[0xF518FA5]
0x199557e  mov [rsp+0x28],rax
0x1995583  mov dword ptr [rsp+0x30],0x1A0
0x199558b  mov dword ptr [rsp+0x20],8
0x1995593  xor ecx,ecx
0x1995595  mov edx,1
0x199559a  xor r8d,r8d
0x199559d  mov r9d,0xF
0x19955a3  call 0x3CF160
0x19955a8  jmp 0x199562E
0x19955ad  cdq
0x19955ae  idiv r12d
0x19955b1  test edx,edx
0x19955b3  je 0x19956D6
0x19955b9  mov qword ptr [rbp-0x20],0
0x19955c1  lea rax,[rbp+0xE8]
0x19955c8  mov [rbp-0x18],rax
0x19955cc  lea rax,[0xF5AEC04]
0x19955d3  mov [rbp+0xF8],rax
0x19955da  mov qword ptr [rbp+0x100],0x47
0x19955e5  mov [rsp+0x40],r14
0x19955ea  lea rax,[rbp+0xF8]
0x19955f1  mov [rsp+0x38],rax
0x19955f6  lea rax,[0xF518FA5]
0x19955fd  mov [rsp+0x28],rax
0x1995602  mov dword ptr [rsp+0x30],0x1AB
0x199560a  mov dword ptr [rsp+0x20],8
0x1995612  xor ecx,ecx
0x1995614  mov edx,1
0x1995619  xor r8d,r8d
0x199561c  mov r9d,0xF
0x1995622  call 0x3CF160
```

#### Phase 9 0x1995627..0x19956ba: Square-image path and common tail 0x199564F: reloads r13=[rbp+0x120], frees the decoded image at [rbp+0xE0] through interface table [0x1233E1A8] (call via [rax+0x10]) plus 0xE935700(edx=0x10) [V]. Format-override paths 0x199569C/0x19956BA recompute ebx from the override byte (esi=2-ebx', ebx=5^dl or 2*dl+3) [I].
```
0x1995627  mov r13,[rbp+0x120]
0x199562e  mov rcx,r15
0x1995631  call qword ptr [0xF9A6F98]
0x1995637  mov byte ptr [r13+0x10],0
0x199563c  mov dword ptr [r13],1
0x1995644  lea rax,[0xF0FF740]
0x199564b  mov [r13+8],rax
0x199564f  mov rdi,[rbp+0xE0]
0x1995656  test rdi,rdi
0x1995659  je short 0x1995685
0x199565b  mov rdx,[rdi]
0x199565e  test rdx,rdx
0x1995661  je short 0x1995678
0x1995663  mov rcx,[0x1233E1A8]
0x199566a  mov rax,[rcx]
0x199566d  mov rax,[rax+0x10]
0x1995671  call qword ptr [0xF99FFA0]
0x1995677  nop
0x1995678  mov edx,0x10
0x199567d  mov rcx,rdi
0x1995680  call 0xE935700
0x1995685  mov rax,r13
0x1995688  add rsp,0x1B8
0x199568f  pop rbx
0x1995690  pop rdi
0x1995691  pop rsi
0x1995692  pop r12
0x1995694  pop r13
0x1995696  pop r14
0x1995698  pop r15
0x199569a  pop rbp
0x199569b  ret
0x199569c  movzx r8d,dl
0x19956a0  xor dl,1
0x19956a3  movzx edx,dl
0x19956a6  lea ebx,[rdx*2+3]
0x19956ad  mov esi,2
0x19956b2  sub esi,r8d
0x19956b5  jmp 0x199532E
0x19956ba  movzx ebx,dl
```

#### Phase 10 0x19956bd..0x199578f: Square path assigns h=w ([rbp+0x12C]=r12d); the byte-size switch rewrites [rbp+0x10C]=1/2/3/4 per case with byte [rbp+0x110]=0 and [rbp+0x114]=0, recomputing the multiplier from [rbp+0xD0]/[rbp+0xD4] (lea x3, shl x4) and jumping to 0x19957AE [V].
```
0x19956bd  mov esi,2
0x19956c2  sub esi,ebx
0x19956c4  xor ebx,5
0x19956c7  jmp 0x199532E
0x19956cc  mov ebx,4
0x19956d1  jmp 0x199532E
0x19956d6  mov r13d,eax
0x19956d9  mov [rbp+0x12C],r12d
0x19956e0  mov r14d,r12d
0x19956e3  jmp 0x1995480
0x19956e8  mov dword ptr [rbp+0x10C],0
0x19956f2  mov byte ptr [rbp+0x110],0
0x19956f9  mov qword ptr [rbp+0x114],0
0x1995704  mov eax,[rbp+0xD0]
0x199570a  cmp eax,1
0x199570d  adc eax,0
0x1995710  mov edx,[rbp+0xD4]
0x1995716  cmp edx,1
0x1995719  adc edx,0
0x199571c  imul rdx,rax
0x1995720  lea rdx,[rdx+rdx*2]
0x1995724  mov ebx,3
0x1995729  jmp 0x19957AE
0x199572e  mov dword ptr [rbp+0x10C],0
0x1995738  mov byte ptr [rbp+0x110],0
0x199573f  mov qword ptr [rbp+0x114],0
0x199574a  mov eax,[rbp+0xD0]
0x1995750  cmp eax,1
0x1995753  adc eax,0
0x1995756  mov edx,[rbp+0xD4]
0x199575c  cmp edx,1
0x199575f  adc edx,0
0x1995762  imul rdx,rax
0x1995766  mov ebx,1
0x199576b  jmp short 0x19957AE
0x199576d  mov dword ptr [rbp+0x10C],0
0x1995777  mov byte ptr [rbp+0x110],0
0x199577e  mov qword ptr [rbp+0x114],0
0x1995789  mov eax,[rbp+0xD0]
0x199578f  cmp eax,1
```

#### Phase 11 0x1995792..0x1995844: Container decode 0x19957AE: destroys the old decoder 0x3C75F0([rbp-0x20]) and calls 0x9144720(rcx=[rbp-0x18], rdx=rbp+0x10C, r8d=ebx, r9=rbp+0xE0) [V]. On success writes the out object ([rdi]=eax, qword [rdi+4]=rdx, [rdi+0xC]=0, byte [rdi+0x10]=cl from [rbp+0x110]+1, [rdi+0x11]=0) and installs the new decoder object at [rdi+0x20] with the 0x3C7B10 vtable at [rdi+0x18] [I].
```
0x1995792  adc eax,0
0x1995795  mov edx,[rbp+0xD4]
0x199579b  cmp edx,1
0x199579e  adc edx,0
0x19957a1  imul rdx,rax
0x19957a5  shl rdx,2
0x19957a9  mov ebx,4
0x19957ae  lea rcx,[rbp-0x20]
0x19957b2  call 0x3C75F0
0x19957b7  nop
0x19957b8  mov rcx,[rbp-0x18]
0x19957bc  mov dword ptr [rsp+0x20],0
0x19957c4  lea rdx,[rbp+0x10C]
0x19957cb  lea r9,[rbp+0xE0]
0x19957d2  mov [rbp+0x120],rcx
0x19957d9  mov r8d,ebx
0x19957dc  call 0x9144720
0x19957e1  nop
0x19957e2  test al,al
0x19957e4  je 0x1995881
0x19957ea  mov eax,[rbp+0x10C]
0x19957f0  cmp eax,4
0x19957f3  ja 0x19959CA
0x19957f9  mov ecx,0x1A
0x19957fe  bt ecx,eax
0x1995801  jae 0x19959CA
0x1995807  movzx ecx,byte ptr [rbp+0x110]
0x199580e  inc cl
0x1995810  mov rdx,[rbp+0x114]
0x1995817  mov [rdi],eax
0x1995819  mov [rdi+4],rdx
0x199581d  mov dword ptr [rdi+0xC],0
0x1995824  mov [rdi+0x10],cl
0x1995827  mov byte ptr [rdi+0x11],0
0x199582b  mov rcx,[rdi+0x20]
0x199582f  mov qword ptr [rdi+0x20],0
0x1995837  test rcx,rcx
0x199583a  je 0x1995992
0x1995840  mov rax,[rdi+0x18]
0x1995844  call qword ptr [0xF99FFA0]
```

#### Phase 12 0x199584a..0x199591a: Out-object wrap-up and decode-failure log 0x1995881: level 8 with string 0xF80EF85 (len 0x1B), 0xF5E339B (line 0x10C) and 0xF7F0CD7 (len 0x19) [V]. Reloads the status object [rbp+0x120] and re-enters the cleanup path through [rbp-0x20] [I].
```
0x199584a  nop
0x199584b  mov rcx,[rdi+0x20]
0x199584f  lea rax,[0x3C7B10]
0x1995856  mov [rdi+0x18],rax
0x199585a  mov qword ptr [rdi+0x28],0
0x1995862  mov rax,[rbp+0x120]
0x1995869  mov [rdi+0x20],rax
0x199586d  test rcx,rcx
0x1995870  je 0x19959B0
0x1995876  call 0x3C7B10
0x199587b  nop
0x199587c  jmp 0x19959B0
0x1995881  mov qword ptr [rbp+0xF8],0
0x199588c  lea rax,[rbp-0x30]
0x1995890  mov [rbp+0x100],rax
0x1995897  lea rax,[0xF80EF85]
0x199589e  mov [rbp+0xE8],rax
0x19958a5  mov qword ptr [rbp+0xF0],0x1B
0x19958b0  lea rax,[rbp+0xF8]
0x19958b7  mov [rsp+0x40],rax
0x19958bc  lea rax,[rbp+0xE8]
0x19958c3  mov [rsp+0x38],rax
0x19958c8  lea rax,[0xF5E339B]
0x19958cf  mov [rsp+0x28],rax
0x19958d4  mov dword ptr [rsp+0x30],0x10C
0x19958dc  mov dword ptr [rsp+0x20],8
0x19958e4  xor ecx,ecx
0x19958e6  mov edx,1
0x19958eb  xor r8d,r8d
0x19958ee  mov r9d,0xF
0x19958f4  call 0x3CF160
0x19958f9  mov rcx,[rbp+0x120]
0x1995900  test rcx,rcx
0x1995903  je short 0x1995980
0x1995905  mov rax,[rbp-0x20]
0x1995909  call qword ptr [0xF99FFA0]
0x199590f  nop
0x1995910  jmp short 0x1995980
0x1995912  mov qword ptr [rbp-0x20],0
0x199591a  lea rax,[rbp+0xE8]
```

#### Phase 13 0x1995921..0x1995a0c: Format-range log (string len 0x19, level 8, line 0x104) and the format-from-decoder switch via jump table 0xF0FFB98 on [rbp+0x10C]-1 (ids above 3 collapse to 4) [V]. Installs the decoder pieces into the out object ([rdi+0x20], [rdi+0x18], [rdi+0x28]) and stages a final log through [rbp+0xE8]/[rbp+0xF0] [I].
```
0x1995921  mov [rbp-0x18],rax
0x1995925  lea rax,[0xF7F0CD7]
0x199592c  mov [rbp+0xF8],rax
0x1995933  mov qword ptr [rbp+0x100],0x19
0x199593e  mov [rsp+0x40],r14
0x1995943  lea rax,[rbp+0xF8]
0x199594a  mov [rsp+0x38],rax
0x199594f  lea rax,[0xF5E339B]
0x1995956  mov [rsp+0x28],rax
0x199595b  mov dword ptr [rsp+0x30],0x104
0x1995963  mov dword ptr [rsp+0x20],8
0x199596b  xor ecx,ecx
0x199596d  mov edx,1
0x1995972  xor r8d,r8d
0x1995975  mov r9d,0xF
0x199597b  call 0x3CF160
0x1995980  mov byte ptr [r13+0x10],0
0x1995985  mov dword ptr [r13],0
0x199598d  jmp 0x1995644
0x1995992  lea rax,[0x3C7B10]
0x1995999  mov [rdi+0x18],rax
0x199599d  mov qword ptr [rdi+0x28],0
0x19959a5  mov rax,[rbp+0x120]
0x19959ac  mov [rdi+0x20],rax
0x19959b0  mov rax,[rbp-0x20]
0x19959b4  mov [rdi+0x18],rax
0x19959b8  mov rax,[rbp-0x10]
0x19959bc  mov [rdi+0x28],rax
0x19959c0  mov byte ptr [r13+0x10],1
0x19959c5  jmp 0x199564F
0x19959ca  mov qword ptr [rbp+0xF8],0
0x19959d5  lea rax,[rbp-0x30]
0x19959d9  mov [rbp+0x100],rax
0x19959e0  lea rax,[0xF7F0CD7]
0x19959e7  mov [rbp+0xE8],rax
0x19959ee  mov qword ptr [rbp+0xF0],0x19
0x19959f9  lea rax,[rbp+0xF8]
0x1995a00  mov [rsp+0x40],rax
0x1995a05  lea rax,[rbp+0xE8]
0x1995a0c  mov [rsp+0x38],rax
```

#### Phase 14 0x1995a11..0x1995a55: Overflow guard 0x1995A31: on size sign-overflow it logs (line 0x11D, level 8), zeroes [rbp-0x18]/[rbp-0x20] (movups [rbp-0x18],xmm0) and raises through 0xEEC6D80 with strings 0xF08E738 and 0xFB3B080, then int3-pads to 0x1995a55 [V/I].
```
0x1995a11  lea rax,[0xF5E339B]
0x1995a18  mov [rsp+0x28],rax
0x1995a1d  mov dword ptr [rsp+0x30],0x11D
0x1995a25  jmp 0x19958DC
0x1995a2a  xor edx,edx
0x1995a2c  jmp 0x19957AE
0x1995a31  xorps xmm0,xmm0
0x1995a34  movups [rbp-0x18],xmm0
0x1995a38  lea rax,[0xF08E738]
0x1995a3f  mov [rbp-0x20],rax
0x1995a43  lea rdx,[0xFB3B080]
0x1995a4a  lea rcx,[rbp-0x20]
0x1995a4e  call 0xEEC6D80
0x1995a53  nop
0x1995a54  int3
0x1995a55  nop [rax+rax]
```

