## NEXT
DONE: sub_661a2f0 fully lifted, LIFTCHECK OK and GATE OK.

## UNIT
U-EX4.661a2f0: lift sub_661a2f0 (0x661a2f0, size 0xce, depth 0, D0, framebuilder, "BgfxFrameBuilder slot 30"). Range [0x661a2f0, 0x661a3be).

## DATA
- Size 0xce (206 bytes) => range [0x661a2f0, 0x661a3be) [V: pack + rdis dis]
- Callees: 0xeec6d80 (sub_eec6d80, lift set, noreturn throw) [V: pack]; 0xe951550 (sub_e951550, boundary crt, noreturn) [V: pack]
- Callers: 0 [V: pack]
- Logic: validates a1[0] and a1[4] (each >= 0.0 and round-trips through u16); on success stores (uint16_t)(int)a1[0] at a0+0x6EE and (uint16_t)(int)a1[4] at a0+0x6F0. On failure calls sub_eec6d80 with exception object qword 0xF08E738 and throw-info rdx 0xFB3B080. Stack cookie via [0x1230A0C0]; mismatch calls sub_e951550. Reads a0+0x6EA and a0+0x6EC feed dead cmovb (results unused) [V: rdis listing].

## FILES
- docs/progress/oc_U-EX4.661a2f0.md (this result file, created/updated)
- docs/functions/661a2f0.md (dossier with Reversed source (complete), created)
- src/client/features/render/native/framebuilder/sub_661a2f0.h (created: Slot30 layout, static_asserts, signature)
- src/client/features/render/native/framebuilder/sub_661a2f0.cpp (created: LIFT source, verbatim quotes, LIFT_FN registry)

## LIFTCHECK
LIFTCHECK OK 0x661a2f0

## UNRESOLVED CALL
none

## CLOSES
CLOSES? YES
