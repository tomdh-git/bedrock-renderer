## NEXT
DONE: chunk range 0xe8262b7..0xe827ab7 lifted; liftcheck passed.

## STATE
- Chunk range disassembled & saved: C:/Users/Atomi/AppData/Local/Temp/opencode/range.txt (1252 lines, first `0xe8262b7  nop`, last `0xe827ab7  mov r8,[rsi]`). Source: `rdis.exe ... dis 0xe8262b7 6400` filtered to [0xe8262b7,0xe827ab7].
- 39 call sites quoted verbatim (two-space) in src/.../sub_e824ab7_chunk_c01.cpp #if 0 block (lines 5-44).
- Callee classification: lift set (native_functions.tsv) = 0xe835f00, 0xe83aed0, 0xe83abb0, 0xe83ace0, 0xe82dcc0, 0xe82d960, 0xe820500, 0xe81e1c0, 0xbc6a9d0, 0xe935700(lift in boundary.tsv), 0xe82de90, 0xbc5f110; boundary = 0xeea6040(vendor, data slot 0xF99FFA0), 0xeec6ed0(crt), 0x47e8f0(stl); forwarder = 0xebce430 (`movzx edx,dl; jmp 0xEEC6ED0`) -> forward-declare sub_ebce430; UNRESOLVED = 0xebd1560 (not a blocker for this chunk).
- Internal jmp targets (not calls): 0xe826131 (0xe8270c3), 0xe825aab (0xe8270e9, 0xe827355, 0xe827710, 0xe8273e4, 0xe8278bd, 0xe827a0c).

## FILES
src/client/features/render/native/d3d12/sub_e824ab7_chunk_c01.cpp
src/client/features/render/native/d3d12/sub_e824ab7_chunk_c01.h
docs/progress/oc_U-EX2.e824ab7.c01.md

## LIFTCHECK
LIFTCHECK OK 0xe824ab7 0xe8262b7..0xe827ab7

## UNRESOLVED CALL
0xebd1560 at 0xe82764b `0xe82764b  call 0xEBD1560` — pure leaf, absent from both tables (classified by other units, not a blocker for this chunk).

CLOSES? YES