# re_m1c_shutdown_drain — M1c unit (c): shutdown 0xbc660a0 drain/teardown blocks (62.01)

## NEXT
- **Status:** Unit (c) analysis pass complete for function body of `0xbc660a0` (static). **OPEN** on mapping task-named resource tables to concrete drain blocks inside this function.
- **Resume commands (if continuing):**
  - `tools\rdis\target\release\rdis.exe "C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe" -c "dis 0xbc65800 --max 300; sum 0xbc65800"`
  - Trace command consumers for post-cmd opcodes emitted here: `0x01, 0x1F, 0x1E, 0x1A` (shutdown) and `0x21` (`sub_bc732e0`), `0x22` (`sub_bc79ed0`) to see render-thread side drains for index/vertex/framebuffer/shader/program/texture/uniform/vertex-layout tables.
  - Search xrefs/callees for table bases `0x93A178, 0x9B2178, 0xC97698, 0xAAA178, 0xB62178, 0xBDE178, 0xC96198` in renderer/D3D12 context shutdown paths.
- **Artifacts produced:** `docs/functions/0xbc660a0.md`, this progress file, temp captures `temp_dis_all.txt`, `temp_sum_full.json`, `temp_callee_*`.

## Context
- Target exe (static): `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe` [V].
- Prior: `docs/progress/re_m1c_shutdown.md` listed unit (c) "6 drain blocks of shutdown 0xbc660a0" as PENDING.
- AGENT_BRIEF live anchors (62.01): RendererContextD3D12 obj = `[base+0x12BB4910]`; tables index obj+0x93A178/0x78, vertex obj+0x9B2178/0x80, shaders obj+0xAAA178/0xB8, programs obj+0xB62178/0xF8, textures obj+0xBDE178/0xB8, vertex layouts obj+0xC96198/0x54, framebuffers obj+0xC97698/0x68; bgfx ctx `[base+0x12AE1748]`.

## Progress log

### 0xbc660a0 (bgfx core shutdown / teardown) — OPEN
**Evidence [V]:** `rdis dis/sum/cfg 0xbc660a0` (proven `.pdata`, `[0xbc660a0..0xbc66a4b)`, size 0x9AB, 48 blocks). Full dossier: `docs/functions/0xbc660a0.md`.

**Verified function structure/order [V]:**
1. **Prologue + flag:** `r15=this`; `and byte ptr [this+0x1EBF19E],0xFB`.
2. **Pre-cmd emit + sync:** emit byte `0x01` to frame pre-cmd buffer (`[this+0x1CFD0C8]+DC5818/DC5820`) via `sub_ebce390`; `inc DC5818`; `call sub_bc65800(this,0)`.
3. **Transient submit/notify cycles:** emit post-cmd `0x1F/0x1E` with handle payloads from frame transient objects at `frame+DC5800` (+0x12) and `frame+DC57F8` (+0x10), append to frame queues `E478AC/E498AC` and `E45828/E47828`, conditional notify via `[*0x12ADF800]->vfunc+8` (indirect through `[data_f99ffa0]`), interleaved `sub_bc65800(this,0)` calls.
4. **Specific handle releases on context:**
   - `u16 this+0x1EBF25C != FFFF` -> `sub_bc732e0(*0x12AE1748, handle)` (lock `ctx+0x1C0` via `ebdbf10/20` inside callee; emits post-cmd `0x21`) [V call/mechanics].
   - `u16 this+0x1EBF1F0 != FFFF` -> locked `sub_bc79ed0(*0x12AE1748, handle)` (emits post-cmd `0x22`) [V].
   - Submit/notify objects at `this+0x1EBF1F8` (u16@+0x12, cmd 0x1F), `this+0x1EBF200` (u16@+0x10, cmd 0x1E), `this+0x1EBF260` (u16@+0x12, cmd 0x1F) [V].
5. **Bulk handle array drain:** if `*0x12ADF818`, for `i in [0, *0x12AE0D70)` drain `u16 this[0x1EBF2BC + i*2]` != FFFF via `sub_bc732e0(*0x12AE1748, handle)` and set to `FFFF` [V].
6. **Additional flush/submit:** `sub_bc65800` calls, more transient `DC5800/DC57F8` submits, emit post-cmd `0x1A`, `sub_bc65800` [V].
7. **View/encoder auxiliary cleanup:** manipulates `this+0x13D18` view object (`+0x6AC` index into `[*+DC57E0]`, uniform-buffer append/reset, timestamp via `sub_ebdb740` to `+0x6F8`) and handle pool at `this+0x13D20` (u16 count/cursor/ring) [V]. If `*0x12AE0DAC`, loop `i` over entries `view=[this+0x13D18]+i*0x700`: drain/zero 16-byte chain from `[view+0x680]` region (stepping down from +0x400 by 0x10 with notify vcalls), clear `+0x680`, call `sub_bc769c0(view+0x6D0)` and `sub_bc769c0(view+0x6B0)` [V].
8. **Top-level object release:** if `*0x12ADF800`, vcall slot 1 on `this+0x13D18` (arg4=0x40), `this+0x13D08`, `this+0x13CF8` [V].
9. **Array teardown:** `sub_ebdbc90(this+0x1DE1310, (end-begin)>>4, 0x10, &sub_bc76e60)` and same for `this+0x1DDD2D0` range; `sub_bc76e60` is comparator (compares qwords, returns ±1) [V], not a per-element destructor.

**Callee notes (sampled) [V/I]:**
- `sub_bc65800` (0xbc65800, 0x37d): frame sync/handoff touching `this+0x13D18/13D20/13D08/13D00/1CFD0C8`, timestamps, locks `this+0x1C0/0x180`, calls `ebdb740/ebdbf10/ebdbf20/ebdbc60/ebdbc50/bc66de0` depending on paths.
- `sub_bc732e0` (0xbc732e0): handle destroy path; locked; updates handle bookkeeping at `a0+0x1E4CAB4/0x1E50AB8/0x1E52AB8` region and emits post-cmd `0x21` into frame cmd buffer.
- `sub_bc79ed0` (0xbc79ed0): handle destroy/release path; emits post-cmd `0x22`, manipulates guarded paged arrays around `a0+0x1E7DA*` and frame alloc state `a0+1CFD0C8 -> E4E8B8/C0/C8/D0`; performs allocations/frees via `data_12ADF800` vfunc+8 [I semantics].
- `sub_bc769c0` (0xbc769c0): vector/container reset/clear helper on `{+0x8 begin,+0x10 end,+0x18 cap}` with notify/release via indirect calls.

**Task-named drain targets vs observed body [V + audit]:**
- Task requested 6 drain/release blocks for tables: index `0x93A178/0x78`, vertex `0x9B2178/0x80`, framebuffer `ctx+0xC97698/0x68`, shader `0xAAA178/0xB8`, program `0xB62178/0xF8`, texture `0xBDE178/0xB8`, and also uniform, vertex layouts `ctx+0xC96198`.
- **[V] Searched full disassembly of 0xbc660a0 (`temp_dis_all.txt`): none of those base offsets or those strides appear directly.** No direct per-table iteration loops over the named RendererContextD3D12/bgfx tables were found in this function body.
- **[?] Interpretation/blocker:** these drains may be (a) performed indirectly via render-thread command processing triggered by emitted opcodes (0x01/1F/1E/1A/21/22), (b) performed in callees not fully traced (e.g. command consumer, vcall targets), or (c) associated with a different/adjacent shutdown routine in this build. Cannot conclusively map each named resource table to a specific block in `0xbc660a0` from static body alone.
- **Contradiction/audit note:** prior/task framing states "6 drain blocks of shutdown 0xbc660a0" naming specific table bases/strides, but disassembly evidence for 0xbc660a0 does not show those addresses/strides. Treat table-to-block mapping as **OPEN** pending command-consumer/callee trace.

**SDK/header/layout asserts:** No new uniquely-proven record-layout constants from this function alone suitable for `RenderLayoutAsserts.h` or `docs/data/layout_asserts.json` beyond existing Frame command buffer offsets already documented elsewhere [I]. No additive edits made.

## Final report
- **DONE (for this pass):** Full static disassembly/CFG/summary capture of `0xbc660a0`; phase-by-phase map and dossier written to `docs/functions/0xbc660a0.md`; identified command emission patterns, handle-release callsites (`sub_bc732e0`, `sub_bc79ed0`), bulk handle array drain at `this+0x1EBF2BC`, per-view auxiliary drain loop (`[this+0x13D18]+i*0x700`, `+0x680/+0x6D0/+0x6B0`, count `*0x12AE0DAC`), object releases (`13D18/13D08/13CF8`), and tail array teardowns (`1DE1310`, `1DDD2D0`, elem 0x10, comparator `sub_bc76e60`).
- **OPEN:** Map each task-named resource table drain (index 0x93A178/0x78, vertex 0x9B2178/0x80, framebuffer ctx+0xC97698/0x68, shader 0xAAA178/0xB8, program 0xB62178/0xF8, texture 0xBDE178/0xB8, uniform, vertex layouts ctx+0xC96198) to specific block(s) in `0xbc660a0` and identify per-record destructors/refcount-dec ops for each. **Blocking fact:** named table bases/strides are not present in `0xbc660a0` body; requires tracing render-thread command consumers for opcodes 0x01/1F/1E/1A/21/22 and/or deeper callee/vcall target analysis.
- **Files created/edited:** `docs/functions/0xbc660a0.md`, `docs/progress/re_m1c_shutdown_drain.md` (additive). Temp analysis files in repo root: `temp_dis_all.txt`, `temp_sum_full.json`, `temp_callee_*.txt`.

## FULL PROPOSED BGFX_MAP ENTRY TEXT (entry IDs TBD)
```md
### <TBD> 0xbc660a0 — bgfx Context shutdown/teardown sequence (62.01, static) [V mechanical]
- **Range/size:** `0xbc660a0..0xbc66a4b` (0x9AB, `.pdata` proven), `this = rcx`.
- **High-level flow/order [V]:**
  1. Clear shutdown/state bit2: `this+0x1EBF19E &= ~0x04`.
  2. Emit pre-cmd byte `0x01` to fill-frame pre-command buffer (`frame=[this+0x1CFD0C8]`, cursor `frame+0xDC5818`, data `frame+0xDC5820`) via `0xEBCE390`; `call 0xBC65800(this,0)`.
  3. Repeated post-cmd submit/notify cycles on frame cmd buffer (`frame+0xE05820/E05828`) for transient/default handles: op `0x1F` with `u16 [frame+0xDC5800]+0x12`, op `0x1E` with `u16 [frame+0xDC57F8]+0x10`, queue inserts into `frame+0xE478AC/E498AC` and `0xE45828/E47828`, conditional notify via `[*0x12ADF800]->v1` (`data_f99ffa0`), and periodic `0xBC65800(this,0)` flushes.
  4. Context handle releases: `u16 this+0x1EBF25C` -> `0xBC732E0(*0x12AE1748,h)` (emits post-cmd `0x21`); locked `u16 this+0x1EBF1F0` -> `0xBC79ED0(*0x12AE1748,h)` (emits post-cmd `0x22`, lock `ctx+0x1C0` via `0xEBDBF10/20`); submit/notify objects at `this+0x1EBF1F8` (op 0x1F, u16@+0x12), `this+0x1EBF200` (op 0x1E, u16@+0x10).
  5. Bulk handle-array drain: if `*0x12ADF818`, for each `i < *0x12AE0D70`, if `u16 this[0x1EBF2BC+i*2] != FFFF` call `0xBC732E0(*0x12AE1748,h)` and clear to `FFFF`.
  6. Submit/notify `this+0x1EBF260` (op 0x1F), additional transient submits, emit post-cmd `0x1A`, final `0xBC65800` calls.
  7. Per-view/aux cleanup: `this+0x13D18` uniform-buffer append+timestamp (`0xEBDB740` -> `+0x6F8`) and `this+0x13D20` handle-pool adjustments; if `*0x12AE0DAC`, iterate `view=[this+0x13D18]+i*0x700` draining 16-byte chain linked from `view+0x680` (descend from +0x400 by 0x10, notify+zero), then clear `+0x680` and call `0xBC769C0(view+0x6D0)`, `0xBC769C0(view+0x6B0)`.
  8. Release owned objects via `[*0x12ADF800]->v1`: `this+0x13D18` (r9=0x40), `this+0x13D08`, `this+0x13CF8`.
  9. Destroy ranges: `0xEBDBC90([this+0x1DE1310..1DE1318), n, 0x10, &0xBC76E60)` and `([this+0x1DDD2D0..1DDD2D8), n, 0x10, &0xBC76E60)`; `0xBC76E60` compares qwords (comparator) [V].
- **Callees (direct, key):** `0xEBCE390` (cmd append/copy), `0xBC65800` (frame sync/swap helper), `0xBC732E0` (handle destroy, emits 0x21), `0xBC79ED0` (handle destroy, emits 0x22), `0xEBDBF10/20` (lock/unlock), `0xEBDB740` (timestamp), `0xBC769C0` (container clear), `0xEBDBC90` (range destroy/sort helper) [V].
- **OPEN / audit:** Task-named renderer table drains (index 0x93A178/0x78, vertex 0x9B2178/0x80, framebuffer ctx+0xC97698/0x68, shader 0xAAA178/0xB8, program 0xB62178/0xF8, texture 0xBDE178/0xB8, uniform, vertex layouts ctx+0xC96198) **do not appear directly** in 0xbc660a0 disassembly; mapping those tables to specific drain blocks/destructors/refcount ops in this function remains unresolved and likely requires tracing render-thread command consumers for emitted opcodes (0x01/1F/1E/1A/21/22) and/or callee internals. [V body negative result, ? mapping]
- **Dossier:** `docs/functions/0xbc660a0.md`
```
