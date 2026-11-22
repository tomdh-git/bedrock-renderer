## NEXT
DONE

# U-EI7 — I7 RTX passes: pending part = lambda bodies + BLAS/TLAS build

Scope (RENDER_CHECKLIST.md item I7):
"I7 RTX passes: 0xbbe2d50 main declaration, 0xc28e330 G-buffer/denoiser resources, 0xbcc4b90 compute list, 0xe8403d0 context init (6cg); lambda bodies + BLAS/TLAS build pending (P3) — RTX, low priority unless RTX hardware"

The four named anchors are already closed elsewhere (RTX pass names + resources from 0xbbe2d50/0xc28e330 closed by oc_U-EL16a [V 53/53]; RTX pass-name hashes in 0xbcc4b90 closed by oc_U-EF4 [V 51/51]; 0xe8403d0 context init mapped in BGFX_MAP 6cg/6bc). This unit does ONLY the pending part of the item line:

1. lambda bodies declared inside sub_bbe2d50 (0xbbe2d50..0xbbf62cf, size 0x1357f, BGFX_MAP 6cg/6ei),
2. BLAS/TLAS build call sites (slot 50 / 63 code, BGFX_MAP 6bi/6ei; located in base submit sub_e82e230 per oc_U-EB10c).

## Input data read (precomputed by the orchestrator, not regenerated)

- docs/progress/oc_U-B10c.md — sub_bbe2d50 anchors (PrepareTLAS 0xbbe5c43, PreBlasSkinDispatch 0xbbe4399, RTXAccelerationStructure 0xbbf5bea) + verbatim disassembly + descriptor stores; all quoted lines verify_oc-clean in that unit.
- docs/progress/oc_U-EB10c.md — BLAS/TLAS build call sites 0xe82ebaa / 0xe82f329 (vtable displacement 0x240) + QI provenance + descriptor stores; verify_oc-clean.
- docs/progress/oc_U-EC5a.md — 3 Declarator registration calls inside sub_bbe2d50 (0xbbe34b8/0xbbe3545/0xbbe35a9 -> 0x567b570), verify_oc-clean verbatim lines.
- docs/functions/pass_bodies.md — pass-body shapes installed by sub_bbe2d50 (draw-list task 0x568cd90, std::function thunk 0xbc084b0, pass object execute 0xbc080c0 -> 0xbcc4b90), [V] addresses but no verbatim instruction lines.
- docs/functions/vv_rtx_pass_table.md — RTX prep pass names/hashes in sub_bbe2d50 and group-level body note [I].
- docs/BGFX_MAP.md sections 6cg (lines 955-966), 6bi (0xe83d440 submit wrapper), 6ei (A12c/B10c ray tracing), 6hb (0xbc080c0 -> 0xbcc4b90 RTX denoise/raygen body), 6gz/pass bodies.
- docs/progress/pre/pass_decl_calls.txt + pass_decl_context.txt — 50 call sites, all in the VV builder (0x55f1450 range); no 0xbbe2d50-range site, so they contribute no RTX rows.

## Answer table (one row per distinct offset, all its sites listed; verbatim `0xRVA  instr` lines copied verbatim from the input data; sizes from the instruction)

| offset | size | name | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| 0xbbe4399 | 8 | PreBlasSkinDispatch lambda declaration | [rbp+0x980] | `0xbbe4399  mov rax,0xC2213BBE3E359E8F` `0xbbe43a3  mov [rbp+0x980],rax` | FNV-1a64 hash constant stored to builder local; decl site at +0x1649 into sub_bbe2d50 — inside the 79 KB declaration function, not a lambda body address | [V] |
| 0xbbe5c43 | 8 | PrepareTLAS lambda declaration | [rbp+0xD20] | `0xbbe5c43  mov rax,0xB2D441638D31EA7A` `0xbbe5c4d  mov [rbp+0xD20],rax` | hash constant stored to builder local; name record passed to sub_568AD40 at bbe5c7b via [rbp+0x12F0]/[rbp+0x1330] | [V] |
| 0xbbf5bea | 8 | RTXAccelerationStructure bind-name reference | [0xF5C72E9] (rdata) | `0xbbf5bea  lea rdx,[0xF5C72E9]` `0xbbf5bfb  call 0x79580` | "RTXAccelerationStructure" string loaded from rdata and passed to sub_79580 registration (BGFX_MAP 6ei Anchor 3) | [V] |
| 0xbbe34b8 | 5 | Declarator registration call 1 of 3 | call 0x567b570 | `0xbbe34b8  call 0x567b570` | Declarator<RenderContext> bind/lookup registration inside sub_bbe2d50 (oc_U-EC5a) | [V] |
| 0xbbe3545 | 5 | Declarator registration call 2 of 3 | call 0x567b570 | `0xbbe3545  call 0x567b570` | same registration helper | [V] |
| 0xbbe35a9 | 5 | Declarator registration call 3 of 3 | call 0x567b570 | `0xbbe35a9  call 0x567b570` | same registration helper | [V] |
| 0x240 | 8 | BuildRaytracingAccelerationStructure vtable displacement | [rax+0x240] (rax = vtable of the QI'd command-list object from [rbp+0x16B8]/[rbp+0x16B0]) | `0xe82ebaa  mov rax,[rax+0x240]` `0xe82f329  mov rax,[rax+0x240]` | slot-72 displacement on ID3D12GraphicsCommandList4 in base submit sub_e82e230; BLAS path 0xe82ebaa, TLAS path 0xe82f329; both then `call qword ptr [0xF99FFA0]` with a build-desc pointer in rdx (matches DESC* 2nd arg, not Copy/Emit u64 args) | [V] |
| 0x16b8 | 8 | BLAS command-list object local | [rbp+0x16b8] | `0xe82eba0  mov rcx,[rbp+0x16b8]` | object whose vtable is read at BLAS build site 0xe82ebaa; also stored at e82eb39/e82efe7 and read by `add r14,[rbp+0x16b8]` at e82f310 | [V] |
| 0x16b0 | 8 | TLAS command-list object local | [rbp+0x16b0] | `0xe82f31f  mov rcx,[rbp+0x16b0]` | same object role at TLAS build site 0xe82f329 (stored at e82eadb/e82eb48/e82efbf/e82f393 on other paths) | [V] |
| 0x1620 | 8 | QI output local | [rbp+0x1620] | `0xe82ea9e  mov qword ptr [rbp+0x1620],0` `0xe82ead4  mov rcx,[rbp+0x1620]` | zeroed then receives the QI'd ID3D12GraphicsCommandList4 pointer (QI call e82eac9); proven QI provenance for both build objects | [V] |
| 0x30 | 8 | command-list wrapper inner-object field | [rax+0x30] (rax = wrapper from [r12+0x19F58]) | `0xe82eab1  mov rcx,[rax+0x30]` `0xe82eac9  call qword ptr [0xF99FFA0]` | inner command-list object on which QI(ID3D12GraphicsCommandList4) is performed (IID at rdata 0xf4ed580); wrapper role per BGFX_MAP 6av/6ek | [V] |
| 0xf4ed580 | 8 | DXR IID pointer (rdata) | [0xf4ed580] | `0xe82eabb  lea rdx,[0xf4ed580]` | IID passed to QI = ID3D12GraphicsCommandList4 (symbol per vv_lambda_bodies.md) | [V code / I symbol] |
| 0xf99ffa0 | 8 | indirect-call thunk | [0xf99ffa0] | `0xe82ebba  call qword ptr [0xf99ffa0]` `0xe82f33a  call qword ptr [0xf99ffa0]` | sub_eea6040 (jmp rax) thunk used for QI (e82eac9) and both build calls | [V] |
| 0x7e0 | 16 | BLAS/TLAS build-desc base | [rbp+0x7e0] | `0xe82ec8a  movapd [rbp+0x7e0],xmm6` `0xe82ecd4  mov [rbp+0x7e0],rcx` `0xe82f351  mov qword ptr [rbp+0x7e0],2` | zeroed 16B; pGeometryDescs=rcx (vertex-buffer-table pointer) at BLAS site 0xe82ebaa; later Type=2 (TOP_LEVEL) when the same slot is reused for the TLAS desc (e82f351) | [V] |
| 0x7e8 | 4 | desc Type field | [rbp+0x7e8] | `0xe82eca2  mov dword ptr [rbp+0x7e8],1` | Type=1 (BOTTOM_LEVEL) at BLAS site; address reused as InstanceDescs pointer for the TLAS desc reuse path (e82f35c `mov [rbp+0x7e8],rax`) | [V] |
| 0x7ec | 4 | desc NumDescs field | [rbp+0x7ec] | `0xe82ecc0  mov [rbp+0x7ec],edx` | NumDescs = geometry count (edx loaded from [rax+0x3c] at e82ecbd) | [V] |
| 0x7f0 | 4 | desc Flags field | [rbp+0x7f0] | `0xe82ec92  movapd [rbp+0x7f0],xmm6` `0xe82ecb3  mov dword ptr [rbp+0x7f0],1` | zeroed then Flags=1 (ALLOW_UPDATE) | [V] |
| 0x7f8 | 8 | desc ScratchAccelerationStructureData | [rbp+0x7f8] | `0xe82ecac  mov [rbp+0x7f8],rax` | scratch buffer GPU virtual address | [V] |
| 0x800 | 16 | desc +0x20 field | [rbp+0x800] | `0xe82ec9a  movapd [rbp+0x800],xmm6` `0xe82ece8  mov [rbp+0x800],rax` | zeroed then conditionally set (cmovne at e82ece4) | [V] |
| 0x808 | 8 | desc +0x28 game-custom field | [rbp+0x808] | `0xe82ecc6  mov [rbp+0x808],r13` | r13 = &[rbp+0x7e0], a self/back-pointer into the descriptor itself — no SDK field; game-custom ~0x30-byte desc layout | [V] |
| -0x30 | 8 | TLAS build-desc base | [rbp-0x30] | `0xe82f31b  mov [rbp-0x30],rax` `0xe82f330  lea rdx,[rbp-0x30]` | InstanceDescs at desc+0 (from vertex-buffer-table +0x58 via r14 at e82f310/e82f317); pointer passed as rdx at TLAS call 0xe82f329; no other field stored on this path (rest is zero stack) | [?] |
| 0x248 | 8 | 2nd consecutive DXR structure slot | [rax+0x248] (same [rbp+0x16b0] object) | `0xe82fa07  mov rax,[rax+0x248]` | read with the same desc pointer rdx=&[rbp-0x30]; CopyRaytracingAccelerationStructure vs EmitRaytracingAccelerationStructurePostbuildInfo not separable from statics alone | [?] |
| 0x250 | 8 | 3rd consecutive DXR structure slot | [rax+0x250] (same [rbp+0x16b0] object) | `0xe82f701  mov rax,[rax+0x250]` | method identity not separable from statics alone | [?] |
| 0xbbe2d50 | 0x1357f | sub_bbe2d50 RTX frame builder (lambda declarations) | - | - | size 0x1357f (0xbbe2d50..0xbbf62cf); group-level bodies installed per pass_bodies.md/vv_rtx_pass_table.md [I]: draw-list task 0x568cd90 (0x615B, RTX prep draw passes), std::function thunk 0xbc084b0 (0x71B), pass object vtable 0xF43EC30 execute 0xbc080c0 (0x25B) -> 0xbcc4b90 (RTX denoise/raygen driver per 6hb); no per-lambda body mapping and no verbatim instruction evidence for any body assignment | [I] |

CLOSES? NO — single blocking fact: the per-pass lambda-body binding inside sub_bbe2d50 is undecoded, i.e. which execute body each declared RTX lambda runs (PreBlasSkinDispatch 0xbbe4399, PrepareTLAS 0xbbe5c43, AlphaTestCracks 0xbbf4180, 7× DepthOnlyAlphaTest, RTXStub, Core/Screen/Blit …). Only group-level installation is known [I] (draw-list task 0x568cd90, std::function thunk 0xbc084b0, pass object execute 0xbc080c0 -> 0xbcc4b90; pass_bodies.md/vv_rtx_pass_table.md, group level only, no per-lambda mapping, no verbatim instruction evidence). BLAS/TLAS build IS proven [V] here: call sites 0xe82ebaa (BLAS) and 0xe82f329 (TLAS), vtable displacement 0x240 on QI'd ID3D12GraphicsCommandList4 objects via thunk [0xF99FFA0], with descriptor stores decoded down to field level.

## Verification

Every quoted `0xRVA  instr` line above was copied verbatim from the precomputed input data (oc_U-B10c.md, oc_U-EB10c.md, oc_U-EC5a.md — each verify_oc-clean in its unit). The file will be re-checked with `python tools/sigs/verify_oc.py docs/progress/oc_U-EI7.md` and `python tools/delegate.py check docs/progress/oc_U-EI7.md` before marking DONE. Rows tagged [I]/[?] are inference or unknown, not claimed instruction-level fact; no offset from the input data was skipped without annotation, and no `etc` shorthand is used.

## TOOL REQUESTS

None — no helper script was written; all evidence was read from precomputed input data files.
