## NEXT
DONE

## FILES
- docs/progress/oc_U-EX1.bcbe410.md (this result file; created)
- docs/functions/bcbe410.md (dossier created: signature, argument map, 'Reversed source (complete)' section, phases, struct fields, callees, open questions)
- src/client/features/render/native/bgfx/sub_bcbe410.h (created: signature, layout constant + static_assert, doc comment with verbatim instruction lines)
- src/client/features/render/native/bgfx/sub_bcbe410.cpp (created: first line `// LIFT 0xbcbe410 size 0x11 1.26.62.01 sub_bcbe410`, reversed body with `// 0xA..0xB` ranges, verbatim call log, static_assert, `LIFT_FN` registry entry)

## LIFTCHECK
LIFTCHECK OK 0xbcbe410

## UNRESOLVED CALL
0xEEC5AE0 (`sub_eec5ae0`), caller instruction `0xbcbe41b  call 0xEEC5AE0` inside [0xbcbe410, 0xbcbe421), with rcx = data slot 0xF571225 ("invalid bitset char", tag [data_f571225] [V]). The target is listed in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv (and not in src/sdk/Sigs.json), so it cannot be called from lifted code and no wrapper was invented; the call is quoted verbatim in the source and dossier but not emitted.

CLOSES? NO UNRESOLVED CALL 0xEEC5AE0 at 0xbcbe41b (`0xbcbe41b  call 0xEEC5AE0` -> sub_eec5ae0): not in docs/data/native_functions.tsv and not in docs/data/native_boundary.tsv
