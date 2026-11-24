## NEXT
DONE — liftcheck printed LIFTCHECK OK 0xbc40a30

## FILES
- docs/progress/oc_U-EX1.bc40a30.md (this result file)
- docs/functions/bc40a30.md (dossier: signature, phases, struct fields, callees, Reversed source (complete))
- src/client/features/render/native/bgfx/sub_bc40a30.h (layout constants + static_asserts, declaration)
- src/client/features/render/native/bgfx/sub_bc40a30.cpp (lifted C++, first line // LIFT 0xbc40a30 size 0x146 1.26.62.01 endFrame, LIFT_FN registry entry)

## LIFTCHECK
LIFTCHECK OK 0xbc40a30

## UNRESOLVED CALL
none

All 6 external call targets are CRT/library intrinsics per spec §5/6:
- 0xbc40ad0  call qword ptr [0xF99FFA0]  malloc (IAT thunk, sub_eea6040 jmp rax)
- 0xbc40af4  call qword ptr [0xF99FFA0]  malloc (IAT thunk)
- 0xbc40b17  call 0xEEC6EC0              memcpy thunk (jmp [0xF9A8A98])
- 0xbc40b5b  call 0x9BC830              CRT heap failure handler (noreturn in practice)
- 0xbc40b68  call 0x75720                invalid_parameter ("string too long", noreturn)
- 0xbc40b70  call 0x9BC830              CRT heap failure handler
None are game functions requiring a boundary wrapper; no native_boundary.tsv exists and none is needed.

CLOSES? YES
