## NEXT
DONE: sub_bc6ee00 lifted (dossier docs/functions/bc6ee00.md; source src/client/features/render/native/bgfx/sub_bc6ee00.cpp + .h). liftcheck prints LIFTCHECK OK 0xbc6ee00, but the unit cannot close: all 3 callees are unclassified (not in docs/data/native_functions.tsv nor docs/data/native_boundary.tsv), so they are UNRESOLVED CALL blockers per the GOAL — no wrapper invented, CLOSES? NO.

## FILES
- docs/progress/oc_U-EX1.bc6ee00.md (this file)
- docs/functions/bc6ee00.md (dossier: signature, register map, Reversed source (complete), fields touched, callees, call claims)
- src/client/features/render/native/bgfx/sub_bc6ee00.h (layout constants, static_asserts, ABI signature, forward declarations of unclassified callees)
- src/client/features/render/native/bgfx/sub_bc6ee00.cpp (// LIFT marker, lifted body with verbatim call quotes and cited ranges, LIFT_FN registry entry)

## LIFTCHECK
LIFTCHECK OK 0xbc6ee00

(from `python tools/sigs/liftcheck.py 0xbc6ee00`; liftcheck runs verify_oc internally: mismatch=0, no-such-instr=0; dossier Reversed source block is free of [?]/[I]/TODO/UNVERIFIED; source has the LIFT marker with size 0x122, LIFT_FN entry, static_asserts; 100% instruction coverage of [0xbc6ee00, 0xbc6ef22) by cited ranges; all 3 calls quoted verbatim.)

## UNRESOLVED CALL
- 0xEBDBF10 sub_ebdbf10 — caller instruction: `0xbc6ee27  call 0xEBDBF10` (preceded by 0xbc6ee24  mov rcx,rdi; rcx = a0 + 0x1C0; return value in rax unused). Seen verbatim in the disassembly at 0xbc6ee27. Absent from docs/data/native_functions.tsv, docs/data/native_boundary.tsv, docs/data/function_classes.tsv and Sigs.json → no sanctioned call mechanism (no native symbol, no boundary wrapper, not lift-classified).
- 0xEEC6EC0 sub_eec6ec0 — caller instruction: `0xbc6ee43  call 0xEEC6EC0` (rcx = a1, rdx = r14 + 0xE60DE8, r8d = 0xD0; return unused). Same absence from both tables → same status.
- 0xEBDBF20 sub_ebdbf20 — caller instruction: `0xbc6ef0e  call 0xEBDBF20` (preceded by 0xbc6ef0b  mov rcx,rdi; rcx = a0 + 0x1C0; return unused, mov rax,rsi follows). Same absence from both tables → same status.

CLOSES? NO UNRESOLVED CALL: calls to 0xEBDBF10 (0xbc6ee27), 0xEEC6EC0 (0xbc6ee43) and 0xEBDBF20 (0xbc6ef0e) have targets in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv (also absent from Sigs.json and function_classes.tsv), so they cannot be called from lifted code through a native symbol or a boundary wrapper and no wrapper may be invented; the lift is statically complete except for these 3 calls.
