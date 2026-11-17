## NEXT
DONE: tag 7 model matrix +0x00..+0x3F and material node +0x140, tag 1 +0x58/+0x00/+0x39 proven [V]; tag 7 prev matrix +0x40..+0x7F + AABB +0x80..+0x97 and tag 1 position +0x38..+0x43 live-data-only ([I]) so CLOSES? = NO

# Unit U-EL5c: item visitor tags 7 and 1 fields from live dumps (checklist item L5c/E1c)

Goal (verbatim from the unit): "Close checklist item: L5c Tag 1/5 and 2/3/7/9: entries (6ci); tag 7 and 1 fields decoded from live dumps (6cv: model matrix pair, AABB, material node at +0x140). Do ONLY the part marked pending/not found/not decoded in that line."

Scope of THIS unit: only the 6cv portion — tag 7 and tag 1 fields decoded from the live item-payload dumps. The 6ci entries (handler addresses 0x6646dc2 tag 7, 0x6646f5b tag 1, jump table 0xf2bf2d0) are already documented elsewhere; this note proves/fields the 6cv decode with verbatim instruction lines.

## Input data (read fully, no tools re-run)

- docs/BGFX_MAP.md — sections 6ci (item-visitor jump table), 6cv (item payload field decode from live dumps), 6cw (1.26.62.01 RVA validity).
- docs/data/listings/item_visitor_6646980_664fe00.txt — full verbatim disassembly of visitor 0x6646980 (7698 lines); source of every `0xRVA  instr` proof line below.
- docs/progress/pre/0x66466E0.md — preflight bundle for 0x66466e0 (_insert Item), corroborates the same listing.
- docs/data/live_item_payloads_1.26.62.01.txt — 6 raw 0x200-byte payload captures (rdi at handler entry), tags 0/1/2/6/7/10.
- docs/data/live/item_visitor.txt — capture header lines (tag, descptr, hexbytes).

## Method / provenance

Visitor entry 0x6646980 does `mov rdi,[r8]` (arg 3 = pointer on the caller's stack to {payload*, tag}), tag byte at `r8+8`, then jumps through table 0xf2bf2d0 (relative i32 entries): tag 7 -> 0x6646dc2, tag 1 -> 0x6646f5b. Every proof line below is copied verbatim (two spaces after the address) from docs/data/listings/item_visitor_6646980_664fe00.txt; RVAs are 1.26.62.01 (section 6cw confirms this region is unshifted in 1.26.62.01). rdi is the item payload/description pointer. Sizes come from the instruction (movups 16, qword 8, byte 1).

## Field table (one row per distinct offset; all sites listed)

| name | offset | size | address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|---|
| tag 7 model matrix row 0 (current frame) | +0x00 | 16 B | [rdi+0x00] | `0x664746b  movups xmm0,[rdi]` | 16-byte read (matrix row 0; live payload: rotation*scale 0.008839, translation row at +0x30 holds actor world pos) | [V] |
| tag 7 model matrix row 1 (current frame) | +0x10 | 16 B | [rdi+0x10] | `0x6647475  movups xmm0,[rdi+0x10]` | 16-byte read (matrix row 1) | [V] |
| tag 7 model matrix row 2 (current frame) | +0x20 | 16 B | [rdi+0x20] | `0x6647480  movups xmm0,[rdi+0x20]` | 16-byte read (matrix row 2) | [V] |
| tag 7 model matrix row 3 (current frame) | +0x30 | 16 B | [rdi+0x30] | `0x664748b  movups xmm0,[rdi+0x30]` | 16-byte read (matrix row 3; completes current-frame matrix +0x00..+0x3F) | [V] |
| tag 7 material node pointer (HashedString node*) | +0x140 | 8 B | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]`; also `0x6647729  mov rcx,[rdi+0x140]`, `0x6647b2e  mov rax,[rdi+0x140]` | qword read; node+0x10 holds the FNV-1 64 material-name hash (live: 0x0694BEA7E37055A4 = "ender_dragon.skinning", 6cn) | [V] |
| tag 7 previous-frame model matrix | +0x40..+0x7F | 64 B | — not read by any instruction | — | live dump holds an identical copy of +0x00..+0x3F here (6cv); no visitor instruction reads it | [I] |
| tag 7 local-space AABB min/max | +0x80..+0x97 | 24 B | — not read by any instruction | — | live dump holds (-12,-12,-24, 12,24,48) exactly at +0x80..+0x97 (6cv); no visitor instruction reads it | [I] |
| tag 1 mShared.mPtr (SharedRef.ptr) | +0x58 | 8 B | [rdi+0x58] | `0x6646f5b  mov rax,[rdi+0x58]` | qword read; validated non-null, then [rax+0x40] checked | [V] |
| tag 1 mOwner pointer | +0x00 | 8 B | [rdi] | `0x6646f77  mov rax,[rdi]` | qword read (mOwner object pointer) | [V] |
| tag 1 mOwner+0x39 byte flag | +0x39 | 1 B | [rax+0x39] (rax=[rdi]) | `0x6646f7a  movzx r8d,byte ptr [rax+0x39]` | byte flag passed to sub_66b2b30 | [V] |
| tag 1 world position (x,y,z floats) | +0x38..+0x43 | 12 B | — not read by any instruction | — | live dump holds position triple here (6cv: x=2.422, y=0.88, z=-1.349 in the sampled frame); no visitor instruction reads it | [I] |

## Live-data cross-check (data-proven, not instruction-proven)

docs/data/live_item_payloads_1.26.62.01.txt tag-7 samples (rdi=0x149620): bytes +0x00..+0x3F and +0x40..+0x7F are two identical 4x4 float matrices (translation row at +0x30 = (60.5, 0.6878, 11.5, 1) per 6cv), bytes +0x80..+0x97 decode to the AABB (-12,-12,-24, 12,24,48), and qword at +0x140 is a material node whose +0x10 hash 0x0694BEA7E37055A4 resolves to "ender_dragon.skinning" (6cn). Tag-1 samples (rdi=0x14A148) hold the position triple at +0x38..+0x43 and a matrix copy at +0xD8..+0x13F per 6cv. None of these three layouts (tag-7 +0x40..+0x7F, tag-7 +0x80..+0x97, tag-1 +0x38..+0x43) is touched by any instruction in tag 7's handler (0x6646dc2, leaves 0x6646E13/0x6647449/0x66475BB, shared tails through 0x6647b2e) nor tag 1's single block (0x6646f5b..0x66471dd), which reads only +0x58, +0x00, +0x39.

## Proof lines (verbatim from docs/data/listings/item_visitor_6646980_664fe00.txt)
0x6646dc2  mov rax,[rdi+0x140]
0x664746b  movups xmm0,[rdi]
0x6647475  movups xmm0,[rdi+0x10]
0x6647480  movups xmm0,[rdi+0x20]
0x664748b  movups xmm0,[rdi+0x30]
0x6646f5b  mov rax,[rdi+0x58]
0x6646f77  mov rax,[rdi]
0x6646f7a  movzx r8d,byte ptr [rax+0x39]
0x6647729  mov rcx,[rdi+0x140]
0x6647b2e  mov rax,[rdi+0x140]

## CLOSES?

CLOSES? NO — blocking fact: the tag 7 previous-frame model matrix (+0x40..+0x7F), tag 7 local AABB (+0x80..+0x97), and tag 1 world position (+0x38..+0x43) exist only in the live dump data (6cv); no instruction in the visitor reads those offsets, so they have no `0xRVA  instr` proof line and cannot be [V]. The [V]-proven subset is tag 7 model matrix +0x00..+0x3F and material node +0x140, and tag 1 +0x58/+0x00/+0x39.
