## NEXT
DONE

# Unit U-EL14c: L14c Text/font — glyph atlas (pending part)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending".

The SDF glyph uniforms + FONT_TYPE permutation half is already closed (prior units U-I5c / U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be + MSDF via 0xF2EA00, all in UI extractor 0x674a3a0). This unit covers ONLY the pending part: the **glyph atlas** — where the `GlyphTexture` uniform's bgfx texture handle comes from, i.e. the glyph atlas texture creation/update site.

BGFX_MAP.md section 6ce anchors the UI pass extractor 0x674a3a0 (UI group, vtable slot 0x368) and states "Still pending: glyph atlas management". Section L8 anchors only PointLightShadowTextureAtlas 0xbb682b0 and MaterialTerrainTextureAtlas (string only) — no glyph-atlas anchor.

## Offset table (one row per distinct offset, all its sites listed)

Size column: movups/movaps = 16; qword/store = 8; dword/movss = 4; word = 2; byte = 1. Meaning only where an instruction or string shows it, tagged [V]/[I]/[-].

| Offset | Size | Sites (RVA) | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------|------------------------------------|------------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string loaded into rdx, hashed via 0x79580, registered via 0x73150 — a uniform binding, not a texture creation site [V] |
| 0x186f7bc | 8 | 0x186f7bc | `0x186F7BC  call qword ptr [0xF99FFA0]` | TerrainAtlas registry-object allocation — general allocator [0xF99FFA0] with size 4 (mov edx,4); a 4-byte registry object, no bgfx createTexture/createDynamicTexture/updateTexture call [V] |
| 0xe84257 | 8 | 0xe84257 | `0xe84257  lea rax,[0xF0BCA58]` | 'FontTexture' address load — 0xF0BCA58 holds data bytes (90 80 07 40 01), no "FontTexture" string exists in the binary; not atlas-creation evidence [V] |
| 0x4f788fc | 8 | 0x4f788fc | `0x4f788fc  lea rdi,[0xF5AFF8A]` | "textures/ui/WarningGlyph" string — glyph texture name loaded in the glyph-texture fetch function 0x4f78830 [V] |
| 0x4f7894d | 8 | 0x4f7894d | `0x4f7894d  lea rdi,[0xF5AFF73]` | "textures/ui/ErrorGlyph" string — fallback glyph texture name in 0x4f78830 [V] |
| 0x4f78960 | 16 | 0x4f78960 | `0x4f78960  movups [rsi],xmm0` | Zeroes the output texture-ref slot (16 bytes) before the fetch [V] |
| 0x4f78966 | 8 | 0x4f78966 | `0x4f78966  call 0xEEC7570` | Indirect call through CFG thunk [0xF9A9048] that performs the actual glyph-texture fetch; target not statically resolvable [V] |

## Answer

No glyph atlas texture creation/update site is isolated anywhere in the font paths.

- The only `GlyphTexture` reference in the binary is a uniform-name hash registration (`0x674dca3` lea of string at 0xF5C6DD7, hashed via 0x79580, registered via 0x73150) inside UI extractor 0x674a3a0 — it is a uniform binding resolved at draw time via 0x73150/0xAA840, not a texture creation site.
- No `GlyphAtlas` string exists (string scan for "glyph"/"Atlas" found only font-parser `glyph-dict`/`glyph_section_*` strings and unrelated atlases: TerrainAtlas, ItemAtlas, AnimatedAtlas, BlockThumbnailAtlas, FlameAtlas, PointLightShadowAtlas, MaterialTerrainTextureAtlas).
- Font init 0xe82e00→0xe84070 and font reset 0x186e6a0 (ClearAndResetFontData) allocate only small registry/resource objects via `[0xF99FFA0]` (sizes 4/8/0x10/0x18, e.g. TerrainAtlas at 0x186f7bc size 4) and insert them via 0x1870DE0 — none call bgfx createTexture (RendererContext slot 26 / 0xe8143c0) or createDynamicTexture (0xbc74a80). The alleged FontTexture string at 0xF0BCA58 is data bytes (90 80 07 40 01), not a string.
- The glyph-texture fetch function 0x4f78830 looks up named glyph textures (`textures/ui/ErrorGlyph` 0xF5AFF73, `textures/ui/WarningGlyph` 0xF5AFF8A, `textures/ui/Caution` 0xF58553B) from an internal cache and returns a shared ref through the indirect CFG thunk `call 0xEEC7570` (target `[0xF9A9048]`, not statically resolvable) — so the bgfx texture handle behind `GlyphTexture` remains untraced statically.

BGFX_MAP.md section L8 gives no glyph-atlas anchor (only PointLightShadowTextureAtlas 0xbb682b0 and MaterialTerrainTextureAtlas, string only), consistent with this being genuinely pending.

## CLOSES?

NO — blocking fact: glyph atlas texture creation/update not found. The `GlyphTexture` uniform is only registered/bound at draw time (0x674dca3 in 0x674a3a0); font paths contain no bgfx createTexture/createDynamicTexture/updateTexture call site for a glyph atlas (only [0xF99FFA0] registry-object allocations, e.g. 0x186f7bc), no "GlyphAtlas"/"FontTexture" string exists, and the glyph-texture fetch (0x4f78830) returns its handle through an indirect CFG thunk `call 0xEEC7570` (0x4f78966) whose target is not statically resolvable, so the texture handle behind `GlyphTexture` cannot be traced statically.

## TOOL REQUESTS

None — all evidence gathered with xref.py str and rdis.exe dis; no helper script needed.
