# rdis: expert-derived feature notes and things to keep in mind

Purpose: hand-off notes for the agent building rdis v2 (`tools/rdis`, plan in `docs/RDIS_V2_PLAN.md`).
Source folder: `C:\Users\Atomi\Downloads\New folder (4)` (20 markdown files).

Labels used throughout:
- **[Q]** stated in the expert documents (file named).
- **[I]** my inference or design proposal, NOT in the documents.
- **[U]** in a document I have NOT read in full (T1, T2, I1-I6, README, README2). Read before relying on it.

Read in full: T9, T10. Read partly: I7 (first 150 lines), I8 (first 90 lines), T3/T4 (only the chams and pass-identity passages).

---

## 1. Rules for the tool (non-negotiable)

1. The db is a revisable belief store, not truth. Every fact has a trust level: `proven`, `derived`, `candidate`, `hint`, `agent`/`user`, `unknown`. Agents can `assert`, `retract`, `contest`, `supersede`, ask `why`, and `audit`. [user request]
2. Accuracy over coverage. Anything the tool cannot prove is labelled, never silently assumed. [user request]
3. Layering for any pseudocode: bytes > proven facts > derived facts > hypotheses/names > optional pseudocode. Pseudocode is a view over proven facts and must never introduce a fact. The more the output moves away from raw bytes, the more is interpretation. [I, agreed with user]
4. Wrong evidence looks plausible. A wrong vtable slot usually gives plausible garbage, not a crash (I8 §8a). So every slot or offset claim needs a confidence level and at least one corroborating route. [Q I8]
5. A passing static check is necessary, never sufficient (Floppy, I8: "ida can show a func has no params when its got 20"; matching vtable length is "not a good way of telling"). [Q I8]
6. Static tools must read the exact exe of the running game and print its SHA/PDB GUID. Refuse on mismatch (60.05 vs 62.01 mixup already happened here). [Q T10 W21, I8; user memory `feedback-check-exe-version`]
7. Be explicit about what is NOT modelled: heap memory, calls assumed to return, join merges become `Unk`, RTTI mostly stripped in 1.26.62.01, type-hash call returns the storage/pool and not the component instance.

## 2. Why it should beat IDA / IDA MCP [I]

- Relationships first: callers, gates (exact necessary conditions on the CFG), chokepoints, nearest common callers, field flow.
- Trust labels on every output line and a persistent, revisable overlay journal; IDA names are unlabelled and unrevisable by evidence.
- Speed: xref index cache, about 0.5-0.8 s start; batched MCP calls so an agent asks many questions in one round trip.
- Built for one game and one compiler family: entt hash scan, vtable discovery by code stores, bgfx/RenderDragon knowledge.
- T10 W21 says IDA fails on ~5% of functions, cannot cleanly decompile clang/LTO output, hangs on huge jump tables, and has had SigMaker problems. [Q]
- Caveat from T10 W21: symbolic execution for sigless work can explode in constraints. Keep it bounded and path-based. [Q]

## 3. The chams question: how would an expert know to add ~1000 to the view id?

What the documents say [Q T3 §9, T4 line 113, T9 I-013/S18#4]:
- Make `tryAddActor` fail for chosen actor types so they use the non-batched path.
- Use the `insert` overload taking `RenderActorDescription`.
- Add about 1000 to the bgfx view id on insert.
- At encode, subtract 1000 and swap the bgfx program handle (or give an invalid handle and catch it at the application stage).
- Pitfalls: loses DDRv2 perf for those actors; offset must stay within the fixed view-id cap; encoder code is fork-specific.

What the documents do NOT say:
- How Akashic discovered it. Nothing in T3/T4/T9 explains it.
- T3 open question 6: unverified. Enzo says his redirect-pass method does not work. Test by counting actor draw calls with and without `tryAddActor` failing.

My inference of the reasoning an agent can reproduce [I]:
- Look for a **carrier field**: an integer written at point A, passed through stages that do not interpret it, and read at point B where behaviour branches on it. A free integer with a hard cap (view id) is an ideal tag channel.
- Look for a **marker point** where per-item info still exists (insert with the actor description) and a **decode point** where behaviour is chosen (encode / program bind).
- Look for a **selector gate** that lets you route an item to a different path (`tryAddActor` returning false).
- Tool support: `uses` (field usage profile: writers, readers, compares, passthrough), `path` (A to B), `gates`/`decide` (what condition selects each path), `choke` (single points everything passes through), `common` (nearest common caller of A and B).

## 4. Expert techniques and what rdis needs

| # | Technique | Source | rdis feature |
|---|---|---|---|
| 1 | Read vtable index from `call [rax+disp]`, index = disp/8 | [Q] T10 W3, I7 | `vslot` has it. Add getter decode `mov rax,[rcx+disp]` giving field offset, with proof. |
| 2 | Index from getter prologue; "CODE-PROVEN" with RVA | [Q] T10 W20, I8 | `prove` helper: emit evidence line (`bytes:`/`fn:`) for an offset or index. |
| 3 | Two independent routes must agree (sig result == `vtable[idx]`; same function through 3 classes) | [Q] I8 §8a kind 4 | `corroborate A B`: records both routes as evidence on one fact. |
| 4 | "Still matches but it's the wrong thing": compare match locations across versions; Akashic checks xrefs | [Q] I8 (Brady `shard14:1580`) | `port <exe_old> <exe_new> <fn>`: compare callers, string xrefs, callee shape. **Not built yet.** |
| 5 | Function fingerprint: ordered string xrefs, caller/callee counts, size | [Q] T9 I-065 | Extend `anchors` with scoring against a second exe. |
| 6 | Re-find via strings inside or around the function xref (loud) | [Q] I8 | `anchors` (done in part). |
| 7 | Vtable shape: length plus `__purecall` positions | [Q] T9 I-067 | Shape signature in `classes`. |
| 8 | entt hash finder: `BA <fnv1a32> E8` | [Q] T9 I-068 | Done (`comp`). |
| 9 | Component size from `imul rax, imm` after assure (Brady `mcbe_dump.py`) | [Q] T9 I-069 | Add size recovery. T10 W6: size mismatch breaks even when hash matches. |
| 10 | Zero-size tag components | [Q] T9 I-069 (S11#8) | Flag in `comps`. |
| 11 | MSVC vs clang hash format (`__FUNCSIG__` vs `__PRETTY_FUNCTION__`) | [Q] T10 W6 | `comps` should say which name form matched. |
| 12 | System access dump: Read/Write/AddRemove per system; find who writes a component | [Q] T9 I-082 | Per-function reader/writer split for a component; walk the system registry. |
| 13 | View-name array in the d3d12 bgfx context (first 0x10000 bytes); key on names not ids | [Q] T4 line 12, I3 | Pass-identity reader (see memory `bluey-pass-identity`). |
| 14 | Debug-assert strings (path, signature, line) name functions | [Q] T9 I-071 | `strnames`: string-to-function naming pass. Check first whether this build still has assert strings (T10 open Q5). |
| 15 | Getter emulation: run first instructions, read `[rcx+X]` | [Q] T9 I-080 | Expose symbolic executor as `emulate`. |
| 16 | Build identity: PDB RSDS GUID + age, plus TimeDateStamp/SizeOfImage | [Q] I8, T9 I-074 | Print in `info`; refuse mixed exes. |
| 17 | Behavioural proof at runtime: hook the slot, do the action | [Q] I8 kind 5 | Static + live join with Cheat Engine MCP. **Not done.** |
| 18 | Neighbour-slot diagnosis: call runs but wrong behaviour means suspect off-by-one (loud) | [Q] I8 | `vslot --neighbours`: show n-1, n+1 with prologue shape. |
| 19 | Hidden return pointer: RCX for free functions, RDX for members; only POD 1/2/4/8 bytes return in RAX | [Q] T10 W5 | Flag per function from first instructions as `derived`. |
| 20 | Sig quality rules: 24-80 bytes, concrete first byte, ends at or before `ret`, no `CC` padding, wildcard rip-relative and call targets, unique match | [Q] T10 W1/W2, checklist 2-5 | `sigcheck`: lint plus uniqueness over the exe. |
| 21 | ICF (identical code folding): one body, many symbols; a sig may match a shared body | [Q] T10 W2 | Mark folded functions (same bytes, many callers). |
| 22 | Inlining check: a hook target must be out-of-line with known callers | [Q] T10 W10 | `callers` count plus "is probably inlined elsewhere" hint. |
| 23 | Tiered anchors: string xref, neighbour sig plus offset, vtable index from a call site | [Q] T9 I-064 | Combine into `resolve <name>` that tries each tier and reports which matched. |
| 24 | Instruction-pattern follower DSL: `start vfunc N, follow 5th call, follow first lea, preceding(comiss)` | [Q] T9 I-066 | `follow` command with steps. |
| 25 | Fog colour found via 0.94/0.06 float constants | [Q] T9 I-015 | Constant search (`consts`) over `.text` and `.rdata` floats. |
| 26 | Find class by vtable length and virtual shape on BDS-like symbol-rich builds, transfer names by strings | [Q] T9 I-070, T10 W20 | Name transfer only by strings/call structure. BDS/Android/Levi indices are hints to verify, never truth. |
| 27 | Terrain-draw heuristic (hundreds of calls means terrain) | [Q] T9 I-085 (S24#6) | Call-count profile for render submit. |
| 28 | Thread affinity of functions (main vs render) | [Q] T10 W7 | Hint only; needs runtime evidence. |
| 29 | Jump tables: huge ones hang IDA | [Q] T10 W21 | Verify rdis jump-table recognition with a switch-hunt option (still unverified). |

## 5. Tested against ground truth (1.26.62.01, after v2 build)

Tested against `docs/BGFX_MAP.md` (hand-derived by disassembly) and results recorded here:
- Jump tables: verified (see `docs/RDIS_V2_PLAN.md` section 7); the switch-hunt option is on by default in `verify.py`.
- `path 0x67c9c20 0xc273420`: 2 hops `0x67c9c20 -> 0xc270460 (site 0x67ca3cd) -> 0xc273420 (site 0xc270521)`, trust proven. The gate on the second hop is `*u8(a0+0x35) == 0`, which is exactly the documented early-out `cmp byte [this+0x35],0` (BGFX_MAP 6n). `choke` returns `0xc270460` as the only chokepoint. MATCHES the notes.
- `path 0x66232b0 -> 0x67c9c20` finds nothing even with `--virt cand`: `vcalls 0x66232b0` shows the calls go through `*(&data_1233e1a8)` slots, "object class not determinable". Correctly reported unknown; resolving it needs `assert global-type` or a runtime observation. This is the concrete gap behind the planned static+live join.
- `sum 0x4e39cb0` shows a virtual call at slot 111 = `[rax+0x378]`, which is the documented Item-group `_insert` slot (+0x378). MATCHES.
- `decide 0x6ebb280` (found by the `tryAddActor` signature in Sigs.json): one caller, `0x53e1160`, branches on the returned byte at `0x53e1b73`. So the tool independently reproduces "tryAddActor is the lever". But the caller is a loop and both outcomes rejoin shared code (5 predecessors each), so `decide` cannot yet say what each outcome does; by hand, the not-taken side falls into a vector growth (`sar rcx,4`, 16-byte elements) i.e. a push to a fallback list. LIMIT: outcome attribution inside loops needs inline-store attribution beyond the first block.
- `info` now prints build identity: file size, TimeDateStamp, SizeOfImage and PDB RSDS GUID/age. The GUID tail spells `LLD PDB.`, so this build is linked by lld-link (clang toolchain): consistent with the clang/LTO notes.
- Added `needs <A> <B>` (per-function gate lists along a path, contradiction detection only inside one function) and outcome attribution in `decide` (calls and memory writes that cannot run unless a given branch edge is taken).

Still unverified or not built: `--virt derived` chains through global objects, cross-build porting, interprocedural field flow, static+live join, `comps` size recovery.

## 6. Documents not yet read (do before trusting related items) [U]

`T1_sigs_updateday.md` (section 8 entt discovery), `T2_hooking_sdk.md`, `I1`-`I6`, `README.md`, `README2.md`. Also the long lines in T3 (11, 13, 83, 245) were omitted by the grep and not read.

## 7. Suggested build order [I]

1. Safety first: item 16 (identity), 20 (sig lint), 19 (ABI flag).
2. Evidence: 1, 2, 3, 18 (slot proof with neighbours and corroboration).
3. ECS: 9, 10, 11, 12.
4. Relationships for the chams-style question: `uses` carrier discovery plus `path` with derived virtual edges, tested on `docs/BGFX_MAP.md` ground truth (insert clone `0x4e39cb0`, callers `0x6ebb510`/`0x4e355a0`, encode chain `0x66232b0` to `0x67c9c20` to `0xc270460` to `0xc273420`).
5. Cross-build `port` (item 4) and runtime join (item 17).
6. Optional: pseudocode view, only as a labelled layer over proven facts.

## 8. Policy notes from the documents [Q]

- T9 dropped ideas that give unfair advantage on public servers (xray, ore/storage ESP, through-wall reveals, reach/hitbox, automation). Keep this in mind when building tool examples.
- T10 W22: read-only/visual features are low risk; anything writing input or packets risks the account.
- T9: the community penalises low-effort AI-built showcase projects (phase, 2026-10-06).
