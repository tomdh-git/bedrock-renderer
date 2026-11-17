# Close order (2026-11-16). Goal: 60-70% done today (209 -> ~255-295 of 421).
Rule: mirror pairs tick together (one real result closes 2-4 lines). Items count only when instruction-complete + verify_oc clean.

## Tier 1 (listing + clone already on disk; transcription work for units, review by me)
- D6c = L4p = R1/R11(part): Clouds (lightgame_clouds_clone_53e88a0), Weather (lightgame_weather_clone_5ad5800), Atmosphere (sky_atmosphere_6656d4b) -> units U-D6cA/B/C
- D9c = L4w = R6/R7: GameplayMetadata, ServerOverride, EditorHighlight -> U-D9cA (+ one more for EditorHighlight lightgame_edhighlight_clone_4c8a5b0)
- D10 = L4x = R5: editor tags 1-4 / 5-7 -> U-D10a/b
- D8 = L4t = L14d = R10: UIMesh/HudIcon done (oc_U-D8d.md); Gameface extractor-call map left
- L4s = R3/R9: FullscreenEffect, BlitFlipbook (effect_blit_*, effect_fullscreen_*)
- L5b/L5c/L5f = R2/R8: Item tags (item_visitor_6646980_664fe00.txt)
- R4: AimAssistHighlight tail read; R13: layout asserts for descriptions (generated from verified tables)

## Tier 2 (tool output + short note; units with precomputed bundles)
- C4a=L3f, C4b=L3g (field tables done; add sizes), L3k (0x6632bf0 flush), L3d, L1p/L1q/L1t (Context offsets), L2l, L2o
- I5c=L14c, I5d, F1b=L6b, F2b=L6d, G4a=L7e, G4b=L7f, L7c=G2, H4=L9f

## Tier 3 (design/doc items I can verify myself from existing files; tick on evidence)
- J2=L18b=P3a (Sigs.json startup check exists), A13=L1z (headers), O2a/O2b/O3a/O3b, N4a/N4b/M4c, K-P7/K-P9 (existing convention), P2a/P2b/P1d (hooks exist)

## Tier 4 (hard / RTX / needs live game): B10*, L16*, I7, L17*, Q*, N1*-N3*, M3*, L8*, L10c, L11c/d

## Order (user, 2026-11-16)
1. easy single items (one unit each) 2. easy multi-step items ascending by step count 3. then by difficulty (my call)
