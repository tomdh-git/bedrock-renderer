## NEXT
DONE

# UNIT U-EC5a — C5a pending part: registration call addresses for module names (6aq)

Source checklist item: "C5a Declarator<RenderContext> + five Bind* dependency kinds + module names — 6aq; registration call addresses pending".
This unit does ONLY the pending part: registration call addresses tying module names (from BGFX_MAP.md 6aq) to call sites in the exe.
Everything else in the item line is treated as already done by prior units (oc_U-C5a, oc_U-C5a2).

EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Static analysis only.
Input data (read fully, not re-run): docs/progress/oc_U-C5a.md, docs/progress/oc_U-C5a2.md.

## PENDING PART
Find, for each module/pass name from 6aq (averageLuminance, localExposure, taau, clusterLights, volumeScattering, generateCubemapMips, rayTrace, fidelityfx::fsr1::_FSR1Draw; framerenderer::preprocessingutils; renderer-resource roots FancyFrameRendererResources, VibrantVisualsFrameRendererResources, RTXMinecraftFrameRendererResources), the registration call address(es) where its pass declaration function is called, with verbatim `0xRVA  instr` proof lines.

## REGISTRATION FUNCTIONS (from prior units, treated as anchors)
- sub_55f1450 VV builder (0x55F1450..0x563F594): calls sub_567b570 x90; build/lookup entry point per 6aq
- sub_bbe2d50 RTX builder (0xBBE2D50..0xBBF62CF): calls sub_567b570 at 0xBBE34B8, 0xBBE3545, 0xBBE35A9
- sub_bbce7b0 (0xBBCE7B0..0xBBD16C3): calls sub_567b570 5x at 0xBBF004D, 0xBBF00D1, 0xBBF012F, 0xBBF01BA, 0xBBF02C1
- sub_567b570 Declarator bind/lookup (0x567B570..0x567B846): 111 xrefs

## TABLE (offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag)

Verified `call 0x567B570` registration sites (Declarator<RenderContext> bind/lookup = the registration function, per input data oc_U-C5a.md). Sub_bbe2d50 is the RTX frame builder; it calls sub_567b570 exactly 3 times, all verified by rdis dis below. VV builder sub_55f1450 calls sub_567b570 x90 and sub_bbce7b0 calls it 5x (input data oc_U-C5a.md, [V] via xref callers count), but no per-module call RVA can be tied to a module name because the exact module-name strings are absent from the exe (see verified-negative below).

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|--------|------|--------------------|------------------------------------|---------|-----|
| 0xBBE34B8 | - | - (call target 0x567B570) | `0xBBE34B8  call 0x567B570` | RTX builder sub_bbe2d50 — Declarator<RenderContext> bind/lookup registration call | [V] |
| 0xBBE3545 | - | - (call target 0x567B570) | `0xBBE3545  call 0x567B570` | RTX builder sub_bbe2d50 — Declarator<RenderContext> bind/lookup registration call | [V] |
| 0xBBE35A9 | - | - (call target 0x567B570) | `0xBBE35A9  call 0x567B570` | RTX builder sub_bbe2d50 — Declarator<RenderContext> bind/lookup registration call | [V] |

## Verified-negative: module-name strings absent from exe

Exact 6aq module-name strings were searched with `rdis str <name>` over the whole exe; none appear as ASCII or UTF-16, so no per-module call-address binding is provable by string xref:
- averageLuminance: not found (only "PreviousFrameAverageLuminance" at 0x563752e / "AdaptedFrameAverageLuminance" at 0x563d0a5 / "Average Frame Luminance" at 0xf7e4090/0xf7ddb80, all uniform/param names, not the module name) [V negative]
- localExposure: not found (only "LocalExposureApply" 0xf51b04c, "ApplyLocalExposure" 0xf5c918b inside sub_bc9d7a0, not sub_55f1450) [V negative]
- taau: not found as module name (only "#upscaling_mode_radio_taau" 0xf5238e6, "options.upscalingModeOptions.taau" 0xf523901) [V negative]
- clusterLights: not found [V negative]
- volumeScattering: not found as module name (only "VolumeScattering" 0xf5b4987 inside sub_bc7c580, not a Declarator builder) [V negative]
- generateCubemapMips: not found [V negative]
- rayTrace: not found [V negative]
- fidelityfx::fsr1::_FSR1Draw: not found [V negative]
- preprocessingutils: not found [V negative]
- FancyFrameRendererResources / VibrantVisualsFrameRendererResources / RTXMinecraftFrameRendererResources: not found as strings [V negative]

Consequence: registration call addresses exist (3 verified above in sub_bbe2d50; 90 in sub_55f1450, 5 in sub_bbce7b0 per input data) but cannot be associated with specific module names from static analysis. The VV builder sub_55f1450 declares the VV pass order (6ar) and the RTX builder sub_bbe2d50 declares RTX passes, but no string or data-flow ties a specific call site to averageLuminance/localExposure/taau/clusterLights/volumeScattering/generateCubemapMips/rayTrace.

## Verbatim instruction proofs (plain lines for verify_oc)

  0xBBE34B8  call 0x567B570
  0xBBE3545  call 0x567B570
  0xBBE35A9  call 0x567B570

## CLOSES?

CLOSES? NO — single blocking fact: the exact 6aq module-name strings (averageLuminance, localExposure, taau, clusterLights, volumeScattering, generateCubemapMips, rayTrace, fidelityfx::fsr1::_FSR1Draw, preprocessingutils, and the three renderer-resource roots) are absent as ASCII/UTF-16 from the exe (verified negative via rdis str over all sections), so no specific module name can be bound to a specific registration call address from static analysis. Registration call addresses themselves are proven [V] (0xBBE34B8, 0xBBE3545, 0xBBE35A9 in sub_bbe2d50; 90+5 more exist per input data) but are module-unresolved.

## Verification artifacts

- rdis dis 0xbbe34a0 (captures 0xBBE34B8, 0xBBE3545, 0xBBE35A9 `call 0x567B570` lines) [V]
- rdis str averageLuminance/localExposure/taau/clusterLights/volumeScattering (all negative) [V negative]
- Input data: docs/progress/oc_U-C5a.md (sub_55f1450 x90, sub_bbe2d50 x3 at 0xBBE34B8/0xBBE3545/0xBBE35A9, sub_bbce7b0 x5, sub_567b570 = Declarator bind/lookup), docs/progress/oc_U-C5a2.md, docs/BGFX_MAP.md 6aq/6ar

Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-EC5a.md` then `python tools/delegate.py check docs/progress/oc_U-EC5a.md`

## TOOL REQUESTS
- A tool to enumerate every `call 0x567b570` site RVA inside a given function range (would let me list all 90 VV-builder sites); currently found by hand-disassembly windows.
- None written yet.
