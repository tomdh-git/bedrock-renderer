## NEXT
DONE — static part of this unit complete; capture oc_u_er2 blocked by the 4-pending queue (retry add next unit); CLOSES? NO — desc+0x00/desc+0x10 meanings, tag-9 producer, pass+0x98 consumer all await the live capture result at visitor 0x6646980.

# U-ER2: R2 BlockChanges (Item tag 9) — field meanings; pass vector (pass+0x98/+0xA0)

## Goal (docs/RENDER_CHECKLIST.md line ~600)

Close "R2 BlockChanges (Item tag 9): field meanings; the pass vector it feeds (pass+0x98/+0xA0)". Pending parts carried from r1-r3 (read fully, NOT repeated): meanings of desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword), the tag-9 producer via builder slot 0x378, and the consumer of the pass+0x98 vector. The pass vector itself (pass+0x98 end cursor, pass+0xA0 capacity bound, 0x18 element stride) is already proven [V].

## Already proven [V] (r1-r3 input data; not re-derived here)

- Tag 9 handler 0x6646bc6..0x6646c8c inside visitor 0x6646980 (jump table 0xf2bf2d0, tag 9 -> 0x6646bc6; docs/functions/6646980.md). Signature: visitItem(BgfxFrameBuilder* this rcx, FrameCtx* frame rdx, const Variant* v r8: {desc* +0, u8 tag +8}) [V]. rdi = description pointer; rsi = pass object after `0x6646bde call 0x5ABA5C0` (passLookup at frame ctx +0x10 +0x9D0) [V].
- `0x6646bc6  movups xmm7,[rdi]` reads desc+0x00 (16-byte float4); `0x6646bc9  movsd xmm6,[rdi+0x10]` reads desc+0x10 (qword). Descriptions.h: RenderBlockChangesDescription { float mVec00[4] +0x00; uint64_t mQword10 +0x10; sizeof 0x18 } — header carries NO semantic comment on either field [V header; field names I from header].
- `0x6646c61  mov r12,[rsi+0x98]` loads pass+0x98 = vector end cursor (insert point) into r12; `0x6646c68  cmp r12,[rsi+0xA0]` compares with pass+0xA0 = end-of-storage / capacity bound; `0x6646c6f  je 0x66474e8` branches to the grow path when full [V].
- `0x6646c75  movups [r12],xmm7` stores desc+0x00 at vector end; `0x6646c7a  movlps [r12+0x10],xmm6` stores desc+0x10 at vector end+0x10; `0x6646c80  add qword ptr [rsi+0x98],0x18` advances the cursor by the 0x18 element stride; `0x6646c88  jmp 0x6647A74` shared tail [V]. Element = 0x18 bytes {float4, qword}.
- `0x66474e8  mov r13,r12`; `0x66474eb  sub r13,[rsi+0x90]` → pass+0x90 = vector begin; grow path computes element count = (end-begin)/0x18, reallocs, copies 0x18-byte elements, commits at shared tail 0x6647a74 [V].
- No insert clone for tag 9 (BGFX_MAP 6w/6g); `_insert(Item)` vtable slot 0x378 = 0x66466e0 has 0 direct xrefs (indirect `call [vtable+0x378]` only); `rdis ptr 0xf2bdeb0` finds zero static vtable stores → no static FrameBuilder anchor (livemem cannot scan) [V].

## Field-meaning table (one row per distinct offset, every site listed; meaning '-' unless an instruction/string shows it)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| desc+0x00 | 16 | 0x6646bc6 | `0x6646bc6  movups xmm7,[rdi]` | - (mVec00[4] float4; copied element-wise into the pass vector; no instruction or string assigns it a meaning) | [V] |
| desc+0x10 | 8 | 0x6646bc9 | `0x6646bc9  movsd xmm6,[rdi+0x10]` | - (mQword10 qword; copied element-wise into the pass vector; no instruction or string assigns it a meaning) | [V] |
| pass+0x98 | 8 | 0x6646c61, 0x6646c80 | `0x6646c61  mov r12,[rsi+0x98]` | vector end cursor / insert point; element stored at it (0x6646c75 `movups [r12],xmm7`, 0x6646c7a `movlps [r12+0x10],xmm6`), then advanced by 0x18 (0x6646c80 `add qword ptr [rsi+0x98],0x18`) | [V] |
| pass+0xA0 | 8 | 0x6646c68 | `0x6646c68  cmp r12,[rsi+0xA0]` | vector capacity bound / end-of-storage; cursor==bound gates the grow path (0x6646c6f `je 0x66474e8`) | [V] |
| pass+0x90 | 8 | 0x66474eb | `0x66474eb  sub r13,[rsi+0x90]` | vector begin (base of the 0x18-stride element array); grow-path count = (end-begin)/0x18 — proven context, not a pending field-meaning offset | [V] |

## New static angles — all exhausted in r1-r3, NOT repeated in this unit

1. `xref str "BlockChanges"`: no such string in the exe; producer/consumer not reachable by name.
2. `xref callers 0x5ABA5C0` (~40 entries, first 100 instr each): only pass consumers; none is the BlockChanges producer; 0x66232b0's `[rax+0x98]` is a vtable slot load (rax = vtable ptr), not pass+0x98.
3. `descscan2.py --visitor item --case 9 --follow` (862 instr through grow path + shared tails): rdi read ONLY at +0x000 (xmmword) and +0x010 (qword); no other description field; no read assigns a semantic meaning.
4. Disassembled grow path 0x66474e8 + shared tail 0x6647a74: generic vector grow/realloc plus a separate 0xC8-stride vector at pass+8/+0x10; no element consumption, no field meaning.
5. `rdis vt/class/ptr 0xf2bdeb0`: 2 ctor sites set the vtable on heap instances at runtime; zero static data locations store the vtable → no static/global FrameBuilder anchor for livemem.
6. `xref callers 0x66466e0` (`_insert(Item)` vtable slot 0x378): EMPTY — 0 direct xrefs, reached only by indirect `call [vtable+0x378]`; no tag-9 call site can be isolated.

## Live capture (read-only; orchestrated — the game is not touched by this unit)

- `python tools/livecap/request.py result oc_u_er2` → "no result yet (orchestrator has not run it)"; docs/data/live/ has no tag-9 capture (item_visitor.txt covers tags 0,1,2,3,6,7,10 only).
- `python tools/livecap/request.py add oc_u_er2 0x6646980 --size 0x100 --max 6 --why "R2: BlockChanges tag-9 desc fields desc+0x00/+0x10 meanings; caller chain (ret=) of visitor 0x6646980"` → REJECTED: "4 requests already pending, ask again next unit" (queue holds mc_root_4e05e50_callers, oc_u_el6b_desc, l8b_texcreate_record, el10b_lighting_desc, all state=pending). Not queued yet.
- Retry next unit: same `add` command once a pending slot frees. Expected to add [V live]: REG=value (R8 = variant {desc*, tag}), desc bytes at descptr (desc+0x00 float4, desc+0x10 qword; confirm the 0x18 size), hit=N, and ret=caller RVA naming the tag-9 insert call site (producer). On result: decode desc bytes, cite [V live] (file + line), then re-run `python tools/delegate.py check docs/progress/oc_U-ER2.md`.

## CLOSES?

NO — blocking fact: pass vector (pass+0x98 end cursor, pass+0xA0 capacity bound, 0x18 element stride) is proven [V], but desc+0x00 and desc+0x10 field meanings are still '-' (no instruction or string shows them), no tag-9 producer via builder slot 0x378 is located, and no consumer of the pass+0x98 vector is located. Static analysis is exhausted (six angles above, all failed). Waiting on live capture oc_u_er2 at visitor 0x6646980: its desc bytes can confirm field sizes/values and its ret= can name the producer caller chain; after the result arrives, decode the bytes, update this table with any [V live] meaning, re-run the delegate check, and set CLOSES? YES only if every pending part is proven by [V] rows.

## TOOL REQUESTS

CAPTURE BLOCKED oc_u_er2 (4 pending in the shared queue; retry `add` next unit)
oc_u_er2 | python tools/livecap/request.py add oc_u_er2 0x6646980 --size 0x100 --max 6 --why "R2: BlockChanges tag-9 desc fields desc+0x00/+0x10 meanings; caller chain (ret=) of visitor 0x6646980" | blocked by the 4-pending limit; visitor-entry capture of the tag-9 BlockChanges case would give desc bytes for desc+0x00/+0x10 field sizes/values [V live] and ret= caller RVA for the producer insert call site; nothing static could name either.
