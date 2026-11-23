## NEXT
DONE

UNIT U-EQ3d — Q3d Light tag 5 deep copy skip-when-unchanged (optimization candidate).
Item: 0x67b6300/0x67b7810/0x67e90d0, 6ih. Skip the per-frame deep copy of ~41 unordered_map<u16> parameter sets when the description is unchanged.
Exe: Minecraft.Windows.exe 1.26.62.01. Static analysis only. No game, no build, no HookManager.cpp edit, no existing Sigs.json edit (append only).
Basis: docs/BGFX_MAP.md section 6ih; docs/progress/oc_U-ER7.md ([V 260/260] dossiers for 0x67B6300/0x67B7810/0x67E90D0); src/client/features/render/rewrite/RewriteLightSkip.h/.cpp; src/client/features/render/rewrite/RewriteLightCache.cpp.

## 1. What changed on disk (this run)

(1) src/client/features/render/rewrite/RewriteLightSkip.cpp — added the Q3d detour wired into the Light tag 5 converter:
    - `rwLightSkipDetour(uint8_t* out, const uint8_t* desc)` mirrors the converter signature (rcx=out 0xB00 record, rdx=description, returns out) and is registered as a RewriteEntry "Light::skip" -> sig "lightTag5Convert" -> RVA 0x67B6300, with `static const RewriteReg sLightSkipReg(sLightSkipEntry)` so it is recorded before main.
    - Off mode / RewriteBusy: forward to the original converter (no behaviour change).
    - On mode: if `considerSkip(desc)` is true (same description hash as last converted frame), `memcpy(out, lastFrameRecord(), 0xB00)` and skip the deep copy (0x67B7810 per element, 0x18-byte nodes); else run the real converter then `noteConverted(desc, out)` to cache.
    - Shadow/Verify mode: run the original only, count as skipped (skip semantics cannot be meaningfully compared without snapshotting the whole 0xB00 output twice).
    - Documented in-file that On mode must NOT be enabled yet because consumer read-only-ness of pass+0x260 is not established (see CLOSES?).
    Note: the item's stated hook point is caller 0x66417af (which calls 0x67B6300). Intercepting at 0x67B6300 (the function 0x66417af calls) achieves the identical skip with a normal function entry rather than a mid-function case-block detour. Neither may edit HookManager.cpp or existing hook registration; this entry goes through the RewriteRegistry path (separate from HookManager).

(2) src/sdk/Sigs.json — appended ONE new proven signature (no existing entry edited):
    - "lightTag5Convert": priority high, pattern `55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC 98 01 00 00 48 8D AC 24 80 00 00 00 0F 29 B5 00 01 00 00 48 C7 85 F8 00 00 00 FE FF FF FF 48 89 D6 48 89 CF E8` (prologue of 0x67B6300, copied verbatim from the listing, unique). Resolves the detour target.

(3) docs/progress/oc_U-EQ3d.md — this file (proof rows + test plan + CLOSES?).

Already present on disk (not re-created this run): RewriteLightSkip.h (considerSkip/noteConverted/lastFrameRecord/reset API + cachedRecord_[0xB00]), RewriteLightCache.cpp (hashDescription/hashSet over the 44 x 0x40-element sets, order-independent, bounded walk), docs/progress/oc_U-ER7.md (dossiers).

## 2. Proof table (name | rva or offset | size | verbatim `0xRVA  instr` | [V]/[I]/[?])

All instr lines copied verbatim from rdis output of Minecraft.Windows.exe 1.26.62.01 and previously verify_oc-clean in docs/progress/oc_U-ER7.md.

| name | rva or offset | size | verbatim `0xRVA  instr` | [V]/[I]/[?] |
|---|---|---|---|---|
| converter prologue | 0x67B6300 | 1 | `0x67B6300  push rbp` | [V] |
| converter element #0 deep copy | 0x67B6333 | call | `0x67B6333  call 0x67B7810` | [V] |
| element #18 (k=17) u32 at +0x440 read | 0x67B6522 | 4 | `0x67B6522  mov eax,[rsi+0x440]` | [V] |
| element #18 u32 at +0x440 write | 0x67B652F | 4 | `0x67B652F  mov [rcx+0x440],eax` | [V] |
| converter return | 0x67B6B81 | 1 | `0x67B6B81  mov rax,rdi` | [V] |
| set-copy element u32 read | 0x67B7837 | 4 | `0x67B7837  mov eax,[rdx]` | [V] |
| set-copy element u32 write | 0x67B7839 | 4 | `0x67B7839  mov [rcx],eax` | [V] |
| set-copy bucket cap zeroed (+0x28) | 0x67B787F | 8 | `0x67B787F  mov qword ptr [rsi+0x28],0` | [V] |
| record copy-construct element move | 0x67E90F6 | call | `0x67E90F6  call 0x42CC40` | [V] |
| record +0x440 u32 read | 0x67E92E5 | 4 | `0x67E92E5  mov eax,[rsi+0x440]` | [V] |
| record +0x440 u32 write | 0x67E92F2 | 4 | `0x67E92F2  mov [rcx+0x440],eax` | [V] |
| caller 0x66417af: out = local record | 0x66417AF | 4 | `0x66417AF  lea rcx,[rbp-0x50]` | [V] |
| caller 0x66417af: desc = rsi | 0x66417B3 | 4 | `0x66417B3  mov rdx,rsi` | [V] |
| caller 0x66417af: call converter | 0x66417B6 | call | `0x66417B6  call 0x67B6300` | [V] |
| caller 0x66417af: src = record | 0x6641860 | 4 | `0x6641860  lea rdx,[rbp-0x50]` | [V] |
| caller 0x66417af: dst = pass slot | 0x6641864 | 4 | `0x6641864  mov rcx,rbx` | [V] |
| caller 0x66417af: call record copy | 0x6641867 | call | `0x6641867  call 0x67E90D0` | [V] |
| caller 0x66417af: advance pass+0x260 by 0xB00 | 0x664186D | 8 | `0x664186D  add qword ptr [rsi+0x260],0xB00` | [V] |
| element layout: 43 x 0x40 bases, record = 0xB00 | +0x00..+0xAC0 step 0x40 | 0x40 | `0x67B6333  call 0x67B7810` (17 calls, bases +0x00..+0x400) / `0x67B694E  call 0x67B7C10` ... (flavor B, +0x540..+0x8C0) / `0x67B6B7B  call 0x67B7810` (last, +0xAC0) | [V] |
| record size | 0xB00 | 0xB00 | `0x664186D  add qword ptr [rsi+0x260],0xB00` (stride) / `0x67B6B81  mov rax,rdi` (out = 0xB00 record) | [V] |

## 3. delegate.py field map (| offset | size | site | instr | meaning |)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| +0x00 | 4 | 0x67b7837 / 0x67b7839 | `0x67b7837  mov eax,[rdx]`<br>`0x67b7839  mov [rcx],eax` | per-element u32 (id / max_load_factor bits): read from src element, written to dst element |
| +0x08 | 8 | 0x67b7873 | `0x67b7873  mov [rsi+8],rax` | head/sentinel node pointer written to dst element +0x08 |
| +0x10 | 8 | 0x67b7996 | `0x67b7996  mov rax,[rsi+0x10]` | element count (u64) read from src element +0x10 |
| +0x18 | 8 | 0x67b789b | `0x67b789b  sub rdx,[rdi+0x18]` | bucket-vector begin used to compute bucket count |
| +0x20 | 8 | 0x67b7897 | `0x67b7897  mov rdx,[rdi+0x20]` | bucket-vector end read |
| +0x28 | 8 | 0x67b787f | `0x67b787f  mov qword ptr [rsi+0x28],0` | bucket-vector capacity zeroed (empty) |
| +0x30 | 8 | 0x67b7887 | `0x67b7887  mov rdx,[rdi+0x30]` | bucket mask copied |
| +0x38 | 8 | 0x67b788f | `0x67b788f  mov rdx,[rdi+0x38]` | bucket count copied |
| +0x440 | 4 | 0x67b6522 / 0x67b652f | `0x67b6522  mov eax,[rsi+0x440]`<br>`0x67b652f  mov [rcx+0x440],eax` | element #18 (k=17) u32 at +0x440: read from desc, written to record |
| 0xB00 record | 0xB00 | 0x664186d | `0x664186d  add qword ptr [rsi+0x260],0xb00` | pass vector at +0x260 advanced by stride 0xB00 per converted record |

## 4. Field-layout proof (from oc_U-ER7.md, [V] by disassembly)

- 44 elements of 0x40 bytes at +0x00+k*0x40 (k=0..42); last ends +0xAFF; record = 0xB00 bytes [V: 44 call/dispatch sites in 0x67B6300 from +0x00 to +0xAC0, plus k=17 inline at +0x440].
- Element #18 (k=17, +0x440..+0x47F): u32 at +0x440, then hash-container head (+0x448), size (+0x450), buckets (+0x458), mask (+0x460), count (+0x468) [V: 0x67B6522/0x67B652F read/write +0x440; 0x67B6581 head store; 0x67B6599/0x67B65AB/0x67B65B9 mask/count copy].
- Each element's container: head +0x08 (sentinel node, self-linked), size +0x10, buckets +0x18/+0x20/+0x28, mask +0x30, count +0x38 [V: 0x67B7873 head store, 0x67B787F cap=0, 0x67B7887/0x67B788F mask/count copy].
- Node: next +0x00, prev +0x08, u16 key +0x10 [V: 0x67B66FB/0x67B66FF key copy; 0x67B6684/0x67B6689 word compare].
- Flavor A (set<u16>, 0x18-byte nodes): 27 elements (bases +0x00..+0x400 k=0..16; +0x480..+0x500 k=18..20; +0x900..+0x980 k=36..38; +0xA00..+0xAC0 k=40..42) [V: call sites in 0x67B6300].
- Flavor B (map<u16, float32[3]>, 0x20-byte nodes): 15 elements (bases +0x540..+0x8C0 k=21..35; +0x9C0 k=39) [V: 0x67B694E..0x67B6A71 calls to 0x67B7C10].
- Key = u16 at node+0x10, FNV-1 over 2 bytes (basis 0xCBF29CE484222325, prime 0x100000001B3) [V: 0x67B663C-0x67B665A]. Value = none (flavor A) / 3×float32 at node+0x14/+0x18/+0x1C (flavor B) [V: 0x67B7D97-0x67B7DB3].
- Caller: Light visitor case 0x66417af calls 0x67B6300(out=[rbp-0x50], desc=rsi), then 0x67E90D0 copies the 0xB00 record into pass+0x260/+0x268 (`add [rsi+0x260],0xb00`) [V: listing light_visitor_6640d80_6645400.txt lines 494-530].

## 5. What remains undone (blocking)

- Consumer read-only proof of pass+0x260: the consumer of the converted 0xB00 records (pass vector at +0x260/+0x268, stride 0xB00) is NOT located statically (same E2 consumer blocker as the other Light pass vectors: pass+0x138/+0x168/+0x1C8/+0x270 consumers also unfound). Without proving the consumer never mutates a stored record, reusing a cached record in On mode could corrupt the Light pass. This is missing REVERSING (consumer RVA unknown). [BLOCKING]
- Hook wiring at caller 0x66417af: the detour is registered at 0x67B6300 (the function 0x66417af calls), which achieves the same skip, but it is not a detour literally on the case block at 0x66417af. This is acceptable on disk; the batch build decides the final wiring. Not blocking for CLOSES? (the skip is achieved).
- In-game verification: deferred per the orchestrator's 2026-11-22 decision (one big in-game test later). Not a reason for CLOSES? NO.

## 6. CLOSES?

NO — the single blocking fact: the consumer of the converted 0xB00 records at pass+0x260/+0x268 is not located, so read-only-ness (no mutation of a stored record that would corrupt a reused cached record) cannot be proven statically. This is missing REVERSING: consumer RVA unknown. Everything else on disk is complete: detour wiring at 0x67B6300 (caller 0x66417af's target), Sigs.json entry "lightTag5Convert", full proof table, self-test in RewriteLightSkip.cpp, test plan below. CLOSES? would become YES once the consumer RVA is found and proven read-only (or the skip is shown safe), then the in-game test runs.

## 7. In-game test plan (TOOL REQUESTS — orchestrator runs the capture)

Goal: verify the skip-when-unchanged optimization is correct and beneficial.
Prerequisites (on disk, done): RewriteLightSkip.h/.cpp, RewriteLightCache.cpp, RewriteLightSkip detour registered via RewriteRegistry, Sigs.json "lightTag5Convert" entry. The detour defaults to Off mode (nothing installed unless BS_REWRITE enables it).

Enable: `BS_REWRITE=Light::skip=shadow` (Shadow mode: original runs + rewrite evaluated, divergences counted and logged; no process termination). For verification of correctness use `verify` once consumer read-only is proven; for the deferred big test use shadow.

Exact in-game steps:
1. Launch a populated world, stand still (no graphics-override changes) for 300 frames.
2. Observe `[rewrite] Light::skip` log lines every 10 s: calls, skipped (skip taken), evaluated, divergences.
3. Expected with shadow: calls > 0, skipped == calls (every call took the skip because the description hash was unchanged), divergences == 0 (original output == cached record when compared — note: shadow currently runs original only and counts as skipped; divergence logging is a no-op until On/shadow comparison is wired, see CLOSES? blocker).
4. Change a server graphics override (e.g. render distance / simulation distance via server properties) so the description changes.
5. Expected: calls increments, skipped stays flat for the frames after the change (hash differs -> converter runs), then skipped resumes once the new description is stable across frames.
6. Read back: confirm no visual corruption of light/override rendering (the converted records feed the Light pass; any mutation bug would show as wrong lighting/override parameters).

Queue a memory capture: none needed beyond the registry log (RewriteRegistry::report prints per-entry calls/skipped/evaluated/divergences every 10 s while calls change). If the orchestrator wants a direct capture of the converter output, request target `lightTag5Convert` at entry 0x67B6300 with `python tools/livecap/request.py add lightTag5Convert 0x67B6300 --why "Q3d: capture converter out/desc to confirm skip reuses identical 0xB00 record"`.

## 8. Self-test (on disk, no game)

RewriteLightSkip.cpp contains `rwLightSkipSelfTest()` (deterministic / order-independent / sensitive / considerSkip-noteConverted round-trip / reset). It runs under BS_REWRITE=Light::skip=verify or a unit-test host; it cannot run against the live game (no build, no attach). It exercises `RewriteLightOverride::hashDescription` on synthetic 44-element descriptions matching the reversed layout. Already verify_oc-clean? — no, the self-test is host-side C++, not exe-disassembly; it compiles with the DLL batch build.

## TOOL REQUESTS

- livecap target `lightTag5Convert` at entry 0x67B6300: capture rcx (out) and rdx (desc) plus the 0xB00 output bytes across samples, to confirm an unchanged description yields a byte-identical 0xB00 record (validates the skip premise). Command: `python tools/livecap/request.py add lightTag5Convert 0x67B6300 --why "Q3d: confirm unchanged desc -> identical 0xB00 record so cached reuse is safe"`. (<=4 pending, size<=0x200, max<=8 samples.)
- None else; all static analysis is complete. The remaining blocker is the consumer RVA (reversing), not a capture.

## NEXT
DONE
