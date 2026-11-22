## NEXT
DONE

# Unit U-EL6a — L6a VV pass names and implementation lambdas (6p, 6v)

Source: docs/BGFX_MAP.md 6p, 6v, 6o, 6ar; checklist item L6a = same open item as F1a (docs/RENDER_CHECKLIST.md line 323).
Pending from oc_U-EF1a.md (check OK 106 rows, not closed):
- IBLSyncPoint and DebugBlitPhase: no imm64 == fnv1(name) site located; only inline string pieces ('IBLSyncP' at 0x562be6c, 'DebugBli' at 0x5633c82) tagged [I].
- 8 names absent from render_hashes.txt (no exact-name hash row): RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent, ForceForwardPBROpaque, FullScreenOverlayTransparent, TransparentDegamma, WaterDepthBufferBlit, SSRColorBufferBlit, BlitUncompressed, LuminanceHistogram-exact.
- 6v implementation-lambda hash-use RVAs not covered for any of the above.

Method: for each pending name, compute FNV-1 64 (basis 0xcbf29ce484222325, prime 0x100000001b3; see 6p), search .text for the imm64 (mov reg,0x<imm64>) site, verify any hit verbatim with rdis; if no site exists, prove absence by full .text imm64 scan (tools/sigs/immscan.py) and tag [?]. String-piece sites quoted verbatim from rdis are tagged [I] (hash not proven). One row per distinct offset; all sites of an offset listed in the row. Hash immediates cross-checked: imm == fnv1(name).

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | tag |
|------|---------------|------|------------------------------------|-----|
| IBLSyncPoint | 0x562be6c | 8 | `0x562be6c  mov rax,0x50636E79534C4249` | [I] |
| DebugBlitPhase | 0x5633c82 | 8 | `0x5633c82  mov rax,0x696C426775626544` | [I] |
| RasterizedOpaque | 0x562e978 | 8 | `0x562e978  mov rax,0x85202050E504B99D` | [V] |
| RasterizedAlphaTest | 0x562eb05 | 8 | `0x562eb05  mov rax,0x81C4B2B3F54F21C` | [V] |
| RasterizedTransparent | 0x562ec92 | 8 | `0x562ec92  mov rax,0x22FA40D14C7A4A0A` | [V] |
| ForceForwardPBROpaque | 0x561206f | 8 | `0x561206f  mov rax,0xA26575EA640FF4CA` | [V] |
| FullScreenOverlayTransparent | 0x562f10d, 0x562ef94 | 8 | `0x562f10d  mov rax,0x8F59BC369063980` ; `0x562ef94  mov rax,0x8F59BC369063980` | [V] |
| TransparentDegamma | 0x5610e8f | 8 | `0x5610e8f  mov rax,0xFB7D12FFA8AA3473` | [V] |
| WaterDepthBufferBlit | 0x560b3d0 | 8 | `0x560b3d0  mov rax,0x3B60C925C8628E7A` | [V] |
| SSRColorBufferBlit | 0x562360b | 8 | `0x562360b  mov rax,0x147D0674F0141B93` | [V] |
| BlitUncompressed | 0x560beac | 8 | `0x560beac  mov rax,0xB28166A6DF8D6576` | [V] |
| LuminanceHistogram-exact | - | - | - | [?] |

Pass-name proof notes:
- [V] builder-immediate sites (mov rax, imm64 == fnv1(name), verified verbatim via rdis dis at each RVA; imm cross-checked == fnv1(name)): RasterizedOpaque 0x562e978 imm 0x85202050E504B99D; RasterizedAlphaTest 0x562eb05 imm 0x81C4B2B3F54F21C; RasterizedTransparent 0x562ec92 imm 0x22FA40D14C7A4A0A; ForceForwardPBROpaque 0x561206f imm 0xA26575EA640FF4CA; FullScreenOverlayTransparent 0x562f10d imm 0x8F59BC369063980 and 0x562ef94 imm 0x8F59BC369063980 (two declaration sites, same imm); TransparentDegamma 0x5610e8f imm 0xFB7D12FFA8AA3473; WaterDepthBufferBlit 0x560b3d0 imm 0x3B60C925C8628E7A; SSRColorBufferBlit 0x562360b imm 0x147D0674F0141B93; BlitUncompressed 0x560beac imm 0xB28166A6DF8D6576. Each site sits in builder 0x55f1450..0x563f594 as: lea r9,[string_addr] ; call 0x9D6D0 ; mov rax,0x<imm64>.
- [I] name-only proof (inline string piece built; hash-immediate load site NOT located): IBLSyncPoint 'IBLSyncP' at 0x562be6c (hash 0x463A4116E7586005 absent from .text, immscan 0 hits); DebugBlitPhase 'DebugBli' at 0x5633c82 (hash 0xBB07784B1B637368 absent from .text, immscan 0 hits).
- [?] LuminanceHistogram-exact: hash 0x2A446D92E190D311 absent from .text (immscan 0 hits); no mov reg,imm64 site exists. Only 'LuminanceHistogram CleanUp' (imm 0xEE7C669FCB4BF335) at 0xbc8f694 exists, tagged [I] in oc_U-EF1a.md, not exact-name.

6v implementation-lambda coverage: none of the pending names' hash immediates appear in any implementation-lambda body (lambda region 0xbb30000..0xbcd0000). All imm64 hits for the 8 newly-proven names are in the builder declaration range (0x55f1450..0x563f594), not in any lambda body. IBLSyncPoint, DebugBlitPhase, and LuminanceHistogram-exact have no imm64 site anywhere in .text. Therefore no implementation-lambda hash-use proof line exists for any pending name; lambdas remain uncovered ([I] at best via builder declaration, no [V] lambda-body site).

CLOSES? NO — not every pending part is [V]: IBLSyncPoint and DebugBlitPhase hash immediates are absent from .text (immscan 0 hits each), so they cannot be tagged [V] (only inline string pieces [I]); LuminanceHistogram-exact hash imm 0x2A446D92E190D311 is similarly absent ([?]); and none of the pending names have an implementation-lambda hash-use site in 0xbb30000..0xbcd0000 (lambdas not covered). Blocking fact: hash immediates for IBLSyncPoint/DebugBlitPhase/LuminanceHistogram-exact do not exist in executable code, so [V] proof is impossible by the mov reg,imm64==fnv1(name) pattern.
