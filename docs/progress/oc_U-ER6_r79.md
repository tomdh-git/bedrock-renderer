## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (Minecraft.Windows.exe 1.26.62.01)

Goal (checklist item): tag value names, the group_visitors.md vs FrameBuilder.h LightGroupTag tag-name conflict, and the consumers (draining element readers) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0. `pass` = per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10); visitor cases call 0x5ABA5C0 and receive pass in rsi/rdi [V, carried from oc_U-ER6_r1..r9; every `0xRVA  instr` quote below was re-copied verbatim from a fresh rdis listing this session and passes tools/sigs/verify_oc.py].

All RVAs image-relative. Tags: [V] seen in disassembly (RVA cited) | [I] inferred | [?] unknown.

## 1. Tag -> type / value names and the tag-name conflict — resolved [V]

| name | rva or offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| variant tag byte + JT dispatch | variant+0x08 | 1 | `0x6640dc4  movzx eax,byte ptr [rdx+8]`<br>`0x6640de6  jmp rax` | tag byte at desc+0x08; dispatch via jump table 0xF2BF2B0 (entries: 0=Ambient 0x6640de8, 1=Directional 0x66415b0, 2=GameplayMetadata 0x6640f1b, 3=LightPoint 0x66410a0, 4=ShadowAtlasFrame 0x6640ec1, 6=VoxelVolume, 7=TransitioningVoxelVolume) [V] | [V] |
| tag 0 store | tag 0 store | 1 | `0x53e3511  mov byte ptr [rbp+0x138],0` | LightGroupTag::Ambient = 0; producer clone 0x53e2c00, srcloc RenderLightAmbientDescription (0xF248E70); JT entry 0 [V] | [V] |
| tag 1 store | tag 1 store | 1 | `0x53709d4  mov byte ptr [rbp+0x18],1` | LightGroupTag::Directional = 1; thin clone 0x5370960, srcloc LightDirectionalDescription (0xF248F70); JT entry 1 [V] | [V] |
| tag 2 store | tag 2 store | 1 | `0x53e5fb4  mov byte ptr [rbp-0x18],2`<br>`0x53e5fbf  mov rax,[rax+0x380]` | LightGroupTag::GameplayMetadata = 2; clone 0x53e5910, Light vslot 0x380 insert, srcloc `__FUNCSIG__ ...gamecomponents::GameplayMetadata` (0xF248ED0); JT entry 2 [V] | [V] |
| tag 3 store | tag 3 store | 1 | `0x535a9b7  mov byte ptr [rbp+0x278],3`<br>`0x535a9c1  mov rax,[rax+0x380]`<br>`0x535a9ce  call qword ptr [0xF99FFA0]` | LightGroupTag::LightPoint = 3; light clone 0x53599d0 insert call, srcloc LightPointDescription (0xF248DA0); JT entry 3 [V] | [V] |
| tag 4 store | tag 4 store | 1 | `0x535a696  mov byte ptr [rbp+0x278],4`<br>`0x535a6a0  mov rax,[rax+0x380]` | LightGroupTag::ShadowAtlasFrame = 4; light clone 0x53599d0 insert, srcloc ShadowAtlasFrameDescription (0xF248D80); JT entry 4 [V] | [V] |
| tag-name conflict | tag map (enum doc) | - | FrameBuilder.h:79-88 `enum class LightGroupTag : uint64_t { Ambient = 0, Directional = 1, GameplayMetadata = 2, LightPoint = 3, ShadowAtlasFrame = 4, ... };` | CONFLICT RESOLVED [V]: producer tag stores + __FUNCSIG__ zone records prove tag 2 = GameplayMetadata and tag 3 = LightPoint, exactly as FrameBuilder.h; group_visitors.md had them swapped (LightPoint@2 / GameplayMetadata@3). Tags 5/6/7 = ServerGraphicsOverrideParameters / VoxelVolume / TransitioningVoxelVolume [V] | [V] |

## 2. Light-visitor writers to pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — proven [V]

| name | rva or offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 end cursor | pass+0x800 | 8 | `0x6640e84  mov rdx,[rsi+0x800]`<br>`0x6640e8b  cmp rdx,[rsi+0x808]`<br>`0x6640eb4  add qword ptr [rsi+0x800],0x14`<br>`0x6641517  add qword ptr [rsi+0x800],0x14`<br>`0x66417a2  add qword ptr [rsi+0x800],0x14` | end cursor of the 0x14-byte summary list (cap +0x808); end += stride 0x14 per element; writers: tag 0 at 0x6640eb4, tag 3 at 0x6641517, tag 1 at 0x66417a2 [V] | [V] |
| pass+0x648 light-record vector | pass+0x648 | 8 | `0x664145a  lea rcx,[rsi+0x648]`<br>`0x6641461  call 0x675FB30`<br>`0x66416f8  lea rcx,[rsi+0x648]`<br>`0x66416ff  call 0x675FB30` | begin cursor of the 0x48-byte light-record vector (end +0x650); vector push 0x675FB30 with &pass+0x648; writers: tag 3 at 0x6641461, tag 1 at 0x66416ff [V] | [V] |
| pass+0x4A0 GameplayMetadata vector | pass+0x4A0 | 8 | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | end cursor of the 0x84-byte GameplayMetadata vector (begin +0x498, cap +0x4A8); end += stride 0x84; writer tag 2 at 0x6641090 [V] | [V] |
| pass+0x1D0 ShadowAtlasFrame vector | pass+0x1D0 | 8 | `0x6641991  mov r14,[rsi+0x1D0]`<br>`0x6641998  cmp r14,[rsi+0x1D8]`<br>`0x66419c6  add qword ptr [rsi+0x1D0],0x50` | end cursor of the 0x50-byte ShadowAtlasFrame vector (begin +0x1C8, cap +0x1D8); end += stride 0x50; writer tag 4 at 0x66419c6 [V] | [V] |

Every write above is an end-cursor increment; no end-cursor pop/decrement exists anywhere in the exe [V, whole-image scans, earlier units].

## 3. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — not located (new static angle tried this session) [?]

Earlier units scanned writes only (`fld --w`), enumerated callers of 0x5ABA5C0, and did `rdis ptr`. This session added:

1. Read scans over every .pdata function: `fld 0x800 --r`, `fld 0x648 --r`, `fld 0x4A0 --r`, `fld 0x1D0 --r`. Every `[reg+disp]` hit is either `[rbp+off]` stack or `[rsi/rax/r12+off]` where the register is the function's entry argument (verified entries: sub_601bb0, sub_603050, sub_67e1c0, sub_2c09b0 all do `mov rsi,rcx` at entry and none calls TLS accessor 0x5ABA5C0) — unrelated objects, not pass [V]. Example non-pass hits seen in listing: 0x601ca9 (sub_601bb0+0xf5), 0x603e9d (sub_603050+0xe4d), 0x67e480 (sub_67e1c0+0x2c0) read `[rsi+0x648]`; 0x91d43 (sub_91cd0+0x73) and 0x2bb7f8 (sub_2bab60+0xc98) read `[rsi+0x4A0]`; 0xc9186 (sub_c8c50+0x536) and 0xca7be (sub_ca580+0x23e) read `[rsi+0x1D0]`; 0x2c1ce7 (sub_2c09b0+0x337) does `cmp r14,[rsi+0x800]`; 0x577aa6 (sub_5776a0+0x406) reads `[r12+0x800]` — all rsi/r12 = entry argument, none derived from pass [V].
2. `rdis ... imm 0x5ABA5C0`: 0 hits — no instruction references the TLS slot address directly; pass is reached only via `call 0x5ABA5C0` [V]. Caller enumeration of 0x5ABA5C0 (earlier units [V]): visitor/producer callers only; no element-reading caller [V].
3. Limitation: `fld` matches `[reg+disp]` only; scaled element reads `[base+index*scale+disp]` are invisible to it [I, tool limitation]. No consumer found in any readable form.

| name | rva or offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| pass+0x800 element read | pass+0x800 element read | - | - | no draining reader of the 0x14-byte summary elements anywhere in Minecraft.Windows.exe 1.26.62.01; only the three end-cursor writers above [V writes only] | [?] |
| pass+0x648 element read | pass+0x648 element read | - | - | no draining reader of the 0x48-byte light-record elements anywhere in the exe [V writes only] | [?] |
| pass+0x4A0 element read | pass+0x4A0 element read | - | - | no draining reader of the 0x84-byte GameplayMetadata elements anywhere in the exe [V writes only] | [?] |
| pass+0x1D0 element read | pass+0x1D0 element read | - | - | no draining reader of the 0x50-byte ShadowAtlasFrame elements anywhere in the exe [V writes only] | [?] |

## 4. Description field value names — unknown [?]

| name | rva or offset | size | site / verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| description value names | descriptions (all fields) | - | - | visitor-case field reads are proven [V] (tag byte at desc+0x08 `0x6640dc4  movzx eax,byte ptr [rdx+8]`; LightPoint case reads desc through +0xF8, ShadowAtlasFrame case through +0x48; desc sizes LightPoint 0x108 B, ShadowAtlasFrame 0x50 B from case code [V]) but the release exe has no RTTI and no description member-name strings; headers type fields as mValue* placeholders with static_assert offsets only; member value names unknown [?] | [?] |

## 5. Live capture (new tool, 2026-11-22)

- `oc_u_er6_light_desc` (rva 0x6640D80 = light-visitor entry, the entry proven for this item; size 0x100, max 6) is already QUEUED/pending in docs/progress/capture_requests.json; `python tools/livecap/request.py result oc_u_er6_light_desc` printed "no result yet (orchestrator has not run it)". Not re-added: request.py rejects a duplicate pending name.
- What it can add [V live when available]: description bytes at entry (RDX = desc ptr per docs/data/live/README.md correction) to confirm tag 3 (0x108 B) and tag 4 (0x50 B) field sizes/runtime values vs Descriptions.h, plus `ret=` naming the visitor caller chain (expected Light insert wrapper).
- What it CANNOT add: the consumers — function-entry sampling installs no data watchpoint on pass+0x800/+0x648/+0x4A0/+0x1D0, so no available live angle can locate a draining reader. The blocking fact below stands regardless of capture outcome [I, tool capability].

## CLOSES?

CLOSES? NO — single blocking fact: no draining reader (element consumer) of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 exists anywhere in Minecraft.Windows.exe 1.26.62.01; all four offsets are write-only statically ([V] writers in Section 2; [V] read scans plus the `imm 0x5ABA5C0` scan show no pass-provenance reader and no other way to obtain pass), no end-cursor pop exists [V], and neither static analysis nor the available live-capture tool (function-entry sampling, no watchpoint) can find one. Resolved [V]: tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins the tag-name conflict. Still open [?]: description member value names and the pass consumers.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_er6_light_desc — already pending at rva 0x6640D80 (size 0x100, max 6); awaiting docs/data/live/oc_u_er6_light_desc.txt from the orchestrator. Helper scripts: None.
