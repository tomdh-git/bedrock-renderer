# UNIT U-EX1.bcacd90 — chunk plan for sub_bcacd90 (VV frame-graph builder)

## NEXT
DONE. Chunk split complete and written to docs/data/native_chunks/bcacd90.tsv. The next unit (the LIFT item for this function) writes docs/functions/bcacd90.md + the .cpp/.h in src/client/features/render/native/bgfx/.

## FILES
- docs/progress/oc_U-EX1.bcacd90.plan.md (this file)
- docs/data/native_chunks/bcacd90.tsv (written — 4 chunks, 0xbcacd90..0xbcb1d0b, no gap/overlap)
- docs/functions/bcacd90.md (NOT written — out of scope for this PLAN unit; the LIFT unit writes it)

## LIFTCHECK
(PLAN/CHUNK item) Coverage: 0xbcacd90..0xbcb1d0b = 0x4f7b bytes split at basic-block boundaries 0xbcae56d / 0xbcafd5f / 0xbcb153c into 4 chunks of size 0x17dd / 0x17f2 / 0x17dd / 0x7cf, all <= 0x1800, union is exactly [0xbcacd90, 0xbcb1d0b) with no gap and no overlap. Every boundary is a basic-block start with exactly one predecessor (a single jcc: 0xbcae565 NotTaken -> 0xbcae56d; 0xbcafd46 NotTaken -> 0xbcafd5f; 0xbcb0043 Taken -> 0xbcb153c), i.e. a clean single entry with no fallthrough pred.

## UNRESOLVED CALL
none
CLOSES? YES