## NEXT
DONE

## UNIT
U-EX1.bc8c720: sub_0xbc8c720, size 0x167 bytes (0xbc8c720..0xbc8c887), depth 2, D0, bgfx region, 0 callees in set (from docs/progress/_d_U-EX1.bc8c720.txt)

## DISASSEMBLY (verbatim from rdis, docs/progress/pre/bc8c720_dis.txt)
All instructions [0xbc8c720, 0xbc8c887) captured. Calls:
0xbc8c74e  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
0xbc8c76d  call 0xE935700               ; -> sub_e935700
0xbc8c790  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
0xbc8c7a6  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
0xbc8c7e7  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
0xbc8c7fd  call qword ptr [0xF99FFA0]   ; [data_f99ffa0] = sub_eea6040
0xbc8c849  call 0xE935700               ; -> sub_e935700
0xbc8c880  call qword ptr [0xF9A8C78]   ; [data_f9a8c78]

## CALLEES (verified)
- [0xF99FFA0] = sub_eea6040 = vendor thunk `jmp rax` (boundary.tsv line 506, class vendor). Indirect virtual call through data slot; modelled as vtable[0/1/4] calls via function pointers.
- 0xE935700 = sub_e935700 = lift class (boundary.tsv line 505). Forward-declared in sub_bc8c720.h, called as plain C++. Signature uintptr_t sub_e935700(uint64_t x).
- [0xF9A8C78] = _invoke_watson IAT slot (VA 0x14F9A8C78). Boundary indirect-call-through-slot per hard rule; modelled as function-pointer read at VA 0x14F9A8C78 at call time.

## FILES CREATED / CHANGED
- src/client/features/render/native/bgfx/sub_bc8c720.h (layout structs + static_asserts + decls)
- src/client/features/render/native/bgfx/sub_bc8c720.cpp (first line `// LIFT 0xbc8c720 size 0x167 1.26.62.01 sub_bc8c720`; LIFT_FN registration; fixed `reinterpret`→`reinterpret_cast`; byte write for field_0x00; static_asserts added)
- docs/functions/bc8c720.md (dossier with Reversed source section, verbatim calls, no [?]/[I]/TODO/UNVERIFIED)

## LIFTCHECK
LIFTCHECK OK 0xbc8c720

## UNRESOLVED CALL
none

## TOOL REQUESTS
None

CLOSES? YES