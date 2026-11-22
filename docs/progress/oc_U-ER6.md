## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and the consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0.
Static analysis only; RVAs image-relative. Every `0xRVA  instr` line is copied verbatim from the listing / re-disassembly and passes tools/sigs/verify_oc.py.
Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.
Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/light_game_descriptions.md; docs/functions/group_visitors.md; docs/functions/5aba5c0.md; docs/data/live/light_visitor.txt; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h.

## 1. Tag -> type / value names (LightGroupTag) and the tag-name conflict

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| variant+0x08 | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08 loaded by the Light visitor; dispatch `jmp rax` through jump table 0xF2BF2B0 (entry targets: 0=0x6640de8, 1=0x66415b0, 2=0x6640f1b, 3=0x66410a0, 4=0x6640ec1, 5=0x66417af, 6=0x664187d, 7=0x6641524; target list [I] parsed from PE) | [V] |
| tag 0 | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc 0xF248E70 `__FUNCSIG__ FrameBuilder::insert [TDescription = RenderLightAmbientDescription]`; case entry 0x6640de8 (jump table entry 0) | [V] |
| tag 1 | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc 0xF248F70 (LightDirectionalDescription); case entry 0x66415b0 (jump table entry 1) | [V] |
| tag 2 | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, insert site 0x53e5fca through vslot 0x380, srcloc 0xF248ED0 `__FUNCSIG__ ... gamecomponents::GameplayMetadata`; case entry 0x6640f1b (jump table entry 2) | [V] |
| tag 3 | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 loop, insert site 0x535a9ce, srcloc 0xF248DA0 `LightPointDescription`; case entry 0x66410a0 (jump table entry 3) | [V] |
| tag 4 | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0, insert site 0x535a6a0, srcloc 0xF248D80 `ShadowAtlasFrameDescription`; case entry 0x6640ec1 (jump table entry 4) | [V] |
| tag-map conflict | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: group_visitors.md line 34 lists the Light variant order as LightPoint@2/GameplayMetadata@3 (BGFX_MAP 6g order); producer tag stores + __FUNCSIG__ srclocs above prove tag 2 = GameplayMetadata and tag 3 = LightPoint, so FrameBuilder.h wins and the 6g/6ih rows are superseded. Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume (6640d80 section 1) | [V] |

## 2. Description layouts ("value names") — reads are [V], semantic value names unknown [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| ambient+0x00 | 8 | `0x6640dfb  movsd xmm7,[rsi]`<br>`0x53e3473  movlps [rbp+0x118],xmm8` | visitor reads desc qword +0x00 -> summary element +0x00 [V]; producer writes stack desc [rbp+0x118]+0x00 from Atmosphere +0xA4 [V] | [V] |
| ambient+0x08 | 4 | `0x6640df6  movss xmm6,[rsi+8]`<br>`0x53e347b  movss [rbp+0x120],xmm7` | desc f32 +0x08 -> summary element +0x8 [V] | [V] |
| ambient+0x0C | 4 | `0x53e3483  movss [rbp+0x124],xmm6` | desc f32 +0x0C WRITTEN by producer, NEVER read by the visitor [V write / I unread] | [V] |
| ambient+0x10 | 4 | `0x6640dff  movss xmm0,[rsi+0x10]` | desc f32 +0x10 -> summary element +0xC [V] | [V] |
| ambient+0x14 | 2 | `0x6640df1  movzx r12d,word ptr [rsi+0x14]`<br>`0x6643352  mov [rdx],r12w`<br>`0x6643356  add qword ptr [rsi+0x8A8],2` | desc u16 +0x14 -> pass+0x8A0 u16 vector [V]; summary element +0x10 = constant 0 (`0x6640e24  mov word ptr [rbp+0xBF4],0`) [V]; LightAmbientDescription size 0x18 [V] | [V] |
| directional+0x00 | 16 | `0x66415cc  movups xmm2,[rsi]` | desc vec4 +0x00 -> local light record +0xBEC [V] | [V] |
| directional+0x10 | 1 | `0x66415c3  movzx ecx,byte ptr [rsi+0x10]` | desc byte +0x10 -> summary element +0x10 (flag byte) [V] | [V] |
| directional+0x14 | 8 | `0x66415c7  movsd xmm1,[rsi+0x14]` | desc qword +0x14 -> local record +0xC20 [V] | [V] |
| directional+0x1C | 4 | `0x66415ba  movss xmm0,[rsi+0x1C]` | desc dword +0x1C -> local record +0xC28 [V] | [V] |
| directional+0x20 | 2 | `0x66415bf  movzx eax,word ptr [rsi+0x20]`<br>`0x6644b18  mov [rdx],ax`<br>`0x6644b1b  add qword ptr [rsi+0x8A8],2` | desc u16 +0x20 -> local +0xBE0 and pass+0x8A0 u16 vector [V]; LightDirectionalDescription size 0x24 [V] (producer store end at +0x22, align 4); real field value names unknown [?] (Descriptions.h mValue* placeholders) | [V]/[?] |
| gm+0x00 | 16 | `0x6640f8c  movups xmm0,[rsi]`<br>`0x6640fad  movups [r12],xmm0` | GameplayMetadata verbatim copy row 1 into pass+0x4A0 vector element +0x00; r12 = element = [rdi+0x4A0] end cursor [V] | [V] |
| gm+0x10 | 16 | `0x6640f8f  movups xmm1,[rsi+0x10]`<br>`0x6640fa7  movups [r12+0x10],xmm1` | element +0x10 [V] | [V] |
| gm+0x20 | 16 | `0x6640f93  movups xmm2,[rsi+0x20]`<br>`0x6640fa1  movups [r12+0x20],xmm2` | element +0x20 [V] | [V] |
| gm+0x2A | 16 | `0x6640f97  movups xmm3,[rsi+0x2A]`<br>`0x6640f9b  movups [r12+0x2A],xmm3` | element +0x2A (overlaps +0x20..+0x39) [V] | [V] |
| gm+0x3C | 4 | `0x6640fb2  movss xmm0,[rsi+0x3C]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | dwords +0x3C..+0x80 copied [V]; size 0x84 [V]; field meanings unknown [?] (+0x00/+0x0C sky/block light [I], +0x1C u16 dimension/biome [I], +0x30 flags [I]) | [V]/[?] |
| lp+0x00 | 4 | `0x664127e  movss xmm5,[rsi]` | LightPoint desc f32 +0x00 [V] | [V] |
| lp+0x10 | 4 | `0x6641279  movss xmm4,[rsi+0x10]` | desc f32 +0x10 [V] | [V] |
| lp+0x14 | 8 | `0x66410a0  movsd xmm0,[rsi+0x14]` | desc qword +0x14 loaded into xmm0 and reused in the record/summary build [V] | [V] |
| lp+0x20 | 1 | `0x6641282  movzx r8d,byte ptr [rsi+0x20]` | desc byte +0x20 -> summary element [V] | [V] |
| lp+0x28 | 8 | `0x66410e2  mov rcx,[rsi+0x28]` | desc qword +0x28 -> shadow-cube element [V] | [V] |
| lp+0x30 | 2 | `0x66410de  movzx eax,word ptr [rsi+0x30]`<br>`0x66446bf  movzx eax,word ptr [rbp-0x50]`<br>`0x66446c6  add qword ptr [rsi+0x8A8],2` | desc u16 +0x30 -> pass+0x8A0 u16 vector [V] | [V] |
| lp+0x38 | 8 | `0x66410fd  mov r8,[rsi+0x38]`<br>`0x664110f  lock inc dword ptr [rdx+0xC]` | slice k=0 weak_ptr pointer +0x38; six slices at +0x38+k*0x20, each {ptr, ctrl, vec4}; case increments WEAK count `lock inc [ctrl+0xC]` [V] | [V] |
| lp+0x40 | 8 | `0x66410f4  mov rdx,[rsi+0x40]`<br>`0x6641144  lock inc dword ptr [rdx+0xC]` | slice k=0 weak control block +0x40 [V] | [V] |
| lp+0x58 | 8 | `0x6641132  mov r8,[rsi+0x58]` | slice k=1 pointer [V] | [V] |
| lp+0x60 | 8 | `0x6641129  mov rdx,[rsi+0x60]` | slice k=1 control block [V] | [V] |
| lp+0xE8 | 16 | `0x664126b  movups xmm4,[rsi+0xE8]` | desc vec4 +0xE8 [V] | [V] |
| lp size | - | - | LightPointDescription size 0x108 [V] (aligned read end); queue destination not followed [?]; real field value names unknown [?] | [V]/[?] |
| sa+0x00 | 16 | `0x6640ec1  movups xmm6,[rsi]` | ShadowAtlasFrame (tag 4) row +0x00 copied verbatim [V] | [V] |
| sa+0x10 | 16 | `0x6640ecb  movups xmm7,[rsi+0x10]` | row +0x10 [V] | [V] |
| sa+0x20 | 16 | `0x6640ed6  movups xmm8,[rsi+0x20]` | row +0x20 [V] | [V] |
| sa+0x30 | 16 | `0x6640ee3  movups xmm9,[rsi+0x30]` | row +0x30 [V] | [V] |
| sa+0x40 | 8 | `0x66418f0  mov rbx,[rsi+0x40]` | shared_ptr pointer +0x40 [V] | [V] |
| sa+0x48 | 8 | `0x6640f01  mov rcx,[rsi+0x48]`<br>`0x6640f0e  lock inc dword ptr [rcx+8]` | shared_ptr control block +0x48; use count incremented [V]; size 0x50 [V] (`0x66419c6  add qword ptr [rsi+0x1D0],0x50`) | [V] |

## 3. Pass-vector writes and the consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x7F8 | 4 | `0x6641ad5  sub eax,[rsi+0x7F8]`<br>`0x6641adb  shr eax,2`<br>`0x6641ade  imul eax,0xFFFFCCCD` | summary list begin cursor; count = (end - begin) / 5 (element 0x14) [V] | [V] |
| pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); writers: Ambient (`0x6640eb4`), Directional (`0x66417a2`), Point (`0x6641517`) [V]; CONSUMER (draining reader of the elements) NOT located [?] | [V]/[?] |
| pass+0x808 | 8 | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor [V] | [V] |
| pass+0x648 | 8 | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664172f  sub eax,[rsi+0x648]`<br>`0x66ed5c0  lea rcx,[r15+0x648]`<br>`0x66ed5ce  call 0x675FB30`<br>`0x66ed5f7  sub eax,[r15+0x648]` | light-record vector begin (end +0x650), stride 0x48; writers: Directional (`0x66416ff call 0x675FB30`), Point (`0x6641461 call 0x675FB30`, case 0x66410a0) [V]; fn at 0x66ea3d0 (r15 = [rdx+0x40], pass identity [I]) reads cursors for index (end-begin)/0x48 - 1 and appends via 0x675FB30 — cursor use only, no element drain [?]; CONSUMER of elements NOT located [?] | [V]/[?] |
| pass+0x650 | 4 | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | end cursor; light-record index = (end - begin)/0x48 - 1 [V] | [V] |
| pass+0x498 | 4 | `0x664319e  sub eax,[rdi+0x498]` | GameplayMetadata vector begin cursor [V] | [V] |
| pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84`<br>`0x6643198  mov eax,[rdi+0x4A0]` | end cursor; tag 2 appends 0x84-byte elements (verified rows gm+0x00..gm+0x3C) [V]; CONSUMER NOT located [?] | [V]/[?] |
| pass+0x4A8 | 8 | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata vector cap cursor [V] | [V] |
| pass+0x1D0 | 8 | `0x66419c6  add qword ptr [rsi+0x1D0],0x50` | ShadowAtlasFrame vector end cursor (vector = pass+0x1C8 begin / +0x1D0 end / +0x1D8 cap, stride 0x50 [V]); tag 4 copies the description verbatim (sa+0x00..sa+0x48 rows) [V]; CONSUMER NOT located [?] | [V]/[?] |

## Consumer sweep

All four vectors are written [V] (rows above). A sweep of the available listings (all of docs/data/listings, including the endFrame chunks _tmp_66232b0*, e4_A-D, the light visitor, and the gameplaymeta clone) finds only stack locals at +0x800/+0x4A0 (e.g. item_visitor [rbp+0x800], shadow extractors [rbp+0x4A0]) and the writers above — no instruction outside the Light visitor reads the ELEMENTS of these vectors. The +0x648/+0x650 cursor reads at 0x66ed5f0/0x66ed5f7 compute an index and append (0x66ed5c0/0x66ed5ce call 0x675FB30) — not an element drain. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0: not located [?] (same E2 consumer blocker as the R2/R5 groups; pass object is the per-thread value of ThreadLocalObject 0x5aba5c0, consumers walk thread lists — not located).

CLOSES? NO — the consumers (draining readers) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 are not located in the exe: only the Light-visitor writers are proven [V]; no element read of these vectors was found anywhere (the +0x648/+0x650 cursor reads at 0x66ed5f0/0x66ed5f7 compute an index and append — not a drain). Tag value names and the group_visitors.md vs LightGroupTag conflict are resolved [V] (FrameBuilder.h: tag 2 = GameplayMetadata, tag 3 = LightPoint; group_visitors.md had them swapped); description field value names remain unknown [?].

## TOOL REQUESTS

None — no helper scripts written; every instruction proof line verified with rdis via tools/sigs/verify_oc.py.
