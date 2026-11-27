## NEXT
DONE — U-EX7.aa3c0 is complete: sub_aa3c0 (0xaa3c0, size 0x8) lifted, liftcheck passed, syntax checked.

## Result
Function 0xaa3c0 `sub_aa3c0` (Minecraft Windows 1.26.62.01), size 0x8 bytes, depth 0, milestone 7, region root, status D0, 0 callees in set. Disassembly [V: rdis dis 0xaa3c0 8 / rdis sum 0xaa3c0]:
- `0xaa3c0  lea rax,[0x128C1588]            ; [data_128c1588]`
- `0xaa3c7  ret`
Takes no arguments, reads/writes no memory, makes no calls, returns &data_128c1588 in RAX. Lifted as `extern "C" void* sub_aa3c0(void)` returning the address of an opaque `data_128c1588` object (pointee type not recoverable from this function alone — exactly one .text reference to 0x128C1588 exists, the lea itself at 0xaa3c3 [V: rdis ripscan 0x128c1588]; callers determine the pointee type [I]).

## FILES
- created src/client/features/render/native/helpers/sub_aa3c0.h (static_assert sizeof(void*)==8 x64 ABI, signature void* sub_aa3c0(void), layout note: no struct/object fields touched)
- created src/client/features/render/native/helpers/sub_aa3c0.cpp (first line `// LIFT 0xaa3c0 size 0x8 1.26.62.01 sub_aa3c0`, LIFT_FN registration, verbatim quotes, `// 0xaa3c0..0xaa3c8` range citation)
- created docs/functions/aa3c0.md (dossier; Reversed source (complete) section free of [?]/[I]/TODO/UNVERIFIED)
- created/changed this file docs/progress/oc_U-EX7.aa3c0.md
- changed by python tools/native_checklist_gen.py --add 0xaa3c0: docs/data/native_functions.tsv (row 0xaa3c0 0x8 depth 0 ms 7 root D0), docs/data/native_roots.txt, docs/data/native_deps.tsv, docs/data/native_boundary_candidates.tsv, docs/RENDER_CHECKLIST.md (checklist item X7.aa3c0)

## UNRESOLVED CALL
none (the function has no calls)

## LIFTCHECK
LIFTCHECK OK 0xaa3c0

Command: PYTHONUTF8=1 python tools/sigs/liftcheck.py 0xaa3c0 (exit 0). Cppsyntax check of the .cpp: OK (syntax).

## TOOL REQUESTS
None

CLOSES? YES
