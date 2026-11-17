## NEXT
DONE

# Unit U-Lr1 — ClientInstance::loadResources 0x186e6a0..0x186eb2f (chunk 1 of 6)

All instruction text below is copied verbatim from docs/progress/_part_Lr1.txt (the precomputed listing of the slice). Every one of the 250 instructions in the slice is quoted as a `0xRVA  instr` line inside its phase; phases are at most 40 instructions and partition the whole slice. After the phases, the field map lists every [reg+off] offset (one row per distinct offset, size-split where mixed), with all sites listed. Meaning is `-` everywhere: no instruction or string in this slice names any field. Absolute memory operands ([0x128D3D68], [0x128D3D70], [0x128D3D80] and the [0]=0xDEADC0DE null-deref stores) are not [reg+off] fields, so they are not table rows; they appear in the phase text.

## Phases

### Phase 1 — 0x186e6a0..0x186e741 (instructions 1..38 of 250)
Prologue and object setup: eight callee-saved registers are pushed, rsp is lowered by 0x6B8, rbp is framed at rsp+0x80, and -2 is stored at [rbp+0x630]; with rcx=this and rdx=arg copied into rbx/rsi, vtable 0xEFCC480 is written into [rbx], 0x18 bytes are allocated through [0xF99FFA0] (branching to 0x187018C if NULL), the 0x18-byte object is initialized (0x100000001 at +8, vtable 0xEFCC490 at +0, byte 1 at +0x10), it is linked through [rbx+8] and [rbx+0x10], vtable 0xF0FBDD0 is stored to [rbx], [rbx+0x18] is zeroed, [rsi] is loaded and the code jumps to 0x186E7EB when nonzero.
0x186e6a0  push rbp
0x186e6a1  push r15
0x186e6a3  push r14
0x186e6a5  push r13
0x186e6a7  push r12
0x186e6a9  push rsi
0x186e6aa  push rdi
0x186e6ab  push rbx
0x186e6ac  sub rsp,0x6B8
0x186e6b3  lea rbp,[rsp+0x80]
0x186e6bb  mov qword ptr [rbp+0x630],0xFFFFFFFFFFFFFFFE
0x186e6c6  mov rsi,rdx
0x186e6c9  mov rbx,rcx
0x186e6cc  lea rax,[0xEFCC480]
0x186e6d3  mov [rcx],rax
0x186e6d6  mov rcx,[0x1233E1A8]
0x186e6dd  mov rax,[rcx]
0x186e6e0  mov rax,[rax+8]
0x186e6e4  mov edx,0x18
0x186e6e9  call qword ptr [0xF99FFA0]
0x186e6ef  test rax,rax
0x186e6f2  je 0x187018C
0x186e6f8  mov rcx,0x100000001
0x186e702  mov [rax+8],rcx
0x186e706  lea rcx,[0xEFCC490]
0x186e70d  mov [rax],rcx
0x186e710  mov rcx,rax
0x186e713  add rcx,0x10
0x186e717  mov byte ptr [rax+0x10],1
0x186e71b  mov [rbx+8],rcx
0x186e71f  mov [rbx+0x10],rax
0x186e723  lea rax,[0xF0FBDD0]
0x186e72a  mov [rbx],rax
0x186e72d  mov dword ptr [rbx+0x18],0
0x186e734  mov rax,[rsi]
0x186e737  test rax,rax
0x186e73a  mov [rbp+0x628],rbx
0x186e741  jne 0x186E7EB

### Phase 2 — 0x186e747..0x186e7eb (instructions 39..70 of 250)
Global pointer patch: if [0x128D3D68] is NULL the code allocates 0x70 bytes, builds a stack descriptor ([rbp+0x5F0] = string 0xF6027EE, [rbp+0x5F8] = 0xB) and calls 0x7709C0 with r8w=0x3C to format into the new buffer, then publishes rax at [0x128D3D68] and decrements the old value's refcount via [0xF99FFA0] with edx=1; rax is reloaded from [rbp+0x620], [0x128D3D68] is updated, the old pointer is released, rbx is restored from [rbp+0x628] and the global value is stored at [rbx+0x20].
0x186e747  mov rax,[0x128D3D68]
0x186e74e  test rax,rax
0x186e751  jne 0x186E7EB
0x186e757  mov rcx,[0x1233E1A8]
0x186e75e  mov rax,[rcx]
0x186e761  mov rax,[rax+8]
0x186e765  mov edx,0x70
0x186e76a  call qword ptr [0xF99FFA0]
0x186e770  nop
0x186e771  mov rdi,rax
0x186e774  test rax,rax
0x186e777  je 0x1870321
0x186e77d  lea rax,[0xF6027EE]
0x186e784  mov [rbp+0x5F0],rax
0x186e78b  mov qword ptr [rbp+0x5F8],0xB
0x186e796  lea rdx,[rbp+0x5F0]
0x186e79d  mov rcx,rdi
0x186e7a0  mov r8w,0x3C
0x186e7a5  mov [rbp+0x620],rdi
0x186e7ac  call 0x7709C0
0x186e7b1  nop
0x186e7b2  mov rcx,[0x128D3D68]
0x186e7b9  mov rax,[rbp+0x620]
0x186e7c0  mov [0x128D3D68],rax
0x186e7c7  test rcx,rcx
0x186e7ca  mov rbx,[rbp+0x628]
0x186e7d1  je short 0x186E7EB
0x186e7d3  mov rax,[rcx]
0x186e7d6  mov rax,[rax]
0x186e7d9  mov edx,1
0x186e7de  call qword ptr [0xF99FFA0]
0x186e7e4  mov rax,[0x128D3D68]
0x186e7eb  mov [rbx+0x20],rax

### Phase 3 — 0x186e7e4..0x186e893 (instructions 71..107 of 250)
Second field store: [rbx+0x20] receives the global, then [rsi+8] is loaded — when NULL the code falls back to global [0x128D3D70], taking the intentional null-deref paths (mov dword ptr [0],0xDEADC0DE at 0x186e80d and at 0x186e943) when the pointer is empty, otherwise using it directly — and the result is stored at [rbx+0x28]; [rbx+0x30..0x3F] are zeroed with movups, 0x30 bytes are allocated (fail → 0x18701A1), the block is initialized as an empty circular list ([rdi], [rdi+8] and [rdi+0x10] self-point to rdi, word 0x101 at [rdi+0x18]), linked at [r15+0x30], [r15+0x40] is cleared, byte [r15+0x48] is set to 1, r13 is set to r15+0x50 as the string cursor, and byte [rsi+0x20] is tested.
0x186e7ef  mov rax,[rsi+8]
0x186e7f3  test rax,rax
0x186e7f6  jne short 0x186E81F
0x186e7f8  mov rax,[0x128D3D70]
0x186e7ff  test rax,rax
0x186e802  je 0x186E943
0x186e808  cmp byte ptr [rax],0
0x186e80b  jne short 0x186E818
0x186e80d  mov dword ptr [0],0xDEADC0DE
0x186e818  mov rax,[0x128D3D80]
0x186e81f  mov [rbx+0x28],rax
0x186e823  xorps xmm0,xmm0
0x186e826  movups [rbx+0x30],xmm0
0x186e82a  mov rcx,[0x1233E1A8]
0x186e831  mov rax,[rcx]
0x186e834  mov rax,[rax+8]
0x186e838  mov edx,0x30
0x186e83d  call qword ptr [0xF99FFA0]
0x186e843  nop
0x186e844  mov rdi,rax
0x186e847  test rax,rax
0x186e84a  je 0x18701A1
0x186e850  mov r15,[rbp+0x628]
0x186e857  lea rax,[r15+0x30]
0x186e85b  mov [rdi],rdi
0x186e85e  mov [rdi+8],rdi
0x186e862  mov [rdi+0x10],rdi
0x186e866  mov word ptr [rdi+0x18],0x101
0x186e86c  mov [r15+0x30],rdi
0x186e870  mov qword ptr [r15+0x40],0
0x186e878  mov byte ptr [r15+0x48],1
0x186e87d  lea r13,[r15+0x50]
0x186e881  cmp byte ptr [rsi+0x20],0
0x186e885  mov [rbp+0x1E0],rax
0x186e88c  mov [rbp+0x1E8],r13
0x186e893  je short 0x186E8C7

### Phase 4 — 0x186e895..0x186e915 (instructions 108..137 of 250)
String sizing/copy setup: when byte [rsi+0x20] is nonzero, rbx=[rsi+0x10] and rdi=[rsi+0x18] (string and size), [r13] and [r13+0x10] are zeroed, a negative size jumps to 0x1870350, sizes below 0x10 use the inline 16-byte buffer (r14=r13, r12d=0xF), and larger sizes compute size|0xF, clamp to a minimum of 0x16 and allocate through the page-aware path (cmp rdx,0xFFF); when [rsi+0x20] is zero, the buffer is zeroed, rbx becomes default string 0xF847A07, rdi=0 and r14=r13.
0x186e895  mov rbx,[rsi+0x10]
0x186e899  mov rdi,[rsi+0x18]
0x186e89d  xorps xmm0,xmm0
0x186e8a0  movups [r13+0x10],xmm0
0x186e8a5  movups [r13],xmm0
0x186e8aa  test rdi,rdi
0x186e8ad  js 0x1870350
0x186e8b3  mov r12d,0xF
0x186e8b9  cmp rdi,0x10
0x186e8bd  jae short 0x186E8EB
0x186e8bf  mov r14,r13
0x186e8c2  jmp 0x186E982
0x186e8c7  xorps xmm0,xmm0
0x186e8ca  movups [r13+0x10],xmm0
0x186e8cf  movups [r13],xmm0
0x186e8d4  mov r12d,0xF
0x186e8da  lea rbx,[0xF847A07]
0x186e8e1  xor edi,edi
0x186e8e3  mov r14,r13
0x186e8e6  jmp 0x186E982
0x186e8eb  mov rdx,rdi
0x186e8ee  or rdx,0xF
0x186e8f2  cmp rdx,0x17
0x186e8f6  mov r12d,0x16
0x186e8fc  cmovae r12,rdx
0x186e900  mov rcx,[0x1233E1A8]
0x186e907  mov rax,[rcx]
0x186e90a  mov rax,[rax+8]
0x186e90e  cmp rdx,0xFFF
0x186e915  jb short 0x186E95C

### Phase 5 — 0x186e917..0x186e998 (instructions 138..169 of 250)
Buffer finalization: the final buffer is allocated (r12+0x28, 32-byte aligned when the request is >= 0x1000, otherwise r12+1; the original pointer is stored back at [r14-8]), NULL leads to 0x1870331/0x187033F with the DEADC0DE block at 0x186e943 between them; on success the buffer is stored at [r13], r15 is restored from [rbp+0x628], [r15+0x60] is set to rdi (size) and [r15+0x68] to r12 (capacity), then call 0xEEC6EC0 with rcx=buffer, rdx=string source and r8=count copies the bytes and the string is null-terminated at [r14+rdi]=0.
0x186e917  lea r15,[r12+0x28]
0x186e91c  mov rdx,r15
0x186e91f  call qword ptr [0xF99FFA0]
0x186e925  nop
0x186e926  mov r14,rax
0x186e929  test rax,rax
0x186e92c  je 0x1870331
0x186e932  mov rax,r14
0x186e935  add r14,0x27
0x186e939  and r14,0xFFFFFFFFFFFFFFE0
0x186e93d  mov [r14-8],rax
0x186e941  jmp short 0x186E977
0x186e943  mov dword ptr [0],0xDEADC0DE
0x186e94e  cmp byte ptr [rax],0
0x186e951  je 0x186E80D
0x186e957  jmp 0x186E818
0x186e95c  lea r15,[r12+1]
0x186e961  mov rdx,r15
0x186e964  call qword ptr [0xF99FFA0]
0x186e96a  nop
0x186e96b  mov r14,rax
0x186e96e  test rax,rax
0x186e971  je 0x187033F
0x186e977  mov [r13],r14
0x186e97b  mov r15,[rbp+0x628]
0x186e982  mov [r15+0x60],rdi
0x186e986  mov [r15+0x68],r12
0x186e98a  mov rcx,r14
0x186e98d  mov rdx,rbx
0x186e990  mov r8,rdi
0x186e993  call 0xEEC6EC0
0x186e998  mov byte ptr [r14+rdi],0

### Phase 6 — 0x186e99d..0x186ea38 (instructions 170..201 of 250)
Descriptor build: rdi=[r15+0x20] and rbx=[r15+0x28] are reloaded, 0x150 bytes are allocated via [0xF99FFA0] (fail → 0x18701B1) and saved at [rbp+0x620], [rbp+0x600] and [rbp+0x5F0] are zeroed with movaps, then 0x20 bytes are allocated (fail → 0x18701C1) into r14/[rbp+0x5F0], [rbp+0x600] receives qword 0x11 and [rbp+0x608] qword 0x1F, 16 bytes are copied from constant 0xF5B0748 into [r14], word 0x68 is written at [r14+0x10], r14 is rebased to &[rbp+0x5F0], and 0x772520 is called with rcx=[rbp+0x620], rdx=rbx, r8=rdi, r9=r14.
0x186e99d  mov rdi,[r15+0x20]
0x186e9a1  mov rbx,[r15+0x28]
0x186e9a5  mov rcx,[0x1233E1A8]
0x186e9ac  mov rax,[rcx]
0x186e9af  mov rax,[rax+8]
0x186e9b3  mov edx,0x150
0x186e9b8  call qword ptr [0xF99FFA0]
0x186e9be  nop
0x186e9bf  mov r14,rax
0x186e9c2  test rax,rax
0x186e9c5  je 0x18701B1
0x186e9cb  mov [rbp+0x620],r14
0x186e9d2  xorps xmm0,xmm0
0x186e9d5  movaps [rbp+0x600],xmm0
0x186e9dc  movaps [rbp+0x5F0],xmm0
0x186e9e3  mov rcx,[0x1233E1A8]
0x186e9ea  mov rax,[rcx]
0x186e9ed  mov rax,[rax+8]
0x186e9f1  mov edx,0x20
0x186e9f6  call qword ptr [0xF99FFA0]
0x186e9fc  nop
0x186e9fd  mov r14,rax
0x186ea00  test rax,rax
0x186ea03  je 0x18701C1
0x186ea09  mov [rbp+0x5F0],r14
0x186ea10  mov qword ptr [rbp+0x600],0x11
0x186ea1b  mov qword ptr [rbp+0x608],0x1F
0x186ea26  movups xmm0,[0xF5B0748]
0x186ea2d  movups [r14],xmm0
0x186ea31  mov word ptr [r14+0x10],0x68
0x186ea38  lea r14,[rbp+0x5F0]

### Phase 7 — 0x186ea3f..0x186eade (instructions 202..232 of 250)
Store and optional sizing: the call result [rbp+0x620] is stored at this+0x70 (rax=[rbp+0x628], [rax+0x70]=rcx); if byte [rsi+0x28]==1 then 8 bytes are allocated (fail → 0x18701D1) as a sized buffer, 0x500000013 is stored at [rsi], the end pointer rsi+8 is saved at [rbp+0x600], and [rbp+0x1F0] is cleared; finally a stack descriptor is built ([rbp-0x50]=string 0xF56B20B, [rbp-0x48]=length 0x18) and r14 is saved at [rsp+0x20].
0x186ea3f  mov rcx,[rbp+0x620]
0x186ea46  mov rdx,rbx
0x186ea49  mov r8,rdi
0x186ea4c  mov r9,r14
0x186ea4f  call 0x772520
0x186ea54  nop
0x186ea55  mov rax,[rbp+0x628]
0x186ea5c  mov rcx,[rbp+0x620]
0x186ea63  mov [rax+0x70],rcx
0x186ea67  cmp byte ptr [rsi+0x28],1
0x186ea6b  jne 0x1870178
0x186ea71  mov rcx,[0x1233E1A8]
0x186ea78  mov rax,[rcx]
0x186ea7b  mov rax,[rax+8]
0x186ea7f  mov edx,8
0x186ea84  call qword ptr [0xF99FFA0]
0x186ea8a  nop
0x186ea8b  mov rsi,rax
0x186ea8e  test rax,rax
0x186ea91  je 0x18701D1
0x186ea97  mov [rbp+0x5F0],rsi
0x186ea9e  mov rax,rsi
0x186eaa1  add rax,8
0x186eaa5  mov [rbp+0x600],rax
0x186eaac  mov rcx,0x500000013
0x186eab6  mov [rsi],rcx
0x186eab9  mov [rbp+0x5F8],rax
0x186eac0  mov qword ptr [rbp+0x1F0],0
0x186eacb  lea rax,[0xF56B20B]
0x186ead2  mov [rbp-0x50],rax
0x186ead6  mov qword ptr [rbp-0x48],0x18
0x186eade  mov [rsp+0x20],r14

### Phase 8 — 0x186eae3..0x186eb2f (instructions 233..250 of 250)
Teardown: call 0x1870DE0 with rcx=this ([rbp+0x628]), rdx=&stack descriptor, rsi=&[rbp+0x1F0], r8=&[rbp+0x1F0] and r9d=0x14; if [rbp+0x1F0] is nonzero, 0x2FE440 is called and then 0xE935700 with rcx=the pointer and edx=0x138, after which [rbp+0x1F0] is cleared with movaps and [rbp+0x200] is zeroed.
0x186eae3  lea rdx,[rbp-0x50]
0x186eae7  lea rsi,[rbp+0x1F0]
0x186eaee  mov rcx,[rbp+0x628]
0x186eaf5  mov r8,rsi
0x186eaf8  mov r9d,0x14
0x186eafe  call 0x1870DE0
0x186eb03  nop
0x186eb04  mov rdi,[rbp+0x1F0]
0x186eb0b  test rdi,rdi
0x186eb0e  je short 0x186EB25
0x186eb10  mov rcx,rdi
0x186eb13  call 0x2FE440
0x186eb18  mov edx,0x138
0x186eb1d  mov rcx,rdi
0x186eb20  call 0xE935700
0x186eb25  xorps xmm0,xmm0
0x186eb28  movaps [rbp+0x1F0],xmm0
0x186eb2f  mov qword ptr [rbp+0x200],0

## Field map

Every [reg+off] load/store in 0x186e6a0..0x186eb2f, one row per distinct offset (size-split where an offset is accessed with mixed instruction sizes), all sites listed with verbatim instruction text. Size is taken from the instruction (movups/movaps = 16, qword = 8, dword = 4, word = 2, byte = 1). Meaning is '-' everywhere: no instruction or string in this slice names any field.

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 0x0 (8B) | 8 | [rcx+0] [rax+0] [rbx+0] [r13+0] [rdi+0] [rsi+0] | 0x186e6d3  mov [rcx],rax; 0x186e70d  mov [rax],rcx; 0x186e72a  mov [rbx],rax; 0x186e734  mov rax,[rsi]; 0x186e7d3  mov rax,[rcx]; 0x186e7d6  mov rax,[rax]; 0x186e85b  mov [rdi],rdi; 0x186e977  mov [r13],r14; 0x186eab6  mov [rsi],rcx | - |
| 0x0 (16B) | 16 | [r13+0] [r14+0] | 0x186e8a5  movups [r13],xmm0; 0x186e8cf  movups [r13],xmm0; 0x186ea2d  movups [r14],xmm0 | - |
| 0x0 (1B) | 1 | [rax+0] [r14+rdi+0] | 0x186e808  cmp byte ptr [rax],0; 0x186e998  mov byte ptr [r14+rdi],0 | - |
| 8 | 8 | [rax+8] [rbx+8] [rsi+8] [rdi+8] | 0x186e702  mov [rax+8],rcx; 0x186e71b  mov [rbx+8],rcx; 0x186e7ef  mov rax,[rsi+8]; 0x186e85e  mov [rdi+8],rdi | - |
| 0x10 (1B) | 1 | [rax+0x10] | 0x186e717  mov byte ptr [rax+0x10],1 | - |
| 0x10 (8B) | 8 | [rbx+0x10] [rdi+0x10] [rsi+0x10] | 0x186e71f  mov [rbx+0x10],rax; 0x186e862  mov [rdi+0x10],rdi; 0x186e895  mov rbx,[rsi+0x10] | - |
| 0x10 (16B) | 16 | [r13+0x10] | 0x186e8a0  movups [r13+0x10],xmm0; 0x186e8ca  movups [r13+0x10],xmm0 | - |
| 0x10 (2B) | 2 | [r14+0x10] | 0x186ea31  mov word ptr [r14+0x10],0x68 | - |
| 0x18 (4B) | 4 | [rbx+0x18] | 0x186e72d  mov dword ptr [rbx+0x18],0 | - |
| 0x18 (2B) | 2 | [rdi+0x18] | 0x186e866  mov word ptr [rdi+0x18],0x101 | - |
| 0x18 (8B) | 8 | [rsi+0x18] | 0x186e899  mov rdi,[rsi+0x18] | - |
| 0x20 (1B) | 1 | [rsi+0x20] | 0x186e881  cmp byte ptr [rsi+0x20],0 | - |
| 0x20 (8B) | 8 | [rbx+0x20] [r15+0x20] [rsp+0x20] | 0x186e7eb  mov [rbx+0x20],rax; 0x186e99d  mov rdi,[r15+0x20]; 0x186eade  mov [rsp+0x20],r14 | - |
| 0x28 (8B) | 8 | [rbx+0x28] [r15+0x28] | 0x186e81f  mov [rbx+0x28],rax; 0x186e9a1  mov rbx,[r15+0x28] | - |
| 0x28 (1B) | 1 | [rsi+0x28] | 0x186ea67  cmp byte ptr [rsi+0x28],1 | - |
| 0x30 (16B) | 16 | [rbx+0x30] | 0x186e826  movups [rbx+0x30],xmm0 | - |
| 0x30 (8B) | 8 | [r15+0x30] | 0x186e86c  mov [r15+0x30],rdi | - |
| 0x40 | 8 | [r15+0x40] | 0x186e870  mov qword ptr [r15+0x40],0 | - |
| 0x48 | 1 | [r15+0x48] | 0x186e878  mov byte ptr [r15+0x48],1 | - |
| 0x60 | 8 | [r15+0x60] | 0x186e982  mov [r15+0x60],rdi | - |
| 0x68 | 8 | [r15+0x68] | 0x186e986  mov [r15+0x68],r12 | - |
| -8 | 8 | [r14-8] | 0x186e93d  mov [r14-8],rax | - |
| 0x1E0 | 8 | [rbp+0x1E0] | 0x186e885  mov [rbp+0x1E0],rax | - |
| 0x1E8 | 8 | [rbp+0x1E8] | 0x186e88c  mov [rbp+0x1E8],r13 | - |
| 0x5F0 (8B) | 8 | [rbp+0x5F0] | 0x186e784  mov [rbp+0x5F0],rax; 0x186ea09  mov [rbp+0x5F0],r14; 0x186ea97  mov [rbp+0x5F0],rsi | - |
| 0x5F0 (16B) | 16 | [rbp+0x5F0] | 0x186e9dc  movaps [rbp+0x5F0],xmm0 | - |
| 0x5F8 | 8 | [rbp+0x5F8] | 0x186e78b  mov qword ptr [rbp+0x5F8],0xB; 0x186eab9  mov [rbp+0x5F8],rax | - |
| 0x600 (8B) | 8 | [rbp+0x600] | 0x186ea10  mov qword ptr [rbp+0x600],0x11; 0x186eaa5  mov [rbp+0x600],rax | - |
| 0x600 (16B) | 16 | [rbp+0x600] | 0x186e9d5  movaps [rbp+0x600],xmm0 | - |
| 0x620 | 8 | [rbp+0x620] | 0x186e7a5  mov [rbp+0x620],rdi; 0x186e7b9  mov rax,[rbp+0x620]; 0x186e9cb  mov [rbp+0x620],r14; 0x186ea3f  mov rcx,[rbp+0x620]; 0x186ea5c  mov rcx,[rbp+0x620] | - |
| 0x628 | 8 | [rbp+0x628] | 0x186e73a  mov [rbp+0x628],rbx; 0x186e7ca  mov rbx,[rbp+0x628]; 0x186ea55  mov rax,[rbp+0x628]; 0x186eaee  mov rcx,[rbp+0x628] | - |
| 0x630 | 8 | [rbp+0x630] | 0x186e6bb  mov qword ptr [rbp+0x630],0xFFFFFFFFFFFFFFFE | - |
| 0x70 | 8 | [rax+0x70] | 0x186ea63  mov [rax+0x70],rcx | - |
| 0x1F0 (8B) | 8 | [rbp+0x1F0] | 0x186eac0  mov qword ptr [rbp+0x1F0],0; 0x186eb04  mov rdi,[rbp+0x1F0] | - |
| 0x1F0 (16B) | 16 | [rbp+0x1F0] | 0x186eb28  movaps [rbp+0x1F0],xmm0 | - |
| -0x50 | 8 | [rbp-0x50] | 0x186ead2  mov [rbp-0x50],rax | - |
| -0x48 | 8 | [rbp-0x48] | 0x186ead6  mov qword ptr [rbp-0x48],0x18 | - |
| 0x200 | 8 | [rbp+0x200] | 0x186eb2f  mov qword ptr [rbp+0x200],0 | - |

## TOOL REQUESTS
None.
