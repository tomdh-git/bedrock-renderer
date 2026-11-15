# Progress: ext-particle-sky (particle 0x67417f0, sky/clouds 0x67375a0)

## NEXT
Clouds 0x67375a0: C0-C5 written (0x67375a0..0x67393d0). RESUME AT 0x67393d0 (disassembly dump line ~1370; command: disrange 67375a0 673b3a0).
Particle 0x67417f0: all phases P0..P15 written to docs/functions/67417f0.md ("Reversed source, phases"), header src/sdk/mc/deps/minecraft_renderer/framebuilder/ParticleSkyExtractors.h created (constexpr + static_asserts, includes blend preset table, index-count rule, material name rule).
Next unit: clouds 0x67375a0 (3262 instr, 0x67375a0..0x6741... size 0x3dfb). Not started: `export PYTHONUTF8=1; python tools/sigs/disrange.py 67375a0 673b39b` then read in 400-line chunks; reuse the idioms ID-SP/ID-STR/ID-STATIC/ID-FNV/ID-MAPFIND/material cache lookup documented in docs/functions/67417f0.md (P3-P7 are the same cache-load sequence).
Particle OPEN reason: bodies of callees 0x67450a0, 0x67b5f30, 0x67b6130, 0x67e8020, 0x67e8900, 0x66b2730, 0xbbd7c70, 0x4dedd00, 0x66adaa0, 0xc2a8c70 are [?] (other functions; the extractor's own 2411 instructions are all mapped).

## Log
- (start) Read AGENT_BRIEF, extractors-dossiers; particle disassembly dumped and read end to end; no edits yet to src/.
- particle phases P0-P15 written (dossier + header). CONTRADICTS earlier dossier: r8 is the description, name choice inverted (ForwardPBR when mode==1 && d+0x91), guarded statics are _Init_thread statics not profiler zones.
