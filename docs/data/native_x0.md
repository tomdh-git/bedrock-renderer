<!-- NATIVE -->
# Native render checklist: every render function lifted to our own verified source, then run as our own code

<!-- STATUS:BEGIN -->
<!-- STATUS:END -->

Goal and definition of done: `docs/RENDER_DONE_STATE.md`. How a function is lifted, what "done" means per item, file layout, ABI/STL/boundary rules: `docs/RENDER_NATIVE_SPEC.md`. Live verification: `docs/NATIVE_VERIFY_PROTOCOL.md`. This file replaces the reversal checklist (kept as `docs/RENDER_CHECKLIST_V1.md`; its dossiers, headers and data are the inputs here).

Generated part (X1-X5): {{NFUNCS}} functions, {{NBYTES}} of machine code, from the direct-call closure of the render roots (`tools/native_checklist_gen.py`; the closure is NOT complete until X0a is done: indirect callees are added then, as X7 items). Order inside each milestone = callees first, and `docs/data/native_deps.tsv` makes `tools/nextitems.py` hand out an item only when every callee in the set is already [x].

## How an item is closed (short; full rules in the spec)
An item is [x] only when `python tools/sigs/liftcheck.py <rva>` prints `LIFTCHECK OK`: every instruction of the function lies in an address range cited by the source/dossier and every call is quoted verbatim (verify_oc mismatch=0), the C++ lives under `src/client/features/render/native/`, every call is to a lifted function or a listed boundary function, every struct offset used is asserted, and the registry entry (Shadow/Verify/On) exists. Items are statically complete when ticked ("L1"); live verification ("L2", zero divergence in the scenes) happens at the milestone gate Xnz and by the user. A stub, a subset, a [?] in the code, or a hook that stands in for the function is NOT [x].

Legend: LIFT = write the function. PLAN/CHUNK/ASSEMBLE = big function (> 0x1800 bytes): plan the split at basic-block boundaries, lift each chunk, assemble. Items ending in `z` are gates owned by the orchestrator. XO items (optimization) are not started before X6z.

## X0. Ground truth and infrastructure (before any bulk lifting)

- [ ] X0a Complete the closure: find every function of the render path that the direct-call scan misses. Sources: vtable slot targets of every vtable the path uses (BgfxFrameBuilder 114 slots, both RendererContext vtables, pass classes, Declarator), `std::function`/lambda targets (pass bodies, task functors, GraphicsTasks lambdas), jump-table case targets of the six group visitors and the executor, tail-jump thunks, callbacks stored in task records. Deliver: `tools/sigs/closure2.py` (re-runnable), every newly found function appended with `python tools/native_checklist_gen.py --add <rva...>` evidence rows in `docs/data/native_roots.txt` (one line per root: `<rva hex> <name>`, each with a [V] proof of how it is reached), and `docs/data/native_unresolved_indirect.tsv` = indirect call sites whose target set is still unknown (site rva, register, why). CLOSES YES only if the unresolved file lists no site on the frame path that is not proven to target only boundary functions.
- [ ] X0b1 Boundary classification, rows 1-100 of `docs/data/native_boundary_candidates.tsv` (callees of the lift set that are outside the render regions, by caller count). Fill the class column with one of `lift` (render-owned code, becomes a lift item), `stl` (MSVC STL internal: we compile the same STL, no lift), `crt`, `os` (kernel32/ntdll/threads), `d3d` (D3D12/DXGI/GDK COM call), `vendor` (DLSS/FSR/cohtml), `alloc`, `other-subsystem` (world/entity/network/audio; stays original), plus the function name and a [V] proof (what the body is: first 8 instructions and callees). Do not guess: a function whose class you cannot prove is `?` with the blocking fact. Rows only; append the `lift` ones to `docs/data/native_roots.txt`.
- [ ] X0b2 Boundary classification, rows 101-200 (same rules as X0b1).
- [ ] X0b3 Boundary classification, rows 201-300 (same rules as X0b1).
- [ ] X0b4 Boundary classification, rows 301-end (same rules as X0b1).
- [ ] X0b5 Boundary decision review (orchestrator): every row classified; the `stl`/`crt`/`alloc` rows justified against the compiler and STL in use; the `other-subsystem` rows are the explicit external boundary written into `docs/data/native_boundary.tsv` (the only calls Native mode may leave original). Ticks X0b once the `lift` rows have been added as X7 items.
- [x] X0c Spec: `docs/RENDER_NATIVE_SPEC.md` written (lift unit, files, ABI, STL/allocator policy, boundary wrappers, annotation format, closure criteria, verify design). 2026-11-23, decisions open to the user's review.
- [ ] X0d (orchestrator) Lift framework: `src/client/features/render/native/Lift.h` (+ `Boundary.h`): LIFT_FN registration (rva, sig, original trampoline, mode), boundary-call wrappers bound to Sigs.json symbols and logged against `native_boundary.tsv`, record/replay hooks for the differential harness, Native-mode install of entry detours only for functions with callers outside the set. Compiles in Release. Blocks every X1-X5 item except the pilot.
- [ ] X0e Fix the 3 world-phase SelfTest failures: `FrameBuilder::visitEditor` layout drift (+0x64 and +0x3C offsets in `docs/data/layout_asserts.json` / `RenderLayoutAsserts.h`): re-derive each constant from the disassembly of the Editor group visitor (0x66742F0), correct both lists, `python tools/sigs/layoutcheck.py` clean. Also list every other assertion that has never been checked against live memory.
- [ ] X0f Live scene list and capture recipes: write `docs/NATIVE_VERIFY_PROTOCOL.md` section "Scenes" with, per scene (first person world, third person with mob and nametag, rain/snow, particles, held item and block, water/lava, chest/sign, VV on and off, resource pack with custom material, inventory/menu, F1, dimension change, join/leave, resize, RTX if available), what must be on screen and which functions it exercises (from the frame-path table), so each lifted function can be assigned to at least one scene. Output: `docs/data/native_scene_coverage.tsv` (function id, scenes that execute it, [V]/[I]).
- [x] X0g Mirror to the professional repo: `tools/mirror_sync.ps1` links new docs, the data/progress/functions junctions, and `src/client/features/render/native` into `C:\Users\Atomi\Desktop\tomdh-git\bedrock-renderer`. 2026-11-23.
- [ ] X0h (orchestrator) Pilot: lift the first three X1 leaf items end to end through the opencode pipeline and `liftcheck`; review the briefs, the output files and the effort; fix the brief and tools; only then is the X1-X5 queue released (`docs/data/native_pilot.txt` lists the pilot ids; until X0h is [x] `tools/nextitems.py` hands out only those).
- [x] X0i Pipeline wiring: `tools/nextitems.py` (dependency gating, pilot gating, gate/orchestrator items skipped), `tools/mkeasy.py` (LIFT brief), `tools/checklist_status.py` (native status), `tools/sigs/liftcheck.py`, `tools/native_activate.py`. 2026-11-23.
- [ ] X0j (orchestrator) Differential harness v2 (spec section 8): footprint snapshot/restore around a call, boundary record/replay, post-state compare, so a function with side effects can be verified, not only pure leaves. Proven on Math::mat4Multiply (pure), one writer (uniform setVec4Array 0x5679db0) and one function that calls the allocator. Compiles in Release. Blocks the X1z gate.

{{GENERATED}}

## X6. Closure and Native mode (the done state)

- [ ] X6a Native roots: design and write the root installer: with `BS_NATIVE=on` the entry detours are installed only at the roots and at functions that have callers outside the lift set or indirect callers (vtable/functor tables the game built); everything below runs as direct calls between lifted functions. List of those entry points derived by tool into `docs/data/native_entries.tsv` with a [V] reason per row.
- [ ] X6b Boundary audit: `tools/sigs/liftcheck.py --boundary` proves every call out of a lifted function goes to a lifted function or to a `native_boundary.tsv` row (nothing hidden behind a raw function pointer or an RVA constant).
- [ ] X6c Closure audit: every function in the set has `LIFTCHECK OK`; every direct callee of every lifted function is in the set or in the boundary; every indirect call site of the frame path is resolved to a lifted target set or a boundary; zero rows in `native_unresolved_indirect.tsv`.
- [ ] X6d Game-built tables: every vtable, `std::function`, task record and callback table that the game constructs and that points into lifted code is listed with how the entry detour (or a table patch) reaches our source; verified against the live objects.
- [ ] X6e Native-mode run recipe and BIGBANG section: exact steps for the user's in-game test (modes, scenes, logs, what zero divergence means, what to send back).
- [ ] X6z GATE (orchestrator + user): `BS_NATIVE=on` runs the whole render path on our code through every scene without divergence or crash; the lifted tree is the renderer. Push mirror and tag.

## XO. Optimization from the lifted source (not started before X6z)

Method: the lifted tree is the baseline. Each change is a source change to a lifted function (or a fusion of several), verified against the baseline for identical output on the scene recordings, and measured. Hot paths come from a profile of the native build, not from guesses.

- [ ] XO1 Profile the native build per frame stage and per lifted function (RewriteTimed/Profiler rows, GPU timestamps via custom item), on the scene list; ranked table `docs/data/native_profile.tsv`.
- [ ] XO2 Candidate list: for the top 40 functions by cost, the specific waste (redundant work, allocation per frame, std container churn, repeated hashing, sort, unnecessary copies, serial where parallel is possible), with the invariant that must hold for the change to be safe.
- [ ] XO3 Hot-path rewrites in cost order, one item per function or fusion, each with before/after output equality and a measured gain.
- [ ] XO4 Allocation and memory layout: per-frame arena for transient data, pooled descriptions, cache-friendly records, only where the game's observable memory contract is kept.
- [ ] XO5 Threading and pipelining changes the lifted structure now allows (encode parallelism, extractor parallelism), with the thread-model proof of the original first.
- [ ] XO6 New renderer pieces behind the lifted interfaces (own terrain submission, own culling, own post), only after XO1-XO3 show where the time goes.
