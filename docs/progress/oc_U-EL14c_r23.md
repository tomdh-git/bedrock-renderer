## NEXT
DONE

# UNIT U-EL14c: Text/font SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas — pending part (live capture required)

Unit line: "L14c Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending". The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c/U-EI5c/U-EL14c r1-r22). This unit covers ONLY the pending part: the GLYPH ATLAS — the 16-byte atlas NAME bound as GlyphTexture at draw time, which field carries it, who writes that field, and the atlas name's load site.

## Status this run (2026-11-23)

- `python tools/sigs/livemem.py status` -> "game not running (no Minecraft.Windows.exe process). Request a capture in your progress file instead." — livemem UNAVAILABLE this run (brief rule 30: write the request in the progress file and stop the live angle). The user GOAL asserted the game is running now; the live status check is authoritative and disagrees. No livemem read possible, and there is no target address to read without capture data. [V live]
- `l14c_glyph_draw` (0x674a3a0) and `l14c_record_builder` (0x6664760): state=done, hits=0, samples=0 each (docs/progress/capture_requests.json; docs/data/live/l14c_glyph_draw.txt and l14c_record_builder.txt contain only the header lines). Neither is on the live glyph-text path; do NOT re-request (orchestrator 2026-11-22 22:35).
- `l14c_uniform_writer` (0x5679db0 = UniformBlock::setVec4Array, size 0x100/256, max 8): state=pending, already queued in docs/progress/capture_requests.json per orchestrator hint 2026-11-22 22:35 — exactly the ONE capture the GOAL asks for (size 0x100, max 8, filtered to the GlyphTexture slot write). Do NOT re-add (duplicate pending names rejected). `python tools/livecap/request.py result l14c_uniform_writer` -> "no result yet (orchestrator has not run it)". The dumped 16 bytes at namePtr ARE the atlas NAME [LIVE] when it runs; ret= names the caller; the load site is then found with `rdis str` on that name string / its hash. "Too hot" (0 hits or 8 non-glyph samples of 390 static call sites) can only be judged from the result — not yet determinable.

## Blocking fact (single unknown)

The live 16-byte glyph atlas NAME bytes bound as GlyphTexture at draw-time slot index 0x000A have never been captured. With them missing, the writer of the UI record name field (inbound caller of sub_6664760 via .rdata slot 0xf2be218, indirect dispatch only) and the atlas creation/load site are also unknown. Static analysis is exhausted (see "What I tried that failed"); livemem is unavailable (game not running); the queued l14c_uniform_writer capture has no result yet.

## Already proven (not redone — [V] unless tagged)

- `GlyphTexture` uniform registered at init: `0x674dca3  lea rdx,[0xF5C6DD7]` ("GlyphTexture" at 0xF5C6DD7) hashed via `0x674dcb4  call 0x79580`, key stored `0x674dd81  mov [0x129FA178],rcx`, registered via `0x674dd8f  call 0x73150` — uniform registration, NOT texture creation [V]
- No createTexture/createDynamicTexture/updateTexture call ANYWHERE in .text [V]; no "GlyphAtlas"/"FontTexture" string in .rdata [V]; font init 0xE82E00->0xE84070 (vtable 0xF09AA70) and reset 0x186e6a0 create no textures (registry objects via [0xF99FFA0] only) [V]
- texload 0x58a1310 is the pack/named texture loader; callers sub_6b84680/sub_6ea2df0, none font-related [V]
- `GlyphTexture` draw-time bind is a 16-byte SSO texture NAME (NOT a bgfx handle) from caller arg8, written into the hash-selected slot by sub_5679DB0 via `0x5679df9  call 0xEEC6EC0` (memcpy 16) [V] [V live: slot index 0x000A = 10, flag 0x01 — 30/30 samples in docs/data/live/glyph_bind.txt lines 1-30]
- Object field holding it: NONE — object [rbp+0xE80] reads +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244 but never +0x38 [V]; descscan2 of sub_6664760 reads object fields +0x000/+0x020/+0x028/+0x0f0/+0x100/+0x260/+0x268/+0x358/+0x36c/+0x370/+0x380 (+0x38 in a gap, never read) [V]
- `0xEEC7570` (`0xEEC7570  jmp qword ptr [0xF9A9048]`) is strlen-style (import thunk, live slot 0x7FFBDDA45F00 in another module per oc_U-EI5c), not a texture-handle fetch [V]; `0x4f78966  call 0xEEC7570` in fetch 0x4f78830 refuted [V]
- Candidate name "ui_text_msdf" at `0xe9ddb5  lea rdx,[0xF5BAEF9]`: only 2 xrefs (sub_e9dd60, sub_4fc2f80 init-once registration), NOT linked to sub_674a3a0 arg8 — dead end [V]; "glyph_section_*" strings are UI section labels [V]; "_ttf"/"_ttfmsdf" suffixes (0x4fb3dff/0x4fbe694) are per-font pack paths, not the atlas name [V]
- sub_6664760's inbound caller: `xref.py callers 0x6664760` = 0; `rdis imm 0xf2be218` = 0 hits; `xref.py ptr 0xf2be218` = 0 hits; vtable slot 0 at .rdata 0xf2be218 (`rdis vt 0xf2be218`, slot 0 = sub_6664760 size 0x2000) — indirect dispatch only, caller not statically locatable [V]

## Offset table (one row per distinct offset, all its sites listed; verbatim instr lines; sizes from the instruction)

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof | Meaning ([V]/[I]/[-]) |
|--------|------|--------------------|-------------------------------|-----------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) loaded for FNV hashing at init — uniform registration, NOT texture creation [V] |
| 0x674dcb4 | 8 | call | `0x674dcb4  call 0x79580` | FNV-1a 64-bit hash of "GlyphTexture" [V] |
| 0x674dd81 | 8 | [0x129FA178] | `0x674dd81  mov [0x129FA178],rcx` | "GlyphTexture" hash stored as the draw-time lookup key [V] |
| 0x674dd8f | 8 | call | `0x674dd8f  call 0x73150` | uniform registration call [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: caller-provided arg8 name pointer loaded into r15 [V] |
| 0x674a9f2 | 8 | [rbp+0xEA0] | `0x674a9f2  mov r8,[rbp+0xEA0]` | Argument slot loaded for texture-object resolver sub_BCABA00 [V] |
| 0x674a9f9 | 8 | call | `0x674a9f9  call 0xBCABA00` | sub_BCABA00 texture-object resolver; result (rbx) staged as namePtr [V] |
| 0x674a9ff | 8 | rax=r15=[rbp+0xEB8] | `0x674a9ff  mov rax,r15` | rax = caller-provided arg8 pointer, feed for the 16-byte load [V] |
| 0x674aa09 | 16 | [rax] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME loaded from caller-provided arg8 — GlyphTexture uniform value is a NAME, not a bgfx handle [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as uniform value buffer [V] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | Draw binding count = 1 (=> 16-byte copy) [V] |
| 0x674aa1e | 8 | [rbp+0x918] | `0x674aa1e  mov [rbp+0x918],rbx` | Draw binding namePtr = rbx (sub_BCABA00 result) staged as binding name pointer [V] |
| 0x674aa25 | 8 | [rbp+0xBA0] | `0x674aa25  mov rax,[rbp+0xBA0]` | Base of the 16-byte-entry uniform slot array (= writer stack struct [rbp+0xB70] + 0x30) [V] |
| 0x674aa2c | 2 | [rbp+0xBAA] | `0x674aa2c  movzx r8d,word ptr [rbp+0xBAA]` | u16 entry count of the slot array [V] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | Search key = FNV-1a hash of "GlyphTexture" from 0x129FA178 [V] |
| 0x674aa50 | 8 | [rcx] | `0x674aa50  mov r10,[rcx]` | Array entry[0] = qword pointer to a uniform record; walk stride `0x674aa59  add rcx,0x10` [V] |
| 0x674aa53 | 8 | [r10+0x28] | `0x674aa53  cmp [r10+0x28],r8` | [uniform-record+0x28] name hash compared with GlyphTexture hash; match selects slot [V] |
| 0x674aa59 | 8 | 0x674aa59 | `0x674aa59  add rcx,0x10` | Uniform-record walk stride 0x10 [V] |
| 0x674aa6f | 4 | ecx | `0x674aa6f  shr ecx,4` | Slot index = (matched entry − array base) / 16 [V] |
| 0x674aa72 | 2 | [rbp+0x5F0] | `0x674aa72  mov [rbp+0x5F0],cx` | u16 slot index stored; live capture docs/data/live/glyph_bind.txt lines 1-30: index 0x000A = 10 (GlyphTexture slot), flag 0x01 — 30/30 samples [V] [V live] |
| 0x674aa79 | 1 | [rbp+0x5F2] | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | u8 bound/valid flag = 1 stored next to the index [V] [V live] |
| 0x674aa80 | 8 | rdx=&[rbp+0x5F0] | `0x674aa80  lea rdx,[rbp+0x5F0]` | {u16 index, u8 flag} passed as rdx to sub_5679DB0 [V] |
| 0x674aa87 | 8 | r8=&[rbp+0x910] | `0x674aa87  lea r8,[rbp+0x910]` | {qword count=1, qword namePtr} passed as r8 to sub_5679DB0 [V] |
| 0x674aa8e | 8 | rcx=r15=[rbp+0xB70] | `0x674aa8e  mov rcx,r15` | Writer object (stack struct at [rbp+0xB70]) passed as this (rcx) to sub_5679DB0 [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind via uniform/subcomponent writer [V] [V live] |
| 0x5679db0 | 8 | fn entry | `0x5679db0  push r15` | sub_5679DB0 = UniformBlock::setVec4Array entry, size 0x2000, 390 static inbound xrefs (every uniform write) [V rdis] |
| 0x5679dbf | 2 | [rdx] | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679DB0: index u16 read from {index,flag} param (a1+0x0) [V rdis] |
| 0x5679dc3 | 8 | [rcx+0x30] | `0x5679dc3  mov r15,[rcx+0x30]` | sub_5679DB0: r15 = writer+0x30 = entry-array base [V rdis] |
| 0x5679dcb | 2 | [r15+r14+8] | `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` | sub_5679DB0: entry[index].+0x08 u16 = slot byte-offset into binding table [V rdis] |
| 0x5679dd1 | 4 | [rsi+0x20] | `0x5679dd1  cmp [rsi+0x20],rcx` | sub_5679DB0: bounds check slot-offset < writer+0x20 limit; fail -> int3 path [V rdis] |
| 0x5679ded | 8 | [rsi+0x28] | `0x5679ded  add rcx,[rsi+0x28]` | sub_5679DB0: dst = writer+0x28 + slot-offset (slot table base + offset) [V rdis] |
| 0x5679df1 | 8 | [rdi+8] | `0x5679df1  mov rdx,[rdi+8]` | sub_5679DB0: src = name pointer from draw binding a2+0x8 = [rbp+0x918] = rbx [V rdis] |
| 0x5679df5 | 8 | r8 | `0x5679df5  shl r8,4` | sub_5679DB0: size = count*16 = 16 [V rdis] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr, size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the binding slot, NOT a bgfx handle [V rdis] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0x0C valid/bound flag set to 1 [V rdis] |
| 0x5679e53 | 8 | [rsi+0x70] | `0x5679e53  mov [rsi+0x70],r8` | sub_5679DB0: writer+0x70 FNV-1a state mixed with index and name hash (from `0x5679e65  call 0x19932c0`, XXH64) [V rdis] |
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | Visitor case 3 (sub_6664a00), stride-0x38 UI record loop (`0x6664cbb  add r9,0x38`): record field +0x28 = qword texture-NAME pointer [V descscan2 case 3] |
| 0x6664cf5 | 8 | [rsp+0x38] | `0x6664cf5  mov [rsp+0x38],r10` | Field +0x28 staged as extractor arg8 at call site `0x6664d46  call 0x674A3A0` [V] |
| 0x6664d46 | 8 | call | `0x6664d46  call 0x674A3A0` | Extractor call site 1: stride-0x38 records, arg8 = [r9+0x28] name pointer [V] |
| 0x6664eb1 | 8 | [r9] | `0x6664eb1  mov r13,[r9]` | Visitor stride-0x86 path: record field +0x0 read (`0x6664eb8  add r9,0x86`) [V] |
| 0x6664ef9 | 8 | [rsp+0x38] | `0x6664ef9  mov [rsp+0x38],r13` | Field +0x0 staged as extractor arg8 at call site `0x6664f4a  call 0x674A3A0` [V] |
| 0x6664f4a | 8 | call | `0x6664f4a  call 0x674A3A0` | Extractor call site 2: stride-0x86 records [V] |
| 0x6664760 | 8 | fn entry | `0x6664760  push rbp` | sub_6664760 UI record builder ("FrameBuilder - Insert UI") entry, size 0x2000, 0 static xrefs; vtable[0] of .rdata dispatch table at 0xf2be218 (`rdis vt 0xf2be218`) — invoked only indirectly [V] |
| 0x66647d7 | 16 | [rbx] | `0x66647d7  movups xmm0,[rbx]` | Record builder: 16 bytes (SSO string contents) from 2nd argument rbx (rdx at entry) [V] |
| 0x66647da | 16 | [rbp-0x40] | `0x66647da  movaps [rbp-0x40],xmm0` | Record builder: 16-byte name written into record local; `0x66648c4  lea r8,[rbp-0x40]` passes &name to sub_6664A00 [V] |
| 0x66647de | 8 | [rsi+0xF0] | `0x66647de  mov rax,[rsi+0xF0]` | Record builder: object field +0xF0 -> record local [rbp-0x28] [V] |
| 0x66648c8 | 8 | call | `0x66648c8  call 0x6664A00` | Record builder drives visitor dispatch that calls the extractor (rdx=&[rbp-0x28], r8=&16-byte name) [V] |
| 0xe840f6 | 8 | 0xe840f6 | `0xe840f6  lea rax,[0xF09AA70]` | Font object vtable pointer 0xF09AA70 loaded (sub_e84070 ctor) [V] |
| 0xe840fd | 8 | [rsi] | `0xe840fd  mov [rsi],rax` | Font object +0x0 = vtable 0xF09AA70 [V] |
| 0xe8483f | 8 | [r13+0x38] | `0xe8483f  mov qword ptr [r13+0x38],0xF` | Only object+0x38 writes in font init: SSO length/flags of font-descriptor sub-object, NOT a texture handle [V] |
| 0xe848dc | 8 | [r13+0x38] | `0xe848dc  mov [r13+0x38],r12` | Heap path: heap pointer stored at descriptor+0x38 — still a font NAME descriptor, not a texture handle [V] |
| 0xe9ddb5 | 8 | 0xe9ddb5 | `0xe9ddb5  lea rdx,[0xF5BAEF9]` | "ui_text_msdf" (12 bytes, fits 16-byte SSO) candidate glyph-atlas NAME; only 2 xrefs (sub_e9dd60, sub_4fc2f80 init-once registration), NOT linked to sub_674a3a0 arg8 — dead end [V] |
| 0x4fb3dff | 8 | 0x4fb3dff | `0x4fb3dff  lea r9,[0xF5B9FBB]` | "_ttf" suffix (0xF5B9FBB) — per-font pack texture path <name>_ttf.png, not the atlas name [V] |
| 0x4fbe694 | 8 | 0x4fbe694 | `0x4fbe694  lea r9,[0xF5BAEF0]` | "_ttfmsdf" suffix (0xF5BAEF0) — per-font pack texture path <name>_ttfmsdf.png, not the atlas name [V] |
| 0x58a1310 | 8 | 0x58a1310 | `0x58a1310  push rbp` | texload pack/named texture loader entry; callers sub_6b84680/sub_6ea2df0 — none font-related [V] |
| 0xEEC7570 | 8 | 0xEEC7570 | `0xEEC7570  jmp qword ptr [0xF9A9048]` | Import thunk = strlen-style (rcx = C string, rax tested as length via `0x76a731  cmp rax,0xF` in sub_76a6f0 SSO setter) — NOT a texture-handle fetch [V] |
| 0x4f78966 | 8 | call | `0x4f78966  call 0xEEC7570` | Glyph-texture fetch 0x4f78830: same strlen-style call on a C string — refuted as a texture-handle fetch; do not re-trace [V] |

## Answer

**(1) Where the GlyphTexture uniform value comes from — proven [V] (+ [V live]):** caller-provided arg8 ([rbp+0xEB8]) is loaded as a 16-byte SSO texture NAME via `0x674aa09  movups xmm0,[rax]` (rax = r15 = [rbp+0xEB8]), staged at `0x674aa0c  movaps [rbp+0xC10],xmm0`, count = 1 at `0x674aa13  mov qword ptr [rbp+0x910],1`, namePtr = sub_BCABA00 result (rbx) staged at `0x674aa1e  mov [rbp+0x918],rbx`, slot selected by walking the 16-byte-entry array at [rbp+0xBA0] (`0x674aa25  mov rax,[rbp+0xBA0]`, count `0x674aa2c  movzx r8d,word ptr [rbp+0xBAA]`) matching [uniform-record+0x28] name hash against FNV("GlyphTexture") from 0x129FA178 (`0x674aa42  mov r8,[0x129FA178]`, `0x674aa50  mov r10,[rcx]`, `0x674aa53  cmp [r10+0x28],r8`, walk stride `0x674aa59  add rcx,0x10`, index `0x674aa6f  shr ecx,4`), then bound via `0x674aa91  call 0x5679DB0`, which memcpy-writes 16 bytes via `0x5679df9  call 0xEEC6EC0` into the hash-selected slot (`0x5679dfe  mov byte ptr [r15+r14+0xC],1` sets the valid flag; `0x5679e53  mov [rsi+0x70],r8` mixes index+name hash into writer+0x70 FNV-1a state). sub_5679DB0 entry verified at `0x5679db0  push r15`, size 0x2000, 390 static inbound xrefs [V rdis]. The value is a TEXTURE NAME resolved by name at draw time, NOT a bgfx handle and NOT an atlas-handle fetch. Slot index for GlyphTexture = 0x000A (10), flag 0x01 — 30/30 samples [V live] in docs/data/live/glyph_bind.txt lines 1-30 (REG=value hit=N hex dumps at entry of sub_5679DB0).

**(2) Which object field holds the texture handle — proven [V]: NONE.** The object+0x38 claim is contradicted: the full sub_674a3a0 listing reads object r14=[rbp+0xE80] at +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244, never +0x38, and descscan2 of sub_6664760 shows object reads +0x000/+0x020/+0x028/+0x0f0/+0x100/+0x260/+0x268/+0x358/+0x36c/+0x370/+0x380 with +0x38 in a gap — never read. The value arrives as caller arg8; the field that carries it is the UI item record field — [r9+0x28] (stride-0x38 records, `0x6664cb0  mov r10,[r9+0x28]`) or [r9] (stride-0x86 records, `0x6664eb1  mov r13,[r9]`) — staged as arg8 at `0x6664cf5` / `0x6664ef9`. The only object+0x38 writes in font init (`0xe8483f`, `0xe848dc`) are SSO length/flags of font-descriptor sub-objects, not a texture handle.

**(3) Who writes that field — OPEN (blocking):** sub_6664760 writes the record from its arguments (`0x66647d7  movups xmm0,[rbx]` -> `0x66647da  movaps [rbp-0x40],xmm0`; `0x66648c8  call 0x6664A00` drives dispatch to the extractor) but `xref.py callers 0x6664760` = 0; it is vtable[0] of the .rdata dispatch table at 0xf2be218 (`rdis vt 0xf2be218`: slot 0 sub_6664760 size 0x2000), `rdis imm 0xf2be218` = 0 hits and `xref.py ptr 0xf2be218` = 0 hits, so the vtable address is stored nowhere and its caller is not statically locatable — indirect dispatch only. The writer of the UI record name field that becomes sub_674a3a0's arg8 is unknown statically.

**(4) Glyph atlas identity / load site — pending [live]:** no atlas name string proven ("ui_text_msdf" dead end), no createTexture/createDynamicTexture/updateTexture call ANYWHERE in .text, texload 0x58a1310 has no font caller — the atlas is a named pack texture resolved by name at draw time. The 16-byte NAME and its load site come from the queued live capture l14c_uniform_writer (0x5679db0); if it returns the name, its load site is found with `rdis str` on that string / its hash.

## CLOSES?

NO — single blocking fact (missing REVERSING / live proof): the live 16-byte glyph atlas NAME bytes (the atlas identity) bound as GlyphTexture at slot index 0x000A have not been captured, and with them the writer/load site of the UI record name field (inbound caller of sub_6664760 via .rdata slot 0xf2be218) and the atlas creation/load site. `python tools/sigs/livemem.py status` -> game not running (livemem unavailable per brief rule 30); l14c_uniform_writer at 0x5679db0 (size 0x100/256, max 8) is already QUEUED pending — do not re-add; l14c_glyph_draw (0x674a3a0) and l14c_record_builder (0x6664760) already ran 0 hits each — do not re-request. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units) and the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot; slot 0x000A=10 confirmed [V live]). This is a REVERSING blocker (live NAME RVA/bytes unknown), so per the DEFERRED TESTING rule no BIGBANG_TESTS.md section is appended.

## What I tried that failed (new angles; static r1-r22 angles not redone)

- livemem: `python tools/sigs/livemem.py status` -> game not running; unavailable until the game runs (brief rule 30).
- l14c_glyph_draw (0x674a3a0) and l14c_record_builder (0x6664760): state=done, hits=0, samples=0 — neither function fires on the live glyph-text path; do NOT re-request (orchestrator 2026-11-22 22:35).
- l14c_uniform_writer (0x5679db0): already QUEUED pending (state=pending) — not re-requested (duplicate pending names rejected); awaiting orchestrator run when the game is up; no result yet; hotness (0 hits or 8 non-glyph samples of 390 static call sites) undetermined until the result exists.
- `rdis imm 0xf2be218` (0 hits), `xref.py ptr 0xf2be218` (0 hits), `rdis vt 0xf2be218` (vtable found: sub_6664760 = vtable[0] size 0x2000, but no stored reference to the vtable address -> caller not locatable), `dispfun.py 0x6664760` (no output), descscan2 of sub_6664760 (object fields enumerated; +0x38 never read; caller still unresolved).
- Full re-dump of sub_674a3a0: 0 reads of object+0x38 — contradicts the object+0x38 SSO-name claim; the value is caller arg8.
- Static angles from r1-r17 remain exhausted: object+0x38 contradicted; no createTexture/createDynamicTexture/updateTexture ANYWHERE in .text; no glyph-atlas name string; font init/reset create no textures; "ui_text_msdf"/"glyph_section_*"/"_ttf"/"_ttfmsdf" all dead ends; `0xEEC7570` call at 0x4f78966 refuted as strlen, not a texture fetch.

## TOOL REQUESTS

- l14c_uniform_writer | `python tools/livecap/request.py add l14c_uniform_writer 0x5679db0 --size 256 --max 8 --why "L14c: UniformBlock::setVec4Array entry; capture the GlyphTexture slot write (index 0x000A): r8 = {count=1, namePtr}; the dumped 16 bytes at namePtr are the atlas NAME [LIVE]. ret= names the caller"` | ALREADY QUEUED (state=pending) in docs/progress/capture_requests.json per orchestrator hint 2026-11-22 22:35 — do NOT re-add (duplicate pending names rejected); read results with `python tools/livecap/request.py result l14c_uniform_writer`. If the result is 0 hits or 8 non-glyph samples, 0x5679db0 is too hot: state that and answer NO with exactly that; the single unknown stays the live 16-byte NAME bytes.
- livemem read | none possible now | `python tools/sigs/livemem.py status` -> game not running; brief rule 30: write the request in the progress file instead; retry once the game is up (deferred in-game test).
- No helper script written; none needed (all evidence from rdis.exe dis/fn/imm/vt, xref.py callers/str/ptr, descscan2.py; no _tmp files left behind).

## NEXT
DONE
