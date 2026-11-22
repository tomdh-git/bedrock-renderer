## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from an rdis listing and passes tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown | [V live] confirmed by capture bytes / live read.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md (pass-vector table: light records +0x648 stride 0x48, summary +0x800 stride 0x14, GameplayMetadata +0x498 stride 0x84, ShadowAtlasFrame +0x1C8 stride 0x50); docs/data/live/light_visitor.txt (tags 0/1/2/5 only, no tag 3/4 samples); docs/data/live/README.md (light visitor takes {desc,tag} in RDX); docs/data/live/_status.txt; docs/data/live/capture_requests.json (oc_u_er6_light_desc queued, state pending); docs/BGFX_MAP.md sections 6gq/6ih/6hi and 6w line 504; FrameBuilder.h LightGroupTag enum; Descriptions.h. Prior units r1-r37 carried [V] and are NOT re-proven per RETRY #1; this unit only (a) consolidates the proven rows, (b) adds the live-capture angle from the 2026-11-22 tool, and (c) reports CLOSES? honestly on the still-open parts.

## 1. Tag -> type / LightGroupTag and the tag-name conflict — RESOLVED [V] (carried from r1-r37, not re-proven this unit)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]<br>0x6640de6  jmp rax` | tag byte at variant+0x08; indirect dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) | [V] |
| tag 0 = Ambient | 1 | 0x53e3511 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc RenderLightAmbientDescription; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 = Directional | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc LightDirectionalDescription; entry 1 (0x66415b0) | [V] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2<br>0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; Light vslot 0x380 insert at 0x53e5fbf; clone 0x53e5910, srcloc GameplayMetadata; entry 2 (0x6640f1b); independently listed as Light tag 2 in BGFX_MAP.md 6w line 504 | [V] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3<br>0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert at 0x535a9c1; srcloc LightPointDescription; entry 3 (0x66410a0) | [V] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4<br>0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert at 0x535a6a0; srcloc ShadowAtlasFrameDescription; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 | - | RESOLVED [V]: `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 }`; producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; BGFX_MAP.md 6w line 504 agrees (Light group: 0 Ambient, 1 Directional, 2 GameplayMetadata) | [V] |

`0x6640dc4  movzx eax,byte ptr [rdx+8]`
`0x6640de6  jmp rax`
`0x53e3511  mov byte ptr [rbp+0x138],0`
`0x53709d4  mov byte ptr [rbp+0x18],1`
`0x53e5fb4  mov byte ptr [rbp-0x18],2`
`0x53e5fbf  mov rax,[rax+0x380]`
`0x535a9b7  mov byte ptr [rbp+0x278],3`
`0x535a9c1  mov rax,[rax+0x380]`
`0x535a696  mov byte ptr [rbp+0x278],4`
`0x535a6a0  mov rax,[rax+0x380]`

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (carried from r1-r37)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans].

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]<br>0x6640e8b  cmp rdx,[rsi+0x808]<br>0x6640eb4  add qword ptr [rsi+0x800],0x14<br>0x6641761  mov rdx,[rsi+0x800]<br>0x66417a2  add qword ptr [rsi+0x800],0x14<br>0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808 compared at 0x6640e8b); writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517 (all increment by 0x14); loads at 0x6640e84 / 0x6641761 | [V] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]<br>0x66416ff  call 0x675FB30<br>0x664145a  lea rcx,[rsi+0x648]<br>0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional (0x66416ff) and LightPoint (0x6641461) pass &end to grow-emplace 0x675FB30; per-draw clones 0x66ed5c0 / 0x670e27c / 0x6725579 do the same | [V] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090, 0x6640f7f | `0x6640f78  mov r12,[rdi+0x4A0]<br>0x6641090  add qword ptr [rdi+0x4A0],0x84<br>0x6640f7f  cmp r12,[rdi+0x4A8]` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84; load at 0x6640f78, cap compare at 0x6640f7f | [V] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V] |

`0x6640e84  mov rdx,[rsi+0x800]`
`0x6640e8b  cmp rdx,[rsi+0x808]`
`0x6640eb4  add qword ptr [rsi+0x800],0x14`
`0x6641761  mov rdx,[rsi+0x800]`
`0x66417a2  add qword ptr [rsi+0x800],0x14`
`0x6641517  add qword ptr [rsi+0x800],0x14`
`0x66416f8  lea rcx,[rsi+0x648]`
`0x66416ff  call 0x675FB30`
`0x664145a  lea rcx,[rsi+0x648]`
`0x6641461  call 0x675FB30`
`0x6640f78  mov r12,[rdi+0x4A0]`
`0x6641090  add qword ptr [rdi+0x4A0],0x84`
`0x6640f7f  cmp r12,[rdi+0x4A8]`
`0x66419c6  add qword ptr [rsi+0x1D0],0x50`

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?] (blocking fact, static angles exhausted)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative | [?] |
| pass+0x648 elements | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only | [?] |
| pass+0x4A0 elements | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only | [?] |
| pass+0x1D0 elements | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only | [?] |

Negative angles proven (NOT redone per RETRY #1; new angles tried this unit): whole-image `fld --r/--w` scans for all four offsets + begin cursors (0x7F8/0x650/0x498/0x1C8) show only the four writer cursor accesses plus stack/unrelated same-offset hits; endFrame full listing (sub_66232b0) contains none of the four offsets though it calls 0x5ABA5C0 3x; all ~200 `0x5ABA5C0` callers (xref.py shows 76 direct callers, all covered by fld) touch only stack locals or are other visitors; `rdis ptr 0x5aba5c0` (0 indirect slots) and `rdis imm 0x5aba5c0` (0 static data refs); grow path 0x675FB30 and shared case epilogue do cursor arithmetic only, never element reads; per-draw code 0x66ea3d0 appends u16 indices to the unrelated pass vector at +0x8A8 and reads none of the four cursors; descscan2 on GameplayMetadata case 0x6640f1b reads ONLY desc+0x00..+0x84 (description fields copied INTO the pass), NO reads of pass+0x4A0 or any pass offset; magic-multiplier imm scans (0xFFFF8E39 ÷0x48, 0xFFFFCCCD ÷0x14, 0xFFFF83E1 ÷0x84) are negative for consumers — every hit is inside known writers; lea register-relative scan (tools/sigs/lea_reg_find.py) for disp 0x800/0x648/0x4A0/0x1D0/0x7F8/0x650/0x498/0x4A8/0x1C8/0x1D8 found only writer sites and scattered unrelated .text hits — NO clean draining element read; one ambiguous hit 0x66286f9 `lea rdx,[rbx+0x650]` then `call 0x6622840` (reads 6 pointers +0x0..+0x28, refcounts them) — rbx=[rbp+0x19D0] not proven to be the pass object, and +0x650 is the light-record END cursor not an element [UNVERIFIED: 0x66286f9 is rbx the pass object and is 0x6622840 a light-vector drain?]. BGFX_MAP.md 6gq/6ih/6w/6hi name no consumer of the four vectors (6ih line 2041 leaves consumers open [?]; line 1843-1844: Sky vector at pass+0x548 also readerless — same blocker for all pass vectors). Static analysis is exhausted for consumers: a live read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 is required, and this toolset provides none (no debugger/Cheat Engine access; livecap entry captures observe description bytes only, not pass-vector reads).

## 4. Live capture (new 2026-11-22 tool) — queued, result awaited

`python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)" [V static, request.py result]. The request oc_u_er6_light_desc is already queued (state pending) at the light-visitor entry already proved for this item: visitor entry 0x6640d80, size 0x100 (256), max 6, why "R6: light-visitor entry producer capture. RDX = desc pointer ... Dump desc bytes to confirm tag 3 (LightPoint, 0x108 B) and tag 4 (ShadowAtlasFrame, 0x50 B) field sizes/runtime values vs Descriptions.h layouts; ret= names the visitor caller chain." [V capture_requests.json]. Results, when produced, land in docs/data/live/oc_u_er6_light_desc.txt as lines `REG=value hit=N ret=0xRVA <bytes>`.

What the live data CAN add (per tools/livecap/README.md visitor kind: line = tag descptr hex): description bytes per tag at visitor entry (RDX = desc pointer, per the 2026-11-15 README correction) -> confirm tag 3 / tag 4 field sizes and runtime values vs Descriptions.h layouts; ret= at entry names the visitor caller chain [V live when run]. Note: light_visitor.txt already carries tags 0/1/2/5 (no tag 3/4 samples yet), so tag-3/tag-4 bytes are genuinely new.

What it CANNOT add (it is not a write-watch): it observes description bytes at visitor entry, never later reads of the pass vectors, so it CANNOT locate consumers of pass+0x800/+0x648/+0x4A0/+0x1D0 — that needs a memory read/write watch on those element offsets. It also yields values only, never member names: no RTTI and no description member-name strings exist in the release exe, so description value names cannot come from live capture either. livemem is not an alternative: no static pass-object target address exists (0x5ABA5C0 = per-call ThreadLocalObject getter; rdis imm/ptr to 0x5aba5c0 = 0 refs/slots), so no livemem read was issued [V static].

## 5. Description field value names — UNKNOWN [?]

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | - | - | unknown [?]: the release exe has no RTTI and no description member-name strings; LightDescriptions.h / LightGameDescriptions.h type every field as mValue* placeholders with static_assert offsets only; live dumps carry description bytes only (sizes confirmed), never member names. Producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. | [?] |

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V negative]; whole-image fld scans, endFrame listing 0x66232b0, all 0x5ABA5C0 callers, rdis ptr/imm/xr indirect checks, magic-multiplier imm scans, descscan2, BGFX_MAP.md 6gq/6ih/6w/6hi, and the lea register-relative scan are all negative [V], and the pending live entry capture oc_u_er6_light_desc cannot install a read/write watch on the pass vectors nor give member names; no pass-object address exists for livemem [V static]. Description value names also remain unknown [?]: no RTTI or description member-name strings in the release exe; headers use mValue* placeholders; live desc bytes confirm sizes only, never names.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued (state pending) at visitor entry 0x6640d80 (size 0x100 = 256, max 6); do NOT re-add (request.py add rejects duplicate name). Result awaited in docs/data/live/oc_u_er6_light_desc.txt via `python tools/livecap/request.py result oc_u_er6_light_desc`; when it lands it can confirm tag-3/tag-4 description sizes/caller chain [V live] but cannot close the consumer blocker (no read/write watch available). Helper scripts: tools/sigs/lea_reg_find.py (input: exe + disp list -> output: `lea reg,[base+disp]` sites; general reusable; used this unit to scan all ten pass-vector displacements, found only writers + scattered unrelated hits; worth keeping).
