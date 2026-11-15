# L14a / L14c / L14b: UI visitor, font loaders, text renderer leads (1.26.62.01)
Tags [V] disassembly/strings, [I] inferred, [?] unknown.

## UI visitor 0x6664a00 (5 cases, table 0xF2BF468) [V, docs/functions/group_visitors.md]
tag0 Gameface -> jmp 0x66ade80; tag1 HudIcon 0x6664d51 (ResourceCache::get 0x675e440); tag2 UIMesh 0x6664bd6 (inline: reads description r9 +0x18, +0x30, +0x58 (cmp 2), +0x60, +0x68, +0x70 float, bytes +0x80..+0x85, +0x88 block); tag3 UIText 0x6664c83 -> extractor 0x674a3a0 (cite docs/functions/674a3a0.md, owned by weather-ui-editor agent); tag4 UIImGui 0x6664aab: material "Debug/ImGui" (string 0x6664ae9) fetched by 0x675e440 (call 0x6664b28), draws through two vcalls (0x6664bb1/0x6664bcb). Strings in the visitor: "Debug/ImGui", "UI/Blit", "ImGuiProj".
## ScreenRenderer
Not located by name/strings; no ScreenRenderer string in the exe.

## Font loading (L14c) [V strings, [I] roles]
- 0x4fb3870 (refs "_ttf", ".png", ".info"): builds the font-texture path for a TrueType font: name + "_ttf" + ".png" and ".info" sidecar. 0x4fbe0c0 (refs "_ttfmsdf", ".png", ".info"): same for the MSDF variant. So the glyph atlases are pre-generated PNG + .info files per font (the two FONT_TYPE values MSDF / TrueType), not rasterised at runtime [I].
- 0x4fb2900 and 0x4fbdcd0: font-file extension tests (.ttf .otf, and .ttc .otc in 0x4fbdcd0).
- Callers: of 0x4fb3870/0x4fbe0c0: 0x4fb2900, 0x4fbbea0, 0x4fbbf20, 0x4fbcab0, 0x4fc3930, 0x4fc3db0, 0x4fe0e10 (font manager functions) [V caller list].
- Shader side: GlyphTexture bound at 0x674dca3, GlyphHeight at 0x674e06a, "UI/Text" at 0x674a59e/0x674d880, all inside 0x674a3a0.
- "glyph-dict"/"sfnt"/"postscript-cmaps" are a linked font-parser library, not the atlas.

## cohtml (L14b) leads: see materials-visuals.md (0x4fc9650 wrapper).
