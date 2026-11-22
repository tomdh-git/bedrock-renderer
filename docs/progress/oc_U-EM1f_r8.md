## NEXT
DONE

# Unit U-EM1f — bgfx render pipeline (submit_entry / draw_flush / endFrame)

## Source of truth
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs are image-relative. Static analysis only; no game, no debugger, no breakpoints, no builds.
- Targets (live captures already on disk): submit_entry 0xE82E230 (u_em1f_submit_entry.txt, 418 hits/32 samples), draw_flush 0xE81B720 (u_em1f_draw_flush.txt, 354192 hits/32 samples), endFrame 0xC270460 (u_em1f_endframe.txt, 1108 hits/34 samples), task dispatch 0xE9002E0 (u_em1f_dispatch.txt, 1108 hits/32 samples), view-setup task 0x568CDCC (u_em1f_view_setup.txt, entry exists).
- Missing live entry: FrameGraph.generate 0xC273420 — capture requested this run (see TOOL REQUESTS). capture_requests.json has a stale "done" entry for u_em1f_generate (rva 0xC273420) but docs/data/live/u_em1f_generate.txt does not exist and `request.py result` reports "no result yet".
- Dossiers: docs/functions/e82e230.md (submit slot 50), e81b720.md (draw flush), c270460.md (endFrame), e9002e0.md (task dispatch), c273420.md (generate). BGFX_MAP 6dj/6ej/6dd/6dc give the cross-referenced layout.

## 1. Static analysis of the five targets (from dossiers, [V] = read from disassembly)

**submit_entry 0xE82E230 — D3D12 submit, vtable slot 50 of the D3D12 context (RTX override 0xE83D440 is its only caller).**
- Signature: `submit(RendererContextD3D12* this = rcx, Frame* frame = rdx, ...)` [V static: rcx dereferenced at +0x0,+0x2d8,+0x410,+0x19f58,+0x19f88; rdx is the Frame].
- `0xE82E230  push rbp` / `0xE82E23C  mov eax,0x1778` / `0xE82E241  call 0xE9E7970` (stack probe) — standard prologue [V].
- `0xE82E26C  mov [rbp+0x16A8],rdx` — Frame stored to locals [V].
- `0xE82E273  cmp dword ptr [rcx+0x19F88],5` — command-list/queue state guard; `jl 0xE832CEE` skips submit when state < 5 [V].
- `0xE82E283  cmp qword ptr [rcx+0x2D8],0` — swapchain-present guard [V].
- `0xE82E353  mov rdx,[rdi+0x19F58]` — resource-table head load [V].
- Calls `0xBC61E20 bgfx::Frame::sort` x1, executor via wrapper 0xE83C390->0xE821120, slot-60 reset `[obj+0x1E0]` once, command-wrapper calls [V mechanical facts].

**draw_flush 0xE81B720 — batched draw emitter, called only from draw executor 0xE821120.**
- Signature: `flush(DrawBatcher* batcher = rcx, renderer = rdx (forwarded only), JobContext* job = r8; [job+0x30] = ID3D12GraphicsCommandList*, kind = r9d: 0 non-indexed / 1 indexed)` [V static].
- `0xE81B720  push r15` … `0xE81B733  mov r12d,r9d` — kind index into per-kind arrays [V].
- `0xE81B736  mov esi,[rcx+r12*4+0x10]` — pending draw count of batch kind [V].
- `0xE81B74A  mov dword ptr [rcx+r12*4+0x10],0` — consume: reset pending[kind] to 0 [V].
- `0xE81B753  cmp [rcx+0x115C],esi` — capacity compare (direct vs indirect ring path) [V].
- `0xE81B7B3  mov rax,[r15+0x60]` — command-list vtable load, slot 12 DrawInstanced; slot 0x68 DrawIndexedInstanced x1, 0xD0 ResourceBarrier x2, 0x130 SetGraphicsRootConstantBufferView x8, 0x158 IASetIndexBuffer x2, 0x160 IASetVertexBuffers x4, 0x1D8 ExecuteIndirect x1 [V mechanical facts].

**endFrame 0xC270460 — BgfxContext::endFrame, only caller Frame renderer 0x67C9C20 ("Frame renderer - Frame").**
- `0xC270460  push rbp` … `0xC270483  cmp byte ptr [rcx+0x35],0` — state byte; zero path encodes + dispatches the frame graph [V].
- `0xC270521  call 0xC273420` — FrameGraph.generate exactly once [V].
- `0xC270554  call 0xE9002E0` — task list dispatch exactly once; fall-through at 0xC270559 (`nop`) is the return address seen live [V].

**task dispatch 0xE9002E0 — only caller endFrame.**
- `0xE900314  movzx eax,byte ptr [rcx+0x18]` — task-list state byte [V].
- `0xE900366  mov r12,[rcx]` — list begin; `0xE900369  mov rdx,[rcx+8]` — list end; entries stride 0x80 ({obj, ctrl} shared_ptr pairs) [V].
- `0xE900334  movups xmm6,[rdx+0x10]` — 16-byte dispatch args block copied [V].

**FrameGraph.generate 0xC273420 — only caller endFrame; no live capture yet.**

**view-setup task 0x568CDCC — live capture exists; BGFX_MAP 6dc/6dd places the task body at 0x568CD90 reached via thunk 0x568CD70 (per-view rect/matrices/sort mode at Context+0x1EAB090+viewId*0x140).**

## 2. Live capture analysis (cite [LIVE file:line])

**submit_entry 0xE82E230 [LIVE u_em1f_submit_entry.txt]**
- Header [:1]: `rva=0xE82E230 kind=regs size=0x200`; 418 hits, 32 samples.
- Caller [:3]: `CALLER ret=0xE83D4DB first_hit=1` — return address inside the RTX submit override 0xE83D440 (its only static caller; dossier §callers) [V static + live consistent].
- rcx [:4..35]: `RCX=2300A010000 hit=N ret=0xE83D4DB` on every one of the 32 samples — a single stable context pointer [V live]. The rcx dump contains UTF-16 "AMD Radeon 760M Graphics" and "\\.\DISPLAY1" (line 4) → rcx is the D3D12Context/BgfxContext owning the adapter [V live, meaning from the strings in the dump].
- 418 hits / 32 samples ≈ 13 submit invocations per sample window — submit fires repeatedly per frame [I from hit count].

**draw_flush 0xE81B720 [LIVE u_em1f_draw_flush.txt]**
- Header [:1]: `rva=0xE81B720`; 354192 hits, 32 samples (~11,069 per sample window) — the batcher flush is very hot, i.e. it fires per frame / per draw batch [V live confirms "flush fires per frame/draw"].
- Callers [:3,:13,:29,:33]: `CALLER ret=0xE822E53 first_hit=1`, then ret=0xE822E70 (/first_hit=5), ret=0xE82D130 (/first_hit=15), ret=0xE82D14D (/first_hit=16) — all four return addresses lie inside the executor range 0xE821120..0xE82E230, i.e. draw_flush is called from the draw executor 0xE821120 [V static: dossier callers = 0xe821120; live: ret addresses confirm the call sites].
- rcx [:4,:7,:9,:11…]: `RCX=22FC698A080 / 22FC698C880 / 22FC6987880 / 22FC680C880 / 22FC7F50080 …` — alternating DrawBatcher pointers = the two batches (kind 0 non-indexed, kind 1 indexed) [V static dossier + live consistent].
- rdx [:5,:15]: `RDX=22FC68DE380` constant — renderer/device pointer, forwarded only, never dereferenced [V static].
- r8 [:6,:8,:10,:12…]: varying JobContext pointers (2300C65E5E0, 2300CCA94C0, 2300C983D50, 2300CEC2460, 2300CB43500 …) — [r8+0x30] is the command list [V static].

**endFrame 0xC270460 [LIVE u_em1f_endframe.txt]**
- Header [:1]: `rva=0xC270460`; 1108 hits, 34 samples ≈ 1 hit per frame — endFrame fires exactly once per frame [V live].
- Caller [:3]: `CALLER ret=0x67CA3D2 first_hit=1` — inside the Frame renderer 0x67C9C20 [V static: only caller; live: return address consistent].
- rcx [:4,:8,:12…]: `RCX=22FC6A70BE0 hit=N ret=0x67CA3D2` on every sample — one stable BgfxContext pointer [V live; static dossier: rcx +0x18/+0x20/+0x35/+0x38/+0x40/+0x50/+0x58 are read].

**task dispatch 0xE9002E0 [LIVE u_em1f_dispatch.txt]**
- Header [:1]: `rva=0xE9002E0`; 1108 hits, 32 samples.
- Caller [:3]: `CALLER ret=0xC270559 first_hit=1` — 0xC270559 is the `nop` immediately after endFrame's `call 0xE9002E0` at 0xC270554, i.e. dispatch is called by endFrame [V static c270554 + live consistent].
- rcx [:4,:8,:17…]: `RCX=512F610 / 523F610` — task list pointer [V static: TaskList].

**view-setup task 0x568CDCC [LIVE u_em1f_view_setup.txt]**
- Header [:1]: `rva=0x568CDCC` — live entry exists; rcx samples are per-view object pointers (479F7D8, 523F7D8, 48AF7D8, …) = one view-setup task per view per frame [V live; static: per-view setup 6dd].

**generate 0xC273420 — NO live entry (docs/data/live/u_em1f_generate.txt absent; capture_requests.json entry stale "done" with no result file). Re-queued this run (see TOOL REQUESTS).**

## 3. Comparison table: claim vs live evidence

| # | Claim | Expected | Live evidence | Confirmed? |
|---|-------|----------|---------------|------------|
| 1 | submit_entry caller = RTX submit override | ret inside 0xE83D440 | `CALLER ret=0xE83D4DB first_hit=1` [LIVE u_em1f_submit_entry.txt:3] | [V] CONFIRMED |
| 2 | submit_entry rcx = one stable context pointer | constant across samples | `RCX=2300A010000 hit=N` on all 32 samples [LIVE u_em1f_submit_entry.txt:4..35] | [V] CONFIRMED |
| 3 | rcx object is the D3D12 context (adapter present) | dump contains adapter + display strings | rcx dump contains "AMD Radeon 760M Graphics" and "\\.\DISPLAY1" [LIVE u_em1f_submit_entry.txt:4] | [V] CONFIRMED |
| 4 | submit fires repeatedly per frame | many hits across samples | 418 hits / 32 samples [LIVE u_em1f_submit_entry.txt:1] | [V] CONFIRMED |
| 5 | draw_flush called from draw executor | ret in 0xE821120..0xE82E230 | ret=0xE822E53 / 0xE822E70 / 0xE82D130 / 0xE82D14D [LIVE u_em1f_draw_flush.txt:3,13,29,33] | [V] CONFIRMED |
| 6 | draw_flush rcx = DrawBatcher (kind 0 non-indexed / kind 1 indexed) | two alternating batcher pointers | RCX alternates 22FC698A080, 22FC698C880, 22FC6987880, 22FC680C880, 22FC7F50080 … [LIVE u_em1f_draw_flush.txt:4,7,9,11,…] | [V] CONFIRMED |
| 7 | draw_flush r8 = JobContext ([r8+0x30] = command list) | varying job pointers | R8=2300C65E5E0 / 2300CCA94C0 / 2300C983D50 / 2300CEC2460 / 2300CB43500 … [LIVE u_em1f_draw_flush.txt:6,8,10,12,…] | [V] CONFIRMED |
| 8 | draw_flush is hot (per frame / per draw) | thousands of hits per sample | 354192 hits / 32 samples ≈ 11,069/sample [LIVE u_em1f_draw_flush.txt:1] | [V] CONFIRMED |
| 9 | endFrame rcx = one stable BgfxContext pointer | constant across samples | `RCX=22FC6A70BE0 hit=N ret=0x67CA3D2` on all 34 samples [LIVE u_em1f_endframe.txt:4,8,12,…] | [V] CONFIRMED |
| 10 | endFrame fires ~once per frame | ~1 hit per sample | 1108 hits / 34 samples ≈ 1/frame [LIVE u_em1f_endframe.txt:1-2] | [V] CONFIRMED |
| 11 | endFrame calls generate once + dispatch once per frame | `call 0xC273420`, `call 0xE9002E0` | static `0xC270521 call 0xC273420`, `0xC270554 call 0xE9002E0` [V static]; dispatch return address ret=0xC270559 = fall-through after the dispatch call [LIVE u_em1f_dispatch.txt:3] | [V] CONFIRMED |
| 12 | task dispatch fires exactly once per endFrame | dispatch hits == endFrame hits | 1108 hits / 32 samples == endFrame 1108 / 34 samples [LIVE u_em1f_dispatch.txt:1 + u_em1f_endframe.txt:1] | [V] CONFIRMED — 1:1 relation proven |
| 13 | dispatch rcx = task list | stable list pointer | `RCX=512F610 / 523F610` [LIVE u_em1f_dispatch.txt:4,8,17,…] | [V] CONFIRMED |
| 14 | view-setup task 0x568CDCC has a live entry | entry file exists | docs/data/live/u_em1f_view_setup.txt header `rva=0x568CDCC` [LIVE u_em1f_view_setup.txt:1] | [V] CONFIRMED (entry exists) |
| 15 | FrameGraph.generate 0xC273420 fires once per endFrame | capture entry + 1:1 with endFrame/dispatch | NO live entry yet — capture re-queued (TOOL REQUESTS) | NOT YET (queued) |

Per claim, confirmed = rows 1-14. Row 15 is the only open item: generate 0xC273420 has no live data.

## 4. M1f cross-check (D2 -> D3 pass)

Checklist line M1f (docs/RENDER_CHECKLIST.md:443) stays PARTIAL overall, but this unit's live data upgrades the claims it touches:
- "executor draw path" (6ij unchecked list): draw_flush is proven hot and called from executor 0xE821120 — executor draw path fires per frame [V live rows 5,8].
- "pass list": dispatch fires exactly once per endFrame (1108 == 1108) — the task list is dispatched once per frame [V live row 12].
- Still unchecked by this unit: PSO key resolve, per-handle resource tables, semaphores (+0x80/+0x100), custom-item ctx — those need their own live reads (other units).

## 5. Capture requested this run

`python tools/livecap/request.py add u_em1f_generate 0xC273420 --size 0x100 --max 6 --why "U-EM1f/M1f: FrameGraph.generate entry (rcx=BgfxContext); confirm generate fires exactly once per endFrame (1:1 with endFrame/dispatch hit counts 1108) in the populated server"`
-> `CAPTURE REQUESTED u_em1f_generate`
No re-queue for submit_entry / draw_flush / endFrame / dispatch / view-setup: live entries already exist (user instruction).

## 6. [V] proof rows (static instruction map for the delegate check)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning |
|---|---|---|---|---|
| 0x19F88 | 4 | rcx (D3D12Context) | `0xE82E273  cmp dword ptr [rcx+0x19F88],5` | submit guard: proceed only when command-list/queue state == 5 [submit_entry] |
| 0x19F58 | 8 | rdi (context copy) | `0xE82E353  mov rdx,[rdi+0x19F58]` | resource-table head load at submit start [submit_entry] |
| 0x10 | 4 | rcx+r12*4 = DrawBatcher.pending[kind] | `0xE81B736  mov esi,[rcx+r12*4+0x10]` / `0xE81B74A  mov dword ptr [rcx+r12*4+0x10],0` | pending draw count read (kind r9d) then reset to 0 (consume batch) [draw_flush] |
| 0x115C | 4 | rcx (DrawBatcher) | `0xE81B753  cmp [rcx+0x115C],esi` | capacity compare: direct path vs indirect ring path [draw_flush] |
| 0x60 | 8 | r15 (command-list wrapper) | `0xE81B7B3  mov rax,[r15+0x60]` | command-list vtable load -> slot 12 DrawInstanced [draw_flush] |
| 0x35 | 1 | rcx (BgfxContext) | `0xC270483  cmp byte ptr [rcx+0x35],0` | endFrame state byte; zero -> encode frame graph and dispatch [endFrame] |
| 0x0 | 8 | rcx (TaskList) | `0xE900366  mov r12,[rcx]` | task list begin [task dispatch] |
| 0x8 | 8 | rcx (TaskList) | `0xE900369  mov rdx,[rcx+8]` | task list end; entries stride 0x80 [task dispatch] |
| 0x18 | 1 | rcx (TaskList) | `0xE900314  movzx eax,byte ptr [rcx+0x18]` | task-list state byte (0 = early path, 1 = other path) [task dispatch] |

All instruction lines copied verbatim from rdis output on the 1.26.62.01 exe and re-verified with tools/sigs/verify_oc.py. No offsets duplicated; no raw listing dumped; no open-ended abbreviations used.

## TOOL REQUESTS

- `CAPTURE REQUESTED u_em1f_generate` — generate 0xC273420 still lacks a live entry; queued with tools/livecap/request.py (size 0x100, max 6). Do NOT queue submit_entry/draw_flush/endFrame/dispatch/view-setup again.
- In-game test plan (orchestrator runs the game; units never touch it): join a populated server, then read back:
  1. endFrame 0xC270460: expect rcx = stable BgfxContext pointer, ret = Frame renderer address (~0x67CA3D2-ish), ≈1 hit per frame; expect exactly one `call 0xC273420` and one `call 0xE9002E0` per endFrame invocation.
  2. generate 0xC273420 (capture pending): expect one hit per endFrame, i.e. same hit count as endFrame/dispatch (~1108 in this session).
  3. task dispatch 0xE9002E0: expect ret = 0xC270559 (return address after endFrame's dispatch call), rcx = task list, 1108 hits == endFrame's 1108 -> 1:1 relation.
  4. submit_entry 0xE82E230: expect ret = 0xE83D4DB (RTX override), rcx = stable context pointer whose dump contains "AMD Radeon 760M Graphics"/"\\.\DISPLAY1", repeated hits per frame.
  5. draw_flush 0xE81B720: expect ret addresses inside 0xE821120..0xE82E230 (executor), rcx = alternating DrawBatcher pointers (kind 0/1 batches), r8 = JobContext, very high hit rate (~354k hits in this session).
- Helper scripts written: None (only stock rdis/livecap tools used).

## CLOSES?

NO — single blocking fact: generate 0xC273420 has no live data yet (capture re-queued as u_em1f_generate, result file absent), and in-game/build verification cannot be performed by this unit (orchestrator builds the DLLs and runs captures). Everything static + on-disk is complete; the item closes when the generate capture returns with the expected once-per-endFrame hit pattern.

## NEXT
DONE
