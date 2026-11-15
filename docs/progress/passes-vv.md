# Progress: passes-vv

## NEXT
Done this round (docs/functions/vv_lambda_bodies.md): 0xbc068f0 control flow, 0xbcc4b90 (all 43 resolved; no selection), 0xbcc1bf0 (buffer create/update, not a virtual). Remaining, in order: (1) 0xe83d7d0 (RTX slot 54, 0x671) and 0x67cf1d0 instruction reads -> closes M1e/L6a (PreBlasSkinDispatch) and L16b/L16d; (2) 0xbc71da0 (buffer create used by TLAS instance upload); (3) slot 64 0xe8403d0 (0xAA5B) DLSS evaluate and slot 60 0xe83ec70 for L15d (strings already in BGFX_MAP 6bc); (4) ColorGrading: find the ColorPostProcess material shader constants (builder 0xbbbcb20 sets ColorGrading_Misc only; the math is in the shader, not the exe) -> likely mark L15c DONE with that fact; (5) L6d Fancy pass list (6da-6dc) re-derive; L15b FSR1 builder 0xbcb3cf0 (0xbcb64f0 caller; resource names are not statics, read with vvskel); L16c RT shaders/denoiser. Tools: `export PYTHONUTF8=1`; tools/sigs/vvskel.py, vvstatics.py, vvclosures.py. Use Write/Edit tools (bash heredocs fail).

## Units
### U1 DONE; U3-U5 bodies in docs/functions/vv_lambda_bodies.md (see that file for the full list).
### L6f - DONE (43 names in order, all resolved every call via findPass; per-call selection does not exist in 0xbcc4b90; textures = fixed 65-slot table by 0xc28f000, slot map 0xF4797D0). Caveat: the RTX renderer (slot 54) chooses what runs; not part of this item.
### L16a - DONE (names, hashes, program resolution, 65 texture slots). Per-pass texture use is inside the RT shaders, not in the exe pass code.
### M1e - OPEN. Blocking fact: 0x67cf1d0 / 0xe83d7d0 (PreBlasSkinDispatch callees) not read; everything else closed (bodies listed in vv_lambda_bodies.md).
### L6a - OPEN: same blocking fact as M1e.
### L6b - OPEN: out target handles are builder arguments (no names); order is 6ar.
### L6d - OPEN: Fancy pass list not re-derived.
### L15a DONE (see earlier). L15b OPEN (FSR1 builder resources). L15c OPEN (ColorGrading math lives in the shader). L15d OPEN (slot 64 instruction read).
### L16b - OPEN: instance buffer upload decoded (0xbcc1bf0 -> 0xbc71da0); TLAS build itself in RTX context slots 50/54 not read.
### L16c - OPEN (not started). L16d - OPEN (slot 54 role now known from its caller; 0xe83d7d0 body unread).
