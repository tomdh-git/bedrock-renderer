## NEXT
DONE

## U-EL2v — L2v TLAS/BLAS: locate the D3D12 build call sites

### Pending part of the checklist item

Item line (RENDER_CHECKLIST.md L2v / 6ei): PrepareTLAS 0xbbe5c43, PreBlasSkinDispatch 0xbbe4399, RTXAccelerationStructure ref 0xbbf5bea (all [V] inside sub_bbe2d50 per oc_U-B10c / oc_U-EB10c / BGFX_MAP 6ei); pending part is **"the D3D12 build call sites not located"**. oc_U-EB10c (mirror item B10c) located them at 0xe82ebaa (BLAS) and 0xe82f329 (TLAS), both using vtable displacement 0x240 on QI'd ID3D12GraphicsCommandList4 objects via thunk [0xF99FFA0]. This unit re-verifies those two call sites directly from the exe and documents them as [V] rows for L2v.

### Verbatim confirmation in the exe (rdis, all checked by verify_oc below)

- `0xe82ebaa  mov rax,[rax+0x240]` then `0xe82ebba  call qword ptr [0xF99FFA0]` — BLAS path [V]
- `0xe82f329  mov rax,[rax+0x240]` then `0xe82f33a  call qword ptr [0xF99FFA0]` — TLAS path [V]
- `0xe82eab1  mov rcx,[rax+0x30]` (wrapper+0x30 = inner cmd-list object) [V]
- `0xe82eabb  lea rdx,[0xF4ED580]` (IID pointer for QI) [V]
- `0xe82ea9e  mov qword ptr [rbp+0x1620],0` (QI output local zeroed) [V]
- `0xe82fa07  mov rax,[rax+0x248]` (second DXR slot) [V]
- `0xe82f701  mov rax,[rax+0x250]` (third DXR slot) [V]

### Answer table (one row per distinct offset, all sites listed)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning [tag] |
|---|---|---|---|---|
| `0x240` | 8 | `[rax+0x240]`; rax = vtable of QI'd cmd-list object | `0xe82ebaa  mov rax,[rax+0x240]` `0xe82f329  mov rax,[rax+0x240]` | `BuildRaytracingAccelerationStructure` vtable slot on ID3D12GraphicsCommandList4; both calls pass a build-descriptor pointer in rdx (BLAS: `&[rbp+0x7E0]`; TLAS: `&[rbp-0x30]`) — 2nd arg = DESC*, matching Build not Copy/EmitPostbuildInfo [V]. Same objects also use consecutive `+0x248` (`0xe82fa07`) and `+0x250` (`0xe82f701`) — the other DXR structure slots [V lines; Copy vs Emit split [?]] |
| `0xF99FFA0` | 8 | `[0xF99FFA0]` (call-thunk data) | `0xe82ebba  call qword ptr [0xF99FFA0]` `0xe82f33a  call qword ptr [0xF99FFA0]` | indirect-call thunk = `sub_eea6040` (`jmp rax`), used for both build call sites [V] |
| `0x16B8` | 8 | `[rbp+0x16B8]` | `0xe82eba0  mov rcx,[rbp+0x16B8]` | BLAS path: holds QI'd `ID3D12GraphicsCommandList4` (rcx = this for the `call [rax+0x240]` at `0xe82ebaa`) [V] |
| `0x16B0` | 8 | `[rbp+0x16B0]` | `0xe82f31f  mov rcx,[rbp+0x16B0]` | TLAS path: holds QI'd `ID3D12GraphicsCommandList4` (rcx = this for the `call [rax+0x240]` at `0xe82f329`) [V] |
| `0x1620` | 8 | `[rbp+0x1620]` | `0xe82ea9e  mov qword ptr [rbp+0x1620],0` | QI output local: zeroed before `call qword ptr [0xF99FFA0]` at `0xe82eac9` receives the QI'd `ID3D12GraphicsCommandList4` [V] |
| `0x30` | 8 | `[rax+0x30]`; rax = `[r12+0x19F58]` (command-list wrapper) | `0xe82eab1  mov rcx,[rax+0x30]` | wrapper+0x30 = underlying command-list object on which `QI(ID3D12GraphicsCommandList4)` is performed at `0xe82eac9` [V code; wrapper role per BGFX_MAP 6av/6ek [I]] |
| `0xF4ED580` | 8 | `[0xF4ED580]` (rdata IID pointer) | `0xe82eabb  lea rdx,[0xF4ED580]` | IID passed to QI = `ID3D12GraphicsCommandList4` (lea [V]; symbol per vv_lambda_bodies.md [I]) |
| `0x248` | 8 | `[rax+0x248]` (same `[rbp+0x16B0]` object) | `0xe82fa07  mov rax,[rax+0x248]` | second consecutive DXR structure slot on same object as TLAS build site — `CopyRaytracingAccelerationStructure` vs `EmitRaytracingAccelerationStructurePostbuildInfo` not separable from statics alone [?] |
| `0x250` | 8 | `[rax+0x250]` (same `[rbp+0x16B0]` object) | `0xe82f701  mov rax,[rax+0x250]` | third consecutive DXR structure slot [V line; method identity [?]] |

### Call site details

**BLAS build site at `0xe82ebaa`** (inside base submit `sub_e82e230`):
- Object source: `[rbp+0x16B8]` holds QI'd `ID3D12GraphicsCommandList4` (from `0xe82eab1` `mov rcx,[rax+0x30]` on wrapper `[r12+0x19F58]`, QI at `0xe82eac9` with IID at rdata `0xF4ED580`) [V]
- Descriptor argument: `rdx = &[rbp+0x7E0]` (BLAS desc: Type=1 BOTTOM_LEVEL at +0x08, pGeometryDescs at +0x00, Flags=1 ALLOW_UPDATE at +0x10) [V]

**TLAS build site at `0xe82f329`** (inside base submit `sub_e82e230`):
- Object source: `[rbp+0x16B0]` holds QI'd `ID3D12GraphicsCommandList4` [V]
- Descriptor argument: `rdx = &[rbp-0x30]` (TLAS desc: InstanceDescs at +0x00, remaining fields not initialized on this path) [?]

CLOSES? YES — the pending part ("the D3D12 build call sites not located") is [V]-proven: both sites located (`0xe82ebaa` BLAS, `0xe82f329` TLAS), both using vtable displacement `0x240` on QI'd `ID3D12GraphicsCommandList4` objects via thunk `[0xF99FFA0]`, with call-argument semantics confirming `0x240` = `BuildRaytracingAccelerationStructure`. Anchors (PrepareTLAS 0xbbe5c43, PreBlasSkinDispatch 0xbbe4399, RTXAccelerationStructure 0xbbf5bea) remain [V] from prior units.

## TOOL REQUESTS
None — existing `rdis` + `verify_oc.py` suffice.
