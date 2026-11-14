# Progress: descriptions (agent "descriptions")

## NEXT
Unit 0 done (tool). Group order: Light (tags 0-7) -> Effect (0-8) -> UI (0-4) -> Sky (0-10) -> Editor (0-7) -> Item (0-10).
Resume with: `export PYTHONUTF8=1; python tools/sigs/descscan2.py --visitor light --case N --stop-on-write` (new tool, case-aware, coverage + GAPS).
Currently starting: Light tag 0 (LightAmbient) size proof via the fat producer clone 0x53e2c00 (stack object stores).

## Tool findings
### R12 - DONE (tools/sigs/descscan2.py; descscan.py is being edited by agent platform-versioning-live: stop-at-write + VISITOR_REG were added there at 14:45, I did not touch it)
- descscan2.py: `--visitor g [--case N]` lists/scan a visitor case between jump-table entries; `--range lo-hi` extra ranges (shared tails); `--stop-on-write`; `--events`; per-group register map (editor rdi, effect r15, ui r9, sky rdi, item rdi, light rsi); prints a COVERAGE map and GAPS of unread bytes.
- BUG FOUND in descscan.py [V]: its operand regexes require `0x` offsets, but capstone prints offsets below 10 as decimal (`[rsi + 8]`, `[rdi + 4]`), so EVERY read at +1..+9 (e.g. +4, +8) was dropped from all earlier descscan lists (Atmosphere +4/+8, LightAmbient +8, ...). descscan2.py handles both. Anything typed from descscan alone is missing those fields: re-check. CONTRADICTS 6id/6ih field lists at offsets 1..9.

## Entries (newest last)
