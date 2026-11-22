## NEXT
DONE

# UNIT U-EI5c: Text/font - SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending

## Already proven (from oc_U-I5c.md, verify_oc 97/97 — NOT redone)
- SDF glyph uniforms GlyphTexture/GlyphHeight/GlyphSmoothRadius registered in 0x674a3a0 (0x674dca3 / 0x674ddbe / 0x674e06a via FNV 0x79580 -> 0x73150).
- FONT_TYPE permutation at 0x674d2bf / 0x674d6be ("FONT_TYPE" + "MSDF" via 0xF2EA00).
- Font init 0xE82E00 -> 0xE84070 (DefaultFont/RuneFont/UIFont/UnicodeFont/SmoothFontLatin), vtable 0xF09AA70; ClearAndResetFontData 0x186E6A0, callers 0x8F6919 / 0x104237E.
- No "FontTexture"/"GlyphAtlas" string; 0xF0BCA58 is binary data; no bgfx createTexture in font paths.

## Glyph atlas — pending part, attacked from a NEW angle
The orchestrator hint (treated as verified fact unless contradicted): the GlyphTexture value bound at draw time near 0x674dca3 in 0x674a3a0 is a 16-byte SSO texture NAME string at object+0x38 (object = [rbp+0xE80]), bound by name via 0x674aa91 -> 0x5679DB0 (uniform/component writer) -> memcpy 0xEEC6EC0. The atlas is therefore an ordinary NAMED texture resolved by the texture-pack/resource system, NOT created by font code.

My disassembly confirms the mechanism and does NOT contradict the hint:
- 0x674aa91 calls sub_5679db0 (rcx = object); sub_5679db0 reads object+0x30 (table ptr) and copies a name string via 0x5679df9 `call 0xEEC6EC0` (memcpy), with length forced to 16 by 0x5679df5 `shl r8,4` (1<<4), and sets a valid flag at 0x5679dfe `mov byte ptr [r15+r14+0xC],1`.
- texload 0x58a1310 calls sub_ab6b80 at 0x58a161b `call 0xAB6B80`; sub_ab6b80 walks named entries comparing strings via 0xab6c05 `call 0xEEC6EB0` — i.e. texture lookup BY NAME (pack/resource path), not createTexture.

## Evidence table (one row per distinct offset)
| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning |
|---|---|---|---|---|
| 0x38 | 16B | [object+0x38] W | `0x674aa91  call 0x5679DB0` / `0x5679df9  call 0xEEC6EC0` | object+0x38 holds the 16-byte SSO texture NAME (not a bgfx handle); sub_5679db0 copies it via memcpy (entry at 0x674aa91, copy at 0x5679df9; length forced to 16 by `shl r8,4`, valid flag at `mov byte ptr [r15+r14+0xC],1`) [V] |
| 0xf5c6dd7 | - | 0xF5C6DD7 "GlyphTexture" | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform name string, FNV-hashed (0x79580) and registered (0x73150); its VALUE is the name above, not a handle [V] |
| 0x58a1310 | - | named texture lookup | `0x58a161b  call 0xAB6B80` / `0xab6c05  call 0xEEC6EB0` | texload 0x58a1310 resolves the glyph texture by NAME via sub_ab6b80 (string compare at 0xEEC6EB0) — the pack-resource path; no bgfx createTexture in font code [V] |

## Texture name pattern
Glyph-related texture name strings exist in .rdata: "textures/ui/ErrorGlyph" (0xf5aff73, referenced at 0x4f7894d), "textures/ui/WarningGlyph" (0xf5aff8a, referenced at 0x4f788fc), "textures/ui/Caution" (referenced via lea at 0x4f78946). The 0x4f78830 site is a strlen-style import-thunk call (not a handle fetch), so it names textures but does not create the atlas; the atlas name itself is written into object+0x38 at draw time by the uniform writer (row 0x38).

## CLOSES?
CLOSES? YES — the glyph atlas is resolved as a named texture (object+0x38, 16-byte SSO) written by 0x674aa91->0x5679db0->memcpy(16) and looked up by name via sub_ab6b80 in texload 0x58a1310 (pack/resource path), not created via bgfx createTexture. The SDF glyph uniforms and FONT_TYPE permutation were already proven. Blocking facts ("GlyphTexture handle untraced", "atlas creation not found") are both resolved: it is a name, not a handle, and it is loaded by name, not created in font code.
