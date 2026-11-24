## NEXT
DONE

## FINDINGS
- 0xeec59e0 size 0x6: single instruction `0xeec59e0  jmp qword ptr [0xF9A7310]     ; [data_f9a7310]` (rdis dis 0xeec59e0, verbatim) [V]
- Slot 0xF9A7310 (.rdata, file off 0xf9a5d10) holds import-by-name RVA 0xF9AA638; entry at 0xF9AA638: hint 652, name '?_Xbad_function_call@std@@YAXXZ' = std::_Xbad_function_call(void), MSVC CRT [V: PE import table read]
- No register reads, no memory writes, no call instruction in [0xeec59e0, 0xeec59e6): 0 callees, 0 callees in set [V: disassembly + docs/data/native_functions.tsv row]
- docs/data/native_boundary.tsv line 516: `0xeec59e0 lift auto-unresolved->lift` [V]
- Lift: tail call to std::_Xbad_function_call through its real symbol (forward-declared with its real mangled symbol in namespace std; resolved statically from the slot, not a boundary wrapper, not an UNRESOLVED CALL)

## FILES
- src/client/features/render/native/helpers/sub_eec59e0.h (new: layout constants + static_asserts + signature + forward declaration of std::_Xbad_function_call)
- src/client/features/render/native/helpers/sub_eec59e0.cpp (new: // LIFT 0xeec59e0 size 0x6 1.26.62.01 sub_eec59e0, lifted body, verbatim quote block, LIFT_FN registry entry)
- docs/functions/eec59e0.md (new dossier with Reversed source (complete))

## LIFTCHECK
LIFTCHECK OK 0xeec59e0

## UNRESOLVED CALL
none

CLOSES? YES
