## NEXT
DONE: sub_eec73f0 (0xeec73f0, size 0x6) lifted L1. The function is one instruction:
0xeec73f0  jmp qword ptr [0xF9A8E08] — an indirect tail jump through data slot 0xF9A8E08,
which resolves (PE import table) to import-by-name RVA 0xF9B07CC, hint 0x7d, name "ceilf"
(float ceilf(float), MSVC CRT). Lifted as `float sub_eec73f0(float value)` forwarding to
`std::ceilf(value)` (XMM0 in, XMM0 out), following the sub_eec5850/sub_eec6ec0 thunk pattern.
Artifacts: helpers/sub_eec73f0.cpp (+.h), docs/functions/eec73f0.md dossier.
LIFTCHECK printed `LIFTCHECK OK 0xeec73f0`. CLOSES? YES.

## FILES
src/client/features/render/native/helpers/sub_eec73f0.cpp   (created)
src/client/features/render/native/helpers/sub_eec73f0.h     (created)
docs/functions/eec73f0.md                                   (created)
docs/progress/oc_U-EX7.eec73f0.md                           (created, this result file)

## LIFTCHECK
LIFTCHECK OK 0xeec73f0
(exit code 0; `python tools/sigs/liftcheck.py 0xeec73f0`)

## UNRESOLVED CALL
none — the only control transfer is a `jmp` (not a `call`) through data slot 0xF9A8E08
resolved to CRT ceilf via import-by-name RVA 0xF9B07CC, called directly as std::ceilf.

CLOSES? YES
