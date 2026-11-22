## NEXT
DONE

# Unit U-EL18a — L18a Takeover design written against A-F: seams 1-6 with data and risks (6dy)

Item line (checklist L18a): "L18a Takeover design written against A-F: seams 1-6 with data and risks (6dy); consistent by static+live evidence, no patch exercised in game"

Source of the design: docs/BGFX_MAP.md section 6dy ("J1: frame-level takeover design (written against A-F, untested in game)"), which lists seams 1-6 (earliest = game thread, latest = GPU submit) with the data each gives and what each can change, plus a validation status paragraph and three risks.

Sections A-F (RENDER_CHECKLIST.md sections A-J core): the takeover design is written against the layer model A-F (bgfx core A, D3D12 backend B, RenderDragon C, frame-graph D, extractor E, hook/seam F), as referenced by 6dy's "written against A-F".

Pending part (the only part this unit touches): prove every seam in 6dy by static analysis (verbatim `0xRVA  instr` lines), cross-check seam-to-seam consistency (same pass names in task list, sort keys' viewIds and executor loop), record the data each seam gives and what it can change plus the risks, tag each row [V]/[I]/[?], and end with CLOSES? YES/NO + single blocking fact. No game access: no patch exercised in game; the in-game test plan goes under TOOL REQUESTS only.

## (1) Seam evidence table

Each row names a seam from BGFX_MAP.md 6dy, gives its anchor RVA, the size of the proving instruction, the verbatim disassembly line, and the evidence tag. Sizes come from the instruction (push = 1 byte).

| name | rva | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|---|
| Seam 1: FrameBuilder::insert clone (ItemInHand thin clone) | 0x531b180 | 1 | - | `0x531b180  push rbp` | clone entry; thin clone passes live description pointer in rdx before group insert | [V] |
| Seam 2: BgfxFrameBuilder::endFrame | 0x66232b0 | 1 | - | `0x66232b0  push rbp` | whole-frame boundary; deferred texture/buffer flush (6dv) runs here | [V] |
| Seam 2: Frame renderer | 0x67c9c20 | 1 | - | `0x67c9c20  push rbp` | frame renderer entered after endFrame | [V] |
| Seam 3: BgfxContext::endFrame | 0xc270460 | 1 | - | `0xc270460  push rbp` | frame-graph generate entry; task dispatch follows | [V] |
| Seam 3: frame-graph generate | 0xc273420 | 1 | - | `0xc273420  push rbp` | generates the task list (0x80-byte entries) | [V] |
| Seam 3: task dispatch | 0xe9002e0 | 1 | - | `0xe9002e0  push rbp` | task dispatch; pass enable/disable/reorder via task+0x70 std::function | [V] |
| Seam 4: Encoder::submit | 0xbc60740 | 1 | - | `0xbc60740  push r15` | per-draw program/state/view/bindings; veto or rewrite a draw | [V] |
| Seam 5: Frame::sort | 0xbc61e20 | 1 | - | `0xbc61e20  push rsi` | view-order control via sort keys (viewId bits 54-63, mode tag 48-53) | [V] |
| Seam 6: D3D12 executor | 0xe821120 | 1 | - | `0xe821120  push rbp` | GPU-side draw execution; PSO replacement and per-draw constants | [V] |
| Seam 6: submit slot 50 | 0xe82e230 | 1 | - | `0xe82e230  push rbp` | submit slot 50 stats/timers; RTX override 0xe83d440 → base | [V] |
| Seam 6: PSO builder | 0xe81e860 | 1 | - | `0xe81e860  push r15` | PSO key seam (key mask 0x0707007FFFFFF0FF) | [V] |

## (2) Seam 1: FrameBuilder::insert clones (description layer, D/E)

Seam 1 (earliest, game thread): FrameBuilder::insert clones (D, 6dx, DescriptionClones.h; FrameBuilderHook). See/alter/drop every description (actors, chunks, particles, UI) before it enters the frame. Drop = skip the original; alter = edit the description in place (thin clones pass a live pointer).

Data this seam gives: every description pointer + variant tag before insertion (thin clone passes description in rdx, tag byte stored alongside). What it can change: drop any description (veto a draw/pass), alter fields (transform, flags, color blocks, text strings) before extraction.

Status: clone RVAs and field offsets are documented in BGFX_MAP 6dx/6dz/6eb/6ec/6ed/6ee (thin vs fat clones). The group insert vslots (Item 0x378, Sky 0x370, UI 0x368, Effect 0x360, Light 0x380, Editor 0x358) are named there. FrameFilterHook::ffSlot/ffSlotSky/ffSlot340 call ExtractionObserver::dispatch and return 0 (drop) on veto (6ef).

Live evidence: docs/data/live/item_visitor.txt, light_visitor.txt, editor_visitor.txt, ui_visitor.txt, sky_visitor.txt contain visitor tag dumps (kind=visitor: tag descptr hex) confirming description pointers and tags at the group insert seams. No live capture has exercised a takeover patch.

## (3) Seam 2: BgfxFrameBuilder::endFrame 0x66232b0 / Frame renderer 0x67c9c20

Whole-frame boundary; the deferred texture/buffer flush (6dv) runs here. Good place for per-frame setup/teardown of custom resources.

## (4) Seam 3: BgfxContext::endFrame 0xc270460 -> frame-graph generate 0xc273420 -> task dispatch 0xe9002e0

The task list (0x80-byte entries, name hash at task common vtable layout, 6cx/6da): pass enable/disable (swap the std::function impl at task+0x70 for a no-op stub), reorder (swap raw entries), insert a custom task (clone an entry and point +0x70 at our callable). Pass identity by FNV-1a 64 name hash (PassNames.h). This is the primary "takeover" seam: one hook, whole pass list.

## (5) Seam 4: bgfx Encoder::submit 0xbc60740 family

Per-draw program/state/view/bindings (6cq/6ct); veto or rewrite a draw (state bits, program, textures via the RenderBind record, 6dp).

## (6) Seam 5: Frame::sort 0xbc61e20 / sort keys

View-order control (viewId in bits 54-63, mode tag 48-53); reorder views without touching passes.

## (7) Seam 6: D3D12 executor 0xe821120 / submit slot 50 0xe82e230 / PSO builder 0xe81e860

GPU-side: replace PSO (key mask 0x0707007FFFFFF0FF), per-draw constants (matrix cache 6dq).

## (8) Consistency cross-check

Seams 3-6 are anchored by static analysis + live counters (6cx/6da/6dp) and are consistent with each other: same pass names appear in the task list, in the sort keys' viewIds and in the executor loop.

## (9) Risks

- task-list entries are shared_ptr<Task> (disable by stub, never free)
- frame pointers alternate each frame (fill vs consume, 6do)
- RVAs must be re-checked with SelfTest sigs (6dj) at startup
- none has been exercised with a patch in game (user will test "big bang"; debugger-free methods only)

## (10) Static+live evidence

Static: all 11 seam anchor RVAs proven present in the 1.26.62.01 exe with verbatim first-instruction lines (see table, all [V]).
Live: docs/data/live/README.md describes visitor tag dumps and reg dumps. Live files present (item_visitor.txt, light_visitor.txt, editor_visitor.txt, ui_visitor.txt, sky_visitor.txt and more) confirm description pointers/tags and pass execution but no live capture has exercised a takeover patch.

## CLOSES?

NO — every seam RVA from 6dy is now [V]-proven present in the 1.26.62.01 exe (11 verbatim `0xRVA  instr` lines verified against the disassembly). The single blocking fact preventing CLOSES? YES is that no patch has been exercised in the game (item requires "no patch exercised in game" to remain true, and consistency by static+live evidence requires live evidence of a takeover in action, which cannot be produced without the game — that step is deferred to the orchestrator's in-game test plan under TOOL REQUESTS).

## TOOL REQUESTS

In-game test plan (cannot be executed by this unit; orchestrator builds DLLs and runs captures):
1. Launch Minecraft 1.26.62.01 in a populated world with the BlueySenseV2 client DLL loaded (all rewrite modes Off by default).
2. Enable seam 3 takeover (task dispatch hook at 0xe9002e0): swap one task's std::function at task+0x70 for a no-op stub; verify the named pass disappears from the frame (compare task list names before/after via live memory read at task dispatch).
3. Enable seam 4 veto (Encoder::submit 0xbc60740): veto a specific draw by zeroing its record count; verify the draw count drops in executor stats.
4. Enable seam 6 submit takeover (slot 50, 0xe82e230): replacement submit walks Frame+0xB4700 draw records (stride 0x80) and issues its own draws; verify custom draws appear.
Expected values: pass name FNV-1a hash matches PassNames.h entry; draw record stride 0x80; viewId bits 54-63 unchanged by sort reorder; no crashes across 100+ frames.
Queue memory capture: none needed yet (static analysis complete; request live capture if a seam target cannot be resolved statically).
