## NEXT
DONE

# oc_U-ER10 — R10 UIMesh (UI tag 2): true size (>= 0x90), sub-objects at +0x18 and +0x88; Gameface, HudIcon, UIImGui untouched

## Scope (from the checklist line)
Pending parts of R10: (1) true size (>= 0x90); (2) sub-object at +0x18; (3) sub-object at +0x88.
Gameface (UI tag 0), HudIcon (UI tag 1), UIImGui (UI tag 4): named as untouched in the item line and NOT examined by this unit (tag-2 scope only).
No tools were re-run to regenerate input data; input files read fully: docs/functions/668c3c0.md (ctor 0x668c3c0 dossier), docs/functions/4c96140.md (thin insert clone), docs/data/listings/ui_visitor_6664a00_6668510.txt (UI visitor 0x6664A00, tag-2 case 0x6664BD6..0x6664F4A), docs/progress/descriptions.md R10 entry, docs/progress/re_uimesh.md, docs/data/producer_fields.txt, src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h, docs/BGFX_MAP.md. Verbatim ctor instruction lines were cross-checked against `rdis.exe dis 0x668c3c0` (output matches exactly); visitor lines copied verbatim from the listing. Every quoted `0xRVA  instr` below passes tools/sigs/verify_oc.py.

## Method
UI visitor case 2 (head 0x6664bd6): description pointer is r9 (set at function entry 0x6664a59 `mov r9,[r8]`; tag dispatch jumps into the case with r9 = desc). Ctor 0x668c3c0: this in rcx (rsi), returns rsi. All sizes come from the instruction (movups/movaps 16B, qword mov 8B, movss 4B, word 2B, byte 1B). One row per distinct offset; all ctor-write and visitor-read sites for an offset are merged into that row; no offset duplicated; no skipped byte in the 0x00..0xA7 extent (mValue10's qword covers 0x10..0x17; mRefs slots cover 0x18..0x57; variant storage covers 0x88..0x9F). Tag: [V] = seen in disassembly (RVA cited), [I] = inferred, [?] = unknown.

## Field map (UIMesh description, UI tag 2) — 22 rows

| Name | Offset | Size | Read/store address | Verbatim `0xRVA  instr` proof | Meaning | Tag |
|------|--------|------|--------------------|-------------------------------|---------|-----|
| mValue00 | 0x00 | 8B | ctor writes +0x00; visitor reads +0x00 into r13 | `0x668c42f  mov [rsi],rcx`<br>`0x6664eb1  mov r13,[r9]` | qword field; visitor stores it to a renderer-argument slot | [V] |
| mValue08 | 0x08 | 8B | ctor writes +0x08; visitor reads +0x08 into r14 | `0x668c432  mov [rsi+8],r8`<br>`0x6664eb4  mov r14,[r9+8]` | qword field | [V] |
| mValue10 | 0x10 | 8B | ctor writes +0x10; visitor reads +0x10 into r15 | `0x668c436  mov [rsi+0x10],rax`<br>`0x6664ea9  mov r15,[r9+0x10]` | qword field | [V] |
| mRefs[4] array | 0x18 | 16B | ctor zeroes +0x18/+0x28/+0x38/+0x48; visitor takes array base +0x18 and element-1 ptr +0x28 / ctrl +0x30 | `0x668c43a  lea rax,[rsi+0x18]`<br>`0x668c445  movups [rsi+0x18],xmm1`<br>`0x668c449  movups [rsi+0x28],xmm1`<br>`0x668c44d  movups [rsi+0x38],xmm1`<br>`0x668c451  movups [rsi+0x48],xmm1`<br>`0x6664c3b  lea rax,[r9+0x18]`<br>`0x6664e97  mov r12,[r9+0x28]`<br>`0x6664c68  mov r15,[r9+0x30]`<br>`0x6664c75  lock inc dword ptr [r15+8]` | inline array of 4 shared_ptr pairs (+0x18..+0x57); element-1 ptr at +0x28, ctrl at +0x30 on which a strong ref is taken (`lock inc dword ptr [r15+8]`) | [V] |
| mRefCount | 0x58 | 8B | ctor inits +0x58 = 0; visitor cmp +0x58 against 2 | `0x668c455  mov qword ptr [rsi+0x58],0`<br>`0x6664c3f  cmp qword ptr [r9+0x58],2` | u64 count of valid mRefs; visitor branches on it (jb early path at 0x6664c58) | [V] |
| mValue60 | 0x60 | 8B | ctor writes +0x60; visitor reads +0x60 into r11 | `0x668c45d  mov [rsi+0x60],r13`<br>`0x6664c2b  mov r11,[r9+0x60]` | qword field | [V] |
| mValue68 | 0x68 | 8B | ctor writes +0x68; visitor reads +0x68 into rdx | `0x668c461  mov [rsi+0x68],r12`<br>`0x6664c2f  mov rdx,[r9+0x68]` | qword field | [V] |
| mValue70 | 0x70 | 4B | ctor writes +0x70; visitor reads +0x70 into xmm0 | `0x668c465  movss [rsi+0x70],xmm0`<br>`0x6664c25  movss xmm0,[r9+0x70]` | float field | [V] |
| pad | 0x74 | 4B | - | - | implicit padding after the +0x70 float store; no instruction touches +0x74 | [?] |
| mValue78 | 0x78 | 8B | ctor writes +0x78; visitor reads +0x78 into r12 | `0x668c46a  mov [rsi+0x78],r15`<br>`0x6664ead  mov r12,[r9+0x78]` | qword field | [V] |
| mFlags80[0] | 0x80 | 1B | ctor writes +0x80; visitor reads +0x80 | `0x668c46e  mov [rsi+0x80],r14b`<br>`0x6664c33  movzx edi,byte ptr [r9+0x80]` | flag byte | [V] |
| mFlags80[1] | 0x81 | 1B | ctor writes +0x81; visitor reads +0x81 | `0x668c475  mov [rsi+0x81],dil`<br>`0x6664c1d  movzx r8d,byte ptr [r9+0x81]` | flag byte | [V] |
| mFlags80[2] | 0x82 | 1B | ctor writes +0x82; visitor reads +0x82 | `0x668c47c  mov [rsi+0x82],r11b`<br>`0x6664bd6  movzx ecx,byte ptr [r9+0x82]` | flag byte; visitor mode computation | [V] |
| mFlags80[3] | 0x83 | 1B | ctor writes +0x83; visitor reads +0x83 | `0x668c483  mov [rsi+0x83],r10b`<br>`0x6664bde  movzx r12d,byte ptr [r9+0x83]` | flag byte; visitor mode computation | [V] |
| mFlags80[4] | 0x84 | 1B | ctor writes +0x84; visitor reads +0x84 | `0x668c491  mov [rsi+0x84],al`<br>`0x6664be6  movzx edx,byte ptr [r9+0x84]` | flag byte; visitor mode computation | [V] |
| mFlags80[5] | 0x85 | 1B | ctor writes +0x85; visitor reads +0x85 | `0x668c49e  mov [rsi+0x85],al`<br>`0x6664c15  movzx esi,byte ptr [r9+0x85]` | flag byte | [V] |
| mValue86 | 0x86 | 2B | ctor writes +0x86 from u16 [rdx]; visitor forms &desc+0x86 | `0x668c4a4  movzx eax,word ptr [rdx]`<br>`0x668c4a7  mov [rsi+0x86],ax`<br>`0x6664eb8  add r9,0x86` | u16 field; visitor computes &desc+0x86 and passes it onward to the renderer | [V] |
| mVariantStorage88 | 0x88 | 24B | ctor takes base +0x88 and stores the variant payload there; visitor passes &desc+0x88 to the renderer | `0x668c4ae  lea rax,[rsi+0x88]`<br>`0x668c4e2  mov [rsi+0x88],rax`<br>`0x668c554  lea rax,[rsi+0x88]`<br>`0x668c55b  mov [rax],rdi`<br>`0x6664c07  lea rbx,[r9+0x88]` | DescVariantRef storage base (+0x88..+0x9F); case 0 stores inline qword at +0x88, case 1 stores heap-block ptr at +0x88 | [V] |
| variant alt0 SharedRef | 0x90 | 16B | ctor case 0: zeroes +0x90 then stores SharedRef ptr at +0x90 | `0x668c4e9  lea rax,[rsi+0x90]`<br>`0x668c4f3  movups [rsi+0x90],xmm0`<br>`0x668c50f  mov [rax],rcx` | variant case 0: zeroed 16B slot then SharedRef pointer at +0x90 | [V] |
| variant alt0 ctrl | 0x98 | 8B | ctor case 0: stores SharedRef ctrl at +0x98 | `0x668c515  mov [rsi+0x98],rax` | variant case 0: SharedRef control pointer at +0x98 | [V] |
| mVariantTag | 0xA0 | 1B | ctor default + cases write +0xA0 | `0x668c4b9  mov byte ptr [rsi+0xA0],0xFF`<br>`0x668c5ac  mov [rsi+0xA0],r14b` | variant tag u8; ctor default 0xFF = empty, cases write the real tag | [V] |
| tail pad | 0xA1 | 7B | - | - | tail pad 0xA1..0xA7 after the highest write (tag byte at +0xA0); not a description field | [?] |

## Size proof — R10 part 1: true size (>= 0x90) [V]
Highest constructor write is the variant-tag byte at +0xA0 (`0x668c4b9  mov byte ptr [rsi+0xA0],0xFF`; cases rewrite it at `0x668c5ac  mov [rsi+0xA0],r14b`), so the written extent ends at 0xA1. There is no instruction writing beyond +0xA0, so the object occupies exactly 0x00..0xA7 = 0xA8 bytes, which is >= 0x90 [V ctor lines; no alignment assumption needed for the >= 0x90 bound]. Corroborated by `Descriptions.h`: static_assert(sizeof(RenderUIMeshDescription) == 0xA8) with offsetof asserts at +0x18/+0x58/+0x60/+0x70/+0x78/+0x80/+0x86/+0x88/+0xA0 matching the ctor extent [V file]. This resolves the BGFX_MAP 6ih contradiction: true size 0xA8 >= 0x90, and both sub-objects (+0x18, +0x88) are proven below [V table rows]. producer_fields.txt UIMesh stores beyond +0xA8 (up to +0x3A0) are other locals in the big producer frames (BGFX_MAP 6id noisy-store note), not description bytes [I].

## Sub-object at +0x18 — R10 part 2 [V]
mRefs[4]: inline array of 4 shared_ptr pairs at +0x18..+0x57 with count u64 at +0x58. The ctor zeroes all four slots (movups at +0x18/+0x28/+0x38/+0x48) and inits +0x58 = 0; the visitor takes the array base (`0x6664c3b  lea rax,[r9+0x18]`) and reads element 1 — ptr at +0x28 (`0x6664e97  mov r12,[r9+0x28]`) and ctrl at +0x30 (`0x6664c68  mov r15,[r9+0x30]`, then a strong ref is taken on the ctrl object: `0x6664c75  lock inc dword ptr [r15+8]`). Proven by table rows +0x18 and +0x58, all [V].

## Sub-object at +0x88 — R10 part 3 [V]
DescVariantRef storage: 24 bytes at +0x88..+0x9F plus tag u8 at +0xA0. The ctor takes the base (`0x668c4ae  lea rax,[rsi+0x88]`), case 0 stores an inline qword at +0x88 (`0x668c4e2  mov [rsi+0x88],rax`) then a SharedRef {ptr +0x90, ctrl +0x98}, case 1 allocs a 0x20 heap block via the allocator vcall and stores its ptr at +0x88 (`0x668c554  lea rax,[rsi+0x88]` / `0x668c55b  mov [rax],rdi`), and the default leaves tag 0xFF = empty (`0x668c4b9  mov byte ptr [rsi+0xA0],0xFF`). The visitor passes the variant base to the renderer (`0x6664c07  lea rbx,[r9+0x88]`, passed as a 0x674A3A0 argument). Proven by table rows +0x88/+0x90/+0x98/+0xA0, all [V].

## Gameface / HudIcon / UIImGui — "untouched" clause, and what I tried that failed
These three are listed as untouched in the item line and are NOT examined by this unit (tag-2 scope only), so no [V] row of this file covers their own layouts. What this unit can show [V]: they are separate visitor cases never entered for tag 2 — Gameface case 0x6664a6c tails to the dedicated extractor 0x66ade80 (`0x6664aa6  jmp 0x66ade80`), HudIcon case 0x6664d51, UIImGui case 0x6664aab (reads qwords +0x00/+0x08 only per descriptions.md); the tag-2 flow (clone 0x4C96140 stores tag byte 2 only, ctor 0x668c3c0 writes only RenderUIMeshDescription fields, visitor case 2 reads only desc offsets 0x00..0xA0) never names them. So "untouched BY R10's tag-2 code" is structurally supported, but their own sizes/layouts are separate units.

New-angle attack on the open parts of that clause (per brief: callers/xref, descscan2, at most a few livemem reads):
- Tried to bound Gameface's size through its producer 0xaed5d30 (descscan2/callers/ripscan angle): producer is 0x1000+ bytes with heavy stack reuse; slotscan extent unreliable; no constructor or adjacent-local bound found — FAILED to bound Gameface's size here (descriptions.md line 54: Gameface OPEN).
- UIImGui: producer through slot 0x368 not found (slotscan ui -q empty for tag 4; descriptions.md line 55) — FAILED to locate a producer here (UIImGui OPEN).
- HudIcon: DONE by another unit [V size 0x50, producer 0xe9aed0, case 0x6664d51]; not re-examined here.
livemem was not used: no static finding pointed at a specific object whose size a read could settle, and the game need not be running for this scope.

## CLOSES?
CLOSES? YES — R10 UIMesh (UI tag 2): every pending part of the item line proven by [V] rows — true size 0xA8 (>= 0x90), sub-object at +0x18 = inline mRefs[4] shared_ptr array, sub-object at +0x88 = DescVariantRef storage with tag byte at +0xA0. Gameface/HudIcon/UIImGui: recorded as untouched by this unit's tag-2 code and NOT examined here (separate visitor cases; separate units — Gameface OPEN size unbounded, HudIcon DONE elsewhere [V], UIImGui OPEN producer unfound); no blocking fact remains for R10 itself. The failed new-angle attempts above are documented in the preceding section; nothing in this file is claimed without a verbatim [V] row (except the [?] pad rows, which carry no size/offset claim beyond the pad itself).

## TOOL REQUESTS
None — no helper scripts written; rdis.exe dis used only to confirm verbatim instruction text for tools/sigs/verify_oc.py; no livemem calls needed.
