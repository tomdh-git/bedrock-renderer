## NEXT
DONE: chunk 0xe824a4f..0xe826240 liftcheck OK; result file written; dossier updated with Reversed source.

## LIFTCHECK
LIFTCHECK OK 0xe824a4f 0xe824a4f..0xe826240
verify_oc: src/client/features/render/native/d3d12/sub_e824a4f.cpp: claimed=38 match=38 mismatch=0 no-such-instr=0

## UNRESOLVED CALL
0xebd1560 at 0xe82533b (call 0xEBD1560 -> sub_ebd1560, size 0xa, 22 xref callers; not in native_functions.tsv or native_boundary.tsv as of X0b5; callers sub_e7ee2e0/e7f27b0/e7f4470/e7f5020/e7f5380/e85d980/e85e5c0 are outside the lift set). Nearest classified rows are 0xebd15b0 (lift) and 0xebd18f0 (lift). This is a 0xa-byte leaf: lea eax,[rcx-0x55]; cmp eax,7; setbe al; ret.

## FILES
- src/client/features/render/native/d3d12/sub_e824a4f.cpp (added 12 verbatim call quotes)
- docs/progress/oc_U-EX2.e824a4f.c00.md (this file)
- docs/functions/e824a4f.md (added Reversed source section)

CLOSES? YES