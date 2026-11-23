## NEXT
DONE

# Unit U-EL14c: L14c Text/font — glyph atlas (static angles exhausted; live capture pending)

## Scope

Checklist item L14c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending" (BGFX_MAP.md 6ce anchors UI pass extractor 0x674a3a0 and lists "Still pending: glyph atlas management"). The SDF glyph uniforms + FONT_TYPE half is closed (prior units U-I5c/U-EI5c: GlyphTexture 0x674dca3, GlyphSmoothRadius 0x674ddbe, GlyphHeight 0x674e06a, FONT_TYPE 0x674d2bf/0x674d6be, all in UI extractor 0x674a3a0). This unit covers ONLY the pending part: the GLYPH ATLAS — the 16-byte atlas NAME bound as GlyphTexture at draw time, who writes it, and its load site.

## Blocking fact (single unknown)

The live 16-byte glyph atlas NAME bytes have never been captured. The name is caller-provided arg8 ([rbp+0xEB8]) in UI extractor 0x674a3a0, loaded as a 16-byte SSO texture NAME and written into the hash-selected GlyphTexture uniform slot by sub_5679DB0 (`0x5679df9  call 0xEEC6EC0`, memcpy 16). The field that carries it is the UI item record field ([r9+0x28] stride-0x38 / [r9] stride-0x86 via sub_6664a00), assembled by record builder sub_6664760, whose inbound caller is reachable only through unresolved .rdata indirect-dispatch slot 0xf2be218 (`xref.py callers 0x6664760` = 0; `xref.py ptr 0x6664760` -> .rdata slot 0xf2be218). No createTexture/createDynamicTexture call exists ANYWHERE in .text, texload 0x58a1310 has no font caller, no "GlyphAtlas"/"FontTexture" string exists, and candidate "ui_text_msdf" (0xF5BAEF9) has no static link to sub_674a3a0's arg8. So the atlas is a named pack texture resolved by name at draw time; its NAME, writer and load site require live data.

## Live capture status (this run)

Per orchestrator 2026-11-22 22:35, the two earlier captures must NOT be re-requested (0 hits each, 60 s, loaded world, text visible):
- l14c_glyph_draw 0x674a3a0 size 0x200 max 8: state=done, hits=0 (docs/data/live/l14c_glyph_draw.txt empty)
- l14c_record_builder 0x6664760 size 0x200 max 8: state=done, hits=0 (docs/data/live/l14c_record_builder.txt empty)

docs/data/live/_status.txt confirms: RUNNING t=7737; l14c_glyph_draw hits=0 samples=0; l14c_record_builder hits=0 samples=0.

The replacement capture was queued by the prior run and must NOT be re-added (duplicate pending names are rejected):
- l14c_uniform_writer 0x5679db0 size 0x100 max 8: state=pending — `python tools/livecap/request.py result l14c_uniform_writer` returns "no result yet (orchestrator has not run it)". UniformBlock::setVec4Array entry; 390 static call sites, bounded, max-8 entry sampling; hits filtered to the GlyphTexture slot write (index 0x000A = 10); the dumped 16 bytes at namePtr are the atlas NAME [LIVE].

livemem: `python tools/sigs/livemem.py status` -> "game not running (no Minecraft.Windows.exe process). Request a capture in your progress file instead." Per brief rule 30 the game is closed and I may not start it; livemem is a read-only last resort and is unavailable until the game runs. No livemem target address exists anyway (name-buffer addresses are past-run ASLR values).

## New angles tried this run (not redone from r1-r8)

- `rdis vt 0xf2be218` -> 0xf2be218 IS a vtable (.rdata dispatch table): slot 0 = sub_6664760 (size 0x218, `push rbp`), slot 1 = sub_6655de0, slot 2 = sub_66466e0, slot 3 = sub_6640ae0, remaining slots non-code pointers. So sub_6664760 is vtable[0] of a UI-builder dispatch table and is invoked only indirectly through this vtable — no direct call exists.
- `rdis imm 0xf2be218` -> 0 hit(s): no instruction references the slot/vtable address.
- `xref.py ptr 0xf2be218` -> no output (0 hits): the vtable address is stored nowhere in the image (loader/resolution indirection), so the builder's inbound caller is not statically locatable.
- `python tools/sigs/descscan2.py --start 0x6664760 --end 0x6664978 --reg rsi` on the builder: object field reads +0x000 qword (@6664880), +0x020 qword (@6664868 x2), +0x028 qword (@666481a), +0x0f0 qword (@66647de), +0x100 addr lea (@6664804), +0x260 qword (@666480f), +0x268 xmmword movups (@666485d), +0x358 qword (@6664898), +0x36c dword (@6664877), +0x370 byte movzx (@66648b2), +0x380 qword (@66647f9). GAPS inside [0,0x388): 0x8-0x20, 0x30-0xf0, 0xf8-0x260, 0x278-0x358, 0x360-0x36c, 0x371-0x380 — object field +0x38 is in a gap and is NEVER read, refuting object+0x38 at the builder too. The builder writes the record buffer (16-byte name from rbx via `0x66647d7  movups xmm0,[rbx]` -> `0x66647da  movaps [rbp-0x40],xmm0`) and drives dispatch via `0x66648c8  call 0x6664A00`.
- Static angles from r1-r8 remain exhausted: no createTexture/createDynamicTexture ANYWHERE in .text; no glyph-atlas name string; "ui_text_msdf"/"_ttf"/"_ttfmsdf" dead ends; 0xEEC7570 call at 0x4f78966 refuted as strlen, not a texture fetch.

## Offset table (one row per distinct offset; all its sites listed; verbatim instr line; size from instruction; [V]/[I]/[-])

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------------|------------------------------------|-----------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string loaded for FNV hashing at init — uniform registration, not texture creation [V] |
| 0x674dcb4 | 8 | call | `0x674dcb4  call 0x79580` | FNV-1a 64 hash of "GlyphTexture" [V] |
| 0x674dd81 | 8 | [0x129FA178] | `0x674dd81  mov [0x129FA178],rcx` | "GlyphTexture" hash stored as draw-time lookup key [V] |
| 0x674dd8f | 8 | call | `0x674dd8f  call 0x73150` | uniform registration call [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: caller arg8 pointer loaded into r15 [V] |
| 0x674a9ff | 8 | rax=r15=[rbp+0xEB8] | `0x674a9ff  mov rax,r15` | rax = caller pointer; feed for the 16-byte load at 0x674aa09 [V] |
| 0x674aa09 | 16 | [rax]=*[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture NAME loaded from caller-provided arg8 — GlyphTexture uniform value is a NAME, not a bgfx handle [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as uniform value buffer [V] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | Draw binding count = 1 (=> 16-byte copy) [V] |
| 0x674aa1e | 8 | [rbp+0x918] | `0x674aa1e  mov [rbp+0x918],rbx` | Draw binding namePtr = rbx (name pointer from sub_BCABA00 Q-table lookup entry+0x30) staged as binding a2+0x8 [V] |
| 0x674aa25 | 8 | [rbp+0xBA0] | `0x674aa25  mov rax,[rbp+0xBA0]` | Base of the 16-byte-entry uniform slot array (= writer stack struct [rbp+0xB70] + 0x30); also read at `0x674abc7  mov rax,[rbp+0xBA0]`; no write to [rbp+0xBA0] located before 0x674aa40 — array initializer not statically located [V read / ? write] |
| 0x674aa2c | 2 | [rbp+0xBAA] | `0x674aa2c  movzx r8d,word ptr [rbp+0xBAA]` | Entry count u16 of the array; also read at `0x674abce  movzx edx,word ptr [rbp+0xBAA]`; no write located before 0x674aa40 [V read / ? write] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | Search key = FNV-1a hash of "GlyphTexture" stored at 0x129FA178 [V] |
| 0x674aa50 | 8 | [rcx] | `0x674aa50  mov r10,[rcx]` | Array entry[0] = qword pointer to a uniform record; walk stride `0x674aa59  add rcx,0x10` [V] |
| 0x674aa53 | 8 | [r10+0x28] | `0x674aa53  cmp [r10+0x28],r8` | [uniform-record+0x28] name hash compared with GlyphTexture hash; match selects slot [V] |
| 0x674aa6f | 4 | ecx | `0x674aa6f  shr ecx,4` | Slot index = (matched entry − array base) / 16 [V] |
| 0x674aa72 | 2 | [rbp+0x5F0] | `0x674aa72  mov [rbp+0x5F0],cx` | u16 slot index stored; live capture docs/data/live/glyph_bind.txt: index 0x000A = 10 (GlyphTexture slot), flag 0x01 — 30/30 samples [V] [V live] |
| 0x674aa79 | 1 | [rbp+0x5F2] | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | u8 flag byte = 1 stored next to the index [V] [V live] |
| 0x674aa80 | 8 | rdx=&[rbp+0x5F0] | `0x674aa80  lea rdx,[rbp+0x5F0]` | {u16 index, u8 flag} passed as rdx to sub_5679DB0 [V] |
| 0x674aa87 | 8 | r8=&[rbp+0x910] | `0x674aa87  lea r8,[rbp+0x910]` | {qword count=1, qword namePtr} passed as r8 to sub_5679DB0; live capture R8 begins count=1 then namePtr [V] [V live] |
| 0x674aa8e | 8 | rcx=r15=[rbp+0xB70] | `0x674aa8e  mov rcx,r15` | Writer object (stack struct at [rbp+0xB70]; +0x28 slot table base, +0x20 limit, +0x30 entry-array base, +0x70 FNV-1a state) passed as this to sub_5679DB0 [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind via uniform/subcomponent writer [V] [V live] |
| 0x5679db0 | 8 | fn entry | `0x5679db0  push r15` | sub_5679DB0 = UniformBlock::setVec4Array entry, size 0x165 (0x5679db0..0x5679f15), 390 static call sites [V rdis fn] |
| 0x5679dbf | 2 | word ptr [rdx] | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679DB0: index u16 read from {index,flag} param (a1+0x0) [V rdis] |
| 0x5679dc3 | 8 | [rcx+0x30] | `0x5679dc3  mov r15,[rcx+0x30]` | sub_5679DB0: r15 = writer+0x30 = entry-array base [V rdis] |
| 0x5679dcb | 2 | [r15+r14+8] | `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` | sub_5679DB0: entry[index].+0x08 u16 = slot byte-offset into binding table [V rdis] |
| 0x5679dd1 | 8 | [rsi+0x20] | `0x5679dd1  cmp [rsi+0x20],rcx` | sub_5679DB0: bounds check slot-offset < writer+0x20 limit; fail -> `0x5679f0f  call 0x78ED0` / `0x5679f14  int3` [V rdis] |
| 0x5679ded | 8 | [rsi+0x28] | `0x5679ded  add rcx,[rsi+0x28]` | sub_5679DB0: dst = writer+0x28 + slot-offset (slot table base + offset) [V rdis] |
| 0x5679df1 | 8 | [rdi+8] | `0x5679df1  mov rdx,[rdi+8]` | sub_5679DB0: src = name pointer from draw binding a2+0x8 = [rbp+0x918] = rbx [V rdis] |
| 0x5679df5 | 8 | r8 | `0x5679df5  shl r8,4` | sub_5679DB0: size = count*16 = 16 [V rdis] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr, size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the binding slot [V rdis] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0x0C valid/bound flag set to 1 [V rdis] |
| 0x5679efe | 8 | [rsi+0x70] | `0x5679efe  mov [rsi+0x70],r8` | sub_5679DB0: writer+0x70 FNV-1a state mixed with index and with name hash from `0x5679e65  call 0x19932c0` [V rdis] |
| 0x674a9f2 | 8 | [rbp+0xEA0] | `0x674a9f2  mov r8,[rbp+0xEA0]` | Argument slot loaded for texture-object resolver sub_BCABA00 [V] |
| 0x674a9f9 | 8 | call | `0x674a9f9  call 0xBCABA00` | sub_BCABA00 texture-object resolver; result (rbx) staged as namePtr [V] |
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | Visitor case 3 (sub_6664a00), stride-0x38 UI record loop `0x6664cbb  add r9,0x38`: record field +0x28 = qword texture-NAME pointer [V descscan2 case 3] |
| 0x6664cf5 | 8 | [rsp+0x38] | `0x6664cf5  mov [rsp+0x38],r10` | Field +0x28 staged as extractor arg8 at call site `0x6664d46  call 0x674A3A0` [V] |
| 0x6664d46 | 8 | call | `0x6664d46  call 0x674A3A0` | Extractor call site 1: stride-0x38 records, arg8 = [r9+0x28] name pointer [V] |
| 0x6664eb1 | 8 | [r9] | `0x6664eb1  mov r13,[r9]` | Visitor stride-0x86 path: record field +0x0 read `0x6664eb8  add r9,0x86` [V] |
| 0x6664ef9 | 8 | [rsp+0x38] | `0x6664ef9  mov [rsp+0x38],r13` | Field +0x0 staged as extractor arg8 [V] |
| 0x6664f4a | 8 | call | `0x6664f4a  call 0x674A3A0` | Extractor call site 2: stride-0x86 records [V] |
| 0x6664760 | 8 | fn entry | `0x6664760  push rbp` | sub_6664760 UI record builder ("FrameBuilder - Insert UI"), size 0x218 (0x6664760..0x6664978), vtable[0] of .rdata dispatch table at 0xf2be218; 0 static callers [V rdis vt; xref callers=0] |
| 0x66647d7 | 16 | [rbx] | `0x66647d7  movups xmm0,[rbx]` | Record builder: 16 bytes (SSO name contents) from 2nd argument rbx [V] |
| 0x66647da | 16 | [rbp-0x40] | `0x674aa0c`-style | ... |
