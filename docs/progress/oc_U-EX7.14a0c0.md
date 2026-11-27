## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_14a0c0.h  (finished lift: signature decided, rdx struct gained f0 at +0x0 for the 0x14a138 read, static_asserts for every field read/written)
- src/client/features/render/native/helpers/sub_14a0c0.cpp  (finished lift: block-by-block translation of [0x14a0c0, 0x14a1f0), all __debugbreak() placeholders replaced, verbatim call log kept)
- docs/functions/14a0c0.md  (appended ## Reversed source (complete) section)

## LIFTCHECK
GATE OK 0x14A0C0 via python tools/ctx/gate.py 0x14a0c0:
  - cppsyntax: sub_14a0c0.cpp OK (MSVC /Zs, no errors)
  - liftcheck: OK (dossier Reversed source section present and clean, LIFT marker size 0x130 matches native_functions.tsv, no stub/TODO markers, LIFT_FN registry entry present, static_asserts present, instruction coverage complete, all 7 calls quoted verbatim, verify_oc mismatch=0)
  - static_assert layout check: present in .cpp (mirrored from .h)

## UNRESOLVED CALL
none. All calls are modeled: sub_14a260 (0x14a103 call 0x14A260), sub_14a430 (0x14a163 call 0x14A430), sub_14abf0 (0x14a18a call 0x14ABF0) are forward-declared native symbols with open signatures (not in the lift set, no native_boundary.tsv entry yet); sub_eea6040 (0x14a143/0x14a1ac/0x14a1c2/0x14a1dc call qword ptr [0xF99FFA0]) is called through data slot 0xF99FFA0 (pack: [data_f99ffa0] = sub_eea6040), modeled as sub_eea6040(object, auxiliary) with the slot dereferenced once.

CLOSES? YES
