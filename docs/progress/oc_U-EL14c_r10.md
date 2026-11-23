## NEXT
step 2

# Unit U-EL14c: L14c Text/font — glyph atlas (live-capture angle; static angles exhausted)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending" (BGFX_MAP.md 6ce anchors UI pass extractor 0x674a3a0 and lists "Still pending: glyph atlas management"). The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c/U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be, all in UI extractor 0x674a3a0). This unit covers ONLY the pending part: the GLYPH ATLAS — the 16-byte atlas NAME bound as GlyphTexture at draw time, who writes it, and its load site.

## Blocking fact (single unknown)

The live 16-byte glyph atlas NAME bytes have never been captured. The name is caller-provided arg8 ([rbp+0xEB8]) in UI extractor 0x674a3a0, loaded as a 16-byte SSO texture NAME and written into the hash-selected GlyphTexture uniform slot by sub_5679DB0 (`0x5679df9  call 0xEEC6EC0`, memcpy 16). The field that carries it is the UI item record field ([r9+0x28] stride-0x38 / [r9] stride-0x86 via sub_6664a00), assembled by record builder sub_6664760, whose inbound caller is reachable only through unresolved .rdata indirect-dispatch slot 0xf2be218 (`xref.py callers 0x6664760` = 0). No createTexture/createDynamicTexture call exists ANYWHERE in .text (imm scan 0 hits), texload 0x58a1310 has no font caller, no "GlyphAtlas"/"FontTexture" string exists, and the candidate "ui_text_msdf" (0xF5BAEF9) has no static link to sub_674a3a0's arg8. So the atlas is a named pack texture resolved by name at draw time; its NAME, writer and load site require live data.

## Live capture status (this run)

The two captures the earlier runs queued ran and got 0 hits each, so they must NOT be re-requested (orchestrator 2026-11-22 22:35):
- l14c_glyph_draw 0x674a3a0 size 0x200 max 8: state=done, hits=0 (docs/data/live/l14c_glyph_draw.txt empty)
- l14c_record_builder 0x6664760 size 0x200 max 8: state=done, hits=0 (docs/data/live/l14c_record_builder.txt empty)

Per the orchestrator 22:35 hint, ONE capture at 0x5679db0 (UniformBlock::setVec4Array = sub_5679DB0, does the 16-byte memcpy of uniform names into hash-selected slots) was queued instead:
- l14c_uniform_writer 0x5679db0 size 0x100 max 8: state=pending — `python tools/livecap/request.py result l14c_uniform_writer` returns "no result yet (orchestrator has not run it)". Not too hot: 390 static call sites (`xref.py callers 0x5679db0`), bounded, max-8 entry sampling stays tractable; hits are filtered to the GlyphTexture slot write (index 0x000A = 10), so the 8 samples are name writes. The dumped 16 bytes at namePtr ARE the atlas NAME [LIVE].

Static "too hot" check: none of the 390 call sites is in a per-vertex hot loop proven by disassembly; entry logging with max 8 samples is the designed operating point of this capture. If the batch returns 0 hits or the slot write never appears among the 8 samples, fall back to answering NO with this same blocking fact.

## Offset table (one row per distinct offset; all its sites listed; verbatim instr line; size from instruction; [V]/[I]/[-])

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string loaded for FNV hashing at init — uniform registration, NOT texture creation [V] |
| 0x674dcb4 | 8 | call | `0x674dcb4  call 0x79580` | FNV-1a 64 hash of "GlyphTexture" [V] |
| 0x674dd81 | 8 | [0x129FA178] | `0x674dd81  mov [0x129FA178],rcx` | "GlyphTexture" hash stored as draw-time lookup key [V] |
| 0x674dd8f | 8 | call | `0x674dd8f  call 0x73150` | uniform registration call [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: caller arg8 pointer loaded into r15 [V] |
| 0x674aa09 | 16 | [rax]=*[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME loaded from caller-provided arg8 — GlyphTexture uniform value is a NAME, not a bgfx handle [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as uniform value buffer [V] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | Draw binding count = 1 (=> 16-byte copy) [V] |
| 0x674aa1e | 8 | [rbp+0x918] | `0x674aa1e  mov [rbp+0x918],rbx` | namePtr (rbx = sub_bcaba00 result) staged as qword name pointer [V] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | Search key = FNV("GlyphTexture") hash from 0x129FA178 [V] |
| 0x674aa50 | 8 | [rcx] | `0x674aa50  mov r10,[rcx]` | Uniform slot array entry = qword pointer to uniform record; walk stride `0x674aa59  add rcx,0x10` [V] |
| 0x674aa53 | 8 | [r10+0x28] | `0x674aa53  cmp [r10+0x28],r8` | [uniform-record+0x28] name hash compared with GlyphTexture hash; match selects slot [V] |
| 0x674aa6f | 4 | ecx | `0x674aa6f  shr ecx,4` | Slot index = (matched entry − array base) / 16 [V] |
| 0x674aa72 | 2 | [rbp+0x5F0] | `0x674aa72  mov [rbp+0x5F0],cx` | u16 slot index stored [V] |
| 0x674aa79 | 1 | [rbp+0x5F2] | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | u8 bound flag = 1 [V] |
| 0x674aa80 | 8 | rdx=&[rbp+0x5F0] | `0x674aa80  lea rdx,[rbp+0x5F0]` | {u16 index, u8 flag} passed in rdx to sub_5679DB0 [V] |
| 0x674aa87 | 8 | r8=&[rbp+0x910] | `0x674aa87  lea r8,[rbp+0x910]` | {qword count=1, qword namePtr} passed in r8 to sub_5679DB0 [V] |
| 0x674aa8e | 8 | rcx=r15 | `0x674aa8e  mov rcx,r15` | Writer object (stack struct [rbp+0xB70]) as this for sub_5679DB0 [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind via uniform/subcomponent writer [V] |
| 0x5679db0 | 8 | fn entry | `0x5679db0  push r15` | sub_5679DB0 = UniformBlock::setVec4Array entry (size ~0x2000; 390 static call sites per xref.py callers) — capture target [V rdis] |
| 0x5679dbf | 2 | word ptr [rdx] | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679DB0: count word read (1) [V rdis] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr, size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the binding slot [V rdis] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0xC valid/bound flag set to 1 [V rdis] |
| 0x674a9f2 | 8 | [rbp+0xEA0] | `0x674a9f2  mov r8,[rbp+0xEA0]` | Argument slot loaded for texture-object resolver sub_bcaba00 [V] |
| 0x674a9f9 | 8 | call | `0x674a9f9  call 0xBCABA00` | sub_bcaba00 texture-object resolver; result (rbx) staged as namePtr [V] |
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | Visitor case 3 (sub_6664a00), stride-0x38 UI record loop `0x6664cbb  add r9,0x38`: record field +0x28 = qword texture-NAME pointer [V descscan2 case 3] |
| 0x6664cf5 | 8 | [rsp+0x38] | `0x6664cf5  mov [rsp+0x38],r10` | Field +0x28 staged as extractor arg8 [V] |
| 0x6664d46 | 8 | call | `0x6664d46  call 0x674A3A0` | Extractor call site 1: stride-0x38 records, arg8 = [r9+0x28] name pointer [V] |
| 0x6664eb1 | 8 | [r9] | `0x6664eb1  mov r13,[r9]` | Visitor stride-0x86 path: record field +0x0 read `0x6664eb8  add r9,0x86` [V] |
| 0x6664ef9 | 8 | [rsp+0x38] | `0x6664ef9  mov [rsp+0x38],r13` | Field +0x0 staged as extractor arg8 [V] |
| 0x6664f4a | 8 | call | `0x6664f4a  call 0x674A3A0` | Extractor call site 2: stride-0x86 records [V] |
| 0x6664760 | 8 | fn entry | `0x6664760  push rbp` | sub_6664760 entry ("FrameBuilder - Insert UI" record builder, size ~0x2000, 0 static xrefs) [V] |
| 0x66647d7 | 16 | [rbx] | `0x66647d7  movups xmm0,[rbx]` | Record builder: 16 bytes (SSO string contents) from 2nd argument rbx [V] |
| 0x66647da | 16 | [rbp-0x40] | `0x66647da  movaps [rbp-0x40],xmm0` | Record builder: 16-byte name written into record local; `0x66648c4  lea r8,[rbp-0x40]` passes &name to sub_6664A00 [V] |
| 0x66647de | 8 | [rsi+0xF0] | `0x66647de  mov rax,[rsi+0xF0]` | Record builder: object field +0xF0 → record local [rbp-0x28] [V] |
| 0x66648c8 | 8 | call | `0x66648c8  call 0x6664A00` | Record builder drives dispatch that calls the extractor (rdx=&[rbp-0x28], r8=&16-byte name) [V] |
| 0xe840f6 | 8 | 0xe840f6 | `0xe840f6  lea rax,[0xF09AA70]` | Font object vtable pointer 0xF09AA70 loaded (sub_e84070 ctor) [V] |
| 0xe840fd | 8 | [rsi] | `0xe840fd  mov [rsi],rax` | Font object +0x0 = vtable 0xF09AA70 [V] |
| 0xe8483f | 8 | [r13+0x38] | `0xe8483f  mov qword ptr [r13+0x38],0xF` | Only object+0x38 writes in font init: SSO length/flags of font-descriptor sub-object, NOT a texture handle [V] |
| 0xe848dc | 8 | [r13+0x38] | `0xe848dc  mov [r13+0x38],r12` | Heap path: heap pointer stored at descriptor+0x38 — still a font NAME descriptor, not a texture handle [V] |
| 0xe9ddb5 | 8 | 0xe9ddb5 | `0xe9ddb5  lea rdx,[0xF5BAEF9]` | "ui_text_msdf" (12 bytes, fits 16-byte SSO) candidate glyph-atlas NAME; only 2 xrefs (sub_e9dd60, sub_4fc2f80 init-once registration), NOT linked to sub_674a3a0 arg8 — dead end [V] |
| 0x4fb3dff | 8 | 0x4fb3dff | `0x4fb3dff  lea r9,[0xF5B9FBB]` | "_ttf" suffix (0xF5B9FBB) — per-font pack texture path <name>_ttf.png, not the atlas name [V] |
| 0x4fbe694 | 8 | 0x4fbe694 | `0x4fbe694  lea r9,[0xF5BAEF0]` | "_ttfmsdf" suffix (0xF5BAEF0) — per-font pack texture path <name>_ttfmsdf.png, not the atlas name [V] |
| 0x58a1310 | 8 | 0x58a1310 | `0x58a1310  push rbp` | texload pack/named texture loader entry; callers sub_58b5220/sub_6a8b620/sub_6b80db0 — none font-related [V] |
| 0xEEC7570 | 8 | 0xEEC7570 | `0xEEC7570  jmp qword ptr [0xF9A9048]` | Import thunk = strlen-style (rcx = C string, rax tested as length) — NOT a texture-handle fetch [V] |
| 0x76a72c | 8 | call | `0x76a72c  call 0xEEC7570` | sub_76a6f0 SSO setter calls strlen then `0x76a731  cmp rax,0xF` — confirms 0xEEC7570 = strlen [V] |
| 0x76a731 | 8 | rax | `0x76a731  cmp rax,0xF` | String length (rax=strlen result) compared to 0xF for SSO-vs-heap decision [V] |
| 0x4f78960 | 16 | [rsi] | `0x4f78960  movups [rsi],xmm0` | Glyph-texture fetch 0x4f78830: zeroes output texture-ref slot (16 bytes) before the fetch [V] |
| 0x4f78966 | 8 | call | `0x4f78966  call 0xEEC7570` | Indirect call through CFG thunk — strlen-style on C string, NOT a texture-handle fetch (refuted; do not re-trace) [V] |

## Answer

**(1) Where the GlyphTexture uniform value comes from — proven [V]:** caller-provided arg8 ([rbp+0xEB8]) is loaded as a 16-byte SSO texture NAME via `0x674aa09  movups xmm0,[rax]` (rax = r15 = [rbp+0xEB8]), staged at `0x674aa0c  movaps [rbp+0xC10],xmm0`, count = 1 at `0x674aa13  mov qword ptr [rbp+0x910],1`, namePtr = sub_bcaba00 result (rbx) staged at `0x674aa1e  mov [rbp+0x918],rbx`, slot selected by matching [uniform-record+0x28] name hash against FNV("GlyphTexture") at 0x129FA178 (`0x674aa42  mov r8,[0x129FA178]`, `0x674aa53  cmp [r10+0x28],r8`, walk stride `0x674aa59  add rcx,0x10`, index `0x674aa6f  shr ecx,4`), then bound via `0x674aa91  call 0x5679DB0`, which memcpy-writes 16 bytes via `0x5679df9  call 0xEEC6EC0` into the hash-selected slot (`0x5679dfe  mov byte ptr [r15+r14+0xC],1` sets the valid flag). The value is a TEXTURE NAME resolved by name at draw time, NOT a bgfx handle and NOT an atlas-handle fetch. Slot index for GlyphTexture = 0x000A (10) observed [V live] in docs/data/live/glyph_bind.txt (30/30 samples).

**(2) Which object field holds the texture handle — proven [V]: NONE.** The object+0x38 claim is contradicted by the full sub_674a3a0 listing: object r14 = [rbp+0xE80] is read at +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244 and never at +0x38. The value arrives as caller arg8; the field that carries it is the UI item record field — [r9+0x28] (stride-0x38 records, `0x6664cb0  mov r10,[r9+0x28]`) or [r9] (stride-0x86 records, `0x6664eb1  mov r13,[r9]`) — staged as arg8 at `0x6664cf5` / `0x6664ef9`. The only object+0x38 writes in font init (`0xe8483f  mov qword ptr [r13+0x38],0xF`, `0xe848dc  mov [r13+0x38],r12`) are SSO length/flags of font-descriptor sub-objects, not a texture handle.

**(3) Who writes that field — OPEN (blocking):** sub_6664760 writes the record from its arguments (`0x66647d7  movups xmm0,[rbx]` → `0x66647da  movaps [rbp-0x40],xmm0`; `0x66648c8  call 0x6664A00` drives dispatch) but `xref.py callers 0x6664760` = 0 and the only reference is unresolved .rdata slot 0xf2be218 — indirect dispatch, caller not statically locatable.

**(4) Glyph atlas identity / load site — pending [live]:** no name string proven, no createTexture/createDynamicTexture call ANYWHERE in .text, texload 0x58a1310 has no font caller — the atlas is a named pack texture resolved by name at draw time. The 16-byte NAME and its load site come from the queued live capture l14c_uniform_writer (0x5679db0).

## CLOSES?

CLOSES? NO — missing REVERSING: the single unknown is the live 16-byte glyph atlas NAME bytes (the atlas identity) and the writer/load site of the UI record name field that becomes sub_674a3a0's arg8 (inbound caller of sub_6664760 via unresolved .rdata slot 0xf2be218). The l14c_uniform_writer capture at 0x5679db0 is queued pending; read it with `python tools/livecap/request.py result l14c_uniform_writer` on the next run. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units), the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot; slot index 0x000A=10), the name source (UI record field, not an object field — object+0x38 contradicted), and that the atlas is a named pack texture, not created by font code.

## What I tried that failed (new angles; static r1-r8 angles not redone)

- `python tools/sigs/livemem.py status` — game state varies by run; per brief rule 1 the game is closed and I may not start it; livemem is read-only last resort and cannot be used to manufacture the NAME statically. If livemem reports the game running, a specific address read may be attempted (at most 12 calls per unit, max 0x400 bytes per read, no scanning/looping).
- l14c_glyph_draw (0x674a3a0) and l14c_record_builder (0x6664760): state=done, hits=0, samples=0 — neither function fires on the live glyph-text path; do NOT re-request (orchestrator 2026-11-22 22:35).
- l14c_name_resolver* variants (sub_bcaba00 at 0xbcaba00 plus callers 0x67417f0/0x6745440/0x673d150 from prior runs): queue was full at 4 pending in prior runs; not re-added this run since sub_5679DB0 is the direct name-writer and its capture supersedes them.
- Static angles from r1-r8 remain exhausted: indirect dispatch slot 0xf2be218 (0 static callers); object+0x38 contradicted by the full sub_674a3a0 listing (0 reads of [r14+0x38]); no createTexture/createDynamicTexture ANYWHERE in .text; no glyph-atlas name string; font init/reset create no textures; "ui_text_msdf"/"glyph_section_*"/"_ttf"/"_ttfmsdf" all dead ends; 0xEEC7570 call at 0x4f78966 refuted as strlen, not a texture fetch.

## TOOL REQUESTS

- l14c_uniform_writer | `python tools/livecap/request.py add l14c_uniform_writer 0x5679db0 --size 0x100 --max 8 --why "L14c: UniformBlock::setVec4Array entry; capture the GlyphTexture slot write (index 0x000A): r8 = {count=1, namePtr}; the dumped 16 bytes at namePtr are the atlas NAME [LIVE]. ret= names the caller"` | ALREADY QUEUED (state=pending) per orchestrator hint 2026-11-22 22:35 — do NOT re-add (duplicate pending names are rejected); read results with `python tools/livecap/request.py result l14c_uniform_writer`. Not too hot: 390 static call sites, bounded, max-8 entry sampling.

- None (helper scripts): all evidence from rdis.exe dis/fn, xref.py callers/str/ptr, descscan2.py; no throwaway one-liners needed; no _tmp files left behind.

## NEXT
DONE
