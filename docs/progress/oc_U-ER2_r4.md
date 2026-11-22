## NEXT
DONE

# U-ER2: R2 BlockChanges (Item tag 9) — field meanings; pass vector (pass+0x98/+0xA0)

GOAL (docs/RENDER_CHECKLIST.md line ~600): close "R2 BlockChanges (Item tag 9): field meanings; the pass vector it feeds (pass+0x98/+0xA0)". Pending per r1–r3: field meanings of desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword), tag-9 producer via builder slot 0x378, consumer of pass+0x98 vector. The pass vector itself (pass+0x98 end cursor, pass+0xA0 capacity bound, 0x18 element stride) is already proven [V] and is NOT redone here.

## Proven already [V] (from r1/r2/r3 input data, verified against the listing; not re-derived)

- Handler 0x6646bc6 (tag 9, extent 0x6646bc6..0x6646c8c; rdis names it sub_6646bc6, 0 static xrefs in — reached only via visitor jump table), visitor 0x6646980, jump table 0xf2bf2d0 tag 9 -> 0x6646bc6. Entry: rdi = description pointer (variant payload, from visitor arg3+0x0), rsi = pass object after `0x6646be3 mov rsi,rax` from `0x6646bde call 0x5ABA5C0` (passLookup at frame_context+0x10+0x9D0); frame context at rbp+0x8A0.
- `0x6646bc6  movups xmm7,[rdi]` reads desc+0x00 (16-byte float4 = RenderBlockChangesDescription.mVec00[4]); `0x6646bc9  movsd xmm6,[rdi+0x10]` reads desc+0x10 (qword = mQword10). Descriptions.h: sizeof 0x18, offsetof mQword10 == 0x10 — handler reads exactly these two fields [V].
- `0x6646c61  mov r12,[rsi+0x98]` loads pass+0x98 = vector end cursor (insert point) into r12; `0x6646c68  cmp r12,[rsi+0xA0]` compares with pass+0xA0 = vector end-of-storage / capacity bound; `0x6646c6f je 0x66474E8` -> grow path when full.
- `0x6646c75  movups [r12],xmm7` stores desc+0x00 float4 at vector end; `0x6646c7a  movlps [r12+0x10],xmm6` stores desc+0x10 qword at vector end+0x10; `0x6646c80  add qword ptr [rsi+0x98],0x18` advances cursor by 0x18 element stride; `0x6646c88  jmp 0x6647A74` shared tail. Element = 0x18 bytes {float4, qword} [V].
- pass+0x90 = vector begin: `0x66474eb  sub r13,[rsi+0x90]` [V]; grow path `0x66474e8  mov r13,r12` then count=(end-begin)/0x18 (`sar rax,3` / `imul 0xAAAAAAAAAAAAAAAB`), generic realloc/copy of 0x18-byte elements, commit [V].

## New angles tried in r1/r2/r3 (ALL failed — do not repeat)

1. `xref str "BlockChanges"` — no output: no such string in the exe; producer/consumer not reachable by name.
2. `xref callers 0x5ABA5C0` (passLookup) — long list (~40 entries incl. 0x66232b0, 0x6646980, 0x66ea3d0); none is the BlockChanges producer; no insert clone for tag 9; insert routed through CFG thunk [0xF99FFA0] / indirect vtable dispatch.
3. `descscan2.py --visitor item --case 9 --follow` — 862 instructions through grow path + shared tails; description register rdi read ONLY at +0x000 (xmmword) and +0x010 (qword); no read assigns semantic meaning.
4. Disassembled grow path 0x66474e8 + shared tail 0x6647a74 — generic vector grow/realloc plus separate 0xC8-stride vector at pass+8/+0x10; no element consumption, no field meaning.
5. `rdis vt/class/ptr 0xf2bdeb0` (BgfxFrameBuilder vtable) — 2 ctor sites (0x660d9d0, 0x67eca07) set vtable at runtime on heap instances; `ptr` finds ZERO static data locations storing the vtable → no static/global FrameBuilder anchor → livemem cannot locate pass objects (no anchor; livemem cannot scan).
6. Whole-.text capstone scan for `{16-byte store, then qword store at +0x10}` description-construction pattern — truncated/unreliable; even if it worked, tracing desc values upstream to semantic meaning still required.
7. passLookup full caller list scanned for `[reg+0x98]`/`[reg+0xA0]`/`[reg+0x90]` reads — only false positives (stack slots, vtable slot load). No consumer of pass+0x98 vector located.
8. `xref callers 0x66466e0` (_insert(Item) body = vtable slot 0x378) — EMPTY: 0 direct xrefs, reached only by indirect `call [vtable+0x378]`; no call site can be isolated as the tag-9 producer; tag 9 has no insert clone (BGFX_MAP 6w).

## Field-meaning table (one row per distinct offset; all sites listed; meaning '-' where no instruction or string assigns it)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|------|-------------------------|---------|-----|
| desc+0x00 | 16 | read `0x6646bc6`; stored into vector slot `0x6646c75` | `0x6646bc6  movups xmm7,[rdi]` | - (mVec00[4] float4; copied element-wise into the pass vector; no instruction or string assigns a meaning) | [V] |
| desc+0x10 | 8 | read `0x6646bc9`; stored into vector slot `0x6646c7a` | `0x6646bc9  movsd xmm6,[rdi+0x10]` | - (mQword10 qword; copied element-wise into the pass vector; no instruction or string assigns a meaning) | [V] |
| pass+0x90 | 8 | `0x66474eb` | `0x66474eb  sub r13,[rsi+0x90]` | vector begin (base of the 0x18-stride element array); proven [V] context, not a pending field-meaning field | [V] |
| pass+0x98 | 8 | `0x6646c61`, advanced `0x6646c80` | `0x6646c61  mov r12,[rsi+0x98]` | vector end cursor / insert point; element stored at it (0x6646c75) then advanced by 0x18 (0x6646c80) | [V] |
| pass+0xA0 | 8 | `0x6646c68`, full-test `0x6646c6f` | `0x6646c68  cmp r12,[rsi+0xA0]` | vector capacity bound; cursor==bound gates grow path (0x6646c6f je 0x66474e8) | [V] |

## Producer status

- tag-9 producer via builder slot 0x378: NOT located. BGFX_MAP 6w: Item group tag 9 = BlockChanges has NO insert clone (clones exist only for tags 0-8, 10); insert is inlined where used. `_insert(Item)` vtable slot 0x378 = 0x66466e0 (vtdump) has 0 direct xrefs — reached only by indirect `call [vtable+0x378]`; its sole downstream target is visitor 0x6646980 (`xref callers 0x6646980` -> 0x66466e0 only). `rdis ptr 0xf2bdeb0`: ZERO static vtable stores → no static/global FrameBuilder anchor.

## Consumer status

- consumer of pass+0x98 vector: NOT located. pass+0x90/+0x98/+0xA0 referenced only inside the tag-9 handler and its grow path (oc_U-ItmB.md tag-9 table: 17 sites, 5 offsets). No code reads the queued 0x18-byte element records after they are pushed.

## Live capture (new angle per orchestrator hint; static analysis exhausted)

- Orchestrator hint: request a live capture at a proven entry (visitor 0x6646980 or handler 0x6646bc6) — result lines `REG=value hit=N ret=0xRVA <bytes of the pointee>`; dumped description bytes confirm desc+0x00 float4 / desc+0x10 qword sizes and values, ret= names the caller chain; cite [V live].
- Checked `docs/data/live/`: no tag-9 capture exists (item_visitor.txt has no tag 9; _status.txt shows no U-ER2 result); no pre-existing result for u_er2_tag9_visitor.
- `python tools/livecap/request.py add u_er2_tag9_visitor ...` was NOT accepted: "4 requests already pending, ask again next unit" (queue full: createtexture_callers, bgfx_createtexture_producer, bgfx_texture_wrapper_bc73bf0, dragon_texture_entry_c296b50, dragon_texture_caller_bc41420 done; mc_root_4e05e50_callers, oc_u_el6b_desc, l8b_texcreate_record, el10b_lighting_desc pending). Livemem is not applicable: no anchor address (zero static vtable stores, no live tag-9 descptr).
- Retry next unit: capture at visitor entry 0x6646980 (targets.lua kind=visitor, arg register R8 = description pointer at entry) or handler entry 0x6646bc6 (rdis: function sub_6646bc6, rdi = description pointer at entry, 0 static xrefs); --size 0x100 --max 6 --why "R2 BlockChanges tag 9: dump description bytes at entry (desc+0x00 float4, desc+0x10 qword) to confirm field sizes/values live; ret= names caller chain (_insert slot 0x378 -> tag-9 producer)".

## CLOSES?

NO — blocking fact: the pass vector (pass+0x98 end cursor, pass+0xA0 capacity bound, 0x18 element stride) is proven [V], but the field meanings of desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword) are not shown by any instruction or string (both '-'), no tag-9 producer via builder slot 0x378 is located (no insert clone; only indirect dispatch through 0x66466e0), and no consumer of the pass+0x98 vector is located. Static analysis is exhausted (8 angles tried in r1–r3); the live capture at visitor 0x6646980 / handler 0x6646bc6 could not be queued (4 requests pending, queue full) and remains the one action that could add desc bytes + caller chain. Until it runs, the "field meanings" part of the item is not proven by [V] rows.

## TOOL REQUESTS

CAPTURE REQUESTED u_er2_tag9_visitor (add attempted, REJECTED — queue full: 4 requests pending; retry next unit at visitor entry 0x6646980, --size 0x100 --max 6, why: dump tag-9 description bytes desc+0x00/desc+0x10 and ret= caller chain). No helper scripts written.
