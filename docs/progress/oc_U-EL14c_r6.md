## NEXT
DONE

# Unit U-EL14c: L14c Text/font — glyph atlas (live-capture retry)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending". BGFX_MAP.md 6ce anchors UI pass extractor 0x674a3a0 and lists "Still pending: glyph atlas management". The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c/U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be, all in UI extractor 0x674a3a0). This unit covers ONLY the pending part: the GLYPH ATLAS — where the GlyphTexture uniform value comes from, which field holds it, who writes that field.

## Blocking fact (single unknown)

The writer of the UI record name field that becomes sub_674a3a0's arg8 — i.e. the inbound caller of record builder sub_6664760 — is not statically locatable: `xref.py callers 0x6664760` = 0 (no static inbound callers) and the only reference to 0x6664760 is an unresolved .rdata pointer at 0xf2be218 (indirect dispatch, slot 0xf2be218). With it unknown: the 16-byte glyph atlas NAME passed as arg8, and the atlas name's load site. No createTexture/createDynamicTexture call exists ANYWHERE in .text (imm scan, 0 hits, prior runs), texload 0x58a1310 has no font caller, and no "GlyphAtlas"/"FontTexture" string exists — so the atlas is an ordinary NAMED texture resolved by the texture-pack/resource system; its identity must come from the live capture.

## Live capture queue — new angle this run (static angles exhausted)

Per the orchestrator hint, instead of more static angles I queued two log-only captures on the running game (game has text on screen). Both names already exist as PENDING in docs/progress/capture_requests.json (rva 0x674a3a0 = 108307360, rva 0x6664760 = 107366240); request.py rejects duplicate pending names, so they were NOT re-added.

| Request | add command | RVA | size | max | state |
| l14c_glyph_draw | `python tools/livecap/request.py add l14c_glyph_draw 0x674a3a0 --size 0x200 --max 8` | 0x674a3a0 | 0x200 | 8 | QUEUED pending — draw-time GlyphTexture binder (sub_674a3a0) |
| l14c_record_builder | `python tools/livecap/request.py add l14c_record_builder 0x6664760 --size 0x200 --max 8` | 0x6664760 | 0x200 | 8 | QUEUED pending — record builder sub_6664760 ("FrameBuilder - Insert UI") |

Expected [live]: entry register dumps give the record pointer (arg8 name bytes = the 16-byte atlas NAME) and ret= names the caller; the NAME string is the glyph atlas identity [LIVE]; its load site is then found with `rdis str` on that string / its hash. Read results with `python tools/livecap/request.py result <name>` (docs/data/live/l14c_glyph_draw.txt / l14c_record_builder.txt) on the next run; if the capture shows the name, that closes "glyph atlas".

## Prior findings (not redone — [V] in docs/progress/oc_U-EL14c_r1..r5)

- GlyphTexture is bound BY NAME at draw time, not as a bgfx handle: 16-byte SSO texture NAME from caller-provided arg8 ([rbp+0xEB8]) via `0x674aa09  movups xmm0,[rax]` (rax = arg8 pointer), staged at `0x674aa0c  movaps [rbp+0xC10],xmm0`, count = 1 at `0x674aa13  mov qword ptr [rbp+0x910],1`, namePtr = sub_bcaba00 result (rbx) staged at `0x674aa1e  mov [rbp+0x918],rbx`, slot selected by matching [uniform-record+0x28] name hash against FNV("GlyphTexture") at `0x674aa42  mov r8,[0x129FA178]` / `0x674aa53  cmp [r10+0x28],r8`, then `0x674aa91  call 0x5679DB0` → `0x5679df9  call 0xEEC6EC0` (memcpy, 16 bytes) into the hash-selected slot, `0x5679dfe  mov byte ptr [r15+r14+0xC],1` sets the valid flag [V]. The 16 bytes written into the GlyphTexture slot are the caller's name from arg8 [V]; exact aliasing of namePtr rbx with the arg8 buffer is [I].
- The GlyphTexture uniform is only registered at init: `0x674dca3  lea rdx,[0xF5C6DD7]` ("GlyphTexture"), hashed `0x674dcb4  call 0x79580`, key stored `0x674dd81  mov [0x129FA178],rcx`, registered `0x674dd8f  call 0x73150` [V]. Not a texture-creation site.
- The value arrives as caller arg8: `0x674a4ca  mov r15,[rbp+0xEB8]`. Object [rbp+0xE80] (r14, `0x674a4d1  mov r14,[rbp+0xE80]`) is read at +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244 but NEVER at +0x38 — the "object+0x38 SSO name" claim from earlier runs is contradicted by the full sub_674a3a0 listing [V].
- The name is supplied by the UI item record: visitor case 3 (sub_6664a00) `0x6664cb0  mov r10,[r9+0x28]` (stride-0x38 loop, `0x6664cbb  add r9,0x38`) staged as arg8 at `0x6664cf5  mov [rsp+0x38],r10`, call `0x6664d46  call 0x674A3A0`; stride-0x86 path `0x6664eb1  mov r13,[r9]` (`0x6664eb8  add r9,0x86`), `0x6664ef9  mov [rsp+0x38],r13`, `0x6664f4a  call 0x674A3A0` [V]. sub_6664a00 is the only static caller of the extractor (`xref.py callers 0x674a3a0` → 0x6664a00) [V].
- Record builder sub_6664760 (`0x6664760  push rbp`, size 0x2000) writes the record from its arguments: `0x66647d7  movups xmm0,[rbx]` (16 bytes from 2nd arg rbx) → `0x66647da  movaps [rbp-0x40],xmm0`, `0x66647de  mov rax,[rsi+0xF0]` (object field +0xF0 → record local [rbp-0x28]), then `0x66648c4  lea r8,[rbp-0x40]` (&16-byte name) and `0x66648c8  call 0x6664A00` drive the dispatch [V]. It has 0 static inbound callers; only .rdata slot 0xf2be218 references it [V].
- sub_5679DB0: `0x5679dbf  movzx r14d,word ptr [rdx]` (count word), `0x5679df9  call 0xEEC6EC0` (memcpy 16 bytes into the slot), `0x5679dfe  mov byte ptr [r15+r14+0xC],1` (valid flag) [V].
- 0xEEC7570 is strlen, not a texture fetch: `0xEEC7570  jmp qword ptr [0xF9A9048]`; called with rcx = C string at `0x76a72c  call 0xEEC7570`, then `0x76a731  cmp rax,0xF` (SSO-vs-heap decision) [V]. `0x4f78966  call 0xEEC7570` in glyph-texture fetch 0x4f78830 (`0x4f78960  movups [rsi],xmm0`, `0x4f7896b  test rax,rax`, `0x4f7896e  js 0x4F78A38`) is the same strlen-style call — refuted as a texture-handle fetch [V].
- Font object: `0xe840f6  lea rax,[0xF09AA70]`, `0xe840fd  mov [rsi],rax` (vtable 0xF09AA70, constructed at sub_e84070) [V]. The only [r13+0x38] writes in font init are SSO length/flags on font-descriptor sub-objects (`0xe8483f  mov qword ptr [r13+0x38],0xF`, heap path `0xe848dc  mov [r13+0x38],r12`) — NOT a texture handle [V].
- Name candidates dead-ended [V]: "ui_text_msdf" at 0xF5BAEF9 (`0xe9ddb5  lea rdx,[0xF5BAEF9]`, `0xe9ddc0  call 0x76a6f0`) has only 2 xrefs (sub_e9dd60, sub_4fc2f80 init-once registration), no link to sub_674a3a0 arg8. "glyph_section_*" strings are UI section labels. Font pack texture suffixes "_ttf" (`0x4fb3dff  lea r9,[0xF5B9FBB]`) and "_ttfmsdf" (`0x4fbe694  lea r9,[0xF5BAEF0]`) are per-font paths, not the atlas. texload 0x58a1310 (`0x58a1310  push rbp`) has no font caller [V].

## Offset table (field map, one row per distinct offset, all its sites listed)

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) loaded for hashing — uniform registration at init, NOT texture creation [V] |
| 0x674dcb4 | 8 | call | `0x674dcb4  call 0x79580` | FNV-1a hash of "GlyphTexture" [V] |
| 0x674dd81 | 8 | [0x129FA178] | `0x674dd81  mov [0x129FA178],rcx` | "GlyphTexture" hash stored as draw-time lookup key [V] |
| 0x674dd8f | 8 | call | `0x674dd8f  call 0x73150` | uniform registration call [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: caller arg8 pointer loaded into r15 [V] |
| 0x674a4d1 | 8 | [rbp+0xE80] | `0x674a4d1  mov r14,[rbp+0xE80]` | Object base into r14; object read at +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244 but NEVER +0x38 — object+0x38 does NOT hold GlyphTexture [V] |
| 0x674a9f2 | 8 | [rbp+0xEA0] | `0x674a9f2  mov r8,[rbp+0xEA0]` | Argument slot loaded for texture-object resolver sub_bcaba00 [V] |
| 0x674a9f9 | 8 | call | `0x674a9f9  call 0xBCABA00` | sub_bcaba00 texture-object resolver; result (rbx) staged as namePtr [V] |
| 0x674a9ff | 8 | rax=r15=[rbp+0xEB8] | `0x674a9ff  mov rax,r15` | rax = caller-provided arg8 pointer [V] |
| 0x674aa02 | 8 | lea r15 | `0x674aa02  lea r15,[rbp+0xB70]` | Writer object (stack struct [rbp+0xB70]) loaded as this [V] |
| 0x674aa09 | 16 | [rax]=*[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME loaded from caller-provided arg8 — GlyphTexture value is a NAME, not a bgfx handle [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as uniform value buffer [V] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | Draw binding count = 1 (=> 16-byte copy) [V] |
| 0x674aa1e | 8 | [rbp+0x918] | `0x674aa1e  mov [rbp+0x918],rbx` | namePtr (rbx = sub_bcaba00 result) staged as qword name pointer [V] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | Search key = FNV("GlyphTexture") hash [V] |
| 0x674aa50 | 8 | [rcx] | `0x674aa50  mov r10,[rcx]` | Uniform slot array entry = qword pointer to uniform record; walk stride `0x674aa59  add rcx,0x10` [V] |
| 0x674aa59 | 8 | 0x674aa59 | `0x674aa59  add rcx,0x10` | Uniform-record walk stride 0x10 [V] |
| 0x674aa53 | 8 | [r10+0x28] | `0x674aa53  cmp [r10+0x28],r8` | [uniform-record+0x28] name hash compared with GlyphTexture hash; match selects slot [V] |
| 0x674aa6f | 4 | ecx | `0x674aa6f  shr ecx,4` | Slot index = (matched entry − array base) / 16 [V] |
| 0x674aa72 | 2 | [rbp+0x5F0] | `0x674aa72  mov [rbp+0x5F0],cx` | u16 slot index stored [V] |
| 0x674aa79 | 1 | [rbp+0x5F2] | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | u8 bound flag = 1 [V] |
| 0x674aa80 | 8 | rdx=&[rbp+0x5F0] | `0x674aa80  lea rdx,[rbp+0x5F0]` | {u16 index, u8 flag} passed in rdx to sub_5679DB0 [V] |
| 0x674aa87 | 8 | r8=&[rbp+0x910] | `0x674aa87  lea r8,[rbp+0x910]` | {qword count=1, qword namePtr} passed in r8 to sub_5679DB0 [V] |
| 0x674aa8e | 8 | rcx=r15=[rbp+0xB70] | `0x674aa8e  mov rcx,r15` | Writer object (this = rcx) for sub_5679DB0 [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind via uniform/subcomponent writer [V] |
| 0x5679dbf | 2 | word ptr [rdx] | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679DB0: count word read (1) [V] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr=[rdi+8], size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the binding slot [V] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0xC valid/bound flag set to 1 [V] |
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | Visitor case 3 (sub_6664a00), stride-0x38 record loop (`0x6664cbb  add r9,0x38`): record field +0x28 = qword texture-NAME pointer [V] |
| 0x6664cf5 | 8 | [rsp+0x38] | `0x6664cf5  mov [rsp+0x38],r10` | Field +0x28 staged as extractor arg8 [V] |
| 0x6664d46 | 8 | call | `0x6664d46  call 0x674A3A0` | Extractor call site 1: stride-0x38 records, arg8 = [r9+0x28] name pointer [V] |
| 0x6664eb1 | 8 | [r9] | `0x6664eb1  mov r13,[r9]` | Visitor stride-0x86 path: record field +0x0 read (`0x6664eb8  add r9,0x86`) [V] |
| 0x6664ef9 | 8 | [rsp+0x38] | `0x6664ef9  mov [rsp+0x38],r13` | Field +0x0 staged as extractor arg8 [V] |
| 0x6664f4a | 8 | call | `0x6664f4a  call 0x674A3A0` | Extractor call site 2: stride-0x86 records [V] |
| 0x6664760 | 8 | fn entry | `0x6664760  push rbp` | sub_6664760 entry ("FrameBuilder - Insert UI" record builder, size 0x2000, 0 static xrefs) [V] |
| 0x66647d7 | 16 | [rbx] | `0x66647d7  movups xmm0,[rbx]` | Record builder: 16 bytes (SSO string contents) from 2nd argument rbx [V] |
| 0x66647da | 16 | [rbp-0x40] | `0x66647da  movaps [rbp-0x40],xmm0` | Record builder: 16-byte name written into record local; `0x66648c4  lea r8,[rbp-0x40]` passes &name to sub_6664A00 [V] |
| 0x66647de | 8 | [rsi+0xF0] | `0x66647de  mov rax,[rsi+0xF0]` | Record builder: object field +0xF0 → record local [rbp-0x28] [V] |
| 0x66648c8 | 8 | call | `0x66648c8  call 0x6664A00` | Record builder drives dispatch that calls the extractor (rdx=&[rbp-0x28], r8=&16-byte name) [V] |
| 0xe840f6 | 8 | 0xe840f6 | `0xe840f6  lea rax,[0xF09AA70]` | Font object vtable pointer 0xF09AA70 loaded (sub_e84070 ctor) [V] |
| 0xe840fd | 8 | [rsi] | `0xe840fd  mov [rsi],rax` | Font object +0x0 = vtable 0xF09AA70 [V] |
| 0xe8483f | 8 | [r13+0x38] | `0xe8483f  mov qword ptr [r13+0x38],0xF` | Only object+0x38 writes in font init: SSO length/flags of font-descriptor sub-object, NOT a texture handle [V] |
| 0xe848dc | 8 | [r13+0x38] | `0xe848dc  mov [r13+0x38],r12` | Heap path: heap pointer stored at descriptor+0x38 — still a font NAME descriptor, not a texture handle [V] |
| 0xe9ddb5 | 8 | 0xe9ddb5 | `0xe9ddb5  lea rdx,[0xF5BAEF9]` | "ui_text_msdf" (12 bytes, fits 16-byte SSO) candidate glyph-atlas NAME; only 2 xrefs (sub_e9dd60, sub_4fc2f80 init-once registration), NOT linked to sub_674a3a0 arg8 — dead end [V] |
| 0x4fb3dff | 8 | 0x4fb3dff | `0x4fb3dff  lea r9,[0xF5B9FBB]` | "_ttf" suffix (0xF5B9FBB) — per-font pack texture path `<name>_ttf.png`, not the atlas name [V] |
| 0x4fbe694 | 8 | 0x4fbe694 | `0x4fbe694  lea r9,[0xF5BAEF0]` | "_ttfmsdf" suffix (0xF5BAEF0) — per-font pack texture path `<name>_ttfmsdf.png`, not the atlas name [V] |
| 0x58a1310 | 8 | 0x58a1310 | `0x58a1310  push rbp` | texload pack/named texture loader entry; callers sub_58b5220/sub_6a8b620/sub_6b80db0 — none font-related [V] |
| 0xEEC7570 | 8 | 0xEEC7570 | `0xEEC7570  jmp qword ptr [0xF9A9048]` | Import thunk = strlen-style (rcx = C string, rax tested as length) — NOT a texture-handle fetch [V] |
| 0x76a72c | 8 | call | `0x76a72c  call 0xEEC7570` | sub_76a6f0 SSO setter calls strlen then `0x76a731  cmp rax,0xF` — confirms 0xEEC7570 = strlen [V] |
| 0x76a731 | 8 | rax | `0x76a731  cmp rax,0xF` | String length vs 0xF for SSO-vs-heap decision [V] |
| 0x4f78960 | 16 | [rsi] | `0x4f78960  movups [rsi],xmm0` | Glyph-texture fetch 0x4f78830: zeroes output texture-ref slot (16 bytes) before the fetch [V] |
| 0x4f78966 | 8 | call | `0x4f78966  call 0xEEC7570` | Indirect call through CFG thunk — strlen-style on C string, NOT a texture-handle fetch (refuted; do not re-trace) [V] |

## Answer

**(1) Where the GlyphTexture uniform value comes from — proven [V]:** caller-provided arg8 ([rbp+0xEB8]); its 16 bytes are loaded as a texture NAME via `0x674aa09  movups xmm0,[rax]` (rax = arg8 pointer), staged at `0x674aa0c  movaps [rbp+0xC10],xmm0`, count = 1 at `0x674aa13  mov qword ptr [rbp+0x910],1`, namePtr (sub_bcaba00 result rbx) staged at `0x674aa1e  mov [rbp+0x918],rbx`, slot selected by matching [uniform-record+0x28] name hash against FNV("GlyphTexture") (`0x674aa42  mov r8,[0x129FA178]`, `0x674aa53  cmp [r10+0x28],r8`), then bound via `0x674aa91  call 0x5679DB0`, which memcpy-writes 16 bytes via `0x5679df9  call 0xEEC6EC0` into the hash-selected slot (`0x5679dfe  mov byte ptr [r15+r14+0xC],1` sets the valid flag). The value is a TEXTURE NAME resolved by name at draw time, NOT a bgfx handle.

**(2) Which object field holds the texture handle — proven [V]: NONE.** The object+0x38 claim is contradicted by the full sub_674a3a0 listing: object r14 = [rbp+0xE80] is read at +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244 and never at +0x38. The value arrives as caller arg8; the field that carries it is the UI item record field — [r9+0x28] (stride-0x38 records, `0x6664cb0  mov r10,[r9+0x28]`) or [r9] (stride-0x86 records, `0x6664eb1  mov r13,[r9]`) — staged as arg8 at `0x6664cf5` / `0x6664ef9`. The only [r13+0x38] writes in font init (`0xe8483f`, `0xe848dc`) are SSO length/flags of font-descriptor sub-objects, not a texture handle.

**(3) Who writes that field — OPEN (blocking):** sub_6664760 writes the record from its arguments (`0x66647d7  movups xmm0,[rbx]` → `0x66647da  movaps [rbp-0x40],xmm0`; `0x66648c8  call 0x6664A00` drives dispatch) but `xref.py callers 0x6664760` = 0 and the only reference is unresolved .rdata slot 0xf2be218 — indirect dispatch, caller not statically locatable.

**(4) Glyph atlas identity / load site — pending [live]:** no name string, no createTexture/createDynamicTexture call anywhere in .text, texload 0x58a1310 has no font caller — the atlas is a named pack texture resolved by name at draw time. The 16-byte NAME and its load site come from the queued live captures (l14c_glyph_draw, l14c_record_builder) on the next run.

## CLOSES?

CLOSES? NO — missing REVERSING: the single unknown is the inbound caller/writer of record builder sub_6664760 (who writes the record name field [r9+0x28] stride-0x38 / [r9] stride-0x86 that becomes sub_674a3a0 arg8 and thereby the GlyphTexture uniform value), reachable only through unresolved indirect dispatch .rdata slot 0xf2be218 with 0 static xrefs. Consequently the 16-byte glyph atlas NAME string and its load site are unknown; awaiting live capture results (l14c_glyph_draw, l14c_record_builder) to name the writer, the NAME, and the load site. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units), the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot), the name source (UI record field, not an object field — object+0x38 contradicted), and that the atlas is a named pack texture, not created by font code.

## What I tried that failed (new angles this run, not redone)

- Full re-dump of sub_674a3a0 + grep of every [r14+...] access: 0 reads of object+0x38 — contradicts the object+0x38 SSO-name claim; the value is caller arg8.
- `xref.py ptr 0x6664760` → only .rdata 0xf2be218; `xref.py callers 0x6664760` → 0 — record builder's caller not statically resolvable (indirect dispatch).
- `rdis fld 0x38 --w`: ~209k global [reg+0x38] writes, first hits all stack/other — no font/record name writer surfaced (too noisy to exhaust).
- sub_e84070 font ctor (vtable 0xF09AA70): object+0x38 writes are SSO length/flags on descriptor sub-objects, not a texture-handle field.
- xref str "glyph_"/"ui_text_msdf"/"Caution"/"ErrorGlyph"/"WarningGlyph": section labels or unlinked init-once registration; no link to sub_674a3a0 arg8.
- texload 0x58a1310: no font caller; no createTexture/createDynamicTexture ANYWHERE in .text.

## TOOL REQUESTS

- l14c_glyph_draw | `python tools/livecap/request.py add l14c_glyph_draw 0x674a3a0 --size 0x200 --max 8` -> docs/data/live/l14c_glyph_draw.txt | Already QUEUED (pending) in docs/progress/capture_requests.json; entry registers + ret= should give the record pointer (arg8 = 16-byte atlas NAME bytes) and name its caller. Awaiting orchestrator run; read with `python tools/livecap/request.py result l14c_glyph_draw`.
- l14c_record_builder | `python tools/livecap/request.py add l14c_record_builder 0x6664760 --size 0x200 --max 8` -> docs/data/live/l14c_record_builder.txt | Already QUEUED (pending); ret= should name the inbound caller (the record name writer); 2nd-arg bytes should be the 16-byte atlas NAME. Awaiting orchestrator run; read with `python tools/livecap/request.py result l14c_record_builder`.

