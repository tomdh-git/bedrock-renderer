## NEXT
DONE

# UNIT U-EI5c: Text/font — SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending
# Pending part of checklist item I5c ONLY: glyph atlas texture creation/update + where the GlyphTexture uniform value/handle comes from.
# SDF glyph uniforms (GlyphTexture/GlyphHeight/GlyphSmoothRadius at 0x674dca3/0x674ddbe/0x674e06a) and FONT_TYPE permutation (0x674d2bf via 0xF2EA00) are CLOSED in U-I5c/U-EL14c — not redone here.

## Source notes (read-only baseline)
- PROGRESS 2026-11-21 oc_U-EI5c.md r2 (verify_oc 12/12 [V]): "GlyphTexture" uniform value bound at draw time (0x674dca3 in 0x674a3a0) is NOT a bgfx handle — provenance traced into the draw path of extractor 0x674a3a0 (full 3756-line listing via dumplist.py, Temp/opencode/u-ei5c_674a3a0.lst).
- ORCHESTRATOR HINT (treated as verified): 0xEEC7570 at 0x4f78966 is an import thunk called with rcx = C string ("textures/ui/Caution"/"textures/ui/ErrorGlyph") and rax tested as a length (test rax,rax/js) = strlen-style call, NOT a texture-handle fetch. Do not redo.
- oc_U-I5c.md (input, verified): font init 0xE82E00 → 0xE84070 ×5 (DefaultFont/RuneFont/UIFont/UnicodeFont/SmoothFontLatin, vtable 0xF09AA70); font reset 0x186e6a0 (ClearAndResetFontData, callers 0x8F6919, 0x104237E); NO "GlyphAtlas" string; NO "FontTexture" string (0xF0BCA58 holds data bytes 90 80 07 40 01); NO bgfx createTexture in font paths; font objects allocate only registry objects via [0xF99FFA0]; font vtable 0xF09AA70 slot 6 = sub_96bd10 (string-copy helper only, 0 xrefs).
- BGFX_MAP.md 6ai/6z/6aj (verified map): createTexture = RendererContext vtable slot 26 (0xe8143c0; RTX override slot 26 = 0xe83d400 stub), updateTexture slot 28 (0xe814a70), createDynamicTexture = 0xbc74a80; bgfx createTexture API variants 0xbc716a0/0xbc71990; bgfx::Context global ptr at 0x12ae1748; texture table at RendererContext+0xbde178 stride 0xB8 (4096 inline, guarded paged chain beyond); createUniform = 0xbc75440. Texture creation is vtable-indirect — no direct call sites.

## Method (NEW angle — do not redo proven facts)
Static analysis only (rdis.exe dis/fn/imm/str, xref.py str; BGFX_MAP.md sections 6ai, 6z, 6aj). No game launch, no debugger, no tools.rtools.*.
1. Traced the GlyphTexture VALUE at draw time inside extractor 0x674a3a0 (3756-line listing grepped exhaustively): 0x674a8ea call 0x675DD80 (named-resource cache lookup by global string 0x129FA4C8) → 0x674a9f9 call 0xBCABA00 (static per-class string table via vtable+0x440; entry: string +0x30, size +0x40, flag +0x80, stride 0x88) → 0x674aa09 movups xmm0,[rax] (16-byte SSO name into [rbp+0xC10]) → 0x674aa91 call 0x5679DB0 (binder writes value into the "GlyphTexture" binding record found by hash [0x129FA178]).
2. Tested the hint's "object field holds the texture handle" premise: full listing grepped — field [rbp+0xE80]+0x38 is NEVER read (no `r14+0x38` anywhere; [rbp+0xE80] fields read are +0x10/+0x18/+0x1D8...+0x244 only); [rbp+0xE80]/[rbp+0xEB8]/[rbp+0xBB0]/[rbp+0xBBA]/[rbp+0xEA0] are read but never written in the visible listing (dumplist skips undecodable bytes — possible gaps; writers not statically locatable). Premise wrong for this path: the uniform carries a NAME string, not a handle.
3. Exhaustive negative checks: rdis imm over .text = 0 hits for 0xbc716a0, 0xbc71990, 0xbc74a80, 0xe8143c0 → NO direct bgfx createTexture/createDynamicTexture/slot-26 call anywhere in the executable. rdis str "glyph"/"font"/"atlas" -i enumerates every glyph/font/atlas string — no glyph-atlas name exists. texload 0x58a1310 disassembled: texture-info/mip parser (iterates 0x30-byte {u32,f32,f32,f32} entries), only 2 xrefs — not the atlas creation path.

## Offset table (one row per distinct offset; all its sites listed)
| Offset | Size | Sites (RVA) | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------|------------------------------------|------------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) loaded into rdx for FNV-1a hash registration: hash via `0x674dcb4  call 0x79580`, stored `0x674dd81  mov [0x129FA178],rcx`, registered `0x674dd8f  call 0x73150` — uniform registration site only, no texture creation [V] |
| 0x674dcb4 | 8 | 0x674dcb4 | `0x674dcb4  call 0x79580` | FNV-1a 64 hash of the "GlyphTexture" name; result stored at [0x129FA178] [V] |
| 0x674dd81 | 8 | 0x674dd81 | `0x674dd81  mov [0x129FA178],rcx` | "GlyphTexture" FNV hash stored at TLS/global 0x129FA178; read at draw time by `0x674aa42  mov r8,[0x129FA178]` to locate the binding record [V] |
| 0x674dd8f | 8 | 0x674dd8f | `0x674dd8f  call 0x73150` | uniform hash-table registration creating the "GlyphTexture" binding record [V] |
| 0x674a8e3 | 8 | 0x674a8e3 | `0x674a8e3  lea rcx,[rbp+0xB68]` | output slot filled by `0x674a8ea  call 0x675DD80`; [rbp+0xB68] becomes the table object passed to 0xBCABA00 [V] |
| 0x674a8ea | 8 | 0x674a8ea | `0x674a8ea  call 0x675DD80` | named-resource cache lookup: FNV-1a hash of name string at global 0x129FA4C8 (`0x674a594  lea r8,[0x129FA4C8]`) into table at object+0x58 with mask +0x70 inside 0x67CFD80; 0x675DD80 body: `0x675ddff  mov rax,[rax+0x18]`, `0x675de03  mov rax,[rax]`, `0x675de06  mov [rdi],rax` — stores derived object ptr at [rbp+0xB68] [V] |
| 0xbcaba30 | 8 | 0xbcaba30 | `0xbcaba30  mov rax,[rcx]` | 0xBCABA00 (rcx = [rbp+0xB68]): reads [rcx] — table base is read from [[Q]+0x440] where Q = [rbp+0xB68] — exact class of Q not statically identifiable (vtable indirection) [I] |
| 0xbcaba36 | 8 | 0xbcaba36 | `0xbcaba36  mov r15,[rax+0x440]` | static per-class string table base inside 0xBCABA00 — table that supplies the GlyphTexture name string [V] |
| 0xbcaba46 | 1 | 0xbcaba46 | `0xbcaba46  movzx r12d,byte ptr [r15+rcx+80]` | table-entry flag byte at +0x80 (stride 0x88); if 0 → entry not found [V] |
| 0xbcaba71 | 8 | 0xbcaba71 | `0xbcaba71  cmp qword ptr [r15+0x48],0x10` | entry size at +0x40 compared to 0x10 → SSO vs heap string handling [V] |
| 0xbcaba78 | 8 | 0xbcaba78 | `0xbcaba78  mov rbx,[r15+0x30]` | entry string pointer at +0x30 (inline SSO buffer if size <= 0x10, else heap pointer) [V] |
| 0x674aa09 | 16 | 0x674aa09 | `0x674aa09  movups xmm0,[rax]` | 16-byte SSO texture-name string from 0xBCABA00 return copied into value buffer [rbp+0xC10] (`0x674aa0c  movaps [rbp+0xC10],xmm0`) — the GlyphTexture UNIFORM VALUE is a TEXTURE NAME STRING, NOT a bgfx handle [V] |
| 0x674aa42 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | "GlyphTexture" FNV hash loaded for binding-record lookup: stride-0x10 table scan `0x674aa50  mov r10,[rcx]`, `0x674aa53  cmp [r10+0x28],r8` until match [V] |
| 0x674aa91 | 8 | 0x674aa91 | `0x674aa91  call 0x5679DB0` | binder invoked: copies the SSO value into the binding record (memcpy 0xEEC6EC0), sets bound flag, stores FNV hash at record+0x70 [V] |
| 0x674a4d1 | 8 | 0x674a4d1 | `0x674a4d1  mov r14,[rbp+0xE80]` | object ptr loaded into r14; its fields are read at +0x10..+0x244 but NEVER at +0x38 (no `r14+0x38` in the full listing) — the hint's "object+0x38 texture-handle field" does not exist in this path [V] |
| 0x4f7894d | 8 | 0x4f7894d | `0x4f7894d  lea rdi,[0xF5AFF73]` | "textures/ui/ErrorGlyph" fallback glyph-texture name — one of only THREE glyph texture-name strings in the binary (also "textures/ui/WarningGlyph" 0xF5AFF8A at `0x4f788fc`/`0x50d887b`, "textures/ui/Caution" 0xF58553B at `0x4f78882`/`0x4f7889e`/`0x4f78946`); all consumed only inside fetch 0x4f78830 (plus sub_27f7550/sub_28eec00 for ErrorGlyph); 0x4f78830 has 0 static callers and its `0x4f78966  call 0xEEC7570` is strlen-style per orchestrator, NOT a handle fetch [V] |
| 0xbc716a0/0xbc71990/0xbc74a80/0xe8143c0 | - | - | - | NEGATIVE: `rdis imm` over .text = 0 hits for each — NO direct call to bgfx createTexture (0xbc716a0/0xbc71990), createDynamicTexture (0xbc74a80), or RendererContext slot-26 createTexture fn (0xe8143c0) anywhere in the executable; all texture creation is vtable-indirect (RendererContext slots 26/28, texture table RendererContext+0xbde178 stride 0xB8 per BGFX_MAP 6z/6aj [V tool, role I]) |
| 0xe84257 | 8 | 0xe84257 | `0xe84257  lea rax,[0xF0BCA58]` | alleged "FontTexture" address — holds data bytes (90 80 07 40 01), not a string; no "FontTexture" string exists [V input data] |
| 0x186f7bc | 8 | 0x186f7bc | `0x186f7bc  call qword ptr [0xF99FFA0]` | example font-reset allocation: TerrainAtlas registry object, size 4 (`mov edx,4` at 0x186f7b7); font init/reset create NO textures — registry objects only [V input data] |

## Answer
**What IS proven [V]:**
- The `GlyphTexture` uniform is REGISTERED at 0x674dca3 (hash via 0x79580, stored [0x129FA178], registered via 0x73150) — closed already in U-I5c.
- At DRAW time in extractor 0x674a3a0, the `GlyphTexture` VALUE is produced by: named-resource cache lookup `0x674a8ea call 0x675DD80` (by global string 0x129FA4C8) → `0x674a9f9 call 0xBCABA00` (static per-class string table at [[Q]+0x440], Q=[rbp+0xB68]; entry string +0x30, size +0x40, flag +0x80, stride 0x88; index u16 at [rbp+0x910] from prior lookup of string [rbp+0xBB0]/len [rbp+0xBBA] in global table 0x129FA550) → returns SSO string pointer in rax → `0x674aa09 movups xmm0,[rax]` copies the 16-byte SSO NAME into [rbp+0xC10] → `0x674aa42 mov r8,[0x129FA178]` locates the "GlyphTexture" binding record → `0x674aa91 call 0x5679DB0` binds the name string into it.
- So `GlyphTexture` = texture NAME string resolved to a bgfx handle LATER by the renderer (name→handle happens at bind/submit time, outside font code) — not a handle, not created here.
- Font paths create nothing: 0xE82E00→0xE84070 (vtable 0xF09AA70; its slot 6 = sub_96bd10 string-copy helper) and 0x186e6a0 allocate registry objects via [0xF99FFA0] only.
- The ONLY glyph-texture-name strings in the binary are the three fallbacks ErrorGlyph/WarningGlyph/Caution, all used only by fetch 0x4f78830 (0 static callers, unreachable statically).

**What is NOT found (blocking):**
- No glyph-atlas texture NAME string exists in .rdata (no "GlyphAtlas", no "FontTexture" — 0xF0BCA58 is data bytes; str "glyph"/"font"/"atlas" -i enumerates everything).
- NO direct bgfx createTexture/createDynamicTexture/slot-26 call exists anywhere in .text (imm searches = 0 hits) → the texture creation site is vtable-indirect and cannot be located statically.
- The exact SSO name string bound as GlyphTexture, and who writes the source of that name, are not statically resolvable (vtable indirection into a static data table + possible listing gaps).

**CLOSES?: NO** — single blocking fact: the glyph atlas texture creation/update site is not found and not isolatable statically (zero direct createTexture/createDynamicTexture calls in the binary; no glyph-atlas name string; font paths create no textures), and the GlyphTexture handle/writer is not traceable because the uniform carries a name string from a static per-class table via 0xBCABA00 whose string content and writer are not statically resolvable. Both pending parts need a LIVE trace: break on RendererContext vtable slot 26/28 (createTexture/updateTexture) or bgfx createTexture 0xbc716a0/0xbc71990 / createDynamicTexture 0xbc74a80 and trace which texture name becomes the GlyphTexture uniform value.

## TOOL REQUESTS
live texture-handle tracer | break on bgfx createTexture/createDynamicTexture (RendererContext slots 26/28; fns 0xbc716a0/0xbc71990/0xbc74a80) and trace which texture name becomes the GlyphTexture value | static analysis exhausted: all texture creation is vtable-indirect and no atlas name string exists; a live trace is the only remaining angle
none additional — unit is blocked on live trace, not on static analysis
