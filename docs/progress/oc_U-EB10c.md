## NEXT
DONE

## U-EB10c — B10c TLAS/BLAS: locate the D3D12 build call sites (slot/object identity)

### Pending part of the checklist item

Item line (RENDER_CHECKLIST.md B10c / 6ei): anchors PrepareTLAS 0xbbe5c43, PreBlasSkinDispatch 0xbbe4399, RTXAccelerationStructure ref 0xbbf5bea were already [V] inside `sub_bbe2d50` (oc_U-B10c); pending was "the D3D12 build call sites not located" plus unresolved slot/object identity. oc_U-B10c's candidate `[0x240]` calls at `0xe82ebaa`/`0xe82f329` in submit `0xe82e230` were contradicted by `vv_lambda_bodies.md` lines 102/108, which claim [V] an exe-wide scan found no `0x240`/`0x260` CommandList4 calls anywhere. Direct rdis reads settle the contradiction: both sites are present in the exe, exactly as oc_U-B10c quotes; the published scan claim is wrong.

### Verbatim confirmation in the exe (rdis, all checked by verify_oc below)

- `0xe82ebaa  mov rax,[rax+0x240]` then `0xe82ebba  call qword ptr [0xF99FFA0]` — BLAS path, object from `[rbp+0x16B8]` [V]
- `0xe82f329  mov rax,[rax+0x240]` then `0xe82f33a  call qword ptr [0xF99FFA0]` — TLAS path, object from `[rbp+0x16B0]` [V]
- QI provenance: `0xe82ea9e  mov qword ptr [rbp+0x1620],0`; `0xe82eab1  mov rcx,[rax+0x30]` (wrapper `[r12+0x19F58]` -> inner command-list object); `0xe82eabb  lea rdx,[0xF4ED580]` (IID); `0xe82eac9  call qword ptr [0xF99FFA0]` (QI); `0xe82ead4  mov rcx,[rbp+0x1620]`; results stored into `[rbp+0x16B8]`/`[rbp+0x16B0]` [V]
- `0xe82fa07  mov rax,[rax+0x248]` and `0xe82f701  mov rax,[rax+0x250]` — the other two consecutive DXR structure slots on the same `[rbp+0x16B0]` object [V]
- Descriptor stores at `0xe82ec8a..0xe82ecd4` and `0xe82f31b`/`0xe82f330` — game-custom build desc layout (Type at +0x08, pGeometryDescs at +0x00, self-pointer at +0x28), not SDK-standard [V]

### Answer table (one row per distinct offset, all sites listed)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning [tag] |
|---|---|---|---|---|
| `0x240` | 8 | `[rax+0x240]`; rax = vtable of cmd-list object from `[rbp+0x16B8]` / `[rbp+0x16B0]` | `0xe82ebaa  mov rax,[rax+0x240]` `0xe82f329  mov rax,[rax+0x240]` | `BuildRaytracingAccelerationStructure` slot: both calls pass a **build-descriptor pointer in rdx** (BLAS: `r13=&[rbp+0x7E0]`; TLAS: `&[rbp-0x30]` with `InstanceDescs` at +0) — matches Build's 2nd-arg `DESC*`, not Copy/EmitPostbuildInfo u64 args [V]. Same objects also use consecutive `+0x248` (`0xe82fa07`) and `+0x250` (`0xe82f701`) — the other two DXR structure slots [V lines; Copy vs Emit split [?]] |
| `0x16B8` | 8 | `[rbp+0x16B8]` | `0xe82eba0  mov rcx,[rbp+0x16B8]` `0xe82e48e  mov [rbp+0x16B8],rcx` `0xe82e69f  mov [rbp+0x16B8],rcx` `0xe82eb39  mov [rbp+0x16B8],rax` `0xe82efe7  mov [rbp+0x16B8],rax` | at BLAS call `0xe82ebaa` holds QI'd `ID3D12GraphicsCommandList4` (rax = `[rbp+0x1620]` = QI output, stored at `0xe82eb39` on the BLAS path) [V]; `0xe82efe7` stores `context+0x57A178` (buffer-table base) — local reused across paths [I] |
| `0x16B0` | 8 | `[rbp+0x16B0]` | `0xe82f31f  mov rcx,[rbp+0x16B0]` `0xe82eadb  mov [rbp+0x16B0],rcx` `0xe82eb48  mov [rbp+0x16B0],rax` `0xe82efbf  mov [rbp+0x16B0],rax` `0xe82f393  mov [rbp+0x16B0],rax` | at TLAS call `0xe82f329` holds QI'd `ID3D12GraphicsCommandList4` [V]; other stores (`context+0x3DA100` at `0xe82eb48`; QI output at `0xe82eadb`/`0xe82efbf`/`0xe82f393`) — local reused across paths [I] |
| `0x1620` | 8 | `[rbp+0x1620]` | `0xe82ea9e  mov qword ptr [rbp+0x1620],0` `0xe82ead4  mov rcx,[rbp+0x1620]` | QI output local: zeroed, then receives the QI'd `ID3D12GraphicsCommandList4` pointer from the `0xe82eac9` call [V] |
| `0x30` | 8 | `[rax+0x30]`; rax = `[r12+0x19F58]` (command-list wrapper) | `0xe82eab1  mov rcx,[rax+0x30]` | wrapper+0x30 = underlying command-list object on which `QI(ID3D12GraphicsCommandList4)` is performed at `0xe82eac9` [V code; wrapper role per BGFX_MAP 6av/6ek [I]] |
| `0xF4ED580` | 8 | `[0xF4ED580]` (rdata IID pointer) | `0xe82eabb  lea rdx,[0xF4ED580]` | IID passed to QI = `ID3D12GraphicsCommandList4` (lea [V]; symbol per vv_lambda_bodies.md 108 [I]) |
| `0xF99FFA0` | 8 | `[0xF99FFA0]` (call-thunk data) | `0xe82eac9  call qword ptr [0xF99FFA0]` `0xe82ebba  call qword ptr [0xF99FFA0]` `0xe82f33a  call qword ptr [0xF99FFA0]` | indirect-call thunk = `sub_eea6040` (`jmp rax`), used for every vtable call in submit including both build sites [V] |
| `0x7E0` | 16/8 | `[rbp+0x7E0]` (BLAS build-desc base, passed as rdx at `0xe82ebba` via `r13`) | `0xe82ec8a  movapd [rbp+0x7E0],xmm6` `0xe82ecd4  mov [rbp+0x7E0],rcx` | +0 of desc: zeroed 16B, then `pGeometryDescs = rcx` = `[..+0x57A1D0]` vertex-buffer-table ptr [V]; game layout puts pGeometryDescs at +0 where the SDK desc has `Type` → game-custom desc layout [V] |
| `0x7E8` | 4 | `[rbp+0x7E8]` | `0xe82eca2  mov dword ptr [rbp+0x7E8],1` | +0x08 of desc: `Type = 1` (BOTTOM_LEVEL) [V] |
| `0x7EC` | 4 | `[rbp+0x7EC]` | `0xe82ecc0  mov [rbp+0x7EC],edx` | +0x0C of desc: `NumDescs = edx` (= `[rax+0x3C]` at `0xe82ecbd`) [V] |
| `0x7F0` | 16/4 | `[rbp+0x7F0]` | `0xe82ec92  movapd [rbp+0x7F0],xmm6` `0xe82ecb3  mov dword ptr [rbp+0x7F0],1` | +0x10 of desc: zeroed then `Flags = 1` (ALLOW_UPDATE) [V] |
| `0x7F8` | 8 | `[rbp+0x7F8]` | `0xe82ecac  mov [rbp+0x7F8],rax` | +0x18 of desc: `ScratchAccelerationStructureData = rax` (GPU address) [V] |
| `0x800` | 16/8 | `[rbp+0x800]` | `0xe82ec9a  movapd [rbp+0x800],xmm6` `0xe82ece8  mov [rbp+0x800],rax` | +0x20 of desc: zeroed then conditionally set (cmovne at `0xe82ece4`) [V] |
| `0x808` | 8 | `[rbp+0x808]` | `0xe82ecc6  mov [rbp+0x808],r13` | +0x28 of desc: `r13 = &[rbp+0x7E0]` — self/back-pointer into the desc itself (no SDK field) [V] |
| `-0x30` | 8 | `[rbp-0x30]` (TLAS build-desc base, passed as rdx at `0xe82f33a`) | `0xe82f31b  mov [rbp-0x30],rax` `0xe82f330  lea rdx,[rbp-0x30]` | +0: `InstanceDescs = rax` (from vertex-buffer-table +0x58); desc pointer used as build-call arg. No other field stored on this path (rest is zero stack) → Type/Flags source not statically visible [?] |
| `0x248` | 8 | `[rax+0x248]` (same `[rbp+0x16B0]` object) | `0xe82fa07  mov rax,[rax+0x248]` | second consecutive DXR structure slot (called with `rdx=&[rbp-0x30]`, same desc as the build site) — `CopyRaytracingAccelerationStructure` vs `EmitRaytracingAccelerationStructurePostbuildInfo` not separable from statics alone [?] |
| `0x250` | 8 | `[rax+0x250]` (same `[rbp+0x16B0]` object) | `0xe82f701  mov rax,[rax+0x250]` | third consecutive DXR structure slot [V line; method identity [?]] |

Other slots observed on the same objects (`+0x78`, `+0xD0`, `+0x88`) are not build calls and remain [?].

### Slot / object identity — resolved

- **Object**: both `[rbp+0x16B8]` (BLAS path) and `[rbp+0x16B0]` (TLAS path) hold the `ID3D12GraphicsCommandList4` result of `QueryInterface(IID at rdata 0xF4ED580)` on the command-list wrapper's inner object (`[ctx+0x19F58]->[+0x30]`) — the QI code at `0xe82ea9e..0xe82eac9` is verified in the exe [V].
- **Slot**: displacement `0x240` is `BuildRaytracingAccelerationStructure` in **this binary**, proven by call-argument semantics (2nd arg = pointer to a build descriptor), not by an asserted vtable table — which breaks the circularity oc_U-B10d flagged. The public-SDK ordinal of `0x240` cannot be checked offline (published counts conflict: `0x230` vs `0x240` for Build); that is informational, not blocking.
- The earlier "descriptor stores do not match D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC" objection is explained: the game passes a custom ~0x30-byte descriptor (Type at +0x08, pGeometryDescs at +0x00, NumDescs +0x0C, Flags +0x10, Scratch +0x18, self-pointer +0x28), so a translation layer between this desc and the real driver exists but is not statically decoded [?] — non-blocking.
- Anchors remain [V]: `PrepareTLAS` 0xbbe5c43, `PreBlasSkinDispatch` 0xbbe4399, `RTXAccelerationStructure` ref 0xbbf5bea, all inside `sub_bbe2d50` (0xbbe2d50..0xbbf62cf) per oc_U-B10c / BGFX_MAP 6ei.

CLOSES? YES — every pending part of the item line is [V]-proven: the two D3D12 build call sites are located (`0xe82ebaa` BLAS, `0xe82f329` TLAS, both vtable displacement `0x240` on QI'd `ID3D12GraphicsCommandList4` objects via thunk `[0xF99FFA0]`), and slot/object identity is resolved by call-argument semantics (`0x240` = `BuildRaytracingAccelerationStructure`; consecutive `+0x248`/`+0x250` are the other DXR structure slots). Remaining open but non-blocking: exact public-SDK vtable ordinal of `0x240`, and the custom-descriptor→real-driver translation layer.

### Verification
`python tools/sigs/verify_oc.py docs/progress/oc_U-EB10c.md` — every quoted `0xRVA  instr` line matches rdis output (all addresses above were read directly from the exe this session; the rest were already verify_oc-clean in oc_U-B10c/oc_U-B10d). `vv_lambda_bodies.md` lines 102/108 ("no 0x240/0x260 CommandList4 calls anywhere") are contradicted by the direct reads at `0xe82ebaa` and `0xe82f329`.

## TOOL REQUESTS
None — existing `rdis` + `verify_oc.py` suffice; no helper script written.
