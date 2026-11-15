# re_m1c_slots39_41 — Slots 39,40,41 (RendererContextD3D12 vtbl 0xF4ED2D0)

## NEXT
- COMPLETE for requested scope (slots 39-41 analysis + docs + progress). If resuming: (1) trace command-stream dispatcher for cmd bytes 20/36 payload decode and call sites, (2) reverse helpers `sub_e9241b0` (swapchain/RT create) and `sub_e819b50` (attachment derive), (3) identify exact D3D12 vcall targets in slot 39 backbuffer loop.
- Exact targets: 39=0xe817880 (0x37b), 40=0xe8176a0 (0xeb), 41=0xe817c00 (0xe5). Table base obj+0xC97698 stride 0x68, 128 records.
- Resume commands: `tools\rdis\target\release\rdis.exe "C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe" -c "fn 0xe817880; fn 0xe8176a0; fn 0xe817c00; fn 0xe9241b0; fn 0xe819b50"`

## Context / prior notes
- [V] Read `docs/AGENT_BRIEF.md`, `tools/README.md`, `docs/progress/re_m1c_shutdown.md`. `graphify query` returned not indexed.
- [V] Prior docs (BGFX_MAP 6ay/6az/6hy/6fr, `src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h` `FrameBufferRecordLayout`) identify `0xC97698` stride `0x68` as framebuffer/window records and slots 39/40/41 as create-window-FB / set-attachments / destroy-FB. This pass confirms against disassembly and writes per-slot dossiers.
- [V] rdis `help`, `sum/fn/cfg` for all three targets and helpers `sub_e9241b0`, `sub_e819b50`, `sub_e817790`, `sub_e80ecb0`, `sub_e81ac80`, `sub_e81ae10`. `callers`/`xr`/xref.py showed 0 direct refs for targets (vtable/indirect dispatch expected).

## Work log
- Gathered context, ran rdis analyses, inspected existing SDK/header/layout asserts and BGFX_MAP sections.
- Produced `docs/functions/0xe817880.md`, `docs/functions/0xe8176a0.md`, `docs/functions/0xe817c00.md`.
- Wrote final report and proposed BGFX_MAP entry in this file.

### SLOTS-39-41 — DONE (per-slot disassembly dossiers written)
- Targets: slot 39 `0xe817880` (0x37b), slot 40 `0xe8176a0` (0xeb), slot 41 `0xe817c00` (0xe5), vtable `0xF4ED2D0` / `0xF4EEE80` [V rdis fn/sum].
- Table: `RendererContextD3D12 + 0xC97698`, stride `0x68`, 128 records (scan `0x00..0x3400` step `0x68` in slot 39) [V disasm 0xe817934-0xe81793f]. Renderer/window list: `+0x2F8` u16 count, `+0x2FA` u16 handle array [V].

#### Slot 39 `0xe817880` (create window-backed framebuffer)
- [V] Prologue: `vtbl+0x1E8` (slot 61, candidate `sub_e81ae10`) called `(this,0,nwh,arg3)`; `sub_e80ecb0(this+0xCC9268,-1)`; `sub_e81ac80(this+0xCC9268)` -> `this+0x19F58`.
- [V] Scans all records: if `rec+0x20 == nwh(arg2/r8)` then if `rec+0x18` non-null COM release `vtbl+0x10` and clear `+0x18`; sets/clears `+0x20=0,+0x33=0,+0x64=0,+0x10=0xFFFF,+0x30=0xFFFF` for matched path.
- [V] Appends fb handle to window list (`this+0x2F8`++ , store handle at `this+old*2+0x2FA`), computes `rec=this+0xC97698+handle*0x68`.
- [V] Calls `sub_e9241b0([0x12BB4910]+0x58,[0x12BB4910]+0xCC9268,&desc,&rec+0x18)` (desc built on stack, includes arg3/stack arg4/nwh and copied template from `[0x12BB4910]+0x19F90`). On success and if backbuffer count `[rsp+0x6C]` nonzero, loops creating/accessing per-buffer RTV/view objects via helper/vcalls (exact D3D12 interfaces partly [I]).
- [V] Finalizes record: `rec+0x20=nwh`, `rec+0x30=oldWindowIndex`, `rec+0x32=1`. Calls `sub_e817790([this+0x3C549F8]+0x2C670,handle,0)`, `sub_e834040([this+0x19F58]+0x2C6A8,[this+0x19F58]+0x30,handle,0)`, and if `rec+0x33` iterates 6-byte attachment entries at `rec+0x34` calling `sub_e82d960` for non-0xFFFF texture handles.
- [?] Command byte 20 payload field mapping not independently decoded from dispatcher (task gives `[u16][u8][u64][u16][u16][u32]`).

#### Slot 40 `0xe8176a0` (set framebuffer attachments, internal)
- [V] `rec=this+0xC97698+handle*0x68`: sets `rec+0x30=0xFFFF`, `rec+0x33=numAttachments(r8b)`, copies `numAttachments*6` bytes from `r9` to `rec+0x34` (`sub_ebce390`), calls `sub_e819b50(rec)`.
- [V] Calls `sub_e817790`, `sub_e834040`; iterates attachment entries from context-side table `[this+0x19F58]+0x2C6A8 + handle*0x68` (+0x33 count, +0x34 entries stride 6) and calls `sub_e82d960` for texture handles != 0xFFFF.
- [I] No command byte (internal) per task/prior; callers indirect [?].

#### Slot 41 `0xe817c00` (destroy framebuffer)
- [V] If `rec+0x18` non-null: flush/wait via slot61/queue helpers, release `rec+0x18` (`vtbl+0x10`) and clear.
- [V] Clears `rec+0x20=0, rec+0x33=0, rec+0x64=0, rec+0x10=0xFFFF`, saves old `rec+0x30` then sets `0xFFFF`.
- [V] If old `+0x30 != 0xFFFF`: decrements `this+0x2F8`; if new count `>= 2` swap-remove from `this+0x2FA` list and patch moved record’s `+0x30` to old index. Returns old `+0x30` [V rdis].
- [?] Command byte 36 `[u16]` not independently traced to dispatcher (consistent with handle-only use).

#### 0x68 record offset meaning (consolidated, from slots 39-41) [V where stated]
- `+0x00..+0x0F`: u16[8] color texture handles (not written by 39-41 directly except implied by existing layout; derived by `sub_e819b50` per prior docs [I]).
- `+0x10`: u16 depth/handle field, set `0xFFFF` on detach/destroy/init paths [V 39 scan,41].
- `+0x18`: swapchain/object pointer (window FB), released on reuse/destroy, created into by slot 39 [V].
- `+0x20`: native window handle [V].
- `+0x30`: window-list index or `0xFFFF` [V].
- `+0x32`: u8, set to `1` for window FB finalize in slot 39 [V].
- `+0x33`: u8 attachment count (cleared on detach/destroy, set by slot 40) [V].
- `+0x34`: attachment entries, stride 6 bytes, count `+0x33` (copied by slot 40; first u16 read as texture handle for state transitions) [V].
- `+0x64`: u8 dirty/flag cleared on detach/destroy [V].

#### Files created/edited
- Created: `docs/functions/0xe817880.md`, `docs/functions/0xe8176a0.md`, `docs/functions/0xe817c00.md`, `docs/progress/re_m1c_slots39_41.md`.
- SDK/data: no additive code changes required for 0x68 layout constants (already covered by `src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h` `FrameBufferRecordLayout` + static_asserts and `RenderLayoutAsserts.h` / `docs/data/layout_asserts.json` entries for `D3D12Tables::kFrameBuffers`) [V existing]. No unique layout_asserts.json additions made. No edits to `BGFX_MAP.md` or `RENDER_CHECKLIST.md`.

#### Contradictions / audit notes (6ek style)
- CONTRADICTS `docs/progress/re_m1c_shutdown.md` NEXT note: "slot 39 ... scans 0xC97698 for [rec+0x20]==arg3(u64)". Disassembly compares `rec+0x20` to arg2/r8 (`rbx`, nwh/window) [V 0xe817941, arg flow]. arg3/r9d is used as create desc field, not scan key.

## Final report
- **DONE**: SLOTS-39-41 (dossiers for 0xe817880, 0xe8176a0, 0xe817c00 with instruction-level behavior, record offsets touched, [V]/[I]/[?] tagging).
- **OPEN**: (1) Command-stream dispatcher mapping for bytes 20/36 -> slots 39/41 payload decode not independently traced [?]. (2) Full reversal of helpers `sub_e9241b0` (swapchain/RT creation), `sub_e819b50` (attachment derive/views), and exact D3D12 vcall identities in slot 39 backbuffer loop [?/I]. (3) Direct callers of vtable slots (indirect dispatch sites) not located [?].
- **Blocking facts**: command-byte handler/dispatch table for renderer command stream in 62.01; deeper helper reversals for complete resource-creation semantics.

## FULL PROPOSED BGFX_MAP ENTRY TEXT
```md
### 6??. RendererContextD3D12 framebuffer slots 39-41 (0xC97698 window/attachment records, 62.01) [V static, partial I]
- Slots: 39 = `0xe817880` (0x37b, create window-backed framebuffer / swapchain), 40 = `0xe8176a0` (0xeb, set attachments, internal), 41 = `0xe817c00` (0xe5, destroy framebuffer). Vtable `0xF4ED2D0`/RTX `0xF4EEE80`. Callers/dispatch: indirect vtable (rdis/xref 0 direct) [?]; task/prior: cmd byte 20 -> slot 39, byte 36 -> slot 41 `[u16]`, slot 40 internal [I, dispatcher untraced].
- Record table: `obj+0xC97698`, stride `0x68`, 128 records. Window list: `obj+0x2F8` u16 count, `obj+0x2FA` u16 fb-handle array [V].
- **Slot 39** [V]: flush/acquire (`vtbl+0x1E8` slot61, `sub_e80ecb0(obj+0xCC9268,-1)`, `sub_e81ac80` -> `obj+0x19F58`); scans all records and for any `rec+0x20 == nwh(arg2)` releases `rec+0x18` (COM vtbl+0x10) and clears `+0x18/+0x20/+0x33/+0x64`, sets `+0x10/+0x30=0xFFFF`; appends handle to window list; builds desc and calls `sub_e9241b0` to create swapchain into `rec+0x18`, then performs per-backbuffer RTV/view setup loop [I details]; finalizes `rec+0x20=nwh, +0x30=windowIndex, +0x32=1`; registers/transitions via `sub_e817790`, `sub_e834040`, and iterates 6-byte attachment entries at `rec+0x34` (count `rec+0x33`) calling `sub_e82d960` for non-0xFFFF texture handles.
- **Slot 40** [V]: for `rec=obj+0xC97698+handle*0x68` sets `+0x30=0xFFFF`, `+0x33=numAttachments`, memcpy `numAttachments*6` bytes to `+0x34`, calls `sub_e819b50(rec)` to derive attachment state [I helper internals], then same registration/state-transition flow over attachment texture handles.
- **Slot 41** [V]: if `rec+0x18` non-null flush/acquire and release swapchain; clears `+0x10=0xFFFF,+0x18=0,+0x20=0,+0x33=0,+0x64=0,+0x30=0xFFFF`; if old window index valid decrements window count and swap-removes from list (when new count>=2 patches moved record `+0x30`).
- Record fields touched (0x68): `+0x10` u16, `+0x18` ptr swapchain, `+0x20` window, `+0x30` u16 window-list index, `+0x32` u8, `+0x33` u8 attach count, `+0x34` attach entries (6B, tex handle word), `+0x64` u8 [V]. Consistent with `d3d12::FrameBufferRecordLayout` (`src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h`) [V existing].
- Audit: corrects prior note claiming slot 39 scanned for `rec+0x20==arg3`; scan key is arg2/r8 (nwh) [V].
- Evidence: rdis `fn/sum/cfg` for 0xe817880/0xe8176a0/0xe817c00 on 62.01 exe; dossiers `docs/functions/0xe817880.md`, `0xe8176a0.md`, `0xe817c00.md`.
```
