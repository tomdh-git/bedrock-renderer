## NEXT
DONE: Unit U-EX2.e8764f0 lifted and verified. Function 0xe8764f0 size 0x105 depth 6, region d3d12, name "BgfxFrameBuilder slot 16".

## FILES
- src/client/features/render/native/d3d12/BgfxFrameBuilder_slot16.cpp (rewrote: correct lift, first line `// LIFT 0xe8764f0 size 0x105 1.26.62.01 BgfxFrameBuilder slot 16`, LIFT_FN registry entry, verbatim call quotes in #if 0 block)
- src/client/features/render/native/d3d12/BgfxFrameBuilder_slot16.h (rewrote: layout constants kGblCookie/kIstreamReadSlot/kExceptObj/kExceptTypeInfo, kOutBegin/kOutEnd/kOutCapacity, static_asserts, forward declaration of lift callee sub_eec6d80)
- docs/functions/e8764f0.md (rewrote: corrected purpose — reads 4-byte length prefix then reads `length` bytes, not a single byte; full Reversed source (complete) matching the .cpp; callees table; no [?]/[I]/TODO/UNVERIFIED tags remain)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xe8764f0` printed:
LIFTCHECK OK 0xe8764f0

## UNRESOLVED CALL
none. All 6 call sites are accounted for:
- 0xe876517, 0xe87658d: `call qword ptr [0xF9A7480]` indirect istream::read via data slot (hard rule 69, not a blocker)
- 0xe87656c: `call 0x47E8F0` stl boundary via native::Boundary (docs/data/native_boundary.tsv row 0x47e8f0 = stl)
- 0xe876579: `call 0xEEC6ED0` crt boundary IAT thunk (docs/data/native_boundary.tsv row 0xeec6ed0 = crt)
- 0xe8765e2: `call 0xEEC6D80` lift callee, forward-declared as `sub_eec6d80` in the header (hard rule 66, not a blocker)
- 0xe8765ef: `call 0xE951550` crt boundary __security_check_cookie (docs/data/native_boundary.tsv row 0xe951550 = crt)

## CppSyntax
`python tools/cppsyntax.py` on the .cpp: no errors in the lifted code; the only diagnostics are pre-existing missing-include errors in project headers Detour.h / Profiler.h (identical failures occur on already-accepted units such as sub_e81e1c0.cpp).

## CLOSES? YES
