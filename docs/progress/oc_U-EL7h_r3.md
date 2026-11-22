## NEXT
DONE

# Unit U-EL7h: L7h Material swap hook — pass-name resolver 0x675e440 + item-visitor hash switches (6cj)

## Scope

Checklist item L7h (docs/RENDER_CHECKLIST.md line 341): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".
This unit decodes the control point only. The hook itself is a runtime code change and is not written here (static-analysis-only unit; brief rules 1 and 3).
Earlier attempts: oc_U-EL7h_r1.md (verify_oc 30/30 — BST switch + resolver call with this=frameCtx+0x68) and oc_U-EL7h_r2.md (43/43 [V] — added all 34 direct call sites of 0x675e440, corrected cache+0xE4 semantics). Both ended with "not implemented" standing: only the hook implementation itself remains.
This retry attacks that single blocking fact from NEW angles: (a) callers of 0x675e440 (already mapped by r2, summarized below), (b) the flow after the resolver call 0x6646eab returns — what the item-visitor does with the resolved Holder (path/rw from the full listing rdis_fn_6646980_full.txt), (c) vt/vcalls of the resolver, (d) livemem (decided unnecessary, see below). Nothing that r1/r2 already proved [V] is re-derived; every quoted line is re-verified verbatim against the exe by verify_oc.py via `python tools/delegate.py check`.

## Source data (read fully, not re-computed)

- docs/BGFX_MAP.md: section 6cj (tag-7 handler 0x6646dc2, BST switch over the material-name hash, resolver 0x675e440), section 6m (item visitor 0x6646980, variant tags incl. tag 7 = block-entity crack/overlay draws with pass names "CracksBlockEntity"), section 6gs (0x675e440 = ResourceCache::get, keyed get-or-load cache, not material-specific).
- docs/functions/675e440.md: dossier of ResourceCache::get (0x4EC bytes, 305 instr; mutex +0x98 with owner count at +0xE4 = mutex+0x4C; Entry used byte at +0x30; loadResource 0xbcbf730; map helpers 0x567d280/0x567cf50/0x567d9f0).
- docs/data/render_hashes.txt: line 39 0x4B8EDB299C93ABB3 = selection_overlay_block_entity.skinning; line 40 0x416AE22CAB22EA37 = selection_overlay_block_entity.skinning_color; line 46 0x2C8B246FD3EDDC59 = cracks_overlay_tile_entity.skinning.
- docs/data/live_item_payloads_1.26.62.01.txt: tag-7 live capture — `[rdi+0x140]` = material-name HashedString node, node+0x10 = FNV-1 64 hash 0x0694BEA7E37055A4 = "ender_dragon.skinning" (confirms payload+0x140 -> +0x10 is the per-item material identity the tag-7 switch keys on).
- The full listing `rdis_fn_6646980_full.txt` (item group visitor 0x6646980, 0x9425 bytes) — every quoted instruction below is copied verbatim from it or from a fresh `rdis dis` run, and is verified by verify_oc.py against the exe.

## What I tried that failed (new angles)

1. Callers of 0x675e440 (r2 angle, re-confirmed): xref.py callers + rdis callers agree — 34 direct call sites in 12 functions (item/sky/UI/effect/editor group visitors, terrain builder x5, block-selection-overlay extractor x2, FlameBillboard, RTX frame builder). Every site is a verbatim `call 0x675E440`; 0x675e440 is ResourceCache::get, a keyed get-or-load cache used by every group visitor, NOT a material-specific resolver. The only tag-7 material-swap-relevant site is 0x6646eab (carries the pass-name string_view). This angle does not yield a material-specific hook — it confirms the hook point is the single resolver call itself.
2. Flow after the resolver return (this unit, path/rw from the listing): after `0x6646eab  call 0x675E440` the resolved Holder* at [rbp+0x1F0] is dereferenced (0x6646eb7), null- and requested-flag-checked (0x6646eba/0x6646ee8), refcount-touched via [0xF99FFA0] (0x6646ef9/0x6646f06/0x6646f35), the flow joins at 0x6647FF1, context slots are swapped (0x6648080-0x6648095), the map entry is marked used [rbx+0x30]=1 (0x6648339/0x664844b), and the resolved Holder is stored into the draw-desc material slot [rbp+0x740]/[rbp+0x743] (0x664852a/0x6648536/0x664853c), with a mat4 copied to [rbp+0x618] (0x664887a loop). No material-swap function is invoked anywhere on this path: the intercept point remains the resolver call 0x6646eab itself (or, equivalently, replacing the Holder result stored at desc [rbp+0x740]).
3. vt/vcalls: the resolver's indirect calls are internal only — allocator setTag(0x30) via the global slot [0xF99FFA0] (0x675e47e/0x675e480) and map-helper slots [obj+0x8]/[obj+0x10] (dossier). The cache object has no vtable slots of its own. No hook/vcall slot exists to intercept.
4. descscan2/rw: not required — the complete store/load map of the post-return flow is read directly from the full listing above; no hidden swap struct or callback slot appears.
5. livemem: not used. Static analysis settles the control point and the post-return flow; a live read of any object/pointer would not change the conclusion (the hook implementation simply does not exist in the exe). 0 livemem calls made.

## Answer table (name | size | address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?])

One row per distinct offset/access; all sites of an access listed in the verbatim cell. Sizes from the instruction (qword 8, dword 4, word 2, byte 1, movss 4, movq 8); "-" where no memory operand exists. Meanings are operand/string readings only; anything beyond is tagged [I]/[?] and argued in prose, not asserted.

| name | size | address | verbatim `0xRVA  instr` | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| sw-payload-load | 8 | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]` | tag-7 payload+0x140 -> material-name HashedString node ptr | [V] |
| sw-node-addr | 8 | lea [rax+0x10] | `0x6646dc9  lea rcx,[rax+0x10]` | node+0x10 (hash field) address | [V] |
| sw-node-null | - | test rax,rax | `0x6646dcd  test rax,rax` | node null -> default path | [V] |
| sw-default-node | 8 | lea [0x1232E708] | `0x6646dd0  lea rdx,[0x1232E708]` | static default node data address | [V] |
| sw-cmov | - | cmovne rdx,rcx | `0x6646dd7  cmovne rdx,rcx` | select node when non-null | [V] |
| sw-hash-load | 8 | [rdx] | `0x6646ddb  mov rcx,[rdx]` | u64 material-name hash from node+0x10 | [V] |
| bst-split | 8 | - | `0x6646dde  mov rdx,0x416AE22CAB22EA36` | BST split immediate | [V] |
| bst-split-cmp | 8 | reg cmp rcx,rdx | `0x6646de8  cmp rcx,rdx` | hash vs split | [V] |
| bst-right-br | - | jg 0x6647449 | `0x6646deb  jg 0x6647449` | `jg` takes the right subtree | [V] |
| bst-left-leaf1 | 8 | - | `0x6646df1  mov rdx,0xD8EF928BC853553A` | left-leaf 1 immediate | [V] |
| leaf1-cmp | 8 | reg cmp rcx,rdx | `0x6646dfb  cmp rcx,rdx` | vs left-leaf 1 | [V] |
| leaf1-match | - | je short 0x6646E13 | `0x6646dfe  je short 0x6646E13` | match -> resolver setup block | [V] |
| bst-left-leaf2 | 8 | - | `0x6646e00  mov rdx,0x2C8B246FD3EDDC59` | left-leaf 2 = cracks_overlay_tile_entity.skinning (render_hashes.txt line 46) | [V] |
| leaf2-cmp | 8 | reg cmp rcx,rdx | `0x6646e0a  cmp rcx,rdx` | vs left-leaf 2 | [V] |
| leaf2-miss | - | jne 0x66475BB | `0x6646e0d  jne 0x66475BB` | no match -> miss path | [V] |
| bst-right-leaf1 | 8 | - | `0x6647449  mov rdx,0x4B8EDB299C93ABB3` | right-leaf 1 = selection_overlay_block_entity.skinning (render_hashes.txt line 39) | [V] |
| right1-cmp | 8 | reg cmp rcx,rdx | `0x6647453  cmp rcx,rdx` | vs right-leaf 1 | [V] |
| right1-match | - | je short 0x664746B | `0x6647456  je short 0x664746B` | match -> item-field copy block | [V] |
| bst-right-leaf2 | 8 | - | `0x6647458  mov rdx,0x416AE22CAB22EA37` | right-leaf 2 = selection_overlay_block_entity.skinning_color (render_hashes.txt line 40) | [V] |
| right2-cmp | 8 | reg cmp rcx,rdx | `0x6647462  cmp rcx,rdx` | vs right-leaf 2 | [V] |
| right2-miss | - | jne 0x66475BB | `0x6647465  jne 0x66475BB` | no match -> miss path | [V] |
| miss-global-load | 8 | [0x128D6FA8] | `0x66475bb  mov rsi,[0x128D6FA8]` | miss path loads global cache base | [V] |
| miss-forwarder | - | call 0x4DF6E80 | `0x66475de  call 0x4DF6E80` | miss forwarder 0x4df6e80 (6cj) -> miss tail 0x664CB91 | [V] |
| miss-tail | 8 | [rbp+0x1F8] | `0x664cb91  mov rsi,[rbp+0x1F8]` | miss tail entry (null rsi -> error path 0x664EBD7) | [V] |
| framectx-load | 8 | [rbp+0x8A0] | `0x6646e51  mov rax,[rbp+0x8A0]` | frameCtx held at rbp+0x8A0 | [V] |
| ctx-0x40-arg | 8 | [rax+0x40] | `0x6646e58  mov r9,[rax+0x40]` | resolver arg r9 = frameCtx+0x40 | [V] |
| cache-this-arg | 8 | [rax+0x68] | `0x6646e5c  mov rcx,[rax+0x68]` | resolver this rcx = frameCtx+0x68 — call-site 'this' provenance (was [I] in oc_U-EG6, now [V]) | [V] |
| pass-name-ptr | 8 | lea [0xF515E74] | `0x6646e6c  lea rax,[0xF515E74]` | pass-name string ptr (data 0xF515E74 = "CracksBlockEntity"; name role [I] per BGFX_MAP.md 6m + earlier verified notes) | [V] instr / [I] name |
| pass-name-len | 8 | [rbp+0x5A8] | `0x6646e7a  mov qword ptr [rbp+0x5A8],0x11` | string_view size 0x11 stored at [rbp+0x5A8] | [V] |
| sv-stack-slot | 8 | [rsp+0x20] | `0x6646e98  mov [rsp+0x20],rsi` | string_view {ptr = [rbp+0x5A0], size = 0x11} passed on stack at [rsp+0x20] | [V] |
| out-slot-lea | 8 | lea [rbp+0x1F0] | `0x6646ea4  lea rdx,[rbp+0x1F0]` | resolver out-param slot [rbp+0x1F0] | [V] |
| loader-arg | 8 | lea [0x129F9CB8] | `0x6646e9d  lea r8,[0x129F9CB8]` | loader arg r8 = data 0x129F9CB8 | [V] |
| resolver-call | - | call 0x675E440 | `0x6646eab  call 0x675E440` | THE control point / hook point: resolver call carrying the pass-name string_view; result material Holder* at [rbp+0x1F0] | [V] |
| global-this-1 | 8 | [0x128D6FA8] | `0x6646e16  mov rax,[0x128D6FA8]` | resolver this provenance part 1: global at 0x128D6FA8 | [V] |
| global-this-2 | 8 | [rax+0x120] | `0x6646e1d  mov rax,[rax+0x120]` | part 2: +0x120 of the global | [V] |
| global-this-3 | 8 | [rax+0x40] | `0x6646e24  mov rax,[rax+0x40]` | part 3: +0x40 -> cache base | [V] |
| cache-movq | 8 | [rax] | `0x6646e28  movq xmm6,[rax]` | cache base consumed (movq xmm6,[rax]) | [V] |
| res-load | 8 | [rbp+0x1F0] | `0x6646eb0  mov rax,[rbp+0x1F0]` | resolved Holder* out-param of ResourceCache::get | [V] |
| res-deref | 8 | [rax] | `0x6646eb7  mov rbx,[rax]` | rbx = Holder->resource (Resource*) | [V] |
| res-null | - | test rbx,rbx / je | `0x6646eba  test rbx,rbx`<br>`0x6646ebd  je 0x664CB91` | null Holder resource -> miss tail 0x664CB91 | [V] |
| requested-flag | 1 | [rbx+0x10] | `0x6646ee8  cmp byte ptr [rbx+0x10],1`<br>`0x6646eec  jne 0x664CB91` | Resource+0x10 requested flag == 1, else miss | [V] |
| refcount-touch | 8/4 | [rax+8] -> [rcx+8] | `0x6646ef2  mov rax,[rbp+0x1F0]`<br>`0x6646ef9  mov rcx,[rax+8]`<br>`0x6646f06  lock inc dword ptr [rcx+8]` | shared_ptr refcount touch (inc then released via [0xF99FFA0]) | [V] |
| refcount-release-call | - | call qword ptr [0xF99FFA0] | `0x6646f35  call qword ptr [0xF99FFA0]` | shared_ptr release helper sub_eea6040 via global slot [0xF99FFA0] | [V] |
| resolve-join | - | test rbx,rbx / je | `0x6646f56  jmp 0x6647FF1`<br>`0x6647ff1  test rbx,rbx`<br>`0x6647ff4  je 0x664CB91` | tag-7 path joins here after refcount dance; null -> miss tail | [V] |
| ctx-slot-swap | 8 | [r14+0x1B0] -> [rbp+0x130]/[rbp+0x138] | `0x6648080  mov rcx,[r14+0x1B0]`<br>`0x6648087  mov [rbp+0x130],rcx`<br>`0x664808e  mov r14,[rbp+0x138]`<br>`0x6648095  mov [rbp+0x138],rax` | context slots swapped around the resolved Holder | [V] |
| entry-used-mark | 1 | [rbx+0x30] | `0x6648339  mov byte ptr [rbx+0x30],1`<br>`0x664844b  mov byte ptr [rbx+0x30],1` | map entry+0x30 used mark set to 1 (entry layout per 0x675e440 dossier) | [V] |
| desc-material-store | 4 | [rbp+0x740]/[rbp+0x743] | `0x664852a  mov eax,[rbp+0x1F0]`<br>`0x6648536  mov [rbp+0x740],eax`<br>`0x664853c  mov [rbp+0x743],ecx` | resolved Holder (lo/hi dwords) stored to draw-desc material slot — the material is applied here | [V] |
| loadResource-call | - | call 0xBCBF730 | `0x664861e  call 0xBCBF730` | loadResource on the resolver's reload path (dossier) | [V] |
| refcount-release | - | call 0x82BE0 | `0x664862b  call 0x82BE0`<br>`0x6648637  call 0x82BE0` | shared_ptr release helper | [V] |
| mutex-unlock | - | call 0xEEC5A10 | `0x664870e  call 0xEEC5A10` | cache mutex unlock, pairs the 0xEEC59F0 lock | [V] |
| desc-matrix | 4 | [rbp+0x618]+idx | `0x6648884  movss [rax+r8],xmm0` (loop head 0x664887a; rax = `lea rax,[rbp+0x618]` at 0x664884b) | mat4, 4x movss, copied into desc at [rbp+0x618] | [V] |
| resolver-entry | 8 | - | `0x675e440  push rbp` | 0x675e440 entry = ResourceCache::get | [V] |
| cache-this-save | 8 | rcx -> r14 | `0x675e46d  mov r14,rcx` | cache this (arg1 rcx) saved to r14; body offsets are r14-relative | [V] |
| mutex-addr | 8 | [r14+0x98] | `0x675e489  lea r15,[r14+0x98]` | recursive mutex address = cache+0x98 | [V] |
| mutex-lock | - | call 0xEEC59F0 | `0x675e493  call 0xEEC59F0` | lock the cache recursive mutex | [V] |
| mutex-owner-count | 4 | [r14+0xE4] | `0x675e4ae  cmp dword ptr [r14+0xE4],0x7FFFFFFF` | cache+0xE4 = recursive-mutex owner count (mutex+0x4C); NOT a stale-key sentinel — the earlier "sentinel" label was a misread; semantic [?], irrelevant to the hook point | [V] instr / [?] sem |
| allocator-setTag-vcall | 1 | [0xF99FFA0] slot | `0x675e47e  mov dl,0x30`<br>`0x675e480  call qword ptr [0xF99FFA0]` | allocator setTag(0x30) via the global vcall slot — internal to the resolver, no hook target | [V] |
| key-lo | 8 | [rbx] | `0x675e4bf  mov rax,[rbx]` | key.lo (key+0x0) starts the FNV-1 64 hash | [V] |
| key-hi-byte0 | 1 | [rbx+8] | `0x675e4c2  movzx ecx,byte ptr [rbx+8]` | key.hi byte 0 mixed into the FNV-1 64 hash | [V] |
| fnv-basis | 8 | - | `0x675e4c6  mov rdx,0xCBF29CE484222325` | FNV-1 64 offset basis (same basis as pass-name hashes) | [V] |
| fnv-prime | 8 | - | `0x675e4d3  mov rcx,0x100000001B3` | FNV-1 64 prime; imul chain over key bytes follows | [V] |

## CLOSES?

NO — single blocking fact: the hook implementation itself is not present in the exe and cannot be produced by static analysis.

Every part of the item line that IS statically decodable is now [V]-proven: the tag-7 hash switch at 0x6646dc2 (BST split 0x416AE22CAB22EA36 @ 0x6646dde; leaves 0xD8EF928BC853553A @ 0x6646df1, 0x2C8B246FD3EDDC59 @ 0x6646e00 = cracks_overlay_tile_entity.skinning; right subtree 0x4B8EDB299C93ABB3 @ 0x6647449 = selection_overlay_block_entity.skinning, 0x416AE22CAB22EA37 @ 0x6647458 = selection_overlay_block_entity.skinning_color; miss path 0x66475bb `mov rsi,[0x128D6FA8]` -> 0x66475de `call 0x4DF6E80` -> miss tail 0x664CB91); the pass-name resolver call 0x6646eab with call-site this = frameCtx+0x68 (0x6646e5c), r9 = frameCtx+0x40 (0x6646e58), out slot [rbp+0x1F0]; and the resolver body 0x675e440 (mutex cache+0x98 locked via 0xEEC59F0, owner count at cache+0xE4, FNV-1 basis 0xCBF29CE484222325 @ 0x675e4c6, prime 0x100000001B3 @ 0x675e4d3). New angle results this unit: (1) all 34 direct call sites of 0x675e440 across 12 callers are ResourceCache::get calls — no material-specific hook; only 0x6646eab is tag-7 material-swap-relevant. (2) Post-return flow: the resolved Holder* at [rbp+0x1F0] ends up stored in the draw-desc material slot [rbp+0x740]/[rbp+0x743] (0x664852a/0x6648536), entry used-mark [rbx+0x30]=1 (0x6648339), mutex unlocked (0x664870e), mat4 to [rbp+0x618] — no swap function is invoked, so the intercept point remains the resolver call itself (detour at 0x6646eab, or replace the Holder result at desc [rbp+0x740]). (3) vt/vcalls: only internal indirect calls (allocator setTag via [0xF99FFA0], map-helper slots); the cache has no vtable slots — no hook slot exists. (4) descscan2/rw: unnecessary, full store map read from the listing. (5) livemem: unnecessary, 0 calls made.

Blocking fact: writing the hook (detour at call 0x6646eab or interception of the resolved Holder at desc [rbp+0x740]) is a runtime code change outside static-analysis scope (brief rules 1 and 3); it cannot be written or verified here. The item stays "not implemented" — this is orchestrator batch-build work, parked in MIRROR_SKIP per the checklist line 341 note. No offsets remain [I] or [?] for the control point itself.

## TOOL REQUESTS

None — rdis.exe `dis` + tools/sigs/verify_oc.py + `python tools/delegate.py check` were sufficient; no helper script written, no _tmp files left behind.
