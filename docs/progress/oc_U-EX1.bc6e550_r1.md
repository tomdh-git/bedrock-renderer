## NEXT
DONE

## STATUS
U-EX1.bc6e550 LIFT 0xbc6e550 size 0x216 (checklist: X1.bc6e550 LIFT sub_bc6e550, depth 4, D0, bgfx, 0 callees in set). Full disassembly of [0xbc6e550, 0xbc6e766) collected verbatim from the exe (124 instructions; all branch targets internal; ret at 0xbc6e765; next function at 0xbc6e770). Dossier written at docs/functions/bc6e550.md with register/argument map, layout model, per-phase reversed source with verbatim instruction citations, field table, and callee table. No src/client/features/render/native/bgfx/sub_bc6e550.cpp/.h created: all 4 calls target functions outside both docs/data/native_functions.tsv and docs/data/native_boundary.tsv, so emitting the calls would invent wrappers, which the GOAL forbids. Unit is blocked and cannot reach L1.

## FILES
docs/progress/oc_U-EX1.bc6e550.md
docs/functions/bc6e550.md

## LIFTCHECK
  - no source file under src/client/features/render/native whose first line is '// LIFT 0xbc6e550 size 0x...'
LIFTCHECK FAIL 0xbc6e550

## UNRESOLVED CALL
0xbc6e5b1  call qword ptr [0xF99FFA0] — target = pointer held at data slot 0xF99FFA0 (rdis symbol sub_eea6040, 0xeea6040; rcx = *(0x12ADF800), rdx = 0, r8 = 0x418, r9 = 0); not a lift row in docs/data/native_functions.tsv and not a row in docs/data/native_boundary.tsv
0xbc6e5c5  call 0xEEC6ED0 — target sub_eec6ed0 (0xeec6ed0; rcx = new SlotArray, rdx = 0, r8 = 0x410, r9 = 0); not in either table
0xbc6e646  call qword ptr [0xF99FFA0] — sub_eea6040 via data slot 0xF99FFA0 (rdx = old slot record); not in either table
0xbc6e689  call qword ptr [0xF99FFA0] — sub_eea6040 via data slot 0xF99FFA0 (r8 = limit*20); not in either table

CLOSES? NO calls to sub_eea6040 (data slot 0xF99FFA0 at 0xbc6e5b1, 0xbc6e646, 0xbc6e689) and sub_eec6ed0 (direct call at 0xbc6e5c5) are classified neither lift (docs/data/native_functions.tsv) nor boundary (docs/data/native_boundary.tsv); the calls cannot be emitted in lifted source and no wrapper may be invented, so the lift is incomplete.
