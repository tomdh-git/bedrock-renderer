# LevelCuller class family (1.26.62.01) - ext-culling-visitor

[V] = disassembly read; [I] = inferred.

## Factory
0x537ea50 `makeCuller(out, kind /*dl 0..5*/, weak level, arg)` [V]: jump table rdata 0xf249c90, six kinds. Kind byte comes from a config byte: callers 0x5334430 (edx = byte [cfg+0x4e], from 0x53599d0 / 0x535f3e0) and 0x537e7e0 (byte [cfg+0x4d], from 0x535ecd0). So the active culler is a setting, not a fixed camera/shadow split [V flow, I meaning].
Kind -> final vtable (slot -1 at address; slot 0 = launcher): 0 -> 0xf247330 [I, case ended outside the linear scan], 1 -> 0xf247450, 2 -> 0xf2473c0, 3 -> 0xf2474e0, 4 -> 0xf247550 (LevelCullerShadow), 5 -> 0xf2495e0 [V for 1-5].
Launchers: kinds 0,1,2 = 0x5343930; kind 3 = 0x5345de0 (body 0x53c7fc0); kind 5 = 0x5347320 (body 0x53ca890); kind 0..2 body 0x53c6610; kind 4 = 0x5347a10 (body 0x53cc570). Task names: "levelCullerDistanceField task" (all but kind 4), "LevelCullerShadow task" (kind 4).

## Shared base slots (identical in all six vtables)
3 0x53419b0, 4 0x5342720, 5 0x5341de0, 6 0x5342340, 7 0x5342510, 9 0x5343590.
- slot 9 `isSectionVisible(state*)` 0x5343590 [V]: the per-section cull query (see progress file Unit 2).
- slot 6 `isSectionFresh(int3*)` 0x5342340 [V].
Both: recursive owner lock (+0xf0/+0xf8/+0x100), grid [this+0x20] with 16-byte cells (+0xE flags, +0xF generation vs this+0x40).

## Algorithm (shadow kind)
Best-first flood over the section grid, see docs/progress/ext-culling-visitor.md H3b entry and Unit 2 field map. No frustum planes.
