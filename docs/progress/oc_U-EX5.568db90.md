## NEXT
DONE

Unit: U-EX5.568db90, function 0x568db90, size 0x80 bytes, depth 1, milestone D0, region pass-tasks, name "Scene/HUD view-setup task", 0 callees in lift set.

## FILES
- src/client/features/render/native/passes/sub_568db90.h (created: ViewElem layout constants + static_asserts, sub_e935700 forward declaration, sub_568db90 signature)
- src/client/features/render/native/passes/sub_568db90.cpp (created: lifted body, // LIFT marker, LIFT_FN registry entry, verbatim call quotes in #if 0 block)
- docs/functions/568db90.md (created: dossier with Reversed source section, struct fields, callees, phase walk)

## LIFTCHECK
LIFTCHECK OK 0x568db90

## UNRESOLVED CALL
none

Both calls resolved:
- 0x568dbdd  call 0xE935700  -> sub_e935700, class lift (native_boundary.tsv line 505), forward-declared and called directly
- 0x568dc09  call qword ptr [0xF9A8C78]  -> data slot fail handler (read at call time, noreturn + int3), not a blocker per hard rule

CLOSES? YES
