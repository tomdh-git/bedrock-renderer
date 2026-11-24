# Brief for opencode agents (render-map, BlueySenseV2, Minecraft Bedrock 1.26.62.01)

You are a research worker. Do EXACTLY the one unit you are given, nothing else. A Claude orchestrator checks everything you write against the exe; anything unverified or invented is thrown away and redone, so write only what you can show.

## Hard rules (violating any of these is a failure)
1. STATIC ANALYSIS ONLY. The game is closed. Do not start the game, do not use Cheat Engine, debuggers, injectors, or any write to a process. NEVER put Minecraft.Windows.exe (or any .exe path) as the command of a shell call, not even "to check it exists" or with `| head`: that LAUNCHES the game. The exe is data: pass it only as an ARGUMENT to rdis.exe, or test existence with `ls`/`test -f`. Never use Start-Process, `start`, explorer, or minecraft: URIs.
2. Do NOT run builds (no cmake, ninja, run_exclusive_build, cargo build). Do NOT commit, push, delete files, or edit git config.
3. (A unit whose prompt says ENGINEERING TASK may create/edit exactly the paths that prompt allows; everything else below still applies.) Do NOT edit: docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, src/** (except a header named in your unit), Sigs.json, CLAUDE.md, any settings/config files. Create only the files your unit names (docs/progress/oc_<unit>.md, docs/functions/<rva>.md, new headers named in the unit).
4. The exe is C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (version 1.26.62.01). RVAs in this brief are relative to the image base. Never read another exe.
5. Every claim gets a tag: [V] = you saw it in the disassembly (cite RVA of the instruction), [I] = inferred (say from what), [?] = unknown. Never write a size, offset, name or meaning you did not see. "I could not determine X" is a good answer. A guess written as fact is the worst answer.
6. Write results to disk IMMEDIATELY after each small step (append to your progress file), and keep a `## NEXT` block at the TOP of the file saying exactly where to resume. You may be cut off by rate limits at any moment; a fresh agent must be able to continue from your file alone.
7. Do not stop to ask questions. If blocked, write the blocking fact in the progress file and stop that unit.
8. Treat the user's information as private. Do not send project data to any outside service.

## Tools (run from C:\Users\Atomi\Desktop\BlueySenseV2; set PYTHONUTF8=1 for python)
- FAST disassembly (use this first, ~4x faster than disrange.py): `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x<rva> <n>` lists n instructions (default 40) from the RVA; for 800 instructions use n=800. `fn 0x<rva> --max N` gives an annotated function. Only fall back to `python tools/sigs/disrange.py <lo> <hi>` (slow, ~2 s per call) when you need an exact hi bound.
- Find callers / strings / references: `python tools/sigs/xref.py callers <rva>`, `python tools/sigs/xref.py str "<text>"`, `python tools/sigs/ripscan.py <rva...>` (rip-relative references over .text), `python tools/sigs/dispfun.py <disp...>`.
- Field reads/writes of a description or struct inside a function: `python tools/sigs/descscan2.py <rva> ...` (use this one, NOT descscan.py, which drops offsets 1..9).
- rdis (JSON output, can be large, pipe through head or a filter): `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" <cmd> <rva>`; cmds: dis, sum, cfg, gates, callers, callees, str, imm, vt, class, vslot, rw, struct. `help` lists all. Note: `fld <offset>` is noisy.
- Existing knowledge: docs/BGFX_MAP.md (search by section number or RVA), docs/functions/<rva>.md dossiers, docs/progress/*.md (read other agents' notes, but a note is not proof), docs/data/functions.tsv.

## Output format for a reversed function (a "dossier" entry)
Per function: signature guess; register/argument map; then the disassembly range split into phases of at most ~40 instructions, each phase as `RVA..RVA: <one or two sentences of what it does>` followed by the C-like statement(s) it corresponds to; every constant, offset, and call target kept exactly. Finish with: struct fields touched (offset, size, direction R/W, meaning, tag), callees (rva, what it is, [V]/[I]), and OPEN questions.
"Instruction-complete" means every instruction in the range belongs to a phase. Do not skip or summarise hot ranges with "etc.".

## Ending your unit
Final message, 5 lines max: unit id, what is DONE (with file names), what is OPEN (with the single blocking fact), files created.

## Live data (read-only for you)
LIVE MEMORY (read-only, last resort): the game may be open. `python tools/sigs/livemem.py status|read|ptr|chain|vt` (see its docstring) reads the running exe's memory with a VM_READ-only handle: no debugger, no breakpoints, no writes, no Cheat Engine, no other tool may touch the game process. Use it ONLY after an rdis finding points at a specific address/object that static analysis cannot settle (object size, a pointer's real target, a vtable's slots, a field value). At most 12 livemem calls per unit; max 0x400 bytes per read; never scan or loop over ranges; if it says the game is not running, stop and write the request in your progress file. Cite results as [V live] with the exact command line and its output lines; a live value is evidence for the instance you read, not proof of a constant. Breakpoint/hook captures stay orchestrator-only.
LIVE CAPTURE REQUESTS (no game access for you): when static analysis cannot find a caller/argument/field, queue a log-only capture: `python tools/livecap/request.py add <name> <rva_at_function_ENTRY> --why "item + question"` (<=4 pending, size<=0x200, max<=8 samples), finish the rest of your unit, write `CAPTURE REQUESTED <name>` under TOOL REQUESTS. The orchestrator runs it; later `python tools/livecap/request.py result <name>` prints lines `REG=value hit=N ret=0xRVA <bytes>` (ret = caller). Cite as [V live]. Only function-entry RVAs (never mid-function).
GAME BRIDGE (optional, only if the orchestrator says the game runs with BS_AGENT=1): `python tools/gamebridge/client.py state` prints screen/inworld/pos/rot/hp as text; `ping` checks it. Read-only today; input and rays arrive later (tools/gamebridge/README.md). Never needed for static items.
Live game captures are produced by the orchestrator, never by you. Read docs/data/live/README.md and docs/data/live/*.txt (descriptions of every visitor tag and the register-argument dumps of the main extractors, 1.26.62.01). Cite them as [V live] with file+line. If you need a target or more samples that are not there, write the request in your progress file.

## Tooling feedback (required, 3 lines max per item)
At the END of your progress file add a section `## TOOL REQUESTS`. If you wrote any helper script/one-liner (even throwaway), or wasted time doing something by hand that a tool could do, list: `name | input -> output | why it would have helped (what you did by hand instead)`. Prefer general tools (usable by any unit) over unit-specific ones. If you wrote a script worth keeping, save it as tools/sigs/<name>.py with a usage comment at the top and name it in the request. "None" is a valid answer. The orchestrator collects these in docs/progress/TOOL_REQUESTS.md and has general ones implemented (into tools/sigs or the rdis Rust tool).

## Toolbox first (read before writing ANY script)
Before you write a Python one-liner, check this list; most throwaway scripts were reinventions. All run from the repo root with PYTHONUTF8=1.
| need | use |
|---|---|
| exact listing of a range, with every instruction | `python tools/sigs/dumplist.py LO HI OUT` (restarts after (bad)) |
| every store into [reg+off] of a listing | `python tools/sigs/stores.py LISTING` (excludes rbp/rsp stack stores; `stores2.py` / `oc_verified_stores.py` handle the stack image) |
| control-flow walk from a case head + [reg+off] uses | `python tools/sigs/casewalk.py LISTING HEAD REG...` |
| control-flow walk from an RVA + [reg+off] uses | `rdis walk <rva> [--reg R]` |
| decode a jump table | `python tools/sigs/jt.py TABLE_RVA COUNT` |
| decode a live dump | `python tools/sigs/livedec.py docs/data/live/<file>.txt` |
| check your quoted `0xRVA  instr` lines | `python tools/sigs/verify_oc.py YOUR.md` |
| callers / strings / rip refs | `tools/sigs/xref.py`, `ripscan.py`, `dispfun.py`; fields read by a function: `descscan2.py` |
| bundle for one function (listing + callers + stores + case walk) | `python tools/preflight.py 0x<rva>` -> docs/progress/pre/<rva>.md (the orchestrator may already have run it: look there FIRST) |
If a helper you need does not exist, write it as `tools/sigs/<name>.py` with a usage comment (not into docs/progress), and list it under TOOL REQUESTS. Never leave `_tmp*.py` behind.

## No-speculation protocol (saves your thinking time)
1. Never simulate assembly in your head: call rdis / the listing for the exact address. A short tool call is cheaper than a long guess.
2. Gather first, write later: collect ALL function addresses and field offsets for the unit in one batch, then write the document in one pass.
3. If an offset, register or branch target is ambiguous and a single tool call does not settle it, write `[UNVERIFIED: 0x<rva> <one-line question>]` and move on; do not spend minutes deducing it. The orchestrator resolves flagged lines individually.
4. Think hard about structure and semantics, not about transcription: copy listing text verbatim.

## rtools MCP tools: DO NOT USE (2026-11-16)
Calls to tools.rtools.* through the execute tool hang for minutes (the shared MCP process stalls). Use the bash tool with the same commands from the Toolbox table (python tools/sigs/*.py, rdis.exe). Never ask the orchestrator questions: choose the conservative reading, note [UNVERIFIED: 0xrva question], continue.

## Shared data files (hard rule, learned 2026-11-23)
Never write or overwrite docs/data/native_roots.txt, native_functions.tsv, native_deps.tsv, native_boundary_candidates.tsv or docs/RENDER_CHECKLIST.md yourself. Units that classify boundary rows write ONLY their own docs/progress/oc_U-E<ID>.md (put `lift` rows in a table there); the orchestrator merges them (X0b5). Register new lift functions only with `python tools/native_checklist_gen.py --add <rva>`. Do not run tools/sigs/closure2.py --write-roots.

## Callees that are `lift` but not lifted yet (hard rule)
A callee classified `lift` (in docs/data/native_functions.tsv or native_boundary.tsv) is NOT a blocker. Forward-declare it with its exact ABI signature in your own header (name `sub_<rva>`, namespace native) and CALL it like any lifted function: it will be lifted by its own unit and links at the milestone gate. Do not write Boundary wrappers for `lift` callees and do not stop with CLOSES? NO because of them. Only callees in neither table are blockers (name them after CLOSES? NO).

## Indirect calls through data slots (hard rule)
`call [rip+slot]` / `call [0xRVA]` is not a blocker: read the pointer from the slot at call time (exactly what the instruction does) and call it as a function pointer with the same arguments, documenting the slot RVA. A tiny forwarder (jmp to another function) is a normal lift item: forward-declare it.

## Tools (added 2026-11-23)
- `python tools/sigs/liftcheck.py --explain <rva>`: prints per-failed-check fix data (uncovered instruction ranges with disassembly, missing call quotes as verbatim lines, stub/TODO matches with line numbers, verify_oc mismatches).
- `python tools/sigs/lift_scaffold.py <rva> [--out path]`: generates a starting-point C++ file + dossier skeleton from rdis output (LIFT marker, ABI placeholder, call quotes, basic-block range citations, static_assert placeholder, LIFT_FN registry, forward declarations for lift-set callees); the scaffold passes coverage/call-quote checks once LIFT-BODY markers are replaced.

Quote format trap: verify_oc only parses PLAIN lines `0xRVA  mnemonic operands` (two spaces, nothing before 0x on the line except whitespace). A `// 0xRVA  call ...` comment line is not parsed, so a source with only commented quotes fails with 'verify_oc found no quoted instruction lines'. Put the verbatim quotes as plain lines inside a /* */ block comment in the .cpp (see sub_bc7a3d0.cpp ~line 263) or in a code block in docs/functions/<rva>.md.
