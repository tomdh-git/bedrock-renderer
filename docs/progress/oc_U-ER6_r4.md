## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and the consumers (draining readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative. Every `0xRVA  instr` line is copied verbatim from a listing / re-disassembly and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.
Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h.

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (0x8B8-byte node; value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings quoted below].

## 1. Tag -> type / value names (LightGroupTag) and the tag-name conflict — resolved [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524) [V] | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; jump-table entry 0 (0x6640de8) | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); entry 1 (0x66415b0) | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; entry 2 (0x6640f1b) | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9c1, srcloc 0xF248DA0 `LightPointDescription`; entry 3 (0x66410a0) | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; entry 4 (0x6640ec1) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h wins; group_visitors.md 6g/6ih rows had them swapped (LightPoint@2 / GameplayMetadata@3) and are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V] | [V] |

## 2. Description field value names — unknown [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| description value names | - | - | LightAmbientDescription (size 0x18), LightDirectionalDescription (0x24), LightPointDescription (0x108), GameplayMetadataDescription (0x84) field reads are proven [V] in the visitor cases, but the exe has no RTTI and no description member name strings; headers type the fields as mValue* placeholders with static_assert offsets only, and the live dumps (docs/data/live/light_visitor.txt) carry values only. Producer-side semantics (e.g. Ambient +0x00 = Atmosphere +0xA4) are inference [I], not names. Value names: unknown [?] | [?] |

## 3. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (not redone this unit)

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x808 | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional (0x66416ff) and Point (0x6641461) via 0x675FB30 [V] | [V] |
| pass+0x650 | 4 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; light-record index = (end - begin)/0x48 - 1 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x4A8 | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V] | [V] |

Every one of these writes is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans, earlier units].

## 4. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — new angles tried, all negative

The old `fld --r/--w` scans catch only `[reg+0x800]`-style accesses. They miss a consumer that loads a cursor once and then indexes elements via `[cursor_reg + index*stride]` (no 0x800-class offset). This unit attacked that blind spot from four angles:

**Angle 1 — endFrame re-read (full listing).** `sub_66232b0` [0x66232b0..0x662e680), size 0xB3D0 (listing /tmp/endframe.txt, converted from UTF-16): it contains NO access at all to [reg+0x7F8]/[0x800]/[0x648]/[0x650]/[0x4A0]/[0x498]/[0x1D0]/[0x1C8] [V]. endFrame does call 0x5ABA5C0 directly (xr lists `0x662891e  call 0x5ABA5C0`, `0x662ab42  call 0x5ABA5C0`, `0x662b38c  call 0x5ABA5C0` inside sub_66232b0 [V]) but none of those sites touches the four cursors — endFrame uses other pass vectors (+0x20/+0x50/+0x38 family) instead [I from earlier units].

**Angle 2 — the three non-visitor 0x5ABA5C0 callers.** Disassembled 0x66a6830, 0x66a9d50, 0x66bb7b0 (220 instructions each): the only accesses at 0x650/0x4A0/0x1D0 are stack locals (`0x66a6ac4  mov rax,[rbp+0x650]`, `0x66a9d83  movaps [rbp+0x4A0],xmm12`, `0x66bb9be  mov [rbp+0x1D0],rax`) [V] — not pass cursors.

**Angle 3 — indirect caller slots.** `rdis ptr 0x5aba5c0`: `-- 0 pointer(s)` [V] — no data slot/vtable holds the getter address, so there are no indirect callers beyond the direct xref list.

**Angle 4 — whole-image cursor-reader enumeration (fresh `fld --r` scans this unit).** `fld 0x800 --r`: 1561 accesses; `fld 0x7F8 --r`: 723 accesses (counts match the earlier complete scans). Every non-stack reader enumerated: the only pass-cursor readers are the light-visitor writer sites (0x6640e84/0x66414c9/0x6641761/0x6641acf/0x6641ea8/0x66427d8 for 0x800; 0x6641a9e/0x6641ad5/0x6641e7f/0x6641eae/0x66427af/0x66427de for 0x7F8). All other non-stack hits are unrelated objects that coincidentally share the offset (e.g. sub_5776a0 [r12+0x7F8/+0x800], sub_8b505c0 [rdi/rsi/r8/r14+0x7F8/+0x800] render-context checks that test begin==end and never index elements) [V]. No function loads a pass cursor and then reads `[cursor_reg + index*stride]`; no end-cursor decrement exists anywhere [V].

**Side finding (not a consumer).** Per-draw code 0x66ea3d0 (terrain/chunk draw setup) obtains the pass via 0x5ABA5C0 (`0x66eca8f  call 0x5ABA5C0`) and APPENDS u16 indices to the *other* pass vector at pass+0x8A8 (`0x66ecb03  mov rdx,[rbx+0x8A8]` / `0x66ecb1e  mov [rdx],ax` / `0x66ecb21  add qword ptr [rbx+0x8A8],2`) [V] — vectors are written during draw recording too, but this function reads none of the four cursors.

Resulting consumer table:

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining reader of the 0x14-byte summary elements located anywhere in Minecraft.Windows.exe 1.26.62.01; only the three light-visitor end-cursor writers above [V] | [?] |
| pass+0x648 element read | - | - | no draining reader of the 0x48-byte light-record elements located anywhere in the exe [?] | [?] |
| pass+0x4A0 element read | - | - | no draining reader of the 0x84-byte GameplayMetadata elements located anywhere in the exe [?] | [?] |
| pass+0x1D0 element read | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements located anywhere in the exe [?] | [?] |

## 5. Conclusion

CLOSES? NO — the consumers (draining element readers) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 are not located in the exe: whole-image `fld --r/--w` scans for all four offsets and their begin cursors (0x7F8/0x650/0x498/0x1C8) show only the four light-visitor writer cursor accesses [V] (re-confirmed this unit for 0x800/0x7F8), every write is an end-cursor increment with no pop/decrement [V], endFrame's full listing contains none of the four offsets though it calls 0x5ABA5C0 three times [V], the three other direct 0x5ABA5C0 callers touch only stack locals [V], and `rdis ptr 0x5aba5c0` finds no indirect caller slot [V]. A reader that loads a cursor once and indexes `[cursor_reg + index*stride]` would be invisible to offset scans, but none of the enumerated cursor-reader functions does that [V].

Tag names and the tag-name conflict ARE closed [V]: tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins over group_visitors.md (which had 2/3 swapped).

Description value names remain unknown [?]: no RTTI and no description member name strings exist in the release exe; headers use mValue* placeholders; producer-side meanings are inference [I] only.

## TOOL REQUESTS

None — no helper scripts written; all evidence from existing tools (rdis dis/walk/xr/ptr/fld, verify_oc) and already-verified listings. The `fld` per-offset scan blind spot (cursor-register indexing) is a genuine tool gap: a "follow a loaded register into indexed element reads" data-flow pass would be the natural addition, but no consumer candidate remains to point it at.
