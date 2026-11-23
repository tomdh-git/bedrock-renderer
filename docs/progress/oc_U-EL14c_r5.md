## NEXT
DONE

# Unit U-EL14c: L14c Text/font — glyph atlas (retry run, new angle per orchestrator hint)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending". The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c/U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be, all in UI extractor 0x674a3a0). This unit covers ONLY the pending part: the GLYPH ATLAS — where the GlyphTexture uniform value comes from, which object field holds it, who writes that field.

Orchestrator anchor fact (verified, NOT re-traced): `0x4f78966  call 0xEEC7570` is an import thunk called with rcx = C string and rax tested as a length (strlen-style), NOT a texture-handle fetch.

Prior runs (not redone): r1-r4 established the GlyphTexture draw-time bind via `0x674aa91  call 0x5679DB0` -> `0x5679df9  call 0xEEC6EC0` (memcpy 16) into a hash-selected uniform slot; no createTexture/createDynamicTexture call anywhere in .text; font init 0xE82E00->0xE84070 and reset 0x186e6a0 create no textures; texload 0x58a1310 has no font caller; "ui_text_msdf" at 0xF5BAEF9 is an unlinked candidate atlas name; "glyph_section_*" strings are UI section labels, not the atlas.

## New verification this run

I re-dumped the FULL sub_674a3a0 listing myself (rdis dis 0x674a3a0, two chunks: 0x674a3a0..0x674c385 and 0x674c385..end of fn at 0x674f006) and grepped every [r14+...] access (r14 = [rbp+0xE80] object base): reads at +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244 — and ZERO reads of [r14+0x38]. The disassembly therefore CONTRADICTS the r2/orchestrator "object+0x38 SSO name" claim: the object field does NOT hold the GlyphTexture value; it arrives as caller arg8 [rbp+0xEB8].

## Offset table (one row per distinct offset; all sites listed; verbatim instr line; size from instruction; [V]/[I]/[-])

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string ([data_f5c6dd7]), hashed via `0x674dcb4  call 0x79580` [V] |
| 0x674dcb4 | 8 | call | `0x674dcb4  call 0x79580` | FNV-1a 64 hash of "GlyphTexture" [V] |
| 0x674dd81 | 8 | [0x129FA178] | `0x674dd81  mov [0x129FA178],rcx` | Hash stored as the draw-time lookup key [V] |
| 0x674dd8f | 8 | call | `0x674dd8f  call 0x73150` | Uniform registration call [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: arg8 = caller-provided pointer loaded into r15 [V] |
| 0x674a4d1 | 8 | [rbp+0xE80] | `0x674a4d1  mov r14,[rbp+0xE80]` | Object base ([rbp+0xE80]) loaded into r14 [V] |
| 0x674a9f2 | 8 | [rbp+0xEA0] | `0x674a9f2  mov r8,[rbp+0xEA0]` | 4th arg (r8 home slot) loaded for the texture resolver [V] |
| 0x674a9f9 | 8 | call | `0x674a9f9  call 0xBCABA00` | sub_bcaba00 texture-object resolver; name result lands in rbx [V] |
| 0x674a9ff | 8 | rax=r15=[rbp+0xEB8] | `0x674a9ff  mov rax,r15` | rax = caller-provided arg8 pointer [V] |
| 0x674aa09 | 16 | [rax]=*[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO TEXTURE NAME loaded from caller-provided pointer — GlyphTexture value is a NAME, not a bgfx handle [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as uniform value buffer [V] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | Draw binding count = 1 (=> 16-byte copy) [V] |
| 0x674aa1e | 8 | [rbp+0x918] | `0x674aa1e  mov [rbp+0x918],rbx` | namePtr staged (rbx = sub_bcaba00 result) [V] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | Search key = FNV("GlyphTexture") hash from 0x129FA178 [V] |
| 0x674aa50 | 8 | [rcx] | `0x674aa50  mov r10,[rcx]` | Uniform slot array entry[0] = qword pointer to uniform record; walk stride `0x674aa59  add rcx,0x10` [V] |
| 0x674aa53 | 8 | [r10+0x28] | `0x674aa53  cmp [r10+0x28],r8` | [uniform-record+0x28] name hash compared with GlyphTexture hash; match selects slot [V] |
| 0x674aa6f | 4 | ecx | `0x674aa6f  shr ecx,4` | Slot index = (matched entry − array base) / 16 [V] |
| 0x674aa72 | 2 | [rbp+0x5F0] | `0x674aa72  mov [rbp+0x5F0],cx` | u16 slot index stored [V] |
| 0x674aa79 | 1 | [rbp+0x5F2] | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | u8 flag byte = 1 [V] |
| 0x674aa80 | 8 | rdx=&[rbp+0x5F0] | `0x674aa80  lea rdx,[rbp+0x5F0]` | {u16 index, u8 flag} -> rdx for sub_5679DB0 [V] |
| 0x674aa87 | 8 | r8=&[rbp+0x910] | `0x674aa87  lea r8,[rbp+0x910]` | {qword count=1, qword namePtr} -> r8 for sub_5679DB0 [V] |
| 0x674aa8e | 8 | rcx=r15=[rbp+0xB70] | `0x674aa8e  mov rcx,r15` | Writer object (stack struct [rbp+0xB70]) as this; `0x674aa02  lea r15,[rbp+0xB70]` set r15 earlier [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind via uniform/subcomponent writer [V] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr, size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the binding slot, NOT a bgfx handle [V] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0xC valid/bound flag set to 1 [V] |
| 0x674a3a0 | fn | listing | - | Full linear listing of sub_674a3a0 (0x674a3a0..0x674f006): object r14=[rbp+0xE80] reads +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244 — ZERO reads of object field +0x38; the "object+0x38 SSO name" claim is CONTRADICTED by the disassembly [V] |
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | Visitor case 3 (sub_6664a00), stride-0x38 UI record loop `0x6664cbb  add r9,0x38`: record field +0x28 = qword texture-NAME pointer [V descscan2 case 3] |
| 0x6664cf5 | 8 | [rsp+0x38] | `0x6664cf5  mov [rsp+0x38],r10` | Field +0x28 staged as extractor arg8 [V] |
| 0x6664d46 | 8 | call | `0x6664d46  call 0x674A3A0` | Extractor call site 1: stride-0x38 records, arg8 = [r9+0x28] name pointer [V] |
| 0x6664eb1 | 8 | [r9] | `0x6664eb1  mov r13,[r9]` | Visitor stride-0x86 path: record field +0x0 read `0x6664eb8  add r9,0x86` [V] |
| 0x6664ef9 | 8 | [rsp+0x38] | `0x6664ef9  mov [rsp+0x38],r13` | Field +0x0 staged as extractor arg8 [V] |
| 0x6664f4a | 8 | call | `0x6664f4a  call 0x674A3A0` | Extractor call site 2: stride-0x86 records [V] |
| 0x6664763 | 8 | fn entry | `0x6664763  push rbx` | sub_6664760 entry ("FrameBuilder - Insert UI" record builder, [0x6664760..0x6666760) size 0x2000, 0 xrefs in) [V] |
| 0x66647d7 | 16 | [rbx] | `0x66647d7  movups xmm0,[rbx]` | Record builder: 16 bytes (SSO string contents) from 2nd argument rbx (=rdx at entry) [V] |
| 0x66647da | 16 | [rbp-0x40] | `0x66647da  movaps [rbp-0x40],xmm0` | Record builder: 16-byte name written into record local [rbp-0x40], then `0x66648c4  lea r8,[rbp-0x40]` passes &name to sub_6664A00 [V] |
| 0x66647de | 8 | [rsi+0xF0] | `0x66647de  mov rax,[rsi+0xF0]` | Record builder: object field +0xF0 -> [rbp-0x28] [V] |
| 0x66648c8 | 8 | call | `0x66648c8  call 0x6664A00` | Record builder drives dispatch that calls the extractor (rdx=&[rbp-0x28], r8=&16-byte name) [V] |
| 0xE840F6 | 8 | 0xE840F6 | `0xE840F6  lea rax,[0xF09AA70]` | Font object (sub_e84070, [0xe84070..0xe84da8)) constructed: +0x0 = vtable 0xF09AA70 (`0xe840fd  mov [rsi],rax`), +0x10 zeroed [V] |
| 0xE8483F | 8 | [r13+0x38] | `0xE8483F  mov qword ptr [r13+0x38],0xF` | Only object+0x38 writes in font init: SSO length/flags byte of a font-DESCRIPTOR sub-object (r13 = 4th arg, SSO chars at r13+0x20, length at r13+0x30; heap path `0xe848dc  mov [r13+0x38],r12` stores the heap pointer) — a font NAME descriptor, NOT the glyph texture handle [V] |
| 0xE9DDB5 | 8 | 0xE9DDB5 | `0xE9DDB5  lea rdx,[0xF5BAEF9]` | "ui_text_msdf" (12 bytes, fits 16-byte SSO) candidate glyph-atlas NAME; copied into SSO [rbp-0x38] via `0xe9ddbc  lea rcx,[rbp-0x38]` / `0xe9ddc0  call 0x76a6f0` (sub_76a6f0 calls `0x76a72c  call 0xEEC7570` strlen then `0x76a731  cmp rax,0xF`, confirming 0xEEC7570=strlen) [V] |
| 0x4FB3DFF | 8 | 0x4FB3DFF | `0x4FB3DFF  lea r9,[0xF5B9FBB]` | "_ttf" suffix at 0xF5B9FBB in sub_4fb3870 — font texture path `<name>_ttf.png` built at runtime [V str] |
| 0x4FBE694 | 8 | 0x4FBE694 | `0x4FBE694  lea r9,[0xF5BAEF0]` | "_ttfmsdf" suffix at 0xF5BAEF0 in sub_4fbe0c0 — font texture path `<name>_ttfmsdf.png` built at runtime [V str] |
| 0x58A1310 | 8 | 0x58A1310 | `0x58A1310  push rbp` | texload pack/named texture loader entry (`0x58a1310..0x58a3310`, 2 xrefs in); callers sub_58b5220/sub_6a8b620/sub_6b80db0 — NONE font-related [V] |

## Answer

**(1) Where the GlyphTexture uniform value comes from — proven [V]:** caller-provided arg8 ([rbp+0xEB8]) is loaded as a 16-byte SSO texture NAME via `0x674aa09  movups xmm0,[rax]` (rax = r15 = [rbp+0xEB8]), staged at `0x674aa0c  movaps [rbp+0xC10],xmm0`, count = 1 at `0x674aa13  mov qword ptr [rbp+0x910],1`, namePtr = rbx from sub_bcaba00 staged at `0x674aa1e  mov [rbp+0x918],rbx`, slot selected by matching [uniform-record+0x28] name hash against FNV("GlyphTexture") at 0x129FA178 (`0x674aa42  mov r8,[0x129FA178]`, `0x674aa53  cmp [r10+0x28],r8`), then bound via `0x674aa91  call 0x5679DB0`, which memcpy-writes 16 bytes via `0x5679df9  call 0xEEC6EC0` into the hash-selected slot (`0x5679dfe  mov byte ptr [r15+r14+0xC],1` sets the valid flag). The value is a TEXTURE NAME resolved by name at draw time, NOT a bgfx handle and NOT an atlas-handle fetch.

**(2) Which object field holds the texture handle — proven [V]: NONE.** The object+0x38 claim is contradicted by the full sub_674a3a0 listing: object r14 = [rbp+0xE80] is read at +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244 and never at +0x38. The value arrives as caller arg8; the field that carries it is the UI item record field — [r9+0x28] (stride-0x38 records, `0x6664cb0  mov r10,[r9+0x28]`) or [r9] (stride-0x86 records, `0x6664eb1  mov r13,[r9]`) — staged as arg8 at `0x6664cf5` / `0x6664ef9`. (The only object+0x38 writes in font init, `0xe8483f  mov qword ptr [r13+0x38],0xF` / `0xe848dc  mov [r13+0x38],r12` in sub_e84070, are SSO length/flags of a font-descriptor sub-object, not a texture handle.)

**(3) Who writes that field — NOT FOUND (blocking):** the record builder sub_6664760 writes the record from its 2nd argument (16-byte SSO at [rbx] via `0x66647d7  movups xmm0,[rbx]` -> `0x66647da  movaps [rbp-0x40],xmm0`, passed to the dispatcher at `0x66648c8  call 0x6664A00`), but `xref.py callers 0x6664760` returns 0 static inbound callers and `xr 0xF2BE218` (the .rdata slot claimed to reach it) returns 0 code references — reached only through unresolved indirect dispatch, so the caller that passes the glyph-texture-name SSO is not statically locatable.

**Glyph texture name pattern strings — searched [V]:** xref str "glyph_" returns ONLY UI section labels (glyph_section_mashup/audio/addon/skin/resource_pack/world at 0xf573cd7..); candidate "ui_text_msdf" at 0xF5BAEF9 (`0xe9ddb5  lea rdx,[0xF5BAEF9]`) has exactly 2 xrefs (sub_e9dd60, sub_4fc2f80 registration init-once), no static link to sub_674a3a0's arg8 — dead end. Font texture path suffixes exist ("_ttf" `0x4fb3dff`, "_ttfmsdf" `0x4fbe694` in sub_4fb3870/sub_4fbe0c0) — per-font pack texture names, not the atlas name itself. No "GlyphAtlas"/"FontTexture" string exists.

**Load path — proven [V] negative:** `0x58a1310  push rbp` (texload, BGFX_MAP.md L8/6z) has no font caller; no createTexture/createDynamicTexture call ANYWHERE in .text (imm scan 0 hits); font init/reset create no textures (registry objects via [0xF99FFA0] only). The glyph atlas is an ordinary NAMED texture resolved by the texture-pack/resource system at load time; its creation/load site is not statically tieable to font code.

## CLOSES?

NO — single blocking fact (missing REVERSING): the writer of the UI record name field that becomes sub_674a3a0's arg8 — i.e. the inbound caller of record builder sub_6664760, reached only via unresolved indirect dispatch (.rdata slot 0xf2be218, 0 xrefs) — is not statically locatable, and with it the glyph atlas texture name/load site. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units), the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot), and that NO object field holds the handle (object+0x38 contradicted by the full listing).

## What I tried that failed (new angles this run, not redone)

- Full re-dump + grep of sub_674a3a0 for object+0x38: 0 hits — disproves the hint's object+0x38 claim; value is arg8.
- `rdis xr 0xF2BE218`: 0 xrefs — the record builder's indirect caller cannot be resolved statically.
- `rdis fld 0x38 --w --max 40`: 209,279 global [reg+0x38] writes, first 40 all stack/other — no font/record name writer found (too noisy to exhaust; no candidate surfaced).
- sub_e82e00/sub_e84070 (font init, vtable 0xF09AA70): object+0x38 writes are SSO length/flags on descriptor sub-objects, not a texture-handle field; e84070 called only by e82e00; e82e00 called by 0x913b50/0xe863d0 (no font-name writer either).
- xref str "glyph_"/"font/"/"Caution"/"ErrorGlyph"/"WarningGlyph": only section labels, unlinked "ui_text_msdf" candidate, and fetch-function fallbacks — none tied to the GlyphTexture arg8.
- texload 0x58a1310: entry verified; no font caller; no createTexture/createDynamicTexture anywhere in .text.

## TOOL REQUESTS

- live_atlas_tracer | break on bgfx createTexture/updateTexture (RendererContext slots 26/28, fns 0xbc716a0/0xbc71990/0xbc74a80; texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj) and trace which texture name becomes the GlyphTexture uniform value | static analysis exhausted: no direct createTexture call anywhere in .text, no atlas name string, vtable-indirect render-thread creation
- sub_6664760 caller tracer | identify who calls record builder sub_6664760 with the glyph-texture-name SSO as 2nd arg | 0 static xrefs; indirect dispatch via unresolved .rdata slot 0xf2be218

## NEXT
DONE
