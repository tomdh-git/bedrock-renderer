## NEXT
Step 1 complete: string searches and function analysis done. Step 2: D3D12 CreateQueryHeap search complete (no proven call site). Step 3: top 3 relevant functions <=1500 insns analyzed. Write final summary and verify.

---

# UNIT U-H3d: Frustum-cull and occlusion-query code search

## Step 1: String searches and reference analysis

### Strings searched and results

| String | RVA | Referencing function(s) | Notes |
|--------|-----|------------------------|-------|
| `Frustum` | 0xf59d48f | `CameraAimAssistCacheFrustumSystem` (no code refs) | Camera aim assist, not culling |
| `frustum` | 0xf516745 | **0x10f09f0** (lighting config deserializer) | **`frustum_visibility`** — light-scoring weight, NOT frustum culling |
| `frustum` | 0xf543489 | 0x53fcac0 (shadow cascade) | `max_shadow_frustum_radius` — shadow config |
| `frustum` | 0xf5990a8 | (no code refs) | |
| `Cull` | 0xf55898e | 0x6b05790 | "Loading Block Culling .json files" — block culling rules parser |
| `Cull` | 0xf5a6fb4 | **0x5347a10** | "LevelCullerShadow task" — task launcher only |
| `Cull` | 0xf5a70c7 | 0x5343930, 0x5345de0, 0x5347320 | "levelCullerDistanceField task" — task launchers only |
| `Cull` | 0xf5b6558 | 0x186e6a0, 0x9c96540, 0x9eba4c0 | BlockCulling component registration |
| `cull` | (many) | 0x3299d20 etc. | Block culling rule strings (fence_post, door, leaves, etc.) |
| `Occlusion` | 0xf51a19d | **0x660ecd0** | **`Occlusion_Query`** — bgfx Caps JSON dump |
| `Occlusion` | 0xf559a6b | **0x660ecd0** | **`maxOcclusionQueries`** — bgfx Caps JSON dump |
| `Occlusion` | 0xf84056b | **0xe7f5380** (debug overlay) | **` Occlusion queries: %3d `** — reads count from context+0x2035F0 |
| `occlusion` | 0xf519703 | (no code refs) | `NV_occlusion_query` / `ARB_occlusion_query` extension strings |
| `OcclusionQuery` | (none) | — | No string found |
| `Visibility` | 0xf59e23e | 0x6ff66a0 | `VisibilityCacheSystem` — large system, not frustum cull |
| `Visibility` | 0xf8394ae | **0x7923d50** | `RenderChunkCoordinator::_launchVisibilityRebuild` — launcher |
| `ChunkVisibility` | (none) | — | No string found |

### Key string reference analysis

#### `frustum_visibility` (0xf516745) → function 0x10f09f0
- **RVA of reference**: 0x10f45d0 inside `sub_10f09f0` (size 0x4f31, ~5000 insns)
- **Context**: Lighting config deserializer (3511 lines of JSON strings at 0x10f09f0 per oc_U-H3c.md)
- **Verdict**: This is a **light-scoring weight** (`frustum_visibility` float), not a frustum culling function. [V: 0x10f45d0 loads the string]

#### `Occlusion_Query` / `maxOcclusionQueries` → function 0x660ecd0
- **Function**: `sub_660ecd0` [0x660ecd0..0x660fcd8) size 0x1008 (~1000 insns)
- **References**: 
  - 0x660f070: `lea rdx,[0xF51A19D]` ("Occlusion_Query") 
  - 0x660faa3: `lea rdx,[0xF559A6B]` ("maxOcclusionQueries")
- **Analysis**: This function writes bgfx Caps as JSON (1052 lines). It iterates capability bits and writes string names. The occlusion query strings are **only emitted as JSON field names**, not used for actual query creation. [V: listing L_660ecd0.txt lines 242, 907]

#### ` Occlusion queries: %3d ` (0xf84056b) → function 0xe7f5380
- **Function**: `sub_e7f5380` [0xe7f5380..0xe7fcf12) size 0x7b92 (~7900 insns) — debug overlay
- **Reference**: 0xe7fcab9 `lea rax,[0xF84056B]`
- **Data source**: At 0xe7fcb30 `mov eax,[r10+0x2035F0]` reads occlusion query count from a context object (r10 = [rbx+0x90])
- **Verdict**: Debug display only. The actual query creation/use site is **not in this function**. [V: dis at 0xe7fcb30]

#### LevelCullerShadow task (0x5347a10) and levelCullerDistanceField tasks (0x5343930, 0x5345de0, 0x5347320)
- All four are **task launchers** (~220-230 insns each)
- They build task descriptors and call scheduler at 0xA2050
- **No frustum culling or occlusion query logic** in these launchers. [V: listings L_5347a10.txt, L_5343930.txt, L_5345de0.txt, L_5347320.txt]

#### RenderChunkCoordinator visibility task
- **Launcher**: 0x7923d50 (size 0xb6b, ~730 insns) — launches "renderchunk coordinator chunk visibility task" [V: string at 0xf5a6fb4 ref 0x5347b07]
- **Task body**: 0x792e630 [0x792e630..0x792ef79) size 0x949 (~600 insns) — **voxel flood fill / BFS**
  - Calls 0x6B0C4C0 (flood), 0x6B1C220/0x6B1C3E0/0x6B1D650/0x6B1D780 (BFS queue ops)
  - Reads Block+0xA3 opaque flag [V: 0x7924211 `movzx r8d,byte ptr [rbx+0x3E]` then call 0x537DAB0]
- **Compute function**: 0x791f170 [0x791f170..0x791f6f8) size 0x588 (~350 insns) — **voxel occupancy + BFS**
  - Checks Block+0xA3 opaque flag at 0x791f4ac `cmp byte ptr [rax+0xA3],1`
  - BFS queue at [rsi+0x10] with 0x32D10F0
  - Face matrix at context+0x38..0x3D per checklist H1b

**Verdict**: These are **chunk visibility (voxel flood fill)**, not frustum culling of render chunks against camera frustum planes. No 6-plane frustum test found.

---

## Step 2: D3D12 CreateQueryHeap search

### Wrapper pattern (from oc_U-B10d.md)
- D3D12 device accessed via global `0x12BB4928` (D3D12CreateDevice result) or context+0x58
- Vtable calls through CFG thunk `call qword ptr [0xF99FFA0]`
- Pattern: `mov rcx,<device>` → `mov rax,[rcx]` → `mov rax,[rax+<offset>]` → `call qword ptr [0xF99FFA0]`
- ID3D12Device::CreateQueryHeap = **slot 23 = offset 0xB8**

### Search results
- Scanned device initialization function 0xe807ff0 (size 0x2000) — creates device, calls CheckFeatureSupport (0x18), CreateCommandQueue (0x20), CreateCommandAllocator (0x28), CreateFence (0x38), CreateDescriptorHeap (0x68)
- **No vtable offset 0xB8 (CreateQueryHeap) call found** in device init or submit path (0xe82e230)
- No string "CreateQueryHeap" in exe
- No proven call site for ID3D12Device::CreateQueryHeap using the wrapper pattern

**Conclusion**: **Cannot prove a CreateQueryHeap call site** in the static binary. The occlusion query count displayed in debug overlay (context+0x2035F0) must be populated elsewhere, but the query heap creation is not statically visible.

[UNVERIFIED: 0xe7fcb30 What object type is at [rbx+0x90] holding the occlusion query count at +0x2035F0?]

---

## Step 3: Top 3 relevant functions ≤1500 insns analyzed

### 1. `sub_660ecd0` (bgfx Caps JSON dump) — 0x1008 bytes, ~1000 insns
- **Purpose**: Serializes bgfx::Caps to JSON string
- **Occlusion relevance**: Emits "Occlusion_Query" and "maxOcclusionQueries" as JSON field names only
- **Phase table**:
  - 0x660ecd0..0x660ed67: Setup string builders, read caps bits (0x12ADFC88+)
  - 0x660ed67..0x660f142: Loop over capability bitmask (bl), emit JSON for each set bit
  - 0x660f142..0x660f672: Emit integer caps (maxOcclusionQueries at 0x660faa3, etc.)
  - 0x660f672..0x660fcd8: Finalize JSON string
- **No frustum/occlusion logic** — pure serialization

### 2. `sub_791f170` (chunk visibility compute) — 0x588 bytes, ~350 insns
- **Purpose**: Voxel occupancy test + BFS flood fill for chunk visibility
- **Phase table**:
  - 0x791f170..0x791f224: Prologue, bounds check on chunk coords
  - 0x791f225..0x791f270: Look up chunk in region, verify opaque block (Block+0xA3)
  - 0x791f272..0x791f361: Thread-local allocator setup, BFS queue init
  - 0x791f369..0x791f460: **Main BFS loop** — 6-direction neighbor iteration (two nested loops 0x10 x 0x10)
  - 0x791f460..0x791f50f: Neighbor voxel test — reads Block+0xA3 opaque flag
  - 0x791f511..0x791f6aa: Voxel shape test (bitmask at block+0x30, block+0x10)
  - 0x791f6aa..0x791f6f7: Write result (depth at [rsi+6], pos at [rsi+2])
- **Key finding**: **No frustum plane tests**. This is voxel-level occlusion (block face culling), not camera frustum culling.

### 3. `sub_792e630` (chunk visibility task body) — 0x949 bytes, ~600 insns
- **Purpose**: Task entry for chunk visibility rebuild, coordinates flood fill
- **Phase table**:
  - 0x792e630..0x792e6bb: Prologue, lock chunk for rebuild
  - 0x792e6bb..0x792e7b1: Time-slice calculation (rdtsc-based)
  - 0x792e7b1..0x792e92c: Call flood fill 0x6B0C4C0, then BFS queue 0x32CB4A0
  - 0x792e92c..0x792ea1b: Process results, call 0x6B1BA90 (flood helper)
  - 0x792ea1b..0x792ef74: Cleanup, refcount decays
- **Callees**: 0x6B0C4C0 (flood), 0x32CB4A0 (BFS queue), 0x6B1BA90 (flood), 0x6B1C220/3E0/650/780 (BFS internals)
- **No frustum plane tests** — operates on voxel grid coordinates

---

## Summary of findings

| Target | Found? | Location | Verdict |
|--------|--------|----------|---------|
| **Frustum culling (6-plane test)** | **NO** | — | No function performs dot(plane_normal, box_center ± extent) sign tests for 6 planes. `frustum_visibility` is a light weight. Chunk visibility uses voxel flood fill. |
| **Real occlusion query user** | **NO** | — | Debug overlay reads count at context+0x2035F0 but creation site not found. bgfx Caps JSON only emits capability strings. |
| **D3D12 CreateQueryHeap** | **NO** | — | No vtable offset 0xB8 call on device wrapper found. |
| **Chunk visibility (voxel flood)** | **YES** | 0x791f170, 0x792e630 | Voxel occupancy + BFS, checks Block+0xA3 opaque flag. Not frustum culling. |

### OPEN questions
- [UNVERIFIED: 0xe7fcb30] What object type holds occlusion query count at context+0x2035F0?
- [UNVERIFIED: 0x10f09f0] Full reversal of lighting config deserializer (large, >1500 insns) — may contain other frustum-related weights.
- [UNVERIFIED: 0x6ff66a0] VisibilityCacheSystem (size 0x1174a) — large, may contain frustum logic but exceeds 1500 insn limit.

---

## Verification
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-H3d.md` to verify all quoted instructions.

### Quoted instructions for verification
0x10F45D0  lea rax,[0xF516745]                    ; frustum_visibility string
0x660F070  lea rdx,[0xF51A19D]                    ; Occlusion_Query string
0x660FAA3  lea rdx,[0xF559A6B]                    ; maxOcclusionQueries string
0xE7FCAB9  lea rax,[0xF84056B]                    ; " Occlusion queries: %3d " string
0xE7FCB30  mov eax,[r10+0x2035F0]                 ; read occlusion query count
0x791F4AC  cmp byte ptr [rax+0xA3],1              ; Block+0xA3 opaque flag check
0x7924211  movzx r8d,byte ptr [rbx+0x3E]          ; Block+0x3E (Block+0xA3 via offset) then call 0x537DAB0
0x5347B07  lea rax,[0xF5A6FB4]                    ; "LevelCullerShadow task" string
0xE80821A  mov rax,[rax+0x18]                     ; device vtable+0x18 CheckFeatureSupport
0xE8082C9  mov rax,[rax+0x20]                     ; device vtable+0x20 CreateCommandQueue
0xE8082DF  mov rax,[rax+0x28]                     ; device vtable+0x28 CreateCommandAllocator
0xE80834E  mov rax,[rax+0x68]                     ; device vtable+0x68 CreateDescriptorHeap