## NEXT
DONE - lift of sub_6ae330 complete; LIFTCHECK OK 0x6ae330 and GATE OK 0x6AE330.

## GOAL
LIFT TASK: lift sub_6ae330 (0x6ae330, size 0xd4 bytes, depth 0, D0, 0 callees in set per data file; pack states 1 direct callee sub_e935700).

## FILES
- src/client/features/render/native/helpers/sub_6ae330.h (new: layout constants + static_asserts + signature + forward declaration of sub_e935700)
- src/client/features/render/native/helpers/sub_6ae330.cpp (new: lifted body, first line `// LIFT 0x6ae330 size 0xd4 1.26.62.01 sub_6ae330`, LIFT_FN registry entry)
- docs/functions/6ae330.md (new: dossier with Reversed source (complete), struct fields, calls)

## DISASSEMBLY (verbatim from rdis dis 0x6ae330 0xd4)
Range [0x6ae330, 0x6ae404). Calls:
0x6ae37d  call qword ptr [0xF99FFA0]   ; sub_eea6040 via data slot (vendor boundary)
0x6ae399  call qword ptr [0xF99FFA0]   ; sub_eea6040 via data slot (vendor boundary)
0x6ae3cf  call 0xE935700               ; sub_e935700 (lift set)
0x6ae3fd  call qword ptr [0xF9A8C78]   ; fatal via data slot (rule #69 indirect data-slot call)

## LIFTCHECK
LIFTCHECK OK 0x6ae330

## UNRESOLVED CALL
none
- sub_e935700 is in the lift set and called through its native symbol `native::sub_e935700`.
- 0xF99FFA0 = sub_eea6040 is a vendor boundary (data-slot thunk), called via slot read per rule #69.
- 0xF9A8C78 is an indirect call through data slot 0xF9A8C78 (rule #69: read pointer at call time, call as function pointer with four null args); not a blocker.

## CLOSES?
CLOSES? YES
