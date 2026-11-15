# Progress: passes-vv

## NEXT
Done: L16c; L6b partial (VV group-builder call order in 0x55f1450 recorded); L6d blocked. Remaining (optional): (1) L6b per-handle output names: read statics in 0x55f1450 around each builder call with vvstatics.py over 55f1450..563f594 split by range; (2) L6d: find the store of vtable 0xf25b2e0 (installed via data) and the Fancy counterpart.

## Units
### L15c - DONE. Checklist wording compared against (docs/RENDER_CHECKLIST.md line "L15c"): "tonemap/SSR strings - 6x (bloom/SSAO inner pending)". Evidence: tonemap/colour grading builder 0xbcacd90 with all uniforms (vv_lambda_bodies.md), SSR 4 passes with all uniforms and textures (vv_group_builders.md 0xbc82ad0), bloom inner passes DFDownSample/ThresholdedDownSample/DFUpSample/BloomBlend with BloomParams/ViewportScale/HDRi/BlurPyramidTexture and bodies (ScreenDraw 0xbc04dc0), SSAO: no such string in the exe (xref str SSAO / AmbientOcclusion = none). Shader-side math is not required by that wording.
### L15d - DONE: slot 64 gate, NGX parameter order, evaluate wrapper 0xed360d0, and slot 60 0xe83ec70 (DLSS optimal settings, mode strings, feature create params) [V].
### L16b - DONE [I]: no DXR build/DispatchRays call exists in the RTX fork (exe-wide offset scan 0x240/0x260 clean; device/command-list classes identified; RTX path is compute Dispatch plus SRV/UAV descriptor writes). Residual: List4 QI result in slot 64 ([rbp+0x9e0]) not traced past releases. See vv_lambda_bodies.md Round 8.
### L16d - DONE: slot 54 push, slot 63 consumer and its loop body (validation strings, hash lookups), slot 64 frame structure [V/I] (vv_lambda_bodies.md Round 7).
### L6f, L16a, L15a - DONE (earlier). M1e/L6a - OPEN (0x67cf1d0 is a helper, slot 63 loop read; blocking: pass-list closure for Fancy/RTX bodies not re-verified). L15b, L6b, L6d, L16c - OPEN (unchanged).

### rdis note (round 6)
- [V] `rdis fld 408 --w` finds no writer of ctx+0x408 inside 0xe80000..0xe86000 (only unrelated string-capacity stores); the device wrapper pointer is set in the base context (outside the RTX fork). Next: `rdis xr`/`fld 408 --w --base rcx` in the base context ctor (near 0xe82e230 base submit), then `rdis vt` on its vtable for slots 0x70/0xd0/0xf8 (L16b).

### L16c - DONE [V/I]: RT pass and denoiser names, inline ray queries (vv_lambda_bodies.md Round 10). L6b - OPEN: pass order recorded, per-handle output names not mapped. L6d - OPEN: blocking fact in Round 10.
