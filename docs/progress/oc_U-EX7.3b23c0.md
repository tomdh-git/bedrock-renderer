## NEXT
DONE — sub_3b23c0 lifted; LIFTCHECK OK 0x3b23c0; CLOSES? YES.

## UNIT
U-EX7.3b23c0 — lift sub_3b23c0 (0x3b23c0, 0x8 bytes, depth 0, D0, 0 callees in set), Minecraft Bedrock 1.26.62.01.

## GOAL
Lift function 0x3b23c0 to C++ with the exact x64 ABI signature; artifacts: docs/progress/oc_U-EX7.3b23c0.md, docs/functions/3b23c0.md, src/client/features/render/native/helpers/sub_3b23c0.cpp + .h; finish with `python tools/sigs/liftcheck.py 0x3b23c0`.

## FINDINGS (from rdis dis 0x3b23c0)
- 0x3b23c0  lea rax,[0x128CC490]                          ; [data_128cc490]
- 0x3b23c7  ret
Function extent [0x3b23c0, 0x3b23c8) = 0x8 bytes (matches docs/data/native_functions.tsv row; rdis sum range [0x3b23c0, 0x3b23c8)). No calls, no callees. Next instruction at 0x3b23c8 belongs to a different function.
- Caller 0xeea5f69: `call 0x3B23C0` then `or qword ptr [rax],2` → returned pointer used as qword (uint64_t*), data_128cc490 is a qword global. [V]
Signature: std::uint64_t* sub_3b23c0(void); returns &data_128cc490 in RAX; no arguments read. Pure function (no reads/writes).

## FILES
- docs/progress/oc_U-EX7.3b23c0.md (this result file, created/updated)
- docs/functions/3b23c0.md (dossier, created; 'Reversed source (complete)' section)
- src/client/features/render/native/helpers/sub_3b23c0.cpp (created; first line LIFT marker; LIFT_FN registration)
- src/client/features/render/native/helpers/sub_3b23c0.h (created; layout constants + static_asserts + signature)

## LIFTCHECK
LIFTCHECK OK 0x3b23c0

## UNRESOLVED CALL
none (function has no calls; 0 callees)

## Verification
- `python tools/sigs/liftcheck.py 0x3b23c0` -> LIFTCHECK OK 0x3b23c0 (exit 0)
- `python tools/cppsyntax.py sub_3b23c0.cpp` -> OK (syntax)
- No calls, so no call quotes required; both instructions (0x3b23c0, 0x3b23c7) covered by cited range `0x3b23c0..0x3b23c8` and verbatim quotes.
- No [?]/[I]/TODO/UNVERIFIED/UNRESOLVED/stub tags in source or dossier.
- static_assert present in header; LIFT_FN registry entry present in source.

CLOSES? YES
