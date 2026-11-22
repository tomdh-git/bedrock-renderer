## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — description value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative. Every `0xRVA  instr` line is copied verbatim from verified listings (r1-r5 passed tools/sigs/verify_oc.py). Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; docs/data/live/README.md; docs/BGFX_MAP.md section 6ih; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h; LightDescriptions.h; LightGameDescriptions.h.

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings].

## 1. Tag -> type / value names (LightGroupTag) and the tag-name conflict — resolved [V]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 tag | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]` `0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=0x6640de8 Ambient, 1=0x66415b0 Directional, 2=0x6640f1b GameplayMetadata, 3=0x66410a0 LightPoint, 4=0x6640ec1 ShadowAtlasFrame, 6=0x664187d VoxelVolume, 7=0x6641524 TransitioningVoxelVolume) [V] | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `__FUNCSIG__ FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; JT entry 0 [V] | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); JT entry 1 [V] | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2` `0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; JT entry 2 [V] | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3` `0x535a9c1  mov rax,[rax+0x380]` `0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc 0xF248DA0 `LightPointDescription`; JT entry 3 [V] | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4` `0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; JT entry 4 [V] | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins (its comment at 77-78 explicitly corrects BGFX_MAP 6g, which had LightPoint@2 / GameplayMetadata@3); group_visitors.md 6ih rows are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V]; BGFX_MAP 6ih still marks the dispute [?] but is contradicted by the disassembly [V]. | [V] |

## 2. Description layouts ("value names") — offsets/sizes [V], semantic names [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| ambient +0x00 | 8 | `0x6640dfb  movsd xmm7,[rsi]` | RenderLightAmbientDescription mValue00[2] read as qword -> summary element +0x00 [V]; size 0x18 [V] | [V] |
| ambient +0x08 | 4 | `0x6640df6  movss xmm6,[rsi+8]` | mValue08 read -> summary element +0x8 [V] | [V] |
| ambient +0x10 | 4 | `0x6640dff  movss xmm0,[rsi+0x10]` | mValue10 read -> summary element +0xC [V] | [V] |
| ambient +0x14 | 2 | `0x6640df1  movzx r12d,word ptr [rsi+0x14]` | mValue14 read -> pass+0x8A0 u16 vector [V]; summary element +0x10 = constant 0 (`0x6640e24  mov word ptr [rbp+0xBF4],0`) [V]; desc +0x0C unread [V] | [V] |
| directional +0x00 | 16 | `0x66415cc  movups xmm2,[rsi]` | RenderLightDirectionalDescription mVec00[4] read -> local light record +0xBEC [V] | [V] |
| directional +0x10 | 1 | `0x66415c3  movzx ecx,byte ptr [rsi+0x10]` | mByte10 -> summary element +0x10 flag byte [V] | [V] |
| directional +0x14 | 8 | `0x66415c7  movsd xmm1,[rsi+0x14]` | mValue14[2] qword -> local record +0xC20 [V] | [V] |
| directional +0x1C | 4 | `0x66415ba  movss xmm0,[rsi+0x1C]` | mValue1C -> local record +0xC28 [V] | [V] |
| directional +0x20 | 2 | `0x66415bf  movzx eax,word ptr [rsi+0x20]` | mValue20 -> local +0xBE0 and pass+0x8A0 u16 vector [V]; LightDirectionalDescription size 0x24 [V] | [V] |
| tag2/GameplayMetadata +0x00..+0x39 | 16 | `0x6640f8c  movups xmm0,[rsi]` `0x6640f8f  movups xmm1,[rsi+0x10]` `0x6640f93  movups xmm2,[rsi+0x20]` `0x6640f97  movups xmm3,[rsi+0x2A]` | RenderLightTag2Description mData[0x84/4]: four 16-byte rows copied verbatim into the pass+0x4A0 vector element (r12 = element cursor = [rdi+0x4A0]); +0x2A overlaps +0x20..+0x39 [V] | [V] |
| tag2/GameplayMetadata +0x3C..+0x80 | 4 | `0x6640fb2  movss xmm0,[rsi+0x3C]` `0x6641090  add qword ptr [rdi+0x4A0],0x84` | mData dwords +0x3C..+0x80 copied [V]; GameplayMetadataDescription size 0x84 [V]; producer static_asserts in LightGameDescriptions.h: mFlags30+0x30, mValue34+0x34, mByte36+0x36, mByte39+0x39, mValue3C+0x3C, mValue48+0x48, mVec4C+0x4C, mValue5C+0x5C, mVec60+0x60, mValue68+0x68 [I] | [V]/[I] |
| tag3/LightPoint +0x00 | 4 | `0x664127e  movss xmm5,[rsi]` | RenderLightTag3Description mValue00 read [V] | [V] |
| tag3 +0x08 | 8 | `0x6641287  movsd xmm7,[rsi+8]` | mValue08[2] read as qword [V] | [V] |
| tag3 +0x10 | 4 | `0x6641279  movss xmm4,[rsi+0x10]` | mValue10 read [V] | [V] |
| tag3 +0x14 | 8 | `0x66410a0  movsd xmm0,[rsi+0x14]` | mValue14[2] read as qword [V] | [V] |
| tag3 +0x1C | 4 | `0x66410c0  movss xmm0,[rsi+0x1C]` | mValue1C read [V] | [V] |
| tag3 +0x20 | 1 | `0x6641282  movzx r8d,byte ptr [rsi+0x20]` | mByte20 read [V] | [V] |
| tag3 +0x28 | 8 | `0x66410e2  mov rcx,[rsi+0x28]` | mValue28 read [V] | [V] |
| tag3 +0x30 | 2 | `0x66410de  movzx eax,word ptr [rsi+0x30]` | mValue30 read -> pass+0x8A0 u16 vector [V] | [V] |
| tag3 +0x38 | 16 | `0x66410fd  mov r8,[rsi+0x38]` `0x66410f4  mov rdx,[rsi+0x40]` `0x664110f  lock inc dword ptr [rdx+0xC]` `0x6641117  movups xmm5,[rsi+0x48]` | slice k=0: weak_ptr {mObject+0x00, mControlBlock+0x08} + mVec[4] at slice+0x10; case does `lock inc dword ptr [ctrl+0xC]` (weak count) [V]; six slices at +0x38+k*0x20 [V] | [V] |
| tag3 +0x58 | 16 | `0x6641132  mov r8,[rsi+0x58]` `0x6641129  mov rdx,[rsi+0x60]` `0x6641155  movups xmm4,[rsi+0x68]` | slice k=1 [V] | [V] |
| tag3 +0x78 | 16 | `0x6641176  mov r8,[rsi+0x78]` `0x664116a  mov rdx,[rsi+0x80]` `0x664119a  movups xmm5,[rsi+0x88]` | slice k=4 [V] | [V] |
| tag3 +0x98 | 16 | `0x66411bb  mov r8,[rsi+0x98]` `0x66411af  mov rdx,[rsi+0xa0]` `0x66411e2  movups xmm3,[rsi+0xa8]` | slice k=5 [V] | [V] |
| tag3 +0xF8 | 8 | `0x66410a5  movsd xmm3,[rsi+0xf8]` | mValueF8[2] read as qword [V] | [V] |
| tag3 +0x100 | 4 | `0x66410c9  movss xmm5,[rsi+0x100]` | mValue100 read [V] | [V] |
| tag3 size | - | - | RenderLightTag3Description size 0x108 (aligned read end); Slice {mObject, mControlBlock, mVec[4]} size 0x20 [V header]; unread gaps +0x04..+0x08, +0x21..+0x28, +0x32..+0x38 [V] | [V]/[I] |
| tag4/ShadowAtlasFrame +0x00..+0x30 | 16 | `0x6640ec1  movups xmm6,[rsi]` `0x6640ecb  movups xmm7,[rsi+0x10]` `0x6640ed6  movups xmm8,[rsi+0x20]` `0x6640ee3  movups xmm9,[rsi+0x30]` | RenderLightTag4Description mMatrix[16]: four 16-byte rows copied verbatim [V] | [V] |
| tag4 +0x40 | 8 | `0x66418f0  mov rbx,[rsi+0x40]` | mObject shared_ptr pointer [V] | [V] |
| tag4 +0x48 | 8 | `0x6640f01  mov rcx,[rsi+0x48]` `0x6640f0e  lock inc dword ptr [rcx+8]` | mControlBlock shared_ptr control block; strong-count refcount incremented (`lock inc [ctrl+8]`) [V]; ShadowAtlasFrameDescription size 0x50 [V] (`0x66419c6  add qword ptr [rsi+0x1D0],0x50`) | [V] |
| description value names | - | - | All light-description field names in Descriptions.h / LightDescriptions.h / LightGameDescriptions.h are mValue*/mData placeholders (mValue00, mVec00, mObject, mControlBlock, ...). The exe has no RTTI and no description member-name strings; producer-side semantics (e.g. Ambient +0x00 copied from Atmosphere +0xA4 [I]) are inference only. Semantic value names: unknown [?]. Live capture requested below to confirm field sizes and runtime values [V live pending]. | [?] |

## 3. Pass-vector writes (Light visitor) — writers [V], consumers not located [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]` `0x6640e8b  cmp rdx,[rsi+0x808]` `0x6640eb4  add qword ptr [rsi+0x800],0x14` `0x6641761  mov rdx,[rsi+0x800]` `0x66417a2  add qword ptr [rsi+0x800],0x14` `0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient 0x6640eb4, Directional 0x66417a2, Point 0x6641517 [V] | [V] |
| pass+0x808 | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]` `0x66416ff  call 0x675FB30` `0x664145a  lea rcx,[rsi+0x648]` `0x6641461  call 0x675FB30` | end cursor of the 0x48-byte light-record vector (begin +0x648 / end +0x650); writers Directional 0x66416ff and Point 0x6641461 via 0x675FB30 [V] | [V] |
| pass+0x650 | 4 | `0x6641729  mov eax,[rsi+0x650]` `0x6641735  shr eax,3` `0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; light-record index = (end - begin)/0x48 - 1 [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]` `0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498 / cap +0x4A8); writer tag 2, stride 0x84 [V] | [V] |
| pass+0x4A8 | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8 / cap +0x1D8); writer tag 4, stride 0x50 [V] | [V] |

Every write above is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image `fld --w` scans, earlier units]; no `[pass_cursor + index*stride]` element read exists for any of the four offsets [V].

## 4. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located (static angles exhausted, new live angle pending)

Static angles already exhausted (not re-run this unit; all [V] from r1-r5):
- whole-image `rdis fld --r/--w` scans for all four offsets and their begin cursors (0x7F8/0x650/0x498/0x1C8): every hit is (a) a stack local, (b) a cursor-field access by the writers themselves or grow/relocate code, or (c) the same offset on an unrelated object; writes are only end-cursor increments, no `sub` end-cursor decrement (pop) anywhere; no `[pass_base + index]` element read for any of the four offsets.
- endFrame's full listing sub_66232b0 (0x66232b0..0x662e680): no access to any of the four offsets, although it calls 0x5ABA5C0 three times (0x662891e, 0x662ab42, 0x662b38c) [V].
- all ~200 `0x5ABA5C0` callers enumerated via `rdis xr`; the three non-visitor callers (0x66a6830, 0x66a9d50, 0x66bb7b0) touch only stack locals at 0x650/0x4A0/0x1D0 [V].
- `rdis ptr 0x5aba5c0`: 0 indirect slots [V]; `rdis imm 0x5aba5c0`: 0 static data references to the TLO global [V]; no indirect callers beyond the direct xref list [V].
- A consumer that loads a cursor once and indexes `[cursor_reg + index*stride]` would be invisible to offset scans; none of the enumerated cursor-reader functions does that [V]. Per-draw code 0x66ea3d0 appends u16 indices to the *other* pass vector at pass+0x8A8 (`0x66ecb03  mov rdx,[rbx+0x8A8]`, `0x66ecb1e  mov [rdx],ax`, `0x66ecb21  add qword ptr [rbx+0x8A8],2`) but reads none of the four cursors [V].

New angle this unit — live capture at the producer entry (the only entry proven for this item): light visitor 0x6640d80 (RDX = desc pointer at entry per docs/data/live/README.md CORRECTION 2026-11-15). A regs capture dumps RCX/RDX/R8/R9 at entry -> description bytes (RDX pointee) to confirm field sizes/runtime values vs Descriptions.h, plus `ret=` (return address on the stack = caller RVA) to name the visitor's caller chain. Producer-side only: it CANNOT observe downstream consumers of the pass vectors, and no consumer candidate exists to target with livemem (live session docs/data/live/_status.txt = DONE t=120; nothing to point livemem at).

Existing live data: docs/data/live/light_visitor.txt (tags 5, 0, 1, 2 only, 8 lines) — no tag 3 (LightPoint, 0x108 B) or tag 4 (ShadowAtlasFrame, 0x50 B) description bytes.

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining reader of the 0x14-byte summary elements located anywhere in Minecraft.Windows.exe 1.26.62.01; only the three light-visitor end-cursor writers above [V] | [?] |
| pass+0x648 element read | - | - | no draining reader of the 0x48-byte light-record elements located anywhere in the exe [?] | [?] |
| pass+0x4A0 element read | - | - | no draining reader of the 0x84-byte GameplayMetadata elements located anywhere in the exe [?] | [?] |
| pass+0x1D0 element read | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements located anywhere in the exe [?] | [?] |

## 5. Conclusion

CLOSES? NO — single blocking fact: the consumers (draining element readers) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 are not located anywhere in Minecraft.Windows.exe 1.26.62.01. All four vectors are write-only in static analysis: only the Light-visitor end-cursor writers are [V], every write is an end-cursor increment, no pop/decrement exists, no element-indexed read of any of the four vectors exists, and every consumer angle above (whole-image fld scans, endFrame listing, all ~200 0x5ABA5C0 callers, ptr/imm/xr indirect-slot checks, cursor-register indexing blind spot) is exhausted. Tag names (tag 2 = GameplayMetadata, tag 3 = LightPoint) and the group_visitors.md vs FrameBuilder.h conflict are closed [V]; the writers are closed [V]; description field offsets/sizes are closed [V], but semantic value names remain unknown [?] (header mValue* placeholders only; live capture pending to confirm runtime field bytes).

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc | `python tools/livecap/request.py add oc_u_er6_light_desc 0x6640d80 --size 0x100 --max 6 --why "R6: light-visitor entry producer capture. RDX = desc pointer (docs/data/live/README.md CORRECTION 2026-11-15: light visitor takes {desc,tag} in RDX). Dump desc bytes to confirm tag 3 (LightPoint, 0x108 B) and tag 4 (ShadowAtlasFrame, 0x50 B) field sizes/runtime values vs Descriptions.h layouts; ret= names the visitor caller chain."` | regs capture at the light-visitor entry (proven producer); result expected in docs/data/live/oc_u_er6_light_desc.txt (none yet — orchestrator has not run the batch). Producer-side only: cannot find pass-vector consumers. No helper scripts written; none needed.
