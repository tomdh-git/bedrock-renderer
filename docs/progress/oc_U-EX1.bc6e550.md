## NEXT
DONE

## STATUS
U-EX1.bc6e550 LIFT 0xbc6e550 size 0x216 complete (checklist: X1.bc6e550 LIFT sub_bc6e550 (0xbc6e550, 0x216 bytes, depth 4, D0, 0 callees in set)). Lifted source written verbatim from the disassembly of [0xbc6e550, 0xbc6e766): block-range coverage comments cite every instruction, all 4 calls quoted verbatim and routed through native::Boundary wrappers (sub_eea6040 vendor via data slot [0xF99FFA0], sub_eec6ed0 crt IAT thunk — docs/data/native_boundary.tsv rows 506-507, not blockers), exact x64 ABI signature preserved, record write order preserved (+0x0A, +0x00, +0x10, +0x11, +0x12, +0x04, +0x08), ready flag = 1 before void return, fail-fast (no null guards/SEH the original lacks). Dossier updated: callee table re-classified to boundary, open questions cleared.

## FILES
- src/client/features/render/native/bgfx/sub_bc6e550.h (new: layout constants sub_bc6e550_state/slot/record + static_asserts + signature decl)
- src/client/features/render/native/bgfx/sub_bc6e550.cpp (new: first line // LIFT 0xbc6e550 size 0x216 1.26.62.01 sub_bc6e550, lifted body, LIFT_FN registry entry)
- docs/functions/bc6e550.md (changed: callee table → boundary vendor/crt, call annotations re-classified, open questions cleared; Reversed source section kept verbatim, free of [?]/[I]/TODO/UNVERIFIED)
- docs/progress/oc_U-EX1.bc6e550.md (this file)

## LIFTCHECK
LIFTCHECK OK 0xbc6e550

## UNRESOLVED CALL
none

CLOSES? YES
