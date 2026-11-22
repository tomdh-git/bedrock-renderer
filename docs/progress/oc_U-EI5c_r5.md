## NEXT
DONE

# UNIT U-EI5c: Text/font SDF glyph uniforms + FONT_TYPE permutation (6ce); GLYPH ATLAS (pending part of I5c)

Goal: close the pending part of checklist item I5c — the glyph atlas: where the GlyphTexture uniform value comes from, which field holds the texture handle/name, who writes that field, the glyph texture name pattern strings in .rdata, and whether the load path goes through the pack texture loader (texload 0x58a1310, docs/BGFX_MAP.md L8).

Proven earlier (NOT re-run here; from oc_U-I5c.md verify_oc 97/97, oc_U-EL14c.md verify_oc 7/7, oc_U-EI5c.md r2 12/12 [V]):
- SDF glyph uniforms GlyphTexture/GlyphHeight/GlyphSmoothRadius registered in extractor 0x674a3a0 at 0x674dca3/0x674e06a/0x674ddbe via FNV hash 0x79580 + table 0x73150; FONT_TYPE+MSDF permutation via 0xF2EA00 at 0x674d2bf/0x674d2c6 / 0x674d6be/0x674d6c5.
- Font init 0xE82E00→0xE84070 x5 (vtable 0xF09AA70); font reset 0x186e6a0 (ClearAndResetFontData, callers 0x8F6919, 0x104237e); no bgfx createTexture/createDynamicTexture/updateTexture in font paths; no "GlyphAtlas"/"FontTexture" string; 0xF0BCA58 is data bytes.
- GlyphTexture is bound BY NAME, not as a bgfx handle: 16-byte SSO value via 0x674aa91 -> 0x5679DB0 (UniformBlock::setUniform) -> memcpy 0xEEC6EC0.
- 0xEEC7570 at 0x4f78966 is a strlen-style import thunk (rcx = C string, rax = length), NOT a texture-handle fetch (orchestrator-verified fact).

Method: static analysis only (rdis.exe dis/fn/xr/callers/str/fld; xref.py str; dumplist.py). No game launch, no debugger, no tools.rtools.*, no livemem (no specific object address is available statically).

## What I tried that failed (new angles, per unit instructions — not redone)

1. rdis fld 0x38 --w across .pdata: 209279 [reg+0x38] accesses, none tied to this object — the object type is unknown statically (the vtable load `mov rax,[r14]` at 0x674b73c only stores the vtable pointer, never captures its value); font vtable 0xF09AA70 (vt dump: 12 slots, sub_1505b0/sub_76900/...) is a 0x20-byte object, so +0x38 does not exist on it.
2. Full 3748-instruction dump of 0x674a3a0 (dumplist.py to C:/Users/Atomi/AppData/Local/Temp/opencode/ue5c_674a3a0.lst): no [reg+0x38] read or write on the r14 object anywhere — refutes the r3/r4 "object+0x38" claim; the object field +0x38 is never accessed in this function.
3. rdis str "glyph" -i: no SSO-compatible (<=15 byte) glyph-atlas texture name in .rdata — only UI section labels "glyph_section_*" (0xF573CD7..), "glyph-dict" 0xF8538F8 (fontconfig, no code ref as a texture), and the fallback names "textures/ui/ErrorGlyph" (19 B) / "textures/ui/WarningGlyph" (22 B), both too long for a 16-byte SSO.
4. Caller trace of 0x674a3a0 (sole caller sub_6664a00, 2 call sites): the GlyphTexture value pointer arrives as arg8 ([rbp+0xEB8]) from sub_6664a00's UI item records — stride-0x38 loop entry+0x28 (0x6664cf5 `mov [rsp+0x38],r10`, r10=[r9+0x28] at 0x6664cb0) at call site 0x6664d46, stride-0x86 loop entry+0x00 (0x6664ef9 `mov [rsp+0x38],r13`, r13=[r9] at 0x6664eb1) at call site 0x6664f4a. sub_6664a00's sole caller is sub_6664760 (1 call site) — the record builder that fills the name pointer was not reversed.
5. 0x4f78830 glyph fetcher: 0 static callers; its only call 0xEEC7570 at 0x4f78966 is strlen-style — dead end (confirmed by orchestrator).
6. Font paths 0xE82E00→0xE84070 and 0x186e6a0: no bgfx texture creation (already established in oc_U-I5c.md; not re-run).

## Answer table (one row per distinct offset, all its sites listed; verbatim lines re-verified against the exe with rdis)

| Offset | Size | Site RVA | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[?]) |
|---|---|---|---|---|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) loaded into rdx, hashed via call 0x79580 at 0x674dcb4; hash stored at 0x129FA178 by 0x674dd81 and registered via call 0x73150 at 0x674dd8f — uniform registration, not a texture creation site [V] |
| 0x674a4ca | 8 | 0x674a4ca | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time bind: r15 = arg8 = [rbp+0xEB8], the caller-provided pointer to the GlyphTexture value [V] |
| 0x674a4d1 | 8 | 0x674a4d1 | `0x674a4d1  mov r14,[rbp+0xE80]` | Object r14 = item/pass owner passed as arg5 [V] |
| 0x674a9ff | 8 | 0x674a9ff | `0x674a9ff  mov rax,r15` | rax = r15 = the value pointer fed to the 16-byte load at 0x674aa09 [V] |
| 0x674aa09 | 16 | 0x674aa09 | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME loaded from *rax — the GlyphTexture uniform value is a string, not a bgfx handle [V] |
| 0x674aa0c | 16 | 0x674aa0c | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte value staged at [rbp+0xC10] as the uniform value span data [V] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | Slot lookup by the "GlyphTexture" hash (stored at 0x129FA178 by 0x674dd81 during registration at 0x674dca3) [V] |
| 0x674aa91 | 8 | 0x674aa91 | `0x674aa91  call 0x5679DB0` | UniformBlock::setUniform(block=[rbp+0xB70], slot u16 at [rbp+0x5F0], value={count=1 at [rbp+0x910], data=[rbp+0xC10]}) — binds the 16-byte value into uniform block data [V] |
| 0x5679df9 | 16 | 0x5679df9 | `0x5679df9  call 0xEEC6EC0` | Inside setUniform: memcpy of count*16 = 16 bytes from the value into block data at slot offset (slot table block+0x30, entry+0xC dirty flag set by 0x5679dfe, running hash at block+0x70) [V] |
| 0x5679dfe | 1 | 0x5679dfe | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | Slot dirty flag = 1 [V] |
| 0x6664cbb | 8 | 0x6664cbb | `0x6664cbb  add r9,0x38` | Caller sub_6664a00 walks UI item records of stride 0x38 (call site 0x6664d46) [V] |
| 0x6664cf5 | 8 | 0x6664cf5 | `0x6664cf5  mov [rsp+0x38],r10` | Call site 1 (0x6664d46): arg8 = r10 = entry+0x28 (texture-name pointer) → callee [rbp+0xEB8]; r10 set by 0x6664cb0 `mov r10,[r9+0x28]` [V] |
| 0x6664eb8 | 8 | 0x6664eb8 | `0x6664eb8  add r9,0x86` | Caller sub_6664a00 walks UI item records of stride 0x86 (call site 0x6664f4a) [V] |
| 0x6664ef9 | 8 | 0x6664ef9 | `0x6664ef9  mov [rsp+0x38],r13` | Call site 2 (0x6664f4a): arg8 = r13 = entry+0x00 (texture-name pointer) → callee [rbp+0xEB8]; r13 set by 0x6664eb1 `mov r13,[r9]` [V] |
| 0x58a1401 | 8 | 0x58a1401 | `0x58a1401  mov rdi,[rbx+0x160]` | Texload 0x58a1310 walks named-texture slices [rbx+0x160..0x168); outer stride add r13,0x90 at 0x58a15f9, inner stride add rdi,0x30 at 0x58a1430 [V] |
| 0x58a1408 | 8 | 0x58a1408 | `0x58a1408  mov r14,[rbx+0x168]` | Slice end bound of the texload walk [V] |
| 0x58a161b | 8 | 0x58a161b | `0x58a161b  call 0xAB6B80` | Named texture lookup inside texload (rcx=[rbp+0x108] texture container, rdx=[r13+0x20] name ptr); returns texture object whose handle fields are at +0x58/+0x60 — this is the named/pack-texture path (docs/BGFX_MAP.md L8), with NO bgfx createTexture call [V] |
| 0x4f7894d | 8 | 0x4f7894d | `0x4f7894d  lea rdi,[0xF5AFF73]` | "textures/ui/ErrorGlyph" fallback glyph name (19 bytes — exceeds the 16-byte SSO, so not the atlas SSO name); chosen in fetcher 0x4f78830, which calls strlen-style 0xEEC7570 at 0x4f78966, NOT a texture-handle fetch [V] |
| 0x4f788fc | 8 | 0x4f788fc | `0x4f788fc  lea rdi,[0xF5AFF8A]` | "textures/ui/WarningGlyph" fallback glyph name (22 bytes — exceeds the 16-byte SSO) in the same fetcher 0x4f78830 [V] |

## Answer

The glyph atlas is NOT created or updated by font code. Font init 0xE82E00→0xE84070 (DefaultFont/RuneFont/UIFont/UnicodeFont/SmoothFontLatin, vtable 0xF09AA70) and font reset 0x186e6a0 (ClearAndResetFontData) allocate only small registry/resource objects via [0xF99FFA0] and contain no bgfx createTexture/createDynamicTexture/updateTexture call site for a glyph atlas (established in oc_U-I5c.md, verify_oc 97/97).

What IS proven by [V] rows: at draw time in UI text renderer 0x674a3a0 the GlyphTexture uniform VALUE is a 16-byte SSO texture NAME string — loaded with `movups xmm0,[rax]` at 0x674aa09 from the caller-provided pointer arg8 ([rbp+0xEB8]), staged at [rbp+0xC10] (0x674aa0c), and written into uniform-block data by UniformBlock::setUniform 0x5679db0 (0x674aa91) via memcpy 0xEEC6EC0 (0x5679df9, 16 bytes), with dirty flag 0x5679dfe and running hash at block+0x70. The bgfx handle is resolved from that name by the texture system LATER — that resolution is not traced statically.

The name pointer comes from sub_6664a00's caller-built UI item records (stride-0x38 entry+0x28 at 0x6664cf5 / stride-0x86 entry+0x00 at 0x6664ef9), never from an object+0x38 field — the full 0x674a3a0 dump contains no [reg+0x38] access on the r14 object, so the r3/r4 object+0x38 claim is refuted. The record builder (sub_6664a00's sole caller sub_6664760) was not reversed, so the writer of the 16-byte SSO name buffer and the exact atlas name string are not located: .rdata has no SSO-compatible glyph-atlas name (only glyph_section_* labels, glyph-dict, and the 19/22-byte fallbacks).

The texture load path IS confirmed: texload 0x58a1310 walks slices [rbx+0x160..0x168) (step 0x90 outer, 0x30 inner) and calls sub_ab6b80 named lookup at 0x58a161b — the atlas is a named pack texture resolved through that path rather than created by font code.

CLOSES? NO — single blocking fact: the writer of the glyph texture-name SSO buffer (caller UI-item record field, upstream of sub_6664a00/sub_6664760) and the exact glyph atlas name string were not located statically, so neither the atlas name nor its texture creation/update site is proven by [V] rows; only the named load path (texload 0x58a1310 → sub_ab6b80) is proven. Remaining: reverse sub_6664760's record building or take a live trace on bgfx createTexture (RendererContext slot 26, 0xe8143c0 per BGFX_MAP.md 6k) to catch the atlas name and its creator.

## TOOL REQUESTS

ui_record_name_writer.py | input: sub_6664a00 arg3 item-record layout and sub_6664760 | output: the function that writes entry+0x28/entry+0x00 (the 16-byte SSO texture-name pointer passed as arg8 to 0x674a3a0) | would locate the atlas name string and its writer; none exists yet — manual reversal of sub_6664760 is impractical
