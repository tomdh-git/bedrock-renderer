# opencode verification (static, exe 1.26.62.01)

## NEXT
Next file: re_atmosphere. Remaining order: re_uimesh, re_blitflipbook, re_deferred_taau, re_m1d_*, re_m1c_*, re_m4_*, re_hashes, re_a4a8, re_b2b3, re_table_collision, re-descriptions, re_small_overlays.
Helper: %TEMP%\h.py (h.dis(lo,hi), h.dq/dd(rva)) built on tools/sigs/xref.py.
Note: Descriptions.h mtime (11-15 00:40) predates every opencode file (01:00+), so opencode did not edit it; no header fixes needed so far.

## re_sky_groups.md - VERIFIED (3 claims were from existing docs, not new)
- Visitor 0x66560f0 jump table: lea rcx at 0x665616b resolves to 0xF2BF39C; 11 entries read from exe: 0x6656174,0x6656697,0x66562d5,0x665649c,0x66561cc,0x66566ee,0x6656812,0x6656516,0x66569b1,0x665627e,0x6656983 = tags 0..10, matches claimed case addresses [V].
- Tag 1 tail-jump -> 0x67375a0 (jmp at 0x66566e9) and tag 9 tail-jump -> 0x6745440 (jmp at 0x66562d0) [V].
- Tag 0 reads word [desc], xmm at +0xA4/+0xB4/+0xC4, qword +0xE0 with lock inc [+8] [V]. Tag 3: [frame+0x70]==1 -> size 0x10 else 6, alloc 0x20 [V]. Tag 8 reads +0x00 word, +0x04..+0x5C, calls 0x5aba5c0 [V]. Tag 10 word [+0], ctrl block [+0x10] [V].
- UNCHECKED: tags 5/6 first callee 0x675e440 (opencode itself marked [I]).
- Contradictions with ours: none. Header: no edits by opencode.
