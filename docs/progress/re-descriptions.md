# Progress: framebuilder descriptions batch (agent "re-descriptions", mce::framebuilder)

## GOAL
Type the NEXT batch of FrameBuilder descriptions (mce::framebuilder), highest frame-path impact per docs/data/frame_path_functions.tsv, small functions before giants, skipping already-typed ones. Deliverables per description: field-by-field dossier docs/functions/<rva>.md (D2 "Reversed source" where possible, else D1 named with [V]/[I]/[?]), additive Descriptions.h edits + static_asserts, optional docs/data/layout_asserts.json + RenderLayoutAsserts.h constants, BGFX_MAP.md entries starting at 6ip, RENDER_CHECKLIST.md M2c/D5 ticks per TICKING RULE. Stop after ~6-10 descriptions or on blocker.

## GROUND TRUTH (read 2026-11-15)
- docs/data/frame_path_functions.tsv: depth-0 root inserts untyped: Editor variants 0-6 (0x4c85d70, 0x4c85f30, 0x4c860f0, 0x4c862b0, 0x5371160, 0x6c956b0, 0x6c961e0; all 0x139 bytes, root, D2), BatchActor 0x4e39cb0 (0x139, root, D2). CelestialBody 0x5370b20 already typed (RenderCelestialBodyDescription 0x88).
- Descriptions.h (ground truth, ahead of stale checklist): ~39 descriptions already typed incl. ChunkGeometry 0xF0, ItemInHand 0x180, BlitFlipbook 0x20 (CONTRADICTS 6ih), AimAssistHighlight 0x88 (CONTRADICTS 6ih), EditorHighlight 0x58, all Light tags, UI Mesh/HudIcon/GameFace, all Sky tags, etc.
- Checklist M2c line 415 says "27 of 62 typed" — STALE relative to Descriptions.h. Editor tags 0-7 (catalog) are NOT in Descriptions.h: RenderEditorBlockVolumeBoundingBoxDescription, RenderEditorBlockVolumeOutlineDescription, RenderEditorGizmoHandleArrow/Cube/Pane/RingDescription, RenderEditorRenderPlaneDescription, RenderEditorSelectionCursorDescription. EditorHighlight (Effect tag 8) IS typed (0x58).
- docs/progress/descriptions.md entries: Editor group OPEN (partial): shared gizmo producer 0x4c83c80 handles tags 1-4 (arrow/cube/pane/ring), desc [rbp+0xa0] REUSED across the four; tag 0 BoundingBox producer 0x6c94b60 ([rbp-0x60]); tag 5 SelectionCursor producer 0x53e7f90 ([rbp-0x60]); tag 6 Outline producer 0x6c95d90 ([rbp+0xa0]); tag 7 RenderPlane producer 0x6d3c040 ([rbp+0x70], extent 0xE3 incl word+0xE0 byte+0xE2 => size 0xE8 [I]). Editor extractor reads (descscan2 --visitor editor --follow): tags 1/2 read 0..0x24, 0x64..0x75, 0x78..0x7C, word +0xD0, byte +0xD2 => size 0xD8 [I]; tag 3 pane additionally word +0x120/byte +0x122 => size 0x128 [I]; tag 4 ring up to +0x1EE => size 0x1F0 [I]. Common base [I]: f32 +0/+4/+8, vec +0x0C, f32 +0x14, qword +0x18, f32 +0x20, 4x4 matrix unit-diag at +0x24 (diag +0x24/+0x38/+0x4C/+0x60), vec4 +0x64?, byte +0x74, f32 +0x78, flag bytes +0x3C/+0x3D/+0x3E. NEEDS per-tag producer read to bound +0x80..+0x1EE (producerscan/callsite + disassembly).
- Tools available: python 3.14.5 + capstone 5.0.7; rdis.exe built; disrange.py/dossier.py/callsite.py/descscan2.py in tools/sigs.
- STATIC ONLY (AGENT_BRIEF rule 16): no debugger/patches/commits; exe read-only; tags [V]/[I]/[?] on every claim.
- NOTE: AGENT_BRIEF rule 4 says don't edit BGFX_MAP.md/RENDER_CHECKLIST.md, but the user task explicitly instructs appending to BGFX_MAP.md from 6ip and ticking the checklist per TICKING RULE; user task takes precedence for this session.

## DONE (this session)
- Disassembled gizmo producer 0x4c83c80 [0x4c83c80..0x4c854ec, size 0x186c] via rdis + disrange (3 ranges: base, 0x4c84a4c-0x4c84e00, 0x4c84e00-0x4c854ec).
- Confirmed description base = [rbp+0xA0] (desc offset D = rbp_off - 0xA0), reused across tags 1-4.
- Clone calls: arrow 0x4c85d70 @4c8458c; cube 0x4c85f30 @4c847f2; pane 0x4c860f0 @4c84efc; ring 0x4c862b0 @4c851ba.
- Confirmed per-tag stores (producer ∩ extractor-read overlap => [V]; extractor-only reads => [?]):
  * arrow/cube (tags 1/2): +0x00 f32, +0x04 f32, +0x08 f32, +0x0C f32, +0x10 xmm(16B), +0x20 qword, mat4 rows +0x24/+0x34/+0x44/+0x54, +0x38 f32=1.0, +0x4C f32=1.0, +0x54 xmm. Extractor reads +0x64..+0x75,+0x78..+0x7C,+0xD0 word,+0xD2 byte NOT confirmed written => [?]. Size 0xD8 [I extent].
  * pane (tag 3): base + +0x64 xmm, +0x74 byte, +0x78 f32, +0x120 word. Size 0x128 [I extent].
  * ring (tag 4): +0x4C xmm, +0x5C byte, +0x1EE byte=1, +0x1F0 f32, +0x1F8 qword=1. Extent unproven (producer writes past +0x1EE) => size [I].
- BLOCKER: [rbp+0xA0] stack object reused with tag-specific OVERLAPPING layouts (e.g. +0x0C is f32 for arrow/cube but mat4 row in the 0x4c84a4c range; mat4 at +0x24 vs +0x0C conflicts). Cannot cleanly separate 4 distinct structs with full certainty from static analysis in one session. Also ring size conflicts: extractor says up to +0x1EE (0x1F0) but producer writes +0x1F8.
- Not attempted (deferred to next batch): tag 0 BoundingBox (0x6c94b60), tag 5 SelectionCursor (0x53e7f90), tag 6 Outline (0x6c95d90), tag 7 RenderPlane (0x6d3c040, size 0xE8 [I]), BatchActor (0x4e355a0, size >=0x100 unproven).

## FILES TO CREATE / EDIT (this session)
- docs/functions/4c83c80.md (gizmo producer dossier, D1 named)
- src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h (add 4 editor gizmo structs, static_asserts on confirmed offsets only)
- docs/BGFX_MAP.md (append entry 6ip, editor gizmo group)
- docs/RENDER_CHECKLIST.md (M2c/D5 editor lines; tick only where TICKING RULE met: header field + BGFX_MAP RVA)

## NEXT
Write the 4 deliverables above, then report. Do NOT add layout_asserts.json/RenderLayoutAsserts.h size constants for gizmo sizes (they are [I] extents, not confirmed immediates in a Sigs-anchored function — static_asserts are the guard; say so).

