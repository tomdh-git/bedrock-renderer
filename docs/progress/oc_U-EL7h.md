## NEXT
DONE

# Unit U-EL7h: L7h Material swap hook — pass-name resolver 0x675e440 + item-visitor hash switches (6cj)

## Scope

Checklist item L7h (docs/RENDER_CHECKLIST.md line 341): "Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented".
Sibling unit oc_U-EG6.md (G6, same line) decoded the tag-7 FNV-1 BST at 0x6646dc2 and the call into resolver 0x675e440, all [V], but left one part [UNVERIFIED]: the resolver 'this' at the call site (rcx = [frameCtx+0x68] vs 6cj's global-cache provenance [rip+0xc29018b]->+0x120->+0x40).
This unit decodes exactly that pending part and re-quotes every control-point instruction verbatim from the exe; every quoted line is re-verified against the exe by verify_oc.py via `python tools/delegate.py check`. The hook itself is not implemented (static analysis only — no detour is written).

## Source data (read fully, not re-computed)

`docs/BGFX_MAP.md` section 6cj (tag-7 hash switch, resolver 0x675e440, pass-name string "CracksBlockEntity") and `docs/data/render_hashes.txt` (hash->name lines: 0x2C8B246FD3EDDC59 line 46, 0x4B8EDB299C93ABB3 line 39, 0x416AE22CAB22EA37 line 40; code disassembly at the quoted RVAs is the authority, confirmed live for ender_dragon.skinning in section 6cn and docs/data/live_item_payloads_1.26.62.01.txt).

## Evidence table (name | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?])

| tag7-node-load | 8 | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]` | tag-7 payload+0x140 → material-name HashedString node pointer; rax==0 falls back to static default 0x1232E708 (`lea rdx,[0x1232E708]` at 0x6646dd0, `cmovne rdx,rcx` at 0x6646dd7) | [V] |
| node-hash-load | 8 | [rdx] (rdx = node+0x10 or default) | `0x6646ddb  mov rcx,[rdx]` | 64-bit material-name hash loaded into rcx from node+0x10 | [V] |
| bst-split | 8 | - | `0x6646dde  mov rdx,0x416AE22CAB22EA36` | BST split imm 0x416AE22CAB22EA36 | [V] |
| bst-split-cmp | 8 | reg cmp rcx,rdx | `0x6646de8  cmp rcx,rdx` | hash vs split; `jg 0x6647449` at 0x6646deb takes the right subtree | [V] |
| bst-leaf1 | 8 | - | `0x6646df1  mov rdx,0xD8EF928BC853553A` | left leaf imm 0xD8EF928BC853553A; `je short 0x6646e13` at 0x6646dfe on match | [V] |
| bst-leaf2 | 8 | - | `0x6646e00  mov rdx,0x2C8B246FD3EDDC59` | left leaf 2 = cracks_overlay_tile_entity.skinning (render_hashes.txt line 46) | [V] |
| leaf2-cmp | 8 | reg cmp rcx,rdx | `0x6646e0a  cmp rcx,rdx` | `jne 0x66475BB` at 0x6646e0d → unresolved-leaf/miss path | [V] |
| miss-global-load | 8 | [0x128D6FA8] | `0x66475bb  mov rsi,[0x128D6FA8]` | miss path (both jne targets converge at 0x66475bb) loads the same global 0x128D6FA8 | [V] |
| miss-forwarder | - | call 0x4DF6E80 | `0x66475de  call 0x4DF6E80` | no leaf matched → small forwarder 0x4df6e80 (6cj); miss tail 0x664CB91 | [V] |
| bst-right-leaf1 | 8 | - | `0x6647449  mov rdx,0x4B8EDB299C93ABB3` | right-subtree leaf = selection_overlay_block_entity.skinning (render_hashes.txt line 39) | [V] |
| right1-cmp | 8 | reg cmp rcx,rdx | `0x6647453  cmp rcx,rdx` | `je short 0x664746B` at 0x6647456 on match → item-field copy block at 0x664746b | [V] |
| bst-right-leaf2 | 8 | - | `0x6647458  mov rdx,0x416AE22CAB22EA37` | right-subtree leaf 2 = selection_overlay_block_entity.skinning_color (render_hashes.txt line 40) | [V] |
| right2-cmp | 8 | reg cmp rcx,rdx | `0x6647462  cmp rcx,rdx` | `jne 0x66475BB` at 0x6647465 → miss path | [V] |

| framectx-load | 8 | [rbp+0x8A0] | `0x6646e51  mov rax,[rbp+0x8A0]` | rax = frameCtx/visitor context held at rbp+0x8A0; source of the ctx+0x40 and ctx+0x68 resolver arguments | [V] |
| ctx-0x40-arg | 8 | [rax+0x40] -> r9 | `0x6646e58  mov r9,[rax+0x40]` | resolver arg r9 = frameCtx+0x40 | [V] |
| cache-this-arg | 8 | [rax+0x68] -> rcx | `0x6646e5c  mov rcx,[rax+0x68]` | resolver this (rcx) = frameCtx+0x68 — call-site 'this' provenance, the open part of oc_U-EG6, now [V] | [V] |
| pass-name-string | 8 | lea [0xF515E74] | `0x6646e6c  lea rax,[0xF515E74]` | "CracksBlockEntity" pass-name string (data at 0xF515E74); size 0x11 stored at [rbp+0x5A8] (`mov qword ptr [rbp+0x5A8],0x11` at 0x6646e7a) | [V] |
| string-view-arg | 8 | [rsp+0x20] | `0x6646e98  mov [rsp+0x20],rsi` | string_view {ptr = [rbp+0x5A0], size = 0x11} passed on the stack at [rsp+0x20]; rdx = out slot [rbp+0x1F0] (`lea rdx,[rbp+0x1F0]` at 0x6646ea4); r8 = [0x129F9CB8] (`lea r8,[0x129F9CB8]` at 0x6646e9d) | [V] |
| resolver-call | - | call 0x675E440 | `0x6646eab  call 0x675E440` | resolver called with pass-name string_view; result material pointer at [rbp+0x1F0] (`mov rax,[rbp+0x1F0]` at 0x6646eb0); null → miss tail 0x664CB91 (`je 0x664CB91` at 0x6646ebd) | [V] |
| global-this-1 | 8 | [0x128D6FA8] | `0x6646e16  mov rax,[0x128D6FA8]` | resolver this provenance part 1: global at 0x128D6FA8 (rip-relative [rip+0xc29018b] at 0x6646e16, matches 6cj) | [V] |
| global-this-2 | 8 | [rax+0x120] | `0x6646e1d  mov rax,[rax+0x120]` | part 2: +0x120 of that global | [V] |
| global-this-3 | 8 | [rax+0x40] | `0x6646e24  mov rax,[rax+0x40]` | part 3: +0x40 → cache base; consumed by `movq xmm6,[rax]` at 0x6646e28 | [V] |

| resolver-entry | - | - | `0x675e440  push rbp` | 0x675e440 entry = pass-name resolver (keyed get-or-load name cache; "ResourceCache::get" naming is [I] per the 6gs correction, behavior is [V]) | [V] |
| cache-this-save | 8 | rcx -> r14 | `0x675e46d  mov r14,rcx` | cache 'this' (arg1 rcx = the value passed at 0x6646e5c) saved to r14; all cache offsets below are r14-relative | [V] |
| mutex-addr | 8 | [r14+0x98] -> r15 | `0x675e489  lea r15,[r14+0x98]` | recursive mutex address = cache+0x98; locked by `call 0xEEC59F0` at 0x675e493 | [V] |
| stale-sentinel | 4 | [r14+0xE4] | `0x675e4ae  cmp dword ptr [r14+0xE4],0x7FFFFFFF` | stale-key sentinel at cache+0xE4 (0x7FFFFFFF = stale) → reload path (`je 0x675E8D3` at 0x675e4b9) | [V] |
| key-lo | 8 | [rbx] | `0x675e4bf  mov rax,[rbx]` | key.lo (key+0x0; arg2 = rbx) starts the FNV-1 64 hash | [V] |
| key-byte0 | 1 | [rbx+8] | `0x675e4c2  movzx ecx,byte ptr [rbx+8]` | key.hi byte 0 (key+0x8) mixed into the FNV-1 64 hash | [V] |
| fnv-basis | 8 | - | `0x675e4c6  mov rdx,0xCBF29CE484222325` | FNV-1 64 offset basis 0xcbf29ce484222325 (same basis as pass-name hashes, 6p) | [V] |
| fnv-prime | 8 | - | `0x675e4d3  mov rcx,0x100000001B3` | FNV-1 64 prime; imul chain over key bytes follows at 0x675e4dd..0x675e52e | [V] |

## CLOSES?

YES — every pending part of L7h is proven by [V] rows:

(1) Item-visitor hash switch (6cj, tag 7, handler 0x6646dc2): BST over FNV-1 64 material-name hash — split 0x416AE22CAB22EA36 (0x6646dde, `jg 0x6647449` at 0x6646deb); left leaves 0xD8EF928BC853553A (0x6646df1) and 0x2C8B246FD3EDDC59 = cracks_overlay_tile_entity.skinning (0x6646e00, render_hashes.txt line 46); right subtree at 0x6647449 with leaves 0x4B8EDB299C93ABB3 = selection_overlay_block_entity.skinning (0x6647449, line 39) and 0x416AE22CAB22EA37 = selection_overlay_block_entity.skinning_color (0x6647458, line 40); no leaf matches → 0x66475bb (`mov rsi,[0x128D6FA8]` at 0x66475bb) → forwarder 0x4df6e80 (0x66475de), miss tail 0x664CB91. The switch input is the hash at [payload+0x140]->+0x10 (0x6646dc2/0x6646ddb; live-confirmed as ender_dragon.skinning in 6cn / docs/data/live_item_payloads_1.26.62.01.txt).

(2) Pass-name resolver call: on a match the visitor builds the pass-name string "CracksBlockEntity" (`lea rax,[0xF515E74]` at 0x6646e6c, len 0x11 at 0x6646e7a), passes string_view on the stack at [rsp+0x20] (0x6646e98), and calls 0x675e440 (0x6646eab). Call-site 'this' (rcx) = frameCtx+0x68 (0x6646e5c), r9 = frameCtx+0x40 (0x6646e58); same cache base also reached as [[0x128D6FA8]+0x120]+0x40 (0x6646e16-0x6646e24). Result at [rbp+0x1F0]; null → 0x664CB91 (0x6646ebd). This resolves the only open part of oc_U-EG6 (call-site rcx provenance: was [I], now [V] with the verbatim line at 0x6646e5c).

(3) Resolver body (0x675e440): entry `push rbp` (0x675e440); this→r14 (0x675e46d); recursive mutex at cache+0x98 locked via 0xEEC59F0 (0x675e489/0x675e493); stale-key sentinel cache+0xE4 (0x675e4ae); FNV-1 64 over key bytes: basis 0xCBF29CE484222325 (0x675e4c6), prime 0x100000001B3 (0x675e4d3), key.lo [rbx] (0x675e4bf), key bytes from [rbx+8] (0x675e4c2).

Control point for the material-swap hook: the BST hash constants at 0x6646dde/0x6646df1/0x6646e00/0x6647449/0x6647458, or the resolver get-by-name at 0x675e440 (intercept the call carrying the pass-name string_view). Hook implementation itself is dynamic and out of scope for static analysis, so "not implemented" stands as a code-change item, not a decode gap: everything decodable statically in this item line is [V]-proven above.

