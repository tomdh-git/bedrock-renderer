# Plan: delegating the render-map checklist to opencode agents

Goal unchanged: close docs/RENDER_CHECKLIST.md. Claude orchestrates and verifies; opencode agents (Kilo gateway, free) do bulk static analysis. Every unit below is mechanical and bounded: transcribe or locate, with evidence. Judgement (what is true, what to tick) stays with Claude.

## Rules of the loop
1. One unit per opencode task via `oc_delegate_task` (directory C:\Users\Atomi\Desktop\BlueySenseV2, agent `coder`). Instructions = "Read docs/OPENCODE_BRIEF.md completely, then do unit <ID> below exactly. Write only docs/progress/oc_<ID>.md." plus the unit text pasted verbatim.
2. Each unit writes ONE file, docs/progress/oc_<ID>.md (NEXT block on top). No two units touch the same file, so any number may run in parallel (limit: 4 at once to stay under free-tier rate limits).
3. Rate limit / `failed` outcome with partial file: re-delegate the same unit with "continue from the NEXT block of docs/progress/oc_<ID>.md". Rotate Kilo account (kilo_switch_account) only when failures repeat.
4. Claude verification (mandatory before anything is used): for each returned file, spot-check at least 5 load-bearing claims per 100 lines against the exe with tools/sigs/disrange.py or rdis (RVA exists, instruction matches, offset matches, callee identity). Any [V] claim that fails => the whole unit is REJECTED (re-run with the failing claims listed), others accepted. Record the verdict in docs/progress/oc_verification.md (unit, verdict, checks run, errors).
5. Accepted units are folded into docs/BGFX_MAP.md section 6ip+ and docs/functions/<rva>.md by Claude (or the merge agent). Checklist ticks only when ALL parts of an item are accepted; otherwise the blocking fact is written next to the item.

## Unit queue (priority order; each is "transcribe range into phases per the brief, with callees and struct fields")
Chunk extractor 0x66ea3d0 (E4/L5g). Context: docs/functions/66ea3d0.md (read it, body A decoded to 0x66ed973), docs/functions/66d9af0_builders.md, ChunkPassKinds.h.
- U-E4-A2: body A remainder 0x66ed987..0x66ef28d.
- U-E4-B: body B 0x66ef308..0x66f2817 (similar to A: note differences from A phase by phase).
- U-E4-C: body C 0x66f2820..0x66f4f5a.
- U-E4-D: body D 0x66f4fcb..0x66f6e36.
- U-E4-F1: builder 0x67762e0 first 800 instructions; U-E4-F2 next 800; continue in 800-instruction units (create ids F3.. as needed). Same for builders 0x670b6e0 (U-E4-G*) and 0x6722cb0 (U-E4-H*); first diff the three builders' mnemonic sequences to find the shared template and say which ranges are identical.
Other extractors:
- U-GF: Gameface 0x66ade80: the Data_VS/Data_PS/Viewport writes 0x66af0c0..0x66af263 and pass-entry words 0x66af72c..0x66afe7a (see docs/functions/66ade80.md).
- U-UI5: UI extractor 0x674a3a0 from 0x674b4d9: the kind switch (jump table 0x674b550), materials Blit/Base/Sprite/Fill, cold tails (see docs/functions/674a3a0.md).
- U-ED: editor extractor callees 0x66a6190, 0x66a6060, 0x66a6470, 0x66a65b0, 0x67d3850, 0x67d2f80 (see docs/functions/66a1860.md).
- U-IH: ItemInHand extractor 0x6698e30 ranges 0x669c35f..0x669c8f9 and 0x669be56..0x669bef8 (see docs/functions/6698e30.md); callees 0x67d14e0, 0x673cc80.
- U-NT: nametag producer 0x11276b0 ranges 0x11278c5..0x1127b06, 0x1127c35..0x1127d23, 0x11283d3..0x11285f4, 0x112888e..0x1128a40 (docs/functions/11276b0.md).
- U-SK1: sky visitor 0x66560f0, Stars joins 0x665c269, 0x665c38a, 0x665b624 and cold 0x665cf64..0x665d7e5 (docs/functions/ext_particle_sky_callees.md).
- U-SK2: sky Cubemap case 0x6659615 and EndSky/LegacyCubemap 0x6656b2b..0x6656d4d.
- U-SK3: sky SkyAmbientSamples 0x665708b and VolumetricFog 0x66569b1.
- U-BA: bodyActor 0x66d0a00 (size 0x738b) in 600-instruction units (ids U-BA1..).
- U-FONT: 0x4fb3870 and its callers: find where the glyph .info sidecar is parsed and which struct receives glyph advances (L14c).
- U-L8: texture path above 0x67ceb40/0x67ceed0: who builds the image object (PNG/TGA decode, ClientTexture) and atlas stitcher callers 0x95ed00, 0x4e198d0, 0x4e1cbb0 (L8a/L8b).
- U-HELP: undecoded helpers: 0x4de9fa0 tail 0x4dea2b4.., 0xe86b370 tail 0xe86b43a.., 0xbcaba00 body, 0xbbd7f70, 0x66a6190 (shared by sky and editor).
- U-PASS: DrawItem pool consumer: callers of 0x5aba5c0 (returns the thread-local pass object): find its vtable/type and the function that drains the pool vectors at pass+0x648/0x750/0x768/0x780/0x8a0 (E2 blocker, BatchActor pool tags).
Verification-type units (run after the above; they re-derive, not transcribe):
- U-VER-n: take one accepted dossier of another agent and re-derive 5 claims; report mismatches.

## Prompt template (paste into oc_delegate_task.instructions)
"Read C:\Users\Atomi\Desktop\BlueySenseV2\docs\OPENCODE_BRIEF.md completely and obey it. Your unit is <ID>: <unit text>. Output file: docs/progress/oc_<ID>.md only (NEXT block at top, append after every phase). Do not edit any other file. If you hit a rate limit, your progress file is the handoff; stop cleanly."

## Fallback
If the bridge or opencode misbehaves: fix the bridge (C:\Users\Atomi\opencode-mcp-bridge), restart opencode, retry once; otherwise continue with Claude subagents using docs/AGENT_BRIEF.md (same unit texts).
