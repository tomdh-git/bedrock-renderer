# rdis accuracy test report

Test exe: 1.26.62.01 (`rdis.exe` built Nov 12 16:44). `port` target: 1.26.60.05. Method: own PE parser + capstone + numpy/regex scans in Python (scratch scripts, not verify.py).
Everything below was checked against raw bytes unless marked UNVERIFIED. The two builds are near-identical (same function sizes, mnemonic sequences equal, only addresses shifted), so `port` was tested on an easy pair of builds; see limitations.

## Summary

| command | checks run | correct | wrong | notes |
|---|---|---|---|---|
| info | TimeDateStamp, SizeOfImage, PDB GUID/age/path, file size, function count, both exes | all | 0 | `functions_pdata` = non-chained .pdata entries (983599), matches mine |
| port (strings) | 8 random unique-string fns + 6 clone groups + 3 new-in-62 fns | 7 of 8 right; 1 unknown (missed) | 0 confident wrong | right = same string xrefs AND identical mnemonic sequence in 60.05 |
| port (no strings) | 6 fns | 3 right (candidate), 1 unknown | 2 wrong top candidates, labelled `candidate` | true match not in top 5 in both wrong cases |
| port (edge) | 18 edge calls | see bugs 3-6 | | |
| sigcheck | 14 sigs (real prologues, wildcards, CC/90/00 runs, overlapping) vs my exhaustive regex scan | 14 | 0 | counts identical incl. 182366 and 0; lint gap in bug 2 |
| hookpoints | `first_16_bytes_matches` for 2 results (5812, 8) | 2 | 0 | ranking logic itself not independently checkable |
| abi | 60 random fns (2 seeds) vs my CFG read-before-write analysis | 10 exact | 48 report args never read, 6 omit args that are read | see bug 1; `hidden_return_pointer` spot-checked on 6, consistent with "returns a0/a1 unchanged" |
| gates | 40 random (fn, call ip) vs my edge-removal CFG | 36 | 0 | 4 skipped (indirect jmp); condition text spot-checked on one (jg after cmp, signed) |
| path / choke | 14 random depth-3 pairs; hop sites decoded, choke set vs my node-removal | 14 | 0 | chokepoint sets identical |
| needs | 1 example; must_hold equals `gates` output | 1 | 0 | thin coverage |
| decide | 4 predicates (call; test al,al; jcc): flagged sites; `outcomes` calls vs my edge-removal on 8 outcome sets | 4 and 8 | 0 | rdis finds more sites than my narrow pattern, all inspected ones real |
| flow `aN` | 165 (call,arg) pairs across 5 samples vs my forward taint | ~155 agree | 0 false claims found | rdis-only cases were jump-table-reachable code my analysis could not reach (rdis right); 4 mine-only cases left UNVERIFIED (rdis likely conservative) |
| flow `--field` | 1 function by hand | reads and tail-call arg correct | 1 over-attribution | see bug 8 |
| contradict | 1 | verdict plausible | 1 duplicate entry | see bug 8 |
| callers | 27 fns (varied fan-in) vs my E8/E9 scan validated by disassembly | 27 | 0 | one name differs: chained fragment shown under primary (consistent with design) |
| sum (calls) | 30 random fns: set of direct call/tail-jmp (ip,target) | 30 | 0 | |
| anchors (strings) | 30 fns | 29 | 0 | 1 string I could not confirm (my scan only finds `lea`) |
| vcalls | 64 vcalls: slot vs preceding `mov rax,[rax+disp]` before CFG dispatch call; 2 derived targets vs vtable bytes | 56 slot confirmed, 2 targets confirmed | 0 | 8 slots not locally checkable (rax loaded in a shared block); it correctly treats `call [__guard_dispatch_icall_fptr]` as a vcall |
| jump table (0xe9759e0, `cfg`) | first switch: index table + dword table decoded by hand, case groups compared | match | 0 | second switch UNVERIFIED |
| assert / retract | assert, facts, retract, facts, audit | ok | 0 | retracted; journal keeps both lines (append-only) |
| MCP | 21 requests | see bugs 9-11 | | survives everything, no hang |
| robustness | 51 fns x (sum, abi, anchors, flow a0) = 204 runs, incl. the 3 largest fns (1.7 MB) | 204 | 0 panics, 0 over 20 s | plus 150 edge-argument runs, no panic |

## BUGS

1. `abi` argument usage is unreliable in both directions.
   - Cmd: `abi 0x370f30`. Raw: static-init function; no instruction reads rcx/rdx/r8/r9 (calls pass `rcx=lea`, `edx=0`, `r8d=imm`, r9 never set). rdis: `arguments_used_in_register: ["a3"]` (r9 passed through to a callee untouched is counted as "used").
   - Cmd: `abi 0xeca3240`. Raw: reads none of the 4 arg regs. rdis: a0, a2, a3.
   - Cmd: `abi 0x115100`. Raw: `mov rsi,r9; mov r14,rdx; mov rdi,rcx; cmp r8,rdx` (all four args read). rdis: only `a3`. Cause: only memory bases and call arguments are scanned, so plain register use (copies, compares, arithmetic) is missed.
   - Rate over 60 random functions: 48 report args that are never read, 6 miss args that are read, 10 exact. Trust line says "hint", but the field is named `arguments_used_in_register`.
2. `sigcheck` rel32 lint off by one. Cmd: `sigcheck 48 83 EC 28 48 8B 49 18 48 8B 01 48 8B 40 30 48 89 5C 24 08 48 8B D9 E8 11 22 33 44`. Expected: warning that call at byte 23 has concrete displacement. rdis: only "matches nothing". Same sig with E8 mid-signature is flagged. (Loop `0..n-5` should include n-5.) Also not linted: rip-relative disp32 (`48 8D 0D xx xx xx xx`, `FF 15`), `0F 8x` jcc rel32. Token `???` is accepted as a wildcard.
3. `port` on a non-function address gives a result instead of an error. Cmd: `port <60.05> 0xf2be508` (a string in .rdata) returns `function_here: data_f2be508`, size 104 and 7 "blocks" (data disassembled). `port <60.05> 0x20000000` returns size 3758096384. `0x0`, `0xffffffff` likewise return a verdict `unknown` with the misleading reason "no anchor exists". Expected: error "not in an executable section". Same for `abi`, `anchors`, `decide`, `flow`, `sum`, `callees` on such addresses (empty/garbage results presented as analysis, e.g. `abi 0xffffffff` -> `arguments_used_in_register: []`).
4. `port` misses unique-string anchors that `anchors` reports. Cmd: `port <60.05> 0xc1ba040` -> verdict `unknown`, no candidates. `anchors 0xc1ba040` lists a unique 100+ char `auto __cdecl OreUI::WorldEditorFacet::saveLocalWorld...` string; 60.05 has the same function at 0xc1b9440 (same string, identical 244-instruction mnemonic sequence). Likely long strings are truncated before the exact-text search (conservative failure, not wrong).
5. `port --top 0` returns `unknown ... no string, type hash or immediate anchor exists` although anchors exist (reason text wrong). Minor.
6. `port C:/nonexist.exe 0x66ea3d0` reports `internal error ... nothing is claimed` with a Rust panic on stderr instead of "cannot read exe". `port <notepad.exe> ...` silently returns `unknown`.
7. `port` no-string functions: confident-looking wrong candidates. Cmd: `port <60.05> 0x4633060` -> candidate 0x462e8f0 (score 3.2, basis `type:StopSoundPacketPayload`; mnemonic shape ratio 0.42). True match is 0x4632e90 (identical shape), absent from the top 5. `port <60.05> 0xbfcae00` -> candidate 0x837b0 (basis `immediates:3/3`, ratio 0.57); true match 0xbfca200. Both labelled `candidate`, never `derived`, so within the contract, but a shape check (blocks/callees) is not used to demote them.
8. `flow <fn> --field` over-attributes: `flow 0x2c16e40 --field 0x18` lists call 0x2c170d5 under the read at 0x2c16e4b, but edx at that call is reloaded from `[rdi+0x18]` at 0x2c170c8, so only the second read reaches it. `contradict 0x18 --fn 0x2c16e40 --as compare-only` lists the call 0x2c170d5 twice (duplicate evidence). The trust text ("textual containment") says this, but per-read grouping reads as flow.
9. MCP: malformed JSON line (`{"jsonrpc":"2.0","id":6,"method":`) and non-JSON text get no response at all (JSON-RPC expects -32700). A client waiting for a reply hangs. Server stays alive and serves the next request.
10. MCP: errors are `isError:false`. Unknown tool `nonexistent` -> `result.content[0].text = "error: unknown command..."`, `isError:false`; `{"error":"missing address"}` likewise; `tools/call` with no params returns empty text, isError false.
11. MCP: a 5 MB bogus argument is echoed back in the error text (5 MB response). No crash.
12. Address normalisation inconsistent: `callers 0x2c16e44` (mid-function) -> 0 callers, while `sum`/`abi`/`anchors`/`decide`/`port` silently round down to the function start. `gates 0x2c16e44 ...` reports function `sub_2c16e44` with block 0x2c16e44 (no rounding). `callers --max 3` ignores `--max` (prints all callers; text output).
13. `uses sub_2c16e40` / `contradict sub_2c16e40 ...` -> `invalid digit found in string` (raw Rust parse error); `contradict -5` and `contradict 0xf2be508` accept nonsense field offsets and answer "no contradictions".

## Limitations observed that the tool does not state

- `port` mostly proves relocation, not change-tolerance: the two builds are almost identical, so only unchanged functions were exercised. The one changed function found (0x3a92e10, 961 vs 818 instructions) was correctly only a `candidate`.
- `port` verdict `derived` rests on string-set equality, size ratio, vcall slots and margin: it cannot separate identical clones when the margin rule is not hit (clone pairs: correct order here, labelled `candidate`).
- `port` loads and indexes the other exe on every call (about 2-8 s); `decide` on a function with ~13 call sites took 7 s in one case and 6 `decide` calls exceeded 200 s together (slow tail, no hang found alone).
- `abi` is only "which registers appear in memory bases / call args"; says nothing about the real prototype, float args, or args used only arithmetically.
- `sigcheck` counts matches only in executable sections and only checks E8/E9 displacement bytes; it is not a stability predictor across builds.
- Not independently verified: `needs` beyond one example, `hookpoints` ranking, `contradict` semantics beyond one case, `uses`, `rw`/`struct`/`system`/`class`, `flow` depth > 1 correctness, second switch in 0xe9759e0, `callers`/`callees` for indirect calls, MCP `batch` content equivalence beyond a smoke test.
- The PDB GUID printed (`...-4C4C-44205044422E`) ends with ASCII "LL DPDB." in both exes: it was patched by the launcher, so it identifies the file but not an official build.
- Created `tools/rdis/names/1.26.62.01.facts.jsonl` (assert + retract lines) as a side effect of testing; it is empty of active facts.
- No rdis.exe processes were left running at the end of testing (checked). Four unrelated-looking `python.exe` processes (PIDs 21372, 5876, 25216, 25328) from an earlier session may remain; they were not killed (kill was refused by the permission classifier).

---
## Fix status (after the report)
Fixed and re-checked: (1) `abi` argument usage now from an exact forward "register still holds entry value" dataflow (0x370f30 -> none, 0xeca3240 -> none, 0x115100 -> a0..a3); (2) `sigcheck` trailing `E8 xx xx xx xx` and `0F 8x` displacements now flagged; (3) data/unmapped addresses refused for sum/cfg/gates/path/choke/decide/anchors/port/abi/flow/hookpoints; interior addresses round to the function start; (4) `port` matches clipped (>60 char) strings by prefix (0xc1ba040 -> 0xc1b9440, derived); (5) `port` trust capped at `hint` when the function has no strings or size ratio < 0.6; (6) missing exe gives a clean error; (8) MCP replies with a -32700 parse error to malformed lines and sets isError for `{"error"...}` results; (7) `contradict` dedupes repeated uses (the flow attribution to a same-expression reload stays: it is the same field value, a documented text-level limit).
Not fixed: `callers` on an interior address still returns none (correct for an interior address, but unannounced) and `callers --max` is ignored; port on no-string functions stays weak by design (labelled hint); 8 vcall slots unverifiable locally; thin independent coverage for needs/uses/rw/struct/class/contradict/deep flow.
Verifier after fixes: seeds 11, 12 at n=200: 0 failures.
