## NEXT
DONE

# Unit U-EL1q — Record table field layouts (checklist L1q pending part)

Goal (from checklist L1q): decode the field layouts of the 0x78/0x80/0x130/0x68 record tables. Texture table 0xB8 [V], shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 already done per 6au — those are not part of this unit.

Part done here (the pending/not-decoded part): field layouts of
- index-buffer records: 0x78 bytes at renderer+0x93A178 (createIndexBuffer 0xe8124c0 + shared init sub_e812740)
- vertex-buffer records: 0x80 bytes at renderer+0x9B2178 (createVertexBuffer 0xe812be0 + sub_e812740)
- framebuffer-texture records: 0x130 bytes, record pointers at renderer+0xA32178 guard slots stride 0x78 (createFrameBuffer 0xe816380)
- framebuffer-window records: 0x68 bytes at renderer+0xC97698, 128 entries (createFrameBuffer 0xe817880 / slot-40 0xe8176a0 / destroy 0xe817c00)

Renderer object = `this` of the D3D12 context slots (live object vtable 0xF4EEE80; `*(base+0x12BB4910)` = 0x49c84010000, [6b/6z]). All RVAs image-relative. All instruction quotes verbatim from `rdis.exe <exe> dis 0x<rva> 800`. Guard/allocator metadata written by the creates (renderer+0x3C549F8, +0x19F58 page tables) is L1r scope and excluded from these record layouts.

Meaning column: '-' unless an instruction/string shows the meaning, else '-'. Tags [V] = offset/size/site seen in disassembly (RVA cited); meanings marked [-] are not shown by any instruction.

## 1. Record-table bases and strides

Index-buffer table 0x78-stride at renderer+0x93A178 [V]: `0xe8124f4` imul rax,rsi,0x78; `0xe8124fc` add rax,rcx; `0xe8124ff` add rax,0x93A178 → record ptr saved at `0xe812505` mov [rbp-0x38],rax and passed to sub_e812740 at `0xe812556` mov rcx,[rbp-0x38] / `0xe812563` call 0xE812740. Destroy confirms base: `0xe812b90` movzx eax,dx / `0xe812b93` imul rax,0x78 / `0xe812b97` add rcx,rax / `0xe812b9a` add rcx,0x93A178 / `0xe812ba1` jmp 0xE80EF60.

Vertex-buffer table 0x80-stride at renderer+0x9B2178 [V]: `0xe812c12` shl eax,7; `0xe812c15` lea r12,[rcx+rax]; `0xe812c19` add r12,0x9B2178 → record ptr r12 passed to sub_e812740 at `0xe812c70` mov rcx,r12 / `0xe812c7c` call 0xE812740; plus direct store `0xe812c89` mov [r12+0x78],ax. Destroy confirms base: `0xe812e80` movzx eax,dx / `0xe812e83` shl eax,7 / `0xe812e86` add rcx,rax / `0xe812e89` add rcx,0x9B2178 / `0xe812e90` jmp 0xE80EF60.

Framebuffer-texture table at renderer+0xA32178 [V]: guard-slot existence check `0xe816396` imul rbp,rcx,0x78 / `0xe81639a` cmp qword ptr [rdi+rbp+0xA32178],0 (guard slot stride 0x78 holds the record pointer qword); records are 0x130-byte allocations from `0xe8164bb` call 0xE8360F0; record pointer read back from guard slot `0xe816517` add rdi,rbp / `0xe81651a` add rdi,0xA32178 / `0xe816534` mov rdx,[rdi]. Pointer-array base read `0xe816403` mov rax,[rax+0x22498] / `0xe81640a` mov rax,[rax+rbp]. Destroy confirms base: `0xe816580` movzx eax,dx / `0xe816583` imul rax,0x78 / `0xe816587` add rcx,rax / `0xe81658a` add rcx,0xA32178 / `0xe816591` jmp 0xE80EF60. Store of the new record pointer into the guard slot is inside sub_e8360f0, not shown in this listing [-].

Framebuffer-window table 0x68-stride at renderer+0xC97698, 128 entries [V]: `0xe8176b1` imul r14,rsi,0x68 / `0xe8176b5` lea rbx,[rcx+r14] / `0xe8176b9` add rbx,0xC97698 → record ptr; cleanup loop stride `0xe817934` add r15,0x68, bound `0xe817938` cmp r15,0x3400 → 0x3400/0x68 = 128 entries. Base `lea r14,[rdi+0xC97698]` at `0xe8178f0`. Destroy confirms base: `0xe817c0d` imul rax,0x68 / `0xe817c11` lea rbx,[rcx+rax] / `0xe817c15` add rbx,0xC97698 / `0xe817c1c` cmp qword ptr [rcx+rax+0xC976B0],0.

All field stores below target record-relative offsets inside these tables (rsi/r12/rbx/rcx = record pointer). Sites inside sub_e812740 apply to BOTH the index-buffer and vertex-buffer records (shared init).

## 2. Index-buffer record fields (0x78 bytes, renderer+0x93A178+handle*0x78)

All stores via sub_e812740 (0xe812740), called from createIndexBuffer 0xe8124c0 at `0xe812563` call 0xE812740. Bytes +0x74..+0x77 (record tail) not written by create.

Verbatim proof lines:
0xe812851  mov [rsi],rcx
0xe812865  mov [rsi+8],r15d
0xe8128bf  mov [rsi+0xC],eax
0xe812869  mov dword ptr [rsi+0x10],0x1688
0xe8128c2  mov [rsi+0x18],r9
0xe812885  mov [rsi+0x20],eax
0xe812888  mov [rsi+0x24],edi
0xe81288b  mov dword ptr [rsi+0x28],0
0xe812892  mov [rsi+0x30],r15d
0xe812896  mov dword ptr [rsi+0x34],1
0xe81289d  mov qword ptr [rsi+0x38],0
0xe8128a5  mov [rsi+0x40],eax
0xe8128a8  mov [rsi+0x44],edi
0xe8128ab  mov qword ptr [rsi+0x48],0
0xe8128b3  mov dword ptr [rsi+0x50],0
0xe81285c  mov [rsi+0x58],r9
0xe81277b  mov [rsi+0x60],r9d
0xe81277f  mov [rsi+0x64],r13w
0xe81278e  sete [rsi+0x66]
0xe812807  mov [rsi+0x70],r10d

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| index-buffer record +0x00 | +0x00 | 8 | sub_e812740 record init | `0xe812851  mov [rsi],rcx` | qword: sub_e815590 result stored first (role not shown by instruction) | [V] |
| index-buffer record +0x08 | +0x08 | 4 | sub_e812740 | `0xe812865  mov [rsi+8],r15d` | dword: r15d (default 3; class patched from flags at 0xe8127ba-0xe8127ae) | [V] |
| index-buffer record +0x0C | +0x0C | 4 | sub_e812740 | `0xe8128bf  mov [rsi+0xC],eax` | dword: 1 on dynamic path (cmp ebp,4 at 0xe812878); unwritten otherwise | [V] |
| index-buffer record +0x10 | +0x10 | 4 | sub_e812740 | `0xe812869  mov dword ptr [rsi+0x10],0x1688` | constant 0x1688 | [V] |
| index-buffer record +0x18 | +0x18 | 8 | sub_e812740 | `0xe8128c2  mov [rsi+0x18],r9` | qword: r9 (sub_e815590 output) | [V] |
| index-buffer record +0x20 | +0x20 | 4 | sub_e812740 | `0xe812885  mov [rsi+0x20],eax` | dword: element count (quotient of div at 0xe812882, [rsi+0x60]/[rsi+0x70]) | [V] |
| index-buffer record +0x24 | +0x24 | 4 | sub_e812740 | `0xe812888  mov [rsi+0x24],edi` | dword 0 | [V] |
| index-buffer record +0x28 | +0x28 | 4 | sub_e812740 | `0xe81288b  mov dword ptr [rsi+0x28],0` | dword 0 | [V] |
| index-buffer record +0x30 | +0x30 | 4 | sub_e812740 | `0xe812892  mov [rsi+0x30],r15d` | dword: r15d (stride/format class) | [V] |
| index-buffer record +0x34 | +0x34 | 4 | sub_e812740 | `0xe812896  mov dword ptr [rsi+0x34],1` | dword 1 | [V] |
| index-buffer record +0x38 | +0x38 | 8 | sub_e812740 | `0xe81289d  mov qword ptr [rsi+0x38],0` | qword 0 | [V] |
| index-buffer record +0x40 | +0x40 | 4 | sub_e812740 | `0xe8128a5  mov [rsi+0x40],eax` | dword: same quotient as +0x20 | [V] |
| index-buffer record +0x44 | +0x44 | 4 | sub_e812740 | `0xe8128a8  mov [rsi+0x44],edi` | dword 0 | [V] |
| index-buffer record +0x48 | +0x48 | 8 | sub_e812740 | `0xe8128ab  mov qword ptr [rsi+0x48],0` | qword 0 | [V] |
| index-buffer record +0x50 | +0x50 | 4 | sub_e812740 | `0xe8128b3  mov dword ptr [rsi+0x50],0` | dword 0 | [V] |
| index-buffer record +0x58 | +0x58 | 8 | sub_e812740 | `0xe81285c  mov [rsi+0x58],r9` | qword: same r9 source as +0x18 | [V] |
| index-buffer record +0x60 | +0x60 | 4 | sub_e812740 | `0xe81277b  mov [rsi+0x60],r9d` | dword: create-call r9d (flags argument) | [V] |
| index-buffer record +0x64 | +0x64 | 2 | sub_e812740 | `0xe81277f  mov [rsi+0x64],r13w` | u16: stack-passed parameter r13w | [V] |
| index-buffer record +0x66 | +0x66 | 1 | sub_e812740 | `0xe81278e  sete [rsi+0x66]` | byte: sete (data-pointer != 0 test shown; role not shown) | [V] |
| index-buffer record +0x70 | +0x70 | 4 | sub_e812740 | `0xe812807  mov [rsi+0x70],r10d` | dword: r10d (stride/format class) | [V] |

## 3. Vertex-buffer record fields (0x80 bytes, renderer+0x9B2178+handle*0x80)

Stores +0x00..+0x70 via sub_e812740 (0xe812740), called from createVertexBuffer 0xe812be0 at `0xe812c7c` call 0xE812740 (rcx = record ptr r12, base proven at `0xe812c12` shl eax,7 / `0xe812c15` lea r12,[rcx+rax] / `0xe812c19` add r12,0x9B2178). Plus the direct create-own store at +0x78.

Verbatim proof lines (shared with index buffer via sub_e812740):
0xe812851  mov [rsi],rcx
0xe812865  mov [rsi+8],r15d
0xe8128bf  mov [rsi+0xC],eax
0xe812869  mov dword ptr [rsi+0x10],0x1688
0xe8128c2  mov [rsi+0x18],r9
0xe812885  mov [rsi+0x20],eax
0xe812888  mov [rsi+0x24],edi
0xe81288b  mov dword ptr [rsi+0x28],0
0xe812892  mov [rsi+0x30],r15d
0xe812896  mov dword ptr [rsi+0x34],1
0xe81289d  mov qword ptr [rsi+0x38],0
0xe8128a5  mov [rsi+0x40],eax
0xe8128a8  mov [rsi+0x44],edi
0xe8128ab  mov qword ptr [rsi+0x48],0
0xe8128b3  mov dword ptr [rsi+0x50],0
0xe81285c  mov [rsi+0x58],r9
0xe81277b  mov [rsi+0x60],r9d
0xe81277f  mov [rsi+0x64],r13w
0xe81278e  sete [rsi+0x66]
0xe812807  mov [rsi+0x70],r10d
0xe812c89  mov [r12+0x78],ax

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| vertex-buffer record +0x00 | +0x00 | 8 | sub_e812740 (called by createVertexBuffer 0xe812be0) | `0xe812851  mov [rsi],rcx` | qword: sub_e815590 result stored first (role not shown by instruction) | [V] |
| vertex-buffer record +0x08 | +0x08 | 4 | sub_e812740 | `0xe812865  mov [rsi+8],r15d` | dword: r15d (default 3) | [V] |
| vertex-buffer record +0x0C | +0x0C | 4 | sub_e812740 | `0xe8128bf  mov [rsi+0xC],eax` | dword: 1 on dynamic path; unwritten otherwise | [V] |
| vertex-buffer record +0x10 | +0x10 | 4 | sub_e812740 | `0xe812869  mov dword ptr [rsi+0x10],0x1688` | constant 0x1688 | [V] |
| vertex-buffer record +0x18 | +0x18 | 8 | sub_e812740 | `0xe8128c2  mov [rsi+0x18],r9` | qword: r9 (sub_e815590 output) | [V] |
| vertex-buffer record +0x20 | +0x20 | 4 | sub_e812740 | `0xe812885  mov [rsi+0x20],eax` | dword: element count (quotient of div at 0xe812882) | [V] |
| vertex-buffer record +0x24 | +0x24 | 4 | sub_e812740 | `0xe812888  mov [rsi+0x24],edi` | dword 0 | [V] |
| vertex-buffer record +0x28 | +0x28 | 4 | sub_e812740 | `0xe81288b  mov dword ptr [rsi+0x28],0` | dword 0 | [V] |
| vertex-buffer record +0x30 | +0x30 | 4 | sub_e812740 | `0xe812892  mov [rsi+0x30],r15d` | dword: r15d | [V] |
| vertex-buffer record +0x34 | +0x34 | 4 | sub_e812740 | `0xe812896  mov dword ptr [rsi+0x34],1` | dword 1 | [V] |
| vertex-buffer record +0x38 | +0x38 | 8 | sub_e812740 | `0xe81289d  mov qword ptr [rsi+0x38],0` | qword 0 | [V] |
| vertex-buffer record +0x40 | +0x40 | 4 | sub_e812740 | `0xe8128a5  mov [rsi+0x40],eax` | dword: same quotient as +0x20 | [V] |
| vertex-buffer record +0x44 | +0x44 | 4 | sub_e812740 | `0xe8128a8  mov [rsi+0x44],edi` | dword 0 | [V] |
| vertex-buffer record +0x48 | +0x48 | 8 | sub_e812740 | `0xe8128ab  mov qword ptr [rsi+0x48],0` | qword 0 | [V] |
| vertex-buffer record +0x50 | +0x50 | 4 | sub_e812740 | `0xe8128b3  mov dword ptr [rsi+0x50],0` | dword 0 | [V] |
| vertex-buffer record +0x58 | +0x58 | 8 | sub_e812740 | `0xe81285c  mov [rsi+0x58],r9` | qword: same r9 source as +0x18 | [V] |
| vertex-buffer record +0x60 | +0x60 | 4 | sub_e812740 | `0xe81277b  mov [rsi+0x60],r9d` | dword: create-call r9d (flags argument) | [V] |
| vertex-buffer record +0x64 | +0x64 | 2 | sub_e812740 | `0xe81277f  mov [rsi+0x64],r13w` | u16: stack-passed parameter r13w | [V] |
| vertex-buffer record +0x66 | +0x66 | 1 | sub_e812740 | `0xe81278e  sete [rsi+0x66]` | byte: sete (data-pointer != 0 test shown; role not shown) | [V] |
| vertex-buffer record +0x70 | +0x70 | 4 | sub_e812740 | `0xe812807  mov [rsi+0x70],r10d` | dword: r10d | [V] |
| vertex-buffer record +0x78 | +0x78 | 2 | createVertexBuffer 0xe812be0 (direct store, not in sub) | `0xe812c89  mov [r12+0x78],ax` | u16: entry r9w (create's 4th argument) | [V] |

## 4. Framebuffer-texture record fields (0x130 bytes, record pointer held at renderer+0xA32178+handle*0x78)

Record allocated by sub_e8360f0 at `0xe8164bb` call 0xE8360F0 (called from createFrameBuffer 0xe816380); attachment descriptors copied at `0xe81652f` call 0xEEC6EC0 with dst=r12 (record), src=[r9] (attachment array, `0xe81648f` mov r14,[r9]), size=[r9+8] (`0xe816492` mov ebx,[r9+8]). Guard-slot record-ptr read: `0xe816534` mov rdx,[rdi]. Every other byte +0x01..+0x12F is NOT written by createFrameBuffer 0xe816380 [-].

Verbatim proof lines:
0xe8164bb  call 0xE8360F0
0xe81652f  call 0xEEC6EC0
0xe81648f  mov r14,[r9]
0xe816492  mov ebx,[r9+8]

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| framebuffer-texture record +0x00 | +0x00 | 6B/entry, N=[r9+8] bytes | createFrameBuffer 0xe816380 | `0xe81652f  call 0xEEC6EC0` | attachment-descriptor block memcpy'd into record+0x00 (6 bytes/entry: u16 handle + u32 flags, per stride-6 loop in 0xe8176a0) | [V] |

## 5. Framebuffer-window record fields (0x68 bytes, renderer+0xC97698+handle*0x68, 128 entries)

Stores from createFrameBuffer 0xe817880 and slot-40 variant 0xe8176a0, plus destroyFrameBuffer window 0xe817c00 clears. Bytes +0x00, +0x08 and the tail not written by located functions [-].

Verbatim proof lines:
0xe8176c0  mov word ptr [rcx+r14+0xC976C8],0xFFFF
0xe8176cb  mov [rcx+r14+0xC976CB],r8b
0xe817b1d  mov [rcx+0x20],rbx
0xe817900  mov qword ptr [rdi+r15+0xC976B8],0
0xe817c7d  mov qword ptr [rbx+0x20],0
0xe817b26  mov [rcx+0x30],ax
0xe817929  mov word ptr [rdi+r15+0xC976C8],0xFFFF
0xe817c97  mov word ptr [rbx+0x30],0xFFFF
0xe817c93  movzx eax,word ptr [rbx+0x30]
0xe817b2a  mov byte ptr [rcx+0x32],1
0xe817731  movzx eax,byte ptr [rbx+r14+0x33]
0xe817779  movzx eax,byte ptr [rbx+0x33]
0xe817b72  movzx eax,byte ptr [rbx+rcx+0x33]
0xe817915  mov byte ptr [rdi+r15+0xC976FC],0
0xe817c85  mov byte ptr [rbx+0x33],0
0xe817c89  mov byte ptr [rbx+0x64],0
0xe817c8d  mov word ptr [rbx+0x10],0xFFFF
0xe8176ea  call 0xEBCE390
0xe817756  add r14,6
0xe81775f  movzx r8d,word ptr [r14]
0xe81775a  cmp r15,rcx
0xe817b9a  cmp r15,rcx
0xe817c75  mov qword ptr [rbx+0x18],0
0xe8179e4  lea r9,[r14+r12]

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|------|--------|------|------|-------------------------|---------|-----|
| framebuffer-window record +0x10 | +0x10 | 2 | create 0xe817880 (`0xe81791e`); destroy 0xe817c00 (`0xe817c8d`) | `0xe81791e  mov word ptr [rdi+r15+0xC976A8],0xFFFF` / `0xe817c8d  mov word ptr [rbx+0x10],0xFFFF` | u16 handle, 0xFFFF = invalid | [V] |
| framebuffer-window record +0x18 | +0x18 | 8 | destroy 0xe817c00 | `0xe817c75  mov qword ptr [rbx+0x18],0` | qword window/swapchain member (record+0x18 passed to sub_e9241b0; cleared on destroy) | [V] |
| framebuffer-window record +0x20 | +0x20 | 8 | create 0xe817880 (`0xe817b1d`); clears `0xe817900`, `0xe817c7d` | `0xe817b1d  mov [rcx+0x20],rbx` / `0xe817c7d  mov qword ptr [rbx+0x20],0` | qword: IDXGISwapChain* (CreateSwapChain-like result rbx stored at 0xe817b1d via sub_e9241b0 at `0xe8179ff` call 0xE9241B0) | [V] |
| framebuffer-window record +0x30 | +0x30 | 2 | create 0xe817880 (`0xe817b26`); clears `0xe817929`, `0xe8176c0`, `0xe817c97`; read `0xe817c93` | `0xe817b26  mov [rcx+0x30],ax` / `0xe817c97  mov word ptr [rbx+0x30],0xFFFF` / `0xe817c93  movzx eax,word ptr [rbx+0x30]` | u16 window index (= handle value at create) | [V] |
| framebuffer-window record +0x32 | +0x32 | 1 | create 0xe817880 | `0xe817b2a  mov byte ptr [rcx+0x32],1` | u8: valid flag = 1 | [V] |
| framebuffer-window record +0x33 | +0x33 | 1 | create slot-40 `0xe8176cb`; clears `0xe81790c`, `0xe817c85`; reads `0xe817731`, `0xe817779`, `0xe817b72` | `0xe8176cb  mov [rcx+r14+0xC976CB],r8b` / `0xe817b72  movzx eax,byte ptr [rbx+rcx+0x33]` | u8 attachment count — loop bound (compare per iteration `0xe81775a` cmp r15,rcx / `0xe817b9a` cmp r15,rcx) | [V] |
| framebuffer-window record +0x34 | +0x34 | 6B/entry, N from +0x33 | create slot-40 `0xe8176ea` (memcpy count*6); reads `0xe81775f` | `0xe8176ea  call 0xEBCE390` / `0xe81775f  movzx r8d,word ptr [r14]` with `0xe817756` add r14,6 | attachment descriptors: u16 handle + u32 flags, 6 bytes each, count N from +0x33 | [V] |
| framebuffer-window record +0x64 | +0x64 | 1 | clears `0xe817915`, `0xe817c89` | `0xe817915  mov byte ptr [rdi+r15+0xC976FC],0` / `0xe817c89  mov byte ptr [rbx+0x64],0` | u8 dirty/present flag cleared to 0 | [V] |

## CLOSES?

NO — blocking fact: the 0x130 framebuffer-texture record layout is not fully proven. The only record-field store in createFrameBuffer 0xe816380 is the attachment-descriptor block memcpy at proof line 0xe81652f; fields +0x01..+0x12F (RTV/SRV handles, dimensions, format, sample count, ...) have no [V] row in any located function. The 0x78 index-buffer layout, the 0x80 vertex-buffer layout, and the 0x68 framebuffer-window layout are fully [V]-proven above (every written field has a verbatim instruction site; unwritten bytes marked '-').

## TOOL REQUESTS

None — all data from rdis `dis` of createIndexBuffer 0xe8124c0, createVertexBuffer 0xe812be0, sub_e812740 0xe812740, createFrameBuffer 0xe816380, createFrameBuffer window 0xe817880, slot-40 0xe8176a0, destroy 0xe817c00; `xref.py callers 0xe816380` returned no callers (vtable-dispatched).
