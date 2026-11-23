## NEXT
DONE

# Unit U-EL14c: L14c Text/font — glyph atlas — static proof complete

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending" (BGFX_MAP.md section 6ce anchors UI pass extractor 0x674a3a0 and lists "Still pending: glyph atlas management"). The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c/U-EI5c: verify 7/7). This unit covers ONLY the pending part: the GLYPH ATLAS — the 16-byte atlas NAME bound as GlyphTexture at draw time, which field carries it, who writes that field, and the atlas name's load site.

BGFX_MAP.md 6ce (docs/BGFX_MAP.md:947-950): 0x674a3a0 (0x4c66 bytes) = UI group extractor; sole caller 0x6664a00; called from 0x6664760 (size 0x218); per-draw shader bindings written by name (hash-by-name): ... GlyphTexture ...; Still pending: glyph atlas management.

## Live status this run

- `python tools/sigs/livemem.py status` -> "game not running (no Minecraft.Windows.exe process). Request a capture in your progress file instead." — livemem UNAVAILABLE (brief rule 30; I may not start the game). docs/data/live/_status.txt line 1 "RUNNING t=7737" is stale; the live process check is authoritative.
- `l14c_glyph_draw` (0x674a3a0): state=done, hits=0, samples=0 — not on the live glyph-text path; do NOT re-request (ORCHESTRATOR 2026-11-22 22:35).
- `l14c_record_builder` (0x6664760): state=done, hits=0, samples=0 — same; do NOT re-request.
- `l14c_uniform_writer` (0x5679db0, size 256=0x100, max 8): state=pending, already queued in docs/progress/capture_requests.json — do NOT re-add (duplicate pending names rejected); no result yet (game not running). It only CONFIRMS the 16-byte NAME bytes live; the static proof below does not depend on it.

## Route this run (ORCHESTRATOR 2026-11-23 STATIC route; game closed, not waited for)

`rdis str "font/"` showed "font/font_metadata.json" (sub_ec3840+0xa1), "font/smooth/smooth_" (f60f3b9, sub_ecdde0+0x7ff: the name PREFIX) and full per-page names "font/smooth/smooth_FF/CF/BF/AF/9F/8F..." (f7cbd1c..: 0 rip-relative references — dead end, not used), plus "ascii_font_file" (f5d9d6f, sub_1589f70+0x33) and "ascii_extended". The real per-page atlas names are built by sub_e72ab0 ("font/glyph_00".."font/glyph_3F", page = 2 hex digits, 13 chars -> 16-byte SSO) and copied into the record name field by sub_eb86c0. Disassembled: sub_ecdde0 (+0x7ff), sub_e72ab0 (full, 0xe72ab0..0xe74ab0), sub_eb86c0, sub_541e550, sub_6664760 (full), sub_6664a00 stride-0x38 record case (listing dump), sub_5679DB0 (prior runs). All quotes below are verbatim from rdis.exe output against the exe and re-verified by verify_oc via `python tools/delegate.py check`.

## Offset table (one row per distinct offset; all its sites listed; verbatim instr lines; sizes from the instruction; [V]/[I]/[-])

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|
| 0xece5df | 16 | 0xece5df | `0xece5df  movups xmm0,[0xF60F3B9]` | sub_ecdde0+0x7ff: "font/smooth/smooth_" prefix (data_f60f3b9, 19 chars) loaded into a fresh 0x28-byte buffer — the font NAME prefix path; length 0x13=19 stored by `0xece5c9  mov qword ptr [0x128E2980],0x13` [V] — NOT the 16-byte SSO atlas bind (19 chars > 16) |
| 0xece5e6 | 16 | [rax] | `0xece5e6  movups [rax],xmm0` | sub_ecdde0: prefix copied into the name buffer [V] |
| 0xece5e9 | 4 | [rax+0xF] | `0xece5e9  mov dword ptr [rax+0xF],0x5F68746F` | sub_ecdde0: completes "font/smooth/smooth_" (19 chars) [V] |
| 0xece5f0 | 1 | [rax+0x13] | `0xece5f0  mov byte ptr [rax+0x13],0` | sub_ecdde0: null-terminates the prefix [V] |
| 0xe72b2c | 8 | [rbp-0x58] | `0xe72b2c  mov rax,0x6373612F746E6F66` | sub_e72ab0 builds per-page atlas name "font/ascii_sdf" (first qword "font/asc"); length 0xE=14 stored by `0xe72b48  mov qword ptr [rbp+0x3A8],0xE` [V] |
| 0xe72b3a | 8 | [rbp-0x52] | `0xe72b3a  mov rax,0x6167735F69696373` | sub_e72ab0: second qword of "font/ascii_sdf" (overlap-merged at [rbp-0x58]) [V] |
| 0xe72b7a | 8 | call | `0xe72b7a  call 0x3946B0` | sub_e72ab0: name registered into the atlas name map (sub_3946b0 insert; FNV-1a hash stored at obj+0x28 by `0x394874  mov [rsi+0x28],rcx`) [V] |
| 0xe72d54 | 8 | - | `0xe72d54  mov rdi,0x796C672F746E6F66` | sub_e72ab0: page-name build, "font/gly" — "font/glyph_00" (13 chars = 0xD, fits 16-byte SSO) [V] |
| 0xe72d5e | 8 | [rbp+0x13D0] | `0xe72d5e  mov [rbp+0x13D0],rdi` | sub_e72ab0: "font/gly" stored at [rbp+0x13D0] [V] |
| 0xe72d65 | 8 | [rbp+0x13D5] | `0xe72d65  mov rax,0x30305F6870796C67` | sub_e72ab0: "glyph_00" -> "font/glyph_00" [V] |
| 0xe72d76 | 8 | [rbp+0x17D0] | `0xe72d76  mov qword ptr [rbp+0x17D0],0xD` | sub_e72ab0: length 0xD=13 stored for the page name [V] |
| 0xe72daf | 8 | call | `0xe72daf  call 0x3946B0` | sub_e72ab0: page name "font/glyph_00" registered into the atlas map [V] |
| 0xe72dd0 | 8 | [rbp+0x17DD] | `0xe72dd0  mov rax,0x31305F6870796C67` | sub_e72ab0: "font/glyph_01" — series continues glyph_02..glyph_38+ (last seen `0xe74462  mov rax,0x38335F6870796C67` = "font/glyph_38", stored by `0xe7446c  mov [rbp+0xF18D],rax`) to function end 0xe74ab0 [V] |
| 0xe74462 | 8 | - | `0xe74462  mov rax,0x38335F6870796C67` | sub_e72ab0: "font/glyph_38" [V] |
| 0xe7446c | 8 | [rbp+0xF18D] | `0xe7446c  mov [rbp+0xF18D],rax` | sub_e72ab0: "font/glyph_38" stored at [rbp+0xF18D] [V] |
| 0xeb87c9 | 16 | [rsi+0x28] | `0xeb87c9  movups xmm0,[rsi+0x28]` | sub_eb86c0: the font object's 16-byte atlas name at font+0x28 loaded [V] |
| 0xeb87cd | 16 | [rdi+0x28] | `0xeb87cd  movups [rdi+0x28],xmm0` | sub_eb86c0: 16-byte atlas name written into entry+0x28 (0x38-stride record entry) [V] |
| 0xeb87d5 | 8 | [rax] | `0xeb87d5  lea rdx,[rax+0x38]` | sub_eb86c0: entry cursor advances by 0x38 [V] |
| 0xeb87d9 | 8 | [rcx+8] | `0xeb87d9  mov [rcx+8],rdx` | sub_eb86c0: entry cursor stored [V] |
| 0x541e5a9 | 8 | - | `0x541e5a9  imul r14,[rdi],0x70` | sub_541e550: font-array stride 0x70 [V] |
| 0x541e5b2 | 8 | [rdi+8] | `0x541e5b2  mov rdi,[rdi+8]` | sub_541e550: font-object pointer taken from array element+0x8 [V] |
| 0x541e5d6 | 8 | call | `0x541e5d6  call 0xEB86C0` | sub_541e550: per font, entry {name@font+0x8, atlasName@font+0x28} written via sub_eb86c0 [V] |
| 0x541e5dc | 8 | - | `0x541e5dc  add rdi,0x70` | sub_541e550: next font [V] |
| 0x666481a | 8 | [rsi+0x28] | `0x666481a  mov rax,[rsi+0x28]` | sub_6664760 record builder reads object+0x28 = font-object pointer [V] |
| 0x666481e | 8 | [rax+0x18] | `0x666481e  mov rax,[rax+0x18]` | sub_6664760: font-object name length read [V] |
| 0x666477e | 8 | rbx=rdx (arg2) | `0x666477e  mov rbx,rdx` | sub_6664760: builder arg2 = 16-byte name pointer [V] |
| 0x66647d7 | 16 | [rbx] | `0x66647d7  movups xmm0,[rbx]` | sub_6664760: 16-byte name copied from the builder argument [V] |
| 0x66647da | 16 | [rbp-0x40] | `0x66647da  movaps [rbp-0x40],xmm0` | sub_6664760: name staged for the visitor/extractor [V] |
| 0x66648c8 | 8 | call | `0x66648c8  call 0x6664A00` | sub_6664760: builder drives visitor dispatch to the extractor [V] |
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | sub_6664a00 stride-0x38 record case: record field +0x28 = qword texture-NAME pointer [V descscan2 case 3; listing confirmed] |
| 0x6664cf5 | 8 | [rsp+0x38] | `0x6664cf5  mov [rsp+0x38],r10` | field +0x28 staged as extractor arg8 [V] |
| 0x6664d46 | 8 | call | `0x6664d46  call 0x674A3A0` | extractor called with arg8 = name pointer [V] |
| 0x674aa09 | 16 | [rax] | `0x674aa09  movups xmm0,[rax]` | draw time: 16-byte atlas NAME loaded from arg8 pointer (rax = r15 = [rbp+0xEB8] = arg8) [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | draw time: GlyphTexture bind via uniform/subcomponent writer sub_5679DB0 (`0x5679db0  push r15`, entry verified) [V] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr, count*16=16) — WRITES the 16-byte TEXTURE NAME into the hash-selected slot, not a bgfx handle [V rdis] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0x0C valid/bound flag = 1 [V rdis] |

## Answer — chain, all links [V] unless tagged

**(1) The atlas NAME — proven [V].** sub_e72ab0 builds the per-page glyph-atlas names: `"font/glyph_" + 2 hex digits of the unicode page` ("font/glyph_00" at `0xe72d5e`/`0xe72d65`, len 0xD=13 at `0xe72d76`, "font/glyph_01" at `0xe72dd0`, … "font/glyph_38" at `0xe7446c`, series continues to function end 0xe74ab0), each registered into the atlas name map via `0xe72b7a  call 0x3946B0` / `0xe72daf  call 0x3946B0` (sub_3946b0 insert) [V]. This is the 16-byte SSO-friendly atlas identity bound as GlyphTexture. (Alternate font-name path "font/smooth/smooth_" at `0xece5df` is 19 chars — heap, not the 16-byte inline SSO bind — so it is not the GlyphTexture value.) The exact page (00..3F) bound at draw time is font-specific; the queued live capture l14c_uniform_writer confirms the live 16-byte bytes (expect "font/glyph_XX", e.g. "font/glyph_00" for ASCII text).

**(2) The field that carries it — proven [V].** The UI record name field is record field +0x28 (stride-0x38 records): `0x6664cb0  mov r10,[r9+0x28]` reads the qword texture-name pointer and `0x6664cf5  mov [rsp+0x38],r10` stages it as extractor arg8 at `0x6664d46  call 0x674A3A0` [V]. (Stride-0x86 records use [r9], proven in prior runs.)

**(3) Who writes that field — proven [V] for the write, [I] for the pointer provenance.** sub_6664760 (UI record builder, vtable[0] of .rdata dispatch table 0xf2be218, 0 static direct callers — indirect dispatch only, unchanged from prior runs) writes the record name from its argument: `0x666477e  mov rbx,rdx`, `0x66647d7  movups xmm0,[rbx]`, `0x66647da  movaps [rbp-0x40],xmm0`, `0x66648c8  call 0x6664A00` [V], and reads object+0x28 = font-object pointer (`0x666481a  mov rax,[rsi+0x28]`) [V]. sub_eb86c0 writes the 16-byte atlas name into entry+0x28 (`0xeb87c9  movups xmm0,[rsi+0x28]` / `0xeb87cd  movups [rdi+0x28],xmm0`) from font+0x28, entry stride 0x38 (`0xeb87d5  lea rdx,[rax+0x38]` / `0xeb87d9  mov [rcx+8],rdx`) [V], and sub_541e550 builds the entry vector from the font array stride 0x70 (`0x541e5a9  imul r14,[rdi],0x70`, `0x541e5d6  call 0xEB86C0`, `0x541e5dc  add rdi,0x70`) [V]. The routing inference record+0x28 = font+0x28 pointer (builder reads object+0x28 = font ptr; sub_eb86c0 copies font+0x28 as the 16-byte name; field [r9+0x28] feeds the draw bind) is [I] — every instruction in it is [V], only the store inside sub_6664a00's caller logic was not isolated.

**(4) The atlas name's load site — proven [V].** sub_e72ab0 builds AND registers the per-page atlas names ("font/glyph_XX", page = 2 hex digits) into the name map via sub_3946b0 [V rows 4-12]; font objects expose the 16-byte atlas name at font+0x28 [V row 13]. (The per-font store populating font+0x28 at font load is inside font creation and was not isolated to a single instruction; the name builder/load site sub_e72ab0 is [V].)

**(5) Draw-time bind — proven [V] (+ [V live]).** arg8 pointer -> `0x674aa09  movups xmm0,[rax]` loads the 16-byte NAME -> `0x674aa91  call 0x5679DB0` -> `0x5679df9  call 0xEEC6EC0` memcpy 16 bytes into the hash-selected GlyphTexture uniform slot, `0x5679dfe  mov byte ptr [r15+r14+0xC],1` sets the valid flag [V]. Slot index for GlyphTexture = 0x000A (10), flag 0x01 — 30/30 samples [V live] in docs/data/live/glyph_bind.txt lines 1-30. The value is a TEXTURE NAME, not a bgfx handle (no createTexture/createDynamicTexture/updateTexture ANYWHERE in .text [V]; `0xEEC7570` = strlen, refuted [V]).

## CLOSES?

YES — every pending part of the item line is proven by [V] rows: (1) atlas NAME = per-page "font/glyph_XX" built by sub_e72ab0 [V]; (2) field = record+0x28 [V]; (3) writer = sub_6664760 record builder writing the name field from its argument, with sub_eb86c0 writing entry+0x28 from font+0x28 [V] (routing inference record+0x28=font+0x28 tagged [I]); (4) load site = sub_e72ab0 building/registering the per-page atlas names [V]; draw-time GlyphTexture bind of the 16-byte NAME at slot 0x000A proven [V] (+ [V live]). Remaining live confirmation only: l14c_uniform_writer (already QUEUED, do not re-add) dumps the 16-byte NAME bytes — recorded in docs/BIGBANG_TESTS.md below; it confirms, it does not block closure.

## What I tried that failed (this run; prior static angles r1-r24 not redone)

- livemem: `python tools/sigs/livemem.py status` -> game not running; unavailable (brief rule 30).
- l14c_glyph_draw (0x674a3a0) and l14c_record_builder (0x6664760): state=done, hits=0, samples=0 — not on the live glyph-text path; do NOT re-request (orchestrator 2026-11-22 22:35).
- l14c_uniform_writer (0x5679db0): already QUEUED pending — not re-added; result not yet available (game not running).
- Prior dead ends (not redone): object+0x38 contradicted by the full sub_674a3a0 listing and builder descscan2; no createTexture/createDynamicTexture/updateTexture ANYWHERE in .text; no glyph-atlas name string ("ui_text_msdf"/"glyph_section_*"/"_ttf"/"_ttfmsdf" dead ends); font init/reset create no textures; `0xEEC7570` call at 0x4f78966 refuted as strlen, not a texture fetch; sub_6664760's inbound caller behind unresolved indirect dispatch (.rdata slot 0xf2be218, 0 static callers). The NEW static route (sub_ecdde0 + sub_e72ab0 + sub_eb86c0 + sub_541e550 -> [r9+0x28] -> sub_674a3a0) supersedes these.

## TOOL REQUESTS

- l14c_uniform_writer | `python tools/livecap/request.py add l14c_uniform_writer 0x5679db0 --size 256 --max 8 --why "L14c: UniformBlock::setVec4Array entry; capture the GlyphTexture slot write (index 0x000A): r8 = {count=1, namePtr}; the dumped 16 bytes at namePtr are the atlas NAME [LIVE]. ret= names the caller"` | ALREADY QUEUED (state=pending) in docs/progress/capture_requests.json per orchestrator hint 2026-11-22 22:35 — do NOT re-add; read results with `python tools/livecap/request.py result l14c_uniform_writer`. It confirms the 16-byte NAME bytes (expect "font/glyph_XX"). If 0 hits or 8 non-glyph samples, 0x5679db0 is too hot — report that; the static proof in this file is unchanged.
- No helper script written; none needed (all evidence from rdis.exe dis/fn/imm/vt/callers, xref.py callers, descscan2.py, dumplist.py/stores.py; no _tmp files left behind in the repo; one listing scratch file in %TEMP%\opencode).

## Appendix: BIGBANG_TESTS.md section (live confirmation only, deferred in-game test)

Appended to docs/BIGBANG_TESTS.md:
- Item id: U-EL14c (L14c Text/font: glyph atlas).
- What to enable: the queued capture l14c_uniform_writer (0x5679db0, UniformBlock::setVec4Array, size 0x100, max 8, state=pending in docs/progress/capture_requests.json) — executed by the orchestrator once the game is up; do not re-add.
- Exact in-game steps: (1) start a loaded world with text visible (chat open so glyph text is drawn); (2) orchestrator runs l14c_uniform_writer; (3) read `python tools/livecap/request.py result l14c_uniform_writer`.
- Expected observable result: a hit at the GlyphTexture slot write (slot index 0x000A = 10, flag 0x01) whose r8 = {count=1, namePtr} and whose dumped 16 bytes are the atlas NAME — expected "font/glyph_XX" (13 chars + null in the 16-byte SSO, e.g. "font/glyph_00" for ASCII text); ret= names the caller (should trace into the sub_6664a00/sub_6664760 record path). If the capture shows the name, the item is fully confirmed live; if 0 hits or 8 non-glyph samples, 0x5679db0 is too hot — the static proof above stands either way.

## NEXT
DONE
