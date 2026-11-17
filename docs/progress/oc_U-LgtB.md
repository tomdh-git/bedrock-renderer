## NEXT
DONE

# U-LgtB: description read lists, GROUP visitor cases — Light tags 4-7 (checklist R7/R8)

Source data: docs/progress/_lightB_data.txt (read fully, lines 1-135). All four cases use reg **rsi** (stated in each tag header of the data file). Every data line reads/writes [rsi+X] directly, so no line was dropped.

Rules applied here:
- ONE row per distinct [rsi+off] per tag; every site address of that field listed in the read/store-address cell, first site first, the rest comma-separated.
- The verbatim cell is the FIRST instruction of the row, copied verbatim (two spaces after the RVA) from the data file; the size column is that first instruction's access size (movups 16, qword 8, dword/lock-dec-dword 4).
- Meaning only where an instruction shows it (tagged [V] with the site RVA); otherwise '-'.
- The offset cell carries a `(tN)` tag suffix because the same description fields are touched by several of the four cases and the progress checker requires unique rows per file; t4/t5/t6/t7 = tags 4/5/6/7.
- Tag->type names [V]: docs/functions/6640d80_light_visitor.md (sections 2/3/4) and docs/functions/ui_editor_descriptions.md (Light row): tag 4 = ShadowAtlasFrame, tag 5 = ServerGraphicsOverrideParameters, tag 6 = VoxelVolume, tag 7 = TransitioningVoxelVolume.

## tag 4 — ShadowAtlasFrame (head 0x6640ec1, reg rsi, 34 data lines -> 11 fields)

| offset | size | read/store address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 (t4) | 16 | 0x6640ec1, 0x6643865, 0x664387a, 0x6643c8f, 0x6643ca8 | `0x6640ec1  movups xmm6,[rsi]` | - |
| 0x8 (t4) | 8 | 0x6643801, 0x664381d, 0x664385f, 0x6643c85 | `0x6643801  mov rax,[rsi+8]` | 0x664381d: ptr += 0xC8 [V]; 0x664385f, 0x6643c85: atomic dec [V] |
| 0xC (t4) | 4 | 0x6643874, 0x6643c9e | `0x6643874  lock dec dword ptr [rsi+0xC]` | atomic dec [V] |
| 0x10 (t4) | 16 | 0x6640ecb, 0x6643805 | `0x6640ecb  movups xmm7,[rsi+0x10]` | 0x6643805: 8B read [V] |
| 0x20 (t4) | 16 | 0x6640ed6 | `0x6640ed6  movups xmm8,[rsi+0x20]` | - |
| 0x30 (t4) | 16 | 0x6640ee3 | `0x6640ee3  movups xmm9,[rsi+0x30]` | - |
| 0x40 (t4) | 8 | 0x66418f0 | `0x66418f0  mov rbx,[rsi+0x40]` | - |
| 0x48 (t4) | 8 | 0x6640f01, 0x6640f12 | `0x6640f01  mov rcx,[rsi+0x48]` | - |
| 0x1C8 (t4) | 8 | 0x6641cec, 0x6643483, 0x66436d2, 0x6643731, 0x664376f, 0x66437cf | `0x6641cec  sub r13,[rsi+0x1C8]` | 0x664376f: store rdi [V]; 0x66437cf: 32-bit read [V] |
| 0x1D0 (t4) | 8 | 0x6641991, 0x66419c6, 0x664348a, 0x66435a1, 0x66436e2, 0x6643788, 0x66437c9 | `0x6641991  mov r14,[rsi+0x1D0]` | 0x66419c6: ptr += 0x50 [V]; 0x6643788: store rax [V]; 0x66437c9: 32-bit read [V] |
| 0x1D8 (t4) | 8 | 0x6641998, 0x6643738, 0x664379a | `0x6641998  cmp r14,[rsi+0x1D8]` | 0x664379a: store rax [V] |

```
0x6640ec1  movups xmm6,[rsi]
0x6643801  mov rax,[rsi+8]
0x6643874  lock dec dword ptr [rsi+0xC]
0x6640ecb  movups xmm7,[rsi+0x10]
0x6640ed6  movups xmm8,[rsi+0x20]
0x6640ee3  movups xmm9,[rsi+0x30]
0x66418f0  mov rbx,[rsi+0x40]
0x6640f01  mov rcx,[rsi+0x48]
0x6641cec  sub r13,[rsi+0x1C8]
0x6641991  mov r14,[rsi+0x1D0]
0x6641998  cmp r14,[rsi+0x1D8]
```

## tag 5 — ServerGraphicsOverrideParameters (head 0x66417af, reg rsi, 16 data lines -> 5 fields)

| offset | size | read/store address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x8 (t5) | 8 | 0x6642b5e, 0x6642b7d | `0x6642b5e  mov rax,[rsi+8]` | 0x6642b7d: ptr += 0xC8 [V] |
| 0x10 (t5) | 8 | 0x6642b62 | `0x6642b62  cmp rax,[rsi+0x10]` | - |
| 0x258 (t5) | 8 | 0x664294a, 0x6642acf, 0x6642b29 | `0x664294a  mov r14,[rsi+0x258]` | 0x6642acf: store rdi [V]; 0x6642b29: 32-bit read [V] |
| 0x260 (t5) | 8 | 0x6641846, 0x664186d, 0x6642951, 0x66429ac, 0x6642a70, 0x6642ae4, 0x6642b23 | `0x6641846  mov rbx,[rsi+0x260]` | 0x664186d: ptr += 0xB00 [V]; 0x6642ae4: store rax [V]; 0x6642b23: 32-bit read [V] |
| 0x268 (t5) | 8 | 0x664184d, 0x6642a98, 0x6642af5 | `0x664184d  cmp rbx,[rsi+0x268]` | 0x6642af5: store rax [V] |

```
0x6642b5e  mov rax,[rsi+8]
0x6642b62  cmp rax,[rsi+0x10]
0x664294a  mov r14,[rsi+0x258]
0x6641846  mov rbx,[rsi+0x260]
0x664184d  cmp rbx,[rsi+0x268]
```

## tag 6 — VoxelVolume (head 0x664187d, reg rsi, 45 data lines -> 11 fields)

| offset | size | read/store address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 (t6) | 8 | 0x664187d, 0x6643b74, 0x6643b91, 0x6643ba6, 0x6643bc8, 0x6643bdd, 0x6643c50, 0x6643c65, 0x6643c8f, 0x6643ca8 | `0x664187d  mov rax,[rsi]` | 0x6643b74: 16B store (movups [rsi],xmm0) [V] |
| 0x8 (t6) | 8 | 0x6641b3a, 0x6643ad8, 0x6643af4, 0x6643b8b, 0x6643bc2, 0x6643c4a, 0x6643c85 | `0x6641b3a  mov rax,[rsi+8]` | 0x6643af4: ptr += 0xC8 [V]; 0x6643b8b, 0x6643bc2, 0x6643c4a, 0x6643c85: atomic dec [V] |
| 0xC (t6) | 4 | 0x6643ba0, 0x6643bd7, 0x6643c5f, 0x6643c9e | `0x6643ba0  lock dec dword ptr [rsi+0xC]` | atomic dec [V] |
| 0x10 (t6) | 8 | 0x6641bb4, 0x6643adc, 0x6643b77 | `0x6641bb4  mov r13,[rsi+0x10]` | 0x6643b77: store 0 [V] |
| 0x18 (t6) | 8 | 0x6641bd8, 0x66422df | `0x6641bd8  mov rcx,[rsi+0x18]` | - |
| 0x20 (t6) | 8 | 0x6641bd4, 0x66422e3 | `0x6641bd4  mov rbx,[rsi+0x20]` | - |
| 0x138 (t6) | 4 | 0x6642499 | `0x6642499  sub eax,[rsi+0x138]` | - |
| 0x140 (t6) | 4 | 0x6642493 | `0x6642493  mov eax,[rsi+0x140]` | - |
| 0x270 (t6) | 8 | 0x66424e3, 0x66439ee, 0x6643a15, 0x6643a2a, 0x6643a6a, 0x6643aa9 | `0x66424e3  sub r15,[rsi+0x270]` | 0x6643a6a: store r14 [V]; 0x6643aa9: 32-bit read [V] |
| 0x278 (t6) | 8 | 0x66424c1, 0x66424d4, 0x66439df, 0x6643a03, 0x6643a74, 0x6643ab1 | `0x66424c1  mov rbx,[rsi+0x278]` | 0x66424d4: store rbx [V]; 0x6643a74: store r13 [V]; 0x6643ab1: 32-bit read [V] |
| 0x280 (t6) | 8 | 0x66424c8, 0x6643a36, 0x6643a7e | `0x66424c8  cmp rbx,[rsi+0x280]` | 0x6643a7e: store rdi [V] |

```
0x664187d  mov rax,[rsi]
0x6641b3a  mov rax,[rsi+8]
0x6643ba0  lock dec dword ptr [rsi+0xC]
0x6641bb4  mov r13,[rsi+0x10]
0x6641bd8  mov rcx,[rsi+0x18]
0x6641bd4  mov rbx,[rsi+0x20]
0x6642499  sub eax,[rsi+0x138]
0x6642493  mov eax,[rsi+0x140]
0x66424e3  sub r15,[rsi+0x270]
0x66424c1  mov rbx,[rsi+0x278]
0x66424c8  cmp rbx,[rsi+0x280]
```

## tag 7 — TransitioningVoxelVolume (head 0x6641524, reg rsi, 33 data lines -> 14 fields)

| offset | size | read/store address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 (t7) | 8 | 0x664213a | `0x664213a  mov rax,[rsi]` | - |
| 0x8 (t7) | 8 | 0x66421a9, 0x6643f7a, 0x6643f96 | `0x66421a9  mov rax,[rsi+8]` | 0x6643f96: ptr += 0xC8 [V] |
| 0x10 (t7) | 8 | 0x6642223, 0x6643f7e | `0x6642223  mov r12,[rsi+0x10]` | - |
| 0x18 (t7) | 8 | 0x6641524 | `0x6641524  mov rax,[rsi+0x18]` | - |
| 0x20 (t7) | 8 | 0x6642244, 0x664236e | `0x6642244  mov rcx,[rsi+0x20]` | - |
| 0x28 (t7) | 8 | 0x6642240, 0x6642372 | `0x6642240  mov rbx,[rsi+0x28]` | - |
| 0x38 (t7) | 8 | 0x6641548, 0x664211a | `0x6641548  mov rcx,[rsi+0x38]` | - |
| 0x40 (t7) | 8 | 0x6641544, 0x664211e | `0x6641544  mov rbx,[rsi+0x40]` | - |
| 0x138 (t7) | 4 | 0x6642678 | `0x6642678  sub eax,[rsi+0x138]` | - |
| 0x140 (t7) | 4 | 0x6642672 | `0x6642672  mov eax,[rsi+0x140]` | - |
| 0x168 (t7) | 8 | 0x66426fa, 0x6643d21, 0x6643e3d, 0x6643ec7, 0x6643f01, 0x6643f4e | `0x66426fa  sub r13,[rsi+0x168]` | 0x6643f01: store rbx [V]; 0x6643f4e: 32-bit read [V] |
| 0x170 (t7) | 8 | 0x66426a1, 0x66426ea, 0x6643d28, 0x6643d8d, 0x6643e4d, 0x6643f0f, 0x6643f48 | `0x66426a1  mov r12,[rsi+0x170]` | 0x66426ea: ptr += 0x20 [V]; 0x6643f0f: store r15 [V]; 0x6643f48: 32-bit read [V] |
| 0x178 (t7) | 8 | 0x66426a8, 0x6643ece, 0x6643f19 | `0x66426a8  cmp r12,[rsi+0x178]` | 0x6643f19: store rdi [V] |

```
0x664213a  mov rax,[rsi]
0x66421a9  mov rax,[rsi+8]
0x6642223  mov r12,[rsi+0x10]
0x6641524  mov rax,[rsi+0x18]
0x6642244  mov rcx,[rsi+0x20]
0x6642240  mov rbx,[rsi+0x28]
0x6641548  mov rcx,[rsi+0x38]
0x6641544  mov rbx,[rsi+0x40]
0x6642678  sub eax,[rsi+0x138]
0x6642672  mov eax,[rsi+0x140]
0x66426fa  sub r13,[rsi+0x168]
0x66426a1  mov r12,[rsi+0x170]
0x66426a8  cmp r12,[rsi+0x178]
```

## Observations (structure only; names are [I], pattern is [V] from the tables above)

- The triplets +0x258/+0x260/+0x268 (t5), +0x270/+0x278/+0x280 (t6), +0x168/+0x170/+0x178 (t7), +0x1C8/+0x1D0/+0x1D8 (t4) behave as vector begin/current/end triplets [I]: the middle field is advanced by the record stride (`add qword ptr [rsi+X],0xB00 / 0xC8 / 0x50 / 0x20` respectively) [V], the end field is compared against the current field [V], and the reset path stores three registers into all three fields (0x6642acf/0x6642ae4/0x6642af5; 0x6643a6a/0x6643a74/0x6643a7e; 0x6643f01/0x6643f0f/0x6643f19; 0x664376f/0x6643788/0x664379a) [V].
- +0x8/+0xC/+0x10 appear in the shutdown path of each case with `lock dec dword ptr` at +0x8 and +0xC [V] — a shared control block pattern; the field NAMES (for example a refcount) are not shown by any instruction, so they stay unnamed [?].
- +0x138/+0x140 (t6/t7) are read as a dword pair, `mov eax,[rsi+0x140]; sub eax,[rsi+0x138]` [V] — a size/count computation; meaning beyond that is not shown [?].

## TOOL REQUESTS

- None (no helper script needed; all data was precomputed and the work was transcription + merging).
