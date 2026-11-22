## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from an rdis listing and passes tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown | [V live] confirmed by capture bytes / live read.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md (ThreadLocalObject::get; pass object = value at node+0x10); docs/functions/group_visitors.md (superseded on tags 2/3); docs/functions/light_game_descriptions.md (pass-vector table: light records +0x648 stride 0x48, summary +0x800 stride 0x14, GameplayMetadata +0x498 stride 0x84, ShadowAtlasFrame +0x1C8 stride 0x50); docs/data/live/light_visitor.txt (tags 0/1/2/5 only, no tag 3/4 samples); docs/data/live/README.md (light visitor takes {desc,tag} in RDX); docs/data/live/_status.txt; docs/data/live/capture_requests.json (absent — no such file; `request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"); docs/BGFX_MAP.md sections 6gq/6ih/6hi and 6w line 504; FrameBuilder.h LightGroupTag enum; Descriptions.h. Prior units r1-r38 carried [V] and are NOT re-proven per RETRY #1; this unit only (a) consolidates the proven rows, (b) tries NEW static angles on the consumer blocker (rdis callers/xr/fld, fn, walk), (c) uses the live-capture angle only for what it can add, and (d) reports CLOSES? honestly on the still-open parts.

## 1. Tag -> type / LightGroupTag and the tag-name conflict — RESOLVED [V] (carried from r1-r38, not re-proven this unit)

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

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (carried from r1-r38)

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

## 3. Consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?]

NEW static angles tried this unit (per RETRY #1), all failed to find a consumer:

- Sole visitor caller: `rdis xr 0x6640d80` returns exactly one xref and `rdis callers 0x6640d80` exactly one function — `sub_6640ae0+0x164 call 0x6640d80`. `sub_6640ae0` is the per-light insert wrapper (string "FrameBuilder - Insert light" at 0x6640c8d). After the visitor call it only tests [rbp+0x68] and conditionally calls `sub_77a2500`; it never reads pass+0x800/+0x648/+0x4A0/+0x1D0 element data, then returns:
  `0x6640c44  call 0x6640d80`
  `0x6640c4a  cmp byte ptr [rbp+0x68],1`
  `0x6640c4e  jne short 0x6640c68`
  `0x6640c50  mov r8,[rbp+0x60]`
  `0x6640c54  add r8,0x60`
  `0x6640c58  lea rcx,[0x1244fd00]`
  `0x6640c5f  mov rdx,rdi`
  `0x6640c62  call 0x77a2500`
  `0x6640c68  add rsp,0x108`
  `0x6640c73  ret`
- `sub_77a2500` (0x77a2500..0x77a2859) is a math/hash helper (magic multipliers 0xB2F4FC0794908CF3 / 0x3B9ACA00, 154 xrefs) — not a vector drain.
- Begin-cursor reads (`fld --r 0x7F8 / 0x498 / 0x1C8`, whole-image): hundreds-thousands of hits, all `[rbp+...]`/`[rsi+...]`/`[rdi+...]` stack or unrelated-struct locals, e.g. `0x2d1d18  mov eax,[rbx+0x7F8]`, `0x91d75  mov rcx,[rsi+0x498]`, `0x7e825  mov rdi,[rbp+0x1C8]`; none is traceable to the pass object. Every pass object in the exe comes from `0x5ABA5C0` (ThreadLocalObject::get); all its callers are the light/other visitors plus endFrame 0x66232b0, and endFrame reads none of the four offsets [V carried].
- Prior proven negatives (not re-run): `fld --r 0x800/0x648/0x4A0/0x1D0` = end-cursor writers only; lea register-relative scan = writers only; magic-multiplier imm scans negative; descscan2 tag-2 reads desc fields only [V carried]. No draining reader of those vectors found in the exe [V, from earlier review].

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 element read (drain consumer) | - | none located | - | no instruction reads [pass+0x800] as element data; `fld --r 0x800` whole-image = end-cursor loads/writes only (0x6640e84/0x6640eb4/0x6641761/0x6641517); sole visitor caller sub_6640ae0 does not drain [V] | [?] |
| pass+0x648 element read (drain consumer) | - | none located | - | no instruction reads [pass+0x648] as element data; grow-emplace writers only (0x66416ff/0x6641461 via 0x675FB30) [V] | [?] |
| pass+0x4A0 element read (drain consumer) | - | none located | - | no instruction reads [pass+0x4A0] as element data; end-cursor writer only (0x6641090) [V] | [?] |
| pass+0x1D0 element read (drain consumer) | - | none located | - | no instruction reads [pass+0x1D0] as element data; end-cursor writer only (0x66419c6) [V] | [?] |
| begin-cursor read tied to pass object (+0x7F8/+0x650/+0x498/+0x1C8) | - | none | - | `fld --r 0x7F8/0x498/0x1C8` hits are stack/other-struct locals (`0x2d1d18  mov eax,[rbx+0x7F8]`, `0x91d75  mov rcx,[rsi+0x498]`, `0x7e825  mov rdi,[rbp+0x1C8]`); none traces to 0x5ABA5C0 pass object [V scans, I tie] | [?] |

`0x6640c44  call 0x6640d80`
`0x6640c4a  cmp byte ptr [rbp+0x68],1`
`0x6640c4e  jne short 0x6640c68`
`0x6640c50  mov r8,[rbp+0x60]`
`0x6640c54  add r8,0x60`
`0x6640c58  lea rcx,[0x1244fd00]`
`0x6640c5f  mov rdx,rdi`
`0x6640c62  call 0x77a2500`
`0x6640c68  add rsp,0x108`
`0x6640c73  ret`
`0x2d1d18  mov eax,[rbx+0x7F8]`
`0x91d75  mov rcx,[rsi+0x498]`
`0x7e825  mov rdi,[rbp+0x1C8]`

## 4. Description field value names — UNKNOWN [?]

No RTTI or member-name strings for the description structs exist in the release exe; headers use `mValue*` placeholders; `descscan2` on the tag-2 case reads desc+0x00..+0x84 only [V]. The live capture `oc_u_er6_light_desc` (visitor entry 0x6640d80, size 0x100, max 6) can confirm description bytes/sizes per tag and name the caller chain via `ret=`, but capture bytes never carry member names; result not yet available (`request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)").

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | none | - | no name-bearing RTTI/strings for description fields; live desc bytes confirm sizes only, never names [V] | [?] |

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc (visitor entry 0x6640d80, size 0x100, max 6) — already queued (`request.py add` -> "already queued"); result pending in docs/data/live/. It can add tag-3/tag-4 description byte sizes and the visitor caller chain via `ret=`, but it cannot add consumers (no read/write watch) or member names.

## CLOSES?

CLOSES? NO — single blocking fact: consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are not located anywhere in the exe: all four offsets are write-only (end-cursor increments / grow-emplace), whole-image `fld --r` finds no element read, begin-cursor reads are not tied to the pass object, `sub_6640ae0` (sole visitor caller) does not drain, and no live write-watch is available to catch runtime consumers. Description field value names are also unknown (no RTTI/name strings; capture pending). Tag mapping [V] and writers [V] are proven; only the consumer blocker and value names remain open.
