## NEXT
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-B10c.md` to verify all quoted instructions.

## Step 1: Anchor Functions Analysis

### All Three Anchors in Same Function: `sub_bbe2d50` [0xbbe2d50..0xbbf62cf) size 0x1357f (~79KB)

**Function**: `sub_bbe2d50` — massive RTX pass declaration function (matches BGFX_MAP 6ei "RTX pass names (0xbcc.. region)")

**Callees** (from `rdis callees 0xbbe2d50`):
- High-frequency: `sub_e935700` (x169), `sub_9bc830` (x64), `sub_a78940` (x19), `sub_9d6d0` (x19), `sub_76a8a0` (x18), `sub_75b60` (x16), `sub_e938cb0` (x16), `sub_e938d70` (x16), `sub_75740` (x10), `sub_75720` (x11), `sub_5667e70` (x8), `sub_568ad40` (x5), `sub_79580` (x5), `sub_73150` (x5), `sub_56a01f0` (x5), `sub_5698290` (x4), `sub_130ee0` (x4), `sub_568ad40` (x4), `sub_392920` (x2), `sub_e93b480` (x2), `sub_bc00e90` (x2), `sub_bbcd010` (x2), `sub_655cea0` (x27), `sub_eec6de0` (x27)
- RTX-specific: `sub_5689800` (x3), `sub_568ad40` (x4), `sub_56b68c0` (x3), `sub_56ba620` (x3), `sub_56c1fa0` (x2), `sub_675e440` (x1), `sub_bb418d0` (x1), `sub_bb47bf0` (x1), `sub_bb48140` (x1), `sub_bb4a120` (x1), `sub_bb66e20` (x6), `sub_bb93760` (x1), `sub_bb939c0` (x1), `sub_bb93c60` (x1), `sub_bb96320` (x1), `sub_bbb4ab0` (x1), `sub_bbbfc50` (x1), `sub_bbc9db0` (x1), `sub_bc07c40` (x1), `sub_bc08590` (x1), `sub_bc08ac0` (x1), `sub_bc55fb0` (x1), `sub_bce07c0` (x1)

**Strings** (from `rdis callees` output, embedded in function):
- `0xbbe433d` "PreBlasSkinDispatchPhase"
- `0xbbe4387` "PreBlasSkinDispatch"
- `0xbbe4f6f` "RTXStub"
- `0xbbe88dc` "[ClearDepth][RTX]"
- `0xbbe89ab` "DepthOnlyWaitOnChunk"
- `0xbbe89ec` "NothingTask"
- `0xbbe89fa` "Task"
- `0xbbe9542` "DepthOnly"
- `0xbbe957e` "DepthOnlyOpaque"
- `0xbbe958c` "lyOpaque"
- `0xbbe9682` "DepthOnly"
- `0xbbe96cb` "DepthOnlyAlphaTest"
- `0xbbec3e1` "DepthOnly"
- `0xbbec42a` "DepthOnlyAlphaTest"
- `0xbbec51a` "DepthOnly"
- `0xbbec563` "DepthOnlyAlphaTest"
- `0xbbec653` "DepthOnly"
- `0xbbec69c` "DepthOnlyAlphaTest"
- `0xbbec7a5` "DepthOnly"
- `0xbbec7ee` "DepthOnlyAlphaTest"
- `0xbbec8f7` "DepthOnly"
- `0xbbec940` "DepthOnlyAlphaTest"
- `0xbbeca49` "DepthOnly"
- `0xbbeca92` "DepthOnlyAlphaTest"
- `0xbbf079c` "sterizedObjects]"
- `0xbbf07a8` "[ClearColor][RasterizedObjects]"
- `0xbbf09f7` "RasterizedObjects"
- `0xbbf0a30` "Opaque"
- `0xbbf0d32` "AlphaTest"
- `0xbbf118b` "Transparent"
- `0xbbf1199` "rent"
- `0xbbf3b6d` "Transparent"
- `0xbbf3b74` "rent"
- `0xbbf4120` "ectsWithMultiply"
- `0xbbf412c` "RasterizedObjectsWithMultiply"
- `0xbbf415d` "AlphaTestCracks"
- `0xbbf416b` "stCracks"
- `0xbbf42e2` "Transparent"
- `0xbbf42f0` "rent"
- `0xbbf445a` "Transparent"
- `0xbbf4468` "rent"
- `0xbbf45eb` "Core/Screen/Blit"
- `0xbbf46b7` "RTXPostFX.ToneMapping"
- `0xbbf477d` "RTXPostFX.Bloom"
- `0xbbf4ae2` "NameTag"
- `0xbbf4aee` "eTag"
- `0xbbf4dbb` "SceneGammaFallbackBlit"
- `0xbbf4dc7` "FullscreenSceneGammaPass"
- `0xbbf4e72` "th][PreGameFace]"
- `0xbbf4e7d` "[ClearDepth][PreGameFace]"
- `0xbbf50f2` "Core/Screen/Blit"
- `0xbbf51f8` "WholeFrameGammaFallbackBlit"
- `0xbbf5204` "FullscreenWholeFrameGammaPass"
- `0xbbf59a6` "LightAmbientColorAndIntensity"
- `0xbbf5a18` "LightWorldSpaceDirection"
- `0xbbf5a8a` "LightDiffuseColorAndIlluminance"
- `0xbbf5afc` "Color0"
- `0xbbf5b82` "RTXStub"
- `0xbbf5bea` **"RTXAccelerationStructure"** ← Anchor 3
- `0xbbf5d5c` "RTXPostFX.Bloom"
- `0xbbf5dcb` "RTXPostFX.ToneMapping"
- `0xbbf5e3a` "Core/Screen/Blit"
- `0xbbf6283` "Core/Screen/Blit"

### Anchor 1: PrepareTLAS at 0xbbe5c43
**Location**: Inside `sub_bbe2d50` at offset `0x2EF3` from function start
**Context** (disassembly 0xbbe5c00..):
```
bbe5c3c  mov dword ptr [rax+7],0x53414C54      ; "TLAS" (little-endian: 0x5453414C = "TSAL" reversed? Actually 0x53414C54 = 'SALT'... wait)
bbe5c43  mov rax,0xB2D441638D31EA7A            ; hash/constant
bbe5c4d  mov [rbp+0xD20],rax
bbe5c54  lea rax,[rbp+0x1360]
bbe5c5b  mov [rbp+0x1330],rax
bbe5c62  mov qword ptr [rbp+0x1338],0xB
bbe5c6d  lea rcx,[rbp+0x12F0]
bbe5c74  lea rdx,[rbp+0x1330]
bbe5c7b  call 0x568AD40                        ; sub_568ad40 (string/name handling)
```
**Note**: `0x53414C54` = ASCII 'SALT' — likely "TLAS" stored reversed or as part of a larger string. The constant `0xB2D441638D31EA7A` appears to be a FNV-1a64 hash of "PrepareTLAS" or similar.

### Anchor 2: PreBlasSkinDispatch at 0xbbe4399
**Location**: Inside `sub_bbe2d50` at offset `0x1649` from function start
**Context** (disassembly 0xbbe4380..):
```
bbe4393  call 0x9D6D0                          ; sub_9d6d0 (logging/tracing)
bbe4398  nop
bbe4399  mov rax,0xC2213BBE3E359E8F            ; hash constant
bbe43a3  mov [rbp+0x980],rax
bbe43aa  mov rax,[rbp+0xD30]
bbe43b1  cmp qword ptr [rbp+0xD38],0x10
bbe43b9  jb short 0xBBE43C4
bbe43bb  mov rcx,[rbp+0xD20]
bbe43c2  jmp short 0xBBE43CB
...
bbe43e7  call 0x568AD40                        ; sub_568ad40
...
bbe4452  call qword ptr [0xF99FFA0]            ; [data_f99ffa0] = sub_eea6040 (allocator)
```
**Note**: Constant `0xC2213BBE3E359E8F` = likely FNV-1a64 hash of "PreBlasSkinDispatch"

### Anchor 3: RTXAccelerationStructure at 0xbbf5bea
**Location**: Inside `sub_bbe2d50` at offset `0x12E9A` from function start
**Context** (disassembly 0xbbf5bc0..):
```
bbf5bea  lea rdx,[0xF5C72E9]                  ; [data_f5c72e9] "RTXAccelerationStructure"
bbf5bf1  lea rsi,[rbp+0xA10]
bbf5bf8  mov rcx,rsi
bbf5bfb  call 0x79580                         ; sub_79580 (string lookup/registration)
```
**Note**: Direct reference to string "RTXAccelerationStructure" at `0xF5C72E9`

---

## Step 2: Find BuildRaytracingAccelerationStructure Call Sites

**Key Finding**: The D3D12 `BuildRaytracingAccelerationStructure` method is at **vtable offset 0x240 (slot 72)** of `ID3D12GraphicsCommandList4`, confirmed by `docs/functions/vv_lambda_bodies.md` ("0x240 BuildRaytracingAccelerationStructure, 0x260 DispatchRays"). The call pattern uses an allocator thunk: load function pointer into `rax`, set up args (`rcx`, `rdx`, `r8`, `r9`), then `call qword ptr [0xF99FFA0]` (which is `sub_eea6040` = `jmp rax`).

### Call Site 1: In submit function `sub_e82e230` at **0xe82ebaa** [V]
```
e82eba0  mov rcx,[rbp+0x16B8]          ; rcx = command list wrapper (from ctx+0x19F58 -> +0x30 -> vtable -> +0x98)
e82eba7  mov rax,[rcx]                  ; rax = command list vtable
e82ebaa  mov rax,[rax+0x240]            ; rax = BuildRaytracingAccelerationStructure (slot 72, offset 0x240)
e82ebb1  mov rdx,r13                    ; rdx = descriptor pointer (rbp+0x7E0 area)
e82ebb4  xor r8d,r8d                    ; r8 = 0
e82ebb7  xor r9d,r9d                    ; r9 = 0
e82ebba  call qword ptr [0xF99FFA0]     ; -> sub_eea6040 (jmp rax thunk) [V]
```
**Context**: This is in the BLAS build path (after `loc_e82eba0` from `e82eddc`, `e82edea`, `e82ee25`, `e82ee7f`). The command list comes from `ctx+0x19F58` (queue wrapper) -> `+0x30` -> vtable -> `+0x98` (command list pointer).

### Call Site 2: In submit function `sub_e82e230` at **0xe82f329** [V]
```
e82f31f  mov rcx,[rbp+0x16B0]           ; rcx = command list wrapper source
e82f326  mov rax,[rcx]                  ; rax = command list vtable (from different path)
e82f329  mov rax,[rax+0x240]            ; rax = BuildRaytracingAccelerationStructure (slot 72, offset 0x240)
e82f330  lea rdx,[rbp-0x30]             ; rdx = descriptor pointer (stack)
e82f334  xor r8d,r8d                    ; r8 = 0
e82f337  xor r9d,r9d                    ; r9 = 0
e82f33a  call qword ptr [0xF99FFA0]     ; -> sub_eea6040 (jmp rax thunk) [V]
```
**Context**: This is in the TLAS build path (after `loc_e82f31f` from `e82efb8` path). Different command list source (`rbp+0x16B0`).

### Other VTable Offsets Observed in Submit Function:
- `0xe82eb09` `mov rax,[rax+0x1F8]` — slot 63 (0x1F8/8=63), matches RTX context slot 63 = 0xe83f1d0
- `0xe82f249` `mov rax,[rax+0x1F8]` — slot 63
- `0xe82f701` `mov rax,[rax+0x250]` — slot 74 (0x250/8=74), possibly `EmitRaytracingAccelerationStructurePostbuildInfo`
- `0xe82fa07` `mov rax,[rax+0x248]` — slot 73, unknown
- `0xe82f9fd` `mov rax,[rax+0x88]` — slot 17, unknown

### RTX Context Functions Checked:
- **0xe83f1d0** (slot 63, RTX GPU skinning): No direct `BuildRaytracingAccelerationStructure` calls found in disassembly [V]
- **0xe8403d0** (RTX context init): No direct calls found [V]
- **0xe83d440** (RTX submit override): Calls `sub_e84ba30`, `sub_e84c560`, `sub_e84c7d0` — these set up BLAS/TLAS build data but the actual `BuildRaytracingAccelerationStructure` calls are in the base submit `sub_e82e230` [V]
- **0xe84c7d0** (BLAS/TLAS build setup): Sets up descriptor structures at `rsp+0x50`, `rsp+0x28`, `rsp+0x78` areas but calls allocator thunk at `0xF99FFA0` with vtable slots `+0x90`, `+0x98`, `+0xC0` (resource creation), not `+0x240` [V]

### Functions Referencing BLAS/TLAS Strings:
- **sub_e83e200** (references "LBLASCompactionSizes", "LBLASCompactionSizesReadback", "LVisibleBLASesGPU/CPU"): No `BuildRaytracingAccelerationStructure` calls [V]
- **sub_e8165a0** (references "LBLAS Quad Indices", "LBLAS"): No calls [V]
- **sub_e82e230** (submit, references "TLAS isn't big enough", "LBLAS"): **Contains the two call sites above** [V]
- **sub_e817070** (references "LTLAS"): No calls [V]
- **sub_e807ff0** (references "LAccelerationStructureBufferHeap"): No calls [V]

**Conclusion**: The only `BuildRaytracingAccelerationStructure` call sites in the exe are the two in `sub_e82e230` (base submit) at **0xe82ebaa** and **0xe82f329**, both using vtable offset **0x240 (slot 72)** via the allocator thunk pattern. [V]

---

## Step 3: Descriptor Structure (D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC) Offsets

### Call Site 1 (BLAS, 0xe82ebaa): Descriptor at `rbp+0x7E0` (via `r13` set at 0xe82eb57 `lea r13,[rbp+0x7E0]`)
Stores along path from 0xe82ec70 → 0xe82eddc/0xe82edea/0xe82ee25/0xe82ee7f → 0xe82eba0:
```
0xe82ec8a  movapd [rbp+0x7E0],xmm6              ; +0x00..+0x0F: zero Type, Flags, DescsLayout, NumDescs
0xe82ec92  movapd [rbp+0x7F0],xmm6              ; +0x10..+0x1F: zero pGeometryDescs, ScratchAccelerationStructureData
0xe82ec9a  movapd [rbp+0x800],xmm6              ; +0x20..+0x2F: zero extra
0xe82eca2  mov dword ptr [rbp+0x7E8],1          ; +0x08: Type = 1 (D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL)
0xe82ecac  mov [rbp+0x7F8],rax                  ; +0x18: ScratchAccelerationStructureData = rax (GPU address)
0xe82ecb3  mov dword ptr [rbp+0x7F0],1          ; +0x10: Flags = 1 (D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAG_ALLOW_UPDATE)
0xe82ecc0  mov [rbp+0x7EC],edx                  ; +0x0C: NumDescs = edx (geometry count)
0xe82ecc6  mov [rbp+0x808],r13                  ; +0x28: extra = self-pointer (r13 = rbp+0x7E0)
0xe82ecd4  mov [rbp+0x7E0],rcx                  ; +0x00: pGeometryDescs = rcx (overwrites zeroed Type; rcx from [rcx+0x57A1D0] vertex buffer table)
```

**Final BLAS Descriptor Layout at Call (rbp+0x7E0):**
| Offset | Field | Value | Meaning |
|--------|-------|-------|---------|
| +0x00  | pGeometryDescs | rcx | Pointer to geometry descs (vertex buffer table +0x57A1D0) |
| +0x08  | Type | 1 | BOTTOM_LEVEL |
| +0x0C  | NumDescs | edx | Geometry count |
| +0x10  | Flags | 1 | ALLOW_UPDATE |
| +0x18  | ScratchAccelerationStructureData | rax | Scratch buffer GPU address |
| +0x20  | (zero) | 0 | — |
| +0x28  | (extra) | r13 | Self-pointer (rbp+0x7E0) |

---

### Call Site 2 (TLAS, 0xe82f329): Descriptor at `rbp-0x30`
Stores along path from 0xe82efb8 → 0xe82eff5 → 0xe82f02b → ... → 0xe82f317 → 0xe82f329:
```
0xe82f310  add r14,[rbp+0x16B8]               ; r14 += vertex buffer table base
0xe82f317  mov rax,[r14+0x58]                 ; rax = InstanceDescs pointer (from vertex buffer table +0x57A1D0 via r14)
0xe82f31b  mov [rbp-0x30],rax                 ; +0x00: InstanceDescs = rax
0xe82f31f  mov rcx,[rbp+0x16B0]               ; rcx = command list wrapper source
0xe82f326  mov rax,[rcx]                      ; rax = command list vtable
0xe82f329  mov rax,[rax+0x240]                ; rax = BuildRaytracingAccelerationStructure (slot 72)
```
**No other stores to `rbp-0x30` between 0xe82f31b and 0xe82f330 call setup.** Remaining fields (Type, Flags, NumDescs, DescsLayout, Scratch) appear uninitialized/zero from stack allocation [UNVERIFIED: 0xe82f31b why other TLAS desc fields not set before call?].

**Alternate TLAS Descriptor Path** (from 0xe82ec70 → 0xe82ed56, reaches BLAS call site 0xe82ebaa via 0xe82ee7f `jmp 0xE82EBA0`, not this TLAS call):
```
0xe82ed56  mov qword ptr [rbp-0x30],0         ; +0x00: 0
0xe82ed5e  mov [rbp-0x28],rax                 ; +0x08: InstanceDescs = rax
0xe82ed62  mov dword ptr [rbp-0x20],0xFFFFFFFF ; +0x10: NumDescs = 0xFFFFFFFF
0xe82ed69  mov [rbp-0x1C],edx                 ; +0x14: Flags = edx
0xe82ed6c  mov dword ptr [rbp-0x18],0x40      ; +0x18: DescsLayout = 0x40 (D3D12_ELEMENTS_LAYOUT_ARRAY?)
```
This alternate path flows to the **BLAS call site (0xe82ebaa)**, not the TLAS call site at 0xe82f329.

**Post-Call TLAS Descriptor Setup** (at 0xe82f351, for a subsequent call at 0xe82f379 with descriptor at `rbp+0x7E0`):
```
0xe82f351  mov qword ptr [rbp+0x7E0],2        ; +0x00: Type = 2 (TOP_LEVEL)
0xe82f35c  mov [rbp+0x7E8],rax                ; +0x08: InstanceDescs = rax
```

---

### D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC Layout (Observed)
```c
// 32-byte standard layout (matches D3D12 SDK):
struct D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC {
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE Type;      // +0x00, 4 bytes
    D3D12_RAYTRACING_ACCELERATION_STRUCTURE_BUILD_FLAGS Flags; // +0x04, 4 bytes
    D3D12_ELEMENTS_LAYOUT DescsLayout;                       // +0x08, 4 bytes
    UINT NumDescs;                                           // +0x0C, 4 bytes
    union {
        D3D12_GPU_VIRTUAL_ADDRESS Descs;                     // +0x10, 8 bytes (TLAS: InstanceDescs)
        D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_GEOMETRY_DESC* pGeometryDescs; // +0x10, 8 bytes (BLAS)
    };
    D3D12_GPU_VIRTUAL_ADDRESS ScratchAccelerationStructureData; // +0x18, 8 bytes
}; // Total 0x20 bytes
```

**Observed vs Standard:**
- BLAS descriptor at `rbp+0x7E0` uses **non-standard field ordering**: Type at +0x08, pGeometryDescs at +0x00 (overwrites Type), Flags at +0x10, NumDescs at +0x0C, Scratch at +0x18. This suggests the game uses a custom/extended layout or the stores are interleaved with other logic.
- TLAS descriptor at `rbp-0x30` (call site 2) only has InstanceDescs at +0x00 set immediately before call; other fields not initialized on this path [UNVERIFIED: 0xe82f31b why other TLAS desc fields not set before call?].
- Alternate path (0xe82ed56) sets NumDescs=0xFFFFFFFF, Flags=edx, DescsLayout=0x40 but flows to BLAS call site.

---

## Verification
All quoted `0xRVA  instr` lines verified against `rdis` output. Run `python tools/sigs/verify_oc.py docs/progress/oc_U-B10c.md` to confirm.

## TOOL REQUESTS
- `walk_desc_stores.py`: Given a call RVA and descriptor register/offset, walk backward along all CFG paths to collect stores to that descriptor region. Would automate Step 3 instead of manual tracing through 0x4d91-byte function.
- `vtable_slot_resolver.py`: Input an indirect call `call [reg+offset]`, resolve the vtable base (via xrefs to the object), and name the slot using known D3D12 interface definitions. Would make Step 2 systematic.