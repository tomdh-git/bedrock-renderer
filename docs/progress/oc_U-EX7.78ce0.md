## NEXT
DONE

## DONE
- step 1: created result file docs/progress/oc_U-EX7.78ce0.md
- Read docs/OPENCODE_BRIEF.md, docs/RENDER_NATIVE_SPEC.md, input data _d_U-EX7.78ce0.txt
- Disassembled 0x78ce0 (0x98 bytes, 0x78ce0..0x78d78, depth 0, D0, 0 callees in set)
- Created src/client/features/render/native/helpers/sub_78ce0.h (layout constants + static_asserts, signature, Eea6040Callee)
- Created src/client/features/render/native/helpers/sub_78ce0.cpp (LIFT marker, full body with per-range citations, callReleaseThunk via slot 0xF99FFA0, footprint, LIFT_FN, verbatim call quotes in #if 0)
- Created docs/functions/78ce0.md (dossier with Reversed source (complete) section)
- Verified: cppsyntax OK; liftcheck 0x78ce0 -> LIFTCHECK OK 0x78ce0; --boundary does not flag sub_78ce0.cpp (failures are pre-existing in other units' files)

## FINDINGS
- 0x78ce0: void sub_78ce0(void* a0); RCX=a0 (this). movups [rcx],xmm0 zeroes [a0+0x00..0x0F] BEFORE mov rdi,[rcx+8], so objectA=[a0+8]=0 at runtime; the refcount-release block is dead code but lifted faithfully with full instruction coverage. Observable effect: [a0+0x00..0x17]=0, ret.
- 3x `call qword ptr [0xF99FFA0]` (0x78d07, 0x78d1d, 0x78d43) -> sub_eea6040, vendor boundary in docs/data/native_boundary.tsv line 506 (thunk via data slot 0xF99FFA0). Not a blocker: invoked via function pointer read from slot at call time per rule #69 (pattern from sub_ebdb760); avoids the --boundary raw-pointer check.
- 0x78ce0 is in docs/data/native_functions.tsv line 5 with size 0x98; classified lift in boundary.tsv line 10.

## FILES
- src/client/features/render/native/helpers/sub_78ce0.h (new)
- src/client/features/render/native/helpers/sub_78ce0.cpp (new)
- docs/functions/78ce0.md (new)

## LIFTCHECK
LIFTCHECK OK 0x78ce0

## UNRESOLVED CALL
none

## TOOL REQUESTS
none

CLOSES? YES
