## NEXT
DONE

# Unit U-EL5c: item visitor tags 7 and 1 fields decoded from live dumps (6cv)

Goal (verbatim from the unit): close checklist item "L5c Tag 1/5 and 2/3/7/9: entries (6ci); tag 7 and 1 fields decoded from live dumps (6cv: model matrix pair, AABB, material node at +0x140)". Do ONLY the part marked pending/not found/not decoded in the status line: every field needs a verbatim `0xRVA  instr` proof line ([V]) or a proven blocking fact ([I]).

Status line (this unit): tag 7 matrix +0x00..0x3F, material +0x140, tag 1 +0x58/+0x00/+0x39 are [V]; tag 7 prev matrix +0x40..0x7F, tag 7 AABB +0x80..0x97 were live-dump only [I]; tag 1 position +0x38..0x43 was listed live-dump only but is NOW [V] (see new-angle hit below). CLOSES? = NO (see below): tag 7 +0x40..0x7F and +0x80..0x97 remain unread by any instruction.

Input data (read fully, no tools re-run to regenerate):
- docs/BGFX_MAP.md — 6ci (item-visitor jump table 0xf2bf2d0, u8 tag at *(r8+8), 11 entries, tag 7 -> 0x6646dc2, tag 1 -> 0x6646f5b), 6m (tag 1 = Nametag fields 0x48/0x58/0x80/0x84/0x94; tag 7 = SkinnedMesh), 6cv (tag 7 live: model matrix pair, AABB, material node at +0x140 of the item payload), 6cw (1.26.62.01 RVAs unshifted in this region).
- docs/data/listings/item_visitor_6646980_664fe00.txt (7698 lines, verbatim; source of every proof line below).
- docs/data/live_item_payloads_1.26.62.01.txt, docs/data/live/item_visitor.txt (6cv live values; data-proven only).
- Prior notes docs/progress/oc_U-EL5c_r1.md, _r2.md, _r3.md (r3's `0x6649451` hit re-verified below; notes are not proof).

Method / provenance: visitor entry 0x6646980 does `mov rdi,[r8]` (arg 3 = pointer to {payload*, tag}), tag byte at r8+8, jumps through table 0xf2bf2d0: tag 7 -> 0x6646dc2, tag 1 -> 0x6646f5b. rdi = item payload/description pointer. Sizes come from the instruction (movups/movaps/movdqu/movdqa = 16, movss = 4, movsd = 8, qword = 8, byte = 1). Every proof line below copied verbatim (two spaces after the address) from the listing. One row per distinct offset, all its sites listed. No input data pasted as-is.

## Field table (11 rows; one row per distinct offset cited by the item line; all sites listed)

| name | size | offset | address | verbatim `0xRVA  instr` proof line | tag | meaning |
|---|---|---|---|---|---|---|
| tag 7 model matrix row 0 (current frame) | 16 B | +0x00 | [rdi] | `0x664746b  movups xmm0,[rdi]` | [V] | row 0 of current-frame model matrix; starts +0x00..+0x3F |
| tag 7 model matrix row 1 (current frame) | 16 B | +0x10 | [rdi+0x10] | `0x6647475  movups xmm0,[rdi+0x10]` | [V] | row 1 of current-frame model matrix |
| tag 7 model matrix row 2 (current frame) | 16 B | +0x20 | [rdi+0x20] | `0x6647480  movups xmm0,[rdi+0x20]` | [V] | row 2 of current-frame model matrix |
| tag 7 model matrix row 3 (current frame) | 16 B | +0x30 | [rdi+0x30] | `0x664748b  movups xmm0,[rdi+0x30]` | [V] | row 3 (translation) of current-frame model matrix; +0x00..+0x3F complete |
| tag 7 material node pointer (HashedString node*) | 8 B | +0x140 | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]`; `0x6647729  mov rcx,[rdi+0x140]`; `0x6647b2e  mov rax,[rdi+0x140]` | [V] | qword read of the material-name node pointer (3 sites in tag 7's flow incl. BST subtree); node+0x10 holds FNV-1 64 material-name hash, live 0x0694BEA7E37055A4 = "ender_dragon.skinning" (§6cn) |
| tag 7 previous-frame model matrix (pair) | 64 B | +0x40..+0x7F | - | - | [I] | second 4x4 float-matrix copy present in the live dump (6cv, identical to +0x00..+0x3F when idle); BLOCKING FACT: no reader — tag 7's payload flow (entry 0x6646dc2, lines up to `0x6647da1`) reads only +0x00..+0x30, +0x140 and +0x198 (node pointer load); then `0x6647da1  mov rdi,[rdi+0x198]` rebases rdi to the material node, so `0x6647e73  mov r14,[rdi+0x40]`, `0x6647eb9  mov r14,[rdi+0x40]`, `0x6647f10  movzx esi,word ptr [rdi+0x48]` are NODE reads, not payload reads; exhaustive `[rdi+0x40..0x7F]` enumeration of the listing shows no other hit in tag 7's flow; live-dump only, no `0xRVA  instr` proof line |
| tag 7 local-space AABB min/max | 24 B | +0x80..+0x97 | - | - | [I] | six floats (-12,-12,-24, 12,24,48) present in the live dump (6cv); BLOCKING FACT: same reason — no reader in tag 7's flow; all `[rdi+0x80..0x97]` hits in the listing belong to other tags' cases (tag 0 at 0x6646a57 or others) or post-rebase node reads; live-dump only, no `0xRVA  instr` proof line |
| tag 1 mShared.mPtr (SharedRef.ptr) | 8 B | +0x58 | [rdi+0x58] | `0x6646f5b  mov rax,[rdi+0x58]` | [V] | qword read, validated non-null, then [rax+0x40] checked |
| tag 1 mOwner pointer | 8 B | +0x00 | [rdi] | `0x6646f77  mov rax,[rdi]` | [V] | qword read of the mOwner object pointer |
| tag 1 mOwner+0x39 byte flag | 1 B | +0x39 | [rax+0x39] (rax=[rdi]) | `0x6646f7a  movzx r8d,byte ptr [rax+0x39]` | [V] | byte flag read, passed to sub_66b2b30 (0x66B2B30) |
| tag 1 world position (x,y,z floats) | 16 B | +0x38 | [rdi+0x38] | `0x6649451  movups xmm4,[rdi+0x38]` | [V] | NEW ANGLE HIT (verified): tag 1's flow (entry 0x6646f5b -> ... -> `0x66471a9 je 0x66482E1` / `0x66471d9 jmp 0x66482F2` / 0x66475B3 -> `0x66475b6 jmp 0x6648312`) reaches the shared nametag block 0x664940d-0x6649494 with rdi still the payload (no `mov rdi` reassignment between 0x6648312 and 0x6649451; next `mov rdi` is 0x664b027, beyond it). Same block copies the owner world mat4 rows +0x08 `0x6649430  movups xmm1,[rdi+8]`, +0x18 `0x664943b  movups xmm2,[rdi+0x18]`, +0x28 `0x6649446  movups xmm3,[rdi+0x28]`, +0x38 `0x6649451  movups xmm4,[rdi+0x38]` — row 3 = translation; xyz = +0x38..+0x43 = live position (2.422, 0.88, -1.349). Block also reads §6m nametag fields +0x80 (`0x6649463  mov si,[rdi+0x80]`), +0x84 (`0x664941d  movups xmm0,[rdi+0x84]`), +0x94 (`0x664940d  cmp byte ptr [rdi+0x94],1`) — confirming this block is tag 1's nametag handling with rdi = payload. movups reads +0x38..+0x47; position is +0x38..+0x43 |

## Live-data cross-check (data-proven; meanings above come from the instructions)

- tag 7 sample (rdi=0x149620): +0x00..+0x3F and +0x40..+0x7F are two identical 4x4 float matrices (translation row at +0x30 = actor world position (60.5, 0.6878, 11.5)); +0x80..+0x97 decodes to the AABB (-12,-12,-24, 12,24,48); +0x140 is the material-name node whose +0x10 hash 0x0694BEA7E37055A4 resolves to "ender_dragon.skinning" (§6cn).
- tag 1 sample (rdi=0x14A148): +0x38..+0x43 holds the world position triple (2.422, 0.88, -1.349) — now instruction-proven as mat4 row 3 at `0x6649451`.

## New angles tried on the blocking fact (all from the listing; livemem not used — it can confirm field values but can never add a `0xRVA  instr` proof line)

1. `rdis walk 0x6646f5b --reg rdi` and `rdis walk 0x6646dc2 --reg rdi` — output identical for both starts (walk is not flow-sensitive); did not attribute reads per tag.
2. Exhaustive enumeration of every `[rdi+0x40..0x7F]` and `[rdi+0x80..0x97]` memory operand in the listing (7 greps): hits are `0x6647e73`/`0x6647eb9`/`0x6647f10` (post-`0x6647da1`, rdi = material node), tag-0 case reads (0x6646a10/0x6646a57), other-tag cases (0x6649915, 0x6649c49, 0x664c06b, 0x664c4dd, 0x664cd7d) — none in tag 7's payload flow.
3. `mov rdi` rebase map (18 sites): only `0x66469fd` (entry), `0x6647593`, `0x664787d`, `0x6647da1` (payload->node at `mov rdi,[rdi+0x198]`) are in-tag; all others load [rbp+...] locals in the shared epilogue. Tag 1's path to 0x6649451 bypasses every rebase (forward jump to 0x66482E1/0x66482F2/0x6648312, all RVAs above the rebases).
4. `descscan2`/`stores` add nothing: the whole visitor is one function; the listing + `mov rdi` map enumerate every instruction and every rdi rebase.
5. Cross-checked against docs/BGFX_MAP.md: 6m assigns tag 1 = Nametag (fields 0x48/0x58/0x80/0x84/0x94 — all read in block 0x664940d-0x6649494, confirming rdi = tag-1 payload there) and tag 7 = SkinnedMesh (fields 0xb0..0x1cc — no +0x40..0x7F/+0x80..0x97).

## CLOSES?

CLOSES? NO — blocking fact: tag 7 previous-frame model matrix +0x40..+0x7F and tag 7 local AABB +0x80..+0x97 exist only in the live dump data (6cv); tag 7's handler (entry 0x6646dc2) reads payload only up to +0x198 (node pointer), then `0x6647da1 mov rdi,[rdi+0x198]` rebases rdi to the material node, and exhaustive `[rdi+0x40..0x7F]`/`[rdi+0x80..0x97]` enumeration shows no payload read of those offsets — so they carry no `0xRVA  instr` proof line and cannot be [V]. Everything else in the item line is [V]: tag 7 model matrix +0x00..0x3F and material node +0x140; tag 1 +0x58, +0x00, +0x39, and position +0x38 (0x6649451). No other consumer of the item payload is in scope for this unit (6ci: the payload lives on the caller stack and is consumed by this visitor; live-dump values cannot be promoted to [V] without an instruction).

## TOOL REQUESTS

None — delegate.py check + verify_oc + rdis dis/walk and the listing greps sufficed; no helper script written.
