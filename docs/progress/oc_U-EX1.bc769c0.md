## NEXT
DONE — unit complete: sub_bc769c0 lifted, liftcheck passed, result file finalized. Nothing left to resume.
## FILES
docs/progress/oc_U-EX1.bc769c0.md (this result file)
src/client/features/render/native/bgfx/sub_bc769c0.cpp (new: lifted body, first line `// LIFT 0xbc769c0 size 0x22c 1.26.62.01 bgfx shutdown`, LIFT_FN registry entry)
src/client/features/render/native/bgfx/sub_bc769c0.h (new: Bc769c0State/Bc769c0Node layout constants + static_asserts, signature)
docs/functions/bc769c0.md (new: dossier with Mechanical facts and Reversed source (complete), verbatim instruction listing)
## LIFTCHECK
LIFTCHECK OK 0xbc769c0
## UNRESOLVED CALL
none — all 4 calls are `call r10` through the CFG thunk [0xF99FFA0] (data_f99ffa0 = sub_eea6040, class vendor in docs/data/native_boundary.tsv); the real target of each call is rax = (*g)->+0x8 = g->vtable[1] with g = *data_12adf800, rcx = g forwarded as `this` (0xbc76a3c, 0xbc76a95 with r8=0x48, 0xbc76b6d, 0xbc76be0), lifted as direct indirect calls through g->vtable[1] with identical reads and argument order. No callee is outside the lift set/boundary.
CLOSES? YES
