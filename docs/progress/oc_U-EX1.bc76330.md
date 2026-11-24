## NEXT
DONE — sub_bc76330 lifted: docs/functions/bc76330.md, src/client/features/render/native/bgfx/sub_bc76330.h and sub_bc76330.cpp written; `python tools/sigs/liftcheck.py 0xbc76330` printed LIFTCHECK OK 0xbc76330. Unit complete, no further steps.

## STATUS
Unit U-EX1.bc76330: lift sub_bc76330 (0xbc76330, 0x4a bytes, depth 7, D0, bgfx, leaf; 0 callees in lift set).
- Disassembly read: [0xbc76330, 0xbc7637a), 25 instructions; single call site 0xbc76369 `call 0xEBCE5E0`; int3 padding 0xbc7637a..0xbc7637f, next function at 0xbc76380 (not part of this unit).
- docs/data/native_boundary.tsv line 504: 0xebce5e0 = class lift -> forward-declared `native::sub_ebce5e0(const char* s, uint32_t maxlen) -> uint32_t` and called directly; not a blocker, no wrapper.
- sub_ebce5e0 head verified by rdis: `test rcx,rcx / jne / xor eax,eax / ret` null path, then bounded NUL scan (strnlen-like).
- Wrote docs/functions/bc76330.md (dossier: mechanical facts, signature, reversed source complete with verbatim call log, struct fields, verification).
- Wrote src/client/features/render/native/bgfx/sub_bc76330.h (Bc76330State +0x00 name / +0x08 nameLen / +0x0c reserved / +0x10 flag; Bc76330Arg +0x00 name / +0x08 maxLen; static_asserts; forward-declared native::sub_ebce5e0; signature).
- Wrote src/client/features/render/native/bgfx/sub_bc76330.cpp (first line `// LIFT 0xbc76330 size 0x4a 1.26.62.01 sub_bc76330`; ranges // 0xbc76330..0xbc76342 and // 0xbc76343..0xbc76378; verbatim call log; LIFT_FN registry entry).
- liftcheck run 1 failed twice (source scan on "unresolved calls"; static_assert missing from the .cpp); both fixed; run 2 printed LIFTCHECK OK 0xbc76330.

## FILES
- docs/progress/oc_U-EX1.bc76330.md (created — this result file)
- docs/functions/bc76330.md (created — dossier)
- src/client/features/render/native/bgfx/sub_bc76330.h (created)
- src/client/features/render/native/bgfx/sub_bc76330.cpp (created)
No other files edited (no Sigs.json, no shared headers, no CMake, no hooks, no other units' files; no build; no game started).

## LIFTCHECK
LIFTCHECK OK 0xbc76330

## UNRESOLVED CALL
none

CLOSES? YES
