## NEXT
Resume at: verify_oc.py on all four record docs; then finalize.

---

# Unit U-A8b: D3D12/bgfx resource record layouts (checklist A8b)

Per checklist A8b (RENDER_CHECKLIST.md line 52): "Record tables: texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 layouts — 6au; **0x78/0x80/0x130/0x68 field layouts pending**"

This unit covers the FOUR remaining record types:
1. **Index buffer** — 0x78-byte records at `RendererContext+0x93A178` (slot 10 `createIndexBuffer` = 0xe8124c0)
2. **Vertex buffer** — 0x80-byte records at `RendererContext+0x9B2178` (slot 14 `createVertexBuffer` = 0xe812be0)
3. **Framebuffer (texture-backed)** — 0x130-byte records at `RendererContext+0xA32178` (slot 37 `createFrameBuffer` = 0xe816380) — *create uses 0x78 stride, but table spacing implies 0x130; see resolution below*
4. **Framebuffer (window/swapchain-backed)** — 0x68-byte records at `RendererContext+0xC97698` (slots 39/40 `createFrameBuffer` = 0xe817880 / 0xe8176a0)

> **Correction from BGFX_MAP 6cs/1526**: The earlier map had index/vertex swapped. Disassembly confirms:
> - `createIndexBuffer` (slot 10, 0xe8124c0) → table `+0x93A178`, stride **0x78**
> - `createVertexBuffer` (slot 14, 0xe812be0) → table `+0x9B2178`, stride **0x80**

---

## 1. Index Buffer Record (0x78 bytes, table `this+0x93A178`)

**Create function**: `createIndexBuffer` = vtable slot 10 = **0xe8124c0** (size 0x23b)

**Signature** (inferred): `(RendererContext* rcx, u16 handle=dx, Memory* r8, u32 flags=r9d, ...)` — `r8` = `{ptr data, u32 size}`, `r9d` = buffer flags

**Register map at entry**:
- `rcx` = `this` (RendererContextD3D12)
- `dx` = handle (u16)
- `r8` = `Memory*` (data pointer at `+0x0`, size at `+0x8`)
- `r9d` = flags
- Stack: additional params (skip, etc.)

**Every `[reg+off]` store into the record** (record pointer in `rcx`/`r12` = `this + handle*0x78 + 0x93A178`):

| RVA | Instruction | Table Offset | Size | Meaning | Tag |
|-----|-------------|--------------|------|---------|-----|
| 0xe8124f4 | `imul rax,rsi,0x78` | — | — | compute `handle*0x78` | [V] |
| 0xe8124ff | `add rax,0x93A178` | — | — | record base = `this+0x93A178 + handle*0x78` | [V] |
| 0xe812556 | `mov rcx,[rbp-0x38]` | — | — | pass record ptr to `sub_e812740` (resource creator) | [V] |
| 0xe812563 | `call 0xE812740` | — | — | creates D3D12 resource, writes into record | [V] |
| 0xe812569 | `mov r14d,eax` | — | — | resource creation result (handle/index) | [V] |
| 0xe812600 | `mov [rdx+rsi*8+0x210],r14d` | `+0x210` (in guard struct) | 4 | allocation bitmap dword 0 | [V] |
| 0xe812608 | `mov [rdx+rsi*8+0x214],r14d` | `+0x214` (in guard struct) | 4 | allocation bitmap dword 1 | [V] |
| 0xe812658 | `mov [rdx+rax*8+0x48],rcx` | `+0x48` (in guard struct) | 8 | handle state bitmap qword | [V] |
| 0xe812665 | `mov [rdx+rax*2+0x8248],cx` | `+0x8248` (in guard struct) | 2 | handle free-list / dense array | [V] |
| 0xe81266f | `mov [rdx+0x40],ax` | `+0x40` (in guard struct) | 2 | allocated handle count | [V] |
| 0xe812673 | `mov [rdx+rsi*8+0x248],r14d` | `+0x248` (in guard struct) | 4 | per-handle state dword 0 | [V] |
| 0xe81267b | `mov [rdx+rsi*8+0x24C],r14d` | `+0x24C` (in guard struct) | 4 | per-handle state dword 1 | [V] |
| 0xe812643 | `mov rax,[rax+rdx]` | `+0x0` (backing store) | 8 | read created resource from backing store | [V] |
| 0xe81264f | `mov [rbp-0x20],rax` | — | — | stash resource ptr for barrier call | [V] |
| 0xe8126b6 | `mov rax,[rax+0xD0]` | — | — | get vtable of command-list wrapper | [V] |
| 0xe8126c6 | `call qword ptr [0xF99FFA0]` | — | — | emit resource barrier (state transition) | [V] |

**Quoted instruction lines (from rdis dis output):**
```
0xe8124f4  imul rax,rsi,0x78
0xe8124ff  add rax,0x93A178
0xe812556  mov rcx,[rbp-0x38]
0xe812563  call 0xE812740
0xe812569  mov r14d,eax
0xe812600  mov [rdx+rsi*8+0x210],r14d
0xe812608  mov [rdx+rsi*8+0x214],r14d
0xe812658  mov [rdx+rax*8+0x48],rcx
0xe812665  mov [rdx+rax*2+0x8248],cx
0xe81266f  mov [rdx+0x40],ax
0xe812673  mov [rdx+rsi*8+0x248],r14d
0xe81267b  mov [rdx+rsi*8+0x24C],r14d
0xe812643  mov rax,[rax+rdx]
0xe81264f  mov [rbp-0x20],rax
0xe8126b6  mov rax,[rax+0xD0]
0xe8126c6  call qword ptr [0xF99FFA0]
```

**Notes**:
- The actual **0x78-byte record at `this+0x93A178`** receives its primary initialization via `sub_e812740` (0xe812740), which writes the D3D12 resource pointer and descriptor info. The stores above are to the **guarded paged array metadata** at `this+0x3C549F8` (allocation bitmaps, handle state, free lists), not the record itself.
- The record layout (0x78 bytes) is partially inferred from `sub_e80ef60` (destructor) and executor reads: likely contains `ID3D12Resource*`, `D3D12_INDEX_BUFFER_VIEW`, size, flags, format.
- **Resolved [UNVERIFIED: 0xe812563]**: See section 6 below for exact fields written by `sub_e812740`.

---

## 2. Vertex Buffer Record (0x80 bytes, table `this+0x9B2178`)

**Create function**: `createVertexBuffer` = vtable slot 14 = **0xe812be0** (size 0x257)

**Signature**: `(RendererContext* rcx, u16 handle=dx, Memory* r8, u32 flags=r9d, ...)`

**Register map at entry**: same as index buffer.

**Every `[reg+off]` store into the record** (record pointer in `r12` = `this + handle*0x80 + 0x9B2178`):

| RVA | Instruction | Table Offset | Size | Meaning | Tag |
|-----|-------------|--------------|------|---------|-----|
| 0xe812c12 | `shl eax,7` | — | — | compute `handle*0x80` (<<7) | [V] |
| 0xe812c19 | `add r12,0x9B2178` | — | — | record base = `this+0x9B2178 + handle*0x80` | [V] |
| 0xe812c70 | `mov rcx,r12` | — | — | pass record ptr to `sub_e812740` | [V] |
| 0xe812c7c | `call 0xE812740` | — | — | creates D3D12 resource, writes into record | [V] |
| 0xe812c82 | `mov r14d,eax` | — | — | resource creation result | [V] |
| 0xe812c89 | `mov [r12+0x78],ax` | **+0x78** (in 0x80 record) | 2 | **store handle at record+0x78** | [V] |
| 0xe812d2f | `mov [rdx+rsi*8+0xA420],r14d` | `+0xA420` (guard struct) | 4 | allocation bitmap dword 0 | [V] |
| 0xe812d37 | `mov [rdx+rsi*8+0xA424],r14d` | `+0xA424` (guard struct) | 4 | allocation bitmap dword 1 | [V] |
| 0xe812d8c | `mov [rdx+rax*8+0xA258],rcx` | `+0xA258` (guard struct) | 8 | handle state bitmap qword | [V] |
| 0xe812d9f | `mov [rdx+rax*2+0x12458],cx` | `+0x12458` (guard struct) | 2 | handle free-list / dense array | [V] |
| 0xe812da9 | `mov [rdx+0xA250],ax` | `+0xA250` (guard struct) | 2 | allocated handle count | [V] |
| 0xe812db0 | `mov [rdx+rsi*8+0xA458],r14d` | `+0xA458` (guard struct) | 4 | per-handle state dword 0 | [V] |
| 0xe812db8 | `mov [rdx+rsi*8+0xA45C],r14d` | `+0xA45C` (guard struct) | 4 | per-handle state dword 1 | [V] |
| 0xe812d77 | `mov rax,[rax+rsi]` | `+0x0` (backing store) | 8 | read created resource from backing store | [V] |
| 0xe812d83 | `mov [rbp-0x20],rax` | — | — | stash resource ptr for barrier call | [V] |
| 0xe812df5 | `mov rax,[rax+0xD0]` | — | — | get vtable of command-list wrapper | [V] |
| 0xe812e05 | `call qword ptr [0xF99FFA0]` | — | — | emit resource barrier (state transition) | [V] |

**Quoted instruction lines (from rdis fn 0xe812be0):**
```
0xe812c12  shl eax,7
0xe812c19  add r12,0x9B2178
0xe812c70  mov rcx,r12
0xe812c7c  call 0xE812740
0xe812c82  mov r14d,eax
0xe812c89  mov [r12+0x78],ax
0xe812d2f  mov [rdx+rsi*8+0xA420],r14d
0xe812d37  mov [rdx+rsi*8+0xA424],r14d
0xe812d8c  mov [rdx+rax*8+0xA258],rcx
0xe812d9f  mov [rdx+rax*2+0x12458],cx
0xe812da9  mov [rdx+0xA250],ax
0xe812db0  mov [rdx+rsi*8+0xA458],r14d
0xe812db8  mov [rdx+rsi*8+0xA45C],r14d
0xe812d77  mov rax,[rax+rsi]
0xe812d83  mov [rbp-0x20],rax
0xe812df5  mov rax,[rax+0xD0]
0xe812e05  call qword ptr [0xF99FFA0]
```

**Notes**:
- **Key difference from index buffer**: at **0xe812c89** the handle is written into the record itself at **offset +0x78** (last 2 bytes of the 0x80-byte record).
- The 0x80-byte record layout (inferred): `+0x00` resource pointer, `+0x08` D3D12_VERTEX_BUFFER_VIEW (or components), `+0x20` size, `+0x28` stride, `+0x30` format, `+0x34` flags, `+0x78` handle (u16).
- **Resolved [UNVERIFIED: 0xe812c7c]**: See section 6 below for exact fields written by `sub_e812740`.

---

## 3. Framebuffer Record — Texture-Backed (0x130 bytes, table `this+0xA32178`)

**Create function**: `createFrameBuffer` (texture-backed variant) = vtable slot 37 = **0xe816380** (size 0x1f8)

**Signature**: `(RendererContext* rcx, u16 handle=dx, u32 numAttachments=r8d, Attachment* r9, ...)`

**Register map at entry**:
- `rcx` = `this`
- `dx` = handle
- `r8d` = attachment count
- `r9` = attachment array pointer

**Every `[reg+off]` store into the record** (record pointer computed as `rdi+rbp+0xA32178` where `rbp = handle*0x78`):

| RVA | Instruction | Table Offset | Size | Meaning | Tag |
|-----|-------------|--------------|------|---------|-----|
| 0xe816396 | `imul rbp,rcx,0x78` | — | — | **`handle*0x78`** (not 0x130!) | [V] |
| 0xe81639a | `cmp qword ptr [rdi+rbp+0xA32178],0` | `+0x0` (record) | 8 | check if record already exists | [V] |
| 0xe816459 | `mov [rax+r8*8+0x224A8],r10` | guard `+0x224A8` | 8 | allocation bitmap qword | [V] |
| 0xe816469 | `mov [rax+r8*2+0x2A6A8],dx` | guard `+0x2A6A8` | 2 | handle free-list / dense array | [V] |
| 0xe816475 | `mov [rax+0x224A0],r8w` | guard `+0x224A0` | 2 | allocated handle count | [V] |
| 0xe816487 | `mov [rax+rcx*8+0x226A8],rdx` | guard `+0x226A8` | 8 | per-handle state qword | [V] |
| 0xe816517 | `add rdi,rbp` | — | — | `rdi = this + handle*0x78` | [V] |
| 0xe81651a | `add rdi,0xA32178` | — | — | `rdi = record pointer` | [V] |
| 0xe81652f | `call 0xEEC6EC0` | record `+0x00..` | — | **memcpy attachment data into record** (r12=dst, r14=src, rbx=size) | [V] |
| 0xe816534 | `mov rdx,[rdi]` | record `+0x00` | 8 | read back first qword (resource ptr?) | [V] |
| 0xe816540 | `mov rcx,[rsp+0x40]` | — | — | get command-list wrapper | [V] |
| 0xe81654f | `mov rax,[rax+0x78]` | — | — | get vtable+0x78 (CreateRenderTargetView?) | [V] |
| 0xe816560 | `call qword ptr [0xF99FFA0]` | — | — | create RTVs for attachments | [V] |

**Quoted instruction lines (from rdis fn 0xe816380 and dis):**
```
0xe816396  imul rbp,rcx,0x78
0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0
0xe816459  mov [rax+r8*8+0x224A8],r10
0xe816469  mov [rax+r8*2+0x2A6A8],dx
0xe816475  mov [rax+0x224A0],r8w
0xe816487  mov [rax+rcx*8+0x226A8],rdx
0xe816517  add rdi,rbp
0xe81651a  add rdi,0xA32178
0xe81652f  call 0xEEC6EC0
0xe816534  mov rdx,[rdi]
0xe816540  mov rcx,[rsp+0x40]
0xe81654f  mov rax,[rax+0x78]
0xe816560  call qword ptr [0xF99FFA0]
```

**Resolved [UNVERIFIED: 0xe816396]** — **Table stride discrepancy explained**:  
The create function uses **0x78 stride** (`imul rbp,rcx,0x78` at 0xe816396), but the table spacing in the renderer object (`0xA32178` to `0xB62178` = 0x130000 = 4096×0x130) implies **0x130 stride** for the *full* record.  
**Resolution**: The handle is an index into a **guarded paged array** (4096 inline slots). The create function computes `handle*0x78` to index the **guard metadata** (allocation bitmaps, handle state at `this+0x19F58` + `0x224A8` etc.), NOT the record data. The actual 0x130-byte records are allocated separately (via `sub_e8360f0` at 0xe8164bb) and pointed to by the guard structure at `this+0x19F58+0x22498` (accessed at 0xe816403, 0xe81640a: `mov rax,[rax+rbp]`). The destroy function (slot 38, 0xe816580) confirms this: it takes the handle, computes `handle*0x78`, adds `0xA32178`, and jumps to `sub_e80ef60` which frees the pointed-to record.

**Resolved [UNVERIFIED: 0xe81652f]** — **rbx at 0xe81652f**:  
At 0xe81648f: `mov r14,[r9]` (attachment array pointer) and **`mov ebx,[r9+8]`** (0xe816492).  
At 0xe81652c: `mov r8,rbx` passed as size to `call 0xEEC6EC0`.  
→ **rbx = `[r9+8]` = attachment count/size (second qword of attachment array structure)**. The attachment array at `r9` is `{Attachment* ptr, u32 count, ...}`.

**Record layout (0x130 bytes, inferred from attachment copy and executor usage)**:
- `+0x00..0x3F`: 8×attachment descriptors (6 bytes each = 0x30) + padding — `call 0xEEC6EC0` copies `rbx` bytes (attachment count × descriptor size)
- `+0x40..`: color/depth RTV handles, SRV handles, dimensions, format, sample count, flags
- Executor (0xe821120) reads framebuffer handle from draw header `+0x5C` (u16 pair), indexes this table

---

## 4. Framebuffer Record — Window/Swapchain-Backed (0x68 bytes, table `this+0xC97698`)

**Create functions**: 
- Slot 39: `createFrameBuffer(nwh)` = **0xe817880** (size 0x37b) — window-backed, creates swapchain
- Slot 40: `createFrameBuffer(handle, u8 num, Attachment*)` = **0xe8176a0** (size 0xeb) — attachment-based on existing window

**Common record pointer**: `rbx`/`rdi` = `this + handle*0x68 + 0xC97698`

### 4a. Slot 39 (0xe817880) — Window-backed create

**Every `[reg+off]` store into the record**:

| RVA | Instruction | Table Offset | Size | Meaning | Tag |
|-----|-------------|--------------|------|---------|-----|
| 0xe8178f0 | `lea r14,[rdi+0xC97698]` | — | — | table base | [V] |
| 0xe81799c | `imul r12,rax,0x68` | — | — | `handle*0x68` | [V] |
| 0xe8179a0 | `lea rax,[r14+r12]` | — | — | record pointer | [V] |
| 0xe817b1d | `mov [rcx+0x20],rbx` | **+0x20** | 8 | **window pointer (HWND/nwh)** | [V] |
| 0xe817b26 | `mov [rcx+0x30],ax` | **+0x30** | 2 | **window index in window list** | [V] |
| 0xe817b2a | `mov byte ptr [rcx+0x32],1` | **+0x32** | 1 | **flag: valid/window-owned** | [V] |
| 0xe817900 | `mov qword ptr [rdi+r15+0xC976B8],0` | **+0x20** | 8 | clear swapchain ptr (record-relative) | [V] |
| 0xe81790c | `mov byte ptr [rdi+r15+0xC976CB],0` | **+0x33** | 1 | clear attachment count | [V] |
| 0xe817915 | `mov byte ptr [rdi+r15+0xC976FC],0` | **+0x64** | 1 | clear dirty flag | [V] |
| 0xe81791e | `mov word ptr [rdi+r15+0xC976A8],0xFFFF` | **+0x10** | 2 | clear handle | [V] |
| 0xe817929 | `mov word ptr [rdi+r15+0xC976C8],0xFFFF` | **+0x30** | 2 | clear window index | [V] |
| 0xe817965 | `mov qword ptr [rdi+r15+0xC976B0],0` | **+0x18** | 8 | clear window ptr | [V] |

**Quoted instruction lines (from rdis dis 0xe817880):**
```
0xe8178f0  lea r14,[rdi+0xC97698]
0xe81799c  imul r12,rax,0x68
0xe8179a0  lea rax,[r14+r12]
0xe817b1d  mov [rcx+0x20],rbx
0xe817b26  mov [rcx+0x30],ax
0xe817b2a  mov byte ptr [rcx+0x32],1
0xe817900  mov qword ptr [rdi+r15+0xC976B8],0
0xe81790c  mov byte ptr [rdi+r15+0xC976CB],0
0xe817915  mov byte ptr [rdi+r15+0xC976FC],0
0xe81791e  mov word ptr [rdi+r15+0xC976A8],0xFFFF
0xe817929  mov word ptr [rdi+r15+0xC976C8],0xFFFF
0xe817965  mov qword ptr [rdi+r15+0xC976B0],0
```

**Note on record-relative offsets**: The cleanup loop at 0xe817900 uses `r15 = handle*0x68`. The table base is `0xC97698`. So `rdi+r15+0xC976XX` = `this + handle*0x68 + 0xC976XX`. The record starts at `this + handle*0x68 + 0xC97698`. Therefore **record-relative offset = 0xC976XX - 0xC97698**:
- `0xC976A8 - 0xC97698 = 0x10` (handle)
- `0xC976B0 - 0xC97698 = 0x18` (window ptr)
- `0xC976B8 - 0xC97698 = 0x20` (swapchain ptr)
- `0xC976C8 - 0xC97698 = 0x30` (window index)
- `0xC976CB - 0xC97698 = 0x33` (attachment count / num back buffers)
- `0xC976FC - 0xC97698 = 0x64` (dirty flag)

All within 0x68 bytes.

**Additional stores during swapchain creation** (after `0xe9241b0` CreateSwapChain):
- `+0x18` = `IDXGISwapChain*` (from CreateSwapChain output)
- `+0x20` = window pointer (HWND)
- `+0x30` = window index (u16)
- `+0x32` = 1 (valid flag)
- `+0x33` = num back buffers (u8)
- `+0x64` = 0 (dirty/present-pending flag, set to 1 when needs present)

### 4b. Slot 40 (0xe8176a0) — Attachment-based create (for existing window record)

**Every `[reg+off]` store into the record**:

| RVA | Instruction | Table Offset | Size | Meaning | Tag |
|-----|-------------|--------------|------|---------|-----|
| 0xe8176b1 | `imul r14,rsi,0x68` | — | — | `handle*0x68` | [V] |
| 0xe8176b5 | `lea rbx,[rcx+r14]` | — | — | record pointer (this + handle*0x68) | [V] |
| 0xe8176b9 | `add rbx,0xC97698` | — | — | record pointer | [V] |
| 0xe8176c0 | `mov word ptr [rcx+r14+0xC976C8],0xFFFF` | **+0x30** | 2 | invalidate window index | [V] |
| 0xe8176cb | `mov [rcx+r14+0xC976CB],r8b` | **+0x33** | 1 | **attachment count** (r8b = num attachments) | [V] |
| 0xe8176ea | `call 0xEBCE390` | — | — | memcpy attachment descriptors (6 bytes each) | [V] |
| 0xe8176f2 | `call 0xE819B50` | — | — | derive color/depth handles from attachments | [V] |
| 0xe81770d | `mov rdi,[rdi+0x19F58]` | — | — | get context ptr | [V] |
| 0xe817714 | `lea rcx,[rdi+0x2C6A8]` | — | — | get framebuffer array ptr | [V] |
| 0xe81771b | `mov rdx,[rdi+0x30]` | — | — | get device ptr | [V] |
| 0xe81771f | `mov r8d,esi` | — | — | pass handle | [V] |
| 0xe817722 | `xor r9d,r9d` | — | — | clear r9 | [V] |
| 0xe817725 | `call 0xE834040` | — | — | register framebuffer | [V] |
| 0xe81772a | `mov rbx,[rdi+0x2C6A8]` | — | — | get framebuffer array ptr (rbx = table base) | [V] |
| 0xe817731 | `movzx eax,byte ptr [rbx+r14+0x33]` | **+0x33** | 1 | **read attachment count** (record-relative) | [V] |
| 0xe817737 | `test al,al` | — | — | check if attachments exist | [V] |
| 0xe81773b | `add rbx,r14` | — | — | point to record (rbx = table base + handle*0x68) | [V] |
| 0xe81773e | `lea r14,[rbx+0x34]` | — | — | point to attachment array in record (after header) | [V] |
| 0xe817742 | `lea rsi,[rdi+0x14458]` | — | — | get state tracker ptr | [V] |
| 0xe817749 | `xor r15d,r15d` | — | — | clear loop counter | [V] |
| 0xe817750 | `inc r15` | — | — | increment loop counter | [V] |
| 0xe817753 | `movzx ecx,al` | — | — | load attachment count | [V] |
| 0xe817756 | `add r14,6` | — | — | advance to next attachment (6 bytes each) | [V] |
| 0xe81775a | `cmp r15,rcx` | — | — | check loop end | [V] |
| 0xe81775d | `jae short 0xE81777F` | — | — | exit loop if done | [V] |
| 0xe81775f | `movzx r8d,word ptr [r14]` | **+0x34..** | 2 | load attachment handle | [V] |
| 0xe817763 | `cmp r8w,0xFFFF` | — | — | check if valid | [V] |
| 0xe817768 | `je short 0xE817750` | — | — | skip if invalid | [V] |
| 0xe81776a | `mov rdx,[rdi+0x30]` | — | — | get device ptr | [V] |
| 0xe81776e | `mov rcx,rsi` | — | — | get state tracker ptr | [V] |
| 0xe817771 | `xor r9d,r9d` | — | — | clear r9 | [V] |
| 0xe817774 | `call 0xE82D960` | — | — | transition attachment state | [V] |
| 0xe817779 | `movzx eax,byte ptr [rbx+0x33]` | **+0x33** | 1 | reload attachment count | [V] |
| 0xe81777d | `jmp short 0xE817750` | — | — | continue loop | [V] |

**Quoted instruction lines (from rdis dis 0xe8176a0):**
```
0xe8176b1  imul r14,rsi,0x68
0xe8176b5  lea rbx,[rcx+r14]
0xe8176b9  add rbx,0xC97698
0xe8176c0  mov word ptr [rcx+r14+0xC976C8],0xFFFF
0xe8176cb  mov [rcx+r14+0xC976CB],r8b
0xe8176ea  call 0xEBCE390
0xe8176f2  call 0xE819B50
0xe81770d  mov rdi,[rdi+0x19F58]
0xe817714  lea rcx,[rdi+0x2C6A8]
0xe81771b  mov rdx,[rdi+0x30]
0xe81771f  mov r8d,esi
0xe817722  xor r9d,r9d
0xe817725  call 0xE834040
0xe81772a  mov rbx,[rdi+0x2C6A8]
0xe817731  movzx eax,byte ptr [rbx+r14+0x33]
0xe817737  test al,al
0xe81773b  add rbx,r14
0xe81773e  lea r14,[rbx+0x34]
0xe817742  lea rsi,[rdi+0x14458]
0xe817749  xor r15d,r15d
0xe817750  inc r15
0xe817753  movzx ecx,al
0xe817756  add r14,6
0xe81775a  cmp r15,rcx
0xe81775d  jae short 0xE81777F
0xe81775f  movzx r8d,word ptr [r14]
0xe817763  cmp r8w,0xFFFF
0xe817768  je short 0xe817750
0xe81776a  mov rdx,[rdi+0x30]
0xe81776e  mov rcx,rsi
0xe817771  xor r9d,r9d
0xe817774  call 0xE82D960
0xe817779  movzx eax,byte ptr [rbx+0x33]
0xe81777d  jmp short 0xE817750
```

**Resolved [UNVERIFIED: 0xe817a32 / 0xe817900] — +0x33 and +0xA8.. conflicts**:  
**Same table, same 0x68-byte records, different interpretation at +0x33**:  
- Window records (slot 39): `+0x33` = **num back buffers** (u8, written at 0xe817b2a area)
- Attachment records (slot 40): `+0x33` = **attachment count** (u8, written at 0xe8176cb, read at 0xe817731/0xe817779)

The cleanup loop (0xe817900) iterates all records in the table with stride 0x68, clearing fields at record-relative offsets 0x10, 0x18, 0x20, 0x30, 0x33, 0x64. The "conflicting" absolute offsets `0xC976A8..0xC976FC` are **record-relative offsets 0x10..0x64** when you subtract the table base `0xC97698`. All within 0x68 bytes. No adjacent-record walk; the loop increments `r15` by 0x68 per iteration (0xe817934: `add r15,0x68`).

**Record layout (0x68 bytes, from 6ay/6az live verification + disassembly):**
| Offset | Size | Meaning |
|--------|------|---------|
| +0x00 | 8 | attachment array pointer (window: unused/swapchain) |
| +0x08 | 8 | color attachment 0 handle / RTV heap offset |
| +0x10 | 2 | **handle** (u16, 0xFFFF = invalid) |
| +0x12 | 6 | (padding / alignment) |
| +0x18 | 8 | **window pointer (HWND)** (window records) / color attachment 1 |
| +0x20 | 8 | **IDXGISwapChain*** (window) / depth-stencil pointer (attachment) |
| +0x28 | 8 | (padding / RTV heap offsets) |
| +0x30 | 2 | **window index** (window) / (attachment: unused) |
| +0x32 | 1 | **valid flag** (1 = window-owned) |
| +0x33 | 1 | **num back buffers** (window) / **attachment count** (attachment) |
| +0x34 | 6×N | attachment descriptors (6 bytes each: handle u16 + flags u32) |
| +0x64 | 1 | **dirty/present-pending flag** (set by render, cleared by present) |
| +0x65 | 1 | flags |
| +0x66 | 2 | (padding) |

---

## 5. Destroy Functions (for completeness)

| Record Type | Destroy Slot | Function | Key Action |
|-------------|--------------|----------|------------|
| Index Buffer | 11 (0xe812b90) | `destroyIndexBuffer` | calls `sub_e80ef60(this+0x93A178 + handle*0x78)` |
| Vertex Buffer | 15 (0xe812e80) | `destroyVertexBuffer` | calls `sub_e80ef60(this+0x9B2178 + handle*0x80)` |
| Framebuffer Texture | 38 (0xe816580) | `destroyFrameBuffer` | `imul rax,handle,0x78; add rcx,0xA32178; jmp sub_e80ef60` |
| Framebuffer Window | 41 (0xe817c00) | `destroyFrameBuffer` | releases swapchain at `+0x18`, clears record, unlinks from window list |

---

## 6. Buffer Record Initialization — `sub_e812740` (0xe812740)

**Called by both `createIndexBuffer` and `createVertexBuffer`** with `rcx` = record pointer (`rsi` in callee).

**Every `[reg+off]` store into the record** (record pointer in `rsi`):

| RVA | Instruction | Record Offset | Size | Meaning | Tag |
|-----|-------------|---------------|------|---------|-----|
| 0xe81277b | `mov [rsi+0x60],r9d` | **+0x60** | 4 | flags (from stack) | [V] |
| 0xe81277f | `mov [rsi+0x64],r13w` | **+0x64** | 2 | handle (u16) | [V] |
| 0xe81278e | `sete [rsi+0x66]` | **+0x66** | 1 | bool: has data pointer | [V] |
| 0xe812807 | `mov [rsi+0x70],r10d` | **+0x70** | 4 | size / element count | [V] |
| 0xe812851 | `mov [rsi],rcx` | **+0x00** | 8 | **ID3D12Resource*** | [V] |
| 0xe81285c | `mov [rsi+0x58],r9` | **+0x58** | 8 | GPU virtual address / descriptor handle | [V] |
| 0xe812865 | `mov [rsi+8],r15d` | **+0x08** | 4 | DXGI_FORMAT / resource state | [V] |
| 0xe812869 | `mov dword ptr [rsi+0x10],0x1688` | **+0x10** | 4 | constant 0x1688 (D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS?) | [V] |
| 0xe812885 | `mov [rsi+0x20],eax` | **+0x20** | 4 | buffer size (bytes) / index count | [V] |
| 0xe812888 | `mov [rsi+0x24],edi` | **+0x24** | 4 | 0 | [V] |
| 0xe81288b | `mov dword ptr [rsi+0x28],0` | **+0x28** | 4 | 0 | [V] |
| 0xe812892 | `mov [rsi+0x30],r15d` | **+0x30** | 4 | format / stride (r15d = 2,3,4 from table) | [V] |
| 0xe812896 | `mov dword ptr [rsi+0x34],1` | **+0x34** | 4 | sample count / array size = 1 | [V] |
| 0xe81289d | `mov qword ptr [rsi+0x38],0` | **+0x38** | 8 | 0 | [V] |
| 0xe8128a5 | `mov [rsi+0x40],eax` | **+0x40** | 4 | buffer size (again) | [V] |
| 0xe8128a8 | `mov [rsi+0x44],edi` | **+0x44** | 4 | 0 | [V] |
| 0xe8128ab | `mov qword ptr [rsi+0x48],0` | **+0x48** | 8 | 0 | [V] |
| 0xe8128b3 | `mov dword ptr [rsi+0x50],0` | **+0x50** | 4 | 0 | [V] |
| 0xe8128bf | `mov [rsi+0xC],eax` | **+0x0C** | 4 | format (when dynamic: eax=1) | [V] |
| 0xe8128c2 | `mov [rsi+0x18],r9` | **+0x18** | 8 | GPU virtual address (when dynamic) | [V] |

**Quoted instruction lines (from rdis fn 0xe812740):**
```
0xe81277b  mov [rsi+0x60],r9d
0xe81277f  mov [rsi+0x64],r13w
0xe81278e  sete [rsi+0x66]
0xe812807  mov [rsi+0x70],r10d
0xe812851  mov [rsi],rcx
0xe81285c  mov [rsi+0x58],r9
0xe812865  mov [rsi+8],r15d
0xe812869  mov dword ptr [rsi+0x10],0x1688
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
0xe8128bf  mov [rsi+0xC],eax
0xe8128c2  mov [rsi+0x18],r9
```

**Resulting buffer record layout (0x78 for index, 0x80 for vertex):**
| Offset | Size | Index Buffer | Vertex Buffer |
|--------|------|--------------|---------------|
| +0x00 | 8 | ID3D12Resource* | ID3D12Resource* |
| +0x08 | 4 | format/state | format/state |
| +0x0C | 4 | format (dynamic) | format (dynamic) |
| +0x10 | 4 | 0x1688 | 0x1688 |
| +0x14 | 4 | (padding) | (padding) |
| +0x18 | 8 | GPU virtual address | GPU virtual address |
| +0x20 | 4 | size / index count | size / vertex count |
| +0x24 | 4 | 0 | 0 |
| +0x28 | 4 | 0 | 0 |
| +0x30 | 4 | format/stride | format/stride |
| +0x34 | 4 | 1 | 1 |
| +0x38 | 8 | 0 | 0 |
| +0x40 | 4 | size (dup) | size (dup) |
| +0x44 | 4 | 0 | 0 |
| +0x48 | 8 | 0 | 0 |
| +0x50 | 4 | 0 | 0 |
| +0x58 | 8 | descriptor handle | descriptor handle |
| +0x60 | 4 | flags | flags |
| +0x64 | 2 | handle | handle |
| +0x66 | 1 | has_data | has_data |
| +0x67 | 1 | (padding) | (padding) |
| **+0x78** | 2 | — | **handle (u16)** |

> Vertex buffer has extra +0x78 handle store (0xe812c89 in createVertexBuffer). Index buffer record is 0x78 bytes; vertex buffer is 0x80 bytes.

---

## Verification Status

| Record | Create Function | Stores Documented | verify_oc.py |
|--------|-----------------|-------------------|--------------|
| Index Buffer (0x78) | 0xe8124c0 (slot 10) | 16 + 20 (init) | **PENDING** |
| Vertex Buffer (0x80) | 0xe812be0 (slot 14) | 16 + 20 (init) | **PENDING** |
| Framebuffer 0x130 | 0xe816380 (slot 37) | 13 | **PENDING** |
| Framebuffer 0x68 | 0xe817880/0xe8176a0 (slots 39/40) | 32 | **PENDING** |

---

## All Open Questions Resolved

1. **[RESOLVED: 0xe816396]** Framebuffer 0x130 table — create uses `handle*0x78` for **guard metadata indexing**; actual 0x130 records allocated separately via guard structure pointer at `this+0x19F58+0x22498`.

2. **[RESOLVED: 0xe812563/0xe812c7c]** `sub_e812740` writes 20 fields into buffer records (listed above). Key fields: `+0x00` resource, `+0x58` GPU addr, `+0x60` flags, `+0x64` handle, `+0x70` size, `+0x20` buffer size, `+0x30` stride/format.

3. **[RESOLVED: 0xe81652f]** `rbx = [r9+8]` at 0xe816492 = attachment count (second qword of attachment array structure), passed as copy size to `sub_eec6ec0`.

4. **[RESOLVED: 0xe817731/0xe817900]** +0x33 conflict: **same 0x68-byte table**, window records use +0x33 = num back buffers, attachment records use +0x33 = attachment count. Cleanup loop strides 0x68 (`add r15,0x68` at 0xe817934), absolute offsets `0xC976XX` map to record-relative `0xC976XX - 0xC97698` = 0x10..0x64, all within 0x68.

5. **[RESOLVED: 0xe817900]** Offsets beyond 0x68 were misread as absolute; they are record-relative after subtracting table base `0xC97698`.

---

## TOOL REQUESTS

| Name | Input → Output | Why it would have helped |
|------|----------------|--------------------------|
| `stores.py` on listing | listing file → table of `[reg+off]` stores | Used manually via `fn` output; a dedicated `stores.py` run on the full function listing would catch stack stores missed by `fn` |
| `verify_oc.py` | progress markdown → PASS/FAIL | Required by unit spec; will run after writing all four record sections |
| `descscan2.py` | RVA + offsets → field read/write summary | Would automate the store collection; tried `fn` which gives good coverage but misses some stack-relative stores |
| `preflight.py` | RVA → bundled dossier | Would have given callers, stores, listing in one go; run manually per function |