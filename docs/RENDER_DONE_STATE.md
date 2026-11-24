# Render done state: the game's render code running as our own source

Decided 2026-11-23. Supersedes the "seams and hooks" framing of RENDER_REVERSAL_PLAN.md section 1 and replaces PLAN_OPTIMIZATION.md (deleted; it planned veto/LOD/knob optimizations from the outside, not from reversed code).

Work list: `docs/RENDER_NATIVE_CHECKLIST.md` (one item per function, generated from the call graph by `tools/native_checklist_gen.py`; activate with `python tools/native_activate.py`). Contract: `docs/RENDER_NATIVE_SPEC.md`. Source tree: `src/client/features/render/native/`. Mirror to the professional repo: `tools/mirror_sync.ps1`.

## 1. Definition of done

Done = we understand everything AND we can control everything, shown by this:

1. **Source for every function.** Every function on the render path has instruction-complete C++ in this repo ("Reversed source" block rule, RENDER_CHECKLIST M5): every instruction maps to a source line, its structs are in SDK headers, its layout constants are asserted.
2. **Byte-identical behavior.** Each function is shadow/verify-compared against the game's original on live inputs (RewriteRegistry Shadow/Verify): same outputs, same memory writes, same callees in the same order. Zero divergence over N frames in every scene on the scene list.
3. **Native mode.** A mode in which the root of the render path runs only our code, top to bottom (frame builder end-of-frame, visitors, extractors, frame-graph generate, task dispatch, pass bodies, bgfx submit/sort, D3D12 executor and flush). The original game code is called only at the **external boundary** (section 3). The game gets back exactly the memory and calls it expects.
4. **Only then** modify. A change to our source is a normal code change, verified against the lifted baseline, not a patch at an RVA.

Not acceptable as done: structural-only understanding, [~] partials, write-only queues with no reader, "[I]" fields in a lifted function, a stub, a rewrite that is "a subset of the original", a veto or detour standing in for a function we have not lifted.

## 2. Real coverage today (measured 2026-11-23, not the checklist's 421/0)

Frame-path census (docs/data/frame_path_functions.tsv, direct-call closure only, 955 functions, 2.18 MB of machine code):

| Status | Functions | Bytes |
|---|---|---|
| D2 (dossier, some with full source) | 82 | 362 KB (17%) |
| D1 (named, described) | 26 | 573 KB |
| D0 (seen, not read) | 847 | 1,249 KB (57%) |

By region (functions): framebuilder 348, pass-tasks 179, bgfx 151, d3d12 106, dragon 65, frame-graph 57, root 33, dragon-tasks 16.

The inventory of L1-L6 is 15,113 functions (131 D2 in functions.tsv). The census is only the direct-call closure: indirect calls (vtables, std::function lambdas, Declarator-supplied pass functors, extractors reached through jump tables) pull in more. The first task is to compute the full closure, not to trust 955.

Known unreadable-so-far items (from the R ledger): consumers of pass queues at +0x548 (Atmosphere), +0x80 (EditorHighlight), +0x800/+0x648/+0x4A0/+0x1D0 (lights), +0x98 (BlockChanges) were not found statically; Gameface/HudIcon/UIImGui; field meanings of several descriptions; PSO desc build body; the 3 failing `visitEditor` layout assertions from the one world-phase SelfTest run.

## 3. External boundary (the only calls that stay original)

Decide explicitly, keep the list short, every entry justified: D3D12/DXGI/GDK API calls (COM vtable calls), OS and CRT, the allocator, threads/semaphores primitives, cohtml/Renoir, DLSS/FSR vendor libraries, subsystems that are not rendering (world, entity, network, audio). Anything else on the path is lifted. Excluded-by-decision list in RENDER_CHECKLIST Q7 is the starting point.

## 4. Method (per function, bottom-up)

Leaf to root by call-graph depth, so a lifted function only ever calls lifted functions or boundary functions.

1. Dossier tool (`tools/sigs/dossier.py`) gives the mechanical half; read the disassembly (rdis) for the analyst half.
2. Write the C++ by hand (no conversion scripts), keeping the original's control flow, struct layout and call order so it can be compared.
3. Add layout constants to both assertion lists; sig anchor to Sigs.json.
4. Register in RewriteRegistry; run Shadow then Verify on live frames; fix divergences; promote to On.
5. Mark D3 only after a clean live verify run. Record in docs/data/functions.tsv.

Rules: no detour is "done"; a detour is only the vehicle for verify mode. Static + plain-memory polling for live checks (no debugger sessions; they crashed the game).

## 5. Milestones

- **N0 Ground truth.** Full closure (direct + vtable + lambda + jump-table callees) of the render root; classify every function; replace the 955 estimate with the real list and sizes. Fix the 3 layout assertion failures. Build the DLL and run SelfTest, FrameProbe and Verify infrastructure once so the harness itself is proven (the harness has never run; the first rewrites found 9 of 13 entries would crash).
- **N1 bgfx core + Frame.** Context, Encoder, submit, sort, handle allocators, view setup, uniforms, frame/handoff.
- **N2 D3D12 backend.** Executor, flush, PSO key and desc build, descriptor heaps, bind cache, constants, resource creation, RTX subclass.
- **N3 RenderDragon.** endFrame, generate, scheduler, task runner, Declarator, lifetimes.
- **N4 FrameBuilder.** All inserts, visitors, extractors (chunk, actor, item, nametag, particle, sky, clouds, weather, UI, editor, lights), materials and uniform writers.
- **N5 Pass bodies.** VV, Fancy, RTX, legacy: every body with its inputs/outputs, close every write-only queue by finding its consumer (live data-watch where static fails).
- **N6 Closure and Native mode.** Root runs entirely on our code; whole-frame Verify clean across the scene list; user runs the in-game test.
- **Phase O (after N6).** Optimization from the lifted source: profile, then rewrite hot functions (sorting, matrix cache, uniform writes, bind/PSO caches, batch building, extractors, per-frame allocation, visibility), each verified against the lifted baseline for identical output. Plan written then, from measurements.

## 6. Risks to state plainly

- Size: ~2 MB of code in the direct closure alone, more with indirect callees. This is many sessions per milestone; the milestone list is the honest plan, not an estimate.
- Memory ownership: the game reads what our code writes (registry, task lists, frame buffers). Layout and lifetime must match byte for byte, including allocator choice and std container internals (MSVC STL).
- Version drift: each patch moves code; a lifted function must keep its sig anchor, and Native mode must refuse to start on an unverified version.
- The checklist's "done" meant "on disk and compiles". For this plan a function is done only at step 5 of section 4.
