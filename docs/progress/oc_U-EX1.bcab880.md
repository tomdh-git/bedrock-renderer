## NEXT
DONE

Unit: U-EX1.bcab880, function 0xbcab880 (sub_bcab880), size 0x6a bytes, depth 3, milestone 1, region bgfx, status D0, name "group insert UI". CLOSES? YES (liftcheck printed LIFTCHECK OK 0xbcab880).
Goal: lift 0xbcab880 to C++ with exact x64 ABI signature; artifacts: docs/functions/bcab880.md (Reversed source (complete)), src/client/features/render/native/bgfx/ sub_bcab880.{cpp,h} (NEW only), result file this one. Then run liftcheck.py 0xbcab880 and fix failures; CLOSES? YES only on LIFTCHECK OK.

Plan:
1. [x] Write progress file (## NEXT / step 2).
2. [x] Disassemble 0xbcab880 for 0x6a bytes; record every instruction verbatim.
3. [x] Determine signature: rcx = GroupEntry* entry; AL = (*(uintptr_t*)*(UiObject**)(entry->uiObject+0x18) != 0); two calls through data slot 0xF99FFA0 -> sub_eea6040 (class vendor boundary, docs/data/native_boundary.tsv line 506; verified slot stores VA 0x14eea6040 = base 0x140000000 + RVA 0xeea6040).
4. [x] Write docs/functions/bcab880.md (Reversed source (complete), verbatim call quotes, struct fields table, no [?]/[I]/TODO/UNVERIFIED).
5. [x] Write src/client/features/render/native/bgfx/sub_bcab880.h (.cpp with LIFT marker, layout constants + static_asserts, signature, LIFT_FN registry entry, footprint).
6. [x] Run python tools/sigs/liftcheck.py 0xbcab880 -> LIFTCHECK OK 0xbcab880 (pasted below under ## LIFTCHECK).
7. [x] Finalize: ## FILES, ## UNRESOLVED CALL = none, CLOSES? YES.

## FILES
- docs/progress/oc_U-EX1.bcab880.md (this result file; created step 1, finalized here)
- docs/functions/bcab880.md (created: dossier with signature, argument use, callees, Reversed source (complete), struct fields touched, ownership/threading, version anchors, verification)
- src/client/features/render/native/bgfx/sub_bcab880.h (created: GroupEntry/RefCnt/UiObject layout constants with static_asserts, signature, footprint declaration)
- src/client/features/render/native/bgfx/sub_bcab880.cpp (created: first line `// LIFT 0xbcab880 size 0x6a 1.26.62.01 sub_bcab880`, lifted body with per-instruction // 0xA..0xB ranges, verbatim call quotes, callReleaseThunk via data slot 0xF99FFA0, footprint, LIFT_FN registry entry)

## LIFTCHECK
LIFTCHECK OK 0xbcab880

## UNRESOLVED CALL
none: both calls `0xbcab8b5  call qword ptr [0xF99FFA0]` and `0xbcab8cb  call qword ptr [0xF99FFA0]` target sub_eea6040 (0xeea6040), class vendor boundary listed in docs/data/native_boundary.tsv line 506 ("thunk via data slot 0xF99FFA0 (loader-resolved)"), reached through a slot read at call time; slot verified in the PE to store VA 0x14eea6040 = image base 0x140000000 + 0xeea6040. No callee is outside the lift set and native_boundary.tsv.

CLOSES? YES
