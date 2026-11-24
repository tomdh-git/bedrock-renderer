## NEXT
DONE — unit U-EX1.bc68e40.c00 complete. Chunk 1 of sub_bc68e40 (0xbc68e40..0xbc6a600) lifted and verified; whole-function liftcheck passes.

## PROGRESS
- Scaffold generated via lift_scaffold.py
- Disassembly read for 0xbc68e40..0xbc6a600 (800 + 400 instructions)
- Jump table at 0xF449638 decoded: 40 entries, tags 0..39
- Callees resolved: sub_ebce390, sub_ebce5e0, sub_bc5f110, sub_bc7a3d0, sub_bc6abd0, sub_bc68840, sub_eea6040 (via data slot 0xF99FFA0)
- Main source file: src/client/features/render/native/bgfx/sub_bc68e40.cpp
- Chunk source file: src/client/features/render/native/bgfx/bc68e40_chunk_c00.cpp
- Chunk header: src/client/features/render/native/bgfx/bc68e40_chunk_c00.h
- Dossier updated: docs/functions/bc68e40.md
- liftcheck PASSED for 0xbc68e40
- liftcheck --range 0xbc68e40 0xbc68e40 0xbc6a600 PASSED
- verify_oc on bc68e40_chunk_c00.cpp: claimed=156 match=156 mismatch=0 no-such-instr=0
- Chunk 2 (0xbc6a600..0xbc6a9c3) already lifted by another unit: sub_bc68e40_chunk2.cpp + sub_bc68e40.cpp LIFT_FN

## BLOCKING
None - liftcheck passes for the whole function and both chunks

## TOOL REQUESTS
None