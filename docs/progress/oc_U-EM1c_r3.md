## NEXT
DONE

# Unit U-EM1c — M1c Dossiers (D2): RendererContextD3D12 vtable slots 39-45 field map

## What this unit did

Verified the first instruction of each RendererContextD3D12 vtable slot 39-45 target function against the exe via `rdis dis <rva> 2`, and documented each slot's role/size from its instruction-level dossier (docs/functions/<rva>.md). Slots 10-34 were previously named with evidence (6fb); slots 39-45 were the remaining unnamed slots on the base D3D12 vtable (0xf4ed2d0) / RTX subclass vtable (0xf4eee80).

Sources:
- Slot RVAs and sizes: docs/data/d3d12_vtable_1.26.62.01.txt [V]
- First instructions: verified via rdis dis <rva> 2 [V] (match d2_first_instructions.json where present)
- Per-slot behavior: docs/functions/0xe817880.md, 0xe8176a0.md, 0xe817c00.md, 0xe817cf0.md, 0xe817e50.md, 0xe818050.md, 0xe8189c0.md [V instruction-level]

## Field map — RendererContextD3D12 vtable slots 39-45

| slot | size | site (fn RVA) | `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 39 | 0x37b | 0xe817880 | `0xe817880  push r15` | create window-backed framebuffer/swapchain: scans 0x68 fb records at this+0xC97698+handle*0x68, detaches matching window, creates swapchain via sub_e9241b0, per-backbuffer RTV setup loop [V docs/functions/0xe817880.md] |
| 40 | 0xeb | 0xe8176a0 | `0xe8176a0  push r15` | set framebuffer attachments (internal): copies numAttachments*6 bytes into rec+0x34, derives attachment state via sub_e819b50, runs texture state transitions per attachment [V docs/functions/0xe8176a0.md] |
| 41 | 0xe5 | 0xe817c00 | `0xe817c00  push rsi` | destroy framebuffer: releases swapchain via COM vtbl+0x10, clears rec fields, swap-removes handle from window list at this+0x2FA [V docs/functions/0xe817c00.md] |
| 42 | 0x15a | 0xe817cf0 | `0xe817cf0  push r15` | per-context uniform/value buffer reallocation: iterates contexts this+0x19F60..0x19F68, reallocs buffer at context+handle*8+0x1250, tail-calls sub_e804590(this+0xC9AA98, handle, arg4) [V docs/functions/0xe817cf0.md] |
| 43 | 0x1fe | 0xe817e50 | `0xe817e50  push r15` | release uniform/value buffer + handle-map removal: clears context+handle*8+0x1250 via allocator vcall slot 1, removes handle from open-addressing hash table at this+0xC9BAA0 [V docs/functions/0xe817e50.md] |
| 44 | 0x438 | 0xe818050 | `0xe818050  push r15` | screenshot/readback: fence wait via sub_e818490, command-list recording, references "LScreenshot" string, submits and waits [V docs/functions/0xe818050.md] |
| 45 | 0xa1 | 0xe8189c0 | `0xe8189c0  push rsi` | set object name: bounded string copy into this+index*0x100+0x7EDE via sub_ebce650, max length 0xFA [V docs/functions/0xe8189c0.md] |

## Verification

- All 7 first instructions verified against the exe via `rdis dis <rva> 2` [V]; each matches d2_first_instructions.json where present [V].
- Function sizes from docs/data/d3d12_vtable_1.26.62.01.txt [V]; extents proven via .pdata [V rdis sum].
- Each slot's behavior documented at instruction level in its docs/functions/<rva>.md dossier [V].

## Remaining M1c pending parts (not this unit)

- 6cs header-field semantics: header-kind withdrawn per 6de correction; branch A at 0xe822480 not decoded [BGFX_MAP 6cs/6de]
- 6 drain blocks of 0xbc660a0: none of the 6 resource-table bases appear as direct memory operands in the function body [oc_U-EM1c_r1.md]
- Generate per-pass loop body decode: 0xc273420 is D1 dossiered; per-pass structure known but detailed pass-by-pass semantics open [docs/functions/0xc273420.md]
- L4/L5 dossiers: endFrame 0x66232b0 and extractor dossiers exist but not all at D2 instruction-complete

CLOSES? NO — slots 39-45 are now D2-verified with [V] proof rows, but the M1c item requires every pending part to be proven; the single blocking fact is the 6 resource-table drain blocks of 0xbc660a0: none of the six table bases (0x93A178/0x78, 0x9B2178/0x80, ctx+0xC97698/0x68, 0xAAA178/0xB8, 0xB62178/0xF8, 0xBDE178/0xB8, ctx+0xC96198) appear as direct memory operands in 0xbc660a0, so their drain mapping requires render-thread command-consumer tracing beyond static disassembly of that function.

## TOOL REQUESTS

None — used rdis dis <rva> 2 for first-instruction verification and existing docs/functions/<rva>.md dossiers.
