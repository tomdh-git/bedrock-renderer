# UNIT U-EP3b — P3b Whole-frame takeover: drive the frame ourselves (L18 goal) — BGFX_MAP 8a

## NEXT
DONE

GOAL: Close checklist item P3b: "- [ ] P3b Whole-frame takeover: drive the frame ourselves (L18 goal) — BGFX_MAP 8a" (docs/RENDER_CHECKLIST.md line 547, currently `[ ]`). The line has no internally marked sub-parts, so the whole item is pending: verify BGFX_MAP section 8a ("Replacement seams", the five seams a whole-frame takeover is built on) with verbatim disassembly proof, and close what can be closed on disk (no builds, no game launch permitted this session).

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base. Every `0xRVA  instr` line below was taken from `rdis.exe <exe> dis 0x<RVA> <n>` on that exe and copied verbatim (two spaces after the address); the file passes `python tools/sigs/verify_oc.py`. Tags: [V] = seen in disassembly (cite RVA), [I] = inferred from structure or order, [?] = unknown. Nothing invented, nothing pasted raw.

VERSION NOTE: BGFX_MAP 8a/8c quote the PSO builder as 0xe81dc60; that is the 1.26.60.05 RVA. In 1.26.62.01 the builder is 0xe81e860 (+0xC00; 0xe81dc60 is mid-function of 0xe81da20 here, per 6cw/6ey). All proof below is 1.26.62.01.

## (1) Seam 1 — submit takeover: RendererContext::submit 0xe82e230, entered through the RTX override 0xe83d440 (slot 50 of the live vtable 0xF4EEE80)

| name | rva or offset | size | address (read/store site) | `0xRVA  instr` | meaning | tag |
| submit entry | 0xE82E230 | – | – | `0xE82E230  push rbp` | RendererContextD3D12::submit entry (vtable slot 50, size 0x4d91 [I per Sigs.json]) | [V] |
| signature: Frame* in rdx | 0xE82E26C | 8 | [rbp+0x16A8] = rdx | `0xE82E26C  mov [rbp+0x16A8],rdx` | rdx (Frame*) saved at submit entry → signature (rcx = RendererContext*, rdx = Frame*) | [V] |
| renderer-state guard | 0x19F88 | 4 | [rcx+0x19F88] | `0xE82E273  cmp dword ptr [rcx+0x19F88],5` | this+0x19F88 renderer-state int; <5 skips submit (jl 0xE832CEE) — upgrades the map's [I] to [V] | [V] |
| reset slot 60 | 0x1E0 | 8 | [rax+0x1E0] (rax = vtable) | `0xE82E297  mov rax,[rax+0x1E0]` | renderer vtable slot 60 = reset; called with rdx = Frame+0xDC5808 | [V] |
| backbuffer size | 0xDC5808 | – | rdx = rdi+0xDC5808 (lea) | `0xE82E28D  add rdx,0xDC5808` | Frame+0xDC5808 {u32 width, u32 height} passed to reset; live value 1920x1137 [V] | [V] |
| frame counter | 0xE746D8 | 4 | [rsi+0xE746D8] | `0xE82E34C  mov r9d,[rsi+0xE746D8]` | Frame+0xE746D8 u32 frame counter, +1 per frame | [V] |
| context pointer | 0x19F58 | 8 | [rdi+0x19F58] | `0xE82E353  mov rdx,[rdi+0x19F58]` | this+0x19F58 = context/resource-table object (role name [I] per 6e/6aj) | [I] |
| RTX override entry | 0xE83D440 | – | – | `0xE83D440  push r14` | RTX override of submit slot 50 on live vtable 0xF4EEE80 (slot index [I per 6al]; entry [V]) | [V] |
| override wraps base submit | 0xE83D4D6 | – | call site | `0xE83D4D6  call 0xE82E230` | override calls base RendererContext::submit after RT pipeline prep | [V] |
| queue wrapper | 0xCC9268 | – | [rsi+0xCC9268] | `0xE83D47C  lea rcx,[rsi+0xCC9268]`; `0xE83D491  call 0xE80ECB0` | this+0xCC9268 command-queue wrapper; queue idle-waited before RT work | [V] |
| RTX frame param block | 0xE748C8 | – | rdx = rdi+0xE748C8 | `0xE83D496  lea rdx,[rdi+0xE748C8]` | Frame+0xE748C8 camera/scene param block passed to RT pipeline build (0xE84BA30); role [I per 6al] | [I] |
| RTX frame param 16 bytes | 0xE746E0 | 16 | [rdx+0xE746E0] | `0xE83D4B5  movups xmm0,[rdx+0xE746E0]` | 16 bytes at Frame+0xE746E0 copied to RTX context+0x3C5642C | [V] |
| RTX frame param dword | 0xE74844 | 4 | [rdx+0xE74844] | `0xE83D4C3  movd xmm0,[rdx+0xE74844]` | Frame+0xE74844 dword copied to RTX context+0x3C56454 | [V] |
| PSO builder entry (62.01) | 0xE81E860 | – | – | `0xE81E860  push r15` | PSO builder entry in 62.01; the item's 0xe81dc60 is the stale 60.05 RVA (mid-function here per 6cw/6ey) | [V] |
| PSO key mask | 0xE81E8EC | – | imm | `0xE81E8EC  mov rsi,0x707007FFFFFF0FF`; `0xE81E8F6  and rsi,r13` | key.S = state & 0x0707007FFFFFF0FF (mask applied; bit map per 6ct/6fs) | [V] |

## (2) Seam 1 Frame contract — draw-record walk verified in Encoder::submit 0xbc60740

| name | rva or offset | size | address (read/store site) | `0xRVA  instr` | meaning | tag |
| per-handle table base | 0x93A178 | 8 | r14 = [this]+0x93A178; [rcx+0x93A178] | `0xE82E51C  add r14,rax`; `0xE82E51F  add r14,0x93A178`; `0xE821888  lea r8,[rcx+0x93A178]` | this+0x93A178 = per-handle record array base (submit); executor copies the same base into job+0x5D8 | [V] |
| per-handle record stride 0x78 | 0x78 | – | `imul rcx,rsi,0x78` | `0xE82EC74  imul rcx,rsi,0x78` | 0x78-byte per-handle record stride at this+0x93A178 | [V] |
| draw index read + CAS | 0xDC57E8 | 4 | [rcx+0xDC57E8] | `0xBC607C2  mov eax,[rcx+0xDC57E8]`; `0xBC607EA  lock cmpxchg [rcx+0xDC57E8],r14d`; `0xBC607FF  cmp edi,0xfffe`; `0xBC60805  jb short 0xBC6083F` | Frame+0xDC57E8 draw index (m_numRenderItems): read then CAS-allocated slot; cap 0xFFFE | [V] |
| per-view block table | 0xDC57E0 | 8 | [rcx+0xDC57E0] | `0xBC60852  mov r11,[rcx+0xDC57E0]` | [frame+0xDC57E0][viewSlot] per-view block pointer table | [V] |
| view slot | 0x6AC | 1 | [rsi+0x6AC] | `0xBC60859  movzx r14d,byte ptr [rsi+0x6AC]` | encoder+0x6AC view-slot byte used as [table+slot*8]; block+4 (`0xBC60865  mov r11d,[r11+4]`) = view's running draw index, stored to encoder+0x698 | [V] |
| sort mode byte | 0x1EAB1B2 | 1 | [r11+r14+0x1EAB1B2] | `0xBC60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]` | per-view sort-mode byte at ctx+0x1EAB080+view*0x140+0x132 (r11 = [0x12AE1748] = bgfx::Context*); feeds the sequence/depth/program key modes | [V] |
| sort keys | 0x14700 | 8 | [rcx+r14*8+0x14700] | `0xBC60991  mov [rcx+r14*8+0x14700],rax` | sort key u64 at Frame+0x14700+idx*8; view in bits 54-61, type tag 0x10/0x14/0x18 at 50-52; sequence via `0xBC608FC  lock xadd [r11+rdx*4+0x1EAAC60],ecx` (mode 1) | [V] |
| sorted list | 0x94700 | 2 | [rax+r14*2+0x94700] | `0xBC6099C  mov [rax+r14*2+0x94700],di` | u16 sorted item index at Frame+0x94700+idx*2 | [V] |
| draw header copy | 0xB4700 | 16 | [rax+rcx+0xB4700] | `0xBC60AB8  shl rcx,7`; `0xBC60B13  movaps [rax+rcx+0xB4700],xmm0`; `0xE821853  lea r8,[rax+0xB4700]`; `0xE82185A  mov [rbx+0x590],r8` | 0x80-byte draw header at Frame+0xB4700+idx*0x80 (stride 0x80 via shl 7; header = encoder+0x40 template verbatim, 8 movaps); executor also loads this base into job+0x590 | [V] |
| state word | 0xB4720 | 16 | [rax+rcx+0xB4720] | `0xBC60B03  movaps [rax+rcx+0xB4720],xmm2` | header+0x20 u64 state = encoder+0x60 (default 0x010000500000001f: `0xBC60B6E  mov rax,0x10000500000001f`; `0xBC60B78  mov [rsi+0x60],rax`) → PSO key input | [V] |
| RenderDraw base | 0x8B4700 | 8 | [r15+0x8B4700] | `0xBC60B1E  lea rcx,[r15+0x8B4700]` | RenderDraw array base at Frame+0x8B4700 | [V] |
| RenderDraw record stride 0x540 | 0x540 | – | `imul rcx,r14,0x540` | `0xBC60B33  imul rcx,r14,0x540` | 0x540-byte RenderDraw record stride | [V] |
| RenderBind memcpy | 0x140 | 0x518 | rdx = rbx = rsi+0x140 | `0xBC60B41  mov r8d,0x518`; `0xBC60B4A  call 0xEEC6EC0` | 0x518-byte memcpy (RenderBind block 0x514 + u32 bind hash at +0x654) from encoder+0x140 into Frame record | [V] |
| bind hash | 0x654 | 4 | [rsi+0x654] | `0xBC60AA5  mov [rsi+0x654],ecx`; `0xBC60A50  call 0xBC76610` | murmur2a bind hash over the 0x514-byte bind block | [V] |
| occlusion query | 0xBA | 2 | [rsi+0xBA] | `0xBC60A25  mov [rsi+0xBA],r9w` | header+0x7A u16 occlusion query id; `0xBC60A21  or byte ptr [rsi+0x67],0x40` sets state bit 62 (query draw) | [V] |

## (3) Seam 2 — per-draw veto/rewrite at the executor flush 0xe81b720 (called by executor 0xe821120)

| name | rva or offset | size | address (read/store site) | `0xRVA  instr` | meaning | tag |
| flush entry + executor call sites | 0xE81B720 | – | – | `0xE81B720  push r15`; `0xE822E4E  call 0xE81B720`; `0xE822E6B  call 0xE81B720` | DrawBatcher flush entry (the draw emitter: DrawInstanced / DrawIndexedInstanced / ExecuteIndirect); executor 0xe821120 flushes both batches on pipeline/state change | [V] |
| pending count | 0x10 | 4 | [rcx+r12*4+0x10] | `0xE81B736  mov esi,[rcx+r12*4+0x10]` | per-kind pending count at batcher+0x10+kind*4 (records at batcher+0x18+kind*8, e.g. `0xE81B779  mov rax,[rdi+r12*8+0x18]`) | [V] |
| record CBV #1 | 0x60 | 8 | [r15+0x60] | `0xE81B7B3  mov rax,[r15+0x60]`; `0xE81BA74  mov rax,[rax+0x60]` | record+0x60 GPU address → root param 2 via cmdlist vtable +0x130 (edx=2); same slot (+0x60/8 = slot 12) is the DrawInstanced target in the kind-0 path | [V] |
| record CBV #2 | 0x68 | 8 | [r15+0x68] | `0xE81B7BE  mov rax,[r15+0x68]` | record+0x68 → root param 3 (edx=3) | [V] |
| indexed draw | 0x158 | 8 | [rax+0x158] | `0xE81B84F  mov rax,[rax+0x158]` | cmdlist vtable slot 43 (0x158/8) IASetIndexBuffer | [V] |
| vertex buffers | 0x160 | 8 | [rax+0x160] | `0xE81BA55  mov rax,[rax+0x160]` | slot 44 (0x160/8) IASetVertexBuffers(0,5,views) | [V] |

## (4) Seam 3 — custom render item Encoder::submitCustom(view, fn, user), sort-key bit 53

| name | rva or offset | size | address (read/store site) | `0xRVA  instr` | meaning | tag |
| submitCustom entry | 0xBC61560 | – | – | `0xBC61560  push r15` | Encoder::submitCustom entry | [V] |
| fn word | 0x100 | 8 | [rsi+0x100] | `0xBC61645  mov [rsi+0x100],r8` | encoder+0x100 = render-thread function pointer (arg r8) | [V] |
| user word | 0x108 | 8 | [rsi+0x108] | `0xBC6164C  mov [rsi+0x108],r9` | encoder+0x108 = user data (arg r9) | [V] |
| key bit 53 mask | 0x20000000000000 | – | rcx = imm | `0xBC61697  mov rcx,0x20000000000000`; `0xBC616A1  or rcx,rax` | sort key bit 53 (0x20<<48) = custom-item class; `0xBC61749  shl rcx,7`; `0xBC61751  movaps [rax+rcx+0xB4700],xmm0` copies the custom header to Frame+0xB4700+idx*0x80 | [V] |

## (5) Seam 4 — pass control: task dispatch 0xe9002e0 (0x80-byte entries)

| name | rva or offset | size | address (read/store site) | `0xRVA  instr` | meaning | tag |
| task dispatch entry | 0xE9002E0 | – | – | `0xE9002E0  push rbp` | task-list dispatch entry (called once per frame from BgfxContext::endFrame 0xc270460 [I per 6cx]) | [V] |
| taskList begin | 0x0 | 8 | [rcx] | `0xE900366  mov r12,[rcx]` | taskList begin pointer | [V] |
| taskList end | 0x8 | 8 | [rcx+8] | `0xE900369  mov rdx,[rcx+8]` | taskList end pointer | [V] |
| entry stride | 0x80 | – | `sar rax,7` | `0xE900373  sar rax,7` | (end−begin)>>3 = entry count; entries are 0x80 bytes | [V] |
| entry state byte | 0x18 | 1 | [rcx+0x18] | `0xE900314  movzx eax,byte ptr [rcx+0x18]` | task entry+0x18 state byte (1 → early path) | [V] |

## (6) Seam 5 — whole-frame takeover (drive the frame ourselves)

Seam #5 has no implementation on disk. It is the composition of seams 1-4, all of which are verified above by [V] rows: a replacement submit walks Frame+0xB4700 draw headers (stride 0x80), allocates its slot by CAS at Frame+0xDC57E8 (cap 0xFFFE), emits sort keys at Frame+0x14700 and sorted indices at Frame+0x94700, writes RenderDraw records at Frame+0x8B4700 (stride 0x540), reads the per-view block table [Frame+0xDC57E0][viewSlot], backbuffer size at Frame+0xDC5808 (1920x1137 live) and frame counter at Frame+0xE746D8, and uses the context at this+0x19F58 with renderer-state guard this+0x19F88 and per-handle records at this+0x93A178 (0x78 stride). Per-draw veto/rewrite goes through the executor flush 0xe81b720; custom render-thread work goes through submitCustom key bit 53; pass add/remove/reorder goes through task dispatch 0xe9002e0. Nothing here drives a frame yet.

## What exists on disk now

- docs/progress/oc_U-EP3b.md — this note (created by this unit; no other output file)
- src/sdk/Sigs.json — appended ONE proven-new entry: RendererContextD3D12.submitRTX (0xE83D440, exactly 1 match in the 1.26.62.01 file). Existing sigs already cover RendererContextD3D12::submit 0xe82e230, Encoder::submit 0xbc60740, drawExecutor 0xe821120, drawFlush 0xe81b720, submitCustom 0xbc61560, taskDispatch 0xe9002e0, psoBuilder 0xe81e860, Frame::sort 0xbc61e20.
- src/sdk/mc/deps/bgfx/Frame.h, Encoder.h, View.h, d3d12/D3D12Context.h — already document every 8a Frame-contract constant (kDrawHeaders 0xB4700 stride 0x80, kItemCount 0xDC57E8 cap 0xFFFE, kSortedItems 0x94700, kSortKeys 0x14700, kRenderDraws 0x8B4700 stride 0x540, kBackbufferSize 0xDC5808, kFrameCounter 0xE746D8, Encoder kState 0x60, kCustomItem 0x100, SortKey::kCustomBit bit 53, D3D12Context table bases). No header edits needed.
- Not changed: HookManager.cpp or any existing hook registration, CMake, existing Sigs.json entries (only appended), no build run, no commit, no game launched or attached to.

## CLOSES?
CLOSES?: NO — BGFX_MAP 8a's five replacement seams are verified on disk by [V] rows above, and the headers/sigs already document them, but P3b's own wording ("drive the frame ourselves") is not met by anything on disk: no replacement submit implementation exists (no code, no enabled/built hook) and the item cannot be exercised in game this session (no builds, no launch permitted). Single blocking fact: the whole-frame takeover itself is unimplemented on disk; only its seams are mapped and verified.

## NEXT
DONE
