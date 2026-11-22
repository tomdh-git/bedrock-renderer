## NEXT
DONE

# Unit U-EN4b — N4b Startup validation: slots point into .text, sigs found, content checks (mask immediates, offset refs); fail loudly

Item line (checklist N4b, docs/RENDER_CHECKLIST.md line 500):
"Startup validation: slots point into .text, sigs found, content checks (mask immediates, offset refs); fail loudly — BGFX_MAP 9b; K-P9; L18b"

Cross-refs: docs/BGFX_MAP.md section 9b (startup validation, fail loudly); K-P9 (DONE 2026-11-21); L18b (DONE 2026-11-16 mirror of J2).

Scope of this unit: verify the statically checkable parts of N4b on the 1.26.62.01 exe and report them as [V] rows:
(1) hooked RendererContextD3D12 vtable slots point into .text,
(2) every renderer signature in Sigs.json is found exactly once in .text,
(3) content checks (mask immediates + offset refs) pass against the anchor function bodies,
(4) failures are reported loudly at startup (SelfTest static phase + world phase).
No build and no game run are needed for the on-disk part; the exact remaining in-game/build step is listed at the end.

EXE: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). .text range [0x1000, 0xeec75d6).

Data sources read fully: docs/OPENCODE_BRIEF.md; docs/BGFX_MAP.md sections 1, 6f, 6aj, 6t, 9b; docs/RENDER_CHECKLIST.md lines 428/500; docs/progress/oc_U-EK-P9.md; docs/progress/platform-versioning-live.md; src/sdk/SelfTest.cpp; src/sdk/SelfTest.h; src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h; src/sdk/mc/deps/bgfx/RendererContext.h; docs/data/layout_asserts.json; src/sdk/Sigs.json; tools/sigs/slotcheck.py; tools/sigs/audit.py; tools/sigs/layoutcheck.py.

## Answer table

Columns: name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | tag ([V] = seen in disassembly/tool output, [I] = inferred, [?] = unknown).

Group A — slots point into .text (slotcheck.py run on the exe; vtable 0xf4ed2d0, 65/65 slots in .text, 0 failures, exit 0). Each slot's value is a function entry in .text, proven by the first instruction at that address.

| vtable slot 50 (submit) | vtable 0xf4ed2d0 +0x190 = 0xf4ed460, holds 0xe82e230 | 8 (qword slot) | `0xe82e230  push rbp` | slotcheck: index 50 holds anchor-resolved 0xe82e230; value ∈ .text [0x1000, 0xeec75d6); RendererContextD3D12::submit per BGFX_MAP 6k/6aj [V] | [V] |
| vtable slot 58 (init) | vtable 0xf4ed2d0 +0x1d0 = 0xf4ed4a0, holds 0xe807ff0 | 8 (qword slot) | `0xe807ff0  push rbp` | slotcheck: index 58 holds 0xe807ff0; value ∈ .text; init per BGFX_MAP 6aj [V] | [V] |
| vtable slot 22 (createShader) | vtable 0xf4ed2d0 +0xb0 = 0xf4ed380, holds 0xe8137b0 | 8 (qword slot) | `0xe8137b0  push r15` | slotcheck: index 22 holds 0xe8137b0; value ∈ .text; createShader per BGFX_MAP 6k/6aj [I role, V address] | [V] |
| vtable slot 26 (createTexture) | vtable 0xf4ed2d0 +0xd0 = 0xf4ed3a0, holds 0xe8143c0 | 8 (qword slot) | `0xe8143c0  push rbp` | slotcheck: index 26 holds 0xe8143c0; value ∈ .text; createTexture per BGFX_MAP 6aj table-evidence [V] | [V] |
| vtable slot 0 (dtor) | vtable 0xf4ed2d0 +0x00 = 0xf4ed2d0, holds 0xe83c630 | 8 (qword slot) | `0xe83c630  push rsi` | slotcheck: index 0 holds 0xe83c630; value ∈ .text; destructor per BGFX_MAP 6k [I role, V address] | [V] |
| vtable slot 60 | vtable 0xf4ed2d0 +0x1e0 = 0xf4ed4b0, holds 0xe81a610 | 8 (qword slot) | `0xe81a610  push r14` | slotcheck: index 60 holds 0xe81a610; value ∈ .text; swapchain/resize/present helper per BGFX_MAP 6k/6aj [I role, V address] | [V] |
| vtable all-slot range check | 0xf4ed2d0..0xf4ed4e8, 65 slots | - | - | slotcheck: unique table holding all 14 anchored slots at their indices is 0xf4ed2d0; "65/65 slots in .text"; 0 failures; exit 0 | [V] |

Group B — hook signatures found exactly once in .text (audit.py run on the exe; all renderer symbols LIVE, matches=1). First instruction at each signature RVA proves the symbol resolves to code.

| Sigs.json Encoder::submit | 0xbc60740 | 26-byte sig pattern | `0xbc60740  push r15` | audit LIVE matches=1; Sigs.json comment documents 0xBC60740 (BGFX_MAP 6cq) [V] | [V] |
| Sigs.json Encoder::reset | 0xbc60d10 | 20-byte sig pattern | `0xbc60d10  push r14` | audit LIVE matches=1 [V] | [V] |
| Sigs.json Encoder::frameSort | 0xbc61e20 | 20-byte sig pattern | `0xbc61e20  push rsi` | audit LIVE matches=1 [V] | [V] |
| Sigs.json FrameGraph::endFrame | 0xc270460 | 30-byte sig pattern | `0xc270460  push rbp` | audit LIVE matches=1; BGFX_MAP section 4 [V] | [V] |
| Sigs.json FrameGraph::taskDispatch | 0xe9002e0 | 56-byte sig pattern | `0xe9002e0  push rbp` | audit LIVE matches=1 (priority high) [V] | [V] |
| Sigs.json D3D12Context::drawExecutor | 0xe821120 | 19-byte sig pattern | `0xe821120  push rbp` | audit LIVE matches=1; BGFX_MAP 6cs [V] | [V] |
| Sigs.json D3D12Context::psoBuilder | 0xe81e860 | 20-byte sig pattern | `0xe81e860  push r15` | audit LIVE matches=1; BGFX_MAP 6ct [V] | [V] |
| Sigs.json D3D12Context::drawFlush | 0xe81b720 | 25-byte sig pattern | `0xe81b720  push r15` | audit LIVE matches=1; BGFX_MAP 6ej [V] | [V] |
| Sigs.json RendererContextD3D12::submit | 0xe82e230 | slot-50 target | `0xe82e230  push rbp` | audit LIVE matches=1; submit per BGFX_MAP 6k [V] | [V] |
| audit summary | 81 symbols | - | - | audit.py: "81 symbols, 0 with no live pattern", exit 0; every renderer hook signature matches exactly once in .text [V] | [V] |

Group C — content checks (mask immediates + offset refs) present in anchor function bodies (layoutcheck.py run on the exe over docs/data/layout_asserts.json).

| psoBuilder PSO key mask | 0xe81e860 | 8-byte imm64 | `0xe81e8ec  mov rsi,0x707007FFFFFF0FF` | layoutcheck: 0x0707007FFFFFF0FF present ("PSO key mask of the state word", RenderLayoutAsserts.h kPsoBuilder) [V] | [V] |
| submit Frame item count | 0xe82e230 | 4-byte disp | - | layoutcheck: 0xDC57E8 present in Encoder::submit body ("Frame item count (draw slot counter)") [V] | [V] |
| frameSort sort-key view mask | 0xbc61e20 | 8-byte imm64 | - | layoutcheck: 0x3FC0000000000000 present in Encoder::frameSort body ("SortKey::kViewMask") [V] | [V] |
| layoutcheck summary | docs/data/layout_asserts.json | 199 assertions | - | layoutcheck.py: "199 assertions, 0 failed", exit 0; every mask-immediate and offset-reference assertion backed by an immediate/displacement in its anchor function's body [V] | [V] |

Group D — fail loudly at startup (SelfTest wiring, read from source).

| checkRendererVtables | src/sdk/SelfTest.cpp:179-207 | - | - | reads both renderer vtables (base 0xF4ED2D0, RTX 0xF4EEE80, 65 slots) via renderlayout::firstSlotOutsideText vs module .text; records a loud failure for any slot outside it; called from runWorldChecks line 212 [V source read] | [V] |
| checkRenderLayout | src/sdk/SelfTest.cpp:155-175 | - | - | for each renderlayout::kFunctions anchor, reads resolved function code and records a loud failure when a constant (mask immediate / offset ref) is absent; called from runWorldChecks line 213 [V source read] | [V] |
| censusSignatureDatabase | src/sdk/SelfTest.cpp:79-94 | - | - | static phase: every dead Sigs.json symbol recorded as a loud failure ([selftest] sig dead: <name>); called from runStatic line 369 [V source read] | [V] |
| runStatic wiring | src/client/app/App.cpp:111 | - | - | `SelfTest::runStatic()` called at app startup, main thread, after hooks enabled; arms runWorld() [V source read] | [V] |
| recordFailure | src/sdk/SelfTest.cpp:46-51 | - | - | Logger::warn + gFailures push; "Never throws, never fatals: a broken promise is one log line" (SelfTest.h) [V source read] | [V] |
| firstSlotOutsideText | src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h:255-260 | - | - | returns index of first vtable slot outside [textBegin, textEnd), or slot count when all inside; client twin of slotcheck.py [V source read] | [V] |
| RendererContextSlots | src/sdk/mc/deps/bgfx/RendererContext.h:6-17 | - | - | kBaseD3D12Vtable = 0xF4ED2D0, kRtxVtable = 0xF4EEE80, kSlotCount = 65 [V source read] | [V] |

## What changed (paths)

- docs/progress/oc_U-EN4b.md — this note (required output; created now).

No source/header/tool change was needed for N4b: every mechanism is already on disk, delivered by the K-P9 unit (2026-11-21) and present on the current checkout:
- src/sdk/SelfTest.cpp — checkRendererVtables, checkRenderLayout, censusSignatureDatabase, recordFailure, runStatic/runWorldChecks (dated 2026-11-21 14:37).
- src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h — renderlayout::firstSlotOutsideText + kFunctions content-check tables (dated 2026-11-21 16:51).
- src/sdk/mc/deps/bgfx/RendererContext.h — RendererContextSlots (kBaseD3D12Vtable/kRtxVtable/kSlotCount).
- docs/data/layout_asserts.json — 199 structure assertions (mask immediates + offset refs).
- src/sdk/Sigs.json — all renderer hook signatures.
- tools/sigs/slotcheck.py, tools/sigs/audit.py, tools/sigs/layoutcheck.py — offline verifiers.

## Remaining step (not done by this unit; game closed, no build allowed)

Build the Release client and run the game once. The world-phase SelfTest (armed by App.cpp:111 via runStatic→runWorld) fires on the first GameUpdateEvent with a local player and writes %APPDATA%\BlueySenseV2\diagnostics\selftest.txt. Confirm the report shows checkRendererVtables + checkRenderLayout + censusSignatureDatabase all green ("world: N passed, 0 failed"). This is runtime validation of code that already exists on disk; it is not part of N4b's on-disk wording.

## CLOSES?

YES — every part of N4b's item wording is met by what exists on disk now and proven by [V] rows:
1. slots point into .text — checkRendererVtables + renderlayout::firstSlotOutsideText implemented; slotcheck: 65/65 slots of vtable 0xf4ed2d0 in .text [0x1000, 0xeec75d6), 0 failures, exit 0 [Group A, V].
2. sigs found — SigManager dead-symbol census in runStatic; audit.py: 81 symbols, 0 with no live pattern; every renderer hook signature matches exactly once in .text [Group B, V].
3. content checks (mask immediates, offset refs) — checkRenderLayout + renderlayout::kFunctions; layoutcheck.py: 199 assertions, 0 failed, exit 0 [Group C, V].
4. fail loudly — recordFailure (warn + gFailures) invoked from checkRendererVtables, checkRenderLayout and censusSignatureDatabase; runStatic called from App.cpp:111 at startup; runWorldChecks runs checkRendererVtables + checkRenderLayout on the first world tick [Group D, V].

Single remaining fact (runtime validation only, not part of the item wording): the world-phase selftest has not been observed in a running game (Release build + in-game run pending, listed above). That does not change CLOSES? because N4b's wording concerns the on-disk validation mechanism, which is complete.

## TOOL REQUESTS

None (existing tools only: slotcheck.py, audit.py, layoutcheck.py, verify_oc.py, rdis.exe; no helper script written).
