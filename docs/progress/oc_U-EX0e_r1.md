## NEXT
step 2

## Unit U-EX0e

GOAL: Fix the 3 world-phase SelfTest failures: `FrameBuilder::visitEditor` layout drift (+0x64 and +0x3C offsets in `docs/data/layout_asserts.json` / `RenderLayoutAsserts.h`): re-derive each constant from the disassembly of the Editor group visitor (0x66742F0), correct both lists, `python tools/sigs/layoutcheck.py` clean. Also list every other assertion that has never been checked against live memory.

Placeholder: work in progress below.
