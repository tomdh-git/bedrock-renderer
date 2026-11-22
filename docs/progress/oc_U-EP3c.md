## NEXT
DONE header-to-record mapping proven on disk with verbatim disassembly rows; new header src/sdk/mc/deps/bgfx/DrawRecord.h; layout_asserts.json constants added. CLOSES? = NO below: M3e still needs an in-game test this static-only unit cannot run.

# U-EP3c — P3c Edit draws at submit: read/modify every draw record before the GPU (refs M3e)

Item text (docs/RENDER_CHECKLIST.md line 548): "P3c Edit draws at submit: read/modify every draw record before the GPU — M3e".
M3e text (line 457): "Edit draws at submit: read/modify every draw record before the GPU (flush 0xe81b720 records 6ej; needs the header-to-record mapping and an in-game test)".

## 1. What changed (paths)

- docs/progress/oc_U-EP3c.md — this note: full header-to-record mapping table with verbatim disassembly proof lines ([V] rows), seam RVAs, and the CLOSES? line.
- src/sdk/mc/deps/bgfx/DrawRecord.h — NEW header: typed DrawRecordNonIndexed (0x70 bytes) and DrawRecordIndexed (0x88 bytes), DrawBatcher fields (+0x10 pending[], +0x18 records[], +0x10C0 vbCache, +0x1110 ibCache, +0x1120/+0x1128 last CBVs, +0x115C capacity, +0x1164 indirectEnabled), all seam RVAs, with static_asserts on every layout offset.
- docs/data/layout_asserts.json — added constants to the D3D12Context::drawExecutor entry (0x40/0x44/0x48/0x54/0x5C/0x76/0x78 header and record field offsets) and to the D3D12Context::drawFlush entry (0x10 pending[], 0x18 records[], 0x88 indexed record stride). Every added value was verified as an immediate/displacement in the function body before adding it.

## 2. Basis (sections and dossiers read)

- docs/BGFX_MAP.md 6e-2: draw header fields read by executor 0xe821120; 6ej: drawFlush record layouts and consumption; 8a: replacement seams (submit 0xe82e230 slot 50, per-draw veto/rewrite at flush 0xe81b720).
- docs/functions/e81b720.md (D2 drawFlush dossier), docs/functions/e821120.md (D2 draw executor dossier), docs/functions/bc60740.md (D2 Encoder::submit dossier).
- Fresh rdis disassembly (verbatim lines quoted below): executor append build 0xe82c40f..0xe82cd2f, drawFlush 0xe81b720, fillVertexBufferViews 0xe81b4d0, submit header copy 0xbc60ab2..0xbc60b13.

## 3. Header-to-record mapping

Rule: one row per distinct offset, all read/store sites listed in the site column, one verbatim `0xRVA  instr` proof line per row (quoted inside the cell so verify_oc checks it). Offset keys: H = draw header field at Frame+0xB4700 + idx*0x80, R = DrawBatcher record field, B = DrawBatcher field.

| offset | size | site (read -> store) | verbatim `0xRVA  instr` | meaning | tag |
| H+0x00..0x7F | 16 | W Frame+0xB4700+idx<<7: 0xbc60ac0, siblings 0xbc60acc/0xbc60ad8/0xbc60ae4/0xbc60b13 (load side 0xbc60abc/0xbc60ac8/0xbc60ad4/0xbc60aec) | `0xbc60ac0  movaps [rax+rcx+0xB4770],xmm0` | Encoder::submit (0xbc60740) copies the whole 0x80 RenderDraw header verbatim from Encoder::m_draw; idx = CAS loop on Frame+0xDC57E8 (cap 0xFFFE) at 0xbc607bf..0xbc607fd | [V] |
| H+0x34 | 4 | R 0xe82c40f ([r12+0x34]) -> W job+0x330 at 0xe82c414 | `0xe82c40f  mov eax,[r12+0x34]` | uniformBegin copied to a job local; drives the constant-upload range, not a record field | [V] |
| H+0x38 | 4 | R 0xe82c41a ([r12+0x38]) -> W job+0x21C at 0xe82c41f | `0xe82c41a  mov eax,[r12+0x38]` | uniformEnd -> job local | [V] |
| H+0x3C | 4 | R 0xe82c425 ([r12+0x3C]) -> W job+0x32C at 0xe82c42a | `0xe82c425  mov eax,[r12+0x3C]` | startMatrix -> job local | [V] |
| H+0x40 | 4 | R 0xe82cd21 ([rcx+0x40]) -> W R+0x78 at 0xe82cd24 | `0xe82cd21  mov eax,[rcx+0x40]` | indexed record StartIndexLocation = header startIndex | [V] |
| H+0x44 | 4 | R 0xe82caf2 ([r12+0x44]) -> W R+0x70 at 0xe82cd11 | `0xe82caf2  mov esi,[r12+0x44]` | indexed record IndexCountPerInstance = header numIndices; if 0xFFFFFFFF it is ib.size/indexStride (0xe82cafc..0xe82cb06) | [V] |
| H+0x48 | 4 | R 0xe82cb5e ([r12+0x48]) -> W R+0x5C at 0xe82cb73 | `0xe82cb5e  cmp dword ptr [r12+0x48],2` | indexed record IBV.Format: stride 2 -> 0x39 DXGI_FORMAT_R16_UINT (0xe82cb69), else 0x2A R32_UINT (0xe82cb64, cmove at 0xe82cb6f) | [V] |
| H+0x54 | 4 | R 0xe82cd1b ([rcx+0x54]) -> W R+0x74 at 0xe82cd1e; R 0xe82cdd8 ([rax+0x54]) -> W R+0x64 at 0xe82cddb | `0xe82cd1b  mov eax,[rcx+0x54]` | InstanceCount = header numInstances in both record kinds (indexed R+0x74, non-indexed R+0x64) | [V] |
| H+0x4C | 4 | R 0xe81b4f4 ([r8+0x4C]) -> W tmp+0 (job+0xC0) at 0xe81b4f8; R job+0xC0 at 0xe82cdde -> W R+0x60 at 0xe82cde4 | `0xe81b4f4  mov eax,[r8+0x4C]` | non-indexed record VertexCountPerInstance = header numVertices; fillVertexBufferViews (0xe81b4d0) stores numVertices to its tmp out-param (job+0xC0 via 0xe82c6e8 lea r9,[rbx+0xC0]) | [V] |
| H+0x63 | 1 | R 0xe81b4fb ([r8+0x63]) | `0xe81b4fb  movzx ebp,byte ptr [r8+0x63]` | streamMask drives the per-stream VBV loop in fillVertexBufferViews | [V] |
| H+s*8 (s<4) | 4/2/2 | R by fillVertexBufferViews -> W R+0x00..0x4F (5 VBVs, n<<4 stride) | `0xe82ccc8  mov [rdi+rax],rcx` | header stream {startVertex u32 +0, vbHandle u16 +4, layout u16 +6} at +0+s*8 -> record VBVs; VBV fields built from vertex-buffer record at ctx+0x9B2178+handle*0x80: +0x50 `0xe82ccbb  mov ecx,[rdx+0x50]`, +0x54 `0xe82ccd8  imul ecx,[rdx+0x54]`, +0x58 `0xe82cccc  movzx ecx,word ptr [rdx+0x58]` | [V] |
| H+0x74 | 2 | R 0xe82c5b8 ([r12+0x74]) -> index record at ctx+0x93A178+handle*0x78; W R+0x50 at 0xe82cb52, W R+0x58 at 0xe82cb5a | `0xe82c5b8  movzx r13d,word ptr [r12+0x74]` | indexed record IBV.BufferLocation = index-buffer-record gpuVA (+0x58), IBV.SizeInBytes = size (+0x60): `0xe82cb4e  mov r8,[rcx+0x58] -> 0xe82cb52  mov [rdx+rax+0x50],r8`; handle 0xFFFF = non-indexed | [V] |
| H+0x76 | 2 | R 0xe82cb9b ([rax+0x76], indexed) / 0xe82c6fc ([r11+0x76], non-indexed) | `0xe82cb9b  movzx ecx,word ptr [rax+0x76]` | instanceDataBuffer handle; when != 0xFFFF an extra instance VBV {VA+offset, stride*count, stride} is appended after the stream VBVs | [V] |
| H+0x78 | 2 | R 0xe82c430 ([r12+0x78]) | `0xe82c430  cmp word ptr [r12+0x78],0xFFFF` | indirectBuffer handle; 0xFFFF -> batched direct draws, != 0xFFFF -> ExecuteIndirect path (constants still bound directly to root CBVs #2/#3 at 0xe82c450/0xe82c478) | [V] |
| B+0x10 | 4 | R 0xe81b736 ([rcx+r12*4+0x10]) -> W same at 0xe81b74a (zeroed after consume) | `0xe81b736  mov esi,[rcx+r12*4+0x10]` | DrawBatcher pending[kind] count; kind 0 = non-indexed, kind 1 = indexed | [V] |
| B+0x18 | 8 | R 0xe81b79e ([rdi+r12*8+0x18]) | `0xe81b79e  mov r15,[rdi+r12*8+0x18]` | DrawBatcher records[kind] array base | [V] |
| R+0x50 | 8 | R 0xe81ba07 ([r15+0x50]) -> slot 38 SetGraphicsRootConstantBufferView(2); also indexed IBV address at 0xe81b84f/0xe81b856 | `0xe81ba07  mov r8,[r15+0x50]` | non-indexed: vsConstantsVA bound as root CBV #2; indexed: record+0x50 passed to IASetIndexBuffer (IBV {gpuVA qword +0x50, size dword +0x58, format dword +0x5C}) | [V] |
| R+0x58 | 8 | R 0xe81ba24 ([r15+0x58]) -> slot 38 SetGraphicsRootConstantBufferView(3) | `0xe81ba24  mov r8,[r15+0x58]` | non-indexed: fsConstantsVA bound as root CBV #3 | [V] |
| R+0x60 | 4 | R 0xe81ba78 ([r15+0x60]) -> DrawInstanced slot 12 at 0xe81ba74 | `0xe81ba78  mov edx,[r15+0x60]` | non-indexed draw args: VertexCount=R+0x60, InstanceCount=R+0x64, StartVertex=R+0x68, StartInstance=R+0x6C (`0xe81ba7c  mov r8d,[r15+0x64]`, `0xe81ba80  mov r9d,[r15+0x68]`, `0xe81ba84  mov r10d,[r15+0x6C]`); stride 0x70 (`0xe81ba9f  add r15,0x70`) | [V] |
| R+0x70 | 4 | R 0xe81b86a ([r15+0x70]) -> DrawIndexedInstanced slot 13 at 0xe81b866 | `0xe81b86a  mov edx,[r15+0x70]` | indexed draw args: IndexCount=R+0x70, InstanceCount=R+0x74, StartIndex=R+0x78, BaseVertex=R+0x7C, StartInstance=R+0x80 (`0xe81b86e  mov r8d,[r15+0x74]`, `0xe81b872  mov r9d,[r15+0x78]`, `0xe81b876  mov r10d,[r15+0x7C]`, `0xe81b87a  mov r11d,[r15+0x80]`); stride 0x88 (`0xe81b8e2  add r15,0x88`) | [V] |

## 4. Where the "edit draws at submit" seam goes

- Submit takeover: RendererContextD3D12::submit slot 50 = 0xe82e230 (live RTX override 0xe83d440 on vtable 0xF4EEE80). A replacement submit walks Frame+0xB4700 headers (count Frame+0xDC57E8, cap 0xFFFE) and can read/modify every header before the executor (0xe821120) turns it into records.
- Per-draw veto/rewrite at the flush: hook D3D12Context::drawFlush 0xe81b720 (the executor calls it at 0xe822e4e, 0xe822e6b, 0xe82cfc1, 0xe82cfde, 0xe82d0f6, 0xe82d12b, 0xe82d148). Set pending[kind] = 0 at batcher+0x10+kind*4 to skip a whole batch, or edit record fields in place (stride 0x70/0x88) before the GPU draw; record fields above are the editable surface (start index, index count, instances, VBV views, CBV addresses).
- Nothing is registered or patched here: this unit documents the seam and proves the mapping; HookManager.cpp and existing registrations are untouched per unit rules.

## 5. Blocking fact

CLOSES? NO — the header-to-record mapping half of M3e is proven on disk by the [V] rows above, but M3e's own wording also requires "an in-game test" (build the DLL, launch the game, hook submit/flush, prove every edited draw record reaches the GPU). That single fact is the blocker: this unit is static-only, the game is closed, and builds/launch/attach are forbidden, so the in-game test cannot be executed here. It stays open for the in-game phase.

## TOOL REQUESTS

None (existing rdis/dossier tooling only; no throwaway scripts written).
