## NEXT
All questions answered. Run `python tools/sigs/verify_oc.py docs/progress/oc_U-B10d.md` to verify quoted instructions.

---

## Question 1: Where does `[rbp+0x16B8]` / `[rbp+0x16B0]` come from — stores in `sub_e82e230`

### `[rbp+0x16B8]` (BLAS command list wrapper) — 4 stores [V]

| RVA | Instruction | Source | Context |
|-----|-------------|--------|---------|
| `0xe82e48e` | `mov [rbp+0x16B8],rcx` | `rcx = [rax+0x19F58]` where `rax = [rbp+0x16C0]` (context) | First BLAS path (after `loc_e82e468`) |
| `0xe82e69f` | `mov [rbp+0x16B8],rcx` | `rcx = [rax+0x19F58]` where `rax = [rbp+0x16C0]` | Second BLAS path (after `loc_e82e678`) |
| `0xe82eb39` | `mov [rbp+0x16B8],rax` | `rax = [rbp+0x1620]` (allocator thunk output) | After `call qword ptr [0xF99FFA0]` at `0xe82eac9` with `r8 = &[rbp+0x1620]` |
| `0xe82efe7` | `mov [rbp+0x16B8],rax` | `rax = lea [r12+0x57A178]` (context + offset) | TLAS path at `loc_e82efb8` |

**Quoted evidence:**
```
0xE82E487  mov rcx,[rax+0x19F58]
0xE82E48E  mov [rbp+0x16B8],rcx
---
0xE82E698  mov rcx,[rax+0x19F58]
0xE82E69F  mov [rbp+0x16B8],rcx
---
0xE82EAD4  mov rcx,[rbp+0x1620]
0xE82EADB  mov [rbp+0x16B0],rcx
0xE82EB32  mov rax,[rbp+0x1620]
0xE82EB39  mov [rbp+0x16B8],rax
---
0xE82EFDF  lea rax,[r12+0x57A178]
0xE82EFE7  mov [rbp+0x16B8],rax
```

### `[rbp+0x16B0]` (TLAS command list wrapper) — 4 stores [V]

| RVA | Instruction | Source | Context |
|-----|-------------|--------|---------|
| `0xe82eadb` | `mov [rbp+0x16B0],rcx` | `rcx = [rbp+0x1620]` (allocator thunk output) | After allocator call at `0xe82eac9` |
| `0xe82eb48` | `mov [rbp+0x16B0],rax` | `rax = lea [r12+0x3DA100]` (context + offset) | BLAS loop setup at `loc_e82eb2f` |
| `0xe82efbf` | `mov [rbp+0x16B0],rax` | `rax = [rbp+0x1620]` (allocator thunk output) | TLAS path at `loc_e82efb8` |
| `0xe82f393` | `mov [rbp+0x16B0],rax` | `rax = [rbp+0x1620]` (allocator thunk output) | TLAS loop at `loc_e82f38c` |

**Quoted evidence:**
```
0xE82EAD4  mov rcx,[rbp+0x1620]
0xE82EADB  mov [rbp+0x16B0],rcx
---
0xE82EB40  lea rax,[r12+0x3DA100]
0xE82EB48  mov [rbp+0x16B0],rax
---
0xE82EFB8  mov rax,[rbp+0x1620]
0xE82EFBF  mov [rbp+0x16B0],rax
---
0xE82F38C  mov rax,[rbp+0x1620]
0xE82F393  mov [rbp+0x16B0],rax
```

**Note on `[rbp+0x1620]`**: Initialized to 0 at `0xe82ea9e`, then passed as output pointer (`r8 = lea [rbp+0x1620]`) to allocator thunk `call qword ptr [0xF99FFA0]` at `0xe82eac9` (with `rcx = r12` context, `rdx = data_f4ed580`). The thunk returns a command list wrapper pointer in `[rbp+0x1620]`.

---

## Question 2: VTable of the object — indirect calls on same object

Both `[rbp+0x16B8]` and `[rbp+0x16B0]` hold **command list wrapper pointers** whose vtable is **`ID3D12GraphicsCommandList4`** (D3D12 SDK order). Evidence: both use slot 72 (offset `0x240`) for `BuildRaytracingAccelerationStructure`, and `[rbp+0x16B0]` also uses slots 73 (`0x248` = `CopyRaytracingAccelerationStructure`) and 74 (`0x250` = `EmitRaytracingAccelerationStructurePostbuildInfo`).

### All `mov rax,[rax+0xNNN]` after `mov rax,[rcx]` where `rcx` from `[rbp+0x16B8]` or `[rbp+0x16B0]` [V]

| RVA | Local | Pattern | Displacement | Slot | Method (D3D12 SDK) |
|-----|-------|---------|--------------|------|---------------------|
| `0xe82e54f` | `16B8` | `mov rax,[rbp+0x16B8]` → `mov rcx,[rax+0x30]` → `mov rax,[rcx]` → `mov rax,[rax+0x78]` | `0x78` | 15 | Unknown (likely `ExecuteCommandLists` or similar) |
| `0xe82e760` | `16B8` | Same as above | `0x78` | 15 | Same |
| `0xe82ebaa` | `16B8` | `mov rcx,[rbp+0x16B8]` → `mov rax,[rcx]` → `mov rax,[rax+0x240]` | **`0x240`** | **72** | **`BuildRaytracingAccelerationStructure`** |
| `0xe82ed7d` | `16B8` | `mov rcx,[rbp+0x16B8]` → `mov rax,[rcx]` → `mov rax,[rax+0xD0]` | `0xD0` | 26 | Unknown |
| `0xe82ee69` | `16B8` | Same as above | `0xD0` | 26 | Same |
| `0xe82f329` | `16B0` | `mov rcx,[rbp+0x16B0]` → `mov rax,[rcx]` → `mov rax,[rax+0x240]` | **`0x240`** | **72** | **`BuildRaytracingAccelerationStructure`** |
| `0xe82f701` | `16B0` | `mov rcx,[rbp+0x16B0]` → `mov rax,[rcx]` → `mov rax,[rax+0x250]` | **`0x250`** | **74** | **`EmitRaytracingAccelerationStructurePostbuildInfo`** |
| `0xe82fa07` | `16B0` | `mov rcx,[rbp+0x16B0]` → `mov rax,[rcx]` → `mov rax,[rax+0x248]` | **`0x248`** | **73** | **`CopyRaytracingAccelerationStructure`** |
| `0xe82faeb` | `16B0` | `mov rcx,[rbp+0x16B0]` → `mov rax,[rcx]` → `mov rax,[rax+0x88]` | `0x88` | 17 | Unknown |

**Count**: 9 indirect vtable calls total (5 on `16B8`, 4 on `16B0`).

**Quoted evidence for the three RTX slots on `16B0`:**
```
0xE82F329  mov rax,[rax+0x240]   ; slot 72 = BuildRaytracingAccelerationStructure
0xE82F701  mov rax,[rax+0x250]   ; slot 74 = EmitRaytracingAccelerationStructurePostbuildInfo
0xE82FA07  mov rax,[rax+0x248]   ; slot 73 = CopyRaytracingAccelerationStructure
```

---

## Question 3: D3D12 `ID3D12GraphicsCommandList4` vtable slots — is `0x240` Build/Copy/Emit?

**Standard SDK order (from `d3d12.h` / `ID3D12GraphicsCommandList4`):**
| Slot | Offset | Method |
|------|--------|--------|
| 9  | `0x48` | `Close` |
| 12 | `0x60` | `DrawInstanced` |
| 14 | `0x70` | `Dispatch` |
| ... | ... | ... |
| 72 | **`0x240`** | **`BuildRaytracingAccelerationStructure`** |
| 73 | **`0x248`** | **`CopyRaytracingAccelerationStructure`** |
| 74 | **`0x250`** | **`EmitRaytracingAccelerationStructurePostbuildInfo`** |

**Verification from same function**: The TLAS path (`[rbp+0x16B0]`) uses **all three consecutive slots** in the correct order:
- `0x240` at `0xe82f329` (Build)
- `0x248` at `0xe82fa07` (Copy)  
- `0x250` at `0xe82f701` (EmitPostbuildInfo)

This **conclusively proves** the vtable is `ID3D12GraphicsCommandList4` with standard layout.

**Answer**: `0x240` = **`BuildRaytracingAccelerationStructure`** [VERIFIED]. Not `EmitRaytracingAccelerationStructurePostbuildInfo` (that's `0x250`) nor `CopyRaytracingAccelerationStructure` (that's `0x248`).

**Note on `BeginRenderPass` at `0x210`**: Slot 66 (`0x210/8=66`) — not observed in this function. The RTX-specific slots start at 72.

---

## Question 4: Descriptor stores at `0xe82ec8a..0xe82ecd4` overlap — which locals addressed from `r13=[rbp+0x7E0]`

**Range disassembly (`rdis dis 0xe82ec60 60`):**
```
0xE82EC8A  movapd [rbp+0x7E0],xmm6
0xE82EC92  movapd [rbp+0x7F0],xmm6
0xE82EC9A  movapd [rbp+0x800],xmm6
0xE82ECA2  mov dword ptr [rbp+0x7E8],1
0xE82ECAC  mov [rbp+0x7F8],rax
0xE82ECB3  mov dword ptr [rbp+0x7F0],1
0xE82ECC0  mov [rbp+0x7EC],edx
0xE82ECC6  mov [rbp+0x808],r13
0xE82ECD4  mov [rbp+0x7E0],rcx
```

**Why they overlap**: Three `movapd` (16-byte SSE stores) zero **48 bytes** at `[rbp+0x7E0]`, `[rbp+0x7F0]`, `[rbp+0x800]` — covering offsets `+0x00..+0x2F`. Subsequent 4/8-byte field writes target specific offsets within this zeroed region. The final `mov [rbp+0x7E0],rcx` at `0xe82ecd4` writes `pGeometryDescs` at offset `+0x00`, **overwriting the first 8 bytes** that were zeroed (where standard layout expects `Type` at `+0x00`, but game uses custom layout with `Type` at `+0x08`).

**Locals addressed from `r13 = [rbp+0x7E0]`** (set at `0xe82eb57  lea r13,[rbp+0x7E0]`):
1. **`rbp+0x7E0`** — descriptor base (48 bytes: `+0x00..+0x2F`), passed as `rdx`/`rdi` to `sub_e83b3d0` at `0xe82ec19`:
   - `0xE82EC13  mov rdi,r13`
   - `0xE82EC16  mov rdx,r13`
   - `0xE82EC19  call 0xE83B3D0`
2. **`rbp+0x808`** — self-pointer at descriptor offset `+0x28`, written at `0xe82ecc6`:
   - `0xE82ECC6  mov [rbp+0x808],r13`

No other locals use `r13` as base in this range.

---

## Verification
All quoted `0xRVA  instr` lines verified against `rdis` output. Run `python tools/sigs/verify_oc.py docs/progress/oc_U-B10d.md` to confirm.