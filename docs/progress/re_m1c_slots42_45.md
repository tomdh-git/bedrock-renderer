# re_m1c_slots42_45 — M1c vtable slots 42-45, RendererContextD3D12 (vtable 0xF4ED2D0), 1.26.62.01

## Scope / constraints
- **Target**: `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe` (static analysis only). [V]
- **Slots**: 42 `0xe817cf0`, 43 `0xe817e50`, 44 `0xe818050`, 45 `0xe8189c0` (`vtbl_f4ed2d0#42..45`, `vtbl_f4eee80#42..45`). [V `rdis sum`]
- **Task claim**: all touch table base `0xC97698` stride `0x68` (128 records). [V task statement] — **not corroborated** by direct displacements in slots 42-45 bodies; see audit. [V analysis]
- Tagging: [V] verified from instruction/sum/data, [I] inferred, [?] unresolved. Contradictions recorded as audit notes (6ek style).

## Progress log
1. Read `docs/AGENT_BRIEF.md`, `tools/README.md`, `docs/progress/re_m1c_shutdown.md`, `src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h`, cmdbuf mapping data. [V]
2. Loaded `code-philosophy` skill (required). `graphify` command not available in PATH in this environment; initial `graphify query` failed (`CommandNotFoundException`), proceeded with rdis/grep/read evidence. [? tooling gap]
3. Collected rdis evidence: `sum` for targets and key callees (`0xe804590`, `0xebce430`, `0xe818490`, `0xebce5e0`, `0xebce650`), `dis` across full ranges of all four target functions, `sum`/partial `dis` for slot 37 `0xe816380` to assess byte-19/shared-tail claim. [V]
4. Wrote function dossiers:
   - `docs/functions/0xe817cf0.md`
   - `docs/functions/0xe817e50.md`
   - `docs/functions/0xe818050.md`
   - `docs/functions/0xe8189c0.md`
5. Additive SDK edits: `src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h` (slot 42-45 RVAs/slot constants, frame-buffer record-count note, `UniformHandleMapOffsets`, `NamedIndexOffsets`, supporting `static_assert`s). [V]
6. `docs/data/layout_asserts.json`: no new entries added (no stable Sigs.json symbol anchors identified for these raw slot RVAs in this pass; avoided speculative/duplicate entries). [I]

## Findings summary (per slot)

### Slot 42 — `0xe817cf0` (byte 21)
- Iterates contexts `[this+0x19F60, this+0x19F68)` and for each stores a (re)allocated buffer pointer at `context + handle*8 + 0x1250` (`D3D12StateOffsets::kUniformValues`). Old pointer released / new allocated via global allocator `data_12adf800` vcall slot 1; size computed as `((data_f441930[formatIndex] * countMul) + 0xF) & ~0xF`; buffer initialized via `sub_ebce430`. Tail-calls `sub_e804590(this+0xC9AA98, handle, arg4)` for handle-map bookkeeping. [V]
- **0x68 record meaning**: no direct access to `this+0xC97698`. Touches uniform/value handle storage and 0x400-entry hash-map bookkeeping (`+0xC9AA98/+0xC9AA9C/+0xC9AAA0/+0xC9BAA0`). [? relation to framebuffer records]

### Slot 43 — `0xe817e50` (byte 37)
- Releases and clears `context + handle*8 + 0x1250` across contexts, then (if handle != 0xFFFF) removes handle from 1024-entry open-addressing hash table: count `+0xC9AA9C`, keys `+0xC9AAA0` (u32[1024]), handles `+0xC9BAA0` (u16[1024], 0xFFFF empty) with hash constants `0x5EBCA77`, `>>0x13`, `*0x1B1`, `&0x3FF`. [V]
- **0x68 record meaning**: no direct `0xC97698` access. Manages handle lifetime for per-context uniform/value pointers. [V]

### Slot 44 — `0xe818050` (byte 40)
- Large screenshot/readback-style path: ring/index selection using `this+0xC9C6D0`/`this+0x19FAC`, waits via `sub_e818490(this+0xCC9268, ...)`, uses command-list wrapper `this+0x19F58`, device `this+0x400`, references `"LScreenshot"`, calls `sub_e815590`, `sub_ebd18f0`, `sub_e80ecb0`, `sub_e81ac80`, `sub_e92a800`, and global `data_12adf808` vcall slot 18. Sets error qword `0x887A000500000004` at `this+0x19F88` when state < 5 on specific path. [V]
- **0x68 record meaning**: no direct `0xC97698` displacement observed. [?] Full stage-by-stage buffer/resource map incomplete.

### Slot 45 — `0xe8189c0` (byte 22 and routed with byte 19)
- Builds string descriptor (default `data_f847a07` or measured name via `sub_ebce5e0`) and writes bounded name via `sub_ebce650` to `this + index*0x100 + 0x7EDE` (max `0xFA`). [V]
- **0x68 record meaning**: no direct `0xC97698` access; uses stride `0x100` name region. [V]
- **Byte 19 / "shared tail"**: cmdbuf maps byte 19 -> slots 37,45 and byte 22 -> slot 45. Slot 37 (`0xe816380`) operates on shader-buffer records at `this+0xA32178` (stride 0x78) and touched-state tracking; slot 45 body is independent name setter. Therefore slot 45 is not a shared implementation tail of slot 37. [V/I] Decoder-level dual-dispatch for byte 19 not traced in this pass. [?]

## 0xC97698 stride 0x68 record (128 records) — coverage from this pass
- `D3D12Context.h` already documents `FrameBufferRecordLayout` (0x68) with fields/`static_assert`s for framebuffer create/destroy slots 39-41 and PSO/executor usage. [V existing header]
- **Slots 42-45**: no direct reads/writes of `this+0xC97698 + h*0x68` found in their instruction streams. [V]
- **Audit (6ek style)**: contradiction between task statement ("All touch table base 0xC97698 stride 0x68") and observed behavior. Likely conflation with adjacent/related handle systems: slots 42/43 manipulate per-context uniform value pointers (`+0x1250`) and the 0x400-entry allocator/hash map (`0xC9AA9C/0xC9AAA0/0xC9BAA0`), while framebuffer records remain at `0xC97698`. [I] Cannot fully map "every offset in the 0x68 record" to slots 42-45 because these slots do not appear to address that record directly. [? blocker for requested completeness]

## Callers (static)
- All four targets are vtable-resident (`vtbl_f4ed2d0`/`vtbl_f4eee80` slots 42-45). [V]
- Direct/static caller enumeration beyond vtable dispatch was not completed (rdis xref tooling usage limited/unavailable in this session). [?]

## Blockers / missing work (precise)
- **Command decoder traces** for bytes 19/21/22/37/40: payload-to-parameter mapping and byte-19 dual dispatch (slot 37 then/and slot 45 ordering, argument reuse) not confirmed from handler bodies (`bgfx_cmdbuf` handler RVAs known from TSV but not fully disassembled here). [?]
- **Slot 44 full semantics**: complete reconstruction of all GPU copy/readback objects, descriptor/state transitions, and external callback contract not finished (large function, many indirect calls). [?]
- **Sub-helper semantics**: `sub_e804590` (tail helper used by slot 42) analyzed only via `sum` (hash/map maintenance visible) but not fully documented as a separate dossier; `sub_ebce430` is a thunk into complex code; `sub_e815590`, `sub_ebd18f0` internals not reversed. [?]
- **No direct 0xC97698 access in 42-45**: cannot attribute specific `FrameBufferRecordLayout` field meanings to these slots from evidence collected; requested "meaning of every offset in the 0x68 record" for these four slots is therefore not satisfiable from their bodies without additional correlated evidence (e.g. slot 39-41 already define it; 42-45 do not touch it directly). [?]
- **layout_asserts.json**: no additions made; if desired, need stable symbol anchors and identified immediate/displacement assertions from these functions. [I]

## Verification
- Lint/Types/Tests: not run (analysis-only pass, no build system invoked). [V process note]

## Final report
- Completed static, instruction-informed analysis of slots 42-45 with rdis `sum`/`dis` evidence and produced per-function dossiers plus additive header constants/asserts for newly confirmed handle-map/name-region offsets.
- Key correction: slots 42/43/45 (and observed parts of 44) do not directly reference `0xC97698` stride-0x68 framebuffer records; they primarily affect per-context uniform/value pointers, a 0x400-entry handle hash map, screenshot machinery, and per-index name storage respectively. Slot 45 is distinct from slot 37 despite byte-19 routing.
- Stopped after requested 4 slots due to remaining decoder/helper/slot-44 depth unknowns listed above.

## FULL PROPOSED BGFX_MAP ENTRY TEXT
```md
### 6??. D3D12 renderer slots 42-45 (1.26.62.01, vtbl 0xF4ED2D0/0xF4EEE80) [V rdis, partial semantics]

| Slot | RVA | Size | Cmd byte(s) | Summary |
| ---: | --- | ---: | --- | --- |
| 42 | 0xE817CF0 | 0x15A | 21 `[u16][u32][u16][u8]` [V task/I payload] | For each context in `[this+0x19F60, this+0x19F68)`, release old and allocate/init a new buffer stored at `context + handle*8 + 0x1250` (`D3D12StateOffsets::kUniformValues`). Size `(fmtTable[fmt]*mul + 0xF)&~0xF` (`data_f441930`), allocator `data_12adf800` vcall slot 1, init `sub_ebce430`; tail `sub_e804590(this+0xC9AA98, handle, arg4)`. [V] |
| 43 | 0xE817E50 | 0x1FE | 37 `[u16]` [V] | Release/clear per-context `context + handle*8 + 0x1250` pointers, then (if handle!=0xFFFF) remove from 0x400-entry open-addressing handle map: `count +0xC9AA9C` (u32), `keys +0xC9AAA0` (u32[1024]), `handles +0xC9BAA0` (u16[1024], 0xFFFF empty), hash `((key*0x5EBCA77)>>0x13)*0x1B1 & 0x3FF`. [V] |
| 44 | 0xE818050 | 0x438 | 40 `[u16][u16]` [V task] | Screenshot/readback-style GPU path (`"LScreenshot"`): waits/synchronizes via queue wrapper `this+0xCC9268` (`sub_e818490`), uses `this+0x19F58/0x400/0x19F20/0xC9C6D0/0x19FAC`, calls `sub_e815590`, `sub_ebd18f0`, `sub_e80ecb0`, `sub_e81ac80`, `sub_e92a800`, `data_12adf808` vcall 18; may write error qword `0x887A000500000004` to `this+0x19F88` when state < 5. Full buffer/state map incomplete. [V body, ? semantics] |
| 45 | 0xE8189C0 | 0x0A1 | 22 `[u16][u16]` and routed with byte 19 -> {37,45} [V TSV/task] | Bounded name write: computes `dst = this + index*0x100 + 0x7EDE`, builds `{ptr,len}` (default `data_f847a07` or `sub_ebce5e0` on provided name), calls `sub_ebce650(dst, 0xFA, &desc, 0x7FFFFFFF)`. [V] Distinct from slot 37 (shader-buffer `0xA32178` stride 0x78 ops); not a shared tail of slot 37 body. [V/I] |

**Audit/corrections:** Task-level claim that 42-45 "touch table base 0xC97698 stride 0x68 (128 records)" is not supported by direct displacements in analyzed 42-45 bodies (no `0xC97698` operand found). [V] Observed structures: per-context uniform/value pointer slots at `+0x1250`, handle hash map at `+0xC9AA9C/+0xC9AAA0/+0xC9BAA0` (0x400), screenshot/queue machinery, and name storage at `+0x7EDE` stride 0x100. Framebuffer record layout at `0xC97698` (0x68) remains as documented for slots 39-41/PSO/executor. [V existing, I linkage]. Byte-19 decoder dual-dispatch details and slot-44 internals remain open. [?]

**Dossiers:** `docs/functions/0xe817cf0.md`, `docs/functions/0xe817e50.md`, `docs/functions/0xe818050.md`, `docs/functions/0xe8189c0.md`.
```
