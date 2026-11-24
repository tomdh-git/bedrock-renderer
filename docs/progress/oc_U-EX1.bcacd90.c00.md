## NEXT
DONE

## FILES
- src/client/features/render/native/bgfx/sub_bcacd90_c00.cpp
- src/client/features/render/native/bgfx/sub_bcacd90_c00.h
- docs/functions/bcacd90.md

## LIFTCHECK
LIFTCHECK OK 0xbcacd90 0xbcacd90..0xbcae56d

## UNRESOLVED CALL
0xE9E7970 (0xbcacda1): crt __chkstk boundary (already boundary, not a blocker).
0xEEC7000 (0xbcad008): neither in native_functions.tsv nor native_boundary.tsv as of this unit; neighbour 0xEEC6DE0 is classified lift. Forward-declared as extern "C" float sub_eec7000(float) in the chunk; needs orchestrator classification.
0xEEC7430 (0xbcad01a/0xbcad124/0xbcad136): same as above; forward-declared as extern "C" double sub_eec7430(double).
Indirect call rdi via slot 0xF9A8F28 (0xbcad357, 0xbcad368): per hard rule, indirect through data slot is not a blocker (pointer read at call time, called as function pointer).

## TOOL REQUESTS
None.

CLOSES? YES