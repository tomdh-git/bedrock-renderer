## NEXT
DONE

# U-EN1b — N1b: per-draw veto/rewrite at draw executor 0xe821120 (flush 0xe81b720) — header-to-record mapping (BGFX_MAP 8a; M3e)

Output file: docs/progress/oc_U-EN1b.md only. Static analysis only: rdis.exe on Minecraft.Windows.exe (1.26.62.01) passed as an argument; the exe is never executed. No edits to HookManager.cpp, any hook registration, CMake, or existing Sigs.json entries; no builds, no commits, no game launch/attach. The game was never touched; the live m3e_test.txt capture (orchestrator-run, read-only) is cited as [V live].

## GOAL / pending part

Checklist item N1b (docs/RENDER_CHECKLIST.md line 480): "Per-draw veto/rewrite at draw executor 0xe821120 (flush 0xe81b720) — needs header-to-record mapping plus in-game test — BGFX_MAP 8a; M3e". The static half (header→record mapping) is decoded here verbatim from the disassembly of executor 0xe821120's record-building tail (0xe82caf2..0xe82cde7). The in-game half cannot be done by a unit (no game/Cheat Engine access); an exact test plan + capture request are written under TOOL REQUESTS.

Basis already on disk (re-used, not re-derived):
- Draw executor 0xe821120, size 0xC3C3, only caller wrapper 0xe83c390 [V per docs/functions/e821120.md].
- Draw flush 0xe81b720, size 0x803, called 7x from executor [V per docs/functions/e81b720.md]; batcher counts pending[2] at +0x10, record arrays at +0x18, kind 0 = non-indexed (stride 0x70), kind 1 = indexed (stride 0x88) [V per e81b720.md + m3e_test.txt].
- Draw header at Frame+0xB4700 + idx*0x80, stride 0x80 [V per BGFX_MAP 6am / Frame.h]; header fields: +0x40 startIndex, +0x44 numIndices, +0x48 indexStride, +0x54 numInstances, +0x58 instanceDataStride, +0x74 indexBuffer, +0x76 instanceDataBuffer [V per Frame.h / e821120.md].
- Live m3e_test.txt: flush 0xE81B720, kind1 records stride 0x88, IndexCount at +0x70 (= 2364 in sample), MODIFY IndexCount→0 and SKIP batch (count→0) applied, game kept running through 600 hits [V live docs/data/live/m3e_test.txt]. STILL OPEN there: header-to-record mapping — closed statically below.

## EVIDENCE: header-to-record mapping (executor record-building tail, 0xe82caf2..0xe82cde7) [V]

The executor builds one DrawBatcher record per draw item. Indexed records (header+0x74 indexBuffer != 0xFFFF) stride 0x88; non-indexed stride 0x70. The flush consumes record+0x00..0x4F as 5 VBVs, record+0x50..0x5F as the IBV (indexed only), record+0x60/0x68 as root CBVs #2/#3, and draw args at +0x60..+0x80 [V per e81b720.md pseudocode, matches disassembly below]. Note: DrawRecord.h's indexed layout had IBV/VBV swapped (ibv at +0x00, vbv at +0x10); the truth is vbv at +0x00, ibv at +0x50 (fixed in DrawRecord.h below).

| name | offset | size | address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| header+0x44 numIndices -> indexed rec+0x70 indexCount | 0x44 | 4 | `[rdi+0x70]` store | `0xe82caf2  mov esi,[r12+0x44]` ; `0xe82cd11  mov [rdi+0x70],esi` | numIndices (0xFFFFFFFF = computed from buffer size/stride) stored as indexed indexCount | [V] |
| header+0x54 numInstances -> indexed rec+0x74 instanceCount | 0x54 | 4 | `[rdi+0x74]` store | `0xe82cd1b  mov eax,[rcx+0x54]` ; `0xe82cd1e  mov [rdi+0x74],eax` | numInstances stored as indexed instanceCount | [V] |
| header+0x40 startIndex -> indexed rec+0x78 startIndex | 0x40 | 4 | `[rdi+0x78]` store | `0xe82cd21  mov eax,[rcx+0x40]` ; `0xe82cd24  mov [rdi+0x78],eax` | startIndex stored as indexed startIndex | [V] |
| indexed rec+0x7C baseVertex+startInstance = 0 | 0x7C | 8 | `[rdi+0x7C]` store | `0xe82cd27  mov qword ptr [rdi+0x7C],0` | baseVertex and startInstance zeroed (covers +0x7C..+0x87) | [V] |
| indexed rec+0x60 vsConstantsGpuVa (root CBV #2) | 0x60 | 8 | `[rdx+rax+0x60]` store | `0xe82cb36  mov r8,[rbx+0x170]` ; `0xe82cb3d  mov [rdx+rax+0x60],r8` | vertex constant-buffer GPU VA bound to root parameter 2 | [V] |
| indexed rec+0x68 fsConstantsGpuVa (root CBV #3) | 0x68 | 8 | `[rdx+rax+0x68]` store | `0xe82cb42  mov r8,[rbx+0x380]` ; `0xe82cb49  mov [rdx+rax+0x68],r8` | fragment constant-buffer GPU VA bound to root parameter 3 | [V] |
| header+0x48 indexStride -> indexed rec+0x5C IBV.Format | 0x48 | 4 | `[rdx+rax+0x5C]` store | `0xe82cb5e  cmp dword ptr [r12+0x48],2` ; `0xe82cb64  mov ecx,0x2A` ; `0xe82cb69  mov r8d,0x39` ; `0xe82cb6f  cmove ecx,r8d` ; `0xe82cb73  mov [rdx+rax+0x5C],ecx` | stride 2 -> DXGI_FORMAT_R16_UINT (0x39), stride 4 -> 0x2A R32_UINT | [V] |
| IB record+0x58 gpuVA -> indexed rec+0x50 IBV.BufferLocation | 0x58 | 8 | `[rdx+rax+0x50]` store | `0xe82cb4e  mov r8,[rcx+0x58]` ; `0xe82cb52  mov [rdx+rax+0x50],r8` | index-buffer record +0x58 (gpuVA) -> record IBV address | [V] |
| IB record+0x60 size -> indexed rec+0x58 IBV.SizeInBytes | 0x60 | 4 | `[rdx+rax+0x58]` store | `0xe82cb57  mov ecx,[rcx+0x60]` ; `0xe82cb5a  mov [rdx+rax+0x58],ecx` | index-buffer record +0x60 (size) -> record IBV size | [V] |
| header stream{s} -> indexed rec VBV[stream*16] | 0x00+s*8 | 16 | `[rdi+rax]`/`[rdi+rax+8]`/`[rdi+rax+0xC]` store | `0xe82ccad  movzx eax,r12b` ; `0xe82ccc8  mov [rdi+rax],rcx` ; `0xe82ccd0  mov [rdi+rax+0xC],ecx` ; `0xe82ccdc  mov [rdi+rax+8],ecx` | per stream (streamMask bits at header+0x63): VBV BufferLocation = vb-record gpuVA + header+0x50 offset, Stride = header+0x58, SizeInBytes = stride*numInstances(header+0x54); loop caps at 4 streams | [V] |
| header+0x54 numInstances -> non-indexed rec+0x64 instanceCount | 0x54 | 4 | `[rsi+0x64]` store | `0xe82cdd8  mov eax,[rax+0x54]` ; `0xe82cddb  mov [rsi+0x64],eax` | numInstances stored as non-indexed instanceCount | [V] |
| non-indexed rec+0x60 vertexCount | 0x60 | 4 | `-` | `-` (no verbatim reader seen) | header+0x4C numVertices -> non-indexed rec+0x60 not observed verbatim; the store at `0xe82cde4  mov [rsi+0x60],eax` writes scratch [rbx+0xC0] whose role is not vertexCount | [UNVERIFIED: 0xe82cde4 what is rbx+0xC0; header+0x4C -> rec+0x60 reader not found] |

Draw header fields read by the executor but NOT copied into a record field (state/PSO/scissor/live state only): +0x20 stateFlags, +0x28 stencil, +0x60 scissor index, +0x62 submitFlags, +0x63 streamMask, +0x64 uniformIdx, +0x74 indexBuffer (selects indexed vs non-indexed path), +0x76 instanceDataBuffer (selects instance-data VBV append), +0x7A occlusionQuery [V per e821120.md item-loop transcription]. These drive PSO/batch decisions, not record fields.

## What changed

1. docs/progress/oc_U-EN1b.md — this note (created).
2. src/sdk/mc/deps/bgfx/DrawRecord.h — corrected the indexed record layout (VBV block at +0x00..0x4F, IBV at +0x50..0x5F, root CBVs at +0x60/+0x68, draw args at +0x70..+0x80); added the verbatim header→record field map with static_asserts on every record offset. Non-indexed layout unchanged (already correct).
3. src/client/features/render/draw/D3D12DrawRecord.h — same indexed-layout correction (VBV/IBV swapped) to match the disassembly and the live m3e_test.txt record contents.

Neither header registers hooks, patches anything, or reads/writes game memory; both are layout documentation + static_asserts only, following CLAUDE.md fail-fast style.

## CLOSES?

NO — the single blocking fact: the header-to-record mapping is now proven statically [V] above, but the item's in-game test (correlating a live frame header to its batcher record, then veto/rewrite and observing the draw change on screen) has not been performed; units cannot touch the game or Cheat Engine, and the orchestrator builds both DLLs and runs captures. Everything the item allows without the game is done on disk.

## TOOL REQUESTS

In-game test plan (for the orchestrator's live build/run):
1. Launch 1.26.62.01, enter a populated world so draws flow through flush 0xe81b720.
2. At flush entry (rcx = DrawBatcher*), read counts u32 [b+0x10]/[b+0x14] (kinds 0/1) and record arrays [b+0x18]/[b+0x20] (already captured once in m3e_test.txt; repeat to confirm stability).
3. For each kind-1 record, verify the header→record mapping: record+0x70 (indexCount) == header+0x44 (numIndices), record+0x74 (instanceCount) == header+0x54, record+0x78 (startIndex) == header+0x40, record+0x5C (IBV format 0x39/0x2A) matches header+0x48 stride, record+0x60/0x68 are the root CBVs. The header for item N is at Frame+0xB4700 + sortedItem[N]*0x80; the record it produced is the one appended to the batch just before flush (same bind hash / program / state).
4. Veto test: set indexed record+0x70 (indexCount) = 0, or set batcher pending[kind] = 0 at +0x10/+0x14 to skip a whole batch; confirm the corresponding draw disappears from the frame and the game keeps running (as m3e_test.txt already showed for count->0 skip).
5. Rewrite test: change indexed record+0x78 (startIndex) or record+0x70 (indexCount); confirm the drawn geometry/index range changes accordingly on the next frame.
6. Expected values: kind-1 record fields match header fields per the [V] table above; indexCount->0 skips that draw; startIndex change shifts geometry; batch remains coherent (no crash, counts update).

Capture request (one target, function-entry only):
`python tools/livecap/request.py add en1b_executor 0xe821120 --size 0x200 --max 8 --why "U-EN1b: capture executor job context (rcx) at entry to correlate job+0x590 header base and job+0x250 batcher pointer for live header-to-record mapping verification"`

After the capture result lands, decode: job+0x590 = Frame* (header base Frame+0xB4700), job+0x250 = DrawBatcher*, then match each flushed record to its source header via indexCount/startIndex/instanceCount and confirm the [V] mapping live.

Existing live data used before requesting: docs/data/live/m3e_test.txt (flush counts + kind1 record contents, 600 hits, read-only) — already confirms record layout and that veto/skip works in game; only the header↔record correlation is missing.
