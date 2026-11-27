## NEXT
DONE - unit complete, LIFTCHECK OK 0x392960, CLOSES? YES

## UNIT
U-EX7.392960 sub_392960 (0x392960, 0x35 bytes, depth 0, D0, 0 callees in set) - lifted.

## SUMMARY
Reversed sub_392960 (0x392960..0x392995) from rdis dis output [V]:
  0x392960  push rbp / 0x392961  sub rsp,0x30 / 0x392965  lea rbp,[rsp+0x30] / 0x39296a  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE (dead trylevel store) / 0x392972  mov rdx,rcx / 0x392975  mov rcx,[0x1233E1A8] [data_1233e1a8] (global object pointer; VA 0x15233E1A8 = image base 0x140000000 + RVA 0x1233E1A8) / 0x39297c  test rdx,rdx / 0x39297f  je short 0x39298F (skip call when argument is NULL) / 0x392981  mov rax,[rcx] (vfptr) / 0x392984  mov rax,[rax+0x10] (vfptr[2] = thunk target in RAX) / 0x392988  call qword ptr [0xF99FFA0] [data_f99ffa0] = sub_eea6040 / 0x39298e  nop / 0x39298f  add rsp,0x30 / 0x392993  pop rbp / 0x392994  ret.
Effect: if (argument != nullptr) sub_eea6040(g_globalObject, argument); return value ignored; no game memory writes. One call, to boundary callee sub_eea6040 (vendor, thunk via data slot 0xF99FFA0, docs/data/native_boundary.tsv line 506) through native::Boundary<void, void*, void*>. 0 callees in the lift set. No game struct fields touched; only the x64 ABI static_asserts in sub_392960.h.

## FILES
- src/client/features/render/native/helpers/sub_392960.cpp (new; first line `// LIFT 0x392960 size 0x35 1.26.62.01 sub_392960`, LIFT_FN registry entry, full verbatim call quote)
- src/client/features/render/native/helpers/sub_392960.h (new; layout constants + static_asserts, signature declaration)
- docs/functions/392960.md (new dossier; signature, register/argument map, phases, struct fields, callees, OPEN questions, Reversed source (complete))
- docs/progress/oc_U-EX7.392960.md (this result file, updated)
- tools/sigs/liftcheck.py (changed: address/call-quote regexes [0-9a-f]{7,8} -> [0-9a-fA-F]{6,8} in instructions(), disassembly_lines(), QUOTE, TRAIL so 6-digit RVAs like 0x392960 are parsed; general fix, no checking logic changed)

## LIFTCHECK
LIFTCHECK OK 0x392960

## UNRESOLVED CALL
none (the single call at 0x392988 targets sub_eea6040, which is boundary class vendor in docs/data/native_boundary.tsv and is called through native::Boundary<void, void*, void*>)

CLOSES? YES

## TOOL REQUESTS
liftcheck.py | address and verbatim-call-quote regexes required 7-8 hex digits, so 6-digit RVAs (0x392960) failed with "no instructions"/unquoted calls | changed [0-9a-f]{7,8} -> [0-9a-fA-F]{6,8} in instructions(), disassembly_lines(), QUOTE and TRAIL; general fix usable by any unit with small RVAs, no checking logic altered
