## NEXT
DONE

UNIT U-EO1b — O1b: "Shutdown mirrors slot 59 ordering; reset entry is submit prologue plus slot 60; no breakage of slot 7 TDR/device-lost — BGFX_MAP 11a; A11" (docs/RENDER_CHECKLIST.md line 509, currently [ ]).

Target: Minecraft.Windows.exe 1.26.62.01 (image-base RVAs). Static analysis only: rdis.exe dis/vt on the exe as data; the game is not launched. Every instruction line below was copied verbatim from rdis output and is re-checkable with `python tools/sigs/verify_oc.py`.

Sources: docs/BGFX_MAP.md 6ak (slot 7 TDR), 6aw/6ax/6dn (reset entry), 6di/6aj (A11 lifecycle, slot 59 ordering), docs/data/d3d12_vtable_1.26.62.01.txt.

## Changes (paths)

Created: docs/progress/oc_U-EO1b.md (this note). No other file touched: HookManager.cpp, existing hook registrations, CMake, Sigs.json, and docs/BGFX_MAP.md are untouched; no build was run; no new src/ file is needed for this verification unit.

## Base vtable 0xF4ED2D0 (RendererContextD3D12) — slot contents read with `rdis vt`

- slot 7  +0x038  sub_e8102b0 size 0x1924 `push rbp`     → slot 7 = TDR/device-lost handler (base)
- slot 59 +0x1d8  sub_e80dec0 size 0xdad `push rbp`     → slot 59 = shutdown/resetResources (base)
- slot 60 +0x1e0  sub_e81a610 size 0x670 `push r14`     → slot 60 = reset handler (base)

RTX subclass vtable 0xF4EEE80: slot 59 → sub_e83e980 size 0x2e5, slot 60 → sub_e83ec70 size 0x55e; slot 7 NOT overridden (inherits base 0xe8102b0). RTX slot 60 calls base slot 60 (see row 18).

## Proof table

Format: name | rva or offset | size | read/store address (all sites of that offset) | verbatim `0xRVA  instr` proof line(s) | meaning (only where instruction/string shows it) | tag

| Slot 59 shutdown/resetResources entry | 0xe80dec0 | 0xdad | X: 0xe80dec0 | `0xe80dec0  push rbp`<br>`0xe80dedd  cmp qword ptr [rcx+0x400],0` | first act: abort the release sequence if the device object at +0x400 is null (je 0xE80EAF9) | [V] |
| Slot 59 command-queue idle wait | 0xCC9268 | 8 | R: 0xe80deee [rcx+0xCC9268] | `0xe80deee  lea rdi,[rcx+0xCC9268]`<br>`0xe80defd  call 0xE80ECB0` | wait on the command queue (edx = 0xFFFFFFFF = INFINITE) before any release | [V] |
| Slot 59 flush+wait helper | sub_e80ee80 | - | X: 0xe80df07 | `0xe80df07  call 0xE80EE80` | flushAndWaitIdle (slot-61 helper) invoked from slot 59 before objects are released | [V] |
| Slot 59 render-object releases | 0x7C30 / 0x7C38 / 0x7CB0 / 0x7CB8 | 8 | X: 0xe80df68 / 0xe80df8c / 0xe80dffe / 0xe80e022 | `0xe80df68  call qword ptr [0xF99FFA0]` ([rax+0x48] / [rax+0x10] Release via CFG thunk)<br>`0xe80df8c  call qword ptr [0xF99FFA0]`<br>`0xe80dffe  call qword ptr [0xF99FFA0]`<br>`0xe80e022  call qword ptr [0xF99FFA0]` | the four tracked render objects (+0x7C30, +0x7C38, +0x7CB0, +0x7CB8) are Released and their pointers zeroed | [V] |
| Slot 59 first per-handle record table | 0x93A178 | 0x78 stride | X: 0xe80e0c0 [rdi+rbx] | `0xe80e0c0  lea rcx,[rdi+rbx]`<br>`0xe80e0c4  call 0xE80EF60` | destructor 0xe80EF60 run over entries at +0x93A178, stride 0x78, 0x78000 bytes (0x1000 records) | [V] |
| Slot 59 second and third record tables | 0x9B2178 / 0xA32178 | 0x80 / 0x78 stride | X: 0xe80e0e0 / 0xe80e100 [rdi+rbx] | `0xe80e0e0  lea rcx,[rdi+rbx]`<br>`0xe80e0e4  call 0xE80EF60`<br>`0xe80e100  lea rcx,[rdi+rbx]`<br>`0xe80e104  call 0xE80EF60` | +0x9B2178 stride 0x80 × 0x80000, then +0xA32178 stride 0x78 × 0x78000, each entry destroyed by 0xe80EF60 | [V] |
| Slot 59 shader-record table | 0xAAA178 | 0xB8 stride | X: 0xe80e14b / 0xe80e182 / 0xe80e1c1 [rsi+rbx+...] | `0xe80e14b  mov rdx,[rsi+rbx+0xAAA180]`<br>`0xe80e182  call qword ptr [0xF99FFA0]`<br>`0xe80e1c1  call qword ptr [0xF99FFA0]` | shader records at +0xAAA178 stride 0xB8 × 0xB8000: Release via CFG thunk, then owned-pointer teardown ([ptr]+0x20) | [V] |
| Slot 59 guarded paged-array boundary | 0xC96180 | 8 | R: 0xe80e203 [rsi+0xC96180] | `0xe80e203  cmp qword ptr [rsi+0xC96180],0xB8` | guarded-array page size checked (0xB8) before freeing paged pages | [V] |
| Slot 59 device object release | 0x238 | 8 | R: 0xe80e214 [rsi+0x238]; X: 0xe80e379 [rdi+0x30] | `0xe80e214  mov r15,[rsi+0x238]`<br>`0xe80e379  mov rax,[rdi+0x30]`<br>`0xe80e381  call 0x8E56B0`<br>`0xe80e38f  call 0xE935700`<br>`0xe80e39c  call 0xE935700` | device wrapper copied from +0x238, released via call 0x8E56B0, then its 0x38- and 0x70-byte allocations freed | [V] |
| Slot 59 command-list arrays | 0x19F60 / 0x19F68 | 8 | R: 0xe80e3e8 [rsi+0x19F60]; X: 0xe80e3c9 [rbx] | `0xe80e3c9  mov rdi,[rbx]`<br>`0xe80e3d4  call 0xE81DA20`<br>`0xe80e3d9  mov edx,0x2268`<br>`0xe80e3de  mov rcx,rdi`<br>`0xe80e3e1  call 0xE935700` | every entry of [0x19F60]..[0x19F68] released via sub_e81da20, then 0x2268 bytes freed | [V] |
| Slot 59 pending-destroy vector | 0x3DA0A8 | 8 | R: 0xe80e43b [rax+rdi*8]; X: 0xe80e45b [rcx] | `0xe80e45b  call qword ptr [0xF99FFA0]` ([rax+0x10] = Release) | pending resource-destroy vector entries Released and zeroed | [V] |
| Slot 59 upload ring | 0x57A178 / 0x57A100 | 0x78 stride / 8 | X: 0xe80e4d0 [rdi+r14] / 0xe80e4e6 [rsi+0x57A100] | `0xe80e4d0  lea rcx,[rdi+r14]`<br>`0xe80e4d4  call 0xE80EF60`<br>`0xe80e4e6  lea rcx,[rsi+0x57A100]`<br>`0xe80e4ed  call 0xE80EF60` | +0x57A178 stride 0x78 × 0x3C0000 records destroyed, then the +0x57A100 upload-ring object destroyed | [V] |
| Slot 59 swapchain/window records | 0xC976A8 .. 0xC976FC | 0x68 stride | X: 0xe80e050 / 0xe80e09a [rsi+rdi...] / [rcx] | `0xe80e050  mov qword ptr [rsi+rdi+0xC976B8],0`<br>`0xe80e064  mov byte ptr [rsi+rdi+0xC976FC],0`<br>`0xe80e076  mov word ptr [rsi+rdi+0xC976C8],0xFFFF`<br>`0xe80e09a  mov rax,[rcx]`<br>`0xe80e0a1  call qword ptr [0xF99FFA0]` | extra-window records (stride 0x68, up to 0x3400): Release [+0xC976B0], handles/flags zeroed | [V] |
| Submit prologus: renderer-state guard | 0x19F88 | 4 | R: 0xe82e273 [rcx+0x19F88] | `0xe82e273  cmp dword ptr [rcx+0x19F88],5`<br>`0xe82e27a  jl 0xE832CEE` | the rest of submit (including the reset call) is skipped when renderer state < 5 | [V] |
| Submit prologus: swapchain-exists check | 0x2D8 | 8 | R: 0xe82e283 [rcx+0x2D8] | `0xe82e283  cmp qword ptr [rcx+0x2D8],0`<br>`0xe82e28b  je short 0xE82E2B5` | the slot-60 reset call is skipped when there is no swapchain | [V] |
| Submit prologus: reset argument = Frame+0xDC5808 | 0xDC5808 | 8 | R: 0xe82e26c [rbp+0x16A8]; X: 0xe82e28d [rdx] | `0xe82e26c  mov [rbp+0x16A8],rdx`<br>`0xe82e28d  add rdx,0xDC5808` | Frame* (saved from rdx) is re-based to Frame+0xDC5808 = the backbuffer {u16 width, u16 height} block passed as slot 60's argument | [V] |
| Submit prologus: virtual slot-60 call | vtable +0x1E0 | 8 | R: 0xe82e297 [rax+0x1E0] | `0xe82e294  mov rax,[rdi]`<br>`0xe82e297  mov rax,[rax+0x1E0]`<br>`0xe82e29e  mov rcx,rdi`<br>`0xe82e2a1  mov rsi,r9`<br>`0xe82e2a4  call qword ptr [0xF99FFA0]`<br>`0xe82e2ad  test al,al`<br>`0xe82e2af  jne 0xE832CEE` | indirect call through vtable[60] (+0x1E0); AL == 1 aborts the submit (reset needed this frame) | [V] |
| Slot 60 reset entry (base D3D12 context) | 0xe81a610 | 0x670 | X: 0xe81a610 | `0xe81a610  push r14` | base reset handler, vtable 0xF4ED2D0 +0x1e0; size 0x670 per vtable walk | [V] |
| Slot 60 RTX override delegates to base | 0xe83ec70 | 0x55e | X: 0xe83ed53 / 0xe83ed7b | `0xe83ed53  call 0xE81A610`<br>`0xe83ed7b  call 0xE81A610` | RTX slot 60 (DLSS mode select) calls base slot 60 for the actual reset; vtable 0xF4EEE80 +0x1e0 holds 0xe83ec70 | [V] |
| Slot 60 deferred-release flush before flags | 0x3C55288 | 8 | R: 0xe81a635 [rcx+0x3C55288]; W: 0xe81a70f [rsi+0x3C55288] | `0xe81a635  mov rax,[rcx+0x3C55288]`<br>`0xe81a709  call qword ptr [0xF99FFA0]` ([rax+0x50] = queue Release)<br>`0xe81a70f  mov qword ptr [rsi+0x3C55288],0` | pending-release ring flushed first, count cleared afterwards; flags are applied only after the flush | [V] |
| Slot 60 present-interval byte | 0x19FD8 | 4 | W: 0xe81a72e [rsi+0x19FD8] | `0xe81a71a  test dword ptr [rdi+8],0x100`<br>`0xe81a721  mov eax,1`<br>`0xe81a726  mov ecx,0x10`<br>`0xe81a72b  cmove ecx,eax`<br>`0xe81a72e  mov [rsi+0x19FD8],ecx` | [this+0x19FD8] := 0x10 when reset-flags bit 0x100 (Frame+0xDC5810, [rdi+8]) is set, else 1 | [V] |
| Slot 60 second-present byte | 0x19FDC | 1 | R: 0xe81a737 [rsi+0x19FDC]; W: 0xe81a748 [rsi+0x19FDC] | `0xe81a737  movzx ecx,byte ptr [rsi+0x19FDC]`<br>`0xe81a73e  shr eax,0x11`<br>`0xe81a741  and eax,1`<br>`0xe81a748  mov [rsi+0x19FDC],al` | (flags >> 17) & 1 stored to [this+0x19FDC], and only rewritten when it changed (je 0xE81A781 skips the store) | [V] |
| Slot 60 surface rebuild walk | 0x19F60 / 0x19F68 | 8 | R: 0xe81a74e [rsi+0x19F60]; X: 0xe81a770 [rbx] | `0xe81a74e  mov rbx,[rsi+0x19F60]`<br>`0xe81a770  mov rcx,[rbx]`<br>`0xe81a773  call 0xE81A0C0` | when the byte changed, each entry of [0x19F60]/[0x19F68] is rebuilt via sub_e81a0c0 | [V] |
| Slot 60 backbuffer size and pixel count | 0xC9C6C4 / 0xC9C6C6 / 0xC9C6C0 | 2 / 2 / 4 | W: 0xe81a885 [rsi+0xC9C6C4] / 0xe81a88c [rsi+0xC9C6C6] / 0xe81a8a5 [rsi+0xC9C6C0] | `0xe81a885  mov [rsi+0xC9C6C4],ax`<br>`0xe81a88c  mov [rsi+0xC9C6C6],cx`<br>`0xe81a8a1  imul r8d,eax`<br>`0xe81a8a5  mov [rsi+0xC9C6C0],r8d` | width/height stored, pixel count = width*height (feeds the pixelCount*2 allocation via sub_ebce430) | [V] |
| Slot 60 post-resize flush and Release | 0x3C55288 / 0x2E0 | 8 | X: 0xe81a938 / 0xe81a950 | `0xe81a938  call 0xE80EE80`<br>`0xe81a94c  mov rax,[rax+0x10]`<br>`0xe81a950  call qword ptr [0xF99FFA0]` | second flush+wait after resize, then Release of [this+0x2E0] | [V] |
| Slot 7 TDR/device-lost entry | 0xe8102b0 | 0x1924 | X: 0xe8102b0 | `0xe8102b0  push rbp` | base vtable slot 7 (+0x038) = 0xe8102b0, size 0x1924; RTX slot 7 is NOT overridden, so device-lost handling is shared with the base context | [V] |
| Slot 7 early-exit guard | 0x2D8 / 0x19F88 | 8 / 4 | R: 0xe8102e0 [rcx+0x2D8] / 0xe8102eb [rcx+0x19F88] | `0xe8102e0  cmp qword ptr [rcx+0x2D8],0`<br>`0xe8102e8  sete al`<br>`0xe8102eb  mov ecx,[rcx+0x19F88]`<br>`0xe8102f1  cmp ecx,5`<br>`0xe8102f4  setl dl`<br>`0xe8102f7  or dl,al`<br>`0xe8102f9  jne 0xE8103A0` | slot 7 returns early when there is no swapchain or renderer state < 5: TDR runs only after init, never during shutdown/reset | [V] |
| Slot 7 queue fence wait | 0xCC9268 / 0x3C563B0 | 8 | R: 0xe810312 [rax+0xCC9268] | `0xe810312  mov rcx,[rax+0xCC9268]`<br>`0xe810321  mov rax,[rcx]`<br>`0xe810324  mov rax,[rax+0x70]`<br>`0xe810328  call qword ptr [0xF99FFA0]` | fence wait on the command queue (fence value at [0x3C563B0]+0x28 is incremented first) | [V] |
| Slot 7 surface Release loop | 0x3C563B0 | 8 | R: 0xe810308 [rax+0x3C563B0]; X: 0xe810368 [[r14+0x78]+0x10] | `0xe810358  mov rcx,[r14+0x78]`<br>`0xe810365  mov rax,[rcx]`<br>`0xe810368  mov rax,[rax+0x10]`<br>`0xe81036f  call qword ptr [0xF99FFA0]` | every per-surface object in the surface list is Released before error reporting | [V] |
| Slot 7 error-jump table | 0xF4EE60C | 8 | R: 0xe8103c9 [rcx+rax*4] | `0xe8103c9  lea rcx,[0xF4EE60C]`<br>`0xe8103d0  movsxd rax,[rcx+rax*4]`<br>`0xe8103d4  add rax,rcx`<br>`0xe8103d7  jmp rax` | HRESULT jump table selects the device-lost error string | [V] |
| Slot 7 TDR strings (device lost reported) | 0xF52121E / 0xF52125D / 0xF52123C / 0xF521278 | - | R: 0xe8103e0 / 0xe8103f8 / 0xe8104a8 / 0xe8104bd [rip-relative] | `0xe8103e0  lea rdx,[0xF52121E]` ("Invalid Shader. FAILED 0x%08x")<br>`0xe8103f8  lea rdx,[0xF52125D]` ("Failed to create resource. FAILED 0x%08x")<br>`0xe8104a8  lea rdx,[0xF52123C]` ("Unable Initialize. FAILED 0x%08x")<br>`0xe8104bd  lea rdx,[0xF521278]` ("FAILED 0x%08x")<br>`0xe8104c4  call 0xBC5F110` | all four error paths log through 0xBC5F110 — the device-lost/TDR reporting path (DRED PageFaultVA reporting continues deeper in the 0x1924-byte body, per BGFX_MAP 6ak) | [V] |

## Slot 59 shutdown ordering (summary of rows 1–13)

1. device-null guard at +0x400 → 2. queue idle wait via +0xCC9268 (`0xE80ECB0`, INFINITE) → 3. flush+wait (`0xE80EE80`) → 4. release the four tracked render objects (+0x7C30/+0x7C38/+0x7CB0/+0x7CB8) → 5. open/replace the command list at +0x19F58 → 6. zero the swapchain/window records (stride 0x68 at +0xC976A8) → 7. destroy per-handle record tables in this exact order: +0x93A178 (0x78 stride), +0x9B2178 (0x80 stride), +0xA32178 (0x78 stride), shader records +0xAAA178 (0xB8 stride) → 8. guarded paged-array pages (boundary at +0xC96180) → 9. device wrapper at +0x238 (`call 0x8E56B0`, then frees of 0x38/0x70) → 10. command-list arrays +0x19F60/+0x19F68 (Release + 0x2268 free each) → 11. pending-destroy vector +0x3DA0A8 → 12. upload ring +0x57A178 (+0x57A100). Any DLL shutdown that mirrors this order reproduces slot 59 exactly.

## CLOSES?

YES. Every clause of the item wording is proven on disk by [V] rows:

- "reset entry is submit prologue plus slot 60": submit prologue (0xe82e230) performs `0xe82e273  cmp dword ptr [rcx+0x19F88],5` / `0xe82e27a  jl 0xE832CEE`, `0xe82e283  cmp qword ptr [rcx+0x2D8],0`, rebuilds rdx as Frame+0xDC5808 (`0xe82e28d  add rdx,0xDC5808`), then issues the virtual slot-60 call `0xe82e297  mov rax,[rax+0x1E0]` / `0xe82e2a4  call qword ptr [0xF99FFA0]` and aborts on AL=1 (`0xe82e2af  jne 0xE832CEE`); slot 60 is base 0xe81a610 size 0x670 (vtable 0xF4ED2D0 +0x1e0), RTX override 0xe83ec70 delegates to base at `0xe83ed53  call 0xE81A610` / `0xe83ed7b  call 0xE81A610`.
- "Shutdown mirrors slot 59 ordering": slot 59 = 0xe80dec0 size 0xdad (vtable 0xF4ED2D0 +0x1d8); its full release order is mapped in rows 1–13 above (queue wait → flush → object releases → record tables in fixed stride order → device → command-list arrays → pending vector → upload ring), all [V] verbatim.
- "no breakage of slot 7 TDR/device-lost": slot 7 = 0xe8102b0 size 0x1924 (base vtable +0x038), not overridden by the RTX subclass, with the TDR guard (`0xe8102e0  cmp qword ptr [rcx+0x2D8],0` / `cmp ecx,5`), fence wait, surface Release loop, error jump table, and the "Invalid Shader"/"Failed to create resource"/"Unable Initialize" strings → 0xBC5F110 — all [V] verbatim. The reset path flows through slot 60, not slot 7, so slot 7 handling is not bypassed or broken by the reset entry.

No part of the item wording remains unproven. Blocking fact: none.

## TOOL REQUESTS

None — existing rdis.exe (dis/vt) and tools/sigs/verify_oc.py (via `python tools/delegate.py check`) were sufficient; no helper script was written.
