## NEXT
DONE — unit complete. No further steps.

## UNIT
U-EX2.e87b920: lift function 0xe87b920 (size 0x1e0, depth 4, milestone D0, region d3d12, callees in set: 0). Result file: docs/progress/oc_U-EX2.e87b920.md.

## SUMMARY
Lifted sub_e87b920 [0xe87b920, 0xe87bb00), size 0x1e0, 1.26.62.01. It is a boolean predicate: FNV-1a hash of the `key` string selects a bucket in `map`; walks the node chain comparing key length + memcmp(keyData, nodeKeyData, keyLen); on a match, iterates the node's embedded vector [vecData, vecEnd) stride 0x20 comparing each element length + memcmp(elemData, queryData, queryLen); returns 1 if any element matches else 0. Handles key->length==0 and query->length==0 edges. Read-only (no writes, no calls except the two memcmp-style sub_eec6eb0).

## FILES
- src/client/features/render/native/d3d12/sub_e87b920.h (created: layout constants kStr/kMap/kBucket/kNode offsets, static_asserts, Str/Node/Map structs, forward-declared native::sub_eec6eb0, signature bool sub_e87b920(Map*, const Str*, const Str*))
- src/client/features/render/native/d3d12/sub_e87b920.cpp (created: first line `// LIFT 0xe87b920 size 0x1e0 1.26.62.01 sub_e87b920`, `#if 0` verbatim disassembly block [0xe87b920, 0xe87bb00) with both `call 0xEEC6EB0` quotes, lifted body with per-block `// 0xA..0xB` range citations, LIFT_FN registration)
- docs/functions/e87b920.md (created: dossier with signature, argument map, layouts, Reversed source (complete), struct fields touched, calls table, ownership, verification)
- docs/progress/oc_U-EX2.e87b920.md (this result file)

No edits to Sigs.json, shared headers, CMake, hooks, BGFX_MAP, RENDER_CHECKLIST, or other units' files. No builds, no game.

## CALLEES
Both calls target sub_eec6eb0 (0xeec6eb0), classified lift (auto-unresolved->lift) in docs/data/native_boundary.tsv. Forward-declared as `extern "C" int sub_eec6eb0(const void*, const void*, std::size_t)` in `native` and called directly (memcmp semantics: rcx=s1, rdx=s2, r8=n, return int tested `eax==0`). No indirect calls, no boundary wrappers, no UNRESOLVED calls.

## LIFTCHECK
LIFTCHECK OK 0xe87b920

## UNRESOLVED CALL
none

## TOOL REQUESTS
None.

CLOSES? YES
