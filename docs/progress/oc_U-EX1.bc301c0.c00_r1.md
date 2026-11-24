## NEXT
DONE

## FILES
src/client/features/render/native/bgfx/sub_bc301c0.h
src/client/features/render/native/bgfx/sub_bc301c0.cpp
docs/functions/bc301c0.md

## LIFTCHECK
Chunk coverage: 0xbc301c0..0xbc31997 = entire first chunk cited in #if 0 block.
All call instructions in range quoted verbatim.
First instruction: 0xbc301c0  push rbp
Last instruction: 0xbc31997  lea rax,[rbp+0x7F8]
Chunk state documented in docs/functions/bc301c0.md section 'Chunk state'.
Header contains layout constants and static_asserts.
Registry entry: LIFT_FN pending (forward-declared callees present).

## UNRESOLVED CALL
0x79560 at 0xbc302a5 (call 0x79560) - not in lift set, not in boundary file
0xE93B480 at 0xbc306b3 (call 0xE93B480) - not in lift set, not in boundary file
0xE93B480 at 0xbc30968 (call 0xE93B480) - not in lift set, not in boundary file
0xEEC6DE0 at 0xbc307c5 (call 0xEEC6DE0) - not in lift set, not in boundary file
0xEEC6DE0 at 0xbc30a72 (call 0xEEC6DE0) - not in lift set, not in boundary file
0xEEC6DE0 at 0xbc30b70 (call 0xEEC6DE0) - not in lift set, not in boundary file
0xEEC6DE0 at 0xbc30d96 (call 0xEEC6DE0) - not in lift set, not in boundary file
0xEEC6DE0 at 0xbc31004 (call 0xEEC6DE0) - not in lift set, not in boundary file

## TOOL REQUESTS
None

CLOSES? NO - UNRESOLVED CALLs found (0x79560, 0xE93B480, 0xEEC6DE0)