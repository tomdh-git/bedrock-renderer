## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; exe never launched; every `0xRVA  instr` line copied verbatim from verified listings. Rows marked carried re-quote oc_U-ER6_r1-r11 lines that passed verify_oc 83/83.

Input data (read fully, not regenerated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/data/live/_status.txt; docs/progress/capture_requests.json; docs/BGFX_MAP.md sections 3/6g/6w; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum, lines 79-88).

## 1. Tag dispatch and LightGroupTag mapping — resolved [V] (carried, not re-run)

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| tag byte at variant+0x08 | 1 | 0x6640dc4, 0x6640de6 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08 loaded; indirect jump via jump table 0xF2BF2B0 (0=Ambient 0x6640de8, 1=Directional 0x66415b0, 2=GameplayMetadata 0x6640f1b, 3=LightPoint 0x66410a0, 4=ShadowAtlasFrame 0x6640ec1, 5=ServerGraphicsOverrideParameters 0x66417af, 6=VoxelVolume 0x664187d, 7=TransitioningVoxelVolume 0x6641524) [V] | [V]
| Ambient tag store | 1 | 0x53e3511 | `0x53e3511  mov byte ptr [rbp+0x138],0` | producer clone 0x53e2c00 stores tag 0; JT entry 0 [V] | [V]
| Directional tag store | 1 | 0x53709d4 | `0x53709d4  mov byte ptr [rbp+0x18],1` | thin clone 0x5370960 stores tag 1; JT entry 1 [V] | [V]
| GameplayMetadata tag store | 1 | 0x53e5fb4, 0x53e5fbf | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | clone 0x53e5910 stores tag 2, insert through Light vslot 0x380; JT entry 2 [V] | [V]
| LightPoint / ShadowAtlasFrame tag store | 1 | 0x535a9b7, 0x535a9c1, 0x535a9ce, 0x535a696, 0x535a6a0 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]`<br>`0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | clone 0x53599d0 stores tag 3 (LightPoint) or 4 (ShadowAtlasFrame) at [rbp+0x278] before each vslot-0x380 insert; JT entries 3/4 [V] | [V]
| LightGroupTag enum (FrameBuilder.h:79-88) | - | FrameBuilder.h:79-88 | - | Ambient=0, Directional=1, GameplayMetadata=2, LightPoint=3, ShadowAtlasFrame=4, ServerGraphicsOverrideParameters=5, VoxelVolume=6, TransitioningVoxelVolume=7 [V]; producer tag stores + __FUNCSIG__ srclocs prove tag 2=GameplayMetadata and tag 3=LightPoint -> FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2, GameplayMetadata@3) and is superseded [V] | [V]

## 2. Pass-vector end-cursor writes — proven [V] (carried, not re-run)

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | 0x6640e84, 0x6640e8b, 0x6640eb4 (Ambient), 0x6641761, 0x66417a2 (Directional), 0x6641517 (Point) | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary vector (cap +0x808); Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 increment it; writes are end-cursor increments only — no pop/decrement and no element-indexed read of this vector anywhere in the exe [?] | [V]
| pass+0x808 cap cursor | 8 | 0x6640e8b | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary-vector cap cursor compared against end +0x800 [V] | [V]
| pass+0x648 end cursor | 8 | 0x66416f8, 0x66416ff (Directional), 0x664145a, 0x6641461 (Point) | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648, end +0x650); grow-emplace helper 0x675FB30 receives &end; no element read [V] | [V]
| pass+0x650 end cursor | 4 | 0x6641729, 0x6641735, 0x6641738 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; element index derived as (end - begin)/0x48 - 1 (shr 3 then multiply by inverse of 0x48) [V] | [V]
| pass+0x4A0 end cursor | 8 | 0x6640f78, 0x6641090 (tag 2) | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498, cap +0x4A8); tag-2 write, stride 0x84 [V] | [V]
| pass+0x4A8 cap cursor | 8 | 0x6640f7f | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata cap cursor [V] | [V]
| pass+0x1D0 end cursor | 8 | 0x66419c6 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8, cap +0x1D8); tag-4 write, stride 0x50 [V] | [V]

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not found [?]

No draining reader (element consumer) of any of the four vectors exists anywhere in Minecraft.Windows.exe 1.26.62.01. Whole-image `rdis fld --r/--w` scans for 0x800/0x648/0x4A0/0x1D0 and for begin cursors 0x7F8/0x650/0x498/0x1C8 return only the cursor writes in section 2. No element-indexed read (`[pass + cursor + index*stride]`) of any of the four vectors exists; every write is an end-cursor increment, no pop/decrement [V negative]. The consumer absence is noted in the meaning of each row above, so no duplicate offset rows are added.

## 4. Description field reads — offsets/sizes [V], names [?] (carried)

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| ShadowAtlasFrame desc fields (tag 4) | 16 | 0x6640ec1, 0x6640ecb, 0x6640ed6, 0x6640ee3, 0x6640f01, 0x66418f0 | `0x6640ec1  movups xmm6,[rsi]`<br>`0x6640ecb  movups xmm7,[rsi+0x10]`<br>`0x6640ed6  movups xmm8,[rsi+0x20]`<br>`0x6640ee3  movups xmm9,[rsi+0x30]`<br>`0x6640f01  mov rcx,[rsi+0x48]`<br>`0x66418f0  mov rbx,[rsi+0x40]` | tag-4 description reads four 16-byte blocks +0x00..+0x30 and a ptr pair +0x40/+0x48; description size 0x50 [V]. Same descscan2-proven pattern for LightAmbient (0x18), LightDirectional (0x24), GameplayMetadata (0x84), LightPoint (0x108) in oc_U-ER6_r1-r5. Field VALUES are visible at runtime; field NAMES are not [?]. | [V]

## 5. Live description bytes [V live] (light_visitor.txt)

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| live desc dumps | - | docs/data/live/light_visitor.txt lines 3-8 | - | tag 5 descptr 14AA80 (ServerGraphicsOverride, stride 0xB00), tag 0 descptr 14A5B8 (Ambient, size 0x18, first 16 bytes zero), tag 1 descptr 14A400 (Directional, vec4(1,1,1,1) at +0x00, size 0x24), tag 2 descptr 14A5A0 (GameplayMetadata, size 0x84, two samples) — bytes confirm sizes only, never member names; NO tag 3 (LightPoint) or tag 4 (ShadowAtlasFrame) description bytes exist in any capture [V live] | [V live]

## 6. Description value names — unknown [?]

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| description member names | - | - | - | the release exe has no RTTI and no description member-name strings; headers type the fields as mValue* placeholders with static_assert offsets only; light_visitor.txt [V live] carries bytes for tags 0/1/2/5 but never names, and no tag 3/4 bytes exist in any capture -> all description value names unknown [?] | [?]

## 7. New angles tried this unit — all negative

- `python tools/livecap/request.py result oc_u_er6_light_desc` -> "no result yet"; capture state=pending in docs/progress/capture_requests.json (4 pending: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc = limit reached, no new add allowed) [shell]. Entry sampling dumps RDX=desc bytes and ret=caller chain only; it cannot install a read/watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so even when run it cannot find the consumers [stated limitation, oc_U-ER6_r7/r8].
- `livemem.py status` -> game running pid 13452, but 0x5ABA5C0 is ThreadLocalObject::get (a function); `rdis imm 0x5aba5c0` = 0 static data references, so no pass-object runtime address exists statically; livemem cannot scan or loop over ranges -> no livemem read target [V live status]. docs/data/live/_status.txt: DONE t=120; oc_u_er6_light_desc not listed.
- Static angles carried from oc_U-ER6_r1-r11 (not re-run, all [V]): whole-image `rdis fld --r/--w` scans for 0x800/0x648/0x4A0/0x1D0 and begin cursors -> only cursor writes; endFrame listing (0x66232b0) touches none of the four offsets although it calls 0x5ABA5C0 3x; all ~200 `0x5ABA5C0` callers enumerated via `rdis xr`, none drain; `rdis ptr`/`imm`/`xr` on 0x5aba5c0 negative; `sub_5aba6d0` vector-grow callers (xr = 200) all grow-only; shared case epilogue 0x66447a0..0x66447d1 does frame restore only, and index arithmetic `mov eax,[rsi+0x1D0]; sub eax,[rsi+0x1C8]; shr eax,4; imul eax,0xFFFFCCCD; dec eax` stores into the stream record, never reads a vector element [V].

## CLOSES?

CLOSES? NO — the single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only statically (end-cursor increments only) [V]; the queued live capture oc_u_er6_light_desc samples function entry (RDX=desc bytes, ret=caller chain) and cannot install a read watchpoint on the pass vectors; livemem has no pass-object target address (0x5ABA5C0 is a function, no static data ref; game running pid 13452 but nothing to point it at) [V live status]. Description value names also remain unknown [?]: no RTTI or member-name strings in the release exe; headers use mValue* placeholders; light_visitor.txt [V live] holds tags 0/1/2/5 bytes only — no tag 3/4 description bytes in any capture. Resolved [V] and not re-proven here: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0 [V].

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already queued in docs/progress/capture_requests.json (state=pending; result not yet available); no new capture can be added (4 pending = limit). It would add runtime desc bytes plus ret= caller chain for the light-visitor entry 0x6640d80 — bytes only, never member names, and no read/write watchpoint, so it cannot close the consumer blocker. A read/watchpoint capability on the pass vectors is what would be needed to close consumers. Helper scripts: None.