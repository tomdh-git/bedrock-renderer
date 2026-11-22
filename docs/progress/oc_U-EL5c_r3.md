## NEXT
DONE

# Unit U-EL5c: item visitor tags 7 and 1 fields from live dumps (checklist item L5c/E1c, 6cv)

Goal (verbatim): close "L5c Tag 1/5 and 2/3/7/9: entries (6ci); tag 7 and 1 fields decoded from live dumps (6cv: model matrix pair, AABB, material node at +0x140)". Scope of THIS unit: only the 6cv portion — tag 7 and tag 1 fields decoded from the live item-payload dumps, with verbatim `0xRVA  instr` proof lines. The 6ci entries (handler 0x6646dc2 tag 7, 0x6646f5b tag 1, jump table 0xf2bf2d0) are documented in docs/BGFX_MAP.md 6ci.

## Input data (read fully; no tools re-run to regenerate)

- docs/BGFX_MAP.md — sections 6ci (item-visitor jump table), 6m (descriptor field offsets), 6w (variant tags), 6cw (1.26.62.01 RVA validity).
- docs/data/listings/item_visitor_6646980_664fe00.txt — full verbatim disassembly of visitor 0x6646980 (7698 lines); source of every proof line below.
- docs/progress/pre/0x66466E0.md — preflight bundle for _insert Item 0x66466e0 (corroborates dispatch: `call 0x6646980` with variant {rdi=payload*, tag} on the stack).
- docs/data/live_item_payloads_1.26.62.01.txt — 6 raw 0x200-byte payload captures (tags 0/1/2/6/7/10).
- Prior unit notes docs/progress/oc_U-EL5c_r1.md, oc_U-EL5c_r2.md (proven [V] subset; three offsets left live-dump-only [I]).

## Method / provenance

Visitor entry 0x6646980 does `mov rdi,[r8]` (arg 3 = pointer to {payload*, tag}), tag byte at `r8+8`, jumps through table 0xf2bf2d0: tag 7 -> 0x6646dc2, tag 1 -> 0x6646f5b. rdi is the item payload/description pointer. rdi is redefined only at `0x66469fd mov rdi,[r8]` (entry), `0x6647593 mov rdi,rax`, `0x664787d mov rdi,rax` (neither on tag-1's flow), and `0x6647da1 mov rdi,[rdi+0x198]` (turns rdi into the material *node* — explains why `0x6647e73/0x6647eb9 mov r14,[rdi+0x40]` are NODE reads, not payload reads). Sizes come from the instruction (movups/movdqu 16, qword 8, movss/movsd 4/8, movzx byte 1, mov si 2). Every proof line below is copied verbatim (two spaces after the address) from the listing; RVAs are 1.26.62.01 (section 6cw confirms this region is unshifted).

## New angles tried on the blocking fact (tag 7 prev matrix +0x40..+0x7F, tag 7 AABB +0x80..+0x97, tag 1 position +0x38..+0x43)

1. `rdis ... cfg 0x6646980` (basic-block edges; rdis caps at 120 blocks per call) plus a full CFG rebuild from the 7698-line listing (leaders = function start + all jump targets; fall-through = next line address), with rdi taint tracking (payload vs node vs clobbered). Reachable-block sets: tag 1 = 38 blocks, tag 7 = 51 blocks, all with clean (payload) rdi.
2. `rdis ... walk 0x6646f5b --reg rdi` and `walk 0x6646dc2 --reg rdi` — enumerated every `[rdi+off]` use reachable from each tag entry.
3. Exhaustive enumeration of every `[rdi+...]` memory operand in the listing (single grep pass), attributed to tags via the CFG above.
4. `descscan2`/`stores` were considered but add nothing: the whole visitor is one function and the listing+CFG enumerate every instruction and every edge. `livemem` was not used: it can confirm field *values* in one instance but can never add a `0xRVA  instr` proof line, and static analysis already settles the reader question exhaustively.

## Field table (one row per distinct offset cited by the item line; all sites listed)

| name | size | offset | address | verbatim `0xRVA  instr` proof line | tag | meaning |
| tag 7 model matrix row 0 (current frame) | 16 B | +0x00 | [rdi] | `0x664746b  movups xmm0,[rdi]` | [V] | row 0 of current-frame model matrix; starts +0x00..+0x3F; re-read in tag-7 reachable shared tail `0x664AFA0  movups xmm0,[rdi]` / `0x664AFAA  movups xmm0,[rdi+0x10]` / `0x664AFB5  movups xmm0,[rdi+0x20]` / `0x664AFC0  movdqu xmm0,[rdi+0x30]` |
| tag 7 model matrix row 1 (current frame) | 16 B | +0x10 | [rdi+0x10] | `0x6647475  movups xmm0,[rdi+0x10]` | [V] | row 1 of current-frame model matrix |
| tag 7 model matrix row 2 (current frame) | 16 B | +0x20 | [rdi+0x20] | `0x6647480  movups xmm0,[rdi+0x20]` | [V] | row 2 of current-frame model matrix |
| tag 7 model matrix row 3 (current frame) | 16 B | +0x30 | [rdi+0x30] | `0x664748b  movups xmm0,[rdi+0x30]` | [V] | row 3 (translation) of current-frame model matrix; +0x00..+0x3F complete |
| tag 7 material node pointer (HashedString node*) | 8 B | +0x140 | [rdi+0x140] | `0x6646dc2  mov rax,[rdi+0x140]`; `0x6647729  mov rcx,[rdi+0x140]`; `0x6647b2e  mov rax,[rdi+0x140]` | [V] | qword read of the material-name node pointer (3 sites in tag 7's flow incl. BST subtree); node+0x10 holds the FNV-1 64 material-name hash, live 0x0694BEA7E37055A4 = "ender_dragon.skinning" (§6cn) |
| tag 7 previous-frame model matrix (pair) | - | +0x40..+0x7F | - | - | [I] | second 4x4 float-matrix copy present in the live dump (6cv, identical to +0x00..+0x3F when idle); CFG-exhaustive: no reader with rdi=payload — tag 7's payload reads stop at +0x1CC, then `0x6647da1 mov rdi,[rdi+0x198]` makes rdi the material node, so `0x6647e73 mov r14,[rdi+0x40]` / `0x6647eb9 mov r14,[rdi+0x40]` read node+0x40, not payload+0x40; live-dump only, no `0xRVA  instr` proof line |
| tag 7 local-space AABB min/max | - | +0x80..+0x97 | - | - | [I] | six floats (-12,-12,-24, 12,24,48) present in the live dump (6cv); CFG-exhaustive: no reader with rdi=payload anywhere in tag 7's 51 reachable blocks; live-dump only, no `0xRVA  instr` proof line |
| tag 1 mShared.mPtr (SharedRef.ptr) | 8 B | +0x58 | [rdi+0x58] | `0x6646f5b  mov rax,[rdi+0x58]` | [V] | qword read, validated non-null, then [rax+0x40] checked |
| tag 1 mOwner pointer | 8 B | +0x00 | [rdi] | `0x6646f77  mov rax,[rdi]` | [V] | qword read of the mOwner object pointer |
| tag 1 mOwner+0x39 byte flag | 1 B | +0x39 | [rax+0x39] (rax=[rdi]) | `0x6646f7a  movzx r8d,byte ptr [rax+0x39]` | [V] | byte flag read, passed to sub_66b2b30 |
| tag 1 world position (x,y,z floats) | 16 B | +0x38 | [rdi+0x38] | `0x6649451  movups xmm4,[rdi+0x38]` | [V] | NEW ANGLE HIT: tag 1's flow (entry 0x6646f5b -> ... -> 0x66475b3 -> jmp 0x6648312 -> ...) reaches block 0x664942B-0x66495AE with rdi still the payload (CFG-proven, clean rdi). Same block copies the owner world mat4 rows +0x08 `0x6649430  movups xmm1,[rdi+8]`, +0x18 `0x664943b  movups xmm2,[rdi+0x18]`, +0x28 `0x6649446  movups xmm3,[rdi+0x28]`, +0x38 `0x6649451  movups xmm4,[rdi+0x38]`, so +0x38 is mat4 row 3 = translation = world position; matches live dump (2.422, 0.88, -1.349 at +0x38..+0x43). This block also reads +0x80 (`0x6649463  mov si,[rdi+0x80]`), +0x84 (`0x664941d  movups xmm0,[rdi+0x84]`), +0x94 (`0x664940d  cmp byte ptr [rdi+0x94],1`) — matching §6m's tag-1 Nametag field list |

## Live-data cross-check (data-proven; meanings above come from the instructions)

- tag 7 sample (rdi=0x149620): +0x00..+0x3F and +0x40..+0x7F are two identical 4x4 float matrices (translation row at +0x30 = actor world position (60.5, 0.6878, 11.5)); +0x80..+0x97 decodes to the AABB (-12,-12,-24, 12,24,48); +0x140 is the material-name node whose +0x10 hash 0x0694BEA7E37055A4 resolves to "ender_dragon.skinning" (§6cn).
- tag 1 sample (rdi=0x14A148): +0x38..+0x43 holds the world position triple (2.422, 0.88, -1.349) — now instruction-proven at `0x6649451` as mat4 row 3.

## CLOSES?

CLOSES? NO — blocking fact: tag 7 previous-frame model matrix +0x40..+0x7F and tag 7 local AABB +0x80..+0x97 exist only in the live dump data (6cv); CFG-exhaustive analysis proves no instruction in tag 7's handler (or any block reachable from it with rdi = payload) reads those offsets (the `0x6647e73`/`0x6647eb9` `[rdi+0x40]` reads are material-node reads after `0x6647da1 mov rdi,[rdi+0x198]`), so they cannot carry a `0xRVA  instr` proof line and cannot be [V]. Tag 1 position +0x38..+0x43 IS now [V] (`0x6649451 movups xmm4,[rdi+0x38]`). The [V]-proven subset — tag 7 model matrix +0x00..+0x3F and material node +0x140; tag 1 +0x58/+0x00/+0x39 and position +0x38 — is closed.

## TOOL REQUESTS

cfg_analyze.py (throwaway, kept in %TEMP%, not in repo) | visitor listing -> CFG + rdi taint reachability | attributed every [rdi+off] read in the 7698-line listing to tag 1 vs tag 7 flow, which manual inspection and rdis cfg (120-block cap) could not do alone; generic enough to reuse for any visitor/handler field-attribution unit
