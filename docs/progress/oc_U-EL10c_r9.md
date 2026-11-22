## NEXT
DONE

# Unit U-EL10c — L10c viewport and render-resolution selection, dynamic resolution pending
Item line: "L10c viewport and render-resolution selection, dynamic resolution pending | 2026-11-16 oc_U-Eratio.md (9 rows OK): NO; ctx+0x1F0 store 0x67c791f and TAAU read 0xbc8d34e proven, but source(r13)+0x1F0 writer and link to upscaling_percentage/targetResolution not found (endFrame 0x66232b0 has no direct callers)"

Goal: close the pending part — who stores source(r13)+0x1F0 (the passLookup descriptor +0x1F0, the upscaling-percentage / render-resolution float4) and link it to upscaling_percentage/targetResolution.
Method: static analysis only. Exe = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe 1.26.62.01; RVAs image-relative. Only file written: docs/progress/oc_U-EL10c.md. No live capture names these RVAs (see Live data section).

## Proven chain ([V] rows)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | tag |
|---|---|---|---|---|
| sub_566cb20 struct copy (0x566cb20..0x566d1bb, size 0x69b, 10 xrefs in): descriptor+0x1F0 (float, movss) read from source and written to dest — the descriptor+0x1F0 -> element+0x1F0 link of the copy chain | +0x1F0 | 4 (movss) | `0x566d04a  movss xmm0,[rsi+0x1F0]` / `0x566d052  movss [rdx+0x1F0],xmm0` | [V] |
| sub_67c73d0 struct copy (0x67c73d0..0x67c7a88, size 0x6b8, 3 xrefs in): element+0x1F0 -> ctx+0x1F0 — the proven ctx+0x1F0 store | +0x1F0 | 4 (movss) | `0x67c7917  movss xmm0,[rsi+0x1F0]` / `0x67c791f  movss [rdx+0x1F0],xmm0` | [V] |
| BgfxFrameBuilder::endFrame 0x66232b0 = vtable slot 18 (+0x90) [V; docs/BGFX_MAP.md vtable, vtable at 0xf2bdeb0]; no direct callers (called through vtable/fp). endFrame calls sub_566cb20 at 7 sites (0x6628728, 0x66289cb, 0x662abef, 0x662cc4c, 0x662cc87, 0x662cce0, 0x662cf57) and sub_67c73d0 at 3 sites (0x662ba52, 0x662cd25, 0x662def4); plus sub_566b500 x1, sub_67c82f0 x4, sub_67c7140 x2 — all of these copiers are called ONLY from endFrame | 0x66232b0 | - | - | [V] |
| TAAU (sub_bc8d320) reads ctx+0x1F0; r13 = ctx in TAAU | 0xbc8d34e | 16 (movups) | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | [V] |
| Settings registration: sub_5b0c1b0 registers "upscaling_percentage"/"options.upscalingPercentage" (default 50=0x32) and "target_resolution"/"options.targetResolution" (default 1); setting names loaded via movups from their rodata addresses | 0x5b3e799 / 0x5b3ead0 | 16 (movups) | `0x5b3e799  movups xmm0,[0xF5E13CC]` ("upscaling_percentage") / `0x5b3ead0  movups xmm0,[0xF5850DE]` ("options.targetResolution") | [V] |
| Registration defaults stored to the settings record | [rsp+0x30] | 4 (dword) | `0x5b3e835  mov dword ptr [rsp+0x30],0x32` (upscalingPercentage=50) / `0x5b3eb0c  mov dword ptr [rsp+0x30],1` (targetResolution=1) | [V] |
| sub_51cd6c0 registers "upscaling_percentage" via rodata load | 0x51de12b | 16 (movups) | `0x51de12b  movups xmm0,[0xF5E13CC]` | [V] |

## Not found (blockers)

- Writer of source(r13)+0x1F0 (the passLookup descriptor +0x1F0, i.e. the upscaling-percentage / render-resolution float4 that flows descriptor -> element -> ctx -> TAAU): NOT found statically. Scanned ALL of endFrame 0x66232b0..0x662E680 (6 dis chunks, ~9000 instructions each) — no write to descriptor+0x1F0: no [reg+0x1F0] store of a settings value; only local zeroing ([rbp+0x1F0] locals at 0x662892b..0x6628993) and element +0x1F0 = 0 init at `0x6628fb0  movups [rsi+0x1F0],xmm6`. The descriptor is passed as a parameter (rdx = source) to sub_566cb20/sub_566b500/sub_67c82f0/sub_67c7140/sub_67c73d0, all called only from endFrame, so its +0x1F0 original store is upstream of endFrame and not isolated statically.
- sub_6863670 writes [rbx+0x1F0] (part of the +0x1D8..0x1F4 float4 block) via a dynamic-resolution lerp (xmm8 = min+(max-min)*idx/(max-1)), but it is called from sub_681b6d0/sub_689e100/sub_68a7130, NOT from endFrame — a different object instance; connection to this descriptor and to upscaling_percentage/targetResolution is unproven [I].
- Strings "upscaling_percentage" (0xF5E13CC) and "options.targetResolution" (0xF5850DE) are referenced ONLY by registration code (sub_5b0c1b0 at 0x5b3e799/0x5b3ead0, sub_51cd6c0 at 0x51de12b); `xref.py str` reports refs=[] for both and there is no runtime reader of "options.upscalingPercentage"/"targetResolution" — the link from the registered setting to descriptor+0x1F0 is not proven [I].

## Live data
- docs/data/live/_status.txt: DONE. Grep of docs/data/live/*.txt for 0x67c791f / 0xbc8d34e / 0x566cb20 / 0x566d04a / 0x566d052 / 0x66232b0 / upscaling_percentage / targetResolution: no matches. No capture target exists for this item; it is not in the zero-hit capture list. No live capture names these RVAs, so nothing to re-derive from capture.

## CLOSES?
NO — every pending part is NOT proven. Proven by [V] rows: ctx+0x1F0 store 0x67c791f, TAAU read 0xbc8d34e, the descriptor->element->ctx copy chain (sub_566cb20/sub_67c73d0 called from endFrame), and settings registration (defaults upscalingPercentage=50, targetResolution=1). Single blocking fact: the writer of source(r13)+0x1F0 (passLookup descriptor +0x1F0) and the link from upscaling_percentage/targetResolution to descriptor+0x1F0 are not found statically — endFrame copies but does not write descriptor+0x1F0 (scanned all of 0x66232b0..0x662E680), and the settings strings have no runtime reader.

## TOOL REQUESTS
None.

## CAPTURE REQUESTED
none — a live capture would not identify the static author of descriptor+0x1F0; static analysis of endFrame and the settings string xrefs is exhausted.
