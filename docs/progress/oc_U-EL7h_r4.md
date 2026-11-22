## NEXT
DONE

# Unit U-EL7h: L7h Material swap hook — pass-name resolver 0x675e440 + item-visitor hash switches (6cj)

## Scope

Checklist item L7h (docs/RENDER_CHECKLIST.md line 341): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".
This unit WRITES the hook (engineering task: this unit MAY write code — the orchestrator hint overrides the static-only reading of prior attempts). The static control point was already proven [V] by oc_U-EL7h r1/r2/r3 (verify_oc 30/30, r2 review 43/43) and is NOT re-derived here; every quoted line below is re-verified verbatim against the exe by verify_oc.py via `python tools/delegate.py check`.
Deliverable: src/client/features/render/rewrite/RewriteMaterialSwap.cpp (+ RewriteMaterialSwap.h), following the RewriteMath.cpp / RewriteResourceCache.cpp pattern exactly: static RewriteEntry + static RewriteReg in the new file, no edit to HookManager.cpp, CMake or Sigs.json (the glob picks the file up; the sig "ResourceCache::get" already exists in Sigs.json, as "Math::mat4Multiply" did for RewriteMath.cpp).
Same target 0x675e440 as RewriteResourceCache.cpp: that file already owns the single Detour on 0x675E440, so this file registers a HOSTED entry — no second detour on the same RVA (see "What I tried that failed").

## Source data (read fully, not re-computed)

- oc_U-EL7h_r1.md, oc_U-EL7h_r2.md, oc_U-EL7h_r3.md: control point [V] — BST consts 0x6646dde/0x6646df1/0x6646e00/0x6647449/0x6647458, resolver call 0x6646eab with this=frameCtx+0x68 (0x6646e5c), resolver 0x675e440 body (mutex cache+0x98, FNV-1 basis 0xCBF29CE484222325), all 34 direct call sites of 0x675e440 mapped.
- docs/BGFX_MAP.md: section 6cj (tag-7 handler 0x6646dc2, BST switch over the material-name hash, resolver 0x675e440, pass-name "CracksBlockEntity" at 0x6646e6c) and section 6gs (0x675e440 = ResourceCache::get(get(out, key16, loader, name, defines)), mutex cache+0x98, FNV-1 basis 0xCBF29CE484222325).
- docs/functions/675e440.md: dossier — signature `get(ResourceCache* this rcx, shared_ptr<Holder>* out rdx, const Key* key r8 [16 bytes], Loader* loader r9, const string_view* name [5th stack arg], const Span<Define>* defines [6th stack arg])`; entry node key +0x10, shared_ptr<Holder> +0x20/+0x28, u8 used +0x30; mutex +0x98, owner count +0xE4.
- Fresh rdis reads of the call site 0x6646e51..0x6646eab and the resolver head 0x675e440..0x675e4d3 (verbatim lines in the table below).

## What I tried that failed (new angles vs r1/r2/r3)

1. Keying the swap on the r8 argument — failed: at 0x6646eab `lea r8,[0x129F9CB8]` loads static per-call-site 16-byte key data (same shape at the other sampled call site 0x6647270: `lea r8,[0x129F9C90]`); the key is NOT the pass name. The pass name is the string view {ptr at [rbp+0x5A0], size 0x11 at [rbp+0x5A8]} passed as a pointer on the stack at [rsp+0x20] (0x6646e98) — that is the per-item material identity (6cj: [payload+0x140]->+0x10 is the material-name hash). The detour therefore keys off the pass-name view, hashed with FNV-1 basis 0xCBF29CE484222325 (0x675e4c6) — the resolver's own basis.
2. A second non-hosted RewriteEntry + Detour at 0x675E440 — rejected, not implemented: RewriteResourceCache.cpp already owns the single Detour on 0x675E440 (sCacheEntry/sCacheReg); MinHook would reject a second hook on the same target (MH_ERROR_ALREADY_CREATED) and install() BS_CHECKs hook != nullptr (RewriteRegistry.cpp:77-82). Forbidden by the unit: "do not register a second detour on the same RVA".
3. Editing RewriteResourceCache.cpp to extend sCacheEntry — not allowed: src/** is not a path this unit may create/edit (only RewriteMaterialSwap.cpp/.h).
4. A hosted entry calling e.original<&rwSwapDetour>() — impossible: hosted entries skip Detour creation (RewriteRegistry.cpp:77-82), so entry.hook is nullptr and getOriginal() would deref null. The original is therefore called through SigManager::get("ResourceCache::get") — the same address install() resolves and checks against knownRva 0x675E440.
5. Verify mode — not applicable: ResourceCache::get is impure (takes the recursive mutex at cache+0x98 (0x675e489/0x675e493), bumps the holder refcount at control+8 (0x675e5d3), marks the entry used at node+0x30 (0x675e649)) so it cannot be run twice for a snapshot comparison, and the swap deliberately changes the name input, so a different holder is the intended result, not a divergence. Shadow/Verify run the original only and count the call as skipped (documented in the code).

## Answer table (name | size | address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?])

One row per distinct offset/access; all sites of an access are listed in the verbatim cell. Sizes from the instruction (qword 8, dword 4, byte 1, xmm store 16, call 5). "-" where no memory operand exists.

| name | size | address | verbatim `0xRVA  instr` | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| visitor-ctx | 8 | [rbp+0x8A0] | `0x6646e51  mov rax,[rbp+0x8A0]` | frameCtx/visitor context held at rbp+0x8A0; source of the cache and loader arguments | [V] |
| visitor-loader | 8 | [rax+0x40] | `0x6646e58  mov r9,[rax+0x40]` | r9 = loader argument = frameCtx+0x40 | [V] |
| visitor-this | 8 | [rax+0x68] | `0x6646e5c  mov rcx,[rax+0x68]` | rcx = cache this = frameCtx+0x68 (call-site 'this' provenance) | [V] |
| visitor-defines-zero | 16 | [rbp+0x220] | `0x6646e60  pxor xmm0,xmm0`<br/>`0x6646e64  movdqa [rbp+0x220],xmm0` | defines span zeroed (16 bytes) before being passed on the stack | [V] |
| visitor-name-ptr | 8 | [rbp+0x5A0] | `0x6646e6c  lea rax,[0xF515E74]`<br/>`0x6646e73  mov [rbp+0x5A0],rax` | pass-name pointer = "CracksBlockEntity" (data 0xF515E74) | [V] |
| visitor-name-size | 8 | [rbp+0x5A8] | `0x6646e7a  mov qword ptr [rbp+0x5A8],0x11` | pass-name size = 0x11 | [V] |
| visitor-name-view-arg | 8 | [rsp+0x20] | `0x6646e91  lea rsi,[rbp+0x5A0]`<br/>`0x6646e98  mov [rsp+0x20],rsi` | stack arg 5 = pointer to string_view {ptr, size} at [rbp+0x5A0] | [V] |
| visitor-defines-arg | 8 | [rsp+0x28] | `0x6646e85  lea rax,[rbp+0x220]`<br/>`0x6646e8c  mov [rsp+0x28],rax` | stack arg 6 = pointer to defines span {0, 0} | [V] |
| visitor-key | 8 | - | `0x6646e9d  lea r8,[0x129F9CB8]` | r8 = key pointer: static per-call-site key data, NOT the pass name (see failed angle 1) | [V] |
| visitor-out | 8 | [rbp+0x1F0] | `0x6646ea4  lea rdx,[rbp+0x1F0]` | rdx = out slot {holder, control block} | [V] |
| resolver-call | 5 | -> 0x675e440 | `0x6646eab  call 0x675E440` | hook point: resolver call carrying the pass-name string_view; result holder at [rbp+0x1F0] | [V] |
| resolver-this-save | 8 | rcx -> r14 | `0x675e46d  mov r14,rcx` | cache this (arg1 rcx) saved to r14; body offsets are r14-relative | [V] |
| resolver-key-copy | 8 | r8 -> rbx | `0x675e467  mov rbx,r8` | arg3 key copied to rbx; key.lo at [rbx], key bytes at [rbx+8..0xF] | [V] |
| resolver-mutex | 8 | [r14+0x98] | `0x675e489  lea r15,[r14+0x98]` | recursive mutex address = cache+0x98 | [V] |
| resolver-mutex-lock | 5 | call 0xEEC59F0 | `0x675e493  call 0xEEC59F0` | lock the cache recursive mutex | [V] |
| resolver-key-lo | 8 | [rbx] | `0x675e4bf  mov rax,[rbx]` | key.lo (key+0x0) | [V] |
| resolver-key-byte0 | 1 | [rbx+8] | `0x675e4c2  movzx ecx,byte ptr [rbx+8]` | key.hi byte 0 fed into the FNV-1 64 hash | [V] |
| resolver-fnv-basis | 8 | - | `0x675e4c6  mov rdx,0xCBF29CE484222325` | FNV-1 64 offset basis — same basis used to hash pass names in this hook (0x675e4c6 = RewriteHash::kFnvBasis) | [V] |
| resolver-fnv-prime | 8 | - | `0x675e4d3  mov rcx,0x100000001B3` | FNV-1 64 prime; imul chain over key bytes follows | [V] |
| bst-split | 8 | - | `0x6646dde  mov rdx,0x416AE22CAB22EA36` | BST split immediate (6cj tag-7 switch) | [V] |
| bst-split-cmp | 8 | reg | `0x6646de8  cmp rcx,rdx` | item hash vs split | [V] |
| bst-split-branch | - | - | `0x6646deb  jg 0x6647449` | taken -> right subtree | [V] |
| bst-left-leaf1 | 8 | - | `0x6646df1  mov rdx,0xD8EF928BC853553A` | left-leaf 1 immediate | [V] |
| bst-left-leaf2 | 8 | - | `0x6646e00  mov rdx,0x2C8B246FD3EDDC59` | left-leaf 2 = cracks_overlay_tile_entity.skinning | [V] |
| bst-left-leaf2-branch | - | - | `0x6646e0d  jne 0x66475BB` | leaf 2 miss -> miss path | [V] |
| bst-right-leaf1 | 8 | - | `0x6647449  mov rdx,0x4B8EDB299C93ABB3` | right-leaf 1 = selection_overlay_block_entity.skinning | [V] |
| bst-right-leaf2 | 8 | - | `0x6647458  mov rdx,0x416AE22CAB22EA37` | right-leaf 2 = selection_overlay_block_entity.skinning_color | [V] |
| bst-right-leaf2-branch | - | - | `0x6647465  jne 0x66475BB` | right leaf 2 miss -> miss path | [V] |

## CLOSES?

YES — the single pending part of the item line ("only the hook implementation itself remains") is now delivered: src/client/features/render/rewrite/RewriteMaterialSwap.cpp (+ RewriteMaterialSwap.h) exists, follows the RewriteMath.cpp / RewriteResourceCache.cpp pattern exactly (static RewriteEntry + static RewriteReg, same sig "ResourceCache::get" and knownRva 0x675E440, no second Detour on 0x675E440 because the entry is hosted — RewriteResourceCache.cpp owns the single detour on that RVA, no HookManager.cpp / CMake / Sigs.json edits), and every layout fact it uses (call-site argument layout at 0x6646e51..0x6646eab, resolver head at 0x675e440..0x675e4d3, BST constants 0x6646dde/0x6646df1/0x6646e00/0x6647449/0x6647458) is cited [V] with verbatim `0xRVA  instr` rows above. Behavior: thread-safe fixed table (<= 16 entries, no allocation in the hot path) via MaterialSwap::set(const char* passName, const char* replacement) / clear(); the detour hashes the pass-name view (FNV-1, basis 0xCBF29CE484222325, the resolver's basis at 0x675e4c6), calls the original with the replacement string_view when a swap exists, passes through unchanged otherwise; Mode Off is a pure pass-through; Verify mode is not applicable (impure function: mutex cache+0x98, refcount at control+8, used-mark at node+0x30; the swap deliberately changes the name input, so a different holder is the intended result, not a divergence — Shadow/Verify run the original only and count skipped). The in-game test is the orchestrator's.

## TOOL REQUESTS

None — rdis.exe `dis`, tools/sigs/verify_oc.py and `python tools/delegate.py check` were sufficient; no helper script written, no _tmp files left behind.
