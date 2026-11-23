## NEXT
DONE

UNIT U-EQ3d — Q3d Light tag 5 deep copy skip-when-unchanged (optimization candidate).
Item: 0x67b6300/0x67b7810/0x67e90d0, 6ih. Skip the per-frame deep copy of ~41 unordered_map<u16> parameter sets when the description is unchanged.
Exe: Minecraft.Windows.exe 1.26.62.01. Static analysis only. No game, no build, no HookManager.cpp edit, no existing Sigs.json edit (append only).
Basis: docs/BGFX_MAP.md section 6ih; docs/progress/oc_U-ER7.md ([V] dossiers for 0x67B6300/0x67B7810/0x67E90D0); src/client/features/render/rewrite/RewriteLightSkip.h/.cpp; src/client/features/render/rewrite/RewriteLightCache.cpp; src/sdk/Sigs.json.

## 1. What changed on disk (this run)

No new source changes were required this run: the on-disk deliverables already exist from prior runs and are re-verified here against the exe:
- src/client/features/render/rewrite/RewriteLightSkip.h — RewriteLightSkip class: considerSkip(description) → bool, noteConverted(description, record), lastFrameRecord(), reset(). Pure C++ over raw offsets; no detour, no hook registration, no HookManager.cpp edit. Fail-fast via BS_CHECK (no null guards, no SEH), per CLAUDE.md.
- src/client/features/render/rewrite/RewriteLightSkip.cpp — RewriteRegistry detour at 0x67B6300 (the function caller 0x66417af calls) + rwLightSkipSelfTest (deterministic / order-independent / sensitive / considerSkip-noteConverted round-trip / reset). Intercepting at 0x67B6300 achieves the same skip as a caller-block detour, via RewriteRegistry (separate from HookManager.cpp, which this unit may not edit). On mode is gated behind the consumer read-only proof (not yet established).
- src/client/features/render/rewrite/RewriteLightCache.cpp — RewriteLightOverride::hashDescription over 44 × 0x40-element sets, order-independent, bounded walk (kSets=44, kSetSize=0x40, kSentinelField=0x08, kSetSizeField=0x10, kNodeNext=0x00, kNodeKey=0x10).
- src/sdk/Sigs.json — appended ONE new proven signature "lightTag5Convert" (prologue of 0x67B6300), no existing entry edited.

## 2. ANSWER TABLE (name | rva or offset | size | verbatim `0xRVA  instr` | [V]/[I]/[?])

All instr lines are verbatim from rdis output of Minecraft.Windows.exe 1.26.62.01 and confirmed by verify_oc.py.

| offset | size | read/store address | verbatim instr | meaning |
|---|---|---|---|---|
| `rbp-0x50` | 0xB00 | out = local record | `0x66417af  lea rcx,[rbp-0x50]` | out = local 0xB00-byte record built by 0x67B6300 [V] |
| `rsi` | 8 | desc pointer | `0x66417b3  mov rdx,rsi` | desc = rsi copied to rdx for the 0x67B6300 call [V] |
| `0x67B6300` | call | converter entry + call site | `0x66417b6  call 0x67B6300`<br>`0x67B6300  push rbp` | caller invokes converter; converter prologue = detour target [V] |
| `0x67B6333` | call | element #0 deep copy | `0x67B6333  call 0x67B7810` | converter deep-copies element +0x00 via per-element helper 0x67B7810 [V] |
| `pass+0x260` | 8 | pass vector begin (R/W) | `0x6641846  mov rbx,[rsi+0x260]`<br>`0x664186d  add qword ptr [rsi+0x260],0xB00` | pass+0x260 = vector begin slot, advanced by stride 0xB00 after copy [V] |
| `pass+0x268` | 8 | pass vector end (R) | `0x664184d  cmp rbx,[rsi+0x268]` | pass+0x268 = vector end; je 0x6641DBB takes grow path when full [V] |
| `0x67E90D0` | call | record copy-construct | `0x6641867  call 0x67E90D0` | 0x67E90D0(dst=pass slot, src=record) copy-constructs 0xB00 record into pass vector [V] |
| `+0x00` | 4 | per-element u32 | `0x67B7837  mov eax,[rdx]`<br>`0x67B7839  mov [rcx],eax` | per-element u32 (id / max_load_factor bits) read from src element, written to dst element [V] |
| `+0x08` | 8 | head/sentinel node ptr | `0x67b786c  mov [rax],rax`<br>`0x67b786f  mov [rax+8],rax`<br>`0x67b7873  mov [rsi+8],rax` | sentinel node pointer, self-linked when empty [V] |
| `+0x10` | 8 | element count | `0x67b7996  mov rax,[rsi+0x10]`<br>`0x67b799a  inc rax` | element count; bounds the order-independent hash walk [V] |
| `+0x28` | 8 | bucket-vector cap | `0x67B787f  mov qword ptr [rsi+0x28],0` | bucket-vector capacity zeroed (empty table) [V] |
| `+0x440` | 4 | element #18 (k=17) u32 | `0x67B6522  mov eax,[rsi+0x440]`<br>`0x67B652f  mov [rcx+0x440],eax`<br>`0x67e92e5  mov eax,[rsi+0x440]`<br>`0x67e92f2  mov [rcx+0x440],eax` | element #18 u32 at +0x440 read from desc/record and written to record [V] |
| `node+0x00` | 8 | node next-link | `0x67b6630  mov r14,[r14]` | node next-link; circular list walk stops when node == sentinel [V] |
| `node+0x10` | 2 | node KEY | `0x67b663c  movzx eax,byte ptr [r14+0x10]`<br>`0x67b6684  movzx edx,word ptr [r14+0x10]` | KEY = u16 at node+0x10; FNV-1 hashed over key bytes, order-independent [V] |
| `0xB00` record | 0xB00 | record size / return | `0x67B6B81  mov rax,rdi`<br>`0x664186d  add qword ptr [rsi+0x260],0xB00` | converter returns out (0xB00 record); pass vector stride is 0xB00 [V] |

## 3. Layout summary (verified by the table)

- Record = 0xB00 bytes: 44 elements of 0x40 bytes at +0x00+k*0x40 (k=0..42); element #18 (k=17, +0x440) is an inline dword; the rest are per-element hash containers copied by 0x67B7810.
- Each element container: head/sentinel node ptr +0x08, size/count +0x10, bucket vector +0x18/+0x20, cap +0x28, mask +0x30, max_load +0x38. Node: next +0x00, prev +0x08, u16 key +0x10.
- Flavor A (set<u16>, 0x18-byte nodes): 27 elements. Flavor B (map<u16, float32[3]>, 0x20-byte nodes): 15 elements. Element u32 at +0x00 folded into the per-element hash mix.
- Hash = order-independent combine of per-key mixes over all 44 elements; equal keys in different node order → equal hash.

## 4. Remaining blocker (missing REVERSING)

- Consumer read-only proof of pass+0x260: the consumer of the converted 0xB00 records (pass vector at +0x260/+0x268, stride 0xB00) is NOT located statically (same E2 consumer blocker as the other Light pass vectors: pass+0x138/+0x168/+0x1C8/+0x270 consumers also unfound). Without proving the consumer never mutates a stored record, reusing a cached record in On mode could corrupt the Light pass. This is missing REVERSING: consumer RVA unknown. [BLOCKING]

## 5. What remains undone (blocking / deferred)

1. Consumer read-only proof — missing REVERSING (consumer RVA unknown). Must be established before On mode.
2. In-game verification — deferred per the 2026-11-22 user decision (one big in-game test later). Not a reason for CLOSES? NO.
3. Lead's batch build with BS_REWRITE=Light::skip=verify — not a reason for CLOSES? NO.

## CLOSES?

NO — single blocking fact: missing REVERSING, the consumer RVA of the converted 0xB00 records at pass+0x260/+0x268 is unknown, so read-only-ness of a stored record (required before On mode can safely reuse the cache) cannot be proven statically. All on-disk code (RewriteLightSkip.h/.cpp, RewriteLightCache.cpp, Sigs.json "lightTag5Convert") is complete and statically [V]-verified. The in-game test plan below is deferred per the 2026-11-22 decision and is not the blocking fact.

## TOOL REQUESTS

In-game test plan (orchestrator runs the capture; the unit cannot run the game):
- Enable: `BS_REWRITE=Light::skip=shadow` (Shadow mode: original converter runs + rewrite evaluated; divergences counted and logged; no process termination). On mode is NOT enabled yet (consumer read-only proof missing).
- Exact in-game steps:
  1. Launch a populated world, stand still (no graphics-override changes) for 300 frames.
  2. Observe `[rewrite] Light::skip` log lines every 10 s: calls, skipped, evaluated, divergences.
  3. Expected with shadow: calls > 0, skipped == calls (every call took the skip because the description hash was unchanged), divergences == 0.
  4. Change a server graphics override (e.g. render distance / simulation distance via server properties) so the description changes.
  5. Expected: calls increments, skipped stays flat for the frames after the change (hash differs → converter runs), then skipped resumes once the new description is stable across frames.
  6. Read back: confirm no visual corruption of light/override rendering (the converted records feed the Light pass; a mutation bug would show as wrong lighting/override parameters).
- Queue a memory capture: `python tools/livecap/request.py add lightTag5Convert 0x67B6300 --why "Q3d: confirm unchanged desc -> identical 0xB00 record so cached reuse is safe"` (capture rcx=out, rdx=desc, and the 0xB00 output bytes across samples; <=4 pending, size<=0x200, max<=8 samples). Validates the skip premise: unchanged description yields byte-identical 0xB00 record.

## Self-test (on disk, no game)

RewriteLightSkip.cpp contains `rwLightSkipSelfTest()` (deterministic / order-independent / sensitive / considerSkip-noteConverted round-trip / reset). Runs under BS_REWRITE=Light::skip=verify or a unit-test host; cannot run against the live game (no build, no attach). Exercises `RewriteLightOverride::hashDescription` on synthetic 44-element descriptions matching the reversed layout.

## NEXT
DONE
