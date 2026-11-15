## NEXT
(none — R9 complete; awaiting lead review / fold into BGFX_MAP.md)

## Progress log — R9 Sky group bodies (1.26.62.01, STATIC ONLY)

### UNIT 1 — DONE: Sky group inventory + existing coverage
Inventory complete: wrapper 0x6655de0 (slot 0x370), visitor 0x66560f0 (11-case jump table 0xF2BF39C). Existing mechanical dossiers for all clones/ctors/producers located: 53707a0 (EndSky thin), 5370b20 (CelestialBody thin), 660b720 (Cubemap thin), 660b1a0 (LegacyCubemap fat), 5ad5800 (Weather thin), 5369b30 (Sky/Stars producer), 53e2c00 (Atmosphere producer), 53e3aa0 (VolumetricFog/SkyAmbientSamples producer), 668c910 (Sky/EndSky ctor).

### UNIT 2 — DONE: Sky visitor case bodies (rdis disassembly of sub_66560f0) [V]
Argument convention [V]: rdx=frameCtx, r8=InsertVariant, [r8]=desc (rdi), [r8+8]=tag (al). Per-case verified reads/calls:
- tag 0 Atmosphere @0x6656174: desc +0x00 word, +0xA4/+0xB4/+0xC4 xmm blocks, +0xE0 qword shared_ptr (lock-inc ctrl+8). Tail 0x6656D4B. Matches RenderAtmosphereDescription/RenderSkyDescription head reads (descscan).
- tag 1 Clouds @0x6656697: tail-jump setup rcx=rbx,rdx=rsi,r8=rdi → extractor 0x67375a0. [V: entry reg setup; target from group_visitors.md first-callee table]
- tag 2 Cubemap @0x66562d5: lock-inc WORD [desc+0x10], byte [desc+0x12] test bit1; frameCtx+0x70==1 → "CubemapHDRi"/"Cubemap"; 0x67d6d70 resource-cache get; addref shared_ptr pair desc+8/+0. [V]
- tag 3 EndSky @0x665649c: frameCtx+0x70==1 → "EndSkyForwardPBR"/"EndSky"; size 0x10 if==1 else 6; alloc 0x20 via frame-ctx allocator [0x1233E1A8]; tail 0x6656BEC (r13d=size, r12=block). [V]
- tag 4 LegacyCubemap @0x66561cc: globals+TLS; material "LegacyCubemapForwardPBR"; jmp 0x6656B2B. Extractor head reads byte +0x3E. [V]
- tag 5 Sky / tag 6 Stars: first callee 0x675e440 resource-cache [group_visitors.md]. Descriptions RenderSkyDescription (0xB0) / RenderStarsDescription built by producer 0x5369b30. [I: bodies not re-dumped past entry; first-callee claim consistent]
- tag 7 CelestialBody @0x6656516: desc +0x18 xmm; byte [desc+0x70]==0 required; frameCtx+0x70==1 → "SunMoonForwardPBR"/"SunMoon"; 0x675e440; addref shared_ptr pair desc+8/+0. RenderCelestialBodyDescription 0x88. [V]
- tag 8 VolumetricFog @0x66569b1: first callee 0x5aba5c0 (thread-local/pass lookup) [group_visitors.md]. RenderVolumetricFogDescription 0xE0 (+0x00 u16, +0x04 rows, +0x44 row, +0x54 qword; tail unread). [I first-callee; V struct]
- tag 9 Weather @0x665627e: bare tail-jump rcx=rbx,rdx=rsi,r8=rdi → 0x6745440 Weather extractor. RenderWeatherDescription 0x130. [V tail-jump; V struct]
- tag 10 SkyAmbientSamples @0x6656983: u16 [desc+0x00]; ref on ctrl block [desc+0x10]. RenderSkyAmbientSamplesDescription 0x18. [V]

### UNIT 3 — DONE: Clone/producer dossiers filled (analyst sections)
- 53707a0.md EndSky thin (tag 3): desc pre-built by ctor 0x668c910 @5369f89, stores tag 3, calls Sky insert slot [obj+0x370] slot 110. [V]
- 5370b20.md CelestialBody thin (tag 7): tag 7, same slot. [V]
- 660b720.md Cubemap thin (tag 2): producer 0x6606580 fills after ctor 0x668eb10; tag 2; same slot. [V]
- 5ad5800.md Weather thin (tag 9): tag 9 → visitor tail-jump to 0x6745440. [V]
- 660b1a0.md LegacyCubemap fat (tag 4): internal 4-way jump table 0xF2BDBB8, resolves texture via 0x4dfb570, fills RenderLegacyCubemapDescription 0x40, tag 4, same slot. [V]

### UNIT 4 — DONE: Visitor + wrapper analyst dossiers
- 66560f0.md Sky visitor: full argument convention, pseudocode, structs/tags/anchors/verification. [V+I as noted]
- 6655de0.md Sky insert wrapper: zone "FrameBuilder - Insert sky" (0x6656000), forwards to 0x66560f0, calls 0x1166e0 profiler helper. [V]

### UNIT 5 — DONE: Reconciliation with Descriptions.h / FrameBuilder.h
All Sky descriptions already present in Descriptions.h with verified offsets: RenderSkyDescription 0xB0, RenderStarsDescription, RenderCubemapDescription 0xC0, RenderLegacyCubemapDescription 0x40, RenderCelestialBodyDescription 0x88, RenderVolumetricFogDescription 0xE0, RenderSkyAmbientSamplesDescription 0x18, RenderAtmosphereDescription 0x138, RenderWeatherDescription 0x130, RenderEndSkyDescription = RenderSkyDescription. SkyGroupTag enum complete (0..10 minus gap at 6? no: 0,1,2,3,4,5,6,7,8,9,10 all present). No header edits needed — all constants already asserted. [V: cross-checked constructor/extractor reads against struct fields]

## Final report

R9 Sky group analysis complete (static disassembly only; no debugger/live writes per brief).

Covered (all [V] unless tagged [I]):
- Insert wrapper 0x6655de0 (slot 0x370) → visitor 0x66560f0.
- Visitor dispatch: 11-case jump table 0xF2BF39C at 0x665616b; argument convention rdx=frameCtx, r8={desc,tag}.
- Per-case field typing and call flow for tags 0 (Atmosphere), 2 (Cubemap), 3 (EndSky), 4 (LegacyCubemap), 7 (CelestialBody), 9 (Weather tail-jump 0x6745440), 10 (SkyAmbientSamples). Tags 1 (Clouds → 0x67375a0), 5/6 (Sky/Stars → 0x675e440), 8 (VolumetricFog → 0x5aba5c0) rely on group_visitors.md first-callee table + Descriptions.h [I for body detail].
- Thin clones 53707a0/5370b20/660b720/5ad5800 and fat clone 660b1a0; producers 0x5369b30/0x53e2c00/0x53e3aa0; ctor 0x668c910.
- All Sky description structs already typed in Descriptions.h with static_asserts; no additive header edits required (constants already asserted). No layout_asserts.json additions needed (no new immediate/displacement constants outside already-asserted structs).

Files created/edited:
- docs/functions/66560f0.md (visitor analyst sections rewritten)
- docs/functions/6655de0.md (wrapper analyst sections rewritten)
- docs/functions/53707a0.md, 5370b20.md, 660b720.md, 660b1a0.md, 5ad5800.md (clone analyst sections rewritten)
- docs/progress/re_sky_groups.md (this file)

OPEN (blockers for full D2 on tags 5/6/8 bodies): visitor bodies for tags 5, 6, 8 not dumped past entry; first-callee claims taken from group_visitors.md [I]. Would require disrange of 0x66566ee/0x6656812/0x66569b1 regions to confirm field reads. Not blocking the struct/tag/call-flow picture.

## FULL PROPOSED BGFX_MAP ENTRY TEXT

Entry IDs TBD (all 6ga-6io allocated; lead to assign). Suggested placement: section 6g, adjacent to 6gf (Sky/Stars descriptions) and 6gb (Clouds).

---

### [TBD-6G-1]. Sky group visitor dispatch — 0x66560f0 (static, 62.01) [V]
Wrapper 0x6655de0 = FrameBuilder vtable slot 0x370 ("FrameBuilder - Insert sky", 0x6656000); forwards (this, frameCtx=rdx, variant=r8) to visitor 0x66560f0. Argument convention: rdx=frame context, r8=InsertVariant{mDescription, mTag}; desc=[r8]→rdi, tag=[r8+8]→al. 11-case jump table at 0xF2BF39C, dispatch 0x665616b. Cases: 0 Atmosphere @0x6656174 (desc +0x00 word, +0xA4/+0xB4/+0xC4 xmm, +0xE0 shared_ptr; tail 0x6656D4B), 1 Clouds → tail-jump 0x67375a0, 2 Cubemap @0x66562d5 (lock-inc WORD desc+0x10, byte desc+0x12, frameCtx+0x70→"Cubemap"/"CubemapHDRi", 0x67d6d70, addref desc+8/+0), 3 EndSky @0x665649c (frameCtx+0x70→"EndSky"/"EndSkyForwardPBR", alloc 0x20 via [0x1233E1A8], tail 0x6656BEC), 4 LegacyCubemap @0x66561cc (globals+TLS, "LegacyCubemapForwardPBR", jmp 0x6656B2B), 5 Sky / 6 Stars → 0x675e440 resource-cache, 7 CelestialBody @0x6656516 (desc +0x18 xmm, byte desc+0x70==0, "SunMoon"/"SunMoonForwardPBR", 0x675e440, addref desc+8/+0), 8 VolumetricFog → 0x5aba5c0 pass lookup, 9 Weather → tail-jump 0x6745440, 10 SkyAmbientSamples @0x6656983 (u16 desc+0x00, ref ctrl block desc+0x10). Cross-checked: Descriptions.h structs + group_visitors.md first-callee table. Tags 5/6/8 bodies not dumped past entry [I]. Docs: docs/functions/66560f0.md, 6655de0.md.

### [TBD-6G-2]. Sky clones + producers + constructors (static, 62.01) [V]
Thin clones (store tag, call Sky insert slot [obj+0x370]=slot110): 0x53707a0 EndSky(tag3, desc by ctor 0x668c910 @5369f89), 0x5370b20 CelestialBody(tag7), 0x660b720 Cubemap(tag2, producer 0x6606580 after ctor 0x668eb10), 0x5ad5800 Weather(tag9 → visitor tail-jump 0x6745440). Fat clone 0x660b1a0 LegacyCubemap(tag4): 4-way jump table 0xF2BDBB8, texture resolve 0x4dfb570, fills RenderLegacyCubemapDescription 0x40. Producer 0x5369b30 builds RenderSkyDescription(0xB0)/RenderStarsDescription via ctor 0x668c910 and inserts EndSky/CelestialBody/Cubemap(x4). Producer 0x53e2c00 builds RenderAtmosphereDescription(0x138). Producer 0x53e3aa0 builds RenderVolumetricFogDescription(0xE0)/RenderSkyAmbientSamplesDescription(0x18). Docs: docs/functions/53707a0.md, 5370b20.md, 660b720.md, 660b1a0.md, 5ad5800.md, 5369b30.md, 53e2c00.md, 53e3aa0.md.

### [TBD-6G-3]. Sky description structs — already in Descriptions.h (static, 62.01) [V]
RenderSkyDescription 0xB0 (+0x00 source, +0x08 SharedRef texture, +0x18 u16 flags, +0x1C color[4], +0x2C mat4, +0x6C uvTransform mat4, +0xAC float). RenderEndSkyDescription = RenderSkyDescription. RenderStarsDescription (+0x00 mesh, +0x08 block[4], +0x18 mat4, +0x58 u16 flags, +0x5A byte; sizeof [I]). RenderCubemapDescription 0xC0 (+0x00 texture, +0x08 SharedRef ctrl, +0x10 mat4 transform, +0x50 u16, +0x52 byte). RenderLegacyCubemapDescription 0x40 (+0x00 dword, +0x08 SharedRef texture, +0x18/+0x20 qwords, +0x28 float, +0x2C u16, +0x30 vec2, +0x38 float, +0x3C u16, +0x3E/+0x3F bytes). RenderCelestialBodyDescription 0x88 (+0x00, +0x08 SharedRef texture, +0x18 vec2, +0x20/+0x24 floats, +0x28 mat4, +0x68 u16, +0x6C, +0x70 byte, +0x74 qword, +0x7C, +0x80). RenderVolumetricFogDescription 0xE0 (+0x00 u16, +0x04 rows[4][4], +0x44 row, +0x54 qword; tail +0x5C..+0xDF producer-only). RenderSkyAmbientSamplesDescription 0x18 (+0x00 u16 flags, +0x08 SharedRef mSamples). RenderAtmosphereDescription 0x138 (+0x00 u16, +0x04 dword, +0x08 vec2 … +0x128; uniform mapping open [?]). RenderWeatherDescription 0x130 (+0x00 head, +0x10 block10[12], +0x40/+0x48 doubles, +0x50/+0x60/+0x70 textures, +0x80 occlusion i32, +0x84, +0x88..+0x11B vec4 uniforms FogColor..Dimensions, +0x128 u16). All offsets already static_asserted; no header edits required. Docs: src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h.
