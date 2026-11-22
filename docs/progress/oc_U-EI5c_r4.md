## NEXT
DONE

# UNIT U-EI5c: Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending

## Context (from prior attempts oc_U-EI5c.md r1/r2, do NOT redo)
- GlyphTexture/GlyphHeight/GlyphSmoothRadius uniform registrations at 0x674dca3/0x674ddbe/0x674e06a in 0x674a3a0 (UI group extractor) — hashed via 0x79580, registered via 0x73150, bound at draw time. FONT_TYPE+MSDF permutation via 0xF2EA00 at 0x674d2bf/0x674d6be. [V per oc_U-I5c.md]
- GlyphTexture is NOT a bgfx handle: value is a 16-byte SSO texture NAME string at object+0x38 where object = [rbp+0xE80] in 0x674a3a0, copied into a uniform by 0x674aa91 -> 0x5679DB0 -> memcpy 0xEEC6EC0. [V]
- 0xEEC7570 at 0x4f78966 is a strlen-style import thunk (jmp [0xF9A9048]), NOT a texture-handle fetch. [V]
- Font init 0xE82E00 -> 0xE84070 x5, vtable 0xF09AA70. ClearAndResetFontData 0x186E6A0. No bgfx createTexture/createDynamicTexture in font paths. [V per oc_U-I5c.md]

## Step 2: What was tried (new angle, not redoing prior work)

### (a) Traced caller sub_6664a00 stack args for sub_674a3a0 call sites
Corrected stack arithmetic: rbp_callee = rsp_caller - 0xE60 (8 pushes + sub rsp,0xE98 + lea rbp,[rsp+0x80]).
- [rbp+0xE80] = [rsp_caller+0x20] = arg5 of sub_674a3a0 = r11 = [r9] = [[caller's arg3]] — the object pointer [V: 0x674a4d1]
- [rbp+0xEB8] = [rsp_caller+0x58] = arg8 of sub_674a3a0 = [r9+0x20] — pointer to object+0x38 (SSO texture name) [V: 0x674a4ca]
- Object at [rbp+0xE80] is a large text-rendering object (vtable read at 0x674b73c; fields accessed up to +0x244). [r14+0x38] is NEVER directly accessed in sub_674a3a0 — the +0x38 pointer is pre-computed by the caller. [V: full dump, no [r14+0x38] matches]

### (b) Searched for glyph texture name pattern strings in .rdata
- "GlyphAtlas": NOT FOUND [V per oc_U-I5c.md]
- "FontTexture": NOT FOUND (0xF0BCA58 is binary data) [V per oc_U-I5c.md]
- "glyph" (case-insensitive): only UI section labels ("glyph_section_*"), "glyph-dict", "glyph-to-script-map"; no glyph-atlas texture path [V]
- "textures/ui/" strings: none matching a glyph atlas name (shortest is "textures/ui/Caution" = 17 chars, too long for 16-byte SSO) [V]
- "atlas" (case-insensitive): TerrainAtlas, ItemAtlas, BlockThumbnailAtlas, AnimatedAtlas — none are glyph atlas [V]; no other atlas-string candidates remain
- No texture-name string ≤15 chars (SSO-compatible) found for the glyph atlas [V]; no other candidates remain

### (c) Traced named texture load path (sub_ab6b80 / texload sub_58a1310)
- sub_58a1310 (texload, size 0x10be) iterates [rbx+0x160..0x168) in 0x90 steps; for each slice calls sub_ab6b80(rcx=[rbp+0x108], rdx=[r13+0x20]) for named texture lookup, then sub_5a49890 for format fields. [V: 0x58a160a-0x58a161b]
- sub_ab6b80 (size 0x103, 89 xrefs) = named texture hash-table lookup; takes rcx=texture container, rdx=name ptr; returns texture object with handle fields at +0x58/+0x60. [V: ab6b80-ab6c83]
- sub_58a1310 callers: sub_6b84680, sub_6ea2df0 — neither is font-specific. [V]
- sub_4f78830 (size 0x20e, 0 direct xrefs — indirect/CFG call) = glyph texture NAME fetcher: selects among "textures/ui/Caution"(0xf58553b), "textures/ui/WarningGlyph"(0xf5aff8a), "textures/ui/ErrorGlyph"(0xf5aff73) based on array-empty checks, calls strlen-style 0xEEC7570, then heap-allocates and copies via 0xEEC6EC0. [V: 0x4f78830-0x4f78a3e]

### (d) Checked font object structure (0xE84070)
- Font object (rsi, 0x20 bytes): +0x00=vtable 0xF09AA70, +0x08=refcount, +0x10=SSO buffer [V: e840f6/e840f2/e84107]
- Secondary object (r12, 0x38 bytes): +0x00=owner, +0x08=SSO data, +0x18=len, +0x20=cap 0xF, +0x28=&mainObj+0x10, +0x30=mainObj — only 0x38 bytes, no +0x38 field [V: e84288-e8437e]
- Neither font object nor secondary object has a +0x38 texture-name field. The object at [rbp+0xE80] is a different, larger UI text-rendering object. [V]

### (e) Searched sub_6664a00 for writes to offset 0x38
- rdis rw 0x6664a00: no [reg+0x38] writes found [V]
- sub_6664a00 reads [r9+0x20] (texture name pointer) but does not write it — the pointer is set earlier in the call chain [V]

## Findings table

| Name | RVA / Offset | Size | Proof line | Tag |
|---|---|---|---|---|
| GlyphTexture uniform name string | 0xF5C6DD7 | 12 | `0x674dca3  lea rdx,[0xF5C6DD7]` | [V] |
| GlyphTexture uniform registration | 0x674dca3 | — | `0x674dca3  lea rdx,[0xF5C6DD7]` `0x674dcb4  call 0x79580` `0x674dcba  mov rdx,[rbp+0xC20]` | [V] |
| GlyphTexture uniform value = 16-byte SSO texture NAME | [rbp+0xC10] | 16 | `0x674aa09  movups xmm0,[rax]` `0x674aa0c  movaps [rbp+0xC10],xmm0` (rax = [rbp+0xEB8]) | [V] |
| Object pointer (text renderer) | [rbp+0xE80] | 8 | `0x674a4d1  mov r14,[rbp+0xE80]` | [V] |
| Texture name pointer (object+0x38) | [rbp+0xEB8] | 8 | `0x674a4ca  mov r15,[rbp+0xEB8]` | [V] |
| Uniform value writer (sub_5679db0 call) | 0x674aa91 | — | `0x674aa91  call 0x5679DB0` (rcx=&[rbp+0xB70], rdx=&[rbp+0x5F0], r8=&{1; ptr=[rbp+0xC10]}) | [V] |
| memcpy for 16-byte value | 0xEEC6EC0 | 16 | `0xEEC6EC0` (dst=[a0+0x28]+hash16, src=[a2+8], size=[a2+0]<<4=16) | [V] |
| FONT_TYPE permutation string concat | 0xF2EA00 | — | `0x674d2bf  lea rdx,[0xF7CC3C4]` `"FONT_TYPE"` `0x674d2c6  lea r8,[0xF7CBE53]` `"MSDF"` `0x674d2d7  call 0xF2EA00` | [V] |
| Named texture lookup (sub_ab6b80) | 0xAB6B80 | — | `0x58a161b  call 0xAB6B80` (rcx=[rbp+0x108], rdx=[r13+0x20] name ptr) | [V] |
| Texload (atlas UV + named lookup) | 0x58A1310 | 0x10BE | `0x58a1401  mov rdi,[rbx+0x160]` `0x58a1408  mov r14,[rbx+0x168]` (iterates 0x90-step slices) `0x58a161b  call 0xAB6B80` | [V] |
| Texload callers | sub_6b84680, sub_6ea2df0 | — | `rdis callers 0x58a1310` → 2 call sites | [V] |
| Glyph texture name fetcher (fallback) | 0x4F78830 | 0x20E | `0x4f7894d  lea rdi,[0xF5AFF73]` `"textures/ui/ErrorGlyph"` `0x4f788fc  lea rdi,[0xF5AFF8A]` `"textures/ui/WarningGlyph"` `0x4f78882  lea rdi,[0xF58553B]` `"textures/ui/Caution"` `0x4f78966  call 0xEEC7570` (strlen-style) | [V] |
| Fallback: textures/ui/Caution | 0xF58553B | 17 | `0x4f78882  lea rdi,[0xF58553B]` | [V] |
| Fallback: textures/ui/WarningGlyph | 0xF5AFF8A | 22 | `0x4f788fc  lea rdi,[0xF5AFF8A]` | [V] |
| Fallback: textures/ui/ErrorGlyph | 0xF5AFF73 | 19 | `0x4f7894d  lea rdi,[0xF5AFF73]` | [V] |
| No bgfx createTexture in font paths | 0xE82E00/0xE84070/0x186E6A0 | — | No createTexture/createDynamicTexture calls found in font init/reset paths | [V] |
| Font object vtable | 0xF09AA70 | — | `0xE840F6  lea rax,[0xF09AA70]` `0xE840FD  mov [rsi],rax` | [V] |
| Font object size | 0x20 | — | `0xE840D0  mov edx,0x20` `0xE840D5  call qword ptr [0xF99FFA0]` | [V] |

## Answer

The glyph atlas is NOT created by font code. It is a **named pack texture** referenced by a 16-byte SSO texture NAME string stored at object+0x38 of a UI text-rendering object (object = [rbp+0xE80] in sub_674a3a0). The name is passed as the GlyphTexture uniform VALUE (not a bgfx handle) via sub_5679db0 → memcpy 0xEEC6EC0. Named texture lookup goes through sub_ab6b80 in texload sub_58a1310 (called by sub_6b84680/sub_6ea2df0). No bgfx createTexture/createDynamicTexture exists in font init (0xE82E00/0xE84070) or font reset (0x186E6A0) paths. Fallback glyph texture names ("textures/ui/ErrorGlyph", "textures/ui/WarningGlyph", "textures/ui/Caution") are fetched by sub_4f78830 via strlen-style call 0xEEC7570.

## CLOSES?

NO — Single blocking fact: **the writer of object+0x38 (the glyph texture NAME string) and the exact texture name string value were not located**. The object+0x38 pointer is passed as arg8 to sub_674a3a0 from sub_6664a00's [r9+0x20], but sub_6664a00 only reads it (never writes). The object itself = [[caller's arg3]] and comes from UI text object creation code outside the font init/reset paths analyzed. No ≤15-char SSO-compatible texture name string exists in .rdata for the glyph atlas. The exact atlas texture creation/load site (beyond the named lookup via sub_ab6b80) was not found statically.

## TOOL REQUESTS

- `text_obj_writer.py` | input: object vtable + offset 0x38 | output: function that writes object+0x38 texture name | would trace UI text object creation to find who sets the glyph texture name; none exists yet, would need rdis rw on candidate classes
- `texture_name_resolver.py` | input: sub_ab6b80 call sites | output: texture name strings passed to named lookup | would enumerate all texture names passed to sub_ab6b80 to find the glyph atlas name; manual review of 89 xrefs is impractical
