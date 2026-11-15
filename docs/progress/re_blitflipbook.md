# Progress: R3 BlitFlipbook (agent "re_blitflipbook")

## NEXT
- DONE for R3 BlitFlipbook core recovery in this pass: description 0x20 and element 0x40 layout/reads verified; dossiers and report written. Remaining follow-ups for lead/other passes (not done here, per brief): reconcile `src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h` and `docs/data/layout_asserts.json` 0xA0 entries for BlitFlipbook against verified 0x20 (see contradictions), fold proposed BGFX_MAP/RENDER_CHECKLIST updates, and confirm producer-side meanings of unread element fields `+0x28..+0x30/+0x34/+0x3C` and desc `+0x00` SharedRef target if needed.

## Progress log
- Read required docs: `docs/AGENT_BRIEF.md`, `tools/README.md`, plus context (`CLAUDE.md`, `docs/BGFX_MAP.md` 6ih/6ee, `docs/RENDER_CHECKLIST.md` R3/M2c/D7c/L4s, `docs/progress/descriptions.md`, `docs/data/producer_fields.txt`, `docs/functions/insert_thin_clones.md`, `docs/functions/group_visitors.md`, existing headers/assert files).
- Static tool evidence gathered from target exe `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe` via `tools\rdis\target\release\rdis.exe`:
  - `rdis sum 0x5acbe20`, `rdis sum 0x5aca680`, `rdis sum 0x5acb9c0`
  - `rdis dis` slices of Effect visitor `0x666aca0` including case 1 entry `0x666aec2`, shared tail/loop setup `0x666b67c/0x666b6f0+`, and element loop `0x666b704..0x666c846`
  - range-bounded search over loop disassembly for `[r14+0x28/2c/30/34/38/3c]` (none found)
- Wrote dossiers: `docs/functions/5acbe20.md`, `docs/functions/5aca680.md`, `docs/functions/5acb9c0.md`, `docs/functions/666aca0_blitflipbook.md`.
- SDK/header/assert state audited: `src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h` already defines `RenderBlitFlipbookDescription` as 0x20 with 0x40 `Element` matching recovered layout [V]; no additive framebuilder header edits required. `src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h` and `docs/data/layout_asserts.json` still contain 0xA0 for BlitFlipbook [CONTRADICTION noted, not edited by this agent beyond report].

## R3 - BlitFlipbook (Effect group tag 1) - DONE [V layout/consumer-reads] / OPEN [field semantics partial]
**Status:** DONE for requested layout recovery of description (incl. 0x40-byte element bytes previously claimed unread) and verified consumer reads in the Effect case-1 element loop; OPEN only for some semantic meanings (not layout/offset correctness) and external doc/assert reconciliation owned elsewhere.

### Key RVAs and roles [V/I]
- Thin insert clone: `0x5acbe20` (0x139, Effect group vtbl slot 108 / +0x360, tag 1). Passes `{desc_ptr, tag=1}` only; no desc reads. [V] `docs/functions/5acbe20.md`
- Producer/insert path: `0x5aca680` (`vtbl_f276200#5`) builds stack description, emplaces elements via `0x5acb9c0 @0x5acb1c6`, builds desc SharedRef via `0x4dfb570 @0x5acb24f`, stores desc span `{count,data}` at desc `+0x10/+0x18`, inserts via `0x5acbe20 @0x5acb267`. [V] `docs/functions/5aca680.md`
- Element emplace/copy helper: `0x5acb9c0` copies full 0x40-byte element, increments strong refcount on `src+0x10` control block when non-null (`inc [ctrl+8]`), advances destination by 0x40. [V] `docs/functions/5acb9c0.md`
- Effect visitor: `0x666aca0`; case 1 entry `0x666aec2` resolves `"Flipbook"` material via `0x675e440` (`[r12+0x40]/[r12+0x68]`), then shared tail iterates elements from desc `+0x10/+0x18` in loop `0x666b704..0x666c846` (`r14` element, stride 0x40). [V] `docs/functions/666aca0_blitflipbook.md`, `docs/functions/group_visitors.md`

### Description layout (verified) [V]
- **Size 0x20** (not 0xA0). [V]
- `+0x00` `SharedRef mRef00` (0x10) - built by `0x4dfb570` in producer. [V type/placement, ? target meaning]
- `+0x10` `u64 mCount` (0x08) - element count used by consumer loop bound (`[r15+0x10]`). [V]
- `+0x18` `Element* mElements` (0x08) - element array base (`[r15+0x18]`). [V]

Evidence: `rdis sum 0x5aca680` (stores + call to `0x5acbe20(&desc)`), `rdis dis 0x666aca0` slices around `0x666b6cf..0x666b704` (`mov rax,[r15+0x10]; mov r14,[r15+0x18]; shl rax,6; add rax,r14`), `rdis sum 0x5acbe20` (pointer passthrough only).

### Element layout (0x40 bytes, verified) [V]
Copied in full by `0x5acb9c0` (fast and slow paths): [V]
- `+0x00` qword `mValue00` - object/mesh handle; consumer does `mov rsi,[r14]` and passes/inspects as mesh-like object (`@0x666b942`, later uses). [V read/use, I name/meaning]
- `+0x08` `SharedRef mRef08` `{ptr,ctrl}` (0x10) - copied and control block strong-ref incremented when present; consumer passes element+0x08 address to `sub_bcaba00` (`lea r8,[r14+8] @0x666b858`). [V]
- `+0x18` qword (blend XY) - `movsd xmm1,[r14+0x18] @0x666b897`. [V]
- `+0x20` dword/float (blend Z) - `movss xmm0,[r14+0x20] @0x666b891`. [V]
- `+0x24` 16 bytes - `movups xmm0,[r14+0x24] @0x666ba25` (consumer reads 16-byte block starting at +0x24). [V]
- `+0x28` float - copied by helper; **no read observed in loop `0x666b704..0x666c846`**. [V stored, V absent in loop, ? meaning]
- `+0x2C` float - copied by helper; no read observed in loop. [V stored, V absent, ?]
- `+0x30` float - copied by helper; no read observed in loop. [V stored, V absent, ?]
- `+0x34` qword (unaligned copy span in helper) - copied by helper; no read observed in loop. [V stored, V absent, ?]
- `+0x3C` byte (+3 pad to 0x40) - copied by helper; no read observed in loop. [V stored, V absent, ?]

### Consumer read verification (range-bounded) [V]
- Verified loop: `0x666b704 cmp r14,[rbp+0x660]; je 0x666c846` with step `0x666b700 add r14,0x40`.
- Confirmed reads inside loop: `[r14]`, `[r14+8]` (address), `[r14+0x18]`, `[r14+0x20]`, `[r14+0x24]`.
- `tools\rdis\target\release\rdis.exe ... -c "dis 0x666b704 0x666c846"` searched for `r14+0x28/2c/30/34/38/3c`: none found. [V]
- Audit note: broader `descscan.py`-style ranges can attribute reads after register reuse/outside this case loop (checkpoint noted hits at `0x666dacd+` beyond end `0x666c846`); such reads must not be attributed to BlitFlipbook elements without range proof. [I]

### Files created/edited
- Created: `docs/functions/5acbe20.md`, `docs/functions/5aca680.md`, `docs/functions/5acb9c0.md`, `docs/functions/666aca0_blitflipbook.md`, `docs/progress/re_blitflipbook.md`.
- Edited: none in `src/` or `docs/data/layout_asserts.json` (existing framebuilder header already matches verified 0x20/0x40 layout; assert-file corrections are non-additive and/or outside permitted framebuilder-header scope).

### Contradictions / audit
- **CONTRADICTS 6ih / older claims:** `RenderBlitFlipbookDescription` is **0x20 bytes** `{SharedRef, u64 count, Element*}` [V], not 0xA0. Prior 0xA0 inference likely came from over-wide producer stack-store windows (`docs/data/producer_fields.txt`) not bounded to the actual description object passed to `0x5acbe20`. [I]
- **CONTRADICTS `src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h`:** `kVisitEffect` asserts `{0xA0, "sizeof(RenderBlitFlipbookDescription)"}` but verified size is 0x20. [V evidence vs current assert]
- **CONTRADICTS `docs/data/layout_asserts.json`:** `FrameBuilder::visitEffect` contains `{"value":"0xa0","backs":"sizeof(RenderBlitFlipbookDescription)"}` but verified size is 0x20. [V evidence vs current entry]
- `docs/progress/descriptions.md` R3 entry states size 0x20 and element 0x40; this pass confirms/corroborates that with explicit function-level evidence and loop-bounded consumer read verification. [V]
- `src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h` currently matches verified 0x20/0x40 layout and offsets (including `+0x34/+0x3C` stored fields) [V]; semantic naming of all element fields remains partly inferred. [I/?]

### Final report
- **DONE:** R3 BlitFlipbook description/element recovery sufficient for layout claims: desc 0x20, element stride 0x40, verified producer build/insert path and element copy, verified consumer loop reads of `+0x00,+0x08(addr),+0x18,+0x20,+0x24` within `0x666b704..0x666c846`, and verified absence of `+0x28..+0x3C` reads in that loop despite bytes being present/copied.
- **OPEN:** precise semantic names/meanings for element `+0x00`, `+0x24` subfields, and stored-but-unread `+0x28..+0x30,+0x34,+0x3C`; meaning of desc `+0x00` SharedRef target; full decomp of producer `0x5aca680`; reconciliation/update of non-framebuilder assert/docs artifacts (`RenderLayoutAsserts.h` 0xA0, `layout_asserts.json` 0xA0, BGFX_MAP/RENDER_CHECKLIST entries) by lead process.
- **Blockers:** none preventing static recovery/dossiering of R3 layout and consumer-read facts. No live polling/debugger actions performed.

## FULL PROPOSED BGFX_MAP ENTRY TEXT
```md
### 6ih R3 BlitFlipbook (Effect group, tag 1) - 1.26.62.01 (static, 2026-11-15) [V layout/reads, I semantics partial]

- Thin insert clone: `0x5acbe20` (0x139, D2) dispatches Effect vtbl `+0x360` (slot 108) with variant `{description*, tag=1}`; clone reads no description fields. [V] (`docs/functions/5acbe20.md`)
- Producer/insert path: `0x5aca680` (`vtbl_f276200#5`) builds stack description at insert callsite, appends 0x40-byte elements via `0x5acb9c0 @0x5acb1c6`, constructs `+0x00` SharedRef via `0x4dfb570 @0x5acb24f`, stores span `{count,data}` at `+0x10/+0x18`, then calls `0x5acbe20 @0x5acb267`. [V] (`docs/functions/5aca680.md`)
- Element copy/emplace: `0x5acb9c0` copies the full 0x40-byte element (qwords/SharedRef/floats/byte including `+0x34` and `+0x3C`) and increments strong refcount on `src+0x10` control block when present (`inc [ctrl+8]`), advancing storage by 0x40. [V] (`docs/functions/5acb9c0.md`)
- Effect visitor consumer: `0x666aca0` case 1 (`0x666aec2`) resolves `"Flipbook"` material via `0x675e440` (`[r12+0x40]/[r12+0x68]`), then shared tail iterates elements from description `+0x10 (u64 count)` / `+0x18 (Element*)`, stride 0x40, loop `0x666b704..0x666c846`. [V] (`docs/functions/666aca0_blitflipbook.md`, `docs/functions/group_visitors.md`)

**RenderBlitFlipbookDescription layout (verified, size 0x20):** [V]
- `+0x00` `SharedRef mRef00` (ptr, ctrl) - producer-built via `0x4dfb570` [V placement/type; ? semantic target]
- `+0x10` `u64 mCount` - element count used for loop bound [V]
- `+0x18` `Element* mElements` - contiguous element array base [V]

**Element layout (verified copied size 0x40):** [V copy; consumer reads noted]
- `+0x00` qword `mValue00` - mesh/object handle used by consumer (`mov rsi,[r14]`, passed to mesh/setup helpers) [V read/use, I meaning]
- `+0x08` `SharedRef mRef08` (ptr, ctrl) - refcounted copy; consumer passes `&element+0x08` to `sub_bcaba00` [V]
- `+0x18` qword `mBlendXY` - consumer `movsd xmm1,[r14+0x18]` [V]
- `+0x20` dword/float `mBlendZ` - consumer `movss xmm0,[r14+0x20]` [V]
- `+0x24` 16-byte block - consumer `movups xmm0,[r14+0x24]` [V read start; ? subfield semantics]
- `+0x28` float, `+0x2C` float, `+0x30` float - copied/stored [V], no read observed in BlitFlipbook loop `0x666b704..0x666c846` [? meaning]
- `+0x34` qword - copied/stored [V], no read observed in loop `0x666b704..0x666c846` [? meaning]
- `+0x3C` byte (+pad to 0x40) - copied/stored [V], no read observed in loop `0x666b704..0x666c846` [? meaning]

**Audit/corrections:** [V/I]
- CONTRADICTS prior 6ih text claiming description size 0xA0 and "element +0x34..+0x3F unread" as if absent from layout: description is 0x20 [V], and element bytes through `+0x3C` are present/copied [V] though `+0x28..+0x3C` were not observed read in the verified case-1 loop range.
- `src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h` and `docs/data/layout_asserts.json` currently assert BlitFlipbook description as 0xA0 in `FrameBuilder::visitEffect`; these require reconciliation to 0x20 with a code-immediate anchor if applicable (lead-owned assert update). Current framebuilder SDK header `Descriptions.h` already reflects 0x20/0x40 layout [V].
```
