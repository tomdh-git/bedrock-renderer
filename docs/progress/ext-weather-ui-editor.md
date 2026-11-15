# Progress: ext-weather-ui-editor

## NEXT
Resume order: (1) Gameface DONE scoped (header GamefaceDescription.h); (2) editor: transcribe callee bodies 0x66a6190, 0x66a6060, 0x66a6470, 0x66a65b0, 0x67d3850 and 0x67d2f80 (pass append helper, 321 instr); (3) UI 0x674a3a0 from RVA 0x674b4d9 (kind switch 0x674b550 -> cases 0x674b559/0x674b9b2/0x674b71a/0x674b85d, materials Blit/Base/Sprite/Fill, cold tails 0x674ce4f..0x674d15e); then UI header; (3b) Flame record-copy block 0x673e740..0x673e9a6 line by line; (3c) Gameface Data_VS/Data_PS/Viewport writes 0x66af0c0..0x66af263 line by line; Template: weather dossier "Phase append" (pass append P=0x5aba5c0(ctx+0x10+0x9d0), 0xc8 entry at P+8, setVec4 by 0x5679db0, cold tails = static inits). Dump: python tools/sigs/disrange.py <lo> <hi>.

### Weather 0x6745440 - DONE (scoped; Off/On matrix resolved [V], second dossier append). Header framebuilder/WeatherDescription.h, dossier docs/functions/6745440.md
Evidence [V]: description field map +0x00..+0x128 (11 vec4 uniforms, 3 TextureBinds, variant u32 +0x84), pass vector indices P+0x780/0x8a0/0x648/0x768/0x678/0x750/0x828/0x2b8/0x3c0/+8 (entry 0xc8). No header/assert constants added.


### FlameBillboard 0x673d150 - DONE (scoped; see dossier "Second phase append"; variant-copy block 0x673e740..0x673e9a6 skeleton-level)
Not read at instruction level: uniform/texture blocks 0x673d4d8..0x673e3c2, record copy 0x673e740..0x673e9a6, second pass-entry delta (0x673efdf..0x673f483), cold tails 0x673f506..0x67403a2. Header framebuilder/FlameBillboardDescription.h (static_asserts). Fields/gates [V descscan].

### Gameface 0x66ade80 - DONE scoped (third append closed blend pairs, record, entry words; header GamefaceDescription.h) [older note: whole function mapped at call/store level; kind->material matrix RESOLVED [V]: 0 Standard,1 StandardRare,2 Stencil,3 StencilRare,4 StencilPath,5 ClearQuad,6 Renoir,7 Path,8 TexturesWithColorMix. Remaining: enum pairs 4..0xa, entry word displacements.)
### editor 0x66a1860 - OPEN (all three draw bodies mapped at call/store level in the second append; callee bodies 0x66a6190/0x66a6060/0x66a6470/0x66a65b0/0x67d3850 and per-form record words not transcribed; header EditorBlockVolumeDescription.h)
### UI 0x674a3a0 - OPEN at RVA 0x674b4d9 (signature + phases 1-4 mapped at call/store level in the dossier second append; phase 5 kind switch 0x674b550 and the rest not transcribed; no header yet)
