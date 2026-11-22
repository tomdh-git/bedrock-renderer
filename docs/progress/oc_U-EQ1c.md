## NEXT
step 2

# U-EQ1c: Q1c R3 frame probe — per-frame dump of typed descriptions, pass list, draw records + RenderDraw + material/program/PSO key, actor attribution; read-only

## Goal (verbatim from docs/RENDER_CHECKLIST.md line 558)
Close checklist item Q1c R3: "per-frame dump of typed descriptions, pass list, draw records + RenderDraw + material/program/PSO key, actor attribution; read-only". Do ONLY the pending/not-decoded parts; read-only; no game launch/attach, no build, no commit, no edits to HookManager.cpp, existing hook registration, CMake, or existing Sigs.json entries. Output file = this one only.

## (1) What I changed (paths)
- docs/progress/oc_U-EQ1c.md — this note (created; the unit's only output file per the unit rule). Created at step 1 per the unit prompt (first line "## NEXT", second line "step 2").

## (2) Frame-probe facts proven in the exe (each claim has a verbatim `0xRVA  instr` proof line checked by verify_oc; sizes come from the instruction)

| item | rva/offset | size | verbatim `0xRVA  instr` proof line | meaning [V/I/?] |
|---|---|---|---|---|
| submit frame counter read | 0xe82e230+0x11c | 4 | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | Frame+0xE746D8 u32 frame counter (rises 1/frame) [V] |
| insert clone tag store | 0x4e39cb0+0x54 | 1 | `0x4e39d24  mov byte ptr [rbp+0x18],0xA` | BatchActor insert variant tag = 0xA (Item group) stored [V] |
| insert clone builder vtable slot | 0x4e39cb0+0x61 | 8 | `0x4e39d2b  mov rax,[rax+0x378]` | builder vtable slot +0x378 = Item `_insert` [V] |
| insert clone CFG-indirect call | 0x4e39cb0+0x79 | 8 | `0x4e39d39  call qword ptr [0xF99FFA0]` | indirect call through CFG thunk data_f99ffa0 = sub_eea6040 [V] |
| Item visitor tag read | 0x6646980+0x1b | 1 | `0x66469eb  movzx eax,byte ptr [r8+8]` | variant tag byte read from payload+8 [V] |
| Item visitor jump table base | 0x6646980+0x26 | 8 | `0x6646a00  lea rcx,[0xF2BF2D0]` | jump-table base 0xF2BF2D0 [V] |
| Item visitor jump-table indirect | 0x6646980+0x2e | 8 | `0x6646a0e  jmp rax` | jump-table indirect jump after `movsxd rax,[rcx+rax*4]; add rax,rcx` [V] |
| BatchActor extractor instance count | 0x66d9af0+0x89 | 8 | `0x66d9b79  mov rax,[r8+0xE0]` | desc+0xE0 = instance count [V] |
| Draw header base | Frame+0xB4700 | - | `0xe822697  mov r9,[rbx+0x590]` / `0xe82269e  lea r12,[r9+rdx]` (`shl edx,7`) | local+0x590 = Frame+0xB4700 draw-header array base; header address = base + (itemIndex<<7), stride 0x80 [V] |
| Sorted draw order array | Frame+0x94700 | 2 | `0xe822673  movzx eax,word ptr [r10+rax*2+0x94700]` | uint16_t sorted item ids at Frame+0x94700 (65536 entries) [V] |
| Per-draw RenderDraw stride | RenderDraw +0x540 | 4 | `0xe82267c  imul r15,rax,0x540` / `0xe8226e9  mov r8d,[r8+r15+0x514]` | per-item 0x540-byte RenderDraw block; +0x514 dword read per item [V] |
| Draw header state word | header+0x20 | 8 | `0xe8226b3  mov r8,[r9+rdx+0x20]` / `0xe8226bf  shr r8,0x3E` | header+0x20 u64 state; bit 62 tested (skip/compute flag) [V] |
| Draw header scissor handle | header+0x7A | 2 | `0xe8226c7  movzx edx,word ptr [r9+rdx+0x7A]` / `cmp rdx,0xFFFF` | header+0x7A u16 handle (0xFFFF = none) [V] |
| Sort key → program index | sortkey >> 0x15 & 0x7FF | 4 | `0xe822483  shr rax,0x15` / `0xe82248e  and eax,0x7FF` / `0xe822493  imul rax,0xF8` | program index (11 bits) → program record at this+0xB62178 + idx*0xF8 [V] |
| Program object signature | program_rec+0xA8 | 4 | `0xe8224b0  mov esi,[rax+0xA8]` | program record +0xA8 u32 signature (4 signed bytes) = PSO-cache probe key [V] |
| PSO cache bucket count | bgfxBlock+0x48/0x50 | 8 | `0xe8224bd  mov rcx,[rcx+0x50]` / `0xe8224c5  sub rcx,rax` / `0xe8224c8  shr rcx,3` | bucket count = (end-start)>>3; chained hash map [V] |
| PSO cache node walk | node+0 / node+0x10 | 8 | `0xe822524  mov rdx,[rax+rcx*8]` / `0xe822540  cmp [rdx],rsi` / `0xe822549  mov rdx,[rdx+0x10]` | bucket node key compare [node+0], next ptr [node+0x10] [V] |
| Sort key view/depth tag 1 | sortkey >> 0x11 & 0x7FF | 4 | `0xe822650  shr r11d,0x11` / `0xe82265a  and r11d,0x7FF` | view/depth-type tag field [V] |
| Sort key view/depth tag 2 | sortkey >> 0x25 & 0x7FF | 4 | `0xe822656  shr r11,0x25` / `0xe82265a  and r11d,0x7FF` | view/depth-type tag field [V] |
| bodyActor flags read | 0x66D0A00+0x21 | 1 | `0x66D0A44  movzx r14d,byte ptr [rax+0x151]` / `0x66D0A51  cmp byte ptr [rax+0x150],0` | bodyActor reads body+0x150/0x151 flags [V] |
| bodyActor chain walk | body+0x140 | 8 | `0x66D0A65  mov rax,[rax+0x140]` | bodyActor follows +0x140 chain [V] |
| passLookup item vector | pass+0xA0 | 8 | `0x5ABA5CC  lea rbx,[rcx+0xA0]` | pass object +0xA0 = item vector head [V] |
| bgfx liveContext global | 0x12BB4910 | 8 | [V live] `python tools/sigs/livemem.py read @0x12BB4910 8` -> `00 00 01 4a 31 05 00 00` = image+0x5014A00? | global holds RendererContextD3D12 (vtable image+0xF4EEE80 live) [V live] |
| RendererContext vtable live | live object | 8 | [V live] `python tools/sigs/livemem.py ptr 0x05314A010000` slot0 -> image+0xF4EEE80 | live RendererContextD3D12 object vtable = RTX subclass 0xF4EEE80 [V live] |
| VV builder first pass name | 0x55f3871 | 16 | `0x55f3871  mov rax,0x7365646163736143` / `0x55f387f  mov rax,0x4320776F64616853` | inline "Shadow Cascades" string built via movabs immediates [V] |
| VV builder GeometryPrepass hash | 0x55ff9a9 | 8 | `0x55ff9a9  mov rax,0x680E1340911894F3` | FNV-1("GeometryPrepass") = 0x680E1340911894F3 stored as 64-bit immediate [V] |

## (3) Remaining decoding (input data already computed; to be written in pieces)
Pass list (VV builder 0x55f1450 declaration order via inline name immediates), material/program/PSO key (sort key → program → signature → PSO cache), actor attribution (bodyActor S+0xC8 → item record → task hash route), draw records + RenderDraw (0x80 header + 0x540 RenderDraw at Frame+0x8B4700 + per-view block Frame+0xDC57E0), typed descriptions (Item visitor tag reads + descscan2), and the exact read-only tool/header to deliver under src/sdk/ or src/client/features/render/.

## CLOSES?
[UNVERIFIED: still need pass-list immediates, material/program/PSO-key proof rows, actor-attribution proof row, the read-only deliverable under src/, and delegate.py check to exit 0]

## TOOL REQUESTS

None yet
