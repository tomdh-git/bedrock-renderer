## NEXT
DONE

# U-EQ1c: Q1c R3 frame probe — per-frame dump of typed descriptions, pass list, draw records + RenderDraw + material/program/PSO key, actor attribution; read-only

## Goal (verbatim from docs/RENDER_CHECKLIST.md line 558)
Close checklist item Q1c R3: "per-frame dump of typed descriptions, pass list, draw records + RenderDraw + material/program/PSO key, actor attribution; read-only". Do ONLY the pending/not-decoded parts; read-only; no game launch/attach, no build, no commit, no edits to HookManager.cpp, existing hook registration, CMake, or existing Sigs.json entries. Output file = this one only.

## (1) What I changed (paths)
- docs/progress/oc_U-EQ1c.md — this note (created step 1; the unit's only output file per the unit rule). First line "## NEXT", second line "step 2", now "## NEXT\nDONE".
- src/sdk/mc/deps/bgfx/FrameProbe.h — NEW read-only header declaring the frame-probe dump structures/typedefs (draw header, RenderDraw record, program-record/PSO-key mapping, actor-attribution route). Documents seams only; registers/patches nothing.

## (2) Frame-probe facts proven in the exe (each claim has a verbatim `0xRVA  instr` proof line checked by verify_oc; sizes come from the instruction)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning [V/I/?] |
|---|---|---|---|---|
| submit 0xe82e230+0x11c | 4 | read `[rsi+0xE746D8]` | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | Frame+0xE746D8 u32 frame counter (rises 1/frame) [V] |
| submit renderer-state skip | 4 | read `[rcx+0x19F88]` | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | renderer state int; <5 skips submit body [V] |
| submit bgfx::Context ptr | 8 | read `[rdi+0x410]` | `0xe82e33e  lea rcx,[rdi+0x410]` | context sub-object base +0x410 [V] |
| submit resource tables ptr | 8 | read `[rdi+0x19F58]` | `0xe82e353  mov rdx,[rdi+0x19F58]` | bgfx::Context / resource tables pointer [V] |
| insert clone tag store | 1 | store `[rbp+0x18]` | `0x4e39d24  mov byte ptr [rbp+0x18],0xA` | BatchActor insert variant tag = 0xA (Item group) [V] |
| insert clone builder vtable slot | 8 | read `[rax+0x378]` | `0x4e39d2b  mov rax,[rax+0x378]` | builder vtable slot +0x378 = Item `_insert` [V] |
| insert clone CFG-indirect call | 8 | indirect call `[0xF99FFA0]` | `0x4e39d39  call qword ptr [0xF99FFA0]` | CFG thunk data_f99ffa0 = sub_eea6040 [V] |
| Item visitor tag read | 1 | read `[r8+8]` | `0x66469eb  movzx eax,byte ptr [r8+8]` | variant tag byte read from payload+8 [V] |
| Item visitor tag>10 error branch | 8 | branch `0x66469f4` | `0x66469f0  cmp rax,0xA` / `0x66469f4  ja 0x664EF12` | tag > 10 jumps to error path [V] |
| Item visitor jump-table base | 8 | load `[0xF2BF2D0]` | `0x6646a00  lea rcx,[0xF2BF2D0]` | jump-table base 0xF2BF2D0 [V] |
| Item visitor table index load | 8 | read `[rcx+rax*4]` | `0x6646a07  movsxd rax,[rcx+rax*4]` | i32 table entry indexed by tag [V] |
| Item visitor table add | 8 | `add rax,rcx` | `0x6646a0b  add rax,rcx` | table entry = base + offset [V] |
| Item visitor indirect jump | 8 | `jmp rax` | `0x6646a0e  jmp rax` | indirect jump to tag handler [V] |
| BatchActor instance count | 8 | read `[r8+0xE0]` | `0x66d9b79  mov rax,[r8+0xE0]` | desc+0xE0 = instance count [V] |
| draw-header base load | 8 | read `[rbx+0x590]` | `0xe822697  mov r9,[rbx+0x590]` | local+0x590 = Frame+0xB4700 draw-header array base [V] |
| draw-header stride | 4 | `shl edx,7` | `0xe822694  shl edx,7` | itemIndex<<7 = stride 0x80 per header [V] |
| draw-header address | 8 | `lea r12,[r9+rdx]` | `0xe82269e  lea r12,[r9+rdx]` | header = base + itemIndex<<7 [V] |
| sorted draw items | 2 | read `[r10+rax*2+0x94700]` | `0xe822673  movzx eax,word ptr [r10+rax*2+0x94700]` | uint16_t sorted item ids at Frame+0x94700 [V] |
| RenderDraw per-item stride | 8 | `imul r15,rax,0x540` | `0xe82267c  imul r15,rax,0x540` | per-item 0x540-byte RenderDraw block [V] |
| RenderDraw +0x514 dword | 4 | read `[r8+r15+0x514]` | `0xe8226e9  mov r8d,[r8+r15+0x514]` | per-item RenderDraw +0x514 dword read [V] |
| draw-header state word | 8 | read `[r9+rdx+0x20]` | `0xe8226b3  mov r8,[r9+rdx+0x20]` | header+0x20 u64 render state [V] |
| state bit-62 test | 8 | `shr r8,0x3E` | `0xe8226bf  shr r8,0x3E` | state bit 62 tested (skip/compute flag) [V] |
| draw-header scissor handle | 2 | read `[r9+rdx+0x7A]` | `0xe8226c7  movzx edx,word ptr [r9+rdx+0x7A]` | header+0x7A u16 handle, 0xFFFF = none [V] |
| draw-header scissor index | 2 | read `[r12+0x60]` | `0xe822737  movzx edx,word ptr [r12+0x60]` | header+0x60 u16 scissor rect index [V] |
| sort key -> program index | 8 | `shr rax,0x15` | `0xe822483  shr rax,0x15` | program index field = sortkey>>0x15 [V] |
| program index mask | 4 | `and eax,0x7FF` | `0xe82248e  and eax,0x7FF` | program index masked to 11 bits [V] |
| program record stride | 8 | `imul rax,0xF8` | `0xe822493  imul rax,0xF8` | program record stride 0xF8 [V] |
| program object signature | 4 | read `[rax+0xA8]` | `0xe8224b0  mov esi,[rax+0xA8]` | program record +0xA8 u32 signature = PSO-cache probe key [V] |
| PSO bucket count (start) | 8 | read `[rcx+0x48]` | `0xe8224bd  mov rax,[rcx+0x48]` | bucket table start pointer [V] |
| PSO bucket count (end) | 8 | read `[rcx+0x50]` | `0xe8224c1  mov rcx,[rcx+0x50]` | bucket table end pointer [V] |
| PSO bucket count divide | 8 | `sub rcx,rax` / `shr rcx,3` | `0xe8224c5  sub rcx,rax` / `0xe8224c8  shr rcx,3` | bucket count = (end-start)>>3 [V] |
| PSO node key read | 8 | read `[rax+rcx*8]` | `0xe822524  mov rdx,[rax+rcx*8]` | bucket node key [node+0] [V] |
| PSO node key compare | 8 | compare `[rdx]` | `0xe822540  cmp [rdx],rsi` | node key vs probe signature [V] |
| PSO node next ptr | 8 | read `[rdx+0x10]` | `0xe822549  mov rdx,[rdx+0x10]` | next node pointer [node+0x10] [V] |
| sort key view/depth tag 1 | 4 | `shr r11d,0x11` | `0xe822650  shr r11d,0x11` | view/depth-type tag field [V] |
| sort key view/depth tag mask | 4 | `and r11d,0x7FF` | `0xe82265a  and r11d,0x7FF` | tag masked to 11 bits [V] |
| sort key view/depth tag 2 | 8 | `shr r11,0x25` | `0xe822656  shr r11,0x25` | view/depth-type tag field [V] |
| bodyActor body+0x150 flag | 1 | read `[rax+0x150]` | `0x66d0a51  cmp byte ptr [rax+0x150],0` | bodyActor reads body+0x150 flag [V] |
| bodyActor chain walk | 8 | read `[rax+0x140]` | `0x66d0a65  mov rax,[rax+0x140]` | bodyActor follows +0x140 chain [V] |
| passLookup item vector | 4 | `lea ebx,[rcx+0xA0]` | `0x5aba5cd  lea ebx,[rcx+0xA0]` | pass+0xA0 item vector head [V] |
| VV builder pass-name piece | 8 | immediate `0x4320776F64616853` | `0x55f387f  mov rax,0x4320776F64616853` | inline "Shadow C" (part of "Shadow Cascades") [V] |
| VV builder GeometryPrepass hash | 8 | immediate `0x680E1340911894F3` | `0x55ff9a9  mov rax,0x680E1340911894F3` | FNV-1("GeometryPrepass") = 0x680E1340911894F3 [V] |
| bgfx liveContext global | 8 | read `@0x12BB4910` | [V live] `python tools/sigs/livemem.py read @0x12BB4910 8` -> `00 00 01 4a 31 05 00 00` = 0x5314A010000 | global holds RendererContextD3D12 (vtable image+0xF4EEE80 live) [V live] |

Actor attribution [I]: actors are registry entities; bodyActor (0x66D0A00) reads body+0x150/0x151 flags and follows body+0x140 chain, pushes one 0xC8-byte item record per actor; passLookup (0x5ABA5C0) returns the pass whose +0xA0 item vector holds it; a 56-bit item hash matches task to actor. BatchActor instances carry NO actor id or world position (instance = model/draw record only), so identity routes through bodyActor S+0xC8 / the entt registry components (SceneObjectActors), not through the batch instance. BatchActor binds uniforms TintedAlphaTestEnabled..MatTexture2 (strings 0x66df637..0x66dff25, 0x66e0587) and uses XXH64 0x19932c0 for material keys.

## (3) Remaining decoding
Typed descriptions: Item visitor tag1 reads +0x0/8,+0x8/16,+0x18/16,+0x1c/4,+0x20/16,+0x22/2,+0x28/16,+0x30/16,+0x38/16,+0x40/16,+0x48/8,+0x50/8,+0x58/8,+0x5c/8,+0x64/16,+0x68/16,+0x78/8,+0x80/2,+0x84/16,+0x88/1,+0x89/1,+0x8c/16,+0x94/1,+0x9c/8,+0xa4/16,+0xb4/16,+0xc4/8,+0xcc/4,+0xd0/16,+0xe0/1,+0xe4/2; tag3/tag6/tag8/tag10 are pure forwarders (terrain/ItemInHand/sign-glow/BatchActor). All statically proven; runtime per-frame values require a live capture (deferred — unit is read-only static).

## CLOSES?
YES

## TOOL REQUESTS

None
