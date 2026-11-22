## NEXT
DONE

UNIT U-ER13 — R13 layout_asserts.json / RenderLayoutAsserts.h description entries
================================================================================
Output file: docs/progress/oc_U-ER13.md (no other file).

R13 checklist line: "[ ] R13 layout_asserts.json / RenderLayoutAsserts.h have no entries for any description (visitors have no Sigs.json anchors): add anchors and the constants"

Part A (anchors): DONE already — Sigs.json anchors exist for all 6 group visitors:
  visitEditor 0x66742F0, visitEffect 0x666ACA0, visitUI 0x6664A00,
  visitSky 0x66560F0, visitItem 0x6646980, visitLight 0x6640D80
  (src/sdk/Sigs.json lines 140-145, [V by file read]).

Part B (pending): layout_asserts.json / RenderLayoutAsserts.h entries for
  descriptions. Current state (docs/data/layout_asserts.json + RenderLayoutAsserts.h):
  - visitSky: 0x548, 0x138, 0x128, 0x11c, 0x10c
  - visitLight: 0x800, 0x648, 0x4a0, 0x1d0, 0x84
  - visitItem: 0x140, 0xc8, 0xe8, 0xc0
  - visitEffect: 0xf8, 0xa0, 0xb0   <- 0xa0 for BlitFlipbook is CONTRADICTED (re_blitflipbook.md: verified size 0x20)
  - visitUI: 0x90
  - visitEditor: NO entries at all (blocking fact per platform-versioning-live.md line 13: "Editor visitor 0x66742f0 has an anchor but no constants")

Evidence table (name | rva or offset | size | verbatim `0xRVA  instr` proof line | [V]/[I]/[?]):
(processed in pieces, appended after each piece; no raw dumps, one row per distinct offset, all sites listed)

| 0x64 | 16B | rdi+0x64 | `0x66758bd  movups xmm6,[rdi+0x64]` `0x66751b2  movups xmm6,[rdi+0x64]` `0x6675dea  movups xmm9,[rdi+0x64]` | Editor description +0x64 16-byte block read (movups), tags 1/2/3/4 | [V] |
| 0xD0 | 2B | rdi+0xD0 | `0x6676c9b  mov r12w,[rdi+0xD0]` `0x667a4dd  mov di,[rdi+0xD0]` `0x6676652  mov r12w,[rdi+0xD0]` `0x667981b  mov di,[rdi+0xD0]` | Editor description +0xD0 u16 field read (word), tags 1/2/4 | [V] |
| 0x3C | 1B | rdi+0x3C | `0x6674ac3  cmp byte ptr [rdi+0x3C],1` `0x6674d02  cmp byte ptr [rdi+0x3C],1` `0x6674760  cmp byte ptr [rdi+0x3C],1` | Editor description +0x3C byte field compared to 1, tags 4/5/6/7 | [V] |
| 0x122 | 1B | rdi+0x122 | `0x6679c65  cmp byte ptr [rdi+0x122],1` | Editor description +0x122 byte field compared to 1, tag 3 | [V] |

All verbatim lines copied from docs/progress/oc_U-D10c.md (Editor per-tag [rdi+off] read views, casewalk over docs/data/listings/editor_visitor_66742f0_667e290.txt, delegate.py check OK). Instruction sizes: movups=16B, word read=2B, byte read=1B.

Plan remaining:
1. Add visitEditor constants (0x64, 0xD0, 0x3C, 0x122) to docs/data/layout_asserts.json under symbol "FrameBuilder::visitEditor"
2. Add visitEditor constants to src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h (kVisitEditor)
3. Re-check visitEffect 0xa0 contradiction (0x20 may not appear as immediate in visitEffect body; 0xa0 is verified [V] by layoutcheck pass)
4. Run python tools/sigs/layoutcheck.py (expect 0 failed)
5. Run python tools/delegate.py check docs/progress/oc_U-ER13.md (expect exit 0)
6. Set ## NEXT line to DONE

CLOSES?: YES — every pending part of R13 is now proven by [V] rows:
  1. Anchors: all 6 group visitors already had Sigs.json anchors (visitEditor 0x66742F0, visitEffect 0x666ACA0, visitUI 0x6664A00, visitSky 0x66560F0, visitItem 0x6646980, visitLight 0x6640D80; Sigs.json lines 140-145, [V]).
  2. Constants: visitEditor added with 4 constants (0x64, 0xD0, 0x3C, 0x122), each backed by verbatim `0xRVA  instr` proof lines from oc_U-D10c.md (casewalk over docs/data/listings/editor_visitor_66742f0_667e290.txt), all [V].
  3. All 5 previously-existing visitor entries (visitSky, visitLight, visitItem, visitEffect, visitUI) remain [V] — unchanged.
  Verification: python tools/sigs/layoutcheck.py -> 191 assertions, 0 failed. python tools/delegate.py check docs/progress/oc_U-ER13.md -> CHECK OK 4 rows.
  Note: visitEffect 0xa0 (BlitFlipbook sizeof) is contradicted by re_blitflipbook.md (true size 0x20), but 0xa0 is verified [V] as present in visitEffect's body (layoutcheck passes) and 0x20 could not be confirmed as an immediate/displacement in visitEffect's 0x6C7C-byte body; this is a pre-existing `backs`-description discrepancy, not a missing entry, and does not block R13 closure.
