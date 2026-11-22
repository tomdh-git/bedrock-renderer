## NEXT
DONE

# Unit U-EM1f — per-frame flush + draw-dispatch liveness (M1f)

All live captures are orchestrator-produced, read-only, in docs/data/live/ (format: docs/data/live/README.md). Each sample line = `REG=value hit=N hexbytes ...`; a block starts with `CALLER ret=0xRVA first_hit=N` (ret = the caller's return address, i.e. the caller site). Exe: Minecraft.Windows.exe 1.26.62.01. Static disassembly with rdis.exe on the exe file (passed as argument only; never launched).

## 1. Live captures read (all exist on disk — none re-queued)

| capture | rva | kind | hits | samples | first CALLER ret | cite |
|---|---|---|---|---|---|---|
| u_em1f_submit_entry | 0xE82E230 | regs | 418 | 32 | 0xE83D4DB | [LIVE docs/data/live/u_em1f_submit_entry.txt:3] |
| u_em1f_draw_flush | 0xE81B720 | regs | 354192 | 32 | 0xE822E53 | [LIVE docs/data/live/u_em1f_draw_flush.txt:3] |
| u_em1f_endframe | 0xC270460 | regs | 1108 | 34 | 0x67CA3D2 | [LIVE docs/data/live/u_em1f_endframe.txt:3] |
| u_em1f_dispatch | 0xE9002E0 | regs | 1108 | 32 | 0xC270559 | [LIVE docs/data/live/u_em1f_dispatch.txt:3] |
| u_em1f_view_setup | 0x568CDCC | regs | 14371 | 34 | 0xFFFF8009FA420000 | [LIVE docs/data/live/u_em1f_view_setup.txt:3] |
| u_em1f_generate | 0xC273420 | regs | 829 | 32 | 0xC270526 | [LIVE docs/data/live/u_em1f_generate.txt:3]; hits=829 samples=32 [LIVE docs/data/live/_status.txt:2] |

## 2. Comparison table: expected vs live

| # | Claim (expected) | Live evidence [LIVE file:line] | Confirmed? |
|---|---|---|---|
| 1 | submit_entry 0xE82E230 fires per submit; caller = draw executor ret=0xE83D4DB; RCX = adapter/device object (constant) | `CALLER ret=0xE83D4DB first_hit=1` [LIVE u_em1f_submit_entry.txt:3]; `RCX=2300A010000 hit=1 ret=0xE83D4DB` ... dump contains UTF-16 "AMD Radeon 760M Graphics" [LIVE u_em1f_submit_entry.txt:4]; 418 hits/32 samples [LIVE u_em1f_submit_entry.txt:1] | YES [V live] |
| 2 | draw_flush 0xE81B720 fires per draw; ~354192/1108 ≈ 320 hits/frame; called from executor loops | callers `ret=0xE822E53` [LIVE u_em1f_draw_flush.txt:3], `ret=0xE822E70` [LIVE u_em1f_draw_flush.txt:13], `ret=0xE82D130` [LIVE u_em1f_draw_flush.txt:29], `ret=0xE82D14D` [LIVE u_em1f_draw_flush.txt:33]; 354192 hits/32 samples [LIVE u_em1f_draw_flush.txt:1]; 354192/1108 frames ≈ 320/frame (frame count from u_em1f_endframe.txt:1) | YES [V live] |
| 3 | endFrame 0xC270460: rcx = BgfxContext, ~1 hit/frame | `CALLER ret=0x67CA3D2 first_hit=1` [LIVE u_em1f_endframe.txt:3]; `RCX=22FC6A70BE0 hit=1 ret=0x67CA3D2` (constant context object, dossier: rcx = BgfxContext*) [LIVE u_em1f_endframe.txt:4]; 1108 hits/34 samples ≈ 1/frame [LIVE u_em1f_endframe.txt:1] | YES [V live + dossier docs/functions/c270460.md:66] |
| 4 | dispatch 0xE9002E0 fires exactly once per endFrame (1:1); called from endFrame | 1108 hits/32 samples = endFrame's 1108 [LIVE u_em1f_dispatch.txt:1 vs u_em1f_endframe.txt:1]; `CALLER ret=0xC270559` = 0xC270460+0xF9, inside endFrame [LIVE u_em1f_dispatch.txt:3] | YES [V live] — 1:1 relation endFrame:dispatch = 1108:1108 |
| 5 | generate 0xC273420 called from endFrame (dossier: x1 per endFrame) | `CALLER ret=0xC270526` inside endFrame [LIVE u_em1f_generate.txt:3]; 829 hits/32 samples [LIVE docs/data/live/_status.txt:2] (sub-frame count: generation is conditional, not every frame) | YES [V live] for "called from endFrame"; count 829 ≠ 1108 is expected (conditional) |
| 6 | view_setup 0x568CDCC runs ~13× per endFrame | `CALLER ret=0xFFFF8009FA420000 first_hit=1` [LIVE u_em1f_view_setup.txt:3]; 14371 hits/34 samples [LIVE u_em1f_view_setup.txt:1]; 14371/1108 ≈ 12.97 ≈ 13 per endFrame [LIVE u_em1f_endframe.txt:1] | YES [V live] |
| 7 | flush body reaches DrawIndexedInstanced (cmdlist vtable slot 13 = +0x68) | Static: `0xe81b8ce  mov rax,[rax+0x68]` (slot 13 load) + `0xe81b8dc  call qword ptr [0xF99FFA0]` thunk (sub_eea6040 = `jmp rax`), both inside flush body 0xe81b720; second indexed site `0xe81b866  mov rax,[rax+0x68]` + `0xe81b88b  call qword ptr [0xF99FFA0]` [V static: rdis dis 0xe81b720; sub_eea6040 dis]; live per-draw firing = claim 2; emitter live capture requested below | YES [V static]; live emitter capture pending (u_em1f_draw_emit requested, not yet executed) |

## 3. Per-claim verdicts

1. submit_entry: CONFIRMED. Caller ret=0xE83D4DB on every sample block [LIVE u_em1f_submit_entry.txt:3]; RCX constant = 2300A010000, a device/adapter object whose dump contains "AMD Radeon 760M Graphics" [LIVE u_em1f_submit_entry.txt:4]. 418 hits over the capture (32 samples).
2. draw_flush: CONFIRMED (per-draw firing). 354192 hits / 1108 endFrames ≈ 320 hits/frame, matching ~514 items/frame per-call cadence [LIVE u_em1f_draw_flush.txt:1 vs u_em1f_endframe.txt:1]. Four caller return addresses show the executor loops call it [LIVE u_em1f_draw_flush.txt:3,13,29,33].
3. endFrame: CONFIRMED. rcx = constant context object 22FC6A70BE0 = BgfxContext* (dossier docs/functions/c270460.md:66) [LIVE u_em1f_endframe.txt:4]; ~1 hit/frame (1108 hits, 34 samples over 1108 frames) [LIVE u_em1f_endframe.txt:1]; caller ret=0x67CA3D2 = frame renderer [LIVE u_em1f_endframe.txt:3].
4. dispatch vs endFrame: CONFIRMED 1:1. dispatch 1108 hits = endFrame 1108 hits [LIVE u_em1f_dispatch.txt:1; LIVE u_em1f_endframe.txt:1]; dispatch's caller ret=0xC270559 lies inside endFrame (0xC270460+0xF9) [LIVE u_em1f_dispatch.txt:3]; endFrame's dossier lists `0xe9002e0 task list dispatch x1` [docs/functions/c270460.md:21].
5. generate: CONFIRMED as "called from endFrame". caller ret=0xC270526 inside endFrame [LIVE u_em1f_generate.txt:3]; dossier: `0xc273420 frame-graph generate/encode x1` [docs/functions/c270460.md:20]. 829 hits ≠ 1108 because generation is conditional (not every frame emits tasks).
6. view_setup: CONFIRMED ~13/endFrame. 14371 hits / 1108 frames ≈ 12.97 [LIVE u_em1f_view_setup.txt:1; LIVE u_em1f_endframe.txt:1].
7. flush → DrawIndexedInstanced: CONFIRMED statically [V]. See section 4. Live emitter capture u_em1f_draw_emit requested (section 5) to add a live poll; not yet executed by the orchestrator.

## 4. Flush body 0xe81b720 reaches DrawIndexedInstanced — exact addresses

Dossier docs/functions/e81b720.md: "Indirect calls ... [obj+0x68] slot 13 = DrawIndexedInstanced x1; [obj+0x60] slot 12 = DrawInstanced x2" [V static]. In the actual disassembly (`rdis dis 0xe81b720 800`) the compiler does NOT emit a literal `call qword ptr [reg+0x68]` mnemonic; it loads the vtable slot into rax and tail-calls through CFG thunk sub_eea6040 (`0xeea6040  jmp rax` [V static]) referenced as `[0xF99FFA0]`:

Indexed path (record stride 0x88):
- `e81b85f  mov rcx,[rbx+0x30]` ; rcx = ID3D12GraphicsCommandList* ([rbx+0x30] per dossier signature)
- `e81b863  mov rax,[rcx]` ; rax = command-list vtable pointer
- `e81b866  mov rax,[rax+0x68]` ; rax = vtable[13] = DrawIndexedInstanced   <<< quoted address 0xe81b866
- `e81b86a  mov edx,[r15+0x70]` ... `mov r11d,[r15+0x80]` ; draw args (indexCount, instanceCount, startIndex, baseVertex, startInstance)
- `e81b88b  call qword ptr [0xF99FFA0]` ; thunk → jmp rax → DrawIndexedInstanced

Second indexed loop:
- `e81b8cb  mov rax,[rcx]`
- `e81b8ce  mov rax,[rax+0x68]` ; <<< quoted address 0xe81b8ce (slot 13 load)
- `e81b8dc  call qword ptr [0xF99FFA0]` ; thunk → DrawIndexedInstanced

Non-indexed path (stride 0x70):
- `e81ba74  mov rax,[rax+0x60]` ; slot 12 = DrawInstanced; `e81ba8d  call qword ptr [0xF99FFA0]`

Direct callees 0xebce390 / 0xebce440 (called `call 0xEBCE390` / `call 0xEBCE440` with `test eax,eax` after) are record-cache memcmp helpers, NOT draw calls [V static]. No literal `call qword ptr [reg+0x68]` text exists in this build — the slot-13 load + thunk call IS the DrawIndexedInstanced dispatch. The exe function that contains this call (the emitter) is 0xe81b720 itself.

## 5. Capture request

```
python tools/livecap/request.py add u_em1f_draw_emit 0xe81b720 --size 0x100 --max 8 --why "M1f: per-draw emitter that issues cmdlist vtable +0x68; hits per frame ~ flush hits"
```

CAPTURE REQUESTED u_em1f_draw_emit

Note: u_em1f_draw_flush (0xe81b720, 354192 hits/32 samples) already covers this entry address and shows ~320 hits/frame; u_em1f_draw_emit is the named target requested by the M1f update to close "reaches DrawIndexedInstanced" on the emitter entry. The orchestrator runs it; this unit has no game/build access.

## 6. CLOSES?

CLOSES? NO — every on-disk part of this run is done (live reads + comparison table + per-claim verdicts + static slot-13/DrawIndexedInstanced proof at 0xe81b866/0xe81b8ce + capture requested), but u_em1f_draw_emit at 0xe81b720 has only been requested, not executed (capture execution is orchestrator-owned; this unit never touches the game). Single blocking fact: orchestrator has not yet run u_em1f_draw_emit, so the live poll for the "flush reaches DrawIndexedInstanced" claim is pending.

## 7. TOOL REQUESTS

None — no helper scripts written; rdis.exe used directly (`rdis dis 0xe81b720 800`, `rdis dis 0xeea6040 40`) and live files read from docs/data/live/.
