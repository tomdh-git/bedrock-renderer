## NEXT
DONE — all files created (docs/functions/bc6e360.md, src/client/features/render/native/bgfx/sub_bc6e360.cpp, sub_bc6e360.h, this progress file); liftcheck printed `LIFTCHECK OK 0xbc6e360`; CLOSES? NO: direct call 0xbc6e3d5 `call 0xEEC6ED0` -> sub_eec6ed0 is neither lifted nor a boundary function (emitted as raw address call, no wrapper invented), documented under ## UNRESOLVED CALL.
## FILES
docs/functions/bc6e360.md (created)
src/client/features/render/native/bgfx/sub_bc6e360.cpp (created)
src/client/features/render/native/bgfx/sub_bc6e360.h (created)
docs/progress/oc_U-EX1.bc6e360.md (this file)
## LIFTCHECK
LIFTCHECK OK 0xbc6e360
## UNRESOLVED CALL
0xEEC6ED0 @ 0xbc6e3d5 — `0xbc6e3d5  call 0xEEC6ED0` (args r14 = alloc result, 0, 0x410; return unused). sub_eec6ed0 is in neither docs/data/native_functions.tsv nor docs/data/native_boundary.tsv, so per the hard rules the call is emitted as a raw address call; no wrapper invented, no stub.
CLOSES? NO direct call 0xbc6e3d5 `call 0xEEC6ED0` -> sub_eec6ed0 is neither lifted nor a boundary function
