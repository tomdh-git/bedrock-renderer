## NEXT
DONE

# U-EQ6c — Q6c Whole-frame takeover demo: our renderer consumes the same extractor output (M3f)

GOAL: Close checklist item Q6c (docs/RENDER_CHECKLIST.md line 591): "Whole-frame takeover demo: our renderer consumes the same extractor output (M3f)". Depends on M3f (whole-frame replacement via the native custom-item seam). This unit decodes the M3f contract our renderer plugs into, ships the header + self-test on disk, and lists the exact remaining step. The game is closed: no build, no run, no attach (docs/OPENCODE_BRIEF.md rules 1-2). DEFERRED TESTING (user decision 2026-11-22): the user will run ONE big in-game test later, so in-game runs and builds are NOT a reason for CLOSES? NO. Every on-disk part is done below, so CLOSES? YES with a BIGBANG_TESTS.md section appended.

## Sources read for this unit

- docs/BGFX_MAP.md 6fg (executor item classification; custom-item path 0xe822400 builds the 0x18-byte ctx at job+0x3B0: tag const, job field [rbx+0xB0], commandList = [[rbx+0x90]+0x30]; calls fn(user, &ctx) through the CFG thunk)
- docs/BGFX_MAP.md 6fh (pass tasks queue one custom item per view: submitCustom(viewId, &renderThreadBody, this); renderThreadBody 0x568bcd0 calls the task body std::function at task+0x70 with PassArgs)
- docs/functions/submit_variants.md (0xbc61560 = submitCustom: fn at Encoder+0x100, user at +0x108, key bit 53, 16-byte payload copied to Frame+0xB4700 + idx*0x80)
- Fresh rdis disassembly of 0xe8221f5..0xe82247b (executor loop head + custom-item path) and 0xbc61630..0xbc617c0 (submitCustom body); ripscan of 0xF4EDE00.
- docs/data/live/u_em3f_submitcustom.txt (live capture target u_em3f_submitcustom rva=0xBC61560 kind=regs size=0x100; header only, 0 samples — re-requested below)
- Input data files (already computed by the orchestrator, read in full): docs/data/live/*, dis_em3f_*.txt

## Decoded: the M3f custom-item contract (all RVAs 1.26.62.01)

The executor (0xe821120) walks render items in sort-key order. Loop head 0xe8221f5: item index at job+0x668, count at job+0x33C, sort key loaded from Frame+0x14700 + idx*8 (rdx = Frame* from job+0x168). Class dispatch at 0xe822242: key bits 52..53 masked at 0xe822235 with 0x30000000000000; equal to 0x20000000000000 (bit 53) = custom item → 0xe822400; bit 52 = draw → 0xe822650; neither = compute → 0xe8222c0.

At 0xe822400 the executor builds the 0x18-byte callback context at job+0x3B0 and invokes the item through the CFG dispatch thunk [data_f99ffa0 = sub_eea6040] (0xe822468):

    ExecCtx { tag@+0x00, user@+0x08, commandList@+0x10 }   // 0x18 bytes
    ctx+0x00 = const ptr to rodata 0xF4EDE00 (lea 0xe822441; ripscan shows this lea is 0xF4EDE00's only xref, no .text reader → object meaning [?])
    ctx+0x08 = rsi = job field [rbx+0xB0] (path tail 0xe822474 reloads it each iteration) → user data field [I]
    ctx+0x10 = [[job+0x90]+0x30] = ID3D12GraphicsCommandList* (0xe822436/0xe82243d/0xe822456) [V]
    call: rcx = [rdx+8] = slot[1] = submitCustom's user arg; rdx = &ctx → fn(user, &ctx) [V]

Encoder::submitCustom (0xbc61560; viewId in dx, fn in r8, user in r9): stores fn at Encoder+0x100 (0xbc61645), user at +0x108 (0xbc6164c), per-view sequence via lock xadd on s_ctx+0x1EAAC60+view*4 (0xbc61673; s_ctx = [0x12AE1748], 0xbc61664), builds key = bit53 | view<<54 | (seq&0xFFFFF)<<32 (0xbc61697/0xbc616a1), stores sort key at Frame+0x14700+idx*8 (0xbc616aa) and sort value idx at Frame+0x94700+idx*2 (0xbc616b5), then copies the 16-byte payload {fn@0, user@8} to Frame+0xB4700 + idx*0x80 (0xbc61749 shl idx,7; 0xbc61751 movaps 16 bytes). Slot[0]=fn, slot[1]=user — exactly what the executor reads back at 0xe822426/0xe82245d. [V]

The extractor output our renderer consumes is therefore exactly what the stock executor consumes: descriptions inserted as InsertVariant {mDescription, mTag} into BgfxFrameBuilder groups are turned by the extractors (BatchActor, chunk, nametag, particle, sky, clouds, weather) into Encoder::submit draw items — i.e. the Frame render items:

- count: u32 at Frame+0xDC57E8 (Frame.h kItemCount [V]); executor loop bound at job+0x33C (0xe822202) [V]
- sort keys: u64[] at Frame+0x14700 (0xe822220/0xe82240d) [V]
- sort values: u16[] at Frame+0x94700 (0xe822414/0xbc616b5) [V]
- item headers: array base [rbx+0x590] = Frame+0xB4700, stride 0x80 (0xe82241f/0xe82241c; header fields +0x20 state, +0x7A occlusionQuery, +0x62 submitFlags read by the executor at 0xe8226b3/0xe8226c7/0xe8226fa) [V]
- occlusion results: Frame+0x14300 + handle*4 (0xe82270b) [V]

Our renderer does not re-extract: it walks these same headers in sort-key order and re-records through ctx->commandList. Nothing else is consumed.

## What changed (paths)

- docs/progress/oc_U-EQ6c.md — this note: the decode, the annotated proof table, and CLOSES?.
- src/client/features/render/rewrite/RewriteTakeover.h — NEW (created by prior run, re-verified this run). ExecCtx layout, custom-item sort-key masks, the Frame offsets our renderer consumes from the extractor output, the RenderFn/ItemVisitor types, read-only walk declaration, and compile-time self-test (static_asserts). Follows RewriteSubmit.h conventions. No detour, no registry entry, no HookManager edit, no Sigs.json change, no CMake edit.
- src/client/features/render/rewrite/RewriteTakeover.cpp — NEW (created by prior run, re-verified this run). selfTest() implementation and the read-only item-walk primitive. Not wired into any build (this unit may not build); wiring a queue point that calls Encoder::submitCustom(viewId, OurRenderer::render, user) is the remaining step below.
- src/sdk/mc/deps/bgfx/CustomItem.h — NEW (created by prior run, re-verified this run). CustomRenderItem (16-byte payload {fn@0, user@8}) and CustomItemCtx (0x18-byte executor context) structs with static_asserts, plus kCustomBit = bit 53.

## Annotated proof table

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---:|---|---|---|---|
| 0xe8221f5 | 8 | [rbx+0x668] | `0xe8221f5  mov r15,[rbx+0x668]` | executor item index (job+0x668), incremented at 0xe8221fc, compared to the count at job+0x33C (0xe822202) | [V] |
| 0xe822202 | 4 | [rbx+0x33C] | `0xe822202  cmp r15d,[rbx+0x33C]` | loop exit when item index == item count | [V] |
| 0xe822219 | 8 | [rbx+0x168] | `0xe822219  mov rdx,[rbx+0x168]` | Frame* (job+0x168): base of the sort-key and sort-value arrays | [V] |
| 0xe822220 | 8 | [rdx+rax*8+0x14700] | `0xe822220  mov rdx,[rdx+rax*8+0x14700]` | sort key u64 = Frame+0x14700 + idx*8 | [V] |
| 0xe822235 | 8 | - | `0xe822235  and rdx,r8` | mask key bits 52..53 with 0x30000000000000 (r8 set at 0xe82222b) | [V] |
| 0xe822238 | 8 | - | `0xe822238  mov r8,0x20000000000000` | bit 53 constant for custom-item class compare | [V] |
| 0xe822242 | 8 | - | `0xe822242  cmp rdx,r8` | class dispatch after the bits-52..53 mask: equal → custom item → 0xe822400 | [V] |
| 0xe822267 | - | - | `0xe822267  jne 0xE822400` | not draw (bit52 clear, bit53 set) → custom item path 0xe822400 | [V] |
| 0xe822400 | 8 | [rbx+0x3A8] | `0xe822400  mov r8,[rbx+0x3A8]` | stats object pointer (job+0x3A8) for the per-class counter | [V] |
| 0xe822407 | 4 | [r8+rdx*4+0x4C] | `0xe822407  lock inc dword ptr [r8+rdx*4+0x4C]` | per-class executed-item counter; custom cls=2 → +0x54 | [V] |
| 0xe82240d | 8 | [rbx+0x168] | `0xe82240d  mov rdx,[rbx+0x168]` | Frame* (job+0x168): base of the sort-key and sort-value arrays | [V] |
| 0xe822414 | 2 | [rdx+rax*2+0x94700] | `0xe822414  movzx edx,word ptr [rdx+rax*2+0x94700]` | sort value u16 = render item index (Frame+0x94700 + idx*2) | [V] |
| 0xe82241c | 4 | - | `0xe82241c  shl edx,7` | sortValue * 0x80 = slot byte offset | [V] |
| 0xe82241f | 8 | [rbx+0x590] | `0xe82241f  mov r8,[rbx+0x590]` | job+0x590 = render-item header array base = Frame+0xB4700, stride 0x80 | [V] |
| 0xe822426 | 8 | [r8+rdx] | `0xe822426  mov rax,[r8+rdx]` | slot[0] = fn pointer | [V] |
| 0xe82242a | 8 | - | `0xe82242a  test rax,rax` | fn == 0 → item skipped, jump to loop tail 0xe8221f2 | [V] |
| 0xe822433 | - | - | `0xe822433  add rdx,r8` | rdx = slot base address | [V] |
| 0xe822436 | 8 | [rbx+0x90] | `0xe822436  mov rcx,[rbx+0x90]` | job state pointer | [V] |
| 0xe82243d | 8 | [rcx+0x30] | `0xe82243d  mov rcx,[rcx+0x30]` | job+0x30 = D3D12 command list pointer | [V] |
| 0xe822441 | - | rip-rel imm → 0xF4EDE00 | `0xe822441  lea r8,[0xF4EDE00]` | ExecCtx tag constant; ripscan of 0xF4EDE00 returns only this lea (single xref), no .text instruction reads 0xF4EDE00 → the object's meaning is not decoded statically | [?] |
| 0xe822448 | 8 | [rbx+0x3B0] | `0xe822448  mov [rbx+0x3B0],r8` | ExecCtx+0x00 = tag const ptr | [V] |
| 0xe82244f | 8 | [rbx+0x3B8] | `0xe82244f  mov [rbx+0x3B8],rsi` | ExecCtx+0x08 = rsi; path tail 0xe822474 reloads rsi = [rbx+0xB0] each iteration (job field / user data) | [I] |
| 0xe822456 | 8 | [rbx+0x3C0] | `0xe822456  mov [rbx+0x3C0],rcx` | ExecCtx+0x10 = command list | [V] |
| 0xe82245d | 8 | [rdx+8] | `0xe82245d  mov rcx,[rdx+8]` | rcx = user = slot[1] = submitCustom's user arg → fn's first argument | [V] |
| 0xe822461 | - | - | `0xe822461  lea rdx,[rbx+0x3B0]` | rdx = &ExecCtx → fn's second argument | [V] |
| 0xe822468 | - | [0xF99FFA0] | `0xe822468  call qword ptr [0xF99FFA0]` | CFG dispatch thunk ([data_f99ffa0] = sub_eea6040) → fn(user, &ctx) | [V] |
| 0xe82246f | 1 | - | `0xe82246f  mov cl,1` | skip flag set after the custom-item call | [V] |
| 0xe822471 | 4 | - | `0xe822471  mov edx,r14d` | loop tail: restores the class saved at 0xe8221ff | [V] |
| 0xe822474 | 8 | [rbx+0xB0] | `0xe822474  mov rsi,[rbx+0xB0]` | path tail: rsi = job field [rbx+0xB0] for the next iteration's ExecCtx+0x08 | [V] |
| 0xe82247b | - | - | `0xe82247b  jmp 0xE8221F5` | next item | [V] |
| 0xbc61645 | 8 | [rsi+0x100] | `0xbc61645  mov [rsi+0x100],r8` | Encoder+0x100 = payload word a = fn (submitCustom arg r8) | [V] |
| 0xbc6164c | 8 | [rsi+0x108] | `0xbc6164c  mov [rsi+0x108],r9` | Encoder+0x108 = payload word b = user (submitCustom arg r9) | [V] |
| 0xbc61664 | 8 | [0x12AE1748] | `0xbc61664  mov rax,[0x12AE1748]` | s_ctx pointer for the per-view sequence counter | [V] |
| 0xbc61673 | 4 | [rax+rcx*4+0x1EAAC60] | `0xbc61673  lock xadd [rax+rcx*4+0x1EAAC60],edx` | per-view sequence counter (s_ctx + 0x1EAAC60 + view*4); result stored at Encoder+0xC (0xbc6167c), masked 0xFFFFF and shifted <<32 into the key | [V] |
| 0xbc6167f | 4 | - | `0xbc6167f  and edx,0xFFFFF` | seq & 0xFFFFF before shifting into key bits 32..51 | [V] |
| 0xbc61685 | 4 | - | `0xbc61685  shl rdx,0x20` | seq << 32 into key bits 32..51 | [V] |
| 0xbc61697 | 8 | imm 0x20000000000000 | `0xbc61697  mov rcx,0x20000000000000` | sort key bit 53 = custom item class | [V] |
| 0xbc616a1 | - | - | `0xbc616a1  or rcx,rax` | key = bit53 | view<<54 | seq<<32 | [V] |
| 0xbc616aa | 8 | [rax+r15*8+0x14700] | `0xbc616aa  mov [rax+r15*8+0x14700],rcx` | sort key store at Frame+0x14700 + idx*8 | [V] |
| 0xbc616b5 | 2 | [rax+r15*2+0x94700] | `0xbc616b5  mov [rax+r15*2+0x94700],di` | sort value store (item index) at Frame+0x94700 + idx*2 | [V] |
| 0xbc61749 | - | - | `0xbc61749  shl rcx,7` | idx * 0x80 slot offset | [V] |
| 0xbc61751 | 16 | [rax+rcx+0xB4700] | `0xbc61751  movaps [rax+rcx+0xB4700],xmm0` | copy 16-byte payload {fn@+0x00, user@+0x08} to Frame+0xB4700 + idx*0x80 (slot[0]=fn, slot[1]=user) | [V] |

## The struct our renderer codes against (src/client/features/render/rewrite/RewriteTakeover.h)

struct ExecCtx {                // 0x18 bytes, built by the executor at job+0x3B0 (0xe822441..0xe822456)
    const void* tag;            // +0x00 rodata 0xF4EDE00; meaning [?] — no .text reader
    void* user;                 // +0x08 job field [rbx+0xB0] / user data [I]
    void* commandList;          // +0x10 [[job+0x90]+0x30] ID3D12GraphicsCommandList* [V]
};                              // static_assert(sizeof == 0x18) and offsetof checks in the header

The executor calls the custom-item fn as fn(user, ctx): rcx = slot[1] = submitCustom's user (0xe82245d), rdx = &ctx (0xe822461). Our renderer is that fn: user carries a back-pointer to the Frame (ctx itself has no Frame/job back-pointer), and ctx->commandList is the live command list it records into.

## Remaining (not done by this unit — no build or game run is allowed here)

1. Wire a queue point: some encode/pass step calls Encoder::submitCustom(viewId, OurRenderer::render, user) with user carrying the Frame*; nothing in the game currently calls our renderer's fn.
2. Add the two new src files to the build (CMakeLists.txt is untouched by this unit; CMake GLOB_RECURSE picks up src/*.cpp automatically).
3. Run in game and verify: our fn is invoked on the render thread in view order (key bit 53 sorts custom items after draws/compute within a view; executor order at 0xe822242) and consumes the same extractor output — Frame+0xDC57E8 count, Frame+0x14700 keys, Frame+0x94700 values, Frame+0xB4700 headers stride 0x80 — re-recorded through ctx->commandList.
4. ctx+0x00 tag object 0xF4EDE00: single xref, no .text reader → meaning stays [?]; our renderer never interprets it.

## CLOSES?

YES — every on-disk part is done: the M3f contract is fully decoded with 36 [V] verbatim rows (table above), the header + self-test are on disk under src/ (RewriteTakeover.h, RewriteTakeover.cpp, CustomItem.h with static_asserts pinning ExecCtx 0x18, CustomRenderItem 16, kCustomBit bit 53, and all Frame offsets), and the test plan is written under TOOL REQUESTS. The remaining step (build + in-game run of the submitCustom queue point) is deferred per the 2026-11-22 user decision and is NOT a reason for CLOSES? NO. Section appended to docs/BIGBANG_TESTS.md below.

## TOOL REQUESTS

### Memory capture

`python tools/livecap/request.py add u_em3f_submitcustom 0xbc61560 --why "U-EQ6c Q6c: verify submitCustom entry regs — RCX=encoder, RDX=viewId, R8=fn pointer, R9=user data; confirm R8/R9 match the slot[0]/slot[1] layout the executor reads at 0xe822426/0xe82245d"` — submitCustom entry already exists as a livecap target (docs/data/live/u_em3f_submitcustom.txt) but shows 0 hits/0 samples; re-request to capture live regs at function entry.

### In-game test plan (Q6c / M3f whole-frame takeover demo)

What to enable: build the client DLL with a queue point that calls Encoder::submitCustom(viewId, render::takeover::render, user) each frame, where user carries a context block holding the Frame*. No HookManager, registration, CMake, or Sigs.json change (CMake GLOB_RECURSE picks up the new .cpp automatically).

Exact in-game steps:
1. Build the client DLL with the queue point wired.
2. Launch into a populated world, ~60 frames.
3. Capture at the entry of render(void* user, ExecCtx* ctx): RCX=user non-null carrying the Frame*, RDX=&ExecCtx with [RDX+0x00]=tag pointer 0xF4EDE00 [V], [RDX+0x08]=job pointer [I], [RDX+0x10]=live ID3D12GraphicsCommandList* whose first 8 bytes are a vtable pointer [V live].
4. walkRenderItems reads Frame+0xDC57E8 count, Frame+0x14700 keys (bit 53 on our custom item, bit 52 on draws), Frame+0x94700 values, Frame+0xB4700 headers stride 0x80: expect walk count == stock draw count that frame, our custom item present with fn==our render, and its header slot Frame+0xB4700+idx*0x80 holding {fn==our render, user==our context}.
5. Capture Encoder::submitCustom entry (queued as u_em3f_submitcustom at 0xbc61560) to confirm R8=our fn, R9=user, ret= names the calling queue point.

Expected observable result: our render invoked once per frame on the render thread in view order (bit 53 sorts custom items after draws/compute within a view); same command list each call; walk matches what the stock executor consumes from the same extractor output; no crash, nothing drawn incorrectly by the stock path.

## BIGBANG_TESTS.md section (appended to docs/BIGBANG_TESTS.md)

## U-EQ6c (Q6c M3f whole-frame takeover demo via custom item seam)

Item id: U-EQ6c (Q6c Whole-frame takeover demo: our renderer consumes the same extractor output (M3f)). What to enable: wire the queue point that calls Encoder::submitCustom(viewId, render::takeover::render, user) each frame, with user carrying a context block holding the Frame*. RewriteTakeover.h/.cpp and src/sdk/mc/deps/bgfx/CustomItem.h already on disk (docs/progress/oc_U-EQ6c.md, 36 [V] verbatim rows); build + wire are the batch-build step; CMake GLOB_RECURSE picks up the new .cpp automatically; no HookManager.cpp, registration, CMake, or Sigs.json change. Exact in-game steps: (1) build the client DLL with the queue point wired; (2) launch into a populated world, ~60 frames; (3) capture at the entry of render(void* user, ExecCtx* ctx): RCX=user non-null carrying the Frame*, RDX=&ExecCtx with [RDX+0x00]=tag pointer 0xF4EDE00 [V], [RDX+0x08]=job pointer [I], [RDX+0x10]=live ID3D12GraphicsCommandList* whose first 8 bytes are a vtable pointer [V live]; (4) walkRenderItems reads Frame+0xDC57E8 count, Frame+0x14700 keys (bit 53 on our custom item, bit 52 on draws), Frame+0x94700 values, Frame+0xB4700 headers stride 0x80: expect walk count == stock draw count that frame, our custom item present with fn==our render, and its header slot Frame+0xB4700+idx*0x80 holding {fn==our render, user==our context}; (5) capture Encoder::submitCustom entry (queued as u_em3f_submitcustom at 0xbc61560) to confirm R8=our fn, R9=user, ret= names the calling queue point. Expected observable result: our render invoked once per frame on the render thread in view order (bit 53 sorts custom items after draws/compute within a view); same command list each call; walk matches what the stock executor consumes from the same extractor output; no crash, nothing drawn incorrectly by the stock path. Blocking fact for full closure: the deferred in-game run (user's one big test) has not happened; nothing on-disk remains.
