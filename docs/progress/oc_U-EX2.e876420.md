## NEXT
DONE

# UNIT U-EX2.e876420 — BgfxFrameBuilder slot 16, sub_e876420 (0xc5 bytes, depth 6, D0, 0 callees in set)

## STEP 1 (done)
- Wrote this file with `## NEXT` / `step 2` header.
- Read docs/OPENCODE_BRIEF.md, docs/RENDER_NATIVE_SPEC.md, docs/progress/_d_U-EX2.e876420.txt.
- Disassembled 0xe876420 (0xc5 bytes = 0xe876420..0xe8764e5) with `rdis dis 0xe876420 80` [V].
- Callees: 0xF9A7480 (indirect slot, read at call time), 0xEEC6D80 (lift, forward-declared), 0xE951550 (crt boundary __security_check_cookie) [V].
- Reference model: src/client/features/render/native/d3d12/sub_e874e20.cpp/.h (same slot-16 family, 0xe874e20) — used as template only, not proof.

## STEP 2 (done)
- Created src/client/features/render/native/d3d12/sub_e876420.cpp + .h (NEW files only).
- Created docs/functions/e876420.md dossier with Reversed source (complete).
- Ran `python tools/sigs/liftcheck.py 0xe876420` → `LIFTCHECK OK 0xe876420`.

## FILES
- docs/progress/oc_U-EX2.e876420.md
- docs/functions/e876420.md
- src/client/features/render/native/d3d12/sub_e876420.cpp
- src/client/features/render/native/d3d12/sub_e876420.h

## LIFTCHECK
LIFTCHECK OK 0xe876420

## UNRESOLVED CALL
none

CLOSES? YES