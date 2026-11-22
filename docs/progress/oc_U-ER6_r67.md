## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative; every `0xRVA  instr` line copied verbatim from verified r1-r3 listings. Tags: [V] seen in disassembly | [I] inferred | [?] unknown.

CLOSED [V] (r1-r3, not redone — summaries only): tag byte at variant+0x08 with `jmp rax` through JT 0xF2BF2B0; tag 0 = Ambient, 1 = Directional, 2 = GameplayMetadata, 3 = LightPoint, 4 = ShadowAtlasFrame (FrameBuilder.h:79-88 wins; group_visitors.md 6g/6ih rows had 2/3 swapped); all four pass-cursor writes by the Light visitor only.

OPEN: consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 (not located anywhere — write-only statically) and description field value names (unknown [?]).

A live capture for this item is already queued: `oc_u_er6_light_desc`, entry 0x6640d80 (the proved light visitor), size 0x100, max 6 — no result yet in docs/data/live/. It can confirm LightPoint/ShadowAtlasFrame description sizes at runtime and name producer callers via `ret=`; it cannot watch pass-vector element reads. Game is running (livemem status: pid 13452) but livemem has no read/write watch and no consumer address is known, so it cannot settle the consumer question either.

## 1. Answer table (one row per distinct offset, all sites listed)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via JT 0xF2BF2B0; JT entry 2 -> GameplayMetadata case 0x6640f1b, 3 -> LightPoint case 0x66410a0, 4 -> ShadowAtlasFrame case 0x6640ec1 (entry-target list parsed from PE [I]); producer tag stores + __FUNCSIG__ srclocs and FrameBuilder.h:79-88 fix tag 2 = GameplayMetadata, tag 3 = LightPoint [V]; group_visitors.md had them swapped [V] | [V] |
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V]; every write is an end-cursor increment, no end-cursor pop/decrement exists anywhere in the exe [V]; CONSUMER (draining element reader) not located anywhere in the exe [?] | [V]/[?] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers: Directional 0x66416ff and Point 0x6641461 via 0x675FB30 [V]; cursor reads at 0x66ed5f0/0x66ed5f7 only compute (end-begin)/stride and append — not an element drain [V]; CONSUMER of elements not located anywhere in the exe [?] | [V]/[?] |
| pass+0x650 | 4 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; light-record index = (end - begin) / 0x48 - 1 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84`<br>`0x6643198  mov eax,[rdi+0x4A0]` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag 2 appends 0x84-byte elements, verified gm+0x00..gm+0x3C copy rows [V]; CONSUMER (draining element reader) not located anywhere in the exe [?] | [V]/[?] |
| pass+0x4A8 | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8, stride 0x50 [V]); tag 4 copies the description verbatim (sa+0x00..sa+0x48) [V]; CONSUMER (draining element reader) not located anywhere in the exe [?] | [V]/[?] |
| description value names | - | - | - | no RTTI and no description member name strings exist in the release exe; headers type fields as mValue* placeholders with static_assert offsets only; producer-side meanings (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names; live capture bytes are values, not names [?] | [?] |

## 2. Consumers — sweep angles (static, exhausted; not redone this unit)

Whole-image `rdis fld --r/--w` scans for 0x800/0x648/0x4A0/0x1D0 and their begin cursors 0x7F8/0x650/0x498/0x1C8: every access is (a) a stack local ([rbp/rsp+disp]), (b) a cursor-field access by the four Light-visitor writers or grow/relocate code, or (c) the same offset on an unrelated object; all writes are end-cursor increments, no pop/decrement, no `[pass_base + index]` element read for any of the four offsets [V]. endFrame full listing (sub_66232b0, 0x66232b0..0x662e680) calls 0x5ABA5C0 three times but touches none of the four cursors; endFrame uses other pass vectors (+0x20/+0x50/+0x38 family) [V]. All 18 direct 0x5ABA5C0 callers enumerated via `xref.py callers` — none drains these vectors [V]. `rdis ptr 0x5aba5c0`: 0 pointer(s) — no indirect caller slot [V]. Cursor-register indexing blind spot (load cursor once, then read `[cursor_reg + index*stride]`) checked by enumerating every cursor-reader function: none indexes elements [V].

New this unit: `python tools/livecap/request.py result oc_u_er6_light_desc` → "no result yet (orchestrator has not run it)" — capture is pending (queued before this unit, not re-queued). livemem `status` → game running pid 13452, but livemem has no read/write watch facility and no consumer address is known, so no livemem read can settle the consumer question; not attempted beyond status.

## 3. CLOSES?

NO — single blocking fact: no draining element reader (consumer) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01: whole-image read/write scans show only the four Light-visitor cursor accesses [V], every write is an end-cursor increment with no pop, all `0x5ABA5C0` callers are accounted for [V], and the cursor-register indexing blind spot was enumerated negative [V]. Closed [V]: tag names (tag 2 = GameplayMetadata, tag 3 = LightPoint) and the group_visitors.md vs LightGroupTag conflict (FrameBuilder.h wins; 2/3 were swapped there); all four cursor writes [V]. Still unknown [?]: description field value names (no RTTI/name strings anywhere) and the four consumers. The pending live capture oc_u_er6_light_desc may add [V live] confirmation of description sizes/tag dispatch and the producer caller chain (`ret=`), but it cannot produce a consumer or field names, so the item stays open until either a consumer entry point is identified (for a targeted capture) or the orchestrator declares write-only acceptable.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued, pending (entry 0x6640d80, size 0x100, max 6; why: R6 desc sizes/tag dispatch + producer caller chain via ret=); result awaited at docs/data/live/oc_u_er6_light_desc.txt. Not re-added (duplicate name fails). No helper scripts written; nothing done by hand that a tool could not do.
