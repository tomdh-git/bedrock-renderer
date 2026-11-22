## NEXT
DONE

# U-ER2: R2 BlockChanges (Item tag 9) — field meanings; pass vector (pass+0x98/+0xA0)

Goal (docs/RENDER_CHECKLIST.md line ~600): close "R2 BlockChanges (Item tag 9): field meanings; the pass vector it feeds (pass+0x98/+0xA0)". Do ONLY the pending parts: field meanings of desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword), plus locating the tag-9 producer and the consumer of the pass+0x98 vector.

## Input data (read fully, not re-derived)

- docs/progress/oc_U-E1c.md: tag-9 handler listing at 0x6646bc6..0x6646c8c (17 instructions). Visitor 0x6646980 jump table 0xf2bf2d0 (tag 9 -> 0x6646bc6). Entry: rdi = description pointer (variant payload), rsi = pass object after `0x6646be3 mov rsi,rax`, rbp+0x8A0 = frame context. Descriptions.h: RenderBlockChangesDescription { float mVec00[4] +0x00; uint64_t mQword10 +0x10; sizeof 0x18 }. Header carries NO semantic comment on either field.
- docs/progress/oc_U-ItmB.md: tag-9 read table over pass reg rsi: offsets 0x90/0x98/0xA0/8/0x10, all 17 sites. pass+0x98 cursor/end and pass+0xA0 bound proven [V]; grow path at 0x66474e8..0x6647a74, shared tail 0x6647a74.
- docs/BGFX_MAP.md 6bg: RenderMark::passLookup = 0x5ABA5C0 returns pass object whose first member is the item vector; same lookup used by tag 9 via `ctx[+0x10] + 0x9D0`. 6w: Item group tag 9 = BlockChanges; NO insert clone exists for tag 9 in the clone table (6g/6w) — the insert is inlined where used, producer not located. No live capture for tag 9 (docs/data/live/item_visitor.txt).

## Proven already [V] (NOT redone)

- pass+0x98 = vector end cursor (insert point): `0x6646c61 mov r12,[rsi+0x98]`; advanced `0x6646c80 add qword ptr [rsi+0x98],0x18` (stride 0x18); grow-path sites 0x66478a2/0x6647917/0x6647a56/0x6647a97.
- pass+0xA0 = vector end-of-storage / capacity bound: `0x6646c68 cmp r12,[rsi+0xA0]`; `0x6646c6f je 0x66474e8` -> grow path; grow sites 0x6647a13/0x6647a65.
- Element = 0x18 bytes: `0x6646c75 movups [r12],xmm7` (desc +0x00 float4) + `0x6646c7a movlps [r12+0x10],xmm6` (desc +0x10 qword), cursor advanced by 0x18.

## Field-meaning table (pending offsets only; every site listed; meaning '-' where no instruction/string assigns it)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|------|-------------------------|---------|-----|
| desc+0x00 | 16 | 0x6646bc6, 0x6647890 | `0x6646bc6  movups xmm7,[rdi]` | - (no instruction or string assigns a meaning; only copied element-wise into the pass vector; grow path re-stores the same 16 bytes at `0x6647890 movups [rdi+r13],xmm7`) | [V] |
| desc+0x10 | 8 | 0x6646bc9, 0x6647895 | `0x6646bc9  movsd xmm6,[rdi+0x10]` | - (no instruction or string assigns a meaning; only copied element-wise into the pass vector; grow path re-stores the same qword at `0x6647895 movlps [rdi+r13+0x10],xmm6`) | [V] |
| pass+0x90 | 8 | 0x66474eb, 0x664789b, 0x6647a07, 0x6647a47, 0x6647a9d | `0x66474eb  sub r13,[rsi+0x90]` | vector begin (base of the 0x18-stride element array); already-proven context for the pass vector, not part of the pending field-meaning question | [V] |

## New angles tried (all failed — do not repeat)

1. `python tools/sigs/xref.py str "BlockChanges"` -> no output: no string "BlockChanges" exists in the exe, so no producer/consumer is reachable via a name string.
2. `python tools/sigs/xref.py callers 0x5ABA5C0` (passLookup) -> long list of pass consumers (0x66232b0, 0x6646980, 0x66ea3d0, ...); none is the BlockChanges producer, and the tag-9 insert has no dedicated caller because it has no insert clone (inlined, dispatched through the CFG thunk [0xF99FFA0]).
3. `python tools/sigs/descscan2.py --visitor item --case 9 --follow` -> followed 862 instructions through grow path + shared tails; the description register (rdi) is read ONLY at +0x000 (xmmword) and +0x010 (qword). No other description field is read, and no read assigns a semantic meaning.
4. Disassembled grow path 0x66474e8 and shared tail 0x6647a74: generic vector grow/realloc (computes count `(end-begin)/0x18`, allocates, copies 0x18-byte elements, commits) plus a separate 0xC8-stride vector at pass+8/+0x10. Neither consumes the stored element for any recognizable purpose; no field meaning is revealed.
5. `rdis vt 0xf2bdeb0`, `rdis class 0xf2bdeb0`, `rdis ptr 0xf2bdeb0` (BgfxFrameBuilder vtable): class shows 2 ctor sites (0x660d9d0, 0x67eca07) that set the vtable at runtime on a heap instance; `ptr` finds ZERO static data locations storing the vtable, so there is NO static/global FrameBuilder instance address to anchor a livemem chain to pass objects. livemem cannot scan, so pass objects (and their vector contents) cannot be located in live memory without an anchor.
6. Whole-.text capstone scan for a `{16-byte store, then qword store at +0x10}` description-construction pattern: capstone disassembly truncated in this environment (not reliable); even if it worked, tracing desc+0x00/+0x10 values upstream to a semantic meaning would still be required.

## Pending: producer and consumer

- tag-9 producer via builder slot 0x378: NOT located. No insert clone for RenderBlockChangesDescription exists (6g/6w clone table omits tag 9); the insert is inlined at its call site, and all inserts route through the CFG thunk [0xF99FFA0] so xref callers cannot isolate the tag-9 call site. descscan2 confirms the handler only *reads* desc+0x00/+0x10; nothing in the exe shows what fills them.
- consumer of the pass+0x98 vector: NOT located. pass+0x90/+0x98/+0xA0 are referenced only inside the tag-9 handler and its grow path (oc_U-ItmB.md); no code reads the vector elements (the 0x18-byte {float4, qword} records) after they are pushed.

## CLOSES?

NO — blocking fact: the pass vector (pass+0x98 end cursor, pass+0xA0 capacity bound, 0x18 element stride) is already proven [V], but the field meanings of desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword) are not shown by any instruction or string (both '-', [V] for the read only), no tag-9 producer via builder slot 0x378 exists in the clone table / is located, and no consumer of the pass+0x98 vector is located. So the "field meanings" part of the item is not proven by [V] rows.

## TOOL REQUESTS

None
