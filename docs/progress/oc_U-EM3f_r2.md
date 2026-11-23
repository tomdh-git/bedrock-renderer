## NEXT
DONE

# U-EM3f — M3f Whole-frame replacement (custom-item seam)

## Status
CLOSES? YES — see end of file. The whole-frame replacement seam (M3f, key bit 53) is fully decoded statically and the implementing code is already on disk; this unit adds only the verified proof note and the in-game test plan (build + the one in-game run are deferred per the user decision 2026-11-22 and are not on-disk blockers).

## What changed (paths)
- Created: docs/progress/oc_U-EM3f.md (this note). No other file created or edited.
- Source: NO source change required. Everything M3f relies on is already on disk (committed by prior unit U-EQ6c; cited as proof, not edited):
  - src/client/features/render/rewrite/RewriteTakeover.h — ExecCtx 0x18 with 3 static_asserts; sort masks kKeyCustomBit (bit 53)/view54/seq32; RenderFn = void(void* user, ExecCtx* ctx); RenderItemView + ItemVisitor; walkRenderItems decl; render() decl unwired.
  - src/client/features/render/rewrite/RewriteTakeover.cpp — selfTest() static_asserts on bgfx::FrameOffsets {kItemCount 0xDC57E8, kSortKeys 0x14700, kSortedItems 0x94700, kDrawHeaders 0xB4700} and bgfx::RenderDrawHeader {kSize 0x80, kState 0x20, kByte62 0x62, kHandle7A 0x7A, kScissor 0x60}; walkRenderItems read-only impl; render() unwired stub (read-only walk + classify, nothing submitted to the GPU).
  - src/sdk/mc/deps/bgfx/Frame.h — FrameOffsets, RenderDrawHeader/RenderDraw 0x80, RenderCompute, SortKey (kDrawBit bit52, kCustomBit bit53).
  - src/sdk/mc/deps/bgfx/Encoder.h — EncoderOffsets (kCustomItem 0x100), EncoderRvas (kSubmit 0xBC60740, kSubmitVariant2 0xBC61560 = submitCustom), Binding, DrawState, SortKey decoders.
  - src/sdk/mc/deps/bgfx/CustomItem.h — CustomRenderItem {fn@0, user@8} (0x10), CustomItemCtx {fnPtr@0, job@8, commandList@16} (0x18), CustomItemFn.
  - src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h — kEncoderSubmitCustom {0x0020000000000000, 0x100, 0x108}; kDrawExecutor class mask 0x0030000000000000 / custom bit 0x0020000000000000; BS_RENDER_LAYOUT_FN("Encoder::submitCustom", 0x372, ...); checked by tools/sigs/layoutcheck.py against Sigs.json symbols+sizes.
- Not edited (and not needed for M3f): HookManager.cpp, any existing hook registration, CMakeLists.txt, existing Sigs.json entries, any build. The one remaining step is a queue point that calls Encoder::submitCustom(viewId, render, user) with user carrying the Frame*, plus a build and the single deferred in-game run — this unit may not do any of those three (docs/OPENCODE_BRIEF.md rules 1-2; deferred-testing rule 2026-11-22).

## Decoded seam — proof rows, every address/instruction verified verbatim against Minecraft.Windows.exe 1.26.62.01 via rdis (exe passed only as rdis argument; never launched)

| offset | size | read/store address | `0xRVA  instr` proof line | meaning |
|---|---|---|---|---|
| bc61584 | 1 | Encoder+0x6AD (read) | `0xbc61584  cmp byte ptr [rcx+0x6AD],1` | submitCustom discard byte; ==1 tail-jumps to reset (0xBC60D10) |
| bc615c2 | 4 | Frame+0xDC57E8 (CAS operand) | `0xbc615c2  mov eax,[rcx+0xDC57E8]` | item slot counter m_numRenderItems (cap 0xFFFE) |
| bc615ea | 8 | Frame+0xDC57E8 (CAS) | `0xbc615ea  lock cmpxchg [rcx+0xDC57E8],r11d` | atomically reserve draw slot index |
| bc6161a | 4 | Encoder+0x68C (store) | `0xbc6161a  inc dword ptr [rsi+0x68C]` | m_numSubmitted++ |
| bc61623 | 8 | Frame+0xDC57E0 (read) | `0xbc61623  mov rax,[rax+0xDC57E0]` | Frame uniform-buffer* table, indexed by encoder+0x6AC |
| bc61645 | 8 | Encoder+0x100 (store) | `0xbc61645  mov [rsi+0x100],r8` | custom item payload word0 = fn (r8 = submitCustom's fn arg) |
| bc6164c | 8 | Encoder+0x108 (store) | `0xbc6164c  mov [rsi+0x108],r9` | custom item payload word1 = user (r9 = submitCustom's user arg) |
| bc61697 | 8 | imm 0x20000000000000 | `0xbc61697  mov rcx,0x20000000000000` | sort key bit 53 = custom item class |
| bc616aa | 8 | Frame+0x14700+idx*8 (store) | `0xbc616aa  mov [rax+r15*8+0x14700],rcx` | sort key stored per submitted item |
| bc616b5 | 2 | Frame+0x94700+idx*2 (store) | `0xbc616b5  mov [rax+r15*2+0x94700],di` | sort value = submitted item index |
| bc61749 | 8 | shift count | `0xbc61749  shl rcx,7` | idx * 0x80 header-slot stride |
| bc61751 | 16 | Frame+0xB4700+idx*0x80 (store) | `0xbc61751  movaps [rax+rcx+0xB4700],xmm0` | 16-byte {fn@0,user@8} payload copied verbatim into the item header slot |
| e822202 | 4 | job+0x33C (read) | `0xe822202  cmp r15d,[rbx+0x33C]` | executor loop bound vs item count |
| e822220 | 8 | Frame+0x14700+idx*8 (read) | `0xe822220  mov rdx,[rdx+rax*8+0x14700]` | sort key read for class dispatch |
| e822235 | 8 | mask r8=0x30000000000000 (e82222b) | `0xe822235  and rdx,r8` | item class mask = draw bit 52 | custom bit 53 |
| e822242 | 8 | r8=0x20000000000000 (e822238) | `0xe822242  cmp rdx,r8` | masked key == custom bit only? |
| e822267 | 2 | branch | `0xe822267  jne 0xE822400` | bit-53-only key routes to custom-item path at 0xe822400 |
| e822414 | 2 | Frame+0x94700+idx*2 (read) | `0xe822414  movzx edx,word ptr [rdx+rax*2+0x94700]` | sort value -> slot offset (<<7 at e82241c) |
| e82241c | 8 | shift count | `0xe82241c  shl edx,7` | slot offset = index * 0x80 |
| e82241f | 8 | job+0x590 (read) | `0xe82241f  mov r8,[rbx+0x590]` | header array base = Frame+0xB4700 |
| e822426 | 8 | slot+0 (read) | `0xe822426  mov rax,[r8+rdx]` | slot[0] = fn; skipped when 0 (e82242a test / e82242d je) |
| e822436 | 8 | job+0x90 (read) | `0xe822436  mov rcx,[rbx+0x90]` | job state |
| e82243d | 8 | [job+0x90]+0x30 (read) | `0xe82243d  mov rcx,[rcx+0x30]` | ID3D12GraphicsCommandList* for this job |
| e822441 | 8 | rodata 0xF4EDE00 (read) | `0xe822441  lea r8,[0xF4EDE00]` | ExecCtx+0x00 tag const; single xref (ripscan); no .text reader -> meaning [?], never interpreted by our renderer |
| e822448 | 8 | job+0x3B0 (store) | `0xe822448  mov [rbx+0x3B0],r8` | ExecCtx+0x00 = tag |
| e82244f | 8 | job+0x3B8 (store) | `0xe82244f  mov [rbx+0x3B8],rsi` | ExecCtx+0x08 = job field, reloaded each iteration from [rbx+0xB0] (e822474) [I] |
| e822456 | 8 | job+0x3C0 (store) | `0xe822456  mov [rbx+0x3C0],rcx` | ExecCtx+0x10 = command list |
| e82245d | 8 | slot+8 (read) | `0xe82245d  mov rcx,[rdx+8]` | rcx = user = slot[1] = submitCustom's user arg |
| e822461 | 8 | lea | `0xe822461  lea rdx,[rbx+0x3B0]` | rdx = &ExecCtx |
| e822468 | 8 | CFG thunk [0xF99FFA0] (call) | `0xe822468  call qword ptr [0xF99FFA0]` | fn(user, &ctx) invoked on the render thread, in view order (thunk = sub_eea6040) |
| e82246f | 1 | imm | `0xe82246f  mov cl,1` | tail flag |
| e822474 | 8 | job+0xB0 (read) | `0xe822474  mov rsi,[rbx+0xB0]` | loop tail: rsi reloaded from job field each iteration [I] |
| e82247b | 5 | branch | `0xe82247b  jmp 0xE8221F5` | back to executor item loop head |

Context: ExecCtx at job+0x3B0 = {tag@0x00, user@0x08, commandList@0x10}, sizeof 0x18 — pinned by RewriteTakeover.h static_asserts and CustomItem.h. submitCustom size 0x372 (0xbc61560..0xbc618D2) per RenderLayoutAsserts.h. Custom-item callers in the game (per BGFX_MAP 6fh, not re-verified by this unit): 0x568ba70, 0x5699c70, 0x56c8650, 0x56ca2f0, 0x56d0d60, 0xbc04300 [I].

## CLOSES?
CLOSES? YES — the M3f whole-frame-replacement seam is fully reversed ([V] rows above), the implementing code and layout static_asserts are on disk and follow CLAUDE.md style (fail fast, no null guards, no SEH), nothing needs HookManager/CMake/Sigs edits, and the in-game verification is explicitly deferred by the user's 2026-11-22 decision (one big in-game run later), so it is not an on-disk blocker. No unknown REVERSING remains for this item: every offset/RVA/meaning in the seam is either [V] or deliberately [I]/[?] (tag object 0xF4EDE00 meaning, not consumed by our renderer).

## TOOL REQUESTS
Helper scripts: none.

In-game test plan (executed by the orchestrator's build + capture, not by this unit):
1. Build the client DLL with RewriteTakeover.h/.cpp wired and a queue point calling Encoder::submitCustom(viewId, render, user) on a view each frame (e.g. main game view); user is a context block carrying the Frame* (ctx has no Frame/job back-pointer).
2. Launch into a populated world, let ~60 frames render.
3. Capture at the entry of render(void* user, ExecCtx* ctx) (RVA unknown until the DLL is built — fill at build time): RCX=user must be non-null and carry the Frame*; RDX=&ExecCtx → [RDX+0x00] tag pointer == 0xF4EDE00 [V], [RDX+0x08] job pointer [I], [RDX+0x10] live ID3D12GraphicsCommandList* whose first 8 bytes are a vtable pointer [V live].
4. Inside render, walkRenderItems(frame, ...): expect count = Frame+0xDC57E8 u32 (>0 and equal to the stock draw count this frame); sort keys Frame+0x14700 u64[] with bit 53 on our own custom item and bit 52 on draws; sort values Frame+0x94700 u16[] = indices; headers Frame+0xB4700 stride 0x80 (state+0x20, submitFlags+0x62, scissor+0x60, occlusionQuery+0x7A). Our custom item's header slot at Frame+0xB4700 + idx*0x80 holds {fn == our render, user == our context}.
5. Expected observable result: our render invoked once per frame on the render thread in view order (custom key bit 53 sorts after draws/compute within the view); each call receives the same command-list pointer; the walk visits exactly `count` items and our item is among them; no crash, nothing drawn incorrectly by the stock path.
6. Queued capture: `python tools/livecap/request.py add u_em3f_submitcustom 0xbc61560 --why "U-EM3f/M3f: confirm the queue point calls Encoder::submitCustom with our renderer's fn (ret= names the calling queue point); register layout R8=fn, R9=user; 0x100-byte capture <= 0x200, max 6 samples."` (render() entry capture: RVA TBD at build time.)

## Live data used
docs/data/live/README.md read; no live capture needed for the static decode — all claims proven against the exe disassembly above ([V]).
