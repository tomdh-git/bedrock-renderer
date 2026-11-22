## NEXT
DONE

# oc U-EF1b — VV pass in/out resources from execute bodies (F1b pending part)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis disassembly of .text). Builder: sub_55f1450 [0x55f1450..0x563f594) [V preflight, oc_U-F1b2.md].

Method (orchestrator rule): the 28-byte pass descriptor is opaque (proven, 5 runs) — per-pass in/out resources live in each pass's EXECUTE body, not its declaration. Map pass name -> declare call in builder 0x55f1450 -> declare helper -> pass object's vtable -> execute slot -> body -> resources read/written by that body.

ScreenDraw precedent [V docs/BGFX_MAP.md 6gz/6ha, docs/progress/oc_U-EM1e.md]: execute bodies write the per-view record at s_ctx [0x12AE1748] + viewId*0x140 (rect +0x1EAB090/+0x1EAB094, mat4 +0x1EAB0A0/+0x1EAB0E0/+0x1EAB120/+0x1EAB160, vec4 +0x1EAB1A0, sort byte +0x1EAB1B2) via sub_EBCE390; view id = word at (*(ctxArg+8))+8.

Rule per row: offset | size | R/W | address | verbatim `0xRVA  instr` proof line | meaning | tag. Meaning only if an instruction/string shows it, else '-'. Sizes: movq 8, movd/movss 4, word 2, byte 1, lea/call '-'. One annotated row per distinct offset; do not paste input data as-is; do not abbreviate. CLOSES? YES only when every pass in the pending order list has a [V] row.

Pending pass names (12, per UPDATE 2026-11-22 after r9; the rest are [V], not redone):
VolumetricsShadows, SampleCascadedShadows, [ClearGBuffer][ScenePrepass], [ClearStencil][WaterSurfaceStencil], TransparentDegamma, WaitOnUpscalingOutput, ForceRasterizedObjects, RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent, FullScreenOverlayObjects, FullScreenOverlayTransparent.

## Pass -> execute body resolution

| pass | declare call site (builder 0x55f1450) | declare helper | object vtable installed at | vtable execute slot | execute body | how proven |
|---|---|---|---|---|---|---|
| VolumetricsShadows | refs 0x55fc1cc / 0x5637edc (lea name 0xF5427D1); call 0x567C8B0 @ 0x55fc20e | ? | ? | ? | ? | not decoded — [?] |
| SampleCascadedShadows | name 0xF5427E4 @ 0x55fc488/0x55fc4d8; hash 0x989445A07245EE08 @ 0x55fc4df | (inline in builder) | 0xF25C660 @ 0x55fc6f8 (`lea rax,[0xF25C660]` / `mov [rsi],rax`) | slot 2 (+0x010) | sub_56d3170 | vt 0xF25C660 dump [V] |
| [ClearGBuffer][ScenePrepass] | name obj @ 0x55ff65b; call 0x56A8BB0 @ 0x55ff6a5 | sub_56A8BB0 | ? | ? | ? | not decoded — [?] |
| [ClearStencil][WaterSurfaceStencil] | name obj @ 0x560b04a; call 0x560b077 | sub_56685C0 | 0xF25C520 @ 0x566866c (`lea rax,[0xF25C520]`) | slot 2 (+0x010) | sub_569a3a0 | vt 0xF25C520 dump [V] |
| TransparentDegamma | name hash 0xFB7D12FFA8AA3473 @ 0x5610e89 (call 0x9D6D0 on 0xF60D9BC); call 0x56876F0 @ 0x5610ee1 | sub_56876F0 | 0xF25B730 @ 0x56877d6 (`lea rax,[0xF25B730]` / `mov [rbp+0x560],rax`) | slot 8 (+0x040) | sub_568cd70 -> 0x568cd90 | vt 0xF25B730 dump [V] |
| WaitOnUpscalingOutput | name "WaitOnUpscalingOutput" @ 0x562d068; object vtable 0xF25C610 @ 0x562d187; call 0x76A8A0 @ 0x562d297 | call 0x76A8A0 | 0xF25C610 @ 0x562d187 (`lea rax,[0xF25C610]` / `mov [rsi],rax`) | slot 2 (+0x010) | sub_56aeeb0 | vt 0xF25C610 dump [V] |
| ForceRasterizedObjects | raster cluster call 0x562e9ca | sub_56AF0F0 | 0xF25C0D0 @ 0x56af1d6 (`lea rax,[0xF25C0D0]`) | slot 8 (+0x040) | sub_568cd70 -> 0x568cd90 | vt 0xF25C0D0 dump [V] |
| RasterizedOpaque | raster cluster hash @ 0x562e96b -> call 0x562e9ca | sub_56AF0F0 | 0xF25C0D0 @ 0x56af1d6 | slot 8 (+0x040) | sub_568cd70 -> 0x568cd90 | vt 0xF25C0D0 dump [V] |
| RasterizedAlphaTest | raster cluster call 0x562eb57 | sub_56B0940 | 0xF25C130 @ 0x56b0a26 (`lea rax,[0xF25C130]`) | slot 8 (+0x040) | sub_568cd70 -> 0x568cd90 | vt 0xF25C130 dump [V] |
| RasterizedTransparent | raster cluster call 0x562ece7 | sub_56B2190 | 0xF25C190 @ 0x56b2276 (`lea rax,[0xF25C190]`) | slot 8 (+0x040) | sub_568cd70 -> 0x568cd90 | vt 0xF25C190 dump [V] |
| FullScreenOverlayObjects | name obj @ 0x562ef35; calls 0xBB66E20 @ 0x562ee0f, 0x5669AE0 @ 0x562f1da | ? | ? | ? | ? | not decoded — [?] |
| FullScreenOverlayTransparent | name hash @ 0x562ef87 / 0x562f100; calls as above | ? | ? | ? | ? | not decoded — [?] |

Body sharing: sub_568cd70 (thunk `0x568cd76  jmp 0x568CD90`) is the execute body for vtables 0xF25B730 / 0xF25B670 / 0xF25C0D0 / 0xF25C130 / 0xF25C190 — one shared body for TransparentDegamma + the four raster passes (proven by identical vt slot 8 in all five vtable dumps [V]). sub_569a3a0 (ClearStencil/WaterSurfaceStencil) and sub_56aeeb0/sub_56d3170 (view-record-only bodies) are separate bodies.

## Reads/writes table (one row per distinct offset accessed by the execute body)

| offset | size | R/W | address | instr | meaning | tag |
| WaitOnUpscalingOutput declare 0x562d187 | - | C | [rsi] = vtable ptr | `0x562d187  lea rax,[0xF25C610]` | - | [V] |
| WaitOnUpscalingOutput declare 0x562d18e | - | C | [rsi] = vtable ptr | `0x562d18e  mov [rsi],rax` | - | [V] |
| WaitOnUpscalingOutput ctxArg+0x8 | 8 | R | ctxArg+0x8 | `0x56aeec6  mov rcx,[rdx+8]` | - | [V] |
| WaitOnUpscalingOutput viewId | 2 | R | (*(ctxArg+8))+0x8 | `0x56aeeca  movzx ecx,word ptr [rcx+8]` | - | [V] |
| WaitOnUpscalingOutput record+0x88 | 8 | R | record+0x88 (rect XY) | `0x56aeedc  movq xmm0,[rsi+0x88]` | - | [V] |
| WaitOnUpscalingOutput record+0x8C | 4 | R | record+0x8C (rect WH) | `0x56aeeec  movd xmm2,[rsi+0x8C]` | - | [V] |
| WaitOnUpscalingOutput view+0x1EAB090 | 4 | W | s_ctx+view*0x140+0x1EAB090 | `0x56aeef4  movd [rdx+r12+0x1EAB090],xmm0` | - | [V] |
| WaitOnUpscalingOutput view+0x1EAB094 | 4 | W | s_ctx+view*0x140+0x1EAB094 | `0x56aef06  movd [rdx+r12+0x1EAB094],xmm2` | - | [V] |
| WaitOnUpscalingOutput view+0x1EAB0A0 | 64 | W | s_ctx+view*0x140+0x1EAB0A0 | `0x56aef44  call 0xEBCE390` | - | [V] |
| WaitOnUpscalingOutput view+0x1EAB0E0 | 64 | W | s_ctx+view*0x140+0x1EAB0E0 | `0x56aef5d  call 0xEBCE390` | - | [V] |
| WaitOnUpscalingOutput view+0x1EAB120 | 64 | W | s_ctx+view*0x140+0x1EAB120 | `0x56aef76  call 0xEBCE390` | - | [V] |
| WaitOnUpscalingOutput view+0x1EAB160 | 64 | W | s_ctx+view*0x140+0x1EAB160 | `0x56aef8f  call 0xEBCE390` | - | [V] |
| WaitOnUpscalingOutput view+0x1EAB1A0 | 16 | W | s_ctx+view*0x140+0x1EAB1A0 | `0x56aefa8  call 0xEBCE390` | - | [V] |
| WaitOnUpscalingOutput record+0x98 | 1 | R | record+0x98 (sort mode) | `0x56aefad  movzx eax,byte ptr [rsi+0x98]` | - | [V] |
| WaitOnUpscalingOutput view+0x1EAB1B2 | 1 | W | s_ctx+view*0x140+0x1EAB1B2 | `0x56aefbb  mov [rcx+r12+0x1EAB1B2],al` | - | [V] |
| SampleCascadedShadows declare 0x55fc6f8 | - | C | [rsi] = vtable ptr | `0x55fc6f8  lea rax,[0xF25C660]` | - | [V] |
| SampleCascadedShadows declare 0x55fc6ff | - | C | [rsi] = vtable ptr | `0x55fc6ff  mov [rsi],rax` | - | [V] |
| SampleCascadedShadows record+0x88 | 8 | R | record+0x88 (rect XY) | `0x56d31c1  movq xmm0,[rsi+0x88]` | - | [V] |
| SampleCascadedShadows record+0x8C | 4 | R | record+0x8C (rect WH) | `0x56d31d1  movd xmm1,[rsi+0x8C]` | - | [V] |
| SampleCascadedShadows view+0x1EAB090 | 4 | W | s_ctx+view*0x140+0x1EAB090 | `0x56d31d9  movd [rcx+rbx+0x1EAB090],xmm0` | - | [V] |
| SampleCascadedShadows view+0x1EAB094 | 4 | W | s_ctx+view*0x140+0x1EAB094 | `0x56d31ee  movd [rcx+rbx+0x1EAB094],xmm1` | - | [V] |
| SampleCascadedShadows view+0x1EAB0A0 | 64 | W | s_ctx+view*0x140+0x1EAB0A0 | `0x56d3228  call 0xEBCE390` | - | [V] |
| SampleCascadedShadows view+0x1EAB0E0 | 64 | W | s_ctx+view*0x140+0x1EAB0E0 | `0x56d3241  call 0xEBCE390` | - | [V] |
| SampleCascadedShadows view+0x1EAB120 | 64 | W | s_ctx+view*0x140+0x1EAB120 | `0x56d325a  call 0xEBCE390` | - | [V] |
| SampleCascadedShadows view+0x1EAB160 | 64 | W | s_ctx+view*0x140+0x1EAB160 | `0x56d3277  call 0xEBCE390` | - | [V] |
| SampleCascadedShadows view+0x1EAB1A0 | 16 | W | s_ctx+view*0x140+0x1EAB1A0 | `0x56d329a  call 0xEBCE390` | - | [V] |
| SampleCascadedShadows record+0x98 | 1 | R | record+0x98 (sort mode) | `0x56d329f  movzx eax,byte ptr [r14+0x98]` | - | [V] |
| SampleCascadedShadows view+0x1EAB1B2 | 1 | W | s_ctx+view*0x140+0x1EAB1B2 | `0x56d32ae  mov [rcx+rbx+0x1EAB1B2],al` | - | [V] |
| ClearStencil/WaterSurfaceStencil declare 0x566866c | - | C | [record] = vtable ptr | `0x566866c  lea rax,[0xF25C520]` | - | [V] |
| ClearStencil/WaterSurfaceStencil record+0x0 | 4 | R | record+0x0 (rect XY) | `0x569a3c6  movd xmm0,[r8]` | - | [V] |
| ClearStencil/WaterSurfaceStencil record+0x4 | 4 | R | record+0x4 (rect WH) | `0x569a3d3  movd xmm2,[r8+4]` | - | [V] |
| ClearStencil/WaterSurfaceStencil view+0x1EAB090 | 4 | W | s_ctx+view*0x140+0x1EAB090 | `0x569a3d9  movd [r9+rdx+0x1EAB090],xmm0` | - | [V] |
| ClearStencil/WaterSurfaceStencil view+0x1EAB094 | 4 | W | s_ctx+view*0x140+0x1EAB094 | `0x569a3eb  movd [r9+rdx+0x1EAB094],xmm2` | - | [V] |
| ClearStencil/WaterSurfaceStencil record+0xC | 1 | R | record+0xC | `0x569a3fd  movzx r8d,byte ptr [rcx+0xC]` | - | [V] |
| ClearStencil/WaterSurfaceStencil record+0x8 | 4 | R | record+0x8 | `0x569a402  movss xmm0,[rcx+8]` | - | [V] |
| ClearStencil/WaterSurfaceStencil view+0x1EAB08E | 2 | W | s_ctx+view*0x140+0x1EAB08E | `0x569a415  mov [rcx+rdx+0x1EAB08E],ax` | - | [V] |
| ClearStencil/WaterSurfaceStencil view+0x1EAB080 | 4 | W | s_ctx+view*0x140+0x1EAB080 | `0x569a41d  mov dword ptr [rcx+rdx+0x1EAB080],0xFFFFFFFF` | - | [V] |
| ClearStencil/WaterSurfaceStencil view+0x1EAB088 | 4 | W | s_ctx+view*0x140+0x1EAB088 | `0x569a428  movss [rcx+rdx+0x1EAB088],xmm0` | - | [V] |
| ClearStencil/WaterSurfaceStencil view+0x1EAB08C | 1 | W | s_ctx+view*0x140+0x1EAB08C | `0x569a431  mov [rcx+rdx+0x1EAB08C],r8b` | - | [V] |
| ClearStencil/WaterSurfaceStencil ctxArg+0x8+0x10 | 8 | R | (*(ctxArg+8))+0x10 | `0x569a43d  mov rcx,[rax+0x10]` | - | [V] |
| ClearStencil/WaterSurfaceStencil call 0x569a441 | - | C | submit dispatch | `0x569a441  call 0xBC60D10` | - | [V] |
| ClearStencil/WaterSurfaceStencil call 0x569a469 | - | C | Encoder::submit | `0x569a469  call 0xBC60740` | - | [V] |
| TransparentDegamma declare 0x5610e82 | - | C | name string ref | `0x5610e82  lea r9,[0xF60D9BC]` | - | [V] |
| TransparentDegamma declare 0x5610e89 | - | C | FNV hash call | `0x5610e89  call 0x9D6D0` | - | [V] |
| TransparentDegamma declare 0x5610ee1 | - | C | register pass | `0x5610ee1  call 0x56876F0` | - | [V] |
| TransparentDegamma declare 0x56877d6 | - | C | [rbp+0x560] = vtable ptr | `0x56877d6  lea rax,[0xF25B730]` | - | [V] |
| TransparentDegamma declare 0x56877dd | - | C | [rbp+0x560] = vtable ptr | `0x56877dd  mov [rbp+0x560],rax` | - | [V] |
| TransparentDegamma body entry 0x568cd76 | - | C | thunk -> body | `0x568cd76  jmp 0x568CD90` | - | [V] |
| TransparentDegamma ctxArg+0x8 | 8 | R | ctxArg+0x8 | `0x568cdc8  mov rax,[rcx+8]` | - | [V] |
| TransparentDegamma viewId | 2 | R | (*(ctxArg+8))+0x8 | `0x568cdcc  movzx eax,word ptr [rax+8]` | - | [V] |
| TransparentDegamma s_ctx | 8 | R | [0x12AE1748] | `0x568cdd0  mov rcx,[0x12AE1748]` | - | [V] |
| TransparentDegamma record+0xF8 | 8 | R | record+0xF8 (rect XY) | `0x568cdde  movq xmm0,[rbx+0xF8]` | - | [V] |
| TransparentDegamma record+0xFC | 4 | R | record+0xFC (rect WH) | `0x568cdee  movd xmm1,[rbx+0xFC]` | - | [V] |
| TransparentDegamma view+0x1EAB090 | 4 | W | s_ctx+view*0x140+0x1EAB090 | `0x568cdf6  movd [rcx+r13+0x1EAB090],xmm0` | - | [V] |
| TransparentDegamma view+0x1EAB094 | 4 | W | s_ctx+view*0x140+0x1EAB094 | `0x568ce0c  movd [rcx+r13+0x1EAB094],xmm1` | - | [V] |
| TransparentDegamma view+0x1EAB0A0 | 64 | W | s_ctx+view*0x140+0x1EAB0A0 | `0x568ce51  call 0xEBCE390` | - | [V] |
| TransparentDegamma view+0x1EAB0E0 | 64 | W | s_ctx+view*0x140+0x1EAB0E0 | `0x568ce6a  call 0xEBCE390` | - | [V] |
| TransparentDegamma view+0x1EAB120 | 64 | W | s_ctx+view*0x140+0x1EAB120 | `0x568ce83  call 0xEBCE390` | - | [V] |
| TransparentDegamma view+0x1EAB160 | 64 | W | s_ctx+view*0x140+0x1EAB160 | `0x568ce9c  call 0xEBCE390` | - | [V] |
| TransparentDegamma view+0x1EAB1A0 | 16 | W | s_ctx+view*0x140+0x1EAB1A0 | `0x568ceb9  call 0xEBCE390` | - | [V] |
| TransparentDegamma record+0x108 | 1 | R | record+0x108 (sort mode) | `0x568cebe  movzx eax,byte ptr [rbx+0x108]` | - | [V] |
| TransparentDegamma view+0x1EAB1B2 | 1 | W | s_ctx+view*0x140+0x1EAB1B2 | `0x568cecc  mov [rcx+r13+0x1EAB1B2],al` | - | [V] |
| TransparentDegamma record+0x10 | 8 | R | record+0x10 (shared_ptr) | `0x568cee4  mov rax,[rbx+0x10]` | - | [V] |
| TransparentDegamma refcount | 4 | W | *(record+0x10)+0x8 | `0x568ceed  lock inc dword ptr [rax+8]` | - | [V] |
| ForceRasterizedObjects call 0x562e9ca | - | C | declare call | `0x562e9ca  call 0x56AF0F0` | - | [V] |
| RasterizedOpaque call 0x562e9ca | - | C | declare call | `0x562e9ca  call 0x56AF0F0` | - | [V] |
| RasterizedAlphaTest call 0x562eb57 | - | C | declare call | `0x562eb57  call 0x56B0940` | - | [V] |
| RasterizedTransparent call 0x562ece7 | - | C | declare call | `0x562ece7  call 0x56B2190` | - | [V] |
| raster vt 0xF25C0D0 0x56af1d6 | - | C | vtable install | `0x56af1d6  lea rax,[0xF25C0D0]` | - | [V] |
| raster vt 0xF25C130 0x56b0a26 | - | C | vtable install | `0x56b0a26  lea rax,[0xF25C130]` | - | [V] |
| raster vt 0xF25C190 0x56b2276 | - | C | vtable install | `0x56b2276  lea rax,[0xF25C190]` | - | [V] |
| shared body 0x568cd90 reads/writes | - | R/W | same as TransparentDegamma rows above | `0x568cd76  jmp 0x568CD90` | - | [V] |

Not covered (blocking CLOSES): VolumetricsShadows, [ClearGBuffer][ScenePrepass], FullScreenOverlayObjects, FullScreenOverlayTransparent — declare helpers / bodies not yet decoded (VolumetricsShadows: refs @ 0x55fc1cc/0x5637edc, call 0x567C8B0 @ 0x55fc20e; ClearGBuffer: sub_56A8BB0 @ 0x55ff6a5; FullScreenOverlay*: calls 0xBB66E20 @ 0x562ee0f, 0x5669AE0 @ 0x562f1da, 0x567C8B0 @ 0x562f29a).

## Verification
- `python tools/sigs/verify_oc.py docs/progress/oc_U-EF1b.md` — all quoted `0xRVA  instr` lines checked against rdis dis output.
- `python tools/delegate.py check docs/progress/oc_U-EF1b.md` — shape/format check.

## CLOSES?
CLOSES? NO — 8 of 12 pending passes have [V] rows (SampleCascadedShadows, [ClearStencil][WaterSurfaceStencil], TransparentDegamma, WaitOnUpscalingOutput, ForceRasterizedObjects, RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent, all with executed-body reads/writes). Blocking fact: 4 passes still have no execute body — VolumetricsShadows, [ClearGBuffer][ScenePrepass], FullScreenOverlayObjects, FullScreenOverlayTransparent — their declare helpers (0x567C8B0/sub_56A8BB0/0xBB66E20/0x5669AE0) and bodies are not yet decoded.
