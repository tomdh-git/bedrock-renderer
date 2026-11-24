## NEXT
DONE. Unit closed.

## UNIT
U-EX1.bc6e360: lift sub_bc6e360 (0xbc6e360, 0x1eb bytes, depth 4, D0, 0 callees in set). CLOSES? YES.

## FILES
- docs/progress/oc_U-EX1.bc6e360.md (this result file)
- src/client/features/render/native/bgfx/sub_bc6e360.cpp (rewritten: first line `// LIFT 0xbc6e360 size 0x1eb 1.26.62.01 sub_bc6e360`; native::Boundary for sub_eec6ed0; data-slot call for sub_eea6040 via [0xF99FFA0]; allocator_global() from [0x12ADF800]; LIFT_FN; static_asserts; all 4 calls quoted verbatim; range 0xbc6e360..0xbc6e54a covers all instructions)
- src/client/features/render/native/bgfx/sub_bc6e360.h (existing: layout structs + static_asserts + signature; verified OK, no change needed)
- docs/functions/bc6e360.md (dossier: replaced 'Reversed source (complete)' with complete corrected source, free of [?]/[I]/TODO/UNVERIFIED)

## CALLS (all verbatim, all resolved)
0xbc6e3c1  call qword ptr [0xF99FFA0]  -> sub_eea6040 via data slot [0xF99FFA0] (vendor thunk, boundary.tsv:506; hard rule 69, not a blocker)
0xbc6e3d5  call 0xEEC6ED0              -> sub_eec6ed0 via native::Boundary<void,void*,u64,u64,u64>("sub_eec6ed0") (crt IAT thunk, boundary.tsv:507; orchestrator hint)
0xbc6e456  call qword ptr [0xF99FFA0]  -> sub_eea6040 via data slot
0xbc6e499  call qword ptr [0xF99FFA0]  -> sub_eea6040 via data slot

## LIFTCHECK
LIFTCHECK OK 0xbc6e360

## UNRESOLVED CALL
none

## TOOL REQUESTS
none

CLOSES? YES
