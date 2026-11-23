## NEXT
DONE

# Unit U-EL14c: L14c Text/font — glyph atlas (retry; pending part of U-EI5c r2 12/12)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending". The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c/U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be, all in UI extractor 0x674a3a0). This unit covers ONLY the pending part: the GLYPH ATLAS — where the GlyphTexture uniform value comes from, which field holds it, who writes that field.

Orchestrator fact (verified): `0x4f78966  call 0xEEC7570` is an import thunk called with rcx = C string and rax tested as a length (strlen-style), NOT a texture-handle fetch. Do NOT re-trace that path.

Per U-EI5c r2 (12/12 [V]): in extractor 0x674a3a0 the GlyphTexture uniform value is a 16-byte SSO texture NAME string (not a bgfx handle), bound at draw time via `0x674aa91  call 0x5679DB0` -> `0x5679df9  call 0xEEC6EC0` (memcpy 16). The glyph atlas is therefore an ordinary NAMED texture resolved by the texture-pack/resource system, not created by font code.

## New findings this run (NOT redone from prior notes)

- Extractor 0x674a3a0 has exactly ONE static caller: UI group visitor dispatch sub_6664a00 (`xref.py callers 0x674a3a0` -> `0x6664a00`), with two call sites: stride-0x38 records at `0x6664d46  call 0x674A3A0` and stride-0x86 records at `0x6664f4a  call 0x674A3A0`.
- Visitor case 3 (0x6664c83..0x6664d51, reg r9, stride-0x38 records): `0x6664cb0  mov r10,[r9+0x28]` reads record field +0x28 (texture-NAME pointer), `0x6664cf5  mov [rsp+0x38],r10` stages it as extractor arg8, then `0x6664d46  call 0x674A3A0`. Stride-0x86 path: `0x6664eb1  mov r13,[r9]`, `0x6664ef9  mov [rsp+0x38],r13`, `0x6664f4a  call 0x674A3A0`. So the GlyphTexture name comes from the UI item record field, not a font object field.
- Record builder sub_6664760 ("FrameBuilder - Insert UI") calls the dispatch: `0x66648c8  call 0x6664A00`. It builds each record from an object at rsi: `0x66647de  mov rax,[rsi+0xF0]` (object field +0xF0 -> record [rbp-0x28]) and `0x66647d7  movups xmm0,[rbx]` (16 bytes from 2nd arg rbx -> record [rbp-0x40]); also reads [rsi+0x28]->[+0x18], [rsi+0x268], [rsi+0x380], [rsi+0x100], [rsi+0x260], [rsi+0x20]->[+0x3A8], [rsi+0x36C], [rsi+0x358]->[+0x6A1], [rsi+0x370].
- `xref.py callers 0x6664760` -> no static inbound callers (0 xrefs). The address is referenced only as a .rdata pointer at 0xf2be218 (`xref.py ptr 0x6664760`), i.e. reached via indirect dispatch (vtable/function-pointer slot), so its caller/writer is not statically locatable.
- `xref.py str "ui_text_msdf"` (0xF5BAEF9, candidate atlas name from prior runs) -> exactly 2 refs, `0xe9ddb5` in sub_e9dd60 and `0x4fc2fd5` in sub_4fc2f80, both registration init-once fns; NOT linked to sub_674a3a0's arg8. Dead end [V].
- No createTexture/createDynamicTexture call anywhere in .text (imm scan 0 hits); texload 0x58a1310 (`0x58a1310  push rbp`) callers sub_6b84680/sub_6ea2df0, none font-related. Atlas load site not tieable to font code statically [V].
- Object+0x38 claim (prior r2) refuted: full sub_674a3a0 listing reads object [rbp+0xE80] fields +0x10/+0x18/+0x1D8/+0x1F8/+0x1DA/+0x1E8/+0x1FC/+0x20C/+0x21C/+0x244, never +0x38; the GlyphTexture value arrives as caller arg8 [rbp+0xEB8] [V].

## Offset table (one row per distinct offset; all sites listed; verbatim instr lines; sizes from instruction)

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) hashed via `0x674dcb4  call 0x79580`, hash stored at 0x129FA178 — uniform registration at init, NOT a texture-creation site [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: caller arg8 pointer loaded into r15 [V] |
| 0x674aa09 | 16 | [rax] = *[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME loaded from caller-provided arg8 — GlyphTexture uniform value is a NAME, not a bgfx handle [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as uniform value buffer [V] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | Draw binding count = 1 (=> 16-byte copy) [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind: writer object (rcx=r15=[rbp+0xB70]) passes {index,flag}@rdx and {count=1,namePtr}@r8 to sub_5679DB0 [V] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr=[rdi+8], size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the hash-selected binding slot, NOT a bgfx handle [V] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0x0C valid/bound flag set to 1 [V] |
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | Visitor case 3 (sub_6664a00): stride-0x38 UI record field +0x28 = qword texture-NAME pointer [V descscan2 case 3] |
| 0x6664cf5 | 8 | [rsp+0x38] | `0x6664cf5  mov [rsp+0x38],r10` | Field +0x28 staged as extractor arg8 (8th stack argument) [V] |
| 0x6664d46 | 8 | call | `0x6664d46  call 0x674A3A0` | Extractor call site 1: stride-0x38 records, arg8 = [r9+0x28] name pointer [V] |
| 0x6664eb1 | 8 | [r9] | `0x6664eb1  mov r13,[r9]` | Visitor stride-0x86 path: record field +0x0 read [V] |
| 0x6664ef9 | 8 | [rsp+0x38] | `0x6664ef9  mov [rsp+0x38],r13` | Field +0x0 staged as extractor arg8 [V] |
| 0x6664f4a | 8 | call | `0x6664f4a  call 0x674A3A0` | Extractor call site 2: stride-0x86 records [V] |
| 0x66648c8 | 8 | call | `0x66648c8  call 0x6664A00` | Record builder sub_6664760 ("FrameBuilder - Insert UI") drives the visitor dispatch that calls the extractor [V] |
| 0x66647d7 | 16 | [rbx] | `0x66647d7  movups xmm0,[rbx]` | Record builder: 16 bytes from 2nd argument rbx written into record buffer [rbp-0x40] [V] |
| 0x66647de | 8 | [rsi+0xF0] | `0x66647de  mov rax,[rsi+0xF0]` | Record builder: object field +0xF0 read into record buffer [rbp-0x28] [V] |
| 0xe9ddb5 | 8 | 0xe9ddb5 | `0xe9ddb5  lea rdx,[0xF5BAEF9]` | "ui_text_msdf" (12 bytes, fits 16-byte SSO) candidate glyph-atlas NAME; `xref str ui_text_msdf` = only 2 refs (0xe9ddb5 sub_e9dd60, 0x4fc2fd5 sub_4fc2f80), both registration init-once, NOT linked to GlyphTexture arg8 -> dead end [V] |
| 0xEEC7570 | 8 | 0xEEC7570 | `0xEEC7570  jmp qword ptr [0xF9A9048]` | Import thunk = strlen-style (rcx = C string, rax tested as length via `0x76a731  cmp rax,0xF` in sub_76a6f0 SSO setter) — NOT a texture-handle fetch [V] |
| 0x58a1310 | 8 | 0x58a1310 | `0x58a1310  push rbp` | texload pack/named texture loader entry; callers sub_6b84680/sub_6ea2df0 only, NONE font-related — no font caller reaches the pack texture loader [V] |

## Answer

**(1) Where GlyphTexture value comes from — proven [V]:** caller-provided arg8 ([rbp+0xEB8]), loaded as a 16-byte SSO texture NAME via `0x674aa09  movups xmm0,[rax]` (rax = r15 = [rbp+0xEB8]), staged at `0x674aa0c  movaps [rbp+0xC10],xmm0`, count = 1 at `0x674aa13  mov qword ptr [rbp+0x910],1`, then bound at draw time via `0x674aa91  call 0x5679DB0`, which memcpy-writes 16 bytes via `0x5679df9  call 0xEEC6EC0` into the hash-selected slot (`0x5679dfe  mov byte ptr [r15+r14+0xC],1` sets the valid flag). The value is a TEXTURE NAME resolved by name at draw time, NOT a bgfx handle.

**(2) Which object field holds the texture handle — proven [V]: NONE.** The object+0x38 claim is refuted: object [rbp+0xE80] in 0x674a3a0 never reads +0x38 (fields read: +0x10/+0x18/+0x1D8/+0x1F8/+0x1DA/+0x1E8/+0x1FC/+0x20C/+0x21C/+0x244). The value arrives as caller arg8; the field that holds it is the UI item record field +0x28 (stride-0x38 records, `0x6664cb0  mov r10,[r9+0x28]`) or +0x0 (stride-0x86 records, `0x6664eb1  mov r13,[r9]`), staged as arg8 at `0x6664cf5` / `0x6664ef9`.

**(3) Who writes that field — NOT FOUND (blocking):** the record builder sub_6664760 writes the record fields ([rbp-0x28] from object+0xF0 via `0x66647de`, [rbp-0x40] 16 bytes from rbx via `0x66647d7`) and calls the dispatch at `0x66648c8  call 0x6664A00`, but `xref.py callers 0x6664760` returns 0 static inbound callers; it is reached only via an unresolved .rdata pointer at 0xf2be218 (indirect dispatch). So the writer of sub_6664760 (who fills the record name field passed as arg8) is not statically locatable.

**Glyph texture name pattern — dead end [V]:** "ui_text_msdf" at 0xF5BAEF9 has exactly 2 xrefs (0xe9ddb5, 0x4fc2fd5), both registration init-once; no static link to the GlyphTexture uniform value. No "GlyphAtlas"/"FontTexture" string exists; "glyph_section_*" strings are UI section labels, not the atlas. The draw-time name comes from the UI record field (above).

**Load path — proven [V] negative:** no createTexture/createDynamicTexture call ANYWHERE in .text; texload 0x58a1310 has no font caller; font init 0xE82E00->0xE84070 and font reset 0x186e6a0 create no textures. The glyph atlas is an ordinary NAMED texture resolved by the texture-pack/resource system at load time; its creation/load site is not statically tieable to font code.

## CLOSES?

NO — single blocking fact: sub_6664760 (the UI record builder that writes the record name field [r9+0x28]/[r9+0] which becomes sub_674a3a0 arg8 and thereby the GlyphTexture uniform value) has 0 static inbound callers (only an unresolved .rdata pointer at 0xf2be218, indirect dispatch), so "who writes the name field" cannot be answered statically; and with zero createTexture/createDynamicTexture calls in .text and no font caller of texload 0x58a1310, the glyph atlas creation/load site is likewise not statically locatable. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units), and the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot; the name source is the UI record field, not an object field). Closing needs a live trace: break on sub_6664760's inbound caller (resolve .rdata ptr 0xf2be218) and on bgfx createTexture/updateTexture (RendererContext slots 26/28, texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj) to catch which texture name becomes the GlyphTexture uniform value.

## TOOL REQUESTS

None — all evidence gathered with rdis.exe dis/fn, xref.py callers/str/ptr; no helper script needed.
