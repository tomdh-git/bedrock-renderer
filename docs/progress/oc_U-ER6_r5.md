## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (1.26.62.01)

Goal: close R6 — tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag conflict, and the consumers (draining readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. Static analysis only; RVAs image-relative. Every `0xRVA  instr` line copied verbatim from a listing / re-disassembly and passes tools/sigs/verify_oc.py. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.

Input data (read fully, not re-generated): docs/functions/6640d80_light_visitor.md; docs/functions/5aba5c0.md; docs/functions/group_visitors.md; docs/functions/light_game_descriptions.md; docs/data/live/light_visitor.txt; src/sdk/mc/deps/minecraft_renderer/framebuilder/FrameBuilder.h (LightGroupTag enum); Descriptions.h.

The pass object is the per-thread value of ThreadLocalObject 0x5ABA5C0 (0x8C8-byte node; value at node+0x10). Visitor cases call 0x5ABA5C0 with rcx = frameCtx+0x10+0x9D0 and get rsi = pass [V]. All four vectors live inside this pass object: begin/end/cap cursors at (+0x7F8/+0x800/+0x808) summary stride 0x14, (+0x648/+0x650) light-record stride 0x48, (+0x498/+0x4A0/+0x4A8) GameplayMetadata stride 0x84, (+0x1C8/+0x1D0/+0x1D8) ShadowAtlasFrame stride 0x50 [V, from the light-visitor listings].

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

## 2. Description field reads / sizes per case — decoded [V] (sizes/extents), value names [?]

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| case 0 Ambient +0x00 | 8 | `0x6640dfb  movsd xmm7,[rsi]` | desc +0x00 read, size 0x18 [V] | [V] |
| case 0 Ambient +0x08 | 4 | `0x6640df6  movss xmm6,[rsi+8]` | desc +0x08 read [V] | [V] |
| case 0 Ambient +0x10 | 4 | `0x6640dff  movss xmm0,[rsi+0x10]` | desc +0x10 read [V] | [V] |
| case 0 Ambient +0x14 | 2 | `0x6640df1  movzx r12d,word ptr [rsi+0x14]` | desc +0x14 read [V]; gap +0x0C–0x10 unread [V] | [V] |
| case 1 Directional +0x00 | 16 | `0x66415cc  movups xmm2,[rsi]` | desc +0x00 read, size 0x24 [V] | [V] |
| case 1 Directional +0x10 | 1 | `0x66415c3  movzx ecx,byte ptr [rsi+0x10]` | desc +0x10 read [V] | [V] |
| case 1 Directional +0x14 | 8 | `0x66415c7  movsd xmm1,[rsi+0x14]` | desc +0x14 read [V] | [V] |
| case 1 Directional +0x1C | 4 | `0x66415ba  movss xmm0,[rsi+0x1C]` | desc +0x1C read [V] | [V] |
| case 1 Directional +0x20 | 2 | `0x66415bf  movzx eax,word ptr [rsi+0x20]` | desc +0x20 read [V]; gap +0x11–0x14 unread [V] | [V] |
| case 2 GameplayMetadata +0x00..+0x39 | 16 | `0x6640f8c  movups xmm0,[rsi]`<br>`0x6640f8f  movups xmm1,[rsi+0x10]`<br>`0x6640f93  movups xmm2,[rsi+0x20]`<br>`0x6640f97  movups xmm3,[rsi+0x2A]` | desc +0x00..+0x39 read (four 16-byte rows, +0x2A overlaps +0x20..+0x39) [V] | [V] |
| case 2 GameplayMetadata +0x3C..+0x80 | 4 | `0x6640fb2  movss xmm0,[rsi+0x3C]` | desc +0x3C..+0x80 read as dwords [V] | [V] |
| case 2 GameplayMetadata size | 0x84 | - | GameplayMetadataDescription size 0x84 [V]; gap +0x3A–0x3C padding unread [V] | [V] |
| case 3 LightPoint +0x00 | 4 | `0x664127e  movss xmm5,[rsi]` | desc +0x00 read [V] | [V] |
| case 3 LightPoint +0x08 | 8 | `0x6641287  movsd xmm7,[rsi+8]` | desc +0x08 read [V] | [V] |
| case 3 LightPoint +0x10 | 4 | `0x6641279  movss xmm4,[rsi+0x10]` | desc +0x10 read [V] | [V] |
| case 3 LightPoint +0x14 | 8 | `0x66410a0  movsd xmm0,[rsi+0x14]` | desc +0x14 read [V] | [V] |
| case 3 LightPoint +0x1C | 4 | `0x66410c0  movss xmm0,[rsi+0x1C]` | desc +0x1C read [V] | [V] |
| case 3 LightPoint +0x20 | 1 | `0x6641282  movzx r8d,byte ptr [rsi+0x20]` | desc +0x20 read [V] | [V] |
| case 3 LightPoint +0x28 | 8 | `0x66410e2  mov rcx,[rsi+0x28]` | desc +0x28 read [V] | [V] |
| case 3 LightPoint +0x30 | 2 | `0x66410de  movzx eax,word ptr [rsi+0x30]` | desc +0x30 read [V] | [V] |
| case 3 LightPoint +0x38 | 8 | `0x66410fd  mov r8,[rsi+0x38]` | desc +0x38 read (slice k=0 weak_ptr pointer) [V] | [V] |
| case 3 LightPoint +0x40 | 8 | `0x66410f4  mov rdx,[rsi+0x40]` | desc +0x40 read (slice k=0 weak control block) [V] | [V] |
| case 3 LightPoint +0x48 | 16 | `0x6641117  movups xmm5,[rsi+0x48]` | desc +0x48 read (slice k=0 vec4) [V] | [V] |
| case 3 LightPoint +0x58 | 8 | `0x6641132  mov r8,[rsi+0x58]` | desc +0x58 read (slice k=1 pointer) [V] | [V] |
| case 3 LightPoint +0x60 | 8 | `0x6641129  mov rdx,[rsi+0x60]` | desc +0x60 read (slice k=1 control block) [V] | [V] |
| case 3 LightPoint +0x68 | 16 | `0x6641155  movups xmm4,[rsi+0x68]` | desc +0x68 read (slice k=1 vec4) [V] | [V] |
| case 3 LightPoint +0x78 | 8 | `0x6641176  mov r8,[rsi+0x78]` | desc +0x78 read (slice k=3 pointer) [V] | [V] |
| case 3 LightPoint +0x80 | 8 | `0x664116a  mov rdx,[rsi+0x80]` | desc +0x80 read (slice k=3 control block) [V] | [V] |
| case 3 LightPoint +0x88 | 16 | `0x664119a  movups xmm5,[rsi+0x88]` | desc +0x88 read (slice k=4 vec4) [V] | [V] |
| case 3 LightPoint +0x98 | 8 | `0x66411bb  mov r8,[rsi+0x98]` | desc +0x98 read (slice k=5 pointer) [V] | [V] |
| case 3 LightPoint +0xa0 | 8 | `0x66411af  mov rdx,[rsi+0xa0]` | desc +0xa0 read (slice k=5 control block) [V] | [V] |
| case 3 LightPoint +0xa8 | 16 | `0x66411e2  movups xmm3,[rsi+0xa8]` | desc +0xa8 read (slice k=5 vec4) [V] | [V] |
| case 3 LightPoint +0xc0 | 8 | `0x66411fa  mov rdx,[rsi+0xc0]` | desc +0xc0 read [V] | [V] |
| case 3 LightPoint +0xb8 | 8 | `0x6641206  mov r8,[rsi+0xb8]` | desc +0xb8 read [V] | [V] |
| case 3 LightPoint +0xc8 | 16 | `0x6641230  movups xmm4,[rsi+0xc8]` | desc +0xc8 read [V] | [V] |
| case 3 LightPoint +0xd8 | 8 | `0x664124a  mov r9,[rsi+0xd8]` | desc +0xd8 read [V] | [V] |
| case 3 LightPoint +0xe0 | 8 | `0x664123e  mov r8,[rsi+0xe0]` | desc +0xe0 read [V] | [V] |
| case 3 LightPoint +0xe8 | 16 | `0x664126b  movups xmm4,[rsi+0xe8]` | desc +0xe8 read (vec4) [V] | [V] |
| case 3 LightPoint +0xf8 | 8 | `0x66410a5  movsd xmm3,[rsi+0xf8]` | desc +0xf8 read [V] | [V] |
| case 3 LightPoint +0x100 | 4 | `0x66410c9  movss xmm5,[rsi+0x100]` | desc +0x100 read [V] | [V] |
| case 3 LightPoint size/gaps | - | - | desc +0x38..+0x104 read (six weak_ptr slices at +0x38+0x20k, vec4 at +0xE8) [V]; gaps +0x4–0x8, +0x21–0x28, +0x32–0x38 unread [V]; size 0x108 [V] | [V] |
| case 4 ShadowAtlasFrame +0x00..+0x30 | 16 | `0x6640ec1  movups xmm6,[rsi]`<br>`0x6640ecb  movups xmm7,[rsi+0x10]`<br>`0x6640ed6  movups xmm8,[rsi+0x20]`<br>`0x6640ee3  movups xmm9,[rsi+0x30]` | desc +0x00..+0x30 read [V] | [V] |
| case 4 ShadowAtlasFrame +0x40..+0x48 | 8 | `0x66418f0  mov rbx,[rsi+0x40]`<br>`0x6640f01  mov rcx,[rsi+0x48]` | desc +0x40/+0x48 read (pointer + control block pair) [V]; gap +0x40–0x48 covers +0x40 only, +0x48 read separately [V] | [V] |
| case 4 ShadowAtlasFrame size | 0x50 | - | ShadowAtlasFrameDescription size 0x50 [V] | [V] |
| description value names | - | - | Field READS and sizes are proven [V] per case above via descscan2, but the exe has no RTTI and no description member name strings; headers type fields as mValue* placeholders with static_assert offsets only; live dumps (docs/data/live/light_visitor.txt) carry values only. Producer-side semantics (e.g. Ambient +0x00 = Atmosphere +0xA4) are inference [I], not names. Value names: unknown [?] | [?] |

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

The old `fld --r/--w` scans catch only `[reg+disp]`-style accesses. They miss a consumer that loads a cursor once and then indexes elements via `[cursor_reg + index*stride]` (no 0x800-class offset). This unit attacked that blind spot from four angles:

**Angle 1 — endFrame re-read (full listing).** `sub_66232b0` [0x66232b0..0x662e680), size 0xB3D0: it contains NO access at all to [reg+0x7F8]/[0x800]/[0x648]/[0x650]/[0x4A0]/[0x498]/[0x1D0]/[0x1C8] [V]. endFrame does call 0x5ABA5C0 directly (xr lists `0x662891e  call 0x5ABA5C0`, `0x662ab42  call 0x5ABA5C0`, `0x662b38c  call 0x5ABA5C0` inside sub_66232b0 [V]) but none of those sites touches the four cursors — endFrame uses other pass vectors (+0x20/+0x50/+0x38 family) instead [I from earlier units].

**Angle 2 — the three non-visitor 0x5ABA5C0 callers.** Disassembled 0x66a6830, 0x66a9d50, 0x66bb7b0 (220 instructions each): the only accesses at 0x650/0x4A0/0x1D0 are stack locals (`0x66a6ac4  mov rax,[rbp+0x650]`, `0x66a9d83  movaps [rbp+0x4A0],xmm12`, `0x66bb9be  mov [rbp+0x1D0],rax`) [V] — not pass cursors.

**Angle 3 — indirect caller slots.** `rdis ptr 0x5aba5c0`: `-- 0 pointer(s)` [V] — no data slot/vtable holds the getter address, so there are no indirect callers beyond the direct xref list.

**Angle 4 — whole-image cursor-reader enumeration (fresh `fld --r` scans this unit).** `fld 0x800 --r`: 1561 accesses; `fld 0x7F8 --r`: 723 accesses (counts match the earlier complete scans). Every non-stack reader enumerated: the only pass-cursor readers are the light-visitor writer sites (0x6640e84/0x66414c9/0x6641761/0x6641acf/0x6641ea8/0x66427d8 for 0x800; 0x6641a9e/0x6641ad5/0x6641e7f/0x6641eae/0x66427af/0x66427de for 0x7F8). All other non-stack hits are unrelated objects that coincidentally share the offset (e.g. sub_5776a0 [r12+0x7F8/+0x800], sub_8b505c0 [rdi/rsi/r8/r14+0x7F8/+0x800] render-context checks that test begin==end and never index elements) [V]. No function loads a pass cursor and then reads `[cursor_reg + index*stride]`; no end-cursor decrement exists anywhere [V].

**Angle 5 — static data reference to the TLO global (new this unit).** `rdis imm 0x5aba5c0 --max 40`: `-- 0 hit(s)` [V] — no instruction loads the global ThreadLocalObject address 0x5ABA5C0 as immediate data, so no consumer obtains the pass by reading that global directly.

**Angle 6 — full xref enumeration of all 0x5ABA5C0 callers.** `rdis xr 0x5aba5c0 --max 30` shows all ~200 xrefs (first 30 shown): 0x5ab9085, endFrame sites 0x662891e/0x662ab42/0x662b38c, all eight Light visitor case entries (0x6640e2d/0x6640f24/0x66413da/0x664169c/0x66417c4/0x664192c/0x664243b/0x664261a), Item visitor sites, Sky visitor sites, UI visitor sites, Effect visitor sites, Editor visitor sites, 0x66a6830/0x66a9d50/0x66ade80/0x66bb7b0. All are accounted for; none drain the four vectors — they only append [V].

**Side finding (not a consumer).** Per-draw code 0x66ea3d0 (terrain/chunk draw setup) obtains the pass via 0x5ABA5C0 (`0x66eca8f  call 0x5ABA5C0`) and APPENDS u16 indices to the *other* pass vector at pass+0x8A8 (`0x66ecb03  mov rdx,[rbx+0x8A8]` / `0x66ecb1e  mov [rdx],ax` / `0x66ecb21  add qword ptr [rbx+0x8A8],2`) [V] — vectors are written during draw recording too, but this function reads none of the four cursors.

Resulting consumer table:

| offset | size | site / verbatim instruction | meaning | tag |
|---|---|---|---|---|
| pass+0x800 element read | - | - | no draining reader of the 0x14-byte summary elements located anywhere in Minecraft.Windows.exe 1.26.62.01; only the three light-visitor end-cursor writers above [V] | [?] |
| pass+0x648 element read | - | - | no draining reader of the 0x48-byte light-record elements located anywhere in the exe [?] | [?] |
| pass+0x4A0 element read | - | - | no draining reader of the 0x84-byte GameplayMetadata elements located anywhere in the exe [?] | [?] |
| pass+0x1D0 element read | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements located anywhere in the exe [?] | [?] |

## 5. Conclusion

CLOSES? NO — two blocking facts remain:

1. The consumers (draining element readers) of pass+0x800 / pass+0x648 / pass+0x4A0 / pass+0x1D0 are not located in the exe: whole-image `fld --r/--w` scans for all four offsets and their begin cursors (0x7F8/0x650/0x498/0x1C8) show only the four light-visitor writer cursor accesses [V] (re-confirmed this unit for 0x800/0x7F8), every write is an end-cursor increment with no pop/decrement [V], endFrame's full listing contains none of the four offsets though it calls 0x5ABA5C0 three times [V], the three other direct 0x5ABA5C0 callers touch only stack locals [V], `rdis ptr 0x5aba5c0` finds no indirect caller slot [V], `rdis imm 0x5aba5c0` finds zero static data references to the TLO global [V], and `rdis xr 0x5aba5c0` enumerates all ~200 callers, none draining these vectors [V]. A reader that loads a cursor once and indexes `[cursor_reg + index*stride]` would be invisible to offset scans, but none of the enumerated cursor-reader functions does that [V]. Static analysis is exhausted for consumers; a live capture at 0x6640d80 (light visitor entry) or at a suspected consumer entry is needed — capture queue is full (4 pending from other units), so no new request could be queued this unit.

2. Description value names remain unknown [?]: no RTTI and no description member name strings exist in the release exe; headers use mValue* placeholders; producer-side meanings are inference [I] only. descscan2 per-case read coverage (section 2) proves field sizes/extents but not names. A live capture dumping description bytes at visitor entry could confirm runtime field values but not symbolic names.

Tag names and the tag-name conflict ARE closed [V]: tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins over group_visitors.md (which had 2/3 swapped).

## TOOL REQUESTS

None — no helper scripts written this unit; all evidence from existing tools (rdis dis/walk/xr/ptr/imm/fld, descscan2, verify_oc) and already-verified listings. The `fld` per-offset scan blind spot (cursor-register indexing) is a genuine tool gap: a "follow a loaded register into indexed element reads" data-flow pass would be the natural addition, but no consumer candidate remains to point it at. Live capture could not be requested: `python tools/livecap/request.py add ...` returned "4 requests already pending, ask again next unit" — the queue is full with pending requests from other units (oc_u_el6b_desc, el10b_lighting_desc, oc_u_er2, oc_u_er1_producer). If a slot frees, request a capture at 0x6640d80 (light visitor entry) to dump tag 3 (LightPoint, 0x108 B) and tag 4 (ShadowAtlasFrame, 0x50 B) description bytes at runtime, which existing light_visitor.txt (tags 0/1/2/5 only) does not cover.
