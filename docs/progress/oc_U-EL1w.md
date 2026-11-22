## NEXT
DONE

# UNIT U-EL1w — L1w ranged vertex-buffer binds (Minecraft.Windows.exe 1.26.62.01)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe. RVAs relative to image base. Disassembly taken with rdis `dis 0x<rva> n`.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.
Scope: closes the pending part of checklist item L1w (RENDER_CHECKLIST.md:232): "only the RTX skinning range check (0xe83f1d0) found (6ei); setter API not isolated". The RTX skinning range check (0xe83f1d0) was already found in BGFX_MAP.md 6ei and is re-proven here [V]; the setter API (0xe81b4d0 setVertexBuffers) is isolated and proven [V] below. No raw listing dumps are pasted — every proof line is quoted verbatim inside a table row.

## (1) RTX skinning range check — 0xe83f1d0 (slot 63 of RTX vtable 0xF4EEE80; found in 6ei; re-proven [V])

The function iterates skinning jobs and, per job, validates that the vertex-buffer bind range (start + count*stride) does not overrun the buffer, raising "Our skinning vertex buffer is asking for a range that will extend past the end of the buffer." on violation.

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| skinning job count u16 | [rbx+0x4] | 2 | [rbx+0x4] | `0xe83fb93  movzx eax,word ptr [rbx+4]` | job record count u16; count*stride builds half of the bind-range end test | [V] |
| skinning vertex-buffer stride u16 | [rsi+0x14] | 2 | [rsi+0x14] | `0xe83fb97  imul eax,[rsi+0x14]` | stride u16 of the skinning vertex buffer; count*stride = range size in bytes | [V] |
| range start offset u32 | [rsi+0x4] | 4 | [rsi+0x4] | `0xe83fb9b  mov ecx,[rsi+4]` | range start offset u32; added to count*stride at 0xe83fb9e | [V] |
| range end vs skinning VB size | [r15+0x60] | 4 | [r15+0x60] | `0xe83fb9e  add ecx,eax` / `0xe83fba0  cmp ecx,[r15+0x60]` / `0xe83fba4  ja short 0xE83FBAE` | start+count*stride vs buffer size u32 at +0x60 of the buffer object; ja (above) = range violation path | [V] |
| range part vs second bound | [rsi+0xC] / [rdi+0x60] | 4 | [rsi+0xC] and [rdi+0x60] | `0xe83fba6  add eax,[rsi+0xC]` / `0xe83fba9  cmp eax,[rdi+0x60]` / `0xe83fbac  jbe short 0xE83FBBD` | count*stride + [rsi+0xC] vs [rdi+0x60]; jbe = in range | [V] |
| range-violation error string | 0xe83fbb0 (lea to data_f7f9f9d) | n/a | lea rdx,[0xF7F9F9D] | `0xe83fbb0  lea rdx,[0xF7F9F9D]` / `0xe83fbb7  call 0xBC5F110` | "Our skinning vertex buffer is asking for a range that will extend past the end of the buffer." raised via 0xBC5F110 when offset+size overruns the buffer | [V] |

## (2) Setter API isolated — setVertexBuffers at 0xe81b4d0 (Sigs.json: `setVertexBuffers`)

The pending part ("setter API not isolated") is now isolated: `setVertexBuffers(ctx rcx, out rdx, draw r8, outNumVertices r9)` [V], called from the draw executor 0xe821120. Per draw stream it builds a D3D12 vertex buffer view with an explicit range: BufferLocation = VB-record m_gpuVA (+0x58) + startVertex*stride (bind offset), SizeInBytes = m_size (+0x60) − startVertex*stride (bind range size). Stream record = {u32 startVertex +0x0, u16 handle +0x4, u16 layout +0x6} at draw+0x4+idx*8; streamMask byte at draw+0x63; draw numVertices u32 at draw+0x4C.

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| draw stream handle u16 | [rdi+r12*8+4] (stream+0x4) | 2 | [rdi+r12*8+4] | `0xe81b54c  movzx r13d,word ptr [rdi+r12*8+4]` | per-stream vertex buffer handle u16; handle*0x80 indexes the ctx+0x9B2178 vertex-buffer record table (0x80 stride) | [V] |
| draw stream startVertex u32 | stream+0x0 ([rdx]) | 4 | [rdx] (rdx = stream ptr = draw+0x4+idx*8) | `0xe81b689  mov r11d,[rdx]` | per-stream startVertex u32; startVertex*stride = the bind byte offset | [V] |
| vertex-layout stride u16 | ctx+0xC9619C+layout*0x54 | 2 | [rax+rsi+0xC9619C] | `0xe81b67c  movzx r8d,word ptr [rax+rsi+0xC9619C]` | layout stride u16 from the layout record (ctx+0xC96198 + layout*0x54, stride field at +4 = +0xC9619C); stride of the ranged bind | [V] |
| VBV BufferLocation (bind base+offset) | VB record +0x58 (m_gpuVA) | 8 | [rcx+0x58] → store [rbx+r10] | `0xe81b690  add r11,[rcx+0x58]` / `0xe81b698  mov [rbx+r10],r11` | BufferLocation qword = m_gpuVA at VB record +0x58 + startVertex*stride → ranged bind base+offset; 8-byte store into the out vertex buffer view | [V] |
| VBV SizeInBytes (bind range size) | VB record +0x60 (m_size) | 4 | [rcx+0x60] → store [rbx+r10+8] | `0xe81b6a9  mov eax,[rcx+0x60]` / `0xe81b6ae  imul edx,r8d` / `0xe81b6b2  sub eax,edx` / `0xe81b6b4  mov [rbx+r10+8],eax` | SizeInBytes dword = m_size at VB record +0x60 − startVertex*stride → the bind range size; 4-byte store into the out view +8 | [V] |
| draw numVertices u32 | draw+0x4C | 4 | [r8+0x4C] → [r9+0x0] | `0xe81b4f4  mov eax,[r8+0x4C]` / `0xe81b4f8  mov [r9],eax` | draw numVertices u32 at +0x4C copied to *outNumVertices; per-stream vertex count bounded by vb.m_size/stride | [V] |

CLOSES?: YES — every pending part of L1w is now [V]-proven in this doc:
- range check: 0xe83f1d0 validates offset+count*stride against the buffer size ([r15+0x60]) with the error string at 0xe83fbb0 "Our skinning vertex buffer is asking for a range that will extend past the end of the buffer." (call 0xBC5F110 at 0xe83fbb7).
- setter API: setVertexBuffers (0xe81b4d0) sets ranged vertex-buffer binds per draw stream — BufferLocation = VB-record+0x58 qword + startVertex*stride (offset), SizeInBytes = VB-record+0x60 − startVertex*stride (range size).
Caveat: this is the render-thread D3D12 applier called from executor 0xe821120; no distinct encoder-side setVertexBuffer/setInstanceDataBuffer function exists in the exe (encoder setters are inlined stores per L1h/6h; Sigs.json names only setVertexBuffers).

## TOOL REQUESTS
None
