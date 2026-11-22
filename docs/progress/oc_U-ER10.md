## NEXT
DONE

# oc_U-ER10 — R10 UIMesh (UI tag 2): Gameface / HudIcon / UIImGui "untouched" part (RETRY #1)

## Scope (from the item line)
UIMesh (tag 2) is DONE [V] (true size 0xA8 >= 0x90, +0x18 inline mRefs[4] shared_ptr array, +0x88 DescVariantRef storage with tag byte +0xA0) — proven in docs/progress/oc_U-ER10_r2.md, NOT redone here.
Pending: Gameface (UI tag 0) and UIImGui (UI tag 4): per-field reads with verbatim `0xRVA  instr` proof, true size, sub-objects. HudIcon (UI tag 1): reported DONE elsewhere [V], cited below, NOT re-examined.

## Input data (read fully, not regenerated)
- docs/data/live/gameface_extractor.txt — live-cap header for extractor 0x66ade80 (no samples yet; capture requested below)
- docs/functions/66ade80.md — Gameface extractor dossier (mechanical facts [V] from disassembly)
- docs/data/listings/ui_visitor_6664a00_6668510.txt — UI visitor 0x6664A00: tag-0 case 0x6664a6c (tail-jumps to 0x66ade80), tag-4 case 0x6664aab
- docs/BGFX_MAP.md — UI group 0x368 tags (line 502/2051), RenderUIGamefaceDescription fat clone 0x1f44d80 (line 312), Gameface extractor field reads (line 1827), tag enum UI 4 = UIImGui (line 2051)
- docs/progress/oc_U-ER10_r2.md — HudIcon DONE citation ([V] size 0x50, producer 0xe9aed0, case 0x6664d51)
- src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h — RenderUIHudIconDescription static_asserts (lines 962-972)

## Method / new angle (retry)
Earlier attempts (r1/r2) that FAILED: Gameface size via its producer 0xaed5d30 (descscan2/xref/callers/ripscan — 0x1000+ byte function, heavy stack reuse, no constructor or adjacent-local bound); UIImGui producer via `slotscan ui -q` (empty for tag 4). Those were about sizing through producers; not re-done.
This unit's angle: decode the two visitor cases themselves + the Gameface extractor. Jump-table decode [V jt.py]: tag 0 -> 0x6664a6c (Gameface -> extractor 0x66ade80), tag 1 -> 0x6664d51 (HudIcon), tag 2 -> 0x6664bd6 (UIMesh), tag 3 -> 0x6664c83 (UIText), tag 4 -> 0x6664aab (UIImGui); tag 2 enters 0x6664bd6 only, so R10's tag-2 flow is disjoint from tags 0/1/4 [V listing]. Casewalk CFG from head 0x6664aab [V]: reachable=2054, block 0x6666c4e `mov rsi,[rbp+0x520]` (desc reload) reachable — so the tag-4 path's desc reads below are on the tag-4 flow.
Sizes come from the instruction (movups/movaps 16B, qword mov 8B, dword/movss 4B, word 2B, byte 1B). One annotated row per distinct offset; all sites merged; no offset duplicated; no skipped-offset shorthand. Tag: [V] = seen in disassembly (RVA cited), [I] = inferred, [?] = unknown. All `0xRVA  instr` quotes copied verbatim from rdis output/listing and pass tools/sigs/verify_oc.py.

## PROGRESS

### HudIcon (UI tag 1) — untouched by R10, DONE elsewhere [V]
HudIcon is not decoded here; it is closed by another unit: docs/progress/oc_U-ER10_r2.md records [V] size 0x50, producer 0xe9aed0, case 0x6664d51. Corroborated [V file] by src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h lines 962-972: `struct RenderUIHudIconDescription` with `static_assert(offsetof(..., mMatrix08) == 0x08)`, `static_assert(offsetof(..., mValue48) == 0x48)`, `static_assert(sizeof(RenderUIHudIconDescription) == 0x50)`.

### Gameface (UI tag 0) — field map [V]
Visitor case 0 (head 0x6664a6c) reads NO description field: it forwards r9 (= desc) as r8 and tail-jumps to the dedicated extractor 0x66ade80 (`0x6664a6c  mov rcx,r13`, `0x6664aa6  jmp 0x66ADE80`). All desc reads below are in extractor 0x66ade80 via rsi = desc (`0x66adec4  mov rsi,r8`) and via spill slot [rbp+0x520] (`0x66ae256  mov [rbp+0x520],rsi`, reloaded `0x66aea9c  mov r14,[rbp+0x520]`). Highest description read is +0x80 qword (list pointer) → size >= 0x88 [I]; no description constructor exists in Minecraft code (fat clone 0x1f44d80, BGFX_MAP line 312; not in the thin-clone set, BGFX_MAP line 810) → upper bound unbounded statically → capture requested (see TOOL REQUESTS). Unread gaps inside [0,0x88) (+0x01-0x03, +0x06-0x07, +0x09-0x0B, +0x10-0x27, +0x29-0x2F, +0x31-0x37, +0x39-0x3F, +0x41-0x47, +0x49-0x4F, +0x51-0x57, +0x59-0x67, +0x69-0x7F) are not description fields [I].

| Name | Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof | Meaning | Tag |
|------|--------|------|--------------------|-------------------------------|---------|-----|
| visitor case tag 0 | case 0x6664a6c | - | case head | `0x6664a6c  mov rcx,r13`<br>`0x6664aa6  jmp 0x66ADE80` | desc (r9) forwarded as r8 to extractor 0x66ade80; no [r9+off] read in the case | [V] |
| +0x00 kind | +0x00 | 4B | extractor 0x66ade80 kind load + range check | `0x66ae25d  mov eax,[rsi]`<br>`0x66ae25f  cmp rax,8`<br>`0x66ae263  ja 0x66AE77A` | u32 kind (0..8) selects material via jump table 0xF2BF8A8 | [V] |
| +0x04 blend pair b4 | +0x04 | 1B | material-state decode | `0x66aeac0  movzx edx,byte ptr [r14+4]` | [desc+4] xor 6, or'd with [desc+5] chain -> blend enum [rbp+0x530] | [V] |
| +0x05 blend pair b5 | +0x05 | 1B | material-state decode | `0x66aeac5  movzx eax,byte ptr [r14+5]` | [desc+5] xor 8, second blend-pair input | [V] |
| +0x08 state byte | +0x08 | 1B | material-state decode | `0x66aebd4  movzx eax,byte ptr [r14+8]` | [desc+8] & 0xF -> rbp+0x51A | [V] |
| +0x0C state byte | +0x0C | 1B | material-state decode | `0x66aebd9  movzx ecx,byte ptr [r14+0xC]` | stored to rbp+0x51B | [V] |
| +0x0D state byte | +0x0D | 1B | material-state decode | `0x66aecb7  movzx eax,byte ptr [r14+0xD]` | stored to rbp+0x51F | [V] |
| +0x0E state byte | +0x0E | 1B | material-state decode | `0x66aebf8  movzx ecx,byte ptr [r14+0xE]` | indexes byte table 0x104070502080603 -> rbp+0x314 | [V] |
| +0x0F sub-desc addr | +0x0F | - | address taken only | `0x66aec6b  lea rdx,[r14+0xF]`<br>`0x66aec6f  lea rcx,[rbp+0x320]`<br>`0x66aec76  call 0x66983B0` | &desc+0x0F normalised by 0x66983B0 (sub-descriptor 2); width shown only by callee | [V] |
| +0x13 sub-desc addr | +0x13 | - | address taken only | `0x66aec1f  lea rdx,[r14+0x13]`<br>`0x66aec23  lea rcx,[rbp+0x320]`<br>`0x66aec2a  call 0x66983B0` | &desc+0x13 normalised by 0x66983B0 (sub-descriptor 1); width shown only by callee | [V] |
| +0x17 flag byte | +0x17 | 1B | material-state decode | `0x66aebec  cmp byte ptr [r14+0x17],1` | [desc+0x17]==1 -> sete rbp+0x51C | [V] |
| +0x28 variantA ptr | +0x28 | 8B | variantA copy path | `0x66adf1b  lea r8,[rsi+0x28]`<br>`0x66adf67  mov rcx,[r8]` | variantA shared_ptr pointer loaded via lea'd address [rsi+0x28] | [V] |
| variantA ctrl+0x10 word | ctrlA+0x10 | 2B | variantA copy path | `0x66adf6f  movzx ecx,word ptr [rcx+0x10]` | word read from shared_ptr ctrl block (rcx = [desc+0x28]) | [V] |
| +0x30 variantA ctrl | +0x30 | 8B | variantA copy path | `0x66adf73  mov rcx,[rsi+0x30]`<br>`0x66adf7c  lock inc dword ptr [rcx+8]` | variantA shared_ptr control pointer; strong ref taken (`lock inc [rcx+8]`) | [V] |
| variantA ctrl+0x8 refcount | ctrlA+0x8 | 4B | variantA copy path | `0x66adf7c  lock inc dword ptr [rcx+8]` | refcount increment on variantA ctrl block | [V] |
| +0x38 variantA tag | +0x38 | 1B | variantA tag test | `0x66adf1f  movzx ecx,byte ptr [rsi+0x38]` | variantA tag byte: 0=empty, 1={ptr,ctrl}, 2=resolve via 0x55F0270 | [V] |
| +0x40 variantB ptr | +0x40 | 8B | variantB copy path | `0x66ae0a7  lea r8,[rsi+0x40]`<br>`0x66ae0f0  mov rax,[r8]` | variantB shared_ptr pointer loaded via lea'd address [rsi+0x40] | [V] |
| +0x48 variantB ctrl | +0x48 | 8B | variantB copy path | `0x66ae0fc  mov rax,[rsi+0x48]` | variantB shared_ptr control pointer | [V] |
| +0x50 variantB tag | +0x50 | 1B | variantB tag test | `0x66ae0ab  movzx eax,byte ptr [rsi+0x50]` | variantB tag byte (same 3 alternatives as variantA) | [V] |
| +0x58 float4 | +0x58 | 16B | extractor hot path | `0x66ae227  movups xmm0,[rsi+0x58]` | float4 -> rbp+0x2F0 | [V] |
| +0x68 float4 | +0x68 | 16B | extractor hot path | `0x66ae232  movups xmm0,[rsi+0x68]` | float4 -> rbp+0x300 | [V] |
| +0x80 record list ptr | +0x80 | 8B | element loop | `0x66aea9c  mov r14,[rbp+0x520]`<br>`0x66aecc2  mov rax,[r14+0x80]`<br>`0x66aecc9  mov r15,[rax]`<br>`0x66aeccc  mov rax,[rax+8]` | desc+0x80 = pointer to {begin,end} record list; end=[ptr+8], records stride 0x1A0 (loop add r15,0x1A0 at 0x66AECE0) | [V] |
| rec+0x18C byte | rec+0x18C | 1B | per-record field | `0x66aed2a  movzx edi,byte ptr [r15+0x18C]` | record byte field (r15 = record cursor, stride 0x1A0) | [V] |
| rec+0x190 float4 | rec+0x190 | 16B | per-record field | `0x66aed32  movups xmm9,[r15+0x190]` | record float4 | [V] |
| rec+0x184 dword | rec+0x184 | 4B | per-record field | `0x66aed3a  mov eax,[r15+0x184]` | record dword | [V] |
| rec+0x188 dword | rec+0x188 | 4B | per-record field | `0x66aed41  mov ecx,[r15+0x188]` | record dword | [V] |
| rec+0x00 qword | rec+0x00 | 8B | per-record field | `0x66aed48  mov rdx,[r15]` | record qword; [rdx+4] read next | [V] |
| rec+4 dword (via rec) | rec+0x00+4 | 4B | per-record field | `0x66aed4b  mov r8d,[rdx+4]` | dword at [rec+0x00]+4 | [V] |
| rec+0x48 qword | rec+0x48 | 8B | per-record field | `0x66aed57  mov rdx,[r15+0x48]` | record qword (shared_ptr-style ptr); refcounted at [rdx+8] | [V] |

## Size proof — Gameface [I]
Highest description read is the +0x80 qword list pointer (`0x66aecc2  mov rax,[r14+0x80]`, r14=desc via `0x66aea9c  mov r14,[rbp+0x520]`; `0x66ae256  mov [rbp+0x520],rsi` stored desc at 0x66ae256). Read extent ends at 0x88 → Gameface description size **>= 0x88 [I]** (corroborates order of BGFX_MAP line 1827's 0x78 [I], extended by the verified +0x80 read). No description constructor exists (fat clone 0x1f44d80, BGFX_MAP line 312) and no static assert/ctor bounds the tail → **true size upper bound is unbounded statically**. The record list at desc+0x80 and the variantA/B shared_ptr ctrl blocks are sub-objects (separate heap objects), not description bytes.

## UIImGui (UI tag 4) — field map [V]
Visitor case 4 (head 0x6664aab) reads NO description field in the case body itself: it stores the desc pointer to frame slot [rbp+0x520] (`0x6664aab  mov [rbp+0x520],r9`), then clobbers r9 := [r14+0x40] and builds the "Debug/ImGui" material key (`0x6664ae9  lea rax,[0xF5AD096]`, `0x6664af7  mov qword ptr [rbp+0x408],0xB`, `0x6664b28  call 0x675E440`) plus shared_ptr bookkeeping — all frame/string ops, zero [r9+off] desc reads (lines 0x6664aac..0x6664bd5 checked). Desc field reads happen in the shared tail reached from the case (`0x6664bd1  jmp 0x6664F6F`; CFG from head 0x6664aab reaches 0x6666c4e `mov rsi,[rbp+0x520]` [V casewalk]):
- desc+0x00 qword -> object pointer (source object); `0x6664f78  mov rax,[rbp+0x520]` / `0x6664f7f  mov r9,[rax]`
- desc+0x08 qword; `0x6664f82  mov r15,[rax+8]`; its high dword divided by word [obj+0x80]
- obj = *(desc+0x00) sub-object fields: `0x6664f86  movzx r8d,word ptr [r9+0x80]` (word at obj+0x80, divisor) [V sequential]; `0x66651a4  mov rax,[rbp+0x520]` / `0x66651ab  mov r8,[rax]` / `0x66651ae  movss xmm0,[r8+0x28]` (float at obj+0x28) — instruction block exists [V listing] but casewalk from tag-4 head stops at seen-gateway 0x666503C before reaching it, so tag-4-path reachability is [?]
- desc+0x28 dword record count, desc+0x30 qword records base, end = base + count*0x28: `0x6666c4e  mov rsi,[rbp+0x520]` / `0x6666c74  mov rax,[rsi+0x28]` / `0x6666c78  mov r15,[rsi+0x30]` / `0x6666c7c  lea rax,[rax+rax*4]` / `0x6666c80  lea rax,[r15+rax*8]`; records stride 0x28 (`0x6666cb0  add r15,0x28`)
- desc+0x38: address only, `0x6666c55  lea r9,[rsi+0x38]` passed to formatter `0x6666c6e  call 0x56D55E0`; field width not shown by lea ([UNVERIFIED: 0x6666c55 width of desc+0x38 field])

| Name | Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof | Meaning | Tag |
|------|--------|------|--------------------|-------------------------------|---------|-----|
| visitor case tag 4 | case 0x6664aab | - | case head | `0x6664aab  mov [rbp+0x520],r9` | desc pointer saved to frame slot; NO [r9+off] desc field read in case body | [V] |
| desc+0x00 obj ptr | +0x00 | 8B | shared tail (reached via 0x6664F6F) | `0x6664f78  mov rax,[rbp+0x520]`<br>`0x6664f7f  mov r9,[rax]` | desc+0x00 = pointer to source object (obj) | [V] |
| desc+0x08 | +0x08 | 8B | shared tail | `0x6664f82  mov r15,[rax+8]` | desc+0x08 qword; high dword used as dividend | [V] |
| obj+0x80 word (sub-object) | obj+0x80 | 2B | shared tail | `0x6664f86  movzx r8d,word ptr [r9+0x80]` | word at *(desc+0x00)+0x80; divisor for (desc+0x08) index | [V] |
| obj+0x28 float (sub-object) | obj+0x28 | 4B | shared tail; casewalk from tag-4 head walks 0x6664f78/0x6664f86/0x6666c4e but stops at seen-gateway 0x666503C before reaching this block | `0x66651a4  mov rax,[rbp+0x520]`<br>`0x66651ab  mov r8,[rax]`<br>`0x66651ae  movss xmm0,[r8+0x28]` | float at obj+0x28 (r8 = [desc+0x00] = obj); instruction exists [V listing], reachability from tag-4 head not confirmed by casewalk | [?] |
| desc+0x28 record count | +0x28 | 4B | record loop | `0x6666c4e  mov rsi,[rbp+0x520]`<br>`0x6666c74  mov rax,[rsi+0x28]` | dword record count; records stride 0x28 | [V] |
| desc+0x30 records base | +0x30 | 8B | record loop | `0x6666c78  mov r15,[rsi+0x30]`<br>`0x6666c7c  lea rax,[rax+rax*4]`<br>`0x6666c80  lea rax,[r15+rax*8]` | records base; end = base + count*0x28 | [V] |
| desc+0x38 field | +0x38 | - | address only | `0x6666c55  lea r9,[rsi+0x38]`<br>`0x6666c60  lea rdx,[rbp+0x1E0]`<br>`0x6666c67  lea rcx,[rbp+0xE8]`<br>`0x6666c6e  call 0x56D55E0` | &desc+0x38 passed to formatter 0x56D55E0; width not shown by lea | [V] |
| rec+0x00 xmmword | rec+0x00 | 16B | per-record field | `0x6666cb0  add r15,0x28`<br>`0x6666ccc  movups xmm7,[r15]` | record 16B field (stride 0x28 array at desc+0x30) | [V] |
| rec+0x10 dword | rec+0x10 | 4B | per-record field | `0x6666cd0  mov eax,[r15+0x10]` | record dword field | [V] |
| rec+0x14 dword | rec+0x14 | 4B | per-record field | `0x6666cd4  mov ecx,[r15+0x14]` | record dword field | [V] |

## Size proof — UIImGui [I]
Reads: +0x00 qword (ends 0x08), +0x08 qword (ends 0x10), +0x28 dword (ends 0x2C), +0x30 qword (ends 0x38), +0x38 field addressed only (lea, width unknown). True size **>= 0x38 [I]**; whether +0x38 is a qword (size 0x40) is not pinned statically ([UNVERIFIED: 0x6666c55 width of desc+0x38 field — lea only]). Sub-objects: obj = *(desc+0x00) (fields obj+0x80 word, obj+0x28 float, vtable-driven) and the record array at desc+0x30 (count desc+0x28, stride 0x28; rec+0x00/0x10/0x14 above) — separate heap objects, not description bytes.

## What I tried that failed (this retry)
- Producer-angle sizing (r1/r2, documented there): Gameface via producer 0xaed5d30 — FAILED (0x1000+ byte function, heavy stack reuse, slotscan extent unreliable, no constructor/adjacent-local bound); UIImGui producer via `slotscan ui -q` — FAILED (empty for tag 4). Not re-done; this unit decodes the visitor cases + extractor directly instead.
- Static upper bound on Gameface size: still fails — fat clone 0x1f44d80, no description ctor in Minecraft code → capture requested below.

## CLOSES?
CLOSES? NO — blocking fact: Gameface true size cannot be bounded statically (fat clone 0x1f44d80, no description constructor; verified reads bound it to >= 0x88 only). Everything else in the item line is [V]-proven: UIMesh tag 2 (size 0xA8, +0x18 mRefs[4], +0x88 DescVariantRef tag +0xA0) in oc_U-ER10_r2.md; HudIcon DONE elsewhere [V] (size 0x50, producer 0xe9aed0, case 0x6664d51; Descriptions.h static_asserts); Gameface per-field reads, sub-objects (variantA/B ptr+ctrl, record list at +0x80, stride 0x1A0); UIImGui per-field reads, sub-objects (obj=*desc+0x00, record array at +0x30 stride 0x28) and size >= 0x38 [I]. Livecap capture requested for Gameface size at extractor entry 0x66ade80 (name u_er10_gameface_size); once it returns, re-run this unit's size check and re-issue CLOSES?.

## TOOL REQUESTS
- livecap capture `u_er10_gameface_size` at entry 0x66ade80 (queued; first add attempt rejected: capture name must match [a-z0-9_]+, retried with underscores) — why: bound Gameface description object size statically unbounded. (No helper scripts written; all evidence from rdis.exe dis + listing + casewalk.py + jt.py.)
