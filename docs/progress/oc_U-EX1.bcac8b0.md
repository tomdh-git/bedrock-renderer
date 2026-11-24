## NEXT
DONE — liftcheck printed LIFTCHECK OK 0xbcac8b0; unit complete.

## FILES
Created (no edits to any other unit's files; no builds; no game):
- src/client/features/render/native/bgfx/sub_bcac8b0.cpp  (lift source; first line `// LIFT 0xbcac8b0 size 0x248 1.26.62.01 sub_bcac8b0`; LIFT_FN registry entry)
- src/client/features/render/native/bgfx/sub_bcac8b0.h   (Item/ControlBlock layout constants + static_asserts + signature + footprint decl)
- docs/functions/bcac8b0.md                              (dossier; 'Reversed source (complete)' section)
- docs/progress/_listing_bcac8b0.txt                     (rdis disassembly scratch evidence)
- docs/progress/oc_U-EX1.bcac8b0.md                      (this result file)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbcac8b0` printed:

LIFTCHECK OK 0xbcac8b0

(verify_oc mismatch=0, no-such-instr=0; all 8 `call` instructions quoted verbatim; 100% instruction coverage of [0xbcac8b0, 0xbcacaf8) by cited ranges; dossier Reversed-source block free of [?]/[I]/TODO/UNVERIFIED; static_asserts present; LIFT_FN registry entry present.)

## UNRESOLVED CALL
none. The function's only `call` instructions are eight `call qword ptr [0xF99FFA0]` sites (0xbcac92a, 0xbcac94c, 0xbcac9d5, 0xbcac9f7, 0xbcaca56, 0xbcaca78, 0xbcacabb, 0xbcacad5), each resolving to boundary class "vendor" sub_eea6040 via data slot 0xF99FFA0 (docs/data/native_boundary.tsv line 506) and called through `native::Boundary`. There are no direct `call` instructions to other functions. The idx 2 and idx 3 paths tail-jump (`jmp 0xBCACB00`, `jmp 0xBCACC20`) to separate continuation functions bcacb00/bcacc20 outside [0xbcac8b0, 0xbcacaf8); these are forward-declared as `sub_bcacb00`/`sub_bcacc20` in `native` and called per the spec section 6 forward-declare pattern (they are their own lift units; native_deps.tsv X1.bcac8b0 lists zero deps).

## CLOSES? YES
