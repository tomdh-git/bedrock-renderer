## NEXT
DONE

UNIT U-EM3e — M3e Edit draws at submit: read/modify every draw record before the GPU (flush 0xe81b720 records 6ej; needs the header-to-record mapping and an in-game test)
OUTPUT FILE: docs/progress/oc_U-EM3e.md (only)
CONSTRAINTS: static analysis only; game closed; no builds; no edits to HookManager.cpp, CMake, Sigs.json, CLAUDE.md, BGFX_MAP.md, RENDER_CHECKLIST.md; new files only under docs/, tools/, src/sdk/, src/client/features/render/.
GAME: Minecraft.Windows.exe 1.26.62.01 (RVAs relative to image base). All RVAs here are for that build.

## (1) What changed

Created:
- docs/progress/oc_U-EM3e.md — this file (proof table, header-to-record mapping, in-game test plan, CLOSES?).
- src/client/features/render/draw/D3D12DrawRecord.h — DrawBatcher + DrawRecordNonIndexed + DrawRecordIndexed structs, every offset tied to a verbatim disassembly line, static_asserts for strides and field offsets.
- src/client/features/render/draw/D3D12DrawEditor.h — DrawEditor class: hooks flush 0xe81b720 at the 7 executor call sites, iterates pending records of a kind, applies a DrawEditFn callback per record (callback returns false → veto the draw), exposes vetoLargeDraws / rebaseInstances helpers. Header-only, no CMake change, registers nothing.

Already existed (not created by this unit, referenced for context):
- src/client/features/render/draw/D3D12DrawFlushWrap.h — declares kJobBatcher=0x250, kJobWrapper=0x90, kWrapperCommandList=0x30, strides 0x70/0x88, PSO key mask, batch-merge test, batcher cache structs, StreamDraw/StreamFlush, DrawFlushRecorder. References oc_U-EQ4b.md for verbatim proof.

Not edited: HookManager.cpp, any hook registration, CMake, Sigs.json, CLAUDE.md, BGFX_MAP.md, RENDER_CHECKLIST.md.

## (2) Proof table (one row per distinct offset; all sites of that offset listed)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning (only if the instruction/string shows it) | tag |
|---|---|---|---|---|---|
| DrawBatcher +0x10+kind*4 | 4 | [rcx+kind*4+0x10] | `0xe81b736  mov esi,[rcx+r12*4+0x10]` `0xe81b74a  mov dword ptr [rcx+r12*4+0x10],0` | pending[kind] draw-count load (kind in r12d=r9d), then cleared after snapshot | [V] |
| DrawBatcher +0x115C | 4 | [rcx+0x115C] | `0xe81b753  cmp [rcx+0x115C],esi` | capacity: n >= cap → overflow path | [V] |
| DrawBatcher +0x1148+kind*4 | 4 | [rdi+kind*4+0x1148] | `0xe81b78f  inc dword ptr [rdi+r12*4+0x1148]` | statDirect[kind]++ when n < cap | [V] |
| DrawBatcher +0x1150+kind*4 | 4 | [rdi+kind*4+0x1150] | `0xe81b75b  inc dword ptr [rdi+r12*4+0x1150]` | statOverflow[kind]++ when n >= cap | [V] |
| DrawBatcher +0x1164 | 1 | [rdi+0x1164] | `0xe81b76c  cmp byte ptr [rdi+0x1164],0` | indirectEnabled flag (0 = direct draws, 1 = ExecuteIndirect batch) | [V] |
| DrawBatcher +0x18+kind*8 | 8 | [rdi+kind*8+0x18] | `0xe81b779  mov rax,[rdi+r12*8+0x18]` | records[kind] pointer load | [V] |
| DrawBatcher +0x10C0 | 0x50 | [rdi+0x10C0] | `0xe81b797  lea r14,[rdi+0x10C0]` | vbCache: last 5 vertex buffer views (0x50 bytes), memcmp'd against each record | [V] |
| DrawBatcher +0x1110 | 0x10 | [rdi+0x1110] | `0xe81b7ac  lea r12,[rdi+0x1110]` | ibCache: last index buffer view (0x10 bytes) | [V] |
| DrawBatcher +0x1120 | 8 | [rdi+0x1120] | `0xe81bae3  mov rcx,[rdi+0x1120]` `0xe81b912  mov [rdi+0x1120],rax` | lastCbv[0] root CBV cache (root param 2): read to compare, written from record+0x60 (indexed path) | [V] |
| DrawBatcher +0x1128 | 8 | [rdi+0x1128] | `0xe81bb0a  mov rax,[r15+0x58]` `0xe81bb0e  mov [rdi+0x1128],rax` `0xe81b91d  mov [rdi+0x1128],rax` | lastCbv[1] root CBV cache (root param 3): non-indexed path read+write from rec+0x58; indexed path write from rec+0x68 | [V] |
| DrawRecordNonIndexed +0x00..0x4F | 0x50 | [r15+0x00..0x4F] | `0xe81ba3d  mov r8d,0x50` `0xe81ba46  mov rdx,r15` `0xe81ba49  call 0xEBCE390` | VBV block: 5 vertex buffer views (5×16B), memcmp'd vs vbCache; if equal, IASetVertexBuffers deduped | [V] |
| DrawRecordNonIndexed +0x50 | 8 | [r15+0x50] | `0xe81bb19  mov r8,[r15+0x50]` `0xe81bb2c  call qword ptr [0xF99FFA0]` | cbv0 → SetGraphicsRootConstantBufferView(cl, slot 2, cbv0) | [V] |
| DrawRecordNonIndexed +0x58 | 8 | [r15+0x58] | `0xe81bb36  mov r8,[r15+0x58]` `0xe81bb49  call qword ptr [0xF99FFA0]` | cbv1 → SetGraphicsRootConstantBufferView(cl, slot 3, cbv1) | [V] |
| DrawRecordNonIndexed +0x60 | 4 | [r15+0x60] | `0xe81babc  mov edx,[r15+0x60]` | vertexCount → DrawInstanced arg 1 | [V] |
| DrawRecordNonIndexed +0x64 | 4 | [r15+0x64] | `0xe81bac0  mov r8d,[r15+0x64]` | instanceCount → DrawInstanced arg 2 | [V] |
| DrawRecordNonIndexed +0x68 | 4 | [r15+0x68] | `0xe81bab8  mov r9d,[r15+0x68]` | startVertex → DrawInstanced arg 3 | [V] |
| DrawRecordNonIndexed +0x6C | 4 | [r15+0x6C] | `0xe81bab4  mov r10d,[r15+0x6C]` `0xe81bacb  mov [rsp+0x20],r10d` | startInstance → DrawInstanced arg 4 (stack slot) | [V] |
| DrawRecordIndexed +0x00..0x0F | 0x10 | [r15+0x00..0x0F] | `-` | IBV (index buffer view), set via IASetIndexBuffer at record+0x50 below | [I] |
| DrawRecordIndexed +0x10..0x5F | 0x50 | [r15+0x10..0x5F] | `-` | VBV block: 5 vertex buffer views | [I] |
| DrawRecordIndexed +0x50 | 0x10 | [r15+0x50] | `0xe81b9a3  lea r13,[r15+0x50]` `0xe81b9d8  mov rax,[rax+0x158]` `0xe81b9df  mov rdx,r13` `0xe81b9e2  call qword ptr [0xF99FFA0]` | IBV → IASetIndexBuffer(cl, record+0x50) (slot 43) | [V] |
| DrawRecordIndexed +0x60 | 8 | [r15+0x60] | `0xe81b8f9  mov rax,[r15+0x60]` `0xe81b928  mov r8,[r15+0x60]` `0xe81b93b  call qword ptr [0xF99FFA0]` | cbv0 → SetGraphicsRootConstantBufferView(cl, slot 2, cbv0) | [V] |
| DrawRecordIndexed +0x68 | 8 | [r15+0x68] | `0xe81b919  mov rax,[r15+0x68]` `0xe81b945  mov r8,[r15+0x68]` `0xe81b958  call qword ptr [0xF99FFA0]` | cbv1 → SetGraphicsRootConstantBufferView(cl, slot 3, cbv1) | [V] |
| DrawRecordIndexed +0x70 | 4 | [r15+0x70] | `0xe81b8c3  mov edx,[r15+0x70]` | indexCount → DrawIndexedInstanced arg 1 | [V] |
| DrawRecordIndexed +0x74 | 4 | [r15+0x74] | `0xe81b8c7  mov r8d,[r15+0x74]` | instanceCount → DrawIndexedInstanced arg 2 | [V] |
| DrawRecordIndexed +0x78 | 4 | [r15+0x78] | `0xe81b8bf  mov r9d,[r15+0x78]` | startIndex → DrawIndexedInstanced arg 3 | [V] |
| DrawRecordIndexed +0x7C | 4 | [r15+0x7C] | `0xe81b8bb  mov r11d,[r15+0x7C]` `0xe81b8d7  mov [rsp+0x20],r11d` | baseVertex → DrawIndexedInstanced arg 4 (stack slot) | [V] |
| DrawRecordIndexed +0x80 | 4 | [r15+0x80] | `0xe81b8b4  mov r10d,[r15+0x80]` `0xe81b8d2  mov [rsp+0x28],r10d` | startInstance → DrawIndexedInstanced arg 5 (stack slot) | [V] |
| non-indexed stride | - | - | `0xe81ba9f  add r15,0x70` | record pointer advances by 0x70 per non-indexed record | [V] |
| indexed stride | - | - | `0xe81b89d  add r15,0x88` | record pointer advances by 0x88 per indexed record | [V] |
| cmdlist object | 8 | [rbx+0x30] | `0xe81b7c9  mov rcx,[rbx+0x30]` `0xe81bac4  mov rax,[rcx]` `0xe81b8cb  mov rax,[rcx]` | [JobContext+0x30] = ID3D12GraphicsCommandList*; vtable slot +0x60 DrawInstanced, +0x68 DrawIndexedInstanced, +0x158 IASetIndexBuffer, +0x160 IASetVertexBuffers, +0x130 SetGraphicsRootConstantBufferView, +0x1D8 ExecuteIndirect | [V] |
| DrawBatcher kind arg | 4 (reg) | - | `0xe81b733  mov r12d,r9d` `0xe82cfbe  xor r9d,r9d` `0xe82cfd8  mov r9d,1` | kind = r9d: 0 = non-indexed (DrawInstanced, stride 0x70), 1 = indexed (DrawIndexedInstanced, stride 0x88) | [V] |
| executor → batcher | 8 | [rbx+0x250] | `0xe821774  mov [rbx+0x250],r8` `0xe822e3a  mov rcx,[rbx+0x250]` `0xe82cfad  mov rcx,[rbx+0x250]` | executor stores DrawBatcher* at job state +0x250; flush reads it back | [V] |
| executor → renderer | 8 | [[rbx+0xB0]+0x238] | `0xe82cfa6  mov rsi,[rax+0x238]` (rax = [rbx+0xB0]) | renderer pointer passed as flush rdx (never dereferenced by flush) | [V] |
| executor → JobContext | 8 | [rbx+0x90] | `0xe82cfb7  mov r8,[rbx+0x90]` | JobContext* passed as flush r8; [job+0x30] = command list | [V] |
| executor flush sites kind 0 | - | - | `0xe82cfc1  call 0xE81B720` `0xe822e4e  call 0xE81B720` | executor → flush call sites, kind 0 (non-indexed); args: rcx=batcher [rbx+0x250], rdx=renderer [[rbx+0xB0]+0x238], r8=job [rbx+0x90], r9d=0 | [V] |
| executor flush sites kind 1 | - | - | `0xe82cfde  call 0xE81B720` `0xe822e6b  call 0xE81B720` | executor → flush call sites, kind 1 (indexed); same args, r9d=1 | [V] |
| indirect ExecuteIndirect | 8 | [rax+0x1D8] | `0xe81beed  mov rax,[rax+0x1D8]` | cmdlist vtable slot 59 = ExecuteIndirect, indirect batch path | [V] |
| DrawIndexedInstanced | 8 | [rax+0x68] | `0xe81b866  mov rax,[rax+0x68]` | cmdlist vtable slot 13 = DrawIndexedInstanced | [V] |
| DrawInstanced | 8 | [rax+0x60] | `0xe81bac7  mov rax,[rax+0x60]` | cmdlist vtable slot 12 = DrawInstanced | [V] |
| submit draw index CAS | 4 | [rcx+0xDC57E8] | `0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d` | Frame+0xDC57E8: CAS-increment allocates draw index | [V] |
| submit draw count load | 4 | [rcx+0xDC57E8] | `0xbc607c2  mov eax,[rcx+0xDC57E8]` | Frame+0xDC57E8 draw/item count load | [V] |
| submit header copy | 16 | [rax+rcx+0xB4700] | `0xbc60b13  movaps [rax+rcx+0xB4700],xmm0` | last of 8 movaps copying the 0x80 draw header (encoder+0x40..0xBF) → Frame+0xB4700+idx*0x80 | [V] |
| submit RenderBind stride | - | imm 0x540 | `0xbc60b33  imul rcx,r14,0x540` | RenderDraw record stride: idx*0x540 → Frame+0x8B4700+idx*0x540 | [V] |
| submit RenderBind copy | - | - | `0xbc60b41  mov r8d,0x518` `0xbc60b4a  call 0xEEC6EC0` | memcpy 0x518 bytes (RenderBind 0x514 + bind hash) → Frame+0x8B4700+idx*0x540 | [V] |
| executor header+0x63 read | 1 | [r12+0x63] | `0xe822b92  movzx r13d,byte ptr [r12+0x63]` | executor reads header bind-slot bitmask byte at header+0x63 during record build | [V] |
| executor header+0x76 read | 2 | [r12+0x76] | `0xe822ba8  movzx eax,word ptr [r12+0x76]` | executor reads header VB handle at header+0x76 during record build | [V] |
| executor header+0x50 read | 4 | [r12+0x50] | `0xe822bb5  mov eax,[r12+0x50]` | executor reads header VB byte offset at header+0x50 during record build | [V] |
| executor header+0x58 read | 2 | [r12+0x58] | `0xe822bc0  movzx eax,word ptr [r12+0x58]` | executor reads header VB stride at header+0x58 during record build | [V] |

## (3) Header-to-record mapping (the pending part of the item line)

The draw header (0x80 bytes at Frame+0xB4700+idx*0x80, written by submit 0xbc60740 via 8 movaps, last at `0xbc60b13 movaps [rax+rcx+0xB4700],xmm0`) carries per-draw fields. The flush reads draw records (0x70 non-indexed / 0x88 indexed) from the DrawBatcher. The executor (0xe821120) reads header fields during record construction — verified verbatim:

- header+0x50 (VB byte offset) read at `0xe822bb5  mov eax,[r12+0x50]`
- header+0x58 (VB stride u16) read at `0xe822bc0  movzx eax,word ptr [r12+0x58]`
- header+0x63 (bind-slot bitmask byte) read at `0xe822b92  movzx r13d,byte ptr [r12+0x63]`
- header+0x76 (VB handle u16) read at `0xe822ba8  movzx eax,word ptr [r12+0x76]`

From field semantics (header field → flush record field), the inferred mapping is:

| header offset | meaning | → record offset (non-indexed 0x70) | → record offset (indexed 0x88) | tag |
|---|---|---|---|---|
| +0x40 | start index | startVertex +0x68 (byte offset / stride) | startIndex +0x78 | [I] |
| +0x44 | index count (0xFFFFFFFF = computed) | - | indexCount +0x70 | [I] |
| +0x48 | index stride (2/4) | - | DXGI format select (IBV) | [I] |
| +0x4C | vertex count | vertexCount +0x60 | - | [I] |
| +0x50 | VB byte offset | startVertex +0x68 (offset/stride) | baseVertex +0x7C (via VBV) | [I] |
| +0x54 | VB count | instanceCount +0x64 | instanceCount +0x74 | [I] |
| +0x58 | VB stride (u16) | VBV stride field | VBV stride field | [I] |
| +0x5A | IB handle (<<5) | - | IBV buffer location | [I] |
| +0x76 | VB handle (<<7) | VBV buffer location | VBV buffer location | [I] |
| +0x1F | marker byte (encoder+0x5F = header+0x1F) | - | - | [I] |

The exact store path from header field to record field (which executor instruction writes which header field into which record offset) is not fully traced statically — the executor accumulates per-item state across multiple loop iterations before the flush, and the record is written to the batcher's record array before `0xe81b720` is called. This is the header-to-record mapping gap: [I] inferred from field semantics, not [V] proven by a store instruction.

## (4) Source changes recap

`src/client/features/render/draw/D3D12DrawRecord.h`:
- `DrawBatcher`: pending[2] at +0x10 (4B each), records[2] at +0x18 (8B pointers each), vbCache at +0x10C0 (0x50B), ibCache at +0x1110 (0x10B), lastCbv[2] at +0x1120/+0x1128, statDirect at +0x1148, statOverflow at +0x1150, capacity at +0x115C, indirectEnabled at +0x1164. `static_assert(sizeof(DrawBatcher) > 0x1165)`.
- `DrawRecordNonIndexed` (0x70 bytes): vbv[0..4] at +0x00..0x4F, cbv0 +0x50, cbv1 +0x58, vertexCount +0x60, instanceCount +0x64, startVertex +0x68, startInstance +0x6C. `static_assert(sizeof(...) == 0x70)`.
- `DrawRecordIndexed` (0x88 bytes): ibv at +0x00..0x0F, vbv[0..4] at +0x10..0x5F, cbv0 +0x60, cbv1 +0x68, indexCount +0x70, instanceCount +0x74, startIndex +0x78, baseVertex +0x7C, startInstance +0x80. `static_assert(sizeof(...) == 0x88)`.

`src/client/features/render/draw/D3D12DrawEditor.h`:
- `DrawEditor`: wraps flush 0xe81b720; `edit(kind, fn)` reads pending=[batcher+0x10+kind*4], records=[batcher+0x18+kind*8], iterates stride (0x70/0x88), calls `DrawEditFn(record)` per record; returns false from fn vetoes the draw (flush skips it by virtue of the record being modified / skipped via the caller's batcher state). `vetoLargeDraws(maxIndexCount)` and `rebaseInstances(instanceDelta)` helpers.

## (5) TOOL REQUESTS

In-game test plan (executed by the orchestrator; this unit does not touch the game):

1. Enter a populated singleplayer world (Vibrant Visuals ON) so draws are being flushed every frame.
2. Poll the DrawBatcher at renderer+0x250 between frames. Read pending[0] and pending[1] (u32 at +0x10 and +0x14), confirming they are non-zero and stable across frames.
3. Read the first record of each kind at records[0] = [batcher+0x18] and records[1] = [batcher+0x20]:
   - Non-indexed: vertexCount (+0x60), instanceCount (+0x64), startVertex (+0x68), startInstance (+0x6C), cbv0 (+0x50), cbv1 (+0x58).
   - Indexed: indexCount (+0x70), instanceCount (+0x74), startIndex (+0x78), baseVertex (+0x7C), startInstance (+0x80), cbv0 (+0x60), cbv1 (+0x68).
4. Hook flush 0xe81b720 (or use the DrawEditor at the 7 executor call sites). On a chosen frame, veto one batch by setting pending[kind] = 0 before the flush runs. Expected: exactly one draw category disappears from the frame (framebudget draw count drops by pending[kind]); no crash; subsequent frames recover (pending re-accumulates).
5. On another frame, instead of vetoing, modify startInstance (+0x6C non-indexed / +0x80 indexed) of the first record by +1. Expected: the corresponding draw targets the next instance/actor (per M3d, startInstance & 0xFF = roster slot → actor), so a different actor/instance is drawn at that draw slot.
6. Read back via the DrawFlushRecorder stream (kind, pending, cbv0/cbv1, vbvDirty, ibvDirty, per-draw StreamDraw) and diff against the unhooked baseline. Expected: vetoed flush shows pending=0 with zero draws; modified-flush shows the patched startInstance value in the stream.

Capture to queue (function-entry RVA only):
- `python tools/livecap/request.py add em3e_flush_verify 0xe81b720 --size 0x200 --max 8 --why "U-EM3e: capture DrawBatcher rcx, records pointer, pending counts and first record fields at flush entry to verify header-to-record mapping in game"`

This captures RCX (DrawBatcher*), RDX (renderer), R8 (JobContext), R9D (kind) and the 0x200 bytes pointed to by RCX (batcher: pending counts, records pointers, caches), plus the records pointed to by [RCX+kind*8+0x18]. Use it to confirm record fields match the header fields from the same frame's submit.

Existing live data check: docs/data/live/README.md read; _status.txt shows DONE with 0 pending hits (u_el17h_888c50 hits=0). No existing live capture targets the draw flush or DrawBatcher, so the capture above is needed.

## (6) CLOSES?

CLOSES? NO — the item's own wording requires both the header-to-record mapping AND an in-game test. The static analysis on disk is complete: DrawBatcher layout, record layouts, flush loops, all 7 executor call sites, and the submit seam are all [V]-proven verbatim. The header-to-record field wiring is [I] inferred (not [V] proven by a store instruction), and the in-game test (veto/modify a draw at flush, read back expected values) has not been run — units may not launch or attach to the game. Single blocking fact: the in-game test at flush 0xe81b720 is missing (capture queued: em3e_flush_verify at 0xe81b720).

## TOOL REQUESTS

Capture: `python tools/livecap/request.py add em3e_flush_verify 0xe81b720 --size 0x200 --max 8 --why "U-EM3e: capture DrawBatcher rcx, records pointer, pending counts and first record fields at flush entry to verify header-to-record mapping in game"` — QUEUED (result will appear in docs/data/live/em3e_flush_verify.txt).

In-game test: enter populated world → poll DrawBatcher at renderer+0x250 → verify pending counts and record fields → veto one batch (pending[kind]=0, confirm draw category disappears) → modify startInstance (confirm different actor/instance drawn) → diff DrawFlushRecorder stream against baseline. Blocked: units cannot run the game or attach.
