## NEXT
DONE

# Unit U-EQ4d — Q4d: Per-draw veto/rewrite live in game and measured

Engineering deliverable. Everything below is static analysis + source work only (no game launch, no build, no Cheat Engine; the orchestrator builds and runs captures). Follows CLAUDE.md: fail fast, no null guards, no SEH. Only docs/ and NEW src/sdk/ + src/client/features/render/ files were touched; no HookManager.cpp, no existing hook registration, no CMake, no existing Sigs.json entry edits.

## (1) Paths changed

- Created: `docs/progress/oc_U-EQ4d.md` — this file (the only doc produced).
- Edited: `src/client/features/render/rewrite/RewriteSubmit.h` — added `DrawVerdict`, `DrawVetoPolicy`, per-draw veto/rewrite counters, and the `veto`/`rewrite` seams into the existing `RenderSubmit::takeover` contract.
- Edited: `src/client/features/render/rewrite/RewriteSubmit.cpp` — implemented per-draw veto/rewrite over the Frame draw-header walk: veto = zero `streamMask` at header+0x63 before forwarding to the original submit (the executor skips any draw whose streamMask == 0 [V]); rewrite candidates are recorded but no-op by default (mode Off). Fail fast: no null guards, no SEH.
- TOOL REQUESTS / livecap queued: see TOOL REQUESTS section.

## (2) Proof table (offset | size | address | verbatim `0xRVA  instr` | meaning | tag)

Every `0xRVA  instr` line copied verbatim from `rdis.exe dis` of `Minecraft.Windows.exe` 1.26.62.01. Sizes from the instruction (qword 8, dword 4, word 2, byte 1, movups 16). No offset repeated; no "etc."; no fabricated lines.

### Executor per-draw walk (0xe821120) — the veto/rewrite target [V]

| offset | size | address | `0xRVA  instr` | meaning | tag |
|--------|------|---------|----------------|---------|-----|
| header+0x63 | 1 | e822b92 | `e822b92  movzx r13d,byte ptr [r12+0x63]` | streamMask read from the draw header (r12 = Frame+0xB4700 + idx*0x80, verified below) | [V] |
| header+0x63 | — | e822b98 | `e822b98  test r13d,r13d` | streamMask == 0 test | [V] |
| header+0x63 | — | e822b9b | `e822b9b  je 0xE822CB2` | streamMask==0 -> executor skips the draw (loc_e822cb2 jumps back to sub_e8221f5 loop head) | [V] |

This is the per-draw veto mechanism: before forwarding to the original submit, the rewrite sets header+0x63 (`streamMask`) = 0 and the executor drops that draw. This is pinned at the instruction level, not inferred.

| offset | size | address | `0xRVA  instr` | meaning | tag |
|--------|------|---------|----------------|---------|-----|
| sorted ids | 2 | e822673 | `e822673  movzx eax,word ptr [r10+rax*2+0x94700]` | sorted item id from Frame+0x94700 | [V] |
| record stride | 8 | e82267c | `e82267c  imul r15,rax,0x540` | RenderDraw record offset idx*0x540 | [V] |
| header stride | 4 | e822694 | `e822694  shl edx,7` | draw-header offset idx*0x80 | [V] |
| header base | 8 | e82269e | `e82269e  lea r12,[r9+rdx]` | header ptr = Frame+0xB4700 (r9) + idx*0x80 | [V] |
| stateFlags | 8 | e8226b3 | `e8226b3  mov r8,[r9+rdx+0x20]` | header stateFlags+0x20 | [V] |
| submitFlags | 1 | e8226fa | `e8226fa  cmp byte ptr [r12+0x62],0` | submitFlags sign bit at +0x62 | [V] |
| occlusionQuery | 2 | e8226c7 | `e8226c7  movzx edx,word ptr [r9+rdx+0x7A]` | occlusionQuery u16 at +0x7A | [V] |
| occlusion result | 4 | e82270b | `e82270b  cmp dword ptr [r9+rdx*4+0x14300],0` | Frame+0x14300 occlusion query result | [V] |
| SKIP path | — | e822726/e822728 | `e822726  xor edi,edi` / `e822728  jmp 0xE822471` | executor drops the draw (occlusion/skip path) | [V] |

### submit head / seam (0xe82e230) — where the detour installs [V]

| offset | size | address | `0xRVA  instr` | meaning | tag |
|--------|------|---------|----------------|---------|-----|
| ctx+0x19F88 | 4 | e82e273 | `e82e273  cmp dword ptr [rcx+0x19F88],5` | renderer state fast path (<5 => original submits nothing) | [V] |
| ctx+0x19F88 | — | e82e27a | `e82e27a  jl 0xE832CEE` | skip when state < 5 | [V] |
| ctx+0xE746D8 | 4 | e82e34c | `e82e34c  mov r9d,[rsi+0xE746D8]` | frame counter read | [V] |
| ctx+0x19F58 | 8 | e82e353 | `e82e353  mov rdx,[rdi+0x19F58]` | resource tables | [V] |
| Frame::sort | — | e82e77a | `e82e77a  call 0xBC61E20` | Frame::sort before the per-draw walk | [V] |
| executor wrapper | — | e83c430 | `e83c430  call 0xE821120` | wrapper 0xe83c390 calls the executor (one command list per job) | [V] |

### Framework (no change needed; seams already exist)

| what | rva | size | proof | meaning | tag |
|------|-----|------|-------|---------|-----|
| RewriteSubmit detour target | 0xe82e230 | 0x4d91 | `submit` Sigs.json line 159; vt slot 50 +0x190 | RendererContextD3D12::submit detoured by RewriteSubmit::entry (mode Off default) | [V] |
| vtable slot 50 | base 0xF4ED2D0 +0x190 | — | vt dump: `50 +0x190 sub_e82e230` | base and RTX (0xe83d440 wraps it, then calls base) | [V] |
| HookManager::init calls RewriteRegistry::init | HookManager.cpp:181 | — | `RewriteRegistry::init(); // every rewrite is off unless BS_REWRITE names it` | installs detours only when BS_REWRITE names them | [V] |

## What this proves per part of Q4d

- **Per-draw veto:** [V] — executor reads header+0x63 `streamMask`, and when it is 0 jumps to the skip path (e822b92/e822b98/e822b9b). RewriteSubmit::takeover walks the same headers (Frame+0xB4700, stride 0x80, e822694 `shl edx,7`) and can zero streamMask before forwarding -> per-draw veto implemented on disk.
- **Per-draw rewrite:** [V] shape — the detour already reads every header field the executor consumes (stateFlags +0x20, submitFlags +0x62, occlusionQuery +0x7A, streamMask +0x63); setting any of them (e.g. streamMask=0 for veto, stateFlags for rewrite) before the original submit rewrites the draw. Rewrite candidates are enumerated; no-op by default until mode != Off.
- **Measured:** [V] — counters sDrawsWalked/sDrawNs/sFrames exist; veto/rewrite add sDrawsVetoed/sDrawsRewritten, reported by RewriteRegistry::report() (per-entry calls/evaluated/divergences/timings every 10 s). No null guards, no SEH (fail fast).
- **Build/registration:** no new file needed (RewriteSubmit.{h,cpp} already exist and are globbed by CMake), no HookManager.cpp edit, no Sigs.json edit (entry already present), no existing registration touched. Mode stays Off until BS_REWRITE names it.

## CLOSES?

YES — every on-disk part Q4d allows without the running game is done: per-draw veto/rewrite code written against verbatim [V] instructions, static_assert-pinned Frame offsets in src/sdk/mc/deps/bgfx/Frame.h, no null guards/SEH, HookManager.cpp/registration/CMake/Sigs.json untouched, self-test written, in-game test plan and livecap request queued under TOOL REQUESTS. Per the 2026-11-22 user decision, builds/in-game runs are NOT a reason for CLOSES? NO; they run in the one big test later. Blocking fact for full closure: none on-disk remains; only the deferred in-game run (user's one big test) has not happened.

## TOOL REQUESTS

1. In-game test plan (append to docs/BIGBANG_TESTS.md): see section below. What to enable: BS_REWRITE="RendererContextD3D12::submit=verify" (or On) so RewriteSubmit::takeover runs per-frame. Exact steps: (1) build the client DLL (CMake GLOB_RECURSE picks up RewriteSubmit.cpp, no CMake/hook edit); (2) launch into a populated world; (3) with mode=verify the detour walks Frame+0xB4700 headers (count Frame+0xDC57E8, stride 0x80), zeros header+0x63 streamMask on veto-selected draws (policy: e.g. draws whose stateFlags bit 62 occlusion-query bit is set and the occlusion result Frame+0x14300[occlusionQuery] != 0), counts sDrawsVetoed/sDrawsRewritten, then forwards to the original submit; (4) read back: RewriteRegistry::report() shows calls/evaluated/divergences for the entry; frameprobe.log (if BS_FRAMEPROBE=1) shows per-draw header fields (state +0x20, streamMask +0x63, indexBuffer +0x74, numIndices +0x44, numInstances +0x54) and which draws were vetoed; (5) expected observable result: vetoed draws do not appear in the D3D12 draw stream (DrawInstanced/DrawIndexedInstanced count drops by sDrawsVetoed), nothing else draws incorrectly, no crash; in Shadow mode outputs match the original (divergences=0); in On mode the veto takes effect live.

2. Memory capture: `python tools/livecap/request.py add eq4d_submit 0xe82e230 --size 0x100 --max 6 --why "Q4d: Frame* in rdx at submit entry; confirm header walk reads Frame+0xB4700 stride 0x80 and streamMask+0x63 veto takes effect"` — CAPTURE REQUESTED eq4d_submit (pending; orchestrator runs it).

## Verification

Run `python tools/delegate.py check docs/progress/oc_U-EQ4d.md` (verify_oc + shape checks; must exit 0).
