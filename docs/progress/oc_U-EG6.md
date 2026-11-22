## NEXT
DONE

# U-EG6: G6 Material swap hook — control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj)

Goal: close checklist item G6 (Material swap hook: control point = pass-name resolver 0x675e440 + item-visitor hash switches (6cj); not implemented).
Do only the pending/not-decoded part: decode the item-visitor hash switches (tag-7 BST of FNV-1 64 material-name hash constants in 0x6646dc2) and the call into resolver 0x675e440, each proven with a verbatim `0xRVA  instr` line.
Note (6gs correction): 0x675e440 is ResourceCache::get (keyed get-or-load cache), not a "material resolver" by name — it is still the control point the hash-switch resolves the pass-name through.

## Evidence table (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?])

| tag7-payload+0x140 | 8 | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]` | tag-7 payload+0x140 → material-name node pointer | [V]
| node+0x10-hash-load | 8 | [rdx] | `0x6646ddb  mov rcx,[rdx]` | load 64-bit material-name hash from node+0x10 | [V]
| bst-split-imm | 8 | - | `0x6646dde  mov rdx,0x416AE22CAB22EA36` | BST split hash constant 0x416AE22CAB22EA36 | [V]
| bst-split-cmp | 8 | reg cmp rcx,rdx | `0x6646de8  cmp rcx,rdx` | hash vs split; jg → right subtree 0x6647449 | [V]
| bst-leaf1-imm | 8 | - | `0x6646df1  mov rdx,0xD8EF928BC853553A` | leaf hash constant 0xD8EF928BC853553A | [V]
| bst-leaf2-imm | 8 | - | `0x6646e00  mov rdx,0x2C8B246FD3EDDC59` | leaf hash = cracks_overlay_tile_entity.skinning (render_hashes.txt line 46) | [V]
| pass-name-string | 8 | lea [0xF515E74] | `0x6646e6c  lea rax,[0xF515E74]` | "CracksBlockEntity" pass-name string built at rbp+0x5A0 | [V]
| resolver-call | - | call 0x675E440 | `0x6646eab  call 0x675E440` | resolver called; name string_view passed on stack at [rsp+0x20] | [V]
| resolver-entry | - | - | `0x675e440  push rbp` | ResourceCache::get entry (0x4EC bytes, keyed get-or-load cache) | [V]
| cache-this-save | 8 | rcx→r14 | `0x675e46d  mov r14,rcx` | cache 'this' (arg1 rcx) saved to r14 | [V]
| mutex-lock | - | [r14+0x98] | `0x675e489  lea r15,[r14+0x98]` | lock recursive mutex at cache+0x98 (call 0xEEC59F0) | [V]
| stale-sentinel | 4 | [r14+0xE4] | `0x675e4ae  cmp dword ptr [r14+0xE4],0x7FFFFFFF` | stale-key sentinel check at cache+0xE4 | [V]
| key-lo-load | 8 | [rbx] | `0x675e4bf  mov rax,[rbx]` | key.lo (key+0x0) for FNV-1 64 hash | [V]
| key-hi-byte0 | 1 | [rbx+8] | `0x675e4c2  movzx ecx,byte ptr [rbx+8]` | key.hi byte 0 for FNV-1 64 hash | [V]
| bst-right-leaf1 | 8 | - | `0x6647449  mov rdx,0x4B8EDB299C93ABB3` | BST right subtree leaf = selection_overlay_block_entity.skinning | [V]
| bst-right-leaf2 | 8 | - | `0x6647458  mov rdx,0x416AE22CAB22EA37` | BST right subtree leaf = selection_overlay_block_entity.skinning_color | [V]

## CLOSES?

YES — every pending part of G6 is proven by [V] rows:
(1) item-visitor tag-7 hash switch (0x6646dc2): BST of FNV-1 64 material-name hash constants (split 0x416AE22CAB22EA36, leaves 0xD8EF928BC853553A and 0x2C8B246FD3EDDC59 = cracks_overlay_tile_entity.skinning; right subtree 0x6647449 leaves 0x4B8EDB299C93ABB3 = selection_overlay_block_entity.skinning and 0x416AE22CAB22EA37 = selection_overlay_block_entity.skinning_color) — decoded with verbatim [V] lines.
(2) pass-name resolver call: on a matching leaf the visitor builds the pass-name string "CracksBlockEntity" (0x6646e6c) and calls 0x675e440 (0x6646eab) with the name string_view on the stack at [rsp+0x20] — [V].
(3) resolver identity: 0x675e440 = ResourceCache::get (6gs correction: keyed get-or-load cache, not a name-based "material resolver") — entry 0x675e440 [V], mutex lock at cache+0x98 [V], stale sentinel at cache+0xE4 [V], FNV-1 64 over key bytes [V].
The control point for a material-swap hook is therefore the hash-switch inputs in 0x6646dc2 (patch the BST constants) or the resolver 0x675e440 (intercept the get-by-name/key). [UNVERIFIED: 0x6646eab rcx at call site — disassembly shows rcx=[frameCtx+0x68], while 6cj claims cache-this=[rip+0xc29018b]->+0x120->+0x40; the pass-name string and call itself are [V], only the exact 'this' provenance is [I]]
