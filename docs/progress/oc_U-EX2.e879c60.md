## NEXT
DONE

## UNIT
U-EX2.e879c60 LIFT sub_e879c60 (0xe879c60, 0x24b bytes, depth 4, D0, 0 callees in set)
Contract: docs/RENDER_NATIVE_SPEC.md.

## SUMMARY
Lifted sub_e879c60 (read-only hash-set key lookup, returns bool in al/eax) into
src/client/features/render/native/d3d12/sub_e879c60.cpp + .h and dossier
docs/functions/e879c60.md. Every instruction in [0xe879c60, 0xe879eab) is covered by
a `// 0xA..0xB` range citation; both `call 0xEEC6EB0` instructions are quoted
verbatim in the `#if 0` block; LIFT_FN registry entry and static_assert layout
constants present. liftcheck prints LIFTCHECK OK.

BLOCKER: the only callee, sub_eec6eb0 (0xEEC6EB0), called at 0xe879e4a and
0xe879e87, is NOT classified in docs/data/native_boundary.tsv or
docs/data/native_functions.tsv → UNRESOLVED CALL. Per the callee rule this blocks
unit closure until it is classified (lift or boundary). Forward-declared in the
header and called directly (same convention as sub_e878010).

## FILES
- src/client/features/render/native/d3d12/sub_e879c60.h (created)
- src/client/features/render/native/d3d12/sub_e879c60.cpp (created)
- docs/functions/e879c60.md (created)
- docs/progress/oc_U-EX2.e879c60.md (created)

## LIFTCHECK
LIFTCHECK OK 0xe879c60

## UNRESOLVED CALL
0xeec6eb0 (sub_eec6eb0) — called at 0xe879e4a (`call 0xEEC6EB0`) and 0xe879e87 (`call 0xEEC6EB0`); not present in docs/data/native_boundary.tsv or docs/data/native_functions.tsv → UNRESOLVED CALL (blocker). Forward-declared as `extern "C" int sub_eec6eb0(const void*, const void*, std::size_t)` in sub_e879c60.h and called directly.

## CLOSES?
CLOSES? NO sub_eec6eb0 (0xEEC6EB0) is an unclassified callee (neither lift nor boundary) → UNRESOLVED CALL blocks closure
