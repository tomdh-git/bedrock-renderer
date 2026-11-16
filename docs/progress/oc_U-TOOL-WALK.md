# oc_U-TOOL-WALK

## NEXT (top) — nothing remaining: implementation done, build verified, comparison written. Awaiting orchestrator check.

## Changes made
- `tools/rdis/src/walk.rs` (NEW): `walk` subcommand — control-flow walk from an RVA: straight-line fallthrough, both sides of conditional jumps, target of unconditional `jmp`, continue after calls; stops at `ret`/`int3`/`ud2` and at indirect `jmp` (printed with `; indirect jmp`); never revisits an instruction; capped at 4000 instructions. Prints reachable instructions sorted by address as `0xRVA  instruction` (same format as `rdis dis`). With `--reg R` prints a table of every `[R+off]` memory operand: offset, direction (R/W), size, RVA.
- `tools/rdis/src/main.rs`: `mod walk;` registration; `walk` command entry under the `walk` token; `--reg` flag parsed into `base` register; added `walk` to `CMDS` array (61→62); added `walk` entry to `HELP`.
- `docs/OPENCODE_BRIEF.md`: added `rdis walk <rva> [--reg R]` usage line to the '## Toolbox first' table.

## Build verification
`cargo build --release` in tools/rdis → succeeds (only pre-existing warnings; no new errors).

## Comparison against tools/sigs/casewalk.py
Listing: docs/data/listings/light_visitor_6640d80_6645400.txt, head 0x66415b0, reg rsi.

- `python tools/sigs/casewalk.py ... 0x66415b0 rsi` → reachable=453
- `rdis walk 0x66415b0 --reg rsi` → 580 instruction(s)

Reachable counts do NOT agree: casewalk=453 vs rdis=580. This is expected: casewalk walks only within the listing file (which ends at 0x6645400), while rdis reads from the full exe and can follow code past the listing boundary.

Offset sets agree: both produce the same 20 unique [rsi+off] offsets:
0x0, 0x8, 0x10, 0x14, 0x1C, 0x20, 0x648, 0x650, 0x6F0, 0x6F8, 0x700, 0x7E0, 0x7E8, 0x7F0, 0x7F8, 0x800, 0x808, 0x8A0, 0x8A8, 0x8B0.

Directions/sizes agree on shared instructions (e.g. 0x66415ba R [rsi+0x1C] size4; 0x6644bad W [rsi+8] size8).

rdis [rsi+off] access table count: 62 accesses.
