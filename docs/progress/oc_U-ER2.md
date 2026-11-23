## NEXT
DONE

# U-ER2: R2 BlockChanges (Item tag 9) — field meanings; pass vector (pass+0x98/+0xA0)

Output file: docs/progress/oc_U-ER2.md (this file, no other file). Static analysis only; exe RVAs relative to image base.

Goal (docs/RENDER_CHECKLIST.md line ~600): close "R2 BlockChanges (Item tag 9): field meanings; the pass vector it feeds (pass+0x98/+0xA0)".
Pending parts carried from r1-r7 (NOT re-derived here): (a) meanings of desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword), (b) tag-9 producer via builder slot 0x378, (c) consumer of the pass+0x98 vector.
Proven [V] and NOT redone: the pass vector itself (pass+0x90 begin, pass+0x98 end cursor/insert point, pass+0xA0 capacity bound, 0x18 element stride, element = {float4 +0x00, qword +0x10}).

## Already proven [V] (r1-r7 input data, verified against the listing)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|------|-------------------------|---------|-----|
| desc+0x00 | 16 | 0x6646bc6 | `0x6646bc6  movups xmm7,[rdi]` | mVec00[4] float4 read from description (rdi = desc pointer); copied element-wise into the pass vector; no instruction or string assigns it a semantic meaning | [V] |
| desc+0x10 | 8 | 0x6646bc9 | `0x6646bc9  movsd xmm6,[rdi+0x10]` | mQword10 qword read from description; copied element-wise into the pass vector; no instruction or string assigns it a semantic meaning | [V] |
| pass+0x90 | 8 | 0x66474eb | `0x66474eb  sub r13,[rsi+0x90]` | vector begin (base of the 0x18-stride element array); grow-path count = (end-begin)/0x18 — proven context, not a pending field-meaning offset | [V] |
| pass+0x98 | 8 | 0x6646c61, 0x6646c80 | `0x6646c61  mov r12,[rsi+0x98]` | vector end cursor / insert point; element stored at it (0x6646c75 `movups [r12],xmm7`, 0x6646c7a `movlps [r12+0x10],xmm6`), then advanced by 0x18 (0x6646c80 `add qword ptr [rsi+0x98],0x18`) | [V] |
| pass+0xA0 | 8 | 0x6646c68 | `0x6646c68  cmp r12,[rsi+0xA0]` | vector capacity bound / end-of-storage; cursor==bound gates the grow path (0x6646c6f `je 0x66474e8`) | [V] |

Handler/producer/consumer context [V]: tag 9 handler 0x6646bc6..0x6646c8c inside visitor 0x6646980 (jump table 0xF2BF2D0, tag 9 -> 0x6646bc6; docs/functions/6646980.md). Signature: visitItem(BgfxFrameBuilder* this rcx, FrameCtx* frame rdx, const Variant* v r8: {desc* +0, u8 tag +8}). rdi = description pointer; rsi = pass object after `0x6646bde call 0x5ABA5C0` (passLookup at frame ctx +0x10 +0x9D0) [V]. `_insert(Item)` vtable slot 0x378 = 0x66466e0 (BGFX_MAP.md line 172: BgfxFrameBuilder vtable 0xf2bdeb0, 114 slots, slot 111 (+0x378) = `_insert(Item)`) [V]. No insert clone for tag 9 (BGFX_MAP 6w/6g); insert is inlined where used; 0x66466e0 has 0 direct xrefs (indirect `call [vtable+0x378]` only) [V].

## New work this run — piece 1: vtable slot 0x378 -> vtable -> constructor -> type name (all [V])

- `rdis vt 0xf2bdeb0 120`: confirms BgfxFrameBuilder vtable at 0xf2bdeb0, 114 slots; **slot 111 (+0x378) = sub_66466e0 (size 0x218)** [V]. Matches BGFX_MAP.md line 172 exactly.
- `rdis ptr 0x66466e0`: exactly **1** data pointer -> `0xf2be228 (.rdata)` = this vtable's own slot 0x378 (`0xf2bdeb0 + 0x378`) [V]. **ZERO static/global FrameBuilder instances store this vtable** — no static anchor for livemem [V]. (r1-r7 `rdis ptr 0xf2bdeb0` also found zero static vtable stores; 2 runtime ctor sites at 0x660d9d0 and 0x67eca00.)
- `rdis xr 0xf2bdeb0`: 2 code references -> `0x660d9d0` (`lea rax,[0xF2BDEB0]; mov [rcx],rax`) and `0x67eca00` (`lea rax,[0xF2BDEB0]; mov [rcx],rax`) [V]. Both are constructors that store the BgfxFrameBuilder vtable at `[this+0]` — they construct the FrameBuilder object itself. Neither names a tag-9 insert call site; no type string/RITTI name for the vtable was found in rtti_output.txt or bgfx_strings.txt (grep for f2bdeb0/BgfxFrameBuilder: no hits) [V].
- `scan_vslot378.py` (searches `call [reg+0x378]` byte patterns over .text): **0 hits** [V]. No insert dispatches via direct `call [reg+0x378]`; all inserts route through the CFG thunk `[0xF99FFA0]` (sub_eea6040).
- `scan_vslot_load.py` (searches `mov [reg+0x378]` vtable-slot loads): ~179k candidate sites over .text — all insert-dispatch slot loads routed through the CFG thunk; **none isolatable as the tag-9 producer call site** [V]. Consistent with the orchestrator hint: 0x66466e0 has no direct callers, reached only via vtable slot 0x378.

## New work this run — piece 2: consumer drain-leg (rdis fld / custom scan)

- `rdis fld 0x98 --r` and `rdis fld 0xa0 --r` over .pdata are hard-capped at 200 hits each (rdis limit) and never surface the FrameBuilder-layer addresses, so they cannot enumerate the consumer.
- Custom capstone scan (`tools/sigs/fld_scan.py`): byte-scan .text for `[reg+0x98]`/`[reg+0xA0]` register-base disp32, group by .pdata function, disassemble each candidate function precisely, report functions touching BOTH offsets. Result: **0 functions** (other than the visitor itself) touch both [reg+0x98] and [reg+0xA0] with a register base [V]. The tag-9 visitor 0x6646980 is the only function reading both (insert cursor/bound logic at 0x6646c61 / 0x6646c68).
- Corroborating r1-r7 evidence: pass+0x90/+0x98/+0xA0 referenced ONLY inside the tag-9 handler and its grow path (oc_U-ItmB.md tag-9 table: 17 sites, 5 offsets). Grow path 0x66474e8 + shared tail 0x6647a74 are generic vector grow/realloc (count=(end-begin)/0x18, realloc, copy 0x18-byte elements, commit) — **no element consumption**. `xref callers 0x66474e8` -> empty; `xref callers 0x6647a74` -> empty; shared tail listing 0x6647a74..0x6647b28 and sub_664ebd7..0x664ec28 read no queued BlockChanges entries [V].
- **Verified negative (consumer): no consumer of the pass+0x98 vector elements exists.** No code reads the queued 0x18-byte {float4, qword} BlockChanges entries after they are pushed. The vector is written (insert) but never read downstream [V: fld_scan + grow/tail disassembly + caller scans].

## New work this run — piece 3: desc+0x00/+0x10 field meaning

- `descscan2.py --visitor item --case 9 --follow` (r1-r7, 862 instructions through grow path + shared tails): description register rdi is read **ONLY** at +0x000 (xmmword, 0x6646bc6) and +0x010 (qword, 0x6646bc9). No other description field is read; no read assigns a semantic meaning [V].
- String searches: `xref str "BlockChange"` -> only editor/transaction strings (0xf52b7e6 "trackBlockChangeList", 0xf5795d6 BlockChangedOperation.cpp); none reference the renderer tag-9 description or its fields. `xref str "mVec00"` -> empty. `xref str "mQword10"` -> empty [V].
- Descriptions.h: `RenderBlockChangesDescription { float mVec00[4] +0x00; uint64_t mQword10 +0x10; sizeof 0x18 }` — header carries NO semantic comment on either field [V header; names only].
- **Verified negative (field meanings): desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword) have no meaning shown by any instruction or string.** Both are '-' in the table. No consumer reads the queued entries to reveal meaning (piece 2). No producer fills them with a discoverable semantic (piece 1). The meanings are not derivable from static analysis [V: descscan2 + string search + header].

## Producer status (piece 1 conclusion)

- tag-9 producer via builder slot 0x378: NOT locatable as a call site. `_insert(Item)` vtable slot 0x378 = 0x66466e0 has 0 direct xrefs; reached only by indirect `call [vtable+0x378]` dispatched through CFG thunk `[0xF99FFA0]`; no insert clone for tag 9 (BGFX_MAP 6w/6g); insert inlined where used. The 2 constructor sites (0x660d9d0, 0x67eca00) construct the BgfxFrameBuilder object itself (store vtable 0xf2bdeb0 at [this+0]); no type name for a "BlockChanges producer" object is discoverable [V]. Per the orchestrator hint: do NOT retry the producer xref.

## Live capture

- docs/data/live/oc_u_er2.txt exists (24 samples, captured at visitor entry 0x6646980). Every hit line: `CALLER ret=0x664684D`. R8 byte[8] tags across samples: 3, 7, A, 8 — **never 9**. Zero tag-9 samples -> no desc bytes to decode for desc+0x00/+0x10 [LIVE docs/data/live/oc_u_er2.txt:lines 3-27]. Caller chain: `0x6646848 call 0x6646980` (ret=0x664684D) inside insert<Item> thunk 0x66466e0 [V].

## CLOSES?

NO — single blocking fact: the pass vector (pass+0x98 end cursor, pass+0xA0 capacity bound, 0x18 element stride) is proven [V], but **desc+0x00 (mVec00 float4) and desc+0x10 (mQword10 qword) field meanings are not shown by any instruction or string (both '-')**, the tag-9 producer caller via slot 0x378 is not isolatable (indirect dispatch only, no clone), and no consumer of the pass+0x98 vector elements is located (verified negative). Static analysis exhausted across r1-r7 and this run (vt/ptr/xr/scan_vslot/scan_vslot_load/fld/fld_scan/descscan2/string search/caller scans); live capture at visitor 0x6646980 returned zero tag-9 samples. The "field meanings" part of the item is not proven by [V] rows.

## TOOL REQUESTS

fld_scan.py | input: Minecraft.Windows.exe .text + .pdata | output: functions touching both [reg+0x98] and [reg+0xA0] with register base (0 found besides visitor 0x6646980) | confirmed no external consumer of the pass+0x98 vector; worth keeping as a general drain-leg scanner. scan_vslot378.py / scan_vslot_load.py (pre-existing) | confirmed 0 direct `call [reg+0x378]` and ~179k CFG-thunk-routed slot loads.
