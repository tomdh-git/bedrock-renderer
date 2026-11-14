# Progress: extractors-dossiers (M1d dossiers, E1b/E1c/E3, H1b/H2/H3b, L9c/L9e/L10b, L12a/c/d)

## NEXT
Session ended after the H2/L9c closure; everything else is OPEN (see below), nothing half-edited, no files other than this one were created or changed.
Resume with H3b/L9e (real camera/chunk frustum cull). Leads found this session [V]: task strings "LevelCullerShadow task" (rva 0xf5a6fb4, only ref 0x5347b07 in fn 0x5347a10) and "levelCullerDistanceField task" (0xf5a70c7; refs in fns 0x5343930 (size 0x3b1), 0x5345de0, 0x5347320). Next step: `python tools/sigs/dossier.py 5347a10` and read what the shadow culler task calls; then look for the camera-side sibling (same task-spawn pattern, a sibling "LevelCuller..." task for the main view); the test itself will be a 6-plane loop (mulps/cmpps over a plane array) inside that task body.
Then dossiers: extractors are 2400-4700 instructions each (0x67417f0 2411, 0x67375a0 3262, 0x6745440 2860, 0x673d150 2633, 0x66ade80 2413, 0x66a1860 2381, 0x6698e30 4728), existing dossiers (docs/functions/<rva>.md) are skeleton + structure level (D1); instruction-complete source needs one agent session per extractor.

---

### H2 - DONE (answer: the game submits no occlusion queries; the feature is supported by the caps but unused)
Evidence:
- Static [V]: every direct caller of Encoder::submit 0xbc60740 passes the occlusion handle `mov r9w, 0xffff` immediately before the call: 0x569a464, 0x56ad434, 0x56ad9d1, 0xbcc3ac9, 0xbcc3cb8, 0xbcc3f55, 0xbcc40df, 0xbcc425e, 0xbcc459e, 0xbcc46fe, 0xbcc6373, 0xc270432, 0xc295e26 (callers list from `xref.py callers bc60740`: 0x569a3a0 0x56ad350 0x56ad810 0xbcc39b0 0xbcc3b90 0xbcc3e50 0xbcc3fa0 0xbcc4150 0xbcc4b90 0xc270330 0xc295d50; 13 call sites in 11 callers all carry 0xffff; found with `disrange.py` + grep of the 7 lines before each call). Calls through a pointer would not show here [I: submit has only direct callers in the xref tool].
- Handles.h already records [V] that the occlusion-query allocator (ctx+0x1DFBE94, cap 256) is touched only by Context::frame() and the destructor in the bgfx range, i.e. no createOcclusionQuery-style allocation exists; live count 0.
- Live poll [V, read-only, game 62.01, base 0x7FF65A5B0000, ctx 0x503a4010040]: 4 consecutive samples of the consume frame (buffers 0x503a4023d80 / 0x503a4e98740 alternate), each with `[F+0xE746D8]` unchanged across the read, 1064 draw headers at F+0xB4700 stride 0x80: 0 headers with u16 +0x7A != 0xFFFF and 0 with state bit 62 (byte +0x27 & 0x40). `Frame+0x14300` int32 m_occlusion[256]: all 256 entries = 0xFFFFFFFF (never written).
- Consequence: H2 is closed as "no occlusion query usage in this build/path"; terrain visibility is CPU-side (H1b flood fill, RenderChunk record +0x254/+0x258/+0x25E) and `ChunkOccluder` / `SimpleOccluder` are materials drawn as normal geometry. CONTRADICTS 6bf line "query-based occlusion helper 0x660ecd0" (already corrected by 6bl).
Caveat [I]: one 4-frame sample in a populated server; a mode that is off in this scene could still exist, but there is no code path that sets a handle.
No files, no assertion constants (existing Frame.h kHandle7A / kOcclusion cover it).

### L9c - DONE
Identical to H2 (same text in the checklist). Evidence as H2.

### L10b - DONE (as scoped: the field), real cull tracked under H3b/L9e
`frustum_visibility` is a light-scoring weight in the lighting-config deserializer 0x10f09f0 (6bj, string site 0x10f45d0); not a cull. The item text also says "real cull unfound": that part is exactly H3b/L9e and stays OPEN there. Recommend the lead splits the item.

### H3b - OPEN (blocking fact: the function that tests a chunk/actor AABB against the camera frustum is not located)
Narrowed [V]: the name-bearing anchors are the task strings "LevelCullerShadow task" (fn 0x5347a10, ref 0x5347b07) and "levelCullerDistanceField task" (fns 0x5343930, 0x5345de0, 0x5347320; refs 0x5343a15, 0x5345ed7, 0x5347417). 0x5343930 is a 0x3b1-byte task wrapper (frame 0x168, no direct callers, reads this+0x108/0x110/0x190/0x1b0, vcalls [obj+8] slot 1 x8) [V dossier.py mechanical output]. The existing 6bm check shows the chunk extractor has no frustum math, so the test is in the LevelCuller task bodies or in the actor queue. No RTTI names for Culler classes exist in the exe (xref str Culler/Frustum finds only the two task names and the aim-assist entt component).
### L9e - OPEN (same blocking fact as H3b)

### H1b, E1b, E1c, E3, L12a, L12c, L12d, and M1d dossiers (particle 0x67417f0, sky/clouds 0x67375a0, weather 0x6745440, FlameBillboard 0x673d150, UI 0x674a3a0, Gameface 0x66ade80, editor 0x66a1860, ItemInHand 0x6698e30, skinned, nametag) - OPEN, not started in depth
Blocking fact for the dossiers: each extractor is 2.4k-4.7k instructions (sizes above) and the present dossiers are D1 skeletons; instruction-complete reversed source is one session of work per extractor and none was completed. Existing dossier files are untouched. E3/E1b/E1c need the Item visitor tag handlers (0x6646980 cases) decoded together with the descriptor field dumps (6cv); H1b needs the compute 0x791f170 body; L12a/L12c/L12d need the dispatcher internals / 0x531b120 re-check on 62.01 / the nametag skin-shadow blob read.
