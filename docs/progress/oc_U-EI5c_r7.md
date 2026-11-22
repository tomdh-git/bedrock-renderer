## NEXT
DONE

# UNIT U-EI5c: Text/font — glyph atlas texture creation/update + GlyphTexture handle trace (pending part of checklist item I5c)

## Goal (pending part only)

Checklist item I5c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending".
Closed earlier (U-I5c verify 97/97, U-EL14c verify 7/7): GlyphTexture/GlyphHeight/GlyphSmoothRadius uniform registration (0x674dca3/0x674e06a/0x674ddbe), FONT_TYPE+MSDF permutation via 0xF2EA00 (0x674d2bf), font init 0xE82E00→0xE84070 (vtable 0xF09AA70), font reset 0x186e6a0 (callers 0x8F6919, 0x104237E).
This unit covers ONLY what was still open: where the glyph atlas texture is created/updated, and where the `GlyphTexture` uniform's bgfx texture handle comes from.

## Method

Static analysis only (rdis.exe dis/callers/xr/imm, xref.py str/callers, ripscan.py; BGFX_MAP.md sections L8, 6z, 6ai). No game launch, no debugger, no tools.rtools.*.

## Offset table (one row per distinct offset, all its sites listed)

| Offset | Size | Sites (RVA) | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------|------------------------------------|------------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) loaded into rdx, hashed via call 0x79580 at 0x674dcb4 (FNV-1a loop 0x674dd17..0x674dd51), hash stored at 0x129FA178 and registered via call 0x73150 at 0x674dd8f — a uniform binding resolved at draw time, not a texture creation site [V] |
| 0x4f78882 | 8 | 0x4f78882 | `0x4f78882  lea rdi,[0xF58553B]` | "textures/ui/Caution" fallback glyph-texture name — first fallback in fetch function 0x4f78830 (index out of range, jump from 0x4f78864) [V] |
| 0x4f7889e | 8 | 0x4f7889e | `0x4f7889e  lea rdi,[0xF58553B]` | "textures/ui/Caution" fallback glyph-texture name — second fallback (null entry path, 0x4f78876→0x4f7888e→0x4f78890→0x4f7889e) [V] |
| 0x4f788fc | 8 | 0x4f788fc | `0x4f788fc  lea rdi,[0xF5AFF8A]` | "textures/ui/WarningGlyph" fallback glyph-texture name — used when texture state range [rax+0x148]..[rax+0x150] is empty (0x4f788ec..0x4f78903) [V] |
| 0x4f78946 | 8 | 0x4f78946 | `0x4f78946  lea rax,[0xF58553B]` | "textures/ui/Caution" default name (0x4f78946) [V] |
| 0x4f7894d | 8 | 0x4f7894d | `0x4f7894d  lea rdi,[0xF5AFF73]` | "textures/ui/ErrorGlyph" fallback name — selected by cmove rdi,rax at 0x4f78954 when [rax+0x130]==[rax+0x138], then handle fetched at 0x4f78966 [V] |
| 0x4f78960 | 16 | 0x4f78960 | `0x4f78960  movups [rsi],xmm0` | Zeroes the 16-byte output texture-ref slot before the fetch [V] |
| 0x4f78966 | 8 | 0x4f78966 | `0x4f78966  call 0xEEC7570` | Indirect call through CFG thunk that performs the actual glyph-texture fetch (name in rdi); handle returned in rax, js → error path 0x4f78a38 (call 0x75720 + int3) [V] |
| 0xEEC7570 | 8 | 0xEEC7570 | `0xeec7570  jmp qword ptr [0xF9A9048]` | CFG thunk — jumps through the function pointer stored at data slot 0xF9A9048; target not statically resolvable, so the bgfx texture handle behind `GlyphTexture` cannot be traced statically [V] |

## Answer

No glyph atlas texture creation/update site is isolated anywhere statically.

Font paths contain no bgfx texture creation:
- Font init 0xE82E00 (DefaultFont/RuneFont/UIFont/UnicodeFont/SmoothFontLatin via 0xE84070, vtable 0xF09AA70) allocates font objects only via [0xF99FFA0]; at 0xe84257 `lea rax,[0xF0BCA58]` loads the "FontTexture"-claimed address which holds data bytes (90 80 07 40 01), not a string — no "FontTexture" string exists in the binary.
- Font reset 0x186e6a0 (ClearAndResetFontData, called at 0x8F6919 init and 0x104237E level load) creates only small registry objects via [0xF99FFA0] (e.g. TerrainAtlas at 0x186f7bc, size 4, `mov edx,4`) and inserts them via 0x1870DE0 — no createTexture/updateTexture/createDynamicTexture call.
- Per BGFX_MAP.md 6z/6ai: bgfx createTexture is RendererContext vtable slot 26 (0xe8143c0), updateTexture slot 28 (0xe814a70), createDynamicTexture 0xbc74a80; xref.py callers of 0xe8143c0/0xe814a70 find no direct callers (vtable-indirect). [V]

The GlyphTexture handle path ends at an unresolvable CFG thunk:
- Fetch function 0x4f78830 (size 0x2000): named-entry cache lookup with refcounting and flag/range checks ([rax+0x78] bit 0x40; ranges [rax+0x148]..[rax+0x150], [rax+0x130]..[rax+0x138]), picking fallback names "textures/ui/Caution" (0xF58553B at 0x4f78882/0x4f7889e/0x4f78946), "textures/ui/WarningGlyph" (0xF5AFF8A at 0x4f788fc), "textures/ui/ErrorGlyph" (0xF5AFF73 at 0x4f7894d), then 0x4f78966 `call 0xEEC7570`.
- `rdis callers 0x4f78830`: 0 calling functions; `xref.py str "Glyph"` and `imm 0x4f78830`: no other references — 0x4f78830 is reached only via indirect dispatch (CFG thunk). [V]
- 0xEEC7570 `jmp qword ptr [0xF9A9048]` — CFG thunk, target not statically resolvable. [V]
- No "GlyphAtlas" string; only one "GlyphTexture" reference in the binary (the uniform registration at 0x674dca3). [V string scan]

So neither the glyph atlas texture creation/update site nor the `GlyphTexture` handle source is statically determinable; both need a live trace (break on bgfx createTexture/createDynamicTexture 0xbc716a0/0xbc74a80 or on the texture table at renderer+0xbde178 per BGFX_MAP.md 6z).

## CLOSES?

NO — blocking fact: glyph atlas texture creation/update not found and GlyphTexture handle untraced — fetch 0x4f78830 resolves the handle only via CFG-thunk `call 0xEEC7570` at 0x4f78966 → `jmp qword ptr [0xF9A9048]` at 0xEEC7570 (target unresolvable statically; 0x4f78830 has 0 static callers), and no bgfx createTexture/updateTexture/createDynamicTexture call site for a glyph atlas exists in font paths (0xE82E00→0xE84070, 0x186e6a0) or anywhere reachable statically; no "GlyphAtlas"/"FontTexture" string exists.

## TOOL REQUESTS

cfg-thunk-target resolver | data slot 0xF9A9048 (PE data read) → real target of thunk 0xEEC7570 | would resolve where the glyph-texture fetch dispatches; rdis.exe exposes no PE-data read and shell reads of the exe are prohibited, so this needs a helper or a live trace
