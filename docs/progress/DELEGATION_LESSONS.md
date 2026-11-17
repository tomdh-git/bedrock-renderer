# Delegation lessons (append one line per failure; tools/delegate.py bakes them into every prompt)
1. Sessions MUST be created with agent "general" (the default `build` agent has no write/shell tool; units fake files with console.log).
2. Pinned ultra model returns 503; alternate nemotron-3.5-super-vl / nemotron-3.5-lightning across units (one shared per-model limit stalls all).
3. A prompt that says "run tool X and write results" yields a raw tool dump. Give the unit PRECOMPUTED data files (I run the tools) and a TEMPLATE table to fill with one annotation per row.
4. Unit file names must be unique (old files with the same name cause false DONE).
5. "## NEXT" must be on its own line followed by a line starting with DONE (keeper detection).
6. Stores/reads of unrelated registers get pasted as description fields: the data file must already be filtered to the one register/object.
7. Sizes must come from the instruction (movups=16, mov qword=8, mov dword/movss=4, word=2, byte=1); a 4B label on a qword store is rejected by check.
8. At most ~150 rows per unit; split bigger jobs by case/tag so each unit finishes in one sitting.
9. The orchestrator verifies with `python tools/delegate.py check FILE` (verify_oc + shape checks) before accepting; a failed check goes back to the SAME session with the exact failure text.
10. Questions are cancelled by the keeper; units must choose a reading and write [UNVERIFIED: addr question].
11. Units loop on "run verify_oc, re-read file" without finishing (D6cB, D8e): tell them verify_oc runs ONCE per fix round, and cap at 3 rounds, then write [UNVERIFIED] and set DONE. Prefer giving the exact call site / line range (orchestrator reads 30 lines, unit extends the table) over open-ended search.
12. Do not delegate a "description field map" whose clone/producer computes the data (Clouds, Weather: stride-0x260 element arrays, mulps chains): the unit pastes stores of unrelated registers. Delegate only items where reads of ONE register in ONE visitor case are the answer (UI, editor, item cases) or where a single call-site arg map is needed.
13. casebest.py (tools/sigs) precomputes per-case reads with a guessed description register; units must ignore lines not reading that register.
14. Hardened prompt (precomputed data + template + delegate.py check) WORKED: D10x1/x2/x3 passed first time. keeper must check isDone BEFORE pause/MAXRUN gates.
