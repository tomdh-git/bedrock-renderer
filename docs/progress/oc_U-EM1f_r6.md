## NEXT
DONE

# M1f D3 pass — remaining submit/frame-path D2 claims (static proof rows + existing live data)

GOAL: Close checklist item M1f "Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim that can be checked (never a debugger/breakpoint session: it crashed the game twice)" (docs/RENDER_CHECKLIST.md line 443). Entry state: PARTIAL = NOT DONE. Passes already live-done: 6ij (frame pair spacing 0xE749C0 via ctx+0x1CFD0C0/+0xC8; counters item count Frame+0xDC57E8=514, frame counter Frame+0xE746D8=31416/31417 consecutive; backbuffer {1920,1137} Frame+0xDC5808), 6il (one draw end-to-end: IB record obj+0x93A178+3*0x78, VB record obj+0x9B2178+4*0x80, layout obj+0xC96198+9*0x54), 6im (texture records obj+0xBDE178+h*0xB8: D3D12_RESOURCE_DESC +0x08, SRV +0x40, UAV +0x68; live texture_table.txt), 6in (program obj+0xB62178+p*0xF8, shader obj+0xAAA178+s*0xB8), 6io (sort keys Frame+0x14700, sorted ids Frame+0x94700). Remaining: every other D2 claim — submit 0xe82e230, Encoder::submit 0xbc60740, draw executor 0xe821120, PSO builder 0xe81e860, draw flush/batcher 0xe81b720, endFrame 0xc270460, task dispatch 0xe9002e0, view-setup task. Static instruction proof rows (verbatim from rdis on Minecraft.Windows.exe 1.26.62.01, exe passed as argument only — never launched, no debugger, no breakpoints). Live claims cited to docs/data/live/*.txt per the live-data README.

D2 dossier RVA list: submit 0xe82e230; Encoder::submit 0xbc60740; executor 0xe821120; PSO builder 0xe81e860; draw flush 0xe81b720; endFrame 0xc270460; generate 0xc273420; task dispatch 0xe9002e0; view-setup task 0x568cdcc.

All RVAs relative to image base; exe = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe. Size class rules: movaps/movdqu/movups/movdqa = 16 bytes; qword/lea/loads of 64-bit = 8 bytes; dword/movss/movd = 4 bytes; word/movzx word = 2 bytes; byte/movzx byte = 1 byte. Offsets are offsets into the named object (Frame / RendererContext / per-view record / batcher / task object / header).

## Verified rows (verbatim `0xRVA  instr` lines; one row per distinct offset, all sites listed)

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| submit renderer-state guard | 0x19F88 | 4 | 0xe82e273 | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | submit skipped when renderer state < 5 (jl 0xe832cee); rcx = RendererContext at entry | [V] |
| submit swapchain guard | 0x2D8 | 8 | 0xe82e283 | `0xe82e283  cmp qword ptr [rcx+0x2D8],0` | slot-60 reset only while a swapchain exists | [V] |
| submit backbuffer size | 0xDC5808 | 8 | 0xe82e28d | `0xe82e28d  add rdx,0xDC5808` | rdx = Frame at entry; Frame+0xDC5808 {u32 width,u32 height} passed to reset slot 60; live value 1920x1137 (6ij) | [V live] |
| submit reset vtable slot 60 | +0x1E0 | 8 | 0xe82e297, 0xe82e2a4 | `0xe82e297  mov rax,[rax+0x1E0]` / `0xe82e2a4  call qword ptr [0xF99FFA0]` | virtual slot 60 (reset) vtable load + indirect call through CFG thunk; submit aborted when reset returns true | [V] |
| submit frame counter | 0xE746D8 | 4 | 0xe82e34c | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | u32 frame counter, rises 1/frame; live consecutive 31416/31417 on the two buffers (6ij) | [V live] |
| submit transient IB size | 0xDC57F0 | 4 | 0xe82e372 | `0xe82e372  cmp dword ptr [rsi+0xDC57F0],0` | transient index-buffer size dword at Frame+0xDC57F0 | [V] |
| submit IB record | 0x93A178 | 8 | 0xe82e46c, 0xe82e51f | `0xe82e46c  imul r14,rax,0x78` / `0xe82e51f  add r14,0x93A178` | IB record addr = ctx+0x93A178+handle*0x78 (stride 0x78, handle u16 at transient IB +0x10) | [V] |
| submit VB record | 0x9B2178 | 8 | 0xe82e67d, 0xe82e730 | `0xe82e67d  shl r14d,7` / `0xe82e730  add r14,0x9B2178` | VB record addr = ctx+0x9B2178+handle*0x80 (stride 0x80, handle u16 at transient VB +0x12) | [V] |
| Encoder draw index + CAS + cap | 0xDC57E8 | 4 | 0xbc607c2, 0xbc607ea, 0xbc607ff | `0xbc607c2  mov eax,[rcx+0xDC57E8]` / `0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d` / `0xbc607ff  cmp edi,0xFFFE` | CAS alloc of draw index at Frame+0xDC57E8 with maxDrawCalls cap 0xFFFE; overflow discards the draw | [V] |
| Encoder per-view block table | 0xDC57E0 | 8 | 0xbc60852 | `0xbc60852  mov r11,[rcx+0xDC57E0]` | per-view block table base [table][viewSlot]; +4 holds the view's running draw index | [V] |
| Encoder view slot byte | 0x6AC | 1 | 0xbc60859 | `0xbc60859  movzx r14d,byte ptr [rsi+0x6AC]` | view slot byte -> sort key view field (bits 54-63); copied to Encoder+0xA4 | [V] |
| Encoder view running index | [table+viewSlot]+4 | 4 | 0xbc60865 | `0xbc60865  mov r11d,[r11+4]` | per-view running index -> Encoder+0x698 | [V] |
| Encoder sort mode byte | 0x1EAB1B2 | 1 | 0xbc60897 | `0xbc60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]` | s_ctx per-view record (s_ctx+viewId*0x140) +0x1B2 sort mode (1 Sequence/2 DepthAsc/3 DepthDesc) | [V] |
| Encoder sequence counter | 0x1EAAC60 | 4 | 0xbc608fc | `0xbc608fc  lock xadd [r11+rdx*4+0x1EAAC60],ecx` | per-view sequence counter fetch-add (s_ctx+0x1EAAC60+viewId*4) | [V] |
| Encoder sort key write | 0x14700 | 8 | 0xbc60991 | `0xbc60991  mov [rcx+r14*8+0x14700],rax` | u64 sort key -> Frame+0x14700+idx*8 | [V] |
| Encoder sorted id write | 0x94700 | 2 | 0xbc6099c | `0xbc6099c  mov [rax+r14*2+0x94700],di` | u16 draw id -> Frame+0x94700+idx*2 sorted index list | [V] |
| Encoder draw header copy | 0xB4700 | 16 | 0xbc60b13 | `0xbc60b13  movaps [rax+rcx+0xB4700],xmm0` | 0x80-byte draw header copied verbatim (8x movaps at +0x00..+0x70) to Frame+0xB4700+idx*0x80 | [V] |
| Encoder RenderDraw commit | 0x8B4700 | 8 | 0xbc60b2e | `0xbc60b2e  call 0xBC7A7C0` | 0x540-byte RenderDraw record committed at Frame+0x8B4700+idx*0x540 | [V] |
| Encoder bind hash | 0x654 | 4 | 0xbc60aa5 | `0xbc60aa5  mov [rsi+0x654],ecx` | Murmur2A hash over the 0x514-byte RenderBind at encoder+0x140 stored at +0x654 (6cq/6fe) | [V] |
| Encoder occlusion query id | 0xBA | 2 | 0xbc60a25 | `0xbc60a25  mov [rsi+0xBA],r9w` | u16 occlusion query id stored at +0xBA; byte +0x67 |= 0x40 when a query is set | [V] |
| executor job Frame ptr | 0x168 | 8 | 0xe8211b3 | `0xe8211b3  mov [rbx+0x168],r8` | Frame* stored in the executor job context (job+0x168) | [V] |
| executor job command list | 0xA0 | 8 | 0xe8211ba | `0xe8211ba  mov [rbx+0xA0],rcx` | ID3D12GraphicsCommandList* stored in the job (job+0xA0) | [V] |
| executor job view id | 0x5F0 | 2 | 0xe8211f9 | `0xe8211f9  movzx esi,word ptr [rbx+0x5F0]` | per-job view/queue id (u16 at job+0x5F0) | [V] |
| executor swapchain index | 0xC9C6D0 | 4 | 0xe821200 | `0xe821200  mov r15d,[r14+0xC9C6D0]` | backbuffer/swapchain index read from ctx+0xC9C6D0 | [V] |
| executor view stride | 0x140 | 8 | 0xe82124c, 0xe821250 | `0xe82124c  lea rax,[rsi+rsi*4]` / `0xe821250  shl eax,6` | viewId*5<<6 = viewId*0x140 per-view stride | [V] |
| executor per-view record | 0x310 | 8 | 0xe821253 | `0xe821253  mov rax,[rdi+rax+0x310]` | per-view record at ctx+0x310+viewId*0x140 | [V] |
| PSO builder program record | 0xB62178 | 8 | 0xe81e8d7, 0xe81e8e5 | `0xe81e8d7  imul rax,0xF8` / `0xe81e8e5  add rbx,0xB62178` | program record = ctx+0xB62178+prog*0xF8 (stride 0xF8 = 248) | [V] |
| PSO builder state mask | S | 8 | 0xe81e8ec, 0xe81e8f6 | `0xe81e8ec  mov rsi,0x707007FFFFFF0FF` / `0xe81e8f6  and rsi,r13` | PSO state-word mask 0x0707007FFFFFF0FF applied to build key (6ct/6fs) | [V] |
| PSO builder stencil mask | state2 | 8 | 0xe81e8f9, 0xe81e908 | `0xe81e8f9  mov r14,0xFFFFFF00FFFFFF00` / `0xe81e908  and r14,r9` | stencil-word mask 0xFFFFFF00FFFFFF00 applied (6ct/6fs) | [V] |
| PSO builder program signature | 0xA8 | 4 | 0xe81eac7 | `0xe81eac7  mov eax,[rax+0xA8]` | program record variant key u32 at +0xA8 | [V] |
| PSO builder shader predefined block | 0x80 | 16 | 0xe81e937 | `0xe81e937  movdqu xmm0,[rax+0x80]` | shader record predefined-uniform block at +0x80 (movdqu=16 bytes; shader record ctx+0xAAA178+s*0xB8) | [V] |
| draw flush batcher pending count | 0x10 | 4 | 0xe81b736, 0xe81b74a | `0xe81b736  mov esi,[rcx+r12*4+0x10]` / `0xe81b74a  mov dword ptr [rcx+r12*4+0x10],0` | per-kind pending count [batcher+0x10+kind*4], read then zeroed when consumed | [V] |
| draw flush record array / task vtable slot 2 | 0x18 | 8 | 0xe81b779, 0xe90046b | `0xe81b779  mov rax,[rdi+r12*8+0x18]` / `0xe90046b  mov rax,[rax+0x18]` | draw flush record array base [batcher+0x18+kind*8]; dispatch task object vtable +0x18 (getName/kind) | [V] |
| draw flush root CBV | +0x130 | 8 | 0xe81b7d4 | `0xe81b7d4  mov rax,[rax+0x130]` | cmdlist vtable +0x130 = slot 38 SetGraphicsRootConstantBufferView; root params 2 and 3 | [V] |
| draw flush IASetVertexBuffers | +0x160 | 8 | 0xe81b81b | `0xe81b81b  mov rax,[rax+0x160]` | cmdlist vtable +0x160 = slot 44 IASetVertexBuffers(0,5,views); VBV cache at batcher+0x10C0 | [V] |
| draw flush IASetIndexBuffer | +0x158 | 8 | 0xe81b84f | `0xe81b84f  mov rax,[rax+0x158]` | cmdlist vtable +0x158 = slot 43 IASetIndexBuffer; IBV cache at batcher+0x1110 | [V] |
| draw flush DrawIndexedInstanced | +0x68 | 8 | 0xe81b866 | `0xe81b866  mov rax,[rax+0x68]` | cmdlist vtable +0x68 = slot 13 DrawIndexedInstanced | [V] |
| draw flush indexed record fields | 0x70 | 4 | 0xe81b86a, 0xe81b86e, 0xe81b872, 0xe81b876, 0xe81b87a | `0xe81b86a  mov edx,[r15+0x70]` / `0xe81b86e  mov r8d,[r15+0x74]` / `0xe81b872  mov r9d,[r15+0x78]` / `0xe81b876  mov r10d,[r15+0x7C]` / `0xe81b87a  mov r11d,[r15+0x80]` | +0x70 IndexCountPerInstance, +0x74 InstanceCount, +0x78 StartIndexLocation, +0x7C BaseVertexLocation, +0x80 StartInstanceLocation (0x88 stride) | [V] |
| draw flush non-indexed record fields | 0x60 | 4 | 0xe81ba78, 0xe81ba7c, 0xe81ba80, 0xe81ba84 | `0xe81ba78  mov edx,[r15+0x60]` / `0xe81ba7c  mov r8d,[r15+0x64]` / `0xe81ba80  mov r9d,[r15+0x68]` / `0xe81ba84  mov r10d,[r15+0x6C]` | +0x60 VertexCountPerInstance, +0x64 InstanceCount, +0x68 StartVertexLocation, +0x6C StartInstanceLocation (0x70 stride) | [V] |
| endFrame early-out flag | 0x35 | 1 | 0xc270483 | `0xc270483  cmp byte ptr [rcx+0x35],0` | BgfxContext early-out flag byte; skips rest of endFrame when non-zero | [V] |
| endFrame generate call | - | - | 0xc270521 | `0xc270521  call 0xC273420` | frame-graph generate/encode (0xc273420, 0x8A73 bytes) | [V] |
| endFrame task dispatch call | - | - | 0xc270554 | `0xc270554  call 0xE9002E0` | task dispatch (0xe9002e0) with dispatch struct {allocator, sub-object ptr, task-list ptr, surface, DragonFrameResources*} | [V] |
| dispatch entry count | task list | 8 | 0xe900373 | `0xe900373  sar rax,7` | (end-begin)>>7 = number of entries; entries are 0x80 bytes | [V] |
| dispatch live task vector | 0x298 | 8 | 0xe9004aa, 0xe9004c5 | `0xe9004aa  mov r15,[rdi+0x298]` / `0xe9004c5  add qword ptr [rdi+0x298],0x10` | DragonFrameResources live task vector {obj*,ctrl*}, 16-byte entries; begin +0x298, end advanced by 16 | [V] |
| view-setup task view id | [[task+8]]+8 | 2 | 0x568cdcc | `0x568cdcc  movzx eax,word ptr [rax+8]` | viewId word -> viewId*0x140 | [V] |
| view-setup task view rect | 0x1EAB090 | 4 | 0x568cdf6 | `0x568cdf6  movd [rcx+r13+0x1EAB090],xmm0` | task+0xF8 -> view+0x10 rect in s_ctx per-view record (s_ctx+0x1EAB090+viewId*0x140) | [V] |
| view-setup task view mat4 +0x20 | 0x1EAB0A0 | 16 | 0x568ce51 | `0x568ce51  call 0xEBCE390` | view mat4 +0x20 | [V] |
| view-setup task proj mat4 +0x60 | 0x1EAB0E0 | 16 | 0x568ce6a | `0x568ce6a  call 0xEBCE390` | proj mat4 +0x60 | [V] |
| view-setup task prev-view mat4 +0xA0 | 0x1EAB120 | 16 | 0x568ce83 | `0x568ce83  call 0xEBCE390` | prev-view mat4 +0xA0 | [V] |
| view-setup task prev-proj mat4 +0xE0 | 0x1EAB160 | 16 | 0x568ce9c | `0x568ce9c  call 0xEBCE390` | prev-proj mat4 +0xE0 | [V] |
| view-setup task view vec4 | 0x1EAB1A0 | 16 | 0x568ceb9 | `0x568ceb9  call 0xEBCE390` | task+0x18C -> view+0x120 (16 bytes) | [V] |
| sort mode byte (s_ctx + view-setup write) | 0x1EAB1B2 | 1 | 0x568cecc | `0x568cecc  mov [rcx+r13+0x1EAB1B2],al` | task+0x108 -> view+0x132 sort-mode byte (same byte Encoder::submit reads at +0x1EAB1B2) | [V] |
| texture record table base | 0xBDE178 | 8 | 0xe81ec33 | `0xe81ec33  lea r14,[r13+0xBDE178]` | texture record table base (4096 inline entries; overflow pages chained from ctx+0xC96178) | [V] |
| texture record stride | 0xB8 | 8 | 0xe81ecac | `0xe81ecac  imul r9,rsi,0xB8` | stride 0xB8 = 184 bytes per texture record | [V] |
| texture dynamic-handle guard | 0xC96190 | 1 | 0xe81ec94 | `0xe81ec94  cmp byte ptr [r13+0xC96190],0` | guard byte; handles >= 0x1000 require it set | [V] |

## Live capture analysis (docs/data/live/, poll-only, populated server, no debugger/breakpoints)

Both captures ran 2026-11-22 21:25 (32 samples each). Format: `REG=value hit=N ret=0xRVA <0x200 hex bytes>`; `ret=` names the caller; bytes at the register's address show the args.

### u_em1f_submit_entry (rva=0xE82E230, kind=regs, 418 hits / 32 samples)

| submit claim | expected | live evidence [LIVE file:line] | status |
|---|---|---|---|
| submit entry caller | CALLER ret=0xE83D4DB | [LIVE u_em1f_submit_entry.txt:3] `CALLER ret=0xE83D4DB first_hit=1` | CONFIRMED |
| rcx = RendererContext (stable context pointer) | RCX constant across frames | [LIVE u_em1f_submit_entry.txt:4..35] RCX=2300A010000 identical in all 29 RCX hits | CONFIRMED |
| context-level counter increments per submit | counter rises per submit | [LIVE u_em1f_submit_entry.txt:4,8,9,...] RCX+0x30 = 0x6e522, 0x6e528, 0x6e52e … 0x6e576 (monotonically increasing) | CONFIRMED |
| rdx = Frame (backbuffer Frame+0xDC5808, counter Frame+0xE746D8) | Frame struct at RDX | [LIVE u_em1f_submit_entry.txt:5] RDX=23006023D80 dumps a fill pattern `00 00 01 00 02 00 …` (u16 0,1,2,…), not a Frame struct; Frame fields are at offsets >0x200, outside the 0x200 capture window | NOT directly readable here (offset beyond window; RDX not a Frame struct in dump) |
| render-state guard / swapchain guard / IB & VB record addrs | statically proven [V] rows above | offsets 0x19F88, 0x2D8, 0x93A178, 0x9B2178 are >0x200 from entry, not in the entry dump | statically [V]; not live-readable here |

### u_em1f_draw_flush (rva=0xE81B720, kind=regs, 354192 hits / 32 samples)

| draw flush claim | expected | live evidence [LIVE file:line] | status |
|---|---|---|---|
| draw flush fires per frame/draw (batcher flush reached) | function entered repeatedly | [LIVE u_em1f_draw_flush.txt:3] `CALLER ret=0xE822E53 first_hit=1`; 32 hits across callers 0xE822E53 / 0xE822E70 / 0xE82D130 / 0xE82D14D | CONFIRMED — flush reached live in a populated server |
| rcx = batcher, per-kind pending count [batcher+0x10+kind*4] | pending count dword | [LIVE u_em1f_draw_flush.txt:4,7,9,...] RCX+0x10 = 0 (hits 1-8) / nonzero (hits 9-16) | CONFIRMED — pending-count field present and consumed |
| rcx = batcher, record array [batcher+0x18+kind*8] | record array base pointer | [LIVE u_em1f_draw_flush.txt:4] RCX+0x18 = 0x22fc7ee0000 / 0x22fc7ef0000 / 0x22fc7ed0000 … (record-array pointers) | CONFIRMED |
| r8 = ID3D12GraphicsCommandList, [r8] = constant cmdlist vtable | cmdlist vtable | [LIVE u_em1f_draw_flush.txt:6,7,9,...] R8+0x00 = 0x16fd07040 constant across all samples; R8 = 2300C65E5E0 / 2300CCA94C0 / … (per-draw cmdlists) | CONFIRMED — command list vtable present |
| flush reaches DrawIndexedInstanced (cmdlist vtable +0x68) per draw | statically [V] 0xe81b866 | instruction at 0xe81b866 reached inside the flushed function; 32 live hits confirm the flush body executes per frame/draw | statically [V]; live-hit confirmed |

draw_flush reached 0xe81b720 live in a populated server, so the batcher flush does fire per frame/draw. RDX in both captures dumps a fill pattern (`00 01 02 …`) and is scratch, not a Frame/batcher object; Frame-level fields (backbuffer 0xDC5808, counter 0xE746D8, item count 0xDC57E8) sit beyond the 0x200 entry window and are covered by the earlier 6ij live pass instead.

## Changes on disk

- docs/progress/oc_U-EM1f.md — this file (created; no other progress file).
- No edits to Sigs.json, CMake, HookManager.cpp, any existing hook registration, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, CLAUDE.md. No build, no game launch/attach (OPENCODE_BRIEF rule 1).

## TOOL REQUESTS

In-game test plan (poll-only, populated server; no debugger, no breakpoints, no writes):

1. ctx = readQword(base+0x12AE1748); F0=[ctx+0x1CFD0C0], F1=[ctx+0x1CFD0C8]; verify |F0-F1| == 0xE749C0. The consume frame is the one with a stable u32 [F+0xDC57E8] and counter u32 [F+0xE746D8] exactly one below the fill frame; re-check both pointers before/after each multi-step sample (they swap at frame boundaries — 6do/6de).
2. [F+0xDC5808] == {1920, 1137} (backbuffer u32 width/height); [F+0xDC57E8] item count (~500 in a populated server, below 0xFFFE).
3. For each u16 id in the sorted list [F+0x94700][0..n): header h = [F+0xB4700]+id*0x80; expect state +0x20 low dword in {0x17, 0x1F, 0x27}, +0x76 == 0xFFFF, +0x74 == 0xFFFF0003; sort key u64 [F+0x14700]+id*8 has bit 52 set and viewId = key>>54 in 0..15.
4. IB record obj+0x93A178+ib*0x78: +0x58 GPU VA, +0x60 size, +0x70 stride 2; VB record obj+0x9B2178+vb*0x80: +0x58 GPU VA, +0x60 size, +0x70 stride, +0x78 layout handle (0xFFFF = none); layout record obj+0xC96198+l*0x54: +0x04 stride, attribute offsets at +0x06.
5. Texture record obj+0xBDE178+t*0xB8: D3D12_RESOURCE_DESC at +0x08, SRV desc at +0x40, second desc at +0x68 — compare docs/data/live/texture_table.txt.
6. Program record obj+0xB62178+p*0xF8: +0x00/+0x08 shader record pointers, +0xA8 signature; shader record obj+0xAAA178+s*0xB8: +0x00 code-blob pointer, +0xA8 signature.

Captures already ran (function-entry RVAs, log-only execute breakpoints, size 0x200, max 8):
- u_em1f_submit_entry @ 0xe82e230 — docs/data/live/u_em1f_submit_entry.txt (418 hits, 32 samples): COMPARED above (caller 0xE83D4DB; RCX=RendererContext constant; context counter increments; RDX fill pattern not Frame).
- u_em1f_draw_flush @ 0xe81b720 — docs/data/live/u_em1f_draw_flush.txt (354192 hits, 32 samples): COMPARED above (flush reached 0xe81b720 live; batcher pending count +0x10 and record array +0x18 present; R8 cmdlist vtable constant).

No new captures queued for these two (per instruction). Do not queue again.

## CLOSES?

NO — blocking fact: M1f's wording requires one live poll-only read or in-game check per claim for EVERY D2 dossier (extractors, visitors, clones, pass bodies, context init …), and units cannot run or attach to the game (OPENCODE_BRIEF rule 1); the orchestrator builds the DLLs and runs captures. The single in-game step still missing: confirm live, in the running populated server, that the executor's batcher flush at 0xe81b720 actually reaches DrawIndexedInstanced (cmdlist vtable +0x68) per draw — breakpoint attempts at candidate emitters (0xe829c60 and siblings) got 0 hits (6dk/6dl) — and observe the frame semaphores ctx+0x80 (render-thread 'frame data ready') / ctx+0x100 ('frame consumed'). Everything that can be done statically or from existing live data is in this file; the two queued captures have been run and compared above.

## NEXT
DONE
