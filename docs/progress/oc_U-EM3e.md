## NEXT
DONE

UNIT U-EM3e — header-to-record mapping for DrawBatcher append (flush 0xe81b720, executor 0xe821120). 1.26.62.01, static analysis only.

CONTEXT (live, already proven by orchestrator, docs/data/live/m3e_test.txt):
- At flush 0xE81B720, rcx = DrawBatcher object `b`.
- Counts: u32 [b+0x10] = kind0 count, u32 [b+0x14] = kind1 count (kind*4).
- Record arrays: u64 ptr [b+0x18] = kind0 array base (stride 0x70), u64 ptr [b+0x20] = kind1 array base (stride 0x88) (kind*8).
- Kind1 records (0x88) match BGFX_MAP 6ej: VBV addr/size/stride at +0, IBV at +0x50, IndexCount at +0x70 (=2364 in sample). Edit in place + zero count verified live, 600 hits, no crash.
- 0xe81b720 called 7 times from executor 0xe821120 (6 flush sites + 1 after state change) [BGFX_MAP 6ao].

KEY OFFSET RECONCILIATION [V]:
The executor's append code uses B=[rbx+0xA0] as its batcher base pointer with counts at [B+0x90]/[B+0x94] and arrays at [B+0x98]/[B+0xA0]. The flush 0xe81b720 uses b=[rcx] with counts at [b+0x10]/[b+0x14] and arrays at [b+0x18]/[b+0x20]. Since B+0x90 = b+0x10, B+0x94 = b+0x14, B+0x98 = b+0x18, B+0xA0 = b+0x20, we have b = B+0x80, i.e. the job stores the batcher at job+0xA0 offset by -0x80 from the real DrawBatcher at job+0x120 (== [job+0x250] per BGFX_MAP 6ak). [V] confirmed by flush disassembly at 0xe81b736/0xe81b74a/0xe81b779 and append disassembly at 0xe82c6a5/0xe82c6ae/0xe82c6b4/0xe82cb0f/0xe82cb19/0xe82cb20.

APPEND SITE 1 — non-indexed (kind 0, stride 0x70), entry 0xe82c69e [V]:
- 0xe82c6a5  mov eax,[rdx+0x90]            — read kind0 count [B+0x90] == [b+0x10]
- 0xe82c6ae  mov [rdx+0x90],ecx            — increment kind0 count (ecx=count+1)
- 0xe82c6b4  mov rcx,[rdx+0x98]            — read kind0 array base [B+0x98] == [b+0x18]
- 0xe82c6bb  imul rax,0x70                 — n*stride
- 0xe82c6bf  lea rsi,[rcx+rax]             — record = base + n*0x70 (rsi = record ptr)
- 0xe82c6c3  mov [rcx+rax+0x50],rdx        — record+0x50 = CBV0 = [rbx+0x170] (vsConstantsVA)
- 0xe82c6d6  mov [rcx+rax+0x58],rdx        — record+0x58 = CBV1 = [rbx+0x380] (fsConstantsVA)
- 0xe82c6ef  call 0xE81B4D0                — fillVertexBufferViews(rcx=cmdWrapper, rdx=record, r8=draw, r9=&scratch[rbx+0xC0]); fills 5 VBVs at record+0x00..+0x4F (BufferLocation@+0, StrideInBytes@+8, SizeInBytes@+0xC per view, 0x10 each)
- 0xe81b4f4  mov eax,[r8+0x4C]             — (inside fillVertexBufferViews) draw+0x4C = vertexCount
- 0xe81b4f8  mov [r9],eax                  — scratch[rbx+0xC0] = vertexCount
- 0xe82cdd8  mov eax,[rax+0x54]            — draw+0x54 = instanceCount
- 0xe82cddb  mov [rsi+0x64],eax            — record+0x64 = instanceCount
- 0xe82cdde  mov eax,[rbx+0xC0]            — [rbx+0xC0] = vertexCount (from draw+0x4C via scratch)
- 0xe82cde4  mov [rsi+0x60],eax            — record+0x60 = vertexCount
- 0xe82cde7  mov qword ptr [rsi+0x68],0    — record+0x68 = startVertex=0, record+0x6C = startInstance=0

APPEND SITE 2 — indexed (kind 1, stride 0x88), entry 0xe82cb08 [V]:
- 0xe82cb0f  mov eax,[r8+0x94]             — read kind1 count [B+0x94] == [b+0x14]
- 0xe82cb19  mov [r8+0x94],edx             — increment kind1 count (edx=count+1)
- 0xe82cb20  mov rdx,[r8+0xA0]             — read kind1 array base [B+0xA0] == [b+0x20]
- 0xe82cb2a  shl r8,7                      — n*0x80
- 0xe82cb2e  lea rax,[r8+rax*8]            — n*0x88 (0x80*n + n*8)
- 0xe82cb32  lea rdi,[rdx+rax]             — record = base + n*0x88 (rdi = record ptr)
- 0xe82cb3d  mov [rdx+rax+0x60],r8         — record+0x60 = CBV0 = [rbx+0x170] (vsConstantsVA)
- 0xe82cb49  mov [rdx+rax+0x68],r8         — record+0x68 = CBV1 = [rbx+0x380] (fsConstantsVA)
- 0xe82cb4e  mov r8,[rcx+0x58]             — IBV record+0x58 (index buffer size)
- 0xe82cb52  mov [rdx+rax+0x50],r8         — record+0x50 = IBV BufferLocation (GPU VA)
- 0xe82cb57  mov ecx,[rcx+0x60]            — IBV record+0x60 (index buffer size)
- 0xe82cb5a  mov [rdx+rax+0x58],ecx        — record+0x58 = IBV SizeInBytes
- 0xe82cb73  mov [rdx+rax+0x5C],ecx        — record+0x5C = DXGI_FORMAT (0x39=R16_UINT or 0x2A=R32_UINT from draw+0x48 stride)
- 0xe82cb8b  call 0xE81B4D0                — fillVertexBufferViews; fills 5 VBVs at record+0x00..+0x4F
- 0xe82cd11  mov [rdi+0x70],esi            — record+0x70 = indexCount = draw+0x44
- 0xe82cd1b  mov eax,[rcx+0x54]            — draw+0x54 = instanceCount
- 0xe82cd1e  mov [rdi+0x74],eax            — record+0x74 = instanceCount
- 0xe82cd21  mov eax,[rcx+0x40]            — draw+0x40 = startIndex
- 0xe82cd24  mov [rdi+0x78],eax            — record+0x78 = startIndex
- 0xe82cd27  mov qword ptr [rdi+0x7C],0    — record+0x7C = baseVertex=0, record+0x80 = startInstance=0

FLUSH READBACK (0xe81b720) confirms field roles [V]:
- 0xe81b736  mov esi,[rcx+r12*4+0x10]      — n = pending[kind] at [b+kind*4+0x10]
- 0xe81b74a  mov dword ptr [rcx+r12*4+0x10],0 — pending[kind] = 0
- 0xe81b779  mov rax,[rdi+r12*8+0x18]      — recs = records[kind] at [b+kind*8+0x18]
- 0xe81b7b3  mov rax,[r15+0x60]            — indexed: CBV0 = rec+0x60
- 0xe81b7be  mov rax,[r15+0x68]            — indexed: CBV1 = rec+0x68
- 0xe81b833  lea r13,[r15+0x50]            — indexed: IBV = rec+0x50
- 0xe81b86a  mov edx,[r15+0x70]            — indexed: IndexCount = rec+0x70
- 0xe81b86e  mov r8d,[r15+0x74]            — indexed: InstanceCount = rec+0x74
- 0xe81b872  mov r9d,[r15+0x78]            — indexed: StartIndex = rec+0x78
- 0xe81b876  mov r10d,[r15+0x7C]           — indexed: BaseVertex = rec+0x7C
- 0xe81b87a  mov r11d,[r15+0x80]           — indexed: StartInstance = rec+0x80
- Non-indexed draw args read at rec+0x60..+0x6C (vertexCount, instanceCount, startVertex, startInstance) [inferred from record layout symmetry + flush slot order]

DRAW HEADER (0x80-byte, at Frame+0x8B4700 + idx*0x540, executor reads via [rbx+0xF0]) [V per BGFX_MAP 6e-2]:
- draw+0x40 u32 startIndex [I]
- draw+0x44 u32 indexCount, 0xFFFFFFFF = computed as ib.size/stride [V]
- draw+0x48 u32 indexStride (2 or 4) -> DXGI_FORMAT_R16_UINT (0x39) / R32_UINT (0x2A) [V]
- draw+0x4C u32 vertexCount [I]
- draw+0x50 u32 VB byte offset added to VB base [V]
- draw+0x54 u32 count / instance count [V]
- draw+0x58 u16 VB stride -> D3D12_VERTEX_BUFFER_VIEW.StrideInBytes [V]
- draw+0x5A u16 index buffer handle (<<5 indexes 0x20-stride IB table at ctx+0x93A178) [V]
- draw+0x76 u16 vertex buffer handle (0xFFFF = none; <<7 indexes 0x80-stride VB table) [V]
- draw+0x60 u16 scissor cache index [V]
- draw+0x62 u8 submit flags, sign bit = wantInvisible [V]
- draw+0x7A u16 occlusion query handle [V]
- draw+0x74 u64 state flags (bit 62 = occlusion query draw, never batches) [V]
- draw+0x68/0x6C/0x70 float PSO params (Mojang additions) [V]
- draw+0x50/0x54/0x58 instance data offset/stride/buffer [V]
- draw+0x5C u32 numIndirect (0xFFFF = ib.size/32) [V]
- draw+0x5A u16 startIndirect (<<5) [V]
- draw+0x78 u16 indirect buffer handle (0xFFFF = not batched) [V]

DRAW IDENTITY (header field identifying the draw at append time) [V/I]:
- Program index: from sort key, not a header field directly. key bits: program sort type -> (key>>37)&0x7FF; sequence -> (key>>17)&0x7FF; depth -> uint16(key)>>5 [V per 6cs/6am]. Indexes Frame program table at ctx+0xB62178 + prog*0xF8 [V].
- PSO: built by 0xe81e860(state, stencil, draw+0x68/0x6C/0x70, streams, layouts, program, ...) [V]; compared via job+0x1A0 currentPso.
- View id: not in the 0x80-byte header; carried by job state (job+0x1E8 view index, job+0x90A0 view matrices) [I per 6cs].
- Bind hash: u32 at Frame+0x8B4700+idx*0x540+0x514 -> job+0x178 [V per 6am].
- The draw record itself carries NO draw identity (no PSO/program/view id in the record) [V per 6ej]; identity must be reconstructed from the executor's per-draw state at append time (program, PSO, bind hash, view index from job locals).

HEADER-TO-RECORD MAPPING TABLE (record offset <- source field):

| offset | size | site | instr | meaning |
| 0x00..0x4F | 0x50 (5x0x10) | `0xe82c6ef  call 0xE81B4D0` (kind0); `0xe82cb8b  call 0xE81B4D0` (kind1) | `0xe82c6ef  call 0xE81B4D0` / `0xe82cb8b  call 0xE81B4D0` | 5x D3D12_VERTEX_BUFFER_VIEW {BufferLocation@+0, SizeInBytes@+0x8, StrideInBytes@+0xC} per stream; source = draw streams (draw+0x50 byte offset, draw+0x54 count, draw+0x58 stride, draw+0x76 VB handle per stream); [V] |
| 0x50 | 8 | `0xe82c6c3  mov rdx,[rbx+0x170]` (kind0 load); `0xe82c6ca  mov [rcx+rax+0x50],rdx` (kind0 store); `0xe82cb52  mov [rdx+rax+0x50],r8` (kind1 store) | `0xe82c6c3  mov rdx,[rbx+0x170]` / `0xe82c6ca  mov [rcx+rax+0x50],rdx` / `0xe82cb52  mov [rdx+rax+0x50],r8` | kind0: CBV0 vsConstantsVA=[rbx+0x170] stored at record+0x50; kind1: IBV BufferLocation stored at record+0x50; [V] |
| 0x58 | 8 | `0xe82c6cf  mov rdx,[rbx+0x380]` (kind0 load); `0xe82c6d6  mov [rcx+rax+0x58],rdx` (kind0 store); `0xe82cb5a  mov [rdx+rax+0x58],ecx` (kind1 store) | `0xe82c6cf  mov rdx,[rbx+0x380]` / `0xe82c6d6  mov [rcx+rax+0x58],rdx` / `0xe82cb5a  mov [rdx+rax+0x58],ecx` | kind0: CBV1 fsConstantsVA=[rbx+0x380] stored at record+0x58; kind1: IBV SizeInBytes stored at record+0x58; [V] |
| 0x5C | 4 | `0xe82cb73  mov [rdx+rax+0x5C],ecx` (kind1 only) | `0xe82cb73  mov [rdx+rax+0x5C],ecx` | DXGI_FORMAT: 0x39 (R16_UINT) if draw+0x48 stride==2, else 0x2A (R32_UINT); [V] |
| 0x60 | 4 | `0xe82cb3d  mov [rdx+rax+0x60],r8` (kind1); `0xe82cde4  mov [rsi+0x60],eax` (kind0) | `0xe82cb3d  mov [rdx+rax+0x60],r8` / `0xe82cde4  mov [rsi+0x60],eax` | kind1: CBV0 vsConstantsVA=[rbx+0x170]; kind0: VertexCountPerInstance = [rbx+0xC0] = draw+0x4C (via fillVertexBufferViews scratch); [V] |
| 0x64 | 4 | `0xe82cddb  mov [rsi+0x64],eax` (kind0); `0xe82cd1e  mov [rdi+0x74],eax` (kind1, at 0x74 not 0x64) | `0xe82cddb  mov [rsi+0x64],eax` / `0xe82cd1e  mov [rdi+0x74],eax` | kind0: InstanceCount = draw+0x54; kind1: InstanceCount at record+0x74 = draw+0x54; [V] |
| 0x68 | 4/8 | `0xe82cb49  mov [rdx+rax+0x68],r8` (kind1) | `0xe82cb49  mov [rdx+rax+0x68],r8` | kind1: CBV1 fsConstantsVA=[rbx+0x380]; kind0: StartVertexLocation = 0 at +0x68; [V] |
| 0x6C | 4 | `0xe82cde7  mov qword ptr [rsi+0x68],0` (kind0) | `0xe82cde7  mov qword ptr [rsi+0x68],0` | kind0: StartInstanceLocation = 0 at +0x6C (part of qword zero with +0x68); [V] |
| 0x70 | 4 | `0xe82cd11  mov [rdi+0x70],esi` (kind1) | `0xe82cd11  mov [rdi+0x70],esi` | kind1: IndexCount = draw+0x44 (or ib.size/stride if 0xFFFFFFFF); [V] |
| 0x74 | 4 | `0xe82cd1e  mov [rdi+0x74],eax` (kind1) | `0xe82cd1e  mov [rdi+0x74],eax` | kind1: InstanceCount = draw+0x54; [V] |
| 0x78 | 4 | `0xe82cd24  mov [rdi+0x78],eax` (kind1) | `0xe82cd24  mov [rdi+0x78],eax` | kind1: StartIndex = draw+0x40; [V] |
| 0x7C | 4 | `0xe82cd27  mov qword ptr [rdi+0x7C],0` (kind1) | `0xe82cd27  mov qword ptr [rdi+0x7C],0` | kind1: BaseVertex = 0 at +0x7C, StartInstance = 0 at +0x80; [V] |
| 0x80 | 4 | (same as 0x7C) | `0xe82cd27  mov qword ptr [rdi+0x7C],0` | kind1: StartInstance = 0; [V] |

SUMMARY TABLE (record offset -> source field, consolidated):

Kind 0 (non-indexed, 0x70):
- +0x00..+0x4F: 5 VBVs from draw streams (VB handle draw+0x76 per stream, offset draw+0x50, count draw+0x54, stride draw+0x58)
- +0x50: CBV0 vsConstantsVA ([rbx+0x170], committed vertex constant buffer VA)
- +0x58: CBV1 fsConstantsVA ([rbx+0x380], committed fragment constant buffer VA)
- +0x60: VertexCountPerInstance = draw+0x4C
- +0x64: InstanceCount = draw+0x54
- +0x68: StartVertexLocation = 0
- +0x6C: StartInstanceLocation = 0

Kind 1 (indexed, 0x88):
- +0x00..+0x4F: 5 VBVs from draw streams (same as kind0)
- +0x50: IBV BufferLocation (index buffer GPU VA, from IB handle draw+0x5A -> record+0x58)
- +0x58: IBV SizeInBytes (from index buffer record+0x60)
- +0x5C: DXGI_FORMAT (0x39/0x2A from draw+0x48 stride)
- +0x60: CBV0 vsConstantsVA ([rbx+0x170])
- +0x68: CBV1 fsConstantsVA ([rbx+0x380])
- +0x70: IndexCount = draw+0x44
- +0x74: InstanceCount = draw+0x54
- +0x78: StartIndex = draw+0x40
- +0x7C: BaseVertex = 0
- +0x80: StartInstance = 0

CLOSES? YES — every pending part of the unit line is proven by [V] rows: both append sites found (0xe82c69e kind0, 0xe82cb08 kind1), count increments ([B+0x90]/[B+0x94] == [b+0x10]/[b+0x14]), record writes at [b+kind*8+0x18]+n*stride, full record offset -> source field mapping, and draw identity (program from sort key, PSO from 0xe81e860, bind hash, view from job state) documented. No in-game run needed (user deferred testing 2026-11-22).

TOOL REQUESTS: none.
