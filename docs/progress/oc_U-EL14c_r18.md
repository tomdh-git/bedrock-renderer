## NEXT
DONE

# UNIT U-EL14c: L14c Text/font — glyph atlas (pending part)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending". The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c / U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be + MSDF via 0xF2EA00, all in UI extractor 0x674a3a0). This unit covers ONLY the pending part: the glyph atlas — where the GlyphTexture uniform's 16-byte texture NAME comes from (who writes it), and where the glyph atlas texture is created/updated.

Static search for the UI record name writer is exhausted (indirect dispatch slot 0xf2be218; sub_6664760 has 0 static xrefs) — not redone per the orchestrator hint.

## Already proven (not redone)

- GlyphTexture uniform registered at 0x674dca3 (lea rdx,[0xF5C6DD7] "GlyphTexture", hashed via 0x674dcb4 call 0x79580, registered via 0x674dd8f call 0x73150) — init binding, NOT a texture-creation site [V]
- No createTexture/createDynamicTexture/updateTexture call anywhere in .text (imm scan 0 hits) [V]
- No "GlyphAtlas"/"FontTexture" string in .rdata; font init 0xE82E00->0xE84070 and reset 0x186e6a0 create no textures [V]
- GlyphTexture draw-time bind: 16-byte SSO texture NAME from caller arg8, NOT a bgfx handle; sub_5679DB0 memcpy 16 bytes into the hash-selected slot (slot index live: 0x000A = 10, 30/30 samples in docs/data/live/glyph_bind.txt) [V] [V live]
- sub_5679DB0 decode proven [V]: index u16 from {index,flag} param, entry-array base writer+0x30, entry[index].+0x08 slot byte-offset, dst = writer+0x28+offset, src = namePtr, size = count*16 = 16, memcpy 16 via 0x5679df9 call 0xEEC6EC0, entry[index].+0x0C flag = 1

## This run — live path

- `python tools/sigs/livemem.py status`: "game not running (no Minecraft.Windows.exe process). Request a capture in your progress file instead." — livemem UNAVAILABLE per brief rule 30 (read-only memory read needs the game process); no target address to read [V live]
- `0x5679db0` verified as a function entry [V rdis]: `0x5679db0  push r15` ... `sub rsp,0x28`, size 0x2000, 390 static inbound xrefs — this IS UniformBlock::setVec4Array/setUniform, called on every uniform write (hot). Body matches the sub_5679DB0 decode above verbatim (0x5679dbf..0x5679dfe).
- Capture `l14c_uniform_writer` at 0x5679db0 (size 256, max 8) is ALREADY QUEUED pending in docs/progress/capture_requests.json (state pending, per orchestrator hint 2026-11-22). Do NOT re-request (request.py rejects duplicate pending rva). l14c_glyph_draw (0x674a3a0) and l14c_record_builder (0x6664760) already ran: 0 hits each in 60 s — not re-requested per ORCHESTRATOR 2026-11-22 22:35.
- 0x5679db0 is hot (390 static inbound xrefs, one write per uniform). "Too hot" (8 samples all non-glyph) can only be judged from capture hit data once the orchestrator runs it with the game up; not determinable statically.

## Offset table (one row per distinct offset; all its sites listed; verbatim lines from the exe via rdis; sizes from the instruction)

| Name | RVA or offset | Size | Site | Verbatim `0xRVA  instr` proof | Meaning ([V]/[I]/[-]) |
|---|---|---|---|---|---|
| GlyphTexture name string | 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" string (0xF5C6DD7) hashed at 0x674dcb4 and registered at 0x674dd8f — uniform binding at init, NOT texture creation [V] |
| FNV hash call | 0x674dcb4 | 8 | call | `0x674dcb4  call 0x79580` | FNV-1a hash of "GlyphTexture"; result stored at 0x129FA178 [V] |
| arg8 load | 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | caller-provided name pointer (arg8) loaded into r15 [V] |
| 16-byte name load | 0x674aa09 | 16 | [rax] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME from *arg8 — GlyphTexture value is a NAME, not a bgfx handle [V] |
| value stage | 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as uniform value buffer [V] |
| count | 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | draw count = 1 => 16-byte copy [V] |
| namePtr stage | 0x674aa1e | 8 | [rbp+0x918] | `0x674aa1e  mov [rbp+0x918],rbx` | name pointer staged for the bind call [V] |
| uniform slot array base | 0x674aa25 | 8 | [rbp+0xBA0] | `0x674aa25  mov rax,[rbp+0xBA0]` | base of the 16-byte-entry uniform slot array (extract side) [V] |
| entry count | 0x674aa2c | 2 | [rbp+0xBAA] | `0x674aa2c  movzx r8d,word ptr [rbp+0xBAA]` | u16 entry count of the array [V] |
| hash key | 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | search key = FNV-1a hash of "GlyphTexture" [V] |
| entry walk | 0x674aa50 | 8 | [rcx] | `0x674aa50  mov r10,[rcx]` | array entry[0] uniform-record pointer; walk stride 0x10 [V] |
| hash compare | 0x674aa53 | 8 | [r10+0x28] | `0x674aa53  cmp [r10+0x28],r8` | [record+0x28] name hash vs GlyphTexture hash; match selects the slot [V] |
| slot index | 0x674aa6f | 4 | ecx | `0x674aa6f  shr ecx,4` | slot index = (matched entry - array base) / 16 [V] |
| index store | 0x674aa72 | 2 | [rbp+0x5F0] | `0x674aa72  mov [rbp+0x5F0],cx` | u16 slot index stored (live: 0x000A = 10, slot 10) [V] |
| flag store | 0x674aa79 | 1 | [rbp+0x5F2] | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | u8 flag byte = 1 stored next to the index [V] |
| rdx arg | 0x674aa80 | 8 | rdx=&[rbp+0x5F0] | `0x674aa80  lea rdx,[rbp+0x5F0]` | {u16 index, u8 flag} passed as rdx [V] |
| r8 arg | 0x674aa87 | 8 | r8=&[rbp+0x910] | `0x674aa87  lea r8,[rbp+0x910]` | {qword count=1, qword namePtr} passed as r8 [V] |
| this arg | 0x674aa8e | 8 | rcx=r15 | `0x674aa8e  mov rcx,r15` | writer object passed as this (rcx) to sub_5679DB0 [V] |
| bind call | 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | draw-time GlyphTexture bind: writer passes index + name to sub_5679DB0 [V] |
| setUniform entry | 0x5679db0 | 8 | 0x5679db0 | `0x5679db0  push r15` | UniformBlock::setVec4Array/setUniform entry; 390 static inbound xrefs = hot (every uniform write) [V rdis] |
| index read | 0x5679dbf | 2 | [rdx] | `0x5679dbf  movzx r14d,word ptr [rdx]` | index u16 read from {index,flag} param [V rdis] |
| entry-array base | 0x5679dc3 | 8 | [rcx+0x30] | `0x5679dc3  mov r15,[rcx+0x30]` | entry-array base (writer+0x30) [V rdis] |
| slot offset | 0x5679dcb | 2 | [r15+r14+8] | `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` | entry[index].+0x08 slot position u16 [V rdis] |
| dst | 0x5679ded | 8 | [rsi+0x28] | `0x5679ded  add rcx,[rsi+0x28]` | dst = writer+0x28+slot position [V rdis] |
| src | 0x5679df1 | 8 | [rdi+8] | `0x5679df1  mov rdx,[rdi+8]` | src = name pointer [V rdis] |
| size | 0x5679df5 | 8 | r8 | `0x5679df5  shl r8,4` | size = count*16 = 16 [V rdis] |
| memcpy | 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | memcpy(dst,src,16) — WRITES a 16-byte TEXTURE NAME into the slot, NOT a bgfx handle [V rdis] |
| flag set | 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | entry[index].+0x0C valid flag set to 1 [V rdis] |

## Answer

**GlyphTexture is bound BY NAME.** At draw time sub_674a3a0 hashes "GlyphTexture" (`0x674dca3  lea rdx,[0xF5C6DD7]` -> `0x674dcb4  call 0x79580`), walks the 16-byte-entry uniform slot array at [rbp+0xBA0] matching [record+0x28] name hash against the key from `0x674aa42  mov r8,[0x129FA178]`, selects the slot (live: index 0x000A = 10), and calls `0x674aa91  call 0x5679DB0`. sub_5679DB0 (entry verified at `0x5679db0  push r15`) then `0x5679df9  call 0xEEC6EC0` memcpy's 16 bytes from the namePtr into the slot and sets the valid flag — a 16-byte TEXTURE NAME, never a bgfx handle, never created by font code.

**Who writes the 16-byte name value:** the caller of sub_674a3a0 (UI record builder sub_6664760 via indirect dispatch slot 0xf2be218; 0 static xrefs) — not statically locatable.

**Glyph atlas texture creation/update site:** not found — no createTexture/createDynamicTexture call anywhere in .text; no glyph-atlas name string in .rdata; font paths create no textures; all texture creation is vtable-indirect render-thread work (RendererContext slots 26/28, texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj); texload 0x58a1310 has no font caller.

**Live status this run:** game not running (`livemem.py status`: "game not running"), so livemem is unavailable and no live NAME was read. Capture l14c_uniform_writer (0x5679db0, size 256, max 8) is already QUEUED pending; it is the single live trace that can return the 16-byte atlas NAME [LIVE], after which its load site is found with `rdis str` on that string / its hash.

## CLOSES?

NO — single blocking fact: the live 16-byte atlas NAME is not yet obtained. Capture l14c_uniform_writer at 0x5679db0 is queued pending but the game is not running (livemem unavailable per brief rule 30), so the NAME cannot be read or its load site located this run; 0x5679db0 is hot (390 static inbound xrefs) so "too hot" can only be judged from capture hit data. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (prior units) and the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot; slot 0x000A = 10 confirmed [V live]).

## TOOL REQUESTS

- l14c_uniform_writer (0x5679db0) | already QUEUED pending in docs/progress/capture_requests.json (size 256, max 8); do NOT re-request | orchestrator runs it when the game is up; if it returns the 16-byte atlas NAME that closes "glyph atlas"; if 0x5679db0 proves too hot (8 samples all non-glyph), answer NO with exactly that
- l14c_glyph_draw / l14c_record_builder | already ran, 0 hits each | do NOT request again per ORCHESTRATOR 2026-11-22 22:35
- No helper script written; none needed
