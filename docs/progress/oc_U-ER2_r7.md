## NEXT
DONE

# U-ER2: R2 BlockChanges (Item tag 9) — field meanings; pass vector (pass+0x98/+0xA0)

GOAL (docs/RENDER_CHECKLIST.md line ~600): close "R2 BlockChanges (Item tag 9): field meanings; the pass vector it feeds (pass+0x98/+0xA0)". Pending parts (carried from r1-r6, NOT repeated): meanings of desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword), the tag-9 producer via builder slot 0x378, and the consumer of the pass+0x98 vector. The pass vector itself (pass+0x90 begin, pass+0x98 end cursor, pass+0xA0 capacity bound, 0x18 element stride) is already proven [V].

## Already proven [V] (r1-r6 input data; verified against the listing; not re-derived here)

- Tag 9 handler 0x6646bc6..0x6646c88 inside visitor 0x6646980 (jump table 0xF2BF2D0, tag 9 -> 0x6646bc6; docs/functions/6646980.md). Signature: visitItem(BgfxFrameBuilder* this rcx, FrameCtx* frame rdx, const Variant* v r8: {desc* +0, u8 tag +8}) [V]. rdi = description pointer; rsi = pass object after `0x6646bde call 0x5ABA5C0` (passLookup at frame ctx +0x10 +0x9D0) [V].
- `0x6646bc6  movups xmm7,[rdi]` reads desc+0x00 (16-byte float4); `0x6646bc9  movsd xmm6,[rdi+0x10]` reads desc+0x10 (qword). Descriptions.h: RenderBlockChangesDescription { float mVec00[4] +0x00; uint64_t mQword10 +0x10; sizeof 0x18 } — header carries NO semantic comment on either field [V header; field names from header only, not semantics].
- `0x6646c61  mov r12,[rsi+0x98]` loads pass+0x98 = vector end cursor (insert point); `0x6646c68  cmp r12,[rsi+0xA0]` compares with pass+0xA0 = end-of-storage / capacity bound; `0x6646c6f  je 0x66474e8` branches to grow path when full [V].
- `0x6646c75  movups [r12],xmm7` stores desc+0x00 at vector end; `0x6646c7a  movlps [r12+0x10],xmm6` stores desc+0x10 at vector end+0x10; `0x6646c80  add qword ptr [rsi+0x98],0x18` advances cursor by 0x18 element stride; `0x6646c88  jmp 0x6647A74` shared tail [V]. Element = 0x18 bytes {float4, qword}.
- `0x66474e8  mov r13,r12`; `0x66474eb  sub r13,[rsi+0x90]` → pass+0x90 = vector begin; grow path computes element count = (end-begin)/0x18, reallocs, copies 0x18-byte elements, commits at shared tail 0x6647a74 [V].
- No insert clone for tag 9 (BGFX_MAP 6w/6g); `_insert(Item)` vtable slot 0x378 = 0x66466e0 has 0 direct xrefs (indirect `call [vtable+0x378]` only); `rdis ptr 0xf2bdeb0` finds zero static vtable stores → no static FrameBuilder anchor [V].

## New static angles tried this run (all exhausted, none succeeded)

- **Live capture parsed** (docs/data/live/oc_u_er2.txt, 24 samples, captured at visitor entry 0x6646980): R8 byte[8] tags across samples = 3, 7, A, 8 — **never 9**. Zero tag-9 samples → no desc bytes to decode for tag-9 desc+0x00/+0x10 [LIVE docs/data/live/oc_u_er2.txt:lines 3-27].
- **Visitor call site named**: `0x6646848  call 0x6646980` inside insert<Item> thunk 0x66466e0 (vtable slot 0x378), ret=0x664684D [V live]. Every capture hit line: `CALLER ret=0x664684D`. But 0x66466e0 itself has 0 direct xrefs → the function that calls insert<Item>(tag=9) cannot be named statically [V: xref.py callers 0x66466e0 → empty]. xref.py callers 0x6646848 → empty (no callers for that specific call site address).
- **Shared tail 0x6647A74 checked**: reads pass+0x98/pass+0x90 only for vector grow bookkeeping (element count = (end-begin)/0x18 via `shr eax,3` + `imul eax,0xFFFFAAAB` magic divide by 3; then `dec eax`), calls `sub_eec6ec0` for commit. sub_664EBd7 = pure register restore + ret. **No consumer of pass+0x98 vector elements found** — no reader of the queued {float4,qword} BlockChanges entries downstream [V: listing 0x6647A74..0x6647B28 and 0x664EBd7..0x664EC28].
- **xref.py callers 0x66474e8 → empty** (no direct callers of grow path); **xref.py callers 0x6647a74 → empty** (no direct callers of shared tail).
- **String search**: xref.py str "BlockChange" → only editor/transaction strings (0xf52b7e6 "trackBlockChangeList", 0xf5795d6 BlockChangedOperation.cpp) — none reference the renderer tag-9 description or its fields. xref.py str "mVec00" → empty. xref.py str "mQword10" → empty.

## What was tried that failed (documented per instructions)

1. Live capture at visitor 0x6646980 → zero tag-9 samples in 24 hits; cannot decode desc field values.
2. xref callers on insert thunk 0x66466e0 → 0 direct xrefs; producer caller not nameable.
3. xref callers on grow path 0x66474e8 and shared tail 0x6647a74 → 0 direct xrefs each.
4. String search for "BlockChange", "mVec00", "mQword10" → no renderer-relevant hits.
5. Listing-based search for pass+0x98/pass+0x90 reads outside visitor → none found in reachable listing.

## Field-meaning table (one row per distinct offset, every site listed; meaning '-' unless an instruction/string shows it)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| desc+0x00 | 16 | 0x6646bc6 | `0x6646bc6  movups xmm7,[rdi]` | - (mVec00[4] float4; copied element-wise into the pass vector; no instruction or string assigns it a meaning) | [V] |
| desc+0x10 | 8 | 0x6646bc9 | `0x6646bc9  movsd xmm6,[rdi+0x10]` | - (mQword10 qword; copied element-wise into the pass vector; no instruction or string assigns it a meaning) | [V] |
| pass+0x98 | 8 | 0x6646c61, 0x6646c80 | `0x6646c61  mov r12,[rsi+0x98]` | vector end cursor / insert point; element stored at it (0x6646c75 `movups [r12],xmm7`, 0x6646c7a `movlps [r12+0x10],xmm6`), then advanced by 0x18 (0x6646c80 `add qword ptr [rsi+0x98],0x18`) | [V] |
| pass+0xA0 | 8 | 0x6646c68 | `0x6646c68  cmp r12,[rsi+0xA0]` | vector capacity bound / end-of-storage; cursor==bound gates the grow path (0x6646c6f `je 0x66474e8`) | [V] |
| pass+0x90 | 8 | 0x66474eb | `0x66474eb  sub r13,[rsi+0x90]` | vector begin (base of the 0x18-stride element array); grow-path count = (end-begin)/0x18 — proven context, not a pending field-meaning offset | [V] |

## Live capture (read-only; orchestrated — the game is not touched by this unit)

- docs/data/live/oc_u_er2.txt exists (24 samples), captured at visitor entry 0x6646980, kind=regs, size=0x100. Every hit line: `CALLER ret=0x664684D`. R8 byte[8] tags across samples: 3, 7, A, 8 — never 9. Zero tag-9 samples → desc+0x00/+0x10 field values cannot be confirmed from live data [LIVE docs/data/live/oc_u_er2.txt:lines 3-27].
- Caller chain: `0x6646848  call 0x6646980` (ret=0x664684D) inside insert<Item> thunk 0x66466e0 (vtable slot 0x378) [V: listing at 0x6646848 + ret match from capture]. 0x66466e0 has 0 direct xrefs → producer caller not statically nameable [V: xref.py callers 0x66466e0 → empty].

## CLOSES?

NO — three blocking facts remain unproven and cannot be resolved with available static + live data:

1. **desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword) field meanings**: no instruction or string assigns them a meaning; live capture had zero tag-9 samples so no desc bytes to decode [LIVE docs/data/live/oc_u_er2.txt:lines 3-27].

2. **Tag-9 producer via builder slot 0x378**: insert<Item> thunk 0x66466e0 has 0 direct xrefs; only indirect `call [vtable+0x378]`; caller function not nameable [V: xref.py callers 0x66466e0 → empty; xref.py callers 0x6646848 → empty].

3. **Consumer of pass+0x98 vector elements**: shared tail 0x6647A74 and sub_664EBd7 checked — neither reads queued BlockChanges entries; xref callers on both returned empty; no reader of pass+0x98 vector elements found anywhere [V: listing 0x6647A74..0x6647B28 and 0x664EBd7..0x664EC28].

Single blocking fact (consolidated): desc+0x00/+0x10 field meanings, tag-9 producer caller, and pass+0x98 vector consumer are all unknown; live capture at visitor 0x6646980 returned zero tag-9 samples. All static angles exhausted (8+ angles tried across r1-r6 and this run).

## TOOL REQUESTS

CAPTURE DONE oc_u_er2 | docs/data/live/oc_u_er2.txt (24 samples, captured at 0x6646980) | zero tag-9 samples — cannot confirm desc field meanings or producer from live data; no new capture requested unless orchestrator adds a tag-9-triggering target.
