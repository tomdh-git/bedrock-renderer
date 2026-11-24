## NEXT
DONE

## FILES
docs/functions/bc68e40.md (extended with Reversed source for chunk 2)
src/client/features/render/native/bgfx/sub_bc68e40_chunk2.cpp (created)
src/client/features/render/native/bgfx/sub_bc68e40_chunk2.h (created)

## LIFTCHECK
Chunk 0xbc6a600..0xbc6a9c3 (size 0x3c3): every instruction in range cited with // 0xA..0xB comments beside corresponding C++ statements. Every call in range quoted verbatim as plain lines in #if 0 block:
0xbc6a619  call 0xEBCE390
0xbc6a636  call 0xEBCE390
0xbc6a656  call 0xEBCE390
0xbc6a6ad  call 0xEBCE390
0xbc6a6cd  call 0xEBCE390
0xbc6a6ea  call 0xEBCE390
0xbc6a707  call 0xEBCE390
0xbc6a724  call 0xEBCE390
0xbc6a744  call 0xEBCE390
0xbc6a761  call 0xEBCE390
0xbc6a814  call 0xEBCE390
0xbc6a925  call 0xEBCE390
0xbc6a942  call 0xEBCE390
0xbc6a95b  call 0xBC68840
0xbc6a97d  call qword ptr [0xF99FFA0]
0xbc6a980  call qword ptr [0xF99FFA0]
0xbc6a9b7  call 0xEBCE390
0xbc6a881  call 0xBC6ABD0
0xbc6a84b  call qword ptr [0xF99FFA0]
0xbc6a863  call qword ptr [0xF99FFA0]
Range first instruction: 0xbc6a600  and edx,0xFFFFFFFE
Range last instruction: 0xbc6a9c3  int3
All calls resolve to: lifted functions (sub_bc68840, sub_bc6abd0) or boundary (sub_ebce390=memcpy, sub_eea6040 via [0xF99FFA0]). No UNVERIFIED/TODO/[?] tags in source.

## UNRESOLVED CALL
none

CLOSES? YES