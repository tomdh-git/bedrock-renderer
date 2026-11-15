# re_m1c_generate_loop — M1c: generate per-pass loop inside Dragon endFrame 0xc273420

## NEXT
- **Status**: COMPLETE for M1c static analysis unit (generate per-pass loop structure mapped at instruction level where feasible). No open blocker for this unit except unresolved type/field naming details recorded below.
- **If resumed**: deepen semantics of jump-table cases (`0xf478e3c/e50/e28/e14/e00/dec`) and trace initialization of pass cursor range (`[rbp+0x3450]/[rbp+0x3418]`, `[rbp+0x3290]` map owner) earlier in `0xc273420`; optionally dump full linear disassembly via scripted `dis <addr>` windows.
- **Resume commands**:
  - `tools\rdis\target\release\rdis.exe "C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe" -c "sum 0xc273420; callees 0xc273420"`
  - `tools\rdis\target\release\rdis.exe "C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe" -c "dis 0xc277e8c; dis 0xc277f10; dis 0xc278030; dis 0xc279cc3; dis 0xc27a63a"`
  - `tools\rdis\target\release\rdis.exe "C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe" -c "sum 0xc27ec60; sum 0xc27ed70"`

## Progress log

### Unit 1 — required context read [V]
- Read `docs/AGENT_BRIEF.md`, `tools/README.md`, `CLAUDE.md`.
- `graphify` command not available in this environment [V] (`CommandNotFoundException`), so graph query could not be run.
- Existing progress file was a stub (`docs/progress/re_m1c_generate_loop.md`); `docs/functions/0xc273420.md` did not exist. Existing `re_m1c_generate_loop_{fn,dis}.txt` were unreadable as UTF-8 text in PowerShell `Get-Content` attempts (treated as binary by read tool).

### Unit 2 — function survey (rdis static) [V]
- Target: `BS_EXE = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`
- `sum 0xc273420`: `sub_c273420 [0xc273420..0xc27be93)`, 1922 blocks, 360 calls, 3548 accesses, 6 switch tables, unordered_map/set error strings, heavy indirect/vcall usage.
- `callees 0xc273420`: notable helpers include `sub_c27ec60`(2), `sub_c27ed70`(1), `sub_a78940`(14), `sub_a4c70`(6), `sub_9bc830`(42), `sub_e935700`(27), `sub_eec73f0`(6), `sub_67bf2c0`(1), `sub_6759ea0`(2), etc.
- `cfg 0xc273420` captured (truncated in log) showing early split at `c2734a5` on `r8+0x50 == 0`.

### Unit 3 — per-pass loop identification and mapping [V][I]
- Located main generate/pass iteration around `0xc277e8c..0xc279cd8` with loop header at `0xc277f10` and cursor advance at `0xc277ef0`.
- **Loop form [V]**: cursor `[rbp+0x3450]` iterates over 0x10-byte entries until `[rbp+0x3418]`; per-iteration loads key `[cursor+0]` and pass object `r13=[cursor+8]`; performs map/tree lookup in `[rbp+0x3290]`, allocates/inserts 0x38-byte record via `sub_a78940`/`sub_a4c70` if needed, initializes per-pass scratch `[rbp+0x3310]`, dispatches on pass mode/fields (`r13+0x228/0x230`, 5-case jump tables), accumulates/emits via `sub_c27ec60`, cleans 0x20-byte typed slots in `[rbp+0x3000..]` (switch table `0xf478e50`), then `sub_c27ed70([rbp+0x3310])` and `cursor += 0x10`.
- **Helper semantics [I from sums/dis]**: `sub_c27ec60` manages 0x80-stride output buffer bounds; `sub_c27ed70` destroys/resets three subranges and clears scratch object.
- **Post-loop [V]**: end-of-range -> `0xc27a63a` finalize (graph/frame list traversals, calls `sub_67bf2c0`, `sub_6759ea0` etc.); alternate stop -> `0xc27a772`.
- **Not analyzed in detail**: `pass+0x548` Atmosphere drain (explicitly R1-owned per task).

### Artifacts written [V]
- `docs/functions/0xc273420.md` — D2-style mechanical facts + instruction-level per-pass loop map, callee table, open questions.
- `docs/progress/re_m1c_generate_loop.md` — this log/report (updated).
- No SDK headers or `docs/data/layout_asserts.json` / `RenderLayoutAsserts.h` edits made (no verified immediate/displacement constants to assert for this unit).

## Final report

### DONE
- **M1c generate per-pass loop in `0xc273420`**: identified iteration range/cursor/end (`rbp+0x3450/rbp+0x3418`, stride 0x10), map-backed per-pass record lookup/insert (`rbp+0x3290`, 0x38-byte alloc via `sub_a78940`, insert via `sub_a4c70`), per-pass scratch lifecycle (`rbp+0x3310`, `sub_c27ed70`), pass-object sourcing (`cursor+8 -> r13`), mode/slot dispatch via jump tables, output accumulation via `sub_c27ec60`, and cleanup/finalize boundaries. Instruction-level map and notable callees documented in `docs/functions/0xc273420.md`.

### OPEN (blocking facts)
- **Type/field identities [?]**: exact struct/class names for generate context, pass cursor entry, pass object, per-pass map node/record (0x38), and scratch/output buffers are not proven.
- **Dispatch semantics [?]**: meaning of pass mode bytes/fields (`r13+0x228/0x230`) and 5-case slot types switched via `0xf478e3c/dec/e00/e14/e28/e50` not fully decoded.
- **Source of pass range/map [?]**: initialization sites for `[rbp+0x3418]`, `[rbp+0x3450]`, `[rbp+0x3290]` earlier in `0xc273420` not fully traced in this unit.
- **Pass+0x548 drain (out of scope)**: noted only; not analyzed (R1).

### Files created/edited
- Created/rewritten: `docs/functions/0xc273420.md`
- Rewritten: `docs/progress/re_m1c_generate_loop.md`
- Edited: none (no SDK headers, no BGFX_MAP/RENDER_CHECKLIST)

## FULL PROPOSED BGFX_MAP ENTRY TEXT
(Entry ID TBD — do not edit BGFX_MAP.md)

```md
### [TBD] Dragon generate: per-pass loop inside endFrame `0xc273420` (M1c, static) [V][I][?]
- **Function**: `sub_c273420` (`0xc273420..0xc27be93`, `.pdata`, 0x8a73 bytes) — Dragon frame-graph generate/end-frame routine (name inferred [I]).
- **Generate per-pass loop (core)** [V]:
  - **Range/cursor**: iterates cursor `[rbp+0x3450]` over 0x10-byte entries until `== [rbp+0x3418]` (`0xc277f10: cmp/je 0xc27a63a`), advanced by `+0x10` at `0xc277f03` via back-edge `0xc279cd8 -> 0xc277ef0 -> 0xc277f10`.
  - **Per-entry inputs**: key/handle = `[cursor+0]`, pass object/desc ptr `r13 = [cursor+8]` (`0xc277f57`, `0xc2780ca`) [V].
  - **Per-pass record map** (`[rbp+0x3290]`) [V][I]: ordered tree/map lookup by pass key (node key at +0x20, nil/color at +0x19, children +0x0/+0x10). On miss, allocates 0x38-byte record via `sub_a78940(allocator=[rbp+0x3288], 0x38, 1)` (`0xc277fd8`), initializes record (stores key at +0x20, clears fields), inserts with `sub_a4c70` (`0xc27807f`), saves ptr to `[rbp+0x3460]`.
  - **Per-pass scratch/output** [V][I]: `sub_c27ec60([rbp+0x32E0],...)` initializes/appends 0x80-stride work buffer (`0xc277e8c`, `0xc2793fe`); `[rbp+0x3310]` cleared per pass and destroyed each iteration by `sub_c27ed70` (`0xc277ef7`).
  - **Dispatch/setup** [V][I]: inspects pass flags/mode (e.g. `r13+0x01`, `r13+0x228`, `r13+0x230`) and runs switch-table-driven setup over 0x20-byte typed slots in `[rbp+0x3000..]` (tables `0xf478e3c/e50/e28/e14/e00/dec`), including refcounted resource handling.
  - **Cleanup tail** [V]: `0xc279cc3` walks 16 slots downward (`rbx=0x1E8..-0x18`, step -0x20), type-dispatch via `0xf478e50`, releases refcounted objects in some cases through `[data_f99ffa0]`, then continues loop.
  - **Finalize** [V][I]: end -> `0xc27a63a` (post-loop graph/frame list traversals/cleanup, e.g. `sub_67bf2c0`, `sub_6759ea0`); alternate stop -> `0xc27a772`.
- **Notable callees** [V][I]: `sub_e9e7970` (stack probe), `sub_c27ec60` (0x80-stride buffer mgmt), `sub_c27ed70` (per-pass scratch teardown), `sub_a78940` (pool/element alloc), `sub_a4c70` (map insert), `sub_9bc830`/`sub_e935700` (free/copy-move helpers), `sub_eec5850/eec73f0/eec6ed0/eec6eb0/eec6de0` (pass/resource/setup helpers), late finalize helpers (`sub_67bf2c0`, `sub_6759ea0`, etc.).
- **Not analyzed (by task scope)**: `pass+0x548` Atmosphere drain — R1.
- **Open** [?]: exact type/field names for cursor entries, pass object, 0x38-byte map record, and scratch/output structs; full semantics of mode/slot switch cases; initialization provenance of pass range/map inputs within `0xc273420`.
- **Evidence**: rdis `sum/cfg/callees/dis` on `0xc273420` and helpers `0xc27ec60/0xc27ed70`; dossier `docs/functions/0xc273420.md`.
```
