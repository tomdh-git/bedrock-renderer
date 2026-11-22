## NEXT
DONE

# oc U-EF1b — VV per-pass in/out resources from execute bodies (checklist F1b pending part, BGFX_MAP 6ar/6gz/6ha)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis).
Goal: for each pending pass name in builder 0x55f1450's order list, map pass-name -> declare helper -> pass object vtable -> execute body (slot 1 thunk tail-jumping `0xBC61560` with r8 = body address) -> body's resource reads/writes as [V] rows.

Method (verified, used as-is):
- pass-object vtables: slot 2 = name getter, slot 1 = callback installer thunk that tail-jumps `0xBC61560` with r8 = body address, r9 = this.
- 0xBC61560 (sub_bc61560) stores r8 at pass+0x100 and r9 at pass+0x108 then calls Encoder::reset 0xBC60D10; proof lines: `0xBC61645  mov [rsi+0x100],r8`, `0xBC6164c  mov [rsi+0x108],r9`.
- sub_5698290 family: vt 0xF25C830 slot 1 = sub_5699be0; `0x5699c60  lea r8,[0x5699E30]` r9=this; `0x5699c70  jmp 0xBC61560`; body = sub_5699E30 [V per orchestrator decode].

Verified slot-1 thunk -> body chain (`xr 0xBC61560` + `dis` of each thunk) [V]:
| vt | slot-1 thunk | `lea r8,[body]` line | body rva | body size |
| 0xF25C790 | sub_568B9E0 | `0x568ba60  lea r8,[0x568BCD0]` | 0x568BCD0 | 0x2000 |
| 0xF25C940 | sub_56C85C0 | `0x56c8640  lea r8,[0x56C8810]` | 0x56C8810 | 0xc4 |
| 0xF25C890 | sub_56CA260 | `0x56ca2e0  lea r8,[0x56CA4C0]` | 0x56CA4C0 | 0xc4 |
| 0xF25CA70 | sub_56D0CD0 | `0x56d0d50  lea r8,[0x56D0F50]` | 0x56D0F50 | 0xc4 |
| 0xF43EA70 | sub_bc04270 | `0xbc042f0  lea r8,[0xBC04530]` | 0xBC04530 | 0xc4 |
| 0xF25C830 | sub_5699be0 | `0x5699c60  lea r8,[0x5699E30]` | 0x5699E30 | 0xc4 |

Name strings in builder (pass-order doc vv_builder_pass_order_55f1450.md + PE byte check at RVA confirmed ASCII present) [V]:
| pass | name string RVA | declare helper |
| ClearGBuffer/ScenePrepass | 0x55FF65B | sub_56A8BB0 (per 2026-11-22 pending list) |
| ClearStencil/WaterSurfaceStencil | 0x560B04A | (helper to locate) |
| TransparentDegamma | 0x5610E82 | sub_5684660, call site `0x5610bd3  call 0x5684660` [V in F1b2] |
| WaitOnUpscalingOutput | 0x562D068 | (helper to locate) |
| FullScreenOverlayObjects | 0x562EF35 | 0xBB66E20 (per 2026-11-22 pending list) |
| FullScreenOverlayTransparent | 0x562EF87 | sub_5669AE0 (13 calls, per 2026-11-22 pending list) |

Vtable -> body mapping is verified above, but helper->vtable assignment (which body serves which pass name) is NOT yet resolved statically; the declare helpers configure bindings/resources but the pass-object vtable is installed by the pass-object constructor, not by the helper, so helper->vtable requires builder call-site context not yet decoded.

Vtable xmm7 load in builder [V]: `0x56104c0  movups xmm7,[0xF546BAA]` ; [data_f546baa] = ASCII "RasterizedObjects" (16 bytes at 0xF546BAA: `85ad4b010000009085ad4b01000000c0`? raw read showed fill bytes; the disasm comment names it "RasterizedObjects"). Second loader `0xbbf09f7  movups xmm6,[0xF546BAA]` in sub_bbe2d50. `xr 0xF546BAA` returns exactly 2 xrefs [V].

## Body resource analysis (per body, instruction-level)

### Body 0x568BCD0 (vt 0xF25C790, size 0x2000) — complex render-state/setup body [V]
Reads pass-object/Resources fields and writes render-state block; calls bind-container helper 0x5669770. Verified memory-access lines:
| offset | size | site | instr | meaning |
| rdi+0x40 | 16 | `0x568bec8  movups xmm0,[rdi+0x40]` | read 16B from pass object +0x40 | [V]
| rdi+0x50 | 16 | `0x568becc  movups xmm1,[rdi+0x50]` | read 16B from pass object +0x50 | [V]
| rdi+0x68 | 16 | `0x568bef7  movups xmm0,[rdi+0x68]` | read 16B from pass object +0x68 | [V]
| rdi+0x78 | 8 | `0x568bf0a  lea rdx,[rdi+0x78]` | address of pass object +0x78 passed to sub_5669770 | [V]
| rdi+0x19C | 16 | `0x568bf28  movups xmm0,[rdi+0x19C]` | read 16B render-state | [V]
| rdi+0x1AC | 16 | `0x568bf2f  movups xmm1,[rdi+0x1AC]` | read 16B render-state | [V]
| rdi+0x1C0 | 4 | `0x568bf65  movss xmm0,[rdi+0x1C0]` | read 4B scalar | [V]
| rdi+0x1C4 | 4 | `0x568bf76  movss xmm0,[rdi+0x1C4]` | read 4B scalar | [V]
| rdi+0x1C8 | 4 | `0x568bf87  movss xmm0,[rdi+0x1C8]` | read 4B scalar | [V]
| rdi+0x1CC | 4 | `0x568bf98  movss xmm0,[rdi+0x1CC]` | read 4B scalar | [V]
| rdi+0x1D4 | 16 | `0x568bfb1  movups xmm0,[rdi+0x1D4]` | read 16B | [V]
| rdi+0x1E4 | 16 | `0x568bfb8  movups xmm1,[rdi+0x1E4]` | read 16B | [V]
| rdi+0x1F4 | 16 | `0x568bfbf  movups xmm2,[rdi+0x1F4]` | read 16B | [V]
| rdi+0x202 | 16 | `0x568bfc6  movups xmm3,[rdi+0x202]` | read 16B | [V]
| rdi+0x218 | 8 | `0x568bffc  lea rax,[rdi+0x218]` | address passed onward | [V]
| rdi+0x220 | 16 | `0x568c031  movups xmm1,[rdi+0x220]` | read 16B | [V]
| rdi+0x230 | 16 | `0x568c038  movups xmm2,[rdi+0x230]` | read 16B | [V]
call `0x568bf0e  call 0x5669770` (bind container copy) [V]; calls `0x568c149  call 0xEEC6EC0`, `0x568c16b/0x568c176  call 0x9BC830`, `0x568c18d  call 0x75720`, `0x568c1c0  call 0x568B010`, `0x568c1f6  call 0x568B950`, `0x568c239  call 0xEEC59E0`, `0x568c24b  call 0x568C270`, `0x568c372  call 0x655CEA0` [V].

### Tiny wrapper bodies (size 0xc4) — delegate to pass+0x70 object [V structure]
Each tiny body reads `pass+0x100` (installed body ptr), `pass+0x108` (this), `pass+0x110` (shared_ptr, AddRef'd), `pass+0x70` (impl object) and `pass+0x78` (Resources). Example body 0x56C8810 [V]:
| offset | size | site | instr | meaning |
| pass+0x100 | 8 | `0x56c8826  mov rax,[rcx+0x100]` | read installed body pointer | [V]
| pass+0x110 | 8 | `0x56c8838  mov rax,[rcx+0x110]` | read shared_ptr (AddRef at `0x56c8844`) | [V]
| pass+0x108 | 8 | `0x56c8853  mov rcx,[r8+0x108]` | read stored this | [V]
| pass+0x70 | 8 | `0x56c8866  mov rcx,[r8+0x70]` | read impl-object pointer | [V]
| pass+0x78 | 8 | `0x56c886f  add r8,0x78` | Resources base derived | [V]
Same shape for bodies 0x56CA4C0, 0x56D0F50, 0xBC04530, 0x5699E30 (slot-1 chain verified above) [V].

## TOOL REQUESTS
- None

## Open
- helper -> vtable assignment: which of the 6 bodies serves which of the 6 pass names is not statically resolved (declare helper configures bindings; vtable installed by pass-object constructor at builder call site).
- Tiny wrapper bodies delegate to [pass+0x70 impl-object vtable slot 1]; the real per-pass execute target and its named resource reads/writes are not decoded.
- Named in/out resources (textures/uniforms by name hash) not decoded for these 6 passes.
CLOSES? NO — blocker: helper->vtable assignment and per-body named resource reads/writes not yet decoded for the 6 pending passes, so not all 12 passes have [V] resource rows.
