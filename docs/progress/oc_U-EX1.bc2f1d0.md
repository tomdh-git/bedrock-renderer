## NEXT
DONE - unit U-EX1.bc2f1d0 complete; liftcheck printed LIFTCHECK OK 0xbc2f1d0; CLOSES? YES.

## Steps
- step 1: wrote docs/progress/oc_U-EX1.bc2f1d0.md with '## NEXT' + 'step 2'. [done]
- step 2: verified disassembly 0xbc2f1d0..0xbc2f3bb with rdis dis (69 instructions, ret at 0xbc2f3bb, size 0x1ec matches docs/data/native_functions.tsv); confirmed callees 0xe869ff0 and 0x5669770 are class lift in docs/data/native_boundary.tsv (lines 501-502, 'auto-unresolved->lift'), so not blockers. [done]
- step 3: rewrote docs/functions/bc2f1d0.md 'Reversed source (complete)' block (callees now lift, called via header declarations); updated Callees table, OPEN questions, STATUS. [done]
- step 4: liftcheck printed LIFTCHECK OK 0xbc2f1d0 (exit 0). [done]

## FILES
- docs/progress/oc_U-EX1.bc2f1d0.md (created; this result file)
- src/client/features/render/native/bgfx/sub_bc2f1d0.cpp (rewritten; first line `// LIFT 0xbc2f1d0 size 0x1ec 1.26.62.01 sub_bc2f1d0`; full lifted body; LIFT_FN registry entry)
- src/client/features/render/native/bgfx/sub_bc2f1d0.h (edited; layout constants + static_asserts, signature, forward declarations of native::sub_e869ff0 / native::sub_5669770)
- docs/functions/bc2f1d0.md (edited; 'Reversed source (complete)' section replaced, Callees table updated to lift callees, OPEN questions / STATUS updated)

## LIFTCHECK
LIFTCHECK OK 0xbc2f1d0

## UNRESOLVED CALL
none

CLOSES? YES

