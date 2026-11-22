## NEXT
DONE

# UNIT U-EI5c: Text/font SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas — pending part of checklist item I5c

## Goal (pending part only, do NOT redo proven facts)

Closed already (U-I5c verify 97/97, U-EL14c verify 7/7): SDF glyph uniforms GlyphTexture/GlyphHeight/GlyphSmoothRadius registered in extractor 0x674a3a0 (0x674dca3/0x674ddbe/0x674e06a via FNV 0x79580 -> 0x73150), FONT_TYPE+MSDF permutation via 0xF2EA00 (0x674d2bf/0x674d6be), font init 0xE82E00->0xE84070 x5 (vtable 0xF09AA70), font reset 0x186e6a0 (ClearAndResetFontData, callers 0x8F6919, 0x104237e).

This unit covers ONLY what remained open per the orchestrator hint: at draw time, follow where the GlyphTexture uniform VALUE comes from (set near 0x674dca3 in 0x674a3a0), which field holds it, who writes that field, and where the glyph atlas texture is created/updated. New angle per the 2026-11-21 orchestrator LIVE CAPTURE (docs/data/live/glyph_bind.txt, 30 samples at bp 0x674aa91, cite [V live]): the earlier "object+0x38 SSO texture-name" claim (r2) is UNPROVEN/REFUTED — the bound value is a draw-data struct selected by u16 index into a 16-byte-entry array (lookup loop 0x674aa50 compares [entry+0x28] with hash from data_129fa178); every sample has RDX={u16 index=0x000A, u8 flag=0x01} (one sample 0x3E), R8=&{qword count=1, qword namePtr}. This note decodes sub_5679DB0 and the array lookup, traces the value back to sub_6664a00's UI item records, and re-attacks the atlas creation site.

Static analysis only (rdis.exe dis/fn; xref.py str; no game launch, no debugger, no tools.rtools.*, no shell reads of the exe). livemem considered but not actionable: the name-buffer addresses from the capture are from a past run (ASLR/restart), so there is no current target address to read; noted as a live-trace request below.

## Offset table (one row per distinct offset; all its sites listed; verbatim lines re-verified against the exe)

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[?]) |
|---|---|---|---|---|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) hashed via `0x674dcb4  call 0x79580`, hash stored `0x674dd81  mov [0x129FA178],rcx`, registered `0x674dd8f  call 0x73150` — uniform registration at init (proven in U-I5c), NOT a texture-creation site [V] |
| 0x674a4ca | 8 | [rbp+0xEB8] | `0x674a4ca  mov r15,[rbp+0xEB8]` | Draw-time GlyphTexture value source: arg8 = caller-provided pointer loaded into r15; sub_6664a00 passes UI item record field [r9+0x28] at call site 0x6664d46 (`0x6664cb0  mov r10,[r9+0x28]` / `0x6664cf5  mov [rsp+0x38],r10`) and [r9] at call site 0x6664f4a (`0x6664eb1  mov r13,[r9]` / `0x6664ef9  mov [rsp+0x38],r13`) [V] |
| 0x674a9ff | 8 | rax=r15=[rbp+0xEB8] | `0x674a9ff  mov rax,r15` | rax = caller pointer; feed for the 16-byte load at 0x674aa09 [V] |
| 0x674aa09 | 16 | [rax] = *[[rbp+0xEB8]] | `0x674aa09  movups xmm0,[rax]` | 16-byte texture NAME loaded from the caller-provided pointer — the GlyphTexture uniform value is a NAME string, not a bgfx handle [V] |
| 0x674aa0c | 16 | [rbp+0xC10] | `0x674aa0c  movaps [rbp+0xC10],xmm0` | 16-byte name staged as the uniform value buffer [V] |
| 0x674aa13 | 8 | [rbp+0x910] | `0x674aa13  mov qword ptr [rbp+0x910],1` | Draw binding count = 1 (=> 16-byte copy) [V] |
| 0x674aa1e | 8 | [rbp+0x918] | `0x674aa1e  mov [rbp+0x918],rbx` | Draw binding namePtr = rbx (name pointer from 0xBCABA00's Q-table lookup, entry+0x30, see row 0xbcaba78) [V] |
| 0x674aa25 | 8 | [rbp+0xBA0] | `0x674aa25  mov rax,[rbp+0xBA0]` | Base of the 16-byte-entry uniform slot array (= writer stack struct [rbp+0xB70] + 0x30); ALSO read at `0x674abc7  mov rax,[rbp+0xBA0]` (GlyphSmoothRadius path). Exhaustive store scan of sub_674a3a0 0x674a3a0..0x674abef shows NO write to [rbp+0xBA0] before 0x674aa40 — the array initializer is NOT located statically [V read / ? write] |
| 0x674aa2c | 2 | [rbp+0xBAA] | `0x674aa2c  movzx r8d,word ptr [rbp+0xBAA]` | Entry count (u16) of the array; ALSO read at `0x674abce  movzx edx,word ptr [rbp+0xBAA]`; NO write to [rbp+0xBAA] located before 0x674aa40 [V read / ? write] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | Search key = FNV-1a hash of "GlyphTexture" (stored at registration by `0x674dd81  mov [0x129FA178],rcx`) [V] |
| 0x674aa50 | 8 | [rcx] | `0x674aa50  mov r10,[rcx]` | Array entry[0] = qword pointer to a uniform record; walk stride `0x674aa59  add rcx,0x10` [V] |
| 0x674aa53 | 8 | [r10+0x28] | `0x674aa53  cmp [r10+0x28],r8` | [uniform-record+0x28] = name hash compared with the GlyphTexture hash; match selects the slot [V] |
| 0x674aa6f | 4 | ecx | `0x674aa6f  shr ecx,4` | Slot index = (matched entry − array base) / 16 [V] |
| 0x674aa72 | 2 | [rbp+0x5F0] | `0x674aa72  mov [rbp+0x5F0],cx` | u16 slot index stored; [V live] live capture docs/data/live/glyph_bind.txt: RDX = 0x000A0001 (index 0x000A = 10 = GlyphTexture slot, flag 0x01) in 30/30 samples (one sample flag byte 0x3E) |
| 0x674aa79 | 1 | [rbp+0x5F2] | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | u8 flag byte = 1 stored next to the index [V] [V live] |
| 0x674aa80 | 8 | rdx=&[rbp+0x5F0] | `0x674aa80  lea rdx,[rbp+0x5F0]` | {u16 index, u8 flag} argument passed as rdx to sub_5679DB0 [V] |
| 0x674aa87 | 8 | r8=&[rbp+0x910] | `0x674aa87  lea r8,[rbp+0x910]` | {qword count=1, qword namePtr} argument passed as r8 to sub_5679DB0; [V live] live capture R8 struct val begins `0100000000000000` (count=1) followed by namePtr |
| 0x674aa8e | 8 | rcx=r15=[rbp+0xB70] | `0x674aa8e  mov rcx,r15` | Writer object (stack struct at [rbp+0xB70]; +0x28 slot table base, +0x20 limit, +0x30 entry-array base = [rbp+0xBA0], +0x70 FNV-1a hash state) passed as this to sub_5679DB0 [V] |
| 0x674aa91 | 8 | call | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind: writer writes the 16-byte name into the slot selected by the hash lookup [V] [V live] |
| 0x5679dbf | 2 | [rdx] | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679DB0 (size 0x165, 390 xrefs): index u16 read from {index,flag} param (a1+0x0) [V] |
| 0x5679dc3 | 8 | [rcx+0x30] | `0x5679dc3  mov r15,[rcx+0x30]` | sub_5679DB0: r15 = writer+0x30 = entry-array base [V] |
| 0x5679dcb | 2 | [r15+r14+8] | `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` | sub_5679DB0: entry[index].+0x08 u16 = slot byte-offset into the binding table [V] |
| 0x5679dd1 | 8 | [rsi+0x20] | `0x5679dd1  cmp [rsi+0x20],rcx` | sub_5679DB0: bounds check slot-offset < writer+0x20 limit; fail -> error path `0x5679f0f  call 0x78ED0` / `0x5679f14  int3` [V] |
| 0x5679ded | 8 | [rsi+0x28] | `0x5679ded  add rcx,[rsi+0x28]` | sub_5679DB0: dst = writer+0x28 + slot-offset (slot table base + offset) [V] |
| 0x5679df1 | 8 | [rdi+8] | `0x5679df1  mov rdx,[rdi+8]` | sub_5679DB0: src = name pointer from draw binding a2+0x8 = [rbp+0x918] = rbx [V] |
| 0x5679df5 | 8 | r8 | `0x5679df5  shl r8,4` | sub_5679DB0: size = count*16 = 16 [V] |
| 0x5679df9 | 16 | - | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slot, src=namePtr, size=16) — WRITES a 16-byte TEXTURE NAME into the binding slot, NOT a bgfx handle [V] |
| 0x5679dfe | 1 | [r15+r14+0xC] | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0x0C valid/bound flag set to 1 [V] |
| 0x5679efe | 8 | [rsi+0x70] | `0x5679efe  mov [rsi+0x70],r8` | sub_5679DB0: writer+0x70 FNV-1a state mixed with index (`0x5679e04..0x5679e53`) and with name hash from `0x5679e65  call 0x19932C0` (`0x5679e57..0x5679efe`) [V] |
| 0x675dd80 | 8 | call | `0x674a8ea  call 0x675DD80` | Named-resource cache accessor producing Q=[rbp+0xB68]; pointer chase `0x675ddff  mov rax,[rax+0x18]` / `0x675de03  mov rax,[rax]` / `0x675de06  mov [rdi],rax`; Q+0x170 hashed name table [V] |
| 0xbcaba30 | 8 | [rcx] | `0xbcaba30  mov rax,[rcx]` | sub_BCABA00: [Q+0] = Q's vtable pointer [V] |
| 0xbcaba36 | 8 | [rax+0x440] | `0xbcaba36  mov r15,[rax+0x440]` | sub_BCABA00: r15 = [vtable+0x440] = STATIC per-class texture-name table base (Q's class not statically identifiable — vtable indirection) [V] |
| 0xbcaba46 | 1 | [r15+rcx+0x80] | `0xbcaba46  movzx r12d,byte ptr [r15+rcx+0x80]` | sub_BCABA00: entry+0x80 valid flag byte; entry stride 0x88 (`0xbcaba3f  shl ecx,7` / `0xbcaba42  lea rcx,[rcx+rsi*8]` = index*0x88) [V] |
| 0xbcaba71 | 8 | [r15+0x48] | `0xbcaba71  cmp qword ptr [r15+0x48],0x10` | sub_BCABA00: entry+0x48 size compared to 0x10 -> SSO vs heap name handling [V] |
| 0xbcaba78 | 8 | [r15+0x30] | `0xbcaba78  mov rbx,[r15+0x30]` / `0xbcabac2  lea rbx,[r15+0x30]` | sub_BCABA00: entry+0x30 = texture NAME (heap pointer when size>0x10, else SSO buffer); result in rbx -> draw-binding namePtr at row 0x674aa1e [V] |
| 0xbcabbe0 | 8 | [rsi+0x20] | `0xbcabbe0  cmp r13,[rsi+0x20]` | sub_BCABA00: global name->texture-object bucket — node+0x20 hash vs FNV hash of entry name, chain via [rsi+8] [V] |
| 0xbcabc0a | 8 | call | `0xbcabc0a  call 0xEEC6EB0` | sub_BCABA00: name strcmp to confirm bucket match [V] |
| 0xbcabca6 | 4 | [r8+8] | `0xbcabca6  lock inc dword ptr [r8+8]` | sub_BCABA00: refcount bump on the located texture object [V] |
| 0x6664cb0 | 8 | [r9+0x28] | `0x6664cb0  mov r10,[r9+0x28]` | sub_6664a00 UI item record (stride 0x38 loop, `0x6664cbb  add r9,0x38`): record field +0x28 = name pointer, staged as arg8 via `0x6664cf5  mov [rsp+0x38],r10` at call site 0x6664d46 [V] |
| 0x6664eb1 | 8 | [r9] | `0x6664eb1  mov r13,[r9]` | sub_6664a00 UI item record (stride 0x86 loop, `0x6664eb8  add r9,0x86`): record field +0x00 = name pointer, staged as arg8 via `0x6664ef9  mov [rsp+0x38],r13` at call site 0x6664f4a [V] |
| 0xe84257 | 8 | 0xe84257 | `0xe84257  lea rax,[0xF0BCA58]` | Alleged "FontTexture" address: holds data bytes (90 80 07 40 01 per U-I5c input), no "FontTexture" string exists; no glyph-atlas name string exists in .rdata (no "GlyphAtlas"; only UI section labels glyph_section_*, glyph-dict, and the 19/22-byte fallbacks ErrorGlyph/WarningGlyph/Caution) [V input data] |

## What I tried that failed (new angles, not redone)

- Refuted r2's "object+0x38 SSO name" claim: the full sub_674a3a0 listing contains no read of [rbp+0xE80]+0x38 (no `r14+0x38` anywhere; object fields read are +0x10/+0x18/+0x1D8...+0x244). The draw-time value is loaded from caller-provided arg8 [rbp+0xEB8] via `0x674aa09  movups xmm0,[rax]` (rax = r15 = [rbp+0xEB8]) — 16 bytes, a texture NAME, not a handle.
- Store scan for the array initializer: no write to [rbp+0xBA0] or [rbp+0xBAA] exists anywhere in sub_674a3a0 0x674a3a0..0x674abef (all memory stores enumerated; only [rbp+0x8xx]/[rbp+0x9xx]/[rbp+0xBxx=BF0]/[rbp+0xCxx]/[rsp+xx] stores appear). The array base/count writer is not located statically.
- rdis field/struct angles on the object field: [rbp+0xE80] object type unknown (caller-provided object pointer, arg5); vtable load `0x674b73c` only stores the vtable pointer, never captures its value — no known struct to run rw/fld/descscan2 against. sub_6664a00 reads [r9+0x28]/[r9] but never writes them (the pointer is set earlier in the chain); sub_6664760 (the UI record builder, sole caller of sub_6664a00) has 0 static xrefs — reached only indirectly, not reversed.
- Texture-name strings: xref str "glyph"/"font"/"atlas" -i enumerates everything — NO glyph-atlas name string in .rdata; the only glyph-texture-name strings are fallbacks "textures/ui/ErrorGlyph" (0xF5AFF73), "textures/ui/WarningGlyph" (0xF5AFF8A), "textures/ui/Caution" (0xF58553B), all 19+ bytes (>16-byte SSO) and consumed only by fetch 0x4f78830, which has 0 static callers and whose `0x4f78966  call 0xEEC7570` is strlen-style per the orchestrator hint, NOT a handle fetch. Resolving CFG-thunk data slot 0xF9A9048 (pepeek) would not yield a creation site for the same reason.
- bgfx creation: `rdis imm` over .text = 0 hits for 0xbc716a0, 0xbc71990 (createTexture variants), 0xbc74a80 (createDynamicTexture), 0xe8143c0 (RendererContext slot 26) — no direct createTexture/createDynamicTexture call ANYWHERE in the executable; font init 0xE82E00->0xE84070 (vtable 0xF09AA70; its 4 slots release/string helpers only) and font reset 0x186e6a0 create no textures (registry objects via [0xF99FFA0] only, per U-I5c). Texture creation is vtable-indirect (RendererContext slots 26/28; texture table at this+0xbde178, stride 0xB8, per BGFX_MAP.md 6z/6aj) and consumed at render-thread submit — not statically tieable to a glyph atlas.
- texload 0x58a1310 (pack/named loader, BGFX_MAP.md L8/6z): `rdis callers` = sub_6b84680 and sub_6ea2df0 only, neither font-related.

## Answer

**Decode of sub_5679DB0 (writer binder) — proven [V]:**
sub_5679DB0(rcx=writer [rbp+0xB70], rdx=&{u16 index, u8 flag} [rbp+0x5F0], r8=&{u16 count=1, qword namePtr} [rbp+0x910]):
- `0x5679dbf  movzx r14d,word ptr [rdx]` index u16; `0x5679dc3  mov r15,[rcx+0x30]` entry-array base (writer+0x30); `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` entry[index].+0x08 u16 slot byte-offset; `0x5679dd1  cmp [rsi+0x20],rcx` bounds-check vs writer+0x20 limit (fail -> `0x5679f0f  call 0x78ED0` / `0x5679f14  int3`); `0x5679ded  add rcx,[rsi+0x28]` dst = writer+0x28+offset; `0x5679df1  mov rdx,[rdi+8]` src = namePtr; `0x5679df5  shl r8,4` size = count*16 = 16; `0x5679df9  call 0xEEC6EC0` memcpy 16 bytes; `0x5679dfe  mov byte ptr [r15+r14+0xC],1` entry[index].+0x0C flag = 1; `0x5679efe  mov [rsi+0x70],r8` mixes index + name hash (0x19932c0) into writer+0x70 FNV-1a state. **The slot therefore receives a 16-byte TEXTURE NAME, not a bgfx handle.**

**Array lookup at draw time — proven [V] (+ [V live]):**
At 0x674aa25-0x674aa91 the extractor walks the 16-byte-entry array at [rbp+0xBA0] (writer+0x30; entries = {qword uniform-record-ptr @+0, u16 slot-offset @+0x8, u8 flag @+0xC}); `0x674aa50  mov r10,[rcx]`, `0x674aa53  cmp [r10+0x28],r8` matches [record+0x28] name hash against the GlyphTexture hash from `0x674aa42  mov r8,[0x129FA178]`; match -> `0x674aa72  mov [rbp+0x5F0],cx` slot index, `0x674aa79  mov byte ptr [rbp+0x5F2],1` flag; then `0x674aa91  call 0x5679DB0`. Live capture: index 0x000A = 10 (GlyphTexture slot), flag 0x01 — 30/30 samples — and R8 = {count=1, namePtr}, exactly matching sub_5679DB0's args. [V] [V live]

**Value provenance — proven [V]:**
The 16 bytes bound as GlyphTexture are loaded from caller-provided arg8: `0x674a4ca  mov r15,[rbp+0xEB8]`, `0x674a9ff  mov rax,r15`, `0x674aa09  movups xmm0,[rax]` (16 bytes from *[[rbp+0xEB8]]), staged `0x674aa0c  movaps [rbp+0xC10],xmm0`. sub_6664a00 (sole caller of sub_674a3a0, 2 sites) passes UI item record fields as that argument: stride-0x38 records field +0x28 (`0x6664cb0  mov r10,[r9+0x28]` / `0x6664cf5  mov [rsp+0x38],r10`) at call 0x6664d46; stride-0x86 records field +0x00 (`0x6664eb1  mov r13,[r9]` / `0x6664ef9  mov [rsp+0x38],r13`) at call 0x6664f4a. Independently, on the matched path `0xBCABA00` resolves a texture object through Q's static per-class texture-name table ([vtable+0x440], stride 0x88, entry+0x30 name / +0x48 size / +0x80 valid flag; global bucket hash-chain `0xbcabbe0  cmp r13,[rsi+0x20]`, strcmp `0xbcabc0a  call 0xEEC6EB0`, refcount bump `0xbcabca6  lock inc dword ptr [r8+8]`) and its entry+0x30 name pointer becomes rbx -> [rbp+0x918] namePtr. Q's class is not statically identifiable (vtable indirection), so the table's content/writer is not pinned to a font object.

**So: GlyphTexture is bound BY NAME (16-byte texture name from the UI item record field), not as a bgfx handle, and not created by font code.**

**Glyph atlas texture creation/update site — NOT FOUND (blocking):**
No direct bgfx createTexture/createDynamicTexture/slot-26 call exists anywhere in .text (imm scan 0 hits); no glyph-atlas name string exists in .rdata (no "GlyphAtlas"; no "FontTexture" — 0xF0BCA58 holds data bytes); font init/reset create no textures; all texture creation is vtable-indirect via RendererContext slots 26/28 (texture table this+0xbde178, stride 0xB8) and happens at render-thread submit. texload 0x58a1310 has no font caller. Fetch 0x4f78830 is unreachable and strlen-style.

## CLOSES?

NO — single blocking fact: the glyph atlas texture creation/update site is not statically locatable (zero direct bgfx createTexture/createDynamicTexture calls in the binary; no glyph-atlas name string; font paths create no textures; texture creation is vtable-indirect render-thread work), AND the writer of the 16-byte glyph texture-name field (sub_6664a00's UI item record field [r9+0x28]/[r9], passed as arg8 to sub_674a3a0) is not located — sub_6664760 (record builder) has 0 static xrefs and no store to [rbp+0xBA0]/[rbp+0xBAA] (the uniform slot array base/count) exists in sub_674a3a0 before 0x674aa40. Everything else in the item IS proven by [V] rows: SDF glyph uniforms + FONT_TYPE permutation (U-I5c/U-EL14c), and the GlyphTexture draw-time bind (16-byte NAME via sub_5679DB0 memcpy into the hash-selected slot; index 0x000A slot 10 confirmed [V live]). Closing needs a LIVE trace: break on bgfx createTexture/updateTexture (RendererContext slots 26/28, fns 0xbc716a0/0xbc71990/0xbc74a80 per BGFX_MAP.md 6z/6aj) or on the texture table at RendererContext+0xbde178, and trace which texture name becomes the GlyphTexture uniform value.

## TOOL REQUESTS

- live_atlas_tracer | break on bgfx createTexture/createDynamicTexture (RendererContext slots 26/28, fns 0xbc716a0/0xbc71990/0xbc74a80; texture table this+0xbde178 stride 0xB8 per BGFX_MAP.md 6z/6aj) and trace which texture name becomes the GlyphTexture uniform value | static analysis exhausted: no direct createTexture call anywhere in .text, no atlas name string, vtable-indirect render-thread creation
- sub_6664760 record-writer tracer | identify the UI item record builder that writes the 16-byte name field ([r9+0x28] stride-0x38 / [r9] stride-0x86) passed as arg8 to sub_674a3a0 | sub_6664760 has 0 static xrefs; not reversed

## NEXT
DONE
