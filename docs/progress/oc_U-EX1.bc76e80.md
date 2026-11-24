## NEXT
DONE

## UNIT
- id: U-EX1.bc76e80
- function: 0xbc76e80, size 0x36f bytes (range [0xbc76e80, 0xbc771ef)), depth 3, D0, region bgfx
- callee set: 0 callees in set (docs/progress/_d_U-EX1.bc76e80.txt lists none)
- calls: 3x `call qword ptr [0xF99FFA0]` -> sub_eea6040, class `vendor` boundary (native_boundary.tsv row 506) via loader-resolved data slot 0xF99FFA0 [V]
- callers (4 sites, all ignore rax): 0xbc66eb8, 0xbc670ce (sub_bc66de0), 0xbc6fe68 (sub_bc6fdc0), 0xbc70885 (sub_bc70800) [V xr]
- signature lifted: void sub_bc76e80(Bc76e80Queue* queue /*rcx*/, uint64_t key /*rdx*/); original rax (bucket sentinel not-found / thunk result found) unused by callers

## DONE
- step 1: result file written (## NEXT + step 2)
- step 2: full disassembly [0xbc76e80, 0xbc771ee] collected via rdis dis 0xbc76e80 800; size 0x36f confirmed in docs/data/native_functions.tsv line 1103; constant 0x1007E0F81 verified as full imm64 (49 BA 81 0F 7E 00 01 00 00 00) at 0xbc76f0c [V]
- step 3: docs/functions/bc76e80.md extended with 'Reversed source (complete)' (analysis kept)
- created src/client/features/render/native/bgfx/sub_bc76e80.h (layout constants + static_asserts + signature)
- created src/client/features/render/native/bgfx/sub_bc76e80.cpp (// LIFT marker, complete lift, verbatim call log, LIFT_FN)
- python tools/sigs/verify_oc.py on the .cpp: claimed=3 match=3 mismatch=0 no-such-instr=0
- python tools/sigs/liftcheck.py 0xbc76e80: LIFTCHECK OK 0xbc76e80 -> CLOSES? YES

## FILES
- created: src/client/features/render/native/bgfx/sub_bc76e80.h
- created: src/client/features/render/native/bgfx/sub_bc76e80.cpp
- changed: docs/functions/bc76e80.md (added 'Reversed source (complete)' section)
- changed: docs/progress/oc_U-EX1.bc76e80.md (this result file)

## LIFTCHECK
LIFTCHECK OK 0xbc76e80

## UNRESOLVED CALL
none: all 3 calls target sub_eea6040 via data slot 0xF99FFA0, class vendor boundary in docs/data/native_boundary.tsv row 506

## TOOL REQUESTS
None

CLOSES? YES
