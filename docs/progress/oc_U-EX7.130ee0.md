## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_130ee0.h (rewritten): structs sub_130ee0_state (f0@0x00, f8@0x08, f10@0x10; sizeof 0x18) and sub_130ee0_refcounted (vptr@0x00, strong@0x08, weak@0x0C; sizeof 0x10); offsetof static_asserts for every field; declares native::sub_e935700(uintptr_t,uintptr_t) forward declaration and native::helpers::sub_130ee0
- src/client/features/render/native/helpers/sub_130ee0.cpp (rewritten): first line `// LIFT 0x130ee0 size 0xfb 1.26.62.01 sub_130ee0`; complete lifted body with `// 0xA..0xB` range citations on every block, verbatim call quotes for all 4 calls, goto-based block translation matching the CFG, reportValidationFailure helper for the noreturn [0xF9A8C78] path, LIFT_FN registry entry with footprint
- docs/functions/130ee0.md (rewritten): complete dossier with signature, argument map, instruction-complete phases, 'Reversed source (complete)', struct fields touched, callees, DECISIONS section, verbatim call quotes

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x130ee0` printed:

LIFTCHECK OK 0x130ee0

`python tools/ctx/gate.py 0x130ee0` printed:

GATE OK 0x130EE0

Full log in docs/progress/gate/0x130EE0.log.

## UNRESOLVED CALL
0x130fd4  call qword ptr [0xF9A8C78]  — data-slot invalid-parameter handler (loader-patched), noreturn, 5 zero args; target neither in lift set nor in native_boundary.tsv; documented with slot RVA per rule 69, no wrapper invented.

CLOSES? YES
