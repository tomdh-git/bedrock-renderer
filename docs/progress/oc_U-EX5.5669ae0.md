## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_5669ae0.h
- src/client/features/render/native/helpers/sub_5669ae0.cpp
- docs/functions/5669ae0.md (appended ## Reversed source (complete) section)

## LIFTCHECK
GATE OK 0x5669AE0
LIFTCHECK OK 0x5669ae0
cppsyntax OK (syntax)

## UNRESOLVED CALL
none

## Summary
sub_5669ae0 (0x5669ae0, size 0x129) lifted to C++. Void function; RCX = self. Walks two inline-buffer ranges: range #2 ([0xB8,0xC0), stride 0x290, cap 0xC8) first, then range #1 ([0x10,0x18), stride 0x290, cap 0x20). Each element released via sub_567e430 (lift set). After each loop, the range heap block is freed via sub_e935700 (lift set): arg = begin pointer when cap-begin <u 0x1000, else block-size header at begin-8 (validated (begin-8)-blockSize <u 0x20, else noreturn fail path call qword ptr [0xF9A8C78](0,0,0,0); int3 via RewriteRegistry::imageBase() + kRvaFailSlot). begin/end/cap fields of each range zeroed afterward. No null guards or SEH (none in original). Struct layouts with offsetof static_asserts in .h and .cpp; all field offsets proven from the listing.

CLOSES? YES
