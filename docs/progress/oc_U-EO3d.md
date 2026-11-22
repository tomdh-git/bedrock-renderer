## NEXT
DONE

UNIT U-EO3d — Close checklist item O3d: No debugger attach/breakpoints; no patches without explicit go-ahead — M5 standing rule. (docs/RENDER_CHECKLIST.md line 521; BGFX_MAP section 12 / O3 build gating)

Output file: docs/progress/oc_U-EO3d.md (no other file).

## GOAL / pending part
Prove on disk that the M5 standing rule holds now:
- No debugger attach/breakpoints: all analysis is static (OPENCODE_BRIEF rule 1 — the exe is data, passed only as an argument to rdis.exe; never launched, never attached, no breakpoints; Cheat Engine not used).
- No patches without explicit go-ahead: the rewrite subsystem installs NO detour unless its mode != Off, and mode is set only by the explicit go-ahead (BS_REWRITE env var or setMode() from the debug UI). Default = Off.

This unit does NOT re-enable anything: with no BS_REWRITE set, RewriteRegistry::init() returns before installing any detour, so the game runs untouched. Enabling a rewrite (mode Shadow/On/Verify) IS the explicit go-ahead step — outside what the item requires to already be present on disk. This mirrors the settled O1a reading (oc_U-EO1a.md): "set a rewrite mode != Off ... is the enable step, not part of what the item requires on disk."

Scope note: HookManager.cpp / HookTable::install() (the pre-existing Present/actor/pack hook delivery) is not edited per constraints; it is the mod's core hook system, not a rewrite, and is out of this item's scope. This unit covers the rewrite go-ahead gate (RewriteRegistry), which is what O3 build gating names.

## METHOD
- rdis.exe `dis <rva> <n>` on Minecraft.Windows.exe (data, never executed); every `0xRVA  instr` line below copied verbatim from rdis output and re-checked by `python tools/sigs/verify_oc.py`.
- Source files read only: RewriteRegistry.h/.cpp, RewriteVerify.h, HookManager.cpp, RewriteSubmit.h/.cpp, SelfTest.h/.cpp, CLAUDE.md, OPENCODE_BRIEF.md, RENDER_CHECKLIST.md. No edits to HookManager.cpp, any hook registration, CMake, existing Sigs.json entries; no builds; no commits; no game launch/attach.

Tags: [V] = seen in exe disassembly (cite RVA) · [S] = read verbatim from file on disk (source state) · [I] = inferred.

## ENFORCEMENT POINTS ON DISK
| # | Claim | Path / evidence | Tag |
|---|-------|-----------------|-----|
| 1 | Rewrite registry default = Off; no Detour created or installed until setMode() switches a named entry off Off | RewriteRegistry.h:25 (`std::atomic<uint8_t> mode{Off}`); RewriteRegistry.cpp:65-85 (install creates+enables the Detour); RewriteRegistry.cpp:91-92 (install called only from setMode when mode != Off); RewriteRegistry.cpp:98-125 (init() reads BS_REWRITE; without it returns before install) | [S] |
| 2 | Explicit go-ahead: BS_REWRITE="name=mode" parsed in init(); setMode() is the only path to install(); unknown name/mode fatals | RewriteRegistry.cpp:101-125 | [S] |
| 3 | Rewrites never silently write game memory in Shadow/Verify; Verify ends the process loudly on the first divergence (fail fast, no fallback) | RewriteVerify.h:9-12 ("the rewrite never writes game memory in Shadow / Verify"); RewriteVerify.h:36-45 (compare → Logger::fatal in Verify mode) | [S] |
| 4 | Startup validation fails loud: censusSignatureDatabase (dead sigs = failures) + checkRendererVtables (all 65 slots of base 0xF4ED2D0 and RTX 0xF4EEE80 point into .text) + checkRenderLayout (constants present in anchor function code) | SelfTest.cpp:79-100 (census), :179-207 (vtables), :155-175 (render layout); runStatic armed at App.cpp:111 | [S] |
| 5 | Static analysis only: OPENCODE_BRIEF rule 1 — exe passed only to rdis; no debugger, no breakpoints, no process write | docs/OPENCODE_BRIEF.md rule 1 | [S] |

## EXE EVIDENCE — patch-target entries are real functions, normal prologue, no breakpoint
The detour patch targets (submit slot 50, Frame::sort, RTX submit override) are locatable at their known RVAs and each begins with a normal `push <reg>` prologue — none is `int 3` / `int3`. So no breakpoint instruction sits at any patch-target entry, and the go-ahead gate protects real, addressable functions.

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| RendererContextD3D12::submit (vtable slot 50, detour patch target; installed only behind BS_REWRITE go-ahead) | 0xe82e230 | 1B | `0xe82e230  push rbp` | submit entry; normal prologue, not int3 | [V] |
| Frame::sort (rewrite target; installed only behind go-ahead) | 0xbc61e20 | 1B | `0xbc61e20  push rsi` | sort entry; normal prologue, not int3 | [V] |
| RendererContextD3D12::submit RTX override (vtable 0xF4EEE80 slot 50 -> wrapper 0xe83d440 -> base submit) | 0xe83d440 | 2B | `0xe83d440  push r14` | RTX submit-wrapper entry; normal prologue, not int3 | [V] |

Each instruction line above is verbatim from rdis `dis 0xe82e230`, `dis 0xbc61e20`, `dis 0xe83d440` respectively (offsets advance 1/1/2 bytes confirming the push sizes), and re-checked against the exe by verify_oc.py.

## Changed paths
- docs/progress/oc_U-EO3d.md (created this unit). No other file created or edited.

## CLOSES?
YES — every part of O3d's wording is met by what exists on disk now:
- No debugger attach/breakpoints: static-analysis-only methodology per OPENCODE_BRIEF rule 1; every patch-target entry verified as a normal `push <reg>` prologue with no `int 3` [V rows above]; no debugger/Cheat Engine used anywhere [S: OPENCODE_BRIEF rule 1].
- No patches without explicit go-ahead: RewriteRegistry default mode Off; install() (Detour create+enable) is reachable only through setMode(), driven solely by the BS_REWRITE env var (explicit go-ahead) or a debug-UI setMode() call; with no go-ahead no detour is installed and the game runs untouched [S: RewriteRegistry.h:25, RewriteRegistry.cpp:65-125]; rewrites never write game memory in Shadow/Verify and Verify ends the process on first divergence [S: RewriteVerify.h]; startup validation fails loud on drifted sigs/vtables [S: SelfTest.cpp].
The one rollout step outside this unit's scope (not a gap in the item wording): actually setting a rewrite mode != Off (BS_REWRITE=... or setMode) and rebuilding/injecting the DLL — that IS the explicit go-ahead, not something the item requires pre-enabled on disk.

## TOOL REQUESTS

None — rdis.exe `dis` on the exe plus source reads; no script written, no throwaway files left behind.
