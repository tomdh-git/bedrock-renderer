## NEXT
step 2

# UNIT U-EI5c: Text/font SDF glyph uniforms + FONT_TYPE permutation; GLYPH ATLAS (pending part)

Goal: close the remaining pending part of checklist item I5c — the glyph atlas: where the GlyphTexture uniform value comes from, which object field holds the texture handle/name, who writes that field, the glyph texture name pattern strings in .rdata, and whether the load path goes through the pack texture loader (texload 0x58a1310, per docs/BGFX_MAP.md).

Inherited proven facts (NOT re-proven here):
- SDF glyph uniforms GlyphTexture/GlyphHeight/GlyphSmoothRadius registered in 0x674a3a0 at 0x674dca3 / 0x674e06a / 0x674ddbe via FNV hash 0x79580 + table 0x73150 (from oc_U-I5c.md, verify_oc 97/97).
- FONT_TYPE + MSDF permutation via 0xF2EA00 at 0x674d2bf/0x674d2c6 / 0x674d6be/0x674d6c5 in 0x674a3a0 (from oc_U-I5c.md).
- GlyphTexture is bound BY NAME: 16-byte SSO texture NAME string at object+0x38 (object = [rbp+0xE80] in 0x674a3a0), via 0x674aa91 -> 0x5679DB0 -> memcpy thunk 0xEEC6EC0 (oc_U-EI5c.md r2, 12/12 [V]).
- 0xEEC7570 at 0x4f78966 is an import thunk (strlen-style with rcx = C string), NOT a texture-handle fetch (orchestrator hint, verified fact).
- No "GlyphAtlas" or "FontTexture" string in the binary (oc_U-I5c.md).

Pending (to resolve now): writer of object+0x38 name; glyph texture name pattern strings; pack-loader path (texload 0x58a1310).
