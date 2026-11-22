## NEXT
DONE

# UNIT U-EI5c: Text/font — glyph atlas texture creation/update + GlyphTexture handle trace (pending part of checklist item I5c)

## Goal (pending part only)

Checklist item I5c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending".
Closed earlier (U-I5c verify 97/97, U-EL14c verify 7/7): GlyphTexture/GlyphHeight/GlyphSmoothRadius uniform registration in extractor 0x674a3a0 (0x674dca3 / 0x674ddbe / 0x674e06a), FONT_TYPE+MSDF permutation via 0xF2EA00 (0x674d2bf / 0x674d6be), font init 0xE82E00→0xE84070 (vtable 0xF09AA70), font reset 0x186e6a0 (callers 0x8F6919, 0x104237e).
This unit covers ONLY what remains open per the orchestrator hint: follow where the GlyphTexture uniform value at draw time comes from, which object field holds the texture handle, and who writes that field; find the glyph atlas texture creation/update site.

## Method (NEW angle vs r1-r10)

Static analysis only (rdis.exe dis/fn/xr/callers; xref.py str/callers; BGFX_MAP.md sections 6ai, 6z, 6aj). No game launch, no debugger, no tools.rtools.*, no shell reads of the exe.
The new angle not exhausted by r1-r10: fully decode the draw-time value production path `0x674a8ea call 0x675DD80` → `0x674a9f9 call 0xBCABA00` → `0x674aa09 movups xmm0,[rax]` → `0x674aa91 call 0x5679DB0`, and decode `sub_675DD80` + `sub_BCABA00` to identify the object field holding the name and whether any writer is statically reachable.

## Offset table (one row per distinct offset; all its sites listed)

| Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[?]) |
|--------|------|--------------------|------------------------------------|------------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) loaded into rdx, hashed via `0x674dcb4  call 0x79580`, hash stored `0x674dd81  mov [0x129FA178],rcx`, registered `0x674dd8f  call 0x73150` — uniform registration at init, NOT a texture creation site [V] (U-I5c, verify 97/97) |
| 0x674a594 | 8 | 0x674a594 | `0x674a594  lea r8,[0x129FA4C8]` | Global name string (data RVA 0x129FA4C8) loaded for the named-resource cache lookup that yields Q=[rbp+0xB68]; referenced twice in sub_674a3a0 (also `0x674d899  lea rcx,[0x129FA4C8]`) [V] |
| 0x674a8ea | 8 | 0x674a8ea | `0x674a8ea  call 0x675DD80` | Named-resource cache accessor: rcx=&Q output, rdx=[rbp+0x2E0], r8=[rsi]; derives Q=[[[rbp+0x2E0]+8]+0x18]+0 and Q+0x170 hash table, stores Q at [rbp+0xB68] [V] |
| 0x675dda2 | 8 | 0x675dda2 | `0x675dda2  mov rax,[rdx+8]` | sub_675DD80: reads a1+0x8 (= [rbp+0x2E0+8]); refcount-inc path `0x675ddab  lock inc dword ptr [rax+8]` [V] |
| 0x675ddff | 8 | 0x675ddff | `0x675ddff  mov rax,[rax+0x18]` | sub_675DD80: pointer chase [rax+0x18] [V] |
| 0x675de03 | 8 | 0x675de03 | `0x675de03  mov rax,[rax]` | sub_675DD80: [[...+0x18]+0] stored at Q=[rdi]=[rbp+0xB68] via `0x675de06  mov [rdi],rax` [V] |
| 0x675de10 | 8 | 0x675de10 | `0x675de10  mov rdx,[rax+0x170]` | sub_675DD80: Q+0x170 = per-object hash table passed to `0x675de17  call 0xE86B370` (name→entry lookup), result stored `0x675de1d  mov [rdi+0x80],rsi` [V] |
| 0x674a9f9 | 8 | 0x674a9f9 | `0x674a9f9  call 0xBCABA00` | Texture-name lookup: rcx=Q=[rbp+0xB68], rdx=&[rbp+0x910] (u16 texture-unit index); walks Q's vtable+0x440 table and matches by FNV hash of entry name [V] |
| 0xbcaba30 | 8 | 0xbcaba30 | `0xbcaba30  mov rax,[rcx]` | sub_BCABA00: [rcx]=[Q+0] = vtable pointer [V] |
| 0xbcaba36 | 8 | 0xbcaba36 | `0xbcaba36  mov r15,[rax+0x440]` | sub_BCABA00: r15 = [vtable+0x440] = STATIC per-class texture-name table base (not populated at runtime) [V] |
| 0xbcaba33 | 2 | 0xbcaba33 | `0xbcaba33  movzx esi,word ptr [rdx]` | sub_BCABA00: u16 texture-unit index from {index} param [V] |
| 0xbcaba46 | 1 | 0xbcaba46 | `0xbcaba46  movzx r12d,byte ptr [r15+rcx+0x80]` | sub_BCABA00: entry+0x80 valid flag byte (stride 0x88 via `0xbcaba3f  shl ecx,7` + `0xbcaba42  lea rcx,[rcx+rsi*8]` = index*0x88) [V] |
| 0xbcaba78 | 8 | 0xbcaba78 | `0xbcaba78  mov rbx,[r15+0x30]` | sub_BCABA00: entry+0x30 name pointer (SSO buffer `0xbcabac2  lea rbx,[r15+0x30]` when size<=0x10 at `0xbcaba71  cmp qword ptr [r15+0x48],0x10`, else heap pointer) [V] |
| 0xbcabbe0 | 8 | 0xbcabbe0 | `0xbcabbe0  cmp r13,[rsi+0x20]` | sub_BCABA00: global name→texture-object bucket hash-chain: node+0x20 hash vs FNV hash of entry name, chain via [rsi+8] [V] |
| 0xbcabc0a | 8 | 0xbcabc0a | `0xbcabc0a  call 0xEEC6EB0` | sub_BCABA00: name string compare to confirm bucket match [V] |
| 0xbcabca6 | 4 | 0xbcabca6 | `0xbcabca6  lock inc dword ptr [r8+8]` | sub_BCABA00: refcount bump on the located texture object [V] |
| 0x674aa09 | 16 | 0x674aa09 | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture-NAME string from sub_BCABA00 return copied into value buffer [rbp+0xC10] (`0x674aa0c  movaps [rbp+0xC10],xmm0`) — the GlyphTexture UNIFORM VALUE is a TEXTURE NAME STRING, NOT a bgfx handle [V] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | "GlyphTexture" FNV hash loaded for binding-record lookup: stride-0x10 array scan `0x674aa50  mov r10,[rcx]`, `0x674aa53  cmp [r10+0x28],r8` until match [V] |
| 0x674aa91 | 8 | 0x674aa91 | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind: binder writes the 16-byte name into the slot selected by the hash lookup (index at [rbp+0x5F0], flag [rbp+0x5F2]); live capture confirms index 0x000A=10, flag 0x01 (30/30 samples) [V] [V live] |
| 0x5679dbf | 2 | 0x5679dbf | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679DB0: index u16 read from {index,flag} param (rdx) [V] |
| 0x5679dc3 | 8 | 0x5679dc3 | `0x5679dc3  mov r15,[rcx+0x30]` | sub_5679DB0: writer+0x30 = base of the 16-byte entry array [V] |
| 0x5679dcb | 2 | 0x5679dcb | `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` | sub_5679DB0: entry[index].+0x08 u16 = slot byte-offset into the binding table [V] |
| 0x5679dd1 | 4 | 0x5679dd1 | `0x5679dd1  cmp [rsi+0x20],rcx` | sub_5679DB0: bounds check slot-offset < writer+0x20 limit, else error path `0x5679f0f  call 0x78ED0` (followed by `0x5679f14  int3`) [V] |
| 0x5679ded | 8 | 0x5679ded | `0x5679ded  add rcx,[rsi+0x28]` | sub_5679DB0: dst = writer+0x28 slot-table base + entry offset [V] |
| 0x5679df1 | 8 | 0x5679df1 | `0x5679df1  mov rdx,[rdi+8]` | sub_5679DB0: src = name pointer from draw binding (+0x8) [V] |
| 0x5679df9 | 8 | 0x5679df9 | `0x5679df9  call 0xEEC6EC0` | sub_5679DB0: memcpy(dst=slotTable+offset, src=namePtr, size=16) — WRITES a 16-byte TEXTURE NAME into the binding slot [V] |
| 0x5679dfe | 1 | 0x5679dfe | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679DB0: entry[index].+0x0C valid/bound flag set to 1 [V] |
| 0x5679efe | 8 | 0x5679efe | `0x5679efe  mov [rsi+0x70],r8` | sub_5679DB0: writer+0x70 FNV-1a state mixed with index (`0x5679e04..0x5679e53`) and with name hash from `0x19932C0` (`0x5679e57..0x5679efe`) [V] |
| 0x4f78966 | 8 | 0x4f78966 | `0x4f78966  call 0xEEC7570` | Legacy glyph-name fetch: CFG-thunk call (name in rdi, rax tested as length js->error) — per orchestrator hint this is strlen-style, NOT a texture-handle fetch; 0x4f78830 has 0 static callers [V] |
| 0xeec7570 | 8 | 0xeec7570 | `0xeec7570  jmp qword ptr [0xF9A9048]` | CFG thunk: jumps through data slot 0xF9A9048, target not statically resolvable [V] |
| 0xe840fd | 8 | 0xe840fd | `0xe840fd  mov [rsi],rax` | Font object ctor 0xE84070 installs vtable 0xF09AA70 at font object +0x00; vtable slots (0x1505b0 release, 0x76900, 0xb8bb0, 0x76920) create no texture [V] (U-I5c input data) |
| 0x186f7bc | 8 | 0x186f7bc | `0x186f7bc  call qword ptr [0xF99FFA0]` | Font-reset registry-object allocation example (TerrainAtlas, size 4, `mov edx,4`); font init/reset create NO textures — registry objects only [V] (U-I5c input data) |
| 0xbc716a0/0xbc71990/0xbc74a80/0xe8143c0 | - | - | - | NEGATIVE: `rdis imm` over .text = 0 hits for each — NO direct call to bgfx createTexture (0xbc716a0/0xbc71990), createDynamicTexture (0xbc74a80), or RendererContext slot-26 createTexture fn (0xe8143c0) anywhere in the executable; all texture creation is vtable-indirect (texture table RendererContext+0xbde178 stride 0xB8 per BGFX_MAP 6z/6aj) [V tool, role I] |

## What I tried that failed (new angles)

- Fully decoded `sub_675DD80` (0x675dd80..0x675de6d, 0xed, 10 xrefs) and `sub_BCABA00` (0xbcaba00..0xbcac23f, 0x83f, 51 xrefs): Q=[rbp+0xB68] is derived by pointer chase `[[rbp+0x2E0]+8]+0x18]+0`; Q+0x170 is a per-object hash table; Q's texture-name table is `[Q+0]=vtable → [vtable+0x440]` = STATIC per-class data (entry stride 0x88, entry+0x30 name SSO-or-heap, entry+0x80 valid flag). The class of Q is NOT statically identifiable (vtable indirection), so the table's content/writer cannot be pinned to a font object. [V]
- `rdis str "glyph"/"font"/"atlas" -i` enumerates every glyph/font/atlas string — NO glyph-atlas name string exists in .rdata; the only glyph-texture-name strings are the three fallbacks "textures/ui/Caution" (0xF58553B), "textures/ui/ErrorGlyph" (0xF5AFF73), "textures/ui/WarningGlyph" (0xF5AFF8A), consumed only by fetch 0x4f78830 (0 static callers, unreachable) [V]
- `rdis imm` over .text = 0 hits for 0xbc716a0, 0xbc71990, 0xbc74a80, 0xe8143c0 — NO direct bgfx createTexture/createDynamicTexture/slot-26 call anywhere in the executable [V tool]
- texload 0x58a1310 (pack texture loader, BGFX_MAP L8/6z): `rdis callers 0x58a1310` = sub_6b84680 and sub_6ea2df0 only, neither font-related [V]
- The object field writer (rdis fld / descscan2 on the field offset) cannot target a known struct because Q's class is unknown (vtable indirection) — this was the hint's "who writes that field" angle and it is statically dead-ended [I]
- livemem on CFG thunk data slot 0xF9A9048 was considered but the orchestrator hint classifies 0x4f78966→0xEEC7570 as strlen-style, NOT a handle fetch, so resolving the thunk would not yield a texture-handle creation site [I per hint]

## Answer

**What IS proven [V]:**
- The `GlyphTexture` uniform is REGISTERED at 0x674dca3 (hash via 0x79580, stored at [0x129FA178], registered via 0x73150) — closed in U-I5c.
- At DRAW time in extractor 0x674a3a0, the `GlyphTexture` VALUE is produced by: named-resource lookup `0x674a8ea call 0x675DD80` → Q=[rbp+0xB68]; then `0x674a9f9 call 0xBCABA00` which reads Q's static per-class texture-name table at `[Q+0]=vtable → [vtable+0x440]` (stride 0x88; entry+0x30 name, entry+0x80 valid flag), hashes the name (FNV-1a), does a global name→texture-object bucket lookup (`[rax+0x400]` buckets, `[rax+0x418]` mask, compare `[rsi+0x20]` hash, `0xEEC6EB0` string compare), bumps the texture refcount (`0xbcabca6  lock inc dword ptr [r8+8]`), and returns the name pointer in rbx → `0x674aa09 movups xmm0,[rax]` copies the 16-byte SSO NAME into [rbp+0xC10] → `0x674aa42 mov r8,[0x129FA178]` locates the "GlyphTexture" binding record → `0x674aa91 call 0x5679DB0` binds the name into it.
- So `GlyphTexture` = a 16-byte texture NAME string resolved to a bgfx handle LATER by the renderer (name→handle at draw-command execution, outside font code) — NOT a handle, NOT created here.
- Font paths create nothing: 0xE82E00→0xE84070 (vtable 0xF09AA70) and 0x186e6a0 allocate registry objects via [0xF99FFA0] only; no texture creation.

**What is NOT found (the single blocking fact):**
- No glyph-atlas texture NAME string exists in .rdata (no "GlyphAtlas", no "FontTexture" — 0xF0BCA58 holds data bytes 90 80 07 40 01).
- NO direct bgfx createTexture/createDynamicTexture/slot-26 call exists anywhere in .text (imm searches = 0 hits); the texture creation site is vtable-indirect and cannot be tied to a glyph atlas statically.
- texload 0x58a1310 has no font caller; fetch 0x4f78830 is unreachable and strlen-style.
- So the glyph atlas texture creation/update site and its bgfx handle allocation are not statically locatable.

## CLOSES?

NO — blocking fact: the glyph atlas texture creation/update site is not found and not isolatable statically (zero direct createTexture/createDynamicTexture calls in the binary; no glyph-atlas name string; font paths create no textures; texload has no font caller), and the GlyphTexture handle/writer is not traceable because the uniform carries a name string from Q's static per-class vtable+0x440 table via 0xBCABA00 whose class/content/writer are not statically resolvable (vtable indirection). Both pending parts of I5c remain unproven by [V] rows. Closing needs a LIVE trace: break on RendererContext vtable slot 26/28 (createTexture/updateTexture, fns 0xbc716a0/0xbc71990/0xbc74a80 per BGFX_MAP 6z/6aj) or on the texture table at RendererContext+0xbde178, and trace which texture name becomes the GlyphTexture value.

## TOOL REQUESTS

- live texture-handle tracer | break on bgfx createTexture/createDynamicTexture (RendererContext slots 26/28; fns 0xbc716a0/0xbc71990/0xbc74a80) and trace which texture name becomes the GlyphTexture value | static analysis exhausted: all texture creation is vtable-indirect and no atlas name string exists; a live trace is the only remaining angle
- cfg-thunk-target resolver | data slot 0xF9A9048 (PE data read) → real target of thunk 0xEEC7570 | rdis exposes no PE-data read; shell reads of the exe are prohibited; needs a helper or a live trace
