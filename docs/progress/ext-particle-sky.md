NEXT (latest): Stars+Sky+SunMoon shared bodies at statement level (A-D). OPEN: joins 665c269/665c38a/665b624, 4de9fa0 tail, e86b370 tail, bcaba00 body; then Cubemap 6659615, EndSky/LegacyCubemap 6656b2b..6656d4d, SkyAmbientSamples 665708b, VolumetricFog 66569b1, cold 665cf64..665d7e5.
# Progress: ext-particle-sky (particle 0x67417f0, sky/clouds 0x67375a0)

## NEXT
PHASE 2 (coordinator request): decode callees. Order: 56d55e0, 5aba5c0, 6760e60, 5aba6d0, 6760710, 6760a80, 675f3b0, 675fb30, 67b5f30, 67b6130, 67450a0, 4dedd00, 66adaa0, bbd7c70, c2a8c70, 67e8020, 67e8900, 67d6d70, 6693850, 67e5f00. 66b2730 and 66a0f60 are DONE by extractors-core (docs/functions/geometry_resolvers.md). Results go to docs/functions/ext_particle_sky_callees.md. Then sky cases (stars, celestial, cubemap, endsky, volfog). Done so far: 56d55e0, 5aba5c0, 6760e60, 5aba6d0, 6760710, 6760a80, 675f3b0, 675fb30, 67450a0, 67b5f30, 67b6130, 67e8020, 67e8900, 67e5f00 (all in docs/functions/ext_particle_sky_callees.md). Remaining: 4dedd00, 66adaa0, bbd7c70, c2a8c70, 67d6d70, 6693850, 678d690(new), 9bd4a0/9bd6d0 (tls registry, optional).
Both extractor bodies fully mapped. Optional follow-up (not part of the 2 extractors): read the callee bodies marked [?]: particle 0x67450a0, 0x67b5f30, 0x67b6130, 0x67e8020, 0x67e8900, 0x66b2730, 0xbbd7c70, 0x4dedd00, 0x66adaa0, 0xc2a8c70; clouds 0x67d6d70, 0x66a0f60, 0x6693850, 0x67e5f00, 0x56d55e0, pool pushes 0x675f3b0/0x675fb30/0x6760710/0x6760a80/0x6760e60/0x5aba6d0.
Nothing half-edited. Files: docs/functions/67417f0.md, docs/functions/67375a0.md (sections "Reversed source, phases"), src/sdk/mc/deps/minecraft_renderer/framebuilder/ParticleSkyExtractors.h (not yet compiled: lead builds).

## Results
### E1b-particle (0x67417f0) - DONE (extractor body, 2411 instr: phases P0-P15 cover 0x67417f0..0x67444c7)
[V] r8 is the description, material = mode==1 ? (d+0x91 ? ParticleForwardPBR : ParticlePrepass) : Particle; defines {PointLightShading=On} when deferred && d+0x74; mutex-guarded material cache; transaction upload of the mesh blob; uniforms FogColor(d+0x6C), FogAndDistanceControl(d+0x7C), ParticleTexture(d+8), MERSTexture(d+0x18), NormalTexture(d+0x30), MERSUniforms(d+0x98 / fb+0x3F4), PBRTextureFlags; blend preset table from d+0x8C/0x8D; forward/prepass submit. CONTRADICTS old dossier: name choice inverted, guarded statics are _Init_thread statics, r8 not a variant.
Open sub-facts [?]: callee bodies listed under NEXT. Constants guarded by static_asserts in ParticleSkyExtractors.h (ParticleExtractor::DescRead/FrameRead/blendPreset/indexCount); no Sigs.json-anchored immediates added to layout_asserts.json.
### E1c-clouds (0x67375a0) - DONE (extractor body, 3262 instr: phases C0-C9 cover 0x67375a0..0x673b39a)
[V] r8 is the description (mesh +0x80, CloudColor +0x88, DistanceControl +0x9C, PrevWorld matrix +0x40, flags +0xA0); draw blocks A/B only when F+0x70==1 and push 0xC8-byte records into the thread-local pass queue pools (offsets in CloudsExtractor::Pass); F+0x75 selects the per-mesh object cache path (fb+0x1b0 map, last-key cache fb+0x240); else block D when d+0x99. Open sub-facts [?]: callee bodies under NEXT.
(Item ids are my labels; the lead maps them to the checklist ids.)

## Log
- Read brief + dossier; both disassemblies read end to end; particle phases written first, clouds C0-C9 next; header created.
