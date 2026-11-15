# UIMesh FrameBuilder RE (R8 task: UIMesh description/clone/ctor/consumers)

## NEXT
- **Status: COMPLETE for requested static scope (no blockers hit).** No debugger/live patch used.
- If further work is needed later: dump variant jump table at `0xF2BF680` targets 2/3 for ctor `0x668C3C0`, and do a bounded `descscan`/disassembly of UI renderer `0x674A3A0` argument use to name semantic fields (STATIC ONLY).

## Progress log
- Read `docs/AGENT_BRIEF.md`, `tools/README.md`, `CLAUDE.md`, `docs/RENDER_CHECKLIST.md`.
- `graphify query "UIMesh FrameBuilder description clone constructor fields layout consumers"` attempted but `graphify` CLI not available in PATH on this host [I env]; fell back to doc/string/xref search as permitted by context.
- Located refs: `docs/RENDER_CATALOG.md` (`RenderUIMeshDescription`), `docs/BGFX_MAP.md` (6ee/6fu/6gd/6gn/6id context), `docs/RENDER_CHECKLIST.md` R10 ("UIMesh ... true size >=0x90, sub-objects at +0x18 and +0x88"), `docs/functions/group_visitors.md` (UI tag 2 inline), `docs/data/producer_fields.txt` (UIMesh noisy), existing headers `Descriptions.h`, `DescriptionClones.h`.
- Static RE (exe `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`):
  - `xref.py dis 0x668C3C0` + `rdis sum/dis`: constructor fully traced (stores, variant init, ref-array fill, ret this).
  - `xref.py dis 0x4C96140`, callers: thin UI insert clone, slot 0x368 tag 2.
  - `xref.py dis 0x6664A00` / case 0x6664BD6..: UI visitor tag 2 inline consumer reads and call to `0x674A3A0`.
  - `descscan.py 0x6664A00 --reg r9`: consumer field reads corroborated.
  - `producerscan.py 0x4C96140`: 4 call sites; noisy/large-frame stores beyond 0xA8 in some sites (treated as low-confidence attribution per 6id note).
  - Inspected producers/wrappers `0x4C95550/0x4C95E00`, `0x5ABB370`, `0x6C11280`, `0x6E77420`.

## Final report

### Items
- **R8 task (UIMesh FrameBuilder description/clone/ctor/fields/consumers): DONE (static D2)**. Checklist text in repo lists UIMesh as **R10** (`[ ] R10 UIMesh (UI tag 2): true size (>= 0x90), sub-objects at +0x18 and +0x88...`); task label given as R8 but scope matches R10/UIMesh. No checklist/map files edited.
- **OPEN:** semantic naming of most payload fields (values/flags/word), full C++ prototype, and variant switch cases 2/3 jump targets; D3 live/poll confirmation. (No hard blocker for static layout/clone/ctor/consumer path.)

### Evidence summary (all claims tagged)
- **[V] Clone/dispatch:** `0x4C96140` is thin insert: stores `{desc=rdi, tag=2}` and calls `builder->vtbl[0x368](builder,&pair)` (UI group). Callers `0x4C95550,0x5ABB370,0x6C11280,0x6C3F880,0x6E77420`.
- **[V] Constructor:** `0x668C3C0` (`this=rcx=rsi`, returns `rsi`). Writes all fields 0x00..0xA0 as in `RenderUIMeshDescription`: fixed scalars/bytes/word, zeroed 4 `SharedRef` slots at +0x18 with `mRefCount=0`, default `mVariantTag=0xFF`. Variant source `rbx=[rbp+0xD0]`, tag `[rbx+0x18]`: `ja` -> keep empty; case 0 copies inline `{+0x88 qword, +0x90 SharedRef, +0x98 qword}` and sets tag 0; case 1 allocs 0x20 (allocator `data_1233e1a8` vslot1) storing heap ptr at +0x88, copies shared ref with weak ref on ctrl+0xC and 16-byte tail, sets tag 1. Then copies `r9` span elements into `mRefs[0..]` via `0x4DFB570`, incrementing `+0x58`.
- **[V] Size/layout:** true constructed/written size ends at +0xA1, aligned to **0xA8**; `offsetof(mRefs)==0x18`, `mRefCount==0x58`, `variant storage==0x88`, `variant tag==0xA0` — matches existing header and static_asserts (resolves R10 ">=0x90, sub-objects at +0x18 and +0x88").
- **[V] Consumer:** UI visitor `0x6664A00` (`"FrameBuilder - Insert Ui"`), tag 2 case at `0x6664BD6` (inline). Reads `mFlags80[0..5]`, `mValue70`, `mValue60/68`, `mRefCount`, `mRefs` base and `mRefs[1]` (+0x28/+0x30), `mValue10/78/00/08`, computes render mode from flags 82/83/84, passes `&desc[0x86]` and variant base `&desc[0x88]`, branches on `mRefCount < 2`, and in both paths invokes UI renderer `0x674A3A0` (same renderer used by UIText case). `descscan` confirms reads at 0x00,0x08,0x10,0x18,0x20,0x28,0x30,0x58,0x60,0x68,0x70,0x78,0x80..0x85,0x86(ref),0x88(ref).
- **[I] Field meanings:** `mRefs` = 4 inline shared texture/ref slots resolved through `0x4DFB570`; `mRefCount < 2` gates alternate submit path in visitor; flags 82/83/84 derive a mode/index passed to renderer; `+0x86` treated as a u16 value/address passed onward. Precise semantic names of scalar fields/flags remain inferred.
- **[I/?] Producers:** representative build+insert flow seen in `0x4C95550` (`desc @rbp+0x290`, ctor, clone, `0x1589340` dtor). `producerscan` reports stores up to +0x3A0 in some large frames — noisy/misaligned attribution likely (6id); not used as sole layout evidence.
- **[?] Open details:** variant cases 2/3 code paths; exact meaning of each `mValue*`/flag byte and of variant payload schema expected by `0x674A3A0`.

### SDK/header/assertion status
- `src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h` already contains `RenderUIMeshDescription` with correct size/offset static_asserts (0xA8, key offsets) [V]. **No additive code edits made** (layout already captured; semantic renames would be speculative).
- `src/sdk/mc/deps/minecraft_renderer/framebuilder/DescriptionClones.h` already lists clone `0x4C96140` (UI, thin) [V]. No edits.
- `docs/data/layout_asserts.json`: not modified (no new verified immediate/displacement constants extracted beyond existing struct asserts).

### Files created/edited
- Created: `docs/progress/re_uimesh.md` (this file)
- Created: `docs/functions/668c3c0.md` (D2 constructor dossier)
- Created: `docs/functions/4c96140.md` (D2 thin-clone dossier)

### Verification run
- Lint/Types/Tests: **N/A** (static RE/docs-only session; no build run per AGENT_BRIEF; no source edits).

## FULL PROPOSED BGFX_MAP ENTRY TEXT (entry ID TBD; DO NOT edit BGFX_MAP.md)
```md
### 6??. RenderUIMeshDescription (UI tag 2): clone/ctor/layout/consumer (static, 62.01) [V layout/flow]
- Thin insert clone `0x4C96140` (`FrameBuilder::insert<RenderUIMeshDescription>`): profiler "FrameBuilder - Insert", stores `{desc*, tag=2}` and calls UI group vslot `+0x368`. Callers (sampled): `0x4C95550, 0x5ABB370, 0x6C11280, 0x6C3F880, 0x6E77420`.
- Constructor `0x668C3C0` (D2: docs/functions/668c3c0.md), returns `this`: initializes fixed fields at +0x00,+0x08,+0x10,+0x60,+0x68,+0x70(f32),+0x78, flags +0x80..+0x85, u16 +0x86 from `[rdx]`; zeroes inline `SharedRef mRefs[4]` at +0x18 and sets `mRefCount` +0x58 = 0; default variant tag +0xA0 = 0xFF. Variant source `[rbp+0xD0]` tag `[+0x18]`: case 0 = inline {qword @+0x88, SharedRef @+0x90, qword @+0x98, tag 0}; case 1 = heap 0x20 allocated via `data_1233e1a8` vslot1, ptr @+0x88 with copied SharedRef (weak ref on ctrl+0xC) + 16B tail, tag 1; then appends span `r9={count,data}` into `mRefs` via resolver `0x4DFB570`, incrementing +0x58. True size 0xA8 (ends +0xA1). Sub-objects confirmed at +0x18 (4x SharedRef + count) and +0x88/+0xA0 (variant storage/tag), matching `Descriptions.h`.
- Consumer: UI visitor `0x6664A00` tag 2 is inline (0x6664BD6..): reads flags/values/refs/variant (+0x00,08,10,18,28,30,58,60,68,70,78,80..86,88), derives mode from flags 82/83/84, branches on `mRefCount < 2`, and calls UI renderer `0x674A3A0` in both paths (cf. group_visitors/UI 2). Semantic names of most scalars/flags and variant cases 2/3 remain [I/?]; producerscan noisy for UIMesh (6id). D3 live not done.
- Cross-ref: 6ee table, 6fu thin-clone template, 6gn/6gi visitor map, R10. Dossiers: docs/functions/668c3c0.md, docs/functions/4c96140.md.
```
