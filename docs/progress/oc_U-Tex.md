## NEXT
DONE

# U-Tex — texload_task ctor (0x541bf00) & texgroup append (0x5417950) — Minecraft Bedrock 1.26.62.01 [V]

Static analysis only. All quoted instruction lines are verbatim from docs/data/listings/*.txt and verified against rdis via tools/sigs/verify_oc.py.

## texload_task (0x541bf00..0x541c6a0)

**Phase 1 — 0x541bf00..0x541bfa3: Prologue builds an rbp frame, saves this=rcx→r14 plus args rdx/r8/r9; stores vtable 0xEFCC480 at [this], allocates a 0x18-byte refcount control block (vtable 0xEFCC490, dual refcounts 0x100000001, byte [+0x10]=1), parks it at this+8/this+0x10, zeroes this+0x20/0x30, and stores vtables 0xF24A760/0xF24A768 at this/this+0x18. [V]**

```
0x541bf00  push rbp
0x541bf01  push r14
0x541bf03  push rsi
0x541bf04  push rdi
0x541bf05  push rbx
0x541bf06  sub rsp,0x100
0x541bf0d  lea rbp,[rsp+0x80]
0x541bf15  mov qword ptr [rbp+0x78],0xFFFFFFFFFFFFFFFE
0x541bf1d  mov rsi,r9
0x541bf20  mov [rbp+0x58],r8
0x541bf24  mov [rbp+0x60],rdx
0x541bf28  mov r14,rcx
0x541bf2b  lea rax,[0xEFCC480]
0x541bf32  mov [rcx],rax
0x541bf35  mov rcx,[0x1233E1A8]
0x541bf3c  mov rax,[rcx]
0x541bf3f  mov rax,[rax+8]
0x541bf43  mov edx,0x18
0x541bf48  call qword ptr [0xF99FFA0]
0x541bf4e  nop
0x541bf4f  mov rdi,rax
0x541bf52  test rax,rax
0x541bf55  je 0x541C610
0x541bf5b  mov rbx,0x100000001
0x541bf65  mov [rdi+8],rbx
0x541bf69  lea rax,[0xEFCC490]
0x541bf70  mov [rdi],rax
0x541bf73  mov rax,rdi
0x541bf76  add rax,0x10
0x541bf7a  mov byte ptr [rdi+0x10],1
0x541bf7e  mov [r14+8],rax
0x541bf82  mov [r14+0x10],rdi
0x541bf86  xorps xmm0,xmm0
0x541bf89  movups [r14+0x20],xmm0
0x541bf8e  lea rax,[0xF24A760]
0x541bf95  mov [r14],rax
0x541bf98  lea rax,[0xF24A768]
0x541bf9f  mov [r14+0x18],rax
0x541bfa3  movups [r14+0x30],xmm0
```

**Phase 2 — 0x541bfa8..0x541c048: Copies shared_ptr arg1 ([rbp+0x60]) into this+0x30/0x38/0x40 with lock inc of the control refcount; null/empty-name checks throw via 0x78ED0; saves this at [rbp+0x70], zeroes locals [rbp+0x20]/[rbp+0x30], allocates a 0x20-byte string buffer and builds the 23-char name (const 16 bytes from 0xF573574, 'skGroup ' at +0xF, NUL at +0x17, size 0x17 cap 0x1F). [V]**

```
0x541bfa8  mov rdx,[rbp+0x60]
0x541bfac  mov rax,[rdx+8]
0x541bfb0  test rax,rax
0x541bfb3  je short 0x541BFBF
0x541bfb5  lock inc dword ptr [rax+8]
0x541bfb9  mov rax,[rdx+8]
0x541bfbd  jmp short 0x541BFC1
0x541bfbf  xor eax,eax
0x541bfc1  mov rcx,[rdx]
0x541bfc4  mov [r14+0x30],rcx
0x541bfc8  mov [r14+0x38],rax
0x541bfcc  mov rax,[rdx+0x10]
0x541bfd0  mov [r14+0x40],rax
0x541bfd4  test rcx,rcx
0x541bfd7  je 0x541C60A
0x541bfdd  cmp byte ptr [rcx],0
0x541bfe0  je 0x541C60A
0x541bfe6  mov [rbp+0x70],r14
0x541bfea  lea rax,[r14+0x30]
0x541bfee  mov [rbp-0x38],rax
0x541bff2  movaps [rbp+0x30],xmm0
0x541bff6  movaps [rbp+0x20],xmm0
0x541bffa  mov rcx,[0x1233E1A8]
0x541c001  mov rax,[rcx]
0x541c004  mov rax,[rax+8]
0x541c008  mov edx,0x20
0x541c00d  call qword ptr [0xF99FFA0]
0x541c013  nop
0x541c014  mov rdi,rax
0x541c017  test rax,rax
0x541c01a  je 0x541C620
0x541c020  mov [rbp+0x20],rdi
0x541c024  mov qword ptr [rbp+0x30],0x17
0x541c02c  mov qword ptr [rbp+0x38],0x1F
0x541c034  movups xmm0,[0xF573574]
0x541c03b  movups [rdi],xmm0
0x541c03e  mov rax,0x70756F7247206B73
0x541c048  mov [rdi+0xF],rax
```

**Phase 3 — 0x541c04c..0x541c0cd: Initializes the singleton registry at [0x128D3D68]: if empty, allocates 0x70 bytes, initializes it with string view {0xF6027EE, len 0xB} and r8w=0x3C via 0x7709C0, publishes the pointer, and releases any prior instance through the allocator deleter (edx=1). [V]**

```
0x541c04c  mov byte ptr [rdi+0x17],0
0x541c050  mov r8,[0x128D3D68]
0x541c057  test r8,r8
0x541c05a  jne short 0x541C0DA
0x541c05c  mov rcx,[0x1233E1A8]
0x541c063  mov rax,[rcx]
0x541c066  mov rax,[rax+8]
0x541c06a  mov edx,0x70
0x541c06f  call qword ptr [0xF99FFA0]
0x541c075  nop
0x541c076  mov r14,rax
0x541c079  test rax,rax
0x541c07c  je 0x541C690
0x541c082  lea rax,[0xF6027EE]
0x541c089  mov [rbp-0x50],rax
0x541c08d  mov qword ptr [rbp-0x48],0xB
0x541c095  lea rdx,[rbp-0x50]
0x541c099  mov rcx,r14
0x541c09c  mov r8w,0x3C
0x541c0a1  mov [rbp+0x68],r14
0x541c0a5  call 0x7709C0
0x541c0aa  nop
0x541c0ab  mov rcx,[0x128D3D68]
0x541c0b2  mov r8,[rbp+0x68]
0x541c0b6  mov [0x128D3D68],r8
0x541c0bd  test rcx,rcx
0x541c0c0  je short 0x541C0DA
0x541c0c2  mov rax,[rcx]
0x541c0c5  mov rax,[rax]
0x541c0c8  mov edx,1
0x541c0cd  call qword ptr [0xF99FFA0]
```

**Phase 4 — 0x541c0d3..0x541c17e: Loads registry slots [0x128D3D70]/[0x128D3D80] under DEADC0DE guards, registers this+0x48 with the name string via 0x58A2EC0, frees the string (0xE935700, edx=0x20), zeroes this+0x1A8, allocates the 0x88-byte intrusive-list sentinel (self-linked at +0/+8/+0x10, word [+0x18]=0x101) into this+0x1A8, and zeroes this+0x1B8. [V]**

```
0x541c0d3  mov r8,[0x128D3D68]
0x541c0da  mov rax,[0x128D3D70]
0x541c0e1  test rax,rax
0x541c0e4  jne short 0x541C0F1
0x541c0e6  mov dword ptr [0],0xDEADC0DE
0x541c0f1  mov rcx,[rbp+0x70]
0x541c0f5  add rcx,0x48
0x541c0f9  cmp byte ptr [rax],0
0x541c0fc  jne short 0x541C109
0x541c0fe  mov dword ptr [0],0xDEADC0DE
0x541c109  mov rdx,[0x128D3D80]
0x541c110  lea r9,[rbp+0x20]
0x541c114  mov [rbp-0x30],rcx
0x541c118  call 0x58A2EC0
0x541c11d  nop
0x541c11e  mov edx,0x20
0x541c123  mov rcx,rdi
0x541c126  call 0xE935700
0x541c12b  xorps xmm0,xmm0
0x541c12e  mov rax,[rbp+0x70]
0x541c132  movups [rax+0x1A8],xmm0
0x541c139  mov rcx,[0x1233E1A8]
0x541c140  mov rax,[rcx]
0x541c143  mov rax,[rax+8]
0x541c147  mov edx,0x88
0x541c14c  call qword ptr [0xF99FFA0]
0x541c152  nop
0x541c153  mov rdi,rax
0x541c156  test rax,rax
0x541c159  je 0x541C630
0x541c15f  mov [rdi],rdi
0x541c162  mov [rdi+8],rdi
0x541c166  mov [rdi+0x10],rdi
0x541c16a  mov word ptr [rdi+0x18],0x101
0x541c170  mov r10,[rbp+0x70]
0x541c174  mov [r10+0x1A8],rdi
0x541c17b  xorps xmm0,xmm0
0x541c17e  movups [r10+0x1B8],xmm0
```

**Phase 5 — 0x541c186..0x541c220: Copies shared_ptr arg2 ([rbp+0x58]) into this+0x1B8/0x1C0/0x1C8 with lock inc; empty check throws 0x78ED0; parks this+0x1A8/this+0x1B8 in stack locals; stores arg3 (rsi) at this+0x1D0; builds a zeroed local string {[rbp+0x20]=0, [rbp+0x30]=0, [rbp+0x38]=0x3C7B10, [rbp+0x40]=0} and sets up call 0x1994F90(rcx=[rbp-0x50] out-param, rdx=&[rbp+0x20], r8d=4, r9=0xF24C8D0, [rsp+0x20]=0x9E, [rsp+0x28]=0). [V]**

```
0x541c186  mov rdx,[rbp+0x58]
0x541c18a  mov rax,[rdx+8]
0x541c18e  test rax,rax
0x541c191  je short 0x541C19D
0x541c193  lock inc dword ptr [rax+8]
0x541c197  mov rax,[rdx+8]
0x541c19b  jmp short 0x541C19F
0x541c19d  xor eax,eax
0x541c19f  mov rcx,[rdx]
0x541c1a2  mov [r10+0x1B8],rcx
0x541c1a9  mov [r10+0x1C0],rax
0x541c1b0  mov rax,[rdx+0x10]
0x541c1b4  mov [r10+0x1C8],rax
0x541c1bb  test rcx,rcx
0x541c1be  je 0x541C60A
0x541c1c4  cmp byte ptr [rcx],0
0x541c1c7  je 0x541C60A
0x541c1cd  lea rax,[r10+0x1A8]
0x541c1d4  mov [rbp-0x28],rax
0x541c1d8  lea rax,[r10+0x1B8]
0x541c1df  mov [rbp-0x20],rax
0x541c1e3  mov [r10+0x1D0],rsi
0x541c1ea  movaps [rbp+0x20],xmm0
0x541c1ee  mov word ptr [rbp+0x30],0
0x541c1f4  lea rax,[0x3C7B10]
0x541c1fb  mov [rbp+0x38],rax
0x541c1ff  movaps [rbp+0x40],xmm0
0x541c203  mov byte ptr [rsp+0x28],0
0x541c208  mov qword ptr [rsp+0x20],0x9E
0x541c211  lea r9,[0xF24C8D0]
0x541c218  lea rcx,[rbp-0x50]
0x541c21c  lea rdx,[rbp+0x20]
0x541c220  mov r8d,4
```

**Phase 6 — 0x541c226..0x541c2c6: Finishes 0x1994F90 (rsi=this) and calls 0x5A4C7C0(rcx=this+0x1D8, rdx=&[rbp+0x20]), saving rsi at [rbp-0x18]; frees the local string via the allocator ([rbp+0x40] deleter / [rbp+0x38] buffer); zeroes this+0x208/0x218 (movups) and this+0x228; allocates a 0x60-byte sentinel and self-links it. [V]**

```
0x541c226  mov rsi,r10
0x541c229  call 0x1994F90
0x541c22e  nop
0x541c22f  add rsi,0x1D8
0x541c236  lea rdx,[rbp+0x20]
0x541c23a  mov rcx,rsi
0x541c23d  call 0x5A4C7C0
0x541c242  nop
0x541c243  mov [rbp-0x18],rsi
0x541c247  mov rcx,[rbp+0x40]
0x541c24b  test rcx,rcx
0x541c24e  je short 0x541C25B
0x541c250  mov rax,[rbp+0x38]
0x541c254  call qword ptr [0xF99FFA0]
0x541c25a  nop
0x541c25b  mov rax,[rbp+0x70]
0x541c25f  lea rcx,[rax+0x208]
0x541c266  mov [rbp+0x68],rcx
0x541c26a  xorps xmm0,xmm0
0x541c26d  movups [rax+0x218],xmm0
0x541c274  movups [rax+0x208],xmm0
0x541c27b  mov qword ptr [rax+0x228],0
0x541c286  mov rcx,[0x1233E1A8]
0x541c28d  mov rax,[rcx]
0x541c290  mov rax,[rax+8]
0x541c294  mov edx,0x60
0x541c299  call qword ptr [0xF99FFA0]
0x541c29f  nop
0x541c2a0  mov rsi,rax
0x541c2a3  test rax,rax
0x541c2a6  je 0x541C640
0x541c2ac  mov rax,[rbp+0x70]
0x541c2b0  lea rcx,[rax+0x220]
0x541c2b7  mov [rbp-0x10],rcx
0x541c2bb  mov [rsi],rsi
0x541c2be  mov [rsi+8],rsi
0x541c2c2  mov [rsi+0x10],rsi
0x541c2c6  mov word ptr [rsi+0x18],0x101
```

**Phase 7 — 0x541c2cc..0x541c35d: Stores the 0x60 sentinel at this+0x220; zeroes this+0x230 (movups); allocates a 0x68 sentinel (throw path 0x541C650) and self-links it, stores it at this+0x230; zeroes this+0x240 and this+0x250; allocates a 0x70-byte block (throw path 0x541C660). [V]**

```
0x541c2cc  mov [rax+0x220],rsi
0x541c2d3  xorps xmm0,xmm0
0x541c2d6  movups [rax+0x230],xmm0
0x541c2dd  mov rcx,[0x1233E1A8]
0x541c2e4  mov rax,[rcx]
0x541c2e7  mov rax,[rax+8]
0x541c2eb  mov edx,0x68
0x541c2f0  call qword ptr [0xF99FFA0]
0x541c2f6  nop
0x541c2f7  mov rsi,rax
0x541c2fa  test rax,rax
0x541c2fd  je 0x541C650
0x541c303  mov rax,[rbp+0x70]
0x541c307  lea rcx,[rax+0x230]
0x541c30e  mov [rbp-8],rcx
0x541c312  mov [rsi],rsi
0x541c315  mov [rsi+8],rsi
0x541c319  mov [rsi+0x10],rsi
0x541c31d  mov word ptr [rsi+0x18],0x101
0x541c323  mov [rax+0x230],rsi
0x541c32a  lea rcx,[rax+0x240]
0x541c331  mov [rbp],rcx
0x541c335  xorps xmm0,xmm0
0x541c338  movups [rax+0x240],xmm0
0x541c33f  mov qword ptr [rax+0x250],0
0x541c34a  mov rcx,[0x1233E1A8]
0x541c351  mov rax,[rcx]
0x541c354  mov rax,[rax+8]
0x541c358  mov edx,0x70
0x541c35d  call qword ptr [0xF99FFA0]
```

**Phase 8 — 0x541c363..0x541c42f: Stores the 0x70 sentinel at this+0x248; zeroes this+0x258; allocates 0x18-byte refcount object #3 (vtable 0xEFCC490, [rsi+8]=rbx refcounts, qword [rsi+0x10]=0) and parks {rsi+0x10, rsi} at this+0x268/this+0x270; zeroes this+0x278 (movups); allocates 0x18-byte object #4 (throw path 0x541C680). [V]**

```
0x541c363  nop
0x541c364  mov rsi,rax
0x541c367  test rax,rax
0x541c36a  je 0x541C660
0x541c370  mov rax,[rbp+0x70]
0x541c374  lea rcx,[rax+0x248]
0x541c37b  mov [rbp+8],rcx
0x541c37f  mov [rsi],rsi
0x541c382  mov [rsi+8],rsi
0x541c386  mov [rsi+0x10],rsi
0x541c38a  mov word ptr [rsi+0x18],0x101
0x541c390  mov [rax+0x248],rsi
0x541c397  lea rcx,[rax+0x258]
0x541c39e  mov [rbp+0x10],rcx
0x541c3a2  xorps xmm0,xmm0
0x541c3a5  movups [rax+0x258],xmm0
0x541c3ac  mov rcx,[0x1233E1A8]
0x541c3b3  mov rax,[rcx]
0x541c3b6  mov rax,[rax+8]
0x541c3ba  mov edx,0x18
0x541c3bf  call qword ptr [0xF99FFA0]
0x541c3c5  nop
0x541c3c6  mov rsi,rax
0x541c3c9  test rax,rax
0x541c3cc  je 0x541C670
0x541c3d2  mov rcx,[rbp+0x70]
0x541c3d6  lea rax,[rcx+0x268]
0x541c3dd  mov [rbp+0x18],rax
0x541c3e1  mov [rsi+8],rbx
0x541c3e5  lea rax,[0xEFCC490]
0x541c3ec  mov [rsi],rax
0x541c3ef  mov rax,rsi
0x541c3f2  add rax,0x10
0x541c3f6  mov qword ptr [rsi+0x10],0
0x541c3fe  mov [rcx+0x268],rax
0x541c405  mov [rcx+0x270],rsi
0x541c40c  xorps xmm0,xmm0
0x541c40f  movups [rcx+0x278],xmm0
0x541c416  mov rcx,[0x1233E1A8]
0x541c41d  mov rax,[rcx]
0x541c420  mov rax,[rax+8]
0x541c424  mov edx,0x18
0x541c429  call qword ptr [0xF99FFA0]
0x541c42f  nop
```

**Phase 9 — 0x541c430..0x541c4ce: Object #4 becomes a list node: reads shared_ptr {[rbx+0x208], [rbx+0x210]} with lock inc, writes vtable 0xF0FB9B0 and zeroes [rsi+8..0x17]; with ctrl non-null it lock incs [rdi+8], stores {[rsi+8]=rax, [rsi+0x10]=rdi}, then releases rdi (strong delete via [[rdi]], weak via [[rax+8]]); the else branch loads [[rbp+0x68]] and leaves [rsi+0x10]=0. [V]**

```
0x541c430  mov rsi,rax
0x541c433  test rax,rax
0x541c436  je 0x541C680
0x541c43c  mov rbx,[rbp+0x70]
0x541c440  mov rax,[rbx+0x210]
0x541c447  test rax,rax
0x541c44a  je short 0x541C4B1
0x541c44c  lock inc dword ptr [rax+8]
0x541c450  mov rax,[rbx+0x208]
0x541c457  mov rdi,[rbx+0x210]
0x541c45e  lea rcx,[0xF0FB9B0]
0x541c465  mov [rsi],rcx
0x541c468  xorps xmm0,xmm0
0x541c46b  movups [rsi+8],xmm0
0x541c46f  test rdi,rdi
0x541c472  mov r14,[rbp+0x60]
0x541c476  je short 0x541C4CE
0x541c478  lock inc dword ptr [rdi+8]
0x541c47c  mov [rsi+8],rax
0x541c480  mov [rsi+0x10],rdi
0x541c484  lock dec dword ptr [rdi+8]
0x541c488  jne short 0x541C4DA
0x541c48a  mov rax,[rdi]
0x541c48d  mov rax,[rax]
0x541c490  mov rcx,rdi
0x541c493  call qword ptr [0xF99FFA0]
0x541c499  lock dec dword ptr [rdi+0xC]
0x541c49d  jne short 0x541C4DA
0x541c49f  mov rax,[rdi]
0x541c4a2  mov rax,[rax+8]
0x541c4a6  mov rcx,rdi
0x541c4a9  call qword ptr [0xF99FFA0]
0x541c4af  jmp short 0x541C4DA
0x541c4b1  mov rax,[rbp+0x68]
0x541c4b5  mov rax,[rax]
0x541c4b8  lea rcx,[0xF0FB9B0]
0x541c4bf  mov [rsi],rcx
0x541c4c2  mov qword ptr [rsi+8],0
0x541c4ca  mov r14,[rbp+0x60]
0x541c4ce  mov [rsi+8],rax
```

**Phase 10 — 0x541c4d2..0x541c567: Stores the node pointer at [rsi+0x10]=0 finalize; links the node into list head [rbx+0x218] releasing the displaced node (edx=1); then destroys the two aliasing shared_ptr temps of arg1 at r14=[rbp+0x60]: movups zero, strong release (delete via [[rsi]]) and weak release, then the second temp at [r14+0x10]. [V]**

```
0x541c4d2  mov qword ptr [rsi+0x10],0
0x541c4da  mov rcx,[rbx+0x218]
0x541c4e1  mov [rbx+0x218],rsi
0x541c4e8  test rcx,rcx
0x541c4eb  je short 0x541C4FE
0x541c4ed  mov rax,[rcx]
0x541c4f0  mov rax,[rax]
0x541c4f3  mov edx,1
0x541c4f8  call qword ptr [0xF99FFA0]
0x541c4fe  xorps xmm0,xmm0
0x541c501  mov rsi,[r14+8]
0x541c505  movups [r14],xmm0
0x541c509  test rsi,rsi
0x541c50c  mov rdi,[rbp+0x58]
0x541c510  je short 0x541C57B
0x541c512  lock dec dword ptr [rsi+8]
0x541c516  jne short 0x541C53D
0x541c518  mov rax,[rsi]
0x541c51b  mov rax,[rax]
0x541c51e  mov rcx,rsi
0x541c521  call qword ptr [0xF99FFA0]
0x541c527  lock dec dword ptr [rsi+0xC]
0x541c52b  jne short 0x541C53D
0x541c52d  mov rax,[rsi]
0x541c530  mov rax,[rax+8]
0x541c534  mov rcx,rsi
0x541c537  call qword ptr [0xF99FFA0]
0x541c53d  mov rsi,[r14+8]
0x541c541  mov qword ptr [r14+0x10],0
0x541c549  test rsi,rsi
0x541c54c  je short 0x541C583
0x541c54e  lock dec dword ptr [rsi+8]
0x541c552  jne short 0x541C583
0x541c554  mov rax,[rsi]
0x541c557  mov rax,[rax]
0x541c55a  mov rcx,rsi
0x541c55d  call qword ptr [0xF99FFA0]
0x541c563  lock dec dword ptr [rsi+0xC]
```

**Phase 11 — 0x541c567..0x541c5f9: Finishes the arg1 temp destruction (weak delete via [[rax+8]]), then destroys the two aliasing shared_ptr temps of arg2 at rdi=[rbp+0x58] with the same strong/weak release pattern; sets return value rax=rbx (this). [V]**

```
0x541c567  jne short 0x541C583
0x541c569  mov rax,[rsi]
0x541c56c  mov rax,[rax+8]
0x541c570  mov rcx,rsi
0x541c573  call qword ptr [0xF99FFA0]
0x541c579  jmp short 0x541C583
0x541c57b  mov qword ptr [r14+0x10],0
0x541c583  xorps xmm0,xmm0
0x541c586  mov rsi,[rdi+8]
0x541c58a  movups [rdi],xmm0
0x541c58d  test rsi,rsi
0x541c590  je short 0x541C5F9
0x541c592  lock dec dword ptr [rsi+8]
0x541c596  jne short 0x541C5BD
0x541c598  mov rax,[rsi]
0x541c59b  mov rax,[rax]
0x541c59e  mov rcx,rsi
0x541c5a1  call qword ptr [0xF99FFA0]
0x541c5a7  lock dec dword ptr [rsi+0xC]
0x541c5ab  jne short 0x541C5BD
0x541c5ad  mov rax,[rsi]
0x541c5b0  mov rax,[rax+8]
0x541c5b4  mov rcx,rsi
0x541c5b7  call qword ptr [0xF99FFA0]
0x541c5bd  mov rsi,[rdi+8]
0x541c5c1  mov qword ptr [rdi+0x10],0
0x541c5c9  test rsi,rsi
0x541c5cc  je short 0x541C5F9
0x541c5ce  lock dec dword ptr [rsi+8]
0x541c5d2  jne short 0x541C5F9
0x541c5d4  mov rax,[rsi]
0x541c5d7  mov rax,[rax]
0x541c5da  mov rcx,rsi
0x541c5dd  call qword ptr [0xF99FFA0]
0x541c5e3  lock dec dword ptr [rsi+0xC]
0x541c5e7  jne short 0x541C5F9
0x541c5e9  mov rax,[rsi]
0x541c5ec  mov rax,[rax+8]
0x541c5f0  mov rcx,rsi
0x541c5f3  call qword ptr [0xF99FFA0]
0x541c5f9  mov rax,rbx
```

**Phase 12 — 0x541c5fc..0x541c63b: Epilogue (add rsp,0x100; pop rbx/rdi/rsi/r14/rbp; ret) with the empty-name throw tail (0x78ED0) and the first three bad_alloc tails: mov ecx,size; call 0x9BC830; jmp back to the allocation retry point. [V]**

```
0x541c5fc  add rsp,0x100
0x541c603  pop rbx
0x541c604  pop rdi
0x541c605  pop rsi
0x541c606  pop r14
0x541c608  pop rbp
0x541c609  ret
0x541c60a  call 0x78ED0
0x541c60f  nop
0x541c610  mov ecx,0x18
0x541c615  call 0x9BC830
0x541c61a  nop
0x541c61b  jmp 0x541BF5B
0x541c620  mov ecx,0x20
0x541c625  call 0x9BC830
0x541c62a  nop
0x541c62b  jmp 0x541C020
0x541c630  mov ecx,0x88
0x541c635  call 0x9BC830
0x541c63a  nop
0x541c63b  jmp 0x541C15F
```

**Phase 13 — 0x541c640..0x541c69b: Remaining bad_alloc tails for the 0x60/0x68/0x70/0x18/0x18/0x70 allocations, each mov ecx,size; call 0x9BC830 (throw bad_alloc); jmp back to the corresponding continuation. [V]**

```
0x541c640  mov ecx,0x60
0x541c645  call 0x9BC830
0x541c64a  nop
0x541c64b  jmp 0x541C2AC
0x541c650  mov ecx,0x68
0x541c655  call 0x9BC830
0x541c65a  nop
0x541c65b  jmp 0x541C303
0x541c660  mov ecx,0x70
0x541c665  call 0x9BC830
0x541c66a  nop
0x541c66b  jmp 0x541C370
0x541c670  mov ecx,0x18
0x541c675  call 0x9BC830
0x541c67a  nop
0x541c67b  jmp 0x541C3D2
0x541c680  mov ecx,0x18
0x541c685  call 0x9BC830
0x541c68a  nop
0x541c68b  jmp 0x541C43C
0x541c690  mov ecx,0x70
0x541c695  call 0x9BC830
0x541c69a  nop
0x541c69b  jmp 0x541C082
```

## texgroup (0x5417950..0x54186e0)

**Phase 1 — 0x5417950..0x541799f: Prologue saves r15..rbx and xmm6-xmm9; queue-gate compares [rcx+0x298] against [rcx+0x29C] (equal → exit 0x541864A), increments the counter, marks the object dirty (byte [rcx]=1); moves xmm6=xmm3 (Z) and xmm7=unpcklps(xmm1,xmm2) (UV pair). [V]**

```
0x5417950  push r15
0x5417952  push r14
0x5417954  push r13
0x5417956  push r12
0x5417958  push rsi
0x5417959  push rdi
0x541795a  push rbp
0x541795b  push rbx
0x541795c  sub rsp,0x78
0x5417960  movaps [rsp+0x60],xmm9
0x5417966  movaps [rsp+0x50],xmm8
0x541796c  movaps [rsp+0x40],xmm7
0x5417971  movaps [rsp+0x30],xmm6
0x5417976  mov eax,[rcx+0x298]
0x541797c  cmp eax,[rcx+0x29C]
0x5417982  je 0x541864A
0x5417988  movaps xmm6,xmm3
0x541798b  mov rsi,rcx
0x541798e  inc eax
0x5417990  mov [rcx+0x298],eax
0x5417996  mov byte ptr [rcx],1
0x5417999  movaps xmm7,xmm1
0x541799c  unpcklps xmm7,xmm2
```

**Phase 2 — 0x54179a6..0x5417a15: If flag byte [rsi+0x210]==1, transforms the position: xmm0=xmm1*[0x21C], xmm2*=[0x22C], xmm3=[0x23C]*xmm6+[0x24C], xmm1 broadcast, then a 2x2 matrix product using movsd-loaded rows [0x214]/[0x224]/[0x234]/[0x244]; xmm6=xmm3 afterwards. [V]**

```
0x54179a6  jne short 0x5417A18
0x54179a8  movaps xmm0,xmm1
0x54179ab  mulss xmm0,[rsi+0x21C]
0x54179b3  mulss xmm2,[rsi+0x22C]
0x54179bb  movss xmm3,[rsi+0x23C]
0x54179c3  mulss xmm3,xmm6
0x54179c7  addss xmm3,[rsi+0x24C]
0x54179cf  addss xmm2,xmm0
0x54179d3  addss xmm3,xmm2
0x54179d7  shufps xmm1,xmm1,0
0x54179db  movsd xmm0,[rsi+0x214]
0x54179e3  mulps xmm0,xmm1
0x54179e6  movsd xmm1,[rsi+0x224]
0x54179ee  movsd xmm2,[rsi+0x234]
0x54179f6  movsd xmm4,[rsi+0x244]
0x54179fe  shufps xmm7,xmm7,0x55
0x5417a02  mulps xmm7,xmm1
0x5417a05  addps xmm7,xmm0
0x5417a08  shufps xmm6,xmm6,0
0x5417a0c  mulps xmm6,xmm2
0x5417a0f  addps xmm6,xmm4
0x5417a12  addps xmm7,xmm6
0x5417a15  movaps xmm6,xmm3
```

**Phase 3 — 0x5417a18..0x5417a94: Loads scale xmm8=[0x1D8] and Z xmm6=xmm6*[0x1E0]+[0x1D4], offset xmm9=[0x1CC]; capacity check of the 12-byte-element vertex vector {begin [rsi+0x10], cap-end [rsi+0x20]} against limit [rsi+0x170] (count via sar 2 + imul 0xAAAAAAAAAAAAAAAB); grows via 0x17708D0(rcx=r14, rdx=&[rsp+0x28]) if over; xmm7=xmm7*xmm8+xmm9. [V]**

```
0x5417a18  movsd xmm8,[rsi+0x1D8]
0x5417a21  mulss xmm6,[rsi+0x1E0]
0x5417a29  addss xmm6,[rsi+0x1D4]
0x5417a31  movsd xmm9,[rsi+0x1CC]
0x5417a3a  lea r14,[rsi+0x10]
0x5417a3e  mov rax,[rsi+0x170]
0x5417a45  mov [rsp+0x28],rax
0x5417a4a  mov r13,[rsi+0x20]
0x5417a4e  mov rcx,r13
0x5417a51  sub rcx,[rsi+0x10]
0x5417a55  sar rcx,2
0x5417a59  mov rbx,0xAAAAAAAAAAAAAAAB
0x5417a63  imul rcx,rbx
0x5417a67  cmp rax,rcx
0x5417a6a  jbe short 0x5417A90
0x5417a6c  mov rcx,0x1555555555555556
0x5417a76  cmp rax,rcx
0x5417a79  jae 0x54186A6
0x5417a7f  lea rdx,[rsp+0x28]
0x5417a84  mov rcx,r14
0x5417a87  call 0x17708D0
0x5417a8c  mov r13,[rsi+0x20]
0x5417a90  mulps xmm7,xmm8
0x5417a94  addps xmm7,xmm9
```

**Phase 4 — 0x5417a98..0x5417b06: Fast append path: if end [rsi+0x18] != cap-end, writes movlps [rbp],xmm7 / movss [rbp+8],xmm6 and advances end by 0xC, then jumps to 0x5417CDC; otherwise computes the new element count rax=(cap_end-begin)/12 and growth capacity r12/r15 via cmovbe/cmova with constants 0x1555555555555555/0x1555555555555556, overflow throws 0x54186A1, zero capacity skips to 0x5417B90. [V]**

```
0x5417a98  mov rbp,[rsi+0x18]
0x5417a9c  cmp rbp,r13
0x5417a9f  je short 0x5417AB4
0x5417aa1  movlps [rbp],xmm7
0x5417aa5  movss [rbp+8],xmm6
0x5417aaa  add qword ptr [rsi+0x18],0xC
0x5417aaf  jmp 0x5417CDC
0x5417ab4  mov rdi,r13
0x5417ab7  sub rdi,[r14]
0x5417aba  mov rax,rdi
0x5417abd  sar rax,2
0x5417ac1  imul rax,rbx
0x5417ac5  lea r12,[rax+1]
0x5417ac9  mov r15,rax
0x5417acc  shr r15,1
0x5417acf  mov rcx,0x1555555555555555
0x5417ad9  mov rdx,rcx
0x5417adc  sub rdx,r15
0x5417adf  add r15,rax
0x5417ae2  cmp r15,r12
0x5417ae5  cmovbe r15,r12
0x5417ae9  cmp rax,rdx
0x5417aec  cmova r15,rcx
0x5417af0  mov rax,0x1555555555555556
0x5417afa  cmp r15,rax
0x5417afd  jae 0x54186A1
0x5417b03  test r15,r15
0x5417b06  je 0x5417B90
```

**Phase 5 — 0x5417b0c..0x5417b96: Computes byte size r15*12 (lea rax,[r15*4]; lea r14,[rax+rax*2]); for r15>=0x156 uses the 32-byte-aligned allocator path (rdx=r14, +0x27, and 0xFFFFFFFFFFFFFFE0, header at [rbx-8], null → 0x5418671), otherwise the plain allocator path with bad_alloc throw 0x9BC830; writes the new vertex movlps [rbx+rdi],xmm7 / movss [rbx+rdi+8],xmm6. [V]**

```
0x5417b0c  lea rax,[r15*4]
0x5417b14  lea r14,[rax+rax*2]
0x5417b18  cmp r15,0x156
0x5417b1f  jb short 0x5417B69
0x5417b21  mov rax,0x1555555555555553
0x5417b2b  cmp r15,rax
0x5417b2e  jae 0x54186A1
0x5417b34  add r14,0x27
0x5417b38  mov rcx,[0x1233E1A8]
0x5417b3f  mov rax,[rcx]
0x5417b42  mov rax,[rax+8]
0x5417b46  mov rdx,r14
0x5417b49  call qword ptr [0xF99FFA0]
0x5417b4f  test rax,rax
0x5417b52  je 0x5418671
0x5417b58  mov rbx,rax
0x5417b5b  add rbx,0x27
0x5417b5f  and rbx,0xFFFFFFFFFFFFFFE0
0x5417b63  mov [rbx-8],rax
0x5417b67  jmp short 0x5417B92
0x5417b69  mov rcx,[0x1233E1A8]
0x5417b70  mov rax,[rcx]
0x5417b73  mov rax,[rax+8]
0x5417b77  mov rdx,r14
0x5417b7a  call qword ptr [0xF99FFA0]
0x5417b80  mov rbx,rax
0x5417b83  test rax,rax
0x5417b86  jne short 0x5417B92
0x5417b88  mov rcx,r14
0x5417b8b  call 0x9BC830
0x5417b90  xor ebx,ebx
0x5417b92  movlps [rbx+rdi],xmm7
0x5417b96  movss [rbx+rdi+8],xmm6
```

**Phase 6 — 0x5417b9c..0x5417c0a: Copies existing 12-byte elements into the new buffer: first loop copies from begin [rsi+0x10] while below cap-end r13 (three movss per element, stride 0xC); skips when begin==r13; the tail copy targets rbx+rdi+0xC with rcx=rdi+rbx+0x14, edx=0. [V]**

```
0x5417b9c  mov rcx,[rsi+0x10]
0x5417ba0  mov rax,[rsi+0x18]
0x5417ba4  cmp r13,rax
0x5417ba7  je 0x5417C46
0x5417bad  cmp rcx,r13
0x5417bb0  je short 0x5417BF7
0x5417bb2  xor eax,eax
0x5417bb4  nop [rax+rax]
0x5417bc0  movss xmm0,[rcx+rax]
0x5417bc5  movss [rbx+rax],xmm0
0x5417bca  movss xmm0,[rcx+rax+4]
0x5417bd0  movss [rbx+rax+4],xmm0
0x5417bd6  movss xmm0,[rcx+rax+8]
0x5417bdc  movss [rbx+rax+8],xmm0
0x5417be2  lea rdx,[rcx+rax]
0x5417be6  add rdx,0xC
0x5417bea  add rax,0xC
0x5417bee  cmp rdx,r13
0x5417bf1  jne short 0x5417BC0
0x5417bf3  mov rax,[rsi+0x18]
0x5417bf7  cmp r13,rax
0x5417bfa  je 0x5417C83
0x5417c00  lea rcx,[rdi+rbx]
0x5417c04  add rcx,0x14
0x5417c08  xor edx,edx
0x5417c0a  nop [rax+rax]
```

**Phase 7 — 0x5417c10..0x5417c81: Second copy loop moves the tail elements from end [rbp] (three movss per 12-byte element into the rbx+rdi region, stride 0xC); the third loop at 0x5417C50 copies from begin when end==cap-end. [V]**

```
0x5417c10  movss xmm0,[rbp+rdx]
0x5417c16  movss [rcx+rdx-8],xmm0
0x5417c1c  movss xmm0,[rbp+rdx+4]
0x5417c22  movss [rcx+rdx-4],xmm0
0x5417c28  movss xmm0,[rbp+rdx+8]
0x5417c2e  movss [rcx+rdx],xmm0
0x5417c33  lea r8,[rdx+rbp]
0x5417c37  add r8,0xC
0x5417c3b  add rdx,0xC
0x5417c3f  cmp r8,rax
0x5417c42  jne short 0x5417C10
0x5417c44  jmp short 0x5417C83
0x5417c46  cmp rcx,r13
0x5417c49  je short 0x5417C8A
0x5417c4b  xor eax,eax
0x5417c4d  nop [rax]
0x5417c50  movss xmm0,[rcx+rax]
0x5417c55  movss [rbx+rax],xmm0
0x5417c5a  movss xmm0,[rcx+rax+4]
0x5417c60  movss [rbx+rax+4],xmm0
0x5417c66  movss xmm0,[rcx+rax+8]
0x5417c6c  movss [rbx+rax+8],xmm0
0x5417c72  lea rdx,[rcx+rax]
0x5417c76  add rdx,0xC
0x5417c7a  add rax,0xC
0x5417c7e  cmp rdx,r13
0x5417c81  jne short 0x5417C50
```

**Phase 8 — 0x5417c83..0x5417cd8: Frees the old buffer via 0xE935700 with size/header checks (cap_end-begin >= 0x1000, header [rcx-8], rcx-=8, jae 0x54186BF); commits the grown vector begin=[rsi+0x10]=rbx, end=[rsi+0x18]=rbx+r12*12, cap-end=[rsi+0x20]=rbx+r15*12. [V]**

```
0x5417c83  lea rax,[rsi+0x10]
0x5417c87  mov rcx,[rax]
0x5417c8a  test rcx,rcx
0x5417c8d  je short 0x5417CC0
0x5417c8f  mov rdx,[rsi+0x20]
0x5417c93  sub rdx,rcx
0x5417c96  cmp rdx,0x1000
0x5417c9d  jb short 0x5417CBB
0x5417c9f  mov rax,[rcx-8]
0x5417ca3  add rcx,0xFFFFFFFFFFFFFFF8
0x5417ca7  sub rcx,rax
0x5417caa  cmp rcx,0x20
0x5417cae  jae 0x54186BF
0x5417cb4  add rdx,0x27
0x5417cb8  mov rcx,rax
0x5417cbb  call 0xE935700
0x5417cc0  mov [rsi+0x10],rbx
0x5417cc4  lea rax,[r12+r12*2]
0x5417cc8  lea rax,[rbx+rax*4]
0x5417ccc  mov [rsi+0x18],rax
0x5417cd0  lea rax,[r15+r15*2]
0x5417cd4  lea rax,[rbx+rax*4]
0x5417cd8  mov [rsi+0x20],rax
```

**Phase 9 — 0x5417cdc..0x5417d44: Updates the axis-aligned bounds: min via shuffles of xmm6/xmm7 against movups [rsi+0x130] with cmpltps/andps/andnps/orps, stored back movups [rsi+0x130],xmm3; max via movsd [rsi+0x140] with maxps, stored movlps [rsi+0x140],xmm1; then gates the first per-flag append on byte [rsi+0x188]==1 (else 0x5417DDB). [V]**

```
0x5417c10  movss xmm0,[rbp+rdx]
0x5417c16  movss [rcx+rdx-8],xmm0
0x5417c1c  movss xmm0,[rbp+rdx+4]
0x5417c22  movss [rcx+rdx-4],xmm0
0x5417c28  movss xmm0,[rbp+rdx+8]
0x5417c2e  movss [rcx+rdx],xmm0
0x5417c33  lea r8,[rdx+rbp]
0x5417c37  add r8,0xC
0x5417c3b  add rdx,0xC
0x5417c3f  cmp r8,rax
0x5417c42  jne short 0x5417C10
0x5417c44  jmp short 0x5417C83
0x5417c46  cmp rcx,r13
0x5417c49  je short 0x5417C8A
0x5417c4b  xor eax,eax
0x5417c4d  nop [rax]
0x5417c50  movss xmm0,[rcx+rax]
0x5417c55  movss [rbx+rax],xmm0
0x5417c5a  movss xmm0,[rcx+rax+4]
0x5417c60  movss [rbx+rax+4],xmm0
0x5417c66  movss xmm0,[rcx+rax+8]
0x5417c6c  movss [rbx+rax+8],xmm0
0x5417c72  lea rdx,[rcx+rax]
0x5417c76  add rdx,0xC
0x5417c7a  add rax,0xC
0x5417c7e  cmp rdx,r13
0x5417c81  jne short 0x5417C50
0x5417c83  lea rax,[rsi+0x10]
0x5417c87  mov rcx,[rax]
0x5417c8a  test rcx,rcx
0x5417c8d  je short 0x5417CC0
0x5417c8f  mov rdx,[rsi+0x20]
0x5417c93  sub rdx,rcx
0x5417c96  cmp rdx,0x1000
0x5417c9d  jb short 0x5417CBB
0x5417c9f  mov rax,[rcx-8]
0x5417ca3  add rcx,0xFFFFFFFFFFFFFFF8
0x5417ca7  sub rcx,rax
0x5417caa  cmp rcx,0x20
0x5417cae  jae 0x54186BF
0x5417cb4  add rdx,0x27
0x5417cb8  mov rcx,rax
0x5417cbb  call 0xE935700
0x5417cc0  mov [rsi+0x10],rbx
0x5417cc4  lea rax,[r12+r12*2]
0x5417cc8  lea rax,[rbx+rax*4]
0x5417ccc  mov [rsi+0x18],rax
0x5417cd0  lea rax,[r15+r15*2]
0x5417cd4  lea rax,[rbx+rax*4]
0x5417cd8  mov [rsi+0x20],rax
```

**Phase 9 — 0x5417cdc..0x5417d44: Updates the axis-aligned bounds: min via shuffles of xmm6/xmm7 against movups [rsi+0x130] with cmpltps/andps/andnps/orps, stored back movups [rsi+0x130],xmm3; max via movsd [rsi+0x140] with maxps, stored movlps [rsi+0x140],xmm1; then gates the first per-flag append on byte [rsi+0x188]==1 (else 0x5417DDB). [V]**

```
0x5417cdc  movups xmm0,[rsi+0x130]
0x5417ce3  movaps xmm1,xmm6
0x5417ce6  movlhps xmm1,xmm7
0x5417ce9  movaps xmm2,xmm7
0x5417cec  shufps xmm2,xmm1,0x84
0x5417cf0  movaps xmm1,xmm0
0x5417cf3  shufps xmm1,xmm6,0xC7
0x5417cf7  movaps xmm3,xmm7
0x5417cfa  shufps xmm3,xmm1,0x24
0x5417cfe  movaps xmm1,xmm0
0x5417d01  movsd xmm1,xmm7
0x5417d05  movaps xmm4,xmm0
0x5417d08  shufps xmm4,xmm1,0x24
0x5417d0c  cmpltps xmm3,xmm4
0x5417d10  andps xmm2,xmm3
0x5417d13  andnps xmm3,xmm0
0x5417d16  orps xmm3,xmm2
0x5417d19  movups [rsi+0x130],xmm3
0x5417d20  movsd xmm0,[rsi+0x140]
0x5417d28  movaps xmm1,xmm6
0x5417d2b  shufps xmm1,xmm7,0xD4
0x5417d2f  shufps xmm1,xmm7,0x52
0x5417d33  maxps xmm1,xmm0
0x5417d36  movlps [rsi+0x140],xmm1
0x5417d3d  cmp byte ptr [rsi+0x188],1
0x5417d44  jne 0x5417DDB
```

**Phase 10 — 0x5417d4a..0x5417dd6: Flag [0x188] append into the 16-byte-element vector {begin [rsi+0x28], end [rsi+0x30], cap-end [rsi+0x38]}: capacity vs limit [rsi+0x170] (sar 4), grow via 0x4E00DE0 (recheck flag after, mismatch → 0x5418697); with space, stores the four float channels [0x178]/[0x17C]/[0x180]/[0x184] at end and advances end by 0x10. [V]**

```
0x5417d4a  lea rdi,[rsi+0x28]
0x5417d4e  mov rcx,[rsi+0x170]
0x5417d55  mov [rsp+0x28],rcx
0x5417d5a  mov rax,[rsi+0x38]
0x5417d5e  mov rdx,rax
0x5417d61  sub rdx,[rsi+0x28]
0x5417d65  sar rdx,4
0x5417d69  cmp rcx,rdx
0x5417d6c  jbe short 0x5417D96
0x5417d6e  shr rcx,0x3C
0x5417d72  jne 0x54186B5
0x5417d78  lea rdx,[rsp+0x28]
0x5417d7d  mov rcx,rdi
0x5417d80  call 0x4E00DE0
0x5417d85  cmp byte ptr [rsi+0x188],1
0x5417d8c  jne 0x5418697
0x5417d92  mov rax,[rsi+0x38]
0x5417d96  mov rdx,[rsi+0x30]
0x5417d9a  cmp rdx,rax
0x5417d9d  je 0x5417E62
0x5417da3  movss xmm0,[rsi+0x178]
0x5417dab  movss [rdx],xmm0
0x5417daf  movss xmm0,[rsi+0x17C]
0x5417db7  movss [rdx+4],xmm0
0x5417dbc  movss xmm0,[rsi+0x180]
0x5417dc4  movss [rdx+8],xmm0
0x5417dc9  movss xmm0,[rsi+0x184]
0x5417dd1  movss [rdx+0xC],xmm0
0x5417dd6  add qword ptr [rsi+0x30],0x10
```

**Phase 11 — 0x5417ddb..0x5417e5d: Flag [0x1B4] append into the 4-byte-element vector {begin [rsi+0x70], end [rsi+0x78], cap-end [rsi+0x80]}: capacity vs limit [rsi+0x170] (sar 2), grow via 0x12B4A0 (flag recheck → 0x5418697); with space, stores dword [rsi+0x1B0] at end and advances end by 4 (full vector → push_back path at 0x5417F11); then gates the next flag [0x1BA]. [V]**

```
0x5417ddb  cmp byte ptr [rsi+0x1B4],1
0x5417de2  jne 0x5417E7E
0x5417de8  lea rdi,[rsi+0x70]
0x5417dec  mov rcx,[rsi+0x170]
0x5417df3  mov [rsp+0x28],rcx
0x5417df8  mov rax,[rsi+0x80]
0x5417dff  mov rdx,rax
0x5417e02  sub rdx,[rsi+0x70]
0x5417e06  sar rdx,2
0x5417e0a  cmp rcx,rdx
0x5417e0d  jbe short 0x5417E3A
0x5417e0f  shr rcx,0x3E
0x5417e13  jne 0x54186B0
0x5417e19  lea rdx,[rsp+0x28]
0x5417e1e  mov rcx,rdi
0x5417e21  call 0x12B4A0
0x5417e26  cmp byte ptr [rsi+0x1B4],1
0x5417e2d  jne 0x5418697
0x5417e33  mov rax,[rsi+0x80]
0x5417e3a  mov rdx,[rsi+0x78]
0x5417e3e  cmp rdx,rax
0x5417e41  je 0x5417F11
0x5417e47  mov eax,[rsi+0x1B0]
0x5417e4d  mov [rdx],eax
0x5417e4f  add qword ptr [rsi+0x78],4
0x5417e54  cmp byte ptr [rsi+0x1BA],1
0x5417e5b  je short 0x5417E8B
0x5417e5d  jmp 0x5417F2D
```

**Phase 12 — 0x5417e62..0x5417eda: The full-vector push_back tail of flag [0x188]: call 0x543D7A0(rcx=rdi=&[rsi+0x28] vector, r8=&[rsi+0x178] value); after grow, re-enters flag [0x1B4] at 0x5417DE8 if set; then flag [0x1BA] append into the 2-byte-element vector {begin [rsi+0x88], end [rsi+0x90], cap-end [rsi+0x98]}: capacity vs limit [rsi+0x170] (sar 1, js 0x54186AB), grow via 0x74C870 (flag recheck → 0x5418697). [V]**

```
0x5417e62  lea r8,[rsi+0x178]
0x5417e69  mov rcx,rdi
0x5417e6c  call 0x543D7A0
0x5417e71  cmp byte ptr [rsi+0x1B4],1
0x5417e78  je 0x5417DE8
0x5417e7e  cmp byte ptr [rsi+0x1BA],1
0x5417e85  jne 0x5417F2D
0x5417e8b  lea rdi,[rsi+0x88]
0x5417e92  mov rcx,[rsi+0x170]
0x5417e99  mov [rsp+0x28],rcx
0x5417e9e  mov rax,[rsi+0x98]
0x5417ea5  mov rdx,rax
0x5417ea8  sub rdx,[rsi+0x88]
0x5417eaf  sar rdx,1
0x5417eb2  cmp rcx,rdx
0x5417eb5  jbe short 0x5417EE1
0x5417eb7  test rcx,rcx
0x5417eba  js 0x54186AB
0x5417ec0  lea rdx,[rsp+0x28]
0x5417ec5  mov rcx,rdi
0x5417ec8  call 0x74C870
0x5417ecd  cmp byte ptr [rsi+0x1BA],1
0x5417ed4  jne 0x5418697
0x5417eda  mov rax,[rsi+0x98]
```

**Phase 13 — 0x5417ee1..0x5417f34: Flag [0x1BA] inline append: stores word [rsi+0x1B8] (movzx) at end and advances end by 2 (full → push_back 0x5417FCD/0x74C9C0 path at 0x5417EEB); then gates flag [0x194], entering its vector at 0x5417F3A when set, else 0x5417FE9. [V]**

```
0x5417ee1  mov rdx,[rsi+0x90]
0x5417ee8  cmp rdx,rax
0x5417eeb  je 0x5417FCD
0x5417ef1  movzx eax,word ptr [rsi+0x1B8]
0x5417ef8  mov [rdx],ax
0x5417efb  add qword ptr [rsi+0x90],2
0x5417f03  cmp byte ptr [rsi+0x194],1
0x5417f0a  je short 0x5417F3A
0x5417f0c  jmp 0x5417FE9
0x5417f11  lea r8,[rsi+0x1B0]
0x5417f18  mov rcx,rdi
0x5417f1b  call 0x12B5F0
0x5417f20  cmp byte ptr [rsi+0x1BA],1
0x5417f27  je 0x5417E8B
0x5417f2d  cmp byte ptr [rsi+0x194],1
0x5417f34  jne 0x5417FE9
```

**Phase 14 — 0x5417f3a..0x5417f8b: Flag [0x194] append into the 8-byte-element vector {begin [rsi+0xA0], end [rsi+0xA8], cap-end [rsi+0xB0]}: capacity vs limit [rsi+0x170] (sar 3, shr 0x3D overflow → 0x541869C), grow via 0x4E00F70 (flag recheck → 0x5418697). [V]**

```
0x5417f3a  lea rdi,[rsi+0xA0]
0x5417f41  mov rcx,[rsi+0x170]
0x5417f48  mov [rsp+0x28],rcx
0x5417f4d  mov rax,[rsi+0xB0]
0x5417f54  mov rdx,rax
0x5417f57  sub rdx,[rsi+0xA0]
0x5417f5e  sar rdx,3
0x5417f62  cmp rcx,rdx
0x5417f65  jbe short 0x5417F92
0x5417f67  shr rcx,0x3D
0x5417f6b  jne 0x541869C
0x5417f71  lea rdx,[rsp+0x28]
0x5417f76  mov rcx,rdi
0x5417f79  call 0x4E00F70
0x5417f7e  cmp byte ptr [rsi+0x194],1
0x5417f85  jne 0x5418697
0x5417f8b  mov rax,[rsi+0xB0]
```

**Phase 15 — 0x5417f92..0x5417fe9: Flag [0x194] inline append: stores floats [0x18C]/[0x190] at end (movss pair) and advances end by 8 (full → push_back 0x543DA60 at 0x5417FF7, r8=[rsi+0x18C]); the flag-[0x1BA] full path calls push_back 0x74C9C0 (r8=[rsi+0x1B8]) and re-enters flag [0x194]; when flag [0x194]==0 the jmp 0x5418697 (0x5417FC8) or the min/max update path follows; then gates flag [0x1A0]. [V]**

```
0x5417f92  mov rdx,[rsi+0xA8]
0x5417f99  cmp rdx,rax
0x5417f9c  je short 0x5417FF7
0x5417f9e  movss xmm0,[rsi+0x18C]
0x5417fa6  movss [rdx],xmm0
0x5417faa  movss xmm0,[rsi+0x190]
0x5417fb2  movss [rdx+4],xmm0
0x5417fb7  add qword ptr [rsi+0xA8],8
0x5417fbf  cmp byte ptr [rsi+0x194],0
0x5417fc6  jne short 0x5418013
0x5417fc8  jmp 0x5418697
0x5417fcd  lea r8,[rsi+0x1B8]
0x5417fd4  mov rcx,rdi
0x5417fd7  call 0x74C9C0
0x5417fdc  cmp byte ptr [rsi+0x194],1
0x5417fe3  je 0x5417F3A
0x5417fe9  cmp byte ptr [rsi+0x1A0],1
0x5417ff0  je short 0x541805C
0x5417ff2  jmp 0x54180E5
```

**Phase 16 — 0x5417ff7..0x541804f: The flag-[0x194] full-vector push_back (0x543DA60, r8=[rsi+0x18C]) and, when flag clears after the call (0x5418006 je 0x5418697), the UV min/max update: movsd xmm0=[rsi+0x18C] vs movupd [rsi+0x148] with unpcklpd/cmpltps/andpd/andnpd/orpd, stored movupd [rsi+0x148],xmm2; then gates flag [0x1A0]. [V]**

```
0x5417ff7  lea r8,[rsi+0x18C]
0x5417ffe  mov rcx,rdi
0x5418001  call 0x543DA60
0x5418006  cmp byte ptr [rsi+0x194],0
0x541800d  je 0x5418697
0x5418013  movsd xmm0,[rsi+0x18C]
0x541801b  movupd xmm1,[rsi+0x148]
0x5418023  movapd xmm2,xmm1
0x5418027  movsd xmm2,xmm0
0x541802b  movapd xmm3,xmm1
0x541802f  unpcklpd xmm3,xmm0
0x5418033  unpcklpd xmm0,xmm0
0x5418037  cmpltps xmm2,xmm3
0x541803b  andpd xmm0,xmm2
0x541803f  andnpd xmm2,xmm1
0x5418043  orpd xmm2,xmm0
0x5418047  movupd [rsi+0x148],xmm2
0x541804f  cmp byte ptr [rsi+0x1A0],1
0x5418056  jne 0x54180E5
```

**Phase 17 — 0x541805c..0x54180e5: Flag [0x1A0] append into the 8-byte-element vector {begin [rsi+0xB8], end [rsi+0xC0], cap-end [rsi+0xC8]}: capacity vs limit [rsi+0x170] (sar 3, shr 0x3D → 0x541869C), grow via 0x4E00F70 (flag recheck → 0x5418697); with space, stores floats [0x198]/[0x19C] at end and advances end by 8 (full → push_back at 0x5418189); then gates flag [0x1AC]. [V]**

```
0x541805c  lea rdi,[rsi+0xB8]
0x5418063  mov rcx,[rsi+0x170]
0x541806a  mov [rsp+0x28],rcx
0x541806f  mov rax,[rsi+0xC8]
0x5418076  mov rdx,rax
0x5418079  sub rdx,[rsi+0xB8]
0x5418080  sar rdx,3
0x5418084  cmp rcx,rdx
0x5418087  jbe short 0x54180B4
0x5418089  shr rcx,0x3D
0x541808d  jne 0x541869C
0x5418093  lea rdx,[rsp+0x28]
0x5418098  mov rcx,rdi
0x541809b  call 0x4E00F70
0x54180a0  cmp byte ptr [rsi+0x1A0],1
0x54180a7  jne 0x5418697
0x54180ad  mov rax,[rsi+0xC8]
0x54180b4  mov rdx,[rsi+0xC0]
0x54180bb  cmp rdx,rax
0x54180be  je 0x5418189
0x54180c4  movss xmm0,[rsi+0x198]
0x54180cc  movss [rdx],xmm0
0x54180d0  movss xmm0,[rsi+0x19C]
0x54180d8  movss [rdx+4],xmm0
0x54180dd  add qword ptr [rsi+0xC0],8
0x54180e5  cmp byte ptr [rsi+0x1AC],1
0x54180ec  jne 0x54181A5
```

**Phase 18 — 0x54180f2..0x541817b: Flag [0x1AC] append into the 8-byte-element vector {begin [rsi+0xD0], end [rsi+0xD8], cap-end [rsi+0xE0]}: capacity vs limit [rsi+0x170] (sar 3, shr 0x3D → 0x541869C), grow via 0x4E00F70 (flag recheck → 0x5418697); with space, stores floats [0x1A4]/[0x1A8] at end and advances end by 8; then gates flag [0x1BE]. [V]**

```
0x54180f2  lea rdi,[rsi+0xD0]
0x54180f9  mov rcx,[rsi+0x170]
0x5418100  mov [rsp+0x28],rcx
0x5418105  mov rax,[rsi+0xE0]
0x541810c  mov rdx,rax
0x541810f  sub rdx,[rsi+0xD0]
0x5418116  sar rdx,3
0x541811a  cmp rcx,rdx
0x541811d  jbe short 0x541814A
0x541811f  shr rcx,0x3D
0x5418123  jne 0x541869C
0x5418129  lea rdx,[rsp+0x28]
0x541812e  mov rcx,rdi
0x5418131  call 0x4E00F70
0x5418136  cmp byte ptr [rsi+0x1AC],1
0x541813d  jne 0x5418697
0x5418143  mov rax,[rsi+0xE0]
0x541814a  mov rdx,[rsi+0xD8]
0x5418151  cmp rdx,rax
0x5418154  je 0x5418238
0x541815a  movss xmm0,[rsi+0x1A4]
0x5418162  movss [rdx],xmm0
0x5418166  movss xmm0,[rsi+0x1A8]
0x541816e  movss [rdx+4],xmm0
0x5418173  add qword ptr [rsi+0xD8],8
0x541817b  cmp byte ptr [rsi+0x1BE],1
0x5418182  je short 0x54181B2
0x5418184  jmp 0x5418254
```

**Phase 19 — 0x5418189..0x541820f: Flag-[0x1A0] full-vector push_back (0x543DA60, r8=[rsi+0x198]); then flag [0x1BE] append into the 2-byte-element vector {begin [rsi+0xE8], end [rsi+0xF0], cap-end [rsi+0xF8]}: capacity vs limit [rsi+0x170] (sar 1, js 0x54186AB), grow via 0x74C870 (flag recheck → 0x5418697). [V]**

```
0x5418189  lea r8,[rsi+0x198]
0x5418190  mov rcx,rdi
0x5418193  call 0x543DA60
0x5418198  cmp byte ptr [rsi+0x1AC],1
0x541819f  je 0x54180F2
0x54181a5  cmp byte ptr [rsi+0x1BE],1
0x54181ac  jne 0x5418254
0x54181b2  lea rdi,[rsi+0xE8]
0x54181b9  mov rcx,[rsi+0x170]
0x54181c0  mov [rsp+0x28],rcx
0x54181c5  mov rax,[rsi+0xF8]
0x54181cc  mov rdx,rax
0x54181cf  sub rdx,[rsi+0xE8]
0x54181d6  sar rdx,1
0x54181d9  cmp rcx,rdx
0x54181dc  jbe short 0x5418208
0x54181de  test rcx,rcx
0x54181e1  js 0x54186AB
0x54181e7  lea rdx,[rsp+0x28]
0x54181ec  mov rcx,rdi
0x54181ef  call 0x74C870
0x54181f4  cmp byte ptr [rsi+0x1BE],1
0x54181fb  jne 0x5418697
0x5418201  mov rax,[rsi+0xF8]
0x5418208  mov rdx,[rsi+0xF0]
0x541820f  cmp rdx,rax
```

**Phase 20 — 0x5418212..0x5418268: Flag [0x1BE] inline append: stores word [rsi+0x1BC] (movzx) at end, advances end by 2 (full → push_back at 0x54182E7); gates flag [0x1C4]; the flag-[0x1AC] full path calls push_back 0x543DA60 (r8=[rsi+0x1A4]) and re-enters flag [0x1BE]; flag [0x1C4] append begins at 0x5418261 into {begin [rsi+0x100], ...}. [V]**

```
0x5418212  je 0x54182E7
0x5418218  movzx eax,word ptr [rsi+0x1BC]
0x541821f  mov [rdx],ax
0x5418222  add qword ptr [rsi+0xF0],2
0x541822a  cmp byte ptr [rsi+0x1C4],1
0x5418231  je short 0x5418261
0x5418233  jmp 0x5418303
0x5418238  lea r8,[rsi+0x1A4]
0x541823f  mov rcx,rdi
0x5418242  call 0x543DA60
0x5418247  cmp byte ptr [rsi+0x1BE],1
0x541824e  je 0x54181B2
0x5418254  cmp byte ptr [rsi+0x1C4],1
0x541825b  jne 0x5418303
0x5418261  lea rdi,[rsi+0x100]
0x5418268  mov rcx,[rsi+0x170]
```

**Phase 21 — 0x541826f..0x5418310: Flag [0x1C4] append into the 4-byte-element vector {begin [rsi+0x100], end [rsi+0x108], cap-end [rsi+0x110]}: capacity vs limit [rsi+0x170] (sar 2, shr 0x3E → 0x54186B0), grow via 0x12B4A0 (flag recheck → 0x5418697); with space, stores dword [rsi+0x1C0] at end and advances end by 4 (full → push_back at 0x5418391); then gates flag [0x1C9]. [V]**

```
0x541826f  mov [rsp+0x28],rcx
0x5418274  mov rax,[rsi+0x110]
0x541827b  mov rdx,rax
0x541827e  sub rdx,[rsi+0x100]
0x5418285  sar rdx,2
0x5418289  cmp rcx,rdx
0x541828c  jbe short 0x54182B9
0x541828e  shr rcx,0x3E
0x5418292  jne 0x54186B0
0x5418298  lea rdx,[rsp+0x28]
0x541829d  mov rcx,rdi
0x54182a0  call 0x12B4A0
0x54182a5  cmp byte ptr [rsi+0x1C4],1
0x54182ac  jne 0x5418697
0x54182b2  mov rax,[rsi+0x110]
0x54182b9  mov rdx,[rsi+0x108]
0x54182c0  cmp rdx,rax
0x54182c3  je 0x5418391
0x54182c9  mov eax,[rsi+0x1C0]
0x54182cf  mov [rdx],eax
0x54182d1  add qword ptr [rsi+0x108],4
0x54182d9  cmp byte ptr [rsi+0x1C9],1
0x54182e0  je short 0x5418310
0x54182e2  jmp 0x54183AD
0x54182e7  lea r8,[rsi+0x1BC]
0x54182ee  mov rcx,rdi
0x54182f1  call 0x74C9C0
0x54182f6  cmp byte ptr [rsi+0x1C4],1
0x54182fd  je 0x5418261
0x5418303  cmp byte ptr [rsi+0x1C9],1
0x541830a  jne 0x54183AD
```

**Phase 22 — 0x5418310..0x54183ba: Flag [0x1C9] append into the 1-byte-element vector {begin [rsi+0x118], end [rsi+0x120], cap-end [rsi+0x128]}: capacity vs limit [rsi+0x170] (no shift, js 0x54186BA), grow via 0x2F6DF0 (flag recheck → 0x5418697); with space, stores byte [rsi+0x1C8] at end and increments end (full → push_back at 0x541847B); then gates batch flag [0x2A1] (unset → exit 0x541864A). [V]**

```
0x5418310  lea rdi,[rsi+0x118]
0x5418317  mov rcx,[rsi+0x170]
0x541831e  mov [rsp+0x28],rcx
0x5418323  mov rax,[rsi+0x128]
0x541832a  mov rdx,rax
0x541832d  sub rdx,[rsi+0x118]
0x5418334  cmp rcx,rdx
0x5418337  jbe short 0x5418363
0x5418339  test rcx,rcx
0x541833c  js 0x54186BA
0x5418342  lea rdx,[rsp+0x28]
0x5418347  mov rcx,rdi
0x541834a  call 0x2F6DF0
0x541834f  cmp byte ptr [rsi+0x1C9],1
0x5418356  jne 0x5418697
0x541835c  mov rax,[rsi+0x128]
0x5418363  mov rdx,[rsi+0x120]
0x541836a  cmp rdx,rax
0x541836d  je 0x541847B
0x5418373  movzx eax,byte ptr [rsi+0x1C8]
0x541837a  mov [rdx],al
0x541837c  inc qword ptr [rsi+0x120]
0x5418383  cmp byte ptr [rsi+0x2A1],1
0x541838a  je short 0x54183BA
0x541838c  jmp 0x541864A
```

**Phase 23 — 0x5418391..0x5418411: Flag-[0x1C4] full-vector push_back (0x12B5F0, r8=[rsi+0x1C0]); then the [0x2A1] batch block: reads mode [rsi+8], builds rdx=0x200030400>>cl with cmovae edx,ecx gate on al<5; accumulates position movlps [rsi+0x200],xmm7 / movss [rsi+0x208],xmm6 and increments batch counter [rsi+0x20C]; when counter reaches the mode byte, resets [rsi+0x20C]=0 and proceeds to flush. [V]**

```
0x5418391  lea r8,[rsi+0x1C0]
0x5418398  mov rcx,rdi
0x541839b  call 0x12B5F0
0x54183a0  cmp byte ptr [rsi+0x1C9],1
0x54183a7  je 0x5418310
0x54183ad  cmp byte ptr [rsi+0x2A1],1
0x54183b4  jne 0x541864A
0x54183ba  mov ecx,[rsi+8]
0x54183bd  mov eax,ecx
0x54183bf  shl ecx,3
0x54183c2  mov rdx,0x200030400
0x54183cc  shr rdx,cl
0x54183cf  xor ecx,ecx
0x54183d1  cmp al,5
0x54183d3  cmovae edx,ecx
0x54183d6  movsd xmm0,[rsi+0x200]
0x54183de  addps xmm7,xmm0
0x54183e1  movlps [rsi+0x200],xmm7
0x54183e8  addss xmm6,[rsi+0x208]
0x54183f0  movss [rsi+0x208],xmm6
0x54183f8  mov ecx,[rsi+0x20C]
0x54183fe  inc ecx
0x5418400  mov [rsi+0x20C],ecx
0x5418406  movzx eax,dl
0x5418409  cmp ecx,eax
0x541840b  jne 0x541864A
0x5418411  mov dword ptr [rsi+0x20C],0
```

**Phase 24 — 0x541841b..0x5418497: Batch flush record build: loads flag bytes [0x1E4]/[0x1E5], computes 1/count via cvtsi2ss/divss by [0xEEC8060], normalizes xmm8=xmm7/count and xmm6*=count; appends a 16-byte record into {begin [rsi+0x1E8], end [rsi+0x1F0], cap-end [rsi+0x1F8]} inline (mov [rbx],r13b / mov [rbx+1],bpl / movlps [rbx+4],xmm8 / movss [rbx+0xC],xmm6, end +=0x10, jmp 0x541862C); full → push_back 0x2F6F30 (flag-[0x1C9] path, r8=[rsi+0x1C8]) then re-enters the batch gate. [V]**

```
0x541841b  movzx r13d,byte ptr [rsi+0x1E4]
0x5418423  movzx ebp,byte ptr [rsi+0x1E5]
0x541842a  xorps xmm0,xmm0
0x541842d  cvtsi2ss xmm0,eax
0x5418431  movss xmm8,[0xEEC8060]
0x541843a  divss xmm8,xmm0
0x541843f  mulss xmm6,xmm8
0x5418444  shufps xmm8,xmm8,0
0x5418449  mulps xmm8,xmm7
0x541844d  mov rbx,[rsi+0x1F0]
0x5418454  cmp rbx,[rsi+0x1F8]
0x541845b  je short 0x541849C
0x541845d  mov [rbx],r13b
0x5418460  mov [rbx+1],bpl
0x5418464  movlps [rbx+4],xmm8
0x5418469  movss [rbx+0xC],xmm6
0x541846e  add qword ptr [rsi+0x1F0],0x10
0x5418476  jmp 0x541862C
0x541847b  lea r8,[rsi+0x1C8]
0x5418482  mov rcx,rdi
0x5418485  call 0x2F6F30
0x541848a  cmp byte ptr [rsi+0x2A1],1
0x5418491  je 0x54183BA
0x5418497  jmp 0x541864A
```

**Phase 25 — 0x541849c..0x5418541: The 16-byte-record vector grow path: new capacity via cmovbe/cmova (cap 0xFFFFFFFFFFFFFFF records, shr 0x3C overflow → 0x54186A1), byte size rax*16 (shl 4); for rax>=0x100 uses the 32-byte-aligned allocator (lea r15,[rdi+0x27], header at [r15-8], null → 0x5418684), else the plain allocator (null → 0x9BC830); zero capacity → r15d=0. [V]**

```
0x541849c  mov r14,rbx
0x541849f  sub r14,[rsi+0x1E8]
0x54184a6  mov rcx,r14
0x54184a9  sar rcx,4
0x54184ad  lea r12,[rcx+1]
0x54184b1  mov rax,rcx
0x54184b4  shr rax,1
0x54184b7  mov rdx,0xFFFFFFFFFFFFFFF
0x54184c1  mov r8,rdx
0x54184c4  sub r8,rax
0x54184c7  add rax,rcx
0x54184ca  cmp rax,r12
0x54184cd  cmovbe rax,r12
0x54184d1  cmp rcx,r8
0x54184d4  cmova rax,rdx
0x54184d8  mov rcx,rax
0x54184db  shr rcx,0x3C
0x54184df  jne 0x54186A1
0x54184e5  mov rdi,rax
0x54184e8  shl rdi,4
0x54184ec  test rax,rax
0x54184ef  je short 0x5418568
0x54184f1  cmp rax,0x100
0x54184f7  jb short 0x5418541
0x54184f9  mov rcx,0xFFFFFFFFFFFFFFE
0x5418503  cmp rax,rcx
0x5418506  jae 0x54186A1
0x541850c  lea r15,[rdi+0x27]
0x5418510  mov rcx,[0x1233E1A8]
0x5418517  mov rax,[rcx]
0x541851a  mov rax,[rax+8]
0x541851e  mov rdx,r15
0x5418521  call qword ptr [0xF99FFA0]
0x5418527  test rax,rax
0x541852a  je 0x5418684
0x5418530  mov r15,rax
0x5418533  add r15,0x27
0x5418537  and r15,0xFFFFFFFFFFFFFFE0
0x541853b  mov [r15-8],rax
0x541853f  jmp short 0x541856B
```

**Phase 26 — 0x5418541..0x54185c8: Plain allocation path for the record buffer; writes the pending record at r15+r14 (mov [r15+r14],r13b / +1,bpl / movlps +4,xmm8 / movss +0xC,xmm6); copies old records with two memmove variants (0xEEC6DE0: middle split r14=r15+r14+0x10 with [rbx..end] tail, or whole [begin..old-end]) and stores the new record byte before the copy. [V]**

```
0x5418541  mov rcx,[0x1233E1A8]
0x5418548  mov rax,[rcx]
0x541854b  mov rax,[rax+8]
0x541854f  mov rdx,rdi
0x5418552  call qword ptr [0xF99FFA0]
0x5418558  mov r15,rax
0x541855b  test rax,rax
0x541855e  jne short 0x541856B
0x5418560  mov rcx,rdi
0x5418563  call 0x9BC830
0x5418568  xor r15d,r15d
0x541856b  mov [r15+r14],r13b
0x541856f  mov [r15+r14+1],bpl
0x5418574  movlps [r15+r14+4],xmm8
0x541857a  movss [r15+r14+0xC],xmm6
0x5418581  cmp rbx,[rsi+0x1F0]
0x5418588  je short 0x54185B8
0x541858a  add r14,r15
0x541858d  add r14,0x10
0x5418591  mov rdx,[rsi+0x1E8]
0x5418598  mov r8,rbx
0x541859b  sub r8,rdx
0x541859e  mov rcx,r15
0x54185a1  call 0xEEC6DE0
0x54185a6  mov r8,[rsi+0x1F0]
0x54185ad  sub r8,rbx
0x54185b0  mov rcx,r14
0x54185b3  mov rdx,rbx
0x54185b6  jmp short 0x54185C8
0x54185b8  mov rdx,[rsi+0x1E8]
0x54185bf  sub rbx,rdx
0x54185c2  mov rcx,r15
0x54185c5  mov r8,rbx
0x54185c8  call 0xEEC6DE0
```

**Phase 27 — 0x54185cd..0x5418670: Frees the old record buffer (0xE935700 with 0x1000/header checks, jae 0x54186BF); commits begin=[rsi+0x1E8]=r15, end=[rsi+0x1F0]=r15+r12*16, cap-end=[rsi+0x1F8]=r15+rdi; resets the batch accumulator {[rsi+0x200]=0 qword, [rsi+0x208]=0 dword} and word [rsi+0x1E4]=6; epilogue restores xmm6-xmm9, pops r15..rbx, ret. [V]**

```
0x54185cd  mov rcx,[rsi+0x1E8]
0x54185d4  test rcx,rcx
0x54185d7  je short 0x541860D
0x54185d9  mov rdx,[rsi+0x1F8]
0x54185e0  sub rdx,rcx
0x54185e3  cmp rdx,0x1000
0x54185ea  jb short 0x5418608
0x54185ec  mov rax,[rcx-8]
0x54185f0  add rcx,0xFFFFFFFFFFFFFFF8
0x54185f4  sub rcx,rax
0x54185f7  cmp rcx,0x20
0x54185fb  jae 0x54186BF
0x5418601  add rdx,0x27
0x5418605  mov rcx,rax
0x5418608  call 0xE935700
0x541860d  mov [rsi+0x1E8],r15
0x5418614  shl r12,4
0x5418618  add r12,r15
0x541861b  mov [rsi+0x1F0],r12
0x5418622  add rdi,r15
0x5418625  mov [rsi+0x1F8],rdi
0x541862c  lea rax,[rsi+0x200]
0x5418633  mov dword ptr [rax+8],0
0x541863a  mov qword ptr [rax],0
0x5418641  mov word ptr [rsi+0x1E4],6
0x541864a  movaps xmm6,[rsp+0x30]
0x541864f  movaps xmm7,[rsp+0x40]
0x5418654  movaps xmm8,[rsp+0x50]
0x541865a  movaps xmm9,[rsp+0x60]
0x5418660  add rsp,0x78
0x5418664  pop rbx
0x5418665  pop rbp
0x5418666  pop rdi
0x5418667  pop rsi
0x5418668  pop r12
0x541866a  pop r13
0x541866c  pop r14
0x541866e  pop r15
0x5418670  ret
```

**Phase 28 — 0x5418671..0x54186df: Failure tails: two bad_alloc-after-null paths (0x9BC830 then jmp back into the aligned-alloc continuation), flag-mismatch throw 0x1A2800, capacity/length throws 0x75B60/0x75740, and the 0x54186BF sanity trap (zero-arg call [0xF9A8C78]) followed by eight int3 pad bytes. [V]**

```
0x5418671  mov rcx,r14
0x5418674  mov rbx,rax
0x5418677  call 0x9BC830
0x541867c  mov rax,rbx
0x541867f  jmp 0x5417B58
0x5418684  mov rcx,r15
0x5418687  mov r15,rax
0x541868a  call 0x9BC830
0x541868f  mov rax,r15
0x5418692  jmp 0x5418530
0x5418697  call 0x1A2800
0x541869c  call 0x75B60
0x54186a1  call 0x75740
0x54186a6  call 0x75B60
0x54186ab  call 0x75B60
0x54186b0  call 0x75B60
0x54186b5  call 0x75B60
0x54186ba  call 0x75B60
0x54186bf  mov qword ptr [rsp+0x20],0
0x54186c8  xor ecx,ecx
0x54186ca  xor edx,edx
0x54186cc  xor r8d,r8d
0x54186cf  xor r9d,r9d
0x54186d2  call qword ptr [0xF9A8C78]
0x54186d8  int3
0x54186d9  int3
0x54186da  int3
0x54186db  int3
0x54186dc  int3
0x54186dd  int3
0x54186de  int3
0x54186df  int3
```

<!-- APPEND -->

## Field map — memory offsets touched (site = instruction address; instr verbatim from the listing; size from the instruction)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| task+0x00 | 8 | 0x541bf32 | `0x541bf32  mov [rcx],rax` | W: vtable 0xEFCC480 stored at [this] (texload_task ctor) |
| task+0x08 | 8 | 0x541bf7e | `0x541bf7e  mov [r14+8],rax` | W: refcount control-block pointer parked at this+8 |
| task+0x10 | 8 | 0x541bf82 | `0x541bf82  mov [r14+0x10],rdi` | W: refcount control-block pointer parked at this+0x10 |
| task+0x18 | 8 | 0x541bf9f | `0x541bf9f  mov [r14+0x18],rax` | W: vtable 0xF24A768 stored at this+0x18 |
| task+0x20 | 16 | 0x541bf89 | `0x541bf89  movups [r14+0x20],xmm0` | W: this+0x20 zeroed (16 bytes) |
| task+0x30 | 8 | 0x541bfc4 | `0x541bfc4  mov [r14+0x30],rcx` | W: shared_ptr arg1 pointer stored at this+0x30 |
| task+0x38 | 8 | 0x541bfc8 | `0x541bfc8  mov [r14+0x38],rax` | W: shared_ptr arg1 control stored at this+0x38 |
| task+0x40 | 8 | 0x541bfd0 | `0x541bfd0  mov [r14+0x40],rax` | W: shared_ptr arg1 end stored at this+0x40 |
| task+0x48 | - | 0x541c0f5 | `0x541c0f5  add rcx,0x48` | R/W: this+0x48 address passed as rcx to name registration 0x58A2EC0 |
| task+0x1A8 | 8 | 0x541c174 | `0x541c174  mov [r10+0x1A8],rdi` | W: 0x88-byte intrusive-list sentinel pointer stored at this+0x1A8 (zeroed first at 0x541c132) |
| task+0x1B8 | 16 | 0x541c17e | `0x541c17e  movups [r10+0x1B8],xmm0` | W: this+0x1B8 zeroed then shared_ptr arg2 pointer stored at this+0x1B8 (0x541c1a2) |
| task+0x1C0 | 8 | 0x541c1a9 | `0x541c1a9  mov [r10+0x1C0],rax` | W: shared_ptr arg2 control stored at this+0x1C0 |
| task+0x1C8 | 8 | 0x541c1b4 | `0x541c1b4  mov [r10+0x1C8],rax` | W: shared_ptr arg2 end stored at this+0x1C8 |
| task+0x1D0 | 8 | 0x541c1e3 | `0x541c1e3  mov [r10+0x1D0],rsi` | W: arg3 (rsi) stored at this+0x1D0 |
| task+0x1D8 | - | 0x541c25f | `0x541c25f  lea rcx,[rax+0x208]` | R: this+0x1D8 passed as rcx to 0x5A4C7C0 |
| task+0x208 | 16 | 0x541c274 | `0x541c274  movups [rax+0x208],xmm0` | W: this+0x208 zeroed (16 bytes) |
| task+0x218 | 16 | 0x541c26d | `0x541c26d  movups [rax+0x218],xmm0` | W: this+0x218 zeroed (16 bytes); list head later at [rbx+0x218] |
| task+0x228 | 8 | 0x541c27b | `0x541c27b  mov qword ptr [rax+0x228],0` | W: this+0x228 zeroed |
| task+0x220 | 8 | 0x541c2cc | `0x541c2cc  mov [rax+0x220],rsi` | W: 0x60-byte sentinel stored at this+0x220 |
| task+0x230 | 8 | 0x541c323 | `0x541c323  mov [rax+0x230],rsi` | W: 0x68-byte sentinel stored at this+0x230 (zeroed first at 0x541c2d6) |
| task+0x240 | 16 | 0x541c338 | `0x541c338  movups [rax+0x240],xmm0` | W: this+0x240 zeroed (16 bytes) |
| task+0x250 | 8 | 0x541c33f | `0x541c33f  mov qword ptr [rax+0x250],0` | W: this+0x250 zeroed |
| task+0x248 | 8 | 0x541c390 | `0x541c390  mov [rax+0x248],rsi` | W: 0x70-byte sentinel stored at this+0x248 |
| task+0x258 | 16 | 0x541c3a5 | `0x541c3a5  movups [rax+0x258],xmm0` | W: this+0x258 zeroed (16 bytes) |
| task+0x268 | 8 | 0x541c3fe | `0x541c3fe  mov [rcx+0x268],rax` | W: refcount object #3 pointer parked at this+0x268 |
| task+0x270 | 8 | 0x541c405 | `0x541c405  mov [rcx+0x270],rsi` | W: refcount object #3 stored at this+0x270 |
| task+0x278 | 16 | 0x541c40f | `0x541c40f  movups [rcx+0x278],xmm0` | W: this+0x278 zeroed (16 bytes) |
| group+0x00 | 1 | 0x5417996 | `0x5417996  mov byte ptr [rcx],1` | W (texgroup this): dirty flag byte [this]=1 |
| group+0x298 | 4 | 0x5417990 | `0x5417990  mov [rcx+0x298],eax` | W: queue counter incremented at [this+0x298] (read at 0x5417976) |
| group+0x29C | 4 | 0x541797c | `0x541797c  cmp eax,[rcx+0x29C]` | R: queue limit compared at [this+0x29C] |
| group+0x21C | 4 | 0x54179ab | `0x54179ab  mulss xmm0,[rsi+0x21C]` | R: position transform scale [this+0x21C] |
| group+0x22C | 4 | 0x54179b3 | `0x54179b3  mulss xmm2,[rsi+0x22C]` | R: [this+0x22C] |
| group+0x23C | 4 | 0x54179bb | `0x54179bb  movss xmm3,[rsi+0x23C]` | R: [this+0x23C] |
| group+0x24C | 4 | 0x54179c7 | `0x54179c7  addss xmm3,[rsi+0x24C]` | R: [this+0x24C] |
| group+0x214 | 8 | 0x54179db | `0x54179db  movsd xmm0,[rsi+0x214]` | R: matrix row [this+0x214] |
| group+0x224 | 8 | 0x54179e6 | `0x54179e6  movsd xmm1,[rsi+0x224]` | R: [this+0x224] |
| group+0x234 | 8 | 0x54179ee | `0x54179ee  movsd xmm2,[rsi+0x234]` | R: [this+0x234] |
| group+0x244 | 8 | 0x54179f6 | `0x54179f6  movsd xmm4,[rsi+0x244]` | R: [this+0x244] |
| group+0x1D8 | 8 | 0x5417a18 | `0x5417a18  movsd xmm8,[rsi+0x1D8]` | R: scale [this+0x1D8] |
| group+0x1E0 | 4 | 0x5417a21 | `0x5417a21  mulss xmm6,[rsi+0x1E0]` | R: [this+0x1E0] |
| group+0x1D4 | 4 | 0x5417a29 | `0x5417a29  addss xmm6,[rsi+0x1D4]` | R: [this+0x1D4] |
| 0x1CC | 8 | 0x5417a31 | `0x5417a31  movsd xmm9,[rsi+0x1CC]` | R: offset [this+0x1CC] |
| group+0x10 | 8 | 0x5417b9c | `0x5417b9c  mov rcx,[rsi+0x10]` | R: vertex vector begin [this+0x10] |
| group+0x18 | 8 | 0x5417aaa | `0x5417aaa  add qword ptr [rsi+0x18],0xC` | W: vertex vector end [this+0x18] advanced by 0xC |
| group+0x20 | 8 | 0x5417a4a | `0x5417a4a  mov r13,[rsi+0x20]` | R: vertex vector cap-end [this+0x20] |
| group+0x170 | 8 | 0x5417a3e | `0x5417a3e  mov rax,[rsi+0x170]` | R: growth limit [this+0x170] |
| group+0x130 | 16 | 0x5417d19 | `0x5417d19  movups [rsi+0x130],xmm3` | W: min bounds [this+0x130] (16 bytes) |
| group+0x140 | 8 | 0x5417d36 | `0x5417d36  movlps [rsi+0x140],xmm1` | W: max bounds [this+0x140] |
| group+0x188 | 1 | 0x5417d3d | `0x5417d3d  cmp byte ptr [rsi+0x188],1` | R: flag byte [this+0x188] |
| group+0x28 | 8 | 0x5417d61 | `0x5417d61  sub rdx,[rsi+0x28]` | R: 16-byte vector begin [this+0x28] |
| group+0x30 | 8 | 0x5417dd6 | `0x5417dd6  add qword ptr [rsi+0x30],0x10` | W: 16-byte vector end [this+0x30] advanced by 0x10 |
| group+0x38 | 8 | 0x5417d5a | `0x5417d5a  mov rax,[rsi+0x38]` | R: 16-byte vector cap-end [this+0x38] |
| group+0x178 | 4 | 0x5417da3 | `0x5417da3  movss xmm0,[rsi+0x178]` | R: channel [this+0x178] |
| group+0x17C | 4 | 0x5417daf | `0x5417daf  movss xmm0,[rsi+0x17C]` | R: [this+0x17C] |
| group+0x180 | 4 | 0x5417dbc | `0x5417dbc  movss xmm0,[rsi+0x180]` | R: [this+0x180] |
| group+0x184 | 4 | 0x5417dc9 | `0x5417dc9  movss xmm0,[rsi+0x184]` | R: [this+0x184] |
| group+0x70 | 8 | 0x5417e02 | `0x5417e02  sub rdx,[rsi+0x70]` | R: 4-byte vector begin [this+0x70] |
| group+0x78 | 8 | 0x5417e4f | `0x5417e4f  add qword ptr [rsi+0x78],4` | W: 4-byte vector end [this+0x78] advanced by 4 |
| group+0x80 | 8 | 0x5417df8 | `0x5417df8  mov rax,[rsi+0x80]` | R: 4-byte vector cap-end [this+0x80] |
| group+0x1B0 | 4 | 0x5417e47 | `0x5417e47  mov eax,[rsi+0x1B0]` | R: dword value [this+0x1B0] |
| group+0x1B4 | 1 | 0x5417ddb | `0x5417ddb  cmp byte ptr [rsi+0x1B4],1` | R: flag byte [this+0x1B4] |
| group+0x88 | 8 | 0x5417ea8 | `0x5417ea8  sub rdx,[rsi+0x88]` | R: 2-byte vector begin [this+0x88] |
| group+0x90 | 8 | 0x5417efb | `0x5417efb  add qword ptr [rsi+0x90],2` | W: 2-byte vector end [this+0x90] advanced by 2 |
| group+0x98 | 8 | 0x5417e9e | `0x5417e9e  mov rax,[rsi+0x98]` | R: 2-byte vector cap-end [this+0x98] |
| group+0x1B8 | 2 | 0x5417ef1 | `0x5417ef1  movzx eax,word ptr [rsi+0x1B8]` | R: word value [this+0x1B8] |
| group+0x194 | 1 | 0x5417f03 | `0x5417f03  cmp byte ptr [rsi+0x194],1` | R: flag byte [this+0x194] |
| group+0xA0 | 8 | 0x5417f57 | `0x5417f57  sub rdx,[rsi+0xA0]` | R: 8-byte vector begin [this+0xA0] |
| group+0xA8 | 8 | 0x5417fb7 | `0x5417fb7  add qword ptr [rsi+0xA8],8` | W: 8-byte vector end [this+0xA8] advanced by 8 |
| group+0xB0 | 8 | 0x5417f4d | `0x5417f4d  mov rax,[rsi+0xB0]` | R: 8-byte vector cap-end [this+0xB0] |
| group+0x18C | 4 | 0x5417f9e | `0x5417f9e  movss xmm0,[rsi+0x18C]` | R: float [this+0x18C] |
| group+0x190 | 4 | 0x5417faa | `0x5417faa  movss xmm0,[rsi+0x190]` | R: float [this+0x190] |
| group+0x148 | 16 | 0x5418047 | `0x5418047  movupd [rsi+0x148],xmm2` | W: UV min/max [this+0x148] (16 bytes) |
| group+0x1A0 | 1 | 0x541804f | `0x541804f  cmp byte ptr [rsi+0x1A0],1` | R: flag byte [this+0x1A0] |
| group+0xB8 | 8 | 0x5418079 | `0x5418079  sub rdx,[rsi+0xB8]` | R: 8-byte vector begin [this+0xB8] |
| group+0xC0 | 8 | 0x54180dd | `0x54180dd  add qword ptr [rsi+0xC0],8` | W: 8-byte vector end [this+0xC0] advanced by 8 |
| group+0xC8 | 8 | 0x541806f | `0x541806f  mov rax,[rsi+0xC8]` | R: 8-byte vector cap-end [this+0xC8] |
| group+0x198 | 4 | 0x54180c4 | `0x54180c4  movss xmm0,[rsi+0x198]` | R: float [this+0x198] |
| group+0x19C | 4 | 0x54180d0 | `0x54180d0  movss xmm0,[rsi+0x19C]` | R: float [this+0x19C] |
| group+0x1AC | 1 | 0x54180e5 | `0x54180e5  cmp byte ptr [rsi+0x1AC],1` | R: flag byte [this+0x1AC] |
| group+0xD0 | 8 | 0x541810f | `0x541810f  sub rdx,[rsi+0xD0]` | R: 8-byte vector begin [this+0xD0] |
| group+0xD8 | 8 | 0x5418173 | `0x5418173  add qword ptr [rsi+0xD8],8` | W: 8-byte vector end [this+0xD8] advanced by 8 |
| group+0xE0 | 8 | 0x5418105 | `0x5418105  mov rax,[rsi+0xE0]` | R: 8-byte vector cap-end [this+0xE0] |
| group+0x1A4 | 4 | 0x541815a | `0x541815a  movss xmm0,[rsi+0x1A4]` | R: float [this+0x1A4] |
| group+0x1A8 | 4 | 0x5418166 | `0x5418166  movss xmm0,[rsi+0x1A8]` | R: float [this+0x1A8] |
| group+0x1BE | 1 | 0x541817b | `0x541817b  cmp byte ptr [rsi+0x1BE],1` | R: flag byte [this+0x1BE] |
| group+0xE8 | 8 | 0x54181cf | `0x54181cf  sub rdx,[rsi+0xE8]` | R: 2-byte vector begin [this+0xE8] |
| group+0xF0 | 8 | 0x5418222 | `0x5418222  add qword ptr [rsi+0xF0],2` | W: 2-byte vector end [this+0xF0] advanced by 2 |
| group+0xF8 | 8 | 0x54181c5 | `0x54181c5  mov rax,[rsi+0xF8]` | R: 2-byte vector cap-end [this+0xF8] |
| group+0x1BC | 2 | 0x5418218 | `0x5418218  movzx eax,word ptr [rsi+0x1BC]` | R: word value [this+0x1BC] |
| group+0x1C4 | 1 | 0x541822a | `0x541822a  cmp byte ptr [rsi+0x1C4],1` | R: flag byte [this+0x1C4] |
| group+0x100 | 8 | 0x541827e | `0x541827e  sub rdx,[rsi+0x100]` | R: 4-byte vector begin [this+0x100] |
| group+0x108 | 8 | 0x54182d1 | `0x54182d1  add qword ptr [rsi+0x108],4` | W: 4-byte vector end [this+0x108] advanced by 4 |
| group+0x110 | 8 | 0x5418274 | `0x5418274  mov rax,[rsi+0x110]` | R: 4-byte vector cap-end [this+0x110] |
| group+0x1C0 | 4 | 0x54182c9 | `0x54182c9  mov eax,[rsi+0x1C0]` | R: dword value [this+0x1C0] |
| group+0x1C9 | 1 | 0x54182d9 | `0x54182d9  cmp byte ptr [rsi+0x1C9],1` | R: flag byte [this+0x1C9] |
| group+0x118 | 8 | 0x541832d | `0x541832d  sub rdx,[rsi+0x118]` | R: 1-byte vector begin [this+0x118] |
| group+0x120 | 8 | 0x541837c | `0x541837c  inc qword ptr [rsi+0x120]` | W: 1-byte vector end [this+0x120] incremented |
| group+0x128 | 8 | 0x5418323 | `0x5418323  mov rax,[rsi+0x128]` | R: 1-byte vector cap-end [this+0x128] |
| group+0x1C8 | 1 | 0x5418373 | `0x5418373  movzx eax,byte ptr [rsi+0x1C8]` | R: byte value [this+0x1C8] |
| group+0x2A1 | 1 | 0x5418383 | `0x5418383  cmp byte ptr [rsi+0x2A1],1` | R: batch flag byte [this+0x2A1] |
| group+0x08 | 4 | 0x54183ba | `0x54183ba  mov ecx,[rsi+8]` | R: mode [this+8] |
| group+0x200 | 8 | 0x54183e1 | `0x54183e1  movlps [rsi+0x200],xmm7` | W: batch position accumulator [this+0x200] (8 bytes) |
| group+0x208 | 4 | 0x54183f0 | `0x54183f0  movss [rsi+0x208],xmm6` | W: batch Z accumulator [this+0x208] (4 bytes) |
| group+0x20C | 4 | 0x5418411 | `0x5418411  mov dword ptr [rsi+0x20C],0` | W: batch counter [this+0x20C] reset to 0 |
| group+0x1E4 | 1 | 0x541841b | `0x541841b  movzx r13d,byte ptr [rsi+0x1E4]` | R: flag byte [this+0x1E4] (written word 6 at 0x5418641) |
| group+0x1E5 | 1 | 0x5418423 | `0x5418423  movzx ebp,byte ptr [rsi+0x1E5]` | R: flag byte [this+0x1E5] |
| group+0x1E8 | 8 | 0x541860d | `0x541860d  mov [rsi+0x1E8],r15` | W: record vector begin [this+0x1E8] |
| group+0x1F0 | 8 | 0x541861b | `0x541861b  mov [rsi+0x1F0],r12` | W: record vector end [this+0x1F0] |
| group+0x1F8 | 8 | 0x5418625 | `0x5418625  mov [rsi+0x1F8],rdi` | W: record vector cap-end [this+0x1F8] |








## ADDENDUM (orchestrator): 1 instruction missing from the phases above, verbatim from texgroup_5417950_54186e0.txt
```
0x541799f  cmp byte ptr [rcx+0x210],1
```
