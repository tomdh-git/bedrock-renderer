## NEXT
DONE: unit complete and closed.

## DONE
Lifted sub_0xbc2be20 (0xbc2be20, size 0x1ec, depth 1, D0, bgfx). All instructions of [0xbc2be20, 0xbc2c00c) covered by cited ranges; both calls quoted verbatim; verify_oc mismatch=0/no-such-instr=0; liftcheck printed LIFTCHECK OK.

## FILES
- docs/functions/bc2be20.md — dossier (signature, register/argument map, Reversed source (complete) with verbatim instruction quotes and cited ranges covering every instruction, struct fields touched table, callees, jump-table resolution, no open questions)
- src/client/features/render/native/bgfx/sub_bc2be20.h — packed struct sub_bc2be20_state, layout constants kOff0x00..kOff0x294, offsetof + sizeof static_asserts, signature, forward declarations native::sub_5669770 / native::sub_e869ff0
- src/client/features/render/native/bgfx/sub_bc2be20.cpp — first line `// LIFT 0xbc2be20 size 0x1ec 1.26.62.01 sub_bc2be20`, complete lifted body, verbatim call quotes, repeated static_asserts, LIFT_FN registry entry (footprint nullptr)
- docs/progress/oc_U-EX1.bc2be20.md — this result file

## LIFTCHECK
LIFTCHECK OK 0xbc2be20

## UNRESOLVED CALL
none

Callees: `0xbc2bf2b  call 0xE869FF0` (sub_e869ff0) and `0xbc2bf5c  call 0x5669770` (sub_5669770); both class `lift` in docs/data/native_boundary.tsv and native_functions.tsv → forward-declared in sub_bc2be20.h (namespace native) and called by native symbol; not boundary, not UNRESOLVED.

Jump table at 0xF440D90 resolved statically [V] from two consistent rdis passes of the table region: entries tag0=0xbc2bee8, tag1=0xbc2beb8, tag2=0xbc2bec0, tag3=0xbc2bec8; tag>3 -> 0xbc2beec. All four targets are in-function case blocks.

CLOSES? YES
