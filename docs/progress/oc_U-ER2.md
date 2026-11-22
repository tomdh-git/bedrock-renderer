## NEXT
DONE

# U-ER2: R2 BlockChanges (Item tag 9) — field meanings; pass vector (pass+0x98/+0xA0)

Goal (from docs/RENDER_CHECKLIST.md line ~600): close "R2 BlockChanges (Item tag 9): field meanings; the pass vector it feeds (pass+0x98/+0xA0)". Do only the pending parts: field meanings of the description fields, and the pass vector at pass+0x98/+0xA0.

Provenance (all read from input data, not re-derived):
- Visitor 0x6646980, jump table 0xF2BF2D0, tag 9 -> case/handler 0x6646bc6 (extent 0x6646bc6..0x6646c8c, next handler tag 2 at 0x6646c8d). Listing: docs/progress/oc_U-E1c.md "### Tag 9: BlockChanges handler at 0x6646bc6". Description pointer in rdi; rsi = pass object after `0x6646be3 mov rsi,rax`; frame context at rbp+0x8A0.
- Pass-vector grow/tail sites: docs/progress/oc_U-ItmB.md "## tag 9 BlockChanges (head 0x6646bc6, reg rsi, 17 sites -> 5 offsets)".
- BGFX_MAP 6ih: "BlockChanges ... copies 0x18 bytes into the pass vector at +0x98 (0x18-byte elements): vec4 +0x00, qword +0x10, size 0x18 [I]". This unit upgrades that to [V].
- src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h: RenderBlockChangesDescription { float mVec00[4] +0x00; uint64_t mQword10 +0x10; }; static_assert sizeof == 0x18, offsetof mQword10 == 0x10. The header carries no semantic comment on either field.
- Live data (docs/data/live/item_visitor.txt): no tag-9 capture, so no live payload to cross-check.

## Field meaning table (one row per distinct offset; all sites listed)

| offset | size | name | read/store address | verbatim `0xRVA  instr` | meaning | tag |
| desc+0x00 | 16 | mVec00[4] (float4) | read at 0x6646bc6 (rdi = description); stored into the vector slot at 0x6646c75 `movups [r12],xmm7` where r12 = current pass+0x98 | `0x6646bc6  movups xmm7,[rdi]` | - (no instruction or string gives it a meaning) | [V] |
| desc+0x10 | 8 | mQword10 (qword) | read at 0x6646bc9; stored at 0x6646c7a `movlps [r12+0x10],xmm6` | `0x6646bc9  movsd xmm6,[rdi+0x10]` | - (no instruction or string gives it a meaning) | [V] |
| pass+0x98 | 8 | pass vector end cursor (insert point) | read 0x6646c61 `mov r12,[rsi+0x98]` (r12 = insert destination); advanced by 0x6646c80 `add qword ptr [rsi+0x98],0x18` (element stride 0x18); grow-path sites 0x66478a2, 0x6647917, 0x6647a56, 0x6647a97 | `0x6646c61  mov r12,[rsi+0x98]` | vector end cursor: the float4 is stored at it (0x6646c75), the qword at +0x10 (0x6646c7a), then the cursor is advanced by 0x18 (element stride) | [V] |
| pass+0xA0 | 8 | pass vector end-of-storage (capacity bound) | 0x6646c68 `cmp r12,[rsi+0xA0]` (cursor == bound -> vector full -> grow path at 0x66474e8); grow-path sites 0x6647a13, 0x6647a65 | `0x6646c68  cmp r12,[rsi+0xA0]` | vector capacity bound; the begin==end full test at 0x6646c68 gates allocation+copy at 0x66474e8 | [V] |
| pass+0x90 | 8 (dword at 0x6647a9d) | pass vector field touched by the grow path | 0x66474eb `sub r13,[rsi+0x90]`; 0x664789b; 0x6647a07; 0x6647a47 (stores rdi); 0x6647a9d (dword sub of [rsi+0x90]) | `0x66474eb  sub r13,[rsi+0x90]` | - (touched only by the grow path; no instruction shows its role) | [V] |

## What the handler proves (tag 9, rdi = description, rsi = pass)

- Pass object from `0x6646bde call 0x5ABA5C0` with rcx = frame_context+0x10+0x9D0 (passLookup at frame ctx +0x10, key 0x9D0); result in rax -> rsi.
- `0x6646c61 mov r12,[rsi+0x98]` loads vector end into r12; `0x6646c68 cmp r12,[rsi+0xA0]` compares with vector end-of-storage; `0x6646c6f je 0x66474E8` goes to the grow path when full.
- Element store: `0x6646c75 movups [r12],xmm7` (desc +0x00 float4), `0x6646c7a movlps [r12+0x10],xmm6` (desc +0x10 qword), `0x6646c80 add qword ptr [rsi+0x98],0x18` advances the cursor by the 0x18 element stride. Each queued element = one RenderBlockChangesDescription (float4 + qword, 0x18 bytes).
- Grow path at 0x66474E8: `0x6646c56 mov dl,0x4A` then `0x6646c58 call qword ptr [0xF99FFA0]` (sub_eea6040 allocator), then 0x66474e8 region reallocation/copy (sites above), shared tail at 0x6647A74.

## Pending: field meanings

Neither description field has a meaning shown by any instruction or string:
- desc+0x00 mVec00[4] (float4): only copied element-wise into the pass vector. Meaning '-'.
- desc+0x10 mQword10 (qword): only copied element-wise into the pass vector. Meaning '-'.

Header names (mVec00/mQword10) come from Descriptions.h only; no semantic comment exists there either. No tag-9 producer: no insert clone through FrameBuilder slot 0x378 for BlockChanges (docs/progress/descriptions.md, oc_U-ItmB.md), so the producer that fills +0x00/+0x10 is not located, and no consumer of the pass+0x98 vector is located either. Therefore field meanings stay undecoded.

CLOSES?: NO — blocking fact: the pass vector (pass+0x98 end cursor, pass+0xA0 capacity bound, 0x18 element stride) is proven [V], but the field meanings of desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword) are not shown by any instruction or string, no tag-9 producer exists through builder slot 0x378, and no consumer of the pass+0x98 vector is located — so the meanings remain '-' and the item's "field meanings" part is not proven by [V] rows.

## TOOL REQUESTS
None
