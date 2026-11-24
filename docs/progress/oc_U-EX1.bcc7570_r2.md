## NEXT
DONE: function too complex for single session; 330 instructions uncovered

## FILES
- src/client/features/render/native/bgfx/sub_bcc7570.h
- src/client/features/render/native/bgfx/sub_bcc7570.cpp
- docs/functions/bcc7570.md

## LIFTCHECK
  - no layout assertion (static_assert) in source or dossier
  - instruction coverage incomplete: 330 of 370 instructions are in no cited range
  - verify_oc found no quoted instruction lines
LIFTCHECK FAIL 0xbcc7570

## UNRESOLVED CALL
0xbcc7ab7  call qword ptr [0xF9A8C78] -> indirect via data slot, target unknown at static analysis time

CLOSES? NO blocking fact: function too complex (370 instructions, 330 uncovered) for single-session lift; needs multi-session work