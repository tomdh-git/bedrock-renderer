## NEXT
DONE

# UNIT U-EI5c: Text/font SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas — pending part of checklist item I5c

## Goal (pending part only — proven parts not redone)

Closed already (U-I5c verify 97/97, U-EL14c verify 7/7): SDF glyph uniforms GlyphTexture/GlyphHeight/GlyphSmoothRadius registered in extractor 0x674a3a0 (0x674dca3/0x674ddbe/0x674e06a via FNV 0x79580 -> 0x73150), FONT_TYPE+MSDF permutation via 0xF2EA00 (0x674d2bf/0x674d6be), font init 0xE82E00->0xE84070 x5 (vtable 0xF09AA70), font reset 0x186e6a0 (ClearAndResetFontData, callers 0x8F6919, 0x104237e).

This unit covers ONLY what remained open per the orchestrator hint: at draw time, follow where the GlyphTexture uniform VALUE comes from (set near 0x674dca3 in 0x674a3a0), which field holds it, who writes that field, and where the glyph atlas texture is created/updated.

NEW ANGLES tried in this unit (not redone from r1-r12):
- descscan2 --visitor ui --case 3 (UIText case 0x6664c83..0x6664d51, reg r9): confirmed the UIText description field +0x28 is READ as a qword at `0x6664cb0  mov r10,[r9+0x28]` and staged as extractor arg8 at `0x6664cf5  mov [rsp+0x38],r10`; stride-0x38 record loop `0x6664cbb  add r9,0x38`. [V] — this is the field that holds the glyph texture name.
- xref.py str "glyph_": only UI section labels (glyph_section_mashup/audio/addon/skin/resource_pack/world at 0xf573cd7..), NO glyph-atlas name string. [V]
- xref.py str "font/": whole-exe scan timed out (not re-run).
- livemem: NOT actionable — docs/data/live/_status.txt = DONE, game not running; no current target address to read. [V]
- r2's "object+0x38 SSO name" claim refuted: full sub_674a3a0 listing contains no read of [rbp+0xE80]+0x38; object fields read are +0x10/+0x18/+0x1D8...+0x244.
- Store scan: no write to [rbp+0xBA0]/[rbp+0xBAA] (uniform slot array base/count) anywhere in sub_674a3a0 0x674a3a0..0x674abef — array initializer not located statically.
- sub_6664760 (UI record builder, sole caller of sub_6664a00 per preflight: 2 xrefs into 0x674a3a0) has 0 static xrefs — not reversed, not located.
- bgfx createTexture/createDynamicTexture: zero direct calls in .text (imm scan 0 hits for slot 26/28 fns 0xe8143c0/0xe814a70; command-buffer byte 14 = createTexture goes via render thread). Texture creation is vtable-indirect (RendererContext slots 26/28, texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj). texload 0x58a1310 callers are sub_6b84680/sub_6ea2df0 only — neither font-related.

## Offset table (one row per distinct offset; all sites listed; verbatim instr lines; sizes from instruction)

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[?]) |
|---|---|---|---|---|
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | UIText description field +0x28 = qword texture-NAME pointer, read in visitor case 3 (0x6664c83..0x6664d51); staged as extractor arg8 via `0x6664cf5  mov [rsp+0x38],r10`; stride-0x38 record loop `0x6664cbb  add r9,0x38` [V descscan2 case 3] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: arg8 = caller-provided pointer loaded into r15 [V preflight 0x674a3a0] |
| 0x674a9ff | 8 | rax=r15=[rbp+0xEB8] | `0x674a9ff  mov rax,r15` | rax = caller pointer; feed for the 16-byte load at 0x674aa09 [V preflight] |
| 0x674aa09 | 16 | [rax] = *[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte TEXTURE NAME loaded from caller-provided pointer — GlyphTexture uniform value is a NAME, not a bgfx handle [V preflight] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as uniform value buffer [V preflight] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | draw binding count = 1 (=> 16-byte copy) [V preflight] |
| 0x674aa1e | 8 | [rbp+0x918] | `0x674aa1e  mov [rbp+0x918],rbx` | draw binding namePtr = rbx (name pointer) [V preflight] |
| 0x674aa25 | 8 | [rbp+0xBA0] | `0x674aa25  mov rax,[rbp+0xBA0]` | base of the 16-byte-entry uniform slot array (= writer stack struct [rbp+0xB70] + 0x30) [V preflight] |
| 0x674aa2c | 2 | [rbp+0xBAA] | `0x674aa2c  movzx r8d,word ptr [rbp+0xBAA]` | entry count u16 of the array [V preflight] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | search key = FNV-1a hash of "GlyphTexture" [V preflight] |
| 0x674aa50 | 8 | [rcx] | `0x674aa50  mov r10,[rcx]` | array entry[0] = qword pointer to uniform record; walk stride `0x674aa59  add rcx,0x10` [V preflight] |
| 0x674aa53 | 8 | [r10+0x28] | `0x674aa53  cmp [r10+0x28],r8` | [uniform-record+0x28] = name hash compared with the GlyphTexture hash; match selects the slot [V preflight] |
| 0x674aa6f | 4 | ecx | `0x674aa6f  shr ecx,4` | slot index = (matched entry − array base) / 16 [V preflight] |
| 0x674aa72 | 2 | [rbp+0x5F0] | `0x674aa72  mov [rbp+0x5F0],cx` | u16 slot index stored; [V live] live capture docs/data/live/glyph_bind.txt: index 0x000A = 10 (GlyphTexture slot), flag 0x01 — 30/30 samples [V preflight+live] |
| 0x674aa79 | 1 | [rbp+0x5F2] | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | u8 flag byte = 1 stored next to the index [V preflight+live] |
| 0x674aa80 | 8 | rdx=&[rbp+0x5F0] | `0x674aa80  lea rdx,[rbp+0x5F0]` | {u16 index, u8 flag} argument passed as rdx to sub_5679DB0 [V preflight+live] |
| 0x674aa87 | 8 | r8=&[rbp+0x910] | `0x674aa87  lea r8,[rbp+0x910]` | {qword count=1, qword namePtr} argument passed as r8 to sub_5679DB0; [V live] R8 struct begins `0100000000000000` (count=1) then namePtr [V preflight+live] |
| 0x674aa8e | 8 | rcx=r15=[rbp+0xB70] | `0x674aa8e  mov rcx,r15` | writer object (stack struct at [rbp+0xB70]; +0x28 slot table base, +0x20 limit, +0x30 entry-array base = [rbp+0xBA0], +0x70 FNV-1a hash state) passed as this to sub_5679DB0 [V preflight] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | draw-time GlyphTexture bind: writer writes the 16-byte name into the hash-selected slot [V preflight+live] |
| 0x5679dbf | 2 | [rdx] | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679DB0 (UniformBlock::setUniform): index u16 read from {index,flag} param (a1+0x0) [V rdis] |
| 0x5679dc3 | 8 | [rcx+0x30] | `0x5679dc3  mov r15,[rcx+0x30]` | sub_5679DB0: r15 = writer+0x30 = entry-array base [V rdis] |
| 0x5679dcb | 2 | [r15+r14+8] | `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` | sub_5679DB0: entry[index].+0x08 u16 = slot byte-offset into binding table [V rdis] |
| 0x5679ded | 8 | [rsi+0x28] | `0x5679ded  add rcx,[rsi+0x28]` | sub_5679DB0: dst = writer+0x28 + slot-offset (slot table base + offset) [V rdis] |
| 0x5679df1 | 8 | [rdi+8] | `0x5679df1  mov rdx,[rdi+8]` | sub_5679DB0: src = name pointer from draw binding a2+0x8 = [rbp+0x918] = rbx [V rdis] |
| 0x5679df5 | 8 | r8 | `0x5679df5  shl r8,4` | sub_5679DB0: size = count*16 = 16 [V rdis] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr, 16) — WRITES a 16-byte TEXTURE NAME into the binding slot, NOT a bgfx handle [V rdis] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0x0C valid/bound flag set to 1 [V rdis] |
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) hashed via `0x674dcb4  call 0x79580`, hash stored at 0x129FA178, registered via 0x73150 — uniform registration at init (proven in U-I5c), NOT a texture-creation site [V rdis] |
| 0x674dcb4 | 8 | call | `0x674dcb4  call 0x79580` | FNV-1a 64 hash of "GlyphTexture" [V rdis] |

## Decode of sub_5679DB0 (writer binder) — proven [V]

sub_5679DB0(rcx=writer [rbp+0xB70], rdx=&{u16 index, u8 flag} [rbp+0x5F0], r8=&{u16 count=1, qword namePtr} [rbp+0x910]):
- `0x5679dbf  movzx r14d,word ptr [rdx]` index u16; `0x5679dc3  mov r15,[rcx+0x30]` entry-array base (writer+0x30); `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` entry[index].+0x08 u16 slot byte-offset; `0x5679dd1  cmp [rsi+0x20],rcx` bounds-check vs writer+0x20 limit (fail -> error path `0x5679f0f  call 0x78ED0` / `0x5679f14  int3`); `0x5679ded  add rcx,[rsi+0x28]` dst = writer+0x28+offset; `0x5679df1  mov rdx,[rdi+8]` src = namePtr; `0x5679df5  shl r8,4` size = count*16 = 16; `0x5679df9  call 0xEEC6EC0` memcpy 16 bytes; `0x5679dfe  mov byte ptr [r15+r14+0xC],1` entry[index].+0x0C flag = 1; `0x5679efe  mov [rsi+0x70],r8` mixes index + name hash (0x19932c0) into writer+0x70 FNV-1a state. **The slot therefore receives a 16-byte TEXTURE NAME, not a bgfx handle.**

## Array lookup at draw time — proven [V] (+ [V live])

At 0x674aa25-0x674aa91 the extractor walks the 16-byte-entry array at [rbp+0xBA0] (writer+0x30; entries = {qword uniform-record-ptr @+0, u16 slot-offset @+0x8, u8 flag @+0xC}); `0x674aa50  mov r10,[rcx]`, `0x674aa53  cmp [r10+0x28],r8` matches [record+0x28] name hash against the GlyphTexture hash from `0x674aa42  mov r8,[0x129FA178]`; match -> `0x674aa72  mov [rbp+0x5F0],cx` slot index, `0x674aa79  mov byte ptr [rbp+0x5F2],1` flag; then `0x674aa91  call 0x5679DB0`. Live capture: index 0x000A = 10 (GlyphTexture slot), flag 0x01 — 30/30 samples — and R8 = {count=1, namePtr}, exactly matching sub_5679DB0's args. [V] [V live docs/data/live/glyph_bind.txt]

## Value provenance — proven [V]

The 16 bytes bound as GlyphTexture are loaded from caller-provided arg8: `0x674a4ca  mov r15,[rbp+0xEB8]`, `0x674a9ff  mov rax,r15`, `0x674aa09  movups xmm0,[rax]` (16 bytes from *[[rbp+0xEB8]]), staged `0x674aa0c  movaps [rbp+0xC10],xmm0`. descscan2 case 3 confirmed sub_6664a00 (sole caller of sub_674a3a0, 2 sites) reads UIText description field +0x28 as the name pointer (`0x6664cb0  mov r10,[r9+0x28]`) and stages it as arg8 (`0x6664cf5  mov [rsp+0x38],r10`) at call site 0x6664d46 (stride-0x38 records); an alternate stride-0x86 record path reads field +0x00 at `0x6664eb1` staged at 0x6664f4a (proven pattern [I] from r12, instr line not re-verified verbatim). Independently, sub_BCABA00 resolves a texture object through Q's static per-class texture-name table ([vtable+0x440], stride 0x88, entry+0x30 name / +0x48 size / +0x80 valid flag; global bucket hash-chain, strcmp, refcount bump) and its entry+0x30 name pointer becomes rbx -> [rbp+0x918] namePtr. Q's class is not statically identifiable (vtable indirection), so the table's content/writer is not pinned to a font object. [V for bind path; I for BCABA00 attribution]

## Glyph atlas — what it IS (proven [V] + [I])

- No "GlyphAtlas" / "FontTexture" string exists in .rdata (r12; xref str "glyph_" returns only UI section labels glyph_section_*). [V]
- The glyph atlas is bound BY NAME at draw time (16-byte name), never as a bgfx handle, never created by font code (no createTexture/createDynamicTexture call anywhere in .text; font init 0xE82E00->0xE84070 and font reset 0x186e6a0 create no textures — registry objects only via [0xF99FFA0]). [V]
- Font texture paths are built at runtime as `<name>_ttf.png` / `<name>_ttfmsdf.png` by 0x4fb3870 / 0x4fbe0c0 (per docs/functions/ui_font_text_leads.md) — pre-generated PNG + .info sidecar per font (MSDF / TrueType FONT_TYPE values), i.e. pack-loaded named textures, not rasterised at runtime. [I from 0x4fb3870/0x4fbe0c0 string refs "_ttf"/".png", "_ttfmsdf"/".png"]
- texload 0x58a1310 (pack/named loader, BGFX_MAP.md L8) has no font caller (callers sub_6b84680/sub_6ea2df0 only); exact atlas creation call site not statically tieable to font code. [V]

## What I tried that failed (new angles, not redone)

- r2's "object+0x38 SSO name" claim: refuted — full sub_674a3a0 listing contains no read of [rbp+0xE80]+0x38; the draw-time value is loaded from caller-provided arg8 [rbp+0xEB8] via `0x674aa09  movups xmm0,[rax]` — 16 bytes, a texture NAME, not a handle.
- Store scan for the array initializer: no write to [rbp+0xBA0] or [rbp+0xBAA] exists anywhere in sub_674a3a0 0x674a3a0..0x674abef (all memory stores enumerated). The array base/count writer is not located statically.
- sub_6664760 (UI record builder) has 0 static xrefs and is not reversed — the writer of UIText description field [r9+0x28] (the glyph texture name) is not located.
- Texture-name strings: xref str "glyph_" = only section labels; no glyph-atlas name string. "font/" whole-exe scan timed out (not re-run).
- livemem: game not running (_status.txt = DONE) — no target address to read; noted as live-trace request.
- bgfx creation: zero direct createTexture/createDynamicTexture/slot-26 calls in .text; all texture creation vtable-indirect render-thread work (RendererContext slots 26/28, texture table this+0xbde178 stride 0xB8). texload 0x58a1310 has no font caller.

## Answer

**GlyphTexture is bound BY NAME (16-byte texture name from the UIText description field [r9+0x28]), not as a bgfx handle, and not created by font code.** The draw-time bind: sub_674a3a0 hashes "GlyphTexture" (`0x674dca3  lea rdx,[0xF5C6DD7]` -> `0x674dcb4  call 0x79580` -> hash at 0x129FA178), walks the 16-byte-entry uniform slot array at [rbp+0xBA0] matching [record+0x28] name hash, selects slot index (live: 0x000A = 10), then sub_5679DB0 memcpy's 16 bytes from the namePtr into the slot and sets the valid flag. The 16-byte name is the UIText description field [r9+0x28] (descscan2 case 3: `0x6664cb0  mov r10,[r9+0x28]`). The actual glyph atlas texture object is created elsewhere — a named pack texture (pre-generated `<font>_ttf.png`/`<font>_ttfmsdf.png`) resolved by the texture/resource system — not by font code and not via a direct createTexture call.

**Glyph atlas texture creation/update site — NOT FOUND (blocking):** no direct bgfx createTexture/createDynamicTexture call anywhere in the binary; no glyph-atlas name string in .rdata; font paths create no textures; texture creation is vtable-indirect render-thread work (RendererContext slots 26/28, texture table this+0xbde178 stride 0xB8). **Writer of the UIText field [r9+0x28] — NOT FOUND:** sub_6664760 (record builder) has 0 static xrefs; no store to [rbp+0xBA0]/[rbp+0xBAA] (uniform slot array base/count) in sub_674a3a0 before 0x674aa40.

## CLOSES?

NO — single blocking fact: the glyph atlas texture creation/update site AND the writer of the UIText description field [r9+0x28] (the glyph texture name, sub_6664760, 0 static xrefs) are not statically locatable; game not running so livemem unavailable. Everything else IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (U-I5c/U-EL14c), and the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot; index 0x000A slot 10 confirmed [V live]; UIText field [r9+0x28] confirmed [V descscan2]). Closing needs a LIVE trace: break on bgfx createTexture/updateTexture (RendererContext slots 26/28, fns 0xe8143c0/0xe814a70; texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj) and on the UIText record builder to find who writes [r9+0x28].

## TOOL REQUESTS

- live_atlas_tracer | break on bgfx createTexture/updateTexture (RendererContext slots 26/28, fns 0xe8143c0/0xe814a70; texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj) and trace which texture name becomes the GlyphTexture uniform value | static analysis exhausted: no direct createTexture call anywhere in .text, no atlas name string, vtable-indirect render-thread creation
- sub_6664760 record-writer tracer | identify the UI item record builder that writes the 16-byte name field ([r9+0x28] stride-0x38 / [r9] stride-0x86) passed as arg8 to sub_674a3a0 | sub_6664760 has 0 static xrefs; not reversed
