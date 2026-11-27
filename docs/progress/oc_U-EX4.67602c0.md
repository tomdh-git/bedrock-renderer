## NEXT
DONE

## FILES
- src/client/features/render/native/helpers/sub_67602c0.h
- src/client/features/render/native/helpers/sub_67602c0.cpp
- docs/functions/67602c0.md

## LIFTCHECK
GATE OK 0x67602C0 (cppsyntax OK, liftcheck OK)

## UNRESOLVED CALL
none

## Summary
Lifted sub_67602c0 (0x67602c0, size 0xea) into C++.
- Signature: `void* sub_67602c0(sub_67602c0_state* self)` (RCX = this, return in RAX = sub_e935700's result).
- State struct `sub_67602c0_state` with fields handle(+0x08), count(+0x10), begin(+0x18), end(+0x20);
  block struct `sub_67602c0_block` with begin(+0x00), end(+0x10), flag(+0x40), stride 0x48;
  offsetof/static_assert for every field read/written.
- Walks the block array; per block with flag==1 and begin!=0: size = end-begin; arg = begin if
  size<0x1000 else validated block size header; calls native::sub_e935700(arg); clears block.
- Final: total = count*72; arg = handle if total<0x1000 else validated handle-8 block size header;
  tail-calls native::sub_e935700(arg).
- Fail path (heap corruption): call qword ptr [0xF9A8C78](0,0,0,0) then int3 (noreturn).
- Null-handle path: ret (rax undefined in original -> returns nullptr).
- Calls: sub_e935700 via native symbol (lift set); data slot 0xF9A8C78 fail handler per rule 69.
- No stubs, no return-0 placeholders, no null guards/SEH beyond the original.

CLOSES? YES
