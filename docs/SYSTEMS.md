# Runtime systems

This is the current map of cross-cutting systems. Put a new service beside the closest existing service, expose one small public facade, and keep implementation details in that subsystem's directory. `app/Systems.cpp` owns lifecycle order; it should wire services together, not become a service locator.

## Ownership map

| Concern | Owner | What it provides |
|---|---|---|
| Startup and shutdown | `client/app/` | Ordered initialization, early Present startup, and reverse teardown. |
| OS and hardware access | `client/platform/` | Files, time, process, window, input, image, resources, and audio-device access. |
| Logs, crash reports, profiling, hang reports | `client/core/diagnostics/` | Central logs, crash capture, profiler, watchdog, and eject drain. |
| Game-thread work | `client/core/threading/` | `GameQueue` and captured game/render thread identities. |
| Runtime capability health | `client/core/health/` | Capability availability and user-facing reasons consumed by modules. |
| Events and event payloads | `client/core/event/` | Dispatcher and shared game/render/UI events. |
| Game build identity | `sdk/GameVersion.*` | Preflight before service startup; known mismatches and unknown identities stop startup unless their separate, explicit environment overrides are set. |
| Signatures, offsets, and SDK probes | `sdk/` and `tools/sigs/`, `tools/sdkgen/` | Runtime resolution, update-day audit, generated layout checks, and static/world self-checks. |
| Hook lifecycle | `client/features/hooks/` | Detour registry, optional/required failure policy, install/enable order, and unload handling. |
| Hook implementations | `client/features/hooks/hooks/{game,render,input,network,resources}/` | Hooks grouped by the game subsystem they touch. |
| Render device and swapchain | `client/features/render/` | Renderer ownership, resize teardown/rebuild, device-removed recovery, backend, tracker, and passes. |
| Module availability and settings | `client/features/modules/` | Requirements, settings, category registration, and unavailable-state UI. |
| User settings | `client/features/settings/` | Preferences plus named module-state profiles; preferences select a profile while profiles serialize and apply module state. Both use versioned JSON and preserve unreadable/newer files. |

## Existing guardrails

- The game-version check runs before `Systems::init`; known mismatches and unknown builds fail closed by default. Diagnostic overrides are `BS_ALLOW_MISMATCH_VERSION=1` and `BS_ALLOW_UNKNOWN_VERSION=1`.
- Signature resolution reports dead, ambiguous, duplicate-address, and canary failures; the static self-check records results instead of crashing on every discrepancy.
- Optional hooks can be skipped and surfaced in the debug UI, including late MinHook creation failures. Required hooks fail startup. Hook install/enable is staged, and eject waits for in-flight calls before unloading.
- `GameQueue` moves work to the game thread. `ThreadContract` currently warns at selected dangerous game-state reads; it does not make arbitrary game-memory reads thread-safe.
- Renderer teardown releases swapchain-bound resources on resize or swapchain replacement. Device removal is detected and rebuilt on the next frame. The health panel reports waiting, ready, resize, minimize, recovery, setup failure, and stopped states.
- Account, token, and HTTP diagnostics redact identity claims, URL paths, query strings, headers, and bodies. Request method, host, status, user agent, and content byte counts remain available for troubleshooting.
- The module UI supports Ctrl+F fuzzy search across module names, tooltips, and setting names/help text; setting descriptions are view-only metadata and are not written to configs.
- MSVC stack-cookie protection remains enabled in Debug and Release builds.
- Crash dump retention keeps the newest ten `crash_*.dmp` files, preventing repeated failures from growing AppData without limit.
- CI builds the Windows client and runs source, signature-database, Python, and C++ checks.

## Remaining audit items

- **MSAA policy:** motion blur and depth of field remain disabled for multisampled scene targets. Supporting them needs a tested depth resolve/read path and a render-mode matrix; silently sampling one depth value per pixel is incorrect. This is an explicit compatibility boundary for now.
- **Thread-affinity coverage:** `ThreadContract` remains warn-only at known call sites. Expand it only where ownership is proven; render snapshots must remain explicit because some game state is intentionally consumed across threads.
- **HLSL CI:** CI now compiles every embedded UnderUI resource shader entry point with the D3D compiler. Inline shaders in the C++ renderer sources are still only compiled when their runtime path is exercised; extracting them into shared shader resources is the remaining coverage gap.
- **Allocation attribution:** existing CPU scopes and GPU timestamps measure elapsed cost, but do not identify allocator pressure. Add counters only around measured hot paths; a process-wide `operator new` hook would distort timings and affect the injected game's allocator.
- **AppData footprint:** general settings are consolidated and crash dumps are bounded. The current local data is dominated by the viewmodel library and its `library.old-*` backup, textures, and user assets; these are retained because they contain user-managed content. The current profile has roughly 1.2 GB in `viewmodel/`, 136 MB in `assets/`, and 16 MB in `orelocations/`.

The expert insight notes in Downloads are research input; several statuses there predate the current code and must not be copied forward without checking the owner listed above.
