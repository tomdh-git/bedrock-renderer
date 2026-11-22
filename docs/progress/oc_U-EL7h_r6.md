## NEXT
DONE

# Unit U-EL7h: L7h Material swap hook — pass-name resolver 0x675e440 + item-visitor hash switches (6cj)

## Scope

Checklist item L7h (docs/RENDER_CHECKLIST.md line 341): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".
This unit WRITES the hook (engineering task — the orchestrator hint overrides the static-only reading of prior attempts oc_U-EL7h r1/r2/r3/r4/r5). The static control point was already proven [V] by those notes (verify_oc 30/30, r2 review 43/43) and is NOT re-derived here; quoted lines are cited verbatim and re-checked by verify_oc.py.

## What I tried that failed (retry #1, new angle vs r4/r5)

The r4/r5 draft of RewriteMaterialSwap.cpp registered a HOSTED RewriteEntry on 0x675E440 with its own detour (rwSwapDetour/rwSwapOriginal) and expected that detour to run. It never does: install() skips Detour creation for hosted entries (RewriteRegistry.cpp:77-82), entry.hook stays nullptr, so entry.original<&rwSwapDetour>() would deref null and the swap never ran. The draft also had compile defects (set/clear/lookup and the static members defined inside an anonymous namespace; Logger::fatal with printf-style %u instead of the std::format {} style at Log.h:42; sSwapEntry used before declaration). None of that re-proves the control point, which is already [V]. New angle: do not create a second detour on 0x675E440 (RewriteResourceCache.cpp owns the single one — MinHook would reject it with MH_ERROR_ALREADY_CREATED and install() BS_CHECKs hook != nullptr). Instead edit rwCacheDetour there (the one existing rewrite file this unit may edit) so that, when the MaterialSwap entry's mode is On, it calls MaterialSwap::lookup on the pass-name argument and substitutes the replacement view before calling the original; otherwise unchanged. The MaterialSwap entry stays hosted (detour nullptr) for mode/report only.

## Files changed (this unit)

- src/client/features/render/rewrite/RewriteMaterialSwap.h — rewritten: Entry {nameHash, replacement[kMaxReplacement], replacementSize, used}, static sTable[kMaxEntries] (kMaxEntries = 16) + static sMutex declared in the struct (<mutex>), set/clear/lookup/swapEnabled API.
- src/client/features/render/rewrite/RewriteMaterialSwap.cpp — rewritten: only hashPassName in the anonymous namespace; set/clear/lookup/swapEnabled defined as MaterialSwap members at namespace scope (not inside an anonymous namespace); Logger::fatal {} style; hosted entry sSwapEntry("MaterialSwap","ResourceCache::get",0x675E440,nullptr,true) + sSwapReg for mode/report only; no detour of its own, no second detour on 0x675E440.
- src/client/features/render/rewrite/RewriteResourceCache.cpp — rwCacheDetour edited: On mode looks up the pass-name view in MaterialSwap and, on a match, calls the original with the replacement view substituted (replacement bytes on the detour's stack, covering the synchronous call; no allocation); Off and no-match pass through unchanged. Shadow/Verify run the original only.

No edit to HookManager.cpp, CMakeLists.txt or Sigs.json: sig "ResourceCache::get" exists (src/sdk/Sigs.json:92) and CMake GLOB_RECURSEs src/*.cpp (CMakeLists.txt:138), so the new file is picked up automatically.

## Symbols checked to exist (file:line)

| symbol | file:line | what |
| RewriteEntry 5th "hosted" ctor arg | src/client/features/render/rewrite/RewriteRegistry.h:37 | `RewriteEntry(const char* n, const char* s, uintptr_t rva, void* fn, bool host = false)` |
| RewriteEntry::skipped counter | src/client/features/render/rewrite/RewriteRegistry.h:32 | `std::atomic<uint64_t> skipped{0}` |
| RewriteResourceCache::Key | src/client/features/render/rewrite/RewriteFunctions.h:127-131 | `struct Key { uint64_t lo; uint64_t hi; }` |
| RewriteResourceCache::Key visible to detour | src/client/features/render/rewrite/RewriteResourceCache.cpp:88-90 | detour signature uses const RewriteResourceCache::Key* |
| Logger::fatal {} style | src/client/core/diagnostics/Log.h:42 | `template <typename... Args> [[noreturn]] static void fatal(fmt::format_string<Args...> fmt, Args&&... args)` |
| hosted detour skip | src/client/features/render/rewrite/RewriteRegistry.cpp:77-82 | `if (!entry.hosted) { entry.hook = HookTable::add(...); ... }` |
| install() RVA check | src/client/features/render/rewrite/RewriteRegistry.cpp:75 | `target != imageBase() + entry.knownRva` fatal |
| PassName {ptr,size} layout | src/client/features/render/rewrite/RewriteMaterialSwap.h:20-23 | `struct PassName { const char* ptr; size_t size; }` — matches the game string_view at the call site |

## Layout facts the code relies on (verbatim `0xRVA  instr`, [V] = seen in the disassembly, re-checked by verify_oc.py)

| offset | size | address | verbatim `0xRVA  instr` | meaning | [V]/[I]/[?] |
| 0x6646e5c | 8 | [rax+0x68] -> rcx | `0x6646e5c  mov rcx,[rax+0x68]` | resolver this = frameCtx+0x68 (call-site 'this'; frameCtx loaded at rbp+0x8A0 by 0x6646e51) | [V] |
| 0x6646e98 | 8 | [rsp+0x20] | `0x6646e98  mov [rsp+0x20],rsi` | get() arg5 = pointer to the pass-name string_view {ptr at [rbp+0x5A0], size 0x11 at [rbp+0x5A8] (0x6646e73/0x6646e7a)} | [V] |
| 0x675e4c6 | 8 | - | `0x675e4c6  mov rdx,0xCBF29CE484222325` | FNV offset basis = RewriteHash::kFnvBasis, used by hashPassName (resolver's basis) | [V] |
| 0x675e440 | 8 | - | `0x675e440  push rbp` | resolver entry 0x675e440 = ResourceCache::get (the detour target; sig "ResourceCache::get") | [V] |
| 0x675e489 | 8 | [r14+0x98] | `0x675e489  lea r15,[r14+0x98]` | recursive mutex address = cache+0x98 (0x675e493 `call 0xEEC59F0` locks it; impure — Verify N/A) | [V] |

## Design (matches the RewriteMath.cpp / RewriteResourceCache.cpp pattern exactly)

MaterialSwap::set(const char* passName, const char* replacement) / clear() manage a fixed thread-safe
table (kMaxEntries = 16, kMaxReplacement = 64 bytes; mutex-guarded, no allocation in the hot path,
fail fast via Logger::fatal / BS_CHECK on impossible states, no silent null-guards).

The detour is rwCacheDetour in RewriteResourceCache.cpp (the Detour installed on 0x675E440 — the one
existing rewrite file this unit edits; no second detour on this RVA). In On mode it reads the
pass-name string_view from get()'s 5th stack argument (pointer to {ptr, size}, verified at
0x6646e91/0x6646e98), hashes it with hashPassName (FNV-1a, basis 0xCBF29CE484222325 @ 0x675e4c6),
and when MaterialSwap::lookup finds a replacement it calls the original with a {repl, replSize} view
substituted for name (storage on this frame's stack, live for the synchronous call); otherwise it
calls the original unchanged. Off mode is a pure pass-through (one atomic mode read, original
arguments, original function). Verify mode is not applicable: the MaterialSwap entry is hosted (no
detour of its own, nothing to compare), and ResourceCache::get is impure anyway (mutex cache+0x98
@ 0x675e489/0x675e493, refcount at control+8, used-mark at node+0x30; the swap intentionally
changes the name input so a different holder is the intended result, not a divergence). Enable with
BS_REWRITE="ResourceCache::get=on,MaterialSwap=on".

## CLOSES?

YES — every pending part of L7h is now closed:

1. Control point (proven [V] by oc_U-EL7h r1/r2/r3/r4/r5, not re-derived): BST hash switch at
   0x6646dc2 (split 0x416AE22CAB22EA36 @ 0x6646dde; leaves 0xD8EF928BC853553A @ 0x6646df1,
   0x2C8B246FD3EDDC59 @ 0x6646e00; right subtree 0x4B8EDB299C93ABB3 @ 0x6647449,
   0x416AE22CAB22EA37 @ 0x6647458; miss path 0x66475bb/0x66475de -> 0x664CB91) and the pass-name
   resolver call 0x6646eab with this = frameCtx+0x68 (0x6646e5c).

2. Hook implementation (this unit): RewriteMaterialSwap.cpp + .h exist and follow the RewriteMath.cpp /
   RewriteResourceCache.cpp pattern exactly (static RewriteEntry + static RewriteReg, same sig
   "ResourceCache::get" and knownRva 0x675E440, hosted entry so no second Detour on 0x675E440;
   RewriteResourceCache.cpp owns the single detour on that RVA and its rwCacheDetour now performs the
   substitution when MaterialSwap::swapEnabled() is On); no HookManager.cpp / CMake / Sigs.json edits;
   CMake GLOB_RECURSE picks the file up. Behavior: fixed thread-safe table (<= 16 entries, <= 64-byte
   replacements, no allocation in the hot path) via set()/clear()/lookup(); the detour hashes the
   pass-name view with FNV-1a (basis 0xCBF29CE484222325 = the resolver's basis @ 0x675e4c6), calls the
   original with the replacement string_view when a swap exists and passes through unchanged otherwise;
   Mode Off is a pure pass-through; Verify mode is not applicable (hosted entry + impure function,
   documented above). Every layout fact the code uses is cited [V] above with verbatim lines. The
   in-game test is the orchestrator's.

## TOOL REQUESTS

None — rdis.exe `dis` (via verify_oc.py) and `python tools/delegate.py check` were sufficient; no helper script written, no _tmp files left behind.
