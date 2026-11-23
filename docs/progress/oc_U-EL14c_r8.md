## NEXT
DONE

# Unit U-EL14c: L14c Text/font — glyph atlas (static angles exhausted; live-capture angle)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending" (BGFX_MAP.md 6ce anchors UI pass extractor 0x674a3a0 and lists "Still pending: glyph atlas management"). The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c/U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be, all in UI extractor 0x674a3a0). This unit covers ONLY the pending part: the GLYPH ATLAS — the 16-byte atlas NAME bound as GlyphTexture at draw time, who writes it, and its load site.

## Blocking fact (single unknown)

The live 16-byte glyph atlas NAME bytes have never been captured. The name is a 16-byte SSO texture name passed as sub_674a3a0 arg8 ([rbp+0xEB8]) and written into the GlyphTexture uniform slot by sub_5679DB0; the name pointer (namePtr) reaches sub_5679DB0 as r8+8, but the NAME bytes at *namePtr were never dumped because the game is not running (`python tools/sigs/livemem.py status` -> "game not running (no Minecraft.Windows.exe process)", checked twice this run) so no livemem read or live capture can execute. The capture queue is at its <=4-pending limit with 4 pending l14c_name_resolver* requests (0xBCABA00, 0x67417F0, 0x6745440, 0x673D150), so `request.py add ... 0x5679db0` cannot be queued until a slot frees. All static angles are exhausted (r1-r7): sub_6664760 (the writer of the record name field) has 0 static xrefs and is reached only via unresolved indirect dispatch .rdata slot 0xf2be218; no createTexture/createDynamicTexture call anywhere in .text; no glyph-atlas name string in .rdata. With the NAME unknown, its writer and load site are unknown too.

## Offset table (one row per distinct offset; all sites listed; verbatim instr line; size from instruction; [V]/[I]/[-])

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string loaded for FNV hashing at init; NOT texture creation [V] |
| 0x674dcb4 | 8 | call | `0x674dcb4  call 0x79580` | FNV-1a hash of "GlyphTexture" [V] |
| 0x674dd81 | 8 | [0x129FA178] | `0x674dd81  mov [0x129FA178],rcx` | "GlyphTexture" hash stored as draw-time lookup key [V] |
| 0x674dd8f | 8 | call | `0x674dd8f  call 0x73150` | uniform registration call [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | arg8 caller-provided name pointer -> r15 [V] |
| 0x674a4d1 | 8 | [rbp+0xE80] | `0x674a4d1  mov r14,[rbp+0xE80]` | object base -> r14; object never read at +0x38 [V] |
| 0x674aa09 | 16 | [rax] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME from *arg8 — GlyphTexture value is a NAME, not a bgfx handle [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as uniform value buffer [V] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | draw binding count = 1 => 16-byte copy [V] |
| 0x674aa1e | 8 | [rbp+0x918] | `0x674aa1e  mov [rbp+0x918],rbx` | namePtr (sub_bcaba00 result) staged [V] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | search key = FNV("GlyphTexture") hash [V] |
| 0x674aa50 | 8 | [rcx] | `0x674aa50  mov r10,[rcx]` | uniform slot array entry = qword pointer to uniform record; walk stride `0x674aa59  add rcx,0x10` [V] |
| 0x674aa53 | 8 | [r10+0x28] | `0x674aa53  cmp [r10+0x28],r8` | [uniform-record+0x28] name hash compared with GlyphTexture hash; match selects slot [V] |
| 0x674aa6f | 4 | ecx | `0x674aa6f  shr ecx,4` | slot index = (matched entry - array base) / 16 [V] |
| 0x674aa72 | 2 | [rbp+0x5F0] | `0x674aa72  mov [rbp+0x5F0],cx` | u16 slot index stored [V] |
| 0x674aa79 | 1 | [rbp+0x5F2] | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | u8 valid/bound flag = 1 [V] |
| 0x674aa80 | 8 | rdx=&[rbp+0x5F0] | `0x674aa80  lea rdx,[rbp+0x5F0]` | {u16 index, u8 flag} passed as rdx to sub_5679DB0 [V] |
| 0x674aa87 | 8 | r8=&[rbp+0x910] | `0x674aa87  lea r8,[rbp+0x910]` | {qword count=1, qword namePtr} passed as r8 to sub_5679DB0 [V] |
| 0x674aa8e | 8 | rcx=r15 | `0x674aa8e  mov rcx,r15` | writer object (stack struct [rbp+0xB70]) as this for sub_5679DB0 [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | draw-time GlyphTexture bind via uniform/subcomponent writer [V] |
| 0x5679dbf | 2 | word ptr [rdx] | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679DB0: count/index word read (1) [V rdis] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr, size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the binding slot [V rdis] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0xC valid/bound flag set to 1 [V rdis] |
| 0x5679db0 | 8 | fn entry | `0x5679db0  push r15` | sub_5679DB0 = UniformBlock::setVec4Array entry (size 0x2000, 390 static callers per xref callers) — the capture target [V rdis] |
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | Visitor case 3 (sub_6664a00), stride-0x38 record loop `0x6664cbb  add r9,0x38`: record field +0x28 = qword texture-NAME pointer [V descscan2 case 3] |
| 0x6664cf5 | 8 | [rsp+0x38] | `0x6664cf5  mov [rsp+0x38],r10` | field +0x28 staged as extractor arg8 [V] |
| 0x6664d46 | 8 | call | `0x6664d46  call 0x674A3A0` | extractor call site 1: stride-0x38 records, arg8 = [r9+0x28] name pointer [V] |
| 0x6664eb1 | 8 | [r9] | `0x6664eb1  mov r13,[r9]` | Visitor stride-0x86 path: record field +0x0 read (`0x6664eb8  add r9,0x86`) [V] |
| 0x6664ef9 | 8 | [rsp+0x38] | `0x6664ef9  mov [rsp+0x38],r13` | field +0x0 staged as extractor arg8 [V] |
| 0x6664f4a | 8 | call | `0x6664f4a  call 0x674A3A0` | extractor call site 2: stride-0x86 records [V] |
| 0x6664760 | 8 | fn entry | `0x6664760  push rbp` | sub_6664760 entry ("FrameBuilder - Insert UI" record builder, size 0x2000, 0 static xrefs) [V] |
| 0x66647d7 | 16 | [rbx] | `0x66647d7  movups xmm0,[rbx]` | record builder: 16 bytes (SSO string contents) from 2nd argument rbx [V] |
| 0x66647da | 16 | [rbp-0x40] | `0x66647da  movaps [rbp-0x40],xmm0` | record builder: 16-byte name written into record local; `0x66648c4  lea r8,[rbp-0x40]` passes &name to sub_6664A00 [V] |
| 0x66647de | 8 | [rsi+0xF0] | `0x66647de  mov rax,[rsi+0xF0]` | record builder: object field +0xF0 -> record local [rbp-0x28] [V] |
| 0x66648c8 | 8 | call | `0x66648c8  call 0x6664A00` | record builder drives dispatch that calls the extractor (rdx=&[rbp-0x28], r8=&16-byte name) [V] |
| 0xe840f6 | 8 | 0xe840f6 | `0xe840f6  lea rax,[0xF09AA70]` | font object vtable pointer 0xF09AA70 loaded (sub_e84070 ctor) [V] |
| 0xe840fd | 8 | [rsi] | `0xe840fd  mov [rsi],rax` | font object +0x0 = vtable 0xF09AA70 [V] |
| 0xe8483f | 8 | [r13+0x38] | `0xe8483f  mov qword ptr [r13+0x38],0xF` | only object+0x38 writes in font init: SSO length/flags of font-descriptor sub-object, NOT a texture handle [V] |
| 0xe848dc | 8 | [r13+0x38] | `0xe848dc  mov [r13+0x38],r12` | heap path: heap pointer stored at descriptor+0x38 — still a font NAME descriptor, not a texture handle [V] |
| 0xe9ddb5 | 8 | 0xe9ddb5 | `0xe9ddb5  lea rdx,[0xF5BAEF9]` | "ui_text_msdf" (12 bytes, fits 16-byte SSO) candidate glyph-atlas NAME; only 2 xrefs (sub_e9dd60, sub_4fc2f80 init-once registration), NOT linked to sub_674a3a0 arg8 — dead end [V] |
| 0x4fb3dff | 8 | 0x4fb3dff | `0x4fb3dff  lea r9,[0xF5B9FBB]` | "_ttf" suffix (0xF5B9FBB) — per-font pack texture path <name>_ttf.png, not the atlas name [V] |
| 0x4fbe694 | 8 | 0x4fbe694 | `0x4fbe694  lea r9,[0xF5BAEF0]` | "_ttfmsdf" suffix (0xF5BAEF0) — per-font pack texture path <name>_ttfmsdf.png, not the atlas name [V] |
| 0x58a1310 | 8 | 0x58a1310 | `0x58a1310  push rbp` | texload pack/named texture loader entry; callers sub_58b5220/sub_6a8b620/sub_6b80db0 — none font-related [V] |
| 0xEEC7570 | 8 | 0xEEC7570 | `0xEEC7570  jmp qword ptr [0xF9A9048]` | import thunk = strlen-style (rcx = C string, rax tested as length) — NOT a texture-handle fetch [V] |
| 0x4f78966 | 8 | call | `0x4f78966  call 0xEEC7570` | glyph-texture fetch 0x4f78830: same strlen-style call — refuted as a texture-handle fetch (refuted; do not re-trace) [V] |

## Answer

**(1) Where the GlyphTexture uniform value comes from — proven [V]:** caller-provided arg8 ([rbp+0xEB8]); its 16 bytes are loaded as a texture NAME via `0x674aa09  movups xmm0,[rax]` (rax = r15 = [rbp+0xEB8]), staged at `0x674aa0c  movaps [rbp+0xC10],xmm0`, count = 1 at `0x674aa13  mov qword ptr [rbp+0x910],1`, namePtr (sub_bcaba00 result rbx) staged at `0x674aa1e  mov [rbp+0x918],rbx`, slot selected by matching [uniform-record+0x28] name hash against FNV("GlyphTexture") at 0x129FA178 (`0x674aa42  mov r8,[0x129FA178]`, `0x674aa53  cmp [r10+0x28],r8`, walk stride `0x674aa59  add rcx,0x10`, index `0x674aa6f  shr ecx,4`), then bound via `0x674aa91  call 0x5679DB0`, which memcpy-writes 16 bytes via `0x5679df9  call 0xEEC6EC0` into the hash-selected slot (`0x5679dfe  mov byte ptr [r15+r14+0xC],1` sets the valid flag). The value is a TEXTURE NAME resolved by name at draw time, NOT a bgfx handle.
**[V live corroboration]** docs/data/live/glyph_bind.txt: 30/30 samples of sub_5679DB0 entries; RDX slot index 0x000A = 10 (the GlyphTexture slot), flag 0x01; R8 = {count=1, namePtr} exactly matching sub_5679DB0's args (`0x674aa80  lea rdx,[rbp+0x5F0]`, `0x674aa87  lea r8,[rbp+0x910]`) [V preflight + V live].

**(2) Which object field holds the texture handle — proven [V]: NONE.** The object+0x38 claim is contradicted by the full sub_674a3a0 listing: object r14 = [rbp+0xE80] is read at +0x10/+0x18/+0x1A0/+0x1A1/+0x1A4/+0x1D8/+0x1DA/+0x1E8/+0x1F8/+0x1FC/+0x1FE/+0x20C/+0x21C/+0x244 and never at +0x38. The value arrives as caller arg8; the field that carries it is the UI item record field — [r9+0x28] (stride-0x38 records, `0x6664cb0  mov r10,[r9+0x28]`) or [r9] (stride-0x86 records, `0x6664eb1  mov r13,[r9]`) — staged as arg8 at `0x6664cf5` / `0x6664ef9`. The only [r13+0x38] writes in font init (`0xe8483f`, `0xe848dc`) are SSO length/flags of font-descriptor sub-objects, not a texture handle.

**(3) Who writes that field — OPEN (blocking):** sub_6664760 writes the record from its arguments (`0x66647d7  movups xmm0,[rbx]` -> `0x66647da  movaps [rbp-0x40],xmm0`; `0x66648c8  call 0x6664A00` drives dispatch to the extractor) but `xref.py callers 0x6664760` = 0 and the only reference is unresolved .rdata slot 0xf2be218 — indirect dispatch, caller not statically locatable. BGFX_MAP.md 6ce confirms the chain 0x6664760 ->(0x218) 0x6664a00 -> 0x674a3a0 exists statically, but the inbound caller of sub_6664760 (the writer of the UI record name field [r9+0x28] stride-0x38 / [r9] stride-0x86) is unknown.

**(4) Glyph atlas identity / load site — pending [live]:** no "GlyphAtlas"/"FontTexture" string exists; xref str "glyph_" returns only UI section labels; "ui_text_msdf" at 0xF5BAEF9 (`0xe9ddb5  lea rdx,[0xF5BAEF9]`) is unlinked (init-once registration only, no link to sub_674a3a0 arg8); "_ttf"/"_ttfmsdf" suffixes are per-font pack paths, not the atlas name; no createTexture/createDynamicTexture call ANYWHERE in .text; texload 0x58a1310 (`0x58a1310  push rbp`) has no font caller; font init 0xE82E00->0xE84070 (vtable 0xF09AA70, `0xe840f6  lea rax,[0xF09AA70]` / `0xe840fd  mov [rsi],rax`) creates no textures. The atlas is a named pack texture resolved by name at draw time; its 16-byte NAME and load site require live data.

## CLOSES?

CLOSES? NO — the single blocking fact: the live 16-byte glyph atlas NAME bytes (at *namePtr; namePtr staged as sub_5679DB0's r8+8, slot index 0x000A = GlyphTexture) and the writer/load site of that name are unknown. Game is not running (livemem unavailable) and the capture queue is full (4 pending l14c_name_resolver* requests), so no live data can be obtained this run. Everything else in the item IS proven by [V]/[V live] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units), the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot; slot index 0x000A=10 confirmed [V live] in docs/data/live/glyph_bind.txt), and that NO object field holds the handle (object+0x38 contradicted by the full listing).

## What I tried that failed (this run — new angles; static r1-r7 angles not redone)

- `python tools/sigs/livemem.py status` -> "game not running (no Minecraft.Windows.exe process)" x2; per the brief, no live memory access; write the request and stop.
- request.py queue already holds 4 pending l14c_name_resolver* requests; request.py enforces <=4 pending per batch, so the 0x5679db0 capture cannot be added until the orchestrator runs a batch and frees a slot.
- l14c_glyph_draw / l14c_record_builder: state=done, hits=0, samples=0 (docs/data/live/_status.txt) — sub_674a3a0 and sub_6664760 never fire on the live path; do not re-request (orchestrator 2026-11-22).
- Static angles from r1-r7 remain exhausted: indirect dispatch slot 0xf2be218 (0 static callers); object+0x38 contradicted by the full sub_674a3a0 listing; no createTexture/createDynamicTexture anywhere in .text; no glyph-atlas name string; font init/reset create no textures.

## TOOL REQUESTS

- l14c_glyph_texture_name | `python tools/livecap/request.py add l14c_glyph_texture_name 0x5679db0 --size 0x100 --max 8 --why "L14c: UniformBlock::setVec4Array entry; capture the GlyphTexture slot write (index 0x000A): r8 = {count=1, namePtr} gives the name pointer whose 16-byte target is the atlas NAME [LIVE]; ret= names the caller/writer"` | blocked this run — capture queue full (4 pending l14c_name_resolver* requests; request.py <=4-pending limit); submit next run once a slot frees. Not too hot: 390 static call sites per `xref.py callers 0x5679db0`, bounded, and max-8 sampled execute-breakpoint logging stays tractable; filter hits to the GlyphTexture slot write (index 0x000A) so the 8 samples are name writes.
