## NEXT
DONE: U-EX1.bc70ff0 lifted and liftcheck-verified; no further steps.

## UNIT
U-EX1.bc70ff0: lift function 0xbc70ff0 (size 0xf1 bytes, depth 1, milestone D0, region bgfx, 0 callees in lift set). Exe: Minecraft Windows 1.26.62.01 (image-base RVAs).

## STATUS
- [x] Disassembled 0xbc70ff0..0xbc710e1 fully, every instruction cited
- [x] Dossier docs/functions/bc70ff0.md (analysis + 'Reversed source (complete)')
- [x] src/client/features/render/native/bgfx/sub_bc70ff0.cpp (+ .h) with LIFT marker, layout constants, static_asserts, LIFT_FN registry entry
- [x] python tools/sigs/liftcheck.py 0xbc70ff0 -> LIFTCHECK OK 0xbc70ff0
- [x] CLOSES? YES

## FILES
- created docs/progress/oc_U-EX1.bc70ff0.md (this file)
- created src/client/features/render/native/bgfx/sub_bc70ff0.h
- created src/client/features/render/native/bgfx/sub_bc70ff0.cpp
- created docs/functions/bc70ff0.md

## LIFTCHECK
LIFTCHECK OK 0xbc70ff0

## UNRESOLVED CALL
none — all 6 calls target lift-classified functions (0xEBDBF10 sub_ebdbf10, 0xEBCE390 x4 sub_ebce390, 0xEBDBF20 sub_ebdbf20), forward-declared in sub_bc70ff0.h per hard rule 66 (native_functions.tsv depth-0 root rows; native_boundary.tsv `lift`/`auto-unresolved->lift`).

## TOOL REQUESTS
none

CLOSES? YES
