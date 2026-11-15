# RE Atmosphere (AtmosphericScattering VV pass + Atmosphere queue) — progress

> Salvage: appended incrementally; do **not** keep results only in memory. Static RE only. Facts tagged `[V] verified`, `[I] inferred`, `[?] unknown`. Contradictions vs docs: note “CONTRADICTS …”.
> Tooling used: `tools\rdis\target\release\rdis.exe` (`str/fn/dis/xr/fld`). `graphify` CLI not available in shell; skill loaded contextually. No builds/commits.

## NEXT
- Locate the **VV AtmosphericScattering pass renderer/execute** body (consumer of Atmosphere queue). Strong leads: `sub_55f1450` refs `AtmosphericScattering` string at `+0x444fa` (abs ~`0x5A3594A`, not yet cleanly mapped to a named pass body in this session) and `AtmosphericScatteringToggles` `+0x43f66`, `SkyAmbientSamples` `+0x46d78`; `sub_57d5880` (`vtbl f0ddc50#2`, caller `0x1119c10`) sets up Atmospherics resources (`atmospherics/atmospherics.json`, `AtmosphericScattering` string at `+0x155`) [V]. Also inspect `0x55f1450` around those offsets with wider context and follow pass registration/build paths.
- Find **all readers/drainers** of the 0x58-byte Atmosphere staging queue: `staging+0x548` begin, `+0x550` end (element size `0x58`) written by Sky visitor via `0x5aba5c0` staging object [V]. `fld 0x548` hits are type-ambiguous (other structs use same offset, e.g. 0x10-byte and 8-ptr vectors) — must prove object/type identity (same `0x8C8` staging base from `0x5aba5c0` / same pass/frame context path). 6ih noted no reader found in `0x6600000-0x6800000` for that Sky staging vector; check merge chains `0xc270460` / `0xc288880` / `0x67591e0` and endframe reset paths (`0x6624855` resets 0x10-byte vector at `+0x548` in a different context) [V].
- Type the 0x58-byte Atmosphere queue element and staging/pass storage (D2-style) once consumers are found; write dossiers under `docs/functions/<rva>.md` (e.g. `0x5aba5c0`, Sky visitor site `0x6656fb8`, merge/consume RVAs).

## Progress log

### 2026-11-15 (session)
- Loaded `code-philosophy` skill (non-frontend RE/docs task). `graphify` skill noted; CLI not on PATH. Read `docs/AGENT_BRIEF.md`, `tools/README.md`, `docs/BGFX_MAP.md` (6ih, 6ik, 6ab/ac, 6hi, 6n/6ep, 6v/ar), `src/sdk/mc/deps/minecraft_renderer/dragon/PassNames.h`, `docs/functions/67c9c20.md`.
- `rdis str` (exe: `LeviLauncher .../1.26.62.01/Minecraft.Windows.exe`):
  - `AtmosphericScattering` (f5b4998): refs `sub_55f1450+0x444fa`, `sub_57d5880+0x155` [V].
  - `AtmosphericScatteringToggles` (f558b46): `sub_55f1450+0x43f66` [V].
  - `AtmosphericScatteringDescription` (f5874ea): `sub_57ccdd0+0xc93` [V].
  - `SkyAmbientSamples` (f558841): referenced near `sub_55f1450+0x46d78` area per checkpoint [V].
- Sky visitor (Atmosphere case) [V, from prior checkpoint disassembly summary, re-verified by reading notes]: around `0x6656fb8` calls `0x5aba5c0` (staging object base returned); `0x665702f` reads `r15=[rsi+0x548]`, compares `[rsi+0x550]`; copies ~0x30 bytes from source region (`rbp+0x348`-based) into `[r15+0..+0x20]`, then writes shared_ptr/control handling and zeros 16 bytes at `+0x30` region in observed pattern; appends 0x58-byte elements (grow path `0x6657237`, guard `max 0x2E8BA2E8BA2E8BB`). Alt path `0x665712a` uses `[rsi+0xB0]/[rsi+0xB8]`, 0x10-byte elements. [V]
- `0x5aba5c0`: alloc/returns per-thread staging object (size `0x8C8`, returns base+`0x10`, TLS via `0x9bd4a0/0x9bd6d0`) [V].
- Helpers noted: `0xc288880`→`0x67591e0` merges per-thread pending entries for 7 loader slots [V/6hi context]. `0x6624855` resets 0x10-byte-element vector at `[rdi+0x548]` (endFrame region) [V].
- `fld 0x548/0x550` scans show many hits on different types (e.g. `0x675530/0x675980` iterate 8-byte ptr elems via callback; `0x67e1c0` clears 8-byte ptr vector at `this+0x548`; `0x6624855` 0x10-byte elems). **Not** the same Atmosphere 0x58-byte queue on `0x5aba5c0` object without type proof [V].
- `sub_57d5880` (vtbl `f0ddc50#2`, caller `0x1119c10`) contains Atmospherics setup strings (e.g. `atmospherics/atmospherics.json`, `AtmosphericScattering`) [V `fn/dis`].
- `xr 0xF5B4998`: only `sub_55f1450+0x444fa`, `sub_57d5880+0x155` [V]. Inspected `sub_55f1450` around `+0x43f66/+0x444fa/+0x46d78` regions via `dis` (large function) — saw uniform/setting hash/name lookup patterns in those windows in this session; did **not** isolate a single “AtmosphericScattering pass renderer/execute” RVA in this pass of analysis [I/?].
- **No source edits, no header/SDK/layout_asserts changes, no BGFX_MAP/RENDER_CHECKLIST edits performed.**

## Key findings (current)

- **Sky → Atmosphere staging (producer, observed):** per-thread staging object from `0x5aba5c0` (`0x8C8`, ret base+`0x10`). Atmosphere queue vector: `staging+0x548` (begin), `staging+0x550` (end), element size **0x58** bytes. Write site: Sky visitor around `0x6656fb8` / related paths in that region (see checkpoint). Element copy observed: copies 0x30 bytes from a source block (context `rbp+0x348`-based in that disassembly) into `[dst+0x00..+0x20)`-region in that snippet plus shared_ptr/control handling and zeroing of 16 bytes near `+0x30` (exact full field layout of 0x58-byte struct **not fully typed** yet) [V partial].
- **Merge/endframe:** 7-slot merge `0xc288880`→`0x67591e0` [V/6hi]. `0x6624855` clears 0x10-byte vector at `+0x548` (different queue) [V]. 6ih states no reader of Sky staging vector found in `0x6600000-0x6800000` and suggests later merge.
- **VV AtmosphericScattering pass (consumer side, naming):** strings present in `sub_55f1450` (builder/config area) and resource setup in `sub_57d5880`. Concrete renderer/execute function RVA and the function that drains `staging+0x548` (0x58) remain **unconfirmed** in this session [?, BLOCKED for full typing].

## Open questions / contradictions
- `fld`-based discovery is misleading across distinct types sharing offset `0x548`; any future “reader of pass+0x548” claim must include object/type identity proof (same staging/pass struct layout family) [V lesson].
- If any later found reader contradicts BGFX_MAP 6ih wording (“no reader found in …”), treat as **CONTRADICTS 6ih (prior note)** and document explicitly.

---

## Final report (snapshot)

**Status:** Partial. Producer (Sky visitor → `0x5aba5c0` staging, `+0x548/+0x550`, 0x58-byte elems) and related helpers/resources are partially verified from prior notes + current `rdis` checks. **Consumer/drain of that specific Atmosphere queue and the VV AtmosphericScattering pass renderer body are not yet located** with file:line-equivalent RVAs beyond string/setup leads (`sub_55f1450`, `sub_57d5880`, `0x1119c10`). No SDK/header/layout_assert edits made (nothing verified enough). No BGFX_MAP/RENDER_CHECKLIST edits.

**Recommended next concrete steps (for follow-up agent/human):**
1. In `sub_55f1450`, extract full pass object construction around `+0x43f66` (`AtmosphericScatteringToggles`), `+0x444fa` (`AtmosphericScattering`), `+0x46d78` (`SkyAmbientSamples`) into a short disassembly excerpt and identify pass name/id registration and execute/callback pointer wiring.
2. Trace `sub_57d5880` callers (`xr/callers 0x57d5880`) and `0x1119c10` to find pass instance setup; look for function pointers/tables that dispatch “AtmosphericScattering”.
3. Search for 0x58-stride iteration patterns tied to the exact staging object type returned by `0x5aba5c0` (cross-ref returns into consumers) rather than generic `fld 0x548`.

---

## FULL PROPOSED BGFX_MAP ENTRY TEXT (IDs TBD)

> **Do not paste into `docs/BGFX_MAP.md` automatically.** This is a proposed additive draft for the Atmosphere/AtmosphericScattering area, aligned with existing style (see 6ih/6ik). Mark uncertainties as `[?]`/`[I]`. Fill IDs/RVAs only when verified.

```markdown
### [TBD-ID] — AtmosphericScattering (VV pass) / Atmosphere queue (producer staging) — [PARTIAL / DRAFT]
- **Pass / name (strings):** `AtmosphericScattering` (`f5b4998`), `AtmosphericScatteringToggles` (`f558b46`), `AtmosphericScatteringDescription` (`f5874ea`), `SkyAmbientSamples` (`f558841`) [V rdis str].
- **Builder/setup leads:** `sub_55f1450` references: `+0x43f66` (Toggles), `+0x444fa` (AtmosphericScattering), `+0x46d78` (SkyAmbientSamples) [V]. Resource/setup: `sub_57d5880` (vtbl `f0ddc50#2`, caller `0x1119c10`) sets up atmospherics-related resources (e.g. `atmospherics/atmospherics.json`, `AtmosphericScattering`) [V].
- **Producer (Sky visitor → per-thread staging), [V]:**
  - Staging allocator/getter: `sub_5aba5c0` returns per-thread staging object (size `0x8C8`, returned pointer = base+`0x10`; TLS helpers `0x9bd4a0/0x9bd6d0`) [V].
  - Atmosphere queue in staging object (observed): `+0x548` = begin, `+0x550` = end, **element stride 0x58 bytes**. Write site: Sky visitor around `0x6656fb8` (and related variant `0x665712a` uses `+0xB0/+0xB8`, 0x10-byte elements — different queue) [V]. Observed element write pattern (partial): copies ~0x30 bytes from a source block in visitor context into the element region starting at begin; followed by shared_ptr/control-block refcount handling and zeroing of a 16-byte tail region in that snippet (full 0x58 layout **[?]** until typed from consumer) [V partial].
- **Merge/endframe notes:** `0xc288880` → `0x67591e0` merges per-thread pending for 7 loader slots [V/6hi]. `0x6624855` resets a 0x10-byte vector at `+0x548` (different context) [V]. Prior note (6ih): no reader of the Sky staging `+0x548/+0x550` (0x58) vector found in `0x6600000-0x6800000`; likely merged later into pass/frame storage [I/6ih].
- **Consumer (VV AtmosphericScattering pass renderer/execute): [?, BLOCKED]** — not yet pinned to a verified RVA in this analysis. Must identify function that drains/reads the 0x58-byte Atmosphere queue from the merged/stored location consumed by the AtmosphericScattering VV pass, and document element struct fields (D2-style) once confirmed.
- **Related (existing):** See also `6ih` (Atmosphere queue partial typing / Sky visitor), `6ik` (VV AtmosphericScattering pass listing context). Any discovered reader contradicting 6ih’s “no reader in …” must be called out as **CONTRADICTS 6ih** in dossiers.
- **Dossiers (target):** `docs/functions/5aba5c0.md` (staging getter), `docs/functions/6656fb8.md` (or surrounding Sky visitor site), plus consumer/merge RVAs once found.
```