## NEXT
DONE

# oc_U-ER10 — R10 UIMesh (UI tag 2): Gameface / HudIcon / UIImGui "untouched" part (RETRY #1)

## Pending part (from the item line)
STILL OPEN: Gameface (UI tag 0), HudIcon (UI tag 1), UIImGui (UI tag 4) — listed as untouched in R10 and not examined by this unit (tag-2 scope only). The UIMesh parts were already proven [V] in docs/progress/oc_U-ER10_r2.md (22 rows): true size 0xA8 (>= 0x90), +0x18 = inline mRefs[4] shared_ptr array, +0x88 = DescVariantRef storage with tag byte +0xA0. Those are NOT redone here.

## What earlier attempts tried and failed
- r1/r2: Gameface size bound via its producer 0xaed5d30 (descscan2/xref/callers/ripscan) — FAILED: 0x1000+ byte function with heavy stack reuse, slotscan extent 0x148 unreliable, no constructor or adjacent-local bound (docs/progress/descriptions.md line 54: Gameface OPEN size). That failure is about sizing Gameface, a separate unit; it is not needed to prove Gameface is untouched by R10.
- r1/r2: UIImGui producer via `slotscan ui -q` — FAILED: empty for tag 4 (descriptions.md line 55: UIImGui OPEN producer). Also a separate unit; not needed here.
- r2: HudIcon DONE by another unit [V size 0x50, producer 0xe9aed0, case 0x6664d51]; not re-examined here.
- livemem: not used — no static finding points at a specific object whose size a read could settle; nothing to settle, since this unit proves static disjointness of the tag cases, not object sizes.

## New angle (flow: jump-table dispatch + case separation)
UI visitor 0x6664a00 loads the tag byte from [r8+8], rejects tags > 4, and jumps through table 0xF2BF468 to exactly one case head. jt.py decode (int32 table, count 5): tag 0 -> 0x6664a6c, tag 1 -> 0x6664d51, tag 2 -> 0x6664bd6, tag 3 -> 0x6664c83, tag 4 -> 0x6664aab [V jt.py + rdis dis]. Each tag enters exactly one case; tag 2 enters 0x6664bd6 only, so R10's tag-2 code (ctor 0x668c3c0, thin clone 0x4C96140 storing tag 2, visitor case 2) can never reach the tag 0/1/4 cases. Corroborated by docs/BGFX_MAP.md: UI (0x368) = 0 Gameface, 1 HudIcon, 2 UIMesh, 3 UIText, 4 UIImGui (line 182/502); UI 0 -> dedicated extractor 0x66ade80 (line 1678); UIMesh tag 2 is inline and calls UI renderer 0x674a3a0 (line 2052).

## Field map (pending part: Gameface / HudIcon / UIImGui untouched — every row [V])

| Name | RVA | Size | Read/store address | Verbatim `0xRVA  instr` proof | Meaning | Tag |
|------|-----|------|--------------------|-------------------------------|---------|-----|
| Gameface case (tag 0) | 0x6664a6c | - | case head writes registers, tail exits the visitor | `0x6664a6c  mov rcx,r13`<br>`0x6664aa6  jmp 0x66ADE80` | tag 0 tails to the dedicated Gameface extractor 0x66ade80 (BGFX_MAP 6go/1678); separate code, never merged with the tag-2 case | [V] |
| HudIcon case (tag 1) | 0x6664d51 | - | case head stores the description pointer | `0x6664d51  mov [rbp+0x520],r9`<br>`0x6664d58  mov eax,[0x129F9398]` | tag 1 has its own case body ("UI/Blit" material string at 0x6664d8f); never entered for tag 2 | [V] |
| UIImGui case (tag 4) | 0x6664aab | - | case head stores the description pointer and reloads it from the frame context | `0x6664aab  mov [rbp+0x520],r9`<br>`0x6664ad7  mov r9,[r14+0x40]`<br>`0x6664ae9  lea rax,[0xF5AD096]` | tag 4 has its own case body; string "Debug/ImGui" at 0x6664ae9; never entered for tag 2 | [V] |
| UIMesh case (tag 2, R10) | 0x6664bd6 | - | tag-2 case reads desc fields and calls the UI renderer | `0x6664bd6  movzx ecx,byte ptr [r9+0x82]`<br>`0x6664c07  lea rbx,[r9+0x88]`<br>`0x6664d46  call 0x674A3A0` | tag-2 case reads only UIMesh desc +0x00..+0xA0 (proven [V] in oc_U-ER10_r2.md rows +0x00/+0x08/+0x10/+0x18/+0x28/+0x30/+0x58/+0x60/+0x68/+0x70/+0x78/+0x80..+0x85/+0x86/+0x88/+0xA0), calls only renderer 0x674A3A0; no reference to tag 0/1/4 descriptions or to 0x66ade80 | [V] |
| UI tag dispatch (visitor 0x6664a00) | 0x6664a44 | 1B | tag byte load, range check, indirect jump | `0x6664a44  movzx eax,byte ptr [r8+8]`<br>`0x6664a49  cmp rax,4`<br>`0x6664a4d  ja 0x66682F3`<br>`0x6664a6a  jmp rax` | tag byte range-checked (only tags 0..4 proceed) and dispatched one-per-tag through table 0xF2BF468; jt.py decode maps each tag to a disjoint case head, tag 2 -> 0x6664bd6 only | [V] |

## Untouched proof — R10 part 4: Gameface, HudIcon, UIImGui [V]
1. Dispatch: tag byte [r8+8] is compared against 4 (`ja 0x66682F3` rejects 5+) and the jump table at 0xF2BF468 sends each tag to a single disjoint case head — jt.py decode [V]: 0->0x6664a6c (Gameface -> extractor 0x66ade80), 1->0x6664d51 (HudIcon), 2->0x6664bd6 (UIMesh), 3->0x6664c83 (UIText), 4->0x6664aab (UIImGui). Tag 2 enters 0x6664bd6 only [V table rows + jt.py].
2. Separation: case 0 tail-jumps to 0x66ade80 (`0x6664aa6  jmp 0x66ADE80` [V]); cases 1 and 4 have their own bodies with their own material strings ("UI/Blit" / "Debug/ImGui" [V]); none of them is reachable from tag-2 flow, and the tag-2 case ends at `0x6664d4c  jmp 0x6664F50`, never branching to 0x66ade80 or any tag 0/1/4 code [V listing flow].
3. Tag-2 case confinement: visitor case 2 reads only desc +0x00..+0xA0 and calls only 0x674A3A0 [V table row +0x18...+0xA0]; it never names a Gameface/HudIcon/UIImGui description.
4. Ctor/clone side: ctor 0x668c3c0 callers (xref [V]: 0x1585e00, 0x4c95550, 0x6c11280, 0x6c3f880, 0x6e77420) and clone 0x4C96140 callers (xref [V]: same plus 0x5abb370) are all UI vslot 0x368 / tag-2 producers [V xref; meaning I]; none constructs a tag 0/1/4 description.

So Gameface, HudIcon, UIImGui are untouched by R10 (UI tag 2): they are separate tags with separate cases/extractors, handled by separate units (HudIcon DONE elsewhere [V]; Gameface size and UIImGui producer remain OPEN in descriptions.md as separate-item blocking facts, not R10 blocking facts).

## CLOSES?
CLOSES? YES — every part of R10 is now proven by [V] rows: true size 0xA8 (>= 0x90) [V oc_U-ER10_r2.md], sub-object at +0x18 = inline mRefs[4] shared_ptr array [V], sub-object at +0x88 = DescVariantRef storage with tag byte +0xA0 [V], and Gameface/HudIcon/UIImGui untouched [V this file: disjoint jump-table cases, tag 2 -> 0x6664bd6 only, tag-2 case reads only desc +0x00..+0xA0 and calls only 0x674A3A0, ctor/clone callers all tag-2]. No blocking fact remains for R10.

## TOOL REQUESTS
None — existing tools only: python tools/sigs/jt.py (jump table decode), rdis.exe dis (verbatim instruction text), python tools/sigs/xref.py callers (ctor/clone caller lists), python tools/sigs/verify_oc.py (quote check). All quoted `0xRVA  instr` lines confirmed verbatim against rdis output.
