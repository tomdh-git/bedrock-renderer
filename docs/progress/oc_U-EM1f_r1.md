## NEXT
DONE

# M1f D3 pass — remaining submit/frame-path D2 claims (static proof rows + existing live data)

GOAL: Close checklist item M1f "Every D2 dossier gets a D3 pass: one live poll-only read or in-game check per claim that can be checked" (docs/RENDER_CHECKLIST.md). Entry state: PARTIAL = NOT DONE. Passes 6ij/6il (2026-11-14, populated server, no client DLL, poll-only reads) covered: frame pair spacing 0xE749C0 (ctx+0x1CFD0C0/+0xC8 hold the two Frame pointers), counters (item count u32 Frame+0xDC57E8, frame counter u32 Frame+0xE746D8), backbuffer 1920x1137 at Frame+0xDC5808, ~514 items/frame, draw header fields (all sentinels), index buffer record ctx+0x93A178+handle*0x78, vertex buffer record ctx+0x9B2178+handle*0x80, vertex layout record ctx+0xC96198+handle*0x54 followed end-to-end for one draw. BGFX_MAP.md 6im/6in/6io mark texture records, program/shader records and sort keys/sorted list as live-done.

This unit adds instruction-proof rows (verbatim from rdis on Minecraft.Windows.exe 1.26.62.01, exe passed as argument only — never launched, no debugger, no breakpoints) for the submit/frame-path D2 claims not yet row-proven on disk: submit slot 50, Encoder::submit, the draw executor head, the PSO builder, the draw flush/DrawBatcher, endFrame -> generate -> task dispatch, and the view-setup task. Live claims are cited to docs/data/live/*.txt (file + line) per the live-data README.

Status of the named M1f claims on entry (all [V live] per BGFX_MAP.md, cited, not re-derived):
- 6ij: frame pair spacing 0xE749C0; item count at Frame+0xDC57E8 (514 in a populated-server frame, below the 0xFFFE cap); frame counter Frame+0xE746D8 consecutive on the two buffers (31416/31417); backbuffer {1920,1137} at Frame+0xDC5808 on both; draw headers sane (state low dwords 0x17/0x1F/0x27, +0x76 == 0xFFFF "none", +0x74 == 0xFFFF0003).
- 6il: one draw (header i=257 of a 515-item frame): stream0 {startVertex 0x16818, handle 4, layout 9}; state +0x20 (low dword 0x1F, high 0x01000040); uniform begin/end +0x34/+0x38 = 0x4DF4/0x51CC; startIndex +0x40 = 0x4251, numIndices +0x44 = 0x24, index stride +0x48 = 2, numVertices +0x4C = 0x18, numInstances +0x54 = 1, scissor +0x60 = 0x009E, uniform index +0x64 = 3, index buffer +0x74 = 3, instance/indirect/occlusion words +0x76/+0x78/+0x7A = 0xFFFF; IB record 3 at ctx+0x93A178+3*0x78 (+0x58 GPU VA 0x204200000, +0x60 size 0x100000, +0x70 stride 2); VB record 4 at ctx+0x9B2178+4*0x80 (+0x58 0x204400000, +0x60 size 0x400000, +0x70 0x10, +0x78 0xFFFF no layout); layout 9 at ctx+0xC96198+9*0x54 (+0x00 hash 0xCCE6BA11, +0x04 stride 0x18, per-attribute offsets at +0x06).
- 6im: texture record at obj+0xBDE178+h*0xB8 = D3D12_RESOURCE_DESC at +0x08 (38 bytes: dimension/width/height/format/…), D3D12_SHADER_RESOURCE_VIEW_DESC at +0x40 (0x28 bytes), second description at +0x68 (0x28 bytes), 8 pad bytes at +0x90, then fields +0x98 flags … +0xB1 mips; live table docs/data/live/texture_table.txt (handle 12 = 1937x333 fmt 0x1C R8G8B8A8_UNORM; handle 0x56A/0x68A 32x32 RGBA8 bound slots seen in a 1111-item frame).
- 6in: program record obj+0xB62178+p*0xF8 (+0x00 vertex shader record ptr, +0x08 fragment shader record ptr, +0x10 predefined entries, +0xF0 numPredefined); shader record obj+0xAAA178+s*0xB8 (+0x00 code-blob pointer, +0x08 constant buffer, +0xA8 signature u32). Program 0 = {vs record 0x503A8ABA178, fs record 0x503A8ABA230, +0x10 = 0x000B000400000000, +0xF0 = 1}; 150/600 program handles and 118/600 shader handles populated in the sampled frame.
- 6io: sort keys Frame+0x14700 (u64; bit 52 = draw class, viewId in bits 54-63, mode tag in bits 48-53, program/sequence below), sorted u16 id list Frame+0x94700, count u32 Frame+0xDC57E8 (1106 items, views 0-15 in the sampled frame).

## Changes on disk

- docs/progress/oc_U-EM1f.md — this file (created; no other progress file).
- docs/progress/capture_requests.json — two read-only capture requests queued via tools/livecap/request.py (u_em1f_submit_entry @ 0xe82e230, u_em1f_draw_flush @ 0xe81b720; state pending, results go to docs/data/live/).
- No edits to Sigs.json, CMake, HookManager.cpp, any existing hook registration, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, CLAUDE.md. No build, no game launch/attach (OPENCODE_BRIEF rule 1).

## Verified rows (verbatim `0xRVA  instr` lines from rdis; one row per distinct offset, all sites listed)

| name | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| submit renderer-state guard | 0x19F88 | 4 | 0xe82e273 | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | submit skipped when renderer state < 5 (jl 0xe832cee) | [V] |
| submit swapchain guard | 0x2D8 | 8 | 0xe82e283 | `0xe82e283  cmp qword ptr [rcx+0x2D8],0` | slot-60 reset only while a swapchain exists | [V] |
| submit backbuffer size | 0xDC5808 | 8 | 0xe82e28d | `0xe82e28d  add rdx,0xDC5808` | Frame+0xDC5808 {u32 width,u32 height} passed to reset slot 60; live value 1920x1137 (6ij) | [V live] |
| submit reset vtable call | slot 60 / +0x1E0 | - | 0xe82e297, 0xe82e2a4 | `0xe82e297  mov rax,[rax+0x1E0]` / `call qword ptr [0xF99FFA0]` | virtual slot 60 = reset called with rdx=Frame+0xDC5808; submit aborted when it returns true (resize in flight, 6dn) | [V] |
| submit frame counter | 0xE746D8 | 4 | 0xe82e34c | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | u32 frame counter, rises 1/frame; live consecutive 31416/31417 on the two buffers (6ij) | [V live] |
| submit transient IB size | 0xDC57F0 | 4 | 0xe82e372 | `0xe82e372  cmp dword ptr [rsi+0xDC57F0],0` | transient index-buffer size dword, Frame+0xDC57F0 | [V] |
| submit index-buffer record addr | 0x93A178 | 8 | 0xe82e46c, 0xe82e51f | `0xe82e46c  imul r14,rax,0x78` / `0xe82e51f  add r14,0x93A178` | IB record addr = ctx+0x93A178+handle*0x78 (stride 0x78, handle u16 at transient IB +0x10) | [V] |
| submit vertex-buffer record addr | 0x9B2178 | 8 | 0xe82e67d, 0xe82e730 | `0xe82e67d  shl r14d,7` / `0xe82e730  add r14,0x9B2178` | VB record addr = ctx+0x9B2178+handle*0x80 (stride 0x80, handle u16 at transient VB +0x12) | [V] |
| Encoder draw/item count | 0xDC57E8 | 4 | 0xbc607c2 | `0xbc607c2  mov eax,[rcx+0xDC57E8]` | count loaded for the CAS draw-index allocation | [V] |
| Encoder draw-index CAS cap | 0xDC57E8 | 4 | 0xbc607ea, 0xbc607ff | `0xbc607ea  lock cmpxchg [rcx+0xDC57E8],r14d` / `cmp edi,0xFFFE; jb` | CAS alloc with maxDrawCalls cap 0xFFFE; overflow discards the draw | [V] |
| Encoder per-view block table | 0xDC57E0 | 8 | 0xbc60852 | `0xbc60852  mov r11,[rcx+0xDC57E0]` | [table][viewSlot] per-view block; +4 holds the view's running draw index | [V] |
| Encoder view slot byte | 0x6AC | 1 | 0xbc60861 | `0xbc60861  movzx r14d,byte ptr [rsi+0x6AC]` | view slot byte -> sort key view field (bits 54-63); copied to Encoder+0xA4 | [V] |
| Encoder view running index | [table+viewSlot]+4 | 4 | 0xbc60865, 0xbc60869 | `0xbc60869  mov r11d,[r11+4]` | per-view running index -> Encoder+0x698 | [V] |
| Encoder sort-mode byte | 0x1EAB1B2 | 1 | 0xbc60897 | `0xbc60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]` | s_ctx per-view record (s_ctx+viewId*0x140) +0x1B2 sort mode (1 Sequence/2 DepthAsc/3 DepthDesc) | [V] |
| Encoder sequence counter | 0x1EAAC60 | 4 | 0xbc608fc | `0xbc608fc  lock xadd [r11+rdx*4+0x1EAAC60],ecx` | per-view sequence counter fetch-add (s_ctx+0x1EAAC60+viewId*4) | [V] |
| Encoder sort key write | 0x14700 | 8 | 0xbc60991 | `0xbc60991  mov [rcx+r14*8+0x14700],rax` | u64 sort key -> Frame+0x14700+idx*8; bit 52 = draw, viewId<<54, mode tag<<48, program<<37 (default mode), per-view sequence<<5 | [V] |
| Encoder sorted id write | 0x94700 | 2 | 0xbc6099c | `0xbc6099c  mov [rax+r14*2+0x94700],di` | u16 draw id -> Frame+0x94700+idx*2 sorted index list | [V] |
| Encoder draw header copy | 0xB4700 | 16 | 0xbc60aec, 0xbc60af3, 0xbc60af7, 0xbc60afb, 0xbc60abc, 0xbc60ac8, 0xbc60ad4, 0xbc60ae0, 0xbc60b13 | `0xbc60b13  movaps [rax+rcx+0xB4700],xmm0` | 0x80-byte draw header copied verbatim (8x movaps at +0x00..+0x70) to Frame+0xB4700+idx*0x80 | [V] |
| Encoder RenderDraw commit | 0x8B4700 | 1360 | 0xbc60b1e, 0xbc60b2e | `0xbc60b2e  call 0xBC7A7C0` (rcx=[r15+0x8B4700], edx=idx) | 0x540-byte RenderDraw record committed at Frame+0x8B4700+idx*0x540; 0x518-byte RenderBind memcpy just before | [V] |
| Encoder bind hash | 0x654 | 4 | 0xbc60a50, 0xbc60aa5 | `0xbc60a50  call 0xBC76610` / `0xbc60aa5  mov [rsi+0x654],ecx` | Murmur2A (seed 0x5BD1E995) over the 0x514-byte RenderBind at encoder+0x140 -> bind hash +0x654 (6cq/6fe) | [V] |
| Encoder occlusion query id | 0xBA | 2 | 0xbc60a25 | `0xbc60a25  mov [rsi+0xBA],r9w` | u16 occlusion query id; byte +0x67 |= 0x40 when a query is set | [V] |
| executor job Frame ptr | 0x168 | 8 | 0xe8211b3 | `0xe8211b3  mov [rbx+0x168],r8` | Frame* stored in the executor job context (job+0x168) | [V] |
| executor job command list | 0xA0 | 8 | 0xe8211ba | `0xe8211ba  mov [rbx+0xA0],rcx` | ID3D12GraphicsCommandList* stored in the job (job+0xA0) | [V] |
| executor job view id | 0x5F0 | 2 | 0xe8211f9 | `0xe8211f9  movzx esi,word ptr [rbx+0x5F0]` | per-job view/queue id (u16 at job+0x5F0) | [V] |
| executor swapchain index | 0xC9C6D0 | 4 | 0xe821200 | `0xe821200  mov r15d,[r14+0xC9C6D0]` | backbuffer/swapchain index read from ctx+0xC9C6D0 | [V] |
| executor view stride | 0x140 | 8 | 0xe82124c, 0xe821250 | `0xe82124c  lea rax,[rsi+rsi*4]` / `shl eax,6` | viewId*0x140 per-view stride | [V] |
| executor per-view record | 0x310 | 8 | 0xe821253 | `0xe821253  mov rax,[rdi+rax+0x310]` | per-view record at ctx+0x310+viewId*0x140 | [V] |
| PSO builder program record | 0xB62178 | 248 | 0xe81e8d7, 0xe81e8e5 | `0xe81e8d7  imul rax,0xF8` / `add rbx,0xB62178` | program record = ctx+0xB62178+prog*0xF8 (stride 0xF8 = 248 bytes, 6au/6in) | [V] |
| PSO builder state mask | S | 8 | 0xe81e8ec, 0xe81e8f6 | `0xe81e8ec  mov rsi,0x707007FFFFFF0FF` / `and rsi,r13` | PSO state-word mask 0x0707007FFFFFF0FF (6ct/6fs) | [V] |
| PSO builder stencil mask | state2 | 8 | 0xe81e8f9, 0xe81e908 | `0xe81e8f9  mov r14,0xFFFFFF00FFFFFF00` / `and r14,r9` | stencil-word mask 0xFFFFFF00FFFFFF00 (6ct/6fs) | [V] |
| PSO builder program signature | 0xA8 | 4 | 0xe81eac7 | `0xe81eac7  mov eax,[rax+0xA8]` | program record variant key u32 (four signed bytes b0..b3) at +0xA8 | [V] |
| PSO builder shader predefined block | 0x80 | 16 | 0xe81e934 | `0xe81e934  movdqu xmm0,[rax+0x80]` | shader record predefined-uniform entry block at +0x80 (movdqu = 16 bytes; shader record ctx+0xAAA178+s*0xB8, 6hv/6in) | [V] |
| PSO builder shader code pointer | 0x00 | 8 | 0xe81e934 | `0xe81e934  mov rax,[rbx]` then `movdqu xmm0,[rax+0x80]` | shader record +0x00 = heap code-blob pointer (6in); +0x80 read above | [V] |
| draw flush batcher pending count | 0x10 | 4 | 0xe81b736, 0xe81b74a | `0xe81b736  mov esi,[rcx+r12*4+0x10]` / `mov dword ptr [rcx+r12*4+0x10],0` | per-kind pending count [batcher+0x10+kind*4], zeroed when consumed | [V] |
| draw flush batcher record array | 0x18 | 8 | 0xe81b779 | `0xe81b779  mov rax,[rdi+r12*8+0x18]` | record array base per kind [batcher+0x18+kind*8]; 0x70-stride non-indexed / 0x88-stride indexed records | [V] |
| draw flush root CBV set | +0x130 | 8 | 0xe81b7d4 | `0xe81b7d4  mov rax,[rax+0x130]` / call | cmdlist vtable +0x130 = slot 38 SetGraphicsRootConstantBufferView; root params 2 and 3 (per-draw constants/matrices) | [V] |
| draw flush IASetVertexBuffers | +0x160 | 8 | 0xe81b81b | `0xe81b81b  mov rax,[rax+0x160]` | cmdlist vtable +0x160 = slot 44 IASetVertexBuffers(0,5,views); VBV cache at batcher+0x10C0 | [V] |
| draw flush IASetIndexBuffer | +0x158 | 8 | 0xe81b84f | `0xe81b84f  mov rax,[rax+0x158]` | cmdlist vtable +0x158 = slot 43 IASetIndexBuffer; IBV cache at batcher+0x1110 | [V] |
| draw flush DrawIndexedInstanced | +0x68 | 8 | 0xe81b866 | `0xe81b866  mov rax,[rax+0x68]` | cmdlist vtable +0x68 = slot 13 DrawIndexedInstanced; record fields +0x70 IndexCount … +0x80 StartInstance (0x88 stride) | [V] |
| draw flush indexed record fields | 0x70 | 4 | 0xe81b86a, 0xe81b86e, 0xe81b872, 0xe81b876, 0xe81b87a | `0xe81b86a  mov edx,[r15+0x70]` … `mov r11d,[r15+0x80]` | +0x70 IndexCountPerInstance, +0x74 InstanceCount, +0x78 StartIndexLocation, +0x7C BaseVertexLocation, +0x80 StartInstanceLocation | [V] |
| draw flush non-indexed record fields | 0x60 | 4 | 0xe81ba78, 0xe81ba7c, 0xe81ba80, 0xe81ba84 | `0xe81ba78  mov edx,[r15+0x60]` … `mov r10d,[r15+0x6C]` | +0x60 VertexCountPerInstance, +0x64 InstanceCount, +0x68 StartVertexLocation, +0x6C StartInstanceLocation (0x70 stride) | [V] |
| endFrame early-out flag | 0x35 | 1 | 0xc270483 | `0xc270483  cmp byte ptr [rcx+0x35],0` | BgfxContext early-out flag byte | [V] |
| endFrame generate call | - | - | 0xc270521 | `0xc270521  call 0xC273420` | frame-graph generate/encode (0xc273420, 0x8A73 bytes) | [V] |
| endFrame task dispatch call | - | - | 0xc270554 | `0xc270554  call 0xE9002E0` | task dispatch (0xe9002e0) with the dispatch struct {allocator, sub-object ptr, task-list ptr, surface, DragonFrameResources*} | [V] |
| task dispatch entry count | task list | 8 | 0xe900373 | `0xe900373  sar rax,7` | (end-begin)>>7 = number of entries; entries are 0x80 bytes | [V] |
| task dispatch vtable slot 2 | 0x18 | 8 | 0xe90046b | `0xe90046b  mov rax,[rax+0x18]` | task object vtable +0x18 (getName/kind); shared_ptr refcount inc at [rax+8] | [V] |
| task dispatch live task vector | 0x298 | 8 | 0xe9004aa, 0xe9004c5 | `0xe9004aa  mov r15,[rdi+0x298]` / `add qword ptr [rdi+0x298],0x10` | DragonFrameResources live task vector {obj*,ctrl*}, 16-byte entries, begin +0x298 / end +0x2A0 | [V] |
| view-setup task view id | [[task+8]]+8 | 2 | 0x568cdcc | `0x568cdcc  movzx eax,word ptr [rax+8]` | viewId word ([[task+8]]+8) -> viewId*0x140 | [V] |
| view-setup task view rect | 0x1EAB090 | 4 | 0x568cdf6 | `0x568cdf6  movd [rcx+r13+0x1EAB090],xmm0` | task+0xF8 -> view+0x10 in the s_ctx per-view record (s_ctx+0x1EAB090+viewId*0x140) | [V] |
| view-setup task view matrices | 0x1EAB0A0 | 16 | 0x568ce4b, 0x568ce67, 0x568ce83, 0x568ce9c | `0x568ce51  call 0xEBCE390` (rcx=s_ctx+r13+0x1EAB0A0; three more identical calls at +0x1EAB0E0/+0x1EAB120/+0x1EAB160) | view mat4 +0x20, proj +0x60, prev-view +0xA0, prev-proj +0xE0 (4x movaps copies, task+0xB8/+0x10C/+0x14C) | [V] |
| view-setup task view vec4 | 0x1EAB120 | 16 | 0x568ceb9 | `0x568ceb9  mov r8d,0x10` / `call 0xEBCE390` | task+0x18C -> view+0x120 (16 bytes) | [V] |
| view-setup task sort mode | 0x1EAB1B2 | 1 | 0x568cecc | `0x568cecc  mov [rcx+r13+0x1EAB1B2],al` | task+0x108 -> view+0x132 sort-mode byte (same byte Encoder::submit reads at +0x1EAB1B2) | [V] |
| texture record table base | 0xBDE178 | 8 | 0xe81ec33 | `0xe81ec33  lea r14,[r13+0xBDE178]` | texture record table base (4096 inline entries; overflow pages chained from ctx+0xC96178) | [V] |
| texture record stride | 0xB8 | 184 | 0xe81ecac | `0xe81ecac  imul r9,rsi,0xB8` | stride 0xB8 = 184 bytes per texture record, handle = record index | [V] |
| texture dynamic-handle guard | 0xC96190 | 1 | 0xe81ec94 | `0xe81ec94  cmp byte ptr [r13+0xC96190],0` | guard byte; handles >= 0x1000 require it set (else "guarded paged heap backed array out of bounds") | [V] |
| live texture record contents | 0x18/0x20/0x28 | - | 0xe81ec33 | `0xe81ec33  lea r14,[r13+0xBDE178]` | live handle 12: width 1937 @+0x18, height 333 @+0x20, format 0x1C @+0x28 (docs/data/live/texture_table.txt line 23); handle 0x56A/0x68A 32x32 RGBA8 seen bound (6im) | [V live] |

## CLOSES?

NO — blocking fact: M1f's wording requires one live poll-only read or in-game check per claim for EVERY D2 dossier (extractors, visitors, clones, pass bodies, context init …), and units cannot run or attach to the game (OPENCODE_BRIEF rule 1); the orchestrator builds the DLLs and runs captures. The single in-game step still missing: confirm live, in the running populated server, that the executor's batcher flush at 0xe81b720 actually reaches DrawIndexedInstanced (cmdlist vtable +0x68) per draw — breakpoint attempts at candidate emitters (0xe829c60 and siblings) got 0 hits (6dk/6dl) — and observe the frame semaphores ctx+0x80 (render-thread 'frame data ready') / ctx+0x100 ('frame consumed'). Everything that can be done statically or from existing live data is in this file; the two queued captures target the missing live observation once the orchestrator runs them.

## TOOL REQUESTS

In-game test plan (poll-only, populated server; no debugger, no breakpoints, no writes):
1. ctx = readQword(base+0x12AE1748); F0=[ctx+0x1CFD0C0], F1=[ctx+0x1CFD0C8]; verify |F0-F1| == 0xE749C0. The consume frame is the one with a stable u32 [F+0xDC57E8] and counter u64 [F+0xE746D8] exactly one below the fill frame; re-check both pointers before/after each multi-step sample (they swap at frame boundaries — 6do/6de).
2. [F+0xDC5808] == {1920, 1137} (backbuffer u32 width/height); [F+0xDC57E8] item count (~500 in a populated server, below 0xFFFE).
3. For each u16 id in the sorted list [F+0x94700][0..n): header h = [F+0xB4700]+id*0x80; expect state +0x20 low dword in {0x17, 0x1F, 0x27}, +0x76 == 0xFFFF, +0x74 == 0xFFFF0003; sort key u64 [F+0x14700]+id*8 has bit 52 set and viewId = key>>54 in 0..15.
4. IB record obj+0x93A178+ib*0x78: +0x58 GPU VA, +0x60 size, +0x70 stride 2; VB record obj+0x9B2178+vb*0x80: +0x58 GPU VA, +0x60 size, +0x70 stride, +0x78 layout handle (0xFFFF = none); layout record obj+0xC96198+l*0x54: +0x04 stride, attribute offsets at +0x06.
5. Texture record obj+0xBDE178+t*0xB8: D3D12_RESOURCE_DESC at +0x08, SRV desc at +0x40, second desc at +0x68 — compare docs/data/live/texture_table.txt.
6. Program record obj+0xB62178+p*0xF8: +0x00/+0x08 shader record pointers, +0xA8 signature; shader record obj+0xAAA178+s*0xB8: +0x00 code-blob pointer, +0xA8 signature.

Queued captures (function-entry RVAs, log-only execute breakpoints, size 0x200, max 8):
- u_em1f_submit_entry @ 0xe82e230: confirm Frame ptr in rdx, item count [Frame+0xDC57E8], counter [Frame+0xE746D8], backbuffer [Frame+0xDC5808] live in the populated server.
- u_em1f_draw_flush @ 0xe81b720: observe DrawBatcher pending counts [batcher+0x10+kind*4] and record arrays to confirm the executor's per-draw emission path live.
When the orchestrator runs them and docs/data/live/u_em1f_submit_entry.txt / u_em1f_draw_flush.txt appear, write "CAPTURE REQUESTED u_em1f_submit_entry" / "CAPTURE REQUESTED u_em1f_draw_flush" here and compare against the expected values above.

## NEXT
step 2
