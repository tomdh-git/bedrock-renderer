## NEXT DONE — unit finished. Lifted source written (sub_336380.cpp/.h), dossier complete, `python tools/sigs/liftcheck.py 0x336380` printed `LIFTCHECK OK 0x336380` (exit 0). Closed YES: all callees resolved — 0xAA3C0 (sub_aa3c0) is classified `lift` (native_functions.tsv:15, native_boundary.tsv:529), forward-declared and called per hard rule #66; 0xE951550 is boundary crt (native_boundary.tsv:467); indirect slot 0xF9A8B20 read as a function pointer. No further steps needed this unit.

## FILES
docs/progress/oc_U-EX7.336380.md (this result file; rewritten this session)
docs/functions/336380.md (dossier: signature, register/argument map, Reversed source (complete) with verbatim call quotes, struct fields, callees; analysis kept, no change needed this session)
src/client/features/render/native/helpers/sub_336380.cpp (// LIFT 0x336380 size 0x97 1.26.62.01 sub_336380; created by the earlier session, edited this session: reworded the two "unresolved callee" notes to the "UNRESOLVED CALL = none" convention (liftcheck STUB_RE clean), and rax = imageBase() + kData128c1588Rva so the [0x128C1588] read uses VA = imageBase + RVA like every other global read)
src/client/features/render/native/helpers/sub_336380.h (layout constants + static_asserts, signature, Boundary<> wrapper for 0xE951550, LIFT_FN registry entry; created by the earlier session, unchanged this session)

## UNRESOLVED CALL
none — all three callees of 0x336380 are resolved: 0xAA3C0 (sub_aa3c0) is classified `lift` (native_functions.tsv:15, native_boundary.tsv:529) and called via forward declaration per hard rule #66; qword [0xF9A8B20] is an indirect data-slot call read at call time; 0xE951550 is boundary crt (native_boundary.tsv:467) called through `native::Boundary<void,std::uintptr_t>`.

## LIFTCHECK
LIFTCHECK OK 0x336380

CLOSES? YES — liftcheck printed `LIFTCHECK OK 0x336380`; all callees resolved (0xAA3C0 = lift callee sub_aa3c0 called via forward declaration; [0xF9A8B20] = indirect data-slot call; 0xE951550 = boundary crt).
