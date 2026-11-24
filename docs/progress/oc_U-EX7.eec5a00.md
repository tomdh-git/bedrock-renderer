## NEXT
DONE

## FACTS (all [V] from the exe)

- Function 0xeec5a00, size 0x6 per docs/data/native_functions.tsv line 1643 [V], depth 0, root, D0: one instruction `0xeec5a00  jmp qword ptr [0xF9A72F0]` ; [data_f9a72f0], then int3 padding [V: rdis dis 0xeec5a00 8]. No call instruction, no prologue/epilogue, no registers read for its own logic, no memory writes. CALLEES list empty (data file line 4-5).
- Data slot 0xF9A72F0 (.rdata) -> MSVCP140.dll !?_Throw_Cpp_error@std@@YAXH@Z = std::_Throw_Cpp_error(int) [V: python tools/sigs/peimports.py prints `0xF9A72F0 -> MSVCP140.dll !?_Throw_Cpp_error@std@@YAXH@Z`].
- Call sites: `mov ecx,5/6; call 0xEEC5A00`, return value ignored [V: 0x7efca/0x7efde, 0x7f019/0x7f02e, 0xbc7a980/0xbc7a991].
- Signature: void sub_eec5a00(int errorCode), x64 Microsoft ABI, error code in RCX [V: import mangling (int arg, void return) + caller register use]. Original is a tail jump through the slot, so the lifted body calls the resolved target directly with the same argument (hard rule 69 pattern, same as helpers/sub_eec5850.cpp and sub_eec59e0.cpp).
- No struct fields touched; no layout offsets; x64 ABI static_asserts only.

## FILES (created)
- docs/functions/eec5a00.md (dossier with section 'Reversed source (complete)')
- src/client/features/render/native/helpers/sub_eec5a00.cpp (first line: // LIFT 0xeec5a00 size 0x6 1.26.62.01 sub_eec5a00; LIFT_FN(eec5a00, "sub_eec5a00", 0xEEC5A00, sub_eec5a00, nullptr))
- src/client/features/render/native/helpers/sub_eec5a00.h (layout constants + static_asserts, signature, std::_Throw_Cpp_error declaration)
- Not edited: Sigs.json, native_boundary.tsv, CMake, hooks, other units' files; no builds, no game.
- cppsyntax: identical result to the accepted sibling lifts (sub_eec5850.cpp/sub_eec59e0.cpp); no errors cite sub_eec5a00.cpp.

## LIFTCHECK
LIFTCHECK OK 0xeec5a00

## UNRESOLVED CALL
none (the function contains no `call` instruction; the indirect tail jump through data slot 0xF9A72F0 is resolved [V] to MSVCP140.dll std::_Throw_Cpp_error(int) and is called directly by name from the lifted body)

CLOSES? YES
