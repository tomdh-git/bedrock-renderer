## NEXT
DONE: lifted sub_e809fb0 (0xe809fb0, 0xa1 bytes, depth 1, D0, d3d12). Files: docs/functions/e809fb0.md, src/client/features/render/native/d3d12/sub_e809fb0.cpp, src/client/features/render/native/d3d12/sub_e809fb0.h. liftcheck printed LIFTCHECK OK 0xe809fb0.

## FILES
docs/progress/oc_U-EX2.e809fb0.md  (this result file: created)
docs/functions/e809fb0.md  (created: dossier with analysis + 'Reversed source (complete)')
src/client/features/render/native/d3d12/sub_e809fb0.cpp  (created: lifted source, first line // LIFT 0xe809fb0 size 0xa1 1.26.62.01 sub_e809fb0, LIFT_FN registry entry, verbatim call-quote log)
src/client/features/render/native/d3d12/sub_e809fb0.h  (created: layout constants, static_asserts, extern "C" signature)

## LIFTCHECK
LIFTCHECK OK 0xe809fb0

## UNRESOLVED CALL
none
- 0xe809fff  call 0xE839020  -> sub_e839020, in lift set (lifted header src/client/features/render/native/d3d12/sub_e839020.h), called via native symbol
- 0xe80a01b / 0xe80a03f  call qword ptr [0xF99FFA0]  -> sub_eea6040 via data slot 0xF99FFA0; sub_eea6040 is classified vendor/boundary in docs/data/native_boundary.tsv (0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)); body is `jmp rax`, so the real target is *(void**)(context.base + 0x20) called with rcx = context pointer, lifted as a direct call of the loaded target

CLOSES? YES
