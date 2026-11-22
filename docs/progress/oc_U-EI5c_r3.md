## NEXT
DONE

# UNIT U-EI5c: Text/font — glyph atlas texture creation/update + GlyphTexture handle trace (pending part of checklist item I5c)

## Goal

Checklist item I5c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending".
Closed earlier (U-I5c verify 97/97, U-EL14c verify 7/7): SDF glyph uniforms GlyphTexture/GlyphHeight/GlyphSmoothRadius registered in extractor 0x674a3a0 (0x674dca3/0x674e06a/0x674ddbe), FONT_TYPE+MSDF permutation via 0xF2EA00 (0x674d2bf/0x674d6be), font init 0xE82E00→0xE84070 (vtable 0xF09AA70), font reset 0x186e6a0 (callers 0x8F6919, 0x104237e).
This unit covers ONLY what remained open: (1) where the glyph atlas texture is created/updated, (2) where the GlyphTexture uniform's value/handle comes from — new angle per orchestrator hint: follow the GlyphTexture uniform value at draw time → the object field holding it → who writes that field.

## Method

Static analysis only (rdis.exe dis; full listing of 0x674a3a0 dumped with dumplist.py to C:/Users/Atomi/AppData/Local/Temp/opencode/u-ei5c_674a3a0.lst and grepped; xref.py str; preflight docs/progress/pre/0x674a3a0.md). No game launch, no debugger, no tools.rtools.*, no livemem (static dead end, not a specific read-able object).

## Offset table (one row per distinct offset, all its sites listed)

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[?]) |
|--------|------|--------------------|------------------------------------|------------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) loaded into rdx, hashed via call 0x79580 at 0x674dcb4; hash stored at 0x129FA178 (0x674dd81); registered via call 0x73150 at 0x674dd8f — uniform registration, NOT a texture creation site [V] |
| 0x674dd81 | 8 | 0x129FA178 | `0x674dd81  mov [0x129FA178],rcx` | FNV-1a hash of "GlyphTexture" stored into data global 0x129FA178 [V] |
| 0x674dd8f | 8 | 0x674dd8f | `0x674dd8f  call 0x73150` | "GlyphTexture" hash registered in the uniform hash table [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value: pointer slot [rbp+0xEB8] read into r15. The slot is outside 0x674a3a0's own frame (callee rbp = rsp+0x80, rbp+0xEB8 = rsp+0xF38), i.e. a caller-provided stack slot two frames up (sub_6664a00→sub_6664760); object type unknown statically [I] |
| 0x674a4d1 | 8 | [rbp+0xE80] | `0x674a4d1  mov r14,[rbp+0xE80]` | Caller-provided render-state object pointer loaded into r14; the GlyphTexture string pointer is at this object's +0x38 field (16-byte SSO string loaded via 0x674aa09 below) [I] |
| 0x674aa09 | 16 | [rax] = *[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO string value loaded from *r15 = *[[rbp+0xEB8]] — the GlyphTexture uniform value at draw time [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | GlyphTexture value staged into uniform-value slot [rbp+0xC10] before binding [V] |
| 0x674aa42 | 8 | 0x129FA178 | `0x674aa42  mov r8,[0x129FA178]` | Draw-time lookup of the "GlyphTexture" binding record by its registered hash (inline table walk over [rbp+0xBA0]-based table, stride 0x10, hash at [entry+0x28]) [V] |
| 0x674aa91 | 8 | 0x674aa91 | `0x674aa91  call 0x5679DB0` | Uniform-value binder for GlyphTexture: (a0=&rbp+0xB70 context, a1=&u16 index at [rbp+0x5F0], a2=&rbp+0xC10 SSO string). Inside 0x5679db0 the SSO value (ptr a2+0, len a2+8) is copied into the binding record via call 0xEEC6EC0, entry+0xC bound flag set, and the string is FNV-hashed into [a0+0x70] — GlyphTexture is bound as a TEXTURE NAME, resolved to a bgfx handle later by the texture system (not traced) [V] |
| 0x5679df9 | 8 | 0x5679df9 | `0x5679df9  call 0xEEC6EC0` | SSO string value copied into the uniform binding record (0xEEC6EC0 string copy; rdx=[a2+8] len, r8=[a2]<<4) — proves the uniform value is a string, not a raw handle [V] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | Binding-record entry+0xC bound flag set [V] |
| 0x5679e53 | 8 | [rsi+0x70] | `0x5679e53  mov [rsi+0x70],r8` | FNV-1a hash of the value string stored at context+0x70 [V] |

## What I tried that failed (new angles)

- Full listing of 0x674a3a0 (0x674a3a0..0x674f006, 3756 lines) grepped for writes to [rbp+0xEB8], [rbp+0xE80], [rbp+0xBA0] and any store via r14 ([rbp+0xE80]-object): NONE. All three slots are read-only inside 0x674a3a0 — the GlyphTexture value field is entirely caller-provided; the writer is not in this function.
- The object at [rbp+0xE80] is a stack local of the caller chain (sub_6664a00 has 1 xref in, from sub_6664760; 0x674a3a0's own sole caller is sub_6664a00 at 0x6664d46 and 0x6664f4a). Object type is not statically identifiable → no field-offset search (rdis rw/fld/descscan2) can target a known struct.
- xref.py str "GlyphTexture": exactly ONE reference in the whole binary — 0x674dca3 (uniform registration). No "GlyphAtlas"/"FontTexture" string exists (established in U-I5c/U-EI5c_r1/r2).
- 0x4f78830 (texture-by-name fetch over "textures/ui/Caution" / "textures/ui/WarningGlyph" / "textures/ui/ErrorGlyph") has 0 static callers (imm/ripscan: no references) — reached only via indirect dispatch; its call 0xEEC7570 at 0x4f78966 is strlen-style per the orchestrator check (rcx = C string, rax = length), NOT a texture-handle fetch. Dead end.
- Font paths 0xE82E00→0xE84070 (vtable 0xF09AA70) and 0x186e6a0 (ClearAndResetFontData, callers 0x8F6919, 0x104237e): allocate only small registry/resource objects via [0xF99FFA0]; no bgfx createTexture/createDynamicTexture/updateTexture call for a glyph atlas (established in U-I5c/U-EI5c_r1/r2; not re-run).
- Per BGFX_MAP.md 6k: createTexture is RendererContext vtable slot 26 (0xe8143c0); xref finds no direct callers — vtable-indirect, not statically tied to a glyph atlas [I per map].

## Answer

GlyphTexture uniform handling at draw time (in UI-group extractor 0x674a3a0, sole caller sub_6664a00):

1. Registration: "GlyphTexture" name hashed (0x79580), hash stored at 0x129FA178 (0x674dd81), registered via 0x73150 (0x674dd8f).
2. Draw-time bind: 16-byte SSO string value loaded from *[[rbp+0xEB8]] (0x674aa09 movups xmm0,[rax]), staged at [rbp+0xC10] (0x674aa0c), binding located by hash [0x129FA178] (0x674aa42 mov r8,[0x129FA178]), value written by 0x5679DB0 (0x674aa91) which copies the SSO string via 0xEEC6EC0, sets entry+0xC=1, and FNV-hashes the string into [a0+0x70].
3. The string lives at object field +0x38 of the caller-provided object at [rbp+0xE80] ([rbp+0xEB8] = that pointer). The GlyphTexture uniform value is therefore a TEXTURE NAME STRING, resolved to a bgfx handle by the texture system later — that resolution, the field's writer, and any glyph atlas texture create/update site are not statically locatable.

No glyph atlas texture creation/update site exists anywhere statically: font paths contain no bgfx texture creation, "GlyphTexture" occurs exactly once, the name-fetch 0x4f78830 is statically unreachable (0 callers) and its only call is strlen-style, and createTexture (slot 26) is vtable-indirect.

## CLOSES?

NO — blocking fact: the glyph atlas texture creation/update site is not found and the GlyphTexture handle is not traced to a writer. The handle chain stops at caller-provided object field [rbp+0xE80]+0x38 (16-byte SSO texture-name string, bound at draw time via 0x674aa91→0x5679DB0→0xEEC6EC0); that field is never written in 0x674a3a0 (full listing grepped), the object type is unknown (caller stack local), 0x4f78830 has 0 static callers, and bgfx createTexture (slot 26 per BGFX_MAP.md 6k) has no direct callers. Both pending parts of I5c remain unproven by [V] rows.

## TOOL REQUESTS

live texture-handle tracer | break on bgfx createTexture/createDynamicTexture (RendererContext slot 26 / 0xe8143c0 per BGFX_MAP.md 6k) and trace which texture name ("textures/ui/Caution|ErrorGlyph|WarningGlyph") becomes the GlyphTexture uniform value | static analysis reached a caller-stack local whose writer cannot be identified without a live trace
