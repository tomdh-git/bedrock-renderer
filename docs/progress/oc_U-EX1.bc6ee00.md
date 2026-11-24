## NEXT DONE

## UNIT
U-EX1.bc6ee00 — sub_bc6ee00 (0xbc6ee00, size 0x122, depth 5, D0, bgfx). Result file: docs/progress/oc_U-EX1.bc6ee00.md.

## FACTS [V] from disassembly (rdis dis 0xbc6ee00; matches dossier exactly)
- 0xbc6ee00..0xbc6ef21: straight-line function, 48 instructions, ends `ret` at 0xbc6ef21 → size 0x122 confirmed [0xbc6ee00+0x122 = 0xbc6ef22].
- Calls: 0xbc6ee27 call 0xEBDBF10 (rcx = a0+0x1C0); 0xbc6ee43 call 0xEEC6EC0 (rcx=a1, rdx=r14+0xE60DE8, r8d=0xD0); 0xbc6ef0e call 0xEBDBF20 (rcx = a0+0x1C0). All returns dead.
- native_boundary.tsv lines 510-512: 0xebdbf10, 0xebdbf20, 0xeec6ec0 all class `lift` (auto-unresolved->lift) → forward-declare + direct call per hard rule 66; not blockers, no UNRESOLVED CALL.

## EDITS [done]
1. docs/progress/oc_U-EX1.bc6ee00.md — result file created (line 1 `## NEXT`, line 2 `step 2`); now finalized below.
2. src/client/features/render/native/bgfx/sub_bc6ee00.h — added `namespace native { extern "C" void sub_ebdbf10(void*); void sub_eec6ec0(void*, const void*, uint32_t); void sub_ebdbf20(void*); }` forward declarations with call-site signatures; callees marked `lift` per boundary tsv 510-512.
3. src/client/features/render/native/bgfx/sub_bc6ee00.cpp — replaced stale callee declarations block with header forward-declaration reference.
4. docs/functions/bc6ee00.md — rewrote ## Callees (all three `lift` with boundary tsv line citations); ## OPEN questions: None; no blockers.

## FILES
- docs/progress/oc_U-EX1.bc6ee00.md (this result file)
- src/client/features/render/native/bgfx/sub_bc6ee00.h
- src/client/features/render/native/bgfx/sub_bc6ee00.cpp
- docs/functions/bc6ee00.md

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc6ee00` → `LIFTCHECK OK 0xbc6ee00` (exit 0); verified twice, both OK.

## UNRESOLVED CALL
none — all three callees class `lift` (boundary tsv 510-512), forwarded in `namespace native` per hard rule 66.

## Sigs.json / CMake / hooks
no edits (per scope).

## BUILD
no build performed (per scope).

CLOSES? YES

Done: lift complete, liftcheck OK, all callees `lift` (boundary tsv 510-512), forward-declared in `namespace native` per hard rule 66, no unresolved calls, no wrapper, no Sigs.json/CMake/hooks changes, no builds. FINAL CONFIRMATION: no remaining steps; unit closed.
