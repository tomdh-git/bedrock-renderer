# Tick plan (2026-11-15)

State: 131 [x], 287 [ ] lines = ~98 unique core items (sections A-J) + ~100 L-mirrors of them + ~90 program items (K, M-R: dossiers/acceptance tests/integration/rewrite).
Why nothing ticks: ticks need (1) exact transcription [mostly done], (2) a synthesis step (dossier + struct header with asserts) [NOT yet scheduled], (3) verification. I have been spending all effort on (1).

## Tier 1 - transcription done or finishing; synthesis next (ticks within this loop)
- E4 / L5g chunk extractor 0x66ea3d0: bodies A-D (units E4X-*), builders 0x670b6e0/0x67762e0/0x6722cb0 (accepted), bodyActor 0x66d0a00 (accepted). Needs: docs/functions/66ea3d0.md final + ChunkPassKinds.h asserts. Tick E4+L5g.
- D7c / L4s FullscreenEffect: tables 475..5869 done; needs field-layout synthesis -> EffectDescriptions.h. Tick D7c+L4s.
- D7b / L4r Shadow: needs instruction-complete listing unit (one unit).
## Tier 2 - static, needs one unit each (transcribe + synthesize)
D5b-D5i descriptions, D6c, D8, D9a, D9c, D10, E1b-E1d, E2, E3, E7, G2, G4a, H1b, I4b, L8a-d.
## Tier 3 - blocked on live capture (22 items mention live; also A12*, B10*, C7a)
Proposal: split each into static part (tickable) + new open line "(live) ..." so progress shows. NEEDS USER OK (house rule: partial != done).
## Tier 4 - program sections K, M-R (dossier definition-of-done, integration, rewrite). Not closable by transcription; do after A-J.

## 2026-11-15 evening status (live + static findings)
- jt.py works (tag 0..7 heads of the light visitor: 0x6640de8, 0x66415b0, 0x6640f1b, 0x66410a0, 0x6640ec1, 0x66417af, 0x664187d, 0x6641524).
- Live light-visitor tags seen: 0, 1, 2, 5 (tags 3,4,6,7 absent in a 10 min run). Tag 1 live = big object with fog/atmosphere colour block at +0x88..+0xFF (same values as sky tag 0/5) -> candidate LightDirectional (thin clone 0x5370960 inserts tag byte 1, [V] listing line 27). Tag 0 head reads only +0x00 (8B), +0x08 f32, +0x10 f32, +0x14 u16 (small struct).
- Clouds clone 0x53e88a0 / Weather clone 0x5ad5800 / Weather extractor 0x6745440 / Clouds handler 0x67375a0: ZERO hits in 60 s (current scene), sky visitor never saw tags 1/9 in 600 s -> they are not submitted in this scene (dimension/world?); need an Overworld-day re-run.
- Editor visitor/extractor, Gameface extractor: zero hits (editor/Gameface UI not open).
- Agents: free-tier units stall on interpretive work (LV1 fake success, CW failed, LV2/D9a/D6c/D9c stalled); mechanical units work. Use scripts (stores.py, casewalk.py, jt.py, union.py) and do interpretation in the orchestrator.
