## NEXT
DONE

## UNIT
U-EX1.bc2e890 | sub_bc2e890 at 0xbc2e890, size 0x1de (0xbc2e890..0xbc2ea6e), depth 1, milestone D0, region bgfx, root added 0xbb7efb0, callees_in_set: none. native_functions.tsv line 992 already lists 0xbc2e890 / 0x1de.

## FILES
src/client/features/render/native/bgfx/sub_bc2e890.h  (new: Bc2e890Object layout with offsetof static_asserts for every touched offset, signature, footprint)
src/client/features/render/native/bgfx/sub_bc2e890.cpp  (new: first line `// LIFT 0xbc2e890 size 0x1de 1.26.62.01 sub_bc2e890`, lifted body with `// 0xA..0xB` range citations and verbatim call quotes, LIFT_FN registry entry)
docs/functions/bc2e890.md  (new: dossier with mechanical facts, callees, jump table, Reversed source (complete), structs touched)

## LIFTCHECK
LIFTCHECK OK 0xbc2e890

## UNRESOLVED CALL
0xbc2e99b  call 0xE869FF0  -- target 0xE869FF0 (sub_e869ff0, [0xE869FF0..0xE86A0C1], size 0xD1, 370 xrefs [V: rdis fn]): descriptor move dest+0x98 <- src+0x98 with source clears, returns dest; callee is outside the lift set and absent from docs/data/native_boundary.tsv [V: grep, no matches].
0xbc2e9cc  call 0x5669770  -- target 0x5669770 (sub_5669770, [0x5669770..0x5669ADA], size 0x36A, 54 xrefs [V: rdis fn]): float-field copy dest+0x118 <- src+0x118; callee is outside the lift set and absent from docs/data/native_boundary.tsv [V: grep, no matches].
No wrapper was written for either target (GOAL: do not invent a wrapper for a callee outside both sets).

## SUMMARY
All 100 instructions of [0xbc2e890, 0xbc2ea6e) lie inside cited `// 0xA..0xB` ranges; both `call` instructions are quoted verbatim and verify_oc reports mismatch=0, no-such-instr=0; the source has no [?]/[I]/TODO/UNVERIFIED/UNRESOLVED/stub token; LIFT_FN is registered; static_asserts cover every layout offset. The lifted body reproduces every field read/write of the original in order, including the switch on src+0x70 with the data_f440da0 jump table (case 0 -> 0xbc2e958, 1 -> 0xbc2e928, 2 -> 0xbc2e930, 3 -> 0xbc2e938 [V: table bytes read from the exe]). The two unresolved calls are not executed by the lifted body, so the lift is not semantically complete as L1.

CLOSES? NO UNRESOLVED CALL: calls at 0xbc2e99b (target 0xE869FF0) and 0xbc2e9cc (target 0x5669770) are outside the lift set and absent from docs/data/native_boundary.tsv, so no wrapper may be written and the unit cannot close as L1 (single blocking fact).
