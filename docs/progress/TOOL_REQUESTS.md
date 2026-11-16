# Tool requests (collected from agents and the orchestrator)

Status: [open] requested, [impl] implemented (where), [skip] not general.

## Existing helper tools added this session (all in tools/sigs): [impl]
- dumplist.py LO HI OUT: exact rdis listing of a range (restarts after (bad)).
- cov_oc.py LO HI DOC...: real instructions in a range not quoted in docs.
- verify_oc.py DOC / verify_tbl.py LISTING DOC / verbatim.py LISTING DOC / union.py LISTING DOC...: check quoted lines against exe or listing, union coverage.
- stores.py LISTING...: every store into [reg+off]. casewalk.py LISTING HEAD REG...: control-flow walk from a case head and the [REG+off] uses.

## Wishes (orchestrator) [open]
1. [impl 2026-11-15, unit U-TOOL-WALK resumed via resume.ts] rdis `walk <rva> [--reg R]`: native CFG walk from an address (calls continue, ret/int3 end) printing reachable instructions and optional [reg+off] uses; replaces casewalk.py and works on the exe directly (no listing needed).
2. rdis `fieldmap <rva> <reg>`: per function, a table offset -> {size, R/W, sites} for one base register with reassignment tracking (stop at the first overwrite of the register).
3. [impl] tools/sigs/jt.py (jump table decoder)
4. rdis `dis --listing <lo> <hi>`: exact `0xRVA  instruction` lines (same format as dumplist.py), no 3000-instruction limit and no mid-instruction starts (always re-synchronise from the function start).
5. [impl] tools/sigs/livedec.py (livedump decoder)

- livedec.py and jt.py now exist and are tested by the orchestrator (TOOL1 stalled and was interrupted; livedec.py written by hand). Open wishes 1,2,3(done: jt.py),4 remain in TOOL_REQUESTS.md.
