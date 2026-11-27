## NEXT
DONE — lift complete and verified by liftcheck

UNIT: U-EX7.4e00d40 — sub_4e00d40 (0x4e00d40, size 0x94 bytes, depth 0, milestone 7, region root/D0, 0 callees in set)

## FILES
docs/functions/4e00d40.md (created — dossier with Reversed source (complete))
src/client/features/render/native/helpers/sub_4e00d40.h (created — layout constants + static_asserts, signature, forward declaration of native::sub_e935700)
src/client/features/render/native/helpers/sub_4e00d40.cpp (created — first line `// LIFT 0x4e00d40 size 0x94 1.26.62.01 sub_4e00d40`, LIFT_FN registry entry)
docs/progress/oc_U-EX7.4e00d40.md (this file)

## LIFTCHECK
LIFTCHECK OK 0x4e00d40
(exit code 0; `python tools/sigs/liftcheck.py 0x4e00d40` run from the repo root)

## UNRESOLVED CALL
none — 0x4e00d6d and 0x4e00db6 `call qword ptr [0xF99FFA0]` both resolve to sub_eea6040 (data slot 0xF99FFA0), boundary class vendor (docs/data/native_boundary.tsv), modeled as direct vtable-entry calls since sub_eea6040 is a `jmp rax` thunk (identical behavior); 0x4e00dc9 `jmp 0xE935700` -> native::sub_e935700 (lift set, already lifted, called through its native symbol); 0x4e00d53 `jmp rcx` computed tail jump modeled through a function-pointer type. No call target outside the lift set/boundary tables.

CLOSES? YES
