## NEXT
DONE - sub_e903360 lifted; LIFTCHECK OK 0xe903360; ready to close

## FILES
docs/progress/oc_U-EX3.e903360.md (this result file; created and updated)
docs/functions/e903360.md (created: dossier with signature, register/argument map, instruction-complete phases, callees, 'Reversed source (complete)')
src/client/features/render/native/dragon/sub_e903360.h (created: layout constants kDataCookie=0x1230A0C0, kTableRva=0xF440E10, kMaxResults=11, kMaxIndex=10; static_asserts; signature bool sub_e903360(uint8_t a1, uint32_t* a2))
src/client/features/render/native/dragon/sub_e903360.cpp (created: first line `// LIFT 0xe903360 size 0xa9 1.26.62.01 BgfxFrameBuilder slot 11`; lifted body with cited ranges 0xe903360..0xe903409 covering every instruction; verbatim call quotes for 0xe90337d call 0xBC6AF50 and 0xe903403 call 0xE951550; LIFT_FN registry entry)
No other files edited (Sigs.json, shared headers, CMake, hooks, and other units' files untouched; no build, no game run).

## LIFTCHECK
LIFTCHECK OK 0xe903360

## UNRESOLVED CALL
none
(0xbc6af50 is in the lift set, called as native::bgfx::sub_bc6af50; 0xe951550 is boundary class crt in docs/data/native_boundary.tsv line 467, called via native::Boundary<void,uintptr_t>("sub_e951550") on the noreturn stack-cookie-failure path)

CLOSES? YES
