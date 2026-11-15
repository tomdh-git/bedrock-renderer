# Progress: platform-versioning-live

## NEXT
Static queue (coordinator 2026-11-14): done L17b, wiring text. Next: L17h (graphics options writers), L10c (65% size code), M1b classification, M1c dossiers, M4d dossier re-run. Game is closed.
Then: K-P7/K-P9/L18b (SelfTest review), M4a-d, live polls L10/L17 (obj=[base+0x12BB4910], ctx=[base+0x12AE1748]).

## Entries (newest last)

### R12 - DONE
- tools/sigs/descscan.py edited: `--stop-at-write` ends the read scan at the first overwrite of the description register (or any call when that register is volatile); per-visitor register map `VISITOR_REG` (Effect 0x666aca0 r15, Sky 0x66560f0 rdi, UI 0x6664a00 r9, Light 0x6640d80 rsi, Item 0x6646980 rdi) used when --reg/--start are absent: the scan then starts after the visitor's own `mov reg,[r8]/[rdx]` load. [V] ran on all five visitors (e.g. Sky: reads +0x00..+0x128 until rdi is reloaded at 0x6656f30).
- Limit [I]: inside one visitor the same register holds different descriptions per case, so offsets of a whole-visitor run mix cases; use --start/--end per case (group_visitors.md) for per-description reads.

### R13 - OPEN (Editor visitor 0x66742f0 has an anchor but no constants: Editor tags 0-7 payloads are untyped, R11)
- Sigs.json: appended deps.bgfx.FrameBuilder.{visitEditor,visitEffect,visitUI,visitSky,visitItem,visitLight} (prologue sigs from mksig, unique in 62.01 [V]; they include the frame-size dword so a stack-size change breaks them: then re-find via the zone strings "FrameBuilder - Insert <group>" -> wrapper -> single non-profiler callee). Wrapper-route sigs are NOT unique (the six wrappers are one template; only Sky is), documented.
- New tool tools/sigs/wrappersig.py (wrapper -> '@N' call-target signature; works for Sky only). Also found: capstone reports disp_size 2 for rip-relative operands behind a 66 prefix, so tools/sigs/mksig.py leaves 2 disp bytes unwildcarded there (not fixed in mksig, not mine; wrappersig fixed).
- layout_asserts.json + RenderLayoutAsserts.h (kVisitSky/Light/Item/Effect/UI + kFunctions): Sky 0x548,0x138,0x128,0x11C,0x10C; Light 0x800,0x648,0x4A0,0x1D0,0x84; Item 0x140,0xC8,0xE8,0xC0; Effect 0xF8,0xA0,0xB0; UI 0x90. `python tools/sigs/layoutcheck.py` -> 186 assertions, 0 failed.
- Caveat [I]: a constant is "present in the visitor body" (raw immediate/displacement), not proof of which case uses it; backs text states the meaning.

### M4d / M4a / K-P7 (tooling part) - OPEN (see the one blocking fact per item)
- New tool tools/sigs/anchors.py: `build` writes docs/data/function_anchors.tsv (233 functions of functions.tsv: unique prefix sig for 217, unique interior window for 216, strings, Sigs.json symbol); `refind` (BS_EXE=any exe) resolves them and prints the rva delta. [V] self-check on 62.01: 217 found, all delta 0. 60.05: 217 found (165 at -0xC00, others at region deltas -0x370/-0x7c0/-0x1d0/+0x140/-0x10), 16 dead. 51.01 and 50.04: only 112 found, 115 dead (layer split on 51.01: L1 13/20, L2 22/34, L3 12/25, L4 28/62, L5 28/51, L6 10/30): the 51->60 patch rewrote most of the render code.
- Reports: docs/data/port_check_functions_{60.05,51.01,50.04}.tsv. Layout-constant port check: docs/data/port_check_layout_asserts.tsv (186 assertions: 62.01 and 60.05 all pass; 51.01/50.04 Encoder::submit 5/20, frameSort 2/9, submitFrameParams 2/5: Frame offsets moved, e.g. 0xdc57e8 -> 0xdd17e8 (+0xC000), 0x8b4700 -> 0x8c0700, bgfx ctx 0x1eaac60 -> 0x1ec2c60 on 51.01).
- 16 functions have no anchor (all D0/D1/D2 thin or template twins): 0x675e440, 0x567c8b0, 0x6765020, 0x67b7810, 0xbc37320, 0xbc37ca0, 0xbc2d550, 0xbc2dd20, 0xbc2eb50, 0xbc0f130, 0xbc0ac20 and the five insert wrappers 0x6674050/0x666aa00/0x6664760/0x66466e0/0x6640ae0 (wrapper template is identical across groups: only the string address differs).
- M4a stays OPEN: the 16 above need a string/caller-route anchor; M4d stays OPEN: the dossier tool itself (per-function field offsets) was not re-run on older exes, only the locate step + layout constants.

### L10d - DONE (live, read-only polls on 62.01, game backgrounded at the time)
- Per-view record V = ctx+0x1EAB090 + id*0x140; projection at V+0x50 (column-major 4x4), view at V+0x10 (identity for every view: camera-relative rendering).
- Main scene views 1..13: proj [0.7586 0 0 0 | 0 1.28 0 0 | 0 0 -1 -1 | 0 0 -0.025 0]; vertical fov = 2*atan(1/m11) = **76.0 deg** (CONTRADICTS 6dd "76.9": its own arithmetic gives 76.0), aspect m11/m00 = 1.6872 = 1920/1137, infinite far (m22=-1), near = -m32/2 = 0.0125 [V formula, I interpretation]. View 14: fov 70 (hand/FOV-effect view [I]). View 15/49-class: fov ~-179.6 (m22 -0.001: orthographic-like/utility [?]). Views 19-25: 1248x739, fov 75, m22 -1.001, m32 -0.1001 => finite far: near 0.05, far 100 (GL-style depth).
- World->screen recipe [V math]: clip = P * V * (M*p) with V identity; ndc = clip.xyz/clip.w (w = -z_view); px = (ndc.x*0.5+0.5)*rectW, py = (0.5-ndc.y*0.5)*rectH (y flip [I], not checked on screen).

### L10c - OPEN (the function that turns the upscaling percentage into the render size is not located)
- Live [V]: backbuffer 1920x1137 (Frame+0xDC5808 = 0x780, +0xDC580C = 0x471 as u32 pair, NOT u16 as 6dn/6aw wrote; reset flags Frame+0xDC5810 = 0x400080 = obj+0x19F80). 50 views are active, 206 unused (1x1, mode 0). Full res 1920x1137: views 0-14 and 15,49 class; **1248x739 = exactly 65% (0.65*1920, 0.65*1137) on views 19-25 and 44-45**; downsample chain 624x369, 312x184, 156x92, 78x46, 39x23, 19x11 (views 27-42, bloom/luminance mips [I]); 1024x1024 view 16 (shadow/cubemap [I]); 1x1 views 17-43 (histogram/exposure [I]).
- Static: the consumers are TAAU body 0xbc8cfd0 (uniforms RenderResolution/DisplayResolution/ResolutionRatiosAndFPEpsilon), FSR1 0xbcb7590/0xbcb7e70, DLSS slot 64; option strings options.upscalingPercentage (ref 0x20ff240 region). Blocking fact: the writer of the 0.65 factor (ClientInstance option -> VV frame-graph builder 0x5255450 view sizes) is not traced.

### L17a - OPEN (hooked-part list and resize path not closed live)
- Live [V]: obj+0x2D8 swapchain, vtable in dxgi.dll (vtbl[8]=Present = dxgi+0x1b8c0 inside dxgi.dll 0x7ff9a4b60000+0xf6000); device obj+0x400 vtable inside D3D12Core.dll; obj+0x2F8 window count = 1; obj+0x19F88 = 5 (init-complete level), 0x19F90/94 = 1920/1137, 0x19F98 = 0x1C (DXGI_FORMAT_R8G8B8A8_UNORM), 0x19FA0 = 1, 0x19FAC = 3, 0x19FBC = 0x42 (NOT a buffer count: 6aw [I] wrong or at least unproven), 0x19FD8 = 1, 0x19FDC = 0.
- CONTRADICTS 6aw: obj+0xC9C6C0 = 17040 = 240*71, +0xC9C6C4 u16 = 240, +0xC9C6C6 u16 = 71: that is a TILE grid of the backbuffer (1920/8 x floor(1137/16)), not width/height in pixels.
- Remaining: swapchain buffer count/format (needs the DXGI_SWAP_CHAIN_DESC passed at 0xe9241b0) and a resize observation (needs the user to resize the window; not done).

### L17f - OPEN (one fact)
- Live [V]: reset flags 0x400080: bit 0x80 (VSYNC) set; Present(SyncInterval = vsync bit, Flags = 4 tearing when vsync off) per 6ay. Counter F+0xE746D8 advanced 18 times in 2.0 s (~9 fps, median gap 109 ms): the game window was not foreground (foreground pid differed), so pacing at foreground is unmeasured. Blocking fact: a poll while the game is focused.

### LIVE STATUS (2026-11-14, later): the game process went away (CE: ctx/obj reads 0, enum_modules fails). All remaining live polls are blocked until the game is relaunched. Live facts gathered before it closed are in the entries above (L10c/L10d/L17a/L17f). Caps live re-check (K-P4) not done.

### K-P7 - DONE
- RVA/slot database per version: Sigs.json (+6 visitor sigs), docs/data/function_anchors.tsv (233 functions, 62.01 reference), per-version re-find reports docs/data/port_check_functions_{60.05,51.01,50.04}.tsv, docs/data/port_check_layout_asserts.tsv (4 versions), docs/data/port_check_render_sigs.tsv (existing). Renderer vtable per version found by tools/sigs/slotcheck.py: 62.01 vtable rva 0xf4ed2d0, 60.05 0xf4ec2b0 (base tables; the 62.01 RTX table 0xF4EEE80 per 6al). OffsetProvider.h needed no append (no new game offset constant was derived).

### K-P9 - OPEN (one fact: not wired into SelfTest, which is not mine)
- Offline validation done and passing: tools/sigs/slotcheck.py finds the renderer vtable from 14 anchored structural slots (7,10,12,14,22,24,26,39,40,41,46,50,58,60) with no rva, checks each holds the function its anchor resolves to and that all 65 slots point into .text: 62.01 and 60.05 pass (0 failures); 51.01 correctly FAILs (anchors dead: slots 7,10,12,58 unresolvable). Sig-missing fail-loud exists already (SelfTest "sig dead", static phase) and the layout phase reports drift.
- Client helper added (append-only) renderlayout::firstSlotOutsideText(vtable, slots, textBegin, textEnd) in RenderLayoutAsserts.h. Needed from the lead: call it in SelfTest world phase on [renderer]'s vtable (65 slots) and recordFailure when result < 65.

### J2 / L18b - OPEN (one fact: never built/run in game)
- 15 unique sigs for renderer functions now in Sigs.json (9 from 6dj + 6 visitors) and 19 anchored functions / 186 content assertions (immediates/displacements) in layout_asserts.json + RenderLayoutAsserts.h, run by SelfTest::checkRenderLayout in the world phase; offline layoutcheck passes on 62.01 and 60.05. Open: the Release build with these headers and an in-game run of the world phase.

### K-P6 - DONE
- [V] 0xe82e230 (D3D12 submit, slot 50): prologue stores rdx at [rbp+0x16a8], tests [rcx+0x19f88] >= 5 and [rcx+0x2d8] (swapchain), then `add rdx,0xdc5808` and calls virtual +0x1e0 (slot 60) with rdx = &Frame.backbuffer block (Frame+0xDC5808), r9 kept in rsi: so rcx = renderer context, rdx = Frame* (the Frame+0xDC5808 arithmetic proves the type), r9 = 4th arg preserved.
- [V] 0x66232b0 (BgfxFrameBuilder::endFrame, vtable slot 18): rcx saved at [rbp+0x19d0], rdx at [rbp+0x1998], `mov rax,[rcx+0x28]` = the BgfxContext handed on. It reaches 0xc270460 through the frame lambda 0x67c9c20 (zone "Frame renderer - Frame", [lambda+0x20]->...).
- [V] 0xc270460 (BgfxContext::endFrame): rcx = the BgfxContext object (byte [rcx+0x35] early-out, [rcx+0x38..0x50] copied into the frame-graph params, [rcx+0x20] and [rcx+0x18] passed to 0xe9002e0), rdx/r8/r9 = DragonFrameResources&, Declarator&, vector<HashedString>&& per the BGFX_MAP 192 signature; calls generate 0xc273420 then dispatch 0xe9002e0.
- CORRECTION to the K-P6 text: "endFrame takes BgfxFrameBuilder in rcx" is true of 0x66232b0 only; 0xc270460 takes the BgfxContext (= [builder+0x28]).

### K-P4 - DONE
- Frame (stride 0xE749C0, counters, backbuffer dwords), draw header (+0x38 uniformEnd, +0x40 start index, +0x44 num indices, +0x4C num vertices decided by 6fj readers, shape live-checked in 6ij/6il), RenderItem (0x540 record array), View (stride 0x140: rect i16 x4 at +0, view +0x10, proj +0x50, mode byte +0x122 - re-confirmed live today for all 256 slots: 50 active, mode 1; rest 1x1 mode 0), Caps (globals typed in Caps.h from a live read; not re-polled today because the game had closed).

### M4b - OPEN (one fact: per-pass VV lambda behaviours and a few task bodies are not dossiered, so no note can be written)
- docs/BEHAVIOR_NOTES.md: added sections "FrameBuilder inserts, visitors, extractors" and "Pass declaration and execution" (wrappers, visitors, thin/fat clones, extractors, shared helpers, VV group builders, submitPass), RVA-free with re-find hints; the "not covered" list is narrowed to: per-pass in/out of the VV lambdas (M1e), PSO desc build on a cache miss (6fr), the Atmosphere producer (R1), most task bodies. Statements are from BGFX_MAP 6fu-6hj text, tagged [V structure]; only the visitor/wrapper claims were re-read today.

### L17b - OPEN (one fact: callers of the GDK shim not enumerated, role in rendering unproven)
- [V static] 0xe9389a4 (size 0x30c) is the XGameRuntime loader shim: strings QueryApiImpl, InitializeApiImpl, InitializeApiImplEx/Ex2, UninitializeApiImpl, XErrorReport; messages "XGameRuntimeInitialize must be called before making this call." (0xf884bf8), "XGameRuntime is outdated ..." and "missing required dependencies, run GamingRepair.exe" (0xe93615a). GameInput is used separately (GameInputTask 0xf5a7139, GameInputRedist.msi). The exe's DLL-name strings include dxgi.dll, dxgidebug.dll, d3d12.dll, amd_ags_x64.dll, playfabmultiplayergdk.dll; the live swapchain vtable is in dxgi.dll (L17a), so presentation does not go through a GDK API [V live+static]. Remaining: callers of 0xe9389a4 and whether any GDK call sits on the frame path (xref callers timed out here).

### L17c / L17d / L17g / L17h / L10b - OPEN (no new evidence; game closed)
- L17c: statics from 6dh unchanged (QueryVideoMemoryInfo budget strings, QPC timers 0xebdb740/0xebdb760 in submit); needs a live read of the timer globals [rip+0x4382c29..0x4382d36 region] with the game running.
- L17d: slot 7 0xe8102b0 anchored (function_anchors.tsv, slotcheck passes); live state obj+0x19F88 = 5 (healthy). A TDR cannot be triggered read-only: OPEN.
- L17g: init/shutdown order from 6di unchanged; shutdown ordering needs an exit observation (the game exited during this run but no trace was being polled).
- L17h: OptionSync plumbing for graphics options not traced (options.upscalingPercentage etc. strings found, writers not located).
- L10b: real cull still unfound.

### J1 / J3 / L18a / L18c - OPEN (one fact each: no patch exercised in game; docs/PLAN_OPTIMIZATION.md validation pending). J2/L18b see above.

### M3a - OPEN (M2c: 35 of 62 description structs untyped). M3b - OPEN (FRAME_CALLGRAPH two [?] links, M1d groups). M3c, M3d, M3e, M3f - OPEN (need the lead's build and an in-game run; no read-only evidence possible for hook behaviour; the game is closed now). M4c - OPEN (the same SelfTest wiring as K-P9; offline checks pass: layoutcheck 186/186, slotcheck).
### M1b / M1c / M1f - OPEN. M1f today: view records V (stride 0x140, rects, proj, mode) and swapchain/reset block checked live; still unchecked live: PSO key/executor claims, pass list names, semaphores ctx+0x80/+0x100, uniforms. M1b/M1c: not worked this run.

## FILES
Edited: src/sdk/Sigs.json (append), docs/data/layout_asserts.json (append), src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h (append, new file in git), docs/BEHAVIOR_NOTES.md, tools/sigs/descscan.py. New: tools/sigs/anchors.py, slotcheck.py, wrappersig.py, docs/data/function_anchors.tsv, port_check_functions_{60.05,51.01,50.04}.tsv, port_check_layout_asserts.tsv, docs/progress/platform-versioning-live.md.

### L17b - DONE (static, 62.01)
- GDK layer = 82 thin API wrappers in 0xe935740..0xe938604, all calling the loader/query helper 0xe9360fc (resolves an interface by GUID through the runtime shim 0xe9389a4: QueryApiImpl / InitializeApiImpl(Ex/Ex2) / UninitializeApiImpl / XErrorReport) then a vtable call [V]. 0xe9389a4's only caller is 0xe9360fc [V].
- ripscan of all 82 wrappers: 154 distinct calling functions (mostly 0x54xxxxx/0x1cxxxxx/0xe93xxxx platform and service code). Intersection with docs/data/frame_path_functions.tsv (955 functions of the direct-call frame path) = EMPTY [V]: no GDK API is called on the frame path. The only call in the renderer regions is 0xe8568f0 (D3D12 adapter/vendor info, strings NVIDIA/AMD/Intel) through wrapper 0xe935ea8: startup device info, not frame work. (0xe91fd60 is a ripscan false positive: a jump-table function.)
- Presentation is plain DXGI (live swapchain vtable in dxgi.dll, L17a). GDK integration therefore touches rendering only for adapter info at init.

### K-P9 / M4c - exact SelfTest wiring text (do not edit SelfTest.cpp; lead to paste)
In `runWorldChecks`, after `checkRenderLayout(tally);` add:
```cpp
checkRendererVtable(tally);
```
and before it define (SelfTest.cpp already includes RenderLayoutAsserts.h and BgfxContext.h is in sdk/mc/deps/bgfx):
```cpp
// K-P9: every slot of the live RendererContextD3D12 vtable (65 slots; BgfxContext::get() is that object, its queue is at +0xCC9268) must point into the game's code.
void checkRendererVtable(Tally& tally) {
    void* renderer = BgfxContext::get();
    if (!renderer) { recordFailure(tally, "[selftest] renderer vtable: no live context"); return; }
    const auto* vtable = *reinterpret_cast<const uintptr_t* const*>(renderer);
    constexpr size_t kSlots = 65;
    if (!hat::process::is_readable({reinterpret_cast<const std::byte*>(vtable), kSlots * sizeof(uintptr_t)})) { recordFailure(tally, "[selftest] renderer vtable unreadable"); return; }
    const auto* dos = reinterpret_cast<const uint8_t*>(GetModuleHandleW(nullptr));
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(dos + reinterpret_cast<const IMAGE_DOS_HEADER*>(dos)->e_lfanew);
    const IMAGE_SECTION_HEADER* sec = IMAGE_FIRST_SECTION(nt);
    uintptr_t begin = 0, end = 0;
    for (unsigned i = 0; i < nt->FileHeader.NumberOfSections; ++i)
        if (std::memcmp(sec[i].Name, ".text", 6) == 0) { begin = reinterpret_cast<uintptr_t>(dos) + sec[i].VirtualAddress; end = begin + sec[i].Misc.VirtualSize; }
    const size_t bad = renderlayout::firstSlotOutsideText(vtable, kSlots, begin, end);
    if (bad == kSlots) ++tally.passed;
    else recordFailure(tally, fmt::format("[selftest] renderer vtable drift: slot {} = 0x{:X} is outside .text", bad, vtable[bad]));
}
```
[I] untested C++ (no build allowed); the renderer-object identity BgfxContext::get() == RendererContextD3D12 is from OffsetProvider bgfx_RendererContextD3D12_mCommandQueue (+0xCC9268, the same offset the live read in L17a used on obj). Slot identity (not just in-.text) is checked offline by tools/sigs/slotcheck.py.
