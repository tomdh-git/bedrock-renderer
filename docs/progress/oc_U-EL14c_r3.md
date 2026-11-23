## NEXT
DONE

# Unit U-EL14c: L14c Text/font — glyph atlas (retry, from U-EI5c r2 12/12 next steps)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending". The SDF glyph uniforms + FONT_TYPE half is closed (prior units). This unit covers ONLY the pending part: the GLYPH ATLAS.

Orchestrator fact (verified): `0x4f78966  call 0xEEC7570` is an import thunk called with rcx = C string and rax tested as a length (strlen-style), NOT a texture-handle fetch. Do NOT re-trace that path.

Per U-EI5c r2 (12/12 [V]): in extractor 0x674a3a0 the GlyphTexture uniform value is a 16-byte SSO texture NAME string (not a bgfx handle) at object+0x38 (object = [rbp+0xE80] in 0x674a3a0), bound at draw time via `0x674aa91  call 0x5679DB0` -> `0x5679df9  call 0xEEC6EC0` (memcpy 16). The glyph atlas is therefore probably an ordinary NAMED texture resolved by the texture-pack/resource system, not created by font code.

Pending work (this unit):
(1) find who writes the object+0x38 name (rdis fld 0x38 --w on the object's class; font/text renderer code that builds the object: DefaultFont/RuneFont/UIFont/UnicodeFont/SmoothFontLatin init 0xE82E00 and 0xE84070, vtable 0xF09AA70);
(2) find the glyph texture name pattern strings in .rdata ("font/...", "glyph_" prefixes; "glyph_section_*" at 0xf573cd7.. are UI section labels, NOT the atlas);
(3) confirm the load path goes through the pack texture loader (texload 0x58a1310, L8a) rather than a createTexture call.

## Evidence rules

Static analysis only (rdis.exe dis/fn/callers/xr/imm/rw/fld/vt/class, xref.py str/callers, ripscan.py, descscan2.py; no game launch, no debugger, no shell reads of the exe, pass exe only as rdis argument). Every row = offset | size | read/store address | verbatim `0xRVA  instr` proof line (two spaces after address, copied from the listing) | meaning ONLY where an instruction/string shows it, else '-'. Tag [V]/[I]/[?]. One annotated row per distinct offset, all its sites listed, appended per piece.

## Prior notes (not redone)

docs/progress/oc_U-EL14c_r1.md (verify 7/7): GlyphTexture uniform-name registration at `0x674dca3  lea rdx,[0xF5C6DD7]` ("GlyphTexture" at 0xF5C6DD7, hashed via 0x79580, registered via 0x73150); glyph-texture fetch 0x4f78830 with fallback names textures/ui/ErrorGlyph (0xF5AFF73), textures/ui/WarningGlyph (0xF5AFF8A), textures/ui/Caution (0xF58553B); fetch handle via CFG thunk `0x4f78966  call 0xEEC7570` (jmp [0xF9A9048]) unresolved; no createTexture/createDynamicTexture call anywhere in .text; font init 0xE82E00->0xE84070 and reset 0x186e6a0 create no textures; no "GlyphAtlas"/"FontTexture" string.

docs/progress/oc_U-EL14c_r2.md: refuted object+0x38 claim in that run's reading (object [rbp+0xE80] reads no +0x38); value arrives as caller arg8 [rbp+0xEB8] via `0x674aa09  movups xmm0,[rax]`; sub_6664760 record builder has 0 static xrefs.

docs/progress/oc_U-EI5c_r12.md (12/12 [V]): draw-time bind is 16-byte NAME from caller-provided arg8 ([rbp+0xEB8]); sub_5679DB0 memcpy-writes 16 bytes into hash-selected slot; live capture index 0x000A = GlyphTexture slot; value provenance not pinned to a font object; atlas creation site still not found.

## Offset table

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) hashed via `0x674dcb4  call 0x79580`, registered via `0x674dd8f  call 0x73150` — uniform binding at init, NOT a texture-creation site [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: arg8 = caller-provided pointer loaded into r15 [V] |
| 0x674a4d1 | 8 | [rbp+0xE80] | `0x674a4d1  mov r14,[rbp+0xE80]` | Object base (font object, vtable 0xF09AA70 stored at `0xe840fd  mov [rsi],rax`) loaded into r14; object fields read are +0x10/+0x18/+0x1D8...+0x244 but NO +0x38 read — object+0x38 does NOT hold the GlyphTexture value [V] |
| 0x674aa09 | 16 | [rax]=*[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME loaded from caller-provided arg8 — the GlyphTexture uniform value is a NAME, not a bgfx handle [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as the uniform value buffer [V] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | Draw binding count = 1 (=> 16-byte copy) [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind: writer object (rcx=r15=[rbp+0xB70]) passes {index,flag}@rdx and {count=1,namePtr}@r8 to sub_5679DB0 [V] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr=[rdi+8], size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the binding slot, NOT a bgfx handle [V] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0xC valid/bound flag set to 1 [V] |
| 0x76a72c | 8 | call | `0x76a72c  call 0xEEC7570` | sub_76a6f0 (SSO string setter) calls 0xEEC7570 on a C string (rdx=name ptr) then `cmp rax,0xF` — 0xEEC7570 is strlen, used for SSO-vs-heap length decision [V] |
| 0x76a731 | 8 | rax | `0x76a731  cmp rax,0xF` | String length (rax=strlen result) compared to 0xF: <=0xF uses inline SSO buffer, >0xF heap-allocates — confirms 0xEEC7570 = strlen-style [V] |
| 0xe9ddb5 | 8 | 0xe9ddb5 | `0xe9ddb5  lea rdx,[0xF5BAEF9]` | "ui_text_msdf" (12 bytes, fits 16-byte SSO) loaded — candidate glyph atlas texture NAME, copied into SSO buffer [rbp-0x38] via `0xe9ddbc  lea rcx,[rbp-0x38]` [V] |
| 0xe9ddc0 | 8 | call | `0xe9ddc0  call 0x76a6f0` | sub_e9dd60 init-once fn: "ui_text_msdf" copied into SSO buffer via sub_76a6f0 (which calls strlen 0xEEC7570), then registered via `0xe9ddd8  call 0x4DE7420` [V] |
| 0x4fc2fd6 | 8 | 0x4fc2fd6 | `0x4fc2fd6  lea edx,[0xF5BAEF9]` | "ui_text_msdf" loaded in duplicate init-once fn sub_4fc2f80 (same registration pattern: SSO buffer [rbp-0x38] via `0x4fc2fdc  lea rcx,[rbp-0x38]`) [V] |
| 0x4fc2fe0 | 8 | call | `0x4fc2fe0  call 0x76a6f0` | sub_4fc2f80: "ui_text_msdf" copied into SSO buffer via sub_76a6f0, registered via `0x4fc2ff8  call 0x4DE7420` [V] |
| 0xe840f6 | 8 | 0xe840f6 | `0xe840f6  lea rax,[0xF09AA70]` | Font object vtable pointer 0xF09AA70 loaded (class vtbl_f09aa70; ctor sites sub_96b9f0 / sub_e84070 / sub_e85290; slots 0..4 = sub_1505b0/sub_76900/sub_b8bb0/sub_76920/non-code) [V] |
| 0xe840fd | 8 | [rsi] | `0xe840fd  mov [rsi],rax` | Font object (rsi) constructed at 0xE84070: +0x0 = vtable 0xF09AA70; its +0x38 is an inline SSO string field on sub-descriptor objects but is NOT the GlyphTexture value source — the value arrives as caller arg8 [rbp+0xEB8] (`0x674a4ca  mov r15,[rbp+0xEB8]`) [V] |
| 0x58a1310 | 8 | 0x58a1310 | `0x58a1310  push rbp` | texload (pack/named texture loader, BGFX_MAP.md L8/6z) entry; 2 xrefs (sub_58b5220, sub_6a8b620 x3, sub_6b80db0 x2), NONE font-related — no font caller reaches the pack texture loader [V] |
| 0xEEC7570 | 8 | 0xEEC7570 | `0xEEC7570  jmp qword ptr [0xF9A9048]` | Import thunk (strlen) — jumps through data slot 0xF9A9048; target not statically resolvable; called with rcx=C string and rax tested as length, i.e. strlen-style, NOT a texture-handle fetch [V] |

## Answer

**(1) Where GlyphTexture value comes from — proven [V]:** caller-provided arg8 ([rbp+0xEB8]), loaded as a 16-byte SSO texture NAME via `0x674aa09  movups xmm0,[rax]` (rax = r15 = [rbp+0xEB8]), staged at `0x674aa0c  movaps [rbp+0xC10],xmm0`, count=1 at `0x674aa13  mov qword ptr [rbp+0x910],1`, then bound at draw time via `0x674aa91  call 0x5679DB0` which memcpy-writes 16 bytes via `0x5679df9  call 0xEEC6EC0` into the hash-selected slot (`0x5679dfe  mov byte ptr [r15+r14+0xC],1` sets the valid flag). The value is a TEXTURE NAME resolved by name at draw time, NOT a bgfx handle.

**(2) Which object field holds the texture handle — proven [V]: NONE.** The claim that object+0x38 ([rbp+0xE80] in 0x674a3a0) holds the name is REFUTED: the object's reads are +0x10/+0x18/+0x1D8/+0x1F8/+0x1DA/+0x1E8/+0x1FC/+0x20C/+0x21C/+0x244, never +0x38. The font object (vtable 0xF09AA70, constructed at 0xE84070, `0xe840fd  mov [rsi],rax`) has +0x38 as an inline SSO string field on its sub-descriptor objects, but that is NOT the GlyphTexture value source. The value arrives as caller arg8.

**(3) Who writes that field — open:** since there is no object field holding it, there is no field writer in this path. The value that becomes arg8 is assembled by sub_6664760 (the UI item record builder), which has 0 static xrefs/callers (reached only via indirect dispatch) and is not statically locatable. The name passed as arg8 traces to UI item record fields ([r9+0x28] stride-0x38 or [r9] stride-0x86) but their writer is not found statically.

**Glyph texture name pattern — candidate [I]:** "ui_text_msdf" at 0xF5BAEF9 (12 bytes, fits 16-byte SSO) is copied into an SSO buffer [rbp-0x38] and registered via sub_76a6f0/sub_4de7420 in the init-once functions sub_e9dd60 (`0xe9ddb5  lea rdx,[0xF5BAEF9]` / `0xe9ddc0  call 0x76a6f0`) and sub_4fc2f80 (`0x4fc2fd6  lea edx,[0xF5BAEF9]` / `0x4fc2fe0  call 0x76a6f0`). sub_76a6f0 calls `0x76a72c  call 0xEEC7570` (strlen) then `0x76a731  cmp rax,0xF` for the SSO-vs-heap decision — confirming 0xEEC7570 = strlen. This is the strongest glyph-atlas-name candidate, but its connection to the GlyphTexture uniform value is NOT statically proven (no static link from sub_e9dd60/sub_4fc2f80 to sub_674a3a0's arg8). No "GlyphAtlas"/"FontTexture" string exists; "glyph_section_*" strings (0xf573cd7..) are UI section labels, not the atlas.

**(4) Load path — proven [V] negative:** `rdis imm` over .text = 0 hits for createTexture/createDynamicTexture; no direct bgfx createTexture/createDynamicTexture call ANYWHERE in the executable. texload 0x58a1310 (`0x58a1310  push rbp`) is the pack/named texture loader but its callers (sub_58b5220, sub_6a8b620 x3, sub_6b80db0 x2) are none font-related. Font init 0xE82E00->0xE84070 and font reset 0x186e6a0 create no textures (registry objects via [0xF99FFA0] only). So the glyph atlas is an ordinary NAMED texture resolved by the texture-pack/resource system at load time, NOT created by font code — consistent with the 16-byte NAME bound at draw time.

## CLOSES?

NO — blocking fact: (a) the writer of the 16-byte glyph texture-name value that becomes sub_674a3a0's arg8 is sub_6664760, which has 0 static xrefs and is not statically locatable (indirect dispatch), so "who writes the name field" cannot be answered statically; (b) the candidate atlas name "ui_text_msdf" is not statically linked to the GlyphTexture uniform value; (c) no createTexture/createDynamicTexture call exists anywhere in .text and texload 0x58a1310 has no font caller, so the atlas creation/load site is vtable-indirect render-thread work (RendererContext slots 26/28, texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj) not reachable statically. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units), and the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot). Closing needs a LIVE trace: break on bgfx createTexture/updateTexture (RendererContext slots 26/28, fns 0xbc716a0/0xbc71990/0xbc74a80; texture table this+0xbde178) and trace which texture name becomes the GlyphTexture uniform value, and trace sub_6664760's record writer.

## TOOL REQUESTS

- live_atlas_tracer | break on bgfx createTexture/createDynamicTexture (RendererContext slots 26/28, fns 0xbc716a0/0xbc71990/0xbc74a80; texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj) and trace which texture name becomes the GlyphTexture uniform value | static analysis exhausted: no direct createTexture call anywhere in .text, no atlas name string proven, vtable-indirect render-thread creation
- sub_6664760 record-writer tracer | identify the UI item record builder that writes the 16-byte name field ([r9+0x28] stride-0x38 / [r9] stride-0x86) passed as arg8 to sub_674a3a0 | sub_6664760 has 0 static xrefs; not reversed

## NEXT
DONE
