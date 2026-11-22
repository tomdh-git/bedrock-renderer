## NEXT
DONE

# U-EQ1b: Q1b R2 shadow/verify harness — close checklist item

## Goal
Close checklist item Q1b R2: "shadow/verify harness: run original + replacement on copied inputs, compare outputs, abort loudly on first divergence" (docs/RENDER_CHECKLIST.md line 557; BGFX_MAP.md section 12b R2).

## (1) What I changed (paths)
- docs/progress/oc_U-EQ1b.md — this note (created, this unit's only output file per the unit rule)
- No source files were created or edited: the shadow/verify harness and all Q2 detours that use it already exist on disk. This unit verifies the existing work is complete and closes the item.

## (2) Shadow/verify harness on disk (Q1b R2 wording)

The harness lives in `src/client/features/render/rewrite/RewriteVerify.h` and is wired into every Q2 rewrite detour:

| checklist phrase | how it is implemented | where |
|---|---|---|
| run original + replacement on copied inputs | each detour copies its inputs (memcpy into thread-local/stack buffers) before calling the original via the trampoline, then calls the replacement on the copies | RewriteMath.cpp:44-56, RewriteUniform.cpp:51-59, RewriteResourceCache.cpp:132-139, RewriteEncoder.cpp (pure Plan), RewriteFrameSort.cpp:105-121, RewriteDiscard.cpp:55-61 |
| compare outputs | `RewriteVerify::compare(entry, mode, what, original, rewrite, size)` memcmps the two buffers and reports the first differing byte | RewriteVerify.h:36-45 |
| abort loudly on first divergence | in `RewriteMode::Verify`, `RewriteVerify::compare` calls `Logger::fatal` ([[noreturn]]) which ends the process with the entry name, what, byte offset, size, and hex windows of both buffers | RewriteVerify.h:41-42; Log.h:42-44 |
| Shadow vs Verify | Shadow counts and logs divergences (first 16); Verify ends the process on the first one; On runs only the rewrite; Off runs only the original | RewriteRegistry.h:9-12, RewriteVerify.h:36-45 |
| never compares inside a comparison | `RewriteBusy::depth` (thread-local) forces nested calls to run the original | RewriteRegistry.h:87-93, used in every detour |
| skip non-comparable calls | entries count `skipped` and run the original when inputs can't be replayed (e.g. uniform slot out of range, non-null side table) | RewriteUniform.cpp:47-48, RewriteDiscard.cpp:51-52, RewriteEncoder.cpp:289-291 |

Q2 detours wired to the harness:
| detour | function (sig) | RVA | compares | file |
|---|---|---|---|---|
| RewriteMath | Math::mat4Multiply | 0xAA6580 | out[16 floats] | RewriteMath.cpp:58 |
| RewriteUniform | UniformBlock::setVec4Array | 0x5679DB0 | uniform data, slot dirty byte, running hash | RewriteUniform.cpp:67-70 |
| RewriteResourceCache | ResourceCache::get | 0x675E440 | returned holder + control block, entry used byte | RewriteResourceCache.cpp:106-108 |
| RewriteEncoder | Encoder::submit | 0xBC60740 | sort key, sort value, draw header, bind block, encoder after, side table fields | RewriteEncoder.cpp:332-347 |
| RewriteFrameSort | Frame::sort | 0xBC61E20 | sorted keys, sorted item ids, sorted blit keys | RewriteFrameSort.cpp:128-130 |
| RewriteDiscard | Encoder::discard | 0xBC60D10 | encoder[0..0x6B0) | RewriteDiscard.cpp:64 |

Hosted entry (not wired: the existing RenderMark detour calls dispatch): RewriteSubmit.cpp (Encoder::submit at 0xBC60740, hosted).

Not yet wired to a detour: RewriteLightCache.cpp (Q3d, OPEN per docs/progress/rewrite-program.md).

## (3) Proof rows — original function entry points exist at the claimed RVAs (one row per distinct offset; site = the RVA itself)

| offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x5679db0 | 2 | - | `0x5679db0  push r15` | prologue: save callee-saved r15 | [V] |
| 0xaa6580 | 4 | - | `0xaa6580  sub rsp,0xB8` | prologue: allocate 0xB8 stack frame | [V] |
| 0x675e440 | 1 | - | `0x675e440  push rbp` | prologue: save callee-saved rbp | [V] |
| 0xbc60d10 | 2 | - | `0xbc60d10  push r14` | prologue: save callee-saved r14 | [V] |
| 0xbc60740 | 2 | - | `0xbc60740  push r15` | prologue: save callee-saved r15 | [V] |
| 0xbc61e20 | 1 | - | `0xbc61e20  push rsi` | prologue: save callee-saved rsi | [V] |

Each proof line was copied verbatim from `rdis.exe dis 0x<RVA> 8` output against `Minecraft.Windows.exe` (1.26.62.01) and confirmed with `tools/sigs/verify_oc.py`.

## CLOSES?
YES — the item's wording is fully met by what exists on disk now: the shadow/verify harness header (RewriteVerify.h) is complete, Logger::fatal is [[noreturn]] (abort loudly on first divergence), all six Q2 detours copy inputs before calling original+replacement and compare outputs via RewriteVerify::compare, and every proof row above is [V] against the exe. No build, commit, or game launch needed; nothing remains on-disk.
