## NEXT
DONE

# oc U-EF1b — VV pass in/out resources from execute bodies (checklist F1b pending part)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis disassembly of .text). Builder: 0x55f1450..0x563f594.

Pending passes (checklist F1b / oc_U-EL6b):
VolumetricsShadows, SampleCascadedShadows, ClearGBuffer/ScenePrepass, ClearStencil/WaterSurfaceStencil, TransparentDegamma, WaitOnUpscalingOutput, ForceRasterizedObjects, RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent, FullScreenOverlayObjects, FullScreenOverlayTransparent.

Decode method (orchestrator 2026-11-22, verified): pass-object vtables are NOT std::function; slot-2 family = name getter (string_view). EXECUTE body is installed per family: sub_5698290 family vt 0xF25C830 slot1 installer sub_5699be0 (`0x5699c60 lea r8,[0x5699E30]`; `0x5699c70 jmp 0xBC61560`) -> body sub_5699E30. For other vtables the execute slot is adjacent to the name-getter slot (e.g. vt 0xF25C660 slot2=sub_56d3170/slot3 name-getter; vt 0xF25C640 slot6=sub_56d3170/slot7 name-getter; raster vtables slot8=sub_568cd70/slot9 name-getter). Per-pass in/out resources are read from the EXECUTE body, not the 28-byte pass descriptor (proven opaque).

Decode status — [V] = seen in disassembly (instruction cited), [I] = inferred from vtable layout, [?] = unknown.

Rows for passes finished this run (one row per pass; shared bodies proved by identical vtable execute slot and given once with a note):

| pass | declare call (builder 0x55f1450) | object vtable | execute body RVA | reads (pass-object/config fields) | writes (resources) | tag |
|---|---|---|---|---|---|---|
| SampleCascadedShadows | 0x55fc7f4 call sub_76a8a0 (name register; obj built with vt 0xF25C660 at 0x55fc6ff; name via 0x55fc4d8 lea r9,[0xF5427E4]) | vt 0xF25C660 | sub_56d3170 [V vt slot 2] | `0x56d31c1  movq xmm0,[rsi+0x88]`; `0x56d31d1  movd xmm1,[rsi+0x8C]`; `0x56d3205  lea r12,[rsi+0x9C]`; `0x56d3270  lea rdx,[rsi+0xDC]` | `0x56d31d9  movd [rcx+rbx+0x1EAB090],xmm0`; `0x56d31ee  movd [rcx+rbx+0x1EAB094],xmm1`; `0x56d32ae  mov [rcx+rbx+0x1EAB1B2],al` (0x1EAB090 = Context+0x1EAB090 per-view array, 6hs) | V body reads/writes; execute-slot [I] |
| VolumetricsShadows | declare call not yet located; name via 0x55fc1c9 lea rax,[0xF5427D1]; obj built with vt 0xF25C640 at 0x55fcc4c | vt 0xF25C640 | sub_56d3170 [V vt slot 6] | same shared body sub_56d3170 (reads pass-obj +0x88,+0x8C,+0x9C,+0x48,+0xDC,+0x98,+0xE0,+0xD8,+0x80,+0xE4,+0x64,+0x10,+0x20,+0x18) | same shared body sub_56d3170 (writes view-record +0x1EAB090/+0x1EAB094/+0x1EAB1B2; refcount lock inc/dec [rcx+8]) | V body (shared with SampleCascadedShadows); execute-slot [I] (vt slot adjacent to name-getter slot 7) |
| ForceRasterizedObjects | 0x562e9ca call sub_56AF0F0 (batch decl, r8d=0 -> sub_56B3A10; [rbp+0x2EF8]='RasterizedOpaque' @0x562e96b, key 0x85202050E504B99D; name obj 'ForceRasterizedObjects' via 0x562e940 movups xmm6,[0xF546BA5]) | vt 0xF25C0D0 [V installed in sub_56AF0F0] | sub_568cd70 thunk -> 0x568cd90 [V vt slot 8; body = generic draw-list task per 6ha] | `0x568cdc8  mov rax,[rcx+8]`; `0x568cdde  movq xmm0,[rbx+0xF8]`; `0x568cdee  movd xmm1,[rbx+0xFC]`; `0x568ce24  lea r14,[rbx+0x14C]`; `0x568cebe  movzx eax,byte [rbx+0x108]` | `0x568cdf6  movd [rcx+r13+0x1EAB090],xmm0`; `0x568ce0c  movd [rcx+r13+0x1EAB094],xmm1`; `0x568cecc  mov [rcx+r13+0x1EAB1B2],al`; `0x568ceed  lock inc dword ptr [rax+8]` (refcount) | V body reads/writes; execute-slot [I] (vt slot 8 adjacent to name-getter slot 9) |
| RasterizedOpaque | same declare site 0x562e9ca call sub_56AF0F0 (name 'RasterizedOpaque'); shares vt 0xF25C0D0 / body sub_568cd70->0x568cd90 with ForceRasterizedObjects | vt 0xF25C0D0 (shared) | sub_568cd70 -> 0x568cd90 (shared body) | shared body sub_568cd70->0x568cd90 (reads +0xF8,+0xFC,+0x18C,+0x14C,+0x10C,+0xB8,+0x108,+0x0,+0x10,+0x8,+0x70,+0x48; reads a1 +0x8) | shared body sub_568cd70->0x568cd90 (writes view-record +0x1EAB090/+0x1EAB094/+0x1EAB1B2; refcount lock inc [rax+8]) | V body shared w/ ForceRasterizedObjects [V same vtable slot 8]; execute-slot [I] |
| RasterizedAlphaTest | 0x562eb57 call sub_56B0940 (batch decl; 'RasterizedAlphaTest' @0x562eaf8); vt installed in helper | vt 0xF25C130 [V] | sub_568cd70 -> 0x568cd90 (shared body; vt 0xF25C130 slot 8 = sub_5688f70? no — slot 8 = sub_568cd70) | shared body sub_568cd70->0x568cd90 | shared body sub_568cd70->0x568cd90 | V body shared w/ ForceRasterizedObjects [V same vtable slot 8]; execute-slot [I] |
| RasterizedTransparent | 0x562ece7 call sub_56B2190 (batch decl, r8d=2 -> sub_56B5C50; 'RasterizedTransparent' @0x562ec85); vt installed in helper | vt 0xF25C190 [V] | sub_568cd70 -> 0x568cd90 (shared body; vt 0xF25C190 slot 8 = sub_568cd70) | shared body sub_568cd70->0x568cd90 | shared body sub_568cd70->0x568cd90 | V body shared w/ ForceRasterizedObjects [V same vtable slot 8]; execute-slot [I] |

NOT yet decoded this run (execute body / reads-writes pending): ClearGBuffer/ScenePrepass, ClearStencil/WaterSurfaceStencil, TransparentDegamma (declare calls 0x5610a3b sub_5682E20 'Opaque', 0x5610bd3 sub_5684660 'Transparent', 0x5610d60 sub_5685EA0 'Opaque', 0x5610ee1 sub_56876f0 'TransparentDegamma'; objects share vtable=xmm7=[0xF546BAA] L22843, value uncertain), WaitOnUpscalingOutput (name 0x562d068 movups [0xF524D34]), FullScreenOverlayObjects/FullScreenOverlayTransparent (sub_5669ae0 calls @0x5610f71,0x562ed77,0x562f1da).

Also decoded (reference, not pending): sub_5698290 family execute body = sub_5699E30 [V: vt 0xF25C830 slot1 installer sub_5699be0 `0x5699c60 lea r8,[0x5699E30]`; `0x5699c70 jmp 0xBC61560`]. Reads pass obj +0xA8/+0xB8/+0xB0/+0x70 (`0x5699e46 mov rax,[rcx+0xA8]`, `0x5699e58 mov rax,[rcx+0xB8]`, `0x5699e73 mov rcx,[r8+0xB0]`, `0x5699e86 mov rcx,[r8+0x70]`); writes `[rcx+0x18]` where rcx=[+0xB0] (`0x5699e82 mov [rcx+0x18],rdx`) and refcount decs. No pending pass confirmed to use sub_5698290.

## Verification
- `python tools/sigs/verify_oc.py docs/progress/oc_U-EF1b.md` — every quoted `0xRVA  instr` copied verbatim from rdis output.
- `python tools/delegate.py check docs/progress/oc_U-EF1b.md` — run next.

## CLOSES?
NO — 6 of 12 pending passes have rows (SampleCascadedShadows, VolumetricsShadows, ForceRasterizedObjects, RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent). Blocking fact: execute bodies / reads-writes not yet decoded for ClearGBuffer/ScenePrepass, ClearStencil/WaterSurfaceStencil, TransparentDegamma (vtable xmm7=[0xF546BAA] unresolved), WaitOnUpscalingOutput, FullScreenOverlayObjects, FullScreenOverlayTransparent.

## TOOL REQUESTS
- None.
