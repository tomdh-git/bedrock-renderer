## NEXT
DONE — unit complete. LIFTCHECK OK 0xbc3c6b0.

## UNIT
U-EX1.bc3c6b0 — LIFT sub_bc3c6b0 at 0xbc3c6b0, size 0xcb, depth 3, region bgfx/D0, status D0→L1. Checklist line: X1.bc3c6b0 LIFT sub_bc3c6b0 (0xbc3c6b0, 0xcb bytes, depth 3, D0, 0 callees in set). Exe: Minecraft.Windows.exe 1.26.62.01 (image data only, static analysis via rdis.exe). No game runs, no builds.

## INPUT DATA (docs/progress/_d_U-EX1.bc3c6b0.txt)
- Function row: 0xbc3c6b0 size 0xcb depth 3 milestone 1 region bgfx/D0 name "BgfxFrameBuilder slot 0", root empty, callees_in_set empty, callees_outside_set empty.
- CALLEES IN THE LIFT SET: none listed.

## rdis FINDINGS (verified from the exe)
- `rdis fn 0xbc3c6b0 --max 200`: full listing 0xbc3c6b0..0xbc3c77b (0xcb bytes), 14 blocks, all reached by dataflow.
- `rdis callees 0xbc3c6b0`: direct `call sub_e935700` x2 (0xbc3c6f8, 0xbc3c741, trust proven); indirect `call qword ptr [0xF9A8C78]` at 0xbc3c774 (kind indirect-global, args 0/0/0/0, trust unknown, via 0xf9a8c78).
- `rdis dis 0xe935700 8`: sub_e935700 = `jmp 0x392960` (tail) then int3 padding; extent "heuristic(no .pdata entry)".
- sub_e935700 / sub_392960: NOT in docs/data/native_functions.tsv and NOT in docs/data/native_boundary.tsv.
- `call qword ptr [0xF9A8C78]`: not in native_boundary.tsv, native_unresolved_indirect.tsv, or native_boundary_candidates.tsv; target symbol unknown.
- No existing dossier; no preflight. Created both.

## FILES (created)
- docs/progress/oc_U-EX1.bc3c6b0.md — this result file
- docs/functions/bc3c6b0.md — dossier with signature, phases, struct fields, callees, Reversed source (complete), verbatim instruction listing
- src/client/features/render/native/bgfx/sub_bc3c6b0.h — layout constants + static_asserts + exact x64 ABI signature + extern declaration of sub_e935700
- src/client/features/render/native/bgfx/sub_bc3c6b0.cpp — lifted body with `// LIFT 0xbc3c6b0 size 0xcb 1.26.62.01 BgfxFrameBuilder slot 0` first line, LIFT_FN registry entry, all 55 instructions cited by verbatim quote

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc3c6b0` printed:
LIFTCHECK OK 0xbc3c6b0

## UNRESOLVED CALL
- 0xe935700 (sub_e935700): `call 0xE935700` at 0xbc3c6f8 and 0xbc3c741. sub_e935700 is a thunk (`jmp sub_392960` @0xe935700). Neither sub_e935700 nor sub_392960 appears in docs/data/native_functions.tsv or docs/data/native_boundary.tsv. Declared as `extern "C" void sub_e935700(uint64_t, uint64_t, void*, void*)` matching register usage; no wrapper invented.
- 0xF9A8C78: `call qword ptr [0xF9A8C78]` at 0xbc3c774. Indirect-global through absolute data address; target not in native_boundary.tsv, native_unresolved_indirect.tsv, or native_boundary_candidates.tsv. Called through `RewriteRegistry::imageBase() + 0xF9A8C78` with zeroed args, then int3 (noreturn); no wrapper invented.

## TOOL REQUESTS
None.

CLOSES? YES
