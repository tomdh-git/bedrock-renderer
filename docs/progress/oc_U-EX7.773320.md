## NEXT
DONE

## UNIT
U-EX7.773320: lift sub_773320 (0x773320, 0xc9 bytes, depth 0, root, D0, 0 callees in set) — COMPLETE

## GOAL (done)
Lifted sub_773320 to C++ that does exactly what the exe does (same reads, writes, calls in same order, same return void), exact x64 ABI signature `void sub_773320(void* a0 /*rcx*/, void* a2 /*rdx*/)`. All 4 calls go through `call qword ptr [0xF99FFA0]` = sub_eea6040 (boundary/vendor thunk, jmp rax). Verified with liftcheck + gate.

## ANALYSIS (from pack/773320.md listing, verbatim)
Function body [0x773320, 0x7733E9); 0x7733E9 starts a different function.
- state = a0+0xB0 (u32). a2 = handle { obj=[a2] at +0, cb=[a2+8] at +8 }. cb = control block { vfptr[0]=dtor, vfptr[8]=dealloc, strong@+8 u32, weak@+0xC u32 }. obj+0x30 = u32 flag zeroed when state==3.
- state==1: skip to release. state==2: obj->vfptr[1](obj, a2) then release (skip block/call2). state==3: zero obj+0x30, block build {obj,cb}, inc cb->strong, a0->vfptr[4](a0,&block,0), release. default: block build, inc strong, call2, release.
- release: cb=[a2+8]; lock dec cb+8 (strong); if 0 -> cb->vfptr[0](cb) dtor; lock dec cb+0xC (weak); if 0 -> cb->vfptr[8](cb) dealloc.

Calls (all `call qword ptr [0xF99FFA0]` = sub_eea6040 boundary/vendor thunk):
 0x77335a  call qword ptr [0xF99FFA0]  (obj->vfptr[1](obj,a2))
 0x7733a2  call qword ptr [0xF99FFA0]  (a0->vfptr[4](a0,&block,0))
 0x7733c5  call qword ptr [0xF99FFA0]  (cb->vfptr[0](cb) dtor)
 0x7733db  call qword ptr [0xF99FFA0]  (cb->vfptr[8](cb) dealloc)

## STATUS (all done)
- [x] Step 1: progress file with ## NEXT + step 2
- [x] Write sub_773320.h (layout constants + static_asserts + Boundary decl + signature)
- [x] Write sub_773320.cpp (LIFT marker, full reversal, registry, verbatim call quotes)
- [x] Write docs/functions/773320.md dossier (Reversed source complete, no [?]/[I]/TODO/UNVERIFIED)
- [x] python tools/sigs/liftcheck.py 0x773320 -> LIFTCHECK OK
- [x] python tools/ctx/gate.py 0x773320 -> GATE OK

## FILES
- docs/progress/oc_U-EX7.773320.md (this progress file)
- src/client/features/render/native/helpers/sub_773320.h (NEW)
- src/client/features/render/native/helpers/sub_773320.cpp (NEW)
- docs/functions/773320.md (NEW dossier)

## LIFTCHECK
LIFTCHECK OK 0x773320

## UNRESOLVED CALL
none (all 4 calls are sub_eea6040 via data slot 0xF99FFA0, boundary/vendor; classified in docs/data/native_boundary.tsv line 506)

## TOOL REQUESTS
none

## CLOSES?
CLOSES? YES
