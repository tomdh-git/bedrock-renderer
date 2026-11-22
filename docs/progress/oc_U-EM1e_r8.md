## NEXT
DONE

# U-EM1e — M1e Pass lambdas (L6): bloom up bodies DFUpSample / BloomBlend (in/out)

This run covers bloom up: DFUpSample 0xbc9bbd4 / BloomBlend 0xbc9bc28 — hash-static registration stubs, their registered execute guard-thunk bodies, the dispatcher tail-call, and per-pass in/out resources.

Per the r4 correction: bloom "bodies" are hash-static registration sites (data), not separate per-pass code bodies; the shared executed draw body is ScreenDraw 0xbc04dc0 ([V] per prior verified rows), reached via guard thunk -> dispatcher `call qword ptr [0xF9A8C78]`.

## Corrected mismatch rows (re-verified against Minecraft.Windows.exe 1.26.62.01 via rdis)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x568cdcc | 2 | sub_568cdcc | `0x568cdcc  movzx eax,word ptr [rax+8]` | viewId word read *(rax)+0x8; shl eax,6 + lea r13,[rax+rax*4] = viewId*0x140 view stride | [V] |
| 0x568d0b8 | 2 | sub_568d0b8 loop | `0x568d0b8  movzx edx,word ptr [rdx+0x2a]` | word field read rdx+0x2a; offset confirmed +0x2a not +0x2c | [V] |

## Bloom up execute bodies — registration stubs + guard thunks (in/out)

Both bodies are refcount guard thunks: read execute refcount slot, bail (zeroing slots, ret) when uninitialized, otherwise tail-call the dispatcher `call qword ptr [0xF9A8C78]`. 0 direct code xrefs to the bodies; invoked only via data slot 0xF9A8C78.

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc9bbcd | 8 | DFUpSample stub | `0xbc9bbcd  lea r8,[0xF5D96FB]` | "DFUpSample" pass-name string -> r8 | [V] |
| 0xbc9bbd4 | 8 | DFUpSample stub | `0xbc9bbd4  mov rdx,0xF91FF9E312C7E556` | FNV-1 pass-name hash imm (DFUpSample) | [V] |
| 0xbc9bbde | - | DFUpSample stub | `0xbc9bbde  call 0x76AD00` | pass-name resolve via sub_76ad00 | [V] |
| 0xbc9bbe4 | 8 | DFUpSample stub | `0xbc9bbe4  lea rcx,[0xBC9C850]` | execute-body address 0xbc9c850 -> rcx | [V] |
| 0xbc9bbeb | - | DFUpSample stub | `0xbc9bbeb  call 0xE935740` | execute-body registration via sub_e935740 | [V] |
| 0xbc9bbf0 | 8 | DFUpSample stub | `0xbc9bbf0  lea rcx,[0x12AE1E88]` | pass execute slot 0x12AE1E88 -> rcx | [V] |
| 0xbc9bbf7 | - | DFUpSample stub | `0xbc9bbf7  call 0xE938D70` | pass-slot registration via sub_e938d70 (DFUpSample -> slot 0x12AE1E88) | [V] |
| 0xbc9bc21 | 8 | BloomBlend stub | `0xbc9bc21  lea r8,[0xF5ED9E9]` | "BloomBlend" pass-name string -> r8 | [V] |
| 0xbc9bc28 | 8 | BloomBlend stub | `0xbc9bc28  mov rdx,0x7ADA5C0EF1420F87` | FNV-1 pass-name hash imm (BloomBlend) | [V] |
| 0xbc9bc32 | - | BloomBlend stub | `0xbc9bc32  call 0x76AD00` | pass-name resolve via sub_76ad00 | [V] |
| 0xbc9bc38 | 8 | BloomBlend stub | `0xbc9bc38  lea rcx,[0xBC9C8E0]` | execute-body address 0xbc9c8e0 -> rcx | [V] |
| 0xbc9bc3f | - | BloomBlend stub | `0xbc9bc3f  call 0xE935740` | execute-body registration via sub_e935740 | [V] |
| 0xbc9bc44 | 8 | BloomBlend stub | `0xbc9bc44  lea rcx,[0x12AE1EC0]` | pass execute slot 0x12AE1EC0 -> rcx | [V] |
| 0xbc9bc4b | - | BloomBlend stub | `0xbc9bc4b  call 0xE938D70` | pass-slot registration via sub_e938d70 (BloomBlend -> slot 0x12AE1EC0) | [V] |
| 0xbc9c854 | 8 | DFUpSample body 0xbc9c850 | `0xbc9c854  mov rax,[0x12AE1E78]` | DFUpSample guard: execute refcount slot read | [V] |
| 0xbc9c861 | 8 | DFUpSample body 0xbc9c850 | `0xbc9c861  mov rcx,[0x12AE1E60]` | DFUpSample guard: refcount list-head ptr read | [V] |
| 0xbc9c8ca | - | DFUpSample body 0xbc9c850 | `0xbc9c8ca  call qword ptr [0xF9A8C78]` | DFUpSample guard: dispatcher indirect tail-call via data slot 0xF9A8C78 | [V] |
| 0xbc9c895 | 8 | DFUpSample body bail | `0xbc9c895  mov qword ptr [0x12AE1E70],0` | DFUpSample bail: refcount slot cleared | [V] |
| 0xbc9c8a0 | 8 | DFUpSample body bail | `0xbc9c8a0  mov qword ptr [0x12AE1E78],0xF` | DFUpSample bail: slot reset to 0xF | [V] |
| 0xbc9c8ab | 1 | DFUpSample body bail | `0xbc9c8ab  mov byte ptr [0x12AE1E60],0` | DFUpSample bail: head byte cleared | [V] |
| 0xbc9c8e4 | 8 | BloomBlend body 0xbc9c8e0 | `0xbc9c8e4  mov rax,[0x12AE1EB0]` | BloomBlend guard: execute refcount slot read | [V] |
| 0xbc9c8f1 | 8 | BloomBlend body 0xbc9c8e0 | `0xbc9c8f1  mov rcx,[0x12AE1E98]` | BloomBlend guard: refcount list-head ptr read | [V] |
| 0xbc9c95a | - | BloomBlend body 0xbc9c8e0 | `0xbc9c95a  call qword ptr [0xF9A8C78]` | BloomBlend guard: dispatcher indirect tail-call via data slot 0xF9A8C78 | [V] |
| 0xbc9c925 | 8 | BloomBlend body bail | `0xbc9c925  mov qword ptr [0x12AE1EA8],0` | BloomBlend bail: refcount slot cleared | [V] |
| 0xbc9c930 | 8 | BloomBlend body bail | `0xbc9c930  mov qword ptr [0x12AE1EB0],0xF` | BloomBlend bail: slot reset to 0xF | [V] |
| 0xbc9c93b | 1 | BloomBlend body bail | `0xbc9c93b  mov byte ptr [0x12AE1E98],0` | BloomBlend bail: head byte cleared | [V] |

## Bloom up — in / out (from the rows above, [V])

- In: DFUpSample execute refcount slot 0x12AE1E78 (read 0xbc9c854), head ptr 0x12AE1E60 (read 0xbc9c861); BloomBlend execute refcount slot 0x12AE1EB0 (read 0xbc9c8e4), head ptr 0x12AE1E98 (read 0xbc9c8f1).
- Out (bail path): 0x12AE1E70/0x12AE1EA8 cleared to 0, 0x12AE1E78/0x12AE1EB0 reset to 0xF, byte [0x12AE1E60]/[0x12AE1E98] cleared to 0. Otherwise out = dispatcher tail-call `call qword ptr [0xF9A8C78]` executing the shared draw body ScreenDraw 0xbc04dc0 ([V] per prior verified rows); ScreenDraw in = drawstate rect x/y +0x88, rect w/h +0x8C, view matrices +0x08/+0x48/+0x9C/+0xDC; out = pass view framebuffer.

## Real executed body

ScreenDraw 0xbc04dc0 — shared executed draw body, reached via guard thunk -> dispatcher `call qword ptr [0xF9A8C78]` (data slot 0xF9A8C78). In: drawstate rect x/y +0x88, rect w/h +0x8C, view matrices +0x08/+0x48/+0x9C/+0xDC. Out: pass view framebuffer.

## CLOSES?

CLOSES? NO — blocking fact: this run covers only bloom up ([V] registration stubs + guard thunks + dispatcher tail-call + in/out). Still unproven/[I]: local exposure 0xbca2671, 0x568d480 tail + 0x568d750 body, RTX denoise UAV writes 0xbcc4b90, plus Fancy clear/Pass/TerrainAtlasBlit data rows, Convolve body, and deferred bodies (only 0xbc2c590 verbatim [V]; others [I structure]). Item requires all 35 VV/RTX lambdas + Fancy pass bodies each with in/out.

## TOOL REQUESTS

None — all quoted instructions confirmed verbatim via rdis against Minecraft.Windows.exe 1.26.62.01; no new helper script needed.

## NEXT
DONE
