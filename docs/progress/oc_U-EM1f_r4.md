## NEXT
DONE — all 63 rows verified verbatim against rdis on Minecraft.Windows.exe 1.26.62.01; CLOSES? NO (endFrame live entry missing)

# M1f D3 pass — remaining submit/frame-path D2 claims (static proof rows + existing live data)

GOAL: Close checklist item M1f "Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim that can be checked (never a debugger/breakpoint session: it crashed the game twice)" (docs/RENDER_CHECKLIST.md line 443). Entry state: PARTIAL = NOT DONE. Passes already live-done: 6ij (frame pair spacing 0xE749C0 via ctx+0x1CFD0C0/+0xC8; counters item count Frame+0xDC57E8=514, frame counter Frame+0xE746D8=31416/31417 consecutive; backbuffer {1920,1137} Frame+0xDC5808), 6il (one draw end-to-end: IB record obj+0x93A178+3*0x78, VB record obj+0x9B2178+4*0x80, layout obj+0xC96198+9*0x54), 6im (texture records obj+0xBDE178+h*0xB8: D3D12_RESOURCE_DESC +0x08, SRV +0x40, UAV +0x68; live texture_table.txt), 6in (program obj+0xB62178+p*0xF8, shader obj+0xAAA178+s*0xB8), 6io (sort keys Frame+0x14700, sorted ids Frame+0x94700). Remaining: every other D2 claim — submit 0xe82e230, Encoder::submit 0xbc60740, draw executor 0xe821120, PSO builder 0xe81e860, draw flush/batcher 0xe81b720, endFrame 0xc270460, task dispatch 0xe9002e0, view-setup task 0x568cdcc. Static instruction proof rows (verbatim from rdis on Minecraft.Windows.exe 1.26.62.01, exe passed as argument only — never launched, no debugger, no breakpoints). Live claims cited to docs/data/live/*.txt per the live-data README.

D2 dossier RVA list: submit 0xe82e230; Encoder::submit 0xbc60740; executor 0xe821120; PSO builder 0xe81e860; draw flush 0xe81b720; endFrame 0xc270460; generate 0xc273420; task dispatch 0xe9002e0; view-setup task 0x568cdcc.

All RVAs relative to image base; exe = C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe. Size class rules: movaps/movdqu/movups = 16 bytes; qword/lea/64-bit loads = 8 bytes; dword/movss/movd = 4 bytes; word = 2 bytes; byte = 1 byte. "-" size = address math or call, no load/store width. Offsets are offsets into the named object (Frame / RendererContext / per-view record / batcher / task object / header).

## Verified rows (verbatim `0xRVA  instr` lines; one row per distinct offset, all sites listed)

| offset | size | name | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| 0x19F88 | 4 | submit renderer-state guard | 0xe82e273 | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | submit aborted when renderer state < 5 (jl 0xe832cee) | [V] |
| 0x2D8 | 8 | submit swapchain guard | 0xe82e283 | `0xe82e283  cmp qword ptr [rcx+0x2D8],0` | reset slot 60 only while swapchain exists (+0x2D8 also read at 0xe82e801) | [V] |
| 0xDC5808 | 8 | submit backbuffer size | 0xe82e28d | `0xe82e28d  add rdx,0xDC5808` | Frame+0xDC5808 {u32 width,u32 height} passed to reset slot 60; live 1920x1137 (6ij) | [V live] |
| 0x1E0 | 8 | submit reset vtable slot 60 | 0xe82e297, 0xe82e2a4 | `0xe82e297  mov rax,[rax+0x1E0]` / `0xe82e2a4  call qword ptr [0xF99FFA0]` | vtable slot 60 (reset) load then indirect call via CFG thunk [0xF99FFA0] | [V] |
| 0xE746D8 | 4 | submit frame counter | 0xe82e34c | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | u32 frame counter, rises 1/frame; live consecutive 31416/31417 on the two buffers (6ij) | [V live] |
| 0xDC57F0 | 4 | submit transient IB size | 0xe82e372 | `0xe82e372  cmp dword ptr [rsi+0xDC57F0],0` | transient index-buffer size dword; zero skips the IB bind path | [V] |
| 0x93A178 | - | submit IB record base | 0xe82e46c, 0xe82e51f | `0xe82e46c  imul r14,rax,0x78` / `0xe82e51f  add r14,0x93A178` | IB record addr = renderer+0x93A178+handle*0x78 (stride 0x78=120 bytes; handle u16 at transient IB +0x10) | [V] |
| 0x9B2178 | - | submit VB record base | 0xe82e67d, 0xe82e730 | `0xe82e67d  shl r14d,7` / `0xe82e730  add r14,0x9B2178` | VB record addr = renderer+0x9B2178+handle*0x80 (stride 0x80=128 bytes; handle u16 at transient VB +0x12) | [V] |
| 0xDC57E8 | 4 | Encoder draw-index CAS | 0xbc607c2, 0xbc607ea, 0xbc607ff | `0xbc607c2  mov eax,[rcx+0xDC57E8]` / `0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d` / `0xbc607ff  cmp edi,0xFFFE` | draw-index load / CAS allocation / 0xFFFE cap at Frame+0xDC57E8 | [V] |
| 0xDC57E0 | 8 | Encoder per-view block table | 0xbc60852 | `0xbc60852  mov r11,[rcx+0xDC57E0]` | per-view block table base; [table+viewSlot] holds the view's running draw index | [V] |
| 0x6AC | 1 | Encoder view slot byte | 0xbc60859 | `0xbc60859  movzx r14d,byte ptr [rsi+0x6AC]` | view slot byte -> sort-key view field (bits 54-63); copied to Encoder+0xA4 | [V] |
| +4/blk | 4 | Encoder view running index | 0xbc60865 | `0xbc60865  mov r11d,[r11+4]` | per-view running index [block-table entry + 4] -> Encoder+0x698 | [V] |
| 0x1EAB1B2 | 1 | s_ctx sort-mode byte | 0xbc60897, 0x568cecc | `0xbc60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]` / `0x568cecc  mov [rcx+r13+0x1EAB1B2],al` | s_ctx per-view sort-mode byte (1 Sequence/2 DepthAsc/3 DepthDesc): Encoder reads, view-setup task writes | [V] |
| 0x1EAAC60 | 4 | Encoder sequence counter | 0xbc608fc | `0xbc608fc  lock xadd [r11+rdx*4+0x1EAAC60],ecx` | per-view sequence counter fetch-add (s_ctx+0x1EAAC60+viewId*4) | [V] |
| 0x14700 | 8 | Encoder sort key write | 0xbc60991 | `0xbc60991  mov [rcx+r14*8+0x14700],rax` | u64 sort key -> Frame+0x14700+idx*8 (bit52=draw, viewId<<54, mode<<48, program<<37, sequence<<5) | [V] |
| 0x94700 | 2 | Encoder sorted id write | 0xbc6099c | `0xbc6099c  mov [rax+r14*2+0x94700],di` | u16 draw id -> Frame+0x94700+idx*2 | [V] |
| 0xB4700 | 16 | Encoder draw header copy | 0xbc60b13 | `0xbc60b13  movaps [rax+rcx+0xB4700],xmm0` | 0x80-byte draw header copied verbatim (8x movaps at +0x00..+0x70) to Frame+0xB4700+idx*0x80 | [V] |
| 0x8B4700 | - | Encoder RenderDraw commit | 0xbc60b2e | `0xbc60b2e  call 0xBC7A7C0` | 0x540-byte RenderDraw record at Frame+0x8B4700+idx*0x540 (rcx=[Frame+0x8B4700], edx=idx) | [V] |
| 0x654 | 4 | Encoder bind hash | 0xbc60aa5 | `0xbc60aa5  mov [rsi+0x654],ecx` | hash over the 0x514-byte bind block at Encoder+0x140 (Murmur2A constant 0x5BD1E995 seen) stored at Encoder+0x654 | [V] |
| 0xBA | 2 | Encoder occlusion id | 0xbc60a25 | `0xbc60a25  mov [rsi+0xBA],r9w` | u16 occlusion query id at +0xBA; `or byte ptr [rsi+0x67],0x40` at 0xbc60a21 flags a query set | [V] |
| 0xC9C6D0 | 4 | renderer swapchain index | 0xe82e81d, 0xe821200 | `0xe82e81d  mov [rsi+0xC9C6D0],eax` / `0xe821200  mov r15d,[r14+0xC9C6D0]` | backbuffer/swapchain index dword at renderer+0xC9C6D0: written by submit, read by executor | [V] |
| 0x168 | 8 | executor job Frame ptr | 0xe8211b3 | `0xe8211b3  mov [rbx+0x168],r8` | Frame* stored in the executor job at job+0x168 | [V] |
| 0xA0 | 8 | executor job command list | 0xe8211ba | `0xe8211ba  mov [rbx+0xA0],rcx` | ID3D12GraphicsCommandList* stored in the job at job+0xA0 | [V] |
| 0x5F0 | 2 | executor job view id | 0xe8211f9 | `0xe8211f9  movzx esi,word ptr [rbx+0x5F0]` | per-job view/queue id u16 at job+0x5F0 | [V] |
| 0x140 | - | executor view stride | 0xe82124c, 0xe821250 | `0xe82124c  lea rax,[rsi+rsi*4]` / `0xe821250  shl eax,6` | viewId*5<<6 = viewId*0x140 per-view stride (lea+shift, address math) | [V] |
| 0x310 | 8 | executor per-view record | 0xe821253 | `0xe821253  mov rax,[rdi+rax+0x310]` | per-view record at Frame+viewId*0x140+0x310 | [V] |
| 0xB62178 | - | PSO builder program record base | 0xe81e8d7, 0xe81e8e5 | `0xe81e8d7  imul rax,0xF8` / `0xe81e8e5  add rbx,0xB62178` | program record = renderer+0xB62178+prog*0xF8 (stride 0xF8=248 bytes) | [V] |
| state-mask | 8 | PSO builder state mask | 0xe81e8ec, 0xe81e8f6 | `0xe81e8ec  mov rsi,0x707007FFFFFF0FF` / `0xe81e8f6  and rsi,r13` | PSO state-word mask 0x0707007FFFFFF0FF applied to build the key | [V] |
| stencil-mask | 8 | PSO builder stencil mask | 0xe81e8f9, 0xe81e908 | `0xe81e8f9  mov r14,0xFFFFFF00FFFFFF00` / `0xe81e908  and r14,r9` | stencil mask 0xFFFFFF00FFFFFF00 applied | [V] |
| 0xA8 | 4 | PSO builder program signature | 0xe81eac7 | `0xe81eac7  mov eax,[rax+0xA8]` | program record variant key u32 at +0xA8 (rax = program record base) | [V] |
| 0x00 | 8 | PSO builder shader code pointer | 0xe81e934 | `0xe81e934  mov rax,[rbx]` | shader record +0x00 = heap code-blob pointer (rbx = shader record from program record +0x00) | [V] |
| shader+0x80 | 16 | PSO builder shader predefined block | 0xe81e937 | `0xe81e937  movdqu xmm0,[rax+0x80]` | shader record predefined-uniform entry block at +0x80 (movdqu = 16 bytes; shader record renderer+0xAAA178+s*0xB8 per 6in) | [V] |
| 0xBDE178 | - | PSO builder texture record base | 0xe81ec33 | `0xe81ec33  lea r14,[r13+0xBDE178]` | texture record table base (4096 inline entries; overflow pages chained from renderer+0xC96178) | [V] |
| 0xB8 | - | PSO builder texture stride | 0xe81ecac | `0xe81ecac  imul r9,rsi,0xB8` | texture record stride 0xB8=184 bytes per handle | [V] |
| 0xC96190 | 1 | texture dynamic-handle guard | 0xe81ec94 | `0xe81ec94  cmp byte ptr [r13+0xC96190],0` | guard byte; handles >= 0x1000 require overflow paging | [V] |
| 0x10 | 4 | draw flush batcher pending count | 0xe81b736, 0xe81b74a | `0xe81b736  mov esi,[rcx+r12*4+0x10]` / `0xe81b74a  mov dword ptr [rcx+r12*4+0x10],0` | per-kind pending count [batcher+0x10+kind*4], read then zeroed when consumed | [V] |
| 0x18 | 8 | draw flush batcher record array | 0xe81b779 | `0xe81b779  mov rax,[rdi+r12*8+0x18]` | record array base per kind [batcher+0x18+kind*8]; 0x70-stride non-indexed / 0x88-stride indexed records | [V] |
| vtable+0x130 | 8 | draw flush root CBV | 0xe81b7d4 | `0xe81b7d4  mov rax,[rax+0x130]` | cmdlist vtable +0x130 = slot 38 SetGraphicsRootConstantBufferView (per-draw root CBV) | [V] |
| vtable+0x160 | 8 | draw flush IASetVertexBuffers | 0xe81b81b | `0xe81b81b  mov rax,[rax+0x160]` | cmdlist vtable +0x160 = slot 44 IASetVertexBuffers(0,5,views); VBV cache at batcher+0x10C0 | [V] |
| vtable+0x158 | 8 | draw flush IASetIndexBuffer | 0xe81b84f | `0xe81b84f  mov rax,[rax+0x158]` | cmdlist vtable +0x158 = slot 43 IASetIndexBuffer; IBV cache at batcher+0x1110 | [V] |
| vtable+0x68 | 8 | draw flush DrawIndexedInstanced | 0xe81b866 | `0xe81b866  mov rax,[rax+0x68]` | cmdlist vtable +0x68 = slot 13 DrawIndexedInstanced; emitted via `call qword ptr [0xF99FFA0]` at 0xe81b88b right after | [V] |
| 0x70 | 4 | draw flush indexed IndexCount | 0xe81b86a | `0xe81b86a  mov edx,[r15+0x70]` | indexed record (0x88 stride) +0x70 IndexCountPerInstance | [V] |
| 0x74 | 4 | draw flush indexed InstanceCount | 0xe81b86e | `0xe81b86e  mov r8d,[r15+0x74]` | +0x74 InstanceCount | [V] |
| 0x78 | 4 | draw flush indexed StartIndexLocation | 0xe81b872 | `0xe81b872  mov r9d,[r15+0x78]` | +0x78 StartIndexLocation | [V] |
| 0x7C | 4 | draw flush indexed BaseVertexLocation | 0xe81b876 | `0xe81b876  mov r10d,[r15+0x7C]` | +0x7C BaseVertexLocation | [V] |
| flushrec+0x80 | 4 | draw flush indexed StartInstanceLocation | 0xe81b87a | `0xe81b87a  mov r11d,[r15+0x80]` | +0x80 StartInstanceLocation (indexed stride 0x88; r15 += 0x88 per record) | [V] |
| 0x60 | 4 | draw flush non-indexed VertexCount | 0xe81ba78 | `0xe81ba78  mov edx,[r15+0x60]` | non-indexed record (0x70 stride) +0x60 VertexCountPerInstance | [V] |
| 0x64 | 4 | draw flush non-indexed InstanceCount | 0xe81ba7c | `0xe81ba7c  mov r8d,[r15+0x64]` | +0x64 InstanceCount | [V] |
| 0x68 | 4 | draw flush non-indexed StartVertexLocation | 0xe81ba80 | `0xe81ba80  mov r9d,[r15+0x68]` | +0x68 StartVertexLocation | [V] |
| 0x6C | 4 | draw flush non-indexed StartInstanceLocation | 0xe81ba84 | `0xe81ba84  mov r10d,[r15+0x6C]` | +0x6C StartInstanceLocation | [V] |
| 0x35 | 1 | endFrame early-out flag | 0xc270483 | `0xc270483  cmp byte ptr [rcx+0x35],0` | BgfxContext early-out flag byte; skips the rest of endFrame when non-zero | [V] |
| endframe-gen | - | endFrame generate call | 0xc270521 | `0xc270521  call 0xC273420` | frame-graph generate/encode (0xc273420, 0x8A73 bytes) | [V] |
| endframe-dispatch | - | endFrame task dispatch call | 0xc270554 | `0xc270554  call 0xE9002E0` | task dispatch with dispatch struct (allocator, sub-object ptr, task-list ptr, surface, DragonFrameResources*) | [V] |
| dispatch-count | - | dispatch entry count | 0xe900373 | `0xe900373  sar rax,7` | (task-end - task-begin)>>7 = entry count; entries are 0x80 bytes | [V] |
| vt+0x18 | 8 | dispatch vtable slot 2 | 0xe90046b | `0xe90046b  mov rax,[rax+0x18]` | task object vtable +0x18 (getName/kind); shared_ptr strong refcount inc at [rax+8] | [V] |
| 0x298 | 8 | dispatch live task vector | 0xe9004aa, 0xe9004c5 | `0xe9004aa  mov r15,[rdi+0x298]` / `0xe9004c5  add qword ptr [rdi+0x298],0x10` | DragonFrameResources live task vector {obj*,ctrl*}, 16-byte entries; end pointer advanced per entry | [V] |
| [[task+8]]+8 | 2 | view-setup task view id | 0x568cdcc | `0x568cdcc  movzx eax,word ptr [rax+8]` | viewId word ([[task+8]]+8) -> viewId*0x140 | [V] |
| 0x1EAB090 | 4 | view-setup task view rect | 0x568cdf6 | `0x568cdf6  movd [rcx+r13+0x1EAB090],xmm0` | task+0xF8 -> view+0x10 rect in s_ctx per-view record (s_ctx+0x1EAB090+viewId*0x140; +0x94 gets rect hi dwords at 0x568ce0c) | [V] |
| view+0x20 | - | view-setup task view mat4 | 0x568ce51 | `0x568ce51  call 0xEBCE390` | view mat4 +0x20 (s_ctx+0x1EAB0A0+viewId*0x140); four 16-byte copies via helper | [V] |
| view+0x60 | - | view-setup task proj mat4 | 0x568ce6a | `0x568ce6a  call 0xEBCE390` | proj mat4 +0x60 | [V] |
| view+0xA0 | - | view-setup task prev-view mat4 | 0x568ce83 | `0x568ce83  call 0xEBCE390` | prev-view mat4 +0xA0 | [V] |
| view+0xE0 | - | view-setup task prev-proj mat4 | 0x568ce9c | `0x568ce9c  call 0xEBCE390` | prev-proj mat4 +0xE0 | [V] |
| view+0x120 | - | view-setup task view vec4 | 0x568ceb9 | `0x568ceb9  call 0xEBCE390` | task+0x18C -> view+0x120 (16 bytes) | [V] |

## Live captures consumed by this unit (existing data, docs/data/live/README.md format)

- docs/data/live/u_em1f_submit_entry.txt (kind=regs, rva=0xE82E230; _status.txt: hits=418 samples=32, DONE): `CALLER ret=0xE83D4DB` (line 3) — submit entered through the RTX slot-50 override wrapper 0xe83d440 -> base submit 0xe82e230; RCX=0x2300A010000 stable renderer object across hits (line 4); RDX=0x23006023D80 Frame pointer whose 0x200-byte dump (line 5) is the identity u16 viewRemap table 0,1,2,...255 = Frame+0x000 [V live]; submit fires every frame (consecutive hit stream) [V live].
- docs/data/live/u_em1f_draw_flush.txt (kind=regs, rva=0xE81B720; _status.txt: hits=354192 samples=32, DONE): `CALLER ret=0xE822E53`/`0xE822E70`/`0xE82D130`/`0xE82D14D` (lines 3, 13, 29, 33) — the batcher flush is reached from executor call sites in the 0xe822xxx/0xe82d1xx region [V live]; RCX = batcher objects (22FC698A080, 22FC698C880, 22FC6987880, 22FC680C880, ...) whose dumps show per-kind pending counts at +0x10+kind*4 and record-array pointers at +0x18+kind*8, matching the static rows above [V live].

## Already-done live passes (do NOT re-prove; cited from BGFX_MAP.md 6ij/6il/6im/6in/6io)

- Frame pair spacing 0xE749C0 (ctx+0x1CFD0C0/+0xC8 hold the two Frame pointers) [V live 6ij]; Frame item count 0xDC57E8 = 514 [V live 6ij]; frame counter 0xE746D8 consecutive [V live 6ij]; backbuffer {1920,1137} at 0xDC5808 [V live 6ij]; one draw end-to-end: IB record 3 at obj+0x93A178+3*0x78 (+0x58 GPU VA, +0x60 size 0x100000, +0x70 stride 2), VB record 4 at obj+0x9B2178+4*0x80 (+0x58 GPU VA, +0x60 size 0x400000, +0x70 stride 0x10, +0x78 = 0xFFFF), layout 9 at obj+0xC96198+9*0x54 (+0x00 hash 0xCCE6BA11, +0x04 stride 0x18) [V live 6il]; texture records obj+0xBDE178+h*0xB8 (D3D12_RESOURCE_DESC +0x08, SRV +0x40, UAV +0x68; docs/data/live/texture_table.txt) [V live 6im]; program obj+0xB62178+p*0xF8 / shader obj+0xAAA178+s*0xB8 [V live 6in]; sort keys Frame+0x14700, sorted ids Frame+0x94700 [V live 6io].

## Changes on disk

- docs/progress/oc_U-EM1f.md — this file only (created). No edits to Sigs.json, CMake, HookManager.cpp, any existing hook registration, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, CLAUDE.md. No build, no game launch/attach (OPENCODE_BRIEF rule 1).

## CLOSES?

NO — blocking fact: M1f's wording requires one live poll-only read or in-game check per claim for EVERY D2 dossier. endFrame 0xc270460, task dispatch 0xe9002e0 and view-setup task 0x568cdcc have static instruction proof [V] above but NO live read yet; units cannot run or attach to the game (OPENCODE_BRIEF rule 1) and breakpoint sessions crashed the game twice (item wording). The single in-game step still missing: a live entry capture at endFrame 0xc270460 in the populated server — expect rcx = BgfxContext object, ~1 hit per frame, and within the same frame the calls to 0xc273420 (frame-graph generate/encode) and 0xe9002e0 (task dispatch), which covers the endFrame/task-dispatch/view-setup dossiers in one check.

## TOOL REQUESTS

In-game test plan (poll-only, populated server; no debugger, no breakpoints, no writes):

1. ctx = readQword(base+0x12AE1748); F0=[ctx+0x1CFD0C0], F1=[ctx+0x1CFD0C8]; verify |F0-F1| == 0xE749C0. The consume frame is the one with stable u32 [F+0xDC57E8] and counter u32 [F+0xE746D8] exactly one below the fill frame; re-check both pointers before/after each multi-step sample (they swap at frame boundaries; 6ij race note).
2. [F+0xDC5808] == {1920, 1137} (backbuffer u32 width/height); [F+0xDC57E8] item count (~500 in a populated server, below 0xFFFE).
3. For each u16 id in the sorted list [F+0x94700][0..n): header h = [F+0xB4700]+id*0x80; expect state +0x20 low dword in {0x17, 0x1F, 0x27}, +0x76 == 0xFFFF, +0x74 == 0xFFFF0003; sort key u64 [F+0x14700]+id*8 has bit 52 set and viewId = key>>54 in 0..15.
4. IB record obj+0x93A178+ib*0x78: +0x58 GPU VA, +0x60 size, +0x70 stride 2; VB record obj+0x9B2178+vb*0x80: +0x58 GPU VA, +0x60 size, +0x70 stride, +0x78 layout handle (0xFFFF = none); layout record obj+0xC96198+l*0x54: +0x04 stride, attribute offsets at +0x06 (6il, re-polled per frame).
5. Texture record obj+0xBDE178+t*0xB8: D3D12_RESOURCE_DESC at +0x08, SRV desc at +0x40, second desc at +0x68 — compare docs/data/live/texture_table.txt (6im).
6. Program record obj+0xB62178+p*0xF8: +0x00/+0x08 shader record pointers, +0xA8 signature; shader record obj+0xAAA178+s*0xB8: +0x00 code-blob pointer, +0xA8 signature (6in).
7. MISSING LIVE STEP: endFrame entry at 0xc270460 — confirm rcx = BgfxContext, ~1 hit/frame, calls to 0xc273420 and 0xe9002e0 inside the same frame (covers endFrame/task-dispatch/view-setup dossiers).

Queued captures (function-entry RVAs, log-only execute breakpoints, size 0x200, max 8):
- python tools/livecap/request.py add u_em1f_endframe @ 0xc270460 --size 0x200 --max 8 --why "M1f: endFrame live entry check — confirm endFrame fires ~1/frame in the populated server and calls generate 0xc273420 + task dispatch 0xe9002e0 (covers the endFrame/task-dispatch/view-setup dossiers, static-only so far)"

CAPTURE REQUESTED u_em1f_endframe (pending the orchestrator's capture batch; result -> docs/data/live/u_em1f_endframe.txt)

## NEXT
step 2
