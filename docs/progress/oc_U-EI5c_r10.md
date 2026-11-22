## NEXT
DONE

# UNIT U-EI5c: Text/font — glyph atlas texture creation/update + GlyphTexture handle trace (pending part of checklist item I5c)

## Goal (pending part only)

Checklist item I5c: "Text/font: SDF glyph uniforms + FONT_TYPE permutation (6ce); glyph atlas pending".
Closed earlier (U-I5c verify 97/97, U-EL14c verify 7/7): GlyphTexture/GlyphHeight/GlyphSmoothRadius uniform registration (0x674dca3/0x674e06a/0x674ddbe), FONT_TYPE+MSDF permutation via 0xF2EA00 (0x674d2bf), font init 0xE82E00→0xE84070 (vtable 0xF09AA70), font reset 0x186e6a0 (callers 0x8F6919, 0x104237E).
This unit covers ONLY what was still open: where the glyph atlas texture is created/updated, and where the `GlyphTexture` uniform's bgfx texture handle comes from.

## Method

Static analysis only (rdis.exe dis/callers/xr/imm, xref.py str/callers, ripscan.py; BGFX_MAP.md sections L8, 6z, 6ai). No game launch, no debugger, no tools.rtools.*.
New angle per orchestrator hint: at draw time the GlyphTexture value is chosen by u16 index (live capture docs/data/live/glyph_bind.txt: RDX=0x000A index, flag 0x01, 30 samples) into a 16-byte-entry array and written by sub_5679db0; the earlier "SSO name at obj+0x38" claim is UNPROVEN (contradicted by the live capture) and is not restated as fact.

## Offset table (one row per distinct offset, all its sites listed)

| Offset | Size | Sites (RVA) | Verbatim `0xRVA  instr` proof line | Meaning ([V]/[I]/[-]) |
|--------|------|-------------|------------------------------------|------------------------|
| 0x674dca3 | 8 | 0x674dca3 | `0x674dca3  lea rdx,[0xF5C6DD7]` | "GlyphTexture" uniform-name string (0xF5C6DD7) loaded, hashed via call 0x79580 at 0x674dcb4 (FNV-1a loop 0x674dd17..0x674dd51), hash stored at 0x129FA178 and registered via call 0x73150 at 0x674dd8f — uniform registration at init, not a texture creation site [V] (U-I5c, verify 97/97) |
| 0x129FA178 | 8 | 0x674aa42 | `0x674aa42  mov r8,[0x129FA178]` | Global holding the FNV-1a hash of "GlyphTexture" (stored at its registration in sub_674a3a0); used as the search key in the draw-time binding-array lookup below [V] |
| 0x674a9f9 | 8 | 0x674a9f9 | `0x674a9f9  call 0xBCABA00` | Texture-table name lookup: rcx=object [rbp+0xB68], rdx=&[rbp+0x910] (u16 texture-unit index at [rdx]), r9=[rbp+0xC10], r8=[rbp+0xEA0]; walks the object+0x440 table (0x88B entries) and matches by FNV hash of the entry name [V] |
| 0xbcaba30 | 8 | 0xbcaba30 | `0xbcaba30  mov rax,[rcx]` | 0xBCABA00: object+0x00 -> table pointer base [V] |
| 0xbcaba33 | 2 | 0xbcaba33 | `0xbcaba33  movzx esi,word ptr [rdx]` | 0xBCABA00: u16 texture-unit index read from [rbp+0x910] [V] |
| 0xbcaba36 | 8 | 0xbcaba36 | `0xbcaba36  mov r15,[rax+0x440]` | 0xBCABA00: texture table pointer at object+0x440 [V] |
| 0xbcaba42 | 8 | 0xbcaba42 | `0xbcaba42  lea rcx,[rcx+rsi*8]` | 0xBCABA00: entry address = table + index*0x88 (0x88-byte stride, set up by `shl ecx,7` at 0xbcaba3f) [V] |
| 0xbcaba46 | 1 | 0xbcaba46 | `0xbcaba46  movzx r12d,byte ptr [r15+rcx+0x80]` | 0xBCABA00: entry+0x80 valid flag byte [V] |
| 0xbcaba78 / 0xbcabac2 | 8 | 0xbcaba78, 0xbcabac2 | `0xbcaba78  mov rbx,[r15+0x30]` / `0xbcabac2  lea rbx,[r15+0x30]` | 0xBCABA00: entry+0x30 name — heap pointer ([r15+0x48]>=0x10) or SSO buffer (lea) [V] |
| 0xbcabbe0 | 8 | 0xbcabbe0 | `0xbcabbe0  cmp r13,[rsi+0x20]` | 0xBCABA00: hash-table node match — node+0x20 hash vs FNV hash of the name (chain via [rsi+8]) [V] |
| 0xbcabca6 | 4 | 0xbcabca6 | `0xbcabca6  lock inc dword ptr [r8+8]` | 0xBCABA00: refcount bump on the located texture object [V] |
| 0x674aa02 | 8 | 0x674aa02 | `0x674aa02  lea r15,[rbp+0xB70]` | The "component writer" object is a stack struct at [rbp+0xB70] (rcx=this for call 0x5679DB0) [V] |
| 0x674aa25 | 8 | 0x674aa25 | `0x674aa25  mov rax,[rbp+0xBA0]` | rax = base of the 16-byte-entry uniform binding array (= writer+0x30) [V] |
| 0x674aa2c | 2 | 0x674aa2c | `0x674aa2c  movzx r8d,word ptr [rbp+0xBAA]` | u16 entry count of the array ([rbp+0xBAA]; end bound = count*16 at 0x674aa37) [V] |
| 0x674aa13 | 8 | 0x674aa13 | `0x674aa13  mov qword ptr [rbp+0x910],1` | Draw binding {count=1, ptr} stored at [rbp+0x910]; count=1 => 16-byte copy [V] |
| 0x674aa1e | 8 | 0x674aa1e | `0x674aa1e  mov [rbp+0x918],rbx` | Draw binding ptr = rbx, the texture NAME string (rbx preserved/callee-saved across 0xBCABA00; set earlier in sub_674a3a0) [V] |
| 0x674aa50 | 8 | 0x674aa50 | `0x674aa50  mov r10,[rcx]` | Array entry[0] = qword pointer to a uniform record; stride 0x10 (`add rcx,0x10` at 0x674aa59) [V] |
| 0x674aa53 | 8 | 0x674aa53 | `0x674aa53  cmp [r10+0x28],r8` | [uniform-record+0x28] = uniform name hash, compared with the "GlyphTexture" hash from 0x129FA178; match -> slot found [V] |
| 0x674aa6f | 4 | 0x674aa6f | `0x674aa6f  shr ecx,4` | Slot index = (matched entry − array base) / 16 [V] |
| 0x674aa72 | 2 | 0x674aa72 | `0x674aa72  mov [rbp+0x5F0],cx` | u16 index stored (live capture: index 0x000A=10 is the GlyphTexture slot, 30/30 samples) [V live] |
| 0x674aa79 | 1 | 0x674aa79 | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | flag byte = 1 stored next to the index [V] |
| 0x674aa80 | 8 | 0x674aa80 | `0x674aa80  lea rdx,[rbp+0x5F0]` | rdx = &{u16 index, u8 flag} argument for 0x5679DB0 [V] |
| 0x674aa87 | 8 | 0x674aa87 | `0x674aa87  lea r8,[rbp+0x910]` | r8 = &draw binding {qword count=1, qword name ptr} argument for 0x5679DB0 [V] |
| 0x674aa8e | 8 | 0x674aa8e | `0x674aa8e  mov rcx,r15` | rcx = writer object [rbp+0xB70] (this) for 0x5679DB0 [V] |
| 0x674aa91 | 8 | 0x674aa91 | `0x674aa91  call 0x5679DB0` | Draw-time GlyphTexture bind: writer writes the 16-byte texture binding into the slot selected by the hash lookup [V] |
| 0x5679dbf | 2 | 0x5679dbf | `0x5679dbf  movzx r14d,word ptr [rdx]` | sub_5679db0: index u16 read from {index,flag} param (rdx) [V] |
| 0x5679dc3 | 8 | 0x5679dc3 | `0x5679dc3  mov r15,[rcx+0x30]` | sub_5679db0: writer+0x30 = base of the 16-byte entry array [V] |
| 0x5679dcb | 2 | 0x5679dcb | `0x5679dcb  movzx ecx,word ptr [r15+r14+8]` | sub_5679db0: entry[index].+0x08 u16 = slot byte-offset into the binding table [V] |
| 0x5679dd1 | 4 | 0x5679dd1 | `0x5679dd1  cmp [rsi+0x20],rcx` | sub_5679db0: bounds check slot-offset < writer+0x20 limit, else error path `call 0x78ED0 / int3` at 0x5679f0f [V] |
| 0x5679ded | 8 | 0x5679ded | `0x5679ded  add rcx,[rsi+0x28]` | sub_5679db0: dst = writer+0x28 slot-table base + entry offset [V] |
| 0x5679df1 | 8 | 0x5679df1 | `0x5679df1  mov rdx,[rdi+8]` | sub_5679db0: src = name pointer from draw binding (+0x8) [V] |
| 0x5679df9 | 8 | 0x5679df9 | `0x5679df9  call 0xEEC6EC0` | sub_5679db0: memcpy(dst=slotTable+offset, src=namePtr, size=count*16=16) — WRITES a 16-byte TEXTURE NAME into the binding slot [V] |
| 0x5679dfe | 1 | 0x5679dfe | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | sub_5679db0: entry[index].+0x0C valid flag set to 1 [V] |
| 0x5679efe | 8 | 0x5679efe | `0x5679efe  mov [rsi+0x70],r8` | sub_5679db0: writer+0x70 FNV-1a hash state mixed with the index (0x5679e04..0x5679e53) and with the name hash from sub_19932c0(count,namePtr) (0x5679e57..0x5679efe) [V] |
| 0x4f78966 | 8 | 0x4f78966 | `0x4f78966  call 0xEEC7570` | Legacy glyph-name fetch: CFG-thunk call (name in rdi, rax tested as length js->error) — per orchestrator hint this is strlen-style, NOT a texture-handle fetch; 0x4f78830 has 0 static callers [V] |
| 0xeec7570 | 8 | 0xeec7570 | `0xeec7570  jmp qword ptr [0xF9A9048]` | CFG thunk: jumps through data slot 0xF9A9048, target not statically resolvable [V] (r8) |
| 0xF09AA70 | 8 | 0xe840fd | `0xe840fd  mov [rsi],rax` | Font object ctor 0xE84070 installs vtable 0xF09AA70 at font object +0x00 (U-I5c, verified); class has 4 vtable slots: 0x1505b0 (refcount release/destroy), 0x76900, 0xb8bb0, 0x76920 — none creates a texture [V] |
| 0x1505be | 4 | 0x1505be | `0x1505be  lock dec dword ptr [rsi+8]` | vtable slot 0 (0x1505b0): refcount release only, no texture creation [V] |
| 0x58a1310 | - | - | (no call sites in font code) | texload pack-texture loader; `rdis callers 0x58a1310` = sub_6b84680 and sub_6ea2df0 only, neither font-related [V] |

## Answer

**What the GlyphTexture uniform value is at draw time (proven [V]):**
At 0x674aa40-0x674aa91 in sub_674a3a0 the extractor walks a 16-byte-entry array at [rbp+0xBA0] (= writer stack struct [rbp+0xB70]+0x30). Each entry is {qword ptr to uniform record, u16 slot byte-offset at +0x08, u8 valid flag at +0x0C}; the uniform record's +0x28 holds its name hash. The search key is the "GlyphTexture" hash from 0x129FA178; on match, index=(entry-base)/16 and flag=1 are stored at [rbp+0x5F0]/[rbp+0x5F2] and sub_5679db0 is called with (rcx=writer [rbp+0xB70], rdx=&{index,flag}, r8=&[rbp+0x910]={count=1, namePtr}). Live capture confirms index=0x000A (10), flag=0x01 (30/30 samples) [V live].

**sub_5679db0 decoded [V] (size 0x165, 390 xrefs):** bounds-checks entry[index].+0x08 u16 offset against writer+0x20 limit (error path 0x5679f0f: call 0x78ED0 + int3), then `memcpy(dst=writer+0x28+offset, src=namePtr, 16)` via 0xEEC6EC0, sets entry[index].+0x0C flag=1, and mixes index + name hash (sub_19932c0) into the FNV-1a state at writer+0x70. The binding slot therefore holds a **16-byte texture NAME**, not a bgfx handle.

**Where the name comes from [V]:** immediately before, 0xBCABA00 looks up a texture by name/index in the object's texture table (object+0x440, 0x88B entries; entry+0x30 = SSO buffer or heap name pointer; entry+0x80 valid flag; match by FNV hash of name through a bucket chain [rax+0x400]/mask [rax+0x418], node hash at [rsi+0x20]); it then bumps the texture object refcount (`lock inc dword ptr [r8+8]` at 0xbcabca6). The name pointer (rbx) becomes the draw binding written into the GlyphTexture slot. The exact earlier definition of rbx/[rbp+0x910] inside the 0x2000-byte extractor was not traced further.

**Glyph atlas texture creation/update site:** NOT FOUND statically.
- Font init 0xE82E00→0xE84070 (vtable 0xF09AA70, installed at 0xe840fd) allocates font objects only; vtable slots (0x1505b0 release, 0x76900, 0xb8bb0, 0x76920) create no texture. Font reset 0x186e6a0 creates only small registry objects (no createTexture/updateTexture/createDynamicTexture).
- No "GlyphAtlas", "FontTexture", "font/*.png", or "glyph_*" texture name string exists in .rdata (xref str "glyph": only UI section labels glyph_section_* and glyph-dict/glyph-to-script-map; xref str "atlas": terrain/compass/flame/forcefield/item atlases only). The only glyph-name references are the fallbacks "textures/ui/Caution" (0xF58553B), "textures/ui/ErrorGlyph" (0xF5AFF73), "textures/ui/WarningGlyph" (0xF5AFF8A) used by fetch 0x4f78830, which has 0 static callers and ends at CFG thunk 0xEEC7570 (`jmp qword ptr [0xF9A9048]`, target unresolvable) — and per the orchestrator hint that call is strlen-style, not a handle fetch.
- texload 0x58a1310 (pack texture loader, BGFX_MAP.md L8/6z) has exactly 2 callers (sub_6b84680, sub_6ea2df0), neither font-related.
- So the glyph atlas is an ordinary named texture resolved by name at draw-command execution time (texture/pack system), not created by font code; its creation/update site and bgfx handle allocation are beyond static reach (CFG thunk / render-thread command consumer).

## CLOSES?

NO — blocking fact: the glyph atlas texture creation/update site and its bgfx handle allocation are not statically locatable: the draw path binds GlyphTexture by 16-byte NAME (proven via 0x674aa40-0x674aa91 + sub_5679db0 + 0xBCABA00, all [V]); the name is resolved to a bgfx handle downstream at draw-command execution, no glyph/font atlas name string exists in .rdata, texload 0x58a1310 has no font caller, and the legacy fetch 0x4f78830 (0 static callers) terminates in the unresolvable CFG thunk 0xEEC7570 -> `jmp qword ptr [0xF9A9048]`. Closing needs a live trace (break on bgfx createTexture slot 26 0xe8143c0 / createDynamicTexture 0xbc74a80 or the texture table at renderer+0xbde178 per BGFX_MAP.md 6z) or a cfg-thunk-target resolution for data slot 0xF9A9048.

## TOOL REQUESTS

cfg-thunk-target resolver | data slot 0xF9A9048 (PE data read) -> real target of thunk 0xEEC7570 (legacy glyph-name fetch) | rdis exposes no PE-data read; shell reads of the exe are prohibited; needs a helper or a live trace
named-texture-to-handle resolver | texture name -> bgfx handle at draw-command execute time | would close the atlas handle trace; render-thread command consumer not statically reachable
