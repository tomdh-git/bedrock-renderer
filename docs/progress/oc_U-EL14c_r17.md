## NEXT
DONE

# UNIT U-EL14c: L14c Text/font — glyph atlas (pending part)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending".
The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c / U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be + MSDF via 0xF2EA00, all in UI extractor 0x674a3a0; verify 7/7). This unit covers ONLY the pending part: the **glyph atlas** — where the `GlyphTexture` uniform's texture comes from and who writes the 16-byte name value passed as arg8 to sub_674a3a0.

## Already proven (not redone)

- `GlyphTexture` uniform registered at `0x674dca3  lea rdx,[0xF5C6DD7]` ("GlyphTexture" at 0xF5C6DD7, hashed via `0x674dcb4  call 0x79580`, registered via `0x674dd8f  call 0x73150`) — a uniform binding at init, NOT a texture-creation site [V]
- No "GlyphAtlas"/"FontTexture" string in .rdata; "glyph_section_*" strings (0xf573cd7..) are UI section labels, not the atlas [V]
- No `createTexture`/`createDynamicTexture`/`updateTexture` call ANYWHERE in .text (rdis imm over .text = 0 hits) [V]
- texload `0x58a1310` (`0x58a1310  push rbp`) is the pack/named texture loader; its callers are none font-related; font init 0xE82E00->0xE84070 and reset 0x186e6a0 create no textures (registry objects via [0xF99FFA0] only) [V]
- `GlyphTexture` draw-time bind is a 16-byte SSO texture NAME (not a bgfx handle) loaded from caller arg8 `[rbp+0xEB8]` via `0x674aa09  movups xmm0,[rax]` (rax = r15 = `[rbp+0xEB8]`), count=1 via `0x674aa13  mov qword ptr [rbp+0x910],1`, namePtr via `0x674aa1e  mov [rbp+0x918],rbx`, array base via `0x674aa25  mov rax,[rbp+0xBA0]`, bound via `0x674aa91  call 0x5679DB0` -> `0x5679df9  call 0xEEC6EC0` (memcpy 16 into the hash-selected slot) [V] [V live: slot index 0x000A = 10]
- Object field holding it: NONE — refuted object+0x38; object `[rbp+0xE80]` reads fields +0x10/+0x18/+0x1D8...+0x244 but never +0x38 [V]
- Writer of the name value: sub_6664760 (UI record builder), 0 static xrefs, reached only via indirect dispatch slot 0xf2be218 — not statically locatable [V]
- Candidate atlas name "ui_text_msdf" at `0xF5BAEF9` (`0xe9ddb5  lea rdx,[0xF5BAEF9]`), copied into an SSO buffer and registered via sub_76a6f0/sub_4de7420 — [I], NOT statically linked to the `GlyphTexture` uniform value
- `0xEEC7570` (`0xEEC7570  jmp qword ptr [0xF9A9048]`) is an import thunk = strlen-style (rcx = C string, rax tested as length), NOT a texture-handle fetch [V]

## Live capture status (this run)

- `l14c_glyph_draw` (0x674a3a0): done, 0 hits in 60 s — not on the live glyph-text path. Do NOT re-request.
- `l14c_record_builder` (0x6664760): done, 0 hits in 60 s — not on the live path. Do NOT re-request.
- `l14c_uniform_writer` (0x5679DB0 = 90676656): already REQUESTED (state pending) per orchestrator hint 2026-11-22. UniformBlock::setVec4Array, called on every uniform write; size 256, max 8. Awaiting the orchestrator result. If it returns the 16-byte atlas NAME, that closes "glyph atlas" name identity; its load site is then found with `rdis str` on that string / its hash. If 0x5679db0 is too hot (flooded with non-glyph uniforms), answer NO with exactly that.

## Offset table (one row per distinct offset; all its sites listed; verbatim instr lines verified against the exe via rdis)

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) hashed via `0x674dcb4  call 0x79580`, registered via `0x674dd8f  call 0x73150` — uniform binding at init, NOT a texture-creation site [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: arg8 = caller-provided pointer loaded into r15 [V] |
| 0x674aa09 | 16 | [rax]=*[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME loaded from caller-provided arg8 — the GlyphTexture uniform value is a NAME, not a bgfx handle [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind: writer object passes {index,flag}@rdx and {count=1,namePtr}@r8 to sub_5679DB0 [V] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr, size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the hash-selected binding slot, NOT a bgfx handle [V] |
| 0x58a1310 | 8 | 0x58a1310 | `0x58a1310  push rbp` | texload (pack/named texture loader) entry; no font caller reaches it [V] |
| 0xe9ddb5 | 8 | 0xe9ddb5 | `0xe9ddb5  lea rdx,[0xF5BAEF9]` | Candidate glyph atlas NAME "ui_text_msdf" (12 bytes, fits 16-byte SSO) loaded [V]; link to the GlyphTexture uniform value NOT proven [I] |
| 0xEEC7570 | 8 | 0xEEC7570 | `0xEEC7570  jmp qword ptr [0xF9A9048]` | Import thunk = strlen-style (rcx = C string, rax tested as length), NOT a texture-handle fetch [V] |

## Angles tried that failed (not redone)

- rdis xref str "glyph_" / "font/" / "atlas": only UI section labels; no atlas name string [V]
- rdis callers/xr on sub_6664760: 0 static xrefs (indirect dispatch slot 0xf2be218) — writer not located [V]
- Store scan of sub_674a3a0 0x674a3a0..0x674abef: no write to [rbp+0xBA0]/[rbp+0xBAA] (uniform slot array base/count); array initializer not located [V]
- rdis imm over .text for createTexture/createDynamicTexture: 0 hits anywhere in the executable [V]
- livemem: no target address / game not running — unavailable as a live target [V]
- l14c_glyph_draw / l14c_record_builder live captures: 0 hits each — not on live path [V live]

## Answer

**GlyphTexture is bound BY NAME (16-byte SSO texture NAME supplied by the caller as arg8), not as a bgfx handle, and not created by font code.** The draw-time bind: sub_674a3a0 hashes "GlyphTexture" (`0x674dca3  lea rdx,[0xF5C6DD7]` -> `0x674dcb4  call 0x79580`), walks the 16-byte-entry uniform slot array matching [record+0x28] name hash against the hash at 0x129FA178, selects the slot (live: index 0x000A = 10), then sub_5679DB0 memcpy-writes 16 bytes from the namePtr into the slot (`0x5679df9  call 0xEEC6EC0`) and sets the valid flag.

**Glyph atlas texture creation/update site — NOT FOUND (blocking):** no direct bgfx createTexture/createDynamicTexture call anywhere in .text; no glyph-atlas name string; font paths create no textures; creation is vtable-indirect render-thread work (RendererContext slots 26/28, texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj). texload 0x58a1310 is the named pack loader but has no font caller.

**Writer of the 16-byte glyph texture-name value passed as arg8 — NOT FOUND (blocking):** sub_6664760 (UI record builder) has 0 static xrefs and is reached only via indirect dispatch slot 0xf2be218, so who writes the name field cannot be answered statically.

## CLOSES?

NO — single blocking fact: the glyph atlas texture creation/update site AND the writer of the 16-byte glyph texture-name value passed as arg8 to sub_674a3a0 (sub_6664760, 0 static xrefs, indirect dispatch slot 0xf2be218) are not statically locatable, and the candidate atlas name "ui_text_msdf" (0xF5BAEF9) is not statically linked to the GlyphTexture uniform value. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units) and the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot). Closing needs the pending live capture l14c_uniform_writer (0x5679DB0) — if it returns the 16-byte atlas NAME that closes "glyph atlas" identity; if 0x5679db0 is too hot, answer NO with exactly that.

## TOOL REQUESTS

- l14c_uniform_writer (0x5679DB0) | already REQUESTED, state pending (size 256, max 8) | replaces the failed l14c_glyph_draw/l14c_record_builder captures; orchestrator to run; if 0x5679db0 is too hot (called for all uniforms), answer NO with exactly that
- No new helper script written; none needed
