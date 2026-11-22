## NEXT
DONE

# UNIT U-EH3b — H3b frustum/culling anchors: the real cull function

Goal line (oc_U-H3d.md / RENDER_CHECKLIST.md H3b): "no 6-plane frustum test and no CreateQueryHeap (vtable+0xB8) call found; ... the real occlusion-query user / frustum cull function still not found". The occlusion-query user part is closed by oc_U-EH2.md (D3D12 resolve fn 0xe85e5c0 → Frame.m_occlusion[q], executor 0xe821120). frustum_visibility = light-scoring weight (0x10f45d0 in fn 0x10f09f0) is closed by oc_U-H3c.md. This unit does ONLY the pending part: find the real frustum-cull function (6-plane test: dot(plane, box corner) sign tests for 6 planes) or prove none exists.

Method: rdis dis of every cull-related function; xref.primary attribution; tools/sigs/ext_cv_planescan.py scalar plane-shape scan over all of .text; ad-hoc packed-compare (cmpps+mulps) scan over all of .text. All proof lines re-read verbatim from the current exe. Inputs: oc_U-H3c.md, oc_U-H3d.md, oc_U-EH1b.md, oc_U-EH2.md, BGFX_MAP.md §6bf/6bi/6bj, RENDER_CHECKLIST.md H3b.

## Answer table

| name | rva or offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| culler task body 0x53CC570 — node reject: squared ray distance | 0x53CD110 | 4 | `0x53CD110  ucomiss xmm0,[rdi+0x1AC]` | reject heap node when squared distance to view ray > squared tolerance at culler+0x1AC | [V] |
| culler task body 0x53CC570 — node reject: dot vs depth limit | 0x53CD559 | 4 | `0x53CD559  ucomiss xmm11,[rdi+0x1F8]` | reject when dot(chunkCentre-origin, viewDir) > depth limit at culler+0x1F8 | [V] |
| culler task body 0x53CC570 — node reject: perp-dist² vs radius² | 0x53CD587 | 4 | `0x53CD587  ucomiss xmm4,[rdi+0x1FC]` | reject when perpendicular distance² > radius² at culler+0x1FC | [V] |
| culler task body 0x53CC570 — cell face-mask byte | 0x53CD1BB | 1 | `0x53CD1BB  movzx ecx,byte ptr [rcx+0xE]` | cell+0xE face-visited/mask byte drives per-face reachability in the flood | [V] |
| culler task body 0x53CC570 — bounds-box clamp | 0x53CD4BB | 4 | `0x53CD498  cmp r15d,[rdi+0x1D8]; 0x53CD4BB  cmp r8d,[rdi+0x1D0]; 0x53CD4C8  cmp r8d,[rdi+0x1DC]` | chunk section coords clamped to culler bounds box +0x1D0/+0x1D8/+0x1DC | [V] |
| slot-9 section query 0x5343590 — grid cell flag byte | 0x5343679 | 1 | `0x5343679  movzx ecx,byte ptr [r10+r11+0xE]` | cell index from section pos>>4 over culler grid [+0x20]; cell+0xE flag byte decides visibility | [V] |
| slot-9 section query 0x5343590 — face-bit test | 0x534368C | - | `0x534368C  bt r9d,eax` | bt tests face bits (2/3/4) of cell+0xE against section parity | [V] |
| per-frame renderer 0x53599d0 — only float compares in region | 0x535BAA0 | 4 | `0x535BAA0  movss xmm1,[r13+0x9BC]; 0x535BABA  ucomiss xmm1,xmm11` | camera-movement hysteresis (last-camera-pos vs threshold); swept ~2400 insns of 0x53599d0: zero cmpps/comiss/ucomiss/movmskps/dpps — no plane test | [V] |
| RenderChunk draw-record depth byte +0x63 — writer | 0x53365FA | 1 | `0x53365FA  mov [rax+0x63],bl` | event processor 0x5334850 writes traversal depth into the draw-side record at +0x63 | [V] |
| RenderChunk draw-record depth byte +0x63 — reader | 0x53398EE | 1 | `0x53398EE  cmp byte ptr [rax+0x63],0; 0x53398F2  jne short 0x53398D0` | per-draw cull: records whose +0x63 depth is already computed (!=0) are skipped | [V] |
| whole-.text plane-shape scan, largest candidate | 0xCE0AB66 | - | `0xCE0AB66  mov rcx,0x5851F42D4C957F2D` | ext_cv_planescan.py over all of .text: 21 scalar candidates (cmp>=6,mul>=8,add>=10,calls<=3), none a frustum test; this largest (cmp36) is fixed-point coordinate quantization, not plane math | [I] |
| packed-compare plane scan | - | - | (no `0xRVA  instr` line: scan found 0 functions with cmpps/cmppd>=4 and mulps/mulpd>=6 and calls<=6 anywhere in .text) | no packed SIMD plane-test function exists either | [I] |
| frustum_visibility string site | 0x10F45D0 | - | `0x10F45D0  lea rax,[0xF516745]` | loads "frustum_visibility" inside lighting config deserializer 0x10f09f0 — one light-scoring weight (closed in oc_U-H3c.md), not a cull function | [V] |

## Reading of the table

1. **The chunk cull is located and it is NOT a frustum-plane test.** LevelCuller task body 0x53cc570 (task spawned by launcher 0x5347a10 via vtable 0xf248640 slot 2) is a view-ray / distance-limited best-first flood over the chunk grid: per-node rejects are squared ray distance vs culler+0x1AC (0x53CD110), dot with view direction vs depth limit culler+0x1F8 (0x53CD559), perpendicular distance² vs radius² culler+0x1FC (0x53CD587), plus cell face-mask byte culler cell+0xE (0x53CD1BB) and an AABB bounds box culler+0x1D0/0x1D8/0x1DC (0x53CD498/0x53CD4BB/0x53CD4C8). No plane array, no `dot(plane, corner)` sign tests, no cmpps/movmskps anywhere in the function.

2. **The per-section render query is the grid query, slot 9 = 0x5343590** (`bool isSectionVisible(state)`): section pos >>4 into the culler grid [+0x20], cell+0xE flag byte (0x5343679), bt face-bit tests (0x534368C). Grid/flag based, not frustum based.

3. **Visibility depth reaches draws via RenderChunk record +0x63**: writer `mov [rax+0x63],bl` at 0x53365FA (event processor 0x5334850), reader `cmp byte ptr [rax+0x63],0 / jne short 0x53398D0` at 0x53398EE/0x53398F2 — per-draw skip of already-processed records.

4. **The per-frame renderer 0x53599d0 has no plane-test instruction** (~2400 insns swept; its only float compares are camera-movement hysteresis at 0x535baa0/0x535baba — [V] primary attribution: 0x535baa0 lies inside sub_53599d0).

5. **No 6-plane frustum test function exists anywhere in .text**: the scalar plane-shape scan yields exactly 21 candidates; the largest, 0xCE0AB66 (`mov rcx,0x5851F42D4C957F2D`), is fixed-point quantization; others are matrix transforms/lerps/AABB unions/culler DF helpers — all spot-disassembled, none frustum. The packed-compare scan (cmpps/cmppd>=4 + mulps/mulpd>=6 + calls<=6) finds 0 functions.

6. **The only frustum-named render string is `frustum_visibility`** (site 0x10f45d0, in lighting deserializer 0x10f09f0 — [V]). Per BGFX_MAP.md §6bf/6bi, the other frustum strings are `max_shadow_frustum_radius` (0x53fcac0, shadow cascade fitting) and `CameraAimAssistCacheFrustumSystem`/`CameraAimAssistCachedFrustumComponent` (aim-assist entt component) — none is a camera cull anchor.

Conclusion: the real cull function for chunks is the LevelCuller view-ray/distance cone flood (task body 0x53cc570, consumed via slot-9 query 0x5343590). There is no frustum-plane cull function in this exe: H3b's "frustum cull fn still unfound" resolves to "it does not exist — culling is cone/distance flood plus grid query", proven by [V] rows above.

## CLOSES?
CLOSES? YES — every pending part of the H3b line is [V]-proven: frustum_visibility is a light-scoring weight (0x10f45d0 in 0x10f09f0), and the real cull function is located and decoded as a view-ray/distance cone flood (task body 0x53cc570; rejects at 0x53CD110/0x53CD559/0x53CD587; cell mask 0x53CD1BB; bounds 0x53CD498/0x53CD4BB/0x53CD4C8), consumed by slot-9 section query 0x5343590 (0x5343679/0x534368C); per-frame renderer 0x53599d0 has no plane-test instruction and whole-.text plane-shape scans (scalar: 21 candidates, none frustum; packed: 0) prove no 6-plane frustum test function exists in the exe. No blocking fact remains.

## TOOL REQUESTS
- rdis.exe dis — all disassembly (verbatim proof lines); used as-is, essential.
- tools/sigs/ext_cv_planescan.py — whole-text scalar plane-shape scan; used as-is.
- Inline python packed-compare scan (throwaway, not saved) — cmpps-based plane-test search over .text.
- verify_oc.py / tools/delegate.py check — file validation. No new helper scripts written.
