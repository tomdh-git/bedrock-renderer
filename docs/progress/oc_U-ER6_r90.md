## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (Minecraft.Windows.exe 1.26.62.01)

Goal (carried from oc_U-ER6_r89, not re-proven this unit): close R6 — LightGroupTag value names, the group_visitors.md vs FrameBuilder.h tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. pass = per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10); visitor cases call 0x5ABA5C0 and receive pass in rsi/rdi [V].

Conventions: [V] = seen in disassembly, verbatim `0xRVA  instr` line cited (verify_oc-clean; exe not launched, no builds) | [I] = inferred | [?] = unknown | [V live] = confirmed by capture bytes, cited as docs/data/live/<file>:<line>. Rows marked "carried" were proven in oc_U-ER6_r1..r88 (verify_oc 83/83) and are not re-run this unit.

## This run — live data consumed (only what the live data can add; nothing re-derived)

`python tools/livecap/request.py result oc_u_er6_light_desc` → result exists: docs/data/live/oc_u_er6_light_desc.txt, 24 samples, capture at the light-visitor entry 0x6640d80 (the producer entry already proved for R6); RDX = desc pointer [LIVE docs/data/live/README.md:12]; every line `CALLER ret=0x6640C49` [LIVE docs/data/live/oc_u_er6_light_desc.txt:3].

`python tools/livecap/request.py result sub_1289440_callers` → result exists but the capture is U-EL7e (sub_1289440 → sub_4e05e50 texgroup_load/texload chain; its bytes carry texture-name strings, e.g. "textures/particles/biome_tinted_leaves_atlas" at docs/data/live/sub_1289440_callers.txt:4) — outside R6, not pursued.

New proof this unit: the visitor's call site inside the FrameBuilder light-insert region (sub_6640c00, 0x6640c00-0x6642c00; "FrameBuilder - Insert light" srcloc at 0x6640c8d):

`0x6640c3c  lea rcx,[rbp-0x28]` / `0x6640c40  lea rdx,[rbp-0x40]` / `0x6640c44  call 0x6640D80` [V] — at the call RCX = RDX + 0x18, matching every live register pair: RCX=14A808 vs RDX=14A7F0 (hit=1), RCX=14A1D8 vs RDX=14A1C0 (hit=2), RCX=149F58 vs RDX=149F40 (hit=3), RCX=14A298 vs RDX=14A280 (hit=4), repeated for hits 5-11 [LIVE docs/data/live/oc_u_er6_light_desc.txt:4-27].

So ret=0x6640C49 names the caller chain: sub_6640c00 (group-visitor light insert) calls light visitor 0x6640d80, return address 0x6640C49 [V live].

Live desc bytes (RDX = desc pointer, 256-byte dump per sample; 4 distinct desc addresses 0x149F40 / 0x14A1C0 / 0x14A280 / 0x14A7F0 reused across samples): +0x00 holds an arena handle (0x14A290 / 0x14A448 / 0x14A430 / 0x14A910 by family), +0x10 a canonical module VA (0x7FF6185E0310 hit=1, ...5E60 hit=2, ...6860 hit=3, ...6220 hit=4), +0x28 heap VA 0x0004661CD35400 identical in all 12 RDX samples, +0x30 heap VA 0x000465B8252900 identical in all 12 RDX samples, +0x18 differs per sample (0x...0A9600 hit=1, ...0AFA80 hit=5, ...0A5A00 hit=9), and f32 scalars present (hit=3 RDX=149F40: f32 1.0 bytes `00 00 80 3F` at +0xF0, f32 ~0.442 bytes `63 C8 FE 3E` at +0xF4; hit=4 RDX=14A280: f32 1.0 at +0xF8, f32 100.0 bytes `00 00 C8 42` at +0xFC) [LIVE docs/data/live/oc_u_er6_light_desc.txt:5,8,10,13,15,19,22,27]. Values differ per sample → live per-light description data; sizes are consistent with the header read-views below but no sample's tag is identifiable from the capture alone and no field semantic name can be read from bytes [?].

## 1. Tag -> type / value names (LightGroupTag) — resolved [V] (carried)

| offset/rva | size | name | site / verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| variant+0x08 tag byte | 1 | LightGroupTag tag | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at variant+0x08; dispatch `jmp rax` via jump table 0xF2BF2B0 (entries: 0=Ambient 0x6640de8, 1=Directional 0x66415b0, 2=GameplayMetadata 0x6640f1b, 3=LightPoint 0x66410a0, 4=ShadowAtlasFrame 0x6640ec1, 5=ServerGraphicsOverrideParameters 0x66417af, 6=VoxelVolume 0x664187d, 7=TransitioningVoxelVolume 0x6641524) [V] | [V] |
| tag 0 store | 1 | LightGroupTag::Ambient | `0x53e3511  mov byte ptr [rbp+0x138],0` | Ambient = 0 (FrameBuilder.h:79-88); producer clone 0x53e2c00, srcloc RenderLightAmbientDescription 0xF248E70; JT entry 0 [V] | [V] |
| tag 1 store | 1 | LightGroupTag::Directional | `0x53709d4  mov byte ptr [rbp+0x18],1` | Directional = 1; thin clone 0x5370960, srcloc LightDirectionalDescription 0xF248F70; JT entry 1 [V] | [V] |
| tag 2 store | 1 | LightGroupTag::GameplayMetadata | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert 0x53e5fbf, srcloc `__FUNCSIG__ ...gamecomponents::GameplayMetadata` 0xF248ED0; JT entry 2 [V] | [V] |
| tag 3 store | 1 | LightGroupTag::LightPoint | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightPoint = 3; light clone 0x53599d0 insert 0x535a9ce, srcloc LightPointDescription 0xF248DA0; JT entry 3 [V] | [V] |
| tag 4 store | 1 | LightGroupTag::ShadowAtlasFrame | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | ShadowAtlasFrame = 4; light clone 0x53599d0 insert 0x535a6a0, srcloc ShadowAtlasFrameDescription 0xF248D80; JT entry 4 [V] | [V] |
| tag-name conflict | - | LightGroupTag enum doc | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ServerGraphicsOverrideParameters = 5, VoxelVolume = 6, TransitioningVoxelVolume = 7 };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ srclocs prove tag 2 = GameplayMetadata and tag 3 = LightPoint; FrameBuilder.h wins; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3) and is superseded; tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V] | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V] (carried)

Pass-object vectors (begin/end/cap cursors): summary +0x7F8/+0x800/+0x808 stride 0x14; light records +0x648/+0x650 stride 0x48; GameplayMetadata +0x498/+0x4A0/+0x4A8 stride 0x84; ShadowAtlasFrame +0x1C8/+0x1D0/+0x1D8 stride 0x50 [V]. Every write below is an end-cursor increment / grow-emplace / element copy at the end cursor; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image fld --w scans].

| offset/rva | size | name | site / verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| pass+0x800 end cursor | 8 | summary vec end cursor | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641761  mov rdx,[rsi+0x800]`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); end += stride 0x14 per element; writers: Ambient 0x6640eb4, Directional 0x66417a2, LightPoint 0x6641517; loads at 0x6640e84 / 0x6641761 [V] | [V] |
| pass+0x808 cap cursor | 8 | summary vec cap cursor | `0x6640e8b  cmp rdx,[rsi+0x808]` | summary list cap cursor compared against end at 0x6640e8b [V] | [V] |
| pass+0x648 begin cursor | 8 | light-record vec begin | `0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30`<br>`0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30` | begin cursor of the 0x48-byte light-record vector (end +0x650); vector grow-emplace 0x675FB30 with &pass+0x648; writers: LightPoint 0x6641461, Directional 0x66416ff [V] | [V] |
| pass+0x650 end cursor | 4 | light-record vec end | `0x6641729  mov eax,[rsi+0x650]`<br>`0x6641735  shr eax,3`<br>`0x6641738  imul eax,0xFFFF8E39` | light-record end cursor; index = (end - begin)/0x48 - 1 (0xFFFF8E39 = magic divide by 6 after >>3 => /0x48) [V] | [V] |
| pass+0x4A0 end cursor | 8 | GameplayMetadata vec end | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84`<br>`0x6643198  mov eax,[rdi+0x4A0]` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498, cap +0x4A8); end += stride 0x84; tag-2 writer at 0x6641090 [V] | [V] |
| pass+0x4A8 cap cursor | 8 | GameplayMetadata vec cap | `0x6640f7f  cmp r12,[rdi+0x4A8]` | GameplayMetadata cap cursor [V] | [V] |
| pass+0x1D0 end cursor | 8 | ShadowAtlasFrame vec end | `0x6641991  mov r14,[rsi+0x1D0]`<br>`0x6641998  cmp r14,[rsi+0x1D8]`<br>`0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8, cap +0x1D8); end += stride 0x50; tag-4 writer at 0x66419c6; element copy writes at [r14] = end cursor only, 0x66419a5-0x66419bc [V] | [V] |
| pass+0x1D8 cap cursor | 8 | ShadowAtlasFrame vec cap | `0x6641998  cmp r14,[rsi+0x1D8]` | ShadowAtlasFrame cap cursor [V] | [V] |

## 3. Consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located [?]

| offset/rva | size | name | site / verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| pass+0x800 element read | - | summary vec element read | - | no draining element read of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers in section 2 [V writes only] | [?] |
| pass+0x648 element read | - | light-record vec element read | - | no draining element read of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | - | GameplayMetadata vec element read | - | no draining element read of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | - | ShadowAtlasFrame vec element read | - | no draining element read of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

What the live data adds (and cannot add): the oc_u_er6_light_desc capture samples the visitor PRODUCER entry only; its REG=value lines and ret=0x6640C49 name the producer's caller chain (section above) and confirm desc pointer/sizes — but function-entry sampling installs no read/write watch on pass+0x800/+0x648/+0x4A0/+0x1D0, so it cannot observe a downstream draining reader [I]. request.py captures function entry only (no watchpoint mode) [tools/livecap/request.py]; the consumer entry RVA is unknown, so no function-entry capture can be queued for it; livemem cannot help: TLS slot 0x5ABA5C0 reads an obfuscated value (0xEC8348FA53630EE9) and +0x10 yields no pass VA, and livemem may not scan [V live carried r89]. All static consumer angles are negative and carried (whole-image fld --r/--w on all four offsets and begin cursors 0x7F8/0x650/0x498/0x1C8; ~200 0x5ABA5C0 callers; rdis xr/imm/ptr indirect checks; magic-multiplier imm scans; lea cursor scan; scaled-stride scan over 0x6600000-0x6700000; endFrame sub_66232b0; per-draw code 0x66ea3d0/0x66ecb03; endFrame merge 0xc288880; vt/vcalls) [V carried].

## 4. Description field value names — offsets/sizes [V], semantic names [?]

Field read-views (header members are mValue* placeholders; names are [?], offsets/sizes and read instructions are [V], from docs/functions/6640d80_light_visitor.md listings re-checked with rdis and carried):

| offset/rva | size | name | site / verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| tag-0 desc +0x00 | 8 | Ambient mValue00 | `0x6640dfb  movsd xmm7,[rsi]` | float[2] as qword at +0x00 [V header RenderLightAmbientDescription] | [V] |
| tag-0 desc +0x08 | 4 | Ambient mValue08 | `0x6640df6  movss xmm6,[rsi+8]` | f32 +0x08 [V] | [V] |
| tag-0 desc +0x10 | 4 | Ambient mValue10 | `0x6640dff  movss xmm0,[rsi+0x10]` | f32 +0x10 [V] | [V] |
| tag-0 desc +0x14 | 2 | Ambient mValue14 | `0x6640df1  movzx r12d,word ptr [rsi+0x14]` | u16 +0x14 [V] | [V] |
| tag-1 desc +0x00 | 16 | Directional mVec00 | `0x66415cc  movups xmm2,[rsi]` | float[4] +0x00 [V] | [V] |
| tag-1 desc +0x10 | 1 | Directional mByte10 | `0x66415c3  movzx ecx,byte ptr [rsi+0x10]` | byte +0x10 [V] | [V] |
| tag-1 desc +0x14 | 8 | Directional mValue14 | `0x66415c7  movsd xmm1,[rsi+0x14]` | float[2] +0x14 [V] | [V] |
| tag-1 desc +0x1C | 4 | Directional mValue1C | `0x66415ba  movss xmm0,[rsi+0x1C]` | f32 +0x1C [V] | [V] |
| tag-1 desc +0x20 | 2 | Directional mValue20 | `0x66415bf  movzx eax,word ptr [rsi+0x20]` | u16 +0x20 [V] | [V] |
| tag-2 desc +0x00..+0x3D | 16 | GameplayMetadata verbatim copy part 1 | `0x6640f8c  movups xmm0,[rsi]`<br>`0x6640f8f  movups xmm1,[rsi+0x10]`<br>`0x6640f93  movups xmm2,[rsi+0x20]`<br>`0x6640f97  movups xmm3,[rsi+0x2A]` | first 0x3E bytes copied verbatim into pass+0x4A0 [V header RenderLightTag2Description] | [V] |
| tag-2 desc +0x3C..+0x80 | 4 | GameplayMetadata scalar fields | `0x6640fb2  movss xmm0,[rsi+0x3C]` ... `0x664107e  movss xmm0,[rsi+0x80]` | movss scalars at +0x3C step 4 through +0x80 [V] | [V] |
| tag-3 desc +0x00 | 4 | LightPoint mValue00 | `0x664127e  movss xmm5,[rsi]` | f32 +0x00 [V] | [V] |
| tag-3 desc +0x08 | 8 | LightPoint mValue08 | `0x6641287  movsd xmm7,[rsi+8]` | float[2] +0x08 [V] | [V] |
| tag-3 desc +0x10 | 4 | LightPoint mValue10 | `0x6641279  movss xmm4,[rsi+0x10]` | f32 +0x10 [V] | [V] |
| tag-3 desc +0x14 | 8 | LightPoint mValue14 | `0x66410a0  movsd xmm0,[rsi+0x14]` | float[2] +0x14 [V] | [V] |
| tag-3 desc +0x1C | 4 | LightPoint mValue1C | `0x66410c0  movss xmm0,[rsi+0x1C]` | f32 +0x1C [V] | [V] |
| tag-3 desc +0x20 | 1 | LightPoint mByte20 | `0x6641282  movzx r8d,byte ptr [rsi+0x20]` | byte +0x20 [V] | [V] |
| tag-3 desc +0x28 | 8 | LightPoint mValue28 | `0x66410e2  mov rcx,[rsi+0x28]` | qword +0x28 [V] | [V] |
| tag-3 desc +0x30 | 2 | LightPoint mValue30 | `0x66410de  movzx eax,word ptr [rsi+0x30]` | u16 +0x30 [V] | [V] |
| tag-3 desc +0x38 slices[0..5] | 16 | LightPoint slices {object,ctrl,vec4} stride 0x20 | `0x66410f4  mov rdx,[rsi+0x40]`<br>`0x6641117  movups xmm5,[rsi+0x48]` | slice k=0: control block (weak-count inc at [rdx+0xC]), vec4; six slices through +0x117 [V header RenderLightTag3Description] | [V] |
| tag-3 desc +0xF8 | 8 | LightPoint mValueF8 | `0x66410a5  movsd xmm3,[rsi+0xF8]` | float[2] at +0xF8/+0xFC [V] | [V] |
| tag-3 desc +0x100 | 4 | LightPoint mValue100 | `0x66410c9  movss xmm5,[rsi+0x100]` | f32 +0x100 [V] | [V] |
| tag-4 desc +0x00 | 16 | ShadowAtlasFrame mRow0 | `0x6640ec1  movups xmm6,[rsi]` | matrix row 0 +0x00 [V] | [V] |
| tag-4 desc +0x10 | 16 | ShadowAtlasFrame mRow1 | `0x6640ecb  movups xmm7,[rsi+0x10]` | matrix row 1 +0x10 [V] | [V] |
| tag-4 desc +0x20 | 16 | ShadowAtlasFrame mRow2 | `0x6640ed6  movups xmm8,[rsi+0x20]` | matrix row 2 +0x20 [V] | [V] |
| tag-4 desc +0x30 | 16 | ShadowAtlasFrame mRow3 | `0x6640ee3  movups xmm9,[rsi+0x30]` | matrix row 3 +0x30 [V] | [V] |
| tag-4 desc +0x40 | 8 | ShadowAtlasFrame mTexture | `0x66418f0  mov rbx,[rsi+0x40]` | texture pointer +0x40 [V] | [V] |
| tag-4 desc +0x48 | 8 | ShadowAtlasFrame mControlBlock | `0x6640f01  mov rcx,[rsi+0x48]`<br>`0x6640f0e  lock inc dword ptr [rcx+8]` | shared-ref control block +0x48, strong count incremented [V] | [V] |
| live desc entry RDX | 8 | desc pointer at visitor entry | - | RDX = desc pointer; RCX = RDX + 0x18 in all 24 samples (matches 0x6640c3c/0x6640c40/0x6640c44 call site) [LIVE docs/data/live/oc_u_er6_light_desc.txt:4-27] | [V live] |
| live desc scalar fields | 4 | per-sample f32 scalars | - | hit=3 RDX=149F40: f32 1.0 at +0xF0, f32 ~0.442 at +0xF4; hit=4 RDX=14A280: f32 1.0 at +0xF8, f32 100.0 at +0xFC; values differ per sample → live per-object data [LIVE docs/data/live/oc_u_er6_light_desc.txt:10,13] | [V live] |

Semantic member names: unknown [?]. The exe has no RTTI and no description member-name strings; LightDescriptions.h / RenderLight*Description.h type every field as mValue* placeholders with static_assert offsets only; live bytes confirm sizes/values, never names [V live]. Producer-side meanings (e.g. Atmosphere +0xA4/+0xA8 → Ambient +0x00/+0x08) are inference [I], not names.

## CLOSES?

CLOSES? NO — single blocking fact: the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 are not located anywhere in Minecraft.Windows.exe 1.26.62.01; all four vectors are write-only in static analysis (only the section-2 end-cursor writers [V]); no end-cursor pop/decrement or element-indexed read exists anywhere [V]; the available live capture (oc_u_er6_light_desc, entry sampling at 0x6640d80) observes the producer side only and its ret= names the producer's caller chain — it cannot observe a downstream reader [V live]; request.py cannot install a read/write watch on pass+0x800/+0x648/+0x4A0/+0x1D0 (entry capture only), and the consumer entry RVA is unknown so no function-entry capture can be queued for it; livemem has no pass VA (TLS value obfuscated) and may not scan [V live]. The missing capture would be a live element-level read watch on pass+0x800/+0x648/+0x4A0/+0x1D0 at an unknown consumer RVA — not expressible as a request.py function-entry capture. Description member value names also remain symbolically unknown [?] (secondary; no RTTI/description-name strings).

Resolved [V] and carried, not re-proven this unit: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h wins the group_visitors.md conflict; group_visitors.md had them swapped); the four end-cursor writers to pass+0x800/+0x648/+0x4A0/+0x1D0; description field offsets/sizes.

## TOOL REQUESTS

None — oc_u_er6_light_desc (visitor entry 0x6640d80) already ran and its result was consumed above; no function-entry capture can close the consumer blocker (no watchpoints; consumer RVA unknown), so nothing is queued. Throwaway aid: inline shell/python3 one-liner to group the 256-byte capture dumps into u64/f32 fields (manual hex counting was error-prone); not saved as a file. Helper scripts: None.
