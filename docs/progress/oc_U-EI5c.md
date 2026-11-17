## NEXT
DONE

# UNIT U-EI5c: Text/font — close I5c pending part: glyph atlas texture creation/update

Proven already in U-I5c (verify_oc 97/97, not re-run here): SDF glyph uniforms GlyphTexture/GlyphHeight/GlyphSmoothRadius registered in extractor 0x674a3a0 (0x674dca3 / 0x674ddbe / 0x674e06a) and FONT_TYPE permutation via 0xF2EA00 at 0x674d2bf/0x674d6be.

Pending part of I5c: glyph atlas texture creation/update — the item line states it "not isolated" and that the 0xF0BCA58 'FontTexture' claim was wrong (data bytes). This note isolates what can be proven from the precomputed input data (docs/progress/oc_U-I5c.md) and docs/BGFX_MAP.md section L8 (textures/atlases/resources): L8 anchors only PointLightShadowTextureAtlas 0xbb682b0 and MaterialTerrainTextureAtlas (string only); no glyph-atlas texture anchor exists there.

## Evidence (one row per distinct offset; verbatim lines copied from docs/progress/oc_U-I5c.md)

    0x674dca3  lea rdx,[0xF5C6DD7]
| GlyphTexture uniform registration — string "GlyphTexture" at 0xF5C6DD7 loaded into rdx and hashed via 0x79580; resolved at draw time via 0x73150/0xAA840; a uniform binding, not a texture creation site | 0x674dca3 | 8 | `0x674dca3  lea rdx,[0xF5C6DD7]` | [V] |

    0x186F7BC  call qword ptr [0xF99FFA0]
| TerrainAtlas registry-object allocation — general allocator [0xF99FFA0] with size 4 (mov edx,4); a 4-byte object, no bgfx createTexture/createDynamicTexture/updateTexture call | 0x186f7bc | 8 | `0x186F7BC  call qword ptr [0xF99FFA0]` | [V] |

    0x186F952  call qword ptr [0xF99FFA0]
| AnimatedAtlas registry-object allocation — allocator [0xF99FFA0] with size 0x10 (mov edx,0x10); registry object, no texture creation call | 0x186f952 | 8 | `0x186F952  call qword ptr [0xF99FFA0]` | [V] |

    0xe84257  lea rax,[0xF0BCA58]
| 'FontTexture' address load — claimed FontTexture string at 0xF0BCA58; rvastr.py shows data bytes 90 80 07 40 01 at 0xF0BCA58, no "FontTexture" string exists in the binary; not atlas-creation evidence | 0xe84257 | 8 | `0xe84257  lea rax,[0xF0BCA58]` | [V] |

    0x186FAEC  call qword ptr [0xF99FFA0]
| BlockGraphics registry-object allocation — allocator [0xF99FFA0] with size 8 (mov edx,8); registry object, no texture creation call | 0x186faec | 8 | `0x186FAEC  call qword ptr [0xF99FFA0]` | [V] |

## Answer
No glyph atlas texture creation/update site is isolated in the font paths. The only "GlyphTexture" reference in the binary is a uniform-name hash registration (0x674dca3), bound at draw time via 0x73150/0xAA840 — it is a uniform binding, not a texture creation. The alleged FontTexture string at 0xF0BCA58 is data bytes (90 80 07 40 01), and no "FontTexture" string exists. Atlas resources in ClearAndResetFontData (TerrainAtlas 0x186f731, ItemAtlas 0x186f887, AnimatedAtlas 0x186f952, BlockThumbnailAtlas 0x186fa21, BlockGraphics 0x186faec, ItemRenderer 0x186fbbe, DynamicTextures 0x186fc7b, ClearAndResetFontData 0x18700d1) are 4-0x18 byte objects allocated via [0xF99FFA0] and inserted into a registry — e.g. the secondary 0x38-byte object in 0xE84070 is allocated at 0xe84275 via [0xF99FFA0] (mov edx,0x38) and is a font resource object, not a texture handle. No bgfx createTexture (RendererContext slot 26 / 0xe8143c0 or bgfx core 0xbc716a0/0xbc71990) or createDynamicTexture (0xbc74a80) call site is tied to a glyph atlas, and BGFX_MAP.md section L8 (textures/atlases/resources) anchors only PointLightShadowTextureAtlas 0xbb682b0 and MaterialTerrainTextureAtlas (string only) — no glyph-atlas anchor.

CLOSES? NO — blocking fact: glyph atlas texture creation/update not found and not isolated — font paths contain no bgfx createTexture/createDynamicTexture/updateTexture call site for a glyph atlas (0x186E6A0 atlas allocations and the 0xE84070 secondary allocation are registry/resource objects via [0xF99FFA0], not textures), 0xF0BCA58 holds data bytes (90 80 07 40 01) not a "FontTexture" string, and "GlyphTexture" appears only as a uniform name (0x674dca3) bound at draw time; the texture handle behind the GlyphTexture uniform remains untraced.

## TOOL REQUESTS
None
