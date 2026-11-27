## NEXT
DONE — unit complete: 0xe809cc0 lifted (L1), liftcheck prints LIFTCHECK OK 0xe809cc0.

UNIT: U-EX2.e809cc0 | fn 0xe809cc0 size 0xa1 ([0xe809cc0, 0xe809d61)), depth 1, D0, region d3d12, name sub_e809cc0
Callee in lift set: 0xe839020 (native::d3d12::sub_e839020(void*, void*), header sub_e839020.h)
Indirect calls: 0xe809d2b and 0xe809d4f `call qword ptr [0xF99FFA0]`; data slot holds sub_eea6040 (vendor boundary, docs/data/native_boundary.tsv line 506; `jmp rax` thunk). Net effect: obj->vptr[4](obj) via rax = [obj->vptr + 0x20]. No unresolved callees.

Artifacts:
- docs/progress/oc_U-EX2.e809cc0.md (this file)
- docs/functions/e809cc0.md (dossier, new; 'Reversed source (complete)' section)
- src/client/features/render/native/d3d12/sub_e809cc0.h (new; layout constants + static_asserts + signature)
- src/client/features/render/native/d3d12/sub_e809cc0.cpp (new; first line is the LIFT marker, body, verbatim call log, LIFT_FN registration)

## FILES
src/client/features/render/native/d3d12/sub_e809cc0.h
src/client/features/render/native/d3d12/sub_e809cc0.cpp
docs/functions/e809cc0.md
docs/progress/oc_U-EX2.e809cc0.md

## LIFTCHECK
LIFTCHECK OK 0xe809cc0

## UNRESOLVED CALL
none

CLOSES? YES
