## NEXT
DONE

# Unit U-EL7h: L7h Material swap hook — pass-name resolver 0x675e440 + item-visitor hash switches (6cj)

## Scope

Checklist item L7h (docs/RENDER_CHECKLIST.md line 341): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".
This unit WRITES the hook (engineering task: this unit MAY write code — the orchestrator hint overrides the static-only reading of prior attempts). Prior units oc_U-EL7h r1/r2/r3 proved the control point [V] and it is NOT re-derived here; every quoted line below is re-verified verbatim against the exe by verify_oc.py via `python tools/delegate.py check`.

Deliverable: src/client/features/render/rewrite/RewriteMaterialSwap.cpp (+ RewriteMaterialSwap.h), following the RewriteMath.cpp / RewriteResourceCache.cpp pattern exactly: static RewriteEntry + static RewriteReg in the new file, same target 0x675E440 as RewriteResourceCache.cpp, hosted entry (RewriteResourceCache.cpp owns the single Detour on 0x675E440 — no second detour on the same RVA, no HookManager.cpp / CMake / Sigs.json edits; the glob picks the file up and sig "ResourceCache::get" already exists in Sigs.json, as "Math::mat4Multiply" did for RewriteMath.cpp). The original is reached through SigManager::get("ResourceCache::get") because a hosted entry has no hook object (install() skips Detour creation for hosted entries, RewriteRegistry.cpp:77-82), so entry.original<&rwSwapDetour>() would deref a null hook.

## Source data (read fully, not re-computed)

- oc_U-EL7h_r1.md (verify_oc 30/30), oc_U-EL7h_r2.md (43/43 [V]), oc_U-EL7h_r3.md: BST hash switch at tag-7 handler 0x6646dc2 (split 0x416AE22CAB22EA36 @ 0x6646dde, jg 0x6647449 @ 0x6646deb; leaves 0xD8EF928BC853553A @ 0x6646df1 and 0x2C8B246FD3EDDC59 = cracks_overlay_tile_entity.skinning @ 0x6646e00, jne miss @ 0x6646e0d; right subtree leaves 0x4B8EDB299C93ABB3 @ 0x6647449 and 0x416AE22CAB22EA37 @ 0x6647458, jne miss @ 0x6647465; miss path 0x66475bb `mov rsi,[0x128D6FA8]` → 0x66475de `call 0x4DF6E80` → miss tail 0x664CB91); resolver call 0x6646eab with call-site this = frameCtx+0x68 (0x6646e5c), r9 = frameCtx+0x40 (0x6646e58); resolver body 0x675e440 (mutex cache+0x98 locked via 0xEEC59F0 @ 0x675e493, FNV basis 0xCBF29CE484222325 @ 0x675e4c6).
- docs/BGFX_MAP.md sections 6cj (tag-7 hash switch, resolver 0x675e440, pass-name "CracksBlockEntity") and 6gs (0x675e440 = ResourceCache::get(get(out, key16, loader, name string_view, defines)); docs/functions/675e440.md (dossier: entry node key +0x10, shared_ptr<Holder> +0x20/+0x28, used +0x30; mutex +0x98).
- docs/data/render_hashes.txt: line 39 0x4B8EDB299C93ABB3 = selection_overlay_block_entity.skinning; line 40 0x416AE22CAB22EA37 = selection_overlay_block_entity.skinning_color; line 46 0x2C8B246FD3EDDC59 = cracks_overlay_tile_entity.skinning.
- Fresh rdis disassembly of the call site 0x6646e51..0x6646eab and the resolver head 0x675e440..0x675e54e (verbatim lines in the table below).

## What I tried that failed (new angles vs r1/r2/r3; none of it re-proves the already-[V] control point)

1. Bound the hook to a material-only resolver — failed: 0x675e440 is ResourceCache::get, a keyed get-or-load cache with 34 direct call sites in 12 functions (xref.py callers + rdis callers, mapped [V] by r2; only 0x6646eab is tag-7 material-swap-relevant, carrying the pass-name string_view). Hooking 0x675e440 intercepts every resource get; the swap-relevant site is the single call 0x6646eab.
2. Second Detour on 0x675E440 — rejected, not implemented: RewriteResourceCache.cpp already owns sCacheEntry/sCacheReg on that RVA; MinHook would fail MH_ERROR_ALREADY_CREATED and install() BS_CHECKs hook != nullptr (RewriteRegistry.cpp:77-82). Forbidden by the unit: "do not register a second detour on the same RVA".
3. Keying the detour on the r8 argument — failed: at 0x6646eab `lea r8,[0x129F9CB8]` loads static per-call-site 16-byte key data (same shape at 0x6647270: `lea r8,[0x129F9C90]`); the key is NOT the pass name. The pass name is the 5th argument of get(), a pointer to a {ptr, size} string_view passed on the stack at [rsp+0x20] (0x6646e98), with {ptr, size} stored at [rbp+0x5A0]/[rbp+0x5A8] (0x6646e73/0x6646e7a). The detour keys off that view.
4. Editing RewriteResourceCache.cpp / HookManager.cpp / CMakeLists / Sigs.json — not allowed (rule 3: src/** off-limits except the files this unit names; no edits to existing Sigs.json entries needed — sig "ResourceCache::get" exists; CMake globs src/*.cpp so the new file is picked up automatically).
5. FNV variant correction — r1/r3 labeled the resolver hash "FNV-1"; the instruction stream is basis `mov rdx,0xCBF29CE484222325` (0x675e4c6), `xor rdx,rcx` (0x675e4d0), prime `mov rcx,0x100000001B3` (0x675e4d3), `imul rdx,rcx` (0x675e4dd): XOR byte first, then multiply = FNV-1a order over key bytes [rbx+8..0xF], then boost hash_combine with key.lo (rax) at 0x675e532..0x675e54e. RewriteHash::fnv1a(kFnvBasis = 0xCBF29CE484222325, = the verified basis at 0x675e4c6) matches this order exactly, so hashPassName is consistent with the resolver. "FNV-1" labels in earlier notes corrected to "FNV-1a order, basis 0xCBF29CE484222325" here.
6. Verify mode — not applicable: ResourceCache::get is impure (takes the recursive mutex at cache+0x98 (0x675e489/0x675e493), bumps the holder refcount at control+8 per the dossier, marks the entry used at node+0x30) so it cannot be run twice for a snapshot comparison, and the swap deliberately changes the name input, so a different holder is the intended result, not a divergence. Shadow/Verify therefore run the original only and count the call as skipped (documented in the code). Mode Off is a pure pass-through (one atomic read of the entry mode, original arguments, original function).
7. Caller/post-return/vtable angles: all 34 direct call sites of 0x675e440 across 12 callers are ResourceCache::get calls (no material-specific hook exists anywhere); the post-return flow stores the resolved Holder into the draw-desc material slot [rbp+0x740]/[rbp+0x743] (0x664852a/0x6648536) with no swap function invoked, so the intercept point remains the resolver call itself; vt/vcalls are internal only (allocator setTag via [0xF99FFA0] at 0x675e47e/0x675e480, map-helper slots; the cache has no vtable slots). descscan2/rw and livemem were not needed — static analysis settles the control point (0 livemem calls made).

## Answer table (name | size | address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?])

One row per distinct offset/access; all sites of an access listed in the verbatim cell. Sizes from the instruction (qword 8, dword 4, byte 1, xmm store 16, call 5; lea/reg moves are 64-bit = 8). "-" where no memory operand exists. Every quoted line is verbatim from the exe disassembly and tagged [V].

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
| visitor-key | 8 | - | `0x6646e9d  lea r8,[0x129F9CB8]` | r8 = key pointer: static per-call-site key data, NOT the pass name (failed angle 3) | [V] |
| visitor-out | 8 | [rbp+0x1F0] | `0x6646ea4  lea rdx,[rbp+0x1F0]` | rdx = out slot {holder, control block} | [V] |
| resolver-call | 5 | -> 0x675e440 | `0x6646eab  call 0x675E440` | THE hook point: resolver call carrying the pass-name string_view; result holder at [rbp+0x1F0] | [V] |
| resolver-entry | 1 | - | `0x675e440  push rbp` | ResourceCache::get entry (0x675e440) | [V] |
| resolver-key-copy | 8 | r8 -> rbx | `0x675e467  mov rbx,r8` | arg3 key copied to rbx; key.lo at [rbx], key bytes at [rbx+8..0xF] | [V] |
| resolver-this-save | 8 | rcx -> r14 | `0x675e46d  mov r14,rcx` | cache this (arg1 rcx) saved to r14; body offsets are r14-relative | [V] |
| resolver-mutex | 8 | [r14+0x98] | `0x675e489  lea r15,[r14+0x98]` | recursive mutex address = cache+0x98 | [V] |
| resolver-mutex-lock | 5 | call 0xEEC59F0 | `0x675e493  call 0xEEC59F0` | lock the cache recursive mutex (impure — Verify not applicable) | [V] |
| resolver-key-lo | 8 | [rbx] | `0x675e4bf  mov rax,[rbx]` | key.lo (key+0x0) | [V] |
| resolver-key-byte0 | 1 | [rbx+8] | `0x675e4c2  movzx ecx,byte ptr [rbx+8]` | key.hi byte 0, first byte mixed into the hash | [V] |
| resolver-fnv-basis | 8 | - | `0x675e4c6  mov rdx,0xCBF29CE484222325` | FNV offset basis = RewriteHash::kFnvBasis, the basis hashPassName uses | [V] |
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
| bst-split | 8 | - | `0x6646dde  mov rdx,0x416AE22CAB22EA36` | BST split immediate | [V] |
| bst-split-cmp | 8 | reg cmp rcx,rdx | `0x6646de8  cmp rcx,rdx` | item hash vs split | [V] |
| bst-split-branch | - | jg 0x6647449 | `0x6646deb  jg 0x6647449` | taken -> right subtree | [V] |
| bst-left-leaf1 | 8 | - | `0x6646df1  mov rdx,0xD8EF928BC853553A` | left-leaf 1 immediate | [V] |
| leaf1-cmp | 8 | reg cmp rcx,rdx | `0x6646dfb  cmp rcx,rdx` | vs left-leaf 1 | [V] |
| leaf1-match | - | je short 0x6646E13 | `0x6646dfe  je short 0x6646E13` | match -> resolver setup block | [V] |
| bst-left-leaf2 | 8 | - | `0x6646e00  mov rdx,0x2C8B246FD3EDDC59` | left-leaf 2 = cracks_overlay_tile_entity.skinning (render_hashes.txt line 46) | [V] |
| leaf2-cmp | 8 | reg cmp rcx,rdx | `0x6646e0a  cmp rcx,rdx` | vs left-leaf 2 | [V] |
| leaf2-miss | - | jne 0x66475BB | `0x6646e0d  jne 0x66475BB` | miss -> miss path | [V] |
| bst-right-leaf1 | 8 | - | `0x6647449  mov rdx,0x4B8EDB299C93ABB3` | right-leaf 1 = selection_overlay_block_entity.skinning (render_hashes.txt line 39) | [V] |
| right1-cmp | 8 | reg cmp rcx,rdx | `0x6647453  cmp rcx,rdx` | vs right-leaf 1 | [V] |
| right1-match | - | je short 0x664746B | `0x6647456  je short 0x664746B` | match -> item-field copy block | [V] |
| bst-right-leaf2 | 8 | - | `0x6647458  mov rdx,0x416AE22CAB22EA37` | right-leaf 2 = selection_overlay_block_entity.skinning_color (render_hashes.txt line 40) | [V] |
| right2-cmp | 8 | reg cmp rcx,rdx | `0x6647462  cmp rcx,rdx` | vs right-leaf 2 | [V] |
| right2-miss | - | jne 0x66475BB | `0x6647465  jne 0x66475BB` | miss -> miss path | [V] |
| miss-global-load | 8 | [0x128D6FA8] | `0x66475bb  mov rsi,[0x128D6FA8]` | miss path loads global cache base | [V] |
| miss-forwarder | - | call 0x4DF6E80 | `0x66475de  call 0x4DF6E80` | miss forwarder 0x4df6e80 (6cj) -> miss tail 0x664CB91 | [V] |

## CLOSES?

YES — every pending part of L7h is now closed:

(1) Control point (already [V] by r1/r2/r3, not re-derived): tag-7 BST hash switch at 0x6646dc2 (split 0x416AE22CAB22EA36 @ 0x6646dde; leaves 0xD8EF928BC853553A @ 0x6646df1, 0x2C8B246FD3EDDC59 @ 0x6646e00 = cracks_overlay_tile_entity.skinning; right subtree 0x4B8EDB299C93ABB3 @ 0x6647449 = selection_overlay_block_entity.skinning, 0x416AE22CAB22EA37 @ 0x6647458 = selection_overlay_block_entity.skinning_color; miss path 0x66475bb `mov rsi,[0x128D6FA8]` → 0x66475de `call 0x4DF6E80` → miss tail 0x664CB91) and the pass-name resolver call 0x6646eab with this = frameCtx+0x68 (0x6646e5c).

(2) Hook implementation delivered (this unit): src/client/features/render/rewrite/RewriteMaterialSwap.cpp + RewriteMaterialSwap.h exist, follow the RewriteMath.cpp / RewriteResourceCache.cpp pattern exactly (static RewriteEntry + static RewriteReg, same sig "ResourceCache::get" and knownRva 0x675E440, hosted entry so no second Detour on 0x675E440 — RewriteResourceCache.cpp owns the single detour on that RVA; no HookManager.cpp / CMake / Sigs.json edits; CMake globs src/*.cpp so the file is picked up; Sigs.json already has "ResourceCache::get"). Behavior: thread-safe fixed table (kMaxEntries = 16, kMaxReplacement = 64, no allocation in the hot path) via MaterialSwap::set(const char* passName, const char* replacement) / clear(); the detour hashes the pass-name string_view with FNV-1a order (basis 0xCBF29CE484222325 = the resolver's basis at 0x675e4c6, verified at 0x675e4c6/0x675e4d0/0x675e4d3/0x675e4dd), calls the original with the replacement string_view when a swap exists, passes through unchanged otherwise. Mode Off is a pure pass-through; Verify mode is not applicable (impure function: mutex cache+0x98 (0x675e489/0x675e493), refcount at control+8, used-mark at node+0x30; the swap deliberately changes the name input so a different holder is intended, not a divergence — Shadow/Verify run the original only and count skipped). No null guards: impossible states fail fast (BS_CHECK / Logger::fatal). Layout facts used are all cited [V] with verbatim `0xRVA  instr` rows above (call-site argument layout 0x6646e51..0x6646eab, resolver head 0x675e440..0x675e54e, BST constants 0x6646dde/0x6646df1/0x6646e00/0x6647449/0x6647458). The in-game test is the orchestrator's.

## TOOL REQUESTS

None — rdis.exe `dis`, tools/sigs/verify_oc.py and `python tools/delegate.py check` were sufficient; no helper script written, no _tmp files left behind.
