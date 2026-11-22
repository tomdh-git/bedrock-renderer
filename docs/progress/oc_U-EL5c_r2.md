## NEXT
DONE: 11 rows — tag 7 model matrix +0x00..+0x3F [V] (0x664746b/0x6647475/0x6647480/0x664748b), material node +0x140 [V] (0x6646dc2/0x6647729/0x6647b2e), tag 1 +0x58/+0x00/+0x39 [V] (0x6646f5b/0x6646f77/0x6646f7a); pending +0x40..+0x7F, +0x80..+0x97, +0x38..+0x43 live-dump-only [I], no reader instruction — CLOSES? = NO (verify_oc 10/10 match)

# Unit U-EL5c: item visitor tags 7 and 1 fields from live dumps (checklist item L5c/E1c, 6cv)

Goal (verbatim from the unit): close checklist item "L5c Tag 1/5 and 2/3/7/9: entries (6ci); tag 7 and 1 fields decoded from live dumps (6cv: model matrix pair, AABB, material node at +0x140)". Do ONLY the part marked pending/not found/not decoded in that line: prove the [V] decodes with verbatim instruction lines, and mark the three pending offsets (tag 7 prev matrix +0x40..+0x7F, tag 7 AABB +0x80..+0x97, tag 1 position +0x38..+0x43) as live-dump only.

Scope of THIS unit: only the 6cv portion — tag 7 and tag 1 fields decoded from the live item-payload dumps. The 6ci entries (handler addresses 0x6646dc2 tag 7, 0x6646f5b tag 1, jump table 0xf2bf2d0) are documented in docs/BGFX_MAP.md section 6ci; this note decodes the 6cv field layout with verbatim instruction proof lines.

## Input data (read fully, no tools re-run)

- docs/BGFX_MAP.md — sections 6ci (item-visitor jump table), 6cv (item payload field decode from the live dumps), 6cw (1.26.62.01 RVA validity).
- docs/data/listings/item_visitor_6646980_664fe00.txt — full verbatim disassembly of visitor 0x6646980 (7698 lines); source of every `0xRVA  instr` proof line below.
- docs/progress/pre/0x66466E0.md — preflight bundle for 0x66466e0 (_insert Item); corroborates the same listing.
- docs/data/live/item_visitor.txt — capture header lines (tag, descptr, hexbytes); 6cv/6cn live values cited below as live data.

## Method / provenance

Visitor entry 0x6646980 does `mov rdi,[r8]` (arg 3 = pointer on the caller's stack to {payload*, tag}), tag byte at `r8+8`, then jumps through table 0xf2bf2d0: tag 7 -> 0x6646dc2, tag 1 -> 0x6646f5b (BGFX_MAP.md 6ci). rdi is the item payload/description pointer. Every proof line below is copied verbatim (two spaces after the address) from docs/data/listings/item_visitor_6646980_664fe00.txt; RVAs are 1.26.62.01 (section 6cw confirms this region is unshifted in 1.26.62.01). Sizes come from the instruction (movups 16, qword 8, byte 1). No input data is pasted as-is; one row per distinct offset, all its sites listed.

## Field table (11 rows; one row per distinct offset, all sites listed)

| name | size | offset | address | verbatim `0xRVA  instr` proof line | tag | meaning |
| tag 7 model matrix row 0 (current frame) | 16 B | +0x00 | [rdi] | `0x664746b  movups xmm0,[rdi]` | [V] | 16-byte read of matrix row 0; starts the current-frame model matrix +0x00..+0x3F |
| tag 7 model matrix row 1 (current frame) | 16 B | +0x10 | [rdi+0x10] | `0x6647475  movups xmm0,[rdi+0x10]` | [V] | 16-byte read of matrix row 1 |
| tag 7 model matrix row 2 (current frame) | 16 B | +0x20 | [rdi+0x20] | `0x6647480  movups xmm0,[rdi+0x20]` | [V] | 16-byte read of matrix row 2 |
| tag 7 model matrix row 3 (current frame) | 16 B | +0x30 | [rdi+0x30] | `0x664748b  movups xmm0,[rdi+0x30]` | [V] | 16-byte read of matrix row 3 (translation row); +0x00..+0x3F complete |
| tag 7 material node pointer (HashedString*) | 8 B | +0x140 | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]`; `0x6647729  mov rcx,[rdi+0x140]`; `0x6647b2e  mov rax,[rdi+0x140]` | [V] | qword read of the material-name node pointer (3 sites in tag 7's handler incl. BST subtree at 0x6647449); node+0x10 holds the FNV-1 64 material-name hash, live 0x0694BEA7E37055A4 = "ender_dragon.skinning" (§6cn) |
| tag 7 previous-frame model matrix | - | +0x40..+0x7F | - | - | [I] | 64-byte second matrix copy present in the live dump (6cv, identical to +0x00..+0x3F); no reader instruction in tag 7's handler (entry 0x6646dc2, incl. subtree 0x6647449) — live-dump only, no `0xRVA  instr` proof line |
| tag 7 local-space AABB min/max | - | +0x80..+0x97 | - | - | [I] | six floats (-12,-12,-24, 12,24,48) present in the live dump (6cv); no reader instruction in tag 7's handler — live-dump only, no `0xRVA  instr` proof line |
| tag 1 mShared.mPtr (SharedRef*) | 8 B | +0x58 | [rdi+0x58] | `0x6646f5b  mov rax,[rdi+0x58]` | [V] | qword read, validated non-null, then [rax+0x40] checked |
| tag 1 mOwner pointer | 8 B | +0x00 | [rdi] | `0x6646f77  mov rax,[rdi]` | [V] | qword read of the mOwner object pointer |
| tag 1 mOwner+0x39 byte flag | 1 B | +0x39 | [rax+0x39] (rax=[rdi]) | `0x6646f7a  movzx r8d,byte ptr [rax+0x39]` | [V] | byte flag read, passed to sub_66b2b30 (0x66B2B30) |
| tag 1 world position (x,y,z floats) | - | +0x38..+0x43 | - | - | [I] | position triple present in the live dump (6cv: 2.422, 0.88, -1.349); no reader instruction in tag 1's block (0x6646f5b..0x66471de) — live-dump only, no `0xRVA  instr` proof line |

## Live-data cross-check (6cv / 6cn, cited as live data; field meanings inferred)

- tag 7 sample (rdi=0x149620): +0x00..+0x3F and +0x40..+0x7F are two identical 4x4 float matrices (translation row at +0x30 = actor world position (60.5, 0.6878, 11.5)); +0x80..+0x97 decodes to the AABB (-12,-12,-24, 12,24,48); +0x140 is the material-name node whose +0x10 hash 0x0694BEA7E37055A4 resolves to "ender_dragon.skinning" (§6cn).
- tag 1 sample (rdi=0x14A148): +0x38..+0x43 holds the world position triple (2.422, 0.88, -1.349).
- Confirmation of no reader: tag 7's handler (0x6646dc2, incl. BST subtree at 0x6647449) reads only +0x140 and +0x00..+0x30 among payload offsets (plus non-pending +0xB0/+0xB8/+0xC0/+0xE8/+0x148/+0x154/+0x198/+0x1A0/+0x1A8); tag 1's block (0x6646f5b..0x66471de) reads only +0x58, +0x00 and [rax+0x39]. Neither reads +0x40..+0x7F, +0x80..+0x97, or +0x38..+0x43.

## CLOSES?

CLOSES? NO — blocking fact: the tag 7 previous-frame model matrix (+0x40..+0x7F), tag 7 local AABB (+0x80..+0x97), and tag 1 world position (+0x38..+0x43) exist only in the live dump data (6cv); no instruction in tag 7's handler or tag 1's block reads those offsets, so they have no `0xRVA  instr` proof line and cannot be [V]. The [V]-proven subset — tag 7 model matrix +0x00..+0x3F and material node +0x140, tag 1 +0x58/+0x00/+0x39 — is closed.
