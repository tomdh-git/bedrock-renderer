# Progress: passes-vv

## NEXT
Unit 2 DONE (all builder timelines are in docs/functions/vv_group_builders.md). Now: dossier the lambda bodies one at a time: 0xbc0b240, 0xbc5bad0, 0xbc36140, 0xbc38c20, 0xbc0f130, 0x56d4880, 0xbc0ac20, 0xbc080c0 -> 0xbcc4b90 (43 RTX passes). Then L15 (TAAU uniforms, FSR1 0xbcb3cf0, DLSS wrapper vt slots 60/64), L16 (TLAS/BLAS, RT shaders), L6a/b/d/f lists.
Tools I added: tools/sigs/vvskel.py, tools/sigs/vvstatics.py. Note: bash heredocs fail in this shell for long text, use the Write tool.

## Units
### U1 (M1e blocking fact: builder declaration order -> Resources) - DONE
Resources layout and per-pass name-keyed bindings: docs/functions/vv_group_builders.md. Resources = pass+0x78 (0x2A0 bytes) of a 0x338 pass object (ctor 0xbc2c040, move ctor 0xbc2be20) [V]. Textures/uniforms are bound by name-hash statics (value at guard-8), not by Resources fields; listed per pass block for 0xbb6b350, 0xbb74040, 0xbb7efb0, 0xbb81880, 0xbb8eb70, 0xbb84ee0, 0xbb3e2b0, 0xbc7c580, 0xbc7f6e0, 0xbc82ad0, 0xbc8a380, 0xbbbfc50, 0xbc57460. Correction to material_pass_bodies.md: "+0x1A0 uniform block" is inside the +0x118 binding container, not a block of its own [I].
