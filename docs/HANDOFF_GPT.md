# Handoff: finishing the render reversal checklist (for GPT as orchestrator)

Written 2026-11-16. Read this top to bottom before touching anything. Everything here was learned the hard way; the "why" is included so you can adapt instead of cargo-culting.

## 1. What the project is and what "done" means

BlueySenseV2 is a Minecraft Bedrock client mod (C++ DLL, repo root `C:\Users\Atomi\Desktop\BlueySenseV2`). The current effort is a full static reversal of the game's rendering (Minecraft.Windows.exe **1.26.62.01**, RenderDragon/bgfx) so that every renderer layer is understood and controllable.

The single source of truth for progress is `docs/RENDER_CHECKLIST.md`. Each line is `- [ ]` (open) or `- [x]` (done). Rules the user set and enforces:

- Only `[x]` and `[ ]` exist. A "partial" item is NOT done. Do not invent `[~]`.
- An item is done only when its output is **instruction-complete reversed source**: phases of at most ~40 instructions, each with the verbatim quoted line `0xRVA  instr` (two spaces after the RVA), plus layouts (struct field tables: offset, size, direction, quoted line, meaning only if an instruction/string proves it), and `python tools/sigs/verify_oc.py FILE` clean (every quoted line matches the exe).
- Mirror pairs (D-items = L-items = R-items in the checklist) tick together when one real result covers them.
- After EVERY tick run `python tools/checklist_status.py "what changed"` (refreshes the status block at the top of the checklist).
- At the very end only: one batch release build, `graphify update .`. Commit only if the user asks. Do not repeat key values, do not touch the user's private info, never kill processes you did not start.
- Current state when this was written: **216 done / 205 open** (core 114/33). User's target for the day was ~60-70%; I told them it is not realistic, only verified items tick. Do not tick to hit a number.

Knowledge docs to keep current: `docs/BGFX_MAP.md`, `docs/functions/<rva>.md`, `docs/data/*`, SDK headers (`src/sdk/mc/...`, e.g. `Descriptions.h`, `UiEditorDescriptions.h`).

## 2. Priority order (user rule, 2026-11-16)

1. Easy single items that one unit can finish alone.
2. Easy multi-step items, sorted ascending by number of steps.
3. After that you decide by difficulty.

Plan tiers are in `docs/progress/PRIORITY.md`. Tier 4 (RTX, GPU, swapchain, needs live game) is deferred.

## 3. Division of labour

- **You (orchestrator)** do: precompute data, write prompts, review, tick, keep the pipeline full. Keep your own usage low. You may finish a tiny item yourself (a few tool calls plus a doc).
- **opencode units** (cheap models via the opencode client) do the bulk transcription/annotation. Do NOT use Claude subagents for bulk work (user rule, saves their usage limit).
- The static tools run against the exe at `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`. Check the version of any exe a tool reads (an earlier 60.05 vs 62.01 mixup shifted everything by +0xC00).
- Nothing needs the game running. Units are static-analysis only (the brief forbids debuggers, builds, git, editing src).

## 4. The delegation machinery

Bridge dir: `C:\Users\Atomi\opencode-mcp-bridge` (bun). If the bridge errors "Failed to start server", the OpenCode desktop app is not running: start `%LOCALAPPDATA%\Programs\@opencode-aidesktop\OpenCode.exe` (this was needed after a reboot), then verify with `bun run st.ts <sessionID>`.

### 4.1 Sessions
Create each unit's session with the bridge tool `oc_create_session` with `agent: "general"` and `model: "opencode/glm-5.3-flash-free"`, directory the repo root. **The agent must be `general`**: the default `build` agent is an orchestrator without write/shell tools, which was the root cause of units "bugging out" (faking files with console.log, looping). Prompts live in `docs/progress/_p_<UNIT>.txt`, the unit writes `docs/progress/oc_<UNIT>.md`.

### 4.2 Building a prompt
```
python tools/delegate.py make UNIT "goal text" DATAFILE [DATAFILE...] [--template docs/progress/_tpl_fieldmap.md]
```
Output `_p_UNIT.txt`: brief rules, input data, a template, strict completion rule. `docs/OPENCODE_BRIEF.md` holds the hard rules every unit reads (static only, no builds, [V]/[I]/[?] tags, write early, `## NEXT` at top, toolbox table, no-speculation protocol, do not use rtools MCP).

Two unit shapes work:
1. **Field map** (best): you precompute per-case reads (`python tools/sigs/casebest.py LISTING TABLE_RVA COUNT OUT` for visitor jump tables; `rdis walk <rva> --reg R`), the unit makes ONE annotated row per distinct offset using `docs/progress/_tpl_fieldmap.md`. Gate: `python tools/delegate.py check FILE` and `python tools/delegate_cov.py FILE DATAFILE REG` (reports wanted offsets missing; it parses `| 0xOFF |` style rows, so rows prefixed like `t6 0x10` look falsely missing: check by hand in that case).
2. **Listing dossier**: input is a ready listing in `docs/data/listings/*.txt`; unit writes phases + quoted lines + field table. Gate: `delegate.py check` AND an instruction-coverage script (see 5.2): `check` alone only validates the lines the unit chose to quote, it does not prove every instruction is covered.

### 4.3 The keeper (keeps units alive)
`keeper.ts` (event-driven) in the bridge dir. Start from that dir:
```
PROVIDER=opencode INITCOOL=0 MAXRUN=3 ./keeper-run.sh >> keeper.events
```
Run it with a background shell (one instance only; always check `Get-CimInstance Win32_Process | ? CommandLine -match keeper.ts` before starting another; stopping a background task does NOT kill its children, and `pkill` does not exist in this Git Bash, use `Stop-Process`).

What it does: sends "continue" to units that went idle, rotates/cools provider keys on quota failures only, auto-rejects permission requests and cancels questions, reports `DONE (file says complete)` when the unit file's `## NEXT` is followed by a line starting `DONE`, `STUCK` after 6 sends with <1500 new tokens, pauses with one wake timer when all keys are cooling. Events go to `keeper.events` / `keeper.log`; watch with a persistent Monitor on `tail -n 0 -F keeper.events | grep --line-buffered -E "DONE|STUCK|GAVE UP|EXITED|ALL KEYS|QUESTION"` (monitors expire after 30 min, re-arm).

**Queue = instant redelegation.** `keeper-queue.json` is a list of pre-created sessions `{id,name,file,promptFile}`. The keeper starts the next one when a slot frees. Quirk: it pumps only on events, so after adding to the queue or after a DONE, run `touch keeper.kick` to force a sweep. Slots: user wants **3 running at all times, optimistic: always try to keep 3**. 5 concurrent burned the shared key quota in minutes (units stuck, keys cooling), so 3 it is. Keep at least 2 units queued ahead.

Provider notes: opencode keys are pooled in `~/.config/opencode/provider-pools/opencode.json` (manage with `bun run provpool.ts list|add|use|del`; never print key values). Kilo free keys are exhausted/flaky; fallback only. curl probes of the endpoint mislead (429s) while the opencode client works: judge by the client.

## 5. How to review every result (do not skip; this is the whole point)

Units lie, skip, copy-paste tool output, and invent meanings. For each DONE:

1. `python tools/delegate.py check docs/progress/oc_<UNIT>.md` must say `CHECK OK N rows` (this runs verify_oc: every quoted line must match the exe).
2. Coverage:
   - field map: `delegate_cov.py` (or the manual check noted above); also confirm skipped offsets are stores/lea only if the data says so.
   - listing dossier: compare the set of `0xRVA` in the listing files against the set of `0xRVA  instr` quoted in the unit file. Missing instructions (it happened: one call out of 893) you add by hand or send back. Quick script pattern: regex `(0x[0-9a-fA-F]{6,8})\s{2}\S` over both.
3. Spot-check 2-3 non-trivial rows with `tools/rdis/target/release/rdis.exe <exe> dis 0xRVA 20`. Meanings (names) are accepted only if an instruction or string shows them; otherwise they must be `-`.
4. Decide whether the **checklist item's wording** is actually satisfied. Many items need more than a read map (true struct size, producer-side stores, a pass body, names). Field maps and dossiers are building blocks; tick only when the item's own text is met. Record partial progress in the item line as `| PROGRESS ... ` text (still `[ ]`).
5. If it is a mirror pair, tick all mirrored lines, then `python tools/checklist_status.py "..."`.
6. Immediately refill the queue/slot (`touch keeper.kick`).

Rejections: send the exact failures back to the same session (bridge `sendm.ts`/`say.ts`, or just rely on the keeper's "continue" plus a specific message); start a fresh unit only if the session produced nothing. Rename a rejected file (e.g. `oc_X_old_rawdump.md`) so the keeper's DONE detection cannot falsely trigger on an old file with the same name (unit file names must be unique).

## 6. Lessons (condensed; full list in `docs/progress/DELEGATION_LESSONS.md`)

- Precompute everything computable; give units a table to fill, not an investigation to run. Targeted, narrow, one function family per unit.
- Do not delegate where the producer computes the data (Clouds/Weather element arrays, stride 0x260, are decoded from the producer loop, a field map of the visitor is not enough). Forwarder cases (Item tags 3, 6, 8, 10) tail-jump to separate extractors: map those extractors separately (done: 0x66EA3D0, 0x6698E30, 0x66E75F0; BatchActor 0x66D9AF0 stores its desc at `[rbp+0x7A8]`, still to do).
- Units must create their file FIRST with `## NEXT`, append after each piece, finish with `## NEXT` then `DONE`.
- No "etc.", no summarised hot ranges, no pasted tool dumps, no subagents, no rtools MCP (it hangs), no questions.
- rdis `walk` prints hex without `0x`; normalise to `0x` before verify.
- Keep `docs/progress/units_running.txt` current.

## 7. Where things stand (2026-11-16)

Done recently: D8 (UIMesh/HudIcon/Gameface arg maps), D10 (editor visitor tags 0-7), L14d (UI tags 1-4), N4a, K-P7. Accepted field maps (building blocks, no tick yet): Light tags (oc_U-LgtA/LgtB), Item tags (ItmA/ItmB), Effect tags 1/3/5/6/7/8 (EffA/EffB), extractors for ChunkGeometry/ItemInHand/BlockSelectionOverlay (XChunk/XHand/XSel), UI tags (UiTxt/UiImg/UiSm), FullscreenEffect dossier (U-Full, 711/711), EditorHighlight dossier (U-Edh, 893/893), Clouds dossier (U-Cld, 784/784).

In flight/queued: U-Blit (BlitFlipbook), U-Wth (Weather), U-Atm (Sky atmosphere tag 0), then U-Part, U-Pvis, U-Flm. These should unlock, together with the above: L4s (Fullscreen + BlitFlipbook), D6c/L4p (Clouds, Weather, Atmosphere: needs the producer element arrays too), D9c (still 25 unverified rows; also needs GameplayMetadata and ServerGraphicsOverrideParameters), L5b/L5c/L5f (Item tags: need names + skinned clone 0x6b84e60, 2270 lines, not yet delegated), R-items (R4 true size of AimAssistHighlight, R5 meanings, R10 UIMesh true size).

Other unclaimed listings in `docs/data/listings/` (not yet referenced anywhere): atlas_meta_*, clientinstance_loadresources, effect_flame*, effect_particle*, effect_shadow_extractor*, effect_volfog_clone, imageutils_*, skinned_clone, texgroup*, texload*. Tier 2 items with ready tool output: C4b sizes, L3k flush 0x6632bf0, L1p/L1q/L1t Context offsets, I5c/I5d, F1b, F2b, G4a/G4b, H4.

Tier 3 (design/doc items you can verify yourself from existing files and tick on evidence): J2, A13, O2a/O2b/O3a/O3b, N4b/M4c, K-P9, P2a/P2b/P1d.

## 8. Operating loop (what to do each time)

1. Check keeper alive (single process), 3 units running, >=2 queued. If not, top up: make prompt, `oc_create_session` (general, glm-5.3-flash-free), append to `keeper-queue.json`, `touch keeper.kick`.
2. On each DONE event: review per section 5, tick if (and only if) the item is met, run the status script, refill.
3. On STUCK: look at the file and the last error (`lasterr.ts`, `hist.ts`, `peek2.ts` in the bridge dir); if the cause is key quota, wait for cooldown (do not add concurrency); if the prompt was too wide, split it and redelegate. After a computer restart: start the OpenCode app, then the keeper.
4. Append new lessons to `DELEGATION_LESSONS.md` so each run's prompts get more targeted.
5. When all items are `[x]`: one batch release build, `graphify update .`, then tell the user. Commit only if asked.
