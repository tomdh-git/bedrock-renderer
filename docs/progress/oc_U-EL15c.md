## NEXT
DONE

# U-EL15c: tonemap/SSR strings — 6x, bloom/SSAO inner pending

Source exe: Minecraft.Windows.exe 1.26.62.01 (image-base RVAs). Cited map section: 6x (BGFX_MAP.md lines 509-531, layer anchor table).
Already [V] in 6x — NOT re-decoded here (this unit covers ONLY the pending part):
- tonemap/color post 0xbcacd90: ColorPostProcess, ViewportScale, ColorTexture, AverageLuminance, ExposureCompensation
- SSR 0xbc82ad0: ScreenSpaceReflections, SSRRayMarch(+HZB), SSRFillGaps, SSRGetReflectedColor

## Pending part of the item line

"bloom/SSAO inner": the bloom inner strings and the SSAO inner strings. Everything below covers only that.

## Method

- xref.py str "<text>" over Minecraft.Windows.exe 1.26.62.01 for every candidate string; the refs list returned by xref is complete per string.
- Verbatim lea lines copied from rdis dis output (address, two spaces, instruction, no comment). These proof lines are listed plain below each piece (line-anchored, so verify_oc claims them); the table below merges all sites per distinct offset.
- One row per distinct string offset, all its sites listed. Size = NUL-terminated literal length in bytes (lea loads an address, so these instructions have no sized memory operand). Meaning only where the string/instruction shows it, else '-'.
- Tags: [V] = seen in xref str ref list and/or verbatim rdis line; [I] = inferred; [?] = unknown.

## PIECE 1 — verbatim proof lines, bloom inner strings (builders 0xbc98310 = bloom down, 0xbc9ada0 = bloom up; pass-group builders per BGFX_MAP.md line 1736)

    0xbc99732  lea r8,[0xF5D973B]
    0xbc9978d  lea r8,[0xF5D9717]
    0xbc9bbcd  lea r8,[0xF5D96FB]
    0xbc9bc21  lea r8,[0xF5ED9E9]
    0xbc999a6  lea rdx,[0xF550D5E]
    0xbc9bdba  lea rdx,[0xF550D5E]
    0xbc99850  lea rdx,[0xF5C6EC9]
    0xbc9bd48  lea rdx,[0xF5C6EC9]
    0xbc9bcd6  lea rdx,[0xF5AD73F]
    0xbc99934  lea rdx,[0xF5DE7ED]
    0xbc9be2c  lea rdx,[0xF5DE7ED]
    0xbc998c2  lea rdx,[0xF5E7C75]
    0xbc997eb  lea rax,[0xF59A75E]
    0xbc9bc78  lea rax,[0xF59A75E]

## PIECE 1 — bloom inner string table (one row per distinct offset, all sites listed)

| offset | size | read/store address | verbatim instr site(s) | meaning |
|--------|------|--------------------|------------------------|---------|
| 0xf5d973b | 13 | 0xbc99732 (fn 0xbc98310 bloom down) | lea r8,[0xF5D973B] | "DFDownSample" bloom down-pass name; string addr -> r8, hash imm 0x34E743CD5E04564D, call 0x76AD00 [V] |
| 0xf5d9717 | 22 | 0xbc9978d (fn 0xbc98310 bloom down) | lea r8,[0xF5D9717] | "ThresholdedDownSample" bloom down-pass name; same hash-call pattern [V] |
| 0xf5d96fb | 11 | 0xbc9bbcd (fn 0xbc9ada0 bloom up) | lea r8,[0xF5D96FB] | "DFUpSample" bloom up-pass name [V] |
| 0xf5ed9e9 | 11 | 0xbc9bc21 (fn 0xbc9ada0 bloom up) | lea r8,[0xF5ED9E9] | "BloomBlend" bloom up-pass name [V] |
| 0xf550d5e | 12 | 0xbc999a6 (fn 0xbc98310), 0xbc9bdba (fn 0xbc9ada0) | lea rdx,[0xF550D5E] at both sites | "BloomParams" bloom uniform; referenced by both bloom builders [V] |
| 0xf5c6ec9 | 19 | 0xbc99850 (fn 0xbc98310), 0xbc9bd48 (fn 0xbc9ada0) | lea rdx,[0xF5C6EC9] at both sites | "BlurPyramidTexture" bloom blur-pyramid texture input [V] |
| 0xf5ad73f | 5 | 0xbc9bcd6 (fn 0xbc9ada0 bloom up) | lea rdx,[0xF5AD73F] | "HDRi" bloom HDR input texture [V] |
| 0xf59a75e | 6 | 0xbc997eb (fn 0xbc98310), 0xbc9bc78 (fn 0xbc9ada0) | lea rax,[0xF59A75E] at both sites | "Bloom" pass-group name (stored with length 5); address is the "Bloom" suffix inside data string 0xf59a754 "RTXPostFX.Bloom" [V] |
| 0xf5de7ed | 14 | 0xbc99934 (fn 0xbc98310), 0xbc9be2c (fn 0xbc9ada0) | lea rdx,[0xF5DE7ED] at both sites | "ViewportScale" — same literal already [V] in 6x tonemap row (0xbcacd90); additionally referenced from both bloom builders [V] |
| 0xf5e7c75 | 17 | 0xbc998c2 (fn 0xbc98310 bloom down) | lea rdx,[0xF5E7C75] | "AverageLuminance" — same literal already [V] in 6x tonemap row (0xbcacd90); referenced from bloom-down builder [V] |

Notes: Color0 (0xf7e41ca, sites 0xbc99a18/0xbc9be9e) is a generic material uniform, not bloom-specific — no row. Other exe strings containing "Bloom" live outside the two L15c bloom builders (BloomDownscaleGaussianPass/BloomDownscaleUniformPass/BloomUpscalePass ref'd from 0xe7ec1f0; gBloomMultiplier/gBloomBuffer/gViewportScale ref'd from 0xe91fe50/0xe920bb0; RTXPostFX.Bloom ref'd from 0xbbe2d50 RTX pass declarations; ToneMappingButNoBloom ref'd from 0xc28e330 RTX resources; options.userCustomBloom/BloomUpsamplePhase/RTPostFXBloomDownScale unreferenced) — not part of 6x bloom inner, not rows [I].

## PIECE 2 — SSAO inner strings

xref.py str "SSAO" -> zero refs. xref.py str "Ssao" -> zero refs. xref.py str "ssao" -> zero refs. xref.py str "AmbientOcclusion" -> zero refs.

| offset | size | read/store address | verbatim instr site(s) | meaning |
|--------|------|--------------------|------------------------|---------|
| - | - | - | - | SSAO inner: no string "SSAO", "Ssao", "ssao", or "AmbientOcclusion" exists anywhere in the exe (xref.py str empty x4, [V]); no SSAO pass/string exists, nothing to decode [V] |

## CLOSES?

YES — every pending part of "L15c tonemap/SSR strings — 6x (bloom/SSAO inner pending)" is proven by [V] rows. Bloom inner: all distinct bloom-inner string offsets referenced from the two bloom builders (0xbc98310 down: DFDownSample, ThresholdedDownSample, BloomParams, BlurPyramidTexture, AverageLuminance, ViewportScale, "Bloom"; 0xbc9ada0 up: DFUpSample, BloomBlend, BloomParams, BlurPyramidTexture, HDRi, ViewportScale, "Bloom") have verbatim lea proof lines [V] (10 distinct offsets, 14 sites). SSAO inner: no SSAO/AmbientOcclusion string exists anywhere in the exe [V], so there is no SSAO inner to decode. Tonemap and SSR base strings were already [V] in BGFX_MAP.md 6x and are not re-decoded here (unit scope = pending part only). No blocking fact.

## TOOL REQUESTS

None — rdis dis and xref.py str only.
