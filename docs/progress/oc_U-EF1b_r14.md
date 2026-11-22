## NEXT
DONE

# oc U-EF1b — VV pass in/out resources from execute bodies (checklist F1b pending part)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis).
Hard rule: the 28-byte pass descriptor is opaque (proven, 5 runs). Per-pass in/out resources live in each pass's EXECUTE body, not its declaration.

## 12 pending passes (update 2026-11-22 after r9; the rest are [V], not redone)
1 VolumetricsShadows  2 SampleCascadedShadows  3 [ClearGBuffer][ScenePrepass]
4 [ClearStencil][WaterSurfaceStencil]  5 TransparentDegamma  6 WaitOnUpscalingOutput
7 ForceRasterizedObjects  8 RasterizedOpaque  9 RasterizedAlphaTest  10 RasterizedTransparent
11 FullScreenOverlayObjects  12 FullScreenOverlayTransparent

## Pass -> declare-helper mapping (verified from builder 0x55f1450 full listing, docs/progress/pre/0x55f1450_full.lst)
| pass | pass-name string ref | declare call site | declare helper | tag |
|---|---|---|---|---|
| VolumetricsShadows | str "VolumetricsShadows" built at builder 0x55fc1c9 ([8297]) | object constructed inline, vtable stored at 0x55fc6f8 ([8510]) | vtable 0xF25C660 assigned to object (lea rax,[0xF25C660]; mov [rsi],rax) | [V] |
| SampleCascadedShadows | str at 0x55fc488 / 0x55fc4d8 ([8416]/[8427]) | 0x55fc531 call 0x568AD40 ([8441]) | sub_568AD40 | [V] |
| [ClearGBuffer][ScenePrepass] | str split 0x55ff650 "r][ScenePrepass]" / 0x55ff65b "[ClearGBuffer][ScenePrepass]" ([10750]/[10752]) | 0x55ff6a5 call 0x56A8BB0 ([10765]) | sub_56A8BB0 | [V] |
| [ClearStencil][WaterSurfaceStencil] | str split 0x560b03f "aterSurfaceStencil]" / 0x560b04a "[ClearStencil][WaterSurfaceStencil]" ([19092]/[19094]) | 0x560b077 call 0x56685C0 ([19102]) | sub_56685C0 | [V] |
| TransparentDegamma | str 0x5610e82 ([23289]) | 0x5610bd3 call 0x5684660 | sub_5684660 (F1b2 pass 23) | [V] |
| WaitOnUpscalingOutput | str 0x562d068 ([43636]) | helper not yet isolated | [?] | [?] |
| ForceRasterizedObjects | str "ForceRasterizedObjects" .rdata 0xF546BA5 loaded at 0x562e91b ([44840]) | 0x562e9ca call 0x56AF0F0 ([44867]) | sub_56AF0F0 | [V] |
| RasterizedOpaque | str "RasterizedOpaque" (.rdata 0xF5BE067 loaded at 0x562e96b [44851]) | declare call after name build not yet isolated | [?] | [?] |
| RasterizedAlphaTest | str .rdata 0xF52CF4C loaded at 0x562eaf8 ([44925]) | 0x562eb57 call 0x56B0940 ([44941]) | sub_56B0940 | [V] |
| RasterizedTransparent | str .rdata 0xF53430F loaded at 0x562ec85 ([44999]) | 0x562ece7 call 0x56B2190 ([50015]) | sub_56B2190 | [V] |
| FullScreenOverlayObjects | str .rdata 0xF5342CB loaded at 0x562ef87 ([45129]) | declare call not yet isolated | [?] | [?] |
| FullScreenOverlayTransparent | str .rdata 0xF5342CB loaded at 0x562f100 ([45197]) | declare call not yet isolated | [?] | [?] |

Note: ForceRasterizedObjects/RasterizedAlphaTest/RasterizedTransparent use THREE different declare helpers (0x56AF0F0, 0x56B0940, 0x56B2190), so they do NOT provably share one body via the same declare helper (contrary to the "same lambda family" guess).

## 4 thunk-chain vtables decoded (update 2026-11-22 after r10, items (a) and (b))
ScreenDraw calibration (verifies slot convention): vtable 0xF44B280 slot 2 (+0x010) = sub_bc04dc0 = execute [V]. Applied identically here: slot 2 = +0x010 entry of each vtable.

Decoded vtables — slot 2 is a getter/destructor, NOT an execute body, and performs no render-resource reads/writes:

vt 0xF25C830: slot 0=sub_5699cb0, slot 1=sub_5699be0, slot 2 (+0x010)=sub_5699c80 (size 0x2c).
vt 0xF25C820: slot 0=sub_1289c0, slot 1=sub_5698400, slot 2 (+0x010)=sub_5699cb0 (size 0x2d), slot 3=sub_5699be0, slot 4=sub_5699c80 (dup of 0xF25C830 slot 2).
vt 0xF0EAB80: slot 0=sub_a2da0, slot 1=sub_76900, slot 2 (+0x010)=sub_1574850 (size 0x23).
vt 0xF25C7B0: slot 0=sub_568c240, slot 1=sub_568c210, slot 2 (+0x010)=sub_568ba80 (size 0x2c). (vt 0xF25C7B0 objects are initialised by sub_568BDC0, which stores [rcx]=0xF25C7B0 at 0x568be0a.)

Slot-2 functions have ZERO direct callers (virtual dispatch only) and are:
- sub_5699c80 / sub_568ba80: NAME accessors — copy the object's name string (inline at +0x88/+0x2C0 if len<=0x10, else heap ptr at +0x98/+0x2D0 with len at +0xA0/+0x2D8) into the caller buffer [rax]/[rax+8]. No render resources read or written.
- sub_1574850: DESTRUCTOR — if dl&1, free 0x2F0 bytes (call 0xE935700), return this. No render resources read or written.
- sub_5699cb0: copy/move helper — calls sub_5699ce0 (which sets [rcx]=0xF25C830), then conditionally releases rsi.

Conclusion: the r10 "take slot 2 of each vtable -> execute body" assumption does NOT hold for these 4 vtables; they are named-data-object vtables (getter/dtor slots), not pass-execute vtables. Their slot-2 functions read/write only pass-object fields, not render targets/buffers.

## Verified reads/writes table (one annotated row per distinct offset; all instr lines verbatim from rdis)

| offset | size | R/W | site (read/store address) | instr | meaning | tag |
|---|---|---|---|---|---|---|
| 0x5699c83 | 8 | R | [rcx+0x98] | `0x5699c83  mov rdx,[rcx+0x98]` | load object name heap ptr (used when len>0x10) | [V] |
| 0x5699c8a | 8 | R | [rcx+0xA0] | `0x5699c8a  cmp qword ptr [rcx+0xA0],0x10` | name length vs 0x10 small-string threshold | [V] |
| 0x5699c94 | 8 | R | [rcx+0x88] | `0x5699c94  mov rcx,[rcx+0x88]` | inline name data at +0x88 (small-string branch) | [V] |
| 0x5699ca4 | 8 | W | [rax] | `0x5699ca4  mov [rax],rcx` | write name ptr into caller output buffer | [V] |
| 0x5699ca7 | 8 | W | [rax+8] | `0x568baa7`-family store; here `0x5699ca7  mov [rax+8],rdx` | write name length/ptr to output+8 | [V] |
| 0x568ba83 | 8 | R | [rcx+0x2D0] | `0x568ba83  mov rdx,[rcx+0x2D0]` | load object name heap ptr (+0x2D0) | [V] |
| 0x568ba8a | 8 | R | [rcx+0x2D8] | `0x568ba8a  cmp qword ptr [rcx+0x2D8],0x10` | name length vs 0x10 threshold (+0x2D8) | [V] |
| 0x568ba94 | 8 | R | [rcx+0x2C0] | `0x568ba94  mov rcx,[rcx+0x2C0]` | inline name data at +0x2C0 (small-string branch) | [V] |
| 0x568baa4 | 8 | W | [rax] | `0x568baa4  mov [rax],rcx` | write name ptr into caller output buffer | [V] |
| 0x568baa7 | 8 | W | [rax+8] | `0x568baa7  mov [rax+8],rdx` | write name length/ptr to output+8 | [V] |
| 0x566787f | 8 | R | [rdx+0x10] | `0x566787f  mov rax,[rdx+0x10]` | sub_5667860 record copy: read src record qword at +0x10 (candidate body-pointer field) | [V] |
| 0x5667883 | 8 | W | [rcx+0x10] | `0x5667883  mov [rcx+0x10],rax` | sub_5667860 record copy: write dst record qword at +0x10 | [V] |
| 0x5667887 | 16 | R | [rdx] | `0x5667887  movups xmm0,[rdx]` | sub_5667860: read 16 bytes of copied 0xE4-byte record from src +0x0 | [V] |
| 0x566788a | 16 | W | [rcx] | `0x566788a  movups [rcx],xmm0` | sub_5667860: write 16 bytes of copied record to dst +0x0 | [V] |

## sub_5667860 record (item (c)) — status
sub_5667860 copies a record from rdx(src) to rcx(dst): qword at +0x10, then movups/movss fields +0x0..+0xE4, dword at +0xE4, then a heap string buffer at +0xE8 (allocated via call [0xF99FFA0], copied with sub_eec6de0). The qword copied at +0x10/0x10 is the only code-pointer-sized field; sub_5667860 itself copies it from the source record (no `lea reg,[0x<func>]` store of a body pointer occurs inside sub_5667860 — the store would be in the record's builder). The 4 sub_5667860 declare call sites (builder 0x55f2929, 0x55f6454, 0x55f67b4, 0x563460e) are NOT in the 12 pending-pass list, so item (c) does not resolve any pending pass.

## sub_5684660 TransparentDegamma (item (d)) — status
sub_5684660 (declare helper, builder call 0x5610bd3) is a large config builder (0x5684660..0x5686660). It reads a1+0x10/0x18/0x28/0x60, builds a pass record at [rbp+0x7B8], and branches on [rbp+0x964] (1->sub_5690960, 2->sub_5690E10, 3->sub_56912D0). It sets fields [rbp+0x2B0]/[rbp+0x5A0] and others. No vtable store and no execute-body pointer store isolated in the first 600 instructions; render-resource reads/writes of its execute body not yet isolated.

## CLOSES?
NO. Blocking fact: none of the 12 pending passes has an isolated EXECUTE body with render-resource reads/writes yet. The 4 r10 vtables' slot-2s are name getters / destructor (verified, quoted above), not execute bodies; the declare helpers (sub_5684660, sub_56AF0F0, sub_56B0940, sub_56B2190, sub_56A8BB0, sub_56685C0, sub_567C8B0, sub_568AD40) and their body-pointer/execute slots still need reversing. Only pass->declare-helper mapping is [V] for 9/12 passes; WaitOnUpscalingOutput, RasterizedOpaque, FullScreenOverlayObjects/Transparent helper still open.
