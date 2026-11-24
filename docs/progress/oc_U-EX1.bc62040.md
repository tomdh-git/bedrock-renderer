## NEXT
DONE — lift complete and liftcheck passed.

## UNIT
U-EX1.bc62040 — lift sub_0xbc62040 (0xbc62040, size 0xb72, depth 3, milestone D0, region bgfx, "D3D12 submit RTX override")

## DATA FROM ORCHESTRATOR (docs/progress/_d_U-EX1.bc62040.txt)
- callees_in_set: none
- callees_outside_set: 0xe951550, 0xe9e7970 (both `crt` in docs/data/native_boundary.tsv lines 467-468)
- functions.tsv line 1056: 0xbc62040 0xb72 depth 3 tier 1 bgfx D0, refs 0xe951550,0xe9e7970
- single caller: 0xbc61e20 (call at 0xbc61f67)

## FILES
- src/client/features/render/native/bgfx/sub_bc62040.h  (written)
- src/client/features/render/native/bgfx/sub_bc62040.cpp  (written)
- docs/functions/bc62040.md  (written, has 'Reversed source' section + static_assert)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc62040` → `LIFTCHECK OK 0xbc62040`

## CLOSES?
YES
