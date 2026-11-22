## NEXT
DONE

# oc U-EF1b — VV pass in/out resources from execute bodies (checklist F1b pending part)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis disassembly of .text). Builder: 0x55f1450..0x563f594.

Pending passes for F1b (6 already have [V] rows elsewhere; do NOT redo):
ClearGBuffer/ScenePrepass, ClearStencil/WaterSurfaceStencil, TransparentDegamma,
WaitOnUpscalingOutput, FullScreenOverlayObjects, FullScreenOverlayTransparent.

## Decode method (verified)

- pass-object vtables are installed into the freshly allocated pass object (`mov [obj],rax` / `mov [obj],rcx`) by the declare helper, NOT by inline `lea rax,[rip+vtable]` in the builder.
- slot-1 of these vtables is NOT the `lea r8 -> body -> jmp 0xBC61560` installer used by the raster vtables (0xF25C790/0xF25C830/etc.); e.g. vt 0xF25C610 slot1 = sub_76900 (`mov rax,[rcx]`), vt 0xF09AA70 slot1 = sub_76900 (`mov rax,[rcx]`). So the pending passes use a different execute dispatch than the slot-1-thunk bodies — the per-pass execute body and its named resource reads/writes remain the open blocker.
- Name strings are inline 16-byte .rdata chunks stored into the pass object at obj+0x0 / obj+0x10 via movups/movupd.

## [V] rows — name string xref -> pass-object vtable -> resource accesses

| offset | size | site | instr | meaning | tag |
|---|---|---|---|---|---|
| 0x55ff662:[rdi] | 16 | [rdi] | `0x55ff662  movups [rdi],xmm0` | ClearGBuffer/ScenePrepass: write pass-object name chunk "[ClearGBuffer][S" at obj+0x0 | [V] |
| 0x55ff657:[rdi+0x10] | 16 | [rdi+0x10] | `0x55ff657  movups [rdi+0x10],xmm0` | ClearGBuffer/ScenePrepass: write pass-object name chunk "r][ScenePrepass]" at obj+0x10 | [V] |
| 0x55ff65b:[0xF640F15] | 16 | [0xF640F15] | `0x55ff65b  movups xmm0,[0xF640F15]` | ClearGBuffer/ScenePrepass: load name chunk 1 from .rdata | [V] |
| 0x55ff650:[0xF640F21] | 16 | [0xF640F21] | `0x55ff650  movups xmm0,[0xF640F21]` | ClearGBuffer/ScenePrepass: load name chunk 2 from .rdata | [V] |
| 0x560b051:[rdi] | 16 | [rdi] | `0x560b051  movups [rdi],xmm0` | ClearStencil/WaterSurfaceStencil: write pass-object name chunk "[ClearStencil][W" at obj+0x0 | [V] |
| 0x560b046:[rdi+0x10] | 16 | [rdi+0x10] | `0x560b046  movups [rdi+0x10],xmm0` | ClearStencil/WaterSurfaceStencil: write pass-object name chunk "aterSurfaceStencil]" at obj+0x10 | [V] |
| 0x560b04a:[0xF66C679] | 16 | [0xF66C679] | `0x560b04a  movups xmm0,[0xF66C679]` | ClearStencil/WaterSurfaceStencil: load name chunk 1 from .rdata | [V] |
| 0x560b03f:[0xF66C689] | 16 | [0xF66C689] | `0x560b03f  movups xmm0,[0xF66C689]` | ClearStencil/WaterSurfaceStencil: load name chunk 2 from .rdata | [V] |
| 0x562d06f:[rsi] | 16 | [rsi] | `0x562d06f  movups [rsi],xmm0` | WaitOnUpscalingOutput: write pass-object name "WaitOnUpscalingOutput" at obj+0x0 | [V] |
| 0x562d068:[0xF524D34] | 16 | [0xF524D34] | `0x562d068  movups xmm0,[0xF524D34]` | WaitOnUpscalingOutput: load name from .rdata | [V] |
| 0x562d18e:[rsi] | 8 | [rsi] | `0x562d18e  mov [rsi],rax` | WaitOnUpscalingOutput: install pass-object vtable at obj+0x0 | [V] |
| 0x562d187:[0xF25C610] | 8 | [0xF25C610] | `0x562d187  lea rax,[0xF25C610]` | WaitOnUpscalingOutput: load pass-object vtable address 0xF25C610 (object is 0x130 bytes) | [V] |
| 0x562ef3d:[rsi] | 16 | [rsi] | `0x562ef3d  movupd [rsi],xmm7` | FullScreenOverlayObjects: write pass-object name "FullScreenOverlayObjects" at obj+0x0 | [V] |
| 0x562ef35:[0xF546B7A] | 16 | [0xF546B7A] | `0x562ef35  movupd xmm7,[0xF546B7A]` | FullScreenOverlayObjects: load name chunk from .rdata | [V] |
| 0x562f0ba:[rsi+0x10] | 8 | [rsi+0x10] | `0x562f0ba  mov [rsi+0x10],rax` | FullScreenOverlayObjects: write name suffix "yObjects" at obj+0x10 | [V] |
| 0x562ef4b:[rsi+0x10] | 8 | [rsi+0x10] | `0x562ef4b  mov [rsi+0x10],rax` | FullScreenOverlayObjects: write name suffix "yObjects" at obj+0x10 | [V] |
| 0x567cc76:[rbx] | 8 | [rbx] | `0x567cc76  mov [rbx],rcx` | FullScreenOverlay family: install pass-object vtable at obj+0x0 (inside declare helper sub_567C8B0) | [V] |
| 0x567cc6f:[0xF09AA70] | 8 | [0xF09AA70] | `0x567cc6f  lea rcx,[0xF09AA70]` | FullScreenOverlay family: load pass-object vtable address 0xF09AA70 (object is 0x20 bytes) | [V] |
| 0x562f100:[0xF5342CB] | 8 | [0xF5342CB] | `0x562f100  lea r9,[0xF5342CB]` | FullScreenOverlayTransparent: pass name pointer "FullScreenOverlayTransparent" to declare helper sub_9d6d0 at 0x562f107 | [V] |
| 0x562ef87:[0xF5342CB] | 8 | [0xF5342CB] | `0x562ef87  lea r9,[0xF5342CB]` | FullScreenOverlayTransparent: pass name pointer "FullScreenOverlayTransparent" to declare helper sub_9d6d0 at 0x562ef8e | [V] |
| 0x5610e82:[0xF60D9BC] | 8 | [0xF60D9BC] | `0x5610e82  lea r9,[0xF60D9BC]` | TransparentDegamma: pass name pointer "TransparentDegamma" to declare helper sub_9d6d0 at 0x5610e89 | [V] |

## Vtable -> slot1 -> execute-body status (per pass)

| pass | name string | declare helper | pass-object vtable | slot1 | execute body | tag |
|---|---|---|---|---|---|---|
| ClearGBuffer/ScenePrepass | 0x55FF65B | sub_56A8BB0 (builder call 0x55ff6a5) | not yet located in builder | ? | ? | [?] |
| ClearStencil/WaterSurfaceStencil | 0x560B04A | sub_56685C0 (builder call 0x560b077) | not yet located in builder | ? | ? | [?] |
| WaitOnUpscalingOutput | 0x562D068 | inline vtable store (builder 0x562d187/0x562d18e) | 0xF25C610 [V] | sub_76900 `mov rax,[rcx]` [V] | not a slot-1-thunk body; body not yet decoded | [?] |
| FullScreenOverlayObjects | 0x562EF35 | sub_567C8B0 family (builder) | 0xF09AA70 [V via sub_567C8B0] | sub_76900 `mov rax,[rcx]` [V] | body not yet decoded | [?] |
| FullScreenOverlayTransparent | 0x562F100 | sub_567C8B0 (builder call 0x562f29a) | 0xF09AA70 [V via 0x567cc6f/0x567cc76] | sub_76900 `mov rax,[rcx]` [V] | body not yet decoded | [?] |
| TransparentDegamma | 0x5610E82 | sub_5684660 (builder call 0x5610bd3) | not yet located in builder | ? | ? | [?] |

Note: vtable 0xF25C610 (WaitOnUpscalingOutput) and 0xF09AA70 (FullScreenOverlay) are installed at obj+0x0 but their slot1 is `sub_76900` (`mov rax,[rcx]`), not the `lea r8,<body> / jmp 0xBC61560` installer used by raster passes. So the execute-body dispatch for these 4 passes differs from the already-decoded raster vtables and is not yet resolved statically.

## Resources read/written

No execute-body resource reads/writes decoded yet for any of the 6 pending passes — same blocker as prior runs (helper->vtable assignment and per-body named resource reads/writes not statically resolved). The name-string and vtable-install rows above are the only [V] resource-address rows for these passes.

## CLOSES?
NO — blocking fact: execute bodies and their named resource reads/writes are not yet decoded for ClearGBuffer/ScenePrepass, ClearStencil/WaterSurfaceStencil, TransparentDegamma, WaitOnUpscalingOutput, FullScreenOverlayObjects, FullScreenOverlayTransparent, so not all 12 passes have [V] resource rows. 6 passes already have [V] rows; these 6 have name+vtable [V] rows but no execute-body resource rows.

## TOOL REQUESTS
- None.
