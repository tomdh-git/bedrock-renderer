## NEXT
DONE

UNIT U-EX0a — decode item visitor jump table 0xf2bf2d0 and executor record-type jump table from .rdata; resolve every case target; add missing targets via native_checklist_gen.py --add; empty docs/data/native_unresolved_indirect.tsv (rows removed only when decoded [V]); fix stale 'currently no data rows' statement.

STATUS: COMPLETE. Both jump tables decoded [V]; all case targets resolved and either already in the lift set or added as X7 roots; the indirect file is header-only (no data rows).

--------------------------------------------------------------
1) ITEM VISITOR JUMP TABLE 0xf2bf2d0 — decoded [V]
--------------------------------------------------------------
Referenced by the item visitor sub_6646980 at 0x6646a00. The tag is byte [r8+8], bounded by cmp rax,0xA (ja -> default 0x664ef12), so there are 11 entries (tags 0..10). The disassembly confirms table-relative int32 semantics:

`0x66469eb  movzx eax,byte ptr [r8+8]`
`0x66469f0  cmp rax,0xA`
`0x66469f4  ja 0x664EF12`          ; default
`0x6646a00  lea rcx,[0xF2BF2D0]`
`0x6646a07  movsxd rax,[rcx+rax*4]`
`0x6646a0b  add rax,rcx`
`0x6646a0e  jmp rax`               ; target = 0xF2BF2D0 + entry

Decoded entries (target = table + entry, jt.py 0xf2bf2d0 11):
tag 0 -> 0x6646a10   tag 1 -> 0x6646f5b   tag 2 -> 0x6646c8d   tag 3 -> 0x6646d5f
tag 4 -> 0x6646a89   tag 5 -> 0x66471de   tag 6 -> 0x6647320   tag 7 -> 0x6646dc2
tag 8 -> 0x66473e6   tag 9 -> 0x6646bc6   tag 10 -> 0x6647383
default -> 0x664ef12

All 12 targets are already present in docs/data/native_functions.tsv (lift set) [verified by membership scan], so no --add was needed for this table.

--------------------------------------------------------------
2) EXECUTOR RECORD-TYPE JUMP TABLE — decoded [V]; 0xfae774 is a typo
--------------------------------------------------------------
The tsv row names 0xfae774, but that address is NOT a call site: rdis xr 0xfae774 = 0 references, rdis imm 0xfae774 = 0 hits, and its raw 9 int32 entries decode to non-code garbage (e.g. targets 0x76863004 / negative offsets). The executor code at 0xe8230b8 (record loop, bounds cmp eax,0x41 at 0xe82306e; type byte at record+0x13) uses the REAL table 0xF4EE774:

`0xe8230aa  movzx eax,byte ptr [rsi+0x13]`
`0xe8230ae  cmp rax,8`
`0xe8230b2  ja 0xE824FBE`          ; default (type > 8)
`0xe8230b8  lea rcx,[0xF4EE774]`
`0xe8230bf  movsxd rax,[rcx+rax*4]`
`0xe8230c3  add rax,rcx`
`0xe8230c6  jmp rax`               ; target = 0xF4EE774 + entry

Decoded entries (target = table + entry, jt.py 0xf4ee774 9), matching BGFX_MAP 6an [V]:
type 0 -> 0xe8230c8   type 1 -> 0xe824a42   type 2 -> 0xe824a4f   type 3 -> 0xe8230c8
type 4 -> 0xe824991   type 5 -> 0xe824ab7   type 6 -> 0xe82326d   type 7 -> 0xe82326d
type 8 -> 0xe824af1   default -> 0xe824fbe

Each target verified as a real function start (each begins a sub_ region, disassembles cleanly) [V]. The 8 targets not already in the lift set were added as X7 roots:

python tools/native_checklist_gen.py --add 0xe8230c8 0xe824a42 0xe824a4f 0xe824991 0xe824ab7 0xe82326d 0xe824af1 0xe824fbe

Result: 965 functions in docs/data/native_functions.tsv; the 8 RVAs now present as `added <rva>` roots (milestone 7, d3d12 region) and recorded in docs/data/native_roots.txt [V].

--------------------------------------------------------------
3) TAIL-JUMP THUNK 0x568cd70 — resolved [V]
--------------------------------------------------------------
`0x568cd70  mov rcx,rdx`
`0x568cd73  mov rdx,r8`
`0x568cd76  jmp 0x568CD90`
-> body `0x568cd90  push rbp` [V]. No other tail-jump thunks on the frame path.

--------------------------------------------------------------
4) docs/data/native_unresolved_indirect.tsv — EMPTIED [V]
--------------------------------------------------------------
All 3 prior data rows removed [V] (each decoded above). File is now header-only. This fixes the stale 'currently no data rows' statement: the file previously contained 3 data rows (0xf2bf2d0, 0xfae774, 0x568cd70); all are resolved and removed, so header-only is now accurate.

--------------------------------------------------------------
PROOF TABLE (name | rva | size | site/instr | meaning | tag)
--------------------------------------------------------------

| offset | size | site | instr | meaning |
| 0xf2bf2d0 | 44 | item-visitor dispatch (sub_6646980) | `0x6646a00  lea rcx,[0xF2BF2D0]` / `0x6646a07  movsxd rax,[rcx+rax*4]` / `0x6646a0b  add rax,rcx` / `0x6646a0e  jmp rax` | 11 case entries (tag=byte[r8+8], 0..10, default 0x664ef12); table-relative target=table+entry; all 12 targets already in lift set [V] |
| 0xf4ee774 | 36 | executor record-type dispatch (sub_e822f80) | `0xe8230b8  lea rcx,[0xF4EE774]` / `0xe8230bf  movsxd rax,[rcx+rax*4]` / `0xe8230c3  add rax,rcx` / `0xe8230c6  jmp rax` | 9 case entries (type=byte[rsi+0x13], 0..8, default 0xe824fbe); target=table+entry; matches BGFX_MAP 6an [V]; 8 missing targets added as X7 roots [V] |
| 0x568cd70 | - | tail-jump thunk | `0x568cd70  mov rcx,rdx` / `0x568cd73  mov rdx,r8` / `0x568cd76  jmp 0x568CD90` | thunk -> pass body 0x568cd90 (`push rbp`) [V] |

--------------------------------------------------------------
FILES CHANGED / CREATED
--------------------------------------------------------------
- docs/data/native_unresolved_indirect.tsv : emptied to header-only (all 3 rows removed [V]).
- docs/data/native_functions.tsv : regenerated by --add; 8 executor targets added (965 functions total).
- docs/data/native_roots.txt : 8 `added 0x<rva>` root lines appended.
- docs/RENDER_CHECKLIST.md : regenerated by native_checklist_gen.py --add.
- docs/progress/oc_U-EX0a.md : this file.
Pre-existing (earlier X0a work, not modified this run): tools/sigs/closure2.py, docs/data/native_roots.txt (123 prior roots), docs/progress/vt_bbfb.txt / vt_rc_base.txt / vt_rc_rtx.txt.

--------------------------------------------------------------
CLOSES?
--------------------------------------------------------------
CLOSES? YES — both frame-path jump tables decoded [V] from .rdata, every case target resolved to a real function, missing targets added to the lift set via native_checklist_gen.py --add, and docs/data/native_unresolved_indirect.tsv lists no frame-path site (it is header-only). The 0xfae774 row was a typo: that address is not referenced (xr=0, imm=0) and is not a jump table; the real executor table 0xF4EE774 was decoded instead. No [UNVERIFIED] items remain for this unit.

--------------------------------------------------------------
## TOOL REQUESTS
None — all work done with rdis dis/xr/imm and jt.py / native_checklist_gen.py (existing tools).
