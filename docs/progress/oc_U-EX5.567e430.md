## NEXT
DONE

Unit: X5.567e430 LIFT sub_567e430 (0x567e430, 0xdd bytes, depth 1, D0, 0 callees in set) — CLOSES? YES.

## FILES
- docs/progress/oc_U-EX5.567e430.md (this result file)
- docs/functions/567e430.md (dossier: mechanical facts, calls, Reversed source (complete))
- src/client/features/render/native/passes/sub_567e430.h (layout constants, static_asserts, signature, forward declaration of native::sub_e935700)
- src/client/features/render/native/passes/sub_567e430.cpp (lifted body, first line `// LIFT 0x567e430 size 0xdd 1.26.62.01 sub_567e430`, LIFT_FN registry entry, verbatim `#if 0` instruction block)

## LIFTCHECK
LIFTCHECK OK 0x567e430

(GATE OK 0x567E430 from python tools/ctx/gate.py 0x567e430; cppsyntax OK.)

## UNRESOLVED CALL
none. All four calls resolved statically:
- 0x567e440 `call 0x655CEA0` -> sub_655cea0 via native::Boundary<void,void*>("sub_655cea0") (boundary/stl, docs/data/native_boundary.tsv line 289)
- 0x567e483 `call 0xE935700` and 0x567e4d9 `call 0xE935700` -> native::sub_e935700 (lift set, helpers/sub_e935700.cpp)
- 0x567e506 `call qword ptr [0xF9A8C78]` -> target read from data slot 0xF9A8C78 at call time (brief rule 69), 4 zero args, then int3 (noreturn fail path); no static callee target exists in either table, and rule 69 covers it, so it is not a blocker.

CLOSES? YES
