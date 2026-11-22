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
