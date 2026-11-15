# rdis v2: relationship-first binary analysis for agents

Goal: an IDA-MCP-class tool where an agent (or developer) can ask *relationship* questions about the game exe and get answers whose every
claim says how it is known. Target: Minecraft.Windows.exe (1.26.62.01 first), x64 PE, MSVC, PGO/LTO-style code, **mostly stripped RTTI**.

## 0. Findings that shaped the design (measured, not assumed)

- Only ~1241 `.?AV` type descriptors exist, nearly all std/webrtc/lambda binders. `Actor`, `Player`, `ClientInstance` have none.
  So: RTTI is parsed (strictly) but **class identity is the vtable**; names come from evidence or from the agent.
- ~944 `__cdecl` function-signature strings and `al::pretty_function() [Type = X]` strings exist. They name *things referenced by* a function,
  not necessarily the function: they are **hints**, never facts.
- ECS component type hashes (FNV-1a 32 of the type name) appear as immediates; names are recoverable from strings that embed type names.
- `.pdata` covers almost all non-leaf code; leaf getters are missing (extent heuristics must be explicit about being heuristics).

## 1. Trust model (the accuracy contract)

Every statement the tool prints carries a `trust`:

| trust | meaning | example |
|---|---|---|
| `proven` | read directly from bytes by a deterministic rule; reproducible | `call` target of a `E8` instruction, a jump-table entry, a COL that validates |
| `derived` | follows from proven facts by a sound rule; evidence addresses attached | "edge C->T is on every path to the call" (removal makes the call unreachable) |
| `hint` | plausible, not sound | funcsig string referenced by a function |
| `agent` / `user` | asserted through the overlay, with evidence and a note | `name 0x.. = Actor::tick` |
| `unknown` | the tool could not decide; says why | unresolved indirect jump, unknown vcall class |

Rules: the tool never upgrades a hint to a fact. Anything it cannot prove is reported as `unknown` with the reason, never guessed.
A verifier (section 5) independently re-reads the binary and checks the `proven`/`derived` claims.

## 2. The db is a revisable belief store, not the truth

Two layers:

1. **Derived layer** (recomputed from the binary, deterministic, never hand-edited): functions, xrefs, vtables, RTTI, strings, component hashes,
   CFGs, summaries. Memoised, keyed by `(binary stamp, pass version, overlay epoch)`.
2. **Overlay** (`names/<ver>.facts.jsonl`, append-only journal): agent/user assertions and retractions.
   `{id, ts, op, kind, subject, value, trust, source, evidence[], note, supersedes?}`.

Operations: `assert` (new belief), `retract <id>` (withdraw), `contest <derived-fact-key>` (say a derived/hint fact is wrong: it is suppressed and dependents recompute),
`supersede <id>` (replace with new value, keeping history), `why <subject>` (full evidence chain, who said it, what it overrode), `audit` (re-check evidence of
every active overlay fact against the binary and flag the ones that no longer hold), `facts` (query), `export`/`import`.

Fact kinds: `name`, `comment`, `class` (vtable -> class name), `vtable-slot-name`, `struct`/`field` (type, offset, size, kind, name), `edge` (add a call edge, e.g. a vcall
target) and `no-edge` (deny a derived edge), `component` (hash -> name), `note`.
Every derived pass reads the **resolved view** (derived facts + overlay), so revising a fact changes later answers; summaries/paths are memoised against the overlay
epoch, so a revision invalidates exactly what depends on it (coarsely: everything, then recomputed lazily).

## 3. Architecture

```
main.rs      CLI + MCP stdio server (JSON-RPC 2.0: initialize, tools/list, tools/call); stdout capture so old text commands work over MCP
pe.rs        image, sections, .pdata, strings            (existing)
index.rs     xref index                                   (extended: data pointers, vtable-slot refs)
db.rs        overlay journal, resolved view, why/audit
cfg.rs       basic blocks, edges, conditions, strict jump tables, necessary-edge gates
sym.rs       symbolic executor: expression values, stack slots, joins; events (loads/stores/calls/branches)
model.rs     vtables/classes/RTTI, component hashes, string hints, call graph with edge kinds, path/rw/struct queries
```

Commands (CLI and MCP tool names are identical; results are JSON; `--max`, `--offset` page everything):

`fn dis xr callers callees str fld imm comp ptr vt find sec` (kept) and new:
`sum` (symbolic summary) `cfg` `gates` `path` `reach` `classes` `class` `vslot` `vcalls` `rw` `struct` `system` `assert` `retract` `contest` `why` `facts` `audit` `verify`.

## 4. Semantics of the new analyses (exact)

- **Function extent**: `.pdata` primary range (+ chained fragments). Non-`.pdata` entries use a CFG-closure from the entry and say `extent: heuristic`.
- **CFG**: leaders = entry, branch targets, fallthrough after branches/ret/jmp. Edges: fallthrough, `jcc` taken/not-taken, `jmp`. A `jmp` out of the function is a tail call.
  Indirect `jmp` is resolved only through a **strict jump-table** match (bounded by a `cmp reg, N; ja default` that dominates it and a table whose every entry lies in the function);
  otherwise the block is marked `unresolved-indirect`.
- **Condition**: the `cmp`/`test`/`sub`/`and`... flag setter immediately feeding a `jcc` (same block, no flag clobber between) rendered with symbolic operands; otherwise `unknown-flags`.
- **Gates of a block B**: conditional edges e such that deleting e makes B unreachable from entry. This is exact (necessary conditions), not a heuristic.
- **Symbolic values**: `Arg(n)`, `Imm`, `Load(expr, size)`, `Ret(call-ip)`, `Add/Sub/And/Or/...`, `StackAddr(off)`, `Global(rva)`, `Unknown`.
  Stack slots (`[rsp+x]`, `[rbp+x]` with tracked frame) hold values; at a CFG join, slots/regs that differ become `Unknown` (never merged optimistically); loops: values written in the loop become `Unknown` at the header.
  Calls clobber volatile registers; the return value is `Ret(ip)`. Memory writes are not alias-analysed: a store through an unknown pointer does **not** kill tracked stack slots only if the store base is provably not the stack (otherwise the slot facts are dropped).
- **Virtual calls**: `call [E+slot*8]` where `E` is `Load(X, 8)` (a vtable pointer of object X).
  - `proven`: the same function stored a vtable address into `[X+0]` on every path to the call -> the target is that vtable slot.
  - `candidates`: otherwise, if the function is itself in vtable V (so `Arg0` is a V-or-subclass instance) and `X = Arg0` -> targets are slot `s` of V and of every vtable whose slot-by-slot prefix contains V's functions (declared as `candidate`, with the set listed).
  - else `unknown(class)` and the overlay can `assert edge`.
- **Components (ECS)**: an `imm32` equal to the FNV-1a hash of a known component name, passed to a call, tags the call's `Ret` as `Comp(name)` (trust `derived`: rule "hash passed as argument"; the verifier checks the rule, not the engine's semantics). Field accesses through that value are `Comp(name)+off`.
- **rw/struct**: field accesses are grouped by a type key: `Comp(name)`, `Class(vtable)` (this of vtable functions), else `anon(root-expression)`. `struct` aggregates offset, size (from operand width), kind (float/ptr/int/vtable), R/W counts and the functions.

## 5. Verification plan

1. `tools/rdis/verify/verify.py`: independent of Rust. Parses the PE by hand (`struct`), disassembles with capstone, and re-derives: pdata function table, direct call targets,
   vtables (pointer runs + the lea/store evidence), RTTI, jump tables, CFG edges and conditions for sample functions, imm/field hits.
   It compares them to `rdis ... verify`/JSON output and fails on any difference.
2. Scenario tests: fixed questions with **expected answers established by reading the bytes** (hex-dump + manual decode written into the test as comments).
3. Negative tests: the tool must answer `unknown` where proof is impossible (indirect jump without bound, vcall with unknown class).
4. Results are recorded at the bottom of this file.

## 6. Checklist

Legend: [ ] todo, [x] done and verified.

### A Foundation
- [x] A1 stdout capture so every command works over MCP
- [x] A2 JSON results for new commands, uniform `{ok, trust, data, truncated, next}` envelope
- [x] A3 MCP stdio server (initialize / tools/list / tools/call), exe + db loaded once
- [x] A4 paging (`--max`, `--offset`) on all list outputs

### B Revisable db
- [x] B1 fact model + trust levels
- [x] B2 append-only journal, ids, timestamps
- [x] B3 assert / retract / contest / supersede
- [x] B4 resolved view (precedence user > agent > derived > hint), consumed by names and passes
- [x] B5 `facts`, `why` (evidence chain), `audit` (re-verify evidence)
- [x] B6 epoch invalidation of memoised derived data
- [x] B7 import of the existing flat names file

### C Derived passes
- [x] C1 function table (+ explicit heuristic extents)
- [x] C2 strict RTTI parse
- [x] C3 vtable discovery with constructor-store evidence
- [x] C4 string hints (funcsig / pretty_function) marked as hints
- [x] C5 component hash table from names in strings
- [x] C6 xref index with data pointers / vtable slots

### D CFG
- [x] D1 blocks + edges
- [x] D2 strict jump tables, `unresolved-indirect` otherwise
- [x] D3 conditions from flag setters
- [x] D4 gates (necessary conditional edges)

### E Symbolic summary
- [x] E1 expression engine, registers and stack slots, joins
- [x] E2 events: loads, stores, calls, vcalls, branches, returns with ip provenance
- [x] E3 `sum` output

### F Relationships
- [x] F1 vcall resolution (proven / candidates / unknown)
- [x] F2 call graph with edge kinds
- [x] F3 `path A B` (with gates per hop), `reach`
- [x] F4 `rw` field producers/consumers
- [x] F5 `struct` inference, `class`, `classes`, `vslot`
- [x] F6 `system` (components touched with field offsets)

### G Verification
- [x] G1 independent python verifier
- [x] G2 scenario tests with manually derived expectations
- [x] G3 negative tests (`unknown` where required)
- [x] G4 results recorded below

### H Docs
- [x] H1 update memory file + tools README

## 7. Results (1.26.62.01)

**Independent verifier** (`tools/rdis/verify/verify.py`, own PE/.pdata parse + capstone, different algorithms where cheap): n=300, seeds 5 and 6, 331 functions each, 0 failures. Per run: ~7-10k block-end/edge checks, ~15-23k field-access r/w checks, 3.7-5.3k branch conditions (op, negation, flag setter along the single-predecessor chain), 240 gates (exact), 458 vtable slots, 839 vtable lea/store evidence pairs, 397 RTTI col/name/link checks, 14-17 call paths hop-by-hop. Seeds 1-4 at n=150 also clean after fixes.

**Bugs the verifier found in rdis (all fixed):** jump-table targets that were not block leaders (entry count right, table dropped; now the CFG is rebuilt with those leaders); table base set outside the switch block (now a backward reaching-definition walk, must be one single `lea [rip+X]`, volatile registers refuse across calls); switch behind another switch (retried to a fixpoint); two-level switches (`movzx byte` index table then dword table) and the `movsxd` copy before the bound; scan fallback for switches with no `cmp` bound; RTTI mangled names truncated at 300 chars.
**Bugs found in the verifier itself:** capstone reports eflags=0 for rip-relative `test`/`cmp`; flag-setter "between" check was linear instead of along the predecessor chain; command line too long at n=300.

**Manual proof against raw bytes:** `0x2c16f3d` switch: read the 24 dword entries straight from the file at `0xf167c50` and all 24 targets equal rdis's case map; `cmp r9,0x17` bytes `49 83 f9 17` confirm the bound. `gates 0x2c16e40 0x2c16f49` matches hand reading of the entt sparse-set lookup (hash `0x78D05959`) and the `jmp r9` dispatch.

**Scenarios run:** MCP over stdio (initialize, 38 tools, tools/call, batch, unknown method error); db: assert with evidence, malformed/false evidence rejected, supersede, retract, contest, why, audit (a malformed item now counts as broken); `sum 0x1` returns "no decodable code", a panic anywhere returns a JSON error instead of crashing.
**Negative results reported as unknown, correctly:** `path 0x66232b0 0xc273420` has no path (virtual dispatch through unnamed globals needs `assert global-type`); `uses 0x1c` in a heap-heavy function returns reads but no profile, because memory is not modelled.

### Known limits (not hidden)
- Jump tables placed inside the function's own range (e.g. `0xe9759e0`): block-level comparison is skipped in the verifier, code bytes there are data.
- A switch whose base register is only reachable through another unresolved indirect jump: predecessor-less blocks are ignored in the reaching-def walk (documented unsoundness; the result is still labelled with its bound kind).
- No heap modelling: conditions show `?` for values loaded from memory. No type propagation across calls. entt `typed<>` is a pool, not an instance.
- Calls assumed to return; indirect calls only resolved by vtable evidence or an agent `global-type`.
- Single build only; no cross-build matching.

## 8. Next phase (priorities from review; decompiler explicitly deferred)
A decompiler, if ever built, is a read-only view over proven facts and never a source of truth.
1. Cross-build `port`: match by `anchors` fingerprint (strings, callee fan-in, type-hash immediates, installed vtable, size), verify caller set and string xrefs ("still matches but wrong thing"), carry facts with trust downgraded to `candidate`.
2. Static+live join: import Cheat Engine observations (vcall targets, vptr values, field write sets) as `observed` facts.
3. Interprocedural field flow (args and stores) so the carrier question ("+1000 on the view id") is answerable: reader profile on every function on the path.
4. `needs <A> <B>`: conjunction of gates along a whole path, with the contradictory-gate case reported.
5. `contradict <fact>`: hypothesis checking; list every reader/writer that treats the field differently.
6. Speed: persist the xref index per build + regression benchmark.
Then `hookpoints`, `investigate <goal>`, `surprises`, `recipes`, `corroborate`, build-identity check (refuse mixed exe versions), `emulate`, `abi`.
The +1000 reasoning has no source in the expert documents beyond one quote; the carrier-discovery shape (written at A, carried through a stage that does not interpret it, read at B) is our inference and is labelled as such.

## 9. Second pass (expert-notes tools)
Added: `info` build identity, `needs`, `decide` outcomes, `port`, `abi`, `sigcheck`, `hookpoints`, `flow`, `contradict`, `comp` size candidates (built, not yet independently tested). Independent test by a separate agent: docs/RDIS_TEST_REPORT.md (13 bugs, fixed list at its end). Chams investigation: docs/RDIS_CHAMS_INVESTIGATION.md. Still not built: static+live join, `investigate`, `surprises`, `recipes`, `corroborate`, name transfer.

## 10. Third pass: subsystem-scale tools (for the full bgfx / RenderDragon / FrameBuilder reverse)

Fixed leftovers: `callers` honours `--max` and explains an interior address; `flow --field` attributes a use to the nearest preceding read of the field; `port` anchors string-less functions through neighbours with unique strings (0xbfcae00 -> 0xbfca200 now correct; clone families such as 0x4633060 stay `hint`).

New commands:
- `gobj <global>` / `gobj --fn F [--depth N] [--apply]`: what object lives in a global slot. Routes: constructor call on the allocation, vtable-installing producer, vtable stored into the global, address of a static object whose vtable is in the file image, static initial value of the slot. Several classes (a slot switched at runtime) give trust `candidate` and a comma list; `--apply` records `global-type` facts.
- Static vtables: vtable discovery now also takes qwords in writable data that point at read-only tables whose first entry is code (objects laid out by the linker, no constructor). They carry no constructor evidence.
- `constructs` edges in `path/reach/choke --virt cand|slot`: a function that installs a vtable (<= 12 slots) gets an edge to each slot. This is how callbacks, std::function bodies and queued tasks become reachable.
- `ptables`: arrays of code pointers in data (also strided records), vtables excluded.
- `structm <fn>`: one field table merged over the call tree that passes a0 / a0+K by direct calls; type guesses; child objects.
- `worklist <fn...>`: reachable functions with named/unnamed, string anchors and unresolved-virtual-call counts (the measurable remaining work).
- `observe vcall|global|import`: runtime observations as trust `observed` (outranks static inference in `vcalls`/`path`).
- `portfacts <other-exe>`: `port` over every named function.

Ground-truth results (1.26.62.01):
- `vcalls 0x66232b0` (BgfxFrameBuilder::endFrame): 53 unknown before; after `gobj --fn 0x66232b0 --apply` all 53 are `candidate` with two classes each. The two globals (0x1233e1a8, 0x1233e1b0) are switched in 0x9d8770 by `lea rax,[static object]; xchg [global],rax` between static objects whose vptrs are in the file image (0xf09ef70/0xf09f000 and 0xf09efb0/0xf09f040): an interface with two implementations chosen at runtime (the calls pass sizes 0x18/0x30, so it looks like the allocator; that reading is a hint).
- `path 0x66232b0 0xc273420 --virt cand` now returns the documented chain `0x66232b0 -constructs(0x662d7ff)-> 0x67c9c20 -call-> 0xc270460 -call-> 0xc273420`; before this pass there was no path in any edge mode.
- Verifier after all changes: seeds 21, 22 at n=200, 0 failures.

Independent test of this pass: docs/RDIS_TEST_REPORT_2.md.

Still not built: `investigate`, `surprises`, `recipes`, `corroborate`, automatic Cheat Engine capture (only the import side, `observe`, exists), heap/alias model, type propagation through returned pointers.
