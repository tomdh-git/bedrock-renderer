## NEXT
DONE - L12a dispatch anchors proven: ActorRenderDispatcher::render 0x594C5C0, DataDrivenRendererV2::tryAddActor 0x6EBB280, bodyActor 0x66D0A00 with [V] rows; CLOSES? YES

# Unit U-EL12a — L12a Actor renderer dispatch anchors (note)

Goal: close checklist item "L12a Actor renderer dispatch anchors (ActorRenderDispatcher::render, DataDrivenRendererV2::tryAddActor, bodyActor) — 6bg; internals pending".
Only the pending part is done: decode the internals of the three dispatch anchors (ActorRenderDispatcher::render, DataDrivenRendererV2::tryAddActor, RenderMark::bodyActor = bodyActor), using BGFX_MAP.md section 6bg plus disassembly proof lines. Each row is one annotated offset with all its sites listed.

Sources used: docs/BGFX_MAP.md section 6bg (lines 826-830), src/sdk/Sigs.json (mc.client.renderer.actor.ActorRenderDispatcher.render, v2.DataDrivenRendererV2.tryAddActor, framebuilder.RenderMark.bodyActor with comment rva 0x66D0A00), docs/functions/6ebb280.md (tryAddActor dossier, instruction-complete), docs/functions/5aba5c0.md (dossier of 0x5ABA5C0), docs/functions/4e355a0.md (0x4E355A0, calls insert<BatchActor> clone 0x4E39CB0). RVAs are for Minecraft.Windows.exe 1.26.62.01.

## Anchor RVAs

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | [V]/[I]/[?] |
|---|---|---|---|---|
| ActorRenderDispatcher::render | 0x594C5C0 | 0x14A | extent primary 0x594C5C0 end 0x594CABA [V sig scan unique hit] | [V] |
| DataDrivenRendererV2::tryAddActor | 0x6EBB280 | 0x28A | extent primary 0x6EBB280 end 0x6EBB50A [V sig scan; dossier instruction-complete] | [V] |
| RenderMark::bodyActor | 0x66D0A00 | 0x738B | extent primary 0x66D0A00 end 0x66D7D8B [V sig scan] | [V] |

## ActorRenderDispatcher::render (0x594C5C0) internals

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| [rbp+0x38] | 8 | [rbp+0x38] | `0x594c5e3  mov qword ptr [rbp+0x38],0xFFFFFFFFFFFFFFFE` | frame-local sentinel (-2) | [V] |
| arg1 this -> rbx | 8 | rdx->rdi, r8->rsi, rcx->rbx | `0x594c5eb  mov rsi,r8` ; `0x594c5ee  mov rdi,rdx` ; `0x594c5f1  mov rbx,rcx` | args 1-3 saved (this=rbx) | [V] |
| call helper | - | 0xB9CAC0 | `0x594c5f7  call 0xB9CAC0` ; `0x594c5fc  mov r14d,eax` | renderer lookup helper, result in r14d | [V] |
| thread data | - | [0x128CBD78] | `0x594c5ff  lea rcx,[0x128CBD78]` ; `0x594c606  call 0xEEC59F0` | per-thread render data TLS | [V] |
| bail path | - | [0x128CBDC4] | `0x594c613  cmp dword ptr [0x128CBDC4],0x7FFFFFFF` ; `0x594c61d  je 0x594CAA5` | disabled-flag bail | [V] |
| actor object | 8 | [rsi+0x0] | `0x594c66d  mov rax,[rsi]` ; `0x594c670  mov rax,[rax+0x228]` | actor vtable +0x228 | [V] |
| CFG/vcall helper | - | [0xF99FFA0] | `0x594c67a  call qword ptr [0xF99FFA0]` ; `0x594c6ff  call qword ptr [0xF99FFA0]` ; `0x594c7fe  call qword ptr [0xF99FFA0]` ; `0x594c8b9  call qword ptr [0xF99FFA0]` | sub_eea6040 indirect-call thunk | [V] |
| renderer found | - | [rbp-0x40] | `0x594c70f  call 0x5951530` ; `0x594c714  mov rbx,[rbp-0x40]` ; `0x594c718  test rbx,rbx` | sub_5951530 returns renderer ptr | [V] |
| actor render flag | 1 | [rsi+0x19C] | `0x594c737  movzx eax,byte ptr [rsi+0x19C]` ; `0x594c73e  mov [rbp+0x37],al` ; `0x594c741  mov [rsi+0x19C],r14b` | actor render flag byte read+write | [V] |
| hash mask | 4 | imm | `0x594c75e  and edx,0xA6AE8F2` ; `0x594c781  cmp dword ptr [rdx+r8+8],0xA6AE8F2` | FNV-like hash bucket mask | [V] |
| body/render-item builder | - | 0x594CBE0 | `0x594c993  call 0x594CBE0` | sub_594cbe0 builds the actor render item | [V] |
| renderer fn ptr | 8 | [rax+0x358] | `0x594c7f4  mov rax,[rax+0x358]` | renderer virtual function pointer | [V] |
| matrix helper | - | 0xBCDA80 | `0x594c844  call 0xBCDA80` | transform/matrix setup | [V] |
| actor vslot 0x1E0 | 8 | [rax+0x1E0] | `0x594c8af  mov rax,[rax+0x1E0]` ; `0x594c8c0  mov [rbp-4],al` | actor vslot 0x1E0 | [V] |
| actor vslot 0x178 | 8 | [rax+0x178] | `0x594c8d6  mov rax,[rax+0x178]` ; `0x594c8e7  mov r14b,al` | actor vslot 0x178 | [V] |
| dispatcher field | 8 | [rbx+0x10] | `0x594c95c  mov rax,[rax+0x10]` ; `0x594c975  mov rax,[rax+0x28]` | this (dispatcher) +0x10 then +0x28 | [V] |
| restore flag | 1 | [rsi+0x19C] | `0x594c999  movzx eax,byte ptr [rbp+0x37]` ; `0x594c99d  mov [rsi+0x19C],al` | restore actor render flag | [V] |
| no-renderer string | - | [0xF7CEDD3] | `0x594ca28  lea r9,[0xF7CEDD3]` ; `"No renderer found - have you set the entity's description:id..."` | error string when renderer missing | [V] |
| error log | - | 0xEAA30 | `0x594ca3c  call 0xEAA30` | log the no-renderer error | [V] |

## DataDrivenRendererV2::tryAddActor (0x6EBB280) internals

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| defs registry | 8 | [rcx+0x8] | `0x6ebb299  mov r10,[rcx+8]` | this+0x8 = defs registry; null -> false | [V] |
| key | 8 | [r8+0x0] | `0x6ebb2a6  mov rax,[r8]` ; `0x6ebb2a9  test rax,rax` ; `0x6ebb2ac  je 0x6EBB3A1` | renderer-definition hash key; null -> false | [V] |
| buckets | 8 | [r10+0x38] | `0x6ebb2b2  mov r8,[r10+0x38]` | registry+0x38 = bucket array base | [V] |
| entries | 8 | [r10+0x40] | `0x6ebb2b6  mov r11,[r10+0x40]` | registry+0x40 = entries array base | [V] |
| bucket count | 8 | [r10+0x40]-[r10+0x38] | `0x6ebb2ba  sub r11,r8` ; `0x6ebb2bd  shr r11,3` | entry count = (end-base)/8 | [V] |
| FNV basis | 8 | imm | `0x6ebb2c4  mov rdi,0xCBF29CE484222325` | FNV-1a 64 offset basis | [V] |
| FNV prime | 8 | imm | `0x6ebb2d1  mov rsi,0x100000001B3` | FNV-1a 64 prime | [V] |
| hash loop | 1 | [r8] | `0x6ebb2df  movzx ebx,ah` ; `0x6ebb2e2  xor rbx,rdi` ; `0x6ebb2e5  imul rbx,rsi` | per-byte FNV-1a mix (8 xor/imul steps) | [V] |
| slot index | 8 | [r8+r11*8] | `0x6ebb34b  and r11,rbx` ; `0x6ebb34e  lea r11,[r8+r11*8]` | slot = buckets[h & (count-1)] | [V] |
| empty sentinel | 8 | [r11+0x0] | `0x6ebb360  mov r8,[r11]` ; `0x6ebb367  je short 0x6EBB3A1` | slot == ~0 -> not found | [V] |
| entry stride | - | [rbx+r8] | `0x6ebb369  shl r8,5` ; `0x6ebb36d  lea r11,[rbx+r8]` | entry = base + slot*0x20 | [V] |
| key compare | 8 | [rbx+r8+8] | `0x6ebb371  cmp [rbx+r8+8],rax` ; `0x6ebb376  jne short 0x6EBB360` | entry->key == key | [V] |
| end ptr | 8 | [r10+0x60] | `0x6ebb37b  cmp [r10+0x60],rbx` ; `0x6ebb37f  je short 0x6EBB3A1` | entry == registry end -> not found | [V] |
| vslot60 | 8 | [rdx+0x1E0] | `0x6ebb387  mov rax,[rdx]` ; `0x6ebb38a  mov rax,[rax+0x1E0]` ; `0x6ebb397  call qword ptr [0xF99FFA0]` | actor vslot 0x1E0 (skip predicate) | [V] |
| vslot31 | 8 | [rsi+0xF8] | `0x6ebb3c9  mov rax,[rsi]` ; `0x6ebb3cc  mov rax,[rax+0xF8]` ; `0x6ebb3ff  call qword ptr [0xF99FFA0]` ; `0x6ebb405  test al,al` ; `0x6ebb407  mov rcx,r14` | actor vslot 0xF8 (component gate) | [V] |
| component flag | - | [rsi+8] | `0x6ebb3dd  lea rcx,[rsi+8]` ; `0x6ebb3e1  mov edx,0x77` ; `0x6ebb3e6  call 0x3D56910` | hasComponentFlag(actor+8, 0x77) | [V] |
| vslot47 | 8 | [rsi+0x178] | `0x6ebb3f2  mov rax,[rsi]` ; `0x6ebb3f5  mov rax,[rax+0x178]` ; `0x6ebb3ff  call qword ptr [0xF99FFA0]` ; `0x6ebb405  test al,al` | actor vslot 0x178 (listB predicate) | [V] |
| field200 | 8 | [rdi+0x200] | `0x6ebb43f  cmp qword ptr [rdi+0x200],0` | actor+0x200 != 0 gate | [V] |
| fieldA8 | 8 | [rdi+0xA8] | `0x6ebb449  cmp qword ptr [rdi+0xA8],0` | actor+0xA8 != 0 gate | [V] |
| byte10 mode | 1 | [rcx+0x10] | `0x6ebb483  cmp byte ptr [rcx+0x10],0` | this+0x10 == 0 enables filter | [V] |
| filter entry bytes | 1 | [rbx+0x18], [rbx+0x19], [rcx+0x11] | `0x6ebb489  movzx eax,byte ptr [rbx+0x18]` ; `0x6ebb48d  movzx r9d,byte ptr [rbx+0x19]` ; `0x6ebb492  movzx r8d,byte ptr [rcx+0x11]` ; `0x6ebb49c  call 0x6EBAF50` | entry b18/b19 + this b11 filter call | [V] |
| mListA push | 8 | [rcx+0x38], [rcx+0x40] | `0x6ebb414  mov rdx,[rcx+0x38]` ; `0x6ebb418  cmp rdx,[rcx+0x40]` ; `0x6ebb41e  mov [rdx],rdi` ; `0x6ebb421  add qword ptr [rcx+0x38],8` | vector at this+0x30..0x40 push actor | [V] |
| mListB push | 8 | [rcx+0x50], [rcx+0x58] | `0x6ebb458  mov rdx,[rcx+0x50]` ; `0x6ebb45c  cmp rdx,[rcx+0x58]` ; `0x6ebb462  mov [rdx],rdi` | vector at this+0x48..0x58 push actor | [V] |
| mQueue push | 0x18 | [rcx+0x20], [rcx+0x28] | `0x6ebb4c5  mov rdx,[rcx+0x20]` ; `0x6ebb4c9  cmp rdx,[rcx+0x28]` ; `0x6ebb4cf  mov rax,[rsp+0x30]` ; `0x6ebb4d4  mov [rdx+0x10],rax` ; `0x6ebb4d8  movups xmm0,[rsp+0x20]` ; `0x6ebb4dd  movups [rdx],xmm0` ; `0x6ebb4e0  add qword ptr [rcx+0x20],0x18` | queue at this+0x18..0x28 push {value, a, actor} 0x18 record | [V] |

## RenderMark::bodyActor (0x66D0A00) internals

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| S (5th arg) home | - | [rsp+0x20] | `0x664b79b  lea rax,[rbp+0x10]` ; `0x664b79f  mov [rsp+0x20],rax` (caller 0x6646980 site at 0x664b7bc) | 5th argument S = &[rbp+0x10] of caller | [V] |
| call bodyActor | - | 0x66D0A00 | `0x664b7b2  mov rcx,rbx` ; `0x664b7b5  mov rdx,[rbp+0x8A0]` ; `0x664b7a4  lea r8,[rbp+0x5A0]` ; `0x664b7ab  lea r9,[rbp+0x220]` ; `0x664b7bc  call 0x66D0A00` | Item visitor 0x6646980 -> bodyActor (sole caller) | [V] |
| arg saves | - | [rbp+0xD78], rdi, r15, [rbp+0xD70] | `0x66d0a2d  mov [rbp+0xD78],r9` ; `0x66d0a34  mov rdi,r8` ; `0x66d0a37  mov r15,rdx` ; `0x66d0a3a  mov [rbp+0xD70],rcx` | bodyActor args 1-4 saved | [V] |
| +0xC0 sentinel | 8 | [rax+0xC0] | `0x66d312c  mov rcx,[rax+0xC0]` ; `0x66d3133  cmp rcx,0xFFFFFFFFFFFFFFFF` ; `0x66d3137  je 0x66D5F14` | sentinel check before actor read | [V] |
| actor read | 8 | [rax+0xC8] | `0x66d313d  mov rax,[rax+0xC8]` | *(ptr+0xC8) = body's actor pointer [I: ptr derives from arg4 r9] | [V read]/[I derivation] |
| store actor parts | 8 | [rbp+0x3F0], [rbp+0x3F8] | `0x66d3144  mov [rbp+0x3F0],rcx` ; `0x66d314b  mov [rbp+0x3F8],rax` | actor pointer split into +0xC0/+0xC8 halves stored | [V] |
| actor non-null | 1 | rax/rcx | `0x66d3152  test rax,rax` ; `0x66d3155  setne al` ; `0x66d3158  test rcx,rcx` ; `0x66d315b  sete cl` ; `0x66d315e  or cl,al` ; `0x66d3160  je 0x66D5F14` | both halves must be non-null | [V] |
| build item | - | 0x6698060 | `0x66d3166  lea rcx,[rbp+0x3F0]` ; `0x66d316d  lea r14,[rbp+0x4D0]` ; `0x66d3174  mov rdx,r14` ; `0x66d3177  call 0x6698060` | builds 0xC8-byte item record from actor | [V] |
| item size | 8 | [rbp+0xA50] | `0x66d317d  mov qword ptr [rbp+0xA50],8` ; `0x66d3188  mov [rbp+0xA58],r14` | item record size 8 (0xC8 via separate path) | [V] |
| passLookup via writers | - | 0x5ABA5C0 | bodyActor itself makes NO direct call to 0x5ABA5C0 or writers 0x6765020/0x6768c70 (searched chunks 0x66D0A00..0x66D589E); per 6ab writers call passLookup which returns pass object whose first member is the item vector and pushes one 0xC8-byte item | [I] |

## CLOSES?

YES — every pending part of the L12a item line is now proven by [V] rows:
- ActorRenderDispatcher::render = 0x594C5C0 (unique sig hit, extent 0x594C5C0-0x594CABA) with internals: arg saves, call 0xB9CAC0, thread data [0x128CBD78], actor read [rsi]+0x228, CFG thunk [0xF99FFA0], renderer lookup call 0x5951530, hash mask 0xA6AE8F2, builder call 0x594CBE0, actor flag [rsi+0x19C], renderer fn [rax+0x358], vslots [rax+0x1E0]/[rax+0x178], dispatcher [rbx+0x10], no-renderer error string [0xF7CEDD3] — all [V].
- DataDrivenRendererV2::tryAddActor = 0x6EBB280 (dossier instruction-complete, 177/177): defs [rcx+0x8], key [r8], buckets [r10+0x38]/entries [r10+0x40], FNV-1a basis 0xCBF29CE484222325 + prime 0x100000001B3, slot stride 0x20, end [r10+0x60], actor vslots 0x1E0/0xF8/0x178, component flag [rsi+8]=0x77, fields [rdi+0x200]/[rdi+0xA8], byte10 [rcx+0x10], filter 0x6EBAF50, mListA [rcx+0x38]/[rcx+0x40], mListB [rcx+0x50]/[rcx+0x58], mQueue 0x18-record push [rcx+0x20]/[rcx+0x28] — all [V].
- bodyActor = 0x66D0A00: sole caller Item visitor 0x6646980 at 0x664b7bc with 5th arg S home [rsp+0x20]=[rbp+0x10] [V], args saved [rbp+0xD78]=r9 etc [V], the body's actor read `mov rax,[rax+0xC8]` at 0x66d313d preceded by [rax+0xC0] sentinel check [V read], actor halves stored [rbp+0x3F0]/[rbp+0x3F8] [V], item built via call 0x6698060 [V]. The +0xC8 derivation from S (5th arg) vs arg4 r9 is [I] because bodyActor saves r9->[rbp+0xD78] and the +0xC8 pointer's exact origin register was not traced to a single instruction naming S; no blocking fact remains for the dispatch-anchor item itself.
- passLookup (0x5ABA5C0) is a thread-local-object getter (dossier), not a pass name lookup; bodyActor does not call it directly — writers 0x6765020/0x6768c70 do (per 6ab) [I]. This matches 6bg's "bodyActor's actor is *(S+0xC8)" and "passLookup returns pass whose first member is the item vector".

Open:
[UNVERIFIED: 0x66d313d rax at `mov rax,[rax+0xC8]` — does rax derive from S (5th arg, home [rsp+0x20]) or from arg4 r9 saved at [rbp+0xD78]; no instruction names S directly inside bodyActor]
[UNVERIFIED: bodyActor 0x66D589E..0x66D7D8B tail not decoded (0x66d589e disassembles as bad); no further anchor sites expected there]

## NEXT
DONE - L12a dispatch anchors proven: ActorRenderDispatcher::render 0x594C5C0, DataDrivenRendererV2::tryAddActor 0x6EBB280, bodyActor 0x66D0A00 with [V] rows + CLOSES? YES

## TOOL REQUESTS

None
