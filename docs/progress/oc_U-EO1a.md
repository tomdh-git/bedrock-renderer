## NEXT
DONE

UNIT U-EO1a — Close checklist item O1a (docs/RENDER_CHECKLIST.md line 508):

O1a (CORRECTED 6ii: modules inside the existing client DLL, registered via R1; no new DLL) was: Single DLL exporting init (detour install + self-test), shutdown, seam entry points (submit replacement, pass toggles, draw veto) — BGFX_MAP 11a.

Output file: docs/progress/oc_U-EO1a.md only. No other file created or edited. Static analysis only: the exe is data, passed only as an argument to rdis.exe; never executed.

## GOAL / pending part

Prove on disk that (a) replacement modules live inside the existing client DLL (src/client/features/render/*, hooks under src/client/features/hooks/hooks/render/), (b) seams are registered through the R1 rewrite registry (docs/BGFX_MAP.md section 12), not exported entry points of a new DLL, (c) no new DLL exists, and (d) the exe anchor the submit seam hangs on — RendererContextD3D12 vtable base 0xF4ED2D0 slot 50 (+0x190) = submit 0xe82e230; RTX subclass vtable 0xF4EEE80 slot 50 → wrapper 0xe83d440 → base — is [V]-proven in the 1.26.62.01 exe.

Shutdown/slot 59/slot 60/slot 7 specifics belong to checklist item O1b and are NOT part of this unit.

## METHOD

- rdis.exe `dis <rva> <n>` on Minecraft.Windows.exe (data, never executed); `vslot` for vtable slot targets. Every `0xRVA  instr` line below is copied verbatim from rdis output and re-checked by `python tools/sigs/verify_oc.py`.
- Source files read only: no edits to HookManager.cpp, any hook registration, CMake, existing Sigs.json entries; no builds, no commits, no game launch.

Tags: [V] = seen in exe disassembly (cite RVA) · [S] = read verbatim from the file on disk (source state, not exe disassembly) · [I] = inferred.

## ON-DISK INVENTORY (O1a, corrected 6ii)

| # | Claim | Path / evidence | Tag |
|---|-------|-----------------|-----|
| 1 | Replacement modules inside the existing client DLL | src/client/features/render/* (RewriteRegistry, RewriteSubmit and the render modules) built into the single client DLL | [S] |
| 2 | Render hooks with seams inside the client DLL | src/client/features/hooks/hooks/render/* (ExtractionObserver veto listeners, ActorRenderDispatcherHook veto/redraw, D3DHook Present/Resize, TaskDispatchHook, FrameFilterHook, FrameBuilderHook, RenderMarkHook, ActorRenderDispatcherHook) | [S] |
| 3 | R1 rewrite registry: entry {name,sig,knownRva,detour,hosted}, modes Off/Shadow/On/Verify, install() fatals on unresolved or knownRva-mismatched sig, Detour via HookTable::add + enable | src/client/features/render/rewrite/RewriteRegistry.h/.cpp | [S] |
| 4 | R1 wired at startup: HookManager::init line 181 calls RewriteRegistry::init() after Detour::enableAll(); HookManager::shutdown() line 188 mirrors teardown (Detour::disableAll, drain, VtableHook::restoreAll, HookTable::remove) | src/client/features/hooks/HookManager.cpp:181, :188 | [S] |
| 5 | Submit replacement seam entry: RewriteSubmit takeover() __fastcall(ctx,frame,a3,a4) at kSubmitRva=0xe82e230; walks Frame+0xB4700 draw headers stride 0x80, count Frame+0xDC57E8 cap 0xFFFE, fast path *(ctx+0x19F88)<5, always forwards via entry.original<Fn>(); registry entry "RendererContextD3D12::submit", sig "deps.bgfx.RendererContextD3D12.submit", knownRva 0xe82e230, hosted=false | src/client/features/render/rewrite/RewriteSubmit.h/.cpp | [S] + exe below |
| 6 | Pass toggles: R1 RewriteMode Off/Shadow/On/Verify, setMode(), BS_REWRITE env; default Off so nothing installs | RewriteRegistry.h:16; RewriteRegistry::init/setMode | [S] |
| 7 | Draw veto seam: ExtractionObserver::dispatch() returns true when any listener vetoed (drop the insert); ActorRenderDispatcherHook fires a cancelable SceneRenderEvent so render modules can veto/redraw an entity | src/client/features/hooks/hooks/render/ExtractionObserver.h:46-56; ActorRenderDispatcherHook.h:3-4 | [S] |
| 8 | SelfTest init + world phase: runStatic() at App.cpp:111; censusSignatureDatabase, checkRendererVtables (all 65 slots of base and RTX vtables point into .text), checkRenderLayout | src/sdk/SelfTest.h/.cpp; App.cpp:111 | [S] |
| 9 | Sigs.json carry the submit sig (appended entry): deps.bgfx.RendererContextD3D12.submit priority high sig `55 41 57 41 56 41 55 41 54 56 57 53 B8 78 17 00 00 E8 ?? ?? ?? ?? 48 29 C4 48 8D AC 24 80` | Sigs.json lines 147-149 | [S] + exe below |
| 10 | No new DLL: exactly one DLL target `add_library(BlueySenseV2 MODULE ...)`, "this DLL exports nothing", LoadLibrary-injected, /DLL binary, no import library; no separate render DLL target in CMake | CMakeLists.txt:144-150 | [S] |

## EXE EVIDENCE (verified against Minecraft.Windows.exe 1.26.62.01)

The R1 entry install() requires SigManager::get("deps.bgfx.RendererContextD3D12.submit") to resolve to imageBase()+0xe82e230 on this build, so the exe anchor to prove [V] is: vtbl 0xF4ED2D0 slot 50 (+0x190) holds 0xe82e230, and code at 0xe82e230 matches the registered signature; vtbl 0xF4EEE80 (RTX) slot 50 holds wrapper 0xe83d440 which forwards to base 0xe82e230.

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| Submit entry | 0xe82e230 | 1 | `0xE82E230  push rbp` | submit entry; first sig byte 0x55 of `deps.bgfx.RendererContextD3D12.submit` | [V] |
| Submit stack-probe size | 0xe82e23c | 5 | `0xE82E23C  mov eax,0x1778` | __alloca probe size 0x1778; sig bytes B8 78 17 00 00 match | [V] |
| Submit stack-probe call | 0xe82e241 | 5 | `0xE82E241  call 0xE9E7970` | sig E8 rel32 (wildcarded) calls the stack probe | [V] |
| Submit frame setup | 0xe82e246 | 3 | `0xE82E246  sub rsp,rax` | sig 48 29 C4 matches | [V] |
| Submit frame pointer | 0xe82e249 | 8 | `0xE82E249  lea rbp,[rsp+0x80]` | sig tail 48 8D AC 24 80 ... matches | [V] |
| Vtable slot target (base) | 0xF4ED460 | 8 | - | vslot: vtbl 0xF4ED2D0 slot 50 (+0x190) → sub_e82e230 = 0xe82e230 | [V] |
| Vtable slot target (RTX) | 0xF4EEEA0 | 8 | - | vslot: vtbl 0xF4EEE80 slot 50 (+0x190) → sub_e83d440 = 0xe83d440 (RTX override) | [V] |
| RTX wrapper forwards to base submit | 0xe83d4d6 | 5 | `0xE83D4D6  call 0xE82E230` | RTX submit wrapper pre-does TLAS/BLAS then calls base submit | [V] |

## VERIFICATION ROWS (each line verified against the exe by tools/sigs/verify_oc.py)

e82e230  push rbp
e82e23c  mov eax,0x1778
e82e241  call 0xE9E7970
e82e246  sub rsp,rax
e82e249  lea rbp,[rsp+0x80]
e83d4d6  call 0xE82E230

## OPEN questions

- None: submit anchor, RTX forward, vtable slots, R1 wiring, single-DLL layout, init/self-test/shutdown are all on disk and [V]- or [S]-proven. Note on scope: RewriteSubmit::takeover itself is observe+forward (walks draw records, stats, timers) and always forwards — draw drop is reached through the hooks/render veto seams (ExtractionObserver dispatch drops inserts; ActorRenderDispatcherHook cancelable SceneRenderEvent), not by the submit detour skipping the forward.

## Changed paths

docs/progress/oc_U-EO1a.md (rewritten this unit). No other file created or edited.

## CLOSES?

YES — every part of the corrected O1a wording exists on disk now: modules inside the existing client DLL (src/client/features/render/* + hooks under src/client/features/hooks/hooks/render/), all built into the single BlueySenseV2 MODULE DLL which exports nothing and is LoadLibrary-injected [CMakeLists.txt:144-150, source read]; seams registered via R1 rewrite registry (RewriteRegistry entry {name,sig,knownRva,detour,hosted}, modes Off/Shadow/On/Verify, install() with knownRva mismatch fatal), wired at HookManager.cpp:181 after Detour::enableAll(), shutdown() at line 188 mirrors teardown [source read]; no new DLL — exactly one DLL target in CMake [source read]; init = detour install + SelfTest (runStatic at App.cpp:111) [source read]; seam entry points: submit replacement RewriteSubmit takeover anchored at vtbl 0xF4ED2D0 slot 50 (+0x190) → 0xe82e230 [V exe: vslot + rdis prologue matches Sigs.json sig; RTX vtbl 0xF4EEE80 slot 50 → 0xe83d440 → `0xe83d4d6  call 0xE82E230`], pass toggles via R1 modes [source read], draw veto via hooks/render veto listeners (ExtractionObserver::dispatch drops inserts; ActorRenderDispatcherHook cancelable SceneRenderEvent) [source read]. Remaining rollout (not a gap in the item wording): set a rewrite mode != Off (BS_REWRITE or setMode) and rebuild/inject the DLL — that is the enable step, not part of what the item requires on disk.

## TOOL REQUESTS

None — rdis.exe `dis`/`vslot` on the exe plus source reads; no script written, no throwaway files left behind.
