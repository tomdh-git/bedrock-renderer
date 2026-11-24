# Native render spec: how a function is lifted, what done means

Version 1, 2026-11-23. Companion of `docs/RENDER_DONE_STATE.md` (goal) and `docs/RENDER_NATIVE_CHECKLIST.md` (work). Target: Minecraft Bedrock 1.26.62.01 (`C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`), RVAs relative to the image base. Where this spec makes a choice the user has not confirmed it says DECISION so it can be revised before bulk work starts.

## 1. The unit: one lifted function

A lifted function is C++ source that does what the exe's function does, instruction for instruction in effect: same reads, same writes (value and order where the order is observable), same calls in the same order, same return value, same calling convention. It is not a reimplementation "in spirit".

Per function there are exactly these artifacts:

1. **Dossier** `docs/functions/<rva>.md` (format of `docs/functions/bc60740.md`): mechanical facts, signature, **Reversed source (complete)**, structs, ownership/threading, version anchors, verification. In the reversed-source block (and the source file) every instruction of the function falls inside a cited address range `// 0xA..0xB` next to the C++ statement it becomes, and every `call` is quoted as a verbatim line `0xRVA  call target` (two spaces after the address; checked by `tools/sigs/verify_oc.py`). Note: the older dossiers (e.g. bc60740.md) describe the code with ranges in prose but quote no verbatim instructions, so they fail the new check until the lift item re-cites them; their analysis is input, not the deliverable.
2. **Source** under `src/client/features/render/native/<area>/` (areas: `bgfx`, `d3d12`, `dragon`, `framebuilder`, `passes`, `helpers`). File name `<Class>_<method>.cpp` (or `sub_<rva>.cpp` while the name is unknown), declaration in `<area>/<same>.h`. First line of the .cpp is the marker
   `// LIFT 0x<rva> size 0x<size> 1.26.62.01 <name>`. Chunked functions keep one file; the chunk boundaries appear as `// CHUNK 0x<a>..0x<b>` comments.
3. **Layout assertions**: every struct offset the function uses is a named constant with a `static_assert`, in the function's own header `native/<area>/<same>.h` (parallel units never edit shared files). The shared lists `docs/data/layout_asserts.json` and `RenderLayoutAsserts.h` are filled from those headers by the orchestrator at the milestone gate (`tools/sigs/layoutcheck.py` clean).
4. **Registry entry**: a `NativeEntry`/`LIFT_FN` registration (framework from X0d) in the same .cpp: name, Sigs.json symbol name, `knownRva`, mode (Off/Shadow/Verify/On). Units do not edit `src/sdk/Sigs.json`; the sig anchors are generated and appended at the milestone gate (`rdis mksig` + `tools/sigs/sigscan.py`, unique match proven).
5. **Status row** in `docs/data/functions.tsv`: D2 (dossier) -> `L1` (lifted source on disk, statically complete) -> `L2` (verified live, zero divergence) -> `L3` (runs in Native mode).

## 2. Closing an item (L1)

`python tools/sigs/liftcheck.py <rva>` must print `LIFTCHECK OK`. It checks:
- the dossier exists; the instructions of `[rva, rva+size)` are 100% inside cited ranges of the source/dossier, every `call` is quoted verbatim, and every quoted line matches the exe (verify_oc mismatch=0, no-such-instr=0);
- the .cpp exists with the `LIFT` marker for this rva and size;
- every `call` target in the function is one of: another lifted function (named in the source as its native symbol), a boundary wrapper (listed in `docs/data/native_boundary.tsv`), or a library intrinsic the compiler would inline (memcpy/memset); the dossier lists each call with its target class;
- no `[?]`/`[I]`/`TODO`/`UNVERIFIED` tag remains inside the function's source or dossier reversed-source block;
- the layout constants it uses are asserted (item 3 above);
- the registry entry exists.
The unit's output file `docs/progress/oc_U-E<ID>.md` quotes the liftcheck output. Closing is static. A function that is statically complete but not yet live-verified is L1; the milestone gate (Xnz) verifies L2.

Not acceptable for [x]: stubs, "subset of the original", skipped paths (error paths included: every branch is lifted), un-lifted callees hidden behind raw pointers, behavior copied from a different game version.

## 3. Calling convention and ABI

Lifted functions are `extern "C"`-style free functions (or static members) with the exact x64 Microsoft ABI signature of the original, `this` first for methods. They are entered either by a direct C++ call from another lifted function, or through an entry detour installed at the original address (only for functions that have callers outside the lift set or indirect callers, see X6a). Argument and return types are the real types from SDK headers; when a register argument is not what the prologue suggests the dossier says so ([V] from the callers).

## 4. Data layout and memory ownership

The game reads what lifted code writes. Therefore: struct layouts are byte-identical (SDK headers with asserts), objects keep their original allocator (the game's allocator interface, boundary class `alloc`) and lifetime, and nothing is "improved" until phase XO. Lifted code never keeps private state in game objects.

## 5. STL, containers and the compiler (DECISION)

The exe uses the MSVC STL ABI. Lifted code that touches `std::vector`, `std::unordered_map`, `std::function`, `std::shared_ptr`, `std::string` objects that the game also touches uses the same MSVC STL headers (the client already does for SDK types) and the layout is asserted by `sizeof`/offset checks in the headers. STL internals the exe contains as separate functions (hash node insert, vector grow, shared_ptr control block release) are classified `stl` in the boundary file and are NOT lifted: we compile the equivalent from our STL. Raw-pointer manipulation of container internals in the original (inlined STL) is lifted as the container operation it is, with a dossier note naming the container and member.

## 6. Boundary (the only calls that stay original)

`docs/data/native_boundary.tsv` (made by X0b) lists every callee outside the lift set with its class: `stl`, `crt`, `alloc`, `os`, `d3d` (D3D12/DXGI/GDK), `vendor` (DLSS/FSR/cohtml), `other-subsystem` (world, entity, network, audio, anything not rendering). A call to a boundary function is made through a `native::boundary::<name>(...)` wrapper that resolves the address from Sigs.json and, in Shadow/Verify mode, records or replays the call (section 8). There is no other way to call original code from lifted code. A function classified `lift` is not boundary: it gets an X7 item.

## 7. Annotation format inside source

Each block of source carries the instruction range it implements:
```
// 0xbc60812..0xbc60839
if (state & kFlag) { ... }          // 0xbc60812  test dword ptr [rbx+0x14], 0x40 ; jz 0xbc60839
```
Control flow follows the original (same branch structure), so a reviewer can walk dossier and source side by side. Compiler-level cleverness is not the goal; an `if` per `jcc` is fine.

## 8. Verification design (DECISION, built in X0d/X0j)

- **V0 static**: liftcheck (section 2).
- **V1 pure differential**: for pure functions (no memory writes except the out argument), run original and lifted on the same live inputs and compare outputs (exists: `RewriteVerify`).
- **V2 footprint differential (general case)**: the lifted function declares its footprint (argument structs and referenced ranges, derived from the dossier). In Shadow/Verify mode at the entry detour: snapshot the footprint, run the original, record its post-state and the sequence of boundary calls (target, arguments, return values), restore the snapshot, run the lifted function with boundary calls served from the recording (and compared: same target, same arguments, same order), compare post-state byte for byte, then put the original's post-state back. Any difference is a divergence; Verify mode ends the process. Footprint gaps (an unlisted written byte) are themselves detected by a canary pattern around the declared ranges.
- **V3 whole-frame**: Native mode over the scene list, user in-game, plus frame-probe comparison of draw records and D3D12 call streams (`tools/sigs/drawstream_compare.py`) between original and Native for the same scenes.
Limits stated up front: V2 cannot cover code whose effects are only visible to another thread at the same instant or to the GPU; those functions get the thread-model proof (`## Ownership / threading` in the dossier) and V3.

## 9. Order of work and delegation

Bottom-up by call graph (callees first); `tools/nextitems.py` enforces it from `docs/data/native_deps.tsv`. Units are opencode agents using rdis (read-only, static, no builds, no game) per `docs/OPENCODE_BRIEF.md` plus the LIFT brief from `tools/mkeasy.py`. One function per unit (chunks for big ones). The orchestrator reviews with liftcheck and the digest, runs the batch build at each gate, and owns gate items. Rules inherited: fail fast (no null guards or SEH in lifted code unless the original has them), edit by hand (no conversion scripts for the source), record every fact as [V] with the instruction line.

## 10. Where things live (and the mirror)

Work happens in BlueySenseV2; the same files appear in the professional repo `C:\Users\Atomi\Desktop\tomdh-git\bedrock-renderer` through hardlinks and junctions (`tools/mirror_sync.ps1` creates them; run it after adding files): `docs/*.md` hardlinks, `docs/data`, `docs/functions`, `docs/progress` junctions, `src/sdk/mc` link, and the new tree `src/client/features/render/native` as a junction. Commit and push from the mirror repo.
Policy (2026-11-23): at X0b5 every boundary row still '?' is classified lift; only rows with a [V] stl/crt/os/alloc/d3d/vendor/other-subsystem proof stay original.
