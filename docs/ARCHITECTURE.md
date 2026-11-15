# Architecture

BlueySenseV2 is a DLL injected into Minecraft Bedrock. It resolves game functions by signature, detours them with MinHook, and lets modules react to an event bus: `sdk` mirrors the game, `platform` is the only code that touches the OS or hardware, `core` holds cross-cutting services, and `features` hold everything the client adds.

## Tree

```
src/client/
  app/         App, Main, Systems
  platform/    OS/hardware boundary, grouped by audio, filesystem, image, input, process, resources, text, time, window
  core/        diagnostics, event, files, game, gpu, health, runtime, threading, util
  features/
    modules/   Module framework + combat/ movement/ player/ visuals/ other/ (one Register.cpp per category)
    settings/  User-facing settings: preferences and module config profiles
    hooks/     Lifecycle/registry plus hooks/{game,render,input,network,resources}
    render/    backend, draw, post, tracker, underui, lce, packcolor
    ui/        manager/input router, accounts, click_gui/{layout,panels,shared,state,widgets}, menu, splash
    accounts/  account identity/session subsystem
    packloader/ resource-pack loading
src/sdk/       the game mirrored (signatures, offsets, generated types), xbox services, the Valve viewmodel port (csgo), vendored LCE reference
```

Related implementations are grouped by the system they serve; shared lifecycle and public facades stay at the subsystem root. Layering is enforced by `tools/check.py`, not by directory depth.

## Layers

| Layer | May depend on |
|---|---|
| `sdk` | OS/std only, plus client `core` (Logger, Json, Eventing) and `platform` (Files) - the SDK logs and reads assets through the client's services |
| `src/sdk/csgo` | everything (client code under sdk/: the Valve viewmodel/paint/studio/VTF port) |
| `platform` | OS/std + `sdk` |
| `core` | `platform`, `sdk` |
| `features/modules` | `core`/`platform`/`sdk` + render, hooks |
| `features/render` | `core`/`platform`/`sdk` + hooks |
| `features/settings` | `core`/`platform`/`sdk`, modules |
| `features/accounts` | `core`/`platform`/`sdk` + render, hooks |
| `features/packloader` | `core`/`platform`/`sdk` + hooks |
| `features/ui` | `core`/`platform`/`sdk`, modules, settings, accounts, render, hooks |
| `features/hooks` | `core`/`platform`/`sdk` + the render facade (`Renderer`, `CommandListTracker`); never ui or concrete modules |
| `app/Systems` | everything |

Checked by `python tools/check.py layers`; parked-WIP files are exempted in `tools/check.py` until they land.

## Lifecycle

`Systems` runs one ordered init and, at eject, the reverse shutdown. Startup order:

```
paths -> logger -> crash -> assets -> modules(register) -> config(load) -> accounts -> audio
-> ui -> render -> hooks -> health -> modules(start) -> window
```

`health` runs after hooks so capability status is known before modules start. Modules whose required capabilities are unavailable are held back (see `docs/MODULES.md`).

## Data flow

```
game function
  -> SigManager resolves a signature   (src/sdk/Sigs.json)
  -> HOOK detour                        (MinHook)
  -> event bus                          (Eventing)
  -> module handlers
  -> render / UI
```

`features/settings` groups the user-facing settings surface. Its `Preferences` service stores client-wide choices (currently the active config name and menu background) in versioned `settings/preferences.json`; its `ConfigManager` stores named JSON profiles because those files serialize and apply module state and therefore depend on `ModuleManager`. Signatures live in `src/sdk/Sigs.json`; game offsets and vtable indices live in `src/sdk/OffsetProvider.h`. The version gate is `src/sdk/GameVersion.*`, called before `Systems::init`; runtime capability health is in `src/client/core/health/Capabilities.*`.

## Manager pattern

- One public manager header per subsystem; implementation files are private to its folder.
- Consumers include the manager, never the implementation.
- `Systems` owns ordered lifecycle and health only, not service lookup. Managers alone: `AssetManager`, `AudioManager`, `AccountManager`, `HookManager`, `ModuleManager`, `ConfigManager`, `UI::Manager`, `UI::InputRouter`, `RenderManager`, `ViewmodelManager`, `Capabilities`.

## Cycles being removed

- `features/render -> ui/modules` (render draws; it does not call the UI or concrete modules).
- `App in core -> features` (App moves to `app/`, and dependencies point down the layer table above).
