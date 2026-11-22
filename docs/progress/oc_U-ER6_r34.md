## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative to Minecraft.Windows.exe 1.26.62.01. Every `0xRVA  instr` line below is copied verbatim from an rdis listing. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown | [V live] confirmed by capture bytes / live read.

## NEW ANGLE TRIED THIS UNIT — live capture at visitor entry (queued; no result yet)
- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet (orchestrator has not run it)"; docs/data/live/oc_u_er6_light_desc.txt does not exist (directory listing). [V static]
- The capture oc_u_er6_light_desc is already queued at visitor entry 0x6640d80 (size 0x100, max 6; `request.py add` returned "already queued", exit 1). [V static: request.py output]
- What the live data CAN add when run: runtime description bytes/sizes per tag at visitor entry (RDX = desc pointer; docs/data/live/README.md: light visitor takes {desc,tag} in RDX) and the ret= caller chain for the visitor. [V live when run]
- What it CANNOT add (not a read/write watch): it observes description bytes at visitor entry, never later reads of pass+0x800/+0x648/+0x4A0/+0x1D0, so it cannot locate consumers; it yields values only, never description member names. livemem: the game is running but there is no static pass-object target address (0x5ABA5C0 = per-call ThreadLocalObject::get; rdis imm/ptr to 0x5aba5c0 = 0 refs/slots), so no livemem read was issued. [V static]
- Also re-checked the carried tag-0 store line: rdis dis 0x53e3500 decodes 0x53e3510 as `add dh,al` and 0x53e3512 as `test [rax],edi` — there is no `mov byte ptr [rbp+0x138],0` at 0x53e3511; the earlier-note address is not reproducible and is not restated. Tag 0 = Ambient still stands [V] via dispatch entry 0x6640de8 plus producer clone 0x53e2c00 (srcloc RenderLightAmbientDescription) carried from r1-r32.

## 1. Tag -> type / LightGroupTag — RESOLVED [V] (carried from r1-r32; not re-proven)
FrameBuilder.h enum (carried [V]): Ambient=0, Directional=1, GameplayMetadata=2, LightPoint=3, ShadowAtlasFrame=4, ServerGraphicsOverrideParameters=5, VoxelVolume=6, TransitioningVoxelVolume=7. group_visitors.md had tags 2/3 swapped and is superseded; BGFX_MAP.md 6w line 504 agrees (0 Ambient, 1 Directional, 2 GameplayMetadata).

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; indirect dispatch `jmp rax` via jump table 0xF2BF2B0 | [V] |
| tag 0 = Ambient | 1 | 0x6640de8 | `0x6640de8  mov ecx,0x9D0` | jump-table entry 0 = tag 0; Ambient producer clone 0x53e2c00 stores tag 0 with srcloc RenderLightAmbientDescription (carried [V]) | [V] |
| tag 1 = Directional | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | tag store = 1; Directional producer thin clone 0x5370960, srcloc LightDirectionalDescription; dispatch entry 1 (0x66415b0) | [V] |
| tag 2 = GameplayMetadata | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | tag store = 2; Light vslot 0x380 insert; GameplayMetadata clone 0x53e5910, srcloc GameplayMetadata; entry 2 (0x6640f1b); BGFX_MAP.md 6w line 504 lists Light tag 2 | [V] |
| tag 3 = LightPoint | 1 | 0x535a9b7, 0x535a9c1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | tag store = 3; light clone 0x53599d0 insert; srcloc LightPointDescription; entry 3 (0x66410a0) | [V] |
| tag 4 = ShadowAtlasFrame | 1 | 0x535a696, 0x535a6a0 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | tag store = 4; light clone 0x53599d0 insert; srcloc ShadowAtlasFrameDescription; entry 4 (0x6640ec1) | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — PROVEN [V] (carried from r1-r32)
Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans].

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4, 0x6641761, 0x66417a2, 0x6641517 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap cursor +0x808); Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 increment by 0x14; cap compared at 0x6640e8b | [V] |
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff, 0x664145a, 0x6641461 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); Directional 0x66416ff and Point 0x6641461 plus per-draw clones (0x66ed5c0, 0x670e27c, 0x6725579 carried) pass &end to grow-emplace 0x675FB30 | [V] |
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090, 0x6640f7f | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); tag-2 writer, stride 0x84 | [V] |
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); tag-4 writer, stride 0x50 | [V] |

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — NOT LOCATED [?]
| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 elements | - | - | - | no draining element read of the 0x14-byte summary vector anywhere in Minecraft.Windows.exe 1.26.62.01; end-cursor increment writes only; whole-image fld --r scans negative [V negative, carried r1-r32, not redone] | [?] |
| pass+0x648 elements | - | - | - | no draining element read of the 0x48-byte light-record vector anywhere in the exe; writes are grow-emplace calls to 0x675FB30 plus index-word stores only [V negative, carried] | [?] |
| pass+0x4A0 elements | - | - | - | no draining element read of the 0x84-byte GameplayMetadata vector anywhere in the exe; writes are end-cursor increments only [V negative, carried] | [?] |
| pass+0x1D0 elements | - | - | - | no draining element read of the 0x50-byte ShadowAtlasFrame vector anywhere in the exe; writes are end-cursor increments only [V negative, carried] | [?] |

Negative angles (carried, not re-proven): whole-image fld --r/--w scans for all four offsets plus begin cursors (0x7F8/0x650/0x498/0x1C8); endFrame listing sub_66232b0; all 0x5ABA5C0 callers (~200, xref 76 direct); rdis ptr/imm/xr to 0x5aba5c0 (0 indirect slots, 0 static data refs); magic-multiplier imm scans (0xFFFF8E39 div 0x48, 0xFFFFCCCD div 0x14, 0xFFFF83E1 div 0x84); descscan2 on GameplayMetadata case 0x6640f1b (reads only desc+0x00..+0x84 copied into the pass); BGFX_MAP.md 6gq/6ih/6w/6hi; vt/vcalls. All negative [V]. New angle this unit: the live capture at visitor entry above — it cannot watch writes to the pass vectors. What would close consumers: a live read/write watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0 (no tool available) or a live pass-object address for livemem (none exists).

## 4. Description field value names — UNKNOWN [?]
| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| description value names | - | - | - | unknown [?]: release exe has no RTTI and no description member-name strings; LightDescriptions.h/LightGameDescriptions.h type fields as mValue* placeholders with static_assert offsets only; live capture desc bytes confirm field sizes per tag at visitor entry but never member names. Producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4) are inference [I], not names. | [?] |

## CLOSES?
CLOSES? NO — single blocking fact: no draining element reader (consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments / grow-emplace + index-word records only, no pop/decrement, no element-indexed read) [V negative]; the one live-capture tool available (oc_u_er6_light_desc at visitor entry 0x6640d80, queued, result awaited) cannot install the read/write watch on the pass vectors that consumers require, and livemem has no pass-object target address [V static]. Also open: description value names are unknowable from this toolchain (no RTTI/name strings; live bytes give sizes, not names).

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued at visitor entry 0x6640d80 (size 0x100, max 6; `request.py add` returned "already queued", exit 1); result awaited in docs/data/live/oc_u_er6_light_desc.txt (`request.py result` -> "no result yet"). When run it can confirm runtime desc bytes/sizes per tag plus ret= caller chain [V live]; it cannot close consumers (no read/write watch) or value names (values only, no names). Helper scripts: None.
