# Conventions

Conventions for new code. Client-owned subsystem namespaces use PascalCase (`Platform`, `Render`, `UI`, `Accounts`, `Config`, `RuntimeHealth`, `Diag`, `Preferences`). Namespaces in `src/sdk` that mirror game types retain the game's spelling. Checked by `python tools/check.py` (see `tools/README.md`).

## Includes

- Client and SDK files use quoted includes only (`"client/..."`, `"sdk/..."`). Every `<...>` include lives in the generated block of `src/Pch.h`.
- Do not edit that block by hand: write `#include <deque>` where you need it, then build or run `python tools/check.py includes`; it moves into `Pch.h`.
- A header includes only what its declarations need; forward-declare (`struct Resource;`) when a pointer or reference is enough. `python tools/check.py fanout` lists the expensive headers to rebuild.
- `Str` (the shared string helpers) lives in `Platform` (`client/platform/text/StringUtils.h`).
- Exception: `src/sdk/xbox/auth/Wam.cpp` (C++/WinRT redefines things the rest of the tree relies on).

## Namespaces

- Client subsystem namespaces are `Platform`, `Render`, `UI`, `Accounts`, `Config`, `RuntimeHealth`, `Diag`, and `Preferences`. The SDK retains external/game ABI namespace spellings to avoid collisions with game types.
- Framework declarations such as `Module`, `Setting`, `Event`, `Hook`, `Detour`, `Logger`, and `Json` remain at the client root when they are shared across subsystems. Platform, rendering, UI, account, config, and health APIs live in their owning namespace.
- No `using namespace` and no anonymous namespaces in client code: file-local functions and state are `static` (a file-local type or class just gets a name that is unique in its folder, since the folder is built as one unity file).
- `src/sdk/` mirrors the game's own names and is exempt.
- Checked by `python tools/check.py namespaces` (one violation per file per kind).

## Layers

| Layer | May depend on |
|---|---|
| `sdk` | OS/std only, plus client `core` (Logger, Json, Eventing) and `Platform` (Files) - the SDK logs and reads assets through the client's services |
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

Only `platform` calls the OS or the hardware. A function is at most 40 lines.

## Managers

- One public manager header per subsystem. Implementation files are private to that folder and are not included by consumers.
- `Systems` owns lifecycle and health only; it is not a service locator.

## Comments

- Default to none. A comment is only for an invariant, a thread/order constraint, an external-format quirk, a game-version dependency, or a non-obvious hazard.
- No narration, no restating signatures.
- Never blanket-delete a comment that records an invariant; remove narration only while touching a file.

## Naming

- Files `PascalCase.h/.cpp`, filename = primary type; related helpers may share a file named for the subsystem.
- Types `PascalCase`. Acronyms are words for client types (`Json`, `Gui`, `Ui`, `Gpu`, `Http`); vendor/API spellings stay (`D3D12`, `ImGui`, `WndProc`, `XAudio2`, `Win32`). SDK keeps game names.
- Functions `camelCase`; manager lifecycle verbs `init`, `start`, `stop`, `shutdown`, `refresh`, `health`. Getters drop `get` unless it collides (`getOriginal`).
- Variables: members `mPascalCase`, file/function statics `sPascalCase`, global inline state `gPascalCase`, compile-time constants `kPascalCase`, locals/params `camelCase`.
- Macros: `BS_` prefix for utilities (`BS_CHECK`, `BS_PROFILE`). The module/hook DSL keeps short names (`ON`, `HOOK`, `HOOK_AT`, `ORIG`, `SIG`) because they read as keywords.
- Directories lowercase; multi-word directories use `_` (`click_gui`, `under_ui`, `view_hands`, `alt_manager`, `pack_loader`, `option_sync`, `main_menu`, `debug_ui`, `wnd_proc`). Names migrated in Phase 1.

## Building

- `build.bat [ninja|vs] [debug|release] [clean]`. Each config has its own tree (`build\ninja-Debug`, `build\ninja-Release`); the DLL lands in `build\Debug\`, `build\Release\`.
- For isolated fast iteration, use `cmake --preset ninja-debug` and `cmake --build --preset ninja-debug --parallel 8`; it uses raw resources and does not build the release packer.
- One build at a time per folder (`build.lock`): two at once corrupt ninja's dependency log and force a full rebuild.
- The source list is refreshed automatically when a `.cpp` is added, removed or renamed. Unity batches are per directory and chosen by a hash of the file path, so such a change rebuilds one batch, not everything after it.
- Release is optimised for speed (`/O2 /Ob3 /GL /LTCG`, AVX2); Debug is `/Od`.
- The game holds the DLL while it runs: a link then fails with LNK1168. Compiling is unaffected.
