# Progress: re_m1d_extractor_census (M1d unit 3: 0x66ea3d0 sub-extractor switch census)

## NEXT

Next unit: (1) Confirm rdis v2 binary exists and runs; run `rdis <exe> -c "dis 0x66ea3d0"` to enumerate all jump tables inside extractor chunk 0x66ea3d0 (0x66ea3d0..0x66f9800, size 0xF430 [V]). (2) Run `path`/`sum` to resolve case targets. (3) For each switch: record case value, target address, FrameBuilder description type + field extracted, extractor function called. (4) Produce D2-style census table in docs/functions/0x66ea3d0.md (rewrite of existing dossier). (5) Additive SDK header edits + static_asserts under src; optional docs/data/layout_asserts.json additions (unique names). (6) Write this file's final report + FULL PROPOSED BGFX_MAP ENTRY TEXT at bottom. DO NOT edit BGFX_MAP.md or RENDER_CHECKLIST.md.

Exe: `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`.
rdis: `tools\rdis\target\release\rdis.exe <exe> -c "cmd; cmd"` (v2 commands: sum/cfg/gates/path/choke/decide/uses/rw/struct/class/vslot; `help` output stale).

## Log

- 2026-11-15: session start. Read AGENT_BRIEF.md, tools/README.md, RDIS_V2_PLAN.md, group_visitors.md, existing docs/functions/66ea3d0.md (D1+ dossier; head/phases 0-5 decoded; four variant bodies NOT instruction-complete), docs/data/layout_asserts.json, docs/BGFX_MAP.md (6be/6bm/6cb sections on 0x66ea3d0), docs/progress/extractors-core.md, docs/progress/re_m1d_clones.md (NEXT listed 0x66ea3d0 sub-extractor switch census as unit 3).
- Existing knowledge [V] from prior units: 0x66ea3d0 = terrain/chunk draw builder (Item group tag 3), entered by tail-jump from Item visitor 0x6646980 tag-3 handler 0x6646d5f; rcx=builder state, rdx=per-frame context, r8=description (RenderChunkGeometryDescription / ChunkGeometryDescriptionView). Pass kind K = *(u64*)(desc+0x48). 17 pass kinds (ChunkPassKinds.h: terrain_opaque=0 .. terrain_alpha_single_side_shifts=16; portal_base=1 EndPortal; terrain_deferred_water=11 WaterPrepass; terrain_blend=10). Four variant bodies A..D (A=generic kinds, B=K==13 light_source, C=f1658 set, D=K==10 terrain_blend). Dedicated fog-alpha builders 0x670b6e0/0x6722cb0/0x67762e0/0x6792d90.

## Blockers

- None yet. Need to confirm rdis binary is built before disassembly.
