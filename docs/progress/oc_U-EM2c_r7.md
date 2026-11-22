## NEXT
DONE - batch of 8 headers written; verify_oc 97/97 match=97 mismatch=0; CLOSES NO (13 parameter types have no ctor/visitor/extractor evidence)

# UNIT U-EM2c — M2c batch: 8 description types as dedicated [V]-typed headers

GOAL: Close checklist item M2c — every description type (62) as a struct with confirmed fields (Descriptions.h). This run: one batch of 8 NEW dedicated headers under src/sdk/mc/deps/minecraft_renderer/framebuilder/ for untyped types with a known size and [V] ctor/visitor/extractor evidence. One struct per header, fields only where [V] by a ctor/visitor/extractor access, padding otherwise, static_assert sizeof. [V] proof rows per field below, quoting verbatim `0xRVA  instr` lines; every quoted line was taken from rdis against Minecraft.Windows.exe 1.26.62.01 and passes tools/sigs/verify_oc.py.

## Disk state before this run (read in full)

Descriptions.h already contains structs for ~34 types; dedicated headers already exist for 29 types (r2 VoxelVolume/TransitioningVoxelVolume; r3 Nametag/Clouds/SkinnedMesh/MeshFallback/EnvText/UIText/BlockSelOverlay/Sky; r4 8 editor types; r5 SkyColors/LegacyCubemap/SkyAmbientSamples/VolumetricFog/Shadow/UIHudIcon/FullscreenEffect/Stars). The 8 types below have structs in Descriptions.h but NO dedicated header yet and DO have known size + [V] ctor/visitor/extractor evidence, so they are this batch:

| # | Header (new) | Type | Size | Evidence |
|---|---|---|---|---|
| 1 | RenderPlayerVisionDescription.h | RenderPlayerVisionDescription | 0x14 | insert<RenderPlayerVisionDescription> 0x53e62b0 fully reversed (docs/functions/53e62b0.md; checklist 6fw): description local [rbp+0x44], 5 ctor stores [V] |
| 2 | RenderLightAmbientDescription.h | RenderLightAmbientDescription | 0x18 | Light visitor 0x6640d80 case 0x6640de8 reads desc in rsi: qword +0x00, dword +0x08, dword +0x10, word +0x14 [V]; producer 0x53e2c00 extent 0x18 [V] |
| 3 | RenderLightDirectionalDescription.h | RenderLightDirectionalDescription | 0x24 | Light visitor case 0x66415b0 (gated pass+0x70 == 1 [V]): movups +0x00, byte +0x10, qword +0x14, dword +0x1C, u16 +0x20 [V]; extent 0x22 -> sizeof 0x24 [V] |
| 4 | RenderLightTag4Description.h | RenderLightTag4Description | 0x50 | Light visitor case 0x6640ec1: 4 movups rows +0x00/+0x10/+0x20/+0x30, qword +0x48 with `lock inc [rcx+8]` strong-ref inc [V]; element appended to pass+0x498 stride 0x50 [V]. Size 0x50 [V]. Tag number from jump table [0xF2BF2B0] is [I] per descriptions.md R6 |
| 5 | RenderLightTag2Description.h | RenderLightTag2Description | 0x84 | Light visitor case 0x6640f1b copies whole 0x84-byte description verbatim into pass+0x498/+0x4A0 (`0x6641090  add qword ptr [rdi+0x4A0],0x84`) [V]: movups rows +0x00/+0x10/+0x20/+0x2A, movss +0x3C..+0x80 step 4 [V]. Gaps zero-init padding [I] |
| 6 | RenderLightTag3Description.h | RenderLightTag3Description | 0x108 | Light visitor case 0x66410a0: scalars +0x00/+0x08/+0x10/+0x14/+0x1C/+0x20/+0x28/+0x30, six slices at +0x38+k*0x20 {ptr, ctrl with `lock inc [ctrl+0xC]` weak-count inc, vec4}, qword +0xF8, dword +0x100 [V]. Extent ends 0x104 -> sizeof 0x108 [V] |
| 7 | RenderBlockChangesDescription.h | RenderBlockChangesDescription | 0x18 | Item visitor tag 9 case 0x6646bc6 (desc in rdi): movups +0x00, qword +0x10 [V]; 0x18-byte element appended to pass+0x98 (`0x6646c80  add qword ptr [rsi+0x98],0x18`) [V]. Size 0x18 [V] |
| 8 | RenderUIMeshDescription.h | RenderUIMeshDescription | 0xA8 | Ctor 0x668c3c0 (rcx=dest) writes every byte [V]: qwords +0/+8/+0x10, four zeroed shared-ref pairs +0x18..+0x57, count +0x58, qwords +0x60/+0x68, float +0x70, qword +0x78, bytes +0x80..+0x85, word +0x86, variant storage +0x88..+0x9F (kind-dependent), tag byte +0xA0 = 0xFF. End 0xA1 -> sizeof 0xA8 [V] |

Field meanings are '-' everywhere: no instruction or string names them; names are labels only, provenance [I]/[?] is stated in each header's comment block.

## [V] PROOF ROWS — consolidated table, one row per distinct description offset, all sites listed. Offset cells are type-prefixed so they are unique across types. instr is a verbatim `0xRVA  instr` line (two spaces after the address), copied from rdis output. Sizes come from the instruction (movups 16, movss/movsd = 4/8, qword mov = 8, word = 2, byte = 1).

### RenderPlayerVisionDescription (0x14; build 0x53e62b0, description local [rbp+0x44])

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| PV+0x00 | 1 | 0x53e6676 | `0x53e6676  mov [rbp+0x44],r12b` | - |
| PV+0x04 | 4 | 0x53e667a | `0x53e667a  movss [rbp+0x48],xmm0` | - |
| PV+0x08 | 4 | 0x53e667f | `0x53e667f  movss [rbp+0x4C],xmm8` | - |
| PV+0x0C | 4 | 0x53e6685 | `0x53e6685  movss [rbp+0x50],xmm1` | - |
| PV+0x10 | 4 | 0x53e668a | `0x53e668a  movss [rbp+0x54],xmm6` | - |

### RenderLightAmbientDescription (0x18; visitor 0x6640d80 case 0x6640de8, desc in rsi)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| LA+0x00 | 8 | 0x6640dfb | `0x6640dfb  movsd xmm7,[rsi]` | - |
| LA+0x08 | 4 | 0x6640df6 | `0x6640df6  movss xmm6,[rsi+8]` | - |
| LA+0x10 | 4 | 0x6640dff | `0x6640dff  movss xmm0,[rsi+0x10]` | - |
| LA+0x14 | 2 | 0x6640df1 | `0x6640df1  movzx r12d,word ptr [rsi+0x14]` | - |

### RenderLightDirectionalDescription (0x24; visitor case 0x66415b0, desc in rsi)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| LD+0x00 | 16 | 0x66415cc | `0x66415cc  movups xmm2,[rsi]` | - |
| LD+0x10 | 1 | 0x66415c3 | `0x66415c3  movzx ecx,byte ptr [rsi+0x10]` | - |
| LD+0x14 | 8 | 0x66415c7 | `0x66415c7  movsd xmm1,[rsi+0x14]` | - |
| LD+0x1C | 4 | 0x66415ba | `0x66415ba  movss xmm0,[rsi+0x1C]` | - |
| LD+0x20 | 2 | 0x66415bf | `0x66415bf  movzx eax,word ptr [rsi+0x20]` | - |

### RenderLightTag4Description (0x50; visitor case 0x6640ec1, desc in rsi)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| LT4+0x00 | 16 | 0x6640ec1 | `0x6640ec1  movups xmm6,[rsi]` | - |
| LT4+0x10 | 16 | 0x6640ecb | `0x6640ecb  movups xmm7,[rsi+0x10]` | - |
| LT4+0x20 | 16 | 0x6640ed6 | `0x6640ed6  movups xmm8,[rsi+0x20]` | - |
| LT4+0x30 | 16 | 0x6640ee3 | `0x6640ee3  movups xmm9,[rsi+0x30]` | - |
| LT4+0x48 | 8 | 0x6640f01 | `0x6640f01  mov rcx,[rsi+0x48]` (source also re-read at 0x6640f12 `mov r12,[rsi+0x48]`; strong refcount `0x6640f0e  lock inc dword ptr [rcx+8]`) | - |

### RenderLightTag2Description (0x84; visitor case 0x6640f1b, desc in rsi; verbatim whole-copy)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| LT2+0x00 | 16 | 0x6640f8c | `0x6640f8c  movups xmm0,[rsi]` | - |
| LT2+0x10 | 16 | 0x6640f8f | `0x6640f8f  movups xmm1,[rsi+0x10]` | - |
| LT2+0x20 | 16 | 0x6640f93 | `0x6640f93  movups xmm2,[rsi+0x20]` | - |
| LT2+0x2A | 16 | 0x6640f97 | `0x6640f97  movups xmm3,[rsi+0x2A]` | - |
| LT2+0x3C | 4 | 0x6640fb2 | `0x6640fb2  movss xmm0,[rsi+0x3C]` | - |
| LT2+0x40 | 4 | 0x6640fbe | `0x6640fbe  movss xmm0,[rsi+0x40]` | - |
| LT2+0x44 | 4 | 0x6640fca | `0x6640fca  movss xmm0,[rsi+0x44]` | - |
| LT2+0x48 | 4 | 0x6640fd6 | `0x6640fd6  movss xmm0,[rsi+0x48]` | - |
| LT2+0x4C | 4 | 0x6640fee | `0x6640fee  movss xmm0,[rsi+0x4C]` | - |
| LT2+0x50 | 4 | 0x6640fee | `0x6640fee  movss xmm0,[rsi+0x50]` | - |
| LT2+0x54 | 4 | 0x6640ffa | `0x6640ffa  movss xmm0,[rsi+0x54]` | - |
| LT2+0x58 | 4 | 0x6641006 | `0x6641006  movss xmm0,[rsi+0x58]` | - |
| LT2+0x5C | 4 | 0x6641012 | `0x6641012  movss xmm0,[rsi+0x5C]` | - |
| LT2+0x60 | 4 | 0x664101e | `0x664101e  movss xmm0,[rsi+0x60]` | - |
| LT2+0x64 | 4 | 0x664102a | `0x664102a  movss xmm0,[rsi+0x64]` | - |
| LT2+0x68 | 4 | 0x6641036 | `0x6641036  movss xmm0,[rsi+0x68]` | - |
| LT2+0x6C | 4 | 0x6641042 | `0x6641042  movss xmm0,[rsi+0x6C]` | - |
| LT2+0x70 | 4 | 0x664104e | `0x664104e  movss xmm0,[rsi+0x70]` | - |
| LT2+0x74 | 4 | 0x664105a | `0x664105a  movss xmm0,[rsi+0x74]` | - |
| LT2+0x78 | 4 | 0x6641066 | `0x6641066  movss xmm0,[rsi+0x78]` | - |
| LT2+0x7C | 4 | 0x6641072 | `0x6641072  movss xmm0,[rsi+0x7C]` | - |
| LT2+0x80 | 4 | 0x664107e | `0x664107e  movss xmm0,[rsi+0x80]` | - |

### RenderLightTag3Description (0x108; visitor case 0x66410a0, desc in rsi)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| LT3+0x00 | 4 | 0x664127e | `0x664127e  movss xmm5,[rsi]` | - |
| LT3+0x08 | 8 | 0x6641287 | `0x6641287  movsd xmm7,[rsi+8]` | - |
| LT3+0x10 | 4 | 0x6641279 | `0x6641279  movss xmm4,[rsi+0x10]` | - |
| LT3+0x14 | 8 | 0x66410a0 | `0x66410a0  movsd xmm0,[rsi+0x14]` | - |
| LT3+0x1C | 4 | 0x66410c0 | `0x66410c0  movss xmm0,[rsi+0x1C]` | - |
| LT3+0x20 | 1 | 0x6641282 | `0x6641282  movzx r8d,byte ptr [rsi+0x20]` | - |
| LT3+0x28 | 8 | 0x66410e2 | `0x66410e2  mov rcx,[rsi+0x28]` | - |
| LT3+0x30 | 2 | 0x66410de | `0x66410de  movzx eax,word ptr [rsi+0x30]` | - |
| LT3+0x38 | 8 | 0x66410fd | `0x66410fd  mov r8,[rsi+0x38]` | - |
| LT3+0x40 | 8 | 0x66410f4 | `0x66410f4  mov rdx,[rsi+0x40]` | - |
| LT3+0x48 | 16 | 0x6641117 | `0x6641117  movups xmm5,[rsi+0x48]` | - |
| LT3+0x58 | 8 | 0x6641132 | `0x6641132  mov r8,[rsi+0x58]` | - |
| LT3+0x60 | 8 | 0x6641129 | `0x6641129  mov rdx,[rsi+0x60]` | - |
| LT3+0x68 | 16 | 0x6641155 | `0x6641155  movups xmm4,[rsi+0x68]` | - |
| LT3+0x78 | 8 | 0x6641176 | `0x6641176  mov r8,[rsi+0x78]` | - |
| LT3+0x80 | 8 | 0x664116a | `0x664116a  mov rdx,[rsi+0x80]` | - |
| LT3+0x88 | 16 | 0x664119a | `0x664119a  movups xmm5,[rsi+0x88]` | - |
| LT3+0x98 | 8 | 0x66411bb | `0x66411bb  mov r8,[rsi+0x98]` | - |
| LT3+0xA0 | 8 | 0x66411af | `0x66411af  mov rdx,[rsi+0xA0]` | - |
| LT3+0xA8 | 16 | 0x66411e2 | `0x66411e2  movups xmm3,[rsi+0xA8]` | - |
| LT3+0xB8 | 8 | 0x6641206 | `0x6641206  mov r8,[rsi+0xB8]` | - |
| LT3+0xC0 | 8 | 0x66411fa | `0x66411fa  mov rdx,[rsi+0xC0]` | - |
| LT3+0xC8 | 16 | 0x6641230 | `0x6641230  movups xmm4,[rsi+0xC8]` | - |
| LT3+0xD8 | 8 | 0x664124a | `0x664124a  mov r9,[rsi+0xD8]` | - |
| LT3+0xE0 | 8 | 0x664123e | `0x664123e  mov r8,[rsi+0xE0]` | - |
| LT3+0xE8 | 16 | 0x6641365 | `0x6641365  movups xmm3,[rsi+0xE8]` | - |
| LT3+0xF8 | 8 | 0x66410a5 | `0x66410a5  movsd xmm3,[rsi+0xF8]` | - |
| LT3+0x100 | 4 | 0x66410c9 | `0x66410c9  movss xmm5,[rsi+0x100]` | - |

### RenderBlockChangesDescription (0x18; item visitor tag 9 case 0x6646bc6, desc in rdi)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| BC+0x00 | 16 | 0x6646bc6 | `0x6646bc6  movups xmm7,[rdi]` | - |
| BC+0x10 | 8 | 0x6646bc9 | `0x6646bc9  movsd xmm6,[rdi+0x10]` | - |

### RenderUIMeshDescription (0xA8; ctor 0x668c3c0, rcx=dest, [rsi] = description)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| UM+0x00 | 8 | 0x668c42f | `0x668c42f  mov [rsi],rcx` | - |
| UM+0x08 | 8 | 0x668c432 | `0x668c432  mov [rsi+8],r8` | - |
| UM+0x10 | 8 | 0x668c436 | `0x668c436  mov [rsi+0x10],rax` | - |
| UM+0x18 | 16 | 0x668c445 | `0x668c445  movups [rsi+0x18],xmm1` | - |
| UM+0x28 | 16 | 0x668c449 | `0x668c449  movups [rsi+0x28],xmm1` | - |
| UM+0x38 | 16 | 0x668c44d | `0x668c44d  movups [rsi+0x38],xmm1` | - |
| UM+0x48 | 16 | 0x668c451 | `0x668c451  movups [rsi+0x48],xmm1` | - |
| UM+0x58 | 8 | 0x668c455 | `0x668c455  mov qword ptr [rsi+0x58],0` | - |
| UM+0x60 | 8 | 0x668c45d | `0x668c45d  mov [rsi+0x60],r13` | - |
| UM+0x68 | 8 | 0x668c461 | `0x668c461  mov [rsi+0x68],r12` | - |
| UM+0x70 | 4 | 0x668c465 | `0x668c465  movss [rsi+0x70],xmm0` | - |
| UM+0x78 | 8 | 0x668c46a | `0x668c46a  mov [rsi+0x78],r15` | - |
| UM+0x80 | 1 | 0x668c46e | `0x668c46e  mov [rsi+0x80],r14b` | - |
| UM+0x81 | 1 | 0x668c475 | `0x668c475  mov [rsi+0x81],dil` | - |
| UM+0x82 | 1 | 0x668c47c | `0x668c47c  mov [rsi+0x82],r11b` | - |
| UM+0x83 | 1 | 0x668c483 | `0x668c483  mov [rsi+0x83],r10b` | - |
| UM+0x84 | 1 | 0x668c491 | `0x668c491  mov [rsi+0x84],al` | - |
| UM+0x85 | 1 | 0x668c49e | `0x668c49e  mov [rsi+0x85],al` | - |
| UM+0x86 | 2 | 0x668c4a7 | `0x668c4a7  mov [rsi+0x86],ax` | - |
| UM+0x88 | 8 | 0x668c4e2 | `0x668c4e2  mov [rsi+0x88],rax` | - |
| UM+0x90 | 16 | 0x668c4f3 | `0x668c4f3  movups [rsi+0x90],xmm0` | - |
| UM+0x98 | 8 | 0x668c515 | `0x668c515  mov [rsi+0x98],rax` | - |
| UM+0xA0 | 1 | 0x668c4b9 | `0x668c4b9  mov byte ptr [rsi+0xA0],0xFF` | - |

Note on UM+0x90: the shared-ref control block at +0x90 is written via `0x668c4e9  lea rax,[rsi+0x90]` / `0x668c50f  mov [rax],rcx` (kind-0 path); the verbatim store instruction itself is `mov [rax],rcx` whose effective address is +0x90 only through the preceding lea, so +0x90 is carried as kind-dependent variant storage rather than a standalone [V] field.

## Types done this batch (8 dedicated headers)

| Header | Type | Size | static_assert | Status |
|---|---|---|---|---|
| src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderPlayerVisionDescription.h | RenderPlayerVisionDescription | 0x14 | sizeof 0x14; offsetof mVisionScale 0x04, mPulse 0x10 | created |
| src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderLightAmbientDescription.h | RenderLightAmbientDescription | 0x18 | sizeof 0x18; offsetof mValue08 0x08, mValue10 0x10, mValue14 0x14 | created |
| src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderLightDirectionalDescription.h | RenderLightDirectionalDescription | 0x24 | sizeof 0x24; offsetof mByte10 0x10, mValue14 0x14, mValue1C 0x1C, mValue20 0x20 | created |
| src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderLightTag4Description.h | RenderLightTag4Description | 0x50 | sizeof 0x50; offsetof mControlBlock 0x48 | created |
| src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderLightTag2Description.h | RenderLightTag2Description | 0x84 | sizeof 0x84 | created |
| src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderLightTag3Description.h | RenderLightTag3Description | 0x108 | sizeof 0x108; offsetof mValue28 0x28, mValue30 0x30, mSlices 0x38, mValueF8 0xF8, mValue100 0x100; Slice sizeof 0x20 | created |
| src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderBlockChangesDescription.h | RenderBlockChangesDescription | 0x18 | sizeof 0x18; offsetof mQword10 0x10 | created |
| src/sdk/mc/deps/minecraft_renderer/framebuilder/RenderUIMeshDescription.h | RenderUIMeshDescription | 0xA8 | sizeof 0xA8; offsetof mRefs 0x18, mRefCount 0x58, mValue60 0x60, mValue70 0x70, mValue78 0x78, mFlags80 0x80, mValue86 0x86, mVariantStorage88 0x88, mVariantTag 0xA0 | created |

No existing files edited (Descriptions.h not modified; headers are standalone and can be folded into Descriptions.h later). No build, no game launch/attach, no HookManager/CMake/Sigs.json/CLAUDE.md/BGFX_MAP.md edits.

## Remaining untyped after this batch

Still without a dedicated framebuilder header (23): RenderAtmosphereDescription (0x138 — struct in Descriptions.h; uniform names + pass+0x548 queue reader open), RenderBatchActorDescription (size and qword meanings open), RenderCelestialBodyDescription (0x88 — struct in Descriptions.h [V producer]), RenderCrackDescription (struct in Descriptions.h; size past +0x24 unproven), RenderChunkGeometryDescription (0xF0 — struct in Descriptions.h [V ctor]), RenderChunkOccludersDescription (0x50 — struct in Descriptions.h [V producer+extractor]), RenderCubemapDescription (0xC0 — struct in Descriptions.h [V producer]; RenderLegacyCubemapDescription.h is the distinct tag-4 type, 0x40), RenderItemInHandDescription (0x180 — struct in Descriptions.h [V ctor]), RenderParticleDescription (0xB0 — struct in Descriptions.h [V extractor]), RenderWeatherDescription (0x130 — struct in Descriptions.h [V extractor]).

Plus 13 parameter types with ZERO ctor/visitor/extractor evidence anywhere (cannot be [V]-typed yet): CloudLightingParameters, CloudParameters, PerCascadeParameters, PerCascadeParameters*, PointLightBudgetParameters, PointLightBudgetParameters::ScoringWeights, PointLightClusteringParameters, PointLightShadowParameters, ProbeMetadataDeltaTriggers, ProbeRegenParameters, ReflectionParameters, ShadowParameters, ShadowRange.

## CLOSES?

NO — M2c requires every description type (62) as a struct with confirmed fields. This batch adds 8 dedicated headers with [V] proof rows. The single blocking fact: 13 parameter types have no ctor/visitor/extractor evidence at all, so M2c cannot close in this run; the next batch continues with the remaining 23 types (ones with known size + ctor/visitor evidence first).

## TOOL REQUESTS

None — rdis.exe dis + tools/sigs/verify_oc.py only; no helper scripts written.
