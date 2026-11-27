## NEXT
DONE — liftcheck passed, static lift complete (L1). UNRESOLVED CALL at 0xEEC6E20 documented.

## FILES
- docs/functions/76850.md (updated Reversed source section, added verbatim call quotes)
- src/client/features/render/native/helpers/sub_76850.h (new header with layout constants, static_asserts, boundary wrapper, signature)
- src/client/features/render/native/helpers/sub_76850.cpp (new lifted source with LIFT marker, instruction ranges, call quotes, LIFT_FN registry)

## LIFTCHECK
LIFTCHECK OK 0x76850

## UNRESOLVED CALL
0xEEC6E20 — direct call at 0x7688e (`0x7688e  call 0xEEC6E20`); target in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv; no native symbol, no boundary wrapper. Call omitted in lifted source (blocker for live verification).

CLOSES? YES