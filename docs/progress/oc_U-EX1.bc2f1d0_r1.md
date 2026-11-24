## NEXT
DONE

## UNIT
U-EX1.bc2f1d0: sub_bc2f1d0 [0xbc2f1d0..0xbc2f3bc) size 0x1ec, depth 1, milestone D0, region bgfx, root added 0xbb81880, 0 callees in set (docs/progress/_d_U-EX1.bc2f1d0.txt). Lifted as `void SubBc2f1d0_lifted(Bc2f1d0Object* a0 /*rcx=dst*/, Bc2f1d0Object* a1 /*rdx=src*/)` returning void — a destructive field move/take from a1 to a0 (fields 0x00..0x294), type-byte switch on a1+0x70 through [data 0xF440DB0] (cases 0..3 -> 0xbc2f298/0xbc2f268/0xbc2f270/0xbc2f278; >3 skips the +0x60 block), with a lock inc refcount on *(a1+0x68)+8 for type 3, and two external calls below.

## FILES
- docs/progress/oc_U-EX1.bc2f1d0.md (this result file; step 1 written 2026-11-23, final now)
- docs/functions/bc2f1d0.md (dossier: mechanical facts, argument map, instruction-complete verbatim disassembly, 'Reversed source (complete)', structs touched, callees, OPEN questions)
- src/client/features/render/native/bgfx/sub_bc2f1d0.h (layout constants Bc2f1d0Object + 35 offset static_asserts, signature declaration)
- src/client/features/render/native/bgfx/sub_bc2f1d0.cpp (first line `// LIFT 0xbc2f1d0 size 0x1ec 1.26.62.01 sub_bc2f1d0`, complete lifted body with // 0xA..0xB range cites and verbatim `0xRVA  instr` quotes, LIFT_FN registry entry)

No other files edited (Sigs.json, shared headers, CMake, hooks, native_boundary.tsv untouched; no build, no game).

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc2f1d0` printed exactly:

LIFTCHECK OK 0xbc2f1d0

## UNRESOLVED CALL
Two call targets of sub_bc2f1d0 are neither in the lift set (0 callees in set) nor listed in docs/data/native_boundary.tsv:

1. 0xE869FF0 (sub_e869ff0) — caller instruction `0xbc2f2db  call 0xE869FF0`, args rcx=&a0->f98[0] (a0+0x98), rdx=&a1->f98[0] (a1+0x98). Seen in the disassembly: moves the +0x98 sub-object (observed span +0x98..+0x10F) and zeroes selected src fields; 370 xrefs in the exe. Not in the lift set, not in native_boundary.tsv.
2. 0x5669770 (sub_5669770) — caller instruction `0xbc2f30c  call 0x5669770`, args rcx=&a0->f118[0] (a0+0x118), rdx=&a1->f118[0] (a1+0x118). Seen in the disassembly: float-field move of the +0x118 sub-object (observed rel +0x00..+0x74); 54 xrefs in the exe. Not in the lift set, not in native_boundary.tsv.

Per the GOAL these are recorded here as UNRESOLVED CALL and no wrapper was invented; the lifted source declares them as the game's own functions (docs/functions/bc2f1d0.md ## Callees, sub_bc2f1d0.cpp extern declarations).

## CHECKLIST
X1.bc2f1d0 LIFT sub_bc2f1d0 (0xbc2f1d0, 0x1ec bytes, depth 1, D0, 0 callees in set) — source on disk, liftcheck OK; not closed (see CLOSES? below).

CLOSES? NO UNRESOLVED CALL: calls at 0xbc2f2db -> 0xe869ff0 and 0xbc2f30c -> 0x5669770 have targets in neither the lift set nor docs/data/native_boundary.tsv (liftcheck itself prints LIFTCHECK OK 0xbc2f1d0).
