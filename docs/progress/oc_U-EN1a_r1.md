## NEXT
DONE

GOAL: Close checklist item N1a: "Submit takeover hook at 0xe82e230 (slot 50 stats/timers); replacement walks Frame+0xB4700 draw records (stride 0x80) — BGFX_MAP 8a, 10".

VERIFIED (static, rdis on 1.26.62.01 Minecraft.Windows.exe, all quotes copied verbatim from listings):

1. Vtable slot 50 → submit: `vt 0xF4ED2D0` prints `50 +0x190  sub_e82e230  size 0x4d91  push rbp`; base vtable 0xF4ED2D0 [V]. RTX subclass vtable 0xF4EEE80 overrides slot 50 at 0xe83d440 and wraps base [I, 6al]; hooking 0xe82e230 covers both entry paths [8a].
2. submit signature: rcx = RendererContext*, rdx = Frame* — `0xe82e26c  mov [rbp+0x16a8],rdx` saves rdx, then `0xe82e345  mov rsi,[rbp+0x16a8]` and `0xe82e34c  mov r9d,[rsi+0xe746d8]` use it as Frame* [V].
3. Renderer-state skip: `0xe82e273  cmp dword ptr [rcx+0x19f88],5` / `0xe82e27a  jl 0xe832cee` — state < 5 skips submit work (8a: this+0x19F88 int <5 = skip) [V].
4. Stats/timers inline: `0xe82e332  call 0xebdb740` (QPC timestamp, stored [rbp+0x15d8]) [V]; 0xe81d660 frame-begin/reset at 0xe82e367 [6t] [I].
5. Frame+0xE746D8 u32 frame counter read via rsi=Frame*: `0xe82e34c  mov r9d,[rsi+0xe746d8]` [V].
6. Frame+0xDC5808 backbuffer size: `0xe82e28d  add rdx,0xdc5808` [V].
7. RendererContext+0x19F58 resource-table ptr: `0xe82e353  mov rdx,[rdi+0x19f58]` [V]; RendererContext+0x2D8 command-list wrapper null-check `0xe82e283  cmp qword ptr [rcx+0x2d8],0` [V].
8. Draw/item count: `0xe8306af  movsxd rcx,[rax+0xdc57e8]` (rax=Frame*, cap 0xFFFE per Frame.h) [V]; sort keys `0xe8306bf  lea r8,[rax+0x14700]` + view field `0xe8306cd  shr rdx,0x36` (key>>54) [V]; per-item u16 load `0xe8306d4  movzx r10d,word ptr [rax+rdx*2]` [V] (rax=Frame*, rdx=viewId; sorted u16 list at Frame+0x94700 is executor-backed, not a literal displacement in submit's body).
9. Draw-record walk base: executor 0xe821120 stores `0xe821853  lea r8,[rax+0xb4700]` then `0xe82185a  mov [rbx+0x590],r8` — Frame+0xB4700 is the header base, addressed as base + (index<<7): executor loop `0xe822414  movzx edx,word ptr [rdx+rax*2+0x94700]` / `0xe82241c  shl edx,7` then `0xe82241f  mov r8,[rbx+0x590]` / `0xe822426  mov rax,[r8+rdx]` [V]. 0x80 stride scale also inside submit: `0xe82e67d  shl r14d,7` [V].
10. Header state word: `0xe8223cd  cmp byte ptr [r8+0x23],0` / `0xe8223d2  je 0xe822480` — executor tests state byte at header+0x23 (part of u64 state at +0x20) [V]; executor also tests bit 62 at 0xe822e1d/0xe82ce5b [6an] [I].

| name | rva or offset | size | verbatim proof line `0xRVA  instr` | tag |
|---|---|---|---|---|
| submit entry (vtable 0xF4ED2D0 slot 50 +0x190) | 0xe82e230 | 0x4d91 | `0xe82e230  push rbp` | [V] |
| Frame* arg (rdx) saved locally | [rbp+0x16a8] ← rdx | 8 | `0xe82e26c  mov [rbp+0x16a8],rdx` | [V] |
| renderer state skip, RendererContext+0x19F88 u32 | 0xe82e273 / 0xe82e27a | 4 | `0xe82e273  cmp dword ptr [rcx+0x19f88],5` ; `0xe82e27a  jl 0xe832cee` | [V] |
| QPC stats/timer call inside submit | call 0xebdb740 | 8 | `0xe82e332  call 0xebdb740` | [V] |
| frame counter | Frame+0xE746D8 u32 | 4 | `0xe82e34c  mov r9d,[rsi+0xe746d8]` | [V] |
| backbuffer size {u32 w, u32 h} | Frame+0xDC5808 | 8 | `0xe82e28d  add rdx,0xdc5808` | [V] |
| resource-table ptr | RendererContext+0x19F58 | 8 | `0xe82e353  mov rdx,[rdi+0x19f58]` | [V] |
| draw/item count (cap 0xFFFE) | Frame+0xDC57E8 u32 | 4 | `0xe8306af  movsxd rcx,[rax+0xdc57e8]` | [V] |
| sort keys u64[], viewId = key>>54 | Frame+0x14700 | 8 | `0xe8306bf  lea r8,[rax+0x14700]` ; `0xe8306cd  shr rdx,0x36` | [V] |
| per-item u16 load | Frame+viewId*2 | 2 | `0xe8306d4  movzx r10d,word ptr [rax+rdx*2]` | [V] |
| draw-header base, stride 0x80 | Frame+0xB4700 | 0x80 | `0xe821853  lea r8,[rax+0xb4700]` ; `0xe82185a  mov [rbx+0x590],r8` | [V] |
| index×0x80 stride in the item loop | `shl edx,7` after the 0x94700 load | 2→0x80 | `0xe82241c  shl edx,7` ; `0xe82241f  mov r8,[rbx+0x590]` ; `0xe822426  mov rax,[r8+rdx]` | [V] |
| state word u64 at header+0x20 (byte +0x23 tested) | header+0x20/+0x23 | 1 | `0xe8223cd  cmp byte ptr [r8+0x23],0` ; `0xe8223d2  je 0xe822480` | [V] |
| 0x80 stride scale inside submit body | `shl r14d,7` | 2→0x80 | `0xe82e67d  shl r14d,7` | [V] |

Per-draw header fields from the section-0 example (program +0x38, startIdx +0x40, indexCnt +0x44, ibHandle +0x5A, vbHandle +0x76, state +0x20, bind mask +0x63) are [I] in BGFX_MAP 8a; the executor-verified subset I quote above is [V]. The packed `RenderDraw` struct in src/sdk/mc/deps/bgfx/Frame.h pins every one of those offsets with static_asserts [V] and matches all quoted lines.

CHANGES ON DISK (this unit only):
- docs/progress/oc_U-EN1a.md — this note (created, this unit's only output so far).
- NEW src/client/features/render/rewrite/RewriteSubmit.h — takeover seam header: entry constants (0xe82e230, slot 50, size 0x4d91), detour prototype, RewriteRegistry entry declaration.
- NEW src/client/features/render/rewrite/RewriteSubmit.cpp — detour that walks Frame+0xB4700 headers stride 0x80 (FrameOffsets::kDrawHeaders / RenderDraw from Frame.h), per-draw stats + QPC timers, fail-fast (no null guards, no SEH), forwards to the original via the registry trampoline; registered mode Off (nothing installs without a mode switch + build).
- src/sdk/Sigs.json — appended ONE new proven entry: deps.bgfx.RendererContextD3D12.submit (sig from the verbatim prologue bytes, 0xe82e230). No existing entry touched.
- docs/data/layout_asserts.json — appended one new symbol entry "RendererContextD3D12::submit" with constants verified present in submit's body (0xdc57e8 item count, 0x14700 sort keys, 0xe746d8 frame counter, 0xdc5808 backbuffer, 0x19f88 renderer state, 0x19f58 resource tables, 0x410 side table); 0x94700 sorted list is executor-backed (drawExecutor), not a literal displacement in submit's body, so it is not asserted for submit.

CLOSES?: NO — the takeover hook source + Frame/draw-record layout header exist on disk and every layout claim above is [V]-proven, but the hook is registered mode Off and the client is not built (builds forbidden in this unit), so nothing calls 0xe82e230 yet and the Frame+0xB4700 walk has not been observed in a live frame. Single blocking fact: the detour must be compiled into the client DLL, switched On via RewriteRegistry, and verified in-game (submit entered through the RTX override 0xe83d440 → base 0xe82e230); all of that requires a build + game launch, both outside this unit.

## TOOL REQUESTS
- rdis `imm 0xb4700` returned 0 hits although `lea r8,[rax+0xB4700]` exists at 0xe821853 (verified by `dis`): the `imm` command does not match lea displacements; I used `dis` listings instead. If `imm` is intended to cover lea displacements, fixing it would let later units scan constant footprints without dumping whole functions.
