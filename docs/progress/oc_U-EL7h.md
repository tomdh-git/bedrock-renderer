## NEXT
DONE

# Unit U-EL7h: L7h Material swap hook — pass-name resolver 0x675e440 + item-visitor hash switches (6cj)

## Scope

Checklist item L7h (docs/RENDER_CHECKLIST.md line 341): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".
This unit WRITES the hook (engineering task — the orchestrator hint overrides the static-only reading of prior attempts oc_U-EL7h r1/r2/r3/r4/r5). The static control point was already proven [V] by those notes (verify_oc 30/30, r2 review 43/43) and is NOT re-derived here; quoted lines are cited verbatim and re-checked by verify_oc.py via `python tools/delegate.py check`.

## What I tried that failed (retry #1, new angle vs r4/r5)

The r4/r5 draft of RewriteMaterialSwap.cpp registered a HOSTED RewriteEntry on 0x675E440 with its own detour (rwSwapDetour/rwSwapOriginal) and expected that detour to run. It never does: install() skips Detour creation for hosted entries (RewriteRegistry.cpp:77-82), entry.hook stays nullptr, so entry.original<&rwSwapDetour>() would deref null and the swap never ran. The draft also had compile defects (set/clear/lookup and the static members defined inside an anonymous namespace; Logger::fatal with printf-style %u instead of the std::format {} style at Log.h:42; sSwapEntry used before declaration). None of that re-proves the control point, which is already [V]. New angle: do not create a second detour on 0x675E440 (RewriteResourceCache.cpp owns the single one — MinHook would reject it with MH_ERROR_ALREADY_CREATED and install() BS_CHECKs hook != nullptr). Instead edit rwCacheDetour there (the one existing rewrite file this unit may edit) so that, when the MaterialSwap entry's mode is On, it calls MaterialSwap::lookup on the pass-name argument and substitutes the replacement view before calling the original; otherwise unchanged. The MaterialSwap entry stays hosted (detour nullptr) for mode/report only.

## Files changed (this unit)

- src/client/features/render/rewrite/RewriteMaterialSwap.h — rewritten: Entry {nameHash, replacement[kMaxReplacement], replacementSize, used}, static sTable[kMaxEntries] (kMaxEntries = 16) + static sMutex declared in the struct (<mutex>), set/clear/lookup/swapEnabled API; #include <mutex> + #include <cstddef> added.
- src/client/features/render/rewrite/RewriteMaterialSwap.cpp — rewritten: only hashPassName at file scope (static internal linkage); set/clear/lookup/swapEnabled defined as MaterialSwap members at namespace scope (not inside an anonymous namespace); Logger::fatal {} style; hosted entry sSwapEntry("MaterialSwap","ResourceCache::get",0x675E440,nullptr,true) + sSwapReg for mode/report only; no detour of its own, no second detour on 0x675E440.
- src/client/features/render/rewrite/RewriteResourceCache.cpp — rwCacheDetour edited: On mode looks up the pass-name view in MaterialSwap and, on a match, calls the original with the replacement view substituted (replacement bytes on the detour's stack, covering the synchronous call; no allocation); Off and no-match pass through unchanged. Shadow/Verify run the original only.

No edit to HookManager.cpp, CMakeLists.txt or Sigs.json: sig "ResourceCache::get" exists (src/sdk/Sigs.json:92) and CMake GLOB_RECURSEs src/*.cpp (CMakeLists.txt:138), so the new file is picked up automatically.

## Symbols checked to exist (file:line)

| symbol | file:line | what |
|---|---|---|
| RewriteEntry 5th "hosted" ctor arg | src/client/features/render/rewrite/RewriteRegistry.h:37 | `RewriteEntry(const char* n, const char* s, uintptr_t rva, void* fn, bool host = false)` |
| RewriteEntry::skipped counter | src/client/features/render/rewrite/RewriteRegistry.h:32 | `std::atomic<uint64_t> skipped{0}` |
| hosted detour skip | src/client/features/render/rewrite/RewriteRegistry.cpp:77-82 | `if (!entry.hosted) { entry.hook = HookTable::add(...); ... }` |
| install() RVA check | src/client/features/render/rewrite/RewriteRegistry.cpp:75 | `target != imageBase() + entry.knownRva` fatal |
| RewriteResourceCache::Key | src/client/features/render/rewrite/RewriteFunctions.h:128-131 | `struct Key { uint64_t lo; uint64_t hi; }` |
| RewriteHash::kFnvBasis | src/client/features/render/rewrite/RewriteFunctions.h:10 | `static constexpr uint64_t kFnvBasis = 0xCBF29CE484222325ull;` |
| RewriteHash::fnv1a | src/client/features/render/rewrite/RewriteFunctions.h:13-17 | FNV-1a over bytes with basis kFnvBasis |
| Logger::fatal {} style | src/client/core/diagnostics/Log.h:42 | `template <typename... Args> [[noreturn]] static void fatal(fmt::format_string<Args...> fmt, Args&&... args)` |
| BS_CHECK | src/client/core/diagnostics/Log.h:56 | `do { if (!(cond)) Logger::fatal("{}:{} check failed: {}", ...); } while (0)` |
| Sigs.json sig ResourceCache::get | src/sdk/Sigs.json:92 | sig "ResourceCache::get", rva 0x675E440 |

## Layout facts the code relies on (verbatim `0xRVA  instr`, [V] = seen in the disassembly, re-checked by verify_oc.py)

| name | size | address | verbatim `0xRVA  instr` | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| visitor-ctx | 8 | [rbp+0x8A0] | `0x6646e51  mov rax,[rbp+0x8A0]` | frameCtx/visitor context held at rbp+0x8A0; source of the cache and loader arguments | [V] |
| visitor-loader | 8 | [rax+0x40] -> r9 | `0x6646e58  mov r9,[rax+0x40]` | r9 = loader argument = frameCtx+0x40 | [V] |
| visitor-cache-this | 8 | [rax+0x68] -> rcx | `0x6646e5c  mov rcx,[rax+0x68]` | rcx = cache this = frameCtx+0x68 (call-site 'this' provenance) | [V] |
| visitor-defines-zero | 16 | xmm0 -> [rbp+0x220] | `0x6646e60  pxor xmm0,xmm0`<br>`0x6646e64  movdqa [rbp+0x220],xmm0` | defines span zeroed (16 bytes) before being passed on the stack | [V] |
| visitor-name-ptr | 8 | [rbp+0x5A0] | `0x6646e6c  lea rax,[0xF515E74]`<br>`0x6646e73  mov [rbp+0x5A0],rax` | pass-name pointer = "CracksBlockEntity" (data 0xF515E74) | [V] |
| visitor-name-size | 8 | [rbp+0x5A8] | `0x6646e7a  mov qword ptr [rbp+0x5A8],0x11` | pass-name size = 0x11 | [V] |
| visitor-defines-arg | 8 | [rsp+0x28] | `0x6646e85  lea rax,[rbp+0x220]`<br>`0x6646e8c  mov [rsp+0x28],rax` | stack arg 6 = pointer to defines span {0, 0} | [V] |
| visitor-name-view-arg | 8 | [rsp+0x20] | `0x6646e91  lea rsi,[rbp+0x5A0]`<br>`0x6646e98  mov [rsp+0x20],rsi` | stack arg 5 = pointer to string_view {ptr = [rbp+0x5A0], size = 0x11} — the per-item material identity | [V] |
| visitor-key | 8 | - | `0x6646e9d  lea r8,[0x129F9CB8]` | r8 = key pointer: static per-call-site key data, NOT the pass name | [V] |
| visitor-out | 8 | [rbp+0x1F0] | `0x6646ea4  lea rdx,[rbp+0x1F0]` | rdx = out slot {holder, control block} | [V] |
| resolver-call | 5 | -> 0x675e440 | `0x6646eab  call 0x675E440` | THE hook point: resolver call carrying the pass-name string_view; result holder at [rbp+0x1F0] | [V] |
| resolver-entry | 1 | - | `0x675e440  push rbp` | ResourceCache::get entry (0x675e440), the detour target | [V] |
| resolver-key-copy | 8 | r8 -> rbx | `0x675e467  mov rbx,r8` | arg3 key copied to rbx; key.lo at [rbx], key bytes at [rbx+8..0xF] | [V] |
| resolver-this-save | 8 | rcx -> r14 | `0x675e46d  mov r14,rcx` | cache this (arg1 rcx) saved to r14; body offsets are r14-relative | [V] |
| resolver-mutex | 8 | [r14+0x98] | `0x675e489  lea r15,[r14+0x98]` | recursive mutex address = cache+0x98 | [V] |
| resolver-mutex-lock | 5 | call 0xEEC59F0 | `0x675e493  call 0xEEC59F0` | lock the cache recursive mutex (impure — Verify not applicable) | [V] |
| resolver-key-lo | 8 | [rbx] | `0x675e4bf  mov rax,[rbx]` | key.lo (key+0x0) | [V] |
| resolver-key-byte0 | 1 | [rbx+8] | `0x675e4c2  movzx ecx,byte ptr [rbx+8]` | key.hi byte 0, first byte mixed into the hash | [V] |
| resolver-fnv-basis | 8 | - | `0x675e4c6  mov rdx,0xCBF29CE484222325` | FNV offset basis = RewriteHash::kFnvBasis, used by hashPassName (resolver's basis) | [V] |
| resolver-fnv-xor | 4 | reg xor rdx,rcx | `0x675e4d0  xor rdx,rcx` | basis XOR first byte — FNV-1a order (xor then multiply), confirmed vs the instruction stream | [V] |
| resolver-fnv-prime | 8 | - | `0x675e4d3  mov rcx,0x100000001B3` | FNV prime | [V] |
| resolver-fnv-imul | 4 | reg imul rdx,rcx | `0x675e4dd  imul rdx,rcx` | (basis ^ byte) * prime over key bytes [rbx+8..0xF] | [V] |
| resolver-fnv-combine | 8 | rax -> rcx | `0x675e532  mov rcx,rax`<br>`0x675e535  shl rcx,6`<br>`0x675e539  mov r9,rax`<br>`0x675e53c  shr r9,2`<br>`0x675e540  add r9,rcx`<br>`0x675e543  mov edx,0x9E3779B9`<br>`0x675e548  add rdx,r9`<br>`0x675e54b  add rdx,r8`<br>`0x675e54e  xor rdx,rax` | boost hash_combine of the running hash with key.lo (rax): h ^= (lo + 0x9E3779B9 + (h<<6) + (h>>2)) | [V] |
| bst-entry | 8 | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]` | tag-7 handler 0x6646dc2 (6cj): payload+0x140 -> material-name HashedString node ptr | [V] |
| bst-node-addr | 8 | lea [rax+0x10] | `0x6646dc9  lea rcx,[rax+0x10]` | node+0x10 (hash field) address | [V] |
| bst-node-null | - | test rax,rax | `0x6646dcd  test rax,rax` | node null -> default path | [V] |
| bst-default-node | 8 | lea [0x1232E708] | `0x6646dd0  lea rdx,[0x1232E708]` | static default node data address | [V] |
| bst-cmov | - | cmovne rdx,rcx | `0x6646dd7  cmovne rdx,rcx` | select node when non-null | [V] |
| bst-hash-load | 8 | [rdx] | `0x6646ddb  mov rcx,[rdx]` | u64 material-name hash from node+0x10 | [V] |
| bst-split | 8 | - | `0x6646dde  mov rdx,0x416AE22CAB22EA36` | BST split immediate (6cj tag-7 switch) | [V] |
| bst-split-cmp | 8 | reg cmp rcx,rdx | `0x6646de8  cmp rcx,rdx` | item hash vs split | [V] |
| bst-split-branch | - | jg 0x6647449 | `0x6646deb  jg 0x6647449` | taken -> right subtree | [V] |
| bst-left-leaf1 | 8 | - | `0x6646df1  mov rdx,0xD8EF928BC853553A` | left-leaf 1 immediate | [V] |
| leaf1-cmp | 8 | reg cmp rcx,rdx | `0x6646dfb  cmp rcx,rdx` | vs left-leaf 1 | [V] |
| leaf1-match | - | je short 0x6646E13 | `0x6646dfe  je short 0x6646E13` | match -> resolver setup block | [V] |
| bst-left-leaf2 | 8 | - | `0x6646e00  mov rdx,0x2C8B246FD3EDDC59` | left-leaf 2 = cracks_overlay_tile_entity.skinning | [V] |
| leaf2-cmp | 8 | reg cmp rcx,rdx | `0x6646e0a  cmp rcx,rdx` | vs left-leaf 2 | [V] |
| leaf2-miss | - | jne 0x66475BB | `0x6646e0d  jne 0x66475BB` | miss -> miss path | [V] |
| bst-right-leaf1 | 8 | - | `0x6647449  mov rdx,0x4B8EDB299C93ABB3` | right-leaf 1 = selection_overlay_block_entity.skinning | [V] |
| right1-cmp | 8 | reg cmp rcx,rdx | `0x6647453  cmp rcx,rdx` | vs right-leaf 1 | [V] |
| right1-match | - | je short 0x664746B | `0x6647456  je short 0x664746B` | match -> item-field copy block | [V] |
| bst-right-leaf2 | 8 | - | `0x6647458  mov rdx,0x416AE22CAB22EA37` | right-leaf 2 = selection_overlay_block_entity.skinning_color | [V] |
| right2-cmp | 8 | reg cmp rcx,rdx | `0x6647462  cmp rcx,rdx` | vs right-leaf 2 | [V] |
| right2-miss | - | jne 0x66475BB | `0x6647465  jne 0x66475BB` | miss -> miss path | [V] |
| miss-global-load | 8 | [0x128D6FA8] | `0x66475bb  mov rsi,[0x128D6FA8]` | miss path loads global cache base | [V] |
| miss-forwarder | - | call 0x4DF6E80 | `0x66475de  call 0x4DF6E80` | miss forwarder 0x4df6e80 (6cj) -> miss tail 0x664CB91 | [V] |

## Design (matches the RewriteMath.cpp / RewriteResourceCache.cpp pattern exactly)

MaterialSwap::set(const char* passName, const char* replacement) / clear() manage a fixed thread-safe table (kMaxEntries = 16, kMaxReplacement = 64 bytes; mutex-guarded, no allocation in the hot path, fail fast via Logger::fatal / BS_CHECK on impossible states, no silent null-guards).

The detour is rwCacheDetour in RewriteResourceCache.cpp (the Detour installed on 0x675E440 — the one existing rewrite file this unit edits; no second detour on this RVA). In On mode it reads the pass-name string_view from get()'s 5th stack argument (pointer to {ptr, size}, verified at 0x6646e91/0x6646e98), hashes it with hashPassName (FNV-1a, basis 0xCBF29CE484222325 @ 0x675e4c6), and when MaterialSwap::lookup finds a replacement it calls the original with a {repl, replSize} view substituted for name (storage on this frame's stack, live for the synchronous call); otherwise it calls the original unchanged. Off mode is a pure pass-through (one atomic mode read, original arguments, original function). Verify mode is not applicable: the MaterialSwap entry is hosted (no detour of its own, nothing to compare), and ResourceCache::get is impure anyway (mutex cache+0x98 @ 0x675e489/0x675e493, refcount at control+8, used-mark at node+0x30; the swap intentionally changes the name input so a different holder is the intended result, not a divergence). Enable with BS_REWRITE="ResourceCache::get=on,MaterialSwap=on".

## Self-check results (r5 gates, run on the finished files)

- `grep -n "^namespace {" -A60 RewriteMaterialSwap.cpp | grep "MaterialSwap::"` -> EMPTY: no MaterialSwap members inside the anonymous namespace (only hashPassName lives at file scope; sTable/sMutex/set/clear/lookup/swapEnabled are at namespace scope).
- `grep -n "%u" RewriteMaterialSwap.cpp` -> EMPTY: no printf-style %u; Logger::fatal uses {} style.
- sSwapEntry declared at line 116, first used at line 119 (swapEnabled): declared before use. ✓
- `grep -n "MaterialSwap" RewriteResourceCache.cpp` shows line 130 `if (MaterialSwap::swapEnabled() ...)` and line 138 `MaterialSwap::lookup(...)`: the detour consults the table, so the swap runs. ✓

## CLOSES?

YES — every pending part of L7h is now closed:

1. Control point (proven [V] by oc_U-EL7h r1/r2/r3/r4/r5, not re-derived): tag-7 BST hash switch at 0x6646dc2 (split 0x416AE22CAB22EA36 @ 0x6646dde; leaves 0xD8EF928BC853553A @ 0x6646df1, 0x2C8B246FD3EDDC59 = cracks_overlay_tile_entity.skinning @ 0x6646e00; right subtree 0x4B8EDB299C93ABB3 @ 0x6647449 = selection_overlay_block_entity.skinning, 0x416AE22CAB22EA37 @ 0x6647458 = selection_overlay_block_entity.skinning_color; miss path 0x66475bb `mov rsi,[0x128D6FA8]` → 0x66475de `call 0x4DF6E80` → miss tail 0x664CB91) and the pass-name resolver call 0x6646eab with this = frameCtx+0x68 (0x6646e5c).

2. Hook implementation (this unit): RewriteMaterialSwap.cpp + .h exist and follow the RewriteMath.cpp / RewriteResourceCache.cpp pattern exactly (static RewriteEntry + static RewriteReg, same sig "ResourceCache::get" and knownRva 0x675E440, hosted entry so no second Detour on 0x675E440 — RewriteResourceCache.cpp owns the single detour on that RVA; no HookManager.cpp / CMake / Sigs.json edits; CMake globs src/*.cpp so the file is picked up; Sigs.json already has "ResourceCache::get"). Behavior: thread-safe fixed table (<= 16 entries, <= 64-byte replacements, no allocation in the hot path) via MaterialSwap::set(const char* passName, const char* replacement) / clear(); the detour hashes the pass-name string_view with FNV-1a order (basis 0xCBF29CE484222325 = the resolver's basis at 0x675e4c6, verified at 0x675e4c6/0x675e4d0/0x675e4d3/0x675e4dd), calls the original with the replacement string_view when a swap exists, passes through unchanged otherwise. Mode Off is a pure pass-through; Verify mode is not applicable (hosted entry + impure function, documented above). Every layout fact the code uses is cited [V] with verbatim `0xRVA  instr` rows above (call-site argument layout 0x6646e51..0x6646eab, resolver head 0x675e440..0x675e54e, BST constants 0x6646dde/0x6646df1/0x6646e00/0x6647449/0x6647458). The in-game test is the orchestrator's.

## TOOL REQUESTS

None — rdis.exe `dis` (via verify_oc.py), `python tools/delegate.py check` and the r5 grep gates were sufficient; no helper script written, no _tmp files left behind.
