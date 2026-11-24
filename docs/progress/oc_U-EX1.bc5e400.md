## NEXT
DONE: sub_bc5e400 lifted to L1 (statically complete). liftcheck printed `LIFTCHECK OK 0xbc5e400`.
## FILES
docs/progress/oc_U-EX1.bc5e400.md (this result file)
src/client/features/render/native/bgfx/sub_bc5e400.h (rewritten: layout constants + static_asserts, signature, forward declaration of native::sub_e935700, LIFT_FN footprint declaration)
src/client/features/render/native/bgfx/sub_bc5e400.cpp (new: full lift, first line `// LIFT 0xbc5e400 size 0x2f1 1.26.62.01 sub_bc5e400`, every instruction of [0xbc5e400, 0xbc5e6f1) inside a cited `// 0xA..0xB` range, every call quoted verbatim, registry entry + static_asserts)
docs/functions/bc5e400.md (extended: phase walk corrected to the rdis ground truth, callees resolved, 'Reversed source (complete)' replaced with the complete cited source)
## LIFTCHECK
LIFTCHECK OK 0xbc5e400
## UNRESOLVED CALL
none
CLOSES? YES
