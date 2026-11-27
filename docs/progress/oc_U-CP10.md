## NEXT
DONE

# U-CP10+CP11+CP12 — ctxpack digest, brief trim, baseline measure

Three tools created under the allowed paths:

## (1) tools/ctx/digest.py (CP10)
`python tools/ctx/digest.py <progress file>` prints a state digest ≤1 KB (done/open/facts/dead ends) from an agent's progress file. `digest.py --template` prints the `state.md` format agents keep at the top of their progress file; continuation prompts can use it instead of replaying history. `digest.py --selftest` passes.

## (2) docs/OPENCODE_BRIEF_NEXT.md (CP11)
Trimmed rewrite of `docs/OPENCODE_BRIEF.md` — same hard rules, fewer words, static content first, nothing per-item inside it (so it can be the stable cached prompt prefix). Original NOT replaced. Ends with a "Removed from OPENCODE_BRIEF.md" section listing everything dropped (specific RVA examples, file paths, line numbers, per-unit narratives, chunk-item specifics, BIGBANG_TESTS section, live-memory examples, quote-format-trap example, verbose toolbox descriptions, historical notes).

## (3) tools/ctx/measure.py (CP12)
`measure.py baseline` reads `ocd.db` (units, journal) and `opencode.db` (session_v2, session_message), computes per finished item: wall time (start→done), sends (message count), tokens cumulative (input+output), rotations (journal ROTATE per unit). Groups by difficulty rank (single/plan/chunk/asm from name suffix) and size bucket (progress file size: <1KB, 1-10KB, 10-100KB, >=100KB). Writes `docs/progress/measure/baseline.json` and prints table of medians with N per bucket.

`measure.py since <timestamp>` prints same table for items finished after that time plus % change per bucket vs baseline.

Both commands work; baseline covers 508 finished items; `since` demo with epoch 1795400000000 covers 484 items with %Δ columns.

## FILES
tools/ctx/digest.py
docs/OPENCODE_BRIEF_NEXT.md
tools/ctx/measure.py
docs/progress/measure/baseline.json

## SELFTESTS
- `python tools/ctx/digest.py --selftest` → OK (302 bytes digest)
- `python tools/ctx/measure.py baseline` → OK (baseline.json written)
- `python tools/ctx/measure.py since 1795400000000` → OK (484 items, %Δ printed)

## TOOL REQUESTS
None

CLOSES? YES