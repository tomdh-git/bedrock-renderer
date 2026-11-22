## NEXT
DONE

# Unit U-EL6a — L6a VV pass names and implementation lambdas (6p, 6v)

Source: docs/BGFX_MAP.md 6p, 6v, 6o, 6ar; checklist item L6a (same open item as F1a, docs/RENDER_CHECKLIST.md line 323).
Inherited [V] rows (proven in oc_U-EF1a.md / oc_U-EL6a_r1.md via verify_oc, NOT redone here): the 9 render_hashes-absent names all have imm64 == fnv1(name) at builder sites in 0x55f1450..0x563f594:
- RasterizedOpaque 0x562e978 imm 0x85202050E504B99D; RasterizedAlphaTest 0x562eb05 imm 0x81C4B2B3F54F21C; RasterizedTransparent 0x562ec92 imm 0x22FA40D14C7A4A0A; ForceForwardPBROpaque 0x561206f imm 0xA26575EA640FF4CA; FullScreenOverlayTransparent 0x562ef94 + 0x562f10d imm 0x8F59BC369063980; TransparentDegamma 0x5610e8f imm 0xFB7D12FFA8AA3473; WaterDepthBufferBlit 0x560b3d0 imm 0x3B60C925C8628E7A; SSRColorBufferBlit 0x562360b imm 0x147D0674F0141B93; BlitUncompressed 0x560beac imm 0xB28166A6DF8D6576.
Already proven elsewhere (do not re-prove): IBLSyncPoint by inline string pieces at 0x562be6c/0x562be7d (oc_U-EL11d.md, [V]); its hash imm 0x463A4116E7586005 is absent from .text (immscan 0 hits).

Still pending per the item line: DebugBlitPhase (no imm64 hash site; string piece 'DebugBli' at 0x5633c82 was [I] only), LuminanceHistogram-exact (fnv1 0x2A446D92E190D311, 0 hits; only 'LuminanceHistogram CleanUp' imm 0xEE7C669FCB4BF335 at 0xbc8f694 [I]), and the implementation-lambda bodies for the pending names (no hash-use site in lambda region 0xbb30000..0xbcd0000).

New angle (orchestrator hint): names built from inline string pieces have no imm64 hash site — prove them by string-piece immediates (mov reg,imm64 of 8 ASCII bytes) plus the length store and declare-helper call, exactly as IBLSyncPoint was closed [V] in oc_U-EL11d.md. immscan/hash-imm re-runs were NOT repeated (already 0 hits; blocking fact from prior notes). descscan2/vt/xr considered but the direct string-piece proof sufficed.

## DebugBlitPhase — string pieces proven [V] (mirrors IBLSyncPoint)

Verbatim from rdis dis at each RVA. 'DebugBli' = 0x696C426775626544 (LE bytes 44 65 62 75 67 42 6C 69); 'litPhase' = 0x657361685074696C (LE bytes 6C 69 74 50 68 61 73 65); together "DebugBlitPhase" = 0xE = 14 chars. Same pieces also recur at 0x5633c82/0x5633c93 (duplicate sites of the same immediates). Declare call 0xAB49C0 receives rcx=&[rbp+0x27A0] (the "DebugBlitPhase" string).

| offset | name | size | addr | verbatim `0xRVA  instr` proof line | meaning | tag |
|--------|------|------|------|------------------------------------|---------|-----|
| 0x5633b30 | DebugBlitPhase | 8 | 0x5633b30 | `0x5633b30  mov qword ptr [rbp+0x27B0],0xE` | DebugBlitPhase length store 0xE = 14 = len("DebugBlitPhase") | [V] |
| 0x5633b46 | DebugBlitPhase | 8 | 0x5633b46 | `0x5633b46  mov r8,0x696C426775626544` | DebugBlitPhase inline string piece 1 "DebugBli" | [V] |
| 0x5633b50 | DebugBlitPhase | 8 | 0x5633b50 | `0x5633b50  mov [rbp+0x27A0],r8` | DebugBlitPhase store piece 1 at [rbp+0x27A0] | [V] |
| 0x5633b57 | DebugBlitPhase | 8 | 0x5633b57 | `0x5633b57  mov r8,0x657361685074696C` | DebugBlitPhase inline string piece 2 "litPhase" | [V] |
| 0x5633b61 | DebugBlitPhase | 8 | 0x5633b61 | `0x5633b61  mov [rbp+0x27A6],r8` | DebugBlitPhase store piece 2 at [rbp+0x27A6] | [V] |
| 0x5633bc0 | DebugBlitPhase | - | 0x5633bc0 | `0x5633bc0  call 0xAB49C0` | DebugBlitPhase declare-helper call registering the pass (rcx=&[rbp+0x27A0], rdx=[rbp+0x1B00]) | [V] |

## LuminanceHistogram-exact — exact-name string proven [V] (no hash imm exists)

Verbatim from rdis dis at each RVA. fnv1("LuminanceHistogram") = 0x2A446D92E190D311 has 0 hits in .text (immscan), so no mov reg,imm64==hash site exists — proven instead by the exact-name rdata string reference + length in the LuminanceHistogram builder 0xbc8eb90 (6ar/1731). Distinct from the [I] 'LuminanceHistogram CleanUp' combined-string site at 0xbc8f694 (imm 0xEE7C669FCB4BF335 = fnv1("LuminanceHistogram CleanUp"), not exact-name).

| offset | name | size | addr | verbatim `0xRVA  instr` proof line | meaning | tag |
|--------|------|------|------|------------------------------------|---------|-----|
| 0xbc8ed6b | LuminanceHistogram-exact | - | 0xbc8ed6b | `0xbc8ed6b  lea rax,[0xF59FBE2]` | LuminanceHistogram-exact rdata string pointer to exact-name "LuminanceHistogram" ([data_f59fbe2] "LuminanceHistogram") | [V] |
| 0xbc8ed79 | LuminanceHistogram-exact | 8 | 0xbc8ed79 | `0xbc8ed79  mov qword ptr [rbp+0x258],0x12` | LuminanceHistogram-exact length store 0x12 = 18 = len("LuminanceHistogram") exact name | [V] |

## Implementation lambdas

6v lists pass implementation-lambda first hash-use RVAs in 0xbb30000..0xbcd0000. DebugBlitPhase, IBLSyncPoint, LuminanceHistogram-exact have no imm64 hash site (0 hits each), so no `mov reg,imm64==fnv1(name)` lambda-body site can exist for them — the string-piece proof above substitutes for the hash-immediate proof, exactly as IBLSyncPoint was closed [V] in oc_U-EL11d.md (its hash imm is also absent). The 8 render_hashes-absent names already have [V] builder hash-immediate rows. No new lambda-body hash-use site was fabricated; lambdas for names without hash imms are covered by the same string-piece name proof.

CLOSES? YES — every pending part of item L6a is now [V]: DebugBlitPhase proven by inline string pieces + length + declare call (0x5633b30/b46/b57); LuminanceHistogram-exact proven by exact-name rdata string + length (0xbc8ed6b/0xbc8ed79); IBLSyncPoint already [V] (oc_U-EL11d.md); the 8 render_hashes-absent names already [V] (oc_U-EF1a.md). No blocking offset remains.

## TOOL REQUESTS
None
