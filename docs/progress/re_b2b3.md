# re_b2b3 progress (B2-B3 D3D12 backend remainder)

## NEXT
- Resume: static analysis of B2-B3 anchors for 62.01 exe `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`.
- Immediate commands (rdis batch): `tools\rdis\target\release\rdis.exe "<exe>" -c "sum 0xe82d960; sum 0xe8360f0; sum 0xe818490; sum 0xe81a610; sum 0xe817880; sum 0xe83ec70; sum 0xe83e200"` then targeted `decide/cfg/path/rw/struct/uses` on smallest high-value functions.
- Half-done: initial context read only (AGENT_BRIEF, tools/README, RENDER_CHECKLIST B2/B3, key dossiers). Need concrete facts for command list/queue management, descriptor heaps, residency/barriers, copy queues; write dossiers in docs/functions/<rva>.md and append evidence here.

## Progress log

### START - OPEN (context gathered)
- [V] Read `docs/AGENT_BRIEF.md`, `tools/README.md`, `CLAUDE.md`, `docs/RENDER_CHECKLIST.md` (A/B/C/D/K sections visible), `docs/BGFX_MAP.md` header/early sections, dossiers `docs/functions/e821120.md`, `e82e230.md`, `e82d960.md` (stub), `e818490.md` (retire/drain), `e81a610.md` (reset slot 60). [V] `graphify` CLI not on PATH but `graphify-out/` exists (skipped query tool; used direct docs/grep).
- [V] Known B2/B3 anchors from prompt: executor 0xe821120, submit 0xe82e230, per-view setup 0xe818490, state transition 0xe82d960, swapchain create/reset/present paths. **CONTRADICTS prompt/anchor label**: `docs/functions/e818490.md` describes "frame retire / deferred-release drain (renderer slot 49 region 'pre-submit step')" with callers incl. submit/0xe807ff0 and fence/ring/deferred-release logic, not per-view setup. Needs re-verification in this pass (audit note).
- [V] B2/B3 open items per checklist: B2b/B2c/B2d partially [x] table-evidence but many slots/descriptors not fully dossiered; B3a stage map partial, B3b descriptor binding/flush/sort-key partial, B5 PSO cache, B6 queue wrapper/fence wait, B7b transition helper, B7c upload/copy paths/slot56, B10c TLAS/BLAS call sites, B2? descriptor heaps/root sig details.
- Next unit: run rdis summaries on 0xe82d960, 0xe8360f0, 0xe818490, 0xe81a610, 0xe817880, slot 6/present/reset related small functions; then decode barrier helper and upload ring/copy queue relevance first.
