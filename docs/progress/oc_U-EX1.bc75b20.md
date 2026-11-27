## NEXT
DONE — all files written, running verification

## UNIT
rva=0xbc75b20 size=0xb9 depth=2 milestone=1 region=bgfx status=D0 name="Item group visitor" callee_in_set=0xebce650

## PLAN
- [x] read data files (native_boundary.tsv, native_functions.tsv, native_deps.tsv) to classify the 4 callees
- [x] read lifted callee headers (sub_ebdbf10.h, sub_ebce5e0.h, sub_ebce650.h, sub_ebdbf20.h) for exact ABI signatures
- [x] run rdis dis 0xbc75b20 0xb9 to get verbatim instruction text for quoting
- [x] write docs/functions/bc75b20.md dossier (analysis + Reversed source (complete))
- [x] write src/client/features/render/native/bgfx/sub_bc75b20.cpp (+ .h) with LIFT marker, LIFT_FN registry, static_asserts, forward decls for lift callees
- [x] run cppsyntax.py to syntax-check
- [ ] run liftcheck.py 0xbc75b20, fix failures, paste output under ## LIFTCHECK
- [ ] run gate.py 0xbc75b20, then CLOSES? YES/NO

## FILES
- docs/progress/oc_U-EX1.bc75b20.md (result file)
- docs/functions/bc75b20.md (dossier)
- src/client/features/render/native/bgfx/sub_bc75b20.h (header with layout constants and static_asserts)
- src/client/features/render/native/bgfx/sub_bc75b20.cpp (lifted source with LIFT marker + LIFT_FN)

## LIFTCHECK
(pending — about to run)

## UNRESOLVED CALL
none — all 4 callees (ebdbf10, ebce5e0, ebce650, ebdbf20) are class lift in native_boundary.tsv, called through native symbols

## TOOL REQUESTS
None yet
