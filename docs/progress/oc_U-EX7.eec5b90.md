## NEXT
DONE — unit complete; CLOSES? YES

## FILES
Created:
- src/client/features/render/native/helpers/sub_eec5b90.cpp  (first line: // LIFT 0xeec5b90 size 0x6 1.26.62.01 sub_eec5b90; LIFT_FN registry entry; verbatim call quotes in #if 0 block)
- src/client/features/render/native/helpers/sub_eec5b90.h    (layout constants + static_asserts, signature, forward declaration of native::sub_eec5b90)
- docs/functions/eec5b90.md                                   (dossier: signature, argument map, disassembly/phases, reversed source, struct fields, callees, version anchors, ownership/threading)
Changed:
- docs/progress/oc_U-EX7.eec5b90.md (this result file)

## LIFTCHECK
LIFTCHECK OK 0xeec5b90

## UNRESOLVED CALL
none. The function (0xeec5b90, size 0x6) is a single instruction,
  0xeec5b90  jmp qword ptr [0xF9A7560]
an indirect tail jump through IAT/data slot 0xF9A7560 (.rdata). peptr reads slot 0xF9A7560 as 0xF9AB854 (import-by-name entry); peimports lists `0F9A7560  MSVCP140.dll!_Cnd_broadcast`. The target is MSVCP140!_Cnd_broadcast (_Thrd_result _Cnd_broadcast(_Cnd_t), _Cnd_t = _Cnd_internal_imp_t*), a CRT import resolved by the loader at runtime, documented via the slot RVA and called through its declared import signature (same pattern as sibling units sub_eec59e0/sub_eec59f0/sub_eec5a00). Not a lift-set callee and not a boundary wrapper; no UNRESOLVED CALL.

## Callees
0 callees in the lift set (per docs/progress/_d_U-EX7.eec5b90.txt). The single control transfer is the tail jump through slot 0xF9A7560 to MSVCP140!_Cnd_broadcast.

CLOSES? YES
