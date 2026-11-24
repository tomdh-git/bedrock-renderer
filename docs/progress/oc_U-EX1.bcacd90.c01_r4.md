## NEXT
DONE

## DONE
- Disassembled the full chunk 2 range (1171 instructions) to /tmp/c01.lst and the whole function to /tmp/whole.lst.
- Confirmed all 53 call sites in the range are quoted verbatim and verified by verify_oc; coverage of every instruction is complete via cited ranges.
- Confirmed callee classification: 0x5679DB0/0x568AD40/0x568C420/0x5693A80/0x56B8630/0x56C9740/0x6760450/0xBC039A0/0xBC03CD0/0xBC04620/0xBC04BB0/0xBC054A0 = lift (in native_functions.tsv); 0x9D6D0/0x76A8A0/0x2679A0/0x78ED0/0x9BC830/0xE935700/0xE938CB0/0xE9E7970 = boundary; 0xEEC6DE0/0xE869FF0 = lift (auto-unresolved->lift in native_boundary.tsv); indirect `call qword ptr [0xF99FFA0]` = allocator thunk (boundary vendor slot); `call qword ptr [0xF9A8C78]` = fatal-log thunk. No UNRESOLVED CALL.

## FILES
- src/client/features/render/native/bgfx/sub_bcacd90_c01.cpp (body to be rewritten)
- src/client/features/render/native/bgfx/sub_bcacd90_c01.h (chunk state struct; keep)
- docs/functions/bcacd90.md (extend Reversed source section)
- docs/progress/oc_U-EX1.bcacd90.c01.md (this file)

## LIFTCHECK
LIFTCHECK OK 0xbcacd90 0xbcae56d..0xbcafd5f  (coverage 1171/1171, 53/53 calls quoted, verify_oc mismatch=0 no-such-instr=0)

## UNRESOLVED CALL
none

## TOOL REQUESTS
none

CLOSES? YES