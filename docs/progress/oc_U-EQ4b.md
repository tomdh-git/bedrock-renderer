## NEXT
DONE

# UNIT U-EQ4b — result: Q4b draw flush 0xe81b720 / executor 0xe821120 wrap

GOAL (verbatim from docs/RENDER_CHECKLIST.md line 578, still unticked):
"Q4b Draw flush 0xe81b720 / executor 0xe821120 rewritten or wrapped: instancing/batch merge, state dedup, PSO key cache; verified by comparing the recorded D3D12 call stream"

This unit is an ENGINEERING TASK. The item needs a build and an in-game run, so every on-disk part is done here and the remaining build/in-game step is listed in section (4). Nothing was run against the game and nothing was built.

## (1) Changed / created paths

- docs/progress/oc_U-EQ4b.md — this result file (rewritten in full)
- src/client/features/render/draw/D3D12DrawFlushWrap.h — NEW header: documented wrap/observer seam for the draw flush (0xe81b720) and executor (0xe821120): flush recorder (the recorded D3D12 call stream), batch-merge rule, state dedup, PSO key cache. Header-only: no CMake change, no build needed to review.
- tools/sigs/drawstream_compare.py — NEW documented tool: compares a recorded D3D12 call stream (JSONL) against an expected stream; --selftest runs offline with no game and no build.

Not edited: HookManager.cpp, any existing hook registration, CMake, Sigs.json, existing source. No build run. Game not launched or attached.

## (2) What was delivered

**Draw flush 0xe81b720 wrapped/observed.** The flush consumes batcher pending[kind] at +0x10+kind*4 (u32), then zeroes it, picks the record array at +0x18+kind*8, walks records with stride 0x70 (non-indexed) / 0x88 (indexed), and emits through the command-list vtable: slot 12 DrawInstanced (+0x60), slot 13 DrawIndexedInstanced (+0x68), slot 43 IASetIndexBuffer (+0x158), slot 44 IASetVertexBuffers (+0x160), slot 38 SetGraphicsRootConstantBufferView (+0x130, root params 2/3 = the CBV pair), slot 15 CopyBufferRegion (+0x78) and slot 59 ExecuteIndirect (+0x1D8) for the indirect path. All [V] below. The wrap header observes every invocation at the executor's 7 flush call sites.

**Instancing / batch merge.** The executor keeps one open batch and appends BatchDraw (0x70) / BatchDrawIndexed (0x88) records; a new draw joins the batch iff bind hash, stencil, program, blend state, primitive type (state bits 48-50), topology, scissor and PSO all match and state bit 62 is clear — otherwise it flushes both kinds via 0xe81b720. Merging = one instanced draw with accumulated instanceCount. The merge rule is implemented in the header (batchMergeable) and proven by the [V] rows below.

**State dedup.** At flush time the CBV pair is compared with the cached lastCbv (+0x1120/+0x1128), the VBV block with vbCache (+0x10C0, 0x50 bytes) and the IBV with ibCache (+0x1110, 0x10 bytes); equal bindings are not re-bound. Implemented in the header (skipCbvPair / skipVbvBlock / skipIbv) and proven by [V] rows below.

**PSO key cache.** psoBuilder 0xe81e860 computes key = state & 0x0707007FFFFFF0FF (mask loaded at 0xe81e8ec, AND at 0xe81e8f6) over the program table at ctx+0xB62178 (stride 0xF8, imul at 0xe81e8d7). The header exposes psoKey() for a side cache keyed on exactly that value.

**Verified by comparing the recorded D3D12 call stream.** drawstream_compare.py diffs two JSONL streams field by field (kind, pending, cbv0/cbv1, vbvDirty, ibvDirty, per-draw args) and reports the first divergence; --selftest proves match / merge-detection / dedup-detection on synthetic streams. The live half (capture from a run with the wrap registered, diff vs baseline) is the remaining step in (4).

## (3) Proof table — every instruction line copied verbatim from the disassembly of Minecraft.Windows.exe 1.26.62.01; [V] = seen in disassembly. Sizes are memory-access sizes from the instruction; '-' = register-only/immediate, no memory access size applies.

| site | size | address | instruction | meaning | tag |
| 0xe81b736 | 4 | [rcx+r12*4+0x10] | `0xe81b736  mov esi,[rcx+r12*4+0x10]` | flush(kind): pending[kind] = u32 at batcher+0x10+kind*4, kind = r9d | [V] |
| 0xe81b74a | 4 | [rcx+r12*4+0x10] | `0xe81b74a  mov dword ptr [rcx+r12*4+0x10],0` | pending[kind] reset to 0 after consume | [V] |
| 0xe81b753 | 4 | [rcx+0x115C] | `0xe81b753  cmp [rcx+0x115C],esi` | pending vs capacity at batcher+0x115C → direct/overflow stat | [V] |
| 0xe81b76c | 1 | [rdi+0x1164] | `0xe81b76c  cmp byte ptr [rdi+0x1164],0` | indirectEnabled flag (batcher+0x1164): 0 → one-by-one draw path | [V] |
| 0xe81b779 | 8 | [rdi+r12*8+0x18] | `0xe81b779  mov rax,[rdi+r12*8+0x18]` | records[kind] array base at batcher+0x18+kind*8 | [V] |
| 0xe81b89d | - | - | `0xe81b89d  add r15,0x88` | indexed record stride 0x88 in the flush loop | [V] |
| 0xe81ba9f | - | - | `0xe81ba9f  add r15,0x70` | non-indexed record stride 0x70 in the flush loop | [V] |
| 0xe81b866 | 8 | [rax+0x68] | `0xe81b866  mov rax,[rax+0x68]` | command-list vtable slot 13 = DrawIndexedInstanced | [V] |
| 0xe81b8ce | 8 | [rax+0x68] | `0xe81b8ce  mov rax,[rax+0x68]` | command-list vtable slot 13 = DrawIndexedInstanced (indexed loop; index count = [r15+0x70]) | [V] |
| 0xe81bac7 | 8 | [rax+0x60] | `0xe81bac7  mov rax,[rax+0x60]` | command-list vtable slot 12 = DrawInstanced (non-indexed loop) | [V] |
| 0xe81b81b | 8 | [rax+0x160] | `0xe81b81b  mov rax,[rax+0x160]` | command-list vtable slot 44 = IASetVertexBuffers | [V] |
| 0xe81b84f | 8 | [rax+0x158] | `0xe81b84f  mov rax,[rax+0x158]` | command-list vtable slot 43 = IASetIndexBuffer | [V] |
| 0xe81bdfa | 8 | [rax+0x78] | `0xe81bdfa  mov rax,[rax+0x78]` | command-list vtable slot 15 = CopyBufferRegion (indirect path) | [V] |
| 0xe81beed | 8 | [rax+0x1D8] | `0xe81beed  mov rax,[rax+0x1D8]` | command-list vtable slot 59 = ExecuteIndirect (indirect path) | [V] |
| 0xe81bb20 | 8 | [rax+0x130] | `0xe81bb20  mov rax,[rax+0x130]` | command-list vtable slot 38 = SetGraphicsRootConstantBufferView, root param 2 (edx=2, after mov rax,[rcx] at 0xe81bb1d) | [V] |
| 0xe81bb3d | 8 | [rax+0x130] | `0xe81bb3d  mov rax,[rax+0x130]` | command-list vtable slot 38 = SetGraphicsRootConstantBufferView, root param 3 (edx=3, after mov rax,[rcx] at 0xe81bb3a) | [V] |
| 0xe81baee | - | - | `0xe81baee  cmp rcx,rax` | state dedup: record CBV[0] vs cached lastCbv[0] at batcher+0x1120; equal → skip rebind | [V] |
| 0xe81bafd | 8 | [r15+0x58] | `0xe81bafd  cmp rdx,[r15+0x58]` | state dedup: record CBV[1] vs cached lastCbv[1] at batcher+0x1128 | [V] |
| 0xe81bb60 | - | - | `0xe81bb60  test eax,eax` | VBV memcmp result test; equal → IASetVertexBuffers skipped (dedup) | [V] |
| 0xe821120 | - | - | `0xe821120  push rbp` | draw executor entry; only caller is wrapper 0xe83c390 | [V] |
| 0xe822dae | 8 | [rbx+0x1B0] | `0xe822dae  mov rax,[rbx+0x1B0]` | previous state load (job+0x1B0), the state-dedup baseline | [V] |
| 0xe822db5 | - | - | `0xe822db5  mov rcx,0x7000000000000` | primitive-type mask = state bits 48-50 (0x0007000000000000) for the batch-merge test | [V] |
| 0xe822dbf | - | - | `0xe822dbf  and rax,rcx` | changedFlags & primitive mask: any change flushes the open batch | [V] |
| 0xe822dc2 | - | - | `0xe822dc2  je short 0xE822DD9` | primitive unchanged → continue with the remaining batch-merge checks | [V] |
| 0xe822e1d | - | - | `0xe822e1d  mov rcx,0x4000000000000000` | state bit 62 mask (occlusion-query / force-flush flag) | [V] |
| 0xe822e27 | - | - | `0xe822e27  and rax,rcx` | state & bit 62: set → batch is flushed, draw never joins | [V] |
| 0xe822e2a | - | - | `0xe822e2a  je short 0xE822E71` | bit 62 clear → bind-hash path of the batch-merge test | [V] |
| 0xe822e0d | 8 | [rbx+0x1A0] | `0xe822e0d  cmp rax,[rbx+0x1A0]` | PSO compare: candidate PSO vs currentPso at job+0x1A0; mismatch flushes | [V] |
| 0xe822dfd | 2 | [rbx+0x520] | `0xe822dfd  cmp [rbx+0x520],ax` | scissor compare inside the batch-merge test | [V] |
| 0xe822e4e | - | - | `0xe822e4e  call 0xE81B720` | flush kind 0 (non-indexed) when a draw breaks batch compatibility | [V] |
| 0xe822e6b | - | - | `0xe822e6b  call 0xE81B720` | flush kind 1 (indexed), the paired site right after | [V] |
| 0xe81e8d7 | - | - | `0xe81e8d7  imul rax,0xF8` | psoBuilder: program record stride 0xF8 | [V] |
| 0xe81e8e5 | - | - | `0xe81e8e5  add rbx,0xB62178` | psoBuilder: program table base at ctx+0xB62178 | [V] |
| 0xe81e8ec | - | - | `0xe81e8ec  mov rsi,0x707007FFFFFF0FF` | psoBuilder: PSO key mask loaded into rsi | [V] |
| 0xe81e8f6 | - | - | `0xe81e8f6  and rsi,r13` | psoBuilder: PSO key = draw state & 0x0707007FFFFFF0FF, the cache lookup key | [V] |

## (4) Remaining build / in-game step (not done in this unit; listed per the unit rules for items that need the game/build)

1. Register DrawFlushRecorder at the 7 executor flush call sites (0xe822e4e, 0xe822e6b, 0xe82cfc1, 0xe82cfde, 0xe82d0f6, 0xe82d12b, 0xe82d148; batcher = [job+0x250], kind in r9d) via the project's hook system — HookManager.cpp is off-limits to this unit, so registration is owned by whoever maintains hook registration.
2. Build the client (no build was run here; CMake is off-limits to this unit).
3. Run a world frame, capture the D3D12 command-list call stream from the recorder (JSONL: kind, pending, cbv0/cbv1, vbvDirty, ibvDirty, per-draw args).
4. Diff with `python tools/sigs/drawstream_compare.py recorded.jsonl baseline.jsonl` and confirm: fewer flushes / larger instanceCount (batch merge), vbvDirty/ibvDirty == 0 on repeats (state dedup), repeated psoKey with no new pipeline (PSO key cache).

CLOSES? NO — the wrap header and stream-compare tool exist on disk and every mechanic above is proven by [V] rows, but Q4b's own wording ("rewritten or wrapped ... verified by comparing the recorded D3D12 call stream") is not met on disk now: the wrap is not registered in the renderer, no build has run, and no live D3D12 call stream has been captured and diffed. Single blocking fact: requires build + registration at the 7 flush call sites + an in-game run capturing the stream + diff with tools/sigs/drawstream_compare.py.
