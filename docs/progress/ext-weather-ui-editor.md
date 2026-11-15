# Progress: ext-weather-ui-editor

## NEXT
Resume order: (1) Gameface 0x66ade80 from RVA 0x66aea45 (material-state checks, second switch 0x66aef04, uniform writes, pass append like weather; resolve kind->name matrix of the 0x66ae270 switch); (2) editor 0x66a1860 (descscan finds only [desc+0x0]; strings EditorBlockVolumeHull / EditorBlockVolumeWireframe, statics CameraDirection FrameTime MatColor, jump tables 0xf2bf7c8/7d8/7e8 at 0x66a2037/0x66a25ef/0x66a2d84; not started); (3) UI 0x674a3a0 (2381 instr; strings UI/Base Blit Fill Glint Sprite Text, FONT_TYPE MSDF, 16 uniform statics; description read only via [+0x0]; not started); (4) FlameBillboard DONE scoped. Template: weather dossier "Phase append" (pass append P=0x5aba5c0(ctx+0x10+0x9d0), 0xc8 entry at P+8, setVec4 by 0x5679db0, cold tails = static inits). Dump: python tools/sigs/disrange.py <lo> <hi>.

### Weather 0x6745440 - DONE (scoped; Off/On matrix resolved [V], second dossier append). Header framebuilder/WeatherDescription.h, dossier docs/functions/6745440.md
Evidence [V]: description field map +0x00..+0x128 (11 vec4 uniforms, 3 TextureBinds, variant u32 +0x84), pass vector indices P+0x780/0x8a0/0x648/0x768/0x678/0x750/0x828/0x2b8/0x3c0/+8 (entry 0xc8). No header/assert constants added.


### FlameBillboard 0x673d150 - DONE (scoped; see dossier "Second phase append"; variant-copy block 0x673e740..0x673e9a6 skeleton-level)
Not read at instruction level: uniform/texture blocks 0x673d4d8..0x673e3c2, record copy 0x673e740..0x673e9a6, second pass-entry delta (0x673efdf..0x673f483), cold tails 0x673f506..0x67403a2. Header framebuilder/FlameBillboardDescription.h (static_asserts). Fields/gates [V descscan].

### Gameface 0x66ade80 - OPEN at RVA 0x66aea45 (head 0x66ade80..0x66aea45, fields, 3 jump tables, string list recorded in dossier; kind->material matrix unresolved)
### editor 0x66a1860 - OPEN (not started; descscan + jump tables recorded in NEXT)
### UI 0x674a3a0 - OPEN (not started; descscan strings/statics in NEXT)
