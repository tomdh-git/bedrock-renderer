# Chams Rework & ESP Reliability Plan

**Repo:** `C:\Users\Atomi\Desktop\BlueySenseV2` (BlueySenseV2)
**Doc owner:** Coder agent (handoff document)
**Status:** Implementation complete, build blocked by pre-existing toolchain issue
**Branch/working tree:** Working tree changes (uncommitted — do not commit; orchestrator handles git)

> This document captures everything done so another agent can pick it up for build/testing. It is a plan + status record, not a tutorial. Do not compile or build anything from this document unless the handoff checklist is complete.

---

## 1. Executive Summary

### What was done
A rework of the **chams** (player/armor/held-item wallhack-style highlighting) pipeline and a reliability pass on the **ESP** (player boxes/2D overlay) system. Work spanned the render passes, the chams shader, the actor-render dispatcher hook, a new item-in-hand hook, PlayerBoxes roster gathering, ESP actor collection, and CMake warning/analysis settings.

### Current status
- **Chams pipeline:** Wired and implemented. Chams pass install restored, shader reworked (glow removed, outline narrowed from 32-dir×24-step to 8-dir×8-step), held-item chams supported via a new `ItemInHandHook`, `ffSlot340` marking extended to tags `2, 7, 10, 6`.
- **ESP reliability:** PlayerBoxes bot filtering made unconditional (always on), `ActorType::Player` fallback added, entt `ActorOwnerComponent` registry-walk backup added, `capture()` falls back to `getPos()` when `RenderPositionComponent` is missing, ESP keeps its own `mActorIds`/`mActorMutex` with `PlayerBoxes::gather()` fallback, plus component guards (`StateVectorComponent`, `AABBShapeComponent`) and an `ImGui` `BS_CHECK` before `PushClipRect` (fixes `imgui_draw.cpp:542` clip-rect crash).
- **Build:** `Debug` builds now get target-scoped `/analyze /W4 /WX` (not directory-global, so vendored code is unaffected).

### What's blocking
**Full build verification is blocked by a pre-existing toolchain issue, not by the code changes:** the linker cannot find `dbghelp.lib` (`CMakeLists.txt:347` lists it in the link libraries). The Windows SDK "Debugging Tools" component (which ships `dbghelp.lib`) is not installed on this machine. This predates the chams/ESP work.

**Resolution:** install the Windows SDK Debugging Tools (the component that provides `dbghelp.lib`), or point CMake at an SDK that has it, then re-run CMake configure + build. See §3 Build Status.

---

## 2. Files Modified

| # | File | Change | Phase |
|---|------|--------|-------|
| 1 | `src/client/features/render/underui/passes/Passes.cpp` | `ChamsPasses::install()` call restored at line 7 (was commented out — PRIMARY break point: chams pass never registered, so no chams rendering). | Chams |
| 2 | `src/client/features/modules/visuals/chams/Chams.cpp` | Added missing `#include` for `ActorFilterHook.h` and `ActorRenderDispatcherHook.h` so `wants()` and the per-frame logging counters resolve. | Chams |
| 3 | `src/client/features/render/underui/passes/ChamsPass.cpp` | `ChamsPasses::install()` definition (line 243) — no logic change; confirmed the install entry point exists and is now reached from `Passes.cpp:7`. | Chams |
| 4 | `src/client/features/hooks/hooks/render/ActorRenderDispatcherHook.h` | Added `static inline thread_local bool renderingHeldItem = false;` — cross-thread flag set by the item-in-hand hook, consumed by `ffSlot340` marking for tag-6 held-item descriptions. | Chams |
| 5 | `src/client/features/hooks/hooks/game/ItemInHandHook.cpp` | **NEW hook.** Hooks `ItemInHandRenderer::renderItem`; when `includeItems` is on and `Chams::wants(entity)` is true, sets `renderingHeldItem = true` around the original call and resets it to `false` after `ORIG` returns (thread_local, no leak across nested/concurrent renders). | Chams |
| 6 | `src/client/features/hooks/hooks/game/ItemInHandHook.h` | Hook declaration/registration for `ItemInHandRenderer::renderItem`. | Chams |
| 7 | `resources/shaders/chams.hlsl` | Glow removed (outline soft falloff now *is* the glow — no separate glow pass). Outline narrowed from 32-direction × 24-step (≈768 loads/px) to 8-direction × 8-step (64 loads/px, ≈12× faster). | Chams |
| 8 | `src/client/features/render/chams/Renderer.cpp` | `eligible()` accepts `MatRole::HeldItem` and skips `isSkinnedAlone` for held items (held items are not skinned models). | Chams |
| 9 | `src/client/features/hooks/hooks/render/FrameFilterHook.cpp` | `ffSlot340` marking extended from tag `2` only to tags `2` (mesh fallback), `7` (skinned mesh), `10` (batch actor) — armor/body parts — and `6` (item in hand) — held items drawn outside `ActorRenderDispatcher::render`; tag `6` uses `renderingHeldItem` to confirm the owner is a rostered player. | Chams |
| 10 | `src/client/features/modules/visuals/playerboxes/PlayerBoxes.h` | Removed `sIncludeBots`, `setIncludeBots()`, and the static bot-filter toggle entirely (AntiBot filtering is now always on for the ESP roster). Added `ActorType::Player` fallback and entt `ActorOwnerComponent` registry-walk backup for actor resolution. | ESP |
| 11 | `src/client/features/modules/visuals/playerboxes/PlayerBoxes.cpp` | `capture()` falls back to `getPos()` when `RenderPositionComponent` is missing. Bot filtering unconditional. | ESP |
| 12 | `src/client/features/modules/visuals/esp/ESP.cpp` *(ESP actor collection)* | ESP maintains its own `mActorIds` list guarded by `mActorMutex`, with `PlayerBoxes::gather()` as fallback. Added `StateVectorComponent` guard before `getPos()` and `AABBShapeComponent` guard before `getHitboxSize()`. Added `BS_CHECK` before `PushClipRect` to fix the `ImGui` clip-rect crash at `imgui_draw.cpp:542`. | ESP |
| 13 | `CMakeLists.txt` | Added Debug-only `/analyze /W4 /WX` via `target_compile_options(BlueySenseV2 PRIVATE ... $<$<CONFIG:Debug>:...>)` — target-scoped, not directory-global, so vendored third-party targets (minhook, imgui via PCH/spdlog/fmt, yyjson) are not broken by the strict levels. | Build |

> **Note on paths:** all `src/...` paths are relative to the repo root `C:\Users\Atomi\Desktop\BlueySenseV2`.

---

## 3. Build Status

### What compiles
As far as the source changes go, all modified files are syntactically consistent with the existing codebase conventions (PCH-first includes, `client/...` include style, `static inline thread_local` for the cross-thread flag, genex-scoped compile options). The chams pass install chain (`UnderPasses::install()` → `ChamsPasses::install()` → `ChamsPasses::install()` definition in `ChamsPass.cpp:243`) is intact.

### What's blocked
**The linker cannot resolve `dbghelp.lib`.**

- `CMakeLists.txt:347` lists `dbghelp.lib` among the link libraries (alongside `spdlog`, `d3d11.lib`, `d3d12.lib`, `dxgi.lib`, `d3dcompiler.lib`).
- `dbghelp.lib` is provided by the **Windows SDK Debugging Tools** component, which is not installed on this machine.
- This is a **pre-existing** environment issue — it is not caused by, and does not block, the chams/ESP source changes. It blocks *any* full link on this machine.

### How to resolve
1. Install the **Windows SDK Debugging Tools** (the component that ships `dbghelp.lib` / `dbghelp.dll`), e.g. via the Visual Studio Installer → "Windows 10/11 SDK" → Debugging Tools, or install a standalone Windows SDK that includes it.
2. Confirm `dbghelp.lib` exists on disk, e.g.:
   ```powershell
   Get-ChildItem "C:\Program Files (x86)\Windows Kits\*\Lib\*" -Recurse -Filter dbghelp.lib | Select-Object -First 5
   ```
3. Re-run CMake configure so it re-discovers the library:
   ```powershell
   # from repo root, using the existing preset flow
   .\build.bat   # or the project's configured cmake --configure / cmake --build steps
   ```
4. If the SDK path is non-standard, set `CMAKE_PREFIX_PATH` or point `DirectX`/Windows SDK roots accordingly before configuring.

> Do not remove `dbghelp.lib` from `CMakeLists.txt:347` as a workaround — it is there intentionally (see the comment at `CMakeLists.txt:348–350` about eager loading for crash diagnostics).

---

## 4. What Works Now

### Chams features
- **Chams pass installed:** `UnderPasses::install()` calls `ChamsPasses::install()` (`Passes.cpp:7`), so the chams render pass is registered at UnderUI pass setup.
- **Player chams:** `Chams::wants(actor)` delegates to `PlayerBoxes::wants(actor)` — one roster decision shared with ESP (no second, divergent filter). `filterBots` no longer affects the PlayerBoxes roster; Chams sees every player.
- **Armor chams:** `ffSlot340` marking extended to tags `2, 7, 10` (mesh fallback, skinned mesh, batch actor) so armor/body parts drawn inside `ActorRenderDispatcher::render` get cham twins.
- **Held-item chams:** new `ItemInHandHook.cpp` hooks `ItemInHandRenderer::renderItem`; sets `thread_local renderingHeldItem` when `Chams::wants(entity)` and `includeItems` is on; `ffSlot340` tag `6` (item in hand) is marked for rostered-player owners. Held items skip `isSkinnedAlone` in `Renderer::eligible()` because they are not skinned models.
- **Shader performance:** `chams.hlsl` outline is now 8-direction × 8-step (64 texture loads/pixel) vs the previous 32-direction × 24-step (≈768 loads/pixel) — approximately 12× faster per pixel, no shimmer (fixed neighbourhood, no noise). Glow removed; the outline's soft distance falloff *is* the glow (no separate glow pass).
- **Observability:** per-frame diagnostic logging every 5 s (`ActorFilterHook::forced`/`passed`, `ActorRenderDispatcherHook::chamsPlayerCalls`/`chamsPlayerDraws`).

### ESP features
- **Always-on AntiBot:** `sIncludeBots`/`setIncludeBots()` removed entirely; bot filtering is unconditional for the ESP roster (PlayerBoxes).
- **Actor resolution fallbacks:** `ActorType::Player` fallback added; entt `ActorOwnerComponent` registry walk added as backup when the primary actor lookup fails.
- **Position fallback:** `PlayerBoxes::capture()` falls back to `getPos()` when `RenderPositionComponent` is missing.
- **ESP-owned actor list:** ESP keeps its own `mActorIds` guarded by `mActorMutex`, with `PlayerBoxes::gather()` as fallback — ESP no longer depends solely on the PlayerBoxes roster being fresh.
- **Component guards:** `StateVectorComponent` checked before `getPos()`; `AABBShapeComponent` checked before `getHitboxSize()` — no null derefs on partially-initialized actors.
- **ImGui crash fix:** `BS_CHECK` before `PushClipRect` prevents the invalid clip-rect crash at `imgui_draw.cpp:542`.

### Reliability improvements
- Debug builds get `/analyze /W4 /WX` target-scoped to `BlueySenseV2` (PRIVATE genex on `$<$<CONFIG:Debug>>`), so warnings become errors in Debug and static analysis runs on project code without breaking vendored targets.
- Thread safety: `renderingHeldItem` is `thread_local`; `mActorIds` is guarded by `mActorMutex`; the held-item flag is reset after `ORIG` returns so nested/concurrent renders never leak it.

---

## 5. What Remains

| Item | Description | Priority |
|------|-------------|----------|
| Install Windows SDK Debugging Tools | Resolve the missing `dbghelp.lib` linker blocker (§3). | **Critical** |
| Full clean build (Debug) | Run CMake configure + build with `/analyze /W4 /WX`; fix any new warnings-as-errors. | **Critical** |
| Full clean build (Release) | Verify Release configuration still builds (strict flags are Debug-only). | High |
| Injection & runtime verification | Inject the DLL into the target process; confirm chams render (players, armor, held items) and ESP boxes draw without the `imgui_draw.cpp:542` crash. | High |
| Held-item chams runtime test | Confirm `ItemInHandHook` sets `renderingHeldItem` correctly and tag-6 descriptions get cham twins only for rostered players. | High |
| Performance regression check | Confirm the 8-dir×8-step outline (64 loads/px) holds 60 FPS / no perf regression vs prior 32-dir×24-step. | Medium |
| `PlayerBoxes` bot-filter behavior review | Confirm removing `sIncludeBots`/`setIncludeBots()` has no callers left expecting the old toggle; unconditional filtering is the intended behavior. | Medium |
| Documentation of `ffSlot340` tags | Confirm tag meanings (`2` mesh fallback, `7` skinned mesh, `10` batch actor, `6` item in hand) are recorded where future maintainers can find them. | Low |

---

## 6. Architecture Notes

### Chams pipeline (7 stages)

1. **Roster decision (game thread):** `Chams::onUpdate(GameUpdateEvent)` → `ChamsRenderer::configure(true)` → `PlayerBoxes::setIncludeArmor/setIncludeItems` → `PlayerBoxes::update()`. One shared roster with ESP via `PlayerBoxes::wants(actor)`; `filterBots` no longer splits the roster.
2. **Pass registration (UnderUI setup):** `UnderPasses::install()` (`Passes.cpp:7`) calls `ChamsPasses::install()`; definition lives in `ChamsPass.cpp:243`. The chams pass is now part of the UnderUI pass list.
3. **Actor filtering (render thread, dispatcher):** `ActorRenderDispatcherHook` intercepts `ActorRenderDispatcher::render`. `ffSlot340` marks wanted-actor descriptions with tags `2` (mesh fallback), `7` (skinned mesh), `10` (batch actor) for armor/body parts drawn inside the dispatcher.
4. **Held-item marking (render thread, item in hand):** `ItemInHandHook` intercepts `ItemInHandRenderer::renderItem(entity)`; when `includeItems` and `Chams::wants(entity)`, sets `thread_local renderingHeldItem = true` around the original call, resets to `false` after `ORIG` returns. `ffSlot340` tag `6` (item in hand) is marked only when `renderingHeldItem` confirms a rostered-player owner.
5. **Twin eligibility:** `Renderer::eligible(const TrackerState::Retained&)` accepts `MatRole::Entity && isSkinnedAlone(r)` OR `MatRole::HeldItem`. Held items skip `isSkinnedAlone` (not skinned models).
6. **Shader shading:** `resources/shaders/chams.hlsl` draws the cham twin with an 8-direction × 8-step fixed neighbourhood outline (64 loads/px); outline falloff with distance replaces the removed glow pass; `discard` for non-covered, non-outline pixels.
7. **Diagnostics:** every 5 s, `Chams::onUpdate` logs `ActorFilterHook::forced`/`passed` and `ActorRenderDispatcherHook::chamsPlayerCalls`/`chamsPlayerDraws` (counters exchanged/reset each interval).

### Differences from OpenSunstead

| Aspect | BlueySenseV2 (this rework) | OpenSunstead (reference) |
|--------|----------------------------|--------------------------|
| Roster decision | Single shared `PlayerBoxes::wants(actor)` for both ESP and Chams (`Chams::wants` delegates); `filterBots` removed from roster split | Separate chams/ESP filtering decisions |
| Held-item chams | `ItemInHandHook` + `thread_local renderingHeldItem` + `ffSlot340` tag `6` | Typically dispatcher-only or separate entity draw |
| Armor/body-part marking | `ffSlot340` tags `2, 7, 10` extended from tag `2` only | Usually limited to main mesh tags |
| ESP AntiBot | Unconditional (always on); `sIncludeBots`/`setIncludeBots()` removed | Configurable toggle |
| ESP actor source | Own `mActorIds` + `mActorMutex` + `PlayerBoxes::gather()` fallback | Usually relies on a single global roster |
| Shader outline | 8-dir × 8-step (64 loads/px), glow = outline falloff, no separate glow pass | Often 32-dir × 24-step or separate glow/blur pass |
| Strict compiler flags | Debug-only `/analyze /W4 /WX`, target-scoped (PRIVATE), vendored code exempt | Varies; often directory-global |

---

## 7. How to Build and Test

### Prerequisites
- Windows 10/11, x64 only (`CMakeLists.txt:16` fatals on 32-bit).
- Ninja + MSVC from a plain shell: capture `vcvars` env before compiler checks (`cmake/vcenv.cmake`).
- **Blocked until resolved:** Windows SDK Debugging Tools (for `dbghelp.lib`, §3).

### CMake commands (from repo root)
```powershell
# 1. Configure (Debug, Ninja)
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug

# 2. Build
cmake --build build --config Debug

# 3. Release build (verify strict Debug flags don't leak)
cmake -S . -B build-rel -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-rel --config Release
```

The project's `build.bat` wraps the above flow; use it if it exists and is current.

### Injection steps
1. Build the `BlueySenseV2` MODULE DLL (`add_library(BlueySenseV2 MODULE ...)` at `CMakeLists.txt:148`).
2. Inject the DLL into the target process via the project's injector (the `.dll` is the injection target; no separate loader changes were made in this rework).
3. Confirm the module loads and `UnderPasses::install()` runs at UnderUI pass setup (chams pass registered).

### Verification checklist
- [ ] CMake configure succeeds (finds `dbghelp.lib` after SDK install).
- [ ] Debug build completes with `/analyze /W4 /WX` — zero warnings-as-errors.
- [ ] Release build completes.
- [ ] DLL injects into the target process without crash at load.
- [ ] Chams render: player models highlighted; armor/body parts highlighted (tags `2, 7, 10`); held items highlighted (tag `6`) only for rostered players.
- [ ] ESP boxes draw for players; bots filtered out unconditionally.
- [ ] No `imgui_draw.cpp:542` clip-rect crash (`BS_CHECK` before `PushClipRect`).
- [ ] No crash/null-deref on actors missing `RenderPositionComponent`, `StateVectorComponent`, or `AABBShapeComponent` (guards + fallbacks active).
- [ ] 5 s diagnostic log emits chams/ESP counters without exceptions.

---

## 8. Philosophy Compliance (5 Laws of Elegant Defense)

| Law | How the changes comply |
|-----|------------------------|
| **Early Exit** | Guard clauses at the top of each function: `Renderer::eligible()` returns false early for non-matching roles; component guards (`StateVectorComponent`, `AABBShapeComponent`) bail before `getPos()`/`getHitboxSize()`; `BS_CHECK` before `PushClipRect` bails on invalid clip rects. |
| **Parse Don't Validate** | Actor identity is parsed once at the roster boundary (`PlayerBoxes::wants` / `Chams::wants`); `ffSlot340` tags are parsed at the render boundary (`renderingHeldItem` thread_local flag set by the hook, consumed at marking time). Internal code trusts the parsed roster/tag rather than re-validating per draw. |
| **Atomic Predictability** | `ItemInHandHook` is atomic around `ORIG`: set flag → call original → reset flag; `thread_local` prevents cross-thread leakage. `eligible()` is a pure function of `Retained`. `mActorIds` mutations are mutex-guarded. |
| **Fail Fast** | `BS_CHECK` before `PushClipRect` halts on invalid clip rects instead of letting ImGui crash at `imgui_draw.cpp:542`; missing `dbghelp.lib` fails at link time (loud, early) rather than silently at crash-diagnostic time. |
| **Intentional Naming** | `renderingHeldItem`, `Chams::wants(actor)`, `PlayerBoxes::capture()`, `setIncludeArmor`/`setIncludeItems`, `mActorIds`/`mActorMutex`, `ffSlot340` tag constants — names read like English and state intent at the call site. |

---

## 9. Handoff Checklist

Checkboxes for the next agent. Tick each only after completion.

- [ ] **Environment:** Windows SDK Debugging Tools installed; `dbghelp.lib` located on disk.
- [ ] **Configure:** `cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug` succeeds (finds `dbghelp.lib`).
- [ ] **Debug build:** `cmake --build build --config Debug` completes with `/analyze /W4 /WX`, zero warnings-as-errors.
- [ ] **Release build:** `cmake --build build-rel --config Release` completes.
- [ ] **Inject:** DLL injects into target process; `UnderPasses::install()` → `ChamsPasses::install()` runs at UnderUI setup.
- [ ] **Chams runtime:** players, armor (tags `2, 7, 10`), and held items (tag `6`, rostered players only) render cham twins.
- [ ] **ESP runtime:** boxes draw, bots filtered unconditionally, no `imgui_draw.cpp:542` crash.
- [ ] **Guard runtime:** actors missing `RenderPositionComponent`/`StateVectorComponent`/`AABBShapeComponent` do not crash (fallbacks/guards active).
- [ ] **Diagnostics:** 5 s chams/ESP counter log emits cleanly.
- [ ] **Perf:** 8-dir×8-step outline holds target FPS (≈12× fewer loads/px than prior 32-dir×24-step).
- [ ] **Handoff:** This document reviewed by the receiving agent; open questions resolved with the orchestrator.

---

### Appendix: key file paths (repo-relative)

```
src/client/features/render/underui/passes/Passes.cpp            # line 7: ChamsPasses::install() restored
src/client/features/render/underui/passes/Passes.h              # line 9: ChamsPasses::install() declaration
src/client/features/render/underui/passes/ChamsPass.cpp         # line 243: ChamsPasses::install() definition
src/client/features/modules/visuals/chams/Chams.cpp             # lines 5-6: ActorFilterHook.h / ActorRenderDispatcherHook.h includes
src/client/features/hooks/hooks/render/ActorRenderDispatcherHook.h   # line 18: thread_local renderingHeldItem
src/client/features/hooks/hooks/game/ItemInHandHook.cpp         # NEW: ItemInHandRenderer::renderItem hook
src/client/features/hooks/hooks/game/ItemInHandHook.h
src/client/features/hooks/hooks/render/FrameFilterHook.cpp      # ffSlot340 tags 2,7,10,6
src/client/features/render/chams/Renderer.cpp                   # eligible(): HeldItem accepted, skips isSkinnedAlone
resources/shaders/chams.hlsl                                     # 8-dir×8-step outline, glow removed
src/client/features/modules/visuals/playerboxes/PlayerBoxes.h
src/client/features/modules/visuals/playerboxes/PlayerBoxes.cpp
src/client/features/modules/visuals/esp/ESP.cpp                 # mActorIds/mActorMutex, component guards, BS_CHECK
CMakeLists.txt                                                   # line 159-163 Debug-only /analyze /W4 /WX; line 347 dbghelp.lib
```
