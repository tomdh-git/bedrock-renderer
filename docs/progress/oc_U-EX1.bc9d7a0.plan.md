## NEXT
DONE: chunk split of 0xbc9d7a0 written to docs/data/native_chunks/bc9d7a0.tsv (5 chunks, covers [0xbc9d7a0,0xbca3f7b) exactly, every boundary is a basic-block start with a single clean entry). Function-wide facts written to docs/functions/bc9d7a0.md. No source to write (PLAN item).

## FILES
- docs/data/native_chunks/bc9d7a0.tsv (rewritten)
- docs/functions/bc9d7a0.md (created)
- docs/progress/oc_U-EX1.bc9d7a0.plan.md (this file)

## LIFTCHECK
PLAN/CHUNK item: coverage statement — TSV rows 0xbc9d7a0..0xbc9e11a, 0xbc9e11a..0xbc9f890, 0xbc9f890..0xbca1080, 0xbca1080..0xbca2785, 0xbca2785..0xbca3f7b cover [0xbc9d7a0, 0xbca3f7b) with no gap and no overlap; chunk sizes 0x97a, 0x1776, 0x17f0, 0x1705, 0x17f6, all <= 0x1800. Every boundary (0xbc9e11a, 0xbc9f890, 0xbca1080, 0xbca2785) is a basic-block start in the rdis cfg (840 blocks, total 840, next_offset None) and has exactly one predecessor edge (0xbc9e044 NotTaken, 0xbc9f860 NotTaken, 0xbca0f87 NotTaken, 0xbca2776 NotTaken); 0xbca3f7b is the function end (last block 0xbca3f49..0xbca3f7b, jmp 0xBCA08E2 tail). Live-state across each boundary computed by backward def/use analysis over the full listing (5222 instructions, /tmp/bc9d7a0.list via tools/sigs/dumplist.py).

## UNRESOLVED CALL
none

## TOOL REQUESTS
None.

CLOSES? YES