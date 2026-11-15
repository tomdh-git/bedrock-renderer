# Progress: extractors-geometry (sections E, H, K L5*/L9*/L10b/L12*, M1d)

## NEXT
Resume with: chunk extractor 0x66ea3d0 inline bodies A..D / callees 0x67762e0 0x670b6e0 0x6722cb0 (see docs/functions/66ea3d0.md "Phase map", Open list); helper scripts were in scratchpad (ripstr/statics) - regenerate with disrange + rip-lea string resolution; tool to dump: `python tools/sigs/disrange.py 66ea3d0 66f9800 > $TEMP/chunk.asm` (12308 lines).
Half-done: the dossier covers the head (0x66ea3d0..0x66ea800, flag derivation from description+0x48 pass kind) and the call/phase skeleton; the four per-pass-variant bodies are NOT decoded.
Then: BatchActor builders: decode 0x66cc7a0 first, confirm (P50,P51,edi) pairing by following jump targets in $TEMP-regenerated disrange 66d9af0 66e26a7 (see docs/functions/66d9af0.md phase map). Live polls (ChunkGeometry description, FOV, FogColor, culling) NOT started: no live poll was run this session.

Honest scope note: the two top-priority extractors are 0xF430 and 0x8BB7 bytes (12.3k and 7.8k instructions); an instruction-complete source block per function is not achievable in one agent session. Entries below say exactly what is closed.

---

### E1d - DONE
Tag 6/8/10 forwarders of the Item visitor 0x6646980 (jump table 0xf2bf2d0 re-read from the exe, [V]): tag 6 -> 0x6647320, tag 8 -> 0x66473e6, tag 10 -> 0x6647383. Each is the identical 25-instruction forwarder: `mov rcx,rbx; mov rdx,[rbp+0x8a0]; mov r8,rdi; restore xmm6-13 from [rbp+0x8b0..0x920]; add rsp,0x9b8; pop rbx,rdi,rsi,r12,r13,r14,r15,rbp; jmp <extractor>` [V disrange]. Targets [V]: 0x6647320 -> 0x6698e30 (ItemInHand, tag 6), 0x6647383 -> 0x66d9af0 (BatchActor, tag 10), 0x66473e6 -> 0x66e75f0 (tag 8, strings BlockSelectionOverlay, BlockSelectionOverlayBlockEntity, MatColor, "UIStructureVolumeCapture texture"). Extractor signature for all: (rcx = builder state (rbx), rdx = per-frame ctx ([rbp+0x8a0]), r8 = description (rdi)).
CONTRADICTS L5d text ("GlowInkSign inside 8"): the string "GlowInkSignForwardPBR" (rva 0xf7ca238) has exactly one reference, at 0x66476d2 inside the visitor's tag-7 hash chain (block 0x66476bb: `cmp [rax+0x10], 0x5857c29e32acef88`, builds a 0x15-char name), not in tag 8 [V xref str]. Tag 8 is BlockSelectionOverlay only.
No code/struct output needed (pure forwarders); no assertion constants.

### H1a - DONE
Anchor `RenderChunkCoordinator::_launchVisibilityRebuild` = rva 0x7923d50 (size 0xb6b); task name string "renderchunk coordinator chunk visibility task" at rva 0xf5a6f86 with exactly one code reference, 0x79242d4 inside 0x7923d50 [V xref str, re-run on 62.01]. Second task anchor `LevelBuilder::scheduleChunkBuild` 0x533c910 ("Render Chunk Build"). RVAs move per patch; the version-stable anchor is the string (RenderChunk task names), as for all P2 anchors.

### E4 - OPEN (blocking: instruction-complete bodies A..D + callees 0x67762e0/0x670b6e0/0x6722cb0 + names of pass kind K)
Closed this session [V]: docs/functions/66ea3d0.md = head (phases 0-2), uniform block (phase 3: MeshContext, ViewPositionAndTime, FogAndDistanceControl, FogColor value sources in the description), dispatch (phase 5), call skeleton of the four bodies (phase 6). New header `src/sdk/mc/deps/minecraft_renderer/framebuilder/ChunkGeometryDescription.h` (ChunkGeometryDescriptionView + ItemFrameContextView, 20 static_asserts on offsets +0x00/+0x10/+0x30/+0x48/+0x50/+0x54/+0x64/+0x74/+0xB8/+0xD8/+0xE0/+0xE1/+0xE4; ctx +0x30/+0x40/+0x48/+0x68/+0x70/+0x74/+0x75). Not Sigs.json-anchored so static_asserts are the guard (no layout_asserts.json entry).
New facts: description +0x54 = FogColor vec4, +0x64 = FogAndDistanceControl vec4 (const {0.99,1,1e5,1e5} when +0xB8 != 0), +0x74 = time, +0xE4 = view position xyz; descr+0x48 -> u64 pass kind K (1=EndPortal, 0xB=WaterPrepass); ctx+0x70 == 1 = ForwardPBR family. CONTRADICTS 6be/6cb nothing; 6cb "four statics" confirmed: each of the four inline bodies hashes its own RenderChunkFogAlpha static.

### E2 / L5e - OPEN (callee map now complete [V]; inner decode pending)
Appended "Phase map" to docs/functions/66d9af0.md: phase 1 (group instances by model key = insts[i]+0x08 ->+0x40, sorted unique vector + u16 slot vector) [V], phase 2 (per-key cached u32 handle at key+0x258/valid +0x25C, key+0x185 flag) [V], phase 5 (ten builders and selector bytes P+0x50/+0x51, flag [rbp+0x7c8], instance-count != 0) with the builder-to-branch pairing [I]. Blocking fact: the ten builders (0x66bf290 0x66c1920 0x66c3840 0x66ce8d0 0x66c5760 0x66cc7a0 0x66c7680 0x66c98e0 0x66bb7b0 0x66bd430) and 0x66d9710/0x66c11b0/0x66a0f60 are not decoded, and the (P50,P51,edi) pairing is not confirmed by jump-target following.
### E7 / L5k - OPEN (builders located and call-site-tabulated above [V]; not decoded; blocking: same ten builders + draw-list builders 0x678c4c0..0x678f640 of the chunk extractor)
### H4 / L9f - OPEN (partial: chunk-side sources of ViewPositionAndTime/FogAndDistanceControl/FogColor/MeshContext are now exact [V] (E4 phase 3); blocking: FogAndDistanceControl/ViewPos writers for sky, weather, particles, clouds and the live producer of the +0x54/+0x64 fields)
### E1b, E1c, E2, E3, H1b, H2, H3b, L9c, L9e, L10b, L12a, L12c, L12d, M1d - OPEN, not started in depth (see final report)
