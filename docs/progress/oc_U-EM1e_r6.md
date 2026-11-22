## NEXT
DONE

# U-EM1e — M1e Pass lambdas (L6): bloom down bodies DFDownSample / ThresholdedDownSample (in/out)

This run covers bloom down: DFDownSample 0xbc99739 / ThresholdedDownSample 0xbc99794 — hash-static registration stubs (FNV-1 imm), their registered execute guard-thunk bodies, the dispatcher tail-call, and per-pass in/out resources.

Per the r4 correction: bloom "bodies" are hash-static registration sites (data), not separate per-pass code bodies; the shared executed draw body is ScreenDraw 0xbc04dc0 ([V] per prior verified rows), reached via guard thunk -> dispatcher `call qword ptr [0xF9A8C78]`.

## Corrected mismatch rows (re-verified against Minecraft.Windows.exe 1.26.62.01 via rdis)

Deleted row: 0x568cdbe — prior claim `movq xmm0,[rbx+f8]` was wrong; 0x568cdbe is not an instruction boundary (it lies inside 0x568cdcc). Row removed; nothing depends on the deleted +0xf8 field offset.

Corrected row: 0x568d0b8 — prior claim `movzx r10d,[r8+0x2C]` was wrong; real instruction is `movzx edx,word ptr [rdx+0x2a]` (field offset +0x2a confirmed, not +0x2c).

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x568cdcc | 2 | sub_568cdc0 | `0x568cdcc  movzx eax,word ptr [rax+8]` | viewId word read *(a0+0x8)+0x8; shl eax,6 + lea r13,[rax+rax*4] = viewId*0x140 view stride | [V] |
| 0x568d0b8 | 2 | sub_568d0b0 loop | `0x568d0b8  movzx edx,word ptr [rdx+0x2a]` | word field read rdx+0x2a; offset confirmed +0x2a not +0x2c | [V] |

## Bloom down execute bodies — registration stubs + guard thunks (in/out)

Both bodies are refcount guard thunks: read execute refcount slot, bail (zero slots, ret) when uninitialized, otherwise tail-call the dispatcher `call qword ptr [0xF9A8C78]`. 0 direct code xrefs to the bodies; invoked only via data slot 0xF9A8C78.

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc99732 | 8 | DFDownSample stub (sub_bc99720) | `0xbc99732  lea r8,[0xF5D973B]` | "DFDownSample" pass-name string -> r8 | [V] |
| 0xbc99739 | 8 | DFDownSample stub | `0xbc99739  mov rdx,0x34E743CD5E04564D` | FNV-1 pass-name hash imm (DFDownSample) | [V] |
| 0xbc99743 | - | DFDownSample stub | `0xbc99743  call 0x76AD00` | pass-name resolve via sub_76ad00 | [V] |
| 0xbc99749 | 8 | DFDownSample stub | `0xbc99749  lea rcx,[0xBC9AC80]` | execute-body address 0xbc9ac80 -> rcx | [V] |
| 0xbc99750 | - | DFDownSample stub | `0xbc99750  call 0xE935740` | execute-body registration via sub_e935740 | [V] |
| 0xbc99755 | 8 | DFDownSample stub | `0xbc99755  lea rcx,[0x12AE1DB0]` | pass execute slot 0x12AE1DB0 -> rcx | [V] |
| 0xbc9975c | - | DFDownSample stub | `0xbc9975c  call 0xE938D70` | pass-slot registration via sub_e938d70 (DFDownSample -> slot 0x12AE1DB0) | [V] |
| 0xbc9978d | 8 | ThresholdedDownSample stub | `0xbc9978d  lea r8,[0xF5D9717]` | "ThresholdedDownSample" pass-name string -> r8 | [V] |
| 0xbc99794 | 8 | ThresholdedDownSample stub | `0xbc99794  mov rdx,0x714FFC3B4FD51617` | FNV-1 pass-name hash imm (ThresholdedDownSample) | [V] |
| 0xbc9979e | - | ThresholdedDownSample stub | `0xbc9979e  call 0x76AD00` | pass-name resolve via sub_76ad00 | [V] |
| 0xbc997a4 | 8 | ThresholdedDownSample stub | `0xbc997a4  lea rcx,[0xBC9AD10]` | execute-body address 0xbc9ad10 -> rcx | [V] |
| 0xbc997ab | - | ThresholdedDownSample stub | `0xbc997ab  call 0xE935740` | execute-body registration via sub_e935740 | [V] |
| 0xbc997b0 | 8 | ThresholdedDownSample stub | `0xbc997b0  lea rcx,[0x12AE1DE8]` | pass execute slot 0x12AE1DE8 -> rcx | [V] |
| 0xbc997b7 | - | ThresholdedDownSample stub | `0xbc997b7  call 0xE938D70` | pass-slot registration via sub_e938d70 (ThresholdedDownSample -> slot 0x12AE1DE8) | [V] |
| 0x12ae1da0 | 8 | 0xbc9ac84, 0xbc9acd0 | `0xbc9ac84  mov rax,[0x12AE1DA0]` | DFDownSample guard: execute refcount slot read; <0x10 bails (0xbc9acc5 clears 0x12ae1d98/0x12ae1da0, byte [0x12ae1d88]=0, ret); else refcount link walked | [V] |
| 0x12ae1d88 | 8 | 0xbc9ac91, 0xbc9acdb | `0xbc9ac91  mov rcx,[0x12AE1D88]` | DFDownSample guard: refcount list-head ptr read; bail clears head byte at 0xbc9acdb | [V] |
| 0x12ae1d98 | 8 | 0xbc9acc5 | `0xbc9acc5  mov qword ptr [0x12AE1D98],0` | DFDownSample bail path: refcount slot cleared | [V] |
| 0xf9a8c78 | 8 | 0xbc9acfa, 0xbc9ad8a | `0xbc9acfa  call qword ptr [0xF9A8C78]` | dispatcher indirect call via data slot 0xF9A8C78; DFDownSample body 0xbc9acfa and ThresholdedDownSample body 0xbc9ad8a both tail-call into it | [V] |
| 0x12ae1dd8 | 8 | 0xbc9ad14, 0xbc9ad60 | `0xbc9ad14  mov rax,[0x12AE1DD8]` | ThresholdedDownSample guard: execute refcount slot read; bail resets slot to 0xF at 0xbc9ad60 | [V] |
| 0x12ae1dc0 | 8 | 0xbc9ad21, 0xbc9ad6b | `0xbc9ad21  mov rcx,[0x12AE1DC0]` | ThresholdedDownSample guard: refcount list-head ptr read; bail clears head byte at 0xbc9ad6b | [V] |
| 0x12ae1dd0 | 8 | 0xbc9ad55 | `0xbc9ad55  mov qword ptr [0x12AE1DD0],0` | ThresholdedDownSample bail path: refcount slot cleared | [V] |

## Bloom down — in / out (from the rows above, [V])

- In: DFDownSample execute refcount slot 0x12AE1DA0 (read 0xbc9ac84), head ptr 0x12AE1D88 (read 0xbc9ac91); ThresholdedDownSample execute refcount slot 0x12AE1DD8 (read 0xbc9ad14), head ptr 0x12AE1DC0 (read 0xbc9ad21).
- Out (bail path): 0x12AE1D98/0x12AE1DD0 cleared to 0, 0x12AE1DA0/0x12AE1DD8 reset to 0xF, byte [0x12AE1D88]/[0x12AE1DC0] cleared to 0. Otherwise out = dispatcher tail-call `call qword ptr [0xF9A8C78]` executing the pass body via data slot 0xF9A8C78 (no direct body xrefs). Shared executed draw body ScreenDraw 0xbc04dc0 ([V] per prior verified rows); ScreenDraw in/out = pass view framebuffer out, drawstate rect/material params in.

## CLOSES?

CLOSES? NO — blocking fact: this run covers only bloom down ([V] registration stubs + guard thunks + dispatcher tail-call + in/out). Still unproven/[I]: bloom up bodies 0xbc9bbd4 / 0xbc9bc28, local exposure 0xbca2671, 0x568d480 tail + 0x568d750 body, RTX denoise UAV writes 0xbcc4b90, plus Fancy clear/Pass/TerrainAtlasBlit and Convolve bodies. Item requires all 35 VV/RTX lambdas + Fancy pass bodies each with in/out.

## TOOL REQUESTS

None — input data read from existing progress notes (oc_U-EM1e_r1..r5); all quoted instructions confirmed verbatim via rdis/verify_oc against Minecraft.Windows.exe 1.26.62.01; no new helper script needed.
