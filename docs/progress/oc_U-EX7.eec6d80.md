## NEXT DONE

## FILES
- docs/progress/oc_U-EX7.eec6d80.md (this file)
- docs/functions/eec6d80.md (dossier with 'Reversed source (complete)' section)
- src/client/features/render/native/helpers/sub_eec6d80.h (layout constants + static_asserts, signature, forward declaration of _CxxThrowException)
- src/client/features/render/native/helpers/sub_eec6d80.cpp (LIFT marker, reversed source, LIFT_FN registry entry)

## LIFTCHECK
LIFTCHECK OK 0xeec6d80

## UNRESOLVED CALL
none — the function body is a single indirect `jmp qword ptr [0xF9A8A18]` through VCRUNTIME140!_CxxThrowException's import slot [V: tools/sigs/peimports.py "0F9A8A18 VCRUNTIME140.dll!_CxxThrowException"]; _CxxThrowException is forward-declared in sub_eec6d80.h and called directly (same precedent as helpers/sub_eec5ae0 tail-calling std::_Xinvalid_argument through slot 0xF9A7318). No `call` instructions exist in [0xeec6d80, 0xeec6d86).

## Basis (all [V], machine-checked)
- 0xeec6d80  jmp qword ptr [0xF9A8A18]   ; [data_f9a8a18] (rdis dis 0xeec6d80; bytes FF 25 92 1C AE 00; RIP target = 0xeec6d86 + 0xAE1C92 = 0xF9A8A18). Size 0x6; 0xeec6d86..0xeec6d8b are int3 padding outside the function.
- Slot 0xF9A8A18 (.rdata) qword = 0x0000000F9B0090 → RVA of import-by-name entry "_CxxThrowException" read from the image.
- Caller convention confirmed at sub_e874d80: 0xe874da2..0xe874e02 lea rcx,<exc>; lea rdx,<throwinfo>; call 0xEEC6D80; "unreachable: sub_eec6d80 throws via _CxxThrowException" [V].

CLOSES? YES
