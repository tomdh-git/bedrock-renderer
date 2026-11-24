## NEXT
LIFTCHECK --range OK for 0xe829147..0xe82a912. Remaining: write the real translated C++ body for the FULL chunk range (density rule: >= ~1 source line per 20 bytes; range is 0x17cb = 6091 bytes, so >= ~300 source lines). Currently only 0xe829147..0xe8294b0 (~0x370 bytes) is translated; the tail from 0xe8294b0..0xe82a912 is a stub. Continue appending translated blocks from chunk_listing.txt (repo-relative file: chunk_listing.txt, 1312 lines, 0xe829147..0xe82a912), citing `// 0xA..0xB` ranges, keeping call quotes in `#if 0..#endif`, then re-run `python tools/sigs/liftcheck.py --range 0xe824991 0xe829147 0xe82a912`.

## FILES
- src/client/features/render/native/d3d12/sub_e824991.cpp (chunk c03 body + 68 call quotes)
- src/client/features/render/native/d3d12/sub_e824991.h
- docs/functions/e824991.md
- docs/progress/oc_U-EX2.e824991.c03.md
- chunk_listing.txt (repo-relative dump of the chunk range, 1312 lines)

## LIFTCHECK
`python tools/sigs/liftcheck.py --range 0xe824991 0xe829147 0xe82a912` -> LIFTCHECK OK 0xe824991 0xe829147..0xe82a912

## UNRESOLVED CALL
none (all 68 call targets in range are quoted verbatim; targets are 0x47E8F0, 0xEEC6ED0, 0xEEC6EC0, 0xE8360F0, qword ptr [0xF99FFA0], r10, r11, 0xBC6A9D0, 0xE81E1C0)

CLOSES? NO body density not yet met (only ~0x370 of 0x17cb bytes translated)