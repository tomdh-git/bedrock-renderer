# re_table_collision — 6fr contradiction: ctx+0xC97698 stride 0x68 framebuffer vs "uniform" table

## NEXT
- **Status**: DONE for requested contradiction resolution (static). No open blocker for the attribution collision itself.
- **Resume if needed**: (1) independently trace command-stream dispatcher for cmd bytes 20/36->slots 39/41 and cmd byte 19 dual-dispatch context around slot 40 callers; (2) reverse `sub_e9241b0` (swapchain/RTV creation) and `sub_e819b50` (attachment derivation) for full record field semantics beyond writer evidence; (3) audit remaining BGFX_MAP tables/rows that still say "uniforms / per-window records" (e.g. 6ex-era table rows if any) for consistency with 6ay/6fr/6hy corrections (do not edit BGFX_MAP.md per task).
- **Key commands**: `tools\rdis\target\release\rdis.exe "C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe" -c "fn 0xe817880; fn 0xe8176a0; fn 0xe817c00; sum 0xe817880; sum 0xe8176a0; sum 0xe817c00; callers 0xe817880; callers 0xe8176a0; callers 0xe817c00"`

## Scope / constraints
- Target: `BS_EXE = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe` [V env/task]
- STATIC ANALYSIS ONLY (no debugger/patches/commits). [V task]
- Read first: `docs/AGENT_BRIEF.md`, `tools/README.md`, `CLAUDE.md`, `docs/BGFX_MAP.md` (6fr and surrounding), `docs/progress/re_m1c_slots39_41.md`, `docs/progress/re_m1c_slots42_45.md`, `docs/progress/re_m1c_shutdown.md`. [V]
- `graphify query "6fr ctx+0xC97698 framebuffer uniform table collision..."` attempted but `graphify` not found in PATH on this environment [V shell]. `Select-String`/`findstr` used for targeted evidence gathering.

## Contradiction under investigation
Task: "ctx+0xC97698/0x68 recorded both as framebuffer table and as uniform table."

### Evidence of the two attributions (same base/stride)
- **Framebuffer table (corrected/current)** [V docs+disasm]:
  - `docs/BGFX_MAP.md:1618` (6fr): `ctx+0xC97698 (stride 0x68)` = framebuffers; per record u16 color texture handles +0x00, u16 depth +0x10, window/swap-chain ptr +0x18, u8 color count +0x32. "The header called this table `kUniforms`; renamed `kFrameBuffers`..." [V doc]
  - `docs/BGFX_MAP.md:787` (6ay): records are window/frame-buffer swapchain records (not uniform records as 6aj slots 39-41 guessed): `+0x18` IDXGISwapChain*, `+0x64` present-pending flag; slots 39-41 are create/destroy/resize-family on `this+0xC97698`. [V doc]
  - `docs/BGFX_MAP.md:792` (6az): slot 39 creates swapchain into window record `+0x18` of the 0x68 table. [V doc]
  - `src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h:75,81-115`: `D3D12Tables::kFrameBuffers = 0xC97698`, stride `0x68`, `FrameBufferRecordLayout` (mColor, mDepth, mSwapChain, mWindow, mWindowIndex, mNumColor, mNumAttachments, mAttachments[8][3], mDirty) with static_asserts. [V existing SDK]
- **"Uniform table" / "uniform record" misattribution (contradictory/stale in places)** [V docs]:
  - `docs/BGFX_MAP.md:641` (6aj): "6 0xC97698 table, 0x19F80..8C | per-frame/reset helper touching uniform-record table" [V doc text]
  - `docs/BGFX_MAP.md:655` (6aj): "39-41 0xC97698 (0x68 records) + 0xCC9268 | uniform record update (create/destroy/update uniform; 0xC976xx fields)" [V doc text]
  - `docs/BGFX_MAP.md:1525`: table row "0xC97698 | 0x68 | ? | slots 39, 41 | uniforms / per-window records" [V doc text]
  - Earlier header name `kUniforms` renamed to `kFrameBuffers` per 6fr (line 1618) and D3D12Context.h comment. [V]

## Writer/indexing code for 0xC97698 (verified, 62.01)

### Slot 39 — `sub_e817880` (0xe817880..0xe817bfb, 0x37b), vtbl_f4ed2d0/f4eee80 #39 [V rdis fn/sum]
- **Indexing/scan**: `r14 = this + 0xC97698`; loop `r15 = 0; while (r15 != 0x3400) { ... r15 += 0x68; }` scans 128 records [V 0xe8178f0,0xe817934-0xe81793f]. Record base for handle: `this + 0xC97698 + handle*0x68` [V 0xe81799c-0xe8179a4].
- **Scan key/writers (detach matching window)**: compares `*(this + r15 + 0xC976B8)` i.e. `rec+0x20` (window) to arg2/r8 `rbx` (nwh) [V 0xe817941]. On match and if `rec+0x18` non-null, releases COM object at `rec+0x18` via `(*obj)->vtbl+0x10` and clears `rec+0x18`; then sets `rec+0x20=0`, `rec+0x33=0`, `rec+0x64=0`, `rec+0x10=0xFFFF`, `rec+0x30=0xFFFF` [V 0xe817900-0xe817971].
- **Window list writers**: increments `*(u16*)(this+0x2F8)`, stores fb handle at `*(u16*)(this + oldCount*2 + 0x2FA)` [V 0xe817973-0xe817989].
- **Create/finalize**: passes `&rec+0x18` to `sub_e9241b0` (swapchain/resource creation) [V 0xe8179e4-0xe8179ff]. On success/final path sets `rec+0x20 = nwh`, `rec+0x30 = old window-list index`, `rec+0x32 = 1` [V 0xe817b18-0xe817b2a].
- **Attachment state reads/writers context**: iterates `rec+0x33` 6-byte entries at `rec+0x34` (u16 texture handle at entry+0) calling `sub_e82d960` for non-0xFFFF handles [V 0xe817b72-0xe817bbd].
- **Direct callers**: none found by rdis (vtable dispatch expected) [V rdis callers 0 results].

### Slot 40 — `sub_e8176a0` (0xe8176a0..0xe81778b, 0xeb), vtbl #40 [V rdis fn/sum]
- **Indexing**: `rec = this + handle*0x68 + 0xC97698` [V 0xe8176b1-0xe8176b9].
- **Writers**: sets `rec+0x30=0xFFFF`, `rec+0x33=numAttachments` (r8b) [V 0xe8176c0-0xe8176cb]; memcpy `numAttachments*6` bytes from r9 into `rec+0x34` via `sub_ebce390` [V 0xe8176d3-0xe8176ea]; calls `sub_e819b50(rec)` to derive attachment state [V 0xe8176ef-0xe8176f2]. Also triggers registration/state-transition over texture handles from per-context attachment table `[this+0x19F58]+0x2C6A8 + handle*0x68` [V 0xe81772a-0xe81777d].

### Slot 41 — `sub_e817c00` (0xe817c00..0xe817ce5, 0xe5), vtbl #41 [V rdis fn/sum]
- **Indexing**: `rec = this + handle*0x68 + 0xC97698` [V 0xe817c0a-0xe817c15].
- **Writers/readers**: if `rec+0x18` non-null flushes/waits then releases COM `vtbl+0x10` and clears `rec+0x18` [V 0xe817c1c-0xe817c75]. Clears `rec+0x20=0, rec+0x33=0, rec+0x64=0, rec+0x10=0xFFFF`; reads old `rec+0x30`, sets `rec+0x30=0xFFFF` [V 0xe817c7d-0xe817c97]. If window-backed, decrements `this+0x2F8` and swap-removes handle from `this+0x2FA`, patching moved record's `+0x30` [V 0xe817ca5-0xe817cd8]. Returns old `+0x30` [V 0xe817ce4].

### Record fields evidenced by writer/indexing code (stride 0x68) [V]
- `+0x00..+0x0F`: u16[8] color texture handles [V 6fr/FrameBufferRecordLayout; not written by 39-41 but part of record consumed by PSO/bind paths per docs].
- `+0x10`: u16 depth/handle, set `0xFFFF` on detach/destroy [V slots 39,41].
- `+0x18`: pointer (IDXGISwapChain*/window resource) released via COM `vtbl+0x10`, created into by slot 39, cleared by 39/41 [V].
- `+0x20`: native window handle (qword) compared/cleared/set [V slots 39,41].
- `+0x30`: u16 window-list index or `0xFFFF` [V slots 39,40,41].
- `+0x32`: u8 set to 1 for window framebuffer finalize [V slot 39].
- `+0x33`: u8 attachment count, cleared/set/read [V slots 39,40,41].
- `+0x34`: attachment entries, 6 bytes each, count `+0x33`; first u16 treated as texture handle [V slots 39,40].
- `+0x64`: u8 dirty/flag cleared on detach/destroy [V slots 39,41]. (6ay: present-pending/dirty for extra-window present loop.)

## Stride/count/placement
- **Stride**: `0x68` bytes, encoded as `imul reg, index, 0x68` / `add reg, 0x68` / indexed `[base + index*0x68]` in slots 39-41 [V].
- **Count (scan bound)**: slot 39 scans from offset 0 to `0x3400` exclusive in 0x68 steps => 128 records [V 0xe817938-0xe81793f]. Consistent with `D3D12Tables::kFrameBufferRecords = 128` and `kFrameBuffersStride * 128 == 0x3400` in D3D12Context.h [V existing].
- **Table placement**: `RendererContextD3D12 + 0xC97698`; adjacent layout asserted in header: `kVertexLayouts + 64*0x54 == kFrameBuffers` [V existing static_assert / 6fr]. Window handle list at `this+0x2F8` (count) and `this+0x2FA` (u16 array) indexes this table by fb handle [V slots 39,41].

## Determination: overloaded base or misattribution?
- **Conclusion** [V]: `ctx(RendererContextD3D12)+0xC97698` stride `0x68` is **one table, not overloaded**. It is the framebuffer/window/attachment record table (swapchain-backed window framebuffers, color/depth handles, attachment records, dirty/present flag). The "uniform table/record" attribution for this same base/stride in 6aj (BGFX_MAP:641,655) and the ambiguous "uniforms / per-window records" row (1525) is **misattributed**.
- **Why misattribution is wrong** [V]: slot 39/40/41 code manages `IDXGISwapChain*` lifetime at `rec+0x18`, native window handle at `rec+0x20`, window-list membership at `rec+0x30` against `this+0x2F8/+0x2FA`, attachment entries, and dirty flag `rec+0x64` used for present (6ay). No uniform value upload, uniform handle allocator, or constant-buffer/uniform-record semantics appear at this base.
- **Earlier confusion source (inferred)** [I]: 6aj pre-correction guessed slots 39-41 as uniform create/destroy/update and labelled 0xC97698 accordingly; 6ay/6az/6fr/6hy later corrected to window/framebuffer records and header rename `kUniforms -> kFrameBuffers`.

## Real framebuffer vs real uniform table base(s)
- **Framebuffer table (this build, D3D12 renderer context)** [V]: `RendererContextD3D12 + 0xC97698`, stride `0x68`, 128 records (`D3D12Tables::kFrameBuffers`, `FrameBufferRecordLayout`). Writers/accessors: slots 39/40/41 `0xe817880/0xe8176a0/0xe817c00` (create window FB, set attachments, destroy), PSO builder/executor/present paths per BGFX_MAP 6ay/6fr/6hy. "Shader buffers" are a different table at `+0xA32178` stride `0x78` (6fq correction) [V doc].
- **Uniform-related structures (NOT at 0xC97698)** [V/I existing]:
  - `D3D12StateOffsets::kUniformValues = 0x1250` (per-context value storage indexed by uniform handle; slot 46 updateUniform copies into `ctx->kUniformValues[handle]` per D3D12Context.h comment) [V header comment/doc refs].
  - `UniformHandleMapOffsets`: base `0xC9AA98`, count `0xC9AA9C`, keys `0xC9AAA0` u32[1024], handles `0xC9BAA0` u16[1024] — handle hash map used by slots 42/43 tail/helper [V header/static_asserts, 6?? slots 42-45 notes].
  - bgfx::Context (encoder/API side, global `0x12AE1748`) uniform registry/hash table at `ctx+0x1E1C2A4/1E1D2A4/1E1DAA8` per 6ah [V doc] — separate object from RendererContextD3D12.
  - **No evidence** of any uniform record table at `RendererContextD3D12 + 0xC97698` stride `0x68` [V absence in writer code + contrary evidence].

## 6ek-style AUDIT NOTE (contradiction resolution)

**AUDIT-6fr-C97698-COLLISION (62.01, static)**  
- **Claim A (stale/wrong in 6aj rows 641,655; ambiguous 1525):** `RendererContextD3D12 + 0xC97698` (0x68 records, slots 39-41) is a "uniform-record table" / "uniform record update (create/destroy/update uniform)". [V quoted doc text]
- **Claim B (corrected, consistent with code):** same base/stride is the framebuffer/window record table (`kFrameBuffers`), holding color/depth texture handles, swapchain/window pointers, window-list index, attachment records/count, and dirty flag; managed by slots 39-41 as window framebuffer create/set-attachments/destroy. [V 6fr/6ay/6az/6hy, D3D12Context.h, rdis of 0xe817880/0xe8176a0/0xe817c00]
- **Verdict:** **CONTRADICTION RESOLVED — Claim A is misattribution. Same base, not overloaded.** [V]
- **Key discriminators:** slot 39 compares `rec+0x20` to native window handle, releases/creates swapchain at `rec+0x18`, maintains window list `this+0x2F8/+0x2FA`; slot 41 destroys swapchain and swap-removes window list entry; slot 40 copies 6-byte attachment entries into `rec+0x34` and derives via `sub_e819b50`. None are uniform operations. [V]
- **Related corrections already in docs/headers:** header renamed `kUniforms`->`kFrameBuffers` (6fr, D3D12Context.h); 6ay explicitly states "not uniform records as 6aj slots 39-41 guessed". [V]
- **Residual doc debt (not edited, per task):** BGFX_MAP 6aj table rows 641/655 and row 1525 still contain stale/ambiguous uniform wording; 6hy text still names "kUniforms" in narrative in some copies? (header corrected) — proposed replacement text provided below for lead fold-in.

## Dossiers
- Existing dossiers cover the identified key writer/accessor functions for 0xC97698: `docs/functions/0xe817880.md`, `docs/functions/0xe8176a0.md`, `docs/functions/0xe817c00.md` [V present, read]. No new per-function behavior beyond them required for this collision resolution; this audit cites and confirms their evidence against rdis output.

## SDK/header/layout changes
- None required. `src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h` already has `D3D12Tables::kFrameBuffers = 0xC97698`, `kFrameBuffersStride = 0x68`, `kFrameBufferRecords = 128`, `FrameBufferRecord`/`FrameBufferRecordLayout` static_asserts, and correct slot 39-41 RVAs/comments [V]. No verified new immediates/displacements needing `docs/data/layout_asserts.json` or `RenderLayoutAsserts.h` additions identified in this pass.

## Verification
- Lint/Types/Tests: not run (static analysis only, no build). [V]
- Evidence sources: `rdis fn/sum/callers` on 62.01 EXE for 0xe817880/0xe8176a0/0xe817c00; existing docs/headers listed above. [V]

## Final report
- **DONE**: Resolved 6fr contradiction. `RendererContextD3D12+0xC97698` stride `0x68` is the framebuffer/window/attachment record table (128 records), written/indexed by slots 39/40/41; "uniform table/record" attribution for this base is a misattribution (stale 6aj text/row), not a true overload. Real uniform-related storage is elsewhere (`kUniformValues` +0x1250 per handle, uniform handle hash map 0xC9AA98 region, bgfx::Context encoder registry) [V/I as noted].
- **OPEN**: none for collision itself. Optional follow-ups (non-blocking): dispatcher payload tracing for cmd 20/36/19 context; helper reversal of `sub_e9241b0`/`sub_e819b50`; BGFX_MAP stale-row cleanup in lead fold-in. [?]
- **Files created/edited**: `docs/progress/re_table_collision.md` (this file). No edits to `docs/BGFX_MAP.md`, `docs/RENDER_CHECKLIST.md`, no commits.

## FULL PROPOSED BGFX_MAP ENTRY TEXT (entry ID TBD; do not edit BGFX_MAP.md here)

```md
### 6??. ctx+0xC97698/0x68 collision resolved: framebuffer/window table only; "uniform table" at same base was misattributed (62.01) [V]

- **Contradiction (6ek audit, resolved):** BGFX_MAP 6aj previously labeled `RendererContextD3D12 + 0xC97698` (stride `0x68`, slots 39-41) as a "uniform-record table" / "uniform record update (create/destroy/update uniform)" (rows 641,655) and a table row noted "uniforms / per-window records" (1525). 6ay/6fr/6hy corrected this to framebuffer/window records and the SDK header renamed `kUniforms` -> `kFrameBuffers`. Static disassembly confirms the correction: **same base/stride is one framebuffer/window/attachment record table, not overloaded with a uniform table**. [V doc text + rdis]

- **Writer/indexing evidence (slots 39-41, vtbl `0xF4ED2D0`/`0xF4EEE80`)** [V rdis 62.01]:
  - Slot 39 `0xe817880` (0x37b): scans 128 records at `this+0xC97698`, `r15 += 0x68` until `0x3400`; matches `rec+0x20` (native window handle) to arg2/r8, releases/clears swapchain at `rec+0x18` on reuse, appends fb handle to window list `this+0x2F8/+0x2FA`, calls `sub_e9241b0(..., &rec+0x18)` to create swapchain, finalizes `rec+0x20=nwh, rec+0x30=windowIndex, rec+0x32=1`, transitions attachment texture handles from `rec+0x34` entries (count `rec+0x33`, 6-byte stride). [V]
  - Slot 40 `0xe8176a0` (0xeb, internal): sets `rec+0x30=0xFFFF`, stores `rec+0x33=numAttachments`, memcpy `numAttachments*6` bytes into `rec+0x34`, calls `sub_e819b50(rec)` to derive attachment state, then registration/state transitions. [V]
  - Slot 41 `0xe817c00` (0xe5): if `rec+0x18` non-null flushes/releases swapchain and clears it; clears `rec+0x10=0xFFFF, rec+0x20=0, rec+0x33=0, rec+0x64=0, rec+0x30=0xFFFF`; if window-backed decrements `this+0x2F8` and swap-removes from `this+0x2FA`, patching moved record `+0x30`. [V]
  - Record fields touched: `+0x10` u16, `+0x18` swapchain/resource ptr, `+0x20` window handle, `+0x30` u16 window-list index, `+0x32` u8, `+0x33` u8 attachment count, `+0x34` 6-byte attachment entries, `+0x64` u8 dirty/present flag. Consistent with `FrameBufferRecordLayout` / 6ay/6fr/6hy. [V]

- **Real bases (applicable)** [V/I]:
  - **Framebuffer/window table:** `RendererContextD3D12 + 0xC97698`, stride `0x68`, 128 records (`D3D12Tables::kFrameBuffers`). [V]
  - **Shader buffers (distinct, was confused historically):** `RendererContextD3D12 + 0xA32178`, stride `0x78` (6fq). [V doc]
  - **Uniform-related storage (distinct, not 0xC97698):** per-context uniform/value pointers at `context + handle*8 + 0x1250` (`D3D12StateOffsets::kUniformValues`, slot 46 updateUniform) and uniform handle hash map `+0xC9AA9C/+0xC9AAA0/+0xC9BAA0` (slots 42/43 helpers) on RendererContextD3D12; bgfx::Context encoder-side uniform registry at `ctx+0x1E1C2A4/1E1D2A4/1E1DAA8` (6ah). [V header/docs, I linkage completeness]

- **Dossiers/evidence:** `docs/functions/0xe817880.md`, `docs/functions/0xe8176a0.md`, `docs/functions/0xe817c00.md`; `docs/progress/re_m1c_slots39_41.md`; this audit `docs/progress/re_table_collision.md`. Lead fold-in should supersede stale 6aj uniform wording for slots 39-41/0xC97698 and clarify row 1525.
```