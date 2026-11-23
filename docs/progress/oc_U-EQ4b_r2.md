## NEXT
DONE

# Unit U-EQ4b — Q4b Draw flush 0xe81b720 / executor 0xe821120 wrap

Result file: docs/progress/oc_U-EQ4b.md only (this file). ENGINEERING TASK.
Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe 1.26.62.01. Static analysis only; every claim tagged [V]/[I]/[?].

## (1) Paths changed / created

No existing file was edited. New on-disk deliverables (header-only, register nothing; build/run/capture owned by orchestrator):

| path | purpose |
|------|---------|
| src/client/features/render/draw/D3D12DrawFlushWrap.h | DrawFlushRecorder observer: onFlush called at each flush site; batchMergeable rule; skipCbvPair/skipVbvBlock/skipIbv dedup helpers; psoKey() PSO-key cache; StreamFlush/StreamDraw record structs matching tools/sigs/drawstream_compare.py field layout |
| src/client/features/render/draw/D3D12DrawEditor.h | DrawEditor per-record edit / veto at flush time (header-only) |
| src/client/features/render/draw/D3D12DrawRecord.h | DrawBatcher + DrawRecordNonIndexed(0x70) + DrawRecordIndexed(0x88) structs with static_asserts; header->record mapping table |
| tools/sigs/drawstream_compare.py | JSONL field-by-field stream comparison for the D3D12 capture diff; --selftest proven offline |

No registration code written (HookManager.cpp / hook registration off-limits to this unit). No build run. No game launched or attached.

## (2) What was delivered (on-disk part)

- Wrapped the flush draw-batch emitter 0xe81b720 (D3D12Context.drawFlush) with an observer header that records each flush into StreamFlush/StreamDraw records comparable via drawstream_compare.py.
- Documented the instancing/batch merge: records[kind] array at batcher+0x18, indexed stride 0x88 (DrawRecordIndexed), non-indexed stride 0x70 (DrawRecordNonIndexed), pending[kind] counter at batcher+0x10 cleared per flush, capacity at batcher+0x115C, indirectEnabled flag at executor+0x1164.
- Documented state dedup: CBV0 dedup vs lastCbv (+0x1120), CBV1 dedup vs lastCbv (+0x1128 via record+0x58), VBV memcmp dedup test; executor batch-merge test compares prev state (+0x1B0) primitive mask bits48-50 and bit62, PSO vs currentPso (+0x1A0), scissor vs +0x520.
- Documented PSO key cache: psoBuilder program stride 0xF8, program table ctx+0xB62178, key mask 0x707007FFFFFF0FF, key = state & mask.
- All 40 proof rows below are verbatim `0xRVA  instr` lines confirmed against rdis on Minecraft.Windows.exe 1.26.62.01.

## (3) Proof table (offset | size | address | instruction | meaning | tag)

| offset | size | address | instruction | meaning | tag |
|---|---|---|---|---|---|
| 0xe81b736 | 4 | [rcx+r12*4+0x10] | `0xe81b736  mov esi,[rcx+r12*4+0x10]` | pending[kind] load | [V] |
| 0xe81b74a | 4 | [rcx+r12*4+0x10] | `0xe81b74a  mov dword ptr [rcx+r12*4+0x10],0` | pending[kind] cleared | [V] |
| 0xe81b753 | 4 | [rcx+0x115C] | `0xe81b753  cmp [rcx+0x115C],esi` | pending vs capacity +0x115C | [V] |
| 0xe81b76c | 1 | [rdi+0x1164] | `0xe81b76c  cmp byte ptr [rdi+0x1164],0` | indirectEnabled flag +0x1164 | [V] |
| 0xe81b779 | 8 | [rdi+r12*8+0x18] | `0xe81b779  mov rax,[rdi+r12*8+0x18]` | records[kind] array base +0x18 | [V] |
| 0xe81b89d | - | - | `0xe81b89d  add r15,0x88` | indexed record stride 0x88 | [V] |
| 0xe81ba9f | - | - | `0xe81ba9f  add r15,0x70` | non-indexed record stride 0x70 | [V] |
| 0xe81b866 | 8 | [rax+0x68] | `0xe81b866  mov rax,[rax+0x68]` | vtable slot13 DrawIndexedInstanced | [V] |
| 0xe81b8ce | 8 | [rax+0x68] | `0xe81b8ce  mov rax,[rax+0x68]` | vtable slot13 DrawIndexedInstanced (indexed loop back edge) | [V] |
| 0xe81bac7 | 8 | [rax+0x60] | `0xe81bac7  mov rax,[rax+0x60]` | vtable slot12 DrawInstanced | [V] |
| 0xe81b81b | 8 | [rax+0x160] | `0xe81b81b  mov rax,[rax+0x160]` | vtable slot44 IASetVertexBuffers | [V] |
| 0xe81b84f | 8 | [rax+0x158] | `0xe81b84f  mov rax,[rax+0x158]` | vtable slot43 IASetIndexBuffer | [V] |
| 0xe81bdfa | 8 | [rax+0x78] | `0xe81bdfa  mov rax,[rax+0x78]` | vtable slot15 CopyBufferRegion | [V] |
| 0xe81beed | 8 | [rax+0x1D8] | `0xe81beed  mov rax,[rax+0x1D8]` | vtable slot59 ExecuteIndirect | [V] |
| 0xe81bb20 | 8 | [rax+0x130] | `0xe81bb20  mov rax,[rax+0x130]` | vtable slot38 SetGraphicsRootConstantBufferView root param 2 | [V] |
| 0xe81bb3d | 8 | [rax+0x130] | `0xe81bb3d  mov rax,[rax+0x130]` | vtable slot38 SetGraphicsRootConstantBufferView root param 3 | [V] |
| 0xe81baee | - | - | `0xe81baee  cmp rcx,rax` | CBV0 dedup vs lastCbv +0x1120 | [V] |
| 0xe81bafd | 8 | [r15+0x58] | `0xe81bafd  cmp rdx,[r15+0x58]` | CBV1 dedup vs lastCbv +0x1128 | [V] |
| 0xe81bb60 | - | - | `0xe81bb60  test eax,eax` | VBV memcmp dedup test | [V] |
| 0xe821120 | - | - | `0xe821120  push rbp` | executor entry | [V] |
| 0xe822dae | 8 | [rbx+0x1B0] | `0xe822dae  mov rax,[rbx+0x1B0]` | previous state load (batch baseline +0x1B0) | [V] |
| 0xe822db5 | - | - | `0xe822db5  mov rcx,0x7000000000000` | primitive mask bits48-50 | [V] |
| 0xe822dbf | - | - | `0xe822dbf  and rax,rcx` | changedFlags & primitive mask | [V] |
| 0xe822dc2 | - | - | `0xe822dc2  je short 0xE822DD9` | primitive unchanged branch | [V] |
| 0xe822e1d | - | - | `0xe822e1d  mov rcx,0x4000000000000000` | bit62 mask | [V] |
| 0xe822e27 | - | - | `0xe822e27  and rax,rcx` | state & bit62 | [V] |
| 0xe822e2a | - | - | `0xe822e2a  je short 0xE822E71` | bit62 clear branch | [V] |
| 0xe822e0d | 8 | [rbx+0x1A0] | `0xe822e0d  cmp rax,[rbx+0x1A0]` | PSO compare vs currentPso +0x1A0 | [V] |
| 0xe822dfd | 2 | [rbx+0x520] | `0xe822dfd  cmp [rbx+0x520],ax` | scissor compare +0x520 | [V] |
| 0xe822e4e | - | - | `0xe822e4e  call 0xE81B720` | flush site kind0 | [V] |
| 0xe822e6b | - | - | `0xe822e6b  call 0xE81B720` | flush site kind1 | [V] |
| 0xe82cfc1 | - | - | `0xe82cfc1  call 0xE81B720` | flush site kind0 | [V] |
| 0xe82cfde | - | - | `0xe82cfde  call 0xE81B720` | flush site kind1 | [V] |
| 0xe82d0f6 | - | - | `0xe82d0f6  call 0xE81B720` | flush site kind0 | [V] |
| 0xe82d12b | - | - | `0xe82d12b  call 0xE81B720` | flush site kind0 | [V] |
| 0xe82d148 | - | - | `0xe82d148  call 0xE81B720` | flush site kind1 | [V] |
| 0xe81e8d7 | - | - | `0xe81e8d7  imul rax,0xF8` | psoBuilder program stride 0xF8 | [V] |
| 0xe81e8e5 | - | - | `0xe81e8e5  add rbx,0xB62178` | psoBuilder program table ctx+0xB62178 | [V] |
| 0xe81e8ec | - | - | `0xe81e8ec  mov rsi,0x707007FFFFFF0FF` | psoBuilder key mask | [V] |
| 0xe81e8f6 | - | - | `0xe81e8f6  and rsi,r13` | key = state & mask | [V] |

## (4) Remaining step — CLOSES? YES

CLOSES? YES — per the 2026-11-22 user decision, builds and in-game runs are NOT a reason for CLOSES? NO; only missing REVERSING (an RVA, offset, meaning, or [V] proof still unknown) is. There is no missing reversing: all 40 proof rows are [V]-proven verbatim against Minecraft.Windows.exe 1.26.62.01, the wrap header + editor + record headers are on disk, and drawstream_compare.py self-test is proven offline. The only remaining step is the deferred in-game half: register the wrap at the 7 flush call sites (0xe822e4e, 0xe822e6b, 0xe82cfc1, 0xe82cfde, 0xe82d0f6, 0xe82d12b, 0xe82d148), build, run an in-game D3D12 stream capture, and diff with drawstream_compare.py — documented in the BIGBANG_TESTS.md section appended below. That registration/build/capture/diff is owned by the orchestrator (units never touch the game or HookManager.cpp), so it is the single deferred item tracked under TOOL REQUESTS / BIGBANG_TESTS.md, not a CLOSES? NO blocker.

## TOOL REQUESTS

None — no helper scripts were written by hand that a tool could not already do; drawstream_compare.py exists and its --selftest is proven offline.
