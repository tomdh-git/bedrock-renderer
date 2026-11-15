# Progress: passes-materials-visuals

## NEXT
Resume with M1e remaining bodies: 0xbc0b240 (voxel combine), 0xbc5bad0 (ClusterLights), 0xbc36140 (DoIndirectSpecularUpscale), 0xbc38c20 (NothingTask x3), 0xbc0f130 (CubemapToOffscreen), 0x56d4880 (TAAU), 0xbc0ac20 (voxel upload), 0xbc080c0->0xbcc4b90 (RTX 43 passes). For each: `python tools/sigs/disrange.py <lo> <hi>` then `xref.py strs <rva>`, write docs/functions/<rva>.md. Also open: live texture census (BGFX_MAP 6im anchors in AGENT_BRIEF) for L7f/L8d.
Template learned: material-pass-object bodies share one skeleton (see docs/functions/material_pass_bodies.md).

## Units
### M1e (partial) - OPEN (6 of 35 VV/RTX lambdas closed to D1; resource-per-pass mapping still missing)
- [V] 0xbc2c590, 0xbc2cd20, 0xbc2d550, 0xbc2dd20, 0xbc2eb50, 0xbc2f4a0: one shared template, pass hashes recomputed with FNV-1 64 and equal to the movabs immediates (CausticsMultiplierPass 0x289bd38b28795cbc, DirectionalLightingPass 0x993692fcf6fc1544, DiscreteIndirectCombinedLightingPass 0x48f2445a7c85f35c, SurfaceRadianceUpscalePass 0xc1772ebae6046ecb, WaterExtinction 0xf4768b63b9171d0b, WaterSurface 0xa77420c6852a856f). Markers: DoDeferredLighting (2), DoDeferredShading (2), WaterExtinction, WaterSurface. Submit forms: 0xbcc38e0 (Caustics, Directional, WaterExtinction), 0xbcc3e50 (Discrete, SurfaceRadiance; pointer-form transform), 0xbcc39b0 (WaterSurface; list form).
- Correction to pass_bodies.md: the other three deferred bodies are NOT all submitted through 0xbcc38e0; two use 0xbcc3e50, one 0xbcc39b0. Also not all apply the +0x1A0 uniform block (Caustics does not).
- File: docs/functions/material_pass_bodies.md.
- OPEN: per-pass sampled textures need the pass-group builders' declaration order mapped to Resources fields; uniform block layout at Resources+0x1A0; WaterSurface variant selection.

### L8d / L7f (partial) - OPEN (VV/RTX render targets cannot be censused while the game runs Fancy)
Live read-only polls (CE evaluate_lua readBytes only, 2 polls, 1.26.62.01, base 0x7FF65A5B0000, obj=[base+0x12BB4910], ctx=[base+0x12AE1748]):
- [V live] Framebuffer table obj+0xC97698 (stride 0x68), records 0..127 scanned: exactly ONE record has numAttachments>0 or a window pointer: fb 0x12 (18): 1 color attachment, texture 0x5A = 1024x1024, requested fmt/actual fmt byte +0xB0 = 0x43, SRV format +0x40 = 0x1C (RGBA8), mips 2, layers 1, flags +0x98 = 0x1000, type 2D, no depth. Used by view 16 (rect 1024x1024). No window-FB record found in 0..127 (swap-chain pointer at +0x18 was zero for all): window FB is likely not in this table or sits at index >= 128 [?].
- [V live] Per-view array ctx+0x1EAB080+v*0x140: +0x130 u16 fb handle was 0xFFFF for every view except view 16; rects (+0x14 w, +0x16 h, +0x132 sort byte): views 0-15 and 46-49 = 1920x1137, 19-25 and 44-45 = 1248x739, 27..32 = 624x369, 312x184, 156x92, 78x46, 39x23, 19x11 (a down-sample chain), 33 = 39x23, 38-42 = 78x46, 156x92, 312x184, 624x369 (up chain), 17,18,26,34-37,43 = 1x1, views 50-63 = 1x1 sort 0 (unused). Sort byte 1 (sequence) on 0..49.
- [I] The 1248x739 = 65% of 1920x1137 and the 6-level down/up chain are the signature of VV bloom/HZB/upscale views, so these rects are residue of VV pass views (the VV lambdas did not run in 6aa; either the rects are from a previous VV frame or a lambda subset executes in this world) [?: needs a poll while the pass-name table 0xe9002e0 task list is read].
- Contradiction note to 6z-2 ("main color target 1920x1137 fmt 0x1a x2"): none of the 128 framebuffer records references such a texture; the color target is therefore bound through a window FB or a record index >= 128 [?].
- Blocking fact: need the live frame-graph (render-target) allocator output while VV is enabled; not available in the user's Fancy session.

### Other items (F1a F1b F2b F4 G1b G2 G4a G4b G6 I1a-I7, L6a/b/d/f, L7b/c/e/f/h, L8a-d, L11a-d, L13a-d, L14a-d, L15a-d, L16a-d) - OPEN (not started this run; see NEXT)
