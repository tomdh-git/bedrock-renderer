# Resource pack manager: 1.26.51 -> 1.26.60 handoff notes

Status: **not working on 1.26.51 either** (in-world global pack change was never confirmed in game). These notes mark where the system was and what moved, so work can continue on 1.26.60.05 directly. Nothing here is re-derived yet.

## 1.26.51.01 reference (from the RE notes, RVAs of that exe)

| Function | RVA | What it does |
|---|---|---|
| `ResourcePackManager::setStack` | 0x14c7f20 | (this, unique_ptr<Stack>*, type); ends with `mPendingRestack \|= changed`. 907 bytes, 6 calls. |
| `_composeFullStack` + notify | 0x14c9010 | asks every listener `onFullPackStackInvalid`, composes, calls listeners' `onActiveResourcePacksChanged` |
| `composeFullStack(out, global, level)` | 0x14c9170 | sig in Sigs.json |
| `_doStackOperation` | 0x14c82b0 | |
| `MinecraftGame::_deserializeGlobalResourcePacks` | 0x773490 | (this, out) |
| `MinecraftGame::_loadGlobalResourcePacks` | 0x773030 | empties the stack and clears `mUseGlobalPackStack` when game vfunc +0x700 is true |
| MinecraftGame listener vtable | 0xe76ee10 | slot1 `onActiveResourcePacksChanged` 0x823ce0 -> `_finishReloadingResources` 0x7cca00; slot2 `onFullPackStackInvalid` 0x824200 |
| `GeneralSettingsScreenController` exit handler (`applyOnExit`) | 0x4e8e3b0 | calls `_setGlobalStack` |
| `_setGlobalStack` | 0x4e8dfa0 | gate on "in a level" returns early; PackHook NOPs the `jne` at +0x11C |

Layout in 1.26.51 (+0x10 vs Levi): level 0x98, global 0xA0, treatment 0xA8, base 0xB0, full 0xB8, listeners set 0x58, mInitializing 0xE8, mPendingRestack 0xE9, mUseGlobalPackStack 0xEA, mutex 0xF0. Stack type enum: Level 0, Global 1, Treatment 2, BaseGame 3. Manager is `MinecraftGame + 0x218` (game vtable +0x260 call).

## What the 1.26.60.05 audit found

- `ResourcePackManager::setStack` signature (36-byte exact prologue) matches **one** place in 1.26.60: RVA **0x61ebfb0**. That is **not** setStack: it is 2855 bytes with 23 calls, against 907 bytes and 6 calls before (instruction similarity 0.32). Treat as a false positive. The prologue is only the common 8-register push + `sub rsp,0xC8` frame.
- Dead (no match at all) in 1.26.60: `composeFullStack`, `applyOnExit`, `setGlobalStack`, `bindingA` to `bindingD`, `canMove`, `canMoveUp`, `canMoveDown`. Together with the false positive, the whole group moved or was rewritten.
- `ResourcePackManager::loadResource` is live and verified (old 0x14c00d0, new 0x17c4600, 0.91 similarity). It is the nearest anchor to start from: setStack and composeFullStack were its neighbours in 1.26.51 (0x14c7f20 and 0x14c9170, about 0x7e50 and 0x9000 after it). Look near 0x17c4600 + that distance.

## Why a rewrite is likely (26.60 changelog)

- Focus now follows a pack to its new position when reordered.
- The pack list scrolls while a pack is carried; controller reorder position bug fixed.
- Joining a friend's world while in a world no longer loads newer Vanilla resources for an older template.
- Malformed resource archives no longer crash.
- Pack settings: multiselect rendering changed.

## How to continue

1. `xref.py str` on the 1.26.51 assert strings the old functions used (the game keeps `__FUNCTION__` text), then run the same strings against 1.26.60.05.
2. Start from `loadResource` (live) and from callers of `_deserializeGlobalResourcePacks` / `MinecraftGame::_update`, which also died: both are in the dead list for the same update.
3. Re-check the member layout above against the new class (the +0x10 shift may have changed).
4. Use `BS_EXE` and `BS_SIGS` env vars so the sig tools point at the 1.26.60.05 exe and this worktree's `src/sdk/Sigs.json` (their defaults are the old exe and the main checkout).
