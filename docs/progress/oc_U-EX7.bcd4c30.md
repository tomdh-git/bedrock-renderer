## NEXT
DONE

## UNIT
U-EX7.bcd4c30 | sub_bcd4c30 [0xbcd4c30, 0xbcd4d1d), size 0xed, depth 0, milestone 7, region root D0.
Caller count 2 (sub_c292a20, sub_c2937a0); direct callee 1 (sub_e935700).

## SUMMARY
Lifted sub_bcd4c30 into C++ that does exactly what the exe does: same reads, writes, calls in the same order, same return. x64 Microsoft ABI: count in RCX (>= 2 required), state pointer in R8 (RDX passed but unread); returns 0 (RAX dead at ret in the original).
If count == 3, buffer 1 (ptr +0x20, size +0x30, cap +0x38) is released first; buffer 0 (ptr +0x00, size +0x10, cap +0x18) is released whenever count >= 2. Per buffer: cap < 0x10 is the inline/empty state (size = 0, cap = 0xF, pointer low byte = 0, no call); otherwise the heap pointer is released through native::sub_e935700(void*) — directly when cap + 1 < 0x1000 (RCX = pointer), or after validating bias = (ptr - 8) - *(uint64_t*)(ptr - 8) (bias >= 0x20 takes the failfast path: data slot [0xF9A8C78] called with four zeroed arguments, then int3). On the validated path RCX = *(uint64_t*)(ptr - 8). Reset writes (size = 0, cap = 0xF, pointer low byte = 0) happen in the same order as the listing after every release path. No stubs, no skipped branches, no null guards/SEH beyond the original.

## FILES
- src/client/features/render/native/helpers/sub_bcd4c30.h (rewritten): sub_bcd4c30_state layout with field names/types matching every [r8 + off] access, offsetof static_asserts for +0x00/+0x10/+0x18/+0x20/+0x30/+0x38, forward declaration of native::sub_e935700(void*), exact signature uintptr_t sub_bcd4c30(uint64_t count, uint64_t, sub_bcd4c30_state* state).
- src/client/features/render/native/helpers/sub_bcd4c30.cpp (rewritten): complete lifted body, block-by-block with // 0xA..0xB range comments covering every instruction of [0xbcd4c30, 0xbcd4d1d), verbatim call quotes preserved, LIFT_FN registry entry retained.
- docs/functions/bcd4c30.md (edited): added ## Reversed source (complete) and resolved ## DECISIONS; verbatim call quotes retained.
- docs/progress/oc_U-EX7.bcd4c30.md (new): this result file.

## LIFTCHECK
`python tools/ctx/gate.py 0xbcd4c30` printed:

GATE OK 0xBCD4C30

`python tools/sigs/liftcheck.py 0xbcd4c30` printed:

LIFTCHECK OK 0xbcd4c30

## UNRESOLVED CALL
none. All calls resolved: `call 0xE935700` at 0xbcd4c87 and 0xbcd4ce1 (lift-set callee sub_e935700, called directly through the native symbol native::sub_e935700(void*)), `call qword ptr [0xF9A8C78]` at 0xbcd4d16 (data-slot failfast, target read from the slot at call time, no static direct target).

## TOOL REQUESTS
None.

CLOSES? YES
