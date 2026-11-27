## NEXT
DONE. Unit closed (L1): liftcheck passed, no remaining steps.

## FILES
src/client/features/render/native/helpers/sub_3c75f0.cpp — first line `// LIFT 0x3c75f0 size 0xb2 1.26.62.01 sub_3c75f0`; full body with range citations + trailing verbatim comments; 5 plain call quotes in #if 0 block; LIFT_FN(sub_3c75f0, "sub_3c75f0", 0x3c75f0, sub_3c75f0, &sub_3c75f0_footprint); footprint {out, 0x18}.
src/client/features/render/native/helpers/sub_3c75f0.h — sub_3c75f0Out {field00,field08,field10} + sub_3c75f0Layout static_asserts (sizeof 0x18, offsets 0/8/0x10, RVA/VA constants, vfptr offsets 0x10/0x8); Boundary decls (void* return for sub_eec6ed0/sub_9bc830 because Lift.h:65 sizeof(R) is ill-formed for R=void; returns discarded with (void)cast).
docs/functions/3c75f0.md — signature/register map, phases, fields-touched table, callees table, data addresses, 'Reversed source (complete)', verbatim call quotes, ownership/threading, version anchors; open questions: none; no [?]/[I]/TODO/UNVERIFIED anywhere.

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x3c75f0` -> `LIFTCHECK OK 0x3c75f0`, exit 0.

## UNRESOLVED CALL
none (all callees boundary: 0x9bc830 alloc @ native_boundary.tsv:149; 0xeea6040 vendor thunk via slot 0xF99FFA0 @ line 506; 0xeec6ed0 crt IAT import thunk @ line 507; 0 callees in lift set).

CLOSES? YES
  step 1 (file written) done; step 2 (boundary tables): [V] native_boundary.tsv:149 `0x9bc830	alloc` (boundary alloc); [V] line 506 `0xeea6040	vendor thunk via data slot 0xF99FFA0`; [V] line 507 `0xeec6ed0	crt jmp qword ptr [IAT] import thunk`. All three callees are boundary, none UNRESOLVED.
  step 3 (dossier): [V] docs/functions/3c75f0.md does NOT exist (will be created).
Disassembly confirmed [V]: 0x3c75f0..0x3c76a2 (0xb2 bytes), 55 instructions, calls: 0x3c761b call qword ptr [0xF99FFA0] (sub_eea6040), 0x3c7635 call qword ptr [0xF99FFA0] (sub_eea6040), 0x3c765b call 0xEEC6ED0 (sub_eec6ed0), 0x3c7672 call qword ptr [0xF99FFA0] (sub_eea6040), 0x3c769a call 0x9BC830 (sub_9bc830). Image base 0x140000000 [V: sub_392960.h]; data RVAs 0x1233E1B0/0x1233E1A8 → VAs 0x15233E1B0/0x15233E1A8; slot 0xF99FFA0 → VA 0x14F99FFA0.

Contract: docs/RENDER_NATIVE_SPEC.md. Lift = C++ doing exactly what the exe function does (same reads/writes/calls/return, same x64 ABI). Quote every call verbatim as `0xRVA  call target`. Cite `// 0xA..0xB` beside every block. No stubs/TODO/[?]/[I]/UNVERIFIED in source or dossier reversed-source block.

Plan:
1. Disassemble 0x3c75f0 fully (confirm size 0xb2 and end 0x3c76a2); list callees.
2. Check docs/data/native_boundary.tsv / native_functions.tsv for 0x9bc830.
3. Read existing dossier docs/functions/3c75f0.md (input, not proof).
4. Write src/client/features/render/native/helpers/sub_3c75f0.cpp (first line LIFT marker) + .h (layout constants, static_asserts, signature, LIFT_FN registry).
5. Write docs/functions/3c75f0.md (analysis + Reversed source (complete)).
6. Run python tools/sigs/liftcheck.py 0x3c75f0; fix every failure; paste final output under ## LIFTCHECK.
7. Finish: ## FILES, ## UNRESOLVED CALL, final line CLOSES? YES / CLOSES? NO <blocking fact>.
