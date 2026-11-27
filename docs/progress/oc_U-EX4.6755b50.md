## NEXT
DONE

## UNIT
U-EX4.6755b50: lift sub_6755b50 (0x6755b50, 0xe2 bytes, depth 2, D0, framebuilder, "BgfxFrameBuilder slot 11", 0 callees in set) — CLOSES? YES.

## FILES
- docs/progress/oc_U-EX4.6755b50.md (this result file)
- docs/functions/6755b50.md (dossier: signature, register/argument map, 'Reversed source (complete)', struct fields, callees, verbatim instruction quotes)
- src/client/features/render/native/framebuilder/sub_6755b50.h (layout constants Sub6755b50Container/Sub6755b50Object + static_asserts, signature, boundary::g_eea6040_thunk forward declaration)
- src/client/features/render/native/framebuilder/sub_6755b50.cpp (lifted source: LIFT marker first line, full reversed source with // 0xA..0xB citations, LIFT_FN registry entry, verbatim call quotes in #if 0 block)

## SUMMARY
Function [0x6755b50, 0x6755c32), 0xe2 bytes. Prologue push rsi/push rdi/sub rsp,0x28; mov eax,0x33; bt rax,rcx: bit (RCX&31) of mask 0x33 set -> epilogue ret (0x6755b61..0x6755b67); bit clear -> cmp rcx,2, RCX==2 skips to slot [r8+8]. Releases up to three refcounted objects in the container (R8): slots +0x38 (0x6755b6e), +0x28 (0x6755bab), +0x08 (0x6755be8). Each object: lock dec [obj+0x8]; on zero call vfptr[0] via `call qword ptr [0xF99FFA0]`; lock dec [obj+0xC]; on zero call vfptr[1] via the same slot. Last slot's second count ends with mov rdx,[0xF99FFA0] / jmp rdx tail call (0x6755c2f). sub_eea6040 (0xeea6040) is a `jmp rax` noreturn thunk [V: rdis dis 0xeea6040] and is listed in docs/data/native_boundary.tsv (row 0xeea6040, vendor, "thunk via data slot 0xF99FFA0 (loader-resolved)") -> boundary callee, called through native::boundary::g_eea6040_thunk per the framebuilder convention. No other callees; 0 callees in the lift set; no unresolved calls. All 70 instructions cited/quoted verbatim; all 5 calls quoted; static_asserts on every struct offset used; registry entry LIFT_FN(sub_6755b50, ...).

## LIFTCHECK
LIFTCHECK OK 0x6755b50

## UNRESOLVED CALL
none

CLOSES? YES
