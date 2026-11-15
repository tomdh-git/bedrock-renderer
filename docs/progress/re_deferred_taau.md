# M1e reverse: DEFERRED + TAAU + VOXEL pass bodies (1.26.62.01)

Agent: coder. Task: find and fully read DEFERRED pass + TAAU pass + VOXEL pass (if present). Per pass: rdis `dis <rva>` + `path`/`sum`; map RTV/DSV handles + allocations, binds, shader/program selection, uniform writes via 0x5679db0, dispatch/clear/resolve order, DLSS stub calls inside TAAU, per-pass in/out. D2-style instruction maps where feasible. Write docs/functions/<rva>.md per pass. Additive SDK header edits under src + static_asserts on confirmed layouts; optional docs/data/layout_asserts.json additions. Write this progress file + final report + FULL PROPOSED BGFX_MAP ENTRY TEXT at bottom. Do NOT edit BGFX_MAP.md or RENDER_CHECKLIST.md. Stop on blocker; report precisely what's missing.

Known anchors [V from brief + existing dossiers]:
- uniform writer 0x5679db0 (dossier docs/functions/5679db0.md)
- pass-name resolver 0x675e440
- VV pass builder 0x55f1450
- frame renderer entry 0x67c9c20
- DLSS stubs 0xe83ec70 / 0xe8403d0
- SSR owned by separate stream: do NOT touch SSR.

Candidate bodies from vv_pass_table.md / vv_group_builders.md / vv_lambda_bodies.md (all [V] via prior reads, not yet re-verified by me):
- DEFERRED group builder 0xbb6b350: CausticsMultiplierPass 0xbc2c590 (0x558), DirectionalLightingPass 0xbc2cd20 (0x5F2, D1), DiscreteIndirectCombinedLightingPass 0xbc2d550 (0x5E4). SurfaceRadianceUpscalePass 0xbc2dd20 (0x5DB) via builder 0xbb74040.
- TAAU: body 0xbc8cfd0 (0x1775), closure vtable 0xF44B2E0, builder 0xbc8a380, pass hash 0x765ef57e0263ffb6 "TAAUpscaling", 10 uniforms [D1 per vv_lambda_bodies.md].
- VOXEL: CombineVoxelLighting 0xbc0b240 (0x88B, D1), builder 0xbb3e2b0, pass hash "Combine" 0x04e50856c4371e38; voxel upload 0xbc0ac20 (0x162, D2).

## NEXT
1. Grep docs/data/render_hashes.txt for Deferred/TAAU/Voxel pass names + confirm which body is "THE DEFERRED pass".
2. rdis dis + path + sum on each target RVA (BS_EXE).
3. Read each body instruction-complete; map RTV/DSV, binds, program selection, uniform writes, dispatch/clear/resolve, DLSS stub calls inside TAAU, in/out.
4. Write docs/functions/<rva>.md per pass (D2: every instruction maps to a source line).
5. SDK header edits + static_asserts + layout_asserts.json additions (unique names).
6. Final report + proposed BGFX_MAP entry text at bottom of this file.
